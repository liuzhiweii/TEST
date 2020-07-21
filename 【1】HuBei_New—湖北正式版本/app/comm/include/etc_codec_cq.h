#ifndef __ETC_CODEC_CQ__
#define __ETC_CODEC_CQ__


extern unsigned char *etc_decode_cq(unsigned char ch, unsigned int *decoded_len);

extern unsigned char *etc_encode_cq(unsigned char *source, unsigned int source_len, unsigned int*p_encoded_len);


#endif
