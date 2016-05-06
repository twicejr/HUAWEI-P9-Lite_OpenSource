/*
 * PCIe host controller driver for Kirin 960 SoCs
 *
 * Copyright (C) 2015 Huawei Electronics Co., Ltd.
 *		http://www.huawei.com
 *
 * Author: Xiaowei Song <songxiaowei@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include "pcie-kirin.h"


/*crgperi ctrl registers*/

#define ISO_ENABLE		   0x1
#define ISO_DISABLE        0x0
#define ISO_CTRL_BIT       0x30
#define BUSIDLE_CLEAR_BIT  0x40000
#define BUSIDLE_SET_BIT    0x40004
#define BUSIDLE_CLEAR_FLAG 0x0
#define BUSIDLE_SET_FLAG   0x1
#define MTCMOS_ON          0x1
#define MTCMOS_OFF         0x0
#define MTCMOS_CTRL_BIT    0x10
#define CLK_ON             0x1
#define CLK_OFF            0x0


#define RESET_ENABLE_FLAG  0x1
#define RESET_DISABLE_FLAG	0x0
#define RESET_CTRL_PHY_BIT	   0x88000000
#define RESET_CTRL_CTRL_BIT 	0x84000000
#define RESET_CTRL_BIT	   (RESET_CTRL_PHY_BIT | RESET_CTRL_CTRL_BIT)

/* PCIe ELBI registers */
#define SOC_PCIECTRL_CTRL0_ADDR 0x000
#define SOC_PCIECTRL_CTRL1_ADDR 0x004
#define PCIE_ELBI_SLV_DBI_ENABLE	(0x1 << 21)
#define SOC_PCIECTRL_CTRL6_ADDR 0x018

#define PCIE_IRQ_PULSE			0x000
#define PCIE_LINK_RETRAIN		(0x1 < 3)

#define PCIE_APP_LTSSM_ENABLE		0x01c
#define PCIE_ELBI_RDLH_LINKUP		0x410
#define PCIE_ELBI_LTSSM_ENABLE		0x11
#define PCIE_LTSSM_ENABLE_BIT	  (0x1<<11)


/* PCIe DBI registers */



#define PCIE_VENDOR_ID_RCP (0x19E5)
#define PCIE_DEVICE_ID_RCP (0x3660)

struct pci_saved_state		 *rc_saved_state = NULL;
struct kirin_pcie *g_rc_pcie = NULL;
struct pci_bus *g_root_bus = NULL;

static void kirin_pcie_clear_irq_pulse(struct pcie_port *pp);
static inline void kirin_elb_writel(struct kirin_pcie *pcie, u32 val, u32 reg)
{
	writel(val, pcie->apb_base + reg);
}

static inline u32 kirin_elb_readl(struct kirin_pcie *pcie, u32 reg)
{
	return readl(pcie->apb_base + reg);
}

/*Registers in PCIePHY*/
static inline void kirin_phy_writel(struct kirin_pcie *pcie, u32 val, u32 reg)
{
	writel(val, pcie->phy_base + reg);
}

static inline u32 kirin_phy_readl(struct kirin_pcie *pcie, u32 reg)
{
	return readl(pcie->phy_base + reg);
}

static void kirin_pcie_busidle_ctrl(struct kirin_pcie *pcie, bool set)
{
	if (set)
		writel(BUSIDLE_SET_BIT, pcie->pmctrl_base + 0x380);
	else
		writel(BUSIDLE_CLEAR_BIT, pcie->pmctrl_base + 0x380);
}

static void kirin_pcie_iso_ctrl(struct kirin_pcie *pcie, bool en_flag)
{
	if (en_flag)
		writel(ISO_CTRL_BIT, pcie->sctrl_base + 0x40);
	else
		writel(ISO_CTRL_BIT, pcie->sctrl_base + 0x44);
}
static void kirin_pcie_mtcmos_ctrl(struct kirin_pcie *pcie, bool enable)
{
	if (enable)
		writel(MTCMOS_CTRL_BIT, pcie->sctrl_base + 0x60);
	else
		writel(MTCMOS_CTRL_BIT, pcie->sctrl_base + 0x64);
}

static void kirin_pcie_reset_ctrl(struct kirin_pcie *pcie, int reset_enable)
{
	unsigned int ret = 0;

	if (reset_enable == RESET_ENABLE_FLAG)
		writel(RESET_CTRL_BIT, pcie->crg_base + 0x84);
	else
		writel(RESET_CTRL_BIT, pcie->crg_base + 0x88);

	ret = readl(pcie->crg_base + 0x8c);
	PCIE_PR_INFO("Reset status register is [0x%x]", ret);
}


static void kirin_pcie_clk_ctrl(struct kirin_pcie *pcie, bool clk_on)
{
	int ret = 0;
	unsigned long ref_clk = 100000000;
	if (clk_on) {
		/*set_rate sctrl val[0x268] = 0x8000800*/
		/*prepare_enable sctrl 0x190 ----- CIO_clk and phy_clk 100MHz*/
		/*prepare_eable crg_peri 0x420 Bit[5 7 8 9]*/
		/*most clk node not exist in clk.dtsi, so here write register directly*/
		ret = clk_set_rate(pcie->phy_ref_clk, ref_clk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to set ref clk rate 100MHz ");
			return;
		}
		PCIE_PR_ERR("register[0x268]=[0x%x] ", readl(pcie->sctrl_base + 0x268));

		ret = clk_prepare_enable(pcie->phy_ref_clk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable aux_clk ");
			return;
		}

		ret = clk_prepare_enable(pcie->io_clk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable io_clk ");
			clk_disable_unprepare(pcie->phy_ref_clk);
			return;
		}

		ret = clk_prepare_enable(pcie->apb_sys_clk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable apb_sys_clk ");
			clk_disable_unprepare(pcie->phy_ref_clk);
			clk_disable_unprepare(pcie->io_clk);
			return;
		}

		ret = clk_prepare_enable(pcie->apb_phy_clk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable apb_phy_clk ");
			clk_disable_unprepare(pcie->phy_ref_clk);
			clk_disable_unprepare(pcie->io_clk);
			clk_disable_unprepare(pcie->apb_sys_clk);
			return;
		}
		ret = clk_prepare_enable(pcie->pcie_aclk);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to enable phy_ref_clk ");
			clk_disable_unprepare(pcie->phy_ref_clk);
			clk_disable_unprepare(pcie->io_clk);
			clk_disable_unprepare(pcie->apb_sys_clk);
			clk_disable_unprepare(pcie->pcie_aclk);
			return;
		} 
	} else {
		/*disable sctrl 0x194 ----- CIO_clk and phy_clk 100MHz*/
		/*disable crg_peri 0x424 Bit[5 7 8 9]*/
		/*set_rate sctrl val[0x268] = 0x8000000*/

		clk_disable_unprepare(pcie->phy_ref_clk);
		clk_disable_unprepare(pcie->io_clk);
		clk_disable_unprepare(pcie->apb_sys_clk);
		clk_disable_unprepare(pcie->apb_phy_clk);
		clk_disable_unprepare(pcie->pcie_aclk);

		ret = clk_set_rate(pcie->phy_ref_clk, ref_clk*16);
		if (0 != ret) {
			PCIE_PR_ERR("Failed to set ref clk rate 1.6 GHz ");
			return;
		}
	}
}

static int32_t kirin_pcie_get_clk(struct kirin_pcie *pcie, struct platform_device *pdev)
{
	pcie->io_clk = devm_clk_get(&pdev->dev, "pcie_io");
	if (IS_ERR(pcie->io_clk)) {
		PCIE_PR_ERR("Failed to get ctrl_apb_clk clock");
		return PTR_ERR(pcie->io_clk);
	}

	pcie->phy_ref_clk = devm_clk_get(&pdev->dev, "pcie_phy_ref");
	if (IS_ERR(pcie->phy_ref_clk)) {
		PCIE_PR_ERR("Failed to get ctrl_axi_clk clock");
		return PTR_ERR(pcie->phy_ref_clk);
	}

	pcie->apb_phy_clk = devm_clk_get(&pdev->dev, "pcie_apb_phy");
	if (IS_ERR(pcie->apb_phy_clk)) {
		PCIE_PR_ERR("Failed to get ctrl_aux_clk clock");
		return PTR_ERR(pcie->apb_phy_clk);
	}

	pcie->apb_sys_clk = devm_clk_get(&pdev->dev, "pcie_apb_sys");
	if (IS_ERR(pcie->apb_sys_clk)) {
		PCIE_PR_ERR("Failed to get cio_in_clk clock");
		return PTR_ERR(pcie->apb_sys_clk);
	}

	pcie->pcie_aclk = devm_clk_get(&pdev->dev, "pcie_aclk");
	if (IS_ERR(pcie->pcie_aclk)) {
		PCIE_PR_ERR("Failed to get phy_apb_clk clock");
		return PTR_ERR(pcie->pcie_aclk);
	}

	PCIE_PR_INFO("Successed to get all clock");

	return 0;
}


static int32_t kirin_pcie_get_resource(struct pcie_port *pp, struct platform_device *pdev)
{
	struct resource *apb;
	struct resource *phy;
	struct resource *dbi;
	struct resource *crg;
	struct resource *sctrl;
	struct resource *pmctrl;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	apb = platform_get_resource_byname(pdev, IORESOURCE_MEM, "apb");
	pcie->apb_base = devm_ioremap_resource(&pdev->dev, apb);
	if (IS_ERR(pcie->apb_base)) {
		PCIE_PR_ERR("cannot get apb base");
		return PTR_ERR(pcie->apb_base);
	}

	phy = platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy");
	pcie->phy_base = devm_ioremap_resource(&pdev->dev, phy);
	if (IS_ERR(pcie->phy_base)) {
		PCIE_PR_ERR("cannot get PCIePHY base");
		return PTR_ERR(pcie->phy_base);
	}

	dbi = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	pp->dbi_base = devm_ioremap_resource(&pdev->dev, dbi);
	if (IS_ERR(pp->dbi_base)) {
		PCIE_PR_ERR("cannot get PCIe dbi base");
		return PTR_ERR(pp->dbi_base);
	}

	crg = platform_get_resource_byname(pdev, IORESOURCE_MEM, "crg");
	pcie->crg_base = devm_ioremap_resource(&pdev->dev, crg);
	if (IS_ERR(pcie->crg_base)) {
		PCIE_PR_ERR("cannot get crgperi base");
		return PTR_ERR(pcie->crg_base);
	}

	sctrl = platform_get_resource_byname(pdev, IORESOURCE_MEM, "sctrl");
	pcie->sctrl_base = devm_ioremap_resource(&pdev->dev, sctrl);
	if (IS_ERR(pcie->sctrl_base)) {
		PCIE_PR_ERR("cannot get sctrl base");
		return PTR_ERR(pcie->sctrl_base);
	}

	pmctrl = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pmctrl");
	pcie->pmctrl_base = devm_ioremap_resource(&pdev->dev, pmctrl);
	if (IS_ERR(pcie->pmctrl_base)) {
		PCIE_PR_ERR("cannot get pmctrl base");
		return PTR_ERR(pcie->pmctrl_base);
	}

	PCIE_PR_INFO("Successed to get all resource");
	return 0;
}

static int32_t kirin_pcie_get_boardtype(struct kirin_pcie *pcie, struct platform_device *pdev)
{
	int len = 0;
	struct property *prop = of_find_property(pdev->dev.of_node, "fpga_flag", &len);
	if (!prop) {
		pcie->fpga_flag = 0;
		PCIE_PR_INFO("ASIC Platform");
	} else {
		pcie->fpga_flag = 1;
		PCIE_PR_INFO("FPGA Platform");
	}

	prop = of_find_property(pdev->dev.of_node, "ep_flag", &len);
	if (prop != NULL) {
		pcie->ep_flag = 1;
		PCIE_PR_INFO("EndPoint Device");
	} else {
		pcie->ep_flag = 0;
		PCIE_PR_INFO("RootComplex");
	}

	return 0;
}


static void kirin_pcie_sideband_dbi_w_mode(struct pcie_port *pp, bool on)
{
	u32 val;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	val = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL0_ADDR);
	if (on)
		val = val | PCIE_ELBI_SLV_DBI_ENABLE;
	else
		val = val & ~PCIE_ELBI_SLV_DBI_ENABLE;

	kirin_elb_writel(pcie, val, SOC_PCIECTRL_CTRL0_ADDR);
}

static void kirin_pcie_sideband_dbi_r_mode(struct pcie_port *pp, bool on)
{
	u32 val;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);
	val = kirin_elb_readl(pcie, SOC_PCIECTRL_CTRL1_ADDR);

	if (on)
		val = val | PCIE_ELBI_SLV_DBI_ENABLE;
	else
		val = val & ~PCIE_ELBI_SLV_DBI_ENABLE;

	kirin_elb_writel(pcie, val, SOC_PCIECTRL_CTRL1_ADDR);
}

static void kirin_pcie_power_on(struct pcie_port *pp)
{
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	/*mtcmos on*/
	kirin_pcie_mtcmos_ctrl(pcie, MTCMOS_ON);
	udelay(100);
	PCIE_PR_DEBUG("mtcmos on Done ");

	/*clk enable*/
	kirin_pcie_clk_ctrl(pcie, CLK_ON);
	udelay(1);
	PCIE_PR_DEBUG("clock on Done ");
	/*clk disable*/
	kirin_pcie_clk_ctrl(pcie, CLK_OFF);
	udelay(1);
	PCIE_PR_DEBUG("clk off Done ");

	/*ISO disable*/
	kirin_pcie_iso_ctrl(pcie, ISO_DISABLE);
	PCIE_PR_DEBUG("iso disable Done ");

	/*unset module*/
	kirin_pcie_reset_ctrl(pcie, RESET_DISABLE_FLAG);
	PCIE_PR_DEBUG("module unreset Done ");

	/*clk on*/
	kirin_pcie_clk_ctrl(pcie, CLK_ON);
	PCIE_PR_DEBUG("clk on Done ");

	/*clear bus idle*/
	kirin_pcie_busidle_ctrl(pcie, BUSIDLE_CLEAR_FLAG);
	udelay(2);
	PCIE_PR_DEBUG("busidle clear Done ");

}


static int kirin_pcie_establish_link(struct pcie_port *pp)
{
	int count = 0;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	PCIE_PR_INFO("++");

	if (dw_pcie_link_up(pp)) {
		PCIE_PR_ERR("Link already up");
		return 0;
	}

	/* setup root complex */
	dw_pcie_setup_rc(pp);
	PCIE_PR_DEBUG("setup rc Done ");

	/* assert LTSSM enable */
	kirin_elb_writel(pcie, PCIE_LTSSM_ENABLE_BIT,
			  PCIE_APP_LTSSM_ENABLE);
	PCIE_PR_DEBUG("enable ltssm Done ");

	/* check if the link is up or not */
	while (!dw_pcie_link_up(pp)) {
		mdelay(100);
		count++;
		if (count == 10) {
			PCIE_PR_ERR("PCIe Link Fail");
			return -EINVAL;
		}
	}

	PCIE_PR_INFO("Link up");

	return 0;
}

static irqreturn_t kirin_pcie_irq_handler(int irq, void *arg)
{
	struct pcie_port *pp = arg;

	kirin_pcie_clear_irq_pulse(pp);
	return IRQ_HANDLED;
}

static irqreturn_t kirin_pcie_msi_irq_handler(int irq, void *arg)
{
	struct pcie_port *pp = arg;

	return dw_handle_msi_irq(pp);
}

static void kirin_pcie_msi_init(struct pcie_port *pp)
{
	dw_pcie_msi_init(pp);

}

static void kirin_pcie_enable_interrupts(struct pcie_port *pp)
{
	if (IS_ENABLED(CONFIG_PCI_MSI))
		kirin_pcie_msi_init(pp);
}

static inline void kirin_pcie_readl_rc(struct pcie_port *pp,
					void __iomem *dbi_base, u32 *val)
{
	kirin_pcie_sideband_dbi_r_mode(pp, 1);
	*val = readl(dbi_base);
	kirin_pcie_sideband_dbi_r_mode(pp, 0);
}

static inline void kirin_pcie_writel_rc(struct pcie_port *pp,
					u32 val, void __iomem *dbi_base)
{
	kirin_pcie_sideband_dbi_w_mode(pp, 1);
	writel(val, dbi_base);
	kirin_pcie_sideband_dbi_w_mode(pp, 0);
}

static int kirin_pcie_rd_own_conf(struct pcie_port *pp, int where, int size,
				u32 *val)
{
	int ret;
	kirin_pcie_sideband_dbi_r_mode(pp, true);
	ret = dw_pcie_cfg_read(pp->dbi_base + (where & ~0x3), where, size, val);
	kirin_pcie_sideband_dbi_r_mode(pp, false);
	return ret;
}

static int kirin_pcie_wr_own_conf(struct pcie_port *pp, int where, int size,
				u32 val)
{
	int ret;
	kirin_pcie_sideband_dbi_w_mode(pp, true);
	ret = dw_pcie_cfg_write(pp->dbi_base + (where & ~0x3),
			where, size, val);
	kirin_pcie_sideband_dbi_w_mode(pp, false);
	return ret;
}

static int kirin_pcie_link_up(struct pcie_port *pp)
{
	struct kirin_pcie *pcie = to_kirin_pcie(pp);
	u32 val = kirin_elb_readl(pcie, PCIE_ELBI_RDLH_LINKUP);

	if (val == PCIE_ELBI_LTSSM_ENABLE)
		return 1;

	return 0;
}


static void kirin_pcie_clear_irq_pulse(struct pcie_port *pp)
{
	u32 val;
	struct kirin_pcie *pcie = to_kirin_pcie(pp);

	val = kirin_elb_readl(pcie, PCIE_IRQ_PULSE);
	kirin_elb_writel(pcie, val, PCIE_IRQ_PULSE);
}

static int kirin_pcie_msi_host_init(struct pcie_port *pp,
			struct msi_controller *chip)
{

	struct device_node *msi_node;
	struct irq_domain *irq_domain;
	struct device_node *np = pp->dev->of_node;

	msi_node = of_parse_phandle(np, "msi-parent", 0);
	if (!msi_node) {
		dev_err(pp->dev, "failed to find msi-parent");
		return -ENODEV;
	}

	irq_domain = irq_find_host(msi_node);
	if (!irq_domain) {
		dev_err(pp->dev, "failed to find irq domain");
		return -ENODEV;
	}

	pp->irq_domain = irq_domain;

	return 0;
}

static void kirin_pcie_host_init(struct pcie_port *pp)
{
	kirin_pcie_establish_link(pp);
	kirin_pcie_enable_interrupts(pp);
}

static struct pcie_host_ops kirin_pcie_host_ops = {
	.readl_rc = kirin_pcie_readl_rc,
	.writel_rc = kirin_pcie_writel_rc,
	.rd_own_conf = kirin_pcie_rd_own_conf,
	.wr_own_conf = kirin_pcie_wr_own_conf,
	.link_up = kirin_pcie_link_up,
	.host_init = kirin_pcie_host_init,
	.msi_host_init = kirin_pcie_msi_host_init,
};

static int __init kirin_add_pcie_port(struct pcie_port *pp,
					   struct platform_device *pdev)
{
	int ret;
	PCIE_PR_INFO("++");
	pp->irq = platform_get_irq(pdev, 1);
	if (!pp->irq) {
		PCIE_PR_ERR("failed to get irq");
		return -ENODEV;
	}

	ret = devm_request_irq(&pdev->dev, pp->irq, kirin_pcie_irq_handler,
				IRQF_SHARED, "kirin-pcie", pp);
	if (ret) {
		PCIE_PR_ERR("failed to request irq");
		return ret;
	}


	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		pp->msi_irq = platform_get_irq(pdev, 0);
		if (!pp->msi_irq) {
			PCIE_PR_ERR("failed to get msi irq");
			return -ENODEV;
		}

		ret = devm_request_irq(&pdev->dev, pp->msi_irq,
					kirin_pcie_msi_irq_handler,
					IRQF_SHARED, "kirin-pcie", pp);
		if (ret) {
			PCIE_PR_ERR("failed to request msi irq");
			return ret;
		}
	}

	pp->root_bus_nr = -1;
	pp->ops = &kirin_pcie_host_ops;

	ret = dw_pcie_host_init(pp);
	if (ret) {
		PCIE_PR_ERR("failed to initialize host");
		return ret;
	}

	PCIE_PR_INFO("Add pcie port sucessed ");
	return 0;
}

static int kirin_pcie_probe(struct platform_device *pdev)
{
	struct kirin_pcie *kirin_pcie;
	struct pcie_port *pp;
	int ret = 0;

	PCIE_PR_INFO("++");

	kirin_pcie = devm_kzalloc(&pdev->dev, sizeof(*kirin_pcie),
				GFP_KERNEL);
	if (!kirin_pcie) {
		PCIE_PR_ERR("devm_kzallic fail");
		return -ENOMEM;
	}

	g_rc_pcie = kirin_pcie;

	if (pdev->dev.of_node == NULL)
		PCIE_PR_ERR("of node is NULL ");

	pp = &kirin_pcie->pp;

	pp->dev = &(pdev->dev);

	kirin_pcie_get_boardtype(kirin_pcie, pdev);

	ret = kirin_pcie_get_clk(kirin_pcie, pdev);
	if (ret != 0)
		return -ENODEV;

	ret = kirin_pcie_get_resource(pp, pdev);
	if (ret != 0)
		return -ENODEV;

	kirin_pcie_power_on(pp);

	/*Default Access remote device*/
	ret = kirin_elb_readl(kirin_pcie, SOC_PCIECTRL_CTRL0_ADDR);
	kirin_pcie_sideband_dbi_r_mode(pp, 0);
	kirin_pcie_sideband_dbi_w_mode(pp, 0);

	kirin_elb_writel(kirin_pcie, 0x800, 0x1c);

	PCIE_PR_INFO("RC Mode, Add port ");
	kirin_elb_writel(kirin_pcie, 0x2007, 0x030);
	kirin_elb_writel(kirin_pcie, 0x800, 0x1c);
	ret = kirin_add_pcie_port(pp, pdev);
	if (ret < 0) {
		PCIE_PR_ERR("Failed to add pcie port, ret=[%d]", ret);
		return ret;
	}

	platform_set_drvdata(pdev, kirin_pcie);

	PCIE_PR_INFO("--");
	return 0;

}

static int kirin_pcie_remove(struct platform_device *pdev)
{
	struct kirin_pcie *pcie = platform_get_drvdata(pdev);
	/*set busidle*/
	kirin_pcie_busidle_ctrl(pcie, BUSIDLE_SET_FLAG);

	/*reset module*/
	kirin_pcie_reset_ctrl(pcie, RESET_ENABLE_FLAG);

	/*clk disable*/
	kirin_pcie_clk_ctrl(pcie, CLK_OFF);

	/*ISO enable*/
	kirin_pcie_iso_ctrl(pcie, ISO_ENABLE);

	/*mtcmos off(ctrl)*/
	kirin_pcie_mtcmos_ctrl(pcie, MTCMOS_OFF);

	/*power off phy*/

	return 0;
}

static int kirin_pcie_resume(struct platform_device *pdev)
{
	struct pci_dev *rc_dev = NULL;
	unsigned int val = 0;
	int ret = 0;

	PCIE_PR_INFO("++");
	/*首先要恢复PCIePHY的供电*/
	/*fpga不涉及*/

	kirin_pcie_clk_ctrl(g_rc_pcie, CLK_ON);

	/*解复位PCIePHY*/
	writel(RESET_CTRL_PHY_BIT, g_rc_pcie->crg_base + 0x88);

	/*重新训练链路*/
	val = kirin_elb_readl(g_rc_pcie, SOC_PCIECTRL_CTRL6_ADDR);
	val |= PCIE_LINK_RETRAIN;
	kirin_elb_writel(g_rc_pcie, val, SOC_PCIECTRL_CTRL6_ADDR);


	ret = kirin_pcie_link_up(&g_rc_pcie->pp);
	if (ret != 1) {
		PCIE_PR_ERR("Establish linkup Again Failed");
		return -EINVAL;
	}
	rc_dev = pci_get_device(PCIE_VENDOR_ID_RCP, PCIE_DEVICE_ID_RCP, NULL);
	if (!rc_dev) {
		PCIE_PR_ERR("Failed to get rc pci_dev");
		return -EINVAL;
	}

	pci_load_and_free_saved_state(rc_dev,
					&rc_saved_state);
	pci_restore_state(rc_dev);

	PCIE_PR_INFO("--");

	return 0;
}


static int kirin_pcie_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct pci_dev *rc_dev = NULL;
	int ret = 0;

	PCIE_PR_INFO("++");
	rc_dev = pci_get_device(PCIE_VENDOR_ID_RCP, PCIE_DEVICE_ID_RCP, NULL);
	if (!rc_dev) {
		PCIE_PR_ERR("Failed to get rc pci_dev");
		return -EINVAL;
	}

	ret = pci_save_state(rc_dev);
	rc_saved_state = pci_store_saved_state(rc_dev);
	if (ret) {
		PCIE_PR_ERR("Failed to save state of RC.");
		return ret;
	}

	/*PCIePHY下电(VP VPTX VPH)，该操作会把PCIeIO也下电*/
	/*fpga上不涉及*/

	/*关闭所有时钟*/
	/* kirin_pcie_clk_ctrl(pcie, CLK_OFF); */
	/*reset phy*/
	writel(RESET_CTRL_PHY_BIT, g_rc_pcie->crg_base + 0x84);
	ret = readl(g_rc_pcie->crg_base + 0x8c);
	PCIE_PR_INFO("Reset status register is [0x%x]", ret);

	PCIE_PR_INFO("--");
	return 0;
}


#if 0
void kirin_pcie_pm_control(int resume_flag)
{
	unsigned int ret = 0;
	PCIE_PR_INFO("EP Notify to Change RC State");
	if (resume_flag)
		kirin_pcie_resume();
	else
		kirin_pcie_suspend();
}
EXPORT_SYMBOL_GPL(kirin_pcie_pm_control);


void power_on_pcie(void)
{
	unsigned int val = 0;
	if (!g_rc_pcie) {
		PCIE_PR_INFO("NULL g_rc_pcie!!!");
		return -EINVAL;
	}

	/*首先要恢复PCIePHY的供电*/
	/*fpga不涉及*/


	/*mtcmos on*/
	kirin_pcie_mtcmos_ctrl(g_rc_pcie, MTCMOS_ON);
	udelay(100);
	PCIE_PR_DEBUG("mtcmos on Done");

	/*clk enable*/
	kirin_pcie_clk_ctrl(g_rc_pcie, CLK_ON);
	udelay(1);
	PCIE_PR_DEBUG("clock on Done");
	/*clk disable*/
	kirin_pcie_clk_ctrl(g_rc_pcie, CLK_OFF);
	udelay(1);
	PCIE_PR_DEBUG("clk off Done");

	/*ISO disable*/
	kirin_pcie_iso_ctrl(g_rc_pcie, ISO_DISABLE);
	PCIE_PR_DEBUG("iso disable Done");

	/*unset module*/
	kirin_pcie_reset_ctrl(g_rc_pcie, RESET_DISABLE_FLAG);
	PCIE_PR_DEBUG("module unreset Done");

	/*clk on*/
	kirin_pcie_clk_ctrl(g_rc_pcie, CLK_ON);
	PCIE_PR_DEBUG("clk on Done");

	/*clear bus idle*/
	kirin_pcie_busidle_ctrl(g_rc_pcie, BUSIDLE_CLEAR_FLAG);
	udelay(2);
	PCIE_PR_DEBUG("busidle clear Done");

	/*重新训练链路	*/
	val = kirin_elb_readl(g_rc_pcie, SOC_PCIECTRL_CTRL6_ADDR);
	val |= PCIE_LINK_RETRAIN;
	kirin_elb_writel(g_rc_pcie, val, SOC_PCIECTRL_CTRL6_ADDR);


	PCIE_PR_INFO("-- Sucessed to repoweron RC --");
	pci_scan_child_bus(g_root_bus);
	pci_assign_unassigned_bus_resources(g_root_bus);
	pci_bus_add_devices(g_root_bus);
	PCIE_PR_INFO("-- Add devices done --");
	return 0;
}
EXPORT_SYMBOL_GPL(power_on_pcie);

#endif
static const struct of_device_id kirin_pcie_match_table[] = {
	{
		.compatible = "Hisilicon,kirin-pcie",
		.data = NULL,
	},
};

MODULE_DEVICE_TABLE(of, kirin_pcie_match_table);

struct platform_driver kirin_pcie_driver = {
	.probe			= kirin_pcie_probe,
	.remove			= kirin_pcie_remove,
#ifdef CONFIG_PM
	.resume			= kirin_pcie_resume,
	.suspend		= kirin_pcie_suspend,
#endif
	.driver			= {
		.name			= "Kirin-pcie",
		.owner			= THIS_MODULE,
		.of_match_table = of_match_ptr(kirin_pcie_match_table),
	},
};


int __init kirin_pcie_init(void)
{
	return platform_driver_probe(&kirin_pcie_driver, kirin_pcie_probe);
}

subsys_initcall(kirin_pcie_init);


MODULE_AUTHOR("Xiaowei Song<songxiaowei@huawei.com>");
MODULE_DESCRIPTION("Hisilicon Kirin pcie driver");
MODULE_LICENSE("GPL");


