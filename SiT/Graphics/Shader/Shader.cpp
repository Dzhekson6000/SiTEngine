#include "Shader.h"

NS_SIT_BEGIN

const char* Shader::SHADER_NAME_POSITION_COLOR = "ShaderPositionColor";
const char* Shader::SHADER_NAME_POSITION_TEXTURE = "ShaderPositionTexture";

const char* Shader::UNIFORM_NAME_MVP_MATRIX = "MVMatrix";
const char* Shader::UNIFORM_NAME_SAMPLER	= "u_Texture0";

const char* Shader::ATTRIBUTE_NAME_COLOR = "a_color";
const char* Shader::ATTRIBUTE_NAME_POSITION = "a_position";
const char* Shader::ATTRIBUTE_NAME_TEX_COORD = "a_texCoord";

Shader::Shader():_shader(0), _shaderV(0), _shaderF(0)
{
	memset(_uniforms, 0, sizeof(_uniforms));
}

Shader::~Shader()
{
	if(_shader)glDeleteProgram(_shader);
}

bool Shader::initWithByteArrays(const GLchar* shaderByteArrayV, const GLchar* shaderByteArrayF)
{
	_shader = glCreateProgram();
	_shaderV = _shaderF = 0;
	if (shaderByteArrayV)
	{
		if (!compileShader(&_shaderV, GL_VERTEX_SHADER, shaderByteArrayV))
		{
			return false;
		}
	}

	if (shaderByteArrayF)
	{
		if (!compileShader(&_shaderF, GL_FRAGMENT_SHADER, shaderByteArrayF))
		{
			return false;
		}
	}

	if (_shaderV)
	{
		glAttachShader(_shader, _shaderV);
	}

	if (_shaderF)
	{
		glAttachShader(_shader, _shaderF);
	}
	return true;
}

bool Shader::compileShader(GLuint * shader, GLenum type, const GLchar* source)
{
	GLint status;
	if (!source)
	{
		return false;
	}

	const GLchar *sources[] = {
		"uniform mat4 MVPMatrix;\n",
		source,
	};

	*shader = glCreateShader(type);
	glShaderSource(*shader, sizeof(sources)/sizeof(*sources), sources, nullptr);
	glCompileShader(*shader);

	glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

	if (! status)
	{
		GLsizei length;
		glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length);
		GLchar* src = (GLchar *)malloc(sizeof(GLchar) * length);

		glGetShaderSource(*shader, length, nullptr, src);
		LOG("cocos2d: ERROR: Failed to compile shader:\n%s", src);

		free(src);
		abort();
	}
	return (status == GL_TRUE);
}

GLint Shader::getAttribLocation(const char* attributeName) const
{
	return glGetAttribLocation(_shader, attributeName);
}

GLint Shader::getUniformLocation(const char* attributeName) const
{
	return glGetUniformLocation(_shader, attributeName);
}

void Shader::bindAttribLocation(const char* attributeName, GLuint index) const
{
	glBindAttribLocation(_shader, index, attributeName);
}

void Shader::updateUniforms()
{
	_uniforms[UNIFORM_MVP_MATRIX]	= glGetUniformLocation(_shader, UNIFORM_NAME_MVP_MATRIX);
	_uniforms[UNIFORM_SAMPLER]		= glGetUniformLocation(_shader, UNIFORM_NAME_SAMPLER);

	this->use();

	this->setUniformLocationWith1i(_uniforms[UNIFORM_SAMPLER], 0);
}

bool Shader::link()
{
	if(_shader == 0)
	{
		LOG("Shader link invalid program");
		return false;
	}

	glLinkProgram(_shader);

	if (_shaderV)
	{
		glDeleteShader(_shaderV);
	}

	if (_shaderF)
	{
		glDeleteShader(_shaderF);
	}

	_shaderV = _shaderF = 0;

	return true;
}

void Shader::use()
{
	glUseProgram(_shader);
}

GLint Shader::getUniformLocationForName(const char* name) const
{
	if(name == nullptr)LOG("Invalid uniform name");
	if(_shader == 0)LOG("Invalid operation. Cannot get uniform location when program is not initialized");
	return glGetUniformLocation(_shader, name);
}

void Shader::setUniformLocationWith1i(GLint location, GLint i1)
{
	glUniform1i( (GLint)location, i1);
}

void Shader::setUniformLocationWith2i(GLint location, GLint i1, GLint i2)
{
	glUniform2i( (GLint)location, i1, i2);
}

void Shader::setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3)
{
	glUniform3i( (GLint)location, i1, i2, i3);
}

void Shader::setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4)
{
	glUniform4i( (GLint)location, i1, i2, i3, i4);
}

void Shader::setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
	glUniform2iv( (GLint)location, (GLsizei)numberOfArrays, ints );
}

void Shader::setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
	glUniform3iv( (GLint)location, (GLsizei)numberOfArrays, ints );
}

void Shader::setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
	glUniform4iv( (GLint)location, (GLsizei)numberOfArrays, ints );
}

void Shader::setUniformLocationWith1f(GLint location, GLfloat f1)
{
	glUniform1f( (GLint)location, f1);
}

void Shader::setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2)
{
	glUniform2f( (GLint)location, f1, f2);
}

void Shader::setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3)
{
	glUniform3f( (GLint)location, f1, f2, f3);
}

void Shader::setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
	glUniform4f( (GLint)location, f1, f2, f3,f4);
}

void Shader::setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
	glUniform2fv( (GLint)location, (GLsizei)numberOfArrays, floats );
}

void Shader::setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
	glUniform3fv( (GLint)location, (GLsizei)numberOfArrays, floats );
}

void Shader::setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
	glUniform4fv( (GLint)location, (GLsizei)numberOfArrays, floats );
}

void Shader::setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices)
{
	glUniformMatrix2fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
}

void Shader::setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices) {
	glUniformMatrix3fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
}


void Shader::setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices)
{
	glUniformMatrix4fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
}

void Shader::reset()
{
	_shaderV = _shaderF = 0;
	memset(_uniforms, 0, sizeof(_uniforms));

	if(_shader)glDeleteProgram(_shader);
	_shader = 0;
}

NS_SIT_END