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
#ifndef __HI6402_DSP_REGS_H__
#define __HI6402_DSP_REGS_H__
#include "hi64xx_dsp_regs.h"
#define HI6402_DSP_I2S_DSPIF_CLK_EN 	   (BASE_ADDR_PAGE_CFG + 0x045)

#define HI6402_DSP_CMD0 				   (BASE_ADDR_PAGE_CFG + 0x070)
/* use for notify DSP PLL status */
#define HI6402_DSP_CMD1 				   (BASE_ADDR_PAGE_CFG + 0x071)
#define HI6402_DSP_CMD2 				   (BASE_ADDR_PAGE_CFG + 0x072)

/* APB CLK */
#define HI6402_APB_CLK_CFG_REG		(BASE_ADDR_PAGE_CFG + 0x053)
#define HI6402_PERI_CLK_SEL_BIT			7
#define HI6402_APB_CLK_EN_BIT			0

#define HI6402_UART_MODE				   (HI6402_DSP_CMD2)
/* use for notify soundtrigger event */
#define HI6402_DSP_CMD3 				   (BASE_ADDR_PAGE_CFG + 0x073)

#define HI6402_MSG_ADDR (HI64xx_OCRAM1_BASE + HI64xx_MSG_START_ADDR_OFFSET)
#define HI6402_PARA_ADDR (HI64xx_OCRAM1_BASE)

#define HI6402_CFG_SW_ENTER 1
#define HI6402_CFG_SW_EXIT 0
#endif