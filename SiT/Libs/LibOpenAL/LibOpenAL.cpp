#include "LibOpenAL.h"

NS_SIT_BEGIN


LibOpenAL::LibOpenAL()
{

}

bool LibOpenAL::init()
{
	ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
	ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
	ALfloat listenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

	_device = alcOpenDevice(NULL);
	if (!_device)
	{
		LOG("Default sound device not present");
		return false;
	}

	_context = alcCreateContext(_device, NULL);
	if (!checkALCError()) return false;

	alcMakeContextCurrent(_context);


	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	return true;
}

void LibOpenAL::destroy()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(_context);
	alcCloseDevice(_device);
}

ALboolean LibOpenAL::checkALCError()
{
	ALenum ErrCode;
	std::string Err = "ALC error: ";
	if ((ErrCode = alcGetError(_device)) != ALC_NO_ERROR)
	{
		Err += (char *)alcGetString(_device, ErrCode);
		LOG(Err.data());
		return AL_FALSE;
	}
	return AL_TRUE;
}

ALboolean LibOpenAL::checkALError()
{
	ALenum ErrCode;
	std::string Err = "OpenAL error: ";
	if ((ErrCode = alGetError()) != AL_NO_ERROR)
	{
		Err += (char *)alGetString(ErrCode);
		LOG(Err.data());
		return AL_FALSE;
	}
	return AL_TRUE;
}

SoundObject* LibOpenAL::createSoundObject(TypeData typeData, std::string name, Data data)
{
	switch (typeData)
	{
	case SiT::SoundLib::TypeData::WAV:
		return createSoundObjectFromWavData(name, data);
	case SiT::SoundLib::TypeData::OGG:
		break;
	}
	return nullptr;
}

void LibOpenAL::deleteObject(std::string name)
{
	for (std::map<std::string, ALuint>::iterator i = _sounds.begin(); i != _sounds.end(); i++)
	{
		if (i->first == name)
		{
			alSourceStop(i->second);
			alDeleteBuffers(1, &i->second);
			_sounds.erase(i);
			break;
		}
	}
}

SoundObject* LibOpenAL::createSoundObjectFromWavData(const std::string &name, Data data)
{
	ALuint	bufId = 0;
	SoundObjectOpenAL* ret = new SoundObjectOpenAL(name);

	for (std::map<std::string, ALuint>::iterator i = _sounds.begin(); i != _sounds.end(); i++)
	{
		if (i->first == name)
		{
			bufId = i->second;
			break;
		}
	}

	if (!bufId)
	{
		alGenBuffers(1, &bufId);
		if (!checkALError()) return false;

		ALenum		format;
		SoundObject::Format formatObject;
		ALsizei		size;
		ALsizei		frequency;
		WAVE_Format waveFormat;
		RIFF_Header riffHeader;
		WAVE_Data waveData;
		unsigned char* dataWav;

		if (!copyDateToStruct(&data, &waveFormat, &riffHeader, &waveData, &dataWav))return nullptr;

		size = waveData.subChunk2Size;
		frequency = waveFormat.sampleRate;

		format = getFormatOpenAlFromInfo(waveFormat.numChannels, waveFormat.bitsPerSample);
		formatObject = getFormatFromInfo(waveFormat.numChannels, waveFormat.bitsPerSample);

		alBufferData(bufId, format, (void*)dataWav, size, frequency);
		if (!checkALError()) return nullptr;


		ret->setFrequency(frequency);
		ret->setFormat(formatObject);

		_sounds[name] = bufId;

		delete[] dataWav;
	}


	ret->setName(name);

	alSourcei(ret->_sourceId, AL_BUFFER, bufId);
	return ret;
}

bool LibOpenAL::copyDateToStruct(Data* data, WAVE_Format* waveFormat, RIFF_Header* riffHeader, WAVE_Data* waveData, unsigned char** dataWav)
{
	unsigned int offset = 0;
	memcpy(riffHeader, &data->getBytes()[offset], sizeof(RIFF_Header));
	offset += sizeof(RIFF_Header) / sizeof(unsigned char);

	if ((riffHeader->chunkID[0] != 'R' || riffHeader->chunkID[1] != 'I' || riffHeader->chunkID[2] != 'F' || riffHeader->chunkID[3] != 'F') ||
		(riffHeader->format[0] != 'W' || riffHeader->format[1] != 'A' || riffHeader->format[2] != 'V' || riffHeader->format[3] != 'E'))
	{
		LOG("Invalid RIFF or WAVE Header");
		return false;
	}

	memcpy(waveFormat, &data->getBytes()[offset], sizeof(WAVE_Format));
	offset += sizeof(WAVE_Format) / sizeof(unsigned char);

	if (waveFormat->subChunkID[0] != 'f' ||
		waveFormat->subChunkID[1] != 'm' ||
		waveFormat->subChunkID[2] != 't' ||
		waveFormat->subChunkID[3] != ' ')
	{
		LOG("Invalid Wave Format");
		return false;
	}

	offset += (waveFormat->subChunkSize - 16) / sizeof(unsigned char);

	memcpy(waveData, &data->getBytes()[offset], sizeof(WAVE_Data));
	offset += sizeof(WAVE_Data) / sizeof(unsigned char);

	if (waveData->subChunkID[0] != 'd' ||
		waveData->subChunkID[1] != 'a' ||
		waveData->subChunkID[2] != 't' ||
		waveData->subChunkID[3] != 'a')
	{
		LOG("Invalid data header");
		return false;
	}

	*dataWav = new unsigned char[waveData->subChunk2Size];
	memcpy(*dataWav, &data->getBytes()[offset], waveData->subChunk2Size);
	return true;
}

SoundObject::Format LibOpenAL::getFormatFromInfo(short numChannels, short bitsPerSample)
{
	switch (numChannels)
	{
	case 1:
		switch (bitsPerSample)
		{
		case 4:
			return SoundObject::Format::MONO_IMA4;
		case 8:
			return SoundObject::Format::MONO8;
		case 16:
			return SoundObject::Format::MONO16;
		}
	case 2:
		switch (bitsPerSample)
		{
		case 4:
			return SoundObject::Format::STEREO_IMA4;
		case 8:
			return SoundObject::Format::STEREO8;
		case 16:
			return SoundObject::Format::STEREO16;
		}
	case 4:
		switch (bitsPerSample)
		{
		case 16:
			return SoundObject::Format::QUAD16;
		}
	case 6:
		switch (bitsPerSample)
		{
		case 16:
			return SoundObject::Format::_51CHN16;
		}
	case 7:
		switch (bitsPerSample)
		{
		case 16:
			return SoundObject::Format::_61CHN16;
		}
	case 8:
		return SoundObject::Format::_71CHN16;
	}
	return SoundObject::Format::UNKOWN;
}

ALenum LibOpenAL::getFormatOpenAlFromInfo(short numChannels, short bitsPerSample)
{
	switch (numChannels)
	{
	case 1:
		switch (bitsPerSample)
		{
		case 4:
			return alGetEnumValue("AL_FORMAT_MONO_IMA4");
		case 8:
			return AL_FORMAT_MONO8;
		case 16:
			return AL_FORMAT_MONO16;
		}
	case 2:
		switch (bitsPerSample)
		{
		case 4:
			return alGetEnumValue("AL_FORMAT_STEREO_IMA4");
		case 8:
			return AL_FORMAT_STEREO8;
		case 16:
			return AL_FORMAT_STEREO16;
		}
	case 4:
		switch (bitsPerSample)
		{
		case 16:
			return alGetEnumValue("AL_FORMAT_QUAD16");
		}
	case 6:
		switch (bitsPerSample)
		{
		case 16:
			return alGetEnumValue("AL_FORMAT_51CHN16");
		}
	case 7:
		switch (bitsPerSample)
		{
		case 16:
			return alGetEnumValue("AL_FORMAT_61CHN16");
		}
	case 8:
		return alGetEnumValue("AL_FORMAT_71CHN16");
	}
	return 0;
}

NS_SIT_END