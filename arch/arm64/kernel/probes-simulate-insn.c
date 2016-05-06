/*
 * arch/arm64/kernel/probes-simulate-insn.c
 *
 * Copyright (C) 2013 Linaro Limited.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/module.h>

#include "probes-simulate-insn.h"

#define sign_extend(x, signbit)		\
	((x) | (0 - ((x) & (1 << (signbit)))))

#define bbl_displacement(insn)		\
	sign_extend(((insn) & 0x3ffffff) << 2, 27)

#define bcond_displacement(insn)	\
	sign_extend(((insn >> 5) & 0x7ffff) << 2, 21)

#define cbz_displacement(insn)	\
	sign_extend(((insn >> 5) & 0x7ffff) << 2, 21)

#define tbz_displacement(insn)	\
	sign_extend(((insn >> 5) & 0x3fff) << 2, 15)

#define ldr_displacement(insn)	\
	sign_extend(((insn >> 5) & 0x7ffff) << 2, 21)


unsigned long __kprobes check_cbz(u32 opcode, struct pt_regs *regs)
{
	int xn = opcode & 0x1f;

	return (opcode & (1 << 31)) ?
	    !(regs->regs[xn]) : !(regs->regs[xn] & 0xffffffff);
}

unsigned long __kprobes check_cbnz(u32 opcode, struct pt_regs *regs)
{
	int xn = opcode & 0x1f;

	return (opcode & (1 << 31)) ?
	    (regs->regs[xn]) : (regs->regs[xn] & 0xffffffff);
}

unsigned long __kprobes check_tbz(u32 opcode, struct pt_regs *regs)
{
	int xn = opcode & 0x1f;
	int bit_pos = ((opcode & (1 << 31)) >> 26) | ((opcode >> 19) & 0x1f);

	return ~((regs->regs[xn] >> bit_pos) & 0x1);
}

unsigned long __kprobes check_tbnz(u32 opcode, struct pt_regs *regs)
{
	int xn = opcode & 0x1f;
	int bit_pos = ((opcode & (1 << 31)) >> 26) | ((opcode >> 19) & 0x1f);

	return (regs->regs[xn] >> bit_pos) & 0x1;
}

/*
 * instruction simulate functions
 */
void __kprobes simulate_none(u32 opcode, long addr, struct pt_regs *regs)
{
}

void __kprobes
simulate_adr_adrp(u32 opcode, long addr, struct pt_regs *regs)
{
	long imm, xn, val;

	xn = opcode & 0x1f;
	imm = ((opcode >> 3) & 0x1ffffc) | ((opcode >> 29) & 0x3);
	imm = sign_extend(imm, 20);
	if (opcode & 0x80000000)
		val = (imm<<12) + (addr & 0xfffffffffffff000);
	else
		val = imm + addr;

	regs->regs[xn] = val;

	instruction_pointer(regs) += 4;
}

void __kprobes
simulate_b_bl(u32 opcode, long addr, struct pt_regs *regs)
{
	int disp = bbl_displacement(opcode);

	/* Link register is x30 */
	if (opcode & (1 << 31))
		regs->regs[30] = addr + 4;

	instruction_pointer(regs) = addr + disp;
}

void __kprobes
simulate_b_cond(u32 opcode, long addr, struct pt_regs *regs)
{
	int disp = bcond_displacement(opcode);

	instruction_pointer(regs) = addr + disp;
}

void __kprobes
simulate_br_blr_ret(u32 opcode, long addr, struct pt_regs *regs)
{
	int xn = (opcode >> 5) & 0x1f;

	/* Link register is x30 */
	if (((opcode >> 21) & 0x3) == 1)
		regs->regs[30] = addr + 4;

	instruction_pointer(regs) = regs->regs[xn];
}

void __kprobes
simulate_cbz_cbnz(u32 opcode, long addr, struct pt_regs *regs)
{
	int disp = cbz_displacement(opcode);

	instruction_pointer(regs) = addr + disp;
}

void __kprobes
simulate_tbz_tbnz(u32 opcode, long addr, struct pt_regs *regs)
{
	int disp = tbz_displacement(opcode);

	instruction_pointer(regs) = addr + disp;
}

void __kprobes
simulate_ldr_literal(u32 opcode, long addr, struct pt_regs *regs)
{
	u64 *load_addr;
	int xn = opcode & 0x1f;
	int disp = ldr_displacement(opcode);

	load_addr = (u64 *) (addr + disp);

	if (opcode & (1 << 30))	/* x0-x31 */
		regs->regs[xn] = *load_addr;
	else			/* w0-w31 */
		*(u32 *) (&regs->regs[xn]) = (*(u32 *) (load_addr));

	instruction_pointer(regs) += 4;
}

void __kprobes
simulate_ldrsw_literal(u32 opcode, long addr, struct pt_regs *regs)
{
	s32 *load_addr;
	int xn = opcode & 0x1f;
	int disp = ldr_displacement(opcode);

	load_addr = (s32 *) (addr + disp);
	regs->regs[xn] = *load_addr;

	instruction_pointer(regs) += 4;
}
