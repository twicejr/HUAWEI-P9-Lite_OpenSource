/* mmu_config.c - modem subsystem mmu remap */

/*
 * Copyright huawei Inc.
 *
 * this file for remap modem subsystem for both vxworks and rtosck
 */

/*lint -e451*/
#include "sre_config.h"
#include "sre_mmu.h"
#include <product_config.h>
#include <osl_bio.h>
#include <bsp_memmap.h>
#ifdef CONFIG_SMART_SYSTEM_MODEM
#include <hi_uart.h>
#include <soc_timer.h>
#endif
/*lint +e451*/
#define MMU_ARRAY_SIZE(array) (sizeof (array) / sizeof ((array) [0]))

#ifndef ROUND_DOWN
#define ROUND_DOWN(x, align)    ((int)(x) & ~(align - 1))
#endif

#define ROUND_UP(uwAddr, uwBoundary)  (((uwAddr) + (uwBoundary) - 1) & ~((uwBoundary) - 1))
#define PAGE_SIZE (4*1024)

#ifdef CONFIG_SMART_SYSTEM_MODEM
VIRT_PHYS_MEM_S sysPhysMemDesc [] =
{
	/* DRAM - Always the first entry */
	{
         DDR_MCORE_ADDR,    /* virtual address */
         DDR_MCORE_ADDR,    /* physical address */
         ROUND_UP (DDR_MCORE_SIZE, PAGE_SIZE),
         MMU_STATEMASK_ALL,
         MMU_STATE_RWX | OS_MMU_STATE_CACHE_WBWA
    },
	{
        HI_MDM_GIC_BASE_ADDR_VIRT,/* HI_MDM_GIC_BASE_ADDR */
        HI_MDM_GIC_BASE_ADDR,
        ROUND_UP (HI_MDM_GIC_SIZE, PAGE_SIZE),
        MMU_STATEMASK_ALL,
        MMU_STATE_RW | OS_MMU_STATE_STRONGLY_ORDERED
    },
    {
        CCORE_SYS_UART_BASE,  /* CCORE_SYS_UART_BASE */
        CCORE_SYS_UART_BASE,
        ROUND_UP (0x1000, PAGE_SIZE),
        MMU_STATEMASK_ALL,
        MMU_STATE_RW | OS_MMU_STATE_STRONGLY_ORDERED
     },
     {
       CCORE_SYS_TIMER_BASE_ADDR,  /* CCORE_SYS_TIMER_BASE_ADDR */
       CCORE_SYS_TIMER_BASE_ADDR,
       ROUND_UP (0x1000, PAGE_SIZE),
       MMU_STATEMASK_ALL,
       MMU_STATE_RW | OS_MMU_STATE_STRONGLY_ORDERED
     },
     {
       HI_SYSCTRL_BASE_ADDR,  /* CCORE_SYS_TIMER_BASE_ADDR */
       HI_SYSCTRL_BASE_ADDR,
       ROUND_UP (HI_SYSCTRL_REG_SIZE, PAGE_SIZE),
       MMU_STATEMASK_ALL,
       MMU_STATE_RW | OS_MMU_STATE_STRONGLY_ORDERED
     },
};
#else

VIRT_PHYS_MEM_S sysPhysMemDesc [] =
{
	/* DRAM - Always the first entry */
	{
         DDR_MCORE_ADDR,    /* virtual address */
         DDR_MCORE_ADDR,    /* physical address */
         ROUND_UP (DDR_MCORE_SIZE, PAGE_SIZE),
         MMU_STATEMASK_ALL,
         MMU_STATE_RWX | OS_MMU_STATE_CACHE_WBWA
    },
     /* DDR_MCORE_DTS_ADDR */
#ifdef DDR_MCORE_DTS_ADDR
         {
         DDR_MCORE_DTS_ADDR,    /* virtual address */
         DDR_MCORE_DTS_ADDR,    /* physical address */
         ROUND_UP (DDR_MCORE_DTS_SIZE, PAGE_SIZE),
         MMU_STATEMASK_ALL,
         MMU_STATE_RWX | OS_MMU_STATE_STRONGLY_ORDERED
         },
#endif
	{0, 0, 0, 0, 0}, /* HI_MDM_GIC_BASE_ADDR */
	{0, 0, 0, 0, 0}, /* HI_UART_REGBASE_ADDR */
    
#ifdef CONFIG_BALONG_L2CACHE
	{0, 0, 0, 0, 0}, /* l2cache */
#endif

};
#endif
int sysPhysMemDescNumEnt = MMU_ARRAY_SIZE(sysPhysMemDesc);


