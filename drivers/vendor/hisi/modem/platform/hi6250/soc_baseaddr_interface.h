

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_BASEADDR_INTERFACE_H__
#define __SOC_BASEADDR_INTERFACE_H__

#include "soc_memmap_comm.h"
#include "hi_bbp_systime.h"
#include "hi_timer.h"
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 寄存器说明： */


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

#define DUMMY_ADDR_BASE 0


//#define SOC_BBP_GSM0_BASE_ADDR                          HI_GBBP_REG_BASE_ADDR
#define SOC_BBP_CDMA_BASE_ADDR          0xE12E0000  /* Cbbp */
#define SOC_Modem_DMAC_BASE_ADDR        0xE0210000  /* Edma1,12channel */
#define SOC_IPC_S_BASE_ADDR             0xFDF21000  /* Ipc */
#define SOC_SOCP_BASE_ADDR              0xFF030000  /* Socp */
#define SOC_AO_SCTRL_BASE_ADDR          0xFFF0A534  /* 32k SOC_AO_SCTRL_BASE_ADDR */

#define SOC_MODEM_SCTRL_BASE_ADDR       0xFFF0A000  /* ASIC上在AP侧 */

#define SOC_ABB_CFG_BASE_ADDR           0xE1FA0000  /* uwAbbCfgAddr */
#define SOC_BBP_COMM_BASE_ADDR          0xE1F80000  /* uwBbpcomAddr */

#define SOC_BBP_COMM_ON_BASE_ADDR       0xFFF12000  /* uwBbpcomOnAddr */
#define SOC_BBP_GLB_ON_BASE_ADDR        0xFFF12000

#define SOC_BBP_WCDMA_BASE_ADDR         0xE1200000
#define SOC_BBP_COMM_2_BASE_ADDR        0xE1280000  /* uwBbpcom2Addr */

#define SOC_BBP_WCDMA_ON_BASE_ADDR      ( 0xFFF12100 )
/* UC2 */
#define SOC_BBP_CDMA_ON_BASE_ADDR       ( 0xFFF12100 )

#define SOC_PMU_SSI_BASE_ADDR             ( 0xFFF34000 )   /* PMU */
#define SOC_PA_POWER_ON_BASE_ADDR        ( 0xe8a18080 )  /* uwPaPowerOnBaseAddr */
#define SOC_BBP_WDG_BASE_ADDR            ( 0xE0211000 )

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_baseaddr_interface.h */

