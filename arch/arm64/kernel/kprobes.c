/*
 * arch/arm64/kernel/kprobes.c
 *
 * Kprobes support for ARM64
 *
 * Copyright (C) 2013 Linaro Limited.
 * Author: Sandeepa Prabhu <sandeepa.prabhu@linaro.org>
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
 */
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/stop_machine.h>
#include <linux/stringify.h>
#include <asm/traps.h>
#include <asm/ptrace.h>
#include <asm/cacheflush.h>
#include <asm/debug-monitors.h>
#include <asm/system_misc.h>
#include <asm/insn.h>
#include <linux/kprobes.h>
#include <asm/kprobes.h>
#include "kprobes.h"
#include "kprobes-arm64.h"

#define MIN_STACK_SIZE(addr)	min((unsigned long)MAX_STACK_SIZE,	\
	(unsigned long)current_thread_info() + THREAD_START_SP - (addr))

DEFINE_PER_CPU(struct kprobe *, current_kprobe) = NULL;
DEFINE_PER_CPU(struct kprobe_ctlblk, kprobe_ctlblk);

static void __kprobes
post_kprobe_handler(struct kprobe_ctlblk *, struct pt_regs *);

static void __kprobes arch_prepare_ss_slot(struct kprobe *p)
{
	/* prepare insn slot */
	p->ainsn.insn[0] = p->opcode;

	flush_icache_range((uintptr_t) (p->ainsn.insn),
			   (uintptr_t) (p->ainsn.insn) + MAX_INSN_SIZE);

	/*
	 * Needs restoring of return address after stepping xol.
	 */
	p->ainsn.restore.addr = (unsigned long) p->addr +
	  sizeof(kprobe_opcode_t);
	p->ainsn.restore.type = RESTORE_PC;
}

static void __kprobes arch_prepare_simulate(struct kprobe *p)
{
	if (p->ainsn.prepare)
		p->ainsn.prepare(p, &p->ainsn);

	/* This instructions is not executed xol. No need to adjust the PC */
	p->ainsn.restore.addr = 0;
	p->ainsn.restore.type = NO_RESTORE;
}

static void __kprobes arch_simulate_insn(struct kprobe *p, struct pt_regs *regs)
{
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	if (p->ainsn.handler)
		p->ainsn.handler((u32)p->opcode, (long)p->addr, regs);

	/* single step simulated, now go for post processing */
	post_kprobe_handler(kcb, regs);
}

int __kprobes arch_prepare_kprobe(struct kprobe *p)
{
	kprobe_opcode_t insn;
	unsigned long probe_addr = (unsigned long)p->addr;

	/* copy instruction */
	insn = *p->addr;
	p->opcode = insn;

	if (in_exception_text(probe_addr))
		return -EINVAL;

	/* decode instruction */
	switch (arm_kprobe_decode_insn(insn, &p->ainsn)) {
	case INSN_REJECTED:	/* insn not supported */
		return -EINVAL;

	case INSN_GOOD_NO_SLOT:	/* insn need simulation */
		p->ainsn.insn = NULL;
//		printk("prepare_kprobe NO_SLOT.............\n");
		break;

	case INSN_GOOD:	/* instruction uses slot */
		p->ainsn.insn = get_insn_slot();
//		printk("prepare_kprobe INSN_GOOD............\n");
		if (!p->ainsn.insn)
			return -ENOMEM;
		break;
	};

	/* prepare the instruction */
//	printk("prepare_kprobe instruction..........\n");
	if (p->ainsn.insn)
		arch_prepare_ss_slot(p);
	else
		arch_prepare_simulate(p);

	return 0;
}

static int __kprobes patch_text(kprobe_opcode_t *addr, u32 opcode)
{
	void *addrs[1];
	u32 insns[1];

	addrs[0] = (void *)addr;
	insns[0] = (u32)opcode;
	
	return aarch64_insn_patch_text_sync(addrs, insns, 1);
}

/* arm kprobe: install breakpoint in text */
void __kprobes arch_arm_kprobe(struct kprobe *p)
{	
//	printk("install arm_kprobe addr:%p, brk:%x.............\n",p->addr, BRK64_OPCODE_KPROBES);
	patch_text(p->addr, BRK64_OPCODE_KPROBES);
}

/* disarm kprobe: remove breakpoint from text */
void __kprobes arch_disarm_kprobe(struct kprobe *p)
{
	patch_text(p->addr, p->opcode);
}

void __kprobes arch_remove_kprobe(struct kprobe *p)
{
	if (p->ainsn.insn) {
		free_insn_slot(p->ainsn.insn, 0);
		p->ainsn.insn = NULL;
	}
}

static void __kprobes save_previous_kprobe(struct kprobe_ctlblk *kcb)
{
	kcb->prev_kprobe.kp = kprobe_running();
	kcb->prev_kprobe.status = kcb->kprobe_status;
}

static void __kprobes restore_previous_kprobe(struct kprobe_ctlblk *kcb)
{
	__this_cpu_write(current_kprobe, kcb->prev_kprobe.kp);
	kcb->kprobe_status = kcb->prev_kprobe.status;
}

static void __kprobes set_current_kprobe(struct kprobe *p)
{
	__this_cpu_write(current_kprobe, p);
}

/*
 * Debug flag (D-flag) is disabled upon exception entry.
 * Kprobes need to unmask D-flag -ONLY- in case of recursive
 * probe i.e. when probe hit from kprobe handler context upon
 * executing the pre/post handlers. In this case we return with
 * D-flag unmasked so that single-stepping can be carried-out.
 *
 * Keep D-flag masked in all other cases.
 */
static void __kprobes
spsr_set_debug_flag(struct pt_regs *regs, int mask)
{
	unsigned long spsr = regs->pstate;

	if (mask)
		spsr |= PSR_D_BIT;
	else
		spsr &= ~PSR_D_BIT;

	regs->pstate = spsr;
}

/*
 * Interrupts need to be disabled before single-step mode is set, and not
 * reenabled until after single-step mode ends.
 * Without disabling interrupt on local CPU, there is a chance of
 * interrupt occurrence in the period of exception return and  start of
 * out-of-line single-step, that result in wrongly single stepping
 * the interrupt handler.
 */
static void __kprobes kprobes_save_local_irqflag(struct pt_regs *regs)
{
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	kcb->saved_irqflag = regs->pstate;
	regs->pstate |= PSR_I_BIT;
}

static void __kprobes kprobes_restore_local_irqflag(struct pt_regs *regs)
{
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	if (kcb->saved_irqflag & PSR_I_BIT)
		regs->pstate |= PSR_I_BIT;
	else
		regs->pstate &= ~PSR_I_BIT;
}

static void __kprobes
set_ss_context(struct kprobe_ctlblk *kcb, unsigned long addr)
{
	kcb->ss_ctx.ss_status = KPROBES_STEP_PENDING;
	kcb->ss_ctx.match_addr = addr + sizeof(kprobe_opcode_t);
}

static void __kprobes clear_ss_context(struct kprobe_ctlblk *kcb)
{
	kcb->ss_ctx.ss_status = KPROBES_STEP_NONE;
	kcb->ss_ctx.match_addr = 0;
}

static void __kprobes
skip_singlestep_missed(struct kprobe_ctlblk *kcb, struct pt_regs *regs)
{
	/* set return addr to next pc to continue */
	instruction_pointer(regs) += sizeof(kprobe_opcode_t);
}

static void __kprobes setup_singlestep(struct kprobe *p,
				       struct pt_regs *regs,
				       struct kprobe_ctlblk *kcb, int reenter)
{
	unsigned long slot;

	if (reenter) {
		save_previous_kprobe(kcb);
		set_current_kprobe(p);
		kcb->kprobe_status = KPROBE_REENTER;
	} else {
		kcb->kprobe_status = KPROBE_HIT_SS;
	}

	if (p->ainsn.insn) {
		/* prepare for single stepping */
		slot = (unsigned long)p->ainsn.insn;

		set_ss_context(kcb, slot);	/* mark pending ss */

		//if (kcb->kprobe_status == KPROBE_REENTER)
			spsr_set_debug_flag(regs, 0);	// if D-flag is setted,single_step will be failed.

		/* IRQs and single stepping do not mix well. */
		kprobes_save_local_irqflag(regs);
		kernel_enable_single_step(regs);
		instruction_pointer(regs) = slot;
	} else	{
		/* insn simulation */
		arch_simulate_insn(p, regs);
	}
}

static int __kprobes reenter_kprobe(struct kprobe *p,
				    struct pt_regs *regs,
				    struct kprobe_ctlblk *kcb)
{
	switch (kcb->kprobe_status) {
	case KPROBE_HIT_SSDONE:
	case KPROBE_HIT_ACTIVE:
		if (!p->ainsn.check_condn || p->ainsn.check_condn(p, regs)) {
			kprobes_inc_nmissed_count(p);
			setup_singlestep(p, regs, kcb, 1);
		} else	{
			/* condition check failed, skip stepping */
			skip_singlestep_missed(kcb, regs);
		}
		break;
	case KPROBE_HIT_SS:
	case KPROBE_REENTER:
		pr_warn("Unrecoverable kprobe detected at %p.\n", p->addr);
		dump_kprobe(p);
		BUG();
		break;
	default:
		WARN_ON(1);
		return 0;
	}

	return 1;
}

static void __kprobes
post_kprobe_handler(struct kprobe_ctlblk *kcb, struct pt_regs *regs)
{
	struct kprobe *cur = kprobe_running();
	if (!cur)
		return;

	/* return addr restore if non-branching insn */
	if (cur->ainsn.restore.type == RESTORE_PC) {
		//("trace_kprobe_return:%s\n", cur->symbol_name);
		instruction_pointer(regs) = cur->ainsn.restore.addr;
		if (!instruction_pointer(regs))
			BUG();
	}

	/* restore back original saved kprobe variables and continue */
	if (kcb->kprobe_status == KPROBE_REENTER) {
		restore_previous_kprobe(kcb);
		return;
	}
	/* call post handler */
	kcb->kprobe_status = KPROBE_HIT_SSDONE;
	if (cur->post_handler)	{
		/* post_handler can hit breakpoint and single step
		 * again, so we enable D-flag for recursive exception.
		 */
		cur->post_handler(cur, regs, 0);
	}
	
	//printk("kprobe_end %s, addr:%p\n", cur->symbol_name, cur->addr);
	reset_current_kprobe();
}

int __kprobes kprobe_fault_handler(struct pt_regs *regs, unsigned int fsr)
{
	struct kprobe *cur = kprobe_running();
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	//printk("trace_kprobe_fault:%s\n", cur->symbol_name);
	switch (kcb->kprobe_status) {
	case KPROBE_HIT_SS:
	case KPROBE_REENTER:
		/*
		 * We are here because the instruction being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the ip points back to the probe address
		 * and allow the page fault handler to continue as a
		 * normal page fault.
		 */
		instruction_pointer(regs) = (unsigned long)cur->addr;
		if (!instruction_pointer(regs))
			BUG();
		if (kcb->kprobe_status == KPROBE_REENTER)
			restore_previous_kprobe(kcb);
		else
			reset_current_kprobe();

		break;
	case KPROBE_HIT_ACTIVE:
	case KPROBE_HIT_SSDONE:
		/*
		 * We increment the nmissed count for accounting,
		 * we can also use npre/npostfault count for accounting
		 * these specific fault cases.
		 */
		kprobes_inc_nmissed_count(cur);

		/*
		 * We come here because instructions in the pre/post
		 * handler caused the page_fault, this could happen
		 * if handler tries to access user space by
		 * copy_from_user(), get_user() etc. Let the
		 * user-specified handler try to fix it first.
		 */
		if (cur->fault_handler && cur->fault_handler(cur, regs, fsr))
			return 1;

		/*
		 * In case the user-specified fault handler returned
		 * zero, try to fix up.
		 */
		if (fixup_exception(regs))
			return 1;

		break;
	}
	return 0;
}

int __kprobes kprobe_exceptions_notify(struct notifier_block *self,
				       unsigned long val, void *data)
{
	return NOTIFY_DONE;
}

void __kprobes kprobe_handler(struct pt_regs *regs)
{
	struct kprobe *p, *cur;
	struct kprobe_ctlblk *kcb;
	unsigned long addr = instruction_pointer(regs);

	kcb = get_kprobe_ctlblk();
	cur = kprobe_running();

	p = get_kprobe((kprobe_opcode_t *) addr);

	if (p) {
	//printk("kprobe_start %s, addr:%p\n", p->symbol_name, p->addr);
		if (cur) {
			if (reenter_kprobe(p, regs, kcb))
				return;
		} else if (!p->ainsn.check_condn ||
			   p->ainsn.check_condn(p, regs)) {
			/* Probe hit and conditional execution check ok. */
			set_current_kprobe(p);
			kcb->kprobe_status = KPROBE_HIT_ACTIVE;

			/*
			 * If we have no pre-handler or it returned 0, we
			 * continue with normal processing.  If we have a
			 * pre-handler and it returned non-zero, it prepped
			 * for calling the break_handler below on re-entry,
			 * so get out doing nothing more here.
			 *
			 * pre_handler can hit a breakpoint and can step thru
			 * before return, keep PSTATE D-flag enabled until
			 * pre_handler return back.
			 */
			if (!p->pre_handler || !p->pre_handler(p, regs)) {
				//printk("trace_kprobe_pre:%s\n", p->symbol_name);
				kcb->kprobe_status = KPROBE_HIT_SS;
				setup_singlestep(p, regs, kcb, 0);
				return;
			}
		} else {
			/*
			 * Breakpoint hit but conditional check failed,
			 * so just skip the instruction (NOP behaviour)
			 */
			skip_singlestep_missed(kcb, regs);
			return;
		}
	} else if (*(kprobe_opcode_t *) addr != BRK64_OPCODE_KPROBES) {
	
		/*
		 * The breakpoint instruction was removed right
		 * after we hit it.  Another cpu has removed
		 * either a probepoint or a debugger breakpoint
		 * at this address.  In either case, no further
		 * handling of this interrupt is appropriate.
		 * Return back to original instruction, and continue.
		 */
		return;
	} else if (cur) {
		
		/* We probably hit a jprobe.  Call its break handler. */
		if (cur->break_handler && cur->break_handler(cur, regs)) {
			kcb->kprobe_status = KPROBE_HIT_SS;
			setup_singlestep(cur, regs, kcb, 0);
			return;
		}
	} else {
		
		/* breakpoint is removed, now in a race
		 * Return back to original instruction & continue.
		 */
	}
}

int __kprobes
kprobe_ss_hit(struct kprobe_ctlblk *kcb, unsigned long addr)
{
	if ((kcb->ss_ctx.ss_status == KPROBES_STEP_PENDING)
	    && (kcb->ss_ctx.match_addr == addr)) {
		clear_ss_context(kcb);	/* clear pending ss */
		return DBG_HOOK_HANDLED;
	}
	/* not ours, kprobes should ignore it */
	return DBG_HOOK_ERROR;
}

int __kprobes
kprobe_single_step_handler(struct pt_regs *regs, unsigned int esr)
{
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	int retval;

	/* return error if this is not our step */
	retval = kprobe_ss_hit(kcb, instruction_pointer(regs));

	if (retval == DBG_HOOK_HANDLED) {
		kprobes_restore_local_irqflag(regs);
		kernel_disable_single_step();

		if (kcb->kprobe_status == KPROBE_REENTER)
			spsr_set_debug_flag(regs, 1);

		post_kprobe_handler(kcb, regs);
	}

	return retval;
}

int __kprobes
kprobe_breakpoint_handler(struct pt_regs *regs, unsigned int esr)
{
	kprobe_handler(regs);

	return DBG_HOOK_HANDLED;
}

int __kprobes setjmp_pre_handler(struct kprobe *p, struct pt_regs *regs)
{
	struct jprobe *jp = container_of(p, struct jprobe, kp);
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	long stack_ptr = stack_pointer(regs);

	kcb->jprobe_saved_regs = *regs;
	memcpy(kcb->jprobes_stack, (void *)stack_ptr,
	       MIN_STACK_SIZE(stack_ptr));

	instruction_pointer(regs) = (long)jp->entry;
	preempt_disable();
	return 1;
}

void __kprobes jprobe_return(void)
{
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	/*
	 * Jprobe handler return by entering break exception,
	 * encoded same as kprobe, but with following conditions
	 * -a magic number in x0 to identify from rest of other kprobes.
	 * -restore stack addr to original saved pt_regs
	 */
	asm volatile ("ldr x0, [%0]\n\t"
		      "mov sp, x0\n\t"
		      "ldr x0, =" __stringify(JPROBES_MAGIC_NUM) "\n\t"
		      "BRK %1\n\t"
		      "NOP\n\t"
		      :
		      : "r"(&kcb->jprobe_saved_regs.sp),
		      "I"(BRK64_ESR_KPROBES)
		      : "memory");
}

int __kprobes longjmp_break_handler(struct kprobe *p, struct pt_regs *regs)
{
	struct kprobe_ctlblk *kcb = get_kprobe_ctlblk();
	long stack_addr = kcb->jprobe_saved_regs.sp;
	long orig_sp = stack_pointer(regs);
	struct jprobe *jp = container_of(p, struct jprobe, kp);

	if (regs->regs[0] == JPROBES_MAGIC_NUM) {
		if (orig_sp != stack_addr) {
			struct pt_regs *saved_regs =
			    (struct pt_regs *)kcb->jprobe_saved_regs.sp;
			pr_err("current sp %lx does not match saved sp %lx\n",
			       orig_sp, stack_addr);
			pr_err("Saved registers for jprobe %p\n", jp);
			show_regs(saved_regs);
			pr_err("Current registers\n");
			show_regs(regs);
			BUG();
		}
		*regs = kcb->jprobe_saved_regs;
		memcpy((void *)stack_addr, kcb->jprobes_stack,
		       MIN_STACK_SIZE(stack_addr));
		preempt_enable_no_resched();
		return 1;
	}
	return 0;
}

/*
 * Kretprobes: kernel return probes handling
 *
 * AArch64 mode does not support popping the PC value from the
 * stack like on ARM 32-bit (ldmia {..,pc}), so atleast one
 * register need to be used to achieve branching/return.
 * It means return probes cannot return back to the original
 * return address directly without modifying the register context.
 *
 * So like other architectures, we prepare a global routine
 * with NOPs, which serve as trampoline address that hack away the
 * function return, with the exact register context.
 * Placing a kprobe on trampoline routine entry will trap again to
 * execute return probe handlers and restore original return address
 * in ELR_EL1, this way saved pt_regs still hold the original
 * register values to be carried back to the caller.
 */
static void __used kretprobe_trampoline_holder(void)
{
	asm volatile (".global kretprobe_trampoline\n"
			"kretprobe_trampoline:\n"
			"NOP\n\t"
			"NOP\n\t");
}

static int __kprobes
trampoline_probe_handler(struct kprobe *p, struct pt_regs *regs)
{
	struct kretprobe_instance *ri = NULL;
	struct hlist_head *head, empty_rp;
	struct hlist_node *tmp;
	unsigned long flags, orig_ret_addr = 0;
	unsigned long trampoline_address =
		(unsigned long)&kretprobe_trampoline;

	INIT_HLIST_HEAD(&empty_rp);
	kretprobe_hash_lock(current, &head, &flags);

	/*
	 * It is possible to have multiple instances associated with a given
	 * task either because multiple functions in the call path have
	 * a return probe installed on them, and/or more than one return
	 * probe was registered for a target function.
	 *
	 * We can handle this because:
	 *     - instances are always inserted at the head of the list
	 *     - when multiple return probes are registered for the same
	 *       function, the first instance's ret_addr will point to the
	 *       real return address, and all the rest will point to
	 *       kretprobe_trampoline
	 */
	hlist_for_each_entry_safe(ri, tmp, head, hlist) {
		if (ri->task != current)
			/* another task is sharing our hash bucket */
			continue;

		if (ri->rp && ri->rp->handler) {
			__this_cpu_write(current_kprobe, &ri->rp->kp);
			get_kprobe_ctlblk()->kprobe_status = KPROBE_HIT_ACTIVE;
			ri->rp->handler(ri, regs);
			__this_cpu_write(current_kprobe, NULL);
		}

		orig_ret_addr = (unsigned long)ri->ret_addr;
		recycle_rp_inst(ri, &empty_rp);

		if (orig_ret_addr != trampoline_address)
			/*
			 * This is the real return address. Any other
			 * instances associated with this task are for
			 * other calls deeper on the call stack
			 */
			break;
	}

	kretprobe_assert(ri, orig_ret_addr, trampoline_address);
	/* restore the original return address */
	instruction_pointer(regs) = orig_ret_addr;
	reset_current_kprobe();
	kretprobe_hash_unlock(current, &flags);

	hlist_for_each_entry_safe(ri, tmp, &empty_rp, hlist) {
		hlist_del(&ri->hlist);
		kfree(ri);
	}
	//printk("kprobe_end tramp %lx..\n", orig_ret_addr);
	/* return 1 so that post handlers not called */
	return 1;
}

void __kprobes arch_prepare_kretprobe(struct kretprobe_instance *ri,
				      struct pt_regs *regs)
{
	ri->ret_addr = (kprobe_opcode_t *)regs->regs[30];

	/* replace return addr (x30) with trampoline */
	regs->regs[30] = (long)&kretprobe_trampoline;
}

static struct kprobe trampoline = {
	.addr = (kprobe_opcode_t *) &kretprobe_trampoline,
	.pre_handler = trampoline_probe_handler
};

int __kprobes arch_trampoline_kprobe(struct kprobe *p)
{
	return p->addr == (kprobe_opcode_t *) &kretprobe_trampoline;
}

int __init arch_init_kprobes(void)
{
	return register_kprobe(&trampoline);
}
