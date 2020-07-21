#ifndef __U_TIMER__
#define __U_TIMER__

#ifdef __cplusplus
extern "C" {
#endif

struct set_timer_t
{
	unsigned int action;  //1:set 0: del
	unsigned int flag;    //1: persist, 0:one short
	unsigned int timer_id;
	unsigned int secs;
	unsigned int u_secs;	
};

#define SET_TIMER 1
#define DEL_TIMER 0
#define TIMER_PERSIST 1
#define TIMER_ONESHOT 0

#define set_timer_ms(timer_id, ms, flag) set_timer(timer_id, (ms/1000), ((ms%1000)*1000), flag)
#define set_timer_us(timer_id, us, flag) set_timer(timer_id, 0, us, flag)

int init_timer(void);  
int set_timer(int timer_id, unsigned long secs, unsigned long us, int flag);
int del_timer(int timer_id);
void close_timer(void);

#ifdef __cplusplus
}
#endif


#endif
