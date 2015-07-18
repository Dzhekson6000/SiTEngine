#ifndef VECTOR_H_
#define VECTOR_H_

#include "Macros.h"

NS_SIT_BEGIN

class SIT_DLL Vector
{
public:
	float x;
	float y;
	float z;

	Vector()
	{
	}

	Vector(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vector(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

NS_SIT_END

#endif // VECTOR_H_

