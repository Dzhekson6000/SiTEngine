#ifndef ROTATE_H_
#define ROTATE_H_

#include "Macros.h"

NS_SIT_BEGIN

class Rotate
{
private:
	SYNTHESIZE(float, _rotateX, X);
	SYNTHESIZE(float, _rotateY, Y);
	SYNTHESIZE(float, _rotateZ, Z);
public:
	Rotate():_rotateX(0.0),_rotateY(0.0),_rotateZ(0.0){}
	Rotate(float rotateX,float rotateY):_rotateX(rotateX),_rotateY(rotateY),_rotateZ(1.0){}
	Rotate(float rotateX,float rotateY, float rotateZ):_rotateX(rotateX),_rotateY(rotateY),_rotateZ(rotateZ){}
};

NS_SIT_END

#endif  // ROTATE_H_