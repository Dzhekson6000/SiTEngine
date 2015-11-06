#include "Application.h"
#include <unistd.h>

#include <sys/time.h>
unsigned long GetTickCount()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000+tv.tv_usec/1000);
} 

NS_SIT_BEGIN

Application * Application::_application = nullptr;

Application::Application() :_interval(0)
{
	assert(!_application);
	_application = this;
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

	while(!glview->isViewClose())
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
			usleep((_interval - dTime));
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