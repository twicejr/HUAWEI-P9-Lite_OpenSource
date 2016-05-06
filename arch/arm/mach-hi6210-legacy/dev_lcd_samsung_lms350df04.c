/*
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
//#include "dev_lcd.h"     /* This file is moved to kernel/drivers/huawei/device folder */ 
#include <mach/platform.h>
#include <mach/gpio.h>
#include <linux/platform_device.h>

#define GPIO_LCD_POWER_NAME "gpio_lcd_power"
#define GPIO_LCD_RESET_NAME "gpio_lcd_reset"
#define GPIO_LCD_ID0_NAME "gpio_lcd_id0"
#define GPIO_LCD_ID1_NAME "gpio_lcd_id1"
#define GPIO_PWM0_NAME   "gpio_pwm0"
#define GPIO_PWM1_NAME   "gpio_pwm1"
#define REG_BASE_PWM0_NAME  "reg_base_pwm0"
#define REGULATOR_DEV_LCD_NAME  "balong_dev_lcd"

#define GPIO_LCD_RESET  (GPIO_0_7)
#define GPIO_LCD_POWER  (GPIO_0_4)
#define GPIO_LCD_ID0	(GPIO_0_2)
#define GPIO_LCD_ID1	(GPIO_0_3)
#define GPIO_PWM0   (GPIO_0_6)
#define GPIO_PWM1   (GPIO_1_0)


#define PLATFORM_DEVICE_LCD_NAME "ldi_samsung_LMS350DF04"


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


int __init lcd_device_sansumg_lms350_init(void)
{
	int ret = 0;
	ret = platform_device_register(&k3_lcd_device);
	return ret;
};

arch_initcall(lcd_device_sansumg_lms350_init);

