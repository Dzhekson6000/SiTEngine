#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "Macros.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "GL/glew.h"
#include "GL/wglew.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include "Texture.h"
#include "FontAtlas.h"

#include <map>

NS_SIT_BEGIN

class SIT_DLL ResourceManager
{
private:
	static ResourceManager * _resourceManager;
	std::map<std::string, ResourceHandle*> _resources;
	ResourceHandle* findHandle(Resource* resource);
	ResourceHandle* loadHandle(Resource* resource);
	ResourceHandle* loadHandleFromType(Resource* resource, ResourceHandle::Type type);
	std::string		getExt(const std::string& str);
public:
	ResourceManager();
	virtual bool init();
	virtual ~ResourceManager();
	static ResourceManager* getInstance();
	ResourceHandle* getHandle(Resource* resource);
};

NS_SIT_END

#endif// RESOURCEMANAGER_H_