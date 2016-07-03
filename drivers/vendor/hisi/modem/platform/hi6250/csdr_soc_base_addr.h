

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __CSDR_SOC_BASE_ADDR_H__
#define __CSDR_SOC_BASE_ADDR_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/


#include "csdr_platform.h"

#define SOC_BBP_CDMA_BASE_ADDR          (g_stPlatformContext.stBaseAddr.uwBbpCdmaBaseAddr)
#define SOC_BBP_CDMA_ON_BASE_ADDR       (g_stPlatformContext.stBaseAddr.uwBbpCdmaOnBaseAddr)
#define SOC_Modem_DMAC_BASE_ADDR        (g_stPlatformContext.stBaseAddr.uwEdmaBaseAddr)
#define SOC_IPC_S_BASE_ADDR             (g_stPlatformContext.stBaseAddr.uwIpcmBaseAddr)
#define SOC_SOCP_BASE_ADDR              (g_stPlatformContext.stBaseAddr.uwSocpBaseAddr)
#define SOC_AO_SCTRL_BASE_ADDR          (g_stPlatformContext.stBaseAddr.uw32kBaseAddr)
#define SOC_MODEM_SCTRL_BASE_ADDR       (g_stPlatformContext.stBaseAddr.uwSysctrlBaseAddr)
#define SOC_ABB_CFG_BASE_ADDR           (g_stPlatformContext.stBaseAddr.uwAbbCfgAddr)
#define SOC_BBP_COMM_BASE_ADDR          (g_stPlatformContext.stBaseAddr.uwBbpcomAddr)
#define SOC_BBP_COMM_ON_BASE_ADDR       (g_stPlatformContext.stBaseAddr.uwBbpcomOnAddr)
#define SOC_BBP_GLB_ON_BASE_ADDR        (g_stPlatformContext.stBaseAddr.uwBbpGlbOnAddr)
#define SOC_BBP_WCDMA_BASE_ADDR         (g_stPlatformContext.stBaseAddr.uwWbbpBaseAddr)
#define CSDR_DDR_RAM_BASE               (g_stPlatformContext.stBaseAddr.uwDataMailboxAddr)
#define SOC_BBP_COMM_2_BASE_ADDR        (g_stPlatformContext.stBaseAddr.uwBbpcom2Addr)
#define SOC_PMU_SSI_BASE_ADDR           (g_stPlatformContext.stBaseAddr.uwPmuSsiAddr)
#define SOC_PA_POWER_ON_BASE_ADDR       (g_stPlatformContext.stBaseAddr.uwPaPowerOnBaseAddr)
#define CSDR_HRPD_HARQ_MEM_ADDR_IN_DDR  (g_stPlatformContext.stBaseAddr.uwHarqMemAddr)
#define SOC_BBP_WDG_BASE_ADDR           (g_stPlatformContext.stBaseAddr.uwWatchDogAddr)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/



/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/



/*****************************************************************************
  7 UNION定义
*****************************************************************************/





/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of csdr_soc_base_addr.h */


