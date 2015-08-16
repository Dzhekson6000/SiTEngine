#include "EventsManager.h"

NS_SIT_BEGIN

EventsManager* EventsManager::_eventsManager= nullptr;

EventsManager* EventsManager::getInstance()
{
	if (!_eventsManager)
	{
		_eventsManager = new EventsManager();
		_eventsManager->init();
	}

	return _eventsManager;
}

EventsManager::EventsManager():_mouseStatus(false)
{

}

EventsManager::~EventsManager()
{

}

bool EventsManager::init()
{
	return false;
}

void EventsManager::addEvent( Event* event_ )
{
	_events.push_back(event_);
}

void EventsManager::removeEvent( Event* event_ )
{
	event_->release();
	for(size_t i = 0; i < _events.size(); i++)
	{
		if(_events[i] = event_)
		{
			_events.erase(_events.begin()+i);
			return;
		}
	}
}

void EventsManager::clear()
{
	for (auto e:_events)
	{
		e->release();
	}
	_events.clear();
}

bool EventsManager::getMouseStatus()
{
	return _mouseStatus;
}

void EventsManager::eventTouchBegin( Point point )
{
	_mouseStatus = true;
	for (unsigned int i = 0; i < _events.size(); i++)
	{
		EventTouch* a = (EventTouch*)_events.at(i);
		if (a->getType() == Event::Type::EVENT_TOUCH &&
			a->getTouchEventType() == EventTouch::TouchEventType::TOUCH_BEGIN)
		{
			a->execute(point);
		}
	}
}

void EventsManager::eventTouchMove( Point point )
{
	for (unsigned int i = 0; i < _events.size(); i++)
	{
		EventTouch* a = (EventTouch*)_events.at(i);
		if (a->getType() == Event::Type::EVENT_TOUCH &&
			(a->getTouchEventType() == EventTouch::TouchEventType::TOUCH_MOVE && _mouseStatus
			|| a->getTouchEventType() == EventTouch::TouchEventType::CURSOR_MOVE
			)
			)
		{
			a->execute(point);
		}
	}
}

void EventsManager::eventTouchEnd( Point point )
{
	_mouseStatus = false;
	for (unsigned int i = 0; i < _events.size(); i++)
	{
		EventTouch* a = (EventTouch*)_events.at(i);
		if (a->getType() == Event::Type::EVENT_TOUCH &&
			a->getTouchEventType() == EventTouch::TouchEventType::TOUCH_END)
		{
			a->execute(point);
		}
	}
}

void EventsManager::eventKeypress(Key key, EventKeypress::EventType eventType)
{
	for (auto e : _events)
	{
		if (e->getType() == Event::Type::EVENT_KEYPRESS)
		{
			((EventKeypress*)e)->execute(key, eventType);
		}
	}
}

void EventsManager::eventKeyboard(unsigned int character)
{
	for (auto e : _events)
	{
		if (e->getType() == Event::Type::EVENT_KEYBOARD)
		{
			((EventKeyboard*)e)->execute(character);
		}
	}
}

NS_SIT_END