/*
 * debugfs test code for hisi_ddr_devfreq.c
 *
 * Copyright (c) 2013- Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/pm_qos.h>

#include <linux/debugfs.h>
#include <linux/uaccess.h>

#define PM_QOS_USERS 5

struct debugfs_pm_qos_user {
	struct pm_qos_request req;
	s32 value;
};

/*
 * 1. debugfs file node:
 * - dev/debugfs/ddr_devfreq/debug
 *
 * 2. test cmd:
 * - "echo add "type"", add a ddr bandwidth request;
 * - "echo request user-"index"", get current sum of bandwidth requests;
 * - "echo update user-"index" "new value"", update user-"index"'s bandwidth request "new value";
 * - "echo remove user-"index"", remove user-"index" bandwidth request;
 * - "cat", show current ddr bandwidth request users information.
 */

static struct dentry *ddr_devfreq_debug_dir;
static struct dentry *ddr_devfreq_fn;

static struct debugfs_pm_qos_user *pm_qos_user[PM_QOS_USERS] = {NULL};
static int pm_qos_users;

static void debugfs_add_request(int type)
{
	struct debugfs_pm_qos_user *new_user = NULL;
	int users = pm_qos_users;

	if (users >= PM_QOS_USERS) {
		pr_info("[DDR DEVFREQ DEBUGFS] no more user\n");
		return;
	}

	new_user = kmalloc(sizeof(struct debugfs_pm_qos_user), GFP_KERNEL);
	if (!new_user) {
		pr_info("[DDR DEVFREQ DEBUGFS] no mem\n");
		return;
	}

	switch (type) {
	case PM_QOS_MEMORY_THROUGHPUT:
		new_user->value =
			PM_QOS_MEMORY_THROUGHPUT_DEFAULT_VALUE;
		break;
	case PM_QOS_MEMORY_THROUGHPUT_UP_THRESHOLD:
		new_user->value =
			PM_QOS_MEMORY_THROUGHPUT_UP_THRESHOLD_DEFAULT_VALUE;
		break;
	default:
		break;
	}

	new_user->req.pm_qos_class = 0;
	pm_qos_add_request(&new_user->req, type, new_user->value);

	pm_qos_user[users] = new_user;
	pm_qos_users++;
	return;
}

static void debugfs_remove_request(int users)
{
	struct debugfs_pm_qos_user *user = NULL;
	int i;

	if (users > pm_qos_users) {
		pr_info("[DDR DEVFREQ DEBUGFS] no such user\n");
		return;
	}

	users--;
	user = pm_qos_user[users];

	pm_qos_remove_request(&user->req);
	kfree(user);
	pm_qos_user[users] = NULL;

	for (i = users + 1; i < PM_QOS_USERS; i++) {
		pm_qos_user[i - 1] = pm_qos_user[i];
		pm_qos_user[i] = NULL;
	}

	pm_qos_users--;
	return;
}

static int debugfs_request_value(int users)
{
	struct debugfs_pm_qos_user *user = NULL;
	struct pm_qos_request *req;

	if (users > pm_qos_users) {
		pr_info("[DDR DEVFREQ DEBUGFS] no such user\n");
		return -1;
	}

	users--;
	user = pm_qos_user[users];
	req = &user->req;
	return pm_qos_request(req->pm_qos_class);
}

static void debugfs_update_request(int users, s32 new_value)
{
	struct debugfs_pm_qos_user *user = NULL;

	if (users > pm_qos_users) {
		pr_info("[DDR DEVFREQ DEBUGFS] no such user\n");
		return;
	}

	users--;
	user = pm_qos_user[users];
	user->value = new_value;
	pm_qos_update_request(&user->req, new_value);
	return;
}

static int debugfs_show(struct seq_file *s, void *data)
{
	int i;

	pr_info("[DDR DEVFREQ DEBUGFS] user information ++++++++++++++++++\n");
	for (i = 0; i < pm_qos_users; i++)
		pr_info("memory throughput user-%d: %d mbyte/s\n", i + 1,
			pm_qos_user[i]->value);

	pr_info("[DDR DEVFREQ DEBUGFS] user information ------------------\n");
	return 0;
}

static int debugfs_open(struct inode *inode, struct file *file)
{
	return single_open(file, debugfs_show, inode->i_private);
}

static ssize_t
debugfs_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
	char buf[128];
	char *cmd = NULL;
	char *_cmd = NULL;
	int users;
	int type;
	s32 value;

	if (copy_from_user(buf, ubuf, cnt - 1)) {
		pr_err("[DDR DEVFREQ DEBUGFS] can not copy from user\n");
		cnt = -EINVAL;
		goto out;
	}

	buf[cnt - 1] = '\0';
	cmd = buf;
	_cmd = buf;
	pr_info("[DDR DEVFREQ DEBUGFS] [cmd: %s[cnt: %d]]\n", cmd, (int)cnt);

	if (!strncmp("add ", _cmd, strlen("add "))) {
		cmd = cmd + strlen("add ");
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;
		*_cmd = '\0';

		if (kstrtos32(cmd, 10, &type)) {
			pr_err("[DDR DEVFREQ DEBUGFS] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		debugfs_add_request(type);
	} else if (!strncmp("remove user-", _cmd, strlen("remove user-"))) {
		cmd = cmd + strlen("remove user-");
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;
		*_cmd = '\0';

		if (kstrtos32(cmd, 10, &users)) {
			pr_err("[DDR DEVFREQ DEBUGFS] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		debugfs_remove_request(users);
	} else if (!strncmp("update user-", _cmd, strlen("update user-"))) {
		cmd = cmd + strlen("update user-");
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;

		if ('\0' == *_cmd) {
			pr_err("[DDR DEVFREQ DEBUGFS] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}
		*_cmd = '\0';

		if (kstrtos32(cmd, 10, &users)) {
			pr_err("[DDR DEVFREQ DEBUGFS] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		cmd = _cmd + 1;
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;
		*_cmd = '\0';

		if (kstrtos32(cmd, 10, &value)) {
			pr_err("[DDR DEVFREQ DEBUGFS] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		debugfs_update_request(users, value);
	} else if (!strncmp("request user-", _cmd, strlen("request user-"))) {
		cmd = cmd + strlen("request user-");
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;
		*_cmd = '\0';

		if (kstrtos32(cmd, 10, &users)) {
			pr_err("[DDR DEVFREQ DEBUGFS] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		pr_info("[DDR DEVFREQ DEBUGFS] memory throughput %d\n",
			debugfs_request_value(users));
	} else {
		pr_err("[DDR DEVFREQ DEBUGFS] cmd error\n");
		cnt = -EINVAL;
	}
out:
	return cnt;
}

static const struct file_operations ddr_devfreq_debugfs_ops = {
	.open		= debugfs_open,
	.read		= seq_read,
	.write		= debugfs_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init ddr_devfreq_debugfs_init(void)
{
	ddr_devfreq_debug_dir = debugfs_create_dir("ddr_devfreq", NULL);
	if (ddr_devfreq_debug_dir)
		ddr_devfreq_fn = debugfs_create_file("debug", S_IRUGO,
			ddr_devfreq_debug_dir, NULL, &ddr_devfreq_debugfs_ops);

	pm_qos_users = 0;
	return 0;
}
module_init(ddr_devfreq_debugfs_init);

static void __exit ddr_devfreq_debugfs_exit(void)
{
	debugfs_remove(ddr_devfreq_fn);
	debugfs_remove(ddr_devfreq_debug_dir);

	return;
}
module_exit(ddr_devfreq_debugfs_exit);
