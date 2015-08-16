#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "ResourceHandle.h"
#include <map>
#include "Geometry/Geometry.h"
#include "Utilities/ImageDataConverter.h"

NS_SIT_BEGIN
class Image;
class SIT_DLL Texture: public ResourceHandle
{
private:

protected:
	SYNTHESIZE_READONLY(Image::PixelFormat, _pixelFormat, PixelFormat);
	SYNTHESIZE_READONLY(bool, _hasPremultipliedAlpha, PremultipliedAlpha);
	SYNTHESIZE_READONLY(Size, _size, Size)
public:
	Texture(Resource resource);
	virtual				~Texture();
	virtual void		releaseTexture();

	bool initImage(Image *image);
	bool initImage(Image *image, Image::PixelFormat format);
	virtual bool initData(const void *data, size_t dataLen, Image::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh);
};

NS_SIT_END

#endif // TEXTURE_H_