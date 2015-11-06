#include <stdio.h>
#include "Macros.h"


#if TARGET_PLATFORM == PLATFORM_WIN32
#include <Windows.h>

void log(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	char buf[MAX_LOG_LENGTH];
	vsnprintf_s(buf, MAX_LOG_LENGTH-3, format, args);
	strcat_s(buf, "\n");
	WCHAR wszBuf[MAX_LOG_LENGTH] = {0};
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, wszBuf, sizeof(wszBuf));
	OutputDebugString(wszBuf);
	va_end(args);
}
#elif TARGET_PLATFORM == PLATFORM_LINUX
#include <syslog.h>
#include <stdarg.h>
#include <cstring>

void log(const char * format, ...)
{
        va_list args;
        va_start(args,format);
        char buf[MAX_LOG_LENGTH];   
        vsnprintf(buf, MAX_LOG_LENGTH-3, format, args);
	strcat(buf, "\n");
	openlog("SiTDebug",LOG_PERROR | LOG_PID,LOG_USER);
        syslog(LOG_DEBUG,buf);
        closelog();
        va_end(args);
}
#endif


