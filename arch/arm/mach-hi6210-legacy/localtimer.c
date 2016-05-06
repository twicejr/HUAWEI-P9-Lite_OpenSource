/*
 *  linux/arch/arm/mach-hi6620/localtimer.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/smp.h>
#include <linux/clockchips.h>
#include <asm/localtimer.h>
#include <asm/smp_twd.h>
#include <asm/irq.h>
#include <asm/localtimer.h>
#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/cpu.h>
#include <asm/hardware/arm_timer.h>
#include <asm/mach/time.h>
#include <mach/early-debug.h>
#include <mach/platform.h>
#include <mach/hardware.h>
#include <mach/hisi_cortex-a9.h>
#include <mach/irqs.h>

/*
 * These timers are currently always setup to be clocked at 26MHz.
 */
#define CFG_TIMER_PRESCALE 1
#define BUSCLK_TO_TIMER_RELOAD(busclk)  (((busclk)/CFG_TIMER_PRESCALE)/HZ)
#define TIMER_RELOAD (BUSCLK_TO_TIMER_RELOAD(CONFIG_DEFAULT_TIMERCLK))

#if 0
static char *local_timer_clkname[] = {NULL, "clk_timer6", "clk_timer7", "clk_timer8"};
#endif

#define SC_PERIPH_CLKEN4    (0x630)
#define TIMER6_ENABLE_BIT	(1<<14)
#define TIMER7_ENABLE_BIT	(1<<16)
#define TIMER8_ENABLE_BIT	(1<<18)

static void local_timer_clkenable(int cpu)
{
#if 0/*modify for atomic panic*/
	struct clk *clk;
	int retval;

	clk = clk_get(NULL, local_timer_clkname[cpu]);
	if (IS_ERR(clk)) {
		printk("%s clk_get get %s failed\n", __FUNCTION__, local_timer_clkname[cpu]);
		return;
	}

	retval = clk_enable(clk);
	if (retval) {
		printk("%s clk_enable get %s failed\n", __FUNCTION__, local_timer_clkname[cpu]);
		return;
	}

#endif
	/*cpu1*/
	if (cpu == 1) {
		writel(TIMER6_ENABLE_BIT, IO_ADDRESS(SOC_AO_SCTRL_BASE_ADDR) + SC_PERIPH_CLKEN4);
	}

	if (cpu == 2) {
		writel(TIMER7_ENABLE_BIT, IO_ADDRESS(SOC_AO_SCTRL_BASE_ADDR) + SC_PERIPH_CLKEN4);
	}

	if (cpu == 3) {
		writel(TIMER8_ENABLE_BIT, IO_ADDRESS(SOC_AO_SCTRL_BASE_ADDR) + SC_PERIPH_CLKEN4);
	}

    return;
}

#define LOCAL_TIMER_DELCARE(cpuid, base, irqno) \
\
static void sp804_set_mode_ ## cpuid (enum clock_event_mode mode,\
        struct clock_event_device *evt)\
{\
	unsigned long ctrl = TIMER_CTRL_32BIT | TIMER_CTRL_IE;\
\
    writel(1, base + TIMER_INTCLR);\
	writel(ctrl, base + TIMER_CTRL);\
\
	switch (mode) {\
	case CLOCK_EVT_MODE_PERIODIC:\
		writel(TIMER_RELOAD, base + TIMER_LOAD);\
		ctrl |= TIMER_CTRL_PERIODIC | TIMER_CTRL_ENABLE;\
		break;\
\
	case CLOCK_EVT_MODE_ONESHOT:\
		ctrl |= TIMER_CTRL_ONESHOT;\
		break;\
\
	case CLOCK_EVT_MODE_UNUSED:\
	case CLOCK_EVT_MODE_SHUTDOWN:\
	default:\
		break;\
	}\
\
	writel(ctrl, base + TIMER_CTRL);\
\
    return;\
}\
\
static int sp804_set_next_event_ ## cpuid(unsigned long next,\
	struct clock_event_device *evt)\
{\
	unsigned long ctrl = readl(base + TIMER_CTRL);\
\
	writel(next, base + TIMER_LOAD);\
	writel(ctrl | TIMER_CTRL_ENABLE, base + TIMER_CTRL);\
\
	return 0;\
}\
\
static void sp804_clockevents_init_ ## cpuid(struct clock_event_device *evt)\
{\
	unsigned long ctrl = TIMER_CTRL_32BIT | TIMER_CTRL_IE;\
\
    writel(1, base + TIMER_INTCLR);\
	writel(ctrl, base+ TIMER_CTRL);\
	writel(TIMER_RELOAD, base + TIMER_LOAD);\
	ctrl |= TIMER_CTRL_PERIODIC | TIMER_CTRL_ENABLE;\
	writel(ctrl, base + TIMER_CTRL);\
\
	evt->name = "timer" __stringify(cpuid);\
    evt->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,\
	evt->rating = 300;\
	evt->shift = 32;\
	evt->set_mode = sp804_set_mode_ ## cpuid;\
	evt->set_next_event = sp804_set_next_event_ ## cpuid;\
\
	evt->mult = div_sc(CONFIG_DEFAULT_TIMERCLK, NSEC_PER_SEC, evt->shift);\
	evt->max_delta_ns = clockevent_delta2ns(0xffffffff, evt);\
	evt->min_delta_ns = clockevent_delta2ns(0xf, evt);\
\
	clockevents_register_device(evt);\
}\
\
static irqreturn_t local_timer_interrupt_ ## cpuid(int irq, void *dev_id)\
{\
	struct clock_event_device *evt = dev_id;\
	unsigned int cpu = smp_processor_id();\
\
	if ((readl(base + TIMER_RIS)) & 0x1) {\
		writel(1, base + TIMER_INTCLR);\
\
	    if (likely(cpu == cpuid))\
			evt->event_handler(evt);\
	}\
\
	return IRQ_HANDLED;\
}\
\
static struct irqaction local_timer_irq_ ## cpuid = {\
		.name		= "cpu" __stringify(cpuid) "-timer",\
		.flags		= IRQF_SHARED | IRQF_DISABLED | IRQF_TIMER,\
		.handler	= local_timer_interrupt_ ## cpuid,\
};\
\
static int cpu_irq_status_ ## cpuid = 0;\
\
static int __cpuinit local_timer_setup_ ## cpuid(struct clock_event_device *evt)\
{\
    /*printk("%s local timer setup on CPU %d\n", __FUNCTION__, cpuid);*/ \
\
	evt->irq = irqno;\
    local_timer_irq_ ## cpuid.dev_id = evt;\
\
	local_timer_clkenable(cpuid);\
\
	if(cpu_irq_status_ ## cpuid == 0) {\
		setup_irq(evt->irq, &local_timer_irq_ ## cpuid);\
		cpu_irq_status_ ## cpuid = 1;\
	}\
\
	irq_set_affinity(irqno, cpumask_of(cpuid));\
\
	sp804_clockevents_init_ ## cpuid(evt);\
\
	return 0;\
}\
\
static void local_timer_stop_ ## cpuid(struct clock_event_device *evt)\
{\
	if (cpu_irq_status_ ## cpuid == 1) {\
		remove_irq(evt->irq, &local_timer_irq_ ## cpuid);\
		cpu_irq_status_ ## cpuid = 0;\
	}\
\
	return;\
}\
\
static int __cpuinit localtimer_hotplug_notify_ ## cpuid(struct notifier_block *self,\
				      unsigned long action, void *hcpu)\
{\
	unsigned int cpu = (unsigned int) hcpu;\
\
    if (cpu != cpuid){\
        return NOTIFY_OK;\
    }\
\
	action &= 0xf;\
\
	switch (action) {\
		case CPU_ONLINE:\
			irq_set_affinity(irqno, cpumask_of(cpu));\
		default:\
			break;\
	}\
\
	return NOTIFY_OK;\
}\
\
static int __init localtimer_irq_affinity_init_ ## cpuid(void)\
{\
	/* Register hotplug notifier. */\
	hotcpu_notifier(localtimer_hotplug_notify_ ## cpuid, 0);\
\
	return 0;\
}\
module_init(localtimer_irq_affinity_init_ ## cpuid);

/*modify here when changing TIMER resources */
LOCAL_TIMER_DELCARE(1, IO_ADDRESS(REG_BASE_TIMER3), IRQ_TIMER6)
LOCAL_TIMER_DELCARE(2, IO_ADDRESS(REG_BASE_TIMER3 + 0x20), IRQ_TIMER7)
LOCAL_TIMER_DELCARE(3, IO_ADDRESS(REG_BASE_TIMER4), IRQ_TIMER8)

typedef int (*local_timer_setup_fn)(struct clock_event_device *evt);
static __cpuinitdata local_timer_setup_fn local_timer_setup_fns [] = {
    NULL,
    local_timer_setup_1,
    local_timer_setup_2,
    local_timer_setup_3
};

/*
 * Setup the local clock events for a CPU.
 */
int __cpuinit local_timer_setup(struct clock_event_device *evt)
{
    unsigned int cpu = smp_processor_id();
    local_timer_setup_fn setup_fn;

    if (0 == cpu) {
        /* FIXME: cpu0 timer already setup in timer.c */
        return 0;
    }

    setup_fn = local_timer_setup_fns[cpu];
    setup_fn(evt);

    return 0;
}

typedef void (*local_timer_stop_fn)(struct clock_event_device *evt);
static local_timer_stop_fn local_timer_stop_fns [] = {
    NULL,
    local_timer_stop_1,
    local_timer_stop_2,
    local_timer_stop_3
};

/*
 *using to stop per-cpu timer;using in kernel/arch/arm/kernel/smp.c
 * */
void local_timer_stop(struct clock_event_device *evt)
{
    unsigned int cpu = smp_processor_id();
    local_timer_stop_fn stop_fn;

    if (cpu == 0) {
        /*FIXME:local_timer_setup do nothing about the cup0's timer */
        return ;
    }

    stop_fn = local_timer_stop_fns[cpu];
    stop_fn(evt);

    return ;
}


