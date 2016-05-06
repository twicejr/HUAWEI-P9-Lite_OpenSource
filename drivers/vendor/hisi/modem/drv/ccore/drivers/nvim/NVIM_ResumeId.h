

#ifndef _NVIM_RESUMEID_H
#define _NVIM_RESUMEID_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "product_config.h"

#if defined(DMT)
#include "comm_adapter.h"
#endif

extern unsigned short   g_ausNvResumeManufactureIdList[];

extern unsigned short   g_ausNvResumeUserIdList[];

extern unsigned short   g_ausNvResumeSecureIdList[];

#if defined(DMT)
/*lint -e553 */
#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)
extern unsigned short   g_ausNvResumeSkuSpecIdList[];
#endif
/*lint +e553 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* NV恢复表类型 */
enum NV_RESUME_ITEM
{
    NV_MANUFACTURE_ITEM = 0,
    NV_USER_ITEM,
    NV_SECURE_ITEM,
#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)
    NV_SKU_ITEM,
#endif
    NV_ITEM_BUTT
};
typedef unsigned int NV_RESUME_ITEM_ENUM_UINT32;

extern unsigned int NV_GetResumeNvIdNum(NV_RESUME_ITEM_ENUM_UINT32 enNvItem);

#else
extern unsigned long bsp_nvm_getRevertNum(unsigned long enNvItem);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif



#endif

