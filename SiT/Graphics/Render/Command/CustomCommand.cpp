#include "CustomCommand.h"

NS_SIT_BEGIN

CustomCommand::CustomCommand():func(nullptr)
{
	_type = RenderCommand::Type::CUSTOM_COMMAND;
}

void CustomCommand::init(float globalOrder)
{
	_globalOrder = globalOrder;
}

CustomCommand::~CustomCommand()
{

}

void CustomCommand::execute()
{
	if(func)
	{
		func();
	}
}

NS_SIT_END