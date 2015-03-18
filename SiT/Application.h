#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Macros.h"
#include <Windows.h>
#include "assert.h"
#include "Director.h"

NS_SIT_BEGIN

class SIT_DLL Application
{
private:
	LARGE_INTEGER _interval;
protected:
	HINSTANCE           _instance;
	static Application * _application;
	virtual bool applicationLaunching(){ return false;}
public:
	Application();
	virtual ~Application();
	int run();
	static Application* getInstance();
	void setFPS(double interval);

};

NS_SIT_END

#endif// APPLICATION_H_