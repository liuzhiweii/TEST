#ifndef __JIFFS__
#define __JIFFS__

extern 	void *jffies_addr;

#define get_jiffies() *((volatile unsigned long *)(jffies_addr))
#define is_jiffies_init() (jffies_addr != NULL)

int init_jiffs(void);


#endif


