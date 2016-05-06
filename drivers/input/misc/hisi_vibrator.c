/*
 * Copyright (C) 2008 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/hrtimer.h>
#include <linux/err.h>
#include <linux/irq.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/regulator/consumer.h>
#include <linux/mfd/hisi_pmic.h>
#include "../../staging/android/timed_output.h"
//#include  "drv_regulator_user.h"
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/clk.h>
#include <linux/of_device.h>
#include <linux/hisi/hisi_vibrator.h>

#ifdef CONFIG_ANDROID_HISI_VIBRATOR_AUTO_CONTROL
#include <linux/hkadc/hisi_adc_hal.h>
#endif

struct hisi_vibrator_data {
	struct timed_output_dev dev;
	struct hisi_vibrator_platform_data *plat_data;
	struct hrtimer timer;
	struct mutex lock;
	struct clk *clk;
	void __iomem *hisi_vibrator_base;
	int value;
    int vibrator_reg_on;
    int vibrator_reg_off;
    int vibrator_bit_on;
	u8 freq;
	u8 power;
	u8 mode;
#ifdef CONFIG_ANDROID_HISI_VIBRATOR_AUTO_CONTROL
	u8 battery_power;
#endif
};

struct hisi_vibrator_data *hisi_vibrator_pdata;
static void hisi_vibrator_onoff_handler(struct work_struct *data);
static struct workqueue_struct *done_queue;

static bool vib_reg_enabled=false;
static struct regulator *hisi_vibrator_vout_reg=NULL;

#ifdef CONFIG_ANDROID_HISI_VIBRATOR_AUTO_CONTROL
static unsigned long g_pre_set_time;
#endif
volatile int vibrator_shake = 0;

static DECLARE_WORK(done_work, hisi_vibrator_onoff_handler);

static void hisi_vibrator_onoff(int on)
{
	struct hisi_vibrator_data *pdata = hisi_vibrator_pdata;
	pdata->value = on;
	if (on) {
	     vibrator_shake = 1;
            hisi_pmic_reg_write(pdata->vibrator_reg_on,pdata->vibrator_bit_on);
	} else {
	     vibrator_shake = 0;
            hisi_pmic_reg_write(pdata->vibrator_reg_off,VIBRATOR_OFF);
    }
}
static void hisi_vibrator_regulator_enable(void)
{
	int error;

	if (true == vib_reg_enabled)
		return ;

	BUG_ON(IS_ERR(hisi_vibrator_vout_reg));
	printk("---- hisi_vibrator_regulator_enable ------ ");
	error = regulator_enable(hisi_vibrator_vout_reg);
	if (error < 0) {
		pr_err( "%s: failed to enable edge vibrator vdd\n", __func__);
		return ;
	}

	vib_reg_enabled = true;
	return ;
}

static void hisi_vibrator_regulator_disable(void)
{
	int error;

	if (false == vib_reg_enabled)
		return ;

	BUG_ON(IS_ERR(hisi_vibrator_vout_reg));
	printk("---- hisi_vibrator_regulator_disable ------ ");
	error = regulator_disable(hisi_vibrator_vout_reg);
	if (error < 0) {
		pr_err( "%s: failed to disable edge vibrator vdd\n", __func__);
		return ;
	}

	vib_reg_enabled = false;
	return ;
}

static void hisi_vibrator_onoff_handler(struct work_struct *data)
{
	struct hisi_vibrator_data *pdata = hisi_vibrator_pdata;
	int on = pdata->value;

        mutex_lock(&pdata->lock);

	if (on) {
            hisi_vibrator_regulator_enable();
	} else {
            hisi_vibrator_regulator_disable();
	}

        mutex_unlock(&pdata->lock);

	return ;
}
static enum hrtimer_restart hisi_vibrator_timer_func(struct hrtimer *timer)
{
    pr_info("hisi_vibrator_timer_func called\n");
	hisi_vibrator_onoff(0);

	return HRTIMER_NORESTART;
}

static int hisi_vibrator_get_time(struct timed_output_dev *dev)
{
	struct hisi_vibrator_data *pdata =
			container_of(dev, struct hisi_vibrator_data, dev);
	if (hrtimer_active(&pdata->timer)) {
		ktime_t r = hrtimer_get_remaining(&pdata->timer);
		struct timeval t = ktime_to_timeval(r);
		return t.tv_sec * 1000 + t.tv_usec / 1000;
	} else
		return 0;
}

static void hisi_vibrator_enable(struct timed_output_dev *dev, int value)
{
	struct hisi_vibrator_data *pdata = container_of(dev, struct hisi_vibrator_data, dev);
#ifdef CONFIG_ANDROID_HISI_VIBRATOR_AUTO_CONTROL
	static int set_count;
#endif
    pr_info("hisi_vibrator_enable,value=%d\n",value);
	if (value < 0) {
		pr_err("error:vibrator_enable value:%d is negative\n", value);
		return;
	}
	/* cancel previous timer */
	if (hrtimer_active(&pdata->timer))
        hrtimer_cancel(&pdata->timer);

	if (value > 0) {
#ifdef CONFIG_ANDROID_HISI_VIBRATOR_AUTO_CONTROL
		if (time_after(jiffies, g_pre_set_time+60*HZ)) {
			g_pre_set_time = jiffies;
			set_count = 0;
		}
		if (set_count == 0)
			pdata->battery_power = hisi_vibrator_get_iset_value(0);

		set_count = (set_count+1)%50;
#endif

		if (value < TIMEOUT_MIN)
			value = TIMEOUT_MIN;
		hisi_vibrator_onoff(1);
		hrtimer_start(&pdata->timer,
			ktime_set(value / 1000, (value % 1000) * 1000000),
			HRTIMER_MODE_REL);
	} else {
		hisi_vibrator_onoff(0);
	}
}

#ifdef CONFIG_OF
static const struct of_device_id hisi_vibrator_match[] = {
	{ .compatible = "hisilicon,vibrator",},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_vibrator_match);

static int hisi_vibrator_get_vout(struct platform_device *pdev){
	int min_voltage=0;
	int max_voltage=0;
	int err = 0;

	hisi_vibrator_vout_reg = regulator_get(&pdev->dev, "vibrator-vdd");

	if (IS_ERR(hisi_vibrator_vout_reg)){
		pr_err( "%s: hisi_vibrator_vout_reg error\n", __func__);
		return -EPERM;
	}

	err = of_property_read_u32(pdev->dev.of_node, "vibrator_vout_min_voltage", &min_voltage);
	if (err) {
		pr_err("%s: min_voltage read failed\n", __func__);
		return -EPERM;
	}

	err = of_property_read_u32(pdev->dev.of_node, "vibrator_vout_max_voltage", &max_voltage);
	if (err) {
		pr_err("%s: max_voltage read failed\n", __func__);
		return -EPERM;
	}

	if (-1 == min_voltage || -1 == max_voltage) return 0;

	if (regulator_set_voltage(hisi_vibrator_vout_reg, min_voltage, max_voltage)){
		pr_err( "%s: vibrator set voltage error\n", __func__);
		return -EPERM;
	}

	return 0;
}

static ssize_t hisi_vibrator_status(struct device_driver *driver, const char *buf, size_t count)
{
	long val;
    int status = count;

    if ((strict_strtol(buf, 10, &val) < 0))
        return -EINVAL;
    if(val)
        hisi_vibrator_onoff(1);
    else
        hisi_vibrator_onoff(0);
    return status;
}

static DRIVER_ATTR(state, 644, NULL,  hisi_vibrator_status);


static struct platform_driver hisi_vibrator_driver;
#if 0
struct resource vib_resource = {
	.start	= REG_BASE_PMUSPI,
	.start	= REG_BASE_PMUSPI + REG_PMUSPI_IOSIZE -1,
	.flags	= IORESOURCE_MEM,
};
#endif

static int hisi_vibrator_probe(struct platform_device *pdev)
{
	struct hisi_vibrator_data *p_data;
	int ret = 0;

	if (!of_match_node(hisi_vibrator_match, pdev->dev.of_node)) {
		dev_err(&pdev->dev, "dev node is not match. exiting.\n");
		return -ENODEV;
	}

	ret = hisi_vibrator_get_vout(pdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to get vib vout\n");
		return ret;
	}

	p_data = kzalloc(sizeof(struct hisi_vibrator_data), GFP_KERNEL);
	if (p_data == NULL) {
		dev_err(&pdev->dev, "failed to allocate vibrator_device\n");
		return -ENOMEM;
	}

    ret = of_property_read_u32(pdev->dev.of_node, "vibrator-reg-on", &p_data->vibrator_reg_on);
    if (ret) {
        dev_err(&pdev->dev, "failed to get vibrator-reg-on\n");
        goto err;
    }

    ret = of_property_read_u32(pdev->dev.of_node, "vibrator-reg-off", &p_data->vibrator_reg_off);
    if (ret) {
        dev_err(&pdev->dev, "failed to get vibrator-reg-off\n");
        goto err;
    }

    ret = of_property_read_u32(pdev->dev.of_node, "vibrator-bit-on", &p_data->vibrator_bit_on);
    if (ret) {
        dev_err(&pdev->dev, "failed to get vibrator-bit-on\n");
        goto err;
    }

	/* init timer */
	hrtimer_init(&p_data->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	p_data->timer.function = hisi_vibrator_timer_func;

	/* init lock */
	mutex_init(&p_data->lock);

	p_data->mode = SET_MODE;
	p_data->freq = PERIOD;
	p_data->power = ISET_POWER;
	p_data->dev.name = HISI_VIBRATOR;
	p_data->dev.get_time = hisi_vibrator_get_time;
	p_data->dev.enable = hisi_vibrator_enable;

	ret = timed_output_dev_register(&p_data->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to regist dev\n");
		goto err;
	}
	platform_set_drvdata(pdev, p_data);

	hisi_vibrator_pdata = p_data;

	/* create a single thread workquene */
	done_queue = create_workqueue("done_queue");
	if (!done_queue) {
		dev_err(&pdev->dev, "failed to creat workqueue\n");
		ret = -ENOMEM;
		goto err_regis;
	}

    ret = driver_create_file(&hisi_vibrator_driver.driver, &driver_attr_state);
    if (ret) {
        dev_err(&pdev->dev, "could not create sysfs files\n");
        goto err_regis;
    }
    dev_info(&pdev->dev, "%s: successful!\n", __FUNCTION__);
	return 0;

err_regis:
	timed_output_dev_unregister(&p_data->dev);
err:
	kfree(p_data);
	p_data = NULL;
	printk("%s: failed!\n",__FUNCTION__);
	return ret;
}

static int hisi_vibrator_remove(struct platform_device *pdev)
{
	struct hisi_vibrator_data *pdata = platform_get_drvdata(pdev);

	if (pdata == NULL) {
		dev_err(&pdev->dev, "%s:pdata is NULL\n", __func__);
		return -ENODEV;
	}

	if (hrtimer_active(&pdata->timer))
		hrtimer_cancel(&pdata->timer);

	timed_output_dev_unregister(&pdata->dev);

	iounmap(pdata->hisi_vibrator_base);
	kfree(pdata);
	pdata = NULL;
	destroy_workqueue(done_queue);
	platform_set_drvdata(pdev, NULL);
	return 0;
}

static void hisi_vibrator_shutdown(struct platform_device *pdev)
{
	struct hisi_vibrator_data *pdata = platform_get_drvdata(pdev);
	if (pdata == NULL) {
		dev_err(&pdev->dev, "%s:pdata is NULL\n", __func__);
		return;
	}

	if (hrtimer_active(&pdata->timer))
		hrtimer_cancel(&pdata->timer);

        hisi_vibrator_onoff(0);

	return ;
}

#ifdef CONFIG_PM
static int  hisi_vibrator_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct hisi_vibrator_data *pdata = platform_get_drvdata(pdev);
	int ret = 0;
	if (pdata == NULL) {
		dev_err(&pdev->dev, "%s:pdata is NULL\n", __func__);
		return -ENODEV;
	}

	if (!mutex_trylock(&pdata->lock)) {
		dev_err(&pdev->dev, "%s: mutex_trylock.\n", __func__);
		return -EAGAIN;
	}
	if (hrtimer_active(&pdata->timer)) {
		if (ret) {
			pr_err("pmu clock enable failed,ret:%d\n", ret);
			mutex_unlock(&pdata->lock);
			return ret;
		}
		hrtimer_cancel(&pdata->timer);
        hisi_vibrator_onoff(0);
	}

	return 0;
}

static int hisi_vibrator_resume(struct platform_device *pdev)
{
	struct hisi_vibrator_data *pdata = platform_get_drvdata(pdev);
	if (pdata == NULL) {
		dev_err(&pdev->dev, "%s:pdata is NULL\n", __func__);
		return -ENODEV;
	}

	mutex_unlock(&pdata->lock);

	return 0;
}
#endif

#endif

static struct platform_driver hisi_vibrator_driver = {
	.probe  = hisi_vibrator_probe,
	.remove = hisi_vibrator_remove,
	.shutdown	= hisi_vibrator_shutdown,
#ifdef CONFIG_PM
	.suspend	= hisi_vibrator_suspend,
	.resume		= hisi_vibrator_resume,
#endif
	.driver = {
		.name   = HISI_VIBRATOR,
		.owner  = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_vibrator_match),
	},
};

static int __init hisi_vibrator_init(void)
{

    return platform_driver_register(&hisi_vibrator_driver);

}

static void __exit hisi_vibrator_exit(void)
{
        if (!IS_ERR(hisi_vibrator_vout_reg))
            regulator_put(hisi_vibrator_vout_reg);

        platform_driver_unregister(&hisi_vibrator_driver);
}

module_init(hisi_vibrator_init);
module_exit(hisi_vibrator_exit);

MODULE_AUTHOR("maintainer");
MODULE_DESCRIPTION(" hisi vibrator driver");
MODULE_LICENSE("GPL");