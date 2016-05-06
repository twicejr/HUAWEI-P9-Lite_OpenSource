/*
 * arch/arm/mach-tegra/include/mach/usb_phy.h
 *
 * Copyright (C) 2011 Hisi, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __MACH_USB_PHY_H
#define __MACH_USB_PHY_H

#include <linux/clk.h>
#include <linux/usb/otg.h>

/*select PHY*/
#define IS_HAVE_NANOPHY   0x1
#define IS_HAVE_HSICPHY   0x2
#define IS_HAVE_PICOPHY   0x4

/*sys ctrl*/
#define SCPEREN1         0x30
#define SCPERDIS1        0x34
#define SCPERCLKEN1    0x38
#define SCPERSTAT1      0x3C
/*--------------------------------*/
#define GT_CLK_USBHSICPHY480	1<<26
#define GT_CLK_USBHSICPHY	1<<25
#define GT_CLK_USBPICOPHY	1<<24
#define GT_CLK_USBNANOPHY	1<<23


#define SCPERRSTEN1                 0x8C
#define SCPERRSTDIS1                0x90
#define SCPERRSTSTAT1              0x94
/*--------------------------------*/
#define IP_RST_NANOPHY             1<<23
#define IP_RST_PICOPHY              1<<24
#define IP_RST_HSICPHY              1<<25

#define SCPERRSTEN3                  0xA4
#define SCPERRSTDIS3                 0xA8
#define SCPERRSTSTAT3              0xAC
/*--------------------------------*/
#define IP_PICOPHY_POR            1<<31
#define IP_HSICPHY_POR            1<<30
#define IP_NANOPHY_POR           1<<29
#define IP_RST_USB2DVC_PHY    1<<28
#define IP_RST_USB2H_UTMI1    1<<21
#define IP_RST_USB2H_UTMI0    1<<20
#define IP_RST_USB2H_PHY        1<<19
#define IP_RST_USB2HOST          1<<18
#define IP_RST_USB2DVC            1<<17

/*peri ctrl*/
#define PERI_CTRL1    0x04
#define USB2HST_FREE_SEL   1<<0

#define PERI_CTRL3  0xC
#define USB2H_HSIC_EN_PORT0   0x1
#define USB2H_HSIC_EN_PORT1   0x2
#define USB2H_HSIC_EN_MASK   0x3<<16



#define PERI_CTRL15   0x3C
#define HSICPHY_COMMON_N         1<<21
#define HSICPHY_SIDDQ   1<<16
#define NANOPHY_COMMON_N         1<<8
#define PICOPHY_COMMON_N         1<<9
#define	TXVREFTUNE_1			1<<5
#define	TXVREFTUNE_2			0x7<<2
#define HSICPHY_TXSRTUNE	(0x7 << 17)



#define PERI_CTRL14   0x38
#define NANOPHY_SIDDQ   1<<0
#define PICOPHY_SIDDQ   1<<0

#define PERI_CTRL21		0x1F4
#define	TXPREEMPAMPTUNE		0x3<<26

enum hisik3_usb_operating_modes {
	HISIK3_USB_DEVICE,
	HISIK3_USB_HOST,
	HISIK3_USB_OTG,
};

enum hisik3_usb_phy_type {
	HISIK3_USB_PHY_TYPE_UTMIP = 0,
	HISIK3_USB_PHY_TYPE_LINK_ULPI = 1,
	HISIK3_USB_PHY_TYPE_NULL_ULPI = 2,
	HISIK3_USB_PHY_TYPE_HSIC = 3,
	HISIK3_USB_PHY_TYPE_ICUSB = 4,
};

struct hisik3_ehci_platform_data {
	enum hisik3_usb_operating_modes operating_mode;
	/* power down the phy on bus suspend */
	int power_down_on_bus_suspend;
	void *phy_config;
	void (*post_suspend)(void);
	void (*pre_resume)(void);
};

struct hisik3_utmip_config {
	u8 hssync_start_delay;
	u8 elastic_limit;
	u8 idle_wait_delay;
	u8 term_range_adj;
	u8 xcvr_setup;
	u8 xcvr_lsfslew;
	u8 xcvr_lsrslew;
};

struct hisik3_ulpi_config {
	int reset_gpio;
	const char *clk;
};

struct hisik3_hsic_config {
	int enable_gpio;
	int reset_gpio;
	u8 sync_start_delay;
	u8 idle_wait_delay;
	u8 term_range_adj;
	u8 elastic_underrun_limit;
	u8 elastic_overrun_limit;
	int (*postsuspend)(void);
	int (*preresume)(void);
};

enum hisik3_usb_phy_port_speed {
	HISIK3_USB_PHY_PORT_SPEED_FULL = 0,
	HISIK3_USB_PHY_PORT_SPEED_LOW,
	HISIK3_USB_PHY_PORT_SPEED_HIGH,
};

enum hisik3_usb_phy_mode {
	HISIK3_USB_PHY_MODE_DEVICE,
	HISIK3_USB_PHY_MODE_HOST,
};

struct tegra_xtal_freq;

struct hisik3_usb_phy {
	int instance;
	const struct hisik3_xtal_freq *freq;
	void __iomem *regs;
	void __iomem *pad_regs;
	struct clk *nano_phy_clk;
	struct clk *hsic_phy_clk;
	struct clk *hsic_phy_clk_480;
	enum hisik3_usb_phy_mode mode;
	void *config;
	struct otg_transceiver *ulpi;
};

struct hisik3_ehci_hcd {
	struct ehci_hcd *ehci;
	struct usb_hcd *hcd;
	struct hisik3_usb_phy *phy;
	struct hisik3_ehci_platform_data *pdata;
	int irq;
	int instance;	
	struct clk *core_clk;
	struct otg_transceiver *transceiver;
	int host_resumed;
	int bus_suspended;
	int port_resuming;
	int power_down_on_bus_suspend;
	int ehci_init;
	int clock_state;
	enum hisik3_usb_phy_port_speed port_speed;
};

struct hisik3_usb_phy *hisik3_usb_phy_open(int instance, void __iomem *regs,
			void *config, enum hisik3_usb_phy_mode phy_mode);

void hisik3_usb_phy_power_on(struct hisik3_ehci_hcd *hiusb_ehci);

void hisik3_usb_phy_clk_disable(struct hisik3_usb_phy *phy);

void hisik3_usb_phy_clk_enable(struct hisik3_usb_phy *phy);

void hisik3_usb_phy_power_off(struct hisik3_ehci_hcd *hiusb_ehci);

void hisik3_usb_phy_preresume(struct hisik3_usb_phy *phy);

void hisik3_usb_phy_postresume(struct hisik3_usb_phy *phy);

void hisik3_ehci_phy_restore_start(struct hisik3_usb_phy *phy,
				 enum hisik3_usb_phy_port_speed port_speed);

void hisik3_ehci_phy_restore_end(struct hisik3_usb_phy *phy);

void hisik3_usb_phy_close(struct hisik3_usb_phy *phy);

#endif /* __MACH_USB_PHY_H */
