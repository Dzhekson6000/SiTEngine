#ifndef FONTATLAS_H_
#define FONTATLAS_H_

#include "Resource/ResourceHandle.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "Platform/Win32/FileUtilsImpl.h"
#include "GL/glew.h"
#include "glfw3.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "Platform/Android/FileUtilsImpl.h"
#endif

#include <map>
#include "Types/Types.h"
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
	GLuint _VBO;

	CharacterInfo(float ax, float ay, unsigned int bw, unsigned int bh, float bl, float bt, unsigned int x, unsigned int y)
		:advance(ax, ay), size(bw, bh), bearing(bl, bt), positionInTexture(x, y)
	{}
};

class FontAtlas : public ResourceHandle
{
public:
	FontAtlas(Resource resource);
	FontAtlas(Resource resource, unsigned int sizeFont);
	void init();
	void resize();
	CharacterInfo* getInfoChar(unsigned int char_);
	CharacterInfo* findChar(unsigned int char_);
	CharacterInfo* loadChar(unsigned int char_);
	Shader*	getShader();
	GLuint* getTextureId();

	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getSizeFont();
	unsigned int getLineSpacing();
private:

	FT_Library _library;
	FT_Face _face;
	FT_GlyphSlot _glyph;

	Data data;
	GLuint _texure;
	Shader*	_shader;
	unsigned int _width;
	unsigned int _height;
	unsigned int _sizeFont;

	std::map<unsigned int, CharacterInfo*> _characters;

	struct LoadInfo
	{
		unsigned int _x;
		unsigned int _y;
		LoadInfo():_x(0),_y(0){}
	} _loadInfo;
};

NS_SIT_END

#endif// FONTATLAS_H_