/*
 * Copyright (c) 2013- Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/hwspinlock.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>

#include "hwspinlock_internal.h"
/*
 * debugfs file node:
 * - dev/debugfs/hwspinlock/debug
 *
 * test cmd:
 * - "echo request 'ID'", request a unused hwspinlock;
 * - "echo free_lock 'ID'", free the requested hwspinlock;
 * - "echo trylock 'ID' 'timeout' 'unlock'", lock the request hwspinlock,
	timeout is msec,unlock = 0 represents that don't unlock after lock,otherwise unlock;
	and nomally maybe unlock be setted 1;
	but trylock timout maybe cause the atomic question because of sys_write is atomic
 * - "echo unlock 'ID'", unlock the hwspinlock;
 * - "cat debug", show current the resources of hwspinlock,but now have requested all locks.
 */

struct hwspinlock_hisi {
       int id_in_group;
       void __iomem *address;
};

static struct dentry *hwspinlock_debug_dir;
static struct dentry *hwspinlock_fn;
static struct hwspinlock *hwlock;
static int locked;
/*lint -e750 -esym(750,*)*/
#define RESOURCE_LOCK_STAT_OFFSET			0x8
/*lint -e750 +esym(750,*)*/

static struct hwspinlock *debugfs_hwspinlock_request_specific(int id,
						int *b_id, int *n_locks)
{
	struct hwspinlock_hisi *hwlockinfo;
	struct hwspinlock *_hwlock;

	_hwlock = hwspin_lock_request_specific(id);
	if (!_hwlock) {
		pr_err("hwspinlock %u is already in use\n", id);
		return NULL;
	}

	*b_id = _hwlock->bank->base_id;
	*n_locks = _hwlock->bank->num_locks;
	hwlockinfo = (struct hwspinlock_hisi *)(_hwlock->priv);
	pr_info("[Debug] Cat Sucess! RESOURCE_LOCK ID_IN_Group=%d  ADDR=%p\n",
				hwlockinfo->id_in_group, hwlockinfo->address);
	return _hwlock;
}

static int debugfs_hwspinlock_lock_free(struct hwspinlock *_hwlock)
{
	int ret;

	ret = hwspin_lock_free(_hwlock);
	if (ret)
		pr_err("[debug] hwspinlock free fail, ret = [%d]\n", ret);
	else
		pr_info("[debug] hwspinlock free %d sucess!\n", hwlock_to_id(_hwlock));

	return ret;
}

/*hwspin_trylock()
* Returns 0 if we successfully locked the hwspinlock, -EBUSY if
* the hwspinlock was already taken, and -EINVAL if @hwlock is invalid.
* hwspin_lock_timeout()
* Returns 0 when the @hwlock was successfully taken, and an appropriate
* error code otherwise (most notably an -ETIMEDOUT if the @hwlock is still
* busy after @timeout msecs). The function will never sleep.
*/
static int debugfs_hwspinlock_trylock_timeout(int id, int timeout, int unlock)
{
	struct hwspinlock_hisi *hwlockinfo, *hwunlockinfo;
	int ret = 0;
	int val0, val1 = 0;

	if (0 == timeout)
		ret = hwspin_trylock(hwlock);
	else if (timeout > 0) {
		ret = hwspin_lock_timeout(hwlock, timeout);
		if (ret) {
			pr_err("%s: hwspinlock timeout!\n", __func__);
			goto _timout;
		}
	}
	hwlockinfo = (struct hwspinlock_hisi *)(hwlock->priv);
	val0 = readl(hwlockinfo->address + RESOURCE_LOCK_STAT_OFFSET);
	locked = 1;
	if (unlock) {
		hwspin_unlock(hwlock);
		hwunlockinfo = (struct hwspinlock_hisi *)(hwlock->priv);
		val1 = readl(hwunlockinfo->address + RESOURCE_LOCK_STAT_OFFSET);
		locked = 0;
	} else
		val1 = readl(hwlockinfo->address + RESOURCE_LOCK_STAT_OFFSET);
	pr_info("[debug]the ResourceLock %d locked val= 0x%x,unlock val=0x%x\n", id, val0, val1);

_timout:
	return ret;
}

static int debugfs_show(struct seq_file *s, void *data)
{
	int base_id, num_locks;
	int i;
	struct hwspinlock *_hwlock;

	base_id = 0;
	num_locks = 64;

	pr_info("[DEBUGFS] HISI RESOURCE_LOCK INFO ++++++++++++\n");

	pr_info("[DEBUGFS] base_id =%d num_locks=%d\n",base_id,num_locks);
	for(i = base_id;i < num_locks; i++){
		_hwlock = debugfs_hwspinlock_request_specific(i,&base_id,&num_locks);

		if(_hwlock) {
			debugfs_hwspinlock_lock_free(_hwlock);
		}
	}

	pr_info("[DEBUGFS] HISI RESOURCE_LOCK INFO ------------\n");
	return 0;
}

static int debugfs_open(struct inode *inode, struct file *file)
{
	return single_open(file, debugfs_show, inode->i_private);
}

extern struct hwspinlock *hwspin_lock_lookup(unsigned int id);
static ssize_t
debugfs_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
	struct hwspinlock *__hwlock;
	char buf[128];
	char *cmd = NULL;
	char *_cmd = NULL;
	int id;
	int timeout;
	int unlock;
	int ret ;

	if (NULL == ubuf || 0 == cnt){
		pr_err("buf is null !\n");
		return (-EINVAL);
	}
	if(cnt > sizeof(buf))
	{
		pr_err("input count larger! \n");
		return (-ENOMEM);
	}

	if (copy_from_user(buf, ubuf, cnt - 1)) {
		pr_err("[Hwspinlock Debugfs] can not copy from user\n");
		cnt = -EINVAL;
		goto out;
	}

	buf[cnt - 1] = '\0';
	cmd = buf;
	_cmd = buf;
	pr_debug("[Hwspinlock Debugfs] [cmd: %s[cnt: %d]]\n", cmd, (int)cnt);

	if (!strncmp("request ", _cmd, strlen("request "))) {
		cmd = cmd + strlen("request ");
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;
		*_cmd = '\0';

		if (kstrtos32(cmd, 10, &id)) {
			pr_err("Hwspinlock Debugfs cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		hwlock = hwspin_lock_request_specific(id);
		if (!hwlock)
			pr_err("hwspinlock %u is already in use\n", id);
		else
			pr_info("[debug] Request hwspinlock %d sucess!",id);
	} else if (!strncmp("free_lock ", _cmd, strlen("free_lock "))) {
		cmd = cmd + strlen("free_lock ");
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;
		*_cmd = '\0';
		if (kstrtos32(cmd, 10, &id)) {
			pr_err("Hwspinlock Debugfs cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		if (!hwlock){
			__hwlock = hwspin_lock_lookup(id);
			if (__hwlock){
				debugfs_hwspinlock_lock_free(__hwlock);
				__hwlock = NULL;
			}else{
				pr_err("Current haven't requested the hwspinlock %d\n",id);
				goto out;
			}
		}else if (hwlock_to_id(hwlock) == id){
			debugfs_hwspinlock_lock_free(hwlock);
			hwlock = NULL;
		}else
			pr_err("[debug] please freelock the correct lock!\n");
	} else if (!strncmp("trylock ", _cmd, strlen("trylock "))) {
		cmd = cmd + strlen("trylock ");
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;

		if ('\0' == *_cmd) {
			pr_err("[debug] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}
		*_cmd = '\0';

		if (kstrtos32(cmd, 10, &id)) {
			pr_err("[debug] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		cmd = _cmd + 1;
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;
		*_cmd = '\0';
		if (kstrtos32(cmd, 10, &timeout)) {
			pr_err("[debug] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		cmd = _cmd + 1;
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;
		*_cmd = '\0';

		if (kstrtos32(cmd, 10, &unlock)) {
			pr_err("[debug] cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

		if (!hwlock){
			pr_err("Current haven't requested the hwspinlock %d\n",id);
			goto out;
		}else if (hwlock_to_id(hwlock) == id && timeout >= 0){
			ret =debugfs_hwspinlock_trylock_timeout(id, timeout, unlock);
			if (!ret){
				if (0 == timeout)
					pr_info("[debug] hwspin_trylock %d sucess!\n",id);
				else
					pr_info("[debug] hwspin_trylock_timout %d sucess!\n",id);
			}
		}else if(timeout < 0)
			pr_err("[debug] cmd err! timeout must > 0\n");
		else
			pr_err("[debug] please trylock the correct lock!\n");
	}else if (!strncmp("unlock ", _cmd, strlen("unlock "))) {
		cmd = cmd + strlen("unlock ");
		_cmd = cmd;
		while ((' ' != *_cmd) && ('\0' != *_cmd))
			_cmd++;
		*_cmd = '\0';
		if (kstrtos32(cmd, 10, &id)) {
			pr_err("Hwspinlock Debugfs cmd error\n");
			cnt = -EINVAL;
			goto out;
		}

                if (!hwlock){
			pr_err("Current don't echo request the hwspinlock %d\n",id);
			goto out;
		}else if(hwlock_to_id(hwlock) == id && locked == 1){
			hwspin_unlock(hwlock);
			pr_info("[debug] hwspin_unlock id=%d sucess!\n",id);
		}else
			pr_err("[debug] please free the correct request lock!\n");
	} else {
		pr_err("Hwspinlock Debugfs cmd error\n");
		cnt = -EINVAL;
	}
out:
	return cnt;
}

static const struct file_operations hwspinlock_debugfs_ops = {
	.open		= debugfs_open,
	.read		= seq_read,
	.write		= debugfs_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init hwspinlock_debugfs_init(void)
{
	hwspinlock_debug_dir = debugfs_create_dir("hwspinlock", NULL);
	if (hwspinlock_debug_dir)
		hwspinlock_fn = debugfs_create_file("debug", S_IRUGO,
			hwspinlock_debug_dir, NULL, &hwspinlock_debugfs_ops);

	return 0;
}
module_init(hwspinlock_debugfs_init);

static void __exit hwspinlock_debugfs_exit(void)
{
	debugfs_remove(hwspinlock_fn);
	debugfs_remove(hwspinlock_debug_dir);

	return;
}
module_exit(hwspinlock_debugfs_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hwspinlock debugfs driver for hisi");
MODULE_AUTHOR("z00241933 <zhaokai1@hisilicon.com>");
