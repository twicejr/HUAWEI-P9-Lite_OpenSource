/*
 * arch/arm/mach-k3v2/include/mach/debugled.h
 *
 * Copyright (C) 2011 Hisilicon Co. Ltd.
 *
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
#ifndef DEBUG_LED_H
#define DEBUG_LED_H

#include <asm/io.h>

#ifdef CONFIG_DEBUG_LED

extern spinlock_t dbgled_rgb_lock;

static unsigned char LED_TIME_PARAM[25] = {
	0x11, 0x14, 0x16, 0x17, 0x19,
	0x41, 0x44, 0x46, 0x47, 0x49,
	0x61, 0x64, 0x66, 0x67, 0x69,
	0x71, 0x74, 0x76, 0x77, 0x79,
	0x91, 0x94, 0x96, 0x97, 0x99,
};

static unsigned char KEYPAD_TIME_PARAM[5] = {
	0x07, 0x33, 0x35, 0x53, 0x55
};


#define ADDR_TIME_GREEN    IO_ADDRESS(0xfcc000f0)
#define ADDR_TIME_RED      IO_ADDRESS(0xfcc00100)
#define ADDR_TIME_BLUE     IO_ADDRESS(0xfcc00110)
#define ADDR_TIME_KPD      IO_ADDRESS(0xfcc0011c)

#define ADDR_LED_ENABLE    IO_ADDRESS(0xfcc000e0)
#define ADDR_KPDLED_ENABLE IO_ADDRESS(0xfcc00118)

#define EN_BIT_GREEN   	   1
#define EN_BIT_RED         2
#define EN_BIT_BLUE        4

#define DEBUG_LED_INIT() \
	do { \
		writel(2, IO_ADDRESS(0xfcc000e8)); \
		writel(2, IO_ADDRESS(0xfcc000fc)); \
		writel(2, IO_ADDRESS(0xfcc00108)); \
	} while(0)

#define DEBUG_LED_SET_GREEN(time) \
	do { \
		spin_lock(&dbgled_rgb_lock); \
		unsigned int val = readl(ADDR_LED_ENABLE); \
		val |= EN_BIT_GREEN; \
		writel(time, ADDR_TIME_GREEN); \
		writel(val, ADDR_LED_ENABLE); \
		spin_unlock(&dbgled_rgb_lock); \
	} while(0)

#define DEBUG_LED_SET_RED(time) \
	do { \
		spin_lock(&dbgled_rgb_lock); \
		unsigned int val = readl(ADDR_LED_ENABLE); \
		val |= EN_BIT_RED; \
		writel(time, ADDR_TIME_RED); \
		writel(val, ADDR_LED_ENABLE); \
		spin_unlock(&dbgled_rgb_lock); \
	} while(0)

#define DEBUG_LED_SET_BLUE(time) \
	do { \
		spin_lock(&dbgled_rgb_lock); \
		unsigned int val = readl(ADDR_LED_ENABLE); \
		val |= EN_BIT_BLUE; \
		writel(time, ADDR_TIME_BLUE); \
		writel(val, ADDR_LED_ENABLE); \
		spin_unlock(&dbgled_rgb_lock); \
	} while(0)

#define DEBUG_LED_SET_KPD(time) \
		do { \
			writel(time, ADDR_TIME_KPD); \
			writel(0x37, ADDR_KPDLED_ENABLE); \
		} while(0)


#define DEBUG_LED_CLEAR(rgb_bit) \
	do { \
		spin_lock(&dbgled_rgb_lock); \
		unsigned int val = readl(ADDR_LED_ENABLE); \
		val &= ~(rgb_bit); \
		writel(val, ADDR_LED_ENABLE); \
		spin_unlock(&dbgled_rgb_lock); \
	} while(0)

#define DEBUG_LED_CLEAR_KPD() \
	do { \
		writel(0, ADDR_KPDLED_ENABLE); \
	} while(0)

#define DEBUG_LED_IRQ_ENTER(cpuid, irq) \
	do { \
		unsigned long time1 = (irq % 100) / 4; \
		unsigned long time2 = irq / 100; \
		if (cpuid == 0) {\
			DEBUG_LED_SET_GREEN(LED_TIME_PARAM[time1]); \
			DEBUG_LED_SET_KPD(KEYPAD_TIME_PARAM[time2]); \
		}\
		else if (cpuid == 1) {\
			DEBUG_LED_SET_RED(LED_TIME_PARAM[time1]); \
			if (time2 != 0) \
				DEBUG_LED_SET_BLUE(LED_TIME_PARAM[time2]); \
		} \
	} while(0)

#define DEBUG_LED_IRQ_EXIT(cpuid, irq) \
	do { \
		if (cpuid == 0) {\
			DEBUG_LED_CLEAR(EN_BIT_GREEN); \
			DEBUG_LED_CLEAR_KPD(); \
		}\
		else if (cpuid == 1) {\
			DEBUG_LED_CLEAR(EN_BIT_RED); \
			DEBUG_LED_CLEAR(EN_BIT_BLUE); \
		}\
	} while(0)

#define DEBUG_LED_SOFTIRQ_ENTER() \
	do { \
		DEBUG_LED_SET_BLUE(0xf0); \
		DEBUG_LED_SET_RED(0xf0); \
	} while(0)

#define DEBUG_LED_SOFTIRQ_EXIT() \
	do { \
		DEBUG_LED_CLEAR(EN_BIT_BLUE); \
		DEBUG_LED_CLEAR(EN_BIT_RED); \
	} while(0)

#else

#define DEBUG_LED_INIT()

#define DEBUG_LED_SET_GREEN(time)

#define DEBUG_LED_SET_RED(time)

#define DEBUG_LED_SET_BLUE(time)

#define DEBUG_LED_SET_KPD(time)

#define DEBUG_LED_CLEAR(rgb_bit)

#define DEBUG_LED_CLEAR_KPD()

#define DEBUG_LED_IRQ_ENTER(cpuid, irq)

#define DEBUG_LED_IRQ_EXIT(cpuid, irq)

#define DEBUG_LED_SOFTIRQ_ENTER()

#define DEBUG_LED_SOFTIRQ_EXIT()

#endif

#endif //DEBUG_LED_H

