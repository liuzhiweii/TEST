/***************************************************************************
* 版权所有:
*
* 文件名称：
* 文件标识：
* 内容摘要：
* 其它说明：
* 当前版本：
* 作    者：
* 完成日期：
*
* 修改记录1：
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
**********************************************************************/
#ifdef CFG_UHF
#include "cfg.h"
#include "cfgUhf.h" 
/***********************************************************
 *                        包含头文件                       *
 **********************************************************/


/***********************************************************
 *                     常量定义                            *
***********************************************************/

/***********************************************************
*                 文件内部使用的宏                         *
***********************************************************/

/***********************************************************
*               文件内部使用的数据类型                    *
***********************************************************/

/***********************************************************
 *                     全局变量                            *
***********************************************************/      
extern JSON_Object *root_object;
/***********************************************************
 *                     本地变量                            *
***********************************************************/

/***********************************************************
 *                     全局函数                            *
***********************************************************/

/***********************************************************
 *                     局部函数                            *
***********************************************************/
int check_antenna_cfg(JSON_Object *antenna_obj)
{
   int loop=0;
   int rc =0;
   int hop_table_num=0;
   int pointer;
   int maskbitlen,membank;
   JSON_Object *C1G2InvCmd_obj;
   JSON_Object *ISO6BInvCmd_obj;
   JSON_Object *GBInvCmd_obj;
   CFG_DEBUG("come into check_antenna_cfg\r\n");
   CHECK_NULL_POINTER_RETURN_INT(antenna_obj);
   
   rc=check_object_between_min_max(antenna_obj,"AntennaID",1,4);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(antenna_obj,"RFTransmitter.ChannelIndex",0,64);
   CHECK_NONZERO_NUMBER(rc);

   /*判断频率*/
   if (1)
    { /*800M*/
        hop_table_num = HOP_TALBE_800M_MAXNUM - 1;
    }
    else
    { /*900M*/
        hop_table_num = HOP_TALBE_900M_MAXNUM - 1;
    }
   rc=check_object_between_min_max(antenna_obj,"RFTransmitter.HopTableID",0,hop_table_num);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(antenna_obj,"RFTransmitter.TransmitPower",0,CFG_ANT_POWER_MAX - CFG_ANT_POWER_MIN);
   CHECK_NONZERO_NUMBER(rc);

   //C1G2InventoryCommand
   C1G2InvCmd_obj=json_object_dotget_object(antenna_obj,"AirProtocolInventoryCommandSettings.C1G2InventoryCommand");
   
   rc=check_object_between_min_max(C1G2InvCmd_obj,"C1G2Filter.FilterNum",0,MaxEPCSelectNum);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TruncateAction",1,1);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TagInventoryMask.MB",1,3);
   CHECK_NONZERO_NUMBER(rc);

   pointer=(int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TagInventoryMask.Pointer");
   maskbitlen=(int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TagInventoryMask.MaskBitLen");
   membank=(int)json_object_dotget_number(C1G2InvCmd_obj,"C1G2Filter.C1G2Filter1.C1G2TagInventoryMask.MB");

   if(1==membank)
   	{
   	   rc=check_value_between_min_max(maskbitlen+pointer,0,160);
       CHECK_NONZERO_NUMBER(rc);
   	}
   else
   {
   	   rc=check_value_between_min_max(maskbitlen+pointer,0,512);
       CHECK_NONZERO_NUMBER(rc);
   	}

   rc=check_object_between_min_max(C1G2InvCmd_obj,"C1G2RFControl.ModeIndex",0,EPC_RFMODE_TABLE_LEN - 1);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(C1G2InvCmd_obj,"C1G2SingulationControl.TagPopulation",1,65535);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(C1G2InvCmd_obj,"C1G2SingulationControl.TagPopulation",1,65535);
   CHECK_NONZERO_NUMBER(rc);

	//6BInventoryCommand
   ISO6BInvCmd_obj =json_object_dotget_object(antenna_obj,"AirProtocolInventoryCommandSettings.6BInventoryCommand");
   rc=check_object_between_min_max(ISO6BInvCmd_obj,"6BFilter.GroupSelectNum",0,MaxISO6BGroupSelectNum);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(ISO6BInvCmd_obj,"6BFilter.6BFilter1.Address",0,208);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(ISO6BInvCmd_obj,"6BFilter.6BFilter1.CommandType",0,7);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(ISO6BInvCmd_obj,"6BFilter.6BFilter1.WordDataLen",8,8);
   CHECK_NONZERO_NUMBER(rc);

   
   rc=check_object_between_min_max(ISO6BInvCmd_obj,"6BRFControl.ModeIndex",0,ISO6B_RFMODE_TABLE_LEN - 1);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(ISO6BInvCmd_obj,"6BSingulationControl.TagPopulation",1,65535);
   CHECK_NONZERO_NUMBER(rc);

	//GBInventoryCommand
    GBInvCmd_obj=json_object_dotget_object(antenna_obj,"AirProtocolInventoryCommandSettings.GBInventoryCommand");

	rc=check_object_between_min_max(GBInvCmd_obj,"GBFilter.FilterNum",0,MaxGBSortNum);
    CHECK_NONZERO_NUMBER(rc);

	rc=check_object_between_min_max(GBInvCmd_obj,"GBFilter.GBFilter1.GBTagInventoryStateAwareFilterAction.Action",0,3);
    CHECK_NONZERO_NUMBER(rc);

	rc=check_object_between_min_max(GBInvCmd_obj,"GBFilter.GBFilter1.GBTagInventoryStateAwareFilterAction.Target",0,4);
    CHECK_NONZERO_NUMBER(rc);

	rc=check_object_between_min_max(GBInvCmd_obj,"GBFilter.GBFilter1.GBTagInventoryStateAwareFilterAction.Target",0,4);
    CHECK_NONZERO_NUMBER(rc);
	   pointer=(unsigned short int)json_object_dotget_number(GBInvCmd_obj,"GBFilter.GBFilter1.GBTargetTagMask.Pointer");
	   maskbitlen=(unsigned short int)json_object_dotget_number(GBInvCmd_obj,"GBFilter.GBFilter1.GBTargetTagMask.MaskBitLen");
	   membank=(unsigned short int)json_object_dotget_number(GBInvCmd_obj,"GBFilter.GBFilter1.GBTargetTagMask.MB");
       if((membank==0)||(membank==0x10)||(membank==0x20)||((membank>=0x30)&&(membank<=0x3F)))
       	{
       	    ;
       	}
	   else
	   	{
	   	   CHECK_NONZERO_NUMBER(-1);
	   	}
	   	if(0x10==membank)
   	{
   	   rc=check_value_between_min_max(maskbitlen+pointer,0,250);
       CHECK_NONZERO_NUMBER(rc);
   	}
   else
   {
   	   rc=check_value_between_min_max(maskbitlen+pointer,0,512);
       CHECK_NONZERO_NUMBER(rc);
   	}

   rc=check_object_between_min_max(GBInvCmd_obj,"GBRFControl.ModeIndex",0, GB_RFMODE_TABLE_LEN - 1);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(GBInvCmd_obj,"GBSingulationControl.CCN",1,10);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(GBInvCmd_obj,"GBSingulationControl.CIN",1,10);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(GBInvCmd_obj,"GBSingulationControl.Session",0,3);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(GBInvCmd_obj,"GBSingulationControl.GBQureyAction",1,10);
   CHECK_NONZERO_NUMBER(rc);

   //rc=check_object_between_min_max(GBInvCmd_obj,"GBSingulationControl.GBQureySel",0,2);
   //CHECK_NONZERO_NUMBER(rc);
   return 0;
}
int check_antenna_extcfg(JSON_Object *antenna_obj)
{
   int loop=0;
   int rc=0;
   int IsHopFreq,hop_table_id;
   int maskbytelen,maskbitlen,hop_table_num,channal_num,channel;
   JSON_Array * array;
   /*判断频率*/
   if (1)
    { /*800M*/
        hop_table_num = HOP_TALBE_800M_MAXNUM - 1;
    }
    else
    { /*900M*/
        hop_table_num = HOP_TALBE_900M_MAXNUM - 1;
    }

   CHECK_NULL_POINTER_RETURN_VOID(antenna_obj);
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.ForandRevConfig",2,2);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(antenna_obj,"ExtCfg.TransmitPower6C",0,CFG_ANT_POWER_MAX - CFG_ANT_POWER_MIN);
   CHECK_NONZERO_NUMBER(rc);
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.TransmitPower6B",0,CFG_ANT_POWER_MAX - CFG_ANT_POWER_MIN);
   CHECK_NONZERO_NUMBER(rc);
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.TransmitPowerGB",0,CFG_ANT_POWER_MAX - CFG_ANT_POWER_MIN);
   CHECK_NONZERO_NUMBER(rc);

   rc=check_object_between_min_max(antenna_obj,"ExtCfg.Frequency6C.HopTableID",0,hop_table_num);
   CHECK_NONZERO_NUMBER(rc);

   IsHopFreq=(int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.IsHopFreq");
   hop_table_id =(int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.HopTableID");
   if(1==IsHopFreq)
   {
       rc=check_object_between_min_max(antenna_obj,"ExtCfg.Frequency6C.FreqHopConfig.HopInterval",1,400);
   	   CHECK_NONZERO_NUMBER(rc);
	   rc=check_object_between_min_max(antenna_obj,"ExtCfg.Frequency6C.FreqHopConfig.FreqChannelNum",1,MAX_FREQ_HOP_NUM);
   	   CHECK_NONZERO_NUMBER(rc);
	   rc=check_object_between_min_max(antenna_obj,"ExtCfg.Frequency6C.FreqHopConfig.HopType",0,2);
   	   CHECK_NONZERO_NUMBER(rc);
	   channal_num = (int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.FreqHopConfig.FreqChannelNum");
	    array=json_object_dotget_array(antenna_obj,"ExtCfg.Frequency6C.FreqHopConfig.FreqChannel");
	   for(loop=0;loop<channal_num && loop<MAX_FREQ_HOP_NUM;loop++)
	   {
		  channel= (int)json_array_get_number(array,loop);
		  if (1)
          {
              if (hop_table_id == 0 && channel > CHINA800_FREQUENCY_LEN - 1)
              { /*800M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
          else
          {
              if (hop_table_id == 0 && channel > CHINA900_FREQUENCY_LEN - 1)
              { /*900M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
              else if (hop_table_id == 1 && channel > AMERIACAN_FREQUENCY_LEN - 1)
              {
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
	   }
   }
   else
   {
        channel = (int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6C.ChannelIndex");
        if (1)
          {
              if (hop_table_id == 0 && channel > CHINA800_FREQUENCY_LEN - 1)
              { /*800M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
          else
          {
              if (hop_table_id == 0 && channel > CHINA900_FREQUENCY_LEN - 1)
              { /*900M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
              else if (hop_table_id == 1 && channel > AMERIACAN_FREQUENCY_LEN - 1)
              {
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
   }

   //6B
    rc=check_object_between_min_max(antenna_obj,"ExtCfg.Frequency6B.HopTableID",0,hop_table_num);
   CHECK_NONZERO_NUMBER(rc);

   IsHopFreq=(int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.IsHopFreq");
   hop_table_id =(int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.HopTableID");
   if(1==IsHopFreq)
   {
       rc=check_object_between_min_max(antenna_obj,"ExtCfg.Frequency6B.FreqHopConfig.HopInterval",1,400);
   	   CHECK_NONZERO_NUMBER(rc);
	   rc=check_object_between_min_max(antenna_obj,"ExtCfg.Frequency6B.FreqHopConfig.FreqChannelNum",1,MAX_FREQ_HOP_NUM);
   	   CHECK_NONZERO_NUMBER(rc);
	   rc=check_object_between_min_max(antenna_obj,"ExtCfg.Frequency6B.FreqHopConfig.HopType",0,2);
   	   CHECK_NONZERO_NUMBER(rc);
	   channal_num = (int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.FreqHopConfig.FreqChannelNum");
	    array=json_object_dotget_array(antenna_obj,"ExtCfg.Frequency6B.FreqHopConfig.FreqChannel");
	   for(loop=0;loop<channal_num && loop<MAX_FREQ_HOP_NUM;loop++)
	   {
		  channel= (int)json_array_get_number(array,loop);
		  if (1)
          {
              if (hop_table_id == 0 && channel > CHINA800_FREQUENCY_LEN - 1)
              { /*800M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
          else
          {
              if (hop_table_id == 0 && channel > CHINA900_FREQUENCY_LEN - 1)
              { /*900M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
              else if (hop_table_id == 1 && channel > AMERIACAN_FREQUENCY_LEN - 1)
              {
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
	   }
   }
   else
   {
        channel = (int)json_object_dotget_number(antenna_obj,"ExtCfg.Frequency6B.ChannelIndex");
        if (1)
          {
              if (hop_table_id == 0 && channel > CHINA800_FREQUENCY_LEN - 1)
              { /*800M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
          else
          {
              if (hop_table_id == 0 && channel > CHINA900_FREQUENCY_LEN - 1)
              { /*900M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
              else if (hop_table_id == 1 && channel > AMERIACAN_FREQUENCY_LEN - 1)
              {
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
   }
   //GB
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.FrequencyGB.HopTableID",0,hop_table_num);
   CHECK_NONZERO_NUMBER(rc);

   IsHopFreq=(int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.IsHopFreq");
   hop_table_id =(int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.HopTableID");
   if(1==IsHopFreq)
   {
       rc=check_object_between_min_max(antenna_obj,"ExtCfg.FrequencyGB.FreqHopConfig.HopInterval",1,400);
   	   CHECK_NONZERO_NUMBER(rc);
	   rc=check_object_between_min_max(antenna_obj,"ExtCfg.FrequencyGB.FreqHopConfig.FreqChannelNum",1,MAX_FREQ_HOP_NUM);
   	   CHECK_NONZERO_NUMBER(rc);
	   rc=check_object_between_min_max(antenna_obj,"ExtCfg.FrequencyGB.FreqHopConfig.HopType",0,2);
   	   CHECK_NONZERO_NUMBER(rc);
	   channal_num = (int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.FreqHopConfig.FreqChannelNum");
	    array=json_object_dotget_array(antenna_obj,"ExtCfg.FrequencyGB.FreqHopConfig.FreqChannel");
	   for(loop=0;loop<channal_num && loop<MAX_FREQ_HOP_NUM;loop++)
	   {
		  channel= (int)json_array_get_number(array,loop);
		  if (1)
          {
              if (hop_table_id == 0 && channel > CHINA800_FREQUENCY_LEN - 1)
              { /*800M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
          else
          {
              if (hop_table_id == 0 && channel > CHINA900_FREQUENCY_LEN - 1)
              { /*900M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
              else if (hop_table_id == 1 && channel > AMERIACAN_FREQUENCY_LEN - 1)
              {
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
	   }
   }
   else
   {
        channel = (int)json_object_dotget_number(antenna_obj,"ExtCfg.FrequencyGB.ChannelIndex");
        if (1)
          {
              if (hop_table_id == 0 && channel > CHINA800_FREQUENCY_LEN - 1)
              { /*800M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
          else
          {
              if (hop_table_id == 0 && channel > CHINA900_FREQUENCY_LEN - 1)
              { /*900M*/
                  CHECK_NONZERO_NUMBER(-1);
              }
              else if (hop_table_id == 1 && channel > AMERIACAN_FREQUENCY_LEN - 1)
              {
                  CHECK_NONZERO_NUMBER(-1);
              }
          }
   }
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.RssiFilter6C.RssiReadThreshold",0,0xffffffff);
   CHECK_NONZERO_NUMBER(rc);
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.RssiFilter6C.RssiWriteThreshold",0,0xffffffff);
   CHECK_NONZERO_NUMBER(rc);
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.RssiFilter6B.RssiReadThreshold",0,0xffffffff);
   CHECK_NONZERO_NUMBER(rc);
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.RssiFilter6B.RssiWriteThreshold",0,0xffffffff);
   CHECK_NONZERO_NUMBER(rc);
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.RssiFilterGB.RssiReadThreshold",0,0xffffffff);
   CHECK_NONZERO_NUMBER(rc);
   rc=check_object_between_min_max(antenna_obj,"ExtCfg.RssiFilterGB.RssiWriteThreshold",0,0xffffffff);
   CHECK_NONZERO_NUMBER(rc);
   
   return 0;
}

int check_uhf_business_config(JSON_Object *input_object)
{
    int rc=0; 
	int loop=0;
	int ro_report_trigger,IsOpen_RFFilter;
	unsigned char tmpBuf[256]={0};
	JSON_Object *antenna_obj=NULL;
    CHECK_NULL_POINTER_RETURN_INT(input_object);

	for(loop=0;loop<READER_ANTENNA_COUNT;loop++)
	{
	    sprintf(tmpBuf,"Antenna%d",loop+1);
	    antenna_obj=json_object_dotget_object(input_object,tmpBuf);
		CHECK_NULL_POINTER_RETURN_INT(antenna_obj);
		rc=check_antenna_cfg(antenna_obj);
		CHECK_NONZERO_NUMBER(rc);
		rc=check_antenna_extcfg(antenna_obj);
		CHECK_NONZERO_NUMBER(rc);
	}
    rc=check_object_between_min_max(input_object,"ROReportSpec.ROReportTrigger",0,2);
    CHECK_NONZERO_NUMBER(rc);

	ro_report_trigger = (int)json_object_dotget_number(input_object,"ROReportSpec.ROReportTrigger");
	if((ro_report_trigger==1)||(ro_report_trigger==2))
	{
	    rc=check_object_between_min_max(input_object,"ROReportSpec.N",1,65535);
    	CHECK_NONZERO_NUMBER(rc);
	}
	IsOpen_RFFilter = (int)json_object_dotget_number(input_object,"TagReportFilter.IsOpenRFFilter");
	if(IsOpen_RFFilter==1)
	{
	    rc=check_object_between_min_max(input_object,"TagReportFilter.RFKeepaliveTime",1,1000);
    	CHECK_NONZERO_NUMBER(rc);
	}
    rc=check_object_between_min_max(input_object,"AccessReportTrigger",0,1);
    CHECK_NONZERO_NUMBER(rc);

    rc=check_object_between_min_max(input_object,"DepthIndex6C",0,2);
    CHECK_NONZERO_NUMBER(rc);

	rc=check_object_between_min_max(input_object,"DepthIndex6B",0,1);
    CHECK_NONZERO_NUMBER(rc);

	rc=check_object_between_min_max(input_object,"DepthIndexGB",0,2);
    CHECK_NONZERO_NUMBER(rc);
    
    return rc;
}

int check_uhf_comm_net_config(JSON_Object *input_object)
{
    int rc=0; 
	int linkMode;
	unsigned int ip_addr;
    CHECK_NULL_POINTER_RETURN_INT(input_object);
	linkMode = json_object_get_number(input_object,"linkMode");
	if((CMP_COMM_LINK_MODE_SERVER==linkMode)||(CMP_COMM_LINK_MODE_MIX==linkMode))
	{
	    rc=check_object_between_min_max(input_object,"hostPort",1024,65535);
    	CHECK_NONZERO_NUMBER(rc);
	}
    if ((CMP_COMM_LINK_MODE_CLIENT==linkMode)||(CMP_COMM_LINK_MODE_MIX==linkMode))
	{
	    rc=check_object_between_min_max(input_object,"clientPort",1024,65535);
    	CHECK_NONZERO_NUMBER(rc);

		ip_addr=(unsigned int)json_object_get_number(input_object,"clientAddress");
        rc=check_ip_gateway_dns(ip_addr);
        CHECK_NONZERO_NUMBER(rc);
	}
    return rc;
}  

int check_uhf_file_comm_config(JSON_Object *input_object)
{
    int rc=0; 
	int loop,link_num;
	unsigned char tmpBuf[256]={0};
    JSON_Object *tmp_object=NULL;
	JSON_Object *link_obj=NULL;
    CHECK_NULL_POINTER_RETURN_INT(input_object);
    
    rc=check_object_between_min_max(input_object,"linkNum",1,UHF_MAX_LINK_NUM);
    CHECK_NONZERO_NUMBER(rc); 

	link_num = (int)json_object_get_number(input_object,"linkNum");
	for(loop=0;loop<link_num;loop++)
	{
	    sprintf(tmpBuf,"link%d",loop+1);
	    link_obj=json_object_dotget_object(input_object,tmpBuf);
		CHECK_NULL_POINTER_RETURN_INT(link_obj);
		tmp_object=json_object_get_object(link_obj,"keepAlive");
	    rc=check_comm_keepalive_config(tmp_object);
	    CHECK_NONZERO_NUMBER(rc);

	    tmp_object=json_object_get_object(link_obj,"net");
	    rc=check_uhf_comm_net_config(tmp_object);
	    CHECK_NONZERO_NUMBER(rc);
	    
	    tmp_object=json_object_get_object(link_obj,"serial");
	    rc=check_comm_serial_config(tmp_object);
	    CHECK_NONZERO_NUMBER(rc);
	}
    return rc;
}    

int check_uhf_file_config(JSON_Object *input_object)
{
    int rc=0; 
    JSON_Object *tmp_object=NULL;
    CHECK_NULL_POINTER_RETURN_INT(input_object);
    
    tmp_object=json_object_get_object(input_object,"uhf");
    rc=check_uhf_business_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);

    tmp_object=json_object_get_object(input_object,"comm");
    rc=check_uhf_file_comm_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);

    tmp_object=json_object_get_object(input_object,"ntp");
    rc=check_file_ntp_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);
    return rc;
}

int check_uhf_config(JSON_Object *input_object)
{
    int rc=0; 
    JSON_Object *tmp_object=NULL;
    CHECK_NULL_POINTER_RETURN_INT(input_object);

    tmp_object=json_object_get_object(input_object,"file");
    rc=check_uhf_file_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);

    tmp_object=json_object_get_object(input_object,"eeprom");
    rc=check_eeprom_ip_config(tmp_object);
    CHECK_NONZERO_NUMBER(rc);
}
#endif

