#ifndef IMAGE_DATA_CONVERTER_H_
#define IMAGE_DATA_CONVERTER_H_

#include "Macros.h"
#include "Resource/Image.h"

NS_SIT_BEGIN

class ImageDataConverter
{
private:
	static Image::PixelFormat convertI8ToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen);
	static Image::PixelFormat convertAI88ToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen);
	static Image::PixelFormat convertRGB888ToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen);
	static Image::PixelFormat convertRGBA8888ToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen);

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
public:
	static Image::PixelFormat convertDataToFormat(const unsigned char* data, size_t dataLen, Image::PixelFormat originFormat, Image::PixelFormat format, unsigned char** outData, size_t* outDataLen);

};

NS_SIT_END

#endif  // IMAGE_DATA_CONVERTER_H_