#include "Sprite.h"

NS_SIT_BEGIN
/*

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
	image = ResourceManager::getInstance()->getHandle(&Resource(path));

	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;
	_indices[3] = 2;
	_indices[4] = 3;
	_indices[5] = 0;

	return true;
}

void Sprite::createSprite(Shader * shader)
{
	_shader = shader;

	createVertex();

	_shader->useShader();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(shader->getPosLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(shader->getColLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glVertexAttribPointer(shader->getUVLocation(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	glUniformMatrix4fv(_shader->getMVP(), 1, GL_TRUE, (const GLfloat*)transform());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *(image->getTextureId()));
	glUniform1i(_shader->getSamplerLocation(), 0);
	

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);
}

const Matrix4f* Sprite::transform()
{
	Matrix4f scale, rotate, translation;
	scale.InitScaleTransform(_scale.getX(), _scale.getY(), _scale.getZ());
	rotate.InitRotateTransform(_rotate.getX(), _rotate.getY(), _rotate.getZ());
	translation.InitTranslationTransform(_point.getX(), _point.getY(), _point.getZ());
	_transformation = translation * rotate * scale;
	return &_transformation;
}

void Sprite::draw()
{
	_shader->useShader();
	_shader->enableVertexAttribArray();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	_shader->disableVertexAttribArray();
}

void Sprite::setPosition( Point point )
{
	_point = point;
}

void Sprite::setSize( Size size )
{
	_size = size;
}

void Sprite::createVertex()
{
	_vertices[0] = Vertex(Vector3f(-0.5f, -0.5f, 0.0f),Vector3f(1.0f, 1.0f, 1.0f),Vector2f(0.0f, 1.0f));
	_vertices[1] = Vertex(Vector3f(0.5f,-0.5f, 0.0f),Vector3f(1.0f, 1.0f, 1.0f),Vector2f(1.0f, 1.0f));
	_vertices[2] = Vertex(Vector3f(0.5f, 0.5f, 0.0f),Vector3f(1.0f, 1.0f, 1.0f),Vector2f(1.0f, 0.0f));
	_vertices[3] = Vertex(Vector3f(-0.5f, 0.5f, 0.0f),Vector3f(1.0f, 1.0f, 1.0f),Vector2f(0.0f, 0.0f));
}

void Sprite::setScreenSize( Size size )
{
	_screenSize = size;
}*/

NS_SIT_END