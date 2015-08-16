#ifndef GLVIEWIMPL_H_
#define GLVIEWIMPL_H_

#include "Graphics/GLView.h"
#include "Libs/GraphicsLib.h"
#include "glfw3.h"

NS_SIT_BEGIN

class SIT_DLL GLViewImpl: public GLView
{
private:
	GLFWwindow*			_mainWindow;
	GLFWmonitor*		_monitor;

						GLViewImpl();
	bool				init(const std::string& viewName, int width, int height);
public:
	static GLViewImpl*	create(const std::string& viewName, int width, int height);

	void				createView();
	bool				isViewClose();
	void				swapBuffers();

	void				setFullScreen(bool isFullScreen);

	void				clear(Color color);
	void				pollEvents();
};


NS_SIT_END

#endif  // GLVIEWIMPL_H_