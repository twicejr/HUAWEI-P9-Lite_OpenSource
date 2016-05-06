#include <linux/pm_qos.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/compiler.h>
#include <linux/syscalls.h>

#include "hisi_freq_ctl.h"

/*
The threshold of total io_wait_time:
If total io_wait_time is bigger than the threshold,
add ddr frequence request immediately.
*/
#define IO_WAIT_TIME_THRESHOLD			100
#ifdef HISI_DDR_FREQ_REQ
/* The band of ddr request */
#define DDR_REQUEST_VALUE_DOWN			1153
#define DDR_REQUEST_VALUE_UP			2303
#endif
/*
The period of the delete_request timer:
When there is not io_req waiting in flight, this timer should be started.
Before time out, if one io_req wait in flight, this timer should be canceled.
*/
#define REMOVE_REQ_TIME_MS				350

/*
when io_is_busy is set to 1,will take iowait time into account when
caculating cpu load the default value is 0
*/
#define PATH_IO_IS_BUSY \
	"/sys/devices/system/cpu/cpu0/cpufreq/interactive/io_is_busy"
#ifdef HISI_DDR_FREQ_REQ
static s32 ddr_qos_update_request(s32 ddr_request_value,
				  struct pm_qos_request *ddr_req)
{
	s32 new_value;
	int cur_ddr_band;

	new_value = ddr_request_value;

	cur_ddr_band = pm_qos_request(PM_QOS_MEMORY_THROUGHPUT);

	if (cur_ddr_band < DDR_REQUEST_VALUE_DOWN)
		new_value += DDR_REQUEST_VALUE_DOWN - cur_ddr_band;
	else if (cur_ddr_band > DDR_REQUEST_VALUE_UP)
		new_value = 0;

	if (new_value != ddr_request_value) {
		ddr_request_value = new_value;
		pm_qos_update_request(ddr_req, ddr_request_value);
		pr_err("%s: block ddr freq request update to %d,curent ddr band is %d\n",
			__func__, ddr_request_value, cur_ddr_band);
	}
	return ddr_request_value;
}

static s32 ddr_qos_add_request(struct pm_qos_request *ddr_req)
{
	int cur_ddr_band;
	s32 ddr_request_value;

	ddr_req->pm_qos_class = 0;

	cur_ddr_band = pm_qos_request(PM_QOS_MEMORY_THROUGHPUT);
	if (cur_ddr_band > DDR_REQUEST_VALUE_DOWN)
		ddr_request_value = 0;
	else
		ddr_request_value = DDR_REQUEST_VALUE_DOWN - cur_ddr_band;
	pm_qos_add_request(ddr_req,
					PM_QOS_MEMORY_THROUGHPUT,
					ddr_request_value);
	pr_err("%s: block ddr freq request add.request_value = %d, curent ddr band is %d\n",
		__func__, ddr_request_value, cur_ddr_band);
	return ddr_request_value;
}


static void ddr_qos_remove_request(struct pm_qos_request *ddr_req)
{
	pm_qos_remove_request(ddr_req);
	pr_err("%s: block ddr freq request remove\n", __func__);
}
#endif
static long set_io_is_busy(void)
{
	long fd_io_is_busy;
	long cnt, ret;
	ret = 0;
	fd_io_is_busy = sys_open(PATH_IO_IS_BUSY, O_WRONLY, 0660);

	if (fd_io_is_busy < 0) {
		/*
		 *we ignore the error that the file is not exit,because
		 *1.The io_is_busy has not been created before the board
		 *start up to lanch,which we can accept
		 *2.When the board start up completely,the io_is_busy will
		 *always exit;
		 */
		if (-ENOENT != fd_io_is_busy)
			pr_err("%s open io_is_busy failed %ld\n",
			       __func__, fd_io_is_busy);
		ret = fd_io_is_busy;
		return ret;
	}
	cnt = sys_write(fd_io_is_busy, "1", 1);
	if (cnt < 0) {
		ret = cnt;
		pr_err("%s write io_is_busy failed %ld\n", __func__,
		       cnt);
		goto close;
	}

close:
	(void)sys_close(fd_io_is_busy);
	return ret;
}

static long clear_io_is_busy(void)
{
	long fd_io_is_busy;
	long cnt, ret;
	ret = 0;

	fd_io_is_busy = sys_open(PATH_IO_IS_BUSY, O_WRONLY, 0660);

	if (fd_io_is_busy < 0) {
		/*
		 *we ignore the error that the file is not exit,because
		 *1.The io_is_busy has not been created before the board
		 *start up to lanch,which we can accept
		 *2.When the board start up completely,the io_is_busy will
		 *always exit;
		 */
		if (-ENOENT != fd_io_is_busy)
			pr_err("%s open io_is_busy failed %ld\n",
			       __func__, fd_io_is_busy);
		ret = fd_io_is_busy;
		return ret;
	}
	cnt = sys_write(fd_io_is_busy, "0", 1);
	if (cnt < 0) {
		ret = cnt;
		pr_err("%s write io_is_busy failed %ld\n", __func__,
		       cnt);
		goto close;
	}

close:
	(void)sys_close(fd_io_is_busy);
	return ret;
}

/*
*when io_is_busy is set to 1,will take iowait time into account
*when caculating cpu load
*/
static void cpu_freq_request_add(void)
{
	if (!set_io_is_busy())
		pr_debug("%s io_is_busy is set,blk cpu freq req add\n",
		       __func__);
}

/*
*set sys_fs point io_is_busy to 0,will not take iowait time into account
*when caculating cpu load
*/
static void cpu_freq_request_remove(void)
{
	if (!clear_io_is_busy())
		pr_debug("%s io_is_busy is clear,cpu_freq req remove\n",
		       __func__);
}

struct hisi_freq_req_ops {
	s32 (*ddr_update_req)(s32 ddr_request_value,
			      struct pm_qos_request *ddr_req);
	s32 (*ddr_add_req)(struct pm_qos_request *ddr_req);
	void (*ddr_remove_request)(struct pm_qos_request *ddr_req);
	void (*cpu_freq_req_add)(void);
	void (*cpu_freq_req_remove)(void);
};


struct freq_ctrl {
	spinlock_t		lock;
	struct mutex	m_lock;
	int cur_type;/* The current stat of ddr frequence request */
	struct pm_qos_request *ddr_req;
	int delete_req_timer_start;/* The sign of the delete_request timer */
	int total_io_wait_time;/* The counter of total io_wait_time */
	s32 ddr_request_value;
	struct workqueue_struct *workqueue;
	struct work_struct work;
	struct delayed_work del_work;
	struct hisi_freq_req_ops *req_ops;
	int new_req_type;
	int new_time_in_queue;
};

static struct freq_ctrl *freq_ctrl_ptr = NULL;

static struct hisi_freq_req_ops freq_req_ops = {
	.ddr_update_req = NULL,
	.ddr_add_req = NULL,
	.ddr_remove_request = NULL,
	.cpu_freq_req_add = cpu_freq_request_add,
	.cpu_freq_req_remove = cpu_freq_request_remove,
};

static void delete_freq_req_work(struct work_struct *work)
{
	if (unlikely((NULL == freq_ctrl_ptr) ||
			(NULL == freq_ctrl_ptr->workqueue)))
		return;

	if ((freq_ctrl_ptr->req_ops->ddr_add_req) &&
			(NULL == freq_ctrl_ptr->ddr_req))
		return;

	/* Delete the ddr frequence request */
	mutex_lock(&freq_ctrl_ptr->m_lock);
	freq_ctrl_ptr->cur_type = FREQ_REQ_REMOVE;
	if (freq_ctrl_ptr->req_ops->ddr_remove_request)
		freq_ctrl_ptr->req_ops->ddr_remove_request(
		    freq_ctrl_ptr->ddr_req);
	if (freq_ctrl_ptr->req_ops->cpu_freq_req_remove)
		freq_ctrl_ptr->req_ops->cpu_freq_req_remove();
	freq_ctrl_ptr->delete_req_timer_start = 0;
	mutex_unlock(&freq_ctrl_ptr->m_lock);
	return;
}

static void hisi_blk_freq_ctrl_work(struct work_struct *work)
{
	int req_type;
	int time_in_queue;
	unsigned long flags;

	if (unlikely((NULL == freq_ctrl_ptr) ||
			(NULL == freq_ctrl_ptr->workqueue)))
		return;
	if ((freq_ctrl_ptr->req_ops->ddr_add_req) &&
		(NULL == freq_ctrl_ptr->ddr_req))
		return;

	spin_lock_irqsave(&freq_ctrl_ptr->lock, flags);
	req_type = freq_ctrl_ptr->new_req_type;
	time_in_queue = freq_ctrl_ptr->new_time_in_queue;
	spin_unlock_irqrestore(&freq_ctrl_ptr->lock, flags);

	mutex_lock(&freq_ctrl_ptr->m_lock);

	if (FREQ_REQ_ADD == freq_ctrl_ptr->cur_type) {
		if (freq_ctrl_ptr->req_ops->ddr_update_req)
			freq_ctrl_ptr->ddr_request_value =
			    freq_ctrl_ptr->req_ops->ddr_update_req(
				freq_ctrl_ptr->ddr_request_value,
				freq_ctrl_ptr->ddr_req);
	}

	if (FREQ_REQ_ADD == req_type) {
		if (FREQ_REQ_ADD == freq_ctrl_ptr->cur_type) {
			/*
			new request:	add_freq_req
			current state:	add_freq_req
			process:	Cancel the delete_request timer,
			if the timer has already been started.
			*/
			if (freq_ctrl_ptr->delete_req_timer_start) {
				cancel_delayed_work_sync(
				    &freq_ctrl_ptr->del_work);
				freq_ctrl_ptr->delete_req_timer_start = 0;
			}
		} else {
			/*
			new request:	add_ddr_freq_req
			current state:	remove_ddr_freq_req
			process:	1) Add total_io_wait_time value.
			2) If total_io_wait_time is bigger than
			threshold,start ddr frequence request.
			*/
			freq_ctrl_ptr->total_io_wait_time += time_in_queue;

			if (freq_ctrl_ptr->total_io_wait_time >=
			    IO_WAIT_TIME_THRESHOLD) {
				if (freq_ctrl_ptr->req_ops->ddr_add_req)
					freq_ctrl_ptr->ddr_request_value =
					    freq_ctrl_ptr->req_ops->ddr_add_req(
						freq_ctrl_ptr->ddr_req);
				if (freq_ctrl_ptr->req_ops->cpu_freq_req_add)
					freq_ctrl_ptr->req_ops
					    ->cpu_freq_req_add();

				freq_ctrl_ptr->cur_type = FREQ_REQ_ADD;
				freq_ctrl_ptr->total_io_wait_time = 0;
			}
		}
	} else {
		if (FREQ_REQ_REMOVE == freq_ctrl_ptr->cur_type) {
			/*
			new request:	remove_freq_req
			current state:	remove_freq_req
			process:	Reduce total_io_wait_time value.
			*/
			if (freq_ctrl_ptr->total_io_wait_time <= time_in_queue)
				freq_ctrl_ptr->total_io_wait_time = 0;
			else
				freq_ctrl_ptr->total_io_wait_time -=
				    time_in_queue;
		} else {
			/*
			new request:	remove_freq_req
			current state:	add_freq_req
			process:	Start the delete_request timer.
			*/
			if (0 == freq_ctrl_ptr->delete_req_timer_start) {
				freq_ctrl_ptr->delete_req_timer_start = 1;
				queue_delayed_work(
				    freq_ctrl_ptr->workqueue,
				    &freq_ctrl_ptr->del_work,
				    msecs_to_jiffies(REMOVE_REQ_TIME_MS));
			}
		}
	}

	mutex_unlock(&freq_ctrl_ptr->m_lock);
	return;
}

void hisi_blk_freq_request(int req_type, int time_in_queue)
{
	unsigned long flags;
	if (unlikely((NULL == freq_ctrl_ptr) ||
		(NULL == freq_ctrl_ptr->workqueue)))
		return;

	if ((freq_ctrl_ptr->req_ops->ddr_add_req) &&
		(NULL == freq_ctrl_ptr->ddr_req))
		return;

	spin_lock_irqsave(&freq_ctrl_ptr->lock, flags);
	freq_ctrl_ptr->new_req_type = req_type;
	freq_ctrl_ptr->new_time_in_queue = time_in_queue;
	spin_unlock_irqrestore(&freq_ctrl_ptr->lock, flags);

	queue_work(freq_ctrl_ptr->workqueue, &freq_ctrl_ptr->work);
	return;
}

void hisi_blk_freq_ctrl_init(void)
{
	/* Init the struction When this function be called the first time */
	if (NULL == freq_ctrl_ptr) {
		freq_ctrl_ptr = kzalloc(sizeof(struct freq_ctrl), GFP_KERNEL);
		if (NULL == freq_ctrl_ptr) {
			pr_err("%s: kzalloc freq_ctrl_ptr error\n", __func__);
			return;
		}
		pr_err("%s: hisi blk freq ctrl init: io_wait_time_threshold=%d, remove_req_time=%dms\n",
				__func__, IO_WAIT_TIME_THRESHOLD,
				REMOVE_REQ_TIME_MS);
#ifdef HISI_DDR_FREQ_REQ
		pr_err("%s: hisi block ddr frequence ctrl: ddr_req_value_down=%d, ddr_req_value_up=%d\n",
				__func__, DDR_REQUEST_VALUE_DOWN,
				DDR_REQUEST_VALUE_UP);
#endif
		spin_lock_init(&freq_ctrl_ptr->lock);
		mutex_init(&freq_ctrl_ptr->m_lock);
	}

	freq_ctrl_ptr->req_ops = &freq_req_ops;

	if (freq_ctrl_ptr->req_ops->ddr_add_req) {
		if (NULL == freq_ctrl_ptr->ddr_req) {
			freq_ctrl_ptr->ddr_req = kmalloc(
			sizeof(struct pm_qos_request), GFP_KERNEL);
			if (freq_ctrl_ptr->ddr_req == NULL) {
				pr_err("%s: malloc ddr req error\n", __func__);
				return;
			}
		}
	}

	if (NULL == freq_ctrl_ptr->workqueue) {
		freq_ctrl_ptr->workqueue =
			create_singlethread_workqueue("hisi_block_freq_ctrl");
		if (NULL == freq_ctrl_ptr->workqueue) {
			pr_err("%s: creat workqueue error\n", __func__);
			return;
		}
		INIT_WORK(&freq_ctrl_ptr->work, hisi_blk_freq_ctrl_work);
		INIT_DELAYED_WORK(&freq_ctrl_ptr->del_work,
			delete_freq_req_work);
	}

	/* Init end */

	return;
}
