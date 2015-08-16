#ifndef SHADER_H_
#define SHADER_H_

#include "Base/Ref.h"

NS_SIT_BEGIN

class SIT_DLL Shader: public Ref
{
public:
						Shader();
	virtual				~Shader();
	virtual bool		link();
	virtual void		use();
	virtual void		updateUniforms();
	virtual void		reset();

	virtual bool		initWithByteArrays(const char* shaderByteArrayV, const char* shaderByteArrayF);
	virtual void		bindAttribLocation(const char* attributeName, unsigned int index) const;

	virtual int			getAttribLocation(const char* attributeName) const;
	virtual int			getUniformLocation(const char* name) const;

	virtual void		setUniformLocationWith1i(int location, int i1);
	virtual void		setUniformLocationWith2i(int location, int i1, int i2);
	virtual void		setUniformLocationWith3i(int location, int i1, int i2, int i3);
	virtual void		setUniformLocationWith4i(int location, int i1, int i2, int i3, int i4);
	virtual void		setUniformLocationWith2iv(int location, int* ints, unsigned int numberOfArrays);
	virtual void		setUniformLocationWith3iv(int location, int* ints, unsigned int numberOfArrays);
	virtual void		setUniformLocationWith4iv(int location, int* ints, unsigned int numberOfArrays);
	virtual void		setUniformLocationWith1f(int location, float f1);
	virtual void		setUniformLocationWith2f(int location, float f1, float f2);
	virtual void		setUniformLocationWith3f(int location, float f1, float f2, float f3);
	virtual void		setUniformLocationWith4f(int location, float f1, float f2, float f3, float f4);
	virtual void		setUniformLocationWith2fv(int location, const float* floats, unsigned int numberOfArrays);
	virtual void		setUniformLocationWith3fv(int location, const float* floats, unsigned int numberOfArrays);
	virtual void		setUniformLocationWith4fv(int location, const float* floats, unsigned int numberOfArrays);
	virtual void		setUniformLocationWithMatrix2fv(int location, const float* matrixArray, unsigned int numberOfMatrices);
	virtual void		setUniformLocationWithMatrix3fv(int location, const float* matrixArray, unsigned int numberOfMatrices);
	virtual void		setUniformLocationWithMatrix4fv(int location, const float* matrixArray, unsigned int numberOfMatrices);

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
		UNIFORM_COLOR,

		UNIFORM_MAX,
	};

	static const char* SHADER_NAME_POSITION_COLOR;
	static const char* SHADER_NAME_POSITION_TEXTURE;
	static const char* SHADER_NAME_POSITION_COLOR_TEXTURE;

	static const char* UNIFORM_NAME_MVP_MATRIX;
	static const char* UNIFORM_NAME_SAMPLER;
	static const char* UNIFORM_NAME_COLOR;

	static const char* ATTRIBUTE_NAME_COLOR;
	static const char* ATTRIBUTE_NAME_POSITION;
	static const char* ATTRIBUTE_NAME_TEX_COORD;
};

NS_SIT_END

#endif  // SHADER_H_