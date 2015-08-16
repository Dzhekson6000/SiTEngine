#ifndef OPENGL_SHADER_H_
#define OPENGL_SHADER_H_

#include "Graphics/Shader/Shader.h"
#include "Libs/GraphicsLib.h"
#include <string>
NS_SIT_BEGIN

class SIT_DLL OpenGLShader : public Shader
{
private:
	bool					compileShader(GLuint * shader, GLenum type, const GLchar* source);
	std::string				logForOpenGLShader(GLuint shader);
public:
							OpenGLShader();
							~OpenGLShader();
	bool					link();
	void					use();
	void					updateUniforms();
	void					reset();
	GLuint getShader(){ return _shader; }

	bool initWithByteArrays(const GLchar* shaderByteArrayV, const GLchar* shaderByteArrayF);
	void bindAttribLocation(const char* attributeName, GLuint index) const;

	GLint getAttribLocation(const char* attributeName) const;
	GLint getUniformLocation(const char* name) const;

	void setUniformLocationWith1i(GLint location, GLint i1);
	void setUniformLocationWith2i(GLint location, GLint i1, GLint i2);
	void setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3);
	void setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4);
	void setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays);
	void setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays);
	void setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays);
	void setUniformLocationWith1f(GLint location, GLfloat f1);
	void setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2);
	void setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);
	void setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
	void setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);
	void setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);
	void setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);
	void setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);
	void setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);
	void setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);

private:
	GLuint				_shader;
	GLuint				_shaderV;
	GLuint				_shaderF;
	GLint				_uniforms[UNIFORM_MAX];
	bool				_hasShaderCompiler;
	static const GLuint	_maxMaterialIDNumber;

};

NS_SIT_END

#endif  // OPENGL_SHADER_H_