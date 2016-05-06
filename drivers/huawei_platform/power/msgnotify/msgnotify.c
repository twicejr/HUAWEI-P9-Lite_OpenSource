/*
 * msgnotify.c
 *
 * calc android main looper thread runtime,and adjust cpu active_time according
 * to looper thread runtime
 *
 *  Copyright (C) 2014 Huawei Technologies Co., Ltd.
 */

#include <linux/sched.h>
#include <linux/time.h>
#include <linux/kernel_stat.h>

#define MSG_NOT_PROCESSING	0
#define MSG_PROCESSING	1

static uint g_msg_threshold = 0;
static uint g_max_msg_percent = 0;
#define DEBUG_PRINT_THRESHOLD 1
#define MAIN_LOOPER_THREAD_INIT_NAME "re-initialized>"

/*
 *calc android main looper thread runtime,and add it to cpustat
 *
 */
inline void update_msg_stat(int cpu, struct task_struct *p, struct task_struct *n)
{
	s64 now, sched_time, runtime;
	struct timespec now_timespec;
	now = 0;

	if (0 == g_msg_threshold) {
		return;
	}

	if (n->ms.main_looper_thread) {
		getnstimeofday(&(n->ms.sched_time));
		now = timespec_to_ns(&(n->ms.sched_time));
	}

	if (p->ms.main_looper_thread) {
		if (0 == now) {
			getnstimeofday(&now_timespec);
			now = timespec_to_ns(&now_timespec);
		}
		sched_time = timespec_to_ns(&(p->ms.sched_time));

		runtime = now - sched_time;
		if (runtime > 0 && sched_time != 0) {
			kcpustat_cpu(cpu).cpustat[CPUTIME_MESSAGE] += runtime;
			if (DEBUG_PRINT_THRESHOLD == g_msg_threshold) {
				printk("update_msg_stat,runtime:%lld us,"
					"cpu:%d,msg_time_stamp:%llu us,task:%s\n", div_s64(runtime, 1000),
					cpu, div_u64(kcpustat_cpu(cpu).cpustat[CPUTIME_MESSAGE], 1000), p->comm);
			}
		}

		p->ms.sched_time.tv_sec = 0;
		p->ms.sched_time.tv_nsec = 0;
	}
}

/*
 *return zoomed active_time according to msg_time
 *note:active_time and total_time,unit is us.
 *msg_time,uint is ns,is time used running looper thread
 */
u64 adjust_active_time_by_msg (int cpu, u64 active_time, u64 total_time, u64 msg_time) {
	u64 new_active_time = active_time;
	u64 max_msg_percent = 0;
	u64 tmp = 0;
	u64 cur_cpu_msg_percent = 0;
	int j;
	int max_percent_cpu = 0;

	if (DEBUG_PRINT_THRESHOLD == g_msg_threshold) {
		printk("adjust_active_time_by_msg,cpu:%d,active_time:%llu,total_time:%llu,"
			"msg_time:%llu us\n", cpu, active_time, total_time, div_u64(msg_time, 1000));
	}

	if (g_msg_threshold > 0 && active_time > 0 && total_time > 0) {
		/*to percent,translate msg_time(ns) to us,and calc the percent in total_time
		mean:msg_time = (msg_time*100/1000)/total_time */
		do_div(msg_time, 10);
		do_div(msg_time, total_time);

		kcpustat_cpu(cpu).cpustat[CPUTIME_MESSAGE_PERCENT] = msg_time;
		cur_cpu_msg_percent = msg_time;

		max_msg_percent = cur_cpu_msg_percent;
		for_each_online_cpu (j) {
			tmp = kcpustat_cpu(j).cpustat[CPUTIME_MESSAGE_PERCENT];
			if (tmp > max_msg_percent) {
				max_msg_percent = tmp;
				max_percent_cpu = j;
			}
		}

		if (max_msg_percent > 100) {
			max_msg_percent = 100;
		}
		g_max_msg_percent = max_msg_percent;

		if (max_msg_percent < g_msg_threshold) {
			//cut off active_time percent of (g_msg_threshold - msg_time)
			u64 cut_off = active_time * (g_msg_threshold - max_msg_percent);
			do_div(cut_off, 100);
			new_active_time -= cut_off;
		} else if (max_msg_percent > (100 - g_msg_threshold)) {
			//increase active_time percent of (msg_time - (100 - g_msg_threshold))
			u64 inc = active_time * (max_msg_percent - (100 - g_msg_threshold));
			do_div(inc, 100);
			new_active_time += inc;
			if (new_active_time > total_time) {
				new_active_time = total_time;
			}
		}

		if (DEBUG_PRINT_THRESHOLD == g_msg_threshold) {
			printk("max_msg_percent:%llu,the cpu:%d,cur_cpu_msg_percent:%llu,cpu:%d,"
				"new_active_percent:%llu,old:%llu\n",
				max_msg_percent, max_percent_cpu, cur_cpu_msg_percent, cpu,
				div_u64(new_active_time*100, total_time), div_u64(active_time*100, total_time));
		}
	}

	return new_active_time;
}

uint get_max_msg_percent(void)
{
	return g_max_msg_percent;
}

uint get_msg_threshold(void)
{
	return g_msg_threshold;
}

void set_msg_threshold(uint value)
{
	//now only use the lowest byte,others is reserved for future
	uint tmp = value & 0xff;
	if (tmp < 100) {
		g_msg_threshold = tmp;
	}
}

void set_main_looper_thread(struct task_struct *tsk, char *buf) {
	if ((tsk->pid == tsk->tgid) && !strcmp(buf, MAIN_LOOPER_THREAD_INIT_NAME))
		tsk->ms.main_looper_thread = true;
}
