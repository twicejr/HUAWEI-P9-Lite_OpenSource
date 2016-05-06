/*
  * trustedcore ipc driver, hisi_ipc.c
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <asm/psci.h>
#include "hisi_ipc.h"
#define REG_MBX_SOURCE_OFFSET(m)		(((m) << 6))
#define REG_MBX_DSET_OFFSET(m)		(((m) << 6) + 0x04)
#define REG_MBX_DCLEAR_OFFSET(m)		(((m) << 6) + 0x08)
#define REG_MBX_DSTATUS_OFFSET(m)	(((m) << 6) + 0x0C)
#define REG_MBX_MODE_OFFSET(m)		(((m) << 6) + 0x10)
#define REG_MBX_IMASK_OFFSET(m)		(((m) << 6) + 0x14)
#define REG_MBX_ICLR_OFFSET(m)		(((m) << 6) + 0x18)
#define REG_MBX_SEND_OFFSET(m)		(((m) << 6) + 0x1C)
#define REG_MBX_DATA_OFFSET(m, d)		(((m) << 6) + 0x20 + ((d) * 4))
#define REG_CPU_IMST_OFFSET(m)		(((m) << 3))
#define REG_IPC_LOCK_OFFSET			(0xA00)
#define REG_IPC_ACK_BIT_SHIFT			(1 << 7)
#define IPC_UNLOCK_VALUE				(0x1ACCE551)
/*********************************************************
 *bit[31:24]:0~AP
 *bit[23:16]:0x1~A15, 0x2~A7
 *bit[15:8]:0~ON, 1~OFF
 *bit[7:0]:0x3 cpu power mode
 *********************************************************/
#define IPC_CMD_TYPE(src_obj, cluster_obj, is_off, mode) \
	((src_obj << 24) | (((cluster_obj) + 1) << 16) | (is_off << 8) |(mode))

/*********************************************************
 *bit[15:8]:0~no idle, 1~idle
 *bit[7:0]:cpux
 *********************************************************/

#define IPC_CMD_PARA(is_idle, cpu) \
	((is_idle << 8) | (cpu))

#define REG_IPC_BASE	REG_IPC_SEC_BASE

enum src_id {
	SRC_IDLE = 0,
	SRC_A15 = 1 << 0,
	SRC_A7 = 1 << 1,
	SRC_IOM3 = 1 << 2,
	SRC_LPM3 = 1 << 3
};

/*lpm3's mailboxs are 13~17*/
enum lpm3_mbox_id {
	LPM3_MBX0 = 13,
	LPM3_MBX1,
	LPM3_MBX2,
	LPM3_MBX3,
	LPM3_MBX4,
};

void __iomem *ipc_base_addr;

static inline void hisi_ipc_set_source(enum src_id source, enum lpm3_mbox_id mbox)
{
	int status = 0;

	do{
		writel(source, ipc_base_addr + REG_MBX_SOURCE_OFFSET(mbox));
		status = readl(ipc_base_addr + REG_MBX_SOURCE_OFFSET(mbox));
	} while (status != source);
}

static inline void hisi_ipc_clear_ack(enum src_id source, enum lpm3_mbox_id mbox)
{
	unsigned int int_status = 0;

	do {
		int_status = readl(ipc_base_addr + REG_MBX_MODE_OFFSET(mbox)) & 0xF0;
	} while (int_status != REG_IPC_ACK_BIT_SHIFT);

	writel(source, ipc_base_addr + REG_MBX_ICLR_OFFSET(mbox));
}

static void hisi_ipc_send_cmd_with_ack(enum src_id source,
		enum lpm3_mbox_id mbox, unsigned int cmdtype, unsigned int cmdpara)
{
	int status = 0;
	enum lpm3_mbox_id mask_cpu = 0;

	/*wait for mailbox idle*/
	do{
		status = readl(ipc_base_addr + REG_MBX_SOURCE_OFFSET(mbox));
	} while (status != 0);

	/*use this mailbox*/
	writel(source, ipc_base_addr + REG_MBX_SOURCE_OFFSET(mbox));
	/*auto answer*/
	writel(0x1, ipc_base_addr + REG_MBX_MODE_OFFSET(mbox));
	/*mask the other cpus*/
	mask_cpu = (source == SRC_A15) ? SRC_A7 : SRC_A15;
	writel(SRC_IOM3 | mask_cpu,\
			ipc_base_addr + REG_MBX_IMASK_OFFSET(mbox));
	/*set data*/
	writel(cmdtype, ipc_base_addr + REG_MBX_DATA_OFFSET(mbox, 0));
	writel(cmdpara, ipc_base_addr + REG_MBX_DATA_OFFSET(mbox, 1));
	/*send cmd*/
	writel(source, ipc_base_addr + REG_MBX_SEND_OFFSET(mbox));
	/*wait ack and clear*/
	hisi_ipc_clear_ack(source, mbox);

	/*release mailbox*/
	writel(source, ipc_base_addr + REG_MBX_SOURCE_OFFSET(mbox));
}

void hisi_ipc_pm_on_off(unsigned int core, unsigned int cluster, enum pm_mode mode)
{
	unsigned int cmdtype = 0;
	unsigned int cmdpara = 0;
	enum src_id source = 0;
	enum lpm3_mbox_id mailbox = LPM3_MBX0;

	cmdtype = IPC_CMD_TYPE(0, cluster, mode, 0x3);
	cmdpara = IPC_CMD_PARA(0, core);
	source = cluster ? SRC_A7: SRC_A15;
	mailbox = LPM3_MBX0 + core;
	hisi_ipc_send_cmd_with_ack(source, mailbox, cmdtype, cmdpara);
}

void hisi_ipc_pm_suspend(unsigned int core, unsigned int cluster, unsigned int affinity_level)
{
	unsigned int cmdtype = 0;
	unsigned int cmdpara = 0;
	enum src_id source = 0;
	enum lpm3_mbox_id mailbox = LPM3_MBX0;

	cmdtype = IPC_CMD_TYPE(0, cluster, 0x1, 0x3 + affinity_level);
	cmdpara = IPC_CMD_PARA(0, core);
	source = cluster ? SRC_A7: SRC_A15;
	mailbox = LPM3_MBX0 + core;
	hisi_ipc_send_cmd_with_ack(source, mailbox, cmdtype, cmdpara);
}

static int __init hisi_ipc_init(void)
{
	int ret = 0;
	enum lpm3_mbox_id  i = LPM3_MBX0;
	struct device_node *np = NULL;

	np = of_find_compatible_node(NULL, NULL, "hisilicon, sec_ipc");
	if (!np) {
		pr_err("HISI IPC:No compatible node found.\n");
		return -ENODEV;
	}
	ipc_base_addr = of_iomap(np, 0);

	writel(IPC_UNLOCK_VALUE, ipc_base_addr + REG_IPC_LOCK_OFFSET);
	for (i = LPM3_MBX0; i <= LPM3_MBX4; i++) {
		writel(1, ipc_base_addr + REG_MBX_MODE_OFFSET(i));
		writel(SRC_IOM3 | SRC_A15 | SRC_A7,\
			ipc_base_addr + REG_MBX_IMASK_OFFSET(i));
		writel(SRC_A7, ipc_base_addr + REG_MBX_ICLR_OFFSET(i));
	}

	return ret;
}

early_initcall(hisi_ipc_init);
MODULE_DESCRIPTION("Hisilicon ipc driver");
MODULE_AUTHOR("zhanjun 00183814");
MODULE_LICENSE("GPL");
