#ifndef MACROS_H_
#define MACROS_H_

#include "Platform/MacrosPlatform.h"
#include "Config.h"


#ifdef __cplusplus
#define NS_SIT_BEGIN                     namespace SiT {
#define NS_SIT_END                       }
#define USING_NS_SIT                     using namespace SiT;
#else
#define NS_SIT_BEGIN                     
#define NS_SIT_END                       
#define USING_NS_SIT                     
#endif


//#if defined(_USRDLL)
//    #define SIT_DLL     __declspec(dllexport)
//#else         /* use a DLL library */
//    #define SIT_DLL     __declspec(dllimport)
//#endif

#define SIT_DLL

#define LOG(format, ...)
void log(const char * format, ...);

#if TARGET_PLATFORM == PLATFORM_WIN32
#undef LOG
#define LOG(format, ...) log(format, ##__VA_ARGS__);
#elif TARGET_PLATFORM == PLATFORM_LINUX
#undef LOG
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

#define PI 3.14

#define ToRadian(x) ((x) * PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / PI)

#define CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create()\
{\
	__TYPE__ *ret = new __TYPE__();\
	if (ret && ret->init())\
	{\
		return (__TYPE__*)ret->autorelease();\
	}\
	else\
	{\
		delete ret;\
		return nullptr;\
	}\
}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#endif// MACROS_H_