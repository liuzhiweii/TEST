/************************************************************************
* 版权所有 (C)2010, 中兴通讯天津研究所
* 
* 文件名称： usp_ioexpander.h
* 文件标识： 
* 内容摘要： ioexpander模块对外接口头文件
* 其它说明： 
* 当前版本： USP01.20.06
* 作            者： 初德进
* 完成日期： 2010-12-30
* 
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/


#ifndef _USP_IOEXPANDER_H_
#define _USP_IOEXPANDER_H_




/*6700  I2C转并口芯片IO功能宏定义*/

/*RFCB单板类型*/
#define USP_IOE_RFCB_TYPE_ID          0x00
#define USP_IOE_RFCB_TYPE_ID_MASK     0x0F
#define USP_IOE_RFCB_TYPE_ID_POS      0x0

/*前向功率控制*/
#define USP_IOE_TX_DATT               0x01
#define USP_IOE_TX_DATT_MASK          0xFC
#define USP_IOE_TX_DATT_POS           0x02


/*天线开关阵列控制信号*/
#define USP_IOE_ANT_CONTROL           0x02
#define USP_IOE_ANT_CONTROL_MASK      0x03
#define USP_IOE_ANT_CONTROL_POS       0x0


/*反向DATT控制*/
#define USP_IOE_RX_DATT               0x03
#define USP_IOE_RX_DATT_MASK          0xFC
#define USP_IOE_RX_DATT_POS           0x2


/*反向低噪放使能开关*/
#define USP_IOE_RX_LNA_EN             0x04
#define USP_IOE_RX_LNA_EN_MASK        0x02
#define USP_IOE_RX_LNA_EN_POS         0x01



/*反向本振选择开关*/
#define USP_IOE_RX_LO_SEL             0x05
#define USP_IOE_RX_LO_SEL_MASK        0x01
#define USP_IOE_RX_LO_SEL_POS         0x0


/*反向解调器的本振衰减值*/
#define USP_IOE_RX_LO_DATT            0x06
#define USP_IOE_RX_LO_DATT_MASK       0xF8
#define USP_IOE_RX_LO_DATT_POS        0x03


/*功率检测通路选择*/
#define USP_IOE_PWRDET_SEL            0x07
#define USP_IOE_PWRDET_SEL_MASK       0x04
#define USP_IOE_PWRDET_SEL_POS        0x02


/*反向基带滤波通路选通*/
#define USP_IOE_ADG704_A              0x08
#define USP_IOE_ADG704_A_MASK         0x03
#define USP_IOE_ADG704_A_POS          0x0


/*RFCB单板的版本*/
#define USP_IOE_RFCB_VER_ID           0x09
#define USP_IOE_RFCB_VER_ID_MASK      0x3F
#define USP_IOE_RFCB_VER_ID_POS       0x0


/*编码为B的芯片所有功能*/
#define USP_IOE_ICB_FUN_ALL           0x0A
#define USP_IOE_ICB_FUN_ALL_MASK      0xFF
#define USP_IOE_ICB_FUN_ALL_POS       0x0


/*编码为C的芯片所有功能*/
#define USP_IOE_ICC_FUN_ALL           0x0B
#define USP_IOE_ICC_FUN_ALL_MASK      0xFF
#define USP_IOE_ICC_FUN_ALL_POS       0x0


/*编码为D的芯片所有功能*/
#define USP_IOE_ICD_FUN_ALL           0x0C
#define USP_IOE_ICD_FUN_ALL_MASK      0xFF
#define USP_IOE_ICD_FUN_ALL_POS       0x0




WORD32 usp_drv_ioexpander_init(void);
WORD32 usp_drv_ioexpander_snd(BYTE ucFID , WORD32 dwData);
WORD32 usp_drv_ioexpander_rcv (BYTE ucFID , WORD32 *dwData);


#endif


