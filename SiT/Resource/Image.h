#ifndef IMAGE_H_
#define IMAGE_H_

#include "Base/Ref.h"
#include <string>

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "Platform/Win32/FileUtilsImpl.h"
#include "external/jpeg/include/win32/jpeglib.h"
#include "external/png/include/win32/png.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "Platform/Android/FileUtilsImpl.h"
#endif

#include "Texture.h"

#define RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
	(unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
	((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
	((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
	((unsigned)(unsigned char)(va) << 24))

NS_SIT_BEGIN

class Image: public Ref
{
public:
	enum class Format
	{
		//! JPEG
		JPG,
		//! PNG
		PNG,
		//! BMP
		BMP,
		//! Unknown format
		UNKOWN
	};
private:
	unsigned char*			_data;
	size_t					_dataLen;
	int						_width;
	int						_height;
	Format					_fileType;
	Texture::PixelFormat	_renderFormat;
	bool					_hasPremultipliedAlpha;

	bool initJpgData(const unsigned char *  data, size_t dataLen);
	bool initPngData(const unsigned char * data, size_t dataLen);

	Format detectFormat(const unsigned char * data, size_t dataLen);
	bool isPng(const unsigned char * data, size_t dataLen);
	bool isJpg(const unsigned char * data, size_t dataLen);

	void premultipliedAlpha();
public:
	Image();
    virtual ~Image();

	bool initImageFile(const std::string& path);
    bool initImageData(const unsigned char * data, size_t dataLen);

	inline unsigned char *		getData()               { return _data; }
	inline size_t				getDataLen()			{ return _dataLen; }
	inline Format				getFileType()           { return _fileType; }
	inline Texture::PixelFormat	getRenderFormat()		{ return _renderFormat; }
	inline int					getWidth()              { return _width; }
	inline int					getHeight()             { return _height; }
	inline bool					hasPremultipliedAlpha() { return _hasPremultipliedAlpha; }
};

NS_SIT_END

#endif // IMAGE_H_
