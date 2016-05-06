/*
* NoC. (NoC Mntn Module.)
*
* Copyright (c) 2016 Huawei Technologies CO., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#include <linux/io.h>
#include <linux/bitops.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/bug.h>
#include <linux/delay.h>
#include "hisi_noc_transcation.h"
#include "hisi_noc_packet.h"
#include <soc_cfg_sys_noc_bus_interface.h>

void init_transcation_info(struct noc_node *node)
{
	node->tran_cfg.statalarmmax = 0x00ffffff;
	node->tran_cfg.statperiod = 0x8;

	node->tran_cfg.trans_f_mode = 0x1;
	node->tran_cfg.trans_f_addrbase_low = 0x0;
	node->tran_cfg.trans_f_addrwindowsize = 0x20;
	node->tran_cfg.trans_f_opcode = 0x3;
	node->tran_cfg.trans_f_usermask = 0x0;
	node->tran_cfg.trans_f_securitymask = 0x0;
	node->tran_cfg.trans_p_mode = 0x0;
	node->tran_cfg.trans_p_thresholds_0_0 = 0x0;
	node->tran_cfg.trans_p_thresholds_0_1 = 0x1;
	node->tran_cfg.trans_p_thresholds_0_2 = 0x2;
	node->tran_cfg.trans_p_thresholds_0_3 = 0x3;
	node->tran_cfg.trans_m_counters_0_src = 0x20;
	node->tran_cfg.trans_m_counters_1_src = 0x21;
	node->tran_cfg.trans_m_counters_2_src = 0x22;
	node->tran_cfg.trans_m_counters_3_src = 0x23;
	node->tran_cfg.trans_m_counters_0_alarmmode = 0x2;
	node->tran_cfg.trans_m_counters_1_alarmmode = 0x2;
	node->tran_cfg.trans_m_counters_2_alarmmode = 0x2;
	node->tran_cfg.trans_m_counters_3_alarmmode = 0x2;

}

void enable_transcation_probe(const struct noc_node *node, void __iomem *base)
{
	unsigned int temp;

	/* Disable Transaction Probe */
	noc_clear_bit((char *)base, TRANS_M_CFGCTL, 0);
	noc_clear_bit((char *)base, TRANS_M_MAINCTL, 3);
	noc_set_bit((char *)base, TRANS_M_MAINCTL, 3);

	/* config Filter mode */
	writel_relaxed(node->tran_cfg.trans_f_mode,
		       (char *)base + TRANS_F_MODE);

	/* config Filter */
	writel_relaxed(node->tran_cfg.trans_f_addrbase_low,
		       (char *)base + TRANS_F_ADDRBASE_LOW);
	writel_relaxed(node->tran_cfg.trans_f_addrwindowsize,
		       (char *)base + TRANS_F_ADDRWINDOWSIZE);
	writel_relaxed(node->tran_cfg.trans_f_opcode,
		       (char *)base + TRANS_F_OPCODE);
	writel_relaxed(node->tran_cfg.trans_f_usermask,
		       (char *)base + TRANS_F_USERMASK);
	writel_relaxed(node->tran_cfg.trans_f_securitymask,
		       (char *)base + TRANS_F_SECURITYMASK);

	/* enable Transaction Probe */
	writel_relaxed(0x1, (char *)base + TRANS_P_EN);

	/* config Transaction Probe Mode */
	writel_relaxed(node->tran_cfg.trans_p_mode,
		       (char *)base + TRANS_P_MODE);

	/* config Transaction Probe Bins */
	writel_relaxed(node->tran_cfg.trans_p_thresholds_0_0,
		       (char *)base + TRANS_P_THRESHOLDS_0_0);
	writel_relaxed(node->tran_cfg.trans_p_thresholds_0_1,
		       (char *)base + TRANS_P_THRESHOLDS_0_1);
	writel_relaxed(node->tran_cfg.trans_p_thresholds_0_2,
		       (char *)base + TRANS_P_THRESHOLDS_0_2);
	writel_relaxed(node->tran_cfg.trans_p_thresholds_0_3,
		       (char *)base + TRANS_P_THRESHOLDS_0_3);

	/* config Transaction Probe Bins Source */
	writel_relaxed(node->tran_cfg.trans_m_counters_0_src,
		       (char *)base + TRANS_M_COUNTERS_0_SRC);
	writel_relaxed(node->tran_cfg.trans_m_counters_1_src,
		       (char *)base + TRANS_M_COUNTERS_1_SRC);
	writel_relaxed(node->tran_cfg.trans_m_counters_2_src,
		       (char *)base + TRANS_M_COUNTERS_2_SRC);
	writel_relaxed(node->tran_cfg.trans_m_counters_3_src,
		       (char *)base + TRANS_M_COUNTERS_3_SRC);

	/* config  Statisticscycle period ????????? */
	writel_relaxed(node->tran_cfg.statperiod,
		       (char *)base + TRANS_M_STATPERIOD);

	/* config alarm mode */
	writel_relaxed(node->tran_cfg.trans_m_counters_0_alarmmode,
		       (char *)base + TRANS_M_COUNTERS_0_ALARMMODE);
	writel_relaxed(node->tran_cfg.trans_m_counters_1_alarmmode,
		       (char *)base + TRANS_M_COUNTERS_1_ALARMMODE);
	writel_relaxed(node->tran_cfg.trans_m_counters_2_alarmmode,
		       (char *)base + TRANS_M_COUNTERS_2_ALARMMODE);
	writel_relaxed(node->tran_cfg.trans_m_counters_3_alarmmode,
		       (char *)base + TRANS_M_COUNTERS_3_ALARMMODE);

	/* config Statisticscycle alarm MAX ??????? */
	writel_relaxed(node->tran_cfg.statalarmmax,
		       (char *)base + TRANS_M_STATALARMMAX);

	/* enable alarm interrupt */
	noc_set_bit((char *)base, TRANS_M_MAINCTL, 4);

	temp = (u32) readl_relaxed((char *)base + TRANS_M_MAINCTL);
	pr_info("base + TRANS_M_MAINCTL is %d\n", temp);
	/* enable Transaction Probe */
	noc_set_bit((char *)base, TRANS_M_CFGCTL, 0);

	temp = (u32) readl_relaxed((char *)base + TRANS_M_CFGCTL);
	pr_info("base + TRANS_M_CFGCTL is %d\n", temp);
	wmb();
}

void disable_transcation_probe(void __iomem *base)
{
	noc_clear_bit((char *)base, TRANS_M_CFGCTL, 0);
	noc_clear_bit((char *)base, TRANS_M_MAINCTL, 3);
	noc_set_bit((char *)base, TRANS_M_MAINCTL, 4);

	wmb();
}

void noc_transcation_probe_hanlder(const struct noc_node *node,
				   void __iomem *base, unsigned int idx)
{
	unsigned int val;

	pr_err("noc_packet_probe_hanlder +++++++++++++++++++++%d\n", idx);
	val = (u32) readl_relaxed((char *)base + TRANS_M_COUNTERS_0_VAL);
	pr_err("the TRANS_M_COUNTERS_0_VAL is 0x%x\n", val);

	val = (u32) readl_relaxed((char *)base + TRANS_M_COUNTERS_1_VAL);
	pr_err("the TRANS_M_COUNTERS_1_VAL is 0x%x\n", val);

	val = (u32) readl_relaxed((char *)base + TRANS_M_COUNTERS_2_VAL);
	pr_err("the TRANS_M_COUNTERS_2_VAL is 0x%x\n", val);

	val = (u32) readl_relaxed((char *)base + TRANS_M_COUNTERS_3_VAL);
	pr_err("the TRANS_M_COUNTERS_3_VAL is 0x%x\n", val);

	val = (u32) readl_relaxed((char *)base + TRANS_P_OVERFLOWSTATUS);

	if (0x1 == val)
		writel_relaxed(0x1, (char *)base + TRANS_P_OVERFLOWRESET);

	writel_relaxed(0x1, (char *)base + TRANS_M_STATALARMCLR);

	wmb();

	disable_transcation_probe(base);

	enable_transcation_probe(node, base);
}

void enable_transcation_probe_by_name(const char *name)
{
	struct noc_node *node;
	void __iomem *base = get_errprobe_base(name);
	if (base == NULL) {
		pr_err("%s cannot get the node!\n", __func__);
		return;
	}

	node = get_probe_node(name);
	if (node == NULL) {
		pr_err("%s cannot get the node!\n", __func__);
		return;
	}

	enable_transcation_probe(node, base);
}
EXPORT_SYMBOL(enable_transcation_probe_by_name);

void disable_transcation_probe_by_name(const char *name)
{
	void __iomem *base = get_errprobe_base(name);
	if (base == NULL) {
		pr_err("%s cannot get the node!\n", __func__);
		return;
	}

	disable_transcation_probe(base);
}
EXPORT_SYMBOL(disable_transcation_probe_by_name);

void config_transcation_probe(const char *name,
			      const struct transcation_configration *tran_cfg)
{
	struct noc_node *node;

	node = get_probe_node(name);
	if (node == NULL) {
		pr_err("%s cannot get the node!\n", __func__);
		return;
	}

	memcpy(&(node->tran_cfg), tran_cfg, sizeof(node->tran_cfg));
}
EXPORT_SYMBOL(config_transcation_probe);
