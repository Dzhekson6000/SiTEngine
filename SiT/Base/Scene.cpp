#include "Scene.h"

NS_SIT_BEGIN

Scene::Scene()
{

}

Scene * Scene::create()
{
	Scene *ret = new Scene();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		delete ret;
		return nullptr;
	}
}

Scene::~Scene()
{

}

bool Scene::init()
{
	bool ret = false;
	do 
	{
		Director * director;
		if(!(director = Director::getInstance())) break;
		this->setScreenSize(director->getWinSize());
		ret = true;
	} while (0);
	return ret;
}


Node* Scene::getScene()
{
	return this;
}

NS_SIT_END