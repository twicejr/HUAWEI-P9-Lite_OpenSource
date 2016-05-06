/*
 * drivers/huawei/drivers/tps65132.c
 *
 * tps65132 driver reffer to lcd
 *
 * Copyright (C) 2012-2015 HUAWEI, Inc.
 * Author: HUAWEI, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/param.h>
#include <linux/delay.h>
#include <linux/idr.h>
#include <linux/i2c.h>
#include <asm/unaligned.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/ctype.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/workqueue.h>
#include <linux/of.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

#include "tps65132.h"
#include "../hisi_fb_def.h"

#define DTS_COMP_TPS65132 "hisilicon,tps65132_phy"
static int gpio_vsp_enable;
static int gpio_vsn_enable;
static bool fastboot_display_enable = true;

#define DTS_COMP_SHARP_NT35695_5P5 "hisilicon,mipi_sharp_NT35695_5P5"
#define DTS_COMP_SHARP_NT35695_5P7 "hisilicon,mipi_sharp_NT35695_5p7"
#define DTS_COMP_SHARP_KNT_NT35597 "hisilicon,mipi_sharp_knt_NT35597"
#define VAL_5V5 0
#define VAL_5V8 1

static int get_lcd_type(void)
{
	struct device_node *np = NULL;
	int ret = 0;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_SHARP_NT35695_5P5);
	ret = of_device_is_available(np);
	if (np && ret) {
		HISI_FB_INFO("device %s! set voltage 5.8V\n", DTS_COMP_SHARP_NT35695_5P5);
		return VAL_5V8;
	}
	np = of_find_compatible_node(NULL, NULL, DTS_COMP_SHARP_NT35695_5P7);
	ret = of_device_is_available(np);
	if (np && ret) {
		HISI_FB_INFO("device %s! set voltage 5.8V\n", DTS_COMP_SHARP_NT35695_5P7);
		return VAL_5V8;
	}
	np = of_find_compatible_node(NULL, NULL, DTS_COMP_SHARP_KNT_NT35597);
	ret = of_device_is_available(np);
	if (np && ret) {
		HISI_FB_INFO("device %s! set voltage 5.8V\n", DTS_COMP_SHARP_KNT_NT35597);
		return VAL_5V8;
	}
	HISI_FB_INFO("not found device %s! set voltage 5.5V\n", DTS_COMP_SHARP_NT35695_5P5);
	return VAL_5V5;
}

static int tps65132_reg_inited(struct i2c_client *client, u8 vpos_target_cmd, u8 vneg_target_cmd)
{
	int vpos = 0;
	int vneg = 0;
	int nRet = 0;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_VPOS);
	if (nRet < 0) {
		pr_err("%s read vpos voltage failed\n", __func__);
		goto exit;
	}
	vpos = nRet;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_VNEG);
	if (nRet < 0) {
		pr_err("%s read vneg voltage failed\n", __func__);
		goto exit;
	}
	vneg = nRet;

	pr_err("vpos : 0x%x, vneg: 0x%x", vpos, vpos);

	if(  ((vpos & TPS65132_REG_VOL_MASK) == vpos_target_cmd)
      && ((vneg & TPS65132_REG_VOL_MASK) == vneg_target_cmd)
      )
		nRet = 1;
	else
		nRet = 0;

exit:
	return nRet;
}


static int tps65132_reg_init(struct i2c_client *client, u8 vpos_cmd, u8 vneg_cmd)
{
	int vpos = 0;
	int vneg = 0;
	int nRet = 0;
	int app_dis = 0;
	int ctl = 0;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_VPOS);
	if (nRet < 0) {
		pr_err("%s read vpos voltage failed\n", __func__);
		goto exit;
	}
	vpos = nRet;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_VNEG);
	if (nRet < 0) {
		pr_err("%s read vneg voltage failed\n", __func__);
		goto exit;
	}
	vneg = nRet;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_APP_DIS);
	if (nRet < 0) {
		pr_err("%s read app_dis failed\n", __func__);
		goto exit;
	}
	app_dis = nRet;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_CTL);
	if (nRet < 0) {
		pr_err("%s read ctl failed\n", __func__);
		goto exit;
	}
	ctl = nRet;

	vpos = (vpos&(~TPS65132_REG_VOL_MASK)) | vpos_cmd;
	vneg = (vneg&(~TPS65132_REG_VOL_MASK)) | vneg_cmd;
	app_dis = app_dis | TPS65312_APPS_BIT | TPS65132_DISP_BIT | TPS65132_DISN_BIT;
	ctl = ctl | TPS65132_WED_BIT;

	nRet = i2c_smbus_write_byte_data(client, TPS65132_REG_VPOS, (u8)vpos);
	if (nRet < 0) {
		pr_err("%s write vpos failed\n", __func__);
		goto exit;
	}

	nRet = i2c_smbus_write_byte_data(client, TPS65132_REG_VNEG, (u8)vneg);
	if (nRet < 0) {
		pr_err("%s write vneg failed\n", __func__);
		goto exit;
	}

	nRet = i2c_smbus_write_byte_data(client, TPS65132_REG_APP_DIS, (u8)app_dis);
	if (nRet < 0) {
		pr_err("%s write app_dis failed\n", __func__);
		goto exit;
	}

	nRet = i2c_smbus_write_byte_data(client, TPS65132_REG_CTL, (u8)ctl);
	if (nRet < 0) {
		pr_err("%s write ctl failed\n", __func__);
		goto exit;
	}
	msleep(60);

exit:
	return nRet;
}


static void tps65132_get_target_voltage(int *vpos_target, int *vneg_target)
{
	int ret = 0;

	ret = get_lcd_type();
	if (ret == VAL_5V8) {
		HISI_FB_INFO("vpos and vneg target is 5.8V\n");
		*vpos_target = TPS65132_VOL_58;
		*vneg_target = TPS65132_VOL_58;
	} else {
		HISI_FB_INFO("vpos and vneg target is 5.5V\n");
		*vpos_target = TPS65132_VOL_55;
		*vneg_target = TPS65132_VOL_55;
	}
	return;
}

static int tps65132_start_setting(void)
{
	int retval = 0;

	retval = gpio_request(gpio_vsp_enable, "gpio_lcd_p5v5_enable");
	if (retval != 0) {
		pr_err("failed to request gpio %d : gpio_lcd_p5v5_enable !\n", gpio_vsp_enable);
		return retval;
	}

	retval = gpio_request(gpio_vsn_enable, "gpio_lcd_n5v5_enable");
	if (retval != 0) {
		pr_err("failed to request gpio %d : gpio_lcd_n5v5_enable !\n", gpio_vsn_enable);
		return retval;
	}


	retval = gpio_direction_output(gpio_vsp_enable, 1);
	if (retval != 0) {
		pr_err("failed to output gpio %d : gpio_lcd_p5v5_enable !\n", gpio_vsp_enable);
		return retval;
	}
	mdelay(5);

	retval = gpio_direction_output(gpio_vsn_enable, 1);
	if (retval != 0) {
		pr_err("failed to output gpio %d : gpio_lcd_p5v5_enable !\n", gpio_vsn_enable);
		return retval;
	}
	mdelay(5);

	return retval;
}

static int tps65132_finish_setting(void)
{
	int retval = 0;

	retval = gpio_direction_output(gpio_vsn_enable, 0);
	if (retval != 0) {
		pr_err("failed to output gpio %d : gpio_lcd_n5v5_enable !\n", gpio_vsn_enable);
		return retval;
	}
	udelay(10);

	retval = gpio_direction_output(gpio_vsp_enable, 0);
	if (retval != 0) {
		pr_err("failed to output gpio %d : gpio_lcd_p5v5_enable !\n", gpio_vsp_enable);
		return retval;
	}
	udelay(10);

	retval = gpio_direction_input(gpio_vsn_enable);
	if (retval != 0) {
		pr_err("failed to set gpio %d input: gpio_lcd_n5v5_enable !\n", gpio_vsn_enable);
		return retval;
	}
	udelay(10);

	retval = gpio_direction_input(gpio_vsp_enable);
	if (retval != 0) {
		pr_err("failed to set gpio %d input: gpio_lcd_p5v5_enable !\n", gpio_vsp_enable);
		return retval;
	}
	udelay(10);

	gpio_free(gpio_vsn_enable);
	gpio_free(gpio_vsp_enable);

	return retval;
}

static int tps65132_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int retval = 0;
	int nRet = 0;
	int vpos_target = 0;
	int vneg_target = 0;
	struct device_node *np = NULL;
	struct tps65132_device_info *di = NULL;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_TPS65132);
	if (!np) {
		pr_err("NOT FOUND device node %s!\n", DTS_COMP_TPS65132);
		retval = -ENODEV;
		goto failed_1;
	}

	gpio_vsp_enable = of_get_named_gpio(np, "gpios", 0);
	gpio_vsn_enable = of_get_named_gpio(np, "gpios", 1);

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		pr_err("[%s,%d]: need I2C_FUNC_I2C\n",__FUNCTION__,__LINE__);
		retval = -ENODEV;
		goto failed_1;
	}

	di = kzalloc(sizeof(*di), GFP_KERNEL);
	if (!di) {
		dev_err(&client->dev, "failed to allocate device info data\n");
		retval = -ENOMEM;
		goto failed_1;
	}

	i2c_set_clientdata(client, di);
	di->dev = &client->dev;
	di->client = client;

	if (!fastboot_display_enable) {
		tps65132_start_setting();
	}

	tps65132_get_target_voltage(&vpos_target, &vneg_target);

	nRet = tps65132_reg_inited(di->client, (u8)vpos_target, (u8)vneg_target);
	if (nRet > 0) {
		pr_info("tps65132 inited needn't reset value\n");
	} else if (nRet < 0) {
		pr_err("tps65132 I2C read fail\n");
		retval = -ENODEV;
		goto failed_2;
	} else {
		nRet = tps65132_reg_init(di->client, (u8)vpos_target, (u8)vneg_target);
		if (nRet) {
			pr_err("tps65132_reg_init failed\n");
			retval = -ENODEV;
			goto failed_2;
		}
		pr_info("tps65132 inited succeed\n");
	}

	#ifdef CONFIG_HUAWEI_HW_DEV_DCT
		/* detect current device successful, set the flag as present */
		set_hw_dev_flag(DEV_I2C_DC_DC);
	#endif

failed_2:
	if (!fastboot_display_enable) {
		tps65132_finish_setting();
	}

	if (di)
		kfree(di);

failed_1:
	return retval;
}



static const struct of_device_id tps65132_match_table[] = {
	{
		.compatible = DTS_COMP_TPS65132,
		.data = NULL,
	},
	{},
};


static const struct i2c_device_id tps65132_i2c_id[] = {
	{ "tps65132", 0 },
	{ }
};


MODULE_DEVICE_TABLE(of, tps65132_match_table);


static struct i2c_driver tps65132_driver = {
	.id_table = tps65132_i2c_id,
	.probe = tps65132_probe,
	.driver = {
		.name = "tps65132",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(tps65132_match_table),
	},
};

static int __init tps65132_module_init(void)
{
	int ret = 0;

	ret = i2c_add_driver(&tps65132_driver);
	if (ret)
		pr_err("Unable to register tps65132 driver\n");

	return ret;

}
static void __exit tps65132_exit(void)
{
	i2c_del_driver(&tps65132_driver);
}

late_initcall(tps65132_module_init);
module_exit(tps65132_exit);

MODULE_DESCRIPTION("TPS65132 driver");
MODULE_LICENSE("GPL");
