#ifndef DERECTOR_H_
#define DERECTOR_H_

#include "Application.h"
#include "Graphics/GLView.h"
#include "Graphics/Render/Renderer.h"

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
	GLView *_openGLView;
public:
	static Director* getInstance();
	inline GLView* getGLView() { return _openGLView; }
	Renderer* getRenderer();
	void setOpenGLView(GLView *openGLView);

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