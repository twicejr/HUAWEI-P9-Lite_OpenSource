/*
 * hi6401-irq.c  --  Interrupt controller support for Hisilicon HI6401
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
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/wakelock.h>
#include <linux/mutex.h>
#include <linux/mfd/hi6401_irq.h>

#include <linux/pinctrl/consumer.h>
#include <linux/irq.h>
#ifndef NO_IRQ
#define NO_IRQ 0
#endif

#define HI6401_REG_VERSION	(HI6401_BASE_ADDR_PAGE_0 + 0x1B0)

/* 8-bit register offset in irq */
#define HI6401_REG_IRQ_0	(HI6401_BASE_ADDR_PAGE_1 + 0x1B0)
#define HI6401_REG_IRQ_1	(HI6401_BASE_ADDR_PAGE_1 + 0x1B1) /* reserved */
#define HI6401_REG_IRQM_0	(HI6401_BASE_ADDR_PAGE_1 + 0x1B2)
#define HI6401_REG_IRQM_1	(HI6401_BASE_ADDR_PAGE_1 + 0x1B3) /* reserved */

#define HI6401_PLL_PD_REG	(HI6401_BASE_ADDR_PAGE_1 + 0x1BA)
#define HI6401_PLL_PD_BIT		0

#define HI6401_PLL_STATUS_REG	(HI6401_BASE_ADDR_PAGE_1 + 0x1E9)
#define HI6401_PLL_STATUS_BIT		0
#define HI6401_PLL_EN_REG	(HI6401_BASE_ADDR_PAGE_1 + 0x1E1)
#define HI6401_PLL_EN_BIT		7

static struct of_device_id of_hi6401_irq_child_match_tbl[] = {
	/* codec */
	{
		.compatible = "hisilicon,hi6401-codec",
	},
	{ /* end */ }
};

static struct of_device_id of_hi6401_irq_match[] = {
	{
		.compatible = "hisilicon,hi6401-irq",
	},
	{ /* end */ }
};

static inline void hi6401_select_reg_page(struct hi6401_irq *irq, unsigned int reg)
{
	if (0 == (HI6401_BASE_ADDR_PAGE_1 & reg)) {
		/* select page 0 */
		writel(0, irq->reg_base_addr + (HI6401_PAGE_SELECT_REG << 2));
	} else {
		/* select page 1 */
		writel(1, irq->reg_base_addr + (HI6401_PAGE_SELECT_REG << 2));
	}

	/* wait 1us */
	udelay(1);
}

/*
 * The irq register is only 8-bit.
 * Hisilicon SoC use hardware to map irq register into SoC mapping.
 * At here, we are accessing SoC register with 32-bit.
 */
u32 hi6401_irq_read(struct hi6401_irq *irq, int reg)
{
	unsigned long flags = 0;
	u32 ret = 0;

	spin_lock_irqsave(&irq->rw_lock, flags);
	hi6401_select_reg_page(irq, reg);
	ret = readl(irq->reg_base_addr + ((reg & HI6401_PAGE_OFFSET_MASK) << 2));

	/* wait 1us */
	udelay(1);

	spin_unlock_irqrestore(&irq->rw_lock, flags);

	return ret;
}
EXPORT_SYMBOL(hi6401_irq_read);

void hi6401_irq_write(struct hi6401_irq *irq, int reg, u32 val)
{
	unsigned long flags = 0;

	spin_lock_irqsave(&irq->rw_lock, flags);
	hi6401_select_reg_page(irq, reg);
	writel(val, irq->reg_base_addr + ((reg & HI6401_PAGE_OFFSET_MASK) << 2));

	/* wait 1us */
	udelay(1);
	spin_unlock_irqrestore(&irq->rw_lock, flags);
}
EXPORT_SYMBOL(hi6401_irq_write);

#if 0
static void hi6401_check_pll(struct hi6401_irq *irq)
{
	unsigned long flags = 0;
	u32 ret = 0;
	u32 val = 0;

	mutex_lock(&irq->sr_mutex);
	spin_lock_irqsave(&irq->rw_lock, flags);
	writel(1, irq->reg_base_addr + (HI6401_PAGE_SELECT_REG << 2));
	udelay(1);
	ret = readl(irq->reg_base_addr + ((HI6401_PLL_PD_REG & HI6401_PAGE_OFFSET_MASK) << 2));
	udelay(1);
	if (0 == (ret & 1)) { /* HI6401_PLL_PD_BIT */
		/* pll power on */
		val = readl(irq->reg_base_addr + ((HI6401_PLL_EN_REG & HI6401_PAGE_OFFSET_MASK) << 2));
		udelay(1);
		if (0 != (val & (1 << HI6401_PLL_EN_BIT))) {
			/* pll enable */
			ret = readl(irq->reg_base_addr + ((HI6401_PLL_STATUS_REG & HI6401_PAGE_OFFSET_MASK) << 2));
			udelay(1);
			if (0 == (ret & (1 << HI6401_PLL_STATUS_BIT))) {
				pr_err("%s,line:%d reset pll.\n", __FUNCTION__, __LINE__);
				/* pll unlocked */
				val &= ~(1 << HI6401_PLL_EN_BIT);
				writel(val, irq->reg_base_addr + ((HI6401_PLL_EN_REG & HI6401_PAGE_OFFSET_MASK) << 2));
				udelay(2);
				val |= (1 << HI6401_PLL_EN_BIT);
				writel(val, irq->reg_base_addr + ((HI6401_PLL_EN_REG & HI6401_PAGE_OFFSET_MASK) << 2));
				udelay(1);
			}
		}
	}
	spin_unlock_irqrestore(&irq->rw_lock, flags);
	mutex_unlock(&irq->sr_mutex);
}
#endif
static void hi6401_pll_work_func(struct work_struct *work)
{
#if 1
	return;
#else
	struct hi6401_irq *irq =
		container_of(work, struct hi6401_irq, pll_delay_work.work);

	if (!irq) {
		pr_err(" %s(%u) error: priv is NULL\n", __FUNCTION__, __LINE__);
		return;
	}

	while(1) {
		mutex_lock(&irq->pll_mutex);
		if (irq->pll_check_enable) {
			hi6401_check_pll(irq);
			mutex_unlock(&irq->pll_mutex);
			msleep(40);
		} else {
			mutex_unlock(&irq->pll_mutex);
			break;
		}
	}
#endif
}

void hi6401_pll_check_enable(struct hi6401_irq *irq, bool enable)
{
#if 1
	return;
#else
	if (!irq) {
		pr_err("hi6401_irq is null\n");
		return;
	}

	mutex_lock(&irq->pll_mutex);

	if (enable) {
		queue_delayed_work(irq->pll_delay_wq,
						&irq->pll_delay_work,
						msecs_to_jiffies(0));
		irq->pll_check_enable = true;
	} else {
		irq->pll_check_enable = false;
	}

	mutex_unlock(&irq->pll_mutex);
#endif
}
EXPORT_SYMBOL(hi6401_pll_check_enable);

void hi6401_irq_work_func(struct work_struct *work)
{
	struct hi6401_irq *hi6401_irq =
		container_of(work, struct hi6401_irq, hi6401_irq_delay_work.work);
	unsigned long pending = 0;
	int offset;
	unsigned long flags = 0;

	BUG_ON(NULL == hi6401_irq);

	mutex_lock(&hi6401_irq->sr_mutex);

	pending = hi6401_irq_read(hi6401_irq, HI6401_REG_IRQ_0);
	pending &= HI6401_MASK_FIELD;
	pending &= (~hi6401_irq_read(hi6401_irq, HI6401_REG_IRQM_0));
	hi6401_irq_write(hi6401_irq, HI6401_REG_IRQ_0, pending);
	enable_irq(hi6401_irq->irq);

	/* handle each irq */
	spin_lock_irqsave(&hi6401_irq->lock, flags);

	if (pending) {
		for_each_set_bit(offset, &pending, HI6401_BITS)
			generic_handle_irq(hi6401_irq->irqs[offset]);
	} else {
		pr_err("clr all hi6401 irq\n");
		hi6401_irq_write(hi6401_irq, HI6401_REG_IRQ_0, 0xFF);
		hi6401_irq_write(hi6401_irq, HI6401_REG_IRQ_1, 0xFF);
		hi6401_irq_write(hi6401_irq, HI6401_REG_IRQM_1, 0xFF);
	}

	spin_unlock_irqrestore(&hi6401_irq->lock, flags);

	wake_lock_timeout(&hi6401_irq->wake_lock, 3000);
	mutex_unlock(&hi6401_irq->sr_mutex);
}

static irqreturn_t hi6401_irq_handler(int irq, void *data)
{
	struct hi6401_irq *hi6401_irq = (struct hi6401_irq *)data;

	if (!hi6401_irq) {
		pr_err("hi6401_irq is null\n");
		return IRQ_HANDLED;
	}

	disable_irq_nosync(hi6401_irq->irq);
	queue_delayed_work(hi6401_irq->hi6401_irq_delay_wq,
			&hi6401_irq->hi6401_irq_delay_work,
			msecs_to_jiffies(0));

	return IRQ_HANDLED;
}

static void hi6401_irq_mask(struct irq_data *d)
{
	/* do nothing */
}

static void hi6401_irq_unmask(struct irq_data *d)
{
	/* do nothing */
}

static struct irq_chip hi6401_irqchip = {
	.name		= "hi6401_irq",
	.irq_mask	= hi6401_irq_mask,
	.irq_unmask	= hi6401_irq_unmask,
	.irq_disable	= hi6401_irq_mask,
	.irq_enable	= hi6401_irq_unmask,
};

static int hi6401_irq_map(struct irq_domain *d, unsigned int virq,
			  irq_hw_number_t hw)
{
	struct hi6401_irq *irq = d->host_data;

	irq_set_chip_and_handler_name(virq, &hi6401_irqchip,
				      handle_simple_irq, "hi6401_irq");
	irq_set_chip_data(virq, irq);
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	return 0;
}

static struct irq_domain_ops hi6401_domain_ops = {
	.map	= hi6401_irq_map,
	.xlate	= irq_domain_xlate_twocell,
};

static int codec_ssi_iomux_default(struct pinctrl *pctrl)
{
	struct pinctrl_state *pinctrl_state;

	BUG_ON(NULL == pctrl);

	pinctrl_state = pinctrl_lookup_state(pctrl, PINCTRL_STATE_DEFAULT);

	if (IS_ERR(pinctrl_state)) {
		pr_err("%s : could not get default state (%li)\n",
				__FUNCTION__ , PTR_ERR(pinctrl_state));
		return -1;
	}

	if (pinctrl_select_state(pctrl, pinctrl_state)) {
		pr_err("%s : could not set pins to default state\n", __FUNCTION__);
		return -1;
	}

	return 0;
}

static int codec_ssi_iomux_idle(struct pinctrl *pctrl)
{
	struct pinctrl_state *pinctrl_state;

	BUG_ON(NULL == pctrl);

	pinctrl_state = pinctrl_lookup_state(pctrl, PINCTRL_STATE_IDLE);

	if (IS_ERR(pinctrl_state)) {
		pr_err("%s : could not get idle state (%li)\n",
				__FUNCTION__ , PTR_ERR(pinctrl_state));
		return -1;
	}

	if (pinctrl_select_state(pctrl, pinctrl_state)) {
		pr_err("%s : could not set pins to idle state\n", __FUNCTION__);
		return -1;
	}

	return 0;
}

static int hi6401_irq_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct hi6401_irq *irq = NULL;
	enum of_gpio_flags flags;
	unsigned int virq;
	int ret = 0;
	int i;

	irq = devm_kzalloc(dev, sizeof(*irq), GFP_KERNEL);
	if (!irq) {
		dev_err(dev, "cannot allocate hi6401_irq device info\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, irq);

	/* get resources */
	irq->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!irq->res) {
		dev_err(dev, "platform_get_resource err\n");
		goto err_exit;
	}

	if (!devm_request_mem_region(dev, irq->res->start,
				     resource_size(irq->res),
				     pdev->name)) {
		dev_err(dev, "cannot claim register memory\n");
		goto err_exit;
	}

	irq->reg_base_addr = devm_ioremap(dev, irq->res->start,
					  resource_size(irq->res));
	if (!irq->reg_base_addr) {
		dev_err(dev, "cannot map register memory\n");
		goto ioremap_err;
	}

#if 0
	/* get pinctrl */
	irq->pctrl = devm_pinctrl_get(dev);
	if (IS_ERR(irq->pctrl)) {
		dev_err(dev, "could not get pinctrl\n");
		goto codec_ssi_get_err;
	}
	ret = codec_ssi_iomux_default(irq->pctrl);
	if (0 != ret)
		goto codec_ssi_iomux_err;

	/* get codec ssi clk */
	irq->codec_ssi_clk = devm_clk_get(dev, "clk_codecssi");
	if (IS_ERR(irq->codec_ssi_clk)) {
		pr_err("clk_get: codecssi clk not found!\n");
		ret = PTR_ERR(irq->codec_ssi_clk);
		goto codec_ssi_clk_err;
	}
	ret = clk_prepare_enable(irq->codec_ssi_clk);
	if (0 != ret) {
		pr_err("codec_ssi_clk :clk prepare enable failed !\n");
		goto codec_ssi_clk_enable_err;
	}

	/* get pmu audio clk */
	irq->pmu_audio_clk = devm_clk_get(dev, "clk_pmuaudioclk");
	if (IS_ERR(irq->pmu_audio_clk)) {
		pr_err("_clk_get: pmu_audio_clk not found!\n");
		ret = PTR_ERR(irq->pmu_audio_clk);
		goto pmu_audio_clk_err;
	}
	ret = clk_prepare_enable(irq->pmu_audio_clk);
	if (0 != ret) {
		pr_err("pmu_audio_clk :clk prepare enable failed !\n");
		goto pmu_audio_clk_enable_err;
	}
#endif

	/* check chip id */
	ret = hi6401_irq_read(irq, HI6401_REG_VERSION);
	if (0xFF == ret || 0 == ret) {
		/*
		 * 0xFF : means ssi err, or chip no ack
		 * 0    : means no chip
		 */
		pr_err("no codec chip connected(%#x)!", ret);
		ret = -ENODEV;
		goto get_gpio_err;
	} else {
		pr_info("codec chip version is %#x", ret);
	}

	spin_lock_init(&irq->lock);
	spin_lock_init(&irq->rw_lock);
	mutex_init(&irq->sr_mutex);
	mutex_init(&irq->pll_mutex);
	wake_lock_init(&irq->wake_lock, WAKE_LOCK_SUSPEND, "hi6401-irq");

	irq->dev = dev;

	/* clear IRQ status */
	hi6401_irq_write(irq, HI6401_REG_IRQ_0, 0xFF);
	hi6401_irq_write(irq, HI6401_REG_IRQ_1, 0xFF);
	/* mask all irqs */
	hi6401_irq_write(irq, HI6401_REG_IRQM_0, 0xFF);
	hi6401_irq_write(irq, HI6401_REG_IRQM_1, 0xFF);

	irq->gpio = of_get_gpio_flags(np, 0, &flags);
	if (0 > irq->gpio) {
		dev_err(dev, "get gpio flags error\n");
		ret = irq->gpio;
		goto get_gpio_err;
	}

	if (!gpio_is_valid(irq->gpio)) {
		dev_err(dev, "gpio is invalid\n");
		ret = -EINVAL;
		goto get_gpio_err;
	}

	ret = gpio_request_one(irq->gpio, GPIOF_IN, "hi6401_irq");
	if (0 > ret) {
		dev_err(dev, "failed to request gpio%d\n", irq->gpio);
		goto get_gpio_err;
	}

	irq->irq = gpio_to_irq(irq->gpio);

	irq->domain = irq_domain_add_simple(np, HI6401_MAX_IRQS, 0,
					    &hi6401_domain_ops, irq);
	if (!irq->domain) {
		dev_err(dev, "irq domain error\n");
		ret = -ENODEV;
		goto gpio_err;
	}

	for (i = 0; i < HI6401_MAX_IRQS; i++) {
		virq = irq_create_mapping(irq->domain, i);
		if (virq == NO_IRQ) {
			dev_err(dev, "Failed mapping hwirq\n");
			ret = -ENOSPC;
			goto gpio_err;
		}
		irq->irqs[i] = virq;
	}

	ret = request_irq(irq->irq, hi6401_irq_handler,
				   IRQF_TRIGGER_LOW | IRQF_NO_SUSPEND,
				   "hi6401_irq", irq);
	if (0 > ret) {
		dev_err(dev, "could not claim irq %d\n", ret);
		ret = -ENODEV;
		goto gpio_err;
	}
	irq->hi6401_irq_delay_wq = create_singlethread_workqueue("hi6401_irq_delay_wq");
	if (!(irq->hi6401_irq_delay_wq)) {
		pr_err("%s(%u) : workqueue create failed", __FUNCTION__,__LINE__);
		ret = -ENOMEM;
		goto irq_delay_wq_err;
	}
	INIT_DELAYED_WORK(&irq->hi6401_irq_delay_work, hi6401_irq_work_func);

	irq->pll_delay_wq = create_singlethread_workqueue("pll_delay_wq");
	if (!(irq->pll_delay_wq)) {
		pr_err("%s : pll_delay_wq create failed", __FUNCTION__);
		ret = -ENOMEM;
		goto pll_delay_wq_err;
	}
	INIT_DELAYED_WORK(&irq->pll_delay_work, hi6401_pll_work_func);

	/* populate sub nodes */
	of_platform_populate(np, of_hi6401_irq_child_match_tbl, NULL, dev);

	return 0;

pll_delay_wq_err:
	if(irq->hi6401_irq_delay_wq) {
		cancel_delayed_work(&irq->hi6401_irq_delay_work);
		flush_workqueue(irq->hi6401_irq_delay_wq);
		destroy_workqueue(irq->hi6401_irq_delay_wq);
	}
irq_delay_wq_err:
	free_irq(irq->irq, irq);
gpio_err:
	gpio_free(irq->gpio);
get_gpio_err:
#if 0
	clk_disable_unprepare(irq->pmu_audio_clk);
pmu_audio_clk_enable_err:
	devm_clk_put(dev, irq->pmu_audio_clk);
pmu_audio_clk_err:
	clk_disable_unprepare(irq->codec_ssi_clk);
codec_ssi_clk_enable_err:
	devm_clk_put(dev, irq->codec_ssi_clk);
codec_ssi_clk_err:
	codec_ssi_iomux_idle(irq->pctrl);
codec_ssi_iomux_err:
	pinctrl_put(irq->pctrl);
codec_ssi_get_err:
#endif
	devm_iounmap(dev, irq->reg_base_addr);
ioremap_err:
	devm_release_mem_region(dev, irq->res->start,
				resource_size(irq->res));
err_exit:
	devm_kfree(dev, irq);

	return ret;
}

static int hi6401_irq_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi6401_irq *irq = platform_get_drvdata(pdev);

	if(irq->pll_delay_wq) {
		cancel_delayed_work(&irq->pll_delay_work);
		flush_workqueue(irq->pll_delay_wq);
		destroy_workqueue(irq->pll_delay_wq);
	}
	if(irq->hi6401_irq_delay_wq) {
		cancel_delayed_work(&irq->hi6401_irq_delay_work);
		flush_workqueue(irq->hi6401_irq_delay_wq);
		destroy_workqueue(irq->hi6401_irq_delay_wq);
	}
	free_irq(irq->irq, irq);
	gpio_free(irq->gpio);
#if 0
	clk_disable_unprepare(irq->pmu_audio_clk);
	devm_clk_put(dev, irq->pmu_audio_clk);
	clk_disable_unprepare(irq->codec_ssi_clk);
	devm_clk_put(dev, irq->codec_ssi_clk);
	codec_ssi_iomux_idle(irq->pctrl);
	pinctrl_put(irq->pctrl);
#endif
	devm_iounmap(dev, irq->reg_base_addr);
	devm_release_mem_region(dev, irq->res->start,
				resource_size(irq->res));
	devm_kfree(dev, irq);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static int hi6401_irq_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct device *dev = &pdev->dev;
	struct hi6401_irq *irq = dev_get_drvdata(dev);
	int ret = 0; 

	BUG_ON(NULL == irq);

	dev_info(dev, "%s+", __FUNCTION__);

	mutex_lock(&irq->sr_mutex);
#if 0
	clk_disable_unprepare(irq->pmu_audio_clk);

	clk_disable_unprepare(irq->codec_ssi_clk);

	ret = codec_ssi_iomux_idle(irq->pctrl);
	if (0 != ret)
		dev_err(dev, "codec ssi set iomux idle err\n");
#endif
	dev_info(dev, "%s-", __FUNCTION__);

	return ret;
}

static int hi6401_irq_resume(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi6401_irq *irq = dev_get_drvdata(dev);
	int ret = 0;

	BUG_ON(NULL == irq);

	dev_info(dev, "%s+", __FUNCTION__);

#if 0
	ret = codec_ssi_iomux_default(irq->pctrl);
	if (0 != ret)
		goto err_exit;

	ret = clk_prepare_enable(irq->codec_ssi_clk);
	if (0 != ret) {
		dev_err(dev, "codec_ssi_clk :clk prepare enable failed !\n");
		goto err_exit;
	}

	ret = clk_prepare_enable(irq->pmu_audio_clk);
	if (0 != ret) {
		dev_err(dev, "pmu_audio_clk :clk prepare enable failed !\n");
		goto err_exit;
	}

err_exit:
#endif
	dev_info(dev, "%s-", __FUNCTION__);

	mutex_unlock(&irq->sr_mutex);

	return ret;
}

static struct platform_driver hi6401_irq_driver = {
	.driver = {
		.name	= "hi6401_irq",
		.owner  = THIS_MODULE,
		.of_match_table = of_hi6401_irq_match,
	},
	.probe		= hi6401_irq_probe,
	.remove		= hi6401_irq_remove,
	.suspend	= hi6401_irq_suspend,
	.resume		= hi6401_irq_resume,
};
module_platform_driver(hi6401_irq_driver);

MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_DESCRIPTION("Hi6401 irq driver");
MODULE_LICENSE("GPL v2");
