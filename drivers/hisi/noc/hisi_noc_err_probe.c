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
#include <linux/notifier.h>
#include <linux/jiffies.h>
#include <linux/nmi.h>
#include <linux/kthread.h>
#include "hisi_noc_err_probe.h"
#include "hisi_noc.h"
#include "hisi_noc_info.h"
#include <linux/hisi/util.h>
#include <linux/hisi/reset.h>
#ifdef CONFIG_HISI_BB
#include <platform_ap/rdr_hisi_platform.h>
#include <linux/hisi/rdr_pub.h>
#endif
#include <soc_cfg_sys_noc_bus_interface.h>
#include <soc_acpu_baseaddr_interface.h>
#include <soc_pmctrl_interface.h>
#include <soc_pctrl_interface.h>
#include <soc_sctrl_interface.h>

#define ERR_CODE_NR	7
static char *err_code[] = {
	"Slave:  returns Error response",
	"Master: access reserved memory space",
	"Master: send the illigel type burst to slave",
	"Master: access the powerdown area",
	"Master: Permission error",
	"Master: received Hide Error Response from Firewall",
	"Master: accessed slave timeout and returned Error reponse",
};

#define MAX_OPC_NR	10
static char *opc[] = {
	"RD:  INCR READ",
	"RDW: WRAP READ",
	"RDL: EXCLUSIVE READ",
	"RDX: LOCK READ",
	"WR:  INCR WRITE",
	"WDW: WRAP WRITE",
	"Reversed",
	"WRC: EXCLUSIVE WRITE",
	"PRE: FIXED BURST",
	"Abnormal"
};

static struct semaphore modemnoc_happen_sem;
static char str_out_of_range[] = { "out of range!" };
static struct noc_errorprobe_backup_info noc_info_backup = {0, 0, NULL};

/*modem的noc发生时的处理任务，主动调用rdr_system_error*/
int modemnoc_happen(void)
{
	pr_err("modemnoc_happen start\n");
	down(&modemnoc_happen_sem);
	pr_err("modemnoc_happen goto rdr_system_error\n");
#ifdef CONFIG_HISI_BB
	rdr_system_error(RDR_MODEM_NOC_MOD_ID, 0, 0);
#endif
	return 0;
}

/*输出base+0x14的值的含义*/
static void print_errlog0(unsigned int val)
{
	unsigned int idx;
	SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION *pt_log0 =
	    (SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION *) &val;

	pr_err("[ERR_LOG0 = 0x%x]:\n", val);

	idx = pt_log0->reg.errcode;

	if (idx < ERR_CODE_NR)
		pr_err("\t[err_code=%d] %s\n", idx, err_code[idx]);
	else
		pr_err("\t[err_code=%d] out of range!\n", idx);

	idx = pt_log0->reg.opc;
	if (idx < MAX_OPC_NR)
		pr_err("\t[opc=%d] %s\n", idx, opc[idx]);
	else
		pr_err("\t[opc=%d] out of range!\n", idx);
}

/*输出输出base+0x18的值的含义*/
u64 print_errlog1(unsigned int val, unsigned int idx, int *pinitflow)
{
	const struct noc_bus_info *noc_bus = 0;
	unsigned int shift = 0;

	int initflow;
	int targetflow;
	int targetsubrange;

	noc_bus = noc_get_bus_info(idx);
	if (NULL == noc_bus) {
		pr_err("[%s] noc_bus get error!\n", __func__);
		return -1;
	}

	pr_err("[ERR_LOG1 = 0x%x]\n", val);

	shift = ffs(noc_bus->initflow_mask) - 1;
	initflow = (val & (noc_bus->initflow_mask)) >> shift;
	if (initflow < noc_bus->initflow_array_size) {
		*pinitflow = initflow;
		noc_info_backup.init_flow = initflow;
		pr_err("\t[init_flow=%d]: %s\n", initflow,
		       noc_bus->initflow_array[initflow]);
	} else {
		*pinitflow = -1;
		pr_err("\t[init_flow=%d]: %s\n", initflow,
		       "index is out of range!");
	}

	shift = ffs(noc_bus->targetflow_mask) - 1;
	targetflow = (val & (noc_bus->targetflow_mask)) >> shift;
	if (targetflow < noc_bus->targetflow_array_size)
		pr_err("\t[target_flow=%d]: %s\n", targetflow,
		       noc_bus->targetflow_array[targetflow]);
	else
		pr_err("\t[target_flow=%d]: %s\n", targetflow,
		       "index is out of range!");

	shift = ffs(noc_bus->targ_subrange_mask) - 1;
	targetsubrange = (val & (noc_bus->targ_subrange_mask)) >> shift;
	pr_err("\t[target_subrange]: %d\n", targetsubrange);

	return noc_find_addr_from_routeid(idx, initflow, targetflow,
					  targetsubrange);

}

/*输出base+0x28的值的含义 ERRLOG5*/
void print_errlog5(unsigned int val, unsigned int idx, int initflow)
{
	struct noc_mid_info *noc_mid = noc_get_mid_info();
	char *mid_name = NULL;

	for (; (noc_mid != NULL) && (noc_mid->idx != 0xffffffff); noc_mid++) {
		if ((noc_mid->idx == idx) && (noc_mid->init_flow == initflow)
		    && (noc_mid->mid_val == (val & noc_mid->mask))) {
			mid_name = noc_mid->mid_name;
			break;
		}
	}

	if (mid_name != NULL)
		pr_err("[ERR_LOG5]: USER_SIGNAL = 0x%x (MID: %s )\n", val,
		       mid_name);
	else
		pr_err("[ERR_LOG5]: USER_SIGNAL = 0x%x\n", val);

	return;
}

/*Output Error log buffer, one-track code for both Hi6xxx and Hi3xxx */
static void print_errlog(void __iomem *base, unsigned int idx)
{
	unsigned int val, val_errlog3, val_errlog5;
	u64 base_addr;
	int initflow = -1;
	struct hisi_noc_device *noc_dev = NULL;
	unsigned int fama_offset;

	/* dump all the err_log register */
	val = readl_relaxed(base + ERR_PORBE_ERRLOG0_OFFSET);
	print_errlog0(val);

	val = readl_relaxed(base + ERR_PORBE_ERRLOG1_OFFSET);
	base_addr = print_errlog1(val, idx, &initflow);

	val_errlog5 = readl_relaxed(base + ERR_PORBE_ERRLOG5_OFFSET);

	noc_dev = platform_get_drvdata(noc_get_pt_pdev());

	if ((noc_dev != NULL) && (noc_dev->noc_property->noc_fama_enable))
		fama_offset = (val_errlog5 >> 6) & noc_dev->noc_property->noc_fama_mask;
	else
		fama_offset = 0;

	val_errlog3 = readl_relaxed(base + ERR_PORBE_ERRLOG3_OFFSET);
	pr_err("[ERR_LOG3]: ADDRESS_LOW = 0x%x,\n", val_errlog3);

	val = readl_relaxed(base + ERR_PORBE_ERRLOG4_OFFSET);
	pr_err("[ERR_LOG4]: ADDRESS_HIGH = 0x%x\n", val);

	pr_err("            adjusted ADDRESS = 0x%llx\n",
	       val_errlog3 + ((u64) val << 32) + base_addr +
	       ((u64) fama_offset << 34));

	print_errlog5(val_errlog5, idx, initflow);

	val = readl_relaxed(base + ERR_PORBE_ERRLOG7_OFFSET);
	pr_err("[ERR_LOG7]: SECURITY = %d (%s).\n", val,
	       val ? "non security mode" : "security mode");

}

void noc_err_get_msg_log0(uint *reg_val_buf, uint idx,
			  struct err_probe_msg *pt_err_msg)
{
	uint val_tmp;
	uint val;
	SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION *pt_log0 =
	    (SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION *) &val;

	val = reg_val_buf[0];

	val_tmp = pt_log0->reg.errcode;

	if (val_tmp < ERR_CODE_NR) {
		pt_err_msg->err_code.val = val_tmp;
		pt_err_msg->err_code.pt_str = err_code[val_tmp];
	} else
		pt_err_msg->err_code.pt_str = str_out_of_range;

	val_tmp = pt_log0->reg.opc;

	if (val_tmp < MAX_OPC_NR) {
		pt_err_msg->opc.val = val_tmp;
		pt_err_msg->opc.pt_str = opc[val_tmp];
	} else {
		pt_err_msg->opc.pt_str = str_out_of_range;
	}
}

void noc_err_get_msg_log1(uint *reg_val_buf, uint idx,
			  struct err_probe_msg *pt_err_msg)
{
	const struct noc_bus_info *noc_bus = 0;
	unsigned int shift = 0;
	uint val;
	int initflow;
	int targetflow;

	noc_bus = noc_get_bus_info(idx);
	if (NULL == noc_bus) {
		pr_err("[%s] noc_bus get error!\n", __func__);
		return;
	}
	val = reg_val_buf[1];
	shift = ffs(noc_bus->initflow_mask) - 1;
	initflow = (val & (noc_bus->initflow_mask)) >> shift;
	pt_err_msg->init_flow.val = initflow;
	if (initflow < noc_bus->initflow_array_size)
		pt_err_msg->init_flow.pt_str =
		    noc_bus->initflow_array[initflow];
	else
		pt_err_msg->init_flow.pt_str = str_out_of_range;

	shift = ffs(noc_bus->targetflow_mask) - 1;
	targetflow = (val & (noc_bus->targetflow_mask)) >> shift;
	pt_err_msg->target_flow.val = targetflow;
	if (targetflow < noc_bus->targetflow_array_size)
		pt_err_msg->target_flow.pt_str =
		    noc_bus->targetflow_array[targetflow];
	else
		pt_err_msg->target_flow.pt_str = str_out_of_range;

	shift = ffs(noc_bus->targ_subrange_mask) - 1;
	pt_err_msg->targetsubrange =
	    (val & (noc_bus->targ_subrange_mask)) >> shift;

	pt_err_msg->base_addr = noc_find_addr_from_routeid(idx, initflow,
							   targetflow, pt_err_msg->targetsubrange);
}

void noc_err_get_msg_log5(uint *reg_val_buf, uint idx,
			  struct err_probe_msg *pt_err_msg)
{
	struct noc_mid_info *noc_mid = noc_get_mid_info();
	int mid_val;
	char *mid_name = NULL;

	pt_err_msg->user_signal = reg_val_buf[5];

	mid_val = pt_err_msg->user_signal;
	for (; (noc_mid != NULL) && (noc_mid->idx != 0xffffffff); noc_mid++) {
		if ((noc_mid->idx == idx)
		    && (noc_mid->init_flow == pt_err_msg->init_flow.val)
		    && (noc_mid->mid_val == (mid_val & noc_mid->mask))) {
			mid_name = noc_mid->mid_name;
			break;
		}
	}

	pt_err_msg->mid_name = mid_name;
}

void noc_err_get_msg(uint *reg_val_buf, uint idx,
		     struct err_probe_msg *pt_err_msg)
{
	/* ERR LOG 0 */
	noc_err_get_msg_log0(reg_val_buf, idx, pt_err_msg);
	/* ERR LOG 1 */
	noc_err_get_msg_log1(reg_val_buf, idx, pt_err_msg);

	/* ERR LOG 3,4 */
	pt_err_msg->addr_low = reg_val_buf[3];
	pt_err_msg->addr_high = reg_val_buf[4];

	/* ERR LOG 5 */
	noc_err_get_msg_log5(reg_val_buf, idx, pt_err_msg);

	/* ERR LOG 7 */
	pt_err_msg->SECURITY = reg_val_buf[7];
}

void noc_err_prt_msg(struct err_probe_msg *pt_err_msg)
{
	if (NULL == pt_err_msg) {
		pr_err("[%s]:arg is NULL in\n", __func__);
		return;
	}

	/* ERR LOG 0 */
	pr_err("[err_code=%d] %s\n", pt_err_msg->err_code.val,
	       pt_err_msg->err_code.pt_str);
	pr_err("[opc=%d] %s\n", pt_err_msg->opc.val, pt_err_msg->opc.pt_str);

	/* ERR LOG 1 */
	pr_err("[init_flow=%d]: %s\n", pt_err_msg->init_flow.val,
	       pt_err_msg->init_flow.pt_str);
	pr_err("[target_flow=%d]: %s\n", pt_err_msg->target_flow.val,
	       pt_err_msg->target_flow.pt_str);
	pr_err("[target_subrange]: %d\n", pt_err_msg->targetsubrange);

	/* ERR LOG 3,4 */
	pr_err("ADDRESS_LOW = 0x%llx  (0x%x)\n",
	       (u64) (pt_err_msg->addr_low + pt_err_msg->base_addr),
	       pt_err_msg->addr_low);
	pr_err("ADDRESS_HIGH = 0x%x\n", pt_err_msg->addr_high);

	/* ERR LOG 5 */
	pr_err("[USER_SIGNAL = 0x%x MID: %s\n", pt_err_msg->user_signal,
	       pt_err_msg->mid_name);

	/* ERR LOG 7 */
	pr_err("SECURITY = %d\n", pt_err_msg->SECURITY);
}

void noc_err_probe_prt(void __iomem *base, uint idx)
{
	uint reg_val[10];
	uint i;
	struct err_probe_msg err_msg;

	memset(&err_msg, 0, sizeof(struct err_probe_msg));

	for (i = 0; i < 8; i++) {
		reg_val[i] =
		    readl_relaxed(base + ERR_PORBE_ERRLOG0_OFFSET + 4 * i);
	}
	noc_err_get_msg(reg_val, idx, &err_msg);
	noc_err_prt_msg(&err_msg);
}

/*******************************************************************************
Function:       is_modemnoc_happen
Description:    check initflow and nodename. if this is modemnoc,
				firstly save log, thensystem reset.
Input:          NA
Output:         NA
Return:         1:this is modemnoc;0:this is not modemnoc
********************************************************************************/
static int is_modemnoc_happen(void)
{
	int i, ret;
	struct noc_busid_initflow *modemnoc_initflow = NULL;
	char **modemnoc_nodename = NULL;

	ret = 0;
	hisi_get_modemnoc_initflow_nodename(&modemnoc_initflow, &modemnoc_nodename);

	if (NULL == modemnoc_initflow || NULL == modemnoc_nodename) {
		pr_err("hisi_get_modemnoc_initflow_nodename fail\n");
		goto out;
	}

	for (i = 0; modemnoc_nodename[i] != NULL; i++) {
		if (0 == strncmp(noc_info_backup.nodename,
			modemnoc_nodename[i],
			strlen(modemnoc_nodename[i]))) {
			pr_err("nodename is modemnoc, then up modemnoc_happen_sem\n");
			ret = 1;
		}
	}

	for (i = 0; modemnoc_initflow[i].bus_id != ARRAY_END_FLAG; i++) {
		if (noc_info_backup.bus_id == modemnoc_initflow[i].bus_id &&
			noc_info_backup.init_flow == modemnoc_initflow[i].init_flow) {
			pr_err("initflow is modemnoc, then up modemnoc_happen_sem\n");
			ret = 1;
		}
	}

out:
	return ret;
}

void noc_err_probe_hanlder(void __iomem *base, struct noc_node *node)
{
	noc_info_backup.bus_id = node->bus_id;
	noc_info_backup.nodename = node->name;

	/* output error log buffer */
	print_errlog(base, node->bus_id);

	/*将noc的寄存器信息打印出来 */
	noc_record_log_pstorememory(base, NOC_PTYPE_UART);

	/* clear interrupt */
	writel_relaxed(ERR_PROBE_CLEAR_BIT, base + ERR_PORBE_ERRCLR_OFFSET);
#ifdef CONFIG_HISI_BB
	if (check_himntn(HIMNTN_NOC_ERROR_REBOOT)) {
		pr_err("noc happen,node->name is [%s], bus_id is [%d], initflow is [%d]\n",
			noc_info_backup.nodename,
			noc_info_backup.bus_id,
			noc_info_backup.init_flow);
		if (is_modemnoc_happen())
			up(&modemnoc_happen_sem);
		else
			rdr_syserr_process_for_ap(MODID_AP_S_NOC, 0, 0);
	}
#endif
}

/***************************************************************************
Function:       noc_err_probe_init
Description:    error probe仅执行一次的初始化，SR流程不会再次调用。
		起modem noc时的处理任务和信号量的初始化。
Input:          NA
Output:         NA
Return:         NA
****************************************************************************/
void noc_err_probe_init(void)
{
	sema_init(&modemnoc_happen_sem, 0);

	/* 起任务，等待modem的noc发生时运行 */
	if (!kthread_run(modemnoc_happen, NULL, "modemnoc_happen"))
		pr_err("create thread modemnoc_happen faild.\n");
}

void enable_err_probe(void __iomem *base)
{
	unsigned int val;
	int bus_id = 0;
	unsigned int noc_bus_info_num = 0;

	val = readl_relaxed(base + ERR_PORBE_ERRVLD_OFFSET);
	if (val & ERR_PORBE_ERRVLD_BIT) {

		pr_err("NoC ErrProbe happened before enabling interrupt\n");
		pr_err("NoC Error Probe:\n");

		bus_id = get_bus_id_by_base(base);

		noc_bus_info_num = hisi_noc_get_bus_info_num();

		if (bus_id >= 0 && bus_id < noc_bus_info_num) {
			print_errlog(base, bus_id);
		} else {
			val = readl_relaxed(base + ERR_PORBE_ERRLOG0_OFFSET);
			print_errlog0(val);

			val = readl_relaxed(base + ERR_PORBE_ERRLOG1_OFFSET);
			pr_err("[ERR_LOG1 = 0x%x]\n", val);

			val = readl_relaxed(base + ERR_PORBE_ERRLOG3_OFFSET);
			pr_err("[ERR_LOG3] = 0x%x\n", val);

			val = readl_relaxed(base + ERR_PORBE_ERRLOG4_OFFSET);
			pr_err("[ERR_LOG4] = 0x%x\n", val);

			val = readl_relaxed(base + ERR_PORBE_ERRLOG5_OFFSET);
			pr_err("[ERR_LOG5] = 0x%x\n", val);

			val = readl_relaxed(base + ERR_PORBE_ERRLOG7_OFFSET);
			pr_err("[ERR_LOG7] = %d\n", val);
		}
		/* clear errvld */
		writel_relaxed(ERR_PROBE_CLEAR_BIT,
			       base + ERR_PORBE_ERRCLR_OFFSET);
		wmb();
	}

	/* enable err probe intrrupt */
	writel_relaxed(ERR_PORBE_ENABLE_BIT, base + ERR_PORBE_FAULTEN_OFFSET);
}

void disable_err_probe(void __iomem *base)
{
	writel_relaxed(~ERR_PORBE_ENABLE_BIT, base + ERR_PORBE_FAULTEN_OFFSET);
}

/* Need check if noc init is finished,
	as this interface would be called by other module */
void enable_err_probe_by_name(const char *name)
{
	void __iomem *base;

	if (!name) {
		pr_err("%s Name is NULL\n", __func__);
		return;
	}

	if (!is_noc_init()) {
		pr_err("%s: NOC not init\n", __func__);
		return;
	}

	base = get_errprobe_base(name);
	if (base == NULL) {
		pr_err("%s cannot get the node!\n", __func__);
		return;
	}

	enable_err_probe(base);
}
EXPORT_SYMBOL(enable_err_probe_by_name);

/* Need check if noc init is finished,
	as this interface would be called by other module */
void disable_err_probe_by_name(char *name)
{
	void __iomem *base;
	if (!name) {
		pr_err("%s Name is NULL\n", __func__);
		return;
	}

	if (!is_noc_init()) {
		pr_err("%s: NOC not init\n", __func__);
		return;
	}

	base = get_errprobe_base(name);
	if (base == NULL) {
		pr_err("%s cannot get the node!\n", __func__);
		return;
	}

	disable_err_probe(base);
}
EXPORT_SYMBOL(disable_err_probe_by_name);
