/*
 * include/linux/msgnotify.h
 *
 * Android messages notification header file
 *
 *  Copyright (C) 2014 Huawei Technologies Co., Ltd.
 */

#ifndef _MSGNOTIFY_H
#define _MSGNOTIFY_H

void msg_notify_start(void);
void msg_notify_end(void);
void proc_fork_msg_init(struct task_struct *p);
void update_msg_stat(int cpu, struct task_struct *p, struct task_struct *n);
uint get_msg_threshold(void);
void set_msg_threshold(uint value);
u64 adjust_active_time_by_msg (int cpu,u64 active_time,u64 total_time,u64 msg_time);
void set_main_looper_thread(struct task_struct *tsk, char *buf);
uint get_max_msg_percent(void);
#endif
