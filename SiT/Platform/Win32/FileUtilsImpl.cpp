#include "FileUtilsImpl.h"

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
	size_t size = 0;

	std::string fullPath = filename;//FileUtils::getInstance()->getPathFilename(filename);

	WCHAR wszBuf[512] = {0};
	MultiByteToWideChar(CP_UTF8, 0, fullPath.c_str(), -1, wszBuf, sizeof(wszBuf)/sizeof(wszBuf[0]));

	HANDLE fileHandle = ::CreateFileW(wszBuf, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, nullptr);
	if(fileHandle == INVALID_HANDLE_VALUE)
	{
		return Data::Null;
	}

	size = ::GetFileSize(fileHandle, nullptr);

	buffer = (unsigned char*) malloc(size);

	DWORD sizeRead = 0;
	BOOL successed = FALSE;
	successed = ::ReadFile(fileHandle, buffer, size, &sizeRead, nullptr);
	::CloseHandle(fileHandle);

	if (!successed)
	{
		if (buffer)
		{
			free(buffer);
			buffer = nullptr;
		}    
	}

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

NS_SIT_END