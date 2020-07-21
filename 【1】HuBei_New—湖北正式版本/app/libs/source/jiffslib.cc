#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "jiffs.h"

void *jffies_addr = NULL;


int init_jiffs(void)
{
	unsigned long offset = 0xc03a4034;
    int fd;
    void *p;

    offset -= 0xc0000000;
    fd = open("/dev/mem", O_RDONLY);
    p = mmap(0, 0x10000, PROT_READ, MAP_SHARED, fd, (off_t)(offset - offset%0x10000));
    jffies_addr = p + (offset%0x10000);

    return 0;
}



