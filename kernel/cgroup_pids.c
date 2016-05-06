/*
 * Process number limiting controller for cgroups.
 *
 * Used to allow a cgroup hierarchy to stop any new processes
 * from fork()ing after a certain limit is reached.
 *
 * Since it is trivial to hit the task limit without hitting
 * any kmemcg limits in place, PIDs are a fundamental resource.
 * As such, PID exhaustion must be preventable in the scope of
 * a cgroup hierarchy by allowing resource limiting of the
 * number of tasks in a cgroup.
 *
 * In order to use the `pids` controller, set the maximum number
 * of tasks in pids.max (this is not available in the root cgroup
 * for obvious reasons). The number of processes currently
 * in the cgroup is given by pids.current. Organisational operations
 * are not blocked by cgroup policies, so it is possible to have
 * pids.current > pids.max. However, fork()s will still not work.
 *
 * To set a cgroup to have no limit, set pids.max to "max". fork()
 * will return -EBUSY if forking would cause a cgroup policy to be
 * violated.
 *
 * pids.current tracks all child cgroup hierarchies, so
 * parent/pids.current is a superset of parent/child/pids.current.
 *
 * Copyright (C) 2015 Aleksa Sarai <cyphar@cyphar.com>
 *
 */

#include <linux/kernel.h>
#include <linux/threads.h>
#include <linux/atomic.h>
#include <linux/cgroup.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/seq_file.h>
#include <linux/sched.h>
#include <linux/eventfd.h>
#include <linux/poll.h>

#define PIDS_MAX (PID_MAX_LIMIT + 1ULL)

struct cgroup_subsys pids_subsys;
struct pids_cgroup {
	struct cgroup_subsys_state	css;

	/*
	 * Use 64-bit types so that we can safely represent "max" as
	 * (PID_MAX_LIMIT + 1).
	 */
	atomic64_t			counter;
	int64_t				limit;
	
	//each group_pids is default limit
	int64_t				group_soft_limit;
	int64_t				group_limit;
#ifdef CONFIG_CGROUP_PIDS_NOTIFY_USER
	/* The list of pid_event structs. */
	struct list_head events;
	/* Have to grab the lock on events traversal or modifications. */
	spinlock_t event_list_lock;
#endif
	struct list_head		group_pids_list;

	int64_t				token;
};

static struct pids_cgroup *css_pids(struct cgroup *cgrp)
{
	return container_of(cgroup_subsys_state(cgrp, pids_subsys_id),
			    struct pids_cgroup, css);
}

static struct pids_cgroup *task_pids(struct task_struct *task)
{
	return container_of(task_subsys_state(task, pids_subsys_id),
			    struct pids_cgroup, css);
}

static struct pids_cgroup *parent_pids(struct pids_cgroup *pids)
{
	struct cgroup *cgrp = pids->css.cgroup->parent;

	if (cgrp)
		return css_pids(cgrp);
	return NULL;
}
struct group_pids {
	/* All the tasks in the same QoS group are in this list */
	struct list_head	head;
	/* Linked to the global group_pids_list */
	struct list_head	node;
	int64_t				soft_limit;
	int64_t				limit;

	atomic64_t	counter;
	int64_t		token;
#ifdef CONFIG_CGROUP_PIDS_NOTIFY_USER
	/*true: has signal to user space, at default, it is false, no */
	bool	signal;
#endif
	
};

#ifdef CONFIG_CGROUP_PIDS_NOTIFY_USER
static void pids_event(struct pids_cgroup *pids, struct group_pids *gp);
#else
#define pids_event(...)
#endif
static DEFINE_SPINLOCK(group_pids_lock);

static int group_pids_try_charge(struct group_pids *gp, int num)
{
	int64_t new;
	int ret;

	if (!gp)
		return 0;

	new = atomic64_add_return(num, &gp->counter);
	if (new > gp->limit) {
		ret = atomic64_add_negative(-num, &gp->counter);
		return -ENOMEM;
	}
	if (new > gp->soft_limit) {
		/*send a pid over soft limit event to user space*/
		return EDQUOT;
	}
	return 0;
}

static void group_pids_uncharge(struct group_pids *gp, int num)
{
	if (!gp)
		return;
	WARN_ON_ONCE(atomic64_add_negative(-num, &gp->counter));
}

static void group_pids_migrate(struct task_struct *tsk, struct group_pids *gp)
{
	struct group_pids *old_gp = tsk->group_pids;

	if (old_gp) {
		list_del(&tsk->group_pids_list);
		atomic64_dec(&old_gp->counter);

		if (list_empty(&old_gp->head)) {
			list_del(&old_gp->node);
			kfree(old_gp);
		}
	}

	list_add_tail(&tsk->group_pids_list, &gp->head);
	atomic64_inc(&gp->counter);
	tsk->group_pids = gp;
}

static int group_pids_max_show(struct cgroup *cgrp, struct cftype *cft,
			       struct seq_file *m)
{
	struct pids_cgroup *pids = css_pids(cgrp);
	struct group_pids *gp;
	struct task_struct *task;

	spin_lock(&group_pids_lock);

	list_for_each_entry(gp, &pids->group_pids_list, node) {
		WARN_ON(list_empty(&gp->head));

		task = list_first_entry(&gp->head, struct task_struct,
					group_pids_list);
		seq_printf(m, "%llu %lu %llu %llu %llu\n",
			   (long long)gp->token,
			   (long)task_tgid_vnr(task),
			   (long long)gp->soft_limit,
			   (long long)gp->limit,
			   (long long)atomic64_read(&gp->counter));
	}

	spin_unlock(&group_pids_lock);
	return 0;
}

static int group_pids_limit_show(struct cgroup *cgrp, struct cftype *cft,
			       struct seq_file *m)
{
	struct pids_cgroup *pids = css_pids(cgrp);
	seq_printf(m, "%llu,%llu\n",
			   (long long)pids->group_soft_limit,
			   (long long)pids->group_limit);
	return 0;
}

static int group_pids_limit_write(struct cgroup *cgrp, struct cftype *cft,
				const char *buffer)
{
	struct pids_cgroup *pids = css_pids(cgrp);
	struct group_pids *gp;
	int64_t soft_limit, max;

	if (sscanf(buffer, "%llu,%llu", &soft_limit, &max) != 2)
		return -EINVAL;

	if (soft_limit > max)
		return -EINVAL;
	
	pids->group_soft_limit = soft_limit;
	pids->group_limit = max;

	spin_lock(&group_pids_lock);

	list_for_each_entry(gp, &pids->group_pids_list, node) {
		gp->soft_limit = soft_limit;
		gp->limit = max;
	}

	spin_unlock(&group_pids_lock);
	return 0;
}


static struct cgroup_subsys_state *pids_css_alloc(struct cgroup *parent)
{
	struct pids_cgroup *pids;

	pids = kzalloc(sizeof(struct pids_cgroup), GFP_KERNEL);
	if (!pids)
		return ERR_PTR(-ENOMEM);

	pids->limit = PIDS_MAX;
	pids->group_soft_limit = PIDS_MAX;
	pids->group_limit = PIDS_MAX;
	atomic64_set(&pids->counter, 0);
	INIT_LIST_HEAD(&pids->group_pids_list);
#ifdef CONFIG_CGROUP_PIDS_NOTIFY_USER
	INIT_LIST_HEAD(&pids->events);
	spin_lock_init(&pids->event_list_lock);
#endif
	return &pids->css;
}

static void pids_css_free(struct cgroup *cgrp)
{
	kfree(css_pids(cgrp));
}

/**
 * pids_cancel - uncharge the local pid count
 * @pids: the pid cgroup state
 * @num: the number of pids to cancel
 *
 * This function will WARN if the pid count goes under 0,
 * because such a case is a bug in the pids controller proper.
 */
static void pids_cancel(struct pids_cgroup *pids, int num)
{
	/*
	 * A negative count (or overflow for that matter) is invalid,
	 * and indicates a bug in the pids controller proper.
	 */
	WARN_ON_ONCE(atomic64_add_negative(-num, &pids->counter));
}

/**
 * pids_uncharge - hierarchically uncharge the pid count
 * @pids: the pid cgroup state
 * @num: the number of pids to uncharge
 */
static void pids_uncharge(struct pids_cgroup *pids, int num)
{
	struct pids_cgroup *p;

	for (p = pids; p; p = parent_pids(p))
		pids_cancel(p, num);
}

/**
 * pids_charge - hierarchically charge the pid count
 * @pids: the pid cgroup state
 * @num: the number of pids to charge
 *
 * This function does *not* follow the pid limit set. It cannot
 * fail and the new pid count may exceed the limit, because
 * organisational operations cannot fail in the unified hierarchy.
 */
static void pids_charge(struct pids_cgroup *pids, int num)
{
	struct pids_cgroup *p;

	for (p = pids; p; p = parent_pids(p))
		atomic64_add(num, &p->counter);
}

/**
 * pids_try_charge - hierarchically try to charge the pid count
 * @pids: the pid cgroup state
 * @num: the number of pids to charge
 *
 * This function follows the set limit. It will fail if the charge
 * would cause the new value to exceed the hierarchical limit.
 * Returns 0 if the charge succeded, otherwise -EAGAIN.
 */
static int pids_try_charge(struct pids_cgroup *pids, int num)
{
	struct pids_cgroup *p, *q;

	for (p = pids; p; p = parent_pids(p)) {
		int64_t new = atomic64_add_return(num, &p->counter);
		if (new > p->limit)
			goto revert;
	}

	return 0;

revert:
	for (q = pids; q != p; q = parent_pids(q))
		pids_cancel(q, num);
	pids_cancel(p, num);

	return -EAGAIN;
}
 
/* This is protected by cgroup lock */
static struct group_pids *tmp_gp;

static int pids_can_attach(struct cgroup *cgrp, struct cgroup_taskset *tset)
{
	struct pids_cgroup *pids = css_pids(cgrp);
	WARN_ON(tmp_gp);
	tmp_gp = kzalloc(sizeof(*tmp_gp), GFP_KERNEL);
	if (!tmp_gp)
		return -ENOMEM;

	tmp_gp->token = pids->token++;
	tmp_gp->limit = PIDS_MAX;
	atomic64_set(&tmp_gp->counter, 0);
	INIT_LIST_HEAD(&tmp_gp->head);
	tmp_gp->soft_limit = pids->group_soft_limit;
	tmp_gp->limit = pids->group_limit;
	return 0;
}

static void pids_cancel_attach(struct cgroup *cgrp, struct cgroup_taskset *tset)
{
	kfree(tmp_gp);
	tmp_gp = NULL;
}
 
static void pids_attach(struct cgroup *cgrp, struct cgroup_taskset *tset)
{
	struct pids_cgroup *pids = css_pids(cgrp);
	struct cgroup *old_cgrp;
	struct task_struct *task;
	int64_t num = 0;

	spin_lock(&group_pids_lock);

	cgroup_taskset_for_each(task, NULL, tset) {
		num++;

		old_cgrp = cgroup_taskset_cur_cgroup(tset);
		pids_uncharge(css_pids(old_cgrp), 1);

		group_pids_migrate(task, tmp_gp);
	}
	list_add(&tmp_gp->node, &pids->group_pids_list);

	spin_unlock(&group_pids_lock);

	/*
	 * Attaching to a cgroup is allowed to overcome the
	 * the PID limit, so that organisation operations aren't
	 * blocked by the `pids` cgroup controller.
	 */
	pids_charge(pids, num);

	tmp_gp = NULL;
}

int cgroup_pids_can_fork(void)
{
	struct pids_cgroup *pids = task_pids(current);
	int ret;

	ret = pids_try_charge(pids, 1);
	if (ret)
		return ret;

	spin_lock(&group_pids_lock);
	ret = group_pids_try_charge(current->group_pids, 1);
	if (ret < 0) {
		printk(KERN_WARNING
		    "Pid %d(%s) over pids cgroup hard_limit\n",
		     task_tgid_vnr(current), current->comm);
		pids_uncharge(pids, 1);
	} if (ret == EDQUOT) {
		pids_event(pids, current->group_pids);
		ret = 0;
	}
	spin_unlock(&group_pids_lock);
	return ret;
}

void cgroup_pids_cancel_fork(void)
{
	struct pids_cgroup *pids = task_pids(current);

	pids_uncharge(pids, 1);

	spin_lock(&group_pids_lock);
	group_pids_uncharge(current->group_pids, 1);
	spin_unlock(&group_pids_lock);
}

static void pids_fork(struct task_struct *tsk)
{
	spin_lock(&group_pids_lock);
	if (tsk->group_pids) {
		tsk->group_pids = current->group_pids;
		list_add_tail(&tsk->group_pids_list,
			      &current->group_pids->head);
	}
	spin_unlock(&group_pids_lock);
}

static void pids_exit(struct cgroup *cgrp, struct cgroup *old_cgrp,
		      struct task_struct *task)
{
	struct pids_cgroup *pids = css_pids(old_cgrp);

	pids_uncharge(pids, 1);

	spin_lock(&group_pids_lock);

	if (task->group_pids) {
		atomic64_dec(&task->group_pids->counter);
		list_del(&task->group_pids_list);
		if (list_empty(&task->group_pids->head)) {
			list_del(&task->group_pids->node);
			kfree(task->group_pids);
		}
	}

	spin_unlock(&group_pids_lock);
}

static int pids_max_write(struct cgroup *cgrp, struct cftype *cft, s64 max)
{
	struct pids_cgroup *pids = css_pids(cgrp);

	if (max < 0 || max > INT_MAX)
		return -EINVAL;

	/*
	 * Limit updates don't need to be mutex'd, since it isn't
	 * critical that any racing fork()s follow the new limit.
	 */
	pids->limit = max;
	return 0;
}

static s64 pids_max_show(struct cgroup *cgrp, struct cftype *cft)
{
	struct pids_cgroup *pids = css_pids(cgrp);

	return pids->limit;
}

static s64 pids_current_read(struct cgroup *cgrp, struct cftype *cft)
{
	struct pids_cgroup *pids = css_pids(cgrp);

	return atomic64_read(&pids->counter);
}
static int
pids_allow_attach(struct cgroup *cgrp, struct cgroup_taskset *tset)
{
	const struct cred *cred = current_cred(), *tcred;
	struct task_struct *task;

	cgroup_taskset_for_each(task, cgrp, tset) {
		tcred = __task_cred(task);

		if ((current != task) && !capable(CAP_SYS_NICE) &&
			cred->euid != tcred->uid && cred->euid != tcred->suid)
			return -EACCES;
		}

	return 0;
}
/**
 *a notify eventfd to report which process to over the process number limit
 */
#ifdef CONFIG_CGROUP_PIDS_NOTIFY_USER
struct pids_event {
	struct eventfd_ctx *efd;
	struct list_head node;
};

/**
 * when a process have soft limit
 */
static void pids_event(struct pids_cgroup *pids, struct group_pids *gp)
{
	struct pids_event *ev;

	//is gp has signal to user space, protect by group_pids_lock
	if (gp->signal)
		return;

	spin_lock(&pids->event_list_lock);
	list_for_each_entry(ev, &pids->events, node) {
		eventfd_signal(ev->efd, 1);
		gp->signal = true;
    }
	spin_unlock(&pids->event_list_lock);

}

static int group_pids_events_show(struct cgroup *cgrp, struct cftype *cft,
				   struct seq_file *m)
{
	struct pids_cgroup *pids = css_pids(cgrp);
	struct group_pids *gp;
	struct task_struct *task;
	int64_t count;

	spin_lock(&group_pids_lock);
	list_for_each_entry(gp, &pids->group_pids_list, node) {
		WARN_ON(list_empty(&gp->head));

		task = list_first_entry(&gp->head, struct task_struct,
					group_pids_list);
		count = atomic64_read(&gp->counter);
		if (count < gp->soft_limit) {
			continue;
		}
		seq_printf(m, "%llu %lu %lu %llu\n",
			    (long long)gp->token,
			    (long)task_tgid_vnr(task),
			    (long)from_kuid_munged(current_user_ns(), task_uid(task)),
			    (long long)count);
	}
	spin_unlock(&group_pids_lock);
	return 0;
}

static int pids_cgroup_usage_register_event(struct cgroup *cgrp,
	struct cftype *cft, struct eventfd_ctx *eventfd, const char *args)
{
	struct pids_cgroup *pids = css_pids(cgrp);
	struct pids_event *ev;

	ev = kzalloc(sizeof(*ev), GFP_KERNEL);
	if (!ev)
		return -ENOMEM;
	ev->efd = eventfd;

	spin_lock(&pids->event_list_lock);
	list_add(&ev->node, &pids->events);
	spin_unlock(&pids->event_list_lock);

	return 0;
}

static void pids_cgroup_usage_unregister_event(struct cgroup *cgrp,
	struct cftype *cft, struct eventfd_ctx *eventfd)
{
	struct pids_cgroup *pids = css_pids(cgrp);
	struct pids_event *ev;

	spin_lock(&pids->event_list_lock);
	list_for_each_entry(ev, &pids->events, node) {
		if (ev->efd != eventfd)
			continue;
		list_del(&ev->node);
		kfree(ev);
		break;
	}
	spin_unlock(&pids->event_list_lock);
}
#endif //end CONFIG_CGROUP_PIDS_NOTIFY_USER

static struct cftype files[] = {
	{
		.name		= "max",
		.write_s64	= pids_max_write,
		.read_s64	= pids_max_show,
		.flags		= CFTYPE_NOT_ON_ROOT,
	},
	{
		.name		= "current",
		.read_s64	= pids_current_read,
	},
    {
		.name		= "group_limit",
		.read_seq_string = group_pids_limit_show,
		.write_string	= group_pids_limit_write,
		.flags		= CFTYPE_NOT_ON_ROOT,
	},	
	{
		.name		= "group_tasks",
		.read_seq_string = group_pids_max_show,
		.flags		= CFTYPE_NOT_ON_ROOT,
	},
#ifdef CONFIG_CGROUP_PIDS_NOTIFY_USER
	{
		.name		= "group_event",
		.read_seq_string = group_pids_events_show,
		.register_event = pids_cgroup_usage_register_event,
		.unregister_event = pids_cgroup_usage_unregister_event,
		.flags		= CFTYPE_NOT_ON_ROOT,
	},
#endif //end CONFIG_CGROUP_PIDS_NOTIFY_USER
	{ }	/* terminate */
};
struct cgroup_subsys pids_subsys = {
	.name		= "pids",
	.css_alloc	= pids_css_alloc,
	.css_free	= pids_css_free,
	.can_attach	= pids_can_attach,
	.cancel_attach	= pids_cancel_attach,
	.attach		= pids_attach,
	.allow_attach   = pids_allow_attach,
	.fork		= pids_fork,
	.exit		= pids_exit,
	.subsys_id	= pids_subsys_id,
	.base_cftypes	= files,
};
