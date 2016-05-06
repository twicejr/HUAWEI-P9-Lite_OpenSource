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
#ifndef HISI_FB_PANEL_H
#define HISI_FB_PANEL_H

#include "hisi_cfg_sbl.h"
#include "hisi_fb_def.h"
#include "hisi_mipi_dsi.h"
#include "hisi_rgb2mipi.h"
#include "hisi_dss.h"


/* panel type list */
#define PANEL_NO	BIT(0)	/* No Panel */
#define PANEL_LCDC	BIT(1)	/* internal LCDC type */
#define PANEL_HDMI	BIT(2)	/* HDMI TV */
#define PANEL_MIPI_VIDEO	BIT(3)	/* MIPI */
#define PANEL_MIPI_CMD	BIT(4)	/* MIPI */
#define PANEL_DUAL_MIPI_VIDEO	BIT(5)	/* DUAL MIPI */
#define PANEL_DUAL_MIPI_CMD	BIT(6)	/* DUAL MIPI */
#define PANEL_EDP	BIT(7)	/* LVDS */
#define PANEL_MIPI2RGB	BIT(8)	/* MIPI to RGB */
#define PANEL_RGB2MIPI	BIT(9)	/* RGB to MIPI */
#define PANEL_OFFLINECOMPOSER	BIT(10)	/* offline composer */
#define PANEL_WRITEBACK	BIT(11)	/* Wifi display */

/* dts initial */
#define DTS_FB_RESOURCE_INIT_READY	BIT(0)
#define DTS_PWM_READY	BIT(1)
//#define DTS_BLPWM_READY	BIT(2)
#define DTS_SPI_READY	BIT(3)
#define DTS_PANEL_PRIMARY_READY	BIT(4)
#define DTS_PANEL_EXTERNAL_READY	BIT(5)
#define DTS_PANEL_OFFLINECOMPOSER_READY	BIT(6)
#define DTS_PANEL_WRITEBACK_READY	BIT(7)

/* device name */
#define DEV_NAME_DSS_DPE		"dss_dpe"
#define DEV_NAME_SPI			"spi_dev0"
#define DEV_NAME_HDMI			"hdmi"
#define DEV_NAME_EDP			"edp"
#define DEV_NAME_MIPI2RGB		"mipi2rgb"
#define DEV_NAME_RGB2MIPI		"rgb2mipi"
#define DEV_NAME_MIPIDSI		"mipi_dsi"
#define DEV_NAME_FB				"hisi_fb"
#define DEV_NAME_PWM			"hisi_pwm"
#define DEV_NAME_BLPWM			"hisi_blpwm"
#define DEV_NAME_LCD_BKL		"lcd_backlight0"

/* vcc name */
#define REGULATOR_PDP_NAME	"regulator_dsssubsys"
#define REGULATOR_MMBUF	"regulator_mmbuf"


/* irq name */
#define IRQ_PDP_NAME	"irq_pdp"
#define IRQ_SDP_NAME	"irq_sdp"
#define IRQ_ADP_NAME	"irq_adp"
#define IRQ_DSI0_NAME	"irq_dsi0"
#define IRQ_DSI1_NAME	"irq_dsi1"

/* dts compatible */
#define DTS_COMP_FB_NAME	"hisilicon,hisifb"
#define DTS_COMP_PWM_NAME	"hisilicon,hisipwm"
#define DTS_COMP_BLPWM_NAME	"hisilicon,hisiblpwm"
#define DTS_PATH_LOGO_BUFFER	"/reserved-memory/logo-buffer"

/* lcd resource name */
#define LCD_BL_TYPE_NAME	"lcd-bl-type"
#define FPGA_FLAG_NAME "fpga_flag"
#define LCD_DISPLAY_TYPE_NAME	"lcd-display-type"
#define LCD_IFBC_TYPE_NAME	"lcd-ifbc-type"

/* backlight type */
#define BL_SET_BY_NONE	BIT(0)
#define BL_SET_BY_PWM	BIT(1)
#define BL_SET_BY_BLPWM	BIT(2)
#define BL_SET_BY_MIPI	BIT(3)
#define BL_SET_BY_SH_BLPWM	BIT(4)

/* supported display effect type */
#define COMFORM_MODE			BIT(0)
#define ACM_COLOR_ENHANCE_MODE	BIT(1)
#define IC_COLOR_ENHANCE_MODE	BIT(2)
#define LED_RG_COLOR_TEMP_MODE	BIT(16)

#define LCD_BL_IC_NAME_MAX	(50)

// blpwm precision type
enum BLPWM_PRECISION_TYPE {
	BLPWM_PRECISION_DEFAULT_TYPE = 0,
	BLPWM_PRECISION_10000_TYPE = 1,
	BLPWM_PRECISION_2048_TYPE = 2,
};

// LCD init step
enum LCD_INIT_STEP {
	LCD_INIT_NONE = 0,
	LCD_INIT_POWER_ON,
	LCD_INIT_LDI_SEND_SEQUENCE,
	LCD_INIT_MIPI_LP_SEND_SEQUENCE,
	LCD_INIT_MIPI_HS_SEND_SEQUENCE,
};

// LCD uninit step
enum LCD_UNINIT_STEP {
	LCD_UNINIT_NONE = 0,
	LCD_UNINIT_POWER_OFF,
	LCD_UNINIT_LDI_SEND_SEQUENCE,
	LCD_UNINIT_MIPI_LP_SEND_SEQUENCE,
	LCD_UNINIT_MIPI_HS_SEND_SEQUENCE,
};

enum LCD_ESD_RECOVER_STEP {
	LCD_ESD_RECOVER_NONE = 0,
	LCD_ESD_RECOVER_POWER_OFF,
	LCD_ESD_RECOVER_POWER_ON,
};

// LCD REFRESH DIRECTION
enum LCD_REFRESH_DIRECTION {
	LCD_REFRESH_LEFT_TOP = 0,
	LCD_REFRESH_RIGHT_TOP,
	LCD_REFRESH_LEFT_BOTTOM,
	LCD_REFRESH_RIGHT_BOTTOM,
};

// IFBC compress mode
enum IFBC_TYPE {
	IFBC_TYPE_NONE = 0,
	IFBC_TYPE_ORISE2X,
	IFBC_TYPE_ORISE3X,
	IFBC_TYPE_HIMAX2X,
	IFBC_TYPE_RSP2X,
	IFBC_TYPE_RSP3X,
	IFBC_TYPE_VESA2X_SINGLE,
	IFBC_TYPE_VESA3X_SINGLE,
	IFBC_TYPE_VESA2X_DUAL,
	IFBC_TYPE_VESA3X_DUAL,

	IFBC_TYPE_MAX
};

// IFBC compress mode
enum IFBC_COMP_MODE {
	IFBC_COMP_MODE_0 = 0,
	IFBC_COMP_MODE_1,
	IFBC_COMP_MODE_2,
	IFBC_COMP_MODE_3,
	IFBC_COMP_MODE_4,
	IFBC_COMP_MODE_5,
	IFBC_COMP_MODE_6,
};

//xres_div
enum XRES_DIV {
	XRES_DIV_1 = 1,
	XRES_DIV_2,
	XRES_DIV_3,
	XRES_DIV_4,
	XRES_DIV_5,
	XRES_DIV_6,
};

//yres_div
enum YRES_DIV {
	YRES_DIV_1 = 1,
	YRES_DIV_2,
	YRES_DIV_3,
	YRES_DIV_4,
	YRES_DIV_5,
	YRES_DIV_6,
};

// pxl0_divxcfg
enum PXL0_DIVCFG {
	PXL0_DIVCFG_0 = 0,
	PXL0_DIVCFG_1,
	PXL0_DIVCFG_2,
	PXL0_DIVCFG_3,
	PXL0_DIVCFG_4,
	PXL0_DIVCFG_5,
	PXL0_DIVCFG_6,
	PXL0_DIVCFG_7,
};

// pxl0_div2_gt_en
enum PXL0_DIV2_GT_EN {
	PXL0_DIV2_GT_EN_CLOSE = 0,
	PXL0_DIV2_GT_EN_OPEN,
};

// pxl0_div4_gt_en
enum PXL0_DIV4_GT_EN {
	PXL0_DIV4_GT_EN_CLOSE = 0,
	PXL0_DIV4_GT_EN_OPEN,
};

// pxl0_dsi_gt_en
enum PXL0_DSI_GT_EN {
	PXL0_DSI_GT_EN_0 = 0,
	PXL0_DSI_GT_EN_1,
	PXL0_DSI_GT_EN_2,
	PXL0_DSI_GT_EN_3,
};

enum VSYNC_CTRL_TYPE {
	VSYNC_CTRL_NONE = 0x0,
	VSYNC_CTRL_ISR_OFF = BIT(0),
	VSYNC_CTRL_MIPI_ULPS = BIT(1),
	VSYNC_CTRL_CLK_OFF = BIT(2),
	VSYNC_CTRL_VCC_OFF = BIT(3),
};

#define MIPI_DSI_BIT_CLK_STR1	"00001"
#define MIPI_DSI_BIT_CLK_STR2	"00010"
#define MIPI_DSI_BIT_CLK_STR3	"00100"
#define MIPI_DSI_BIT_CLK_STR4	"01000"
#define MIPI_DSI_BIT_CLK_STR5	"10000"

/* resource desc */
struct resource_desc {
	uint32_t flag;
	char *name;
	uint32_t *value;
};

/* dtype for vcc */
enum {
	DTYPE_VCC_GET,
	DTYPE_VCC_PUT,
	DTYPE_VCC_ENABLE,
	DTYPE_VCC_DISABLE,
	DTYPE_VCC_SET_VOLTAGE,
};

/* vcc desc */
struct vcc_desc {
	int dtype;
	char *id;
	struct regulator **regulator;
	int min_uV;
	int max_uV;
	int waittype;
	int wait;
};

/* pinctrl operation */
enum {
	DTYPE_PINCTRL_GET,
	DTYPE_PINCTRL_STATE_GET,
	DTYPE_PINCTRL_SET,
	DTYPE_PINCTRL_PUT,
};

/* pinctrl state */
enum {
	DTYPE_PINCTRL_STATE_DEFAULT,
	DTYPE_PINCTRL_STATE_IDLE,
};

/* pinctrl data */
struct pinctrl_data {
	struct pinctrl *p;
	struct pinctrl_state *pinctrl_def;
	struct pinctrl_state *pinctrl_idle;
};
struct pinctrl_cmd_desc {
	int dtype;
	struct pinctrl_data *pctrl_data;
	int mode;
};

/* dtype for gpio */
enum {
	DTYPE_GPIO_REQUEST,
	DTYPE_GPIO_FREE,
	DTYPE_GPIO_INPUT,
	DTYPE_GPIO_OUTPUT,
};

/* gpio desc */
struct gpio_desc {
	int dtype;
	int waittype;
	int wait;
	char *label;
	uint32_t *gpio;
	int value;
};

struct spi_cmd_desc {
	int reg_len;
	char *reg;
	int val_len;
	char *val;
	int waittype;
	int wait;
};

enum {
	IFBC_ORISE_CTL_8LINE = 0,
	IFBC_ORISE_CTL_16LINE,
	IFBC_ORISE_CTL_32LINE,
	IFBC_ORISE_CTL_FRAME,
};

typedef struct mipi_ifbc_division {
	uint32_t xres_div;
	uint32_t yres_div;
	uint32_t comp_mode;
	uint32_t pxl0_div2_gt_en;
	uint32_t pxl0_div4_gt_en;
	uint32_t pxl0_divxcfg;
	uint32_t pxl0_dsi_gt_en;
} mipi_ifbc_division_t;

struct ldi_panel_info {
	uint32_t h_back_porch;
	uint32_t h_front_porch;
	uint32_t h_pulse_width;

	/*
	** note: vbp > 8 if used overlay compose,
	** also lcd vbp > 8 in lcd power on sequence
	*/
	uint32_t v_back_porch;
	uint32_t v_front_porch;
	uint32_t v_pulse_width;

	uint8_t hsync_plr;
	uint8_t vsync_plr;
	uint8_t pixelclk_plr;
	uint8_t data_en_plr;

	/* for cabc */
	uint8_t dpi0_overlap_size;
	uint8_t dpi1_overlap_size;
};

/* DSI PHY configuration */
struct mipi_dsi_phy_ctrl {
	uint64_t lane_byte_clk;
	uint32_t clk_division;

	uint32_t clk_lane_lp2hs_time;
	uint32_t clk_lane_hs2lp_time;
	uint32_t data_lane_lp2hs_time;
	uint32_t data_lane_hs2lp_time;
	uint32_t clk2data_delay;
	uint32_t data2clk_delay;

	uint32_t clk_pre_delay;
	uint32_t clk_post_delay;
	uint32_t clk_t_lpx;
	uint32_t clk_t_hs_prepare;
	uint32_t clk_t_hs_zero;
	uint32_t clk_t_hs_trial;
	uint32_t clk_t_wakeup;
	uint32_t data_pre_delay;
	uint32_t data_post_delay;
	uint32_t data_t_lpx;
	uint32_t data_t_hs_prepare;
	uint32_t data_t_hs_zero;
	uint32_t data_t_hs_trial;
	uint32_t data_t_ta_go;
	uint32_t data_t_ta_get;
	uint32_t data_t_wakeup;

	uint32_t phy_stop_wait_time;

	uint32_t rg_vrefsel_vcm;
	uint32_t rg_hstx_ckg_sel;
	uint32_t rg_pll_fbd_div5f;
	uint32_t rg_pll_fbd_div1f;
	uint32_t rg_pll_fbd_2p;
	uint32_t rg_pll_enbwt;
	uint32_t rg_pll_fbd_p;
	uint32_t rg_pll_fbd_s;
	uint32_t rg_pll_pre_div1p;
	uint32_t rg_pll_pre_p;
	uint32_t rg_pll_vco_750m;
	uint32_t rg_pll_lpf_rs;
	uint32_t rg_pll_lpf_cs;
	uint32_t rg_pll_enswc;
	uint32_t rg_pll_chp;

	//only for Chicago<3660> use
	uint32_t pll_register_override;		//0x1E[0]
	uint32_t pll_power_down;			//0x1E[1]
	uint32_t rg_band_sel;				//0x1E[2]
	uint32_t rg_phase_gen_en;		//0x1E[3]
	uint32_t reload_sel;				//0x1E[4]
	uint32_t rg_pll_cp_p;				//0x1E[7:5]
	uint32_t rg_pll_refsel;				//0x16[1:0]
	uint32_t rg_pll_cp;				//0x16[7:5]
	uint32_t load_command;
};

struct mipi_panel_info {
	uint8_t vc;
	uint8_t lane_nums;
	uint8_t lane_nums_select_support;
	uint8_t color_mode;
	uint32_t dsi_bit_clk; /* clock lane(p/n) */
	uint32_t burst_mode;
	uint32_t max_tx_esc_clk;
	uint8_t non_continue_en;

	uint32_t dsi_bit_clk_val1;
	uint32_t dsi_bit_clk_val2;
	uint32_t dsi_bit_clk_val3;
	uint32_t dsi_bit_clk_val4;
	uint32_t dsi_bit_clk_val5;
	uint32_t dsi_bit_clk_upt;
	/*uint32_t dsi_pclk_rate;*/

	uint32_t hs_wr_to_time;

	// dphy config parameter adjust
	uint32_t clk_post_adjust;
	uint32_t clk_pre_adjust;
	uint32_t clk_pre_delay_adjust;
	uint32_t clk_t_hs_exit_adjust;
	uint32_t clk_t_hs_trial_adjust;
	uint32_t clk_t_hs_prepare_adjust;
	int clk_t_lpx_adjust;
	uint32_t clk_t_hs_zero_adjust;
	uint32_t data_post_delay_adjust;
	int data_t_lpx_adjust;
	uint32_t data_t_hs_prepare_adjust;
	uint32_t data_t_hs_zero_adjust;
	uint32_t data_t_hs_trial_adjust;
	uint32_t rg_vrefsel_vcm_adjust;

	//only for Chicago<3660> use
	uint32_t rg_vrefsel_vcm_clk_adjust;
	uint32_t rg_vrefsel_vcm_data_adjust;
};

#ifdef CONFIG_SBL_BY_FILE
struct sbl_panel_info_cfg {
	uint32_t sbl_enable;
	uint32_t balck_level;
	uint32_t white_level;
	uint32_t variance_intensity_space;
	uint32_t bright_dark_amp_limit;
	uint32_t slope_max;
	uint32_t slope_min;
	uint32_t dither_mode;
	uint32_t apical_dither;
	uint32_t frame_width;
	uint32_t frame_height;
	uint32_t logo_left;
	uint32_t logo_top;
	uint32_t *BL_linearity_LUT;
	uint32_t *BL_linearity_inverse_LUT;
	uint32_t *BL_att_LUT;
	uint32_t *AL_CALIB_LUT;
	uint32_t *asymmetry_lut;
	uint32_t *color_correctton_lut;
	uint32_t backlight_min;
	uint32_t backlight_max;
	uint32_t backlight_scale;
	uint32_t ambient_light_min;
	uint32_t filter_a;
	uint32_t filter_b;
	uint32_t calibration_a;
	uint32_t calibration_b;
	uint32_t calibration_c;
	uint32_t calibration_d;
	uint32_t strength_limit;
	uint32_t t_filter_control;
	uint32_t stabilization_iterations;
	uint32_t power_saving_coeff;
	uint32_t al_change_detect_coeff_tolerance;
	uint32_t al_change_detect_coeff_offset;
 };
#endif

struct sbl_panel_info {
	uint32_t strength_limit;
	uint32_t calibration_a;
	uint32_t calibration_b;
	uint32_t calibration_c;
	uint32_t calibration_d;
	uint32_t t_filter_control;
	uint32_t backlight_min;
	uint32_t backlight_max;
	uint32_t backlight_scale;
	uint32_t ambient_light_min;
	uint32_t filter_a;
	uint32_t filter_b;
	uint32_t logo_left;
	uint32_t logo_top;
	uint32_t variance_intensity_space;
	uint32_t slope_max;
	uint32_t slope_min;
#ifdef NEW_SBL_CTRL
	uint32_t *BL_linearity_LUT;
	uint32_t *BL_linearity_inverse_LUT;
	uint32_t *BL_att_LUT;
#endif
};

typedef struct dss_sharpness_bit {
	uint32_t sharp_en;
	uint32_t sharp_mode;

	uint32_t flt0_c0;
	uint32_t flt0_c1;
	uint32_t flt0_c2;

	uint32_t flt1_c0;
	uint32_t flt1_c1;
	uint32_t flt1_c2;

	uint32_t flt2_c0;
	uint32_t flt2_c1;
	uint32_t flt2_c2;

	uint32_t ungain;
	uint32_t ovgain;

	uint32_t lineamt1;
	uint32_t linedeten;
	uint32_t linethd2;
	uint32_t linethd1;

	uint32_t sharpthd1;
	uint32_t sharpthd1mul;
	uint32_t sharpamt1;

	uint32_t edgethd1;
	uint32_t edgethd1mul;
	uint32_t edgeamt1;
} sharp2d_t;


//the same as DDIC
struct dsc_panel_info {
	//DSC_CTRL
	uint32_t bits_per_pixel;
	uint32_t block_pred_enable;
	uint32_t linebuf_depth;
	uint32_t bits_per_component;

	//DSC_SLICE_SIZE
	uint32_t slice_width;
	uint32_t slice_height;

	//DSC_INITIAL_DELAY
	uint32_t initial_xmit_delay;

	//DSC_RC_PARAM1
	uint32_t first_line_bpg_offset;

	uint32_t mux_word_size;

	//RC_PARAM3
	//uint32_t final_offset;
	uint32_t initial_offset;

	//FLATNESS_QP_TH
	uint32_t flatness_max_qp;
	uint32_t flatness_min_qp;

	//RC_PARAM4
	uint32_t rc_edge_factor;
	uint32_t rc_model_size;

	//DSC_RC_PARAM5
	uint32_t rc_tgt_offset_lo;
	uint32_t rc_tgt_offset_hi;
	uint32_t rc_quant_incr_limit1;
	uint32_t rc_quant_incr_limit0;

	//DSC_RC_BUF_THRESH0
	uint32_t rc_buf_thresh0;
	uint32_t rc_buf_thresh1;
	uint32_t rc_buf_thresh2;
	uint32_t rc_buf_thresh3;

	//DSC_RC_BUF_THRESH1
	uint32_t rc_buf_thresh4;
	uint32_t rc_buf_thresh5;
	uint32_t rc_buf_thresh6;
	uint32_t rc_buf_thresh7;

	//DSC_RC_BUF_THRESH2
	uint32_t rc_buf_thresh8;
	uint32_t rc_buf_thresh9;
	uint32_t rc_buf_thresh10;
	uint32_t rc_buf_thresh11;

	//DSC_RC_BUF_THRESH3
	uint32_t rc_buf_thresh12;
	uint32_t rc_buf_thresh13;

	//DSC_RC_RANGE_PARAM0
	uint32_t range_min_qp0;
	uint32_t range_max_qp0;
	uint32_t range_bpg_offset0;
	uint32_t range_min_qp1;
	uint32_t range_max_qp1;
	uint32_t range_bpg_offset1;

	//DSC_RC_RANGE_PARAM1
	uint32_t range_min_qp2;
	uint32_t range_max_qp2;
	uint32_t range_bpg_offset2;
	uint32_t range_min_qp3;
	uint32_t range_max_qp3;
	uint32_t range_bpg_offset3;

	//DSC_RC_RANGE_PARAM2
	uint32_t range_min_qp4;
	uint32_t range_max_qp4;
	uint32_t range_bpg_offset4;
	uint32_t range_min_qp5;
	uint32_t range_max_qp5;
	uint32_t range_bpg_offset5;

	//DSC_RC_RANGE_PARAM3
	uint32_t range_min_qp6;
	uint32_t range_max_qp6;
	uint32_t range_bpg_offset6;
	uint32_t range_min_qp7;
	uint32_t range_max_qp7;
	uint32_t range_bpg_offset7;

	//DSC_RC_RANGE_PARAM4
	uint32_t range_min_qp8;
	uint32_t range_max_qp8;
	uint32_t range_bpg_offset8;
	uint32_t range_min_qp9;
	uint32_t range_max_qp9;
	uint32_t range_bpg_offset9;

	//DSC_RC_RANGE_PARAM5
	uint32_t range_min_qp10;
	uint32_t range_max_qp10;
	uint32_t range_bpg_offset10;
	uint32_t range_min_qp11;
	uint32_t range_max_qp11;
	uint32_t range_bpg_offset11;

	//DSC_RC_RANGE_PARAM6
	uint32_t range_min_qp12;
	uint32_t range_max_qp12;
	uint32_t range_bpg_offset12;
	uint32_t range_min_qp13;
	uint32_t range_max_qp13;
	uint32_t range_bpg_offset13;

	//DSC_RC_RANGE_PARAM7
	uint32_t range_min_qp14;
	uint32_t range_max_qp14;
	uint32_t range_bpg_offset14;
};

struct hisi_panel_info {
	uint32_t type;
	uint32_t xres;
	uint32_t yres;
	uint32_t width; //mm
	uint32_t height; //mm
	uint32_t bpp;
	uint32_t orientation;
	uint32_t bgr_fmt;
	uint32_t bl_set_type;
	uint32_t bl_min;
	uint32_t bl_max;
	uint32_t bl_default;
	uint32_t blpwm_precision_type;
	uint32_t blpwm_input_ena;
	uint32_t blpwm_in_num;
	uint32_t blpwm_input_precision;
	uint32_t bl_ic_ctrl_mode;
	uint64_t pxl_clk_rate;
	uint32_t pxl_clk_rate_div;
	uint32_t vsync_ctrl_type;
	uint8_t  fake_hdmi;
	uint8_t  reserved[3];

	//ifbc
	uint32_t ifbc_type;
	uint32_t ifbc_cmp_dat_rev0;
	uint32_t ifbc_cmp_dat_rev1;
	uint32_t ifbc_auto_sel;
	uint32_t ifbc_orise_ctl;
	uint32_t ifbc_orise_ctr;

	uint8_t lcd_init_step;
	uint8_t lcd_uninit_step;
	uint8_t lcd_uninit_step_support;
	uint8_t lcd_refresh_direction_ctrl;
	uint8_t lcd_adjust_support;

	uint8_t sbl_support;
	uint8_t color_temperature_support;
	uint8_t color_temp_rectify_support;
	uint32_t color_temp_rectify_R;
	uint32_t color_temp_rectify_G;
	uint32_t color_temp_rectify_B;
	uint8_t comform_mode_support;
	uint8_t cinema_mode_support;
	uint8_t frc_enable;
	uint8_t esd_enable;
	uint8_t esd_skip_mipi_check;
	uint8_t esd_recover_step;
	uint8_t dirty_region_updt_support;
	uint8_t dsi_bit_clk_upt_support;

	uint8_t panel_effect_support;

	uint8_t prefix_ce_support; //rch ce
	uint8_t prefix_sharpness1D_support; //rch sharpness 1D
	uint8_t prefix_sharpness2D_support; //rch sharpness 2D
	sharp2d_t *sharp2d_table;

	uint8_t gmp_support;
	uint8_t gamma_support;
	uint8_t gamma_type; //normal, cinema
	uint8_t xcc_support;
	uint8_t acm_support;
	uint8_t acm_ce_support;
#ifdef CONFIG_HISI_FB_3660
	uint8_t hiace_support;
	uint8_t dither_support;
	uint8_t arsr1p_support;
#endif

	//acm, acm lut
	uint32_t acm_valid_num;
	uint32_t r0_hh;
	uint32_t r0_lh;
	uint32_t r1_hh;
	uint32_t r1_lh;
	uint32_t r2_hh;
	uint32_t r2_lh;
	uint32_t r3_hh;
	uint32_t r3_lh;
	uint32_t r4_hh;
	uint32_t r4_lh;
	uint32_t r5_hh;
	uint32_t r5_lh;
	uint32_t r6_hh;
	uint32_t r6_lh;

	uint32_t cinema_acm_valid_num;
	uint32_t cinema_r0_hh;
	uint32_t cinema_r0_lh;
	uint32_t cinema_r1_hh;
	uint32_t cinema_r1_lh;
	uint32_t cinema_r2_hh;
	uint32_t cinema_r2_lh;
	uint32_t cinema_r3_hh;
	uint32_t cinema_r3_lh;
	uint32_t cinema_r4_hh;
	uint32_t cinema_r4_lh;
	uint32_t cinema_r5_hh;
	uint32_t cinema_r5_lh;
	uint32_t cinema_r6_hh;
	uint32_t cinema_r6_lh;

	uint32_t *acm_lut_hue_table;
	uint32_t acm_lut_hue_table_len;
	uint32_t *acm_lut_value_table;
	uint32_t acm_lut_value_table_len;
	uint32_t *acm_lut_sata_table;
	uint32_t acm_lut_sata_table_len;
	uint32_t *acm_lut_satr_table;
	uint32_t acm_lut_satr_table_len;

	uint32_t *cinema_acm_lut_hue_table;
	uint32_t cinema_acm_lut_hue_table_len;
	uint32_t *cinema_acm_lut_value_table;
	uint32_t cinema_acm_lut_value_table_len;
	uint32_t *cinema_acm_lut_sata_table;
	uint32_t cinema_acm_lut_sata_table_len;
	uint32_t *cinema_acm_lut_satr_table;
	uint32_t cinema_acm_lut_satr_table_len;

	//acm for 3660
	uint32_t *acm_lut_satr0_table;
	uint32_t acm_lut_satr0_table_len;
	uint32_t *acm_lut_satr1_table;
	uint32_t acm_lut_satr1_table_len;
	uint32_t *acm_lut_satr2_table;
	uint32_t acm_lut_satr2_table_len;
	uint32_t *acm_lut_satr3_table;
	uint32_t acm_lut_satr3_table_len;
	uint32_t *acm_lut_satr4_table;
	uint32_t acm_lut_satr4_table_len;
	uint32_t *acm_lut_satr5_table;
	uint32_t acm_lut_satr5_table_len;
	uint32_t *acm_lut_satr6_table;
	uint32_t acm_lut_satr6_table_len;
	uint32_t *acm_lut_satr7_table;
	uint32_t acm_lut_satr7_table_len;

	//gamma, igm, gmp, xcc
	uint32_t *gamma_lut_table_R;
	uint32_t *gamma_lut_table_G;
	uint32_t *gamma_lut_table_B;
	uint32_t gamma_lut_table_len;
	uint32_t *cinema_gamma_lut_table_R;
	uint32_t *cinema_gamma_lut_table_G;
	uint32_t *cinema_gamma_lut_table_B;
	uint32_t cinema_gamma_lut_table_len;
	uint32_t *igm_lut_table_R;
	uint32_t *igm_lut_table_G;
	uint32_t *igm_lut_table_B;
	uint32_t igm_lut_table_len;
	uint32_t *gmp_lut_table_low32bit;
	uint32_t *gmp_lut_table_high4bit;
	uint32_t gmp_lut_table_len;
	uint32_t *xcc_table;
	uint32_t xcc_table_len;

	//arsr1p lut
	uint32_t *pgainlsc0;
	uint32_t *pgainlsc1;
	uint32_t pgainlsc_len;
	uint32_t *hcoeff0y;
	uint32_t *hcoeff1y;
	uint32_t *hcoeff2y;
	uint32_t *hcoeff3y;
	uint32_t *hcoeff4y;
	uint32_t *hcoeff5y;
	uint32_t hcoeffy_len;
	uint32_t *vcoeff0y;
	uint32_t *vcoeff1y;
	uint32_t *vcoeff2y;
	uint32_t *vcoeff3y;
	uint32_t *vcoeff4y;
	uint32_t *vcoeff5y;
	uint32_t vcoeffy_len;
	uint32_t *hcoeff0uv;
	uint32_t *hcoeff1uv;
	uint32_t *hcoeff2uv;
	uint32_t *hcoeff3uv;
	uint32_t hcoeffuv_len;
	uint32_t *vcoeff0uv;
	uint32_t *vcoeff1uv;
	uint32_t *vcoeff2uv;
	uint32_t *vcoeff3uv;
	uint32_t vcoeffuv_len;

	struct spi_device *spi_dev;
	struct ldi_panel_info ldi;
	struct mipi_panel_info mipi;
	struct sbl_panel_info smart_bl;
#ifdef CONFIG_SBL_BY_FILE
	struct sbl_panel_info_cfg smart_bl_cfg;
#endif
	struct dsc_panel_info vesa_dsc;
	struct lcd_dirty_region_info dirty_region_info;

	struct mipi_dsi_phy_ctrl dsi_phy_ctrl;

	// Contrast Alogrithm
	struct ce_algorithm_parameter ce_alg_param;
};

struct hisi_fb_data_type;

struct hisi_fb_panel_data {
	struct hisi_panel_info *panel_info;

	/* function entry chain */
	int (*set_fastboot) (struct platform_device *pdev);
	int (*on) (struct platform_device *pdev);
	int (*off) (struct platform_device *pdev);
	int (*lp_ctrl) (struct platform_device *pdev, bool lp_enter);
	int (*remove) (struct platform_device *pdev);
	int (*set_backlight) (struct platform_device *pdev, uint32_t bl_level);
	int (*sbl_ctrl) (struct platform_device *pdev, int enable);
	int (*vsync_ctrl) (struct platform_device *pdev, int enable);
	int (*frc_handle) (struct platform_device *pdev, int fps);
	int (*esd_handle) (struct platform_device *pdev);
	int (*set_display_region) (struct platform_device *pdev, struct dss_rect *dirty);
	int (*set_pixclk_rate) (struct platform_device *pdev);
	int (*set_display_resolution) (struct platform_device *pdev);
	int (*get_lcd_id) (struct platform_device *pdev);

	ssize_t (*lcd_model_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_cabc_mode_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_cabc_mode_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_check_reg) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_mipi_detect) (struct platform_device *pdev, char *buf);
	ssize_t (*mipi_dsi_bit_clk_upt_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*mipi_dsi_bit_clk_upt_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_hkadc_debug_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_hkadc_debug_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_gram_check_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_gram_check_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_dynamic_sram_checksum_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_dynamic_sram_checksum_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_color_temperature_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_color_temperature_show) (struct platform_device *pdev, char *buf);
	ssize_t (*led_rg_lcd_color_temperature_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*led_rg_lcd_color_temperature_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_comform_mode_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_comform_mode_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_cinema_mode_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_cinema_mode_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_support_mode_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_support_mode_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_voltage_enable_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_bist_check) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_sleep_ctrl_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_sleep_ctrl_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_test_config_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_test_config_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_support_checkmode_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_lp2hs_mipi_check_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_lp2hs_mipi_check_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_inversion_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_inversion_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_scan_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_scan_show) (struct platform_device *pdev, char *buf);
	ssize_t (*amoled_pcd_errflag_check)(struct platform_device *pdev, char *buf);
	ssize_t (*lcd_hbm_ctrl_store)(struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_hbm_ctrl_show)(struct platform_device *pdev, char *buf);
	ssize_t (*sharpness2d_table_store)(struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*sharpness2d_table_show)(struct platform_device *pdev, char *buf);
	ssize_t (*panel_info_show)(struct platform_device *pdev, char *buf);
	ssize_t (*lcd_acm_state_store) (struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_acm_state_show) (struct platform_device *pdev, char *buf);
	ssize_t (*lcd_acl_ctrl_store)(struct platform_device *pdev, const char *buf, size_t count);
	ssize_t (*lcd_acl_ctrl_show)(struct platform_device *pdev, char *buf);

	struct platform_device *next;
};

#if defined (CONFIG_HUAWEI_DSM)
struct lcd_reg_read_t {
	u8 reg_addr;				//register address
	u32 expected_value;			//the expected value should returned when lcd is in good condtion
	u32 read_mask;				//set read mask if there are bits should ignored
	char *reg_name;				//register name
};
#endif


/*******************************************************************************
** FUNCTIONS PROTOTYPES
*/
#define MIPI_DPHY_NUM	(2)

extern uint32_t g_dts_resouce_ready;
extern mipi_ifbc_division_t g_mipi_ifbc_division[MIPI_DPHY_NUM][IFBC_TYPE_MAX];

int resource_cmds_tx(struct platform_device *pdev,
	struct resource_desc *cmds, int cnt);
int vcc_cmds_tx(struct platform_device *pdev, struct vcc_desc *cmds, int cnt);
int pinctrl_cmds_tx(struct platform_device *pdev, struct pinctrl_cmd_desc *cmds, int cnt);
int gpio_cmds_tx(struct gpio_desc *cmds, int cnt);
extern struct spi_device *g_spi_dev;
int spi_cmds_tx(struct spi_device *spi, struct spi_cmd_desc *cmds, int cnt);

int panel_next_set_fastboot(struct platform_device *pdev);
int panel_next_on(struct platform_device *pdev);
int panel_next_off(struct platform_device *pdev);
int panel_next_lp_ctrl(struct platform_device *pdev, bool lp_enter);
int panel_next_remove(struct platform_device *pdev);
int panel_next_set_backlight(struct platform_device *pdev, uint32_t bl_level);
int panel_next_sbl_ctrl(struct platform_device *pdev, int enable);
int panel_next_vsync_ctrl(struct platform_device *pdev, int enable);
int panel_next_frc_handle(struct platform_device *pdev, int fps);
int panel_next_esd_handle(struct platform_device *pdev);
int panel_next_set_display_region(struct platform_device *pdev, struct dss_rect *dirty);
int panel_next_get_lcd_id(struct platform_device *pdev);

ssize_t panel_next_lcd_model_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_cabc_mode_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_cabc_mode_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_check_reg(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_mipi_detect(struct platform_device *pdev, char *buf);
ssize_t panel_next_mipi_dsi_bit_clk_upt_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_mipi_dsi_bit_clk_upt_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_hkadc_debug_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_hkadc_debug_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_gram_check_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_gram_check_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_dynamic_sram_checksum_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_dynamic_sram_checksum_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_voltage_enable_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_bist_check(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_support_checkmode_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_panel_info_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_sleep_ctrl_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_sleep_ctrl_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_test_config_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_test_config_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_support_mode_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_support_mode_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_lp2hs_mipi_check_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_lp2hs_mipi_check_store(struct platform_device *pdev, 	const char *buf, size_t count);
ssize_t panel_next_amoled_pcd_errflag_check(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_hbm_ctrl_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_hbm_ctrl_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_lcd_acl_ctrl_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_lcd_acl_ctrl_show(struct platform_device *pdev, char *buf);
ssize_t panel_next_sharpness2d_table_store(struct platform_device *pdev, const char *buf, size_t count);
ssize_t panel_next_sharpness2d_table_show(struct platform_device *pdev, char *buf);

int hisi_pwm_set_backlight(struct hisi_fb_data_type *hisifd, uint32_t bl_level);
int hisi_pwm_off(struct platform_device *pdev);
int hisi_pwm_on(struct platform_device *pdev);

int hisi_blpwm_set_backlight(struct hisi_fb_data_type *hisifd, uint32_t bl_level);

int hisi_blpwm_off(struct platform_device *pdev);
int hisi_blpwm_on(struct platform_device *pdev);

int hisi_sh_blpwm_set_backlight(struct hisi_fb_data_type *hisifd, uint32_t bl_level);
int hisi_sh_blpwm_off(struct platform_device *pdev);
int hisi_sh_blpwm_on(struct platform_device *pdev);

int hisi_lcd_backlight_on(struct platform_device *pdev);
int hisi_lcd_backlight_off(struct platform_device *pdev);

bool is_ldi_panel(struct hisi_fb_data_type *hisifd);
bool is_mipi_cmd_panel(struct hisi_fb_data_type *hisifd);
bool is_mipi_cmd_panel_ext(struct hisi_panel_info *pinfo);
bool is_mipi_video_panel(struct hisi_fb_data_type *hisifd);
bool is_mipi_panel(struct hisi_fb_data_type *hisifd);
bool is_dual_mipi_panel(struct hisi_fb_data_type *hisifd);
bool is_dual_mipi_panel_ext(struct hisi_panel_info *pinfo);
bool is_ifbc_panel(struct hisi_fb_data_type *hisifd);
bool is_ifbc_vesa_panel(struct hisi_fb_data_type *hisifd);
bool mipi_panel_check_reg (struct hisi_fb_data_type *hisifd, uint32_t *read_value);
int mipi_ifbc_get_rect(struct hisi_fb_data_type *hisifd, struct dss_rect *rect);
bool is_hisi_writeback_panel(struct hisi_fb_data_type *hisifd);

void hisi_fb_device_set_status0(uint32_t status);
int hisi_fb_device_set_status1(struct hisi_fb_data_type *hisifd);
bool hisi_fb_device_probe_defer(uint32_t panel_type, uint32_t bl_type);

#if defined (CONFIG_HUAWEI_DSM)
void panel_check_status_and_report_by_dsm(struct lcd_reg_read_t *lcd_status_reg, int cnt, char __iomem *mipi_dsi0_base);
#endif


#endif /* HISI_FB_PANEL_H */
