#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "GL/glew.h"
#include "GL/wglew.h"
#include "ResourceHandle.h"
#include <map>
#include <SOIL.h>


NS_SIT_BEGIN

class SIT_DLL ResourceManager
{
private:
	static ResourceManager * _resourceManager;
	std::map<std::string, ResourceHandle*> _resources;
	ResourceHandle* findHandle(Resource* resource);
	ResourceHandle* loadHandle(Resource* resource);
public:
	ResourceManager();
	virtual bool init();
	virtual ~ResourceManager();
	static ResourceManager* getInstance();
	ResourceHandle* getHandle(Resource* resource);
};

NS_SIT_END

#endif// RESOURCEMANAGER_H_