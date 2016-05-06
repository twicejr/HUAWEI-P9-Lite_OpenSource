/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  pm_om_platform.H
*
*   作    者 :  y00184236
*
*   描    述 :  平台相关头文件
*
*   修改记录 :  2014年11月17日  v1.00  y00184236  创建
*************************************************************************/

#ifndef __PM_OM_PLATFORM_H__
#define __PM_OM_PLATFORM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <libc.h>
#include <bsp_dump.h>
#include <bsp_icc.h>

#define PM_OM_DUMP_ID           DUMP_M3_PM_OM
#define PM_OM_DUMP_SIZE         (0x8000)
#define PM_OM_ICC_CHN_ID        (ICC_CHANNEL_ID_MAKEUP(ICC_CHN_MCORE_ACORE, MCORE_ACORE_FUNC_PM_OM))
#define PM_OM_CPUID             (ICC_CPU_MCU)

int pm_om_fwrite_trigger(void);
static inline int pm_om_platform_init(void){return 0;}

#ifdef __cplusplus
}
#endif

#endif  /* __PM_OM_PLATFORM_H__ */
