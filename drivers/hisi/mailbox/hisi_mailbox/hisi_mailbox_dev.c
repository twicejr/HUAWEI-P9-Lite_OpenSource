/*
 * hi3xxx mailbox device driver
 *
 * Copyright (c) 2013-2014 Hisilicon Technologies CO., Ltd.
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
#include <linux/hisi/hisi_mailbox.h>
#include <linux/hisi/hi3xxx_irq_affinity.h>
#include <linux/kern_levels.h>

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

#define MODULE_NAME				"hisi_mailbox_dev"
#define FAST_MBOX				(1 << 0)
#define COMM_MBOX				(1 << 1)
#define SOURCE_MBOX				(1 << 2)
#define DESTINATION_MBOX			(1 << 3)
/*#define SECURE_MBOX				(1 << 4)
#define NONSECURE_MBOX				(1 << 5)*/

#define IPC_UNLOCKED				0x00000000
#define IPCACKMSG				0x00000000
#define COMM_MBOX_IRQ				(-2)
#define AUTOMATIC_ACK_CONFIG			(1 << 0)
#define NO_FUNC_CONFIG				(0 << 0)

/* Optimize interrupts assignment */
#define IPC_IRQ_AFFINITY_CPU			(1)

#define SYS_RPROC_NUMBER  0x8
#define ISP_RPROC_NUMBER  0x2
#define STATE_NUMBER  0x4

#define MAILBOX_ASYNC_TIMEOUT_CNT  (1060)
#define MAILBOX_ASYNC_UDELAY_CNT   (1000)

#define MDEV_TRACE(fmt, args ...)	\
	({				\
		pr_err("%s(%d):" fmt "\n", \
			MODULE_NAME, __LINE__, ##args); \
	})
/*MDEV_DEBUG used only in project  developing  phase*/
#define MDEV_DEBUG(fmt, args ...)
/*
	({				\
		pr_debug("%s(%d):" fmt "\n", \
			MODULE_NAME, __LINE__, ##args); \
	})
*/
enum {
	RX_BUFFER_TYPE = 0,
	ACK_BUFFER_TYPE,
	MBOX_BUFFER_TYPE_MAX,
};

/*
 * Table for available remote processors. DTS sub-node, "remote_processor_type",
 * of node, "hisi_mdev", is configured according to the table.
 *
 * If the table was modified, DTS configiuration should be updated accordingly.
 */
typedef enum {
	GIC = 0,
	GIC_1 = 0,
	GIC_2,
	IOM3,
	LPM3,
	HIFI,
	MCPU,
	BBE16,
	IVP32,
	ISP,
	UNCERTAIN_REMOTE_PROCESSOR,
	HI3XXX_RP_TYPES
} remote_processor_type_t;

struct hisi_remote_processor {
	const char *name;
	remote_processor_type_t type;
};

struct hisi_common_mbox_info {
	int gic_1_irq_requested;
	int gic_2_irq_requested;
	int cmbox_gic_1_irq;
	int cmbox_gic_2_irq;
	struct hisi_mbox_device *cmdev;
};

struct hisi_ipc_device {
	void __iomem *base;
	u32 unlock;
	mbox_msg_t *buf_pool;
	struct hisi_common_mbox_info *cmbox_info;
	struct hisi_mbox_device **mdev_res;
	int rp_num;
	struct hisi_remote_processor *rp;
};

struct hisi_mbox_device_priv {
	u8 func;
	const char *src_name;
	const char *des_name;
	remote_processor_type_t src;
	remote_processor_type_t des;
	int index;
	int irq;
	int capability;
	struct hisi_ipc_device *idev;
};

/*
**HiIPCV230 fixed all the communicate  processors to the unique bits:
**austin:
**00000001:A53
**00000010:Maia
**00000100:IOM7
**00001000:LPM3
**00010000:ASP
**00100000:Modem-A9
**01000000:Modem-bbe16
**10000000:IVP32
**
**seattle:
**0000001:A15
**0000010:A7
**0000100:IOM3
**0001000:LPM3
**0010000:ASP
**0100000:Modem-A9
**1000000:Modem-bbe16
*/
char *sys_rproc_name[SYS_RPROC_NUMBER] = {
	"AP_LIT_CLUSTER",
	"AP_BIG_CLUSTER",
	"SENSORHUB",
	"LPMCU",
	"HIFI",
	"MODEM",
	"BBE16",
	"IVP"
};

char *isp_rproc_name[ISP_RPROC_NUMBER] = {
	"AP_LIT_CLUSTER",
	"ISP"
};

/*
**HiIPCV230 have a state machine, the state machine have 4 status:
**4'b0001:IDLE_STATE
**4'b0010:SOURCE_STATE
**4'b0100:DEST_STATE
**4'b1000:ACK_STATE
*/
char *ipc_state_name[STATE_NUMBER] = {
	"%s  is idle\n",
	"%s  is occupied\n",
	"%s  may be power off or freeze\n",
	"%s  have no time to handle ACK\n"
};

enum IPC_STATE_MACHINE {
	IDLE_STATE,
	SOURCE_STATE,
	DEST_STATE,
	ACK_STATE
};

extern int hisi_rproc_init(void);

char *rproc_analysis(const char *mdev_name, unsigned int pro_code)
{
	unsigned char index = 0;
	while (pro_code) {
		index++;
		pro_code >>= 1;
	}
	if (likely(0 != index))
		index--;
	else
		return "ERR_RPROC";
	/*sys ips's mailbox channel */
	if (NULL == strstr(mdev_name, "isp")) {
		if (likely(index < SYS_RPROC_NUMBER))
			return sys_rproc_name[index];
		else
			return "ERR_RPROC";
	} else {					/*isp  ips's mailbox channel */

		if (likely(index < ISP_RPROC_NUMBER))
			return isp_rproc_name[index];
		else
			return "ERR_RPROC";
	}

}

char *ipc_state_analysis(unsigned int mode, unsigned char *outp)
{
	unsigned char index = 0;
	mode >>= 4;					/*bit4~bit7 is the state machine index */
	while (mode) {
		index++;
		mode >>= 1;
	}
	if (likely(0 != index))
		index--;
	else
		return "%s ERR_STATE\n";

	*outp = index;

	if (likely(index < STATE_NUMBER))
		return ipc_state_name[index];
	else
		return "%s ERR_STATE\n";
}

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

static inline void __ipc_send(void __iomem *base, unsigned int tosend, int mdev)
{
	__raw_writel(tosend, base + IPCMBxSEND(mdev));
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

static inline void __ipc_cpu_imask_clr(void __iomem *base, unsigned int toclr, int mdev)
{
	unsigned int reg;

	reg = __raw_readl(base + IPCMBxIMASK(mdev));
	reg = reg & (~(toclr));

	__raw_writel(reg, base + IPCMBxIMASK(mdev));
}

static inline void __ipc_cpu_imask_all(void __iomem *base, int mdev)
{
	__raw_writel((~0), base + IPCMBxIMASK(mdev));
}

static inline void __ipc_cpu_iclr(void __iomem *base, unsigned int toclr, int mdev)
{
	__raw_writel(toclr, base + IPCMBxICLR(mdev));
}

static inline int __ipc_cpu_istatus(void __iomem *base, int mdev)
{
	return __raw_readl(base + IPCMBxICLR(mdev));
}

static inline unsigned int __ipc_mbox_istatus(void __iomem *base, int cpu)
{
	return __raw_readl(base + IPCCPUxIMST(cpu));
}

static inline unsigned int __ipc_mbox_irstatus(void __iomem *base, int cpu)
{
	return __raw_readl(base + IPCCPUxIRST(cpu));
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
	 * nothing won't be done during suspend & resume flow for HI3xxx IPC.
	 * see dummy like SR function, hisi_mdev_suspend & hisi_mdev_resume.
	 * reserve runtime power management proceeding for further modification,
	 * if necessary.
	 */
	return 0;
}

static void hisi_mdev_shutdown(struct hisi_mbox_device *mdev)
{
	/*
	 * nothing won't be done during suspend & resume flow for HI3xxx IPC.
	 * see dummy like SR function, hisi_mdev_suspend & hisi_mdev_resume.
	 * reserve runtime power management proceeding for further modification,
	 * if necessary.
	 */
	return;
}

static void hisi_mdev_dump_status(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	/*the size 64 is the sumary max size of  sys_rproc_name and ipc_state_name */
	char finalfortmat[64] = { 0 };
	char statem = 0;
	char *src_name = rproc_analysis(mdev->name, __ipc_read_src(priv->idev->base, priv->index));
	char *des_name = rproc_analysis(mdev->name, __ipc_des_status(priv->idev->base, priv->index));
	/*\0013 is the  KERN_SOH KERN_ERR */
	char *direcstr = KERN_ERR "\n<INFO>: [%s]-->[%s], ";
	char *machinestr = ipc_state_analysis(__ipc_status(priv->idev->base, priv->index), &statem);

	memcpy(finalfortmat, direcstr, strlen(direcstr));

	strncat(finalfortmat, machinestr, strlen(machinestr));

	if (DEST_STATE == statem)
		printk(finalfortmat, src_name, des_name, des_name);
	else if (ACK_STATE == statem)
		printk(finalfortmat, src_name, des_name, src_name);
	else
		printk(finalfortmat, src_name, des_name, mdev->name);

#if  0							/*see above Analyzation is enough, open it if you want to see the clearly register dump */
	pr_info("====  mdev-%d registers dump  ====\n  [SOURCE]  : 0x%08x\n  [DSTATUS] : 0x%08x\n  [MODE]    : 0x%08x\n  [IMASK]   : 0x%08x\n  [ICLR]    : 0x%08x\n  [CPUIRST]   : 0x%08x\n  [DATA0]   : 0x%08x\n  [DATA1]   : 0x%08x\n==============  end  =============\n",
		priv->index, __ipc_read_src(priv->idev->base, priv->index), __ipc_des_status(priv->idev->base, priv->index),
		__ipc_status(priv->idev->base, priv->index), __ipc_cpu_imask_get(priv->idev->base, priv->index),
		__ipc_cpu_istatus(priv->idev->base, priv->index), __ipc_mbox_irstatus(priv->idev->base, priv->des),
		__ipc_read(priv->idev->base, priv->index, 0), __ipc_read(priv->idev->base, priv->index, 1));
#endif

	return;
}

static int hisi_mdev_check(struct hisi_mbox_device *mdev, mbox_mail_type_t mtype, const char *rp_name)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int ret = RPUNACCESSIBLE;

	if ((TX_MAIL == mtype) && (SOURCE_MBOX & priv->func) && !strcmp(rp_name, priv->des_name))
		ret = RPACCESSIBLE;
	else if ((RX_MAIL == mtype) && (DESTINATION_MBOX & priv->func) && !strcmp(rp_name, priv->src_name))
		ret = RPACCESSIBLE;

	return ret;
}

static void hisi_mdev_clr_ack(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	unsigned int imask;
	unsigned int toclr;

	imask = __ipc_cpu_imask_get(priv->idev->base, priv->index);
	toclr = (IPCBITMASK(GIC_1) | IPCBITMASK(GIC_2)) & (~imask);
	__ipc_cpu_iclr(priv->idev->base, toclr, priv->index);
}

static void hisi_mdev_clr_irq_and_ack(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	unsigned int status = 0;
	unsigned int imask;
	unsigned int todo;
	int i;

	/*
	 * temporarily, local processor will clean msg register,
	 * and ack zero for an ipc from remote processors.
	 */
	for (i = 0; i < priv->capability; i++)
		__ipc_write(priv->idev->base, IPCACKMSG, priv->index, i);

	imask = __ipc_cpu_imask_get(priv->idev->base, priv->index);
	/*get the irq unmask core bits, and clear the irq according to the unmask core bits,
	 * because the irq to be sure triggered to the unmasked cores
	 */
	todo = (IPCBITMASK(GIC_1) | IPCBITMASK(GIC_2)) & (~imask);
	__ipc_cpu_iclr(priv->idev->base, todo, priv->index);

	status = __ipc_status(priv->idev->base, priv->index);

	if ((DESTINATION_STATUS & status) && (!(AUTOMATIC_ACK_CONFIG & status))) {
		__ipc_send(priv->idev->base, todo, priv->index);
	}

	return;
}

static void hisi_mdev_ack(struct hisi_mbox_device *mdev, mbox_msg_t *msg, mbox_msg_len_t len)
{
	return;
}

static mbox_msg_len_t hisi_mdev_hw_read(struct hisi_mbox_device *mdev, mbox_msg_t *msg)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	mbox_msg_len_t cap;
	int i;

	cap = priv->capability;
	for (i = 0; i < cap; i++)
		msg[i] = __ipc_read(priv->idev->base, priv->index, i);

	return cap;
}

/*to judge the four kind machine status of the ip, they are idle,src,des,ack*/
static int hisi_mdev_is_stm(struct hisi_mbox_device *mdev, unsigned int stm)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int is_stm = 0;

	if ((stm & __ipc_status(priv->idev->base, priv->index)))
		is_stm = 1;

	return is_stm;
}

static mbox_msg_len_t hisi_mdev_receive_msg(struct hisi_mbox_device *mdev, mbox_msg_t **buf)
{
	mbox_msg_t *_buf = NULL;
	mbox_msg_len_t len = 0;

	if (hisi_mdev_is_stm(mdev, ACK_STATUS))
		_buf = mdev->ack_buffer;
	else
		_buf = mdev->rx_buffer;

	if (_buf)
		len = hisi_mdev_hw_read(mdev, _buf);
	*buf = _buf;

	hisi_mdev_clr_irq_and_ack(mdev);
	return len;
}

static int hisi_mdev_unlock(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int retry = 3;

	do {
		__ipc_unlock(priv->idev->base, priv->idev->unlock);
		if (IPC_UNLOCKED == __ipc_lock_status(priv->idev->base))
			break;

		udelay(10);
		retry--;
	} while (retry);

	if (!retry)
		return -ENODEV;

	return 0;
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
			asm volatile ("wfe");
		} else {
			/*set the source processor bit, we set common mailbox's  source processor bit through dtsi */
			__ipc_set_src(priv->idev->base, priv->src, priv->index);
			if (__ipc_read_src(priv->idev->base, priv->index) & IPCBITMASK(priv->src))
				break;
		}
		retry--;
		/* Hardware unlock */
	} while (retry);

	if (!retry)
		return -ENODEV;

	return 0;
}

static int hisi_mdev_hw_send(struct hisi_mbox_device *mdev, mbox_msg_t *msg, mbox_msg_len_t len, int ack_mode)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int i;
	unsigned int temp;

	/* interrupts unmask */
	__ipc_cpu_imask_all(priv->idev->base, priv->index);

	if (AUTO_ACK == ack_mode)
		temp = IPCBITMASK(priv->des);
	else
		temp = IPCBITMASK(priv->src) | IPCBITMASK(priv->des);

	__ipc_cpu_imask_clr(priv->idev->base, temp, priv->index);

	/* des config */

	__ipc_set_des(priv->idev->base, priv->des, priv->index);

	/* ipc mode config */
	if (AUTO_ACK == ack_mode)
		temp = AUTOMATIC_ACK_CONFIG;
	else
		temp = NO_FUNC_CONFIG;

	__ipc_mode(priv->idev->base, temp, priv->index);

	/* write data */
	for (i = 0; i < ((priv->capability < len) ? priv->capability : len); i++)
		__ipc_write(priv->idev->base, msg[i], priv->index, i);

	/* enable sending */
	__ipc_send(priv->idev->base, IPCBITMASK(priv->src), priv->index);
	return 0;
}

static void hisi_mdev_ensure_channel(struct hisi_mbox_device *mdev)
{

	int timeout = 0;

	if (mdev->ops->is_stm(mdev, IDLE_STATUS)) {
		/*IDLE STATUS, return directly */
		return;
	}
	/*the ack status is reached, just release, the sync and async is mutexed by by mdev->dev_lock */
	else if (mdev->ops->is_stm(mdev, ACK_STATUS)) {
		/*ACK STATUS, release the channel directly */
		goto release;
	}
	/*DEST STATUS and SRC STATUS, the dest is processing, wait here */
	else {						/*if(mdev->ops->is_stm(mdev, DESTINATION_STATUS) || mdev->ops->is_stm(mdev, SOURCE_STATUS)) */

		/*the worst situation is to delay 1000*5us+60*5ms = 305ms */
		while (timeout < MAILBOX_ASYNC_TIMEOUT_CNT) {
			if (timeout < MAILBOX_ASYNC_UDELAY_CNT) {
				udelay(5);
			} else {
				/*the hifi may power off when send ipc msg, so the ack status may wait 20ms */
				usleep_range(3000, 5000);
				/*MDEV_TRACE("mdev %s sleep 5ms, timeout = %d\n", mdev->name, timeout); */
			}
			/*if the ack status is ready, break out */
			if (mdev->ops->is_stm(mdev, ACK_STATUS)) {
				break;
			}
			timeout++;
		}

		if (unlikely(timeout == MAILBOX_ASYNC_TIMEOUT_CNT)) {
			MDEV_TRACE("\n %s ipc timeout...\n", mdev->name);

			if (mdev->ops->status)
				mdev->ops->status(mdev);
		}

		goto release;
	}

release:
	/*release the channel */
	mdev->ops->refresh(mdev);
}

static int hisi_mdev_send_msg(struct hisi_mbox_device *mdev, mbox_msg_t *msg, mbox_msg_len_t len, int ack_mode)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int err = 0;
	/*all the mailbox channel is treated as fast-mailbox */
	if (DESTINATION_MBOX & priv->func) {
		MDEV_TRACE("mdev %s has no tx ability\n", mdev->name);
		err = -EMDEVCLEAN;
		goto out;
	}

	/*
	 * Whenever an ipc starts,
	 * ipc module has to be unlocked at the very beginning.
	 */
	if (hisi_mdev_unlock(mdev)) {
		pr_err("%s: mdev %s can not be unlocked\n", MODULE_NAME, mdev->name);
		err = -EMDEVCLEAN;
		goto out;
	}

	if (hisi_mdev_occupy(mdev)) {
		MDEV_TRACE("mdev %s can not be occupied\n", mdev->name);
		err = -EMDEVCLEAN;
		goto out;
	}

	(void)hisi_mdev_hw_send(mdev, msg, len, ack_mode);

out:
	return err;
}

static void hisi_mdev_release(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;

	__ipc_cpu_imask_all(priv->idev->base, priv->index);
	__ipc_set_src(priv->idev->base, priv->src, priv->index);

	asm volatile ("sev");
	return;
}

static int hisi_mdev_irq_request(struct hisi_mbox_device *mdev, irq_handler_t handler, void *p)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;
	int ret = 0;

	if (priv->idev->cmbox_info->cmbox_gic_1_irq == priv->irq) {
		if (!priv->idev->cmbox_info->gic_1_irq_requested++) {
			ret = request_irq(priv->irq, handler, IRQF_DISABLED, mdev->name, (void *)priv->idev->cmbox_info->cmdev);
			if (ret) {
				MDEV_TRACE("fast source %s request gic_1_irq %d failed\n", mdev->name, priv->irq);
				priv->idev->cmbox_info->gic_1_irq_requested--;
				goto out;
			}

			hisi_irqaffinity_register(priv->irq, IPC_IRQ_AFFINITY_CPU);
		}
	} else if (priv->idev->cmbox_info->cmbox_gic_2_irq == priv->irq) {
		if (!priv->idev->cmbox_info->gic_2_irq_requested++) {
			ret = request_irq(priv->irq, handler, IRQF_DISABLED, mdev->name, (void *)priv->idev->cmbox_info->cmdev);
			if (ret) {
				MDEV_TRACE("fast source %s request gic_2_irq %d failed\n", mdev->name, priv->irq);
				priv->idev->cmbox_info->gic_2_irq_requested--;
				goto out;
			}

			hisi_irqaffinity_register(priv->irq, IPC_IRQ_AFFINITY_CPU);
		}
	} else {
		ret = request_irq(priv->irq, handler, IRQF_DISABLED, mdev->name, p);
		if (ret) {
			MDEV_TRACE("fast desitnation %s request irq %d failed\n", mdev->name, priv->irq);
			goto out;
		}

		hisi_irqaffinity_register(priv->irq, IPC_IRQ_AFFINITY_CPU);
	}

out:
	return ret;
}

static void hisi_mdev_irq_free(struct hisi_mbox_device *mdev, void *p)
{
	struct hisi_mbox_device_priv *priv = mdev->priv;

	if (priv->idev->cmbox_info->cmbox_gic_1_irq == priv->irq) {
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

static void hisi_mdev_irq_enable(struct hisi_mbox_device *mdev)
{
	enable_irq((unsigned int)mdev->cur_irq);
}

static void hisi_mdev_irq_disable(struct hisi_mbox_device *mdev)
{
	disable_irq_nosync((unsigned int)mdev->cur_irq);
}

static struct hisi_mbox_device *hisi_mdev_irq_to_mdev(struct hisi_mbox_device *_mdev, struct list_head *list, int irq)
{
	struct hisi_mbox_device_priv *_priv = NULL;
	struct hisi_mbox_device *mdev = NULL;
	struct hisi_mbox_device_priv *priv = NULL;
	remote_processor_type_t src = UNCERTAIN_REMOTE_PROCESSOR;
	unsigned int regval = 0x0;

	if ((list_empty(list)) || (NULL == _mdev)) {
		MDEV_TRACE("invalid input\n");
		goto out;
	}

	_priv = _mdev->priv;

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
		MDEV_TRACE("odd irq for hisi mailboxes\n");
		goto out;
	}

	regval = __ipc_mbox_istatus(_priv->idev->base, src);
	if (0 == regval) {
		mdev = NULL;
		goto out;
	}
	list_for_each_entry(mdev, list, node) {
		priv = mdev->priv;

		if ((regval & IPCBITMASK(priv->index)) && (priv->func & SOURCE_MBOX))
			goto out;
	}

out:
	/* it is nearly occured */
	return mdev;
}

struct hisi_mbox_dev_ops hisi_mdev_ops = {
	.startup = hisi_mdev_startup,
	.shutdown = hisi_mdev_shutdown,
	.check = hisi_mdev_check,
	.recv = hisi_mdev_receive_msg,
	.send = hisi_mdev_send_msg,
	.ack = hisi_mdev_ack,
	.refresh = hisi_mdev_release,

	.request_irq = hisi_mdev_irq_request,
	.free_irq = hisi_mdev_irq_free,
	.enable_irq = hisi_mdev_irq_enable,
	.disable_irq = hisi_mdev_irq_disable,
	.irq_to_mdev = hisi_mdev_irq_to_mdev,
	.is_stm = hisi_mdev_is_stm,
	.clr_ack = hisi_mdev_clr_ack,
	.ensure_channel = hisi_mdev_ensure_channel,
	.status = hisi_mdev_dump_status,
};

static void hisi_mdev_put(struct hisi_ipc_device *idev)
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

static int hisi_mdev_remove(struct platform_device *pdev)
{
	struct hisi_ipc_device *idev = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);

	if (idev) {
		hisi_mbox_device_unregister(idev->mdev_res);
		hisi_mdev_put(idev);
		kfree(idev);
	}

	return 0;
}

static int hisi_mdev_get(struct hisi_ipc_device *idev, struct hisi_mbox_device **mdevs, struct device_node *node)
{
	struct device_node *son = NULL;
	struct hisi_common_mbox_info *cmbox_info = NULL;
	struct hisi_mbox_device *mdev;
	struct hisi_mbox_device_priv *priv;
	remote_processor_type_t src_bit;
	remote_processor_type_t des_bit;
	mbox_msg_t *buf_pool = NULL;
	mbox_msg_len_t buf_pool_len = 0;
	const char *mdev_name = NULL;
	const char *src_name = NULL;
	const char *des_name = NULL;
	struct hisi_remote_processor *rp;
	mbox_msg_t *rx_buffer = NULL;
	mbox_msg_t *ack_buffer = NULL;
	u8 func = 0;
	u32 output[3] = { 0 };
	int rp_num = 0;
	int irq = 0;
	int i = 0;
	int index;
	int ret = 0;
	int cm_gic_1_irq = -1;
	int cm_gic_2_irq = -1;
	int capability = 0;
	u32 unlock = 0;
	int mdev_num = 0;
	void __iomem *ipc_base = NULL;

	ipc_base = of_iomap(node, 0);
	if (!ipc_base) {
		MDEV_TRACE("iomap error\n");
		ret = -ENOMEM;
		goto out;
	}

	MDEV_DEBUG("ipc_base: 0x%lx\n", (unsigned long)ipc_base);

	ret = of_property_read_u32(node, "capability", &capability);
	if (ret) {
		MDEV_TRACE("prop \"capability\" error %d\n", ret);
		ret = -ENODEV;
		goto to_iounmap;
	}

	MDEV_DEBUG("capability: %d\n", (int)capability);

	ret = of_property_read_u32(node, "unlock_key", &unlock);
	if (ret) {
		MDEV_TRACE("prop \"key\" error %d\n", ret);
		ret = -ENODEV;
		goto to_iounmap;
	}

	MDEV_DEBUG("unlock_key: 0x%x\n", (unsigned int)unlock);

	ret = of_property_read_u32(node, "remote_processor_num", &rp_num);
	if (ret) {
		MDEV_TRACE("prop \"remote_processor_num\" error %d\n", ret);
		ret = -ENODEV;
		goto to_iounmap;
	}

	MDEV_DEBUG("remote processer number: %d\n", (int)rp_num);

	ret = of_property_read_u32(node, "mailboxes", &mdev_num);
	if (ret) {
		pr_err("%s: prop \"mailboxes\" error %d\n", MODULE_NAME, ret);
		ret = -ENODEV;
		goto to_iounmap;
	}

	MDEV_DEBUG("mailboxes: %d\n", (int)mdev_num);

	rp = kmalloc(sizeof(*rp) * rp_num, GFP_KERNEL);
	if (!rp) {
		ret = -ENOMEM;
		goto to_iounmap;
	}

	for (i = 0; i < rp_num; i++) {
		ret = of_property_read_string_index(node, "remote_processor", i, &rp[i].name);
		if (ret)
			break;

		ret = of_property_read_u32_index(node, "remote_processor_type", i, &rp[i].type);
		if (ret)
			break;

		MDEV_DEBUG("rp name[%d]: %s(%d)\n", i, rp[i].name, (int)rp[i].type);
	}

	if (ret) {
		MDEV_TRACE("prop \"remote_processor\" error %d\n", ret);
		ret = -ENODEV;
		goto free_rp;
	}

	cmbox_info = kmalloc(sizeof(*cmbox_info), GFP_KERNEL);
	if (!cmbox_info) {
		ret = -ENOMEM;
		goto free_rp;
	}

	buf_pool_len = capability * MBOX_BUFFER_TYPE_MAX * mdev_num;
	buf_pool = kzalloc(sizeof(mbox_msg_t) * buf_pool_len, GFP_KERNEL);
	if (!buf_pool) {
		ret = -ENOMEM;
		goto free_cmbox;
	}

	MDEV_DEBUG("buffer pool: 0x%lx\n", (unsigned long)buf_pool);

	cm_gic_1_irq = irq_of_parse_and_map(node, 0);
	cm_gic_2_irq = irq_of_parse_and_map(node, 1);

	cmbox_info->gic_1_irq_requested = 0;
	cmbox_info->gic_2_irq_requested = 0;
	cmbox_info->cmbox_gic_1_irq = cm_gic_1_irq;
	cmbox_info->cmbox_gic_2_irq = cm_gic_2_irq;
	cmbox_info->cmdev = NULL;

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

		MDEV_DEBUG("mailbox node: %s\n", mdev_name);

		ret = of_property_read_string(son, "src_remote_processor", &src_name);
		if (ret)
			goto free_priv;

		ret = of_property_read_string(son, "des_remote_processor", &des_name);
		if (ret)
			goto free_priv;

		ret = of_property_read_u32(son, "src_bit", &src_bit);
		if (ret)
			goto free_priv;

		ret = of_property_read_u32(son, "des_bit", &des_bit);
		if (ret)
			goto free_priv;

		MDEV_DEBUG("src processor: %s(%d)\n", src_name, (int)src_bit);
		MDEV_DEBUG("des processor: %s(%d)\n", des_name, (int)des_bit);

		ret = of_property_read_u32(son, "index", &index);
		if (ret)
			goto free_priv;

		MDEV_DEBUG("index: %d\n", (int)index);

		ret = of_property_read_u32_array(son, "func", output, 3);
		if (ret)
			goto free_priv;

		func |= (output[0] ? FAST_MBOX : COMM_MBOX);

		func |= (output[1] ? SOURCE_MBOX : 0);

		func |= (output[2] ? DESTINATION_MBOX : 0);

		if ((FAST_MBOX & func) && (DESTINATION_MBOX & func)) {
			MDEV_DEBUG("func FAST DES MBOX\n");
			irq = irq_of_parse_and_map(son, 0);
			MDEV_DEBUG("irq: %d\n", (int)irq);
		} else if ((FAST_MBOX & func) && (SOURCE_MBOX & func)) {
			MDEV_DEBUG("func FAST SRC MBOX\n");
			irq = (GIC_1 == src_bit) ? cm_gic_1_irq : cm_gic_2_irq;
			MDEV_DEBUG("irq: %d\n", (int)irq);
			/*set the cmdev, the cmdev will be used in acore't interrupts */
			if (NULL == cmbox_info->cmdev)
				cmbox_info->cmdev = mdev;
		} else {
			/* maybe GIC_1 OR GIC_2 */
			MDEV_DEBUG(" xxxxxxxxx we don't use comm-mailbox , we use it as fast-mailbox\n");
			/*we don't use comm-mailbox , we use it as fast-mailbox, please set the comm to fast in the dtsi */
			irq = COMM_MBOX_IRQ;
			cmbox_info->cmdev = mdev;
			MDEV_DEBUG("irq: %d\n", (int)irq);
		}

		rx_buffer = buf_pool + capability * RX_BUFFER_TYPE;
		ack_buffer = buf_pool + capability * ACK_BUFFER_TYPE;
		buf_pool = buf_pool + capability * MBOX_BUFFER_TYPE_MAX;
		MDEV_DEBUG("rx_buffer: 0x%lx\nack_buffer: 0x%lx\n", (unsigned long)rx_buffer, (unsigned long)ack_buffer);

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
		mdev->rx_buffer = rx_buffer;
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

	kfree(idev->buf_pool);
free_cmbox:
	kfree(cmbox_info);
free_rp:
	kfree(rp);
to_iounmap:
	iounmap(ipc_base);
out:
	return ret;
}

static int hisi_mdev_probe(struct platform_device *pdev)
{
	struct hisi_ipc_device *idev = NULL;
	struct hisi_mbox_device **mdev_res = NULL;
	struct device_node *node = pdev->dev.of_node;
	int mdev_num = 0;
	int ret = 0;

	if (!node) {
		MDEV_TRACE("dts[%s] node not found\n", "hisilicon,HiIPCV230");
		ret = -ENODEV;
		goto out;
	}

	idev = kmalloc(sizeof(*idev), GFP_KERNEL);
	if (!idev) {
		MDEV_TRACE("no mem for ipc resouce\n");
		ret = -ENOMEM;
		goto out;
	}

	ret = of_property_read_u32(node, "mailboxes", &mdev_num);
	if (ret) {
		MDEV_TRACE("no mailboxes resources\n");
		ret = -ENODEV;
		goto free_idev;
	}

	mdev_res = kzalloc((sizeof(*mdev_res) * (mdev_num + 1)), GFP_KERNEL);
	if (!mdev_res) {
		ret = -ENOMEM;
		goto free_idev;
	}
	mdev_res[mdev_num] = NULL;

	ret = hisi_mdev_get(idev, mdev_res, node);
	if (ret) {
		MDEV_TRACE("can not get ipc resource\n");
		ret = -ENODEV;
		goto free_mdevs;
	}

	ret = hisi_mbox_device_register(&pdev->dev, mdev_res);
	if (ret) {
		MDEV_TRACE("mdevs register failed\n");
		ret = -ENODEV;
		goto put_res;
	}

	platform_set_drvdata(pdev, idev);

	MDEV_DEBUG("HiIPCV230 mailboxes are ready\n");

	hisi_rproc_init();			/*we call it here to let the pl011_init can use the rproc send function  */

	return 0;

put_res:
	hisi_mdev_put(idev);
free_mdevs:
	kfree(idev->mdev_res);
free_idev:
	kfree(idev);
out:
	return ret;
}

static int hisi_mdev_suspend(struct device *dev)
{
	struct platform_device *pdev = container_of(dev, struct platform_device, dev);
	struct hisi_ipc_device *idev = platform_get_drvdata(pdev);

	pr_info("%s: suspend +\n", __func__);
	if (idev)
		hisi_mbox_device_deactivate(idev->mdev_res);
	pr_info("%s: suspend -\n", __func__);
	return 0;
}

static int hisi_mdev_resume(struct device *dev)
{
	struct platform_device *pdev = container_of(dev, struct platform_device, dev);
	struct hisi_ipc_device *idev = platform_get_drvdata(pdev);

	pr_info("%s: resume +\n", __func__);
	if (idev)
		hisi_mbox_device_activate(idev->mdev_res);
	pr_info("%s: resume -\n", __func__);
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id hisi_mdev_of_match[] = {
	{.compatible = "hisilicon,HiIPCV230",},
	{},
};

MODULE_DEVICE_TABLE(of, hisi_mdev_of_match);
#endif

static const struct dev_pm_ops hisi_mdev_pm_ops = {
	.suspend_late = hisi_mdev_suspend,
	.resume_early = hisi_mdev_resume,
};

static struct platform_driver hisi_mdev_driver = {
	.probe = hisi_mdev_probe,
	.remove = hisi_mdev_remove,
	.driver = {
			   .name = "HiIPCV230-mailbox",
			   .owner = THIS_MODULE,
			   .of_match_table = of_match_ptr(hisi_mdev_of_match),
			   .pm = &hisi_mdev_pm_ops,
		},
};

static int __init hisi_mdev_init(void)
{
	pr_debug("%s: init\n", MODULE_NAME);

	platform_driver_register(&hisi_mdev_driver);
	return 0;
}

core_initcall(hisi_mdev_init);

static void __exit hisi_mdev_exit(void)
{
	platform_driver_unregister(&hisi_mdev_driver);
	return;
}

module_exit(hisi_mdev_exit);

MODULE_DESCRIPTION("HiIPCV230 ipc, mailbox device driver");
MODULE_LICENSE("GPL V2");
