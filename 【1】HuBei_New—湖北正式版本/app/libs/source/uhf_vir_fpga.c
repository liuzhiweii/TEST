//#include "usp.h"

//#if (USP_VIR_TAG_USE) && (UHF_BOARD_TYPE !=BOARD_TYPE_RFCB2)
#include <zmq.h>
#include "usp_typeDef.h"
#include "usp_pub.h"
#include "usp_vos.h"
#include "usp_ipc.h"
#include "usp.conf"
#include "scp.conf"
#include "usp_eventDef.h"
#include "uhfFpgaRegDef.h"
#include "uhf_vir_fpga.h"
#include "uhf_vir_tag.h"

static WORD16 s_awVirFpgaRegTable[VIR_FPGA_REG_TABLE_SIZE];
static WORD16 s_awVirFpgaSelectMaskReg[VIR_FPGA_SELECT_MASK_LEN];
static WORD16 s_awVirFpgaBlockDataReg[VIR_FPGA_BLOCK_DATA_LEN];

USP_OssIpcMutex g_tUSPVirFpgaMutex;
WORD16 *g_pwUSPVirFpgaFrameBuf = NULL;  
WORD32 *g_pdwUspVirFpgaFrameReadyFlag = NULL; 

void *push_socket = NULL;

WORD32 usp_oss_vos_createMutex(USP_OssVosMutex *pMutex, WORD16 wMutexKey)
{        
    union semun 
    {
        int val;
        unsigned short *array;
		
    } sem_union;/*in the manul says that you have to declare your own.*/
	
    *pMutex = semget((key_t)wMutexKey, 1, 0666 | IPC_CREAT);
    if (-1 == *pMutex)
    {
        return 0xF0003000;
    }
    
	/*初始化信号量*/
    /*lint -save -e437 */
	sem_union.val = 1;
	if (-1 == semctl(*pMutex, 0, SETVAL, sem_union))
	{
		return 0xF0003001;	
	}
    /*lint -restore */
    
    return USP_SUCCESS;
}

WORD32 usp_oss_vos_takeMutex(USP_OssVosMutex mutex, WORD32 dwFlag)
{
    struct sembuf tSemBuf;

    if (USP_OSS_VOS_MUTEX_INVALID == mutex)
    {
        return 0xF0003002;
    }

    tSemBuf.sem_op = -1;
    tSemBuf.sem_num = 0;
    tSemBuf.sem_flg = SEM_UNDO;

    semop(mutex, &tSemBuf, 1);
    
    return USP_SUCCESS;
}

WORD32 usp_oss_vos_giveMutex(USP_OssVosMutex mutex)
{
    struct sembuf tSemBuf;

    if (USP_OSS_VOS_MUTEX_INVALID == mutex)
    {
        return 0xF0003003;
    }

    tSemBuf.sem_op = 1;
	tSemBuf.sem_num = 0;
    tSemBuf.sem_flg = SEM_UNDO;

    semop(mutex, &tSemBuf, 1);
    
    return USP_SUCCESS;
}



void create_vir_fpga_socket(void *ctx)
{
    int ret;
    
    push_socket = zmq_socket(ctx, ZMQ_PUSH);
	if(NULL == push_socket)
	{
		printf("create push_socket fail!\n");
		exit(-1);
	}

	ret = zmq_connect(push_socket, "tcp://127.0.0.1:5111");
	if(0 < ret)
	{
	    printf("connect to vir_tag fail!\n");
	    exit(-1);
	}
}

/*****************************************************************************
 函 数 名  : vir_fpga_fillRegs
 功能描述  : 根据寄存器表的值，填写有效寄存器数据结构
 输入参数  : T_VirTagEffectiveRegs *ptRegs
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月28日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_fpga_fillRegs(T_VirTagEffectiveRegs *ptRegs)
{
    ptRegs->wREG_CPU_CMD_type = s_awVirFpgaRegTable[REG_CPU_CMD_type];
    ptRegs->wREG_PROTO_TYPE = s_awVirFpgaRegTable[REG_PROTO_TYPE];
    ptRegs->wREG_G2_Select_Addr = s_awVirFpgaRegTable[REG_G2_Select_Addr];
    ptRegs->wREG_G2_Select_Mask_BitLen = s_awVirFpgaRegTable[REG_G2_Select_Mask_BitLen];
    ptRegs->wREG_G2_Select_Para = s_awVirFpgaRegTable[REG_G2_Select_Para];
    ptRegs->wREG_G2_Query_Para = s_awVirFpgaRegTable[REG_G2_Query_Para];
    ptRegs->wREG_G2_Access_Password_h = s_awVirFpgaRegTable[REG_G2_Access_Password_h];
    ptRegs->wREG_G2_Access_Password_L = s_awVirFpgaRegTable[REG_G2_Access_Password_L];
    ptRegs->wREG_I_QT_WR_PER = s_awVirFpgaRegTable[REG_I_QT_WR_PER];
    ptRegs->wREG_I_QT_PAYLOAD = s_awVirFpgaRegTable[REG_I_QT_PAYLOAD];
    ptRegs->wREG_G2_Read_Membank = s_awVirFpgaRegTable[REG_G2_Read_Membank];
    ptRegs->wREG_G2_Read_Addr = s_awVirFpgaRegTable[REG_G2_Read_Addr];
    ptRegs->wREG_G2_Read_WordCount = s_awVirFpgaRegTable[REG_G2_Read_WordCount];
    ptRegs->wREG_G2_Write_Membank = s_awVirFpgaRegTable[REG_G2_Write_Membank];
    ptRegs->wREG_G2_Write_Addr = s_awVirFpgaRegTable[REG_G2_Write_Addr];
    ptRegs->wREG_G2_Write_WordCount = s_awVirFpgaRegTable[REG_G2_Write_WordCount];
    ptRegs->wREG_G2_Block_Write_Membank = s_awVirFpgaRegTable[REG_G2_Block_Write_Membank];
    ptRegs->wREG_G2_Block_Write_Adress = s_awVirFpgaRegTable[REG_G2_Block_Write_Adress];
    ptRegs->wREG_G2_Block_Write_Length = s_awVirFpgaRegTable[REG_G2_Block_Write_Length];
    ptRegs->wREG_G2_Loc_payload_mask = s_awVirFpgaRegTable[REG_G2_Loc_payload_mask];
    ptRegs->wREG_G2_Loc_payload_Action = s_awVirFpgaRegTable[REG_G2_Loc_payload_Action];
    ptRegs->wREG_G2_Kill_Password_h = s_awVirFpgaRegTable[REG_G2_Kill_Password_h];
    ptRegs->wREG_G2_Kill_Password_L = s_awVirFpgaRegTable[REG_G2_Kill_Password_L];
    ptRegs->wREG_G2_Kill_RFU = s_awVirFpgaRegTable[REG_G2_Kill_RFU];
    ptRegs->wREG_G2_Block_Lock_MemBank = s_awVirFpgaRegTable[REG_G2_Block_Lock_MemBank];
    ptRegs->wREG_G2_Blcokpermalock_EVB = s_awVirFpgaRegTable[REG_G2_Blcokpermalock_EVB];
    ptRegs->wREG_G2_Blockpermalock_Blockrange = s_awVirFpgaRegTable[REG_G2_Blockpermalock_Blockrange];
    ptRegs->wREG_G2_Blockreadlock_mask = s_awVirFpgaRegTable[REG_G2_Blockreadlock_mask];

    return;
}

/*****************************************************************************
 函 数 名  : vir_fpga_startMacCmd
 功能描述  : 触发fpga开始工作
 输入参数  : WORD16 wMsgId
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月28日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_fpga_startMacCmd(WORD16 wMsgId)
{
    WORD32 adwSendMsgBuf[512];
    WORD32 dwRet;


    T_Msg *ptMsg = (T_Msg *) & (adwSendMsgBuf[0]);
    T_VirTagEffectiveRegs *ptRegs = (T_VirTagEffectiveRegs *)(ptMsg + 1);
    void *pSelectMaskAddr = ptRegs + 1;
    void *pBlockDataAddr = pSelectMaskAddr + sizeof(s_awVirFpgaSelectMaskReg);

    ptMsg->mtype = 1;
    ptMsg->wMsgID = wMsgId;
    ptMsg->wMsgLen = sizeof(T_VirTagEffectiveRegs) + sizeof(s_awVirFpgaSelectMaskReg) \
                     +sizeof(s_awVirFpgaBlockDataReg);

    vir_fpga_fillRegs(ptRegs);
    memcpy(pSelectMaskAddr, &s_awVirFpgaSelectMaskReg[0], sizeof(s_awVirFpgaSelectMaskReg));
    memcpy(pBlockDataAddr, &s_awVirFpgaBlockDataReg[0], sizeof(s_awVirFpgaBlockDataReg));

    //dwRet = usp_oss_scp_sendTaskMsg(USP_VIR_TAG_TNO, ptMsg, USP_OSS_IPC_FOREVERWAIT);
    dwRet = zmq_send(push_socket, ptMsg, (ptMsg->wMsgLen + sizeof(T_Msg)), 0);
    if(0 != dwRet)
    {
        vir_fpga_debug("(vir_fpga) send cmd msg fail \r\n");
    }
    else
    {
        vir_fpga_debug("(vir_fpga) send cmd msg success \r\n");
    }

    return;
}


/*****************************************************************************
 函 数 名  : vir_fpga_startLlrpCmd
 功能描述  : 开始单个标签的命令，不会执行select query
 输入参数  : void
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_fpga_startLlrpCmd(void)
{
    vir_fpga_debug("(vir_fpga) send start llrp cmd \r\n");
    vir_fpga_startMacCmd(EV_USP_VIR_TAG_StartLlrpCmd);
    return;
}

/*****************************************************************************
 函 数 名  : vir_fpga_startCmd
 功能描述  : 开始标签命令，先要执行select和query
 输入参数  : void
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月28日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_fpga_startCmd(void)
{
    vir_fpga_debug("(vir_fpga) send start cmd \r\n");
    vir_fpga_startMacCmd(EV_USP_VIR_TAG_StartCmd);
    return;
}


/*****************************************************************************
 函 数 名  : vir_fpga_stopMacCmd
 功能描述  : 触发fpga停止工作，恢复到初始状态
 输入参数  : void
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月28日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void vir_fpga_stopMacCmd(void)
{
    WORD32 adwSendMsgBuf[256];

    vir_fpga_debug("(vir_fpga) send stop mac cmd \r\n");

    T_Msg *ptMsg = (T_Msg *) & (adwSendMsgBuf[0]);

    ptMsg->mtype = 1;
    ptMsg->wMsgID = EV_USP_VIR_TAG_StopCmd;
    ptMsg->wMsgLen = 0;
    //usp_oss_scp_sendTaskMsg(USP_VIR_TAG_TNO, ptMsg, USP_OSS_IPC_FOREVERWAIT);

    
    zmq_send(push_socket, ptMsg, (ptMsg->wMsgLen + sizeof(T_Msg)), 0);
    return;
}


void *vir_fpga_mallocShm(WORD16 wKey, WORD32 dwSize)
{
    SWORD32 sdwShmId;
    void * ret;
    sdwShmId = shmget((key_t)wKey, 0, 0666);
    printf("sdwshmid = %x\r\n",sdwShmId);
    if(-1 != sdwShmId)
    {
        //return shmat(sdwShmId, (void *)0, SHM_RND);
        ret = shmat(sdwShmId, (void *)0, SHM_RND);
        printf("-1 != sdwShmId  shmat = %x\r\n",ret);
        return ret;
    }
    else
    {
        sdwShmId = shmget((key_t)wKey, dwSize, 0666|IPC_CREAT);
        printf("-1 == sdwShmId sdwshmid = %x\r\n",sdwShmId);
        if(sdwShmId < 0)
        {
            return NULL;
        }
        else
        {
            //return shmat(sdwShmId, (void *)0, SHM_RND);
            ret = shmat(sdwShmId, (void *)0, SHM_RND);
            printf("sdwShmId > 0 shmat = %x\r\n",ret);
            return ret;
        }
    }
}


/*****************************************************************************
 函 数 名  : usp_vir_tag_initReg
 功能描述  : 初始化虚拟FPGA寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月21日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/

void usp_vir_fpga_initReg(void)
{
    s_awVirFpgaRegTable[REG_PLL_READY] = 0x01;

    usp_oss_vos_createMutex(&g_tUSPVirFpgaMutex, USP_VIR_TAG_MUTEX_KEY);
    g_pwUSPVirFpgaFrameBuf = (WORD16 *)vir_fpga_mallocShm(USP_VIR_TAG_SHM_KEY, VIR_TAG_SHM_SIZE);
    
    g_pdwUspVirFpgaFrameReadyFlag = (WORD32 *)vir_fpga_mallocShm(USP_VIR_TAG_SHM1_KEY, sizeof(WORD32));
    memset(g_pwUSPVirFpgaFrameBuf, 0, VIR_TAG_SHM_SIZE);
    memset(g_pdwUspVirFpgaFrameReadyFlag, 0, sizeof(WORD32));
       
    return;
}


/*****************************************************************************
 函 数 名  : vir_fpga_writeReg
 功能描述  : 此函数截获了Rcp模块对FPGA的写入操作
 输入参数  : WORD16 wAddr
             WORD16 wData
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月17日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
void usp_vir_fpga_writeReg(WORD32 wAddr, WORD16 wData)
{
    vir_tag_debug("(vir_fpga) write addr is %04X, wData is %04X \r\n", wAddr, wData);
    if (wAddr == REG_Fpga_test)
    {
        s_awVirFpgaRegTable[wAddr] = ~wData;
    }
    else if (wAddr == REG_CPU_LLRP_CMD_Trig)
    {
        if ((s_awVirFpgaRegTable[wAddr] & 0x01) == ((~wData) & 0x01))
        {
            /* 开始动作 */
            vir_fpga_startLlrpCmd();
        }
        else
        {
            s_awVirFpgaRegTable[wAddr] = wData;
        }
    }
    else if (wAddr == REG_CPU_CMD_Trig)
    {
        if (wData & 0x02)
        {
            /*stop mac*/
            vir_fpga_stopMacCmd();
        }
        else if (wData & 0x01)
        {
            /* start mac */
            vir_fpga_startCmd();
        }
        else
        {
            s_awVirFpgaRegTable[wAddr] = wData;
        }
    }
    else if ((wAddr >= REG_G2_Select_Mask_Start) && (wAddr <= (REG_G2_Select_Mask_Start + 31)))
    {
        s_awVirFpgaSelectMaskReg[wAddr - 0x10000] = wData;
    }
    else if ((wAddr >= REG_G2_BlockWrite_Data_Start) && (wAddr <= (REG_G2_BlockWrite_Data_Start + 31)))
    {
        s_awVirFpgaBlockDataReg[wAddr - REG_G2_BlockWrite_Data_Start] = wData;
    }
    else
    {
        s_awVirFpgaRegTable[wAddr] = wData;
    }
}

/*****************************************************************************
 函 数 名  : vir_fpga_readReg
 功能描述  : 此函数截获了Rcp模块对FPGA的读操作
 输入参数  : WORD16 wAddr
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月17日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
WORD16 usp_vir_fpga_readReg(WORD32 wAddr)
{
    if (wAddr < VIR_FPGA_REG_TABLE_SIZE)
    {
        return s_awVirFpgaRegTable[wAddr];
    }
    else
    {
        return 0;
    }
}

void vir_fpga_takeMutex(void)
{
    vir_fpga_debug("(vir_fpga) take mutex \r\n");
    usp_oss_vos_takeMutex(g_tUSPVirFpgaMutex, 0);
    vir_fpga_debug("(vir_fpga) take mutex success \r\n");
    return;
}

void vir_fpga_giveMutex(void)
{
    vir_fpga_debug("(vir_fpga) give mutex \r\n");
    usp_oss_vos_giveMutex(g_tUSPVirFpgaMutex);
    vir_fpga_debug("(vir_fpga) give mutex success \r\n");

    return;
}

/*****************************************************************************
 函 数 名  : usp_vir_fpga_readFrame
 功能描述  : 截获了Rcp模块从FPGA中读取响应帧的操作
 输入参数  : WORD16 *pwReadLen
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年9月19日
    作    者   : 侯晓凡
    修改内容   : 新生成函数

*****************************************************************************/
WORD32 usp_vir_fpga_readFrame(BYTE *pucDataPacket, WORD32 dwDataLen, WORD32 *pdwReadLen)
{
    WORD32 dwTryNum = 0;
    WORD32 dwReadLen = 0;


    while(dwTryNum < 100)
    {
        vir_fpga_takeMutex();
        if(*g_pdwUspVirFpgaFrameReadyFlag == TRUE)
        {
            //vir_fpga_debug("(vif_fpga) frame is ready \r\n");
            if(dwDataLen < (g_pwUSPVirFpgaFrameBuf[VIR_TAG_FPGA_FRAME_LEN]+1)*2)
            {
                dwReadLen = dwDataLen;
            }
            else
            {
                dwReadLen = (g_pwUSPVirFpgaFrameBuf[VIR_TAG_FPGA_FRAME_LEN]+1)*2;
            }
            memcpy(pucDataPacket, &g_pwUSPVirFpgaFrameBuf[0], dwReadLen);            
            *g_pdwUspVirFpgaFrameReadyFlag = FALSE;
            vir_fpga_giveMutex();
            *pdwReadLen = dwReadLen;
            return 0;
        }        
        else
        {
            vir_fpga_debug("(vir_fpga) frame not ready \r\n");
        }
        vir_fpga_giveMutex();
        dwTryNum++;
        usleep(100);
    }

    *pdwReadLen = 0;
    return -1;
}


//#endif



