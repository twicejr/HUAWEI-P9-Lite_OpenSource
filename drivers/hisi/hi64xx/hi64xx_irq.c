/*
 * hi64xx_irq.c  --  Interrupt controller support for Hisilicon HI64xx
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/wakelock.h>
#include <linux/mutex.h>
#include <linux/clk.h>
#include <linux/irq.h>
#include <linux/clk-private.h>
#include <dsm/dsm_pub.h>
#include <hisi/hilog.h>
#include <linux/hisi/hi64xx/hi_cdc_ctrl.h>
#include <linux/hisi/hi64xx/hi64xx_irq.h>
#include <linux/hisi/hi64xx_hifi_misc.h>

#ifndef NO_IRQ
#define NO_IRQ 0
#endif

/* definition of platform data */
struct hi64xx_irq_platform_data {
	/* public data */
	struct hi64xx_irq hi64xx_irq;
	/* irq controller */
	struct irq_domain *domain;
	/* irq id of interrupt controller */
	unsigned int irq_id;
	/* sub irq ids */
	unsigned int sub_irq_id[HI64XX_MAX_IRQS_NUM];
	/* mutex for irq thread handler */ /* not sure */
	struct mutex handler_mutex;
	/* mutex for irq_mask & irq_source */
	struct mutex irq_lock;
	/* mutex for sr */
	struct mutex sr_lock;
	/* wake lock for irq thread handler */
	struct wake_lock wake_lock;
	/* used to mask sub irqs */
	u8 irq_mask[HI64XX_MAX_IRQ_REGS_NUM];
	/* used to clear sub irqs */
	u8 irq_source[HI64XX_MAX_IRQ_REGS_NUM];
	/* phy irqs map */
	struct hi64xx_irq_map phy_irq_map;
	/* hi_cdc_ctrl */
	struct hi_cdc_ctrl *hi_cdc;
};

static struct of_device_id of_hi64xx_irq_match[] = {
	{
		.compatible = "hisilicon,hi64xx-irq",
	},
	{ /* end */ },
};
MODULE_DEVICE_TABLE(of, of_hi64xx_irq_match);

static irqreturn_t hi64xx_irq_handler(int irq, void *data)
{
	disable_irq_nosync(irq);
	return IRQ_WAKE_THREAD;
}

static irqreturn_t hi64xx_irq_handler_thread(int irq, void *data)
{
	struct hi64xx_irq_platform_data *hi64xx_irq = (struct hi64xx_irq_platform_data *)data;
	unsigned long pending = 0;
	/* irq index in single irq register */
	int irq_index = 0;
	/* offset of different irq registers */
	int irq_index_offset = 0;
	int i = 0;
	int irq_regs_num = 0;

	if (!hi64xx_irq) {
		pr_err("%s: hi64xx_irq_platform_data is null\n", __FUNCTION__);
		return IRQ_HANDLED;
	}

	irq_regs_num = hi64xx_irq->phy_irq_map.irq_num / HI64XX_IRQ_REG_BITS_NUM;

	mutex_lock(&hi64xx_irq->sr_lock);
	wake_lock(&hi64xx_irq->wake_lock);

	for (i = 0; i < irq_regs_num; i++) {
		/* 8 irqs in each irq register */
		irq_index_offset = i * HI64XX_IRQ_REG_BITS_NUM;
		/* get irq status */
		pending = hi_cdcctrl_reg_read(hi64xx_irq->hi_cdc, hi64xx_irq->phy_irq_map.irq_regs[i]);
		/* get irq status with irq mask status */
		pending &= (~hi_cdcctrl_reg_read(hi64xx_irq->hi_cdc, hi64xx_irq->phy_irq_map.irq_mask_regs[i]));
		/* clr all unmask irqs */
		hi_cdcctrl_reg_write(hi64xx_irq->hi_cdc, hi64xx_irq->phy_irq_map.irq_regs[i], pending);

		/* handle each irq */
		if (pending)
			for_each_set_bit(irq_index, &pending, HI64XX_IRQ_REG_BITS_NUM)
					handle_nested_irq(hi64xx_irq->sub_irq_id[irq_index + irq_index_offset]);
	}

	wake_unlock(&hi64xx_irq->wake_lock);
	mutex_unlock(&hi64xx_irq->sr_lock);
	enable_irq(irq);

	return IRQ_HANDLED;
}

static void _irq_mask(struct hi64xx_irq_platform_data *data, unsigned long phy_irq)
{
	int index = phy_irq >> 3;

	if (index >= data->phy_irq_map.irq_num / HI64XX_IRQ_REG_BITS_NUM)
	{
		pr_err("%s: phy_irq %lu out of range\n", __FUNCTION__, phy_irq);
		return;
	}
	data->irq_mask[index] |= (u8)(1 << (phy_irq & 0x07));
}

static void _irq_unmask(struct hi64xx_irq_platform_data *data, unsigned long phy_irq)
{
	int index = phy_irq >> 3;

	if (index >= data->phy_irq_map.irq_num / HI64XX_IRQ_REG_BITS_NUM)
	{
		pr_err("%s: phy_irq %lu out of range\n", __FUNCTION__, phy_irq);
		return;
	}
	data->irq_mask[index] &= ~(u8)(1 << (phy_irq & 0x07));
	data->irq_source[index] |= (u8)(1 << (phy_irq & 0x07));
}

static void _irq_state_sync(struct hi64xx_irq_platform_data *data)
{
	int i = 0;

	for (i = 0; i < data->phy_irq_map.irq_num / HI64XX_IRQ_REG_BITS_NUM; i++) {
		hi_cdcctrl_reg_write(data->hi_cdc, data->phy_irq_map.irq_regs[i],
			data->irq_source[i]);
		hi_cdcctrl_reg_write(data->hi_cdc, data->phy_irq_map.irq_mask_regs[i],
			data->irq_mask[i]);
		data->irq_source[i] = 0;
	}
}


static void hi64xx_irq_mask(struct irq_data *d)
{
	struct hi64xx_irq_platform_data *data = irq_data_get_irq_chip_data(d);
	unsigned long phy_irq = irqd_to_hwirq(d);

	_irq_mask(data, phy_irq);
}

static void hi64xx_irq_unmask(struct irq_data *d)
{
	struct hi64xx_irq_platform_data *data = irq_data_get_irq_chip_data(d);
	unsigned long phy_irq = irqd_to_hwirq(d);

	_irq_unmask(data, phy_irq);
}

static void hi64xx_irq_bus_lock(struct irq_data *d)
{
	struct hi64xx_irq_platform_data *data = irq_data_get_irq_chip_data(d);

	mutex_lock(&data->irq_lock);
}

static void hi64xx_irq_bus_unlock(struct irq_data *d)
{
	struct hi64xx_irq_platform_data *data = irq_data_get_irq_chip_data(d);
	_irq_state_sync(data);

	mutex_unlock(&data->irq_lock);
}

static struct irq_chip hi64xx_irq_chip = {
	.name = "hi64xx_irq",
	.irq_mask = hi64xx_irq_mask,
	.irq_unmask = hi64xx_irq_unmask,
	.irq_disable = hi64xx_irq_mask,
	.irq_enable = hi64xx_irq_unmask,
	.irq_bus_lock = hi64xx_irq_bus_lock,
	.irq_bus_sync_unlock = hi64xx_irq_bus_unlock,
};

static int hi64xx_irq_map(struct irq_domain *d, unsigned int virq,
			irq_hw_number_t hw)
{
	struct hi64xx_irq_platform_data *irq = d->host_data;

	irq_set_chip_data(virq, irq);
	irq_set_chip(virq, &hi64xx_irq_chip);
	irq_set_nested_thread(virq, true);
	set_irq_flags(virq, IRQF_VALID);

	return 0;
}

static struct irq_domain_ops hi64xx_domain_ops = {
	.map = hi64xx_irq_map,
	.xlate = irq_domain_xlate_twocell,
};

static int hi64xx_irq_irqdomain_init(struct device *dev, struct hi64xx_irq_platform_data *data)
{
	int ret = 0;
	int i = 0;
	/* create irq domain */
	data->domain = irq_domain_add_linear(dev->of_node, data->phy_irq_map.irq_num,
					    &hi64xx_domain_ops, data);
	if (!data->domain) {
		dev_err(dev, "create irq domain error\n");
		ret = -ENODEV;
		return ret;
	}
	/* get gpio map */
	for (i = 0; i < data->phy_irq_map.irq_num; i++) {
		data->sub_irq_id[i] = irq_create_mapping(data->domain, i);
		if (NO_IRQ == data->sub_irq_id[i]) {
			dev_err(dev, "failed mapping irq ids\n");
			ret = -ENOSPC;
		}
	}

	return ret;
}

int hi64xx_irq_init_irq(struct hi64xx_irq *hi64xx_data, struct hi64xx_irq_map *irq_map)
{
	struct hi_cdc_ctrl *cdc_data = NULL;
	struct hi64xx_irq_platform_data *data = NULL;
	int ret = 0;
	int i = 0;

	data = (struct hi64xx_irq_platform_data *)hi64xx_data;
	cdc_data = data->hi_cdc;

	memcpy(&data->phy_irq_map, irq_map, sizeof(struct hi64xx_irq_map));

	for (i = 0; i < data->phy_irq_map.irq_num / HI64XX_IRQ_REG_BITS_NUM; i++)
	{
		hi_cdcctrl_reg_write(cdc_data, data->phy_irq_map.irq_mask_regs[i], 0xFF);
		data->irq_mask[i] = 0xFF;
		hi_cdcctrl_reg_write(cdc_data, data->phy_irq_map.irq_regs[i], 0xFF);
		data->irq_source[i] = 0;
	}

	/* get irq_id from gpio */
	data->irq_id = hi_cdcctrl_get_irq(cdc_data);

	/* init irq domain */
	ret = hi64xx_irq_irqdomain_init(data->hi64xx_irq.dev, data);
	if (0 > ret) {
		pr_err("request irq domain fail! return is %d\n", ret);
		return ret;
	}

	/* request gpio irq for codec */
	ret = request_threaded_irq(data->irq_id, hi64xx_irq_handler,
				hi64xx_irq_handler_thread,
				IRQF_TRIGGER_LOW | IRQF_NO_SUSPEND | IRQF_ONESHOT,
				dev_name(data->hi64xx_irq.dev), data);

	if (0 > ret) {
		dev_err(data->hi64xx_irq.dev, "register irq fail! return is %d\n", ret);
	}

	return ret;
}
EXPORT_SYMBOL(hi64xx_irq_init_irq);

void hi64xx_irq_deinit_irq(struct hi64xx_irq *hi64xx_data)
{
	struct hi64xx_irq_platform_data * data =
		(struct hi64xx_irq_platform_data *)hi64xx_data;
	free_irq(data->irq_id, data);
}
EXPORT_SYMBOL(hi64xx_irq_deinit_irq);

int hi64xx_irq_request_irq(struct hi64xx_irq *hi64xx_data, int phy_irq_id,
				irq_handler_t handler, const char *name, void *pri_data)
{
	struct hi64xx_irq_platform_data *data = NULL;

	BUG_ON(NULL == hi64xx_data);
	data = (struct hi64xx_irq_platform_data *)hi64xx_data;

	if (phy_irq_id >= data->phy_irq_map.irq_num)
	{
		pr_err("%s: physical irq id %d is out of the range\n", __FUNCTION__, phy_irq_id);
		return -1;
	}

	return request_threaded_irq(data->sub_irq_id[phy_irq_id], NULL, handler,
				IRQF_NO_SUSPEND | IRQF_ONESHOT, name, pri_data);
}
EXPORT_SYMBOL(hi64xx_irq_request_irq);

void hi64xx_irq_free_irq(struct hi64xx_irq *irq_data, int phy_irq, void *priv)
{
	struct hi64xx_irq_platform_data *data =
		(struct hi64xx_irq_platform_data *)irq_data;

	if (phy_irq >= data->phy_irq_map.irq_num)
		return;

	free_irq(data->sub_irq_id[phy_irq], priv);
}
EXPORT_SYMBOL(hi64xx_irq_free_irq);

int hi64xx_irq_enable_irq(struct hi64xx_irq *irq_data, int phy_irq)
{
	struct hi64xx_irq_platform_data *data =
		(struct hi64xx_irq_platform_data *)irq_data;

	if (phy_irq >= data->phy_irq_map.irq_num || phy_irq < 0) {
		pr_err("%s: physical irq id %d out of range\n", __FUNCTION__, phy_irq);
		return -EINVAL;
	}

	enable_irq(data->sub_irq_id[phy_irq]);

	return 0;
}
EXPORT_SYMBOL(hi64xx_irq_enable_irq);

int hi64xx_irq_disable_irq(struct hi64xx_irq *irq_data, int phy_irq)
{
	struct hi64xx_irq_platform_data *data =
		(struct hi64xx_irq_platform_data *)irq_data;

	if (phy_irq >= data->phy_irq_map.irq_num || phy_irq < 0) {
		pr_err("%s: physical irq id %d out of range\n", __FUNCTION__, phy_irq);
		return -EINVAL;
	}

	disable_irq(data->sub_irq_id[phy_irq]);

	return 0;
}
EXPORT_SYMBOL(hi64xx_irq_disable_irq);

int hi64xx_irq_enable_irqs(struct hi64xx_irq *irq_data, int irq_num, int* phy_irqs)
{
	struct hi64xx_irq_platform_data *data =
		(struct hi64xx_irq_platform_data *)irq_data;
	int i;

	mutex_lock(&data->irq_lock);

	for (i = 0; i < irq_num; i++) {
		_irq_unmask(data, phy_irqs[i]);
	}
	_irq_state_sync(data);

	mutex_unlock(&data->irq_lock);
	return 0;
}
EXPORT_SYMBOL(hi64xx_irq_enable_irqs);

int hi64xx_irq_disable_irqs(struct hi64xx_irq *irq_data, int irq_num, int* phy_irqs)
{
	struct hi64xx_irq_platform_data *data =
		(struct hi64xx_irq_platform_data *)irq_data;
	int i;

	mutex_lock(&data->irq_lock);

	for (i = 0; i < irq_num; i++) {
		_irq_mask(data, phy_irqs[i]);
	}
	_irq_state_sync(data);

	mutex_unlock(&data->irq_lock);

	return 0;
}
EXPORT_SYMBOL(hi64xx_irq_disable_irqs);

void hi64xx_irq_resume_wait(struct hi64xx_irq *irq_data)
{
	struct hi64xx_irq_platform_data *data =
		(struct hi64xx_irq_platform_data *)irq_data;
	mutex_lock(&data->sr_lock);
	mutex_unlock(&data->sr_lock);
}
EXPORT_SYMBOL(hi64xx_irq_resume_wait);

static struct of_device_id of_hi64xx_irq_child_match_tbl[] = {
	/* hi64xx_irq */
	{
		.compatible = "hisilicon,hi6402-codec",
	},
	{ /* end */ }
};

static int hi64xx_irq_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct hi64xx_irq_platform_data *data = NULL;
	struct hi_cdc_ctrl *cdc_data = NULL;
	const struct of_device_id *match = NULL;

	dev_info(dev, "%s: probe enter\n", __FUNCTION__);

	data = devm_kzalloc(dev, sizeof(struct hi64xx_irq_platform_data), GFP_KERNEL);
	if (!data) {
		dev_err(dev, "cannot allocate hi64xx_irq_platform_data device info\n");
		return -ENOMEM;
	}

	match = of_match_device(of_hi64xx_irq_match, dev);

	if (!match) {
		dev_err(dev, "%s: get device info err\n", __FUNCTION__);
		return -ENOENT;
	}

	mutex_init(&data->irq_lock);
	mutex_init(&data->sr_lock);
	mutex_init(&data->handler_mutex);
	wake_lock_init(&data->wake_lock, WAKE_LOCK_SUSPEND, "hi64xx-irq");

	data->hi64xx_irq.dev = dev;

	platform_set_drvdata(pdev, data);
	/* get parent data */
	cdc_data = (struct hi_cdc_ctrl *)dev_get_drvdata(pdev->dev.parent);
	data->hi_cdc = cdc_data;

	/* populate sub nodes */
	of_platform_populate(np, of_hi64xx_irq_child_match_tbl, NULL, dev);

	dev_info(dev, "%s: probe ok\n", __FUNCTION__);
	return 0;
}

static int hi64xx_irq_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi64xx_irq_platform_data *data = platform_get_drvdata(pdev);

	if (!data) {
		dev_err(dev, "%s data is null!\n", __FUNCTION__);
		return -EINVAL;
	}

	free_irq(data->irq_id, data);

	wake_lock_destroy(&data->wake_lock);
	mutex_destroy(&data->handler_mutex);
	mutex_destroy(&data->irq_lock);
	mutex_destroy(&data->sr_lock);

	devm_kfree(dev, data);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static int hi64xx_irq_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct device *dev = &pdev->dev;
	struct hi64xx_irq_platform_data *data = platform_get_drvdata(pdev);
	int ret = 0;

	dev_info(dev, "%s ok!\n", __FUNCTION__);

	if (!data) {
		dev_err(dev, "%s data is null!\n", __FUNCTION__);
		return -EINVAL;
	}

	mutex_lock(&data->sr_lock);

	ret = hi64xx_hifi_misc_suspend();
	if (ret) {
		mutex_unlock(&data->sr_lock);
		return ret;
	}

	return ret;
}

static int hi64xx_irq_resume(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi64xx_irq_platform_data *data = platform_get_drvdata(pdev);
	int ret = 0;

	dev_info(dev, "%s ok!\n", __FUNCTION__);

	if (!data) {
		dev_err(dev, "%s data is null!\n", __FUNCTION__);
		return -EINVAL;
	}

	ret = hi64xx_hifi_misc_resume();
	if (ret)
		dev_err(dev, "%s hifi misc resume failed!\n", __FUNCTION__);

	mutex_unlock(&data->sr_lock);

	return ret;
}

static struct platform_driver hi64xx_irq_driver = {
	.driver = {
		.name	= "hi64xx_irq",
		.owner  = THIS_MODULE,
		.of_match_table = of_hi64xx_irq_match,
	},
	.probe		= hi64xx_irq_probe,
	.remove		= hi64xx_irq_remove,
	.suspend	= hi64xx_irq_suspend,
	.resume		= hi64xx_irq_resume,
};

static int __init hi64xx_irq_init(void)
{
	return platform_driver_register(&hi64xx_irq_driver);
}

static void __exit hi64xx_irq_exit(void)
{
	platform_driver_unregister(&hi64xx_irq_driver);
}

fs_initcall(hi64xx_irq_init);
module_exit(hi64xx_irq_exit);

MODULE_DESCRIPTION("hi64xx irq controller driver");
MODULE_AUTHOR("liuyang <liuyang66@hisilicon.com>");
MODULE_LICENSE("GPL");
