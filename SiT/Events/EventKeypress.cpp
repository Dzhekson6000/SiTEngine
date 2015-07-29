#include "EventKeypress.h"

NS_SIT_BEGIN

EventKeypress::EventKeypress() :
Event(Event::Type::EVENT_KEYPRESS), _func(nullptr)
{

}

EventKeypress::EventKeypress(std::function<void(Key, EventType)> func):
Event(Event::Type::EVENT_KEYPRESS), _func(func)
{

}

void EventKeypress::setFunc(std::function<void(Key, EventType)> func)
{
	_func = func;
}

void EventKeypress::execute(Key key, EventType eventType)
{
	if (_func)
	{
		_func(key, eventType);
	}
}

NS_SIT_END