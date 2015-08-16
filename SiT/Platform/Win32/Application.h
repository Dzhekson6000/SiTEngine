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
	int _interval;
protected:
	static Application * _application;
	virtual bool applicationLaunching(){ return false;}
public:
	Application();
	virtual ~Application();
	int run();
	static Application* getInstance();
	void setFPS(double interval);

	unsigned int _fps;

};

NS_SIT_END

#endif// APPLICATION_H_