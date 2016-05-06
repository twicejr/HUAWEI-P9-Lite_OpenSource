/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"

#include "hisi_fb.h"

/*
** /sys/class/graphics/fb0/vsync_event
*/
#if defined(CONFIG_HISI_FB_VSYNC_THREAD)
#define VSYNC_TIMEOUT_MSEC (100)
#endif
#define VSYNC_CTRL_EXPIRE_COUNT	(4)

#ifdef CONFIG_REPORT_VSYNC
extern void mali_kbase_pm_report_vsync(int);
#endif
extern int mipi_dsi_ulps_cfg(struct hisi_fb_data_type *hisifd, int enable);
extern bool hisi_dss_check_reg_reload_status(struct hisi_fb_data_type *hisifd);


void hisifb_frame_updated(struct hisi_fb_data_type *hisifd)
{
	BUG_ON(hisifd == NULL);

	if (hisifd->vsync_ctrl.vsync_report_fnc) {
		atomic_inc(&(hisifd->vsync_ctrl.buffer_updated));
	}
}

void hisifb_vsync_isr_handler(struct hisi_fb_data_type *hisifd)
{
	struct hisifb_vsync *vsync_ctrl = NULL;
	int buffer_updated = 0;
	ktime_t pre_vsync_timestamp;

	BUG_ON(hisifd == NULL);
	vsync_ctrl = &(hisifd->vsync_ctrl);
	BUG_ON(vsync_ctrl == NULL);

	pre_vsync_timestamp = vsync_ctrl->vsync_timestamp;
	vsync_ctrl->vsync_timestamp = ktime_get();
	wake_up_interruptible_all(&(vsync_ctrl->vsync_wait));

	if (hisifd->panel_info.vsync_ctrl_type != VSYNC_CTRL_NONE) {
		spin_lock(&vsync_ctrl->spin_lock);
		if (vsync_ctrl->vsync_ctrl_expire_count) {
			vsync_ctrl->vsync_ctrl_expire_count--;
			if (vsync_ctrl->vsync_ctrl_expire_count == 0)
				schedule_work(&vsync_ctrl->vsync_ctrl_work);
		}
		spin_unlock(&vsync_ctrl->spin_lock);
	}

	if (vsync_ctrl->vsync_report_fnc) {
		if (hisifd->vsync_ctrl.vsync_enabled) {
			buffer_updated = atomic_dec_return(&(vsync_ctrl->buffer_updated));
		} else {
			buffer_updated = 1;
		}

		if (buffer_updated < 0) {
			atomic_cmpxchg(&(vsync_ctrl->buffer_updated), buffer_updated, 1);
		} else {
			vsync_ctrl->vsync_report_fnc(buffer_updated);
		}
	}

	if (g_debug_online_vsync) {
		HISI_FB_INFO("fb%d, VSYNC=%llu, time_diff=%llu.\n", hisifd->index,
			ktime_to_ns(hisifd->vsync_ctrl.vsync_timestamp),
			(ktime_to_ns(hisifd->vsync_ctrl.vsync_timestamp) - ktime_to_ns(pre_vsync_timestamp)));
	}
}

static int vsync_timestamp_changed(struct hisi_fb_data_type *hisifd,
	ktime_t prev_timestamp)
{
	BUG_ON(hisifd == NULL);
	return !ktime_equal(prev_timestamp, hisifd->vsync_ctrl.vsync_timestamp);
}

#if defined(CONFIG_HISI_FB_VSYNC_THREAD)
static int wait_for_vsync_thread(void *data)
{
	struct hisi_fb_data_type *hisifd = (struct hisi_fb_data_type *)data;
	ktime_t prev_timestamp;
	int ret = 0;

#if 0
	sigset_t setmask;
	sigset_t oldmask;
	sigemptyset(&setmask);
	sigaddset(&setmask, SIGSTOP);
	sigprocmask(SIG_SETMASK, &setmask, &oldmask);
#endif

	while (!kthread_should_stop()) {
		prev_timestamp = hisifd->vsync_ctrl.vsync_timestamp;
		ret = wait_event_interruptible_timeout(
			hisifd->vsync_ctrl.vsync_wait,
			vsync_timestamp_changed(hisifd, prev_timestamp) &&
			hisifd->vsync_ctrl.vsync_enabled,
			msecs_to_jiffies(VSYNC_TIMEOUT_MSEC));

		/*if (ret == 0) {
			HISI_FB_ERR("wait vsync timeout!");
			return -ETIMEDOUT;
		}*/

		if (ret > 0) {
			char *envp[2];
			char buf[64];
			/* fb%d_VSYNC=%llu */
			snprintf(buf, sizeof(buf), "VSYNC=%llu",
				ktime_to_ns(hisifd->vsync_ctrl.vsync_timestamp));
			envp[0] = buf;
			envp[1] = NULL;
			kobject_uevent_env(&hisifd->pdev->dev.kobj, KOBJ_CHANGE, envp);
		}
	}

	return 0;
}
#else
static ssize_t vsync_show_event(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	ssize_t ret = 0;
	int vsync_flag = 0;
	int secure_flag = 0;
	struct fb_info *fbi = NULL;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_secure *secure_ctrl = NULL;
	ktime_t prev_timestamp;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Pointer.\n");
		return 0;
	}

	fbi = dev_get_drvdata(dev);
	if (NULL == fbi) {
		HISI_FB_ERR("NULL Pointer.\n");
		return 0;
	}

	hisifd = (struct hisi_fb_data_type *)fbi->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer.\n");
		return 0;
	}

	secure_ctrl = &(hisifd->secure_ctrl);
	if (NULL == secure_ctrl) {
		HISI_FB_ERR("NULL Pointer.\n");
		return 0;
	}

	if (NULL == buf) {
		HISI_FB_ERR("NULL Pointer.\n");
		return 0;
	}

	prev_timestamp = hisifd->vsync_ctrl.vsync_timestamp;

	/*lint -e666*/
	ret = wait_event_interruptible(hisifd->vsync_ctrl.vsync_wait,
		(vsync_timestamp_changed(hisifd, prev_timestamp) && hisifd->vsync_ctrl.vsync_enabled)
		|| (secure_ctrl->tui_need_switch));
	/*lint +e666*/

	vsync_flag = (vsync_timestamp_changed(hisifd, prev_timestamp) &&
						hisifd->vsync_ctrl.vsync_enabled);

	secure_flag = secure_ctrl->tui_need_switch;
	if (vsync_flag && secure_flag) {
		HISI_FB_INFO("report (secure_event = %d) to hwc with vsync at (frame_no = %d).\n", \
						secure_ctrl->secure_event, hisifd->ov_req.frame_no);

		ret = snprintf(buf, PAGE_SIZE, "VSYNC=%llu, SecureEvent=%d \n",
			ktime_to_ns(hisifd->vsync_ctrl.vsync_timestamp), secure_ctrl->secure_event);
		buf[strlen(buf) + 1] = '\0';
		if (secure_ctrl->secure_event == DSS_SEC_DISABLE) {
			secure_ctrl->tui_need_switch = 0;
		}

	} else if (vsync_flag) {
		ret = snprintf(buf, PAGE_SIZE, "VSYNC=%llu, xxxxxxevent=x \n",
			ktime_to_ns(hisifd->vsync_ctrl.vsync_timestamp));
		buf[strlen(buf) + 1] = '\0';
		secure_ctrl->tui_need_skip_report = 0;

	} else if (secure_flag && !secure_ctrl->tui_need_skip_report) {
		HISI_FB_INFO("report (secure_event = %d) to hwc at (frame_no = %d).\n", \
						secure_ctrl->secure_event, hisifd->ov_req.frame_no);

		ret = snprintf(buf, PAGE_SIZE, "xxxxx=%llu, SecureEvent=%d \n",
			ktime_to_ns(hisifd->vsync_ctrl.vsync_timestamp), secure_ctrl->secure_event);
		buf[strlen(buf) + 1] = '\0';
		secure_ctrl->tui_need_skip_report = 1;
		if (secure_ctrl->secure_event == DSS_SEC_DISABLE) {
			secure_ctrl->tui_need_switch = 0;
		}

	} else {
		;//do nothing
	}

	return ret;
}

static ssize_t vsync_timestamp_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	ssize_t ret = 0;
	struct fb_info *fbi = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Pointer.\n");
		return 0;
	}

	fbi = dev_get_drvdata(dev);
	if (NULL == fbi) {
		HISI_FB_ERR("NULL Pointer.\n");
		return 0;
	}

	hisifd = (struct hisi_fb_data_type *)fbi->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer.\n");
		return 0;
	}

	if (NULL == buf) {
		HISI_FB_ERR("NULL Pointer.\n");
		return 0;
	}

	ret = snprintf(buf, PAGE_SIZE, "%llu \n",
		ktime_to_ns(hisifd->vsync_ctrl.vsync_timestamp));
	buf[strlen(buf) + 1] = '\0';

	return ret;
}

static DEVICE_ATTR(vsync_event, S_IRUGO, vsync_show_event, NULL);
static DEVICE_ATTR(vsync_timestamp, S_IRUGO, vsync_timestamp_show, NULL);
#endif

#ifdef CONFIG_FAKE_VSYNC_USED
enum hrtimer_restart hisifb_fake_vsync(struct hrtimer *timer)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int fps = 60;

	hisifd = container_of(timer, struct hisi_fb_data_type, fake_vsync_hrtimer);
	BUG_ON(hisifd == NULL);

	if (!hisifd->panel_power_on)
		goto error;

	if (hisifd->fake_vsync_used && hisifd->vsync_ctrl.vsync_enabled) {
		hisifd->vsync_ctrl.vsync_timestamp = ktime_get();
		wake_up_interruptible_all(&hisifd->vsync_ctrl.vsync_wait);
	}

error:
	hrtimer_start(&hisifd->fake_vsync_hrtimer,
		ktime_set(0, NSEC_PER_SEC / fps), HRTIMER_MODE_REL);

	return HRTIMER_NORESTART;
}
#endif

static void hisifb_vsync_ctrl_workqueue_handler(struct work_struct *work)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_vsync *vsync_ctrl = NULL;
	struct hisi_fb_panel_data *pdata = NULL;
	unsigned long flags = 0;

	vsync_ctrl = container_of(work, typeof(*vsync_ctrl), vsync_ctrl_work);
	BUG_ON(vsync_ctrl == NULL);
	hisifd = vsync_ctrl->hisifd;
	BUG_ON(hisifd == NULL);
	pdata = dev_get_platdata(&hisifd->pdev->dev);
	BUG_ON(pdata == NULL);

	down(&(hisifd->blank_sem));

	if (!hisifd->panel_power_on) {
		HISI_FB_INFO("fb%d, panel is power off!", hisifd->index);
		up(&(hisifd->blank_sem));
		return;
	}

	mutex_lock(&(vsync_ctrl->vsync_lock));
	if (vsync_ctrl->vsync_ctrl_disabled_set &&
		(vsync_ctrl->vsync_ctrl_expire_count == 0) &&
		vsync_ctrl->vsync_ctrl_enabled &&
		!vsync_ctrl->vsync_enabled && !vsync_ctrl->vsync_ctrl_offline_enabled) {
		HISI_FB_DEBUG("fb%d, dss clk off!\n", hisifd->index);

		spin_lock_irqsave(&(vsync_ctrl->spin_lock), flags);
		if (pdata->vsync_ctrl) {
			pdata->vsync_ctrl(hisifd->pdev, 0);
		} else {
			HISI_FB_ERR("fb%d, vsync_ctrl not supported!\n", hisifd->index);
		}
		vsync_ctrl->vsync_ctrl_enabled = 0;
		vsync_ctrl->vsync_ctrl_disabled_set = 0;
		spin_unlock_irqrestore(&(vsync_ctrl->spin_lock), flags);

		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_MIPI_ULPS) {
			mipi_dsi_ulps_cfg(hisifd, 0);
		}

		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_VCC_OFF) {
			if (hisifd->lp_fnc)
				hisifd->lp_fnc(hisifd, true);
		}

		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_CLK_OFF) {
			dpe_inner_clk_disable(hisifd);
			dpe_common_clk_disable(hisifd);
			mipi_dsi_clk_disable(hisifd);
		}

		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_VCC_OFF) {
			dpe_regulator_disable(hisifd);
		}
	}
	mutex_unlock(&(vsync_ctrl->vsync_lock));

	if (vsync_ctrl->vsync_report_fnc) {
		vsync_ctrl->vsync_report_fnc(1);
	}

	up(&(hisifd->blank_sem));
}

void hisifb_vsync_register(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_vsync *vsync_ctrl = NULL;
#if defined(CONFIG_HISI_FB_VSYNC_THREAD)
	char name[64] = {0};
#endif

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	vsync_ctrl = &(hisifd->vsync_ctrl);
	BUG_ON(vsync_ctrl == NULL);

	if (vsync_ctrl->vsync_created)
		return;

	vsync_ctrl->hisifd = hisifd;
	vsync_ctrl->vsync_infinite = 0;
	vsync_ctrl->vsync_enabled = 0;
	vsync_ctrl->vsync_ctrl_offline_enabled = 0;
	vsync_ctrl->vsync_timestamp = ktime_get();
	init_waitqueue_head(&(vsync_ctrl->vsync_wait));
	spin_lock_init(&(vsync_ctrl->spin_lock));
	INIT_WORK(&vsync_ctrl->vsync_ctrl_work, hisifb_vsync_ctrl_workqueue_handler);

	mutex_init(&(vsync_ctrl->vsync_lock));

	atomic_set(&(vsync_ctrl->buffer_updated), 1);
#ifdef CONFIG_REPORT_VSYNC
	vsync_ctrl->vsync_report_fnc = mali_kbase_pm_report_vsync;
#else
	vsync_ctrl->vsync_report_fnc = NULL;
#endif

#ifdef CONFIG_FAKE_VSYNC_USED
	/* hrtimer for fake vsync timing */
	hisifd->fake_vsync_used = false;
	hrtimer_init(&hisifd->fake_vsync_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hisifd->fake_vsync_hrtimer.function = hisifb_fake_vsync;
	hrtimer_start(&hisifd->fake_vsync_hrtimer,
		ktime_set(0, NSEC_PER_SEC / 60), HRTIMER_MODE_REL);
#endif

#if defined(CONFIG_HISI_FB_VSYNC_THREAD)
	snprintf(name, sizeof(name), "hisifb%d_vsync", hisifd->index);
	vsync_ctrl->vsync_thread = kthread_run(wait_for_vsync_thread, hisifd, name);
	if (IS_ERR(vsync_ctrl->vsync_thread)) {
		vsync_ctrl->vsync_thread = NULL;
		HISI_FB_ERR("failed to run vsync thread!\n");
		return;
	}
#else
	if (hisifd->sysfs_attrs_append_fnc) {
		hisifd->sysfs_attrs_append_fnc(hisifd, &dev_attr_vsync_event.attr);
		hisifd->sysfs_attrs_append_fnc(hisifd, &dev_attr_vsync_timestamp.attr);
	}
#endif

	vsync_ctrl->vsync_created = 1;
}

void hisifb_vsync_unregister(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_vsync *vsync_ctrl = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	vsync_ctrl = &(hisifd->vsync_ctrl);
	BUG_ON(vsync_ctrl == NULL);

	if (!vsync_ctrl->vsync_created)
		return;

#ifdef CONFIG_FAKE_VSYNC_USED
	hisifd->fake_vsync_used = false;
	hrtimer_cancel(&hisifd->fake_vsync_hrtimer);
#endif

#if defined(CONFIG_HISI_FB_VSYNC_THREAD)
	if (vsync_ctrl->vsync_thread)
		kthread_stop(vsync_ctrl->vsync_thread);
#endif

	vsync_ctrl->vsync_created = 0;
}

void hisifb_set_vsync_activate_state(struct hisi_fb_data_type *hisifd, bool infinite)
{
	struct hisifb_vsync *vsync_ctrl = NULL;

	BUG_ON(hisifd == NULL);
	vsync_ctrl = &(hisifd->vsync_ctrl);
	BUG_ON(vsync_ctrl == NULL);

	if (hisifd->panel_info.vsync_ctrl_type == VSYNC_CTRL_NONE)
		return;

	mutex_lock(&(vsync_ctrl->vsync_lock));

	if (infinite) {
		vsync_ctrl->vsync_infinite_count += 1;
	} else {
		vsync_ctrl->vsync_infinite_count -= 1;
	}

	if (vsync_ctrl->vsync_infinite_count >= 1) {
		vsync_ctrl->vsync_infinite = 1;
	}

	if (vsync_ctrl->vsync_infinite_count == 0) {
		vsync_ctrl->vsync_infinite = 0;
	}

	mutex_unlock(&(vsync_ctrl->vsync_lock));
}

void hisifb_activate_vsync(struct hisi_fb_data_type *hisifd)
{
	struct hisi_fb_panel_data *pdata = NULL;
	struct hisifb_vsync *vsync_ctrl = NULL;
	unsigned long flags = 0;
	int clk_enabled = 0;

	BUG_ON(hisifd == NULL);
	pdata = dev_get_platdata(&hisifd->pdev->dev);
	BUG_ON(pdata == NULL);
	vsync_ctrl = &(hisifd->vsync_ctrl);
	BUG_ON(vsync_ctrl == NULL);

	if (hisifd->panel_info.vsync_ctrl_type == VSYNC_CTRL_NONE)
		return;

	mutex_lock(&(vsync_ctrl->vsync_lock));

	if (vsync_ctrl->vsync_ctrl_enabled == 0) {
		HISI_FB_DEBUG("fb%d, dss clk on!\n", hisifd->index);

		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_VCC_OFF) {
			dpe_regulator_enable(hisifd);
		}

		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_CLK_OFF) {
			mipi_dsi_clk_enable(hisifd);
			dpe_common_clk_enable(hisifd);
			dpe_inner_clk_enable(hisifd);
		}

		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_VCC_OFF) {
			if (hisifd->lp_fnc)
				hisifd->lp_fnc(hisifd, false);
		}

		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_MIPI_ULPS) {
			mipi_dsi_ulps_cfg(hisifd, 1);
		}

		vsync_ctrl->vsync_ctrl_enabled = 1;
		clk_enabled = 1;
	} else if (vsync_ctrl->vsync_ctrl_isr_enabled) {
		clk_enabled = 1;
		vsync_ctrl->vsync_ctrl_isr_enabled = 0;
	} else {
		;
	}

	spin_lock_irqsave(&(vsync_ctrl->spin_lock), flags);
	vsync_ctrl->vsync_ctrl_disabled_set = 0;
	vsync_ctrl->vsync_ctrl_expire_count = 0;

	if (clk_enabled) {
		if (pdata->vsync_ctrl) {
			pdata->vsync_ctrl(hisifd->pdev, 1);
		} else {
			HISI_FB_ERR("fb%d, vsync_ctrl not supported!\n", hisifd->index);
		}
	}
	spin_unlock_irqrestore(&(vsync_ctrl->spin_lock), flags);

	mutex_unlock(&(vsync_ctrl->vsync_lock));
}

void hisifb_deactivate_vsync(struct hisi_fb_data_type *hisifd)
{
	struct hisi_fb_panel_data *pdata = NULL;
	struct hisifb_vsync *vsync_ctrl = NULL;
	unsigned long flags = 0;

	BUG_ON(hisifd == NULL);
	pdata = dev_get_platdata(&hisifd->pdev->dev);
	BUG_ON(pdata == NULL);
	vsync_ctrl = &(hisifd->vsync_ctrl);
	BUG_ON(vsync_ctrl == NULL);

	if (hisifd->panel_info.vsync_ctrl_type == VSYNC_CTRL_NONE)
		return;

	if (hisifd->secure_ctrl.secure_event == DSS_SEC_ENABLE) {
		return;
	}

	mutex_lock(&(vsync_ctrl->vsync_lock));

	spin_lock_irqsave(&(vsync_ctrl->spin_lock), flags);
	if (vsync_ctrl->vsync_infinite == 0)
		vsync_ctrl->vsync_ctrl_disabled_set = 1;

	if (vsync_ctrl->vsync_ctrl_enabled)
		vsync_ctrl->vsync_ctrl_expire_count = VSYNC_CTRL_EXPIRE_COUNT;
	spin_unlock_irqrestore(&(vsync_ctrl->spin_lock), flags);

	mutex_unlock(&(vsync_ctrl->vsync_lock));
}

int hisifb_vsync_ctrl(struct fb_info *info, void __user *argp)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_fb_panel_data *pdata = NULL;
	struct hisifb_vsync *vsync_ctrl = NULL;
	int enable = 0;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	pdata = dev_get_platdata(&hisifd->pdev->dev);
	if (NULL == pdata) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	vsync_ctrl = &(hisifd->vsync_ctrl);
	if (NULL == vsync_ctrl) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	ret = copy_from_user(&enable, argp, sizeof(enable));
	if (ret) {
		HISI_FB_ERR("hisifb_vsync_ctrl ioctl failed!\n");
		return ret;
	}

	enable = (enable) ? 1 : 0;

	mutex_lock(&(vsync_ctrl->vsync_lock));

	if (vsync_ctrl->vsync_enabled == enable) {
		mutex_unlock(&(vsync_ctrl->vsync_lock));
		return 0;
	}

	if (g_debug_online_vsync)
		HISI_FB_INFO("fb%d, enable=%d!\n", hisifd->index, enable);

	vsync_ctrl->vsync_enabled = enable;

	mutex_unlock(&(vsync_ctrl->vsync_lock));

	down(&hisifd->blank_sem);

	if (!hisifd->panel_power_on) {
		HISI_FB_INFO("fb%d, panel is power off!", hisifd->index);
		up(&hisifd->blank_sem);
		return 0;
	}

	if (enable) {
		hisifb_activate_vsync(hisifd);
	} else {
		hisifb_deactivate_vsync(hisifd);
	}

	up(&hisifd->blank_sem);

	return 0;
}

int hisifb_vsync_resume(struct hisi_fb_data_type *hisifd)
{
	struct hisifb_vsync *vsync_ctrl = NULL;

	BUG_ON(hisifd == NULL);
	vsync_ctrl = &(hisifd->vsync_ctrl);
	BUG_ON(vsync_ctrl == NULL);

	vsync_ctrl->vsync_enabled = 0;
	vsync_ctrl->vsync_ctrl_expire_count = 0;
	vsync_ctrl->vsync_ctrl_disabled_set = 0;
	vsync_ctrl->vsync_ctrl_enabled = 1;
	vsync_ctrl->vsync_ctrl_isr_enabled = 1;
	//vsync_ctrl->vsync_infinite = 0;

	atomic_set(&(vsync_ctrl->buffer_updated), 1);

#if 0
	if (hisifd->panel_info.vsync_ctrl_type != VSYNC_CTRL_NONE) {
		if ((hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_MIPI_ULPS) ||
			(hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_CLK_OFF) ||
			(hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_VCC_OFF)) {

			if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_MIPI_ULPS) {
				mipi_dsi_ulps_cfg(hisifd, 0);
			}

			if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_CLK_OFF) {
				dpe_inner_clk_disable(hisifd);
				dpe_common_clk_disable(hisifd);
				mipi_dsi_clk_disable(hisifd);
			}

			if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_VCC_OFF) {
				dpe_regulator_disable(hisifd);
			}
		}
	}
#endif

	return 0;
}

int hisifb_vsync_suspend(struct hisi_fb_data_type *hisifd)
{
	return 0;
}
#pragma GCC diagnostic pop
