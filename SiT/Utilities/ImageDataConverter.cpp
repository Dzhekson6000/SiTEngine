#include "ImageDataConverter.h"

NS_SIT_BEGIN

Image::PixelFormat ImageDataConverter::convertDataToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat originFormat, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen)
{
	if (format == originFormat || format == Image::PixelFormat::AUTO)
	{
		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return originFormat;
	}

	switch (originFormat)
	{
	case Image::PixelFormat::I8:
		return convertI8ToFormat(data, dataLen, format, outData, outDataLen);
	case Image::PixelFormat::AI88:
		return convertAI88ToFormat(data, dataLen, format, outData, outDataLen);
	case Image::PixelFormat::RGB888:
		return convertRGB888ToFormat(data, dataLen, format, outData, outDataLen);
	case Image::PixelFormat::RGBA8888:
		return convertRGBA8888ToFormat(data, dataLen, format, outData, outDataLen);
	default:
		LOG("unsupport convert for format %d to format %d", originFormat, format);
		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return originFormat;
	}
}

Image::PixelFormat ImageDataConverter::convertI8ToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen)
{
	switch (format)
	{
	case Image::PixelFormat::RGBA8888:
		*outDataLen = dataLen * 4;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGBA8888(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB888:
		*outDataLen = dataLen * 3;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGB888(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB565:
		*outDataLen = dataLen * 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGB565(data, dataLen, *outData);
		break;
	case Image::PixelFormat::AI88:
		*outDataLen = dataLen * 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToAI88(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGBA4444:
		*outDataLen = dataLen * 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGBA4444(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB5A1:
		*outDataLen = dataLen * 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertI8ToRGB5A1(data, dataLen, *outData);
		break;
	default:
		if (format != Image::PixelFormat::AUTO && format != Image::PixelFormat::I8)
		{
			LOG("Can not convert image format PixelFormat::I8 to format ID:%d, we will use it's origin format PixelFormat::I8", format);
		}

		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return Image::PixelFormat::I8;
	}

	return format;
}

Image::PixelFormat ImageDataConverter::convertAI88ToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen)
{
	switch (format)
	{
	case Image::PixelFormat::RGBA8888:
		*outDataLen = dataLen * 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGBA8888(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB888:
		*outDataLen = dataLen / 2 * 3;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGB888(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB565:
		*outDataLen = dataLen;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGB565(data, dataLen, *outData);
		break;
	case Image::PixelFormat::A8:
		*outDataLen = dataLen / 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToA8(data, dataLen, *outData);
		break;
	case Image::PixelFormat::I8:
		*outDataLen = dataLen / 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToI8(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGBA4444:
		*outDataLen = dataLen;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGBA4444(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB5A1:
		*outDataLen = dataLen;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertAI88ToRGB5A1(data, dataLen, *outData);
		break;
	default:
		if (format != Image::PixelFormat::AUTO && format != Image::PixelFormat::AI88)
		{
			LOG("Can not convert image format PixelFormat::AI88 to format ID:%d, we will use it's origin format PixelFormat::AI88", format);
		}

		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return Image::PixelFormat::AI88;
		break;
	}

	return format;
}

Image::PixelFormat ImageDataConverter::convertRGB888ToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen)
{
	switch (format)
	{
	case Image::PixelFormat::RGBA8888:
		*outDataLen = dataLen / 3 * 4;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToRGBA8888(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB565:
		*outDataLen = dataLen / 3 * 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToRGB565(data, dataLen, *outData);
		break;
	case Image::PixelFormat::I8:
		*outDataLen = dataLen / 3;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToI8(data, dataLen, *outData);
		break;
	case Image::PixelFormat::AI88:
		*outDataLen = dataLen / 3 * 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToAI88(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGBA4444:
		*outDataLen = dataLen / 3 * 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToRGBA4444(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB5A1:
		*outDataLen = dataLen;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGB888ToRGB5A1(data, dataLen, *outData);
		break;
	default:
		if (format != Image::PixelFormat::AUTO && format != Image::PixelFormat::RGB888)
		{
			LOG("Can not convert image format PixelFormat::RGB888 to format ID:%d, we will use it's origin format PixelFormat::RGB888", format);
		}

		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return Image::PixelFormat::RGB888;
	}
	return format;
}

Image::PixelFormat ImageDataConverter::convertRGBA8888ToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen)
{

	switch (format)
	{
	case Image::PixelFormat::RGB888:
		*outDataLen = dataLen / 4 * 3;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToRGB888(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB565:
		*outDataLen = dataLen / 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToRGB565(data, dataLen, *outData);
		break;
	case Image::PixelFormat::A8:
		*outDataLen = dataLen / 4;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToA8(data, dataLen, *outData);
		break;
	case Image::PixelFormat::I8:
		*outDataLen = dataLen / 4;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToI8(data, dataLen, *outData);
		break;
	case Image::PixelFormat::AI88:
		*outDataLen = dataLen / 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToAI88(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGBA4444:
		*outDataLen = dataLen / 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToRGBA4444(data, dataLen, *outData);
		break;
	case Image::PixelFormat::RGB5A1:
		*outDataLen = dataLen / 2;
		*outData = (unsigned char*)malloc(sizeof(unsigned char) * (*outDataLen));
		convertRGBA8888ToRGB5A1(data, dataLen, *outData);
		break;
	default:
		if (format != Image::PixelFormat::AUTO && format != Image::PixelFormat::RGBA8888)
		{
			LOG("Can not convert image format PixelFormat::RGBA8888 to format ID:%d, we will use it's origin format PixelFormat::RGBA8888", format);
		}

		*outData = (unsigned char*)data;
		*outDataLen = dataLen;
		return Image::PixelFormat::RGBA8888;
	}

	return format;
}

void ImageDataConverter::convertI8ToRGB888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0; i < dataLen; ++i)
	{
		*outData++ = data[i];     //R
		*outData++ = data[i];     //G
		*outData++ = data[i];     //B
	}
}

void ImageDataConverter::convertAI88ToRGB888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*outData++ = data[i];     //R
		*outData++ = data[i];     //G
		*outData++ = data[i];     //B
	}
}

void ImageDataConverter::convertI8ToRGBA8888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0; i < dataLen; ++i)
	{
		*outData++ = data[i];     //R
		*outData++ = data[i];     //G
		*outData++ = data[i];     //B
		*outData++ = 0xFF;        //A
	}
}

void ImageDataConverter::convertAI88ToRGBA8888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*outData++ = data[i];     //R
		*outData++ = data[i];     //G
		*outData++ = data[i];     //B
		*outData++ = data[i + 1]; //A
	}
}

void ImageDataConverter::convertI8ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0; i < dataLen; ++i)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i] & 0x00FC) << 3         //G
			| (data[i] & 0x00F8) >> 3;        //B
	}
}

void ImageDataConverter::convertAI88ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i] & 0x00FC) << 3         //G
			| (data[i] & 0x00F8) >> 3;        //B
	}
}

void ImageDataConverter::convertI8ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData)
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

void ImageDataConverter::convertAI88ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*out16++ = (data[i] & 0x00F0) << 8    //R
			| (data[i] & 0x00F0) << 4             //G
			| (data[i] & 0x00F0)                  //B
			| (data[i + 1] & 0x00F0) >> 4;          //A
	}
}

void ImageDataConverter::convertI8ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData)
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

void ImageDataConverter::convertAI88ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData)
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

void ImageDataConverter::convertI8ToAI88(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0; i < dataLen; ++i)
	{
		*out16++ = 0xFF00     //A
			| data[i];            //I
	}
}

void ImageDataConverter::convertAI88ToA8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 1; i < dataLen; i += 2)
	{
		*outData++ = data[i]; //A
	}
}

void ImageDataConverter::convertAI88ToI8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 1; i < l; i += 2)
	{
		*outData++ = data[i]; //R
	}
}

void ImageDataConverter::convertRGB888ToRGBA8888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*outData++ = data[i];         //R
		*outData++ = data[i + 1];     //G
		*outData++ = data[i + 2];     //B
		*outData++ = 0xFF;            //A
	}
}

void ImageDataConverter::convertRGBA8888ToRGB888(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*outData++ = data[i];         //R
		*outData++ = data[i + 1];     //G
		*outData++ = data[i + 2];     //B
	}
}

void ImageDataConverter::convertRGB888ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i + 1] & 0x00FC) << 3     //G
			| (data[i + 2] & 0x00F8) >> 3;    //B
	}
}

void ImageDataConverter::convertRGBA8888ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i + 1] & 0x00FC) << 3     //G
			| (data[i + 2] & 0x00F8) >> 3;    //B
	}
}

void ImageDataConverter::convertRGB888ToI8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
	}
}

void ImageDataConverter::convertRGBA8888ToI8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
	}
}

void ImageDataConverter::convertRGBA8888ToA8(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*outData++ = data[i + 3]; //A
	}
}

void ImageDataConverter::convertRGB888ToAI88(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
		*outData++ = 0xFF;
	}
}

void ImageDataConverter::convertRGBA8888ToAI88(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*outData++ = (data[i] * 299 + data[i + 1] * 587 + data[i + 2] * 114 + 500) / 1000;  //I =  (R*299 + G*587 + B*114 + 500) / 1000
		*outData++ = data[i + 3];
	}
}

void ImageDataConverter::convertRGB888ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*out16++ = ((data[i] & 0x00F0) << 8           //R
			| (data[i + 1] & 0x00F0) << 4     //G
			| (data[i + 2] & 0xF0)            //B
			| 0x0F);                         //A
	}
}

void ImageDataConverter::convertRGBA8888ToRGBA4444(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 3; i < l; i += 4)
	{
		*out16++ = (data[i] & 0x00F0) << 8    //R
			| (data[i + 1] & 0x00F0) << 4         //G
			| (data[i + 2] & 0xF0)                //B
			| (data[i + 3] & 0xF0) >> 4;         //A
	}
}

void ImageDataConverter::convertRGB888ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 2; i < l; i += 3)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i + 1] & 0x00F8) << 3     //G
			| (data[i + 2] & 0x00F8) >> 2     //B
			| 0x01;                          //A
	}
}

void ImageDataConverter::convertRGBA8888ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData)
{
	unsigned short* out16 = (unsigned short*)outData;
	for (size_t i = 0, l = dataLen - 2; i < l; i += 4)
	{
		*out16++ = (data[i] & 0x00F8) << 8    //R
			| (data[i + 1] & 0x00F8) << 3     //G
			| (data[i + 2] & 0x00F8) >> 2     //B
			| (data[i + 3] & 0x0080) >> 7;   //A
	}
}

NS_SIT_END