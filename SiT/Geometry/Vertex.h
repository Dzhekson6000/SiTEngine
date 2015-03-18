#ifndef VERTEX_H_
#define VERTEX_H_
#include "external/math_3d.h"

struct Vertex
{
	Vector3f position;
	Vector3f color;
	Vector2f uv;

	Vertex(){}
	Vertex(Vector3f pos, Vector3f col, Vector2f texCoord): position(pos), color(col), uv(texCoord) {}
};

#endif  // GLVIEW_H_