#ifndef COLOR_H_
#define COLOR_H_

#include "Macros.h"

NS_SIT_BEGIN

class Color
{
private:
	SYNTHESIZE(float, _r, R);
	SYNTHESIZE(float, _g, G);
	SYNTHESIZE(float, _b, B);
public:

	Color() :_r(0), _g(0), _b(0){}
	Color(float r, float g, float b) :_r(r), _g(g), _b(b){}
	Color(int r, int g, int b) :_r((float)r / 255), _g((float)g / 255), _b((float)b / 255){}

	const static Color WHITE;
	const static Color YELLOW;
	const static Color BLUE;
	const static Color GREEN;
	const static Color RED;
	const static Color MAGENTA;
	const static Color BLACK;
	const static Color ORANGE;
	const static Color GRAY;
};

NS_SIT_END

#endif  // COLOR_H_