#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Resource/ResourceHandle.h"
#include <map>
#include "Types/Types.h"
#include "Utilities/ImageDataConverter.h"

NS_SIT_BEGIN

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
	virtual void		texSubImage(Point point, Size size, Image::PixelFormat pixelFormat, const void *data);
	virtual void		texImage(Size size, Image::PixelFormat pixelFormat, const void *data);

	virtual bool		init();
	virtual bool		initEmpty(unsigned int width, unsigned int height);
	bool				initImage(Image *image);
	bool				initImage(Image *image, Image::PixelFormat format);
	virtual bool		initData(const void *data, size_t dataLen, Image::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh);
};

NS_SIT_END

#endif // TEXTURE_H_