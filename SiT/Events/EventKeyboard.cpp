#include "EventKeyboard.h"

NS_SIT_BEGIN

EventKeyboard::EventKeyboard():
Event(Event::Type::EVENT_KEYBOARD), _func(nullptr)
{

}

EventKeyboard::EventKeyboard(std::function<void(unsigned int)> func):
Event(Event::Type::EVENT_KEYBOARD), _func(func)
{

}

void EventKeyboard::setFunc(std::function<void(unsigned int)> func)
{
	_func = func;
}

void EventKeyboard::execute(unsigned int character)
{
	if (_func)
	{
		_func(character);
	}
}

NS_SIT_END
