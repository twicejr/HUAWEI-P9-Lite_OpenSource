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
#ifndef __HI6403_DSP_REGS_H__
#define __HI6403_DSP_REGS_H__
#include "hi64xx_dsp_regs.h"
#define HI6403_DSP_I2S_DSPIF_CLK_EN 	   (HI64xx_DSP_SCTRL_BASE + 0x0F0)

#define HI6403_CFG_REG_CLK_CTRL			   (BASE_ADDR_PAGE_CFG + 0x038)
#define HI6403_DSP_CTRL6_DMAC		(BASE_ADDR_PAGE_CFG + 0x054)
#define HI6403_DSP_LP_CTRL1				   (BASE_ADDR_PAGE_CFG + 0x082)

#define HI6403_DSP_CMD_BASE				   (0x10000000 + 0xFA00)
#define HI6403_DSP_CMD0 				   (HI6403_DSP_CMD_BASE)
/* use for notify DSP PLL status */
#define HI6403_DSP_CMD1 				   (HI6403_DSP_CMD_BASE + 0x004)
#define HI6403_DSP_CMD2 				   (HI6403_DSP_CMD_BASE + 0x008)
/* use for notify soundtrigger event */
#define HI6403_DSP_CMD3 				   (HI6403_DSP_CMD_BASE + 0x00C)

#define HI6403_PARA_ADDR 0x10007D00
#define HI6403_MSG_ADDR 0x10011D00
#endif