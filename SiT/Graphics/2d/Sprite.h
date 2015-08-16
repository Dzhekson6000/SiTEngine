#ifndef SPRITE_H_
#define SPRITE_H_

#include "Base/Node.h"
#include "Resource/ResourceManager.h"

NS_SIT_BEGIN

class SIT_DLL Sprite: public Node
{
private:
								Sprite(){};
	ResourceHandle*				_image;
	CustomCommand				_customCommand;

	Vertex						_vertices[4];
	unsigned int				_indices[6];
	unsigned int				_VBO;
	unsigned int				_IBO;

public:
	static Sprite*				create(const std::string& path);
	bool						init(const std::string& path);

	const Matrix<4, 4, float>*	transform();

	virtual void				draw(Renderer *renderer);
	virtual void				onDraw();
};

NS_SIT_END

#endif  // SPRITE_H_