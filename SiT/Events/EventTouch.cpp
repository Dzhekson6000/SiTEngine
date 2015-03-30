#include "EventTouch.h"

NS_SIT_BEGIN

EventTouch::EventTouch( TouchEventType touchEventType ):
	Event(Type::EVENT_TOUCH)
{
	_touchEventType = touchEventType;
}

void EventTouch::execute(Point point)
{
	if(_func)
	{
		_func(point);
	}
}

NS_SIT_END