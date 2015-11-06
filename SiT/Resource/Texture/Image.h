#ifndef IMAGE_H_
#define IMAGE_H_

#include "Base/Ref.h"
#include <string>

#include "Platform/FileUtilsImpl.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "external/jpeg/include/win32/jpeglib.h"
#include "external/png/include/win32/png.h"
#endif

#if TARGET_PLATFORM == PLATFORM_LINUX
#include "jpeglib.h"
#include "png.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#endif


#define RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
	(unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
	((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
	((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
	((unsigned)(unsigned char)(va) << 24))

NS_SIT_BEGIN

class Image: public Ref
{
public:
	enum class DataFormat
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

private:
	unsigned char*				_data;
	size_t						_dataLen;
	int							_width;
	int							_height;
	DataFormat						_fileType;
	Image::PixelFormat			_renderFormat;
	bool						_hasPremultipliedAlpha;

	bool						initJpgData(const unsigned char *  data, size_t dataLen);
	bool						initPngData(const unsigned char * data, size_t dataLen);

	DataFormat						detectFormat(const unsigned char * data, size_t dataLen);
	bool						isPng(const unsigned char * data, size_t dataLen);
	bool						isJpg(const unsigned char * data, size_t dataLen);

	void						premultipliedAlpha();
public:
								Image();
	virtual						~Image();

	bool						initImageFile(const std::string& path);
	bool						initImageData(const unsigned char * data, size_t dataLen);

	inline unsigned char*		getData()               { return _data; }
	inline size_t				getDataLen()			{ return _dataLen; }
	inline DataFormat			getFileType()           { return _fileType; }
	inline Image::PixelFormat	getRenderFormat()		{ return _renderFormat; }
	inline int					getWidth()              { return _width; }
	inline int					getHeight()             { return _height; }
	inline bool					hasPremultipliedAlpha() { return _hasPremultipliedAlpha; }
};

NS_SIT_END

#endif // IMAGE_H_
