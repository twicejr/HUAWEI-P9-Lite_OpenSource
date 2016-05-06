/*
 * blackbox. (kernel run data recorder.)
 *
 * Copyright (c) 2013 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/uaccess.h>
#include <linux/rtc.h>
#include <linux/syscalls.h>
#include <linux/io.h>
#include <linux/stat.h>
#include <linux/string.h>

#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/util.h>
#include "rdr_inner.h"
#include "rdr_field.h"
#include "rdr_print.h"

struct linux_dirent {
	unsigned long d_ino;
	unsigned long d_off;
	unsigned short d_reclen;
	char d_name[1];
};

static int rdr_rm_dir(char *path);

static int __rdr_create_dir(char *path)
{
	int fd;
	mm_segment_t old_fs;

	/* BB_PRINT_START(); */
	if (path == NULL) {
		BB_PRINT_PN("invalid  parameter. path:%p.\n", path);
		BB_PRINT_END();
		return -1;
	}
	old_fs = get_fs();
	set_fs(KERNEL_DS);

	fd = sys_access(path, 0);
	if (0 != fd) {
		BB_PRINT_DBG("rdr: need create dir %s !\n", path);
		fd = sys_mkdir(path, DIR_LIMIT);
		if (fd < 0) {
			BB_PRINT_ERR("rdr: create dir %s failed! ret = %d\n",
				     path, fd);
			set_fs(old_fs);
			BB_PRINT_END();
			return fd;
		}
		BB_PRINT_DBG("rdr: create dir %s successed [%d]!!!\n", path,
			     fd);
	}

	set_fs(old_fs);

	/* BB_PRINT_END(); */
	return 0;
}

/*
 * func name: rdr_create_dir
 * .
 * func args:
 *  char*  path,
 * return
 *	<0 fail
 *	0  success
 */
static int rdr_create_dir(const char *path)
{
	char cur_path[64];
	int index = 0;

	BB_PRINT_START();
	if (path == NULL) {
		BB_PRINT_PN("invalid  parameter. path:%p\n", path);
		BB_PRINT_END();
		return -1;
	}
	memset(cur_path, 0, 64);
	if (*path != '/')
		return -1;
	cur_path[index++] = *path++;

	while (*path != '\0') {
		if (*path == '/')
			__rdr_create_dir(cur_path);
		cur_path[index] = *path;
		path++;
		index++;
	}

	BB_PRINT_END();
	return 0;
}

#ifdef CONFIG_PROC_POSTFSDATA
extern int wait_for_postfsdata(unsigned int timeout);
#endif

/*
 * func name: rdr_wait_partition
 * .
 * func args:
 *  char*  path,			path of watit file.
 *  u32 timeouts,       time out.
 * return
 *	<0 fail
 *	0  success
 */
int rdr_wait_partition(char *path, int timeouts)
{
	struct kstat m_stat;
	mm_segment_t old_fs;
	int timeo;
	/* BB_PRINT_START(); */

	if (path == NULL) {
		BB_PRINT_PN("invalid  parameter. path:%p\n", path);
		BB_PRINT_END();
		return -1;
	}
#ifdef CONFIG_PROC_POSTFSDATA
	if (0 == strncmp(path, "/data", strlen("/data")))
		wait_for_postfsdata(0);
#endif
	timeo = timeouts;

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	/* rdr_debug("wait for %s ready ...", path); */

	while (0 != vfs_stat(path, &m_stat)) {
		current->state = TASK_INTERRUPTIBLE;
		(void)schedule_timeout(HZ / 10);	/*wait for 1/10 second */
		if (timeouts-- < 0) {
			set_fs(old_fs);
			BB_PRINT_DBG("rdr:wait partiton[%s] fail. use [%d]'s . skip!\n",
			     path, timeo);
			/* BB_PRINT_END(); */
			return -1;
		}
	}
	set_fs(old_fs);

	/* BB_PRINT_END(); */
	return 0;
}

int rdr_create_epath_bc(u64 core, char *path)
{
	char date[DATATIME_MAXLEN];
	int index = 0;
	int ret = 0;
	int invalid_date = 1;
	int len = 0;
	struct rdr_struct_s *pbb = rdr_get_tmppbb();

	BB_PRINT_START();
	if (!check_himntn(HIMNTN_GOBAL_RESETLOG))
		return -1;
	if (pbb == NULL || path == NULL) {
		BB_PRINT_PN("invalid  parameter.\n");
		BB_PRINT_END();
		return -1;
	}

	pbb->base_info.datetime[DATATIME_MAXLEN - 1] = '\0';
	BB_PRINT_PN("Address of temp BBox [%p], and datetime[%s]\n", pbb,
		    pbb->base_info.datetime);
	memset(date, 0, DATATIME_MAXLEN);
	len = strlen(pbb->base_info.datetime);
	if (DATATIME_MAXLEN > len && len != 0) {
		strncpy(date, pbb->base_info.datetime, DATATIME_MAXLEN - 1);
		date[DATATIME_MAXLEN - 1] = '\0';
		while (index < len) {
			if ((date[index] > '9' || date[index] < '0')
			    && date[index] != '-') {
				invalid_date = 1;
				BB_PRINT_DBG("get date buf[%s] invalid.\n",
					     date);
				break;
			}
			index++;
		}
	} else {
		invalid_date = 1;
	}

	if (invalid_date) {
		memset(date, 0, DATATIME_MAXLEN);
		snprintf(date, DATATIME_MAXLEN, "%s-%08lld",
			 rdr_get_timestamp(), rdr_get_tick());
		snprintf(path, PATH_MAXLEN, "%s%s/", PATH_ROOT, date);
		BB_PRINT_DBG("date buf error, cur log path:[%s].\n", path);
	} else {
		snprintf(path, PATH_MAXLEN, "%s%s/", PATH_ROOT,
			 pbb->base_info.datetime);
		BB_PRINT_DBG("log path[%s].\n", path);
	}

	ret = rdr_create_dir(path);
	BB_PRINT_END();

	return ret;
}

int rdr_create_exception_path(struct rdr_exception_info_s *e,
			      char *path, char *date)
{
	int ret = 0;

	BB_PRINT_START();
	if (!check_himntn(HIMNTN_GOBAL_RESETLOG))
		return -1;

	if (e == NULL || path == NULL || date == NULL) {
		BB_PRINT_PN("invalid  parameter. e:%p\n", e);
		BB_PRINT_END();
		return ret = -1;
	}
	memset(date, 0, DATATIME_MAXLEN);
	snprintf(date, DATATIME_MAXLEN, "%s-%08lld",
		 rdr_get_timestamp(), rdr_get_tick());

	memset(path, 0, PATH_MAXLEN);
	snprintf(path, PATH_MAXLEN, "%s%s/", PATH_ROOT, date);

	ret = rdr_create_dir(path);
	BB_PRINT_END();
	return ret;
}

static LIST_HEAD(__rdr_logpath_info_list);
static DEFINE_SPINLOCK(__rdr_logpath_info_list_lock);
struct logpath_info_s {
	struct list_head s_list;
	struct timespec ctime;
	u64 logpath_tm;
	char path[32];
};

struct RDR_LOG_TM_RANGE {
	char name[10];
	int idx[2];		/*start, len */
	int rg[2];		/*min, max */
};

const struct RDR_LOG_TM_RANGE tbl_rdr_logdir_tm_rg[] = {
/*	name		idx{start,len}	rg{min,max}*/
	{"year", {0, 4}, {1900, 2200} },
	{"month", {4, 2}, {1, 12} },
	{"day", {6, 2}, {1, 31} },
	{"hour", {8, 2}, {0, 23} },
	{"minute", {10, 2}, {0, 59} },
	{"second", {12, 2}, {0, 59} },
};

int rdr_is_logdir_nm_tm(char *buf, int len)
{
	int i;
	char tempstr[10];
	int val;
	const struct RDR_LOG_TM_RANGE *pt_rg;

	pt_rg = (const struct RDR_LOG_TM_RANGE *)&tbl_rdr_logdir_tm_rg;

	/* Judge if all char is number */
	for (i = 0; i < len; i++) {
		if (buf[i] > '9' || buf[i] < '0') {
			return 0;
		}
	}
	/* Judge all field range */
	for (i = 0; i < ARRAY_SIZE(tbl_rdr_logdir_tm_rg); i++, pt_rg++) {
		memcpy(tempstr, buf + pt_rg->idx[0], pt_rg->idx[1]);
		tempstr[pt_rg->idx[1]] = 0;
		if (1 != sscanf(tempstr, "%d", &val)) {
			BB_PRINT_ERR("[%s], val get failed!\n", __func__);
			return 0;
		}
		BB_PRINT_DBG("%s, val = %d, <%d,%d>\n", pt_rg->name, val,
			     pt_rg->rg[0], pt_rg->rg[1]);
		if (val < pt_rg->rg[0] || val > pt_rg->rg[1]) {
			return 0;
		}
	}
	return 1;
}

u64 rdr_cal_tm_from_logdir_name(char *path)
{
	char sec[15];
	static u64 date_sec; /* default value is 0 */

	strncpy(sec, path, 15);
	sec[14] = 0;
	if (rdr_is_logdir_nm_tm(sec, 14)) {
		if (1 != sscanf(sec, "%lld", &date_sec)) {
			BB_PRINT_ERR("[%s], date_sec get failed!\n", __func__);
		}
	} else {
		date_sec++;	/* when dir name error, it is a little bigger than perv */
	}
	BB_PRINT_DBG("[%s], date_sec = %lld\n", __func__, date_sec);
	return date_sec;
}

/*******************************************************************************
Function:       bbox_clear_notexist_logpath
Description:    if a logpath is in list, but is not exist.
                need del logpath from list.
Input:          NA
Output:         NA
Return:         NA
********************************************************************************/
static void bbox_clear_notexist_logpath(void)
{
	struct logpath_info_s *p_info = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	char fullname[PATH_MAXLEN];
	struct kstat m_stat;
	mm_segment_t old_fs;

	BB_PRINT_START();

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	spin_lock(&__rdr_logpath_info_list_lock);
	list_for_each_safe(cur, next, &__rdr_logpath_info_list) {
		p_info = list_entry(cur, struct logpath_info_s, s_list);
		if (p_info == NULL) {
			BB_PRINT_ERR("It might be better to look around here.\n");
			continue;
		}

		memset(fullname, 0, PATH_MAXLEN);
		snprintf(fullname, PATH_MAXLEN, "%s%s", PATH_ROOT, p_info->path);

		/* if dir in list is not exist,
		 * del the dir from list
		 */
		if (0 != vfs_stat(fullname, &m_stat)) {
			BB_PRINT_ERR("[%s] is not exist, need list_del(cur)\n", fullname);
			list_del(cur);
			kfree(p_info);
		}
	}
	spin_unlock(&__rdr_logpath_info_list_lock);

	set_fs(old_fs);

	BB_PRINT_END();
	return ;
}

void rdr_check_logpath_repeat(struct logpath_info_s *info)
{
	struct logpath_info_s *p_info = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	/*BB_PRINT_START();*/
	spin_lock(&__rdr_logpath_info_list_lock);
	list_for_each_safe(cur, next, &__rdr_logpath_info_list) {
		p_info = list_entry(cur, struct logpath_info_s, s_list);
		if (p_info == NULL) {
			BB_PRINT_DBG
			    ("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}
		/*BB_PRINT_DBG("i am here. [%s][%s]\n", info->path, p_info->path);*/
		if (0 == memcmp(info->path, p_info->path, strlen(info->path))) {
			/*BB_PRINT_DBG("delete it. [%s][%s]\n", info->path, p_info->path);*/
			list_del(cur);
			kfree(p_info);
		}
	}

	spin_unlock(&__rdr_logpath_info_list_lock);
	/*BB_PRINT_END();*/
	return;
}

/*kernel/drivers/input/ate.c*/
u32 __rdr_add_logpath_list(struct logpath_info_s *info)
{
	struct logpath_info_s *p_info = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	/*BB_PRINT_START();*/
	spin_lock(&__rdr_logpath_info_list_lock);

	if (list_empty(&__rdr_logpath_info_list)) {
		list_add_tail(&info->s_list, &__rdr_logpath_info_list);
		BB_PRINT_END();
		goto out;
	}
	p_info = list_entry(__rdr_logpath_info_list.next,
			    struct logpath_info_s, s_list);
	if (info->logpath_tm >= p_info->logpath_tm) {
		list_add(&info->s_list, &__rdr_logpath_info_list);
		/*BB_PRINT_END();*/
		goto out;
	}
	list_for_each_safe(cur, next, &__rdr_logpath_info_list) {
		p_info = list_entry(next, struct logpath_info_s, s_list);
		if (p_info == NULL) {
			BB_PRINT_ERR("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}
		if (0 == memcmp(info->path, p_info->path, strlen(info->path))) {
			p_info->ctime.tv_sec = info->ctime.tv_sec;
			p_info->ctime.tv_nsec = info->ctime.tv_nsec;
			/*BB_PRINT_ERR("It might be better to look around here. %s:%d\n",
			      __func__, __LINE__);*/
		}
		if (info->logpath_tm >= p_info->logpath_tm) {
			list_add(&info->s_list, cur);
			/*BB_PRINT_END();*/
			goto out;
		}
	}
	list_add_tail(&info->s_list, &__rdr_logpath_info_list);
	/*BB_PRINT_END();*/
out:
	spin_unlock(&__rdr_logpath_info_list_lock);
	return 0;
}

void rdr_add_logpath_list(char *path, struct timespec *time)
{
	struct logpath_info_s *lp_info = NULL;
	/*BB_PRINT_START();*/
	lp_info = kmalloc(sizeof(struct logpath_info_s), GFP_ATOMIC);

	if (lp_info == NULL) {
		BB_PRINT_PN("kmalloc logpath_info_s faild.\n");
		return;
	}

	memset(lp_info, 0, sizeof(struct logpath_info_s));
	memcpy(lp_info->path, path, strlen(path));
	lp_info->ctime.tv_sec = time->tv_sec;
	lp_info->ctime.tv_nsec = time->tv_nsec;
	lp_info->logpath_tm = rdr_cal_tm_from_logdir_name(lp_info->path);

	rdr_check_logpath_repeat(lp_info);
	__rdr_add_logpath_list(lp_info);
	/*BB_PRINT_END();*/
}

int bbox_chown(const char *path, uid_t user, gid_t group, bool recursion)
{
	int fd = -1, bpos, count, ret = 0;
	char buf[1024];
	int bufsize;
	struct linux_dirent *d;
	char d_type;
	char fullname[PATH_MAXLEN];
	mm_segment_t old_fs;

	BB_PRINT_DBG("[%s], enter, path:%s\n", __func__, path);
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	ret = (int)sys_chown((const char __user *)path, user, group);
	if (ret) {
		BB_PRINT_ERR("[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
		     __func__, path, user, group, ret);
	}

	if (!recursion) {
		goto not_recursion;
	}

	fd = sys_open(path, O_RDONLY, DIR_LIMIT);
	if (fd < 0) {
		BB_PRINT_ERR("[%s], open %s fail, ret:%d\n", __func__, path,
			     fd);
		set_fs(old_fs);
		BB_PRINT_END();
		return -1;
	}

	for (count = 0; count < 1000; count++) {	/*防止死循环 */
		bufsize = sys_getdents(fd, (struct linux_dirent *)buf, 1024);
		if (bufsize == -1) {
			BB_PRINT_ERR("[%s], sys_getdents failed, ret [%d]\n",
				     __func__, bufsize);
			goto out;
		}

		if (bufsize == 0) {
			/*处理结束 */
			goto out;
		}

		for (bpos = 0; bpos < bufsize; bpos += d->d_reclen) {
			d = (struct linux_dirent *)(buf + bpos);
			d_type = *(buf + bpos + d->d_reclen - 1);
			snprintf(fullname, sizeof(fullname), "%s/%s", path,
				 d->d_name);

			if (d_type == DT_DIR
			    && strncmp(d->d_name, ".", sizeof("."))
			    && strncmp(d->d_name, "..", sizeof(".."))) {	/*处理目录，过滤"."和".."目录，否则会无限递归 */
				/*递归修改目录及子目录的属主及属组 */
				ret = (int)bbox_chown((const char __user *)
						      fullname, user, group,
						      true);
				if (ret) {
					BB_PRINT_ERR("[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
					     __func__, fullname, user, group,
					     ret);
				}
			} else if (d_type == DT_REG) {	/*处理文件 */
				ret = (int)sys_chown((const char __user *)
						     fullname, user, group);
				if (ret) {
					BB_PRINT_ERR("[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
					     __func__, fullname, user, group,
					     ret);
				}
			}
		}
	}
	if (1000 == count) {
		BB_PRINT_ERR("[%s], [%s] failed, ret [%d]\n", __func__, path,
			     bufsize);
	}
out:
	if (fd >= 0) {
		sys_close(fd);
	}
not_recursion:
	set_fs(old_fs);
	return 0;
}

void rdr_print_all_logpath(void)
{
	int index = 1;
	struct logpath_info_s *p_module_ops = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;

	BB_PRINT_START();
	spin_lock(&__rdr_logpath_info_list_lock);
	list_for_each_safe(cur, next, &__rdr_logpath_info_list) {
		p_module_ops = list_entry(cur, struct logpath_info_s, s_list);
		if (p_module_ops == NULL) {
			BB_PRINT_DBG("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}
		BB_PRINT_DBG("==========[%.2d]-start==========\n", index);
		BB_PRINT_DBG(" path:    [%s]\n", p_module_ops->path);
		BB_PRINT_DBG(" ctime:   [0x%llx]\n",
			     (u64) (p_module_ops->ctime.tv_sec));
		BB_PRINT_DBG("==========[%.2d]-e n d==========\n", index);
	}
	spin_unlock(&__rdr_logpath_info_list_lock);

	BB_PRINT_END();
	return;
}

char *known[] = {
	"",
};

char *ignore[] = {
	".",
	"..",
	PATH_MEMDUMP,
	"running_trace",
	"history.log",
	"reboot_times.log",
};

int rdr_dump_init(void)
{
	int ret = 0;

	while (rdr_wait_partition("/data/lost+found", 1000) != 0)
		;

	/* 提前检查并设置版本信息 */
	(void)bbox_check_edition();

	ret = rdr_create_dir(PATH_ROOT);
	if (ret) {
		return ret;
	}

	/*根据权限要求，hisi_logs目录及子目录群组调整为root-system */
	ret = (int)bbox_chown((const char __user *)PATH_ROOT, ROOT_UID,
			    SYSTEM_GID, true);
	if (ret) {
		BB_PRINT_ERR("[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
		     __func__, PATH_ROOT, ROOT_UID, SYSTEM_GID, ret);
	}

	return 0;
}

void rdr_dump_exit(void)
{
}

int rdr_check_logpath_legality(char *path)
{
	int ret = 1;		/*0 => ignore. !0 => process.*/
	int size;
	int index;

	/*BB_PRINT_START();*/
	size = sizeof(ignore) / sizeof(char *);
	for (index = 0; index < size; index++) {
		if (0 == strncmp(path, ignore[index], strlen(path))) {
			/*BB_PRINT_DBG("ignore list hit [%s]\n", path);*/
			/*BB_PRINT_END();*/
			ret = -1;
			goto out;
		}
	}

	size = DATA_MAXLEN + TIME_MAXLEN + 1;
	for (index = 0; path[index] != '\0' && index < size; index++) {
		if (path[index] < '0' || path[index] > '9') {
			if (index == DATA_MAXLEN && path[index] == '-')
				continue;
			BB_PRINT_DBG("invalid path [%s]\n", path);
			BB_PRINT_END();
			ret = 0;
			goto out;
		}
	}
	/*BB_PRINT_DBG("legality path [%s] pass...\n", path);*/
	/*BB_PRINT_END();*/
out:
	return ret;
}

int rdr_dir_size(char *path, bool recursion)
{
	/*DT_DIR, DT_REG */
	int fd = -1, bpos, ret = 0;
	char buf[1024];
	int bufsize;
	struct linux_dirent *d;
	char d_type;
	char fullname[PATH_MAXLEN];
	struct kstat stat;
	u32 size = 0;

	/*BB_PRINT_START();*/

	fd = sys_open(path, O_RDONLY, DIR_LIMIT);
	if (fd < 0) {
		BB_PRINT_ERR("rdr:%s(),open %s fail,r:%d\n", __func__, path,
			     fd);
		BB_PRINT_END();
		goto out;
	}

	memset(&stat, 0, sizeof(struct kstat));
	if (0 != vfs_stat(path, &stat)) {
		BB_PRINT_ERR("stat failed :[%s]\n", fullname);
	}
	size += stat.size;

	for (;;) {
		bufsize = sys_getdents(fd, (struct linux_dirent *)buf, 1024);
		/* NOTE: should that bufsize is negative be the judgement? */
		if (bufsize == -1) {
			BB_PRINT_ERR("rdr:%s():sys_getdents failed\n",
				     __func__);
			break;
		}

		if (bufsize == 0) {
			/*BB_PRINT_DBG("rdr:%s():sys_getdents [%s] end.\n", __func__, path);*/
			break;
		}

		for (bpos = 0; bpos < bufsize; bpos += d->d_reclen) {
			d = (struct linux_dirent *)(buf + bpos);
			d_type = *(buf + bpos + d->d_reclen - 1);
			memset(&stat, 0, sizeof(struct kstat));
			snprintf(fullname, sizeof(fullname), "%s/%s", path,
				 d->d_name);
			if (0 != vfs_stat(fullname, &stat)) {
				BB_PRINT_ERR("stat failed :[%s]\n", fullname);
			}
			/*BB_PRINT_DBG("fullname:%s\n", fullname);*/
			if (d_type == DT_DIR) {
				ret = rdr_check_logpath_legality(d->d_name);
				if (ret == -1) {
					/*BB_PRINT_DBG("check legality: ignore.\n");*/
					continue;
				}
				if (!recursion && ret == 0) {
					BB_PRINT_DBG("check legality: invalid\n");
					if (!recursion)
						rdr_rm_dir(fullname);
					continue;
				}

				if (recursion) {
					size += rdr_dir_size(fullname, recursion);
				} else {
					/*size += stat.size; */
					rdr_add_logpath_list(d->d_name,
							     &stat.ctime);
				}
				/*BB_PRINT_DBG("DIR\n");*/
			} else if (d_type == DT_REG) {
				/*BB_PRINT_DBG("stat.size:   [%lld]\n", stat.size);*/
				/*BB_PRINT_DBG("stat.atime:  [0x%x]\n", stat.atime.tv_sec);*/
				size += stat.size;
				/*BB_PRINT_DBG("REG\n");*/
			}
		}
	}
	/*BB_PRINT_END();*/
out:
	if (fd >= 0)
		sys_close(fd);
	/*BB_PRINT_DBG("path:[%s] size:[0x%x].\n", path, size);*/
	return size;
}

void rdr_count_size(void)
{
	struct logpath_info_s *p_info = NULL;
	struct list_head *cur = NULL;
	struct list_head *next = NULL;
	u32 size = 0;
	u32 tmpsize = 0;
	bool oversize = false;
	char fullname[PATH_MAXLEN];
	mm_segment_t old_fs;
	int ret;

	BB_PRINT_START();

	bbox_clear_notexist_logpath();
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	size += rdr_dir_size(PATH_ROOT, false);
	list_for_each_safe(cur, next, &__rdr_logpath_info_list) {
		p_info = list_entry(cur, struct logpath_info_s, s_list);
		if (p_info == NULL) {
			list_del(cur);
			BB_PRINT_ERR("It might be better to look around here. %s:%d\n",
			     __func__, __LINE__);
			continue;
		}

		memset(fullname, 0, PATH_MAXLEN);
		snprintf(fullname, PATH_MAXLEN, "%s%s", PATH_ROOT,
			 p_info->path);

		if (oversize) {
			BB_PRINT_DBG("over size: cur[0x%x], max[0x%llx]\n",
				     size, rdr_get_logsize());
			list_del(cur);
			rdr_rm_dir(fullname);
			kfree(p_info);
			continue;
		}

		/* 递归检查目录大小，超过指定大小则删除之后的日志目录，同上if (oversize)。 */
		tmpsize = rdr_dir_size(fullname, true);
		if (tmpsize + size > rdr_get_logsize()) {
			oversize = true;
			BB_PRINT_DBG("over size: cur[0x%x], next[0x%x],max[0x%llx]\n",
			     size, tmpsize, rdr_get_logsize());
			list_del(cur);
			rdr_rm_dir(fullname);
			kfree(p_info);
		} else {
			size += tmpsize;
		}
	}

	/*根据权限要求，hisi_logs目录及子目录群组调整为root-system */
	ret = (int)bbox_chown((const char __user *)PATH_ROOT, ROOT_UID,
			    SYSTEM_GID, true);
	if (ret) {
		BB_PRINT_ERR("[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
		     __func__, PATH_ROOT, ROOT_UID, SYSTEM_GID, ret);
	}

	rdr_print_all_logpath();
	set_fs(old_fs);
	BB_PRINT_END();
	return;
}

static int rdr_rm_file(char *fullname)
{
	BB_PRINT_START();
	BB_PRINT_DBG("rdr:%s():delete file [%s]\n", __func__, fullname);
	sys_unlink(fullname);
	BB_PRINT_END();
	return 0;
}

static int __rdr_rm_dir(char *path)
{
	char *pdst = path;
	int ret = 0;
	BB_PRINT_START();
	BB_PRINT_DBG("rdr:%s():delete path [%s]\n", __func__, path);

	while (*pdst)
		pdst++;
	pdst--;
	if (*pdst == '/')
		*pdst = '\0';
	ret = sys_rmdir(path);
	if (ret != 0)
		BB_PRINT_DBG("rdr:%s():del %s failed. ret[%d]\n", __func__,
			     path, ret);
	BB_PRINT_END();
	return ret;
}

static int rdr_rm_dir(char *path)
{
	int fd = -1, bpos;
	char buf[1024];
	int bufsize;
	struct linux_dirent *d;
	char d_type;
	char fullname[PATH_MAXLEN];
	int ret = 0;

	fd = sys_open(path, O_RDONLY, DIR_LIMIT);
	if (fd < 0) {
		BB_PRINT_ERR("rdr:%s(),open %s fail,r:%d\n", __func__, path,
			     fd);
		BB_PRINT_END();
		ret = -1;
		goto out;
	}

	for (;;) {
		bufsize = sys_getdents(fd, (struct linux_dirent *)buf, 1024);
		if (bufsize == -1) {
			BB_PRINT_ERR("rdr:%s():sys_getdents failed\n",
				     __func__);
			break;
		}

		if (bufsize == 0) {
			break;
		}

		for (bpos = 0; bpos < bufsize; bpos += d->d_reclen) {
			d = (struct linux_dirent *)(buf + bpos);
			d_type = *(buf + bpos + d->d_reclen - 1);
			snprintf(fullname, sizeof(fullname), "%s/%s", path,
				 d->d_name);
			if (d_type == DT_DIR) {
				if (rdr_check_logpath_legality(d->d_name) == -1) {
					/*BB_PRINT_DBG("check legality: ignore.\n");*/
					continue;
				}
				rdr_rm_dir(fullname);
			} else if (d_type == DT_REG) {
				rdr_rm_file(fullname);
			}
		}
	}
out:
	__rdr_rm_dir(path);
	if (fd >= 0)
		sys_close(fd);
	return ret;
}
