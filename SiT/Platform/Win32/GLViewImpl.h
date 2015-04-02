#ifndef GLVIEWIMPL_H_
#define GLVIEWIMPL_H_

#include "GL/glew.h"
#include "glfw3.h"
#include "Graphics/GLView.h"

NS_SIT_BEGIN

class SIT_DLL GLViewImpl: public GLView
{
private:
	GLViewImpl();
	bool initGlew();
	GLFWwindow* _mainWindow;
	GLFWmonitor* _monitor;
	void createWindow();
public:
	static GLViewImpl* create(const std::string& viewName, int width, int height);
	bool init(const std::string& viewName, int width, int height);

	bool windowShouldClose();
	void swapBuffers();
	GLFWwindow*getGLFWwindow(){return _mainWindow;}

	void setFullScreen(bool isFullScreen);

	void clear(float r, float g, float b);
	void pollEvents();
};


NS_SIT_END

#endif  // GLVIEWIMPL_H_