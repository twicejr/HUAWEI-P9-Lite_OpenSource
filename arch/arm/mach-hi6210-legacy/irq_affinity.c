/*
 *  arch/arm/mach-hi660/irq_affinity.c
 *
 *  Copyright (C) 2011 Hisilicon Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/smp.h>
#include <linux/cpumask.h>
#include <linux/notifier.h>
#include <linux/interrupt.h>
#include <linux/cpu.h>
#include <asm/irq.h>
#include <mach/irqs.h>
#include <mach/util.h>
#include <linux/seq_file.h>

static unsigned int irq_affinity_records[NR_IRQS];
static struct irq_affinity_notify notifiers[NR_IRQS];

static int restore_irq_affinity_record(unsigned int cpu)
{
    unsigned int i;
    int ret = 0;

    for (i = 0; i < NR_IRQS; i++){
        if (cpu != irq_affinity_records[i])
            continue;

        ret = irq_set_affinity(i, cpumask_of(cpu));
        if (ret)
            printk("%s : fail to restore IRQ %d on CPU %d\n", __FUNCTION__, i, cpu);
    }

    return ret;
}

static int cpu_up_notify(struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
    unsigned int cpu = (unsigned int)cpuid;

    switch(status){
        case CPU_ONLINE:
            restore_irq_affinity_record(cpu);
            break;
        default:
            /*just pass other event*/
            break;
    }

    return NOTIFY_DONE;
}

static struct notifier_block __refdata cpu_up_notifier = {
    .notifier_call = cpu_up_notify,
};

static void irq_affinity_notifier(struct irq_affinity_notify *notify, const cpumask_t *mask)
{
	unsigned int cpu = cpumask_first(mask);
    unsigned int irq = notify->irq;

    irq_affinity_records[irq] = cpu;

    return;
}

/*follow irq affinity setting event*/
static int __init follow_irq_affinity(int irq)
{
    struct irq_affinity_notify *notify;
    int ret;

    notify = &notifiers[irq];

    memset((void *)notify, 0, sizeof(struct irq_affinity_notify));
    notify->notify = irq_affinity_notifier;

	ret = irq_set_affinity_notifier(irq, notify);
	if (ret){
        printk("%s : fail to set irq affinity notifier %d\n", __FUNCTION__, ret);
        return -1;
	}

    return 0;
}

static int __initdata irq_affinity_disabled = 0; /*1 : disabled , 0 : enabled*/
static int __init irq_affinity_disable(char *__unused)
{
	irq_affinity_disabled = 1;

	return 0;
}
early_param("no_irq_affinity", irq_affinity_disable);

static int __init irq_affinity_init(void)
{
    int i;

    if (1 == irq_affinity_disabled)
        return 0;

    for (i = 0; i < NR_IRQS; i++){
        /*follow this irq*/
        follow_irq_affinity(i);

        /*init the records. as default, irqs bonds to CPU0*/
        irq_affinity_records[i] = 0;
    }

    register_hotcpu_notifier(&cpu_up_notifier);

	return 0;
}
postcore_initcall(irq_affinity_init);


static int proc_irq_affinity_record_show(struct seq_file *m, void *v)
{
    int i;

    seq_printf(m, "irq affinity record : \n");
    for(i = 0; i < NR_IRQS ; i++){
	    seq_printf(m, "IRQ [%3d] CPU [%u]\n", i, irq_affinity_records[i]);
    }
    seq_printf(m, "end.\n");

	return 0;
}

static int proc_irq_affinity_record_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_irq_affinity_record_show, NULL);
}

static const struct file_operations proc_irq_affinity_record_fops = {
	.open = proc_irq_affinity_record_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init proc_irq_affinity_record_init(void)
{
    return 0;

    balong_create_stats_proc_entry("irq_affinity", S_IRUGO, &proc_irq_affinity_record_fops, NULL);

	return 0;
}
module_init(proc_irq_affinity_record_init);

static void __exit proc_irq_affinity_record_exit(void)
{
	return;
}
module_exit(proc_irq_affinity_record_exit);

MODULE_DESCRIPTION("IRQ Affinity Set/Restore Module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");

