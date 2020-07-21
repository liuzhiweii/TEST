#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include <event.h>  
#include <event2/listener.h>
#include <sys/time.h>
#include <time.h>
#include "utimer.h"
#include <stdio.h>

int sock;

void test_timer_last(unsigned int timer_id, unsigned int secs, unsigned int us)
{
	struct timeval start;
	struct timeval end;
	int ret_timerid;

	gettimeofday(&start, NULL);
	set_timer(timer_id, secs, us, 0);
    read(sock, &ret_timerid, sizeof(int));
    gettimeofday(&end, NULL);

    printf("timer id is %d \n", ret_timerid);
    printf("last time secondes is %ul \n", (end.tv_sec  - start.tv_sec));
    printf("last time us is %ul \n", (end.tv_usec  - start.tv_usec));
}

void test_timer_last_us(unsigned int timer_id, unsigned int us)
{
	struct timeval start;
	struct timeval end;
	int ret_timerid;

	gettimeofday(&start, NULL);
	set_timer_us(timer_id, us, 0);
    read(sock, &ret_timerid, sizeof(int));
    gettimeofday(&end, NULL);

    printf("timer id is %d \n", ret_timerid);
    printf("last time secondes is %ul \n", (end.tv_sec  - start.tv_sec));
    printf("last time us is %ul \n", (end.tv_usec  - start.tv_usec));
}

int main(int argc, char *argv[])
{
	sock = init_timer();

	test_timer_last(1, 0, 1000);
	test_timer_last(2, 0, 2000);
	test_timer_last(3, 0, 3000);
	test_timer_last(4, 0, 4000);
	test_timer_last(5, 0, 5000);
	test_timer_last(6, 0, 6000);
	test_timer_last(7, 0, 7000);
	test_timer_last(8, 0, 8000);
	test_timer_last(9, 0, 9000);
	test_timer_last(10, 0, 10000);
	test_timer_last(1, 0, 100000);
	test_timer_last(2, 0, 200000);
	test_timer_last(3, 0, 300000);
	test_timer_last(4, 1, 1000);
	test_timer_last(5, 2, 0);
	test_timer_last_us(6, 500);
    
    return 0;
}