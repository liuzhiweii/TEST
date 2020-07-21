
#include <string.h>
#include "etc_codec_ff_rsctl.h"
#include "logm.h"


#define recv_buf_size  2048
#define send_buf_size 2048

typedef enum decode_state_e 
{
    STATE_FIRST_FF = 0,
    STATE_RSCTL,
    STATE_DATA,
    STATE_DATA_DECODE,
    STATE_BCC
} e_decode_state;

typedef  unsigned char *(*func_ptr)(unsigned char u8Data, unsigned int *pu32DecodeLen);


e_decode_state eState = STATE_FIRST_FF;

unsigned int u32RecvLen = 0;
unsigned char *pRecvBuf = NULL;
unsigned char *pSendBuf = NULL;
unsigned char recv_buf[recv_buf_size];
unsigned char send_buf[send_buf_size];

unsigned char rsctl_ff = 0x08;

unsigned char etc_calc_bcc(unsigned char *pucData, unsigned int u32Length)
{
    unsigned int u32Loop = 0;
    unsigned char u8bcc = 0;

    for(u32Loop = 0; u32Loop < u32Length; ++u32Loop)
    {
        u8bcc ^= pucData[u32Loop];
    }

    return u8bcc;
}

unsigned char *state_first_ff(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    u32RecvLen = 0;
    pRecvBuf = recv_buf;
    memset(pRecvBuf, 0, recv_buf_size);

    if(0xFF == u8Data)
    {
        eState = STATE_RSCTL;
    }

    return NULL;
}

unsigned char *state_ff_rsctl(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    if(0xFF == u8Data)
    {
        eState = STATE_RSCTL;
    }
    else
    {
        eState = STATE_DATA;
        //rsctl_ff = (u8Data>>4)|(u8Data<<4);
    }

    return NULL;
}


unsigned char *state_ff_data(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    if (0xff == u8Data)
    {
        eState = STATE_FIRST_FF;
        *pu32DecodeLen = u32RecvLen - 1; // delete BCC byte
        return pRecvBuf;
    }
    else if(0xFE == u8Data)
    {
        eState = STATE_DATA_DECODE;
    }
    else
    {
        pRecvBuf[u32RecvLen++] = u8Data;
    }

    return NULL;
}

unsigned char *state_data_decode(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    if(0x01 == u8Data)
    {
        pRecvBuf[u32RecvLen++] = 0xFF;
        eState = STATE_DATA;
    }
    else if (0x00 == u8Data)
    {
        pRecvBuf[u32RecvLen++] = 0xFE;
        eState = STATE_DATA;
    }
    else
    {
        eState = STATE_FIRST_FF;
    }

    return NULL;
}

func_ptr func_array[] =
{
    state_first_ff,
    state_ff_rsctl,
    state_ff_data,
    state_data_decode,
};

unsigned char *etc_decode_ff_rsctl(unsigned char ch, unsigned int *decoded_len)
{
    return func_array[eState](ch, decoded_len);
}


unsigned char *etc_decode_ff_rsctl_optimise(unsigned char *recv, unsigned int recv_len, unsigned int *decode_len)
{
    unsigned int recv_index = 0;

    u32RecvLen = 0;
    pRecvBuf = recv_buf;
    memset(pRecvBuf, 0, recv_buf_size);

    // process STX
    for (recv_index = 0; recv_index < recv_len; recv_index++)
    {
        if(recv[recv_index] != 0xFF)
        {
            break;
        }
    }
    recv_index += 1; // jump rsctl

    // decode Data
    for(; recv_index < recv_len; recv_index++)
    {
        // get ETX
        if(recv[recv_index] == 0xFF)
        {
            if(u32RecvLen != 0)
            {
                u32RecvLen -= 1; // delete BCC byte
                *decode_len = u32RecvLen;
                return pRecvBuf;
            }
            break;
        }
        else if(recv[recv_index] == 0xFE)
        {
            if(recv[recv_index + 1] == 0x00)
            {
                pRecvBuf[u32RecvLen++] = 0xFE;
                recv_index++;
            }
            else if(recv[recv_index + 1] == 0x01)
            {
                pRecvBuf[u32RecvLen++] = 0xFF;
                recv_index++;
            }
        }
        else
        {
            pRecvBuf[u32RecvLen++] = recv[recv_index];
        }
    }
    return NULL;    
}



unsigned char *etc_encode_ff_rsctl(unsigned char *source, unsigned int source_len, unsigned int*p_encoded_len)
{
    unsigned int u32SendLen = 0;
    unsigned int u32Loop = 0;
    unsigned char bcc;

    pSendBuf = send_buf;
    memset(pSendBuf , 0, send_buf_size);

    if(source_len < send_buf_size) 
    {
        /* Set frame head */
        pSendBuf[u32SendLen++] = 0xFF;
        pSendBuf[u32SendLen++] = 0xFF;//lzw
        pSendBuf[u32SendLen++] = rsctl_ff;
        rsctl_ff = ((((rsctl_ff >> 4) + 1) % 10) << 4) | 0x08;

        /* Set frame data */
        for(u32Loop = 0; u32Loop < source_len; u32Loop++ )
        {
            if(0xFF == *(source + u32Loop)) 
            {
                pSendBuf[u32SendLen++] = 0xFE;
                pSendBuf[u32SendLen++] = 0x01;
            }
            else if(0xFE == *(source + u32Loop))
            {
                pSendBuf[u32SendLen++] = 0xFE;
                pSendBuf[u32SendLen++] = 0x00;
            }
            else
            {
                pSendBuf[u32SendLen++] = *(source + u32Loop);
            }
        }

        bcc = etc_calc_bcc(&pSendBuf[2], u32SendLen-2);//lzw
        if(0xFF == bcc)
        {
            pSendBuf[u32SendLen++] = 0xFE;
            pSendBuf[u32SendLen++] = 0x01;
        }
        else if(0xFE == bcc)
        {
			pSendBuf[u32SendLen++] = 0xFE;
            pSendBuf[u32SendLen++] = 0x00;
        }
        else
        {
        	pSendBuf[u32SendLen++] = bcc;
        }

        /*Set frame end */
        pSendBuf[u32SendLen++] = 0xFF;
    } 
    else
    {
        *p_encoded_len = 0;
        return NULL;
    }

    *p_encoded_len = u32SendLen;
    return pSendBuf;
}

