#include "SoundManager.h"

NS_SIT_BEGIN

SoundManager* SoundManager::_soundManager = nullptr;

SoundManager* SoundManager::getInstance()
{
	if (!_soundManager)
	{
		_soundManager = new SoundManager();
		_soundManager->init();
	}

	return _soundManager;
}

SoundManager::SoundManager()
{

}

bool SoundManager::init()
{
	return true;
}

SoundObject* SoundManager::createSoundObject(std::string path)
{
	SoundObject* ret = nullptr;
	Data data = FileUtils::getInstance()->getDataFromFile(path);
	
	std::string ext = extractFileExt(path).data();
	if (ext == "WAV")
	{
		ret = SOUND_LIB()->createSoundObject(SoundLib::TypeData::WAV, path, data);
	}
	
	_buffers.push_back(ret);

	return ret;
}

void SoundManager::deleteSoundObject(SoundObject* soundObject)
{
	std::string name = soundObject->getName();
	unsigned int n = 0;
	for (unsigned int i = 0; i < _buffers.size(); i++)
	{
		if (_buffers.at(i) == soundObject)
		{
			delete _buffers.at(i);
			_buffers.erase(_buffers.begin()+i);
			i--;
			break;
		}
		else if(_buffers.at(i)->getName() == soundObject->getName())
			n++;
	}
	if (n == 0)
	{
		SOUND_LIB()->deleteObject(name);
	}
}

std::string SoundManager::extractFileExt(const std::string &filePath)
{
	if (filePath.size() == 0) return "";

	int i = filePath.size();
	std::string buf;
	while ((filePath[i] != '.') && (i > 0))
	{
		buf = filePath[i--] + buf;
	}
	std::transform(buf.begin(), buf.end(), buf.begin(), toupper);
	return buf;
}


NS_SIT_END