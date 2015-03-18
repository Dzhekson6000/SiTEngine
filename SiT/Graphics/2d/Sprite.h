#ifndef SPRITE_H_
#define SPRITE_H_

#include "GL/glew.h"
#include "Macros.h"
#include "Base/Ref.h"
#include <string>
#include "Resource/ResourceManager.h"
#include "Geometry/Geometry.h"
#include "Graphics/Shader/Shader.h"

NS_SIT_BEGIN

class SIT_DLL Sprite: public Ref
{
private:
	Sprite(){};
	ResourceHandle * image;
	Point _point;
	Size _size;
	Rotate _rotate;
	Scale _scale;
	Matrix4f _transformation;

	Vertex _vertices[4];
	unsigned int _indices[6];
	
	Shader * _shader;
	GLuint VBO;
	GLuint IBO;

	void createVertex();
	Size _screenSize;
	
public:
	static Sprite* create(const std::string& path);
	bool init(const std::string& path);
	Point* getPoint(){return &_point;}
	void setPosition(Point point);
	void setSize(Size size);
	void createSprite(Shader * shader);
	const Matrix4f* transform();
	void draw();
	void setScreenSize(Size size);
};

NS_SIT_END

#endif  // SPRITE_H_