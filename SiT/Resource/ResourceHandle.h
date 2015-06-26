#ifndef RESOURCEHANDLE_H_
#define RESOURCEHANDLE_H_

#include "Macros.h"
#include <string>

NS_SIT_BEGIN

struct Resource
{
	std::string _name;
	Resource();
	Resource(std::string name):_name(name){};
};

class SIT_DLL ResourceHandle
{
public:
	enum class Type
	{
		noType,
		TEXTURE,
		FONT,
	};
private:
	Resource	_resource;
	Type		_type;
public:
	ResourceHandle(Resource resource, Type type);
	Type getType();
	Resource getResource();
};

NS_SIT_END

#endif// RESOURCEHANDLE_H_