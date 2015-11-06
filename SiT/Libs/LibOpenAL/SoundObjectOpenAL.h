#ifndef SOUND_OBJECT_OPENAL_H_
#define SOUND_OBJECT_OPENAL_H_

#include "AL/al.h"
#include "AL/alc.h"
#include "Sound/SoundObject.h"

NS_SIT_BEGIN

class SIT_DLL SoundObjectOpenAL : public SoundObject
{
private:
	enum class Format
	{
		MONO8,
		STEREO8,
		MONO16,
		STEREO16,
		UNKOWN
	};

	float			_velocity[3];
	float			_position[3];

	
protected:
	
public:

					SoundObjectOpenAL(std::string filePath);
	virtual			~SoundObjectOpenAL();

	unsigned int	getSourceId();
	void			setSourceId(unsigned int sourceId);

	unsigned int	_sourceId;

	void play();
	void stop();
	void close();
	void move(float x, float y, float z);
	void setLooping(bool loop);
	void update();
};

NS_SIT_END

#endif// SOUND_OBJECT_OPENAL_H_