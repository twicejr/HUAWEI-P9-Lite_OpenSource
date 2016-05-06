/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef LINUX_MMC_CQ_HCI_H
#define LINUX_MMC_CQ_HCI_H
#include <linux/mmc/core.h>

/* registers */
#define CQVER		0x00
#define CQCAP		0x04

#define CQCFG		0x08
#define CQ_DCMD		0x00001000
#define CQ_TASK_DESC_SZ 0x00000100
#define CQ_ENABLE	0x00000001

#define CQCTL		0x0C
#define CLEAR_ALL_TASKS 0x00000100
#define HALT		0x00000001


#define CQIS		0x10
#define CQISTE		0x14
#define CQISGE		0x18
#define CQIC		0x1C

#define CQTDLBA		0x20
#define CQTDLBAU	0x24
#define CQTDBR		0x28
#define CQTCN		0x2C

#define CQDQS		0x30
#define CQDPT		0x34
#define CQTCLR		0x38

#define CQSSC1		0x40
#define CQSSC2		0x44
#define CQCRDCT		0x48

#define CQRMEM		0x50
#define CQTERRI		0x54
#define CQCRI		0x58
#define CQCRA		0x5C

#define CQIC_ENABLE	(1 << 31)
#define CQIC_RESET	(1 << 16)
#define CQIC_ICCTHWEN	(1 << 15)
#define CQIC_ICCTH(x)	((x & 0x1F) << 8)
#define CQIC_ICTOVALWEN (1 << 7)
#define CQIC_ICTOVAL(x) (x & 0x7F)

#define CQIS_HAC	(1 << 0)
#define CQIS_TCC	(1 << 1)
#define CQIS_RED	(1 << 2)
#define CQIS_TCL	(1 << 3)
#define CQIS_TERR	(1 << 4)

#define CQ_INT_EN	(0x3 << 14)
//#define CQ_INT_ALL	0xF
#define CQ_INT_ALL	0x1F
#define CQIC_DEFAULT_ICCTH 31
#define CQIC_DEFAULT_ICTOVAL 1

/* attribute fields */
#define VALID(x)	((x & 1) << 0)
#define END(x)		((x & 1) << 1)
#define INT(x)		((x & 1) << 2)
#define ACT(x)		((x & 0x7) << 3)

/* data command task descriptor fields */
#define FORCED_PROG(x)	((x & 1) << 6)
#define CONTEXT(x)	((x & 0xF) << 7)
#define DATA_TAG(x)	((x & 1) << 11)
#define DATA_DIR(x)	((x & 1) << 12)
#define PRIORITY(x)	((x & 1) << 13)
#define QBAR(x)		((x & 1) << 14)
#define REL_WRITE(x)	((x & 1) << 15)
#define BLK_COUNT(x)	((x & 0xFFFF) << 16)
#define BLK_ADDR(x)	((x & 0xFFFFFFFF) << 32)

/* direct command task descriptor fields */
#define CMD_INDEX(x)	((x & 0x3F) << 16)
#define CMD_TIMING(x)	((x & 1) << 22)
#define RESP_TYPE(x)	((x & 0x3) << 23)

/* transfer descriptor fields */
#define DAT_LENGTH(x)	((x & 0xFFFF) << 16)
#define DAT_ADDR_LO(x)	((x & 0xFFFFFFFF) << 32)
#define DAT_ADDR_HI(x)	((x & 0xFFFFFFFF) << 0)

#define CQTERRI_DAT_ERR		(1 << 31)
#define CQTERRI_DAT_TASK(x)	((x >> 24) & 0x1F)
#define CQTERRI_DAT_CMD(x)	((x >> 16) & 0x3F)
#define CQTERRI_RES_ERR		(1 << 15)
#define CQTERRI_RES_TASK(x)	((x >> 8) & 0x1F)
#define CQTERRI_RES_CMD(x)	(x & 0x3F)

/* response type*/
#define RES_TYPE_NO_RES  (0)
#define RES_TYPE_R145    (2)
#define RES_TYPE_R1B     (3)

struct cmdq_host {
	const struct cmdq_host_ops *ops;
	void __iomem *mmio;
	struct mmc_host *mmc;

	/* 64 bit DMA */
	bool dma64;
	int num_slots;

	u32 dcmd_slot;
	u32 caps;
#define CMDQ_TASK_DESC_SZ_128 0x1

	u32 quirks;
#define CMDQ_QUIRK_SHORT_TXFR_DESC_SZ 0x1
#define CMDQ_QUIRK_NO_DCMD	0x2

	bool enabled;
	bool halted;
	bool init_done;

	u64 *desc_base;

	/* total descriptor size */
	u8 slot_sz;

	u32 reg;

	u32 cqcfg;
	u32 rca;

	/* 64/128 bit depends on CQCFG */
	u8 task_desc_len;

	/* 64 bit on 32-bit arch, 128 bit on 64-bit */
	u8 link_desc_len;

	u64 *trans_desc_base;
	/* same length as transfer descriptor */
	u8 trans_desc_len;

	/*set the trans descriptor length for 64bit dma, use the "char" as the unit rather than "u64
	 *it is only used in linked trans descriptor
	 */
	u8 dma64_trans_desc_len;

	dma_addr_t desc_dma_base;
	dma_addr_t trans_desc_dma_base;

	struct completion halt_comp;
	struct completion clear_comp;
	spinlock_t cmdq_lock;
	struct mmc_request **mrq_slot;
	bool check_busy;
	bool err_handle;
	bool fix_qbr;
	u32 cmd13_err_count;
#define CMDQ_CMD13_RETRY_TIMES		0
	struct workqueue_struct* wq_resend;
	struct work_struct      work_resend;
	struct timer_list *timer;      /* Timer for timeouts */
	unsigned long     *timeout;    /* timeout value for timer unit:jiffies*/

	void *private;
};

struct cmdq_host_ops {
	void (*reset)(struct mmc_host *mmc, u8 mask);
	void (*set_tranfer_params)(struct mmc_host *mmc);
	void (*set_data_timeout)(struct mmc_host *mmc, u32 val);
	u32 (*clear_set_irqs)(struct mmc_host *mmc, u32 clear, u32 set);
	int (*discard_task)(struct mmc_host *mmc, u32 tag, bool entire);
	int (*tuning_move)(struct mmc_host *mmc, int is_move_strobe, int flag);
	void (*clean_irqs)(struct mmc_host *mmc, u32 clean);
	void (*dump_vendor_regs)(struct mmc_host *mmc);
	int (*card_busy)(struct mmc_host *mmc);
	void (*write_l)(struct cmdq_host *host, u32 val, int reg);
	u32 (*read_l)(struct cmdq_host *host, int reg);
};

static inline void cmdq_writel(struct cmdq_host *host, u32 val, int reg)
{
	if (unlikely(host->ops->write_l))
		host->ops->write_l(host, val, reg);
	else
		writel(val, host->mmio + reg);
}

static inline u32 cmdq_readl(struct cmdq_host *host, int reg)
{
	if (unlikely(host->ops->read_l))
		return host->ops->read_l(host, reg);
	else
		return readl(host->mmio + reg);
}

extern irqreturn_t cmdq_irq(struct mmc_host *mmc, u32 intmask);
extern int cmdq_init(struct cmdq_host *cq_host, struct mmc_host *mmc,
		     bool dma64);
extern struct cmdq_host *cmdq_pltfm_init(struct platform_device *pdev,
					void __iomem * cmda_ioaddr);
#endif
