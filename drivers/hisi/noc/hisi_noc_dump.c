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
#include <linux/hisi/reset.h>
#include <linux/clk.h>

#include "hisi_noc.h"
#include "hisi_noc_err_probe.h"
#include "hisi_noc_packet.h"
#include "hisi_noc_info.h"
#include "hisi_noc_transcation.h"
#include "hisi_noc_dump.h"
#ifdef CONFIG_HISI_BB
#include "platform_ap/rdr_hisi_platform.h"
#endif
#include <soc_cfg_sys_noc_bus_interface.h>
#include <soc_acpu_baseaddr_interface.h>
#include <soc_pmctrl_interface.h>
#include <soc_pctrl_interface.h>
#include <soc_sctrl_interface.h>

/* Gloable Stucture For Recording Hisi NoC Dump Info.*/
static struct hisi_noc_dump_info g_noc_dump_info;

static const uint noc_dump_errprobe_offset[NOC_DUMP_ERRPRO_OFF_NUM] = {
	ERR_PORBE_FAULTEN_OFFSET,
	ERR_PORBE_ERRVLD_OFFSET,
	ERR_PORBE_ERRLOG0_OFFSET,
	ERR_PORBE_ERRLOG1_OFFSET,
	ERR_PORBE_ERRLOG3_OFFSET,
	ERR_PORBE_ERRLOG5_OFFSET,
	ERR_PORBE_ERRLOG7_OFFSET,
};

static int noc_dump_err_log_parse(char *kn_buf, int *pt_buf_seek,
				  struct err_probe_msg *pt_err_msg)
{
	NOC_L_D_PRT("[err_code=%d] %s\n", pt_err_msg->err_code.val,
		    pt_err_msg->err_code.pt_str);
	NOC_L_D_PRT("[opc=%d] %s\n", pt_err_msg->opc.val,
		    pt_err_msg->opc.pt_str);
	/* ERR LOG 1 */
	NOC_L_D_PRT("[init_flow=%d]: %s\n", pt_err_msg->init_flow.val,
		    pt_err_msg->init_flow.pt_str);
	NOC_L_D_PRT("[target_flow=%d]: %s\n", pt_err_msg->target_flow.val,
		    pt_err_msg->target_flow.pt_str);
	NOC_L_D_PRT("[target_subrange]: %d\n", pt_err_msg->targetsubrange);
	/* ERR LOG 3,4 */
	NOC_L_D_PRT("ADDRESS_LOW = 0x%llx  (0x%x)\n",
		    pt_err_msg->addr_low + pt_err_msg->base_addr,
		    pt_err_msg->addr_low);
	NOC_L_D_PRT("ADDRESS_HIGH = 0x%x\n", pt_err_msg->addr_high);
	/* ERR LOG 5 */
	NOC_L_D_PRT("[USER_SIGNAL = 0x%x MID: %s\n", pt_err_msg->user_signal,
		    pt_err_msg->mid_name);
	/* ERR LOG 7 */
	NOC_L_D_PRT("SECURITY = %d\n", pt_err_msg->SECURITY);
	return 0;
}

static int noc_dump_err_probe(char *kn_buf, int *pt_buf_seek)
{
	struct noc_node *node = NULL;
	int j, k;
	void __iomem *iobase = NULL;
	struct err_probe_msg err_msg;
	struct err_probe_msg *pt_err_msg = &err_msg;
	uint reg_val_buf[10];
	unsigned long long pending;
	uint faulten, errvld;

	NOC_L_D_PRT("***ErrorProbe status***\n");

	pending = noc_get_irq_status(g_noc_dump_info.noc_device_ptr->pctrl_base);

	for (j = 0; j < g_noc_dump_info.noc_bus_node_info.noc_node_idx; j++) {
		node = g_noc_dump_info.noc_bus_node_info.noc_node_pptr[j];

		if (NULL == node)
			break;

		/* Only Dump Error Probe Type NoC Bus Node. */
		if (NOC_ERR_PROBE_IRQ != node->hwirq_type)
			continue;

		if (!is_noc_node_available(node)) {
			pr_err("[%s]: this node is power down, cannot access.\n",
			     node->name);
			continue;
		}
		iobase = node->base + node->eprobe_offset;
		faulten = readl_relaxed(iobase + ERR_PORBE_FAULTEN_OFFSET);
		errvld = readl_relaxed(iobase + ERR_PORBE_ERRVLD_OFFSET);
		if (!(pending & BIT(node->eprobe_hwirq))
		    && !(errvld & ERR_PORBE_ERRVLD_BIT)) {
			pr_err("[%s]:no error probe happens on this node!\n",
			       node->name);
			continue;
		}
		NOC_L_D_PRT("ERR_PORBE_BUS is [%s]\n",
			    g_noc_dump_info.noc_bus_node_info.noc_node_pptr[j]->name);
		NOC_L_D_PRT("FAULTEN_OFFSET = 0x%x\n", faulten);
		NOC_L_D_PRT("ERR_VLD = 0x%x\n", errvld);

		for (k = 0; k < 8; k++) {
			reg_val_buf[k] = readl_relaxed(iobase +
							ERR_PORBE_ERRLOG0_OFFSET + 4 * k);
			NOC_L_D_PRT("ERRLOG %d = 0x%08x\n", k, reg_val_buf[k]);
		}
		/* Parse error log and dump */
		noc_err_get_msg(reg_val_buf, node->bus_id, pt_err_msg);
		noc_dump_err_log_parse(kn_buf, pt_buf_seek, pt_err_msg);
	}
	return 0;
}

static int noc_dump_prt(char *kn_buf, int *pt_buf_seek)
{
	uint reg_value, reg_val1;
/* NoPendingTrans×´Ì¬ */
	NOC_L_D_PRT("***NoPendingTrans status***\n");
	reg_value = readl_relaxed(g_noc_dump_info.noc_device_ptr->pctrl_base + PCTRL_PERI_STAT2);
	NOC_L_D_PRT("PCTRL_PERI_STAT2 = 0x%x\n", reg_value);
	reg_value = readl_relaxed(g_noc_dump_info.noc_device_ptr->sctrl_base + SCTRL_SCPERSTATUS6);
	NOC_L_D_PRT("SCTRL_SCPERSTATUS6 = 0x%x\n", reg_value);
/* µÍ¹¦ºÄÎÕÊÖ×´Ì¬ */
	NOC_L_D_PRT("***LowPower HandInHand***\n");
	reg_value =
	    readl_relaxed(g_noc_dump_info.noc_device_ptr->pmctrl_base + PMCTRL_NOC_POWER_IDLEREQ);
	NOC_L_D_PRT("PMCTRL_NOC_POWER_IDLEREQ = 0x%x\n", reg_value);
	reg_value =
	    readl_relaxed(g_noc_dump_info.noc_device_ptr->pmctrl_base + PMCTRL_NOC_POWER_IDLEACK);
	NOC_L_D_PRT("PMCTRL_NOC_POWER_IDLEACK = 0x%x\n", reg_value);
	reg_value = readl_relaxed(g_noc_dump_info.noc_device_ptr->pmctrl_base + PMCTRL_NOC_POWER_IDLE);
	NOC_L_D_PRT("PMCTRL_NOC_POWER_IDLE = 0x%x\n", reg_value);
/* Timeout ×´Ì¬ */
	NOC_L_D_PRT("***Timeout status***\n");
	reg_value =
	    readl_relaxed(g_noc_dump_info.noc_device_ptr->pmctrl_base + PMCTRL_PERI_INT_STAT0_OFFSET);
	NOC_L_D_PRT("PMCTRL_PERI_INT0_STAT = 0x%x\n", reg_value);
	reg_val1 = readl_relaxed(g_noc_dump_info.noc_device_ptr->sctrl_base + SCTRL_SCPERSTATUS6);
	NOC_L_D_PRT("SCTRL_SCPERSTATUS6 = 0x%x\n", reg_val1);
/* ErrorProbe */
	if (!IS_NOC_TMOUT_HAPPEN(reg_value, reg_val1)) {
		/* Timeout happened , do not dump error probe register */
		noc_dump_err_probe(kn_buf, pt_buf_seek);
	}

/* µØÖ·½»Ö¯Á£¶ÈÅäÖÃ */
	NOC_L_D_PRT("***Address interleaving status***\n");
	reg_value = readl_relaxed(g_noc_dump_info.noc_device_ptr->pctrl_base + PCTRL_PERI_CTRL19);
	NOC_L_D_PRT("PCTRL_PERI_CTRL19 = 0x%x\n", reg_value);
	return 0;
}

static int noc_dump(void *dump_addr, unsigned int size)
{
	struct noc_node *node = NULL;
	int i, j;
	struct noc_dump_data *pt_dump = kzalloc(sizeof(*pt_dump), GFP_KERNEL);
	uint *ptr;
	void __iomem *iobase;
	uint ret_size = 0;
    unsigned int node_idx = 0;

	pr_info("noc_dump:addr=0x%llx,size=[0x%x/0x%x]",
		(unsigned long long)dump_addr, (unsigned int)sizeof(*pt_dump),
		size);

	if (pt_dump == NULL) {
		pr_err("noc_dump: pt_dump malloc error\n");
		goto malloc_free;
	}

	for (i = 0; i < (NOC_DUMP_SYNC_LEN - 1); i++) {
		/* sync head 1 */
		pt_dump->sync[i] = NOC_DUMP_SYNC_HEAD1;
	}
	/* sync head 2 */
	pt_dump->sync[i] = ((NOC_DUMP_SYNC_HEAD2 & 0xFFFFFF00) |
				(g_noc_dump_info.noc_device_ptr->noc_property->platform_id & 0xFF));

	/* Dump NoC Related Register into bbox.bin. */
	pt_dump->NopendingTrans.uPERI_STAT2   = readl_relaxed(
			SOC_PCTRL_PERI_STAT2_ADDR(g_noc_dump_info.noc_device_ptr->pctrl_base));
	pt_dump->NopendingTrans.uSCPERSTATUS6 = readl_relaxed(
			SOC_SCTRL_SCPERSTATUS6_ADDR(g_noc_dump_info.noc_device_ptr->sctrl_base));
	pt_dump->LmHand.uNOC_POWER_IDLEREQ    = readl_relaxed(
			SOC_PMCTRL_NOC_POWER_IDLEREQ_ADDR(g_noc_dump_info.noc_device_ptr->pmctrl_base));
	pt_dump->LmHand.uNOC_POWER_IDLEACK    = readl_relaxed(
			SOC_PMCTRL_NOC_POWER_IDLEACK_ADDR(g_noc_dump_info.noc_device_ptr->pmctrl_base));
	pt_dump->LmHand.uNOC_POWER_IDLE       = readl_relaxed(
			SOC_PMCTRL_NOC_POWER_IDLE_ADDR(g_noc_dump_info.noc_device_ptr->pmctrl_base));
	pt_dump->TimeoutSts.uPERI_INT0_STAT   = readl_relaxed(
			SOC_PMCTRL_PERI_INT0_STAT_ADDR(g_noc_dump_info.noc_device_ptr->pmctrl_base));
	pt_dump->TimeoutSts.uSCPERSTATUS6     = readl_relaxed(
			SOC_SCTRL_SCPERSTATUS6_ADDR(g_noc_dump_info.noc_device_ptr->sctrl_base));

	if (IS_NOC_TMOUT_HAPPEN(pt_dump->TimeoutSts.uPERI_INT0_STAT,
	     pt_dump->TimeoutSts.uSCPERSTATUS6)) {
		/* Timeout happened , do not dump error probe register */
		goto ERR_PROBE_DUMP_END;
	}

	/* ERR PROBE Register dumping start */
	for (i = 0; i < g_noc_dump_info.noc_bus_node_info.noc_node_idx; i++) {
		node = g_noc_dump_info.noc_bus_node_info.noc_node_pptr[i];
		if (NULL == node) {
			pr_err("NoC Bus Node Pointer = NULL .\n");
			break;
		}

		/* Only Dump Error Probe Type NoC Bus Node. */
		if (NOC_ERR_PROBE_IRQ != node->hwirq_type) {
			pr_err("[%s]:Not NoC Error Probe Bus Node.\n", node->name);
			continue;
		}

		if (!is_noc_node_available(node)) {
			pr_err("[%s]:NoC Bus Node Not Availble.\n", node->name);
			continue;
		}

		ptr = (u32 *)&pt_dump->ErrorProbe[node_idx];

		/* Dump Node Name into bbox.bin. */
		if (strlen(node->name) >= NOC_DUMP_NOC_NODE_NAME_LEN) {
			pr_err("Error: NoC Bus Node Name Too Long : [%d].\n",
				(unsigned int)strlen(node->name));
			strncpy((char *)ptr, (char *)node->name,
				(NOC_DUMP_NOC_NODE_NAME_LEN-1));
		} else {
			strncpy((char *)ptr, (char *)node->name, strlen(node->name));
		}
		ptr += NOC_DUMP_NOC_NODE_NAME_LEN / sizeof(uint);

		/* Enable Flag. */
		*ptr++ = NOC_DUMP_NODE_EN_F;
		iobase = node->base + node->eprobe_offset;
		for (j = 0; j < ARRAY_SIZE(noc_dump_errprobe_offset); j++)
			*ptr++ = readl_relaxed(iobase + noc_dump_errprobe_offset[j]);

		node_idx++;
	}

	/* Dump Bus Node Number Index. */
	pt_dump->NoCBusNodeIdx = node_idx;

ERR_PROBE_DUMP_END:
	pt_dump->AddrInter.uPERI_CTRL19 =
	    readl_relaxed(g_noc_dump_info.noc_device_ptr->pctrl_base + PCTRL_PERI_CTRL19);

	for (i = 0; i < NOC_DUMP_NOC_LEN; i++)
		pt_dump->tail[i] = NOC_DUMP_TAIL_NR;	/* tail */

	if (sizeof(*pt_dump) >= size) {
		pr_err("NoC Dump Overflow. Dump Size[%lx], Alloc Size[%d].\n",
			sizeof(*pt_dump), size);
		ret_size = size;
	} else {
		ret_size = sizeof(*pt_dump);
	}

	/* COPY data to RDR module */
	memcpy(dump_addr, pt_dump, ret_size);

	/* Check buffer data */
	ptr = (uint *) pt_dump;
	for (i = 0; i < sizeof(*pt_dump) / 16; i++) {
		pr_info("(%03d~%03d)%08x %08x %08x %08x\n", 4 * i, 4 * i + 3,
			ptr[4 * i], ptr[4 * i + 1], ptr[4 * i + 2],
			ptr[4 * i + 3]);
	}

malloc_free:
	/* kmalloc free */
	kfree(pt_dump);
	pt_dump = NULL;
	noc_dump_prt(NULL, NULL);
	return ret_size;
}


/*
Function: noc_dump_init
Description: noc dump function registers to black-box module, so noc dump can be processed before reset
input: none
output: none
return: 0->success
*/
int noc_dump_init(void)
{
	int ret = -1;

	/* Get Hisi NoC Device Stucture Pointer. */
	g_noc_dump_info.noc_device_ptr = platform_get_drvdata(noc_get_pt_pdev());

	/* Get Hisi NoC Bus Node Stucture Pointer and Number. */
	noc_get_bus_nod_info((void **)&g_noc_dump_info.noc_bus_node_info.noc_node_pptr,
				&g_noc_dump_info.noc_bus_node_info.noc_node_idx);

	if ((NULL == g_noc_dump_info.noc_bus_node_info.noc_node_pptr) ||
		(0 == g_noc_dump_info.noc_bus_node_info.noc_node_idx) ||
		(NULL == g_noc_dump_info.noc_device_ptr)) {
			pr_err("[%s] No Bus Node Registered. ", __func__);

		return ret;
	}

	/* Debug Print. */
	if (g_noc_dump_info.noc_device_ptr->noc_property->noc_debug) {
		pr_err("[%s] NoC Bus Dump Info:\n", __func__);
		pr_err("noc_device_ptr=%lx\n",
				(unsigned long)g_noc_dump_info.noc_device_ptr);
		pr_err("noc_node_ptr=%lx\n",
				(unsigned long)g_noc_dump_info.noc_bus_node_info.noc_node_pptr);
		pr_err("noc_node_idx=%d\n",
				g_noc_dump_info.noc_bus_node_info.noc_node_idx);
	}

#ifdef CONFIG_HISI_BB
	/* function "register_module_dump_mem_func" can only be used when CONFIG_HISI_BB */
	ret = register_module_dump_mem_func(noc_dump, "NOC", MODU_NOC);
#endif

	return ret;
}

/*END OF FILE*/
