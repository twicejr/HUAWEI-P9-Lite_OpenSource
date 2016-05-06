

#ifndef __HWTC_KERNEL_H__
#define __HWTC_KERNEL_H__ 


#include "hwtc_id.h"

#define HWTC_TAG_OFFSET                          0
/* TODO ADD OTHER TAG */
#define HWTC_TAG_NEVER                           0x00000000
#define HWTC_TAG_CAMERA                          (1 << HWTC_TAG_OFFSET)
#define HWTC_TAG_DISPLAY                         (2 << HWTC_TAG_OFFSET)







/* #ifndef HWTC_TAG */
/* #define HWTC_TAG HWTC_TAG_NEVER */
/* #endif */

void hwtc_begin(uint32_t tag, const char *name, int32_t *id, uint32_t threshold);
void hwtc_end(uint32_t tag, const char *name, int32_t *id, int32_t *output);

#define HWTC_BEGIN(name, id) \
do{ \
    if (likely(HWTC_KLID_LAST < HWTC_KLID_END)) { \
        hwtc_begin(HWTC_TAG, name, &id, 0); \
    } \
}while(0)

#define HWTC_MONITOR_BEGIN(name, id, threshold) \
do{ \
    if (likely(HWTC_KLID_LAST < HWTC_KLID_END)) { \
        hwtc_begin(HWTC_TAG, name, &id, threshold); \
    } \
}while(0)

#define HWTC_END(name, id, output) \
do{ \
    if (likely((uint32_t)HWTC_KLID_LAST < (uint32_t)HWTC_KLID_END)) { \
        hwtc_end(HWTC_TAG, name, &id, &output); \
    } \
}while(0)


#endif /*__HWTC_KERNEL_H__*/
