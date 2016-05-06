/*
 * Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
 * Qualcomm PMIC hisi_peripheral Thermal Manager driver
 */

#define pr_fmt(fmt) "%s: " fmt, __func__

#include <linux/module.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/completion.h>
#include <linux/of.h>
#include <linux/device.h>
#include <linux/hisi/hisi_rproc.h>
#include <linux/hisi/ipc_msg.h>
#include <linux/huawei/hisi_adc.h>
#include "hisi_peripheral_tm.h"


#define PM_TM_DEV_NAME	"hisi_peripheral_tm"
#define HISI_PERIP_RPROC_SEND_ID	HISI_RPROC_LPM3_MBX28
#define HISI_TM_RPROC_RECV_ID		HISI_RPROC_LPM3_MBX0
#define HISI_PERIP_TO_LPM3_MSG_NUM	2
#define HISI_PERIP_RED_BACK_MSG_NUM	2
#define TSENSOR_USED_NUM		5
#define BOARD_BUFFER_LENGTH 40

enum tm_trip_type {
	TM_TRIP_HOT = 0,
	TM_TRIP_COOL,
	TM_TRIP_MAX,
};

struct config {
	u8 channel;
	u8 ret;
	u16 value; /*volt for HKADC ,ADC for Tsensor*/
};

struct tm_switch {
	u8 channel;/*tid*/
	u8 which_thershold;/*level*/
	u8 ret;
	u8 res;
};

struct tm_event {
	u8 channel;/*tid*/
	u8 which_thershold;/*level*/
	u16 value;
};

typedef union {
	unsigned char ipc_data[4];
	struct config setting;
	struct config getting;
	struct tm_switch onoff;
	struct tm_event  notify;
} U_THERMAL_IPC_PARA;/*IPC Data Register1*/

enum hisi_peripheral_temp_chanel {
	DETECT_SYSTEM_H_CHANEL = 0,
	DETECT_FLASH_LED_CHANEL,
	DETECT_CHARGER_CHANEL,
	DETECT_PA_0_CHANEL,
	DETECT_PA_1_CHANEL,
	DETECT_DCXO0_CHANEL,
	DETECT_SHELL_CHANEL,
	DETECT_CHARGER1_CHANEL
};

char *hisi_peripheral_chanel[] = {
	[DETECT_SYSTEM_H_CHANEL] = "system_h",
	[DETECT_FLASH_LED_CHANEL] = "flash_led",
	[DETECT_CHARGER_CHANEL] = "charger",
	[DETECT_PA_0_CHANEL] = "pa_0",
	[DETECT_PA_1_CHANEL] = "pa_1",
	[DETECT_DCXO0_CHANEL] = "dcxo0",
	[DETECT_SHELL_CHANEL] = "shell",
	[DETECT_CHARGER1_CHANEL] = "charger1",
};

static struct hisi_peripheral_tm_chip *gtm_dev;
int g_tm_debug = 0;
void tm_debug(int onoff)
{
	g_tm_debug = onoff;
}

static int hisi_peripheral_tm_get_temp(struct thermal_zone_device *thermal,
				      unsigned long *temp)
{
	struct periph_tsens_tm_device_sensor *chip = thermal->devdata;
	int ret = 0;
	int volt = 0;

	if (!chip || !temp)
		return -EINVAL;

	volt = hisi_adc_get_value(chip->chanel);
	if (volt <= 0) {
		pr_err("AP get volt value is fail,chan[%d]volt[%d]!\n", chip->chanel, volt);
		volt = ADC_RTMP_DEFAULT_VALUE;
	}

	ret = hisi_peripheral_ntc_2_temp(chip, temp, volt);
	if (ret < 0) {
		pr_err("%s,get temp failed\n\r", __func__);
		return ret;
	}

	return 0;
}

static int hisi_peripheral_tm_get_mode(struct thermal_zone_device *thermal,
			      enum thermal_device_mode *mode)
{
	struct periph_tsens_tm_device_sensor *chip = thermal->devdata;

	if (!chip || !mode)
		return -EINVAL;

	*mode = chip->mode;

	return 0;
}

int hisi_peripheral_tm_target(union ipc_data *tm_ipc, int *value)
{
	int ret = 0;
	u32 ack_buffer[2] = {0};
	union ipc_data *ipc_phr = (union ipc_data *)&ack_buffer[0];
	U_THERMAL_IPC_PARA *tm_ipc_para = (U_THERMAL_IPC_PARA *)&ack_buffer[1];

	ret = RPROC_SYNC_SEND(HISI_PERIP_RPROC_SEND_ID,
			(rproc_msg_t *)tm_ipc,
			(rproc_msg_len_t)HISI_PERIP_TO_LPM3_MSG_NUM,
			(rproc_msg_t *)ack_buffer,
			(rproc_msg_len_t)HISI_PERIP_RED_BACK_MSG_NUM);
	if (ret) {
		pr_err("[%s] send data:[%d][%d]\n", __func__, tm_ipc->data[0], tm_ipc->data[1]);
		return -EINVAL;
	}

	if (ack_buffer[0] != tm_ipc->data[0]) {
		pr_err("[%s] recv data0 should same to send data0, [%d]!=[%d]\n",
			__func__, ack_buffer[0] , tm_ipc->data[0]);
		return -EINVAL;
	}

	if (g_tm_debug)
		pr_err("[%s]SEN[0x%0x][0x%0x]ACK[0x%0x][0x%0x]\n", __func__,
			tm_ipc->data[0], tm_ipc->data[1], ack_buffer[0], ack_buffer[1]);

	switch (ipc_phr->cmd_mix.cmd) {
	case CMD_NOTIFY:
		if (value)
			*value = tm_ipc_para->getting.value;
	case CMD_SETTING:
	case CMD_ON:
	case CMD_OFF:
		break;
	default:
		pr_err("[%s] no this cmd ,ack_buffer reg0[%d]reg1[%d]\n",
					__func__,  ack_buffer[0], ack_buffer[1]);
		return -EINVAL;
	}

	return 0;
}

static int hisi_peripheral_tm_get_trip_temp(struct thermal_zone_device *thermal,
				int trip, unsigned long *temp)
{
	struct periph_tsens_tm_device_sensor *tm_sensor = thermal->devdata;
	union ipc_data tm_ipc;
	int volt = 0;
	int ret = 0;
	U_THERMAL_IPC_PARA *tm_ipc_para = (U_THERMAL_IPC_PARA *)tm_ipc.cmd_mix.cmd_para;

	if (!tm_sensor || trip < 0 || !temp)
		return -EINVAL;

	memset((void *)&tm_ipc, 0, sizeof(tm_ipc));

	switch (trip) {
	case TM_TRIP_HOT:
		tm_ipc.cmd_mix.cmd_type = TYPE_UPLIMIT;
		break;
	case TM_TRIP_COOL:
		tm_ipc.cmd_mix.cmd_type = TYPE_DNLIMIT;
		break;
	default:
		return -EINVAL;
	}

	tm_ipc.cmd_mix.cmd = CMD_NOTIFY;
	tm_ipc.cmd_mix.cmd_obj = OBJ_HKADC;
	tm_ipc.cmd_mix.cmd_src = OBJ_AP;
	tm_ipc_para->getting.channel = tm_sensor->chanel;

	ret = hisi_peripheral_tm_target(&tm_ipc, &volt);
	if (ret < 0) {
		pr_err("[%s] hisi_peripheral_tm_target ret[%d]\n", __func__, ret);
		return -EINVAL;
	}

	ret = hisi_peripheral_ntc_2_temp(tm_sensor, temp, volt);
	if (ret < 0) {
		pr_err("[%s] hisi_peripheral_get_temp ret=%d volt[%d]\n", __func__, ret, volt);
		return -EINVAL;
	}

	return 0;
}

static int hisi_peripheral_tm_set_trip_temp(struct thermal_zone_device *thermal,
				int trip, unsigned long temp)
{
	struct periph_tsens_tm_device_sensor *tm_sensor = thermal->devdata;
	u16 volt = 0;
	int ret = 0;
	union ipc_data tm_ipc;
	U_THERMAL_IPC_PARA *tm_ipc_para = (U_THERMAL_IPC_PARA *)tm_ipc.cmd_mix.cmd_para;

	if (!tm_sensor || trip < 0 || (long)temp < NTC_TEMP_MIN_VALUE || (long)temp > NTC_TEMP_MAX_VALUE) {
		pr_err("[%s] parm err temp[%lu]\n", __func__, temp);
		return -EINVAL;
	}

	memset((void *)&tm_ipc, 0, sizeof(tm_ipc));

	ret = hisi_peripheral_temp_2_ntc(tm_sensor, temp, &volt);
	if (ret < 0) {
		pr_err("[%s]: hisi_peripheral_temp_2_ntc ret[%d]\n", __func__, ret);
		return -EINVAL;
	}

	switch (trip) {
	case TM_TRIP_HOT:
		tm_ipc.cmd_mix.cmd_type = TYPE_UPLIMIT;
		break;
	case TM_TRIP_COOL:
		tm_ipc.cmd_mix.cmd_type = TYPE_DNLIMIT;
		break;
	default:
		return -EINVAL;
	}

	tm_ipc.cmd_mix.cmd = CMD_SETTING;
	tm_ipc.cmd_mix.cmd_obj = OBJ_HKADC;
	tm_ipc.cmd_mix.cmd_src = OBJ_AP;
	tm_ipc_para->setting.channel = tm_sensor->chanel;
	tm_ipc_para->setting.value = volt;

	ret = hisi_peripheral_tm_target(&tm_ipc, NULL);
	if (ret < 0) {
		pr_err("[%s] hisi_peripheral_tm_target ret[%d]\n", __func__, ret);
		return -EINVAL;
	}

	return 0;
}

static int hisi_peripheral_tm_trip_type(struct thermal_zone_device *thermal,
			int trip, enum thermal_trip_type *type)
{
	struct periph_tsens_tm_device_sensor *tm_sensor = thermal->devdata;
	if (!tm_sensor || trip < 0 || !type)
		return -EINVAL;
	switch (trip) {
	case TM_TRIP_HOT:
		*type = THERMAL_TRIP_CONFIGURABLE_HI;
		break;
	case TM_TRIP_COOL:
		*type = THERMAL_TRIP_CONFIGURABLE_LOW;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int hisi_peripheral_tm_activate_trip_type(struct thermal_zone_device *thermal,
		int trip, enum thermal_trip_activation_mode mode)
{
	struct periph_tsens_tm_device_sensor *tm_sensor = thermal->devdata;
	int ret = 0;
	union ipc_data tm_ipc;
	U_THERMAL_IPC_PARA *tm_ipc_para = (U_THERMAL_IPC_PARA *)tm_ipc.cmd_mix.cmd_para;

	if (!tm_sensor || trip < 0)
		return -EINVAL;

	memset((void *)&tm_ipc, 0, sizeof(tm_ipc));

	if (trip == TM_TRIP_HOT || trip == TM_TRIP_COOL)
		tm_ipc_para->onoff.which_thershold = !trip;
	else {
		pr_err("[%s]trip[%d]\n", __func__, trip);
		return -EINVAL;
	}

	if (mode == THERMAL_TRIP_ACTIVATION_ENABLED)
		tm_ipc.cmd_mix.cmd = CMD_ON;
	else
		tm_ipc.cmd_mix.cmd = CMD_OFF;

	tm_ipc.cmd_mix.cmd_type = TYPE_T;
	tm_ipc.cmd_mix.cmd_obj = OBJ_HKADC;
	tm_ipc.cmd_mix.cmd_src = OBJ_AP;
	tm_ipc_para->onoff.channel = tm_sensor->chanel;

	ret = hisi_peripheral_tm_target(&tm_ipc, NULL);
	if (ret) {
		pr_err("[%s] hisi_peripheral_tm_target ret[%d]\n", __func__,  ret);
		return -EINVAL;
	}

	return 0;
}


static struct thermal_zone_device_ops hisi_peripheral_thermal_zone_ops = {
	.get_temp = hisi_peripheral_tm_get_temp,
	.get_mode = hisi_peripheral_tm_get_mode,
	.get_trip_type = hisi_peripheral_tm_trip_type,
	.activate_trip_type = hisi_peripheral_tm_activate_trip_type,
	.get_trip_temp = hisi_peripheral_tm_get_trip_temp,
	.set_trip_temp = hisi_peripheral_tm_set_trip_temp,
};

static int get_equipment_tree_data(struct platform_device *pdev, int sensor_num)
{
	struct device_node *of_node = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	int equipment_chanel_value = 0;
	const char *equipment_chanel_ntc_name, *equipment_chanel_ntc_state;
	int i, rc, j;
	char temp_buffer[BOARD_BUFFER_LENGTH];

	/*get detect equipment thermal HKADC chanel, name and state*/
	for (i = DETECT_SYSTEM_H_CHANEL, j = DETECT_SYSTEM_H_CHANEL; i < sensor_num; i++, j++) {
		memset((void *)temp_buffer, 0, sizeof(temp_buffer));
		snprintf(temp_buffer, sizeof(temp_buffer), "hisi,detect_%s_tm_chanel", hisi_peripheral_chanel[i]);
		rc = of_property_read_u32(of_node, temp_buffer, &equipment_chanel_value);
		if (rc) {
			dev_err(&pdev->dev, "canot get %d tm chanel\n", i);
			rc = -ENODEV;
			goto read_chanel_fail;
		}
		gtm_dev->sensor[i].chanel = equipment_chanel_value;

		memset((void *)temp_buffer, 0, sizeof(temp_buffer));
		snprintf(temp_buffer, sizeof(temp_buffer), "hisi,detect_%s_tm_state", hisi_peripheral_chanel[i]);
		rc = of_property_read_string(of_node, temp_buffer, &equipment_chanel_ntc_state);
		if (rc) {
			dev_err(dev, "detect %d tm ntc state failed\n", i);
			rc = -EINVAL;
			goto read_state_fail;
		}
		if (strcmp(equipment_chanel_ntc_state, "enable") == 0) {
			gtm_dev->sensor[i].state = 1;
		} else if (strcmp(equipment_chanel_ntc_state, "disable") == 0) {
			gtm_dev->sensor[i].state = 0;
		} else {
			dev_err(dev, "input  ntc %d state is error\n\r", i);
			rc = -EINVAL;
			goto read_state_fail;
		}

		memset(temp_buffer, 0, sizeof(temp_buffer));
		snprintf(temp_buffer, sizeof(temp_buffer), "hisi,detect_%s_tm_ntc", hisi_peripheral_chanel[i]);
		rc = of_property_read_string(of_node, temp_buffer, &equipment_chanel_ntc_name);
		if (rc) {
			dev_err(dev, "detect %d tm ntc name failed\n", i);
			rc = -EINVAL;
			goto read_name_fail;
		}

		gtm_dev->sensor[i].ntc_name = (const char *)kmemdup((const void *)equipment_chanel_ntc_name, strlen(equipment_chanel_ntc_name) + 1, GFP_KERNEL);
		if (!gtm_dev->sensor[i].ntc_name) {
			dev_err(dev, "application %d chanel ntc name room failing\n", i);
			rc = -EINVAL;
			goto kmalloc_fail;
		}
	}

	return 0;

kmalloc_fail:
read_name_fail:
read_state_fail:
read_chanel_fail:
	for (i = DETECT_SYSTEM_H_CHANEL; i < j; i++)
		kfree(gtm_dev->sensor[i].ntc_name);

	return rc;
}
static int get_periph_tm_device_tree_data(struct platform_device *pdev)
{
	const struct device_node *of_node = pdev->dev.of_node;
	u32 rc = 0, periph_tsens_num_sensors = 0;

	rc = of_property_read_u32(of_node,
			"hisi,peripheral_sensors", &periph_tsens_num_sensors);
	if (rc) {
		dev_err(&pdev->dev, "missing sensor number\n");
		return -ENODEV;
	}

	gtm_dev = devm_kzalloc(&pdev->dev, sizeof(struct hisi_peripheral_tm_chip) +
			periph_tsens_num_sensors * sizeof(struct periph_tsens_tm_device_sensor), GFP_KERNEL);
	if (gtm_dev == NULL) {
		pr_err("%s: kzalloc() failed.\n", __func__);
		return -ENOMEM;
	}

	gtm_dev->tsens_num_sensor = periph_tsens_num_sensors;
	rc = get_equipment_tree_data(pdev, periph_tsens_num_sensors);
	if (rc) {
		dev_err(&pdev->dev, "get periph equipment dts data error\n");
		return -ENODEV;
	}

	return rc;
}

static int hisi_tm_m3_notifier(struct notifier_block *nb, unsigned long len, void *msg)
{
	int i, hw_channel = 0;
	union ipc_data *ptm_ipc = (union ipc_data *)msg;
	U_THERMAL_IPC_PARA *tm_ipc_para = (U_THERMAL_IPC_PARA *)ptm_ipc->cmd_mix.cmd_para;
	int m3_notfier_flag = IPC_CMD(OBJ_LPM3, OBJ_HKADC, CMD_NOTIFY, TYPE_T);

	if (m3_notfier_flag != ptm_ipc->data[0])
		return 0;

	if (!gtm_dev)
		return 0;

	hw_channel = (tm_ipc_para->notify).channel;

	for (i = 0; i < gtm_dev->tsens_num_sensor; i++) {
		if (gtm_dev->sensor[i].chanel == hw_channel) {
			schedule_work(&gtm_dev->sensor[i].work);
			return 0;
		}
	}

	return 0;
}

static void notify_thermal_app(struct work_struct *work)
{
	struct periph_tsens_tm_device_sensor *tm = container_of(work,
		struct periph_tsens_tm_device_sensor, work);
	sysfs_notify(&tm->tz_dev->device.kobj, NULL, "type");
	if (1 == g_tm_debug)
		pr_err("[%s]TZ[%s] hw channel[%d]\n", __func__, tm->tz_dev->type, tm->chanel);
}

static int hisi_peripheral_tm_probe(struct platform_device *pdev)
{
	int rc = 0;
	char name[BOARD_BUFFER_LENGTH];
	int i, k, flag;

	rc = get_periph_tm_device_tree_data(pdev);
	if (rc) {
		dev_err(&pdev->dev, "Error reading peripheral tm \n");
		return rc;
	}

	gtm_dev->pdev = pdev;

	for (i = DETECT_SYSTEM_H_CHANEL, flag = DETECT_SYSTEM_H_CHANEL; i < (gtm_dev->tsens_num_sensor + DETECT_SYSTEM_H_CHANEL); i++) {
		int k = 0, mask = 0;
		if (gtm_dev->sensor[i].state == 0)
			continue;

		memset((void *)name, 0, sizeof(name));
		snprintf(name, sizeof(name), "%s", hisi_peripheral_chanel[i]);

		gtm_dev->sensor[i].mode = THERMAL_DEVICE_ENABLED;
		gtm_dev->sensor[i].sensor_num = (i + TSENSOR_USED_NUM);

		for (k = 0; k < TM_TRIP_MAX; k++)
			mask |= 1 << k;

		gtm_dev->sensor[i].tz_dev = thermal_zone_device_register(name,
				TM_TRIP_MAX, mask, &gtm_dev->sensor[i],
				&hisi_peripheral_thermal_zone_ops, NULL, 0, 0);
		flag++;
		if (IS_ERR(gtm_dev->sensor[i].tz_dev)) {
			dev_err(&pdev->dev, "thermal_zone_device_register() failed.\n");
			rc = -ENODEV;
			goto fail;
		}
	}

	platform_set_drvdata(pdev, gtm_dev);

	for (k = 0; k < gtm_dev->tsens_num_sensor; k++)
		INIT_WORK(&gtm_dev->sensor[k].work, notify_thermal_app);

	gtm_dev->nb.next = NULL;
	gtm_dev->nb.notifier_call = hisi_tm_m3_notifier;
	rc = RPROC_MONITOR_REGISTER(HISI_TM_RPROC_RECV_ID, &gtm_dev->nb);
	if (rc) {
		dev_err(&pdev->dev, "[%s]rproc monitor register Failed!\n", __func__);
		return -ENODEV;
	}

	return 0;
fail:
	for (i = DETECT_SYSTEM_H_CHANEL; i < flag; i++)
		thermal_zone_device_unregister(gtm_dev->sensor[i].tz_dev);

	return rc;
}

static int hisi_peripheral_tm_remove(struct platform_device *pdev)
{
	struct hisi_peripheral_tm_chip *chip = platform_get_drvdata(pdev);
	int i;

	if (chip) {
		platform_set_drvdata(pdev, NULL);
		for (i = DETECT_SYSTEM_H_CHANEL; i < (gtm_dev->tsens_num_sensor + DETECT_SYSTEM_H_CHANEL); i++) {
			kfree(gtm_dev->sensor[i].ntc_name);
			thermal_zone_device_unregister(gtm_dev->sensor[i].tz_dev);
		}
		kfree(chip);
	}
	return 0;
}

static struct of_device_id hisi_peripheral_tm_match[] = {
	{	.compatible = "hisi,hisi-peripheral-tm",
	},
	{}
};

static struct platform_driver hisi_peripheral_tm_driver = {
	.probe	= hisi_peripheral_tm_probe,
	.remove	= hisi_peripheral_tm_remove,
	.driver	= {
		.name = PM_TM_DEV_NAME,
		.owner = THIS_MODULE,
		.of_match_table = hisi_peripheral_tm_match,
	},
};

static int __init hisi_peripheral_tm_init(void)
{
	return platform_driver_register(&hisi_peripheral_tm_driver);
}

static void __exit hisi_peripheral_tm_exit(void)
{
	platform_driver_unregister(&hisi_peripheral_tm_driver);
}

module_init(hisi_peripheral_tm_init);
module_exit(hisi_peripheral_tm_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PM Thermal Manager driver");
MODULE_VERSION("1.0");
MODULE_ALIAS("platform:" PM_TM_DEV_NAME);
