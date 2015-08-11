#include "Application.h"

NS_SIT_BEGIN

Application * Application::_application = nullptr;

Application::Application()
{
	assert(!_application);
	_application = this;
	_interval = 0;
}

Application::~Application()
{
	assert(this == _application);
	_application = NULL;
}

int Application::run()
{

	int frame = 0;
	int dTime = 0;
	int newTime = GetTickCount();
	int oldTime = GetTickCount();

	if (!applicationLaunching())
	{
		return 0;
	}

	auto director = Director::getInstance();
	auto glview = director->getGLView();
	
	glview->retain();

	while(!glview->windowShouldClose())
	{
		newTime = GetTickCount();
		dTime =  newTime - oldTime;
		if (_interval == 0 || dTime >= _interval)
		{
			if (dTime > 1000)
			{
				_fps = frame;
				frame = 0;
			}
			frame++;

			director->mainLoop();
			glview->pollEvents();
			oldTime = newTime;
		}
		else{
			Sleep(_interval - dTime);
		}
	}

	return 0;
}

Application* Application::getInstance()
{
	assert(_application);
	return _application;
}

void Application::setFPS(double interval)
{
	_interval = 1000*interval;
}

NS_SIT_END