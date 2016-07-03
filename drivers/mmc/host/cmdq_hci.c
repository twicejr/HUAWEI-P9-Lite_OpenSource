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

#include <linux/delay.h>
#include <linux/highmem.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include <linux/scatterlist.h>
#include <linux/leds.h>
#include <linux/platform_device.h>

#include <linux/mmc/mmc.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/slot-gpio.h>
#include <linux/mmc/cmdq_hci.h>
#include <linux/pm_runtime.h>
#include "sdhci.h"

/* 1 sec FIXME: optimize it */
#define HALT_TIMEOUT_MS 1000
#define CLEAR_TIMEOUT_MS 1000

#define CMDQ_TASK_TIMEOUT_MS 60000

#define DRV_NAME "cmdq-host"

#define CMDQ_FIX_CHECKBUSY
/*fix the soc bug that the qbr task can't be cleared*/
#define CMDQ_FIX_CLEAR_QBRTASK

#define CMDQ_DATA_DIR(cmdq_req) (((cmdq_req)->cmdq_req_flags & DIR) ? 1 : 0)

#ifdef CONFIG_HUAWEI_EMMC_DSM
extern void sdhci_cmdq_dsm_set_host_status(struct sdhci_host *host, u32 error_bits);
extern void sdhci_cmdq_dsm_work(struct cmdq_host *cq_host, bool dsm);
#endif

static void cmdq_dumpregs(struct cmdq_host *cq_host)
{
	struct mmc_host *mmc = cq_host->mmc;

	pr_info(DRV_NAME ": ========== REGISTER DUMP (%s)==========\n", mmc_hostname(mmc));

	pr_info(DRV_NAME ": Version: 0x%08x | Caps:  0x%08x\n",
			cmdq_readl(cq_host, CQVER),
			cmdq_readl(cq_host, CQCAP));
	pr_info(DRV_NAME ": Queing config: 0x%08x | Queue Ctrl:  0x%08x\n",
			cmdq_readl(cq_host, CQCFG),
			cmdq_readl(cq_host, CQCTL));
	pr_info(DRV_NAME ": Int stat: 0x%08x | Int enab:  0x%08x\n",
			cmdq_readl(cq_host, CQIS),
			cmdq_readl(cq_host, CQISTE));
	pr_info(DRV_NAME ": Int sig: 0x%08x | Int Coal:  0x%08x\n",
			cmdq_readl(cq_host, CQISGE),
			cmdq_readl(cq_host, CQIC));
	pr_info(DRV_NAME ": TDL base: 0x%08x | TDL up32:  0x%08x\n",
			cmdq_readl(cq_host, CQTDLBA),
			cmdq_readl(cq_host, CQTDLBAU));
	pr_info(DRV_NAME ": Doorbell: 0x%08x | Comp Notif:  0x%08x\n",
			cmdq_readl(cq_host, CQTDBR),
			cmdq_readl(cq_host, CQTCN));
	pr_info(DRV_NAME ": Dev queue: 0x%08x | Dev Pend:  0x%08x\n",
			cmdq_readl(cq_host, CQDQS),
			cmdq_readl(cq_host, CQDPT));
	pr_info(DRV_NAME ": Task clr: 0x%08x | Send stat 1:  0x%08x\n",
			cmdq_readl(cq_host, CQTCLR),
			cmdq_readl(cq_host, CQSSC1));
	pr_info(DRV_NAME ": Send stat 2: 0x%08x | DCMD resp:  0x%08x\n",
			cmdq_readl(cq_host, CQSSC2),
			cmdq_readl(cq_host, CQCRDCT));
	pr_info(DRV_NAME ": Resp err mask: 0x%08x | Task err:  0x%08x\n",
			cmdq_readl(cq_host, CQRMEM),
			cmdq_readl(cq_host, CQTERRI));
	pr_info(DRV_NAME ": Resp idx 0x%08x | Resp arg:  0x%08x\n",
			cmdq_readl(cq_host, CQCRI),
			cmdq_readl(cq_host, CQCRA));
	pr_info(DRV_NAME ": ===========================================\n");

	if (cq_host->ops->dump_vendor_regs)
		cq_host->ops->dump_vendor_regs(mmc);
}

#ifdef CONFIG_PM
static int cmdq_runtime_pm_get(struct mmc_host *mmc)
{
	return pm_runtime_get_sync(mmc->parent);
}

static int cmdq_runtime_pm_put(struct mmc_host *mmc)
{
	pm_runtime_mark_last_busy(mmc->parent);
	return pm_runtime_put_autosuspend(mmc->parent);
}
#else
static int cmdq_runtime_pm_get(struct mmc_host *mmc)
{
	return 0;
}

static int cmdq_runtime_pm_put(struct mmc_host *mmc)
{
	return 0;
}
#endif

static inline u64 *get_desc(struct cmdq_host *cq_host, u8 tag)
{
	return cq_host->desc_base + (tag * cq_host->slot_sz);
}

static inline u64 *get_link_desc(struct cmdq_host *cq_host, u8 tag)
{
	u64 *desc = get_desc(cq_host, tag);

	return desc + cq_host->task_desc_len;
}

static inline dma_addr_t get_trans_desc_dma(struct cmdq_host *cq_host, u8 tag)
{

	u8 mul = sizeof(u64)/sizeof(dma_addr_t);
	return (dma_addr_t)((char *)cq_host->trans_desc_dma_base +
		(mul * cq_host->trans_desc_len * cq_host->mmc->max_segs * tag *
		 sizeof(*cq_host->trans_desc_base)));

}

static inline u64 *get_trans_desc(struct cmdq_host *cq_host, u8 tag)
{
	u8 mul = sizeof(u64) / sizeof(dma_addr_t);


	return (u64 *)((char *)cq_host->trans_desc_base +
		(mul * cq_host->trans_desc_len * cq_host->mmc->max_segs * tag *
		 sizeof(*cq_host->trans_desc_base)));

}

static void setup_trans_desc(struct cmdq_host *cq_host, u8 tag)
{
	u64 *link_temp;
	dma_addr_t trans_temp;

	link_temp = get_link_desc(cq_host, tag);
	trans_temp = get_trans_desc_dma(cq_host, tag);

	memset(link_temp, 0, sizeof(*link_temp));
	if (cq_host->link_desc_len > 1)
		*(link_temp + 1) &= 0;

	*link_temp = VALID(1) | ACT(0x6) | END(0);

	*link_temp |= DAT_ADDR_LO((u64) lower_32_bits(trans_temp));
	if (cq_host->link_desc_len > 1)
		*(link_temp + 1) |= DAT_ADDR_HI(upper_32_bits(trans_temp));
}

static void cmdq_clear_set_irqs(struct cmdq_host *cq_host, u32 clear, u32 set)
{
	u32 ier;

	ier = cmdq_readl(cq_host, CQISTE);
	ier &= ~clear;
	ier |= set;
	cmdq_writel(cq_host, ier, CQISTE);
	cmdq_writel(cq_host, ier, CQISGE);
	/* ensure the writes are done */
	mb();
}

/**
 * The allocated descriptor table for task, link & transfer descritors
 * looks like:
 * |----------|
 * |task desc |  |->|----------|
 * |----------|  |  |trans desc|
 * |link desc-|->|  |----------|
 * |----------|          .
 *      .                .
 *  no. of slots      max-segs
 *      .           |----------|
 * |----------|
 * The idea here is to create the [task+trans] table and mark & point the
 * link desc to the transfer desc table on a per slot basis.
 */
static int cmdq_host_alloc_tdl(struct cmdq_host *cq_host, int noalloc)
{

	size_t desc_size;
	size_t data_size;
	int i = 0;

	/* task descriptor can be 64/128 bit irrespective of arch */
	if (cq_host->caps & CMDQ_TASK_DESC_SZ_128) {
		cmdq_writel(cq_host, cmdq_readl(cq_host, CQCFG) | CQ_TASK_DESC_SZ, CQCFG);
		cq_host->task_desc_len = 2;
	} else {
		cq_host->task_desc_len = 1;
	}

	/* transfer desc. is 64 bit for 32 bit arch and 128 bit for 64 bit */
	if (cq_host->dma64)
		cq_host->trans_desc_len = 2;
	else
		cq_host->trans_desc_len = 1;

	cq_host->link_desc_len = cq_host->trans_desc_len;

	/* total size of a slot: 1 task & 1 transfer (link) */
	cq_host->slot_sz = cq_host->task_desc_len + cq_host->link_desc_len;

	/*
	 * 96 bits length of transfer desc instead of 128 bits which means
	 * ADMA would expect next valid descriptor at the 96th bit
	 * or 128th bit
	 */
	if (cq_host->dma64) {
		if (cq_host->quirks & CMDQ_QUIRK_SHORT_TXFR_DESC_SZ)
			cq_host->dma64_trans_desc_len = 12;
		else
			cq_host->dma64_trans_desc_len = 16;
	}
	desc_size = (sizeof(*cq_host->desc_base)) * cq_host->slot_sz * cq_host->num_slots;

	/* FIXME: consider allocating smaller chunks iteratively */
	data_size = (sizeof(*cq_host->trans_desc_base)) * cq_host->trans_desc_len * cq_host->mmc->max_segs * (cq_host->num_slots - 1);

	/*
	 * allocate a dma-mapped chunk of memory for the descriptors
	 * allocate a dma-mapped chunk of memory for link descriptors
	 * setup each link-desc memory offset per slot-number to
	 * the descriptor table.
	 */
	if (!noalloc) {
		cq_host->desc_base = dmam_alloc_coherent(mmc_dev(cq_host->mmc), desc_size, &cq_host->desc_dma_base, GFP_KERNEL);
		cq_host->trans_desc_base = dmam_alloc_coherent(mmc_dev(cq_host->mmc), data_size, &cq_host->trans_desc_dma_base, GFP_KERNEL);
#if 0
		memset(cq_host->desc_base, 0x5a, desc_size);
		memset(cq_host->trans_desc_base, 0x5a, data_size);
#endif
	}
	if (!cq_host->desc_base || !cq_host->trans_desc_base)
		return -ENOMEM;

	for (i = 0; i < (cq_host->num_slots - 1); i++)
		setup_trans_desc(cq_host, i);

	return 0;
}

static int cmdq_enable(struct mmc_host *mmc)
{
	int err = 0;
	u32 cqcfg;
	bool dcmd_enable;
	struct cmdq_host *cq_host = mmc_cmdq_private(mmc);

	cmdq_runtime_pm_get(mmc);

	if (!cq_host || !mmc->card || !mmc_card_mmc(mmc->card)
		|| !mmc_card_cmdq(mmc->card)) {
		pr_err("%s: cmdq_enable fail -- cq_host:%p; mmc->card:%p," " mmc_card_mmc(mmc->card):%d, mmc_card_cmdq(mmc->card):%d" "mmc->card:%p\n", __func__, cq_host, mmc->card, mmc_card_mmc(mmc->card), mmc_card_cmdq(mmc->card), mmc->card);
		err = -EINVAL;
		goto out;
	}

	if (cq_host->enabled)
		pr_err("WRONG reenabled cmdq %s:line %u\n", __func__, __LINE__);
	/*  goto out; */

	/* TODO: if the legacy MMC host controller is in idle state */

	cqcfg = cmdq_readl(cq_host, CQCFG);
	if (cqcfg & 0x1) {
		pr_err("%s: %s: cq_host is already enabled\n", mmc_hostname(mmc), __func__);
		WARN_ON(1);
		goto out;
	}

	if (!cq_host->desc_base || !cq_host->trans_desc_base) {
		err = cmdq_host_alloc_tdl(cq_host, cq_host->enabled);
		if (err)
			goto out;
	}

	pr_debug("****** %s:line %u  desc_dma_base is 0x%x  desc_base is %p trans_desc_base is %p\n", __func__, __LINE__, (u32) cq_host->desc_dma_base, cq_host->desc_base, cq_host->trans_desc_base);

	if (cq_host->quirks & CMDQ_QUIRK_NO_DCMD)
		dcmd_enable = false;
	else
		dcmd_enable = true;

	cqcfg = ((cq_host->dma64 ? CQ_TASK_DESC_SZ : 0) | (dcmd_enable ? CQ_DCMD : 0));

	cmdq_writel(cq_host, cqcfg, CQCFG);
	cmdq_writel(cq_host, 0x10100, CQSSC1);
	cq_host->cqcfg = cqcfg;

	/* want to write this address in any enable scario. */
	cmdq_writel(cq_host, lower_32_bits(cq_host->desc_dma_base), CQTDLBA);
	cmdq_writel(cq_host, upper_32_bits(cq_host->desc_dma_base), CQTDLBAU);

	/* leave send queue status timer configs to reset values */

	/* configure interrupt coalescing */
	/* mmc_cq_host_intr_aggr(host->cq_host, CQIC_DEFAULT_ICCTH,
	   CQIC_DEFAULT_ICTOVAL); */

	/* leave CQRMEM to reset value */

	/*
	 * disable all vendor interrupts
	 * enable CMDQ interrupts
	 * enable the vendor error interrupts
	 */
	if (cq_host->ops->clear_set_irqs)
		cq_host->reg = cq_host->ops->clear_set_irqs(mmc, 0xFFFFFFFF, SDHCI_INT_CMDQ_EN | SDHCI_INT_ERROR_MASK);

	cmdq_clear_set_irqs(cq_host, 0x0, CQ_INT_ALL);

	/* cq_host would use this rca to address the card */
	cmdq_writel(cq_host, mmc->card->rca, CQSSC2);

	cq_host->rca = mmc->card->rca;

	/* ensure the writes are done before enabling CQE */
	mb();

	/* enable CQ_HOST */
	cmdq_writel(cq_host, cmdq_readl(cq_host, CQCFG) | CQ_ENABLE, CQCFG);

	cq_host->enabled = true;

out:
	cmdq_runtime_pm_put(mmc);
	return err;
}

static int cmdq_disable(struct mmc_host *mmc, bool soft)
{
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	u32 reg = 0;
	int i = 0;
	unsigned long timeout = (8 * 1000);

	cmdq_runtime_pm_get(mmc);

	do {
		reg = cmdq_readl(cq_host, CQTDBR);
		reg |= cmdq_readl(cq_host, CQTCN);
		reg |= cmdq_readl(cq_host, CQDPT);

		for (i = 0; i < cq_host->num_slots; i++) {
			if (cq_host->mrq_slot[i])
				reg |= (u32) 1 << i;
		}

		if (timeout == 0) {
			pr_err("%s: wait cmdq complete reqs timeout !\n", __func__);
			return -ETIMEDOUT;
		}
		timeout--;
		mdelay(1);
	} while (reg);

	if (soft) {
		cmdq_writel(cq_host, cmdq_readl(cq_host, CQCFG) & ~(CQ_ENABLE), CQCFG);
	} else {
		/* FIXME: free the allocated descriptors */
	}
	cmdq_clear_set_irqs(cq_host, 0x0, 0x0);

	if (cq_host->ops->clear_set_irqs)
		cq_host->ops->clear_set_irqs(mmc, 0xFFFFFFFF, cq_host->reg);

	cq_host->enabled = false;

	pr_debug("%s: done.\n", __func__);

	cmdq_runtime_pm_put(mmc);

	return 0;
}

static int cmdq_restore_irqs(struct mmc_host *mmc)
{
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);

	if (!cq_host->enabled)
		return 0;

	if (cq_host->ops->clear_set_irqs)
		cq_host->reg = cq_host->ops->clear_set_irqs(cq_host->mmc, 0xFFFFFFFF, SDHCI_INT_CMDQ_EN | SDHCI_INT_ERROR_MASK);
	cmdq_clear_set_irqs(cq_host, 0x0, CQ_INT_ALL);

	return 0;
}

static void cmdq_prep_task_desc(struct mmc_request *mrq, u64 *data, bool intr, bool qbr)
{
	struct mmc_cmdq_req *cmdq_req = mrq->cmdq_req;
	u32 req_flags = cmdq_req->cmdq_req_flags;

	pr_debug("%s: %s: data-tag: 0x%08x - dir: %d - prio: %d - cnt: 0x%08x -	addr: 0x%x\n", mmc_hostname(mrq->host), __func__,
			!!(req_flags & DAT_TAG), !!(req_flags & DIR), !!(req_flags & PRIO), cmdq_req->data.blocks, mrq->cmdq_req->blk_addr);
#ifdef CMDQ_FIX_CLEAR_QBRTASK
	qbr = false;
#endif
	*data = VALID(1) | END(1) | INT(intr) | ACT(0x5) | FORCED_PROG(!!(req_flags & FORCED_PRG))
		| CONTEXT(mrq->cmdq_req->ctx_id) | DATA_TAG(!!(req_flags & DAT_TAG))
		| DATA_DIR(!!(req_flags & DIR)) | PRIORITY(!!(req_flags & PRIO)) | QBAR(qbr) | REL_WRITE(!!(req_flags & REL_WR))
		| BLK_COUNT(mrq->cmdq_req->data.blocks) | BLK_ADDR((u64)mrq->cmdq_req->blk_addr);
}

static int cmdq_dma_map(struct mmc_host *host, struct mmc_request *mrq)
{
	int sg_count;
	struct mmc_data *data = mrq->data;

	if (!data)
		return -EINVAL;

	sg_count = dma_map_sg(mmc_dev(host), data->sg, data->sg_len, (data->flags & MMC_DATA_READ) ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
	if (!sg_count)
		return -ENOMEM;

	return sg_count;
}

static void cmdq_set_tran_desc_32(u8 *desc, dma_addr_t addr, int len, bool end)
{
	u32 *link = (u32 __force *) desc;
	u32 *dataddr = (u32 __force *) (desc + 4);

	*link = (VALID(1) | END((end ? 1 : 0)) | INT(0) | ACT(0x4) | DAT_LENGTH(len));

	*dataddr = (u32) ((u32) addr & 0xFFFFFFFF);
	if (!*dataddr)
		pr_err("%s:%d cmdq task data is null!!!!\n", __func__, __LINE__);
}

static void cmdq_set_tran_desc_64(u8 *desc, dma_addr_t addr, int len, bool end)
{
	__le32 *link = (__le32 __force *) desc;
	__le64 *dataddr = (__le64 __force *) (desc + 4);

	*link = (VALID(1) | END((end ? 1 : 0)) | INT(0) | ACT(0x4) | DAT_LENGTH(len));

	dataddr[0] = cpu_to_le64(addr);
}

static int cmdq_prep_tran_desc(struct mmc_request *mrq, struct cmdq_host *cq_host, int tag)
{
	struct mmc_data *data = mrq->data;
	int i, sg_count, len;
	bool end = false;
	u64 *trans_desc = NULL;
	dma_addr_t addr;
	u8 *desc;
	struct scatterlist *sg;

	mrq->data->bytes_xfered = 0;
	sg_count = cmdq_dma_map(mrq->host, mrq);
	if (sg_count < 0) {
		pr_err("%s: %s: unable to map sg lists, %d\n", mmc_hostname(mrq->host), __func__, sg_count);
		return sg_count;
	}
	trans_desc = get_trans_desc(cq_host, tag);
	desc = (u8 *) trans_desc;
	memset(trans_desc, 0, sizeof(*trans_desc));
	for_each_sg(data->sg, sg, sg_count, i) {
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);

		if ((i + 1) == sg_count)
			end = true;

		if (cq_host->dma64) {
			cmdq_set_tran_desc_64(desc, addr, len, end);
			desc += cq_host->dma64_trans_desc_len;
		} else {
			cmdq_set_tran_desc_32(desc, addr, len, end);
			desc += 8;
		}

		mrq->data->bytes_xfered += len;
	}

	pr_debug("%s: req: 0x%p tag: %d calc-link_des: 0x%p sg-cnt: %d\n", __func__, mrq->req, tag, trans_desc, sg_count);

	return 0;
}

static void cmdq_prep_dcmd_desc(struct mmc_host *mmc, struct mmc_request *mrq)
{
	u64 *task_desc = NULL;
	u64 data = 0;
	u8 resp_type;
	u8 *desc;
	/*__le64 *dataddr;*/
	u32 *dataddr;
	struct cmdq_host *cq_host = mmc_cmdq_private(mmc);

	if (!(mrq->cmd->flags & MMC_RSP_PRESENT)) {
		resp_type = RES_TYPE_NO_RES;
	} else if ((mrq->cmd->flags & MMC_RSP_R1B) == MMC_RSP_R1B) {
#ifdef CMDQ_FIX_CHECKBUSY
		resp_type = RES_TYPE_R145;
#else
		resp_type = RES_TYPE_R1B;
#endif
	} else if (((mrq->cmd->flags & MMC_RSP_R1) == MMC_RSP_R1)
				|| ((mrq->cmd->flags & MMC_RSP_R4) == MMC_RSP_R4)
				|| ((mrq->cmd->flags & MMC_RSP_R5) == MMC_RSP_R5)) {
			resp_type = RES_TYPE_R145;
	} else {
		pr_err("%s: weird response: 0x%x\n", mmc_hostname(mmc), mrq->cmd->flags);
		BUG_ON(1);
	}

	pr_debug("%s: DCMD->opcode: %d, arg: 0x%x, resp_type = %d\n", __func__, mrq->cmd->opcode, mrq->cmd->arg, resp_type);

	task_desc = get_desc(cq_host, cq_host->dcmd_slot);
	memset(task_desc, 0, sizeof(*task_desc));
	data |= (VALID(1) | END(1) | INT(1) | QBAR(1) | ACT(0x5) | CMD_INDEX(mrq->cmd->opcode) | CMD_TIMING(0) | RESP_TYPE(resp_type));
	*task_desc |= data;
	desc = (u8 *) task_desc;

	/*dataddr = (__le64 __force *)(desc + 4);*/
	/*dataddr[0] = cpu_to_le64((u64)mrq->cmd->arg);*/

	dataddr = (u32 *) (desc + 4);
	dataddr[0] = (u32) mrq->cmd->arg;
	wmb();

	if (cq_host->ops->set_data_timeout)
		cq_host->ops->set_data_timeout(mmc, 0xf);
}

static int cmdq_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	int err;
	u64 data = 0;
	u64 *task_desc = NULL;
	u32 tag = mrq->cmdq_req->tag;
	u32 i = 0;
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	unsigned long flags;
	int busy_status;
	u32 req_status = 0;
	u32 waitbusy_timeout;

	if (!cq_host->enabled) {
		pr_err("%s cq_host->enable not true.\n", __func__);
		err = -EHOSTDOWN;
		goto out;
	}

	cmdq_runtime_pm_get(mmc);

	spin_lock_irqsave(&cq_host->cmdq_lock, flags);
#ifdef CMDQ_FIX_CHECKBUSY
	if (true == cq_host->check_busy) {
		while (1) {
			req_status = cmdq_readl(cq_host, CQTDBR);
			if (0 == (req_status & (1 << 31)))
				break;
		}

		if (cq_host->ops->card_busy) {
			/*some dcmd such as secure trim will cost long time
			 *set the timeout time to 10s,the same with the timeout
			 *set in emmc5.0;
			 */
			waitbusy_timeout = 10000000;
			while (1) {
				busy_status = cq_host->ops->card_busy(mmc);
				if (!busy_status)
					break;
				if (0 == waitbusy_timeout) {
					pr_err("%s: wait card busy timeout\n", __func__);
					break;
				}
				waitbusy_timeout--;
				udelay(1);
			}
		} else {
			pr_warn("%s: no card_busy ops.\n", __func__);
		}
		cq_host->check_busy = false;
	}
#endif
	if (mrq->cmdq_req->cmdq_req_flags & DCMD) {
		pr_debug("%s: DCMD mrq\n", __func__);
#ifdef CMDQ_FIX_CHECKBUSY
		while (1) {
			req_status = cmdq_readl(cq_host, CQTDBR);

			for (i = 0; i < cq_host->num_slots; i++) {
				if (cq_host->mrq_slot[i])
					req_status |= (u32) 1 << i;
			}

			if (0 == req_status)
				break;
			else {
				spin_unlock_irqrestore(&cq_host->cmdq_lock, flags);
				spin_lock_irqsave(&cq_host->cmdq_lock, flags);
			}

		}
#endif
		cmdq_prep_dcmd_desc(mmc, mrq);
		if (cq_host->mrq_slot[31])
			BUG_ON(1);

		cq_host->mrq_slot[31] = mrq;
		mod_timer(&cq_host->timer[31], jiffies + msecs_to_jiffies(CMDQ_TASK_TIMEOUT_MS));

		if (true == cq_host->fix_qbr)
			BUG_ON(cmdq_readl(cq_host, CQTDBR));

		if (false == cq_host->err_handle)
			cmdq_writel(cq_host, 1 << 31, CQTDBR);
#ifdef CMDQ_FIX_CHECKBUSY
		cq_host->check_busy = true;
#endif
		spin_unlock_irqrestore(&cq_host->cmdq_lock, flags);
		return 0;
	}

	task_desc = get_desc(cq_host, tag);

	cmdq_prep_task_desc(mrq, &data, 1, (mrq->cmdq_req->cmdq_req_flags & QBR));
	*task_desc = cpu_to_le64(data);
	if (!*task_desc)
		pr_emerg("%s:%d cmdq task data is null!!!!\n", __func__, __LINE__);

	err = cmdq_prep_tran_desc(mrq, cq_host, tag);
	if (err) {
		pr_err("%s: %s: failed to setup tx desc: %d\n", mmc_hostname(mmc), __func__, err);
		BUG_ON(1);
	}
	wmb();

	BUG_ON(cmdq_readl(cq_host, CQTDBR) & (1 << tag));

	if (cq_host->mrq_slot[tag])
		BUG_ON(1);

	if (cq_host->ops->set_tranfer_params)
		cq_host->ops->set_tranfer_params(mmc);

	if (cq_host->ops->set_data_timeout)
		cq_host->ops->set_data_timeout(mmc, 0xf);

	cq_host->mrq_slot[tag] = mrq;
	mod_timer(&cq_host->timer[tag], jiffies + msecs_to_jiffies(CMDQ_TASK_TIMEOUT_MS));

	if (true == cq_host->fix_qbr) {
		if ((0 == cmdq_readl(cq_host, CQTDBR))
			&& (false == cq_host->err_handle))
			cmdq_writel(cq_host, (u32) 1 << tag, CQTDBR);
	} else {
		if (false == cq_host->err_handle)
			cmdq_writel(cq_host, (u32) 1 << tag, CQTDBR);
	}

	spin_unlock_irqrestore(&cq_host->cmdq_lock, flags);

out:
	return err;
}

static int cmdq_finish_data(struct mmc_host *mmc, unsigned int tag)
{
	struct mmc_request *mrq;
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);

	mrq = cq_host->mrq_slot[tag];
	if (NULL == mrq) {
		pr_err("%s: mrq_slot %d is NULL in data finishing!!!\n", mmc_hostname(mmc), tag);
		return -1;
	}

	cq_host->mrq_slot[tag] = NULL;
	del_timer(&cq_host->timer[tag]);
	cq_host->ops->tuning_move(mmc, TUNING_CLK, TUNING_FLAG_CLEAR_COUNT);

	if (mrq->cmd)
		mrq->cmd->error = 0;
	if (mrq->data)
		mrq->data->error = 0;
	/*TODO: error handle*/
	mrq->done(mrq);

	return 0;
}

u32 sdhci_cmdq_readl(struct cmdq_host *host, int reg)
{
	return cmdq_readl(host, CQTDBR);
}

irqreturn_t cmdq_irq(struct mmc_host *mmc, u32 intmask)
{
	u32 status;
	unsigned long tag = 0, comp_status;
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	u32 reg_val = 0;
	u32 tmp_qctcn = 0;
	u32 req_count = 0;
	u32 err = 0;
	u32 err_info = 0;
	int ret = 0;

	if (intmask & SDHCI_INT_ERROR_MASK) {
		pr_err("%s: cmd queue err, intmask = 0x%x\n", __func__, intmask);
		cmdq_dumpregs(cq_host);
		err = 1;
	} else if (intmask != SDHCI_INT_CMDQ) {
		pr_err("%s: not expect cmdq irq, intmask = 0x%x\n", __func__, intmask);
		cmdq_dumpregs(cq_host);
	}

	status = cmdq_readl(cq_host, CQIS);
	cmdq_writel(cq_host, status, CQIS);
	if ((status & CQIS_RED) || err) {
		spin_lock(&cq_host->cmdq_lock);
		if (!err) {
			/* task response has an error */
			pr_err("%s: RED error %d !!!\n", mmc_hostname(mmc), status);
			cmdq_dumpregs(cq_host);
		}

		if (cq_host->err_handle)
			pr_warn("%s: error handle is doing\n", mmc_hostname(mmc));

		/* prase error information */
		err_info = cmdq_readl(cq_host, CQTERRI);
		if (err_info & CQTERRI_RES_ERR) {
			if (CQTERRI_RES_CMD(err_info) == 13) {
				if (++cq_host->cmd13_err_count > CMDQ_CMD13_RETRY_TIMES) {
					cq_host->err_handle = true;
				}
			} else {
				cq_host->err_handle = true;
			}
		} else if (err_info & CQTERRI_DAT_ERR) {
			cq_host->err_handle = true;
		} else if (status & CQIS_RED) {
			cq_host->err_handle = true;
		} else {
			pr_err("%s: error irq without error info, err_info = 0x%x!!!\n", mmc_hostname(mmc), err_info);
			BUG_ON(1);
		}

		if (cq_host->err_handle) {
			/* mask & disable error interupt */
			cq_host->ops->clear_set_irqs(mmc, 0xFFFFFFFF, SDHCI_INT_CMDQ_EN);
			cmdq_clear_set_irqs(cq_host, CQIS_RED, 0x0);
			/* clean error interupt */
			cq_host->ops->clean_irqs(mmc, SDHCI_INT_ERROR_MASK);
			cmdq_writel(cq_host, CQIS_RED, CQIS);
#ifdef CONFIG_HUAWEI_EMMC_DSM
			sdhci_cmdq_dsm_set_host_status(mmc_priv(mmc), (intmask & SDHCI_INT_ERROR_MASK));
#endif
			queue_work(cq_host->wq_resend, &cq_host->work_resend);
		}
		spin_unlock(&cq_host->cmdq_lock);
	}
	if (status & CQIS_HAC) {
		/* halt is completed, wakeup waiting thread */
		pr_err("%s: cmd queue halt completed. status = 0x%x\n", __func__, status);
		complete(&cq_host->halt_comp);
	}
	if (status & CQIS_TCL) {
		/* task is cleared, wakeup waiting thread */
		pr_err("%s: cmd queue task clear. status = 0x%x\n", __func__, status);
		complete(&cq_host->clear_comp);
	}
	if (status & CQIS_TERR) {
		pr_err("%s: cmd queue task error (invalid task descriptor) %d !!!\n", mmc_hostname(mmc), status);
		cmdq_dumpregs(cq_host);
		BUG_ON(1);
	}
	if (status & CQIS_TCC) {
		spin_lock(&cq_host->cmdq_lock);
		if (false == cq_host->err_handle) {
			spin_unlock(&cq_host->cmdq_lock);

			cq_host->cmd13_err_count = 0;
			/* read QCTCN and complete the request */
			comp_status = cmdq_readl(cq_host, CQTCN);
			cmdq_writel(cq_host, comp_status, CQTCN);
			reg_val = cmdq_readl(cq_host, CQTDBR);
			comp_status &= ~reg_val;
			req_count = 0;
			for_each_set_bit(tag, &comp_status, cq_host->num_slots) {
				/* complete the corresponding mrq */
				ret = cmdq_finish_data(mmc, tag);
				/* complete DCMD on tag 31 */
				if (!ret)
					req_count++;
			}
			if (true == cq_host->fix_qbr) {
				spin_lock(&cq_host->cmdq_lock);
				if (0 == cmdq_readl(cq_host, CQTDBR)) {
					reg_val = 0;
					tmp_qctcn = cmdq_readl(cq_host, CQTCN);
					for (tag = 0; tag < cq_host->num_slots - 1; tag++) {
						if (cq_host->mrq_slot[tag] && (!(tmp_qctcn & (1 << tag))))
							reg_val |= 1 << tag;
					}
					cmdq_writel(cq_host, reg_val, CQTDBR);
				}
				spin_unlock(&cq_host->cmdq_lock);
			}
			while (req_count) {
				cmdq_runtime_pm_put(mmc);
				req_count--;
			}
		} else {
			spin_unlock(&cq_host->cmdq_lock);
		}
	}

	return IRQ_HANDLED;
}

EXPORT_SYMBOL(cmdq_irq);

/* May sleep */
static int cmdq_halt(struct mmc_host *mmc, bool halt)
{
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	u32 val;

	if (halt) {
		if (cmdq_readl(cq_host, CQCTL) & HALT) {
			pr_warn("%s: CQE already HALT\n", mmc_hostname(mmc));
			return 0;
		}
		cmdq_writel(cq_host, cmdq_readl(cq_host, CQCTL) | HALT, CQCTL);
		val = wait_for_completion_timeout(&cq_host->halt_comp, msecs_to_jiffies(HALT_TIMEOUT_MS));
		return val ? 0 : -ETIMEDOUT;
	} else {
		cmdq_writel(cq_host, cmdq_readl(cq_host, CQCTL) & ~HALT, CQCTL);
	}

	return 0;
}

static int cmdq_clear_task(struct mmc_host *mmc, u32 task)
{
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	u32 value, ret;
	unsigned long tag, comp_status;

	if (!task) {
		pr_err("%s: task is null\n", __func__);
		return 0;
	}

	if (0 == (HALT & cmdq_readl(cq_host, CQCTL))) {
		pr_err("CQE is not in HALT, cannot clear task\n");
		return -1;
	}

	value = cmdq_readl(cq_host, CQTDBR);
	if (value == task) {
		/* clean all task */
		cmdq_writel(cq_host, CLEAR_ALL_TASKS | cmdq_readl(cq_host, CQCTL), CQCTL);
		ret = wait_for_completion_timeout(&cq_host->clear_comp, msecs_to_jiffies(CLEAR_TIMEOUT_MS));
		return ret ? 0 : -ETIMEDOUT;
	} else {
		/* clean task one by one */
		comp_status = task;
		for_each_set_bit(tag, &comp_status, cq_host->num_slots) {
			cmdq_writel(cq_host, 1 << tag, CQTCLR);
			ret = wait_for_completion_timeout(&cq_host->clear_comp, msecs_to_jiffies(CLEAR_TIMEOUT_MS));
			if (!ret)
				return -ETIMEDOUT;
		}
		return 0;
	}
}

static void cmdq_post_req(struct mmc_host *mmc, struct mmc_request *mrq, int err)
{
	struct mmc_data *data = mrq->data;

	if (data) {
		data->error = 0;
		dma_unmap_sg(mmc_dev(mmc), data->sg, data->sg_len, (data->flags & MMC_DATA_READ) ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
	}
}

static void cmdq_work_resend(struct work_struct *work)
{
	struct cmdq_host *cq_host = container_of(work, struct cmdq_host, work_resend);
	struct mmc_host *mmc = cq_host->mmc;
	int ret = 0;
	int move_type = 0;
	bool need_tuning_move;
	u32 tag, val, timeout, i;
	unsigned long comp_status;
	struct mmc_request *mrq;
	unsigned long flags;
	u32 db_reg = 0;
	u32 req_count = 0;
	bool timeout_fail = false;

#ifdef CONFIG_HUAWEI_EMMC_DSM
	bool dsm = true;
#endif
	pr_err("%s:%s++\n", mmc_hostname(cq_host->mmc), __func__);
	/* count error retry */
	val = cmdq_readl(cq_host, CQTERRI);
	if (val & CQTERRI_DAT_ERR) {
		tag = CQTERRI_DAT_TASK(val);
		if ((cq_host->mmc->ios.timing == MMC_TIMING_MMC_HS400)
			|| cq_host->mmc->card->ext_csd.strobe_enhanced_en)
			move_type = TUNING_STROBE;
		else
			move_type = TUNING_CLK;
		need_tuning_move = true;
	} else if (val & CQTERRI_RES_ERR) {
		tag = CQTERRI_RES_TASK(val);
		if (cq_host->mmc->card->ext_csd.strobe_enhanced_en)
			move_type = TUNING_STROBE;
		else
			move_type = TUNING_CLK;
		need_tuning_move = true;
	} else {
		timeout_fail = true;
		need_tuning_move = false;
		pr_err("%s:%s: timeout or other error\n", mmc_hostname(cq_host->mmc), __func__);
	}

	/* halt */
	ret = cmdq_halt(cq_host->mmc, true);
	if (ret) {
		pr_err("cmdq_halt timeout\n");
		cmdq_dumpregs(cq_host);
		BUG_ON(1);
	}

	/* tuning move */
	if (need_tuning_move) {
		ret = cq_host->ops->tuning_move(cq_host->mmc,
							move_type, TUNING_FLAG_NOUSE);
		if (ret) {
				pr_err("cmdq tuning move fail\n");
		}
	}

	if (timeout_fail) {
		val = cmdq_readl(cq_host, CQTCN);
		/*if TCN has val,we should finish all the finish tasks */
		if (val) {
			comp_status = val;
			req_count = 0;
			pr_err("%s:%s timeout but reg notify is 0x%x\n", mmc_hostname(cq_host->mmc), __func__, val);
			cmdq_writel(cq_host, val, CQTCN);
			for_each_set_bit(i, &comp_status, cq_host->num_slots) {
				/* complete the corresponding mrq */
				ret = cmdq_finish_data(mmc, i);
				/* complete DCMD on tag 31 */
				if (!ret)
					req_count++;
			}
		}

		val = cmdq_readl(cq_host, CQTDBR);
		if (!val) {
			/*doorbell is 0,means all task finished,but we need to
			 *solve the stored tasks that did not set dbr because
			 *of this error handle,we need update all the timers
			 *of the stored tasks;
			 */
			pr_err("%s:%s timeout but dbr is 0\n", mmc_hostname(cq_host->mmc), __func__);
			goto dishalt;
		} else {
			comp_status = val;
			tag = find_first_bit(&comp_status, cq_host->num_slots);
			pr_err("%s:%s: no need tuning move\n", mmc_hostname(cq_host->mmc), __func__);
		}
	}

	if (tag < cq_host->num_slots) {
		mrq = cq_host->mrq_slot[tag];
		pr_err("%s:%s check retries\n", mmc_hostname(cq_host->mmc), __func__);
		if (mrq) {
			if (mrq->cmd->retries-- == 0) {
				pr_err("%s: mrq->cmd->retries == 0\n", __func__);
				BUG_ON(1);
			}
		}
	} else {
		pr_err("%s:err tag num %d\n", __func__, tag);
		BUG_ON(1);
	}

	/* clear pending task */
	val = cmdq_readl(cq_host, CQDPT);

	ret = cmdq_clear_task(cq_host->mmc, val);
	if (ret) {
		pr_err("cmdq_clear timeout\n");
		cmdq_dumpregs(cq_host);
		BUG_ON(1);
	}
	db_reg = cmdq_readl(cq_host, CQTDBR);
	pr_err("%s:%s: doorbell is 0x%x after clear task\n", mmc_hostname(cq_host->mmc), __func__, db_reg);

	/* send cmd48 */
	ret = cq_host->ops->discard_task(cq_host->mmc, 0, true);
	if (ret) {
		pr_err("cmdq discard task fail\n");
	}

	/* wait busy */
	timeout = CLEAR_TIMEOUT_MS;
	while (cq_host->ops->card_busy(cq_host->mmc)) {
		if (timeout == 0) {
			pr_err("%s: wait discard task busy timeout\n", __func__);
			cmdq_dumpregs(cq_host);
			break;
		}
		timeout--;
		mdelay(1);
	}

	/* enable error interupt */
	cq_host->ops->clear_set_irqs(cq_host->mmc, 0xFFFFFFFF, SDHCI_INT_CMDQ_EN | SDHCI_INT_ERROR_MASK);
	cmdq_clear_set_irqs(cq_host, 0x0, CQ_INT_ALL);

dishalt:
	/* dis-halt */
	cmdq_halt(cq_host->mmc, false);
	pr_err("%s dishalt complete\n", __func__);

	spin_lock_irqsave(&cq_host->cmdq_lock, flags);
	cq_host->err_handle = false;
	/* re-write doorbell,because err_handle is true,tasks can't set dbr
	 * we need set dbr and retry the stored tasks
	 */
	if (db_reg == cmdq_readl(cq_host, CQTDBR)) {
		val = db_reg;
		for (tag = 0; tag < cq_host->num_slots; tag++) {
			/*TODO: need check DCMD*/
			if (cq_host->mrq_slot[tag])
				val |= (1 << tag);
		}
		cmdq_writel(cq_host, val, CQTDBR);
	} else {
		pr_err("%s:%s: There are tasks written to doorbell after clear task!!!\n", mmc_hostname(cq_host->mmc), __func__);
	}

	spin_unlock_irqrestore(&cq_host->cmdq_lock, flags);

	/*pm put for the finished tasks */
	while (req_count) {
		cmdq_runtime_pm_put(mmc);
		req_count--;
	}

	pr_err("%s:%s--\n", mmc_hostname(cq_host->mmc), __func__);

#ifdef CONFIG_HUAWEI_EMMC_DSM
	sdhci_cmdq_dsm_work(cq_host, dsm);
#endif
}

static void cmdq_timeout_timer(unsigned long param)
{
	struct cmdq_host *cq_host = (struct cmdq_host *)param;
	unsigned long flags;

	spin_lock_irqsave(&cq_host->cmdq_lock, flags);
	pr_err("%s: Timeout waiting for hardware interrupt.\n", __func__);
	cmdq_dumpregs(cq_host);
	if (false == cq_host->err_handle) {
		cq_host->err_handle = true;
		/* mask & disable error interupt */
		cq_host->ops->clear_set_irqs(cq_host->mmc, 0xFFFFFFFF, SDHCI_INT_CMDQ_EN);
		cmdq_clear_set_irqs(cq_host, CQIS_RED, 0x0);
#ifdef CONFIG_HUAWEI_EMMC_DSM
		sdhci_cmdq_dsm_set_host_status(mmc_priv(cq_host->mmc), -1U);	/* timeout*/
#endif
		queue_work(cq_host->wq_resend, &cq_host->work_resend);
	}
	spin_unlock_irqrestore(&cq_host->cmdq_lock, flags);

	return;
}

static const struct mmc_cmdq_host_ops cmdq_host_ops = {
	.enable = cmdq_enable,
	.disable = cmdq_disable,
	.restore_irqs = cmdq_restore_irqs,
	.request = cmdq_request,
	.halt = cmdq_halt,
	.post_req = cmdq_post_req,
};

struct cmdq_host *cmdq_pltfm_init(struct platform_device *pdev, void __iomem *cmda_ioaddr)
{
	struct cmdq_host *cq_host;
	struct resource *cmdq_memres = NULL;

	if (cmda_ioaddr) {
		cq_host = kzalloc(sizeof(*cq_host), GFP_KERNEL);
		if (!cq_host) {
			dev_err(&pdev->dev, "allocate memory for CMDQ fail\n");
			return ERR_PTR(-ENOMEM);
		}

		cq_host->mmio = cmda_ioaddr;
	} else {
		/* check and setup CMDQ interface */
		cmdq_memres = platform_get_resource_byname(pdev, IORESOURCE_MEM, "cmdq_mem");
		if (!cmdq_memres) {
			dev_err(&pdev->dev, "CMDQ not supported\n");
			return ERR_PTR(-EINVAL);
		}
		cq_host = kzalloc(sizeof(*cq_host), GFP_KERNEL);
		if (!cq_host) {
			dev_err(&pdev->dev, "failed to allocate memory for CMDQ\n");
			return ERR_PTR(-ENOMEM);
		}

		cq_host->mmio = devm_ioremap(&pdev->dev, cmdq_memres->start, resource_size(cmdq_memres));

		if (!cq_host->mmio) {
			dev_err(&pdev->dev, "failed to remap cmdq regs\n");
			kfree(cq_host);
			return ERR_PTR(-EBUSY);
		}

		dev_dbg(&pdev->dev, "CMDQ ioremap: done\n");
	}

	return cq_host;
}

EXPORT_SYMBOL(cmdq_pltfm_init);

int cmdq_init(struct cmdq_host *cq_host, struct mmc_host *mmc, bool dma64)
{
	int i;

	cq_host->dma64 = dma64;
	cq_host->mmc = mmc;

	/* should be parsed */
	cq_host->num_slots = 32;
	cq_host->dcmd_slot = 31;

	mmc->cmdq_ops = &cmdq_host_ops;

	cq_host->mrq_slot = kzalloc(sizeof(cq_host->mrq_slot) * cq_host->num_slots, GFP_KERNEL);
	if (!cq_host->mrq_slot)
		return -ENOMEM;
	cq_host->timer = kzalloc(sizeof(struct timer_list) * cq_host->num_slots, GFP_KERNEL);

	if (!cq_host->timer) {
		kfree(cq_host->mrq_slot);
		return -ENOMEM;
	}

	mmc->cmdq_private = cq_host;
	cq_host->check_busy = false;
	cq_host->cmd13_err_count = 0;
	cq_host->err_handle = false;

	spin_lock_init(&cq_host->cmdq_lock);

	init_completion(&cq_host->halt_comp);
	init_completion(&cq_host->clear_comp);

	cq_host->wq_resend = create_singlethread_workqueue("cmdq_wq_resend");
	INIT_WORK(&cq_host->work_resend, cmdq_work_resend);

	for (i = 0; i < cq_host->num_slots; i++) {
		setup_timer(&cq_host->timer[i], cmdq_timeout_timer, (unsigned long)cq_host);
	}

	pr_err("%s: done.\n", __func__);
	return 0;
}

EXPORT_SYMBOL(cmdq_init);
