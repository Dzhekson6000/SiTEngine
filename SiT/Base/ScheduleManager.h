#ifndef SCHEDULE_MANAGER_H_
#define SCHEDULE_MANAGER_H_

#include "Macros.h"
#include <vector>
#include <functional>
#include "Schedule.h"

NS_SIT_BEGIN

class SIT_DLL ScheduleManager
{
private:
	std::vector<Schedule*> _schedules;

	static ScheduleManager* _scheduleManager;
	ScheduleManager();
	bool init();
protected:
	
public:
	static ScheduleManager* getInstance();
	void updateSchedules();
	void clearSchedules();
	void addSchedule(std::function<void(float)> func, float interval);
};

#define SCHEDULE_MANADGER() ScheduleManager::getInstance()

NS_SIT_END

#endif// SCHEDULE_MANAGER_H_