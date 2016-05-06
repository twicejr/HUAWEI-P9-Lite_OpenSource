/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_pdlock.h
*
*   作    者 :  l00312158
*
*   描    述 :  pdlock模块对底软内接口
*
*   修改记录 :  2015年6月16日  v1.00  l00312158  创建
*************************************************************************/

#ifndef __BSP_PDLOCK_H__
#define __BSP_PDLOCK_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include "product_config.h"
#include "osl_types.h"
#include "drv_comm.h"


#ifdef CONFIG_PDLOCK
s32 bsp_pdlock_init(void);
#else
static s32 inline bsp_pdlock_init(void)
{
    return BSP_OK;
}
#endif

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_PDLOCK_H__ */
