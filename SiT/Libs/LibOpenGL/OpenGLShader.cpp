#include "OpenGLShader.h"

NS_SIT_BEGIN

OpenGLShader::OpenGLShader() :_shader(0), _shaderV(0), _shaderF(0)
{
	memset(_uniforms, 0, sizeof(_uniforms));
}

OpenGLShader::~OpenGLShader()
{
	if (_shader)glDeleteProgram(_shader);
}

bool OpenGLShader::initWithByteArrays(const GLchar* shaderByteArrayV, const GLchar* shaderByteArrayF)
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

std::string OpenGLShader::logForOpenGLShader(GLuint shader)
{
	std::string ret;
	GLint logLength = 0, charsWritten = 0;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength < 1) return "";

	char *logBytes = (char*)malloc(logLength + 1);
	glGetShaderInfoLog(shader, logLength, &charsWritten, logBytes);
	logBytes[logLength] = '\0';
	ret = logBytes;
	free(logBytes);

	return ret;
}

bool OpenGLShader::compileShader(GLuint * shader, GLenum type, const GLchar* source)
{
	GLint status;
	if (!source) return false;

	const GLchar *sources[] = {
		"#version 120\n",
#if TARGET_PLATFORM == PLATFORM_WIN32
		(type == GL_VERTEX_SHADER ? "precision mediump float;\n precision mediump int;\n" : "precision mediump float;\n precision mediump int;\n"),
#elif (TARGET_PLATFORM != PLATFORM_WIN32 && TARGET_PLATFORM != PLATFORM_LINUX && TARGET_PLATFORM != PLATFORM_MAC)
		(type == GL_VERTEX_SHADER ? "precision highp float;\n precision highp int;\n" : "precision mediump float;\n precision mediump int;\n"),
#endif
		"uniform mat4 MVPMatrix;\n",
		source,
	};

	*shader = glCreateShader(type);

	GLint lengths = strlen(source);
	glShaderSource(*shader, sizeof(sources) / sizeof(*sources), sources, nullptr);
	glCompileShader(*shader);

	glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		GLsizei length;
		glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length);
		GLchar* src = (GLchar *)malloc(sizeof(GLchar) * length);

		glGetShaderSource(*shader, length, nullptr, src);
		LOG("ERROR: Failed to compile shader:\n%s", src);

		LOG("SiT: %s", logForOpenGLShader(*shader).c_str());

		free(src);
		//abort();
	}
	return (status == GL_TRUE);
}



GLint OpenGLShader::getAttribLocation(const char* attributeName) const
{
	return glGetAttribLocation(_shader, attributeName);
}

GLint OpenGLShader::getUniformLocation(const char* name) const
{
	if (name == nullptr)	LOG("Invalid uniform name");
	if (_shader == 0)		LOG("Invalid operation. Cannot get uniform location when program is not initialized");
	return glGetUniformLocation(_shader, name);
}

void OpenGLShader::bindAttribLocation(const char* attributeName, GLuint index) const
{
	glBindAttribLocation(_shader, index, attributeName);
}

void OpenGLShader::updateUniforms()
{
	_uniforms[UNIFORM_MVP_MATRIX]	= glGetUniformLocation(_shader, UNIFORM_NAME_MVP_MATRIX);
	_uniforms[UNIFORM_SAMPLER]		= glGetUniformLocation(_shader, UNIFORM_NAME_SAMPLER);
	_uniforms[UNIFORM_COLOR]		= glGetUniformLocation(_shader, UNIFORM_NAME_COLOR);

	this->use();

	this->setUniformLocationWith1i(_uniforms[UNIFORM_SAMPLER], 0);
}

bool OpenGLShader::link()
{
	if (_shader == 0)
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

void OpenGLShader::use()
{
	glUseProgram(_shader);
}

void OpenGLShader::setUniformLocationWith1i(GLint location, GLint i1)
{
	glUniform1i((GLint)location, i1);
}

void OpenGLShader::setUniformLocationWith2i(GLint location, GLint i1, GLint i2)
{
	glUniform2i((GLint)location, i1, i2);
}

void OpenGLShader::setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3)
{
	glUniform3i((GLint)location, i1, i2, i3);
}

void OpenGLShader::setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4)
{
	glUniform4i((GLint)location, i1, i2, i3, i4);
}

void OpenGLShader::setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
	glUniform2iv((GLint)location, (GLsizei)numberOfArrays, ints);
}

void OpenGLShader::setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
	glUniform3iv((GLint)location, (GLsizei)numberOfArrays, ints);
}

void OpenGLShader::setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays)
{
	glUniform4iv((GLint)location, (GLsizei)numberOfArrays, ints);
}

void OpenGLShader::setUniformLocationWith1f(GLint location, GLfloat f1)
{
	glUniform1f((GLint)location, f1);
}

void OpenGLShader::setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2)
{
	glUniform2f((GLint)location, f1, f2);
}

void OpenGLShader::setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3)
{
	glUniform3f((GLint)location, f1, f2, f3);
}

void OpenGLShader::setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
	glUniform4f((GLint)location, f1, f2, f3, f4);
}

void OpenGLShader::setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
	glUniform2fv((GLint)location, (GLsizei)numberOfArrays, floats);
}

void OpenGLShader::setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
	glUniform3fv((GLint)location, (GLsizei)numberOfArrays, floats);
}

void OpenGLShader::setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays)
{
	glUniform4fv((GLint)location, (GLsizei)numberOfArrays, floats);
}

void OpenGLShader::setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices)
{
	glUniformMatrix2fv((GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
}

void OpenGLShader::setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices) {
	glUniformMatrix3fv((GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
}


void OpenGLShader::setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices)
{
	glUniformMatrix4fv((GLint)location, (GLsizei)numberOfMatrices, GL_TRUE, matrixArray);
}

void OpenGLShader::reset()
{
	_shaderV = _shaderF = 0;
	memset(_uniforms, 0, sizeof(_uniforms));

	if (_shader)glDeleteProgram(_shader);
	_shader = 0;
}

NS_SIT_END