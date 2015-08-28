#ifndef DATA_H_
#define DATA_H_

#include "Macros.h"
#include <string>

NS_SIT_BEGIN

class SIT_DLL Data
{
private:
	unsigned char*	_bytes;
	size_t			_size;
public:
	static const Data Null;

	Data();
	Data(const Data& other);
	Data(unsigned char* bytes, const size_t size);
	~Data();

	void fastSet(unsigned char* bytes, const size_t size);

	size_t getSize() const;
	unsigned char* getBytes() const;

	void clear();
	bool isNull() const;

	Data& operator= (const Data& other);
};

NS_SIT_END

#endif // DATA_H_