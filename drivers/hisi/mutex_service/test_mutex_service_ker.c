/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_mutex_service_ker.c
  版 本 号   : 初稿
  作    者   : 卜涛 00260479
  生成日期   : 2013年11月19日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2013年11月19日
    作    者   :卜涛 00260479
    修改内容   : 创建文件

******************************************************************************/

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

/*****************************************************************************
 函 数 名  : hisi_test_service_kernel_notify
 功能描述  : 内核态业务的ST回调函数测试入口
 输出参数  : 无
 返 回 值  : 传递的参数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : 卜涛 00260479
    修改内容   : 新生成函数

*****************************************************************************/
int hisi_test_service_kernel_notify(int hisi_id)
{
	int disabled = 0;

	disabled = hisi_mutex_mng_service_stop(hisi_id);
	printk(KERN_INFO "%s: mutex_service notify return value is %d for hisi_test_service_kernel_notify\n",
				__func__, disabled);

	return  disabled;
}

/*****************************************************************************
 函 数 名  : hisi_test_service_kstart
 功能描述  : 内核态业务启动功能的ST测试入口
 输出参数  : 无
 返 回 值  : 写入字符长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : 卜涛 00260479
    修改内容   : 新生成函数

*****************************************************************************/
int hisi_mutex_service_test_kstart(int hisi_id)
{
	int enabled = 0;

	enabled = hisi_mutex_mng_service_start( hisi_id, &hisi_test_service_kernel_notify);
	printk(KERN_INFO "%s: return value is %d for hisi_mutex_mng_service_start\n",
				__func__, enabled);

	return enabled;
}

/*****************************************************************************
 函 数 名  : hisi_test_service_kstop_store
 功能描述  : 内核态业务停止功能的ST测试入口
 输出参数  : 无
 返 回 值  : 写入字符长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : 卜涛 00260479
    修改内容   : 新生成函数

*****************************************************************************/
int hisi_mutex_service_test_kstop(int hisi_id)
{
	int disabled = 0;

	disabled = hisi_mutex_mng_service_stop(hisi_id);
	printk(KERN_INFO "%s: return value is %d for hisi_mutex_mng_service_stop\n",
				__func__, disabled);

	return disabled;
}

/*****************************************************************************
 函 数 名  : hisi_test_service_kstop_store
 功能描述  : 内核态业务停止功能的ST测试入口
 输出参数  : 无
 返 回 值  : 写入字符长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : 卜涛 00260479
    修改内容   : 新生成函数

*****************************************************************************/
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

