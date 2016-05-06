/* linux/drivers/usb/phy/phy-hisi-usb2.c
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
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/usb/otg.h>
#include <linux/usb/hisi_usb_phy.h>
#include <linux/platform_data/hisi-usbphy.h>

#include "phy-hisi-usb.h"

static int hisi_usbphy_set_host(struct usb_otg *otg, struct usb_bus *host)
{
	if (!otg)
		return -ENODEV;

	if (!otg->host)
		otg->host = host;

	return 0;
}

static void hisi_usb2phy_enable(struct hisi_usbphy *sphy)
{
	/*
	TO DO
	*/
	return;
}


static void hisi_usb2phy_disable(struct hisi_usbphy *sphy)
{
	/*
	TO DO
	*/
	return;
}

/*
 * The function passed to the usb driver for phy initialization
 */
static int hisi_usb2phy_init(struct usb_phy *phy)
{
	struct hisi_usbphy *sphy;

	sphy = phy_to_sphy(phy);

	/*
	TO DO. SUCH AS ENABLE CLK
	*/

	hisi_usb2phy_enable(sphy);

	return 0;
}

/*
 * The function passed to the usb driver for phy shutdown
 */
static void hisi_usb2phy_shutdown(struct usb_phy *phy)
{
	struct hisi_usbphy *sphy;

	sphy = phy_to_sphy(phy);

	/*
	TO DO. SUCH AS disable CLK
	*/

	hisi_usb2phy_disable(sphy);
	return;
}

static int hisi_usb2phy_probe(struct platform_device *pdev)
{
	struct hisi_usbphy *sphy;
	struct usb_otg *otg;
	struct hisi_usbphy_data *pdata = pdev->dev.platform_data;
	const struct hisi_usbphy_drvdata *drv_data;
	struct device *dev = &pdev->dev;
	struct resource *phy_mem;
	void __iomem	*phy_base;
	struct clk *clk = NULL;

	phy_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	phy_base = devm_ioremap_resource(dev, phy_mem);
	if (IS_ERR(phy_base))
		return PTR_ERR(phy_base);

	sphy = devm_kzalloc(dev, sizeof(*sphy), GFP_KERNEL);
	if (!sphy)
		return -ENOMEM;

	otg = devm_kzalloc(dev, sizeof(*otg), GFP_KERNEL);
	if (!otg)
		return -ENOMEM;

	drv_data = hisi_usbphy_get_driver_data(pdev);

	/*
	TO DO. GET PHY CLK, PARSE DTS......
	*/

	sphy->dev = dev;

	sphy->plat		= pdata;
	sphy->regs		= phy_base;
	sphy->clk		= clk;
	sphy->drv_data		= drv_data;
	sphy->phy.dev		= sphy->dev;
	sphy->phy.label		= "hisi-usb2phy";
	sphy->phy.init		= hisi_usb2phy_init;
	sphy->phy.shutdown	= hisi_usb2phy_shutdown;
	sphy->ref_clk_freq	= hisi_usbphy_get_refclk_freq(sphy);

	sphy->phy.otg		= otg;
	sphy->phy.otg->phy	= &sphy->phy;
	sphy->phy.otg->set_host = hisi_usbphy_set_host;

	spin_lock_init(&sphy->lock);

	platform_set_drvdata(pdev, sphy);

	return usb_add_phy(&sphy->phy, USB_PHY_TYPE_USB2);
}

static int hisi_usb2phy_remove(struct platform_device *pdev)
{
	struct hisi_usbphy *sphy = platform_get_drvdata(pdev);

	usb_remove_phy(&sphy->phy);

#if 0
	if (sphy->pmuregs)
		iounmap(sphy->pmuregs);
	if (sphy->sysreg)
		iounmap(sphy->sysreg);
#endif

	return 0;
}

static const struct hisi_usbphy_drvdata usb2phy = {
	.devphy_en_mask		= 0X0,
	.hostphy_en_mask = 0X0,
};

#ifdef CONFIG_OF
static const struct of_device_id hisi_usbphy_dt_match[] = {
	{
		.compatible = "hisilicon,hisi-usb2phy",
		.data = &usb2phy,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_usbphy_dt_match);
#endif

static struct platform_device_id hisi_usbphy_driver_ids[] = {
	{
		.name		= "hisi-usb2phy",
		.driver_data	= (unsigned long)&usb2phy,
	},
	{},
};

MODULE_DEVICE_TABLE(platform, hisi_usbphy_driver_ids);

static struct platform_driver hisi_usb2phy_driver = {
	.probe		= hisi_usb2phy_probe,
	.remove		= hisi_usb2phy_remove,
	.id_table	= hisi_usbphy_driver_ids,
	.driver		= {
		.name	= "hisi-usb2phy",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_usbphy_dt_match),
	},
};

module_platform_driver(hisi_usb2phy_driver);

MODULE_DESCRIPTION("hisi USB 2.0 phy controller");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hisi-usb2phy");
