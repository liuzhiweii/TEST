/************************************************************************
* 版权所有 (C)2012, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： usp_lib.h
* 文件标识： 
* 内容摘要： USP动态库头文件，所有使用USP的应用包含该文件即可
* 其它说明： 
* 当前版本： 
* 作    者： 高峰
* 完成日期： 2012.02.06
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef _USP_LIB_H
#define _USP_LIB_H

#ifndef _PC_LINT
#ifdef __cplusplus
extern "C" {
#endif
#endif


/**************************************************************************
 *                       开关宏定义                                        *
 **************************************************************************/
#define TRUE             (1)
#define FALSE            (0)

/**************************************************************************
 *                       包含总的配置文件                                 *
 **************************************************************************/

/**************************************************************************
 *                       包含公用头文件                                   *
 **************************************************************************/
#include "usp_lib_typeDef.h"
#include "usp_lib_msg.h"

/**************************************************************************
 *                       USP操作句柄抽象数据类型                          *
 **************************************************************************/
typedef struct tagT_USPLibHandle    *USPLibHandle;

/**************************************************************************
 *                       包含其他配置文件                                 *
 **************************************************************************/

/**************************************************************************
 *                       USP各子系统对外接口                              *
 **************************************************************************/
#include "usp_lib_vos.h"
#include "usp_lib_scp.h"
#//include "usp_lib_ltk.h"
//#include "usp_lib_cli.h"
//#include "usp_lib_psam.h"
//#include "usp_lib_timer.h"
//#include "usp_lib_comm.h"
//#include "usp_lib_cmp.h"
//#include "usp_lib_sysdata.h"
//#include "usp_lib_lap.h"
//#include "usp_lib_amp.h"
//#include "usp_lib_dmp.h"
//#include "usp_lib_mpi.h"
//#include "usp_lib_dsrc.h"
//#include "usp_lib_shell.h"
//#include "usp_lib_etc.h"
//#include "usp_lib_uhf.h"
//#include "usp_lib_psp.h"
//#include "usp_lib_vmp.h"
//#include "usp_lib_gpio.h"
//#include "usp_lib_misc.h"
//#include "usp_lib_led.h"
//#include "usp_lib_dsm.h"
/**************************************************************************
 *                       USP操作句柄数据类型                              *
 **************************************************************************/
typedef struct tagT_USPLibHandle
{
    WORD32              dwMagic;    /* 校验魔术字（0x5A5A5A5A）*/
    #if 0
    USPLibScpHandle     scpHandle;  /* SCP操作句柄 */
    USPLibLtkHandle     ltkHandle;  /* LTK操作句柄 */
    USPLibCliHandle     cliHandle;  /* CLI操作句柄 */
    USPLibDmpHandle     dmpHandle;  /* DMP操作句柄 */
    USPLibPsamHandle    psamHandle; /* PSAM操作句柄 */
    USPLibTimerHandle   timerHandle;/* TIMER操作句柄 */
    USPLibCommHandle    commHandle; /* COMM操作句柄 */ 
    USPLibLapHandle     lapHandle;  /* LAP操作句柄 */ 
    USPLibAmpHandle     ampHandle;  /* AMP操作句柄 */ 
	USPLibCmpHandle     cmpHandle;  /* CMP操作句柄 */
    USPLibMpiHandle     mpiHandle;  /* MPI操作句柄 */
	USPLibDsrcHandle    dsrcHandle;
    USPLibUhfHandle     uhfHandle;
    USPLibPspHandle     pspHandle;
    USPLibVmpHandle     vmpHandle;
    USPLibGpioHandle    gpioHandle;
    USPLibMiscHandle    miscHandle;
    USPLibLedHandle     ledHandle;
    USPLibDsmHandle     dsmHandle;
    #endif
}T_USPLibHandle;

#ifndef _PC_LINT
#ifdef __cplusplus
}
#endif
#endif

#endif  /* _USP_LIB_H */

