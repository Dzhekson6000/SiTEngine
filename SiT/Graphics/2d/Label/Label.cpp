#include "Label.h"

NS_SIT_BEGIN

Label* Label::create()
{
	auto ret = new Label();

	if (ret)
	{
		ret->autorelease();
	}

	return ret;
}

Label::Label()
{
	//loadFont

	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;
	_indices[3] = 2;
	_indices[4] = 3;
	_indices[5] = 0;

	glGenBuffers(1, &_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

}

const Matrix4f* Label::transform(CharacterInfo* info)
{
	Size screen = *getScreenSize();
	float scaleX = (float)_font->getWidth() / (float)(screen.getWidth() / 2);
	float scaleY = (float)_font->getHeight() / (float)(screen.getHeight() / 2);

	Matrix4f scale, rotate, translation;
	scale.InitScaleTransform(
		scaleX + _scale.getX(),
		scaleY + _scale.getY(),
		_scale.getZ()
		);
	rotate.InitRotateTransform(_rotate.getX(), _rotate.getY(), _rotate.getZ());

	translation.InitTranslationTransform(
		_point.getX() / (float)_font->getWidth(),
		_point.getY() / (float)_font->getHeight(),
		_point.getZ()
		);

	_transformation = translation * rotate * scale;
	return &_transformation;
}

Label::~Label()
{

}

void Label::onDraw()
{
	
}

void Label::setColor(Color color)
{
	_color = color;
}

void Label::drawChar(unsigned int char_)
{
	CharacterInfo* info = _font->getInfoChar(char_);

	Shader* shader = _font->getShader();
	GLfloat color[4] = { _color._r, _color._g, _color._b, 1 };

	shader->use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *(_font->getTextureId()));
	shader->setUniformLocationWith1i(shader->getUniformLocation(shader->UNIFORM_NAME_SAMPLER), 0);
	shader->setUniformLocationWith4fv(shader->getUniformLocation(shader->UNIFORM_NAME_COLOR), (const GLfloat*) color, 1);
	shader->setUniformLocationWithMatrix4fv(shader->getUniformLocation(shader->UNIFORM_NAME_MVP_MATRIX), (const GLfloat*)transform(info), 1);
	
	glBindBuffer(GL_ARRAY_BUFFER, info->_VBO);
	glVertexAttribPointer(_shader->VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(_shader->VERTEX_ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glVertexAttribPointer(_shader->VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDisable(GL_BLEND);
}

void Label::draw(Renderer *renderer)
{
	_customCommand.init(1);
	_customCommand.func = CALLBACK_0(Label::onDraw, this);
	renderer->addCommand(&_customCommand);
}

NS_SIT_END