#include "MatrixObject.h"
#include <string>

NS_SIT_BEGIN


MatrixObject::MatrixObject()
{
}

void MatrixObject::initScaleTransform(Scale scale)
{
	initScaleTransform(scale.getX(), scale.getY(), scale.getZ());
}


void MatrixObject::initScaleTransform(float scaleX, float scaleY, float scaleZ)
{
	_matrix[0][0] = scaleX; _matrix[0][1] = 0.0f;   _matrix[0][2] = 0.0f;   _matrix[0][3] = 0.0f;
	_matrix[1][0] = 0.0f;   _matrix[1][1] = scaleY; _matrix[1][2] = 0.0f;   _matrix[1][3] = 0.0f;
	_matrix[2][0] = 0.0f;   _matrix[2][1] = 0.0f;   _matrix[2][2] = scaleZ; _matrix[2][3] = 0.0f;
	_matrix[3][0] = 0.0f;   _matrix[3][1] = 0.0f;   _matrix[3][2] = 0.0f;   _matrix[3][3] = 1.0f;
}

void MatrixObject::initRotateTransform(Rotate rotate)
{
	initRotateTransform(rotate.getX(), rotate.getY(), rotate.getZ());
}

void MatrixObject::initRotateTransform(float rotateX, float rotateY, float rotateZ)
{
	Matrix rx, ry, rz;

	const float x = (const float)ToRadian(rotateX);
	const float y = (const float)ToRadian(rotateY);
	const float z = (const float)ToRadian(rotateZ);

	rx._matrix[0][0] = 1.0f; rx._matrix[0][1] = 0.0f;	 rx._matrix[0][2] = 0.0f;		rx._matrix[0][3] = 0.0f;
	rx._matrix[1][0] = 0.0f; rx._matrix[1][1] = cosf(x); rx._matrix[1][2] = -sinf(x);	rx._matrix[1][3] = 0.0f;
	rx._matrix[2][0] = 0.0f; rx._matrix[2][1] = sinf(x); rx._matrix[2][2] = cosf(x);	rx._matrix[2][3] = 0.0f;
	rx._matrix[3][0] = 0.0f; rx._matrix[3][1] = 0.0f;	 rx._matrix[3][2] = 0.0f;		rx._matrix[3][3] = 1.0f;

	ry._matrix[0][0] = cosf(y);	ry._matrix[0][1] = 0.0f; ry._matrix[0][2] = -sinf(y);	ry._matrix[0][3] = 0.0f;
	ry._matrix[1][0] = 0.0f;	ry._matrix[1][1] = 1.0f; ry._matrix[1][2] = 0.0f;		ry._matrix[1][3] = 0.0f;
	ry._matrix[2][0] = sinf(y); ry._matrix[2][1] = 0.0f; ry._matrix[2][2] = cosf(y);	ry._matrix[2][3] = 0.0f;
	ry._matrix[3][0] = 0.0f;	ry._matrix[3][1] = 0.0f; ry._matrix[3][2] = 0.0f;		ry._matrix[3][3] = 1.0f;

	rz._matrix[0][0] = cosf(z);	rz._matrix[0][1] = -sinf(z);	rz._matrix[0][2] = 0.0f; rz._matrix[0][3] = 0.0f;
	rz._matrix[1][0] = sinf(z); rz._matrix[1][1] = cosf(z);		rz._matrix[1][2] = 0.0f; rz._matrix[1][3] = 0.0f;
	rz._matrix[2][0] = 0.0f;	rz._matrix[2][1] = 0.0f;		rz._matrix[2][2] = 1.0f; rz._matrix[2][3] = 0.0f;
	rz._matrix[3][0] = 0.0f;	rz._matrix[3][1] = 0.0f;		rz._matrix[3][2] = 0.0f; rz._matrix[3][3] = 1.0f;

	Matrix<4, 4, float> m = rz * ry * rx;
	memcpy(&_matrix, &m._matrix, sizeof(m._matrix));
	return;
}

void MatrixObject::initTranslationTransform(Point point)
{
	initTranslationTransform(point.getX(), point.getY(), point.getZ());
}

void MatrixObject::initTranslationTransform(float x, float y, float z)
{
	_matrix[0][0] = 1.0f; _matrix[0][1] = 0.0f; _matrix[0][2] = 0.0f; _matrix[0][3] = x;
	_matrix[1][0] = 0.0f; _matrix[1][1] = 1.0f; _matrix[1][2] = 0.0f; _matrix[1][3] = y;
	_matrix[2][0] = 0.0f; _matrix[2][1] = 0.0f; _matrix[2][2] = 1.0f; _matrix[2][3] = z;
	_matrix[3][0] = 0.0f; _matrix[3][1] = 0.0f; _matrix[3][2] = 0.0f; _matrix[3][3] = 1.0f;
}

NS_SIT_END