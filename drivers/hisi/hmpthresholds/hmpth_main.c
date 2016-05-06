/*
 * set policy to hmp thresholds.
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/thread_info.h>
#include <linux/kthread.h>
#include <linux/sysfs.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>
#include "hmpth_main.h"

struct hmp_policy_struct hmp_policy[MAX_MUM_POLICY];
struct hmp_policy_struct pri_hmp_policy[MAX_MUM_POLICY];

static unsigned int hmpset_enable = 0;

static spinlock_t hmpset_lock;

#ifdef HMPTH_SET_DEBUG
void debug_hmp_policy_struct(char *name, struct hmp_policy_struct *test)
{
	int i = 0;
	pr_err("Debug_struct:%s\n", name);

	while (i < MAX_MUM_POLICY) {
		pr_err("[%15s] %4d %4d %4d %4d %4d\n",
				test[i].name,
				test[i].prior,
				test[i].policy_state,
				test[i].thrsh_up,
				test[i].thrsh_down,
				test[i].prior_direct);
		i++;
	}
}
#else
#define debug_hmp_policy_struct(n, t) {}
#endif

#ifdef CONFIG_CPU_HOTPLUG
extern int change_cpu_hmp_threshold(unsigned int threshold);
#endif

/*
 * write /sys/kernel/hmp/{up,down}_threshold
 * or set hmp_up_threshold,hmp_down_threshold
 * in fair.c
*/
static void set_hmp_thresholds(unsigned int tsh_up, unsigned int tsh_down)
{
	hmp_up_threshold = tsh_up;
	hmp_down_threshold = tsh_down;

#ifdef CONFIG_CPU_HOTPLUG
#ifdef CONFIG_USE_BIG_CORE_DEPTH
	#error "can't set hmpthreshold here."
#endif
	change_cpu_hmp_threshold(tsh_up);
#endif /* CONFIG_CPU_HOTPLUG */

	return;
}

static void calc_thresholds(void)
{
	int cntpc = 0;
	int priority = -1;
	unsigned int up_value = 0;
	unsigned int down_value = 0;
	int prior_direct = LOWPOWER;

	while (cntpc < MAX_MUM_POLICY) {
		if (strlen(pri_hmp_policy[cntpc].name) <= 0)
			break;
		if (STATE_OFF == pri_hmp_policy[cntpc].policy_state) {
			cntpc++;
			continue;
		}
		/*
		 * since pri_hmp_policy is arranged by policy from
		 * big to small, this "if" will enter only once.
		 */
		if (priority < pri_hmp_policy[cntpc].prior) {
			priority = pri_hmp_policy[cntpc].prior;
			up_value = pri_hmp_policy[cntpc].thrsh_up;
			down_value = pri_hmp_policy[cntpc].thrsh_down;
			prior_direct = pri_hmp_policy[cntpc].prior_direct;
			/*this is the default state*/
			if (0 == priority)
				break;
			cntpc++;
			continue;
		} else if (priority > pri_hmp_policy[cntpc].prior)
			break;
		/*
		 * priority == pri_hmp_policy[cntpc].prior
		 */
		if (prior_direct == PROFORM) {
			if (up_value > pri_hmp_policy[cntpc].thrsh_up)
				up_value = pri_hmp_policy[cntpc].thrsh_up;
			if (down_value > pri_hmp_policy[cntpc].thrsh_down)
				down_value = pri_hmp_policy[cntpc].thrsh_down;
		} else {	/*prior_direct == LOWPOWER*/
			if (up_value < pri_hmp_policy[cntpc].thrsh_up)
				up_value = pri_hmp_policy[cntpc].thrsh_up;
			if (down_value < pri_hmp_policy[cntpc].thrsh_down)
				down_value = pri_hmp_policy[cntpc].thrsh_down;
		}
		cntpc++;
	}

	if (up_value - down_value < 100) {
		pr_err("hmpth: error! it's impossible to enter here!\n");
		if (up_value < 100)
			up_value = 100;
		down_value = up_value - 100;
	}

	set_hmp_thresholds(up_value, down_value);
	return;
}

static void cp_policy(struct hmp_policy_struct *tmpolicy,
		const char *pname, int prio, int state,
		unsigned int up_thresholds, unsigned int down_thresholds)
{
	strncpy(tmpolicy->name, pname,
		sizeof(tmpolicy->name) - 1);
	tmpolicy->prior = prio;
	tmpolicy->policy_state = state;
	tmpolicy->thrsh_up = up_thresholds;
	tmpolicy->thrsh_down = down_thresholds;

	switch (prio) {
	case PRIOR_2:
		tmpolicy->prior_direct = PROFORM;
		break;
	case PRIOR_4:
		tmpolicy->prior_direct = LOWPOWER;
		break;
	default:
		tmpolicy->prior_direct = LOWPOWER;
		break;
	}
	return;
}

static void rearrange_policys(void)
{
	int count_new = 0;
	int count_old = 0;
	int count_prior = PRIOR_5;

	memset(pri_hmp_policy, 0x00, sizeof(pri_hmp_policy));
	while (count_prior >= PRIOR_0) {
		count_old = 0;
		while (count_old < MAX_MUM_POLICY) {
			if (strlen(hmp_policy[count_old].name) == 0)
				break;
			if (hmp_policy[count_old].prior != count_prior) {
				count_old++;
				continue;
			}
			cp_policy(&pri_hmp_policy[count_new],
					hmp_policy[count_old].name,
					hmp_policy[count_old].prior,
					hmp_policy[count_old].policy_state,
					hmp_policy[count_old].thrsh_up,
					hmp_policy[count_old].thrsh_down);
			count_old++;
			count_new++;
			if (count_new >= MAX_MUM_POLICY) {
				/*not likely it can enter here.*/
				pr_err("hmpth: error!  count_new > 15 !\n");
				return;
			}
		}
		count_prior--;
	}
	return;
}

static int fill_policy_in(const char *pname, int prio, int state,
		unsigned int up_thresholds, unsigned int down_thresholds)
{
	int plcon = 0;
	unsigned int inputlen = strlen(pname);

	/*first, try to find if policy exist*/
	while (plcon < MAX_MUM_POLICY) {
		if ((inputlen == strlen(hmp_policy[plcon].name))
			&& (strncmp(hmp_policy[plcon].name,
				pname, inputlen) == 0)
			&& (hmp_policy[plcon].prior == prio)) {
			cp_policy(&hmp_policy[plcon], pname, prio, state,
				up_thresholds, down_thresholds);
			return 0;
		}
		plcon++;
	}
	/*second, policy not exist, find a vacant*/
	plcon = 0;
	while (plcon < MAX_MUM_POLICY) {
		if (0 == strlen(hmp_policy[plcon].name)) {
			cp_policy(&hmp_policy[plcon],
				pname, prio, state,
				up_thresholds, down_thresholds);
			return 0;
		}
		plcon++;
	}
	/* plcon == MAX_MUM_POLICY    hmp_policy is full!*/
	pr_err("hmpth: error!  too much policys!\n");
	return -1;
}

/*
 * this func can be called from other modules in kernel.
 */
int set_hmp_policy(const char *pname, int prio, int state,
		int up_thresholds, int down_thresholds)
{
	unsigned int len_name = 0;
	int ret = 0;
	unsigned int i = 0;

	if (!hmpset_enable && prio)
		 return 0;

	/*check if args has legal value.*/
	len_name = strlen(pname);
	if ((len_name < 2) || (len_name > 15)) {
		pr_err("hmpth--err_input--name_length");
		goto err_input;
	}
	while (i < len_name) {
		ret += islowchac(pname[i]);
		i++;
	}
	if (ret != len_name) {
		hmpth_debug("DEBUG: ret %d, len_name %d.\n", ret, len_name);
		pr_err("hmpth--err_inputt--name must be [a-z] only");
		goto err_input;
	}
	if ((prio < PRIOR_0) || (prio > PRIOR_5)) {
		pr_err("hmpth--err_inputt--prio");
		goto err_input;
	}
	if ((state < STATE_OFF) || (state > STATE_ON)) {
		pr_err("hmpth--err_inputt--state");
		goto err_input;
	}
	if ((up_thresholds < MIN_THRESHOLDS)
		|| (up_thresholds > MAX_THRESHOLDS)) {
		pr_err("hmpth--err_input--up");
		goto err_input;
	}
	if ((down_thresholds < MIN_THRESHOLDS)
		|| (down_thresholds > MAX_THRESHOLDS)) {
		pr_err("hmpth--err_input--down");
		goto err_input;
	}
	if ((down_thresholds + UP_MUST_BIG_THAN_DOWN) > up_thresholds) {
		pr_err("hmpth err input:up - down < 100.\n");
		goto err_input;
	}

	/*
	 * only "default" can be PRIOR_0,
	 * and default can NOT be set to OFF
	 */
	if (PRIOR_0 == prio) {
		if ((len_name != strlen(DEFAULT_POLICY_NAME))
			|| (0 != strncmp(pname, DEFAULT_POLICY_NAME, len_name))
			|| (STATE_ON != state)) {
			pr_err("PRIOR_0 must be default,and must be ON.\n");
			goto err_input;
		}
	}

	/* ---------prevent concurrent-------mutex_lock------*/
	spin_lock_bh(&hmpset_lock);
	hmpth_debug("DEBUG lock: [%s], %d, %d, %d, %d.\n", pname, prio, state,
			up_thresholds, down_thresholds);

	/*fill the input policy into hmp_policy*/
	ret = fill_policy_in(pname, prio, state,
		up_thresholds, down_thresholds);
	if (ret < 0)
		return -1;
	debug_hmp_policy_struct("fill_policy_in", &hmp_policy[0]);
	/*rearrange policys by priority*/
	rearrange_policys();
	debug_hmp_policy_struct("calc_thresholds.", &pri_hmp_policy[0]);

	/*calc the proper thresholds*/
	calc_thresholds();
	spin_unlock_bh(&hmpset_lock);
	/*---------prevent concurrent-------mutex_unlock------*/

	return 0;

err_input:
	pr_err(": illegal values!\n");
	pr_err("%s, %d, %d, %d, %d.\n",
		pname, prio, state, up_thresholds, down_thresholds);
	return -1;

}

static ssize_t policy_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	int print_cnt = 0;
	char *start = buf;
	char firstline[] =
		"            name prior state   up  down direction.\n";
	char sperateline[] =
		"---------------------------------------------------\n";

	buf += snprintf(buf, sizeof(firstline), "%s", firstline);

	while ((print_cnt < MAX_MUM_POLICY)
		&& (strlen(pri_hmp_policy[print_cnt].name) > 0)) {
		buf += snprintf(buf, 49, "%16s, %3d, %4d, %4d, %4d, %6d\n",
			pri_hmp_policy[print_cnt].name,
			pri_hmp_policy[print_cnt].prior,
			pri_hmp_policy[print_cnt].policy_state,
			pri_hmp_policy[print_cnt].thrsh_up,
			pri_hmp_policy[print_cnt].thrsh_down,
			pri_hmp_policy[print_cnt].prior_direct);

		print_cnt++;
	}
	buf += snprintf(buf, sizeof(sperateline), "%s", sperateline);
	buf += snprintf(buf, 41, "%33d, %4d\n",
		hmp_up_threshold, hmp_down_threshold);

	return buf - start;

}

static ssize_t policy_store(struct kobject *kobj,
		struct kobj_attribute *attr, const char *buf, size_t n)
{
	unsigned int args_len = 0;
	unsigned int args_num = 0;
	struct hmp_policy_struct input;
	unsigned int len = n;
	const char *tmp = buf;
	char *p;

	/*total input should less than 32 */
	if (n > 32)
		goto err_store;

	memset(&input, 0xff, sizeof(input));
	memset(input.name, 0x00, sizeof(input.name));

	while ((len > 0) && (args_num < 5)) {
		p = memchr(tmp, ',', len);
		args_len = p ? p - tmp : 0;

		switch (args_num) {
		case 0:
			/* name 2-15 bytes,*/
			if ((args_len < 2)
				|| (args_len >= MAX_LENGTH_OF_POLICY_NAME))
				goto err_store;
			strncpy(input.name, tmp, args_len);
			break;
		case 1:
			if ((args_len != 1))
				goto err_store;
			if (sscanf(tmp, "%1d", &input.prior) != 1)
				goto err_store;
			break;
		case 2:
			if ((args_len != 1))
				goto err_store;
			if (sscanf(tmp, "%1d", &input.policy_state) != 1)
				goto err_store;
			break;
		case 3:
			if ((args_len < 1) || (args_len > 4))
				goto err_store;
			if (sscanf(tmp, "%4d", &input.thrsh_up) != 1)
				goto err_store;
			break;
		case 4:
			if (args_len == 0) {
				p = memchr(tmp, '\0', len);
				args_len = p ? p - tmp : len;
			}
			if ((args_len < 1) || (args_len > 4))
				goto err_store;
			if (sscanf(tmp, "%4d", &input.thrsh_down) != 1)
				goto err_store;
			break;
		default:
			goto err_store;
		}
		tmp = tmp + args_len + 1;
		len = len - args_len - 1;
		args_num++;
	}

	hmpth_debug("hmpth: debug input buf: [%s]\n", buf);

	set_hmp_policy(input.name, input.prior, input.policy_state,
		input.thrsh_up, input.thrsh_down);
	return n;

err_store:
	pr_err("hmpth: input err! buf: [%s]\n", buf);
	pr_err("args_num: %u, args_len: %u, n: %ld.\n", args_num, args_len, n);
	return n;
}

static struct kobj_attribute policy_attr = {
	.attr   = {
		.name = "policy",
		.mode = 0644,
	},
	.show   = policy_show,
	.store  = policy_store,
};

static ssize_t enable_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, 16,"%u\n", hmpset_enable);
}

static ssize_t enable_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t n)
{
	unsigned int input;
	int ret = 0;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input > 1)
		return -EINVAL;
	if (hmpset_enable != input) {
		if(input) {
			memset(hmp_policy, 0x00, sizeof(hmp_policy));
			set_hmp_policy(DEFAULT_POLICY_NAME, PRIOR_0, STATE_ON,
				hmp_up_threshold, hmp_down_threshold);
		}
		hmpset_enable = input;
	}
	return ret;
}

static struct kobj_attribute enable_attr = {
	.attr   = {
		.name = "enable",
		.mode = 0644,
	},
	.show   = enable_show,
	.store  = enable_store,
};

static struct attribute *attrs[] = {
	&enable_attr.attr,
	&policy_attr.attr,
	NULL
};

static struct attribute_group hmpth_attr_group = {
	.attrs = attrs,
};

struct kobject *hmpth_kobj;

static int create_sysfs_node(void)
{
	int retval;

	memset(hmp_policy, 0x00, sizeof(hmp_policy));

	/* wait for kernel_kobj node ready: */
	while (kernel_kobj == NULL)
		msleep(100);

	/* Create kobject named "hungtask",located under /sys/kernel/ */
	hmpth_kobj = kobject_create_and_add("set_hmp_thresholds", kernel_kobj);
	if (!hmpth_kobj)
		return -ENOMEM;

	/* Create the files associated with this kobject */
	retval = sysfs_create_group(hmpth_kobj, &hmpth_attr_group);
	if (retval)
		kobject_put(hmpth_kobj);
	return retval;
}

static int __init hmpth_init(void)
{
	int ret;
	/*
	 * init sysfs_node
	 */
	ret = create_sysfs_node();
	if (ret)
		pr_err("hmpth: create_sysfs_node fail.\n");

	spin_lock_init(&hmpset_lock);

	return 0;
}

module_init(hmpth_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("weiyuan <weiyuan.wei@huawei.com>");
MODULE_DESCRIPTION("set policy to hmp thresholds");
