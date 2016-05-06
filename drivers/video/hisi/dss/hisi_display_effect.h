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
#ifndef HISI_DISPLAY_EFFECT_H
#define HISI_DISPLAY_EFFECT_H

#include "hisi_fb_def.h"
#include "hisi_dss.h"


#define CE_VALUE_BITWIDTH	(8)
#define CE_VALUE_RANK		(1 << CE_VALUE_BITWIDTH)
#define CE_SERVICE_LIMIT	(3)

struct hisi_fb_data_type;

typedef enum {
	CE_SERVICE_IDLE = 0,
	CE_SERVICE_HIST_REQ,
	CE_SERVICE_LUT_REQ,
	CE_SERVICE_STATUS_COUNT,
} ce_service_status;

typedef struct dss_display_effect {
	int ctrl_enabled;
	struct mutex ctrl_lock;
} dss_display_effect_t;

typedef struct dss_ce_info {
	// Running control
	bool new_hist_rpt;
	bool first_lut_set;

	// Register value
	int algorithm_result;
	uint32_t lut_sel;
	char __iomem *lut_base;
	uint32_t histogram[CE_VALUE_RANK];
	uint8_t lut_table[CE_VALUE_RANK];

	// Algorithm parameter
	int width; // Image size
	int height; // Image size
	int hist_mode; // 0 -- V of HSV, 1 -- Y of YUV
	int mode; // 0 -- video, 1 -- normal image
	ce_algorithm_parameter_t *p_ce_alg_param;
} dss_ce_info_t;

typedef struct ce_service {
	ce_service_status status;
	wait_queue_head_t wq_hist;
	wait_queue_head_t wq_lut;
	dss_ce_info_t *ce_info;
} ce_service_t;



#ifdef CONFIG_HISI_FB_3660
#define XBLOCKNUM	(6)
#define YBLOCKNUM	(6)
#define HIACE_LHIST_RANK	(16)
#define HIACE_GAMMA_RANK	(11)
#define HIACE_VALUE_RANK		(32)

typedef struct dss_hiace_info {
	uint32_t golbal_hist[HIACE_VALUE_RANK];
	uint32_t local_hist[YBLOCKNUM * XBLOCKNUM * HIACE_LHIST_RANK];
	uint32_t local_gamma_lut[YBLOCKNUM * XBLOCKNUM * HIACE_GAMMA_RANK];
} dss_hiace_info_t;
#endif



/*******************************************************************************
** FUNCTIONS PROTOTYPES
*/
int do_contrast(dss_ce_info_t *info);

void hisi_effect_init(struct hisi_fb_data_type *hisifd);

void hisifb_ce_service_init(void);
void hisifb_ce_service_deinit(void);
int hisifb_ce_service_get_support(struct fb_info *info, void __user *argp);
int hisifb_ce_service_get_limit(struct fb_info *info, void __user *argp);
int hisifb_ce_service_get_hist(void __user *argp);
int hisifb_ce_service_set_lut(struct fb_info *info, void __user *argp);
ssize_t hisifb_display_effect_ce_ctrl_show(struct fb_info *info, char *buf);
ssize_t hisifb_display_effect_ce_ctrl_store(struct fb_info *info, const char *buf, size_t count);

void hisi_dss_dpp_ace_set_reg(struct hisi_fb_data_type *hisifd);
void hisi_dss_dpp_ace_handle_func(struct work_struct *work);

#ifdef CONFIG_HISI_FB_3660
void init_hiace(struct hisi_fb_data_type *hisifd);
void hisi_dss_dpp_hiace_set_reg(struct hisi_fb_data_type *hisifd);
void hisi_dss_hiace_end_handle_func(struct work_struct *work);
#endif


#endif  //HISI_DISPLAY_EFFECT_H
