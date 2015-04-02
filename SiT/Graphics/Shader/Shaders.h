#ifndef SHADERS_H_
#define SHADERS_H_

#include "Macros.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "GL/glew.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif



NS_SIT_BEGIN

extern SIT_DLL const GLchar * positionColorV;
extern SIT_DLL const GLchar * positionColorF;

extern SIT_DLL const GLchar * positionTextureV;
extern SIT_DLL const GLchar * positionTextureF;

NS_SIT_END

#endif // SHADERS_H_