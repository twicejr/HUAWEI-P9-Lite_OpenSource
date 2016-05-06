/*
 * arch/arm64/kernel/kprobes-arm64.c
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
#include <asm/kprobes.h>
#include <asm/insn.h>

#include "kprobes-arm64.h"
#include "probes-simulate-insn.h"

/*
 * condition check functions for kprobes simulation
 */
static unsigned long __kprobes
__check_pstate(struct kprobe *p, struct pt_regs *regs)
{
	struct arch_specific_insn *asi = &p->ainsn;
	unsigned long pstate = regs->pstate & 0xffffffff;

	return asi->pstate_cc(pstate);
}

static unsigned long __kprobes
__check_cbz(struct kprobe *p, struct pt_regs *regs)
{
	return check_cbz((u32)p->opcode, regs);
}

static unsigned long __kprobes
__check_cbnz(struct kprobe *p, struct pt_regs *regs)
{
	return check_cbnz((u32)p->opcode, regs);
}

static unsigned long __kprobes
__check_tbz(struct kprobe *p, struct pt_regs *regs)
{
	return check_tbz((u32)p->opcode, regs);
}

static unsigned long __kprobes
__check_tbnz(struct kprobe *p, struct pt_regs *regs)
{
	return check_tbnz((u32)p->opcode, regs);
}

/*
 * prepare functions for instruction simulation
 */
static void __kprobes
prepare_none(struct kprobe *p, struct arch_specific_insn *asi)
{
}

static void __kprobes
prepare_bcond(struct kprobe *p, struct arch_specific_insn *asi)
{
	kprobe_opcode_t insn = p->opcode;

	asi->check_condn = __check_pstate;
	asi->pstate_cc = kprobe_condition_checks[insn & 0xf];
}

static void __kprobes
prepare_cbz_cbnz(struct kprobe *p, struct arch_specific_insn *asi)
{
	kprobe_opcode_t insn = p->opcode;

	asi->check_condn = (insn & (1 << 24)) ? __check_cbnz : __check_cbz;
}

static void __kprobes
prepare_tbz_tbnz(struct kprobe *p, struct arch_specific_insn *asi)
{
	kprobe_opcode_t insn = p->opcode;

	asi->check_condn = (insn & (1 << 24)) ? __check_tbnz : __check_tbz;
}

static bool __kprobes aarch64_insn_is_steppable(u32 insn)
{
	if (aarch64_get_insn_class(insn) == AARCH64_INSN_CLS_BR_SYS) {
		if (aarch64_insn_is_branch(insn))
			return false;

		/* modification of daif creates issues */
		if (aarch64_insn_is_daif_access(insn))
			return false;

		if (aarch64_insn_is_exception(insn))
			return false;

		if (aarch64_insn_is_hint(insn))
			return aarch64_insn_is_nop(insn);

		return true;
	}

	if (aarch64_insn_uses_literal(insn))
		return false;

	if (aarch64_insn_is_exclusive(insn))
		return false;

	
	return true;
}

/* Return:
 *   INSN_REJECTED     If instruction is one not allowed to kprobe,
 *   INSN_GOOD         If instruction is supported and uses instruction slot,
 *   INSN_GOOD_NO_SLOT If instruction is supported but doesn't use its slot.
 */
enum kprobe_insn __kprobes
arm_kprobe_decode_insn(kprobe_opcode_t insn, struct arch_specific_insn *asi)
{
	/*
	 * Instructions reading or modifying the PC won't work from the XOL
	 * slot.
	 */
	if (aarch64_insn_is_steppable(insn))
		return INSN_GOOD;

	asi->prepare = prepare_none;

	if (aarch64_insn_is_bcond(insn)) {
		asi->prepare = prepare_bcond;
		asi->handler = simulate_b_cond;
	} else if (aarch64_insn_is_cb(insn)) {
		asi->prepare = prepare_cbz_cbnz;
		asi->handler = simulate_cbz_cbnz;
	} else if (aarch64_insn_is_tb(insn)) {
		asi->prepare = prepare_tbz_tbnz;
		asi->handler = simulate_tbz_tbnz;
	} else if (aarch64_insn_is_adr_adrp(insn))
		asi->handler = simulate_adr_adrp;
	else if (aarch64_insn_is_b_bl(insn))
		asi->handler = simulate_b_bl;
	else if (aarch64_insn_is_br_blr(insn) || aarch64_insn_is_ret(insn))
		asi->handler = simulate_br_blr_ret;
	else if (aarch64_insn_is_ldr_lit(insn))
		asi->handler = simulate_ldr_literal;
	else if (aarch64_insn_is_ldrsw_lit(insn))
		asi->handler = simulate_ldrsw_literal;
	else
		/*
		 * Instruction cannot be stepped out-of-line and we don't
		 * (yet) simulate it.
		 */
		return INSN_REJECTED;

	return INSN_GOOD_NO_SLOT;
}
