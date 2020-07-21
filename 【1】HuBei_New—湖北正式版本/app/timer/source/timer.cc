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
#include "utimer.h"
#include "logm.h"


struct timeout_arg_t
{
	struct event timeout_ev;
	int socket_fd;
	int flags;
    unsigned int timer_id;
};


struct read_arg_t
{
    struct event read_event;
    struct timeout_arg_t timer_array[64];
};


unsigned int cnt;

static void timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	struct timeout_arg_t *timeout_arg  = (struct timeout_arg_t *)arg;
    int ret;

    logm_debug("timeout occure!\n");
    logm_debug("cnt is %d \n", cnt++);
    logm_debug("event is %d, socket fd is %d, flags is %d \n", &(timeout_arg->timeout_ev), timeout_arg->socket_fd, timeout_arg->flags);
    logm_debug("tiemr id is %d \n", timeout_arg->timer_id);
    
    ret = write(timeout_arg->socket_fd, &(timeout_arg->timer_id), sizeof(unsigned int));
    if(ret < 0)
    {
        logm_debug("write error, close socket!\n");
        close(timeout_arg->socket_fd);
        event_del(&(timeout_arg->timeout_ev));
        memset(timeout_arg, 0, sizeof(struct timeout_arg_t));
        return;
    }
	
    if(timeout_arg->flags == 0)
    {
        logm_debug("not persist timer\n");
        memset(timeout_arg, 0, sizeof(struct timeout_arg_t));
    }

    return;
}


static void read_cb(evutil_socket_t fd, short what, void *arg)
{
    int len;
    int flags;
    struct set_timer_t cmd;
    struct event_base *base;
    struct timeval tv;
    struct timeout_arg_t *timeout_arg;
    struct read_arg_t *read_arg;

    logm_debug("enter read_cb \n");

    read_arg = (read_arg_t *)arg;

    len = read(fd, &cmd, sizeof(struct set_timer_t));
    logm_debug("read len is %d \n", len);
    if(len > 0)
    {
    	logm_debug("cmd action is %d, cmd flags is %d, cmd timer id is %d, cmd seconds is %d, cmd usecondes is %d \n",
    			    cmd.action, cmd.flag, cmd.timer_id, cmd.secs, cmd.u_secs);

    	if(cmd.action == SET_TIMER)
    	{
    		logm_debug("arg is %08X \n", arg);
    		base = event_get_base((event *)&(read_arg->read_event));
            if(cmd.timer_id > 63 || cmd.timer_id == 0) 
            {
                logm_debug("timer id %d incorrect\n", cmd.timer_id);
                return;
            }

            flags = (cmd.flag == TIMER_PERSIST) ? EV_PERSIST : 0;

            timeout_arg = &(read_arg->timer_array[cmd.timer_id]);      
            if(timeout_arg->timer_id != 0)
            {
                event_del(&(timeout_arg->timeout_ev));
                memset(timeout_arg, 0, sizeof(struct timeout_arg_t));
            }

            timeout_arg->socket_fd = fd;
            timeout_arg->flags = flags;
            timeout_arg->timer_id = cmd.timer_id;
            event_assign(&(timeout_arg->timeout_ev), base, -1, flags, timeout_cb, timeout_arg);
    		evutil_timerclear(&tv);
            tv.tv_sec = cmd.secs;
    		tv.tv_usec = cmd.u_secs;
    		event_add(&(timeout_arg->timeout_ev), &tv);
    	}
    	else
    	{
    		timeout_arg = &(read_arg->timer_array[cmd.timer_id]);   
            event_del(&(timeout_arg->timeout_ev));
            memset(timeout_arg, 0, sizeof(struct timeout_arg_t));
    	}
    }
    else
    {
    	logm_debug("socket closed \n");
        event_del(&(read_arg->read_event));
        free(arg);
    	close(fd);
    }
}




static void accept_conn_cb(struct evconnlistener *listener,
    evutil_socket_t fd, struct sockaddr *address, int socklen,
    void *ctx)
{
    struct event_base *base;
    struct read_arg_t *read_arg;
    struct read_cb_arg_t *read_cb_arg;


    base = evconnlistener_get_base(listener);
    
    read_arg = (struct read_arg_t *)malloc(sizeof(struct read_arg_t));
    if(NULL == read_arg)
    {
    	return;
    }

    memset(read_arg, 0, sizeof(struct read_arg_t));

    event_assign(&(read_arg->read_event), base, fd, EV_READ|EV_PERSIST, read_cb, (void *)read_arg); 
    event_add(&(read_arg->read_event), NULL);

    logm_debug("accept a new link\n");

    return;
}



int main (int argc, char *argv[])
{
	struct event_base *base;
    struct evconnlistener *listener;
    struct sockaddr_in sin;
    int port = 9876;

    init_logm("timer");

    if (argc > 1) 
    {
        port = atoi(argv[1]);
    }
    if (port<=0 || port>65535) 
    {
        logm_debug("port in correct!\n");
        return -1;
    }

    base = event_base_new();
    if (!base) 
    {
        logm_debug("Couldn't open event base");
        return -1;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(port);

    listener = evconnlistener_new_bind(base, accept_conn_cb, NULL,
        LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
        (struct sockaddr*)&sin, sizeof(sin));
    if (!listener) 
    {
        perror("Couldn't create listener");
        logm_err("Couldn't create listener");
        return -1;
    }
    //evconnlistener_set_error_cb(listener, accept_error_cb);

    event_base_dispatch(base);
    return 0;
}

