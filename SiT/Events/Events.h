#ifndef EVENTS_H_
#define EVENTS_H_

#include "Macros.h"
#include <vector>
#include "EventTouch.h"

NS_SIT_BEGIN

class EventsManager: public Ref
{
private:
	static EventsManager* _eventsManager;
	EventsManager();
	std::vector<Event*> _events;
	bool _mouseStatus;
public:
	static EventsManager* getInstance();
	virtual ~EventsManager();
	bool init();
	void addEvent(Event* event_);
	void removeEvent(Event* event_);
	void clear();

	bool getMouseStatus();

	void eventTouchBegin(Point point);
	void eventTouchMove(Point point);
	void eventTouchEnd(Point point);
};

#define EVENTSMANADGER() EventsManager::getInstance()


NS_SIT_END

#endif  // EVENTS_H_