#ifndef SCENE_H_
#define SCENE_H_

#include "Macros.h"
#include "Node.h"

NS_SIT_BEGIN

class SIT_DLL Scene: public Node
{
private:
	Scene();
protected:

public:
	static Scene *create();
	virtual ~Scene();
	virtual bool init() override;
	virtual Node* getScene() override;

	using Node::addChild;
};

NS_SIT_END

#endif // SCENE_H_
