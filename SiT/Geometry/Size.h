#ifndef SIZE_H_
#define SIZE_H_

#include "Macros.h"

NS_SIT_BEGIN

class Size
{
private:
	int _width;
	int _height;
public:
	Size():_width(0),_height(0){}
	Size(int width, int height):_width(width),_height(height){}
	int getWidth(){return _width;}
	int getHeight(){return _height;}

	static const Size ZERO;
};

NS_SIT_END

#endif  // SIZE_H_