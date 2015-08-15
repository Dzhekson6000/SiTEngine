#include "Scene.h"

NS_SIT_BEGIN

Scene::Scene()
{
	EventsManager::getInstance()->clear();
	SCHEDULE_MANADGER()->clearSchedules();
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

const Matrix<4, 4, float>* Scene::transform()
{
	Size* screen = getScreenSize();

	if (_isUpdated)return &_transformation;

	MatrixObject scale, rotate, translation;
	scale.initScaleTransform(_scale);
	rotate.initRotateTransform(_rotate);

	translation.initTranslationTransform(
		_point.getX() / (screen->getWidth() / 2)-1,
		_point.getY() / (screen->getHeight() / 2)-1,
		_point.getZ()
		);

	_transformation = scale * rotate * translation;

	Node::transform();

	_isUpdated = true;
	return &_transformation;
}

NS_SIT_END
