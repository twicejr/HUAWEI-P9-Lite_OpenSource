#include <linux/types.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/syslog.h>

#include <asm/uaccess.h>
#include <asm/io.h>
#include "console_boot_log.h"

static int boot_log_open(struct inode * inode, struct file * file)
{
	return 0;
}

static int boot_log_release(struct inode * inode, struct file * file)
{
	return 0;
}

static ssize_t boot_log_read(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
    return boot_log_console_read(buf, count);
}

static unsigned int boot_log_poll(struct file *file, poll_table *wait)
{
	return 0;
}


static const struct file_operations proc_boot_log_operations = {
	.read		= boot_log_read,
	.poll		= boot_log_poll,
	.open		= boot_log_open,
	.release	= boot_log_release,
	.llseek		= generic_file_llseek,
};

static int __init boot_log_init(void)
{
    boot_log_register();
	proc_create("kmsg_boot", S_IRUSR, NULL, &proc_boot_log_operations);
	return 0;
}
module_init(boot_log_init);
