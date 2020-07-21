/************************************************************************
* 版权所有 (C)2015, 上海华虹集成电路有限责任公司
* 
* 文件名称：phy7816-3.h
* 文件标识： 
* 内容摘要：psam驱动7816协议层实现头文件
* 其它说明： 
* 当前版本： 
* 作    者：
* 完成日期：2015.2.09
* 
************************************************************************/

/***********************************************************
 *                                      包含头文件                               *
 ***********************************************************/

#ifndef  __PHY7816_3__
#define  __PHY7816_3__


typedef struct tagT_7816_Ctl
{
    unsigned char   ucTimerClkRatio;   /* timer 计时频率和clk时钟频率的比率 */
    unsigned char   ucPad;
    unsigned short wEtu;             /* 每个bit传输占用的clk周期 */

    unsigned short w1BitTime;
    unsigned short w1HalfBitTime;    /* 1 .5个bit传输所占用的timer计数 */
    unsigned short w2HalfBitTime;   
    unsigned short w3HalfBitTime;   
    unsigned short w4HalfBitTime;   
    unsigned short w5HalfBitTime;   
    unsigned short w6HalfBitTime;   
    unsigned short w7HalfBitTime;   
    unsigned short w8HalfBitTime;   
    unsigned short w9HalfBitTime;   
    unsigned short w10HalfBitTime;
    unsigned short w11HalfBitTime;
    unsigned int dwOverflowFin;     /* 接收超时时timer的最大溢出次数 */
    unsigned int dwTimeFin;         

    unsigned char   ucTS;
    unsigned char   ucT0;
    unsigned char   ucTA1;
    unsigned char   ucTB1;
    unsigned char   ucTC1;
    unsigned char   ucTD1;
    unsigned char   ucTA2;
    unsigned char   ucTB2;
    unsigned char   ucTC2;
    unsigned char   ucTD2;
    unsigned char   ucGardEtu;
    unsigned char   ucPPSEn;

    unsigned int dwAtrLen;
    unsigned char   aucAtr[32];

    unsigned int dwHistLen;
    unsigned char   aucHistory[32];
            
}T_Phy7816_Ctl;

#define  PHY7816_DEBUG(...)

#define PROCESS_COMPLETED     0x9000
#define TRANSFER_RESPONSE     0x61
#define ABORTED_WRONG_LENGTH  0x67
#define ABORTED_LE_LENGTH     0x6C
#define ABORTED_INVALID_INS   0x6D00
#define CLASS_NOT_SUPPORTED   0x6E00
#define INCORRECT_P1P2        0x6A86




extern T_Phy7816_Ctl g_atPhy7816_Ctl[BSP_DRV_PSAM_NR];

void Phy7816_DelayClk(unsigned int dwClkNum);
void Phy7816_DelayEtu(unsigned char ucSockId, unsigned char ucEtuNum);
unsigned int Phy7816_Rcv(unsigned char ucSockId, unsigned char *pucBuf, unsigned short wLen);
unsigned int Phy7816_Snd(unsigned char ucSockId, unsigned char *pucBuf, unsigned short wLen);
unsigned int Phy7816_Active(unsigned char ucSockId, T_CardPara *ptCardPara);
void Phy7816_Deactive(unsigned char ucSockId);
unsigned int CPU_CardCmdProc(unsigned char ucSockId, unsigned char ucCmdLen, unsigned char *pucCmdApdu, unsigned char *pucResLen, unsigned char 
*pucResTpdu);
unsigned int Phy7816_RcvHistory(unsigned char ucSockId);
#endif



