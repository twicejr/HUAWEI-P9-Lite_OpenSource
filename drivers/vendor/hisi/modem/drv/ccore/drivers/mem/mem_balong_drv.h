
#ifndef    _BSP_MEM_DRV_H_
#define    _BSP_MEM_DRV_H_

#include "product_config.h"
#include "bsp_sram.h"
#include "bsp_shared_ddr.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ASIC2 调试 */

/**************************************************************************
  宏定义
**************************************************************************/
/* 主核定义 */
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#define BSP_MEM_MAIN_PART
#endif

/* 长度定义 */
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#define MEM_NORM_DDR_POOL_SIZE      (512*1024)
#else
#define MEM_NORM_DDR_POOL_SIZE      (1024*1024)/*2^n*4K*/
#endif

#define MEM_ICC_DDR_POOL_SIZE       (SHM_SIZE_MEMMGR)
#define MEM_ICC_AXI_POOL_SIZE       (SRAM_SIZE_DYNAMIC_SEC)

/* Mem 全局变量放在AXI中 */
#define MEM_CTX_ADDR                ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MEMMGR_FLAG)


/* 基地址定义 */
#define MEM_NORM_DDR_POOL_BASE_ADDR (memalign(32, MEM_NORM_DDR_POOL_SIZE))
#define MEM_ICC_AXI_POOL_BASE_ADDR  ((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_DYNAMIC_SEC)
#define MEM_ICC_DDR_POOL_BASE_ADDR  ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MEMMGR)


/* 使用ACP模式不需要刷 Cache */
//#define MEM_USE_ACP

#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif /* _BSP_MEM_DRV_H_ */



