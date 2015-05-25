#include "FileUtils.h"

NS_SIT_BEGIN

FileUtils * FileUtils::_fileUtils = nullptr;

void FileUtils::destroyInstance()
{
	delete _fileUtils;
	_fileUtils = nullptr;
}

FileUtils::FileUtils():_defaultResRootPath("")
{
}

bool FileUtils::init()
{
	return true;
}

Data FileUtils::getData( const std::string& filename )
{
	return Data::Null;
}

Data FileUtils::getDataFromFile( const std::string& filename )
{
	return getData(filename);
}

std::string FileUtils::getPathFilename( const std::string &filename )
{
	if (filename.empty())
	{
		return "";
	}

	if (isAbsolutePath(filename))
	{
		return filename;
	}

	return filename;

}

long FileUtils::getFileSize( const std::string &filepath )
{
	return NULL;
}

bool FileUtils::isAbsolutePath( const std::string& path ) const
{
	return (path[0] == '/');
}

bool FileUtils::createDirectory( const std::string& dirPath )
{
	return false;
}

bool FileUtils::removeDirectory( const std::string& dirPath )
{
	return false;
}

bool FileUtils::removeFile( const std::string &filepath )
{
	return false;
}

bool FileUtils::renameFile( const std::string &path, const std::string &oldname, const std::string &name )
{
	return false;
}

NS_SIT_END