/*
* NoC. (NoC Mntn Module.)
*
* Copyright (c) 2016 Huawei Technologies CO., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#include <linux/module.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/syscore_ops.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/debugfs.h>
#include <linux/io.h>
#include <linux/string.h>
#include <linux/clk.h>
#include <linux/hisi/util.h>

#ifdef CONFIG_HISI_BB
#include "platform_ap/rdr_hisi_platform.h"
#endif
#include "hisi_noc.h"
#include "hisi_noc_err_probe.h"
#include "hisi_noc_packet.h"
#include "hisi_noc_info.h"
#include "hisi_noc_transcation.h"
#include "hisi_noc_dump.h"
#include "hisi_noc_dbg.h"

#include <soc_acpu_baseaddr_interface.h>
#include <soc_pmctrl_interface.h>
#include <soc_pctrl_interface.h>
#include <soc_sctrl_interface.h>

static struct noc_node *noc_nodes_array[MAX_NOC_NODES_NR] = {NULL};
static unsigned int nodes_array_idx;

static struct hisi_noc_irqd  noc_irqdata[NOC_MAX_IRQ_NR];
static struct platform_device *g_this_pdev;

static unsigned int g_noc_init;

/* NoC Property From DTS. */
static struct hisi_noc_property noc_property_dt = {
	.platform_id               = 0x0,
	.pctrl_irq_mask            = 0x0,
	.stop_cpu_bus_node_name    = NULL,
	.smp_stop_cpu_bit_mask     = 0x0,
	.apcu_init_flow_array      = {0x0, 0x0},
	.faulten_default_enable    = false,
	.packet_enable             = false,
	.transcation_enable        = false,
	.error_enable              = false,
	.noc_timeout_enable        = false,
	.noc_fama_enable           = false,
	.noc_fama_mask             = 0x0,
	.bus_node_base             = NULL,
	.noc_debug                 = false,
};

static struct of_device_id hisi_noc_match[] = {
	{.compatible = "hisilicon,noc", .data = (void *)NULL},
	{} /* end */
};

/*当ptype=1时，将noc的寄存器信息用printk输出，
	当ptype=0时，将其写入pstore的内存中*/
void noc_record_log_pstorememory(void __iomem *base, int ptype)
{
	unsigned int offset;
	unsigned int *reg;
	unsigned int size = SZ_128;

	pr_err("[base is 0x%llx]\n ", (u64) base);

	if (ptype == NOC_PTYPE_PSTORE) {
		mntn_print_to_ramconsole("Error logger dump:\n");
		for (offset = 0; offset < size;
		     offset += 4 * sizeof(unsigned int)) {
			reg = (unsigned int *)((char *)base + offset);
			mntn_print_to_ramconsole
			    ("[%08x] : %08x %08x %08x %08x\n", offset, *reg,
			     *(reg + 1), *(reg + 2), *(reg + 3));
		}
	} else if (ptype == NOC_PTYPE_UART) {
		pr_err("Error logger dump:\n");
		for (offset = 0; offset < size;
		     offset += 4 * sizeof(unsigned int)) {
			reg = (unsigned int *)((char *)base + offset);
			pr_err("[%08x] : %08x %08x %08x %08x\n", offset, *reg,
			       *(reg + 1), *(reg + 2), *(reg + 3));
		}
	} else {
		pr_err("ptype is error ,[%d]\n", ptype);
	}
}

/* Check if the noc clock is enabled.
To be backward-compatible,
it returns 1 by defualt, if there is no clock defined */
static unsigned int noc_clock_enable(struct hisi_noc_device *noc_dev,
				     struct noc_node *node)
{
	void __iomem *crgstatus_reg;
	unsigned int status;
	unsigned int i;
	unsigned int flag = 1;

	if (!noc_dev->pcrgctrl_base) {
		if (1 == noc_property_dt.noc_debug)
			pr_err("[%s]: pcrgctrl_base is null.\n", __func__);
		return 1;	/* For portland , CRG is not defined */
	}

	flag = 1;
	for (i = 0; i < HISI_NOC_CLOCK_MAX; i++) {
		if (0xFFFFFFFF == node->crg_clk[i].offset)
			continue;

		crgstatus_reg =
		    noc_dev->pcrgctrl_base + node->crg_clk[i].offset;
		status = readl_relaxed(crgstatus_reg);

		/* Clock is enabled */
		if (status & (1 << node->crg_clk[i].mask_bit))
			continue;
		else {
			flag = 0;
			break;
		}
	}

	if (1 == noc_property_dt.noc_debug) {
		pr_err("[%s] node(%s) clock enable=%d\n", __func__, node->name,
		       flag);
	}

	return flag;
}

int is_noc_node_available(struct noc_node *node)
{
	struct hisi_noc_device *noc_dev = NULL;
	unsigned int request, ack, status;

	if (NULL == g_this_pdev || NULL == node) {
		pr_err("[%s] g_this_pdev or node is NULL!!!\n", __func__);
		return 0;
	}

	noc_dev = platform_get_drvdata(g_this_pdev);
	if (NULL == noc_dev) {
		pr_err("[%s] Can not get device node pointer!!\n", __func__);
		return 0;
	}

	request = readl_relaxed(SOC_PMCTRL_NOC_POWER_IDLEREQ_ADDR(noc_dev->pmctrl_base));
	ack =  readl_relaxed(SOC_PMCTRL_NOC_POWER_IDLEACK_ADDR(noc_dev->pmctrl_base));
	status =  readl_relaxed(SOC_PMCTRL_NOC_POWER_IDLE_ADDR(noc_dev->pmctrl_base));
	if (!((request|ack|status) & (1 << node->pwrack_bit))
	    && noc_clock_enable(noc_dev, node)) {
		return 1;
	}

	return 0;
}

int noc_node_try_to_giveup_idle(struct noc_node *node)
{
	struct hisi_noc_device *noc_dev = NULL;
	unsigned long status = 0;
	void __iomem *pm_idlereq_reg = NULL;

	if (NULL == g_this_pdev || NULL == node) {
		pr_err("[%s] g_this_pdev or node is NULL!!!\n", __func__);
		return -1;
	}

	noc_dev = platform_get_drvdata(g_this_pdev);
	if (NULL == noc_dev) {
		pr_err("[%s] Can not get device node pointer!!\n", __func__);
		return -1;
	}

	status = readl_relaxed(SOC_PMCTRL_NOC_POWER_IDLE_ADDR(noc_dev->pmctrl_base));
	pr_err("[%s] before +, NOC_POWER_IDLE = 0x%lx;\n", __func__, status);

	/* try to exit idle state */
	pm_idlereq_reg =
	    SOC_PMCTRL_NOC_POWER_IDLEREQ_ADDR(noc_dev->pmctrl_base);
	status = readl_relaxed(pm_idlereq_reg);
	status &= ~(1 << (node->pwrack_bit));
	status |= (1 << (node->pwrack_bit + 16));
	writel_relaxed(status, pm_idlereq_reg);

	status = readl_relaxed(SOC_PMCTRL_NOC_POWER_IDLE_ADDR(noc_dev->pmctrl_base));
	pr_err("[%s] after -, NOC_POWER_IDLE = 0x%lx;\n", __func__, status);
	return 0;
}

int is_noc_err_node_available(struct noc_node *node)
{
	if (NULL == node)
		return 0;

	if ((NOC_ERR_PROBE_IRQ == node->hwirq_type) && (node->eprobe_autoenable)
	    && is_noc_node_available(node))
		return 1;

	return 0;
}

int is_noc_transcation_node_available(struct noc_node *node)
{
	if (NULL == node)
		return 0;

	if ((NOC_TRANS_PROBE_IRQ == node->hwirq_type)
	    && (node->eprobe_autoenable)
	    && is_noc_node_available(node))
		return 1;

	return 0;
}

int is_noc_packet_node_available(struct noc_node *node)
{
	if (NULL == node)
		return 0;

	if ((NOC_PACKET_PROBE_IRQ == node->hwirq_type)
	    && (node->eprobe_autoenable)
	    && is_noc_node_available(node))
		return 1;

	return 0;
}

struct platform_device *noc_get_pt_pdev(void)
{
	return g_this_pdev;
}

unsigned int is_noc_init(void)
{
	return g_noc_init;
}

bool noc_err_smp_stop_acpu(unsigned long long irq_status)
{
	unsigned int errlog_1 = 0;

	/* NoC Error Happened On Sys Bus Node. */
	if (irq_status & noc_property_dt.smp_stop_cpu_bit_mask) {

		errlog_1 = readl_relaxed(SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_ADDR(noc_property_dt.bus_node_base));

		/* sys_bus, init flow = acpu */
		if ((errlog_1 & noc_property_dt.apcu_init_flow_array[0]) == noc_property_dt.apcu_init_flow_array[1])
			return true;
	}

	return false;
}

/*
Function: noc_get_irq_status
Description: noc part, get irq status
input: void __iomem *pctrl_base: pctrl virtual base address
output: none
return: irq status
*/
unsigned long long noc_get_irq_status(void __iomem *pctrl_base)
{
	unsigned long long ret = 0;

	ret = readl_relaxed(pctrl_base + noc_property_dt.pctrl_peri_stat3_off);
	ret = (ret << 32) | readl_relaxed(pctrl_base + noc_property_dt.pctrl_peri_stat0_off);
	ret = ret & noc_property_dt.pctrl_irq_mask;

	return ret;
}

static irqreturn_t hisi_noc_timeout_irq_handler(int irq, void *data)
{
	void __iomem *pmctrl_base;
	struct hisi_noc_device *noc_dev = (struct hisi_noc_device *)data;
	unsigned int pending, scperstatus6;

	pmctrl_base = noc_dev->pmctrl_base;
	pending = readl_relaxed(pmctrl_base + PMCTRL_PERI_INT_STAT0_OFFSET);
	if (pending)
		pr_err("NoC timeout IRQ occured, PERI_INT_STAT0 = 0x%x\n", pending);
	else
		pr_err("PMCTRL other interrupt source occurs!\n");

	scperstatus6 = readl_relaxed(noc_dev->sctrl_base + SCTRL_SCPERSTATUS6);
	pr_err("SCTRL_SCPERSTATUS6 = 0x%x\n", scperstatus6);

	writel_relaxed(pending, pmctrl_base + PMCTRL_PERI_INT_MASK_OFFSET);

#ifdef CONFIG_HISI_BB
	if (check_himntn(HIMNTN_NOC_ERROR_REBOOT))
		rdr_syserr_process_for_ap(MODID_AP_S_NOC, 0, 1);
#endif
	return IRQ_HANDLED;
}

static irqreturn_t hisi_noc_irq_handler(int irq, void *data)
{
	unsigned long long pending;
	int offset;
	struct noc_node *node = NULL;
	void __iomem *porbe_base = NULL;
	struct hisi_noc_device *noc_dev = (struct hisi_noc_device *)data;
	const struct noc_bus_info *noc_bus;

    /* Get NoC Bus Irq Status From PCTRL. */
	pending = noc_get_irq_status(noc_dev->pctrl_base);

	/* Stop Other Cpus Immediately to Dump Call Stack. */
	if (!noc_property_dt.packet_enable || !noc_property_dt.transcation_enable) {
#ifdef CONFIG_HISI_BB
		if (check_himntn(HIMNTN_NOC_ERROR_REBOOT) && noc_err_smp_stop_acpu(pending)) {
			/* Stop Other CPUs. */
			smp_send_stop();

			/* Debug Print. */
			if (1 == noc_property_dt.noc_debug)
				pr_err("hisi_noc_irq_handler -- Stop CPUs First.\n");
		}
#endif
	}

	pr_err("noc irq status = 0x%llx\n", pending);

	if (1 == noc_property_dt.noc_debug)
		pr_err("Get into hisi_noc_irq_handler.\n");

	if (pending) {
		for_each_set_bit(offset, &pending, BITS_PER_LONG) {
			node = noc_irqdata[offset].node;
			if (NULL == node) {
				pr_err("node is null pointer !\n");
				return IRQ_HANDLED;
			}
			noc_bus = noc_get_bus_info(node->bus_id);
			if (NULL == noc_bus) {
				pr_err("[%s] noc_bus get error!\n", __func__);
				return IRQ_HANDLED;
			}

			porbe_base = node->eprobe_offset + node->base;

			switch (noc_irqdata[offset].type) {
			case NOC_ERR_PROBE_IRQ:
				if (noc_property_dt.error_enable) {
					u32 giveup_idle_retry = 0;
					if (is_noc_node_available(node)) {
						noc_record_log_pstorememory(porbe_base,
						     NOC_PTYPE_PSTORE);
					}
					pr_err("NoC Error Probe:\n");
					pr_err("noc_bus: %s\n", noc_bus->name);
					pr_err("noc_node: %s\n", node->name);
NOC_ERROR_CHECK:
					if (is_noc_node_available(node)) {
						noc_err_probe_hanlder(porbe_base, node);
					} else {
						pr_err("noc_node: %s, module powerdown\n", node->name);
						if (giveup_idle_retry++ < 5) {
							noc_node_try_to_giveup_idle(node);
							pr_err("noc_node_try_to_giveup_idle , %d time\n",
							     giveup_idle_retry);
							goto NOC_ERROR_CHECK;
						}
						pr_err("Finally, noc_node: %s powerdown state cann't be changed!\n",
						     node->name);
						/* while(1);
						dead loop for manually check out what happened
						on the noc bus */
						BUG_ON(1);
					}
				}
				break;
			case NOC_PACKET_PROBE_IRQ:
				if (noc_property_dt.packet_enable) {
					/* FixMe: packet probe irq handler */
					pr_err("NoC PACKET Probe:\n");
					pr_err("noc_bus: %s\n", noc_bus->name);
					pr_err("noc_node: %s\n", node->name);
					if (is_noc_node_available(node)) {
						noc_packet_probe_hanlder(node,
									 porbe_base);
					} else {
						pr_err
						("noc_node: %s, module powerdown\n",
						node->name);
					}
				}
				break;
			case NOC_TRANS_PROBE_IRQ:
				if (noc_property_dt.transcation_enable) {
					/* FixMe: trans probe irq handler */
					pr_err("NoC TRANSCATION Probe:\n");
					pr_err("noc_bus: %s\n", noc_bus->name);
					pr_err("noc_node: %s\n", node->name);

					if (is_noc_node_available(node))
						noc_transcation_probe_hanlder(node,
							porbe_base, node->bus_id);
					else
						pr_err("noc_node: %s, module powerdown\n",
							node->name);
				}
				break;
			default:
				pr_err("NoC IRQ type is wrong!\n");

			}
		}
	}

	return IRQ_HANDLED;
}

static int find_bus_id_by_name(const char *bus_name)
{
	int i;
	struct noc_arr_info *pt_noc_arr;
	const struct noc_bus_info *pt_noc_bus_info;

	pt_noc_arr = noc_get_buses_info();
	pt_noc_bus_info = pt_noc_arr->ptr;

	for (i = 0; i < pt_noc_arr->len; i++) {
		if (strncmp(bus_name, pt_noc_bus_info[i].name, 256) == 0)
			return i;
	}
	return -ENODEV;
}

/****************************************************
 FUNC: get_noc_node_clock()

 Description : Read clock information from NOC DTSI.
 In DTSI, the clock defination should be like below:
 crg_clk0=<0x0c,22>;
 crg_clk1=<0x1c,22>;

 If it's not defined in DTSI, fill the struct data by 0xFFFFFFFF
******************************************************/
static void get_noc_node_clock(struct device_node *np, struct noc_node *node)
{

	unsigned int clk_reg_u32[2] = { 0 };
	char clock_name[16] = { };
	int i;
	int ret = 0;

	if (!np) {
		if (noc_property_dt.noc_debug)
			pr_err("[%s]:np is NULL\n", __func__);
		return;
	}

	if (!node) {
		if (noc_property_dt.noc_debug)
			pr_err("[%s]:node is NULL\n", __func__);
		return;
	}
	/* Init struct data as 0xFFFFFFFF */
	memset(&node->crg_clk[0], 0xff,
	       sizeof(struct noc_clk) * HISI_NOC_CLOCK_MAX);

	for (i = 0; i < HISI_NOC_CLOCK_MAX; i++) {
		snprintf(clock_name, sizeof(clock_name), "crg_clk%d", i);
		ret = of_property_read_u32_array(np,
					clock_name, clk_reg_u32, 2);
		if (ret) {
			continue;
		} else {
			if (clk_reg_u32[1] > 32) {	/* 32 bit register */
				pr_err("[%s]:NOC node[%s] %s  invalid mask_bit=%d\n",
				     __func__, node->name, clock_name,
				     node->crg_clk[i].mask_bit);
				continue;
			}
			node->crg_clk[i].offset = clk_reg_u32[0];
			node->crg_clk[i].mask_bit = clk_reg_u32[1];
			if (noc_property_dt.noc_debug)
				pr_info("[%s]:NOC node[%s] %s  offset=0x%x, mask_bit=%d\n",
				     __func__, node->name, clock_name,
				     node->crg_clk[i].offset,
				     node->crg_clk[i].mask_bit);
		}
	}

	return;
}

static int register_noc_node(struct device_node *np)
{
	struct noc_node *node;
	int ret = 0;
	const char *bus_name;

	node = kzalloc(sizeof(struct noc_node), GFP_KERNEL);
	if (!node) {
		pr_err("fail to alloc memory, noc_node=%s!\n", np->name);
		ret = -ENOMEM;
		goto err;
	}

	node->base = of_iomap(np, 0);
	if (!node->base) {
		WARN_ON(1);
		goto err_iomap;
	}

	/* err probe property */
	if (noc_property_dt.error_enable) {
		if (of_property_read_bool(np, "eprobe-autoenable"))
			node->eprobe_autoenable = true;

		ret = of_property_read_u32(np, "eprobe-hwirq",
					 &node->eprobe_hwirq);
		if (ret < 0) {
			node->eprobe_hwirq = -1;
			pr_debug("the node doesnot have err probe!\n");
		}

		if (node->eprobe_hwirq >= 0) {
			ret = of_property_read_u32(np, "eprobe-offset",
						 &node->eprobe_offset);
			if (ret < 0) {
				node->eprobe_hwirq = -1;
				pr_debug("the node doesnot have err probe!\n");
			}
		}

	}

	if (node->eprobe_hwirq >= 0) {
		ret = of_property_read_u32(np, "hwirq-type", &node->hwirq_type);
		if (ret < 0) {
			node->hwirq_type = -1;
			pr_err("the node doesnot have hwirq type!\n");
		}
	}
	ret = of_property_read_u32(np, "pwrack-bit", &node->pwrack_bit);
	if (ret < 0) {
		node->pwrack_bit = -1;
		pr_debug("the node doesnot have pwrack_bit property!\n");
		ret = -ENODEV;
		goto err_iomap;
	}

	node->name = kstrdup(np->name, GFP_KERNEL);
	if (!node->name) {
		ret = -ENOMEM;
		goto err_iomap;
	}

	if (!strcmp(node->name, noc_property_dt.stop_cpu_bus_node_name))
		noc_property_dt.bus_node_base = node->base;

	/* Get clock information */
	get_noc_node_clock(np, node);

	ret = of_property_read_string(np, "bus-name", &bus_name);
	if (ret < 0) {
		WARN_ON(1);
		goto err_property;
	}

	ret = find_bus_id_by_name(bus_name);
	if (ret < 0) {
		WARN_ON(1);
		goto err_property;
	}
	node->bus_id = ret;

	/* FIXME: handle the transprobe & packet probe property */
	/* Debug info */
	if (noc_property_dt.noc_debug) {
		pr_debug("[%s]: nodes_array_idx = %d\n", __func__,
			 nodes_array_idx);
		pr_debug("np->name = %s\n", np->name);
		pr_debug("node->base = 0x%p\n", node->base);
		pr_debug("node->eprobe_hwirq = %d\n", node->eprobe_hwirq);
		pr_debug("node->eprobe_offset = 0x%x\n", node->eprobe_offset);
	}

	/* put the node into nodes_arry */
	noc_nodes_array[nodes_array_idx] = node;

	nodes_array_idx++;

	/* FIXME: handle the other irq */

	return 0;

err_property:
	kfree(node->name);
	iounmap(node->base);
err_iomap:
	kfree(node);
err:
	return ret;
}

void register_irqdata(void)
{
	struct noc_node *node = NULL;
	unsigned int i = 0;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}

		if (node->eprobe_hwirq >= NOC_MAX_IRQ_NR) {
			pr_err("[%s]: node->eprobe_hwirq(%d) is out of range(%d)!\n",
			     __func__, node->eprobe_hwirq,
			     NOC_MAX_IRQ_NR);
			continue;
		}
		if ((node->hwirq_type >= NOC_ERR_PROBE_IRQ)
		    && (node->hwirq_type <= NOC_TRANS_PROBE_IRQ)) {
			noc_irqdata[node->eprobe_hwirq].type = node->hwirq_type;
			noc_irqdata[node->eprobe_hwirq].node = node;

			if (NOC_TRANS_PROBE_IRQ == node->hwirq_type)
				init_transcation_info(node);
			else if (NOC_PACKET_PROBE_IRQ == node->hwirq_type)
				init_packet_info(node);
		} else {
			pr_err("[%s]: the node type error!!!\n", __func__);
		}
	}
}

void register_noc_nodes(void)
{
	struct device_node *np;

	for_each_compatible_node(np, NULL, "hisilicon,noc-node") {
		register_noc_node(np);
	}

	/* register_irqdata */
	register_irqdata();

}

static void unregister_noc_nodes(void)
{
	struct noc_node *node = NULL;
	int i = 0;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}

		if (noc_property_dt.error_enable) {
			if (NOC_ERR_PROBE_IRQ == node->hwirq_type) {
				disable_err_probe(node->base +
						  node->eprobe_offset);
			} else if (NOC_TRANS_PROBE_IRQ == node->hwirq_type) {
				disable_transcation_probe(node->base +
							  node->eprobe_offset);
			} else if (NOC_PACKET_PROBE_IRQ == node->hwirq_type) {
				disable_packet_probe(node->base +
						     node->eprobe_offset);
			} else {
				pr_err("[%s]: the node type error!!!\n",
				       __func__);
			}
		}

		iounmap(node->base);

		kfree(node);
	}

	nodes_array_idx = 0;
}

void __iomem *get_errprobe_base(const char *name)
{
	struct noc_node *node = NULL;
	int i = 0;

	if (!name)
		return NULL;
	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}

		if (!strncmp(name, node->name, 256))
			return node->base + node->eprobe_offset;
	}

	pr_warn("[%s]  cannot get node base name = %s\n",
		__func__, name);
	return NULL;
}
EXPORT_SYMBOL(get_errprobe_base);

/* return node index,
	error: return -1. */
int get_bus_id_by_base(const void __iomem *base)
{
	struct noc_node *node = NULL;
	int i = 0;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}
		if ((node->base + node->eprobe_offset) == base)
			return node->bus_id;
	}
	pr_warn("[%s]  cannot get bus ID\n", __func__);
	return -1;
}

struct noc_node *get_probe_node(const char *name)
{
	struct noc_node *node = NULL;
	int i = 0;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}

		if (!strncmp(name, node->name, 256))
			return node;
	}

	pr_warn("[%s] cannot get node base name = %s\n",
		__func__, name);
	return NULL;
}
EXPORT_SYMBOL(get_probe_node);

void noc_get_bus_nod_info(void **node_array_pptr, unsigned int *idx_ptr)
{
	*node_array_pptr = &noc_nodes_array;
	*idx_ptr = nodes_array_idx;

	pr_err("[%s]: nodes_array addr: %llx.\n", __func__,
		(unsigned long long)&noc_nodes_array);
}

void enable_errprobe(struct device *dev)
{
	struct noc_node *node = NULL;
	unsigned int i;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}
		if (is_noc_err_node_available(node)) {
			if (1 == noc_property_dt.noc_debug)
				pr_err("Start to enable error probe for bus %s.\n",
				     node->name);

			enable_err_probe(node->base + node->eprobe_offset);
		} else {
			if (1 == noc_property_dt.noc_debug)
				pr_err("Noc %s is powerdown, cannot enable\n",
				       node->name);
		}
	}
}

void disable_errprobe(struct device *dev)
{
	struct noc_node *node = NULL;
	unsigned int i = 0;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}

		if (is_noc_err_node_available(node)) {
			disable_err_probe(
				node->base + node->eprobe_offset);
		}
	}
}

void enable_noc_transcation_probe(struct device *dev)
{
	struct noc_node *node = NULL;
	unsigned int i = 0;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}
		if (is_noc_transcation_node_available(node)) {
			if (1 == noc_property_dt.noc_debug)
				pr_err("Start to enable transaction probe for bus %s.\n",
				     node->name);

			enable_transcation_probe(node,
					node->base + node->eprobe_offset);
		}
	}
}

void disable_noc_transcation_probe(struct device *dev)
{
	struct noc_node *node = NULL;
	unsigned int i = 0;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}
		if (is_noc_transcation_node_available(node))
			disable_transcation_probe(
					node->base + node->eprobe_offset);
	}
}

void enable_noc_packet_probe(struct device *dev)
{
	struct noc_node *node = NULL;
	unsigned int i = 0;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}

		if (is_noc_packet_node_available(node)) {
			if (1 == noc_property_dt.noc_debug)
				pr_err("Start to enable packet probe for bus %s.\n",
				     node->name);

			enable_packet_probe(node,
					    node->base + node->eprobe_offset);
		}
	}
}

void disable_noc_packet_probe(struct device *dev)
{
	struct noc_node *node = NULL;
	unsigned int i = 0;

	for (i = 0; i < nodes_array_idx; i++) {
		GET_NODE_FROM_ARRAY(node, i);
		if (!node) {
			pr_err("[%s]: nodes_array index %d not found.\n",
			       __func__, i);
			continue;
		}
		if (is_noc_packet_node_available(node))
			disable_packet_probe(node->base + node->eprobe_offset);
	}
}

static int hisi_noc_suspend(struct device *dev)
{
	pr_err("%s+\n", __func__);
	if (noc_property_dt.error_enable) {
		if (noc_property_dt.transcation_enable)
			disable_noc_transcation_probe(dev);
		if (noc_property_dt.packet_enable)
			disable_noc_packet_probe(dev);
	}

	pr_err("%s-\n", __func__);
	return 0;
}

static int hisi_noc_resume(struct device *dev)
{
	pr_err("%s+\n", __func__);
	if (noc_property_dt.error_enable) {
		enable_errprobe(dev);

		if (noc_property_dt.transcation_enable)
			enable_noc_transcation_probe(dev);
		if (noc_property_dt.packet_enable)
			enable_noc_packet_probe(dev);
	}
	pr_err("%s-\n", __func__);
	return 0;
}

static SIMPLE_DEV_PM_OPS(noc_pm_ops, hisi_noc_suspend, hisi_noc_resume);

static void hisi_noc_get_property(struct device_node *np)
{
	const char *dts_str = NULL;
	unsigned int dts_u32_value = 0;
	unsigned int dts_u32_array[NOC_ACPU_INIT_FLOW_ARRY_SIZE] = {0, 0};
	unsigned long long dts_u64_value = 0;

	/* Get platform_id Form DTS. */
	if (0 == of_property_read_u32(np, "platform_id", &dts_u32_value))
		noc_property_dt.platform_id = dts_u32_value;

	/* Read PCTRL IRQ mask Form DTS. */
	if (0 == of_property_read_u64(np, "pctrl-irq-mask", &dts_u64_value))
		noc_property_dt.pctrl_irq_mask = dts_u64_value;

	/* Read PCTRL PERI STAT0 Offset Form DTS. */
	if (0 == of_property_read_u32(np, "pctrl-peri-stat0-offset",
					&dts_u32_value))
		noc_property_dt.pctrl_peri_stat0_off = dts_u32_value;

	/* Read PCTRL PERI STAT3 Offset Form DTS. */
	if (0 == of_property_read_u32(np, "pctrl-peri-stat3-offset",
					&dts_u32_value))
		noc_property_dt.pctrl_peri_stat3_off = dts_u32_value;

	/* Get fama_mask Form DTS. */
	if (0 == of_property_read_u32(np, "fama-mask", &dts_u32_value))
		noc_property_dt.noc_fama_mask = dts_u32_value;

	/* Get smp_stop_cpu_bit_mask Form DTS. */
	if (0 == of_property_read_u64(np, "smp_stop_cpu_bit_mask",
					&dts_u64_value))
		noc_property_dt.smp_stop_cpu_bit_mask = dts_u64_value;

	/* Get stop_cpu_bus_node_name Form DTS. */
	if (0 == of_property_read_string(np, "stop_cpu_bus_node_name",
					&dts_str))
		noc_property_dt.stop_cpu_bus_node_name = dts_str;

	/* Get noc_acpu_init_flow_array Form DTS. */
	if (0 == of_property_read_u32_array(np,
					"noc_acpu_init_flow_array",
					dts_u32_array,
					NOC_ACPU_INIT_FLOW_ARRY_SIZE))
		memcpy(&noc_property_dt.apcu_init_flow_array,
				dts_u32_array, sizeof(dts_u32_array));

	/* Get Fuction Enable Flag Form DTS. */
	noc_property_dt.faulten_default_enable = of_property_read_bool(np,
													"faulten_default_enable");
	noc_property_dt.packet_enable          = of_property_read_bool(np,
													"packet_enable");
	noc_property_dt.transcation_enable     = of_property_read_bool(np,
													"transcation_enable");
	noc_property_dt.error_enable           = of_property_read_bool(np,
													"error_enable");
	noc_property_dt.noc_debug              = of_property_read_bool(np,
													"noc_debug");
	noc_property_dt.noc_timeout_enable     = of_property_read_bool(np,
													"noc_timeout_enable");
	noc_property_dt.noc_fama_enable        = of_property_read_bool(np,
													"fama_enable");

    /* Debug Print. */
	if (noc_property_dt.noc_debug) {
		pr_err("NoC Property:\n");
		pr_err("platform_id = %d\n", noc_property_dt.platform_id);
		pr_err("pctrl_irq_mask = 0x%lx\n",
			(unsigned long)noc_property_dt.pctrl_irq_mask);
		pr_err("pctrl_peri_stat0_off = 0x%x\n",
			noc_property_dt.pctrl_peri_stat0_off);
		pr_err("pctrl_peri_stat3_off = 0x%x\n",
			noc_property_dt.pctrl_peri_stat3_off);
		pr_err("smp_stop_cpu_bit_mask = 0x%lx\n",
			(unsigned long)noc_property_dt.smp_stop_cpu_bit_mask);
		pr_err("noc_fama_mask  = 0x%x\n",
			noc_property_dt.noc_fama_mask);
		pr_err("faulten_default_enable = %d\n",
			noc_property_dt.faulten_default_enable);
		pr_err("packet_enable = %d\n", noc_property_dt.packet_enable);
		pr_err("error_enable = %d\n", noc_property_dt.error_enable);
		pr_err("noc_debug = %d\n", noc_property_dt.noc_debug);
		pr_err("noc_timeout_enable = %d\n",
			noc_property_dt.noc_timeout_enable);
		pr_err("noc_fama_enable = %d\n",
			noc_property_dt.noc_fama_enable);
		pr_err("stop_cpu_bus_node_name = %s\n",
			noc_property_dt.stop_cpu_bus_node_name);
		pr_err("apcu_init_flow_array[0,1] = 0x%x,0x%x\n",
			noc_property_dt.apcu_init_flow_array[0],
			noc_property_dt.apcu_init_flow_array[1]);
	}
}

static void noc_set_platform_info(void)
{
    /* buses information select among platforms*/
	noc_set_buses_info();

	return;
}

static int hisi_noc_part_probe(struct platform_device *pdev,
				      struct device_node *np)
{
	struct hisi_noc_device *noc_dev = NULL;
	struct device *dev = NULL;

	if (NULL == pdev || NULL == np) {
		pr_err("[%s]: pdev or np is NULL!!!\n", __func__);
		return -1;
	}

	noc_dev = platform_get_drvdata(pdev);
	if (NULL == noc_dev) {
		pr_err("[%s]: noc_dev  is NULL!!!\n", __func__);
		return -1;
	}

	dev = &pdev->dev;

	np = of_find_node_by_name(NULL, "pctrl");
	BUG_ON(!np);

	noc_dev->pctrl_base = of_iomap(np, 0);
	BUG_ON(!noc_dev->pctrl_base);

	np = of_find_node_by_name(NULL, "sctrl");
	BUG_ON(!np);

	noc_dev->sctrl_base = of_iomap(np, 0);	/* get sctrl base from dts */
	if (!noc_dev->sctrl_base) {
		BUG_ON(1);
		goto err_sctrl;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pmctrl");

	noc_dev->pmctrl_base = of_iomap(np, 0);
	if (!noc_dev->pmctrl_base) {
		BUG_ON(1);
		goto err_pmctrl;
	}
	/* Read PERI_CRG base addr */
	np = of_find_compatible_node(NULL, NULL, "hisilicon,clk-crgctrl");

	noc_dev->pcrgctrl_base = of_iomap(np, 0);
	if (!noc_dev->pcrgctrl_base) {
		if (1 == noc_property_dt.noc_debug)
			pr_err("[%s]: crg ctrl not available\n", __func__);
		BUG_ON(1);
		goto err_crgctrl;
	}

	/* get the pwrctrl_reg offset  */
	np = dev->of_node;

	noc_dev->pwrctrl_reg =
	    SOC_PMCTRL_NOC_POWER_IDLEACK_ADDR(noc_dev->pmctrl_base);

    /* Record NoC Prorerty Pointer. */
	noc_dev->noc_property = &noc_property_dt;

	return 0;

err_crgctrl:
	if (noc_dev->pmctrl_base)
		iounmap(noc_dev->pmctrl_base);

err_pmctrl:
	if (noc_dev->sctrl_base)
		iounmap(noc_dev->sctrl_base);

err_sctrl:
	if (noc_dev->pctrl_base)
		iounmap(noc_dev->pctrl_base);

	return -ENODEV;
}

static int hisi_noc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hisi_noc_device *noc_dev;
	struct device_node *np;
	const struct of_device_id *match;
	int ret = 0;

	pr_info("HISI NOC PROBE START!!!\n");

	g_this_pdev = pdev;	/* Get platform device pointer */

	/* to check which type of regulator this is */
	match = of_match_device(hisi_noc_match, dev);
	if (NULL == match) {
		pr_err("hisi_noc_probe: mismatch of hisi noc driver\n\r");
		BUG_ON(1);
		goto err;
	}

	/* Platform information should be executed as early as
	   the moment getting g_config_hisi_noc_data */
	noc_set_platform_info();

	/* get the pwrctrl_reg offset  */
	np = dev->of_node;

	hisi_noc_get_property(np);

	noc_dev = devm_kzalloc(&pdev->dev,
					sizeof(struct hisi_noc_device),
					GFP_KERNEL);
	if (!noc_dev) {
		dev_err(dev, "cannot get memory\n");
		ret = -ENOMEM;
		goto err;
	}

	platform_set_drvdata(pdev, noc_dev);

	ret = hisi_noc_part_probe(pdev, np);
	if (ret != 0) {
		pr_err("hisi_noc_part_probe err\n");
		goto err;
	}

	/* process each noc node */
	register_noc_nodes();

	/* enable err probe if Soc don't support faultem auto enable.*/
	if (noc_property_dt.error_enable &&
		!noc_property_dt.faulten_default_enable)
		enable_errprobe(dev);

    /* enable noc transcation probe */
	if (noc_property_dt.transcation_enable)
		enable_noc_transcation_probe(dev);

    /* enable noc packet probe */
	if (noc_property_dt.packet_enable)
		enable_noc_packet_probe(dev);

	ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot find IRQ\n");
		goto err;
	}
	noc_dev->irq = ret;
	if (1 == noc_property_dt.noc_debug)
		pr_err("[%s] noc_irq = %d\n", __func__, noc_dev->irq);

	ret = devm_request_irq(&pdev->dev, noc_dev->irq,
			     hisi_noc_irq_handler,
			     IRQF_TRIGGER_HIGH | IRQF_DISABLED, "hisi_noc",
			     noc_dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "request_irq fail!\n");
		goto err;
	}

	if (noc_property_dt.noc_timeout_enable) {
		ret = platform_get_irq(pdev, 1);
		if (ret < 0) {
			dev_err(&pdev->dev, "cannot find noc timeout IRQ\n");
			goto err;
		}

		noc_dev->timeout_irq = ret;
		pr_debug("[%s] timeout_irq = %d\n", __func__,
			 noc_dev->timeout_irq);

		ret = devm_request_irq(&pdev->dev, noc_dev->timeout_irq,
				     hisi_noc_timeout_irq_handler,
				     IRQF_TRIGGER_HIGH | IRQF_DISABLED,
				     "hisi_noc_timeout_irq", noc_dev);
		if (ret < 0) {
			dev_err(&pdev->dev, "request timeout irq fail!\n");
			goto err;
		}
	}

	if (-1 == noc_dump_init())
		pr_err("[%s] noc_dump_init failed!\n", __func__);

#ifdef CONFIG_DEBUG_FS
	/* Creat debug file */
	if (0 != noc_dbg_creat_node())
		pr_err("[%s] dbg node creation failed!\n", __func__);
#endif
	noc_err_probe_init();
	g_noc_init = 1;
	return 0;

err:
	return ret;
}

static int hisi_noc_remove(struct platform_device *pdev)
{
	struct hisi_noc_device *noc_dev = platform_get_drvdata(pdev);

	unregister_noc_nodes();
	if (noc_dev != NULL) {
		free_irq(noc_dev->irq, noc_dev);
		iounmap(noc_dev->pctrl_base);
	}

	return 0;
}

MODULE_DEVICE_TABLE(of, hisi_noc_match);

static struct platform_driver hisi_noc_driver = {
	.probe = hisi_noc_probe,
	.remove = hisi_noc_remove,
	.driver = {
		   .name = MODULE_NAME,
		   .owner = THIS_MODULE,
#ifdef CONFIG_PM_SLEEP
		   .pm = &noc_pm_ops,
#endif
		   .of_match_table = of_match_ptr(hisi_noc_match),
		   },
};

static int __init hisi_noc_init(void)
{
	return platform_driver_register(&hisi_noc_driver);
}

static void __exit hisi_noc_exit(void)
{
	platform_driver_unregister(&hisi_noc_driver);
}

late_initcall(hisi_noc_init);
module_exit(hisi_noc_exit);
