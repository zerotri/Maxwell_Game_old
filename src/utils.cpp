#include "utils.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <System.h>
extern System* LogSys;
void Log(char* format,...)
{
	if(LogSys==NULL) return;
	char _strbuf[256];
	///create va_list and load all arguments
	va_list ap;
	va_start(ap, format);
	vsprintf(_strbuf,format, ap); /// Call vprintf
	va_end(ap); /// Cleanup the va_list
	LogSys->Log("%s\n",_strbuf);
}
