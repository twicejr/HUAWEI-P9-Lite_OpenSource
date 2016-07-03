/*
 *  linux/drivers/devfreq/governor_maliondemand.c
 *  Copyright (C) 2013 Hisilicon
 *
 * base on:
 *  linux/drivers/devfreq/governor_simpleondemand.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/errno.h>
#include <linux/module.h>
#include <linux/devfreq.h>
#include <linux/math64.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/pm.h>
#include <linux/mutex.h>
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
#include <linux/pm_qos.h>
#endif
#include "../../../../../../drivers/devfreq/governor.h"


/* Default constants for DevFreq-Mali-Ondemand (DFMO) */
#define DFMO_VSYNC_UPTHRESHOLD		(85)
#define DFMO_VSYNC_DOWNDIFFERENCTIAL	(15)
#define DFMO_NO_VSYNC_UPTHRESHOLD	(40)
#define DFMO_NO_VSYNC_DOWNDIFFERENCTIAL	(10)
#define DFMO_MAX_UPTHRESHOLD		(100)
#define DFMO_MIN_UPTHRESHOLD		(11)
#define DFMO_MAX_DOWNDIFFERENCTIAL	(30)
#define DFMO_MIN_DOWNDIFFERENCTIAL	(1)
#define DFMO_CONSANTS_DIGIT_MAX		(16)
#define DFMO_ANIMATION_BOOST_ON		(1)
#define DFMO_ANIMATION_BOOST_DN		(0)
#define DFMO_MIN_ANIMATION_BOOST_FREQ	(120000000)
#define DFMO_MAX_ANIMATION_BOOST_FREQ	(680000000)
#define DFMO_DEFAULT_ANIMATION_BOOST_FREQ	(480000000)
#define DFMO_MIN_HISPEED_FREQ		(120000000)
#define DFMO_MAX_HISPEED_FREQ		(680000000)
#define DFMO_DEFAULT_HISPEED_FREQ	(480000000)

#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
#define DFMO_MIN_FREQ_FOR_QOS_CPU_DMA_LATENCY		(120000000)
#define DFMO_MAX_FREQ_FOR_QOS_CPU_DMA_LATENCY		(680000000)
#define DFMO_DEFAULT_FREQ_FOR_QOS_CPU_DMA_LATENCY	(680000000)
#define DFMO_MIN_QOS_CPU_DMA_LATENCY_REQUEST_VALUE	(1)
#define DFMO_MAX_QOS_CPU_DMA_LATENCY_REQUEST_VALUE	(10000)
#define DFMO_DEFAULT_QOS_CPU_DMA_LATENCY_REQUEST_VALUE	(50)
#define DFMO_MIN_QOS_CPU_DMA_LATENCY_REQUEST_DELAY	(0)
#define DFMO_MAX_QOS_CPU_DMA_LATENCY_REQUEST_DELAY	(100)
#define DFMO_DEFAULT_QOS_CPU_DMA_LATENCY_REQUEST_DELAY	(40)
#define DFMO_QOS_CPU_DMA_LATENCY_REQUESTED		(1)
#define DFMO_QOS_CPU_DMA_LATENCY_RELEASED		(0)
#endif

struct devfreq_mali_ondemand_data {
	unsigned int vsync_upthreshold;
	unsigned int vsync_downdifferential;
	unsigned int no_vsync_upthreshold;
	unsigned int no_vsync_downdifferential;
	int vsync;
	int utilisation;
	int animation_boost;
	unsigned int animation_boost_freq;
	unsigned int hispeed_freq;
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
	struct pm_qos_request qos_cpu_dma_latency_request;
	unsigned int qos_cpu_dma_latency_request_freq;
	int qos_cpu_dma_latency_request_value;
	int qos_cpu_dma_latency_request_delay;
	int qos_cpu_dma_latency_request_delay_cnt;
	int qos_cpu_dma_latency_requested;
#endif
};

static int devfreq_mali_ondemand_func(struct devfreq *df,
					unsigned long *freq)
{
	struct devfreq_dev_status stat;
	int err = df->profile->get_dev_status(df->dev.parent, &stat);
	unsigned long long a, b;
	unsigned int dfso_upthreshold = DFMO_VSYNC_UPTHRESHOLD;
	unsigned int dfso_downdifferential = DFMO_VSYNC_DOWNDIFFERENCTIAL;
	struct devfreq_mali_ondemand_data *data = df->data;
	unsigned long max = (df->max_freq) ? df->max_freq : UINT_MAX;

	if (err)
		return err;

	if(data == NULL)
		return -EINVAL;

	if (data) {
		data->vsync = stat.private_data ? 1 : 0;
		data->utilisation = stat.busy_time * 100 / stat.total_time;

		if (data->vsync) {
			dfso_upthreshold = data->vsync_upthreshold;
			dfso_downdifferential = data->vsync_downdifferential;
		} else {
			dfso_upthreshold = data->no_vsync_upthreshold;
			dfso_downdifferential = data->no_vsync_downdifferential;
		}
	}
	if (dfso_upthreshold > 100 ||
	    dfso_upthreshold < dfso_downdifferential) {
		pr_err("%s: invalid performance parameter, upth[%d], diff[%d]\n",
			__func__, dfso_upthreshold, dfso_downdifferential);
		return -EINVAL;
	}

	/* Assume MAX if it is going to be divided by zero  &&
	   Set MAX if we do not know the initial frequency */
	if (unlikely(stat.total_time == 0 || stat.current_frequency == 0)) {
		*freq = max;
		return 0;
	}

	/* Prevent overflow */
	if (stat.busy_time >= (1 << 24) || stat.total_time >= (1 << 24)) {
		stat.busy_time >>= 7;
		stat.total_time >>= 7;
	}

	/* Set MAX if it's busy enough */
	if (stat.busy_time * 100 >
	    stat.total_time * dfso_upthreshold) {
		if (*freq < data->hispeed_freq) {
			*freq = data->hispeed_freq;
			goto check_barrier;
		}
	} else if (stat.busy_time * 100 >
	    stat.total_time * (dfso_upthreshold - dfso_downdifferential)) {
		/* Keep the current frequency */
		*freq = stat.current_frequency;
		goto check_barrier;
	}

	/* Set the desired frequency based on the load */
	a = stat.busy_time;
	a *= stat.current_frequency;
	b = div_u64(a, stat.total_time);
	b *= 100;
	b = div_u64(b, (dfso_upthreshold - dfso_downdifferential / 2));
	*freq = (unsigned long) b;

check_barrier:
	/* Not less than animation_boost_freq, if necessary. */
	if (data && data->animation_boost &&
		(*freq < data->animation_boost_freq))
		*freq = (unsigned long)data->animation_boost_freq;

	if (df->min_freq && *freq < df->min_freq)
		*freq = df->min_freq;
	if (df->max_freq && *freq > df->max_freq)
		*freq = df->max_freq;

#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
	if (data) {
		if (*freq >= data->qos_cpu_dma_latency_request_freq) {
			if (DFMO_QOS_CPU_DMA_LATENCY_RELEASED ==
				data->qos_cpu_dma_latency_requested) {
				if (data->qos_cpu_dma_latency_request_delay_cnt >=
					data->qos_cpu_dma_latency_request_delay) {
					pm_qos_update_request(
						&data->qos_cpu_dma_latency_request,
						data->qos_cpu_dma_latency_request_value);
					data->qos_cpu_dma_latency_requested =
						DFMO_QOS_CPU_DMA_LATENCY_REQUESTED;
					data->qos_cpu_dma_latency_request_delay_cnt = 0;
				} else {
					data->qos_cpu_dma_latency_request_delay_cnt++;
				}
			}
		} else {
			data->qos_cpu_dma_latency_request_delay_cnt = 0;

			if (DFMO_QOS_CPU_DMA_LATENCY_REQUESTED ==
				data->qos_cpu_dma_latency_requested) {
				pm_qos_update_request(
					&data->qos_cpu_dma_latency_request,
					PM_QOS_DEFAULT_VALUE);
				data->qos_cpu_dma_latency_requested =
					DFMO_QOS_CPU_DMA_LATENCY_RELEASED;
			}
		}
	}
#endif

	return 0;
}


#define store_one(object, min, max)						\
static ssize_t store_##object						\
(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)	\
{										\
	struct devfreq *devfreq = to_devfreq(dev);				\
	struct devfreq_mali_ondemand_data *data;				\
	unsigned int input;							\
	int ret = 0;								\
	ret = sscanf(buf, "%u", &input);					\
	if (ret != 1 || input > max || input < min)				\
		return -EINVAL;							\
	mutex_lock(&devfreq->lock);						\
	data = devfreq->data;							\
	data->object = input;							\
	ret = update_devfreq(devfreq);						\
	if (ret == 0)								\
		ret = count;							\
	mutex_unlock(&devfreq->lock);						\
	return ret;								\
}

store_one(vsync_upthreshold, DFMO_MIN_UPTHRESHOLD, DFMO_MAX_UPTHRESHOLD)
store_one(vsync_downdifferential, DFMO_MIN_DOWNDIFFERENCTIAL, DFMO_MAX_DOWNDIFFERENCTIAL)
store_one(no_vsync_upthreshold, DFMO_MIN_UPTHRESHOLD, DFMO_MAX_UPTHRESHOLD)
store_one(no_vsync_downdifferential, DFMO_MIN_DOWNDIFFERENCTIAL, DFMO_MAX_DOWNDIFFERENCTIAL)
store_one(animation_boost, DFMO_ANIMATION_BOOST_DN, DFMO_ANIMATION_BOOST_ON)
store_one(animation_boost_freq, DFMO_MIN_ANIMATION_BOOST_FREQ, DFMO_MAX_ANIMATION_BOOST_FREQ)
store_one(hispeed_freq, DFMO_MIN_HISPEED_FREQ, DFMO_MAX_HISPEED_FREQ)
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
store_one(qos_cpu_dma_latency_request_freq, DFMO_MIN_FREQ_FOR_QOS_CPU_DMA_LATENCY, DFMO_MAX_FREQ_FOR_QOS_CPU_DMA_LATENCY)
store_one(qos_cpu_dma_latency_request_value, DFMO_MIN_QOS_CPU_DMA_LATENCY_REQUEST_VALUE, DFMO_MAX_QOS_CPU_DMA_LATENCY_REQUEST_VALUE)
store_one(qos_cpu_dma_latency_request_delay, DFMO_MIN_QOS_CPU_DMA_LATENCY_REQUEST_DELAY, DFMO_MAX_QOS_CPU_DMA_LATENCY_REQUEST_DELAY)
#endif

#define show_one(object)					\
static ssize_t show_##object					\
(struct device *dev, struct device_attribute *attr, char *buf)	\
{								\
	struct devfreq *devfreq = to_devfreq(dev);		\
	struct devfreq_mali_ondemand_data *data;		\
	int ret = 0;						\
	mutex_lock(&devfreq->lock);				\
	data = devfreq->data;					\
	ret = snprintf(buf, DFMO_CONSANTS_DIGIT_MAX,		\
				"%u\n", (unsigned int)data->object);		\
	mutex_unlock(&devfreq->lock);				\
	return ret;						\
}

show_one(vsync_upthreshold)
show_one(vsync_downdifferential)
show_one(no_vsync_upthreshold)
show_one(no_vsync_downdifferential)
show_one(vsync)
show_one(utilisation)
show_one(animation_boost)
show_one(animation_boost_freq)
show_one(hispeed_freq)
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
show_one(qos_cpu_dma_latency_request_freq)
show_one(qos_cpu_dma_latency_request_value)
show_one(qos_cpu_dma_latency_request_delay)
#endif

#define MALI_ONDEMAND_ATTR_RW(_name) \
	static DEVICE_ATTR(_name, 0644, show_##_name, store_##_name)

MALI_ONDEMAND_ATTR_RW(vsync_upthreshold);
MALI_ONDEMAND_ATTR_RW(vsync_downdifferential);
MALI_ONDEMAND_ATTR_RW(no_vsync_upthreshold);
MALI_ONDEMAND_ATTR_RW(no_vsync_downdifferential);
MALI_ONDEMAND_ATTR_RW(animation_boost);
MALI_ONDEMAND_ATTR_RW(animation_boost_freq);
MALI_ONDEMAND_ATTR_RW(hispeed_freq);
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
MALI_ONDEMAND_ATTR_RW(qos_cpu_dma_latency_request_freq);
MALI_ONDEMAND_ATTR_RW(qos_cpu_dma_latency_request_value);
MALI_ONDEMAND_ATTR_RW(qos_cpu_dma_latency_request_delay);
#endif

#define MALI_ONDEMAND_ATTR_RO(_name) \
	static DEVICE_ATTR(_name, 0444, show_##_name, NULL)

MALI_ONDEMAND_ATTR_RO(vsync);
MALI_ONDEMAND_ATTR_RO(utilisation);


static struct attribute *dev_entries[] = {
	&dev_attr_vsync_upthreshold.attr,
	&dev_attr_vsync_downdifferential.attr,
	&dev_attr_no_vsync_upthreshold.attr,
	&dev_attr_no_vsync_downdifferential.attr,
	&dev_attr_vsync.attr,
	&dev_attr_utilisation.attr,
	&dev_attr_animation_boost.attr,
	&dev_attr_animation_boost_freq.attr,
	&dev_attr_hispeed_freq.attr,
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
	&dev_attr_qos_cpu_dma_latency_request_freq.attr,
	&dev_attr_qos_cpu_dma_latency_request_value.attr,
	&dev_attr_qos_cpu_dma_latency_request_delay.attr,
#endif
	NULL,
};


static struct attribute_group dev_attr_group = {
	.name	= "mali_ondemand",
	.attrs	= dev_entries,
};

static int mali_ondemand_init(struct devfreq *devfreq)
{
	int err = 0;
	struct devfreq_mali_ondemand_data *data;

	if (!devfreq->data) {
		data = kzalloc(sizeof(struct devfreq_mali_ondemand_data),
					      GFP_KERNEL);
		if (!data) {
			pr_err("%s: alloc err\n", __func__);
			err = -ENOMEM;
			goto out;
		}
		data->vsync_upthreshold = DFMO_VSYNC_UPTHRESHOLD;
		data->vsync_downdifferential = DFMO_VSYNC_DOWNDIFFERENCTIAL;
		data->no_vsync_upthreshold = DFMO_NO_VSYNC_UPTHRESHOLD;
		data->no_vsync_downdifferential = DFMO_NO_VSYNC_DOWNDIFFERENCTIAL;
		data->animation_boost = DFMO_ANIMATION_BOOST_DN;
		data->animation_boost_freq = DFMO_DEFAULT_ANIMATION_BOOST_FREQ;
		data->hispeed_freq = DFMO_DEFAULT_HISPEED_FREQ;
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
		pm_qos_add_request(&data->qos_cpu_dma_latency_request,
			PM_QOS_CPU_DMA_LATENCY, PM_QOS_DEFAULT_VALUE);
		data->qos_cpu_dma_latency_request_freq =
			DFMO_DEFAULT_FREQ_FOR_QOS_CPU_DMA_LATENCY;
		data->qos_cpu_dma_latency_request_value =
			DFMO_DEFAULT_QOS_CPU_DMA_LATENCY_REQUEST_VALUE;
		data->qos_cpu_dma_latency_request_delay =
			DFMO_DEFAULT_QOS_CPU_DMA_LATENCY_REQUEST_DELAY;
		data->qos_cpu_dma_latency_request_delay_cnt = 0;
		data->qos_cpu_dma_latency_requested =
			DFMO_QOS_CPU_DMA_LATENCY_RELEASED;
#endif
		devfreq->data = data;
	}

	err = sysfs_create_group(&devfreq->dev.kobj, &dev_attr_group);
	if (err) {
		pr_err("%s: sysfs create err %d\n", __func__, err);
	}
out:
	return err;
}

static void mali_ondemand_exit(struct devfreq *devfreq)
{
	struct devfreq_mali_ondemand_data *data;

	sysfs_remove_group(&devfreq->dev.kobj, &dev_attr_group);

	data = devfreq->data;
	if (!data)
		return;
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
	pm_qos_remove_request(&data->qos_cpu_dma_latency_request);
#endif
	kfree(data);
	devfreq->data = NULL;
}


static int devfreq_mali_ondemand_handler(struct devfreq *devfreq,
				unsigned int event, void *data)
{
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
	struct devfreq_mali_ondemand_data *priv;
#endif
	int ret = 0;

	switch (event) {
	case DEVFREQ_GOV_START:
		ret = mali_ondemand_init(devfreq);
		if (!ret)
			devfreq_monitor_start(devfreq);
		break;

	case DEVFREQ_GOV_STOP:
		devfreq_monitor_stop(devfreq);
		mali_ondemand_exit(devfreq);
		break;

	case DEVFREQ_GOV_INTERVAL:
		devfreq_interval_update(devfreq, (unsigned int *)data);
		break;

	case DEVFREQ_GOV_SUSPEND:
		devfreq_monitor_suspend(devfreq);
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
		priv = devfreq->data;
		if (priv && (DFMO_QOS_CPU_DMA_LATENCY_REQUESTED ==
			priv->qos_cpu_dma_latency_requested)) {
			pm_qos_update_request(
				&priv->qos_cpu_dma_latency_request,
				PM_QOS_DEFAULT_VALUE);
			priv->qos_cpu_dma_latency_requested =
				DFMO_QOS_CPU_DMA_LATENCY_RELEASED;
		}
#endif
		break;

	case DEVFREQ_GOV_RESUME:
#ifdef DFMO_REQUEST_QOS_CPU_DMA_LATENCY
		priv = devfreq->data;
		if (priv)
			priv->qos_cpu_dma_latency_request_delay_cnt = 0;
#endif
		devfreq_monitor_resume(devfreq);
		break;

	default:
		break;
	}

	return ret;
}

static struct devfreq_governor devfreq_mali_ondemand = {
	.name = "mali_ondemand",
	.get_target_freq = devfreq_mali_ondemand_func,
	.event_handler = devfreq_mali_ondemand_handler,
};

static int __init devfreq_mali_ondemand_init(void)
{
	return devfreq_add_governor(&devfreq_mali_ondemand);
}
subsys_initcall(devfreq_mali_ondemand_init);

static void __exit devfreq_mali_ondemand_exit(void)
{
	int ret;

	ret = devfreq_remove_governor(&devfreq_mali_ondemand);
	if (ret)
		pr_err("%s: failed remove governor %d\n", __func__, ret);

	return;
}
module_exit(devfreq_mali_ondemand_exit);
MODULE_LICENSE("GPL");
