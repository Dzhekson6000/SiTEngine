#ifndef SHADER_H_
#define SHADER_H_
#include "GL/glew.h"
#include "glfw3.h"
#include "Base/Ref.h"
#include <set>

NS_SIT_BEGIN

class SIT_DLL Shader: public Ref
{
private:
	bool compileShader(GLuint * shader, GLenum type, const GLchar* source);
public:
	Shader();
	~Shader();
	bool link();
	void use();
	void updateUniforms();
	void reset();

	bool initWithByteArrays(const GLchar* shaderByteArrayV, const GLchar* shaderByteArrayF);

	GLint getAttribLocation(const char* attributeName) const;
	GLint getUniformLocation(const char* attributeName) const;
	GLint getUniformLocationForName(const char* name) const;
	void bindAttribLocation(const char* attributeName, GLuint index) const;

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

	enum
	{
		VERTEX_ATTRIB_POSITION,
		VERTEX_ATTRIB_COLOR,
		VERTEX_ATTRIB_TEX_COORDS,
		VERTEX_ATTRIB_MAX,
	};

	enum
	{
		UNIFORM_MVP_MATRIX,
		UNIFORM_SAMPLER,

		UNIFORM_MAX,
	};

	static const char* SHADER_NAME_POSITION_COLOR;
	static const char* SHADER_NAME_POSITION_TEXTURE;

	static const char* UNIFORM_NAME_MVP_MATRIX;
	static const char* UNIFORM_NAME_SAMPLER;

	static const char* ATTRIBUTE_NAME_COLOR;
	static const char* ATTRIBUTE_NAME_POSITION;
	static const char* ATTRIBUTE_NAME_TEX_COORD;

private:
	GLuint				_shader;
	GLuint				_shaderV;
	GLuint				_shaderF;
	GLint				_uniforms[UNIFORM_MAX];
	bool				_hasShaderCompiler;
	static const GLuint	_maxMaterialIDNumber;

};

NS_SIT_END

#endif  // SHADER_H_