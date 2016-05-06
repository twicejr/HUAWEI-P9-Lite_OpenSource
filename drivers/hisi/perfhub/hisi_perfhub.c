#include <linux/init.h>
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/cpumask.h>
#include <linux/threads.h>
#include <linux/cpu.h>
#include <linux/security.h>
#include <linux/cpuset.h>

#define LITTLE_CPU_START 0
#define BIG_CPU_START    4
#define CPU_TOTAL        8

static char g_last_tag;
static int g_last_pid;

enum cpu_cluster {
	CPU_CLUSTER_LITTLE,
	CPU_CLUSTER_BIG,
	CPU_CLUSTER_ALL,
};

static int bind_cpu_cluster(enum cpu_cluster e_cpu_cluster, pid_t pid)
{
	cpumask_var_t cpus_allowed, new_mask;
	struct task_struct *p = NULL;
	int retval;
	struct cpumask mask;
	int cpu_no;
	const struct cred *pcred = NULL;

	cpumask_clear(&mask);

	switch (e_cpu_cluster) {
		case CPU_CLUSTER_LITTLE: for (cpu_no = LITTLE_CPU_START; cpu_no < BIG_CPU_START; cpu_no++) cpumask_set_cpu(cpu_no, &mask); break;
		case CPU_CLUSTER_BIG:    for (cpu_no = BIG_CPU_START; cpu_no < CPU_TOTAL; cpu_no++) cpumask_set_cpu(cpu_no, &mask); break;
		default:                 for (cpu_no = LITTLE_CPU_START; cpu_no < CPU_TOTAL; cpu_no++) cpumask_set_cpu(cpu_no, &mask); break;
	}

	get_online_cpus();
	rcu_read_lock();

	p = find_task_by_vpid(pid);
	if (!p) {
		rcu_read_unlock();
		put_online_cpus();
		return -ESRCH;
	}

	/* Prevent p going away */
	get_task_struct(p);
	pcred = __task_cred(p);
	rcu_read_unlock();

	if (p->flags & PF_NO_SETAFFINITY) {
		retval = -EINVAL;
		goto out_put_task;
	}
	if (!alloc_cpumask_var(&cpus_allowed, GFP_KERNEL)) {
		retval = -ENOMEM;
		goto out_put_task;
	}
	if (!alloc_cpumask_var(&new_mask, GFP_KERNEL)) {
		retval = -ENOMEM;
		goto out_free_cpus_allowed;
	}

	retval = security_task_setscheduler(p);
	if (retval)
		goto out_unlock;

	cpuset_cpus_allowed(p, cpus_allowed);
	cpumask_and(new_mask, &mask, cpus_allowed);
again:
	retval = set_cpus_allowed_ptr(p, new_mask);

	if (!retval) {
		cpuset_cpus_allowed(p, cpus_allowed);
		if (!cpumask_subset(new_mask, cpus_allowed)) {
			/*
			 * We must have raced with a concurrent cpuset
			 * update. Just reset the cpus_allowed to the
			 * cpuset's cpus_allowed
			 */
			cpumask_copy(new_mask, cpus_allowed);
			goto again;
		}
	}
out_unlock:
	free_cpumask_var(new_mask);
out_free_cpus_allowed:
	free_cpumask_var(cpus_allowed);
out_put_task:
	put_task_struct(p);
	put_online_cpus();

	return retval;
}

static ssize_t perfhub_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%c|%d\n", g_last_tag, g_last_pid);
}

static ssize_t perfhub_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	char tag;
	long pid;
	int ret;
	char *pstrchr = NULL;

	tag = *buf;

	pstrchr = strchr(buf, '|');
	if (NULL == pstrchr)
		return -EINVAL;

	pstrchr++;

	ret = strict_strtol(pstrchr, 10, &pid);
	if (ret != 0)
		return -EINVAL;

	g_last_tag = tag;
	g_last_pid = pid;

	if (tag == 'P') {
		ret = bind_cpu_cluster(CPU_CLUSTER_BIG, pid);
		if (0 != ret)
			return -EINVAL;
	} else if (tag == 'N') {
		ret = bind_cpu_cluster(CPU_CLUSTER_ALL, pid);
		if (0 != ret)
			return -EINVAL;
	} else {
		pr_err("invalid tag (%c)", tag);
		return -EINVAL;
	}

	return count;
}

static struct kobj_attribute perfhub_attribute = __ATTR(cpuaffinity, 0660, perfhub_show, perfhub_store);

static struct kobject *perfhub_kobj = NULL;

static int __init perfhub_init(void)
{
	int retval = 0;

	perfhub_kobj = kobject_create_and_add("perfhub", kernel_kobj);
	if (!perfhub_kobj)
		return -ENOMEM;

	retval = sysfs_create_file(perfhub_kobj, &perfhub_attribute);
	if (retval) {
		kobject_put(perfhub_kobj);
		perfhub_kobj = NULL;
	}

	return retval;
}

static void __exit perfhub_exit(void)
{
	if (perfhub_kobj) {
		sysfs_remove_file(perfhub_kobj, &perfhub_attribute);
		kobject_put(perfhub_kobj);
		perfhub_kobj = NULL;
	}
}

module_init(perfhub_init);
module_exit(perfhub_exit);

MODULE_DESCRIPTION("Hisilicon hisi perf hub");
MODULE_LICENSE("GPL v2");

