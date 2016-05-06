/*
 * hw_soundtrigger_event.c -- huawei soundigger event driver
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/miscdevice.h>
#include <linux/input.h>
#include <misc/hw_soundtrigger_event.h>

#define LOG_TAG "HW_SOUNDTRIGGER_EVENT"

#define PRINT_INFO  1
#define PRINT_WARN  0
#define PRINT_DEBUG 0
#define PRINT_ERR   1

#if PRINT_INFO
#define logi(fmt, ...) printk("[" LOG_TAG "][I]" fmt "\n", ##__VA_ARGS__)
#else
#define logi(fmt, ...) ((void)0)
#endif

#if PRINT_WARN
#define logw(fmt, ...) printk("[" LOG_TAG "][W]" fmt "\n", ##__VA_ARGS__)
#else
#define logw(fmt, ...) ((void)0)
#endif

#if PRINT_DEBUG
#define logd(fmt, ...) printk("[" LOG_TAG "][D]" fmt "\n", ##__VA_ARGS__)
#else
#define logd(fmt, ...) ((void)0)
#endif

#if PRINT_ERR
#define loge(fmt, ...) printk("[" LOG_TAG "][E]" fmt "\n", ##__VA_ARGS__)
#else
#define loge(fmt, ...) ((void)0)
#endif

#define SOUNDTRIGGER_EVENT_BASE				KEY_F14
#define SOUNDTRIGGER_EVENT_NUM				(5)

#define	ENVP_LENTH					(16)

struct input_dev *soundtrigger_input_dev;

struct miscdevice hw_soundtrigger_miscdev = {
	.minor	=	MISC_DYNAMIC_MINOR,
	.name	=	"hw_soundtrigger_uevent",
};

void hw_soundtrigger_event_input(unsigned int soundtrigger_event)
{
	if(soundtrigger_event < SOUNDTRIGGER_EVENT_NUM) {
		input_report_key(soundtrigger_input_dev,
			SOUNDTRIGGER_EVENT_BASE + soundtrigger_event, 1);
		input_sync(soundtrigger_input_dev);

		input_report_key(soundtrigger_input_dev,
			SOUNDTRIGGER_EVENT_BASE + soundtrigger_event, 0);
		input_sync(soundtrigger_input_dev);
	}
	return;
}
EXPORT_SYMBOL(hw_soundtrigger_event_input);

void hw_soundtrigger_event_uevent(unsigned int soundtrigger_event)
{
	char envp_ext0[ENVP_LENTH];
	char *envp_ext[2] = { envp_ext0, NULL };
	snprintf(envp_ext0, ENVP_LENTH, "soundtrigger=%d", soundtrigger_event);

	kobject_uevent_env(&hw_soundtrigger_miscdev.this_device->kobj, KOBJ_CHANGE, envp_ext);
	return;
}
EXPORT_SYMBOL(hw_soundtrigger_event_uevent);

static const struct of_device_id hw_soundtrigger_event_of_match[] = {
	{
		.compatible = "hisilicon,hw-soundtrigger-event",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, hi6402_vad_of_match);

static int soundtrigger_input_init(struct device *dev)
{
	int error = 0;

	soundtrigger_input_dev = input_allocate_device();
	if (!soundtrigger_input_dev) {
		loge("failed to allocate memory for input dev\n");
		error = -ENOMEM;
		goto err_dev;
	}

	soundtrigger_input_dev->name = "soundtrigger_input_dev";

	soundtrigger_input_dev->evbit[0] = BIT_MASK(EV_KEY);
	soundtrigger_input_dev->keybit[BIT_WORD(KEY_F14)] |= BIT_MASK(KEY_F14);
	soundtrigger_input_dev->keybit[BIT_WORD(KEY_F15)] |= BIT_MASK(KEY_F15);
	soundtrigger_input_dev->keybit[BIT_WORD(KEY_F16)] |= BIT_MASK(KEY_F16);
	soundtrigger_input_dev->keybit[BIT_WORD(KEY_F17)] |= BIT_MASK(KEY_F17);
	soundtrigger_input_dev->keybit[BIT_WORD(KEY_F18)] |= BIT_MASK(KEY_F18);
	error = input_register_device(soundtrigger_input_dev);
	if(error < 0) {
		loge("input register device failed, error_no is %d.\n", error);
		goto err_free_dev;
	}
	logi("input register device successful.\n");
	return 0;

err_free_dev:
	input_free_device(soundtrigger_input_dev);

err_dev:
	loge("error_no is %d.\n", error);

	return error;
}

 static int hw_soundtrigger_event_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret = 0;

	logi("%s enter\n",__FUNCTION__);

	//register soundtrigger input device.
	ret = soundtrigger_input_init(dev);
	if(ret) {
		loge("input registor failed: %d\n", ret);
		goto init_err;
	}

	ret = misc_register(&hw_soundtrigger_miscdev);
	if (ret) {
	loge("%s : hw_soundtrigger_miscdev register failed", __FUNCTION__);
		goto init_err;
	}

	logi("%s : huawei soundtrigger event probe successfully \n", __FUNCTION__);

	return 0;

init_err:
	loge("%s : huawei soundtrigger event probe failed \n", __FUNCTION__);

	return ret;
}

static int hw_soundtrigger_event_remove(struct platform_device *pdev)
{
	input_unregister_device(soundtrigger_input_dev);

	return 0;
}

static struct platform_driver hw_soundtrigger_event_driver = {
	.driver = {
		.name	= "hw_soundtrigger_event",
		.owner	= THIS_MODULE,
		.of_match_table = hw_soundtrigger_event_of_match,
	},
	.probe	= hw_soundtrigger_event_probe,
	.remove	= hw_soundtrigger_event_remove,
};

static int __init hw_soundtrigger_event_init(void)
{
	logi("%s : huawei soundtrigger event init ok \n", __FUNCTION__);
	return platform_driver_register(&hw_soundtrigger_event_driver);
}

static void __exit hw_soundtrigger_event_exit(void)
{
	platform_driver_unregister(&hw_soundtrigger_event_driver);
}

fs_initcall(hw_soundtrigger_event_init);
module_exit(hw_soundtrigger_event_exit);

MODULE_DESCRIPTION("hw_soundtrigger_event driver");
MODULE_LICENSE("GPL");

