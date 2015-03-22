#ifndef GLVIEW_H_
#define GLVIEW_H_
#include "GL/glew.h"
#include "glfw3.h"
#include "Base/Ref.h"
#include <string>
#include "Geometry/Geometry.h"

NS_SIT_BEGIN

class SIT_DLL GLView: public Ref
{
private:
	GLView();
	bool initGlew();
	GLFWwindow* _mainWindow;
	GLFWmonitor* _monitor;
	void createWindow();
	std::string _viewName;
	int _width;
	int _height;
	bool _isFullScreen;
	Size _resolutionSize;
public:
	static GLView* create(const std::string& viewName, int width, int height);
	bool init(const std::string& viewName, int width, int height);
	bool windowShouldClose();
	void swapBuffers();
	void pollEvents();
	GLFWwindow*getGLFWwindow(){return _mainWindow;}

	void setFullScreen(bool isFullScreen);
	bool getFullScreen(){return _isFullScreen;}

	const Size&  getResolutionSize() const;

	void clear(float r, float g, float b);
};

NS_SIT_END

#endif  // GLVIEW_H_