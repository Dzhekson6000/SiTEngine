#include "SoundObject.h"
#include "SoundManager.h"

NS_SIT_BEGIN

SoundObject::SoundObject(std::string name) :_name(name), _frequency(0), _format(SoundObject::Format::UNKOWN)
{

}

SoundObject::~SoundObject()
{
	
}

std::string SoundObject::getName()
{
	return _name;
}

SoundObject::Format SoundObject::getFormat()
{
	return _format;
}

unsigned int SoundObject::getFrequency()
{
	return _frequency;
}

void SoundObject::setName(std::string name)
{
	_name = name;
}

void SoundObject::setFormat(Format format)
{
	_format = format;
}

void SoundObject::setFrequency(unsigned int frequency)
{
	_frequency = frequency;
}

void SoundObject::play()
{

}
void SoundObject::stop()
{

}

void SoundObject::close()
{
	SoundManager::getInstance()->deleteSoundObject(this);
}

void SoundObject::move(Point point)
{
	move(point.getX(),point.getY(), point.getZ());
}

void SoundObject::move(float x, float y, float z)
{

}

void SoundObject::setLooping(bool loop)
{

}

bool SoundObject::isStreamed()
{
	return _streamed;
}

void SoundObject::update()
{

}

NS_SIT_END