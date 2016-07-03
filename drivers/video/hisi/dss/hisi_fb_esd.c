/* Copyright (c) 2013-2016, Hisilicon Tech. Co., Ltd. All rights reserved.
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

#include "hisi_fb.h"

#define HISI_ESD_RECOVER_MAX_COUNT   (5)
#define HISI_ESD_CHECK_MAX_COUNT     (3)

#if defined (CONFIG_HUAWEI_DSM)
int dsm_lcd_esd_recover = -1;
#endif
static int hisifb_esd_handle_thread(void *data)
{
	struct hisi_fb_data_type *hisifd = (struct hisi_fb_data_type *)data;
	uint32_t old_esd_status = 0;
	int ret = 0;

	while (!kthread_should_stop()) {
		ret = wait_event_interruptible(hisifd->esd_ctrl.esd_handle_wait, (hisifd->esd_happened != old_esd_status));
		if (!ret && (hisifd->esd_happened == 1)) {
			char *envp[2];
			char buf[64];
			snprintf(buf, sizeof(buf), "ESD_HAPPENDED=1");
			envp[0] = buf;
			envp[1] = NULL;
			kobject_uevent_env(&(hisifd->fbi->dev->kobj), KOBJ_CHANGE, envp);

			HISI_FB_INFO("ESD_HAPPENDED=1!\n");
		}
		old_esd_status = hisifd->esd_happened;
	}
	return 0;
}

static void hisifb_esd_recover(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;
	uint32_t bl_level_cur = 0;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null");
		return ;
	}

	down(&hisifd->blank_sem);
	if (!hisifd->panel_power_on) {
		HISI_FB_ERR("panel is off\n");
		up(&hisifd->blank_sem);
		return ;
	}
	down(&hisifd->brightness_esd_sem);
	bl_level_cur = hisifd->bl_level;
	hisifb_set_backlight(hisifd, 0);
	up(&hisifd->brightness_esd_sem);

	hisifb_activate_vsync(hisifd);
	/*lcd panel off*/
	ret = panel_next_off(hisifd->pdev);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, blank_mode(%d) failed!\n", hisifd->index, FB_BLANK_POWERDOWN);
	}
	/*lcd panel on*/
	ret = panel_next_on(hisifd->pdev);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, blank_mode(%d) failed!\n", hisifd->index, FB_BLANK_UNBLANK);
	}
	/*cmd panel need to update frame*/
	if (is_mipi_cmd_panel(hisifd)) {
		single_frame_update(hisifd);
	}
	hisifb_deactivate_vsync(hisifd);

	/*backlight on*/
	mdelay(100);
	down(&hisifd->brightness_esd_sem);
	hisifb_set_backlight(hisifd, bl_level_cur);
	up(&hisifd->brightness_esd_sem);
	up(&hisifd->blank_sem);

	return ;
}

static void hisifb_esd_check_wq_handler(struct work_struct *work)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_esd *esd_ctrl = NULL;
	int ret = 0;
	int recover_count = 0;
	int esd_check_count = 0;

	esd_ctrl = container_of(work, struct hisifb_esd, esd_check_work);
	BUG_ON(esd_ctrl == NULL);
	hisifd = esd_ctrl->hisifd;
	BUG_ON(hisifd == NULL);

	if (!hisifd->panel_info.esd_enable)
		return ;

	while (recover_count < HISI_ESD_RECOVER_MAX_COUNT) {
		if (esd_check_count < HISI_ESD_CHECK_MAX_COUNT) {
			if (DSS_SEC_RUNNING == hisifd->secure_ctrl.secure_status)
				break;

			if ((DSS_SEC_IDLE == hisifd->secure_ctrl.secure_status)
				&& (DSS_SEC_ENABLE == hisifd->secure_ctrl.secure_event))
				break;

			ret = hisifb_ctrl_esd(hisifd);
			if (ret) {
				esd_check_count++;
				hisifd->esd_happened = 1;
				if (hisifd->panel_info.dirty_region_updt_support) {
					wake_up_interruptible_all(&(esd_ctrl->esd_handle_wait));
				}
				HISI_FB_INFO("esd check abnormal, esd_check_count:%d!\n", esd_check_count);
			} else {
				hisifd->esd_happened = 0;
				if (hisifd->panel_info.dirty_region_updt_support) {
					wake_up_interruptible_all(&(esd_ctrl->esd_handle_wait));
				}
				break;
			}
		} else {
			HISI_FB_ERR("esd recover panel, recover_count:%d!\n",recover_count);
			hisifb_esd_recover(hisifd);
			esd_check_count = 0;
			recover_count++;
		#if 0
		#if defined (CONFIG_HUAWEI_DSM)
			if (dsm_lcd_esd_recover >= 0) {
				dsm_client_record(lcd_dclient,"[%s]ESD recovery count: %d.\n",
					__func__, recover_count);
				dsm_lcd_esd_recover++;
			}
		#endif
		#endif
		}
	}

	// recover count equate 5, we disable esd check function
	if (recover_count >= HISI_ESD_RECOVER_MAX_COUNT) {
		hrtimer_cancel(&esd_ctrl->esd_hrtimer);
		hisifd->panel_info.esd_enable = 0;
		HISI_FB_ERR("esd recover %d count, disable esd function\n", HISI_ESD_RECOVER_MAX_COUNT);
	}
}

static enum hrtimer_restart hisifb_esd_hrtimer_fnc(struct hrtimer *timer)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_esd *esd_ctrl = NULL;

	esd_ctrl = container_of(timer, struct hisifb_esd, esd_hrtimer);
	BUG_ON(esd_ctrl == NULL);
	hisifd = esd_ctrl->hisifd;
	BUG_ON(hisifd == NULL);

	if (hisifd->panel_info.esd_enable) {
		if (esd_ctrl->esd_check_wq) {
			queue_work(esd_ctrl->esd_check_wq, &(esd_ctrl->esd_check_work));
		}
	}
	hrtimer_start(&esd_ctrl->esd_hrtimer, ktime_set(ESD_CHECK_TIME_PERIOD / 1000,
		(ESD_CHECK_TIME_PERIOD % 1000) * 1000000), HRTIMER_MODE_REL);

	return HRTIMER_NORESTART;
}

#ifdef CONFIG_HUAWEI_OCP
#include <huawei_platform/ocp/hw_ocp_ext.h>
int hisi_lcd_ocp_recover(struct notifier_block *nb,
		unsigned long event, void *data)
{
	int ret = 0;
	unsigned int lcd_is_recover = 0;

	struct hisi_fb_data_type *hisifd = hisifd_list[PRIMARY_PANEL_IDX];

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null");
		return -1;
	}

	if (event == HW_OCP_LCD_EVENT && g_fastboot_already_set) {
		lcd_is_recover = *(unsigned int*)data;
		if (!lcd_is_recover) {
			down(&hisifd->blank_sem);
			if (!hisifd->panel_power_on) {
				HISI_FB_ERR("panel is off\n");
				up(&hisifd->blank_sem);
				return -1;
			}
			hisifb_activate_vsync(hisifd);
			/*lcd panel off*/
			ret = panel_next_off(hisifd->pdev);
			if (ret != 0) {
				HISI_FB_ERR("fb%d, blank_mode(%d) failed!\n", hisifd->index, FB_BLANK_POWERDOWN);
			}
			/*close esd check*/
			if (hisifd->panel_info.esd_enable) {
				hrtimer_cancel(&hisifd->esd_ctrl.esd_hrtimer);
				hisifd->panel_info.esd_enable = 0;
			}
			hisifb_deactivate_vsync(hisifd);
			up(&hisifd->blank_sem);
		} else {
			hisifb_esd_recover(hisifd);
		}
#if defined (CONFIG_HUAWEI_DSM)
		if (!dsm_client_ocuppy(lcd_dclient)) {
			dsm_client_record(lcd_dclient, "lcd happen ocp.\n");
			dsm_client_notify(lcd_dclient, DSM_LCD_ESD_OCP_RECOVERY_NO);
		}
#endif

	}

	return ret;
}
#endif

void hisifb_esd_register(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_esd *esd_ctrl = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	esd_ctrl = &(hisifd->esd_ctrl);
	BUG_ON(esd_ctrl == NULL);

	if (esd_ctrl->esd_inited) {
		return;
	}

	if (hisifd->panel_info.esd_enable) {
		hisifd->esd_happened = 0;
		esd_ctrl->hisifd = hisifd;

		esd_ctrl->esd_check_wq = create_singlethread_workqueue("esd_check");
		if (!esd_ctrl->esd_check_wq) {
			HISI_FB_ERR("create esd_check_wq failed\n");
		}

		INIT_WORK(&esd_ctrl->esd_check_work, hisifb_esd_check_wq_handler);

		/* hrtimer for ESD timing */
		hrtimer_init(&esd_ctrl->esd_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		esd_ctrl->esd_hrtimer.function = hisifb_esd_hrtimer_fnc;
		hrtimer_start(&esd_ctrl->esd_hrtimer, ktime_set(ESD_CHECK_TIME_PERIOD / 1000,
			(ESD_CHECK_TIME_PERIOD % 1000) * 1000000), HRTIMER_MODE_REL);

		if (hisifd->panel_info.dirty_region_updt_support) {
			init_waitqueue_head(&(esd_ctrl->esd_handle_wait));
			esd_ctrl->esd_handle_thread = kthread_run(hisifb_esd_handle_thread, hisifd, "esd_handle");
			if (IS_ERR(esd_ctrl->esd_handle_thread)) {
				esd_ctrl->esd_handle_thread = NULL;
				HISI_FB_ERR("failed to run esd recover thread!\n");
			}
		}
		esd_ctrl->esd_inited = 1;
	}
}

void hisifb_esd_unregister(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_esd *esd_ctrl = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	esd_ctrl = &(hisifd->esd_ctrl);
	BUG_ON(esd_ctrl == NULL);

	if (!esd_ctrl->esd_inited)
		return;

	if (hisifd->panel_info.esd_enable) {
		hrtimer_cancel(&esd_ctrl->esd_hrtimer);

		if (esd_ctrl->esd_handle_thread) {
			kthread_stop(esd_ctrl->esd_handle_thread);
		}
	}

	esd_ctrl->esd_inited = 0;
}
