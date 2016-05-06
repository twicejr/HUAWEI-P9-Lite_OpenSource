

#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/printk.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define POSTFSDATA_NAME "post-fs-data"

struct proc_dir_entry *post_fs_data = NULL;

static unsigned int postfsdata_flag = 0;

unsigned int get_postfsdata_flag(void)
{
    return postfsdata_flag;
}
EXPORT_SYMBOL(get_postfsdata_flag);

void set_postfsdata_flag(int value)
{
    postfsdata_flag = value;
}
EXPORT_SYMBOL(set_postfsdata_flag);

int wait_for_postfsdata(unsigned int timeout)
{
	while (postfsdata_flag == 0) {
		/*--------------------------------------------------
		* schedule_timeout(HZ);
		*--------------------------------------------------*/
		msleep(1000);
		if (timeout) {
			timeout--;
			if (timeout == 0)
				return 1;
		}
	}
	return 0;
}
EXPORT_SYMBOL(wait_for_postfsdata);

static int postfsdata_info_show(struct seq_file *m, void *v)
{
	int len = 0;
	len = seq_printf(m,"%d\n", postfsdata_flag);
	return 0;
}
int postfsdata_write_proc(struct file *file, const char *buffer, unsigned long count, void *data) {
	long value = -1;
	int strtol_ret = -1;
	int ret = -EINVAL;
	char tmp;

	if (count > 2)
		return ret;

	if (copy_from_user(&tmp, buffer, 1)) { //should ignore character '\n'
		return -EFAULT;
	}
	if (tmp == '1')
		set_postfsdata_flag(1);
	else if (tmp == '0')
		set_postfsdata_flag(0);
	return 1;
}

static int postfsdata_open(struct inode *inode, struct file *file)
{
	return single_open(file, postfsdata_info_show, NULL);
}


static const struct file_operations postfsdata_proc_fops = {
	.open		= postfsdata_open,
	.read		= seq_read,
	.write		= postfsdata_write_proc,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init postfsdata_proc_init(void) {
	proc_create(POSTFSDATA_NAME, 0600, NULL, &postfsdata_proc_fops);
	return 0;
}

module_init(postfsdata_proc_init);

