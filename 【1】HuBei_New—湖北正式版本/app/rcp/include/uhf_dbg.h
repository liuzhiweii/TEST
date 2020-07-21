#ifndef _USP_UHFDBG_H
#define _USP_UHFDBG_H

#define  FILE_UHF_BASE	              (0x0500)
#define  FILE_UHF	                  (0x0501)
#define  FILE_UHF_EPC	              (0x0502)
#define  FILE_UHF_ISO6B	              (0x0503)
#define  FILE_UHF_RF	              (0x0504)
#define  FILE_FPGAAPI	              (0x0505)
#define  FILE_RCPDMP	              (0x0507)
#define  FILE_RFCB   	              (0x0508)
#define  FILE_PURM                    (0x0509)
#define  FILE_FPGACTL   	          (0x050a)
#define  FILE_RFCB2                   (0x050b)
#define  FILE_UHF_RFCTRL              (0x050c)
#define  FILE_UHF_EPC_START           (0x050d)
#define  FILE_UHF_FPGARES             (0x050e)
#define  FILE_UHF_GB	                     (0x050f)
#define  FILE_UHF_GB_START           (0x0510)



#include "logm.h"

//#define LAPInsert(FileId,exceptCode,var1,var2)  \
//            USP_LAP_ABN_REPORT(var1, var2, 0, FileId, exceptCode); 

/* 错误提示信息打印 */

#if USP_OSS_PRINTF_USE
#define uhfDevPrint(...)    usp_oss_printf(USP_UHF_TNO,USP_OSS_PRINTF_LEVEL_DEBUG,__VA_ARGS__)
#define UHFErrorPrint(...)   usp_oss_printf(USP_UHF_TNO,USP_OSS_PRINTF_LEVEL_ERROR,__VA_ARGS__)
#define UHFAlertPrint(...)   usp_oss_printf(USP_UHF_TNO,USP_OSS_PRINTF_LEVEL_ALERT,__VA_ARGS__)
#define UHFWarningPrint(...)   usp_oss_printf(USP_UHF_TNO,USP_OSS_PRINTF_LEVEL_ALERT,__VA_ARGS__)
//#define LAPInsert(FileId,exceptCode,var1,var2)  \
//            USP_LAP_ABN_REPORT(var1, var2, 0, FileId, exceptCode); 
//#define uhf_amp_report(dwAlarmMsgType,dwAlarmCode,dwAlarmReason,ucAlarmLevel,pucAddInfo,ucAddInfoLen)\ 
//             usp_amp_reportAlarm(dwAlarmMsgType,dwAlarmCode,dwAlarmReason,ucAlarmLevel,pucAddInfo,ucAddInfoLen)            

#else

#define uhfDevPrint    logm_debug
#define UHFErrorPrint  logm_err
#define UHFAlertPrint  logm_alert
#define UHFWarningPrint  logm_warn
#define LAPInsert(FileId,exceptCode,var1,var2)  
#define uhf_amp_report(dwAlarmMsgType,dwAlarmCode,dwAlarmReason,ucAlarmLevel,pucAddInfo,ucAddInfoLen)

#endif


#if USP_OSS_PRINTF_USE
#define uhfRfDevPrint(...)    usp_oss_printf(USP_UHF_RF_TNO,USP_OSS_PRINTF_LEVEL_DEBUG,__VA_ARGS__)
#define UHFRfErrorPrint(...)   usp_oss_printf(USP_UHF_RF_TNO,USP_OSS_PRINTF_LEVEL_ERROR,__VA_ARGS__)
#define UHFRfAlertPrint(...)   usp_oss_printf(USP_UHF_RF_TNO,USP_OSS_PRINTF_LEVEL_ALERT,__VA_ARGS__)
#define UHFRfWarningPrint(...)   usp_oss_printf(USP_UHF_RF_TNO,USP_OSS_PRINTF_LEVEL_ALERT,__VA_ARGS__)
#else

#define uhfRfDevPrint   logm_debug
#define UHFRfErrorPrint  logm_err
#define UHFRfAlertPrint  logm_alert
#define UHFRfWarningPrint logm_warn
#endif



#define uhf_SetTestpin()    g_pvUSPDrvFpgaVirtStartAddr0[0x118]^=0x1;
#define uhfRf_SetTestpin()  g_pvUSPDrvFpgaVirtStartAddr0[0x20]^=0x1;

/*信令跟踪FPGA错误帧用到的宏*/
#define FPGATrace(wTraceLen) if(usp_cli_isTraceByTno(USP_FPGA_TNO))\
{\
  wTraceLen=FPGA_ERROR_TRACE_LEN*2;\
  uhf_SendTraceMsg(EV_FPGA_TO_RCP,EV_FPGA_UNKNOW_RESP,wTraceLen,g_awFpgaReadBuf);\
}

int g_iFpgaFd ;     /* file descriptor for fpga device     */

#endif


