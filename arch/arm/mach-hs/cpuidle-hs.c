/*
 * Copyright (c) 2013 Hisilicon Limited.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cpuidle.h>

#include <asm/cpuidle.h>

static struct cpuidle_driver hs_idle_driver = {
	.name = "hs_idle",
	.owner = THIS_MODULE,
	.state_count = 1,
	.states = {
		[0] = ARM_CPUIDLE_WFI_STATE_PWR(600),
	},
};

static DEFINE_PER_CPU(struct cpuidle_device, hs_idle_device);

int __init hs_cpuidle_init(void)
{
	int ret;
	unsigned int cpu;
	struct cpuidle_device *dev;
	struct cpuidle_driver *drv = &hs_idle_driver;

	ret = cpuidle_register_driver(&hs_idle_driver);
	if (ret) {
		pr_err("CPUidle driver registration failed\n");
		return ret;
	}

	for_each_possible_cpu(cpu) {
		dev = &per_cpu(hs_idle_device, cpu);
		dev->cpu = cpu;

		dev->state_count = drv->state_count;
		ret = cpuidle_register_device(dev);
		if (ret) {
			pr_err("CPU%u: CPUidle device registration failed\n",
				cpu);
			return ret;
		}
	}
	return 0;
}
device_initcall(hs_cpuidle_init);
