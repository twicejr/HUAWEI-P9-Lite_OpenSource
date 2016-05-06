/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_m3.h
*
*   作    者 :  y00184236
*
*   描    述 :  m3启动相关内容
*
*   修改记录 :  2013年5月23日  v1.00  y00184236  创建
*************************************************************************/
#ifndef __BSP_M3_H__
#define __BSP_M3_H__

#include <bsp_sram.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif 

#endif /* __BSP_M3_H__ */
