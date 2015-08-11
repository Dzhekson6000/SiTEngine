#define _CRT_SECURE_NO_WARNINGS
#ifndef LIB_OPENAL_H_
#define LIB_OPENAL_H_

#include <map>
#include "Libs/SoundLib.h"
#include "SoundObjectOpenAL.h"

NS_SIT_BEGIN

class SIT_DLL LibOpenAL: public SoundLib
{
public:
	struct RIFF_Header {
		char chunkID[4];
		long chunkSize;
		char format[4];
	};

	struct WAVE_Format {
		char subChunkID[4];
		long subChunkSize;
		short audioFormat;
		short numChannels;
		long sampleRate;
		long byteRate;
		short blockAlign;
		short bitsPerSample;
	};

	struct WAVE_Data {
		char subChunkID[4];
		long subChunk2Size;
	};
private:

	ALCdevice*	_device;
	ALCcontext*	_context;
	
	std::map<std::string, ALuint> _sounds;

	bool				init();
	void				destroy();
	ALboolean			checkALCError();
	ALboolean			checkALError();

	SoundObject*		createSoundObjectFromWavData(const std::string &filePath, Data data);
	bool				copyDateToStruct(Data* data, WAVE_Format* waveFormat, RIFF_Header* riffHeader, WAVE_Data* waveData, unsigned char** dataWav);
	SoundObject::Format getFormatFromInfo(short numChannels, short bitsPerSample);
	ALenum				getFormatOpenAlFromInfo(short numChannels, short bitsPerSample);
protected:

public:
				LibOpenAL();

	SoundObject*		createSoundObject(TypeData typeData, std::string name, Data data);
	void				deleteObject(std::string name);
};

NS_SIT_END

#endif// LIB_OPENAL_H_