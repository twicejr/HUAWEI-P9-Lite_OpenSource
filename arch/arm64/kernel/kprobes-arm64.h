/*
 * arch/arm64/kernel/kprobes-arm64.h
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

#ifndef _ARM_KERNEL_KPROBES_ARM64_H
#define _ARM_KERNEL_KPROBES_ARM64_H

enum kprobe_insn {
	INSN_REJECTED,
	INSN_GOOD_NO_SLOT,
	INSN_GOOD,
};

extern kprobes_pstate_check_t * const kprobe_condition_checks[16];

enum kprobe_insn __kprobes
arm_kprobe_decode_insn(kprobe_opcode_t insn, struct arch_specific_insn *asi);

#endif /* _ARM_KERNEL_KPROBES_ARM64_H */
