#include "GLViewImpl.h"
#include "GLFWEventHandler.h"

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
	if (!glfwInit()) {
		LOG("GLFW Init - failed");
		return false;
	}

	//GraphicsLib::createLib(GraphicsLib::TypeGraphicsLib::OpenGL);

	_viewName = viewName;
	_width = width;
	_height = height;

	_resolutionSize = Size(width, height);
	
	createView();

	return true;

}

void GLViewImpl::createView()
{
	_monitor = _isFullScreen ? glfwGetPrimaryMonitor() : NULL;
	_mainWindow = glfwCreateWindow(_width, _height, _viewName.c_str(), _monitor, nullptr);
	
	glfwMakeContextCurrent(_mainWindow);
	glfwSwapInterval(0);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_CULL_FACE);

	glfwSetMouseButtonCallback(_mainWindow, GLFWEventHandler::onGLFWMouseCallBack);
	glfwSetCursorPosCallback(_mainWindow, GLFWEventHandler::onGLFWMouseMoveCallBack);
	glfwSetCharCallback(_mainWindow, GLFWEventHandler::onGLFWCharCallback);
	glfwSetKeyCallback(_mainWindow, GLFWEventHandler::onGLFWKeyCallback);

	glfwSetWindowPosCallback(_mainWindow, GLFWEventHandler::onGLFWWindowPosCallback);
	glfwSetFramebufferSizeCallback(_mainWindow, GLFWEventHandler::onGLFWframebuffersize);
	glfwSetWindowSizeCallback(_mainWindow, GLFWEventHandler::onGLFWWindowSizeFunCallback);

	GraphicsLib::getInstance();
}

bool GLViewImpl::isViewClose()
{
	if (_mainWindow)
		return glfwWindowShouldClose(_mainWindow) ? true : false;
	else
		return true;
}

void GLViewImpl::setFullScreen( bool isFullScreen )
{
	if (_isFullScreen == isFullScreen) return;
	_isFullScreen = isFullScreen;

	if (_mainWindow)
	{
		glfwDestroyWindow(_mainWindow);
		createView();
	}
}

void GLViewImpl::swapBuffers()
{
	if (_mainWindow)glfwSwapBuffers(_mainWindow);
}

void GLViewImpl::clear(Color color)
{
	GRAPHICS_LIB()->clearView(color);
}

void GLViewImpl::pollEvents()
{
	glfwPollEvents();
}

NS_SIT_END