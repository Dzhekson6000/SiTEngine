#include "FontAtlas.h"

#include "Director.h"

#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>

NS_SIT_BEGIN

FontAtlas* FontAtlas::create(Resource resource)
{
	auto ret = new FontAtlas(resource, DEFAULT_SIZE_FONT);
	if (ret && ret->init())
	{
		return ret;
	}
	return nullptr;
}

FontAtlas* FontAtlas::create(Resource resource, unsigned int sizeFont)
{
	auto ret = new FontAtlas(resource, sizeFont);
	if (ret && ret->init())
	{
		return ret;
	}
	return nullptr;
}

FontAtlas::FontAtlas(Resource resource, unsigned int sizeFont) :ResourceHandle(resource, Type::FONT),
_sizeFont(sizeFont)
{
}

bool FontAtlas::init()
{
	if (FT_Init_FreeType(&_library)) {
		LOG("FT init error");
		return false;
	}

	data = FileUtils::getInstance()->getDataFromFile(getResource()._name);

	if (FT_New_Memory_Face(_library, data.getBytes(), data.getSize(), 0, &_face)) {
		LOG("Could not font");
		return false;
	}

	FT_Set_Pixel_Sizes(_face, 0, _sizeFont);

	_shader = ShaderManager::getInstance()->getShader(Shader::SHADER_NAME_POSITION_COLOR_TEXTURE);

	std::string name = "FontAtlas[" + _sizeFont;
	name += "]" + getResource()._name;

	_texture = GRAPHICS_LIB()->createNewTexture(Resource(name));
	_texture->initEmpty(DEFAULT_SIZE_TEXTURE, DEFAULT_SIZE_TEXTURE);

	return true;
}

unsigned int FontAtlas::getLineSpacing()
{
	return _face->glyph->metrics.vertAdvance >> 6;
}

void FontAtlas::resize()
{
	Size textureSize = _texture->getSize();
	unsigned int newWidth = 0;
	unsigned int newHeight = 0;

	int maxSize = GRAPHICS_LIB()->getMaxSizeTexture();

	if (textureSize.getHeight() < maxSize)
	{
		newHeight = maxSize - textureSize.getHeight();
		if (newHeight > DEFAULT_SIZE_TEXTURE)
		{
			newHeight = textureSize.getHeight() + DEFAULT_SIZE_TEXTURE;
		}
	}
	else if (textureSize.getWidth() < maxSize)
	{
		newWidth = maxSize - textureSize.getWidth();
		if (newWidth > DEFAULT_SIZE_TEXTURE)
		{
			newWidth = textureSize.getWidth() + DEFAULT_SIZE_TEXTURE;
		}
	}
	else
	{
		return;//error size texture
	}

	delete _texture;

	std::string name = "FontAtlas[" + _sizeFont;
	name += "]" + getResource()._name;

	_texture = GRAPHICS_LIB()->createNewTexture(Resource(name));
	_texture->initEmpty(DEFAULT_SIZE_TEXTURE, DEFAULT_SIZE_TEXTURE);

	clearCharacters();
}

void FontAtlas::clearCharacters()
{
	for (auto character: _characters)
	{
		GRAPHICS_LIB()->deleteBuffers(1, &character.second->_VBO);
	}
	_characters.clear();
}

CharacterInfo* FontAtlas::loadChar(unsigned int char_)
{
	Size textureSize = _texture->getSize();
	_glyph = _face->glyph;

	if (FT_Load_Char(_face, char_, FT_LOAD_RENDER)) return nullptr;	

	if (_loadInfo.getX() + _glyph->bitmap.width > textureSize.getWidth() &&
		_loadInfo.getY() + _glyph->bitmap.rows > textureSize.getHeight())
	{
		resize();
		return loadChar(char_);
	} else
	if(_loadInfo.getX() + _glyph->bitmap.width > textureSize.getWidth())
	{
		_loadInfo.setX(0);
		_loadInfo.setY(_loadInfo.getY() + _glyph->bitmap.rows + DEFAULT_OFFSET);
	}

	_texture->texSubImage(_loadInfo, 
		Size(_glyph->bitmap.width, _glyph->bitmap.rows),
		Image::PixelFormat::A8,
		_glyph->bitmap.buffer
		);


	CharacterInfo* characterInfo = new CharacterInfo(
		_glyph->advance.x >>6,
		_glyph->advance.y >> 6,
		_glyph->bitmap.width,
		_glyph->bitmap.rows,
		_glyph->bitmap_left,
		_glyph->bitmap_top,
		_loadInfo.getX(),
		_loadInfo.getY()
	);

	float charX = (float)characterInfo->positionInTexture.getX() / textureSize.getWidth();
	float charY = (float)characterInfo->positionInTexture.getY() / textureSize.getHeight();
	float charWidth = (float)characterInfo->size.getWidth() / textureSize.getWidth();
	float charHeight = (float)characterInfo->size.getHeight() / textureSize.getHeight();

	Size* screen = Director::getInstance()->getWinSize();
	float scaleX = characterInfo->size.getWidth() / (float)screen->getWidth();
	float scaleY = characterInfo->size.getHeight() / (float)screen->getHeight();

	Vertex vertices[4];
	float x = -scaleX;
	float y = -scaleY;
	float w = 2 * scaleX;
	float h = 2 * scaleY;

	vertices[0] = Vertex(Vector(x, y, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(charX, charY + charHeight));
	vertices[1] = Vertex(Vector(x + w, y, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(charX + charWidth, charY + charHeight));
	vertices[2] = Vertex(Vector(x + w, y + h, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(charX + charWidth, charY));
	vertices[3] = Vertex(Vector(x, y + h, 0.0f), Vector(1.0f, 1.0f, 1.0f), Vector(charX, charY));

	GRAPHICS_LIB()->genBuffers(1, &characterInfo->_VBO);
	GRAPHICS_LIB()->bindBuffer(GraphicsLib::TargetBuffer::ARRAY_BUFFER, characterInfo->_VBO);
	GRAPHICS_LIB()->bufferData(GraphicsLib::TargetBuffer::ARRAY_BUFFER, sizeof(vertices), vertices, GraphicsLib::UsageStore::STATIC_DRAW);

	GRAPHICS_LIB()->enableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_POSITION));
	GRAPHICS_LIB()->enableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_COLOR));
	GRAPHICS_LIB()->enableVertexAttribArray(_shader->getAttribLocation(_shader->ATTRIBUTE_NAME_TEX_COORD));

	_characters.insert(std::make_pair(char_, characterInfo));

	_loadInfo.setX(_loadInfo.getX() + _glyph->bitmap.width + DEFAULT_OFFSET);

	return characterInfo;
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
