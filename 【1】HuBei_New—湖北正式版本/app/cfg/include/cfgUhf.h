#ifndef  CFG_UHF_H
#define  CFG_UHF_H

#ifdef CFG_UHF
#include "cfgPub.h"

#define READER_ANTENNA_COUNT 4
#define EPC_MAX_MASK_WORD_NUM           32   /*EPC最大掩码字数*/
#define CFG_ANT_POWER_MAX                 33
#define CFG_ANT_POWER_MIN                 15
#define EPC_RFMODE_TABLE_LEN        (4)
#define ISO6B_RFMODE_TABLE_LEN      (2)
#define GB_RFMODE_TABLE_LEN         (4)
#define  MAX_FREQ_HOP_NUM        (50)
#define  CHINA800_FREQUENCY_LEN  (20)
#define  CHINA900_FREQUENCY_LEN  (20)
#define  AMERIACAN_FREQUENCY_LEN (50)
#define  FREQ800MTABLE_NUM      (1)
#define  FREQ900MTABLE_NUM      (2)
#define  FREQ800900MTABLE_NUM   (3)
#define  UHF_MAX_LINK_NUM   (2)
#define CMP_COMM_LINK_MODE_SERVER   0
#define CMP_COMM_LINK_MODE_CLIENT   1
#define CMP_COMM_LINK_MODE_MIX      2

//如下内容暂时放在这里
#define   EPC_RFMODE_MAXNUM                    10
#define   ISO6B_RFMODE_MAXNUM                2
#define   HOP_TALBE_800M_MAXNUM            1    /* 最大跳频表数*/
#define   HOP_TALBE_900M_MAXNUM            2    /* 最大跳频表数*/
#define   MaxEPCSelectNum                           1     /*最大EPC 支持select 数*/
#define   MaxGBSortNum                           1    /*最大GB 支持sort 数*/
#define   EPC_MAX_MASK_WORD_NUM           32   /*EPC最大掩码字数*/
#define   MaxISO6BGroupSelectNum               1


/*标签过滤轮询时间*/
#define TAGFILTER_OPPOLLTIME 20
#define TAGFILTER_RFPOLLTIME 20

/*结束*/
#define MAX_EPC_WRITE_WORD_LEN    (256)


int check_antenna_cfg(JSON_Object *antenna_obj);
int check_antenna_extcfg(JSON_Object *antenna_obj);
int check_uhf_business_config(JSON_Object *input_object);
int check_uhf_comm_net_config(JSON_Object *input_object);
int check_uhf_file_comm_config(JSON_Object *input_object);
int check_uhf_file_config(JSON_Object *input_object);
int check_uhf_config(JSON_Object *input_object);

#endif
#endif