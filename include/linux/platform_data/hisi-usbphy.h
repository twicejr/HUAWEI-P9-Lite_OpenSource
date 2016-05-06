/*
 *
 * Defines platform data for hisi usb phy driver.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#ifndef __HISI_USBPHY_PLATFORM_H
#define __HISI_USBPHY_PLATFORM_H

/**
 * hisi_usbphy_data - Platform data for USB PHY driver.
 * @pmu_isolation: Function to control usb phy isolation in PMU.
 */
struct hisi_usbphy_data {
	void (*pmu_isolation)(int on);
};

extern void hisi_usbphy_set_pdata(struct hisi_usbphy_data *pd);

#endif /* __HISI_USBPHY_PLATFORM_H */
