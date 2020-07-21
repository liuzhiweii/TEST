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
#include "utimer.h"
#include <stdio.h>
#include "logm.h"

#define TIMER_PORT 9876

int timer_socket = -1;

int init_timer(void)
{
	int sock;
	struct sockaddr_in  addr;
	int level;
	int name;
	int value;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(TIMER_PORT);

    if (0 > connect(sock, (struct sockaddr *)&addr, sizeof(addr)))
    {
        logm_debug("connect error! errno\r\n");
        perror("");
        return -1;
    }

    level = IPPROTO_TCP;
    name = TCP_NODELAY;
    value = 1;
    setsockopt(sock, level, name, &value, sizeof(int));

    timer_socket = sock;
    return sock;
}

int set_timer(int timer_id, unsigned long secs, unsigned long us, int flag)
{
	struct set_timer_t set_timer;
	int ret;

	if((timer_id <=0) || (timer_id > 63))
	{
		logm_debug("timer_id incorrect!\n");
		return -1;
	}

	set_timer.action = SET_TIMER;
	set_timer.flag = flag;
	set_timer.timer_id = timer_id;
	set_timer.secs = secs;
	set_timer.u_secs = us;

    ret = write(timer_socket, &set_timer, sizeof(struct set_timer_t));
    if (ret == sizeof(set_timer_t))
    {
    	return 0;
    }
    else
    {
    	return -1;
    }
}


int del_timer(int timer_id)
{
	struct set_timer_t set_timer;
	int ret;

	if((timer_id <=0) || (timer_id > 63))
	{
		logm_debug("timer_id incorrect!\n");
		return -1;
	}

	set_timer.action = DEL_TIMER;
	set_timer.timer_id = timer_id;

    ret = write(timer_socket, &set_timer, sizeof(struct set_timer_t));
    if (ret == sizeof(set_timer_t))
    {
    	return 0;
    }
    else
    {
    	return -1;
    }
}

void close_timer(void)
{
	close(timer_socket);
	return;
}
