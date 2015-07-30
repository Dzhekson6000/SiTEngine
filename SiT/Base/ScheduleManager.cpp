#include "ScheduleManager.h"

NS_SIT_BEGIN

ScheduleManager* ScheduleManager::_scheduleManager = nullptr;

ScheduleManager* ScheduleManager::getInstance()
{
	if (!_scheduleManager)
	{
		_scheduleManager = new ScheduleManager();
		_scheduleManager->init();
	}

	return _scheduleManager;
}

ScheduleManager::ScheduleManager()
{

}

bool ScheduleManager::init()
{
	return true;
}

void ScheduleManager::updateSchedules()
{
	clock_t time = 0;
	float dt = 0;
	for (auto schedules:_schedules)
	{
		time = clock();
		if (time - schedules->getOldTime() >= schedules->getInterval())
		{
			dt = time - schedules->getOldTime() / 1000;
			schedules->setOldTime(time);
			schedules->execute(dt);
		}
	}
	
}

void ScheduleManager::clearSchedules()
{
	for (auto schedule:_schedules)
	{
		delete schedule;
	}
	_schedules.clear();
}

void ScheduleManager::addSchedule(std::function<void(float)> func, float interval)
{
	_schedules.push_back(new Schedule(func, interval));
}

NS_SIT_END