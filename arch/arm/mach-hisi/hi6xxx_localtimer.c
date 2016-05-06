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
/*#include <mach/early-debug.h>*/
#include <linux/hisi/hi6xxx-platform.h>
#include <linux/hisi/hi6xxx-iomap.h>                   /* For IO_ADDRESS access */
/*#include <mach/hisi_cortex-a9.h>*/
#include <soc_irqs.h>
#include <soc_ao_sctrl_interface.h>
#include <soc_baseaddr_interface.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>

#define CONFIG_DEFAULT_TIMERCLK 19200000
static void __iomem *ao_sctrl_base = NULL;
/*
 * These timers are currently always setup to be clocked at 26MHz.
 */
#define CFG_TIMER_PRESCALE 1
#define BUSCLK_TO_TIMER_RELOAD(busclk)  (((busclk)/CFG_TIMER_PRESCALE)/HZ)
#define TIMER_RELOAD (BUSCLK_TO_TIMER_RELOAD(CONFIG_DEFAULT_TIMERCLK))

#define TIMER6_ENABLE_BIT	(1<<SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_18pclk_timer3_START)
#define TIMER7_ENABLE_BIT	(1<<SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_18pclk_timer3_START)
#define TIMER8_ENABLE_BIT	(1<<SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_19pclk_timer4_START)
#define TIMER12_ENABLE_BIT	(1<<SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_21pclk_timer6_START)

#define TIMER14_ENABLE_BIT	(1<<SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_22pclk_timer7_START)
#define TIMER15_ENABLE_BIT	(1<<SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_22pclk_timer7_START)
#define TIMER16_ENABLE_BIT	(1<<SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_23pclk_timer8_START)
#define TIMER17_ENABLE_BIT	(1<<SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_23pclk_timer8_START)

static void __iomem * time0_base;
static void __iomem * time1_base;
static void __iomem * time2_base;
static void __iomem * time3_base;
static void __iomem * time4_base;
static void __iomem * time5_base;
static void __iomem * time6_base;
static void __iomem * time7_base;

void local_timer_clkenable(int cpu)
{
   /*cpu0*/
	if (cpu == 0) {
		writel(TIMER12_ENABLE_BIT, SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(ao_sctrl_base));
	}

	/*cpu1*/
	if (cpu == 1) {
		writel(TIMER6_ENABLE_BIT, SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(ao_sctrl_base));
	}

	if (cpu == 2) {
		writel(TIMER7_ENABLE_BIT, SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(ao_sctrl_base));
	}

	if (cpu == 3) {
		writel(TIMER8_ENABLE_BIT, SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(ao_sctrl_base));
	}
	if (cpu == 4) {
		writel(TIMER14_ENABLE_BIT, SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(ao_sctrl_base));
	}

	if (cpu == 5) {
		writel(TIMER15_ENABLE_BIT, SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(ao_sctrl_base));
	}

	if (cpu == 6) {
		writel(TIMER16_ENABLE_BIT, SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(ao_sctrl_base));
	}

	if (cpu == 7) {
		writel(TIMER17_ENABLE_BIT, SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(ao_sctrl_base));
	}
    return;
}

#define LOCAL_TIMER_DELCARE(cpuid, base, irqno) \
static void __iomem * timer_base_ ## cpuid = 0; \
\
static void sp804_set_mode_ ## cpuid (enum clock_event_mode mode,\
        struct clock_event_device *evt)\
{\
	unsigned long ctrl = TIMER_CTRL_32BIT | TIMER_CTRL_IE;\
\
    /*printk(KERN_ERR"local_timer_set_mode cpu:%d mode:%d\n", cpuid, mode);*/\
    writel(1, timer_base_ ## cpuid + TIMER_INTCLR);\
	writel(ctrl, timer_base_ ## cpuid + TIMER_CTRL);\
\
	switch (mode) {\
	case CLOCK_EVT_MODE_PERIODIC:\
		writel(TIMER_RELOAD, timer_base_ ## cpuid + TIMER_LOAD);\
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
	writel(ctrl, timer_base_ ## cpuid + TIMER_CTRL);\
\
    return;\
}\
\
static int sp804_set_next_event_ ## cpuid(unsigned long next,\
	struct clock_event_device *evt)\
{\
	unsigned long ctrl = readl(timer_base_ ## cpuid + TIMER_CTRL);\
\
	writel(next, timer_base_ ## cpuid + TIMER_LOAD);\
	writel(ctrl | TIMER_CTRL_ENABLE, timer_base_ ## cpuid + TIMER_CTRL);\
\
	return 0;\
}\
\
static void sp804_clockevents_init_ ## cpuid(struct clock_event_device *evt)\
{\
	unsigned long ctrl = TIMER_CTRL_32BIT | TIMER_CTRL_IE;\
\
    writel(1, timer_base_ ## cpuid + TIMER_INTCLR);\
	writel(ctrl, timer_base_ ## cpuid + TIMER_CTRL);\
	writel(TIMER_RELOAD, timer_base_ ## cpuid + TIMER_LOAD);\
	ctrl |= TIMER_CTRL_PERIODIC | TIMER_CTRL_ENABLE;\
	writel(ctrl, timer_base_ ## cpuid + TIMER_CTRL);\
\
	evt->name = "timer" __stringify(cpuid);\
    evt->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT | \
        CLOCK_EVT_FEAT_C3STOP,\
	evt->rating = 450;\
	/*evt->shift = 32;*/\
	evt->set_mode = sp804_set_mode_ ## cpuid;\
	evt->set_next_event = sp804_set_next_event_ ## cpuid;\
\
    clockevents_config_and_register(evt, CONFIG_DEFAULT_TIMERCLK,\
					0xf, 0x7fffffff);\
}\
\
static irqreturn_t local_timer_interrupt_ ## cpuid(int irq, void *dev_id)\
{\
	struct clock_event_device *evt = dev_id;\
	unsigned int cpu = smp_processor_id();\
\
	if ((readl(timer_base_ ## cpuid + TIMER_RIS)) & 0x1) {\
		writel(1, timer_base_ ## cpuid + TIMER_INTCLR);\
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
static int cpu_enter_cnt_ ## cpuid = 0;\
\
static int __cpuinit local_timer_setup_ ## cpuid(struct clock_event_device *evt)\
{\
    /*printk("%s local timer setup on CPU %d\n", __FUNCTION__, cpuid);*/ \
    if (timer_base_ ## cpuid == 0){ \
        timer_base_ ## cpuid = base; \
    }\
\
    evt->irq = irqno;\
    local_timer_irq_ ## cpuid.dev_id = evt;\
\
    local_timer_clkenable(cpuid);\
\
    if(0 == cpu_enter_cnt_ ## cpuid) {\
		if(cpu_irq_status_ ## cpuid == 0) {\
	        cpu_enter_cnt_ ## cpuid = 1;\
			setup_irq(evt->irq, &local_timer_irq_ ## cpuid);\
			cpu_irq_status_ ## cpuid = 1;\
		}\
	} else \
	{\
		if(cpu_irq_status_ ## cpuid == 0) {\
			enable_irq(evt->irq);\
			cpu_irq_status_ ## cpuid = 1;\
		}\
	} \
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
    printk(KERN_ERR"local_timer_stop cpu:%d\n", cpuid);\
	if (cpu_irq_status_ ## cpuid == 1) {\
		/*remove_irq(evt->irq, &local_timer_irq_ ## cpuid);*/\
		disable_irq(evt->irq);\
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
LOCAL_TIMER_DELCARE(0, time0_base, IRQ_TIMER12)
LOCAL_TIMER_DELCARE(1, time1_base, IRQ_TIMER6)
LOCAL_TIMER_DELCARE(2, time2_base, IRQ_TIMER7)
LOCAL_TIMER_DELCARE(3, time3_base, IRQ_TIMER8)
LOCAL_TIMER_DELCARE(4, time4_base, IRQ_TIMER14)
LOCAL_TIMER_DELCARE(5, time5_base, IRQ_TIMER15)
LOCAL_TIMER_DELCARE(6, time6_base, IRQ_TIMER16)
LOCAL_TIMER_DELCARE(7, time7_base, IRQ_TIMER17)

typedef int (*local_timer_setup_fn)(struct clock_event_device *evt);
static __cpuinitdata local_timer_setup_fn local_timer_setup_fns [] = {
    local_timer_setup_0,
    local_timer_setup_1,
    local_timer_setup_2,
    local_timer_setup_3,
    local_timer_setup_4,
    local_timer_setup_5,
    local_timer_setup_6,
    local_timer_setup_7    
};

/*
 * Setup the local clock events for a CPU.
 */
int __cpuinit local_timer_setup(struct clock_event_device *evt)
{
    unsigned int cpu = smp_processor_id();
    local_timer_setup_fn setup_fn;

    printk(KERN_ERR"local_timer_setup cpu:%d\n", cpu);
#if 0
    if (0 == cpu) {
        /* FIXME: cpu0 timer already setup in timer.c */
        return 0;
    }
#endif
    setup_fn = local_timer_setup_fns[cpu];
    setup_fn(evt);

    return 0;
}

typedef void (*local_timer_stop_fn)(struct clock_event_device *evt);
static local_timer_stop_fn local_timer_stop_fns [] = {
    local_timer_stop_0,
    local_timer_stop_1,
    local_timer_stop_2,
    local_timer_stop_3,
    local_timer_stop_4,
    local_timer_stop_5,
    local_timer_stop_6,
    local_timer_stop_7    
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

static struct local_timer_ops hisi_lt_ops __cpuinitdata = {
	.setup	= local_timer_setup,
	.stop	= local_timer_stop,
};

int hisi_local_timer_register(void)
{
    int err = 0;
    u32 local_timer = 0;
    struct device_node *root;
    struct device_node *node;

	node = of_find_compatible_node(NULL, NULL,"hisilicon,aosctrl");
	if (node)
		ao_sctrl_base = of_iomap(node, 0);
	else {
		BUG_ON(NULL == ao_sctrl_base);
		return -EFAULT;
	}

	root = of_find_compatible_node(NULL,NULL,"hisilicon,hi6210");
	if (!root){
		pr_err("[%s] find root node fail!\n",
			__func__);
		return err;
	}

	if (of_property_read_u32(root, "power,localtimer", &local_timer)) {
		pr_err("[%s] node doesn't have this property!\n", __func__);
		return err;
	}

	if (1 == local_timer) {
		err = local_timer_register(&hisi_lt_ops);
		if (err)
			printk(KERN_ERR"register local timer failed!!! err code:%d\n", err);
	}
	time0_base = ioremap(SOC_Timer6_BASE_ADDR, SZ_4K);
	time1_base = ioremap(SOC_Timer3_BASE_ADDR, SZ_4K);
	time2_base = time1_base + 0x20;
	time3_base = ioremap(SOC_Timer4_BASE_ADDR, SZ_4K);
	time4_base = ioremap(SOC_Timer7_BASE_ADDR, SZ_4K);
	time5_base = time4_base + 0x20;
	time6_base = ioremap(SOC_Timer8_BASE_ADDR, SZ_4K);
	time7_base = time6_base + 0x20;	

    return err;
}
