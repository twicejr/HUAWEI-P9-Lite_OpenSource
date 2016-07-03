 /* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "hisi_display_effect.h"
#include "hisi_fb.h"

static bool g_is_ce_service_init = false;
static spinlock_t g_ce_service_lock;
static ce_service_t g_ce_services[CE_SERVICE_LIMIT];

extern int g_dss_effect_ce_en;

#define ce_service_wait_event(wq, condition)												\
{																							\
	long ret = 0;																			\
	do {																					\
		ret = wait_event_interruptible_timeout(wq, condition, msecs_to_jiffies(100000));	\
	} while(!ret);																			\
	if (ret == -ERESTARTSYS) {																\
		hisifb_ce_service_deinit();															\
	}																						\
}																							\


static inline ce_service_t *get_available_service(ce_service_status status)
{
	int i = 0;
	ce_service_t *service = NULL;

	hisifb_ce_service_init();
	for (i = 0; i < CE_SERVICE_LIMIT; i++) {
		if (g_ce_services[i].status == status) {
			g_ce_services[i].status = (g_ce_services[i].status + 1) % CE_SERVICE_STATUS_COUNT;
			service = &g_ce_services[i];
			break;
		}
	}

	return service;
}

static inline void service_transform_to_next_status(ce_service_t *service)
{
	service->status = (service->status + 1) % CE_SERVICE_STATUS_COUNT;
}

int do_contrast(dss_ce_info_t * info)
{
	if (g_is_ce_service_init) {
		ce_service_t *service = get_available_service(CE_SERVICE_HIST_REQ);

		if (service) {
			service->ce_info = info;
			wake_up_interruptible(&service->wq_hist);
			ce_service_wait_event(service->wq_lut, !service->ce_info || !g_is_ce_service_init);
			if (!g_is_ce_service_init) {
				info->algorithm_result = -1;
			}
		} else {
			info->algorithm_result = -1;
		}
	} else {
		hisifb_ce_service_init();
		info->algorithm_result = -1;
	}

	return info->algorithm_result;
}

void hisi_effect_init(struct hisi_fb_data_type *hisifd)
{
	spin_lock_init(&g_ce_service_lock);
	mutex_init(&(hisifd->ce_ctrl.ctrl_lock));
}

void hisifb_ce_service_init(void)
{
	int i = 0;

	spin_lock(&g_ce_service_lock);
	if (!g_is_ce_service_init) {
		memset(g_ce_services, 0, sizeof(g_ce_services));

		for (i = 0; i < CE_SERVICE_LIMIT; i++) {
			init_waitqueue_head(&g_ce_services[i].wq_hist);
			init_waitqueue_head(&g_ce_services[i].wq_lut);
		}
		g_is_ce_service_init = true;
	}
	spin_unlock(&g_ce_service_lock);
}

void hisifb_ce_service_deinit(void)
{
	int i = 0;

	spin_lock(&g_ce_service_lock);
	if (g_is_ce_service_init) {
		g_is_ce_service_init = false;
		for (i = 0; i < CE_SERVICE_LIMIT; i++) {
			wake_up_interruptible(&g_ce_services[i].wq_hist);
			wake_up_interruptible(&g_ce_services[i].wq_lut);
		}
	}
	spin_unlock(&g_ce_service_lock);
}

int hisifb_ce_service_get_support(struct fb_info *info, void __user *argp)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	unsigned int support = 0;
	int ret = 0;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	pinfo = &(hisifd->panel_info);

	if (pinfo->acm_ce_support || pinfo->prefix_ce_support) {
		support = 1;
	}

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = copy_to_user(argp, &support, sizeof(support));
	if (ret) {
		HISI_FB_ERR("copy_to_user failed! ret=%d.\n", ret);
		return ret;
	}

	return ret;
}

int hisifb_ce_service_get_limit(struct fb_info *info, void __user *argp)
{
	int limit = CE_SERVICE_LIMIT;
	int ret = 0;

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = copy_to_user(argp, &limit, sizeof(limit));
	if (ret) {
		HISI_FB_ERR("copy_to_user failed! ret=%d.\n", ret);
		return ret;
	}

	return ret;
}

int hisifb_ce_service_get_hist(void __user *argp)
{
	ce_parameter_t param;
	ce_service_t *service = get_available_service(CE_SERVICE_IDLE);
	int ret = 0;

	if (service == NULL) {
		HISI_FB_ERR("service is NULL\n");
		return -2;
	}

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = copy_from_user(&param, argp, sizeof(ce_parameter_t));
	if (ret) {
		HISI_FB_ERR("copy_from_user failed! ret=%d.\n", ret);
		return -2;
	}

	ce_service_wait_event(service->wq_hist, service->ce_info || !g_is_ce_service_init);
	if (service->ce_info) {
		param.service = service;
		param.width = service->ce_info->width;
		param.height = service->ce_info->height;
		param.hist_mode = service->ce_info->hist_mode;
		param.mode = service->ce_info->mode;
		param.ce_alg_param = *service->ce_info->p_ce_alg_param;

		ret = copy_to_user(param.histogram, service->ce_info->histogram, sizeof(service->ce_info->histogram));
		if (ret) {
			HISI_FB_ERR("copy_to_user failed(hist)! ret=%d.\n", ret);
			return -2;
		}

		ret = copy_to_user(argp, &param, sizeof(ce_parameter_t));
		if (ret) {
			HISI_FB_ERR("copy_to_user failed(param)! ret=%d.\n", ret);
			return -2;
		}
	} else {
		ret = -1;
	}

	return ret;
}

int hisifb_ce_service_set_lut(struct fb_info *info, void __user *argp)
{
	ce_parameter_t param;
	ce_service_t *service = NULL;
	int ret = 0;
	int i = 0;

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = copy_from_user(&param, argp, sizeof(ce_parameter_t));
	if (ret) {
		HISI_FB_ERR("copy_from_user(param) failed! ret=%d.\n", ret);
		return -2;
	}

	if ((param.width < 16) || (param.width > 4096) || (param.height < 16) || (param.height > 4096)) {
		HISI_FB_ERR("width :%d height :%d,the size is not supported,please check it !!\n",param.width,param.height);
		return -1;
	}

	service = (ce_service_t *)param.service;

	for (i = 0; i < CE_SERVICE_LIMIT; i++ ) {
		if (service == &g_ce_services[i]) {
			break;
		}
	}

	if (i >= CE_SERVICE_LIMIT) {
		HISI_FB_ERR("service is not corrtct\n");
		return -1;
	}

	if (service == NULL || service->ce_info == NULL) {
		HISI_FB_ERR("service or ce_info is NULL\n");
		return -1;
	}

	service->ce_info->algorithm_result = param.result;
	if (service->ce_info->algorithm_result == 0) {
		ret = copy_from_user(service->ce_info->lut_table, param.lut_table, sizeof(service->ce_info->lut_table));
		if (ret) {
			HISI_FB_ERR("copy_from_user(lut_table) failed! ret=%d.\n", ret);
			return -2;
		}
	}

	service->ce_info = NULL;
	service_transform_to_next_status(service);
	wake_up_interruptible(&service->wq_lut);

	return ret;
}

ssize_t hisifb_display_effect_ce_ctrl_show(struct fb_info *info, char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	dss_display_effect_t *ce_ctrl = NULL;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	ce_ctrl = &(hisifd->ce_ctrl);

	return snprintf(buf, PAGE_SIZE, "%d\n", ce_ctrl->ctrl_enabled);
}

ssize_t hisifb_display_effect_ce_ctrl_store(struct fb_info *info, const char *buf, size_t count)
{
	struct hisi_fb_data_type *hisifd = NULL;
	dss_display_effect_t *ce_ctrl = NULL;
	unsigned int enable = 0;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return 0;
	}

	ce_ctrl = &(hisifd->ce_ctrl);

	enable = (buf[0] == '1') ? 1 : 0;

	mutex_lock(&(ce_ctrl->ctrl_lock));
	if (ce_ctrl->ctrl_enabled != enable) {
		ce_ctrl->ctrl_enabled = enable;
	}
	mutex_unlock(&(ce_ctrl->ctrl_lock));

	return count;
}

////////////////////////////////////////////////////////////////////////////////
// ACM CE
void hisi_dss_dpp_ace_set_reg(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	dss_display_effect_t *ce_ctrl = NULL;
	dss_ce_info_t *ce_info = NULL;
	char __iomem *ce_base = NULL;

	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return;
	}

	pinfo = &(hisifd->panel_info);
	ce_ctrl = &(hisifd->ce_ctrl);
	ce_info = &(hisifd->acm_ce_info);
	ce_base = hisifd->dss_base + DSS_DPP_ACM_CE_OFFSET;

	if (pinfo->acm_ce_support == 0)
		return;

	if (g_dss_effect_acm_ce_en != 1 || ce_ctrl->ctrl_enabled != 1) {
		set_reg(ce_base + ACM_CE_HIST_CTL, 0x2, 3, 0);
		set_reg(ce_base + ACM_CE_LUT_ENABLE, 0x0, 2, 0);
		ce_info->first_lut_set = false;
		return;
	}

	if (ce_info->new_hist_rpt) {
		ce_info->new_hist_rpt = false;
		if (ce_info->algorithm_result == 0) {
			char __iomem *dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
			int i = 0;

			if ((inp32(ce_base + ACM_CE_LUT_USING_IND) & 0x1) == 0) {
				ce_info->lut_base = dpp_base + ACM_CE_LUT0_OFFSET;
				ce_info->lut_sel = 1;
			} else {
				ce_info->lut_base = dpp_base + ACM_CE_LUT1_OFFSET;
				ce_info->lut_sel = 0;
			}

			for (i = 0; i < CE_VALUE_RANK; i++) {
				outp32(ce_info->lut_base + i * 4, ce_info->lut_table[i]);
			}

			ce_info->first_lut_set = true;
		}
	}

	if (ce_info->first_lut_set) {
		set_reg(ce_base + ACM_CE_LUT_SEL, ce_info->lut_sel, 32, 0);
	}

	set_reg(ce_base + ACM_CE_HIST_CTL, 0x1, 3, 0);
	set_reg(ce_base + ACM_CE_LUT_ENABLE, 0x3, 2, 0);
}

void hisi_dss_dpp_ace_handle_func(struct work_struct *work)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	dss_display_effect_t *ce_ctrl = NULL;
	dss_ce_info_t *ce_info = NULL;
	char __iomem *dpp_base = NULL;
	char __iomem *acm_ce_base = NULL;
	char __iomem *ce_hist_prt_base = NULL;
	int i = 0;

	hisifd = container_of(work, struct hisi_fb_data_type, dpp_ce_end_work);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	ce_info = &(hisifd->acm_ce_info);
	ce_ctrl = &(hisifd->ce_ctrl);

	if (pinfo->acm_ce_support == 0)
		return;

	if (g_dss_effect_acm_ce_en != 1 || ce_ctrl->ctrl_enabled != 1) {
		return;
	}

	down(&hisifd->blank_sem);
	if (!hisifd->panel_power_on) {
		up(&hisifd->blank_sem);
		return;
	}

	dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
	acm_ce_base = hisifd->dss_base + DSS_DPP_ACM_CE_OFFSET;

	ce_info->width = pinfo->xres;
	ce_info->height = pinfo->yres;
	ce_info->hist_mode = 0;
	ce_info->mode = 0;
	ce_info->p_ce_alg_param = &pinfo->ce_alg_param;

	hisifb_activate_vsync(hisifd);
	if ((inp32(acm_ce_base + ACM_CE_HIST_RPT_IND) & 0x1) == 0) {
		ce_hist_prt_base = dpp_base + ACM_CE_HIST_RPT0_OFFSET;
	} else {
		ce_hist_prt_base = dpp_base + ACM_CE_HIST_RPT1_OFFSET;
	}

	for (i = 0; i < CE_VALUE_RANK; i++) {
		ce_info->histogram[i] = inp32(ce_hist_prt_base + i * 4);
	}
	hisifb_deactivate_vsync(hisifd);
	up(&hisifd->blank_sem);

	ce_info->algorithm_result = do_contrast(ce_info);

	ce_info->new_hist_rpt = true;
}
