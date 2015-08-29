#include "OpenGLTexture.h"

NS_SIT_BEGIN

const OpenGLTexture::PixelFormatInfoMapValue OpenGLTexture::TexturePixelFormatInfoTablesValue[] =
{
	PixelFormatInfoMapValue(Image::PixelFormat::BGRA8888, OpenGLTexture::PixelFormatInfo(GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE, 32, false, true)),
	PixelFormatInfoMapValue(Image::PixelFormat::RGBA8888, OpenGLTexture::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 32, false, true)),
	PixelFormatInfoMapValue(Image::PixelFormat::RGBA4444, OpenGLTexture::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 16, false, true)),
	PixelFormatInfoMapValue(Image::PixelFormat::RGB5A1, OpenGLTexture::PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 16, false, true)),
	PixelFormatInfoMapValue(Image::PixelFormat::RGB565, OpenGLTexture::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 16, false, false)),
	PixelFormatInfoMapValue(Image::PixelFormat::RGB888, OpenGLTexture::PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 24, false, false)),
	PixelFormatInfoMapValue(Image::PixelFormat::A8, OpenGLTexture::PixelFormatInfo(GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 8, false, false)),
	PixelFormatInfoMapValue(Image::PixelFormat::I8, OpenGLTexture::PixelFormatInfo(GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE, 8, false, false)),
	PixelFormatInfoMapValue(Image::PixelFormat::AI88, OpenGLTexture::PixelFormatInfo(GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 16, false, true)),
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
	PixelFormatInfoMapValue(Image::PixelFormat::S3TC_DXT1, OpenGLTexture::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)),
#endif

#ifdef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
	PixelFormatInfoMapValue(Image::PixelFormat::S3TC_DXT3, OpenGLTexture::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif

#ifdef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
	PixelFormatInfoMapValue(Image::PixelFormat::S3TC_DXT5, OpenGLTexture::PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)),
#endif
};

const OpenGLTexture::PixelFormatInfoMap OpenGLTexture::_pixelFormatInfoTables(TexturePixelFormatInfoTablesValue,
	TexturePixelFormatInfoTablesValue + sizeof(TexturePixelFormatInfoTablesValue) / sizeof(TexturePixelFormatInfoTablesValue[0]));

bool OpenGLTexture::init()
{
	glGenTextures(1, &_textureId);
	return true;
}

bool OpenGLTexture::initEmpty(unsigned int width, unsigned int height)
{
	if(!init()) return false;

	glBindTexture(GL_TEXTURE_2D, _textureId);
	unsigned int* data = (unsigned int*)new GLuint[((width * height) * 4 * sizeof(unsigned int))];
	ZeroMemory(data, ((width * height) * 4 * sizeof(unsigned int)));

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
	delete[] data;

	_size.setWidth(width);
	_size.setHeight(height);
}

bool OpenGLTexture::initData(const void *data, size_t dataLen, Image::PixelFormat pixelFormat, int pixelsWide, int pixelsHigh)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		LOG("OpenGL error 0x%04X in %s %s %d\n", error, __FILE__, __FUNCTION__, __LINE__);
	}

	if (pixelFormat == Image::PixelFormat::NONE || pixelFormat == Image::PixelFormat::AUTO)
	{
		LOG("the \"pixelFormat\" param must be a certain value!");
		return false;
	}
	if (dataLen <= 0 || pixelsWide <= 0 || pixelsHigh <= 0)
	{
		LOG("Invalid size");
		return false;
	}

	if (_pixelFormatInfoTables.find(pixelFormat) == _pixelFormatInfoTables.end())
	{
		LOG("SiT: WARNING: unsupported pixelformat: %lx", (unsigned long)pixelFormat);
		return false;
	}

	const PixelFormatInfo& info = _pixelFormatInfoTables.at(pixelFormat);

	pixelStoreiFromPixelFormat(pixelsWide, pixelFormat);

	if (_textureId != 0)
	{
		releaseTexture();
	}

	if (!init()) return false;
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	error = glGetError();
	if (error != GL_NO_ERROR) {
		LOG("OpenGL error 0x%04X in %s %s %d\n", error, __FILE__, __FUNCTION__, __LINE__);
		return false;
	}

	texImage(Size(pixelsWide, pixelsHigh), pixelFormat, data);

	error = glGetError();
	if (error != GL_NO_ERROR) {
		LOG("OpenGL error 0x%04X in %s %s %d\n", error, __FILE__, __FUNCTION__, __LINE__);
		return false;
	}

	return true;
}

OpenGLTexture::OpenGLTexture(Resource resource):
Texture(resource),_textureId(0)
{
}

void OpenGLTexture::releaseTexture()
{
	glDeleteTextures(1, &_textureId);
	_textureId = 0;
}

void OpenGLTexture::pixelStoreiFromPixelFormat(unsigned int pixelsWide, Image::PixelFormat pixelFormat)
{
	if (_pixelFormatInfoTables.find(pixelFormat) == _pixelFormatInfoTables.end())
	{
		LOG("SiT: WARNING: unsupported pixelformat: %lx", (unsigned long)pixelFormat);
		return;
	}
	const PixelFormatInfo& info = _pixelFormatInfoTables.at(pixelFormat);

	unsigned int bytesPerRow = pixelsWide * info._bpp / 8;

	if (bytesPerRow % 8 == 0)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
	}
	else if (bytesPerRow % 4 == 0)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	}
	else if (bytesPerRow % 2 == 0)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
	}
	else
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}
}

void OpenGLTexture::texImage(Size size, Image::PixelFormat pixelFormat, const void *data)
{
	if (_pixelFormatInfoTables.find(pixelFormat) == _pixelFormatInfoTables.end())
	{
		LOG("SiT: WARNING: unsupported pixelformat: %lx", (unsigned long)pixelFormat);
		return;
	}
	const PixelFormatInfo& info = _pixelFormatInfoTables.at(pixelFormat);

	glTexImage2D(GL_TEXTURE_2D, 0, info._internalFormat, (GLsizei)size.getWidth(), (GLsizei)size.getHeight(), 0, info._format, info._type, data);
}

void OpenGLTexture::texSubImage(Point point, Size size, Image::PixelFormat pixelFormat, const void *data)
{
	if (_pixelFormatInfoTables.find(pixelFormat) == _pixelFormatInfoTables.end())
	{
		LOG("SiT: WARNING: unsupported pixelformat: %lx", (unsigned long)pixelFormat);
		return;
	}
	const PixelFormatInfo& info = _pixelFormatInfoTables.at(pixelFormat);
	pixelStoreiFromPixelFormat(size.getWidth(), pixelFormat);
	glTexSubImage2D(GL_TEXTURE_2D, 0, point.getX(), point.getY(), (GLsizei)size.getWidth(), (GLsizei)size.getHeight(), info._format, info._type, data);
}

NS_SIT_END