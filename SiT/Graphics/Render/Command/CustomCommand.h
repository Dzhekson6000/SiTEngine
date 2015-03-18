#ifndef CUSTOMCOMMAND_H_
#define CUSTOMCOMMAND_H_

#include "RenderCommand.h"
#include <functional>

NS_SIT_BEGIN

class CustomCommand : public RenderCommand
{
public:
	CustomCommand();
	~CustomCommand();
	void init(float globalOrder);

	void execute();

	inline bool isTranslucent() { return true; }
	std::function<void()> func;
};

NS_SIT_END

#endif //CUSTOMCOMMAND_H_