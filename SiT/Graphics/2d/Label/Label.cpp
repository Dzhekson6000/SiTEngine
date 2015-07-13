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

Label::Label(std::string text, unsigned int sizeFont) :
_sizeFont(sizeFont)
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

	_shader = _font->getShader();
}


Matrix<4, 4, float> Label::transform(Point point, CharacterInfo* info)
{
	Size* screen = getScreenSize();

	float scaleSizeFont = (float)_sizeFont / (float)_font->getSizeFont();

	float width = screen->getWidth();
	float height = screen->getHeight();
	float imageWidth = info->_width;
	float imageHeight = info->_height;

	float scaleX = imageWidth / width * scaleSizeFont;
	float scaleY = imageHeight / height * scaleSizeFont;

	MatrixObject scale, rotate, translation;
	scale.initScaleTransform(
		scaleX + _scale.getX() - 1.0f,
		scaleY + _scale.getY() - 1.0f,
		_scale.getZ()
		);

	rotate.initRotateTransform(_rotate.getX(), _rotate.getY(), _rotate.getZ());

	translation.initTranslationTransform(
		((2 * (point.getX() + _point.getX()) - width) / imageWidth),
		((2 * (point.getY() + _point.getY()) - height) / imageHeight),
		point.getZ()
	);

	return translation * rotate * scale;
}

Label::~Label()
{

}

void Label::onDraw()
{
	_shader->use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *(_font->getTextureId()));

	unsigned int offsetX = 0;
	unsigned int offsetY = 0;

	for (unsigned int i = 0; i < _text.size(); i++)
	{
		unsigned int char_ = _text[i];
		CharacterInfo* info = _font->getInfoChar(char_);

		drawChar(
			Point(offsetX + info->_left + info->_width/2,
			-info->_height/2 + info->_top),
		info);

		offsetX += info->_advanceX;
		offsetY += info->_advanceY;
	}
	
	glDisable(GL_BLEND);
}

void Label::setColor(Color color)
{
	_color = color;
}

void Label::drawChar(Point point, CharacterInfo* info)
{
	GLfloat color[4] = { _color._r, _color._g, _color._b, 1 };

	_shader->setUniformLocationWith1i(_shader->getUniformLocation(_shader->UNIFORM_NAME_SAMPLER), 0);
	_shader->setUniformLocationWith4fv(_shader->getUniformLocation(_shader->UNIFORM_NAME_COLOR), (const GLfloat*) color, 1);
	_shader->setUniformLocationWithMatrix4fv(_shader->getUniformLocation(_shader->UNIFORM_NAME_MVP_MATRIX), (const GLfloat*)&transform(point, info), 1);
	
	glBindBuffer(GL_ARRAY_BUFFER, info->_VBO);
	glVertexAttribPointer(_shader->VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(_shader->VERTEX_ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glVertexAttribPointer(_shader->VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Label::draw(Renderer *renderer)
{
	_customCommand.init(1);
	_customCommand.func = CALLBACK_0(Label::onDraw, this);
	renderer->addCommand(&_customCommand);
}

NS_SIT_END