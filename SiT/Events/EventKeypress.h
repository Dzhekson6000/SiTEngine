#ifndef EVENTKEYPRESS_H_
#define EVENTKEYPRESS_H_

#include "Event.h"
#include "Resource/Keys.h"

NS_SIT_BEGIN

class EventKeypress : public Event
{
public:
	enum class EventType
	{
		NONE,
		KEY_UP,
		KEY_DOWN,
		KEY_PRESS
	};
private:
	std::function<void(Key, EventType)> _func;
public:
	EventKeypress();
	EventKeypress(std::function<void(Key, EventType)> func);
	void setFunc(std::function<void(Key, EventType)> func);
	virtual void execute(Key key, EventType eventType);
};


NS_SIT_END

#endif  // EVENTKEYPRESS_H_