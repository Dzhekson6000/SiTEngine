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
#include "Geometry/Geometry.h"
#include "Graphics/Shader/ShaderManager.h"

#include <ft2build.h>
#include FT_FREETYPE_H


#define DEFAULT_SIZE_TEXTURE 2048
#define DEFAULT_OFFSET 20
#define DEFAULT_SIZE_FONT 48

NS_SIT_BEGIN

struct CharacterInfo {
	float _advanceX;
	float _advanceY;

	float _width;
	float _height;

	float _left;
	float _top;

	GLuint _VBO;

	unsigned int _x;
	unsigned int _y;
	CharacterInfo(float ax, float ay, float bw, float bh, float bl, float bt, unsigned int x, unsigned int y)
		:_advanceX(ax), _advanceY(ay), _width(bw), _height(bh), _left(bl), _top(bt), _x(x), _y(y)
	{}
};

class FontAtlas : public ResourceHandle
{
public:
	FontAtlas(Resource resource);
	void init();
	void resize();
	CharacterInfo* getInfoChar(unsigned int char_);
	CharacterInfo* findChar(unsigned int char_);
	CharacterInfo* loadChar(unsigned int char_);
	Shader*	getShader();
	GLuint* getTextureId();

	unsigned int getWidth();
	unsigned int getHeight();
private:

	FT_Library _library;
	FT_Face _face;
	FT_GlyphSlot _glyph;

	Data data;
	GLuint _texure;
	Shader*	_shader;
	unsigned int _width;
	unsigned int _height;

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