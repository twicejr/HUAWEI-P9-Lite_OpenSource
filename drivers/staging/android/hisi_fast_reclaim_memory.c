/**
 * default
 * --w------- root   root  /sys/kernel/mm/fast_raclaim/flush_mulkiller
 * @uvevnt.rc chown /sys/kernel/mm/fast_raclaim/flush_mulkiller
 * echo "xxx" > /sys/kernel/mm/fast_raclaim/flush_mulkiller
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

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
#include <linux/freezer.h>
#include <linux/atomic.h>
#include <linux/kobject.h>

#define MULTIPLE_PREKILLER_DEPTH (20)
#define PER_PROCESS_TASK_SIZE    (60 << 20)
#define MIN_ADJ                  (529)
#define PAGE_CACHE_LEVL          (512 << 8)

static int debug_level = 1;

#define FAST_RECLAIM_ATTR(_name) \
	static struct kobj_attribute _name##_attr = __ATTR_WO(_name)


#define lowmem_print(level, x...)			\
	do {						\
		if (debug_level >= (level))	\
			pr_info(x);			\
	} while (0)


static int test_task_flag(struct task_struct *p, int flag)
{
	struct task_struct *t = p;

	do {
		task_lock(t);
		if (test_tsk_thread_flag(t, flag)) {
			task_unlock(t);
			return 1;
		}
		task_unlock(t);
	} while_each_thread(p, t);

	return 0;
}


static void dump_tasks(void)
{
	struct task_struct *p;
	struct task_struct *task;

	pr_info("[ pid ]   uid  tgid total_vm      rss nr_ptes swapents oom_score_adj name\n");
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

		pr_info("[%5d] %5d %5d %8lu %8lu %7lu %8lu         %5hd %s\n",
			task->pid, from_kuid(&init_user_ns, task_uid(task)),
			task->tgid, task->mm->total_vm, get_mm_rss(task->mm),
			task->mm->nr_ptes,
			get_mm_counter(task->mm, MM_SWAPENTS),
			task->signal->oom_score_adj, task->comm);
		task_unlock(task);
	}
	rcu_read_unlock();
}

static void dump_meminfo(void)
{
	show_mem(SHOW_MEM_FILTER_NODES);
	dump_tasks();
}

static int multiple_prekiller(int alloc_depth, long *reclaim_size)
{
	int i;
	int depth;
	long tasksize;
	long freed_size = 0;
	short min_score_adj = MIN_ADJ;
	int all_selected = 0;
	int max_selected_idx = 0;
	struct task_struct *tsk = NULL;

	struct task_struct *selected[MULTIPLE_PREKILLER_DEPTH] = {NULL,};
	int selected_tasksize[MULTIPLE_PREKILLER_DEPTH] = {0,};
	int selected_score_adj[MULTIPLE_PREKILLER_DEPTH] = {OOM_ADJUST_MAX,};

	depth = alloc_depth <= MULTIPLE_PREKILLER_DEPTH ? alloc_depth : MULTIPLE_PREKILLER_DEPTH;

	if (depth <= 0) {
		return 0;
	}
	/* init all select_xxx array */
	for (i = 0; i < depth; i++){
		selected_score_adj[i] = min_score_adj;
		selected_tasksize[i] = 0;
		selected[i] = NULL;
	}

	rcu_read_lock();
	for_each_process(tsk) {
		struct task_struct *p;
		int oom_score_adj;
		int is_exist_task = 0;

		if (tsk->flags & PF_KTHREAD)
			continue;

		/* may be select task already is killed */
		if (test_task_flag(tsk, TIF_MEMDIE))
			continue;

		p = find_lock_task_mm(tsk);
		if (!p)
			continue;

		oom_score_adj = p->signal->oom_score_adj;
		if (oom_score_adj < min_score_adj) {
			task_unlock(p);
			continue;
		}

		tasksize = get_mm_rss(p->mm);
		task_unlock(p);
		if (tasksize <= 0)
			continue;

		if (all_selected < depth) {
			for (i = 0; i < depth; i++) {
				if (!selected[i]) {
					is_exist_task = 1;
					max_selected_idx = i;
					break;
				}
			}
		} else if (selected_score_adj[max_selected_idx] < oom_score_adj ||
			(selected_score_adj[max_selected_idx] == oom_score_adj &&
			selected_tasksize[max_selected_idx] < tasksize)) {
			is_exist_task = 1;
		}

		if (is_exist_task) {
			selected[max_selected_idx] = p;
			selected_tasksize[max_selected_idx] = tasksize;
			selected_score_adj[max_selected_idx] = oom_score_adj;

			if (all_selected < depth) {
				all_selected++;
			}
			else if (all_selected == depth) {
				for (i = 0; i < depth; i++) {
					if (selected_score_adj[i] < selected_score_adj[max_selected_idx])
						max_selected_idx = i;
					else if (selected_score_adj[i] == selected_score_adj[max_selected_idx] &&
						selected_tasksize[i] < selected_tasksize[max_selected_idx])
						max_selected_idx = i;
				}
			}

			lowmem_print(2, "prekill: max_selected_idx(%d) select %d (%s), adj %d, \
					size %ld, to kill\n",
				max_selected_idx, p->pid, p->comm, oom_score_adj, (tasksize * PAGE_SIZE));
		}
	}
	for (i = 0; i < depth; i++) {
		if (selected[i]) {
			lowmem_print(1, "prekill: send sigkill to %d (%s), adj %d,\
				     size %d\n",
				     selected[i]->pid, selected[i]->comm,
				     selected_score_adj[i],
				     selected_tasksize[i] * PAGE_SIZE);
			send_sig(SIGKILL, selected[i], 0);
			set_tsk_thread_flag(selected[i], TIF_MEMDIE);

			freed_size += (selected_tasksize[i] * PAGE_SIZE);
		}
	}
	*reclaim_size = freed_size;
	rcu_read_unlock();

	return !(all_selected < depth);
}


static void fast_reclaim_memory(long size)
{
	int ret = 0;
	int free_page = 0;
	int file_page = 0;
	int anon_page = 0;
	int kill_depth = 0;
	long alloc_size = size;
	long need_size = 0;
	long reclaim_size = 0;
	unsigned long nr_reclaimed = 0;
	unsigned long nr_reclaiming = 0;

	free_page = global_page_state(NR_FREE_PAGES);
	if (alloc_size < free_page * PAGE_SIZE){
		return;
	}

	if (global_page_state(NR_SHMEM) + total_swapcache_pages() <
		global_page_state(NR_FILE_PAGES))
		file_page = global_page_state(NR_FILE_PAGES)
						- global_page_state(NR_SHMEM)
						- total_swapcache_pages();
	else
		file_page = 0;


	lowmem_print(1, "free memory %d page cache memory %d page\n", free_page, file_page);

	/**
	 * reclaim memory from page cache
	 *
	 */
	if (file_page - PAGE_CACHE_LEVL > 0){
		nr_reclaiming = file_page - PAGE_CACHE_LEVL;
		nr_reclaimed = shrink_all_memory(nr_reclaiming);
	}
	lowmem_print(1, "nr_reclaiming %lu page VS nr_reclaimed %lu page from page cache\n", nr_reclaiming, nr_reclaimed);

	/* calc per-zone free-memory file-cache anonimous-memory*/
	free_page = global_page_state(NR_FREE_PAGES);
	if (global_page_state(NR_SHMEM) + total_swapcache_pages() <
		global_page_state(NR_FILE_PAGES))
		file_page = global_page_state(NR_FILE_PAGES)
						- global_page_state(NR_SHMEM)
						- total_swapcache_pages();
	else
		file_page = 0;

	lowmem_print(1, "free memory %d page  cache memory %d page", free_page, file_page);

	need_size = (alloc_size - free_page * PAGE_SIZE);
	if (need_size < 0){
		lowmem_print(1, "prekill: need_size < 0\n");
		return;
	}

    anon_page = global_page_state(NR_ACTIVE_ANON) + global_page_state(NR_INACTIVE_ANON);
	if (need_size > anon_page * PAGE_SIZE){
		dump_meminfo();
		return;
	}

	/* according to the pressure and kill ? number processes */
	kill_depth = need_size/(PER_PROCESS_TASK_SIZE) + 1;
	lowmem_print(1, "kill_depth %ld\n", kill_depth);

	do {
		reclaim_size = 0;
		ret = multiple_prekiller(1, &reclaim_size);
		need_size -= reclaim_size;
		lowmem_print(2, "need_size %ld reclaim_size %ld kill_depth %d\n",  need_size, reclaim_size, kill_depth);
	}
	while (ret && need_size > 0 && kill_depth--);

}

static ssize_t flush_mulkiller_store(struct kobject *kobj,
				     struct kobj_attribute *attr,
				     const char *buf, size_t count)
{
	long size = simple_strtol(buf, NULL, 10);
	fast_reclaim_memory(size);

	return count;
}

FAST_RECLAIM_ATTR(flush_mulkiller);

static struct attribute *fast_raclaim_attrs[] = {
	&flush_mulkiller_attr.attr,
	NULL,
};

static struct attribute_group fast_raclaim_attr_group = {
	.attrs = fast_raclaim_attrs,
	.name = "fast_raclaim",
};

static int __init hisi_fast_reclaim_init(void)
{

	int err;
	err = sysfs_create_group(mm_kobj, &fast_raclaim_attr_group);
	if (err) {
		lowmem_print(2, "register sysfs failed\n");
	}

	return 0;
}
module_init(hisi_fast_reclaim_init);
