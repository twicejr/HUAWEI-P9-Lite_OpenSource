

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/printk.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define LOG_USERTYPE_NAME "log-usertype"

struct proc_dir_entry *log_usertype = NULL;

static unsigned int log_usertype_flag = 0;

unsigned int get_logusertype_flag(void)
{
    return log_usertype_flag;
}
EXPORT_SYMBOL(get_logusertype_flag);

static void set_logusertype_flag(int value)
{
    log_usertype_flag = value;
}

static int logusertype_info_show(struct seq_file *m, void *v)
{
    int len = 0;
    len = seq_printf(m,"%d\n", log_usertype_flag);
    return 0;
}

int logusertype_write_proc(struct file *file, const char *buffer, unsigned long count, void *data) {
    int ret = -EINVAL;
    char tmp;

    if (count > 2)
        return ret;

    if (copy_from_user(&tmp, buffer, 1)) { //should ignore character '\n'
        return -EFAULT;
    }
    if (get_logusertype_flag() == 0) { //log_usertype_flag should be assigned only once
        if (tmp >= '1' && tmp <= '9') {
            set_logusertype_flag((int)(tmp-'0'));
        }
    }
    return 1;
}

static int logusertype_open(struct inode *inode, struct file *file)
{
    return single_open(file, logusertype_info_show, NULL);
}


static const struct file_operations logusertype_proc_fops = {
    .open		= logusertype_open,
    .read		= seq_read,
    .write		= logusertype_write_proc,
    .llseek		= seq_lseek,
    .release	= single_release,
};

static int __init logusertype_proc_init(void) {
    proc_create(LOG_USERTYPE_NAME, 0600, NULL, &logusertype_proc_fops);
    return 0;
}

module_init(logusertype_proc_init);

