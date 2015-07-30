#include "Schedule.h"

NS_SIT_BEGIN


Schedule::Schedule():
_func(nullptr), _interval(0), _oldTime(0)
{
}

Schedule::Schedule(std::function<void(float)> func, float interval):
_func(func), _interval(interval), _oldTime(0)
{
}

Schedule::~Schedule()
{
}

void Schedule::setFunc(std::function<void(float)> func)
{
	_func = func;
}

void Schedule::setInterval(int interval)
{
	_interval = interval;
}

void Schedule::setOldTime(clock_t oldTime)
{
	_oldTime = oldTime;
}

clock_t Schedule::getOldTime()
{
	return _oldTime;
}

int Schedule::getInterval()
{
	return _interval;
}

void Schedule::execute(float dt)
{
	if (_func)
	{
		_func(dt);
	}
}

NS_SIT_END