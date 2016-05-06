#include <linux/module.h>
#include <linux/init.h>
#include <linux/hisi/hisi_mailbox.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/suspend.h>
#include <linux/hisi/hisi_rproc.h>
#include "hisi-clk-mailbox.h"

#define MAX_SEND_IPC_TRY	3
#define MAX_SEND_MSG_TRY	3

struct mailbox_clk {
	struct hisi_mbox *mbox;
};

static int mailbox_disable;

static int mailbox_pm_callback(struct notifier_block *nb,
			unsigned long action, void *ptr)
{

	switch (action) {

	case PM_SUSPEND_PREPARE:
		mailbox_disable = 1;
		break;

	case PM_POST_SUSPEND:
		mailbox_disable = 0;
		break;

	default:
		return NOTIFY_DONE;
	}

	return NOTIFY_OK;
}

static struct notifier_block mailbox_pm_notif_block = {
	.notifier_call = mailbox_pm_callback,
};



static int hisi_clkmbox_send_ipc(mbox_msg_t *msg)
{
	int loop = MAX_SEND_IPC_TRY;
	int ret, rproc_id;

	rproc_id = HISI_RPROC_LPM3_MBX13;
	/* try again if failing to send */
	do {
		ret = RPROC_ASYNC_SEND(rproc_id, (mbox_msg_t *)msg, LPM3_CMD_LEN);
		loop--;
	} while (ret == -ENOMEM && loop > 0);
	if (ret) {
		pr_err("[%s] fail to send mbox msg, ret = %d!\n",
				__func__, ret);
		return ret;
	}

	return 0;
}

static int hisi_clkmbox_send_ipc_sync(mbox_msg_t *msg)
{
	int loop = MAX_SEND_IPC_TRY;
	int ret, rproc_id;

	rproc_id = HISI_RPROC_LPM3_MBX13;
	/* try again if failing to send */
	do {
		ret = RPROC_SYNC_SEND(rproc_id, (mbox_msg_t *)msg, LPM3_CMD_LEN, NULL, 0);
		loop--;
	} while (ret == -ENOMEM && loop > 0);
	if (ret) {
		pr_err("[%s] fail to send mbox msg, ret = %d!\n",
				__func__, ret);
		return ret;
	}

	return 0;
}

/*
 * Please pay attention to the following points:
 * (1) This function can be called from atomic and non-atomic context.
 * (2) Please check the return variable, as the mailbox may not ready.
 *
 */
int hisi_clkmbox_send_msg(mbox_msg_t *msg)
{
	int ret = 0;
	int loop = MAX_SEND_MSG_TRY;

	/* try again when the mail box is full */
	do {
		ret = hisi_clkmbox_send_ipc(msg);
		loop--;
	} while (ret != 0 && loop > 0);

	return ret;
}

int hisi_clkmbox_send_msg_sync(mbox_msg_t *msg)
{
	int ret = 0;
	int loop = MAX_SEND_MSG_TRY;

	/* try again when the mail box is full */
	do {
		ret = hisi_clkmbox_send_ipc_sync(msg);
		loop--;
	} while (ret != 0 && loop > 0);

	return ret;
}

static int __init hisi_clkmbox_init(void)
{
	int ret = 0;

	/*2015/5/16 del the pm notify for cpufreq sending freq ipc after ipc sr */
	mailbox_disable = 0;
	register_pm_notifier(&mailbox_pm_notif_block);

	return ret;
}

static void __exit hisi_clkmbox_exit(void)
{
	int rproc_id = 0;

	rproc_id = HISI_RPROC_LPM3_MBX13;
	/*the HISI_RPROC_LPM3 is a shared channel by many IP, but the exit function should never be used  */
	RPROC_PUT(rproc_id);
	unregister_pm_notifier(&mailbox_pm_notif_block);
}

fs_initcall(hisi_clkmbox_init);
module_exit(hisi_clkmbox_exit);
