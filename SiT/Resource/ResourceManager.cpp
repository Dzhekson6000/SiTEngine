#include "ResourceManager.h"
#include "Libs/GraphicsLib.h"


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
	std::string ext = getExt(resource->_name);
	if (ext.empty())return nullptr;
	for (unsigned int i = 0; i < ext.size(); i++)
	{
		ext[i] = tolower(ext[i]);
	}
	
	ResourceHandle::Type type;

	if (!strcmp(ext.c_str(), "png") || !strcmp(ext.c_str(), "jpg"))
	{
		type = ResourceHandle::Type::TEXTURE;
	}
	else if (!strcmp(ext.c_str(), "ttf"))
	{
		type = ResourceHandle::Type::FONT;
	}

	return loadHandleFromType(resource, type);
}

ResourceHandle* ResourceManager::loadHandleFromType(Resource* resource, ResourceHandle::Type type)
{
	ResourceHandle* resourceHandle = nullptr;

	switch (type)
	{
	case ResourceHandle::Type::TEXTURE:
	{
		Image image;
		image.initImageFile(resource->_name);

		resourceHandle = GRAPHICS_LIB()->createNewTexture(*resource);
		((Texture*)resourceHandle)->initImage(&image);

		break;
	}
	case ResourceHandle::Type::FONT:
	{
		resourceHandle = new FontAtlas(*resource);

		break;
	}
	}

	_resources.insert(std::make_pair(resource->_name, resourceHandle));
	return resourceHandle;
}

std::string ResourceManager::getExt(const std::string& str) {
	size_t pos = str.rfind('.');
	if (pos <= 0) return "";
	return str.substr(pos + 1, std::string::npos);
}

NS_SIT_END