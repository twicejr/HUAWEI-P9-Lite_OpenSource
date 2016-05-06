#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/printk.h>
#include <linux/stat.h>
#include <linux/string.h>

extern unsigned int get_pd_charge_flag(void);
extern unsigned int resetmode_is_normal(void);
extern unsigned int get_boot_into_recovery_flag(void);
/*
static int app_info_show(struct seq_file *m, void *v)
{
	int len = 0;
	len = seq_printf(m,"recovery_flag:\n%d\n"
                                        "charge_flag:\n%d\n"
                                        "reset_normal_flag:\n%d\n",
                                        (int)get_boot_into_recovery_flag(),
                                        (int)get_pd_charge_flag(),
                                        (int)resetmode_is_normal());
	return 0;
}
*/
static int app_info_show(struct seq_file *m, void *v)
{
	int len = 0;
	len = seq_printf(m,"recovery_flag:\n%d\n"
                                        "charge_flag:\n%d\n",
                                        (int)get_boot_into_recovery_flag(),
                                        (int)get_pd_charge_flag());
	return 0;
}

static int appinfo_open(struct inode *inode, struct file *file)
{
	return single_open(file, app_info_show, NULL);
}

static const struct file_operations proc_appinfo_operations = {
	.open		= appinfo_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_app_info_init(void)
{
	/* fixme::: should change "app_info_1" to "app_info" ;;
	 * now: in touch scream driver , app_info is create ; but it's not correct;
	 */
	proc_create("app_info", 0, NULL, &proc_appinfo_operations);
	return 0;
}

module_init(proc_app_info_init);
