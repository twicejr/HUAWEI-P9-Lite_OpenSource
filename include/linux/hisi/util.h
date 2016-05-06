/*
 * arch/arm/mach-k3v2/include/mach/util.h
 *
 * balong platform misc utilities function
 *
 * Copyright (C) 2012 Hisilicon, Inc.
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

#ifndef __MACH_UTIL_H__
#define __MACH_UTIL_H__

#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/sysctl.h>
#include "hisi_himntn_enum.h"

#define HIMNTN_VALID_SIZE   (64)

extern int  check_himntn(int feature);

struct proc_dir_entry *balong_create_stats_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_stats_proc_entry(const char *name);

struct proc_dir_entry *balong_create_memory_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_memory_proc_entry(const char *name);

struct proc_dir_entry *balong_create_log_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_log_proc_entry(const char *name);

#ifdef CONFIG_FACTORY_MODE
struct proc_dir_entry *balong_create_ddrtest_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_ddrtest_proc_entry(const char *name);
#endif

ssize_t general_proc_file_read(char *base, loff_t size,
	char __user *userbuf, size_t bytes, loff_t *off);

struct ctl_table_header *balong_register_sysctl_table(struct ctl_table *table);

void create_dump_virt_mem_proc_file(char *name, void *virt_addr, size_t size);

int 	is_fastboot_dumpmem_enable(void );
#endif

