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

	Sprite * sprite1 = Sprite::create("2.png");
	sprite1->setPosition(Point(-200,-200));
	scene->addChild(sprite1);

	Sprite * sprite2 = Sprite::create("2.png");
	sprite2->setPosition(Point(0, 0));
	scene->addChild(sprite2);

	Label* label = Label::create();
	label->setPosition(Point(0,0));
	scene->addChild(label);

	director->runScene(scene);

	return true;
}
