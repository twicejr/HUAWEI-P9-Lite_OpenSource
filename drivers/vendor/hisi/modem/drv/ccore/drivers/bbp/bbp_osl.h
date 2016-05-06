/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bbp_osl.c
*
*   作    者 :  x00195528
*
*   描    述 :
*
*   修改记录 :  2013年2月2日  v1.00  x00195528  创建
*************************************************************************/

#ifndef __HI_BBP_OSL_H__
#define __HI_BBP_OSL_H__

#include "osl_types.h"
#include "osl_bio.h"

#ifdef __cplusplus
extern "C" {
#endif

/*设置某bit位*/
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
