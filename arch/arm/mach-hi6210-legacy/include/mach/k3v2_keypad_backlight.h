/*
 * Filename:kernel/arch/arm/mach-k3v2/include/mach/k3v2_keypad_backlight.h
 *
 * Discription:define Macros that will be used in k3v2_keypad_backlight.c.
 *
 * Copyright (C) 2011 Hisilicon
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 *
 * Revision history:
 */

#ifndef _K3_KEYPAD_BACKLIGHT_H
#define _K3_KEYPAD_BACKLIGHT_H
#include <mach/platform.h>

/*define keypad backlight's current by setting register DR1_CTRL*/
#define BRIGHTNESS_5			0x0		/*means    5mA*/
#define BRIGHTNESS_10			0x1		/*means   10mA*/
#define BRIGHTNESS_15			0x2		/*means   15mA*/
#define BRIGHTNESS_20			0x3		/*means   20mA*/
#define BRIGHTNESS_25			0x4		/*means   25mA*/
#define BRIGHTNESS_30			0x5		/*means   30mA*/
#define BRIGHTNESS_35			0x6		/*means   35mA*/
#define BRIGHTNESS_40			0x7		/*means   40mA*/

/*define keypad backlight's on-time in register DR1_TIM_CONT1*/
#define BRIGHTNESS_ON_LEVEL0	0x0		/*means    1ms	*/
#define BRIGHTNESS_ON_LEVEL1	0x1		/*means    0.25s*/
#define BRIGHTNESS_ON_LEVEL2	0x2		/*means    0.5s	*/
#define BRIGHTNESS_ON_LEVEL3	0x3		/*means    1s	*/
#define BRIGHTNESS_ON_LEVEL4	0x4		/*means    2s	*/
#define BRIGHTNESS_ON_LEVEL5	0x5		/*means    4s	*/
#define BRIGHTNESS_ON_LEVEL6	0x6		/*means    4s	*/
#define BRIGHTNESS_ON_LEVEL7	0x7		/*means    all-time*/

/*define keypad backlight's off-time in register DR1_TIM_CONT1*/
#define BRIGHTNESS_OFF_LEVEL0	0x0		/*means    1ms	*/
#define BRIGHTNESS_OFF_LEVEL1	0x1		/*means    0.25s*/
#define BRIGHTNESS_OFF_LEVEL2	0x2		/*means    0.5s	*/
#define BRIGHTNESS_OFF_LEVEL3	0x3		/*means    1s	*/
#define BRIGHTNESS_OFF_LEVEL4	0x4		/*means    2s	*/
#define BRIGHTNESS_OFF_LEVEL5	0x5		/*means    4s	*/
#define BRIGHTNESS_OFF_LEVEL6	0x6		/*means    4s	*/
#define BRIGHTNESS_OFF_LEVEL7	0x7		/*means    all-time*/

/*define keypad backlight's on-time contorl bit in register DR1_TIM_CONT1*/
#define BRIGHTNESS_ON_BIT		4

/*define keypad backlight's contorl bit in register DR1_CTRL*/
#define DR1_FLASH_ENABLE		(1<<5)
#define DR1_ENABLE			(1<<4)
#define DR1_DISABLE			(0x0)

/*define keypad backlight's register address*/
#define DR1_CTRL			IO_ADDRESS(REG_BASE_PMUSPI + (0x46 << 2))
#define DR1_TIM_CONT1			IO_ADDRESS(REG_BASE_PMUSPI + (0x47 << 2))

#define BACKLIGHT_MAX_BRIGHTNESS BRIGHTNESS_40
#define BACKLIGHT_MIN_BRIGHTNESS BRIGHTNESS_5

#define APP_MAX_BRIGHTNESS		255

#endif
