#ifndef SOUND_LIB_H_
#define SOUND_LIB_H_

#include "Sound\SoundObject.h"
#include "Resource\Data.h"

NS_SIT_BEGIN

class SIT_DLL SoundLib
{
public:
	enum class TypeData
	{
		WAV,
		OGG
	};
private:

	#define DEFAULT_SOUND_LIB TypeSoundLib::OpenAL

	enum class TypeSoundLib
	{
		OpenAL,
		Win32
	};
	static SoundLib*	_soundLib;
	TypeSoundLib		_type;
protected:
						SoundLib();
	virtual bool		init();
	virtual void		destroy();
public:
	static SoundLib*	createLib(TypeSoundLib type);
	static SoundLib*	getInstance();

	virtual SoundObject*createSoundObject(TypeData typeFile, std::string name, Data data);
	virtual int			getNumObject(std::string name);
	virtual void		deleteObject(std::string name);
};

NS_SIT_END

#endif// SOUND_LIB_H_