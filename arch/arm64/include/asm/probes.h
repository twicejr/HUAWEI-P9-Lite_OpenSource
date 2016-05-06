/*
 * arch/arm64/include/asm/probes.h
 *
 * Copyright (C) 2013 Linaro Limited
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
#ifndef _ARM_PROBES_H
#define _ARM_PROBES_H

struct kprobe;
struct arch_specific_insn;

typedef u32 kprobe_opcode_t;
typedef unsigned long (kprobes_pstate_check_t)(unsigned long);
typedef unsigned long
(probes_condition_check_t)(struct kprobe *p, struct pt_regs *);
typedef void
(probes_prepare_t)(struct kprobe *, struct arch_specific_insn *);
typedef void (kprobes_handler_t) (u32 opcode, long addr, struct pt_regs *);

enum pc_restore_type {
	NO_RESTORE,
	RESTORE_PC,
};

struct kprobe_pc_restore {
	enum pc_restore_type type;
	unsigned long addr;
};

/* architecture specific copy of original instruction */
struct arch_specific_insn {
	kprobe_opcode_t *insn;
	kprobes_pstate_check_t *pstate_cc;
	probes_condition_check_t *check_condn;
	probes_prepare_t *prepare;
	kprobes_handler_t *handler;
	/* restore address after step xol */
	struct kprobe_pc_restore restore;
};

#endif
