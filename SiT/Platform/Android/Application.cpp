#include "Application.h"
#include <android/log.h>
#include <jni.h>

NS_SIT_BEGIN

Application * Application::_application = nullptr;

Application::Application()
{
	assert(!_application);
	_application = this;
}

Application::~Application()
{
	assert(this == _application);
	_application = NULL;
}

int Application::run()
{
	if (! applicationLaunching())
	{
		return 0;
	}

	return -1;
}

Application* Application::getInstance()
{
	assert(_application);
	return _application;
}

void Application::setFPS(double interval)
{
	//-> java.setFPS
}

NS_SIT_END

void android_app_init() __attribute__((weak));

extern "C"
{
	void Java_org_SiT_lib_SiTLib_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
	{
		auto director = SiT::Director::getInstance();
		auto glview = director->getGLView();
		if (!glview)
		{
			glview = SiT::GLViewImpl::create("Android app", w, h);
			director->setOpenGLView(glview);

			android_app_init();
			SiT::Application::getInstance()->run();
		}
	}

	void Java_org_SiT_lib_SiTLib_nativeDraw(JNIEnv*  env, jobject thiz)
	{
		SiT::Director::getInstance()->mainLoop();
	}

	void Java_org_SiT_lib_SiTLib_nativeOnSurfaceChanged(JNIEnv*  env, jobject thiz, jint w, jint h)
	{
	}


}