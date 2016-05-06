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

#include "hisi_fb.h"

#define K3_DSS_SBL_WORKQUEUE	"k3_dss_sbl_workqueue"

static int lcd_backlight_registered;
static unsigned int is_recovery_mode;
static int is_no_fastboot_bl_enable;

#ifdef CONFIG_HISI_FB_BACKLIGHT_DELAY
unsigned long backlight_duration = (3 * HZ / 60);
#endif

extern unsigned int get_boot_into_recovery_flag(void);

void hisifb_set_backlight(struct hisi_fb_data_type *hisifd, uint32_t bkl_lvl)
{
	struct hisi_fb_panel_data *pdata = NULL;
	uint32_t temp = bkl_lvl;

	BUG_ON(hisifd == NULL);
	pdata = dev_get_platdata(&hisifd->pdev->dev);
	BUG_ON(pdata == NULL);

	if (!hisifd->panel_power_on || !hisifd->backlight.bl_updated) {
		hisifd->bl_level = bkl_lvl;
		return;
	}

	if (pdata->set_backlight) {
		if (hisifd->backlight.bl_level_old == temp) {
			hisifd->bl_level = bkl_lvl;
			return;
		}
		if (hisifd->backlight.bl_level_old == 0) {
			HISI_FB_INFO("backlight level = %d", bkl_lvl);
		}
		hisifd->bl_level = bkl_lvl;
		if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
			hisifb_set_vsync_activate_state(hisifd, true);
			hisifb_activate_vsync(hisifd);
		}
		pdata->set_backlight(hisifd->pdev, bkl_lvl);
		if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
			hisifb_set_vsync_activate_state(hisifd, false);
			hisifb_deactivate_vsync(hisifd);
		}
		hisifd->backlight.bl_level_old = temp;
	}
}

#ifdef CONFIG_HISI_FB_BACKLIGHT_DELAY
static void hisifb_bl_workqueue_handler(struct work_struct *work)
#else
static void hisifb_bl_workqueue_handler(struct hisi_fb_data_type *hisifd)
#endif
{
	struct hisi_fb_panel_data *pdata = NULL;
#ifdef CONFIG_HISI_FB_BACKLIGHT_DELAY
	struct hisifb_backlight *pbacklight = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	pbacklight = container_of(to_delayed_work(work), struct hisifb_backlight, bl_worker);
	BUG_ON(pbacklight == NULL);

	hisifd = container_of(pbacklight, struct hisi_fb_data_type, backlight);
#endif

	BUG_ON(hisifd == NULL);
	pdata = dev_get_platdata(&hisifd->pdev->dev);
	BUG_ON(pdata == NULL);

	if (!hisifd->backlight.bl_updated) {
		down(&hisifd->blank_sem);

		if (hisifd->backlight.frame_updated == 0) {
			up(&hisifd->blank_sem);
			return;
		}

		hisifd->backlight.frame_updated = 0;
		hisifd->backlight.bl_updated = 1;
		if (is_recovery_mode) {
			hisifd->bl_level = hisifd->panel_info.bl_default;
		} else {
			if (!is_fastboot_display_enable() && !is_no_fastboot_bl_enable) {
				is_no_fastboot_bl_enable = 1;
				hisifd->bl_level = hisifd->panel_info.bl_default;
			}
		}

		hisifb_set_backlight(hisifd, hisifd->bl_level);
		up(&hisifd->blank_sem);
	}
}

void hisifb_backlight_update(struct hisi_fb_data_type *hisifd)
{
	struct hisi_fb_panel_data *pdata = NULL;

	BUG_ON(hisifd == NULL);
	pdata = dev_get_platdata(&hisifd->pdev->dev);
	BUG_ON(pdata == NULL);

	if (!hisifd->backlight.bl_updated) {
		hisifd->backlight.frame_updated = 1;
	#ifdef CONFIG_HISI_FB_BACKLIGHT_DELAY
		schedule_delayed_work(&hisifd->backlight.bl_worker,
			backlight_duration);
	#else
		hisifb_bl_workqueue_handler(hisifd);
	#endif
	}
}

void hisifb_backlight_cancel(struct hisi_fb_data_type *hisifd)
{
	struct hisi_fb_panel_data *pdata = NULL;

	BUG_ON(hisifd == NULL);
	pdata = dev_get_platdata(&hisifd->pdev->dev);
	BUG_ON(pdata == NULL);

#ifdef CONFIG_HISI_FB_BACKLIGHT_DELAY
	cancel_delayed_work(&hisifd->backlight.bl_worker);
#endif
	hisifd->backlight.bl_updated = 0;
	hisifd->backlight.bl_level_old = 0;
	hisifd->backlight.frame_updated = 0;

	if (pdata->set_backlight) {
		hisifd->bl_level = 0;
		if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI)
			hisifb_activate_vsync(hisifd);
		pdata->set_backlight(hisifd->pdev, hisifd->bl_level);
		if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI)
			hisifb_deactivate_vsync(hisifd);
	}
}

#ifdef CONFIG_FB_BACKLIGHT
static int hisi_fb_bl_get_brightness(struct backlight_device *pbd)
{
	if (NULL == pbd) {
		HISI_FB_ERR("NULL pointer!\n");
		return 0;
	}
	return pbd->props.brightness;
}

static int hisi_fb_bl_update_status(struct backlight_device *pbd)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t bl_lvl = 0;

	if (NULL == pbd) {
		HISI_FB_ERR("NULL pointer!\n");
		return 0;
	}

	hisifd = bl_get_data(pbd);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL pointer!\n");
		return 0;
	}

	bl_lvl = pbd->props.brightness;
	bl_lvl = hisifd->fbi->bl_curve[bl_lvl];

	down(&hisifd->blank_sem);
	hisifb_set_backlight(hisifd, bl_lvl);
	up(&hisifd->blank_sem);

	return 0;
}

static struct backlight_ops hisi_fb_bl_ops = {
	.get_brightness = hisi_fb_bl_get_brightness,
	.update_status = hisi_fb_bl_update_status,
};
#else
static void hisi_fb_set_bl_brightness(struct led_classdev *led_cdev,
	enum led_brightness value)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int bl_lvl = 0;

	if (NULL == led_cdev) {
		HISI_FB_ERR("NULL pointer!\n");
		return;
	}

	hisifd = dev_get_drvdata(led_cdev->dev->parent);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL pointer!\n");
		return;
	}

	if (value < 0)
		value = 0;

	if (value > hisifd->panel_info.bl_max)
		value = hisifd->panel_info.bl_max;

	/* This maps android backlight level 0 to 255 into
	   driver backlight level 0 to bl_max with rounding */
	bl_lvl = (2 * value * hisifd->panel_info.bl_max + hisifd->panel_info.bl_max)
		/(2 * hisifd->panel_info.bl_max);
	if (!bl_lvl && value)
		bl_lvl = 1;
	down(&hisifd->brightness_esd_sem);
	hisifb_set_backlight(hisifd, bl_lvl);
	up(&hisifd->brightness_esd_sem);
}

static struct led_classdev backlight_led = {
	.name = DEV_NAME_LCD_BKL,
	.brightness_set = hisi_fb_set_bl_brightness,
};
#endif

#ifdef CONFIG_HISI_FB_3660
static void hisifb_sbl_work(struct work_struct *work)
{
}

#else
static void hisifb_sbl_work(struct work_struct *work)
{
	struct hisifb_backlight *pbacklight = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	char __iomem *sbl_base = NULL;
	uint32_t bkl_from_AD = 0;

	pbacklight = container_of(work, struct hisifb_backlight, sbl_work);
	BUG_ON(pbacklight == NULL);
	hisifd = container_of(pbacklight, struct hisi_fb_data_type, backlight);
	BUG_ON(hisifd == NULL);

	down(&hisifd->blank_sem);

	if (!hisifd->panel_power_on) {
		up(&hisifd->blank_sem);
		return;
	}

	sbl_base = hisifd->dss_base + DSS_DPP_SBL_OFFSET;
	bkl_from_AD = (inp32(sbl_base + SBL_BACKLIGHT_OUT_H) << 8)
		| inp32(sbl_base + SBL_BACKLIGHT_OUT_L);
	bkl_from_AD = (bkl_from_AD * 255) / 0xffff;
	hisifb_set_backlight(hisifd, bkl_from_AD);

	up(&hisifd->blank_sem);
}
#endif
void hisifb_sbl_isr_handler(struct hisi_fb_data_type *hisifd)
{
	BUG_ON(hisifd == NULL);

	if ((hisifd->sbl_enable == 0) || (hisifd->panel_info.sbl_support == 0)) {
		return;
	}

	if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_SBL)) {
		return;
	}

	queue_work(hisifd->backlight.sbl_queue, &(hisifd->backlight.sbl_work));
}

void hisifb_backlight_register(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
#ifdef CONFIG_FB_BACKLIGHT
	struct backlight_device *pbd = NULL;
	struct fb_info *fbi = NULL;
	char name[16] = {0};
	struct backlight_properties props;
#endif

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	hisifd->backlight.bl_updated = 0;
	hisifd->backlight.frame_updated = 0;
	hisifd->backlight.bl_level_old = 0;
	sema_init(&hisifd->backlight.bl_sem, 1);
#ifdef CONFIG_HISI_FB_BACKLIGHT_DELAY
	INIT_DELAYED_WORK(&hisifd->backlight.bl_worker, hisifb_bl_workqueue_handler);
#endif

	if (lcd_backlight_registered)
		return;

	is_recovery_mode = get_boot_into_recovery_flag();

#ifdef CONFIG_FB_BACKLIGHT
	fbi = hisifd->fbi;

	snprintf(name, sizeof(name), "hisifb%d_bl", hisifd->index);
	props.max_brightness = FB_BACKLIGHT_LEVELS - 1;
	props.brightness = FB_BACKLIGHT_LEVELS - 1;
	pbd = backlight_device_register(name, fbi->dev, hisifd,
		&hisi_fb_bl_ops, &props);
	if (IS_ERR(pbd)) {
		fbi->bl_dev = NULL;
		HISI_FB_ERR("backlight_device_register failed!\n");
	}

	fbi->bl_dev = pbd;
	fb_bl_default_curve(fbi, 0,
		hisifd->panel_info.bl_min, hisifd->panel_info.bl_max);
#else
	backlight_led.brightness = hisifd->panel_info.bl_default;
	backlight_led.max_brightness = hisifd->panel_info.bl_max;
	/* android supports only one lcd-backlight/lcd for now */
	if (led_classdev_register(&pdev->dev, &backlight_led)) {
		HISI_FB_ERR("led_classdev_register failed!\n");
		return;
	}
#endif

	//support sbl
	if (HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_SBL)) {
		INIT_WORK(&(hisifd->backlight.sbl_work), hisifb_sbl_work);
		hisifd->backlight.sbl_queue = create_singlethread_workqueue(K3_DSS_SBL_WORKQUEUE);
		if (!hisifd->backlight.sbl_queue) {
			HISI_FB_ERR("failed to create sbl_queue!\n");
			return ;
		}
	}

	lcd_backlight_registered = 1;
}

void hisifb_backlight_unregister(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	if (lcd_backlight_registered) {
		lcd_backlight_registered = 0;
	#ifdef CONFIG_FB_BACKLIGHT
		/* remove /sys/class/backlight */
		backlight_device_unregister(hisifd->fbi->bl_dev);
	#else
		led_classdev_unregister(&backlight_led);
	#endif

		if (hisifd->backlight.sbl_queue) {
			destroy_workqueue(hisifd->backlight.sbl_queue);
			hisifd->backlight.sbl_queue = NULL;
		}
	}
}
