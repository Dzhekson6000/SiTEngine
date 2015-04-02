#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Macros.h"
#include "assert.h"
#include "Director.h"

NS_SIT_BEGIN

class SIT_DLL Application
{
private:
protected:
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