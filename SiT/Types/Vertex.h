#ifndef VERTEX_H_
#define VERTEX_H_

#include "Vector.h"

NS_SIT_BEGIN

class SIT_DLL Vertex
{
public:
	Vector position;
	Vector color;
	Vector uv;

	Vertex(){}
	Vertex(Vector pos, Vector col, Vector texCoord): position(pos), color(col), uv(texCoord) {}
};

NS_SIT_END

#endif  // GLVIEW_H_