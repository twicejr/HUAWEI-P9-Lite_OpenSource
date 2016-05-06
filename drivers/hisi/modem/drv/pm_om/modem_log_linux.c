/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2016. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/suspend.h>
#include <linux/wakelock.h>
#include <linux/uaccess.h>
#include <linux/poll.h>

#include <osl_generic.h>
#include <bsp_ipc.h>
#include <bsp_slice.h>
#include <bsp_ring_buffer.h>
#include <bsp_modem_log.h>

#define IPC_ACPU_INT_SRC_CCPU_MODEM_LOG (IPC_ACPU_INT_SRC_CCPU_PM_OM)

#define modem_log_pr_err(fmt, ...)      pr_err("[modem log]: " fmt, ##__VA_ARGS__)
#define modem_log_pr_err_once(fmt, ...) pr_err_once("[modem log]: " fmt, ##__VA_ARGS__)
#define modem_log_pr_debug(fmt, ...)   // pr_err("[modem log]: " fmt, ##__VA_ARGS__)

/* Ä£¿é·µ»Ø´íÎóÂë */
enum MODEM_LOG_ERR_TYPE
{
	MODEM_LOG_NO_MEM      = -ENOMEM,
	MODEM_LOG_NO_USR_INFO = -35,
	MODEM_LOG_NO_IPC_SRC  = -36,
};

struct logger_log {
	struct log_usr_info *usr_info;
	wait_queue_head_t   wq;            /* The wait queue for reader */
	struct miscdevice   misc;          /* The "misc" device representing the log */
	struct mutex        mutex;         /* The mutex that protects the @buffer */
	struct list_head    logs;          /* The list of log channels */
	u32 fopen_cnt;
};

struct modem_log
{
	struct wake_lock  wake_lock;
	struct notifier_block pm_notify;
	u32 init_flag;
};

static LIST_HEAD(modem_log_list);
struct modem_log g_modem_log;

static struct logger_log *get_modem_log_from_name(const char* name)
{
    struct logger_log *log;

    list_for_each_entry(log, &modem_log_list, logs)
    {
	    if (!strcmp(log->misc.name,name))
	    {
	        return log;
	    }
    }

    return NULL;
}

struct logger_log *get_modem_log_from_minor(int minor)
{
    struct logger_log *log;

    list_for_each_entry(log, &modem_log_list, logs)
    {
        if (log->misc.minor == minor)
        {
            return log;
        }
    }

    return NULL;
}

unsigned long kernel_user_memcpy(void* dest, u32 destMax, const void* src, u32 count)
{
	return copy_to_user(dest, src, count);
}

void modem_log_ring_buffer_get(struct log_usr_info * usr_info, struct ring_buffer *rb)
{
	if (usr_info  && usr_info->mem)
	{
		rb->buf   = usr_info->ring_buf;
		rb->read  = usr_info->mem->read;
		rb->write = usr_info->mem->write;
		rb->size  = usr_info->mem->size;
	}
	else
	{
		memset((void *)rb, 0, sizeof(*rb));
	}
}

static unsigned int modem_log_poll(struct file *file, poll_table *wait)
{
	struct logger_log *log;
	unsigned int ret = 0;

	modem_log_pr_debug("%s entry\n", __func__);
	if (!(file->f_mode & FMODE_READ))
	{
		return ret;
	}

	log = file->private_data;

	mutex_lock(&log->mutex);
	if (log->usr_info->mem && log->usr_info->mem->read != log->usr_info->mem->write)
	{
		ret = POLLIN | POLLRDNORM;
	}
	mutex_unlock(&log->mutex);

	if (!ret)
	{
		poll_wait(file, &log->wq, wait);
	}

	modem_log_pr_debug("%s exit\n", __func__);

	return ret;
}

/*
 * modem_log_read - our log's read() method
 *
 *	1) O_NONBLOCK works
 *	2) If there are no log to read, blocks until log is written to
 *  3) Will set errno to EINVAL if read
 */
static ssize_t modem_log_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
	struct logger_log *log = (struct logger_log *)file->private_data;
	struct ring_buffer rb;
	ssize_t ret = 1;
	u32 len = 0;
	DEFINE_WAIT(wait);

	modem_log_pr_debug("%s entry\n", __func__);

	while (1) {
		mutex_lock(&log->mutex);

		prepare_to_wait(&log->wq, &wait, TASK_INTERRUPTIBLE);

		if (!log->usr_info->mem_is_ok)
		{
			goto skip_read;
		}

		modem_log_ring_buffer_get(log->usr_info, &rb);

		if (log->usr_info->read_func)
		{
			ret = log->usr_info->read_func(log->usr_info, buf, (u32)count);
			if (ret)
			{
				mutex_unlock(&log->mutex);
				pr_err_once("[modem log]user(%s) read method invoked\n", log->usr_info->dev_name);
				break;
			}
		}

		ret = is_ring_buffer_empty(&rb);
skip_read:
		mutex_unlock(&log->mutex);
		if (!ret) /* has data to be read, break out */
		{
			break;
		}
		if (file->f_flags & O_NONBLOCK) {
			modem_log_pr_err_once("try again, when read file flag is O_NONBLOCK\n");
			ret = -EAGAIN;
			break;
		}

		if (signal_pending(current)) {
			ret = -EINTR;
			break;
		}

		wake_unlock(&g_modem_log.wake_lock);
		schedule();
		modem_log_pr_debug("give up cpu in modem_log_read\n");
	}

	finish_wait(&log->wq, &wait);
	if (ret)
	{
		return ret;
	}

	mutex_lock(&log->mutex);

	len = bsp_ring_buffer_readable_size(&rb);
	len = min(len, (u32)count);
	ret = bsp_ring_buffer_out(&rb, buf, len, (MEMCPY_FUNC)kernel_user_memcpy);
	if(ret < 0)
	{
		goto out;
	}

	log->usr_info->mem->read = rb.read;

	modem_log_pr_debug("%s exit\n", __func__);

out:
	mutex_unlock(&log->mutex);

	return ret;
}

/*
 * modem_log_open - our log's open() method, not support open twice by same application
 */
static int modem_log_open(struct inode *inode, struct file *file)
{
    struct logger_log * log;

    log = get_modem_log_from_minor(MINOR(inode->i_rdev));
    if(unlikely(NULL == log))
    {
        modem_log_pr_err("device get fail\n");
        return -ENODEV;
    }

    file->private_data = log;

	mutex_lock(&log->mutex);
	if (log->usr_info->open_func && log->usr_info->open_func(log->usr_info))
	{	/* generally writer tell reader memory info  */
		modem_log_pr_err("user(%s) open method error, exit\n", log->usr_info->dev_name);
		mutex_unlock(&log->mutex);
		return -EINVAL;
	}

	if (log->usr_info->mem)
	{
		log->usr_info->mem->app_is_active = 1; /* reader is ready  */
	}

	log->fopen_cnt++;

	mutex_unlock(&log->mutex);

	/* indicate that application exit exceptionally, need to clear ring buffer */
	if (log->fopen_cnt > 1)
	{
		modem_log_pr_err("file_open_cnt=%d\n", log->fopen_cnt);
		mutex_lock(&log->mutex);
		if (log->usr_info->mem)
		{
			log->usr_info->mem->read = log->usr_info->mem->write;
		}
		mutex_unlock(&log->mutex);
	}

	modem_log_pr_debug("%s entry\n", __func__);

    return 0;
}

/*
 * modem_log_release - our log's close() method
 */
static int modem_log_release(struct inode *inode, struct file *file)
{
    struct logger_log *log;

    log = file->private_data;
    if(unlikely(NULL == log))
    {
        modem_log_pr_err("device release fail\n");
        return -ENODEV;
    }

	mutex_lock(&log->mutex);
	if (log->usr_info->mem)
	{
		log->usr_info->mem->app_is_active = 0; /* reader cannot work  */
	}
	mutex_unlock(&log->mutex);

	wake_unlock(&g_modem_log.wake_lock);

	modem_log_pr_debug("%s entry\n", __func__);
	return 0;
}

static const struct file_operations modem_log_fops = {
	.read    = modem_log_read,
	.poll    = modem_log_poll,
	.open    = modem_log_open,
	.release = modem_log_release,
};


/*
 * modem_log_wakeup_all - wake up all waitquque
 */
void modem_log_wakeup_all(void)
{
    struct logger_log *log;
	wake_lock(&g_modem_log.wake_lock);
    list_for_each_entry(log, &modem_log_list, logs)
    {
		if (log->usr_info->mem && log->usr_info->mem->read != log->usr_info->mem->write)
		{
			wake_up_interruptible(&log->wq);
		}
    }
}

/*
 * modem_log_ipc_handler - wake up waitquque
 */
void modem_log_ipc_handler(u32 data)
{
	modem_log_pr_debug("ipc = 0x%x\n", data);
	modem_log_wakeup_all();
}

/*
 * modem_log_notify - modem log pm notify
 */
s32 modem_log_notify(struct notifier_block *notify_block, unsigned long mode, void *unused)
{
    struct logger_log *log;

	modem_log_pr_debug("entry\n");

	switch (mode)
	{
	case PM_POST_HIBERNATION:
		wake_lock(&g_modem_log.wake_lock);
	    list_for_each_entry(log, &modem_log_list, logs)
	    {
			if ((log->usr_info->mem) && (log->usr_info->mem->read != log->usr_info->mem->write) && (log->usr_info->mem->app_is_active))
			{
				wake_up_interruptible(&log->wq);
			}
	    }
		break;
	default:
		break;
	}

	return 0;
}

/**
 * bsp_modem_log_register - tell modem log which user information is
 * @usr_info: information which modem log need to know
 *
 * Returns 0 if success
 */
s32 bsp_modem_log_register(struct log_usr_info *usr_info)
{
	s32 ret = 0;
	struct logger_log *log = NULL;

	if (unlikely(NULL == usr_info))
	{
		ret = (s32)MODEM_LOG_NO_USR_INFO;
		modem_log_pr_err("no user info to register\n");
		goto out;
	}

	log = kzalloc(sizeof(*log), GFP_KERNEL);
	if (log == NULL)
	{
		ret = (s32)MODEM_LOG_NO_MEM;
		goto out;
	}

	log->usr_info = usr_info;

	log->misc.minor = MISC_DYNAMIC_MINOR;
	log->misc.name = kstrdup(usr_info->dev_name, GFP_KERNEL);
	if (unlikely(log->misc.name == NULL))
	{
		ret = (s32)MODEM_LOG_NO_MEM;
		goto out_free_log;
	}

	log->misc.fops = &modem_log_fops;
	log->misc.parent = NULL;

	init_waitqueue_head(&log->wq);
	mutex_init(&log->mutex);

	INIT_LIST_HEAD(&log->logs);
	list_add_tail(&log->logs, &modem_log_list);

	/* finally, initialize the misc device for this log */
	ret = misc_register(&log->misc);
	if (unlikely(ret))
	{
		modem_log_pr_err("failed to register misc device for log '%s'!\n", log->misc.name);
		goto out_rm_node;
	}

	modem_log_pr_debug("created log '%s'\n", log->misc.name);
	/* coverity[leaked_storage] */
	return 0;
out_rm_node:
	list_del(&log->logs);
out_free_log:
	kfree(log);
out:
	return ret;
}

/**
 * bsp_modem_log_fwrite_trigger - trigger file write from ring buffer to log record file
 * @usr_info: information regitered to modem log 
 */
void bsp_modem_log_fwrite_trigger(struct log_usr_info *usr_info)
{
	struct logger_log *log = NULL;

	if (!usr_info)
	{
		modem_log_pr_err("no user info\n");
		return;
	}

	log = get_modem_log_from_name(usr_info->dev_name);
	if(!log)
	{
		modem_log_pr_err("no device log\n");
		return;
	}

	/* if reader is not ready, no need to wakeup waitqueue */
	if (usr_info->mem && usr_info->mem->app_is_active)
	{
		wake_lock(&g_modem_log.wake_lock);
		wake_up_interruptible(&log->wq);
	}
	modem_log_pr_debug("%s\n", __func__);
}

/**
 * modem_log_fwrite_trigger_force - wakeup acore and trigger file write from ring buffer to log record file
 */
void modem_log_fwrite_trigger_force(void)
{
	modem_log_wakeup_all();
}

/**
 * bsp_modem_log_init - modem log init
 */
static int __init modem_log_init(void)
{
	wake_lock_init(&g_modem_log.wake_lock, WAKE_LOCK_SUSPEND, "modem_log_wake");

	g_modem_log.pm_notify.notifier_call = modem_log_notify;
	register_pm_notifier(&g_modem_log.pm_notify);


	if(0 != bsp_ipc_int_connect((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_MODEM_LOG, 
		(voidfuncptr)modem_log_ipc_handler, IPC_ACPU_INT_SRC_CCPU_MODEM_LOG))
	{
		goto ipc_err;
	}
	if(0 != bsp_ipc_int_enable((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_MODEM_LOG))
	{
		goto ipc_err;
	}

	g_modem_log.init_flag = 1;
	modem_log_pr_err("init ok\n");

	return 0;
ipc_err:
	modem_log_pr_err("ipc err\n");
	return MODEM_LOG_NO_IPC_SRC;
}

module_init(modem_log_init);
