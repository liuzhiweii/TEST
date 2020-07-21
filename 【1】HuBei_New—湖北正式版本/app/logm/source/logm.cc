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
#include "logm.h"
#include <errno.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h> 

using namespace std;


const char *fifo_name = "/log.fifo";

int *shm_ptr_array[MODULE_NUM];

void print_usage()
{
	printf("Usage: \n\tlogm comm:debug  rcp:warn .....\n");
}

void print_all_module_name(void)
{
	for(int i=0; i<(sizeof(module_keys)/sizeof(module_key_t)); ++i)
	{
		printf("%s \t", module_keys[i].name);
	}

	printf("\n");

	return;
}


int level_to_int(const char *level)
{
    if(strncmp(level, "debug", 5) == 0)
    {
        return 5;
    }

    if(strncmp(level, "info", 4) == 0)
    {
        return 4;
    }

    if(strncmp(level, "warn", 4) == 0)
    {
        return 3;
    }

    if(strncmp(level, "error", 5) == 0)
    {
        return 2;
    }

    if(strncmp(level, "alert", 5) == 0)
    {
        return 1;
    }

    return 0;
}



void init_shm_ptr_array(void)
{
    int i;
    int key;
    int shm_id;
    int *shm_ptr = NULL;

    for(i=0; i<(sizeof(module_keys)/sizeof(module_key_t)); ++i)
    {
        key = module_keys[i].shm_key;
        shm_id = shmget(key, sizeof(int), 0660|IPC_CREAT);
        if(shm_id < 0)
        {
            printf("create shm key:%d fail!\n", key);
            shm_ptr_array[i] = NULL;
            continue;
        }

        shm_ptr = (int *)shmat(shm_id, 0, 0);  
        if(shm_ptr == (void *)-1)
        {
            shm_ptr_array[i] = NULL;
            continue;
        }
        
        *shm_ptr = 0; //init all the level to 0
        shm_ptr_array[i] = shm_ptr;
    }

    return;
}

int *name_to_shmptr(const char *name)
{
    int i;
    for(i=0; i<MODULE_NUM; ++i)
    {
        if(0 == strncmp(name, module_keys[i].name, strlen(name)))
        {
            return shm_ptr_array[i];
        }
    }

    return NULL;
}

int find_key_by_name(const char *name)
{
    int i;

    for(i=0; i<MODULE_NUM; ++i)
    {
        if(0 == strncmp(name, module_keys[i].name, strlen(name)))
        {
            printf("find %s shm_key is %d", name, module_keys[i].shm_key);
            return module_keys[i].shm_key;
        }
    }

    return -1;
}

void set_level_by_name(const char *name, int level)
{

    int *shm_ptr = NULL;

    shm_ptr = name_to_shmptr(name);
    if(NULL != shm_ptr)
    {
        *shm_ptr = level;
    }
    else
    {
    	printf("module name \"%s\" not registered!\n", name);
    	printf("all register module name:\n");
    	print_all_module_name();
    	exit(-1);
    }
}


void set_all_modules(int level)
{
    int i;
    int *shm_ptr;

    for(i=0; i<MODULE_NUM; ++i)
    {
        shm_ptr = shm_ptr_array[i];
        if(NULL != shm_ptr)
        {
            *shm_ptr = level;
        }
    }
}

void set_module_log_level(int num, char *argv[])
{    
    
    
    for(int i=0; i<num; ++i)
    {
        string para(argv[i]);
        string::size_type pos = para.find(":");
        if(pos == string::npos)
        {
            print_usage();
            exit(-1);
        }

        string module_name = para.substr(0, pos);
        string level = para.substr(pos+1);

        if(0 == strncmp(module_name.c_str(), "all", 3))
        {
            int level_int;
            level_int = level_to_int(level.c_str());
            set_all_modules(level_int);
            return;
        }

        set_level_by_name(module_name.c_str(), level_to_int(level.c_str()));  
        printf("set module %s level %d \n", module_name.c_str(), level_to_int(level.c_str()));
    }

    return;
}

void sig_func(int signo)
{
    int i;
    int *p_shm_ptr;

    for(i=0; i<MODULE_NUM; ++i)
    {
        p_shm_ptr = shm_ptr_array[i];
        if(p_shm_ptr != NULL)
        {
            *p_shm_ptr = 0;
        }
    }

    exit(0);
}

int main(int argc, char *argv[])
{
	
    int ret;
    int read_fd;
    char buf[4096];
    int len;

	if(argc < 2)
	{
		print_usage();
        exit(-1);
	}

    if(access(fifo_name, F_OK) < 0)   
    {
        int ret;
        ret = mkfifo(fifo_name, S_IRUSR | S_IWUSR);
        if(ret < 0)
        {
            perror("create fifo fail!\n");
            exit(-1);
        }
    }

    init_shm_ptr_array();

    signal(SIGINT, sig_func); 
    signal(SIGQUIT, sig_func); 

    read_fd = open(fifo_name, O_RDONLY|O_NONBLOCK , 0);
    if(read_fd < 0)
    {
        printf("open fifo fail!\n");
        exit(-1);
    }

    while(1)
    {
        len = read(read_fd, buf, 4096);
        if(len <= 0)
        {
            printf("clear fifo ok!\n");
            break;
        }
    }

    printf("read_fd=%d\n",read_fd);
    set_module_log_level((argc-1), &argv[1]);

    while(1)
    {
        fd_set rset;
        FD_ZERO(&rset);
        FD_SET(read_fd, &rset);
        int cnt = 0;
        select((read_fd+1), &rset, NULL, NULL, NULL);
        if(FD_ISSET(read_fd, &rset))
        {
            len = read(read_fd, buf, 4096);
            if(len > 0)
            {
                write(1, buf, len);
            }
        }
    }

    return 0;
}