
#include <string.h>
#include "etc_codec_cq.h"
#include "logm.h"


#define recv_buf_size  2048
#define send_buf_size 2048

enum codec_state
{
    STATE_INIT = 0,
    STATE_AA,
    STATE_RSCTL,
    STATE_LEN_HIGH,
    STATE_LEN_LOW,
    STATE_FX,
    STATE_DATA,
    STATE_BCC
};

enum codec_state state  = STATE_INIT;

typedef  unsigned char *(*func_ptr)(unsigned char ch, unsigned int *len);
unsigned char recv_buf[recv_buf_size];
unsigned int recv_pos;
unsigned char send_buf[send_buf_size];
unsigned char recv_rsctl;
unsigned int recv_frame_len;
unsigned char send_rsctl = 0x01;



unsigned char *state_init(unsigned char ch, unsigned int *decoded_len)
{
    recv_pos = 0;
    recv_frame_len = 0;

    if(ch == 0x55)
    {
        state = STATE_AA;
    }
    
    return NULL;
}

unsigned char *state_aa(unsigned char ch, unsigned int *decoded_len)
{
    if(ch == 0xaa)
    {
        state = STATE_RSCTL;
    }
    else
    {
        state = STATE_INIT;
    }

    return NULL;
}

unsigned char *state_rsctl(unsigned char ch, unsigned int *decoded_len)
{
    state = STATE_LEN_HIGH;
    recv_rsctl = ch;
    return NULL;
}

unsigned char *state_len_high(unsigned char ch, unsigned int *decoded_len)
{
    recv_frame_len = (unsigned int)ch << 8;
    state = STATE_LEN_LOW;

    return NULL;
}

unsigned char *state_len_low(unsigned char ch, unsigned int *decoded_len)
{
    recv_frame_len += (unsigned char)ch;
    state = STATE_FX;

    return NULL;
}

unsigned char *state_fx(unsigned char ch, unsigned int *decoded_len)
{
    recv_buf[recv_pos] = ch;
    recv_pos++;
    state = STATE_DATA;

    return NULL;
}

unsigned char *state_data(unsigned char ch, unsigned int *decoded_len)
{
    if(recv_pos >= recv_buf_size)
    {
        state = STATE_INIT;
    }

    recv_buf[recv_pos] = ch;
    recv_pos++;

    if(recv_pos == (recv_frame_len+1))
    {
        state = STATE_BCC;
    }

    return NULL;
}

unsigned char *state_bcc(unsigned char ch, unsigned int *decoded_len)
{
    state = STATE_INIT;
    *decoded_len = recv_pos;
    return recv_buf;
}

func_ptr func_array[] = 
{
    state_init,
    state_aa,
    state_rsctl,
    state_len_high,
    state_len_low,
    state_fx,
    state_data,
    state_bcc
};


unsigned char * etc_decode_cq(unsigned char ch, unsigned int *decoded_len)
{
    return func_array[state](ch, decoded_len);
}

unsigned char calc_bcc(unsigned char *data, unsigned int len)
{
    int i;
    unsigned char bcc = 0;

    for(i=0; i<len; ++i)
    {
        bcc ^= data[i];
    }

    return bcc;
}

unsigned char *etc_encode_cq(unsigned char *source, unsigned int source_len, unsigned int*p_encoded_len)
{    
    unsigned int encoded_len = source_len + 6;

    logm_debug("source_len=%d,encoded_len=%d\r\n",source_len,encoded_len);
    if(encoded_len > send_buf_size)
    {
    	logm_debug("return null,source_len=%d,encoded_len=%d\r\n",source_len,encoded_len);
        return NULL;
    }

    send_buf[0] = 0x55;
    send_buf[1] = 0xaa;
    send_buf[2] = send_rsctl;
    send_buf[3] = (source_len-1)>>8;
    send_buf[4] = (source_len-1);
    memcpy(&send_buf[5], source, source_len);
    send_buf[source_len+5] = calc_bcc(&send_buf[2], (encoded_len-3));

    *p_encoded_len = encoded_len;
    send_rsctl = (send_rsctl == 0x07) ? 0x01 : (send_rsctl+1);

    return send_buf;
}

