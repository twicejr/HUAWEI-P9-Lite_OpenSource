/*
 * hisi_adc.c for the hkadc driver.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO.Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/notifier.h>
#include <linux/delay.h>
#include <linux/completion.h>
#include <linux/mutex.h>
#include <linux/debugfs.h>
#include <linux/hisi/hisi_mailbox.h>
#include <linux/hisi/hisi_mailbox_dev.h>
#include <linux/huawei/hisi_adc.h>
#include <linux/hisi/hisi_rproc.h>


#define	MODULE_NAME		"hisi_adc"
/*adc maybe IPC timeout*/
#define ADC_IPC_TIMEOUT		1500
#define	ADC_IPC_MAX_CNT		3

#define HISI_AP_ID		0x00
#define	ADC_OBJ_ID		0x0b
#define ADC_IPC_CMD_TYPE0	0x02
#define	ADC_IPC_CMD_TYPE1	0x0c
#define	ADC_IPC_DATA		((HISI_AP_ID << 24) | (ADC_OBJ_ID << 16) | (ADC_IPC_CMD_TYPE0 << 8) | ADC_IPC_CMD_TYPE1)

#define	ADC_DATA_BIT_R(d, n)	((d) >> (n))
#define	ADC_DATA_MASK		0xff
#define	ADC_RESULT_ERR		(-EINVAL)
#define	ADC_CHN_MAX		18

enum {
	ADC_IPC_CMD_TYPE = 0,
	ADC_IPC_CMD_CHANNEL,
	ADC_IPC_CMD_LEN
};

struct adc_info {
	int channel;
	int value;
};

struct hisi_adc_device {
	struct adc_info		info;
	mbox_msg_t		tx_msg[ADC_IPC_CMD_LEN];
	struct notifier_block	*nb;
	struct mutex		mutex;
	struct completion	completion;
};

static struct hisi_adc_device	*hisi_adc_dev = NULL;

#ifdef CONFIG_DEBUG_FS
/* creat a debugfs directory for adc debugging. */
static struct dentry		*debugfs_root;
static int buff[3];
#endif

#define HKADC_VREF  (1800)
#define HKADC_ACCURACY  (0xFFF)
#define ADC_RPROC_SEND_ID	HISI_RPROC_LPM3_MBX16
#define ADC_RPROC_RECV_ID	HISI_RPROC_LPM3_MBX0

int g_hkadc_debug = 0;
void hkadc_debug(int onoff)
{
	g_hkadc_debug = onoff;
}

/* notifiers AP when LPM3 sends msgs*/
static int adc_dev_notifier(struct notifier_block *nb, unsigned long len, void *msg)
{
	u32 *_msg = (u32 *)msg;
	int is_complete = ADC_RESULT_ERR;
	unsigned long i;

	if (1 == g_hkadc_debug) {
		for (i = 0; i < len; i++)
			pr_info("%s_debug:[notifier] msg[%lu] = 0x%x\n", MODULE_NAME, i, _msg[i]);
	}

	if (_msg[0] == ADC_IPC_DATA) {
		if (!(ADC_DATA_BIT_R(_msg[1], 8) & ADC_DATA_MASK)) {
			if ((_msg[1] & ADC_DATA_MASK) == hisi_adc_dev->info.channel) {
				hisi_adc_dev->info.value = ADC_DATA_BIT_R(_msg[1], 16);
				is_complete = 0;
			} else {
				pr_info("%s: msg[1][0x%x]\n", MODULE_NAME, _msg[1]);
			}
		} else {
			is_complete = 0;
			hisi_adc_dev->info.value = ADC_RESULT_ERR;
			pr_err("%s: error value msg[1][0x%x]\n", MODULE_NAME, _msg[1]);
		}
	}

	if (!is_complete)
		complete(&hisi_adc_dev->completion);

	return 0;
}


/* AP sends msgs to LPM3 for adc sampling&converting. */
static int adc_send_ipc_to_lpm3(int channel)
{
	int loop = ADC_IPC_MAX_CNT;
	int ret = 0;

	if (channel > ADC_CHN_MAX) {
		pr_err("%s: invalid channel!\n", MODULE_NAME);
		ret = -EINVAL;
		goto err_adc_channel;
	}

	if (!hisi_adc_dev) {
		pr_err("%s: adc dev is not initialized yet!\n", MODULE_NAME);
		ret = -ENODEV;
		goto err_adc_dev;
	}

	if (hisi_adc_dev->tx_msg[ADC_IPC_CMD_TYPE] != ADC_IPC_DATA)
		hisi_adc_dev->tx_msg[ADC_IPC_CMD_TYPE] = ADC_IPC_DATA;

	hisi_adc_dev->info.channel = channel;
	hisi_adc_dev->tx_msg[ADC_IPC_CMD_CHANNEL] = channel;

	do {
		ret = RPROC_ASYNC_SEND(ADC_RPROC_SEND_ID, (mbox_msg_t *)hisi_adc_dev->tx_msg, ADC_IPC_CMD_LEN);
		loop--;
	} while (ret == -ENOMEM && loop > 0);
	if (ret) {
		pr_err("%s: fail to send mbox msg, ret = %d!\n", MODULE_NAME, ret);
		goto err_msg_async;
	}

	return ret;

err_msg_async:
	hisi_adc_dev->info.channel = ADC_RESULT_ERR;
err_adc_dev:
err_adc_channel:
	return ret;
}

/*
 * Function name:adc_to_volt.
 * Discription:calculate volt from hkadc.
 * Parameters:
 *      @ adc
 * return value:
 *      @ volt(mv): negative-->failed, other-->succeed.
 */
static int adc_to_volt(int adc)
{
	int volt;
	if (adc < 0)
		return -1;

	volt = ((adc * HKADC_VREF) / HKADC_ACCURACY);
	return volt;
}

/*
 * Function name:hisi_adc_get_value.
 * Discription:get volt from hkadc.
 * Parameters:
 *      @ adc_channel
 * return value:
 *      @ channel volt(mv): negative-->failed, other-->succeed.
 */
int hisi_adc_get_value(int adc_channel)
{
	int ret;
	int volt;
	ret = hisi_adc_get_adc(adc_channel);

	if (ret < 0)
		return ret;
	volt = adc_to_volt(ret);
	return volt;

}
EXPORT_SYMBOL(hisi_adc_get_value);

/*
 * Function name:hisi_adc_get_adc.
 * Discription:get adc value from hkadc.
 * Parameters:
 *      @ adc_channel
 * return value:
 *      @ adc value(12 bits): negative-->failed, other-->succeed.
 */
int hisi_adc_get_adc(int adc_channel)
{
	int ret = 0;

	mutex_lock(&hisi_adc_dev->mutex);
	INIT_COMPLETION(hisi_adc_dev->completion);

	ret = adc_send_ipc_to_lpm3(adc_channel);
	if (ret)
		goto err_send_msg;

	ret = wait_for_completion_timeout(&hisi_adc_dev->completion, msecs_to_jiffies(ADC_IPC_TIMEOUT));
	if (!ret) {
		pr_err("%s: channel-%d timeout!\n", MODULE_NAME, adc_channel);
		ret =  -ETIMEOUT;
	} else {
		ret = 0;
	}

err_send_msg:
	hisi_adc_dev->info.channel = ADC_RESULT_ERR;
	mutex_unlock(&hisi_adc_dev->mutex);
	if (1 == g_hkadc_debug)
		pr_info("%s value %d;ret %d\n", __func__, hisi_adc_dev->info.value, ret);

	return ret ? ret : hisi_adc_dev->info.value;
}
EXPORT_SYMBOL(hisi_adc_get_adc);

#ifdef CONFIG_DEBUG_FS

/* debugfs for adc */
static int adc_debugfs_show(struct seq_file *s, void *data)
{
	return seq_printf(s, "ch-%d: adc = %d, volt = %dmv\n", buff[0], buff[1], buff[2]);
}

static int adc_debugfs_open(struct inode *inode, struct file *file)
{
	return single_open(file, adc_debugfs_show, NULL);
}

static ssize_t adc_debugfs_write(struct file *file,
					const char __user *user_buf,
					size_t count,
					loff_t *ppos)
{
	int ret;
	long val;
	char buf[64];
	int buf_size;

	buf_size = min(count, sizeof(buf)-1);

	if (copy_from_user(buf, user_buf, buf_size))
		return -EFAULT;

	buf[buf_size] = 0;

	ret = kstrtol(buf, 10, &val);
	if (ret < 0) {
		pr_err("%s: input error!\n", MODULE_NAME);
		return count;
	}

	buff[0] = (int)val;
	buff[1] = hisi_adc_get_adc(buff[0]);
	buff[2] = adc_to_volt(buff[1]);
	pr_info("%s: channel[%d] adc is %d\n, volt is %dmv\n",
					MODULE_NAME,
					buff[0],
					buff[1],
					buff[2]);
	return count;
}

static const struct file_operations adc_operations = {
	.open		= adc_debugfs_open,
	.read		= seq_read,
	.write		= adc_debugfs_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static void adc_init_device_debugfs(void)
{
	buff[0] = ADC_RESULT_ERR;
	buff[1] = ADC_RESULT_ERR;
	buff[2] = ADC_RESULT_ERR;

	debugfs_root = debugfs_create_dir(MODULE_NAME, NULL);
	if (IS_ERR(debugfs_root) || !debugfs_root) {
		pr_err("%s: failed to create debugfs directory!\n", MODULE_NAME);
		return;
	}

	debugfs_create_file("channel", S_IFREG | S_IRUGO,
			    debugfs_root, NULL, &adc_operations);
}

static void adc_remove_device_debugfs(void)
{
	debugfs_remove_recursive(debugfs_root);
}

#else

static void adc_init_device_debugfs(void)
{
}

static void adc_remove_device_debugfs(void)
{
}

#endif

/* hisi adc init function */
static int __init hisi_adc_driver_init(void)
{
	int ret = 0;

	hisi_adc_dev = kzalloc(sizeof(*hisi_adc_dev), GFP_KERNEL);
	if (!hisi_adc_dev) {
		pr_err("%s: fail to alloc adc dev!\n", MODULE_NAME);
		ret = -ENOMEM;
		goto err_adc_dev;
	}

	hisi_adc_dev->nb = kzalloc(sizeof(struct notifier_block), GFP_KERNEL);
	if (!hisi_adc_dev->nb) {
		pr_err("%s: fail to alloc notifier_block!\n", MODULE_NAME);
		ret =  -ENOMEM;
		goto err_adc_nb;
	}

	hisi_adc_dev->nb->next = NULL;
	hisi_adc_dev->nb->notifier_call = adc_dev_notifier;

	/* register the rx notify callback */
	ret = RPROC_MONITOR_REGISTER(ADC_RPROC_RECV_ID,  hisi_adc_dev->nb);
	if (ret)
	{
		pr_info("%s:RPROC_MONITOR_REGISTER failed", __func__);
		goto err_get_mbox;
	}

	hisi_adc_dev->tx_msg[ADC_IPC_CMD_TYPE] = ADC_IPC_DATA;
	hisi_adc_dev->tx_msg[ADC_IPC_CMD_CHANNEL] = ADC_RESULT_ERR;

	mutex_init(&hisi_adc_dev->mutex);
	init_completion(&hisi_adc_dev->completion);
	adc_init_device_debugfs();

	pr_info("%s: init ok!\n", MODULE_NAME);
	return ret;

err_get_mbox:
	kfree(hisi_adc_dev->nb);
	hisi_adc_dev->nb = NULL;
err_adc_nb:
	kfree(hisi_adc_dev);
	hisi_adc_dev = NULL;
err_adc_dev:
	return ret;
}

/* hisi adc exit function */
static void __exit hisi_adc_driver_exit(void)
{
	if (hisi_adc_dev) {
		kfree(hisi_adc_dev->nb);
		hisi_adc_dev->nb = NULL;

		kfree(hisi_adc_dev);
		hisi_adc_dev = NULL;
	}

	adc_remove_device_debugfs();
}

fs_initcall(hisi_adc_driver_init);
module_exit(hisi_adc_driver_exit);
