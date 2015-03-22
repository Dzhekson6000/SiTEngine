#include "GLView.h"

NS_SIT_BEGIN

GLView* GLView::create(const std::string& viewName, int width, int height)
{
	auto ret = new GLView;
	if(ret && ret->init(viewName, width, height)) {
		ret->autorelease();
		return ret;
	}

	return nullptr;
}

GLView::GLView()
{
	glfwInit();	_isFullScreen = false;
	_viewName = "";
}
bool GLView::init(const std::string& viewName, int width, int height)
{
	_viewName = viewName;
	_width = width;
	_height = height;

	_resolutionSize = Size(width, height);

	createWindow();
	glfwMakeContextCurrent(_mainWindow);

	const GLubyte* glVersion = glGetString(GL_VERSION);
	if ( atof((const char*)glVersion) < 1.5 )return false;

	if(!initGlew()) return false;

	return true;
}
bool GLView::initGlew()
{	GLenum res = glewInit();
	if (res != GLEW_OK) {
		//error((const char*)glewGetErrorString(res));
		return false;
	}
	return true;
}

bool GLView::windowShouldClose()
{
	if(_mainWindow)
		return glfwWindowShouldClose(_mainWindow) ? true : false;
	else
		return true;
}

void GLView::swapBuffers()
{
	if(_mainWindow)glfwSwapBuffers(_mainWindow);
}

void GLView::pollEvents()
{
	glfwPollEvents();
}

void GLView::setFullScreen( bool isFullScreen )
{
	if(_isFullScreen == isFullScreen) return;
	_isFullScreen = isFullScreen;

	if(_mainWindow)
	{
		glfwDestroyWindow(_mainWindow);
		createWindow();
	}
}

const Size& GLView::getResolutionSize() const
{
	return _resolutionSize;
}

void GLView::createWindow()
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

void GLView::clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

NS_SIT_END