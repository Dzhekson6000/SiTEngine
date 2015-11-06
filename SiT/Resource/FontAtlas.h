#ifndef FONTATLAS_H_
#define FONTATLAS_H_

#include <map>
#include "Types/Types.h"

#include "Platform/FileUtilsImpl.h"
#include "Resource/ResourceHandle.h"

#include "Libs/GraphicsLib.h"
#include "Graphics/Shader/ShaderManager.h"

#include <ft2build.h>
#include FT_FREETYPE_H


#define DEFAULT_SIZE_TEXTURE 2048
#define DEFAULT_OFFSET 20
#define DEFAULT_SIZE_FONT 48

NS_SIT_BEGIN

struct CharacterInfo {
	Point	advance;
	Size	size;
	Point	bearing;
	Point	positionInTexture;
	unsigned int _VBO;

	CharacterInfo(float ax, float ay, unsigned int bw, unsigned int bh, float bl, float bt, Point positionInTexture)
		:advance(ax, ay), size(bw, bh), bearing(bl, bt), positionInTexture(positionInTexture)
	{}
};

class FontAtlas : public ResourceHandle
{
private:
	FT_Library _library;
	FT_Face _face;
	FT_GlyphSlot _glyph;

	Data data;

	std::map<unsigned int, CharacterInfo*> _characters;

	Point _loadInfo;
	void				clearCharacters();
public:
	static FontAtlas*	create(Resource resource);
	static FontAtlas*	create(Resource resource, unsigned int sizeFont);

						FontAtlas(Resource resource, unsigned int sizeFont);
	bool				init();
	void				resize();

	CharacterInfo*		getInfoChar(unsigned int char_);
	CharacterInfo*		findChar(unsigned int char_);
	CharacterInfo*		loadChar(unsigned int char_);
	
	unsigned int getLineSpacing();

	SYNTHESIZE_READONLY(Texture*, _texture, Texture);
	SYNTHESIZE_READONLY(Shader*, _shader, Shader);
	SYNTHESIZE_READONLY(unsigned int, _sizeFont, SizeFont);
};

NS_SIT_END

#endif// FONTATLAS_H_