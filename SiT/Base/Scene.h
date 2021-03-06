#ifndef SCENE_H_
#define SCENE_H_

#include "Node.h"

NS_SIT_BEGIN

class SIT_DLL Scene: public Node
{
private:
protected:

public:
	Scene();
	virtual ~Scene();
	virtual bool init();
	virtual Node* getScene();
	const Matrix<4, 4, float>* transform();

	using Node::addChild;
        CREATE_FUNC(Scene);
};

NS_SIT_END

#endif // SCENE_H_
