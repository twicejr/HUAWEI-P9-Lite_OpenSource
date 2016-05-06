/*
 * Device driver for  hi3xxx power manger
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2011 Hisilicon.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/mfd/hi3xxx_hi3650.h>

static DEFINE_MUTEX(reg_lock_mutex);

static struct of_device_id of_hisi_regulator_hi3xxx_core_child_match_tbl[] = {
	/* regulators */
	{
		.compatible = "hi3xxx-regulator-type1",
	},
	{
		.compatible = "hi3xxx-regulator-type2",
	},
	{ /* end */ }
};

static struct of_device_id of_hisi_regulator_hi3xxx_core_match_tbl[] = {
	{
		.compatible = "hisilicon,hisi_regulator_hi3xxx_core",
	},
	{ /* end */ }
};

static int hisi_regulator_hi3xxx_core_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct hisi_regulator_hi3xxx_core *pmic = NULL;
	int ret = 0;

	pmic = devm_kzalloc(dev, sizeof(*pmic), GFP_KERNEL);
	if (!pmic) {
		dev_err(dev, "cannot allocate hisi_regulator_hi3xxx_core device info\n");
		return -ENOMEM;
	}

	/* get resources */
	pmic->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!pmic->res) {
		dev_err(dev, "platform_get_resource err !\n");
		return -ENOENT;
	}

	if (!devm_request_mem_region(dev, pmic->res->start,
				     resource_size(pmic->res),
				     pdev->name)) {
		dev_err(dev, "cannot claim register memory\n");
		return -ENOMEM;
	}

	pmic->regs = devm_ioremap(dev, pmic->res->start,
				  resource_size(pmic->res));
	if (!pmic->regs) {
		dev_err(dev, "cannot map register memory\n");
		return -ENOMEM;
	}
	platform_set_drvdata(pdev, pmic);

	of_platform_populate(np, of_hisi_regulator_hi3xxx_core_child_match_tbl, NULL, dev);

	return ret;

}

static int hisi_regulator_hi3xxx_core_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hisi_regulator_hi3xxx_core *pmic = platform_get_drvdata(pdev);

	devm_iounmap(dev, pmic->regs);
	devm_release_mem_region(dev, pmic->res->start,
				resource_size(pmic->res));
	devm_kfree(dev, pmic);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static struct platform_driver hisi_regulator_hi3xxx_core_driver = {
	.driver = {
		.name	= "hisi_regulator_hi3xxx_core",
		.owner  = THIS_MODULE,
		.of_match_table = of_hisi_regulator_hi3xxx_core_match_tbl,
	},
	.probe	= hisi_regulator_hi3xxx_core_probe,
	.remove	= hisi_regulator_hi3xxx_core_remove,
};

static int __init hisi_regulator_hi3xxx_core_init(void)
{
	return platform_driver_register(&hisi_regulator_hi3xxx_core_driver);
}
fs_initcall(hisi_regulator_hi3xxx_core_init);

static void __exit hisi_regulator_hi3xxx_core_exit(void)
{
	platform_driver_unregister(&hisi_regulator_hi3xxx_core_driver);
}
module_exit(hisi_regulator_hi3xxx_core_exit);

MODULE_DESCRIPTION("Hisi regulator hi3xxx driver");
MODULE_LICENSE("GPL v2");
