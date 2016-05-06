/*
 * hisi ipc mailbox driver
 *
 * Copyright (c) 2013- Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/pm_runtime.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/mod_devicetable.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/huawei/mailbox.h>

#define IPCBITMASK(n)				(1 << (n))
#define IPCMBxSOURCE(mdev)			((mdev) << 6)
#define IPCMBxDSET(mdev)			(((mdev) << 6) + 0x04)
#define IPCMBxDCLR(mdev)			(((mdev) << 6) + 0x08)
#define IPCMBxDSTATUS(mdev)			(((mdev) << 6) + 0x0C)
#define IPCMBxMODE(mdev)			(((mdev) << 6) + 0x10)
#define IPCMBxIMASK(mdev)			(((mdev) << 6) + 0x14)
#define IPCMBxICLR(mdev)			(((mdev) << 6) + 0x18)
#define IPCMBxSEND(mdev)			(((mdev) << 6) + 0x1C)
#define IPCMBxDATA(mdev, index)		(((mdev) << 6) + 0x20 + ((index) << 2))
#define IPCCPUxIMST(cpu)			(((cpu) << 3) + 0x800)
#define IPCCPUxIRST(cpu)			(((cpu) << 3) + 0x804)
#define IPCLOCK()				(0xA00)

#ifdef CONFIG_HISI_MAILBOX
#define MODULE_NAME				"hisi_mailbox"
#define FAST_MBOX				(1 << 0)
#define COMM_MBOX				(1 << 1)
#define SOURCE_MBOX				(1 << 2)
#define DESTINATION_MBOX			(1 << 3)
#define SECURE_MBOX				(1 << 4)
#define NONSECURE_MBOX				(1 << 5)

#define HISI_PL320_IPC_MBOX_NUM_NAX		26
#define IPC_UNLOCKED				0x00000000
#define IPCACKMSG				0x00000000
#define UNDEFINED_MBOX_IRQ			(-1)
#define COMM_MBOX_IRQ				(-2)
#define AUTOMATIC_ACK_CONFIG			(1 << 0)
#define NO_FUNC_CONFIG				(0 << 0)

#define IDLE_STATUS				(1 << 4)
#define SOURCE_STATUS				(1 << 5)
#define DESTINATION_STATUS			(1 << 6)
#define ACK_STATUS				(1 << 7)

enum {
	RX_BUFFER_TYPE = 0,
	ACK_BUFFER_TYPE,
	MBOX_BUFFER_TYPE_MAX,
};

/*
 * Table for available remote processors. DTS sub-node, "remote_processor_type",
 * of node, "hisi_ipc", is configured according to the table.
 *
 * If the table was modified, DTS configiuration should be updated accordingly.
 */
typedef enum {
	GIC_1 = 0,
	GIC_2,
	IOM3,
	LPM3,
	HIFI,
	MCPU,
	BBE16,
	UNCERTAIN_REMOTE_PROCESSOR,
	HI3630_RP_TYPES
} remote_processor_type_t;

struct hisi_remote_processor {
	const char		*name;
	remote_processor_type_t	type;
};

struct hisi_common_mbox_info {
	int			gic_1_irq_requested;
	int			gic_2_irq_requested;
	int			cmbox_gic_1_irq;
	int			cmbox_gic_2_irq;
	struct hisi_mbox_device *cmdev;
};

struct hisi_ipc_device {
	void __iomem			*base;
	u32				unlock;
	mbox_msg_t			*buf_pool;
	struct hisi_common_mbox_info	*cmbox_info;
	struct hisi_mbox_device		**mdev_res;
	int				rp_num;
	struct hisi_remote_processor	*rp;
};

struct hisi_mbox_device_priv {
	u8			func;
	const char		*src_name;
	const char		*des_name;
	remote_processor_type_t	src;
	remote_processor_type_t des;
	int			index;
	unsigned int		irq;
	int			capability;
	struct hisi_ipc_device *idev;
};

static inline void __ipc_lock(void __iomem *base, unsigned int lock_key)
{
	__raw_writel(lock_key, base + IPCLOCK());
}

static inline void __ipc_unlock(void __iomem *base, unsigned int key)
{
	__raw_writel(key, base + IPCLOCK());
}

static inline unsigned int __ipc_lock_status(void __iomem *base)
{
	return __raw_readl(base + IPCLOCK());
}

static inline void __ipc_set_src(void __iomem *base, int source, int mdev)
{
	__raw_writel(IPCBITMASK(source), base + IPCMBxSOURCE(mdev));
}

static inline unsigned int __ipc_read_src(void __iomem *base, int mdev)
{
	return __raw_readl(base + IPCMBxSOURCE(mdev));
}

static inline void __ipc_set_des(void __iomem *base, int source, int mdev)
{
	__raw_writel(IPCBITMASK(source), base + IPCMBxDSET(mdev));
}

static inline void __ipc_clr_des(void __iomem *base, int source, int mdev)
{
	__raw_writel(IPCBITMASK(source), base + IPCMBxDCLR(mdev));
}

static inline unsigned int __ipc_des_status(void __iomem *base, int mdev)
{
	return __raw_readl(base + IPCMBxDSTATUS(mdev));
}

static inline void __ipc_send(void __iomem *base, int source, int mdev)
{
	__raw_writel(IPCBITMASK(source), base + IPCMBxSEND(mdev));
}

static inline unsigned int __ipc_read(void __iomem *base, int mdev, int index)
{
	return __raw_readl(base + IPCMBxDATA(mdev, index));
}

static inline void __ipc_write(void __iomem *base, u32 data, int mdev, int index)
{
	__raw_writel(data, base + IPCMBxDATA(mdev, index));
}

static inline unsigned int __ipc_cpu_imask_get(void __iomem *base, int mdev)
{
	return __raw_readl(base + IPCMBxIMASK(mdev));
}

static inline void __ipc_cpu_imask_clr(void __iomem *base, int source, int mdev)
{
	unsigned int reg;

	reg = __raw_readl(base + IPCMBxIMASK(mdev));
	reg = reg & (~(IPCBITMASK(source)));

	__raw_writel(reg, base + IPCMBxIMASK(mdev));
}

static inline void __ipc_cpu_imask_all(void __iomem *base, int mdev)
{
	unsigned int reg;
	int i;

	reg = reg & 0x0;
	for (i = GIC_1; i < UNCERTAIN_REMOTE_PROCESSOR; i++)
		reg = reg | IPCBITMASK(i);

	__raw_writel(reg, base + IPCMBxIMASK(mdev));
}

static inline void __ipc_cpu_iclr(void __iomem *base, int source, int mdev)
{
	__raw_writel(IPCBITMASK(source), base + IPCMBxICLR(mdev));
}

static inline int __ipc_cpu_istatus(void __iomem *base, int mdev)
{
	return __raw_readl(base + IPCMBxICLR(mdev));
}

static inline unsigned int __ipc_mbox_istatus(void __iomem *base, int cpu)
{
	return __raw_readl(base + IPCCPUxIMST(cpu));
}

static inline unsigned int __ipc_status(void __iomem *base, int mdev)
{
	return __raw_readl(base + IPCMBxMODE(mdev));
}

static inline void __ipc_mode(void __iomem *base, unsigned int mode, int mdev)
{
	__raw_writel(mode, base + IPCMBxMODE(mdev));
}

static int hisi_mdev_startup(struct hisi_mbox_device *mdev)
{
	/*
	 * nothing won't be done during suspend & resume flow for HI3630 IPC.
	 * see dummy like SR function, hisi_mdev_suspend & hisi_mdev_resume.
	 * reserve runtime power management proceeding for further modification,
	 * if necessary.
	 */
	return 0;
}

static void hisi_mdev_shutdown(struct hisi_mbox_device *mdev)
{
	/*
	 * nothing won't be done during suspend & resume flow for HI3630 IPC.
	 * see dummy like SR function, hisi_mdev_suspend & hisi_mdev_resume.
	 * reserve runtime power management proceeding for further modification,
	 * if necessary.
	 */
	return;
}

static int
hisi_mdev_remote_processor_is_accessible(struct hisi_mbox_device *mdev,
				mbox_mail_type_t mtype, const char *rp_name)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	struct hisi_ipc_device *idev = priv->idev;
	struct hisi_remote_processor *rp = idev->rp;
	int rp_num = idev->rp_num;
	int ret = RPUNACCESSIBLE;
	int i;

	if (!rp_name)
		goto out;

	/* fast mailbox */
	if ((FAST_MBOX & priv->func)) {
		if ((TX_MAIL == mtype) && (SOURCE_MBOX & priv->func)) {
			if (!strcmp(rp_name, priv->des_name))
				ret = RPACCESSIBLE;
		} else if ((RX_MAIL == mtype) &&
				(DESTINATION_MBOX & priv->func)) {
			for (i = 0; i < rp_num; i++) {
				if (!strcmp(rp_name, rp[i].name)) {
					if (priv->src == rp[i].type)
						ret = RPACCESSIBLE;
					break;
				}
			}
		} else {
			;
		}

		goto out;
	}

	/* common mailbox */
	for (i = 0; i < rp_num; i++) {
		if (!strcmp(rp_name, rp[i].name)) {
			if (!strcmp(rp_name, HI3630_MAILBOX_RP_UNCERTAIN))
				ret = RPUNCERTAIN;
			else
				ret = RPACCESSIBLE;
			goto out;
		}
	}

out:
	return ret;
}

static void hisi_mdev_clr_irq_and_ack(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	unsigned int status = 0;
	unsigned int imask;
	int i;

	/*
	 * temporarily, local processor will clean msg register,
	 * and ack zero for an ipc from remote processors.
	 */
	for (i = 0; i < priv->capability; i++)
		__ipc_write(priv->idev->base, IPCACKMSG, priv->index, i);

	imask = __ipc_cpu_imask_get(priv->idev->base, priv->index);
	if (IPCBITMASK(GIC_1) & (~imask))
		__ipc_cpu_iclr(priv->idev->base, GIC_1, priv->index);

	if (IPCBITMASK(GIC_2) & (~imask))
		__ipc_cpu_iclr(priv->idev->base, GIC_2, priv->index);

	status = __ipc_status(priv->idev->base, priv->index);
	if ((DESTINATION_STATUS & status) && (!(AUTOMATIC_ACK_CONFIG & status))) {
		if (IPCBITMASK(GIC_1) & (~imask))
			__ipc_send(priv->idev->base, GIC_1, priv->index);

		if (IPCBITMASK(GIC_2) & (~imask))
			__ipc_send(priv->idev->base, GIC_2, priv->index);
	}

	return;
}

static mbox_msg_len_t
hisi_mdev_hw_read(struct hisi_mbox_device *mdev, mbox_msg_t *msg)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	mbox_msg_len_t cap;
	int i;

	cap = priv->capability;
	for (i = 0; i < cap; i++)
		msg[i] = __ipc_read(priv->idev->base, priv->index, i);

	return cap;
}

static int hisi_mdev_is_ack(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int is_ack = 0;

	if ((ACK_STATUS & __ipc_status(priv->idev->base, priv->index)))
		is_ack = 1;

	return is_ack;
}

static mbox_msg_len_t
hisi_mdev_receive_msg(struct hisi_mbox_device *mdev, mbox_msg_t **buf)
{
	mbox_msg_t *_buf = NULL;
	mbox_msg_len_t len = 0;

	if (hisi_mdev_is_ack(mdev))
		_buf = mdev->ack_buffer;
	else
		_buf = mdev->rx_buffer;

	if (_buf)
		len = hisi_mdev_hw_read(mdev, _buf);
	*buf = _buf;

	hisi_mdev_clr_irq_and_ack(mdev);
	return len;
}

static void
hisi_mdev_config(struct hisi_mbox_device *mdev,
		const char *src_name, const char *des_name)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	struct hisi_ipc_device *idev = priv->idev;
	struct hisi_remote_processor *rp = idev->rp;
	int rp_num = idev->rp_num;
	int i;

	if ((FAST_MBOX & priv->func))
		return;

	for (i = 0; i < rp_num; i++) {
		if (!strcmp(src_name, rp[i].name))
			priv->src = rp[i].type;

		if (!strcmp(des_name, rp[i].name))
			priv->des = rp[i].type;
	}

	return;
}

static int hisi_mdev_occupy(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int retry = 10;

	do {
		/*
		 * Hardware lock
		 * A hardware lock is needed here to lock a mailbox resource,
		 * which could be used by another remote proccessor, such as
		 * a HiIPCV230 common mailbox-25/mailbox-26.
		 */
		if (!(__ipc_status(priv->idev->base, priv->index) & IDLE_STATUS)) {
			asm volatile("wfe");
		} else {
			__ipc_set_src(priv->idev->base, priv->src, priv->index);
			if (__ipc_read_src(priv->idev->base, priv->index) &
				IPCBITMASK(priv->src))
				break;
		}
		/* Hardware unlock */
	} while (retry--);

	if (!retry)
		return -ENODEV;

	return 0;
}

static int
hisi_mdev_hw_send(struct hisi_mbox_device *mdev, mbox_msg_t *msg,
					mbox_msg_len_t len, int auto_ack)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int i;

	/* interrupts unmask */
	__ipc_cpu_imask_all(priv->idev->base, priv->index);
	__ipc_cpu_imask_clr(priv->idev->base, priv->src, priv->index);
	__ipc_cpu_imask_clr(priv->idev->base, priv->des, priv->index);

	/* des config */
	if ((COMM_MBOX & priv->func))
		__ipc_set_des(priv->idev->base, priv->des, priv->index);

	/* ipc mode config */
	if (auto_ack)
		__ipc_mode(priv->idev->base, AUTOMATIC_ACK_CONFIG, priv->index);
	else
		__ipc_mode(priv->idev->base, NO_FUNC_CONFIG, priv->index);

	/* write data */
	for (i = 0; i < ((priv->capability < len) ? priv->capability : len); i++)
		__ipc_write(priv->idev->base, msg[i], priv->index, i);

	/* enable sending */
	__ipc_send(priv->idev->base, priv->src, priv->index);
	return 0;
}

static int
hisi_mdev_send_msg(struct hisi_mbox_device *mdev, const char *rp_name,
			mbox_msg_t *msg, mbox_msg_len_t len, int need_auto_ack)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int err = 0;

	if ((FAST_MBOX & priv->func) && (DESTINATION_MBOX & priv->func)) {
		pr_err("%s: mdev %s has no tx ability\n", MODULE_NAME, mdev->name);
		err = -EMDEVCLEAN;
		goto out;
	}

	hisi_mdev_config(mdev, HI3630_MAILBOX_RP_GIC2, rp_name);

	if (hisi_mdev_occupy(mdev)) {
		pr_err("%s: mdev %s can not be occupied\n", MODULE_NAME, mdev->name);
		err = -EMDEVCLEAN;
		goto out;
	}

	if (hisi_mdev_hw_send(mdev, msg, len, need_auto_ack)) {
		pr_err("%s: mdev %s can not be sent\n", MODULE_NAME, mdev->name);
		err = -EMDEVDIRTY;
		goto out;
	}

out:
	return err;
}

static void hisi_mdev_release(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;

	__ipc_cpu_imask_all(priv->idev->base, priv->index);
	__ipc_set_src(priv->idev->base, priv->src, priv->index);

	asm volatile("sev");
	return;
}

static int
hisi_mdev_irq_request(struct hisi_mbox_device *mdev,
				irq_handler_t handler, void *p)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int ret = 0;

	if (COMM_MBOX_IRQ == priv->irq) {
		if (!priv->idev->cmbox_info->gic_1_irq_requested++) {
			ret = request_irq(priv->idev->cmbox_info->cmbox_gic_1_irq,
					handler,
					IRQF_DISABLED,
					mdev->name,
					(void *)priv->idev->cmbox_info->cmdev);
			if (ret) {
				pr_err("%s: common %s request gic_1_irq %d failed\n",
					MODULE_NAME, mdev->name,
					priv->idev->cmbox_info->cmbox_gic_1_irq);
				priv->idev->cmbox_info->gic_1_irq_requested--;
				goto out;
			}
		}

		if (!priv->idev->cmbox_info->gic_2_irq_requested++) {
			ret = request_irq(priv->idev->cmbox_info->cmbox_gic_2_irq,
					handler,
					IRQF_DISABLED,
					mdev->name,
					(void *)priv->idev->cmbox_info->cmdev);
			if (ret) {
				pr_err("%s: common %s request gic_2_irq %d failed\n",
					MODULE_NAME, mdev->name,
					priv->idev->cmbox_info->cmbox_gic_2_irq);
				priv->idev->cmbox_info->gic_2_irq_requested--;
				free_irq(priv->idev->cmbox_info->cmbox_gic_1_irq,
					(void *)priv->idev->cmbox_info->cmdev);
				priv->idev->cmbox_info->gic_1_irq_requested--;
				goto out;
			}
		}
	} else if (priv->idev->cmbox_info->cmbox_gic_1_irq == priv->irq) {
		if (!priv->idev->cmbox_info->gic_1_irq_requested++) {
			ret = request_irq(priv->irq,
					handler,
					IRQF_DISABLED,
					mdev->name,
					(void *)priv->idev->cmbox_info->cmdev);
			if (ret) {
				pr_err("%s: fast source %s request gic_1_irq %d failed\n",
					MODULE_NAME, mdev->name, priv->irq);
				priv->idev->cmbox_info->gic_1_irq_requested--;
				goto out;
			}
		}
	} else if (priv->idev->cmbox_info->cmbox_gic_2_irq == priv->irq) {
		if (!priv->idev->cmbox_info->gic_2_irq_requested++) {
			ret = request_irq(priv->irq,
					handler,
					IRQF_DISABLED,
					mdev->name,
					(void *)priv->idev->cmbox_info->cmdev);
			if (ret) {
				pr_err("%s: fast source %s request gic_2_irq %d failed\n",
					MODULE_NAME, mdev->name, priv->irq);
				priv->idev->cmbox_info->gic_2_irq_requested--;
				goto out;
			}
		}
	} else {
		ret = request_irq(priv->irq, handler, IRQF_DISABLED, mdev->name, p);
		if (ret) {
			pr_err("%s: fast desitnation %s request irq %d failed\n",
					MODULE_NAME, mdev->name, priv->irq);
			goto out;
		}
	}

out:
	return ret;
}

static void hisi_mdev_irq_free(struct hisi_mbox_device *mdev, void *p)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;

	if (COMM_MBOX_IRQ == priv->irq) {
		if (!--priv->idev->cmbox_info->gic_1_irq_requested)
			free_irq(priv->idev->cmbox_info->cmbox_gic_1_irq,
				(void *)priv->idev->cmbox_info->cmdev);

		if (!--priv->idev->cmbox_info->gic_2_irq_requested)
			free_irq(priv->idev->cmbox_info->cmbox_gic_2_irq,
				(void *)priv->idev->cmbox_info->cmdev);
	} else if (priv->idev->cmbox_info->cmbox_gic_1_irq == priv->irq) {
		if (!--priv->idev->cmbox_info->gic_1_irq_requested)
			free_irq(priv->irq, (void *)priv->idev->cmbox_info->cmdev);
	} else if (priv->idev->cmbox_info->cmbox_gic_2_irq == priv->irq) {
		if (!--priv->idev->cmbox_info->gic_2_irq_requested)
			free_irq(priv->irq, (void *)priv->idev->cmbox_info->cmdev);
	} else {
		free_irq(priv->irq, p);
	}

	return;
}

static struct hisi_mbox_device *
hisi_mdev_irq_to_mdev(struct hisi_mbox_device *_mdev, struct hisi_mbox_device **list, int irq)
{
	struct hisi_mbox_device_priv *_priv = _mdev->priv;
	struct hisi_mbox_device *mdev = NULL;
	struct hisi_mbox_device_priv *priv = NULL;
	remote_processor_type_t src = UNCERTAIN_REMOTE_PROCESSOR;
	unsigned int regval = 0x0;
	int i;

	if (!list) {
		pr_err("%s: invalid input\n", MODULE_NAME);
		goto err;
	}

	/* fast destination mailboxes use unique irq number */
	if ((DESTINATION_MBOX & _priv->func) && (FAST_MBOX & _priv->func)) {
		mdev = _mdev;
		goto out;
	}

	/* fast source & common mailboxes share GIC_1 & GIC_2 irq number */
	if (irq == _priv->idev->cmbox_info->cmbox_gic_1_irq) {
		src = GIC_1;
	} else if (irq == _priv->idev->cmbox_info->cmbox_gic_2_irq) {
		src = GIC_2;
	} else {
		pr_err("%s: odd irq for hisi mailboxes\n", MODULE_NAME);
		goto err;
	}

	regval = __ipc_mbox_istatus(_priv->idev->base, src);
	for (i = 0; (mdev = list[i]); i++) {
		priv = mdev->priv;

		if ((regval & IPCBITMASK(priv->index)) &&
			((priv->func & SOURCE_MBOX) || (priv->func & COMM_MBOX)))
			goto out;
	}

err:
out:
	/* it is nearly occured */
	return mdev;
}

struct hisi_mbox_dev_ops hisi_mdev_ops = {
	.startup = hisi_mdev_startup,
	.shutdown = hisi_mdev_shutdown,
	.ability = hisi_mdev_remote_processor_is_accessible,

	.read = hisi_mdev_receive_msg,
	.send = hisi_mdev_send_msg,
	.refresh = hisi_mdev_release,

	.request_irq = hisi_mdev_irq_request,
	.free_irq = hisi_mdev_irq_free,
	.irq_to_mdev = hisi_mdev_irq_to_mdev,
};

static void hisi_ipc_device_put(struct hisi_ipc_device *idev)
{
	struct hisi_mbox_device **list = idev->mdev_res;
	struct hisi_mbox_device *mdev = NULL;
	int i;

	iounmap(idev->base);

	kfree(idev->rp);
	kfree(idev->cmbox_info);
	kfree(idev->buf_pool);

	for (i = 0; (mdev = list[i]); i++) {
		kfree(mdev->priv);
		kfree(mdev);
	}

	return;
}

static int hisi_ipc_remove(struct platform_device *pdev)
{
	struct hisi_ipc_device *idev = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);

	hisi_mbox_device_unregister();

	if (idev) {
		hisi_ipc_device_put(idev);
		kfree(idev->mdev_res);
		kfree(idev);
	}

	return 0;
}

static int
hisi_ipc_device_get(struct hisi_ipc_device *idev,
		struct hisi_mbox_device **mdevs, struct device_node *node)
{
	struct device_node *son = NULL;
	struct hisi_common_mbox_info *cmbox_info = NULL;
	struct hisi_mbox_device *mdev;
	struct hisi_mbox_device_priv *priv;
	remote_processor_type_t	src_bit;
	remote_processor_type_t	des_bit;
	mbox_msg_t *buf_pool = NULL;
	mbox_msg_len_t buf_pool_len = 0;
	const char *mdev_name = NULL;
	const char *src_name = NULL;
	const char *des_name = NULL;
	struct hisi_remote_processor *rp;
	mbox_msg_t *rx_buffer = NULL;
	mbox_msg_t *ack_buffer = NULL;
	u8 func = 0;
	u32 output[3] = {0};
	int rp_num = 0;
	int irq = 0;
	int i = 0;
	int index;
	int ret = 0;
	int cm_gic_1_irq = -1;
	int cm_gic_2_irq = -1;
	int capability = 0;
	u32 unlock = 0;
	void __iomem *ipc_base = NULL;

	ipc_base = of_iomap(node, 0);
	if (!ipc_base) {
		pr_err("%s: iomap error\n", MODULE_NAME);
		ret = -ENOMEM;
		goto out;
	}

	ret = of_property_read_u32(node, "capability", &capability);
	if (ret) {
		pr_err("%s: prop \"capability\" error %d\n", MODULE_NAME, ret);
		ret = -ENODEV;
		goto to_iounmap;
	}

	ret = of_property_read_u32(node, "unlock_key", &unlock);
	if (ret) {
		pr_err("%s: prop \"key\" error %d\n", MODULE_NAME, ret);
		ret = -ENODEV;
		goto to_iounmap;
	}

	ret = of_property_read_u32(node, "remote_processor_num", &rp_num);
	if (ret) {
		pr_err("%s: prop \"remote_processor_num\" error %d\n",
							MODULE_NAME, ret);
		ret = -ENODEV;
		goto to_iounmap;
	}

	rp = kmalloc(sizeof(*rp) * rp_num, GFP_KERNEL);
	if (!rp) {
		ret = -ENOMEM;
		goto to_iounmap;
	}

	for (i = 0; i < rp_num; i++) {
		ret = of_property_read_string_index(node,
				"remote_processor", i, &rp[i].name);
		if (ret)
			break;

		ret = of_property_read_u32_index(node,
			"remote_processor_type", i, &rp[i].type);
		if (ret)
			break;

	}

	if (ret) {
		pr_err("%s: prop \"remote_processor\" error %d\n",
							MODULE_NAME, ret);
		ret = -ENODEV;
		goto free_rp;
	}

	cmbox_info = kmalloc(sizeof(*cmbox_info), GFP_KERNEL);
	if (!cmbox_info) {
		ret = -ENOMEM;
		goto free_rp;
	}

	buf_pool_len = capability * MBOX_BUFFER_TYPE_MAX *
				HISI_PL320_IPC_MBOX_NUM_NAX;
	buf_pool = kzalloc(sizeof(mbox_msg_t) * buf_pool_len, GFP_KERNEL);
	if (!buf_pool) {
		ret = -ENOMEM;
		goto free_cmbox;
	}

	cm_gic_1_irq = irq_of_parse_and_map(node, 0);
	cm_gic_2_irq = irq_of_parse_and_map(node, 1);

	cmbox_info->gic_1_irq_requested = 0;
	cmbox_info->gic_2_irq_requested = 0;
	cmbox_info->cmbox_gic_1_irq = cm_gic_1_irq;
	cmbox_info->cmbox_gic_2_irq = cm_gic_2_irq;

	idev->cmbox_info = cmbox_info;
	idev->unlock = unlock;
	idev->base = ipc_base;
	idev->mdev_res = mdevs;
	idev->buf_pool = buf_pool;
	idev->rp_num = rp_num;
	idev->rp = rp;

	for (i = 0; (son = of_get_next_child(node, son)); i++) {
		mdev = NULL;
		priv = NULL;
		mdev_name = NULL;
		func = 0;
		src_name = NULL;
		des_name = NULL;
		index = -1;
		irq = UNDEFINED_MBOX_IRQ;
		rx_buffer = NULL;
		ack_buffer = NULL;

		mdev = kzalloc(sizeof(*mdev), GFP_KERNEL);
		if (!mdev) {
			ret = -ENOMEM;
			goto to_break;
		}

		priv = kzalloc(sizeof(*priv), GFP_KERNEL);
		if (!priv) {
			ret = -ENOMEM;
			goto free_mdev;
		}

		mdev_name = son->name;

		ret = of_property_read_string(son,
				"src_remote_processor", &src_name);
		if (ret)
			goto free_priv;

		ret = of_property_read_string(son,
				"des_remote_processor", &des_name);
		if (ret)
			goto free_priv;

		ret = of_property_read_u32(son, "src_bit", &src_bit);
		if (ret)
			goto free_priv;

		ret = of_property_read_u32(son, "des_bit", &des_bit);
		if (ret)
			goto free_priv;

		ret  = of_property_read_u32(son, "index", &index);
		if (ret)
			goto free_priv;

		ret = of_property_read_u32_array(son, "func", output, 3);
		if (ret)
			goto free_priv;

		func |= (output[0] ? FAST_MBOX : COMM_MBOX);

		func |= (output[1] ? SOURCE_MBOX : 0);

		func |= (output[2] ? DESTINATION_MBOX : 0);

		if ((FAST_MBOX & func) && (DESTINATION_MBOX & func)) {
			irq = irq_of_parse_and_map(son, 0);
		} else if ((FAST_MBOX & func) && (SOURCE_MBOX & func)) {
			irq = (GIC_1 == src_bit) ? cm_gic_1_irq : cm_gic_2_irq;
		} else {
			/* maybe GIC_1 OR GIC_2 */
			irq = COMM_MBOX_IRQ;
			cmbox_info->cmdev = mdev;
		}

		rx_buffer = buf_pool + capability * RX_BUFFER_TYPE;
		ack_buffer = buf_pool + capability * ACK_BUFFER_TYPE;
		buf_pool = buf_pool + capability * MBOX_BUFFER_TYPE_MAX;

		priv->capability = capability;
		priv->func = func;
		priv->src_name = src_name;
		priv->des_name = des_name;
		priv->src = src_bit;
		priv->des = des_bit;
		priv->irq = irq;
		priv->index = index;
		priv->idev = idev;

		mdev->name = mdev_name;
		mdev->priv = priv;
		mdev->rx_buffer =  rx_buffer;
		mdev->ack_buffer = ack_buffer;
		mdev->ops = &hisi_mdev_ops;

		mdevs[i] = mdev;
		continue;
free_priv:
		kfree(priv);
free_mdev:
		kfree(mdev);
to_break:
		break;
	}

	if (ret)
		goto deinit_mdevs;

	return ret;

deinit_mdevs:
	while (i--) {
		kfree(mdevs[i]->priv);
		kfree(mdevs[i]);
	}

	kfree(buf_pool);
free_cmbox:
	kfree(cmbox_info);
free_rp:
	kfree(rp);
to_iounmap:
	iounmap(ipc_base);
out:
	return ret;
}

static int hisi_ipc_probe(struct platform_device *pdev)
{
	struct hisi_ipc_device *idev = NULL;
	struct hisi_mbox_device **mdev_res = NULL;
	struct device_node *node = NULL;
	int mdev_num = 0;
	int ret = 0;
	int timeout = 10;

	idev = kmalloc(sizeof(*idev), GFP_KERNEL);
	if (!idev) {
		pr_err("%s: no mem for ipc resouce\n", MODULE_NAME);
		ret = -ENOMEM;
		goto out;
	}

	node = of_find_compatible_node(NULL, NULL, "hisilicon,HiIPCV230");
	if (!node) {
		pr_err("%s: dts[%s] node not found\n",
				MODULE_NAME, "hisilicon,HiIPCV230");
		ret = -ENODEV;
		goto free_idev;
	}

	ret = of_property_read_u32(node, "mailboxes", &mdev_num);
	if (ret) {
		pr_err("%s: no mailboxes resources\n", MODULE_NAME);
		ret = -ENODEV;
		goto free_idev;
	}

	mdev_res = kzalloc((sizeof(*mdev_res) * mdev_num), GFP_KERNEL);
	if (!mdev_res) {
		ret = -ENOMEM;
		goto free_idev;
	}

	ret = hisi_ipc_device_get(idev, mdev_res, node);
	if (ret) {
		pr_err("%s: can not get ipc resource\n", MODULE_NAME);
		ret = -ENODEV;
		goto free_mdevs;
	}

	ret = hisi_mbox_device_register(&pdev->dev, mdev_res);
	if (ret) {
		pr_err("%s: mdevs register failed\n", MODULE_NAME);
		ret = -ENODEV;
		goto put_res;
	}

	while (IPC_UNLOCKED != __ipc_lock_status(idev->base)) {
		__ipc_unlock(idev->base, idev->unlock);
		if (!timeout) {
			pr_err("%s: ipc unlock timeout\n", MODULE_NAME);
			ret = -ENODEV;
			goto unregister;
		}
		timeout--;
		msleep(1);
	}

	platform_set_drvdata(pdev, idev);

	pr_info("%s: HiIPCV230 mailboxes are ready\n", MODULE_NAME);
	return 0;

unregister:
	hisi_mbox_device_unregister();
put_res:
	hisi_ipc_device_put(idev);
free_mdevs:
	kfree(idev->mdev_res);
free_idev:
	kfree(idev);
out:
	return ret;
}

static int hisi_ipc_device_suspend(struct device *dev)
{
	struct platform_device *pdev =
		container_of(dev, struct platform_device, dev);
	struct hisi_ipc_device *idev = platform_get_drvdata(pdev);

	pr_info("%s: suspend +\n", __func__);
	hisi_mbox_device_deactivate(idev->mdev_res);
	pr_info("%s: suspend -\n", __func__);
	return 0;
}

static int hisi_ipc_device_resume(struct device *dev)
{
	struct platform_device *pdev =
		container_of(dev, struct platform_device, dev);
	struct hisi_ipc_device *idev = platform_get_drvdata(pdev);

	pr_info("%s: resume +\n", __func__);
	hisi_mbox_device_activate(idev->mdev_res);
	pr_info("%s: resume -\n", __func__);
	return 0;
}
#endif

#ifdef CONFIG_OF
static const struct of_device_id hisi_ipc_of_match[] = {
	{.compatible = "hisilicon,HiIPCV230",},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_mdev_of_match);
#endif

static const struct dev_pm_ops hisi_ipc_dev_pm_ops = {
	.suspend_late = hisi_ipc_device_suspend,
	.resume_early = hisi_ipc_device_resume,
};

static struct platform_driver hisi_ipc_driver = {
	.probe = hisi_ipc_probe,
	.remove = hisi_ipc_remove,
	.driver = {
		.name = "HiIPCV230-mailbox",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_ipc_of_match),
		.pm = &hisi_ipc_dev_pm_ops,
	},
};

static int __init hisi_ipc_init(void)
{
	pr_debug("%s: init\n", MODULE_NAME);

	platform_driver_register(&hisi_ipc_driver);
	return 0;
}
core_initcall(hisi_ipc_init);

static void __exit hisi_ipc_exit(void)
{
	platform_driver_unregister(&hisi_ipc_driver);
	return;
}
module_exit(hisi_ipc_exit);

MODULE_DESCRIPTION("HiIPCV230 ipc, mailbox device driver");
MODULE_LICENSE("GPL V2");
