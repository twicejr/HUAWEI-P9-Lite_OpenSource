
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#include "media_mntn_test.h"

#define LOG_TAG "MNTN_MODULE_CRASH_TEST"

static int crash_start = 0;
static char *p = NULL;

static int __init media_mntn_sys_crash_init(void)
{
    bbit_log(" ====================== enter.");
	if (crash_start != 0) {
		p = NULL;
	}
    bbit_log(" ====================== exit.");
	return 0;
}

static void __exit media_mntn_sys_crash_exit(void)
{
    bbit_log(" ====================== enter.");
	if (crash_start == 0) {
		p = NULL;
	}
    bbit_log(" ====================== exit.");
}

MODULE_LICENSE("GPL");
module_param(crash_start, int, S_IRUGO);
module_init(media_mntn_sys_crash_init);
module_exit(media_mntn_sys_crash_exit);

