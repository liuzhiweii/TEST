/************************************************************************
* 版权所有 (C)2009, 中兴通讯天津研究所
* 
* 文件名称： usp_tsensor.h
* 文件标识： 
* 内容摘要： 温度传感器模块对外接口头文件
* 其它说明： 
* 当前版本： USP01.10.00
* 作    者： 管慧娟
* 完成日期： 2009-12-11
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/


#ifndef _USP_TSENSOR_H_
#define _USP_TSENSOR_H_

/*功能ID 号定义--begin*/

/*对6700,first tsensor位于数字板上*/
#define FIRST_TSENSOR_LOCAL_TEMP               0
#define FIRST_TSENSOR_REMOTE_TEMP              1
#define FIRST_TSENSOR_LOCAL_TEMP_LOW           2
#define FIRST_TSENSOR_LOCAL_TEMP_HIGH          3
#define FIRST_TSENSOR_REMOTE_TEMP_LOW          4
#define FIRST_TSENSOR_REMOTE_TEMP_HIGH         5
#define FIRST_TSENSOR_ALARM_STATUS             6

/*射频板上的温度传感器*/
#define SECOND_TSENSOR_LOCAL_TEMP              7
#define SECOND_TSENSOR_REMOTE_TEMP             8
#define SECOND_TSENSOR_LOCAL_TEMP_LOW          9
#define SECOND_TSENSOR_LOCAL_TEMP_HIGH         10
#define SECOND_TSENSOR_REMOTE_TEMP_LOW         11
#define SECOND_TSENSOR_REMOTE_TEMP_HIGH        12
#define SECOND_TSENSOR_ALARM_STATUS            13
#define SECOND_TSENSOR_CLEAR_INT              14

/*功能ID 号定义--end*/



WORD32 usp_drv_tsensor_init(VOID);
WORD32 usp_drv_tsensor_get_temp_input(BYTE * pucValue);
WORD32 usp_drv_tsensor_get_remote_temp_input(BYTE * pucValue);
WORD32 usp_drv_tsensor_set_temp_high(BYTE ucValue);
WORD32 usp_drv_tsensor_set_temp_low(BYTE ucValue);
WORD32 usp_drv_tsensor_set_remote_temp_high(BYTE ucValue);
WORD32 usp_drv_tsensor_set_remote_temp_low(BYTE ucValue);
WORD32 usp_drv_tsensor_get_temp_high(BYTE * pucValue);
WORD32 usp_drv_tsensor_get_temp_low(BYTE * pucValue);
WORD32 usp_drv_tsensor_get_remote_temp_high(BYTE * pucValue);
WORD32 usp_drv_tsensor_get_remote_temp_low(BYTE * pucValue);
WORD32 usp_drv_tsensor_get_alarm_status(BYTE * pucValue);
WORD32 usp_drv_tsensor_get_temperature(BYTE ucFunID,BYTE * pucValue);
WORD32 usp_drv_tsensor_set_temperature(BYTE ucFunID,BYTE  ucValue);

#endif


