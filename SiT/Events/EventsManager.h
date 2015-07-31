#ifndef EVENTS_MANAGER_H_
#define EVENTS_MANAGER_H_

#include <vector>
#include "EventTouch.h"
#include "EventKeypress.h"
#include "EventKeyboard.h"

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

	void eventKeypress(Key key, EventKeypress::EventType eventType);
	void eventKeyboard(unsigned int character);
};

#define EVENTS_MANADGER() EventsManager::getInstance()


NS_SIT_END

#endif  // EVENTS_MANAGER_H_