#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/oom.h>
#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/swap.h>
#include <linux/fs.h>
#include <linux/jiffies.h>
#include <linux/workqueue.h>
#include <linux/freezer.h>
#include <linux/ksm.h>
#include <linux/ion.h>
#include <linux/hisi/hisi_ion.h>

#define LMK_PRT_TSK_RSS 10000
#define LMK_DBG_SECONDS 3
/* service adj = (((oom_adj) * OOM_SCORE_ADJ_MAX) / -OOM_DISABLE) */
#define LMK_SERVICE_ADJ 294
static void dump_meminfo_wk(struct work_struct *work);
static unsigned long long before_jiffies;
#ifdef CONFIG_ION
static bool need_to_log_ion;
#endif
static DECLARE_WORK(lowmem_dbg_wk, dump_meminfo_wk);

static const char state_to_char[] = TASK_STATE_TO_CHAR_STR;

static int task_state_char(unsigned long state)
{
	int bit = state ? __ffs(state) + 1 : 0;

	return bit < sizeof(state_to_char) - 1 ? state_to_char[bit] : '?';
}

static void dump_tasks(void)
{
	struct task_struct *p;
	struct task_struct *task;
	short tsk_oom_adj = 0;

	pr_info("[ pid ] uid tgid total_vm rss nr_ptes swapents oom_score_adj s name\n");

	rcu_read_lock();
	for_each_process(p) {
		task = find_lock_task_mm(p);
		if (!task) {
			/*
			 * This is a kthread or all of p's threads have already
			 * detached their mm's.  There's no need to report
			 * them; they can't be oom killed anyway.
			 */
			continue;
		}

		tsk_oom_adj = task->signal->oom_score_adj;
		if (tsk_oom_adj && (tsk_oom_adj <= LMK_SERVICE_ADJ) &&
		    (get_mm_rss(task->mm) < LMK_PRT_TSK_RSS)) {
			task_unlock(task);
			continue;
		}

		pr_info("[%5d] %5d %5d %8lu %8lu %7lu %8lu %5hd %c %s%c\n",
			task->pid, from_kuid(&init_user_ns, task_uid(task)),
			task->tgid, task->mm->total_vm, get_mm_rss(task->mm),
			task->mm->nr_ptes,
			get_mm_counter(task->mm, MM_SWAPENTS),
			tsk_oom_adj,
			task_state_char(task->state),
			task->comm,
			frozen(task) ? '*' : ' ');
		task_unlock(task);
	}
	rcu_read_unlock();
}

static void dump_meminfo_wk(struct work_struct *work)
{
	before_jiffies = get_jiffies_64();
#ifdef CONFIG_ION
	hisi_ion_memory_info(need_to_log_ion);
	if (need_to_log_ion)
		need_to_log_ion = false;
#endif
	show_mem(SHOW_MEM_FILTER_NODES | SHOW_MEM_FILTER_PAGE_COUNT);
	dump_tasks();
	ksm_show_stats();
}

void lowmem_dbg(short adj)
{
	unsigned long long now_jiffies = get_jiffies_64();
#ifdef CONFIG_ION
	if (adj <= 0) {
		need_to_log_ion = true;
		before_jiffies = 0;
	}
#endif
	if (time_after64(now_jiffies,
			 (before_jiffies + LMK_DBG_SECONDS * HZ)))
		schedule_work(&lowmem_dbg_wk);
}
EXPORT_SYMBOL(lowmem_dbg);
