#ifndef GLFWEVENTHANDLER_H_
#define GLFWEVENTHANDLER_H_

#include "Macros.h"
#include "glfw3.h"
#include "Events/Events.h"

NS_SIT_BEGIN

class GLFWEventHandler
{
public:
	static void onGLFWError(int errorID, const char* errorDesc);
	static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
	static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
	static void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y);
	static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
	static void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y);
	static void onGLFWframebuffersize(GLFWwindow* window, int w, int h);
	static void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height);
	static void setEventsManager(EventsManager* eventsManager);


private:
	static EventsManager* _eventsManager;
};

NS_SIT_END

#endif  // GLFWEVENTHANDLER_H_