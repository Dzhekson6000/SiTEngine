#include "GLFWEventHandler.h"

NS_SIT_BEGIN

EventsManager* GLFWEventHandler::_eventsManager = nullptr;

void GLFWEventHandler::onGLFWError( int errorID, const char* errorDesc )
{

}

void GLFWEventHandler::onGLFWMouseCallBack( GLFWwindow* window, int button, int action, int modify )
{
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	Point point((float)x,(float)y);

	if(GLFW_PRESS == action)
	{
		EVENTSMANADGER()->eventTouchBegin(point);
	}
	else if(GLFW_RELEASE == action)
	{
		EVENTSMANADGER()->eventTouchEnd(point);
	}
}

void GLFWEventHandler::onGLFWMouseMoveCallBack( GLFWwindow* window, double x, double y )
{
	Point point((float)x,(float)y);

	if(EVENTSMANADGER()->getMouseStatus())EVENTSMANADGER()->eventTouchMove(point);
}

void GLFWEventHandler::onGLFWMouseScrollCallback( GLFWwindow* window, double x, double y )
{

}

void GLFWEventHandler::onGLFWKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{

}

void GLFWEventHandler::onGLFWCharCallback( GLFWwindow* window, unsigned int character )
{

}

void GLFWEventHandler::onGLFWWindowPosCallback( GLFWwindow* windows, int x, int y )
{

}

void GLFWEventHandler::onGLFWframebuffersize( GLFWwindow* window, int w, int h )
{

}

void GLFWEventHandler::onGLFWWindowSizeFunCallback( GLFWwindow *window, int width, int height )
{

}

void GLFWEventHandler::setEventsManager(EventsManager* eventsManager)
{
	_eventsManager = eventsManager;
}

NS_SIT_END