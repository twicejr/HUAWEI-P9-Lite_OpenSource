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
#include "hisi_noc_packet.h"
#include <soc_cfg_sys_noc_bus_interface.h>

void noc_set_bit(void __iomem *base, unsigned int offset, unsigned int bit)
{
	unsigned int temp;

	temp = (u32)readl_relaxed((char *)base + offset);

	temp = temp | ((unsigned int)0x1 << bit);

	writel_relaxed(temp, (char *)base + offset);
}

void noc_clear_bit(void __iomem *base, unsigned int offset, unsigned int bit)
{
	unsigned int temp;

	temp = (u32)readl_relaxed((char *)base + offset);

	temp = temp & (~(unsigned int)((unsigned int)0x1 << bit));

	writel_relaxed(temp, (char *)base + offset);
}

void init_packet_info(struct noc_node *node)
{
	node->packet_cfg.statalarmmax = 0xf;
	/*node->packet_cfg.statalarmmax = 0x1;*/


	node->packet_cfg.packet_filterlut = 0xE;
	/*node->packet_cfg.packet_f0_routeidbase = 0x114000;*/

	/*node->packet_cfg.packet_f0_routeidmask = 0x3FF000;*/

	node->packet_cfg.packet_f0_addrbase = 0x0;
	/*node->packet_cfg.packet_f0_windowsize = 0x1f;*/
	node->packet_cfg.packet_f0_windowsize = 0x20;
	node->packet_cfg.packet_f0_securitymask = 0x0;
	node->packet_cfg.packet_f0_opcode = 0xF;
	node->packet_cfg.packet_f0_status = 0x3;
	node->packet_cfg.packet_f0_length = 0x8;
	node->packet_cfg.packet_f0_urgency = 0x0;
	node->packet_cfg.packet_f0_usermask = 0x0;
	node->packet_cfg.statperiod = 0x8;
	node->packet_cfg.packet_f0_routeidbase = 0x600;
	node->packet_cfg.packet_f0_routeidmask = 0xFC0;
	node->packet_cfg.packet_f1_routeidbase = 0x400;
	node->packet_cfg.packet_f1_routeidmask = 0xFC0;
	node->packet_cfg.packet_counters_0_src = 0x12;

	node->packet_cfg.packet_f1_addrbase = 0x0;
	node->packet_cfg.packet_f1_windowsize = 0x20;
	node->packet_cfg.packet_f1_securitymask = 0x0;
	node->packet_cfg.packet_f1_opcode = 0xF;
	node->packet_cfg.packet_f1_status = 0x3;
	node->packet_cfg.packet_f1_length = 0x8;
	node->packet_cfg.packet_f1_urgency = 0x0;
	node->packet_cfg.packet_f1_usermask = 0x0;

	node->packet_cfg.packet_counters_1_src = 0x10;
	node->packet_cfg.packet_counters_0_alarmmode = 0x2;
	node->packet_cfg.packet_counters_1_alarmmode = 0x0;
}

void enable_packet_probe(const struct noc_node *node, void __iomem *base)
{
	unsigned int temp;
	/* Disable Packet Probe */
	noc_clear_bit(base, PACKET_CFGCTL, 0);
	noc_clear_bit(base, PACKET_MAINCTL, 3);
	noc_set_bit(base, PACKET_MAINCTL, 3);

	/* config packet source */
	writel_relaxed(node->packet_cfg.packet_counters_0_src, (char *)base + PACKET_COUNTERS_0_SRC);
	writel_relaxed(node->packet_cfg.packet_counters_1_src, (char *)base + PACKET_COUNTERS_1_SRC);

	/* config Statisticscycle ??????????*/
	writel_relaxed(node->packet_cfg.statperiod, (char *)base + PACKET_STATPERIOD);

	/* config counters alarmmode */
	writel_relaxed(node->packet_cfg.packet_counters_0_alarmmode, (char *)base + PACKET_COUNTERS_0_ALARMMODE);
	writel_relaxed(node->packet_cfg.packet_counters_1_alarmmode, (char *)base + PACKET_COUNTERS_1_ALARMMODE);

    writel_relaxed(node->packet_cfg.statalarmmax, (char *)base + PACKET_STATALARMMAX);

	/* config Filter */
	writel_relaxed(node->packet_cfg.packet_filterlut, (char *)base + PACKET_FILTERLUT);
	writel_relaxed(node->packet_cfg.packet_f0_routeidbase, (char *)base + PACKET_F0_ROUTEIDBASE);
	writel_relaxed(node->packet_cfg.packet_f0_routeidmask, (char *)base + PACKET_F0_ROUTEIDMASK);
	writel_relaxed(node->packet_cfg.packet_f0_addrbase, (char *)base + PACKET_F0_ADDRBASE);
	writel_relaxed(node->packet_cfg.packet_f0_windowsize, (char *)base + PACKET_F0_WINDOWSIZE);
	writel_relaxed(node->packet_cfg.packet_f0_securitymask, (char *)base + PACKET_F0_SECURITYMASK);
	writel_relaxed(node->packet_cfg.packet_f0_opcode, (char *)base + PACKET_F0_OPCODE);
	writel_relaxed(node->packet_cfg.packet_f0_status, (char *)base + PACKET_F0_STATUS);
	writel_relaxed(node->packet_cfg.packet_f0_length, (char *)base + PACKET_F0_LENGTH);
	writel_relaxed(node->packet_cfg.packet_f0_urgency, (char *)base + PACKET_F0_URGENCY);
	writel_relaxed(node->packet_cfg.packet_f0_usermask, (char *)base + PACKET_F0_USERMASK);

	writel_relaxed(node->packet_cfg.packet_f1_routeidbase, (char *)base + PACKET_F1_ROUTEIDBASE);
	writel_relaxed(node->packet_cfg.packet_f1_routeidmask, (char *)base + PACKET_F1_ROUTEIDMASK);
	writel_relaxed(node->packet_cfg.packet_f1_addrbase, (char *)base + PACKET_F1_ADDRBASE);
	writel_relaxed(node->packet_cfg.packet_f1_windowsize, (char *)base + PACKET_F1_WINDOWSIZE);
	writel_relaxed(node->packet_cfg.packet_f1_securitymask, (char *)base + PACKET_F1_SECURITYMASK);
	writel_relaxed(node->packet_cfg.packet_f1_opcode, (char *)base + PACKET_F1_OPCODE);
	writel_relaxed(node->packet_cfg.packet_f1_status, (char *)base + PACKET_F1_STATUS);
	writel_relaxed(node->packet_cfg.packet_f1_length, (char *)base + PACKET_F1_LENGTH);
	writel_relaxed(node->packet_cfg.packet_f1_urgency, (char *)base + PACKET_F1_URGENCY);
	writel_relaxed(node->packet_cfg.packet_f1_usermask, (char *)base + PACKET_F1_USERMASK);

	/* enable alarm interrupt */
	noc_set_bit(base, PACKET_MAINCTL, 4);

	temp = (u32)readl_relaxed((char *)base + PACKET_MAINCTL);
	pr_info("the PACKET_MAINCTL is 0x%x\n", temp);

	/* enable Packet Probe */
	noc_set_bit(base, PACKET_CFGCTL, 0);

	temp = (u32)readl_relaxed((char *)base + PACKET_CFGCTL);
	pr_info("the PACKET_CFGCTL is 0x%x\n", temp);

	wmb();
}

void disable_packet_probe(void __iomem *base)
{
	noc_clear_bit(base, PACKET_CFGCTL, 0);
	noc_clear_bit(base, PACKET_MAINCTL, 3);
	noc_set_bit(base, PACKET_MAINCTL, 4);

	wmb();
}

void noc_packet_probe_hanlder(const struct noc_node *node, void __iomem *base)
{
	unsigned int val;

	/* read packet counters value register */
	val = (unsigned int)readl_relaxed((char *)base + PACKET_COUNTERS_0_VAL);
	pr_err("noc_packet_probe_hanlder +++++++++++++++++++++\n");
	pr_err("the PACKET_COUNTERS_0_VAL is 0x%x\n", val);

	val = (unsigned int)readl_relaxed((char *)base + PACKET_COUNTERS_1_VAL);
	pr_err("the PACKET_COUNTERS_1_VAL is 0x%x\n", val);
	pr_err("noc_packet_probe_hanlder ---------------------\n");

	/* clear interrupt */
	writel_relaxed(0x1, (char *)base + PACKET_STATALARMCLR);

	wmb();

	disable_packet_probe(base);

	enable_packet_probe(node, base);
}

void enable_packet_probe_by_name(const char *name)
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

	enable_packet_probe(node, base);
}
EXPORT_SYMBOL(enable_packet_probe_by_name);


void disable_packet_probe_by_name(const char *name)
{
	void __iomem *base = get_errprobe_base(name);
	if (base == NULL) {
		pr_err("%s cannot get the node!\n", __func__);
		return;
	}

	disable_packet_probe(base);
}
EXPORT_SYMBOL(disable_packet_probe_by_name);

void config_packet_probe(const char *name, const struct packet_configration *packet_cfg)
{
	struct noc_node *node;

	node = get_probe_node(name);
	if (node == NULL) {
		pr_err("%s cannot get the node!\n", __func__);
		return;
	}

	memcpy(&(node->packet_cfg), packet_cfg, sizeof(node->packet_cfg));
}
EXPORT_SYMBOL(config_packet_probe);
