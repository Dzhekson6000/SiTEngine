#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Macros.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "GL/glew.h"
#include "glfw3.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#ifndef GL_BGRA
#define GL_BGRA  0x80E1
#endif

#endif

#include "ResourceHandle.h"
#include <map>
#include "Geometry/Geometry.h"

NS_SIT_BEGIN
class Image;
class SIT_DLL Texture: public ResourceHandle
{
private:
	GLuint _textureId;
	unsigned int _width, _height;
	bool _hasPremultipliedAlpha;
public:
	Texture(Resource resource);
	virtual ~Texture();
	void releaseTexture();


	GLuint* getTextureId();
	unsigned int getWidth();
	void setWidth(unsigned int width);
	unsigned int getHeight();
	void setHeight(unsigned int height);
	bool getPremultipliedAlpha(); 

	enum class PixelFormat
	{
		AUTO,
		//! 32-bit texture: BGRA8888
		BGRA8888,
		//! 32-bit texture: RGBA8888
		RGBA8888,
		//! 24-bit texture: RGBA888
		RGB888,
		//! 16-bit texture without Alpha channel
		RGB565,
		//! 8-bit textures used as masks
		A8,
		//! 8-bit intensity texture
		I8,
		//! 16-bit textures used as masks
		AI88,
		//! 16-bit textures: RGBA4444
		RGBA4444,
		//! 16-bit textures: RGB5A1
		RGB5A1,
		//! S3TC-compressed texture: S3TC_Dxt1
		S3TC_DXT1,
		//! S3TC-compressed texture: S3TC_Dxt3
		S3TC_DXT3,
		//! S3TC-compressed texture: S3TC_Dxt5
		S3TC_DXT5,
		//! Default texture format: AUTO
		DEFAULT = AUTO,

		NONE = -1
	};

	struct PixelFormatInfo {
		PixelFormatInfo(GLenum internalFormat, GLenum format, GLenum type, int bpp, bool compressed, bool alpha)
			: _internalFormat(internalFormat)
			, _format(format)
			, _type(type)
			, _bpp(bpp)
			, _alpha(alpha)
		{}
		GLenum _internalFormat;
		GLenum _format;
		GLenum _type;
		int _bpp;
		bool _alpha;
	};

	typedef std::map<Texture::PixelFormat, const PixelFormatInfo> PixelFormatInfoMap;

	static void setDefaultAlphaPixelFormat(Texture::PixelFormat format);
	static Texture::PixelFormat getDefaultAlphaPixelFormat();
	Texture::PixelFormat getPixelFormat() const;

	bool initImage(Image *image);
	bool initImage(Image * image, PixelFormat format);
	bool initData(const void *data, size_t dataLen, Texture::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh);
	bool updateData(const void *data,int offsetX,int offsetY,int width,int height);

private:
	Texture::PixelFormat _pixelFormat;

	static PixelFormat convertDataToFormat(const unsigned char* data, size_t dataLen, PixelFormat originFormat, PixelFormat format, unsigned char** outData, size_t* outDataLen);

	static PixelFormat convertI8ToFormat(const unsigned char* data, size_t dataLen, PixelFormat format, unsigned char** outData, size_t* outDataLen);
	static PixelFormat convertAI88ToFormat(const unsigned char* data, size_t dataLen, PixelFormat format, unsigned char** outData, size_t* outDataLen);
	static PixelFormat convertRGB888ToFormat(const unsigned char* data, size_t dataLen, PixelFormat format, unsigned char** outData, size_t* outDataLen);
	static PixelFormat convertRGBA8888ToFormat(const unsigned char* data, size_t dataLen, PixelFormat format, unsigned char** outData, size_t* outDataLen);

	//I8 to XXX
	static void convertI8ToRGB888(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertI8ToRGBA8888(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertI8ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertI8ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertI8ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertI8ToAI88(const unsigned char* data, size_t dataLen, unsigned char* outData);

	//AI88 to XXX
	static void convertAI88ToRGB888(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertAI88ToRGBA8888(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertAI88ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertAI88ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertAI88ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertAI88ToA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertAI88ToI8(const unsigned char* data, size_t dataLen, unsigned char* outData);

	//RGB888 to XXX
	static void convertRGB888ToRGBA8888(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGB888ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGB888ToI8(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGB888ToAI88(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGB888ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGB888ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData);

	//RGBA8888 to XXX
	static void convertRGBA8888ToRGB888(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGBA8888ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGBA8888ToI8(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGBA8888ToA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGBA8888ToAI88(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGBA8888ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData);
	static void convertRGBA8888ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData);

	static const PixelFormatInfoMap _pixelFormatInfoTables;

};

NS_SIT_END

#endif // TEXTURE_H_