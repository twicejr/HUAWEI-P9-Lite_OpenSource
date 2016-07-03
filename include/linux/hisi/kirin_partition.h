
#ifndef __KIRIN_PARTITION__
#define __KIRIN_PARTITION__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern int flash_find_ptn(const char* str, char* pblkname);
extern int get_cunrrent_total_ptn_num(void);
extern unsigned int flash_get_ptn_index(const char* pblkname);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

