#include <stdio.h>
#include <zmq.h>
#include <stdlib.h>
#include <json/json.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>   
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/time.h>
#include "logm.h"
#include "jiffs.h"


int default_log_level = 0;
int *p_cur_level = &default_log_level;

const char *fifo_name = "/log.fifo";
int write_fd = -1;
int timeflag = 0;


struct module_key_t module_keys[] = \
{
	{
		"cmm",
		1000
	},
	{
		"comm",
		1001
	},
	{
		"cfg",
		1002
	},
	{
		"instep",
		1003
	},
	{
		"timer",
		1004
	},
	{
		"vmm",
		1005
	},

	{
	    "vir_tag",
	    1006
	},
	/*
	{
	    "rcp",
	    1007
	},
	*/
	{
		"webmast",
		1007
	},
	{
	    "dispatch",
	    1008
	},
	
	{
		"scheduler",
		1009
	},
	
	{
		"psamserver",
		1010
	},
	
	{
		"uart",
		1011
	}
	
};

int create_fifo_fd(void)
{
	int fd;
	int temp;
	int file_ctrl;

	if(access(fifo_name, F_OK) < 0)   //file if exist ?
	{
		int ret;
		ret = mkfifo(fifo_name, S_IRUSR | S_IWUSR);
	 	if(ret < 0)
	 	{
	 		perror("create fifo fail!\n");
	 		exit(-1);
	 	}
	}

	if (0 == fork()) 
	{
	    open(fifo_name, O_RDONLY, 0);
	    sleep(1);
	    exit(0);
	}
	
	fd = open(fifo_name, O_WRONLY , 0);
	if(fd < 0)
	{
		perror("open fifo write fail!\n");
		exit(-1);
	}

	temp = open(fifo_name, O_RDONLY, 0);
	if(temp < 0)
	{
		perror("open fifo temp fail!\n");
		exit(-1);
	}

	printf("open fifo success\n");

	file_ctrl = fcntl(fd, F_GETFL, 0);
    file_ctrl |= O_NONBLOCK;
    fcntl(fd, F_SETFL, file_ctrl); 

    printf("set non block success!\n");
	return fd;
}

void init_logm(char *module_name)
{
	int i;
	int key = -1;
	int ret;
	int shm_exist = 0;
	int shm_id;

    for(int i=0; i<sizeof(module_keys)/sizeof(struct module_key_t); ++i)
	{
		if(0 == strncmp(module_name, module_keys[i].name, strlen(module_name)))
		{
			key = module_keys[i].shm_key;
			break;
		}
	}

	if(key < 0)
	{
		printf("init_logm fail! can not find shm_key \n");
		return;
	}

    ret = shmget(key, sizeof(unsigned int), 0660|IPC_CREAT|IPC_EXCL);
    if(ret < 0)
    {
    	printf("shm key:%d has been create\n", key);
    	shm_exist = 1;
    	shm_id = shmget(key, sizeof(unsigned int), 0660|IPC_CREAT);
        if(shm_id < 0)
        {
        	perror("create shm key fail");
    	    printf("create shm key:%d fail!\n", key);
    	    return;
        }
    }
    else
    {
        shm_exist = 0;
        shm_id = ret;
    }

    p_cur_level = (int *)shmat(shm_id, 0, 0);  
    if(p_cur_level == (void *)-1)
    {
    	printf("map shm fail!\n");
    	return;
    }

    if(0 == shm_id) //not initialized
    {
    	printf("shm not init, set to 0");
    	*p_cur_level = 0;
    }
    else
    {
    	printf("shm has been init, log level is %d \n", *p_cur_level);
    }

    if(write_fd < 0)
	{
		write_fd = create_fifo_fd();
	}

    return;
}


void set_timeflag()
{
	if(is_jiffies_init())
	{
		timeflag = 1;
	}

	return;
}


void send_log_msg(char* file_name, int line, const char *fmt, ...)
{
	va_list args;
	char printbuffer[1024*10];
	int head_len;
	int len = 0;
	struct timeval now;
	struct tm result;
	
	if(write_fd < 0) return;

	if(timeflag)
	{
		#if 0
		gettimeofday(&now, NULL);
		localtime_r(&now.tv_sec, &result);
		head_len = sprintf(printbuffer, "%d-%d-%d-%d ", \
						   result.tm_hour, result.tm_min,  result.tm_sec, now.tv_usec/1000);
		#endif
		head_len = sprintf(printbuffer, "%u ", get_jiffies());
	}
	else
	{
		head_len = sprintf(printbuffer, "%s line: %d ", file_name, line);		
	}

	va_start(args, fmt);
	len = vsnprintf(&printbuffer[head_len],(1024*10 - head_len), fmt, args);
	va_end(args);

	write(write_fd, printbuffer, (head_len+len));

	

	return;
}

void send_log_raw_msg(const char *fmt, ...)
{
	va_list args;
	char printbuffer[1024*10];
	int len = 0;
	
	if(write_fd < 0) return;

	va_start(args, fmt);
	len = vsnprintf(printbuffer,1024*10, fmt, args);
	va_end(args);

	write(write_fd, printbuffer, len);

	return;
}

void print_cur_level(void)
{
	printf("current log level is %d \n", *p_cur_level);
}



