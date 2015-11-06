#ifndef FILEUTILSIMPL_H_
#define FILEUTILSIMPL_H_

#include "Macros.h"
#include "Resource/FileUtils.h"
#include <windows.h>

NS_SIT_BEGIN

class SIT_DLL FileUtilsImpl: public FileUtils
{
public:
					FileUtilsImpl();
	virtual bool	init();
	virtual Data	getData(const std::string& filename);
	bool			isAbsolutePath(const std::string& path) const;
};


NS_SIT_END

#endif