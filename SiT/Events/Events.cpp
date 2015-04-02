#include "Events.h"

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
	for (auto e:_events)
	{
		if(e->getType() == Event::Type::EVENT_TOUCH &&
			((EventTouch*)e)->getTouchEventType() == EventTouch::TouchEventType::TOUCH_BEGIN)
		{
			((EventTouch*)e)->execute(point);
		}
	}
}

void EventsManager::eventTouchMove( Point point )
{
	for (auto e:_events)
	{
		if(e->getType() == Event::Type::EVENT_TOUCH &&
			((EventTouch*)e)->getTouchEventType() == EventTouch::TouchEventType::TOUCH_MOVE)
		{
			((EventTouch*)e)->execute(point);
		}
	}
}

void EventsManager::eventTouchEnd( Point point )
{
	_mouseStatus = false;
	for (auto e:_events)
	{
		if(e->getType() == Event::Type::EVENT_TOUCH &&
			((EventTouch*)e)->getTouchEventType() == EventTouch::TouchEventType::TOUCH_END)
		{
			((EventTouch*)e)->execute(point);
		}
	}
}

NS_SIT_END