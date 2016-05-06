

#ifndef __M3BOOT_H__
#define __M3BOOT_H__

#include <product_config.h>
#include <ptable_com.h>
#include <soc_memmap.h>
#include <hi_uart.h>
#include <hi_nandc.h>

/******************** AXI MEM BASE & CPU BOOT ADDR *******************/
#define  RUN_BASE_ADDR_APPA9         FASTBOOT_DDR_ENTRY
#define  APPA9_FASTBOOT_BASE         (HI_NAND_MEM_BUFFER_ADDR+PTABLE_FASTBOOT_START)
#define  FASTBOOT_SIZE_OFFSET        0x24
#define  FASTBOOT_SIZE_IN_NAND       (APPA9_FASTBOOT_BASE + FASTBOOT_SIZE_OFFSET)

/******************************* m3 *********************************/
#define  M3_KERNEL_ENTRY             (HI_M3TCM0_MEM_ADDR + 4)
#define  M3_BOOT_LOOP_NEW_ADDR       (HI_M3TCM0_MEM_ADDR + 78*1024) /* in ARMCMx.ld.s LENGTH = 78k */

#define  ALIGN( __size, __bits )      ( ( ( ( __size - 1 ) >> __bits ) + 1 ) << __bits )

/* Memory mapping of Cortex-M3 Hardware */
#define SCS_BASE            (0xE000E000)                            /*!< System Control Space Base Address  */
#define ITM_BASE            (0xE0000000)                            /*!< ITM Base Address                   */
#define DWT_BASE            (0xE0001000)                            /*!< DWT Base Address                   */
#define TPI_BASE            (0xE0040000)                            /*!< TPI Base Address                   */
#define CoreDebug_BASE      (0xE000EDF0)                            /*!< Core Debug Base Address            */
#define SysTick_BASE        (SCS_BASE +  0x0010)                    /*!< SysTick Base Address               */
#define NVIC_BASE           (SCS_BASE +  0x0100)                    /*!< NVIC Base Address                  */
#define SCB_BASE            (SCS_BASE +  0x0D00)                    /*!< System Control Block Base Address  */
#define MPU_BASE            (SCS_BASE +  0x0D90)                    /*!< Memory Protection Unit             */

/* System Control Block */
#define SCB_VTOR            (SCB_BASE + 0x08)

/* Memory Protection Unit */
#define MPU_TYPE_OFFSET     (0x00)
#define MPU_CTRL_OFFSET     (0x04)
#define MPU_RNR_OFFSET      (0x08)
#define MPU_RBAR_OFFSET     (0x0C)
#define MPU_RASR_OFFSET     (0x10)

#define M3_VTOR_SIZE               (144 * 4)
#define M3_IMAGE_LOAD_MAGIC        (0x87654321)
#define M3_IMAGE_UNLOAD_MAGIC      (0x5A5A1234)
#define M3_IMAGE_RUN_ADDR          (HI_M3TCM0_MEM_ADDR)
#define M3_IMAGE_LEN_ADDR          (M3_IMAGE_RUN_ADDR + M3_VTOR_SIZE)
#define STACK_TOP                  (HI_M3TCM0_MEM_ADDR + 0xD800)     /* 54KB */

#endif /* __M3BOOT_H__ */
