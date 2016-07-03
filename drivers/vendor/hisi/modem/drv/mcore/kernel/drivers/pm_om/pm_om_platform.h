

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
