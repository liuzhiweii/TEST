/**
 * \file     test_parser.c
 * \brief    Test program for parser library. 
 * \details  This is a test program with a simple CLI that serves as a demo 
 *           as well.
 * \version  \verbatim $Id: test_parser.c 33 2009-01-22 06:45:33Z henry $ \endverbatim
 */
/*
 * Copyright (c) 2008-2009, Henry Kwok
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the project nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY HENRY KWOK ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL HENRY KWOK BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> 
#include "cparser.h"
#include "cparser_token.h"
#include "parson.h"
#include "cli.h"
#include "drvtest.h"


extern void *req_socket_cfg;
char send_buf[CLI_MAX_MSG_LEN]={0};
char recv_buf[CLI_MAX_MSG_LEN]={0};


int interactive = 0;
#define PRINTF(args...)                                 \
    if (interactive) {                                  \
        printf(args);                                   \
    } else {                                            \
        output_ptr += sprintf(output_ptr, args);        \
    }

#define MAX_NAME        (128)
#define MAX_TITLE       (32)

char *output_ptr;
char output[2000]; /* buffer for sprintf */

/*cli发送消息接口*/
void send_msg(const char *type,const char *action,const char *content)
{
    int rc=0;     
    JSON_Value *tmp_value=NULL;
    JSON_Object *tmp_object=NULL;
 
    printf("send_msg type=%s,action=%s,content=%s\r\n",type,action,content);
    
    tmp_value=json_value_init_object();
    tmp_object=tmp_value->value.object;
    json_object_set_string(tmp_object,"type",type);
    json_object_set_string(tmp_object,"action",action);
    if(NULL!=content)
    {
       json_object_set_string(tmp_object,"content",content);
    }
    memset(send_buf,0,sizeof(send_buf));
    rc=json_serialize_to_buffer(tmp_value,send_buf,CLI_MAX_MSG_LEN);
    /*释放*/
    json_value_free(tmp_value);
    printf("json_serialize_to_buffer send_buf = %s \r\n", send_buf);
    CLI_SEND_MSG(req_socket_cfg,send_buf,strlen(send_buf)+1);
}

/*处理cli接收消息*/
JSON_Object *parse_string_to_object(const char *strings,JSON_Value **string_value)
{
    JSON_Object *tmp_object=NULL;
    JSON_Value *tmp_value=NULL;
 
    /* 解析默认配置 */
    tmp_value= json_parse_string(strings);
    *string_value = NULL;
    assert(tmp_value);

   if(json_value_get_type(tmp_value) == JSONObject)
   {
      tmp_object = json_value_get_object(tmp_value);
      *string_value = tmp_value;
   }
   else
   {
       json_value_free(tmp_value);
       *string_value=NULL;
       return NULL;
   }
    return tmp_object;
}

cparser_result_t cparser_cmd_config(cparser_context_t *context)
{
    char prompt[CPARSER_MAX_PROMPT];

    assert(context);

    /* Enter the submode */
    snprintf(prompt, CPARSER_MAX_PROMPT, "config#");
    return cparser_submode_enter(context->parser, NULL, prompt);
}

cparser_result_t cparser_cmd_config_exit(cparser_context_t *context)
{
    assert(context && context->parser);
    return cparser_submode_exit(context->parser);
}

void print_value_by_json_type(JSON_Value *json_value)
{
    assert(json_value);
    switch(json_value->type)
    {
        case JSONString:
        {
           PRINTF("%s\n",json_value->value.string);
           break;
        }
        case JSONNumber:
        {
           PRINTF("%u\n",(unsigned int)json_value->value.number);
           break;
        }
        case JSONBoolean:
        {
           if(0==json_value->value.boolean)
           {
              PRINTF("false\n");
           }
           else
           {
              PRINTF("true\n");
           }
           break;
        }
        default:
        {
           PRINTF("wrong type\n");
           break;
        }
        
    }
}

cparser_result_t cparser_cmd_config_get_key(cparser_context_t *context,
    char **key_ptr)
{
    int rc=0;
    const char *type=NULL;
    int result=0;
    JSON_Value *cur_value=NULL;
    JSON_Object *cur_object=NULL;
    JSON_Value *tmp_value=NULL;
    assert(context && key_ptr && *key_ptr);
    send_msg("cli","get",*key_ptr);
    memset(recv_buf,0,sizeof(recv_buf));
    rc=CLI_RECV_MSG(req_socket_cfg,recv_buf,CLI_MAX_MSG_LEN);
    if(-1==rc)
    {
       PRINTF("recv msg error errno=%d\r\n",errno);
       return CPARSER_NOT_OK;
    }
    else if(rc>0)
    {
       cur_object=parse_string_to_object(recv_buf,&cur_value);
       assert(cur_object);
       type=json_object_get_string(cur_object,"type");
       result=(int)json_object_get_number(cur_object,"result");
       tmp_value=json_object_get_value(cur_object,"value");
       if((0==strcmp(type,"get_ack"))&&(0==result))
       {
          print_value_by_json_type(tmp_value);
       }
       else
       {
          PRINTF("failed\r\n");
       }
       json_value_free(cur_value);
    }
    else 
    {
        PRINTF("recv msg success but recv 0 byte\r\n");
        return CPARSER_NOT_OK;
    }
    return CPARSER_OK;
}
#if 1
cparser_result_t cparser_cmd_config_set_key_value(cparser_context_t *context,
    char **key_ptr,
    char **value_ptr)
{
    int rc=0;
    char tmpBuf[512]={0};
    const char *type=NULL;
    int result=0;
    JSON_Value *cur_value=NULL;
    JSON_Object *cur_object=NULL;
    assert(context && key_ptr && *key_ptr&&value_ptr&&*value_ptr);
    sprintf(tmpBuf,"{\"%s\":%s}",*key_ptr,*value_ptr);
    printf("send content:%s",tmpBuf);
    send_msg("cli","set",tmpBuf);
    memset(recv_buf,0,sizeof(recv_buf));
    rc=CLI_RECV_MSG(req_socket_cfg,recv_buf,CLI_MAX_MSG_LEN);
    if(-1==rc)
    {
       PRINTF("recv msg error errno=%d\r\n",errno);
       return CPARSER_NOT_OK;
    }
    else if(rc>0)
    {
       cur_object=parse_string_to_object(recv_buf,&cur_value);
       assert(cur_object);
       type=json_object_get_string(cur_object,"type");
       result=(int)json_object_get_number(cur_object,"result");
       if((0==strcmp(type,"set_ack"))&&(0==result))
       {
          PRINTF("success\r\n");
       }
       else
       {
          PRINTF("failed\r\n");
       }
       json_value_free(cur_value);
    }
    else 
    {
        PRINTF("recv msg success but recv 0 byte\r\n");
        return CPARSER_NOT_OK;
    }
    return CPARSER_OK;
}
#endif
#if 0 //test client set and get
cparser_result_t cparser_cmd_config_set_key_value(cparser_context_t *context,
    char **key_ptr,
    char **value_ptr)
{
    int rc=0;
    char tmpBuf[512]={0};
    const char *type=NULL;
    const char *content=NULL;
    char *send_content=NULL;
    int result=0;
    JSON_Value *cur_value=NULL;
    JSON_Object *cur_object=NULL;
    JSON_Value *set_value=NULL;
    JSON_Object *set_object=NULL;
    JSON_Value *tmp_value=NULL;
    unsigned int number=0;
    assert(context && key_ptr && *key_ptr&&value_ptr&&*value_ptr);
    sprintf(tmpBuf,"{\"%s\":%s}",*key_ptr,*value_ptr);
    printf("key value:%s",tmpBuf);
    
    send_msg("client","get",NULL);
    memset(recv_buf,0,sizeof(recv_buf));
    rc=CLI_RECV_MSG(req_socket_cfg,recv_buf,CLI_MAX_MSG_LEN);
    if(-1==rc)
    {
       PRINTF("recv msg error errno=%d\r\n",errno);
       return CPARSER_NOT_OK;
    }
    else if(rc>0)
    {
       cur_object=parse_string_to_object(recv_buf,&cur_value);
       assert(cur_object);
       type=json_object_get_string(cur_object,"type");
       result=(int)json_object_get_number(cur_object,"result");
       content=json_object_get_string(cur_object,"content");
       if((0==strcmp(type,"client_get_ack"))&&(0==result))
       {
          PRINTF("client get content:%s\r\n",content);
          //将content转化为对象，修改其中的值
          set_object=parse_string_to_object(content,&set_value);
          assert(set_object);
          tmp_value=json_object_dotget_value(set_object,*key_ptr);
          assert(tmp_value);
          if(JSONString==tmp_value->type)
          {
             json_object_dotset_string(set_object,*key_ptr,*value_ptr);
          }
          else if(JSONNumber==tmp_value->type)
          {
             number=strtoul(*value_ptr,NULL,10);
             printf("%u",number);
             json_object_dotset_number(set_object,*key_ptr,number);
          }
          else if(JSONBoolean==tmp_value->type)
          {
             json_object_dotset_boolean(set_object,*key_ptr,((0==strcmp(*value_ptr,"true"))?1:((0==strcmp(*value_ptr,"false"))?0:-1)));
          }
          else
          {
             PRINTF("unsupported type\r\n");
          }
          send_content=json_serialize_to_string(set_value);
          send_msg("client","set",send_content);
          json_value_free(set_value);
          json_free_serialized_string(send_content);
          memset(recv_buf,0,sizeof(recv_buf));
          rc=CLI_RECV_MSG(req_socket_cfg,recv_buf,CLI_MAX_MSG_LEN);
          assert(rc>0);
          PRINTF("SUCCESS\r\n");
          
       }
       else
       {
          PRINTF("failed\r\n");
       }
       json_value_free(cur_value);
    }
    else 
    {
        PRINTF("recv msg success but recv 0 byte\r\n");
        return CPARSER_NOT_OK;
    }
    return CPARSER_OK;
}
#endif
cparser_result_t cparser_cmd_config_restore(cparser_context_t *context)
{
    int rc=0;
    const char *type=NULL;
    int result=0;
    JSON_Value *cur_value=NULL;
    JSON_Object *cur_object=NULL;
    assert(context);
    send_msg("restore","restore",NULL);
    memset(recv_buf,0,sizeof(recv_buf));
    rc=CLI_RECV_MSG(req_socket_cfg,recv_buf,CLI_MAX_MSG_LEN);
    if(-1==rc)
    {
       PRINTF("recv msg error errno=%d\r\n",errno);
       return CPARSER_NOT_OK;
    }
    else if(rc>0)
    {
       cur_object=parse_string_to_object(recv_buf,&cur_value);
       assert(cur_object);
       type=json_object_get_string(cur_object,"type");
       result=(int)json_object_get_number(cur_object,"result");
       if((0==strcmp(type,"restore_ack"))&&(0==result))
       {
          PRINTF("success\r\n");
       }
       else
       {
          PRINTF("failed\r\n");
       }
       json_value_free(cur_value);
    }
    else 
    {
        PRINTF("recv msg success but recv 0 byte\r\n");
        return CPARSER_NOT_OK;
    }
    return CPARSER_OK;
}

cparser_result_t cparser_cmd_config_reset(cparser_context_t *context)
{
    int rc=0;
    const char *type=NULL;
    int result=0;
    JSON_Value *cur_value=NULL;
    JSON_Object *cur_object=NULL;
    assert(context);
    send_msg("reset","reset",NULL);
    memset(recv_buf,0,sizeof(recv_buf));
    rc=CLI_RECV_MSG(req_socket_cfg,recv_buf,CLI_MAX_MSG_LEN);
    if(-1==rc)
    {
       PRINTF("recv msg error errno=%d\r\n",errno);
       return CPARSER_NOT_OK;
    }
    else if(rc>0)
    {
       cur_object=parse_string_to_object(recv_buf,&cur_value);
       assert(cur_object);
       type=json_object_get_string(cur_object,"type");
       result=(int)json_object_get_number(cur_object,"result");
       if((0==strcmp(type,"reset_ack"))&&(0==result))
       {
          PRINTF("success\r\n");
       }
       else
       {
          PRINTF("failed\r\n");
       }
       json_value_free(cur_value);
    }
    else 
    {
        PRINTF("recv msg success but recv 0 byte\r\n");
        return CPARSER_NOT_OK;
    }
    return CPARSER_OK;
}


cparser_result_t cparser_cmd_config_save(cparser_context_t *context)
{
    int rc=0;
    const char *type=NULL;
    int result=0;
    JSON_Value *cur_value=NULL;
    JSON_Object *cur_object=NULL;
    assert(context); 
    send_msg("cli","save",NULL);
    memset(recv_buf,0,sizeof(recv_buf));
    rc=CLI_RECV_MSG(req_socket_cfg,recv_buf,CLI_MAX_MSG_LEN);
    if(-1==rc)
    {
       PRINTF("recv msg error errno=%d\r\n",errno);
       return CPARSER_NOT_OK;
    }
    else if(rc>0)
    {
       cur_object=parse_string_to_object(recv_buf,&cur_value);
       assert(cur_object);
       type=json_object_get_string(cur_object,"type");
       result=(int)json_object_get_number(cur_object,"result");
       if((0==strcmp(type,"save_ack"))&&(0==result))
       {
          PRINTF("success\r\n");
       }
       else
       {
          PRINTF("failed\r\n");
       }
       json_value_free(cur_value);
    }
    else 
    {
        PRINTF("recv msg success but recv 0 byte\r\n");
        return CPARSER_NOT_OK;
    }
    return CPARSER_OK;
}

cparser_result_t cparser_cmd_config_help_filter(cparser_context_t *context,
    char **filter_ptr)
{
    assert(context);
    return cparser_help_cmd(context->parser, filter_ptr ? *filter_ptr : NULL);
}   
cparser_result_t cparser_cmd_version(cparser_context_t *context)
{
    char prompt[CPARSER_MAX_PROMPT];

    assert(context);

    /* Enter the submode */
    snprintf(prompt, CPARSER_MAX_PROMPT, "version#");
    return cparser_submode_enter(context->parser, NULL, prompt);
}

cparser_result_t cparser_cmd_diagnose(cparser_context_t *context)
{
    char prompt[CPARSER_MAX_PROMPT];

    assert(context);

    /* Enter the submode */
    snprintf(prompt, CPARSER_MAX_PROMPT, "diagnose#");
    return cparser_submode_enter(context->parser, NULL, prompt);
}

cparser_result_t cparser_cmd_drvtest(cparser_context_t *context)
{
    char prompt[CPARSER_MAX_PROMPT];

    assert(context);

    /* Enter the submode */
    snprintf(prompt, CPARSER_MAX_PROMPT, "drvtest#");
    return cparser_submode_enter(context->parser, NULL, prompt);
}

cparser_result_t cparser_cmd_drvtest_help_filter(cparser_context_t *context,
    char **filter_ptr)
{
    assert(context);
    return cparser_help_cmd(context->parser, filter_ptr ? *filter_ptr : NULL);
} 


cparser_result_t cparser_cmd_drvtest_norflash_mod_offset_len_data(cparser_context_t *context,
    char **mod_ptr,
    uint32_t *offset_ptr,
    uint32_t *len_ptr,
    uint32_t *data_ptr)
{
    assert(context && *mod_ptr); 

    if (0 == strcmp("write", *mod_ptr))
    {
        assert(offset_ptr && len_ptr && data_ptr); 
        drvtest_flash_write(*offset_ptr, *len_ptr, *data_ptr);
    }
    else if (0 == strcmp("read", *mod_ptr))
    {
        assert(offset_ptr && len_ptr); 
        drvtest_flash_read(*offset_ptr, *len_ptr);

    }
    else if(0 == strcmp("erase", *mod_ptr))
    {
        assert(offset_ptr && len_ptr); 
        drvtest_flash_erase(*offset_ptr, *len_ptr);

    }
    else if(0 == strcmp("info", *mod_ptr))
    {
        drvtest_flash_info();
    }
    else
    {
        PRINTF("input test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;
}
cparser_result_t cparser_cmd_drvtest_epld_mod_addr_data(cparser_context_t *context,
    char **mod_ptr,
    uint32_t *addr_ptr,
    uint32_t *data_ptr)
{

    unsigned int iRet = 0;
    unsigned int dwRegOffset = 0;
    unsigned short int iData = 0;

    assert(context && *mod_ptr); 

    if (*data_ptr > 0xFFFF)
    {
        iData = 0xFFFF;
    }
    else
    {
        iData = *data_ptr;
    }
    if (0 == strcmp("write", *mod_ptr))
    {
        assert(addr_ptr); 
        iRet = drvtest_writepld(*addr_ptr, iData);
    }
    else if (0 == strcmp("read", *mod_ptr))
    {
        iRet = drvtest_readepld(*addr_ptr);
    }
    else
    {
        PRINTF("input test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;

}

cparser_result_t cparser_cmd_drvtest_fpga_mod_addr_data(cparser_context_t *context,
    char **mod_ptr,
    uint32_t *addr_ptr,
    uint32_t *data_ptr)
{

    unsigned int iRet = 0;
    unsigned int dwRegOffset = 0;
    unsigned short int iData = 0;

    assert(context && *mod_ptr); 

    //if (*data_ptr > 0xFFFF)
    //{
    //    iData = 0xFFFF;
    //}
    //else
    {
        iData = *data_ptr;
    }

    if (0 == strcmp("write", *mod_ptr))
    {
        assert(addr_ptr); 
        iRet = drvtest_writefpga(*addr_ptr, iData);
    }
    else if (0 == strcmp("read", *mod_ptr))
    {
        iRet = drvtest_readfpga(*addr_ptr);
    }
    else
    {
        PRINTF("input test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;

}


cparser_result_t cparser_cmd_drvtest_eeprom_mod_data(cparser_context_t *context,
    char **mod_ptr,
    uint32_t *data_ptr)
{
    assert(context && *mod_ptr);
    if (0 == strcmp("write", *mod_ptr))
    {
        assert(data_ptr);
        (void)drvtest_eeprom_write(*data_ptr);
    }
    else if (0 == strcmp("read", *mod_ptr))
    {
        (void)drvtest_eeprom_read();
    }
    else if (0 == strcmp("save", *mod_ptr))
    {
        (void)drvtest_eeprom_savedata();
    }
    else if (0 == strcmp("recover", *mod_ptr))
    {
        (void)drvtest_eeprom_recoverdata();
    }
    else
    {
        PRINTF("input test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;

}
cparser_result_t cparser_cmd_drvtest_eepromaddr_mod_addr_len_data(cparser_context_t *context,
    char **mod_ptr,
    uint32_t *addr_ptr,
    uint32_t *len_ptr,
    char **data_ptr)
{
    assert(context && *mod_ptr && addr_ptr &&len_ptr);
    if (0 == strcmp("write", *mod_ptr))
    {
        assert(data_ptr&&*data_ptr);
        (void)drvtest_eeprom_write_addr_len_data(*addr_ptr,*len_ptr,*data_ptr);
    }
    else if (0 == strcmp("read", *mod_ptr))
    {
        (void)drvtest_eeprom_read_addr_len(*addr_ptr,*len_ptr);
    }
    else
    {
        PRINTF("input test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;

}


cparser_result_t cparser_cmd_drvtest_seteeprom_configPath(cparser_context_t *context,
    char **configPath_ptr)
{

    assert(context && *configPath_ptr);

    (void)drvtest_eeprom_setdefault(*configPath_ptr);

    return CPARSER_OK;

}


cparser_result_t cparser_cmd_drvtest_uart_index_baundrate_testMode_loopNum(cparser_context_t *context,
    int32_t *index_ptr,
    int32_t *baundrate_ptr,
    char **testMode_ptr,
    int32_t *loopNum_ptr)
{

    int iRet = 0; 
    
    assert(context && index_ptr && baundrate_ptr && *testMode_ptr);

    if ((*index_ptr > 3) || (*index_ptr < 0))
    {
        PRINTF("input index error!\r\n");
        return CPARSER_NOT_OK;
        
    }

    if (0 == strcmp("rec_send", *testMode_ptr))
    {
        iRet = drvtest_uart_revsend(*index_ptr, *baundrate_ptr);
    }
    else if (0 == strcmp("loopback", *testMode_ptr))
    {
        assert(loopNum_ptr);
        iRet = drvtest_uart_loopback(*index_ptr, *baundrate_ptr, *loopNum_ptr);
    }
    else
    {
        PRINTF("input test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;

}

cparser_result_t cparser_cmd_drvtest_wtd_wtd_mod(cparser_context_t *context,
    char **wtd_mod_ptr)
{
    int iRet = 0;
    assert(context && *wtd_mod_ptr);

    if (0 == strcmp("softWtd", *wtd_mod_ptr))
    {
        iRet = drvtest_softwtd();
    }
    else if (0 == strcmp("hwWtd", *wtd_mod_ptr))
    {
        iRet = drvtest_hwwtd();
    }
    else if (0 == strcmp("stopWtd", *wtd_mod_ptr))
    {
        iRet = drvtest_stopwtd();
    }
    else
    {
        PRINTF("input wtd mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;
    
}


cparser_result_t cparser_cmd_drvtest_psam_pasm_mod_VALUE(cparser_context_t *context,
    char **pasm_mod_ptr,
    int32_t *VALUE_ptr)
{
    int iRet = 0;
    assert(context && *pasm_mod_ptr);
    
    if (0 == strcmp("init", *pasm_mod_ptr))
    {
        iRet = drvtest_psaminit();
    }
    else if (0 == strcmp("setclk", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_psamsetclk(*VALUE_ptr);
    }
    else if (0 == strcmp("active", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_psamactive(*VALUE_ptr);
    }
    else if (0 == strcmp("deactive", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_psamdeactive(*VALUE_ptr);
    }
    else if (0 == strcmp("getrand", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_psamrandomdata(*VALUE_ptr);
    }
    else if (0 == strcmp("choseapp", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_psamchoseapp(*VALUE_ptr);
    }
    else if (0 == strcmp("getkey", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_psamassignkey(*VALUE_ptr);
    }
    else if (0 == strcmp("decryptinfo", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_psamdecryptinfo(*VALUE_ptr);
    }
    else if (0 == strcmp("decrypt", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_autodecrypt(*VALUE_ptr);
    }
    else if (0 == strcmp("enablepps", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_psam_enable_pps(*VALUE_ptr);
    }
    else if (0 == strcmp("disablepps", *pasm_mod_ptr))
    {
        assert(VALUE_ptr);
        iRet = drvtest_psam_disable_pps(*VALUE_ptr);
    }
    else
    {
        PRINTF("input psam mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;
}
cparser_result_t cparser_cmd_drvtest_loadfpga_verPath(cparser_context_t *context,
    char **verPath_ptr)
{
    int iRet = 0;
    
    assert(context && *verPath_ptr);

    (void)drvtest_loadfpag(*verPath_ptr);

    return CPARSER_OK;
}

cparser_result_t cparser_cmd_drvtest_lcd_mod(cparser_context_t *context,
    char **mod_ptr)
{
    //int iRet = 0;

    assert(context && *mod_ptr);

    if (0 == strcmp("clear", *mod_ptr))
    {
       drvtest_lcdclear();
    }
    else if (0 == strcmp("light", *mod_ptr))
    {
        drvtest_lcdlight();
    }
    else if (0 == strcmp("showstr", *mod_ptr))
    {
        drvtest_lcd_showstr();
    }
    else
    {
        PRINTF("input lcd test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;
}
cparser_result_t cparser_cmd_drvtest_led_mod_state(cparser_context_t *context,
    char **mod_ptr,
    int32_t *state_ptr)
{

    assert(context && *mod_ptr && state_ptr);

    if (0 == strcmp("run", *mod_ptr))
    {
       drvtest_ledrun(*state_ptr);
    }
    else if (0 == strcmp("psam", *mod_ptr))
    {
        drvtest_ledpsam(*state_ptr);
    }
    else if (0 == strcmp("alarm", *mod_ptr))
    {
        drvtest_ledalarm(*state_ptr);
    }
    else
    {
        PRINTF("input led test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;

}

cparser_result_t cparser_cmd_drvtest_devicectl_mod_devlist_powctl(cparser_context_t *context,
    char **mod_ptr,
    int32_t *devlist_ptr,
    int32_t *powctl_ptr)
{
    assert(context && *mod_ptr && devlist_ptr && powctl_ptr);

    if (0 == strcmp("rst", *mod_ptr))
    {
        drvtest_device_rst(*devlist_ptr);
    }
    else if (0 == strcmp("pow", *mod_ptr))
    {
        drvtest_device_powctl(*devlist_ptr, *powctl_ptr);
    }
    else
    {
        PRINTF("input device ctrl test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;


}

cparser_result_t cparser_cmd_drvtest_key(cparser_context_t *context)
{
    assert(context);
    drvtest_key();
    return CPARSER_OK;
}

cparser_result_t cparser_cmd_drvtest_ver(cparser_context_t *context)
{
    assert(context);
    drvtest_ver();
    return CPARSER_OK;
}

cparser_result_t cparser_cmd_drvtest_rtcset_year_mon_mon_day_week_day_hour_min_sec(cparser_context_t *context,
    int32_t *year_ptr,
    int32_t *mon_ptr,
    int32_t *mon_day_ptr,
    int32_t *week_day_ptr,
    int32_t *hour_ptr,
    int32_t *min_ptr,
    int32_t *sec_ptr)
{
    rtc_time_t tTime;

    assert(context && year_ptr && mon_ptr && mon_day_ptr && week_day_ptr\
            && hour_ptr && min_ptr && sec_ptr);

    tTime.tm_year = *year_ptr;
    tTime.tm_mon = *mon_ptr;
    tTime.tm_mday = *mon_day_ptr;
    tTime.tm_wday = *week_day_ptr;
    tTime.tm_hour = *hour_ptr;
    tTime.tm_min = *min_ptr;
    tTime.tm_sec = *sec_ptr;
    
    drvtest_settime(tTime);
    return CPARSER_OK;

}
cparser_result_t cparser_cmd_drvtest_rtcget(cparser_context_t *context)
{
    assert(context);

    drvtest_gettime();
    return CPARSER_OK;
}

cparser_result_t cparser_cmd_drvtest_tsentor_mod_id_temper(cparser_context_t *context,
    char **mod_ptr,
    int32_t *id_ptr,
    int32_t *temper_ptr)
{
    
    assert(context && *mod_ptr && id_ptr && temper_ptr);

    if (0 == strcmp("set", *mod_ptr))
    {
        drvtest_settsensor(*id_ptr, *temper_ptr);
    }
    else if (0 == strcmp("get", *mod_ptr))
    {
        drvtest_gettsensor(*id_ptr);
    }
    else
    {
        PRINTF("input test mode error!\r\n");
        return CPARSER_NOT_OK;
    }

    return CPARSER_OK;

}

cparser_result_t cparser_cmd_drvtest_net_loopNum(cparser_context_t *context,
    int32_t *loopNum_ptr)
{
    assert(context && loopNum_ptr);

    drvtest_net_loopback(*loopNum_ptr);
    return CPARSER_OK;
}

cparser_result_t cparser_cmd_drvtest_exit(cparser_context_t *context)
{
    assert(context && context->parser);
    return cparser_submode_exit(context->parser);
}


cparser_result_t cparser_cmd_help_filter(cparser_context_t *context,char **filter_ptr)
{
    assert(context);
    return cparser_help_cmd(context->parser, filter_ptr ? *filter_ptr : NULL);
}

    
cparser_result_t cparser_cmd_quit(cparser_context_t *context)
{
    assert(context);
    return cparser_quit(context->parser);
}


