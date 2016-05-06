/*
 * Hisilicon CCI extra driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <asm/cacheflush.h>
#include <asm/smp_plat.h>
#include <linux/arm-cci.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/perf_event.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/syscore_ops.h>

#define CCI400_SPEC_CTRL           (0x0004)

#define CCI400_SLAVE_RQOR_OFFSET   (0x100)
#define CCI400_SLAVE_WQOR_OFFSET   (0x104)
#define CCI400_SLAVE_QCR_OFFSET    (0x10C)
#define CCI400_SLAVE_MOTR_OFFSET   (0x110)
#define CCI400_SLAVE_RTR_OFFSET    (0x130)
#define CCI400_SLAVE_QRSFR_OFFSET  (0x134)
#define CCI400_SLAVE_QRR_OFFSET    (0x138)

#define CRG_CCI500_CTRL0_OFFSET    (0x228)


/* qos config for cci port, cci400 only */
struct cci_extra_port_config {
	void __iomem *base;
	unsigned int qcr_set;
	unsigned int qcr_val;   /* qos-control */
	unsigned int rtr_set;
	unsigned int rtr_val;   /* regulator-target */
	unsigned int sfr_set;
	unsigned int sfr_val;   /* salar */
	unsigned int qrr_set;
	unsigned int qrr_val;   /* qos-range */
	unsigned int rqor_set;
	unsigned int rqor_val;  /* read-qos-override*/
	unsigned int wqor_set;
	unsigned int wqor_val;  /* write-qos-override*/
};

/* hisilicon cci extra device */
struct cci_extra_dev {
	struct cci_extra_port_config *port_configs;
	int nb_ports;
	unsigned int speculative_dis_set;
	unsigned int speculative_dis_val;
	unsigned int crg_qos_accept_set;
	unsigned int crg_qos_accept_val;
	void __iomem *cci_ctrl_base;
	void __iomem *crg_ctrl_base;
};

static struct cci_extra_dev *cci_extra_device;

/*number of cci port*/
struct cci_extra_port {
	unsigned int nb_ace;
	unsigned int nb_ace_lite;
};

/*max interfaces definition for cci400*/
static const struct cci_extra_port extra_ports = {
	.nb_ace = 2,
	.nb_ace_lite = 3
};

/*no port config for cci500*/
static const struct cci_extra_port no_ports = {
	.nb_ace = 0,
	.nb_ace_lite = 0
};

static const struct of_device_id hisilicon_cci_extra_matches[] = {
	{ .compatible = "hisilicon,cci400-extra", .data = &extra_ports},
	{ .compatible = "hisilicon,cci500-extra", .data = &no_ports},
	{},
};

static const struct of_device_id hisilicon_cci_extra_if_matches[] = {
	{.compatible = "hisilicon,cci400-extra-if", },
	{},
};

static void cci_extra_set_speculative_dis(struct cci_extra_dev *dev)
{
	void __iomem *reg;

	if (!dev->speculative_dis_set)
		return;

	pr_debug("cci_init_speculation: data=0x%x\n",
			 dev->speculative_dis_val);

	reg = dev->cci_ctrl_base + CCI400_SPEC_CTRL;
	writel_relaxed(dev->speculative_dis_val, reg);

	return;
}

static void cci_extra_set_port_qos(struct cci_extra_port_config *config)
{
	void  __iomem *reg;

	if (config->qcr_set) {
		pr_debug("qcr: 0x%x\n", config->qcr_val);
		reg = config->base + CCI400_SLAVE_QCR_OFFSET;
		writel_relaxed(config->qcr_val, reg);
	}

	if (config->rtr_set) {
		pr_debug("rtr: 0x%x\n", config->rtr_val);
		reg = config->base + CCI400_SLAVE_RTR_OFFSET;
		writel_relaxed(config->rtr_val, reg);
	}

	if (config->sfr_set) {
		pr_debug("sfr: 0x%x\n", config->sfr_val);
		reg = config->base + CCI400_SLAVE_QRSFR_OFFSET;
		writel_relaxed(config->sfr_val, reg);
	}

	if (config->qrr_set) {
		pr_debug("qrr: 0x%x\n", config->qrr_val);
		reg = config->base + CCI400_SLAVE_QRR_OFFSET;
		writel_relaxed(config->qrr_val, reg);
	}

	if (config->rqor_set) {
		pr_debug("rqor: 0x%x\n", config->rqor_val);
		reg = config->base +  CCI400_SLAVE_RQOR_OFFSET;
		writel_relaxed(config->rqor_val, reg);
	}

	if (config->wqor_set) {
		pr_debug("wqor: 0x%x\n", config->wqor_val);
		reg = config->base + CCI400_SLAVE_WQOR_OFFSET;
		writel_relaxed(config->wqor_val, reg);
	}

	return;
}

static void cci_extra_set_ports_qos(struct cci_extra_dev *dev)
{
	int i;

	for (i = 0; i < dev->nb_ports; i++)
		cci_extra_set_port_qos(&dev->port_configs[i]);

	return;
}

static void cci_extra_set_qos_accept(struct cci_extra_dev *dev)
{
	unsigned int val;
	void __iomem *reg;

	if (!dev->crg_qos_accept_set)
		return;

	pr_debug("cci_extra_set_qos_accept: data=0x%x\n",
			 dev->crg_qos_accept_val);

	reg = dev->crg_ctrl_base + CRG_CCI500_CTRL0_OFFSET;
	val = readl_relaxed(reg);
	val = val | (dev->crg_qos_accept_val & 0xffff);
	writel_relaxed(val, reg);

	return;
}

#ifdef CONFIG_PM_SLEEP
static void cci_extra_resume(void)
{
	struct cci_extra_dev *dev = cci_extra_device;

	if (!dev)
		return;

	cci_extra_set_speculative_dis(dev);
	cci_extra_set_qos_accept(dev);
	cci_extra_set_ports_qos(dev);

	return;
}
#else
static void cci_extra_resume(void)
{
	return;
}
#endif

static struct syscore_ops cci_extra_syscore_ops = {
	.resume = cci_extra_resume,
};

static int cci_extra_init(void)
{
	const struct of_device_id *id;
	struct cci_extra_dev *dev;
	struct device_node *np, *cp, *crg;
	struct resource res;
	struct cci_extra_port *port = NULL;
	struct cci_extra_port_config *port_configs = NULL;

	int nb_ports = 0;
	int ret = 0;
	int i = 0;
	unsigned int val;
	void __iomem *base;

	np = of_find_matching_node(NULL, hisilicon_cci_extra_matches);
	if (!np)
		return -ENODEV;

	id = of_match_node(hisilicon_cci_extra_matches, np);
	port = (struct cci_extra_port *)(id->data);
	if (!port)
		return -ENODEV;

	nb_ports = port->nb_ace + port->nb_ace_lite;
	if (nb_ports) {
		port_configs = kzalloc(nb_ports*sizeof(*port_configs),
							   GFP_KERNEL);
		if (!port_configs)
			return -ENOMEM;
	}

	dev = kzalloc(sizeof(struct cci_extra_dev), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto err_alloc_dev;
	}
	dev->nb_ports = nb_ports;

	ret = of_address_to_resource(np, 0, &res);
	if (!ret) {
		dev->cci_ctrl_base = ioremap(res.start, resource_size(&res));
		if (!dev->cci_ctrl_base){
			ret = -ENOMEM;
			goto err_cci_ctrl;
		}
	}

	ret = of_property_read_u32(np, "speculative-disable",
							   &val);
	if (!ret) {
		if (!dev->cci_ctrl_base) {
			pr_err("cci_probe: cci_ctrl_base invalid !\n");
			ret = -EINVAL;
			goto err_cci_ctrl;
		} else {
			dev->speculative_dis_set = 1;
			dev->speculative_dis_val = val;
			pr_info("cci_probe: speculative-disable 0x%x\n",
					dev->speculative_dis_val);
		}
	}

	crg = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (IS_ERR(crg)) {
		pr_info("cci_probe: no crgctrl compatible_node\n");
	} else {
		dev->crg_ctrl_base = of_iomap(crg, 0);
		if (!dev->crg_ctrl_base) {
			pr_err("cci_probe: crgctrl of_iomap failed!\n");
			ret = -ENOMEM;
			goto err_crg;
		}
	}

	ret = of_property_read_u32(np, "crg-qos-accept", &val);
	if (!ret) {
		if (NULL == dev->crg_ctrl_base) {
			pr_err("cci_probe: cci_crg_base invalid !\n");
			ret = -EINVAL;
			goto err_crg;
		} else {
			dev->crg_qos_accept_set = 1;
			dev->crg_qos_accept_val = val;
			pr_info("cci_probe: crg-qos-accept 0x%x\n",
					dev->crg_qos_accept_val);
		}
	}

	for_each_child_of_node(np, cp) {
		if (!of_match_node(hisilicon_cci_extra_if_matches, cp))
			continue;

		if (i == nb_ports)
			break;

		ret = of_address_to_resource(cp, 0, &res);
		if (!ret)
			base = ioremap(res.start, resource_size(&res));

		if (ret || !base) {
			WARN(1, "unable to ioremap CCI port %d\n", i);
			continue;
		}

		port_configs[i].base = base;/*[false alarm]*/
		ret = of_property_read_u32(cp, "qos-control", &val);
		if (!ret) {
			port_configs[i].qcr_set = 1;
			port_configs[i].qcr_val = val;
		}

		ret = of_property_read_u32(cp, "regulator-target", &val);
		if (!ret) {
			port_configs[i].rtr_set = 1;
			port_configs[i].rtr_val = val;
		}

		ret = of_property_read_u32(cp, "scalar", &val);
		if (!ret) {
			port_configs[i].sfr_set = 1;
			port_configs[i].sfr_val = val;
		}

		ret = of_property_read_u32(cp, "qos-range", &val);
		if (!ret) {
			port_configs[i].qrr_set = 1;
			port_configs[i].qrr_val = val;
		}

		ret = of_property_read_u32(cp, "read-qos-override", &val);
		if (!ret) {
			port_configs[i].rqor_set = 1;
			port_configs[i].rqor_val = val;
		}

		ret = of_property_read_u32(cp, "write-qos-override", &val);
		if (!ret) {
			port_configs[i].wqor_set = 1;
			port_configs[i].wqor_val = val;
		}

		i++;
	}
	dev->port_configs = port_configs;

	cci_extra_set_speculative_dis(dev);
	cci_extra_set_qos_accept(dev);
	cci_extra_set_ports_qos(dev);

	register_syscore_ops(&cci_extra_syscore_ops);

	cci_extra_device = dev;

	pr_info("Hisilicon CCI Extra driver probed\n");

	return 0;

err_crg:
	if (dev->cci_ctrl_base)
		iounmap(dev->cci_ctrl_base);
err_cci_ctrl:
	kfree(dev);
err_alloc_dev:
	kfree(port_configs);

	return ret;
}


early_initcall(cci_extra_init);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hisilicon CCI Extra support");

