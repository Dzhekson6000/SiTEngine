#include "Sprite.h"

NS_SIT_BEGIN


Sprite* Sprite::create( const std::string& path )
{
	auto ret = new Sprite;
	if(ret && ret->init(path)) {
		ret->autorelease();
		return ret;
	}
	return nullptr;
}

bool Sprite::init( const std::string& path)
{
	_image = ResourceManager::getInstance()->getHandle(new Resource(path));

	_shader = ShaderManager::getInstance()->getShader(Shader::SHADER_NAME_POSITION_TEXTURE);

	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;
	_indices[3] = 2;
	_indices[4] = 3;
	_indices[5] = 0;


	Size* screen = getScreenSize();
	float scaleX = ((Texture*)_image)->getWidth() / (float)screen->getWidth();
	float scaleY = ((Texture*)_image)->getHeight() / (float)screen->getHeight();

	float x = -scaleX;
	float y = -scaleY;
	float w = 2 * scaleX;
	float h = 2 * scaleY;

	_vertices[0] = Vertex(Vector(x, y, 0.0f),Vector(1.0f, 1.0f, 1.0f),Vector(0.0f, 1.0f));
	_vertices[1] = Vertex(Vector(x+w, y, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(1.0f, 1.0f));
	_vertices[2] = Vertex(Vector(x+w, y+h, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(1.0f, 0.0f));
	_vertices[3] = Vertex(Vector(x, y+h, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 0.0f));


	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_POSITION));
	glEnableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_COLOR));
	glEnableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_TEX_COORD));

	glGenBuffers(1, &_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);
	return true;
}

const Matrix<4, 4, float>* Sprite::transform()
{
	if (_isUpdated)return &_transformation;
	Size* screen = getScreenSize();

	MatrixObject scale, rotate, translation;
	scale.initScaleTransform(_scale);
	rotate.initRotateTransform(_rotate);

	translation.initTranslationTransform(
		_point.getX() / (screen->getWidth() / 2 * _parent->getAbsoluteScaleX()),
		_point.getY() / (screen->getHeight() / 2 * _parent->getAbsoluteScaleY()),
		_point.getZ()
	);

	_transformation = scale * rotate * translation * _parent->getTransformation();

	_isUpdated = true;
	Node::transform();

	return &_transformation;
}

void Sprite::draw( Renderer *renderer )
{
	_customCommand.init(1);
	_customCommand.func = CALLBACK_0(Sprite::onDraw, this);
	renderer->addCommand(&_customCommand);
}

void Sprite::onDraw()
{
	_shader->use();

	if(((Texture*)_image)->getPremultipliedAlpha())
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *( ((Texture*)_image)->getTextureId()));
	_shader->setUniformLocationWith1i(_shader->getUniformLocation(_shader->UNIFORM_NAME_SAMPLER), 0);
	_shader->setUniformLocationWithMatrix4fv(_shader->getUniformLocation(_shader->UNIFORM_NAME_MVP_MATRIX), (const GLfloat*)transform(), 1);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	glVertexAttribPointer(_shader->VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(_shader->VERTEX_ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glVertexAttribPointer(_shader->VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	if(((Texture*)_image)->getPremultipliedAlpha())
	{
		glDisable(GL_BLEND);
	}
}

NS_SIT_END