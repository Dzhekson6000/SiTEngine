#ifndef MACROSPLATFORM_H_
#define MACROSPLATFORM_H_

#define PLATFORM_UNKNOWN			0
#define PLATFORM_IOS				1
#define PLATFORM_ANDROID			2
#define PLATFORM_WP8				3
#define PLATFORM_WIN32				4
#define PLATFORM_LINUX				5
#define PLATFORM_MAC				6

#define TARGET_PLATFORM				PLATFORM_UNKNOWN

#if defined(TARGET_OS_IPHONE)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_IOS
#endif

#if defined(ANDROID)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_ANDROID
#endif

#if defined(WP8)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM			PLATFORM_WP8
#endif

#if defined(_WIN32) && defined(_WINDOWS)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_WIN32
#endif

#if defined(LINUX) && !defined(__APPLE__)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_LINUX
#endif

#if (defined __linux__)
#undef TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_LINUX
#endif

#if defined(TARGET_OS_MAC) || defined(__APPLE__)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM         PLATFORM_MAC
#endif

#endif // MACROSPLATFORM_H_