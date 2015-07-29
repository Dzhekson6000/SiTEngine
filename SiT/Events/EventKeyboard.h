#ifndef EVENTKEYBOARD_H_
#define EVENTKEYBOARD_H_

#include "Event.h"

NS_SIT_BEGIN

class EventKeyboard : public Event
{
private:
	std::function<void(unsigned int)> _func;
public:
	EventKeyboard();
	EventKeyboard(std::function<void(unsigned int)> func);
	void setFunc(std::function<void(unsigned int)> func);
	virtual void execute(unsigned int character);
};


NS_SIT_END

#endif  // EVENTKEYBOARD_H_