#ifndef OPENGL_TEXTURE_H_
#define OPENGL_TEXTURE_H_

#include "Libs/GraphicsLib.h"
#include "Resource/Texture/Texture.h"


NS_SIT_BEGIN

class SIT_DLL OpenGLTexture : public Texture
{
private:
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

	typedef std::map<Image::PixelFormat, const PixelFormatInfo> PixelFormatInfoMap;
	static const PixelFormatInfoMap								_pixelFormatInfoTables;
	typedef PixelFormatInfoMap::value_type						PixelFormatInfoMapValue;
	static const PixelFormatInfoMapValue						TexturePixelFormatInfoTablesValue[];

	SYNTHESIZE_READONLY(GLuint, _textureId, TextureId);

	void	pixelStoreiFromPixelFormat(unsigned int pixelsWide, Image::PixelFormat pixelFormat);

public:
					OpenGLTexture(Resource resource);
	void			releaseTexture();
	void			texImage(Size size, Image::PixelFormat pixelFormat, const void *data);
	void			texSubImage(Point point, Size size, Image::PixelFormat pixelFormat, const void *data);

	bool			init();
	bool			initEmpty(unsigned int width, unsigned int height);
	bool			initData(const void *data, size_t dataLen, Image::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh);
};

NS_SIT_END

#endif  // OPENGL_TEXTURE_H_