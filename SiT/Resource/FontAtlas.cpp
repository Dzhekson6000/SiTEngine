#include "FontAtlas.h"


#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>



NS_SIT_BEGIN

FontAtlas::FontAtlas(Resource resource) :ResourceHandle(resource, Type::FONT),
_sizeFont(DEFAULT_SIZE_FONT),
_width(DEFAULT_SIZE_TEXTURE),
_height(DEFAULT_SIZE_TEXTURE)
{
	init();
}

FontAtlas::FontAtlas(Resource resource, unsigned int sizeFont) :ResourceHandle(resource, Type::FONT),
_sizeFont(sizeFont),
_width(DEFAULT_SIZE_TEXTURE),
_height(DEFAULT_SIZE_TEXTURE)
{
	init();
}

void FontAtlas::init()
{
	if (FT_Init_FreeType(&_library)) {
		LOG("FT init error");
		return;
	}

	data = FileUtils::getInstance()->getDataFromFile(getResource()._name);

	if (FT_New_Memory_Face(_library, data.getBytes(), data.getSize(), 0, &_face)) {
		LOG("Could not font");
		return;
	}

	FT_Set_Pixel_Sizes(_face, 0, _sizeFont);

	_shader = ShaderManager::getInstance()->getShader(Shader::SHADER_NAME_POSITION_COLOR_TEXTURE);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &_texure);
	glBindTexture(GL_TEXTURE_2D, _texure);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int* data = (unsigned int*)new GLuint[((_width * _height) * 4 * sizeof(unsigned int))];
	ZeroMemory(data, ((_width * _height) * 4 * sizeof(unsigned int)));

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _width, _height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
	delete[] data;
}

unsigned int FontAtlas::getSizeFont()
{
	return _sizeFont;
}



unsigned int FontAtlas::getLineSpacing()
{
	return _face->glyph->metrics.vertAdvance >> 6;
}

void FontAtlas::resize()
{
	GLuint oldTexture = _texure;
	int newWidth = _width;
	int newHeight = _height;

	int maxSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize);

	if (_height < maxSize)
	{
		newHeight = maxSize-_height;
		if (newHeight > DEFAULT_SIZE_TEXTURE){
			newHeight = _height + DEFAULT_SIZE_TEXTURE;
		}
	}
	else if (_width < maxSize)
	{
		newWidth = maxSize - _width;
		if (newWidth > DEFAULT_SIZE_TEXTURE){
			newWidth = _width + DEFAULT_SIZE_TEXTURE;
		}
	}
	else
	{
		return;//error size texture
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texure);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, newWidth, newHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, NULL);

	_characters.clear();
	_width = newWidth;
	_height = newHeight;
}

CharacterInfo* FontAtlas::loadChar(unsigned int char_)
{
	_glyph = _face->glyph;

	if (FT_Load_Char(_face, char_, FT_LOAD_RENDER))
		return nullptr;	

	if (_loadInfo._x + _glyph->bitmap.width > _width && _loadInfo._y + _glyph->bitmap.rows > _height)
	{
		resize();
		return loadChar(char_);
	} else
	if (_loadInfo._x + _glyph->bitmap.width > _width)
	{
		_loadInfo._x = 0;
		_loadInfo._y += _glyph->bitmap.rows + DEFAULT_OFFSET;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texure);
	glTexSubImage2D(GL_TEXTURE_2D, 0, _loadInfo._x, _loadInfo._y, _glyph->bitmap.width, _glyph->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, _glyph->bitmap.buffer);

	CharacterInfo* characterInfo = new CharacterInfo(
		_glyph->advance.x >>6,
		_glyph->advance.y >> 6,
		_glyph->bitmap.width,
		_glyph->bitmap.rows,
		_glyph->bitmap_left,
		_glyph->bitmap_top,
		_loadInfo._x,
		_loadInfo._y
	);

	float charX = (float)characterInfo->positionInTexture.getX() / _width;
	float charY = (float)characterInfo->positionInTexture.getY() / _height;
	float charWidth = (float)characterInfo->size.getWidth() / _width;
	float charHeight = (float)characterInfo->size.getHeight() / _height;

	Vertex vertices[4];
	vertices[0] = Vertex(Vector(-1.0f, -1.0f, 0.0f), Vector(1.0f, 1.0f, 1.0f),
		Vector(charX, charY + charHeight));
	vertices[1] = Vertex(Vector(1.0f, -1.0f, 0.0f), Vector(1.0f, 1.0f, 1.0f),
		Vector(charX + charWidth, charY + charHeight));
	vertices[2] = Vertex(Vector(1.0f, 1.0f, 0.0f), Vector(1.0f, 1.0f, 1.0f),
		Vector(charX + charWidth, charY));
	vertices[3] = Vertex(Vector(-1.0f, 1.0f, 0.0f), Vector(1.0f, 1.0f, 1.0f),
		Vector(charX, charY));

	glGenBuffers(1, &characterInfo->_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, characterInfo->_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_POSITION));
	glEnableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_COLOR));
	glEnableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_TEX_COORD));

	_characters.insert(std::make_pair(char_, characterInfo));

	_loadInfo._x += _glyph->bitmap.width + DEFAULT_OFFSET;

	return characterInfo;
}

Shader* FontAtlas::getShader()
{
	return _shader;
}

GLuint* FontAtlas::getTextureId()
{
	return &_texure;
}

unsigned int FontAtlas::getWidth()
{
	return _width;
}

unsigned int FontAtlas::getHeight()
{
	return _height;
}

CharacterInfo* FontAtlas::getInfoChar(unsigned int char_)
{
	CharacterInfo* info = findChar(char_);
	if (info == nullptr)
	{
		info = loadChar(char_);
	}
	
	return info;
}

CharacterInfo* FontAtlas::findChar(unsigned int char_)
{
	auto info = _characters.find(char_);
	if (info == _characters.end())
	{
		return nullptr;
	}
	else
	{
		return info->second;
	}
}

NS_SIT_END
