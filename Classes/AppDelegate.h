#ifndef  APPDELEGATE_H_
#define  APPDELEGATE_H_

#include "SiT.h"

USING_NS_SIT

class AppDelegate : private Application
{
public:
	AppDelegate();
	virtual ~AppDelegate();

	virtual bool applicationLaunching();
};

#endif // APPDELEGATE_H_