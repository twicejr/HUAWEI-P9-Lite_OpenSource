/*
* NoC. (NoC Mntn Module.)
*
* Copyright (c) 2016 Huawei Technologies CO., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#ifndef __HISI_NOC_H
#define __HISI_NOC_H

#include <soc_acpu_baseaddr_interface.h>

#define MODULE_NAME	"HISI_NOC"
#define MAX_NOC_NODE_NAME_LEN	20
#define GET_NODE_FROM_ARRAY(node, idx) do {\
	node = noc_nodes_array[idx];\
} while (0)


#define NOC_MAX_IRQ_NR     64
#define MAX_NOC_NODES_NR   33
#define HISI_NOC_CLOCK_MAX	2

#define PCTRL_NOC_IRQ_STAT0  SOC_PCTRL_PERI_STAT0_ADDR(0)
#define PCTRL_NOC_IRQ_STAT3   SOC_PCTRL_PERI_STAT3_ADDR(0)
#define PCTRL_PERI_STAT2   SOC_PCTRL_PERI_STAT2_ADDR(0)
#define PCTRL_PERI_CTRL19   SOC_PCTRL_PERI_CTRL19_ADDR(0)
#define SCTRL_SCPERSTATUS6  SOC_SCTRL_SCPERSTATUS6_ADDR(0)

#define PMCTRL_PERI_INT_STAT0_OFFSET   SOC_PMCTRL_PERI_INT0_STAT_ADDR(0)
#define PMCTRL_PERI_INT_MASK_OFFSET   SOC_PMCTRL_PERI_INT0_MASK_ADDR(0)
#define PMCTRL_NOC_POWER_IDLEREQ    SOC_PMCTRL_NOC_POWER_IDLEREQ_ADDR(0)
#define PMCTRL_NOC_POWER_IDLEACK    SOC_PMCTRL_NOC_POWER_IDLEACK_ADDR(0)
#define PMCTRL_NOC_POWER_IDLE    SOC_PMCTRL_NOC_POWER_IDLE_ADDR(0)

#define NOC_PTYPE_UART 1
#define NOC_PTYPE_PSTORE 0

#define NOC_ACPU_INIT_FLOW_ARRY_SIZE 2

enum NOC_IRQ_TPYE {
	NOC_ERR_PROBE_IRQ,
	NOC_PACKET_PROBE_IRQ,
	NOC_TRANS_PROBE_IRQ,
};

struct hisi_noc_irqd {
	enum NOC_IRQ_TPYE type;
	struct noc_node *node;
};

struct hisi_noc_property {
	unsigned long long pctrl_irq_mask;
	unsigned long long smp_stop_cpu_bit_mask;
	const char *stop_cpu_bus_node_name;
	unsigned int apcu_init_flow_array[NOC_ACPU_INIT_FLOW_ARRY_SIZE];
	unsigned int pctrl_peri_stat0_off;
	unsigned int pctrl_peri_stat3_off;
	bool faulten_default_enable;
	unsigned int platform_id;
	bool packet_enable;
	bool transcation_enable;
	bool error_enable;
	bool noc_debug;
	bool noc_timeout_enable;
	bool noc_fama_enable;
	unsigned int noc_fama_mask;
	void __iomem *bus_node_base;
};

struct hisi_noc_device {
	struct device *dev;
	void __iomem *sys_base;
	void __iomem *media_base;
	void __iomem *pctrl_base;
	void __iomem *pmctrl_base;
	void __iomem *sctrl_base;
	void __iomem *pwrctrl_reg;
	void __iomem *pcrgctrl_base;
	unsigned int irq;
	unsigned int timeout_irq;
	struct hisi_noc_property *noc_property;
};

struct packet_configration {
	unsigned int statperiod;
	unsigned int statalarmmax;

	unsigned int packet_counters_0_src;
	unsigned int packet_counters_1_src;
	unsigned int packet_counters_2_src;
	unsigned int packet_counters_3_src;

	unsigned int packet_counters_0_alarmmode;
	unsigned int packet_counters_1_alarmmode;
	unsigned int packet_counters_2_alarmmode;
	unsigned int packet_counters_3_alarmmode;

	unsigned int packet_filterlut;
	unsigned int packet_f0_routeidbase;
	unsigned int packet_f0_routeidmask;
	unsigned int packet_f0_addrbase;
	unsigned int packet_f0_windowsize;
	unsigned int packet_f0_securitymask;
	unsigned int packet_f0_opcode;
	unsigned int packet_f0_status;
	unsigned int packet_f0_length;
	unsigned int packet_f0_urgency;
	unsigned int packet_f0_usermask;

	unsigned int packet_f1_routeidbase;
	unsigned int packet_f1_routeidmask;
	unsigned int packet_f1_addrbase;
	unsigned int packet_f1_windowsize;
	unsigned int packet_f1_securitymask;
	unsigned int packet_f1_opcode;
	unsigned int packet_f1_status;
	unsigned int packet_f1_length;
	unsigned int packet_f1_urgency;
	unsigned int packet_f1_usermask;

};
struct transcation_configration {
	unsigned int statperiod;
	unsigned int statalarmmax;

	unsigned int trans_f_mode;
	unsigned int trans_f_addrbase_low;
	unsigned int trans_f_addrwindowsize;
	unsigned int trans_f_opcode;
	unsigned int trans_f_usermask;
	unsigned int trans_f_securitymask;

	unsigned int trans_p_mode;
	unsigned int trans_p_thresholds_0_0;
	unsigned int trans_p_thresholds_0_1;
	unsigned int trans_p_thresholds_0_2;
	unsigned int trans_p_thresholds_0_3;

	unsigned int trans_m_counters_0_src;
	unsigned int trans_m_counters_1_src;
	unsigned int trans_m_counters_2_src;
	unsigned int trans_m_counters_3_src;

	unsigned int trans_m_counters_0_alarmmode;
	unsigned int trans_m_counters_1_alarmmode;
	unsigned int trans_m_counters_2_alarmmode;
	unsigned int trans_m_counters_3_alarmmode;
};

/* Clock information for Noc */
struct noc_clk {
	/* offset of clock status register in PERI_CRG */
	unsigned int offset;
	/* bit to indicate clock status */
	unsigned int mask_bit;
};

struct noc_node {
	char *name;
	void __iomem *base;
	unsigned int bus_id;
	unsigned int interrupt_num;
	unsigned int pwrack_bit;
	unsigned int eprobe_offset;
	bool eprobe_autoenable;
	int eprobe_hwirq;
	int hwirq_type;
	struct transcation_configration tran_cfg;
	struct packet_configration packet_cfg;
	/* Currently 2 clock sources for each noc node */
	struct noc_clk crg_clk[HISI_NOC_CLOCK_MAX];
};

void __iomem *get_errprobe_base(const char *name);
struct noc_node *get_probe_node(const char *name);
void noc_get_bus_nod_info(void **node_array_pptr, unsigned int *idx_ptr);

u64 noc_find_addr_from_routeid(unsigned int idx, int initflow, int targetflow,
			       int targetsubrange);

int get_bus_id_by_base(const void __iomem *base);
int is_noc_node_available(struct noc_node *node);
struct platform_device *noc_get_pt_pdev(void);
unsigned int is_noc_init(void);
/*
Function: noc_get_irq_status
Description: noc part, get irq status
input: void __iomem * pctrl_base: pctrl virtual base address
output: none
return: irq status
*/
unsigned long long noc_get_irq_status(void __iomem *pctrl_base);
void enable_noc_transcation_probe(struct device *dev);
void disable_noc_transcation_probe(struct device *dev);
void enable_noc_packet_probe(struct device *dev);
void disable_noc_packet_probe(struct device *dev);
void noc_record_log_pstorememory(void __iomem *base, int ptype);

extern void mntn_print_to_ramconsole(const char *fmt, ...);
extern void noc_err_probe_hanlder(void __iomem *base, struct noc_node *node);
#endif
