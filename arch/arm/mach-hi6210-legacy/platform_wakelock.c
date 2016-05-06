#include <linux/module.h>			/* For module specific items */
#include <linux/moduleparam.h>		/* For new moduleparam's */
#include <linux/types.h>			/* For standard types (like size_t) */
#include <linux/errno.h>			/* For the -ENODEV/... values */
#include <linux/kernel.h>			/* For printk/... */
#include <linux/init.h>				/* For __init/__exit/... */
#include <linux/fs.h>				/* For file operations */
#include <linux/wakelock.h>			/* For file operations */
#include <linux/ioport.h>			/* For io-port access */
#include <linux/spinlock.h>			/* For spin_lock/spin_unlock/... */
#include <linux/suspend.h>
#include <linux/completion.h>
#include <linux/uaccess.h>			/* For copy_to_user/put_user/... */
#include <linux/workqueue.h>		/* For workqueue... */
#include <linux/notifier.h>			/* For notifier... */
#include <linux/interrupt.h>		/* For request_irq*/
#include <linux/io.h>				/* For writel */
#include <mach/util.h>

static int platform_wakelock_notify(struct notifier_block *notify_block,
					unsigned long mode, void *unused);

static struct wake_lock platform_wakelock;
static int platform_wakelock_timeout = HZ/2;

static struct ctl_table platform_wakelock_table[] = {
	{
		.procname     = "wakelock_timeout",
		.data	      = &platform_wakelock_timeout,
		.maxlen	      = sizeof(int),
		.mode	      = 0644,
		.proc_handler = proc_dointvec
	},
	{ }
};

static struct notifier_block platform_wakelock_notifier = {
    .notifier_call = platform_wakelock_notify,
    .priority = INT_MIN
};

static int platform_wakelock_notify(struct notifier_block *notify_block,
					unsigned long mode, void *unused)
{
	switch (mode) {
        case PM_POST_SUSPEND:
            wake_lock_timeout(&platform_wakelock, platform_wakelock_timeout);
            break;
    }

	return 0;
}

static int __init platform_wakelock_init(void)
{
    struct ctl_table_header *platform_wakelock_header;
    int ret;

	ret = register_pm_notifier(&platform_wakelock_notifier);
	if (ret < 0){
        printk(KERN_ERR"%s : register_pm_notifier failed %d !\n",__FUNCTION__, ret);
        return ret;
	}

	wake_lock_init(&platform_wakelock, WAKE_LOCK_SUSPEND, "platform_wakelock");

    platform_wakelock_header = balong_register_sysctl_table(platform_wakelock_table);
    if (NULL == platform_wakelock_header){
        printk(KERN_ERR"%s : balong_register_sysctl_table failed !\n",__FUNCTION__);
    }

	return 0;
}

module_init(platform_wakelock_init);

