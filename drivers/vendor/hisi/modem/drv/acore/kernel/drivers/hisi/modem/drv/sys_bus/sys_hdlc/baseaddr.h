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

#ifndef __BASEADDR_H
#define __BASEADDR_H

#include <soc_memmap.h>
#include <bsp_shared_ddr.h>
#include "basicfunc.h"
////////////////////////
// TEST MODULE SELECT //
////////////////////////
//#define A13_PLATFORM
//#define A19_PLATFORM
//#define V3_PLATFORM
//#define V3R2_PLATFORM

////////////////////////
// DEBUG INFO DISPLAY //
////////////////////////
//#define _UNIT_DEBUG

////////////////////////
// TEST MODULE SELECT //
////////////////////////
#define CEVATEST
#define CEVAL2SRAMTEST
//#define CICOMV200TEST
//#difine CICOMV300TEST
#define COMMTEST
//#define DMTEST
#define EDMACTEST
//#define HDLCTEST
#define SMIMTEST
//#define UPACCTEST
#define XDMACTEST
//#define BalongB030
//#define K3V3_FPGA

#ifdef K3V3_FPGA
#define UPACC_BASEADDR              HI_UPACC_BASE_ADDR
#define CICOM_BASEADDR              HI_CICOM0_REGBASE_ADDR
#define CICOM2_BASEADDR             HI_CICOM1_REGBASE_ADDR
#define SYSCTRL_BASEADDR            HI_SYSCTRL_BASE_ADDR
#define SYSCTRL_SCMISCCTRL          HI_SYSCTRL_BASE_ADDR + 0x410
#define SYSCTRL_CRG                   HI_SYSCTRL_BASE_ADDR+0X64
#define SYSCTRL_CRG_VALUE                  0xFFFFFFFF
#define Cicom_sel                   0
#endif
#ifdef P531_FPGA
#define SYSCTRL_CRG                   HI_SYSCTRL_BASE_ADDR+0X64
#define SYSCTRL_CR_VALUE                  0x1F80000/*关闭软复位请求*/
#define UPACC_BASEADDR              0x90135000 
//#define DDR_BASEADDR                0x50000000 

#define SYSCTRL_BASEADDR            0x90000000
#define HDLC_BASEADDR               0x90120000


#define MDDRC_BASEADDR              0x90020000
#define EDMAC_BASEADDR              0x90024000 
//#define HSSPI_BASEADDR              0x90182000//

#define NANDC_BASEADDR              0xA0000000
//#define SRAM0_BASEADDR              0x4FE00000 //暂时用AXI MEMEOY
#define EFUSE_BASEADDR              0x90021000 
#define BOOTROM_BASEADDR            0x90140000 

//#define ZSPITCM_BASEADDR            0x20000000 //
//#define ZSPDTCM_BASEADDR            0x20100000
//#define WBBP_BASEADDR               0x9002C000 //to be confirmed
//#define SMIM_BASEADDR               0x20300000 //
#define MDDR_BASEADDR               0x50000000 //
#define CICOM_BASEADDR              0x90110000
#define CICOM2_BASEADDR             0x90100000
//#define DMOVE_BASEADDR              0xffff0000 //

#define SYSCTRL_SCMISCCTRL          0x90000410
#define Cicom_sel                   0
#define DMAV300_BASEADDR            EDMAC_BASEADDR

#define SRAM_BASEADDR                 0x50000000  

#endif /*__BASEADDR_H*/

#define P530_DEBUG
#endif

#ifdef BSP_CONFIG_V721_PORTING
#define SYSCTRL_CRG                   HI_SYSCTRL_BASE_ADDR+0X64
#define SYSCTRL_CR_VALUE                  0x1F80000/*关闭软复位请求*/
#define UPACC_BASEADDR              HI_UPACC_BASE_ADDR 

#define SYSCTRL_BASEADDR            HI_SYSCTRL_BASE_ADDR
#define HDLC_BASEADDR               HI_HDLC_REGBASE_ADDR


#define MDDRC_BASEADDR              HI_MDDRC_REGBASE_ADDR
#define EDMAC_BASEADDR              HI_EDMA_REGBASE_ADDR 

#define NANDC_BASEADDR              HI_NANDC_REGBASE_ADDR
#define EFUSE_BASEADDR              HI_EFUSE_REGBASE_ADDR 
#define BOOTROM_BASEADDR            HI_BOOTROM_REGBASE_ADDR 

#define MDDR_BASEADDR               0x50000000 //
#define CICOM_BASEADDR              HI_CICOM0_REGBASE_ADDR
#define CICOM2_BASEADDR             HI_CICOM1_REGBASE_ADDR

#define SYSCTRL_SCMISCCTRL          HI_SYSCTRL_BASE_ADDR + 0x410
#define Cicom_sel                   0
#define DMAV300_BASEADDR            EDMAC_BASEADDR

#define SRAM_BASEADDR                 SRAM_GU_MAC_HEADER_ADDR  

#endif
#ifdef BSP_CONFIG_V711_PORTING
#define SYSCTRL_CRG                   HI_SYSCTRL_BASE_ADDR+0X64
#if 0
#define SYSCTRL_CR_VALUE                  0x1F80000/*关闭软复位请求*/
#endif
#define UPACC_BASEADDR              HI_UPACC_BASE_ADDR 

#define SYSCTRL_BASEADDR            HI_SYSCTRL_BASE_ADDR
#define HDLC_BASEADDR               HI_HDLC_REGBASE_ADDR


#define MDDRC_BASEADDR              HI_MDDRC_REGBASE_ADDR
#define EDMAC_BASEADDR              HI_EDMA_REGBASE_ADDR 

#define NANDC_BASEADDR              HI_NANDC_REGBASE_ADDR
#define EFUSE_BASEADDR              HI_EFUSE_REGBASE_ADDR 
#define BOOTROM_BASEADDR            HI_BOOTROM_REGBASE_ADDR 

#define CICOM_BASEADDR              HI_CICOM0_REGBASE_ADDR
#define CICOM2_BASEADDR             HI_CICOM1_REGBASE_ADDR

#define SYSCTRL_SCMISCCTRL          HI_SYSCTRL_BASE_ADDR + 0x410
#define Cicom_sel                   0
#define DMAV300_BASEADDR            EDMAC_BASEADDR

#define SRAM_BASEADDR                 SRAM_GU_MAC_HEADER_ADDR  
#define SYSCTRL_CRG_VALUE                  0xFFFFFFFF
#define Cicom_sel                   0


#endif
#ifdef BSP_CONFIG_HI6950
#define SYSCTRL_CRG                 HI_MODEM_SC_BASE_ADDR+0X24

#define UPACC_BASEADDR              HI_UPACC_BASE_ADDR 

#define HDLC_BASEADDR               HI_HDLC_REGBASE_ADDR


#define MDDRC_BASEADDR              HI_MDDRC_REGBASE_ADDR
#define EDMAC_BASEADDR              HI_EDMA_REGBASE_ADDR 

#define EFUSE_BASEADDR              HI_EFUSE_REGBASE_ADDR 

#define CICOM_BASEADDR              HI_CICOM0_REGBASE_ADDR
#define CICOM2_BASEADDR             HI_CICOM1_REGBASE_ADDR

#define SYSCTRL_SCMISCCTRL          HI_MODEM_SC_BASE_ADDR + 0x410
#define Cicom_sel                   0

#define SYSCTRL_CRG_VALUE           0xFFFFFFFF

#endif
/*hi6932*/
extern void * sys_bus_sysctrl_crg_addr;
#define SYSCTRL_CRG                 (UINT32)(sys_bus_sysctrl_crg_addr + 0x24)//HI_MODEM_SC_BASE_ADDR+0X24

//#define UPACC_BASEADDR              HI_UPACC_BASE_ADDR 
extern void * sys_bus_hdlc_base_addr;
#define HDLC_BASEADDR               (UINT32)sys_bus_hdlc_base_addr  //HI_HDLC_REGBASE_ADDR


//#define MDDRC_BASEADDR              HI_MDDRC_REGBASE_ADDR
//#define EDMAC_BASEADDR              HI_EDMA_REGBASE_ADDR 

//#define EFUSE_BASEADDR              HI_EFUSE_REGBASE_ADDR 

//#define CICOM_BASEADDR              HI_CICOM0_REGBASE_ADDR
//#define CICOM2_BASEADDR             HI_CICOM1_REGBASE_ADDR

//#define SYSCTRL_SCMISCCTRL          HI_MODEM_SC_BASE_ADDR + 0x410
//#define Cicom_sel                   0

#define SYSCTRL_CRG_VALUE           0xFFFFFFFF


#ifdef v7r2_porting_bsustress
#define NANDC_BASEADDR              0x900A4000	
#endif

//#define V9R1_DEBUG
//#define BalongV9R1BBIT

#ifdef BalongV9R1BBIT
#define P500_BASEADDR               0x00000000
#define BBP_BASEADDR                0x5E200000
#define SRAM0_BASEADDR              0x5E400000
#define SRAM1_BASEADDR              0x5E500000
#define VIC0_BASEADDR               0x5F000000
#define CICOM_BASEADDR              0x5F010000
#define VIC1_BASEADDR               0x5F020000
#define VIC2_BASEADDR               0x5F030000
#define UPACC_BASEADDR              0x5F040000
#define PeriCtrl_BASEADDR           0x5F050000
#define DTimer5_BASEADDR            0x5F051000
#define EDMAC_BASEADDR              0x5F052000
#define SOCP_BASEADDR               0x5F053000
#define IPC_BASEADDR                0x5F054000
#define I2C0_BASEADDR               0x5F055000
#define DTimer6_BASEADDR            0x5F056000
#define DTimer7_BASEADDR            0x5F057000
#define DTimer8_BASEADDR            0x5F058000
#define PMU_SSI0_BASEADDR           0x5F059000
#define PMU_SSI1_BASEADDR           0x5F05A000
#define SCI0_BASEADDR               0x5F060000
#define SSI0_BASEADDR               0x5F061000
#define SSI1_BASEADDR               0x5F062000
#define GPIO0_BASEADDR              0x5F063000
#define GPIO1_BASEADDR              0x5F064000
#define UART0_BASEADDR              0x5F065000
#define SCI1_BASEADDR               0x5F066000
#define DTimer0_BASEADDR            0x5F067000
#define DTimer1_BASEADDR            0x5F068000
#define DTimer2_BASEADDR            0x5F069000
#define DTimer3_BASEADDR            0x5F06A000
#define DTimer4_BASEADDR            0x5F06B000
#define Watchdog_BASEADDR           0x5F06C000
#define GPIO2_BASEADDR              0x5F06D000
#define GPIO3_BASEADDR              0x5F06E000
#define IPF_BASEADDR                0x5F0B0000
#define HDLC_BASEADDR               0x5F0C0000

#define ZSPITCM_BASEADDR            0x5E000000
#define ZSPDTCM_BASEADDR            0x5E100000
//#define CICOM_BASEADDR              0x50100000
#define PERICTRL_BASEADDR           0x5F050000
#define SMIM_BASEADDR               0x5E300000
//#define UPACC_BASEADDR              0x5E340000
#define ZDMAC_BASEADDR              0x5E380000
#define ONCHIPRAM_BASEADDR          0x5E400000
#define WBBP_BASEADDR               0x5E200000
#define GBBP_BASEADDR               0x5E210000
#define DMAV300_BASEADDR            0x5f052000
//#define EDMAC_BASEADDR              0x5f052000
#define DMOVE_BASEADDR              0x5f052000
//#define HDLC_BASEADDR               0x5f052000
#define IIC_BASEADDR                0xC2010000
#define EFUSE_BASEADDR              0x5F050000
#define HIFIDMEM_BASEADDR           0xC2010000
#define HIFIIMEM_BASEADDR           0xC2010000
#define ZSPDMEM_BASEADDR            0xC2010000

#define SYSCTRL_BASEADDR            0x5F050000
#define MDDR_BASEADDR               0xC2000000
#define SRAM_BASEADDR               0x5E400000



#define SYSCTRL_SCMISCCTRL          0x5F05003C
#define Cicom_sel                      0
#endif



#ifdef BalongV3R2SFT
#define ZSPIMEM_BASEADDR            0x20000000
#define ZSPDMEM_BASEADDR            0x20100000
#define IMI_BASEADDR                0x20200000
#define MAILBOX_BASEADDR            0x20300000
#define UPACC_BASEADDR              0x20340000
#define ZDMAC_BASEADDR              0x20380000
#define SIO0_BASEADDR               0x20390000

#define HIFIDMEM_BASEADDR           0x2BFF8000
#define HIFIIMEM_BASEADDR           0x2C000000
#define SRAM1_BASEADDR              0x2ffe0000
#define DDR_BASEADDR                0x30000000

#define SYSCTRL_BASEADDR            0x90000000
#define TIMER1_BASEADDR             0x90002000
#define TIMER2_BASEADDR             0x90003000
#define IOC_BASEADDR                0x90004000
#define RTC_BASEADDR                0x90005000
#define SCI_BASEADDR                0x90009000
#define WDT0_BASEADDR               0x9000D000
#define WDT1_BASEADDR               0x9000E000
#define WDT2_BASEADDR               0x9000F000
#define WDT3_BASEADDR               0x90010000
#define GPIO0_BASEADDR              0x90011000
#define GPIO1_BASEADDR              0x90012000
#define GPIO2_BASEADDR              0x90013000
#define GPIO3_BASEADDR              0x90014000
#define GPIO4_BASEADDR              0x90015000
#define GPIO5_BASEADDR              0x90016000
#define GPIO6_BASEADDR              0x90017000
#define GPIO7_BASEADDR              0x90018000
#define GPIO8_BASEADDR              0x90019000
#define GPIO9_BASEADDR              0x9001A000
#define GPIO10_BASEADDR             0x9001B000
#define GPIO11_BASEADDR             0x9001C000

#define UART0_BASEADDR              0x90020000
#define UART1_BASEADDR              0x90021000
#define UART2_BASEADDR              0x90022000
#define UART3_BASEADDR              0x90023000
#define SSP0_BASEADDR               0x90024000
#define SSP1_BASEADDR               0x90025000
#define TIMER0_BASEADDR             0x90026000
#define IIC_BASEADDR                0x90027000
#define UICC_BASEADDR               0x90040000
#define HSIC_BASEADDR               0x90080000
#define EMIREG_BASEADDR             0x900A2000
#define EMIMEM_BASEADDR             0x900A3000
#define IPC_BASEADDR                0x900A5000
#define HSUART_BASEADDR             0x900A8000
#define SOCP_BASEADDR               0x900A9000
#define MMC0_BASEADDR               0x900AD000
#define MMC1_BASEADDR               0x900AE000
#define MMC2_BASEADDR               0x900AF000
#define SDDC_BASEADDR               0x900B0000
#define SDDMA_BASEADDR              0x900B4000
#define USBOTG_BASEADDR             0x900C0000
#define CICOM0_BASEADDR             0x90100000
#define CICOM1_BASEADDR             0x90110000
#define HDLC_BASEADDR               0x90120000
#define ADMAC_BASEADDR              0x90130000
#define IPF_BASEADDR                0x90140000
#define SIO1_BASEADDR               0x90150000
#define SSI0_BASEADDR               0x90160000
#define SSI1_BASEADDR               0x90161000
#define SSI2_BASEADDR               0x90162000

#define MDDRC_BASEADDR              0x90180000
#define EDMAC_BASEADDR              0x90181000
#define HSSPI_BASEADDR              0x90182000

#define NANDC_BASEADDR              0xA0000000
#define SRAM0_BASEADDR              0xFFFD0000
#define EFUSE_BASEADDR              0xfffe0000
#define BOOTROM_BASEADDR            0xffff0000

#define ZSPITCM_BASEADDR            0x20000000
#define ZSPDTCM_BASEADDR            0x20100000
#define WBBP_BASEADDR               0x20200000
#define SMIM_BASEADDR               0x20300000
#define MDDR_BASEADDR               0x31000000
#define CICOM_BASEADDR              0x90110000
#define CICOM2_BASEADDR             0x90100000
#define DMOVE_BASEADDR              0xffff0000

#define SYSCTRL_SCMISCCTRL          0x900000DC
#define Cicom_sel        0
#define DMAV300_BASEADDR            EDMAC_BASEADDR
#endif

#ifdef BalongB030
#define ZSPITCM_BASEADDR            0x60000000
#define ZSPDTCM_BASEADDR            0x60100000
#define CICOM_BASEADDR              0x61010000
#define CICOM2_BASEADDR             0x61070000
#define PERICTRL_BASEADDR           0x61050000
#define SMIM_BASEADDR               0x60300000
#define UPACC_BASEADDR              0x60340000
#define ZDMAC_BASEADDR              0x60380000
#define ONCHIPRAM_BASEADDR          0x60400000
#define WBBP_BASEADDR               0x60200000
#define GBBP_BASEADDR               0x60210000

#define MDDR_BASEADDR               0xA0000000

#define SYSCTRL_SCMISCCTRL          0x61050040
#define Cicom_sel        0
#define DMAV300_BASEADDR           0x60012000
//for compile fail
#define DMOVE_BASEADDR             0x61010000
#define HDLC_BASEADDR              0x61010000
#define EDMAC_BASEADDR             0x60012000
#define HIFIIMEM_BASEADDR          0xa1234000
#define HIFIDMEM_BASEADDR          0xa1235000
#define ZSPDMEM_BASEADDR           0x60100000
#define SYSCTRL_BASEADDR           0xa1235000
#define IIC_BASEADDR               0xa1235000
#define EFUSE_BASEADDR             0xa1235000
#endif

#ifdef BalongB031
#define ZSPITCM_BASEADDR            0x5E000000
#define ZSPDTCM_BASEADDR            0x5E100000
#define CICOM_BASEADDR              0x5F010000
#define CICOM2_BASEADDR             0x5F070000
#define PERICTRL_BASEADDR           0x5F050000
#define SMIM_BASEADDR               0x5E300000
#define UPACC_BASEADDR              0x5E340000
#define ZDMAC_BASEADDR              0x5E380000
#define ONCHIPRAM_BASEADDR          0x5E400000
#define WBBP_BASEADDR               0x5E200000
#define GBBP_BASEADDR               0x5E210000

#define MDDR_BASEADDR               0xC2000000

#define SYSCTRL_SCMISCCTRL          0x5F050040
#define Cicom_sel        0
#endif

#ifdef BalongU020
#define ZSPITCM_BASEADDR            0x60040000
#define ZSPDTCM_BASEADDR            0x60040000
#define CICOM_BASEADDR              0x60040000
#define CICOM2_BASEADDR             0x60040000
#define PERICTRL_BASEADDR           0x60000000
#define SMIM_BASEADDR               0x61000000
#define UPACC_BASEADDR              0x60340000
#define ZDMAC_BASEADDR              0x60380000
#define ONCHIPRAM_BASEADDR          0x60400000
#define WBBP_BASEADDR               0x60040000
#define GBBP_BASEADDR               0x60040000
#define DMAV300_BASEADDR           0x60012000

#define MDDR_BASEADDR               0xA0000000

#define SYSCTRL_SCMISCCTRL          0x61050040
#define Cicom_sel        0
#endif
#define DMOVE2_BASEADDR             0x60030000

#ifdef CICOMV200TEST
#define CICOM_BASEADDR              0x30040000
#endif

#ifdef HICICOMV300
#define CICOM_BASEADDR              0x60000000
#endif

#ifdef A13_PLATFORM
//Fast APB Bus
#define DTMR4_BASEADDR              0x21000000
#define SYSCTRL_BASEADDR            0x21001000
#define IOC_BASEADDR                0x21002000
#define MDDRCREG_BASEADDR           0x21003000
#define EDMAC_BASEADDR              0x21005000
#define VIC_BASEADDR                0x21010000
//Slow APB Bus
#define SCI_BASEADDR                0x21020000
#define SSI_A_BASEADDR              0x21021000
#define SPI_A_BASEADDR              0x21022000
#define UART_A_BASEADDR             0x21023000
#define GPIO0_BASEADDR              0x21024000
#define GPIO1_BASEADDR              0x21025000
#define GPIO2_BASEADDR              0x21026000
#define GPIO3_BASEADDR              0x21027000
#define I2C_BASEADDR                0x21028000
#define I2C1_BASEADDR                0x21028000
#define DTMR0_BASEADDR              0x21029000
#define DTMR1_BASEADDR              0x2102A000
#define DTMR2_BASEADDR              0x2102B000
#define DTMR3_BASEADDR              0x2102C000
#define WDOG_A_BASEADDR             0x2102D000
#define WDOG_C_BASEADDR             0x2102E000
#define RTC_BASEADDR                0x2102F000
//AHB Local Bus
#define DMOVE_BASEADDR              0x30000000
#define USBDC_BASEADDR              0x30010000
#define MMC_BASEADDR                0x30020000
#define HDMACREG_BASEADDR           0x30030000
//#define CICOM_BASEADDR              0x30040000
#define HDLC_BASEADDR               0x30080000
#define NANDC_BASEADDR              0x30100000
//ARMSS SRAM
#define MIFA_BASEADDR               0x32000000
//CEVASS 
#define CEVADTCM_BASEADDR           0x40000000
#define XDMA_BASEADDR               0x40100000
//EXT APB Bus
#define SSI_C_BASEADDR              0x40110000
#define SPI_C_BASEADDR              0x40111000
#define UART_C_BASEADDR             0x40112000
//HIAPB Bus
#define CEVA_PMU_BASEADDR           0x40130000
#define CEVA_ICU_BASEADDR           0x40130400
#define CEVA_TMR0_BASEADDR          0x40130800
#define CEVA_TMR1_BASEADDR          0x40130C00
#define CEVA_GPIO_BASEADDR          0x40131000
#define CEVA_CRU_BASEADDR           0x40131400
#define CEVA_PIU_BASEADDR           0x40132000
#define CEVA_L2SRAM0_BASEADDR       0x40200000
#define CEVA_L2SRAM1_BASEADDR       0x40400000
//AHB EXT Bus
//#define UPACC_BASEADDR            0x40600000
//#define SMIM_BASEADDR             0x40640000
#define SIO_BASEADDR              0x40680000
//MEMORY
//#define MDDR_BASEADDR               0xA0000000
//FPGA ARM AXI
//#define WBBP_BASEADDR               0x60700000
//#define GBBP_BASEADDR               0x60710000
#define WBBP_DRX_BASEADDR           0x60720000
#define GBBP_DRX_BASEADDR           0x60730000
#define FPGA_VIC_BASEADDR           0x60740000
//#define PERICTRL_BASEADDR           0x60750000
#define FPGA_SSI0_BASEADDR          0x60751000
#define FPGA_SSI1_BASEADDR          0x60752000
#define FPGA_GPIO0_BASEADDR         0x60753000
#define FPGA_GPIO1_BASEADDR         0x60754000
#define FPGA_UART_BASEADDR          0x60755000
#define FPGA_I2C_BASEADDR           0x60756000
#define FPGA_SIO_BASEADDR           0x60760000
//FPGA CEVA AHB
#define WBBP_CEVA_BASEADDR               0x40700000
#define GBBP_CEVA_BASEADDR               0x40710000
#define WBBP_DRX_CEVA_BASEADDR           0x40720000
#define GBBP_DRX_CEVA_BASEADDR           0x40730000
//CEVA BASEADDR
#define CEVADTCM_CEVA_BASEADDR           0x00000000
#define CEVA_L2SRAM0_CEVA_BASEADDR       0x00200000
#define CEVA_L2SRAM1_CEVA_BASEADDR       0x00400000

#endif



