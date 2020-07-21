
#ifndef _COMMON_H
#define _COMMON_H

#include <arpa/inet.h>

#include <sys/ioctl.h>

#include <stdarg.h>

#include <fcntl.h>

#include <fcntl.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <errno.h>

#include <malloc.h>

#include <netinet/in.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netdb.h>

#include <stdio.h>

#include <unistd.h>

#define ERR        			0xFFFF
#define SUCCESS     		0
#define BUFFERSIZE 			96
#define TFTPSERVER 			0
#define FTPSERVER  			1
#define SYS_VERSION         0
#define APP_VERSION         1
#define TFTP_READ_FILE      0
#define TFTP_WRITE_FILE     1

#define DEBUG_MSG logm_debug 


#endif

