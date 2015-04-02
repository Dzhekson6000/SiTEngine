#ifndef RESOURCEHANDLE_H_
#define RESOURCEHANDLE_H_

#include "Macros.h"
#include <string>

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "glfw3.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

NS_SIT_BEGIN

struct Resource
{
	std::string _name;
	Resource();
	Resource(std::string name):_name(name){};
};

class SIT_DLL ResourceHandle
{
private:
	Resource _resource;
	GLuint _textureId;
	unsigned int _width, _height;
public:
	ResourceHandle(Resource resource);
	GLuint* getTextureId();
	unsigned int getWidth();
	void setWidth(unsigned int width);
	unsigned int getHeight();
	void setHeight(unsigned int height);
};

NS_SIT_END

#endif// RESOURCEHANDLE_H_