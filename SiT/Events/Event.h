#ifndef EVENT_H_
#define EVENT_H_

#include "Macros.h"
#include "Base/Ref.h"
#include <functional>

NS_SIT_BEGIN

class Event: public Ref
{
public:
	enum class Type
	{
		noType,
		EVENT_TOUCH
	};
	virtual Type getType() const { return _type; }
	std::function<void()> _func;
	virtual void execute();
protected:
	Event(Type type);
	Type _type;
};


NS_SIT_END

#endif  // EVENT_H_