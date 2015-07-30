#ifndef DERECTOR_H_
#define DERECTOR_H_

#include "Graphics/Render/Renderer.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "Platform/Win32/Application.h"
#include "Platform/Win32/GLViewImpl.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "Platform/Android/Application.h"
#include "Platform/Android/GLViewImpl.h"
#endif

#include "Events/EventsManager.h"
#include "Base/ScheduleManager.h"

NS_SIT_BEGIN

class Scene;

class SIT_DLL Director
{
private:
	Director(void);
	static Director* _director;
	double _intervalFPS;
	Size _winSize;
	Renderer _renderer;
	Scene * _runningScene;
protected:
	GLViewImpl *_openGLView;
public:
	static Director* getInstance();
	inline GLViewImpl* getGLView() { return _openGLView; }
	Renderer* getRenderer();
	void setOpenGLView(GLViewImpl *openGLView);

	void runScene(Scene *scene);
	Size* getWinSize();


	virtual ~Director();
	virtual bool init();
	void setFPS(double interval);
	void mainLoop();
	void drawScene();
};

NS_SIT_END

#endif// DERECTOR_H_