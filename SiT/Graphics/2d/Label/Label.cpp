#include "Label.h"

NS_SIT_BEGIN

Label* Label::create()
{
	auto ret = new Label("", DEFAULT_SIZE_FONT);

	if (ret)
	{
		ret->autorelease();
	}

	return ret;
}

Label* Label::create(std::string text)
{
	auto ret = new Label(text, DEFAULT_SIZE_FONT);
	if (ret)
	{
		ret->autorelease();
	}
	return ret;
}
Label* Label::create(std::string text, unsigned int sizeFont)
{
	auto ret = new Label(text, sizeFont);
	if (ret)
	{
		ret->autorelease();
	}
	return ret;
}

Label::Label(std::string text, unsigned int sizeFont)
{
	_font = (FontAtlas *)ResourceManager::getInstance()->getHandle(new Resource("1.ttf"));
	_text = text;

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

const Matrix4f* Label::transform(Point point, CharacterInfo* info)
{
	Size screen = *getScreenSize();
	float scaleX = (float)info->_width / (float)(screen.getWidth() / 2)-1;
	float scaleY = (float)info->_height / (float)(screen.getHeight() / 2)-1;

	Matrix4f scale, rotate, translation;
	scale.InitScaleTransform(
		scaleX + _scale.getX(),
		scaleY + _scale.getY(),
		_scale.getZ()
		);
	rotate.InitRotateTransform(_rotate.getX(), _rotate.getY(), _rotate.getZ());

	translation.InitTranslationTransform(
		(point.getX() + _point.getX()) / (screen.getWidth() / 2),
		(point.getY() + _point.getY()) / (screen.getHeight() / 2),
		point.getZ()
	);

	_transformation = translation * rotate * scale;
	return &_transformation;
}

Label::~Label()
{

}

void Label::onDraw()
{
	unsigned int offsetX = 0;
	unsigned int offsetY = 0;

	for (unsigned int i = 0; i < _text.size(); i++)
	{
		unsigned int char_ = _text[i];
		CharacterInfo* info = _font->getInfoChar(char_);

		drawChar(
			Point(offsetX + info->_left/2,
			info->_top / 2),
		info);

		offsetX += info->_advanceX;
		offsetY += info->_advanceY;
	}
	
}

void Label::setColor(Color color)
{
	_color = color;
}

void Label::drawChar(Point point, CharacterInfo* info)
{
	Shader* shader = _font->getShader();
	GLfloat color[4] = { _color._r, _color._g, _color._b, 1 };

	shader->use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *(_font->getTextureId()));
	shader->setUniformLocationWith1i(shader->getUniformLocation(shader->UNIFORM_NAME_SAMPLER), 0);
	shader->setUniformLocationWith4fv(shader->getUniformLocation(shader->UNIFORM_NAME_COLOR), (const GLfloat*) color, 1);
	shader->setUniformLocationWithMatrix4fv(shader->getUniformLocation(shader->UNIFORM_NAME_MVP_MATRIX), (const GLfloat*)transform(point,info), 1);
	
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