#include "ResourceHandle.h"

NS_SIT_BEGIN

ResourceHandle::ResourceHandle( Resource resource )
:_resource(resource), _width(0), _height(0)
{
}

GLuint* ResourceHandle::getTextureId()
{
	return &_textureId;
}
unsigned int ResourceHandle::getWidth()
{
	return _width;
}

unsigned int ResourceHandle::getHeight()
{
	return _height;
}

void ResourceHandle::setWidth( unsigned int width )
{
	_width = width;
}

void ResourceHandle::setHeight( unsigned int height )
{
	_height = height;
}

NS_SIT_END