#ifndef LIB_OPENGL_H_
#define LIB_OPENGL_H_

#include "Libs/GraphicsLib.h"

NS_SIT_BEGIN

class SIT_DLL LibOpenGL : public GraphicsLib
{
private:
	bool		init();
	void		destroy();
	bool		glewCheckGLError(GLenum var);
	GLenum		getTargetBufferGL(TargetBuffer target);
	GLenum		getUsageStoreGL(UsageStore usage);
	GLenum		getDataTypeGl(DataType type);
	GLenum		getRenderTypeGL(RenderType mode);
	GLboolean	getBool(bool boolean);
protected:

public:
				LibOpenGL();
	void		clearView(Color color);
	Shader*		createNewShader();
	Texture*	createNewTexture(Resource resource);
	void		genBuffers(unsigned int n, unsigned int* buffers);
	void		deleteBuffers(unsigned int n, unsigned int* buffers);
	void		bindBuffer(TargetBuffer target, unsigned int buffer);
	void		bufferData(TargetBuffer  target, ptrdiff_t  size, const void* data, UsageStore usage);

	void		bindTexture(Texture* texture);
	void		activeTexture(unsigned int id);

	void		enableVertexAttribArray(unsigned int index);
	void		vertexAttribPointer(unsigned int index, unsigned int size, DataType type, bool normalized, int stride, const void * pointer);

	void		drawElements(RenderType mode, unsigned int count, DataType type, const void * indices);

	void		enableAlpha();
	void		disableAlpha();

};

NS_SIT_END

#endif// LIB_OPENGL_H_