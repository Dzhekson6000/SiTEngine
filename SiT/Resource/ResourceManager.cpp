#include "ResourceManager.h"
#include "Image.h"

NS_SIT_BEGIN

ResourceManager * ResourceManager::_resourceManager = nullptr;

ResourceManager* ResourceManager::getInstance()
{
	if (!_resourceManager)
	{
		_resourceManager = new ResourceManager();
		_resourceManager->init();
	}
	return _resourceManager;
}

ResourceManager::ResourceManager()
{

}

bool ResourceManager::init()
{
	return true;
}


ResourceManager::~ResourceManager()
{

}

ResourceHandle* ResourceManager::getHandle( Resource* resource )
{
	ResourceHandle* handle = findHandle(resource);
	if (handle == nullptr)
	{
		handle = loadHandle(resource);
	}
	return handle;
}

ResourceHandle* ResourceManager::findHandle( Resource* resource )
{
	auto name = _resources.find(resource->_name);
	if (name == _resources.end())
	{
		return nullptr;
	}
	else
	{
		return name->second;
	}
}

ResourceHandle* ResourceManager::loadHandle( Resource* resource )
{
	Image image;
	image.initImageFile(resource->_name);

	ResourceHandle* resourceHandle = new Texture(*resource);
	((Texture*) resourceHandle)->initImage(&image);

	return resourceHandle;
}

NS_SIT_END