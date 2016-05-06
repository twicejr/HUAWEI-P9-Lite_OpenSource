/*
 * HI3630, driver for irq affinity recovery in smp system.
 * arch/arm/mach-hisi/hisi_irq_affinity.c
 *
 * Copyright (c) 2011-2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/smp.h>
#include <linux/cpumask.h>
#include <linux/notifier.h>
#include <linux/interrupt.h>
#include <linux/cpu.h>
#include <linux/slab.h>
#include <asm/irq.h>
//#include <asm/mach-types.h>

#define MODULE_NAME "[HISI IRQ AFFINITY]"

struct irq_affinity_info {
	struct list_head node;
	int cpu;
	unsigned int irq;
};

struct irq_affinity_list {
	struct list_head list;
	spinlock_t irqaff_lock;
};

struct irq_affinity_list irqaff_list[NR_CPUS];

void hisi_irqaffinity_status(void)
{
	struct irq_affinity_info *p = NULL;
	struct list_head *list = NULL;
	spinlock_t *list_lock = NULL;
	int cpu;

	printk("irq affinity ++\n");
	for (cpu = 0; cpu < NR_CPUS; cpu++) {
		list = &irqaff_list[cpu].list;
		list_lock = &irqaff_list[cpu].irqaff_lock;

		printk("cpu-%d: ", cpu);
		spin_lock(list_lock);
		list_for_each_entry(p, list, node) {
			spin_unlock(list_lock);
			printk("irq-%03d ", p->irq);
			spin_lock(list_lock);
		}
		spin_unlock(list_lock);

		printk("\n");
	}

	printk("irq affinity --\n");
	return;
}
EXPORT_SYMBOL_GPL(hisi_irqaffinity_status);

static struct irq_affinity_info *is_registered_irq(unsigned int irq)
{
	struct irq_affinity_info *p = NULL;
	struct list_head *list = NULL;
	spinlock_t *list_lock = NULL;
	int cpu, gotten = 0;

	for (cpu = 0; cpu < NR_CPUS; cpu++) {
		list = &irqaff_list[cpu].list;
		list_lock = &irqaff_list[cpu].irqaff_lock;

		spin_lock(list_lock);
		list_for_each_entry(p, list, node) {
			if (p->irq == irq) {
				gotten = 1;
				break;
			}
		}
		spin_unlock(list_lock);

		if (gotten)
			break;
	}

	return gotten ? p : NULL;
}

int hisi_irqaffinity_register(unsigned int irq, int cpu)
{
	struct irq_affinity_info *p = NULL;
	struct irq_affinity_info *_p = NULL;
	struct list_head *list = NULL;
	spinlock_t *list_lock = NULL;
	int ret = 0;

	if (cpu >= NR_CPUS) {
		pr_err(KERN_ERR MODULE_NAME " error cpu num %d\n", cpu);
		ret =  -EINVAL;
		goto out;
	}

	list = &irqaff_list[cpu].list;
	list_lock = &irqaff_list[cpu].irqaff_lock;

	_p = is_registered_irq(irq);

	/* registered */
	if (_p && (_p->cpu == cpu)) {
		pr_warn("irq-%u affinity have been registered on cpu-%d\n",
			irq, cpu);
		goto out;
	}

	/* transit */
	if(_p && (_p->cpu != cpu)) {
		pr_warn("Transit irq-%u from cpu-%d to cpu-%d\n",
			irq, _p->cpu, cpu);

		_p->cpu = cpu;

		(void)irq_set_affinity(irq, cpumask_of(cpu));

		spin_lock(list_lock);
		list_del(&_p->node);
		list_add_tail(&_p->node, list);
		spin_unlock(list_lock);

		goto out;
	}

	/* new */
	ret = irq_set_affinity(irq, cpumask_of(cpu));
	if (ret) {
		pr_err("Fail to register irq-%u affinity on cpu-%d, err %d\n",
			irq, cpu, ret);
		goto out;
	}

	p = kmalloc(sizeof(*p), GFP_KERNEL);
	if (!p) {
		pr_err(KERN_ERR MODULE_NAME " no mem\n");
		ret = -ENOMEM;
		goto out;
	}

	p->cpu = cpu;
	p->irq = irq;

	spin_lock(list_lock);
	list_add_tail(&p->node, list);
	spin_unlock(list_lock);

	pr_info("Register irq-%u affinity on cpu-%d\n", irq, cpu);
out:
	return ret;
}
EXPORT_SYMBOL_GPL(hisi_irqaffinity_register);

void hisi_irqaffinity_unregister(unsigned int irq)
{
	struct irq_affinity_info *p = NULL;
	struct list_head *list = NULL;
	spinlock_t *list_lock = NULL;
	int cpu, gotten = 0;

	for (cpu = 0; cpu < NR_CPUS; cpu++) {
		list = &irqaff_list[cpu].list;
		list_lock = &irqaff_list[cpu].irqaff_lock;

		spin_lock(list_lock);
		list_for_each_entry(p, list, node) {
			if (p->irq == irq) {
				gotten = 1;
				list_del(&p->node);
				kfree(p);
				break;
			}
		}
		spin_unlock(list_lock);

		if (gotten) {
			pr_info("Unregister irq-%u affinity on cpu-%d(->cpu-0)\n",
				irq, cpu);
			irq_set_affinity(irq, cpumask_of(0));
			break;
		}
	}

	if (!gotten) {
		pr_warn("Fail to unregister irq affinity,"
			"irq-%u affinity have never been registered.\n", irq);
	}

	return;
}
EXPORT_SYMBOL_GPL(hisi_irqaffinity_unregister);

static int __cpuinit
hisi_irqaffinity_hotplug_notify(struct notifier_block *self,
				 unsigned long action, void *hcpu)
{
	struct irq_affinity_info *p = NULL;
	unsigned int cpu = (unsigned int)(long)hcpu;
	struct list_head *list = &irqaff_list[cpu].list;
	spinlock_t *list_lock = &irqaff_list[cpu].irqaff_lock;

	switch (action & 0xf) {
	case CPU_ONLINE:
		spin_lock(list_lock);
		list_for_each_entry(p, list, node) {
			if (p->cpu == cpu) {
				spin_unlock(list_lock);
				irq_set_affinity(p->irq, cpumask_of(cpu));
				pr_info("Recover irq-%u affinity on cpu-%d\n",
					p->irq, cpu);
				spin_lock(list_lock);
			}
		}
		spin_unlock(list_lock);
	default:
		break;
	}

	return NOTIFY_OK;
}

static int __init hisi_irqaffinity_init(void)
{
	int cpu;

	/* Initialize irq affinity list for each cpu. */
	for (cpu = 0; cpu < NR_CPUS; cpu++) {
		INIT_LIST_HEAD(&irqaff_list[cpu].list);
		spin_lock_init(&irqaff_list[cpu].irqaff_lock);
	}

	/* Register hotplug event notifier. */
	hotcpu_notifier(hisi_irqaffinity_hotplug_notify, 0);

	return 0;
}
core_initcall(hisi_irqaffinity_init);

MODULE_DESCRIPTION("HI3630, driver for irq affinity recovery in smp system.");
MODULE_LICENSE("GPL V2");
