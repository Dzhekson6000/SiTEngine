#include "Size.h"

NS_SIT_BEGIN

const Size Size::ZERO = Size(0, 0);

bool Size::operator==( const Size& size ) const
{
	if(this->_width == size._width && this->_height == size._height)
	{
		return true;
	}
	return false;
}

NS_SIT_END
