#include "Image.h"

NS_SIT_BEGIN

Image::Image(): _data(nullptr)
, _dataLen(0)
, _width(0)
, _height(0)
, _fileType(Format::UNKOWN)
{
}

Image::~Image()
{
	if(_data)
	{
		free(_data);
		_data = nullptr;
	}
}

bool Image::initImageFile( const std::string& path )
{
	bool ret = false;
	Data data = FileUtils::getInstance()->getDataFromFile(path.c_str());
	if (!data.isNull())
	{
		ret = initImageData(data.getBytes(), data.getSize());
	}
	return ret;
}

bool Image::initImageData( const unsigned char * data, size_t dataLen )
{
	bool ret = false;

	do
	{
		if(! data || dataLen <= 0)break;

		_fileType = detectFormat(data, dataLen);

		switch (_fileType)
		{
		case Format::PNG:
			ret = initPngData(data, dataLen);
			break;
		case Format::JPG:
			ret = initJpgData(data, dataLen);
			break;
		default:
			break;
		}
	} while (0);

	return ret;
}

struct MyErrorMgr
{
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
};

typedef struct MyErrorMgr * MyErrorPtr;
METHODDEF(void)
	myErrorExit(j_common_ptr cinfo)
{
	MyErrorPtr myerr = (MyErrorPtr) cinfo->err;
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message) (cinfo, buffer);
	LOG("jpeg error: %s", buffer);
	longjmp(myerr->setjmp_buffer, 1);
}

bool Image::initJpgData( const unsigned char * data, size_t dataLen )
{
	struct jpeg_decompress_struct cinfo;
	struct MyErrorMgr jerr;

	JSAMPROW row_pointer[1] = {0};
	unsigned long location = 0;

	bool ret = false;
	do 
    {
		cinfo.err = jpeg_std_error(&jerr.pub);
		jerr.pub.error_exit = myErrorExit;
		if (setjmp(jerr.setjmp_buffer))
        {
			jpeg_destroy_decompress(&cinfo);
			break;
		}

        jpeg_create_decompress( &cinfo );

#if (JPEG_LIB_VERSION >= 90)
        jpeg_read_header(&cinfo, TRUE);
#else
        jpeg_read_header(&cinfo, TRUE);
#endif

		if (cinfo.jpeg_color_space == JCS_GRAYSCALE)
		{
			_renderFormat = Texture::PixelFormat::I8;
		}else
		{
			cinfo.out_color_space = JCS_RGB;
			_renderFormat = Texture::PixelFormat::RGB888;
		}

        jpeg_start_decompress( &cinfo );

        _width  = cinfo.output_width;
        _height = cinfo.output_height;

        _dataLen = cinfo.output_width*cinfo.output_height*cinfo.output_components;
        _data = static_cast<unsigned char*>(malloc(_dataLen * sizeof(unsigned char)));
        if(!_data)break;

        while (cinfo.output_scanline < cinfo.output_height)
        {
            row_pointer[0] = _data + location;
            location += cinfo.output_width*cinfo.output_components;
            jpeg_read_scanlines(&cinfo, row_pointer, 1);
        }
		jpeg_destroy_decompress( &cinfo );
        ret = true;
    } while (0);
    return ret;
}


namespace
{
	typedef struct 
	{
		const unsigned char * data;
		size_t size;
		int offset;
	}tImageSource;

	static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
	{
		tImageSource* isource = (tImageSource*)png_get_io_ptr(png_ptr);

		if((int)(isource->offset + length) <= isource->size)
		{
			memcpy(data, isource->data+isource->offset, length);
			isource->offset += length;
		}
		else
		{
			png_error(png_ptr, "pngReaderCallback failed");
		}
	}
}


bool Image::initPngData( const unsigned char * data, size_t dataLen )
{
#define PNGSIGSIZE  8
	bool ret = false;
	png_byte        header[PNGSIGSIZE]   = {0}; 
	png_structp     png_ptr     =   0;
	png_infop       info_ptr    = 0;

	do 
	{
		if(dataLen < PNGSIGSIZE)break;

		memcpy(header, data, PNGSIGSIZE);
		if(png_sig_cmp(header, 0, PNGSIGSIZE))break;

		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
		if(! png_ptr)break;

		info_ptr = png_create_info_struct(png_ptr);
		if(!info_ptr)break;

		if(setjmp(png_jmpbuf(png_ptr)))break;

		tImageSource imageSource;
		imageSource.data    = (unsigned char*)data;
		imageSource.size    = dataLen;
		imageSource.offset  = 0;
		png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

		png_read_info(png_ptr, info_ptr);

		_width = png_get_image_width(png_ptr, info_ptr);
		_height = png_get_image_height(png_ptr, info_ptr);
		png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

		if (color_type == PNG_COLOR_TYPE_PALETTE)
		{
			png_set_palette_to_rgb(png_ptr);
		}
		
		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		{
			bit_depth = 8;
			png_set_expand_gray_1_2_4_to_8(png_ptr);
		}

		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			png_set_tRNS_to_alpha(png_ptr);
		}  

		if (bit_depth == 16)
		{
			png_set_strip_16(png_ptr);            
		} 

		if (bit_depth < 8)
		{
			png_set_packing(png_ptr);
		}

		png_read_update_info(png_ptr, info_ptr);
		bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		color_type = png_get_color_type(png_ptr, info_ptr);

		switch (color_type)
		{
		case PNG_COLOR_TYPE_GRAY:
			_renderFormat = Texture::PixelFormat::I8;
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			_renderFormat = Texture::PixelFormat::AI88;
			break;
		case PNG_COLOR_TYPE_RGB:
			_renderFormat = Texture::PixelFormat::RGB888;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			_renderFormat = Texture::PixelFormat::RGBA8888;
			break;
		default:
			break;
		}

		png_size_t rowbytes;
		png_bytep* row_pointers = (png_bytep*)malloc( sizeof(png_bytep) * _height );

		rowbytes = png_get_rowbytes(png_ptr, info_ptr);

		_dataLen = rowbytes * _height;
		_data = static_cast<unsigned char*>(malloc(_dataLen * sizeof(unsigned char)));
		if (!_data)
		{
			if (row_pointers != nullptr)
			{
				free(row_pointers);
			}
			break;
		}

		for (unsigned short i = 0; i < _height; ++i)
		{
			row_pointers[i] = _data + i*rowbytes;
		}
		png_read_image(png_ptr, row_pointers);

		png_read_end(png_ptr, nullptr);

		if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		{
			premultipliedAlpha();
		}
		else
		{
			_hasPremultipliedAlpha = false;
		}


		if (row_pointers != nullptr)
		{
			free(row_pointers);
		}

		ret = true;
	} while (0);

	if (png_ptr)
	{
		png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
	}
	return ret;
}

Image::Format Image::detectFormat( const unsigned char * data, size_t dataLen )
{
	if (isPng(data, dataLen))
	{
		return Format::PNG;
	}
	else if (isJpg(data, dataLen))
	{
		return Format::JPG;
	}else
	{
		return Format::UNKOWN;
	}
}

bool Image::isPng( const unsigned char * data, size_t dataLen )
{
	if (dataLen <= 8)
	{
		return false;
	}
	static const unsigned char PNG_SIGNATURE[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};
	return memcmp(PNG_SIGNATURE, data, sizeof(PNG_SIGNATURE)) == 0;
}

bool Image::isJpg( const unsigned char * data, size_t dataLen )
{
	if (dataLen <= 4)
	{
		return false;
	}
	static const unsigned char JPG_SOI[] = {0xFF, 0xD8};
	return memcmp(data, JPG_SOI, 2) == 0;
}

void Image::premultipliedAlpha()
{
	if(_renderFormat != Texture::PixelFormat::RGBA8888)
	{
		LOG("The pixel format should be RGBA8888!");
	};

	unsigned int* fourBytes = (unsigned int*)_data;
	for(int i = 0; i < _width * _height; i++)
	{
		unsigned char* p = _data + i * 4;
		fourBytes[i] = RGB_PREMULTIPLY_ALPHA(p[0], p[1], p[2], p[3]);
	}

	_hasPremultipliedAlpha = true;
}

NS_SIT_END