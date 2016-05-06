/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_dspdvs.h
*
*   作    者 :  l00312158
*
*   描    述 :  dsp_dvs模块对底软内接口
*
*   修改记录 :  2015年11月17日  v1.00  l00312158  创建
*************************************************************************/

#ifndef __BSP_DSPDVS_H__
#define __BSP_DSPDVS_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include "product_config.h"
#include "osl_types.h"
#include "drv_comm.h"


#ifdef CONFIG_DSPDVS
s32 bsp_dsp_dvs_init(void);

#else
static s32 inline bsp_dsp_dvs_init(void)
{
    return BSP_OK;
}

#endif

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_DSPDVS_H__ */

