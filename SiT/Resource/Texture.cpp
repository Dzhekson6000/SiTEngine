#include "Texture.h"
#include "Image.h"

NS_SIT_BEGIN

namespace {
	typedef Texture::PixelFormatInfoMap::value_type PixelFormatInfoMapValue;
	static const PixelFormatInfoMapValue TexturePixelFormatInfoTablesValue[] =
	{
		PixelFormatInfoMapValue(Texture::PixelFormat::BGRA8888, Texture::PixelFormatInfo(GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE, 32, false, true)),
		PixelFormatInfoMapValue(Texture::PixelFormat::RGBA8888, Texture::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 32, false, true)),
		PixelFormatInfoMapValue(Texture::PixelFormat::RGBA4444, Texture::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 16, false, true)),
		PixelFormatInfoMapValue(Texture::PixelFormat::RGB5A1, Texture::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 16, false, true)),
		PixelFormatInfoMapValue(Texture::PixelFormat::RGB565, Texture::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 16, false, false)),
		PixelFormatInfoMapValue(Texture::PixelFormat::RGB888, Texture::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 24, false, false)),
		PixelFormatInfoMapValue(Texture::PixelFormat::A8, Texture::PixelFormatInfo(GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 8, false, false)),
		PixelFormatInfoMapValue(Texture::PixelFormat::I8, Texture::PixelFormatInfo(GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE, 8, false, false)),
		PixelFormatInfoMapValue(Texture::PixelFormat::AI88, Texture::PixelFormatInfo(GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 16, false, true)),
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
		PixelFormatInfoMapValue(Texture::PixelFormat::S3TC_DXT1, Texture::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
#endif

#ifdef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
		PixelFormatInfoMapValue(Texture::PixelFormat::S3TC_DXT3, Texture::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif

#ifdef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
		PixelFormatInfoMapValue(Texture::PixelFormat::S3TC_DXT5, Texture::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
	};
}

static Texture::PixelFormat _defaultAlphaPixelFormat = Texture::PixelFormat::DEFAULT;

const Texture::PixelFormatInfoMap Texture::_pixelFormatInfoTables(TexturePixelFormatInfoTablesValue,
																	  TexturePixelFormatInfoTablesValue + sizeof(TexturePixelFormatInfoTablesValue) / sizeof(TexturePixelFormatInfoTablesValue[0]));


Texture::PixelFormat Texture::convertDataToFormat(const unsigned char* data, size_t dataLen, PixelFormat originFormat, PixelFormat format, unsigned char** outData, size_t* outDataLen)
{
	if (format == originFormat || format == PixelFormat::AUTO)
	{
		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return originFormat;
	}

	switch (originFormat)
	{
	case PixelFormat::I8:
		return convertI8ToFormat(data, dataLen, format, outData, outDataLen);
	case PixelFormat::AI88:
		return convertAI88ToFormat(data, dataLen, format, outData, outDataLen);
	case PixelFormat::RGB888:
		return convertRGB888ToFormat(data, dataLen, format, outData, outDataLen);
	case PixelFormat::RGBA8888:
		return convertRGBA8888ToFormat(data, dataLen, format, outData, outDataLen);
	default:
		LOG("unsupport convert for format %d to format %d", originFormat, format);
		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return originFormat;
	}
}

Texture::PixelFormat Texture::convertI8ToFormat(const unsigned char* data, size_t dataLen, PixelFormat format, unsigned char** outData, size_t* outDataLen)
{
	switch (format)
	{
	case PixelFormat::RGBA8888:
		*outDataLen = dataLen*4;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGBA8888(data, dataLen, *outData);
		break;
	case PixelFormat::RGB888:
		*outDataLen = dataLen*3;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGB888(data, dataLen, *outData);
		break;
	case PixelFormat::RGB565:
		*outDataLen = dataLen*2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGB565(data, dataLen, *outData);
		break;
	case PixelFormat::AI88:
		*outDataLen = dataLen*2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToAI88(data, dataLen, *outData);
		break;
	case PixelFormat::RGBA4444:
		*outDataLen = dataLen*2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGBA4444(data, dataLen, *outData);
		break;
	case PixelFormat::RGB5A1:
		*outDataLen = dataLen*2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGB5A1(data, dataLen, *outData);
		break;
	default:
		if (format != PixelFormat::AUTO && format != PixelFormat::I8)
		{
			LOG("Can not convert image format PixelFormat::I8 to format ID:%d, we will use it's origin format PixelFormat::I8", format);
		}

		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return PixelFormat::I8;
	}

	return format;
}

Texture::PixelFormat Texture::convertAI88ToFormat(const unsigned char* data, size_t dataLen, PixelFormat format, unsigned char** outData, size_t* outDataLen)
{
	switch (format)
	{
	case PixelFormat::RGBA8888:
		*outDataLen = dataLen*2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGBA8888(data, dataLen, *outData);
		break;
	case PixelFormat::RGB888:
		*outDataLen = dataLen/2*3;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGB888(data, dataLen, *outData);
		break;
	case PixelFormat::RGB565:
		*outDataLen = dataLen;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGB565(data, dataLen, *outData);
		break;
	case PixelFormat::A8:
		*outDataLen = dataLen/2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToA8(data, dataLen, *outData);
		break;
	case PixelFormat::I8:
		*outDataLen = dataLen/2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToI8(data, dataLen, *outData);
		break;
	case PixelFormat::RGBA4444:
		*outDataLen = dataLen;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGBA4444(data, dataLen, *outData);
		break;
	case PixelFormat::RGB5A1:
		*outDataLen = dataLen;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGB5A1(data, dataLen, *outData);
		break;
	default:
		if (format != PixelFormat::AUTO && format != PixelFormat::AI88)
		{
			LOG("Can not convert image format PixelFormat::AI88 to format ID:%d, we will use it's origin format PixelFormat::AI88", format);
		}

		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return PixelFormat::AI88;
		break;
	}

	return format;
}

Texture::PixelFormat Texture::convertRGB888ToFormat(const unsigned char* data, size_t dataLen, PixelFormat format, unsigned char** outData, size_t* outDataLen)
{
	switch (format)
	{
	case PixelFormat::RGBA8888:
		*outDataLen = dataLen/3*4;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToRGBA8888(data, dataLen, *outData);
		break;
	case PixelFormat::RGB565:
		*outDataLen = dataLen/3*2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToRGB565(data, dataLen, *outData);
		break;
	case PixelFormat::I8:
		*outDataLen = dataLen/3;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToI8(data, dataLen, *outData);
		break;
	case PixelFormat::AI88:
		*outDataLen = dataLen/3*2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToAI88(data, dataLen, *outData);
		break;
	case PixelFormat::RGBA4444:
		*outDataLen = dataLen/3*2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToRGBA4444(data, dataLen, *outData);
		break;
	case PixelFormat::RGB5A1:
		*outDataLen = dataLen;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToRGB5A1(data, dataLen, *outData);
		break;
	default:
		if (format != PixelFormat::AUTO && format != PixelFormat::RGB888)
		{
			LOG("Can not convert image format PixelFormat::RGB888 to format ID:%d, we will use it's origin format PixelFormat::RGB888", format);
		}

		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return PixelFormat::RGB888;
	}
	return format;
}

Texture::PixelFormat Texture::convertRGBA8888ToFormat(const unsigned char* data, size_t dataLen, PixelFormat format, unsigned char** outData, size_t* outDataLen)
{

	switch (format)
	{
	case PixelFormat::RGB888:
		*outDataLen = dataLen/4*3;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToRGB888(data, dataLen, *outData);
		break;
	case PixelFormat::RGB565:
		*outDataLen = dataLen/2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToRGB565(data, dataLen, *outData);
		break;
	case PixelFormat::A8:
		*outDataLen = dataLen/4;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToA8(data, dataLen, *outData);
		break;
	case PixelFormat::I8:
		*outDataLen = dataLen/4;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToI8(data, dataLen, *outData);
		break;
	case PixelFormat::AI88:
		*outDataLen = dataLen/2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToAI88(data, dataLen, *outData);
		break;
	case PixelFormat::RGBA4444:
		*outDataLen = dataLen/2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToRGBA4444(data, dataLen, *outData);
		break;
	case PixelFormat::RGB5A1:
		*outDataLen = dataLen/2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToRGB5A1(data, dataLen, *outData);
		break;
	default:
		if (format != PixelFormat::AUTO && format != PixelFormat::RGBA8888)
		{
			LOG("Can not convert image format PixelFormat::RGBA8888 to format ID:%d, we will use it's origin format PixelFormat::RGBA8888", format);
		}

		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return PixelFormat::RGBA8888;
	}

	return format;
}

void Texture::convertI8ToRGB888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i=0; i < dataLen; ++i)
	{
		*outData++ = data[i];     //R
		*outData++ = data[i];     //G
		*outData++ = data[i];     //B
	}
}

void Texture::convertAI88ToRGB888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*outData++ = data[i];     //R
		*outData++ = data[i];     //G
		*outData++ = data[i];     //B
	}
}

void Texture::convertI8ToRGBA8888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0; i < dataLen; ++i)
	{
		*outData++ = data[i];     //R
		*outData++ = data[i];     //G
		*outData++ = data[i];     //B
		*outData++ = 0xFF;        //A
	}
}

void Texture::convertAI88ToRGBA8888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*outData++ = data[i];     //R
		*outData++ = data[i];     //G
		*outData++ = data[i];     //B
		*outData++ = data[i + 1]; //A
	}
}

void Texture::convertI8ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0; i < dataLen; ++i)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i] & 0x00FC) << 3         //G
			| (data[i] & 0x00F8) >> 3;        //B
	}
}

void Texture::convertAI88ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i] & 0x00FC) << 3         //G
			| (data[i] & 0x00F8) >> 3;        //B
	}
}

void Texture::convertI8ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0; i < dataLen; ++i)
	{
		*out16++ = (data[i] & 0x00F0) << 8    //R
			| (data[i] & 0x00F0) << 4             //G
			| (data[i] & 0x00F0)                  //B
			| 0x000F;                             //A
	}
}

void Texture::convertAI88ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*out16++ = (data[i] & 0x00F0) << 8    //R
			| (data[i] & 0x00F0) << 4             //G
			| (data[i] & 0x00F0)                  //B
			| (data[i+1] & 0x00F0) >> 4;          //A
	}
}

void Texture::convertI8ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0; i < dataLen; ++i)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i] & 0x00F8) << 3         //G
			| (data[i] & 0x00F8) >> 2         //B
			| 0x0001;                         //A
	}
}

void Texture::convertAI88ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i] & 0x00F8) << 3         //G
			| (data[i] & 0x00F8) >> 2         //B
			| (data[i + 1] & 0x0080) >> 7;    //A
	}
}

void Texture::convertI8ToAI88(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0; i < dataLen; ++i)
	{
		*out16++ = 0xFF00     //A
			| data[i];            //I
	}
}

void Texture::convertAI88ToA8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 1; i < dataLen; i += 2)
	{
		*outData++ = data[i]; //A
	}
}

void Texture::convertAI88ToI8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*outData++ = data[i]; //R
	}
}

void Texture::convertRGB888ToRGBA8888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*outData++ = data[i];         //R
		*outData++ = data[i + 1];     //G
		*outData++ = data[i + 2];     //B
		*outData++ = 0xFF;            //A
	}
}

void Texture::convertRGBA8888ToRGB888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*outData++ = data[i];         //R
		*outData++ = data[i + 1];     //G
		*outData++ = data[i + 2];     //B
	}
}

void Texture::convertRGB888ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i + 1] & 0x00FC) << 3     //G
			| (data[i + 2] & 0x00F8) >> 3;    //B
	}
}

void Texture::convertRGBA8888ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i + 1] & 0x00FC) << 3     //G
			| (data[i + 2] & 0x00F8) >> 3;    //B
	}
}

void Texture::convertRGB888ToI8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
	}
}

void Texture::convertRGBA8888ToI8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
	}
}

void Texture::convertRGBA8888ToA8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen -3; i < l; i += 4)
	{
		*outData++ = data[i + 3]; //A
	}
}

void Texture::convertRGB888ToAI88(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
		*outData++ = 0xFF;
	}
}

void Texture::convertRGBA8888ToAI88(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
		*outData++ = data[i + 3];
	}
}

void Texture::convertRGB888ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*out16++ = ((data[i] & 0x00F0) << 8           //R
			| (data[i + 1] & 0x00F0) << 4     //G
			| (data[i + 2] & 0xF0)            //B
			|  0x0F);                         //A
	}
}

void Texture::convertRGBA8888ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*out16++ = (data[i] & 0x00F0) << 8    //R
			| (data[i + 1] & 0x00F0) << 4         //G
			| (data[i + 2] & 0xF0)                //B
			|  (data[i + 3] & 0xF0) >> 4;         //A
	}
}

void Texture::convertRGB888ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i + 1] & 0x00F8) << 3     //G
			| (data[i + 2] & 0x00F8) >> 2     //B
			|  0x01;                          //A
	}
}

void Texture::convertRGBA8888ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 2; i < l; i += 4)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i + 1] & 0x00F8) << 3     //G
			| (data[i + 2] & 0x00F8) >> 2     //B
			|  (data[i + 3] & 0x0080) >> 7;   //A
	}
}

Texture::Texture( Resource resource ):ResourceHandle(resource, ResourceHandle::Type::TEXTURE),
	_pixelFormat(Texture::PixelFormat::DEFAULT),
	_textureId(0),
	_hasPremultipliedAlpha(false)
{

}

Texture::~Texture()
{
	releaseTexture();
}

void Texture::releaseTexture()
{
	glDeleteTextures(1, &_textureId);
	_textureId = 0;
}

bool Texture::initImage( Image *image )
{
	return initImage(image, _defaultAlphaPixelFormat);
}

bool Texture::initImage( Image * image, PixelFormat format )
{
	if (image == nullptr)
	{
		LOG("SiT: Texture2D. Can't create Texture. UIImage is nil");
		return false;
	}

	int imageWidth = image->getWidth();
	int imageHeight = image->getHeight();

	unsigned char*   tempData = image->getData();
	PixelFormat      pixelFormat = ((PixelFormat::NONE == format) || (PixelFormat::AUTO == format)) ? image->getRenderFormat() : format;
	PixelFormat      renderFormat = image->getRenderFormat();
	size_t	         tempDataLen = image->getDataLen();

	unsigned char* outTempData = nullptr;
	size_t outTempDataLen = 0;

	pixelFormat = convertDataToFormat(tempData, tempDataLen, renderFormat, pixelFormat, &outTempData, &outTempDataLen);

	initData(outTempData, outTempDataLen, pixelFormat, imageWidth, imageHeight);


	if (outTempData != nullptr && outTempData != tempData)
	{

		free(outTempData);
	}

	_hasPremultipliedAlpha = image->hasPremultipliedAlpha();

	_width = imageWidth;
	_height = imageHeight;

	return true;
}

bool Texture::initData( const void *data, size_t dataLen, Texture::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh)
{
	if(pixelFormat == PixelFormat::NONE || pixelFormat == PixelFormat::AUTO)
	{
		LOG("the \"pixelFormat\" param must be a certain value!");
		return false;
	}
	if(dataLen<=0 || pixelsWide<=0 || pixelsHigh<=0)
	{
		LOG("Invalid size");
		return false;
	}

	if(_pixelFormatInfoTables.find(pixelFormat) == _pixelFormatInfoTables.end())
	{
		LOG("SiT: WARNING: unsupported pixelformat: %lx", (unsigned long)pixelFormat );
		return false;
	}

	const PixelFormatInfo& info = _pixelFormatInfoTables.at(pixelFormat);

	unsigned int bytesPerRow = pixelsWide * info._bpp / 8;

	if(bytesPerRow % 8 == 0)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
	}
	else if(bytesPerRow % 4 == 0)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	}
	else if(bytesPerRow % 2 == 0)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
	}
	else
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}

	if(_textureId != 0)
	{
		releaseTexture();
	}

	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	GLenum __error = glGetError();
	if(__error) {
		LOG("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, info._internalFormat, (GLsizei)pixelsWide, (GLsizei)pixelsHigh, 0, info._format, info._type, data);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		LOG("SiT: Texture: glError: 0x%04X", err);
		return false;
	}


	return true;
}

bool Texture::updateData( const void *data,int offsetX,int offsetY,int width,int height )
{
	if (_textureId)
	{
		glBindTexture(GL_TEXTURE_2D, _textureId);
		const PixelFormatInfo& info = _pixelFormatInfoTables.at(_pixelFormat);
		glTexSubImage2D(GL_TEXTURE_2D,0,offsetX,offsetY,width,height,info._format, info._type,data);

		return true;
	}
	return false;
}

GLuint* Texture::getTextureId()
{
	return &_textureId;
}

unsigned int Texture::getWidth()
{
	return _width;
}

unsigned int Texture::getHeight()
{
	return _height;
}

void Texture::setWidth( unsigned int width )
{
	_width = width;
}

void Texture::setHeight( unsigned int height )
{
	_height = height;
}

bool Texture::getPremultipliedAlpha()
{
	return _hasPremultipliedAlpha;
}

Texture::PixelFormat Texture::getPixelFormat() const
{
	return _pixelFormat;
}

NS_SIT_END