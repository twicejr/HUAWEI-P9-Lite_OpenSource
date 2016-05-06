/* linux/drivers/usb/phy/phy-hisi-usb.h
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

#include <linux/usb/phy.h>

/* Register definitions */

#ifndef MHZ
#define MHZ (1000*1000)
#endif

#ifndef KHZ
#define KHZ (1000)
#endif

/*
 * struct hisi_usbphy_drvdata - driver data for various SoC variants
 * @cpu_type: machine identifier
 * @devphy_en_mask: device phy enable mask for PHY CONTROL register
 * @hostphy_en_mask: host phy enable mask for PHY CONTROL register
 * @devphy_reg_offset: offset to DEVICE PHY CONTROL register from
 *		       mapped address of system controller.
 * @hostphy_reg_offset: offset to HOST PHY CONTROL register from
 *		       mapped address of system controller.
 *
 *	Here we have a separate mask for device type phy.
 *	Having different masks for host and device type phy helps
 *	in setting independent masks in case of SoCs like S5PV210,
 *	in which PHY0 and PHY1 enable bits belong to same register
 *	placed at position 0 and 1 respectively.
 *	Although for newer SoCs like exynos these bits belong to
 *	different registers altogether placed at position 0.
 */
struct hisi_usbphy_drvdata {
	int cpu_type;
	int devphy_en_mask;
	int hostphy_en_mask;
	u32 devphy_reg_offset;
	u32 hostphy_reg_offset;
};

/*
 * struct hisi_usbphy - transceiver driver state
 * @phy: transceiver structure
 * @plat: platform data
 * @dev: The parent device supplied to the probe function
 * @clk: usb phy clock
 * @regs: usb phy controller registers memory base
 * @pmuregs: USB device PHY_CONTROL register memory base
 * @sysreg: USB2.0 PHY_CFG register memory base
 * @ref_clk_freq: reference clock frequency selection
 * @drv_data: driver data available for different SoCs
 * @phy_type: Samsung SoCs specific phy types:	#HOST
 *						#DEVICE
 * @phy_usage: usage count for phy
 * @lock: lock for phy operations
 */
struct hisi_usbphy {
	struct usb_phy	phy;
	struct hisi_usbphy_data *plat;
	struct device	*dev;
	struct clk	*clk;
	void __iomem	*regs;
	void __iomem	*pmuregs;
	void __iomem	*sysreg;
	int		ref_clk_freq;
	const struct hisi_usbphy_drvdata *drv_data;
	enum hisi_usb_phy_type phy_type;
	atomic_t	phy_usage;
	spinlock_t	lock;
};

#define phy_to_sphy(x)		container_of((x), struct hisi_usbphy, phy)

static const struct of_device_id hisi_usbphy_dt_match[];

static inline const struct hisi_usbphy_drvdata
*hisi_usbphy_get_driver_data(struct platform_device *pdev)
{
	if (pdev->dev.of_node) {
		const struct of_device_id *match;
		match = of_match_node(hisi_usbphy_dt_match,
							pdev->dev.of_node);
		return match ? match->data : NULL;
	}

	return (struct hisi_usbphy_drvdata *)
				platform_get_device_id(pdev)->driver_data;
}

extern int hisi_usbphy_parse_dt(struct hisi_usbphy *sphy);
extern void hisi_usbphy_set_isolation(struct hisi_usbphy *sphy, bool on);
extern void hisi_usbphy_cfg_sel(struct hisi_usbphy *sphy);
extern int hisi_usbphy_set_type(struct usb_phy *phy,
					enum hisi_usb_phy_type phy_type);
extern int hisi_usbphy_get_refclk_freq(struct hisi_usbphy *sphy);
