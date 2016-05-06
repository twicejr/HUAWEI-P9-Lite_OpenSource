/*
 *  Hisilicon K3 soc camera ISP driver header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __MINI_K3_ISPV1_H__
#define __MINI_K3_ISPV1_H__

#include "k3_ispv1_comm.h"

/* REGISTER READ/WRITE DEFINITION */
#define GETREG8(reg) \
	(((reg) >= COMMAND_BUFFER_END) ? \
	(ioread8_mutex((mini_isp_hw_data.base + (reg)))) : \
	(ioread8_mutex((mini_isp_hw_data.base + BIG_ENDIAN((reg))))))

#define GETREG32(reg, value) \
	do { \
		(value) = (GETREG8(reg) << 24) + \
			(GETREG8((reg) + 1) << 16) + \
			(GETREG8((reg) + 2) << 8) + \
			(GETREG8((reg) + 3)); \
	} while (0)

#define GETREG16(reg, value) \
	do { \
		(value) = (GETREG8(reg) << 8) + \
		(GETREG8((reg) + 1)); \
	} while (0)

typedef struct _mini_irq_reg {
	u32 irq_status;
	u32 mac_irqstatus_h;
	u32 mac_irqstatus_l;

	u32 mcu_cmd_finish;

	u8  mac_irqstatus_h_done_cnt;
} mini_irq_reg_t;


typedef struct _mini_flash_weight {
	u32 preflash_env;
	u32 preflash_flash;
	u32 capflash_env;
	u32 capflash_flash;
} mini_flash_weight_t;

typedef struct _mini_aec_data {
	u32 gain;
	u32 expo;
	u32 lum;
	u32 lum_max; /* using for save max lum in 4x4 raw lum stat window */
	u32 lum_sum;
} mini_aec_data_t;


typedef struct _mini_isp_hw_data {

	struct semaphore sem_cmd_done;
	struct semaphore sem_cap_raw_cmd_done;
	struct semaphore sem_proc_img_cmd_done;
	struct semaphore sem_wrt_done;
	spinlock_t irq_status_lock;

	/* camera work mode */
	camera_state cur_state;
	struct mini_i2c_t i2c_config;

	u8 __iomem * base;
	u32 irq;
	mini_irq_reg_t irq_val;
	struct clk *isp_clk;        /* sclk, isp clk */
	struct clk *ispmipi_clk;    /* mipi ref clk */
	struct clk *isp_aclk;       /* aclk, isp axi master clk */
    struct clk *isp_csi_clk;    /* csi APB MUX clk */
    struct clk *isp_hclk;       /* hclk, AHB Slave clk */
    struct clk *dsppll_clk;     /* dsppll */
    struct clk *isp_gated_clk_mux;  /* gated clock */
	struct regulator *inter_ldo;

	u32 pix_fmt;
	mini_uv_offset  preview_uv_offset;
	mini_uv_offset  capture_uv_offset;

	u8 command_set_id;

	mini_aec_data_t preview_ae;
	mini_awb_gain_t preview_awb;
	mini_aec_data_t preflash_ae;
	u32 preview_ratio_lum;

	mini_aecawb_step_t aecawb_step;
	mini_awb_gain_t flash_preset_awb;
	bool flash_resume;
	bool ae_resume;
	mini_awb_gain_t led_awb[2];
	FLASH_AWBTEST_POLICY awb_test; /* used to save policy of flash awb test. */

	isp_process_mode_t process_mode;

	volatile u8 aec_cmd_id;
	u32 frame_count;

	mini_data_queue_t *data_queue_ref;

	offline_state_t	offline_state;
	bool preview_stop;
	u8 fps_max;
	u8 fps_min;
	u8 fps_mid;

	camera_flash	flash_mode;

	u32 ratio_factor;
} mini_isp_hw_data_t;

extern mini_isp_hw_data_t mini_isp_hw_data;

static inline void SETREG8(u32 reg, u8 value) {
	(reg >= COMMAND_BUFFER_END) ?
		iowrite8_mutex(value, mini_isp_hw_data.base + reg) :
		iowrite8_mutex(value, mini_isp_hw_data.base + BIG_ENDIAN(reg));
}

/* Used for tune ops and AF functions to get isp_data handler */
int mini_ispv1_tune_ops_init(mini_k3_isp_data *ispdata);
void mini_ispv1_tune_ops_exit(void);
void mini_ispv1_tune_ops_prepare(camera_state state);
void mini_ispv1_tune_ops_withdraw(camera_state state);

/* for tune ops */
int mini_ispv1_set_anti_shaking_block(int blocksize);
int mini_ispv1_set_anti_shaking(camera_anti_shaking flag);
int mini_ispv1_get_anti_shaking_coordinate(mini_coordinate_s *coordinate);

/*
 * set ISO: convert ISO to gain and set to sensor
 */
int mini_ispv1_set_iso(camera_iso iso);

int mini_ispv1_iso2gain(int iso, bool summary);

int mini_ispv1_gain2iso(int gain, bool summary);

u32 mini_get_writeback_cap_expo(void);
u32 mini_get_writeback_cap_gain(void);

/* only useful for ISO auto mode */
int mini_ispv1_get_actual_iso(void);

int mini_ispv1_get_exposure_time(void);

u32 mini_ispv1_get_awb_gain(int withShift);
u32 mini_ispv1_get_focus_code(void);
u32 mini_ispv1_get_focus_rect(mini_camera_rect_s *rect);

u32 mini_ispv1_get_expo_line(void);
u32 mini_ispv1_get_sensor_vts(void);

u32 mini_ispv1_get_current_ccm_rgain(void);
u32 mini_ispv1_get_current_ccm_bgain(void);

int mini_ispv1_get_fps(mini_camera_sensor *sensor, camera_fps fps);
int mini_ispv1_set_fps(mini_camera_sensor *sensor, camera_fps fps, u8 value);

/*
 * set exposure value
 */
int mini_ispv1_set_ev(int ev);

/*
 * set anti_banding
 */
int mini_ispv1_set_anti_banding(camera_anti_banding banding);
int mini_ispv1_get_anti_banding(void);

/*
 * related to sensor.
 */
int mini_ispv1_set_awb(camera_white_balance awb_mode);

/*also called edge enhancement*/
int mini_ispv1_set_sharpness(camera_sharpness sharpness);
int mini_ispv1_set_saturation(camera_saturation saturation);
int mini_ispv1_set_contrast(camera_contrast contrast);
int mini_ispv1_set_scene(camera_scene scene);
int mini_ispv1_set_brightness(camera_brightness brightness);

int mini_ispv1_switch_brightness(camera_state state, camera_brightness brightness);
int mini_ispv1_switch_contrast(camera_state state, camera_contrast contrast);

int mini_ispv1_set_effect(camera_effects effect);

/*
 * before start_preview or start_capture, it should be called to update size information
 */
int mini_ispv1_update_LENC_scale(u32 inwidth, u32 inheight);

/*using for write ad register(set position) of vcm driver ic by i2c bus*/
int mini_ispv1_write_vcm(u8 i2c_addr, u16 reg, u16 val, i2c_length length, int mutex_wait);

int mini_ispv1_get_current_vts(mini_camera_sensor *sensor);
int mini_ispv1_get_current_fps(mini_camera_sensor *sensor);
int mini_ispv1_get_band_threshold(mini_camera_sensor *sensor, camera_anti_banding banding);
void mini_ispv1_set_fps_lock(int lock);
void mini_ispv1_preview_done_do_tune(void);
void mini_ispv1_cmd_id_do_ecgc(struct work_struct *work);
void mini_ispv1_set_aecagc_mode(aecagc_mode_t mode);
void mini_ispv1_set_awb_mode(awb_mode_t mode);

void mini_ispv1_save_aecawb_step(mini_aecawb_step_t *step);
void mini_ispv1_config_aecawb_step(bool flash_mode, mini_aecawb_step_t *step);
void mini_ispv1_check_flash_prepare(void);

void mini_ispv1_get_wb_value(mini_awb_gain_t *awb);
void mini_ispv1_set_wb_value(mini_awb_gain_t *awb);
bool mini_ispv1_copy_preview_data(u8 *dest, mini_camera_rect_s *rect);

int mini_ispv1_get_frame_rate_level(void);
void mini_ispv1_set_frame_rate_level(int level);

camera_frame_rate_state mini_ispv1_get_frame_rate_state(void);
void mini_ispv1_set_frame_rate_state(camera_frame_rate_state state);

bool mini_ae_is_need_flash(mini_camera_sensor *sensor, mini_aec_data_t *ae_data, u32 target_y_low);

bool mini_ispv1_is_hdr_movie_mode(void);

void mini_ispv1_red_clip_correction(void);
int mini_ispv1_uv_stat_init(void);
void mini_ispv1_uv_stat_excute(void);
void mini_ispv1_uv_stat_exit(void);
int mini_ispv1_do_aeag_wq_init(void);
int mini_ispv1_aeag_excute(void);
int mini_ispv1_aeag_exit(void);
void mini_ispv1_switch_dns(mini_camera_sensor *sensor, camera_state state, bool flash_on, u32 expo_line);
void mini_ispv1_refresh_yuv_crop_pos(void);
void mini_ispv1_get_banding_step(mini_camera_sensor *sensor, u32 frame_index, u32 *step_50hz, u32 *step_60hz);
#endif /*__K3_ISPV1_H__ */
/********************************* END ***********************************************/
