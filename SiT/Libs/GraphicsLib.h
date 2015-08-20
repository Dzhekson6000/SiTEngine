#ifndef GRAPHICS_LIB_H_
#define GRAPHICS_LIB_H_

#include "Macros.h"
#include "Geometry/Geometry.h"
#include "Graphics/Shader/Shader.h"
#include "Resource/Texture.h"

#if (TARGET_PLATFORM == PLATFORM_WIN32 && USE_GRAPHICS_LIB == LIB_GRAPHICS_OPENGL)
	#include "GL/glew.h"
#elif(TARGET_PLATFORM == PLATFORM_ANDROID && USE_GRAPHICS_LIB == LIB_GRAPHICS_OPENGL)
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#endif


NS_SIT_BEGIN

class SIT_DLL GraphicsLib
{
public:
	enum class TargetBuffer
	{
		ARRAY_BUFFER,
		ATOMIC_COUNTER_BUFFER,
		COPY_READ_BUFFER,
		COPY_WRITE_BUFFER,
		DISPATCH_INDIRECT_BUFFER,
		DRAW_INDIRECT_BUFFER,
		ELEMENT_ARRAY_BUFFER,
		PIXEL_PACK_BUFFER,
		PIXEL_UNPACK_BUFFER,
		QUERY_BUFFER,
		SHADER_STORAGE_BUFFER,
		TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK_BUFFER,
		UNIFORM_BUFFER,
		UNKOWN
	};

	enum class UsageStore
	{
		STREAM_DRAW,
		STREAM_READ,
		STREAM_COPY,
		STATIC_DRAW,
		STATIC_READ,
		STATIC_COPY,
		DYNAMIC_DRAW,
		DYNAMIC_READ,
		DYNAMIC_COPY,
		UNKOWN
	};

	enum class DataType
	{
		BYTE,
		UNSIGNED_BYTE,
		SHORT,
		UNSIGNED_SHORT,
		INT,
		UNSIGNED_INT,
		HALF_FLOAT,
		FLOAT,
		DOUBLE,
		FIXED,
		INT_2_10_10_10_REV,
		UNSIGNED_INT_2_10_10_10_REV,
		UNSIGNED_INT_10F_11F_11F_REV,
		UNKOWN
	};

	enum class RenderType
	{
		POINTS,
		LINE_STRIP,
		LINE_LOOP,
		LINES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		TRIANGLES,
		QUAD_STRIP,
		QUADS,
		POLYGON,
		UNKOWN
	};

private:
	static GraphicsLib*	_graphicsLib;
protected:
	GraphicsLib();
	virtual bool		init();
	virtual void		destroy();
public:
	static GraphicsLib*	createLib();
	static GraphicsLib*	getInstance();

	virtual void		clearView(Color color);
	virtual Shader*		createNewShader();
	virtual Texture*	createNewTexture(Resource resource);
	virtual void		genBuffers(unsigned int n, unsigned int* buffers);
	virtual void		deleteBuffers(unsigned int n, unsigned int* buffers);
	virtual void		bindBuffer(TargetBuffer target, unsigned int buffer);
	virtual void		bufferData(TargetBuffer  target, ptrdiff_t  size, const void* data, UsageStore usage);
	virtual void		bindTexture(Texture* texture);
	virtual void		activeTexture(unsigned int id);

	virtual void		enableVertexAttribArray(unsigned int index);
	virtual void		vertexAttribPointer(unsigned int index, unsigned int size, DataType type, bool normalized, int stride, const void * pointer);
	
	virtual void		drawElements(RenderType mode, unsigned int count, DataType type, const void * indices);

	virtual void		enableAlpha();
	virtual void		disableAlpha();
};

#define GRAPHICS_LIB() GraphicsLib::getInstance()

NS_SIT_END

#endif// GRAPHICS_LIB_H_