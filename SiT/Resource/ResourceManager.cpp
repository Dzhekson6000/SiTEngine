#include "ResourceManager.h"

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
	ResourceHandle* resourceHandle = new ResourceHandle(*resource);

	int width, height;
	unsigned char* buffer = SOIL_load_image(resource->_name.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	resourceHandle->setWidth(width);
	resourceHandle->setHeight(height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, resourceHandle->getTextureId());
	glBindTexture(GL_TEXTURE_2D, *(resourceHandle->getTextureId()));

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);

	return resourceHandle;
}

NS_SIT_END