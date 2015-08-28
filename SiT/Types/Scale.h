#ifndef SCALE_H_
#define SCALE_H_

#include "Macros.h"

NS_SIT_BEGIN

class Scale
{
private:
	SYNTHESIZE(float, _scaleX, X);
	SYNTHESIZE(float, _scaleY, Y);
	SYNTHESIZE(float, _scaleZ, Z);
public:
	Scale():_scaleX(1.0),_scaleY(1.0),_scaleZ(1.0){}
	Scale(float scaleX, float scaleY) :_scaleX(scaleX), _scaleY(scaleY), _scaleZ(1.0){}
	Scale(float scaleX, float scaleY, float scaleZ) :_scaleX(scaleX), _scaleY(scaleY), _scaleZ(scaleZ){}
};

NS_SIT_END

#endif  // SCALE_H_