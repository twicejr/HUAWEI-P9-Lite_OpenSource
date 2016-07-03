/*
 * Copyright (C) 2012 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/devfreq.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/pm_qos.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>

#include "../../../../../../drivers/devfreq/governor.h"
#include "../../../../../../drivers/atfdriver/atfdriver.h"

#define DFPQ_BDUTILIZATION		(60)
#define DFPQ_MAX_BDUTILIZATION		(100)
#define DFPQ_MIN_BDUTILIZATION		(1)

#define SOC_DMSS_GLB_ADDR_INTLV_ADDR(base)            ((base) + (0x6100))
#define SOC_ACPU_DMSS_BASE_ADDR                       (0xFFFC0000)

struct devfreq_pm_qos_notifier_block {
	struct list_head node;
	struct notifier_block nb;
	struct devfreq *df;
};

static ssize_t
show_bd_utilization(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct devfreq *devfreq = to_devfreq(dev);
	struct devfreq_pm_qos_data *data;
	int ret = 0;

	mutex_lock(&devfreq->lock);
	data = devfreq->data;
	ret = sprintf(buf, "%u\n", data->bd_utilization);
	mutex_unlock(&devfreq->lock);

	return ret;
}

static ssize_t
store_bd_utilization(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct devfreq *devfreq = to_devfreq(dev);
	struct devfreq_pm_qos_data *data;
	unsigned int input;
	int ret = 0;

	ret = sscanf(buf, "%u", &input);
	if ((ret != 1) || (input > DFPQ_MAX_BDUTILIZATION) ||
		(input < DFPQ_MIN_BDUTILIZATION))
		return -EINVAL;

	mutex_lock(&devfreq->lock);
	data = devfreq->data;
	data->bd_utilization = input;

	ret = update_devfreq(devfreq);
	if (ret == 0)
		ret = count;
	mutex_unlock(&devfreq->lock);

	return ret;
}

static ssize_t
show_ddr_bandwidth(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct devfreq *devfreq = to_devfreq(dev);
	struct devfreq_pm_qos_data *data;
	unsigned long freq;
	unsigned long bw;
	int ret = 0;

	mutex_lock(&devfreq->lock);
	data = devfreq->data;
	if (!devfreq->profile->get_cur_freq) {
		freq = devfreq->previous_freq;
	} else {
		if ((ret = devfreq->profile->get_cur_freq(devfreq->dev.parent,
								&freq))) {
			pr_err("%s %d, failed to get cur freq\n",
						__func__, __LINE__);
			mutex_unlock(&devfreq->lock);
			return ret;
		}
	}

	freq = freq / 1000 / 1000;
	bw = freq * data->bd_utilization * data->bytes_per_sec_per_hz / 100;
	mutex_unlock(&devfreq->lock);

	ret = sprintf(buf, "%lu\n", bw);
	return ret;
}

/*Austin SOC_DMSS_GLB_ADDR_INTLV_ADDR
intlv_granule	[6:4]
"0x0: 128Byte;
 0x1: 256Byte;
 0x2: 512Byte;
 0x3: 1KByte;
 0x4: 2KByte;
 0x5: 4KByte;*/
static ssize_t
show_ddr_chintlv(struct device *dev, struct device_attribute *attr, char *buf)
{
	int ret = 0;
#ifdef CONFIG_HISI_DDR_CHINTLV
	struct devfreq *devfreq = to_devfreq(dev);
	unsigned long chintlv = 0;
	unsigned long reg_val = 0;

	mutex_lock(&devfreq->lock);

	reg_val = atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID,SOC_DMSS_GLB_ADDR_INTLV_ADDR(SOC_ACPU_DMSS_BASE_ADDR), 0x4,ACCESS_REGISTER_FN_SUB_ID_DDR_INTLV);
	chintlv = 1 << ((reg_val >> 4) & 0x7);
	chintlv *= 128;

	/*pr_err("%s %d, chintlv %d\n", __func__, __LINE__,chintlv);*/

	mutex_unlock(&devfreq->lock);

	ret = sprintf(buf, "%lu\n", chintlv);
#endif
	return ret;
}

/*lint -e665 */
static DEVICE_ATTR(bd_utilization, (S_IRUGO | S_IWUSR),
			show_bd_utilization, store_bd_utilization);
static DEVICE_ATTR(ddr_bandwidth, S_IRUGO, show_ddr_bandwidth, NULL);

static DEVICE_ATTR(ddr_chintlv, S_IRUGO, show_ddr_chintlv, NULL);

static const struct attribute *governor_pm_qos_attrs[] = {
	&dev_attr_bd_utilization.attr,
	&dev_attr_ddr_bandwidth.attr,
	&dev_attr_ddr_chintlv.attr,
	NULL,
};
/*lint +e665 */

static LIST_HEAD(devfreq_pm_qos_list);
static DEFINE_MUTEX(devfreq_pm_qos_mutex);

static int devfreq_pm_qos_func(struct devfreq *df, unsigned long *freq)
{
	struct devfreq_pm_qos_data *data = df->data;
	unsigned long megabytes_per_sec;
	unsigned long mhz;
	unsigned long ul_max = (ULONG_MAX / 1000 / 1000 / \
			100 * data->bytes_per_sec_per_hz * data->bd_utilization);

	megabytes_per_sec = pm_qos_request(data->pm_qos_class);
	if ((megabytes_per_sec > 0) && (megabytes_per_sec < ul_max)) {
		megabytes_per_sec = megabytes_per_sec * 100;
		megabytes_per_sec = \
			DIV_ROUND_UP(megabytes_per_sec, data->bd_utilization);
		mhz = DIV_ROUND_UP(megabytes_per_sec, data->bytes_per_sec_per_hz);
		*freq = mhz * 1000 * 1000;
	} else if (megabytes_per_sec >= ul_max) {
		*freq = ULONG_MAX;
	} else {
		*freq = 0;
	}

	if (df->min_freq && *freq < df->min_freq)
		*freq = df->min_freq;
	if (df->max_freq && *freq > df->max_freq)
		*freq = df->max_freq;

	return 0;
}

static int
devfreq_pm_qos_notifier(struct notifier_block *nb, unsigned long val, void *v)
{
	struct devfreq_pm_qos_notifier_block *pq_nb;

	pq_nb = container_of(nb, struct devfreq_pm_qos_notifier_block, nb);
	mutex_lock(&pq_nb->df->lock);
	(void)update_devfreq(pq_nb->df);
	mutex_unlock(&pq_nb->df->lock);

	return NOTIFY_OK;
}

static int devfreq_pm_qos_gov_init(struct devfreq *df)
{
	int ret;
	struct devfreq_pm_qos_notifier_block *pq_nb;
	struct devfreq_pm_qos_data *data = df->data;

	if (!data) {
		pr_err("%s %d, invalid pointer\n", __func__, __LINE__);
		return -EINVAL;
	}

	if (!data->bytes_per_sec_per_hz) {
		pr_err("%s %d, invalid parameter\n", __func__, __LINE__);
		return -EINVAL;
	}

	pq_nb = kzalloc(sizeof(*pq_nb), GFP_KERNEL);
	if (!pq_nb) {
		pr_err("%s %d, no mem\n", __func__, __LINE__);
		return -ENOMEM;
	}

	pq_nb->df = df;
	pq_nb->nb.notifier_call = devfreq_pm_qos_notifier;
	INIT_LIST_HEAD(&pq_nb->node);

	ret = pm_qos_add_notifier(data->pm_qos_class, &pq_nb->nb);
	if (ret < 0) {
		pr_err("%s %d, Failed to add pm qos notifier\n",
						__func__, __LINE__);
		kfree(pq_nb);
		return ret;
	}

	data->bd_utilization = DFPQ_BDUTILIZATION;
	ret = sysfs_create_files(&df->dev.kobj, governor_pm_qos_attrs);
	if (ret) {
		pr_err("%s: failed to create sysfs file\n", __func__);
		pm_qos_remove_notifier(data->pm_qos_class, &pq_nb->nb);
		kfree(pq_nb);
		return ret;
	}

	mutex_lock(&devfreq_pm_qos_mutex);
	list_add_tail(&pq_nb->node, &devfreq_pm_qos_list);
	mutex_unlock(&devfreq_pm_qos_mutex);

	return 0;
}

static void devfreq_pm_qos_gov_exit(struct devfreq *df)
{
	struct devfreq_pm_qos_notifier_block *pq_nb;
	struct devfreq_pm_qos_data *data;

	mutex_lock(&devfreq_pm_qos_mutex);

	list_for_each_entry(pq_nb, &devfreq_pm_qos_list, node) {
		if (pq_nb->df == df) {
			data = pq_nb->df->data;
			pm_qos_remove_notifier(data->pm_qos_class, &pq_nb->nb);
			goto out;
		}
	}

out:
	mutex_unlock(&devfreq_pm_qos_mutex);
	kfree(pq_nb);
}

static int devfreq_pm_qos_handler(struct devfreq *devfreq,
				unsigned int event, void *data)
{
	int ret = 0;

	switch (event) {
	case DEVFREQ_GOV_START:
		ret = devfreq_pm_qos_gov_init(devfreq);
		break;
	case DEVFREQ_GOV_STOP:
		devfreq_pm_qos_gov_exit(devfreq);
		break;
	default:
		break;
	}

	return ret;
}

struct devfreq_governor devfreq_pm_qos = {
	.name = "pm_qos",
	.get_target_freq = devfreq_pm_qos_func,
	.event_handler = devfreq_pm_qos_handler,
};

static int __init devfreq_pm_qos_init(void)
{
	return devfreq_add_governor(&devfreq_pm_qos);
}
subsys_initcall(devfreq_pm_qos_init);

static void __exit devfreq_pm_qos_exit(void)
{
	int ret;

	ret = devfreq_remove_governor(&devfreq_pm_qos);
	if (ret)
		pr_err("%s: failed remove governor %d\n", __func__, ret);

	return;
}
module_exit(devfreq_pm_qos_exit);
MODULE_LICENSE("GPL");
