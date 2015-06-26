#ifndef FILEUTILSIMPL_H_
#define FILEUTILSIMPL_H_

#include "Macros.h"

#if TARGET_PLATFORM == PLATFORM_ANDROID


#include "Resource/FileUtils.h"
#include "jni.h"
#include "android/asset_manager.h"

NS_SIT_BEGIN

class SIT_DLL FileUtilsImpl: public FileUtils
{
private:
	static AAssetManager* _assetManager;
public:
	FileUtilsImpl();
	virtual bool init();
	virtual Data getData(const std::string& filename);

	static void setAssetManager(AAssetManager* assetManager);
	static AAssetManager* getAssetManager();

	bool isAbsolutePath(const std::string& path) const;

};


NS_SIT_END

#endif // TARGET_PLATFORM == PLATFORM_ANDROID

#endif//FILEUTILSIMPL_H_