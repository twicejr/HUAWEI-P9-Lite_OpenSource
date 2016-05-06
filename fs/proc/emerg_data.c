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

#define EMERGDATA_NAME "emerg_data"

struct proc_dir_entry *emerg_data = NULL;

extern unsigned int get_datamount_flag(void);
extern void set_datamount_flag(int value);


static int emergdata_info_show(struct seq_file *m, void *v)
{
	 int len = 0;
	len = seq_printf(m,"%d\n",get_datamount_flag());
	return 0;
}
int emergdata_write_proc(struct file *file, const char *buffer, unsigned long count, void *data) {
    long value = -1;
    int strtol_ret = -1;
    int ret = -EINVAL;
    char *tmp_buf = NULL;

    if ((tmp_buf = kzalloc(count, GFP_KERNEL)) == NULL)
        return -ENOMEM;
    if (copy_from_user(tmp_buf, buffer, count - 1)) { //should ignore character '\n'
        kfree(tmp_buf);
        return -EFAULT;
    }
    *(tmp_buf + count - 1) = '\0';

    strtol_ret = strict_strtol(tmp_buf, 10, &value);

    /*
     * call function set_datamount_flag conditions as follow
     * 1. strict_strtol return 0, AND,
     * 2. value equal 0
     */
    if (strtol_ret == 0) {
        if (value == 0) {
            set_datamount_flag(value);
            ret = count;
        }
    }
    kfree(tmp_buf);
    return ret;
}

static int emergdata_open(struct inode *inode, struct file *file)
{
	return single_open(file, emergdata_info_show, NULL);
}


static const struct file_operations emergdata_proc_fops = {
	.open		= emergdata_open,
	.read		= seq_read,
    .write      = emergdata_write_proc,
	.llseek		= seq_lseek,
	.release	= single_release,
};


static int __init emergdata_proc_init(void) {	
	proc_create(EMERGDATA_NAME, 0660, NULL, &emergdata_proc_fops);
	return 0;
}



module_init(emergdata_proc_init);


