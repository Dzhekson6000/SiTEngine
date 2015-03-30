#include "Event.h"

NS_SIT_BEGIN

Event::Event(Type type):
_type(type),
_func(nullptr)
{

}

void Event::execute()
{
	if(_func)
	{
		_func();
	}
}

NS_SIT_END