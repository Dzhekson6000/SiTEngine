#include "Platform/MacrosPlatform.h"

#define NS_SIT_BEGIN                     namespace SiT {
#define NS_SIT_END                       }
#define USING_NS_SIT                     using namespace SiT;

//#if defined(_USRDLL)
//    #define SIT_DLL     __declspec(dllexport)
//#else         /* use a DLL library */
//    #define SIT_DLL     __declspec(dllimport)
//#endif

#define SIT_DLL

void log(const char * format, ...);

#if TARGET_PLATFORM == PLATFORM_WIN32
#define LOG(format, ...) log(format, ##__VA_ARGS__);
#endif

#if TARGET_PLATFORM == PLATFORM_ANDROID
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "main"
#define  LOG(format, ...) LOGD(format, ##__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#endif


#define MAX_LOG_LENGTH 1000

#define CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)