#ifndef EVENT_H_
#define EVENT_H_

#include "Macros.h"
#include "Base/Ref.h"
#include <functional>

NS_SIT_BEGIN

class Event: public Ref
{
public:
	enum class Type : unsigned int
	{
		noType,
		EVENT_TOUCH,
		EVENT_KEYPRESS,
		EVENT_KEYBOARD
	};
private:
protected:
	Event(Type type);
	Type _type;
public:
	virtual Type getType() const { return _type; }
	virtual void execute();
};


NS_SIT_END

#endif  // EVENT_H_