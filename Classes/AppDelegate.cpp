#include "AppDelegate.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationLaunching()
{
	auto director = Director::getInstance();
	auto glview = director->getGLView();
	if(!glview) {
		glview = GLViewImpl::create("Test", 800, 600);
		//glview->setFullScreen(true);
		director->setOpenGLView(glview);
	}

	director->setFPS(1.0/60.0);

	Scene* scene = Scene::create();
	Sprite * sprite = Sprite::create("1.bmp");
	scene->addChild(sprite);

	director->runScene(scene);

	return true;
}
