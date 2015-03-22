#include <Windows.h>
#include <stdio.h>
#include "Macros.h"


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