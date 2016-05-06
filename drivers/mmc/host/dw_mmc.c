/*
 * Synopsys DesignWare Multimedia Card Interface driver
 *  (Based on NXP driver for lpc 31xx)
 *
 * Copyright (C) 2009 NXP Semiconductors
 * Copyright (C) 2009, 2010 Imagination Technologies Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/blkdev.h>
#include <linux/clk.h>
#include <linux/debugfs.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/stat.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/sdio.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sd.h>
#include <linux/mmc/dw_mmc.h>
#include <linux/bitops.h>
#include <linux/regulator/consumer.h>
#include <linux/pinctrl/consumer.h>
#include <linux/workqueue.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_address.h>
#include <asm/cacheflush.h>
#include <linux/pm_runtime.h>

#include "k3v3_mmc_raw.h"
#include "dw_mmc.h"
#include <linux/hisi/hw_cmdline_parse.h> /*for runmode_is_factory*/
#include <linux/hisi/mmc_trace.h>

#ifdef  CONFIG_HUAWEI_DSM
#include <dsm/dsm_pub.h>
#endif
/* Common flag combinations */

#define DW_MCI_SEND_STATUS	1
#define DW_MCI_RECV_STATUS	2
#define DW_MCI_DMA_THRESHOLD	4

#define DW_MCI_DESC_SZ 1
#define DW_MCI_DESC_SZ_64BIT 2

#ifdef CONFIG_MMC_DW_IDMAC
/* Each descriptor can transfer up to 4KB of data in chained mode */
#define DW_MCI_DESC_DATA_LENGTH	0x1000
/*32bit DMA descriptor struct*/
struct idmac_desc {
	u32		des0;	/* Control Descriptor */
#define IDMAC_DES0_DIC	BIT(1)
#define IDMAC_DES0_LD	BIT(2)
#define IDMAC_DES0_FD	BIT(3)
#define IDMAC_DES0_CH	BIT(4)
#define IDMAC_DES0_ER	BIT(5)
#define IDMAC_DES0_OWN	BIT(31)

	u32		des1;	/* Buffer sizes */
#define IDMAC_SET_BUFFER1_SIZE(d, s) \
	((d)->des1 = ((d)->des1 & 0x03ffe000) | ((s) & 0x1fff))

	u32		des2;	/* buffer 1 physical address */

	u32		des3;	/* buffer 2 physical address */
};

/*64bit DMA descriptor struct*/
struct idmac_desc_64bit {
	u32		des0;	/* Control Descriptor */
#define IDMAC_DES0_DIC	BIT(1)
#define IDMAC_DES0_LD	BIT(2)
#define IDMAC_DES0_FD	BIT(3)
#define IDMAC_DES0_CH	BIT(4)
#define IDMAC_DES0_ER	BIT(5)
#define IDMAC_DES0_OWN	BIT(31)

	u32		des1;	/* reserved */
	u32		des2;	/* Buffer sizes */
#define IDMAC_64ADDR_SET_BUFFER1_SIZE(d, s) \
	((d)->des2 = ((d)->des2 & cpu_to_le32(0x03ffe000)) | \
	 ((cpu_to_le32(s)) & cpu_to_le32(0x1fff)))

	u32		des3;	/* reserved */

	u32		des4;	/* buffer 1 low 32bit address point */

	u32		des5;    /* buffer 1 upper 32bit  address point */

	u32		des6;	/* buffer 2 low 32bit address point */

	u32		des7;    /* buffer 2 upper 32bit  address point */
};
#endif /* CONFIG_MMC_DW_IDMAC */

struct mmc_host *g_mmc_for_mmctrace[3] = {NULL};

extern void gic_reg_dump(void);

#ifdef  CONFIG_HUAWEI_DSM
extern void dw_mci_dsm_dump(struct dw_mci  *host, int err_num);
#endif

#if defined(CONFIG_DEBUG_FS)
static int dw_mci_req_show(struct seq_file *s, void *v)
{
	struct dw_mci_slot *slot = s->private;
	struct mmc_request *mrq;
	struct mmc_command *cmd;
	struct mmc_command *stop;
	struct mmc_data	*data;

	/* Make sure we get a consistent snapshot */
	spin_lock_bh(&slot->host->lock);
	mrq = slot->mrq;

	if (mrq) {
		cmd = mrq->cmd;
		data = mrq->data;
		stop = mrq->stop;

		if (cmd)
			seq_printf(s,
				   "CMD%u(0x%x) flg %x rsp %x %x %x %x err %d\n",
				   cmd->opcode, cmd->arg, cmd->flags,
				   cmd->resp[0], cmd->resp[1], cmd->resp[2],
				   cmd->resp[2], cmd->error);
		if (data)
			seq_printf(s, "DATA %u / %u * %u flg %x err %d\n",
				   data->bytes_xfered, data->blocks,
				   data->blksz, data->flags, data->error);
		if (stop)
			seq_printf(s,
				   "CMD%u(0x%x) flg %x rsp %x %x %x %x err %d\n",
				   stop->opcode, stop->arg, stop->flags,
				   stop->resp[0], stop->resp[1], stop->resp[2],
				   stop->resp[2], stop->error);
	}

	spin_unlock_bh(&slot->host->lock);

	return 0;
}

static int dw_mci_req_open(struct inode *inode, struct file *file)
{
	return single_open(file, dw_mci_req_show, inode->i_private);
}

static const struct file_operations dw_mci_req_fops = {
	.owner		= THIS_MODULE,
	.open		= dw_mci_req_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int dw_mci_regs_show(struct seq_file *s, void *v)
{
	seq_printf(s, "STATUS:\t0x%08x\n", SDMMC_STATUS);
	seq_printf(s, "RINTSTS:\t0x%08x\n", SDMMC_RINTSTS);
	seq_printf(s, "CMD:\t0x%08x\n", SDMMC_CMD);
	seq_printf(s, "CTRL:\t0x%08x\n", SDMMC_CTRL);
	seq_printf(s, "INTMASK:\t0x%08x\n", SDMMC_INTMASK);
	seq_printf(s, "CLKENA:\t0x%08x\n", SDMMC_CLKENA);

	return 0;
}

static int dw_mci_regs_open(struct inode *inode, struct file *file)
{
	return single_open(file, dw_mci_regs_show, inode->i_private);
}

static const struct file_operations dw_mci_regs_fops = {
	.owner		= THIS_MODULE,
	.open		= dw_mci_regs_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int mmc_caps_opt_get(void *data, u64 *val)
{
	struct mmc_host *host = data;

	*val = host->caps;

	return 0;
}

static int mmc_caps_opt_set(void *data, u64 val)
{
	struct mmc_host *host = data;

	host->caps = val;

	return 0;
}
DEFINE_SIMPLE_ATTRIBUTE(mmc_caps_fops, mmc_caps_opt_get, mmc_caps_opt_set,
	"%llu\n");

static int mmc_caps2_opt_get(void *data, u64 *val)
{
	struct mmc_host *host = data;

	*val = host->caps2;

	return 0;
}

static int mmc_caps2_opt_set(void *data, u64 val)
{
	struct mmc_host *host = data;

	host->caps2 = val;

	return 0;
}
DEFINE_SIMPLE_ATTRIBUTE(mmc_caps2_fops, mmc_caps2_opt_get, mmc_caps2_opt_set,
	"%llu\n");

static void dw_mci_init_debugfs(struct dw_mci_slot *slot)
{
	struct mmc_host	*mmc = slot->mmc;
	struct dw_mci *host = slot->host;
	struct dentry *root;
	struct dentry *node;

	root = mmc->debugfs_root;
	if (!root)
		return;

	node = debugfs_create_file("regs", S_IRUSR, root, host,
				   &dw_mci_regs_fops);
	if (!node)
		goto err;

	node = debugfs_create_file("req", S_IRUSR, root, slot,
				   &dw_mci_req_fops);
	if (!node)
		goto err;

	node = debugfs_create_u32("state", S_IRUSR, root, (u32 *)&host->state);
	if (!node)
		goto err;

	node = debugfs_create_x32("pending_events", S_IRUSR, root,
				  (u32 *)&host->pending_events);
	if (!node)
		goto err;

	node = debugfs_create_x32("completed_events", S_IRUSR, root,
				  (u32 *)&host->completed_events);
	if (!node)
		goto err;

	if (!debugfs_create_file("caps", S_IRUSR | S_IWUSR, root, mmc,
			&mmc_caps_fops))
		goto err;

	if (!debugfs_create_file("caps2", S_IRUSR | S_IWUSR, root, mmc,
			&mmc_caps2_fops))
		goto err;

	return;

err:
	dev_err(&mmc->class_dev, "failed to initialize debugfs for slot\n");
}
#endif /* defined(CONFIG_DEBUG_FS) */

static void dw_mci_reg_dump(struct dw_mci *host)
{
	u32 status, mintsts;
	dev_err(host->dev, ": ============== REGISTER DUMP ==============\n");
	dev_err(host->dev, ": CTRL:	0x%08x\n", mci_readl(host, CTRL));
	dev_err(host->dev, ": PWREN:	0x%08x\n", mci_readl(host, PWREN));
	dev_err(host->dev, ": CLKDIV:	0x%08x\n", mci_readl(host, CLKDIV));
	dev_err(host->dev, ": CLKSRC:	0x%08x\n", mci_readl(host, CLKSRC));
	dev_err(host->dev, ": CLKENA:	0x%08x\n", mci_readl(host, CLKENA));
	dev_err(host->dev, ": TMOUT:	0x%08x\n", mci_readl(host, TMOUT));
	dev_err(host->dev, ": CTYPE:	0x%08x\n", mci_readl(host, CTYPE));
	dev_err(host->dev, ": BLKSIZ:	0x%08x\n", mci_readl(host, BLKSIZ));
	dev_err(host->dev, ": BYTCNT:	0x%08x\n", mci_readl(host, BYTCNT));
	dev_err(host->dev, ": INTMSK:	0x%08x\n", mci_readl(host, INTMASK));
	dev_err(host->dev, ": CMDARG:	0x%08x\n", mci_readl(host, CMDARG));
	dev_err(host->dev, ": CMD:	0x%08x\n", mci_readl(host, CMD));
	dev_err(host->dev, ": MINTSTS:	0x%08x\n", mci_readl(host, MINTSTS));
	dev_err(host->dev, ": RINTSTS:	0x%08x\n", mci_readl(host, RINTSTS));
	dev_err(host->dev, ": STATUS:	0x%08x\n", mci_readl(host, STATUS));
	dev_err(host->dev, ": FIFOTH:	0x%08x\n", mci_readl(host, FIFOTH));
	dev_err(host->dev, ": CDETECT:	0x%08x\n", mci_readl(host, CDETECT));
	dev_err(host->dev, ": WRTPRT:	0x%08x\n", mci_readl(host, WRTPRT));
	dev_err(host->dev, ": GPIO:	0x%08x\n", mci_readl(host, GPIO));
	dev_err(host->dev, ": TCBCNT:	0x%08x\n", mci_readl(host, TCBCNT));
	dev_err(host->dev, ": TBBCNT:	0x%08x\n", mci_readl(host, TBBCNT));
	dev_err(host->dev, ": DEBNCE:	0x%08x\n", mci_readl(host, DEBNCE));
	dev_err(host->dev, ": USRID:	0x%08x\n", mci_readl(host, USRID));
	dev_err(host->dev, ": VERID:	0x%08x\n", mci_readl(host, VERID));
	dev_err(host->dev, ": HCON:	0x%08x\n", mci_readl(host, HCON));
	dev_err(host->dev, ": UHS_REG:	0x%08x\n", mci_readl(host, UHS_REG));
	dev_err(host->dev, ": BMOD:	0x%08x\n", mci_readl(host, BMOD));
	dev_err(host->dev, ": PLDMND:	0x%08x\n", mci_readl(host, PLDMND));
	if(SDMMC_32_BIT_DMA == host->dma_64bit_address) {
	        dev_err(host->dev, ": DBADDR:	0x%08x\n", mci_readl(host, DBADDR));
	        dev_err(host->dev, ": IDSTS:    0x%08x\n", mci_readl(host, IDSTS));
	        dev_err(host->dev, ": IDINTEN:	0x%08x\n", mci_readl(host, IDINTEN));
	        dev_err(host->dev, ": DSCADDR:	0x%08x\n", mci_readl(host, DSCADDR));
	        dev_err(host->dev, ": BUFADDR:	0x%08x\n", mci_readl(host, BUFADDR));
	} else {
	        dev_err(host->dev, ": DBADDRL:	0x%08x\n", mci_readl(host, DBADDRL));
	        dev_err(host->dev, ": DBADDRU:	0x%08x\n", mci_readl(host, DBADDRU));
	        dev_err(host->dev, ": IDSTS:    0x%08x\n", mci_readl(host, IDSTS_64DMA));
	        dev_err(host->dev, ": IDINTEN:	0x%08x\n", mci_readl(host, IDINTEN_64DMA));
	}
	dev_err(host->dev, ": CARDTHRCTL: 	0x%08x\n", mci_readl(host, CARDTHRCTL));
	dev_err(host->dev, ": UHS_REG_EXT:	0x%08x\n", mci_readl(host, UHS_REG_EXT));
	dev_err(host->dev, ": ============== STATUS DUMP ================\n");
	dev_err(host->dev, ": cmd_status:      0x%08x\n", host->cmd_status);
	dev_err(host->dev, ": data_status:     0x%08x\n", host->data_status);
	dev_err(host->dev, ": pending_events:  0x%08lx\n", host->pending_events);
	dev_err(host->dev, ": completed_events:0x%08lx\n", host->completed_events);
	dev_err(host->dev, ": state:           %d\n", host->state);
	dev_err(host->dev, ": ===========================================\n");

	/* summary */
	mintsts = mci_readl(host, MINTSTS);
	status = mci_readl(host, STATUS);
	dev_err(host->dev, "CMD%d, ARG=0x%08x, intsts : %s, status : %s.\n",
			mci_readl(host, CMD) & 0x3F,
			mci_readl(host, CMDARG),
			mintsts & 0x8 ? "Data transfer done" : \
			mintsts & 0x4 ? "Command Done" : "refer to dump",
			status & (0x1 << 9) ? "dat0 busy" : "refer to dump");
	dev_err(host->dev, ": RESP0:	0x%08x\n", mci_readl(host, RESP0));
	dev_err(host->dev, ": RESP1:	0x%08x\n", mci_readl(host, RESP1));
	dev_err(host->dev, ": RESP2:	0x%08x\n", mci_readl(host, RESP2));
	dev_err(host->dev, ": RESP3:	0x%08x\n", mci_readl(host, RESP3));
	dev_err(host->dev, ": host : cmd_status=0x%08x, data_status=0x%08x.\n",
			host->cmd_status, host->data_status);
	dev_err(host->dev, ": host : pending_events=0x%08lx, "
			"completed_events=0x%08lx.\n",
			host->pending_events, host->completed_events);
	dev_err(host->dev, ": ===========================================\n");
}

void dw_mci_reg_dump_fortrace(struct mmc_host *mmc)
{
	u32 status, mintsts;
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;

	pm_runtime_get_sync(mmc_dev(mmc));

	mmc_trace_comm_record (mmc, ": =========== REGISTER DUMP (%s)===========\n",
				mmc_hostname(mmc));

	mmc_trace_comm_record(mmc, ": ============== REGISTER DUMP ==============\n");
	mmc_trace_comm_record(mmc, ": CTRL:	0x%x\n", mci_readl(host, CTRL));
	mmc_trace_comm_record(mmc, ": PWREN:	0x%x\n", mci_readl(host, PWREN));
	mmc_trace_comm_record(mmc, ": CLKDIV:	0x%x\n", mci_readl(host, CLKDIV));
	mmc_trace_comm_record(mmc, ": CLKSRC:	0x%x\n", mci_readl(host, CLKSRC));
	mmc_trace_comm_record(mmc, ": CLKENA:	0x%x\n", mci_readl(host, CLKENA));
	mmc_trace_comm_record(mmc, ": TMOUT:	0x%x\n", mci_readl(host, TMOUT));
	mmc_trace_comm_record(mmc, ": CTYPE:	0x%x\n", mci_readl(host, CTYPE));
	mmc_trace_comm_record(mmc, ": BLKSIZ:	0x%x\n", mci_readl(host, BLKSIZ));
	mmc_trace_comm_record(mmc, ": BYTCNT:	0x%x\n", mci_readl(host, BYTCNT));
	mmc_trace_comm_record(mmc, ": INTMSK:	0x%x\n", mci_readl(host, INTMASK));
	mmc_trace_comm_record(mmc, ": CMDARG:	0x%x\n", mci_readl(host, CMDARG));
	mmc_trace_comm_record(mmc, ": CMD:	0x%x\n", mci_readl(host, CMD));
	mmc_trace_comm_record(mmc, ": MINTSTS:	0x%x\n", mci_readl(host, MINTSTS));
	mmc_trace_comm_record(mmc, ": RINTSTS:	0x%x\n", mci_readl(host, RINTSTS));
	mmc_trace_comm_record(mmc, ": STATUS:	0x%x\n", mci_readl(host, STATUS));
	mmc_trace_comm_record(mmc, ": FIFOTH:	0x%x\n", mci_readl(host, FIFOTH));
	mmc_trace_comm_record(mmc, ": CDETECT:	0x%x\n", mci_readl(host, CDETECT));
	mmc_trace_comm_record(mmc, ": WRTPRT:	0x%x\n", mci_readl(host, WRTPRT));
	mmc_trace_comm_record(mmc, ": GPIO:	0x%x\n", mci_readl(host, GPIO));
	mmc_trace_comm_record(mmc, ": TCBCNT:	0x%x\n", mci_readl(host, TCBCNT));
	mmc_trace_comm_record(mmc, ": TBBCNT:	0x%x\n", mci_readl(host, TBBCNT));
	mmc_trace_comm_record(mmc, ": DEBNCE:	0x%x\n", mci_readl(host, DEBNCE));
	mmc_trace_comm_record(mmc, ": USRID:	0x%x\n", mci_readl(host, USRID));
	mmc_trace_comm_record(mmc, ": VERID:	0x%x\n", mci_readl(host, VERID));
	mmc_trace_comm_record(mmc, ": HCON:	0x%x\n", mci_readl(host, HCON));
	mmc_trace_comm_record(mmc, ": UHS_REG:	0x%x\n", mci_readl(host, UHS_REG));
	mmc_trace_comm_record(mmc, ": BMOD:	0x%08x\n", mci_readl(host, BMOD));
	mmc_trace_comm_record(mmc, ": PLDMND:	0x%x\n", mci_readl(host, PLDMND));
	mmc_trace_comm_record(mmc, ": DBADDR:	0x%x\n", mci_readl(host, DBADDR));
	mmc_trace_comm_record(mmc, ": IDSTS:	0x%x\n", mci_readl(host, IDSTS));
	mmc_trace_comm_record(mmc, ": IDINTEN:	0x%x\n", mci_readl(host, IDINTEN));
	mmc_trace_comm_record(mmc, ": DSCADDR:	0x%x\n", mci_readl(host, DSCADDR));
	mmc_trace_comm_record(mmc, ": BUFADDR:	0x%x\n", mci_readl(host, BUFADDR));
	mmc_trace_comm_record(mmc, ": CARDTHRCTL: 	0x%x\n", mci_readl(host, CARDTHRCTL));
	mmc_trace_comm_record(mmc, ": UHS_REG_EXT:	0x%x\n", mci_readl(host, UHS_REG_EXT));
	mmc_trace_comm_record(mmc, ": ============== STATUS DUMP ================\n");
	mmc_trace_comm_record(mmc, ": cmd_status:      0x%x\n", host->cmd_status);
	mmc_trace_comm_record(mmc, ": data_status:     0x%x\n", host->data_status);
	mmc_trace_comm_record(mmc, ": pending_events:  0x%x\n", host->pending_events);
	mmc_trace_comm_record(mmc, ": completed_events:0x%x\n", host->completed_events);
	mmc_trace_comm_record(mmc, ": state:           %d\n", host->state);
	mmc_trace_comm_record(mmc, ": ===========================================\n");

	/* summary */
	mintsts = mci_readl(host, MINTSTS);
	status = mci_readl(host, STATUS);
	mmc_trace_comm_record(mmc, "CMD%d, ARG=0x%x, intsts : %s, status : %s.\n",
			mci_readl(host, CMD) & 0x3F,
			mci_readl(host, CMDARG),
			mintsts & 0x8 ? "Data transfer done" : \
			mintsts & 0x4 ? "Command Done" : "refer to dump",
			status & (0x1 << 9) ? "dat0 busy" : "refer to dump");
	mmc_trace_comm_record(mmc, ": RESP0:	0x%x\n", mci_readl(host, RESP0));
	mmc_trace_comm_record(mmc, ": RESP1:	0x%x\n", mci_readl(host, RESP1));
	mmc_trace_comm_record(mmc, ": RESP2:	0x%x\n", mci_readl(host, RESP2));
	mmc_trace_comm_record(mmc, ": RESP3:	0x%x\n", mci_readl(host, RESP3));
	mmc_trace_comm_record(mmc, ": host : cmd_status=0x%x, data_status=0x%x.\n",
			host->cmd_status, host->data_status);
	mmc_trace_comm_record(mmc, ": host : pending_events=0x%x, "
			"completed_events=0x%x.\n",
			host->pending_events, host->completed_events);

	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));

	mmc_trace_comm_record(mmc, ": ===========================================\n");
}

static void dw_mci_set_timeout(struct dw_mci *host)
{
	/* timeout (maximum) */
	mci_writel(host, TMOUT, 0xffffffff);
}

static inline bool dw_mci_stop_abort_cmd(struct mmc_command *cmd)
{
	u32 op = cmd->opcode;

	if ((op == MMC_STOP_TRANSMISSION) ||
	    (op == MMC_GO_IDLE_STATE) ||
	    (op == MMC_GO_INACTIVE_STATE) ||
	    ((op == SD_IO_RW_DIRECT) && (cmd->arg & 0x80000000) &&
	     ((cmd->arg >> 9) & 0x1FFFF) == SDIO_CCCR_ABORT))
		return true;
	return false;
}

static u32 dw_mci_prepare_command(struct mmc_host *mmc, struct mmc_command *cmd)
{
	struct mmc_data	*data;
	struct dw_mci_slot *slot = mmc_priv(mmc);
	const struct dw_mci_drv_data *drv_data = slot->host->drv_data;
	u32 cmdr;
	cmd->error = -EINPROGRESS;

	cmdr = cmd->opcode;

	if (cmdr == SD_SWITCH_VOLTAGE)
		cmdr |= SDMMC_VOLT_SWITCH;
	if (cmdr == MMC_STOP_TRANSMISSION)
		cmdr |= SDMMC_CMD_STOP;
	else
		cmdr |= SDMMC_CMD_PRV_DAT_WAIT;

	if (cmd->flags & MMC_RSP_PRESENT) {
		/* We expect a response, so set this bit */
		cmdr |= SDMMC_CMD_RESP_EXP;
		if (cmd->flags & MMC_RSP_136)
			cmdr |= SDMMC_CMD_RESP_LONG;
	}

	if (cmd->flags & MMC_RSP_CRC)
		cmdr |= SDMMC_CMD_RESP_CRC;

	data = cmd->data;
	if (data) {
		cmdr |= SDMMC_CMD_DAT_EXP;
		if (data->flags & MMC_DATA_STREAM)
			cmdr |= SDMMC_CMD_STRM_MODE;
		if (data->flags & MMC_DATA_WRITE)
			cmdr |= SDMMC_CMD_DAT_WR;
	}

	if (drv_data && drv_data->prepare_command)
		drv_data->prepare_command(slot->host, &cmdr);

	return cmdr;
}

static u32 dw_mci_prep_stop(struct dw_mci *host, struct mmc_command *cmd)
{
	struct mmc_command *stop = &host->stop;
	const struct dw_mci_drv_data *drv_data = host->drv_data;
	u32 cmdr = cmd->opcode;

	memset(stop, 0, sizeof(struct mmc_command));

	if(cmdr == SD_IO_RW_EXTENDED) {
		stop->opcode = SD_IO_RW_DIRECT;
		stop->arg = 0x80000000;
		stop->arg |= (cmd->arg >> 28) & 0x7;
		stop->arg |= SDIO_CCCR_ABORT << 9;
		stop->flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_AC;
	} else {
		stop->opcode = MMC_STOP_TRANSMISSION;
		stop->arg = 0;
		stop->flags = MMC_RSP_R1B | MMC_CMD_AC;
	}

	cmdr = stop->opcode | SDMMC_CMD_STOP |
		SDMMC_CMD_RESP_CRC | SDMMC_CMD_RESP_EXP;

	/* Use hold bit register */
	if (drv_data && drv_data->prepare_command)
		drv_data->prepare_command(host, &cmdr);

	return cmdr;
}

static void dw_mci_start_command(struct dw_mci *host,
				 struct mmc_command *cmd, u32 cmd_flags)
{
	host->cmd = cmd;
	dev_vdbg(host->dev,
		 "start command: ARGR=0x%08x CMDR=0x%08x\n",
		 cmd->arg, cmd_flags);

	if (cmd->opcode == SD_SWITCH_VOLTAGE) {
		int loop_count;
		u32 temp;

		temp = mci_readl(host, INTMASK);
		temp &= ~SDMMC_INT_RESP_ERR;
		mci_writel(host, INTMASK, temp);
		cmd_flags |= SDMMC_VOLT_SWITCH;

		/* disable clock low power */
		mci_writel(host, CLKENA, (0x1<<0));
		mci_writel(host, CMD , SDMMC_CMD_ONLY_CLK | SDMMC_VOLT_SWITCH);
		loop_count = 0x100000;
		do {
			if (!(mci_readl(host, CMD) & SDMMC_CMD_START))
				break;
			loop_count--;
		} while (loop_count);
		if (!loop_count)
			dev_err(host->dev, "disable clk low power failed in volt_switch\n");

	}
	mci_writel(host, CMDARG, cmd->arg);
	wmb();

	mci_writel(host, CMD, cmd_flags | SDMMC_CMD_START);
}

static void send_stop_cmd(struct dw_mci *host, struct mmc_data *data)
{
	dw_mci_start_command(host, data->stop, host->stop_cmdr);
}

/* DMA interface functions */
static void dw_mci_stop_dma(struct dw_mci *host)
{
	if (host->using_dma) {
		host->dma_ops->stop(host);
		host->dma_ops->cleanup(host);
		host->dma_ops->reset(host);
	} else {
		/* Data transfer was stopped by the interrupt handler */
		set_bit(EVENT_XFER_COMPLETE, &host->pending_events);
	}
}

static int dw_mci_get_dma_dir(struct mmc_data *data)
{
	if (data->flags & MMC_DATA_WRITE)
		return DMA_TO_DEVICE;
	else
		return DMA_FROM_DEVICE;
}

static bool dw_mci_wait_reset(struct device *dev, struct dw_mci *host,
		unsigned int reset_val)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(500);
	unsigned int ctrl;

	ctrl = mci_readl(host, CTRL);
	ctrl |= reset_val;
	mci_writel(host, CTRL, ctrl);

	/* wait till resets clear */
	do {
		if (!(mci_readl(host, CTRL) & reset_val))
			return true;
	} while (time_before(jiffies, timeout));

	dev_err(dev, "Timeout resetting block (ctrl %#x)\n", ctrl);

	return false;
}

static int mci_send_cmd(struct dw_mci_slot *slot, u32 cmd, u32 arg)
{
	struct dw_mci *host = slot->host;
	unsigned long timeout = jiffies + msecs_to_jiffies(500);
	unsigned int cmd_status = 0;
	int try = 3;

	mci_writel(host, CMDARG, arg);
	wmb();
	mci_writel(host, CMD, SDMMC_CMD_START | cmd);

	do {
		while (time_before(jiffies, timeout)) {
			cmd_status = mci_readl(host, CMD);
			if (!(cmd_status & SDMMC_CMD_START))
				return 0;
		}

		dw_mci_wait_reset(host->dev, host, SDMMC_CTRL_RESET);
		mci_writel(host, CMD, SDMMC_CMD_START | cmd);
		timeout = jiffies + msecs_to_jiffies(500);
	} while (--try);

	dev_err(&slot->mmc->class_dev,
		"Timeout sending command (cmd %#x arg %#x status %#x)\n",
		cmd, arg, cmd_status);
	return 1;
}

static void dw_mci_ciu_reset(struct device *dev, struct dw_mci *host)
{
	struct dw_mci_slot *slot = host->cur_slot;

	if (slot) {
		dw_mci_wait_reset(dev, host, SDMMC_CTRL_RESET);
		mci_send_cmd(slot, SDMMC_CMD_UPD_CLK |
			SDMMC_CMD_PRV_DAT_WAIT, 0);
	}
}

static bool dw_mci_fifo_reset(struct device *dev, struct dw_mci *host)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);
	unsigned int ctrl;
	bool result;

	do {
		result = dw_mci_wait_reset(host->dev, host, SDMMC_CTRL_FIFO_RESET);

		if (!result)
			break;

		ctrl = mci_readl(host, STATUS);
		if (!(ctrl & SDMMC_STATUS_DMA_REQ)) {
			result = dw_mci_wait_reset(host->dev, host,
					SDMMC_CTRL_FIFO_RESET);
			if (result) {
				/* clear exception raw interrupts can not be handled
				   ex) fifo full => RXDR interrupt rising */
				ctrl = mci_readl(host, RINTSTS);
				ctrl = ctrl & ~(mci_readl(host, MINTSTS));
				if (ctrl)
					mci_writel(host, RINTSTS, ctrl);

				return true;
			}
		}
	} while (time_before(jiffies, timeout));

	dev_err(dev, "%s: Timeout while resetting host controller after err\n",
		__func__);

	return false;
}

#ifdef CONFIG_MMC_DW_IDMAC
static void dw_mci_dma_cleanup(struct dw_mci *host)
{
	struct mmc_data *data = host->data;

	if (data)
		if (!data->host_cookie)
			dma_unmap_sg(host->dev,
				     data->sg,
				     data->sg_len,
				     dw_mci_get_dma_dir(data));
}

static void dw_mci_idmac_stop_dma(struct dw_mci *host)
{
	u32 temp;

	/* Disable and reset the IDMAC interface */
	temp = mci_readl(host, CTRL);
	temp &= ~SDMMC_CTRL_USE_IDMAC;
	mci_writel(host, CTRL, temp);

	/* reset the IDMAC interface */
	dw_mci_wait_reset(host->dev, host, SDMMC_CTRL_DMA_RESET);

	/* Stop the IDMAC running */
	temp = mci_readl(host, BMOD);
	temp &= ~(SDMMC_IDMAC_ENABLE | SDMMC_IDMAC_FB);
	mci_writel(host, BMOD, temp);
}

static void dw_mci_idma_reset_dma(struct dw_mci *host)
{
	u32 temp;

	temp = mci_readl(host, BMOD);
	/* Software reset of DMA */
	temp |= SDMMC_IDMAC_SWRESET;
	mci_writel(host, BMOD, temp);
}

static void dw_mci_idmac_complete_dma(struct dw_mci *host)
{
	struct mmc_data *data = host->data;

	dev_vdbg(host->dev, "DMA complete\n");
	if ((1 == host->use_dma) &&
	    data && (data->flags & MMC_DATA_READ))
		/* Invalidate cache after read */
		dma_sync_sg_for_cpu(mmc_dev(host->cur_slot->mmc),
				    data->sg,
				    data->sg_len,
				    DMA_FROM_DEVICE);

	host->dma_ops->cleanup(host);

	/*
	 * If the card was removed, data will be NULL. No point in trying to
	 * send the stop command or waiting for NBUSY in this case.
	 */
	if (data) {
		set_bit(EVENT_XFER_COMPLETE, &host->pending_events);
		tasklet_schedule(&host->tasklet);
	}
}

static void dw_mci_translate_sglist(struct dw_mci *host, struct mmc_data *data,
				    unsigned int sg_len)
{
	unsigned int desc_len;
	if(SDMMC_32_BIT_DMA == host->dma_64bit_address) {
		int i;
		struct idmac_desc *desc = host->sg_cpu;

		if (!sg_len)
			return;

		for (i = 0; i < sg_len; i++, desc++) {
			unsigned int length = sg_dma_len(&data->sg[i]);
			u32 mem_addr = sg_dma_address(&data->sg[i]);

			/* Set the OWN bit and disable interrupts for this descriptor */
			desc->des0 = IDMAC_DES0_OWN | IDMAC_DES0_DIC | IDMAC_DES0_CH;
			/*优化修改，防止内存不初始化*/
			if(desc->des0 & IDMAC_DES0_CH) {
				desc->des1 = 0;
			}

			/*优化修改，防止内存不初始化*/
			if(desc->des0 & IDMAC_DES0_CH) {
				desc->des1 = 0;
			}

			/* Buffer length */
			IDMAC_SET_BUFFER1_SIZE(desc, length);

			/* Physical address to DMA to/from */
			desc->des2 = mem_addr;
		}

		/* Set first descriptor */
		desc = host->sg_cpu;
		desc->des0 |= IDMAC_DES0_FD;

		/* Set last descriptor */
		desc = host->sg_cpu + (i - 1) * sizeof(struct idmac_desc);
		desc->des0 &= ~(IDMAC_DES0_CH | IDMAC_DES0_DIC);
		desc->des0 |= IDMAC_DES0_LD;

		wmb();
	} else {
		int i;

		struct idmac_desc_64bit *desc_first, *desc_last, *desc;

		desc_first = desc_last = desc = host->sg_cpu;

		if (!sg_len)
			return;

		for (i = 0; i < sg_len; i++) {
			unsigned int length = sg_dma_len(&data->sg[i]);
			u64 mem_addr = sg_dma_address(&data->sg[i]);

			for ( ; length ; desc++) {
				desc_len = (length <= DW_MCI_DESC_DATA_LENGTH) ?
					   length : DW_MCI_DESC_DATA_LENGTH;

				length -= desc_len;
				/* Set the OWN bit and disable interrupts for this descriptor */
				desc->des0 = IDMAC_DES0_OWN | IDMAC_DES0_DIC | IDMAC_DES0_CH;

				/*优化修改，防止内存不初始化*/
				if(desc->des0 & IDMAC_DES0_CH) {
				        desc->des2 = 0;
				}

				/*优化修改，防止内存不初始化*/
				if(desc->des0 & IDMAC_DES0_CH) {
				        desc->des2 = 0;
				}


				/* Buffer length */
				IDMAC_64ADDR_SET_BUFFER1_SIZE(desc, desc_len);

				/* Physical address to DMA to/from */
				desc->des4 = mem_addr & 0xffffffff;
				desc->des5 = mem_addr >> 32;
				/* Update physical address for the next desc */
				mem_addr += desc_len;

				/* Save pointer to the last descriptor */
				desc_last = desc;
			}
		}

		/* Set first descriptor */
		desc_first->des0 |= IDMAC_DES0_FD;

		/* Set last descriptor */
		desc_last->des0 &= ~(IDMAC_DES0_CH | IDMAC_DES0_DIC);
		desc_last->des0 |= IDMAC_DES0_LD;

		wmb();
	}
}

static void dw_mci_idmac_start_dma(struct dw_mci *host, unsigned int sg_len)
{
	u32 temp;

	dw_mci_translate_sglist(host, host->data, sg_len);

	/* Select IDMAC interface */
	temp = mci_readl(host, CTRL);
	temp |= SDMMC_CTRL_USE_IDMAC;
	mci_writel(host, CTRL, temp);

	wmb();

#ifdef CONFIG_ARM64
#endif
	/* Enable the IDMAC */
	temp = mci_readl(host, BMOD);
	temp |= SDMMC_IDMAC_ENABLE | SDMMC_IDMAC_FB;
	mci_writel(host, BMOD, temp);

	/* Start it running */
	mci_writel(host, PLDMND, 1);
}

static int dw_mci_idmac_init(struct dw_mci *host)
{
	if(SDMMC_32_BIT_DMA == host->dma_64bit_address) {
		struct idmac_desc *p;
		int i;

		/* Number of descriptors in the ring buffer */
		host->ring_size = host->desc_sz * PAGE_SIZE / sizeof(struct idmac_desc);

		/* Forward link the descriptor list */
		for (i = 0, p = host->sg_cpu; i < host->ring_size - 1; i++, p++)
		    p->des3 = host->sg_dma + (sizeof(struct idmac_desc) * (i + 1));

		/* Set the last descriptor as the end-of-ring descriptor */
		p->des3 = host->sg_dma;
		p->des0 = IDMAC_DES0_ER;

		mci_writel(host, BMOD, SDMMC_IDMAC_SWRESET);

		/* Mask out interrupts - get Tx & Rx complete only */
#ifdef CONFIG_MMC_DW_IDMAC
		mci_writel(host, IDSTS, IDMAC_INT_CLR);
		mci_writel(host, IDINTEN, SDMMC_IDMAC_INT_NI | SDMMC_IDMAC_INT_RI |
			SDMMC_IDMAC_INT_TI);
#endif
		/* Set the descriptor base address */
		mci_writel(host, DBADDR, host->sg_dma);
		return 0;
	} else {
		struct idmac_desc_64bit *p;
		int i;

		/* Number of descriptors in the ring buffer */
		host->ring_size = host->desc_sz * PAGE_SIZE / sizeof(struct idmac_desc_64bit);

		/* Forward link the descriptor list */
		for (i = 0, p = host->sg_cpu; i < host->ring_size - 1; i++, p++) {
			p->des6 = (host->sg_dma + (sizeof(struct idmac_desc_64bit) * (i + 1)))& 0xffffffff;
			p->des7 = (host->sg_dma + (sizeof(struct idmac_desc_64bit) * (i + 1)))>> 32;
			p->des1 = 0;
			p->des2 = 0;
			p->des3 = 0;
		}
		/* Set the last descriptor as the end-of-ring descriptor */
		p->des6 = host->sg_dma & 0xffffffff;
		p->des7 = (u64)host->sg_dma >> 32;
		p->des0 = IDMAC_DES0_ER;

		mci_writel(host, BMOD, SDMMC_IDMAC_SWRESET);
		/* Mask out interrupts - get Tx & Rx complete only */
		mci_writel(host, IDSTS_64DMA, IDMAC_INT_CLR);
		mci_writel(host, IDINTEN_64DMA, SDMMC_IDMAC_INT_NI | SDMMC_IDMAC_INT_RI | SDMMC_IDMAC_INT_TI);
		/* Set the descriptor base address */
		mci_writel(host, DBADDRL, host->sg_dma & 0xffffffff);
		mci_writel(host, DBADDRU,(u64)host->sg_dma >> 32);
		return 0;
	}
}

static const struct dw_mci_dma_ops dw_mci_idmac_ops = {
	.init = dw_mci_idmac_init,
	.start = dw_mci_idmac_start_dma,
	.stop = dw_mci_idmac_stop_dma,
	.reset = dw_mci_idma_reset_dma,
	.complete = dw_mci_idmac_complete_dma,
	.cleanup = dw_mci_dma_cleanup,
};
#endif /* CONFIG_MMC_DW_IDMAC */

static int dw_mci_pre_dma_transfer(struct dw_mci *host,
				   struct mmc_data *data,
				   bool next)
{
	struct scatterlist *sg;
	unsigned int i, sg_len;

	if (!next && data->host_cookie)
		return data->host_cookie;

	/*
	 * We don't do DMA on "complex" transfers, i.e. with
	 * non-word-aligned buffers or lengths. Also, we don't bother
	 * with all the DMA setup overhead for short transfers.
	 */
	if (data->blocks * data->blksz < DW_MCI_DMA_THRESHOLD)
		return -EINVAL;

	if (data->blksz & 3)
		return -EINVAL;

	for_each_sg(data->sg, sg, data->sg_len, i) {
		if (sg->offset & 3 || sg->length & 3)
			return -EINVAL;
	}

	sg_len = dma_map_sg(host->dev,
			    data->sg,
			    data->sg_len,
			    dw_mci_get_dma_dir(data));
	if (sg_len == 0)
		return -EINVAL;

	if (next)
		data->host_cookie = sg_len;

	return sg_len;
}

static void dw_mci_pre_req(struct mmc_host *mmc,
			   struct mmc_request *mrq,
			   bool is_first_req)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct mmc_data *data = mrq->data;

	if (!slot->host->use_dma || !data)
		return;

	if (data->host_cookie) {
		data->host_cookie = 0;
		return;
	}

	if (dw_mci_pre_dma_transfer(slot->host, mrq->data, 1) < 0)
		data->host_cookie = 0;
}

static void dw_mci_post_req(struct mmc_host *mmc,
			    struct mmc_request *mrq,
			    int err)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct mmc_data *data = mrq->data;

	if (!slot->host->use_dma || !data)
		return;

	if (data->host_cookie)
		dma_unmap_sg(slot->host->dev,
			     data->sg,
			     data->sg_len,
			     dw_mci_get_dma_dir(data));
	data->host_cookie = 0;
}

static void dw_mci_adjust_fifoth(struct dw_mci *host, struct mmc_data *data)
{
#ifdef CONFIG_MMC_DW_IDMAC
	unsigned int blksz = data->blksz;
	const u32 mszs[] = { 1, 4, 8, 16, 32, 64, 128, 256 };
	u32 fifo_width = 1 << host->data_shift;
	u32 blksz_depth = blksz / fifo_width, fifoth_val;
	u32 msize = 0, rx_wmark = 1, tx_wmark, tx_wmark_invers;
	int idx = (sizeof(mszs) / sizeof(mszs[0])) - 1;

	tx_wmark = (host->fifo_depth) / 2;
	tx_wmark_invers = host->fifo_depth - tx_wmark;

	/*
	 * MSIZE is '1',
	 * if blksz is not a multiple of the FIFO width
	 */
	if (blksz % fifo_width) {
		msize = 0;
		rx_wmark = 1;
		goto done;
	}

	do {
		if (!((blksz_depth % mszs[idx]) ||
		      (tx_wmark_invers % mszs[idx]))) {
			msize = idx;
			rx_wmark = mszs[idx] - 1;
			break;
		}
	} while (--idx > 0);
	/*
	 * If idx is '0', it won't be tried
	 * Thus, initial values are uesed
	 */
done:
	fifoth_val = SDMMC_SET_FIFOTH(msize, rx_wmark, tx_wmark);
	mci_writel(host, FIFOTH, fifoth_val);
#endif
}

static void dw_mci_ctrl_rd_thld(struct dw_mci *host, struct mmc_data *data)
{
	unsigned int blksz = data->blksz;
	u32 blksz_depth, fifo_depth;
	u16 thld_size;

	WARN_ON(!(data->flags & MMC_DATA_READ));

	if (host->cur_slot->mmc->ios.timing != MMC_TIMING_MMC_HS200 &&
	    host->cur_slot->mmc->ios.timing != MMC_TIMING_UHS_SDR104)
		goto disable;

	blksz_depth = blksz / (1 << host->data_shift);
	fifo_depth = host->fifo_depth;

	if (blksz_depth > fifo_depth)
		goto disable;

	/*
	 * If (blksz_depth) >= (fifo_depth >> 1), should be 'thld_size <= blksz'
	 * If (blksz_depth) <  (fifo_depth >> 1), should be thld_size = blksz
	 * Currently just choose blksz.
	 */
	thld_size = blksz;
	mci_writel(host, CARDTHRCTL, SDMMC_SET_RD_THLD(thld_size, 1));
	return;

disable:
	mci_writel(host, CARDTHRCTL, SDMMC_SET_RD_THLD(0, 0));
}

static int dw_mci_submit_data_dma(struct dw_mci *host, struct mmc_data *data)
{
	int sg_len;
	u32 temp;

	host->using_dma = 0;

	/* If we don't have a channel, we can't do DMA */
	if (!host->use_dma)
		return -ENODEV;

	sg_len = dw_mci_pre_dma_transfer(host, data, 0);
	if (sg_len < 0) {
		host->dma_ops->stop(host);
		return sg_len;
	}

	host->using_dma = 1;

	dev_vdbg(host->dev,
		 "sd sg_cpu: %#lx sg_dma: %#lx sg_len: %d\n",
		 (unsigned long)host->sg_cpu, (unsigned long)host->sg_dma,
		 sg_len);

	/*
	 * Decide the MSIZE and RX/TX Watermark.
	 * If current block size is same with previous size,
	 * no need to update fifoth.
	 */
	if (host->prev_blksz != data->blksz)
		dw_mci_adjust_fifoth(host, data);

#if 0
	/* Enable the DMA interface */
	temp = mci_readl(host, CTRL);
	temp |= SDMMC_CTRL_DMA_ENABLE;
	mci_writel(host, CTRL, temp);
#endif
	/* Disable RX/TX IRQs, let DMA handle it */
	temp = mci_readl(host, INTMASK);
	temp  &= ~(SDMMC_INT_RXDR | SDMMC_INT_TXDR);
	mci_writel(host, INTMASK, temp);

	host->dma_ops->start(host, sg_len);

	return 0;
}

static void dw_mci_submit_data(struct dw_mci *host, struct mmc_data *data)
{
	u32 temp;

	data->error = -EINPROGRESS;

	WARN_ON(host->data);
	host->sg = NULL;
	host->data = data;

	if (data->flags & MMC_DATA_READ){
		host->dir_status = DW_MCI_RECV_STATUS;
		dw_mci_ctrl_rd_thld(host,data);
	}
	else
		host->dir_status = DW_MCI_SEND_STATUS;

	if (dw_mci_submit_data_dma(host, data)) {
		int flags = SG_MITER_ATOMIC;
		if (host->data->flags & MMC_DATA_READ)
			flags |= SG_MITER_TO_SG;
		else
			flags |= SG_MITER_FROM_SG;

		sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);
		host->sg = data->sg;
		host->part_buf_start = 0;
		host->part_buf_count = 0;

		mci_writel(host, RINTSTS, SDMMC_INT_TXDR | SDMMC_INT_RXDR);
		temp = mci_readl(host, INTMASK);
		temp |= SDMMC_INT_TXDR | SDMMC_INT_RXDR;
		mci_writel(host, INTMASK, temp);

		temp = mci_readl(host, CTRL);
		temp &= ~SDMMC_CTRL_DMA_ENABLE;
		mci_writel(host, CTRL, temp);
		/*
		 * Use the initial fifoth_val for PIO mode.
		 * If next issued data may be transfered by DMA mode,
		 * prev_blksz should be invalidated.
		 */
		mci_writel(host, FIFOTH, host->fifoth_val);
		host->prev_blksz = 0;
	} else {
		/*
		 * Keep the current block size.
		 * It will be used to decide whether to update
		 * fifoth register next time.
		 */
		host->prev_blksz = data->blksz;
	}
}

static bool dw_mci_wait_data_busy(struct dw_mci *host, struct mmc_request *mrq)
{
	u32 status;
	unsigned long timeout = jiffies + msecs_to_jiffies(500);
	int try = 2;

	do {
		do {
			status = mci_readl(host, STATUS);
			if (!(status & SDMMC_DATA_BUSY))
				return true;

			usleep_range(10, 20);
		} while (time_before(jiffies, timeout));

		/* card is checked every 1s by CMD13 at least */
		if (mrq->cmd->opcode == MMC_SEND_STATUS)
			return true;

		dev_info(host->dev, "status is busy, reset ctrl\n");

		dw_mci_wait_reset(host->dev, host, SDMMC_CTRL_RESET);
		/* After CTRL Reset, Should be needed clk val to CIU */
		if (host->cur_slot)
			mci_send_cmd(host->cur_slot,
				SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT, 0);
		timeout = jiffies + msecs_to_jiffies(500);
	} while (--try);

	dev_err(host->dev, "Data[0]: data is busy\n");

	return false;
}

static void dw_mci_setup_bus(struct dw_mci_slot *slot, bool force_clkinit)
{
	struct dw_mci *host = slot->host;
	const struct dw_mci_drv_data *drv_data = slot->host->drv_data;
	u32 div;
	u32 clk_en_a;
	u32 ret = 0;
	u32 retry_times = 1;
	u32 i = 0;

	if (slot->clock != host->current_speed || force_clkinit) {
		div = host->bus_hz / slot->clock;
		if (host->bus_hz % slot->clock && host->bus_hz > slot->clock)
			/*
			 * move the + 1 after the divide to prevent
			 * over-clocking the card.
			 */
			div += 1;

		div = (host->bus_hz != slot->clock) ? DIV_ROUND_UP(div, 2) : 0;

		dev_info(&slot->mmc->class_dev,
			 "Bus speed (slot %d) = %dHz (slot req %dHz, actual %dHZ"
			 " div = %d)\n", slot->id, host->bus_hz, slot->clock,
			 div ? ((host->bus_hz / div) >> 1) : host->bus_hz, div);

retry:
		/* disable clock */
		mci_writel(host, CLKENA, 0);
		mci_writel(host, CLKSRC, 0);

		/* inform CIU */
		ret = mci_send_cmd(slot,
			     SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT, 0);
		if (ret && retry_times)
			goto reset;

		/* set clock to desired speed */
		mci_writel(host, CLKDIV, div);

		/* inform CIU */
		ret = mci_send_cmd(slot,
			     SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT, 0);
		if (ret && retry_times)
			goto reset;

		/* enable clock; only low power if no SDIO */
		clk_en_a = SDMMC_CLKEN_ENABLE << slot->id;
		if (!(mci_readl(host, INTMASK) & SDMMC_INT_SDIO(slot->id))
			&& (host->hw_mmc_id != DWMMC_SD_ID)
			&& mmc_host_wifi_support_lowpwr(slot->mmc))
			clk_en_a |= SDMMC_CLKEN_LOW_PWR << slot->id;
		mci_writel(host, CLKENA, clk_en_a);

		/* inform CIU */
		ret = mci_send_cmd(slot,
			     SDMMC_CMD_UPD_CLK | SDMMC_CMD_PRV_DAT_WAIT, 0);
		if (ret && retry_times)
			goto reset;

		host->current_speed = slot->clock;
reset:
		if (ret && retry_times) {
			udelay(100);
			for (i = 0; i < 1000; i++) {
				if (host->cmd_status & SDMMC_INT_HLE)
					mdelay(1);
				else
					break;
			}

			dev_err(host->dev, "need to reset ip\n");
			if (drv_data && drv_data->work_fail_reset)
				drv_data->work_fail_reset(host);
			retry_times = 0;
			goto retry;
		}
	}

	/* Set the current slot bus width */
	mci_writel(host, CTYPE, (slot->ctype << slot->id));
}

static void __dw_mci_start_request(struct dw_mci *host,
				   struct dw_mci_slot *slot,
				   struct mmc_command *cmd)
{
	struct mmc_request *mrq;
	struct mmc_data	*data;
	u32 cmdflags;

	mrq = slot->mrq;
	host->stop_snd = false;
	if (host->pdata->select_slot)
		host->pdata->select_slot(slot->id);

	/* Slot specific timing and width adjustment */
	dw_mci_setup_bus(slot, 0);

	if (host->flags & DWMMC_IN_TUNING){
		mod_timer(&host->timer, jiffies + msecs_to_jiffies(100));
	} else {
		if(DWMMC_EMMC_ID == host->hw_mmc_id) {
			/*add to 20s timeout for some write slow emmc*/
			mod_timer(&host->timer, jiffies + msecs_to_jiffies(20000));
#ifdef CONFIG_HUAWEI_EMMC_DSM
			mod_timer(&host->rw_to_timer, jiffies + msecs_to_jiffies(8000));
#endif
		} else if ((host->hw_mmc_id == DWMMC_SD_ID) && (slot->mmc->card)) {
			if (mmc_card_suspended(slot->mmc->card))
				mod_timer(&host->timer, jiffies + msecs_to_jiffies(2000));
			else
				mod_timer(&host->timer, jiffies + msecs_to_jiffies(10000));
		} else
			mod_timer(&host->timer, jiffies + msecs_to_jiffies(10000));
	}

	host->cur_slot = slot;
	host->mrq = mrq;

	host->pending_events = 0;
	host->completed_events = 0;
	host->data_status = 0;
	host->cmd_status = 0;
	host->dir_status = 0;
#ifdef CONFIG_HUAWEI_EMMC_DSM
	host->dmd_cmd_status = 0;
#endif

	data = cmd->data;
	if (data) {
		dw_mci_set_timeout(host);
		mci_writel(host, BYTCNT, data->blksz*data->blocks);
		mci_writel(host, BLKSIZ, data->blksz);
	}

	cmdflags = dw_mci_prepare_command(slot->mmc, cmd);

	/* this is the first command, send the initialization clock */
	if (test_and_clear_bit(DW_MMC_CARD_NEED_INIT, &slot->flags))
		cmdflags |= SDMMC_CMD_INIT;

	if (data) {
		dw_mci_submit_data(host, data);
		wmb();
	}

	dw_mci_start_command(host, cmd, cmdflags);

	if (mrq->stop)
		host->stop_cmdr = dw_mci_prepare_command(slot->mmc, mrq->stop);
	else {
		if (data)
			host->stop_cmdr = dw_mci_prep_stop(host, cmd);
	}
}

static void dw_mci_start_request(struct dw_mci *host,
				 struct dw_mci_slot *slot)
{
	struct mmc_request *mrq = slot->mrq;
	struct mmc_command *cmd;

	cmd = mrq->sbc ? mrq->sbc : mrq->cmd;
	__dw_mci_start_request(host, slot, cmd);
}

/* must be called with host->lock held */
static void dw_mci_queue_request(struct dw_mci *host, struct dw_mci_slot *slot,
				 struct mmc_request *mrq)
{
	dev_vdbg(&slot->mmc->class_dev, "queue request: state=%d\n",
		 host->state);

	slot->mrq = mrq;

	if (host->state == STATE_IDLE) {
		host->state = STATE_SENDING_CMD;
		dw_mci_start_request(host, slot);
	} else {
		list_add_tail(&slot->queue_node, &host->queue);
	}
}

static void dw_mci_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;

	WARN_ON(slot->mrq);


	/*
	 * The check for card presence and queueing of the request must be
	 * atomic, otherwise the card could be removed in between and the
	 * request wouldn't fail until another card was inserted.
	 */

	if (!test_bit(DW_MMC_CARD_PRESENT, &slot->flags)) {
		mrq->cmd->error = -ENOMEDIUM;
		mmc_request_done(mmc, mrq);
		return;
	}

	pm_runtime_get_sync(mmc_dev(mmc));

	if (!dw_mci_stop_abort_cmd(mrq->cmd)) {
		if (!dw_mci_wait_data_busy(host, mrq)) {
			dev_err(&mmc->class_dev, "wait data busy timeout !\n");
			mrq->cmd->error = -ENOTRECOVERABLE;
			mmc_request_done(mmc, mrq);
			pm_runtime_mark_last_busy(mmc_dev(mmc));
			pm_runtime_put_autosuspend(mmc_dev(mmc));
			return;
		}
	}

	spin_lock_bh(&host->lock);

	dw_mci_queue_request(host, slot, mrq);

	spin_unlock_bh(&host->lock);
}

static void dw_mci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	const struct dw_mci_drv_data *drv_data = slot->host->drv_data;
	u32 regs;

	pm_runtime_get_sync(mmc_dev(mmc));

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_4:
		slot->ctype = SDMMC_CTYPE_4BIT;
		break;
	case MMC_BUS_WIDTH_8:
		slot->ctype = SDMMC_CTYPE_8BIT;
		break;
	default:
		/* set default 1 bit mode */
		slot->ctype = SDMMC_CTYPE_1BIT;
	}

	regs = mci_readl(slot->host, UHS_REG);

	/* DDR mode set */
	if (ios->timing == MMC_TIMING_UHS_DDR50)
		regs |= ((0x1 << slot->id) << 16);
	else
		regs &= ~((0x1 << slot->id) << 16);

	if (slot->host->pdata->caps &
				(MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
				 MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 |
				 MMC_CAP_UHS_DDR50))
		regs |= (0x1 << slot->id);
	mci_writel(slot->host, UHS_REG, regs);

	if (ios->clock) {
		/*
		 * Use mirror of ios->clock to prevent race with mmc
		 * core ios update when finding the minimum.
		 */
		slot->clock = ios->clock;
	}

	if (drv_data && drv_data->set_ios)
		drv_data->set_ios(slot->host, ios);

	mmc->f_min = DIV_ROUND_UP(slot->host->bus_hz, 510);
	mmc->f_max = slot->host->bus_hz;/*上面设置的bus_hz*/

	/* Slot specific timing and width adjustment */
	dw_mci_setup_bus(slot, false);

	switch (ios->power_mode) {
	case MMC_POWER_UP:
		set_bit(DW_MMC_CARD_NEED_INIT, &slot->flags);
		/* Power up slot */
		if (slot->host->pdata->setpower)
			slot->host->pdata->setpower(slot->id, mmc->ocr_avail);
		regs = mci_readl(slot->host, PWREN);
		regs |= (1 << slot->id);
		mci_writel(slot->host, PWREN, regs);
		break;
	case MMC_POWER_OFF:
		/* Power down slot */
		if (slot->host->pdata->setpower)
			slot->host->pdata->setpower(slot->id, 0);
		regs = mci_readl(slot->host, PWREN);
		regs &= ~(1 << slot->id);
		mci_writel(slot->host, PWREN, regs);
		break;
	default:
		break;
	}

	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));
}

static int dw_mci_get_ro(struct mmc_host *mmc)
{
	int read_only;
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci_board *brd = slot->host->pdata;

	pm_runtime_get_sync(mmc_dev(mmc));

	/* Use platform get_ro function, else try on board write protect */
	if (slot->quirks & DW_MCI_SLOT_QUIRK_NO_WRITE_PROTECT)
		read_only = 0;
	else if (brd->get_ro)
		read_only = brd->get_ro(slot->id);
	else if (gpio_is_valid(slot->wp_gpio))
		read_only = gpio_get_value(slot->wp_gpio);
	else
		read_only =
			mci_readl(slot->host, WRTPRT) & (1 << slot->id) ? 1 : 0;

	dev_dbg(&mmc->class_dev, "card is %s\n",
		read_only ? "read-only" : "read-write");

	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));

	return read_only;
}

void dw_mci_set_cd(struct dw_mci *host){

	if(host == NULL)
		return;

	if(host->slot[0] && host->slot[0]->mmc){
		dev_dbg(&host->slot[0]->mmc->class_dev,"sdio_present = %d\n",host->slot[0]->mmc->sdio_present);
		host->slot[0]->mmc->sdio_present = 1;
	}
}
EXPORT_SYMBOL(dw_mci_set_cd);

static int dw_mci_get_cd(struct mmc_host *mmc)
{
	int present;
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;
	struct dw_mci_board *brd = slot->host->pdata;

	pm_runtime_get_sync(mmc_dev(mmc));

	/* Use platform get_cd function, else try onboard card detect */
	if (brd->quirks & DW_MCI_QUIRK_BROKEN_CARD_DETECTION)
		present = 1;
	else if (brd->get_cd)
		present = !brd->get_cd(slot->host, slot->id);
	else if (host->hw_mmc_id == DWMMC_SDIO_ID) {
		present = mmc->sdio_present;
	}
	else
		present = (mci_readl(slot->host, CDETECT) & (1 << slot->id))
			== 0 ? 1 : 0;

	if (present)
		dev_err(&mmc->class_dev, "card is present\n");
	else
		dev_err(&mmc->class_dev, "card is not present\n");

	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));

	return present;
}

/*
 * Disable lower power mode.
 *
 * Low power mode will stop the card clock when idle.  According to the
 * description of the CLKENA register we should disable low power mode
 * for SDIO cards if we need SDIO interrupts to work.
 *
 * This function is fast if low power mode is already disabled.
 */
static void dw_mci_disable_low_power(struct dw_mci_slot *slot)
{
	struct dw_mci *host = slot->host;
	u32 clk_en_a;
	const u32 clken_low_pwr = SDMMC_CLKEN_LOW_PWR << slot->id;

	clk_en_a = mci_readl(host, CLKENA);

	if (clk_en_a & clken_low_pwr) {
		mci_writel(host, CLKENA, clk_en_a & ~clken_low_pwr);
		mci_send_cmd(slot, SDMMC_CMD_UPD_CLK |
			     SDMMC_CMD_PRV_DAT_WAIT, 0);
	}
}

static void dw_mci_enable_sdio_irq(struct mmc_host *mmc, int enb)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;
	u32 int_mask;

	/* Enable/disable Slot Specific SDIO interrupt */
	int_mask = mci_readl(host, INTMASK);
	if (enb) {
		/*
		 * Turn off low power mode if it was enabled.  This is a bit of
		 * a heavy operation and we disable / enable IRQs a lot, so
		 * we'll leave low power mode disabled and it will get
		 * re-enabled again in dw_mci_setup_bus().
		 */
		dw_mci_disable_low_power(slot);

		mci_writel(host, INTMASK,
			   (int_mask | SDMMC_INT_SDIO(slot->id)));
	} else {
		mci_writel(host, INTMASK,
			   (int_mask & ~SDMMC_INT_SDIO(slot->id)));
	}
}

static int dw_mci_execute_tuning(struct mmc_host *mmc,u32 opcode)
{
    struct dw_mci_slot *slot = mmc_priv(mmc);
    struct dw_mci *host = slot->host;
    const struct dw_mci_drv_data *drv_data = host->drv_data;
    struct dw_mci_tuning_data tuning_data;
    int err = -ENOSYS;

    if(drv_data&&drv_data->execute_tuning)
        err = drv_data->execute_tuning(slot,opcode,&tuning_data);

    return err;
}

int dw_mci_start_signal_voltage_switch(struct mmc_host *mmc,
		struct mmc_ios *ios)
{

    struct dw_mci_slot *slot = mmc_priv(mmc);
    struct dw_mci *host = slot->host;
    const struct dw_mci_drv_data *drv_data = host->drv_data;
    int err = -ENOSYS;

    if(drv_data&&drv_data->start_signal_voltage_switch)
        err = drv_data->start_signal_voltage_switch(mmc,ios);

    return err;
}

static void dw_mci_slowdown_clk(struct mmc_host *mmc, int timing)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;
	const struct dw_mci_drv_data *drv_data = host->drv_data;

	if (host->flags & DWMMC_TUNING_DONE)
		host->flags &= ~DWMMC_TUNING_DONE;

	if (drv_data->slowdown_clk) {
		if (host->sd_reinit)
			return;
		else {
			host->sd_reinit = 1;

			pm_runtime_get_sync(mmc_dev(mmc));
			drv_data->slowdown_clk(host, timing);
			pm_runtime_mark_last_busy(mmc_dev(mmc));
			pm_runtime_put_autosuspend(mmc_dev(mmc));
		}
	}

}

#ifdef CONFIG_MMC_PASSWORDS
static int dw_mci_sd_lock_reset(struct mmc_host *mmc)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;
	const struct dw_mci_drv_data *drv_data = slot->host->drv_data;
	u32 present = 0;

	pm_runtime_get_sync(mmc_dev(mmc));
	present = dw_mci_get_cd(mmc);
	if (present == 1) {
		 if (drv_data && drv_data->work_fail_reset)
			drv_data->work_fail_reset(host);
	}
	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));

	return 0;
}
#endif

static int dw_mci_card_busy(struct mmc_host *mmc)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;
	u32 present_state;

	pm_runtime_get_sync(mmc_dev(mmc));
	/* Check whether DAT[3:0] is 0000 */
	present_state = mci_readl(host, STATUS);
	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));

	return (present_state & SDMMC_DATA_BUSY);
}

static const struct mmc_host_ops dw_mci_ops = {
	.request		= dw_mci_request,
	.pre_req		= dw_mci_pre_req,
	.post_req		= dw_mci_post_req,
	.set_ios		= dw_mci_set_ios,
	.get_ro			= dw_mci_get_ro,
	.get_cd			= dw_mci_get_cd,
	.slowdown_clk		= dw_mci_slowdown_clk,
	.card_busy		= dw_mci_card_busy,
	.enable_sdio_irq	= dw_mci_enable_sdio_irq,
	.start_signal_voltage_switch = dw_mci_start_signal_voltage_switch,
	.panic_probe = raw_mmc_panic_probe,
	.panic_write = raw_mmc_panic_write,
	.panic_erase = raw_mmc_panic_erase,
	.execute_tuning		 = dw_mci_execute_tuning,
#ifdef CONFIG_MMC_PASSWORDS
	.sd_lock_reset		= dw_mci_sd_lock_reset,
#endif
};

#ifdef CONFIG_HUAWEI_EMMC_DSM
static inline void dw_mci_dsm_host_error_filter(struct dw_mci *host, struct mmc_request *mrq, u32 *error_bits) {
	if (mrq->data && mrq->data->flags & MMC_DATA_WRITE)
		*error_bits &= ~SDMMC_INT_SBE;
	if (mrq->cmd) {
		if (mrq->cmd->opcode == MMC_SEND_TUNING_BLOCK_HS200)
			*error_bits = 0;
		else if (host->cur_slot->mmc->ios.clock <= 400000UL) {
			if (((mrq->cmd->opcode == SD_IO_RW_DIRECT) || (mrq->cmd->opcode == SD_SEND_IF_COND) || (mrq->cmd->opcode == SD_IO_SEND_OP_COND) || (mrq->cmd->opcode == MMC_APP_CMD)))
				*error_bits = 0;
			else if (mrq->cmd->opcode == MMC_SEND_STATUS)
				*error_bits &= ~SDMMC_INT_RCRC;
		}
	}
}
#endif

static void dw_mci_request_end(struct dw_mci *host, struct mmc_request *mrq)
	__releases(&host->lock)
	__acquires(&host->lock)
{
	struct dw_mci_slot *slot;
	struct mmc_host	*prev_mmc = host->cur_slot->mmc;
	const struct dw_mci_drv_data *drv_data = host->drv_data;
	int timing = prev_mmc->ios.timing;

	WARN_ON(host->cmd || host->data);

#ifdef CONFIG_HUAWEI_EMMC_DSM
	if(DWMMC_EMMC_ID == host->hw_mmc_id) {
		u32 error_bits = (host->data_status | host->dmd_cmd_status) & SDMMC_INT_ERROR;
		host->dmd_cmd_status = 0;
		if (error_bits) {
			dw_mci_dsm_host_error_filter(host, mrq, &error_bits);
			if (error_bits) {
				host->para = (error_bits | (((mrq->cmd ? mrq->cmd->opcode : 0) & 0x3f) << 16) | 0x80000000);
				queue_work(host->card_workqueue, &host->dmd_work); /* The following request maybe get lost */
			}
		}
	}
#endif

#ifdef CONFIG_HUAWEI_EMMC_DSM
	if(DWMMC_EMMC_ID == host->hw_mmc_id)
		del_timer(&host->rw_to_timer);
#endif
	del_timer(&host->timer);
	if (host->cur_slot->mrq == NULL || host->mrq == NULL)
		return;

	host->cur_slot->mrq = NULL;
	host->mrq = NULL;

	if (drv_data->tuning_move) {

	/*SOC1005*/
	if ((host->flags & DWMMC_TUNING_DONE) && mrq && mrq->cmd &&
		((mrq->cmd->error ) ||
		(mrq->cmd->data && ((mrq->cmd->data->error) ||
		(mrq->cmd->data->stop && mrq->cmd->data->stop->error))))){
			/* if SD get hardware timeout, No tuning move! */
			if (host->sd_hw_timeout == 1) {
				host->sd_hw_timeout = 0;
				goto out;
			}

			dev_dbg(host->dev, "move tuning del_sel, start=%d, cmd=%d, arg=0x%x\n",
					host->tuning_move_start, mrq->cmd->opcode, mrq->cmd->arg);
			/* req error, need move del_sel */
			if (host->tuning_move_start != -1) {
				if (drv_data->tuning_move(host, timing, host->tuning_move_start)) {
					host->tuning_move_start = 0;
					mrq->cmd->retries++;

					if (mrq->cmd->data && mrq->cmd->data->error) {
						mrq->cmd->data->error = 0;
					}
					if (mrq->cmd->data && mrq->cmd->data->stop && mrq->cmd->data->stop->error) {
						mrq->cmd->data->stop->error = 0;
					}
					if (!mrq->cmd->error) {
						mrq->cmd->error = -EILSEQ;
					}
				} else {
					host->tuning_move_start = -1;
				}
			}
		} else {
			host->tuning_move_start = 1;
		}
	}

out:
	if (!list_empty(&host->queue)) {
		slot = list_entry(host->queue.next,
				  struct dw_mci_slot, queue_node);
		list_del(&slot->queue_node);
		dev_vdbg(host->dev, "list not empty: %s is next\n",
			 mmc_hostname(slot->mmc));
		host->state = STATE_SENDING_CMD;
		dw_mci_start_request(host, slot);
	} else {
		dev_vdbg(host->dev, "list empty\n");
		host->state = STATE_IDLE;
	}

	spin_unlock(&host->lock);
	mmc_request_done(prev_mmc, mrq);
	spin_lock(&host->lock);

	pm_runtime_mark_last_busy(mmc_dev(prev_mmc));
	pm_runtime_put_autosuspend(mmc_dev(prev_mmc));
}

static void dw_mci_command_complete(struct dw_mci *host, struct mmc_command *cmd)
{
	u32 status = host->cmd_status;
	struct dw_mci_slot *slot = host->cur_slot;

#ifdef CONFIG_HUAWEI_EMMC_DSM
	host->dmd_cmd_status = host->cmd_status;
#endif
	host->cmd_status = 0;

	/* Read the response from the card (up to 16 bytes) */
	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			cmd->resp[3] = mci_readl(host, RESP0);
			cmd->resp[2] = mci_readl(host, RESP1);
			cmd->resp[1] = mci_readl(host, RESP2);
			cmd->resp[0] = mci_readl(host, RESP3);
		} else {
			cmd->resp[0] = mci_readl(host, RESP0);
			cmd->resp[1] = 0;
			cmd->resp[2] = 0;
			cmd->resp[3] = 0;
		}
	}

	if (status & SDMMC_INT_RTO) {
		if ((host->hw_mmc_id == DWMMC_SD_ID) &&
		    (cmd->opcode == MMC_SEND_TUNING_BLOCK))
			udelay(1000);

		if (!(slot && slot->sdio_wakelog_switch))
			dev_err(host->dev, "CMD %d(arg=0x%x) REP time out\n",
				cmd->opcode, cmd->arg);
		cmd->error = -ETIMEDOUT;
	} else if ((cmd->flags & MMC_RSP_CRC) && (status & SDMMC_INT_RCRC)) {
		if ((host->hw_mmc_id == DWMMC_SD_ID) &&
		    (cmd->opcode == MMC_SEND_TUNING_BLOCK))
			udelay(1000);

		dev_err(host->dev, "CMD %d(arg=0x%x) REP CRC error\n",
			cmd->opcode, cmd->arg);
		cmd->error = -EILSEQ;
	} else if (status & SDMMC_INT_RESP_ERR) {
		if ((host->hw_mmc_id == DWMMC_SD_ID) &&
		    (cmd->opcode == MMC_SEND_TUNING_BLOCK))
			udelay(1000);

		dev_err(host->dev, "CMD %d(arg=0x%x) REP error\n", cmd->opcode,
			cmd->arg);
		cmd->error = -EIO;
	} else
		cmd->error = 0;

	if (cmd->error) {
		/* newer ip versions need a delay between retries */
		if (host->quirks & DW_MCI_QUIRK_RETRY_DELAY)
			mdelay(20);
	}
}

static void dw_mci_tasklet_func(unsigned long priv)
{
	struct dw_mci *host = (struct dw_mci *)priv;
	struct mmc_data	*data;
	struct mmc_command *cmd;
	enum dw_mci_state state;
	enum dw_mci_state prev_state;
	u32 status;

	spin_lock(&host->lock);

	state = host->state;
	data = host->data;

	if (host->cmd_status & SDMMC_INT_HLE) {
		clear_bit(EVENT_CMD_COMPLETE, &host->pending_events);
		dev_err(host->dev, "hardware locked write error\n");
		dw_mci_reg_dump(host);

#ifdef CONFIG_HUAWEI_DSM
		dw_mci_dsm_dump(host, DSM_SDIO_HARDWARE_LOCK_NO);
#endif
		host->cmd_status &= ~SDMMC_INT_HLE;
		goto unlock;
	}

	do {
		prev_state = state;

		switch (state) {
		case STATE_IDLE:
			break;

		case STATE_SENDING_CMD:
			if (NULL == host->cmd) {
				printk(KERN_ERR"%s: The command currently being send to the card is NULL!\n",
						__func__);
				break;
			}
			if (!test_and_clear_bit(EVENT_CMD_COMPLETE,
						&host->pending_events))
				break;
			cmd = host->cmd;
			host->cmd = NULL;
			set_bit(EVENT_CMD_COMPLETE, &host->completed_events);
			dw_mci_command_complete(host, cmd);
			if (cmd == host->mrq->sbc && !cmd->error) {
				prev_state = state = STATE_SENDING_CMD;
				__dw_mci_start_request(host, host->cur_slot,
						       host->mrq->cmd);
				goto unlock;
			}

			if (data && cmd->error &&
					cmd != data->stop) {
				if (host->mrq->data->stop)
					send_stop_cmd(host, host->mrq->data);
				else {
					dw_mci_start_command(host, &host->stop,
							host->stop_cmdr);
					host->stop_snd = true;
				}
				/* To avoid fifo full condition */
				dw_mci_fifo_reset(host->dev, host);
				state = STATE_SENDING_STOP;
				break;
			}

			if (!host->mrq->data || cmd->error) {
				dw_mci_request_end(host, host->mrq);
				goto unlock;
			}

			prev_state = state = STATE_SENDING_DATA;
			/* fall through */

		case STATE_SENDING_DATA:
			if (test_and_clear_bit(EVENT_DATA_ERROR,
					       &host->pending_events)) {
				set_bit(EVENT_XFER_COMPLETE,
						&host->pending_events);
				if (data->stop)
					send_stop_cmd(host, data);
				else {
					dw_mci_start_command(host,
							&host->stop,
							host->stop_cmdr);
					host->stop_snd = true;
				}
				/* To avoid fifo full condition */
				dw_mci_fifo_reset(host->dev, host);
				state = STATE_DATA_ERROR;
				break;
			}

			if (!test_and_clear_bit(EVENT_XFER_COMPLETE,
						&host->pending_events))
				break;

			set_bit(EVENT_XFER_COMPLETE, &host->completed_events);
			prev_state = state = STATE_DATA_BUSY;
			/* fall through */

		case STATE_DATA_BUSY:
			if (!test_and_clear_bit(EVENT_DATA_COMPLETE,
						&host->pending_events))
				break;

			set_bit(EVENT_DATA_COMPLETE, &host->completed_events);
			status = host->data_status;

			if (status & DW_MCI_DATA_ERROR_FLAGS) {
				if (status & SDMMC_INT_DTO) {
					dev_err(host->dev,
						"data timeout error\n");
					data->error = -ETIMEDOUT;
				} else if (status & SDMMC_INT_DCRC) {
					if (!(host->flags & DWMMC_IN_TUNING)) {
						dev_err(host->dev,
							"data CRC error\n");
						dw_mci_reg_dump(host);
					}
					data->error = -EILSEQ;
				} else if (status & SDMMC_INT_EBE) {
					if (host->dir_status ==
							DW_MCI_SEND_STATUS) {
						/*
						 * No data CRC status was returned.
						 * The number of bytes transferred will
						 * be exaggerated in PIO mode.
						 */
						data->bytes_xfered = 0;
						data->error = -ETIMEDOUT;
						dev_err(host->dev,
							"Write no CRC\n");
					} else {
						data->error = -EIO;
						dev_err(host->dev,
							"End bit error\n");
					}

				} else if (status & SDMMC_INT_SBE) {
					dev_err(host->dev,
						"Start bit error "
						"(status=%08x)\n",
						status);
					data->error = -EIO;
				} else {
					dev_err(host->dev,
						"data FIFO error "
						"(status=%08x)\n",
						status);
					data->error = -EIO;
				}
				/*
				 * After an error, there may be data lingering
				 * in the FIFO, so reset it - doing so
				 * generates a block interrupt, hence setting
				 * the scatter-gather pointer to NULL.
				 */
				sg_miter_stop(&host->sg_miter);
				host->sg = NULL;
				dw_mci_fifo_reset(host->dev, host);
			} else {
				data->bytes_xfered = data->blocks * data->blksz;
				data->error = 0;
			}

			host->data = NULL;

			if (!data->stop && !host->stop_snd) {
				dw_mci_request_end(host, host->mrq);
				goto unlock;
			}

			if (host->mrq->sbc && !data->error) {
				if (data->stop)
					data->stop->error = 0;
				dw_mci_request_end(host, host->mrq);
				goto unlock;
			}

			prev_state = state = STATE_SENDING_STOP;
			if (!data->error)
				send_stop_cmd(host, data);

			if (test_and_clear_bit(EVENT_DATA_ERROR,
						&host->pending_events)) {
				if (data->stop)
					send_stop_cmd(host, data);
				else {
					dw_mci_start_command(host,
							&host->stop,
							host->stop_cmdr);
					host->stop_snd = true;
				}
			}
			/* fall through */

		case STATE_SENDING_STOP:
			if (!test_and_clear_bit(EVENT_CMD_COMPLETE,
						&host->pending_events))
				break;

			if (host->mrq->cmd->error &&
					host->mrq->data) {
				dw_mci_stop_dma(host);
				sg_miter_stop(&host->sg_miter);
				host->sg = NULL;
				dw_mci_fifo_reset(host->dev, host);
				dw_mci_ciu_reset(host->dev, host);
			}

			host->cmd = NULL;
			host->data = NULL;

			if (host->mrq->stop)
				dw_mci_command_complete(host, host->mrq->stop);
			else {
#ifdef CONFIG_HUAWEI_EMMC_DSM
				host->dmd_cmd_status = host->cmd_status;
#endif
				host->cmd_status = 0;
			}
			dw_mci_request_end(host, host->mrq);
			goto unlock;

		case STATE_DATA_ERROR:
			if (!test_and_clear_bit(EVENT_XFER_COMPLETE,
						&host->pending_events))
				break;

			dw_mci_stop_dma(host);
			set_bit(EVENT_XFER_COMPLETE, &host->completed_events);

			state = STATE_DATA_BUSY;
			break;
		}
	} while (state != prev_state);

	host->state = state;
unlock:
	spin_unlock(&host->lock);

}

/* push final bytes to part_buf, only use during push */
static void dw_mci_set_part_bytes(struct dw_mci *host, void *buf, int cnt)
{
	memcpy((void *)&host->part_buf, buf, cnt);
	host->part_buf_count = cnt;
}

/* append bytes to part_buf, only use during push */
static int dw_mci_push_part_bytes(struct dw_mci *host, void *buf, int cnt)
{
	cnt = min(cnt, (1 << host->data_shift) - host->part_buf_count);
	memcpy((void *)&host->part_buf + host->part_buf_count, buf, cnt);
	host->part_buf_count += cnt;
	return cnt;
}

/* pull first bytes from part_buf, only use during pull */
static int dw_mci_pull_part_bytes(struct dw_mci *host, void *buf, int cnt)
{
	cnt = min(cnt, (int)host->part_buf_count);
	if (cnt) {
		memcpy(buf, (void *)&host->part_buf + host->part_buf_start,
		       cnt);
		host->part_buf_count -= cnt;
		host->part_buf_start += cnt;
	}
	return cnt;
}

/* pull final bytes from the part_buf, assuming it's just been filled */
static void dw_mci_pull_final_bytes(struct dw_mci *host, void *buf, int cnt)
{
	memcpy(buf, &host->part_buf, cnt);
	host->part_buf_start = cnt;
	host->part_buf_count = (1 << host->data_shift) - cnt;
}

static void dw_mci_push_data16(struct dw_mci *host, void *buf, int cnt)
{
	struct mmc_data *data = host->data;
	int init_cnt = cnt;

	/* try and push anything in the part_buf */
	if (unlikely(host->part_buf_count)) {
		int len = dw_mci_push_part_bytes(host, buf, cnt);
		buf += len;
		cnt -= len;
		if (host->part_buf_count == 2) {
			mci_writew(host, DATA(host->data_offset),
					host->part_buf16);
			host->part_buf_count = 0;
		}
	}
#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	if (unlikely((unsigned long)buf & 0x1)) {
		while (cnt >= 2) {
			u16 aligned_buf[64];
			int len = min(cnt & -2, (int)sizeof(aligned_buf));
			int items = len >> 1;
			int i;
			/* memcpy from input buffer into aligned buffer */
			memcpy(aligned_buf, buf, len);
			buf += len;
			cnt -= len;
			/* push data from aligned buffer into fifo */
			for (i = 0; i < items; ++i)
				mci_writew(host, DATA(host->data_offset),
						aligned_buf[i]);
		}
	} else
#endif
	{
		u16 *pdata = buf;
		for (; cnt >= 2; cnt -= 2)
			mci_writew(host, DATA(host->data_offset), *pdata++);
		buf = pdata;
	}
	/* put anything remaining in the part_buf */
	if (cnt) {
		dw_mci_set_part_bytes(host, buf, cnt);
		 /* Push data if we have reached the expected data length */
		if ((data->bytes_xfered + init_cnt) ==
		    (data->blksz * data->blocks))
			mci_writew(host, DATA(host->data_offset),
				   host->part_buf16);
	}
}

static void dw_mci_pull_data16(struct dw_mci *host, void *buf, int cnt)
{
#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	if (unlikely((unsigned long)buf & 0x1)) {
		while (cnt >= 2) {
			/* pull data from fifo into aligned buffer */
			u16 aligned_buf[64] = {0};
			int len = min(cnt & -2, (int)sizeof(aligned_buf));
			int items = len >> 1;
			int i;
			for (i = 0; i < items; ++i)
				aligned_buf[i] = mci_readw(host,
						DATA(host->data_offset));
			/* memcpy from aligned buffer into output buffer */
			memcpy(buf, aligned_buf, len);
			buf += len;
			cnt -= len;
		}
	} else
#endif
	{
		u16 *pdata = buf;
		for (; cnt >= 2; cnt -= 2)
			*pdata++ = mci_readw(host, DATA(host->data_offset));
		buf = pdata;
	}
	if (cnt) {
		host->part_buf16 = mci_readw(host, DATA(host->data_offset));
		dw_mci_pull_final_bytes(host, buf, cnt);
	}
}

static void dw_mci_push_data32(struct dw_mci *host, void *buf, int cnt)
{
	struct mmc_data *data = host->data;
	int init_cnt = cnt;

	/* try and push anything in the part_buf */
	if (unlikely(host->part_buf_count)) {
		int len = dw_mci_push_part_bytes(host, buf, cnt);
		buf += len;
		cnt -= len;
		if (host->part_buf_count == 4) {
			mci_writel(host, DATA(host->data_offset),
					host->part_buf32);
			host->part_buf_count = 0;
		}
	}
#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	if (unlikely((unsigned long)buf & 0x3)) {
		while (cnt >= 4) {
			u32 aligned_buf[32];
			int len = min(cnt & -4, (int)sizeof(aligned_buf));
			int items = len >> 2;
			int i;
			/* memcpy from input buffer into aligned buffer */
			memcpy(aligned_buf, buf, len);
			buf += len;
			cnt -= len;
			/* push data from aligned buffer into fifo */
			for (i = 0; i < items; ++i)
				mci_writel(host, DATA(host->data_offset),
						aligned_buf[i]);
		}
	} else
#endif
	{
		u32 *pdata = buf;
		for (; cnt >= 4; cnt -= 4)
			mci_writel(host, DATA(host->data_offset), *pdata++);
		buf = pdata;
	}
	/* put anything remaining in the part_buf */
	if (cnt) {
		dw_mci_set_part_bytes(host, buf, cnt);
		 /* Push data if we have reached the expected data length */
		if ((data->bytes_xfered + init_cnt) ==
		    (data->blksz * data->blocks))
			mci_writel(host, DATA(host->data_offset),
				   host->part_buf32);
	}
}

static void dw_mci_pull_data32(struct dw_mci *host, void *buf, int cnt)
{
#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	if (unlikely((unsigned long)buf & 0x3)) {
		while (cnt >= 4) {
			/* pull data from fifo into aligned buffer */
			u32 aligned_buf[32] = {0};
			int len = min(cnt & -4, (int)sizeof(aligned_buf));
			int items = len >> 2;
			int i;
			for (i = 0; i < items; ++i)
				aligned_buf[i] = mci_readl(host,
						DATA(host->data_offset));
			/* memcpy from aligned buffer into output buffer */
			memcpy(buf, aligned_buf, len);
			buf += len;
			cnt -= len;
		}
	} else
#endif
	{
		u32 *pdata = buf;
		for (; cnt >= 4; cnt -= 4)
			*pdata++ = mci_readl(host, DATA(host->data_offset));
		buf = pdata;
	}
	if (cnt) {
		host->part_buf32 = mci_readl(host, DATA(host->data_offset));
		dw_mci_pull_final_bytes(host, buf, cnt);
	}
}

static void dw_mci_push_data64(struct dw_mci *host, void *buf, int cnt)
{
	struct mmc_data *data = host->data;
	int init_cnt = cnt;

	/* try and push anything in the part_buf */
	if (unlikely(host->part_buf_count)) {
		int len = dw_mci_push_part_bytes(host, buf, cnt);
		buf += len;
		cnt -= len;

		if (host->part_buf_count == 8) {
			mci_writeq(host, DATA(host->data_offset),
					host->part_buf);
			host->part_buf_count = 0;
		}
	}
#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	if (unlikely((unsigned long)buf & 0x7)) {
		while (cnt >= 8) {
			u64 aligned_buf[16] = {0};
			int len = min(cnt & -8, (int)sizeof(aligned_buf));
			int items = len >> 3;
			int i;
			/* memcpy from input buffer into aligned buffer */
			memcpy(aligned_buf, buf, len);
			buf += len;
			cnt -= len;
			/* push data from aligned buffer into fifo */
			for (i = 0; i < items; ++i)
				mci_writeq(host, DATA(host->data_offset),
						aligned_buf[i]);
		}
	} else
#endif
	{
		u64 *pdata = buf;
		for (; cnt >= 8; cnt -= 8)
			mci_writeq(host, DATA(host->data_offset), *pdata++);
		buf = pdata;
	}
	/* put anything remaining in the part_buf */
	if (cnt) {
		dw_mci_set_part_bytes(host, buf, cnt);
		/* Push data if we have reached the expected data length */
		if ((data->bytes_xfered + init_cnt) ==
		    (data->blksz * data->blocks))
			mci_writeq(host, DATA(host->data_offset),
				   host->part_buf);
	}
}

static void dw_mci_pull_data64(struct dw_mci *host, void *buf, int cnt)
{
#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	if (unlikely((unsigned long)buf & 0x7)) {
		while (cnt >= 8) {
			/* pull data from fifo into aligned buffer */
			u64 aligned_buf[16];
			int len = min(cnt & -8, (int)sizeof(aligned_buf));
			int items = len >> 3;
			int i;
			for (i = 0; i < items; ++i)
				aligned_buf[i] = mci_readq(host,
						DATA(host->data_offset));
			/* memcpy from aligned buffer into output buffer */
			memcpy(buf, aligned_buf, len);
			buf += len;
			cnt -= len;
		}
	} else
#endif
	{
		u64 *pdata = buf;
		for (; cnt >= 8; cnt -= 8)
			*pdata++ = mci_readq(host, DATA(host->data_offset));
		buf = pdata;
	}
	if (cnt) {
		host->part_buf = mci_readq(host, DATA(host->data_offset));
		dw_mci_pull_final_bytes(host, buf, cnt);
	}
}

static void dw_mci_pull_data(struct dw_mci *host, void *buf, int cnt)
{
	int len;

	/* get remaining partial bytes */
	len = dw_mci_pull_part_bytes(host, buf, cnt);
	if (unlikely(len == cnt))
		return;
	buf += len;
	cnt -= len;

	/* get the rest of the data */
	host->pull_data(host, buf, cnt);
}

static void dw_mci_read_data_pio(struct dw_mci *host, bool dto)
{
	struct sg_mapping_iter *sg_miter = &host->sg_miter;
	void *buf;
	unsigned int offset;
	struct mmc_data	*data = host->data;
	int shift = host->data_shift;
	u32 status;
	unsigned int len;
	unsigned int remain, fcnt;

	do {
		if (!sg_miter_next(sg_miter))
			goto done;

		host->sg = sg_miter->piter.sg;
		buf = sg_miter->addr;
		remain = sg_miter->length;
		offset = 0;

		do {
			fcnt = (SDMMC_GET_FCNT(mci_readl(host, STATUS))
					<< shift) + host->part_buf_count;
			len = min(remain, fcnt);
			if (!len)
				break;
			dw_mci_pull_data(host, (void *)(buf + offset), len);
			data->bytes_xfered += len;
			offset += len;
			remain -= len;
		} while (remain);

		sg_miter->consumed = offset;
		status = mci_readl(host, MINTSTS);
		mci_writel(host, RINTSTS, SDMMC_INT_RXDR);
	/* if the RXDR is ready read again */
	} while ((status & SDMMC_INT_RXDR) ||
		 (dto && SDMMC_GET_FCNT(mci_readl(host, STATUS))));

	if (!remain) {
		if (!sg_miter_next(sg_miter))
			goto done;
		sg_miter->consumed = 0;
	}
	sg_miter_stop(sg_miter);
	return;

done:
	sg_miter_stop(sg_miter);
	host->sg = NULL;
	smp_wmb();
	set_bit(EVENT_XFER_COMPLETE, &host->pending_events);
}

static void dw_mci_write_data_pio(struct dw_mci *host)
{
	struct sg_mapping_iter *sg_miter = &host->sg_miter;
	void *buf;
	unsigned int offset;
	struct mmc_data	*data = host->data;
	int shift = host->data_shift;
	u32 status;
	unsigned int len;
	unsigned int fifo_depth = host->fifo_depth;
	unsigned int remain, fcnt;

	do {
		if (!sg_miter_next(sg_miter))
			goto done;

		host->sg = sg_miter->piter.sg;
		buf = sg_miter->addr;
		remain = sg_miter->length;
		offset = 0;

		do {
			fcnt = ((fifo_depth -
				 SDMMC_GET_FCNT(mci_readl(host, STATUS)))
					<< shift) - host->part_buf_count;
			len = min(remain, fcnt);
			if (!len)
				break;
			host->push_data(host, (void *)(buf + offset), len);
			data->bytes_xfered += len;
			offset += len;
			remain -= len;
		} while (remain);

		sg_miter->consumed = offset;
		status = mci_readl(host, MINTSTS);
		mci_writel(host, RINTSTS, SDMMC_INT_TXDR);
	} while (status & SDMMC_INT_TXDR); /* if TXDR write again */

	if (!remain) {
		if (!sg_miter_next(sg_miter))
			goto done;
		sg_miter->consumed = 0;
	}
	sg_miter_stop(sg_miter);
	return;

done:
	sg_miter_stop(sg_miter);
	host->sg = NULL;
	smp_wmb();
	set_bit(EVENT_XFER_COMPLETE, &host->pending_events);
}

static void dw_mci_cmd_interrupt(struct dw_mci *host, u32 status)
{
	if (!host->cmd_status)
		host->cmd_status = status;

	smp_wmb();

	set_bit(EVENT_CMD_COMPLETE, &host->pending_events);
	tasklet_schedule(&host->tasklet);/*dw_mci_tasklet_func*/
}

static irqreturn_t dw_mci_interrupt(int irq, void *dev_id)
{
	struct dw_mci *host = dev_id;
	u32 pending;
	int i;
	u32 temp;

	pending = mci_readl(host, MINTSTS); /* read-only mask reg */

	if (pending) {

		/*
		 * DTO fix - version 2.10a and below, and only if internal DMA
		 * is configured.
		 */
		if (host->quirks & DW_MCI_QUIRK_IDMAC_DTO) {
			if (!pending &&
			    ((mci_readl(host, STATUS) >> 17) & 0x1fff))
				pending |= SDMMC_INT_DATA_OVER;
		}

		if (pending & SDMMC_INT_CMD_DONE) {
			u32 cmd = mci_readl(host, CMD) & 0x3f;
			if (cmd == SD_SWITCH_VOLTAGE &&
				!(mci_readl(host, STATUS) & SDMMC_DATA_BUSY)) {
					pending |= SDMMC_INT_RTO;
			}
		}

		if (pending & SDMMC_INT_HLE) {
			mci_writel(host, RINTSTS, SDMMC_INT_HLE);
			host->cmd_status = pending;
			tasklet_schedule(&host->tasklet);/*dw_mci_tasklet_func*/
		}

		if (pending & DW_MCI_CMD_ERROR_FLAGS) {
			mci_writel(host, RINTSTS, DW_MCI_CMD_ERROR_FLAGS);
			host->cmd_status = pending;
			smp_wmb();
			set_bit(EVENT_CMD_COMPLETE, &host->pending_events);
		}

		if (pending & SDMMC_INT_VOLT_SW) {
			u32 cmd = mci_readl(host, CMD) & 0x3f;
			if (cmd == SD_SWITCH_VOLTAGE) {
				mci_writel(host, RINTSTS, SDMMC_INT_VOLT_SW);

				dw_mci_cmd_interrupt(host, pending);

				mci_writel(host, RINTSTS, SDMMC_INT_RESP_ERR);
				temp = mci_readl(host, INTMASK);
				temp |= SDMMC_INT_RESP_ERR;
				mci_writel(host, INTMASK, temp);
			}
		}

		if (pending & DW_MCI_DATA_ERROR_FLAGS) {
			/* if there is an error report DATA_ERROR */
			mci_writel(host, RINTSTS, DW_MCI_DATA_ERROR_FLAGS);
			host->data_status = pending;
			smp_wmb();
			set_bit(EVENT_DATA_ERROR, &host->pending_events);
			tasklet_schedule(&host->tasklet);/*dw_mci_tasklet_func*/
		}

		if (pending & SDMMC_INT_DATA_OVER) {
			mci_writel(host, RINTSTS, SDMMC_INT_DATA_OVER);
			if (!host->data_status)
				host->data_status = pending;
			smp_wmb();
			if (host->dir_status == DW_MCI_RECV_STATUS) {
				if (host->sg != NULL)
					dw_mci_read_data_pio(host, true);
			}
			set_bit(EVENT_DATA_COMPLETE, &host->pending_events);
			tasklet_schedule(&host->tasklet);/*dw_mci_tasklet_func*/
		}

		if (pending & SDMMC_INT_RXDR) {
			mci_writel(host, RINTSTS, SDMMC_INT_RXDR);
			if (host->dir_status == DW_MCI_RECV_STATUS && host->sg)
				dw_mci_read_data_pio(host, false);
		}

		if (pending & SDMMC_INT_TXDR) {
			mci_writel(host, RINTSTS, SDMMC_INT_TXDR);
			if (host->dir_status == DW_MCI_SEND_STATUS && host->sg)
				dw_mci_write_data_pio(host);
		}

		if (pending & SDMMC_INT_CMD_DONE) {
			mci_writel(host, RINTSTS, SDMMC_INT_CMD_DONE);
			dw_mci_cmd_interrupt(host, pending);
		}

		if (pending & SDMMC_INT_CD) {
			mci_writel(host, RINTSTS, SDMMC_INT_CD);
			queue_work(host->card_workqueue, &host->card_work);/*dw_mci_work_routine_card*/
		}

		/* Handle SDIO Interrupts */
		for (i = 0; i < host->num_slots; i++) {
			struct dw_mci_slot *slot = host->slot[i];
			if (pending & SDMMC_INT_SDIO(i)) {
				mci_writel(host, RINTSTS, SDMMC_INT_SDIO(i));
				mmc_signal_sdio_irq(slot->mmc);
			}
		}

	}

#ifdef CONFIG_MMC_DW_IDMAC
	if(SDMMC_32_BIT_DMA == host->dma_64bit_address) {
		/* Handle 32 bit DMA interrupts */
		pending = mci_readl(host, IDSTS);
		if (pending & (SDMMC_IDMAC_INT_TI | SDMMC_IDMAC_INT_RI)) {
			mci_writel(host, IDSTS, SDMMC_IDMAC_INT_TI | SDMMC_IDMAC_INT_RI);
			mci_writel(host, IDSTS, SDMMC_IDMAC_INT_NI);
			host->dma_ops->complete(host);
		}
	} else {
		/* Handle 64 bit DMA interrupts */
		pending = mci_readl(host, IDSTS_64DMA);
		if (pending & (SDMMC_IDMAC_INT_TI | SDMMC_IDMAC_INT_RI)) {
			mci_writel(host, IDSTS_64DMA, SDMMC_IDMAC_INT_TI | SDMMC_IDMAC_INT_RI);
			mci_writel(host, IDSTS_64DMA, SDMMC_IDMAC_INT_NI);
			host->dma_ops->complete(host);
		}
	}
#endif

	return IRQ_HANDLED;
}

#ifdef CONFIG_HUAWEI_EMMC_DSM
static void dw_mci_dmd_work(struct work_struct *work) {
	struct mmc_card *card = NULL;
	struct dw_mci *host = container_of(work, struct dw_mci, dmd_work);
	u32 error_bits, opcode;
	u32 para;
	spin_lock_bh(&host->lock);
	para = host->para;
	if(host->cur_slot && host->cur_slot->mmc && host->cur_slot->mmc->card)
		card = host->cur_slot->mmc->card;
	spin_unlock_bh(&host->lock);
	error_bits = para & 0xffff;
	opcode = ((para >> 16) & 0x3f);
	if(para & 0x80000000) {
		DSM_EMMC_LOG(card, DSM_EMMC_HOST_ERR,
			"opcode:%d failed, status:%x\n",
			opcode, error_bits);
	} else {
		DSM_EMMC_LOG(card, DSM_EMMC_RW_TIMEOUT_ERR,
			"opcode:%d failed, status:%x\n",
			opcode, error_bits);
	}
}

static void dw_mci_rw_timeout_timer(unsigned long data) {
	struct dw_mci *host = (struct dw_mci *)data;
	u32 error_bits;
	spin_lock_bh(&host->lock);
	error_bits = (host->data_status | host->dmd_cmd_status) & SDMMC_INT_ERROR;
	host->para = (error_bits | ((((host->mrq && host->mrq->cmd) ? host->mrq->cmd->opcode : 0) & 0x3f) << 16));
	spin_unlock_bh(&host->lock);
	queue_work(host->card_workqueue, &host->dmd_work);
}
#endif

static void dw_mci_timeout_timer(unsigned long data)
{
	struct dw_mci *host = (struct dw_mci *)data;
	struct mmc_request *mrq;


	if (host) {
		spin_lock(&host->lock);
		if (host->mrq) {
			mrq = host->mrq;
			dev_vdbg(host->dev, "time out host->mrq = %p\n", host->mrq);

			dev_err(host->dev,
				"Timeout waiting for hardware interrupt."
				" state = %d\n", host->state);
			dw_mci_reg_dump(host);
#ifdef CONFIG_HUAWEI_DSM
			dw_mci_dsm_dump(host, DSM_SDIO_RW_TIMEOUT_NO);
#endif

			host->sg = NULL;
			host->data = NULL;
			host->cmd = NULL;

			switch (host->state) {
			case STATE_IDLE:
				break;
			case STATE_SENDING_CMD:
				mrq->cmd->error = -ENOMEDIUM;
				if (!mrq->data)
					break;
			/* fall through */
			case STATE_SENDING_DATA:
				mrq->data->error = -ENOMEDIUM;
				dw_mci_stop_dma(host);
				break;
			case STATE_DATA_BUSY:
			case STATE_DATA_ERROR:
				if (mrq->data->error == -EINPROGRESS)
					mrq->data->error = -ENOMEDIUM;
				/* fall through */
			case STATE_SENDING_STOP:
				if (mrq->stop)
					mrq->stop->error = -ENOMEDIUM;
				break;
			}

			if (host->hw_mmc_id == DWMMC_SD_ID)
				host->sd_hw_timeout = 1;

			dw_mci_fifo_reset(host->dev, host);
			dw_mci_ciu_reset(host->dev, host);
			dw_mci_request_end(host, mrq);
		}
		spin_unlock(&host->lock);
	}
}

static void dw_mci_work_routine_card(struct work_struct *work)
{
	struct dw_mci *host = container_of(work, struct dw_mci, card_work);
	int i;

	for (i = 0; i < host->num_slots; i++) {
		struct dw_mci_slot *slot = host->slot[i];
		struct mmc_host *mmc = slot->mmc;
		struct mmc_request *mrq;
		int present;

		present = dw_mci_get_cd(mmc);
		while (present != slot->last_detect_state) {
			dev_dbg(&slot->mmc->class_dev, "card %s\n",
				present ? "inserted" : "removed");

			spin_lock_bh(&host->lock);

			/* Card change detected */
			slot->last_detect_state = present;

			/* Mark card as present if applicable */
			if (present != 0)
				set_bit(DW_MMC_CARD_PRESENT, &slot->flags);

			/* Clean up queue if present */
			mrq = slot->mrq;
			if (mrq) {
				if (mrq == host->mrq) {
					host->data = NULL;
					host->cmd = NULL;

					switch (host->state) {
					case STATE_IDLE:
						break;
					case STATE_SENDING_CMD:
						mrq->cmd->error = -ENOMEDIUM;
						if (!mrq->data)
							break;
						/* fall through */
					case STATE_SENDING_DATA:
						mrq->data->error = -ENOMEDIUM;
						dw_mci_stop_dma(host);
						break;
					case STATE_DATA_BUSY:
					case STATE_DATA_ERROR:
						if (mrq->data->error == -EINPROGRESS)
							mrq->data->error = -ENOMEDIUM;
						if (!mrq->stop)
							break;
						/* fall through */
					case STATE_SENDING_STOP:
						if(mrq->stop)
							mrq->stop->error = -ENOMEDIUM;
						break;
					}

					dw_mci_request_end(host, mrq);
				} else {
					list_del(&slot->queue_node);
					mrq->cmd->error = -ENOMEDIUM;
					if (mrq->data)
						mrq->data->error = -ENOMEDIUM;
					if (mrq->stop)
						mrq->stop->error = -ENOMEDIUM;

#ifdef CONFIG_HUAWEI_EMMC_DSM
					if(DWMMC_EMMC_ID == host->hw_mmc_id)
						del_timer(&host->rw_to_timer);
#endif
					del_timer(&host->timer);
					spin_unlock(&host->lock);
					mmc_request_done(slot->mmc, mrq);
					spin_lock(&host->lock);
				}
			}

			/* Power down slot */
			if (present == 0) {
				clear_bit(DW_MMC_CARD_PRESENT, &slot->flags);

				/*
				 * Clear down the FIFO - doing so generates a
				 * block interrupt, hence setting the
				 * scatter-gather pointer to NULL.
				 */
				sg_miter_stop(&host->sg_miter);
				host->sg = NULL;

				dw_mci_fifo_reset(host->dev, host);
				dw_mci_ciu_reset(host->dev, host);
#ifdef CONFIG_MMC_DW_IDMAC
				dw_mci_idma_reset_dma(host);
#endif
			}

			spin_unlock_bh(&host->lock);

			present = dw_mci_get_cd(mmc);
		}

		mmc_detect_change(slot->mmc,
			msecs_to_jiffies(host->pdata->detect_delay_ms));
	}
}

#ifdef CONFIG_OF
/* given a slot id, find out the device node representing that slot */
static struct device_node *dw_mci_of_find_slot_node(struct device *dev, u8 slot)
{
	struct device_node *np;
	const __be32 *addr;
	int len;

	if (!dev || !dev->of_node)
		return NULL;

	for_each_child_of_node(dev->of_node, np) {
		addr = of_get_property(np, "reg", &len);
		if (!addr || (len < sizeof(int)))
			continue;
		if (be32_to_cpup(addr) == slot)
			return np;
	}
	return NULL;
}

static struct dw_mci_of_slot_quirks {
	char *quirk;
	int id;
} of_slot_quirks[] = {
	{
		.quirk	= "disable-wp",
		.id	= DW_MCI_SLOT_QUIRK_NO_WRITE_PROTECT,
	},
};

static int dw_mci_of_get_slot_quirks(struct device *dev, u8 slot)
{
	struct device_node *np = dw_mci_of_find_slot_node(dev, slot);
	int quirks = 0;
	int idx;

	/* get quirks */
	for (idx = 0; idx < ARRAY_SIZE(of_slot_quirks); idx++)
		if (of_get_property(np, of_slot_quirks[idx].quirk, NULL))
			quirks |= of_slot_quirks[idx].id;

	return quirks;
}

/* find out bus-width for a given slot */
static u32 dw_mci_of_get_bus_wd(struct device *dev, u8 slot)
{
	struct device_node *np = dw_mci_of_find_slot_node(dev, slot);
	u32 bus_wd = 1;

	if (!np)
		return 1;

	if (of_property_read_u32(np, "bus-width", &bus_wd))
		dev_err(dev, "bus-width property not found, assuming width"
			       " as 1\n");
	return bus_wd;
}

/* find the write protect gpio for a given slot; or -1 if none specified */
static int dw_mci_of_get_wp_gpio(struct device *dev, u8 slot)
{
	struct device_node *np = dw_mci_of_find_slot_node(dev, slot);
	int gpio;

	if (!np)
		return -EINVAL;

	gpio = of_get_named_gpio(np, "wp-gpios", 0);

	/* Having a missing entry is valid; return silently */
	if (!gpio_is_valid(gpio))
		return -EINVAL;

	if (devm_gpio_request(dev, gpio, "dw-mci-wp")) {
		dev_warn(dev, "gpio [%d] request failed\n", gpio);
		return -EINVAL;
	}

	return gpio;
}
#else /* CONFIG_OF */
static int dw_mci_of_get_slot_quirks(struct device *dev, u8 slot)
{
	return 0;
}
static u32 dw_mci_of_get_bus_wd(struct device *dev, u8 slot)
{
	return 1;
}
static struct device_node *dw_mci_of_find_slot_node(struct device *dev, u8 slot)
{
	return NULL;
}
static int dw_mci_of_get_wp_gpio(struct device *dev, u8 slot)
{
	return -EINVAL;
}
#endif /* CONFIG_OF */

static int dw_mci_init_slot(struct dw_mci *host, unsigned int id)
{
	struct mmc_host *mmc;
	struct dw_mci_slot *slot;
	const struct dw_mci_drv_data *drv_data = host->drv_data;
	int ctrl_id, ret;
	u8 bus_width;

	mmc = mmc_alloc_host(sizeof(struct dw_mci_slot), host->dev);
	if (!mmc)
		return -ENOMEM;

	g_mmc_for_mmctrace[mmc->index] = mmc;
	printk(KERN_ERR "$$$$$$$$$$$$$$$$$$$$ %p, %d \n", g_mmc_for_mmctrace[mmc->index], mmc->index );

	slot = mmc_priv(mmc);
	slot->id = id;
	slot->mmc = mmc;
	slot->host = host;
	host->slot[id] = slot;

	slot->quirks = dw_mci_of_get_slot_quirks(host->dev, slot->id);

	mmc->ops = &dw_mci_ops;
	mmc->f_min = DIV_ROUND_UP(host->bus_hz, 510);
	mmc->f_max = host->bus_hz;

	mmc->sdio_present = 0;

	if (host->pdata->get_ocr)
		mmc->ocr_avail = host->pdata->get_ocr(id);
	else
		mmc->ocr_avail = MMC_VDD_28_29;

	/*
	 * Start with slot power disabled, it will be enabled when a card
	 * is detected.
	 */
	if (host->pdata->setpower)
		host->pdata->setpower(id, 0);


	if (host->pdata->caps)
		mmc->caps = host->pdata->caps;

	if (host->pdata->pm_caps) {
		mmc->pm_caps = host->pdata->pm_caps;
		mmc->pm_flags = mmc->pm_caps;
	}

	if (host->dev->of_node) {
		ctrl_id = of_alias_get_id(host->dev->of_node, "mshc");
		if (ctrl_id < 0)
			ctrl_id = 0;
	} else {
		ctrl_id = to_platform_device(host->dev)->id;
	}

	if (drv_data && drv_data->caps)
		mmc->caps |= drv_data->caps[ctrl_id];

	if (host->pdata->caps2)
		mmc->caps2 = host->pdata->caps2;

	if (host->pdata->get_bus_wd)
		bus_width = host->pdata->get_bus_wd(slot->id);
	else if (host->dev->of_node)
		bus_width = dw_mci_of_get_bus_wd(host->dev, slot->id);
	else
		bus_width = 1;

	switch (bus_width) {
	case 8:
		mmc->caps |= MMC_CAP_8_BIT_DATA;
	case 4:
		mmc->caps |= MMC_CAP_4_BIT_DATA;
	}

	if (host->pdata->quirks & DW_MCI_QUIRK_HIGHSPEED)
		mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED;

	if (host->pdata->blk_settings) {
		mmc->max_segs = host->pdata->blk_settings->max_segs;
		mmc->max_blk_size = host->pdata->blk_settings->max_blk_size;
		mmc->max_blk_count = host->pdata->blk_settings->max_blk_count;
		mmc->max_req_size = host->pdata->blk_settings->max_req_size;
		mmc->max_seg_size = host->pdata->blk_settings->max_seg_size;
	} else {
		/* Useful defaults if platform data is unset. */
#ifdef CONFIG_MMC_DW_IDMAC
		mmc->max_segs = host->ring_size;
		mmc->max_blk_size = 65536;
		mmc->max_seg_size = 0x1000;
		mmc->max_req_size = mmc->max_seg_size * host->ring_size;
		mmc->max_blk_count = mmc->max_req_size / 512;
#else
		mmc->max_segs = 64;
		mmc->max_blk_size = 65536; /* BLKSIZ is 16 bits */
		mmc->max_blk_count = 512;
		mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;
		mmc->max_seg_size = mmc->max_req_size;
#endif /* CONFIG_MMC_DW_IDMAC */
	}

	host->pinctrl = devm_pinctrl_get(mmc_dev(mmc));
	if (IS_ERR(host->pinctrl)) {
		dev_warn(host->dev, "could not get pinctrl\n");
		host->pinctrl = NULL;
	}

	host->pins_default = pinctrl_lookup_state(host->pinctrl,
			PINCTRL_STATE_DEFAULT);

	/* enable pins to be muxed in and configured */
	if (IS_ERR(host->pins_default)) {
		dev_warn(host->dev, "could not get default pinstate\n");
		host->pins_default = NULL;
	}

	host->pins_idle = pinctrl_lookup_state(host->pinctrl,
			PINCTRL_STATE_IDLE);
	if (IS_ERR(host->pins_idle)) {
		dev_warn(host->dev, "could not get default pinstate\n");
		host->pins_idle = NULL;
	}

    	/*
	 * comment only for balong
    	 * sd:vmmc :ldo10 卡侧电压；
       	 * vqmmc:ldo7  I/O 上拉；
       	 * buck2/ldo5 硬件确认不需要控制，包括低功耗模式下；

    	 * mmc:vmmc:ldo19 vcc 常供3V；
         * vqmmc:ldo5 vccq 单板长供，软件不设置
	*/
	host->vmmc = devm_regulator_get(mmc_dev(mmc), "vmmc");
	if (IS_ERR(host->vmmc)) {
		pr_info("%s: no vmmc regulator found\n", mmc_hostname(mmc));
		host->vmmc = NULL;
	}/* else {
		ret = regulator_enable(host->vmmc);
		if (ret) {
			dev_err(host->dev,
				"failed to enable regulator: %d\n", ret);
			goto err_setup_bus;
		}
	}*/

	host->vqmmc = devm_regulator_get(mmc_dev(mmc), "vqmmc");
	if (IS_ERR(host->vqmmc)) {
		pr_warning("%s: no vqmmc regulator found\n", mmc_hostname(mmc));
		host->vqmmc = NULL;
	} /*else {
		ret = regulator_enable(host->vqmmc);
		if (ret) {
			dev_err(host->dev,
				"failed to enable regulator vqmmc: %d\n", ret);
			goto err_setup_bus;
		}
	}*/

	if (drv_data && drv_data->cd_detect_init)
		drv_data->cd_detect_init(host);

	if (dw_mci_get_cd(mmc))
		set_bit(DW_MMC_CARD_PRESENT, &slot->flags);
	else
		clear_bit(DW_MMC_CARD_PRESENT, &slot->flags);

	slot->wp_gpio = dw_mci_of_get_wp_gpio(host->dev, slot->id);

	ret = mmc_add_host(mmc);
	if (ret)
		goto err_setup_bus;

#if defined(CONFIG_DEBUG_FS)
	dw_mci_init_debugfs(slot);
#endif

	/* Card initially undetected */
	slot->last_detect_state = 0;

	return 0;

err_setup_bus:
	mmc_free_host(mmc);
	return -EINVAL;
}

static void dw_mci_cleanup_slot(struct dw_mci_slot *slot, unsigned int id)
{
	/* Shutdown detect IRQ */
	if (slot->host->pdata->exit)
		slot->host->pdata->exit(id);

	/* Debugfs stuff is cleaned up by mmc core */
	mmc_remove_host(slot->mmc);
	slot->host->slot[id] = NULL;
	mmc_free_host(slot->mmc);
}

static void dw_mci_init_dma(struct dw_mci *host)
{
	int addr_config = 0;
	/* Check ADDR_CONFIG bit in HCON to find IDMAC address bus width*/

	addr_config = (mci_readl(host, HCON) >> 27) & 0x01;

	if (1 == addr_config) {
		/* host supports IDMAC in 64-bit address mode */
		host->desc_sz = DW_MCI_DESC_SZ_64BIT;
		host->dma_64bit_address = SDMMC_64_BIT_DMA;
		dev_info(host->dev, "IDMAC supports 64-bit address mode.\n");
		host->dma_mask = DMA_BIT_MASK(64);
		host->dev->dma_mask = &host->dma_mask;
	} else {
		/* host supports IDMAC in 32-bit address mode */
		host->desc_sz = DW_MCI_DESC_SZ;
		host->dma_64bit_address = SDMMC_32_BIT_DMA;
		dev_info(host->dev, "IDMAC supports 32-bit address mode.\n");
		host->dma_mask = DMA_BIT_MASK(32);
		host->dev->dma_mask = &host->dma_mask;
	}

	/* Alloc memory for sg translation */
	host->sg_cpu = dmam_alloc_coherent(host->dev, host->desc_sz * PAGE_SIZE,
					  &host->sg_dma, GFP_KERNEL);
	if (!host->sg_cpu) {
		dev_err(host->dev, "%s: could not alloc DMA memory\n",
			__func__);
		goto no_dma;
	}

	/* Determine which DMA interface to use */
#ifdef CONFIG_MMC_DW_IDMAC
	host->dma_ops = &dw_mci_idmac_ops;
	dev_info(host->dev, "Using internal DMA controller.\n");
#endif

	if (!host->dma_ops)
		goto no_dma;

	if (host->dma_ops->init && host->dma_ops->start &&
	    host->dma_ops->stop && host->dma_ops->cleanup) {
		if (host->dma_ops->init(host)) {
			dev_err(host->dev, "%s: Unable to initialize "
				"DMA Controller.\n", __func__);
			goto no_dma;
		}
	} else {
		dev_err(host->dev, "DMA initialization not found.\n");
		goto no_dma;
	}

	host->use_dma = 1;

	return;

no_dma:
	dev_info(host->dev, "Using PIO mode.\n");
	host->use_dma = 0;
	return;
}

static bool mci_wait_reset(struct device *dev, struct dw_mci *host)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(500);
	unsigned int ctrl;

	mci_writel(host, CTRL, (SDMMC_CTRL_RESET | SDMMC_CTRL_FIFO_RESET |
				SDMMC_CTRL_DMA_RESET));

	/* wait till resets clear */
	do {
		ctrl = mci_readl(host, CTRL);
		if (!(ctrl & (SDMMC_CTRL_RESET | SDMMC_CTRL_FIFO_RESET |
			      SDMMC_CTRL_DMA_RESET)))
			return true;
	} while (time_before(jiffies, timeout));

	dev_err(dev, "Timeout resetting block (ctrl %#x)\n", ctrl);

	return false;
}

#ifdef CONFIG_OF
static struct dw_mci_of_quirks {
	char *quirk;
	int id;
} of_quirks[] = {
	{
		.quirk	= "supports-highspeed",
		.id	= DW_MCI_QUIRK_HIGHSPEED,
	}, {
		.quirk	= "broken-cd",
		.id	= DW_MCI_QUIRK_BROKEN_CARD_DETECTION,
	},
};

static struct dw_mci_board *dw_mci_parse_dt(struct dw_mci *host)
{
	struct dw_mci_board *pdata;
	struct device *dev = host->dev;
	struct device_node *np = dev->of_node;
	const struct dw_mci_drv_data *drv_data = host->drv_data;
	int idx, ret;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		dev_err(dev, "could not allocate memory for pdata\n");
		return ERR_PTR(-ENOMEM);
	}

	/* find out number of slots supported */
	if (of_property_read_u32(dev->of_node, "num-slots",
				&pdata->num_slots)) {
		dev_info(dev, "num-slots property not found, "
				"assuming 1 slot is available\n");
		pdata->num_slots = 1;
	}

	/* get quirks */
	for (idx = 0; idx < ARRAY_SIZE(of_quirks); idx++)
		if (of_get_property(np, of_quirks[idx].quirk, NULL))
			pdata->quirks |= of_quirks[idx].id;

	if (of_property_read_u32(np, "fifo-depth", &pdata->fifo_depth))
		dev_info(dev, "fifo-depth property not found, using "
				"value of FIFOTH register as default\n");

	if (of_property_read_u32(np, "card-detect-delay", &pdata->detect_delay_ms))
		dev_info(dev, "card-detect-delay property not found, "
				"using default value\n");

	if (drv_data && drv_data->parse_dt) {
		ret = drv_data->parse_dt(host);
		if (ret)
			return ERR_PTR(ret);
	}

	if (of_find_property(np, "keep-power-in-suspend", NULL))
		pdata->pm_caps |= MMC_PM_KEEP_POWER;

	if (of_find_property(np, "keep-power-ignore-pm-notify", NULL))
		pdata->pm_caps |= MMC_PM_IGNORE_PM_NOTIFY;

	if (of_find_property(np, "enable-sdio-wakeup", NULL))
		pdata->pm_caps |= MMC_PM_WAKE_SDIO_IRQ;

	if (of_find_property(np, "caps2-mmc-packed-command", NULL))
		pdata->caps2 |= MMC_CAP2_PACKED_CMD;

	if (of_find_property(np, "caps2-mmc-hs200-1_8v", NULL))
		pdata->caps2 |= MMC_CAP2_HS200_1_8V_SDR;

	if (of_find_property(np, "caps2-mmc-hs200-1_2v", NULL))
		pdata->caps2 |= MMC_CAP2_HS200_1_2V_SDR;

	if (of_find_property(np, "caps2-mmc-cache-ctrl", NULL))
	{
		dev_info(dev, "caps2-mmc-cache-ctrl is set in dts.\n");
		if(!runmode_is_factory()) {
			dev_info(dev, "normal mode cache ctrl on\n");
			pdata->caps2 |= MMC_CAP2_CACHE_CTRL;
		} else {
			dev_info(dev, "factory mode cache ctrl off\n");
		}
	}

	if (of_find_property(np, "caps2-wifi-support-cmd11", NULL)) {
		dev_info(dev, "dw_mci:%d %s find wifi support cmd11 in dts\n",
									host->hw_mmc_id,  __func__);
		pdata->caps2 |= MMC_CAP2_SUPPORT_WIFI_CMD11;
	}

	if (of_find_property(np, "caps-wifi-no-lowpwr", NULL)) {
		dev_info(dev, "dw_mci:%d %s find wifi support no_lowpwr in dts\n",
									host->hw_mmc_id,  __func__);
		pdata->caps2 |= MMC_CAP2_WIFI_NO_LOWPWR;
	}

	if (of_find_property(np, "caps2-support-wifi", NULL)) {
		pr_info("dw_mci:%d %s find caps2-support-wifi in dts\n", host->hw_mmc_id,  __func__);
		pdata->caps2 |= MMC_CAP2_SUPPORT_WIFI;
	}

	if (of_find_property(np, "caps2-support-via-modem", NULL)) {
		pr_info("dw_mci:%d %s find caps2-support-via-modem in dts\n", host->hw_mmc_id,  __func__);
		pdata->caps2 |= MMC_CAP2_SUPPORT_VIA_MODEM;
	}

	if (of_find_property(np, "full-pwr-cycle", NULL))
		pdata->caps2 |= MMC_CAP2_FULL_PWR_CYCLE;

	if (of_find_property(np, "caps2-mmc-ddr50-notify", NULL))
	{
	    if(drv_data && drv_data->caps)
		drv_data->caps[0] |= MMC_CAP_1_8V_DDR|MMC_CAP_UHS_DDR50;
	}

	return pdata;
}

#else /* CONFIG_OF */
static struct dw_mci_board *dw_mci_parse_dt(struct dw_mci *host)
{
	return ERR_PTR(-EINVAL);
}
#endif /* CONFIG_OF */

int dw_mci_probe(struct dw_mci *host)
{
	const struct dw_mci_drv_data *drv_data = host->drv_data;
	int width, i, ret = 0;
	u32 fifo_size;
	int init_slots = 0;

	if (!host->pdata) {
		host->pdata = dw_mci_parse_dt(host);
		if (IS_ERR(host->pdata)) {
			dev_err(host->dev, "platform data not available\n");
			return -EINVAL;
		}
	}

	if (!host->pdata->select_slot && host->pdata->num_slots > 1) {
		dev_err(host->dev,
			"Platform data must supply select_slot function\n");
		return -ENODEV;
	}

	host->biu_clk = devm_clk_get(host->dev, "biu");
	if (IS_ERR(host->biu_clk)) {
		dev_dbg(host->dev, "biu clock not available\n");
	} else {
		ret = clk_prepare_enable(host->biu_clk);
		if (ret) {
			dev_err(host->dev, "failed to enable biu clock\n");
			return ret;
		}
	}

	host->ciu_clk = devm_clk_get(host->dev, "ciu");
	if (IS_ERR(host->ciu_clk)) {
		dev_dbg(host->dev, "ciu clock not available\n");
	} else {
		ret = clk_prepare_enable(host->ciu_clk);
		if (ret) {
			dev_err(host->dev, "failed to enable ciu clock\n");
			goto err_clk_biu;
		}
	}

	if (IS_ERR(host->ciu_clk))
		host->bus_hz = host->pdata->bus_hz;
	else
		host->bus_hz = clk_get_rate(host->ciu_clk);

	host->parent_clk = clk_get_parent(host->ciu_clk);
	if (IS_ERR_OR_NULL(host->parent_clk)) {
		dev_err(host->dev, "failed to get ciu clock parent\n");
		goto err_clk_ciu;
	}

	if (drv_data && drv_data->setup_clock) {
		ret = drv_data->setup_clock(host);
		if (ret) {
			dev_err(host->dev,
				"implementation specific clock setup failed\n");
			goto err_clk_ciu;
		}
	}

	if (!host->bus_hz) {
		dev_err(host->dev,
			"Platform data must supply bus speed\n");
		ret = -ENODEV;
		goto err_clk_ciu;
	}

	host->quirks = host->pdata->quirks;
	host->sd_reinit = 0;
	host->sd_hw_timeout = 0;

	spin_lock_init(&host->lock);
	INIT_LIST_HEAD(&host->queue);

	/*
	 * Get the host data width - this assumes that HCON has been set with
	 * the correct values.
	 */
	i = (mci_readl(host, HCON) >> 7) & 0x7;
	if (!i) {
		host->push_data = dw_mci_push_data16;
		host->pull_data = dw_mci_pull_data16;
		width = 16;
		host->data_shift = 1;
	} else if (i == 2) {
		host->push_data = dw_mci_push_data64;
		host->pull_data = dw_mci_pull_data64;
		width = 64;
		host->data_shift = 3;
	} else {
		/* Check for a reserved value, and warn if it is */
		WARN((i != 1),
		     "HCON reports a reserved host data width!\n"
		     "Defaulting to 32-bit access.\n");
		host->push_data = dw_mci_push_data32;
		host->pull_data = dw_mci_pull_data32;
		width = 32;
		host->data_shift = 2;
	}

	/* Reset all blocks */
	if (!mci_wait_reset(host->dev, host))
		return -ENODEV;

	host->dma_ops = host->pdata->dma_ops;
	dw_mci_init_dma(host);

	/* Clear the interrupts for the host controller */
	mci_writel(host, RINTSTS, 0xFFFFFFFF);

	/* disable all mmc interrupt first */
	mci_writel(host, INTMASK, 0);

	/* Put in max timeout */
	mci_writel(host, TMOUT, 0xFFFFFFFF);

	/*
	 * FIFO threshold settings  RxMark  = fifo_size / 2 - 1,
	 *                          Tx Mark = fifo_size / 2 DMA Size = 8
	 */
	if (!host->pdata->fifo_depth) {
		/*
		 * Power-on value of RX_WMark is FIFO_DEPTH-1, but this may
		 * have been overwritten by the bootloader, just like we're
		 * about to do, so if you know the value for your hardware, you
		 * should put it in the platform data.
		 */
		fifo_size = mci_readl(host, FIFOTH);
		fifo_size = 1 + ((fifo_size >> 16) & 0xfff);
	} else {
		fifo_size = host->pdata->fifo_depth;
	}
	host->fifo_depth = fifo_size;
	host->fifoth_val =
		SDMMC_SET_FIFOTH(0x2, fifo_size / 2 - 1, fifo_size / 2);
	mci_writel(host, FIFOTH, host->fifoth_val);

	/* disable clock to CIU */
	mci_writel(host, CLKENA, 0);
	mci_writel(host, CLKSRC, 0);

	/*
	 * In 2.40a spec, Data offset is changed.
	 * Need to check the version-id and set data-offset for DATA register.
	 */
	host->verid = SDMMC_GET_VERID(mci_readl(host, VERID));
	dev_info(host->dev, "Version ID is %04x\n", host->verid);

	if (host->verid < DW_MMC_240A)
		host->data_offset = DATA_OFFSET;
	else
		host->data_offset = DATA_240A_OFFSET;

	tasklet_init(&host->tasklet, dw_mci_tasklet_func, (unsigned long)host);

	host->card_workqueue = alloc_workqueue("dw-mci-card/%d",
			WQ_MEM_RECLAIM | WQ_NON_REENTRANT, 1, host->hw_mmc_id);
	if (!host->card_workqueue)
		goto err_dmaunmap;

	INIT_WORK(&host->card_work, dw_mci_work_routine_card);
#ifdef CONFIG_HUAWEI_EMMC_DSM
	if(DWMMC_EMMC_ID == host->hw_mmc_id)
		INIT_WORK(&host->dmd_work, dw_mci_dmd_work);
#endif

	setup_timer(&host->timer, dw_mci_timeout_timer, (unsigned long)host);
#ifdef CONFIG_HUAWEI_EMMC_DSM
	if(DWMMC_EMMC_ID == host->hw_mmc_id)
		setup_timer(&host->rw_to_timer, dw_mci_rw_timeout_timer, (unsigned long)host);
#endif

	ret = devm_request_irq(host->dev, host->irq, dw_mci_interrupt,
			       host->irq_flags, "dw-mci", host);
	if (ret)
		goto err_workqueue;

	if (host->pdata->num_slots)
		host->num_slots = host->pdata->num_slots;
	else
		host->num_slots = ((mci_readl(host, HCON) >> 1) & 0x1F) + 1;

	/*
	 * Enable interrupts for command done, data over, data empty, card det,
	 * receive ready and error such as transmit, receive timeout, crc error
	 */
	mci_writel(host, RINTSTS, 0xFFFFFFFF);
#ifdef CONFIG_MMC_DW_IDMAC
	if(SDMMC_32_BIT_DMA == host->dma_64bit_address)
		mci_writel(host, IDSTS, IDMAC_INT_CLR); //32 bit dma interrupt clear
	else
		mci_writel(host, IDSTS_64DMA, IDMAC_INT_CLR); //64 bit dma interrupt clear
#endif
	mci_writel(host, INTMASK, SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVER |
		   SDMMC_INT_TXDR | SDMMC_INT_RXDR |
		   DW_MCI_ERROR_FLAGS | SDMMC_INT_CD);
	mci_writel(host, CTRL, SDMMC_CTRL_INT_ENABLE); /* Enable mci interrupt */

	dev_info(host->dev, "DW MMC controller at irq %d, "
		 "%d bit host data width, "
		 "%u deep fifo\n",
		 host->irq, width, fifo_size);

	/*每个IP可以支持多张卡*/
	/* We need at least one slot to succeed */
	for (i = 0; i < host->num_slots; i++) {
		ret = dw_mci_init_slot(host, i);
		if (ret)
			dev_dbg(host->dev, "slot %d init failed\n", i);
		else
			init_slots++;
	}

	if (init_slots) {
		dev_info(host->dev, "%d slots initialized\n", init_slots);
	} else {
		dev_dbg(host->dev, "attempted to initialize %d slots, "
					"but failed on all\n", host->num_slots);
		goto err_workqueue;
	}

	if (host->quirks & DW_MCI_QUIRK_IDMAC_DTO)
		dev_info(host->dev, "Internal DMAC interrupt fix enabled.\n");

	return 0;

err_workqueue:
	destroy_workqueue(host->card_workqueue);

err_dmaunmap:
	if (host->use_dma && host->dma_ops->exit)
		host->dma_ops->exit(host);

	if(host->vmmc) {
		ret = regulator_disable(host->vmmc);
		if (ret)
			dev_warn(host->dev, "regulator_disable failed ret = %d \n",ret);
	}

err_clk_ciu:
	if (!IS_ERR(host->ciu_clk))
		clk_disable_unprepare(host->ciu_clk);
err_clk_biu:
	if (!IS_ERR(host->biu_clk))
		clk_disable_unprepare(host->biu_clk);
#ifdef CONFIG_HUAWEI_DSM
	dw_mci_dsm_dump(host, DSM_SDIO_DCM_INIT_ERROR_NO);
#endif
	return ret;
}
EXPORT_SYMBOL(dw_mci_probe);

void dw_mci_remove(struct dw_mci *host)
{
	int i;

	mci_writel(host, RINTSTS, 0xFFFFFFFF);
	mci_writel(host, INTMASK, 0); /* disable all mmc interrupt first */

	for (i = 0; i < host->num_slots; i++) {
		dev_dbg(host->dev, "remove slot %d\n", i);
		if (host->slot[i])
			dw_mci_cleanup_slot(host->slot[i], i);
	}

	host->flags &= ~DWMMC_IN_TUNING;
	host->flags &= ~DWMMC_TUNING_DONE;
	host->sd_reinit = 0;

	/* disable clock to CIU */
	mci_writel(host, CLKENA, 0);
	mci_writel(host, CLKSRC, 0);

#ifdef CONFIG_HUAWEI_EMMC_DSM
	if(DWMMC_EMMC_ID == host->hw_mmc_id)
		del_timer_sync(&host->rw_to_timer);
#endif
	del_timer_sync(&host->timer);
	destroy_workqueue(host->card_workqueue);

	if (host->use_dma && host->dma_ops->exit)
		host->dma_ops->exit(host);

	if (host->vmmc) {
		if(regulator_disable(host->vmmc))
			dev_warn(host->dev, "regulator_disable vmmc failed\n");
	}
	if (host->vqmmc) {
		if(regulator_disable(host->vqmmc))
		    dev_warn(host->dev, "regulator_disable vqmmc failed\n");
	}

	if (!IS_ERR(host->ciu_clk))
		clk_disable_unprepare(host->ciu_clk);

	if (!IS_ERR(host->biu_clk))
		clk_disable_unprepare(host->biu_clk);
}
EXPORT_SYMBOL(dw_mci_remove);



#ifdef CONFIG_PM_SLEEP
/*
 * TODO: we should probably disable the clock to the card in the suspend path.
 */
int dw_mci_suspend(struct dw_mci *host)
{
	return 0;
}
EXPORT_SYMBOL(dw_mci_suspend);

int dw_mci_resume(struct dw_mci *host)
{
	int i, ret;

	if (!mci_wait_reset(host->dev, host)) {
		ret = -ENODEV;
		return ret;
	}

	if (host->use_dma && host->dma_ops->init)
		host->dma_ops->init(host);

	/* Restore the old value at FIFOTH register */
	mci_writel(host, FIFOTH, host->fifoth_val);
	host->prev_blksz = 0;

	mci_writel(host, RINTSTS, 0xFFFFFFFF);
	mci_writel(host, INTMASK, SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVER |
		   SDMMC_INT_TXDR | SDMMC_INT_RXDR |
		   DW_MCI_ERROR_FLAGS | SDMMC_INT_CD);
	mci_writel(host, CTRL, SDMMC_CTRL_INT_ENABLE);

	for (i = 0; i < host->num_slots; i++) {
		struct dw_mci_slot *slot = host->slot[i];
		if (!slot)
			continue;
		if(slot->mmc->ios.power_mode == MMC_POWER_OFF)
			continue;

		if (slot->mmc->pm_flags & MMC_PM_KEEP_POWER) {
			dw_mci_set_ios(slot->mmc, &slot->mmc->ios);
			dw_mci_setup_bus(slot, true);
		}
	}

	return 0;
}
EXPORT_SYMBOL(dw_mci_resume);
#endif /* CONFIG_PM_SLEEP */

static int __init dw_mci_init(void)
{
	pr_info("Synopsys Designware Multimedia Card Interface Driver\n");

	return 0;
}

static void __exit dw_mci_exit(void)
{
}

module_init(dw_mci_init);
module_exit(dw_mci_exit);

MODULE_DESCRIPTION("DW Multimedia Card Interface driver");
MODULE_AUTHOR("NXP Semiconductor VietNam");
MODULE_AUTHOR("Imagination Technologies Ltd");
MODULE_LICENSE("GPL v2");
