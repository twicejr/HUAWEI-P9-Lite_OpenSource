/* include/linux/hisi_dss.h
 *
 * Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
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

#ifndef _HISI_DSS_H_
#define _HISI_DSS_H_

#include <linux/types.h>
#include <linux/fb.h>
#include <linux/hisi_fb_common.h>


#define HISIFB_VSYNC_CTRL _IOW(HISIFB_IOCTL_MAGIC, 0x02, unsigned int)
#define HISIFB_DSS_CLK_RATE_SET _IOW(HISIFB_IOCTL_MAGIC, 0x04, struct dss_clk_rate)
//#define HISIFB_PIXCLK_RATE_SET _IOW(HISIFB_IOCTL_MAGIC, 0x05, struct fb_var_screeninfo)
#define HISIFB_DIRTY_REGION_UPDT_SET _IOW(HISIFB_IOCTL_MAGIC, 0x06, int)
#define HISIFB_DSS_MMBUF_ALLOC _IOW(HISIFB_IOCTL_MAGIC, 0x08, struct dss_mmbuf)
#define HISIFB_DSS_MMBUF_FREE _IOW(HISIFB_IOCTL_MAGIC, 0x09, struct dss_mmbuf)

//#define HISIFB_OV_TEST _IOW(HISIFB_IOCTL_MAGIC, 0x20, struct dss_overlay_test)
#define HISIFB_OV_ONLINE_PLAY _IOW(HISIFB_IOCTL_MAGIC, 0x21, struct dss_overlay)
#define HISIFB_OV_OFFLINE_PLAY _IOW(HISIFB_IOCTL_MAGIC, 0x22, struct dss_overlay)

#define HISIFB_PURE_LAYER_CHECK _IOW(HISIFB_IOCTL_MAGIC, 0x40, struct dss_pure_layer_check)
#define HISIFB_IDLE_IS_ALLOWED  _IOW(HISIFB_IOCTL_MAGIC, 0x42, int)

#define HISIFB_CE_SUPPORT_GET _IOW(HISIFB_IOCTL_MAGIC, 0x50, unsigned int)
#define HISIFB_CE_SERVICE_LIMIT_GET _IOW(HISIFB_IOCTL_MAGIC, 0x51, int)
#define HISIFB_CE_HIST_GET _IOW(HISIFB_IOCTL_MAGIC, 0x52, struct ce_parameter)
#define HISIFB_CE_LUT_SET _IOW(HISIFB_IOCTL_MAGIC, 0x53, struct ce_parameter)


#ifndef BIT
#define BIT(x)  (1<<(x))
#endif

/* for fb0 fb1 fb2 and so on */
#define PRIMARY_PANEL_IDX	(0)
#define EXTERNAL_PANEL_IDX	(1)
#define AUXILIARY_PANEL_IDX	(2)

#define DSS_WCH_MAX  (2)


/* for YUV */
#define MAX_PLANES	(3)


enum hisi_fb_pixel_format {
	HISI_FB_PIXEL_FORMAT_RGB_565 = 0,
	HISI_FB_PIXEL_FORMAT_RGBX_4444,
	HISI_FB_PIXEL_FORMAT_RGBA_4444,
	HISI_FB_PIXEL_FORMAT_RGBX_5551,
	HISI_FB_PIXEL_FORMAT_RGBA_5551,
	HISI_FB_PIXEL_FORMAT_RGBX_8888,
	HISI_FB_PIXEL_FORMAT_RGBA_8888,

	HISI_FB_PIXEL_FORMAT_BGR_565,
	HISI_FB_PIXEL_FORMAT_BGRX_4444,
	HISI_FB_PIXEL_FORMAT_BGRA_4444,
	HISI_FB_PIXEL_FORMAT_BGRX_5551,
	HISI_FB_PIXEL_FORMAT_BGRA_5551,
	HISI_FB_PIXEL_FORMAT_BGRX_8888,
	HISI_FB_PIXEL_FORMAT_BGRA_8888,

	HISI_FB_PIXEL_FORMAT_YUV_422_I,

	/* YUV Semi-planar */
	HISI_FB_PIXEL_FORMAT_YCbCr_422_SP, /* NV16 */
	HISI_FB_PIXEL_FORMAT_YCrCb_422_SP,
	HISI_FB_PIXEL_FORMAT_YCbCr_420_SP,
	HISI_FB_PIXEL_FORMAT_YCrCb_420_SP, /* NV21*/

	/* YUV Planar */
	HISI_FB_PIXEL_FORMAT_YCbCr_422_P,
	HISI_FB_PIXEL_FORMAT_YCrCb_422_P,
	HISI_FB_PIXEL_FORMAT_YCbCr_420_P,
	HISI_FB_PIXEL_FORMAT_YCrCb_420_P, /* HISI_FB_PIXEL_FORMAT_YV12 */

	/* YUV Package */
	HISI_FB_PIXEL_FORMAT_YUYV_422_Pkg,
	HISI_FB_PIXEL_FORMAT_UYVY_422_Pkg,
	HISI_FB_PIXEL_FORMAT_YVYU_422_Pkg,
	HISI_FB_PIXEL_FORMAT_VYUY_422_Pkg,
};

enum hisi_fb_blending {
	HISI_FB_BLENDING_NONE = 0,
	HISI_FB_BLENDING_PREMULT = 1,
	HISI_FB_BLENDING_COVERAGE = 2,
	HISI_FB_BLENDING_MAX = 3,
};

enum hisi_fb_transform{
	HISI_FB_TRANSFORM_NOP = 0x0,
	/* flip source image horizontally (around the vertical axis) */
	HISI_FB_TRANSFORM_FLIP_H = 0x01,
	/* flip source image vertically (around the horizontal axis)*/
	HISI_FB_TRANSFORM_FLIP_V = 0x02,
	/* rotate source image 90 degrees clockwise */
	HISI_FB_TRANSFORM_ROT_90 = 0x04,
	/* rotate source image 180 degrees */
	HISI_FB_TRANSFORM_ROT_180 = 0x03,
	/* rotate source image 270 degrees clockwise */
	HISI_FB_TRANSFORM_ROT_270 = 0x07,
};

enum dss_csc_mode {
	DSS_CSC_601_WIDE = 0,
	DSS_CSC_601_NARROW,
	DSS_CSC_709_WIDE,
	DSS_CSC_709_NARROW,
};

enum dss_afbc_scramble_mode {
	DSS_AFBC_SCRAMBLE_NONE = 0,
	DSS_AFBC_SCRAMBLE_MODE1,
	DSS_AFBC_SCRAMBLE_MODE2,
	DSS_AFBC_SCRAMBLE_MODE3,
};

enum dss_chn_idx {
	DSS_RCHN_NONE = -1,
	DSS_RCHN_D2 = 0,
	DSS_RCHN_D3,
	DSS_RCHN_V0,
	DSS_RCHN_G0,
	DSS_RCHN_V1,
	DSS_RCHN_G1,
	DSS_RCHN_D0,
	DSS_RCHN_D1,

	DSS_WCHN_W0,
	DSS_WCHN_W1,

	DSS_CHN_MAX,

	DSS_RCHN_V2 = DSS_CHN_MAX,  //for copybit, only supported in chicago
	DSS_WCHN_W2,

	DSS_COPYBIT_MAX,
};

enum dss_ovl_idx {
	DSS_OVL0 = 0,
	DSS_OVL1,
	DSS_OVL2,
	DSS_OVL3,
	DSS_OVL_IDX_MAX,
};

enum dss_wb_compose_type {
	DSS_WB_COMPOSE_PRIMARY = 0,
	DSS_WB_COMPOSE_COPYBIT,
	DSS_WB_COMPOSE_TYPE_MAX,
};

/* dss capability priority description */
#define CAP_1D_SHARPNESS	BIT(13)
#define CAP_2D_SHARPNESS	BIT(12)
#define CAP_TILE	BIT(11)
#define CAP_AFBCD	BIT(10)
#define CAP_AFBCE	BIT(9)
#define CAP_YUV_DEINTERLACE	BIT(8)
#define CAP_YUV_PLANAR	BIT(7)
#define CAP_YUV_SEMI_PLANAR	BIT(6)
#define CAP_YUV_PACKAGE	BIT(5)
#define CAP_SCL	BIT(4)
#define CAP_ROT	BIT(3)
#define CAP_PURE_COLOR	BIT(2)
#define CAP_DIM	BIT(1)
#define CAP_BASE	BIT(0)

typedef struct dss_rect {
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
} dss_rect_t;

typedef struct dss_rect_ltrb {
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
} dss_rect_ltrb_t;

typedef struct dss_mmbuf {
	uint32_t addr;
	int32_t size;
} dss_mmbuf_t;

typedef struct dss_img {
	uint32_t format;
	uint32_t width;
	uint32_t height;
	uint32_t bpp;	/* bytes per pixel */
	uint32_t buf_size;
	uint32_t stride;
	uint32_t stride_plane1;
	uint32_t stride_plane2;
	uint64_t phy_addr;
	uint64_t vir_addr;
	uint32_t offset_plane1;
	uint32_t offset_plane2;

	uint64_t afbc_header_addr;
	uint64_t afbc_payload_addr;
	uint32_t afbc_header_stride;
	uint32_t afbc_payload_stride;
	uint32_t afbc_scramble_mode;
	uint32_t mmbuf_base;
	uint32_t mmbuf_size;

	uint32_t mmu_enable;
	uint32_t csc_mode;
	uint32_t secure_mode;
	int32_t shared_fd;
	uint32_t reserved0;
} dss_img_t;

typedef struct dss_block_info {
	int32_t first_tile;
	int32_t last_tile;
	uint32_t acc_hscl;
	uint32_t h_ratio;
	uint32_t v_ratio;
	int32_t h_v_order;
} dss_block_info_t;

typedef struct dss_layer {
	dss_img_t img;
	dss_rect_t src_rect;
	dss_rect_t src_rect_mask;
	dss_rect_t dst_rect;
	uint32_t transform;
	int32_t blending;
	uint32_t glb_alpha;
	uint32_t color; /* background color or dim color */
	int32_t layer_idx;
	int32_t chn_idx;
	uint32_t need_cap;
	int32_t acquire_fence;

	dss_block_info_t block_info;
} dss_layer_t;

typedef struct dss_wb_layer {
	dss_img_t dst;
	dss_rect_t src_rect;
	dss_rect_t dst_rect;
	uint32_t transform;
	int32_t chn_idx;
	uint32_t need_cap;
	uint32_t reserved0;

	int32_t acquire_fence;
	int32_t release_fence;
} dss_wb_layer_t;


/*
** dss error status
*/
#define DSS_PDP_LDI_UNDERFLOW		BIT(0)
#define DSS_SDP_LDI_UNDERFLOW		BIT(1)
#define DSS_PDP_SMMU_ERR			BIT(2)
#define DSS_SDP_SMMU_ERR			BIT(3)

/*
** crc enable status
*/
enum dss_crc_enable_status {
	DSS_CRC_NONE = 0,
	DSS_CRC_OV_EN = 1,
	DSS_CRC_LDI_EN,
	DSS_CRC_SUM_EN,
};

/*
** sec enable status
*/
enum dss_sec_enable_status {
	DSS_SEC_STOP = 0,
	DSS_SEC_RUN = 1,
};

typedef struct dss_crc_info {
	uint32_t crc_ov_result;
	uint32_t crc_ldi_result;
	uint32_t crc_sum_result;
	uint32_t crc_ov_frm;
	uint32_t crc_ldi_frm;
	uint32_t crc_sum_frm;

	uint32_t err_status;
	uint32_t reserved0;
} dss_crc_info_t;


/* Max multi-src channel number of the DSS. */
#define MAX_DSS_SRC_NUM	(7)
#define MAX_DSS_DST_NUM	(2)


#define HISI_DSS_OV_BLOCK_NUMS	(23)


typedef struct dss_overlay_block {
	dss_layer_t layer_infos[MAX_DSS_SRC_NUM];
	dss_rect_t ov_block_rect;
	uint32_t layer_nums;
	uint32_t reserved0;
} dss_overlay_block_t;

typedef struct dss_overlay {
	dss_wb_layer_t wb_layer_infos[MAX_DSS_DST_NUM];
	dss_rect_t wb_ov_rect;
	uint32_t wb_layer_nums;
	uint32_t wb_compose_type;

	// struct dss_overlay_block
	uint64_t ov_block_infos_ptr;
	uint32_t ov_block_nums;
	int32_t ovl_idx;
	uint32_t wb_enable;
	uint32_t frame_no;

	// dirty region
	dss_rect_t dirty_rect;

	// resolution change
	struct dss_rect res_updt_rect;

	// crc
	dss_crc_info_t crc_info;
	int32_t crc_enable_status;
	uint32_t sec_enable_status;

	uint32_t to_be_continued;
	int32_t release_fence;
} dss_overlay_t;


typedef struct dss_clk_rate {
	uint64_t dss_pri_clk_rate;
	uint64_t dss_pclk_dss_rate;
	uint64_t dss_pclk_pctrl_rate;
} dss_clk_rate_t;

typedef struct dss_pure_layer_check {
	int32_t layer_index;
	uint32_t color_flag;
	uint32_t alpha_flag;
	uint32_t color; /* argb8888 (31:0 AARRGGBB) */
} dss_pure_layer_check_t;

typedef struct dss_reg {
	uint32_t reg_addr;
	uint32_t reg_val;
} dss_reg_t;

typedef struct dss_overlay_test {
	uint64_t reg;
	uint32_t reg_cnt;
	uint32_t reserved0;
} dss_overlay_test_t;

typedef struct ce_algorithm_parameter {
	int iDiffMaxTH;
	int iDiffMinTH;
	int iAlphaMinTH;
	int iFlatDiffTH;
	int iBinDiffMaxTH;

	int iDarkPixelMinTH;
	int iDarkPixelMaxTH;
	int iDarkAvePixelMinTH;
	int iDarkAvePixelMaxTH;
	int iWhitePixelTH;
	int fweight;
	int fDarkRatio;
	int fWhiteRatio;

	int iDarkPixelTH;
	int fDarkSlopeMinTH;
	int fDarkSlopeMaxTH;
	int fDarkRatioMinTH;
	int fDarkRatioMaxTH;

	int iBrightPixelTH;
	int fBrightSlopeMinTH;
	int fBrightSlopeMaxTH;
	int fBrightRatioMinTH;
	int fBrightRatioMaxTH;

	int iZeroPos0MaxTH;
	int iZeroPos1MaxTH;

	int iDarkFMaxTH;
	int iDarkFMinTH;
	int iPos0MaxTH;
	int iPos0MinTH;

	int fKeepRatio;
} ce_algorithm_parameter_t;

typedef struct ce_parameter {
	int width;
	int height;
	int hist_mode;
	int mode;
	int result;
	uint32_t reserved0;
	uint32_t *histogram;
	uint8_t *lut_table;
	void *service;
	ce_algorithm_parameter_t ce_alg_param;
} ce_parameter_t;

#endif /*_HISI_DSS_H_*/
