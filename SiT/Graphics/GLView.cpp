#include "GLView.h"

NS_SIT_BEGIN

GLView::GLView() :_isFullScreen(false), _viewName("")
{
}

const Size& GLView::getResolutionSize() const
{
	return _resolutionSize;
}

NS_SIT_END