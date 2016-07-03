/* config.h - ARM RealView PBX-A9 board configuration header */

/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,20oct09,z_l  created
*/

/*
DESCRIPTION
This file contains the configuration parameters for the 
ARM RealView PBX-A9 board.
*/

#ifndef __INCconfigh
#define __INCconfigh

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * BSP version/revision identification, should be placed
 * before #include "configAll.h"
 */

#define BSP_VERSION     "2.0"
#define BSP_REV         "/0" /* 0 for first revision */

#include <configAll.h>

#include "product_config.h"
#include "arm_pbxa9.h"

#undef  CONSOLE_BAUD_RATE
#define CONSOLE_BAUD_RATE 38400

#define BOOT_FROM_UBOOT

#ifdef _WRS_CONFIG_SMP
#   define SYS_MODEL "ARM RealView PBX-A9 MPCore"
#else
#   define SYS_MODEL "ARM RealView PBX-A9"
#endif /* _WRS_CONFIG_SMP */

#define INCLUDE_VXBUS
#define INCLUDE_HWMEM_ALLOC
#define INCLUDE_PLB_BUS
#define INCLUDE_PARAM_SYS
#define INCLUDE_MII_BUS
#define INCLUDE_SMSCLAN9118_VXB_END
#define INCLUDE_GENERICPHY
#define INCLUDE_SIO_UTILS
#define DRV_SIO_PRIMECELL
#define INCLUDE_INTCTLR_LIB 
#define DRV_ARM_GIC
#define INCLUDE_TIMER_SYS
#define DRV_TIMER_AMBA

#undef INCLUDE_PCI

#ifdef INCLUDE_PCI
#   define INCLUDE_PCI_BUS
#   define INCLUDE_PCI_BUS_AUTOCONF
#   define DRV_PCIBUS_ARMAXI
#   define INCLUDE_GEI825XX_VXB_END
#endif /* INCLUDE_PCI */

#ifdef _WRS_CONFIG_SMP
#   define INCLUDE_VXIPI
#endif

#define HWMEM_POOL_SIZE 50000
#define INCLUDE_VXB_CMDLINE

/* Support network devices */

#ifdef INCLUDE_SMSCLAN9118_VXB_END
#   ifndef INCLUDE_NETWORK
#       define INCLUDE_NETWORK
#   endif /* INCLUDE_NETWORK */
#   ifndef INCLUDE_END
#       define INCLUDE_END
#   endif /* INCLUDE_END */
#endif /* INCLUDE_SMSCLAN9118_VXB_END */

#define DEFAULT_BOOT_LINE \
    "sme(0,0) host:vxWorks h=192.168.255.2 e=192.168.255.1 u=target pw=vxTarget"

#define FORCE_DEFAULT_BOOT_LINE

/* the new bspfilllong routine will reduce 2-3 seconds of system boot time */

#define BSP_FILL_LONGS bspfilllong

/* Memory configuration */

#define USER_RESERVED_MEM    0

#define LOCAL_MEM_LOCAL_ADRS  0x00000000

/*
 * In this BSP, LOCAL_MEM_SIZE does not effect the whole system memory size
 * managed by VxWorks, as we use PBXA9_DRAM_SIZE to define the memory size for 
 * MMU and kernel module. However, bootrom uses this definition to clear memory 
 * to zero and this will take a long time(more than 30s). It turns out that 
 * after U-Boot boot up, all memory, except a small segment start from 
 * 0x1000000, will be 0, or other invalid data, such 0xff. Therefore, here we 
 * define LOCAL_MEM_SIZE with a small value to reduce the bootrom boot time. 
 * For address 0x1000000, we use it to define RAM_HIGH_ADRS, so it will be 
 * overwritten by bootrom image.
 */

//#define LOCAL_MEM_SIZE        0x2000000

/*
 * The constants ROM_TEXT_ADRS and ROM_SIZE are defined
 * in config.h, MakeSkel, Makefile and Makefile.*
 * All definitions for these constants must be identical.
 */

#define ROM_BASE_ADRS       0x40000000     /* base of NOR Flash/EPROM */
#ifdef BOOT_FROM_UBOOT
#   define ROM_TEXT_ADRS    0x41000000     /* code start addr in ROM */
#else
#   define ROM_TEXT_ADRS    0x40000000     /* code start addr in ROM */
#endif /* BOOT_FROM_UBOOT */

#define ROM_SIZE            0x00100000     /* size of ROM holding VxWorks*/

#define ROM_SIZE_TOTAL      0x04000000     /* total size of ROM */

/*
 * Flash/NVRAM memory configuration
 *
 * A block of the flash memory (FLASH_MEM_SIZE bytes at ALT_FLASH_ADRS) is
 * reserved for non-volatile storage of data.
 *
 */

#undef INCLUDE_FLASH

#ifdef INCLUDE_FLASH
#   define FLASH_28F256L30B      0x89
#   define SYS_FLASH_TYPE        FLASH_28F256L30B
#   define FLASH_CHIP_WIDTH      2
#   define ALT_FLASH_ADRS        0x44000000
#   define FLASH_MEM_SIZE        0x200000
#   define FLASH_SECTOR_SIZE     0x20000     /* sector size of 28F256L30B */
#   define FLASH_WIDTH           2
#   define FLASH_SEGMENT_SIZE    0x40000
#   define FLASH_WIDTH_SPECIAL_2

/*
 * FLASH_OVERLAY means saving the sector firstly and then write the 
 * speficied offset.
 */

#   define FLASH_OVERLAY
#   undef  NV_BOOT_OFFSET
#   define NV_BOOT_LINE_SIZE     0x200
#   define NV_BOOT_OFFSET        0
#   define NV_RAM_SIZE           FLASH_SEGMENT_SIZE
#   define NV_RAM_ADRS           ALT_FLASH_ADRS
#endif /* INCLUDE_FLASH */

/* Serial port configuration */

#undef  NUM_TTY
#define NUM_TTY           N_SIO_CHANNELS

/*
 * Cache/MMU configuration
 *
 * Note that when MMU is enabled, cache modes are controlled by
 * the MMU table entries in sysPhysMemDesc[], not the cache mode
 * macros defined here.
 */

/*
 * We use the generic architecture libraries, with caches/MMUs present. A
 * call to sysHwInit0() is needed from within usrInit before
 * cacheLibInit() is called.
 */

#ifndef _ASMLANGUAGE
IMPORT void sysHwInit0 (void);
#endif

#define INCLUDE_SYS_HW_INIT_0
#define SYS_HW_INIT_0()         sysHwInit0 ()

#ifdef _WRS_CONFIG_SMP
#   define VX_SMP_NUM_CPUS 2
#endif

/*
 * These processors can be either write-through or copyback (defines 
 * whether write-buffer is enabled); cache itself is write-through.
 *
 * Specifying CACHE_SNOOP_ENABLE initialized the processor for 
 * cache coherency, i.e, enables SMP mode(AMP is not supported).
 * CACHE_SNOOP_ENABLE must be defined if the system is running 
 * with SMP mode.
 */
 

#undef  USER_I_CACHE_MODE
#define USER_I_CACHE_MODE    (CACHE_COPYBACK)

#undef  USER_D_CACHE_MODE
#ifdef _WRS_CONFIG_SMP
#   define USER_D_CACHE_MODE    (CACHE_COPYBACK | CACHE_SNOOP_ENABLE)
#else
#   define USER_D_CACHE_MODE    (CACHE_COPYBACK)
#endif /* _WRS_CONFIG_SMP */

#define INCLUDE_MMU_BASIC
#define INCLUDE_MMU
#define INCLUDE_CACHE_SUPPORT

#define INCLUDE_VFP /* vector floating point support */

/*
 * interrupt mode - interrupts can be in either preemptive or non-preemptive
 * mode. For preemptive mode, change INT_MODE to INT_PREEMPT_MODEL
 */

//#define INT_MODE    INT_NON_PREEMPT_MODEL
#define INT_MODE      INT_PREEMPT_MODEL


#define ISR_STACK_SIZE    0x2000    /* size of ISR stack, in bytes */

#undef INCLUDE_TFFS    /* TrueFFS is supported but undefined by default */

#ifdef INCLUDE_TFFS

/* FLASH_BASE_ADRS is the base address used by TFFS */

#   define FLASH_BASE_ADRS       (ALT_FLASH_ADRS + FLASH_SEGMENT_SIZE)

/* FLASH_SIZE is the flash size used by TFFS. This definition can be modified */

#   define FLASH_SIZE            (0x800000)

#   define INCLUDE_TFFS_MOUNT
#   define INCLUDE_TL_FTL
#   define INCLUDE_DOSFS
#endif /* INCLUDE_TFFS */

#ifdef INCLUDE_DOSFS
#   define INCLUDE_DOSFS_MAIN
#   define INCLUDE_DOSFS_CHKDSK
#   define INCLUDE_DOSFS_FMT
#   define INCLUDE_DOSFS_FAT
#   define INCLUDE_DOSFS_SHOW
#   define INCLUDE_DOSFS_DIR_VFAT
#   define INCLUDE_DOSFS_DIR_FIXED
#   define INCLUDE_HRFS
#   define INCLUDE_FS_MONITOR
#   define INCLUDE_FS_EVENT_UTIL
#   define INCLUDE_ERF
#   define INCLUDE_XBD
#   define INCLUDE_XBD_BLKDEV
#   define INCLUDE_XBD_TRANS
#   define INCLUDE_DEVICE_MANAGER
#   define INCLUDE_XBD_BLK_DEV
#   define INCLUDE_XBD_PART_LIB
#   define INCLUDE_DISK_UTIL
#endif /* INCLUDE_DOSFS */

/* optional timestamp support */

#undef INCLUDE_TIMESTAMP
#define INCLUDE_TIMESTAMP

#undef INCLUDE_AUX_CLK

/* realtime clock support */

#undef INCLUDE_RTC

/* internal SRAM support */

#undef INCLUDE_INTERNAL_SRAM

/* L2 cache support */
#define INCLUDE_L2_CACHE

#if defined(PRJ_BUILD)
#include "prjParams.h"
#endif

#define RAM_LINE_SIZE                    0x10000

#undef  LOCAL_MEM_LOCAL_ADRS
#define LOCAL_MEM_LOCAL_ADRS            DDR_MCORE_ADDR

#undef  LOCAL_MEM_SIZE
#define LOCAL_MEM_SIZE                  DDR_MCORE_SIZE

#undef  RAM_HIGH_ADRS
#define RAM_HIGH_ADRS                   (LOCAL_MEM_LOCAL_ADRS+LOCAL_MEM_SIZE)
#undef  RAM_LOW_ADRS
#define RAM_LOW_ADRS                    (LOCAL_MEM_LOCAL_ADRS+RAM_LINE_SIZE)

#undef  USER_RESERVED_MEM
#define USER_RESERVED_MEM               0x10000



#ifdef __cplusplus
}
#endif
#endif  /* __INCconfigh */


