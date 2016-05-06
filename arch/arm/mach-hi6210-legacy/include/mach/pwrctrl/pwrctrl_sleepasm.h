/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_sleepasm.h
  版 本 号   : 初稿
  作    者   : 刘永富 56193
  生成日期   : 2012年7月25日
  最近修改   :
  功能描述   : pwrctrl_sleepasm.s 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月25日
    作    者   : 刘永富 56193
    修改内容   : 创建文件

******************************************************************************/
#include <soc_baseaddr_interface.h>
#include <pwrctrl_multi_memcfg.h>


#ifndef PWRCTRL_ACPU_SLEEP_ASM_H
#define PWRCTRL_ACPU_SLEEP_ASM_H


#define _ARM_FUNCTION_CALLED_FROM_C(a) \
    .globl a ;\
    .code  32 ;\
    .balign 4 ;\
a:

/* CPSR config bit . */
#define I_BIT                   (1 << 7)
#define F_BIT                   (1 << 6)

/* mode bits */
#define MODE_SYSTEM32           (0x1F)
#define MODE_UNDEF32            (0x1B)
#define MODE_ABORT32            (0x17)
#define MODE_SVC32              (0x13)
#define MODE_IRQ32              (0x12)
#define MODE_FIQ32              (0x11)
#define MODE_USER32             (0x10)
#define MODE_MASK               (0x1F)



#define IO_ADDRESS(x)                       (x)
#define BIT(x)                              (0x1 << (x))







/******************************************************************************/
/*asm 头文件需要定义, GIC*/
#define ACPU_SCU_BASE                       (SOC_ACPU_A7_PRIVATE_BASE_ADDR)
#define ACPU_GIC_ICC_BASE                   (SOC_ACPU_A7_PRIVATE_BASE_ADDR + 0x2000)
#define ACPU_GIC_DIST_BASE                  (SOC_ACPU_A7_PRIVATE_BASE_ADDR + 0x1000)
#define ACPU_GIC_ICCICR                     (ACPU_GIC_ICC_BASE + 0x000)
#define ACPU_GIC_ICDDCR                     (ACPU_GIC_DIST_BASE + 0x000)
#define ACPU_GIC_ICDICER                    (ACPU_GIC_DIST_BASE + 0x180)

/*asm 头文件需要定义, Ipc*/
#define PWRCTRL_SOC_IPC_CPU_RAW_INT_ADDR(base, i)             \
                                            ((base) + (0x400+(0x10*(i))))

#define PWRCTRL_ACPU_PD_IPC_REG             PWRCTRL_SOC_IPC_CPU_RAW_INT_ADDR(SOC_IPC_S_BASE_ADDR, 2)  /*tobedone*/
#define PWRCTRL_ACPU_PD_IPC_BIT             (BIT(16))                       /*tobedone,PWC_PWDN_IPC_ACPU_ID */

/*asm 头文件需要定义, EXC*/
#define EXCH_ACPU_CORE_PWC_ASM_ADDR         (EXCH_A_CORE_POWRCTRL_CONV_ADDR)    /*phy addr*/
#define EXCH_ACPU_CORE_INFO_OFFSET          (0x50)   /* (sizeof(PWRCTRL_ACPU_EXC_PD_STRU)) */

/*asm 头文件需要定义,AO*/
#define PWRCTRL_SOC_AO_SCTRL_SC_RESERVED32_ADDR(base)         ((base) + (0x13A4))
#define PWRCTRL_ACPU0_L2CACHE_FLUSH_FLAG	PWRCTRL_SOC_AO_SCTRL_SC_RESERVED32_ADDR(IO_ADDRESS(SOC_AO_SCTRL_BASE_ADDR))

/*asm 头文件需要定义，L2C*/
#define PWRCTRL_SOC_L2C_CACHE_SYNC_ADDR(base)                 ((base) + (0x730))
#define PWRCTRL_SOC_L2C_CLEAN_WAY_ADDR(base)                  ((base) + (0x7BC))
#if defined(CHIP_BB_HI6210)/*B020 Modify*/
#else
#define PWRCTRL_ACPU0_L2CACHE_CACHE_SYNC	PWRCTRL_SOC_L2C_CACHE_SYNC_ADDR(SOC_L2CC_BASE_ADDR)
#define PWRCTRL_ACPU0_L2CACHE_CLEAN_WAY		PWRCTRL_SOC_L2C_CLEAN_WAY_ADDR(SOC_L2CC_BASE_ADDR)
#endif
/******************************************************************************/

/**********************************L2CACHE FLASH**************************************/
#define L2CACHE_REFSH_START		(0x11551155)
#define L2CACHE_REFSH_DONE		(0x55111155)

/********************************* v addr **************************************/
#define PWRCTRL_ACPU_ASM_D_C0_VA            IO_ADDRESS(PWRCTRL_ACPU_ASM_D_C0_ADDR)
#define PWRCTRL_ACPU_ASM_D_C0_MMU_PARA_VA   IO_ADDRESS(PWRCTRL_ACPU_ASM_D_C0_VA + 0)


#define PWRCTRL_ACPU_ASM_D_COMM_VA          IO_ADDRESS(PWRCTRL_ACPU_ASM_D_COMM_ADDR)/*common addr*/
#define PWRCTRL_ACPU_ASM_MEM_VADDR          IO_ADDRESS(PWRCTRL_ACPU_ASM_CODE_BASE)

#define PWRCTRL_ACPU_ASM_SLICE_BAK_VA       IO_ADDRESS(PWRCTRL_ACPU_ASM_SLICE_BAK_ADDR)
#define PWRCTRL_ACPU_ASM_DEBUG_FLAG_VA      IO_ADDRESS(PWRCTRL_ACPU_ASM_DEBUG_FLAG_ADDR)







/******************************************************************************/
#define PWRCTRL_ASM_CODE_COPY_OFFSET        (0x100)
#define PWRCTRL_ASM_CORE_AREA_OFFSET        (0x200)



#define PWRCTRL_ACPU_DLOOP_WAKE             (0xADEB0)
#define PWRCTRL_ACPU_DLOOP_SLEEP_MMU_DIS    (0xADEB1)
#define PWRCTRL_ACPU_DLOOP_SLEEP            (0xADEB2)




#define PWRCTRL_ASM_LINK_MAGIC1             (0xAABBCCDD)
#define PWRCTRL_ASM_LINK_MAGIC2             (0xDDCCBBAA)




#endif
