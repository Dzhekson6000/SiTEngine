#ifndef  SIT_H_
#define  SIT_H_

#include "Macros.h"
#include "Director.h"
#include "Base/Scene.h"
#include "Graphics/2d/Sprite.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
	#include "Platform/Win32/Application.h"

	#pragma comment (lib, "glew32.lib")
	#pragma comment (lib, "glfw3.lib")
	#pragma comment (lib, "glfw3dll.lib")
	#pragma comment (lib, "opengl32.lib")
	#pragma comment (lib, "libjpeg.lib")
	#pragma comment (lib, "libpng.lib")
	#pragma comment (lib, "libzlib.lib")
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "Platform/Android/Application.h"
#endif

#endif // SIT_H_