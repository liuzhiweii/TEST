
#ifndef __ETC_CODEC_FF_CRC__
#define __ETC_CODEC_FF_CRC__


extern unsigned char *etc_decode_ff_crc(unsigned char ch, unsigned int *decoded_len);

extern unsigned char *etc_encode_ff_crc(unsigned char *source, unsigned int source_len, unsigned int*p_encoded_len);

unsigned char *etc_decode_ff_crc_optimise(unsigned char *recv, unsigned int recv_len, unsigned int *decode_len);
#endif





