#ifndef GLVIEWIMPL_H_
#define GLVIEWIMPL_H_

#include <EGL/egl.h>
#include <android/log.h>
#include "Graphics/GLView.h"

NS_SIT_BEGIN

class SIT_DLL GLViewImpl: public GLView
{
private:
	GLViewImpl();
public:
	static GLViewImpl* create(const std::string& viewName, int width, int height);
	bool init(const std::string& viewName, int width, int height);
	void swapBuffers();
};


NS_SIT_END

#endif  // GLVIEWIMPL_H_