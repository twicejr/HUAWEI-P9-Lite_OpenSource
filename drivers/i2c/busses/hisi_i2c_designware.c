/*
 * Hisilicon Synopsys DesignWare I2C adapter driver (master only).
 *
 * Copyright (c) 2012-2013 Linaro Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/clk.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/of_i2c.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/pinctrl/consumer.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/delay.h>
#include "i2c-designware-core.h"


struct hs_i2c_priv_data {
	u32 delay_off;
	u32 delay_bit;
	u32 reset_enable_off;
	u32 reset_disable_off;
	u32 reset_status_off;
	u32 reset_bit;
};

static struct i2c_algorithm hs_i2c_dw_algo = {
	.master_xfer	= i2c_dw_xfer,
	.functionality	= i2c_dw_func,
};

static u32 hs_i2c_dw_get_clk_rate_khz(struct dw_i2c_dev *dev)
{
	return clk_get_rate(dev->clk)/1000;
}

static void hs_i2c_dw_reset_controller(struct dw_i2c_dev *dev)
{
	struct hs_i2c_priv_data *priv = dev->priv;
	u32 val = 0, timeout = 10;

	writel(BIT(priv->reset_bit), dev->reset_reg_base + priv->reset_enable_off);
	do {
		val = readl(dev->reset_reg_base + priv->reset_status_off);
		val &= BIT(priv->reset_bit);
		udelay(1);
	} while (!val && timeout--);

	timeout = 10;

	writel(BIT(priv->reset_bit), dev->reset_reg_base + priv->reset_disable_off);
	do {
		val = readl(dev->reset_reg_base + priv->reset_status_off);
		val &= BIT(priv->reset_bit);
		udelay(1);
	} while (val && timeout--);

	return;
}

static int hs_dw_i2c_probe(struct platform_device *pdev)
{
	struct dw_i2c_dev *d;
	struct i2c_adapter *adap;
	struct resource *iores;
	u32 data[4] = {0};
	struct hs_i2c_priv_data *priv;
	u64 clk_rate = 0;
	int r;

	d = devm_kzalloc(&pdev->dev, sizeof(struct dw_i2c_dev), GFP_KERNEL);
	if (!d) {
		dev_err(&pdev->dev, "mem alloc failed for dw_i2c_dev data\n");
		return -ENOMEM;
	}

	priv = devm_kzalloc(&pdev->dev, sizeof(struct hs_i2c_priv_data), GFP_KERNEL);
	if (!priv) {
		dev_err(&pdev->dev, "mem alloc failed for private data\n");
		return -ENOMEM;
	}
	d->priv = priv;

	/* NOTE: driver uses the static register mapping */
	iores = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!iores)
		return -EINVAL;

	d->mapbase  = iores->start;
	d->base = devm_request_and_ioremap(&pdev->dev, iores);
	if (!d->base)
		return -EADDRNOTAVAIL;

	d->platform_dev = &pdev->dev;
	d->pinctrl_flag = 0;
	d->pinctrl = NULL;

	r = of_property_read_u32_array(pdev->dev.of_node, "reset-reg-base", &data[0], 4);
	if(r) {
		pr_err("[%s] node %s doesn't have reset-reg-base property!\n",
		__func__, pdev->dev.of_node->name);
	} else {
		d->reset_reg_base = ioremap(data[1], data[3]);
		dev_info(&pdev->dev, "i2c reset register phy_addr is: %x\n", data[1]);
	}
	dev_info(&pdev->dev, "i2c reset register vir_addr is: %p\n", d->reset_reg_base);

	r = of_property_read_u32_array(pdev->dev.of_node, "delay-off", &d->delay_off, 1);
	if(r) {
		pr_err("[%s] node %s doesn't have delay-off property!\n",
		__func__, pdev->dev.of_node->name);
	}

	r = of_property_read_u32_array(pdev->dev.of_node, "reset-controller-reg",
						&data[0], 4);
	if(r) {
		pr_err("[%s] node %s doesn't have reset-controller-reg property!\n",
		__func__, pdev->dev.of_node->name);
	}

	d->gpio_scl = of_get_named_gpio(pdev->dev.of_node, "cs-gpios", 0);
	d->gpio_sda = of_get_named_gpio(pdev->dev.of_node, "cs-gpios", 1);
	dev_info(&pdev->dev, "i2c cs-gpios = %d, %d!\n", d->gpio_scl, d->gpio_sda);
	if (d->gpio_scl == -ENOENT || d->gpio_sda == -ENOENT) {
		dev_err(&pdev->dev, "node %s doesn't have gpio scl/sda property!\n", pdev->dev.of_node->name);
		d->deadlock_recovery = 0;
		goto cs_gpio_err;
	}
	if (gpio_request(d->gpio_scl, "i2c scl")) {
		dev_err(&pdev->dev, "i2c scl gpio request failed\n");
		d->deadlock_recovery = 0;
		goto cs_gpio_err;
	}
	if (gpio_request(d->gpio_sda, "i2c sda")) {
		dev_err(&pdev->dev, "i2c sda gpio request failed\n");
		d->deadlock_recovery = 0;
		goto cs_gpio_err;
	}
	d->deadlock_recovery = 1;

cs_gpio_err:
	priv->reset_enable_off = data[0];
	priv->reset_disable_off = data[1];
	priv->reset_status_off = data[2];
	priv->reset_bit = data[3];

	d->get_clk_rate_khz = hs_i2c_dw_get_clk_rate_khz;
	d->reset_controller = hs_i2c_dw_reset_controller;

#ifdef CONFIG_HISI_I2C_DESIGNWARE
	r = devm_pinctrl_state_select(d, PINCTRL_STATE_DEFAULT);
	if (r<0)
		dev_warn(&pdev->dev,
				 "pins are not configured from the driver\n");

	d->clk = devm_clk_get(&pdev->dev, "clk_i2c");
	if (IS_ERR(d->clk))
		return -ENODEV;

	r = of_property_read_u64(pdev->dev.of_node, "clock-rate", &clk_rate);
	if (r) {
		dev_info(&pdev->dev, "[%s] node %s doesn't have clock-rate property!\n",
				__func__, pdev->dev.of_node->name);
	} else {
		dev_info(&pdev->dev, "%s clock rate is %llu\n", pdev->dev.of_node->name, clk_rate);
		r = clk_set_rate(d->clk, clk_rate);
		if (r) {
			dev_err(&pdev->dev, "%s clock rate set failed r[0x%x]\n",
				pdev->dev.of_node->name, r);
            return  -EINVAL;
		}
	}

	r = clk_prepare_enable(d->clk);
	if(r) {
		dev_warn(&pdev->dev,"Unable to enable clock!\n");
		return  -EINVAL;
	}
#endif

	init_completion(&d->cmd_complete);
	init_completion(&d->dma_complete);
	mutex_init(&d->lock);
	d->dev = get_device(&pdev->dev);

	d->functionality =
		I2C_FUNC_I2C |
		I2C_FUNC_10BIT_ADDR |
		I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_I2C_BLOCK;

	d->master_cfg =  DW_IC_CON_MASTER | DW_IC_CON_SLAVE_DISABLE |
					 DW_IC_CON_RESTART_EN | DW_IC_CON_SPEED_FAST;

	d->accessor_flags = ACCESS_32BIT;

	if(d && d->reset_controller)
		d->reset_controller(d);

	{
		u32 param1 = readl(d->base + DW_IC_COMP_PARAM_1);

		d->tx_fifo_depth = ((param1 >> 16) & 0xff) + 1;
		d->rx_fifo_depth = ((param1 >> 8)  & 0xff) + 1;
		dev_info(&pdev->dev, "tx_fifo_depth: %d, rx_fifo_depth: %d\n",
				 d->tx_fifo_depth, d->rx_fifo_depth);
	}

	r = i2c_dw_init(d);
	if (r)
		goto err;

	i2c_dw_disable_int(d);

	d->irq = platform_get_irq(pdev, 0);
	if (d->irq < 0) {
		dev_err(&pdev->dev, "no irq resource?\n");
		return d->irq; /* -ENXIO */
	}

	d->irq_is_run = 0;
	r = devm_request_irq(&pdev->dev, d->irq,
						 i2c_dw_isr, IRQF_DISABLED, pdev->name, d);
	if (r) {
		dev_err(&pdev->dev, "failure requesting irq %i\n", d->irq);
		return -EINVAL;
	}

	adap = &d->adapter;
	i2c_set_adapdata(adap, d);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_HWMON;
	strlcpy(adap->name, "Synopsys DesignWare I2C adapter",
			sizeof(adap->name));
	adap->algo = &hs_i2c_dw_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	adap->nr = pdev->id;
	r = i2c_add_numbered_adapter(adap);
	if (r) {
		dev_err(&pdev->dev, "failure adding adapter\n");
		goto err;
	}
	of_i2c_register_devices(adap);
	platform_set_drvdata(pdev, d);

	//DMA probe
	i2c_dw_dma_probe(d);

#ifdef CONFIG_HISI_I2C_DESIGNWARE
	clk_disable(d->clk);

	r = devm_pinctrl_state_select(d, PINCTRL_STATE_IDLE);
	if (r<0)
		dev_warn(&pdev->dev,
				 "pins are not configured from the driver\n");
#endif
	dev_info(&pdev->dev, "i2c probe succeed!\n");
	return 0;

err:
#ifdef CONFIG_HISI_I2C_DESIGNWARE
	clk_disable_unprepare(d->clk);
	//devm_clk_put(&pdev->dev, d->clk);
	d->clk = NULL;

	r = devm_pinctrl_state_select(d, PINCTRL_STATE_IDLE);
	if (r<0)
		dev_warn(&pdev->dev,
				 "pins are not configured from the driver\n");
#endif
	put_device(&pdev->dev);
	return r;
}

static int hs_dw_i2c_remove(struct platform_device *pdev)
{
	struct dw_i2c_dev *d = platform_get_drvdata(pdev);

        if (!d){
                pr_err("%s: get drvdata failed\n", __func__);
                return -EINVAL;
        }

	platform_set_drvdata(pdev, NULL);
	i2c_del_adapter(&d->adapter);
	put_device(&pdev->dev);
	clk_disable_unprepare(d->clk);
	devm_clk_put(&pdev->dev, d->clk);
	d->clk = NULL;

	i2c_dw_dma_remove(d);

	i2c_dw_disable(d);

	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id hs_dw_i2c_of_match[] = {
	{ .compatible = "hisilicon,designware-i2c", },
	{},
};
MODULE_DEVICE_TABLE(of, hs_dw_i2c_of_match);
#endif

#ifdef CONFIG_PM
static int hs_dw_i2c_suspend(struct device *dev)
{
	unsigned limit = 500;
	struct platform_device *pdev = to_platform_device(dev);
	struct dw_i2c_dev *i_dev = platform_get_drvdata(pdev);

	if (!i_dev){
		pr_err("%s: get drvdata failed\n", __func__);
		return -EINVAL;
	}

	dev_info(&pdev->dev, "%s: suspend +\n", __func__);

	while (!mutex_trylock(&i_dev->lock)) {
		if (limit == 0) {
			dev_info(&pdev->dev, "%s: mutex_trylock 500 times fail.\n", __func__);
			return -EAGAIN;
		}
		limit--;
		msleep(1);
	}

	dev_info(&pdev->dev, "%s: suspend -\n", __func__);
	return 0;
}

static int hs_dw_i2c_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct dw_i2c_dev *i_dev = platform_get_drvdata(pdev);
	int ret = 0;

        if (!i_dev){
                pr_err("%s: get drvdata failed\n", __func__);
                return -EINVAL;
        }

	dev_info(&pdev->dev, "%s: resume +\n", __func__);

	ret = clk_enable(i_dev->clk);
	if(ret) {
		dev_err(&pdev->dev, "clk_prepare_enable failed!\n");
		return -EAGAIN;
	}
	hs_i2c_dw_reset_controller(i_dev);
	i2c_dw_init(i_dev);
	i2c_dw_disable_int(i_dev);
	clk_disable(i_dev->clk);

	mutex_unlock(&i_dev->lock);

	dev_info(&pdev->dev, "%s: resume -\n", __func__);
	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(hs_dw_i2c_dev_pm_ops, hs_dw_i2c_suspend, hs_dw_i2c_resume);

static struct platform_driver hs_dw_i2c_driver = {
	.probe		= hs_dw_i2c_probe,
	.remove		= hs_dw_i2c_remove,
	.driver		= {
		.name	= "i2c_designware-hs",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(hs_dw_i2c_of_match),
		.pm	= &hs_dw_i2c_dev_pm_ops,
	},
};
module_platform_driver(hs_dw_i2c_driver);

MODULE_DESCRIPTION("HS Synopsys DesignWare I2C bus adapter");
MODULE_ALIAS("platform:i2c_designware-hs");
MODULE_LICENSE("GPL");
