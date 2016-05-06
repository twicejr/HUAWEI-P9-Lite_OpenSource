#ifndef _HI_GLOBAL_SRAM_MAP_INCLUDE_H_
#define _HI_GLOBAL_SRAM_MAP_INCLUDE_H_


#include "soc_baseaddr_interface.h"

/*******************************************
多核共享头文件
不允许包含操作系统相关头文件
*******************************************/

#define SRAM_BASE_ADDR              (SOC_SRAM_OFF_BASE_ADDR)

/*共72KB，分成三部分*/
#define SRAM_SIZE                   (0x12000)

/*第一部分:7KB*/
#define SRAM_SECTION1_SIZE          (0x1C00)

/*第二部分:64KB*/
#define SRAM_SECTION2_SIZE          (0x10000)

/*第三部分:1KB*/
#define SRAM_SECTION3_SIZE          (0x400)

/*-------------------------------------------------------------------------------
                            SRAM划分(分时复用)
  -------------------------------------------------------------------------------
  onchiprom/fastboot启动阶段:
                          -----------------------
                         |  fastboot1的VRL       |->2KB
                          -----------------------
                         |  fastboot1镜像数据    |----
                          -----------------------     |->69KB
                         |  onchiprom的栈        |----
                          -----------------------
                         |  软件标志区           |->1KB
                          -----------------------
  linux/vxworks阶段:
                          -----------------------
                         |  低功耗区域           |->7KB
                          -----------------------
                         |  安全OS               |->64KB
                          -----------------------
                         |  软件标志区           |->1KB
                          -----------------------

-------------------------------------------------------------------------------*/

/*pm use section 7K*/
#define PM_SRAM_ADDR                (SRAM_BASE_ADDR)
#define PM_SRAM_SIZE                (SRAM_SECTION1_SIZE)

/*teeos use section 64K*/
#define TEEOS_SRAM_ADDR             (SRAM_BASE_ADDR + SRAM_SECTION1_SIZE)
#define TEEOS_SRAM_SIZE             (SRAM_SECTION2_SIZE)

/*general use section 1K*/
#define GENERAL_SRAM_ADDR           (SRAM_BASE_ADDR + SRAM_SECTION1_SIZE + SRAM_SECTION2_SIZE)
#define GENERAL_SRAM_SIZE           (SRAM_SECTION3_SIZE)



/*******************************************
MODEM SRAM分配情况
*******************************************/
/*GU DSP LOAD*/
#define MEMORY_AXI_DSP_LOAD_ADDR      (SOC_Modem_SRAM_BASE_ADDR)
#define MEMORY_AXI_DSP_LOAD_SIZE      (896*1024)

/*******************************************
FASTBOOT1 HARQ_RAM 分配
-----------------------
         fastboot1 运行空间           256KB
         fastboot1 log 存储空间       32KB
*******************************************/
/*harqmem基地址*/
#define FASTBOOT_HARQMEM_BASE_ADDR    (SOC_XG2RAM0_HARQ_BASE_ADDR)
/*fastboot 运行使用harqmem大小*/
#define FASTBOOT_RUN_SIZE             (0x40000)  

/*log 存储空间地址*/
#define FASTBOOT_HARQMEM_LOG_ADDR     (SOC_XG2RAM0_HARQ_BASE_ADDR + FASTBOOT_RUN_SIZE) 
/*log 存储空间大小*/
#define FASTBOOT_HARQMEM_LOG_SIZE      (0x8000)

#endif /*_HI_GLOBAL_MEM_MAP_INCLUDE_H_*/

