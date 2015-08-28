#ifndef MATRIX4_H_
#define MATRIX4_H_

#include "Matrix.h"

NS_SIT_BEGIN

class MatrixObject:public Matrix<4,4,float>
{
public:
	MatrixObject();
	~MatrixObject(){}

	void initScaleTransform(Scale scale);
	void initScaleTransform(float scaleX, float scaleY, float scaleZ);
	void initRotateTransform(Rotate rotate);
	void initRotateTransform(float rotateX, float rotateY, float rotateZ);
	void initTranslationTransform(Point point);
	void initTranslationTransform(float x, float y, float z);

private:

};

NS_SIT_END

#endif // MATRIX4_H_