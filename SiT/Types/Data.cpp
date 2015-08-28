#include "Data.h"

NS_SIT_BEGIN

const Data Data::Null;

Data::Data():_bytes(nullptr),_size(0)
{

}

Data::Data( unsigned char* bytes, const size_t size )
{
	fastSet(bytes,size);
}

Data::Data( const Data& other )
{
	fastSet(other.getBytes(),other.getSize() );
}

Data::~Data()
{
	clear();
}

void Data::fastSet( unsigned char* bytes, const size_t size )
{
	clear();
	_size = size;
	_bytes = (unsigned char*)malloc(sizeof(unsigned char) * _size);
	memcpy(_bytes, bytes, _size);
}

size_t Data::getSize() const
{
	return _size;
}

unsigned char* Data::getBytes() const
{
	return _bytes;
}

void Data::clear()
{
	if (!_bytes)free(_bytes);
	_bytes = nullptr;
	_size = 0;
}

bool Data::isNull() const
{
	return (_bytes == nullptr || _size == 0);
}

Data& Data::operator=( const Data& other )
{
	if (other.getSize() > 0)
	{
		fastSet(other.getBytes(), other.getSize());
	}
	return *this;
}

NS_SIT_END