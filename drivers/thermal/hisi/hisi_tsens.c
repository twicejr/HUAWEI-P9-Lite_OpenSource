/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/thermal.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/hisi/hisi_rproc.h>

#define TSENSOR_RPROC_SEND_ID	HISI_RPROC_LPM3_MBX28
#define TSENSOR_RPROC_RECV_ID	HISI_RPROC_LPM3_MBX0

struct tsensor_config {
	u8 channel;/*tid*/
	u8 ret;
	u16 temp;
};

struct tsensor_switch {
	u8 channel;/*tid*/
	u8 which_thershold;/*level*/
	u8 ret;
	u8 res;
};

struct tsensor_event {
	u8 channel;/*tid*/
	u8 which_thershold;/*level*/
	u16 temp;
};

typedef union {
	unsigned char ipc_data[4];
	struct tsensor_config setting;
	struct tsensor_config getting;
	struct tsensor_switch onoff;
	struct tsensor_event  notify;
} U_TSENSOR_IPC;

static DEFINE_MUTEX(tsens_mutex);

#define TSENS_DRIVER_NAME	"hisi-tsens"
static struct tsens_tm_device	*g_tmdev;

#define CLUSTER0				0
#define CLUSTER1				1
#define GPU					2
#define MODEM					3
#define DDR					4

/*lint -e750 -esym(750,*) */
#define	TSENSOR_BUFFER_LENGTH	40
/*lint -e750 -esym(750,*) */

char *hisi_tsensor_name[] = {
	[CLUSTER0] = "cluster0",
	[CLUSTER1] = "cluster1",
	[GPU] = "gpu",
	[MODEM] = "modem",
	[DDR] = "ddr",
};
EXPORT_SYMBOL_GPL(hisi_tsensor_name);

/* Trips: warm and cool */
enum tsens_trip_type {
	TSENS_TRIP_WARM = 0,
	TSENS_TRIP_COOL,
	TSENS_TRIP_NUM,
};

struct tsens_tm_device_sensor {
	struct thermal_zone_device		*tz_dev;
	enum thermal_device_mode		mode;
	unsigned int			sensor_num;
	struct work_struct			work;
	u32				enable[2];
	u32				disable[2];
	u32				read_thermal_h[2];
	u32				read_thermal_l[2];
	u32				write_thermal_h[2];
	u32				write_thermal_l[2];
	u32				read_temperature[2];
};

struct tsens_tm_device {
	struct platform_device		*pdev;
	uint32_t				tsens_num_sensor;
	struct notifier_block		*nb;
	struct hisi_mbox			*mbox;
	struct work_struct			tsens_work;
	u32				tsensor_enable_flag;
	u32				tsensor_disable_flag;
	u32				read_thermal_h_flag;
	u32				read_thermal_l_flag;
	u32				write_thermal_h_flag;
	u32				write_thermal_l_flag;
	u32				read_temperature_flag;
	u32				int_reback_flag;
	struct tsens_tm_device_sensor	sensor[0];/*put the struct last place*/
};
struct tsens_context {
	u32		sensor_id;
	u32		sensor_cur_temp;
	u32		sensor_thermal_h;
	u32		sensor_thermal_l;
};

enum {
	TSENSOR_ENABLE = 0,
	TSENSOR_DISABLE,
	TSENSOR_READ_THERMAL_H,
	TSENSOR_READ_THERMAL_L,
	TSENSOR_WRITE_THERMAL_H,
	TSENSOR_WRITE_THERMAL_L,
	TSENSOR_READ_TEMPERATURE,
};

#define TSENS_TO_LPM3_MSG_NUM	2
#define TSENS_RED_BACK_MSG_NUM	2

#define TSENSOR_8BIT			8
#define TSENS_THRESHOLD_MIN_CODE	0x0
#define TSENS_TEMP_START_VALUE		(-40)/* -40 deg C */
#define TSENS_ADC_START_VALUE		(116)
#define TSENS_ADC_END_VALUE			(922)
#define TSENS_TEMP_END_VALUE		125


int g_tsensor_debug = 0;
void tsen_debug(int onoff)
{
	g_tsensor_debug = onoff;
}
static int tsens_tz_code_to_degc(int adc_val)
{
	int temp = 0;

	if ((TSENS_THRESHOLD_MIN_CODE > adc_val) || (adc_val > TSENS_ADC_END_VALUE)) {
		pr_debug("adc_to_temp_conversion failed \n");
		return temp;
	}

	temp = ((adc_val - TSENS_ADC_START_VALUE) * (TSENS_TEMP_END_VALUE - TSENS_TEMP_START_VALUE))
			/ (TSENS_ADC_END_VALUE - TSENS_ADC_START_VALUE);
	temp = temp + TSENS_TEMP_START_VALUE;

	return temp;
}

static int tsens_tz_degc_to_code(unsigned long degc)
{
	int code = 0;

	if ((long)degc > TSENS_TEMP_END_VALUE)
		return TSENS_ADC_END_VALUE;
	else if ((long)degc < TSENS_TEMP_START_VALUE)
		return TSENS_THRESHOLD_MIN_CODE;

	code = TSENS_ADC_START_VALUE + (degc - TSENS_TEMP_START_VALUE) * (TSENS_ADC_END_VALUE - TSENS_ADC_START_VALUE) /
			(TSENS_TEMP_END_VALUE - TSENS_TEMP_START_VALUE);

	return code;
}


static int hisi_tsens_cmd_send(struct tsens_tm_device_sensor *tm_sensor, int cmd)
{
	int i, rc = 0;
	u32 ack_buffer[2];
	u32 tx_buffer[2] = {0};
	int temperature;
	int id;
	U_TSENSOR_IPC *tsen_ipcdata = (U_TSENSOR_IPC *)(&ack_buffer[1]);

	if (TSENSOR_ENABLE == cmd) {
		tx_buffer[0] = tm_sensor->enable[0];/*g_tmdev->tsensor_enable_flag;*/
		tx_buffer[1] = tm_sensor->enable[1];/*(0x01 << TSENSOR_8BIT) | tm_sensor->sensor_num; lpm3:  level(1:HIGH;0:LOW)|tid*/
	} else if (TSENSOR_DISABLE == cmd) {
		tx_buffer[0] = tm_sensor->disable[0];/*g_tmdev->tsensor_disable_flag*/
		tx_buffer[1] = tm_sensor->disable[1];/*(0x01 << TSENSOR_8BIT) | tm_sensor->sensor_num;  lpm3:  level(1:HIGH;0:LOW)|tid*/
	} else if (TSENSOR_READ_THERMAL_H == cmd) {
		tx_buffer[0] = tm_sensor->read_thermal_h[0];/*g_tmdev->read_thermal_h_flag*/
		tx_buffer[1] = tm_sensor->read_thermal_h[1];/*tm_sensor->sensor_num*/
	} else if (TSENSOR_READ_THERMAL_L == cmd) {
		tx_buffer[0] = tm_sensor->read_thermal_l[0];/*g_tmdev->read_thermal_l_flag*/
		tx_buffer[1] = tm_sensor->read_thermal_l[1];/* tm_sensor->sensor_num*/
	} else if (TSENSOR_WRITE_THERMAL_H == cmd) {
		tx_buffer[0] = tm_sensor->write_thermal_h[0];/*g_tmdev->write_thermal_h_flag*/
		tx_buffer[1] = tm_sensor->write_thermal_h[1];/*(temperature << 8) | tm_sensor->sensor_num*/
	} else if (TSENSOR_WRITE_THERMAL_L == cmd) {
		tx_buffer[0] = tm_sensor->write_thermal_l[0];/*g_tmdev->write_thermal_l_flag*/
		tx_buffer[1] = tm_sensor->write_thermal_l[1];/*(temperature << 8) | tm_sensor->sensor_num*/
	} else if (TSENSOR_READ_TEMPERATURE == cmd) {
		tx_buffer[0] = tm_sensor->read_temperature[0];/*g_tmdev->read_temperature_flag*/
		tx_buffer[1] = tm_sensor->read_temperature[1];/*tm_sensor->sensor_num(char)---> lpm3 tid*/
	} else {
		pr_err("tsensor send msg to lpm3 err!\n\r");
	}

	if (1 == g_tsensor_debug) {
		for (i = 0; i < TSENS_TO_LPM3_MSG_NUM; i++)
			pr_info("%s: send[%d] = 0x%x to lpm3\n", __func__, i, tx_buffer[i]);
	}

	rc = RPROC_SYNC_SEND(TSENSOR_RPROC_SEND_ID,
			tx_buffer,
			TSENS_TO_LPM3_MSG_NUM,
			ack_buffer,
			TSENS_RED_BACK_MSG_NUM);
	if (0 == rc) {
		if (1 == g_tsensor_debug) {
			for (i = 0; i < TSENS_RED_BACK_MSG_NUM; i++)
				pr_info("%s: read back msg[%d] = 0x%x\n", __func__, i, ack_buffer[i]);
		}

		if (ack_buffer[0] == g_tmdev->read_temperature_flag ||/*在LPM3 封装在IPC模块  ack_buffer[0] =tx_buffer[0] 在IPC模块中*/
			ack_buffer[0] == g_tmdev->read_thermal_h_flag ||
			ack_buffer[0] == g_tmdev->read_thermal_l_flag) {
			temperature = tsens_tz_code_to_degc((tsen_ipcdata->getting).temp);
			id = (tsen_ipcdata->getting).channel;
			if (1 == g_tsensor_debug)
				pr_info("%s:Tsensor_ID[%d],Tsensor_temperature[%d]\n", __func__, id, temperature);
			return temperature;
		} else {
			/*BYPASS*/}
	} else {
		pr_err("%s: tsens send msg to lpm3 fail!\n", __func__);
		return -EINVAL;
	}

	return 0;
}

static int hisi_tsens_mbox_notifier(struct notifier_block *nb, unsigned long len, void *msg)
{
	u32 *result = (u32 *)msg;
	int sensor_id, temp, interrupt_flag;

	if (result[0] == g_tmdev->int_reback_flag) {
		U_TSENSOR_IPC *tsen_ipcdata = (U_TSENSOR_IPC *)(&result[1]);
		sensor_id = (tsen_ipcdata->notify).channel;
		temp = tsens_tz_code_to_degc((tsen_ipcdata->notify).temp);
		interrupt_flag = (tsen_ipcdata->notify).which_thershold;
		schedule_work(&g_tmdev->sensor[sensor_id].work);
		if (1 == g_tsensor_debug)
			pr_info("sensor[%d] trigger temp (%d degC) Level[%d]\n",
					sensor_id, temp, interrupt_flag);
	}

	mb();
	return 0;
}

static int tsens_tz_get_temp(struct thermal_zone_device *thermal,
			     unsigned long *temp)
{
	struct tsens_tm_device_sensor *tm_sensor = thermal->devdata;

	if (!tm_sensor || tm_sensor->mode != THERMAL_DEVICE_ENABLED || !temp)
		return -EINVAL;

	tm_sensor->read_temperature[0] = g_tmdev->read_temperature_flag;
	tm_sensor->read_temperature[1] = tm_sensor->sensor_num;
	*temp = (unsigned long)hisi_tsens_cmd_send(tm_sensor, TSENSOR_READ_TEMPERATURE);
	if ((long)*temp < TSENS_TEMP_START_VALUE) {
		pr_err("%s: tsens get temperature value fail,temp=[%ld]\n", __func__, *temp);
		return -EINVAL;
	}

	return 0;
}

/*add for IPA*/
int tsens_get_temp(u32 sensor, long *temp)
{
	int i = 0;
	struct thermal_zone_device *thermal;
	int ret = -EINVAL;
	unsigned long tmp = 0;

	for (i = 0; i < g_tmdev->tsens_num_sensor; i++) {
		if (sensor == g_tmdev->sensor[i].sensor_num) {
			thermal = g_tmdev->sensor[i].tz_dev;
			ret = tsens_tz_get_temp(thermal, &tmp);
			if ((long)tmp < 0)
				tmp = 0;
			*temp = (long)tmp * 1000;
		}
	}

	return ret;
}

int ipa_get_sensor_id(char *name)
{
	int ret = -ENODEV;
	u32 id = 0;
	u32 sensor_num = sizeof(hisi_tsensor_name)/sizeof(char *);

	pr_info("IPA sensor_num =%d\n", sensor_num);

	for (id = 0; id < sensor_num; id++) {
		pr_info("IPA: sensor_name=%s, hisi_tsensor_name[%d]=%s\n", name, id, hisi_tsensor_name[id]);

		if (!strcmp(name, hisi_tsensor_name[id])) {
			ret = id;
			pr_info("sensor_id=%d\n", ret);
			return ret;/*break;*/
		}
	}

	return ret;

}
EXPORT_SYMBOL_GPL(ipa_get_sensor_id);

int ipa_get_sensor_value(u32 sensor, long *val)
{
	int ret = -EINVAL;
	u32 id = 0;
	u32 sensor_num = sizeof(hisi_tsensor_name)/sizeof(char *);
	if (!val) {
		pr_err("[%s]parm null\n", __func__);
		return ret;
	}

	if (sensor < sensor_num)
		ret = tsens_get_temp(sensor, val);
	else
		pr_err("tsensor id=%d is not supported!\n", id);

	return ret;
}
EXPORT_SYMBOL_GPL(ipa_get_sensor_value);

static int tsens_tz_get_mode(struct thermal_zone_device *thermal,
			      enum thermal_device_mode *mode)
{
	struct tsens_tm_device_sensor *tm_sensor = thermal->devdata;

	if (!tm_sensor || !mode)
		return -EINVAL;

	*mode = tm_sensor->mode;

	return 0;
}

static int tsens_tz_get_trip_type(struct thermal_zone_device *thermal,
				   int trip, enum thermal_trip_type *type)
{
	struct tsens_tm_device_sensor *tm_sensor = thermal->devdata;
	if (!tm_sensor || trip < 0 || !type)
		return -EINVAL;
	switch (trip) {
	case TSENS_TRIP_WARM:
		*type = THERMAL_TRIP_CONFIGURABLE_HI;
		break;
	case TSENS_TRIP_COOL:
		*type = THERMAL_TRIP_CONFIGURABLE_LOW;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
#ifdef THERMAL_SOC_USER_CONTRL
static int tsens_tz_activate_trip_type(struct thermal_zone_device *thermal,
			int trip, enum thermal_trip_activation_mode mode)
{
	struct tsens_tm_device_sensor *tm_sensor = thermal->devdata;
	int ret;

	if (!tm_sensor || trip < 0)
		return -EINVAL;

	switch (trip) {
	case TSENS_TRIP_WARM:
		if (mode == THERMAL_TRIP_ACTIVATION_DISABLED) {
			tm_sensor->disable[0] = g_tmdev->tsensor_disable_flag;
			tm_sensor->disable[1] = (0x01 << TSENSOR_8BIT) | tm_sensor->sensor_num;
			ret = hisi_tsens_cmd_send(tm_sensor, TSENSOR_DISABLE);
			if (ret) {
				pr_err("%s: tsens send disable cmd fail\n", __func__);
				return -EINVAL;
			}
		} else {
			tm_sensor->enable[0] = g_tmdev->tsensor_enable_flag;
			tm_sensor->enable[1] = (0x01 << TSENSOR_8BIT) | tm_sensor->sensor_num;
			ret = hisi_tsens_cmd_send(tm_sensor, TSENSOR_ENABLE);
			if (ret) {
				pr_err("%s: tsens send eanble cmd fail\n", __func__);
				return -EINVAL;
			}
		}

		break;
	case TSENS_TRIP_COOL:
		if (mode == THERMAL_TRIP_ACTIVATION_DISABLED) {
			tm_sensor->disable[0] = g_tmdev->tsensor_disable_flag;
			tm_sensor->disable[1] = (0x00 << TSENSOR_8BIT) | tm_sensor->sensor_num;
			ret = hisi_tsens_cmd_send(tm_sensor, TSENSOR_DISABLE);
			if (ret) {
				pr_err("%s: tsens send disable cmd fail\n", __func__);
				return -EINVAL;
			}
		} else {
			tm_sensor->enable[0] = g_tmdev->tsensor_enable_flag;
			tm_sensor->enable[1] = (0x00 << TSENSOR_8BIT) | tm_sensor->sensor_num;
			ret = hisi_tsens_cmd_send(tm_sensor, TSENSOR_ENABLE);
			if (ret) {
				pr_err("%s: tsens send eanble cmd fail\n", __func__);
				return -EINVAL;
			}
		}

		break;
	}

	mb();
	return 0;
}

static int tsens_tz_get_trip_temp(struct thermal_zone_device *thermal,
				   int trip, unsigned long *temp)
{
	struct tsens_tm_device_sensor *tm_sensor = thermal->devdata;

	if (!tm_sensor || trip < 0 || !temp)
		return -EINVAL;

	switch (trip) {
	case TSENS_TRIP_WARM:
		tm_sensor->read_thermal_h[0] = g_tmdev->read_thermal_h_flag;
		tm_sensor->read_thermal_h[1] = tm_sensor->sensor_num;
		*temp = (unsigned long)hisi_tsens_cmd_send(tm_sensor, TSENSOR_READ_THERMAL_H);
		if ((long)*temp < TSENS_TEMP_START_VALUE) {
			pr_err("%s: tsens get high thermal value fail, temperature=%ld\n", __func__, *temp);
			return -EINVAL;
		}
		break;
	case TSENS_TRIP_COOL:
		tm_sensor->read_thermal_l[0] = g_tmdev->read_thermal_l_flag;
		tm_sensor->read_thermal_l[1] = tm_sensor->sensor_num;
		*temp = (unsigned long)hisi_tsens_cmd_send(tm_sensor, TSENSOR_READ_THERMAL_L);
		if ((long)*temp < TSENS_TEMP_START_VALUE) {
			pr_err("%s: tsens get low thermal value fail, temperature=%ld\n", __func__, *temp);
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int tsens_tz_set_trip_temp(struct thermal_zone_device *thermal,
				   int trip, unsigned long temp)
{
	U_TSENSOR_IPC *tsen_ipcdata = NULL;
	struct tsens_tm_device_sensor *tm_sensor = thermal->devdata;
	int ret;
	int temperature;

	if (!tm_sensor || trip < 0 || (long)temp < TSENS_TEMP_START_VALUE || (long)temp > TSENS_TEMP_END_VALUE)
		return -EINVAL;

	temperature = tsens_tz_degc_to_code(temp);

	switch (trip) {
	case TSENS_TRIP_WARM:
		tsen_ipcdata = (U_TSENSOR_IPC *)(&tm_sensor->write_thermal_h[1]);
		tm_sensor->write_thermal_h[0] = g_tmdev->write_thermal_h_flag;
		(tsen_ipcdata->setting).channel = tm_sensor->sensor_num;
		(tsen_ipcdata->setting).temp = temperature;
		ret = hisi_tsens_cmd_send(tm_sensor, TSENSOR_WRITE_THERMAL_H);
		if (ret) {
			pr_err("%s: hisi tsens write high thermal fail\n", __func__);
			return -EINVAL;
		}
		break;
	case TSENS_TRIP_COOL:
		tsen_ipcdata = (U_TSENSOR_IPC *)(&tm_sensor->write_thermal_l[1]);
		tm_sensor->write_thermal_l[0] = g_tmdev->write_thermal_l_flag;
		(tsen_ipcdata->setting).channel = tm_sensor->sensor_num;
		(tsen_ipcdata->setting).temp = temperature;
		ret = hisi_tsens_cmd_send(tm_sensor, TSENSOR_WRITE_THERMAL_L);
		if (ret) {
			pr_err("%s: hisi tsens write low thermal fail\n", __func__);
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	mb();
	return 0;
}

static int tsens_tz_notify(struct thermal_zone_device *thermal,
				int count, enum thermal_trip_type type)
{
	/* TSENS driver does not shutdown the device.
	   All Thermal notification are sent to the
	   thermal daemon to take appropriate action */
	pr_debug("%s debug\n", __func__);
	return 0;
}
#endif
static struct thermal_zone_device_ops tsens_thermal_zone_ops = {
	.get_temp = tsens_tz_get_temp,
	.get_mode = tsens_tz_get_mode,
	.get_trip_type = tsens_tz_get_trip_type,
#ifdef THERMAL_SOC_USER_CONTRL
	.activate_trip_type = tsens_tz_activate_trip_type,
	.get_trip_temp = tsens_tz_get_trip_temp,
	.set_trip_temp = tsens_tz_set_trip_temp,
	.notify = tsens_tz_notify,
#endif
};

static void notify_uspace_tsens_fn(struct work_struct *work)
{
	struct tsens_tm_device_sensor *tm = container_of(work,
		struct tsens_tm_device_sensor, work);
	sysfs_notify(&tm->tz_dev->device.kobj,
					NULL, "type");
}

static int get_device_tree_data(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct device_node *of_node = pdev->dev.of_node;
	unsigned int register_info = 0;
	u32 rc = 0, tsens_num_sensors = 0;

	/* parse .hisi tsensor number */
	rc = of_property_read_u32(of_node, "hisi,sensors", &tsens_num_sensors);
	if (rc) {
		dev_err(&pdev->dev, "missing sensor number\n");
		return -ENODEV;
	}

	g_tmdev = devm_kzalloc(&pdev->dev, sizeof(struct tsens_tm_device) +
			tsens_num_sensors * sizeof(struct tsens_tm_device_sensor), GFP_KERNEL);
	if (g_tmdev == NULL) {
		dev_err(&pdev->dev, "kzalloc() failed.\n");
		return -ENOMEM;
	}

	g_tmdev->tsens_num_sensor = tsens_num_sensors;
	/* parse .hisi tsensor enable cmd */
	rc = of_property_read_u32(of_node, "hisi,tsensor_enable_cmd", &register_info);
	if (rc) {
		dev_err(dev, "no hisi,tsensor_enable_cmd cmd!\n");
		goto dt_parse_common_end;
	}
	g_tmdev->tsensor_enable_flag = register_info;
	/* parse .hisi tsensor disable cmd */
	rc = of_property_read_u32(of_node, "hisi,tsensor_disable_cmd", &register_info);
	if (rc) {
		dev_err(dev, "no hisi,tsensor_disable_cmd cmd!\n");
		goto dt_parse_common_end;
	}
	g_tmdev->tsensor_disable_flag = register_info;
	/* parse .hisi tsensor read high thermal cmd */
	rc = of_property_read_u32(of_node, "hisi,tsensor_read_thermal_h_cmd", &register_info);
	if (rc) {
		dev_err(dev, "no hisi,tsensor read high thermal cmd!\n");
		goto dt_parse_common_end;
	}
	g_tmdev->read_thermal_h_flag = register_info;
	/* parse .hisi tsensor read low thermal cmd */
	rc = of_property_read_u32(of_node, "hisi,tsensor_read_thermal_l_cmd", &register_info);
	if (rc) {
		dev_err(dev, "no hisi,tsensor read low thermal cmd!\n");
		goto dt_parse_common_end;
	}
	g_tmdev->read_thermal_l_flag = register_info;
	/* parse .hisi tsensor write high thermal cmd */
	rc = of_property_read_u32(of_node, "hisi,tsensor_write_thermal_h_cmd", &register_info);
	if (rc) {
		dev_err(dev, "no hisi,tsensor write high thermal cmd!\n");
		goto dt_parse_common_end;
	}
	g_tmdev->write_thermal_h_flag = register_info;
	/* parse .hisi tsensor write low thermal cmd */
	rc = of_property_read_u32(of_node, "hisi,tsensor_write_thermal_l_cmd", &register_info);
	if (rc) {
		dev_err(dev, "no hisi,tsensor write low thermal cmd!\n");
		goto dt_parse_common_end;
	}
	g_tmdev->write_thermal_l_flag = register_info;
	/* parse .hisi tsensor read temperature cmd */
	rc = of_property_read_u32(of_node, "hisi,tsensor_read_temperature_cmd", &register_info);
	if (rc) {
		dev_err(dev, "no hisi,tsensor read temperature cmd!\n");
		goto dt_parse_common_end;
	}
	g_tmdev->read_temperature_flag = register_info;
	/* parse .hisi tsensor INT reback cmd */
	rc = of_property_read_u32(of_node, "hisi,tsensor_int_reback_cmd", &register_info);
	if (rc) {
		dev_err(dev, "no hisi,tsensor int reback cmd!\n");
		goto dt_parse_common_end;
	}
	g_tmdev->int_reback_flag = register_info;

	return 0;
dt_parse_common_end:
	return -EINVAL;
}

static int  tsens_tm_probe(struct platform_device *pdev)
{
	int rc = 0;

	if (g_tmdev) {
		dev_err(&pdev->dev, "TSENS device already in use\n");
		return -EBUSY;
	}

	if (pdev->dev.of_node) {
		rc = get_device_tree_data(pdev);
		if (rc) {
			dev_err(&pdev->dev, "Error reading TSENS DT\n");
			return rc;
		}
	} else
		return -ENODEV;
	g_tmdev->pdev = pdev;

	platform_set_drvdata(pdev, g_tmdev);

	return 0;
}

static int  _tsens_register_thermal(void)
{
	struct platform_device *pdev;
	int rc = 0, i, j, k;
	char name[18];

	if (!g_tmdev) {
		pr_err("TSENS early init not done!\n");
		return -ENODEV;
	}

	pdev = g_tmdev->pdev;

	for (i = 0, j = 0; i < g_tmdev->tsens_num_sensor; i++, j++) {
		int k = 0, mask = 0;
		memset((void *)name, 0, sizeof(name));
		snprintf(name, sizeof(name), hisi_tsensor_name[i]);
		g_tmdev->sensor[i].mode = THERMAL_DEVICE_ENABLED;
		g_tmdev->sensor[i].sensor_num = i;

		for (k = 0; k < TSENS_TRIP_NUM; k++)
			mask |= 1 << k;

		g_tmdev->sensor[i].tz_dev = thermal_zone_device_register(name,
				TSENS_TRIP_NUM, mask, &g_tmdev->sensor[i],
				&tsens_thermal_zone_ops, NULL, 0, 0);
		if (IS_ERR(g_tmdev->sensor[i].tz_dev)) {
			dev_err(&pdev->dev, "Tsensor thermal_zone_device_register() failed\n");
			rc = -ENODEV;
			goto register_fail;
		}
	}

	platform_set_drvdata(pdev, g_tmdev);
	/*register tm sensor notify userspace work.*/
	for (k = 0; k < g_tmdev->tsens_num_sensor; k++)
		INIT_WORK(&g_tmdev->sensor[k].work, notify_uspace_tsens_fn);

	g_tmdev->nb = kmalloc(sizeof(struct notifier_block), GFP_KERNEL);
	if (!g_tmdev->nb) {
		dev_err(&pdev->dev, "failed to get mbox notifier block !\n");
		goto mailbox_nb_malloc_fail;
	}
	g_tmdev->nb->next = NULL;
	g_tmdev->nb->notifier_call = hisi_tsens_mbox_notifier;
	rc = RPROC_MONITOR_REGISTER(TSENSOR_RPROC_RECV_ID, g_tmdev->nb);
	if (rc) {
		dev_err(&pdev->dev, "rproc monitor register Failed!\n");
		goto mailbox_get_nb_fail;
	}

	return 0;

mailbox_get_nb_fail:
	kfree(g_tmdev->nb);
mailbox_nb_malloc_fail:
register_fail:
	for (i = 0; i < j; i++)
		thermal_zone_device_unregister(g_tmdev->sensor[i].tz_dev);
	return rc;
}

static int  tsens_tm_remove(struct platform_device *pdev)
{
	int i;
	struct tsens_tm_device *tmdev = platform_get_drvdata(pdev);
	if (tmdev == NULL)
		return -1;

	kfree(tmdev->nb);
	for (i = 0; i < tmdev->tsens_num_sensor; i++)
		thermal_zone_device_unregister(tmdev->sensor[i].tz_dev);

	platform_set_drvdata(pdev, NULL);

	return 0;
}

static struct of_device_id tsens_match[] = {
	{.compatible = "hisi,tsens",
	},
	{}
};

static struct platform_driver tsens_tm_driver = {
	.probe = tsens_tm_probe,
	.remove = tsens_tm_remove,
	.driver = {
		.name = "hisi-tsens",
		.owner = THIS_MODULE,
		.of_match_table = tsens_match,
	},
};

static int __init tsens_tm_init_driver(void)
{
	return platform_driver_register(&tsens_tm_driver);
}
arch_initcall(tsens_tm_init_driver);

static int __init tsens_thermal_register(void)
{
	return _tsens_register_thermal();
}
module_init(tsens_thermal_register);

static void __exit _tsens_tm_remove(void)
{
	platform_driver_unregister(&tsens_tm_driver);
}
module_exit(_tsens_tm_remove);

MODULE_ALIAS("platform:" TSENS_DRIVER_NAME);
MODULE_LICENSE("GPL v2");
