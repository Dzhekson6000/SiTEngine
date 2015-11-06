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

extern SIT_DLL const char * positionColorV;
extern SIT_DLL const char * positionColorF;

extern SIT_DLL const char * positionColorTextureV;
extern SIT_DLL const char * positionColorTextureF;

extern SIT_DLL const char * positionTextureV;
extern SIT_DLL const char * positionTextureF;

NS_SIT_END

#endif // SHADERS_H_