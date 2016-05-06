/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: switch_usb_class.c
* Author: lixiuna(00213837)       Version : 0.1      Date:  2013-11-06
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*  Description:    .c adatper file for USBSwitch
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/syscalls.h>
#include <linux/notifier.h>
#include <huawei_platform/usb/switch/switch_usb.h>
#include "switch_usb_class.h"
#include <huawei_platform/log/hw_log.h>

#define HWLOG_TAG switch_usb_class
HWLOG_REGIST();

static struct switch_usb_dev sdev;
static int swstate_value;

static struct switch_usb_info *p_switch_usb_info = NULL;

static int switch_usb_set_state(struct switch_usb_dev *sdev, int state);

void usb_custom_acc5_event(int pedestal_attach)
{
    char event_buf[32];
    char *envp[] = {event_buf, NULL};
    int ret;

    int pedestal_attach_flag = pedestal_attach;
    if (pedestal_attach_flag == 1) {
        snprintf(event_buf, sizeof(event_buf), "USB_CUSTOM_ACC5=pedestal_attach");
    }else {
        snprintf(event_buf, sizeof(event_buf), "USB_CUSTOM_ACC5=pedestal_detach");
    }
    ret = kobject_uevent_env(&(sdev.dev->kobj), KOBJ_CHANGE, envp);
    hwlog_info("%s: sent uevent %s\n", __func__, envp[0]);

    if (ret < 0){
        hwlog_err("%s: uevent sending failed!!! ret=%d\n", __func__, ret);
    }else{
        hwlog_info("%s: uevent sending ok USB_CUSTOM_ACC5=custom_acc5_mode\n", __func__);
    }
}
EXPORT_SYMBOL_GPL(usb_custom_acc5_event);

int get_swstate_value(void)
{
    hwlog_info("%s: swstate_value=%d\n", __func__, swstate_value);
    switch (swstate_value){
        case USB_TO_AP:
            return FSA9685_USB1;
        case USB_TO_MODEM1:
            return FSA9685_USB2;
        case USB_OFF:
            return FSA9685_OPEN;
        default:
            hwlog_err("%s: swstate_value[%d] is error!!!\n", __func__, swstate_value);
            return FSA9685_OPEN;
    }
}
EXPORT_SYMBOL_GPL(get_swstate_value);

void switch_usb2_access_through_ap(void)
{
    int ret = 0;
    ret = fsa9685_manual_sw(FSA9685_USB2);
    if (ret < 0)
        hwlog_err("%s: fsa9685_manual_sw error!!! ret = %d\n", __func__, ret);
}
EXPORT_SYMBOL_GPL(switch_usb2_access_through_ap);

//switch USB state to AP due to gpio go to up
static void usb_switch_work(struct work_struct *work)
{
    switch_usb_set_state(&sdev, USB_TO_AP);
}
EXPORT_SYMBOL_GPL(usb_switch_work);

int switch_usb_register_notifier(struct notifier_block *nb)
{
	unsigned long flags;
	int ret = -1;
	if(p_switch_usb_info != NULL) {
		spin_lock_irqsave(&p_switch_usb_info->reg_flag_lock, flags);
		ret = atomic_notifier_chain_register(
				&p_switch_usb_info->charger_type_notifier_head, nb);
		spin_unlock_irqrestore(&p_switch_usb_info->reg_flag_lock, flags);
	}
	return ret;
}
EXPORT_SYMBOL_GPL(switch_usb_register_notifier);

int switch_usb_unregister_notifier(struct notifier_block *nb)
{
	unsigned long flags;
	int ret = -1;
	if(p_switch_usb_info != NULL) {
		spin_lock_irqsave(&p_switch_usb_info->reg_flag_lock, flags);
		ret = atomic_notifier_chain_unregister(
				&p_switch_usb_info->charger_type_notifier_head, nb);
		spin_unlock_irqrestore(&p_switch_usb_info->reg_flag_lock, flags);
	}
	return ret;
}
EXPORT_SYMBOL_GPL(switch_usb_unregister_notifier);

//Show and Store function for sys node
static ssize_t usb_state_show(struct device *dev, struct device_attribute *attr,
        char *buf)
{
    struct switch_usb_dev *sdev = (struct switch_usb_dev *)
        dev_get_drvdata(dev);

    return sprintf(buf, "%d\n", sdev->state);
}


static ssize_t usb_state_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    struct switch_usb_dev *sdev = (struct switch_usb_dev *)
                dev_get_drvdata(dev);
    int state;

    sscanf(buf, "%d", &state);
    swstate_value =state;

    if (switch_usb_set_state(sdev, state) < 0) {
        hwlog_info("%s: switch_usb_set_state err\n", __func__);
        return -EINVAL;
    }

    return size;
}

static void set_reg_to_target_state(int state)
{
    hwlog_info("%s: ------entry. state=%d\n", __func__, state);
    switch(state){
    case USB_TO_AP:
        fsa9685_manual_sw(FSA9685_USB1);
        break;
    case USB_TO_MODEM1:
        fsa9685_manual_sw(FSA9685_USB2);
        break;
    case USB_OFF:
        fsa9685_manual_sw(FSA9685_OPEN);
        break;
    default:
        hwlog_err("%s: state[%d] is error!!!\n", __func__, state);
        break;
    }
    hwlog_info("%s: ------end.\n", __func__);
}

static void notify_switch_state(int state)
{
	atomic_notifier_call_chain(&p_switch_usb_info->charger_type_notifier_head,
				state, NULL);
	pr_info("[%s]Notify usb switch state: %d\n", __func__, state);
}

//Store usb state to sys node
static int switch_usb_set_state(struct switch_usb_dev *sdev, int state)
{
    int ret = 0;
    hwlog_info("%s: ------entry.\n", __func__);
    if ((state < USB_TO_AP) || (state > USB_OFF))
    {
        hwlog_err("%s: swstate[%d] is invalid!!!\n", __func__, state);
        ret = -EINVAL;
        return ret;
    }

    if (sdev->state == state)
    {
        hwlog_info("%s: swstate is not changed. sdev->state[%d] and state[%d]\n", __func__, sdev->state, state);
        ret = -EINVAL;
        return ret;
    }

    set_reg_to_target_state(USB_OFF);
    msleep (1000);

    if (state != USB_OFF)
    {
        set_reg_to_target_state(state);
    }

    // update the sys value
    sdev->state = state;

    notify_switch_state(state);

    hwlog_info("%s: ------end.\n", __func__);
    return ret;
}

static DEVICE_ATTR(swstate, S_IRUGO | S_IWUSR, usb_state_show, usb_state_store);

//Create usb class for sys node
struct class *switch_usb_class;

static int create_switch_usb_class(void)
{
    hwlog_info("%s: ------entry.\n", __func__);
    if (NULL==switch_usb_class) {
        hwlog_info("%s: switch_usb_class=NULL and class_create will start.\n", __func__);
        switch_usb_class = class_create(THIS_MODULE, "usbswitch");
        if (IS_ERR(switch_usb_class)){
            hwlog_err("%s: class_create error!!! switch_usb_class=%p\n", __func__, switch_usb_class);
            return PTR_ERR(switch_usb_class);
        }
    }
    hwlog_info("%s: ------end.\n", __func__);
    return 0;
}

static int switch_usb_dev_register(struct switch_usb_dev *sdev)
{
    int ret = 0;

    if (IS_ERR_OR_NULL(switch_usb_class)) {
        hwlog_info("%s: switch_usb_class is ERR or NULL, and create_switch_usb_class will start.", __func__);
        ret = create_switch_usb_class();
        if (ret < 0){
            hwlog_err("%s: create_switch_usb_class error!!! sdev->name=%s\n", __func__, sdev->name);
            goto err_create_file;
        }
    }
    hwlog_info("%s: device_create will start.", __func__);
    sdev->dev = device_create(switch_usb_class, NULL,
        MKDEV(0, 0), NULL, "usbsw");
    if (IS_ERR(sdev->dev))
    {
        ret = PTR_ERR(sdev->dev);
        hwlog_err("%s: device_create error!!! sdev->name=%s\n", __func__, sdev->name);
        goto err_create_file;
    }

    return 0;

err_create_file:

    return ret;
}


static void switch_usb_dev_unregister(struct switch_usb_dev *sdev)
{
    device_destroy(switch_usb_class, MKDEV(0, 0));
}


//Config DTS information
#ifdef CONFIG_OF
static const struct of_device_id platform_usbswitch_ids[] = {
    { .compatible = "huawei,usbswitch" },
    {},
};
MODULE_DEVICE_TABLE(of, platform_usbswitch_ids);
#endif

static int usb_switch_probe(struct platform_device *pdev)
{
    int ret = 0;

    hwlog_info("%s: ------entry.\n", __func__);

    sdev.name = pdev->name;    //pdev->name; "usbsw"

    INIT_WORK(&sdev.work, usb_switch_work);

    ret = switch_usb_dev_register(&sdev);
    if (ret < 0){
        hwlog_err("%s: switch_usb_dev_register error!!!\n", __func__);
        goto err_switch_usb_dev_register;
    }

    ret = device_create_file(sdev.dev, &dev_attr_swstate);
    if (ret < 0){
        hwlog_err("%s: device_create_file error!!!\n", __func__);
        goto err_switch_usb_dev_register;
    }
    dev_set_drvdata(sdev.dev, &sdev);
    sdev.state = USB_TO_AP;

    hwlog_info("%s: ------OK.\n", __func__);
    return 0;

err_switch_usb_dev_register:
    hwlog_err("%s: ------FAIL!!! ret=%d\n", __func__, ret);
    return ret;
}

static int  usb_switch_remove(struct platform_device *pdev)
{
    cancel_work_sync(&sdev.work);
    switch_usb_dev_unregister(&sdev);
    device_remove_file(sdev.dev, &dev_attr_swstate);
    dev_set_drvdata(sdev.dev, NULL);
    class_destroy(switch_usb_class);

    return 0;
}

static struct platform_driver usb_switch_driver = {
    .probe        = usb_switch_probe,
    .remove        = usb_switch_remove,
    .driver        = {
        .name    = "switch-usb",
        .owner    = THIS_MODULE,
        .of_match_table = of_match_ptr(platform_usbswitch_ids),
    },
};

//init function for switch_usb_class mode
static int __init switch_usb_class_init(void)
{
    int ret = 0;
    struct switch_usb_info *sui;

    hwlog_info("%s: ------entry.\n", __func__);
    ret = platform_driver_register(&usb_switch_driver);

    if(NULL == p_switch_usb_info)
	{
		sui = kzalloc(sizeof(struct switch_usb_info), GFP_KERNEL);
		if(NULL == sui) {
			pr_err("kzalloc failed!\n");
			return -ENOMEM;
		}
		p_switch_usb_info = sui;
		ATOMIC_INIT_NOTIFIER_HEAD(&sui->charger_type_notifier_head);
		spin_lock_init(&sui->reg_flag_lock);
	}

    hwlog_info("%s: ------end. ret=%d\n", __func__, ret);

    return ret;
}

static void __exit switch_usb_class_exit(void)
{
    struct switch_usb_info *sui = p_switch_usb_info;

	class_destroy(switch_usb_class);

	if(NULL != sui)
	{
		kfree(sui);
		p_switch_usb_info = NULL;
	}

    platform_driver_unregister(&usb_switch_driver);
}

module_init(switch_usb_class_init);
module_exit(switch_usb_class_exit);

MODULE_AUTHOR("Lixiuna<lixiuna@huawei.com>");
MODULE_DESCRIPTION("Switch usb class driver");
MODULE_LICENSE("GPL");
