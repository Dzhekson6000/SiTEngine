#include "Macros.h"

#if TARGET_PLATFORM == PLATFORM_WIN32
#include "Platform/Win32/FileUtilsImpl.h"
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include "Platform/Android/FileUtilsImpl.h"
#endif