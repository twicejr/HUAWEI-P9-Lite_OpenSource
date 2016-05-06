/*
 * PCIe host controller driver for HiSilicon Hip05 SoC
 *
 * Copyright (C) 2015 HiSilicon Co., Ltd. http://www.hisilicon.com
 *
 * Author: Zhou Wang <wangzhou1@hisilicon.com>
 *         Dacai Zhu <zhudacai@hisilicon.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irqdomain.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_pci.h>
#include <linux/platform_device.h>

#include "pcie-designware.h"

#define PCIE_SUBCTRL_MODE_REG                           0x2800
#define PCIE_SUBCTRL_SYS_STATE4_REG                     0x6818
#define PCIE_SLV_DBI_MODE                               0x0
#define PCIE_SLV_SYSCTRL_MODE                           0x1
#define PCIE_SLV_CONTENT_MODE                           0x2
#define PCIE_SLV_MSI_ASID                               0x10
#define PCIE_LTSSM_LINKUP_STATE                         0x11
#define PCIE_LTSSM_STATE_MASK                           0x3F
#define PCIE_MSI_ASID_ENABLE                            (0x1 << 12)
#define PCIE_MSI_ASID_VALUE                             (0x1 << 16)
#define PCIE_MSI_TRANS_ENABLE                           (0x1 << 12)
#define PCIE_MSI_TRANS_REG                              0x1c8
#define PCIE_MSI_LOW_ADDRESS                            0x1b4
#define PCIE_MSI_HIGH_ADDRESS                           0x1c4
#define PCIE_MSI_ADDRESS_VAL                            0xb7010040

#define PCIE_SYS_CTRL20_REG                             0x20
#define PCIE_RD_TAB_SEL                                 BIT(31)
#define PCIE_RD_TAB_EN                                  BIT(30)
#define PCIE_CFG_BAR0BASE                               0x10
#define PCIE_DB2_ENABLE_SHIFT                           BIT(0)
#define PCIE_DBI_CS2_ENABLE                             0x1
#define PCIE_DBI_CS2_DISABLE                            0x0

#define PCIE_CTRL_7_REG                                 0x114
#define PCIE_LTSSM_ENABLE_SHIFT                         BIT(11)
#define PCIE_SUBCTRL_RESET_REQ_REG                      0xA00
#define PCIE0_2_SUBCTRL_RESET_REQ_REG(port_id) \
	(PCIE_SUBCTRL_RESET_REQ_REG + (port_id << 3))
#define PCIE3_SUBCTRL_RESET_REQ_REG                     0xA68

#define PCIE_SUBCTRL_DRESET_REQ_REG                     0xA04
#define PCIE0_2_SUBCTRL_DRESET_REQ_REG(port_id) \
	(PCIE_SUBCTRL_DRESET_REQ_REG + (port_id << 3))
#define PCIE3_SUBCTRL_DRESET_REQ_REG                    0xA6C

#define PCIE_SUBCTRL_RESET_ST_REG                       0x5A00
#define PCIE0_2_SUBCTRL_RESET_ST_REG(port_id) \
	(PCIE_SUBCTRL_RESET_ST_REG + (port_id << 2))
#define PCIE3_SUBCTRL_RESET_ST_REG                      0x5A34

#define PCIE_SUBCTRL_SC_PCIE0_CLK_DIS_REG               0x304
#define PCIE_SUBCTRL_SC_PCIE0_2_CLK_DIS_REG(port_id) \
	(PCIE_SUBCTRL_SC_PCIE0_CLK_DIS_REG + (port_id << 3))
#define PCIE_SUBCTRL_SC_PCIE3_CLK_DIS_REG               0x324

#define PCIE_SUBCTRL_SC_PCIE0_CLK_ST_REG                0x5300
#define PCIE_SUBCTRL_SC_PCIE0_2_CLK_ST_REG(port_id) \
	(PCIE_SUBCTRL_SC_PCIE0_CLK_ST_REG + (port_id << 2))
#define PCIE_SUBCTRL_SC_PCIE3_CLK_ST_REG                0x5310

#define PCIE_SUBCTRL_SC_PCIE0_CLK_EN_REG                0x300
#define PCIE_SUBCTRL_SC_PCIE0_2_CLK_EN_REG(port_id) \
	(PCIE_SUBCTRL_SC_PCIE0_CLK_EN_REG + (port_id << 3))
#define PCIE_SUBCTRL_SC_PCIE3_CLK_EN_REG                0x320

#define PCIE_ASSERT_RESET_ON                            1
#define PCIE_DEASSERT_RESET_ON                          0
#define PCIE_CLOCK_ON                                   1
#define PCIE_CLOCK_OFF                                  0

#define PCIE_PCS_LOCAL_RESET_REQ                        0xAC0
#define PCIE_PCS_LOCAL_DRESET_REQ                       0xAC4
#define PCIE_PCS_RESET_REQ_REG                          0xA60
#define PCIE_PCS_RESET_REG_ST                           0x5A30
#define PCIE_PCS_LOCAL_DRESET_ST                        0x5A60
#define PCIE_PCS_LOCAL_RESET_ST                         0x5A60
#define PCIE_PCS_DRESET_REQ_REG                         0xA64
#define PCIE_M_PCS_IN15_CFG                             0x74
#define PCIE_M_PCS_IN13_CFG                             0x34
#define PCIE_PCS_RXDETECTED                             0xE4
#define PCIE_PCS_SERDES_STATUS                          0x8108
#define HIP05_PCIE_CORE_IS_RESET                        0x1
#define PCIE_CORE_MODE_REG                              0xF8
#define PCIE_LINK_WIDTH_SPEED_CONTROL                   0x80C
#define PORT_LOGIC_SPEED_CHANGE                         (0x1 << 17)

#define DS_API(lane) ((0x1FF6c + 8 * (15 - lane)) * 2)
#define PCIE_DFE_ENABLE_VAL                             0x3851
enum pcie_mac_phy_rate_e {
	PCIE_GEN1 = 0,		/* PCIE 1.0 */
	PCIE_GEN2 = 1,		/* PCIE 2.0 */
	PCIE_GEN3 = 2		/* PCIE 3.0 */
};

#define to_hisi_pcie(x)	container_of(x, struct hisi_pcie, pp)

struct hisi_pcie {
	void __iomem *subctrl_base;
	void __iomem *reg_base;
	void __iomem *phy_base;
	void __iomem *serdes_base;
	u32 port_id;
	struct pcie_port pp;
};

static inline void hisi_pcie_subctrl_writel(struct hisi_pcie *pcie,
					    u32 val, u32 reg)
{
	writel(val, pcie->subctrl_base + reg);
}

static inline u32 hisi_pcie_subctrl_readl(struct hisi_pcie *pcie, u32 reg)
{
	return readl(pcie->subctrl_base + reg);
}

static inline void hisi_pcie_apb_writel(struct hisi_pcie *pcie,
					u32 val, u32 reg)
{
	writel(val, pcie->reg_base + reg);
}

static inline u32 hisi_pcie_apb_readl(struct hisi_pcie *pcie, u32 reg)
{
	return readl(pcie->reg_base + reg);
}
static inline void hisi_pcie_pcs_writel(struct hisi_pcie *pcie,
					u32 val, u32 reg)
{
	writel(val, pcie->phy_base + reg);
}

static inline u32 hisi_pcie_pcs_readl(struct hisi_pcie *pcie, u32 reg)
{
	return readl(pcie->phy_base + reg);
}

static inline void hisi_pcie_serdes_writel(struct hisi_pcie *pcie,
					   u32 val, u32 reg)
{
	writel(val, pcie->serdes_base + reg);
}

/*
 * Change mode to indicate the same reg_base to base of PCIe host configure
 * registers, base of RC configure space or base of vmid/asid context table
 */
static void hisi_pcie_change_apb_mode(struct hisi_pcie *pcie, u32 mode)
{
	u32 val;
	u32 bit_mask;
	u32 bit_shift;
	u32 port_id = pcie->port_id;
	u32 reg = PCIE_SUBCTRL_MODE_REG + 0x100 * port_id;

	if ((port_id == 1) || (port_id == 2)) {
		bit_mask = 0xc;
		bit_shift = 0x2;
	} else {
		bit_mask = 0x6;
		bit_shift = 0x1;
	}

	val = hisi_pcie_subctrl_readl(pcie, reg);
	val = (val & (~bit_mask)) | (mode << bit_shift);
	hisi_pcie_subctrl_writel(pcie, val, reg);
}

/* Configure vmid/asid table in PCIe host */
static void hisi_pcie_config_context(struct hisi_pcie *pcie)
{
	int i;
	u32 val;

	/* enable to clean vmid and asid tables though apb bus */
	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_SYSCTRL_MODE);

	val = hisi_pcie_apb_readl(pcie, PCIE_SYS_CTRL20_REG);
	/* enable ar channel */
	val |= PCIE_RD_TAB_SEL | PCIE_RD_TAB_EN;
	hisi_pcie_apb_writel(pcie, val, PCIE_SYS_CTRL20_REG);

	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_CONTENT_MODE);
	for (i = 0; i < 0x800; i++)
		hisi_pcie_apb_writel(pcie, 0x0, i * 4);

	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_SYSCTRL_MODE);
	/* enable aw channel */
	val &= (~PCIE_RD_TAB_SEL);
	val |= PCIE_RD_TAB_EN;
	hisi_pcie_apb_writel(pcie, val, PCIE_SYS_CTRL20_REG);

	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_CONTENT_MODE);

	/*
	 * init vmid and asid tables for all PCIe devices as 0
	 * vmid table: 0 ~ 0x3ff, asid table: 0x400 ~ 0x7ff
	 */
	for (i = 0; i < 0x800; i++)
		hisi_pcie_apb_writel(pcie, 0x0, i * 4);

	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_SYSCTRL_MODE);

	val = hisi_pcie_apb_readl(pcie, PCIE_SYS_CTRL20_REG);
	/* disable ar channel */
	val |= PCIE_RD_TAB_SEL;
	val &= (~PCIE_RD_TAB_EN);
	hisi_pcie_apb_writel(pcie, val, PCIE_SYS_CTRL20_REG);
	/* disable aw channel */
	val &= ((~PCIE_RD_TAB_SEL) & (~PCIE_RD_TAB_EN));
	hisi_pcie_apb_writel(pcie, val, PCIE_SYS_CTRL20_REG);

	hisi_pcie_apb_writel(pcie, PCIE_MSI_ADDRESS_VAL, PCIE_MSI_LOW_ADDRESS);
	hisi_pcie_apb_writel(pcie, 0x0, PCIE_MSI_HIGH_ADDRESS);
	hisi_pcie_apb_writel(pcie, PCIE_MSI_ASID_ENABLE | PCIE_MSI_ASID_VALUE,
			     PCIE_SLV_MSI_ASID);
	hisi_pcie_apb_writel(pcie, PCIE_MSI_TRANS_ENABLE, PCIE_MSI_TRANS_REG);

	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_DBI_MODE);
}

static int hisi_pcie_link_up(struct pcie_port *pp)
{
	u32 val;
	struct hisi_pcie *hisi_pcie = to_hisi_pcie(pp);

	val = hisi_pcie_subctrl_readl(hisi_pcie, PCIE_SUBCTRL_SYS_STATE4_REG +
				      0x100 * hisi_pcie->port_id);

	return ((val & PCIE_LTSSM_STATE_MASK) == PCIE_LTSSM_LINKUP_STATE);
}

static void hisi_pcie_enable_ltssm(struct hisi_pcie *pcie, bool on)
{
	u32 val;

	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_SYSCTRL_MODE);

	val = hisi_pcie_apb_readl(pcie, PCIE_CTRL_7_REG);
	if (on)
		val |= PCIE_LTSSM_ENABLE_SHIFT;
	else
		val &= ~(PCIE_LTSSM_ENABLE_SHIFT);
	hisi_pcie_apb_writel(pcie, val, PCIE_CTRL_7_REG);

	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_DBI_MODE);
}

static void hisi_pcie_gen3_dfe_enable(struct hisi_pcie *pcie)
{
	u32 val;
	u32 lane;
	u32 current_speed;
	u32 port_id = pcie->port_id;

	if (port_id == 3)
		return;

	val = hisi_pcie_subctrl_readl(pcie,
				      PCIE_SUBCTRL_SYS_STATE4_REG +
				      0x100 * port_id);
	current_speed = (val >> 6) & 0x3;

	if (current_speed != PCIE_GEN3)
		return;

	for (lane = 0; lane < 8; lane++)
		hisi_pcie_serdes_writel(pcie,
					PCIE_DFE_ENABLE_VAL, DS_API(lane) + 4);

	dev_info(pcie->pp.dev, "enable DFE success!\n");
}


static void hisi_pcie_core_reset_ctrl(struct hisi_pcie *pcie,
			bool reset_on)
{
	u32 reg_reset_ctrl;
	u32 reg_dereset_ctrl;
	u32 reg_reset_status;
	u32 reset_status;
	u32 reset_status_checked;
	unsigned long timeout;
	u32 port_id = pcie->port_id;

	if (port_id == 3) {
		reg_reset_ctrl = PCIE3_SUBCTRL_RESET_REQ_REG;
		reg_dereset_ctrl = PCIE3_SUBCTRL_DRESET_REQ_REG;
		reg_reset_status = PCIE3_SUBCTRL_RESET_ST_REG;
	} else {
		reg_reset_ctrl = PCIE0_2_SUBCTRL_RESET_REQ_REG(port_id);
		reg_dereset_ctrl = PCIE0_2_SUBCTRL_DRESET_REQ_REG(port_id);
		reg_reset_status = PCIE0_2_SUBCTRL_RESET_ST_REG(port_id);
	}

	if (reset_on) {
		/* if core is link up, stop the ltssm state machine first */
		if (hisi_pcie_link_up(&pcie->pp))
			hisi_pcie_enable_ltssm(pcie, 0);

		hisi_pcie_subctrl_writel(pcie, 0x1, reg_reset_ctrl);
	} else
		hisi_pcie_subctrl_writel(pcie, 0x1, reg_dereset_ctrl);

	timeout = jiffies + HZ * 1;
	do {
		reset_status = hisi_pcie_subctrl_readl(pcie, reg_reset_status);
		if (reset_on)
			reset_status_checked = ((reset_status & 0x01) !=
				HIP05_PCIE_CORE_IS_RESET);
		else
			reset_status_checked = ((reset_status & 0x01) != 0);

	} while ((reset_status_checked) && (time_before(jiffies, timeout)));

	/* get a timeout error */
	if (reset_status_checked)
		dev_err(pcie->pp.dev, "pcie core reset or dereset failed!\n");
}

static void hisi_pcie_clock_ctrl(struct hisi_pcie *pcie, bool clock_on)
{
	u32 reg_clock_disable;
	u32 reg_clock_enable;
	u32 reg_clock_status;
	u32 clock_status;
	u32 clock_status_checked;
	unsigned long timeout;
	u32 port_id = pcie->port_id;

	if (port_id == 3) {
		reg_clock_disable = PCIE_SUBCTRL_SC_PCIE3_CLK_DIS_REG;
		reg_clock_enable = PCIE_SUBCTRL_SC_PCIE3_CLK_EN_REG;
		reg_clock_status = PCIE_SUBCTRL_SC_PCIE3_CLK_ST_REG;
	} else {
		reg_clock_disable =
		    PCIE_SUBCTRL_SC_PCIE0_2_CLK_DIS_REG(port_id);
		reg_clock_enable = PCIE_SUBCTRL_SC_PCIE0_2_CLK_EN_REG(port_id);
		reg_clock_status = PCIE_SUBCTRL_SC_PCIE0_2_CLK_ST_REG(port_id);
	}

	if (clock_on)
		hisi_pcie_subctrl_writel(pcie, 0x3, reg_clock_enable);
	else
		hisi_pcie_subctrl_writel(pcie, 0x3, reg_clock_disable);

	timeout = jiffies + HZ * 1;
	do {
		clock_status = hisi_pcie_subctrl_readl(pcie, reg_clock_status);
		if (clock_on)
			clock_status_checked = ((clock_status & 0x03) != 0x3);
		else
			clock_status_checked = ((clock_status & 0x03) != 0);

	} while ((clock_status_checked) && (time_before(jiffies, timeout)));

	/* get a timeout error */
	if (clock_status_checked)
		dev_err(pcie->pp.dev, "clock operation failed!\n");
}

static void hisi_pcie_assert_core_reset(struct hisi_pcie *pcie)
{
	hisi_pcie_core_reset_ctrl(pcie, PCIE_ASSERT_RESET_ON);
	hisi_pcie_clock_ctrl(pcie, PCIE_CLOCK_OFF);
}

static void hisi_pcie_deassert_core_reset(struct hisi_pcie *pcie)
{
	hisi_pcie_core_reset_ctrl(pcie, PCIE_DEASSERT_RESET_ON);
}

static void hisi_pcie_deassert_pcs_reset(struct hisi_pcie *pcie)
{
	u32 val;
	u32 hilink_reset_status;
	u32 pcs_local_status;
	u32 hilink_status_checked;
	u32 pcs_local_status_checked;
	unsigned long timeout;
	u32 port_id = pcie->port_id;

	val = 1 << port_id;
	hisi_pcie_subctrl_writel(pcie, val, PCIE_PCS_LOCAL_DRESET_REQ);

	val = 0xff << (port_id << 3);
	hisi_pcie_subctrl_writel(pcie, val, PCIE_PCS_DRESET_REQ_REG);

	timeout = jiffies + HZ * 1;
	/* read reset status, make sure pcs is deassert */
	do {
		pcs_local_status = hisi_pcie_subctrl_readl(pcie,
						PCIE_PCS_LOCAL_RESET_ST);
		pcs_local_status_checked = (pcs_local_status & (1 << port_id));
	} while ((pcs_local_status_checked) && (time_before(jiffies, timeout)));

	/* get a timeout error */
	if (pcs_local_status_checked)
		dev_err(pcie->pp.dev, "pcs deassert reset failed!\n");

	timeout = jiffies + HZ * 1;

	do {
		hilink_reset_status = hisi_pcie_subctrl_readl(pcie,
						PCIE_PCS_RESET_REG_ST);
		hilink_status_checked = (hilink_reset_status &
					 (0xff << (port_id << 3)));
	} while ((hilink_status_checked) && (time_before(jiffies, timeout)));

	if (hilink_status_checked)
		dev_err(pcie->pp.dev, "pcs deassert reset failed!\n");
}

static void hisi_pcie_assert_pcs_reset(struct hisi_pcie *pcie)
{
	u32 reg;
	u32 hilink_reset_status;
	u32 pcs_local_reset_status;
	u32 hilink_status_checked;
	u32 pcs_local_status_checked;
	unsigned long timeout;
	u32 port_id = pcie->port_id;

	reg = 1 << port_id;
	hisi_pcie_subctrl_writel(pcie, reg, PCIE_PCS_LOCAL_RESET_REQ);

	reg = 0xff << (port_id << 3);
	hisi_pcie_subctrl_writel(pcie, reg, PCIE_PCS_RESET_REQ_REG);

	timeout = jiffies + HZ * 1;
	/* read reset status, make sure pcs is reset */
	do {
		pcs_local_reset_status = hisi_pcie_subctrl_readl(pcie,
						PCIE_PCS_LOCAL_RESET_ST);
		pcs_local_status_checked =
		    ((pcs_local_reset_status & (1 << port_id)) !=
		     (1 << port_id));

	} while ((pcs_local_status_checked) && (time_before(jiffies, timeout)));

	if (pcs_local_status_checked)
		dev_err(pcie->pp.dev, "pcs local reset status read failed\n");

	timeout = jiffies + HZ * 1;
	do {
		hilink_reset_status = hisi_pcie_subctrl_readl(pcie,
						PCIE_PCS_RESET_REG_ST);
		hilink_status_checked =
		    ((hilink_reset_status & (0xff << (port_id << 3))) !=
		     (0xff << (port_id << 3)));
	} while ((hilink_status_checked) && (time_before(jiffies, timeout)));

	if (hilink_status_checked)
		dev_err(pcie->pp.dev, "error:pcs assert reset failed\n");
}

static void hisi_pcie_init_pcs(struct hisi_pcie *pcie)
{
	u32 i;
	u32 lane_num = pcie->pp.lanes;

	if (pcie->port_id <= 2) {
		hisi_pcie_serdes_writel(pcie, 0x212, 0xc088);

		hisi_pcie_pcs_writel(pcie, 0x2026044, 0x8020);
		hisi_pcie_pcs_writel(pcie, 0x2126044, 0x8060);
		hisi_pcie_pcs_writel(pcie, 0x2126044, 0x80c4);
		hisi_pcie_pcs_writel(pcie, 0x2026044, 0x80e4);
		hisi_pcie_pcs_writel(pcie, 0x4018, 0x80a0);
		hisi_pcie_pcs_writel(pcie, 0x804018, 0x80a4);
		hisi_pcie_pcs_writel(pcie, 0x11201100, 0x80c0);
		hisi_pcie_pcs_writel(pcie, 0x3, 0x15c);
		hisi_pcie_pcs_writel(pcie, 0x0, 0x158);
	} else {
		for (i = 0; i < lane_num; i++)
			hisi_pcie_pcs_writel(pcie, 0x46e000,
					     PCIE_M_PCS_IN15_CFG + (i << 2));
		for (i = 0; i < lane_num; i++)
			hisi_pcie_pcs_writel(pcie, 0x1001,
					     PCIE_M_PCS_IN13_CFG + (i << 2));

		hisi_pcie_pcs_writel(pcie, 0xffff, PCIE_PCS_RXDETECTED);
	}
}

/*
 * In p660, pcie 3 do not support the 8Gbps speed we have no need to
 * use the equalization, but it has not affected to the funcion.
 */
void pcie_equalization(struct hisi_pcie *pcie)
{

	u32 val;

	hisi_pcie_apb_writel(pcie, 0x1400, 0x890);
	hisi_pcie_apb_writel(pcie, 0xfd7, 0x894);

	hisi_pcie_apb_writel(pcie, 0x0, 0x89c);
	hisi_pcie_apb_writel(pcie, 0xfc00, 0x898);
	hisi_pcie_apb_writel(pcie, 0x1, 0x89c);
	hisi_pcie_apb_writel(pcie, 0xbd00, 0x898);
	hisi_pcie_apb_writel(pcie, 0x2, 0x89c);
	hisi_pcie_apb_writel(pcie, 0xccc0, 0x898);
	hisi_pcie_apb_writel(pcie, 0x3, 0x89c);
	hisi_pcie_apb_writel(pcie, 0x8dc0, 0x898);
	hisi_pcie_apb_writel(pcie, 0x4, 0x89c);
	hisi_pcie_apb_writel(pcie, 0xfc0, 0x898);
	hisi_pcie_apb_writel(pcie, 0x5, 0x89c);
	hisi_pcie_apb_writel(pcie, 0xe46, 0x898);
	hisi_pcie_apb_writel(pcie, 0x6, 0x89c);
	hisi_pcie_apb_writel(pcie, 0xdc8, 0x898);
	hisi_pcie_apb_writel(pcie, 0x7, 0x89c);
	hisi_pcie_apb_writel(pcie, 0xcb46, 0x898);
	hisi_pcie_apb_writel(pcie, 0x8, 0x89c);
	hisi_pcie_apb_writel(pcie, 0x8c07, 0x898);
	hisi_pcie_apb_writel(pcie, 0x9, 0x89c);
	hisi_pcie_apb_writel(pcie, 0xd0b, 0x898);
	hisi_pcie_apb_writel(pcie, 0x103ff21, 0x8a8);

	val = hisi_pcie_apb_readl(pcie, 0x80);
	val |= 0x80;
	hisi_pcie_apb_writel(pcie, val, 0x80);

	hisi_pcie_apb_writel(pcie, 0x44444444, 0x184);
	hisi_pcie_apb_writel(pcie, 0x44444444, 0x188);
	hisi_pcie_apb_writel(pcie, 0x44444444, 0x18c);
	hisi_pcie_apb_writel(pcie, 0x44444444, 0x190);
}

static void hisi_pcie_mode_set(struct hisi_pcie *pcie)
{
	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_SYSCTRL_MODE);
	hisi_pcie_apb_writel(pcie, 0x4 << 28, PCIE_CORE_MODE_REG);
	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_DBI_MODE);
}

static void hisi_pcie_spd_set(struct hisi_pcie *pcie, u32 spd)
{
	u32 val;

	val = hisi_pcie_apb_readl(pcie, 0xa0);
	val &= ~(0xf);
	val |= spd;
	hisi_pcie_apb_writel(pcie, val, 0xa0);
}

static void hisi_pcie_spd_control(struct hisi_pcie *pcie)
{
	u32 val;

	/* set link width speed control register */
	val = hisi_pcie_apb_readl(pcie, PCIE_LINK_WIDTH_SPEED_CONTROL);
	/*
	 * set the Directed Speed Change field of the Link Width and Speed
	 * Change Control register
	 */
	val |= PORT_LOGIC_SPEED_CHANGE;
	hisi_pcie_apb_writel(pcie, val, PCIE_LINK_WIDTH_SPEED_CONTROL);
}

void hisi_pcie_establish_link(struct hisi_pcie *pcie)
{
	u32 val;
	int count = 0;

	if (dw_pcie_link_up(&pcie->pp)) {
		dev_info(pcie->pp.dev, "already Link up\n");
		return;
	}
	/* assert reset signals */
	hisi_pcie_assert_core_reset(pcie);
	hisi_pcie_assert_pcs_reset(pcie);

	/* de-assert phy reset */
	hisi_pcie_deassert_pcs_reset(pcie);

	/* de-assert core reset */
	hisi_pcie_deassert_core_reset(pcie);

	/* enable clock */
	hisi_pcie_clock_ctrl(pcie, PCIE_CLOCK_ON);

	/* initialize phy */
	hisi_pcie_init_pcs(pcie);

	/* set controller to RC mode */
	hisi_pcie_mode_set(pcie);

	/* set target link speed */
	hisi_pcie_spd_set(pcie, 3);

	/* set link speed control*/
	hisi_pcie_spd_control(pcie);

	/* setup root complex */
	dw_pcie_setup_rc(&pcie->pp);

	pcie_equalization(pcie);

	/* assert LTSSM enable */
	hisi_pcie_enable_ltssm(pcie, 1);

	/* check if the link is up or not */
	while (!dw_pcie_link_up(&pcie->pp)) {
		mdelay(100);
		count++;
		if (count == 10) {
			val = hisi_pcie_pcs_readl(pcie, PCIE_PCS_SERDES_STATUS);
			dev_info(pcie->pp.dev,
				 "PCIe Link Failed! PLL Locked: 0x%x\n", val);
			return;
		}
	}

	dev_info(pcie->pp.dev, "Link up\n");

	/* dfe enable is just for 660 */
	hisi_pcie_gen3_dfe_enable(pcie);
	/*
	 * add a 1s delay between linkup and enumeration, make sure
	 * the EP device's configuration registers are prepared well
	 */
	mdelay(1000);
}

static void hisi_pcie_set_db2_enable(struct hisi_pcie *pcie, u32 enable)
{
	u32 dbi_ctrl;

	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_SYSCTRL_MODE);

	dbi_ctrl = hisi_pcie_apb_readl(pcie, PCIE_SYS_CTRL20_REG);
	if (enable)
		dbi_ctrl |= PCIE_DB2_ENABLE_SHIFT;
	else
		dbi_ctrl &= ~PCIE_DB2_ENABLE_SHIFT;
	hisi_pcie_apb_writel(pcie, dbi_ctrl, PCIE_SYS_CTRL20_REG);

	hisi_pcie_change_apb_mode(pcie, PCIE_SLV_DBI_MODE);
}

static void hisi_pcie_disabled_bar0(struct hisi_pcie *pcie)
{
	hisi_pcie_set_db2_enable(pcie, PCIE_DBI_CS2_ENABLE);
	hisi_pcie_apb_writel(pcie, 0, PCIE_CFG_BAR0BASE);
	hisi_pcie_set_db2_enable(pcie, PCIE_DBI_CS2_DISABLE);
}

static int hisi_pcie_msi_host_init(struct pcie_port *pp,
			struct msi_controller *chip)
{
	struct device_node *msi_node;
	struct irq_domain *irq_domain;
	struct device_node *np = pp->dev->of_node;

	msi_node = of_parse_phandle(np, "msi-parent", 0);
	if (!msi_node) {
		dev_err(pp->dev, "failed to find msi-parent\n");
		return -ENODEV;
	}

	irq_domain = irq_find_host(msi_node);
	if (!irq_domain) {
		dev_err(pp->dev, "failed to find irq domain\n");
		return -ENODEV;
	}

	pp->irq_domain = irq_domain;

	return 0;
}

static void hisi_pcie_host_init(struct pcie_port *pp)
{
	struct hisi_pcie *pcie = to_hisi_pcie(pp);

	hisi_pcie_establish_link(pcie);
	hisi_pcie_config_context(pcie);
	/*
	 * The default size of BAR0 in p660 host bridge is 0x10000000,
	 * which will bring problem when most resource has been allocated
	 * to BAR0 in host bridge.However, we need not use BAR0 in host bridge
	 * in RC mode. Here we just disable it
	 */
	hisi_pcie_disabled_bar0(pcie);
}

static int hisi_pcie_cfg_write(struct pcie_port *pp, int where, int  size,
				u32 val)
{
	u32 reg_val;
	u32 reg;
	struct hisi_pcie *pcie = to_hisi_pcie(pp);
	void *walker = &reg_val;

	walker += (where & 0x3);
	reg = where & ~0x3;
	if (size == 4)
		hisi_pcie_apb_writel(pcie, val, reg);
	else if (size == 2) {
		reg_val = hisi_pcie_apb_readl(pcie, reg);
		*(u16 __force *) walker = val;
		hisi_pcie_apb_writel(pcie, reg_val, reg);
	} else if (size == 1) {
		reg_val = hisi_pcie_apb_readl(pcie, reg);
		*(u8 __force *) walker = val;
		hisi_pcie_apb_writel(pcie, reg_val, reg);
	} else
		return PCIBIOS_BAD_REGISTER_NUMBER;

	return PCIBIOS_SUCCESSFUL;
}

static struct pcie_host_ops hisi_pcie_host_ops = {
	.link_up = hisi_pcie_link_up,
	.msi_host_init = hisi_pcie_msi_host_init,
	.host_init = hisi_pcie_host_init,
	.wr_own_conf = hisi_pcie_cfg_write,
};

static int hisi_add_pcie_port(struct pcie_port *pp,
			      struct platform_device *pdev)
{
	int ret;
	u32 port_id;
	struct hisi_pcie *hisi_pcie = to_hisi_pcie(pp);

	if (of_property_read_u32(pdev->dev.of_node, "port-id", &port_id)) {
		dev_err(&pdev->dev, "failed to read port-id\n");
		return -EINVAL;
	}
	if (port_id > 3) {
		dev_err(&pdev->dev, "Invalid port-id: %d\n", port_id);
		return -EINVAL;
	}
	hisi_pcie->port_id = port_id;

	pp->ops = &hisi_pcie_host_ops;

	ret = dw_pcie_host_init(pp);
	if (ret) {
		dev_err(&pdev->dev, "failed to initialize host\n");
		return ret;
	}

	return 0;
}

static int hisi_pcie_probe(struct platform_device *pdev)
{
	struct hisi_pcie *hisi_pcie;
	struct pcie_port *pp;
	struct resource *reg;
	struct resource *subctrl;
	struct resource *phy;
	struct resource *serdes;
	int ret;

	hisi_pcie = devm_kzalloc(&pdev->dev, sizeof(*hisi_pcie), GFP_KERNEL);
	if (!hisi_pcie)
		return -ENOMEM;

	pp = &hisi_pcie->pp;
	pp->dev = &pdev->dev;

	subctrl = platform_get_resource_byname(pdev, IORESOURCE_MEM, "subctrl");
	hisi_pcie->subctrl_base = devm_ioremap_nocache(&pdev->dev,
					subctrl->start, resource_size(subctrl));
	if (IS_ERR(hisi_pcie->subctrl_base)) {
		dev_err(pp->dev, "cannot get subctrl base\n");
		return PTR_ERR(hisi_pcie->subctrl_base);
	}

	reg = platform_get_resource_byname(pdev, IORESOURCE_MEM, "rc_dbi");
	hisi_pcie->reg_base = devm_ioremap_resource(&pdev->dev, reg);
	if (IS_ERR(hisi_pcie->reg_base)) {
		dev_err(pp->dev, "cannot get rc_dbi base\n");
		return PTR_ERR(hisi_pcie->reg_base);
	}

	hisi_pcie->pp.dbi_base = hisi_pcie->reg_base;

	phy = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pcs");
	hisi_pcie->phy_base = devm_ioremap_resource(&pdev->dev, phy);
	if (IS_ERR(hisi_pcie->phy_base)) {
		dev_err(pp->dev, "cannot get phy base\n");
		return PTR_ERR(hisi_pcie->phy_base);
	}

	serdes = platform_get_resource_byname(pdev, IORESOURCE_MEM, "serdes");
	hisi_pcie->serdes_base = devm_ioremap_resource(&pdev->dev, serdes);
	if (IS_ERR(hisi_pcie->serdes_base)) {
		dev_err(pp->dev, "cannot get serdes base\n");
		return PTR_ERR(hisi_pcie->serdes_base);
	}
	ret = hisi_add_pcie_port(pp, pdev);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, hisi_pcie);

	return 0;
}

static const struct of_device_id hisi_pcie_of_match[] = {
	{.compatible = "hisilicon,hip05-pcie",},
	{},
};

MODULE_DEVICE_TABLE(of, hisi_pcie_of_match);

static struct platform_driver hisi_pcie_driver = {
	.driver = {
		   .name = "hisi-pcie",
		   .of_match_table = hisi_pcie_of_match,
	},
};

static int __init hisi_pcie_init(void)
{
	return platform_driver_probe(&hisi_pcie_driver, hisi_pcie_probe);
}
subsys_initcall(hisi_pcie_init);
