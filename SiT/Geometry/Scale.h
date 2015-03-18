#ifndef SCALE_H_
#define SCALE_H_

#include "Macros.h"

NS_SIT_BEGIN

class Scale
{
private:
	float _scaleX,_scaleY,_scaleZ;
public:
	Scale():_scaleX(1.0),_scaleY(1.0),_scaleZ(1.0){}
	Scale(float rotateX,float rotateY):_scaleX(rotateX),_scaleY(rotateY),_scaleZ(1.0){}
	Scale(float rotateX,float rotateY, float rotateZ):_scaleX(rotateX),_scaleY(rotateY),_scaleZ(rotateZ){}
	float getX(){return _scaleX;}
	float getY(){return _scaleY;}
	float getZ(){return _scaleZ;}
};

NS_SIT_END

#endif  // SCALE_H_