#include "Application.h"

NS_SIT_BEGIN

Application * Application::_application = nullptr;

Application::Application()
: _instance(nullptr)
{
	_instance    = GetModuleHandle(nullptr);
	assert(!_application);
	_application = this;
	_interval.QuadPart = 0;
}

Application::~Application()
{
	assert(this == _application);
	_application = NULL;
}

int Application::run()
{

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nLast);

	if (!applicationLaunching())
	{
		return 0;
	}

	auto director = Director::getInstance();
	auto glview = director->getGLView();
	
	glview->retain();

	while(!glview->windowShouldClose())
	{
		QueryPerformanceCounter(&nNow);
		if (nNow.QuadPart - nLast.QuadPart > _interval.QuadPart)
		{
			nLast.QuadPart = nNow.QuadPart;

			director->drawScene();
			glview->pollEvents();
		}
		else{
			Sleep((int)(((double)_interval.QuadPart/(double)nFreq.QuadPart)*1000));
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
	LARGE_INTEGER nFreq;
	QueryPerformanceFrequency(&nFreq);
	_interval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

NS_SIT_END