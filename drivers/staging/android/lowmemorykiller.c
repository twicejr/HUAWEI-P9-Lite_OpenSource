/* drivers/misc/lowmemorykiller.c
 *
 * The lowmemorykiller driver lets user-space specify a set of memory thresholds
 * where processes with a range of oom_score_adj values will get killed. Specify
 * the minimum oom_score_adj values in
 * /sys/module/lowmemorykiller/parameters/adj and the number of free pages in
 * /sys/module/lowmemorykiller/parameters/minfree. Both files take a comma
 * separated list of numbers in ascending order.
 *
 * For example, write "0,8" to /sys/module/lowmemorykiller/parameters/adj and
 * "1024,4096" to /sys/module/lowmemorykiller/parameters/minfree to kill
 * processes with a oom_score_adj value of 8 or higher when the free memory
 * drops below 4096 pages and kill processes with a oom_score_adj value of 0 or
 * higher when the free memory drops below 1024 pages.
 *
 * The driver considers memory used for caches to be free, but if a large
 * percentage of the cached memory is locked this can be very inaccurate
 * and processes may not get killed until the normal oom killer is triggered.
 *
 * Copyright (C) 2007-2008 Google, Inc.
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
#include <linux/swap.h>
#include <linux/fs.h>
#include <linux/freezer.h>
#include <linux/atomic.h>
#include <linux/ksm.h>

#define CREATE_TRACE_POINTS
#include "trace/lowmemorykiller.h"


#ifdef CONFIG_HIGHMEM
#define _ZONE ZONE_HIGHMEM
#else
#define _ZONE ZONE_NORMAL
#endif
#ifdef CONFIG_HUAWEI_KSTATE
#include <linux/hw_kcollect.h>
#endif
#ifdef CONFIG_HISI_LOWMEM_DBG
extern ssize_t write_log_to_exception(const char* category, char level, const char* msg);
#endif
static uint32_t lowmem_debug_level = 1;
static short lowmem_adj[6] = {
	0,
	1,
	6,
	12,
};
static int lowmem_adj_size = 4;
static int lowmem_minfree[6] = {
	3 * 512,	/* 6MB */
	2 * 1024,	/* 8MB */
	4 * 1024,	/* 16MB */
	16 * 1024,	/* 64MB */
};
static int lowmem_minfree_size = 4;
static int lmk_fast_run = 1;

static ulong lowmem_kill_count;
static ulong lowmem_free_mem;

static unsigned long lowmem_deathpending_timeout;

#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
//adj add 1, so score_adj should add 59
#define SCORE_ADJ_UNIT         59
#define SERVICE_APPS_COUNT     5
#define CACHED_APPS_COUNT      20
#define CACHED_APP_MIN_ADJ     529
#define PERCEPTIBLE_APP_ADJ    117
//MEMSIZE_2G  2 * 1024 * 1024 * 1024UL/ PAGE_SIZE
#define MEMSIZE_2G    (1024 * 512)
#endif

#define lowmem_print(level, x...)			\
	do {						\
		if (lowmem_debug_level >= (level))	\
			pr_info(x);			\
	} while (0)

int can_use_cma_pages(gfp_t gfp_mask)
{
	int can_use = 0;
	int mtype = allocflags_to_migratetype(gfp_mask);
	int i = 0;
	int *mtype_fallbacks = get_migratetype_fallbacks(mtype);

	if (is_migrate_cma(mtype)) {
		can_use = 1;
	} else {
		for (i = 0;; i++) {
			int fallbacktype = mtype_fallbacks[i];

			if (is_migrate_cma(fallbacktype)) {
				can_use = 1;
				break;
			}

			if (fallbacktype == MIGRATE_RESERVE)
				break;
		}
	}
	return can_use;
}
void tune_lmk_zone_param(struct zonelist *zonelist, int classzone_idx,
					int *other_free, int *other_file,
					int use_cma_pages)
{
	struct zone *zone;
	struct zoneref *zoneref;
	int zone_idx;

	for_each_zone_zonelist(zone, zoneref, zonelist, MAX_NR_ZONES) {
		zone_idx = zonelist_zone_idx(zoneref);
		if (zone_idx == ZONE_MOVABLE) {
			if (!use_cma_pages)
				*other_free -=
				    zone_page_state(zone, NR_FREE_CMA_PAGES);
			continue;
		}

		if (zone_idx > classzone_idx) {
			if (other_free != NULL)
				*other_free -= zone_page_state(zone,
							       NR_FREE_PAGES);
			if (other_file != NULL)
				*other_file -= zone_page_state(zone,
							       NR_FILE_PAGES)
					      - zone_page_state(zone, NR_SHMEM)
					      - zone_page_state(zone, NR_SWAPCACHE);
		} else if (zone_idx < classzone_idx) {
			if (other_free != NULL) {
				if (zone_watermark_ok(zone, 0, 0, classzone_idx, 0)) {
					if (!use_cma_pages) {
						*other_free -= min(
						  zone->lowmem_reserve[classzone_idx] +
						  zone_page_state(
						    zone, NR_FREE_CMA_PAGES),
						  zone_page_state(
						    zone, NR_FREE_PAGES));
					} else {
						*other_free -=
						  zone->lowmem_reserve[classzone_idx];
					}
				} else {
					*other_free -=
						   zone_page_state(zone, NR_FREE_PAGES);
				}
			}
		}
	}
}
#ifdef CONFIG_HIGHMEM
void adjust_gfp_mask(gfp_t *gfp_mask)
{
	struct zone *preferred_zone;
	struct zonelist *zonelist;
	enum zone_type high_zoneidx;

	if (current_is_kswapd()) {
		zonelist = node_zonelist(0, *gfp_mask);
		high_zoneidx = gfp_zone(*gfp_mask);
		first_zones_zonelist(zonelist, high_zoneidx, NULL,
				&preferred_zone);

		if (high_zoneidx == ZONE_NORMAL) {
			if (zone_watermark_ok_safe(preferred_zone, 0,
					high_wmark_pages(preferred_zone), 0,
					0))
				*gfp_mask |= __GFP_HIGHMEM;
		} else if (high_zoneidx == ZONE_HIGHMEM) {
			*gfp_mask |= __GFP_HIGHMEM;
		}
	}
}
#else
void adjust_gfp_mask(gfp_t *unused)
{
}
#endif
void tune_lmk_param(int *other_free, int *other_file, struct shrink_control *sc)
{
	gfp_t gfp_mask;
	struct zone *preferred_zone;
	struct zonelist *zonelist;
	enum zone_type high_zoneidx, classzone_idx;
	unsigned long balance_gap;
	int use_cma_pages;

	gfp_mask = sc->gfp_mask;
	adjust_gfp_mask(&gfp_mask);

	zonelist = node_zonelist(0, gfp_mask);
	high_zoneidx = gfp_zone(gfp_mask);
	first_zones_zonelist(zonelist, high_zoneidx, NULL, &preferred_zone);
	classzone_idx = zone_idx(preferred_zone);
	use_cma_pages = can_use_cma_pages(gfp_mask);

	balance_gap = min(low_wmark_pages(preferred_zone),
			  (preferred_zone->present_pages +
			   KSWAPD_ZONE_BALANCE_GAP_RATIO-1) /
			   KSWAPD_ZONE_BALANCE_GAP_RATIO);

	if (likely(current_is_kswapd() && zone_watermark_ok(preferred_zone, 0,
			  high_wmark_pages(preferred_zone) + SWAP_CLUSTER_MAX +
			  balance_gap, 0, 0))) {
		if (lmk_fast_run)
			tune_lmk_zone_param(zonelist, classzone_idx, other_free,
				       other_file, use_cma_pages);
		else
			tune_lmk_zone_param(zonelist, classzone_idx, other_free,
				       NULL, use_cma_pages);

		if (zone_watermark_ok(preferred_zone, 0, 0, _ZONE, 0)) {
			if (!use_cma_pages) {
				*other_free -= min(
				  preferred_zone->lowmem_reserve[_ZONE]
				  + zone_page_state(
				    preferred_zone, NR_FREE_CMA_PAGES),
				  zone_page_state(
				    preferred_zone, NR_FREE_PAGES));
			} else {
				*other_free -=
				  preferred_zone->lowmem_reserve[_ZONE];
			}
		} else {
			*other_free -= zone_page_state(preferred_zone,
						      NR_FREE_PAGES);
		}

		lowmem_print(4, "lowmem_shrink of kswapd tunning for highmem "
			     "ofree %d, %d\n", *other_free, *other_file);
	} else {
		tune_lmk_zone_param(zonelist, classzone_idx, other_free,
			       other_file, use_cma_pages);

		if (!use_cma_pages) {
			*other_free -=
			  zone_page_state(preferred_zone, NR_FREE_CMA_PAGES);
		}

		lowmem_print(4, "lowmem_shrink tunning for others ofree %d, "
			     "%d\n", *other_free, *other_file);
	}
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
	ksm_show_stats();
}

#ifdef CONFIG_HISI_LOWMEM_DBG
extern void lowmem_dbg(short adj);
#endif

static void dump_threads(struct task_struct *tsk)
{
	struct task_struct *t;

	for_each_thread(tsk, t) {
		lowmem_print(1,
			     "pid=%d tgid=%d %s mm=%d frozen=%d 0x%lx 0x%x\n",
			     t->pid, t->tgid, t->comm, t->mm ? 1 : 0,
			     frozen(t), t->state, t->flags);
	}
}

#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
static int multiple_process_kill(struct task_struct *ptr[], int ptr_size)
{
    int i = 0;
	int tasksize = 0;
	int free_size = 0;

	for (i = 0; i < ptr_size; i++) {
	    if (ptr[i] == NULL)
		    break;

		if (test_tsk_thread_flag(ptr[i], TIF_MEMDIE))
			continue;

		task_lock(ptr[i]);
		if (ptr[i]->mm) {
			lowmem_print(1, "multiple apps killing '%s' (%d), tgid=%d  adj = %d\n",
			   ptr[i]->comm, ptr[i]->pid, ptr[i]->tgid, ptr[i]->signal->oom_score_adj);
			tasksize = get_mm_rss(ptr[i]->mm);
			free_size += tasksize;
			send_sig(SIGKILL, ptr[i], 0);
			set_tsk_thread_flag(ptr[i], TIF_MEMDIE);
			__thaw_task(ptr[i]);
			set_user_nice(ptr[i], -10);
		}
		task_unlock(ptr[i]);
	}

	return free_size;
}
#endif
static int lowmem_shrink(struct shrinker *s, struct shrink_control *sc)
{
	struct task_struct *tsk;
	struct task_struct *selected = NULL;
	int rem = 0;
	int tasksize;
	int i;
	short min_score_adj = OOM_SCORE_ADJ_MAX + 1;
	int minfree = 0;
	int selected_tasksize = 0;
	short selected_oom_score_adj;
	int array_size = ARRAY_SIZE(lowmem_adj);
	int other_free;
	int other_file;
	unsigned long nr_to_scan = sc->nr_to_scan;
	static atomic_t atomic_lmk = ATOMIC_INIT(0);
#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
	struct task_struct *cached_apps[CACHED_APPS_COUNT];
	struct task_struct *cached_min_apps[SERVICE_APPS_COUNT];
	struct task_struct *service_apps[SERVICE_APPS_COUNT];
	int j = 0;
	int m = 0;
	int n = 0;
	int k = 0;
	int cached_mem = 0;
	int service_mem = 0;
	bool total_mem_2G = false;
#endif

	other_free = global_page_state(NR_FREE_PAGES);

	if (global_page_state(NR_SHMEM) + total_swapcache_pages() <
		global_page_state(NR_FILE_PAGES))
		other_file = global_page_state(NR_FILE_PAGES) -
						global_page_state(NR_SHMEM) -
						total_swapcache_pages();
	else
		other_file = 0;

	tune_lmk_param(&other_free, &other_file, sc);

	if (lowmem_adj_size < array_size)
		array_size = lowmem_adj_size;
	if (lowmem_minfree_size < array_size)
		array_size = lowmem_minfree_size;
	for (i = 0; i < array_size; i++) {
		minfree = lowmem_minfree[i];
		if (other_free < minfree && other_file < minfree) {
			min_score_adj = lowmem_adj[i];
			break;
		}
	}
	if (nr_to_scan > 0)
		lowmem_print(3, "lowmem_shrink %lu, %x, ofree %d %d, ma %hd\n",
				nr_to_scan, sc->gfp_mask, other_free,
				other_file, min_score_adj);
	rem = global_page_state(NR_ACTIVE_ANON) +
		global_page_state(NR_ACTIVE_FILE) +
		global_page_state(NR_INACTIVE_ANON) +
		global_page_state(NR_INACTIVE_FILE);
	if (nr_to_scan <= 0 || min_score_adj == OOM_SCORE_ADJ_MAX + 1) {
		lowmem_print(5, "lowmem_shrink %lu, %x, return %d\n",
			     nr_to_scan, sc->gfp_mask, rem);

		return rem;
	}
	selected_oom_score_adj = min_score_adj;

	if (atomic_inc_return(&atomic_lmk) > 1) {
		atomic_dec(&atomic_lmk);
		return 0;
	}

#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
	if (totalram_pages <= MEMSIZE_2G) {
		lowmem_print(3,"the mem total is = 0x%x, 2G MEM!\n", totalram_pages);
		total_mem_2G = true;
		for (j = 0; j < CACHED_APPS_COUNT; j++) {
			cached_apps[j] = NULL;
		}
		j = 0;

		for (k = 0; k < SERVICE_APPS_COUNT; k++) {
			service_apps[k] = NULL;
			cached_min_apps[k] = NULL;
		}
		k = 0;
	}

#endif
	rcu_read_lock();
	for_each_process(tsk) {
		struct task_struct *p;
		short oom_score_adj;

		if (tsk->flags & PF_KTHREAD)
			continue;

		p = find_lock_task_mm(tsk);
		if (!p)
			continue;
#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
		oom_score_adj = p->signal->oom_score_adj;
#endif

		if (test_tsk_thread_flag(p, TIF_MEMDIE)) {
			if (time_before_eq(jiffies,
					   lowmem_deathpending_timeout)) {
				task_unlock(p);
				rcu_read_unlock();
				atomic_dec(&atomic_lmk);
				return 0;
			} else {
				lowmem_print(1, "timeout '%s' (%d)\n",
					     p->comm, p->pid);
				dump_threads(tsk);
				show_stack(p, NULL);
#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
				oom_score_adj -= SCORE_ADJ_UNIT;
#endif
			}
		}

#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
		if (total_mem_2G) {
			if ((oom_score_adj > CACHED_APP_MIN_ADJ) && (j < CACHED_APPS_COUNT))
				cached_apps[j++] = p;
			if (min_score_adj == CACHED_APP_MIN_ADJ) {
				if (oom_score_adj == CACHED_APP_MIN_ADJ)
					cached_apps[j++] = p;
				else if ((oom_score_adj < min_score_adj) && (k < SERVICE_APPS_COUNT) &&
				   ((oom_score_adj + SCORE_ADJ_UNIT) >= min_score_adj))
					service_apps[k++] = p;
			}
		}
#endif

#ifndef CONFIG_HUAWEI_CACHED_APPS_KILL
		oom_score_adj = p->signal->oom_score_adj;
#endif
		if (oom_score_adj < min_score_adj) {
			task_unlock(p);
			continue;
		}
		tasksize = get_mm_rss(p->mm);
#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
        tasksize = get_mm_rss(p->mm) +
                p->mm->nr_ptes +
                get_mm_counter(p->mm, MM_SWAPENTS);
#endif
		task_unlock(p);
		if (tasksize <= 0)
			continue;
		if (selected) {
#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
			if ((total_mem_2G) && (oom_score_adj <= CACHED_APP_MIN_ADJ) &&
				(oom_score_adj > PERCEPTIBLE_APP_ADJ)) {
				if ((oom_score_adj == selected_oom_score_adj) && (m < SERVICE_APPS_COUNT)) {
					if (tasksize > selected_tasksize) {
						cached_min_apps[m++] = selected;
						lowmem_print(2, " '%s' (%d), adj %hd, size %d, to cached min\n",
							 selected->comm, selected->pid, oom_score_adj, selected_tasksize);
					} else {
						cached_min_apps[m++] = p;
						lowmem_print(2, " '%s' (%d), adj %hd, size %d, to cached min\n",
							 p->comm, p->pid, oom_score_adj, tasksize);
					}
				} else if ((oom_score_adj < selected_oom_score_adj) && (n < SERVICE_APPS_COUNT) &&
						   ((oom_score_adj + SCORE_ADJ_UNIT) >= selected_oom_score_adj )){
					service_apps[n++] = p;
					lowmem_print(2, " '%s' (%d), adj %hd, size %d, to services\n",
					p->comm, p->pid, oom_score_adj, tasksize);
				}
			}
#endif

			if (oom_score_adj < selected_oom_score_adj)
				continue;
			if (oom_score_adj == selected_oom_score_adj &&
			    tasksize <= selected_tasksize)
				continue;
#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
			if ((total_mem_2G) && (oom_score_adj > selected_oom_score_adj) &&
               (oom_score_adj <= CACHED_APP_MIN_ADJ)) {
				n = m;
				for (m = 0; m < SERVICE_APPS_COUNT; m++) {
					service_apps[m] = cached_min_apps[m];
					cached_min_apps[m] = NULL;
				}
				m = 0;

				if (oom_score_adj <= (selected_oom_score_adj + SCORE_ADJ_UNIT))
					service_apps[n++] = selected;

				lowmem_print(1, "cached_min_apps clean\n");
			}
#endif
		}
		selected = p;
		selected_tasksize = tasksize;
		selected_oom_score_adj = oom_score_adj;
		lowmem_print(2, "select '%s' (%d), adj %hd, size %d, to kill\n",
			     p->comm, p->pid, oom_score_adj, tasksize);
	}
	if (selected) {
		long cache_size = other_file * (long)(PAGE_SIZE / 1024);
		long cache_limit = minfree * (long)(PAGE_SIZE / 1024);
		long free = other_free * (long)(PAGE_SIZE / 1024);
		trace_lowmemory_kill(selected, cache_size, cache_limit, free);
		lowmem_print(1, "Killing '%s' (%d), tgid=%d, adj %hd,\n" \
				"   to free %ldkB on behalf of '%s' (%d) because\n" \
				"   cache %ldkB is below limit %ldkB for oom_score_adj %hd\n" \
				"   Free memory is %ldkB above reserved\n",
			     selected->comm, selected->pid, selected->tgid,
			     selected_oom_score_adj,
			     selected_tasksize * (long)(PAGE_SIZE / 1024),
			     current->comm, current->pid,
			     other_file * (long)(PAGE_SIZE / 1024),
			     minfree * (long)(PAGE_SIZE / 1024),
			     min_score_adj,
			     other_free * (long)(PAGE_SIZE / 1024));

		if (selected_oom_score_adj == 0)
			dump_meminfo();

		lowmem_kill_count++;
		lowmem_free_mem += selected_tasksize * (long)(PAGE_SIZE / 1024) / 1024;

#ifdef CONFIG_HUAWEI_KSTATE
		hwkillinfo(selected->tgid, 0); /* 0 stand for low memory kill */
#endif
#ifdef CONFIG_HISI_LOWMEM_DBG
		lowmem_dbg(selected_oom_score_adj);
#endif

		task_lock(selected);
		send_sig(SIGKILL, selected, 0);
		if (selected->mm) {
			set_tsk_thread_flag(selected, TIF_MEMDIE);
			__thaw_task(selected);
		}
		task_unlock(selected);

		lowmem_deathpending_timeout = jiffies + HZ;
		rem -= selected_tasksize;

#ifdef CONFIG_HUAWEI_CACHED_APPS_KILL
		if (total_mem_2G) {
			lowmem_print(1, "cached apps killed!\n");
			cached_mem = multiple_process_kill(cached_apps, CACHED_APPS_COUNT);

			if (j < SERVICE_APPS_COUNT) {
				lowmem_print(1, "cached min apps killed!\n");
				cached_mem += multiple_process_kill(cached_min_apps, SERVICE_APPS_COUNT);
			}
			lowmem_print(1, "cached_mem = %ldkB\n", cached_mem * (long)(PAGE_SIZE / 1024));

			if ((m < SERVICE_APPS_COUNT) && (selected_oom_score_adj <= CACHED_APP_MIN_ADJ)) {
				lowmem_print(1, "service apps killed!\n");
				service_mem = multiple_process_kill(service_apps, SERVICE_APPS_COUNT - m);
				lowmem_print(1, "service_mem = %ldkB\n", service_mem * (long)(PAGE_SIZE / 1024));
			}
		}
#endif

#ifdef CONFIG_HISI_LOWMEM_DBG
		if (selected_oom_score_adj == 0)
			write_log_to_exception("LMK-EXCEPTION", 'C', "lower memory killer exception");
#endif
	}

	lowmem_print(4, "lowmem_shrink %lu, %x, return %d\n",
		     nr_to_scan, sc->gfp_mask, rem);
	rcu_read_unlock();
	atomic_dec(&atomic_lmk);
	return rem;
}

static struct shrinker lowmem_shrinker = {
	.shrink = lowmem_shrink,
	.seeks = DEFAULT_SEEKS * 16
};

static int __init lowmem_init(void)
{
	register_shrinker(&lowmem_shrinker);
	return 0;
}

static void __exit lowmem_exit(void)
{
	unregister_shrinker(&lowmem_shrinker);
}

#ifdef CONFIG_ANDROID_LOW_MEMORY_KILLER_AUTODETECT_OOM_ADJ_VALUES
static short lowmem_oom_adj_to_oom_score_adj(short oom_adj)
{
	if (oom_adj == OOM_ADJUST_MAX)
		return OOM_SCORE_ADJ_MAX;
	else
		return (oom_adj * OOM_SCORE_ADJ_MAX) / -OOM_DISABLE;
}

static void lowmem_autodetect_oom_adj_values(void)
{
	int i;
	short oom_adj;
	short oom_score_adj;
	int array_size = ARRAY_SIZE(lowmem_adj);

	if (lowmem_adj_size < array_size)
		array_size = lowmem_adj_size;

	if (array_size <= 0)
		return;

	oom_adj = lowmem_adj[array_size - 1];
	if (oom_adj > OOM_ADJUST_MAX)
		return;

	oom_score_adj = lowmem_oom_adj_to_oom_score_adj(oom_adj);
	if (oom_score_adj <= OOM_ADJUST_MAX)
		return;

	lowmem_print(1, "lowmem_shrink: convert oom_adj to oom_score_adj:\n");
	for (i = 0; i < array_size; i++) {
		oom_adj = lowmem_adj[i];
		oom_score_adj = lowmem_oom_adj_to_oom_score_adj(oom_adj);
		lowmem_adj[i] = oom_score_adj;
		lowmem_print(1, "oom_adj %d => oom_score_adj %d\n",
			     oom_adj, oom_score_adj);
		lowmem_print(2, "oom_score_adj %d => min memory %d\n",
			     oom_score_adj, lowmem_minfree[i]);
	}
}

static int lowmem_adj_array_set(const char *val, const struct kernel_param *kp)
{
	int ret;

	ret = param_array_ops.set(val, kp);

	/* HACK: Autodetect oom_adj values in lowmem_adj array */
	lowmem_autodetect_oom_adj_values();

	return ret;
}

static int lowmem_adj_array_get(char *buffer, const struct kernel_param *kp)
{
	return param_array_ops.get(buffer, kp);
}

static void lowmem_adj_array_free(void *arg)
{
	param_array_ops.free(arg);
}

static struct kernel_param_ops lowmem_adj_array_ops = {
	.set = lowmem_adj_array_set,
	.get = lowmem_adj_array_get,
	.free = lowmem_adj_array_free,
};

static const struct kparam_array __param_arr_adj = {
	.max = ARRAY_SIZE(lowmem_adj),
	.num = &lowmem_adj_size,
	.ops = &param_ops_short,
	.elemsize = sizeof(lowmem_adj[0]),
	.elem = lowmem_adj,
};
#endif

module_param_named(cost, lowmem_shrinker.seeks, int, S_IRUGO | S_IWUSR);
#ifdef CONFIG_ANDROID_LOW_MEMORY_KILLER_AUTODETECT_OOM_ADJ_VALUES
__module_param_call(MODULE_PARAM_PREFIX, adj,
		    &lowmem_adj_array_ops,
		    .arr = &__param_arr_adj,
		    S_IRUGO | S_IWUSR, -1);
__MODULE_PARM_TYPE(adj, "array of short");
#else
module_param_array_named(adj, lowmem_adj, short, &lowmem_adj_size,
			 S_IRUGO | S_IWUSR);
#endif
module_param_array_named(minfree, lowmem_minfree, uint, &lowmem_minfree_size,
			 S_IRUGO | S_IWUSR);
module_param_named(debug_level, lowmem_debug_level, uint, S_IRUGO | S_IWUSR);
module_param_named(lmk_fast_run, lmk_fast_run, int, S_IRUGO | S_IWUSR);
module_param_named(kill_count, lowmem_kill_count, ulong, S_IRUGO | S_IWUSR);
module_param_named(free_mem, lowmem_free_mem, ulong, S_IRUGO | S_IWUSR);

module_init(lowmem_init);
module_exit(lowmem_exit);

MODULE_LICENSE("GPL");

