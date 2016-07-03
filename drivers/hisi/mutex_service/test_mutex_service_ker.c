

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/platform_device.h>	/* For platform_driver framework */
#include <linux/module.h>			/* For module specific items */
#include <linux/moduleparam.h>		/* For new moduleparam's */
#include <linux/types.h>			/* For standard types (like size_t) */
#include <linux/errno.h>			/* For the -ENODEV/... values */
#include <linux/kernel.h>			/* For printk/... */
#include <linux/init.h>				/* For __init/__exit/... */
#include <linux/fs.h>				/* For file operations */
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/stat.h>
#include <linux/delay.h>
#include <hisi/drv_hisi_mutex_service.h>

#include "test_mutex_service_ker.h"

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


int hisi_test_service_kernel_notify(int hisi_id)
{
	int disabled = 0;

	disabled = hisi_mutex_mng_service_stop(hisi_id);
	printk(KERN_INFO "%s: mutex_service notify return value is %d for hisi_test_service_kernel_notify\n",
				__func__, disabled);

	return  disabled;
}


int hisi_mutex_service_test_kstart(int hisi_id)
{
	int enabled = 0;

	enabled = hisi_mutex_mng_service_start( hisi_id, &hisi_test_service_kernel_notify);
	printk(KERN_INFO "%s: return value is %d for hisi_mutex_mng_service_start\n",
				__func__, enabled);

	return enabled;
}


int hisi_mutex_service_test_kstop(int hisi_id)
{
	int disabled = 0;

	disabled = hisi_mutex_mng_service_stop(hisi_id);
	printk(KERN_INFO "%s: return value is %d for hisi_mutex_mng_service_stop\n",
				__func__, disabled);

	return disabled;
}


int hisi_mutex_service_test_alive(int hisi_id)
{
	int alive = 0;
	int i = 0;

	while (i < 10){
		i++;
		alive = hisi_mutex_mng_notify_alive(hisi_id);
		printk(KERN_INFO "%s: return value is %d for hisi_mutex_service_test_alive & i = %d\n", 
					__func__, alive, i);
		mdelay(1000);
	}
	
	return alive;
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

