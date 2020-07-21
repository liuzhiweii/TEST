
#include <string.h>
#include "etc_codec_ff_crc.h"
#include "logm.h"


const unsigned short crc16_ccitt_table[256] =
{
0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};


#define PROTOCOL_VER     (0x00)

#define recv_buf_size  2048
#define send_buf_size 2048


typedef enum decode_state_e 
{
    STATE_FIRST_FF = 0,
    STATE_SECOND_FF,
    STATE_VER,
    STATE_SEQ,
    STATE_LEN_RES1,
    STATE_LEN_RES2,
    STATE_LEN_HIGH,
    STATE_LEN_LOW,
    STATE_DATA,
    STATE_CRC
} e_decode_state_crc;


typedef  unsigned char *(*func_ptr)(unsigned char u8Data, unsigned int *pu32DecodeLen);


e_decode_state_crc eState_crc = STATE_FIRST_FF;

unsigned char *pRecvBufcrc = NULL;
unsigned char *pSendBufcrc = NULL;
unsigned char recv_buf_crc[recv_buf_size];
unsigned char send_buf_crc[send_buf_size];

unsigned char send_seq = 0x01;
unsigned char protocol_ver = 0x00;
unsigned int recv_frame_len_crc = 0;
unsigned int recv_pos_crc;


unsigned short do_crc(unsigned short reg_init, unsigned char *message, unsigned int len)
{
    unsigned short crc_reg = reg_init;
         
    while (len--)
    {
        crc_reg = (crc_reg >> 8) ^ crc16_ccitt_table[(crc_reg ^ *message++) & 0xff];
    }        
       
    return ~crc_reg;
}


int check_crc(unsigned char *pdata, unsigned char len, unsigned short crcValue)
{
    unsigned short crc_reg = 0;
    crc_reg = do_crc(0xffff, pdata, len);
    //logm_debug("crcValue = %x, crc_reg = %x \n", crcValue, crc_reg);
    if (crc_reg == crcValue)
    {
        return 0;
    }
    else
    {
        crc_reg = do_crc(0x0000, pdata, len);
        if (crc_reg == crcValue)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
}


unsigned char *state_first_ff_crc(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    pRecvBufcrc = recv_buf_crc;    
    recv_pos_crc = 0;
    recv_frame_len_crc = 0;
    memset(pRecvBufcrc, 0, recv_buf_size);

    if(0xFF == u8Data)
    {
        eState_crc = STATE_SECOND_FF;
    }

    return NULL;
}

unsigned char *state_second_ff_crc(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    if(0xFF == u8Data) 
    {
        eState_crc = STATE_VER;
    }
    else
    {
        eState_crc = STATE_FIRST_FF;
    }

    return NULL;
}

unsigned char *state_ver_crc(unsigned char u8Data, unsigned int *pu32DecodeLen)
{    
    protocol_ver = u8Data;
    if(0xFF != u8Data)
    {
        eState_crc = STATE_SEQ;    
    }

    return NULL;
}

unsigned char *state_seq_crc(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    eState_crc = STATE_LEN_RES1;
    return NULL;
}

unsigned char *state_len_res1_crc(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    eState_crc = STATE_LEN_RES2;
    return NULL;
}

unsigned char *state_len_res2_crc(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    eState_crc = STATE_LEN_HIGH;
    return NULL;
}

unsigned char *state_len_high_crc(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    recv_frame_len_crc = (unsigned int)u8Data << 8;
    eState_crc = STATE_LEN_LOW;
    return NULL;
}

unsigned char *state_len_low_crc(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    recv_frame_len_crc += (unsigned char)u8Data;
    eState_crc = STATE_DATA;
    return NULL;
}

unsigned char *state_data_crc(unsigned char u8Data, unsigned int *pu32DecodeLen)
{
    if(recv_pos_crc >= recv_buf_size)
    {
        eState_crc = STATE_FIRST_FF;
    }

    recv_buf_crc[recv_pos_crc] = u8Data;
    recv_pos_crc++;

    if(recv_pos_crc == recv_frame_len_crc)
    {
        eState_crc = STATE_CRC;
    }
    return NULL;
}

unsigned char *state_crc(unsigned char ch, unsigned int *pu32DecodeLen)
{
    eState_crc = STATE_FIRST_FF;
    *pu32DecodeLen = recv_pos_crc;
    return recv_buf_crc;
}

func_ptr func_array_crc[] =
{
    state_first_ff_crc,
    state_second_ff_crc,
    state_ver_crc,
    state_seq_crc,
    state_len_res1_crc,
    state_len_res2_crc,
    state_len_high_crc,
    state_len_low_crc,    
    state_data_crc,
    state_crc,
};


unsigned char *etc_decode_ff_crc(unsigned char ch, unsigned int *decoded_len)
{
    return func_array_crc[eState_crc](ch, decoded_len);
}

unsigned char *etc_decode_ff_crc_optimise(unsigned char *recv, unsigned int recv_len, unsigned int *decode_len)
{
    unsigned int recv_index = 0;
    unsigned int ver_index = 0;
    unsigned short check_crc = 0x00;
    unsigned char protocol_version;    

    pRecvBufcrc = recv_buf_crc;    
    recv_pos_crc = 0;
    recv_frame_len_crc = 0;
    memset(pRecvBufcrc, 0, recv_buf_size);

    /* process STX */
    for(recv_index = 0; recv_index < recv_len; recv_index++)
    {
        if(recv[recv_index] != 0xFF)
        {
            break;
        }
    }
    
    if(recv_index >= recv_len)
    {
        /* decode failed */
        return NULL;
    }

    /* get version_pos */
    ver_index = recv_index;
    /* get VER */
    protocol_version = recv[recv_index++];
    /* jump SEQ */
    recv_index++;

    /* get length of Data */
    if(protocol_version == 0x00)
    {
        /* jump two bytes */
        recv_index += 2;
        recv_frame_len_crc += recv[recv_index++] << 8;
        recv_frame_len_crc += recv[recv_index++];        
    }
    else
    {
        recv_frame_len_crc += recv[recv_index++] << 24;
        recv_frame_len_crc += recv[recv_index++] << 16;
        recv_frame_len_crc += recv[recv_index++] << 8;
        recv_frame_len_crc += recv[recv_index++];        
    }

    /* decode Data */
    for(; recv_index < recv_len; recv_index++)
    {
        /* decode completed */
        if(recv_pos_crc == recv_frame_len_crc)
        {
            *decode_len = recv_pos_crc;

        #if 0
            /* calc CRC,  CRC-16/X25,  poly: 0x1021 */
            check_crc = do_crc(0xFFFF, &recv[ver_index], recv_pos_crc + 6);
            /* check CRC */
            if(check_crc != ((recv[recv_index] << 8) | recv[recv_index + 1]))
            {
                return NULL;
            }
        #endif
        
            /* check CRC ok, decode successfully */
            return recv_buf_crc;
        }
        /* index overflow buffer_len */
        else if((recv_index >= recv_buf_size))
        {
            return NULL;
        }

        /* get data from recv_frame */
        recv_buf_crc[recv_pos_crc++] = recv[recv_index];
    }
    return NULL;
}

unsigned char *etc_encode_ff_crc(unsigned char *source, unsigned int source_len, unsigned int*p_encoded_len)
{
    unsigned short crc;

    pSendBufcrc = send_buf_crc;
    memset(pSendBufcrc , 0, send_buf_size);

    if(source_len < send_buf_size) 
    {
        /* Set frame head */
        pSendBufcrc[0] = 0xFF;
        pSendBufcrc[1] = 0xFF;
        pSendBufcrc[2] = PROTOCOL_VER;
        pSendBufcrc[3] = send_seq;        
        pSendBufcrc[4] = 0x00;
        pSendBufcrc[5] = 0x00;
        pSendBufcrc[6] = source_len >> 8;
        pSendBufcrc[7] = source_len;
        memcpy(&pSendBufcrc[8], source, source_len);

        crc = do_crc(0xFFFF, &pSendBufcrc[2], source_len + 6);

        pSendBufcrc[8 + source_len] = crc >> 8;
        pSendBufcrc[9 + source_len] = crc;

        *p_encoded_len = source_len + 10;  // 8 Bytes cmd_head,  2 bytes CRC
        
        send_seq = (send_seq == 0x09) ? 0x01 : (send_seq + 1);
    } 
    else
    {
        *p_encoded_len = 0;
        return NULL;
    }
    return pSendBufcrc;
}

