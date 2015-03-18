#ifndef REF_H_
#define REF_H_

#include "Macros.h"

NS_SIT_BEGIN

class SIT_DLL Ref
{
public:
	void retain();
	void release();
	Ref* autorelease();
	unsigned int getReferenceCount() const;
protected:
	Ref();
	unsigned int _referenceCount;
public:
	virtual ~Ref();
};

NS_SIT_END

#endif// REF_H_