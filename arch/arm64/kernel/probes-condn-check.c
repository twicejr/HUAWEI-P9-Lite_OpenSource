/*
 * arch/arm64/kernel/probes-condn-check.c
 *
 * Copyright (C) 2013 Linaro Limited
 *
 * Copied from: arch/arm/kernel/kprobes-common.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * Description:
 *
 *  AArch64 and AArch32 shares same conditional(CNZV) flags encoding.
 *  This file implements conditional check helpers compatible with
 *  both AArch64 and AArch32 modes. Uprobes on v8 can handle both 32-bit
 *  & 64-bit user-space instructions, so we abstract the common functions
 *  in this file. While AArch64 and AArch32 specific instruction handling
 *  are implemented in separate files, this file contains common bits.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/probes.h>

static unsigned long __kprobes __check_eq(unsigned long pstate)
{
	return pstate & PSR_Z_BIT;
}

static unsigned long __kprobes __check_ne(unsigned long pstate)
{
	return (~pstate) & PSR_Z_BIT;
}

static unsigned long __kprobes __check_cs(unsigned long pstate)
{
	return pstate & PSR_C_BIT;
}

static unsigned long __kprobes __check_cc(unsigned long pstate)
{
	return (~pstate) & PSR_C_BIT;
}

static unsigned long __kprobes __check_mi(unsigned long pstate)
{
	return pstate & PSR_N_BIT;
}

static unsigned long __kprobes __check_pl(unsigned long pstate)
{
	return (~pstate) & PSR_N_BIT;
}

static unsigned long __kprobes __check_vs(unsigned long pstate)
{
	return pstate & PSR_V_BIT;
}

static unsigned long __kprobes __check_vc(unsigned long pstate)
{
	return (~pstate) & PSR_V_BIT;
}

static unsigned long __kprobes __check_hi(unsigned long pstate)
{
	pstate &= ~(pstate >> 1);	/* PSR_C_BIT &= ~PSR_Z_BIT */
	return pstate & PSR_C_BIT;
}

static unsigned long __kprobes __check_ls(unsigned long pstate)
{
	pstate &= ~(pstate >> 1);	/* PSR_C_BIT &= ~PSR_Z_BIT */
	return (~pstate) & PSR_C_BIT;
}

static unsigned long __kprobes __check_ge(unsigned long pstate)
{
	pstate ^= (pstate << 3);	/* PSR_N_BIT ^= PSR_V_BIT */
	return (~pstate) & PSR_N_BIT;
}

static unsigned long __kprobes __check_lt(unsigned long pstate)
{
	pstate ^= (pstate << 3);	/* PSR_N_BIT ^= PSR_V_BIT */
	return pstate & PSR_N_BIT;
}

static unsigned long __kprobes __check_gt(unsigned long pstate)
{
	/*PSR_N_BIT ^= PSR_V_BIT */
	unsigned long temp = pstate ^ (pstate << 3);

	temp |= (pstate << 1);	/*PSR_N_BIT |= PSR_Z_BIT */
	return (~temp) & PSR_N_BIT;
}

static unsigned long __kprobes __check_le(unsigned long pstate)
{
	/*PSR_N_BIT ^= PSR_V_BIT */
	unsigned long temp = pstate ^ (pstate << 3);

	temp |= (pstate << 1);	/*PSR_N_BIT |= PSR_Z_BIT */
	return temp & PSR_N_BIT;
}

static unsigned long __kprobes __check_al(unsigned long pstate)
{
	return true;
}

kprobes_pstate_check_t * const kprobe_condition_checks[16] = {
	&__check_eq, &__check_ne, &__check_cs, &__check_cc,
	&__check_mi, &__check_pl, &__check_vs, &__check_vc,
	&__check_hi, &__check_ls, &__check_ge, &__check_lt,
	&__check_gt, &__check_le, &__check_al, &__check_al
};
