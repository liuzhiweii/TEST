#include <stdio.h>
#include <unistd.h>

#include "logm.h"

int main(int argc, char *argv[])
{
	init_logm("comm");

    while(1)
    {
    	sleep(1);
    	print_cur_level();
    	logm(M_DEBUG, "hellow world\n");
    }
	
}