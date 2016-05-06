/******************************************************************************
修改以下文件需要保证下面文件的一致性：
hardware\libhardware\include\hardware\hisi\pwrctrl_multi_memcfg.h       ->vendor\hisi\modem\drv\hi6210\src\comm\inc\pwrctrl_multi_memcfg.h
hardware\libhardware\include\hardware\hisi\pwrctrl_multi_dfs_asm.h      ->vendor\hisi\modem\drv\hi6210\src\comm\inc\pwrctrl_multi_dfs_asm.h
hardware\libhardware\include\hardware\hisi\soc_baseaddr_interface.h     ->vendor\hisi\platform\hi6210sft\soc_baseaddr_interface.h
hardware\libhardware\include\hardware\hisi\global_ddr_map.h             ->vendor\hisi\config\product\include\hi6210sft\global_ddr_map.h
******************************************************************************/
#ifndef _HI_GLOBAL_MEM_MAP_INCLUDE_H_
#define _HI_GLOBAL_MEM_MAP_INCLUDE_H_


#include "soc_baseaddr_interface.h"

/*******************************************
多核共享头文件
不允许包含操作系统相关头文件
*******************************************/

/******************************************
V900R001 Dual-Channel DDR Details:
*******************************************/

#define DDR_BASE_ADDR					(SOC_DRAM_BASE_ADDR)
#define DDR_LAST_ADDR					(0x3FFFFFFF)

/******************************************************
         以下内存在DDR非交织区
********************************************************/
/******************************************************
         DDR非交织区 上半区 103M
********************************************************/
/*在这里添加新的内存区域后，需要在 ..\kernel\arch\arm\mach-hi6620\init_param.c
文件里面添加对应的检测项目-start*/
/*Modem系统内存 90M*/
#define MODEM_SYS_MEM_ADDR				(DDR_BASE_ADDR)                                 /*0x00000000*/
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
#define MODEM_SYS_MEM_SIZE				(0x05900000)
#else
#define MODEM_SYS_MEM_SIZE				(0x05A00000)
#endif

/* when ADDR changed,please check the vendor\hisi\build\scripts\gen_img_vrl_tbl.py */

/*HIFI系统内存 4M*/
#define HIFI_SYS_MEM_ADDR				(MODEM_SYS_MEM_ADDR + MODEM_SYS_MEM_SIZE)       /*0x05A00000*/
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
#define HIFI_SYS_MEM_SIZE				(0x00500000)
#else
#define HIFI_SYS_MEM_SIZE				(0x00400000)
#endif

/*MCU系统内存 1M*/
#define MCU_SYS_MEM_ADDR				(HIFI_SYS_MEM_ADDR + HIFI_SYS_MEM_SIZE)         /*0x05E00000*/
#define MCU_SYS_MEM_SIZE				(0x00100000)

#define TELE_MNTN_AREA_ADDR				(MCU_SYS_MEM_ADDR + MCU_SYS_MEM_SIZE)           /*0x05F00000*/
#define TELE_MNTN_AREA_SIZE				(0x00100000)

/*C核给GUPS预留的内存 19M*/
#define GU_RESERVED_MEM_ADDR		    (TELE_MNTN_AREA_ADDR + TELE_MNTN_AREA_SIZE)           /*0x06000000*/
#define GU_RESERVED_MEM_SIZE		    (0x00300000)        /* 以前为17M 后来TTF由静态内存改为动态申请空出10+3M 再加上HUTAF空出的2M 故裁剪后大小为2M */

/*C核给LPS预留的内存7M,若地址发生改变偏移，需要同步修改BBE16代码*/
#define LPS_RESERVED_MEM_ADDR		    (GU_RESERVED_MEM_ADDR + GU_RESERVED_MEM_SIZE)   /*0x06300000*/
#define LPS_RESERVED_MEM_SIZE		    (0x00700000)

/*核间共享内存4M*/
#define IPC_SHARE_MEM_ADDR				(LPS_RESERVED_MEM_ADDR + LPS_RESERVED_MEM_SIZE) /*0x06A00000*/
#define IPC_SHARE_MEM_SIZE				(0x00400000)

/*Modem异常信息记录1M */
#define MODEM_DUMP_LOG_ADDR				(IPC_SHARE_MEM_ADDR + IPC_SHARE_MEM_SIZE)       /*0x06E00000*/
#define MODEM_DUMP_LOG_SIZE				(0x00100000)

/******************************************************
         DDR非交织区 下半区111M
********************************************************/

/*AP异常信息记录1M */
#define ANDROID_DUMP_LOG_ADDR			(MODEM_DUMP_LOG_ADDR + MODEM_DUMP_LOG_SIZE)       /*0x06F00000*/
#define ANDROID_DUMP_LOG_SIZE			(0x00100000)

/*FASTBOOT 系统内存3.5M*/
#define FASTBOOT_SYS_MEM_ADDR			(ANDROID_DUMP_LOG_ADDR + ANDROID_DUMP_LOG_SIZE) /*0x07000000*/
#define FASTBOOT_SYS_MEM_SIZE			(0x00300000)

/*FASTBOOT log内存256K*/
#define FASTBOOT_DUMP_LOG_ADDR			(FASTBOOT_SYS_MEM_ADDR + FASTBOOT_SYS_MEM_SIZE) /*0x07300000*/
#define FASTBOOT_DUMP_LOG_SIZE			(0x00040000)

/*arm-trusted-firmware bl31系统内存768K*/
#define ATF_BL31_SYS_MEM_ADDR           (FASTBOOT_DUMP_LOG_ADDR + FASTBOOT_DUMP_LOG_SIZE) /*0x07340000*/
#define ATF_BL31_SYS_MEM_SIZE           (0x000C0000)
/*Android 系统内存两部分共886M 为了A核Kernel使用方便 */
#define ANDROID_SYS_MEM_ADDR			(ATF_BL31_SYS_MEM_ADDR + ATF_BL31_SYS_MEM_SIZE) /*0x07400000*/
#define ANDROID_SYS_MEM_SIZE			(DDR_LAST_ADDR - ANDROID_SYS_MEM_ADDR + 1)

#if 0
/*FASTBOOT 系统内存32M 使用1G/2G最后32M空间 */
#define FASTBOOT_SYS_MEM_ADDR			(ANDROID_SYS_MEM_ADDR + ANDROID_SYS_MEM_SIZE - 0x02000000)
#define FASTBOOT_SYS_MEM_SIZE			(0x02000000)
#endif

#define SYS_DUMP_MEM_ADDR                (0x40000000)
#define SYS_DUMP_MEM_SIZE                (0x20000000)

/*在这里添加新的内存区域后，需要在 ..\kernel\arch\arm\mach-hi6620\init_param.c
文件里面添加对应的检测项目 end*/

/******************************************************
  以下是需要预留的虚地址区64MB(0xFBA00000~0xFFA00000)
  起始地址必须2MB对齐!!!
********************************************************/
#define GLOBAL_VIRT_ADDR                (0xFB200000)
#define GLOBAL_VIRT_SIZE                (0x04000000)

/*C核给GUPS预留的内存虚地址*/
#define GU_RESERVED_MEM_VIRT_ADDR       (GLOBAL_VIRT_ADDR)                                  /*0xF0000000*/

/*C核给LPS预留的内存虚地址*/
#define LPS_RESERVED_MEM_VIRT_ADDR      (GU_RESERVED_MEM_VIRT_ADDR + GU_RESERVED_MEM_SIZE)  /*0xF1100000*/

/*核间共享内存虚地址*/
#define IPC_SHARE_MEM_VIRT_ADDR         (LPS_RESERVED_MEM_VIRT_ADDR + LPS_RESERVED_MEM_SIZE)/*0xF1700000*/

/*Modem异常信息记录虚地址 */
#define MODEM_DUMP_LOG_VIRT_ADDR        (IPC_SHARE_MEM_VIRT_ADDR + IPC_SHARE_MEM_SIZE)      /*0xF1B00000*/

/*温保核间共享内存虚地址*/
#define MCU_SHARE_MEM_VIRT_ADDR         (MODEM_DUMP_LOG_VIRT_ADDR + MODEM_DUMP_LOG_SIZE)    /*0xF1D00000*/



/*                       MCU使用内存

+---------------------+--------------------------------+ --> 0x05700000
MCU_SYS_MEM_ADDR  --|--    MCU_LP_SYS_MEM_ADDR   --|--   SYSTEM(0x80000)
(0x100000)          |      (0x80000)               |--   reserved(0x0)
                    |
                    |--    MCU_STORAGE_MEM_ADDR  --|--   MCU_LP_MCU_BK_ADDR(0x00025000)
                    |      (0x40000)               |--   MCU_LP_PARAM_ADDR(0x8000)
                    |                              |--   reserved(0x13000)
                    |
                    |
                    |--    MCU_SHARE_MEM_ADDR    --|--   MCU_DUMP_LOG_ADDR(0x30000)
                    |      (0x40000)               |--   MCU_HKADC_DDR_ADDR(0x4000)
                    |                              |--   ACPU_POLICY_IN_DDR_STROE_AREA(0xC00)
                    |                              |--   DDR_POLICY_IN_DDR_STROE_AREA(0xC00)
                    |                              |--   DDR_MCUSHELL_ADDR(0xC00)                   
                    |                              |--   reserved(0x9C00)
                    |
                    |--    reserved
                    |      (0x0)
*/

/*----MCU系统内存区域----*/
#define MCU_LP_SYS_MEM_ADDR                 (MCU_SYS_MEM_ADDR)
#define MCU_LP_SYS_MEM_SIZE			    	(0x00080000)  /*mcu前512K DDR空间为可cache存储区域，为mcu系统使用*/

/*----MCU存储内存区域----*/
#define MCU_STORAGE_MEM_ADDR                (MCU_LP_SYS_MEM_ADDR + MCU_LP_SYS_MEM_SIZE)
#define MCU_STORAGE_MEM_SIZE                (0x00040000)

#define MCU_LP_MCU_BK_ADDR                  (MCU_STORAGE_MEM_ADDR)
#define MCU_LP_MCU_BK_SIZE                  (0x00025000)


#define MCU_LP_PARAM_ADDR                   (MCU_LP_MCU_BK_ADDR + MCU_LP_MCU_BK_SIZE)
#define MCU_LP_PARAM_ADDR_SIZE              (0x00008000)

#define MCU_STORAGE_MEM_USED_SIZE           (MCU_LP_MCU_BK_SIZE + MCU_LP_PARAM_ADDR_SIZE)

#if (MCU_STORAGE_MEM_USED_SIZE > MCU_STORAGE_MEM_SIZE)
#error mcu_storage_memory(MCU_STORAGE_MEM_USED_SIZE) used beyond (MCU_STORAGE_MEM_SIZE)
#endif

/*----MCU共享内存区域----*/
#define MCU_SHARE_MEM_ADDR                  (MCU_STORAGE_MEM_ADDR + MCU_STORAGE_MEM_SIZE)
#define MCU_SHARE_MEM_SIZE                  (0x00040000)

/*MCU 异常处理dump区*/
#define MCU_DUMP_LOG_ADDR			    	(MCU_SHARE_MEM_ADDR)
#define MCU_DUMP_LOG_SIZE                   (0x00030000)

/*MCU 系统温保共享内存区 MCU_HKADC_DDR_ADDR*/
#define MCU_HKADC_DDR_ADDR                  (MCU_DUMP_LOG_ADDR + MCU_DUMP_LOG_SIZE)
#define MCU_HKADC_DDR_SIZE                  (0x0004000)

#define SHM_MEM_TEMPERATURE_ADDR            (MCU_HKADC_DDR_ADDR)
#define SHM_MEM_TEMPERATURE_SIZE            (MCU_HKADC_DDR_SIZE)

/*acpu policy param addr*/
#define ACPU_POLICY_IN_DDR_STROE_AREA       (MCU_HKADC_DDR_ADDR + MCU_HKADC_DDR_SIZE)
#define ACPU_POLICY_IN_DDR_STROE_SIZE       (0xC00)/*(24 * 8 * 15)*/

/*ddr policy param addr*/
#define DDR_POLICY_IN_DDR_STROE_AREA        (ACPU_POLICY_IN_DDR_STROE_AREA + ACPU_POLICY_IN_DDR_STROE_SIZE)
#define DDR_POLICY_IN_DDR_STROE_SIZE        (0xC00)/*(24 * 8 * 15)*/

#define DDR_MCUSHELL_ADDR                   (DDR_POLICY_IN_DDR_STROE_AREA + DDR_POLICY_IN_DDR_STROE_SIZE)
#define DDR_MCUSHELL_SIZE                   (0xC00)

#define MCU_SHARE_MEM_USED_SIZE             (MCU_DUMP_LOG_SIZE+MCU_HKADC_DDR_SIZE + ACPU_POLICY_IN_DDR_STROE_SIZE + DDR_POLICY_IN_DDR_STROE_SIZE + DDR_MCUSHELL_SIZE)

#if (MCU_SHARE_MEM_USED_SIZE > MCU_SHARE_MEM_SIZE)
#error mcu_share_memory(MCU_SHARE_MEM_USED_SIZE) used beyond (MCU_SHARE_MEM_SIZE)
#endif
#endif /*_HI_GLOBAL_MEM_MAP_INCLUDE_H_*/
