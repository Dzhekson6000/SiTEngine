#include "GLViewImpl.h"
#include "Events/GLFWEventHandler.h"

NS_SIT_BEGIN

GLViewImpl::GLViewImpl()
{
	glfwInit();
}

bool GLViewImpl::initGlew()
{	GLenum res = glewInit();
	if (res != GLEW_OK) {
		//error((const char*)glewGetErrorString(res));
		return false;
	}
	return true;
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
	_viewName = viewName;
	_width = width;
	_height = height;

	_resolutionSize = Size(width, height);

	createWindow();
	glfwMakeContextCurrent(_mainWindow);

	GLFWEventHandler::setEventsManager(EVENTSMANADGER());
	glfwSetMouseButtonCallback(_mainWindow, GLFWEventHandler::onGLFWMouseCallBack);
	glfwSetCursorPosCallback(_mainWindow, GLFWEventHandler::onGLFWMouseMoveCallBack);
	glfwSetScrollCallback(_mainWindow, GLFWEventHandler::onGLFWMouseScrollCallback);
	glfwSetCharCallback(_mainWindow, GLFWEventHandler::onGLFWCharCallback);
	glfwSetKeyCallback(_mainWindow, GLFWEventHandler::onGLFWKeyCallback);
	glfwSetWindowPosCallback(_mainWindow, GLFWEventHandler::onGLFWWindowPosCallback);
	glfwSetFramebufferSizeCallback(_mainWindow, GLFWEventHandler::onGLFWframebuffersize);
	glfwSetWindowSizeCallback(_mainWindow, GLFWEventHandler::onGLFWWindowSizeFunCallback);


	const GLubyte* glVersion = glGetString(GL_VERSION);
	if ( atof((const char*)glVersion) < 1.5 )return false;

	if(!initGlew()) return false;

	return true;
}

void GLViewImpl::createWindow()
{
	_monitor = _isFullScreen ? glfwGetPrimaryMonitor() : NULL;
	_mainWindow = glfwCreateWindow(_width,
		_height,
		_viewName.c_str(),
		_monitor,
		nullptr);

	glViewport(0, 0, _width, _height);

	glEnable( GL_DEPTH_TEST);
	glEnable( GL_LIGHTING);
	glEnable( GL_LIGHT0);

}

bool GLViewImpl::windowShouldClose()
{
	if(_mainWindow)
		return glfwWindowShouldClose(_mainWindow) ? true : false;
	else
		return true;
}

void GLViewImpl::setFullScreen( bool isFullScreen )
{
	if(_isFullScreen == isFullScreen) return;
	_isFullScreen = isFullScreen;

	if(_mainWindow)
	{
		glfwDestroyWindow(_mainWindow);
		createWindow();
	}
}

void GLViewImpl::swapBuffers()
{
	if(_mainWindow)glfwSwapBuffers(_mainWindow);
}

void GLViewImpl::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLViewImpl::pollEvents()
{
	glfwPollEvents();
}

NS_SIT_END