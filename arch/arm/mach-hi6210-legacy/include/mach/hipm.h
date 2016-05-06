/*
 *
 * arch/arm/mach-k3v2/include/mach/hipm.h
 *
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 * Basic platform init and mapping functions.
 *
 */
#ifndef __MACH_K3V2_HIPM_H
#define __MACH_K3V2_HIPM_H


#include <linux/linkage.h>
#include <linux/init.h>
#include <asm/pgtable.h>
#include <mach/platform.h>



/* Define A9 Cluster Address */
#define A9_SCU_BASE             REG_BASE_A9PER
#define A9_GLB_TIMER_BASE       (REG_BASE_A9PER + 0x200)
#define A9_PRV_TIMER_BASE       (REG_BASE_A9PER + 0x600)

#define DDR_CTRLOR_BASE         (REG_BASE_DDRC_CFG)
#define NAND_CTRLOR_BASE        (REG_BASE_NANDC_CFG)

/* MASTER_SR_BACK_PHY_ADDR Store the restore address of CPU0
   SLAVE_BACK_PHY_ADDR store the restore address of CPU1/CPU2/CPU3 */
#define MASTER_SR_BACK_PHY_ADDR    (REG_BASE_SC_OFF+0x308)
#define SLAVE_BACK_PHY_ADDR        (REG_BASE_SC_OFF+0x314)



/************************************************************
 SecuRAM Useage Map During Suspend/Resume


+---------------------------+  0xF8000000
|                           |                 Boot-Code(Support S/R operation)
|       2K Bytes            |                 Including Function: DISMMU_IN_SECURAM, 
|                           |                 ENMMU_IN_SECURAM
+---------------------------+  0xF8000800
|       32 Bytes            |                 Prestore area of CTRL_Register/Aux_Ctrl_register/
|                           |                 TTBR0/TTBR1/TTBCR/DAC of CPU0
+---------------------------+  0xF8000820
|       32 Bytes            |                 Prestore area of CTRL_Register/Aux_Ctrl_register/
|                           |                 TTBR0/TTBR1/TTBCR/DAC of CPU1
+---------------------------+  0xF8000840
|       32 Bytes            |                 Prestore area of CTRL_Register/Aux_Ctrl_register/
|                           |                 TTBR0/TTBR1/TTBCR/DAC of CPU2
+---------------------------+  0xF8000860
|       32 Bytes            |                 Prestore area of CTRL_Register/Aux_Ctrl_register/
|                           |                 TTBR0/TTBR1/TTBCR/DAC of CPU3
+---------------------------+  0xF8000880
|                           |
+---------------------------+  0xF8000900
|       64 Bytes            |                 Store the disable_mmu assembly code
|                           |                 copyed from DDR by hisik3_pm_init()
+---------------------------+  0xF8000940
|       64 Bytes            |                 Store the enable_mmu assembly code
|                           |                 copyed from DDR by hisik3_pm_init()
+---------------------------+  0xF8000980
|       128 Bytes           |                 Slave CPU entry code
|                           |
+---------------------------+  0xF8000A00
|      DeepSleep Code       |
|         1K Bytes          |                 Code to make DDR enter self-refresh, and
|                           |                 Configure the SYSCTRL to make system enter deepsleep
|                           |                 must running in Securam
+---------------------------+  0xF8000E00
|                           |
|~~  ~~  ~~  ~~  ~~  ~~  ~~ |
   ~~  ~~  ~~  ~~  ~~  ~~  ~

A9_PRE_STORE_DATA_ADDR:  the Address in Securam,
A9_PRE_STORE_DATA_LEN:   the data length of each A9
DPSLEEP_CODE_ADDR:       the address of DeepSleep Code
DPSLEEP_CODE_LEN:        the len of DeepSleep Code

******************************************************************/
#define A9_PRE_STORE_DATA_ADDR		(REG_BASE_SECRAM+0x800)
#define A9_PRE_STORE_DATA_LEN		(32)

/* Disable/Enable MMU FUNCTION ADDRESS */
#define DISMMU_CODE_IN_SECURAM  (REG_BASE_SECRAM+0x900)
#define ENMMU_CODE_IN_SECURAM   (REG_BASE_SECRAM+0x940)
#define SECURAM_CODE_LEN        (0x40)
#define SLAVE_CPU_ENTRY_CODE_ADDR	(REG_BASE_SECRAM+0x980)
#define SLAVE_CPU_ENTRY_CODE_LEN	(0x80)

#define DPSLEEP_CODE_ADDR			(REG_BASE_SECRAM+0xA00)
#define DPSLEEP_CODE_LEN			(0x400)

#define SECURAM_CODE_READY_FLAG		(REG_BASE_SCTRL+0x330)

/* SUSPEND_STORE_OFFSET_UNIT define
   the Data-Length of DDR area to save
   A9 context */
#define SUSPEND_STORE_OFFSET_UNIT	(0x200)
#define SUSPEND_STORE_RESEVED_UNIT	(0x30)
#define SUSPEND_STACK_ADDR			(SUSPEND_STORE_RESEVED_UNIT - 0x4)


#define SCU_CONTROL_OFFSET			(0x00)
#define SCU_CONFIG_OFFSET			(0x04)
#define SCU_POWER_STATE_OFFSET		(0x08)
#define SCU_SEC_INVALID_REG_OFFSET	(0x0c)
#define SCU_FILTER_START_OFFSET		(0x40)
#define SCU_FILTER_END_OFFSET		(0x44)
#define SCU_ACCESS_CONTROL_OFFSET	(0x50)
#define SCU_NONSEC_CONTROL_OFFSET	(0x54)

#define L2X0_CACHE_ID				0x000
#define L2X0_CACHE_ID_PART_MASK		(0xf << 6)
#define L2X0_CACHE_ID_PART_L210		(1 << 6)
#define L2X0_CACHE_ID_PART_L310		(3 << 6)
#define L2X0_CACHE_TYPE				0x004
#define L2X0_CTRL                       0x100
#define L2X0_AUX_CTRL                   0x104
#define L2X0_TAG_LATENCY_CTRL           0x108
#define L2X0_DATA_LATENCY_CTRL          0x10C
#define L2X0_EVENT_CNT_CTRL             0x200
#define L2X0_EVENT_CNT1_CFG             0x204
#define L2X0_EVENT_CNT0_CFG             0x208
#define L2X0_EVENT_CNT1_VAL             0x20C
#define L2X0_EVENT_CNT0_VAL             0x210
#define L2X0_INTR_MASK                  0x214
#define L2X0_MASKED_INTR_STAT           0x218
#define L2X0_RAW_INTR_STAT              0x21C
#define L2X0_INTR_CLEAR                 0x220
#define L2X0_CACHE_SYNC                 0x730
#define L2X0_INV_LINE_PA                0x770
#define L2X0_INV_WAY                    0x77C
#define L2X0_CLEAN_LINE_PA              0x7B0
#define L2X0_CLEAN_LINE_IDX             0x7B8
#define L2X0_CLEAN_WAY                  0x7BC
#define L2X0_CLEAN_INV_LINE_PA          0x7F0
#define L2X0_CLEAN_INV_LINE_IDX         0x7F8
#define L2X0_CLEAN_INV_WAY              0x7FC
#define L2X0_LOCKDOWN_WAY_D             0x900
#define L2X0_LOCKDOWN_WAY_I             0x904
#define L2X0_TEST_OPERATION             0xF00
#define L2X0_LINE_DATA                  0xF10
#define L2X0_LINE_TAG                   0xF30
#define L2X0_DEBUG_CTRL                 0xF40
#define L2X0_PREFETCH_OFFSET            0xF60
#define L2X0_PWR_CTRL                   0xF80


#define TIMER_Ld        (0x0)
#define TIMER_Cnt       (0x4)
#define TIMER_Ctl       (0x8)
#define Timer_Int       (0xC)


#define TIM64_CntLo     (0x0)
#define TIM64_CntHi     (0x4)
#define TIM64_Ctl       (0x8)
#define TIM64_Status    (0xC)
#define TIM64_CmpLo     (0x10)
#define TIM64_CmpHi     (0x14)
#define TIM64_AutoInc   (0x18)

/* General CPU constants */
#define Mode_USR        (0x10)
#define Mode_FIQ        (0x11)
#define Mode_IRQ        (0x12)
#define Mode_SVC        (0x13)
#define Mode_ABT        (0x17)
#define Mode_UND        (0x1B)
#define Mode_SYS        (0x1F)
#define I_Bit           (0x80)
#define F_Bit           (0x40)

#define TTBRBIT_MASK			0xFFFFC000
#define TABLE_INDEX_MASK		0xFFF00000
#define TABLE_ENTRY				0x00000C02

#define hisi_v2p(x)		((x) - PAGE_OFFSET + PLAT_PHYS_OFFSET)
#define hisi_p2v(x)		((x) - PLAT_PHYS_OFFSET + PAGE_OFFSET)
#define hisi_se_v2p(x)	((x) - REG_BASE_SECRAM_VIRT + REG_BASE_SECRAM)
#define hisi_se_p2v(x)	((x) - REG_BASE_SECRAM + REG_BASE_SECRAM_VIRT)
#define hisi_sc_v2p(x)	((x) - REG_BASE_SCTRL_VIRT + REG_BASE_SCTRL)
#define hisi_sc_p2v(x)	((x) - REG_BASE_SCTRL + REG_BASE_SCTRL_VIRT)
#define hisi_prv_v2p(x)	((x) - REG_BASE_A9PER_VIRT + REG_BASE_A9PER)
#define hisi_prv_p2v(x)	((x) - REG_BASE_A9PER + REG_BASE_A9PER_VIRT)

/* TCXO stable time configuation */
#define SCXTALCTRL_CFG_VAL_005MS	(0x1FFFF5D0)   /*5ms*/
#define SCXTALCTRL_CFG_VAL_200MS	(0x1FFE6660)   /*200ms*/

#ifndef __ASSEMBLY__
extern asmlinkage void hilpm_cpu_godpsleep(void);
extern asmlinkage void hilpm_cp_securam_code(void);
extern asmlinkage void hilpm_cp_cpuidle_code(void);
#endif

#endif /* #ifndef __MACH_K3V2_HIPM_H */
