#include "utils.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

void Log(char* format,...)
{
	char _strbuf[256];
	///create va_list and load all arguments
	va_list ap;
	va_start(ap, format);
	vsprintf(_strbuf,format, ap); /// Call vprintf
	va_end(ap); /// Cleanup the va_list
	printf("%s\n",_strbuf);
}
