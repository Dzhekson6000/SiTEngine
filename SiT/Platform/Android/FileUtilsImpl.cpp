#include "FileUtilsImpl.h"
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#include <stdlib.h>
#include <stdio.h>

NS_SIT_BEGIN

AAssetManager* FileUtilsImpl::_assetManager = nullptr;

void FileUtilsImpl::setAssetManager(AAssetManager* assetManager) {
	if (nullptr == assetManager) {
		LOG("setassetmanager : received unexpected nullptr parameter");
		return;
	}

	FileUtilsImpl::_assetManager = assetManager;
}

AAssetManager* FileUtilsImpl::getAssetManager() {
	return FileUtilsImpl::_assetManager;
}

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
	_defaultResRootPath = "assets/";

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

	std::string fullPath = FileUtils::getInstance()->getPathFilename(filename);

	if (fullPath[0] != '/')
	{
		std::string relativePath = std::string();

		size_t position = fullPath.find("assets/");
		if (0 == position) {
			relativePath += fullPath.substr(strlen("assets/"));
		} else {
			relativePath += fullPath;
		}
		LOG("relative path = %s", relativePath.c_str());

		if (nullptr == FileUtilsImpl::_assetManager) {
			LOG("... FileUtilsAndroid::assetmanager is nullptr");
			return Data::Null;
		}

		AAsset* asset =
			AAssetManager_open(FileUtilsImpl::_assetManager,
			relativePath.c_str(),
			AASSET_MODE_UNKNOWN);
		if (nullptr == asset) {
			LOG("asset is nullptr");
			return Data::Null;
		}

		off_t fileSize = AAsset_getLength(asset);

		buffer = (unsigned char*) malloc(fileSize);

		int bytesread = AAsset_read(asset, (void*)buffer, fileSize);
		size = bytesread;

		AAsset_close(asset);
	}
	else
	{
		do
		{
			const char* mode = nullptr;
			mode = "rb";

			FILE *fp = fopen(fullPath.c_str(), mode);
			if(!fp)break;

			long fileSize;
			fseek(fp,0,SEEK_END);
			fileSize = ftell(fp);
			fseek(fp,0,SEEK_SET);
			buffer = (unsigned char*) malloc(fileSize);
			fileSize = fread(buffer,sizeof(unsigned char), fileSize,fp);
			fclose(fp);

			size = fileSize;
		} while (0);
	}

	Data ret;
	if (buffer == nullptr || size == 0)
	{
		std::string msg = "Get data from file(";
		msg.append(filename).append(") failed!");
		LOG("%s", msg.c_str());
	}
	else
	{
		ret.fastSet(buffer, size);
	}

	return ret;
}

bool FileUtilsImpl::isAbsolutePath( const std::string& path ) const
{
	return (path[0] == '/' || path.find(_defaultResRootPath) == 0);
}

NS_SIT_END