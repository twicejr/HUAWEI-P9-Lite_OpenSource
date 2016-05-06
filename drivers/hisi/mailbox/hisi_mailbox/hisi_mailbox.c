/*
 * mailbox core driver
 *
 * Copyright (c) 2013- Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/notifier.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/wakelock.h>
#include <linux/semaphore.h>
#include <linux/sched/rt.h>
#include <linux/kthread.h>
#include <linux/hisi/hisi_mailbox.h>

#define MBOX_PR_ERR(fmt, args ...)	\
	({				\
		pr_err("%s(%d):" fmt "\n", \
			MODULE_NAME, __LINE__, ##args); \
	})
#define MBOX_PR_INFO(fmt, args ...)	\
	({				\
		pr_info("%s(%d):" fmt "\n", \
			MODULE_NAME, __LINE__, ##args); \
	})
#define MBOX_PR_DEBUG(fmt, args ...)	\
	({				\
		; \
	})

#define MODULE_NAME "hisi_mailbox"

/*#define  HISI_MAILBOX_DBG */   /*open this only in every early phase*/

/* debugfs tts for ipc performance */
#ifdef CONFIG_HISI_MAILBOX_PERFORMANCE_DEBUG
#define PERFORMANCE_DEBUG(tx_task, timing)		\
do {							\
	if (tx_task->perf_debug)			\
		getnstimeofday(&tx_task->tts[timing]);	\
} while (0)

#define TASK_DEBUG_ON(tx_task)		(tx_task->perf_debug =	\
						PERFORMANCE_DEBUG_ON)
#define TASK_DEBUG_OFF(tx_task)		(tx_task->perf_debug =	\
						PERFORMANCE_DEBUG_OFF)
#define START_TTS(tx_task)		PERFORMANCE_DEBUG(tx_task, IPC_START)
#define SEND_TTS(tx_task)		PERFORMANCE_DEBUG(tx_task, IPC_SEND)
#define RECEIVE_TTS(tx_task)		PERFORMANCE_DEBUG(tx_task, IPC_RECEIVE)
#define BH_TTS(tx_task)			PERFORMANCE_DEBUG(tx_task, IPC_BH)
#define COMPLETE_TTS(tx_task)		PERFORMANCE_DEBUG(tx_task, IPC_COMPLETE)
#define PRINT_TTS(tx_task)		\
do {					\
	if (tx_task->perf_debug)	\
		dump_tts(tx_task);	\
} while (0)
#else
#define TASK_DEBUG_ON(tx_task)		do {} while (0)
#define TASK_DEBUG_OFF(tx_task)		do {} while (0)
#define START_TTS(tx_task)		do {} while (0)
#define SEND_TTS(tx_task)		do {} while (0)
#define RECEIVE_TTS(tx_task)		do {} while (0)
#define BH_TTS(tx_task)			do {} while (0)
#define COMPLETE_TTS(tx_task)		do {} while (0)
#define PRINT_TTS(tx_task)		do {} while (0)
#endif

#define TX_FIFO_CELL_SIZE   (sizeof(struct hisi_mbox_task *))
/* max 256 simultaneous tasks for every mailbox device */
#define MAILBOX_MAX_TX_BUFFER (256 * TX_FIFO_CELL_SIZE)
/*max 8 simultaneous tasks for mailbox-13 which is only used by lpmcu freq set */
#define MAILBOX13_MAX_TX_BUFFER (8 * TX_FIFO_CELL_SIZE)

/*
 * timeout for waiting auto ack, 300ms.
 * timeout for waiting manual ack, 300ms.
 */

enum { NOCOMPLETION = 0, COMPLETING, COMPLETED };
enum { TX_TASK = 0, RX_TASK };

spinlock_t g_task_buffer_lock;
struct hisi_mbox_task *g_TxTaskBuffer = NULL;
/*use the g_ContinuousFailCnt to control the Continuous ipc timeout times which may overflow the kmesg log */
int g_ContinuousFailCnt = 0;
/* mailbox device resource pool */
static LIST_HEAD(mdevices);

#ifdef CONFIG_HISI_MAILBOX_PERFORMANCE_DEBUG
static void dump_tts(struct hisi_mbox_task *tx_task)
{
	struct timespec *tts = tx_task->tts;

	MBOX_PR_INFO("\n=======  current IPC time stamp  =======\n  [START]    : %lu.%lu\n  [SEND]     : %lu.%lu\n  [RECEIVE]  : %lu.%lu\n  [BHalf]    : %lu.%lu\n  [COMPLETE] : %lu.%lu\n  [SEND  -> COMPLETE] : %lus %luns\n  [START -> COMPLETE] : %lus %luns\n=================  end  ================\n\n",
		tts[IPC_START].tv_sec, tts[IPC_START].tv_nsec,
		tts[IPC_SEND].tv_sec, tts[IPC_SEND].tv_nsec,
		tts[IPC_RECEIVE].tv_sec, tts[IPC_RECEIVE].tv_nsec,
		tts[IPC_BH].tv_sec, tts[IPC_BH].tv_nsec,
		tts[IPC_COMPLETE].tv_sec, tts[IPC_COMPLETE].tv_nsec,
		tts[IPC_COMPLETE].tv_sec - tts[IPC_SEND].tv_sec,
		tts[IPC_COMPLETE].tv_nsec - tts[IPC_SEND].tv_nsec,
		tts[IPC_COMPLETE].tv_sec - tts[IPC_START].tv_sec,
		tts[IPC_COMPLETE].tv_nsec - tts[IPC_START].tv_nsec);

	return;
}
#endif

struct hisi_mbox_task *hisi_mbox_node_alloc(void)
{
	int index = 0;
	struct hisi_mbox_task *ptask = g_TxTaskBuffer;
	spin_lock(&g_task_buffer_lock);
	for (index = 0; index < TX_TASK_DDR_NODE_NUM; index++) {
		if (TX_TASK_DDR_NODE_AVA == ptask->tx_buffer[0])
			break;
		ptask++;
	}

	if (likely(TX_TASK_DDR_NODE_NUM != index))
		ptask->tx_buffer[0] = TX_TASK_DDR_NODE_OPY;	/*set the node occupied */
	else
		ptask = NULL;

	spin_unlock(&g_task_buffer_lock);

	return ptask;
}

void hisi_mbox_task_free(struct hisi_mbox_task **tx_task)
{
	if ((NULL == tx_task) || (NULL == *tx_task)) {
		MBOX_PR_ERR("null pointer\n");
		return;
	}
	spin_lock(&g_task_buffer_lock);
	/*use the tx_buffer[0] as the available flag */
	(*tx_task)->tx_buffer[0] = TX_TASK_DDR_NODE_AVA;
	spin_unlock(&g_task_buffer_lock);

	return;
}

EXPORT_SYMBOL(hisi_mbox_task_free);

struct hisi_mbox_task *hisi_mbox_task_alloc(struct hisi_mbox *mbox, const char *rp_name,
						mbox_msg_t *tx_buffer, mbox_msg_len_t tx_buffer_len, int need_auto_ack)
{
	struct hisi_mbox_task *tx_task = NULL;

	if (!mbox || !mbox->tx || !tx_buffer) {
		if (!mbox)
			MBOX_PR_ERR("null pointer mbox!\n");
		else
			MBOX_PR_ERR("%s  no tx ability or no tx_buffer\n", mbox->name);
		goto out;
	}
#ifdef HISI_MAILBOX_DBG
	/* remote processor must be certain and accesilbe for mailbox */
	if (mbox->tx->ops->check(mbox->tx, TX_MAIL, rp_name) != RPACCESSIBLE) {
		MBOX_PR_ERR("invalid remote processor \"%s\" for %s\n", rp_name, mbox->tx->name);
		goto out;
	}
#endif
	tx_task = hisi_mbox_node_alloc();
	if (!tx_task) {
		MBOX_PR_ERR("tx task no mem\n");
		goto out;
	}
	memcpy((void *)tx_task->tx_buffer, (void *)tx_buffer, tx_buffer_len * (sizeof(mbox_msg_t)));
	tx_task->tx_buffer_len = tx_buffer_len;
	tx_task->need_auto_ack = need_auto_ack;

	if (MBOX_IS_DEBUG_ON(mbox))
		TASK_DEBUG_ON(tx_task);
	else
		TASK_DEBUG_OFF(tx_task);
out:
	return tx_task;
}

EXPORT_SYMBOL(hisi_mbox_task_alloc);

static inline int set_status(struct hisi_mbox_device *mdev, int status)
{
	int ret = 0;

	spin_lock(&mdev->status_lock);
	if ((MDEV_DEACTIVATED & mdev->status)) {
		spin_unlock(&mdev->status_lock);
		MBOX_PR_INFO("an unexpected ipc caused by %s\n", mdev->name);
		/* WARN_ON(1); */
		ret = -ENODEV;
		goto out;
	} else if ((MDEV_DEACTIVATED & status)) {
		mdev->status |= status;

		while ((MDEV_SYNC_SENDING & mdev->status) || (MDEV_ASYNC_ENQUEUE & mdev->status)) {
			spin_unlock(&mdev->status_lock);
			msleep(5);
			spin_lock(&mdev->status_lock);
		}
	} else {
		mdev->status |= status;
	}

	spin_unlock(&mdev->status_lock);
out:
	return ret;
}

static inline void clr_status(struct hisi_mbox_device *mdev, int status)
{
	spin_lock(&mdev->status_lock);
	mdev->status &= ~status;
	spin_unlock(&mdev->status_lock);
	return;
}

static int hisi_mbox_task_send_async(struct hisi_mbox_device *mdev, struct hisi_mbox_task *tx_task)
{
	int ret = 0;

	mdev->ops->ensure_channel(mdev);

	mdev->tx_task = tx_task;
	ret = mdev->ops->send(mdev, tx_task->tx_buffer, tx_task->tx_buffer_len, tx_task->need_auto_ack);
	if (ret) {
		MBOX_PR_ERR("mdev %s can not be sent\n", mdev->name);
	}
	mdev->tx_task = NULL;
	return ret;
}

static int hisi_mbox_task_send_sync(struct hisi_mbox_device *mdev, struct hisi_mbox_task *tx_task)
{
	unsigned long tx_timeout = 0;
	long timeout;
	int ret = 0;
	mbox_msg_t *rx_buffer = NULL;
	mbox_msg_len_t rx_len = 0;
	int wait = 0;
	int need_irq_enable = 0;
	int receipted = 0;
	unsigned long flags;

	SEND_TTS(tx_task);

	mdev->ops->ensure_channel(mdev);

	INIT_COMPLETION(mdev->complete);
	mdev->completed = NOCOMPLETION;
	mdev->tx_task = tx_task;

	ret = mdev->ops->send(mdev, tx_task->tx_buffer, tx_task->tx_buffer_len, tx_task->need_auto_ack);
	if (ret) {
		mdev->tx_task = NULL;
		MBOX_PR_ERR("mdev %s can not be sent\n", mdev->name);
		goto out;
	}							/*else {
								   mdev->ops->track(mdev, SEND_MSG);
								   } */
	if (AUTO_ACK == tx_task->need_auto_ack) {
		tx_timeout = MAILBOX_AUTOACK_TIMEOUT;
	} else if (MANUAL_ACK == tx_task->need_auto_ack) {
		tx_timeout = MAILBOX_MANUACK_TIMEOUT;
	} else {
		MBOX_PR_ERR("%s invalid ack mode.\n", mdev->name);
		goto refresh;
	}

	timeout = wait_for_completion_timeout(&mdev->complete, tx_timeout);
	if (unlikely(0 == timeout)) {
		g_ContinuousFailCnt++;
		if (CONTINUOUS_FAIL_JUDGE) {
			MBOX_PR_ERR("\n %s ipc timeout...\n" "<INFO> MSG[0] : 0x%08x\n" "<INFO> MSG[1] : 0x%08x\n" "<INFO> fifo   : %d\n",
				mdev->name, tx_task->tx_buffer[0], tx_task->tx_buffer[1], (int)(kfifo_len(&mdev->fifo) / TX_FIFO_CELL_SIZE));

			if (mdev->ops->status)
				mdev->ops->status(mdev);
		}
		/* Synchronization for isr. */
		spin_lock_irqsave(&mdev->complete_lock, flags);

		switch (mdev->completed) {
		case NOCOMPLETION:
			if (CONTINUOUS_FAIL_JUDGE)
				MBOX_PR_ERR("NOCOMPLETION.\n");
			mdev->completed = COMPLETED;
			break;

		case COMPLETING:
			if (CONTINUOUS_FAIL_JUDGE)
				MBOX_PR_ERR("COMPLETING.\n");
			/*
			 * Wait for ACK reception in behind half in 50ms.
			 * Both ACK reception and irq restore will be handled
			 * here instead of in behind half, in the case of
			 * tasklet jam in irq-affinity core.
			 */
			wait = 10;
			do {
				spin_unlock_irqrestore(&mdev->complete_lock, flags);
				msleep(5);
				spin_lock_irqsave(&mdev->complete_lock, flags);
			} while (mdev->completed != COMPLETED && wait--);

			/* Tasklet jam */
			if (mdev->completed != COMPLETED) {
				mdev->completed = COMPLETED;
				need_irq_enable = 1;
				break;
			}

		case COMPLETED:
			if (CONTINUOUS_FAIL_JUDGE)
				MBOX_PR_ERR("COMPLETED.\n");
			receipted = 1;

		default:
			goto unlock;
		}

		/* Handle ack & irq. */
		if (mdev->ops->is_stm(mdev, ACK_STATUS) || need_irq_enable) {
			rx_len = mdev->ops->recv(mdev, &rx_buffer);
			tx_task->ack_buffer = rx_buffer;
			tx_task->ack_buffer_len = rx_len;
			receipted = 1;

			if (need_irq_enable)
				mdev->ops->enable_irq(mdev);
		} else {
			/* ACK lost */
			ret = -ETIMEOUT;
		}

unlock:
		spin_unlock_irqrestore(&mdev->complete_lock, flags);

		if (receipted && need_irq_enable) {
			if (CONTINUOUS_FAIL_JUDGE)
				MBOX_PR_ERR("reason: TASKLET jam.\n");
		} else if (receipted && !need_irq_enable) {
			if (CONTINUOUS_FAIL_JUDGE)
				MBOX_PR_ERR("reason: ISR jam.\n");
		} else if (!receipted) {
			if (CONTINUOUS_FAIL_JUDGE)
				MBOX_PR_ERR("reason: ACK lost.\n");
		}
	} else {
		/*once success, clear the g_ContinuousFailCnt */
		g_ContinuousFailCnt = 0;
	}

refresh:
	mdev->ops->refresh(mdev);
	/*mdev->ops->track(mdev, FREE_CHAN); */
out:
	/* completion */
	MBOX_PR_DEBUG("mdev %s completion\n", mdev->name);
	mdev->tx_task = NULL;
	COMPLETE_TTS(tx_task);

	return ret;
}

int hisi_mbox_msg_send_sync(struct hisi_mbox *mbox, const char *rp_name,
					mbox_msg_t *tx_buffer, mbox_msg_len_t tx_buffer_len,
					int need_auto_ack, mbox_msg_t *ack_buffer, mbox_msg_len_t ack_buffer_len)
{
	struct hisi_mbox_device *mdev;
	struct hisi_mbox_task tx_task;
	struct hisi_mbox_task *p_tx_task = NULL;
	int ret = 0;

	if (!mbox || !mbox->tx || !tx_buffer) {
		if (!mbox)
			MBOX_PR_ERR("null pointer mbox!\n");
		else
			MBOX_PR_ERR("%s  no tx ability or no tx_buffer\n", mbox->name);
		ret = -EINVAL;
		goto out;
	}
#ifdef HISI_MAILBOX_DBG
	/* remote processor must be certain and accesilbe for mailbox */
	if (mbox->tx->ops->check(mbox->tx, TX_MAIL, rp_name) != RPACCESSIBLE) {
		MBOX_PR_ERR("invalid remote processor \"%s\" for %s\n", rp_name, mbox->tx->name);
		goto out;
	}
#endif
	memcpy((void *)tx_task.tx_buffer, (void *)tx_buffer, tx_buffer_len * (sizeof(mbox_msg_t)));
	tx_task.tx_buffer_len = tx_buffer_len;
	tx_task.need_auto_ack = need_auto_ack;

	mdev = mbox->tx;
	p_tx_task = &tx_task;

	START_TTS(p_tx_task);

	/* SYNC_SENDING start */
	ret = set_status(mdev, MDEV_SYNC_SENDING);
	if (ret) {
		MBOX_PR_ERR("MSG{0x%08x, 0x%08x}\n", tx_task.tx_buffer[0], tx_task.tx_buffer[1]);
		goto out;
	}

	/* send */
	mutex_lock(&mdev->dev_lock);
	ret = hisi_mbox_task_send_sync(mdev, &tx_task);
	if (!ret && ack_buffer) {
		memcpy((void *)ack_buffer, (void *)tx_task.ack_buffer, sizeof(mbox_msg_t) / sizeof(u8) * ack_buffer_len);
	}

	PRINT_TTS(p_tx_task);
	mutex_unlock(&mdev->dev_lock);

	/* SYNC_SENDING end */
	clr_status(mdev, MDEV_SYNC_SENDING);

out:
	return ret;
}

EXPORT_SYMBOL(hisi_mbox_msg_send_sync);

int hisi_mbox_msg_send_async(struct hisi_mbox *mbox, struct hisi_mbox_task *tx_task)
{
	struct hisi_mbox_device *mdev = NULL;
	int ret = 0;
	unsigned long flags;

	if (!tx_task || !mbox || !mbox->tx) {
		MBOX_PR_ERR("invalid parameters\n");
		ret = -EINVAL;
		goto out;
	}

	mdev = mbox->tx;

	START_TTS(tx_task);

	/* ASYNC_ENQUEUE start */
	ret = set_status(mdev, MDEV_ASYNC_ENQUEUE);
	if (ret) {
		MBOX_PR_ERR("MSG{0x%08x, 0x%08x}\n", tx_task->tx_buffer[0], tx_task->tx_buffer[1]);
		goto out;
	}

	/* enqueue */
	spin_lock_irqsave(&mdev->fifo_lock, flags);
	if (kfifo_avail(&mdev->fifo) < TX_FIFO_CELL_SIZE) {
		spin_unlock_irqrestore(&mdev->fifo_lock, flags);
		ret = -ENOMEM;
		goto clearstatus;
	}

	kfifo_in(&mdev->fifo, &tx_task, TX_FIFO_CELL_SIZE);

	spin_unlock_irqrestore(&mdev->fifo_lock, flags);

	wake_up_interruptible(&mdev->tx_wait);

clearstatus:
	/* ASYNC_ENQUEUE end */
	clr_status(mdev, MDEV_ASYNC_ENQUEUE);
out:
	return ret;
}

EXPORT_SYMBOL(hisi_mbox_msg_send_async);

static struct hisi_mbox_task *hisi_mbox_dequeue_task(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_task *tx_task = NULL;
	unsigned long flags;

	spin_lock_irqsave(&mdev->fifo_lock, flags);
	if (kfifo_len(&mdev->fifo) >= TX_FIFO_CELL_SIZE) {
		if (!kfifo_out(&mdev->fifo, &tx_task, TX_FIFO_CELL_SIZE))
			tx_task = NULL;
	}

	spin_unlock_irqrestore(&mdev->fifo_lock, flags);
	return tx_task;
}

void hisi_mbox_empty_task(struct hisi_mbox_device *mdev)
{
	struct hisi_mbox_task *tx_task = NULL;
	unsigned long flags;

	spin_lock_irqsave(&mdev->fifo_lock, flags);
	while (kfifo_len(&mdev->fifo) >= TX_FIFO_CELL_SIZE) {
		if (kfifo_out(&mdev->fifo, &tx_task, TX_FIFO_CELL_SIZE)) {
			hisi_mbox_task_free(&tx_task);
		}
	}
	spin_unlock_irqrestore(&mdev->fifo_lock, flags);

	mutex_lock(&mdev->dev_lock);
	/*do nothing here just to wait for the already-kfifo-out's tx_task finish */
	mutex_unlock(&mdev->dev_lock);
}

EXPORT_SYMBOL(hisi_mbox_empty_task);

static void hisi_mbox_tx_thread(unsigned long context)
{
	struct hisi_mbox_device *mdev = (struct hisi_mbox_device *)context;
	struct hisi_mbox_task *tx_task = NULL;
	int ret = 0;

	while (!kthread_should_stop()) {
		/*lint -e666 */
		ret = wait_event_interruptible(mdev->tx_wait, (kfifo_len(&mdev->fifo) >= TX_FIFO_CELL_SIZE));
		/*lint +e666 */
		if (unlikely(ret)) {
			printk("hisi_mbox_tx_thread wait event failed\n");
			continue;
		}

		mutex_lock(&mdev->dev_lock);
		/*kick out the async send request from  mdev's kfifo one by one and send it out */
		while ((tx_task = hisi_mbox_dequeue_task(mdev))) {
			ret = hisi_mbox_task_send_async(mdev, tx_task);
			PRINT_TTS(tx_task);
			hisi_mbox_task_free(&tx_task);
			/* current task unlinked */
			mdev->tx_task = NULL;
		}

		mutex_unlock(&mdev->dev_lock);
	}
	return;
}

static void hisi_mbox_rx_bh(unsigned long context)
{
	struct hisi_mbox_device *mdev = (struct hisi_mbox_device *)context;
	mbox_msg_t *rx_buffer = NULL;
	mbox_msg_len_t rx_len = 0;
	unsigned long flags;

	MBOX_PR_DEBUG("mdev %s rx enter\n", mdev->name);

	/*
	 * check msg type
	 * - if ack interrupt occur,
	 *   an entire ipc have completed, and a completion should be excuted;
	 * - if msg interrupt occur,
	 *   we need broadcast msgs to useres only after submit an ack.
	 */
	switch (mdev->cur_task) {
	case TX_TASK:
		/*mdev->ops->track(mdev, ACK_SCHE); */
		if (unlikely(NULL == mdev->tx_task)) {
			/*the tasklet is blocked by after scheduled, after timeout for TASKLET jam, the tx_task is set to NULL,
			 *but then this tasklet has it's turn, then abort.*/
			mdev->ops->enable_irq(mdev);
			return;
		}
		rx_len = mdev->ops->recv(mdev, &rx_buffer);
		spin_lock_irqsave(&mdev->complete_lock, flags);

		BH_TTS(mdev->tx_task);
		mdev->tx_task->ack_buffer = rx_buffer;
		mdev->tx_task->ack_buffer_len = rx_len;
		mdev->completed = COMPLETED;
		complete(&mdev->complete);
		spin_unlock_irqrestore(&mdev->complete_lock, flags);
		break;

	case RX_TASK:
		/*mdev->ops->track(mdev, MSG_SCHE); */
		rx_len = mdev->ops->recv(mdev, &rx_buffer);
		/*mdev->ops->track(mdev, DEAL_START); */
		atomic_notifier_call_chain(&mdev->notifier, rx_len, (void *)rx_buffer);
		/*mdev->ops->track(mdev, DEAL_END); */
		mdev->ops->ack(mdev, NULL, 0);
		/*mdev->ops->track(mdev, SEND_ACK); */
		break;

	default:
		break;
	}

	mdev->ops->enable_irq(mdev);
	MBOX_PR_DEBUG("mdev %s rx leave\n", mdev->name);

	return;
}

static int hisi_mbox_interrupt(int irq, void *p)
{
	struct hisi_mbox_device *mdev = (struct hisi_mbox_device *)p;

	mdev = mdev->ops->irq_to_mdev(mdev, &mdevices, irq);
	if (!mdev) {
		MBOX_PR_ERR("an unexpected inttrupt %d occured\n", irq);
		return IRQ_NONE;
	}

	if (!mdev->configured) {
		MBOX_PR_ERR("mdev %s has not startup yet\n", mdev->name);
		return IRQ_NONE;
	}

	/* ipc */
	if (mdev->ops->is_stm(mdev, DESTINATION_STATUS)) {
		MBOX_PR_DEBUG("mdev %s ipc\n", mdev->name);
		mdev->cur_task = RX_TASK;
		mdev->cur_irq = irq;
		mdev->ops->disable_irq(mdev);
		tasklet_schedule(&mdev->rx_bh);
		return IRQ_HANDLED;
	}

	/* ack */
	spin_lock(&mdev->complete_lock);
	if (mdev->tx_task && mdev->ops->is_stm(mdev, ACK_STATUS)) {
		RECEIVE_TTS(mdev->tx_task);

		if (unlikely(COMPLETED == mdev->completed)) {
			spin_unlock(&mdev->complete_lock);
			/*need to clear the ack if the ack is reached after 300ms' timeout, otherwise the ack will trigger all the time */
			mdev->ops->clr_ack(mdev);
			MBOX_PR_ERR("%s(%d) has been handled" "caused of current IPC timeout(ISR).\n", mdev->name, irq);
			return IRQ_HANDLED;
		} else {
			MBOX_PR_DEBUG("mdev %s ack\n", mdev->name);
			mdev->completed = COMPLETING;
			mdev->cur_task = TX_TASK;
			mdev->cur_irq = irq;
			mdev->ops->disable_irq(mdev);
			tasklet_schedule(&mdev->rx_bh);
		}
	}
	spin_unlock(&mdev->complete_lock);

	MBOX_PR_DEBUG("mdev %s interrupt leave, irq %d\n", mdev->name, irq);
	return IRQ_HANDLED;
}

static void hisi_mbox_shutdown(struct hisi_mbox_device *mdev, mbox_mail_type_t mail_type)
{
	mutex_lock(&mdev->dev_lock);
	if (!--mdev->configured) {
		MBOX_PR_DEBUG("%s, %s shutdown.\n", MODULE_NAME, mdev->name);

		mdev->ops->free_irq(mdev, (void *)mdev);
		mdev->ops->shutdown(mdev);

		switch (mail_type) {
		case TX_MAIL:
			kthread_stop(mdev->tx_kthread);
			kfifo_free(&mdev->fifo);
		case RX_MAIL:
			tasklet_kill(&mdev->rx_bh);
			break;
		default:
			break;
		}
	}

	mutex_unlock(&mdev->dev_lock);
	return;
}

static void hisi_mbox_free(struct hisi_mbox **mbox)
{
	struct hisi_mbox *_mbox = *mbox;

	kfree(_mbox->name);
	kfree(_mbox);
	_mbox = NULL;

	*mbox = _mbox;
	return;
}

void hisi_mbox_put(struct hisi_mbox **mbox)
{
	struct hisi_mbox *_mbox = NULL;
	struct hisi_mbox_device *mdev[MAIL_TYPE_MAX] = { NULL };
	int i;

	if (!mbox) {
		MBOX_PR_ERR("null pointer\n");
		return;
	}

	_mbox = *mbox;
	if (!_mbox) {
		MBOX_PR_ERR("null pointer\n");
		return;
	}

	/* tx & rx mailbox devices deinit */
	mdev[TX_MAIL] = _mbox->tx;
	mdev[RX_MAIL] = _mbox->rx;
	for (i = TX_MAIL; i < MAIL_TYPE_MAX; i++) {
		if (mdev[i])
			hisi_mbox_shutdown(mdev[i], i);
	}

	if (mdev[RX_MAIL] && _mbox->nb) {
		atomic_notifier_chain_unregister(&mdev[RX_MAIL]->notifier, _mbox->nb);
	}

	hisi_mbox_free(mbox);
	return;
}

EXPORT_SYMBOL(hisi_mbox_put);

static int hisi_mbox_startup(struct hisi_mbox_device *mdev, mbox_mail_type_t mail_type)
{
	int ret = 0;
	unsigned int tx_buff = 0;
	int policy = 0;

	mutex_lock(&mdev->dev_lock);
	if (!mdev->configured++) {
		switch (mail_type) {
		case TX_MAIL:
			if (0 == strncmp(mdev->name, (const char *)"mailbox-13", strlen("mailbox-13"))) {
				tx_buff = MAILBOX13_MAX_TX_BUFFER;	/*mbox-13  is only gived 16 fifo */
			} else {
				tx_buff = MAILBOX_MAX_TX_BUFFER;
			}
			if (kfifo_alloc(&mdev->fifo, tx_buff, GFP_KERNEL)) {
				MBOX_PR_ERR("tx mdev %s alloc kfifo failed\n", mdev->name);
				ret = -ENOMEM;
				goto deconfig;
			}

			init_waitqueue_head(&mdev->tx_wait);
			/*create the async tx thread */
			mdev->tx_kthread = kthread_create(hisi_mbox_tx_thread, (unsigned long)mdev, "%s", mdev->name);
			if (unlikely(IS_ERR(mdev->tx_kthread))) {
				MBOX_PR_ERR("create kthread tx_kthread failed!\n");
				ret = -EINVAL;
				kfifo_free(&mdev->fifo);
				goto deconfig;
			} else {
				struct sched_param param;
				if (0 == strncmp(mdev->name, (const char *)"mailbox-13", strlen("mailbox-13"))) {
					/*set the freq adjust to the max 99, to solve the schedule nervous problem */
					param.sched_priority = (MAX_RT_PRIO - 1);
					policy = SCHED_FIFO;
				} else {
					/*set the thread's priority to 80, the bigger sched_priority, the higher priority */
					param.sched_priority = (MAX_RT_PRIO - 20);
					policy = SCHED_RR;
				}
				(void)sched_setscheduler(mdev->tx_kthread, policy, &param);
				wake_up_process(mdev->tx_kthread);
			}
			/* tx mdev owns rx tasklet as well, for ipc ack msg. */
		case RX_MAIL:
			tasklet_init(&mdev->rx_bh, hisi_mbox_rx_bh, (unsigned long)mdev);
			break;
		default:
			ret = -EINVAL;
			goto deconfig;
		}

		ret = mdev->ops->startup(mdev);
		if (ret) {
			MBOX_PR_ERR("mdev %s startup failed\n", mdev->name);
			ret = -ENODEV;
			goto deinit_work;
		}

		ret = mdev->ops->request_irq(mdev, (irq_handler_t) hisi_mbox_interrupt, (void *)mdev);
		if (ret) {
			MBOX_PR_ERR("mdev %s request irq failed\n", mdev->name);
			ret = -ENODEV;
			goto shutdown;
		}
	}

	mutex_unlock(&mdev->dev_lock);
	return ret;

shutdown:
	mdev->ops->shutdown(mdev);
deinit_work:
	switch (mail_type) {
	case TX_MAIL:
		/*flush_work(&mdev->tx_work);*/
		kfifo_free(&mdev->fifo);
	case RX_MAIL:
		tasklet_kill(&mdev->rx_bh);
		break;
	default:
		break;
	}
deconfig:
	mdev->configured--;
	mutex_unlock(&mdev->dev_lock);
	return ret;
}

static struct hisi_mbox *hisi_mbox_alloc(struct hisi_mbox_device *tx_mdev, struct hisi_mbox_device *rx_mdev, const char *rp_name)
{
	struct hisi_mbox *mbox = NULL;
	char *mbox_name = NULL;
	int len = strlen("->") + strlen(rp_name);

	mbox_name = kmalloc(sizeof(char) * (len + 1), GFP_KERNEL);
	if (!mbox_name) {
		MBOX_PR_ERR("no memory for mbox name <->%s>\n", rp_name);
		goto out;
	}
	snprintf(mbox_name, len + 1, "->%s", rp_name);

	mbox = kmalloc(sizeof(*mbox), GFP_KERNEL);
	if (!mbox) {
		MBOX_PR_ERR("no memory for mbox <%s>\n", mbox_name);
		kfree(mbox_name);
		goto out;
	}

	mbox->name = (const char *)mbox_name;
	mbox->tx = tx_mdev;
	mbox->rx = rx_mdev;
	mbox->nb = NULL;

out:
	return mbox;
}

/*
 * search a certain mdev,
 * which could access the remote proccessor, "rp_name", in the list.
 */
static struct hisi_mbox_device *hisi_mbox_device_get(struct list_head *list, mbox_mail_type_t mtype, const char *rp_name)
{
	struct hisi_mbox_device *mdev = NULL;
	struct hisi_mbox_device *_mdev = NULL;

	list_for_each_entry(_mdev, list, node) {
		/*
		 * though remote processor of mailboxes could be uncertain,
		 * when mailboxes prepare for use, it won't be an uncertain one
		 * or an unaccessible one, when a tx task of mailbox is alloced.
		 *
		 * the regulation is compatible for some mailboxes, whose remote
		 * processor could not be assigned, until mailboxes is used
		 * in an ipc.
		 */
		if (_mdev->ops->check(_mdev, mtype, rp_name) != RPUNACCESSIBLE) {
			mdev = _mdev;
			break;
		}
	}

	return mdev;
}

struct hisi_mbox *hisi_mbox_get(const char *rp_name, struct notifier_block *nb)
{
	struct hisi_mbox *mbox = NULL;
	struct list_head *list = &mdevices;
	struct hisi_mbox_device *mdev[MAIL_TYPE_MAX] = { NULL };
	int i;

	if (list_empty(list)) {
		MBOX_PR_ERR("mailboxes not ready\n");
		goto out;
	}

	if (!rp_name) {
		MBOX_PR_ERR("null pointer\n");
		goto out;
	}

	mdev[TX_MAIL] = hisi_mbox_device_get(list, TX_MAIL, rp_name);
	mdev[RX_MAIL] = hisi_mbox_device_get(list, RX_MAIL, rp_name);
	if ((!mdev[TX_MAIL]) && (!mdev[RX_MAIL])) {
		/*MBOX_PR_ERR("neither tx nor rx mboxes were gotten, may get later\n");*/
		goto out;
	}

	for (i = TX_MAIL; i < MAIL_TYPE_MAX; i++) {
		if ((RX_MAIL == i) && mdev[i] && nb)
			atomic_notifier_chain_register(&mdev[i]->notifier, nb);

		if (mdev[i] && hisi_mbox_startup(mdev[i], i)) {
			MBOX_PR_ERR("%s mdev %s startup failed\n", ((i == TX_MAIL) ? "tx" : "rx"), mdev[i]->name);
			goto shutdown;
		}
	}

	mbox = hisi_mbox_alloc(mdev[TX_MAIL], mdev[RX_MAIL], rp_name);
	if (!mbox) {
		MBOX_PR_ERR("failed to alloc mbox\n");
		goto shutdown;
	}
	mbox->nb = nb;
	MBOX_DEBUG_OFF(mbox);

	return mbox;

shutdown:
	if ((RX_MAIL == i) && nb)
		atomic_notifier_chain_unregister(&mdev[i]->notifier, nb);
	while (i--) {
		if (mdev[i])
			hisi_mbox_shutdown(mdev[i], i);
	}
out:
	return mbox;
}

EXPORT_SYMBOL(hisi_mbox_get);

void hisi_mbox_device_deactivate(struct hisi_mbox_device **list)
{
	struct hisi_mbox_device *mdev = NULL;
	struct hisi_mbox_task *tx_task = NULL;
	int i, ret;

	for (i = 0; (mdev = list[i]); i++) {
		(void)set_status(mdev, MDEV_DEACTIVATED);

		mutex_lock(&mdev->dev_lock);
		if (!mdev->configured) {
			mutex_unlock(&mdev->dev_lock);
			continue;
		}
		mutex_unlock(&mdev->dev_lock);

		/* flush tx work & tx task list synchronously */
		/*flush_work(&mdev->tx_work);*/

		mutex_lock(&mdev->dev_lock);
		while ((tx_task = hisi_mbox_dequeue_task(mdev))) {
			ret = hisi_mbox_task_send_sync(mdev, tx_task);
			/* current task unlinked */
			mdev->tx_task = NULL;
		}
		mutex_unlock(&mdev->dev_lock);
	}

	return;
}

EXPORT_SYMBOL(hisi_mbox_device_deactivate);

void hisi_mbox_device_activate(struct hisi_mbox_device **list)
{
	struct hisi_mbox_device *mdev = NULL;
	int i;

	for (i = 0; (mdev = list[i]); i++)
		clr_status(mdev, MDEV_DEACTIVATED);

	return;
}

EXPORT_SYMBOL(hisi_mbox_device_activate);

static struct class *hisi_mbox_class;

int hisi_mbox_device_unregister(struct hisi_mbox_device **list)
{
	struct hisi_mbox_device *mdev = NULL;
	int i;

	if (!list) {
		MBOX_PR_ERR("no mboxes registered\n");
		return -EINVAL;
	}

	for (i = 0; (mdev = list[i]); i++) {
		mutex_destroy(&mdev->dev_lock);
		device_destroy(hisi_mbox_class, (dev_t) i);
		list_del(&mdev->node);
	}
#ifdef CONFIG_HISI_MAILBOX_DEBUGFS
	mbox_debugfs_unregister(list);
#endif

	list = NULL;

	return 0;
}

EXPORT_SYMBOL(hisi_mbox_device_unregister);

static int hisi_mbox_device_is_valid(struct hisi_mbox_device *mdev)
{
	if (WARN_ON(!mdev->ops->startup || !mdev->ops->shutdown || !mdev->ops->check || !mdev->ops->recv || !mdev->ops->send || !mdev->ops->refresh || !mdev->ops->request_irq || !mdev->ops->free_irq || !mdev->ops->irq_to_mdev || !mdev->ops->is_stm))
		return 0;

	return 1;
}

int hisi_mbox_device_register(struct device *parent, struct hisi_mbox_device **list)
{
	struct hisi_mbox_device *mdev = NULL;
	int ret, i;

	if (!list) {
		MBOX_PR_ERR("null pointer\n");
		return -EINVAL;
	}

	for (i = 0; (mdev = list[i]); i++) {
		if (!hisi_mbox_device_is_valid(mdev)) {
			MBOX_PR_ERR("invalid mdev\n");
			ret = -EINVAL;
			goto err_out;
		}

		mdev->dev = device_create(hisi_mbox_class, parent, (dev_t) i, mdev, "%s", mdev->name);
		if (IS_ERR(mdev->dev)) {
			MBOX_PR_ERR("mdev %s can not create device\n", mdev->name);
			ret = PTR_ERR(mdev->dev);
			goto err_out;
		}

		spin_lock_init(&mdev->fifo_lock);
		mdev->status = 0;
		spin_lock_init(&mdev->status_lock);
		spin_lock_init(&mdev->complete_lock);
		mutex_init(&mdev->dev_lock);

		init_completion(&mdev->complete);

		ATOMIC_INIT_NOTIFIER_HEAD(&mdev->notifier);
		list_add_tail(&mdev->node, &mdevices);
	}
#ifdef CONFIG_HISI_MAILBOX_DEBUGFS
	mbox_debugfs_register(list);
#endif
	return 0;

err_out:
	while (i--) {
		mdev = list[i];
		list_del(&mdev->node);
		mutex_destroy(&mdev->dev_lock);
		device_destroy(hisi_mbox_class, (dev_t) i);
	}

	return ret;
}

EXPORT_SYMBOL(hisi_mbox_device_register);

static int __init hisi_mbox_init(void)
{
	pr_debug("%s: init\n", MODULE_NAME);

	hisi_mbox_class = class_create(THIS_MODULE, "hisi-mailbox");
	if (IS_ERR(hisi_mbox_class))
		return PTR_ERR(hisi_mbox_class);

	spin_lock_init(&g_task_buffer_lock);
	return 0;
}

postcore_initcall(hisi_mbox_init);

static void __exit hisi_mbox_exit(void)
{
	if (hisi_mbox_class)
		class_destroy(hisi_mbox_class);

	return;
}

module_exit(hisi_mbox_exit);

MODULE_DESCRIPTION("HS mailbox interface");
MODULE_LICENSE("GPL V2");
