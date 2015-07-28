#ifndef ROTATE_H_
#define ROTATE_H_

#include "Macros.h"

NS_SIT_BEGIN

class Rotate
{
private:
	float _rotateX,_rotateY,_rotateZ;
public:
	Rotate():_rotateX(0.0),_rotateY(0.0),_rotateZ(0.0){}
	Rotate(float rotateX,float rotateY):_rotateX(rotateX),_rotateY(rotateY),_rotateZ(1.0){}
	Rotate(float rotateX,float rotateY, float rotateZ):_rotateX(rotateX),_rotateY(rotateY),_rotateZ(rotateZ){}
	float getX(){return _rotateX;}
	float getY(){return _rotateY;}
	float getZ(){return _rotateZ;}
	void setX(float rotateX){ _rotateX = rotateX; }
	void setY(float rotateY){ _rotateY = rotateY; }
	void setZ(float rotateZ){ _rotateZ = rotateZ; }
};

NS_SIT_END

#endif  // ROTATE_H_