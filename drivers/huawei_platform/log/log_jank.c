/*
 *  drivers/huawei/device/log_jank.c
 *
 *  Copyright (C) 2014 Huawei Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#if defined (CONFIG_LOG_JANK)
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/aio.h>
#include <linux/types.h>
#include <linux/mutex.h>
#include <huawei_platform/log/hw_log.h>
#include <huawei_platform/log/log_jank.h>

#define   MAX_WORK_COUNT   10
#define   MAX_TAG_SIZE     64
#define   MAX_MSG_SIZE     256
#define HWLOG_TAG	log_jank
HWLOG_REGIST();

struct my_work_struct{
    int   bWaiting;
    u16   nPrio;
    u16   ntagid;
    u64   uptime;
    u64   realtime;
    int   msglen;
    char  msg[MAX_MSG_SIZE];
    struct work_struct writelog;
};

static bool             bInited = false;
static int              nwork_index = 0;
struct my_work_struct   janklog_work[MAX_WORK_COUNT];
struct workqueue_struct *janklog_workqueue = NULL;

static int __write_jank_init(struct my_work_struct  *pjanklog);
static int __write_jank_kernel(struct my_work_struct  *pjanklog);

static int (*write_jank)(struct my_work_struct  *pjanklog) = __write_jank_init;
static struct file* filp = NULL;

static DEFINE_MUTEX(janklogfile_mutex);
static DEFINE_RAW_SPINLOCK(janklog_spinlock);

void janklog_write(struct work_struct *p_work)
{
    struct my_work_struct *p_janklog_work = container_of(p_work, struct my_work_struct, writelog);
    write_jank(p_janklog_work);
    p_janklog_work->bWaiting = 0;
}

static int __init janklog_workqueue_init(void)
{
    int   i;

    if (bInited) {
        hwlog_err("create jank_workqueue again\n");
		return 1;
	}
	hwlog_info("jank_log: create jank_workqueue\n");
    janklog_workqueue = create_singlethread_workqueue("janklog_workqueue");
    if (!janklog_workqueue)
    {
        hwlog_err("failed to create janklog_workqueue\n");
        return 1;
    }
    nwork_index = 0;
    for (i = 0;i <MAX_WORK_COUNT;i++)
    {
        INIT_WORK(&(janklog_work[i].writelog), janklog_write);
        janklog_work[i].bWaiting = 0;
    }
    bInited = true;

    return 0;
}

static void __exit janklog_workqueue_destory(void)
{
    if (janklog_workqueue)
    {
        destroy_workqueue(janklog_workqueue);
        janklog_workqueue = NULL;
    }
    if (0 == IS_ERR(filp))
    {
        filp_close(filp, NULL);
        filp = NULL;
    }
}

static int __write_jank_init(struct my_work_struct  *pjanklog)
{
    mm_segment_t oldfs;

    mutex_lock(&janklogfile_mutex);
    if (__write_jank_init == write_jank)
    {
        oldfs = get_fs();
        set_fs(get_ds());

        filp = filp_open(LOG_JANK_FS, O_WRONLY, 0);

        set_fs(oldfs);

        if (IS_ERR(filp)) {
            hwlog_err("failed to open %s: %ld \n", LOG_JANK_FS, PTR_ERR(filp));
            mutex_unlock(&janklogfile_mutex);
            return 0;
        } else {
            write_jank = __write_jank_kernel;
        }
    }
    mutex_unlock(&janklogfile_mutex);

    return write_jank(pjanklog);
}
/*
static int __write_jank_null(char* tag, char* msg)
{
    return -1;
}
*/
static int __write_jank_kernel(struct my_work_struct  *pjanklog)
{
    struct iovec vec[5];

    mm_segment_t oldfs;
    int ret;

    if (unlikely(!pjanklog)) {
        hwlog_err("invalid arguments\n");
        return -1;
    }

    if (IS_ERR(filp)) {
        hwlog_err("file descriptor to %s is invalid: %ld\n", LOG_JANK_FS, PTR_ERR(filp));
        return -1;
    }

    // format: <priority:1><message:N>\0
    vec[0].iov_base = &pjanklog->nPrio;
    vec[0].iov_len  = 2;
    vec[1].iov_base = &pjanklog->ntagid;
    vec[1].iov_len  = 2;
    vec[2].iov_base = &pjanklog->uptime;
    vec[2].iov_len  = sizeof(pjanklog->uptime);
    vec[3].iov_base = &pjanklog->realtime;
    vec[3].iov_len  = sizeof(pjanklog->realtime);
    vec[4].iov_base = pjanklog->msg;
    vec[4].iov_len  = pjanklog->msglen;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_writev(filp, &vec[0], 5, &filp->f_pos);

    set_fs(oldfs);

    if (unlikely(ret < 0)) {
        hwlog_err("failed to write %s\n", LOG_JANK_FS);
    }
    return ret;
}

int log_to_jank(int tag, int prio, const char* fmt, ...)
{
    unsigned long           flags;
    va_list                 args;
    struct my_work_struct  *pWork = NULL;
    int                     len;
    struct timespec         upts, realts;
    u64                     uptime;
    u64                     realtime;

    do_posix_clock_monotonic_gettime(&upts);
    realts = upts;
    monotonic_to_bootbased(&realts);
    uptime = (u64)upts.tv_sec*1000 + upts.tv_nsec/1000000;
    realtime = (u64)realts.tv_sec*1000 + realts.tv_nsec/1000000;

    raw_spin_lock_irqsave(&janklog_spinlock, flags);
    if (!bInited)
    {
        hwlog_err("janklog_workqueue is null.\n");
        raw_spin_unlock_irqrestore(&janklog_spinlock, flags);
        return -1;
    }
    pWork = &janklog_work[nwork_index];
    if (0 == pWork->bWaiting)
    {
        pWork->bWaiting = 1;
        nwork_index++;
        if (nwork_index >= MAX_WORK_COUNT)
            nwork_index = 0;
    }
    else
    {
        pWork = NULL;
    }
    raw_spin_unlock_irqrestore(&janklog_spinlock, flags);

    if (NULL == pWork)
    {
        hwlog_err("janklog_workqueue is full, logd_to_jank failed.\n");
        return -1;
    }
    pWork->nPrio = prio;
    pWork->ntagid = tag;
    pWork->uptime = uptime;
    pWork->realtime = realtime;

    va_start(args, fmt);
    len = vscnprintf(pWork->msg, MAX_MSG_SIZE, fmt, args);
    va_end(args);
    pWork->msglen = len + 1;

    queue_work(janklog_workqueue, &(pWork->writelog));

    return 0;
}

EXPORT_SYMBOL(log_to_jank);

module_init(janklog_workqueue_init);
module_exit(janklog_workqueue_destory);
#endif

