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
#ifndef __HI64xx_DSP_REGS_H__
#define __HI64xx_DSP_REGS_H__
#include "hi64xx_regs.h"
extern uint64_t soc_dma_vir;

#define IMAGE_DOWN_MEM_SIZE 				524288
#define IMAGEDOWN_SIZE_THRESH				1000

#define SLIMBUS_PORT12_ADDR 				0xe8051300
#define ASP_DMAC_BASE_ADDR					0xe804b000
#define ASP_DMAC_SIZE						0x1000

#define ASP_DMAC_CX_CNT0(ch)			(void __iomem *)((soc_dma_vir) + 0x810 + 0x40 * (ch))
#define ASP_DMAC_CX_SRC_ADDR(ch)		(void __iomem *)((soc_dma_vir) + 0x814 + 0x40 * (ch))
#define ASP_DMAC_CX_DES_ADDR(ch)		(void __iomem *)((soc_dma_vir) + 0x818 + 0x40 * (ch))
#define ASP_DMAC_CX_CONFIG(ch)			(void __iomem *)((soc_dma_vir) + 0x81C + 0x40 * (ch))

#define ASP_DMAC_STAT               		(void __iomem *)((soc_dma_vir) + 0x690)
#define ASP_DMAC_CX_CURR_CNT0(ch)			(void __iomem *)((soc_dma_vir) + 0x704 + 0x10 * (ch))
#define ASP_DMAC_CX_CURR_SRC_ADDR(ch)		(void __iomem *)((soc_dma_vir) + 0x708 + 0x10 * (ch))
#define ASP_DMAC_CX_CURR_DES_ADDR(ch)		(void __iomem *)((soc_dma_vir) + 0x70C + 0x10 * (ch))

#define HI64xx_DSP_IF6_ADDR 				0x20016000
#define HI64xx_DMA_CONFIG_OFFSET			0x40
#define HI64xx_DMA_STATUS_OFFSET			0x10

#define HI64xx_DSP_EDMA_BASE				0x20000000
#define HI64xx_DSP_IOSHARE_BASE 			0x20001000
#define HI64xx_DSP_WATCHDOG_BASE			0x20002000
#define HI64xx_DSP_SCTRL_BASE				0x20003000
#define HI64xx_DSP_UART_BASE				0x20004000
#define HI64xx_CFG_SUB_BASE 				0x20007000
#define HI64xx_AUDIO_SUB_BASE				0x20007200
#define HI64xx_GPIO0_BASE					0x20008000
#define HI64xx_OCRAM1_BASE					0x10046340
#define HI64xx_MSG_START_ADDR_OFFSET		0xA000

#define HI64xx_CODE_CORE_BASE			   (HI64xx_CFG_SUB_BASE + 0x200)
#define HI64xx_MLIB_TO_AP_MSG_ADDR		  (HI64xx_OCRAM1_BASE + 0x19874)
#define HI64xx_MLIB_TO_AP_MSG_LEN			(588)
#define UCOM_PROTECT_WORD			   (0x5A5A5A5A)

#define HI64xx_TCM_START_ADDR			   (0x08000000)
#define HI64xx_TCM_SIZE 				   (0x25000)
#define HI64xx_OCRAM_START_ADDR 		   (0x10000000)
#define HI64xx_OCRAM_SIZE				   (0x60000)
#define HI64xx_REG_SIZE 				   (HI64xx_CFG_SUB_SIZE + HI64xx_AUDIO_SUB_SIZE \
											+ HI64xx_DSP_EDMA_SIZE1 + HI64xx_DSP_EDMA_SIZE2)
#define HI64xx_CFG_SUB_SIZE 			   (0x100)
#define HI64xx_AUDIO_SUB_SIZE			   (0x200)
#define HI64xx_DSP_EDMA_SIZE1			   (0x30)
#define HI64xx_DSP_EDMA_SIZE2			   (0x300)

#define HI64XX_1BYTE_SUB_START			0x20007000
#define HI64XX_1BYTE_SUB_END			0x20007FFF

/* 0x20000000 */
#define HI64xx_DMA_CH_STAT			       (HI64xx_DSP_EDMA_BASE + 0x690)
#define HI64xx_CX_CURR_CNT0(ch) 			   (HI64xx_DSP_EDMA_BASE + 0x704 + 0x10 * (ch))
#define HI64xx_CX_CURR_SRC_ADDR(ch) 		   (HI64xx_DSP_EDMA_BASE + 0x708 + 0x10 * (ch))
#define HI64xx_CX_CURR_DES_ADDR(ch) 		   (HI64xx_DSP_EDMA_BASE + 0x70C + 0x10 * (ch))

#define HI64xx_CX_CNT0(ch)				   (HI64xx_DSP_EDMA_BASE + 0x810 + 0x40 * (ch))
#define HI64xx_CX_SRC_ADDR(ch)			   (HI64xx_DSP_EDMA_BASE + 0x814 + 0x40 * (ch))
#define HI64xx_CX_DES_ADDR(ch)			   (HI64xx_DSP_EDMA_BASE + 0x818 + 0x40 * (ch))
#define HI64xx_CX_CONFIG(ch)			   (HI64xx_DSP_EDMA_BASE + 0x81C + 0x40 * (ch))

/* 0x20002000 */
#define HI64xx_DSP_WATCHDOG_LOCK		   (HI64xx_DSP_WATCHDOG_BASE + 0xC00)
#define HI64xx_DSP_WATCHDOG_CONTROL 	   (HI64xx_DSP_WATCHDOG_BASE + 0x008)

/* 0x20003000 */
#define HI64xx_DSP_SUB_CMD_STATUS		   (HI64xx_DSP_SCTRL_BASE +0x008)

/* 0x20004000 */
#define HI64xx_DSP_UART_RBR_THR_DLL 	   (HI64xx_DSP_UART_BASE + 0x000)
#define HI64xx_DSP_UART_DLH_IER 		   (HI64xx_DSP_UART_BASE + 0x004)
#define HI64xx_DSP_UART_IIR_FCR 		   (HI64xx_DSP_UART_BASE + 0x008)
#define HI64xx_DSP_UART_LCR 			   (HI64xx_DSP_UART_BASE + 0x00C)

/* 0x20008000 */
#define HI64xx_GPIO0_DATA_ch5			   (HI64xx_GPIO0_BASE + 0x080)
#define HI64xx_GPIO0_DIR				   (HI64xx_GPIO0_BASE + 0x400)
#define HI64xx_GPIO0_IS 				   (HI64xx_GPIO0_BASE + 0x404)
#define HI64xx_GPIO0_IBE				   (HI64xx_GPIO0_BASE + 0x408)
#define HI64xx_GPIO0_IEV				   (HI64xx_GPIO0_BASE + 0x40c)
#define HI64xx_GPIO0_RIS				   (HI64xx_GPIO0_BASE + 0x414)
#define HI64xx_GPIO0_IE2				   (HI64xx_GPIO0_BASE + 0x500)
#define HI64xx_GPIO0_MIS2				   (HI64xx_GPIO0_BASE + 0x530)
/* for dump */
/* 0x20007000 ~ 0x20007037 */
#define HI64xx_DUMP_CFG_SUB_ADDR1		HI64xx_CFG_SUB_BASE
#define HI64xx_DUMP_CFG_SUB_SIZE1		0x38
/* 0x2000703A ~ 0x200070A0 */
#define HI64xx_DUMP_CFG_SUB_ADDR2		(HI64xx_CFG_SUB_BASE + 0x3A)
#define HI64xx_DUMP_CFG_SUB_SIZE2		0x67
/* 0x20007200 ~ 0x200073FF */
#define HI64xx_DUMP_AUDIO_SUB_ADDR		HI64xx_AUDIO_SUB_BASE
#define HI64xx_DUMP_AUDIO_SUB_SIZE		0x200
/* 0x20000000 ~ 0x20000028 */
#define HI64xx_DUMP_DSP_EDMA_ADDR1		HI64xx_DSP_EDMA_BASE
#define HI64xx_DUMP_DSP_EDMA_SIZE1		0x2C
/* 0x20000600 ~ 0x2000069C */
#define HI64xx_DUMP_DSP_EDMA_ADDR2		(HI64xx_DSP_EDMA_BASE + 0x600)
#define HI64xx_DUMP_DSP_EDMA_SIZE2		0xA0
/* 0x20000700 ~ 0x20000BDC */
#define HI64xx_DUMP_DSP_EDMA_ADDR3		(HI64xx_DSP_EDMA_BASE + 0x700)
#define HI64xx_DUMP_DSP_EDMA_SIZE3		0x4E0
/* 0x20002000 ~ 0x20002008 */
#define HI64xx_DUMP_DSP_WATCHDOG_ADDR1		HI64xx_DSP_WATCHDOG_BASE
#define HI64xx_DUMP_DSP_WATCHDOG_SIZE1		0xC
/* 0x20002010 ~ 0x20002014 */
#define HI64xx_DUMP_DSP_WATCHDOG_ADDR2		(HI64xx_DSP_WATCHDOG_BASE + 0x10)
#define HI64xx_DUMP_DSP_WATCHDOG_SIZE2		0x8
/* 0x20003000 ~ 0x20003018 */
#define HI64xx_DUMP_DSP_SCTRL_ADDR1		HI64xx_DSP_SCTRL_BASE
#define HI64xx_DUMP_DSP_SCTRL_SIZE1		0x1C
/* 0x20003100 ~ 0x2000311C */
#define HI64xx_DUMP_DSP_SCTRL_ADDR2		(HI64xx_DSP_SCTRL_BASE + 0x100)
#define HI64xx_DUMP_DSP_SCTRL_SIZE2		0x20
/* 0x20007038 ~ 0x20007039 */
#define HI64xx_DUMP_CFG_SUB_ADDR3		(HI64xx_CFG_SUB_BASE + 0x38)
#define HI64xx_DUMP_CFG_SUB_SIZE3		0x2

#endif/*__HI64xx_DSP_REGS_H__*/