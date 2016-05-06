/*
 * Header file for device driver Hi6421 PMIC
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (C) 2011 Hisilicon.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef	__HISI_HI6421_OCP_H
#define	__HISI_HI6421_OCP_H

#include <linux/irqdomain.h>

#define 	HI6421_OCP_IRQ1		0x125
#define 	HI6421_OCP_IRQ2		0x126
#define 	HI6421_OCP_IRQ3		0x127
#define 	HI6421_OCP_IRQ4		0x128
#define 	HI6421_OCP_IRQ5		0x129
#define 	HI6421_OCP_IRQ6		0x12A
#define 	HI6421_OCP_IRQ7		0x12B

#define 	HI6421_OCP_IRQM1		0x107
#define 	HI6421_OCP_IRQM2		0x108
#define 	HI6421_OCP_IRQM3		0x109
#define 	HI6421_OCP_IRQM4		0x10A
#define 	HI6421_OCP_IRQM5		0x10B
#define 	HI6421_OCP_IRQM6		0x10C
#define 	HI6421_OCP_IRQM7		0x10D

#define 	HI6421_OCP_NR_IRQ		56
#define 	HI6421_OCP_MASK_FIELD 0xFF
#define	HI6421_OCP_BITS		8

#define 	BUCK0 			7
#define 	BUCK1 			6
#define 	BUCK2 			5
#define 	BUCK3 			4
#define 	BUCK4 			3
#define 	BUCK5 			2
#define 	BUCK6 			1
#define 	LDO0_2 			0

#define 	LDO1 			15
#define 	LDO2 			14
#define 	LDO3 			13
#define 	LDO4 			12
#define 	LDO5 			11
#define 	LDO6 			10
#define 	LDO7 			9
#define 	LDO8 			8

#define 	LDO9 			23
#define 	LDO10 			22
#define 	LDO11 			21
#define 	LDO12 			20
#define 	LDO13 			19
#define 	LDO14 			18
#define 	LDO15 			17
#define 	LDO16 			16

#define 	LDO17 			31
#define 	LDO18 			30
#define 	LDO19 			29
#define 	LDO20 			28
#define 	LDO21 			27
#define 	LDO22 			26
#define 	LDO23 			25
#define 	LDO24 			24

#define 	LDO25 			7
#define 	LDO26 			6
#define 	LSW50 			5
#define 	LSW51 			4
#define 	LSW52 			3
#define 	LSW53 			2
#define 	DCDR2 			1
#define 	ACDR2 			0

#define 	BST				15
#define 	CLASSD 			14
#define 	BSTSHORT 		13
#define 	BUCK0SHORT	12
#define 	BUCK12SHORT 	11
#define 	BUCK3SHORT	10
#define 	BUCK4SHORT	9
#define 	BUCK5SHORT	8

#define 	BUCK6SHORT 		23

#endif		/* __HISI_HI6421_OCP_H */
