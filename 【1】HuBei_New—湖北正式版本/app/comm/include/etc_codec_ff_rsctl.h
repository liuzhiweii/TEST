
#ifndef __ETC_CODEC_FF_RSCTL__
#define __ETC_CODEC_FF_RSCTL__


extern unsigned char *etc_decode_ff_rsctl(unsigned char ch, unsigned int *decoded_len);

unsigned char *etc_decode_ff_rsctl_optimise(unsigned char *recv, unsigned int recv_len, unsigned int *decode_len);

extern unsigned char *etc_encode_ff_rsctl(unsigned char *source, unsigned int source_len, unsigned int*p_encoded_len);

#endif





