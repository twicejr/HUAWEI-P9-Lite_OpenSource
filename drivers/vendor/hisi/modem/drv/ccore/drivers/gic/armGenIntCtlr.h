#ifndef _INCarmGenIntCtlrh
#define _INCarmGenIntCtlrh

#ifdef __cplusplus
extern "C"{
#endif
#include "product_config.h"

/* 
 * the explanation of some abbreviations
 *
 * CPC - Cross Processor Call
 * IPI - Inter Processor Interrupt
 * GIC - General Interrupt Controller
 * SGI - Software Generated Interrupt
 * PPI - Private Peripheral Interrupt
 * SPI - Shared Peripheral Interrupt
 */

#define ARM_GIC_IPI_COUNT       16  /* MPCore IPI count */
#define GIC_LEVEL_MAX           16

#define GIC_INT_ALL_ENABLED     0xFF  /* priority 0-0x1F can run */

#define GIC_INT_ALL_DISABLED    0x00  /* nothing higher than 0 hence disabled */
#define GIC_INT_SPURIOUS        0x3FF /* no interrupt currently */
#define GIC_INT_CONFIG_SOFT     0xAAAAAAAA /* interrupt config to N-N, Edge */
#define GIC_INT_CONFIG_SPI      0x55555555 /* interrupt config to 1-N, High */
#define GIC_CPU_BINP_DEFAULT    0x02  /* 0x02 means that the mask is 0xf8 */
#define GIC_CPU_CONTROL_ENABLE  0x1   /* enable the processor interface */
#define GIC_CPU_ALL_ENABLED     0xFF  /* priority 0-E can run */
#define GIC_CPU_ALL_DISABLED    0x00  /* nothing higher than 0 */
#define GIC_SGI_SRC_CPU_ID_MASK 0x1C00
#define GIC_INT_HIGHEST_PRIORITY 0x0 /* the highest priority for interrupts */


#define GIC_INT_LOWEST_PRIORITY 0x1F /* the lowest priority for interrupts */

#define GIC_CPU_DIR_DEFAULT 0x01010101 /* all interrupts are directed to CPU0 */

#define GIC_CPU_DIR_CORE1   0x02020202 /* all interrupts are directed to CPU0 */

#define GIC_CONTROL_ENABLE  0x01

#define ALL_PPI_INT_MASK    0xF8000000 /* bit field for all PPI interrupts */
#define ALL_SGI_INT_MASK    0x0000FFFF /* bit field for all SGI interrupts */

/**************************************************************************
                  *中断优先级别*
***************************************************************************/
#define GIC_CFG_TO_CPU0 0x01010101
/* Generic Interupt Controller details configuration*/
#define GIC_IPI_LEVEL       0xc0c0c0c0        /*SGI level(24)*/
#define GIC_DEFAULT_LEVEL   0xf0f0f0f0        
#define GIC_SPI_LEVEL       0xf0f0f0f0
#define GIC_CPU_NUM         (2)


/* ARM GIC interrupt distributor and CPU interface register access macros */

#define BITS_PER_WORD           32
#define CONFIGS_PER_WORD        16
#define PRIOS_PER_WORD          4
#define TARGETS_PER_WORD        4
#define NWORD(bitnum)           (bitnum / 32)
#define BIT(bitnum)             (1 << (bitnum % BITS_PER_WORD))
#define REG_BYTE(index)         ((index % 4) * 8)
#define BYTE_MASK               0x00ff

#ifndef _ASMLANGUAGE

#define GIC_DIST  (armGicBase + 0x1000) /* GIC distributor base address */
#define GIC_CPU   (armGicBase + 0x100)  /* GIC CPU interface base address */

/* interrupt distributor control */

#define GIC_Control            ((volatile UINT32 *)(GIC_DIST + 0x000))

/* interrupt controller type */

#define GIC_Type               ((volatile UINT32 *)(GIC_DIST + 0x004))

/* interrupt enable */

#define GIC_IntEnable(Periph)  ((volatile UINT32 *)(GIC_DIST + 0x100 + \
                                          (0x4 * NWORD(Periph))))
/* clear interrupt enable */

#define GIC_IntEnClr(Periph)   ((volatile UINT32 *)(GIC_DIST + 0x180 + \
                                          (0x4 * NWORD(Periph))))
/* interrupt active status */

#define GIC_IntActSts(Periph)   ((volatile UINT32 *)(GIC_DIST + 0x300 + \
                                          (0x4 * NWORD(Periph))))

/* clear pending interrupt */

#define GIC_IntPendClr(Periph) ((volatile UINT32 *)(GIC_DIST + 0x280 + \
                                          (0x4 * NWORD(Periph))))
/* interrupt configuration */

#define GIC_Config(Periph)     ((volatile UINT32 *)(GIC_DIST + 0xC00 + \
                                          (0x4 * (Periph / CONFIGS_PER_WORD))))
/* interrupt priority  */

#define GIC_Prio(Periph)       ((volatile UINT32 *)(GIC_DIST + 0x400 + \
                                          (0x4 * (Periph / PRIOS_PER_WORD))))                        
/* CPU target */

#define GIC_CPUTarg(Periph)    ((volatile UINT32 *)(GIC_DIST + 0x800 + \
                                          (0x4 * (Periph / TARGETS_PER_WORD))))
                                          
#define GIC_SetPend(Periph) ((volatile UINT32 *)(GIC_DIST + 0x200 + \
                                          (0x4 * NWORD(Periph))))
/* software interrupt generate */

#define GIC_SWInterrupt        ((volatile UINT32 *)(GIC_DIST + 0xF00))

/* CPU interrupt control */

#define GIC_CPU_Control        ((volatile UINT32 *)(GIC_CPU + 0x00))

/* CPU priority mask */

#define GIC_CPU_PriMask        ((volatile UINT32 *)(GIC_CPU + 0x04))

/* CPU binary point */

#define GIC_CPU_BinPoint       ((volatile UINT32 *)(GIC_CPU + 0x08))

/* CPU interrupt acknowledge */

#define GIC_CPU_IntAck         ((volatile UINT32 *)(GIC_CPU + 0x0C))

/* CPU end of interrupt */

#define GIC_CPU_EOInt          ((volatile UINT32 *)(GIC_CPU + 0x10))

/* the running  priority interrupt */

#define GIC_CPU_RPR            ((volatile UINT32 *)(GIC_CPU + 0x14))
       
/* the highest pending interrupt */

#define GIC_CPU_HPIR           ((volatile UINT32 *)(GIC_CPU + 0x18))


#endif /* _ASMLANGUAGE */

//trigger mode
enum tri_mode
{
   EDGE,
   LEVEL
};

/******************************************************************************
* Function     :   armGicHwLvlChg
* 
* Description  :   修改GIC中断优先级
* 
* Input        :   vector   要修改优先级的中断号
*              :   level        修改改后的中断优先级   
* 
* return       :   STATUS OK OR ERROR
******************************************************************************/

STATUS armGicHwLvlChg(int vector,int level);


/******************************************************************************
* Function     :   armGicIntReroute
* 
* Description  :   重新配置处理某个中断的CPU ID
* 
* Input        :   index    要配置的中断号
*              :   destCpu      配置中断发往的目标CPU ID  
* 
* return       :   STATUS OK OR ERROR
******************************************************************************/
STATUS armGicIntReroute
    (
    UINT32                 index,
    cpuset_t            destCpu
    );


#ifdef __cplusplus
}
#endif

#endif  
