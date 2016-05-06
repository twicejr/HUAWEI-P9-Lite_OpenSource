/* Copyright (c) 2014-2015, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#include "hisi_fb.h"

static void hisifb_secure_ctrl_wq_handler(struct work_struct *work)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_secure *secure_ctrl = NULL;
	secure_ctrl = container_of(work, typeof(*secure_ctrl), secure_ctrl_work);
	BUG_ON(secure_ctrl == NULL);
	hisifd = secure_ctrl->hisifd;
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG(": secure_ctrl->secure_status = %d, secure_ctrl->secure_event = %d, frame_no = %d +++ \n",\
			secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no);

	if ((DSS_SEC_IDLE == secure_ctrl->secure_status)
			&& (DSS_SEC_ENABLE == secure_ctrl->secure_event)) {
		secure_ctrl->secure_status = DSS_SEC_RUNNING;
	}

	if ((DSS_SEC_RUNNING == secure_ctrl->secure_status)
			&& (DSS_SEC_ENABLE == secure_ctrl->secure_event)) {
		hisifb_activate_vsync(hisifd);
#if defined (CONFIG_TEE_TUI)
		send_tui_msg_config(TUI_POLL_CFG_OK, 0, "DSS");
#endif
		HISI_FB_INFO("TUI switch to DSS_SEC_RUNNING succ!!!\n");
		secure_ctrl->tui_need_switch = 0;
		mutex_unlock(&(secure_ctrl->secure_lock));
	}

	HISI_FB_DEBUG(": secure_ctrl->secure_status = %d, secure_ctrl->secure_event = %d, frame_no = %d --- \n",\
			secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no);
}

/* receive switch tui request
 **1: secure enable
 **0: secure disable
 */
static int notify_dss_tui_request(void *data, int secure)
{
	int ret = 0;
	struct hisifb_secure *secure_ctrl = NULL;
	struct hisi_fb_data_type *hisifd = NULL;
	int tui_request = secure ? DSS_SEC_ENABLE : DSS_SEC_DISABLE;

	hisifd = (struct hisi_fb_data_type *)data; //hisifd_list[PRIMARY_PANEL_IDX];
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	BUG_ON(secure_ctrl == NULL);

	if (!secure_ctrl->secure_created) {
		HISI_FB_ERR("fb%d, secure is not created yet!\n", hisifd->index);
		return -1;
	}

	mutex_lock(&(secure_ctrl->secure_lock));
	if (!hisifd->panel_power_on) {
		HISI_FB_INFO("fb%d, panel is power off!", hisifd->index);
		mutex_unlock(&(secure_ctrl->secure_lock));
		return -1;
	}
	HISI_FB_INFO("secure_ctrl->secure_status = %d, secure_ctrl->secure_event = %d, frame_no = %d , tui_request = %d +++ \n",\
			secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no, tui_request);

	if (secure_ctrl->secure_status == tui_request) {
		HISI_FB_INFO("secure_status = %d,---!\n", secure_ctrl->secure_status);
		mutex_unlock(&(secure_ctrl->secure_lock));
		return -1;
	}
	secure_ctrl->secure_event = tui_request;

	secure_ctrl->tui_need_switch = 1;
	secure_ctrl->tui_need_skip_report = 0;

	if (DSS_SEC_ENABLE == secure_ctrl->secure_event) {
		hisifd->dss_module_default.mctl_sys.chn_ov_sel[DSS_OVL0] = set_bits32(hisifd->dss_module_default.mctl_sys.chn_ov_sel[DSS_OVL0], TUI_SEC_RCH, 4, 24);
		hisifb_activate_vsync(hisifd);
		wake_up_interruptible_all(&(hisifd->vsync_ctrl.vsync_wait));
	} else {
		hisifd->dss_module_default.mctl_sys.chn_ov_sel[DSS_OVL0] = 0xFFFFFFFF;
		secure_ctrl->secure_status = DSS_SEC_IDLE;
		mutex_unlock(&(secure_ctrl->secure_lock));
		if (secure_ctrl->secure_blank_flag) {
			ret = hisi_fb_blank_sub(FB_BLANK_POWERDOWN, hisifd->fbi);
			if (ret != 0) {
				HISI_FB_ERR("fb%d, blank_mode(%d) failed!\n", hisifd->index, FB_BLANK_POWERDOWN);
			}
			secure_ctrl->secure_blank_flag = 0;
		}
	}

	HISI_FB_INFO("secure_ctrl->secure_status = %d, secure_ctrl->secure_event = %d, frame_no = %d , tui_request = %d --- \n",\
			secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no, tui_request);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
static ssize_t hisifb_secure_event_store(struct device* dev,
		struct device_attribute* attr, const char* buf, size_t count)
{
	int val = 0;
	struct fb_info *fbi = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	fbi = dev_get_drvdata(dev);
	if (NULL == fbi) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	hisifd = (struct hisi_fb_data_type *)fbi->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	val = (int)simple_strtoul(buf, NULL, 0);

	notify_dss_tui_request(hisifd, val);

	return count;
}

static ssize_t hisifb_secure_event_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	ssize_t ret = 0;
	struct fb_info *fbi = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	fbi = dev_get_drvdata(dev);
	if (NULL == fbi) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	hisifd = (struct hisi_fb_data_type *)fbi->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	snprintf(buf, PAGE_SIZE, "SECURE_EVENT=%d, SECURE_STATUS=%d\n",
	        hisifd->secure_ctrl.secure_event, hisifd->secure_ctrl.secure_status);
	ret = strlen(buf) + 1;
	return ret;
}

/*lint -e665*/
static DEVICE_ATTR(dss_secure, S_IRUGO|S_IWUSR, hisifb_secure_event_show, hisifb_secure_event_store);
/*lint -e665*/

/* for DRM config */
static void hisifd_secure_layer_config(struct hisi_fb_data_type *hisifd, dss_layer_t *layer)
{
	struct hisifb_secure *secure_ctrl = NULL;
	dss_module_reg_t *dss_module = NULL;

	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	BUG_ON(secure_ctrl == NULL);
	dss_module = &(hisifd->dss_module);
	HISI_FB_INFO(": ++ chn_idx: %d \n", layer->chn_idx);


	HISI_FB_INFO(": --\n");
}
static void hisifd_secure_layer_deconfig(struct hisi_fb_data_type *hisifd, dss_layer_t *layer)
{
	struct hisifb_secure *secure_ctrl = NULL;
	dss_module_reg_t *dss_module = NULL;
	uint32_t dss_base = 0;
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	BUG_ON(secure_ctrl == NULL);
	dss_module = &(hisifd->dss_module);
	HISI_FB_INFO(": ++ chn_idx: %d \n", layer->chn_idx);
	dss_base = hisifd->dss_base_phy;

	HISI_FB_INFO(": --\n");
}
static void hisifd_notify_secure_switch(struct hisi_fb_data_type *hisifd)
{
	struct hisifb_secure *secure_ctrl = NULL;
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	BUG_ON(secure_ctrl == NULL);

	if (secure_ctrl->secure_status != secure_ctrl->secure_event) {
		if (hisifd->ov_req.sec_enable_status == DSS_SEC_ENABLE) {
			schedule_work(&secure_ctrl->secure_ctrl_work);
		}
	}
}

static void hisifd_secure_set_reg(uint32_t addr, uint32_t val, uint8_t bw, uint8_t bs)
{
#if defined (CONFIG_ATFDRIVER)
	//configure_dss_register_security(addr, val, bw, bs);
#endif
}

void hisifb_secure_register(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_secure *secure_ctrl = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	BUG_ON(secure_ctrl == NULL);

	if (secure_ctrl->secure_created) {
		return;
	}
	secure_ctrl->secure_status = DSS_SEC_IDLE;
	secure_ctrl->secure_event  = DSS_SEC_DISABLE;
	secure_ctrl->secure_blank_flag = 0;
	secure_ctrl->tui_need_switch = 0;

	INIT_WORK(&secure_ctrl->secure_ctrl_work, hisifb_secure_ctrl_wq_handler);
	mutex_init(&(secure_ctrl->secure_lock));

#if defined (CONFIG_TEE_TUI)
	/* register dss tui process function to sw */
	register_tui_driver(notify_dss_tui_request, "DSS", hisifd, 0);
#endif
	secure_ctrl->secure_layer_config = hisifd_secure_layer_config;
	secure_ctrl->secure_layer_deconfig = hisifd_secure_layer_deconfig;
	secure_ctrl->notify_secure_switch = hisifd_notify_secure_switch;
	secure_ctrl->set_reg = hisifd_secure_set_reg;
	secure_ctrl->hisifd = hisifd;

	secure_ctrl->secure_created = 1;

	if (hisifd->sysfs_attrs_append_fnc)
		hisifd->sysfs_attrs_append_fnc(hisifd, &dev_attr_dss_secure.attr);
}

void hisifb_secure_unregister(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_secure *secure_ctrl = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	BUG_ON(secure_ctrl == NULL);

	if (!secure_ctrl->secure_created)
		return;

	secure_ctrl->secure_created = 0;
}
