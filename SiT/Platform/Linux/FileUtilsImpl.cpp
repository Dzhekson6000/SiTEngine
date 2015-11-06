#include "FileUtilsImpl.h"
#include <stdio.h>
#include <unistd.h>

NS_SIT_BEGIN

FileUtilsImpl::FileUtilsImpl()
{
}

FileUtils* FileUtils::getInstance()
{
	if(_fileUtils == nullptr)
	{
		_fileUtils = new FileUtilsImpl();
		if(!_fileUtils->init())
		{
			delete _fileUtils;
			_fileUtils = nullptr;
			LOG("ERROR: Could not init FileUtilsImpl");
		}
	}
	return _fileUtils;
}

bool FileUtilsImpl::init()
{
	return FileUtils::init();
}

Data FileUtilsImpl::getData(const std::string& filename)
{
	if (filename.empty())
	{
		return Data::Null;
	}

	unsigned char *buffer = nullptr;
	off64_t size = 0;

	std::string fullPath = filename;//FileUtils::getInstance()->getPathFilename(filename);

	FILE *fileHandle = fopen(filename.c_str(), "r");
        if(fileHandle == 0)
	{
		return Data::Null;
	}
        
        size = getfilesize(fileHandle);
        
        buffer = (unsigned char*) malloc(size);
        fread(buffer,size,1,fileHandle);
        
        fclose(fileHandle);
        
	Data ret;
	ret.fastSet(buffer, size);

	return ret;
}

bool FileUtilsImpl::isAbsolutePath(const std::string& strPath) const
{
	return (   strPath.length() > 2 
		&& ( (strPath[0] >= 'a' && strPath[0] <= 'z') || (strPath[0] >= 'A' && strPath[0] <= 'Z') )
		&& strPath[1] == ':');
}

off64_t FileUtilsImpl::getfilesize(FILE *f)
{
    off64_t result = -1;
    off64_t p=ftello64(f);

    if(fseeko64(f, 0, SEEK_END)==0)
    {
        result=ftello64(f);
        fseeko64(f, p, SEEK_SET);
    }
    return result;
}

NS_SIT_END