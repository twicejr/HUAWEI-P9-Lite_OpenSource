/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/clk.h>
#include <linux/delay.h>

#define HI64XX_CFG_BASE_ADDR            0x20007000

#define HI64XX_PAGE_SELECT_MASK_SSI     (0xFF)
#define HI64XX_REG32_OFFSET_MASK_SSI    (0xFC)
#define HI64XX_REG_VAL_BIT              (8)
#define HI64XX_REG_VAL_MASK             (0xFF)

#define HI64XX_PAGE_SELECT_REG_0_SSI    (0x1FD)
#define HI64XX_PAGE_SELECT_REG_1_SSI    (0x1FE)
#define HI64XX_PAGE_SELECT_REG_2_SSI    (0x1FF)

#define HI64XX_RAM2AXI_RD_DATA0         (HI64XX_CFG_BASE_ADDR + 0x23)
#define HI64XX_RAM2AXI_RD_DATA1         (HI64XX_CFG_BASE_ADDR + 0x24)
#define HI64XX_RAM2AXI_RD_DATA2         (HI64XX_CFG_BASE_ADDR + 0x25)
#define HI64XX_RAM2AXI_RD_DATA3         (HI64XX_CFG_BASE_ADDR + 0x26)

struct hi_cdcssi_priv {
	struct clk *codec_ssi_clk;
	struct clk *pmu_audio_clk;
	struct pinctrl *pctrl;
	struct pinctrl_state *pin_default;
	struct pinctrl_state *pin_idle;
	unsigned int ssi_page_sel;
	void __iomem *ssi_base;
};

static struct hi_cdcssi_priv *pdata;

void _ssi_select_reg_page(unsigned int reg)
{
	unsigned int reg_page = reg & (~HI64XX_PAGE_SELECT_MASK_SSI);

	if(pdata->ssi_page_sel == reg_page) {
		return;
	} else {
		pdata->ssi_page_sel = reg_page;
	}

	reg_page = reg_page >> HI64XX_REG_VAL_BIT;
	writel(reg_page & HI64XX_REG_VAL_MASK,  pdata->ssi_base + (HI64XX_PAGE_SELECT_REG_0_SSI << 2));

	reg_page = reg_page >> HI64XX_REG_VAL_BIT;
	writel(reg_page & HI64XX_REG_VAL_MASK,  pdata->ssi_base + (HI64XX_PAGE_SELECT_REG_1_SSI << 2));

	reg_page = reg_page >> HI64XX_REG_VAL_BIT;
	writel(reg_page & HI64XX_REG_VAL_MASK,  pdata->ssi_base + (HI64XX_PAGE_SELECT_REG_2_SSI << 2));
}

unsigned int ssi_reg_read8(unsigned int reg)
{
	int val = 0x5a;

	_ssi_select_reg_page(reg);
	readl((void*)pdata->ssi_base + ((reg & (HI64XX_REG_VAL_MASK)) << 2));
	val = readl((void*)pdata->ssi_base + ((reg & (HI64XX_REG_VAL_MASK)) << 2));

	return val;
}
EXPORT_SYMBOL(ssi_reg_read8);

unsigned int ssi_reg_read32(unsigned int reg)
{
	unsigned int ret = 0;

	_ssi_select_reg_page(reg );
	readl((void*)pdata->ssi_base + ((reg & (HI64XX_REG32_OFFSET_MASK_SSI)) << 2));
	ret = readl((void*)pdata->ssi_base + ((reg & (HI64XX_REG32_OFFSET_MASK_SSI)) << 2));

	_ssi_select_reg_page(HI64XX_RAM2AXI_RD_DATA0 );
	readl((void*)pdata->ssi_base + (((HI64XX_RAM2AXI_RD_DATA3 ) & (HI64XX_REG_VAL_MASK)) << 2));
	ret = readl((void*)pdata->ssi_base + (((HI64XX_RAM2AXI_RD_DATA3 ) & (HI64XX_REG_VAL_MASK)) << 2));
	readl((void*)pdata->ssi_base + (((HI64XX_RAM2AXI_RD_DATA2) & (HI64XX_REG_VAL_MASK)) << 2));
	ret = (ret<<8) + (0xFF & readl((void*)pdata->ssi_base + (((HI64XX_RAM2AXI_RD_DATA2) & (HI64XX_REG_VAL_MASK)) << 2)));
	readl((void*)pdata->ssi_base + (((HI64XX_RAM2AXI_RD_DATA1) & (HI64XX_REG_VAL_MASK)) << 2));
	ret = (ret<<8) + (0xFF & readl((void*)pdata->ssi_base + (((HI64XX_RAM2AXI_RD_DATA1) & (HI64XX_REG_VAL_MASK)) << 2)));
	readl((void*)pdata->ssi_base + (((HI64XX_RAM2AXI_RD_DATA0) & (HI64XX_REG_VAL_MASK)) << 2));
	ret = (ret<<8) + (0xFF & readl((void*)pdata->ssi_base + (((HI64XX_RAM2AXI_RD_DATA0) & (HI64XX_REG_VAL_MASK)) << 2)));

	return ret ;
}
EXPORT_SYMBOL(ssi_reg_read32);

void ssi_reg_write8(unsigned int reg, unsigned int val)
{
	_ssi_select_reg_page(reg);

	writel(val & HI64XX_REG_VAL_MASK , (void*)pdata->ssi_base + ((reg & HI64XX_REG_VAL_MASK) << 2));
}
EXPORT_SYMBOL(ssi_reg_write8);

void ssi_reg_write32(unsigned int reg, unsigned int val)
{
	if (reg & 0x3) {
		pr_err("%s:reg is 0x%x, it's not alignment!!\n", __FUNCTION__, reg);
		return;
	}

	_ssi_select_reg_page(reg);

	writel(val & HI64XX_REG_VAL_MASK, (void*)pdata->ssi_base + ((reg & HI64XX_REG_VAL_MASK) << 2));
	writel((val>>8) & HI64XX_REG_VAL_MASK, (void*)pdata->ssi_base + (((reg+1) & HI64XX_REG_VAL_MASK) << 2));
	writel((val>>16) & HI64XX_REG_VAL_MASK, (void*)pdata->ssi_base + (((reg+2) & HI64XX_REG_VAL_MASK) << 2));
	writel((val>>24) & HI64XX_REG_VAL_MASK, (void*)pdata->ssi_base + (((reg+3) & HI64XX_REG_VAL_MASK) << 2));
}
EXPORT_SYMBOL(ssi_reg_write32);

static int hi_cdcssi_probe(struct platform_device *pdev)
{
	struct hi_cdcssi_priv *priv;
	struct device *dev = &pdev->dev;
	struct resource *resource;
	int ret = 0;

	priv = devm_kzalloc(dev, sizeof(struct hi_cdcssi_priv), GFP_KERNEL);
	if (!priv) {
		dev_err(dev, "devm_kzalloc failed\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, priv);
	pdata = priv;

	priv->ssi_page_sel = 1;

	/* get codec ssi clk */
	priv->codec_ssi_clk = devm_clk_get(dev, "clk_codecssi");
	if (IS_ERR(priv->codec_ssi_clk)) {
		dev_err(dev, "clk_get: codecssi clk not found!\n");
		ret = PTR_ERR(priv->codec_ssi_clk);
		goto exit;
	}

	ret = clk_prepare_enable(priv->codec_ssi_clk);
	if (0 != ret) {
		dev_err(dev, "codec_ssi_clk :clk prepare enable failed !\n");
		goto exit;
	}
	mdelay(1);

	/* get pinctrl */
	priv->pctrl = devm_pinctrl_get(dev);
	if (IS_ERR(priv->pctrl)) {
		dev_err(dev, "could not get pinctrl\n");
		ret = -EIO;
		goto exit;
	}

	priv->pin_default = pinctrl_lookup_state(priv->pctrl, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(priv->pin_default)) {
		dev_err(dev, "could not get default state (%li)\n" , PTR_ERR(priv->pin_default));
		ret = -EIO;
		goto exit;
	}

	priv->pin_idle = pinctrl_lookup_state(priv->pctrl, PINCTRL_STATE_IDLE);
	if (IS_ERR(priv->pin_idle)) {
		dev_err(dev, "could not get idle state (%li)\n", PTR_ERR(priv->pin_idle));
		ret = -EIO;
		goto exit;
	}

	if (pinctrl_select_state(priv->pctrl, priv->pin_default)) {
		dev_err(dev, "could not set pins to default state\n");
		ret = -EIO;
		goto exit;
	}

	resource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!resource) {
		dev_err(dev, "get IORESOURCE_MEM failed\n");
		ret = -ENXIO;
		goto exit;
	}

	priv->ssi_base = ioremap(resource->start, resource_size(resource));
	if (!priv->ssi_base) {
		dev_err(dev, "remap base address %p failed\n", (void*)resource->start);
		ret = -ENXIO;
		goto exit;
	}

	return 0;

exit:
	return ret;
}

static int hi_cdcssi_remove(struct platform_device *pdev)
{
	struct hi_cdcssi_priv *priv = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;
	int ret = 0;

	iounmap(priv->ssi_base);
	pinctrl_put(priv->pctrl);
	clk_disable_unprepare(priv->codec_ssi_clk);
	devm_kfree(dev, priv);

	return ret;
}

static int hi_cdcssi_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct hi_cdcssi_priv *priv = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;
	int ret = 0;

	ret = pinctrl_select_state(priv->pctrl, priv->pin_idle);
	if (ret) {
		dev_err(dev, "could not set pins to idle state\n");
	}

	clk_disable_unprepare(priv->codec_ssi_clk);

	return ret;
}

static int hi_cdcssi_resume(struct platform_device *pdev)
{
	struct hi_cdcssi_priv *priv = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;
	int ret = 0;

	ret = clk_prepare_enable(priv->codec_ssi_clk);
	if (0 != ret) {
		dev_err(dev, "codec_ssi_clk :clk prepare enable failed !\n");
	}

	ret = pinctrl_select_state(priv->pctrl, priv->pin_default);
	if (ret) {
		dev_err(dev, "could not set pins to default state\n");
	}

	return ret;
}

static const struct of_device_id codecssi_match[] = {
	{
		.compatible = "hisilicon,codecssi",
	},
	{},
};
MODULE_DEVICE_TABLE(of, slimbus_match);

static struct platform_driver codecssi_driver = {
	.probe	= hi_cdcssi_probe,
	.remove = hi_cdcssi_remove,
	.suspend = hi_cdcssi_suspend,
	.resume  = hi_cdcssi_resume,
	.driver = {
		.name	= "hisilicon,codecssi",
		.owner	= THIS_MODULE,
		.of_match_table = codecssi_match,
	},
};

static int __init hi_cdcssi_init(void)
{
	int ret;

	ret = platform_driver_register(&codecssi_driver);
	if (ret) {
		pr_err("driver register failed\n");
	}

	return ret;
}

static void __exit hi_cdcssi_exit(void)
{
	platform_driver_unregister(&codecssi_driver);
}
fs_initcall_sync(hi_cdcssi_init);
module_exit(hi_cdcssi_exit);

MODULE_DESCRIPTION("hisi codecssi controller");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon");
