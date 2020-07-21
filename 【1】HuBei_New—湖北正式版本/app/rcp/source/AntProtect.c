#include "usp.h"
#if (UHF_PROTOCOL_USE)
#include "Board.h"
#if USP_UHF_AUTO_PROTECTED_USE
#include "uhf_dbg.h"
#include "FpgaCtl.h"
#include "uhf_rf.h"
#include "RfCtl.h"


/**************************************************************************
* 函数名称：WORD32 InitI2CValue(void)
* 功能描述：初始化I2C总线上射频相关地址的值，
                                 用来当需要写入I2C数据时进行比较
* 输入参数：无
* 输出参数：
* 返 回 值：    WORD32  成功返回0
                                 其他错误
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
*11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
#define TSENSOR_HIGHTEM_ALARM (105)
#define TSENSOR_LOWTEM_ALARM  (-55)
void uhfRf_initVswrAlarm(void)
{
    BYTE ucEpldVal = 0;
    WORD32 dwRet = 0;
    /*下面屏蔽掉驻波比告警中断，应用采用查询的方式实现*/
    ucEpldVal = uhf_epld_reg_read(REG_VSWR_ALARM_MASK);
    ucEpldVal &= (~0x2);
    uhf_epld_reg_write(REG_VSWR_ALARM_MASK, ucEpldVal);
	#if 0

    dwRet = usp_drv_tsensor_set_temperature(UHF_RF_TSENSOR_LOCAL_TEMP_LOW, TSENSOR_LOWTEM_ALARM);

    if (dwRet != USP_SUCCESS)
    {
        LAPInsert(FILE_RFCB, USP_UHF_TSENSOR_ERROR, dwRet, 0);
    }

    dwRet = usp_drv_tsensor_set_temperature(UHF_RF_TSENSOR_LOCAL_TEMP_HIGH, TSENSOR_HIGHTEM_ALARM);

    if (dwRet != USP_SUCCESS)
    {
        LAPInsert(FILE_RFCB, USP_UHF_TSENSOR_ERROR, dwRet, 0);
    }

    dwRet = usp_drv_tsensor_set_temperature(UHF_RF_TSENSOR_REMOTE_TEMP_LOW, TSENSOR_LOWTEM_ALARM);

    if (dwRet != USP_SUCCESS)
    {
        LAPInsert(FILE_RFCB, USP_UHF_TSENSOR_ERROR, dwRet, 0);
    }

    dwRet = usp_drv_tsensor_set_temperature(UHF_RF_TSENSOR_REMOTE_TEMP_HIGH, TSENSOR_HIGHTEM_ALARM);

    if (dwRet != USP_SUCCESS)
    {
        LAPInsert(FILE_RFCB, USP_UHF_TSENSOR_ERROR, dwRet, 0);
    }
	#endif
}

/**************************************************************************
* 函数名称：RFCB_IsAntProtected
* 功能描述：反向DATT控制
* 输入参数：在清点完成后验证是否进行了筑波保护
* 输出参数：
* 返 回 值：    WORD32  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
#define VSWR_PROTECTED    1
#define VSWR_UNPROTECTED  0
WORD32 uhfRf_IsAntProtected(void)
{
    if (VSWR_PROTECTED == uhf_epld_reg_read(REG_VSWR_ALARM))
    {
        uhfRfDevPrint("uhfRf:Ant has been protected\r\n");
        return USP_UHF_ANT_IS_PROTECTED;
    }
    else
    {
        return USP_SUCCESS;
    }
}

/**************************************************************************
* 函数名称：void uhfRf_DealAlarmReport(WORD16 *pwRestults,WORD16 wAntIndex)
* 功能描述：是否发送告警给后台
* 输入参数：天线号和返回值
* 输出参数：
* 返 回 值：    无
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V4.50.00     zdx	      创建
**************************************************************************/
WORD16 uhfRf_dealAlarmReport(WORD16 wAntIndex)
{
    static BYTE aucAntAlarmStaus[5] = {0};
    WORD16 wReslts = USP_SUCCESS;

    if (USP_UHF_ANT_IS_PROTECTED == uhfRf_IsAntProtected())
    {
        if (aucAntAlarmStaus[wAntIndex] == VSWR_UNPROTECTED)
        {
            SendAntAbnoramlAlarm(wAntIndex, EV_USP_OAM_AMP_AlarmReport);
            uhfRfDevPrint("Send Alarm to back\r\n");
            aucAntAlarmStaus[wAntIndex] = VSWR_PROTECTED;
            wReslts = USP_UHF_ANT_IS_PROTECTED;
        }
    }
    else
    {
        if (VSWR_PROTECTED == aucAntAlarmStaus[wAntIndex])
        {
            SendAntAbnoramlAlarm(wAntIndex, EV_USP_OAM_AMP_AlarmRestoreReport);
            uhfRfDevPrint("Send Alarm restore to back\r\n");
            aucAntAlarmStaus[wAntIndex] = VSWR_UNPROTECTED;
        }
    }

    return wReslts;
}
/**************************************************************************
* 函数名称：RemoveAntAlarmStatus
* 功能描述：处理天线是否筑波保护
* 输入参数：无
* 输出参数：
* 返 回 值：    WORD32  成功返回0
* 其它说明：
* 修改日期     版本号     修改人	     修改内容
* -----------------------------------------------
* 11/01/17	     V05.00.00	    zdx	      创建
**************************************************************************/
#define TEMP_ALARMED      (1)
#define TEMP_NOT_ALARME   (0)

#define RemoveVswrAlarm  \
{\
    uhf_epld_reg_write(REG_PA_EN_TRIG,0x0);\
    uhf_epld_reg_write(REG_PA_EN_TRIG,0x1);\
    usp_uhf_rf_setAmp(RF_AMP_ON);\
}

WORD32 usp_uhf_rf_removeAntAlarm()
{
    BYTE ucVswrAlarmVal = 0;
    BYTE ucTemAlarmStaus = 0;
    CHAR ucLocalTem = 0;
    CHAR ucRemoteTem = 0;
    BYTE ucClearInt = 0;
    WORD32 dwRet = USP_SUCCESS;
    static BYTE s_ucAlarmed = TEMP_NOT_ALARME;

    ucVswrAlarmVal = uhf_epld_reg_read(REG_VSWR_ALARM);
    uhfRfDevPrint("uhfRf:VSWR Alarm status %d\r\n", ucVswrAlarmVal);
#if 0
    if (ucVswrAlarmVal == VSWR_PROTECTED)
    {
        uhfRfDevPrint("uhfRf:VSWR Alarm happened\r\n");
        /* 此处查看是否是因为温度导致的筑波保护*/
        dwRet = usp_drv_tsensor_get_temperature(UHF_RF_TSENSOR_ALARM_STATUS, &ucTemAlarmStaus);

        if (dwRet != USP_SUCCESS)
        {
            uhfRfDevPrint("uhfRf:Get temperature alarm staus failed %d\r\n", dwRet);
            ucTemAlarmStaus = 0;
        }

        uhfRfDevPrint("uhfRf:SECOND_TSENSOR_ALARM_STATUS %d\r\n", ucTemAlarmStaus);
        /* 取寄存器值的3~6位的值，表示告警标志 */
        /* 0x78=0111 1000 */
        ucTemAlarmStaus &= 0x78;

        if (ucTemAlarmStaus != 0 || s_ucAlarmed == TEMP_ALARMED)
        {
            s_ucAlarmed = TEMP_ALARMED;
            dwRet = usp_drv_tsensor_get_temperature(UHF_RF_TSENSOR_LOCAL_TEMP, (BYTE *)&ucLocalTem);

            if (dwRet != USP_SUCCESS)
            {
                uhfRfDevPrint("uhfRf:Get temperature local staus failed %d\r\n", dwRet);
                ucLocalTem = 0;
            }

            uhfRfDevPrint("uhfRf:SECOND_TSENSOR_LOCAL_TEMP  %d\r\n", ucLocalTem);
            dwRet = usp_drv_tsensor_get_temperature(UHF_RF_TSENSOR_REMOTE_TEMP, (BYTE *)&ucRemoteTem);

            if (dwRet != USP_SUCCESS)
            {
                uhfRfDevPrint("uhfRf:Get temperature remote staus failed %d\r\n", dwRet);
                ucRemoteTem = 0;
            }

            uhfRfDevPrint("uhfRf:SECOND_TSENSOR_REMOTE_TEMP  %d\r\n", ucRemoteTem);

            if (((ucLocalTem > -40) && (ucLocalTem < 90)) && ((ucRemoteTem > -40) && (ucRemoteTem < 90)))
            {
                dwRet = usp_drv_tsensor_get_temperature(UHF_RF_TSENSOR_CLEAR_INT, &ucClearInt);

                if (dwRet != USP_SUCCESS)
                {
                    uhfRfDevPrint("uhfRf:Get SECOND_TSENSOR_CLEAR_INT failed 0x%x\r\n", dwRet);
                }

                uhfRfDevPrint("uhfRf:SECOND_TSENSOR_CLEAR_INT is 0x%x\r\n", ucClearInt);
                /* 清除驻波保护 */
                RemoveVswrAlarm;
                s_ucAlarmed = TEMP_NOT_ALARME;
                uhfRfDevPrint("uhfRf:Remove alarm tmep\r\n");
            }
            else
            {
                return USP_UHF_TEM_ABNORMAL;
            }

        }
        else
        {
            uhfRfDevPrint("uhfRf:Remove alarm tmep\r\n");
            RemoveVswrAlarm;
        }

        /* 查看是否还有驻波保护 */
        ucVswrAlarmVal = uhf_epld_reg_read(REG_VSWR_ALARM);

        if (VSWR_UNPROTECTED == ucVswrAlarmVal)
        {
            uhfRfDevPrint("uhfRf:VSWR Alarm is removed\r\n");
        }
        else
        {
            uhfRfDevPrint("uhfRf:VSWR Alarm is not removed!!!!!\r\n");
            return USP_UHF_ANT_IS_PROTECTED;
        }
    }
#endif
    return USP_SUCCESS;
}

#else

/*下面是在老板5.0硬件上的实现函数为空，不存在
    此驻波保护的功能，以后不维护了可以删掉*/
void   uhfRf_initVswrAlarm(void)
{

}

WORD32 uhfRf_IsAntProtected(void)
{
    return USP_SUCCESS;
}

WORD16 uhfRf_dealAlarmReport(WORD16 wAntIndex)
{
    return USP_SUCCESS;
}

WORD32 usp_uhf_rf_removeAntAlarm()
{
    return USP_SUCCESS;
}

#endif

#endif

