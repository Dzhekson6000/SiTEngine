#ifndef  SIT_H_
#define  SIT_H_

#include "Macros.h"
#include "Director.h"
#include "Base/Scene.h"
#include "Graphics/2d/Sprite.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "Platform/Win32/Application.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "Platform/Android/Application.h"
#endif

#endif // SIT_H_