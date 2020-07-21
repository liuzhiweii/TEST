#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>   
#include <sys/types.h>
#include <sys/stat.h>
#include "abn.h"
#include <errno.h> 
#include <syslog.h>



void record_abn(char* file_name, int line, const char *fmt, ...)
{
	va_list args;
	char printbuffer[1024]={0};
	int head_len;
	int len = 0;

	head_len = sprintf(printbuffer, "[abn] %s line: %d ", file_name, line);

	va_start(args, fmt);
	len = vsnprintf(&printbuffer[head_len],(1024 - head_len), fmt, args);
	va_end(args);

	syslog(LOG_DEBUG|LOG_USER, printbuffer);

	return;
}

void record_log(char* file_name, int line, const char *fmt, ...)
{
	va_list args;
	char printbuffer[1024]={0};
	int head_len;
	int len = 0;


	head_len = sprintf(printbuffer, "##log %s line: %d ", file_name, line);

	va_start(args, fmt);
	len = vsnprintf(&printbuffer[head_len],(1024 - head_len), fmt, args);
	va_end(args);

	syslog(LOG_DEBUG|LOG_USER, printbuffer);

	return;
}


