/*
 * deviceboxID.c -- deviceboxID driver
 *
 * Copyright (c) 2014 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/regulator/consumer.h>
#include <linux/string.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/huawei/hisi_adc.h>
#include <linux/pinctrl/consumer.h>
#include <linux/ioctl.h>

#define LOG_TAG "deviceboxID"

#define READ_SPEAKER_ID      0x00
#define READ_RECEIVER_ID     0x01

#define DEVICEBOX_ID_NAME    "deviceboxID"
#define ADC_READ_COUNT       3
#define DEVICEBOX_ID_LIMIT   500

#define VENDOR_DEFAULT       0
#define ELECTRIC_LEVEL_LOW   0
#define ELECTRIC_LEVEL_HIGH  1
#define VENDOR               2
#define DEVICEBOX_ID_GET_SPEAKER        _IOR('H', 0x01, __u32)
#define DEVICEBOX_ID_GET_RECEIVER       _IOR('H', 0x02, __u32)

#define DEVICEBOX_ID_MODE_OF_GPIO       "gpio"
#define CODEC_GPIO_BASE                 (224)
static int speakerID_map[VENDOR][VENDOR] =  {-1, -1, -1, -1};
static int receiverID_map[VENDOR] = {-1, -1};


enum {
	DEVICEBOX_ID_MODE_USE_GPIO          = 0x0,
	DEVICEBOX_ID_MODE_USE_ADC           = 0x1,
};

enum {
	USE_ONE_GPIO            = 1,
	USE_TWO_GPIO            = 2,
};


struct out_audio_device_id {
	int adc_channel;
	int deviceboxID_limit;
	int spk_gpio_id[2];
	int rec_gpio_id;
	int spk_enable;
	int rec_enable;
	int check_mode;
	int gpio_num;
	int gpio_spk_status[2];
	int gpio_rec_status;
};

struct out_audio_device_id deviceboxID = {-1};

static int adc_read()
{
	int value = VENDOR_DEFAULT;
	int loop = ADC_READ_COUNT;

	while (loop) {
		loop--;
		value = hisi_adc_get_value(deviceboxID.adc_channel);
		pr_info("adc_read adc:%d\n", value);
		if (value < 0) {
			pr_err("%s(%u) : get hkadc error err = %d\n", __FUNCTION__, __LINE__, value);
			continue;
		}
		break;
	}
	// read err default as ELECTRIC_LEVEL_LOW
	if (value < deviceboxID.deviceboxID_limit)
		return ELECTRIC_LEVEL_LOW;
	else
		return ELECTRIC_LEVEL_HIGH;
}

static int gpio_read(int out_id)
{
	int value = VENDOR_DEFAULT;

	if (out_id >= CODEC_GPIO_BASE) {
		value = gpio_get_value_cansleep(out_id);
	} else {
		value = gpio_get_value(out_id);
	}
	if (value < 0 || value >= VENDOR) {
		pr_err("invalid value: %d",value);
		return -EINVAL;
	}
	pr_info("%s:gpio read:%d\n",__FUNCTION__, value);
	return value;
}

static int deviceboxID_read(int out_id)
{
	int id = VENDOR_DEFAULT;
	int vend = VENDOR_DEFAULT;

	if (DEVICEBOX_ID_MODE_USE_GPIO == deviceboxID.check_mode) {
		if (out_id == READ_SPEAKER_ID) {
			if (deviceboxID.gpio_num == USE_ONE_GPIO) {
				vend = speakerID_map[0][deviceboxID.gpio_spk_status[0]];
			}else if (deviceboxID.gpio_num == USE_TWO_GPIO) {
				vend = speakerID_map[deviceboxID.gpio_spk_status[0]][deviceboxID.gpio_spk_status[1]];
			}
		} else if (out_id == READ_RECEIVER_ID) {
			vend = receiverID_map[deviceboxID.gpio_rec_status];
		}
	} else {
		vend = adc_read();
	}

	pr_info("deviceboxID_read vend:%d\n", vend);
	return vend;
}

static long deviceboxID_do_ioctl(struct file *file, unsigned int cmd,
			void __user *p, int compat_mode)
{
	int ret = 0;
	unsigned int value = VENDOR_DEFAULT;
	unsigned int __user *pUser = (unsigned int __user *) p;

	switch(cmd) {
		case DEVICEBOX_ID_GET_SPEAKER:
			if (deviceboxID.spk_enable) {
				value = deviceboxID_read(READ_SPEAKER_ID);
			}
			ret |= put_user(value, pUser);
			break;
		case DEVICEBOX_ID_GET_RECEIVER:
			if (deviceboxID.rec_enable) {
				value = deviceboxID_read(READ_RECEIVER_ID);
			}
			ret |= put_user(value, pUser);
			break;
		default:
			pr_err("unsupport deviceboxID cmd\n");
			ret = -EINVAL;
			break;
	}
	return (long)ret;
}

static long deviceboxID_ioctl(struct file *file, unsigned int command,
			unsigned long arg)
{
	return deviceboxID_do_ioctl(file, command, (void __user *)arg, 0);
}

#ifdef CONFIG_COMPAT
static long deviceboxID_ioctl_compat(struct file *file, unsigned int command,
			unsigned long arg)
{
	return deviceboxID_do_ioctl(file, command, compat_ptr(arg), 1);
}
#else
#define deviceboxID_ioctl_compat NULL
#endif

static const struct of_device_id deviceboxID_match[] = {
	{ .compatible = "huawei,deviceboxID", },
	{},
};
MODULE_DEVICE_TABLE(of, deviceboxID_match);

static const struct file_operations deviceboxID_fops = {
	.owner          = THIS_MODULE,
	.unlocked_ioctl = deviceboxID_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = deviceboxID_ioctl,
#endif
};

static struct miscdevice deviceboxID_device = {
	.minor  = MISC_DYNAMIC_MINOR,
	.name   = DEVICEBOX_ID_NAME,
	.fops   = &deviceboxID_fops,
};

static ssize_t deviceboxID_gpio_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	 return snprintf(buf, 32, "spk:%d rec:%d\n", gpio_read(deviceboxID.spk_gpio_id), gpio_read(deviceboxID.rec_gpio_id));
}

static DEVICE_ATTR(deviceboxID_gpio_status, 0660, deviceboxID_gpio_show, NULL);

static struct attribute *deviceboxID_attributes[] = {
	&dev_attr_deviceboxID_gpio_status.attr,
	NULL
};

static const struct attribute_group deviceboxID_attr_group = {
	.attrs = deviceboxID_attributes,
};

static int get_check_mode(struct device_node *dev_node)
{
	const char *mode;
	int rc;
	/*get check mode*/
	rc = of_property_read_string(dev_node, "check_mode", &mode);
	if (rc) {
		pr_info("%s: not find dev_node ,rc=%d\n", __FUNCTION__, rc);
		return DEVICEBOX_ID_MODE_USE_ADC;
	} else {
		pr_info("%s: mode: %s\n", __FUNCTION__, mode);
	}

	if (!strncmp(mode, DEVICEBOX_ID_MODE_OF_GPIO, sizeof(DEVICEBOX_ID_MODE_OF_GPIO))) {
		return DEVICEBOX_ID_MODE_USE_GPIO;
	}else{
		return DEVICEBOX_ID_MODE_USE_ADC;
	}
}

static int get_gpio_num(struct device_node* dev_node)
{
	int gpio_num = USE_ONE_GPIO;
	int rc = 0;

	/*get gpio number*/
	rc = of_property_read_u32(dev_node, "gpio_num", &gpio_num);
	if (rc < 0) {
		pr_info("%s: not find dev_node ,rc=%d\n", __FUNCTION__, rc);
	} else {
		pr_info("%s: gpio_num: %d\n", __FUNCTION__, gpio_num);
	}

	if (gpio_num == USE_ONE_GPIO) {
		return USE_ONE_GPIO;
	} else {
		return USE_TWO_GPIO;
	}
}


static int deviceboxID_probe(struct platform_device *pdev)
{
	int ret = -ENODEV;
	const struct of_device_id *match;
	struct device_node *node;
	int temp;
	int i;
	struct pinctrl *p;
	struct pinctrl_state *pinctrl_def;

	pr_info("deviceboxID_probe++\n");
	match = of_match_device(deviceboxID_match, &pdev->dev);
	if (!match) {
		pr_err("get deviceboxID device info err\n");
		return -ENOENT;
	}
	node = pdev->dev.of_node;

	deviceboxID.check_mode = get_check_mode(node);
	deviceboxID.gpio_num = get_gpio_num(node);

	if (!of_property_read_u32(node, "enable_speakerID", &temp)) {
		deviceboxID.spk_enable = temp;
	} else {
		pr_err("get gpio type failed, set to SOC type\n");
		deviceboxID.spk_enable = 0;
	}

	if (!of_property_read_u32(node, "enable_receiverID", &temp)) {
		deviceboxID.rec_enable = temp;
	} else {
		pr_err("get gpio type failed, set to SOC type\n");
		deviceboxID.rec_enable = 0;
	}

	if (DEVICEBOX_ID_MODE_USE_GPIO == deviceboxID.check_mode) {
		p = devm_pinctrl_get(&pdev->dev);
		if (IS_ERR(p)) {
			pr_err("could not get pinctrl.\n");
			return -ENOENT;
		}

		pinctrl_def = pinctrl_lookup_state(p, "default");
		if (IS_ERR(pinctrl_def)) {
			pr_err("could not get defstate.\n");
			return -ENOENT;
		}

		ret = pinctrl_select_state(p, pinctrl_def);
		if (ret) {
			pr_err("could not set pins to default state.\n");
			return -ENOENT;
		}

		/* create sysfs for debug function */
		if ((sysfs_create_group(&pdev->dev.kobj, &deviceboxID_attr_group)) < 0) {
			pr_err("%s:failed to register sysfs\n",__FUNCTION__);
			return -ENOENT;
		}

		if (1 == deviceboxID.spk_enable) {
			if(deviceboxID.gpio_num == USE_ONE_GPIO) {
				if (of_property_read_u32_array(node, "speakerID_map", speakerID_map, sizeof(speakerID_map) / sizeof(int) / 2)) {
					pr_err("of_property_read_u32_array by one gpio spk_id_map err\n");
					goto err_out_sysfs;
				}
			}else if(deviceboxID.gpio_num == USE_TWO_GPIO) {
				if (of_property_read_u32_array(node, "speakerID_map", speakerID_map, sizeof(speakerID_map) / sizeof(int))) {
					pr_err("of_property_read_u32_array by two gpio spk_id_map err\n");
					goto err_out_sysfs;
				}
			}

		}

		for (i = 0; i < deviceboxID.gpio_num; i++) {

			deviceboxID.spk_gpio_id[i] = of_get_named_gpio(node, "gpio_speakerID", i);
			if (deviceboxID.spk_gpio_id[i]  < 0) {
				pr_err("%s: spk_id.gpio_id is unvalid!\n", __FUNCTION__);
				goto err_gpio_speakerID;
			}

			if (!gpio_is_valid(deviceboxID.spk_gpio_id[i])) {
				pr_err("%s:gpio is unvalid!\n", __FUNCTION__);
				goto err_gpio_speakerID;
			}

			ret = gpio_request(deviceboxID.spk_gpio_id[i], "speaker_id_check");
			if (ret) {
				pr_err("%s:error request GPIO %d for speaker_id_check fail %d\n", __FUNCTION__, i, ret);
				goto err_gpio_speakerID;
			}

			/* set gpio to input status */
			gpio_direction_input(deviceboxID.spk_gpio_id[i]);

			deviceboxID.gpio_spk_status[i] = gpio_get_value_cansleep(deviceboxID.spk_gpio_id[i]);

			if (deviceboxID.gpio_spk_status[i] < ELECTRIC_LEVEL_LOW || 
				deviceboxID.gpio_spk_status[i] > ELECTRIC_LEVEL_HIGH ) {
				pr_err("%s:gpio_spk_status[%d] is invalid\n", __FUNCTION__, i);
				goto err_gpio_speakerID;

			}
			pr_info("%s:read gpio_spk_status[%d] is %d\n", __FUNCTION__, i, deviceboxID.gpio_spk_status[i]);

			
		}

		if (1 == deviceboxID.rec_enable) {
			if (of_property_read_u32_array(node, "receiverID_map", receiverID_map, sizeof(receiverID_map) / sizeof(int))) {
				pr_err("of_property_read_u32_array rec_id_map err\n");
				goto err_gpio_speakerID;
			}
			deviceboxID.rec_gpio_id = of_get_named_gpio(node, "gpio_receiverID", 0);
			if (deviceboxID.rec_gpio_id < 0) {
				pr_err("%s: rec_id.gpio_id is unvalid!\n",__FUNCTION__);
				goto err_gpio_speakerID;
			}
			if (!gpio_is_valid(deviceboxID.rec_gpio_id)) {
				pr_err("%s:receiver gpio is unvalid!\n",__FUNCTION__);
				goto err_gpio_receiverID;
			}
			ret = gpio_request(deviceboxID.rec_gpio_id, "device_receiverID");
			if (ret) {
				pr_err("%s:error receiver request GPIO for deviceboxID_check fail %d\n",__FUNCTION__, ret);
				goto err_gpio_receiverID;
			}
			/* set gpio to input status */
			gpio_direction_input(deviceboxID.rec_gpio_id);

			deviceboxID.gpio_rec_status = gpio_get_value_cansleep(deviceboxID.rec_gpio_id);

			if (deviceboxID.gpio_rec_status < ELECTRIC_LEVEL_LOW ||
				deviceboxID.gpio_rec_status > ELECTRIC_LEVEL_HIGH ) {
				pr_err("%s:gpio_rec_status is invalid\n", __FUNCTION__);
				goto err_gpio_receiverID;
			}

			pr_info("%s:read gpio_rec_status is %d\n", __FUNCTION__, deviceboxID.gpio_spk_status);
		}

		//reset gpio to NP status for saving power
		pinctrl_def = pinctrl_lookup_state(p, "idle");
		if (IS_ERR(pinctrl_def)) {
			pr_err("could not get idle defstate.\n");
			goto err_gpio_receiverID;
		}

		ret = pinctrl_select_state(p, pinctrl_def);
		if (ret) {
			pr_err("could not set pins to idle state.\n");
			goto err_gpio_receiverID;
		}

	} else {
		/* get channel id */
		if (!of_property_read_u32(node, "channel", &temp)) {
			deviceboxID.adc_channel= temp;
		} else {
			pr_err("get adc channel failed, set default value\n");
			deviceboxID.adc_channel = 5;
		}
		/*get deviceboxID deviceboxID value*/
		if (!of_property_read_u32(node, "deviceboxID_limit", &temp)) {
			deviceboxID.deviceboxID_limit= temp;
			pr_info("get deviceboxID_limit from dts:%d\n", temp);
		} else {
			pr_err("get deviceboxID_limit failed, set default value\n");
			deviceboxID.deviceboxID_limit = DEVICEBOX_ID_LIMIT;
		}
	}

	ret = misc_register(&deviceboxID_device);
	if (ret) {
		pr_err("%s: deviceboxID_device register failed", __FUNCTION__);
		goto err_gpio_receiverID;
	}
	pr_info("deviceboxID_probe--\n");
	return 0;

err_gpio_receiverID:
	if (1 == deviceboxID.rec_enable) {
		gpio_free(deviceboxID.rec_gpio_id);
	}
err_gpio_speakerID:
	if (1 == deviceboxID.spk_enable) {
		for (i = 0; i < deviceboxID.gpio_num; i++) {
			if (deviceboxID.spk_gpio_id[i] < 0) {
				continue;
			}
			gpio_free(deviceboxID.spk_gpio_id[i]);
		}
	}
err_out_sysfs:
	sysfs_remove_group(&pdev->dev.kobj, &deviceboxID_attr_group);
	return ret;
}

static int deviceboxID_remove(struct platform_device *pdev)
{
	int i;
	if (DEVICEBOX_ID_MODE_USE_GPIO == deviceboxID.check_mode) {
		if (1 == deviceboxID.spk_enable) {
			for (i = 0; i < deviceboxID.gpio_num; i++) {
				if (deviceboxID.spk_gpio_id[i] < 0) {
					continue;
				}
				gpio_free(deviceboxID.spk_gpio_id[i]);
			}
		}
		if (1 == deviceboxID.rec_enable) {
			gpio_free(deviceboxID.rec_gpio_id);
		}
	}
	misc_deregister(&deviceboxID_device);

	return 0;
}


static struct platform_driver deviceboxID_driver = {
	.driver = {
		.name  = DEVICEBOX_ID_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(deviceboxID_match),
	},
	.probe  = deviceboxID_probe,
	.remove = deviceboxID_remove,
};

static int __init deviceboxID_init(void)
{
	return platform_driver_register(&deviceboxID_driver);
}

static void __exit deviceboxID_exit(void)
{
	platform_driver_unregister(&deviceboxID_driver);
}

module_init(deviceboxID_init);
module_exit(deviceboxID_exit);

MODULE_DESCRIPTION("deviceboxID driver");
MODULE_LICENSE("GPL");
