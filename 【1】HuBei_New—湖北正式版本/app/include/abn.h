#ifndef __ABN_H__
#define __ABN_H__


#ifdef __cplusplus
extern "C"
{
#endif
void record_abn(char* file_name, int line, const char *fmt, ...);
void record_log(char* file_name, int line, const char *fmt, ...);

#define abn_debug(...)  record_abn(__FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...)  record_log(__FILE__, __LINE__, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif