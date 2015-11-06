#include "Shader.h"
#include <cstddef>

NS_SIT_BEGIN

const char* Shader::SHADER_NAME_POSITION_COLOR = "ShaderPositionColor";
const char* Shader::SHADER_NAME_POSITION_TEXTURE = "ShaderPositionTexture";
const char* Shader::SHADER_NAME_POSITION_COLOR_TEXTURE = "ShaderPositionColorTexture";

const char* Shader::UNIFORM_NAME_MVP_MATRIX = "MVPMatrix";
const char* Shader::UNIFORM_NAME_SAMPLER	= "u_Texture0";
const char* Shader::UNIFORM_NAME_COLOR		= "u_color";

const char* Shader::ATTRIBUTE_NAME_COLOR = "a_color";
const char* Shader::ATTRIBUTE_NAME_POSITION = "a_position";
const char* Shader::ATTRIBUTE_NAME_TEX_COORD = "a_texCoord";

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::initWithByteArrays(const char* shaderByteArrayV, const char* shaderByteArrayF)
{
	return true;
}

void Shader::bindAttribLocation(const char* attributeName, unsigned int index) const
{
}

void Shader::updateUniforms()
{
}

bool Shader::link()
{
	return false;
}

void Shader::use()
{
}

int Shader::getAttribLocation(const char* attributeName) const
{
	return NULL;
}

int Shader::getUniformLocation(const char* name) const
{
	return NULL;
}

void Shader::setUniformLocationWith1i(int location, int i1)
{
}

void Shader::setUniformLocationWith2i(int location, int i1, int i2)
{
}

void Shader::setUniformLocationWith3i(int location, int i1, int i2, int i3)
{
}

void Shader::setUniformLocationWith4i(int location, int i1, int i2, int i3, int i4)
{
}

void Shader::setUniformLocationWith2iv(int location, int* ints, unsigned int numberOfArrays)
{
}

void Shader::setUniformLocationWith3iv(int location, int* ints, unsigned int numberOfArrays)
{
}

void Shader::setUniformLocationWith4iv(int location, int* ints, unsigned int numberOfArrays)
{
}

void Shader::setUniformLocationWith1f(int location, float f1)
{
}

void Shader::setUniformLocationWith2f(int location, float f1, float f2)
{
}

void Shader::setUniformLocationWith3f(int location, float f1, float f2, float f3)
{
}

void Shader::setUniformLocationWith4f(int location, float f1, float f2, float f3, float f4)
{
}

void Shader::setUniformLocationWith2fv(int location, const float* floats, unsigned int numberOfArrays)
{
}

void Shader::setUniformLocationWith3fv(int location, const float* floats, unsigned int numberOfArrays)
{
}

void Shader::setUniformLocationWith4fv(int location, const float* floats, unsigned int numberOfArrays)
{
}

void Shader::setUniformLocationWithMatrix2fv(int location, const float* matrixArray, unsigned int numberOfMatrices)
{
}

void Shader::setUniformLocationWithMatrix3fv(int location, const float* matrixArray, unsigned int numberOfMatrices) {
}


void Shader::setUniformLocationWithMatrix4fv(int location, const float* matrixArray, unsigned int numberOfMatrices)
{
}

void Shader::reset()
{
}

NS_SIT_END