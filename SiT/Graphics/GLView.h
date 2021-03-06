#ifndef GLVIEW_H_
#define GLVIEW_H_
#include "Base/Ref.h"
#include <string>
#include "Types/Types.h"

NS_SIT_BEGIN

class SIT_DLL GLView: public Ref
{
protected:
	std::string		_viewName;
	int				_width;
	int				_height;
	bool			_isFullScreen;
	Size			_resolutionSize;
public:
					GLView();
	virtual void	pollEvents(){};
	virtual void	setFullScreen(bool isFullScreen){_isFullScreen = isFullScreen;};
	virtual bool	getFullScreen(){return _isFullScreen;}

	virtual const	Size& getResolutionSize() const;

	virtual void	clear(Color color){};
	virtual bool	isViewClose(){ return true; };
};

NS_SIT_END

#endif  // GLVIEW_H_