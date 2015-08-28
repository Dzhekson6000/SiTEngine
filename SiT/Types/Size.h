#ifndef SIZE_H_
#define SIZE_H_

#include "Macros.h"

NS_SIT_BEGIN

class Size
{
private:
	SYNTHESIZE(int, _width, Width);
	SYNTHESIZE(int, _height, Height);
public:
	Size():_width(0),_height(0){}
	Size(int width, int height):_width(width),_height(height){}
	bool operator==(const Size& size) const;

	static const Size ZERO;
};

NS_SIT_END

#endif  // SIZE_H_