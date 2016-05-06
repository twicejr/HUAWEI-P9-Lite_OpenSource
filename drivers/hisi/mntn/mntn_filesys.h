/*
 * head file of mntn_filesys
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef	__MNTN_FILESYS_H__
#define __MNTN_FILESYS_H__

#include <linux/types.h>

/*
 ***************************************************************************
 * Macro define here
 ***************************************************************************
*/
#define MNTN_FILESYS_PRINT		printk

#define MNTN_FILESYS_FNAME_LEN 128 	/*the max length of file/dir name.*/
#define MNTN_FILESYS_DEFAULT_MODE 0770  /*default mode when creating a file or dir if user doesn't set mode*/
#define MNTN_FILESYS_DIR_ENTRY_SIZE    1024  /* the size of entry variable when listing in a dir*/

#define MNTN_FILESYS_MAX_CYCLE    32	/*avoid loop forever! */
#define MNTN_FILESYS_PURE_DIR_NAME_LEN    64	/*the max length of pure name of a file or dir, that is, exclusive path */
/*
 ***************************************************************************
 * Struct define here
 ***************************************************************************
*/
struct linux_dirent {
	unsigned long d_ino;
	unsigned long d_off;
	unsigned short d_reclen;
	char d_name[1];
};

typedef void (*mntn_filesys_funcptr) (unsigned long, unsigned long,
				      unsigned long);
/*
 ***************************************************************************
 *extern functions here
 ***************************************************************************
*/
extern int mntn_filesys_chown(const char *filename, uid_t user, gid_t group);
extern int mntn_filesys_create_dir(const char *path, umode_t umode);
extern int mntn_filesys_rm_dir(const char *dirname);
extern int mntn_filesys_dir_list(const char *path, char *pout_namelist, int cnt,
				 int type);
extern int mntn_filesys_rm_all_file(const char *path);
extern int mntn_filesys_write_log(const char *pname, void *pbuf,
				  unsigned int ulen, umode_t mode);
extern int mntn_filesys_rm_file(const char *fullname);
extern void mntn_rm_old_log(const char *path, unsigned int unumber);

#endif /* End #define __EXCH_FILESYS_H__ */
