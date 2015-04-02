#include "AppDelegate.h"
#include <jni.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

void android_app_init () {
	AppDelegate *appDelegate = new AppDelegate();
}