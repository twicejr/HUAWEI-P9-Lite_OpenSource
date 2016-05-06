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

#define ce_service_wait_event(wq, condition)	\
{	\
	long ret = 0;	\
	do {	\
		ret = wait_event_interruptible_timeout(wq, condition, msecs_to_jiffies(100000));	\
	} while (!ret);	\
	if (ret == -ERESTARTSYS) {	\
		hisifb_ce_service_deinit();	\
	}	\
}	\


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

	if (NULL == argp) {
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

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	ret = copy_from_user(&param, argp, sizeof(ce_parameter_t));
	if (ret) {
		HISI_FB_ERR("copy_from_user(param) failed! ret=%d.\n", ret);
		return -2;
	}

	service = (ce_service_t *)param.service;
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

void init_hiace(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *hi_ace_base = NULL;

	unsigned long dw_jiffies = 0;
	uint32_t tmp = 0;
	bool is_ready = false;

	int global_hist_ab_work;
	int global_hist_ab_shadow;
	int gamma_ab_work;
	int gamma_ab_shadow;
	int width;
	int height;
	int half_block_h;
	int half_block_w;
	int slop;
	int th_max;
	int th_min;
	int up_thres;
	int low_thres;
	int fixbit_y;
	int fixbit_x;
	int reciprocal_y;
	int reciprocal_x;

	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return ;
	}

	pinfo = &(hisifd->panel_info);
	hi_ace_base = hisifd->dss_base + DSS_HI_ACE_OFFSET;

	set_reg(hi_ace_base + HIACE_BYPASS_ACE, 0x1, 1, 0);
	set_reg(hi_ace_base + HIACE_INIT_GAMMA, 0x1, 1, 0);
	set_reg(hi_ace_base + HIACE_UPDATE_LOCAL, 0x1, 1, 0);

	//parameters
	width = hisifd->panel_info.xres & 0x1fff;
	height = hisifd->panel_info.yres & 0xfff;
	set_reg(hi_ace_base + HIACE_IMAGE_INFO, (height << 16) | width, 32, 0);

	half_block_w = (width / 12) & 0x1ff;
	half_block_h = ((height + 11) / 12) & 0xff;
	set_reg(hi_ace_base + HIACE_HALF_BLOCK_H_W,
		(half_block_h << 16) | half_block_w, 32, 0);

	set_reg(hi_ace_base + HIACE_LHIST_SFT, 0x0, 3, 0);

	slop = 68 & 0xff;
	th_min = 0 & 0x1ff;
	th_max = 30 & 0x1ff;
	set_reg(hi_ace_base + HIACE_HUE, (slop << 24) | (th_max << 12) | th_min, 32, 0);

	slop = 136 & 0xff;
	th_min = 50 & 0xff;
	th_max = 174 & 0xff;
	set_reg(hi_ace_base + HIACE_SATURATION, (slop << 24) | (th_max << 12) | th_min, 32, 0);

	slop = 136 & 0xff;
	th_min = 40 & 0xff;
	th_max = 255 & 0xff;
	set_reg(hi_ace_base + HIACE_VALUE, (slop << 24) | (th_max << 12) | th_min, 32, 0);

	set_reg(hi_ace_base + HIACE_SKIN_GAIN, 128, 8, 0);

	up_thres = 248 & 0xff;
	low_thres = 8 & 0xff;
	set_reg(hi_ace_base + HIACE_UP_LOW_TH, (up_thres << 8) | low_thres, 32, 0);

	fixbit_x = 9 & 0x1f;
	fixbit_y = 8 & 0x1f;
	reciprocal_x = 409 & 0x3ff;
	reciprocal_y = 364 & 0x3ff;
	set_reg(hi_ace_base + HIACE_XYWEIGHT, (fixbit_y < 26) | (reciprocal_y << 16)
		| (fixbit_x << 10) | reciprocal_x, 32, 0);

	//wait hiace gamma init
	is_ready = false;
	dw_jiffies = jiffies + HZ / 2;
	do {
		tmp = inp32(hi_ace_base + HIACE_INIT_GAMMA);
		if ((tmp & 0x1) != 0x1) {
			is_ready = true;
			break;
		}
	} while (time_after(dw_jiffies, jiffies));

	if (!is_ready) {
		HISI_FB_INFO("fb%d, HIACE_INIT_GAMMA is not ready!HIACE_INIT_GAMMA=0x%x.\n",
			hisifd->index, tmp);
	}

#if 0
	{
		int i = 0, j = 0, k= 0;
		int indx = 0;

		set_reg(hi_ace_base + HIACE_GAMMA_EN_HV_R, 1, 1, 31);

		for(i = 0; i < 6; i++) {
			for(j = 0; j < 6; j++) {
				for(k = 0; k< 11; k++) {
					int gamma = inp32(hi_ace_base + HIACE_GAMMA_VxHy_3z2_3z1_3z_R );
					printk("%x %x %x", gamma&0x3ff, (gamma>>10)&0x3ff, (gamma>>20)&0x3ff);
				}
				printk("\n");
			}
			printk("\n");
		}

		set_reg(hi_ace_base + HIACE_GAMMA_EN_HV_R, 0, 1, 31);
	}
#endif

	global_hist_ab_work = inp32(hi_ace_base + HIACE_GLOBAL_HIST_AB_WORK);
	global_hist_ab_shadow = !global_hist_ab_work;

	gamma_ab_work = inp32(hi_ace_base + HIACE_GAMMA_AB_WORK);
	gamma_ab_shadow = !gamma_ab_work;

	set_reg(hi_ace_base + HIACE_GLOBAL_HIST_AB_SHADOW, global_hist_ab_shadow, 1, 0);
	set_reg(hi_ace_base + HIACE_GAMMA_AB_SHADOW, gamma_ab_shadow, 1, 0);

	//clean hiace interrupt
	set_reg(hi_ace_base + HIACE_INT_STAT, 0x1, 1, 0);

	//unmask hiace interrupt
	set_reg(hi_ace_base + HIACE_INT_UNMASK, 0x1, 1, 0);

	//enable hiace
	set_reg(hi_ace_base + HIACE_BYPASS_ACE, 0x0, 1, 0);
}

void hisi_dss_dpp_hiace_set_reg(struct hisi_fb_data_type *hisifd)
{
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return ;
	}
}

void  hisi_dss_hiace_end_handle_func(struct work_struct *work)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *hiace_base = NULL;
	int i = 0, j = 0;
	int global_hist_ab_shadow = 0;
	int global_hist_ab_work = 0;
	int gamma_ab_shadow = 0;
	int gamma_ab_work = 0;
	int local_valid =0 ;

	int up_cnt = 0;
	int low_cnt = 0;

	hisifd = container_of(work, struct hisi_fb_data_type, hiace_end_work);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return ;
	}

	pinfo = &(hisifd->panel_info);
	hiace_base = hisifd->dss_base + DSS_HI_ACE_OFFSET;

	if (pinfo->hiace_support == 0)
		return;

	down(&hisifd->blank_sem);
	if (!hisifd->panel_power_on) {
		up(&hisifd->blank_sem);
		return;
	}

	hisifb_activate_vsync(hisifd);

	up_cnt = inp32(hiace_base + HIACE_UP_CNT);
	low_cnt = inp32(hiace_base + HIACE_LOW_CNT);

	global_hist_ab_shadow = inp32(hiace_base + HIACE_GLOBAL_HIST_AB_SHADOW);
	global_hist_ab_work = inp32(hiace_base + HIACE_GLOBAL_HIST_AB_WORK);

	if (global_hist_ab_shadow == global_hist_ab_work) {
		//read global hist
		for (i = 0; i < 32; i ++ ) {
			hisifd->hiace_info.golbal_hist[i] = inp32(hiace_base + HIACE_GLOBAL_HIST_LUT_ADDR + i * 4);
		}

		global_hist_ab_shadow ^= 1;
		outp32(hiace_base +  HIACE_GLOBAL_HIST_AB_SHADOW, global_hist_ab_shadow);
	}
	local_valid = inp32(hiace_base + HIACE_LOCAL_VALID);

	if (local_valid == 1) {
		//read local hist
		outp32(hiace_base + HIACE_LHIST_EN, 1);

		for (i=0; i < (6 * 6 * 16); i ++) {//H  L
			hisifd->hiace_info.local_hist[i] = inp32(hiace_base + HIACE_LOCAL_HIST_VxHy_2z_2z1);
		}

		outp32(hiace_base + HIACE_LHIST_EN, 0);
		outp32(hiace_base + HIACE_UPDATE_LOCAL, 1);
	}

	gamma_ab_shadow = inp32(hiace_base + HIACE_GAMMA_AB_SHADOW);
	gamma_ab_work = inp32(hiace_base + HIACE_GAMMA_AB_WORK);

	hisifb_deactivate_vsync(hisifd);


	if (((local_valid == 1) || ( global_hist_ab_shadow == global_hist_ab_work))
		&& (gamma_ab_shadow == gamma_ab_work)) {
		//call algorithm
		for (i = 0; i < 6 * 6 ; i ++) {//H M L
			uint32_t *p_local_gamma = hisifd->hiace_info.local_gamma_lut + 11 * i;
			int k = 0;
			for (j = 0; j < 33; j += 3) {
				p_local_gamma[k++] = (((j + 2 )<<5) << 20) | (((j + 1)<<5) << 10) | (j<<5);
			}
		}
	}

	hisifb_activate_vsync(hisifd);
	if (gamma_ab_shadow == gamma_ab_work) {
		//write gamma lut
		outp32(hiace_base + HIACE_GAMMA_EN, 1);
		for (i = 0; i < (6 * 6 * 11); i++) {
			outp32(hiace_base + HIACE_GAMMA_VxHy_3z2_3z1_3z_W, hisifd->hiace_info.local_gamma_lut[i]);
		}
		outp32(hiace_base + HIACE_GAMMA_EN, 0);
		gamma_ab_shadow ^= 1;
		outp32(hiace_base + HIACE_GAMMA_AB_SHADOW, gamma_ab_shadow);
	}

	outp32(hiace_base + HIACE_INT_STAT, 0x1);
	hisifb_deactivate_vsync(hisifd);

	up(&hisifd->blank_sem);
}

////////////////////////////////////////////////////////////////////////////////
//ACE
static u32 ace_orginal_lut[] = {
	0x50002,	0x90007,	0xe000c,	0x130011,	0x180016,	0x1e001b,	0x230020,	0x290026,
	0x2f002c,	0x350032,	0x3b0038,	0x42003e,	0x480045,	0x4f004c,	0x560053,	0x5e005a,
	0x650061,	0x6d0069,	0x750071,	0x7d0079,	0x850081,	0x8e0089,	0x960092,	0x9f009a,
	0xa700a3,	0xb000ac,	0xb900b5,	0xc200bd,	0xcb00c6,	0xd400cf,	0xdd00d9,	0xe600e2,
	0xef00eb,	0xf900f4,	0x10200fd,	0x10b0107,	0x1150110,	0x11e0119,	0x1280123,	0x131012d,
	0x13b0136,	0x1450140,	0x14e0149,	0x1580153,	0x162015d,	0x16c0167,	0x1760171,	0x180017b,
	0x18a0185,	0x194018f,	0x19e0199,	0x1a801a3,	0x1b201ad,	0x1bc01b7,	0x1c601c1,	0x1d001cb,
	0x1da01d5,	0x1e401df,	0x1ee01e9,	0x1f801f3,	0x20101fd,	0x20b0206,	0x2150210,	0x21f021a,
	0x2290224,	0x232022d,	0x23c0237,	0x2450241,	0x24f024a,	0x2580253,	0x261025d,	0x26a0266,
	0x273026f,	0x27c0278,	0x2850281,	0x28e028a,	0x2970293,	0x2a0029b,	0x2a802a4,	0x2b102ad,
	0x2ba02b6,	0x2c302be,	0x2cc02c7,	0x2d502d0,	0x2de02d9,	0x2e702e2,	0x2ef02eb,	0x2f802f4,
	0x30102fd,	0x30a0306,	0x313030e,	0x31b0317,	0x3240320,	0x32c0328,	0x3350331,	0x33d0339,
	0x3450341,	0x34d0349,	0x3540350,	0x35c0358,	0x3630360,	0x36b0367,	0x372036f,	0x37a0376,
	0x381037d,	0x3880384,	0x38f038c,	0x3960393,	0x39e039a,	0x3a503a1,	0x3ab03a8,	0x3b203af,
	0x3b903b6,	0x3bf03bc,	0x3c603c3,	0x3cc03c9,	0x3d203cf,	0x3d703d4,	0x3dc03da,	0x3e203df,
	0x3e603e4,	0x3eb03e8,	0x3ef03ed,	0x3f203f1,	0x3f603f4,	0x3f903f7,	0x3fc03fa,	0x3fe03fd,
};

void hisi_dss_dpp_ace_set_reg(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	dss_ce_info_t *ace_info = NULL;
	char __iomem *ace_base = NULL;
	char __iomem *ace_lut_base = NULL;
	uint32_t i = 0;

	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return ;
	}

	pinfo = &(hisifd->panel_info);
	ace_info = &(hisifd->acm_ce_info);
	ace_base = hisifd->dss_base + DSS_DPP_ACE_OFFSET;
	ace_lut_base = hisifd->dss_base + DSS_DPP_ACE_LUT_OFFSET;

	if (pinfo->acm_ce_support == 0)
		return;

	if ((inp32(ace_base + ACE_LUT_SEL) & 0x1) == 0) {
		ace_info->lut_base = ace_lut_base + ACE_LUT0;
		for (i = 0; i < 128; i++) {
			//output lut0
			outp32(ace_info->lut_base + i * 4, ace_orginal_lut[i]);
		}
		ace_info->lut_sel = 1;
	} else {
		ace_info->lut_base = ace_lut_base + ACE_LUT1;
		for (i = 0; i < 128; i++) {
			//output lut1
			outp32(ace_info->lut_base + i * 4, ace_orginal_lut[i]);
		}
		ace_info->lut_sel = 0;
	}

	hisifd->set_reg(hisifd, ace_base + ACE_LUT_SEL, ace_info->lut_sel, 32, 0);
}

void hisi_dss_dpp_ace_handle_func(struct work_struct *work)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	dss_ce_info_t *ace_info = NULL;

	char __iomem *ace_base = NULL;
	char __iomem *ace_lut_base = NULL;
	char __iomem *ace_hist_prt_base = NULL;
	int i = 0;

	hisifd = container_of(work, struct hisi_fb_data_type, dpp_ce_end_work);

	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return ;
	}

	pinfo = &(hisifd->panel_info);
	ace_info = &(hisifd->acm_ce_info);

	ace_base = hisifd->dss_base + DSS_DPP_ACE_OFFSET;
	ace_lut_base = hisifd->dss_base + DSS_DPP_ACE_LUT_OFFSET;

	if (pinfo->acm_ce_support == 0)
		return;

	down(&hisifd->blank_sem);
	if (!hisifd->panel_power_on) {
		up(&hisifd->blank_sem);
		return;
	}

	hisifb_activate_vsync(hisifd);
	if ((inp32(ace_base + ACE_HIST_IND) & 0x1) == 0) {
		ace_hist_prt_base = ace_lut_base + ACE_HIST0;
		for (i = 0; i < 256; i++) {
			ace_info->histogram[i] = inp32(ace_hist_prt_base + i * 4);
		}
	} else {
		ace_hist_prt_base = ace_lut_base + ACE_HIST1;
		for (i = 0; i < 256; i++) {
			ace_info->histogram[i] = inp32(ace_hist_prt_base + i * 4);
		}
	}
	hisifb_deactivate_vsync(hisifd);

	up(&hisifd->blank_sem);
}
