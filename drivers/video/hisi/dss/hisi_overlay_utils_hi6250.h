/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/
#ifndef _HISI_OVERLAY_UTILS_PLATFORM_H_
#define _HISI_OVERLAY_UTILS_PLATFORM_H_

#include <linux/hisi_fb_common.h>

#define CONFIG_DSS_LP_USED
//#define CONFIG_BACKLIGHT_10000


//GPIO
#define GPIO_LCD_POWER_1V2  (47)     //GPIO_5_7
#define GPIO_LCD_STANDBY    (50)     //GPIO_6_2
#define GPIO_LCD_RESETN     (49)     //GPIO_6_1
#define GPIO_LCD_GATING     (40)     //GPIO_5_0
#define GPIO_LCD_PCLK_GATING (41)    //GPIO_5_1
#define GPIO_LCD_REFCLK_GATING (42)  //GPIO_5_2
#define GPIO_LCD_SPICS         (168) //GPIO_21_0
#define GPIO_LCD_DRV_EN        (53)  //GPIO_6_5

#define GPIO_PG_SEL_A (65)    //GPIO_8_1
#define GPIO_TX_RX_A (67)    //GPIO_8_3
#define GPIO_PG_SEL_B (54)    //GPIO_6_6
#define GPIO_TX_RX_B (56)    //GPIO_7_0

//288 KB
#define MMBUF_SIZE_MAX	(288 * 1024)
#define HISI_DSS_CMDLIST_IDXS_MAX (0x15F3)   //9 cmdlist, 14bit, 01,0101,1111,0011=0x15f3
#define HISI_DSS_DPP_MAX_SUPPORT_BIT (0x3bf) //contrast to enmu dpp_module_idx, DPP_LCP_GMP, IFBC not support
#define HISIFB_DSS_PLATFORM_TYPE  (FB_ACCEL_HI625x | FB_ACCEL_PLATFORM_TYPE_ASIC)

/* for DFS */
/* 1008 * 144bits */
#define DFS_TIME	(80)
#define DBUF0_DEPTH	(1008)

/* scl */
#define SCF_LINE_BUF	(1200)

#define DSS_MIF_SMMU_SMRX_IDX_STEP (1)

//peri reg
#define CRG_PERI_DIS3_DEFAULT_VAL     (0x0002B000)  //bit14 is different

//SYSCTRL
#define SCPWREN 	(0x060)
#define SCPEREN1    (0x170)
#define SCPERDIS1   (0x174)
#define SCPERCLKEN1 (0x0188)
#define SCPERRSTDIS1	(0x210)
#define SCISODIS	    (0x44)

//DSS global
#define DSS_GLB_MODULE_CLK_SEL_DEFAULT_VAL  (0xE0000008)

//LDI0 clk sel
#define DSS_LDI_CLK_SEL_DEFAULT_VAL    (0x0)

//DBuf mem ctrl
#define DSS_DBUF_MEM_CTRL_DEFAULT_VAL  (0x0)

//SMMU
#define DSS_SMMU_RLD_EN0_DEFAULT_VAL    (0xfffffff0)
#define DSS_SMMU_RLD_EN1_DEFAULT_VAL    (0xffffffff)
#define DSS_SMMU_OUTSTANDING_VAL		(0x1)


//MIF
#define DSS_MIF_CTRL2_INVAL_SEL3_STRIDE_MASK		(0xe)

//AFBCE
#define DSS_AFBCE_ENC_OS_CFG_DEFAULT_VAL			(0x5)

#define TUI_SEC_RCH			(DSS_RCHN_V1)

#define DSS_CHN_MAX_DEFINE (DSS_CHN_MAX)

/*******************************************************************************
**
*/
#define CRGPERI_PLL0_CLK_RATE	(1440000000UL)
#define CRGPERI_PLL2_CLK_RATE	(1290000000UL)
#define CRGPERI_PLL3_CLK_RATE	(1600000000UL)

#define DEFAULT_DSS_CORE_CLK_RATE	(360000000UL)
#define DEFAULT_PCLK_DSS_RATE	(120000000UL)
#define DEFAULT_PCLK_PCTRL_RATE	(120000000UL)

/* perf stat */
#define DSS_DEVMEM_PERF_BASE						(0xFF012000)
#define CRG_PERIPH_APB_PERRSTSTAT0_REG 				(0x68)
#define CRG_PERIPH_APB_IP_RST_PERF_STAT_BIT 		(18)
#define PERF_SAMPSTOP_REG 							(0x10)
#define DEVMEM_PERF_SIZE							(0x100)

#endif
