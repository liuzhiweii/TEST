#include <stdio.h>
#include <unistd.h>

#include "logm.h"

int main(int argc, char *argv[])
{
	init_logm("cfg");
	int num = 0;

    while(1)
    {
    	logm(M_DEBUG, "fast write num %d\n", num++);
    }
	
}