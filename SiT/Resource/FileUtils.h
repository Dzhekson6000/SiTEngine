#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include "Macros.h"
#include "Types/Data.h"
#include <string>

NS_SIT_BEGIN

class SIT_DLL FileUtils
{
protected:
	FileUtils();
	virtual bool init();
	static FileUtils* _fileUtils;
	std::string _defaultResRootPath;
public:
	static FileUtils* getInstance();
	static void destroyInstance();

	virtual Data getData(const std::string& filename);
	virtual Data getDataFromFile(const std::string& filename);

	virtual std::string getPathFilename(const std::string &filename);
	virtual long getFileSize(const std::string &filepath);

	virtual bool isAbsolutePath(const std::string& path) const;

	virtual bool createDirectory(const std::string& dirPath);
	virtual bool removeDirectory(const std::string& dirPath);
	virtual bool removeFile(const std::string &filepath);
	virtual bool renameFile(const std::string &path, const std::string &oldname, const std::string &name);
};

NS_SIT_END

#endif // FILEUTILS_H_