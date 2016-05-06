/*
 * test_hi64xx_irq.c  --  Unit test for hi64xx_irq
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/debugfs.h>

#include <linux/hisi/hi64xx/hi64xx_irq.h>


static struct of_device_id of_test_hi64xx_irq[] = {
	{
		.compatible = "hisilicon,test-hi64xx-irq",
	},
	{ /* end */ }
};

static struct hi64xx_irq_map test_irq_map = {
	.irq_num = 32
};

static struct hi64xx_irq *hi64xx_irq_data = NULL;
static struct device *test_device;

irqreturn_t test_irq_handler(int irq, void *data)
{
	dev_info(test_device, "handle irq %d", irq);
	return IRQ_HANDLED;
}


static ssize_t do_test_write(struct file *file, const char __user *user_buf,
			size_t count, loff_t *ppos)
{
	char cmdbuf[64] = {0};
	char irqname[16] = {0};
	int ret;
	int irq;
	int i;

	if (count >= sizeof(cmdbuf))
		count = sizeof(cmdbuf) - 1;

	if(copy_from_user(cmdbuf, user_buf, count))
		pr_warn("test_hi64xx_irq: user buffer is not completely copied");

	ret = kstrtoint(cmdbuf, 10, &irq);
	if (ret != 0) {
		pr_err("test_hi64xx_irq: invalid input");
		return 0;
	}

	if (irq == 255) {
		ret = hi64xx_irq_init_irq(hi64xx_irq_data, &test_irq_map);
		if (ret) {
			dev_err(test_device, "hi64xx_irq_init_irq failed: %d", ret);
		} else {
			dev_info(test_device, "hi64xx_irq_init_irq OK");
		}
	} else if (irq == 254) {
		int irqs[] = {0, 7, 8, 15, 16, 23, 24, 31};

		for (i = 0; i < ARRAY_SIZE(irqs); i++) {
			snprintf(irqname, sizeof(irqname) - 1, "testirq%d", irqs[i]);
			ret = hi64xx_irq_request_irq(hi64xx_irq_data,
				irqs[i], test_irq_handler, irqname, NULL);
			if (ret)
				dev_info(test_device, "hi64xx_irq_request_irq failed: %d", ret);
		}
		hi64xx_irq_disable_irqs(hi64xx_irq_data, ARRAY_SIZE(irqs), irqs);

		hi64xx_irq_enable_irqs(hi64xx_irq_data, ARRAY_SIZE(irqs), irqs);

		hi64xx_irq_disable_irqs(hi64xx_irq_data, ARRAY_SIZE(irqs), irqs);
	} else {
		snprintf(irqname, sizeof(irqname) - 1, "testirq%d", irq);

		ret = hi64xx_irq_request_irq(hi64xx_irq_data, irq, test_irq_handler, irqname, NULL);
		if (ret)
			dev_info(test_device, "hi64xx_irq_request_irq failed: %d", ret);

		ret = hi64xx_irq_disable_irq(hi64xx_irq_data, irq);
		if (ret)
			dev_info(test_device, "hi64xx_irq_disable_irq failed: %d", ret);

		ret = hi64xx_irq_enable_irq(hi64xx_irq_data, irq);
		if (ret)
			dev_info(test_device, "hi64xx_irq_enable_irq failed: %d", ret);

		ret = hi64xx_irq_disable_irq(hi64xx_irq_data, irq);
		if (ret)
			dev_info(test_device, "hi64xx_irq_disable_irq failed: %d", ret);
	}

	return count;
}

static const struct file_operations do_test_fops = {
	.write = do_test_write,
};

static int test_hi64xx_irq_probe(struct platform_device *pdev)
{
	struct dentry *dbg_fs_dir;

	hi64xx_irq_data = (struct hi64xx_irq *)dev_get_drvdata(pdev->dev.parent);

	if (hi64xx_irq_data == NULL) {
		dev_err(&pdev->dev, "hi64xx_irq_data is NULL");
		return -EINVAL;
	}

	test_device = &pdev->dev;

	dbg_fs_dir = debugfs_create_dir("hi64xx_irq", NULL);
	if (!dbg_fs_dir)
		return -EINVAL;

	if (!debugfs_create_file("test", 0644, dbg_fs_dir, NULL, &do_test_fops))
		dev_err(&pdev->dev, "failed to create debugfs node\n");

	return 0;
}

static int test_hi64xx_irq_remove(struct platform_device *pdev)
{
	return 0;
}

static struct platform_driver test_hi64xx_irq_driver = {
	.driver = {
		.name	= "test_hi64xx_irq",
		.owner  = THIS_MODULE,
		.of_match_table = of_test_hi64xx_irq,
	},
	.probe		= test_hi64xx_irq_probe,
	.remove		= test_hi64xx_irq_remove

};

static int __init test_hi64xx_irq_init(void)
{
	return platform_driver_register(&test_hi64xx_irq_driver);
}

static void __exit test_hi64xx_irq_exit(void)
{
	platform_driver_unregister(&test_hi64xx_irq_driver);
}

module_init(test_hi64xx_irq_init);
module_exit(test_hi64xx_irq_exit);

MODULE_AUTHOR("dingqing <dingqing@hisilicon.com>");
MODULE_DESCRIPTION("test hi64xx_resmgr");
MODULE_LICENSE("GPL");
