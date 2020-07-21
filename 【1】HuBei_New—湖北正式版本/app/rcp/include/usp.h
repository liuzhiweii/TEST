/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp.h
* 文件标识： 
* 内容摘要： USP系统头文件，所有使用USP的应用包含该文件即可
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2009.03.10
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _USP_H
#define _USP_H

#ifndef _PC_LINT
#ifdef __cplusplus
extern "C" {
#endif
#endif

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <termios.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <sys/select.h>
#include <pthread.h>
#include <setjmp.h>
#include <crypt.h>
#include <sys/prctl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <linux/rtnetlink.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/route.h>
#include <sched.h>
#include <dlfcn.h>
#include <linux/ppp_defs.h>
#include <linux/if_ppp.h>   
#include <sys/utsname.h>
#include <sys/mman.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <sys/dir.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <pthread.h>


#define  EEPROM_SWITCH          0  /* EEPROM read or write switch now off(0)  then in the release version  on (1)*/

/**************************************************************************
 *                       开关宏定义                                        *
 **************************************************************************/
#define TRUE             (1)
#define FALSE            (0)

/**************************************************************************
 *                       包含总的配置文件                                 *
 **************************************************************************/
#include "usp.conf"

/**************************************************************************
 *                       包含公用头文件                                   *
 **************************************************************************/
#include "usp_typeDef.h"
#include "usp_errorDef.h"
#include "usp_eventDef.h"
#include "usp_pub.h"

/**************************************************************************
 *                       包含其他配置文件                                 *
 **************************************************************************/
#include "drv.conf"

/**************************************************************************
 *                       USP各子系统对外接口                              *
 **************************************************************************/

/* ioexpander模块对外接口*/
#if USP_DRV_IOE_USE
    #include "usp_drvIoexpander.h"
#endif

/* Tsensor对外接口 */
#if USP_DRV_TSENSOR_USE
    #include "usp_drvTsensor.h"
#endif




#if USP_OSS_SCP_USE
/* 系统主控对外接口 */
#include "usp_scp.h"
#endif


/* 驱动模块(DRV)对外接口 */

/*  Epld块对外接口*/
#if USP_DRV_EPLD_USE
	#include "usp_drvEpld.h"
#endif

 volatile WORD16 g_pvUSPDrvFpgaVirtStartAddr0[2048];
 volatile WORD16 g_pvUSPDrvEpldVirtStartAddr0[2048];


#if UHF_PROTOCOL_USE
#include "uhf.conf"
#include "usp_uhf_cfg.h"
#include "usp_uhf_epc.h"
#include "usp_uhf_iso6b.h"
#include "usp_uhf_gb.h"   // support for GB
#include "usp_uhf_err.h"
#include "usp_uhf.h"
//#include "usp_uhfllrpconfig.h"
#endif



#ifndef _PC_LINT
#ifdef __cplusplus
}
#endif
#endif

#endif  /* _USP_H */


