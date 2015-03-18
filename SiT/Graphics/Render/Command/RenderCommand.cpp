#include "RenderCommand.h"

NS_SIT_BEGIN

RenderCommand::RenderCommand():_type(RenderCommand::Type::UNKNOWN_COMMAND), _globalOrder(0)
{

}

RenderCommand::~RenderCommand()
{
}

NS_SIT_END