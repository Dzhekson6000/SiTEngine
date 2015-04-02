#include "GLViewImpl.h"

NS_SIT_BEGIN

GLViewImpl::GLViewImpl()
{
}

GLViewImpl* GLViewImpl::create(const std::string& viewName, int width, int height)
{
	auto ret = new GLViewImpl;
	if(ret && ret->init(viewName, width, height)) {
		ret->autorelease();
		return ret;
	}

	return nullptr;
}

bool GLViewImpl::init(const std::string& viewName, int width, int height)
{
	return true;
}

void GLViewImpl::swapBuffers()
{
}

NS_SIT_END