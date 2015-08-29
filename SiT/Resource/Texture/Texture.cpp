#include "Texture.h"

NS_SIT_BEGIN

Texture::Texture( Resource resource ):ResourceHandle(resource, ResourceHandle::Type::TEXTURE),
_pixelFormat(Image::PixelFormat::DEFAULT),_hasPremultipliedAlpha(false)
{
}

Texture::~Texture()
{
	releaseTexture();
}

void Texture::releaseTexture()
{
}

void Texture::texSubImage(Point point, Size size, Image::PixelFormat pixelFormat, const void *data)
{
}

void Texture::texImage(Size size, Image::PixelFormat pixelFormat, const void *data)
{

}

bool Texture::init()
{
	return false;
}

bool Texture::initEmpty(unsigned int width, unsigned int height)
{
	return false;
}

bool Texture::initImage(Image *image)
{
	return initImage(image, Image::PixelFormat::DEFAULT);
}

bool Texture::initImage(Image * image, Image::PixelFormat format)
{
	if (image == nullptr)
	{
		LOG("SiT: Texture2D. Can't create Texture. UIImage is nil");
		return false;
	}

	unsigned int imageWidth = image->getWidth();
	unsigned int imageHeight = image->getHeight();

	unsigned char*   tempData = image->getData();
	Image::PixelFormat pixelFormat = ((Image::PixelFormat::NONE == format) || (Image::PixelFormat::AUTO == format)) ? image->getRenderFormat() : format;
	Image::PixelFormat renderFormat = image->getRenderFormat();
	size_t	         tempDataLen = image->getDataLen();

	unsigned char* outTempData = nullptr;
	size_t outTempDataLen = 0;

	pixelFormat = ImageDataConverter::convertDataToFormat(tempData, tempDataLen, renderFormat, pixelFormat, &outTempData, &outTempDataLen);

	if (!initData(outTempData, outTempDataLen, pixelFormat, imageWidth, imageHeight))return false;


	if (outTempData != nullptr && outTempData != tempData)
	{

		free(outTempData);
	}

	_hasPremultipliedAlpha = image->hasPremultipliedAlpha();

	_size.setWidth(imageWidth);
	_size.setHeight(imageHeight);

	return true;
}

bool Texture::initData(const void *data, size_t dataLen, Image::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh)
{
	return false;
}

NS_SIT_END