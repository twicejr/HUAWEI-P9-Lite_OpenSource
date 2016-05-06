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

#ifndef __K3_ISPV1_H__
#define __K3_ISPV1_H__

#include "k3_ispv1_comm.h"

/* REGISTER READ/WRITE DEFINITION */
#define GETREG8(reg) \
	(((reg) >= COMMAND_BUFFER_END) ? \
	(ioread8_mutex((isp_hw_data.base + (reg)))) : \
	(ioread8_mutex((isp_hw_data.base + BIG_ENDIAN((reg))))))

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

typedef struct _meta_data_info_of_raw_imgdata {
    u16 img_width;
    u16 img_height;
    u16 analog_sensor_gain;
    u16 exposure_line;
    u16 sensor_vts;
    u16 awb_b_gain1;
    u16 awb_g_gain1;
    u16 awb_r_gain1;
    u16 awb_b_gain2;
    u16 awb_gb_gain2;
    u16 awb_gr_gain2;
    u16 awb_r_gain2;
    u8 black_level;
    u8 bayer_order;
} meta_data_info_of_raw_imgdata_t;

typedef struct _irq_reg {
	u32 irq_status;
	u32 mac_irqstatus_h;
	u32 mac_irqstatus_l;

	u32 mcu_cmd_finish;

	u8  mac_irqstatus_h_done_cnt;
} irq_reg_t;


typedef struct _flash_weight {
	u32 preflash_env;
	u32 preflash_flash;
	u32 capflash_env;
	u32 capflash_flash;
} flash_weight_t;

typedef struct _aec_data {
	u32 gain;
	u32 expo;
	u32 lum;
	u32 lum_max; /* using for save max lum in 4x4 raw lum stat window */
	u32 lum_sum;
} aec_data_t;


typedef struct _isp_hw_data {
    struct semaphore sem_cmd_busy;          /* cmdset mutex */
	struct semaphore sem_cmd_done;
	struct semaphore sem_cap_raw_cmd_done;
	struct semaphore sem_proc_img_cmd_done;
	struct semaphore sem_wrt_done;
	spinlock_t irq_status_lock;

	/* camera work mode */
	camera_state cur_state;
	struct i2c_t i2c_config;

	u8 __iomem * base;
	u32 irq;
	irq_reg_t irq_val;
	struct clk *isp_clk;        /* sclk, isp clk */
	struct clk *ispmipi_clk;    /* mipi ref clk */
	struct clk *isp_aclk;       /* aclk, isp axi master clk */
    struct clk *isp_csi_clk;    /* csi APB MUX clk */
    struct clk *isp_hclk;       /* hclk, AHB Slave clk */
    struct clk *clk_medpll_src_gated;
    //struct clk *media_pll_clk;     /* media pll */ /*not need enable medpll clock, it's invalid. 20140505*/

    /*for common image, z62576, 20140429, begin*/
    u32 clk_freq;
    u32 mipi_clk_freq;

    u32 complt_timeout;
    /*for common image, z62576, 20140429, end*/

	u32 pix_fmt;
	uv_offset  preview_uv_offset;
	uv_offset  capture_uv_offset;

	u8 command_set_id;

	aec_data_t preview_ae;
	awb_gain_t preview_awb;
	aec_data_t preflash_ae;
	u32 preview_ratio_lum;

	aecawb_step_t aecawb_step;
	awb_gain_t flash_preset_awb;
	bool flash_resume;
	bool ae_resume;
	awb_gain_t led_awb[2];
	FLASH_AWBTEST_POLICY awb_test; /* used to save policy of flash awb test. */

	isp_process_mode_t process_mode;

	volatile u8 aec_cmd_id;
	u32 frame_count;

	data_queue_t *data_queue_ref;
	int           rsv_buf_use_cnt[2];/* left&right buf using rsv buf counter. */

	offline_state_t	offline_state;
	bool preview_stop;
	u8 fps_max;
	u8 fps_min;
	u8 fps_mid;

	camera_flash	flash_mode;

	u32 ratio_factor;
	stream_state  sensor_stream_state;
} isp_hw_data_t;

extern isp_hw_data_t isp_hw_data;

static inline void SETREG8(u32 reg, u8 value) {
	(reg >= COMMAND_BUFFER_END) ?
		iowrite8_mutex(value, isp_hw_data.base + reg) :
		iowrite8_mutex(value, isp_hw_data.base + BIG_ENDIAN(reg));
}

/* Used for tune ops and AF functions to get isp_data handler */
int ispv1_tune_ops_init(k3_isp_data *ispdata);
void ispv1_tune_ops_exit(void);
void ispv1_tune_ops_prepare(camera_state state);
void ispv1_tune_ops_withdraw(camera_state state);

/* for tune ops */
int ispv1_set_anti_shaking_block(int blocksize);
int ispv1_set_anti_shaking(camera_anti_shaking flag);
int ispv1_get_anti_shaking_coordinate(coordinate_s *coordinate);

/*
 * set ISO: convert ISO to gain and set to sensor
 */
int ispv1_set_iso(camera_iso iso);

int ispv1_iso2gain(int iso, bool summary);

int ispv1_gain2iso(int gain, bool summary);

u32 get_writeback_cap_expo(void);
u32 get_writeback_cap_gain(void);

/* only useful for ISO auto mode */
int ispv1_get_actual_iso(void);

int ispv1_get_exposure_time(void);

u32 ispv1_get_awb_gain(int withShift);
u32 ispv1_get_focus_code(void);
u32 ispv1_get_focus_rect(camera_rect_s *rect);

u32 ispv1_get_expo_line(void);
u32 ispv1_get_sensor_vts(void);

u32 ispv1_get_current_ccm_rgain(void);
u32 ispv1_get_current_ccm_bgain(void);

int ispv1_get_fps(camera_sensor *sensor, camera_fps fps);
int ispv1_set_fps(camera_sensor *sensor, camera_fps fps, u8 value);

/*
 * set exposure value
 */
int ispv1_set_ev(int ev);

/*
 * set anti_banding
 */
int ispv1_set_anti_banding(camera_anti_banding banding);
int ispv1_get_anti_banding(void);

/*
 * related to sensor.
 */
int ispv1_set_awb(camera_white_balance awb_mode);

/*also called edge enhancement*/
int ispv1_set_sharpness(camera_sharpness sharpness);
int ispv1_set_saturation(camera_saturation saturation);
int ispv1_set_contrast(camera_contrast contrast);
int ispv1_set_scene(camera_scene scene);
int ispv1_set_brightness(camera_brightness brightness);

int ispv1_switch_brightness(camera_state state, camera_brightness brightness);
int ispv1_switch_contrast(camera_state state, camera_contrast contrast);

int ispv1_set_effect(camera_effects effect);

/*
 * before start_preview or start_capture, it should be called to update size information
 */
int ispv1_update_LENC_scale(u32 inwidth, u32 inheight);

/*using for write ad register(set position) of vcm driver ic by i2c bus*/
int ispv1_write_vcm(u8 i2c_addr, u16 reg, u16 val, i2c_length length, int mutex_wait);

int ispv1_get_current_vts(camera_sensor *sensor);
int ispv1_get_current_fps(camera_sensor *sensor);
int ispv1_get_band_threshold(camera_sensor *sensor, camera_anti_banding banding);
void ispv1_set_fps_lock(int lock);
void ispv1_preview_done_do_tune(void);
void ispv1_cmd_id_do_ecgc(struct work_struct *work);
void ispv1_set_aecagc_mode(aecagc_mode_t mode);
void ispv1_set_awb_mode(awb_mode_t mode);

void ispv1_read_i2c_buf(struct isp_I2C_t *addr, u8 num, u8 start, i2c_length len);

void ispv1_save_aecawb_step(aecawb_step_t *step);
void ispv1_config_aecawb_step(bool flash_mode, aecawb_step_t *step);
void ispv1_check_flash_prepare(void);

void ispv1_get_wb_value(awb_gain_t *awb);
void ispv1_set_wb_value(awb_gain_t *awb);
bool ispv1_copy_preview_data(u8 *dest, camera_rect_s *rect);

int ispv1_get_frame_rate_level(void);
void ispv1_set_frame_rate_level(int level);

camera_frame_rate_state ispv1_get_frame_rate_state(void);
void ispv1_set_frame_rate_state(camera_frame_rate_state state);

bool ae_is_need_flash(camera_sensor *sensor, aec_data_t *ae_data, u32 target_y_low);

bool ispv1_is_hdr_movie_mode(void);

void ispv1_red_clip_correction(void);
int ispv1_uv_stat_init(void);
void ispv1_uv_stat_excute(void);
void ispv1_uv_stat_exit(void);
int ispv1_do_aeag_wq_init(void);
int ispv1_aeag_excute(void);
int ispv1_aeag_exit(void);
void ispv1_switch_dns(camera_sensor *sensor, camera_state state, bool flash_on, u32 expo_line);
void ispv1_refresh_yuv_crop_pos(void);
void ispv1_get_banding_step(camera_sensor *sensor, u32 frame_index, u32 *step_50hz, u32 *step_60hz);
#endif /*__K3_ISPV1_H__ */
/********************************* END ***********************************************/
