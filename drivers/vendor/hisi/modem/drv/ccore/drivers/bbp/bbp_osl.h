

#ifndef __HI_BBP_OSL_H__
#define __HI_BBP_OSL_H__

#include "osl_types.h"
#include "osl_bio.h"

#ifdef __cplusplus
extern "C" {
#endif

/*ÉèÖÃÄ³bitÎ»*/
static __inline__ void bbp_bit_set(u32 addr,u32 mask)
{
    writel(readl(addr)|(mask),addr);
}
static __inline__ void bbp_bit_clr(u32 addr,u32 mask)
{
    writel(readl(addr)&~(mask),addr);
}
static __inline__ unsigned int bbp_bit_get(u32 addr,u32 mask)
{
    return (readl(addr)&mask);
}
static __inline__ unsigned int bbp_bit_chk(u32 addr,u32 mask)
{
    return (mask == (readl(addr)&mask));
}

#ifdef __cplusplus
}
#endif

#endif
