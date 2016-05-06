/*
 * blackbox. (kernel run data recorder.)
 *
 * Copyright (c) 2013 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/hardirq.h>
#include <linux/syscalls.h>
#include <linux/wakelock.h>
#include <linux/reboot.h>

#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/util.h>

#include "rdr_inner.h"
#include "rdr_field.h"
#include "rdr_print.h"
#include "rdr_debug.h"

static struct semaphore rdr_sem;
static LIST_HEAD(g_rdr_syserr_list);
static DEFINE_SPINLOCK(g_rdr_syserr_list_lock);
static struct wake_lock blackbox_wl;

void rdr_register_system_error(u32 modid, u32 arg1, u32 arg2)
{
	struct rdr_syserr_param_s *p = NULL;
	struct rdr_exception_info_s *p_exce_info = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	struct rdr_syserr_param_s *e_cur = NULL;
	int exist = 0;

	BB_PRINT_START();
	p = kmalloc(sizeof(struct rdr_syserr_param_s), GFP_ATOMIC);
	if (p == NULL) {
		BB_PRINT_PN("kmalloc rdr_syserr_param_s faild.\n");
		return;
	}

	p->modid = modid;
	p->arg1 = arg1;
	p->arg2 = arg2;

	p_exce_info = rdr_get_exception_info(modid);
	spin_lock(&g_rdr_syserr_list_lock);
	if (p_exce_info != NULL &&
	    p_exce_info->e_reentrant == RDR_REENTRANT_DISALLOW) {
		list_for_each_safe(cur, next, &g_rdr_syserr_list) {
			e_cur = list_entry(cur, struct rdr_syserr_param_s, syserr_list);
			if (e_cur->modid == p->modid) {
				exist = 1;
				BB_PRINT_DBG
				    ("exception:[0x%x] disallow reentrant.  return.\n",
				     modid);
				break;
			}
		}
	}
	if (exist == 0) {
		list_add_tail(&p->syserr_list, &g_rdr_syserr_list);
	} else if (exist == 1) {
		kfree(p);
	}
	spin_unlock(&g_rdr_syserr_list_lock);
	BB_PRINT_END();
}

void rdr_system_error(u32 modid, u32 arg1, u32 arg2)
{
	char *modid_str = NULL;
	BB_PRINT_START();
	if (in_atomic() || irqs_disabled() || in_irq()) {
		BB_PRINT_ERR("%s: in atomic or irqs disabled or in irq\n",
			     __func__);
	}
	modid_str = blackbox_get_modid_str(modid);
	BB_PRINT_ERR("%s: blackbox receive exception modid is [0x%x][%s]!\n",
		     __func__, modid, modid_str);
	show_stack(current, NULL);
	if (!rdr_init_done()) {
		BB_PRINT_ERR("rdr init faild!\n");
		BB_PRINT_END();
		return;
	}
	rdr_register_system_error(modid, arg1, arg2);
	up(&rdr_sem);
	BB_PRINT_END();
	return;
}

extern void record_exce_type(struct rdr_exception_info_s *einfo);
void rdr_syserr_process_for_ap(u32 modid, u64 arg1, u64 arg2)
{
	struct rdr_exception_info_s *p_exce_info = NULL;
	char date[DATATIME_MAXLEN];
	struct rdr_syserr_param_s p;
	BB_PRINT_START();

	p.modid = modid, p.arg1 = arg1, p.arg2 = arg2;
	preempt_disable();
	show_stack(current, NULL);

	rdr_field_baseinfo_reinit();
	rdr_save_args(modid, arg1, arg2);
	p_exce_info = rdr_get_exception_info(modid);
	if (p_exce_info == NULL) {
		/* rdr_save_history_log_for_undef_exception(&p); */
		BB_PRINT_ERR("get exception info faild.  return.\n");
		return;
	}
	record_exce_type(p_exce_info);
	memset(date, 0, DATATIME_MAXLEN);
	snprintf(date, DATATIME_MAXLEN, "%s-%08lld",
		 rdr_get_timestamp(), rdr_get_tick());
	/* rdr_save_history_log(p_exce_info, date); */

	rdr_fill_edata(p_exce_info, date);

	rdr_notify_module_dump(modid, p_exce_info, NULL);
	rdr_record_reboot_times2mem();
	rdr_notify_module_reset(modid, p_exce_info);

	preempt_enable();
	BB_PRINT_END();
	return;
}

void rdr_syserr_process(struct rdr_syserr_param_s *p)
{
	int reboot_times = 0;
	int i = 0;
	int max_reboot_times = rdr_get_reboot_times();
	int wait_dumplog_timeout = rdr_get_dumplog_timeout();
	int inter_ms = 500;
	u32 mod_id = p->modid;
	u32 mask = 0;
	u32 cur_mask = 0;
	struct rdr_exception_info_s *p_exce_info = NULL;
	char path[PATH_MAXLEN];
	char date[DATATIME_MAXLEN];

	BB_PRINT_START();

	wake_lock(&blackbox_wl);	/*make sure that the task can not be interrupted by suspend. */
	rdr_field_baseinfo_reinit();
	rdr_save_args(p->modid, p->arg1, p->arg2);
	p_exce_info = rdr_get_exception_info(mod_id);

	while (1) {
		if (rdr_get_suspend_state()) {
			BB_PRINT_DBG("%s: wait for suspend.\n", __func__);
			msleep(50);
		} else {
			break;
		}
	}

	if (p_exce_info == NULL) {
		rdr_save_history_log_for_undef_exception(p);
		wake_unlock(&blackbox_wl);
		BB_PRINT_ERR("get exception info faild.  return.\n");
		return;
	}

	/*如果此次异常需要复位全系统，则需要向pmu寄存器中记录复位原因，否则只写入history.log中 */
	if (p_exce_info->e_reset_core_mask & RDR_AP) {
		record_exce_type(p_exce_info);
	}

	BB_PRINT_DBG("start saving data.\n");
	rdr_set_saving_state(1);

	rdr_print_one_exc(p_exce_info);
	if (0 != p_exce_info->e_notify_core_mask) {
		if (0 != rdr_create_exception_path(p_exce_info, path, date)) {
			BB_PRINT_ERR("create exception path error.\n");
			goto out;
		}
	} else {		/*if no dump need(like modem-reboot), don't create exc-dir, but date is a must. */
		memset(date, 0, DATATIME_MAXLEN);
		snprintf(date, DATATIME_MAXLEN, "%s-%08lld",
			 rdr_get_timestamp(), rdr_get_tick());
	}
	rdr_fill_edata(p_exce_info, date);

	if (p_exce_info->e_exce_type != LPM3_S_EXCEPTION) {
		rdr_save_history_log(p_exce_info, date, true);
	}

	mask = rdr_notify_module_dump(mod_id, p_exce_info, path);

	BB_PRINT_DBG("rdr_notify_module_dump done. return mask=[0x%x]\n", mask);

	/* mask的值是根据p_exce_info->e_notify_core_mask获得的,
	 * 当mask为0时, 不走RDR框架导出LOG的流程. 确认人:刘海龙
	 */
	if (mask != 0) {
		while (wait_dumplog_timeout > 0) {
			cur_mask = rdr_get_dump_result(mod_id);
			if (mask != cur_mask) {
				BB_PRINT_DBG("%s: wait for dump .\n", __func__);
				msleep(inter_ms);
				wait_dumplog_timeout -= inter_ms;
				i++;
			} else {
				BB_PRINT_DBG
				    ("wait for dump done. use time:[%d], cur_maks[0x%x]\n",
				     i * inter_ms, cur_mask);
				break;
			}
			BB_PRINT_DBG
			    ("wait for dump done. current status:[0x%x]\n",
			     cur_mask);
		}
		if (wait_dumplog_timeout <= 0) {
			BB_PRINT_ERR
			    ("wait for dump status timeout... cur_mask[0x%x],"
			     "target_mask[0x%x]\n", cur_mask, mask);
		}
	}

	rdr_field_dumplog_done();

	if (0 != mask) {
		if (check_himntn(HIMNTN_GOBAL_RESETLOG)) {
			rdr_save_cur_baseinfo(path);

			/* 如果这次异常需要复位全系统，则表示log保存还未完成 */
			if (p_exce_info->e_reset_core_mask & RDR_AP) {
				/* 复位重启后还有一部分log需要保存 */
				bbox_save_done(path, BBOX_SAVE_STEP1);
			} else {
				if (!in_atomic() && !irqs_disabled()
				    && !in_irq()) {
					/* 确保之前的所有文件系统相关操作都能完成 */
					sys_sync();
				}
				/* 此异常目录下的所有log都保存完毕 */
				bbox_save_done(path, BBOX_SAVE_STEP_DONE);
			}
		}
	} else {
		BB_PRINT_DBG("Don't need to dump, current mask:[0x%x]\n", mask);
	}

	rdr_field_procexec_done();

out:
	rdr_set_saving_state(0);
	rdr_callback(p_exce_info, mod_id, path);
	BB_PRINT_DBG("saving data done.\n");
	rdr_count_size();
	BB_PRINT_DBG("rdr_count_size: done.\n");

	if (p_exce_info->e_upload_flag == RDR_UPLOAD_YES) {
/*
#include <linux/log_exception.h>
	char cmd[256] = {0};
	snprint(cmd,256,"archive -i %s -o rdr-%s-%s.zip -z zip",
		path, date, rdr_get_exception_core(p_exce_info->e_from_core));
	log_to_exception("rdr",cmd);
*/
		BB_PRINT_DBG("rdr_upload log: done.\n");
	}

	BB_PRINT_DBG("rdr_notify_module_reset: start.\n");
	/* check if the last reset was triggered by AP  */
	if (p_exce_info->e_reset_core_mask & RDR_AP) {
		rdr_record_reboot_times2mem();
		reboot_times = rdr_record_reboot_times2file();
		BB_PRINT_ERR("ap has reboot %d times.\n", reboot_times);
		if (max_reboot_times < reboot_times) {
			BB_PRINT_ERR("need reboot to erecovery.\n");

			/*write "erecovery_enter_reason=2015" to cache*/
			rdr_record_erecovery_reason();

			/*reset the file of reboot_times*/
			rdr_reset_reboot_times();

			kernel_restart("erecovery");
		}
	}
	rdr_notify_module_reset(mod_id, p_exce_info);
	BB_PRINT_DBG("rdr_notify_module_reset: done.\n");

	wake_unlock(&blackbox_wl);
	BB_PRINT_END();
	return;
}

bool rdr_syserr_list_empty(void)
{
	return list_empty(&g_rdr_syserr_list);
}

void rdr_syserr_list_print(void)
{
	struct list_head *cur = NULL;
	struct rdr_syserr_param_s *e_cur = NULL;
	struct list_head *next = NULL;
	struct rdr_exception_info_s *p_exce_info = NULL;

	BB_PRINT_DBG("============rdr_syserr_list_print start=============\n");
	BB_PRINT_DBG("empty? [%s]\n",
		rdr_syserr_list_empty() ? "true" : "false");
	spin_lock(&g_rdr_syserr_list_lock);
	list_for_each_safe(cur, next, &g_rdr_syserr_list) {
		e_cur = list_entry(cur, struct rdr_syserr_param_s, syserr_list);
		p_exce_info = rdr_get_exception_info(e_cur->modid);
		if (p_exce_info == NULL) {
			BB_PRINT_DBG("exception info is NULL.\n");
			continue;
		}
		rdr_print_one_exc(p_exce_info);
		p_exce_info = NULL;
	}
	spin_unlock(&g_rdr_syserr_list_lock);
	BB_PRINT_DBG("============rdr_syserr_list_print end=============\n");
}

static int rdr_main_thread_body(void *arg)
{
	struct list_head *cur = NULL;
	struct list_head *process = NULL;
	struct rdr_syserr_param_s *e_cur = NULL;
	struct rdr_syserr_param_s *e_process = NULL;
	struct list_head *next = NULL;
	u32 e_priority = RDR_PPRI_MAX;
	struct rdr_exception_info_s *p_exce_info = NULL;
	long jiffies = 0;

	BB_PRINT_START();

	while (!kthread_should_stop()) {
		jiffies = msecs_to_jiffies(1000);
		if (down_timeout(&rdr_sem, jiffies)) {
			if (rdr_syserr_list_empty())
				continue;
			/*return -1; */
		}
		BB_PRINT_DBG
		    ("============wait for fs ready start =============\n");
		while (rdr_wait_partition("/data/lost+found", 1000) != 0)
			;
		BB_PRINT_DBG
		    ("============wait for fs ready e n d =============\n");
		while (!rdr_syserr_list_empty()) {
			spin_lock(&g_rdr_syserr_list_lock);
			list_for_each_safe(cur, next, &g_rdr_syserr_list) {
				e_cur = list_entry(cur, struct rdr_syserr_param_s, syserr_list);
				p_exce_info = rdr_get_exception_info(e_cur->modid);
				if (p_exce_info == NULL) {
					if (process == NULL) {
						/* ??rdr_save_history_log_for_undef_exception(e_cur); */
						process = cur;
						e_process = e_cur;
					}
					continue;
				}
				if (p_exce_info->e_process_priority >= RDR_PPRI_MAX)
					BB_PRINT_DBG
					    ("invalid prio[%d], current modid [0x%x]\n",
					     p_exce_info->e_process_priority,
					     e_cur->modid);
				/* 查找链表中所有已接收异常中处理优先级最高的一个 */
				if (p_exce_info->e_process_priority < e_priority) {
					BB_PRINT_DBG
					    ("current prio[%d], current modid [0x%x]\n",
					     p_exce_info->e_process_priority,
					     e_cur->modid);
					process = cur;
					e_process = e_cur;
					e_priority = p_exce_info->e_process_priority;
				}
			}

			if (process == NULL || e_process == NULL) {
				BB_PRINT_DBG("exception: NULL\n");
				spin_unlock(&g_rdr_syserr_list_lock);
				continue;
			}

			list_del(process);
			spin_unlock(&g_rdr_syserr_list_lock);

			rdr_syserr_process(e_process);

			kfree(e_process);

			e_priority = RDR_PPRI_MAX;
			process = NULL;
			e_process = NULL;
		}
	}
	BB_PRINT_END();
	return 0;
}

static bool init_done;		/* default value is false */
bool rdr_init_done()
{
	BB_PRINT_START();
	if (init_done)
		return init_done;

	/*INIT_WORK(&regiser_work, rdr_register_work); */
	if (0 != rdr_common_early_init()) {
		BB_PRINT_ERR("rdr_common_early_init faild.\n");
		return init_done;
	}
	if (0 != rdr_common_init()) {
		BB_PRINT_ERR("rdr_common_init faild.\n");
		return init_done;
	}
	if (0 != rdr_field_init()) {
		BB_PRINT_ERR("rdr_field_init faild.\n");
		return init_done;
	}

	sema_init(&rdr_sem, 0);
	init_done = true;

	BB_PRINT_END();
	return init_done;
}

static s32 __init rdr_init(void)
{
	struct task_struct *rdr_main = NULL;
	struct task_struct *rdr_bootcheck = NULL;
	struct sched_param   param;

	BB_PRINT_START();
	if (!rdr_init_done()) {
		BB_PRINT_ERR("init environment faild.\n");
		return -1;
	}
	wake_lock_init(&blackbox_wl, WAKE_LOCK_SUSPEND, "blackbox");
	rdr_main = kthread_run(rdr_main_thread_body, NULL, "bbox_main");
	if (!rdr_main) {
		BB_PRINT_ERR("create thread rdr_main_thread faild.\n");
		wake_lock_destroy(&blackbox_wl);
		return -1;
	}

	param.sched_priority = BBOX_RT_PRIORITY;
	if (sched_setscheduler(rdr_main, SCHED_FIFO, &param)) {
		BB_PRINT_ERR("sched_setscheduler rdr_bootcheck_thread faild.\n");
		kthread_stop(rdr_main);
		wake_lock_destroy(&blackbox_wl);
		return -1;
	}
	rdr_bootcheck =
	    kthread_run(rdr_bootcheck_thread_body, NULL, "bbox_bootcheck");
	if (!rdr_bootcheck) {
		BB_PRINT_ERR("create thread rdr_bootcheck_thread faild.\n");
		kthread_stop(rdr_main);
		wake_lock_destroy(&blackbox_wl);
		return -1;
	}
	if (!kthread_run(rdr_dump_init, NULL, "bbox_dump_init")) {
		BB_PRINT_ERR("create thread rdr_dump_init faild.\n");
		kthread_stop(rdr_main);
		wake_lock_destroy(&blackbox_wl);
		return -1;
	}

	BB_PRINT_END();
	return 0;
}

static void __exit rdr_exit(void)
{
	rdr_dump_exit();
	return;
}

core_initcall(rdr_init);
module_exit(rdr_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("x00208050 <x00208050@notesmail.huawei.com>");
MODULE_DESCRIPTION("black box. kernel run data recorder");
