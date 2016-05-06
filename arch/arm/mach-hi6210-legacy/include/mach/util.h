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

int mach_call_usermodeshell(char *script, unsigned int params, ...);

struct proc_dir_entry *balong_create_base_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_base_proc_entry(const char *name);

struct proc_dir_entry *balong_create_debug_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_debug_proc_entry(const char *name);

struct proc_dir_entry *balong_create_stats_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_stats_proc_entry(const char *name);

struct proc_dir_entry *balong_create_memory_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_memory_proc_entry(const char *name);

struct proc_dir_entry *balong_create_reboot_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_reboot_proc_entry(const char *name);

struct proc_dir_entry *balong_create_register_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_register_proc_entry(const char *name);

struct proc_dir_entry *balong_create_log_proc_entry(const char *name, mode_t mode,
	const struct file_operations *proc_fops, void *data);
void balong_remove_log_proc_entry(const char *name);

ssize_t general_proc_file_read(char *base, loff_t size,
	char __user *userbuf, size_t bytes, loff_t *off);

struct ctl_table_header *balong_register_sysctl_table(struct ctl_table *table);


#endif

