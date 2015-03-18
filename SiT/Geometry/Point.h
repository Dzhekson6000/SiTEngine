#ifndef POINT_H_
#define POINT_H_

#include "Macros.h"

NS_SIT_BEGIN

class SIT_DLL Point
{
private:
	float _x;
	float _y;
	float _z;
public:
	Point():_x(0.0f), _y(0.0f), _z(0.0f){};
	Point(float x, float y):_x(x), _y(y), _z(0.0f){};
	Point(float x, float y, float z):_x(x), _y(y), _z(z){};
	float getX(){return _x;}
	float getY(){return _y;}
	float getZ(){return _z;}
};

NS_SIT_END

#endif  // POINT_H_