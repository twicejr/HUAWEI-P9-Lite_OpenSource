/* include/linux/hisi_hi6421_vibrator.h
 *
 * Copyright (c) 2011-2013 Hisilicon Technologies CO., Ltd.
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

#ifndef _LINUX_VIBRATOR_K3_H
#define _LINUX_VIBRATOR_K3_H

#define K3_VIBRATOR "vibrator"

#define DR2_CTRL		(0xC7 << 2)
#define DR2_CTRL1	(0xC8 << 2)
#define DR2_CTRL2	(0xC9 << 2)
#define DR2_ISET		(0xCA << 2)
#define DR2_FREQ		(0xCB << 2)
#define DR2_RESERVED	(0xCC << 2)

#define REG_DR2_EN	(1 << 0)
#define DRIVE_MODE	(1 << 1)
#define LM_FIX_MODE	(0 << 4)
#define LM_DR2_TEST	((1<<5)|(1<<6))
#define DR2_DISABLE	(0xFE)

#define DR2_TEST_MODE_CLR	(0x8E)
#define DR2_OCP_HIGHZ_CLR	(0xCF)
#define DR2_HIGHZ_EN	(0x10)
#define DR2_HIGHZ_DIS	(0xEF)
#define DR2_OT_EN	(1 << 0)

#define DR2_OT_SEL_10		10
#define DR2_OT_SEL_20		20
#define DR2_OT_SEL_40		40
#define DR2_OT_SEL_50		50
#define DR2_OT_SEL_60		60
#define DR2_OT_SEL_80		80
#define DR2_OT_SEL_100		100
#define DR2_OT_SEL_200		200
#define DR2_OT_SEL_300		300
#define DR2_OT_SEL_400		400
#define DR2_OT_SEL_500		500
#define DR2_OT_SEL_600		600
#define DR2_OT_SEL_700		700
#define DR2_OT_SEL_800		800
#define DR2_OT_SEL_900		900
#define DR2_OT_SEL_1000		1000

#define	DR2_OT_SEL00		0x00
#define	DR2_OT_SEL01		0x10
#define	DR2_OT_SEL02		0x20
#define	DR2_OT_SEL03		0x30
#define	DR2_OT_SEL04		0x40
#define	DR2_OT_SEL05		0x50
#define	DR2_OT_SEL06		0x60
#define	DR2_OT_SEL07		0x70

#define	DR2_OT_SEL08		0x80
#define	DR2_OT_SEL09		0x90
#define	DR2_OT_SEL10		0xA0
#define	DR2_OT_SEL11		0xB0
#define	DR2_OT_SEL12		0xC0
#define	DR2_OT_SEL13		0xD0
#define	DR2_OT_SEL14		0xE0
#define	DR2_OT_SEL15		0xF0
#define	WORK_ERM		0
#define	MAX_LM_DR2	(0x60)
#define	ISET_POWER	(0x3F)  /* iset power,3.3v */
/* read register  */
#define K3_VIB_REG_R(base_reg, reg)  readl((base_reg) + (reg))
/* wirte register  */
#define K3_VIB_REG_W(set, base_reg, reg)  do { \
	writel((set), (base_reg) + (reg)); \
} while (0)
#endif
