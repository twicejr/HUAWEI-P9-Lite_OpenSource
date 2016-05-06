/*
 * hisi_hwspinlock driver for hisi hardware_hwspinlock_lock
 *
 * Copyright (C) 20013-2014 hisilicon. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/pm_runtime.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/hwspinlock.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>

#include "hwspinlock_internal.h"

#define	MODULE_NAME			"hisi_hwspinlock"

/*
 * CPU ID for master running hisi kernel.
 * hwspinlocks should only be used to synchonise operations
 * between the Cortex A_x core and the other CPUs.  Hence
 * forcing the masterID to a preset value.
 */
#define	MASTER_ID			0x01
#define	LOCK_CMD			((MASTER_ID << 1) | 0x01)

#define	ID_MASK				0x0f

/*lint -e750 -esym(750,*)*/
#define	UNLOCK_OFFSET			0x04
#define	LOCK_ST_OFFSET			0x08
/*lint -e750 +esym(750,*)*/
struct hisi_hwspinlock {
	int id_in_group;
	void __iomem *address;
};

static int lock_bits_g;

static int hisi_hwspinlock_trylock(struct hwspinlock *lock)
{
	struct hisi_hwspinlock *lock_temp = (struct hisi_hwspinlock *)(lock->priv);
	void __iomem *lock_addr = lock_temp->address;
	int num_in_group = lock_temp->id_in_group;
	unsigned int status;

	writel(LOCK_CMD << (num_in_group * lock_bits_g), lock_addr);
	status = readl(lock_addr + LOCK_ST_OFFSET) >> (num_in_group * lock_bits_g);

	/* get only fourth (lock_bits_g) bits and compare to masterID.
	 * if equal, we have the lock, otherwise
	 * someone else has it.
	 */
	return (LOCK_CMD == (ID_MASK & status));
}

static void hisi_hwspinlock_unlock(struct hwspinlock *lock)
{
	struct hisi_hwspinlock *lock_temp = (struct hisi_hwspinlock *)(lock->priv);
	void __iomem *lock_addr = lock_temp->address;
	int num_in_group = lock_temp->id_in_group;

	/* release the lock by writing LOCK_CMD to it */
	writel(LOCK_CMD << (num_in_group * lock_bits_g), lock_addr + UNLOCK_OFFSET);
}

/*
 * hisi: what value is recommended here ?
 */
static void hisi_hwspinlock_relax(struct hwspinlock *lock)
{
	ndelay(50);
}

static const struct hwspinlock_ops hisi_hwspinlock_ops = {
	.trylock	= hisi_hwspinlock_trylock,
	.unlock		= hisi_hwspinlock_unlock,
	.relax		= hisi_hwspinlock_relax,
};

static struct of_device_id hisi_hwlock_of_match[];

static int hisi_hwspinlock_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = pdev->dev.of_node;
	struct hwspinlock_device *bank;
	struct hwspinlock *hwlock;
	void __iomem *hwspinlock_base;
	struct device_node *np_pctrl;
	int i, ret, num_lock, register_width, lock_groups, locks_per_register;
	unsigned int *addr;
	struct hisi_hwspinlock *hwspinlock_info;

	np_pctrl = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
	if (!np_pctrl) {
		dev_err(dev, "no find pctrl node!\n");
		return -EINVAL;
	}

	hwspinlock_base = of_iomap(np_pctrl, 0);
	if (!hwspinlock_base) {
		dev_err(dev, "failed to iomap!\n");
		of_node_put(np_pctrl);
		return -ENOMEM;
	}

	ret = of_property_read_u32(np, "hwlock,register-width", &register_width);
	if (ret) {
		dev_err(dev, "no find 'hwlock,register-width' property!\n");
		goto iounmap_base;
	}

	ret = of_property_read_u32(np, "hwlock,bits-per-single", &lock_bits_g);
	if (ret) {
		dev_err(dev, "no find 'hwlock,bits-per-single' property!\n");
		goto iounmap_base;
	}

	ret = of_property_read_u32(np, "hwlock,groups", &lock_groups);
	if (ret) {
		dev_err(dev, "no find 'hwlock,groups' property!\n");
		goto iounmap_base;
	}

	locks_per_register = register_width / lock_bits_g;
	num_lock = locks_per_register * lock_groups;

	bank = devm_kzalloc(dev, sizeof(*bank) + num_lock * sizeof(*hwlock), GFP_KERNEL);
	if (!bank) {
		ret = -ENOMEM;
		goto iounmap_base;
	}

	addr = devm_kzalloc(dev, lock_groups * sizeof(unsigned int), GFP_KERNEL);
	if (!addr) {
		ret = -ENOMEM;
		goto iounmap_base;
	}

	hwspinlock_info = devm_kzalloc(dev, num_lock * sizeof(*hwspinlock_info), GFP_KERNEL);
	if (!hwspinlock_info) {
		ret = -ENOMEM;
		goto iounmap_base;
	}

	ret = of_property_read_u32_array(np, "hwlock,offset", addr, lock_groups);
	if (ret) {
		dev_err(dev, "no find 'hwlock,offset' property!\n");
		goto iounmap_base;
	}
	for (i = 0, hwlock = &bank->lock[0]; i < num_lock; i++, hwlock++, hwspinlock_info++) {
		hwspinlock_info->id_in_group = i % locks_per_register;
		hwspinlock_info->address = hwspinlock_base + addr[i / locks_per_register];
		hwlock->priv = hwspinlock_info;
	}

	platform_set_drvdata(pdev, bank);
	/*
	 * runtime PM will make sure the clock of this module is
	 * enabled iff at least one lock is requested
	 */
	pm_runtime_enable(dev);

	ret = hwspin_lock_register(bank, dev, &hisi_hwspinlock_ops,
						0, num_lock);
	if (ret)
		goto reg_fail;

	of_node_put(np_pctrl);

	dev_info(dev, "init ok.\n");
	return 0;

reg_fail:
	pm_runtime_disable(dev);
iounmap_base:
	iounmap(hwspinlock_base);
	of_node_put(np_pctrl);
	return ret;
}

static int hisi_hwspinlock_remove(struct platform_device *pdev)
{
	struct hwspinlock_device *bank = platform_get_drvdata(pdev);
	struct hisi_hwspinlock *lock_temp;
	void __iomem *hwspinlock_base;
	int ret;

	if (NULL == bank) {
		return -EFAULT;
	}

	lock_temp = (struct hisi_hwspinlock *)(bank->lock[0].priv);
	hwspinlock_base = lock_temp->address - 0x400;

	ret = hwspin_lock_unregister(bank);
	if (ret) {
		dev_err(&pdev->dev, "hwspinlcoks failed to unregister!\n");
		return ret;
	}

	pm_runtime_disable(&pdev->dev);
	iounmap(hwspinlock_base);

	return 0;
}

static struct of_device_id hisi_hwlock_of_match[] = {
	{ .compatible = "hisilicon,hwspinlock" },
	{ },
};
MODULE_DEVICE_TABLE(of, hisi_hwlock_of_match);

static struct platform_driver hisi_hwspinlock_driver = {
	.probe		= hisi_hwspinlock_probe,
	.remove		= hisi_hwspinlock_remove,
	.driver		= {
		.name	= MODULE_NAME,
		.owner	= THIS_MODULE,
		.of_match_table	= of_match_ptr(hisi_hwlock_of_match),
	},
};

static int __init hisi_hwspinlock_init(void)
{
	return platform_driver_register(&hisi_hwspinlock_driver);
}
/* board init code might need to reserve hwspinlocks for predefined purposes */
arch_initcall(hisi_hwspinlock_init);

static void __exit hisi_hwspinlock_exit(void)
{
	platform_driver_unregister(&hisi_hwspinlock_driver);
}
module_exit(hisi_hwspinlock_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hardware Spinlock driver for hisi");
MODULE_AUTHOR("w00221409 <hw.wangxiaoyin@huawei.com>");
