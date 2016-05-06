/*
 * copyright (C) 2014 HUAWEI, Inc.
 * Author: tuhaibo <tuhaibo@huawei.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "hall_sensor.h"

#ifdef HWLOG_TAG
#undef HWLOG_TAG
#endif
#define HWLOG_TAG hall
HWLOG_REGIST();

static struct class *hall_class;

static ssize_t hall_info_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	char info[256] = {0};
	struct hall_cdev *cdev = dev_get_drvdata(dev);

	cdev->hall_get_info(cdev, info);

	return snprintf(buf, PAGE_SIZE, "%s\n", info);
}

static ssize_t hall_count_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	return snprintf(buf, 50, "%d\n", cdev->hall_count);
}

static ssize_t hall_report_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned long state = 0L;
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	packet_data pdata = 0;

	if (!strict_strtol(buf, 10, &state)) {
		pdata = (packet_data)state;
		cdev->hall_report_debug_data(cdev, pdata);
	}

	return size;
}

static ssize_t hall_now_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	packet_data value = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	value = cdev->hall_get_state(cdev);
	return snprintf(buf, 50, "%d\n", value);
}

static ssize_t hall_now_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	cdev->hall_report_state(cdev);
	return size;
}

#ifdef HALL_TEST
//***********************************************/
static ssize_t hall_value_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	packet_data value = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	value = cdev->value;
	return snprintf(buf, 50, "%d\n", value);
}

static ssize_t hall_value_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned long state = 0L;
	int value;
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	if (!strict_strtol(buf, 10, &state)) {
		value = (packet_data)state;
		cdev->value = value;
		cdev->hall_set_report_value(cdev);
	}else
		hwlog_err("[%s] err.\n", __FUNCTION__);

	return size;
}

static ssize_t hall_report_count_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int report_count = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	report_count = cdev->count;
	return snprintf(buf, 50, "%d\n", report_count);
}

static ssize_t hall_report_count_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned long state = 0L;
	int count = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);

	if (!strict_strtol(buf, 10, &state)) {
		count = (int)state;
		if (count < HALL_REPORT_MIN_COUNT) {
			count = HALL_REPORT_MIN_COUNT;
		} else if(count > HALL_REPORT_MAX_COUNT) {
			count = HALL_REPORT_MAX_COUNT;
		}
		cdev->count = count;
	} else
		hwlog_err("[%s] err.\n", __FUNCTION__);

	return size;
}
static ssize_t hall_flag_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int flag = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	flag = cdev->flag;
	return snprintf(buf, 50, "%d\n", flag);
}

static ssize_t hall_flag_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned long state = 0L;
	int flag = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);

	if (!strict_strtol(buf, 10, &state)) {
		flag = state&0xFFFFFFFF;
		cdev->flag = flag;
	} else
		hwlog_err("[%s] err.\n", __FUNCTION__);

	return size;
}

static ssize_t hall_period_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int period = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	period = cdev->period;
	return snprintf(buf, 50, "%d\n", period);
}

static ssize_t hall_period_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned long state = 0L;
	int period = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);

	if (!strict_strtol(buf, 10, &state)) {
		period = (int)state;
		if (period < HALL_REPORT_MIN_PERIOD) {
			period = HALL_REPORT_MIN_PERIOD;
		} else if (period > HALL_REPORT_MAX_PERIOD) {
			period = HALL_REPORT_MAX_PERIOD;
		}
		cdev->period = period;
	} else
		hwlog_err("[%s] err.\n", __FUNCTION__);

	return size;
}

static ssize_t hall_enable_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int enable = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);
	enable = cdev->enable;
	return snprintf(buf, 50, "%d\n", enable);
}

static ssize_t hall_enable_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned long state = 0L;
	int enable = 0;
	struct hall_cdev *cdev = dev_get_drvdata(dev);

	if (!strict_strtol(buf, 10, &state)) {
		enable = !!state;
		cdev->enable = enable;
	} else
		hwlog_err("[%s] err.\n", __FUNCTION__);

	return size;
}
//***********************************************/
#endif

static struct device_attribute hall_class_attrs[] = {
	__ATTR(info, 0440, hall_info_show, NULL),
	__ATTR(count, 0440, hall_count_show, NULL),
	__ATTR(report, 0220, NULL, hall_report_store),
	__ATTR(state, 0660, hall_now_show, hall_now_store),
#ifdef HALL_TEST
	__ATTR(value, 0660, hall_value_show, hall_value_store),
	__ATTR(report_count, 0660, hall_report_count_show, hall_report_count_store),
	__ATTR(flag, 0660, hall_flag_show, hall_flag_store),
	__ATTR(period, 0660, hall_period_show, hall_period_store),
	__ATTR(enable, 0660, hall_enable_show, hall_enable_store),
#endif
	__ATTR_NULL,
};

int hall_register(struct hall_cdev *cdev)
{
	cdev->dev = device_create(hall_class, NULL, 0, cdev, "hall");
	if (NULL == cdev->dev) {
		hwlog_err("[%s] Failed to create hall dev.", __FUNCTION__);
		return -1;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(hall_register);

void hall_unregister(struct hall_cdev *cdev)
{
	device_destroy(hall_class, 0);
}
EXPORT_SYMBOL_GPL(hall_unregister);

static int  hall_init(void)
{
	hall_class = class_create(THIS_MODULE, "hall");
	if (IS_ERR(hall_class)) {
		return PTR_ERR(hall_class);
	}

	hall_class->dev_attrs = hall_class_attrs;

	hwlog_info("[%s]hall init\n", __FUNCTION__);
	return 0;
}

static void  hall_exit(void)
{
	class_destroy(hall_class);
}

subsys_initcall(hall_init);
module_exit(hall_exit);

MODULE_AUTHOR("Huawei");
MODULE_DESCRIPTION("Hall class init");
MODULE_LICENSE("GPL");
