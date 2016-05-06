/* linux/drivers/usb/phy/phy-hisi-usb.c
 *
 *
 * Samsung USB-PHY helper driver with common function calls;
 * interacts with Samsung USB 2.0 PHY controller driver and later
 * with Samsung USB 3.0 PHY driver.
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
#include <linux/device.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/usb/hisi_usb_phy.h>

#include "phy-hisi-usb.h"

int hisi_usbphy_parse_dt(struct hisi_usbphy *sphy)
{
	struct device_node *usbphy_sys;

	/* Getting node for system controller interface for usb-phy */
	usbphy_sys = of_get_child_by_name(sphy->dev->of_node, "usbphy-sys");
	if (!usbphy_sys) {
		dev_err(sphy->dev, "No sys-controller interface for usb-phy\n");
		return -ENODEV;
	}

	sphy->pmuregs = of_iomap(usbphy_sys, 0);

	if (sphy->pmuregs == NULL) {
		dev_err(sphy->dev, "Can't get usb-phy pmu control register\n");
		goto err0;
	}

	sphy->sysreg = of_iomap(usbphy_sys, 1);

	/*
	 * Not returning error code here, since this situation is not fatal.
	 * Few SoCs may not have this switch available
	 */
	if (sphy->sysreg == NULL)
		dev_warn(sphy->dev, "Can't get usb-phy sysreg cfg register\n");

	of_node_put(usbphy_sys);

	return 0;

err0:
	of_node_put(usbphy_sys);
	return -ENXIO;
}
EXPORT_SYMBOL_GPL(hisi_usbphy_parse_dt);

/*
 * Set isolation here for phy.
 * Here 'on = true' would mean USB PHY block is isolated, hence
 * de-activated and vice-versa.
 */
void hisi_usbphy_set_isolation(struct hisi_usbphy *sphy, bool on)
{
	/*
	to do
	*/
	return;
}
EXPORT_SYMBOL_GPL(hisi_usbphy_set_isolation);

/*
 * Configure the mode of working of usb-phy here: HOST/DEVICE.
 */
void hisi_usbphy_cfg_sel(struct hisi_usbphy *sphy)
{
	/*
	to do.
	*/
	return;
}
EXPORT_SYMBOL_GPL(hisi_usbphy_cfg_sel);

/*
 * PHYs are different for USB Device and USB Host.
 * This make sure that correct PHY type is selected before
 * any operation on PHY.
 */
int hisi_usbphy_set_type(struct usb_phy *phy,
				enum hisi_usb_phy_type phy_type)
{
	/*
	to do
	*/
	return 0;
}
EXPORT_SYMBOL_GPL(hisi_usbphy_set_type);

/*
 * Returns reference clock frequency selection value
 */
int hisi_usbphy_get_refclk_freq(struct hisi_usbphy *sphy)
{
	/*
	to do.
	*/
	return 0;
}
EXPORT_SYMBOL_GPL(hisi_usbphy_get_refclk_freq);
