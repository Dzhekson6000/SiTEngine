#include "GLFWEventHandler.h"

NS_SIT_BEGIN

void GLFWEventHandler::onGLFWError( int errorID, const char* errorDesc )
{

}

void GLFWEventHandler::onGLFWMouseCallBack( GLFWwindow* window, int button, int action, int modify )
{
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	Point point((float)x, (float)(Director::getInstance()->getWinSize()->getHeight() - y));

	if(GLFW_PRESS == action)
	{
		EVENTS_MANADGER()->eventTouchBegin(point);
	}
	else if(GLFW_RELEASE == action)
	{
		EVENTS_MANADGER()->eventTouchEnd(point);
	}
}

void GLFWEventHandler::onGLFWMouseMoveCallBack( GLFWwindow* window, double x, double y )
{
	Point point((float)x, (float)(Director::getInstance()->getWinSize()->getHeight() - y));

	if(EVENTS_MANADGER()->getMouseStatus())EVENTS_MANADGER()->eventTouchMove(point);
}

void GLFWEventHandler::onGLFWKeyCallback( GLFWwindow* window, int keyCode, int scancode, int action, int mods )
{
	EventKeypress::EventType type = EventKeypress::EventType::NONE;
	Key key = Key::KEY_UNKNOWN;
	if (action == GLFW_PRESS)
	{
		type = EventKeypress::EventType::KEY_DOWN;
	}
	else if (action == GLFW_RELEASE)
	{
		type = EventKeypress::EventType::KEY_UP;
	}
	else if (action = GLFW_REPEAT)
	{
		type = EventKeypress::EventType::KEY_PRESS;
	}

	switch (keyCode)
	{
		case GLFW_KEY_SPACE:
			key = Key::KEY_SPACE;
			break;
		case GLFW_KEY_APOSTROPHE:
			key = Key::KEY_APOSTROPHE;
			break;
		case GLFW_KEY_COMMA:
			key = Key::KEY_COMMA;
			break;
		case GLFW_KEY_MINUS:
			key = Key::KEY_MINUS;
			break;
		case GLFW_KEY_PERIOD:
			key = Key::KEY_PERIOD;
			break;
		case GLFW_KEY_SLASH:
			key = Key::KEY_SLASH;
			break;
		case GLFW_KEY_0:
			key = Key::KEY_0;
			break;
		case GLFW_KEY_1:
			key = Key::KEY_1;
			break;
		case GLFW_KEY_2:
			key = Key::KEY_2;
			break;
		case GLFW_KEY_3:
			key = Key::KEY_3;
			break;
		case GLFW_KEY_4:
			key = Key::KEY_4;
			break;
		case GLFW_KEY_5:
			key = Key::KEY_5;
			break;
		case GLFW_KEY_6:
			key = Key::KEY_6;
			break;
		case GLFW_KEY_7:
			key = Key::KEY_7;
			break;
		case GLFW_KEY_8:
			key = Key::KEY_8; 
			break;
		case GLFW_KEY_9:
			key = Key::KEY_9; 
			break;
		case GLFW_KEY_SEMICOLON:
			key = Key::KEY_SEMICOLON;
			break;
		case GLFW_KEY_EQUAL:
			key = Key::KEY_EQUAL;
			break;
		case GLFW_KEY_A:
			key = Key::KEY_A;
			break;
		case GLFW_KEY_B:
			key = Key::KEY_B;
			break;
		case GLFW_KEY_C:
			key = Key::KEY_C;
			break;
		case GLFW_KEY_D:
			key = Key::KEY_D; 
			break;
		case GLFW_KEY_E:
			key = Key::KEY_E; 
			break;
		case GLFW_KEY_F:
			key = Key::KEY_F; 
			break;
		case GLFW_KEY_G:
			key = Key::KEY_G; 
			break;
		case GLFW_KEY_H:
			key = Key::KEY_H; 
			break;
		case GLFW_KEY_I:
			key = Key::KEY_I; 
			break;
		case GLFW_KEY_J:
			key = Key::KEY_J; 
			break;
		case GLFW_KEY_K:
			key = Key::KEY_K; 
			break;
		case GLFW_KEY_L:
			key = Key::KEY_L; 
			break;
		case GLFW_KEY_M:
			key = Key::KEY_M; 
			break;
		case GLFW_KEY_N:
			key = Key::KEY_N; 
			break;
		case GLFW_KEY_O:
			key = Key::KEY_O; 
			break;
		case GLFW_KEY_P:
			key = Key::KEY_P; 
			break;
		case GLFW_KEY_Q:
			key = Key::KEY_Q; 
			break;
		case GLFW_KEY_R:
			key = Key::KEY_R; 
			break;
		case GLFW_KEY_S:
			key = Key::KEY_S; 
			break;
		case GLFW_KEY_T:
			key = Key::KEY_T; 
			break;
		case GLFW_KEY_U:
			key = Key::KEY_U; 
			break;
		case GLFW_KEY_V:
			key = Key::KEY_V; 
			break;
		case GLFW_KEY_W:
			key = Key::KEY_W; 
			break;
		case GLFW_KEY_X:
			key = Key::KEY_X;
			break;
		case GLFW_KEY_Y:
			key = Key::KEY_Y;
			break;
		case GLFW_KEY_Z:
			key = Key::KEY_Z; 
			break;
		case GLFW_KEY_LEFT_BRACKET:
			key = Key::KEY_LEFT_BRACKET;
			break;
		case GLFW_KEY_BACKSLASH:
			key = Key::KEY_BACKSLASH;
			break;
		case GLFW_KEY_RIGHT_BRACKET:
			key = Key::KEY_RIGHT_BRACKET;
			break;
		case GLFW_KEY_GRAVE_ACCENT:
			key = Key::KEY_GRAVE_ACCENT;
			break;
		case GLFW_KEY_ESCAPE:
			key = Key::KEY_ESCAPE;
			break;
		case GLFW_KEY_ENTER:
			key = Key::KEY_ENTER;
			break;
		case GLFW_KEY_TAB:
			key = Key::KEY_TAB;
			break;
		case GLFW_KEY_BACKSPACE:
			key = Key::KEY_BACKSPACE;
			break;
		case GLFW_KEY_INSERT:
			key = Key::KEY_INSERT;
			break;
		case GLFW_KEY_DELETE:
			key = Key::KEY_DELETE;
			break;
		case GLFW_KEY_RIGHT:
			key = Key::KEY_RIGHT;
			break;
		case GLFW_KEY_LEFT:
			key = Key::KEY_LEFT;
			break;
		case GLFW_KEY_DOWN:
			key = Key::KEY_DOWN;
			break;
		case GLFW_KEY_UP:
			key = Key::KEY_UP;
			break;
		case GLFW_KEY_PAGE_UP:
			key = Key::KEY_PAGE_UP;
			break;
		case GLFW_KEY_PAGE_DOWN:
			key = Key::KEY_PAGE_DOWN;
			break;
		case GLFW_KEY_HOME:
			key = Key::KEY_HOME;
			break;
		case GLFW_KEY_END:
			key = Key::KEY_END;
			break;
		case GLFW_KEY_CAPS_LOCK:
			key = Key::KEY_CAPS_LOCK;
			break;
		case GLFW_KEY_SCROLL_LOCK:
			key = Key::KEY_SCROLL_LOCK;
			break;
		case GLFW_KEY_NUM_LOCK:
			key = Key::KEY_NUM_LOCK;
			break;
		case GLFW_KEY_PRINT_SCREEN:
			key = Key::KEY_PRINT_SCREEN;
			break;
		case GLFW_KEY_PAUSE:
			key = Key::KEY_PAUSE;
			break;
		case GLFW_KEY_F1:
			key = Key::KEY_F1;
			break;
		case GLFW_KEY_F2:
			key = Key::KEY_F2;
			break;
		case GLFW_KEY_F3:
			key = Key::KEY_F3;
			break;
		case GLFW_KEY_F4:
			key = Key::KEY_F4;
			break;
		case GLFW_KEY_F5:
			key = Key::KEY_F5;
			break;
		case GLFW_KEY_F6:
			key = Key::KEY_F6;
			break;
		case GLFW_KEY_F7:
			key = Key::KEY_F7;
			break;
		case GLFW_KEY_F8:
			key = Key::KEY_F8;
			break;
		case GLFW_KEY_F9:
			key = Key::KEY_F9;
			break;
		case GLFW_KEY_F10:
			key = Key::KEY_F10;
			break;
		case GLFW_KEY_F11:
			key = Key::KEY_F11;
			break;
		case GLFW_KEY_F12:
			key = Key::KEY_F12;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			key = Key::KEY_LEFT_SHIFT;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			key = Key::KEY_LEFT_CONTROL;
			break;
		case GLFW_KEY_LEFT_ALT:
			key = Key::KEY_LEFT_ALT;
			break;
		case GLFW_KEY_LEFT_SUPER:
			key = Key::KEY_LEFT_SUPER;
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			key = Key::KEY_RIGHT_SHIFT;
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			key = Key::KEY_RIGHT_CONTROL;
			break;
		case GLFW_KEY_RIGHT_ALT:
			key = Key::KEY_RIGHT_ALT;
			break;
		case GLFW_KEY_RIGHT_SUPER:
			key = Key::KEY_RIGHT_SUPER;
			break;
		case GLFW_KEY_MENU:
			key = Key::KEY_MENU;
			break;
	}

	EVENTS_MANADGER()->eventKeypress(key, type);
}

void GLFWEventHandler::onGLFWCharCallback( GLFWwindow* window, unsigned int character )
{
	EVENTS_MANADGER()->eventKeyboard(character);
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

NS_SIT_END