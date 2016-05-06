/* drivers/huawei_platform/uid_iostats.c
 *
 * Copyright (C) 2014 - 2015 Huawei, Inc.
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

#include <linux/atomic.h>
#include <linux/err.h>
#include <linux/hashtable.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/profile.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define UID_HASH_BITS	10
#define UID_IO_STATS_DEBUG (0)
DECLARE_HASHTABLE(uid_io_hash_table, UID_HASH_BITS);

static DEFINE_MUTEX(uid_lock);
static struct proc_dir_entry *parent;

static void uid_add_action(uid_t uid);
static void uid_remove_action(uid_t uid);

enum uid_action_type {
	UIDACTION_REMOVE = 0,
	UIDACTION_ADD,
	UIDACTION_UNKNOWN
};

typedef void (*action_handler)(uid_t uid);

struct uid_action_handler {
	enum uid_action_type type;
	action_handler	func;
};

struct uid_action_handler g_handlers[] = {
	{UIDACTION_REMOVE, uid_remove_action},
	{UIDACTION_ADD, uid_add_action},
	{UIDACTION_UNKNOWN, NULL},
};

struct uid_entry {
	uid_t uid;
	u64 read_bytes;
	u64 write_bytes;
	struct hlist_node hash;
};

static struct uid_entry *find_uid_entry(uid_t uid)
{
	struct uid_entry *uid_entry;
	hash_for_each_possible(uid_io_hash_table, uid_entry, hash, uid) {
		if (uid_entry->uid == uid) {
#if UID_IO_STATS_DEBUG
			pr_err("%s: find the uid_entry for %ld\n",
					__func__, (long int)uid);
#endif
			return uid_entry;
		}
	}
#if UID_IO_STATS_DEBUG
	pr_err("%s: cannot find the uid_entry for %ld\n",
				__func__, (long int)uid);
#endif

	return NULL;
}

static struct uid_entry *find_or_register_uid(uid_t uid)
{
	struct uid_entry *uid_entry;

	uid_entry = find_uid_entry(uid);
	if (uid_entry) {
#if UID_IO_STATS_DEBUG
		pr_err("%s: find the uid_entry\n", __func__);
#endif
		return uid_entry;
	}

	uid_entry = kzalloc(sizeof(struct uid_entry), GFP_ATOMIC);
	if (!uid_entry) {
		pr_err("%s: cannot alloc the uid_entry\n", __func__);
		return NULL;
	}

	uid_entry->uid = uid;

	hash_add(uid_io_hash_table, &uid_entry->hash, uid);

	return uid_entry;
}

static int uid_stat_show(struct seq_file *m, void *v)
{
	struct uid_entry *uid_entry;
	unsigned long bkt;

	mutex_lock(&uid_lock);

	hash_for_each(uid_io_hash_table, bkt, uid_entry, hash) {
		seq_printf(m, "%d: %llu %llu\n", uid_entry->uid,
					uid_entry->read_bytes,
					uid_entry->write_bytes);
	}

	mutex_unlock(&uid_lock);
	return 0;
}

static int uid_stat_open(struct inode *inode, struct file *file)
{
	return single_open(file, uid_stat_show, PDE_DATA(inode));
}

static const struct file_operations uid_stat_fops = {
	.open		= uid_stat_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static void uid_add_action(uid_t uid)
{
	struct uid_entry *uid_entry;

	mutex_lock(&uid_lock);

	uid_entry = find_or_register_uid(uid);
	if (!uid_entry) {
		pr_err("%s: failed to find the uid_entry for uid %ld\n",
			__func__, (long int)uid);
	}

	mutex_unlock(&uid_lock);
}

static void uid_remove_action(uid_t uid)
{
	struct uid_entry *uid_entry = NULL;

	mutex_lock(&uid_lock);

	uid_entry = find_uid_entry(uid);
	if (uid_entry) {
		hash_del(&uid_entry->hash);
		kfree(uid_entry);
		uid_entry = NULL;
	}

	mutex_unlock(&uid_lock);
}


static void uid_list_action(char *uids, int type)
{
	char *start_uid = NULL;
	char *end_uid = NULL;
	uid_t uid_start;


	if (!uids || '\0' == uids[0])
		return;

	start_uid = &uids[0];

	do {
		end_uid = strstr(start_uid, ",");
		if (end_uid)
			*end_uid = '\0';

		if (kstrtol(start_uid, 10, (long *)&uid_start) != 0) {
			pr_err("%s: the input include invalid value\n",
						__func__);
			break;
		}

#if  UID_IO_STATS_DEBUG
		pr_err("%s: the uid is %ld\n", __func__, (long int)uid_start);
#endif

		g_handlers[type].func(uid_start);

		if (end_uid)
			start_uid = end_uid + 1;
		else
			start_uid = end_uid;

	} while (start_uid && *start_uid != '\0');
}

static int uid_remove_open(struct inode *inode, struct file *file)
{
	return single_open(file, NULL, NULL);
}

static ssize_t uid_remove_write(struct file *file,
			const char __user *buffer, size_t count, loff_t *ppos)
{
	char *uids = NULL;

	uids = kzalloc(count + 1, GFP_KERNEL);
	if (!uids)
		return -EFAULT;

	if (copy_from_user(uids, buffer, count)) {
		kfree(uids);
		return -EFAULT;
	}

	uids[count] = '\0';

	uid_list_action(uids, UIDACTION_REMOVE);

	kfree(uids);
	return count;
}

static const struct file_operations uid_remove_fops = {
	.open		= uid_remove_open,
	.release	= single_release,
	.write		= uid_remove_write,
};

static int uid_add_open(struct inode *inode, struct file *file)
{
	return single_open(file, NULL, NULL);
}

static ssize_t uid_add_write(struct file *file,
			const char __user *buffer, size_t count, loff_t *ppos)
{
	char *uids = NULL;

	uids = kzalloc(count + 1, GFP_KERNEL);
	if (!uids)
		return -EFAULT;

	if (copy_from_user(uids, buffer, count)) {
		kfree(uids);
		return -EFAULT;
	}

	uids[count] = '\0';

#if UID_IO_STATS_DEBUG
	pr_err("%s: the uids is %s\n", __func__, uids);
#endif

	uid_list_action(uids, UIDACTION_ADD);

	kfree(uids);
	return count;
}

static const struct file_operations uid_add_fops = {
	.open		= uid_add_open,
	.release	= single_release,
	.write		= uid_add_write,
};

static int process_notifier(struct notifier_block *self,
			unsigned long cmd, void *v)
{
	struct task_struct *task = v;
	struct uid_entry *uid_entry = NULL;
	uid_t uid;

	if (!task)
		return NOTIFY_OK;

	mutex_lock(&uid_lock);
	uid = from_kuid_munged(current_user_ns(), task_uid(task));
#if UID_IO_STATS_DEBUG
	pr_err("%s: the task %s's pid is %d, the uid is %d\n",
			__func__,
			task->comm,
			task->pid, uid);
	pr_err("%s: the task write_bytes is %llu\n",
				__func__,
				task->ioac.write_bytes);
#endif

	uid_entry = find_uid_entry(uid);
	if (!uid_entry)
		goto exit;


	if (uid_entry) {
		uid_entry->read_bytes += task->ioac.read_bytes;
		uid_entry->write_bytes += task->ioac.write_bytes;
	} else
		pr_err("%s: uid_entry is null\n", __func__);


exit:
	mutex_unlock(&uid_lock);
	return NOTIFY_OK;
}

static struct notifier_block process_notifier_block = {
	.notifier_call	= process_notifier,
};

static int __init proc_uid_io_account_init(void)
{
	hash_init(uid_io_hash_table);

	parent = proc_mkdir_mode("uid_iostats",
					S_IRUSR | S_IXUSR | S_IRGRP
					| S_IXGRP | S_IROTH | S_IXOTH,
					NULL);
	if (!parent) {
		pr_err("%s: failed to create proc entry\n", __func__);
		return -ENOMEM;
	}
	proc_create_data("uid_iomonitor_list",
			S_IWUSR | S_IWGRP, parent, &uid_add_fops,
			NULL);

	proc_create_data("remove_uid_list",
			S_IWUSR | S_IWGRP, parent, &uid_remove_fops,
			NULL);

	proc_create_data("show_uid_iostats",
			S_IRUSR | S_IRGRP, parent, &uid_stat_fops,
			NULL);

	profile_event_register(PROFILE_TASK_EXIT, &process_notifier_block);

	return 0;
}

early_initcall(proc_uid_io_account_init);
