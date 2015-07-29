#include "EventTouch.h"

NS_SIT_BEGIN

EventTouch::EventTouch( TouchEventType touchEventType ):
Event(Type::EVENT_TOUCH), _func(nullptr)
{
	_touchEventType = touchEventType;
}

EventTouch::EventTouch(TouchEventType touchEventType, std::function<void(Point)> func):
Event(Type::EVENT_TOUCH), _touchEventType(touchEventType), _func(func)
{

}

void EventTouch::setFunc(std::function<void(Point)> func)
{
	_func = func;
}

void EventTouch::execute(Point point)
{
	if(_func)
	{
		_func(point);
	}
}

NS_SIT_END