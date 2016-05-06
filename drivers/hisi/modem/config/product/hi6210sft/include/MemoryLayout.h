/*************************************************************************
*   版权所有(C) 1987-2004, 深圳华为技术有限公司.
*
*   文 件 名 :  MemoryLayout.h
*
*   作    者 :  liumengcun
*
*   描    述 :  单板整体内存分配
*
*   修改记录 :  2011年12月20日  v1.00  liumengcun  创建
*
*************************************************************************/
#ifndef __MEMMORY_LAYOUT_H__
#define __MEMMORY_LAYOUT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "product_config.h"
#include "global_ddr_map.h"
#include "global_sram_map.h"
#include "general_sram_map.h"


/* MCORE使用内存 */
#define GLOBAL_MEM_MCORE_BASE_ADDR             (MODEM_SYS_MEM_ADDR)
#define GLOBAL_MEM_MCORE_SIZE                  (MODEM_SYS_MEM_SIZE)


/* 给GU预留的内存 */
#define GLOBAL_MEM_GU_RESERVED_ADDR            (GU_RESERVED_MEM_ADDR)
#define GLOBAL_MEM_GU_RESERVED_SIZE            (GU_RESERVED_MEM_SIZE)

/* 给L预留的内存 */
#define GLOBAL_MEM_LPS_RESERVED_ADDR            (LPS_RESERVED_MEM_ADDR)
#define GLOBAL_MEM_LPS_RESERVED_SIZE            (LPS_RESERVED_MEM_SIZE)

/* 异常记录内存 */
#define GLOBAL_MEM_EXCP_BASE_ADDR              (MODEM_DUMP_LOG_ADDR)
#define GLOBAL_MEM_EXCP_SIZE                   (MODEM_DUMP_LOG_SIZE)

/* 核间共享内存 */
#define GLOBAL_MEM_CORE_SHARE_ADDR             (IPC_SHARE_MEM_ADDR)
#define GLOBAL_MEM_CORE_SHARE_SIZE             (IPC_SHARE_MEM_SIZE)


/* HIFI内存 */
#define GLOBAL_MEM_HIFI_BASE_ADDR              (HIFI_SYS_MEM_ADDR)
#define GLOBAL_MEM_HIFI_SIZE                   (HIFI_SYS_MEM_SIZE)


/*vxworks高低地址配置*/
#define VXWORKS_HIGH_ADDR                      (GLOBAL_MEM_MCORE_BASE_ADDR + GLOBAL_MEM_MCORE_SIZE - 6*4096)  /*预留24K给DMR*/
#define VXWORKS_LOW_ADDR                       (GLOBAL_MEM_MCORE_BASE_ADDR + 0x4000)


/*-------------------------------------------------------------------------------
                            双核共享内存
  -------------------------------------------------------------------------------
                          -----------------------
                         |  SYNC(0x60)                |
                          -----------------------
                         |  MEM spinlock(0x20)        |
                          -----------------------
                         |  ICC(0x80)                 |
                          -----------------------
                         |  TENCILICA_TEXT(0)         |  4M
                          -----------------------
                         |  WAN(0x8000)               |
                          -----------------------
                         |  mailbox  (0x100000)       |
                          -----------------------
						  -----------------------
                         |  hifi     (0x1000)         |
                          -----------------------
                         |  MEM MGR M(0x2F6F00)       |
                          -----------------------
                          GLOBAL_MEM_CORE_SHARE_ADDR

-------------------------------------------------------------------------------*/
#define FEATURE_IPF_BF_NUM                          (64)
/* 从顶往下分配，以下地址和大小不可改变 */
#define MEMORY_RAM_CORESHARE_SIZE                   (GLOBAL_MEM_CORE_SHARE_SIZE)

#define MEMORY_RAM_CORESHARE_IPF_RULE_SIZE          (88 * FEATURE_IPF_BF_NUM)
#define MEMORY_RAM_CORESHARE_IPF_FLAG_SIZE          (4)
#define MEMORY_RAM_CORESHARE_SYNC_RESV              (96)
#define MEMORY_RAM_CORESHARE_MEM_RESV               (32)
#define MEMORY_RAM_CORESHARE_ICC_RESV               (128)
/* 多band预留内存,装备CT BT使用*/
#define CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE      (0x18000)

#define MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV    (0)
#define MEMORY_RAM_CORESHARE_MEM_WAN_SIZE           (0x8000)
#define MEMORY_RAM_CORESHARE_MAILBOX_SIZE           (0x100000)
#define MEMORY_RAM_CORESHARE_LOAD_HIFI_SIZE         (0x1000)
#define MEMORY_RAM_CORESHARE_RFS_MNTN_SIZE          (0x4000)
#define MEMORY_RAM_CORESHARE_CCORE_LOGBUF_SIZE  (0x40000)

#define MEMORY_RAM_CORESHARE_MEMMGR_ADDR            (GLOBAL_MEM_CORE_SHARE_ADDR)/*share mem start*/
#define MEMORY_RAM_CORESHARE_CCORE_LOGBUF_ADDR        (MEMORY_RAM_CORESHARE_MEMMGR_ADDR + MEMORY_RAM_CORESHARE_MEMMGR_SIZE)
#define MEMORY_RAM_CORESHARE_LOAD_HIFI_ADDR         (MEMORY_RAM_CORESHARE_CCORE_LOGBUF_ADDR + MEMORY_RAM_CORESHARE_CCORE_LOGBUF_SIZE)
#define MEMORY_RAM_CORESHARE_MAILBOX_ADDR           (MEMORY_RAM_CORESHARE_LOAD_HIFI_ADDR + MEMORY_RAM_CORESHARE_LOAD_HIFI_SIZE)
#define MEMORY_RAM_CORESHARE_MEM_WAN_ADDR           (MEMORY_RAM_CORESHARE_MAILBOX_ADDR + MEMORY_RAM_CORESHARE_MAILBOX_SIZE)
#define MEMORY_RAM_CORESHARE_TENCILICA_TEXT_ADDR    (MEMORY_RAM_CORESHARE_MEM_WAN_ADDR+MEMORY_RAM_CORESHARE_MEM_WAN_SIZE)
#define MEMORY_RAM_CORESHARE_ICC_ADDR               (MEMORY_RAM_CORESHARE_TENCILICA_TEXT_ADDR+MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV)
#define CORESHARE_MEM_TENCILICA_MULT_BAND_ADDR      ((MEMORY_RAM_CORESHARE_ICC_ADDR) + (MEMORY_RAM_CORESHARE_ICC_RESV))
#define MEMORY_RAM_CORESHARE_MEM_ADDR               (CORESHARE_MEM_TENCILICA_MULT_BAND_ADDR + CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE)
#define MEMORY_RAM_CORESHARE_SYNC_ADDR              (MEMORY_RAM_CORESHARE_MEM_ADDR + MEMORY_RAM_CORESHARE_MEM_RESV)
#define MEMORY_RAM_CORESHARE_RFS_MNTN_ADDR          (MEMORY_RAM_CORESHARE_SYNC_ADDR + MEMORY_RAM_CORESHARE_SYNC_RESV)
#define MEMORY_RAM_CORESHARE_IPF_FLAG_ADDR          (MEMORY_RAM_CORESHARE_RFS_MNTN_ADDR + MEMORY_RAM_CORESHARE_RFS_MNTN_SIZE)
#define MEMORY_RAM_CORESHARE_IPF_RULE_ADDR          (MEMORY_RAM_CORESHARE_IPF_FLAG_ADDR + MEMORY_RAM_CORESHARE_IPF_FLAG_SIZE)


#define MEMORY_AXI_IPF_ADDR                         (MEMORY_RAM_CORESHARE_IPF_RULE_ADDR + MEMORY_RAM_CORESHARE_IPF_RULE_SIZE)
#define MEMORY_AXI_IPF_SIZE                         (0x000007800)

/* ICC标识 */
#define MEMORY_AXI_ICC_ADDR                         (MEMORY_AXI_IPF_ADDR + MEMORY_AXI_IPF_SIZE)
#define MEMORY_AXI_ICC_SIZE                         (2048)

/* 内存管理 */
#define MEMORY_AXI_MEMMGR_FLAG_ADDR                 (MEMORY_AXI_ICC_ADDR + MEMORY_AXI_ICC_SIZE)
#define MEMORY_AXI_MEMMGR_FLAG_SIZE                 (1024)

/* BBE16标识 */
#define MEMORY_RAM_CORESHARE_BBE16_FLAG_ADDR        (MEMORY_AXI_MEMMGR_FLAG_ADDR + MEMORY_AXI_MEMMGR_FLAG_SIZE)
#define MEMORY_RAM_CORESHARE_BBE16_FLAG_SIZE        (8)

/* MBOX */
#define MEMORY_RAM_MBOX_DEVICE_ADDR                 (MEMORY_RAM_CORESHARE_BBE16_FLAG_ADDR + MEMORY_RAM_CORESHARE_BBE16_FLAG_SIZE)
#define MEMORY_RAM_MBOX_DEVICE_SIZE                 (2048)

#define MEMORY_RAM_CORESHARE_MEMMGR_SIZE            (MEMORY_RAM_CORESHARE_SIZE \
                                                    - MEMORY_RAM_CORESHARE_ICC_RESV \
                                                    - MEMORY_RAM_CORESHARE_MEM_RESV \
                                                    - MEMORY_RAM_CORESHARE_SYNC_RESV \
                                                    - MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV\
                                                    - MEMORY_RAM_CORESHARE_MEM_WAN_SIZE\
                                                    - MEMORY_RAM_CORESHARE_MAILBOX_SIZE\
                                                    - MEMORY_RAM_CORESHARE_LOAD_HIFI_SIZE\
                                                    - MEMORY_RAM_CORESHARE_RFS_MNTN_SIZE\
													- MEMORY_RAM_CORESHARE_IPF_FLAG_SIZE\
													- MEMORY_RAM_CORESHARE_IPF_RULE_SIZE\
													- CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE\
													- MEMORY_AXI_IPF_SIZE\
													- MEMORY_AXI_ICC_SIZE\
													- MEMORY_AXI_MEMMGR_FLAG_SIZE\
													- MEMORY_RAM_CORESHARE_BBE16_FLAG_SIZE\
													- MEMORY_RAM_CORESHARE_CCORE_LOGBUF_SIZE\
													- MEMORY_RAM_MBOX_DEVICE_SIZE)

/* 使用物理地址 */
#define CORESHARE_MEM_WAN_ADDR                      (MEMORY_RAM_CORESHARE_MEM_WAN_ADDR)
#define CORESHARE_MEM_WAN_SIZE                      (MEMORY_RAM_CORESHARE_MEM_WAN_SIZE)

#if(MEMORY_RAM_CORESHARE_MEMMGR_SIZE > MEMORY_RAM_CORESHARE_SIZE)
#error MEMORY_RAM_CORESHARE_MEMMGR_SIZE_(MEMORY_RAM_CORESHARE_MEMMGR_SIZE) > MEMORY_RAM_CORESHARE_SIZE_(MEMORY_RAM_CORESHARE_SIZE)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __MEMMORY_LAYOUT_H__ */

