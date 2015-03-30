#include "Director.h"
#include "Base/Scene.h"

NS_SIT_BEGIN

Director* Director::_director= nullptr;

Director* Director::getInstance()
{
	if (!_director)
	{
		_director = new Director();
		_director->init();
	}

	return _director;
}

Renderer* Director::getRenderer()
{
	return &_renderer;
}

Director::Director(): _runningScene(nullptr)
{
}

bool Director::init()
{
	_openGLView = nullptr;	
	_winSize	= Size::ZERO;

	return true;
}

Director::~Director(void)
{
	PoolManager::destroyInstance();
	_director = nullptr;
	if(_runningScene)
	{
		_runningScene->release();
		_runningScene = nullptr;
	}
}

void Director::setOpenGLView( GLView *openGLView )
{
	if (_openGLView != openGLView)
	{
		if(_openGLView)
			_openGLView->release();
		_openGLView = openGLView;
		_openGLView->retain();

		_winSize = _openGLView->getResolutionSize();
	}

}

void Director::setFPS( double interval )
{
	_intervalFPS = interval;
	Application::getInstance()->setFPS(interval);
}

void Director::mainLoop()
{
	drawScene();
	PoolManager::getInstance()->getCurrentPool()->clear();
}

void Director::drawScene()
{
	_openGLView->clear(0.0f,0.0f,0.0f);

	if(_runningScene)_runningScene->visit(&_renderer);

	_renderer.render();
	if (_openGLView)_openGLView->swapBuffers();
}

void Director::runScene(Scene *scene)
{
	if (_runningScene)
	{
		_runningScene->cleanup();
		_runningScene->release();
	}
	_runningScene = scene;
}

Size* Director::getWinSize()
{
	return &_winSize;
}

NS_SIT_END