

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

