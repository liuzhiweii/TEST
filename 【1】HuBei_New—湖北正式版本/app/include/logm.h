#ifndef __LOGM__
#define __LOGM__


#ifdef __cplusplus
extern "C"
{
#endif

extern int write_fd;

#define M_DEBUG  5
#define M_INFO   4
#define M_WARN   3
#define M_ERR    2
#define M_ALERT  1

#define logm_debug(...) if(*p_cur_level >= M_DEBUG) send_log_msg(__FILE__, __LINE__, __VA_ARGS__)
#define logm_info(...) if(*p_cur_level >= M_INFO) send_log_msg(__FILE__, __LINE__, __VA_ARGS__)
#define logm_warn(...) if(*p_cur_level >= M_WARN) send_log_msg(__FILE__, __LINE__, __VA_ARGS__)
#define logm_err(...) if(*p_cur_level >= M_ERR) send_log_msg(__FILE__, __LINE__, __VA_ARGS__)
#define logm_alert(...) if(*p_cur_level >= M_ALERT) send_log_msg(__FILE__, __LINE__, __VA_ARGS__)
#define logm(level, ...)  if(*p_cur_level >= level) send_log_msg(__FILE__, __LINE__, __VA_ARGS__)

#define logm_debug_raw(...) if(*p_cur_level >= M_DEBUG) send_log_raw_msg(__VA_ARGS__)
#define logm_info_raw(...) if(*p_cur_level >= M_INFO) send_log_raw_msg(__VA_ARGS__)
#define logm_warn_raw(...) if(*p_cur_level >= M_WARN) send_log_raw_msg(__VA_ARGS__)
#define logm_err_raw(...) if(*p_cur_level >= M_ERR) send_log_raw_msg(__VA_ARGS__)



#define logm_debug_buffer(buffer, length)\
do\
{\
	char buffer_00_00[1024*5];\
	int index__00; \
	unsigned char upper0; \
	unsigned char lower0; \
    if(*p_cur_level >= M_DEBUG) \
    {\
    	for(index__00=0; index__00<length; ++index__00)\
    	{\
    		upper0 = buffer[index__00]>>4;\
			lower0 = buffer[index__00]&0x0f;\
			buffer_00_00[index__00<<1] = (upper0>9) ? (upper0+87) : (upper0+48);\
			buffer_00_00[(index__00<<1)+1] = (lower0>9) ? (lower0+87) : (lower0+48);\
    	}\
    	buffer_00_00[length<<1] = '\n'; \
    	buffer_00_00[(length<<1)+1] = 0; \
    	write(write_fd, buffer_00_00, ((length<<1)+2));\
    }\
}while(0)


#define CMM_KEY  1000
#define COMM_KEY 1001
#define CFG_KEY 1002

#define MODULE_NUM 12

struct module_key_t
{
    char *name;
    int shm_key;
};



extern void init_logm(char *module_name);
extern void set_timeflag();
extern void send_log_msg(char* file_name, int line, const char *fmt, ...);
extern void send_log_raw_msg(const char *fmt, ...);
extern struct module_key_t module_keys[MODULE_NUM];
extern int *p_cur_level;
extern void print_cur_level(void);

#ifdef __cplusplus
}
#endif

#endif
