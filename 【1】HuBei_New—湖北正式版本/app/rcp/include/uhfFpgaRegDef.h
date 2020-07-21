/************************************************************************
* 版权所有 (C)2008, 深圳市中兴通讯股份有限公司。
* 
* 文件名称： uhfFpgaRegs.h
* 文件标识： 
* 内容摘要： fpga协议相关的寄存器定义文件
* 其它说明： 
* 当前版本： 
* 作    者： ft
* 完成日期： 2009.03.10
* 
* 修改记录1：赵董兴
*    修改日期：2012.3.8
*    版 本 号：
*    修 改 人：
*    修改内容：去掉不用的一些寄存器和数据定义，根据
                                 RUP平台化要求进行修改。
* 修改记录2：…
************************************************************************/
#ifndef _FPGA_UHF_REG_H
#define _FPGA_UHF_REG_H
/**************************************************************************
 *                        常量                                            *
 **************************************************************************/

/**********************************************
               CPU与FPGA接口寄存器  
***********************************************/


#define reg_rb_module_type (0x0049)

/*
FPGA逻辑版本寄存器
    Bit15~Bit0
*/
#define REG_FPGA_VERSION  (0x0000)

/*
中断状态寄存器
Bit15~bit1 保留    
Bit0        frame_indic
frame_indic：FIFO中有新数据帧
*/
#define REG_INT_Status  (0x0001)

#define FPGA_INT_STATE_HAS_FRAME (0x1)

/*
中断屏蔽寄存器
Bit15~bit1保留    
Bit0        frame_indic mask
frame_indic mask ：帧接收中断屏蔽 
*/
#define REG_INT_Mask  (0x007D)

#define FPGA_INT_ENABLE   (1)
#define FPGA_INT_DISABLE  (0)

/*
中断使能寄存器，地址：0002H
Bit15~bit1保留
Bit0 int_enble
int_enble，总的中断禁止和使能位
1：使能中断
0：禁止向CPU发中断
*/
#define REG_INT_enable  (0x0002)


/*
读写测试寄存器
Bit15~Bit0
CPU读写测试，用户自定义
*/
#define REG_Fpga_test  (0x0003)


/*
CPU接收FIFO缓冲区帧计数器
Bit15~bit5保留    
Bit4~Bit0        frame_cnt
frame_cnt：当前FIFO中缓存的帧个数
*/
#define REG_FIFO_Frame_cnt  (0x0008)

/* MAC协议层寄存器 */
/*
协议类型寄存器
Bit15~Bit2   保留    
Bit1~Bit0        protocal type
protocal type：
00：EPC G2
01：18000-6B
10：中国标准
11：保留
*/
#define REG_PROTO_TYPE  (0x0004)


/*
CPU命令类型寄存器
保留    nak    blkerase    blkwrt    lock    kill    write    read    query    Select
Bit8~Bit0：1：CPU发出该命令，其余BIT为0；
*/
#define REG_CPU_CMD_type  (0x0005)

/*
CPU指示寄存器
BIT0 有效，上电默认为0,沿触发fpga 进行下一步操作
*/
#define REG_CPU_LLRP_CMD_Trig  (0x007a)

/*
CPU指示寄存器
Bit15~bit2  保留    
Bit1    stop mac    
Bit0        cmd_indic
cmd_indic：0跳变为1，CPU触发MAC命令开始工作
CPU需要在写操作命令类型寄存器之后，之后才能写入该位。
stop mac： 0跳变为1，CPU触发MAC命令停止工作
*/
#define REG_CPU_CMD_Trig  (0x007B)

/*
CPU指示寄存器
收发分离时DATT 的值
*/
#define REG_FPGA_AGC_VALUE  (0x007E)


/*
mac层公共状态寄存器
Bit1   MAC busy    
Bit0  frame indic 
 
frame indic：   1：FIFO中有数据帧，只要FIFO中帧个数大于0，该位一直为1。
MAC busy：   1：MAC状态机BUSY ；0：空闲
*/
#define REG_G2_mac_status  (0x0006)

/*
mac层自定义错误码寄存器
Bit5 EPC err    
Bit4 handel error
Bit3 tag error
Bit2 crc error
Bit1 Collision
Bit0 Timeout
Timeout：超时，无信号
Collision：碰撞
crc error：CRC校验错
tag error：标签返回错误码
handel error：handel不匹配
EPC err： EPC代码不匹配
*/
#define REG_G2_mac_selfdefine_error_code  (0x0007)

/*
CPU接收FIFO输出端口寄存器
Bit15~bit0        cpumsg_fifo_port
cpumsg_fifo_port：消息FIFO的输出端口寄存器，因FIFO只有一个输出端口，可以通过寄存器方式由CPU来访问。
16位宽度，与CPU到FPGA的数据总线宽度相同。
*/
#define REG_FPGA_FIFO   (0x000A)

/*
select命令参数寄存器
Bit8        Truncate    
Bit7~Bit6   MemBank    
Bit5~Bit3   action    
Bit2~Bit0   target
 
*/
#define REG_G2_Select_Para  (0x000B)


/*
select命令地址寄存器
Bit15~Bit8   EBV  BLOCK2    
Bit7~Bit0        EBV  BLOCK1
EBV  BLOCK1：   掩码开始地址的第1个EBV块
EBV  BLOCK2：   掩码开始地址的第2个EBV块
根据协议，每个EVB块中包含7个有效BIT和1个扩展指示BIT，两个连续的EBV可以表示的地址范围是0～16383。
根据目前的应用状况，该地址范围满足实际的需求。因此，目前只采用2个块来表示这个地址空间。
若要表示更大的地址空间，需要另外增加寄存器。 
*/
#define REG_G2_Select_Addr  (0x000C)


/*
select命令MASK寄存器
MASK word31
MASK word30
-----------
MASK word3
MASK word2
MASK word1
MASK word0
 
MASK寄存器组共32个，可以存储最多512个BIT的掩码。
该寄存器组可以看作一片连续的存储区，如同访问内存块。
*/
#define REG_G2_Select_Mask_Start     (0x10000)

#define REG_G2_BlockWrite_Data_Start (0x20000)


/*
query命令参数寄存器
其余保留    
Bit12～Bit9   Q     
Bit8          Target     
Bit7～Bit6    Session     
Bit5～Bit4    Sel    
Bit3          TRext     
Bit2～Bit1    M    
Bit0          DR
 
DR：      0: DR=8；    1: DR=64/3
M ：      00:M=1；   01: M=2；   10: M=4   11: M=8
TRext：   0: No pilot tone；    1: Use pilot tone
Sel：     00: All；    01: All；  10: ~SL；   11: SL
Session： 00: S0；   01: S1；  10: S2；     11: S3
Target：  0：A；    1：B；
Q：       0–15
*/
#define REG_G2_Query_Para  (0x002E)

/*
read命令MemBank寄存器
Bit15~Bit2
Bit1~Bit0 MemBank
MemBank：
00: Reserved 
01: EPC 
10: TID 
11: User
*/
#define REG_G2_Read_Membank  (0x002F)


/*
read命令地址寄存器
Bit15~Bit8   EBV  BLOCK2    
Bit7~Bit0        EBV  BLOCK1
EBV  BLOCK1：   掩码开始地址的第1个EBV块
EBV  BLOCK2：   掩码开始地址的第2个EBV块
根据协议，每个EVB块中包含7个有效BIT和1个扩展指示BIT，两个连续的EBV可以表示的地址范围是0～16383。
根据目前的应用状况，该地址范围满足实际的需求。因此，目前只采用2个块来表示这个地址空间。若要表示更大的地址空间，需要另外增加寄存器。
*/
#define REG_G2_Read_Addr  (0x0030)


/*
read命令读字个数寄存器
保留    
Bit7~Bit0        WordCount
WordCount：要读取得字的个数，最大256。
 
*/
#define REG_G2_Read_WordCount  (0x0031)

/*
write命令MemBank寄存器
Bit15~Bit2       Bit1~Bit0   MemBank     
MemBank：
00: Reserved 
01: EPC 
10: TID 
11: User
*/
#define REG_G2_Write_Membank  (0x0032)

/*
write命令地址寄存器
Bit15~Bit8   EBV  BLOCK2    
Bit7~Bit0        EBV  BLOCK1
EBV  BLOCK1：   掩码开始地址的第1个EBV块
EBV  BLOCK2：   掩码开始地址的第2个EBV块
根据协议，每个EVB块中包含7个有效BIT和1个扩展指示BIT，两个连续的EBV可以表示的地址范围是0～16383。
根据目前的应用状况，该地址范围满足实际的需求。因此，目前只采用2个块来表示这个地址空间。若要表示更大的地址空间，需要另外增加寄存器。
*/
#define REG_G2_Write_Addr  (0x0033)

/*
write命令数据寄存器
Bit15~Bit0           Data
Data:  16BIT，该命令用于单个数据的写操作
*/
#define REG_G2_Write_Data  (0x0034)

/*
write命令写个数寄存器（暂时不使用该寄存器）
保留    Bit7~Bit0        WordCount
WordCount：要写入字的个数，最大256。
该寄存器用于使用多个单字写操作命令连续写入多个字。
*/
#define REG_G2_Write_WordCount (0x0035)

/*
lock命令payload_mask寄存器，地址：0039H
保留
Bit9~Bit0 payload_mask
payload_mask：Lock指令包含一个20-bit的payload，定义如下：
前10个payload位为屏蔽位（Mask bit）。标签须按照如下意思理解这些位的值：
Mask=0：忽略相应的Action区域，并保留当前的锁定设置。
Mask=1：执行相应的Action区域，并覆盖当前的锁定设置。
后10位为Action bit。标签须按照如下意思理解这些位的值：
Action=0：撤销相应存储位置的锁定。
Action=1：设定相应存储位置为锁定或者永久锁定。
各Action区域的功能参看协议中表6.39。
Lock指令的payload须始终为20bit长
*/
#define REG_G2_Loc_payload_mask (0x0039)

/*
lock命令payload_Action寄存器，地址：003AH
保留
Bit9~Bit0 payload_Action
payload_Action：参见payload_mask寄存器的说明
*/
#define REG_G2_Loc_payload_Action (0x003A)

/* access命令密码（高半字）寄存器，地址：003BH
Bit15~Bit0 Password_h ( high half word)
Password_h: 32位access密码的高半字。
*/
#define REG_G2_Access_Password_h (0x003B)

/*access命令密码（低半字）寄存器，地址：003CH
Bit15~Bit0 Password_L ( low half word)
Password_L: 32位access密码的低半字。
*/
#define REG_G2_Access_Password_L (0x003C)


/*
blockwrite membank 寄存器，地址：003DH
保留
操作的membank号
*/
#define REG_G2_Block_Write_Membank (0x003D)


/*
blockwrite adress地址：003EH

payload_Action：参见payload_mask寄存器的说明
*/
#define REG_G2_Block_Write_Adress (0x003E)


/*
blockwrite 地址：003EH
payload_Action：参见payload_mask寄存器的说明
*/
#define REG_G2_Block_Write_Length (0x003F)

/*
kill命令密码（高半字）寄存器，地址：0036H
Bit15~Bit0 Password_h ( high half word)
Password_h: 32位密码的高半字。
*/
#define REG_G2_Kill_Password_h (0x0036)

/*kill命令密码（低半字）寄存器，地址：0037H
Bit15~Bit0 Password_L ( low half word)
Password_L: 32位密码的低半字。
*/
#define REG_G2_Kill_Password_L (0x0037)

/*
kill命令RFU寄存器，地址：0038H
保留
Bit2~Bit0 RFU
RFU： Kill指令包含三个RFU位。当阅读器与Class-1的标签通讯时，阅读器将这些位社为0002。Class-1标签忽略这几位。
更高功能的标签可以使用这些位来扩展Kill指令的功能（如，杀死一个标签使之进入一个可再生的状态，而不是直接杀死）
*/
#define REG_G2_Kill_RFU (0x0038)



#define REG_forward_filter_enable (0x0043)

#define REG_backward_filter_enable (0x0045)

/* ISO18000-6B的前导码类型寄存器，ISO18000_6B_forward_preamble_type，16位，地址：0048H
Bit15－bit2，保留	preamble_type
preamble_type
00：delimeter1
01：delimeter2
10：delimeter3
11：delimeter4
其他保留 */
#define ISO18000_6B_forward_preamble_type (0x0048)

#define ISO18000_6B_forward_delimeter1 (0x0)
#define ISO18000_6B_forward_delimeter2 (0x1)
#define ISO18000_6B_forward_delimeter3 (0x2)
#define ISO18000_6B_forward_delimeter4 (0x3)


/*
EPC G2协议的前向链路速率寄存器，G2_forlink_v，16位
Bit15-bit9，保留    
bit8-bit0   G2_FORLINK_V
G2_FORLINK_V：G2的R＝>T的链路bit速率，Bit8－bit0，G2的R＝>T的链路速率乘以2的值；其他位保留。例：G2的R＝>T的链路速率为40K，则该值为40×2＝80。
*/
#define G2_forlink_v  (0x004C)


/*
EPC G2协议的T1值寄存器，G2_t1_value，16位
G2_T1_VAL
G2_T1_VAL：G2协议中的T1对应的时间值，16位，该值作为接受等待计数器的参考值，配置以32M时钟作为基准计数器的计数值。例：T1为5uS，则该值为32000000×0.000005=160.
*/
#define G2_t1_value  (0x004D)


/*
EPC G2协议的T2值寄存器，G2_t2_value，16位
G2_T2_VAL
G2_T2_VAL：G2协议中的T1对应的时间值，该值为发送等待计数器的参考值，配置以26M时钟作为基准计数器的计数值。例：T2为5uS，则该值为26000000×0.000005=130.
*/
#define G2_t2_value  (0x004E)

/*
EPC G2协议的T4值寄存器，G2_t4_value，16位
G2_T4_VAL
G2_T4_VAL：G2协议中的T4对应的时间值，该值为接受窗口计数器的参考值，配置以26M时钟作为基准计数器的计数值。例：T4为5uS，则该值为26000000×0.000005=130.
*/
#define G2_t4_value  (0x0050)


/*
反向链路状态指示寄存器，phy_col_indicate，16位DET_SIGNAL，地址：0051H
Bit15-bit5，保留
DEC_ERR
BEY_MAXPLS
LOW_MINPLS
PRM_MATCH
DET_SIGNAL
DET_SIGNAL：是否检测到信号指示，1：检测到信号；0：没有检测到信号
PRM_MATCH：前导码匹配指示，1：匹配；0：没有匹配
LOW_MINPLS：波形检测模块检测到的脉冲小于最小有效脉冲宽度错误，1：出错；0：正常
BEY_MAXPLS：波形检测模块检测到的脉冲大于最大有效脉冲宽度错误，1：出错；0：正常
DEC_ERR：解码出错指示，1：出错；0：正常
*/
#define REG_reverse_link_status  (0x0051)


/*
EPC G2协议的标签编码类型寄存器，G2_tag_code_type，16位
Bit15-bit2，保留    
bit1-bit0   G2_tag_code_type
G2_tag_code_type
00：FM0
01：Miller
其他保留
*/
#define G2_tag_code_type  (0x0052)

/*
EPC G2协议的反向链路数据速率寄存器，G2_reverse_link_v，16位
G2_reverse_link_v
G2_reverse_link_v：G2中reader指定的T＝>R的链路速率，16位。例：反向速率为160K时，该值为160。
*/
#define G2_reverse_link_v  (0x0056)

/*
EPC G2协议前向前导码类型寄存器，G2_forward_preamble_type，16位
Bit15-bit10，保留        
Bit9-bit8,RTCal_Ta    
Bit7-bit0,TRCal_RTCal
Prm_type，前导码的类型
0：表示前导码类型为R＝>T的前导码
1：表示前导码类型为R＝>T的同步码
RTCal_Ta：RTcal与Tari的比值，目前暂定仅取3
TRCal_RTCal：TRcal与Tari的比值，
*/
#define G2_forward_preamble_type  (0x0047)

/*
EPC G2协议中反向链路数据前导码占用的时间值寄存器，G2_reverse_preamble_t_val，16位，地址：0058H
G2_reverse_preamble_t_val：G2的T＝>R的前导码占用的时间值，该值为接受窗口计数器的参考值，
配置以26M时钟作为基准计数器的计数值。例：T4为5uS，则该值为26000000×0.000005=130.
*/
#define G2_reverse_preamble_t_val  (0x0058)

/*
EPC G2协议中反向链路数据前导码占用的时间值高16位寄存器，G2_reverse_preamble_t_val_h，16位，地址：00b1H
G2_reverse_preamble_t_val_h
G2的T＝>R的前导码占用的时间值，该值为接受窗口计数器的参考值，配置以32M时钟作为基准计数器的计数值。例：T4为5uS，则该值为32000000×0.000005=130.
G2_reverse_preamble_t_val_l：该寄存器为G2的T＝>R的前导码占用的时间值高16位值
*/
#define G2_reverse_preamble_t_val_h (0x00b1)

/***********************************************************
               射频配置寄存器
************************************************************/ 


/* PLL配数寄存器高字,  Bit7-bit0：24位PLL配数的数据高八位 */
#define REG_PLL_DATA_H      (0x005F)

/* PLL配数寄存器低字,  Bit15-bit0：24位PLL配数的数据低16位 */
#define REG_PLL_DATA_L      (0x0060)


/* PLL配置触发寄存器，PLL_TRIG， 16位
Bit15-bit1，保留
bit0 PLL_TRIG
1：触发PLL配置模块开始配置PLL,表示软件已准备好配置数据，要去逻辑开始传送。
0：null
*/
#define REG_PLL_TRIG      (0x0061)

#define PLL_DATA_READY_TRIG  (0x1)

/* PLL准备好，PLL_READY，16位
Bit15-bit1，保留
bit0 PLL_RDY
1：当前逻辑数据已经传送完成，可已开始下一次PLL数据传送。
0：正在传送PLL配置数据，
*/
#define REG_PLL_READY      (0x0063)

#define PLL_CFG_RDY  (1)  /* 1：当前逻辑数据已经传送完成，可已开始下一次PLL数据传送。 */
#define PLL_CFG_BUSY (0)  /* 0：正在传送PLL配置数据， */


/*
耦合方式选择寄存器，COUPLE_TYPE，16位，，地址：0066H
Bit15-bit1，保留
COUPLE_SW
COUPLE_SW
1：DC补偿环路断开
0：DC补偿环路通
*/

#define REG_COUPLE_TYPE (0x0066)

/*
天线连接状态指示寄存器，ANT_STATUS，16位
Bit15-bit4，保留    
bit3-bit0   ANT_STAT3    ANT_ STAT 2    ANT_ STAT 1    ANT_ STAT 0
ANT_STAT0－ANT_STAT3分别对应0、1、2、3号天线
1：表示对应的天线端口有天线正常连接
0：表示对应的天线端口没有检测到有天线正常连接
*/
#define REG_ANT_STATUS      (0x0067)


/*
发送通道调制器关断使能寄存器，MOD_EN，16位，地址：0073H
Bit15-bit1，保留
MOD_EN
MOD_EN：
1：打开发送通道调制器
0：关断发送通道调制器
*/
#define REG_MOD_EN      (0x0073)


/*
功放开关控制寄存器，PA_EN，16位，地址：0074H
Bit15-bit2
bit1       PA_ENB
这个开关控制寄存器决定，阅读器的前向通道是否打开；
前向通道开启的触发条件应该为：
1、LBT侦听结果表明，该信道为空闲；
2、中间件下发清点或读写等前向操作。条件1若在非欧洲标准应用条件下，可不打开。
*/
#define REG_RF_TX_Ctrl  (0x0074)


/*
禁止DAC工作寄存器，DAC_SLEEP，地址：007CH
Bit15-bit1，保留
Dac_sleep
Dac_sleep
1：禁止dac工作
0：使能dac工作
*/
#define REG_DAC_SLEEP  (0x007c)


/*
Select命令长度寄存器 SELECT_LENTH 地址 000dH
Bit15-bit8 保留
Bit7-bit0 select_lenth
*/
#define REG_G2_Select_Mask_BitLen  (0x000d)


/*
采样信号的有效信号门限值寄存器，sam_valid_signal_val，16位，地址：0054H
Bit15-bit12，保留
sam_valid_signal_val
sam_valid_signal_val：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define REG_sam_valid_signal_val  (0x0054)


/* 下降沿门限值调整系数寄存器，signal_down_thresh_reg_factor，16位，地址：0055H
   Bit15-bit9，保留
   Bit7-bit0，Factor
    上升沿门限调制值寄存器，范围从1-128。建议配置为28 */

#define REG_signal_down_thresh_reg_factor  (0x0055)


/* 上升沿门限值调整系数寄存器，signal_up_thresh_reg_factor，16位，地址：0093H
   Bit15-bit9，保留
   Bit7-bit0，Factor
    上升沿门限调制值寄存器，范围从1-128。建议配置为跟下降沿相同的值 */
#define REG_signal_up_thresh_reg_factor  (0x0093)




/*DAC输出零值寄存器，DAC_DC_VALUE_REG，地址，0087H
Bit15-bit14，保留
Bit13－bit0,dac_dc_value
该值为DAC输出为0电平时对应的DAC的14位DAC输入数字值，本系统中设为2000H或1fffH，建议配置为2000H。复位默认值为2000h
*/ 
//#define DAC_DC_VALUE_REG 0x0087

/* 反向噪声门限控制寄存器，sam_valid_signal_ctrl，地址，0088H
Bit15-bit14，保留
bit0,sam_valid_signal_ctrl
Bit0:sam_valid_signal_ctrl
0：反向噪声门限由FPGA计算得出
1：反向噪声门限由CPU配置，则cpu需要配置sam_valid_signal_val寄存器，写入反向噪声门限
复位默认由FPGA计算
*/ 
//#define sam_valid_signal_ctrl 0x0088

/* CPU触发FPGA进行反向噪声门限测试寄存器，cpu_trig_noise_test_reg，地址，008aH
Bit15-bit14，保留
bit0, cpu_trig_noise_test
Bit0: cpu_trig_noise_test
CPU每次先向该位写入0，然后再写入1，触发FPGA进行反向噪声门限测试 
*/
#define cpu_trig_noise_test_reg 0x008a

/* FPGA进行反向噪声门限测量时打开功放后的延迟值高16位，noise_test_delay_val_h，地址，008bH
Bit15-bitt0, noise_test_delay_val_h
该值为FPGA测量出来的反向噪声门限值
FPGA进行反向噪声门限测量时，需要首先打开功放，然后延迟一段时间后再开始对ADC输入的采样数据进行门限测量。该延迟以26MHz时钟来计数，例要延迟10s，则该延迟的计数值应该设置为10×26000000即 F7F4900H。复位默认延迟值为1s。
该寄存器值为该延迟计数值的高16位。复位默认值为18cH
*/
#define noise_test_delay_val_h 0x008b

/* FPGA进行反向噪声门限测量时打开功放后的延迟值高16位，noise_test_delay_val_l，地址，008cH
Bit15-bitt0, noise_test_delay_val_l
该值为FPGA测量出来的反向噪声门限值
FPGA进行反向噪声门限测量时，需要首先打开功放，然后延迟一段时间后再开始对ADC输入的采样数据进行门限测量。该延迟以26MHz时钟来计数，
例要延迟10s，则该延迟的计数值应该设置为10×26000000即 F7F4900H。该寄存器值为该延迟的低16位。复位默认值为ba80H
*/
#define noise_test_delay_val_l 0x008c


/* FPGA进行反向噪声门限测量时统计的采样点数，noise_test_sampoint_cnt，地址，008dH
Bit15-bitt0, noise_test_sampoint_cnt
该值为FPGA测量出来的反向噪声门限值时统计的采样点数，FPGA进行噪声门限测量需要对一定数量的采样点数进行统计，找出最大和最小值相减即为测试出来的噪声门限值，建议设置为4000即FA0H。复位默认值为FA1H。
*/
#define noise_test_sampoint_cnt 0x008d

/*FPGA进行反向噪声门限测量的门限调整值， noise_test_adj_val，地址，008eH
Bit15-bitt0, noise_test_adj_val
通过实际测试发现，FPGA测量出来测门限值fpga_sam_valid_signal_val需要进行调整，一般为加上或减去一个值，该值由CPU通过noise_test_adj_val写入。复位默认为140H。
*/
#define noise_test_adj_val 0x008e



/* 反向噪声门限测量调整系数，fpga_noise_adj_factor，地址，0090H
Bit15-bit14，保留
bit0,sam_valid_signal_ctrl
Bit0:sam_valid_signal_ctrl
0：反向噪声门限值为fpga_sam_valid_signal_val－noise_test_adj_val
1：反向噪声门限值为fpga_sam_valid_signal_val＋noise_test_adj_val
复位默认为0。
配置要求：
改变G2_forward_preamble_type寄存器值时，必须超前于触发标签访问的信号2uS。
ASK调制时，module_depth调制深度寄存器值配置：目前假设DAC输出零电平对应2000H，DAC输出高电平即输出载波对应值为0000H。则调制深度假设为80％时，module_depth值计算如下：
1fffH－(1fffH-0000H)*80%
打开功放的前提条件：
配置DAC_SLEEP寄存器，使能DAC工作；配置配置MOD_EN寄存器，使能调制器工作；配置ANT_SEL寄存器，选择其中的一组天线，其中天线选择根据天线连接状态来配置，不能选择没有连接天线的端口；将来还要增加配置LBT_SWITCH，关闭LBT调节，目前的逻辑中暂没有该条件限制。必须满足以上条件，并且配置PA_EN寄存器，使能功放，功放才会打开，射频才有功率输出；否则即使PA_EN寄存器配置为使能功放，功放也不会打开。
*/
#define fpga_noise_adj_factor  0x0090


#define fpga_ant0_noise_thresh_val_i 0x009c

/*FPGA测试的天线0对应的I路噪声门限值，fpga_ant0_noise_thresh_val_q，16位，地址：009dH
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_ant0_noise_thresh_val_q 0x009d

/*FPGA测试的天线1对应的I路噪声门限值，fpga_ant1_noise_thresh_val_i，16位，地址：009eH
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_ant1_noise_thresh_val_i 0x009e


/*FPGA测试的天线1对应的I路噪声门限值，fpga_ant1_noise_thresh_val_q，16位，地址：009fH
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_ant1_noise_thresh_val_q 0x009f

/*FPGA测试的天线2对应的I路噪声门限值，fpga_ant2_noise_thresh_val_i，16位，地址：00a0H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_ant2_noise_thresh_val_i 0x00a0

/*FPGA测试的天线2对应的I路噪声门限值，fpga_ant2_noise_thresh_val_q，16位，地址：00a1H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_ant2_noise_thresh_val_q 0x00a1

/*
FPGA测试的天线3对应的I路噪声门限值，fpga_ant3_noise_thresh_val_i，16位，地址：00a2H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_ant3_noise_thresh_val_i    0x00a2

/* FPGA测试的天线3对应的I路噪声门限值，fpga_ant3_noise_thresh_val_q，16位，地址：00a3H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_ant3_noise_thresh_val_q 0x00a3

/* 调整fpga测试的门限值后的天线0对应的I路噪声门限值，fpga_adj_ant0_noise_thresh_val_i，16位，地址：00a4H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_adj_ant0_noise_thresh_val_i 0x00a4


/* 调整fpga测试的门限值后的天线0对应的I路噪声门限值，fpga_ adj_ant0_noise_thresh_val_q，16位，地址：00a5H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_adj_ant0_noise_thresh_val_q 0x00a5

/* 调整fpga测试的门限值后的天线1对应的I路噪声门限值，fpga_ adj_ant1_noise_thresh_val_i，16位，地址：00a6H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_adj_ant1_noise_thresh_val_i 0x00a6

/* 调整fpga测试的门限值后的天线1对应的I路噪声门限值，fpga_ adj_ant1_noise_thresh_val_q，16位，地址：00a7H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_adj_ant1_noise_thresh_val_q 0x00a7

/* 调整fpga测试的门限值后的天线2对应的I路噪声门限值，fpga_ adj_ant2_noise_thresh_val_i，16位，地址：00a8H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_adj_ant2_noise_thresh_val_i 0x00a8

/* 调整fpga测试的门限值后的天线2对应的I路噪声门限值，fpga_ adj_ant2_noise_thresh_val_q，16位，地址：00a9H
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_adj_ant2_noise_thresh_val_q 0x00a9

/* 调整fpga测试的门限值后的天线3对应的I路噪声门限值，fpga_ adj_ant3_noise_thresh_val_i，16位，地址：00aaH
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_adj_ant3_noise_thresh_val_i 0x00aa

/*调整fpga测试的门限值后的天线3对应的I路噪声门限值，fpga_ adj_ant3_noise_thresh_val_q，16位，地址：00abH
sam_valid_signal_val
ant0_noise_thresh_val_i：当采样点最大值与最小值差的一半大于该值时，认为有有效信号
*/
#define fpga_adj_ant3_noise_thresh_val_q 0x00ab

/* 反向噪声门限测量状态寄存器，fpga_noise_test_status，地址，00acH
Bit15-bit14，保留
bit0,noise_test_end
Bit0 noise_test_end
0：正在进行噪声门限测量，此时不能清点标签
1：反向噪声门限测量完成，可以清点标签
复位默认为0。
*/
#define fpga_noise_test_status 0x00ac

/* G2带有写标签操作的的命令的接受窗口超时计数器延迟时间值高16位，G2_write_rcv_delay_val_h，16位，地址：00adH
Bit15－bit0，G2_write_rcv_delay_val_h
该值为G2协议中带有写标签操作的的命令的接受窗口超时计数器延迟时间值高16位。G2带有写标签操作的的命令的接受窗口超时计数器延迟时间值配置以26M时钟作为基准计数器的计数值。例：T2为5uS，则该值为26000000×0.000005=130. 该值默认为20ms对应的时间值。
*/
#define G2_write_rcv_delay_val_h 0x00ad

/* G2带有写标签操作的的命令的接受窗口超时计数器延迟时间值低16位，G2_write_rcv_delay_val_l，16位，地址：00aeH
Bit15－bit0，G2_write_rcv_delay_val_l
该值为G2协议中带有写标签操作的的命令的接受窗口超时计数器延迟时间值低16位。G2带有写标签操作的的命令的接受窗口超时计数器延迟时间值配置以26M时钟作为基准计数器的计数值。例：T2为5uS，则该值为26000000×0.000005=130.该值默认为20ms对应的时间值。
*/
#define G2_write_rcv_delay_val_l 0x00ae

#define REG_fir_sig_down_thresh_factor  (0x00AF)
#define REG_fir_sig_up_thresh_factor  (0x00B0)


/*
DAC输出高电平值寄存器，DAC_HIGH_VALUE_REG，地址，0086H
Bit15-bit14，保留
Bit13－bit0,dac_high_value
该值为DAC输出载波时对应的DAC的14位DAC输入数字值，一般设置为3fffH或0000H，建议设置为3fffh
*/
#define REG_DAC_HIGH_VALUE_REG  (0x0086)

#define REG_FPGA_SAM_VALID_SIGNAL_CONTROL (0x0088)
#define REG_FPGA_SAM_VALID_SIGNAL_VAL     (0x0089)

/* 18000-6B 命令模式寄存器，地址：0012H
保留	Bit1~Bit0        18000B_cmd_mode
18000B_cmd_mode：
01：清点模式
10：直接命令访问模式
*/
#define REG_18000B_cmd_mode (0x0012)

#define ISO18000B_cmd_mode_invent        (0x1)
#define ISO18000B_cmd_mode_direct_access (0x2)
#define ISO18000B_cmd_mode_noinit_invent   (0x3)


/* 18000-6B 选择命令类型寄存器，地址：0013H
保留	Bit7~Bit0        18000B_selectcmd_typ
18000B_selectcmd_typ：与协议规定的命令码相同

*/
#define     GROUP_SELECT_EQ     0x00
#define     GROUP_SELECT_NE     0x01
#define     GROUP_SELECT_GT     0x02
#define     GROUP_SELECT_LT     0x03
#define     GROUP_UNSELECT_EQ   0x04
#define     GROUP_UNSELECT_NE   0x05
#define     GROUP_UNSELECT_GT   0x06
#define     GROUP_UNSELECT_LT   0x07

#define GROUP_SELECT_EQ_FLAGS   0x17
#define GROUP_SELECT_NE_FLAGS   0x18
#define GROUP_UNSELECT_EQ_FLAGS 0x19
#define GROUP_UNSELECT_NE_FLAGS 0x1A

#define REG_18000B_selectcmd_type (0x0013)

#define ISO18000B_selectcmd_type_GROUP_SELECT_EQ  (0x0)

/* 18000-6B 访问命令类型寄存器，地址：0014H
保留	Bit7~Bit0        18000B_accesscmd_typ
18000B_accesscmd_typ：与协议规定的命令码相同
0B： Recommended   DATA_READ
0C： Mandatory     READ
0D： Recommended   WRITE
0E： Recommended   WRITE_MULTIPLE
0F： Recommended   LOCK
11： Recommended   QUERY_LOCK
12： Recommended   READ_VERIFY
1B： Recommended   WRITE4BYTE
1C： Recommended   WRITE4BYTE_MULTIPLE
1D： Recommended   READ_VERIFY_4BYTE
*/
#define REG_18000B_accesscmd_type (0x0014)

#define ISO18000B_accesscmd_type_READ (0x000C)
#define ISO18000B_accesscmd_type_Variable_READ (0x0051)

/* add by mk */
#define ISO18000B_accesscmd_type_Write4Bytes (0x001B)
#define ISO18000B_accesscmd_type_WriteByte (0x000D)
#define ISO18000B_accesscmd_type_Lock (0x000F)
#define ISO18000B_accesscmd_type_LockQuery (0x0011) 
/* 18000-6B选择命令地址参数寄存器，地址：0015H
保留	Bit7~Bit0        18000B_sel_address
18000B_sel_address：标签从该地址开始，读取之后的存储器与阅读器发送的WORD_DATA进行比较
 */
#define REG_18000B_sel_address (0x0015)

/* 18000-6B选择命令掩码参数寄存器，地址：0016H
保留	Bit7~Bit0        18000B_sel_mask
18000B_sel_mask：参见标准的8.2.7.7.3 Data comparison for selection command on flags
Bit 7 (MSB) is set Consider D7 and FLAG7 for comparison
Bit 6 is set Consider D6 and FLAG6 for comparison
Bit 5 is set Consider D5 and FLAG5 for comparison
Bit 4 is set Consider D4 and FLAG4 for comparison
Bit 3 is set Consider D3 and FLAG3 for comparison
Bit 2 is set Consider D2 and FLAG2 for comparison
Bit 1 is set Consider D1 and FLAG1 for comparison
Bit 0 (LSB) is set Consider D0 and FLAG0 for comparison
Bit 7 (MSB) is cleared Ignore D7 and FLAG7 for comparison
Bit 6 is cleared Ignore D6 and FLAG6 for comparison
Bit 5 is cleared Ignore D5 and FLAG5 for comparison
Bit 4 is cleared Ignore D4 and FLAG4 for comparison
Bit 3 is cleared Ignore D3 and FLAG3 for comparison
Bit 2 is cleared Ignore D2 and FLAG2 for comparison
Bit 1 is cleared Ignore D1 and FLAG1 for comparison
Bit 0 (LSB) is cleared Ignore D0 and FLAG0 for comparison
 */
#define REG_18000B_sel_mask (0x0016)


/* 18000-6B选择命令WORD_DATA寄存器0，地址：0017H
Bit15~Bit0           18000B_sel_worddata_0
*/
#define REG_18000B_sel_worddata_0 (0x0017)

/* 18000-6B选择命令WORD_DATA寄存器1，地址：0018H
Bit15~Bit0           18000B_sel_worddata_1
*/
#define REG_18000B_sel_worddata_1 (0x0018)

/* 18000-6B选择命令WORD_DATA寄存器2，地址：0019H
Bit15~Bit0           18000B_sel_worddata_2
*/
#define REG_18000B_sel_worddata_2 (0x0019)

/* 18000-6B选择命令WORD_DATA寄存器3，地址：001AH
Bit15~Bit0           18000B_sel_worddata_3
*/
#define REG_18000B_sel_worddata_3 (0x001A)

/* 18000-6B FLAGS选择命令WORD_DATA寄存器3，地址：001BH
Bit15~Bit0           18000B_sel_worddata_3
*/
#define REG_18000B_sel_flags_Byte_data (0x001B)


/* 18000-6B访问命令UID寄存器0，地址：001CH
Bit15~Bit0          18000B_UID_reg_0 */
#define REG_18000B_access_UID_0 (0x001C)

/* 18000-6B访问命令UID寄存器1，地址：001DH
Bit15~Bit0          18000B_UID_reg_1 */
#define REG_18000B_access_UID_1 (0x001D)

/* 18000-6B访问命令UID寄存器2，地址：001EH
Bit15~Bit0          18000B_UID_reg_2 */
#define REG_18000B_access_UID_2 (0x001E)

/* 18000-6B访问命令UID寄存器3，地址：001FH
Bit15~Bit0          18000B_UID_reg_3 */
#define REG_18000B_access_UID_3 (0x001F)

/* 18000-6B访问命令地址参数寄存器，地址：0020H
保留	Bit7~Bit0        18000B_Address
18000B_Address：标签从该地址开始进行读写访问 */
#define REG_18000B_access_Address (0x0020) 

/* 18000-6B访问命令写数据寄存器0，地址：0021H */
#define REG_18000B_Read_Variable_Len  (0x0021)

/* add by mk */
/* 18000-6B访问命令写数据寄存器0，地址：0021H */
#define REG_18000B_write_data_0  (0x0021)

/* 18000-6B访问命令写数据寄存器1，地址：0022H */
#define REG_18000B_write_data_1  (0x0022)

/* 18000-6B访问命令写数据寄存器2，地址：0023H */
//#define REG_18000B_write_data_2  (0x0023)

/* 18000-6B访问命令写数据寄存器3，地址：0024H */
//#define REG_18000B_write_data_3  (0x0024)

/* 18000-6B写命令掩码参数寄存器，地址：0025H */
#define REG_18000B_write_bytemask  (0x0023) 
/* add by mk for 6B write */
/* 18000-6B 写命令后续是否有命令*/
#define REG_18000B_write_continue  (0x0024)



/*
硬件补丁，由Epld的偏移地址0x0184读取数值
 
当软件读EPLD料单版本寄存器值为01，就选择FPGA寄存器00BA=0。
当软件读EPLD料单版本寄存器值为00，就选择FPGA寄存器00BA=1。
*/
#define REG_FPGA_PATCH_VERSION    (0x00ba) 
/*
标签测速功能的寄存器
1、	多普勒频移周期寄存器 Doppler_shift_timer，地址：00BBH
2、	多普勒频移有效周期次数寄存器 Doppler_shift_times，地址：00BCH
*/
#define REG_DOPPLER_SHIFT_TIMER    (0x00BB)
#define REG_DOPPLER_SGIFT_TIMES    (0x00BC)

/* Added  by gaoyu for DATTControl, 2007年8月17日 10:01:17 */
/*
反向解调器本振衰减值寄存器 
Bit4 - Bit0为 rx_lo2_datt寄存器
可调节范围为0dbm - 15.5dbm 
*/
#define FPGA_TESTVERSION_CTRL  (0x00c5)

#define FPGA_RSSI_SWITCH    (0x00d4)



/*2010.1.26 cj add*/
/*
block lock命令MemBank寄存器地址005b
Bit15~Bit3 	BIT2:read/lock		Bit1~Bit0   MemBank     
MemBank：
00: Reserved 
01: EPC 
10: TID 
11: User
READ/LOCK:
0:read
1:lock
 
*/
#define REG_G2_Block_Lock_MemBank  (0x005b)


/*	Blockpermalock命令EVB地址寄存器，地址：005CH
Bit15~Bit8   EBV  BLOCK2	Bit7~Bit0        EBV  BLOCK1
以16个块为单位EBV  BLOCK1：   掩码开始地址的第1个EBV块
EBV  BLOCK2：   掩码开始地址的第2个EBV块
*/
#define REG_G2_Blcokpermalock_EVB (0x005c)


/*
Blockpermalock命令BLOCKRANGE锁定范围寄存器，地址：005DH
保留	Bit7~Bit0        Blockrange
Blockrange：块锁定范围，最大256个16blocks。
Blockpermalock命令数据寄存器，地址空间为20000H－2FFFFH，
总共128K，基址为20000H实际占用512字节(256个字)。
*/

#define REG_G2_Blockpermalock_Blockrange (0x005d)

/*Blockreadlock命令读块锁定命令（ALIEN标签）的块范围寄存器，地址：005eH
BIT15~BIT8:保留	Bit7~Bit0        blockcnt
*/


#define REG_G2_Blockreadlock_mask (0x005e)
/*2010.1.26add end*/

/* FPGA 在EPC协议中读写的重试次数寄存器*/
#define REG_FPGA_WRITE_READ_RETRY_TIME  (0x00d0)

/* FPGA 在ISO Q值设置寄存器*/
#define REG_FPGA_ISO6B_INVENTQ  (0x0076)



/* IPJ 配置的读写和状态模式*/
#define REG_I_QT_WR_PER  (0x0089)

/* IPJ指令的净荷*/
#define REG_I_QT_PAYLOAD  (0x008a)

////////////////////////
/// GB Reg Def
////////////////////////

#define ACCESS_KILL      0x10//0b00010000 
#define ACCESS_LOCK     0x32//0b00110010
#define ACCESS_READ     0x76//0b01110110
#define ACCESS_WRITE   0x98//0b10011000

#define REG_GB_Sort_Para  (0xC001)
#define REG_GB_Sort_Cmd_Ptr  (0xC002)
#define REG_GB_Sort_Cmd_BitLen  (0xC003)

#define REG_GB_Query_Para  (0xC004)

#define REG_GB_Read_Membank  (0xC005)
#define REG_GB_Read_Addr  (0xC006)
#define REG_GB_Read_WordCount  (0xC007)

#define REG_GB_Write_Membank  (0xC008)
#define REG_GB_Write_Addr  (0xC009)
#define REG_GB_Write_WordCount (0xC00A)

/* LOCK 命令参数 */
#define REG_GB_Lock_Para   (0xC00B)

/*
  access 访问存储区命令
  bit0-bit5 存储区
  bit6-bit9 口令类别
*/
#define REG_GB_Access_Membank (0xC00C)

#define REG_GB_Access_Password_L (0xC00D)
#define REG_GB_Access_Password_H (0xC011)

/* ERASE 命令参数 */

#define REG_GB_Erase_Membank        (0xC00E)
#define REG_GB_Erase_Addr               (0xC00F)
#define REG_GB_Erase_WordCount     (0xC010)

/*
select/sort命令MASK寄存器
MASK word31
MASK word30
-----------
MASK word3
MASK word2
MASK word1
MASK word0
 
MASK寄存器组共32个，可以存储最多512个BIT的掩码。
该寄存器组可以看作一片连续的存储区，如同访问内存块。
*/
#define REG_GB_Select_Mask_Start     (0x10000)

#define REG_GB_BlockWrite_Data_Start (0x20000)
/* FPGA 在EPC协议中读写的重试次数寄存器*/
#define REG_GB_FPGA_WRITE_READ_RETRY_TIME  (0x00d0)

/*
kill命令密码（高半字）寄存器，地址：0036H
Bit15~Bit0 Password_h ( high half word)
Password_h: 32位密码的高半字。
*/
#define REG_GB_Kill_Password_H (0x0036)

/*kill命令密码（低半字）寄存器，地址：0037H
Bit15~Bit0 Password_L ( low half word)
Password_L: 32位密码的低半字。
*/
#define REG_GB_Kill_Password_L (0x0037)

/*
kill命令RFU寄存器，地址：0038H
保留
Bit2~Bit0 RFU
RFU： Kill指令包含三个RFU位。当阅读器与Class-1的标签通讯时，阅读器将这些位社为0002。Class-1标签忽略这几位。
更高功能的标签可以使用这些位来扩展Kill指令的功能（如，杀死一个标签使之进入一个可再生的状态，而不是直接杀死）
*/
#define REG_GB_Kill_RFU (0x0038)

#endif


