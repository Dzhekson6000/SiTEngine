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

	/*FILE *file;
	unsigned char header[54];

	//not crossplatform
	fopen_s(&file, resource->_name.c_str(), "rb");

	if ( fread(header, 1, 54, file)!=54 ){
		//printf("Not a correct BMP file\n");
		return nullptr;
	}

	if ( header[0]!='B' || header[1]!='M' ){
		//printf("Not a correct BMP file\n");
		return nullptr;
	}
*/

	unsigned int size;
	int width, height;
	unsigned char* buffer;

	

	/*size		= *(int*)&(header[0x22]);
	width       = *(int*)&(header[0x12]);
	height      = *(int*)&(header[0x16]);

	if (size == 0) size = width*height*3;
	resourceHandle->setWidth(width);
	resourceHandle->setHeight(height);
	
	//buffer = (unsigned char *)malloc( size );
	fread(buffer, 1, size, file);
	fclose(file);*/

	buffer = SOIL_load_image(resource->_name.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	/*for (unsigned int i = 0; i < unsigned int(size); i += 3)
	{
		unsigned char temp = buffer[i];
		buffer[i] = buffer[i + 2];
		buffer[i + 2] = temp;
	}*/

	resourceHandle->setBuffer(buffer);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, resourceHandle->getTextureId());
	glBindTexture(GL_TEXTURE_2D, *(resourceHandle->getTextureId()));

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, resourceHandle->getBuffer());

	return resourceHandle;
}

NS_SIT_END