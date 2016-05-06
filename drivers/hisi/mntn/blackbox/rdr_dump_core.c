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
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/stat.h>
#include <linux/string.h>

#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/util.h>
#include "rdr_inner.h"
#include "rdr_print.h"
#include "rdr_field.h"

/*
 * func name: rdr_save_history_log
 * save exce info to history.log .
 * func args:
 *  struct rdr_exception_info_s,	exec info.
 *  char*,                          path.
 * return
 *	!0   fail
 *	== 0 success
 */
#define HISTORY_LOG_SIZE 256
#define HISTORY_LOG_MAX  0x400000	/*64*16*1024*4 = 4M */
int rdr_save_history_log(struct rdr_exception_info_s *p, char *date,
			 bool is_save_done)
{
	int ret = 0;
	char buf[HISTORY_LOG_SIZE];
	struct kstat historylog_stat;
	mm_segment_t old_fs;
	char local_path[PATH_MAXLEN];
	char* reboot_from_ap;

	if (!check_himntn(HIMNTN_GOBAL_RESETLOG)) {
		return 0;
	}
	BB_PRINT_START();
	if (DATATIME_MAXLEN < (strlen(date) + 1)) {
		date[DATATIME_MAXLEN - 1] = '\0';
	}
	memset(buf, 0, HISTORY_LOG_SIZE);
	
	if(p->e_reset_core_mask & RDR_AP)
		reboot_from_ap = "true";
	else
		reboot_from_ap = "false";
	/*如果此次复位是走简易流程的，则正常记录，否则需要增加last_save_not_done字符串 */
	if (is_save_done) {
		snprintf(buf, HISTORY_LOG_SIZE,
			 "system exception core [%s], reason [%s], time [%s], sysreboot[%s]\n",
			 rdr_get_exception_core(p->e_from_core),
			 rdr_get_exception_type(p->e_exce_type), date, reboot_from_ap);
	} else {
		snprintf(buf, HISTORY_LOG_SIZE,
			 "system exception core [%s], reason [%s], time [%s][last_save_not_done], sysreboot[%s]\n",
			 rdr_get_exception_core(p->e_from_core),
			 rdr_get_exception_type(p->e_exce_type), date, reboot_from_ap);
	}

	memset(local_path, 0, PATH_MAXLEN);
	snprintf(local_path, PATH_MAXLEN, "%s/%s", PATH_ROOT, "history.log");

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	if (0 == vfs_stat(local_path, &historylog_stat) &&
	    historylog_stat.size > HISTORY_LOG_MAX) {
		sys_unlink(local_path);	/* delete history.log */
	}

	if (0 != vfs_stat(PATH_ROOT, &historylog_stat)) {
		ret = rdr_dump_init();
		if (ret) {
			BB_PRINT_ERR("%s():rdr_create_dir fail\n", __func__);
			set_fs(old_fs);
			return ret;
		}
	}

	set_fs(old_fs);

	rdr_savebuf2fs(PATH_ROOT, "history.log", buf, strlen(buf), 1);
	BB_PRINT_END();
	return ret;
}

int rdr_save_history_log_for_undef_exception(struct rdr_syserr_param_s *p)
{
	int ret = 0;
	char buf[HISTORY_LOG_SIZE];
	struct kstat historylog_stat;
	mm_segment_t old_fs;
	char local_path[PATH_MAXLEN];

	if (!check_himntn(HIMNTN_GOBAL_RESETLOG)) {
		return 0;
	}
	BB_PRINT_START();
	memset(buf, 0, HISTORY_LOG_SIZE);
	snprintf(buf, HISTORY_LOG_SIZE,
		 "system exception undef. modid[0x%x], arg [0x%x], arg [0x%x].\n",
		 p->modid, p->arg1, p->arg2);

	memset(local_path, 0, PATH_MAXLEN);
	snprintf(local_path, PATH_MAXLEN, "%s/%s", PATH_ROOT, "history.log");

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	if (0 == vfs_stat(local_path, &historylog_stat) &&
	    historylog_stat.blksize > HISTORY_LOG_MAX) {
		sys_unlink(local_path);	/* delete history.log */
	}

	set_fs(old_fs);

	rdr_savebuf2fs(PATH_ROOT, "history.log", buf, strlen(buf), 1);
	BB_PRINT_END();
	return ret;
}

/*
 * func name: rdr_savebuf2fs
 * append(save) data to path.
 * func args:
 *  char*  path,			path of save file.
 *  void*  buf,             save data.
 *  u32 len,            data lenght.
 *  u32 is_append,      determine whether write with append
 * return
 *	>=len fail
 *	==len success
 */
int rdr_savebuf2fs(char *logpath, char *filename,
		   void *buf, u32 len, u32 is_append)
{
	int ret = 0, flags;
	struct file *fp;
	mm_segment_t old_fs;
	char path[PATH_MAXLEN];

	BB_PRINT_START();
	if (logpath == NULL || filename == NULL || buf == NULL || len <= 0) {
		BB_PRINT_PN("invalid  parameter. path:%p, name:%p buf:%p len:0x%x\n",
		     logpath, filename, buf, len);
		ret = -1;
		goto out2;
	}

	snprintf(path, PATH_MAXLEN, "%s/%s", logpath, filename);

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	flags = O_CREAT | O_RDWR | (is_append ? O_APPEND : O_TRUNC);
	fp = filp_open(path, flags, FILE_LIMIT);
	if (IS_ERR(fp)) {
		set_fs(old_fs);
		BB_PRINT_ERR("%s():create file %s err.\n", __func__, path);
		ret = -1;
		goto out2;
	}
	vfs_llseek(fp, 0L, SEEK_END);
	ret = vfs_write(fp, buf, len, &(fp->f_pos));
	if (ret != len) {
		BB_PRINT_ERR("%s():write file %s exception with ret %d.\n",
			     __func__, path, ret);
		ret = -1;
		goto out1;
	}

	vfs_fsync(fp, 0);
out1:
	filp_close(fp, NULL);

	/*根据权限要求，hisi_logs目录及子目录群组调整为root-system */
	ret = (int)bbox_chown((const char __user *)path, ROOT_UID,
				SYSTEM_GID, false);
	if (ret) {
		BB_PRINT_ERR("[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
		     __func__, path, ROOT_UID, SYSTEM_GID, ret);
	}
	set_fs(old_fs);
	BB_PRINT_END();
out2:
	return ret;
}

void rdr_save_cur_baseinfo(char *logpath)
{
	BB_PRINT_START();
	/* save pbb to fs */
	rdr_savebuf2fs(logpath, RDR_BIN, rdr_get_pbb(), rdr_get_pbb_size(), 0);

	BB_PRINT_END();
	return;
}

void rdr_save_last_baseinfo(char *logpath)
{
	BB_PRINT_START();
	/* save pbb to fs */
	rdr_savebuf2fs(logpath, RDX_BIN,
		       rdr_get_tmppbb(), rdr_get_pbb_size(), 0);

	BB_PRINT_END();
	return;
}
