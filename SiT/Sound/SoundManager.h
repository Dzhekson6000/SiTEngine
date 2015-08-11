#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include <vector>
#include <algorithm>

#include "Macros.h"
#include "SoundObject.h"
#include "Libs/SoundLib.h"
#include "Resource/FileUtils.h"

NS_SIT_BEGIN

class SIT_DLL SoundManager
{
private:
	static SoundManager* _soundManager;

	typedef std::vector<SoundObject*> TBuf;
	TBuf		_buffers;

	SoundManager();
	bool init();
	std::string extractFileExt(const std::string &filePath);
protected:

public:
	static SoundManager* getInstance();
	SoundObject* createSoundObject(std::string path);
	void deleteSoundObject(SoundObject* soundObject);
};

#define SOUND_MANADGER() SoundManager::getInstance()

NS_SIT_END

#endif// SOUND_MANAGER_H_