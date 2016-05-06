/*
 * hi3630_asp_irq.c  --  Interrupt controller support for Hisilicon HI3630 ASP
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
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
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/mfd/hi3630_asp_irq.h>

#include <linux/irq.h>

#ifndef NO_IRQ
#define NO_IRQ	0
#endif

#define HI3630_REG_ASP_CFG_IRQ		(0x6C)
#define HI3630_REG_ASP_CFG_IRQ_MASK	(0x68)

static struct of_device_id of_hi3630_asp_irq_child_match_tbl[] = {
	{
		.compatible = "hisilicon,hi3630-asp-common",
	},
	{
		.compatible = "hisilicon,hi3630-srcup-normal",
	},
	{
		.compatible = "hisilicon,hi3630-srcup-dsp",
	},
	{
		.compatible = "hisilicon,hi3630-pcm-hdmi",
	},
	{ /* end */ }
};

static const struct of_device_id of_hi3630_asp_irq_of_match[] = {
	{ .compatible = "hisilicon,hi3630-asp-irq", },
	{ }
};
MODULE_DEVICE_TABLE(of, hi3630_asp_irq_of_match);

/*
 * make sure module of audio cfg is enalbed, when call read & write function
 */
int hi3630_asp_irq_read(struct hi3630_asp_irq *irq,
			unsigned int reg)
{
	/* TODO : MUTEX WITHOUT DSP */
	BUG_ON(NULL == irq);
	return readl(irq->reg_base_addr + reg);
}
EXPORT_SYMBOL(hi3630_asp_irq_read);

void hi3630_asp_irq_write(struct hi3630_asp_irq *irq,
			unsigned int reg, unsigned int value)
{
	/* TODO : MUTEX WITHOUT DSP */
	BUG_ON(NULL == irq);
	writel(value, irq->reg_base_addr + reg);
}
EXPORT_SYMBOL(hi3630_asp_irq_write);

void hi3630_asp_irq_set_bit(struct hi3630_asp_irq *irq,
			unsigned int reg, unsigned int offset)
{
	unsigned long flags = 0;
	unsigned int value = 0;

	spin_lock_irqsave(&irq->lock, flags);
	value = hi3630_asp_irq_read(irq, reg);
	value |= (1 << offset);
	hi3630_asp_irq_write(irq, reg, value);
	spin_unlock_irqrestore(&irq->lock, flags);
}
EXPORT_SYMBOL(hi3630_asp_irq_set_bit);

void hi3630_asp_irq_clr_bit(struct hi3630_asp_irq *irq,
			unsigned int reg, unsigned int offset)
{
	unsigned long flags = 0;
	unsigned int value = 0;

	spin_lock_irqsave(&irq->lock, flags);
	value = hi3630_asp_irq_read(irq, reg);
	value &= ~(1 << offset);
	hi3630_asp_irq_write(irq, reg, value);
	spin_unlock_irqrestore(&irq->lock, flags);
}
EXPORT_SYMBOL(hi3630_asp_irq_clr_bit);

static irqreturn_t hi3630_asp_irq_handler(int irq, void *data)
{
	struct hi3630_asp_irq *hi3630_asp_irq = (struct hi3630_asp_irq *)data;
	unsigned long pending = 0;
	unsigned int mask = 0;
	int offset = 0;

	if (!hi3630_asp_irq) {
		pr_err("hi3630_asp_irq is null\n");
		return IRQ_HANDLED;
	}

	mask = hi3630_asp_irq_read(hi3630_asp_irq, HI3630_REG_ASP_CFG_IRQ_MASK);
	pending = hi3630_asp_irq_read(hi3630_asp_irq, HI3630_REG_ASP_CFG_IRQ) & mask;

	/* handle each irq */
	if (pending) {
		for_each_set_bit(offset, &pending, HI3630_ASP_IRQ_BITS)
				generic_handle_irq(hi3630_asp_irq->irqs[offset]);
	}

	return IRQ_HANDLED;
}

static void hi3630_asp_irq_mask(struct irq_data *d)
{
	/* do not take care of mask */
}

static void hi3630_asp_irq_unmask(struct irq_data *d)
{
	/* do not take care of mask */
}

static struct irq_chip hi3630_asp_irqchip = {
	.name		= "hi3630_asp_irq",
	.irq_mask	= hi3630_asp_irq_mask,
	.irq_unmask	= hi3630_asp_irq_unmask,
};

static int hi3630_asp_irq_map(struct irq_domain *d, unsigned int virq,
			      irq_hw_number_t hw)
{
	struct hi3630_asp_irq *irq = d->host_data;

	irq_set_chip_and_handler_name(virq, &hi3630_asp_irqchip,
				      handle_simple_irq, "hi3630_asp_irq");
	irq_set_chip_data(virq, irq);
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	return 0;
}

static struct irq_domain_ops hi3630_asp_domain_ops = {
	.map	= hi3630_asp_irq_map,
	.xlate	= irq_domain_xlate_twocell,
};

static int hi3630_asp_irq_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct hi3630_asp_irq *irq = NULL;
	int virq;
	int ret;
	int i;

	irq = devm_kzalloc(dev, sizeof(*irq), GFP_KERNEL);
	if (!irq) {
		dev_err(dev, "cannot allocate hi3630_asp_irq device info\n");
		return -ENOMEM;
	}

	/* get resources */
	irq->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!irq->res) {
		dev_err(dev, "platform_get_resource err\n");
		return -ENOENT;
	}

	if (!devm_request_mem_region(dev, irq->res->start,
				     resource_size(irq->res),
				     pdev->name)) {
		dev_err(dev, "cannot claim register memory\n");
		return -ENOMEM;
	}

	irq->reg_base_addr = devm_ioremap(dev, irq->res->start,
					  resource_size(irq->res));

	if (!irq->reg_base_addr) {
		dev_err(dev, "cannot map register memory\n");
		return -ENOMEM;
	}

	irq->irq = platform_get_irq_byname(pdev, "asp_irq");
	if (0 > irq->irq) {
		dev_err(dev, "could not get irq line\n");
		return -ENOENT;
	}

	spin_lock_init(&irq->lock);

	irq->domain = irq_domain_add_simple(np, HI3630_ASP_IRQ_NR_IRQ, 0,
					    &hi3630_asp_domain_ops, irq);
	if (!irq->domain) {
		dev_err(dev, "irq domain error\n");
		ret = -ENOENT;
		goto err_exit;
	}

	for (i = 0; i < HI3630_ASP_IRQ_NR_IRQ; i++) {
		virq = irq_create_mapping(irq->domain, i);
		if (virq == NO_IRQ) {
			dev_err(dev, "Failed mapping hwirq\n");
			ret = -ENOSPC;
			goto err_exit;
		}
		irq->irqs[i] = virq;
	}

	ret = request_irq(irq->irq, hi3630_asp_irq_handler,
				   IRQF_TRIGGER_HIGH,
				   "hi3630_asp_irq", irq);
	if (0 > ret) {
		dev_err(dev, "could not claim irq %d\n", ret);
		ret = -ENODEV;
		goto err_exit;
	}

	platform_set_drvdata(pdev, irq);

	/* populate sub nodes */
	of_platform_populate(np, of_hi3630_asp_irq_child_match_tbl, NULL, dev);

err_exit:
	return ret;
}

static int hi3630_asp_irq_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi3630_asp_irq *irq = platform_get_drvdata(pdev);

	free_irq(irq->irq, irq);
	devm_iounmap(dev, irq->reg_base_addr);
	devm_release_mem_region(dev, irq->res->start,
				resource_size(irq->res));

	devm_kfree(dev, irq);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static struct platform_driver hi3630_asp_irq_driver = {
	.driver = {
		.name	= "hi3630_asp_irq",
		.owner  = THIS_MODULE,
		.of_match_table = of_hi3630_asp_irq_of_match,
	},
	.probe	= hi3630_asp_irq_probe,
	.remove	= hi3630_asp_irq_remove,
};
module_platform_driver(hi3630_asp_irq_driver);

MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("Hi3630 irq driver");
MODULE_LICENSE("GPL v2");
