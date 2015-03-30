#ifndef EVENTTOUCH_H_
#define EVENTTOUCH_H_

#include "Event.h"
#include "Geometry/Geometry.h"

NS_SIT_BEGIN

class EventTouch: public Event
{
public:
	enum class TouchEventType
	{
		TOUCH_NONE,
		TOUCH_BEGIN,
		TOUCH_MOVE,
		TOUCH_END
	};
	
	EventTouch(TouchEventType touchEventType);
	TouchEventType getTouchEventType(){return _touchEventType; }
	std::function<void(Point)> _func;
	virtual void execute(Point point);
private:
	TouchEventType _touchEventType;
};


NS_SIT_END

#endif  // EVENTTOUCH_H_