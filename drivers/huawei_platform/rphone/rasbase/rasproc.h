#ifndef _PROC_COM_H_
#define _PROC_COM_H_

#include <linux/version.h>
#include <linux/seq_file.h>
#include <linux/file.h>
#include <asm/uaccess.h>

#define FILE_NODE(file) file->f_dentry->d_inode
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
#define PDE_DATA(node)   (PDE(node)->data)
#endif

#define proc_ops_name(name) proc_ops_##name
#define proc_ops_open(name)  proc_open_##name
#define proc_ops_show(name)  proc_show_##name
#define proc_ops_write(name)  proc_write_##name
#define proc_ops_init(name) {\
	.open	= proc_ops_open(name),\
	.read		= seq_read,\
	.write	= proc_ops_write(name),\
	.llseek	= seq_lseek,\
	.release	= single_release,\
}

#define proc_ops_define(name) \
static struct file_operations proc_ops_name(name) =  proc_ops_init(name)

int proc_init(char *name , struct file_operations *proc_ops, void *data);

void proc_exit(const char* name);
#endif

