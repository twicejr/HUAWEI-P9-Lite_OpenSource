/*
 * hi6402-gpio driver.
 *
 * Copyright (c) 2014 Hisilicon Technologies CO.Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/clk.h>
#include <linux/mutex.h>
#include <linux/pinctrl/consumer.h>
#include <linux/irq.h>
#include <linux/mfd/hi6402_gpio.h>
#include <linux/hisi/hi64xx/hi64xx_compat.h>
#include <linux/hisi/hi64xx/hi64xx_regs.h>

#define GPIODIR 0x400
#define GPIOIS  0x404
#define GPIOIBE 0x408
#define GPIOIEV 0x40C
#define GPIOIE  0x410
#define GPIOMIS 0x418
#define GPIOIC  0x41C

#define HI6402_AWAKE_GPIO_CNT 4
#define HI6402_GPIO_NR 8
#define HI6402_GPIO_MASK 0xff

#define HI6402_GPIO_AWAKE_UNMASK 0x00000001
#define HI6402_GPIO_AWAKE_MASK 0x00000002

#define HI6402_AWAKE_GPIO_SEL(_gpio, _flag, _irq0, _irq1, _status, _mask_ctrl)	\
{				\
	.binding_gpio = _gpio,	\
	.flag = _flag,		\
	.irq[0] = _irq0,	\
	.irq[1] = _irq1,	\
	.is_requested = _status,	\
	.mask_ctrl = _mask_ctrl,	\
}


#ifdef CONFIG_HI6402_GPIO_PM_SUPPORT
struct hi6402_gpio_context_save_regs {
	u8 gpio_data;
	u8 gpio_dir;
	u8 gpio_is;
	u8 gpio_ibe;
	u8 gpio_iev;
	u8 gpio_ie;
};
#endif

struct hi6402_gpio {
	struct irq_domain *domain;
	struct gpio_chip gc;
	struct clk *audio_clk;
	struct mutex lock;
	struct mutex irq_lock;
	int p_irq;
	unsigned reg_offset;
	u8 gpioie;
	u8 gpiois;
	u8 gpioiev;
	u8 gpioibe;
#ifdef CONFIG_HI6402_GPIO_PM_SUPPORT
	struct hi6402_gpio_context_save_regs csave_regs;
#endif
};

struct hi6402_gpio_awake_irq {
	int binding_gpio;
	unsigned flag;
	int irq[2];
	unsigned is_requested;
	unsigned mask_ctrl;
};
struct irqname2num{
	const char *irq_name;
	const int irq_num;
};
static const char *hi6402_awake_irq_names[HI6402_AWAKE_GPIO_CNT*2] = {
	"pos_awake_irq0",
	"neg_awake_irq0",
	"pos_awake_irq1",
	"neg_awake_irq1",
	"pos_awake_irq2",
	"neg_awake_irq2",
	"pos_awake_irq3",
	"neg_awake_irq3",
};

static const struct irqname2num hi6402_awake_irq_name_num[HI6402_AWAKE_GPIO_CNT*2] = {
	{"pos_awake_irq0",24},
	{"neg_awake_irq0",25},
	{"pos_awake_irq1",26},
	{"neg_awake_irq1",27},
	{"pos_awake_irq2",28},
	{"neg_awake_irq2",29},
	{"pos_awake_irq3",30},
	{"neg_awake_irq3",31},
};

static struct hi6402_gpio_awake_irq gpio_awake_irq[HI6402_AWAKE_GPIO_CNT] = {
	HI6402_AWAKE_GPIO_SEL(-1, 0, -1, -1, 0, 0),
	HI6402_AWAKE_GPIO_SEL(-1, 0, -1, -1, 0, 0),
	HI6402_AWAKE_GPIO_SEL(-1, 0, -1, -1, 0, 0),
	HI6402_AWAKE_GPIO_SEL(-1, 0, -1, -1, 0, 0),
};
static unsigned hi6402_gpio_base;
static int hi6402_get_awake_irq_num(const char* name)
{
	int irq = 0, i;
	for(i = 0; i < HI6402_AWAKE_GPIO_CNT * 2; i++){
		if(!strcmp(hi6402_awake_irq_name_num[i].irq_name,name)){
			irq = hi6402_awake_irq_name_num[i].irq_num;
			pr_info("%s: get awake irq num %d\n",__FUNCTION__, irq);
			break;
		}
	}
	return irq;
}
static u8 hi6402_gpio_readb(struct hi6402_gpio *chip, unsigned reg)
{
	return (u8)hi64xx_compat_reg_read(chip->reg_offset + reg); /* [false alarm]:funtion hi6402_gpio_readb return a unsigned value */
}

static void hi6402_gpio_writeb(struct hi6402_gpio *chip, u8 val, unsigned reg)
{
	hi64xx_compat_reg_write(chip->reg_offset + reg, (unsigned)val);
}

static int hi6402_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	/*
	 * Map back to global GPIO space and request muxing, the direction
	 * parameter does not matter for this controller.
	 */
	unsigned gpio = (unsigned)chip->base + offset;

	return pinctrl_request_gpio(gpio);
}

static void hi6402_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	int gpio = chip->base + offset;

	pinctrl_free_gpio(gpio);
}

static int hi6402_gpio_direction_input(struct gpio_chip *gc, unsigned offset)
{
	struct hi6402_gpio *chip = container_of(gc, struct hi6402_gpio, gc);
	u8 gpiodir;

	if (offset >= gc->ngpio)
		return -EINVAL;

	mutex_lock(&chip->lock);

	gpiodir = hi6402_gpio_readb(chip, GPIODIR);
	gpiodir &= ~(1 << offset);
	hi6402_gpio_writeb(chip, gpiodir, GPIODIR);

	mutex_unlock(&chip->lock);

	return 0;
}

static int hi6402_gpio_direction_output(struct gpio_chip *gc, unsigned offset, int value)
{
	struct hi6402_gpio *chip = container_of(gc, struct hi6402_gpio, gc);
	u8 gpiodir;

	if (offset >= gc->ngpio)
		return -EINVAL;

	mutex_lock(&chip->lock);

	hi6402_gpio_writeb(chip, !!value << offset, 1 << (offset + 2));
	gpiodir = hi6402_gpio_readb(chip, GPIODIR);
	gpiodir |= 1 << offset;
	hi6402_gpio_writeb(chip, gpiodir, GPIODIR);

	/*
	 * gpio value is set again, because hi6402 gpio doesn't allow to set value of
	 * a gpio pin before configuring it in OUT mode.
	 */
	hi6402_gpio_writeb(chip, !!value << offset, 1 << (offset + 2));
	mutex_unlock(&chip->lock);

	return 0;
}

static int hi6402_gpio_get_value(struct gpio_chip *gc, unsigned offset)
{
	struct hi6402_gpio *chip = container_of(gc, struct hi6402_gpio, gc);

	return !!hi6402_gpio_readb(chip, 1 << (offset + 2));
}

static void hi6402_gpio_set_value(struct gpio_chip *gc, unsigned offset, int value)
{
	struct hi6402_gpio *chip = container_of(gc, struct hi6402_gpio, gc);

	hi6402_gpio_writeb(chip, (!!value) << offset, 1 << (offset + 2));
}

static int hi6402_gpio_to_irq(struct gpio_chip *gc, unsigned offset)
{
	struct hi6402_gpio *chip = container_of(gc, struct hi6402_gpio, gc);
	return irq_create_mapping(chip->domain, offset);
}

static bool hi6402_gpio_irq_is_awake(int irq, int *gpio)
{
	int i;

	for (i = 0; i < (HI6402_AWAKE_GPIO_CNT * 2); i++) {
		if (irq == gpio_awake_irq[i>>1].irq[i%2]) {
			*gpio = gpio_awake_irq[i>>1].binding_gpio;
			return true;
		}
	}
	return false;
}

static int virq_to_phyirq(int virq)
{
	struct irq_data *irq_data = irq_get_irq_data(virq);
	if (unlikely(!irq_data)) {
		pr_err("%s: irq_data is NULL", __func__);
		return -EINVAL;
	}
	return irq_data->hwirq;
}

static irqreturn_t hi6402_gpio_irq_handler(int irq, void *data)
{
	unsigned long pending;
	int offset, gpio;
	int hwirq;
	struct hi6402_gpio *chip = (struct hi6402_gpio *)data;
	if (!chip)
		return IRQ_HANDLED;

	hwirq = virq_to_phyirq(irq);

	mutex_lock(&chip->lock);
	pending = hi6402_gpio_readb(chip, GPIOMIS);
	pending &= HI6402_GPIO_MASK;
	hi6402_gpio_writeb(chip, (u8)pending, GPIOIC);
	mutex_unlock(&chip->lock);

	if (hi6402_gpio_irq_is_awake(hwirq, &gpio))
		pending |= BIT(gpio % HI6402_GPIO_NR);

	if (pending) {
		for_each_set_bit(offset, &pending, HI6402_GPIO_NR)
			handle_nested_irq(hi6402_gpio_to_irq(&chip->gc, offset));
	}

	return IRQ_HANDLED;
}

static int hi6402_gpio_is_binding_awake_irq(int gpio)
{
	int i, found = -ENOENT;

	for (i = 0; i < HI6402_AWAKE_GPIO_CNT ; i++) {
		if (gpio_awake_irq[i].binding_gpio == gpio) {
			found = i;
			break;
		}
	}

	return found;
}

static void hi6402_gpio_irq_mask(struct irq_data *d)
{
	struct hi6402_gpio *chip = irq_data_get_irq_chip_data(d);
	struct gpio_chip *gc = &chip->gc;
	int offset = irqd_to_hwirq(d);
	int ret;

	ret = hi6402_gpio_is_binding_awake_irq(gc->base + offset);
	if (ret < 0)
		chip->gpioie &= ~(1 << offset);
	else
		gpio_awake_irq[ret].mask_ctrl = HI6402_GPIO_AWAKE_MASK;
}

static void hi6402_gpio_irq_unmask(struct irq_data *d)
{
	struct hi6402_gpio *chip = irq_data_get_irq_chip_data(d);
	struct gpio_chip *gc = &chip->gc;
	int offset = irqd_to_hwirq(d);
	int ret;

	ret = hi6402_gpio_is_binding_awake_irq(gc->base + offset);
	if (ret < 0)
		chip->gpioie |= 1 << offset;
	else
		gpio_awake_irq[ret].mask_ctrl = HI6402_GPIO_AWAKE_UNMASK;
}

static int hi6402_gpio_irq_type(struct irq_data *d, unsigned int trigger)
{
	struct hi6402_gpio *chip = irq_data_get_irq_chip_data(d);
	int offset = irqd_to_hwirq(d);
	struct gpio_chip *gc = &chip->gc;
	int ret, gpio;

	gpio = gc->base + offset;

	ret = hi6402_gpio_is_binding_awake_irq(gpio);
	if (ret < 0)
		goto not_awake_irq;

	gpio_awake_irq[ret].flag |= (trigger & IRQ_TYPE_EDGE_BOTH);
	if (!(gpio_awake_irq[ret].flag & IRQ_TYPE_EDGE_BOTH)) {
		return -ENOENT;
	}
	gpio_awake_irq[ret].is_requested |= 0x01;
	return 0;

not_awake_irq:
	if (trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) {
		chip->gpiois |= 1 << offset;
		if (trigger & IRQ_TYPE_LEVEL_HIGH)
			chip->gpioiev |= 1 << offset;
		else
			chip->gpioiev &= ~(1 << offset);
	} else {
		chip->gpiois &= ~(1 << offset);
	}

	if ((trigger & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH) {
		chip->gpioibe |= 1 << offset;
	} else {
		chip->gpioibe &= ~(1 << offset);
		if (trigger & IRQ_TYPE_EDGE_RISING)
			chip->gpioiev |= 1 << offset;
		else if (trigger & IRQ_TYPE_EDGE_FALLING)
			chip->gpioiev &= ~(1 << offset);
	}

	return 0;
}

static int hi6402_gpio_awake_irq_request(struct hi6402_gpio *chip, struct irq_data *d)
{
	struct gpio_chip *gc = &chip->gc;
	int offset = irqd_to_hwirq(d);
	int ret, i;

	for (i = 0; i < HI6402_AWAKE_GPIO_CNT ; i++) {
		if (((gc->base + offset) == gpio_awake_irq[i].binding_gpio) && (gpio_awake_irq[i].is_requested & 0x01)) {
			if ((gpio_awake_irq[i].flag & IRQ_TYPE_EDGE_RISING) && (!(gpio_awake_irq[i].is_requested & 0x02))) {
				ret = hi64xx_compat_request_irq(gpio_awake_irq[i].irq[0], hi6402_gpio_irq_handler, dev_name(gc->dev), (void*)chip);
				if (ret) {
					dev_err(gc->dev, "gpio-%d could not request rising-edge awake irq\n",
						gpio_awake_irq[i].binding_gpio);
					return ret;
				}
				gpio_awake_irq[i].is_requested |= 0x02;
			} else {
				if ((!(gpio_awake_irq[i].flag & IRQ_TYPE_EDGE_RISING)) && (gpio_awake_irq[i].is_requested & 0x02)) {
					devm_free_irq(gc->dev, gpio_awake_irq[i].irq[0], chip);
					gpio_awake_irq[i].is_requested &= ~0x02;
				}
			}

			if ((gpio_awake_irq[i].flag & IRQ_TYPE_EDGE_FALLING) && (!(gpio_awake_irq[i].is_requested & 0x04))) {
				ret = hi64xx_compat_request_irq(gpio_awake_irq[i].irq[1], hi6402_gpio_irq_handler, dev_name(gc->dev), (void*)chip);
				if (ret) {
					dev_err(gc->dev, "gpio-%d could not request falling-edge awake irq\n",
						gpio_awake_irq[i].binding_gpio);
					if ((gpio_awake_irq[i].flag & IRQ_TYPE_EDGE_RISING) && (gpio_awake_irq[i].is_requested & 0x02)) {
						devm_free_irq(gc->dev, gpio_awake_irq[i].irq[0], chip);
						gpio_awake_irq[i].is_requested &= ~0x02;
					}
					return ret;
				}
				gpio_awake_irq[i].is_requested |= 0x04;
			} else {
				if ((!(gpio_awake_irq[i].flag & IRQ_TYPE_EDGE_FALLING)) && (gpio_awake_irq[i].is_requested & 0x04)) {
					devm_free_irq(gc->dev, gpio_awake_irq[i].irq[1], chip);
					gpio_awake_irq[i].is_requested &= ~0x04;
				}
			}

			gpio_awake_irq[i].is_requested &= ~0x01;
		}
	}
	return 0;
}

static void hi6402_gpio_awake_irq_ctrl(struct hi6402_gpio *chip, int gpio)
{
	unsigned data;
	int ret;

	ret =hi6402_gpio_is_binding_awake_irq(gpio);
	if (ret < 0)
		return;

	data = hi64xx_compat_reg_read(HI64xx_REG_IRQM_3);

	if (gpio_awake_irq[ret].flag & IRQ_TYPE_EDGE_RISING) {
		if (gpio_awake_irq[ret].mask_ctrl & HI6402_GPIO_AWAKE_UNMASK)
			data &= ~BIT(ret<<1);
		if (gpio_awake_irq[ret].mask_ctrl & HI6402_GPIO_AWAKE_MASK)
			data |= BIT(ret << 1);
	}
	if (gpio_awake_irq[ret].flag & IRQ_TYPE_EDGE_FALLING) {
		if (gpio_awake_irq[ret].mask_ctrl & HI6402_GPIO_AWAKE_UNMASK)
			data &= ~BIT(1+(ret<<1));
		if (gpio_awake_irq[ret].mask_ctrl & HI6402_GPIO_AWAKE_MASK)
			data |= BIT(1+(ret<<1));
	}

	hi64xx_compat_reg_write(HI64xx_REG_IRQM_3, data);
}

static void hi6402_gpio_irq_bus_lock(struct irq_data *d)
{
	struct hi6402_gpio *chip = irq_data_get_irq_chip_data(d);

	mutex_lock(&chip->irq_lock);
}

static void hi6402_gpio_irq_bus_unlock(struct irq_data *d)
{
	struct hi6402_gpio *chip = irq_data_get_irq_chip_data(d);
	struct gpio_chip *gc = &chip->gc;
	int offset = irqd_to_hwirq(d);
	int ret;

	mutex_lock(&chip->lock);

	ret = hi6402_gpio_awake_irq_request(chip, d);
	hi6402_gpio_awake_irq_ctrl(chip, gc->base + offset);

	hi6402_gpio_writeb(chip, chip->gpiois, GPIOIS);
	hi6402_gpio_writeb(chip, chip->gpioibe, GPIOIBE);
	hi6402_gpio_writeb(chip, chip->gpioiev, GPIOIEV);
	hi6402_gpio_writeb(chip, chip->gpioie, GPIOIE);

	mutex_unlock(&chip->lock);
	mutex_unlock(&chip->irq_lock);
}

static struct irq_chip hi6402_gpio_irqchip = {
	.name			= "gpio-hi6402",
	.irq_mask		= hi6402_gpio_irq_mask,
	.irq_unmask		= hi6402_gpio_irq_unmask,
	.irq_disable		= hi6402_gpio_irq_mask,
	.irq_enable		= hi6402_gpio_irq_unmask,
	.irq_set_type		= hi6402_gpio_irq_type,
	.irq_bus_lock		= hi6402_gpio_irq_bus_lock,
	.irq_bus_sync_unlock	= hi6402_gpio_irq_bus_unlock,
};

static int hi6402_gpio_irq_map(struct irq_domain *d, unsigned int irq,
			irq_hw_number_t hwirq)
{
	irq_set_chip_data(irq, d->host_data);
	irq_set_chip(irq, &hi6402_gpio_irqchip);
	irq_set_nested_thread(irq, true);
	set_irq_flags(irq, IRQF_VALID);

	return 0;
}

static const struct irq_domain_ops hi6402_gpio_irq_domain_ops = {
	.map = hi6402_gpio_irq_map,
	.xlate = irq_domain_xlate_twocell,
};

static int hi6402_get_awake_irq(struct platform_device *pdev)
{
	int irq;
	int i, irq_cnt = HI6402_AWAKE_GPIO_CNT * 2;

	for (i = 0; i < irq_cnt; i++) {
		//irq = platform_get_irq_byname(pdev, hi6402_awake_irq_names[i]);
		irq = hi6402_get_awake_irq_num(hi6402_awake_irq_names[i]);
		if (irq == 0) {
			pr_err("could not find '%s' irq\n", hi6402_awake_irq_names[i]);
			return irq;
		}
		gpio_awake_irq[i>>1].irq[i%2] = irq;
	}

	return 0;
}

static int hi6402_gpio_irq_setup(struct hi6402_gpio *chip, struct platform_device *pdev)
{
	struct gpio_chip *gc = &chip->gc;
	const __be32 *mux;
	int gpio_sel_array[HI6402_AWAKE_GPIO_CNT];
	int ret, i, size, j = 0;

	mutex_init(&chip->irq_lock);

	chip->gpioiev = hi6402_gpio_readb(chip, GPIOIEV);
	chip->gpiois = hi6402_gpio_readb(chip, GPIOIS);
	chip->gpioibe = hi6402_gpio_readb(chip, GPIOIBE);
	chip->gpioie = 0;

	/* disable irqs */
	hi6402_gpio_writeb(chip, 0, GPIOIE);

	chip->domain = irq_domain_add_linear(gc->of_node, HI6402_GPIO_NR,
					     &hi6402_gpio_irq_domain_ops, chip);

	gc->to_irq = hi6402_gpio_to_irq;

	/* request thread irq, and its' parent irq is hi6402 irq controller */
	ret = hi64xx_compat_request_irq((int)chip->p_irq, hi6402_gpio_irq_handler, dev_name(gc->dev), (void*)chip);
	if (ret) {
		dev_err(gc->dev, "could not requset irq-%d\n", chip->p_irq);
		goto error;
	}

	mux = of_get_property(gc->of_node, "awake-gpio", &size);
	if (NULL == mux) {
		pr_debug("%s: gpios of the group could not support to awake\n", dev_name(gc->dev));
		goto get_awake_irq_num;
	}

	size /= sizeof(*mux);

	ret = of_property_read_u32_array(gc->of_node, "awake-gpio", gpio_sel_array, size);

	for (i = 0; i < HI6402_AWAKE_GPIO_CNT; i++) {
		if ((gpio_awake_irq[i].binding_gpio == -1) && (j < size)) {
			gpio_awake_irq[i].binding_gpio = gpio_sel_array[j++] + gc->base;
			hi64xx_compat_reg_write(HI64xx_AP_GPIO0_SEL + i,
				gpio_awake_irq[i].binding_gpio - hi6402_gpio_base);
		}
	}

	if (ret || (j != size)) {
		dev_err(gc->dev, "failed to get awake-gpio number\n");
		ret = -EINVAL;
		goto error;
	}

get_awake_irq_num:
	if (of_get_property(gc->of_node, "awake-irq-number", NULL)) {
		ret = hi6402_get_awake_irq(pdev);
		if (ret)
			goto error;
	}

	return 0;

error:
	irq_domain_remove(chip->domain);
	return ret;
}

/* Parse gpio base from DT */
static int hi6402_parse_gpio_base(struct device *dev)
{
	struct device_node *np = dev->of_node;
	int ret = -EINVAL;

	if (of_property_read_u32(np, "linux,gpio-base", &ret))
		return -ENOENT;
	if (ret >= 0) {
		hi6402_gpio_base = ret;
		return ret;
	}
	return -EINVAL;
}

static int hi6402_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = pdev->dev.of_node;
	struct hi6402_gpio_platform_data *pdata = dev->platform_data;
	struct hi6402_gpio *chip;
	int ret, i, irq_base;
	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;

	mutex_init(&chip->lock);

	ret = of_property_read_u32(np, "reg-offset", &chip->reg_offset);
	if (ret) {
		dev_err(dev, "could not find gpio offset address\n");
		ret = -ENOENT;
		goto error;
	}

	if (pdata) {
		chip->gc.base = pdata->gpio_base;
		irq_base = pdata->irq_base;
		if (irq_base <= 0) {
			ret = -ENODEV;
			goto error;
		}
	} else {
		chip->gc.base = hi6402_parse_gpio_base(dev);
		irq_base = 0;
	}
	ret = of_property_read_u32(np, "irq_hi6402_gpio", &chip->p_irq);
	if (ret) {
		dev_err(dev, "could not find irq base\n");
		ret = -ENOENT;
		goto error;
	}
	/* Hook the request()/free() for pinctrl operation */
	if (of_get_property(np, "gpio-ranges", NULL)) {
		chip->gc.request = hi6402_gpio_request;
		chip->gc.free = hi6402_gpio_free;
	}
	chip->gc.direction_input = hi6402_gpio_direction_input;
	chip->gc.direction_output = hi6402_gpio_direction_output;
	chip->gc.get = hi6402_gpio_get_value;
	chip->gc.set = hi6402_gpio_set_value;
	chip->gc.to_irq = hi6402_gpio_to_irq;
	chip->gc.can_sleep = 1;
	chip->gc.ngpio = HI6402_GPIO_NR;
	chip->gc.label = dev_name(dev);
	chip->gc.dev = dev;
	chip->gc.owner = THIS_MODULE;
	ret = gpiochip_add(&chip->gc);
	if (ret) {
		dev_err(dev, "could not add gpio chip\n");
		ret = -ENODEV;
		goto error;
	}

	for (i = 0; i < HI6402_GPIO_NR; i++) {
		if (pdata) {
			if (pdata->directions & (1 << i))
				hi6402_gpio_direction_output(&chip->gc, i,
						pdata->values & (1 << i));
			else
				hi6402_gpio_direction_input(&chip->gc, i);
		}
	}
	ret = hi6402_gpio_irq_setup(chip, pdev);
	if (ret) {
		ret = gpiochip_remove(&chip->gc);
		ret = -ENODEV;
		goto error;
	}

	platform_set_drvdata(pdev, chip);
	dev_err(dev, "init ok");

	return 0;

error:
	if (chip->audio_clk)
		clk_disable_unprepare(chip->audio_clk);
	pr_err("%s: error\n", __FUNCTION__);
	return ret;
}

#ifdef CONFIG_HI6402_GPIO_PM_SUPPORT
static int hi6402_gpio_suspend(struct device *dev)
{
	struct hi6402_gpio *chip = dev_get_drvdata(dev);
	int offset;

	chip->csave_regs.gpio_data = 0;
	chip->csave_regs.gpio_dir = hi6402_gpio_readb(chip, GPIODIR);
	chip->csave_regs.gpio_is = hi6402_gpio_readb(chip, GPIOIS);
	chip->csave_regs.gpio_ibe = hi6402_gpio_readb(chip, GPIOIBE);
	chip->csave_regs.gpio_iev = hi6402_gpio_readb(chip, GPIOIEV);
	chip->csave_regs.gpio_ie = hi6402_gpio_readb(chip, GPIOIE);

	for (offset = 0; offset < HI6402_GPIO_NR; offset++) {
		if (chip->csave_regs.gpio_dir & (1 << offset))
			chip->csave_regs.gpio_data |=
				hi6402_gpio_get_value(&chip->gc, offset) << offset;
	}

	return 0;
}

static int hi6402_gpio_resume(struct device *dev)
{
	struct hi6402_gpio *chip = dev_get_drvdata(dev);
	int offset;

	for (offset = 0; offset < HI6402_GPIO_NR; offset++) {
		if (chip->csave_regs.gpio_dir & (1 << offset))
			hi6402_gpio_direction_output(&chip->gc, offset,
					chip->csave_regs.gpio_data &
					(1 << offset));
		else
			hi6402_gpio_direction_input(&chip->gc, offset);
	}

	hi6402_gpio_writeb(chip, chip->csave_regs.gpio_is, GPIOIS);
	hi6402_gpio_writeb(chip, chip->csave_regs.gpio_ibe, GPIOIBE);
	hi6402_gpio_writeb(chip, chip->csave_regs.gpio_iev, GPIOIEV);
	hi6402_gpio_writeb(chip, chip->csave_regs.gpio_ie, GPIOIE);

	return 0;
}

static const struct dev_pm_ops hi6402_gpio_dev_pm_ops = {
	.suspend = hi6402_gpio_suspend,
	.resume = hi6402_gpio_resume,
	.freeze = hi6402_gpio_suspend,
	.restore = hi6402_gpio_resume,
};
#endif

static struct of_device_id hi6402_gpio_of_match[] = {
	{ .compatible = "hisilicon,hi6402-gpio" },
	{ },
};
MODULE_DEVICE_TABLE(of, hi6402_gpio_of_match);

static struct platform_driver hi6402_gpio_driver = {
	.probe		= hi6402_gpio_probe,
	.driver		= {
		.name	= "hi6402-gpio",
		.owner	= THIS_MODULE,
#ifdef CONFIG_HI6402_GPIO_PM_SUPPORT
		.pm	= &hi6402_gpio_dev_pm_ops,
#endif
		.of_match_table	= hi6402_gpio_of_match,
	},
};

static int __init hi6402_gpio_init(void)
{
	return platform_driver_register(&hi6402_gpio_driver);
}

static void __exit hi6402_gpio_exit(void)
{
	platform_driver_unregister(&hi6402_gpio_driver);
}

rootfs_initcall(hi6402_gpio_init);
module_exit(hi6402_gpio_exit);

MODULE_AUTHOR("hw.wangxiaoyin@hisilicon.com");
MODULE_DESCRIPTION("HI6402 GPIO driver");
MODULE_LICENSE("GPL");
