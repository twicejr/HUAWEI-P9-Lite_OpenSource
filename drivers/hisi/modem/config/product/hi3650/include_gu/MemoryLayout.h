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

#include "bsp_shared_ddr.h"
#include "bsp_sram.h"
#include "bsp_memmap.h"
#if 0
/* 虚地址转换规则 */
#define IO_ADDRESS(x)         ((((x) & 0xF0000000) >> 4) | ((x) & 0x00FFFFFF) | 0xF0000000)

#if (defined(BOARD_ASIC) && defined(VERSION_V3R2))


#elif (defined (BOARD_FPGA) && defined(VERSION_V3R2))
/*monan for v9r1bbit*/
/* 单板DDR内存 */
#define GLOBAL_MEM_BASE_ADDR                   (0xC0000000)
#define GLOBAL_MEM_SIZE                        (0x10000000)           /*128MB*2*/
#define GLOBAL_MEM_BASE_ADDR_VIRT              (0xFC000000)

/*                      DDR 分配图

               +---------------------+---------+ --> 0xC0000000
               | A核内存             | 32M     |
               +---------------------+---------+ --> 0xC2000000
               | C核内存             | 48M     |
               +---------------------+---------+ --> 0xC5000000        虚地址统一从0xFC000000开始
               | GUPS预留内存        | 26M+672KB|
               +---------------------+---------+ --> 0xC6AA8000
               | 异常记录            | 512K    |
               +---------------------+---------+ --> 0xC6BA8000
               | 共享内存            | 640K    |
               +---------------------+---------+ --> 0xC6FA8000
               | HIFI内存(预留)      | 11M+352KB|
               +---------------------+---------+ --> 0xC7B00000
               | GUPS预留内存        | 5M      |
               +---------------------+---------+ --> 0xc8000000
*/
/* ACORE使用内存 */
#define GLOBAL_MEM_ACORE_BASE_ADDR             (GLOBAL_MEM_BASE_ADDR)       /*0x30000000*/
#define GLOBAL_MEM_ACORE_SIZE                  (0x02000000)  /*32MB*/


/* MCORE使用内存 */
#define GLOBAL_MEM_MCORE_BASE_ADDR             (GLOBAL_MEM_ACORE_BASE_ADDR + GLOBAL_MEM_ACORE_SIZE)
#define GLOBAL_MEM_MCORE_SIZE                  (0x03200000)  /*48MB+2MB GUL分支临时修改*/

/* 给GU预留的内存 */
#define GLOBAL_MEM_GU_RESERVED_ADDR            (GLOBAL_MEM_MCORE_BASE_ADDR + GLOBAL_MEM_MCORE_SIZE)
#define GLOBAL_MEM_GU_RESERVED_ADDR_VIRT       (GLOBAL_MEM_BASE_ADDR_VIRT)
#define GLOBAL_MEM_GU_RESERVED_SIZE            (0x018A8000)  /*26.672MB-2MB GUL分支临时修改*/


/* 异常记录内存 */
#define GLOBAL_MEM_EXCP_BASE_ADDR              (GLOBAL_MEM_GU_RESERVED_ADDR + GLOBAL_MEM_GU_RESERVED_SIZE)
#define GLOBAL_MEM_EXCP_BASE_ADDR_VIRT         (GLOBAL_MEM_GU_RESERVED_ADDR_VIRT + GLOBAL_MEM_GU_RESERVED_SIZE)
#define GLOBAL_MEM_EXCP_SIZE                   (0x00100000)

/* 核间共享内存 */
#define GLOBAL_MEM_CORE_SHARE_ADDR             (GLOBAL_MEM_EXCP_BASE_ADDR + GLOBAL_MEM_EXCP_SIZE)
#define GLOBAL_MEM_CORE_SHARE_ADDR_VIRT        (GLOBAL_MEM_EXCP_BASE_ADDR_VIRT + GLOBAL_MEM_EXCP_SIZE)
#define GLOBAL_MEM_CORE_SHARE_SIZE             (0x00400000)


/* HIFI内存 */
#define GLOBAL_MEM_HIFI_BASE_ADDR              (GLOBAL_MEM_CORE_SHARE_ADDR + GLOBAL_MEM_CORE_SHARE_SIZE)            /*0x33F38000*/
#define GLOBAL_MEM_HIFI_SIZE                   (0xB58000)/*(0x000C8000)
 */


/* 给L模预留的内存 */
#define GLOBAL_MEM_L_RESERVED_ADDR            (GLOBAL_MEM_HIFI_BASE_ADDR + GLOBAL_MEM_HIFI_SIZE)
#define GLOBAL_MEM_L_RESERVED_ADDR_VIRT       (GLOBAL_MEM_BASE_ADDR_VIRT + GLOBAL_MEM_GU_RESERVED_SIZE)
#define GLOBAL_MEM_L_RESERVED_SIZE            (0x00500000)


/*vxworks高低地址配置*/
#define VXWORKS_HIGH_ADDR                      (GLOBAL_MEM_MCORE_BASE_ADDR + GLOBAL_MEM_MCORE_SIZE - 6*4096)  /*预留24K给DMR*/
#define VXWORKS_LOW_ADDR                       (GLOBAL_MEM_MCORE_BASE_ADDR + 0x4000)


/*Android boot.img 起始及参数地址配置*/
#define LINUX_ADDR_TAGS                        (GLOBAL_MEM_ACORE_BASE_ADDR + 0x100)
#define LINUX_PHYS_OFFSET                      (GLOBAL_MEM_ACORE_BASE_ADDR)


/* 单板AXI内存 */
#define GLOBAL_AXI_MEM_BASE_ADDR_PHY           (0x30000000)
#define GLOBAL_AXI_MEM_SIZE                    (0x00020000)

#define GLOBAL_AXI_MEM_BASE_ADDR_VIRT          (IO_ADDRESS(GLOBAL_AXI_MEM_BASE_ADDR_PHY))


#ifdef BSP_CORE_MODEM
#define GLOBAL_AXI_MEM_BASE_ADDR               (GLOBAL_AXI_MEM_BASE_ADDR_PHY)
#else
#ifdef __FASTBOOT__
#define GLOBAL_AXI_MEM_BASE_ADDR               (GLOBAL_AXI_MEM_BASE_ADDR_PHY)
#else
#define GLOBAL_AXI_MEM_BASE_ADDR               (GLOBAL_AXI_MEM_BASE_ADDR_VIRT)
#endif

#define AXI_MEM_BASE_ADDR                      (GLOBAL_AXI_MEM_BASE_ADDR_PHY)
#define AXI_MEM_ADDR                           (GLOBAL_AXI_MEM_BASE_ADDR)
#define AXI_MEM_SIZE                           (GLOBAL_AXI_MEM_SIZE)
#endif

/*                      AXI Memory 分配图

               +---------------------+---------+ --> 0x2FFE0000
               | A核低功耗           | 16KB    |
               +---------------------+---------+ --> 0x2FFE4000
               | FLASH资源锁         | 32B     |
               +---------------------+---------+ --> 0x2FFE4020
               | IFC标识             | 32B     |
               +---------------------+---------+ --> 0x2FFE4040
	           | ICC标识             | 1K      |
	           +---------------------+---------+ --> 0x2FFE4440
	           | 内存管理            | 1K      |
               +---------------------+---------+ --> 0x2FFE4840
               | 动态内存区          |73K-256B|
               +---------------------+---------+ --> 0x2FFF6B40
               | IPF数据区           | 30K     |
               +---------------------+---------+ --> 0x2FFFE340
               | 温保区              | 128B    |
               +---------------------+---------+ --> 0x2FFFE3C0
               | 开关机              | 32B     |
               +---------------------+---------+ --> 0x2FFFE3E0
               | DICC标识            | 32B     |
               +---------------------+---------+ --> 0x2FFFE400
               | HIFI数据区          | 6K      |
               +---------------------+---------+ --> 0x2FFFFC00
               | 保留区              | 1K-256B |
               +---------------------+---------+ --> 0x2FFFFF00
               | 升级标识            | 256B    |
               +---------------------+---------+ --> 0x30000000
*/
/*FastBoot*/
#define MEMORY_AXI_FASTBOOT_START_ADDR        (GLOBAL_AXI_MEM_BASE_ADDR)
#define MEMORY_AXI_FASTBOOT_START_SIZE        (0x08)

/* 开关机 */
#define MEMORY_AXI_ONOFF_ADDR               (MEMORY_AXI_FASTBOOT_START_ADDR + MEMORY_AXI_FASTBOOT_START_SIZE)
#define MEMORY_AXI_ONOFF_SIZE               (32)

/* DICC标识 */
#define MEMORY_AXI_DICC_ADDR                (MEMORY_AXI_ONOFF_ADDR + MEMORY_AXI_ONOFF_SIZE)
#define MEMORY_AXI_DICC_SIZE                (32)

/* 温保区 */
#define GLOBAL_AXI_TEMP_PROTECT_ADDR        (MEMORY_AXI_DICC_ADDR + MEMORY_AXI_DICC_SIZE)
#define GLOBAL_AXI_TEMP_PROTECT_SIZE        (128)

/* USB拔插 */
#define MEMORY_AXI_USB_INOUT_ADDR           (GLOBAL_AXI_TEMP_PROTECT_ADDR + GLOBAL_AXI_TEMP_PROTECT_SIZE)
#define MEMORY_AXI_USB_INOUT_SIZE           (4)

/*CSHELL*/
#define MEMORY_AXI_USB_CSHELL_ADDR         (MEMORY_AXI_USB_INOUT_ADDR + MEMORY_AXI_USB_INOUT_SIZE)
#define MEMORY_AXI_USB_CSHELL_SIZE         (4)

/* 物理串口与A/C shell口切换 */
#define MEMORY_AXI_UART_INOUT_ADDR          (MEMORY_AXI_USB_CSHELL_ADDR + MEMORY_AXI_USB_CSHELL_SIZE)
#define MEMORY_AXI_UART_INOUT_SIZE          (4)

/* 软标志区，大小减去了8，因为最后的地方放置了标记 */
#define MEMORY_AXI_SOFT_FLAG_ADDR           (MEMORY_AXI_UART_INOUT_ADDR + MEMORY_AXI_UART_INOUT_SIZE)
#define MEMORY_AXI_SOFT_FLAG_SIZE           (1024 - (MEMORY_AXI_SOFT_FLAG_ADDR - GLOBAL_AXI_MEM_BASE_ADDR) - 8)

/* A核低功耗 */
#define MEMORY_AXI_ACPU_DEEPSLEEP_ADDR      (GLOBAL_AXI_MEM_BASE_ADDR + 1024)
#define MEMORY_AXI_ACPU_DEEPSLEEP_SIZE      (0x3000)

/* ICC标识 */
#define MEMORY_AXI_ICC_ADDR                 (MEMORY_AXI_ACPU_DEEPSLEEP_ADDR + MEMORY_AXI_ACPU_DEEPSLEEP_SIZE)
#define MEMORY_AXI_ICC_SIZE                 (1024)

/* 内存管理 */
#define MEMORY_AXI_MEMMGR_FLAG_ADDR         (MEMORY_AXI_ICC_ADDR + MEMORY_AXI_ICC_SIZE)
#define MEMORY_AXI_MEMMGR_FLAG_SIZE         (1024)

/* 动态内存区 */
#define MEMORY_AXI_DYNAMIC_SEC_ADDR         (MEMORY_AXI_MEMMGR_FLAG_ADDR + MEMORY_AXI_MEMMGR_FLAG_SIZE)
#define MEMORY_AXI_DYNAMIC_SEC_SIZE         (48*1024 - (MEMORY_AXI_DYNAMIC_SEC_ADDR - GLOBAL_AXI_MEM_BASE_ADDR))

/* FLASH资源锁 */
#define MEMORY_AXI_FLASH_SEM_ADDR           (MEMORY_AXI_DYNAMIC_SEC_ADDR + MEMORY_AXI_DYNAMIC_SEC_SIZE)
#define MEMORY_AXI_FLASH_SEM_SIZE           (4)

/* IFC标识 */
#define MEMORY_AXI_IFC_ADDR                 (MEMORY_AXI_FLASH_SEM_ADDR + MEMORY_AXI_FLASH_SEM_SIZE)
#define MEMORY_AXI_IFC_SIZE                 (32)

/* HIFI数据区 */
#define MEMORY_AXI_HIFI_ADDR                (MEMORY_AXI_IFC_ADDR + MEMORY_AXI_IFC_SIZE)
#define MEMORY_AXI_HIFI_SIZE                (6*1024)

/* 保留 */
#define MEMORY_AXI_RESERVE_ADDR             (MEMORY_AXI_HIFI_ADDR + MEMORY_AXI_HIFI_SIZE)
#define MEMORY_AXI_RESERVE_SIZE             (GLOBAL_AXI_MEM_SIZE - (MEMORY_AXI_RESERVE_ADDR - GLOBAL_AXI_MEM_BASE_ADDR) - \
                                            MEMORY_AXI_PTABLE_SIZE - MEMORY_AXI_FLAG_BAK_SIZE - \
                                            MEMORY_AXI_DLOAD_SIZE - MEMORY_AXI_DLOAD_AUTOINSTALL_SIZE)/*monan for v9r1bbit
 */

/* 复位标记保存区 */
#define MEMORY_AXI_FLAG_BAK_ADDR             (MEMORY_AXI_RESERVE_ADDR + MEMORY_AXI_RESERVE_SIZE)
#define MEMORY_AXI_FLAG_BAK_SIZE             (1024)

/* 升级标识 *//*monan for v9r1bbit 因为p500 A核启动代码跑在sram，不打开sram保护区拷贝功能， 移动到sram后部分*/
#define MEMORY_AXI_DLOAD_ADDR               (MEMORY_AXI_FLAG_BAK_ADDR + MEMORY_AXI_FLAG_BAK_SIZE)
#define MEMORY_AXI_DLOAD_SIZE               (256-48)

#define MEMORY_AXI_DLOAD_AUTOINSTALL_ADDR   (MEMORY_AXI_DLOAD_ADDR + MEMORY_AXI_DLOAD_SIZE)
#define MEMORY_AXI_DLOAD_AUTOINSTALL_SIZE   (48)

/* Flash分区表 */
#define MEMORY_AXI_PTABLE_ADDR              (MEMORY_AXI_DLOAD_AUTOINSTALL_ADDR + MEMORY_AXI_DLOAD_AUTOINSTALL_SIZE)
#define MEMORY_AXI_PTABLE_SIZE              (2*1024)

#define MEMORY_AXI_END_ADDR               (MEMORY_AXI_PTABLE_ADDR + MEMORY_AXI_PTABLE_SIZE)


#define MEMORY_AXI_NEED_TO_SAVE_BEFORE_RESET   4
#define MEMORY_AXI_VX_BACK_UP_FLAG1 0x12121212
#define MEMORY_AXI_VX_BACK_UP_FLAG2 0x21212121

#define MEMORY_AXI_BOOTROM_BACK_UP_FLAG1 0x34343434
#define MEMORY_AXI_BOOTROM_BACK_UP_FLAG2 0x43434343


/*Memory size check*/
#if (MEMORY_AXI_END_ADDR > (GLOBAL_AXI_MEM_BASE_ADDR + GLOBAL_AXI_MEM_SIZE))
#error AXI(MEMORY_AXI_END_ADDR) USED beyond the mark (GLOBAL_AXI_MEM_BASE_ADDR + GLOBAL_AXI_MEM_SIZE)
#endif


#endif
/*Memory size check*/
#if (MEMORY_AXI_END_ADDR > (GLOBAL_AXI_MEM_BASE_ADDR + GLOBAL_AXI_MEM_SIZE))
#error AXI(MEMORY_AXI_END_ADDR) USED beyond the mark (GLOBAL_AXI_MEM_BASE_ADDR + GLOBAL_AXI_MEM_SIZE)
#endif

/*-------------------------------------------------------------------------------
                            双核共享内存
  -------------------------------------------------------------------------------
                         -----------------------
                         |  SYNC(0x60)                  |
                         -----------------------
                         |  MEM spinlock(0x20)       |
                         -----------------------
                         |  ICC(0x80)                    |
                         -----------------------
                         | TENCILICA_TEXT(0)       |
                         -----------------------
                         |  WAN0x8000)                 |
                         -----------------------
                         |  MEM MGR M                  |
                         -----------------------
-------------------------------------------------------------------------------*/
/* 从顶往下分配，以下地址和大小不可改变 */
#define MEMORY_RAM_CORESHARE_SIZE                   (GLOBAL_MEM_CORE_SHARE_SIZE)

#define MEMORY_RAM_CORESHARE_SYNC_RESV              (96)
#define MEMORY_RAM_CORESHARE_MEM_RESV               (32)
#define MEMORY_RAM_CORESHARE_ICC_RESV               (128)
/* 多band预留内存,装备CT BT使用*/
#define CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE  (0x8000)

#define MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV    (0)
#define MEMORY_RAM_CORESHARE_MEM_WAN_SIZE           (0x8000)
#if (defined(BOARD_ASIC) && defined(VERSION_V3R2) && (defined(CHIP_BB_6756CS)))||(defined(BOARD_FPGA) && defined(VERSION_V3R2)) /*monan for v9r1bbit
 */
#define MEMORY_RAM_CORESHARE_MEM_IPF_SIZE            (30*1024)
#define MEMORY_RAM_CORESHARE_MEMMGR_SIZE            (MEMORY_RAM_CORESHARE_SIZE \
                                                    - MEMORY_RAM_CORESHARE_ICC_RESV \
                                                    - CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE\
                                                    - MEMORY_RAM_CORESHARE_MEM_RESV \
                                                    - MEMORY_RAM_CORESHARE_SYNC_RESV \
                                                    - MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV\
                                                    - MEMORY_RAM_CORESHARE_MEM_WAN_SIZE\
                                                    - MEMORY_RAM_CORESHARE_MEM_IPF_SIZE)
#else
#define MEMORY_RAM_CORESHARE_MEMMGR_SIZE            (MEMORY_RAM_CORESHARE_SIZE \
                                                    - MEMORY_RAM_CORESHARE_ICC_RESV \
                                                    - CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE\
                                                    - MEMORY_RAM_CORESHARE_MEM_RESV \
                                                    - MEMORY_RAM_CORESHARE_SYNC_RESV \
                                                    - MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV\
                                                    - MEMORY_RAM_CORESHARE_MEM_WAN_SIZE)
#endif

#ifdef BSP_CORE_MODEM
#define MEMORY_RAM_CORESHARE_ADDR                   (GLOBAL_MEM_CORE_SHARE_ADDR)
#else
#define MEMORY_RAM_CORESHARE_ADDR                   (GLOBAL_MEM_CORE_SHARE_ADDR_VIRT)
#endif
#define MEMORY_RAM_CORESHARE_MEMMGR_ADDR            (MEMORY_RAM_CORESHARE_ADDR)
#if (defined(BOARD_ASIC) && defined(VERSION_V3R2) && (defined(CHIP_BB_6756CS)))||(defined(BOARD_FPGA) && defined(VERSION_V3R2)) /*monan for v9r1bbit
 */


#define MEMORY_RAM_CORESHARE_IPF_ADDR               (MEMORY_RAM_CORESHARE_MEMMGR_ADDR + MEMORY_RAM_CORESHARE_MEMMGR_SIZE)
#define MEMORY_RAM_CORESHARE_MEM_WAN_ADDR           (MEMORY_RAM_CORESHARE_IPF_ADDR + MEMORY_RAM_CORESHARE_MEM_IPF_SIZE)
#else
#define MEMORY_RAM_CORESHARE_MEM_WAN_ADDR           (MEMORY_RAM_CORESHARE_MEMMGR_ADDR+MEMORY_RAM_CORESHARE_MEMMGR_SIZE)
#endif
#define MEMORY_RAM_CORESHARE_TENCILICA_TEXT_ADDR    (MEMORY_RAM_CORESHARE_MEM_WAN_ADDR+MEMORY_RAM_CORESHARE_MEM_WAN_SIZE)
#define MEMORY_RAM_CORESHARE_ICC_ADDR               (MEMORY_RAM_CORESHARE_TENCILICA_TEXT_ADDR+MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV)
#define CORESHARE_MEM_TENCILICA_MULT_BAND_ADDR ((MEMORY_RAM_CORESHARE_ICC_ADDR) + (MEMORY_RAM_CORESHARE_ICC_RESV))
#define MEMORY_RAM_CORESHARE_MEM_ADDR               (CORESHARE_MEM_TENCILICA_MULT_BAND_ADDR + CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE)
#define MEMORY_RAM_CORESHARE_SYNC_ADDR              (MEMORY_RAM_CORESHARE_MEM_ADDR + MEMORY_RAM_CORESHARE_MEM_RESV)

#if (defined(BOARD_ASIC) && defined(VERSION_V3R2) && (defined(CHIP_BB_6756CS)))\
    ||(defined(BOARD_FPGA) && defined(VERSION_V3R2)) /*monan for v9r1bbit
 */
#define MEMORY_AXI_IPF_ADDR MEMORY_RAM_CORESHARE_IPF_ADDR
#define MEMORY_AXI_IPF_SIZE MEMORY_RAM_CORESHARE_MEM_IPF_SIZE
#endif

/* 使用物理地址 */
#define CORESHARE_MEM_WAN_ADDR                      (MEMORY_RAM_CORESHARE_MEM_WAN_ADDR - MEMORY_RAM_CORESHARE_ADDR + GLOBAL_MEM_CORE_SHARE_ADDR)
#define CORESHARE_MEM_WAN_SIZE                      (MEMORY_RAM_CORESHARE_MEM_WAN_SIZE)

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __MEMMORY_LAYOUT_H__ */

