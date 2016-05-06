#ifndef CGROUP_PIDS_H_INCLUDED
#define CGROUP_PIDS_H_INCLUDED

#ifdef CONFIG_CGROUP_PIDS

int cgroup_pids_can_fork(void);
void cgroup_pids_cancel_fork(void);

#else /* CONFIG_CGROUP_PIDS */

static inline int cgroup_pids_can_fork(void)
{
	return 0;
}

static void cgroup_pids_cancel_fork(void)
{
}

#endif /* CONFIG_CGROUP_PIDS */

#endif /* CGROUP_PIDS_H_INCLUDED */
