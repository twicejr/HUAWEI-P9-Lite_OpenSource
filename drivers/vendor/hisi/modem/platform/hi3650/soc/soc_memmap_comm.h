/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __SOC_MEMMAP_COMM_H__
#define __SOC_MEMMAP_COMM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"

/* 非2^n大小的宏，内核未定义，需要放到公共区 */
#ifndef SZ_20K
#define SZ_20K                           (0x00005000)
#endif

#ifndef SZ_80K
#define SZ_80K                           (0x00014000)
#endif

#ifndef SZ_96K
#define SZ_96K                           (0x00018000)
#endif

#ifndef SZ_3M
#define SZ_3M                            (0x00300000)
#endif

#ifdef __KERNEL__
#include <asm-generic/sizes.h>
#else
/************************************************************************
                * size *
************************************************************************/
#ifndef SZ_512
#define SZ_512                          (0x00000200)
#endif

#ifndef SZ_1K
#define SZ_1K                            (0x00000400)
#endif

#ifndef SZ_2K
#define SZ_2K                            (0x00000800)
#endif

#ifndef SZ_4K
#define SZ_4K                            (0x00001000)
#endif

#ifndef SZ_8K
#define SZ_8K                            (0x00002000)
#endif

#ifndef SZ_16K
#define SZ_16K                           (0x00004000)
#endif

#ifndef SZ_32K
#define SZ_32K                           (0x00008000)
#endif

#ifndef SZ_64K
#define SZ_64K                           (0x00010000)
#endif

#ifndef SZ_128K
#define SZ_128K                          (0x00020000)
#endif

#ifndef SZ_256K
#define SZ_256K                          (0x00040000)
#endif

#ifndef SZ_512K
#define SZ_512K                          (0x00080000)
#endif

#ifndef SZ_1M
#define SZ_1M                            (0x00100000)
#endif

#ifndef SZ_2M
#define SZ_2M                            (0x00200000)
#endif

#ifndef SZ_4M
#define SZ_4M                            (0x00400000)
#endif

#ifndef SZ_8M
#define SZ_8M                            (0x00800000)
#endif

#ifndef SZ_16M
#define SZ_16M                           (0x01000000)
#endif

#ifndef SZ_32M
#define SZ_32M                           (0x02000000)
#endif

#ifndef SZ_64M
#define SZ_64M                           (0x04000000)
#endif

#ifndef SZ_128M
#define SZ_128M                          (0x08000000)
#endif

#ifndef SZ_256M
#define SZ_256M                          (0x10000000)
#endif

#ifndef SZ_512M
#define SZ_512M                          (0x20000000)
#endif
#endif

/************************************************************************
                * IP BASE ADDR *
************************************************************************/

/* SOCP */
#define HI_SOCP_REGBASE_ADDR              (0XFF030000)
#define HI_SOCP_REG_SIZE                  (SZ_4K)

/* I2C1 */
#define HI_I2C1_REGBASE_ADDR              (0XFDF0AFFF)
#define HI_I2C1_REG_SIZE                  (SZ_4K)

/* I2C0 */
#define HI_I2C0_REGBASE_ADDR              (0XFDF09FFF)
#define HI_I2C0_REG_SIZE                  (SZ_4K)

/*SPI Master 0*/
#define HI_SPI_MST0_REGBASE_ADDR          (0XFDF07FFF)
#define HI_SPI_MST0_REG_SIZE              (SZ_4K)

/*SPI Master 1*/
#define HI_SPI_MST1_REGBASE_ADDR          (0XFDF08FFF)
#define HI_SPI_MST1_REG_SIZE              (SZ_4K)

/* UART5 */
#define HI_UART5_REGBASE_ADDR			  (0xFDF05000)
#define HI_UART5_REG_SIZE                 (SZ_4K)
/* UART3 */
#define HI_UART3_REGBASE_ADDR             (0XFDF04FFF)
#define HI_UART3_REG_SIZE                 (SZ_4K)

/* UART2 */
#define HI_UART2_REGBASE_ADDR             (0XFDF03FFF)
#define HI_UART2_REG_SIZE                 (SZ_4K)

/* UART0 */
#define HI_APB_CFG_UART0_BASE_ADDR        (0XFDF02FFF)
#define HI_APB_CFG_UART0_SIZE             (SZ_4K)

/* UART1 */
#define HI_UART1_REGBASE_ADDR             (0XFDF00FFF)
#define HI_UART1_REG_SIZE                 (SZ_4K)

/*********************** APB1_CFG  definition ***********************/

/* PINTRL MUX AND CFG */
#define HI_PINTRL_REG_ADDR				  (0xE896C000)
#define HI_PINTRL_REG_SIZE			      (SZ_4K)

/* PINTRL MUX AND CFG */
#define HI_PINTRL_SYS_REG_ADDR			  (0xFFF11000)
#define HI_PINTRL_SYS_REG_SIZE			  (SZ_4K)

/* GPIO0 */
#define HI_GPIO0_REGBASE_ADDR		       (0xE8A0B000)
#define HI_GPIO0_REG_SIZE                  (SZ_4K)

/* GPIO1 */
#define HI_GPIO1_REGBASE_ADDR			   (0xE8A0C000)
#define HI_GPIO1_REG_SIZE                  (SZ_4K)

/* GPIO2 */
#define HI_GPIO2_REGBASE_ADDR			   (0xE8A0D000)
#define HI_GPIO2_REG_SIZE                  (SZ_4K)

/* GPIO3 */
#define HI_GPIO3_REGBASE_ADDR			   (0xE8A0E000)
#define HI_GPIO3_REG_SIZE                  (SZ_4K)

/* GPIO4 */
#define HI_GPIO4_REGBASE_ADDR		       (0xE8A0F000)
#define HI_GPIO4_REG_SIZE                  (SZ_4K)

/* GPIO5 */
#define HI_GPIO5_REGBASE_ADDR			   (0xE8A10000)
#define HI_GPIO5_REG_SIZE                  (SZ_4K)

/* GPIO6 */
#define HI_GPIO6_REGBASE_ADDR		       (0xE8A11000)
#define HI_GPIO6_REG_SIZE                  (SZ_4K)

/* GPIO7 */
#define HI_GPIO7_REGBASE_ADDR			   (0xE8A12000)
#define HI_GPIO7_REG_SIZE                  (SZ_4K)

/* GPIO8 */
#define HI_GPIO8_REGBASE_ADDR			   (0xE8A13000)
#define HI_GPIO8_REG_SIZE                  (SZ_4K)

/* GPIO9 */
#define HI_GPIO9_REGBASE_ADDR			   (0xE8A14000)
#define HI_GPIO9_REG_SIZE                  (SZ_4K)

/* GPIO10 */
#define HI_GPIO10_REGBASE_ADDR			   (0xE8A15000)
#define HI_GPIO10_REG_SIZE                 (SZ_4K)

/* GPIO11 */
#define HI_GPIO11_REGBASE_ADDR			   (0xE8A16000)
#define HI_GPIO11_REG_SIZE                 (SZ_4K)

/* GPIO12 */
#define HI_GPIO12_REGBASE_ADDR			   (0xE8A17000)
#define HI_GPIO12_REG_SIZE                 (SZ_4K)

/* GPIO13 */
#define HI_GPIO13_REGBASE_ADDR			   (0xE8A18000)
#define HI_GPIO13_REG_SIZE                 (SZ_4K)

/* GPIO14 */
#define HI_GPIO14_REGBASE_ADDR			   (0xE8A19000)
#define HI_GPIO14_REG_SIZE                 (SZ_4K)

/* GPIO15 */
#define HI_GPIO15_REGBASE_ADDR			   (0xE8A1A000)
#define HI_GPIO15_REG_SIZE                 (SZ_4K)

/* GPIO16 */
#define HI_GPIO16_REGBASE_ADDR			   (0xE8A1B000)
#define HI_GPIO16_REG_SIZE                 (SZ_4K)

/* GPIO17 */
#define HI_GPIO17_REGBASE_ADDR			   (0xE8A1C000)
#define HI_GPIO17_REG_SIZE                 (SZ_4K)

/* GPIO18 */
#define HI_GPIO18_REGBASE_ADDR			   (0xE8A1D000)
#define HI_GPIO18_REG_SIZE                 (SZ_4K)

/* GPIO19 */
#define HI_GPIO19_REGBASE_ADDR			   (0xE8A1E000)
#define HI_GPIO19_REG_SIZE                 (SZ_4K)

/* GPIO20 */
#define HI_GPIO20_REGBASE_ADDR			   (0xE8A1F000)
#define HI_GPIO20_REG_SIZE                 (SZ_4K)

/* GPIO21 */
#define HI_GPIO21_REGBASE_ADDR			   (0xE8A20000)
#define HI_GPIO21_REG_SIZE                 (SZ_4K)

/* GPIO22 */
#define HI_GPIO22_REGBASE_ADDR			   (0xFFF0B000)
#define HI_GPIO22_REG_SIZE                 (SZ_4K)

/* GPIO23 */
#define HI_GPIO23_REGBASE_ADDR			   (0xFFF0C000)
#define HI_GPIO23_REG_SIZE                 (SZ_4K)

/* GPIO24 */
#define HI_GPIO24_REGBASE_ADDR			   (0xFFF0D000)
#define HI_GPIO24_REG_SIZE                 (SZ_4K)

/* GPIO25 */
#define HI_GPIO25_REGBASE_ADDR			   (0xFFF0E000)
#define HI_GPIO25_REG_SIZE                 (SZ_4K)

/* GPIO26 */
#define HI_GPIO26_REGBASE_ADDR			   (0xFFF0F000)
#define HI_GPIO26_REG_SIZE                 (SZ_4K)

/* todo: PWM1 */
#define HI_PWM1_REGBASE_ADDR              (0XE8A05000)
#define HI_PWM1_REG_SIZE                  (SZ_4K)

/* todo: PWM0 */
#define HI_PWM0_REGBASE_ADDR              (0XE8A04000)
#define HI_PWM0_REG_SIZE                  (SZ_4K)

/* HKADC SSI */
#define HI_HKADCSSI_REGBASE_ADDR          (0XE82B8000)
#define HI_HKADCSSI_REG_SIZE              (SZ_4K)

/* APP GIC */
#define HI_APP_GIC_BASE_ADDR              (0xE82B0000)
#define HI_APP_GIC_SIZE                   (SZ_32K)

/*********************** MODEM_SUBSYS  definition ***********************/
#define HI_MODEM_BASE_ADDR                (0xE0000000)
#define HI_MODEM_SIZE                     (SZ_128M)

/* A9 L2 reg */
#define HI_MDMA9_L2_REGBASE_ADDR          (0xE0000000)
#define HI_MDMA9_L2_REG_SIZE              (SZ_1M)

/* MDM GIC */
#define HI_MDM_GIC_BASE_ADDR              (0xE0100000)
#define HI_MDM_GIC_SIZE                   (SZ_8K)

/* system controller */
#define HI_SYSCTRL_BASE_ADDR              (0xE0200000)
#define HI_SYSCTRL_REG_SIZE               (SZ_4K)

#define HI_SYSCRG_BASE_ADDR               HI_SYSCTRL_BASE_ADDR
#define HI_SYSSC_BASE_ADDR                HI_SYSCTRL_BASE_ADDR
#define HI_PWRCTRL_BASE_ADDR              HI_SYSCTRL_BASE_ADDR
#define HI_SYSSC_AO_BASE_ADDR                    HI_SYSCTRL_BASE_ADDR
#define HI_SYSSC_PD_BASE_ADDR                    HI_SYSCTRL_BASE_ADDR

/* AP 侧system controller */
#define HI_AP_SYSCTRL_BASE_ADDR              (0xFFF0A000)
#define HI_AP_SYSCTRL_REG_SIZE               (SZ_4K)

#define HI_AP_SCTRL_BASE_ADDR             HI_AP_SYSCTRL_BASE_ADDR
#define HI_AP_SYS_CNT_BASE_ADDR              (0xFFF08000)
#define HI_AP_SYS_CNT_SIZE                   (SZ_8K)

/* PERI_CRG  */
#define HI_LP_PERI_CRG_REG_ADDR           (0xFFF35000)
#define HI_LP_PERI_CRG_REG_SIZE           (SZ_4K)

/* PERI_CRG  */
#define HI_NOC_PMC_REG_ADDR           (0xFFF31000)
#define HI_NOC_PMC_REG_SIZE           (SZ_4K)




/* watchdog(WDT) */
#define HI_WDT_BASE_ADDR                  (0xE0201000)
#define HI_WDT_REG_SIZE                   (SZ_4K)


/* UART0 */
#define HI_UART0_REGBASE_ADDR             (0xE0203000)
#define HI_UART0_REG_SIZE                 (SZ_4K)

/* EDMA CH16 */
#define HI_EDMA_REGBASE_ADDR              (0xE0204000)
#define HI_EDMA_REG_SIZE                  (SZ_4K)

/* DramTest/ASHB */
#define HI_ASHB_REGBASE_ADDR              (0xE0205000)
#define HI_ASHB_REG_SIZE                  (SZ_4K)

/* UICC */
#define HI_UICC_REGBASE_ADDR              (0xE0400000)
#define HI_UICC_REG_SIZE                  (SZ_256K)

/* CICOM0 */
#define HI_CICOM0_REGBASE_ADDR            (0xE0440000)
#define HI_CICOM0_REG_SIZE                (SZ_64K)

/* CICOM1 */
#define HI_CICOM1_REGBASE_ADDR            (0xE0450000)
#define HI_CICOM1_REG_SIZE                (SZ_64K)

/* CIPHER */
#define HI_CIPHER_BASE_ADDR               (0xE0470000)
#define HI_CIPHER_REG_SIZE                (SZ_4K)

/* UPACC */
#define HI_UPACC_BASE_ADDR                (0xE0471000)
#define HI_UPACC_REG_SIZE                 (SZ_4K)

/* todo: HDLC */
#define HI_HDLC_REGBASE_ADDR              (0x0)
#define HI_HDLC_REG_SIZE                  (SZ_64K)

/* IPF */
#define HI_IPF_REGBASE_ADDR               (0xE0472000)
#define HI_IPF_REG_SIZE                   (SZ_4K)

/* HS UART */
#define HI_HSUART_REGBASE_ADDR            (0xE0473000)
#define HI_HSUART_REG_SIZE                (SZ_4K)

/* BBE16 VIC */
#define HI_BBE16VIC_REGBASE_ADDR          (0xE0474000)
#define HI_BBE16VIC_REG_SIZE              (SZ_4K)

/* IPCM */
#define HI_IPCM_REGBASE_ADDR              (0xFDF21000)
#define HI_IPCM_REG_SIZE                  (SZ_4K)

/* AP IPC*/
#define HI_IPC_S_REGBASE_ADDR             (0xE8610000)
#define HI_IPC_S_REG_SIZE                 (SZ_4K)

/* todo: AMON_CPUSLOW */
#define HI_AMON_SOC_REGBASE_ADDR          (0xE0476000)
#define HI_AMON_SOC_REG_SIZE              (SZ_16K)

/* todo: AMON_CPUFAST */
#define HI_AMON_CPUFAST_REGBASE_ADDR      (0xE0476000)
#define HI_AMON_CPUFAST_REG_SIZE          (SZ_16K)

/* SRAM(AXI memroy) */
#define HI_SRAM_MEM_BASE_ADDR               (DRV_SRAM_ADDR)
#define HI_SRAM_MEM_SIZE                    (DRV_SRAM_SIZE)

/* dsp subsystem */
#define HI_DSP_SUBSYSTEM_BASE_ADDR        (0xE1000000)
#define HI_DSP_SUBSYSTEM_SIZE             (SZ_32M)

#define HI_BBP_UL_BASE_ADDR               (0xE1600000)
#define HI_BBP_UL_SIZE                    (SZ_1M)

#define HI_BBE16DMEM_BASE_ADDR            (0xE2780000)
#define HI_BBE16DMEM_SIZE                 (SZ_512K)

#define HI_BBE16IMEM_BASE_ADDR            (0xE2800000)
#define HI_BBE16IMEM_SIZE                 (SZ_512K)

/* Sec RAM */
#define HI_SECRAM_BASE_ADDR               (0xE8000000)
#define HI_SECRAM_SIZE                    (SZ_256K)

/* PMUSSI0 */
#define HI_PMUSSI0_REGBASE_ADDR           (0xFFF34000)
#define HI_PMUSSI0_REG_SIZE               (SZ_4K)

/* Tsensor */
#define HI_TSENSOR_REGBASE_ADDR           (0xFFF30000)
#define HI_TSENSOR_REG_SIZE               (SZ_4K)

/* MDDRC */
#define HI_MDDRC_REGBASE_ADDR             (0xFFF20000)
#define HI_MDDRC_REG_SIZE                 (SZ_64K)

/* efusec */
#define HI_EFUSE_REGBASE_ADDR             (0xFFF10000)
#define HI_EFUSE_REG_SIZE                 (SZ_4K)

/*SCI1*/
#define HI_SCI1_REGBASE_ADDR              (0xFFF07000)
#define HI_SCI1_REG_SIZE                  (SZ_4K)

/*SCI0*/
#define HI_SCI0_REGBASE_ADDR              (0xFFF06000)
#define HI_SCI0_REG_SIZE                  (SZ_4K)

/* RTC1 */
#define HI_RTC1_BASE_ADDR                 (0xFFF05000)
#define HI_RTC1_SIZE                      (SZ_4K)

/* RTC0 */
#define HI_RTC0_BASE_ADDR                 (0xFFF04000)
#define HI_RTC0_SIZE                      (SZ_4K)

/* todo: CS_SYS */
#define HI_CS_SYS_REGBASE_ADDR            (0xFFF00000)
#define HI_CS_SYS_REG_SIZE                (SZ_1M)

/* todo: NANDC reg */
#define HI_NANDC_REGBASE_ADDR             (0xFFFA0000)
#define HI_NANDC_REG_SIZE                 (SZ_128K)

/* todo: NANDC buffer */
#define HI_NAND_MEM_BUFFER_ADDR           (0xFFF80000)
#define HI_NAND_MEM_BUFFER_SIZE           (SZ_128K)

/* todo: DDR */
#define HI_DDR_BASE_ADDR                  (0x30000000)
#define HI_DDR_SIZE                       (SZ_128M)

/* shared  DDR */
#define HI_SHARED_DDR_BASE_ADDR           (DDR_SHARED_MEM_ADDR)
#define HI_SHARED_DDR_SIZE                (DDR_SHARED_MEM_SIZE)

/* BOOTROM */
#define HI_BOOTROM_REGBASE_ADDR           (0xFFF60000)
#define HI_BOOTROM_REG_SIZE               (SZ_64K)

/* LP M3 TCM */
/* M3 TCM1 only valid in LPMCU. PD region*/
#define HI_M3TCM1_MEM_ADDR                (0xFFF50000)
#define HI_M3TCM1_MEM_SIZE                (SZ_32K)

/* M3 TCM0 only valid in LPMCU. AO region*/
#define HI_M3TCM0_MEM_ADDR                (0xFFF40000)
#define HI_M3TCM0_MEM_SIZE                (SZ_64K)

/*******************************************************************************/
#define HI_ZSP_AHB_REG_BASE_ADDR              0xFFFFFFFF            /* not found */
#define HI_ZSP_DTCM_REG_BASE_ADDR             0xFFFFFFFF            /* not found */

/*******************************************************************************/

/*****************************BBP BEGIN*****************************************/
/*tl*/
#define HI_BBP_SRC_BASE_ADDR                  (0xE1000000)
#define HI_BBP_SRC_SIZE                        SZ_1M

#define HI_BBP_DMA_BASE_ADDR                  (0xE1200000)
#define HI_BBP_DMA_SIZE                        SZ_1M

#define HI_BBP_DBG_BASE_ADDR                  (0xE1300000)
#define HI_BBP_DBG_SIZE                        SZ_1M

#define HI_BBP_INT_BASE_ADDR                  (0xE1700000)
#define HI_BBP_INT_SIZE                        SZ_4K

#define HI_BBP_STU_BASE_ADDR                  (0xE170e000)
#define HI_BBP_STU_SIZE                        SZ_4K

#define HI_BBP_TSTU_BASE_ADDR                 (0xE1d00000)
#define HI_BBP_TSTU_SIZE                       SZ_8K
/*gu*/
#define HI_GBBP_REG_BASE_ADDR                 (0xE1800000)
#define HI_GBBP_REG_SIZE                       SZ_512K

#define HI_GBBP1_REG_BASE_ADDR	              (0xE1880000)
#define HI_GBBP1_REG_SIZE                      SZ_512K

#define HI_WBBP_REG_BASE_ADDR                 (0xE1900000)
#define HI_WBBP_REG_REG_SIZE                   SZ_1M

#define HI_BBP_CDMA_BASE_ADDR                 (0xE19E0000)
#define HI_BBP_GSDR_BASE_ADDR                 (0xE19E0000)

#define HI_CTU_SIZE                            SZ_32K
#if defined(BSP_CONFIG_BOARD_SFT)&&defined(BSP_CONFIG_HI3650)
/*tl*/
#ifdef  FEATURE_MULTIMODE_GUL
#define HI_CTU_BASE_ADDR                      (0xE1820000)
#else
#define HI_CTU_BASE_ADDR                      (0xE1f80000)
#endif

#define HI_BBP_LTEDRX_BASE_ADDR               (0xE1F90000)

#define HI_BBP_TDSDRX_BASE_ADDR               (0xE19F3400)

/*gu*/
#define HI_BBP_COMM_ON_BASE_ADDR              (0xE1832000)

#define HI_GBBP_DRX_REG_BASE_ADDR             (0xE1812800)

#define HI_GBBP1_DRX_REG_BASE_ADDR	          (0xE1892C00)

#define HI_WBBP_DRX_REG_BASE_ADDR	          (0xE19A2000)

#define HI_BBP_CDMA_ON_BASE_ADDR              (0xE19F2000)

#define HI_BBP_GLB_ON_BASE_ADDR               (0xE19F2000)

#else
/*tl*/
#define HI_CTU_BASE_ADDR                      (0xE1f80000)

#define HI_BBP_LTEDRX_BASE_ADDR               (0xFFF12000)

#define HI_BBP_TDSDRX_BASE_ADDR               (0xFFF13400)

/*gu*/
#define HI_BBP_COMM_ON_BASE_ADDR              (0xFFF12000)

#define HI_GBBP_DRX_REG_BASE_ADDR             (0xFFF12800)

#define HI_GBBP1_DRX_REG_BASE_ADDR	          (0xFFF12C00)

#define HI_WBBP_DRX_REG_BASE_ADDR	          (0xFFF12000)

#define HI_BBP_CDMA_ON_BASE_ADDR              (0xFFF12000)

#define HI_BBP_GLB_ON_BASE_ADDR               (0xFFF12000)

#endif

#define HI_BBP_CTU_BASE_ADDR                  HI_CTU_BASE_ADDR
#define HI_BBPMASTER_REG_BASE_ADDR            HI_WBBP_REG_BASE_ADDR
/*****************************BBP END*****************************************/

/* CoreSignt Core1 PTM */
#define HI_CORESIGHT_PTM1_BASE_ADDR          0xffefc000
#define HI_CORESIGHT_PTM1_SIZE               SZ_4K

/* CoreSignt FUNNEL */
#define HI_CORESIGHT_FUNNEL_BASE_ADDR        0xffec1000
#define HI_CORESIGHT_FUNNEL_SIZE             SZ_4K

#if defined(BSP_CONFIG_BOARD_SFT)&&defined(BSP_CONFIG_HI3650)
#define HI_ABB_REG_BASE_ADDR                  (0xE19CC000)
#else
#define HI_ABB_REG_BASE_ADDR                  (0xE1F8C000)
#endif
#define HI_ABB_REG_SIZE                       (0x2000)

#if defined(BSP_CONFIG_BOARD_SFT)&&defined(BSP_CONFIG_HI3650)
#define HI_BBP_SYSTIME_BASE_ADDR              (0xFFF08000)
#else
#define HI_BBP_SYSTIME_BASE_ADDR              (HI_AP_SYSCTRL_BASE_ADDR)
#endif
#define HI_BBP_SYSTIME_SIZE                    SZ_8K

#define HI_XG2RAM_HARQ_BASE_ADDR              (0xEA000000)

#ifdef __cplusplus
}
#endif

#endif    /* __SOC_MEMMAP_COMM_H__ */

