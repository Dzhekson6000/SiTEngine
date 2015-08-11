#include "SoundObjectOpenAL.h"

NS_SIT_BEGIN

SoundObjectOpenAL::SoundObjectOpenAL(std::string filePath)
:SoundObject(filePath), _sourceId(0)
{
	for (int i = 0; i < 3; i++)
	{
		_position[i] = _velocity[i] = 0.0f;
	}

	alGenSources(1, &_sourceId);
	setLooping(true);
}

SoundObjectOpenAL::~SoundObjectOpenAL()
{
	
}

unsigned int SoundObjectOpenAL::getSourceId()
{
	return NULL;
}

void SoundObjectOpenAL::setSourceId(unsigned int sourceId)
{
	_sourceId = sourceId;
}

void SoundObjectOpenAL::play()
{
	alSourcePlay(_sourceId);
}

void SoundObjectOpenAL::stop()
{
	alSourceStop(_sourceId);
}

void SoundObjectOpenAL::close()
{
	alSourceStop(_sourceId);
	alSourcei(_sourceId, AL_BUFFER, 0);
	if (alIsSource(_sourceId))alDeleteSources(1, &_sourceId);
	SoundObject::close();
}

void SoundObjectOpenAL::move(float x, float y, float z)
{
	_position[0] = x;
	_position[1] = y;
	_position[3] = z;
	alSourcefv(_sourceId, AL_POSITION, _position);
}

void SoundObjectOpenAL::setLooping(bool loop)
{
	alSourcei(_sourceId, AL_LOOPING, loop);
}

void SoundObjectOpenAL::update()
{

}

NS_SIT_END