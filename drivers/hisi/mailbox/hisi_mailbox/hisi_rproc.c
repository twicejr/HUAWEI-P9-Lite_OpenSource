/*
 * hisi rproc communication interface
 *
 * Copyright (c) 2013- Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/notifier.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/hisi/hisi_mailbox.h>
#include <linux/hisi/hisi_rproc.h>

#define MODULE_NAME "hisi_rproc"

#define READY()				do { is_ready = 1; } while (0)
#define NOT_READY()			do { is_ready = 0; } while (0)
#define IS_READY()			({ is_ready; })
#define RPROC_PR_ERR(fmt, args ...)	\
	({				\
		pr_err("%s(%d):" fmt "\n", \
			MODULE_NAME, __LINE__, ##args); \
	})
/*#define RPROC_PR_INFO(fmt, args ...)	\
	({				\
		pr_info("%s(%d):" fmt "\n", \
			MODULE_NAME, __LINE__, ##args); \
	})*/

typedef enum {
	ASYNC_CALL = 0,
	SYNC_CALL
} call_type_t;

struct hisi_rproc_info {
	rproc_id_t rproc_id;
	const char *mbox_rp;
	struct atomic_notifier_head notifier;
	struct notifier_block nb;
	struct hisi_mbox *mbox;
};

static int is_ready;
extern struct hisi_mbox_task *g_TxTaskBuffer;
static struct hisi_rproc_info rproc_table[] = {
	{
	 .rproc_id = HISI_RPROC_LPM3_MBX0,
	 .mbox_rp = HISI_MAILBOX_RP_LPM3_MBX0,
	 },
	{
	 .rproc_id = HISI_RPROC_RDR_MBX1,
	 .mbox_rp = HISI_MAILBOX_RP_DEFAULT_MBX1,
	 },
	{
	 .rproc_id = HISI_RPROC_HIFI_MBX2,
	 .mbox_rp = HISI_MAILBOX_RP_HIFI_MBX2,
	 },
	{
	 .rproc_id = HISI_RPROC_DEFAULT_MBX3,
	 .mbox_rp = HISI_MAILBOX_RP_DEFAULT_MBX3,
	 },
	{
	 .rproc_id = HISI_RPROC_IOM3_MBX4,
	 .mbox_rp = HISI_MAILBOX_RP_IOM3_MBX4,
	 },
	{
	 .rproc_id = HISI_RPROC_IVP_MBX5,
	 .mbox_rp = HISI_MAILBOX_RP_IVP_MBX5,
	 },
	{
	 .rproc_id = HISI_RPROC_IVP_MBX6,
	 .mbox_rp = HISI_MAILBOX_RP_IVP_MBX6,
	 },
#if 0							/*use maybe in the future */
	{
	 .rproc_id = HISI_RPROC_DEFAULT_MBX7,
	 .mbox_rp = HISI_MAILBOX_RP_DEFAULT_MBX7,
	 },
	{
	 .rproc_id = HISI_RPROC_DEFAULT_MBX8,
	 .mbox_rp = HISI_MAILBOX_RP_DEFAULT_MBX8,
	 },
	{
	 .rproc_id = HISI_RPROC_DEFAULT_MBX9,
	 .mbox_rp = HISI_MAILBOX_RP_DEFAULT_MBX9,
	 },
#endif
	{
	 .rproc_id = HISI_RPROC_IOM3_MBX10,
	 .mbox_rp = HISI_MAILBOX_RP_IOM3_MBX10,
	 },
	{
	 .rproc_id = HISI_RPROC_IOM3_MBX11,
	 .mbox_rp = HISI_MAILBOX_RP_IOM3_MBX11,
	 },
	{
	 .rproc_id = HISI_RPROC_IOM3_MBX12,
	 .mbox_rp = HISI_MAILBOX_RP_IOM3_MBX12,
	 },
	{
	 .rproc_id = HISI_RPROC_LPM3_MBX13,
	 .mbox_rp = HISI_MAILBOX_RP_LPM3_MBX13,
	 },
	{
	 .rproc_id = HISI_RPROC_LPM3_MBX14,
	 .mbox_rp = HISI_MAILBOX_RP_LPM3_MBX14,
	 },
	{
	 .rproc_id = HISI_RPROC_LPM3_MBX15,
	 .mbox_rp = HISI_MAILBOX_RP_LPM3_MBX15,
	 },
	{
	 .rproc_id = HISI_RPROC_LPM3_MBX16,
	 .mbox_rp = HISI_MAILBOX_RP_LPM3_MBX16,
	 },
	{
	 .rproc_id = HISI_RPROC_LPM3_MBX17,
	 .mbox_rp = HISI_MAILBOX_RP_LPM3_MBX17,
	 },
	{
	 .rproc_id = HISI_RPROC_HIFI_MBX18,
	 .mbox_rp = HISI_MAILBOX_RP_HIFI_MBX18,
	 },
#if 0							/*use maybe in the future */
	{
	 .rproc_id = HISI_RPROC_MODEM_A9_MBX19,
	 .mbox_rp = HISI_MAILBOX_RP_MODEM_A9_MBX19,
	 },
	{
	 .rproc_id = HISI_RPROC_MODEM_A9_MBX20,
	 .mbox_rp = HISI_MAILBOX_RP_MODEM_A9_MBX20,
	 },
	{
	 .rproc_id = HISI_RPROC_MODEM_A9_MBX21,
	 .mbox_rp = HISI_MAILBOX_RP_MODEM_A9_MBX21,
	 },
	{
	 .rproc_id = HISI_RPROC_MODEM_BBE16_MBX22,
	 .mbox_rp = HISI_MAILBOX_RP_MODEM_BBE16_MBX22,
	 },
	{
	 .rproc_id = HISI_RPROC_MODEM_BBE16_MBX23,
	 .mbox_rp = HISI_MAILBOX_RP_ISP_MBX23,
	 },
	{
	 .rproc_id = HISI_RPROC_MODEM_BBE16_MBX24,
	 .mbox_rp = HISI_MAILBOX_RP_ISP_MBX24,
	 },
#endif
	{
	 .rproc_id = HISI_RPROC_IVP_MBX25,
	 .mbox_rp = HISI_MAILBOX_RP_IVP_MBX25,
	 },
	{
	 .rproc_id = HISI_RPROC_IVP_MBX26,
	 .mbox_rp = HISI_MAILBOX_RP_IVP_MBX26,
	 },
	{
	 .rproc_id = HISI_RPROC_LPM3_MBX27,
	 .mbox_rp = HISI_MAILBOX_RP_LPM3_MBX27,
	 },
	{
	 .rproc_id = HISI_RPROC_LPM3_MBX28,
	 .mbox_rp = HISI_MAILBOX_RP_LPM3_MBX28,
	 },
	{
	 .rproc_id = HISI_RPROC_HIFI_MBX29,
	 .mbox_rp = HISI_MAILBOX_RP_HIFI_MBX29,
	 },
#if 0							/*use maybe in the future */
	{
	 .rproc_id = HISI_RPROC_LPM3_MBX30,
	 .mbox_rp = HISI_MAILBOX_RP_LPM3_MBX30,
	 },
#endif
	{
	 .rproc_id = HISI_RPROC_ISP_MBX0,
	 .mbox_rp = HISI_MAILBOX_RP_ISP_MBX0,
	 },
	{
	 .rproc_id = HISI_RPROC_ISP_MBX1,
	 .mbox_rp = HISI_MAILBOX_RP_ISP_MBX1,
	 },
	{
	 .rproc_id = HISI_RPROC_ISP_MBX2,
	 .mbox_rp = HISI_MAILBOX_RP_ISP_MBX2,
	 },
	{
	 .rproc_id = HISI_RPROC_ISP_MBX3,
	 .mbox_rp = HISI_MAILBOX_RP_ISP_MBX3,
	 }
};

static inline struct hisi_rproc_info *find_rproc(rproc_id_t rproc_id)
{
	struct hisi_rproc_info *rproc = NULL;
	int i;

	for (i = 0; i < sizeof(rproc_table) / sizeof(struct hisi_rproc_info); i++) {
		if (rproc_id == rproc_table[i].rproc_id) {
			rproc = &rproc_table[i];
			break;
		}
	}

	return rproc;
}

int hisi_rproc_xfer_async(rproc_id_t rproc_id, rproc_msg_t *msg, rproc_msg_len_t len)
{
	struct hisi_rproc_info *rproc;
	struct hisi_mbox_task *tx_task = NULL;
	struct hisi_mbox *mbox = NULL;
	const char *rproc_name = NULL;
	mbox_ack_type_t ack_type = AUTO_ACK;

	int ret = 0;

	BUG_ON(!IS_READY());

	if (MBOX_CHAN_DATA_SIZE < len) {
		ret = -EINVAL;
		goto out;
	}

	rproc = find_rproc(rproc_id);
	if (!rproc) {
		RPROC_PR_ERR("invalid rproc xfer\n");
		ret = -EINVAL;
		goto out;
	}

	mbox = rproc->mbox;
	rproc_name = rproc->mbox_rp;

	tx_task = hisi_mbox_task_alloc(mbox, rproc_name, msg, len, ack_type);
	if (!tx_task) {
		RPROC_PR_ERR("no mem\n");
		ret = -ENOMEM;
		goto out;
	}

	ret = hisi_mbox_msg_send_async(mbox, tx_task);
	if (ret) {
		RPROC_PR_ERR("mdev %s fail to async send, error num:%d\n", mbox->tx->name, ret);
		hisi_mbox_task_free(&tx_task);
	}

out:
	return ret;
}

EXPORT_SYMBOL(hisi_rproc_xfer_async);

int hisi_rproc_xfer_sync(rproc_id_t rproc_id, rproc_msg_t *msg, rproc_msg_len_t len, rproc_msg_t *ack_buffer, rproc_msg_len_t ack_buffer_len)
{
	struct hisi_rproc_info *rproc;
	struct hisi_mbox *mbox = NULL;
	const char *rproc_name = NULL;
	mbox_ack_type_t ack_type = MANUAL_ACK;
	int ret = 0;

	BUG_ON(!IS_READY());

	if (MBOX_CHAN_DATA_SIZE < len || MBOX_CHAN_DATA_SIZE < ack_buffer_len) {
		ret = -EINVAL;
		goto out;
	}

	rproc = find_rproc(rproc_id);
	if (!rproc) {
		RPROC_PR_ERR("invalid rproc xfer\n");
		ret = -EINVAL;
		goto out;
	}

	mbox = rproc->mbox;
	rproc_name = rproc->mbox_rp;

	ret = hisi_mbox_msg_send_sync(mbox, rproc_name, msg, len, ack_type, ack_buffer, ack_buffer_len);
	if (ret) {
		RPROC_PR_ERR("fail to sync send\n");
	}

out:
	return ret;
}

EXPORT_SYMBOL(hisi_rproc_xfer_sync);

static int hisi_rproc_rx_notifier(struct notifier_block *nb, unsigned long len, void *msg)
{
	struct hisi_rproc_info *rproc = container_of(nb, struct hisi_rproc_info, nb);

	atomic_notifier_call_chain(&rproc->notifier, len, msg);
	return 0;
}

int hisi_rproc_rx_register(rproc_id_t rproc_id, struct notifier_block *nb)
{
	struct hisi_rproc_info *rproc;
	int ret = 0;

	BUG_ON(!IS_READY());

	rproc = find_rproc(rproc_id);
	if (!rproc) {
		RPROC_PR_ERR("invalid rproc xfer\n");
		ret = -EINVAL;
		goto out;
	}

	atomic_notifier_chain_register(&rproc->notifier, nb);
out:
	return ret;
}

EXPORT_SYMBOL(hisi_rproc_rx_register);

int hisi_rproc_rx_unregister(rproc_id_t rproc_id, struct notifier_block *nb)
{
	struct hisi_rproc_info *rproc;
	int ret = 0;

	BUG_ON(!IS_READY());

	rproc = find_rproc(rproc_id);
	if (!rproc) {
		RPROC_PR_ERR("invalid rproc xfer\n");
		ret = -EINVAL;
		goto out;
	}

	atomic_notifier_chain_unregister(&rproc->notifier, nb);
out:
	return ret;
}

/*
 * Function name:hisi_rproc_put.
 * Discription:release the ipc channel's structure, it's usually called by  module_exit function, but the module_exit function should never be used  .
 * Parameters:
 *      @ rproc_id_t
 * return value:
 *      @ -ENODEV-->failed, other-->succeed.
 */
int hisi_rproc_put(rproc_id_t rproc_id)
{
	struct hisi_rproc_info *rproc;
	int i;

	for (i = 0; i < sizeof(rproc_table) / sizeof(struct hisi_rproc_info); i++) {
		rproc = &rproc_table[i];
		if (rproc->mbox && rproc_id == rproc->rproc_id) {
			hisi_mbox_put(&rproc->mbox);
			break;
		}
	}
	if (unlikely(sizeof(rproc_table) / sizeof(struct hisi_rproc_info) == i)) {
		RPROC_PR_ERR("\nrelease the ipc channel %d 's structure failed\n", rproc->rproc_id);
		return -ENODEV;
	}
	return 0;
}

/*
 * Function name:hisi_rproc_flush_tx.
 * Discription:flush the tx_work queue.
 * Parameters:
 *      @ rproc_id_t
 * return value:
 *      @ -ENODEV-->failed, other-->succeed.
 */
int hisi_rproc_flush_tx(rproc_id_t rproc_id)
{
	struct hisi_rproc_info *rproc;
	int i;

	for (i = 0; i < sizeof(rproc_table) / sizeof(struct hisi_rproc_info); i++) {
		rproc = &rproc_table[i];
		if (rproc->mbox->tx && rproc_id == rproc->rproc_id) {
			hisi_mbox_empty_task(rproc->mbox->tx);
			break;
		}
	}

	if (unlikely(sizeof(rproc_table) / sizeof(struct hisi_rproc_info) == i)) {
		return -ENODEV;
	}
	return 0;
}

EXPORT_SYMBOL(hisi_rproc_rx_unregister);

int hisi_rproc_init(void)
{
	struct hisi_rproc_info *rproc;
	struct hisi_mbox_task *ptask = NULL;
	int i;

	for (i = 0; i < sizeof(rproc_table) / sizeof(struct hisi_rproc_info); i++) {
		rproc = &rproc_table[i];

		if (NULL == rproc->mbox) {
			ATOMIC_INIT_NOTIFIER_HEAD(&rproc->notifier);

			rproc->nb.next = NULL;
			rproc->nb.notifier_call = hisi_rproc_rx_notifier;

			rproc->mbox = hisi_mbox_get(rproc->mbox_rp, &rproc->nb);
			if (!rproc->mbox) {
				/*RPROC_PR_ERR("\nrproc %d will get later \n",rproc->rproc_id);*/
				break;
			}
		}
		/*the last rproc info has been initialize, set the rproc ready */
		if (((sizeof(rproc_table) / sizeof(struct hisi_rproc_info) - 1) == i) && (NULL != rproc->mbox)) {
			READY();
		}
	}

	if (NULL == g_TxTaskBuffer) {
		g_TxTaskBuffer = (struct hisi_mbox_task *)kmalloc(TX_TASK_DDR_NODE_NUM * sizeof(struct hisi_mbox_task), GFP_KERNEL);
		if (NULL == g_TxTaskBuffer) {
			RPROC_PR_ERR("\n failed to get g_TxTaskBuffer\n");
			return -ENOMEM;
		}

		ptask = g_TxTaskBuffer;
		for (i = 0; i < TX_TASK_DDR_NODE_NUM; i++) {
			/*init the tx buffer 's node , set the flag to available */
			ptask->tx_buffer[0] = TX_TASK_DDR_NODE_AVA;
			ptask++;
		}
	}

	return 0;
}

EXPORT_SYMBOL(hisi_rproc_init);
static void __exit hisi_rproc_exit(void)
{
	struct hisi_rproc_info *rproc;
	int i;

	NOT_READY();

	for (i = 0; i < sizeof(rproc_table) / sizeof(struct hisi_rproc_info); i++) {
		rproc = &rproc_table[i];
		if (rproc->mbox)
			hisi_mbox_put(&rproc->mbox);
	}

	return;
}

module_exit(hisi_rproc_exit);

MODULE_DESCRIPTION("HISI rproc communication interface");
MODULE_LICENSE("GPL V2");
