#ifndef COLOR_H_
#define COLOR_H_

struct Color
{
	float _r;
	float _g;
	float _b;

	Color() :_r(0), _g(0), _b(0){}
	Color(float r, float g, float b) :_r(r), _g(g), _b(b){}
};

#endif  // COLOR_H_