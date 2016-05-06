/*
 * drivers/rtc/rtc-pl031.c
 *
 * Real Time Clock interface for ARM AMBA PrimeCell 031 RTC
 *
 * Author: Deepak Saxena <dsaxena@plexity.net>
 *
 * Copyright 2006 (c) MontaVista Software, Inc.
 *
 * Author: Mian Yousaf Kaukab <mian.yousaf.kaukab@stericsson.com>
 * Copyright 2010 (c) ST-Ericsson AB
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include <linux/module.h>
#include <linux/rtc.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/amba/bus.h>
#include <linux/io.h>
#include <linux/bcd.h>
#include <linux/delay.h>
#include <linux/slab.h>
#ifdef CONFIG_RTC_DRV_HI3635_PMU
#include <linux/of_address.h>
#include <linux/reboot.h>
#include <linux/syscalls.h>
#include <linux/workqueue.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/mfd/hi3xxx_hi6421v300.h>
#endif

/*
 * Register definitions
 */
#define	RTC_DR		0x00	/* Data read register */
#define	RTC_MR		0x04	/* Match register */
#define	RTC_LR		0x08	/* Data load register */
#define	RTC_CR		0x0c	/* Control register */
#define	RTC_IMSC	0x10	/* Interrupt mask and set register */
#define	RTC_RIS		0x14	/* Raw interrupt status register */
#define	RTC_MIS		0x18	/* Masked interrupt status register */
#define	RTC_ICR		0x1c	/* Interrupt clear register */
/* ST variants have additional timer functionality */
#define RTC_TDR		0x20	/* Timer data read register */
#define RTC_TLR		0x24	/* Timer data load register */
#define RTC_TCR		0x28	/* Timer control register */
#define RTC_YDR		0x30	/* Year data read register */
#define RTC_YMR		0x34	/* Year match register */
#define RTC_YLR		0x38	/* Year data load register */

#define RTC_CR_EN	(1 << 0)	/* counter enable bit */
#define RTC_CR_CWEN	(1 << 26)	/* Clockwatch enable bit */

#define RTC_TCR_EN	(1 << 1) /* Periodic timer enable bit */

/* Common bit definitions for Interrupt status and control registers */
#define RTC_BIT_AI	(1 << 0) /* Alarm interrupt bit */
#define RTC_BIT_PI	(1 << 1) /* Periodic interrupt bit. ST variants only. */

/* Common bit definations for ST v2 for reading/writing time */
#define RTC_SEC_SHIFT 0
#define RTC_SEC_MASK (0x3F << RTC_SEC_SHIFT) /* Second [0-59] */
#define RTC_MIN_SHIFT 6
#define RTC_MIN_MASK (0x3F << RTC_MIN_SHIFT) /* Minute [0-59] */
#define RTC_HOUR_SHIFT 12
#define RTC_HOUR_MASK (0x1F << RTC_HOUR_SHIFT) /* Hour [0-23] */
#define RTC_WDAY_SHIFT 17
#define RTC_WDAY_MASK (0x7 << RTC_WDAY_SHIFT) /* Day of Week [1-7] 1=Sunday */
#define RTC_MDAY_SHIFT 20
#define RTC_MDAY_MASK (0x1F << RTC_MDAY_SHIFT) /* Day of Month [1-31] */
#define RTC_MON_SHIFT 25
#define RTC_MON_MASK (0xF << RTC_MON_SHIFT) /* Month [1-12] 1=January */

#define RTC_TIMER_FREQ 32768

#ifdef CONFIG_RTC_DRV_HI3635_PMU
/*
 * Hi6421V300 RTC Register definitions
 */
#define HI6421V300_RTCDR0               (0x12C) /* Data read register */
#define HI6421V300_RTCDR1               (0x12D) /* Data read register */
#define HI6421V300_RTCDR2               (0x12E) /* Data read register */
#define HI6421V300_RTCDR3               (0x12F) /* Data read register */
#define HI6421V300_RTCMR0               (0x130) /* Match register */
#define HI6421V300_RTCMR1               (0x131) /* Match register */
#define HI6421V300_RTCMR2               (0x132) /* Match register */
#define HI6421V300_RTCMR3               (0x133) /* Match register */
#define HI6421V300_RTCLR0               (0x134) /* Data load register */
#define HI6421V300_RTCLR1               (0x135) /* Data load register */
#define HI6421V300_RTCLR2               (0x136) /* Data load register */
#define HI6421V300_RTCLR3               (0x137) /* Data load register */
#define HI6421V300_RTCCTRL              (0x138) /* Control register */
#define HI6421V300_RTCIRQ0              (0x120) /* Alarm interrupt bit */
#define HI6421V300_RTCIRQM0             (0x102) /* Alarm interrupt mask and set register  1:enable,0:disable */
#define HI6421V300_IRQSTS             (0x001) /* Alarm interrupt mask and set register  1:enable,0:disable */
#define HI6421V300_ALARM_ON             (0x001) /* Alarm current status */
#define ALARM_ENABLE_MASK               0xFE
#endif
/**
 * struct pl031_vendor_data - per-vendor variations
 * @ops: the vendor-specific operations used on this silicon version
 * @clockwatch: if this is an ST Microelectronics silicon version with a
 *	clockwatch function
 * @st_weekday: if this is an ST Microelectronics silicon version that need
 *	the weekday fix
 * @irqflags: special IRQ flags per variant
 */
struct pl031_vendor_data {
	struct rtc_class_ops ops;
	bool clockwatch;
	bool st_weekday;
	unsigned long irqflags;
};

struct pl031_local {
	struct pl031_vendor_data *vendor;
	struct rtc_device *rtc;
	void __iomem *base;
#ifdef CONFIG_RTC_DRV_HI3635_PMU
	void __iomem *hisi_pmurtc_base;
#endif
};
#ifdef CONFIG_RTC_DRV_HI3635_PMU
extern unsigned int get_pd_charge_flag(void);
static struct pl031_local *pmurtcdata;
/* read 4 8-bit registers & covert it into a 32-bit data */
static unsigned int hisi_pmu_read_bulk(void __iomem *base, unsigned int reg)
{
	unsigned int data, sum = 0;
	int i;
	for (i = 0; i < 4; i++) {
		data = readl_relaxed(base + ((reg + i) << 2));
		sum |= (data & 0xff) << (i * 8);
	}
	return sum;
}

/* write a 32-bit data into 4 8-bit registers */
static void hisi_pmu_write_bulk(void __iomem *base, unsigned int reg,
			      unsigned int data)
{
	unsigned int value;
	int i;

	for (i = 0; i < 4; i++) {
		value = (data >> (i * 8)) & 0xff;
		writel_relaxed(value, base + ((reg + i) << 2));
	}
}

static int hisi_pmu_rtc_settime(struct device *dev, struct rtc_time *tm)
{
	unsigned long time;
	struct pl031_local *ldata = dev_get_drvdata(dev);
	int ret;

	ret = rtc_valid_tm(tm);
	if (ret != 0) {
		dev_err(dev, "pmu rtc set time is not valid!\n");
		return ret;
	}

	rtc_tm_to_time(tm, &time);

    writel_relaxed(1, ldata->hisi_pmurtc_base + (HI6421V300_RTCCTRL << 2));

    udelay(100);

	hisi_pmu_write_bulk(ldata->hisi_pmurtc_base, HI6421V300_RTCLR0, time);

	return 0;
}

/* FIXME: Alarm Open the Phone if shutdown.
 * Record Alarm Time to PMU RTC RTCMR
 */
void hisi_pmu_rtc_setalarmtime(unsigned long time)
{
	unsigned char maskbit = 0;

	maskbit = readl_relaxed(pmurtcdata->hisi_pmurtc_base + (HI6421V300_RTCIRQM0 << 2));

	if (0 == time) {
		maskbit |= ~ALARM_ENABLE_MASK;
		writel_relaxed(maskbit, pmurtcdata->hisi_pmurtc_base + (HI6421V300_RTCIRQM0 << 2));
		return;
	}

	hisi_pmu_write_bulk(pmurtcdata->hisi_pmurtc_base, HI6421V300_RTCMR0, time);

	maskbit &= ALARM_ENABLE_MASK;
	writel_relaxed(maskbit, pmurtcdata->hisi_pmurtc_base + (HI6421V300_RTCIRQM0 << 2));
}

void hisi_pmu_rtc_readtime(struct rtc_time *tm)
{
	unsigned long time;

	time = hisi_pmu_read_bulk(pmurtcdata->hisi_pmurtc_base, HI6421V300_RTCDR0);

	rtc_time_to_tm(time, tm);
}

static int hisi_pmu_rtc_config(struct device *dev)
{
	unsigned long time_val = 0;
	unsigned long rtccr_val = 0;
	int ret = 0;
	struct device_node *node;
	struct rtc_time tm;
	struct pl031_local *ldata = dev_get_drvdata(dev);

	node = of_find_compatible_node(NULL, NULL, "hisilicon,hi6421-pmurtc");
	if (!node) {
		dev_err(dev, "hisi_pmu_rtc_config: of_find_compatible_node failed!\n");
		goto err;
	}

	ldata->hisi_pmurtc_base = of_iomap(node, 0);
	if (!ldata->hisi_pmurtc_base) {
		dev_err(dev, "hisi_pmu_rtc_config: of_iomap failed\n");
		goto err;
	}

	memset(&tm, 0, sizeof(struct rtc_time));

	/* read PMU RTC (battery there!) */
	rtccr_val = readl_relaxed(ldata->hisi_pmurtc_base
			+ (HI6421V300_RTCCTRL << 2));
	if (rtccr_val == 0) {
		tm.tm_year = 111;
		tm.tm_mon = 0;
		tm.tm_mday = 1;
		ret = hisi_pmu_rtc_settime(dev, &tm);
		if (ret)
			goto err_settime;
	} else {
		hisi_pmu_rtc_readtime(&tm);
	}

	rtc_tm_to_time(&tm, &time_val);

	dev_info(dev, "rtc: year %d mon %d day %d hour %d min %d sec %d time 0x%lx\n",
			tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, time_val);

	/* set on-cpu rtc load value */
	writel(time_val, ldata->base + RTC_LR);

	return ret;

err_settime:
	iounmap(ldata->hisi_pmurtc_base);
err:
	dev_err(dev, "hisi_pmu_rtc_config() failed!\n");
	return ret;
}

static void hisi_pmu_rtc_unconfig(struct device *dev)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);

	iounmap(ldata->hisi_pmurtc_base);
}

static int oem_rtc_reboot_thread(void *u)
{
	printk(KERN_INFO "Entering Rebooting Causeed by Alarm...\n");
	emergency_remount();
	sys_sync();
	msleep(500);
	kernel_restart("oem_rtc");

	/* should not be here */
	panic("oem_rtc");
	return 0;
}

void oem_rtc_reboot(unsigned long t)
{
	kernel_thread(oem_rtc_reboot_thread, NULL, CLONE_FS | CLONE_FILES);
}
static DECLARE_TASKLET(oem_rtc_reboot_tasklet, oem_rtc_reboot, 0);

irqreturn_t pmu_rtc_handler(int irq, void *data)
{
	struct hi6421_pmic *pmic = (struct hi6421_pmic *)data;
	unsigned char alarm_status = HI6421V300_ALARM_ON;

	/*needn't clear interrupt irq because pmic has done*/
	alarm_status &= hi6421_pmic_read(pmic, HI6421V300_IRQSTS);

	printk(KERN_INFO "pmu_rtc_handler alarm_status=%d\n", alarm_status);

	if (0 == alarm_status) {
		return IRQ_HANDLED;
	}

	if(unlikely(get_pd_charge_flag()))
	{
		printk(KERN_INFO "pmu_rtc_handler startreboot");
		tasklet_schedule(&oem_rtc_reboot_tasklet);
	}
	return IRQ_HANDLED;
}
EXPORT_SYMBOL(pmu_rtc_handler);

#else

static void hisi_pmu_rtc_settime(struct device *dev, struct rtc_time *tm) { }

void hisi_pmu_rtc_setalarmtime(unsigned long time) { }

static int hisi_pmu_rtc_config(struct device *dev) { return 0; }

static void hisi_pmu_rtc_unconfig(struct device *dev) { }

#endif

static int pl031_alarm_irq_enable(struct device *dev,
	unsigned int enabled)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);
	unsigned long imsc;

	/* Clear any pending alarm interrupts. */
	writel(RTC_BIT_AI, ldata->base + RTC_ICR);

	imsc = readl(ldata->base + RTC_IMSC);

	if (enabled == 1)
		writel(imsc | RTC_BIT_AI, ldata->base + RTC_IMSC);
	else
		writel(imsc & ~RTC_BIT_AI, ldata->base + RTC_IMSC);

	return 0;
}

/*
 * Convert Gregorian date to ST v2 RTC format.
 */
static int pl031_stv2_tm_to_time(struct device *dev,
				 struct rtc_time *tm, unsigned long *st_time,
	unsigned long *bcd_year)
{
	int year = tm->tm_year + 1900;
	int wday = tm->tm_wday;

	/* wday masking is not working in hardware so wday must be valid */
	if (wday < -1 || wday > 6) {
		dev_err(dev, "invalid wday value %d\n", tm->tm_wday);
		return -EINVAL;
	} else if (wday == -1) {
		/* wday is not provided, calculate it here */
		unsigned long time;
		struct rtc_time calc_tm;

		rtc_tm_to_time(tm, &time);
		rtc_time_to_tm(time, &calc_tm);
		wday = calc_tm.tm_wday;
	}

	*bcd_year = (bin2bcd(year % 100) | bin2bcd(year / 100) << 8);

	*st_time = ((tm->tm_mon + 1) << RTC_MON_SHIFT)
			|	(tm->tm_mday << RTC_MDAY_SHIFT)
			|	((wday + 1) << RTC_WDAY_SHIFT)
			|	(tm->tm_hour << RTC_HOUR_SHIFT)
			|	(tm->tm_min << RTC_MIN_SHIFT)
			|	(tm->tm_sec << RTC_SEC_SHIFT);

	return 0;
}

/*
 * Convert ST v2 RTC format to Gregorian date.
 */
static int pl031_stv2_time_to_tm(unsigned long st_time, unsigned long bcd_year,
	struct rtc_time *tm)
{
	tm->tm_year = bcd2bin(bcd_year) + (bcd2bin(bcd_year >> 8) * 100);
	tm->tm_mon  = ((st_time & RTC_MON_MASK) >> RTC_MON_SHIFT) - 1;
	tm->tm_mday = ((st_time & RTC_MDAY_MASK) >> RTC_MDAY_SHIFT);
	tm->tm_wday = ((st_time & RTC_WDAY_MASK) >> RTC_WDAY_SHIFT) - 1;
	tm->tm_hour = ((st_time & RTC_HOUR_MASK) >> RTC_HOUR_SHIFT);
	tm->tm_min  = ((st_time & RTC_MIN_MASK) >> RTC_MIN_SHIFT);
	tm->tm_sec  = ((st_time & RTC_SEC_MASK) >> RTC_SEC_SHIFT);

	tm->tm_yday = rtc_year_days(tm->tm_mday, tm->tm_mon, tm->tm_year);
	tm->tm_year -= 1900;

	return 0;
}

static int pl031_stv2_read_time(struct device *dev, struct rtc_time *tm)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);

	pl031_stv2_time_to_tm(readl(ldata->base + RTC_DR),
			readl(ldata->base + RTC_YDR), tm);

	return 0;
}

static int pl031_stv2_set_time(struct device *dev, struct rtc_time *tm)
{
	unsigned long time;
	unsigned long bcd_year;
	struct pl031_local *ldata = dev_get_drvdata(dev);
	int ret;

	ret = pl031_stv2_tm_to_time(dev, tm, &time, &bcd_year);
	if (ret == 0) {
		writel(bcd_year, ldata->base + RTC_YLR);
		writel(time, ldata->base + RTC_LR);
	}

	return ret;
}

static int pl031_stv2_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);
	int ret;

	ret = pl031_stv2_time_to_tm(readl(ldata->base + RTC_MR),
			readl(ldata->base + RTC_YMR), &alarm->time);

	alarm->pending = readl(ldata->base + RTC_RIS) & RTC_BIT_AI;
	alarm->enabled = readl(ldata->base + RTC_IMSC) & RTC_BIT_AI;

	return ret;
}

static int pl031_stv2_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);
	unsigned long time;
	unsigned long bcd_year;
	int ret;

	/* At the moment, we can only deal with non-wildcarded alarm times. */
	ret = rtc_valid_tm(&alarm->time);
	if (ret == 0) {
		ret = pl031_stv2_tm_to_time(dev, &alarm->time,
					    &time, &bcd_year);
		if (ret == 0) {
			writel(bcd_year, ldata->base + RTC_YMR);
			writel(time, ldata->base + RTC_MR);

			pl031_alarm_irq_enable(dev, alarm->enabled);
		}
	}

	return ret;
}

static irqreturn_t pl031_interrupt(int irq, void *dev_id)
{
	struct pl031_local *ldata = dev_id;
	unsigned long rtcmis;
	unsigned long events = 0;

	rtcmis = readl(ldata->base + RTC_MIS);
	if (rtcmis & RTC_BIT_AI) {
		writel(RTC_BIT_AI, ldata->base + RTC_ICR);
		events |= (RTC_AF | RTC_IRQF);
		rtc_update_irq(ldata->rtc, 1, events);

		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}

static int pl031_read_time(struct device *dev, struct rtc_time *tm)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);

	rtc_time_to_tm(readl(ldata->base + RTC_DR), tm);

	return 0;
}

static int pl031_set_time(struct device *dev, struct rtc_time *tm)
{
	unsigned long time;
	struct pl031_local *ldata = dev_get_drvdata(dev);
	int ret;

	ret = rtc_tm_to_time(tm, &time);

	if (ret == 0)
		writel(time, ldata->base + RTC_LR);

	hisi_pmu_rtc_settime(dev, tm);

	return ret;
}

static int pl031_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);

	rtc_time_to_tm(readl(ldata->base + RTC_MR), &alarm->time);

	alarm->pending = readl(ldata->base + RTC_RIS) & RTC_BIT_AI;
	alarm->enabled = readl(ldata->base + RTC_IMSC) & RTC_BIT_AI;

	return 0;
}

static int pl031_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);
	unsigned long time;
	int ret;

	/* At the moment, we can only deal with non-wildcarded alarm times. */
	ret = rtc_valid_tm(&alarm->time);
	if (ret == 0) {
		ret = rtc_tm_to_time(&alarm->time, &time);
		if (ret == 0) {
			writel(time, ldata->base + RTC_MR);
			pl031_alarm_irq_enable(dev, alarm->enabled);
		}
	}

	return ret;
}

static int pl031_remove(struct amba_device *adev)
{
	struct pl031_local *ldata = dev_get_drvdata(&adev->dev);

	amba_set_drvdata(adev, NULL);
	free_irq(adev->irq[0], ldata);
	rtc_device_unregister(ldata->rtc);
	iounmap(ldata->base);
	hisi_pmu_rtc_unconfig(&adev->dev);
	kfree(ldata);
	amba_release_regions(adev);

	return 0;
}

static int pl031_probe(struct amba_device *adev, const struct amba_id *id)
{
	int ret;
	struct pl031_local *ldata;
	struct pl031_vendor_data *vendor = id->data;
	struct rtc_class_ops *ops = &vendor->ops;
	unsigned long time = 0;
	unsigned long data = 0;

	ret = amba_request_regions(adev, NULL);
	if (ret)
		goto err_req;

	ldata = kzalloc(sizeof(struct pl031_local), GFP_KERNEL);
	if (!ldata) {
		ret = -ENOMEM;
		goto out;
	}
	ldata->vendor = vendor;

	ldata->base = ioremap(adev->res.start, resource_size(&adev->res));

	if (!ldata->base) {
		ret = -ENOMEM;
		goto out_no_remap;
	}

	amba_set_drvdata(adev, ldata);
#ifdef CONFIG_RTC_DRV_HI3635_PMU
	pmurtcdata = ldata;
#endif
	dev_dbg(&adev->dev, "designer ID = 0x%02x\n", amba_manf(adev));
	dev_dbg(&adev->dev, "revision = 0x%01x\n", amba_rev(adev));

	data = readl(ldata->base + RTC_CR);
	/* Enable the clockwatch on ST Variants */
	if (vendor->clockwatch)
		data |= RTC_CR_CWEN;
	else
		data |= RTC_CR_EN;
	writel(data, ldata->base + RTC_CR);

	/*
	 * On ST PL031 variants, the RTC reset value does not provide correct
	 * weekday for 2000-01-01. Correct the erroneous sunday to saturday.
	 */
	if (vendor->st_weekday) {
		if (readl(ldata->base + RTC_YDR) == 0x2000) {
			time = readl(ldata->base + RTC_DR);
			if ((time &
			     (RTC_MON_MASK | RTC_MDAY_MASK | RTC_WDAY_MASK))
			    == 0x02120000) {
				time = time | (0x7 << RTC_WDAY_SHIFT);
				writel(0x2000, ldata->base + RTC_YLR);
				writel(time, ldata->base + RTC_LR);
			}
		}
	}

	device_init_wakeup(&adev->dev, 1);

	ret = hisi_pmu_rtc_config(&adev->dev);
	if (ret)
		goto out_pmu_rtc_config;

	ldata->rtc = rtc_device_register("pl031", &adev->dev, ops, THIS_MODULE);
	if (IS_ERR(ldata->rtc)) {
		ret = PTR_ERR(ldata->rtc);
		goto out_no_rtc;
	}

	if (request_irq(adev->irq[0], pl031_interrupt,
			vendor->irqflags, "rtc-pl031", ldata)) {
		ret = -EIO;
		goto out_no_irq;
	}

	device_init_wakeup(&adev->dev, 1);

	return 0;

out_no_irq:
	rtc_device_unregister(ldata->rtc);
out_no_rtc:
	hisi_pmu_rtc_unconfig(&adev->dev);
out_pmu_rtc_config:
	iounmap(ldata->base);
	amba_set_drvdata(adev, NULL);
out_no_remap:
	kfree(ldata);
out:
	amba_release_regions(adev);
err_req:

	return ret;
}

#ifdef CONFIG_PM
static int pl031_suspend(struct device *dev)
{
	struct amba_device *adev = to_amba_device(dev);

	dev_info(dev, "%s+.\n",__func__);

	if (adev->irq[0] >= 0 && device_may_wakeup(&adev->dev))
		enable_irq_wake(adev->irq[0]);

	dev_info(dev, "%s-.\n",__func__);

	return 0;
}

static int pl031_resume(struct device *dev)
{
	struct amba_device *adev = to_amba_device(dev);

	dev_info(dev, "%s+.\n",__func__);

	if (adev->irq[0] >= 0 && device_may_wakeup(&adev->dev))
		disable_irq_wake(adev->irq[0]);

	dev_info(dev, "%s-.\n",__func__);

	return 0;
}

static SIMPLE_DEV_PM_OPS(pl031_pm, pl031_suspend, pl031_resume);

#define PL031_PM (&pl031_pm)
#else
#define PL031_PM NULL
#endif

/* Operations for the original ARM version */
static struct pl031_vendor_data arm_pl031 = {
	.ops = {
		.read_time = pl031_read_time,
		.set_time = pl031_set_time,
		.read_alarm = pl031_read_alarm,
		.set_alarm = pl031_set_alarm,
		.alarm_irq_enable = pl031_alarm_irq_enable,
	},
	.irqflags = IRQF_NO_SUSPEND,
};

/* The First ST derivative */
static struct pl031_vendor_data stv1_pl031 = {
	.ops = {
		.read_time = pl031_read_time,
		.set_time = pl031_set_time,
		.read_alarm = pl031_read_alarm,
		.set_alarm = pl031_set_alarm,
		.alarm_irq_enable = pl031_alarm_irq_enable,
	},
	.clockwatch = true,
	.st_weekday = true,
	.irqflags = IRQF_NO_SUSPEND,
};

/* And the second ST derivative */
static struct pl031_vendor_data stv2_pl031 = {
	.ops = {
		.read_time = pl031_stv2_read_time,
		.set_time = pl031_stv2_set_time,
		.read_alarm = pl031_stv2_read_alarm,
		.set_alarm = pl031_stv2_set_alarm,
		.alarm_irq_enable = pl031_alarm_irq_enable,
	},
	.clockwatch = true,
	.st_weekday = true,
	/*
	 * This variant shares the IRQ with another block and must not
	 * suspend that IRQ line.
	 */
	.irqflags = IRQF_SHARED | IRQF_NO_SUSPEND,
};

static struct amba_id pl031_ids[] = {
	{
		.id = 0x00041031,
		.mask = 0x000fffff,
		.data = &arm_pl031,
	},
	/* ST Micro variants */
	{
		.id = 0x00180031,
		.mask = 0x00ffffff,
		.data = &stv1_pl031,
	},
	{
		.id = 0x00280031,
		.mask = 0x00ffffff,
		.data = &stv2_pl031,
	},
	{0, 0},
};

MODULE_DEVICE_TABLE(amba, pl031_ids);

static struct amba_driver pl031_driver = {
	.drv = {
		.name = "rtc-pl031",
		.pm = PL031_PM,
	},
	.id_table = pl031_ids,
	.probe = pl031_probe,
	.remove = pl031_remove,
};

module_amba_driver(pl031_driver);

MODULE_AUTHOR("Deepak Saxena <dsaxena@plexity.net");
MODULE_DESCRIPTION("ARM AMBA PL031 RTC Driver");
MODULE_LICENSE("GPL");
