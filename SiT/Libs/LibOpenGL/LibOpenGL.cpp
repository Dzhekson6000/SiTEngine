#include "LibOpenGL.h"
#include "OpenGlShader.h"
#include "OpenGLTexture.h"

NS_SIT_BEGIN

LibOpenGL::LibOpenGL()
{	
}

bool LibOpenGL::init()
{
	return glewCheckGLError(glewInit());
}

void LibOpenGL::destroy()
{

}

bool LibOpenGL::glewCheckGLError(GLenum var)
{
	if (var != GLEW_OK) {
		LOG("LibOpenGL GLEW error: %c", (const char*)glewGetErrorString(var));
		return false;
	}
	return true;
}

GLenum LibOpenGL::getTargetBufferGL(TargetBuffer target)
{
	switch (target)
	{
	case SiT::GraphicsLib::TargetBuffer::ARRAY_BUFFER:
		return GL_ARRAY_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::ATOMIC_COUNTER_BUFFER:
		return GL_ATOMIC_COUNTER_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::COPY_READ_BUFFER:
		return GL_COPY_READ_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::COPY_WRITE_BUFFER:
		return GL_COPY_WRITE_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::DISPATCH_INDIRECT_BUFFER:
		return GL_DISPATCH_INDIRECT_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::DRAW_INDIRECT_BUFFER:
		return GL_DRAW_INDIRECT_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::ELEMENT_ARRAY_BUFFER:
		return GL_ELEMENT_ARRAY_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::PIXEL_PACK_BUFFER:
		return GL_PIXEL_PACK_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::PIXEL_UNPACK_BUFFER:
		return GL_PIXEL_UNPACK_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::QUERY_BUFFER:
		return GL_QUERY_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::SHADER_STORAGE_BUFFER:
		return GL_SHADER_STORAGE_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::TEXTURE_BUFFER:
		return GL_TEXTURE_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::TRANSFORM_FEEDBACK_BUFFER:
		return GL_TRANSFORM_FEEDBACK_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::UNIFORM_BUFFER:
		return GL_UNIFORM_BUFFER;
	case SiT::GraphicsLib::TargetBuffer::UNKOWN:
		return 0;
	default:
		return 0;
	}
}

GLenum LibOpenGL::getUsageStoreGL(UsageStore usage)
{
	switch (usage)
	{
	case SiT::GraphicsLib::UsageStore::STREAM_DRAW:
		return GL_STREAM_DRAW;
	case SiT::GraphicsLib::UsageStore::STREAM_READ:
		return GL_STREAM_READ;
	case SiT::GraphicsLib::UsageStore::STREAM_COPY:
		return GL_STREAM_COPY;
	case SiT::GraphicsLib::UsageStore::STATIC_DRAW:
		return GL_STATIC_DRAW;
	case SiT::GraphicsLib::UsageStore::STATIC_READ:
		return GL_STATIC_READ;
	case SiT::GraphicsLib::UsageStore::STATIC_COPY:
		return GL_STATIC_COPY;
	case SiT::GraphicsLib::UsageStore::DYNAMIC_DRAW:
		return GL_DYNAMIC_DRAW;
	case SiT::GraphicsLib::UsageStore::DYNAMIC_READ:
		return GL_DYNAMIC_READ;
	case SiT::GraphicsLib::UsageStore::DYNAMIC_COPY:
		return GL_DYNAMIC_COPY;
	case SiT::GraphicsLib::UsageStore::UNKOWN:
		return 0;
	default:
		return 0;
	}
}

GLenum LibOpenGL::getDataTypeGl(DataType type)
{
	switch (type)
	{
	case SiT::GraphicsLib::DataType::BYTE:
		return GL_BYTE;
	case SiT::GraphicsLib::DataType::UNSIGNED_BYTE:
		return GL_UNSIGNED_BYTE;
	case SiT::GraphicsLib::DataType::SHORT:
		return GL_SHORT;
	case SiT::GraphicsLib::DataType::UNSIGNED_SHORT:
		return GL_UNSIGNED_SHORT;
	case SiT::GraphicsLib::DataType::INT:
		return GL_INT;
	case SiT::GraphicsLib::DataType::UNSIGNED_INT:
		return GL_UNSIGNED_INT;
	case SiT::GraphicsLib::DataType::HALF_FLOAT:
		return GL_HALF_FLOAT;
	case SiT::GraphicsLib::DataType::FLOAT:
		return GL_FLOAT;
	case SiT::GraphicsLib::DataType::DOUBLE:
		return GL_DOUBLE;
	case SiT::GraphicsLib::DataType::FIXED:
		return GL_FIXED;
	case SiT::GraphicsLib::DataType::INT_2_10_10_10_REV:
		return GL_INT_2_10_10_10_REV;
	case SiT::GraphicsLib::DataType::UNSIGNED_INT_2_10_10_10_REV:
		return GL_UNSIGNED_INT_2_10_10_10_REV;
	case SiT::GraphicsLib::DataType::UNSIGNED_INT_10F_11F_11F_REV:
		return GL_UNSIGNED_INT_10F_11F_11F_REV;
	case SiT::GraphicsLib::DataType::UNKOWN:
		return 0;
	default:
		return 0;
	}
}

GLenum LibOpenGL::getRenderTypeGL(RenderType mode)
{
	switch (mode)
	{
	case SiT::GraphicsLib::RenderType::POINTS:
		return GL_POINTS;
	case SiT::GraphicsLib::RenderType::LINE_STRIP:
		return GL_LINE_STRIP;
	case SiT::GraphicsLib::RenderType::LINE_LOOP:
		return GL_LINE_LOOP;
	case SiT::GraphicsLib::RenderType::LINES:
		return GL_LINES;
	case SiT::GraphicsLib::RenderType::TRIANGLE_STRIP:
		return GL_TRIANGLE_STRIP;
	case SiT::GraphicsLib::RenderType::TRIANGLE_FAN:
		return GL_TRIANGLE_FAN;
	case SiT::GraphicsLib::RenderType::TRIANGLES:
		return GL_TRIANGLES;
	case SiT::GraphicsLib::RenderType::QUAD_STRIP:
		return GL_QUAD_STRIP;
	case SiT::GraphicsLib::RenderType::QUADS:
		return GL_QUADS;
	case SiT::GraphicsLib::RenderType::POLYGON:
		return GL_POLYGON;
	case SiT::GraphicsLib::RenderType::UNKOWN:
		return 0;
	default:
		return 0;
	}
}

GLboolean LibOpenGL::getBool(bool boolean)
{
	if (boolean)
	{
		return GL_TRUE;
	}
	return GL_FALSE;
}

void LibOpenGL::clearView(Color color)
{
	glClearColor(color.getR(), color.getG(), color.getB(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Shader* LibOpenGL::createNewShader()
{
	return new OpenGLShader();
}

Texture* LibOpenGL::createNewTexture(Resource resource)
{
	return new OpenGLTexture(resource);
}

void LibOpenGL::genBuffers(unsigned int n, unsigned int* buffers)
{
	glGenBuffers(n, buffers);
}

void LibOpenGL::bindBuffer(TargetBuffer target, unsigned int buffer)
{
	glBindBuffer(getTargetBufferGL(target), buffer);
}

void LibOpenGL::bufferData(TargetBuffer target, ptrdiff_t size, const void* data, UsageStore usage)
{
	glBufferData(getTargetBufferGL(target), size, data, getUsageStoreGL(usage));
}

void LibOpenGL::bindTexture(Texture* texture)
{
	glBindTexture(GL_TEXTURE_2D, ((OpenGLTexture*)texture)->getTextureId());
}

void LibOpenGL::activeTexture(unsigned int id)
{
	glActiveTexture(id);
}

void LibOpenGL::enableVertexAttribArray(unsigned int index)
{
	glEnableVertexAttribArray(index);
}

void LibOpenGL::vertexAttribPointer(unsigned int index, unsigned int size, DataType type, bool normalized, int stride, const void * pointer)
{
	glVertexAttribPointer(index, size, getDataTypeGl(type), getBool(normalized), stride, pointer);
}

void LibOpenGL::drawElements(RenderType mode, unsigned int count, DataType type, const void * indices)
{
	glDrawElements(getRenderTypeGL(mode), count, getDataTypeGl(type), indices);
}

void LibOpenGL::enableAlpha()
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void LibOpenGL::disableAlpha()
{
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}

NS_SIT_END