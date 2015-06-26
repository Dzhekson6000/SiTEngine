#include "ResourceHandle.h"

NS_SIT_BEGIN

ResourceHandle::ResourceHandle( Resource resource, Type	type)
:_resource(resource), _type(type)
{
}

ResourceHandle::Type ResourceHandle::getType()
{
	return _type;
}

Resource ResourceHandle::getResource()
{
	return _resource;
}

NS_SIT_END