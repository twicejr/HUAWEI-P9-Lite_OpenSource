/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*lint --e{537} */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include "mdrv_temp_cfg.h"
#include "bsp_temperature.h"


#define THERMAL_OK          0
#define THERMAL_ERROR       1 
#define HKADC_NULL          (void*)(0)
#define THERMAL_CLASS_NAME   "thermal"
#define THERMAL_DEVICE_NAME  "temp"
//#define TEMPERATOR_DEV_MAX   HKADC_TEMP_BUTT

typedef struct drv_hkadc_map TEMPSYS_DEV; /* tempsys_dev换成大写 */

struct hkadc_chan_name{
	unsigned int logic_chan;
    char * name;
};

struct hkadc_chan_name g_hkadc_chan_map[] = {
    {HKADC_TEMP_BATTERY,    "battery"},
    {HKADC_TEMP_PA0,        "pa0"},
    {HKADC_TEMP_PA1,        "pa1"},
    {HKADC_TEMP_XO0,        "xo0"},
    {HKADC_TEMP_XO0_LOW,    "xo0_low"},
    {HKADC_TEMP_XO1,        "xo1"},
    {HKADC_TEMP_XO1_LOW,    "xo1_low"},
    {HKADC_TEMP_LCD,        "lcd"},
    {HKADC_TEMP_SIM_CARD,   "sim_card1"}
};

static ssize_t tempsys_val_show(struct device *dev, struct device_attribute *attr, char *buf);
/*
static ssize_t tempsys_val_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
*/

/*定义: dev_attr_val*/
DEVICE_ATTR(val, S_IRUGO, tempsys_val_show, NULL);/* 确认这两个属性配置为只读 */

static ssize_t tempsys_val_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    unsigned short volt;
    short temp;

	TEMPSYS_DEV* tem_dev = (TEMPSYS_DEV*)dev_get_drvdata(dev);
	if(0 != drv_hkadc_get_temp((HKADC_TEMP_PROTECT_E)tem_dev->logic_chan,&volt,&temp, (HKADC_CONV_MODE_E)0))
	{
		return -1;
	}

    /*返回字符形式的设备温度值*/
	/*lint -save -e123*/
    return snprintf(buf, PAGE_SIZE, "%d\n",temp);
	/*lint -restore*/
}
#if 0
static ssize_t tempsys_val_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    return 0;
}
#endif
/*****************************************************************************
 函 数 名  : tempsys_create_device
 功能描述  : 根据hkadc的逻辑通道号列表，创建thermal class下面的sysfs文件节点
 输入参数  : 温保设备类描述

 输出参数  :
 返 回 值  : 成功返回0，失败返回错误号
*****************************************************************************/
int tempsys_create_device(struct class* thermal_class)
{
	struct hkadc_chan_name map;
    struct device *new_dev = NULL;
	char dev_name[64];/* 建议减小，注意对齐 */
	dev_t devno = 0;
	int i = 0, ret = 0;

	for (i = 0 ; i < ARRAY_SIZE(g_hkadc_chan_map) ; i++) {
		 	map = g_hkadc_chan_map[i];
			memset(dev_name, 0, sizeof(dev_name));
			snprintf(dev_name,64,"%s:%s", THERMAL_DEVICE_NAME, map.name);

			/*在设备类别目录创建char型文件节点: /sys/class/thermal/temp:i*/
			new_dev = device_create(thermal_class, NULL, devno, "%s",
									dev_name);
			if (IS_ERR(new_dev)) {
				ret = PTR_ERR(new_dev);
				printk(KERN_ALERT"failed to create tempsys device %s.\n", g_hkadc_chan_map[i].name);
				return ret;
			}

			ret = device_create_file(new_dev, &dev_attr_val);
			if (ret < 0) {
				printk(KERN_ALERT"failed to create tempsys file.\n");
				return ret;
			}

			dev_set_drvdata(new_dev, &g_hkadc_chan_map[i]);
        }

	return 0;
}


/*****************************************************************************
 函 数 名  : tempsys_device_init
 功能描述  : 温度sysfs节点设备创建初始化
 输入参数  :

 输出参数  :
 返 回 值  :
*****************************************************************************/
static int __init tempsys_device_init(void)
{
	int ret = THERMAL_ERROR;
	struct class * thermal_class;

	/* 创建目录/sys/class/thermal/  */
	thermal_class = class_create(THIS_MODULE, THERMAL_CLASS_NAME);
	if (IS_ERR(thermal_class)) {
        ret = PTR_ERR(thermal_class);
        printk(KERN_ERR "failed to create thermal class.\n");
        goto destory_class;
    }

    printk(KERN_INFO " initialize thermal device.\n");/* 打印级别 */

	if (tempsys_create_device(thermal_class))
	{
		goto destory_device;
	}

	printk(KERN_INFO "Succeedded to initialize thermal device.\n");

	return 0;

destory_device:
destory_class:

    return ret;
}

#if 0
static void __exit tempsys_device_exit(void)
{

}
module_exit(tempsys_device_exit);
#endif

module_init(tempsys_device_init);

MODULE_AUTHOR("  <@huawei.com>");
MODULE_DESCRIPTION("tempator sysfs interface");
MODULE_LICENSE("GPL");

