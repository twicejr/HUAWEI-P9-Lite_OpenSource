/*
 * Implement file functions used to save log.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/unistd.h>
#include <linux/sort.h>
#include "mntn_filesys.h"

extern void sort(void *base, size_t num, size_t size,
		 int (*cmp_func) (const void *, const void *),
		 void (*swap_func) (void *, void *, int size));


int mntn_filesys_chown(const char *filename, uid_t user, gid_t group)
{
	int iret;
	mm_segment_t old_fs = 0;

	if (NULL == filename) {
		return 0;
	}
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	iret = (int)sys_chown((const char __user *)filename, user, group);
	set_fs(old_fs);
	return iret;
}


int mntn_filesys_rm_file(const char *fullname)
{
	int iret;
	mm_segment_t old_fs = 0;

	if (NULL == fullname) {
		return 0;
	}
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	iret = (int)sys_access(fullname, 0);
	if (0 == iret) {
		if (sys_unlink(fullname)) {
			MNTN_FILESYS_PRINT(KERN_ERR
					   "mntn_err: Fail to rm the file %s!\n",
					   fullname);
			set_fs(old_fs);
			return -1;
		}
	}
	set_fs(old_fs);
	return 0;
}


int mntn_filesys_rm_all_file(const char *path)
{
	struct kstat m_stat;
	int fd = -1;
	int nread = 0;
	int bpos = 0;
	int ret = 0;
	char *buf;
	struct linux_dirent *d;
	char fullname[MNTN_FILESYS_FNAME_LEN] = { 0 };
	mm_segment_t old_fs = 0;

	if (NULL == path) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: path is NULL when removing all files in dir\n");
		return -1;
	}
	buf = kmalloc(MNTN_FILESYS_DIR_ENTRY_SIZE, GFP_KERNEL);
	if (buf == NULL) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: fail to kmalloc when removing all files\n");
		return -1;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	/* check path , if path isnt exist, return. */
	ret = vfs_stat(path, &m_stat);
	if (ret) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: dir doesn't exist when removing all files, path %s\n",
				   path);
		ret = -1;
		goto oper_over2;
	}

	fd = sys_open(path, O_RDONLY, MNTN_FILESYS_DEFAULT_MODE);	/*create file */
	if (fd < 0) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: fail to open dir when removing all files, path %s,  fd %d\n",
				   path, fd);
		ret = -1;
		goto oper_over2;
	}

	nread = sys_getdents(fd, (struct linux_dirent *)buf,
			 MNTN_FILESYS_DIR_ENTRY_SIZE);
	if (nread == -1) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: fail to getdents when when removing all files\n");
		ret = -1;
		goto oper_over1;
	}

	for (bpos = 0; bpos < nread;) {
		d = (struct linux_dirent *)(buf + bpos);
		if (!strcmp(d->d_name, "..") || !strcmp(d->d_name, ".")) {
			bpos += d->d_reclen;
			continue;
		}

		strncat(fullname, path, strlen(path));
		if (strlen(fullname) + strlen(d->d_name) >=
		    MNTN_FILESYS_FNAME_LEN) {
			ret = -1;
			goto oper_over1;
		}
		strncat(fullname, d->d_name, strlen(d->d_name));
		ret = mntn_filesys_rm_file((const char *)fullname);
		if (ret) {
			MNTN_FILESYS_PRINT(KERN_ERR
					   "mntn_err: fail to mntn_filesys_rm_file\n");
		}
		memset(fullname, 0, sizeof(fullname));
		bpos += d->d_reclen;
	}

oper_over1:
	sys_close(fd);
oper_over2:
	set_fs(old_fs);
	kfree(buf);

	return ret;
}


int mntn_filesys_rm_dir(const char *dirname)
{
	char *pdst = (char *)dirname;
	int iret = 0;
	mm_segment_t old_fs = 0;

	if (NULL == dirname) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: dir is null , so fail to open it!\n");
		return -1;
	}
	while (*pdst) {
		pdst++;
	}
	pdst--;
	if (*pdst == '/') {
		*pdst = '\0';
	}
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	iret = sys_rmdir(dirname);
	if (iret != 0) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: Fail to remove the dir %s!, iret = %d\n",
				   dirname, iret);
	}
	set_fs(old_fs);
	return iret;
}


static int __mntn_filesys_create_dir(char *path, umode_t umode)
{
	int iret = 0;
	mm_segment_t old_fs = 0;

	if (NULL == path) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: dir is null , so fail to make it!\n");
		return -1;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	iret = sys_mkdir(path, umode);
	if (iret < 0) {
		set_fs(old_fs);
		return iret;
	}

	set_fs(old_fs);
	return 0;
}


int mntn_filesys_create_dir(const char *path, umode_t umode)
{
	char cur_path[MNTN_FILESYS_FNAME_LEN] = { 0 };
	int index = 0;
	int iret = 0;

	if (NULL == path) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: dir is null , so fail to make it!\n");
		return -1;
	}

	if (*path != '/') {
		return -1;
	}
	cur_path[index++] = *path++;

	while (*path != '\0') {
		if (*path == '/') {
			iret = __mntn_filesys_create_dir(cur_path, umode);
			/*the dir may exist if the result is not equal to 0, so needn't return */
			if (0 != iret && (iret != (-EEXIST))) {
				MNTN_FILESYS_PRINT(KERN_ERR
						   "mntn_err: Fail to create the dir %s!, result is %d\n",
						   cur_path, iret);
			}
		}
		cur_path[index] = *path;
		path++;
		index++;
	}
	return 0;
}


int mntn_filesys_dir_list(const char *path, char *pout_namelist, int cnt,
			  int type)
{
	struct kstat m_stat;
	int fd = -1;
	int nread = 0;
	int bpos = 0;
	int ret = 0;
	int tmp_cnt = 0;
	int ulen = 0;
	char *buf;
	char *ptmp = pout_namelist;
	char d_type;
	struct linux_dirent *d;
	mm_segment_t old_fs;

	if (NULL == pout_namelist || NULL == path) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn error: pointer is NULL when listing dir\n");
		return 0;
	}
	buf = kmalloc(MNTN_FILESYS_DIR_ENTRY_SIZE, GFP_KERNEL);
	if (buf == NULL) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: fail to kmalloc when when listing dir\n");
		return 0;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	/* check path , if path isnt exist, return. */
	ret = vfs_stat(path, &m_stat);
	if (ret) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: dir doesn't exist when when listing dir\n");
		goto oper_over2;
	}

	fd = sys_open(path, O_RDONLY, MNTN_FILESYS_DEFAULT_MODE);	/*create file */
	if (fd < 0) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: fail to open dir when when listing dir, fd %d\n",
				   fd);
		goto oper_over2;
	}

	nread = sys_getdents(fd, (struct linux_dirent *)buf,
			 MNTN_FILESYS_DIR_ENTRY_SIZE);
	if (nread == -1) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: fail to getdents when when listing dir\n");
		goto oper_over1;
	}

	for (bpos = 0; bpos < nread;) {
		if (ptmp > pout_namelist + cnt) {
			break;
		}
		d = (struct linux_dirent *)(buf + bpos);
		if (!strcmp(d->d_name, "..") || !strcmp(d->d_name, ".")) {
			bpos += d->d_reclen;
			continue;
		}

		d_type = *(buf + bpos + d->d_reclen - 1);
		if (d_type == type) {
			ulen =
			    (strlen(d->d_name) >
			     MNTN_FILESYS_PURE_DIR_NAME_LEN) ?
			    MNTN_FILESYS_PURE_DIR_NAME_LEN : strlen(d->d_name);
			strncat(ptmp, d->d_name, ulen);
			ptmp = ptmp + MNTN_FILESYS_PURE_DIR_NAME_LEN;
			tmp_cnt++;
		}
		bpos += d->d_reclen;
	}

oper_over1:
	sys_close(fd);
oper_over2:
	kfree(buf);
	set_fs(old_fs);

	return tmp_cnt;
}


int mntn_filesys_write_log(const char *pname, void *pbuf_vir, unsigned int ulen,
			   umode_t mode)
{
	int bytes = 0;
	long fd = 0;
	umode_t udefault = (0 == mode) ? MNTN_FILESYS_DEFAULT_MODE : mode;
	mm_segment_t old_fs = 0;
	int iret = 0;

	if (NULL == pname) {
		MNTN_FILESYS_PRINT(KERN_ERR "mntn_err: File name is NULL\n");
		return 0;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	/*create dir, no error if it has been created */
	iret = mntn_filesys_create_dir(pname, udefault);
	if (0 != iret) {
		MNTN_FILESYS_PRINT(KERN_ERR "mntn_err: Fail to create dir!\n");
	}

	fd = sys_open(pname, O_CREAT | O_RDWR, udefault);
	if (fd < 0) {
		MNTN_FILESYS_PRINT(KERN_ERR "mntn_err: Fail to open file %s\n",
				   pname);
	} else {
		sys_lseek((int)(fd), 0, 2);
		bytes = sys_write(fd, pbuf_vir, ulen);
		if (bytes != ulen) {
			MNTN_FILESYS_PRINT(KERN_ERR
					   "mntn_err: Fail to write all the data into the file %s, %d/%d\n",
					   pname, bytes, ulen);
		}
		iret = sys_fsync(fd);
		if (iret < 0) {
			MNTN_FILESYS_PRINT(KERN_ERR
					   "mntn_err: Fail to sys_fsync data when saving log\n");
		}
		sys_close(fd);
	}
	set_fs(old_fs);
	return bytes;
}


int mntn_str_cmp(const void *a, const void *b)
{
	if (NULL == a || NULL == b) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: pointer a or pointer b is null!\n");
		return -1;
	}

	return strncmp((char *)a, (char *)b, MNTN_FILESYS_PURE_DIR_NAME_LEN);
}


void mntn_rm_old_log(const char *ppath, unsigned int unumber)
{
	char fullpath_arr[128 + 1] = { 0 };
	int i = 0;
	int iret = 0;
	unsigned int ulen = 0;
	int tmp_cnt = MNTN_FILESYS_MAX_CYCLE * MNTN_FILESYS_PURE_DIR_NAME_LEN;
	char *pbuff = NULL;

	if (NULL == ppath) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: path is NULL when removing old log\n");
		return;
	}
	pbuff = kmalloc(tmp_cnt, GFP_KERNEL);
	if (NULL == pbuff) {
		MNTN_FILESYS_PRINT(KERN_ERR
				   "mntn_err: fail to kmalloc when removing old log\n");
		return;
	}
	memset((void *)pbuff, 0, tmp_cnt);
	tmp_cnt = mntn_filesys_dir_list(ppath, pbuff, tmp_cnt, DT_DIR);
	if (tmp_cnt >= unumber) {
		sort((void *)pbuff, tmp_cnt, MNTN_FILESYS_PURE_DIR_NAME_LEN,
		     mntn_str_cmp, NULL);
		for (i = 0; i < (tmp_cnt - unumber + 1); i++) {
			strncat(fullpath_arr, ppath, strlen(ppath));
			ulen =
			    strlen(pbuff + i * MNTN_FILESYS_PURE_DIR_NAME_LEN);
			strncat(fullpath_arr,
				(const char *)(pbuff + i * MNTN_FILESYS_PURE_DIR_NAME_LEN),
				ulen);
			strncat(fullpath_arr, "/", strlen("/"));

			iret = mntn_filesys_rm_all_file(fullpath_arr);
			iret += mntn_filesys_rm_dir(fullpath_arr);
			if (0 != iret) {
				MNTN_FILESYS_PRINT(KERN_ERR
						   "mntn_err: fail to rm dir, %d",
						   i);
			}
			memset((void *)fullpath_arr, 0, sizeof(fullpath_arr));
		}
	}
	kfree(pbuff);
}
