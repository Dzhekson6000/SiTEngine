#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include "Macros.h"
#include <functional>
#include <time.h>

NS_SIT_BEGIN

class SIT_DLL Schedule
{
private:
	clock_t _oldTime;
	int _interval;
	std::function<void(float)> _func;
public:
	Schedule();
	Schedule(std::function<void(float)> func, float interval);
	virtual ~Schedule();
	void setFunc(std::function<void(float)> func);
	void setInterval(int interval);
	void setOldTime(clock_t oldTime);
	clock_t getOldTime();
	int		getInterval();
	virtual void execute(float dt);
};

NS_SIT_END

#endif// SCHEDULE_MANAGER_H_