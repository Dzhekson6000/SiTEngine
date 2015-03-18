#ifndef RENDERCOMMAND_H_
#define RENDERCOMMAND_H_

#include "Macros.h"

NS_SIT_BEGIN

class RenderCommand
{
public:

    enum class Type
    {
        UNKNOWN_COMMAND,
        CUSTOM_COMMAND,
        GROUP_COMMAND,
    };

    inline float getGlobalOrder() const { return _globalOrder; }
    inline Type getType() const { return _type; }

protected:
    RenderCommand();
    virtual ~RenderCommand();

    Type _type;
    float _globalOrder;
};

NS_SIT_END

#endif //RENDERCOMMAND_H_