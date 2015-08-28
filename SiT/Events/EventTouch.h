#ifndef EVENTTOUCH_H_
#define EVENTTOUCH_H_

#include "Event.h"
#include "Types/Types.h"

NS_SIT_BEGIN

class EventTouch: public Event
{
public:
	enum class TouchEventType : unsigned int
	{
		TOUCH_NONE,
		TOUCH_BEGIN,
		TOUCH_MOVE,
		TOUCH_END,
		CURSOR_MOVE
	};
private:
	std::function<void(Point)> _func;
	TouchEventType _touchEventType;
public:
	
	EventTouch(TouchEventType touchEventType);
	EventTouch(TouchEventType touchEventType, std::function<void(Point)> func);
	void setFunc(std::function<void(Point)> func);
	TouchEventType getTouchEventType(){return _touchEventType; }
	virtual void execute(Point point);
};


NS_SIT_END

#endif  // EVENTTOUCH_H_