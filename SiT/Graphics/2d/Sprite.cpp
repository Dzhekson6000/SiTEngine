#include "Sprite.h"
#include "Libs/GraphicsLib.h"

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

Sprite::~Sprite()
{
	GRAPHICS_LIB()->deleteBuffers(1, &_VBO);
	GRAPHICS_LIB()->deleteBuffers(1, &_IBO);

}

bool Sprite::init(const std::string& path)
{
	_image = ResourceManager::getInstance()->getHandle(new Resource(path));

	_shader = ShaderManager::getInstance()->getShader(Shader::SHADER_NAME_POSITION_TEXTURE);

	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;
	_indices[3] = 2;
	_indices[4] = 3;
	_indices[5] = 0;
	GRAPHICS_LIB()->genBuffers(1, &_IBO);
	GRAPHICS_LIB()->bindBuffer(GraphicsLib::TargetBuffer::ELEMENT_ARRAY_BUFFER, _IBO);
	GRAPHICS_LIB()->bufferData(GraphicsLib::TargetBuffer::ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GraphicsLib::UsageStore::STATIC_DRAW);

	GRAPHICS_LIB()->genBuffers(1, &_VBO);

	setTexture(_image);
	
	GRAPHICS_LIB()->enableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_POSITION));
	GRAPHICS_LIB()->enableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_COLOR));
	GRAPHICS_LIB()->enableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_TEX_COORD));

	return true;
}

void Sprite::updateSize()
{
	Texture* texture = (Texture*)_image;
	_size.setWidth(texture->getSize().getWidth() * _scale.getX());
	_size.setWidth(texture->getSize().getHeight() * _scale.getY());
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

	if(((Texture*)_image)->getPremultipliedAlpha()) GRAPHICS_LIB()->enableAlpha();

	GRAPHICS_LIB()->activeTexture(0);
	GRAPHICS_LIB()->bindTexture((Texture*)_image);
	_shader->setUniformLocationWith1i(_shader->getUniformLocation(_shader->UNIFORM_NAME_SAMPLER), 0);
	_shader->setUniformLocationWithMatrix4fv(_shader->getUniformLocation(_shader->UNIFORM_NAME_MVP_MATRIX), (const GLfloat*)transform(), 1);

	GRAPHICS_LIB()->bindBuffer(GraphicsLib::TargetBuffer::ARRAY_BUFFER, _VBO);
	
	GRAPHICS_LIB()->vertexAttribPointer(_shader->VERTEX_ATTRIB_POSITION, 3, GraphicsLib::DataType::FLOAT, false, sizeof(Vertex), nullptr);
	GRAPHICS_LIB()->vertexAttribPointer(_shader->VERTEX_ATTRIB_COLOR, 3, GraphicsLib::DataType::FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
	GRAPHICS_LIB()->vertexAttribPointer(_shader->VERTEX_ATTRIB_TEX_COORDS, 2, GraphicsLib::DataType::FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	
	GRAPHICS_LIB()->bindBuffer(GraphicsLib::TargetBuffer::ELEMENT_ARRAY_BUFFER, _IBO);
	GRAPHICS_LIB()->drawElements(GraphicsLib::RenderType::TRIANGLES, 6, GraphicsLib::DataType::UNSIGNED_INT, 0);

	if(((Texture*)_image)->getPremultipliedAlpha()) GRAPHICS_LIB()->disableAlpha();
}

void Sprite::setScale(const Scale &scale)
{
	Node::setScale(scale);
	updateSize();
}

void Sprite::setTexture(ResourceHandle* texture)
{
	_image = texture;

	Size* screen = getScreenSize();
	float scaleX = ((Texture*)texture)->getSize().getWidth() / (float)screen->getWidth();
	float scaleY = ((Texture*)texture)->getSize().getHeight() / (float)screen->getHeight();

	float x = -scaleX;
	float y = -scaleY;
	float w = 2 * scaleX;
	float h = 2 * scaleY;

	_vertices[0] = Vertex(Vector(x, y, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 1.0f));
	_vertices[1] = Vertex(Vector(x + w, y, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(1.0f, 1.0f));
	_vertices[2] = Vertex(Vector(x + w, y + h, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(1.0f, 0.0f));
	_vertices[3] = Vertex(Vector(x, y + h, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 0.0f));

	GRAPHICS_LIB()->bindBuffer(GraphicsLib::TargetBuffer::ARRAY_BUFFER, _VBO);
	GRAPHICS_LIB()->bufferData(GraphicsLib::TargetBuffer::ARRAY_BUFFER, sizeof(_vertices), _vertices, GraphicsLib::UsageStore::STATIC_DRAW);
	updateSize();
}

NS_SIT_END