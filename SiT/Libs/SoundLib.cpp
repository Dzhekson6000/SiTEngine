#include "SoundLib.h"
#include "LibOpenAL/LibOpenAL.h"

NS_SIT_BEGIN

SoundLib* SoundLib::_soundLib = nullptr;

SoundLib* SoundLib::createLib(TypeSoundLib type)
{
	if (_soundLib) delete _soundLib;

	switch (type)
	{
	case SoundLib::TypeSoundLib::OpenAL:
		_soundLib = new LibOpenAL();
		_soundLib->init();
		break;
	default:
		_soundLib = new SoundLib();
		_soundLib->init();
		break;
	}

	return _soundLib;
}

SoundLib* SoundLib::getInstance()
{
	if (!_soundLib)
	{
		_soundLib = createLib(DEFAULT_SOUND_LIB);
	}

	return _soundLib;
}

SoundLib::SoundLib()
{

}

bool SoundLib::init()
{
	return true;
}

void SoundLib::destroy()
{
}

SoundObject* SoundLib::createSoundObject(TypeData typeFile, std::string name, Data data)
{
	return nullptr;
}

int SoundLib::getNumObject(std::string name)
{
	return NULL;
}

void SoundLib::deleteObject(std::string name)
{

}

NS_SIT_END