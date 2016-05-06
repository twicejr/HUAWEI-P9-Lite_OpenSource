/*
 * arch/arm/mach-k3v2/board-tc45msu3.c
 *
 * Copyright (C) 2010 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include "dev_lcd.h"
#include <mach/platform.h>
#include <mach/gpio.h>
#include <linux/platform_device.h>
 
#define GPIO_LCD_RESET  (GPIO_9_7)
#define GPIO_LCD_POWER  (GPIO_4_0)
#define GPIO_LCD_ID0	(GPIO_9_5)
#define GPIO_LCD_ID1	(GPIO_9_6)
#define GPIO_PWM0   (GPIO_8_0)//reserved
#define GPIO_PWM1   (GPIO_8_4)//reserved


#define PLATFORM_DEVICE_LCD_NAME "mipi_toshiba_MDW70"


static struct resource k3_lcd_resources[] = {
	[0] = {
		.name = GPIO_LCD_RESET_NAME,
		.start = GPIO_LCD_RESET,
		.end = GPIO_LCD_RESET,
		.flags = IORESOURCE_IO,
	},
	[1] = {
		.name = GPIO_LCD_POWER_NAME,
		.start = GPIO_LCD_POWER,
		.end = GPIO_LCD_POWER,
		.flags = IORESOURCE_IO,
	},
	[2] = {
		.name = GPIO_LCD_ID0_NAME,
		.start = GPIO_LCD_ID0,
		.end = GPIO_LCD_ID0,
		.flags = IORESOURCE_IO,
	},
	[3] = {
		.name = GPIO_LCD_ID1_NAME,
		.start = GPIO_LCD_ID1,
		.end = GPIO_LCD_ID1,
		.flags = IORESOURCE_IO,
	},
	[4] = {
		.name = GPIO_PWM0_NAME,
		.start = GPIO_PWM0,
		.end = GPIO_PWM0,
		.flags = IORESOURCE_IO,
	},
	[5] = {
		.name = GPIO_PWM1_NAME,
		.start = GPIO_PWM1,
		.end = GPIO_PWM1,
		.flags = IORESOURCE_IO,
	},
	[6] = {
		.name = REG_BASE_PWM0_NAME,
		.start = REG_BASE_PWM0,
		.end = REG_BASE_PWM0 + REG_PWM0_IOSIZE-1,
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device k3_lcd_device = {
	.name = PLATFORM_DEVICE_LCD_NAME,
	.id	= 1,
	.dev = {
		.init_name = REGULATOR_DEV_LCD_NAME,
	},
	.num_resources = ARRAY_SIZE(k3_lcd_resources),
	.resource = k3_lcd_resources,
};


int __init lcd_device_toshiba_init(void)
{
	int ret = 0;
	ret = platform_device_register(&k3_lcd_device);
	return ret;
};

arch_initcall(lcd_device_toshiba_init);

