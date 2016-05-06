/*
 * Copyright (C) huawei company
 *
 * This	program	is free	software; you can redistribute it and/or modify
 * it under	the	terms of the GNU General Public	License	version	2 as
 * published by	the	Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/mtd/hisi_nve_interface.h>
#include <linux/module.h>

#include <huawei_platform/log/hw_log.h>
#define HWLOG_TAG tp_color
HWLOG_REGIST();

#define WHITE	0xE1
#define BLACK	0xD2
#define PINK	0xC3
#define RED		0xB4
#define YELLOW	0xA5
#define BLUE	0x96
#define GOLD  0x87
#define TP_COLOR_BUF_SIZE		20
static unsigned char tp_color_buf[TP_COLOR_BUF_SIZE];

u8 cypress_tp_color[15]={0};

/******************************************************************************
Function:	    read_tp_color
******************************************************************************/
int read_tp_color(void)
{
	int tp_color;
	hwlog_info("tp color is %s\n", tp_color_buf);

	tp_color = (int)simple_strtol(tp_color_buf, NULL, 0);
	return tp_color;
}

static int __init early_parse_tp_color_cmdline(char *arg)
{
	int len = 0;
	memset(tp_color_buf, 0, sizeof(tp_color_buf));
	if (arg) {
		len = strlen(arg);

		if (len > sizeof(tp_color_buf)) {
			len = sizeof(tp_color_buf);
		}
		memcpy(tp_color_buf, arg, len);
	} else {
		hwlog_info("%s : arg is NULL\n", __func__);
	}

	return 0;
}
early_param("TP_COLOR", early_parse_tp_color_cmdline);

int is_color_correct(u8 color)
{
	return ((color&0x0f)==((~(color>>4))&0x0f));
}
static int read_tp_color_from_nv(char *color_info)
{
	int ret=0;
	struct hisi_nve_info_user user_info;

	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = 1;
	user_info.nv_number = 16;
	user_info.valid_size = 15;
	strncpy(user_info.nv_name, "TPCOLOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name)-1]='\0';
	ret = hisi_nve_direct_access(&user_info);
	if (ret)
	{
		hwlog_err("hisi_nve_direct_access read error(%d)\n", ret);
		return -1;
	}
	if((!strncmp(user_info.nv_data, "white", strlen("white")))
		||(!strncmp(user_info.nv_data, "black", strlen("black")))
		||(!strncmp(user_info.nv_data, "pink", strlen("pink")))
		||(!strncmp(user_info.nv_data, "red", strlen("red")))
		||(!strncmp(user_info.nv_data, "yellow", strlen("yellow")))
		||(!strncmp(user_info.nv_data, "blue", strlen("blue")))
		||(!strncmp(user_info.nv_data, "gold", strlen("gold"))))
	{
		strncpy(color_info, user_info.nv_data, strlen(user_info.nv_data));
		color_info[strlen(user_info.nv_data)]='\0';
		return 0;
	}
	else
	{
		hwlog_err("[%s]:read_tp_color_from_nv read unormal value!!\n", __func__);
		return -1;
	}
}
static int write_tp_color_to_nv(void)
{
	int ret=0;
	u8 lcd_id=0;
	u8 phone_color=0;
	struct hisi_nve_info_user user_info;

	memset(&user_info, 0, sizeof(user_info));
	lcd_id = read_tp_color();
	if (lcd_id != 0xff) {
		hwlog_info("lcd id is %u from read tp color\n", lcd_id);
	}
	if(is_color_correct(cypress_tp_color[0]))
		phone_color=cypress_tp_color[0];
	else if(is_color_correct(lcd_id))
		phone_color=lcd_id;
	else
	{
		hwlog_err("LCD/TP ID both error!\n");
		return -1;
	}
	switch(phone_color)
	{
	case WHITE:
			strncpy(user_info.nv_data, "white", sizeof(user_info.nv_data));
			break;
	case BLACK:
			strncpy(user_info.nv_data, "black", sizeof(user_info.nv_data));
			break;
	case PINK:
			strncpy(user_info.nv_data,"pink", sizeof(user_info.nv_data));
			break;
	case RED:
			strncpy(user_info.nv_data,"red", sizeof(user_info.nv_data));
			break;
	case YELLOW:
			strncpy(user_info.nv_data,"yellow", sizeof(user_info.nv_data));
			break;
	case BLUE:
			strncpy(user_info.nv_data,"blue", sizeof(user_info.nv_data));
			break;
	case GOLD:
			strncpy(user_info.nv_data,"gold", sizeof(user_info.nv_data));
			break;
	default:
			strncpy(user_info.nv_data,"", sizeof(user_info.nv_data));
			break;
	}
	user_info.nv_operation = 0;
	user_info.nv_number = 16;
	user_info.valid_size = 15;
	strncpy(user_info.nv_name, "TPCOLOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name)-1]='\0';
	ret = hisi_nve_direct_access(&user_info);
	if (ret)
	{
		hwlog_err("hisi_nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	hwlog_info("[%s]:(%s)\n", __func__, user_info.nv_data);
	return ret;
}
static ssize_t attr_get_tp_color_info(struct device *dev, struct device_attribute *attr, char *buf)
{
	int ret=0;
	u8 lcd_id=0;
	u8 phone_color=0;
	lcd_id = read_tp_color();
	if (lcd_id != 0xff) {
		hwlog_info("lcd id is %u from read tp color\n", lcd_id);
	}
	hwlog_info("%s:tp id=%x   lcd id=%x.\n", __func__, cypress_tp_color[0], lcd_id);
	if(is_color_correct(cypress_tp_color[0]))
		phone_color=cypress_tp_color[0];
	else if(is_color_correct(lcd_id))
		phone_color=lcd_id;
	else
	{
		ret=read_tp_color_from_nv(buf);
		if(ret) strncpy(buf,"", sizeof(""));
		return strlen(buf);
	}
	switch(phone_color)
	{
	case WHITE:
			strncpy(buf,"white", sizeof("white"));
			break;
	case BLACK:
			strncpy(buf,"black", sizeof("black"));
			break;
	case PINK:
			strncpy(buf,"pink", sizeof("pink"));
			break;
	case RED:
			strncpy(buf,"red", sizeof("red"));
			break;
	case YELLOW:
			strncpy(buf,"yellow", sizeof("yellow"));
			break;
	case BLUE:
			strncpy(buf,"blue", sizeof("blue"));
			break;
	case GOLD:
			strncpy(buf,"gold", sizeof("gold"));
			break;
	default:
			strncpy(buf,"", sizeof(""));
			break;
	}
	return strlen(buf);
}

static ssize_t attr_set_tp_color_info(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long val = simple_strtoul(buf, NULL, 10);
	hwlog_info("[%s] val=%lu\n", __func__, val);
	if (val == 1) {
		write_tp_color_to_nv();
	}
	return count;
}
static struct device_attribute tp_color_file =
	__ATTR(tp_color_info, 0664, attr_get_tp_color_info, attr_set_tp_color_info);

static struct platform_device huawei_tp_color = {
	.name = "huawei_tp_color",
	.id = -1,
};

static int __init tp_color_info_init(void)
{
	int ret = 0;
	hwlog_info("[%s] ++", __func__);

	ret = platform_device_register(&huawei_tp_color);
	if (ret) {
		hwlog_err("%s: platform_device_register failed, ret:%d.\n",
				__func__, ret);
		goto REGISTER_ERR;
	}
	if (device_create_file(&huawei_tp_color.dev, &tp_color_file)) {
		hwlog_err("%s:Unable to create interface\n", __func__);
		goto SYSFS_CREATE_FILE_ERR;
	}
	hwlog_info("[%s] --", __func__);
	return 0;

SYSFS_CREATE_FILE_ERR:
	platform_device_unregister(&huawei_tp_color);
REGISTER_ERR:
	return ret;

}

device_initcall(tp_color_info_init);
MODULE_DESCRIPTION("tp color info");
MODULE_AUTHOR("huawei driver group of k3");
MODULE_LICENSE("GPL");
