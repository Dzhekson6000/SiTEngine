#ifndef SOUND_OBJECT_H_
#define SOUND_OBJECT_H_

#include "Macros.h"
#include <string>
#include "Geometry/Geometry.h"

NS_SIT_BEGIN

class SIT_DLL SoundObject
{
public:
	enum class Format
	{
		MONO_IMA4,
		MONO8,
		MONO16,
		STEREO_IMA4,
		STEREO8,
		STEREO16,
		QUAD16,
		_51CHN16,
		_61CHN16,
		_71CHN16,
		UNKOWN
	};
private:
	
protected:
	std::string		_name;
	Format			_format;
	unsigned int	_frequency;
	bool			_streamed;
public:
					SoundObject(std::string	name);
	virtual			~SoundObject();

	std::string		getName();
	Format			getFormat();
	unsigned int	getFrequency();

	void			setName(std::string	name);
	void			setFormat(Format format);
	void			setFrequency(unsigned int frequency);

	virtual void play();
	virtual void stop();
	virtual void close();
	virtual void move(Point point);
	virtual void move(float x, float y, float z);
	virtual void setLooping(bool loop);
	virtual bool isStreamed();
	virtual void update();

};

NS_SIT_END

#endif// SOUND_OBJECT_H_