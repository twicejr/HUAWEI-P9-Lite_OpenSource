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
#ifndef __HI64XX_DSP_DEBUG_H__
#define __HI64XX_DSP_DEBUG_H__

extern unsigned long hi64xx_dsp_debug_level;

#define HI64XX_DSP_ERROR(msg, ...)	  \
	do {						  \
		if (hi64xx_dsp_debug_level > 0)  \
			printk(KERN_ERR "[hi64xx-dsp]%s: "msg, __func__, ## __VA_ARGS__); \
	   } while (0)

#define HI64XX_DSP_WARNING(msg, ...)	\
	do {						  \
		if (hi64xx_dsp_debug_level > 1)  \
			printk(KERN_WARNING "[hi64xx-dsp]%s: "msg, __func__, ## __VA_ARGS__); \
	   } while (0)

#define HI64XX_DSP_INFO(msg, ...)	 \
	do {						  \
		if (hi64xx_dsp_debug_level > 2)  \
			printk(KERN_INFO "[hi64xx-dsp]%s: "msg, __func__, ## __VA_ARGS__); \
	   } while (0)

#define HI64XX_DSP_DEBUG(msg, ...)	  \
	do {						  \
		if (hi64xx_dsp_debug_level > 3)  \
			printk(KERN_INFO "[hi64xx-dsp]%s: "msg, __func__, ## __VA_ARGS__); \
	   } while (0)

#define IN_FUNCTION  HI64XX_DSP_DEBUG("++\n");
#define OUT_FUNCTION HI64XX_DSP_DEBUG("--\n");

enum HI64XX_HIFI_DEBUG {
	HI64XX_HIFI_IMG_DOWNLOAD = 0,     /* 0*/
	HI64XX_HIFI_INIT,                 /* 1*/
	HI64XX_HIFI_DEINIT,               /* 2*/
	HI64XX_HIFI_RUNSTALL_PULL_DOWN,   /* 3*/
	HI64XX_HIFI_RUNSTALL_PULL_UP,     /* 4*/
	HI64XX_HIFI_JTAG_ENABLE,          /* 5*/
	HI64XX_HIFI_UART_ENABLE,          /* 6*/
	HI64XX_HIFI_HIPLL_ENABLE,         /* 7*/
	HI64XX_HIFI_HIPLL_DIAABLE,        /* 8*/
	HI64XX_HIFI_LOWPLL_ENABLE,        /* 9*/
	HI64XX_HIFI_LOWPLL_DIAABLE,       /*10*/
	HI64XX_HIFI_FPGA_CODEC_RESET,     /*11*/
	HI64XX_HIFI_FPGA_PWRON_TEST,      /*12*/
	HI64XX_HIFI_FPGA_OM_TEST,         /*13*/
	HI64XX_HIFI_FACTORY_TEST,         /*14*/
	HI64XX_HIFI_DUMP,                 /*15*/
};

#endif
