#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/delay.h>

#include "dwc_otg_hi6250.h"

#include <linux/gpio.h>

int hi6250_enable_abb_clk(struct otg_dev *otg_device)
{
	void __iomem *pctrl_base = otg_device->pctrl_reg_base;
	uint32_t temp = 0;
	int ret = 0;

	/* config and switch on abb clk */
	temp = readl(pctrl_base + PCTRL_PERI_CTRL24);
	temp &= ~(7 << 24);
	temp |= (5 << 24);
	writel(temp, pctrl_base + PCTRL_PERI_CTRL24);

	/* enable abb clk */
	ret = clk_prepare_enable(otg_device->clk);
	if (ret) {
		usb_err("[USB2.0]:clk_prepare_enable failed:%d\n", ret);
		return ret;
	}

	return 0;
}

void hi6250_disable_abb_clk(struct otg_dev *otg_device)
{
	void __iomem *pctrl_base = otg_device->pctrl_reg_base;
	uint32_t temp = 0;;

	/* config and switch off abb clk */
	temp = readl(pctrl_base + PCTRL_PERI_CTRL24);
	temp &= ~(1 << 24);
	writel(temp, pctrl_base + PCTRL_PERI_CTRL24);


	/* disable abb clk */
	clk_disable_unprepare(otg_device->clk);
}

void init_usb_otg_phy_hi6250(struct otg_dev *otg_device, int is_host_mode)
{
	void __iomem *pericrg_base = otg_device->pericrg_base;
	struct usb_ahbif_registers *ahbif = (struct usb_ahbif_registers *)otg_device->usb_ahbif_base;
	union usbotg2_ctrl0 ctrl0;
	union usbotg2_ctrl2 ctrl2;

	if (otg_device->fpga_usb_mode_gpio > 0) {
		/* set gpio_21[2] = is_host_mode, 0:device mode, 1:host mode */
		gpio_direction_output(otg_device->fpga_usb_mode_gpio, is_host_mode);
	}

	writel(BIT_HCLK_USB2OTG, pericrg_base + PERI_CRG_CLK_EN4);

	/* unreset usb ahbif */
	writel(BIT_RST_USB2OTG_ADP | BIT_RST_USB2OTG_32K |
		   BIT_RST_USB2OTG_MUX |
		   BIT_RST_USB2OTG_AHBIF,
		   pericrg_base + PERI_CRG_RSTDIS4);

	ctrl0.reg = readl(&ahbif->usbotg2_ctrl0);
#ifndef FORCE_ID_STATE
	ctrl0.bits.id_sel = 1; /* 1: from phy iddig, 2: from phy aca*/
#else
	ctrl0.bits.id_sel = 0; /* 1: from phy iddig, 2: from phy aca*/
	if (is_host_mode) {
		ctrl0.bits.id = 0;
	} else {
		ctrl0.bits.id = 1;
	}
#endif

	ctrl0.bits.acaenb_sel = 1;
	ctrl0.bits.acaenb = 0;
	writel(ctrl0.reg, &ahbif->usbotg2_ctrl0);

	/* set eye pattern parameter */
	writel(otg_device->eyePattern, &ahbif->usbotg2_ctrl3);

	/* unreset phy */
	writel(BIT_RST_USB2OTGPHYPOR, pericrg_base + PERI_CRG_RSTDIS4);

	/* dealy 50us */
	udelay(50);

	/* unreset phy clk domain */
	writel(BIT_RST_USB2OTGPHY, pericrg_base + PERI_CRG_RSTDIS4);

	/* dealy 100us */
	udelay(100);

	/* unreset hclk domain */
	writel(BIT_RST_USB2OTG, pericrg_base + PERI_CRG_RSTDIS4);

	/* enable vbusvalidext & vbusvldextsel */
	ctrl2.reg = readl(&ahbif->usbotg2_ctrl2);
	ctrl2.bits.vbusvldsel = 1;
	ctrl2.bits.vbusvldext = 1;
	writel(ctrl2.reg, &ahbif->usbotg2_ctrl2);

	msleep(1);
}

void close_usb_otg_phy_hi6250(struct otg_dev *otg_device)
{
	void __iomem *pericrg_base = otg_device->pericrg_base;

	/* reset controller */
	writel(BIT_RST_USB2OTG, pericrg_base + PERI_CRG_RSTEN4);
	udelay(1);

	/* reset phy */
	writel(BIT_RST_USB2OTGPHY, pericrg_base + PERI_CRG_RSTEN4);

	writel(BIT_RST_USB2OTGPHYPOR, pericrg_base + PERI_CRG_RSTEN4);

	/* reset usb ahbif */
	writel(BIT_RST_USB2OTG_ADP | BIT_RST_USB2OTG_32K | BIT_RST_USB2OTG_MUX |
		   BIT_RST_USB2OTG_AHBIF, pericrg_base + PERI_CRG_RSTEN4);

	writel(BIT_HCLK_USB2OTG, pericrg_base + PERI_CRG_CLK_DIS4);

	msleep(1);
}

struct usb_phy_ops hi6250_usb_phy_ops = {
	.init = init_usb_otg_phy_hi6250,
	.close = close_usb_otg_phy_hi6250,
	.enable_clk = hi6250_enable_abb_clk,
	.disable_clk = hi6250_disable_abb_clk
};

static int dwc_otg_hi6250_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct otg_dev *dev_p = NULL;

	dev_p = devm_kzalloc(&pdev->dev, sizeof(*dev_p), GFP_KERNEL);
	if (!dev_p) {
		usb_err("alloc otg_dev failed! not enough memory\n");
		return -ENOMEM;
	}
	dev_p->pdev = pdev;

	register_usb_phy_ops(dev_p, &hi6250_usb_phy_ops);

	ret = dwc_otg_hicommon_probe(dev_p); /* usb common interface */

	return ret;
}

static int dwc_otg_hi6250_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct otg_dev *dev_p = platform_get_drvdata(pdev);
	if (!dev_p) {
		return 0;
	}

	ret = dwc_otg_hicommon_remove(dev_p);  /* usb common interface*/
	return ret;
}

#ifdef CONFIG_OF
static const struct of_device_id dwc_otg_hi6250_mach[] = {
	{ .compatible = "hisilicon,hi6250-usb-otg" },
	{},
};
MODULE_DEVICE_TABLE(of, dwc_otg_hi6250_mach);
#else
#define dwc_otg_hi6250_mach NULL
#endif

static struct platform_driver dwc_otg_hi6250_driver = {
	.probe		= dwc_otg_hi6250_probe,
	.remove		= dwc_otg_hi6250_remove,
	.driver		= {
		.name	= "hi6250_otg",
		.of_match_table = of_match_ptr(dwc_otg_hi6250_mach),
		.pm = dwc_otg_dev_pm_ops_p,
	},
};

module_platform_driver(dwc_otg_hi6250_driver);

MODULE_AUTHOR("z00289564");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("DesignWare OTG2.0 hi6250 Glue Layer");
