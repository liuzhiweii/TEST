/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称： timerDef.h
* 文件标识： 
* 内容摘要：timer驱动接口头文件
* 其它说明： 
* 当前版本： 
* 作    者： lg
* 完成日期：2015.2.09
* 
************************************************************************/

#ifndef _TIMER_DEF_H_
#define _TIMER_DEF_H_


typedef unsigned short T_TimerAddr;



/*宏定义*/
#define WRITE_TIMER_REG(OFFSET,DATA)   *((volatile T_TimerAddr*)((unsigned int)g_pTimerUsrSpaceBaseAddr+OFFSET))=(DATA)
#define READ_TIMER_REG(OFFSET)         *((volatile T_TimerAddr*)((unsigned int)g_pTimerUsrSpaceBaseAddr+OFFSET))
#define WRITE_TIMER_WORD32_REG(OFFSET,DATA)   *((volatile unsigned int*)((unsigned int)g_pTimerUsrSpaceBaseAddr+OFFSET))=(DATA)
#define READ_TIMER_WORD32_REG(OFFSET)         *((volatile unsigned int*)((unsigned int)g_pTimerUsrSpaceBaseAddr+OFFSET))
#define WRITE_TIMER_WORD16_REG(OFFSET,DATA)   *((volatile unsigned short*)((unsigned int)g_pTimerUsrSpaceBaseAddr+OFFSET))=(DATA)
#define READ_TIMER_WORD16_REG(OFFSET)         *((volatile unsigned short*)((unsigned int)g_pTimerUsrSpaceBaseAddr+OFFSET))
#define WRITE_TIMER_BYTE_REG(OFFSET,DATA)   *((volatile unsigned char*)((unsigned int)g_pTimerUsrSpaceBaseAddr+OFFSET))=(DATA)
#define READ_TIMER_BYTE_REG(OFFSET)         *((volatile unsigned char*)((unsigned int)g_pTimerUsrSpaceBaseAddr+OFFSET))
    extern volatile T_TimerAddr *g_pTimerUsrSpaceBaseAddr;
#ifdef TIMER_USE_INT_MODE
    #define WRITE_TIMER_REG_INT(OFFSET,DATA)   *((volatile unsigned short*)((unsigned int)g_pTimerKernelSpaceBaseAddr+OFFSET))=(DATA)
	#define READ_TIMER_REG_INT(OFFSET)         *((volatile unsigned short*)((unsigned int)g_pTimerKernelSpaceBaseAddr+OFFSET))
    #define WRITE_TIMER_BYTE_REG_INT(OFFSET,DATA)   *((volatile unsigned char*)((unsigned int)g_pTimerKernelSpaceBaseAddr+OFFSET))=(DATA)
	#define READ_TIMER_BYTE_REG_INT(OFFSET)         *((volatile unsigned char*)((unsigned int)g_pTimerKernelSpaceBaseAddr+OFFSET))
    extern volatile unsigned short *g_pTimerKernelSpaceBaseAddr;

	#define BSP_DRV_TIMER_IRQ_NUMBER       84     /*GTM3中断号*/
	/*ioctl命令*/
	#define    TIMER_IOCTL_BASE            'T'
	#define    TIMER_SLEEP_SET             _IOWR(TIMER_IOCTL_BASE, 1, unsigned long)
#endif

/*MPC8306 TIMER1 寄存器定义*/
#define TIMER_GTCFR1_REG_OFFSET      0x500    /*Timer1配置寄存器*/
#define TIMER_GTMDR1_REG_OFFSET      0x510    /*Timer1模式寄存器*/
#define TIMER_GTMDR2_REG_OFFSET      0x512    /*Timer2模式寄存器*/
#define TIMER_GTRFR1_REG_OFFSET      0x514    /*Timer1参考寄存器*/
#define TIMER_GTRFR2_REG_OFFSET      0x516    /*Timer2参考寄存器*/
#define TIMER_GTCPR1_REG_OFFSET      0x518    /*Timer1捕获寄存器*/
#define TIMER_GTCPR2_REG_OFFSET      0x51A    /*Timer2捕获寄存器*/
#define TIMER_GTCNR1_REG_OFFSET      0x51C    /*Timer1计数寄存器*/
#define TIMER_GTCNR2_REG_OFFSET      0x51E    /*Timer2计数寄存器*/
#define TIMER_GTEVR1_REG_OFFSET      0x530    /*Timer1事件寄存器*/
#define TIMER_GTEVR2_REG_OFFSET      0x532    /*Timer2事件寄存器*/
#define TIMER_GTPSR1_REG_OFFSET      0x538    /*Timer1分频寄存器*/
#define TIMER_GTPSR2_REG_OFFSET      0x53A    /*Timer2分频寄存器*/

#define TIMER_GTCFR2_REG_OFFSET      0x504    /*Timer3配置寄存器*/
#define TIMER_GTMDR3_REG_OFFSET      0x520    /*Timer3模式寄存器*/
#define TIMER_GTRFR3_REG_OFFSET      0x524    /*Timer3参考寄存器*/
#define TIMER_GTCPR3_REG_OFFSET      0x528    /*Timer3捕获寄存器*/
#define TIMER_GTCNR3_REG_OFFSET      0x52C    /*Timer3计数寄存器*/
#define TIMER_GTEVR3_REG_OFFSET      0x534    /*Timer3事件寄存器*/
#define TIMER_GTPSR3_REG_OFFSET      0x53C    /*Timer3分频寄存器*/

/*初始化定时器,TIMER3用于中断模式*/
	/*
	1.停止timer3;
	3.设置3级分频系数
	4.设置3级分频系数和时钟源，最终定时器时钟频率10KHz；
	5.清除事件寄存器；
	6.设置参考寄存器；
	7.计数器清0;
	*/
	#define TIMER_INIT_INT(REF_VALUE)\
	do\
	{\
	    WRITE_TIMER_BYTE_REG_INT(TIMER_GTCFR2_REG_OFFSET,0x33);\
	    WRITE_TIMER_REG_INT(TIMER_GTPSR3_REG_OFFSET,0x0063);\
        WRITE_TIMER_REG_INT(TIMER_GTMDR3_REG_OFFSET,0x841A);\
        WRITE_TIMER_REG_INT(TIMER_GTEVR3_REG_OFFSET,0x0003);\
        WRITE_TIMER_REG_INT(TIMER_GTRFR3_REG_OFFSET,REF_VALUE);\
        WRITE_TIMER_REG_INT(TIMER_GTCNR3_REG_OFFSET,0x0000);\
	    WRITE_TIMER_BYTE_REG_INT(TIMER_GTCFR2_REG_OFFSET,0x2D);\
	}while(0)

    /*关闭定时器*/

	#define TIMER_STOP_INT()\
	do\
	{\
	    WRITE_TIMER_BYTE_REG_INT(TIMER_GTCFR2_REG_OFFSET,0xFF);\
	}while(0)


/*初始化定时器*/
/*
1.停止timer1和timer2;
2.设置timer1和timer2级联；
3.设置2级分频系数
4.设置1级分频系数和时钟源，最终定时器时钟频率1MHz；
5.清除事件寄存器；
6.设置参考寄存器；
7.计数器清0;
*/
#define TIMER_INIT()\
do\
{\
    unsigned int dwRegData = 0;\
    WRITE_TIMER_BYTE_REG(TIMER_GTCFR1_REG_OFFSET,0x33);\
    dwRegData = READ_TIMER_BYTE_REG(TIMER_GTCFR1_REG_OFFSET);\
    WRITE_TIMER_BYTE_REG(TIMER_GTCFR1_REG_OFFSET,(dwRegData | 0x80));\
    WRITE_TIMER_REG(TIMER_GTPSR1_REG_OFFSET,0x0000);\
    WRITE_TIMER_REG(TIMER_GTPSR2_REG_OFFSET,0x0000);\
    WRITE_TIMER_REG(TIMER_GTMDR2_REG_OFFSET,0x8402);\
    WRITE_TIMER_REG(TIMER_GTMDR1_REG_OFFSET,0x0000);\
    WRITE_TIMER_REG(TIMER_GTEVR1_REG_OFFSET,0x0003);\
    WRITE_TIMER_REG(TIMER_GTEVR2_REG_OFFSET,0x0003);\
    WRITE_TIMER_REG(TIMER_GTRFR1_REG_OFFSET,0xFFFF);\
    WRITE_TIMER_REG(TIMER_GTRFR2_REG_OFFSET,0xFFFF);\
    WRITE_TIMER_REG(TIMER_GTCNR1_REG_OFFSET,0x0000);\
    WRITE_TIMER_REG(TIMER_GTCNR2_REG_OFFSET,0x0000);\
}while(0)

/*启动定时器*/

#define TIMER_START()\
do\
{\
    WRITE_TIMER_BYTE_REG(TIMER_GTCFR1_REG_OFFSET,0xDD);\
}while(0)


/*关闭定时器*/

#define TIMER_STOP()\
do\
{\
    WRITE_TIMER_BYTE_REG(TIMER_GTCFR1_REG_OFFSET,0xFF);\
}while(0)

/*清零定时器*/
#define TIMER_CLEAR()\
do\
{\
    TIMER_INIT();\
    TIMER_START();\
}while(0)

/*获取当前计数值*/
#define GET_CURRENT_COUNTER()\
do\
{\
    dwCurrenCounter = READ_TIMER_WORD32_REG(TIMER_GTCNR1_REG_OFFSET);\
}while(0)

#endif
