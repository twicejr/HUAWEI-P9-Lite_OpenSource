/*
 * Routines for PMU/Hi6421 suspend/resume. Hi4511 board specific.
 *
 * Copyright © 2011-2013 HiSilicon Technologies Co., Ltd.
 *              http://www.hisilicon.com
 * Copyright © 2012-2013 Linaro Ltd.
 *              http://www.linaro.org
 *
 * Author: Guodong Xu <guodong.xu@linaro.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 * Note: Routines defined in this file is for Hi4511 board specific, and will be
 * called during system suspend to RAM. It should be finally moved to Hi6421
 * driver's pm routines.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/console.h>
#include <asm/hardware/arm_timer.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include "core.h"

/* function:    pmuspi_enable
 * description:
 *  enable pmu clk.
 */
static void pmuspi_enable(void)
{
	/*set clk div*/
	writel(0xFF0003, (hs_pctrl_va_base + 0x8));

	/*enable clk*/
	writel(1<<1, (hs_sctrl_base + 0x40));

	/*undo reset*/
	writel(1<<1, (hs_sctrl_base + 0x9C));
}

/* function:    pmuspi_disable
 * description:
 *  disable pmu clk.
 */
static void pmuspi_disable(void)
{
	/*reset*/
	writel(1<<1, (hs_sctrl_base + 0x98));

	/*disable clk*/
	writel(1<<1, (hs_sctrl_base + 0x44));
}

#define PMUSPI_REG(x) (hs_pmuspi_va_base + ((x)<<2))

struct pmuregs {
	unsigned char ucoffset;
	char cval;
	char old_val;
	char cmask;
};

#define PMU_LOW(x, y, z) { .ucoffset = (x),\
			   .cval = (y), \
			   .cmask = (z), \
			   .old_val = 0, \
			 }

static struct pmuregs pmuregs_lookups[] = {
	/*close LDO0 */
	PMU_LOW(0x20, 0x00, 0x10),

	/*w 35 0, emmc rst2_n output low.*/
	PMU_LOW(0x35, 0x00, 0x01),

	/*close ldo13*/
	PMU_LOW(0x2D, 0x30, 0x30),

	/*w 25 31  LDO5 ECO mode*/
	/*PMU_LOW(0x25, 0x20, 0x20),*/

	/*w 26 34  LDO6 ECO mode*/
	/*PMU_LOW(0x26, 0x20, 0x20),*/

	/*w 4e 20 close over temperature protect*/
	PMU_LOW(0x4E, 0x00, 0x01),

	/*w 52 00 close backup battery charging*/
	PMU_LOW(0x52, 0x00, 0x01),

	/*w 14 11  BUCK4 Sleep*/
	PMU_LOW(0x14, 0x11, 0x11),

	/*w 16 11  BUCK5 Sleep*/
	PMU_LOW(0x16, 0x11, 0x11),

	/*w 8f 08 sleep*/
	/*PMU_LOW(0x8F, 0x08, 0x07),*/
};


/* function: pmulowpower
 * description:
 *  configure pmu low power state.
 */
void pmulowpower(int isuspend)
{
	int i = 0;
	int ilen = ARRAY_SIZE(pmuregs_lookups);
	unsigned uregv = 0;

	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	pmuspi_enable();

	if (1 == isuspend) {
		for (i = 0; i < ilen; i++) {
			uregv = readl(PMUSPI_REG(pmuregs_lookups[i].ucoffset));
			pmuregs_lookups[i].old_val = uregv;
			uregv &= ~pmuregs_lookups[i].cmask;
			uregv |= pmuregs_lookups[i].cval;
			writel(uregv, PMUSPI_REG(pmuregs_lookups[i].ucoffset));
		}
	} else {
		for (i = (ilen - 1); i >= 0; i--) {
			uregv = readl(PMUSPI_REG(pmuregs_lookups[i].ucoffset));
			uregv &= ~pmuregs_lookups[i].cmask;
			uregv |= pmuregs_lookups[i].old_val;
			writel(uregv, PMUSPI_REG(pmuregs_lookups[i].ucoffset));
		}
	}

	if (1 == isuspend) {
		pmuspi_disable();
		/* here is an workround way to delay 40ms
		 * make sure LDO0 is poweroff very clean
		 */
		mdelay(40);
	}
}
