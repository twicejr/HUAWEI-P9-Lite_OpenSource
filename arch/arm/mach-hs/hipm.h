/*
 * Header for power management related routines
 *
 * Copyright © 2011-2013 HiSilicon Technologies Co., Ltd.
 *              http://www.hisilicon.com
 * Copyright © 2012-2013 Linaro Ltd.
 *              http://www.linaro.org
 *
 * Author: Guodong Xu <guodong.xu@linaro.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 */
#ifndef __MACH_HS_HIPM_H
#define __MACH_HS_HIPM_H

#include <linux/linkage.h>
#include <linux/init.h>
#include <asm/pgtable.h>

/* Physical DRAM offset */
#define K3_PLAT_PHYS_OFFSET		UL(0x40000000)

#define SR_PROTECT_CTX_BUFF_SIZE	(2048)
#define PMU_HRST_REG			(hs_pmuspi_va_base + (0x87 << 2))

#define REG_BASE_SECRAM			(0xF8000000)
#define REG_BASE_L2CC			(0xFC100000)
#define REG_BASE_A9PER			(0xFC000000)
#define REG_BASE_DDRC_CFG		(0xFCD00000)
#define REG_BASE_SCTRL			(0xFC802000)
#define REG_BASE_PMCTRL			(0xFCA08000)
#define REG_BASE_PCTRL			(0xFCA09000)
#define REG_BASE_PMUSPI			(0xFCC00000)

/* Define A9 Cluster Address */
#define A9_SCU_BASE             REG_BASE_A9PER
#define A9_PRV_TIMER_BASE	(REG_BASE_A9PER + 0x600)
#define A9_GLB_TIMER_BASE       (REG_BASE_A9PER + 0x200)

#define DDR_CTRLOR_BASE         (REG_BASE_DDRC_CFG)
#define NAND_CTRLOR_BASE        (REG_BASE_NANDC_CFG)

/* OFFSETs based off SYSCTRL */
/* MASTER_SR_BACK_PHY_ADDR Store the restore address of CPU0
 */
#define MASTER_SR_BACK_PHY_ADDR			(REG_BASE_SCTRL + 0x308)

/************************************************************
 SecuRAM Useage Map During Suspend/Resume


+---------------------------+  0xF8000000
|                           |                 Boot-Code(Support S/R operation)
|       2K Bytes            |                 Including Function:
|                           |				DISMMU_IN_SECURAM,
|                           |                 ENMMU_IN_SECURAM
+---------------------------+  0xF8000800
|       32 Bytes            |                 Prestore area of CTRL_Register/
|                           |			           Aux_Ctrl_register/
|                           |                 TTBR0/TTBR1/TTBCR/DAC of CPU0
+---------------------------+  0xF8000820
|       32 Bytes            |                 Prestore area of CTRL_Register/
|                           |				   Aux_Ctrl_register/
|                           |                 TTBR0/TTBR1/TTBCR/DAC of CPU1
+---------------------------+  0xF8000840
|       32 Bytes            |                 Prestore area of CTRL_Register/
|                           |				   Aux_Ctrl_register/
|                           |                 TTBR0/TTBR1/TTBCR/DAC of CPU2
+---------------------------+  0xF8000860
|       32 Bytes            |                 Prestore area of CTRL_Register/
|                           |				   Aux_Ctrl_register/
|                           |                 TTBR0/TTBR1/TTBCR/DAC of CPU3
+---------------------------+  0xF8000880
|                           |
+---------------------------+  0xF8000900
|       64 Bytes            |                 Store disable_mmu assembly code
+---------------------------+  0xF8000940
|       64 Bytes            |                 Store the enable_mmu assembly code
+---------------------------+  0xF8000980
|       128 Bytes           |                 Slave CPU entry code
|                           |
+---------------------------+  0xF8000A00
|      DeepSleep Code       |
|         1K Bytes          |                 Code to make DDR enter
|                           |			self-refresh, and
|                           |			configure the SYSCTRL to
|                           |			make system enter deepsleep
+---------------------------+  0xF8000E00
|                           |
|~~  ~~  ~~  ~~  ~~  ~~  ~~ |
   ~~  ~~  ~~  ~~  ~~  ~~  ~

A9_PRE_STORE_DATA_ADDR:  the Address in Securam,
A9_PRE_STORE_DATA_LEN:   the data length of each A9
DPSLEEP_CODE_ADDR:       the address of DeepSleep Code
DPSLEEP_CODE_LEN:        the len of DeepSleep Code

******************************************************************/

/* Disable/Enable MMU FUNCTION ADDRESS */
#define DISMMU_CODE_IN_SECURAM  (REG_BASE_SECRAM+0x900)
#define ENMMU_CODE_IN_SECURAM   (REG_BASE_SECRAM+0x940)
#define SECURAM_CODE_LEN        (0x40)

/* OFFSETs based off SECRAM */
#define SLAVE_CPU_ENTRY_CODE_ADDR	(REG_BASE_SECRAM + 0x980)
#define SLAVE_CPU_ENTRY_CODE_LEN	(0x80)
#define A9_PRE_STORE_DATA_ADDR_OFFSET	(0x800)
#define A9_PRE_STORE_DATA_LEN		(32)
#define DPSLEEP_CODE_ADDR_OFFSET	(0xA00)
#define DPSLEEP_CODE_LEN		(0x400)

#define SECURAM_CODE_READY_FLAG		(REG_BASE_SCTRL+0x330)

/* SUSPEND_STORE_OFFSET_UNIT define
   the Data-Length of DDR area to save
   A9 context */
#define SUSPEND_STORE_OFFSET_UNIT	(0x200)
#define SUSPEND_STORE_RESEVED_UNIT	(0x30)
#define SUSPEND_STACK_ADDR		(SUSPEND_STORE_RESEVED_UNIT - 0x4)


#define SCU_CONTROL_OFFSET			(0x00)
#define SCU_CONFIG_OFFSET			(0x04)
#define SCU_POWER_STATE_OFFSET		(0x08)
#define SCU_SEC_INVALID_REG_OFFSET	(0x0c)
#define SCU_FILTER_START_OFFSET		(0x40)
#define SCU_FILTER_END_OFFSET		(0x44)
#define SCU_ACCESS_CONTROL_OFFSET	(0x50)
#define SCU_NONSEC_CONTROL_OFFSET	(0x54)

#define L2X0_AUX_CTRL                   0x104
#define L2X0_TAG_LATENCY_CTRL           0x108
#define L2X0_DATA_LATENCY_CTRL          0x10C
#define L2X0_PREFETCH_OFFSET            0xF60

#define TIMER_LD        (0x0)
#define TIMER_CTL       (0x8)

#define TIM64_CNTLO     (0x0)
#define TIM64_CNTHI     (0x4)
#define TIM64_CTL       (0x8)
#define TIM64_CMPLO     (0x10)
#define TIM64_CMPHI     (0x14)
#define TIM64_AUTOINC   (0x18)

/* General CPU constants */
#define MODE_FIQ        (0x11)
#define MODE_IRQ        (0x12)
#define MODE_SVC        (0x13)
#define MODE_ABT        (0x17)
#define MODE_UND        (0x1B)
#define MODE_SYS        (0x1F)
#define I_BIT           (0x80)
#define F_BIT           (0x40)

#define TTBRBIT_MASK			0xFFFFC000
#define TABLE_INDEX_MASK		0xFFF00000
#define TABLE_ENTRY				0x00000C02

#define hisi_v2p(x)		((x) - PAGE_OFFSET + K3_PLAT_PHYS_OFFSET)
#define hisi_p2v(x)		((x) - K3_PLAT_PHYS_OFFSET + PAGE_OFFSET)

/* TCXO stable time configuation */
#define SCXTALCTRL_CFG_VAL_005MS	(0x1FFFF5D0)   /*5ms*/
#define SCXTALCTRL_CFG_VAL_200MS	(0x1FFE6660)   /*200ms*/

#ifndef __ASSEMBLY__
extern asmlinkage void __iomem *hs_finish_suspend(void);
extern asmlinkage void __iomem *master_cpu_resume(void);
extern asmlinkage void __iomem *get_ttbr0(void);
extern asmlinkage void hilpm_cpu_godpsleep(void);
extern asmlinkage void hilpm_cp_securam_code(void __iomem *);
extern asmlinkage void hilpm_cp_cpuidle_code(void);
extern unsigned long hi_cpu_godpsleep_ddrbase;
extern unsigned long hi_cpu_godpsleep_phybase;
#endif

#endif /* #ifndef __MACH_HS_HIPM_H */
