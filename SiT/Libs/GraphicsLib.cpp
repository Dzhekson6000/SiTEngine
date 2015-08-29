#include "GraphicsLib.h"

#if (USE_GRAPHICS_LIB == LIB_GRAPHICS_OPENGL)
	#include "LibOpenGL/LibOpenGL.h"
#endif

NS_SIT_BEGIN

GraphicsLib* GraphicsLib::_graphicsLib = nullptr;

GraphicsLib* GraphicsLib::createLib()
{
#if (USE_GRAPHICS_LIB == LIB_GRAPHICS_OPENGL)
	return new LibOpenGL();
#endif
	return new GraphicsLib();
		
}

GraphicsLib* GraphicsLib::getInstance()
{
	if (!_graphicsLib)
	{
		_graphicsLib = createLib();

		if (!_graphicsLib->init())
		{
			delete _graphicsLib;
			_graphicsLib = nullptr;
		}
	}

	return _graphicsLib;
}

GraphicsLib::GraphicsLib()
{
}

bool GraphicsLib::init()
{
	return false;
}

void GraphicsLib::destroy()
{
}

void GraphicsLib::clearView(Color color)
{
}

Shader* GraphicsLib::createNewShader()
{
	return new Shader();
}

Texture* GraphicsLib::createNewTexture(Resource resource)
{
	return new Texture(resource);
}

void GraphicsLib::genBuffers(unsigned int n, unsigned int* buffers)
{

}

void GraphicsLib::deleteBuffers(unsigned int n, unsigned int* buffers)
{

}

void GraphicsLib::bindBuffer(TargetBuffer target, unsigned int buffer)
{
}

void GraphicsLib::bufferData(TargetBuffer target, ptrdiff_t size, const void* data, UsageStore usage)
{

}

void GraphicsLib::bindTexture(Texture* texture)
{
}

void GraphicsLib::activeTexture(unsigned int id)
{
}

void GraphicsLib::enableVertexAttribArray(unsigned int index)
{
}

void GraphicsLib::vertexAttribPointer(unsigned int index, unsigned int size, DataType type, bool normalized, int stride, const void * pointer)
{

}

void GraphicsLib::pixelStorei(PackingParameter packingParameter, unsigned int param)
{
}

unsigned int GraphicsLib::getMaxSizeTexture()
{
	return NULL;
}

void GraphicsLib::drawElements(RenderType mode, unsigned int count, DataType type, const void * indices)
{

}

void GraphicsLib::enableAlpha()
{
}

void GraphicsLib::disableAlpha()
{
}


NS_SIT_END