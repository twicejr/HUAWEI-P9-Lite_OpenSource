/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MemoryMap.h
  版 本 号   : 初稿
  作    者   : file
  生成日期   : 2010年06月25日
  最近修改   :
  功能描述   : Sytem Memory Map
  函数列表   :
  修改历史   :
  1.日    期   : 2010年06月25日
    作    者   : l00131505
    修改内容   : 创建文件

******************************************************************************/
#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "MemoryLayout.h"

/* GU PS预留内存物理地址、虚拟地址转定义 */
#define ECS_MDDR_RESERVE_BASE_ADDR          (DDR_GU_ADDR)
#define ECS_MDDR_RESERVE_BASE_ADDR_VIRT     DDR_GU_ADDR_VIRT

/*AXI Memory Base*/
#define AXI_PHY_BASE_ADDR                   (GLOBAL_AXI_MEM_BASE_ADDR_PHY)

/*TTF DICC Spinlock Memory*/
#define ECS_TTF_DICC_SPINLOCK_ADDR          (MEMORY_AXI_DICC_ADDR - GLOBAL_AXI_MEM_BASE_ADDR + AXI_PHY_BASE_ADDR)
#define ECS_TTF_ACPU_FREE_MEM_CNT_ADDR      (ECS_TTF_DICC_SPINLOCK_ADDR + 4)

/*                       GU PS预留内存

               +---------------------+-------+ --> 0x33100000
               |   TTF预留内存       |9M+704K|
               +---------------------+-------+ --> 0x33AB0000
               |   ARM/DSP内存       |2M+640K|
               +---------------------+-------+ --> 0x33D50000
               |    UPA              | 128K  |
               +---------------------+-------+ --> 0x33D70000
               |    CQI              | 13K   |
               +---------------------+-------+ --> 0x33D73400
               |    APT              | 33K   |
               +---------------------+-------+ --> 0x33D7B800
               |    ET(尚未使用)     | 18K   |
               +---------------------+-------+ --> 0x33D80000
               |   BSP_Master        | 0K    |
               +---------------------+-------+ --> 0x33D80000
               |   NV共享区          | 192K  |
               +---------------------+-------+ --> 0x33DB0000
               |   TTF DICC          | 64K   |
               +---------------------+-------+ --> 0x33DC0000
               |   未使用            | 352K  |
               +---------------------+-------+ --> 0x33E18000
*/

#define ECS_TTF_SIZE                        (0x00860000)
#define HUTAF_HLT_MEM_SIZE                  (0x00000000)/*HUTAF使用2M*/
#define ECS_TTF_SAVE_SIZE                   (0x00000000)/*TTF裁掉,备用。2.5MB-2MB GUL分支临时修改*/
#define ECS_BBPHAC_SIZE                     (0x00000000)/*320K*/
#define ECS_ARM_DSP_BUFFER_SIZE             (0x00250000)
#define ECS_UPA_SIZE                        (0x00024000)
#define ECS_CQI_SIZE                        (0x00003400)
#define ECS_APT_SIZE                        (0x00008400)
#define ECS_ET_SIZE                         (0x00004800)
#define ECS_BBP_MASTER_SIZE                 (0x00000000)
#define ECS_NV_SIZE                         (0x00000000)
#define ECS_TTF_DICC_SIZE                   (0x00000000)
#define ZSP_UP_SIZE                         (0x00008000)/*monan for v9r1bbit
 */
#define ECS_MDDR_RESERVE_SIZE               (ECS_TTF_SIZE + ECS_BBPHAC_SIZE+ ECS_ARM_DSP_BUFFER_SIZE + ECS_UPA_SIZE \
                                             + ECS_CQI_SIZE + ECS_APT_SIZE + ECS_ET_SIZE + ECS_BBP_MASTER_SIZE \
                                             + ECS_NV_SIZE + ECS_TTF_DICC_SIZE + ZSP_UP_SIZE + HUTAF_HLT_MEM_SIZE + ECS_TTF_SAVE_SIZE)

#define ECS_TTF_BASE_ADDR                   (ECS_MDDR_RESERVE_BASE_ADDR)
#define HUTAF_HLT_MEM_ADDR                  (ECS_TTF_BASE_ADDR            + ECS_TTF_SIZE)
#define ECS_TTF_SAVE_ADDR                   (HUTAF_HLT_MEM_ADDR           + HUTAF_HLT_MEM_SIZE)
#define ECS_BBPHAC_BASE_ADDR                (ECS_TTF_SAVE_ADDR            + ECS_TTF_SAVE_SIZE)
#define ECS_ARM_DSP_BUFFER_BASE_ADDR        (ECS_BBPHAC_BASE_ADDR         + ECS_BBPHAC_SIZE)
#define ECS_UPA_BASE_ADDR                   (ECS_ARM_DSP_BUFFER_BASE_ADDR + ECS_ARM_DSP_BUFFER_SIZE)
#define ECS_CQI_BASE_ADDR                   (ECS_UPA_BASE_ADDR            + ECS_UPA_SIZE)
#define ECS_APT_BASE_ADDR                   (ECS_CQI_BASE_ADDR            + ECS_CQI_SIZE)
#define ECS_ET_BASE_ADDR                    (ECS_APT_BASE_ADDR            + ECS_APT_SIZE)
#define ECS_BBP_MASTER_BASE_ADDR            (ECS_ET_BASE_ADDR             + ECS_ET_SIZE)
#define ECS_NV_BASE_ADDR                    (ECS_BBP_MASTER_BASE_ADDR     + ECS_BBP_MASTER_SIZE)
#define ECS_TTF_DICC_ADDR                   (ECS_NV_BASE_ADDR             + ECS_NV_SIZE)
#define ZSP_UP_ADDR                         (ECS_TTF_DICC_ADDR            + ECS_TTF_DICC_SIZE)/*monan for v9r1bbit
 */

/*TTF Memory Virtual Address*/
#define ECS_TTF_BASE_ADDR_VIRT              (ECS_MDDR_RESERVE_BASE_ADDR_VIRT)
#define ECS_BBPHAC_BASE_ADDR_VIRT           (ECS_BBPHAC_BASE_ADDR - ECS_MDDR_RESERVE_BASE_ADDR \
                                             + ECS_MDDR_RESERVE_BASE_ADDR_VIRT)

/*NV Virtual Address*/
#define ECS_NV_BASE_ADDR_VIRT               (ECS_NV_BASE_ADDR - ECS_MDDR_RESERVE_BASE_ADDR \
                                             + ECS_MDDR_RESERVE_BASE_ADDR_VIRT)

/*DICC Virtual Address*/
#define ECS_TTF_DICC_ADDR_VIRT              (ECS_TTF_DICC_ADDR - ECS_MDDR_RESERVE_BASE_ADDR \
                                             + ECS_MDDR_RESERVE_BASE_ADDR_VIRT)

/*HUTAF Virtual Address*/
#define HUTAF_HLT_MEM_ADDR_VIRT             (HUTAF_HLT_MEM_ADDR - ECS_MDDR_RESERVE_BASE_ADDR \
                                             + ECS_MDDR_RESERVE_BASE_ADDR_VIRT)

/*Memory size check*/
#if (ECS_MDDR_RESERVE_SIZE > DDR_GU_SIZE)
#error GU PS used size (ECS_MDDR_RESERVE_SIZE) beyond the reserve size (DDR_GU_SIZE)
#endif

/*Memory size check*/
#if 0 /* TODO fix, hujianbo */
#if ((GLOBAL_MEM_MCORE_ACP_ADDR + GLOBAL_MEM_MCORE_ACP_SIZE) != (GLOBAL_MEM_L_RESERVED_ADDR + GLOBAL_MEM_L_RESERVED_SIZE))
#error GU PS used size (GLOBAL_MEM_MCORE_ACP_ADDR + GLOBAL_MEM_MCORE_ACP_SIZE) beyond the reserve size (GLOBAL_MEM_L_RESERVED_ADDR + GLOBAL_MEM_L_RESERVED_SIZE)
#endif
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* MEMORY_MAP_H */

