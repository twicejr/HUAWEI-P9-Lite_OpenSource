/* linux/drivers/usb/phy/phy-hisi-usb3.c
 *
 *
 * Samsung USB 3.0 PHY transceiver; talks to DWC3 controller.
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
#include <linux/err.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/usb/hisi_usb_phy.h>
#include <linux/platform_data/hisi-usbphy.h>

#include "phy-hisi-usb.h"

static int hisi_usb3phy_init(struct usb_phy *phy)
{
	struct hisi_usbphy *sphy;
	unsigned long flags;
	int ret = 0;

	sphy = phy_to_sphy(phy);

	/*
	to do enable the clk.
	*/

	spin_lock_irqsave(&sphy->lock, flags);

	/* setting default phy-type for USB 3.0 */
	hisi_usbphy_set_type(&sphy->phy, USB_PHY_TYPE_DEVICE);

	/* Disable phy isolation */
	hisi_usbphy_set_isolation(sphy, false);

	spin_unlock_irqrestore(&sphy->lock, flags);
	/*
	to do disable the clk.
	*/
	return ret;
}

/*
 * The function passed to the usb driver for phy shutdown
 */
static void hisi_usb3phy_shutdown(struct usb_phy *phy)
{
	struct hisi_usbphy *sphy;
	unsigned long flags;

	sphy = phy_to_sphy(phy);

	/*
	to do enable the clk.
	*/

	spin_lock_irqsave(&sphy->lock, flags);

	/* setting default phy-type for USB 3.0 */
	hisi_usbphy_set_type(&sphy->phy, USB_PHY_TYPE_DEVICE);

	/* Enable phy isolation */
	hisi_usbphy_set_isolation(sphy, true);

	spin_unlock_irqrestore(&sphy->lock, flags);
	/*
	to do disable the clk.
	*/
}

static int hisi_usb3phy_probe(struct platform_device *pdev)
{
	struct hisi_usbphy *sphy;
	struct hisi_usbphy_data *pdata = pdev->dev.platform_data;
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

	/*
	TO DO. GET PHY CLK, PARSE DTS......
	*/

	sphy->dev = dev;

	sphy->plat		= pdata;
	sphy->regs		= phy_base;
	sphy->clk		= clk;
	sphy->phy.dev		= sphy->dev;
	sphy->phy.label		= "hisi-usb3phy";
	sphy->phy.init		= hisi_usb3phy_init;
	sphy->phy.shutdown	= hisi_usb3phy_shutdown;
	sphy->drv_data		= hisi_usbphy_get_driver_data(pdev);
	sphy->ref_clk_freq	= hisi_usbphy_get_refclk_freq(sphy);

	spin_lock_init(&sphy->lock);

	platform_set_drvdata(pdev, sphy);

	return usb_add_phy(&sphy->phy, USB_PHY_TYPE_USB3);
}

static int hisi_usb3phy_remove(struct platform_device *pdev)
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

static struct hisi_usbphy_drvdata usb3phy = {
	.devphy_en_mask		= 0x0,
};

#ifdef CONFIG_OF
static const struct of_device_id hisi_usbphy_dt_match[] = {
	{
		.compatible = "hisilicon,hisi-usb3phy",
		.data = &usb3phy
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_usbphy_dt_match);
#endif

static struct platform_device_id hisi_usbphy_driver_ids[] = {
	{
		.name		= "hisi-usb3phy",
		.driver_data	= (unsigned long)&usb3phy,
	},
	{},
};

MODULE_DEVICE_TABLE(platform, hisi_usbphy_driver_ids);

static struct platform_driver hisi_usb3phy_driver = {
	.probe		= hisi_usb3phy_probe,
	.remove		= hisi_usb3phy_remove,
	.id_table	= hisi_usbphy_driver_ids,
	.driver		= {
		.name	= "hisi-usb3phy",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_usbphy_dt_match),
	},
};

module_platform_driver(hisi_usb3phy_driver);

MODULE_DESCRIPTION("hisi USB 3.0 phy controller");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hisi-usb3phy");
