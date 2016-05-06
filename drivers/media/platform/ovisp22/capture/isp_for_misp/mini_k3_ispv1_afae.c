/*
 *  Hisilicon K3 soc camera ISP driver source file
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

#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/ctype.h>
#include <linux/slab.h>
#include <linux/pagemap.h>
#include <linux/vmalloc.h>
#include <linux/fb.h>
#include <linux/pci.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <asm/io.h>
#include <asm/bug.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
//#include <linux/android_pmem.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/clk.h>
#include <linux/time.h>

#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>

#include <linux/workqueue.h>
#include <linux/semaphore.h>

#include "mini_cam_util.h"
#include "mini_cam_dbg.h"
#include "mini_k3_isp.h"
#include "mini_k3_ispv1.h"
#include "mini_k3_ispv1_afae.h"
#include "mini_k3_isp_io.h"

//#include "mach/irqs.h"

#define LOG_TAG "K3_ISPV1_AFAE"
#include "mini_cam_log.h"
#include "camera_agent.h"
#define ISP_MAX_FOCUSED_WIN		4
//#define ISP_MAX_FOCUS_WIN		25

/* same as metering default CWA area */
#define DEFAULT_AF_WIDTH_PERCENT	20
#define DEFAULT_AF_HEIGHT_PERCENT	25

/* with stabilizer, max size is larger than 1080P. */
#define MAX_PREVIEW_WIDTH	2112
#define MAX_PREVIEW_HEIGHT	1200

#define AF_SINGLE_WINMODE_ONLY

#ifdef __KERNEL__
#define CAM_WAIT_FOCUS_TIMEOUT      CONFIG_CAMERA_WAIT_FOCUS_TIMEOUT
#endif

#ifndef CAM_WAIT_FOCUS_TIMEOUT
#define CAM_WAIT_FOCUS_TIMEOUT   (100)
#endif
#if 0 //by wind
typedef struct _focus_win_info_s{
	u32 left;
	u32 top;
	u32 width;
	u32 height;

	u32 width1;
	u32 height1;

	u32 weight[ISP_MAX_FOCUS_WIN];
} mini_focus_win_info_s;
#endif
typedef struct _focused_result_s {
	u32 focused_win_num;
	u32 focused_win[ISP_MAX_FOCUSED_WIN];
} focused_result_s;

/* point to global isp_data */
extern mini_k3_isp_data *mini_this_ispdata;

static u32 raw_unit_area;
mini_ispv1_afae_ctrl *mini_afae_ctrl;
static camera_metering this_metering = CAMERA_METERING_CWA;
static struct semaphore sem_af_schedule;

mini_axis_triple mini_mXYZ;

#define AF_TIME_PRINT
#ifdef AF_TIME_PRINT
	static struct timeval tv_start, tv_end;
#endif

#if 0
static int __attribute__((unused)) ispv1_get_merged_rect(mini_focus_area_s *area,
				mini_camera_rect_s *yuv_rect, u32 preview_width, u32 preview_height);
static int __attribute__((unused)) ispv1_get_focus_win_info(mini_camera_rect_s *raw_rect,
				mini_focus_win_info_s *win_info, int *binning);
static int __attribute__((unused)) ispv1_get_map_table(mini_focus_area_s *area,
				mini_focus_win_info_s *win_info, int *map_table);
#endif

//static bool ispv1_check_rect_differ(mini_camera_rect_s *rect1, mini_camera_rect_s *rect2, u32 preview_width, u32 preview_height);

static struct workqueue_struct *af_start_work_queue;
static struct work_struct af_start_work;
static void ispv1_af_start_work_func(struct work_struct *work);

static bool ispv1_setreg_vcm_code(u32 vcm_code);
static void ispv1_focus_vcm_go_infinite(u8 delay_flag);

//static void ispv1_setreg_focus_win(mini_focus_win_info_s *win_info);
static int ispv1_setreg_vcm_DLC_mode(void);
static int ispv1_setreg_vcm_lsc_mode(u16 para1, u16 para2);
static int ispv1_setreg_af_mode(camera_af_mode mode);
static int ispv1_getreg_focus_result(focused_result_s *result, int multi_win);

static int ispv1_set_focus_mode_done(camera_focus focus_mode);
static int ispv1_set_focus_area_done(mini_focus_area_s *area, u32 zoom);

static u32 ispv1_focus_get_win_lum(mini_lum_win_info_s *lum_info);

static void ispv1_assistant_af(bool action);
static bool ispv1_focus_need_flash(u32 cur_lum, u32 cur_gain, bool summary, bool support_summary);
static bool ispv1_af_flash_needed(mini_camera_sensor *sensor, camera_flash flash_mode, mini_lum_win_info_s lum_info);
static void ispv1_af_flash_check_open(void);
static void ispv1_af_flash_check_close(void);

static void ispv1_focus_status_reset(void);

static bool ispv1_af_need_wait_stable(u8 stage, u8 hold_cnt);
static void ispv1_af_range_cal(mini_af_run_param *af_info, mini_pos_info *curr, af_run_stage next_stage);
static void ispv1_vcaf_range_cal(mini_af_run_param *af_info, mini_pos_info *curr, af_run_stage next_stage, FOCUS_STATUS result);
static af_run_stage ispv1_af_recognise_curve(mini_af_run_param *af_info, mini_pos_info *curr, mini_vcm_info_s *vcm);
static af_run_stage ispv1_vcaf_recognise_curve(mini_af_run_param *af_info, mini_pos_info *curr, mini_vcm_info_s *vcm, u32 *reserved);
static af_run_stage ispv1_af_search_top(mini_af_run_param *af_info, mini_pos_info *curr, mini_vcm_info_s *vcm, bool coarse, u32* contrast_array, int first_contrast);
static af_run_stage ispv1_vcaf_search_top(mini_af_run_param *af_info, mini_pos_info *curr, mini_vcm_info_s *vcm);
static FOCUS_STATUS ispv1_af_judge_result(mini_af_run_param *af_info);

static bool ispv1_check_caf_need_restart(mini_focus_frame_stat_s *start_data, mini_focus_frame_stat_s *end_data);

static void ispv1_k3focus_run(void);
static u32 ispv1_get_single_win_raw_lum(u8 win_idx, u32 stat_unit_area);

static bool enlarge_focus_window(mini_camera_rect_s *rect, int width, int height, int zoom);
static bool analysis_large_contrast_value(mini_pos_info *array, mini_af_run_param *af_info, mini_pos_info *top);
static bool detect_local_maximum(mini_af_run_param *af_info, u32* contrast_array, int contrast);

#define afae_adjust_zoom_ratio(ratio, zoom_base, zoom_max, afae_max) \
	(((ratio) - (zoom_base)) * ((afae_max) - (zoom_base)) \
	/ ((zoom_max) - (zoom_base)) \
	+ (zoom_base))

static inline mini_effect_params *get_effect_ptr(void)
{
	return mini_this_ispdata->sensor->effect;
}

inline FOCUS_STATUS mini_get_focus_result(void)
{
	return mini_afae_ctrl->af_result;
}

static inline void set_focus_result(FOCUS_STATUS status)
{
	mini_afae_ctrl->af_result = status;
}

static inline void save_focus_code(int code)
{
	mini_afae_ctrl->curr.code = code;
}

static inline int get_focus_code(void)
{
	return mini_afae_ctrl->curr.code;
}

static inline u16 get_caf_forcestart(void)
{
	return mini_afae_ctrl->force_start;
}

static inline void set_caf_forcestart(int value)
{
	mini_afae_ctrl->force_start = value;
}

inline focus_state_e mini_get_focus_state(void)
{
	return mini_afae_ctrl->focus_state;
}

inline void mini_set_focus_state(focus_state_e state)
{
	mini_afae_ctrl->focus_state = state;
}

static inline af_run_stage get_focus_stage(void)
{
	return mini_afae_ctrl->af_stage;
}

static inline void set_focus_stage(af_run_stage stage)
{
	mini_afae_ctrl->af_stage = stage;
}

inline bool mini_afae_ctrl_is_valid(void)
{
	return (mini_afae_ctrl != NULL);
}

static inline void set_pre_focus_mode(camera_focus mode)
{
	mini_afae_ctrl->pre_mode = mode;
}

static inline camera_focus get_pre_focus_mode(void)
{
	return mini_afae_ctrl->pre_mode;
}

static inline camera_focus get_focus_mode(void)
{
	return mini_afae_ctrl->mode;
}

static inline void set_focus_mode(camera_focus mode)
{
	mini_afae_ctrl->mode = mode;
}

static inline mini_vcm_info_s *get_vcm_ptr(void)
{
	return mini_this_ispdata->sensor->vcm;
}

inline void mini_save_target_high(void)
{
	if (mini_afae_ctrl != NULL)
		mini_afae_ctrl->target_high = GETREG8(REG_ISP_TARGET_Y_HIGH);
}
static inline void restore_target_high(void)
{
	if (mini_afae_ctrl != NULL)
	{
	    SETREG8(REG_ISP_TARGET_Y_HIGH, mini_afae_ctrl->target_high);
	}
}
static inline void set_near_target(void)
{
	u8 near_target = GETREG8(REG_ISP_TARGET_Y_LOW) + 4;
	SETREG8(REG_ISP_TARGET_Y_HIGH, near_target);
}
static inline bool ispv1_get_af_run_sem(void)
{
	long jiffies = 0;

	jiffies = msecs_to_jiffies(2000);
	if (down_timeout(&(mini_afae_ctrl->af_run_sem), jiffies)) {
		print_error("wait focus semaphore timeout");
		return false;
	} else {
		print_debug("focus semaphore waking up###########");
		return true;
	}
}

static inline void ispv1_free_af_run_sem(void)
{
	up(&(mini_afae_ctrl->af_run_sem));
}

inline u32 mini_ispv1_get_stat_unit_area(void)
{
	return raw_unit_area;
}

inline void mini_ispv1_set_stat_unit_area(u32 unit_area)
{
	raw_unit_area = unit_area;
}

u32 mini_ispv1_get_focus_code(void)
{
	u32 code = 0;
	mini_focus_result_s result;
	int ret;

	code = get_focus_code();
	ret = mini_ispv1_get_focus_result(&result);

	code &= 0xfffc;
	code |= result.status;

	return code;
}

/* set focus performance registers */
static void ispv1_setvcm_init(mini_vcm_info_s *vcm_info)
{
	print_debug("enter %s", __func__);

	/* init vcm ad5823 */
	if ((vcm_info->moveLensAddr[0] == 0x4) && (vcm_info->moveLensAddr[1] == 0x5)) {
		mini_ispv1_write_vcm(vcm_info->vcm_id, 0x02, 0x01, I2C_8BIT, SCCB_BUS_MUTEX_WAIT);
		mini_ispv1_write_vcm(vcm_info->vcm_id, 0x03, 0x80, I2C_8BIT, SCCB_BUS_MUTEX_WAIT);
	}
}

/* added for micro distance */
static u32 get_af_large_step(u32 step, u32 ratio)
{
	u32 ret;
	ret  = step * ratio / FOCUS_PARAM_LARGE_STRIDE_BASE;
	return ret;
}

static void ispv1_adjust_vcm_range(mini_vcm_info_s *vcm)
{
	int range;
	u32 large_step;

	range = vcm->normalDistanceEnd - vcm->infiniteDistance;

	/* calculate focus range in picture mode */
	large_step = get_af_large_step(vcm->normalStep, vcm->normalStrideRatio);
	if ((range - vcm->strideOffset) % large_step != 0) {
		range = vcm->strideOffset + ((range - vcm->strideOffset) / large_step + 1) * large_step;
	}

	vcm->normalDistanceEnd = vcm->infiniteDistance + range;

	range = vcm->videoDistanceEnd - vcm->infiniteDistance;

	/* calculate focus range in video mode */
	large_step = get_af_large_step(vcm->videoStep, vcm->videoStrideRatio);
	if ((range - vcm->strideOffset) % large_step != 0) {
		range = vcm->strideOffset + ((range - vcm->strideOffset) / large_step + 1) * large_step;
	}

	vcm->videoDistanceEnd = vcm->infiniteDistance + range;
}

static void ispv1_cal_vcm_range(mini_vcm_info_s *vcm)
{
	u16 otp_start = 0;
	u16 otp_end = 0;
	int otp_range;

	int normal_range;
	int normal_end;

	int video_range;
	int video_end;

	if (vcm->get_vcm_otp != NULL) {
		vcm->get_vcm_otp(&otp_start, &otp_end);
		print_info("get 10bit otp start 0x%x, end 0x%x***************", otp_start, otp_end);

		if (otp_start > 0xa0)
			otp_start = 0xa0;

		if (otp_end != 0) {
			normal_range = vcm->normalDistanceEnd - vcm->infiniteDistance;
			video_range = vcm->videoDistanceEnd - vcm->infiniteDistance;
			otp_range = (otp_end & 0x3f0) - (otp_start & 0x3f0);

			normal_range = (normal_range < otp_range) ? normal_range:otp_range;
			video_range = (video_range < otp_range) ? video_range:otp_range;
			if ( (otp_start & 0x3f0) < (2 * vcm->normalStep) ) {
				vcm->infiniteDistance = (2 * vcm->normalStep);
			} else {
				vcm->infiniteDistance = (otp_start & 0x3f0);
			}

			normal_end = vcm->infiniteDistance + normal_range;
			if (normal_end >= 0x400) {
				print_error("normalDistanceEnd 0x%x too large!", vcm->normalDistanceEnd);
				normal_range = (0x3f0 - vcm->infiniteDistance);
				normal_range -= (normal_range % vcm->normalStep);
				normal_end = vcm->infiniteDistance + normal_range;
			} else if (normal_end < vcm->normalDistanceEnd) {
				normal_end = vcm->normalDistanceEnd;
			}
			vcm->normalDistanceEnd = normal_end;

			video_end = vcm->infiniteDistance + video_range;
			if (vcm->videoDistanceEnd >= 0x400) {
				print_error("videoDistanceEnd 0x%x too large!", vcm->videoDistanceEnd);
				video_range = (0x3f0 - vcm->infiniteDistance);
				video_range -= (normal_range % vcm->videoStep);
				video_end = vcm->infiniteDistance + video_range;
			} else if (video_end < vcm->videoDistanceEnd) {
				video_end = vcm->videoDistanceEnd;
			}
			vcm->videoDistanceEnd = video_end;
		}
	}

	/*adjust range again */
	ispv1_adjust_vcm_range(vcm);
	print_info("focus infiniteDistance 0x%x, normalDistanceEnd 0x%x, videoDistanceEnd 0x%x***************",
		vcm->infiniteDistance, vcm->normalDistanceEnd, vcm->videoDistanceEnd);
}


static int ispv1_setreg_vcm_code_done(mini_vcm_info_s *vcm, u32 vcm_code)
{
	int ret = 0;
#if 0
	SETREG16(0x1c5da, vcm_code & 0xffff);
	SETREG8(0x1cddd, 0x01);
#else
	/*
	 * Change the NOWAIT to WAIT. Because sometimes the I2C would be occupied when the AF code was setted.
	 * In this case, if we don't wait, the code will not be setted into register, and will cause the AF fail.
	 */
	if (vcm->vcm_type == VCM_AD5823) {
		ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], ((vcm_code >> 8) | 0x04), I2C_8BIT, SCCB_BUS_MUTEX_WAIT);
		ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[1], (vcm_code & 0xFF), I2C_8BIT, SCCB_BUS_MUTEX_WAIT);
	} else if (vcm->vcm_type == VCM_DW9714) {
		/*in dw9714 case, ad value must set to bit4 ~ bit13*/
		ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], ((vcm_code << 4)|0x04), I2C_16BIT, SCCB_BUS_MUTEX_WAIT);
	} else if (vcm->vcm_type == VCM_DW9714_Sunny) {
		/*in dw9714 case, ad value must set to bit4 ~ bit13*/
		ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], ((vcm_code << 4)|0x04), I2C_16BIT, SCCB_BUS_MUTEX_WAIT);
	}  else if (vcm->vcm_type == VCM_DW9714_Liteon) {
		/*in dw9714 case, ad value must set to bit4 ~ bit13*/
		ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], ((vcm_code << 4)|0x04), I2C_16BIT, SCCB_BUS_MUTEX_WAIT);
	}  else {
		print_error("%s: unsupported vcm",  __func__);
		ret = -1;
	}
#endif
	return ret;
}


static bool ispv1_setreg_vcm_code(u32 dest_code)
{
	int ret = 0;
	mini_vcm_info_s *vcm = get_vcm_ptr();
	u32 curr_code = get_focus_code();
	bool divide_mode = false;
	int unit_step = 0;
	u32 safe_position = vcm->offsetInit + vcm->strideDivideOffset;
	u32 max_step_cnt = 0;
	u32 step_index = 0;

	/* if the dest code smaller than safe_position and the current code is larger than safe_position, divide the stride to avoid clash */
	if ((dest_code < safe_position) && (curr_code > safe_position)
	    && ((curr_code - dest_code) > vcm->strideDivideOffset)) {
		divide_mode = true;
		if (vcm->vcm_type == VCM_AD5823) {
			/* for AD5823, divide the stride into four steps */
			unit_step = (curr_code - dest_code) / 4;
			/* limit the minimal unit step to be 0x40*/
			if (unit_step < 0x40)
				unit_step = 0x40;
			if ((curr_code - dest_code) % unit_step == 0) {
				max_step_cnt = (curr_code - dest_code) / unit_step;
			} else {
				max_step_cnt = (curr_code - dest_code) / unit_step + 1;
			}
		} else if (vcm->vcm_type == VCM_DW9714) {
			/* for DW9714, divide the stride into two steps */
			unit_step = curr_code - safe_position;
			max_step_cnt = 2;
		} else if (vcm->vcm_type == VCM_DW9714_Sunny || vcm->vcm_type == VCM_DW9714_Liteon){
			if((curr_code - dest_code) > 550) {
				ispv1_setreg_vcm_lsc_mode(0xA106, 0xF2B0);
			} else if ((curr_code - dest_code) > 500) {
				ispv1_setreg_vcm_lsc_mode(0xA106, 0xF298);
			} else if ((curr_code - dest_code) > 450) {
				ispv1_setreg_vcm_lsc_mode(0xA105, 0xF258);
			} else if ((curr_code - dest_code) > 400) {
				ispv1_setreg_vcm_lsc_mode(0xA105, 0xF228);
			} else if ((curr_code - dest_code) > 350) {
				ispv1_setreg_vcm_lsc_mode(0xA105, 0xF2F8);
			} else if ((curr_code - dest_code) > 300) {
				ispv1_setreg_vcm_lsc_mode(0xA105, 0xF2D0);
			} else if ((curr_code - dest_code) > 250) {
				ispv1_setreg_vcm_lsc_mode(0xA105, 0xF2A8);
			} else if ((curr_code - dest_code) > 200) {
				ispv1_setreg_vcm_lsc_mode(0xA105, 0xF288);
			} else if ((curr_code - dest_code) > 150) {
				ispv1_setreg_vcm_lsc_mode(0xA104, 0xF2F8);
			} else if ((curr_code - dest_code) > 100) {
				ispv1_setreg_vcm_lsc_mode(0xA104, 0xF2A8);
			}else if ((curr_code - dest_code) > 50) {
				ispv1_setreg_vcm_lsc_mode(0xA104, 0xF280);
			}  else {
				ispv1_setreg_vcm_DLC_mode();
			}
			max_step_cnt = 1;
		} else {
			print_error("%s: unsupported vcm",  __func__);
			ret = -1;
			return ret;
		}

		for (step_index = 0; step_index < max_step_cnt - 1; step_index++) {
			curr_code -= unit_step;
			ret = ispv1_setreg_vcm_code_done(vcm, curr_code);
			msleep(vcm->motorDelayTime);
		}
		ret = ispv1_setreg_vcm_code_done(vcm, dest_code);
	} else {
		if ( vcm->vcm_type == VCM_DW9714_Sunny || vcm->vcm_type == VCM_DW9714_Liteon)
			ispv1_setreg_vcm_DLC_mode();
		ret = ispv1_setreg_vcm_code_done(vcm, dest_code);
	}

	if (ret != -1)
		save_focus_code(dest_code);

	return divide_mode;
}

/*
  *************************************************************************
  * FunctionName: ispv1_focus_vcm_go_infinite;
  * Description : using for vcm go to infinite position
  * Input       : delay_flag : 0 meens needless hold time;
  *			       1 meens need hold time
  * Output      : NA;
  * ReturnValue : NA;
  * Other       : in delay_flag equals 1 case, using for exit camera ;
  **************************************************************************
  */
static void ispv1_focus_vcm_go_infinite(u8 delay_flag)
{
	mini_vcm_info_s *vcm = get_vcm_ptr();
	int val_vcm = get_focus_code();
	bool divide_mode = false;

	print_debug("%s, val_vcm 0x%x, infiniteDistance 0x%x, vcm_id 0x%x, Addr 0x%x, 0x%x",
		__func__, val_vcm, vcm->infiniteDistance, vcm->vcm_id,
		vcm->moveLensAddr[0], vcm->moveLensAddr[1]);

	mini_ispv1_auto_focus(FOCUS_STOP);	/*Stop auto focus mode */

	/*
	 * in power off camera case,
	 * if current position bigger than infinite distance(safe position),
	 * then must return to infinite position by slow speed.
	 * after arriving infinite position, holding power few micro seconds,
	 * then power off camera.
	 * but, in change mode case,
	 * set current position to infinite distance directly.
	 */
	if (val_vcm <= vcm->infiniteDistance)
		return;

	divide_mode = ispv1_setreg_vcm_code(vcm->infiniteDistance);

	if ((1 == delay_flag) && (true == divide_mode)) {
		msleep(50);	/*holding time */
	}
}
static int ispv1_setreg_vcm_lsc_mode(u16 para1, u16 para2)
{
	int ret = 0;
	mini_vcm_info_s *vcm = mini_this_ispdata->sensor->vcm;
	print_info("enter %s, para1:0x%x, para2:0x%x", __func__, para1, para2);
	/*
	 * Change the NOWAIT to WAIT. Because sometimes the I2C would be occupied when the AF code was setted.
	 * In this case, if we don't wait, the code will not be setted into register, and will cause the AF fail.
	 */
	ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xECA3, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
	ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], para1, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
	ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], para2, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
	ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xDC51, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
	return ret;
}
static int ispv1_setreg_vcm_DLC_mode()
{
	int ret = 0;
	mini_vcm_info_s *vcm = mini_this_ispdata->sensor->vcm;
	/*
	 * Change the NOWAIT to WAIT. Because sometimes the I2C would be occupied when the AF code was setted.
	 * In this case, if we don't wait, the code will not be setted into register, and will cause the AF fail.
	 */
	if ((vcm->moveLensAddr[0] == 0x0) && (vcm->moveLensAddr[1] == 0x0)) {
		ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xECA3, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
		if (vcm->vcm_type == VCM_DW9714) {
			ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xF220, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
			ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xA10D, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
		} else if (vcm->vcm_type == VCM_DW9714_Sunny) {
			ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xF260, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
			ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xA10D, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
		} else if (vcm->vcm_type == VCM_DW9714_Liteon) {
			ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xF208, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
			ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xA10D, I2C_16BIT, SCCB_BUS_MUTEX_NOWAIT);
		}
		ret |= mini_ispv1_write_vcm(vcm->vcm_id, vcm->moveLensAddr[0], 0xDC51, I2C_16BIT, SCCB_BUS_MUTEX_WAIT);
	} else {
		print_error("%s: unsupported vcm",  __func__);
	}
	return ret;
}

/* Set focus windows(suitable for ISP) to registers. */
#if 0
static void ispv1_setreg_focus_win(mini_focus_win_info_s *win_info)
{
	u32 loopi;

	print_debug("enter %s", __func__);

    if (!win_info)
    {
        printk("!!!!!ASSERT ERROR!!!!");
        return;
    }

	SETREG16(REG_ISP_FOCUS_WIN_X0, win_info->left);
	SETREG16(REG_ISP_FOCUS_WIN_Y0, win_info->top);
	SETREG16(REG_ISP_FOCUS_WIN_W0, win_info->width);
	SETREG16(REG_ISP_FOCUS_WIN_H0, win_info->height);

	if ((win_info->width1 == 0) && (win_info->height1 == 0)) {
		print_debug("%s: single win mode", __func__);
		return;
	}

	SETREG16(REG_ISP_FOCUS_WIN_W1, win_info->width1);
	SETREG16(REG_ISP_FOCUS_WIN_H1, win_info->height1);

	for (loopi = 0; loopi < ISP_MAX_FOCUS_WIN; loopi++) {
		SETREG16(REG_ISP_FOCUS_WEIGHT_LIST(loopi), win_info->weight[loopi]);
	}
}
#endif
/*
 **************************************************************************
 * FunctionName: ispv1_setreg_af_mode;
 * Description : set auto focus mode;
 * Input       : mode; 0-snapshot auto mode;
 *                             1-snapshot single mode;
 *                             2-snapshot weighted mode;
 *                             3-video servo mode.
 * Output      : NA;
 * ReturnValue : ture or false;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_setreg_af_mode(camera_af_mode mode)
{
	u8 reg1 = 0;

	print_debug("enter %s, af mode %d", __func__, mode);

	SETREG16(REG_ISP_FOCUS_AFCCTRL2, 0x10);

	/*
	 * 0x66100: [2] bIfBinning: (1:binning; 0:non-binning); [1] nMode: (1:5x5;0:single)
	 * ISP_VIDEO_SERVO_MODE/ISP_SINGLE_SNAPSHOT_MODE is 0x4;
	 * ISP_AUTO_SNAPSHOT_MODE/ISP_WEIGHTED_SNAPSHOT_MODE is 0x2;
	 *
	 * REG_ISP_FOCUS_MODE; video 1; snapshot 0
	 * REG_ISP_FOCUS_WINMODE; single 0; 5x5 1;
	 * REG_ISP_FOCUS_bIFAUTO; auto 1;
	 * REG_ISP_FOCUS_bIFWEIGHTED; weighted 1; only works when nWinMode=1;
	 */
#ifdef AF_SINGLE_WINMODE_ONLY
	reg1 = ISP_FOCUS_NONBINNING;
#else
	if (mini_afae_ctrl->binning)
		reg1 = ISP_FOCUS_BINNING;
	else
		reg1 = ISP_FOCUS_NONBINNING;
#endif
	/* set register REG_ISP_FOCUS_AFCCTRL0's bit0 to 1  */
	reg1 |= 0x01;
	switch (mode) {
	case CAMERA_VIDEO_SERVO_MODE:
		SETREG8(REG_ISP_FOCUS_AFCCTRL0, reg1 | ISP_FOCUS_SINGLE_WINDOW);
		SETREG8(REG_ISP_FOCUS_MODE, ISP_FOCUS_VIDEO_MODE);
		SETREG8(REG_ISP_FOCUS_WINMODE, ISP_FOCUS_WINMODE_SINGLE);
		/*
		 * No need to set REG_ISP_FOCUS_bIFAUTO
		 * No need to set REG_ISP_FOCUS_bIFWEIGHTED
		 */
		break;

	case CAMERA_SINGLE_SNAPSHOT_MODE:
		SETREG8(REG_ISP_FOCUS_AFCCTRL0, reg1 | ISP_FOCUS_SINGLE_WINDOW);
		SETREG8(REG_ISP_FOCUS_MODE, ISP_FOCUS_SNAPSHOT_MODE);
		SETREG8(REG_ISP_FOCUS_WINMODE, ISP_FOCUS_WINMODE_SINGLE);
		/*
		 * No need to set REG_ISP_FOCUS_bIFAUTO
		 * No need to set REG_ISP_FOCUS_bIFWEIGHTED
		 */
		break;

	case CAMERA_AUTO_SNAPSHOT_MODE:
		SETREG8(REG_ISP_FOCUS_AFCCTRL0, reg1 | ISP_FOCUS_5X5_WINDOW);
		SETREG8(REG_ISP_FOCUS_MODE, ISP_FOCUS_SNAPSHOT_MODE);
		SETREG8(REG_ISP_FOCUS_WINMODE, ISP_FOCUS_WINMODE_5X5);
		SETREG8(REG_ISP_FOCUS_IFAUTO, ISP_FOCUS_IS_AUTO);
		SETREG8(REG_ISP_FOCUS_IFWEIGHTED, ISP_FOCUS_ISNOT_WEIGHTED);
		break;

	case CAMERA_WEIGHTED_SNAPSHOT_MODE:
		SETREG8(REG_ISP_FOCUS_AFCCTRL0, reg1 | ISP_FOCUS_5X5_WINDOW);
		SETREG8(REG_ISP_FOCUS_MODE, ISP_FOCUS_SNAPSHOT_MODE);
		SETREG8(REG_ISP_FOCUS_WINMODE, ISP_FOCUS_WINMODE_5X5);
		SETREG8(REG_ISP_FOCUS_IFAUTO, ISP_FOCUS_ISNOT_AUTO);
		SETREG8(REG_ISP_FOCUS_IFWEIGHTED, ISP_FOCUS_IS_WEIGHTED);
		break;

	default:
		print_error("mini_ispv1_set_focus_mode param error!\n");
		return -1;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_getreg_focus_result;
 * Description : get focus result from isp
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : STATUS_FOCUSING, STATUS_FOCUSED, STATUS_OUT_FOCUS
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_getreg_focus_result(focused_result_s *result, int multi_win)
{
	print_debug("enter %s", __func__);
    if (!result)
    {
        printk("!!!!!ASSERT ERROR!!!!");
        return -1;
    }

	result->focused_win_num = 1;
	result->focused_win[0] = 0;

	return mini_get_focus_result();
}

/*Just set some fixed parameters. And get some resource. */
int mini_ispv1_focus_init(void)
{
	mini_vcm_info_s *vcm = get_vcm_ptr();
	u32 size;
    mini_effect_params *effect = get_effect_ptr();
    mini_focus_area_param *this_focus_area = &effect->af_param.focus_area;

	mini_afae_ctrl = kmalloc(sizeof(mini_ispv1_afae_ctrl), GFP_KERNEL);
	if (!mini_afae_ctrl) {
		print_error("malloc is failed in %s function at line#%d\n", __func__, __LINE__);
		return -ENOMEM;
	}
	memset(mini_afae_ctrl, 0, sizeof(mini_ispv1_afae_ctrl));

	mini_afae_ctrl->map_table = kmalloc(MAX_FOCUS_RECT * ISP_MAX_FOCUS_WIN * sizeof(int), GFP_KERNEL);
	if (!mini_afae_ctrl->map_table) {
		print_error("malloc is failed in %s function at line#%d\n", __func__, __LINE__);
		kfree(mini_afae_ctrl);
		mini_afae_ctrl = NULL;
		return -ENOMEM;
	}
	memset(mini_afae_ctrl->map_table, 0, MAX_FOCUS_RECT * ISP_MAX_FOCUS_WIN * sizeof(int));

	/* request stat data for copy and calculate contrast extend threshold. */
	size = MAX_PREVIEW_WIDTH * MAX_PREVIEW_HEIGHT *
		this_focus_area->percent_w * this_focus_area->percent_h / 100 / 100 * 9;
	mini_afae_ctrl->stat_data = vmalloc(size);
	if (mini_afae_ctrl->stat_data == NULL) {
		print_error("malloc is failed in %s function at line#%d\n", __func__, __LINE__);
		kfree(mini_afae_ctrl->map_table);
		kfree(mini_afae_ctrl);
		mini_afae_ctrl->map_table = NULL;
		mini_afae_ctrl = NULL;
		return -ENOMEM;
	}

	set_focus_mode(CAMERA_FOCUS_CONTINUOUS_PICTURE);
	mini_set_focus_state(FOCUS_STATE_STOPPED);
	set_focus_result(STATUS_FOCUSED);

	memset(&mini_afae_ctrl->compare_data, 0, sizeof(mini_focus_frame_stat_s));
	set_caf_forcestart(CAF_FORCESTART_FORCEWAIT);

	mini_afae_ctrl->binning = 0;
	mini_afae_ctrl->focus_failed = 0;

	memset(&mini_afae_ctrl->cur_rect, 0, sizeof(mini_camera_rect_s));

	/* init af start work queue. */
	af_start_work_queue = create_singlethread_workqueue("af_start_wq");
	if (!af_start_work_queue) {
		print_error("create workqueue is failed in %s function at line#%d\n", __func__, __LINE__);
		kfree(mini_afae_ctrl);
		mini_afae_ctrl = NULL;
		return -1;
	}
	INIT_WORK(&af_start_work, ispv1_af_start_work_func);

	ispv1_cal_vcm_range(vcm);
	ispv1_setvcm_init(vcm);

	ispv1_setreg_vcm_code(vcm->infiniteDistance);

	sema_init(&(mini_afae_ctrl->af_run_sem), 1);
	mini_save_target_high();

	sema_init(&sem_af_schedule, 0);
	return 0;
}

/*called by exit */
int mini_ispv1_focus_exit(void)
{
	ispv1_focus_vcm_go_infinite(1);
	if (mini_afae_ctrl->map_table) {
		kfree(mini_afae_ctrl->map_table);
		mini_afae_ctrl->map_table = NULL;
	}

	if (mini_afae_ctrl->stat_data) {
		vfree(mini_afae_ctrl->stat_data);
		mini_afae_ctrl->stat_data = NULL;
	}

	destroy_workqueue(af_start_work_queue);

	if (mini_afae_ctrl) {
		kfree(mini_afae_ctrl);
		mini_afae_ctrl = NULL;
	}

	return 0;
}

/* called by start_preview */
int mini_ispv1_focus_prepare(void)
{
	print_debug("enter %s", __func__);

	set_focus_mode(CAMERA_FOCUS_CONTINUOUS_PICTURE);
	mini_set_focus_state(FOCUS_STATE_STOPPED);
	mini_afae_ctrl->af_area.focus_rect_num = 1;
	mini_afae_ctrl->focus_failed = 0;
	mini_afae_ctrl->k3focus_running = false;

	mini_afae_ctrl->focus_stat_frames = 0;
	memset(&mini_afae_ctrl->compare_data, 0, sizeof(mini_focus_frame_stat_s));

	return 0;
}

/* called by stop_preview */
int mini_ispv1_focus_withdraw(void)
{
	/* ispv1_wait_caf_done(); */
	mini_ispv1_auto_focus(FOCUS_STOP);
	mini_set_focus_state(FOCUS_STATE_STOPPED);
	flush_workqueue(af_start_work_queue);
	mini_afae_ctrl->focus_failed = 0;
	mini_afae_ctrl->af_area.focus_rect_num = 0;
	return 0;
}

static void ispv1_exit_focus_workqueue(camera_focus focus_mode)
{
	mini_afae_ctrl->k3focus_running = false;
	mini_ispv1_wakeup_focus_schedule(true);
	flush_workqueue(af_start_work_queue);
	if ((focus_mode != CAMERA_FOCUS_CONTINUOUS_VIDEO) &&
		(focus_mode != CAMERA_FOCUS_CONTINUOUS_PICTURE)) {
		ispv1_af_flash_check_close();
		mini_ispv1_set_aecagc_mode(AUTO_AECAGC);
	}
}

int mini_ispv1_auto_focus(int flag)
{
	int ret = 0;
	int i = 0;
    mini_camera_flashlight *flashlight = NULL;
	print_info("enter %s: flag: %d, focus state:%d, focus_mode:%d, result:%d",
		__func__, flag, mini_get_focus_state(), get_focus_mode(), mini_afae_ctrl->af_result);

	if(!mini_this_ispdata->sensor->af_enable)
		return ret;
	if(flag == FOCUS_START)
	{
		if(get_focus_mode() == CAMERA_FOCUS_AUTO)//by wind
		{
			for(i = 0;i<10;i++){
				if(mini_get_focus_state() == FOCUS_STATE_S1_ABORT){
					msleep(35);
				}else{
					break;
				}
			}
			camera_agent_set_flash_mode(mini_isp_check_af_flash_mode());
			print_info("FLASH S1_3A_UNLOCKED_BY_TAF");
			camera_agent_set_s1_AF_enable(CAMERA_SENSOR_PRIMARY, 1);
			camera_agent_s1_lock(mini_this_ispdata->sensor->sensor_index);
			mini_set_focus_state(FOCUS_STATE_AF_PREPARING);
			mini_afae_ctrl->af_result = STATUS_FOCUSING;
			mutex_lock(&mini_this_ispdata->mini_isp_flash_period_lock);
			mini_this_ispdata->s1_3a_state = S1_3A_UNLOCKED_BY_TAF;
			mutex_unlock(&mini_this_ispdata->mini_isp_flash_period_lock);
		}
	}

	if(flag == FOCUS_STOP)
	{
		if((mini_afae_ctrl->af_result ==STATUS_FOCUSING)&&(get_focus_mode() == CAMERA_FOCUS_AUTO))//by wind
		{
			camera_agent_s1_lock_abort();
			mini_set_focus_state(FOCUS_STATE_S1_ABORT);
			mutex_lock(&mini_this_ispdata->mini_isp_flash_period_lock);
			if (mini_this_ispdata->s1_3a_state != S1_3A_LOCKED)
				print_error("FLASH TAF timeout!!");
			mutex_unlock(&mini_this_ispdata->mini_isp_flash_period_lock);
			mini_afae_ctrl->af_result = STATUS_OUT_FOCUS;
		}
		else if(get_focus_mode() == CAMERA_FOCUS_AUTO)
		{
			camera_agent_set_PreviewAFLock(mini_this_ispdata->sensor->sensor_index,0);//by wind
			camera_agent_set_PreviewAELock(mini_this_ispdata->sensor->sensor_index,0);
		}
		if (get_focus_mode() == CAMERA_FOCUS_AUTO) {
			mutex_lock(&mini_this_ispdata->mini_isp_flash_period_lock);
			if (mini_this_ispdata->s1_3a_state != S1_3A_LOCKED) {
				print_info("TAF done, TAF_FLASH --> FLASH_IDLE");
				flashlight = mini_get_camera_flash();
				if (mini_this_ispdata->flash_on && flashlight) {
					print_info("turn_off TAF_FLASH");
					flashlight->turn_off();
					mini_this_ispdata->flash_on = false;
				}
				mini_this_ispdata->mini_isp_flash_period = FLASH_IDLE;
				mini_this_ispdata->s1_3a_state = S1_3A_LOCKED;
			}
			mutex_unlock(&mini_this_ispdata->mini_isp_flash_period_lock);
		}
	}
	
	//if(flag == FOCUS_CAF_FORCE_AF)
	//{
		//do nothing
	//}
return 0;//by wind
	if (ispv1_get_af_run_sem() == false) {
		return -1;
	}
	if (flag == FOCUS_START) {
		if (get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_VIDEO) {
			if (mini_get_focus_state() == FOCUS_STATE_STOPPED) {
				mini_set_focus_state(FOCUS_STATE_CAF_PREPARING);
				set_focus_result(STATUS_FOCUSED);
			} else {
				print_error("line %d: not valid status %d", __LINE__, mini_get_focus_state());
				ret = -1;
				goto free_out;
			}
		} else if (get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_PICTURE) {
			if (mini_get_focus_state() == FOCUS_STATE_STOPPED) {
				mini_set_focus_state(FOCUS_STATE_CAF_PREPARING);
			} else {
				print_error("line %d: not valid status %d", __LINE__, mini_get_focus_state());
				ret = -1;
				goto free_out;
			}
		} else if (get_focus_mode() == CAMERA_FOCUS_AUTO_VIDEO) {
			if (mini_get_focus_state() == FOCUS_STATE_STOPPED) {
				mini_set_focus_state(FOCUS_STATE_AF_PREPARING);
				set_focus_result(STATUS_FOCUSING);
			} else {
				print_error("line %d: not valid status %d", __LINE__, mini_get_focus_state());
				ret = -1;
				goto free_out;
			}
		} else {
			/* if this time is snapshot focus,
			 * should goto AF_PREPARING state
			 */
			mini_set_focus_state(FOCUS_STATE_AF_PREPARING);
			set_focus_result(STATUS_FOCUSING);

			mini_afae_ctrl->area_changed = false;
		}
		queue_work(af_start_work_queue, &af_start_work);
		goto normal_out;
	} else if ((flag == FOCUS_STOP) && (mini_get_focus_state() != FOCUS_STATE_STOPPED)) {

		if ((get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_PICTURE) ||
			(get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_VIDEO)) {
			if (mini_get_focus_state() != FOCUS_STATE_CAF_DETECTING) {
				print_info("caf doesn't stoped");
				set_focus_result(STATUS_OUT_FOCUS);
			} else {
				set_focus_result(STATUS_FOCUSED);
			}
		} else {
			if (mini_get_focus_result() == STATUS_FOCUSING) {
				print_info("auto focus timeout");
				set_focus_result(STATUS_OUT_FOCUS);
			}
		}
		ispv1_exit_focus_workqueue(get_focus_mode());
		mini_set_focus_state(FOCUS_STATE_STOPPED);

		goto free_out;
	} else if (flag == FOCUS_CAF_FORCE_AF) {
		if ((get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_PICTURE) ||
			(get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_VIDEO)) {
			if (mini_get_focus_state() != FOCUS_STATE_CAF_RUNNING) {
				set_focus_result(STATUS_FOCUSING);
				ispv1_exit_focus_workqueue(get_focus_mode());

				set_pre_focus_mode(get_focus_mode());
				if (get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_VIDEO){
					set_focus_mode(CAMERA_FOCUS_AUTO_VIDEO);
				} else {
					set_focus_mode(CAMERA_FOCUS_CAF_FORCE_AF);
				}
				mini_set_focus_state(FOCUS_STATE_AF_PREPARING);
				queue_work(af_start_work_queue, &af_start_work);
				goto normal_out;
			} else {
				print_info("%s, CAF already running, must wait CAF done.", __func__);
				goto free_out;
			}
		} else {
			print_error("line %d: not valid status %d", __LINE__, mini_get_focus_state());
			goto free_out;
		}
	} else if (flag == FOCUS_AF_RESUME_CAF) {
		if ((get_focus_mode() != CAMERA_FOCUS_CONTINUOUS_PICTURE) &&
			(get_focus_mode() != CAMERA_FOCUS_CONTINUOUS_VIDEO)) {
			set_focus_result(STATUS_OUT_FOCUS);
			ispv1_exit_focus_workqueue(get_focus_mode());

			set_caf_forcestart(CAF_FORCESTART_FORCE);
			set_focus_mode(get_pre_focus_mode());
			mini_set_focus_state(FOCUS_STATE_CAF_PREPARING);
			queue_work(af_start_work_queue, &af_start_work);
			goto normal_out;
		} else {
			print_error("line %d: not valid status %d", __LINE__, mini_get_focus_state());
			goto free_out;
		}
	} else {
		print_error("mini_ispv1_auto_focus param error!");
		ret = -1;
		goto free_out;
	}

free_out:
	ispv1_free_af_run_sem();
normal_out:
	return ret;
}

static void ispv1_af_start_work_func(struct work_struct *work)
{
	mini_camera_sensor *sensor =  mini_this_ispdata->sensor;
	camera_focus cur_focus_mode = get_focus_mode();

	/* if focus state has changed, should return immediately. */
	if ((mini_get_focus_state() != FOCUS_STATE_CAF_PREPARING) &&
		(mini_get_focus_state() != FOCUS_STATE_AF_PREPARING))
		return;

	if (cur_focus_mode < CAMERA_FOCUS_MAX)
		ispv1_set_focus_mode_done(cur_focus_mode);

	ispv1_set_focus_area_done(&mini_afae_ctrl->af_area, mini_afae_ctrl->zoom);

	
	mini_this_ispdata->af_need_flash = ispv1_af_flash_needed(sensor, mini_this_ispdata->flash_mode, mini_afae_ctrl->lum_info);


	if ((cur_focus_mode == CAMERA_FOCUS_CONTINUOUS_PICTURE)
		|| (cur_focus_mode== CAMERA_FOCUS_CONTINUOUS_VIDEO)){
		mini_set_focus_state(FOCUS_STATE_CAF_DETECTING);

		if (mini_afae_ctrl->area_changed == true)
			set_caf_forcestart(CAF_FORCESTART_FORCEWAIT);
		else
			ispv1_focus_status_reset();

		if (mini_afae_ctrl->k3focus_running == false)
			ispv1_k3focus_run();
		else {
			print_error("fatal error in %s line %d: state error!", __func__, __LINE__);
			ispv1_free_af_run_sem();
		}
	} else if ((cur_focus_mode == CAMERA_FOCUS_CAF_FORCE_AF) &&
			(false == mini_this_ispdata->af_need_flash) && (CAF_FORCESTART_CLEAR == get_caf_forcestart())) {
		print_info("%s, don't excute auto focus, af_need_flash:%d, force_start:0x%x",
			__func__, mini_this_ispdata->af_need_flash, get_caf_forcestart());
		set_focus_result(STATUS_FOCUSED);
		mini_set_focus_state(FOCUS_STATE_STOPPED);
		ispv1_free_af_run_sem();
	} else {
		mini_set_focus_state(FOCUS_STATE_AF_RUNNING);
		set_focus_stage(AF_RUN_STAGE_PREPARE);

		if (mini_afae_ctrl->k3focus_running == false) {
			ispv1_k3focus_run();
		} else {
			print_error("fatal error in %s line %d: state error!", __func__, __LINE__);
			ispv1_free_af_run_sem();
		}
	}
}

static int ispv1_get_yuvrect_of_full(mini_pic_attr_t *pic_attr, mini_camera_rect_s *rect, u32 zoom)
{
	int ratio = isp_zoom_to_ratio(zoom, 0);
	mini_coordinate_s center;
	mini_coordinate_s phy_center;
	int left, top;

	center.x = rect->left + rect->width / 2;
	center.y = rect->top + rect->height / 2;
	phy_center.x = pic_attr->out_width / 2;
	phy_center.y = pic_attr->out_height / 2;

	if (center.x >= pic_attr->out_width)
		center.x = pic_attr->out_width;

	if (center.y >= pic_attr->out_height)
		center.y = pic_attr->out_height;

	/* new center position in original full yuv according ratio */
	center.x = (int)phy_center.x + ((int)center.x - (int)phy_center.x) * ISP_ZOOM_BASE_RATIO / ratio;
	center.y = (int)phy_center.y + ((int)center.y - (int)phy_center.y) * ISP_ZOOM_BASE_RATIO / ratio;

	rect->width = rect->width * ISP_ZOOM_BASE_RATIO / ratio;
	rect->height = rect->height * ISP_ZOOM_BASE_RATIO / ratio;

	left = (int)center.x - (int)rect->width / 2;
	top = (int)center.y - (int)rect->height / 2;

	rect->left = (left > 0) ? left : 0;
	rect->top = (top > 0) ? top : 0;

	return 0;
}

static int ispv1_get_yuvrect_of_app(mini_pic_attr_t *pic_attr, mini_camera_rect_s *rect, u32 zoom)
{
	int ratio = isp_zoom_to_ratio(zoom, 0);
	mini_coordinate_s center;
	mini_coordinate_s phy_center;
	int left, top;
    mini_effect_params *effect = get_effect_ptr();
    mini_focus_area_param *this_focus_area = &effect->af_param.focus_area;
    u32 preview_width = pic_attr->out_width;
    u32 preview_height = pic_attr->out_height;

	center.x = rect->left + rect->width / 2;
	center.y = rect->top + rect->height / 2;
	phy_center.x = pic_attr->out_width / 2;
	phy_center.y = pic_attr->out_height / 2;

	if (center.x >= pic_attr->out_width)
		center.x = pic_attr->out_width;

	if (center.y >= pic_attr->out_height)
		center.y = pic_attr->out_height;

	/* new center position in app plane's yuv */
	center.x = (int)phy_center.x + ((int)center.x - (int)phy_center.x) * ratio / ISP_ZOOM_BASE_RATIO;
	center.y = (int)phy_center.y + ((int)center.y - (int)phy_center.y) * ratio / ISP_ZOOM_BASE_RATIO;

	rect->width = rect->width * ratio / ISP_ZOOM_BASE_RATIO;
	rect->height = rect->height * ratio / ISP_ZOOM_BASE_RATIO;
    if (rect->width > (preview_width * this_focus_area->percent_w / 100)) {
        rect->width = preview_width * this_focus_area->percent_w / 100;
    }
    if (rect->height > (preview_height * this_focus_area->percent_h/ 100)) {
        rect->height = preview_height * this_focus_area->percent_h / 100;
    }

	left = (int)center.x - (int)rect->width / 2;
	top = (int)center.y - (int)rect->height / 2;

	/* check left/top side */
	rect->left = (left > 0) ? left : 0;
	rect->top = (top > 0) ? top : 0;

	/*check right/bottom side */
	rect->left = ((rect->left + rect->width) > pic_attr->out_width) ? \
		(pic_attr->out_width - rect->width) : rect->left;
	rect->top = ((rect->top + rect->height) > pic_attr->out_height) ? \
		(pic_attr->out_height - rect->height) : rect->top;

	return 0;
}


#if 0
static bool ispv1_check_rect_center(mini_camera_rect_s *rect, u32 preview_width, u32 preview_height)
{
	bool ret = false;
	mini_coordinate_s center, rect_center;

	if (rect->width == 0 || rect->height == 0)
		return true;

	center.x = preview_width / 2;
	center.y = preview_height / 2;
	rect_center.x = rect->left + rect->width / 2;
	rect_center.y = rect->top + rect->height / 2;

	if (abs(rect_center.x - center.x) < 4 && abs(rect_center.y - center.y) < 4)
		ret = true;

	return ret;
}


static bool ispv1_check_rect_differ(mini_camera_rect_s *rect1, mini_camera_rect_s *rect2,
				   u32 preview_width, u32 preview_height)
{
	mini_coordinate_s center1, center2;
	u32 width_diff, height_diff;

	center1.x = rect1->left + rect1->width / 2;
	center1.y = rect1->top + rect1->height / 2;

	center2.x = rect2->left + rect2->width / 2;
	center2.y = rect2->top + rect2->height / 2;

	/* if center pointer differ a lot, then it is differ. */
	if ((abs(center2.x - center1.x) > (preview_width / 16)) || (abs(center2.y - center1.y) > (preview_height / 16)))
		return true;

	/* if size is differ a lot, then it is differ. */
	width_diff = abs(rect1->width - rect2->width);
	height_diff = abs(rect1->height - rect2->height);
	if ((width_diff > rect1->width / 2) || (width_diff > rect2->width / 2)
	    || (height_diff > rect1->height / 2) || (height_diff > rect2->height / 2))
		return true;

	return false;
}
#endif

#if 0
static int ispv1_get_map_table(mini_focus_area_s *area,
				mini_focus_win_info_s *win_info, int *map_table)
{
	u32 area_idx;
	u32 win_idx;
	mini_camera_rect_s user_rect;
	mini_camera_rect_s isp_rect;
	int ret;

	/* check every area,
	 * it is in which yuv win, maybe in several wins, maybe none
	 */
	for (area_idx = 0; area_idx < area->focus_rect_num; area_idx++) {
		print_debug("map table for region %d:", area_idx);

		/* get each yuv win */
		ret = mini_k3_isp_yuvrect_to_rawrect(&area->rect[area_idx], &user_rect);
		if (ret) {
			print_error("%s:line %d error", __func__, __LINE__);
			return ret;
		}

		for (win_idx = 0; win_idx < ISP_MAX_FOCUS_WIN; win_idx++) {
			/* get each raw win */
			ispv1_get_raw_win(win_idx, win_info, &isp_rect);
			print_debug("isp_rect %d: %d,%d,%d,%d", win_idx,
				isp_rect.left, isp_rect.top, isp_rect.width, isp_rect.height);

			ret = ispv1_check_rect_intersection(&user_rect, &isp_rect);
			if (ret == 0) {
				*(map_table + area_idx * ISP_MAX_FOCUS_WIN + win_idx) = 1;
				win_info->weight[win_idx] = 1;
			} else
				*(map_table + area_idx * ISP_MAX_FOCUS_WIN + win_idx) = 0;
		}
	}

	return 0;
}
#endif
/* changed 2012-03-15 for zero size rect*/
static int ispv1_focus_get_default_yuvrect(mini_camera_rect_s *rectin, u32 preview_width, u32 preview_height)
{
	mini_effect_params *effect = get_effect_ptr();
	mini_focus_area_param *this_focus_area = &effect->af_param.focus_area;

	rectin->left = preview_width * (100 - this_focus_area->percent_w) / 200;
	rectin->top = preview_height * (100 - this_focus_area->percent_h) / 200;
	rectin->width = preview_width * this_focus_area->percent_w / 100;
	rectin->height = preview_height * this_focus_area->percent_h / 100;

	return 0;
}

static int ispv1_focus_adjust_yuvrect(mini_camera_rect_s *yuv, u32 preview_width, u32 preview_height, u32 zoom)
{
	u32 ratio = isp_zoom_to_ratio(zoom, 0);
	u32 width = yuv->width;
	u32 height = yuv->height;
	int left, top;
	u32 height_ratio;
	u32 max_hzoom_ratio;
	mini_effect_params *effect = get_effect_ptr();
	mini_focus_area_param *this_focus_area = &effect->af_param.focus_area;

	/* first re-size ratio to fit focus: 1x-4x change to 1x-2x. */
	ratio = afae_adjust_zoom_ratio(ratio, ISP_ZOOM_BASE_RATIO, ISP_ZOOM_MAX_RATIO, this_focus_area->max_zoom_ratio);
	max_hzoom_ratio = this_focus_area->min_height_ratio * (this_focus_area->max_zoom_ratio / ISP_ZOOM_BASE_RATIO);

	height_ratio = this_focus_area->min_height_ratio * ratio / ISP_ZOOM_BASE_RATIO;

	/* adjust height ratio. */
	if (height_ratio < this_focus_area->min_height_ratio)
		height_ratio = this_focus_area->min_height_ratio;
	else if (height_ratio > this_focus_area->min_height_ratio * this_focus_area->max_zoom_ratio / ISP_ZOOM_BASE_RATIO)
		height_ratio = max_hzoom_ratio;

	print_debug("before left:%d, top:%d, yuv->width:%d; yuv->height:%d, height_ratio 0x%x",
		yuv->left, yuv->top, yuv->width, yuv->height, height_ratio);

	/* first, check if edge is not valid, set to default. */
	if ((yuv->left > preview_width) || (yuv->top > preview_height) ||
		(yuv->width > preview_width) || (yuv->height > preview_height)) {
		ispv1_focus_get_default_yuvrect(yuv, preview_width, preview_height);
	} else if (((yuv->left + yuv->width) > preview_width) || ((yuv->top + yuv->height) > preview_height)) {
		if ((yuv->left + yuv->width) > preview_width) {
			yuv->width -= ((yuv->left + yuv->width) - preview_width);
		}
		if ((yuv->top + yuv->height) > preview_height) {
			yuv->height -= ((yuv->top + yuv->height) - preview_height);
		}
	}

	/* second, check if width/height is larger than default or not */
	width = yuv->width;
	height = yuv->height;
	if (yuv->width > (preview_width * this_focus_area->percent_w / 100))
		width = preview_width * this_focus_area->percent_w / 100;
	if (yuv->height > (preview_height * this_focus_area->percent_h / 100))
		height = preview_height * this_focus_area->percent_h / 100;

	yuv->left = yuv->left + ((int)yuv->width - (int)width) / 2;
	yuv->top = yuv->top + ((int)yuv->height - (int)height) / 2;
	yuv->width = width;
	yuv->height = height;

	/* avoid zero divide error. */
	if (yuv->height <= 0)
		yuv->height = 1;

	/* third, check if rect is too small */
	if (yuv->height < (preview_height / height_ratio)) {
		width = yuv->width * (preview_height / height_ratio) / yuv->height;
		height = preview_height / height_ratio;

		if (width > (height * 3 / 2)) {
			width =height * 3 / 2;
		} else if (width < (height * 2 / 3)) {
			width = height * 2 / 3;
		}

		left = yuv->left - ((int)width - (int)yuv->width) / 2;
		top = yuv->top - ((int)height - (int)yuv->height) / 2;

		if (left < 0) {
			/* left is out of valid area */
			yuv->left = 0;
		} else if ((left + width) > preview_width) {
			/* right is larger than preview width */
			yuv->left = preview_width - width;
		} else {
			yuv->left = left;
		}

		if (top < 0) {
			/* top is out of valid area */
			yuv->top = 0;
		} else if ((top + height) > preview_height) {
			/* buttom is larger than preview height */
			yuv->top = preview_height - height;
		} else {
			yuv->top = top;
		}

		print_info("%s, focus rect from [%d X %d]->[%d,%d, %d X %d]",
			__func__, yuv->width, yuv->height, yuv->left, yuv->top, width, height);
		yuv->height = height;
		yuv->width = width;
	}
	print_debug("after left:%d, top:%d, yuv->width:%d; yuv->height:%d",
		yuv->left, yuv->top, yuv->width, yuv->height);
	return 0;
}

static int ispv1_focus_adjust_rawwin(mini_focus_win_info_s *win_info, u32 raw_width, u32 raw_height)
{
	if (win_info->left < 24) {
		win_info->left = 24;
		if (win_info->width > 72) {
			win_info->width -= 24;
		} else {
			win_info->width = 48;
		}
	}

	if (win_info->top < 24) {
		win_info->top = 24;
		if (win_info->height > 72) {
			win_info->height -= 24;
		} else {
			win_info->height = 48;
		}
	}

	if ((win_info->top + win_info->height) > raw_height)
		win_info->top -= (win_info->top + win_info->height) - raw_height;

	if ((win_info->left + win_info->width) > raw_width)
		win_info->left -= (win_info->left + win_info->width) - raw_width;

	/* win startx+starty should be odd. */
	if ((win_info->left + win_info->top) % 2 == 0) {
		win_info->left += 1;
	}

	/* width and height should be mutiple of 6 */
	win_info->width -= (win_info->width % 6);
	win_info->height -= (win_info->height % 6);

	return 0;
}

#define ISP_LUM_WIN_CENTER_X(width, win_id) \
	((width) / ISP_LUM_WIN_WIDTH_NUM * ((win_id) % ISP_LUM_WIN_WIDTH_NUM) \
	+ (width) / ISP_LUM_WIN_WIDTH_NUM / 2)

#define ISP_LUM_WIN_CENTER_Y(height, win_id) \
	((height) / ISP_LUM_WIN_HEIGHT_NUM * ((win_id) / ISP_LUM_WIN_WIDTH_NUM) \
	+ (height) / ISP_LUM_WIN_HEIGHT_NUM / 2)

static inline u32 ispv1_get_distance_to_lumwin(mini_coordinate_s *curr, mini_coordinate_s *lum_win)
{
	u32 x_coff, y_coff;

	x_coff = abs((int)curr->x - (int)lum_win->x);
	x_coff *= x_coff;

	y_coff = abs((int)curr->y - (int)lum_win->y);
	y_coff *= y_coff;

	return (x_coff + y_coff);
}


static void ispv1_focus_get_lumwin_info(mini_focus_win_info_s *win_info, u32 raw_width, u32 raw_height, mini_lum_win_info_s *lum_info)
{
	mini_coordinate_s center;
	mini_coordinate_s lumwin_center;
	u32 distance;
	u32 saved_distance[4];
	int loop;

	saved_distance[0] = 0xffff;
	saved_distance[1] = 0xffff;
	saved_distance[2] = 0xffff;
	saved_distance[3] = 0xffff;

	lum_info->index[0] = 0;
	lum_info->index[1] = 0;
	lum_info->index[2] = 0;
	lum_info->index[3] = 0;

	center.x = win_info->left + win_info->width / 2;
	center.y = win_info->top + win_info->height / 2;

	for (loop = 0; loop < (ISP_LUM_WIN_WIDTH_NUM * ISP_LUM_WIN_HEIGHT_NUM); loop++) {
		lumwin_center.x = ISP_LUM_WIN_CENTER_X(raw_width, loop);
		lumwin_center.y = ISP_LUM_WIN_CENTER_Y(raw_height, loop);

		distance = ispv1_get_distance_to_lumwin(&center, &lumwin_center);
		if (distance < saved_distance[0]) {
			saved_distance[3] = saved_distance[2];
			lum_info->index[3] = lum_info->index[2];

			saved_distance[2] = saved_distance[1];
			lum_info->index[2] = lum_info->index[1];

			saved_distance[1] = saved_distance[0];
			lum_info->index[1] = lum_info->index[0];

			saved_distance[0] = distance;
			lum_info->index[0] = loop;
		} else if (distance < saved_distance[1]) {
			saved_distance[3] = saved_distance[2];
			lum_info->index[3] = lum_info->index[2];

			saved_distance[2] = saved_distance[1];
			lum_info->index[2] = lum_info->index[1];

			saved_distance[1] = distance;
			lum_info->index[1] = loop;
		} else if (distance < saved_distance[2]) {
			saved_distance[3] = saved_distance[2];
			lum_info->index[3] = lum_info->index[2];

			saved_distance[2] = distance;
			lum_info->index[2] = loop;
		} else if (distance < saved_distance[3]) {
			saved_distance[3] = distance;
			lum_info->index[3] = loop;
		}
	}

	lum_info->width = (raw_width / 8);
	lum_info->height = (raw_height / 6);
}
static int ispv1_get_metering_winidx(mini_camera_rect_s *win, u32 raw_width, u32 raw_height)
{
	mini_coordinate_s center;
	int idx_x, idx_y;

	center.x = win->left + win->width / 2;
	center.y = win->top + win->height / 2;

	idx_x = center.x / (raw_width / ISP_LUM_WIN_WIDTH_NUM);
	idx_y = center.y / (raw_height / ISP_LUM_WIN_HEIGHT_NUM);

	return(idx_y * ISP_LUM_WIN_WIDTH_NUM + idx_x);
}

static bool ispv1_check_metering_area_enhance(mini_pic_attr_t *pic_attr, mini_camera_rect_s *win)
{
	u32 raw_width = pic_attr->in_width;
	u32 raw_height = pic_attr->in_height;
	u32 unit_area = mini_ispv1_get_stat_unit_area();
	u32 lum_sum = 0;
	u32 lum_curr;
	int win_idx;

	for (win_idx = 0; win_idx < (ISP_LUM_WIN_WIDTH_NUM * ISP_LUM_WIN_HEIGHT_NUM); win_idx++) {
		lum_sum += ispv1_get_single_win_raw_lum(win_idx, unit_area);
	}
	lum_sum /= (ISP_LUM_WIN_WIDTH_NUM * ISP_LUM_WIN_HEIGHT_NUM);

	win_idx = ispv1_get_metering_winidx(win, raw_width, raw_height);
	lum_curr = ispv1_get_single_win_raw_lum(win_idx, unit_area);

	print_debug("focus AE lum_sum 0x%x, lum_curr 0x%x", lum_sum, lum_curr);

	if (lum_curr > lum_sum)
		return true;
	else
		return false;
}

static mini_lum_table_s lum_table[] = {
	{256, 20480},{255, 20465},{254, 20451},{253, 20436},{252, 20421},{251, 20407},{250, 20392},{249, 20377},
	{248, 20362},{247, 20347},{246, 20332},{245, 20317},{244, 20302},{243, 20287},{242, 20272},{241, 20256},
	{240, 20241},{239, 20226},{238, 20210},{237, 20195},{236, 20179},{235, 20163},{234, 20148},{233, 20132},
	{232, 20116},{231, 20100},{230, 20084},{229, 20068},{228, 20052},{227, 20035},{226, 20019},{225, 20003},
	{224, 19986},{223, 19970},{222, 19953},{221, 19937},{220, 19920},{219, 19903},{218, 19886},{217, 19869},
	{216, 19852},{215, 19835},{214, 19818},{213, 19800},{212, 19783},{211, 19766},{210, 19748},{209, 19730},
	{208, 19713},{207, 19695},{206, 19677},{205, 19659},{204, 19641},{203, 19623},{202, 19605},{201, 19586},
	{200, 19568},{199, 19549},{198, 19531},{197, 19512},{196, 19493},{195, 19474},{194, 19455},{193, 19436},
	{192, 19417},{191, 19398},{190, 19378},{189, 19359},{188, 19339},{187, 19320},{186, 19300},{185, 19280},
	{184, 19260},{183, 19240},{182, 19219},{181, 19199},{180, 19179},{179, 19158},{178, 19137},{177, 19117},
	{176, 19096},{175, 19075},{174, 19053},{173, 19032},{172, 19011},{171, 18989},{170, 18968},{169, 18946},
	{168, 18924},{167, 18902},{166, 18880},{165, 18857},{164, 18835},{163, 18812},{162, 18790},{161, 18767},
	{160, 18744},{159, 18720},{158, 18697},{157, 18674},{156, 18650},{155, 18626},{154, 18602},{153, 18578},
	{152, 18554},{151, 18530},{150, 18505},{149, 18481},{148, 18456},{147, 18431},{146, 18405},{145, 18380},
	{144, 18355},{143, 18329},{142, 18303},{141, 18277},{140, 18250},{139, 18224},{138, 18197},{137, 18170},
	{136, 18143},{135, 18116},{134, 18089},{133, 18061},{132, 18033},{131, 18005},{130, 17977},{129, 17948},
	{128, 17920},{127, 17891},{126, 17861},{125, 17832},{124, 17802},{123, 17772},{122, 17742},{121, 17712},
	{120, 17681},{119, 17650},{118, 17619},{117, 17588},{116, 17556},{115, 17524},{114, 17492},{113, 17459},
	{112, 17426},{111, 17393},{110, 17360},{109, 17326},{108, 17292},{107, 17258},{106, 17223},{105, 17188},
	{104, 17153},{103, 17117},{102, 17081},{101, 17045},{100, 17008},{99 , 16971},{98 , 16933},{97 , 16895},
	{96 , 16857},{95 , 16818},{94 , 16779},{93 , 16740},{92 , 16700},{91 , 16659},{90 , 16619},{89 , 16577},
	{88 , 16536},{87 , 16493},{86 , 16451},{85 , 16408},{84 , 16364},{83 , 16320},{82 , 16275},{81 , 16230},
	{80 , 16184},{79 , 16137},{78 , 16090},{77 , 16042},{76 , 15994},{75 , 15945},{74 , 15896},{73 , 15845},
	{72 , 15795},{71 , 15743},{70 , 15690},{69 , 15637},{68 , 15583},{67 , 15529},{66 , 15473},{65 , 15417},
	{64 , 15360},{63 , 15301},{62 , 15242},{61 , 15182},{60 , 15121},{59 , 15059},{58 , 14996},{57 , 14932},
	{56 , 14866},{55 , 14800},{54 , 14732},{53 , 14663},{52 , 14593},{51 , 14521},{50 , 14448},{49 , 14373},
	{48 , 14297},{47 , 14219},{46 , 14140},{45 , 14059},{44 , 13976},{43 , 13891},{42 , 13804},{41 , 13715},
	{40 , 13624},{39 , 13530},{38 , 13434},{37 , 13336},{36 , 13235},{35 , 13130},{34 , 13023},{33 , 12913},
	{32 , 12800},{31 , 12682},{30 , 12561},{29 , 12436},{28 , 12306},{27 , 12172},{26 , 12033},{25 , 11888},
	{24 , 11737},{23 , 11580},{22 , 11416},{21 , 11244},{20 , 11064},{19 , 10874},{18 , 10675},{17 , 10463},
	{16 , 10240},{15 , 10001},{14 , 9746 },{13 , 9473 },{12 , 9177 },{11 , 8856 },{10 , 8504 },{9  , 8115 },
	{8  , 7680 },{7  , 7186 },{6  , 6617 },{5  , 5944 },{4  , 5120 },{3  , 4057 },{2  , 2560 },{1  , 0    },

};

/*
 **************************************************************************
 * FunctionName: ispv1_convert_win_lum;
 * Description : NA;
 * Input       : stat_value:luminance stat value
 *			lum_tbl:luminance table,
 *			size:table size;
 * Output      : NA;
 * ReturnValue : luminance value;
 * Other       : NA;
 **************************************************************************
 */
static u32 ispv1_convert_win_lum(u32 stat_value, mini_lum_table_s *lum_tbl, u32 size)
{
	int top = 0;
	int bottom = size - 1;
	int  middle;

	while (abs(top - bottom) > 1) {
		middle = (top + bottom) / 2;
		if (stat_value >= lum_tbl[middle].value)
			bottom = middle;
		else
			top = middle;
	}

	return lum_tbl[top].lum;
}

/*
 **************************************************************************
 * FunctionName: mini_ispv1_get_raw_lum_info;
 * Description : NA;
 * Input       : mini_aec_data_t *ae_data, stat_unit_area:area of minimum luminance stat window;
 * Output      : lum_max, lum_sum;
 * ReturnValue : void;
 * Other       : NA;
 **************************************************************************
 */
void mini_ispv1_get_raw_lum_info(mini_aec_data_t *ae_data, u32 stat_unit_area)
{
	u32 win_idx;
	u32 width_idx, height_idx;
	u32 lum;
	u32 lum_max = 0;
	u32 idx_max = 0;
	u32 lum_sum = 0;

	for (width_idx = 2; width_idx < ISP_LUM_WIN_WIDTH_NUM - 2; width_idx++) {
		for (height_idx = 1; height_idx < ISP_LUM_WIN_HEIGHT_NUM - 1; height_idx++) {
			win_idx = height_idx * ISP_LUM_WIN_WIDTH_NUM + width_idx;
			/* get each raw win raw */
			lum = ispv1_get_single_win_raw_lum(win_idx, stat_unit_area);

			/* reflash max raw data */
			if (lum_max < lum) {
				lum_max = lum;
				idx_max = win_idx;
			}
			/* reflash sum of raw data */
			lum_sum += lum;
		}
	}

	ae_data->lum_max = lum_max;
	ae_data->lum_sum = lum_sum;

	print_debug("%s, idx_max:%d, lum_max:0x%x, lum_sum:0x%x, current_y:0x%x",
		__func__, idx_max, lum_max, lum_sum, get_current_y());
}

static u32 ispv1_focus_get_win_lum(mini_lum_win_info_s *lum_info)
{
	u32 lum[4];
	u32 lum_sum;

	lum[0]= get_win_lum(lum_info->index[0]); lum[0] /= (lum_info->width * lum_info->height);
	lum[1]= get_win_lum(lum_info->index[1]); lum[1] /= (lum_info->width * lum_info->height);
	lum[2]= get_win_lum(lum_info->index[2]); lum[2] /= (lum_info->width * lum_info->height);
	lum[3]= get_win_lum(lum_info->index[3]); lum[3] /= (lum_info->width * lum_info->height);

	lum_sum = lum[0] + lum[1] + lum[2] + lum[3];
	lum_sum /= 4;

	return(ispv1_convert_win_lum(lum_sum, lum_table, ARRAY_SIZE(lum_table)));
}

/*
 **************************************************************************
 * FunctionName: ispv1_get_single_win_raw_lum;
 * Description : NA;
 * Input       : win_idx:index of luminance window,
 *			stat_unit_area:area of minimum luminance stat window;
 * Output      : NA;
 * ReturnValue : lum:luminance of minimum luminance stat window;
 * Other       : NA;
 **************************************************************************
 */
static u32 ispv1_get_single_win_raw_lum(u8 win_idx, u32 stat_unit_area)
{
	u32 stat_value;
	u32 lum = 0;

	stat_value = get_win_lum(win_idx)  / stat_unit_area;
	lum = ispv1_convert_win_lum(stat_value, lum_table, ARRAY_SIZE(lum_table));

	return lum;
}


static int ispv1_set_vcm_parameters(camera_focus focus_mode)
{
	int ret = 0;
	mini_vcm_info_s *vcm = get_vcm_ptr();

	print_debug("enter %s, focus_mode:%d", __func__, focus_mode);

	/*
	 * should update following params, such as:
	 * offsetInit/fullRange/coarseStep/fineStep/frameRate
	 */
	switch (focus_mode) {
	case CAMERA_FOCUS_AUTO:
	case CAMERA_FOCUS_MACRO:
	case CAMERA_FOCUS_CONTINUOUS_PICTURE:
	case CAMERA_FOCUS_CAF_FORCE_AF:
		vcm->offsetInit = vcm->infiniteDistance;
		vcm->fullRange = vcm->normalDistanceEnd;
		vcm->moveRange = RANGE_NORMAL;
		break;

	case CAMERA_FOCUS_INFINITY:
		vcm->offsetInit = vcm->infiniteDistance;
		vcm->fullRange = vcm->infiniteDistance + vcm->normalStep * 2;
		vcm->moveRange = RANGE_INFINITY;
		break;

	case CAMERA_FOCUS_CONTINUOUS_VIDEO:
	case CAMERA_FOCUS_AUTO_VIDEO:
		vcm->offsetInit = vcm->infiniteDistance;
		vcm->fullRange = vcm->videoDistanceEnd;
		vcm->moveRange = RANGE_NORMAL;
		break;
	case CAMERA_FOCUS_FIXED:
		break;
	case CAMERA_FOCUS_EDOF:
		ret = -1;
		print_error("focus mode not supported: %d", focus_mode);
		break;
	default:
		ret = -1;
		print_error("focus range mode unknow: %d", focus_mode);
		break;
	}

	if (ret == -1)
		return ret;

	if (CAMERA_FOCUS_CONTINUOUS_VIDEO == focus_mode) {
		vcm->coarseStep = vcm->videoStep;
	} else if ((RANGE_NORMAL == vcm->moveRange) || (RANGE_MACRO == vcm->moveRange)) {
		vcm->coarseStep = vcm->normalStep;
	} else if (RANGE_INFINITY == vcm->moveRange) {
		vcm->coarseStep = vcm->normalStep;
	}

	vcm->fineStep = vcm->coarseStep / 2;

	return ret;
}


int mini_ispv1_set_focus_mode(camera_focus focus_mode)
{
	print_info("Enter %s, focus_mode:%d", __func__, focus_mode);

	if(!mini_this_ispdata->sensor->af_enable)
		return 0;

	//ispv1_set_focus_range(focus_mode); //by wind
	camera_agent_set_focusmode(mini_this_ispdata->sensor->sensor_index,focus_mode);//by wind
	if(focus_mode==CAMERA_FOCUS_CONTINUOUS_PICTURE)
	{
		camera_agent_set_PreviewAFLock(mini_this_ispdata->sensor->sensor_index,0);//by wind
		camera_agent_set_PreviewAELock(mini_this_ispdata->sensor->sensor_index,0);
		camera_agent_set_PreviewAWBLock(mini_this_ispdata->sensor->sensor_index,0);

	}
	set_focus_mode(focus_mode);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_set_focus_mode_done;
 * Description : called by mini_ispv1_auto_focus();
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_set_focus_mode_done(camera_focus focus_mode)
{
	int ret = 0;
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;

	print_info("enter %s, focus mode %d", __func__, focus_mode);

	if (!sensor->af_enable) {
		print_error("This sensor not support AF!");
		return -1;
	}
	ret = ispv1_set_vcm_parameters(focus_mode);

	if (ret == -1)
		return ret;

	if ((focus_mode == CAMERA_FOCUS_CONTINUOUS_VIDEO) ||
	    (focus_mode == CAMERA_FOCUS_CONTINUOUS_PICTURE))
		ret = ispv1_setreg_af_mode(CAMERA_VIDEO_SERVO_MODE);
	else if (mini_afae_ctrl->multi_win)
		ret = ispv1_setreg_af_mode(CAMERA_WEIGHTED_SNAPSHOT_MODE);
	else
		ret = ispv1_setreg_af_mode(CAMERA_SINGLE_SNAPSHOT_MODE);

	if (ret) {
		print_error("%s:line %d error", __func__, __LINE__);
		return -EINVAL;
	}

	return ret;
}

int mini_ispv1_set_focus_zoom(u32 zoom)
{
	mini_ispv1_set_focus_area(&mini_afae_ctrl->af_area, zoom);
	mini_afae_ctrl->zoom = zoom;
	return 0;
}

int mini_ispv1_set_sharpness_zoom(u32 zoom)
{
	u32 max_sharpness;
	u32 min_sharpness;
	u32 sharpness;
	u32 ratio;

	mini_effect_params *effect = get_effect_ptr();
	mini_sharpness_cfg_s *this_sharpness = effect->sharpness;
	max_sharpness = this_sharpness[0].sharpness_preview;
	min_sharpness = this_sharpness[0].sharpness_capture;

	ratio = isp_zoom_to_ratio(zoom, 0);
	print_debug("enter %s, ratio: 0x%0x", __func__, ratio);

	sharpness = max_sharpness - (max_sharpness - min_sharpness) \
			* (ratio - ISP_ZOOM_BASE_RATIO) / 0x300;

	SETREG8(REG_ISP_SHARPNESS, sharpness);

	return 0;
}

static bool ispv1_check_focus_area_changed(mini_camera_rect_s *rect1, mini_camera_rect_s *rect2)
{
	if ((rect1->left != rect2->left) || (rect1->top != rect2->top) ||
		(rect1->width != rect2->width) || (rect1->height != rect2->height))
		return true;
	else
		return false;
}

/*
 * mini_ispv1_set_focus_area just save focus area
 */
int mini_ispv1_set_focus_area(mini_focus_area_s *area, u32 zoom)
{
//	mini_camera_rect_s *current_rect;
//	mini_camera_rect_s *previous_rect;
//	u32 preview_width = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_width;
//	u32 preview_height = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_height;
//	bool ret = false;

	print_debug("enter %s", __func__);
#if 0
	/* y36721 0229 add */
	if (mini_get_focus_state() == FOCUS_STATE_CAF_RUNNING ||
		mini_get_focus_state() == FOCUS_STATE_CAF_DETECTING) {
		/*
		 * If caf is running and CAF area changed,
		 * such as face is detected,
		 * should change focus area and force start.
		 */

		/*If it is CAF and new area is differ a little with previous,
		 * should ommit it
		 */
#ifndef AF_SINGLE_WINMODE_ONLY
		current_rect = &area->rect[0];
		previous_rect = &mini_afae_ctrl->af_area.rect[0];
#else
		current_rect = &area->rect[area->focus_rect_num - 1];
			previous_rect = &mini_afae_ctrl->af_area.rect[area->focus_rect_num - 1];
#endif

		if (zoom == mini_afae_ctrl->zoom) {
			//ret = ispv1_check_rect_differ(current_rect, previous_rect, preview_width, preview_height);
			ret = ispv1_check_focus_area_changed(current_rect, previous_rect);
			if (ret == false) {
				/* if focus area not changed, return directly. */
				print_info("CAF rect not change, ommit it");
				return 0;
			}
		}

		ret = ispv1_check_rect_center(current_rect, preview_width, preview_height);
		if (ret == true) {
			/* new focus area is center focus. */
			if (mini_get_focus_state() == FOCUS_STATE_CAF_RUNNING)
				set_focus_stage(AF_RUN_STAGE_BREAK);
			set_caf_forcestart(CAF_FORCESTART_FORCEWAIT);
		} else {
			/* if large differ flag is set and CAF is running, should break current focusing and restart immediately */
			ret = ispv1_check_rect_differ(current_rect, previous_rect, preview_width, preview_height);
			if (ret == true) {
				if (mini_get_focus_state() == FOCUS_STATE_CAF_RUNNING)
					set_focus_stage(AF_RUN_STAGE_BREAK);
				set_caf_forcestart(CAF_FORCESTART_FORCE);
			} else {
				/*very small change, do nothing */
				print_info("CAF rect change little, ommit it");
				return 0;
			}
		}

		ispv1_set_focus_area_done(area, zoom);
	}

	memcpy(&mini_afae_ctrl->af_area, area, sizeof(mini_focus_area_s));
#else
       ispv1_set_focus_area_done(area, zoom);
#endif
	return 0;
}


static int ispv1_set_focus_area_done(mini_focus_area_s *area, u32 zoom)
{
	mini_k3_isp_data *ispdata = mini_this_ispdata;
	u32 preview_width = ispdata->pic_attr[STATE_PREVIEW].out_width;
	u32 preview_height = ispdata->pic_attr[STATE_PREVIEW].out_height;
	u32 raw_width = ispdata->pic_attr[STATE_PREVIEW].in_width;
	u32 raw_height = ispdata->pic_attr[STATE_PREVIEW].in_height;
	mini_camera_rect_s yuv_rect, yuv_in_full, raw_rect;
	/*mini_camera_rect_s merged_yuv_rect;*/
	mini_focus_win_info_s win_info;
	int binning = 0;
	int multi_win = 0;
	int index;
	int ret;

	/*int *map_table = mini_afae_ctrl->map_table;*/

	print_debug("enter %s", __func__);

	print_debug("focus_area: focus_area_num %d", area->focus_rect_num);
	for (index = 0; index < area->focus_rect_num; index++) {
		print_debug("focus rect %d:%d,%d,%d,%d,%d", index,
					area->rect[index].left,
					area->rect[index].top,
					area->rect[index].width,
					area->rect[index].height,
					area->rect[index].weight);
	}

	memset(&win_info, 0, sizeof(mini_focus_win_info_s));

	/*y36721 changed for supporting one windows only. */
#ifndef AF_SINGLE_WINMODE_ONLY
	multi_win = (area->focus_rect_num > 1) ? 1 : 0;
#else
	multi_win = 0;
#endif

	print_debug("%s, line %d: multi_win %d", __func__, __LINE__, multi_win);

	if (multi_win == 0) {
		/*y36721 changed for supporting one windows only.*/
		#ifndef AF_SINGLE_WINMODE_ONLY
		memcpy(&yuv_rect, &area->rect[0], sizeof(mini_camera_rect_s));
		#else
		memcpy(&yuv_rect, &area->rect[area->focus_rect_num - 1], sizeof(mini_camera_rect_s));
		#endif

		/* check width and height are valid, then adjust it. */
	if (yuv_rect.width == 0 || yuv_rect.height == 0) {
		win_info.left = 0;
		win_info.top = 0;
		win_info.width = 0;
		win_info.height = 0;
		win_info.width1 = 0;
		win_info.height1 = 0;
		camera_agent_set_focusarea(&win_info);//by wind
		return 0;
		ispv1_focus_get_default_yuvrect(&yuv_rect, preview_width, preview_height);
		print_debug("default yuv rect:%d,%d,%d,%d",
		    yuv_rect.left, yuv_rect.top, yuv_rect.width, yuv_rect.height);
	}

	/* most case is just one focus rect. */
	if ((yuv_rect.left + yuv_rect.width) > preview_width || (yuv_rect.top + yuv_rect.height) > preview_height) {
		print_error("%s, line %d: rect area error!", __func__, __LINE__);
		return -1;
		}

	memcpy(&yuv_in_full, &yuv_rect, sizeof(mini_camera_rect_s));
	print_debug("focus AE focus step1:[%d,%d:%d x %d], zoom %d", yuv_in_full.left, yuv_in_full.top, yuv_in_full.width, yuv_in_full.height, zoom);
	ispv1_get_yuvrect_of_full(&ispdata->pic_attr[STATE_PREVIEW], &yuv_in_full, zoom);
	print_debug("focus AE focus step2:[%d,%d:%d x %d], zoom %d", yuv_in_full.left, yuv_in_full.top, yuv_in_full.width, yuv_in_full.height, zoom);

	/* adjust yuv rect. */
	ispv1_focus_adjust_yuvrect(&yuv_in_full, preview_width, preview_height, zoom);
	print_debug("focus AE focus step3:[%d,%d:%d x %d], zoom %d", yuv_in_full.left, yuv_in_full.top, yuv_in_full.width, yuv_in_full.height, zoom);

	/* convert back to modified app rect for contrast calculate */
	memcpy(&yuv_rect, &yuv_in_full, sizeof(mini_camera_rect_s));
	ispv1_get_yuvrect_of_app(&ispdata->pic_attr[STATE_PREVIEW], &yuv_rect, zoom);
	print_debug("focus AE focus step4:[%d,%d:%d x %d], zoom %d", yuv_rect.left, yuv_rect.top, yuv_rect.width, yuv_rect.height, zoom);

	/* convert yuv rect to raw rect. */
	ret = mini_k3_isp_yuvrect_to_rawrect2(&yuv_in_full, &raw_rect);
		if (ret) {
			print_error("%s, line %d: error", __func__, __LINE__);
			return ret;
		}

		win_info.left = raw_rect.left;
		win_info.top = raw_rect.top;
		win_info.width = raw_rect.width;
		win_info.height = raw_rect.height;
		win_info.width1 = 0;
		win_info.height1 = 0;

		print_debug("win_info before %d:%d:%d:%d", win_info.left, win_info.top, win_info.width, win_info.height);

		goto setreg_out;
	}
#ifndef AF_SINGLE_WINMODE_ONLY
#endif

setreg_out:
	mini_afae_ctrl->binning = binning;
	mini_afae_ctrl->multi_win = multi_win;

	ispv1_focus_adjust_rawwin(&win_info, raw_width, raw_height);
	print_debug("win_info after %d:%d:%d:%d", win_info.left, win_info.top, win_info.width, win_info.height);

	/* Set ISP defined rects to ISP register */
	//ispv1_setreg_focus_win(&win_info); //by wind
	camera_agent_set_focusarea(&win_info);//by wind
	ispv1_focus_get_lumwin_info(&win_info, raw_width, raw_height, &mini_afae_ctrl->lum_info);

	mini_afae_ctrl->area_changed = ispv1_check_focus_area_changed(&mini_afae_ctrl->cur_rect, &yuv_rect);
	print_info("######mini_afae_ctrl->area_changed %d, lum_info[%d,%d,%d,%d]######",\
		mini_afae_ctrl->area_changed,\
		mini_afae_ctrl->lum_info.index[0],\
		mini_afae_ctrl->lum_info.index[1],\
		mini_afae_ctrl->lum_info.index[2],\
		mini_afae_ctrl->lum_info.index[3]);

	memcpy(&mini_afae_ctrl->cur_rect, &yuv_rect, sizeof(mini_camera_rect_s));

	return 0;
}

/*
 **************************************************************************
 * FunctionName: mini_ispv1_get_focus_result;
 * Description : get focus result
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : STATUS_FOCUSING, STATUS_FOCUSED, STATUS_OUT_FOCUS
 * Other       : NA;
 **************************************************************************
 */
int mini_ispv1_get_focus_result(mini_focus_result_s *result)
{
	u32 win_idx = 0;
	u32 rect_idx = 0;
	int status;
	focused_result_s isp_result;
	int ret = 0;

	mini_focus_area_s *area;
	int *map_table;

	print_debug("enter %s", __func__);

	if(!mini_this_ispdata->sensor->af_enable) {
		return 0;
	}

    if (!result)
    {
        printk("!!!!!ASSERT ERROR!!!!");
        return -1;
    }
#if 1 //by wind
	memset(result, 0, sizeof(mini_focus_result_s));
	status = ispv1_getreg_focus_result(&isp_result, mini_afae_ctrl->multi_win);
	if (status != STATUS_FOCUSED) {
		result->status = status;
		ret = -1;
		goto out;
	}

	result->status = STATUS_FOCUSED;
	result->each_status[0] = STATUS_FOCUSED;
	//print_info("enter %s status = %d", __func__,status);
	return ret; //by wind
#endif	  //by wind
	area = &mini_afae_ctrl->af_area;
	map_table = mini_afae_ctrl->map_table;


	memset(result, 0, sizeof(mini_focus_result_s));
	mini_afae_ctrl->focus_failed = 0;

	status = ispv1_getreg_focus_result(&isp_result, mini_afae_ctrl->multi_win);
	if (status != STATUS_FOCUSED) {
		result->status = status;

		/* added reason: if last time out focus, then maybe also not run in continus mode */
		if ((result->status == STATUS_OUT_FOCUS) && (get_focus_mode() == CAMERA_FOCUS_AUTO)) {
			mini_afae_ctrl->focus_failed = 1;
		}

		ret = -1;
		goto out;
	}

	/* If it is focused and single win mode, then just set status and each_status[0]. */
	if (mini_afae_ctrl->multi_win == 0) {
		result->status = STATUS_FOCUSED;

		/*y36721 changed for supporting one windows only.*/
		#ifndef AF_SINGLE_WINMODE_ONLY
			result->each_status[0] = STATUS_FOCUSED;
		#else
			for (win_idx = 0; win_idx < isp_result.focused_win_num; win_idx++) {
				result->each_status[win_idx] = STATUS_FOCUSED;
			}
		#endif
	} else {
		/*
		 * If it is focused and multi win mode,
		 * then search map table and set result.
		 * use ISP defined win id to get user defined rect id.
		 */
		result->status = STATUS_FOCUSED;
		for (win_idx = 0; win_idx < isp_result.focused_win_num; win_idx++) {
			for (rect_idx = 0; rect_idx < area->focus_rect_num; rect_idx++) {
				if (*(map_table + rect_idx * ISP_MAX_FOCUS_WIN + isp_result.focused_win[win_idx]) == 1) {
					result->each_status[rect_idx] = STATUS_FOCUSED;
				}
			}
		}
	}

out:
	return ret;
}

/*
 * Default metering rect is like that:
 * SPOT is rect of quarter width and quarter height
 * CWA is  rect of half width and half height
 * AVERAGE is all of preview region;
 */
static int ispv1_get_default_metering_rect(camera_metering metering,
				mini_camera_rect_s *yuv, u32 out_width, u32 out_height)
{
	int retvalue = 0;
	mini_effect_params *effect = get_effect_ptr();
	mini_percent_s *win3x3_param = effect->ae_param.ae_win.win_3x3;

	u8 spot_width_percent = win3x3_param[CAMERA_METERING_SPOT].percent_w;
	u8 spot_height_percent = win3x3_param[CAMERA_METERING_SPOT].percent_h;
	u8 cwa_width_percent = win3x3_param[CAMERA_METERING_CWA].percent_w;
	u8 cwa_height_percent = win3x3_param[CAMERA_METERING_CWA].percent_h;
	u8 average_width_percent = win3x3_param[CAMERA_METERING_AVERAGE].percent_w;
	u8 average_height_percent = win3x3_param[CAMERA_METERING_AVERAGE].percent_h;
	print_debug("enter %s", __func__);

	switch (metering) {
	case CAMERA_METERING_SPOT:
		yuv->width = out_width * spot_width_percent / 100;
		yuv->height = out_height * spot_height_percent / 100;
		yuv->left = out_width * (100 - spot_width_percent) / 200;
		yuv->top = out_height * (100 - spot_height_percent) / 200;
		break;

	case CAMERA_METERING_CWA:
		yuv->width = out_width * cwa_width_percent / 100;
		yuv->height = out_height * cwa_height_percent / 100;
		yuv->left = out_width * (100 - cwa_width_percent) / 200;
		yuv->top = out_height * (100 - cwa_height_percent) / 200;
		break;

	case CAMERA_METERING_AVERAGE:
		yuv->width = out_width * average_width_percent / 100;
		yuv->height = out_height * average_height_percent / 100;
		yuv->left = out_width * (100 - average_width_percent) / 200;
		yuv->top = out_height * (100 - average_height_percent) / 200;
		break;

	default:
		retvalue = -1;
		print_error("metering mode invalid!");
		goto out;
		break;
	}

out:
	return retvalue;

}

/*
 * Called by mini_ispv1_set_metering_area
 */
static int ispv1_setreg_metering_area(mini_camera_rect_s *raw, u32 raw_width, u32 raw_height, int roi)
{
	mini_effect_params *effect = get_effect_ptr();
	mini_ae_win_s *this_ae_win_params = &effect->ae_param.ae_win;
	u8 *default_weight = this_ae_win_params->default_weight;
	u8 default_weight_shift = this_ae_win_params->default_weight_shift;
	u8 *touch_weight = this_ae_win_params->touch_weight;
	u8 touch_weight_shift = this_ae_win_params->touch_weight_shift;
	print_debug("enter %s", __func__);

	/*
	 * Just care about center 3x3 windows. 3x3 weight is all 1.
	 * Long&short exposure are same
	 * set raw rect to ISP registers
	 */
	if (raw->height < 80)
		raw->height = 80;

	if (raw->width < 80)
		raw->width = 80;

	if ((raw->top + raw->height) > raw_height)
		raw->top -= (raw->top + raw->height) - raw_height;

	if ((raw->left + raw->width) > raw_width)
		raw->left -= (raw->left + raw->width) - raw_width;
	camera_agent_set_meteringarea(raw);//by wind
	if (roi == 0) {
		SETREG16(REG_ISP_AECAGC_CENTER_LEFT, raw->left);
		SETREG16(REG_ISP_AECAGC_CENTER_LEFT_SHORT, raw->left);
		SETREG16(REG_ISP_AECAGC_CENTER_TOP, raw->top);
		SETREG16(REG_ISP_AECAGC_CENTER_TOP_SHORT, raw->top);

		SETREG16(REG_ISP_AECAGC_CENTER_WIDTH, raw->width);
		SETREG16(REG_ISP_AECAGC_CENTER_WIDTH_SHORT, raw->width);

		SETREG16(REG_ISP_AECAGC_CENTER_HEIGHT, raw->height);
		SETREG16(REG_ISP_AECAGC_CENTER_HEIGHT_SHORT, raw->height);

		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_IN, 1);
		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_IN_SHORT, 1);
		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_OUT, 1);
		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_OUT_SHORT, 1);

		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(0), default_weight[0]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(1), default_weight[1]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(2), default_weight[2]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(3), default_weight[3]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(4), default_weight[4]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(5), default_weight[5]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(6), default_weight[6]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(7), default_weight[7]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(8), default_weight[8]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(9), default_weight[9]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(10), default_weight[10]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(11), default_weight[11]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(12), default_weight[12]);

		//weight shift
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT_SHIFT, default_weight_shift);
	} else {
	#if 0 //real roi mode
		SETREG16(REG_ISP_AECAGC_ROI_LEFT, raw->left);
		SETREG16(REG_ISP_AECAGC_ROI_LEFT_SHORT, raw->left);
		SETREG16(REG_ISP_AECAGC_ROI_TOP, raw->top);
		SETREG16(REG_ISP_AECAGC_ROI_TOP_SHORT, raw->top);

		SETREG16(REG_ISP_AECAGC_ROI_RIGHT, (raw_width - (raw->left + raw->width)));
		SETREG16(REG_ISP_AECAGC_ROI_RIGHT_SHORT, (raw_width - (raw->left + raw->width)));
		SETREG16(REG_ISP_AECAGC_ROI_BOTTOM, (raw_height - (raw->top + raw->height)));
		SETREG16(REG_ISP_AECAGC_ROI_BOTTOM_SHORT, (raw_height - (raw->top + raw->height)));

		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_IN, 1);
		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_IN_SHORT, 1);
		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_OUT, 0);
		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_OUT_SHORT, 0);
	#else //enhanced 3x3 win mode
		SETREG16(REG_ISP_AECAGC_CENTER_LEFT, raw->left);
		SETREG16(REG_ISP_AECAGC_CENTER_LEFT_SHORT, raw->left);
		SETREG16(REG_ISP_AECAGC_CENTER_TOP, raw->top);
		SETREG16(REG_ISP_AECAGC_CENTER_TOP_SHORT, raw->top);

		SETREG16(REG_ISP_AECAGC_CENTER_WIDTH, raw->width);
		SETREG16(REG_ISP_AECAGC_CENTER_WIDTH_SHORT, raw->width);

		SETREG16(REG_ISP_AECAGC_CENTER_HEIGHT, raw->height);
		SETREG16(REG_ISP_AECAGC_CENTER_HEIGHT_SHORT, raw->height);

		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_IN, 1);
		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_IN_SHORT, 1);
		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_OUT, 1);
		SETREG8(REG_ISP_AECAGC_ROI_WEIGHT_OUT_SHORT, 1);

		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(0), touch_weight[0]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(1), touch_weight[1]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(2), touch_weight[2]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(3), touch_weight[3]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(4), touch_weight[4]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(5), touch_weight[5]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(6), touch_weight[6]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(7), touch_weight[7]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(8), touch_weight[8]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(9), touch_weight[9]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(10), touch_weight[10]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(11), touch_weight[11]);
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT(12), touch_weight[12]);

		//weight shift
		SETREG8(REG_ISP_AECAGC_WIN_WEIGHT_SHIFT, touch_weight_shift);
	#endif
	}

	return 0;
}

static void ispv1_setreg_ae_statwin(u32 left, u32 top, u32 right, u32 bottom)
{
	SETREG16(REG_ISP_AECAGC_STATWIN_LEFT, left);
	SETREG16(REG_ISP_AECAGC_STATWIN_TOP, top);
	SETREG16(REG_ISP_AECAGC_STATWIN_RIGHT, right);
	SETREG16(REG_ISP_AECAGC_STATWIN_BOTTOM, bottom);
}

int mini_ispv1_set_ae_statwin(mini_pic_attr_t *pic_attr, mini_coordinate_s *center, METERING_STATWIN_MODE statwin_mode, u32 zoom)
{
	mini_camera_rect_s yuv;
	mini_camera_rect_s raw;
	int left, top, right, bottom;
	int ratio = isp_zoom_to_ratio(zoom, 0);
	u32 statwin_percent;
	mini_coordinate_s phy_center;

	if (statwin_mode == METERING_STATWIN_NORMAL) {
		ratio = afae_adjust_zoom_ratio(ratio, ISP_ZOOM_BASE_RATIO, ISP_ZOOM_MAX_RATIO, 0x200);
	}

	phy_center.x = pic_attr->out_width / 2;
	phy_center.y = pic_attr->out_height / 2;

	if (center->x >= pic_attr->out_width)
		center->x = pic_attr->out_width;

	if (center->y >= pic_attr->out_height)
		center->y = pic_attr->out_height;

	/* original yuv center */
	print_debug("focus AE %s before yuv center[x %d,y %d], phy_center[x %d,y %d]",
		__func__, center->x, center->y, phy_center.x, phy_center.y);
	center->x = (int)phy_center.x + ((int)center->x - (int)phy_center.x) * 0x100 / ratio;
	center->y = (int)phy_center.y + ((int)center->y - (int)phy_center.y) * 0x100 / ratio;
	print_debug("focus AE %s new yuv center[x %d,y %d]", __func__, (int)center->x, (int)center->y);

	if (statwin_mode == METERING_STATWIN_ENHANCE_BRIGHT)
		statwin_percent = METERING_ROIWIN_BRIGHT_PERCENT;
	else if (statwin_mode == METERING_STATWIN_ENHANCE_DARK)
		statwin_percent = METERING_ROIWIN_DARK_PERCENT;
	else
		statwin_percent = METERING_AECAGC_WINDOW_PERCENT;

	/* get yuv rect of stat win */
	yuv.width = pic_attr->out_width * statwin_percent / 100 \
		* ISP_ZOOM_BASE_RATIO / ratio;
	yuv.height = pic_attr->out_height * statwin_percent / 100 \
		* ISP_ZOOM_BASE_RATIO / ratio;

	left = (int)center->x - (int)yuv.width / 2;
	top = (int)center->y - (int)yuv.height / 2;

	yuv.left = (left > 0) ? left : 0;
	yuv.top = (top > 0) ? top : 0;

	if (mini_k3_isp_yuvrect_to_rawrect2(&yuv, &raw)) {
		print_error("%s:line %d error", __func__, __LINE__);
		return -1;
	}

	/* adjust and set stat win */
	left = raw.left;
	top = raw.top;

	raw.width = (raw.width < MIN_STAT_RAW_WIDTH) ? MIN_STAT_RAW_WIDTH : raw.width;
	raw.height = (raw.height < MIN_STAT_RAW_HEIGHT) ? MIN_STAT_RAW_HEIGHT : raw.height;

	right = pic_attr->in_width - raw.left - raw.width;
	right = (right < 0) ? 0 : right;

	bottom = pic_attr->in_height - raw.top - raw.height;
	bottom = (bottom < 0) ? 0 : bottom;

	print_debug("focus AE %s new raw stat win mode %d,[%d,%d,%d,%d]",
		__func__, statwin_mode, left, top, right, bottom);

	ispv1_setreg_ae_statwin(left, top, right, bottom);
	return 0;
}

int mini_ispv1_set_gsensor_stat(mini_axis_triple *xyz)
{
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	int interval;

	if (!sensor->af_enable) {
		return -1;
	}

	interval = (xyz->time.tv_sec - mini_mXYZ.time.tv_sec) * 1000
		+ (xyz->time.tv_usec - mini_mXYZ.time.tv_usec) / 1000;
	mini_afae_ctrl->gsensor_interval = interval;

	memcpy(&mini_mXYZ, xyz, sizeof(mini_axis_triple));
	print_debug("%s: ts %dms, current xyz: 0x%4x,  0x%4x, 0x%4x",
		__func__, (int)(mini_mXYZ.time.tv_sec * 1000 + mini_mXYZ.time.tv_usec / 1000), mini_mXYZ.x, mini_mXYZ.y, mini_mXYZ.z);
	return 0;
}

/*
 * Added for metering mode
 * spot, CWA, average
 */
int mini_ispv1_set_metering_mode(camera_metering mode)
{
	print_debug("enter %s, mode %d", __func__, mode);

	this_metering = mode;
	return 0;
}

int mini_ispv1_set_metering_area(mini_metering_area_s *area, u32 zoom)
{
	mini_k3_isp_data *ispdata = mini_this_ispdata;
	u32 loopi;
	u32 preview_width = ispdata->pic_attr[STATE_PREVIEW].out_width;
	u32 preview_height = ispdata->pic_attr[STATE_PREVIEW].out_height;
	u32 in_width = ispdata->pic_attr[STATE_PREVIEW].in_width;
	u32 in_height = ispdata->pic_attr[STATE_PREVIEW].in_height;

	mini_camera_rect_s yuv;
	mini_camera_rect_s raw;
	bool roi_flag = false;
	mini_coordinate_s center;
	bool enhance_flag = false;
	METERING_STATWIN_MODE statwin_mode = METERING_STATWIN_NORMAL;

	print_debug("enter %s", __func__);

	if (ispdata->sensor->isp_location == CAMERA_USE_SENSORISP)
		return 0;

	if (NULL == area) {
		print_error("%s:no metering area", __func__);
		return -1;
	}

	for (loopi = 0; loopi < area->metering_rect_num; loopi++) {
		print_info("metering rect %d: %d,%d,%d,%d,weight %d",
			   loopi,
			   area->rect[loopi].left, area->rect[loopi].top,
			   area->rect[loopi].width, area->rect[loopi].height,
			   area->rect[loopi].weight);
	}

	/* y36721 2012-03-28
	 * set ROI metering before take picture when auto focus not selected.
	 */
	memcpy(&yuv, &area->rect[0], sizeof(mini_camera_rect_s));

	/* check width and height are valid, then adjust it. */
	if (yuv.width == 0 || yuv.height == 0) {
		camera_agent_set_meteringarea(&yuv);//by wind
		return 0;
        ispv1_get_default_metering_rect(this_metering, &yuv, preview_width, preview_height);
		roi_flag = false;
	} else {
		roi_flag = true;
	}
	print_debug("focus AE metering step1:ori_rect[%d,%d:%d x %d]", yuv.left, yuv.top, yuv.width, yuv.height);

	ispv1_get_yuvrect_of_full(&ispdata->pic_attr[STATE_PREVIEW], &yuv, zoom);
	print_debug("focus AE metering step2:rect_of_full[%d,%d:%d x %d]", yuv.left, yuv.top, yuv.width, yuv.height);
	if (mini_k3_isp_yuvrect_to_rawrect2(&yuv, &raw)) {
		print_error("%s:line %d error", __func__, __LINE__);
		return -1;
	}

	ispv1_setreg_metering_area(&raw, in_width, in_height, roi_flag);
	print_debug("focus AE metering step3:get raw[%d,%d:%d x %d]", raw.left, raw.top, raw.width, raw.height);

	if (roi_flag == true) {
		enhance_flag = ispv1_check_metering_area_enhance(&ispdata->pic_attr[STATE_PREVIEW], &raw);
		if (enhance_flag == true) {
			statwin_mode = METERING_STATWIN_ENHANCE_BRIGHT;
			restore_target_high();
		} else {
			statwin_mode = METERING_STATWIN_ENHANCE_DARK;
			set_near_target();
		}

		center.x = area->rect[0].left + area->rect[0].width/2;
		center.y = area->rect[0].top + area->rect[0].height/2;
	}
	else {

		statwin_mode = METERING_STATWIN_NORMAL;
		restore_target_high();
		center.x = preview_width/2;
		center.y = preview_height/2;
	}

	/*
	 * first convert current center position to new center of full yuv plane
	 * then get stat win rect and convert to raw, then set to stat win registers.
	 */
	mini_ispv1_set_ae_statwin(&ispdata->pic_attr[STATE_PREVIEW], &center, statwin_mode, zoom);

	return 0;
}


int mini_ispv1_set_focus_range(camera_focus focus_mode)
{
	int ret = 0;
	int val_vcm = 0;
	mini_vcm_info_s *vcm = get_vcm_ptr();

	if(!mini_this_ispdata->sensor->af_enable)
		return 0;
	print_debug("enter %s, focus_mode:%d", __func__, focus_mode);
	ret = ispv1_set_vcm_parameters(focus_mode);

	if (ret == -1)
		return ret;

	val_vcm = get_focus_code();
	if (val_vcm < vcm->offsetInit) {
		ispv1_setreg_vcm_code(vcm->offsetInit);
	} else if (val_vcm > vcm->fullRange) {
		ispv1_setreg_vcm_code(vcm->fullRange);
	}
	return ret;
}

/*
 **************************************************************************
 * FunctionName: mini_ispv1_get_focus_distance;
 * Description : get focus_distance value ( cm )
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_ispv1_get_focus_distance(void)
{
	/* just reserve interface */
	return 0;
}


static bool ispv1_focus_need_flash(u32 cur_lum, u32 cur_gain, bool summary, bool support_summary)
{
	bool ret = false;
	u8 compare_lum;
	mini_effect_params *effect = get_effect_ptr();
	mini_assistant_af_s *this_asst_af = &effect->flash.assistant_af;
	if ((summary == false)
	&&(true == support_summary)){
		cur_gain /= 2;
	}
	if (cur_gain < this_asst_af->gainth_high) {
		compare_lum = this_asst_af->lumth_1ow + (cur_gain - 0x10) / 0x10 * 4;
		if (cur_lum <= compare_lum)
			ret = true;
		else
			ret = false;
	} else {
		ret = true;
	}

	return ret;
}


static void ispv1_assistant_af(bool action)
{
	mini_camera_flashlight *flashlight = mini_get_camera_flash();
	mini_effect_params *effect = get_effect_ptr();
	flash_lum_level lum_level1 = effect->flash.assistant_af.flash_level;
	print_debug("enter %s,action:%d", __func__, action);
	if (flashlight == NULL)
		return;

	if (true == action) {
		mini_ispv1_config_aecawb_step(true, &mini_isp_hw_data.aecawb_step);
		flashlight->turn_on(TORCH_MODE, lum_level1);
	} else {
		mini_ispv1_config_aecawb_step(false, &mini_isp_hw_data.aecawb_step);
		flashlight->turn_off();
	}
}


static bool ispv1_af_flash_needed(mini_camera_sensor *sensor, camera_flash flash_mode, mini_lum_win_info_s lum_info)
{
	u32 index = sensor->preview_frmsize_index;
	bool summary = sensor->frmsize_list[index].summary;
	bool support_summary = sensor->support_summary;
	u32 cur_lum;
	u32 cur_gain;
	bool ret = false;

	if (mini_get_focus_state() == FOCUS_STATE_AF_PREPARING) {
		cur_lum = ispv1_focus_get_win_lum(&lum_info);
		cur_gain = get_writeback_gain();
		if (((CAMERA_FLASH_AUTO ==  flash_mode) || (CAMERA_FLASH_ON == flash_mode))
			&& (true == ispv1_focus_need_flash(cur_lum, cur_gain, summary, support_summary))) {
			ret = true;
		}
	}
	return ret;
}


static void ispv1_af_flash_check_open(void)
{
	mini_camera_sensor *sensor =  mini_this_ispdata->sensor;
	u8 framerate = sensor->fps;
	u32 cur_lum;
	u8 over_expo_th = GETREG8(REG_ISP_TARGET_Y_HIGH) + DEFAULT_FLASH_AEC_FAST_STEP;
	u8 frame_count = 0;

	if (mini_this_ispdata->af_need_flash == true) {
		ispv1_assistant_af(true);
		mini_this_ispdata->assistant_af_flash = true;
		msleep((1000 / framerate) * 2);
		cur_lum = get_current_y();
		while ((frame_count++ < FLASH_TEST_MAX_COUNT) &&
			(cur_lum > over_expo_th) && (mini_get_focus_state() != FOCUS_STATE_STOPPED)) {
			msleep(1000 / framerate);
			cur_lum = get_current_y();
		}
		print_debug("%s, af_need_flash:%d, frame_cout:%d, focus_state:%d, cur_lum:0x%x, over_expo_th:0x%x",
			__func__, mini_this_ispdata->af_need_flash, frame_count, mini_get_focus_state(), cur_lum, over_expo_th);
	}
}


static void ispv1_af_flash_check_close(void)
{
	mini_camera_sensor *sensor =  mini_this_ispdata->sensor;
	u8 framerate = sensor->fps;

	print_debug("%s, af_need_flash:%d", __func__, mini_this_ispdata->af_need_flash);
	if (true == mini_this_ispdata->assistant_af_flash) {
		ispv1_assistant_af(false);
		msleep((1000 / framerate) * 3);
		mini_this_ispdata->assistant_af_flash = false;
	}
	mini_this_ispdata->af_need_flash = false;
}

static int ispv1_focus_status_collect(mini_focus_frame_stat_s *curr_data, mini_focus_frame_stat_s *mean_data)
{
	int loopi;
	u32 variance[5] = {0, 0, 0, 0, 0};
	u32 contrast_diff = 0;
	u32 lum_diff = 0;
	mini_axis_triple xyz_diff = {0, 0, 0};
	int stat_cnt;
	mini_effect_params *effect = get_effect_ptr();
	mini_caf_trigger_s *this_caf_trigger = &effect->af_param.focus_algo.caf_trigger;
	int caf_stat_cmp_frames =
		this_caf_trigger->stat_cmp_end_frame - this_caf_trigger->stat_cmp_start_frame + 1;

	mini_afae_ctrl->focus_stat_frames++;

	/* skip first frame, and get mean of next 4 frames contrast/gain/expo/lum value as compare data. */
	if ((mini_afae_ctrl->focus_stat_frames >= this_caf_trigger->stat_cmp_start_frame)
		&& (mini_afae_ctrl->focus_stat_frames <= this_caf_trigger->stat_cmp_end_frame)) {
		mini_afae_ctrl->compare_data.contrast += curr_data->contrast;
		mini_afae_ctrl->compare_data.lum += curr_data->lum;
		mini_afae_ctrl->compare_data.ae += curr_data->ae;
		mini_afae_ctrl->compare_data.rbratio += curr_data->rbratio;
		mini_afae_ctrl->compare_data.xyz.x += curr_data->xyz.x;
		mini_afae_ctrl->compare_data.xyz.y += curr_data->xyz.y;
		mini_afae_ctrl->compare_data.xyz.z += curr_data->xyz.z;

		if (mini_afae_ctrl->focus_stat_frames == this_caf_trigger->stat_cmp_end_frame) {
			mini_afae_ctrl->compare_data.contrast /= caf_stat_cmp_frames;
			mini_afae_ctrl->compare_data.lum /= caf_stat_cmp_frames;
			mini_afae_ctrl->compare_data.ae /= caf_stat_cmp_frames;
			mini_afae_ctrl->compare_data.rbratio /= caf_stat_cmp_frames;
			mini_afae_ctrl->compare_data.xyz.x /= caf_stat_cmp_frames;
			mini_afae_ctrl->compare_data.xyz.y /= caf_stat_cmp_frames;
			mini_afae_ctrl->compare_data.xyz.z /= caf_stat_cmp_frames;

			/*
			 * init all frame's contrast/gain/expo/lum array as compare data.
			 * used in preview tasklet to judge scene switch.
			 */
			for (loopi = 0; loopi < this_caf_trigger->stat_frame; loopi++) {
				memcpy(&mini_afae_ctrl->frame_stat[loopi], &mini_afae_ctrl->compare_data,
					sizeof(mini_focus_frame_stat_s));
			}
		}
	}

	if (mini_afae_ctrl->focus_stat_frames <= this_caf_trigger->stat_skip_frame)
		return -1;

	if (curr_data->fps <= 20)
		stat_cnt = this_caf_trigger->stat_frame_low;
	else
		stat_cnt = this_caf_trigger->stat_frame;

	/* update new contrast/gain/expo/lum value array */
	memcpy(&mini_afae_ctrl->frame_stat[0], &mini_afae_ctrl->frame_stat[1],
		(stat_cnt - 1) * sizeof(mini_focus_frame_stat_s));

	memcpy(&mini_afae_ctrl->frame_stat[stat_cnt - 1], curr_data,
		sizeof(mini_focus_frame_stat_s));

	/* calculate current mean contrast/gain/expo/lum */
	memset(mean_data, 0, sizeof(mini_focus_frame_stat_s));
	for (loopi = 0; loopi < stat_cnt; loopi++) {
		mean_data->contrast += mini_afae_ctrl->frame_stat[loopi].contrast;
		mean_data->lum += mini_afae_ctrl->frame_stat[loopi].lum;
		mean_data->ae += mini_afae_ctrl->frame_stat[loopi].ae;
		mean_data->rbratio += mini_afae_ctrl->frame_stat[loopi].rbratio;
		mean_data->xyz.x += mini_afae_ctrl->frame_stat[loopi].xyz.x;
		mean_data->xyz.y += mini_afae_ctrl->frame_stat[loopi].xyz.y;
		mean_data->xyz.z += mini_afae_ctrl->frame_stat[loopi].xyz.z;
	}

	mean_data->contrast /= stat_cnt;
	mean_data->lum /= stat_cnt;
	mean_data->ae /= stat_cnt;
	mean_data->rbratio /= stat_cnt;
	mean_data->xyz.x /= stat_cnt;
	mean_data->xyz.y /= stat_cnt;
	mean_data->xyz.z /= stat_cnt;

	for (loopi = 0; loopi < stat_cnt; loopi++) {
		/* use last stat data as base calculate value */
		variance[0] = abs(mini_afae_ctrl->frame_stat[loopi].contrast - mini_afae_ctrl->frame_stat[stat_cnt - 1].contrast);
		variance[1] = abs(mini_afae_ctrl->frame_stat[loopi].lum - mini_afae_ctrl->frame_stat[stat_cnt - 1].lum);
		variance[2] = abs(mini_afae_ctrl->frame_stat[loopi].xyz.x - mini_afae_ctrl->frame_stat[stat_cnt - 1].xyz.x);
		variance[3] = abs(mini_afae_ctrl->frame_stat[loopi].xyz.y - mini_afae_ctrl->frame_stat[stat_cnt - 1].xyz.y);
		variance[4] = abs(mini_afae_ctrl->frame_stat[loopi].xyz.z - mini_afae_ctrl->frame_stat[stat_cnt - 1].xyz.z);

		variance[0] *= variance[0];
		variance[1] *= variance[1];
		variance[2] *= variance[2];
		variance[3] *= variance[3];
		variance[4] *= variance[4];

		contrast_diff += variance[0];
		lum_diff += variance[1];
		xyz_diff.x += variance[2];
		xyz_diff.y += variance[3];
		xyz_diff.z += variance[4];
	}
	contrast_diff /= stat_cnt;
	lum_diff /= stat_cnt;
	xyz_diff.x /= stat_cnt;
	xyz_diff.y /= stat_cnt;
	xyz_diff.z /= stat_cnt;

	mean_data->contrast_var = contrast_diff;
	mean_data->lum_var = lum_diff;
	mean_data->xyz_var.x = xyz_diff.x;
	mean_data->xyz_var.y = xyz_diff.y;
	mean_data->xyz_var.z = xyz_diff.z;

	return 0;
}

static void ispv1_focus_status_reset(void)
{
	mini_afae_ctrl->focus_stat_frames = 0;
	set_caf_forcestart(CAF_FORCESTART_CLEAR); /* clear force start bits */
	memset(&mini_afae_ctrl->compare_data, 0, sizeof(mini_focus_frame_stat_s));
}


static u16 ispv1_calc_frame_stat_diff(mini_focus_frame_stat_s *pre_data, mini_focus_frame_stat_s *cur_data)
{
	u16 ret_val = 0;
	mini_focus_frame_stat_s diff;
	mini_effect_params *effect = get_effect_ptr();
	mini_caf_trigger_s *this_caf_trigger = &effect->af_param.focus_algo.caf_trigger;

	diff.contrast = abs(pre_data->contrast - cur_data->contrast);
	diff.lum = abs(pre_data->lum - cur_data->lum);
	diff.ae = abs(pre_data->ae - cur_data->ae);
	diff.rbratio= abs(pre_data->rbratio - cur_data->rbratio);

	diff.xyz.x = abs(pre_data->xyz.x - cur_data->xyz.x);
	diff.xyz.y = abs(pre_data->xyz.y - cur_data->xyz.y);
	diff.xyz.z = abs(pre_data->xyz.z - cur_data->xyz.z);

	if ((diff.contrast >= (pre_data->contrast / this_caf_trigger->cmp_contrast) ||
		diff.contrast >= (cur_data->contrast / this_caf_trigger->cmp_contrast))
		&& (diff.contrast >= this_caf_trigger->min_trigger_contrast_diff))
		ret_val |= 0x01;
	/*
	if ((diff.lum >= (pre_data->lum / FOCUS_PARAM_COMPARE_RATIO_LUM))
		&& (diff.lum >= FOCUS_PARAM_MIN_TRIGGER_LUM_DIFF))
		ret_val |= 0x02;
	*/
	if (diff.ae >= (pre_data->ae / this_caf_trigger->cmp_ae))
		ret_val |= 0x04;
	if (diff.rbratio >= (pre_data->rbratio / this_caf_trigger->cmp_awb))
		ret_val |= 0x08;

	if (diff.xyz.x >= this_caf_trigger->cmp_diff_xyz)
		ret_val |= 0x10;
	if (diff.xyz.y >= this_caf_trigger->cmp_diff_xyz)
		ret_val |= 0x20;
	if (diff.xyz.z >= this_caf_trigger->cmp_diff_xyz)
		ret_val |= 0x40;

	return ret_val;
}

static caf_detect_result ispv1_check_caf_need_trigger(mini_focus_frame_stat_s *compare_data, mini_focus_frame_stat_s *mean_data, mini_focus_frame_stat_s cur_data)
{
	u8 unpeace = 0;
	static u16 unpeace_ms;
	u16 force_start = get_caf_forcestart();
	u16 diff_val = 0;
	u8 fps = mini_this_ispdata->sensor->fps;
	bool trigger = false;
	mini_effect_params *effect = get_effect_ptr();
	mini_caf_trigger_s *this_caf_trigger = &effect->af_param.focus_algo.caf_trigger;

	if (force_start == 0) {
		/* if diff too much, should force focus start. */
		diff_val = ispv1_calc_frame_stat_diff(compare_data, mean_data);
		force_start = diff_val;
		set_caf_forcestart(force_start);
	} else if ((force_start & CAF_FORCESTART_FORCE) != 0) {
		unpeace_ms = 0;
		return CAF_DETECT_RESULT_TRIGGER;
	}

	if (force_start == 0)
		return CAF_DETECT_RESULT_NONE;

	if (mean_data->contrast_var > (mean_data->contrast * mean_data->contrast / this_caf_trigger->var_ratio_contrast))
		unpeace |= 0x01;
	if (mean_data->lum_var > (mean_data->lum * mean_data->lum / this_caf_trigger->var_ratio_lum))
		unpeace |= 0x02;
	if (mean_data->xyz_var.x > this_caf_trigger->var_diff_xyz)
		unpeace |= 0x10;
	if (mean_data->xyz_var.y > this_caf_trigger->var_diff_xyz)
		unpeace |= 0x20;
	if (mean_data->xyz_var.z > this_caf_trigger->var_diff_xyz)
		unpeace |= 0x40;

	print_debug("mean contrast var [0x%x:0x%x], lum var [0x%x:0x%x], xyz var [%d, %d, %d]",
		mean_data->contrast_var, mean_data->contrast,
		mean_data->lum_var, mean_data->lum,
		mean_data->xyz_var.x, mean_data->xyz_var.y, mean_data->xyz_var.z);

	if (force_start && unpeace == 0) {
		if (mean_data->lum >= this_caf_trigger->min_trigger_lum) {
			if ((mini_afae_ctrl->focus_stat_frames > this_caf_trigger->stat_skip_frame)
                  && ((force_start & 0xff00) == 0)) {
				
				diff_val = ispv1_calc_frame_stat_diff(compare_data, &cur_data);
				if (diff_val != 0)
					trigger = true;
			}else {
				/* CAF_FORCESTART_FORCE or CAF_FORCESTART_FORCEWAIT */
				trigger = true;
			}
			unpeace_ms = 0;
			if (trigger == true) {
				print_info("CAF scene changed reason: 0x%.4x; contrast [0x%x->0x%x], diff_val 0x%x!",
					force_start, compare_data->contrast, mean_data->contrast, diff_val);
				return CAF_DETECT_RESULT_TRIGGER;
			} else {
				set_caf_forcestart(CAF_FORCESTART_CLEAR);
				return CAF_DETECT_RESULT_NOISE;
			}
		} else {
			return CAF_DETECT_RESULT_NONE;
		}
	} else {
		print_debug("force_start 0x%x, but unpeace 0x%x, gsensor unpeace_ms %d", force_start, unpeace, unpeace_ms);

		/* if unpeace caused by Gsensor more than XX seconds, force VCM go to infinite. */
		if ((unpeace & 0xf0) != 0) {
			if (unpeace_ms < this_caf_trigger->goto_infinite_timeout) {
				unpeace_ms += 1000 / fps;
				return CAF_DETECT_RESULT_NONE;
			} else {
				/* if gsensor is unpeace than (XX * fps), force VCM go to infinite */
				unpeace_ms = 0;
				return CAF_DETECT_RESULT_INFINITE;
			}
		} else {
			/* if gsensor is stable, Gsensor unpeace count set zero and return RESULT_NONE. */
			unpeace_ms = 0;
			return CAF_DETECT_RESULT_NONE;
		}
	}
}

/*
 **************************************************************************
 * FunctionName: ispv1_focus_get_curr_data
 * Description : using for save current envionment variables
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_focus_get_curr_data(mini_focus_frame_stat_s *curr_data)
{
	mini_awb_gain_t awb_gain;
	u32 gain, expo;

	GETREG16(REG_ISP_FOCUS_CONTRAST(0), curr_data->contrast);
	gain = get_writeback_gain();
	expo = get_writeback_expo();

	curr_data->lum = ispv1_focus_get_win_lum(&mini_afae_ctrl->lum_info);
	curr_data->ae = gain * expo;
	curr_data->fps = mini_this_ispdata->sensor->fps;

	mini_ispv1_get_wb_value(&awb_gain);
	if ((awb_gain.b_gain != 0) && (awb_gain.r_gain != 0)) {
		curr_data->rbratio = 0x8000 / (awb_gain.b_gain * 0x100 / awb_gain.r_gain);
	} else {
		curr_data->rbratio = 0x100;
	}
	memcpy(&curr_data->xyz, &mini_mXYZ, sizeof(mini_axis_triple));

	print_debug("current contrast 0x%.3x, lum 0x%.2x, xyz: %.4d, %.4d, %.4d",
		curr_data->contrast, curr_data->lum,
		curr_data->xyz.x, curr_data->xyz.y, curr_data->xyz.z);
}

static void ispv1_get_default_focusrect(mini_camera_rect_s *rect)
{
	u32 preview_width = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_width;
	u32 preview_height = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_height;

	ispv1_focus_get_default_yuvrect(rect, preview_width, preview_height);
}

u32 mini_ispv1_get_focus_rect(mini_camera_rect_s *rect)
{
	u32 preview_width = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_width;
	u32 preview_height = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_height;

	memcpy(rect, &mini_afae_ctrl->af_area.rect[0], sizeof(mini_camera_rect_s));
	if (rect->width == 0 || rect->height == 0)
		ispv1_get_default_focusrect(rect);

	ispv1_focus_adjust_yuvrect(rect, preview_width, preview_height, mini_afae_ctrl->zoom);
	return 0;
}

static bool ispv1_copy_preview_data(u8 *dest, mini_camera_rect_s *rect)
{
    mini_camera_frame_buf *currframe = mini_this_ispdata->current_frame;
    mini_camera_frame_buf frame;
    mini_camera_rect_s rect_org;
	u32 preview_width = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_width;
	u32 preview_height = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_height;
	u32 index;
	u8 *src;
	bool ret = false;

	if (down_trylock(&(mini_this_ispdata->frame_sem)) != 0) {
		print_warn("enter %s, frame_sem already locked", __func__);
		goto error_out2;
	}

	if (NULL == dest || NULL == currframe) {
		print_error("params error, dest 0x%x, frame 0x%x", (unsigned int)dest, (unsigned int)currframe);
		goto error_out1;
	}

	if ((0 == currframe->phyaddr) || (NULL != currframe->viraddr)) {
		print_error("params error, frame->phyaddr 0x%x, frame->viraddr:0x%x",
			(unsigned int)currframe->phyaddr, (unsigned int)currframe->viraddr);
		goto error_out1;
	}
	memcpy(&frame,currframe,sizeof(mini_camera_frame_buf));
	memcpy(&rect_org,rect,sizeof(mini_camera_rect_s));

	frame.viraddr = ioremap_nocache(frame.phyaddr, preview_width * preview_height);
	if (NULL == frame.viraddr) {
		print_error("%s line %d error", __func__, __LINE__);
		goto error_out1;
	}

	for(index = 0; index < rect_org.height; index++) {
		src = (u8 *)frame.viraddr+ preview_width * (rect_org.top + index) + rect_org.left;
		memcpy(dest, src, rect_org.width);
		dest += rect_org.width;
	}
	iounmap(frame.viraddr);
	frame.viraddr = NULL;
	ret = true;
error_out1:
	up(&(mini_this_ispdata->frame_sem));

error_out2:
	return ret;
}

#if 0
static int ispv1_focus_calc_variance(u8 *pdata, u32 size)
{
	int index;
	u32 average_y = 0;
	u32 variance_y = 0;

	print_debug("enter %s", __func__);

	/* calculate average */
	if (pdata == NULL) {
		print_error("pdata NULL in %s function at line %d\n", __func__, __LINE__);
		return -ENOMEM;
	}

	for (index = 0; index < size; index++)
		average_y += pdata[index];
	average_y /= size;

	for (index = 0; index < size; index++) {
		variance_y += (pdata[index] - average_y) * (pdata[index] - average_y);
	}

	/* variance of mean */
	variance_y /= size;
	return variance_y;
}
#endif

#define FOCUS_VAR_LOW_LIMIT		0x100
#define FOCUS_VAR_HIGH_LIMIT		0x400

#define FOCUS_VAR_LOW_COEFF		0x18
#define FOCUS_VAR_HIGH_COEFF		0x10

#define MAX_COUNT_FOR_SMOOTH_AREA	6

#if 0
static void ispv1_focus_update_threshold_ext(u8 *pdata, u32 size)
{
	u32 curr_y;
	u32 curr_gain;
	u32 threshold_ext;
	u32 variance_y = 0;
	u32 coeff = 0;

	variance_y = ispv1_focus_calc_variance(pdata, size);
	if (variance_y <= FOCUS_VAR_LOW_LIMIT) {
		coeff = FOCUS_VAR_LOW_COEFF;
	} else if ((variance_y > FOCUS_VAR_LOW_LIMIT) && (variance_y <= FOCUS_VAR_HIGH_LIMIT)) {
		coeff =  (FOCUS_VAR_HIGH_LIMIT - variance_y);
		coeff *=  (FOCUS_VAR_LOW_COEFF - FOCUS_VAR_HIGH_COEFF);
		coeff /= (FOCUS_VAR_HIGH_LIMIT - FOCUS_VAR_LOW_LIMIT);
		coeff += FOCUS_VAR_HIGH_COEFF;
	} else {
		coeff = FOCUS_VAR_HIGH_COEFF;
	}

	curr_y = get_current_y();
	curr_gain = get_writeback_gain();
	//curr_gain = (curr_gain > 0x70) ? 0x70 : (curr_gain & 0xf8);
	curr_gain = (curr_gain > 0x40) ? 0x40 : (curr_gain & 0xf8);

	threshold_ext = (0xd0 - curr_gain) / 0xc;
	if (curr_y < 0x10) {
		threshold_ext = 0;
	} else if ((curr_y >= 0x10) && (curr_y < 0x20)) {
		threshold_ext = (curr_y - 0x10) * threshold_ext / 0x10;
	}

	threshold_ext = threshold_ext * coeff / FOCUS_VAR_HIGH_COEFF;

	SETREG16(REG_ISP_FOCUS_AFCCTRL2, threshold_ext);
	print_info("y:0x%.2x, y_var 0x%x, gain: 0x%.2x, threshold_ext: 0x%.2x, coeff 0x%x",
		curr_y, variance_y, curr_gain, threshold_ext, coeff);
}
#endif
/*
 **************************************************************************
 * FunctionName: ispv1_focus_calc_edge;
 * Description : using for calculate contrast;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : in 1080P preview case, coarse_flag must set to true;
 **************************************************************************
 */
static u32 ispv1_focus_calc_edge(u8 *pdata, mini_camera_rect_s *rect, int contrast_shift, bool coarse_flag)
{
	u32 i, j;
	u32 sum = 0;
	u32 total = 1;
	u32 value1, value2;
	u32 thr = 1;
	u32 result = 0;
	u8 *sdata;
	u32 step;
	u32 width = rect->width;
	u32 height = rect->height;

	struct timeval tv1, tv2;
	int t1;
	int width_shift = width << 1;
	int step_width;

	sdata = pdata;
	do_gettimeofday(&tv1);

	thr >>= contrast_shift;
	step = (coarse_flag == true) ? 3 : 1;

       step_width = step * width;

	for (i = 0; i < (height - 2); i += step) {
		for (j = 0; j < (width - 2); j += step) {
			value1 = abs(sdata[j + 2] + (sdata[width + j + 2]<<1) + sdata[width_shift + j + 2]
					-sdata[j] - (sdata[width + j]<<1) - sdata[width_shift + j]);
			value2 = abs(sdata[width_shift + j] + (sdata[width_shift + j + 1]<<1) + sdata[width_shift + j + 2]
					-sdata[j] - (sdata[j + 1]<<1) - sdata[j + 2]);

				if (value1 < thr)
					value1 = 0;
				if (value2 < thr)
					value2 = 0;

				if (coarse_flag)
					sum += value1 * value1 + value2 * value2;
				else
					sum += value1 + value2;

			total++;
		}
		sdata += step_width;
	}
	result = (sum << 4) / total;

	do_gettimeofday(&tv2);

	t1 = (tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec) / 1000;

	print_debug("%s: w %3d, h %3d, coarse_flag %d, used %dms", __func__, width, height, coarse_flag, t1);

	return result;
}

static int ispv1_focus_need_schedule(void)
{
	int schedule_case = -1;

	if (mini_afae_ctrl->k3focus_running == false)
		return schedule_case;

	if (get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_PICTURE &&
	    mini_get_focus_state() == FOCUS_STATE_CAF_DETECTING) {
		schedule_case = FOCUS_SCHEDULE_CASE_CAF_PICTURE_DETECT;
	} else if (get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_PICTURE &&
	    mini_get_focus_state() == FOCUS_STATE_CAF_RUNNING) {
		schedule_case = FOCUS_SCHEDULE_CASE_CAF_PICTURE_MOVE;
	} else if (get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_VIDEO &&
	    mini_get_focus_state() == FOCUS_STATE_CAF_DETECTING) {
		schedule_case = FOCUS_SCHEDULE_CASE_CAF_VIDEO_DETECT;
	} else if (get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_VIDEO &&
	    mini_get_focus_state() == FOCUS_STATE_CAF_RUNNING) {
		schedule_case = FOCUS_SCHEDULE_CASE_CAF_VIDEO_MOVE;
	} else if (mini_get_focus_state() == FOCUS_STATE_AF_RUNNING) {
		schedule_case = FOCUS_SCHEDULE_CASE_AF_MOVE;
	} else if (get_focus_mode() == CAMERA_FOCUS_AUTO_VIDEO &&
	    mini_get_focus_state() == FOCUS_STATE_AF_RUNNING) {
		schedule_case = FOCUS_SCHEDULE_CASE_VAF_MOVE;
	}

	return schedule_case;
}

void mini_ispv1_wakeup_focus_schedule(bool force_flag)
{
	if(!mini_this_ispdata->sensor->af_enable) {
		return;
	}

	if (force_flag == true) {
		up(&sem_af_schedule);
		return;
	}

	if ((ispv1_focus_need_schedule() != -1) && (mini_afae_ctrl->k3focus_running == true))
		up(&sem_af_schedule);
}

static int ispv1_wait_focus_schedule_timeout(int time_out)
{
	long jiffies = 0;

	jiffies = msecs_to_jiffies(time_out);
	if (down_timeout(&sem_af_schedule, jiffies)) {
		print_error("wait focus schedule timeout\n");
		return -ETIME;
	} else {
		print_debug("focus schedule waking up###########");
		return 0;
	}
}

/* for Picture CAF, adjust current code to a smaller code if it is not aligned. */
static int af_adjust_curr_vcmcode(mini_vcm_info_s *vcm, int curr)
{
	int strideSeparator;
	int ret_code;
	u32 strideRatio;

	strideSeparator = vcm->offsetInit + vcm->strideOffset;

	if ((get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_VIDEO)
		|| (get_focus_mode() == CAMERA_FOCUS_AUTO_VIDEO)) {
		strideRatio = vcm->videoStrideRatio;
	} else {
		strideRatio = vcm->normalStrideRatio;
	}

	if (curr >= strideSeparator) {
		ret_code = curr - (curr - strideSeparator) % get_af_large_step(vcm->coarseStep, strideRatio);
	} else {
		ret_code = curr - (curr - vcm->offsetInit) % vcm->coarseStep;
	}

	return ret_code;
}

/*
 **************************************************************************
 * FunctionName: af_get_next_vcmcode
 * Description : calculate next position;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : overflow_flag true:within, false: overflow;
 * Other       :
 **************************************************************************
 */
static bool af_get_next_vcmcode(mini_af_trip_info *trip, int curr_code, int direction, af_code_step step_type, int *next)
{
	mini_vcm_info_s *vcm = get_vcm_ptr();

	int stride = vcm->coarseStep;
	int large_stride;
	int next_code = 0;
	int strideSeparator;

	int left, right; /* left is small code, right is large code */

	left = (trip->end_pos > trip->start_pos) ? trip->start_pos: trip->end_pos;
	right = (trip->end_pos > trip->start_pos) ? trip->end_pos: trip->start_pos;

	/* check current code, already overflow */
	if (curr_code <= left && direction == AF_RUN_DIRECTION_BACKWARD)
		return false;
	if (curr_code >= right && direction == AF_RUN_DIRECTION_FORWARD)
		return false;

	/* maybe large stride in macro distance. */
	if (step_type == AF_CODE_STEP_VIDEO)
		large_stride = get_af_large_step(vcm->coarseStep, vcm->videoStrideRatio);
	else
		large_stride = get_af_large_step(vcm->coarseStep, vcm->normalStrideRatio);

	if ((step_type == AF_CODE_STEP_COARSE) || (step_type == AF_CODE_STEP_VIDEO)) {
		strideSeparator = vcm->offsetInit + vcm->strideOffset;
		strideSeparator += ((vcm->fullRange - strideSeparator) % large_stride);
		if ((curr_code == strideSeparator && direction == AF_RUN_DIRECTION_FORWARD) || (curr_code > strideSeparator))
			stride = large_stride;
		else
			stride = vcm->coarseStep;
	} else if (step_type == AF_CODE_STEP_FINE) {
		stride = vcm->fineStep;
	}

	next_code = curr_code + direction * stride;

	/* check next code again */
	if (next_code > right || next_code < left) {
		return false;
	} else {
		*next = next_code;
		return true;
	}
}

/*
 **************************************************************************
 * FunctionName: check_vcmcode_is_edge
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : overflow_flag true:overflow, false: within;
 * Other       :
 **************************************************************************
 */
static inline bool check_vcmcode_is_edge(mini_af_trip_info *trip, int code)
{
	int left, right; /* left is small code, right is large code */

	left = (trip->end_pos > trip->start_pos) ? trip->start_pos: trip->end_pos;
	right = (trip->end_pos > trip->start_pos) ? trip->end_pos: trip->start_pos;

	/* check current code. */
	if (code <= left && trip->direction == AF_RUN_DIRECTION_BACKWARD)
		return true;
	if (code >= right && trip->direction == AF_RUN_DIRECTION_FORWARD)
		return true;

	return false;
}

/* for CAF try stage to coarse, current trip should reverse. */
static void af_reverse_curr_trip(mini_vcm_info_s *vcm, mini_af_trip_info *trip, u32 start_code)
{
	/* end_pos goto another side */
	trip->start_pos = start_code;
	trip->direction = 0 - trip->direction;

	if (trip->direction == AF_RUN_DIRECTION_BACKWARD)
		trip->end_pos = vcm->offsetInit;
	else
		trip->end_pos = vcm->fullRange;
}

static inline focus_position_e check_postion_partition(int curr, int focus_range)
{
	mini_effect_params *effect = get_effect_ptr();
	mini_focus_algo_s *this_focus_algo = &effect->af_param.focus_algo;
	if (curr <= (focus_range / this_focus_algo->try_dir_range))
		return FOCUS_POSITION_PART_LEFT;
	else if (curr > (focus_range / this_focus_algo->try_dir_range) && curr <= focus_range / 2)
		return FOCUS_POSITION_PART_CENTER_LEFT;
	else if (curr > (focus_range / 2) &&
		curr < (focus_range * (this_focus_algo->try_dir_range - 1)  / this_focus_algo->try_dir_range))
		return FOCUS_POSITION_PART_CENTER_RIGHT;
	else
		return FOCUS_POSITION_PART_RIGHT;
}

/*
 **************************************************************************
 * FunctionName: analysis_contrast_value;
 * Description : analysis contrast value of coarse step phase,
 			and judge focus result in this time
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static bool analysis_contrast_value(u32 *array, mini_af_run_param *af_info)
{
	mini_af_trip_info *trip = &(af_info->trip);
	u32 array_size = trip->step_cnt;
	u32 index = 0;
	u8  top_cnt = 0;
	u32 contrast_top = 0;
	u8 top_index = 0;
	bool ret = true;
	u8 start_index = 0;
	u32 contrast_threshold = 0;
	u32 focus_lum;
	mini_effect_params *effect = get_effect_ptr();
	mini_judge_result *this_judge_result = &effect->af_param.focus_algo.param_judge;

	/* search top contrast and count that */
	af_info->af_analysis = 0;

	/* search top contrast's index and count that */
	for (index = 0; index < array_size; index++) {
		if (contrast_top < array[index]) {
			contrast_top = array[index];
			top_index = index;
			af_info->af_analysis = 0;
		} else if (contrast_top == array[index]) {
			if ((index - top_index) > 2 ) {
				af_info->af_analysis |= 0x02;
			}
		}
	}

	if ((abs(contrast_top - array[0]) < this_judge_result->error_mindiff) &&
		(array_size > this_judge_result->error_minsteps) &&
		contrast_top < this_judge_result->low_contrast) {
		af_info->af_analysis |= 0x04;
	}

	focus_lum = ispv1_focus_get_win_lum(&mini_afae_ctrl->lum_info);
	if (focus_lum <= this_judge_result->error_lum) {
		af_info->af_analysis |= 0x04;
	}

	contrast_threshold = contrast_top * this_judge_result->stat_th_percent / 100;
	/* analysis slope of curve */
	if (array_size > 10) {
		if (top_index < 3) {
			start_index = 0;
		} else if (top_index > array_size - 4) {
			start_index = array_size - 7;
		} else {
			start_index = top_index - 3;
		}

		for (index = start_index; index < start_index + 7; index++) {
			if (contrast_threshold < array[index]) {
				top_cnt++;
			}
		}
		if (top_cnt > MAX_COUNT_FOR_SMOOTH_AREA) {
			af_info->af_analysis |= 0x01;
		}
	}
#if 0
	else {
		for (index = 0; index < array_size; index++) {
			if (contrast_threshold < array[index]) {
				top_cnt++;
			}
		}

		if (top_cnt > array_size - 2) {
			af_info->af_analysis |= 0x01;
		}
	}
#endif

	if (af_info->af_analysis != 0) {
		ret = false;
	}
	print_debug("%s, af_info->af_analysis:0x%x, top_count:%d, contrast_top:0x%x, array_size:%d, start_index:%d",
		__func__, af_info->af_analysis, top_cnt, contrast_top, array_size, start_index);
	return ret;
}

/*
 **************************************************************************
 * FunctionName: ispv1_judge_skip_frame;
 * Description : calculate idle time of sensor, if idle time less than 10ms
 			and current frame rate large than 15fps, than need skip frame;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static bool ispv1_judge_skip_frame(void)
{
	bool ret = false;

	mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	mini_vcm_info_s *vcm = get_vcm_ptr();
	u32 frame_index = sensor->preview_frmsize_index;
	u32 basic_vts = sensor->frmsize_list[frame_index].vts;
	u32 fullfps = sensor->frmsize_list[frame_index].fps;
	u32 height = sensor->frmsize_list[frame_index].height;
	u32 fps = sensor->fps;
	u32 vts = basic_vts * fullfps / fps;
	int expo_time_ms;
	int stable_expo_ms;

	expo_time_ms = (get_writeback_expo() >> 4) * 1000 / (basic_vts * fullfps);
	stable_expo_ms = (vts - height) * 1000 / (vts * fps) - vcm->motorResTime;

	if ((sensor->fps > 15) && (stable_expo_ms <= (expo_time_ms / 2))) {
		ret = true;
	} else {
		ret = false;
	}
	print_debug("expo_line:%d, vts:%d, expo time:%d, stable_expo_ms:%d ret:%d, fps:%d",
		get_writeback_expo()>>4, vts, expo_time_ms, stable_expo_ms, ret, sensor->fps);
	return ret;
}

/*
 **************************************************************************
 * FunctionName: mini_ispv1_get_aec_state;
 * Description : get current aec is stable or not
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : true is aec stable false is unstable;
 * Other       : NA;
 **************************************************************************
 */
bool mini_ispv1_get_aec_state(void)
 {
 	bool ret = false;
 	u16 gain;

	mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	gain = get_writeback_gain();

 	if ( 1 == GETREG8(REG_ISP_AECAGC_STABLE)){
 		ret = true;
 	}else{
 		if (gain >= sensor->max_gain){
 			ret = true;
 			print_info("++++++++++++arrival the max gain so aec is stable");
 		}
 	}
 	 return ret;

 }
static void ispv1_k3focus_run(void)
{
	mini_vcm_info_s *vcm = get_vcm_ptr();
	u32 preview_width = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_width;
	u32 preview_height = mini_this_ispdata->pic_attr[STATE_PREVIEW].out_height;
	int schedule_case = -1;
	FOCUS_STATUS result = STATUS_FOCUSING;
	int ret;

	/* hold and detect case use these. */
	caf_detect_result check_result = CAF_DETECT_RESULT_NONE;
	mini_focus_frame_stat_s curr_data;
	mini_focus_frame_stat_s mean_data;

	mini_focus_frame_stat_s start_data;
	bool restart = false;

	mini_camera_rect_s rect_used = mini_afae_ctrl->cur_rect;
	mini_camera_rect_s rect_large = rect_used;
	mini_camera_rect_s *rect = &rect_used;

	mini_pos_info large_contrast_array[30];
	u32 large_curr = 0;
	mini_pos_info large_top;
	bool large_ret = false;
	int contrast_count = 0;
	u32 top_contrast = 0;
	bool enlarge_flag = false;
	int frames = 0;
	u8 *pstat_data = mini_afae_ctrl->stat_data;

	mini_af_run_param af_info;
	mini_af_trip_info *trip = &(af_info.trip);
	mini_pos_info *top = &(af_info.top);
	mini_pos_info *histtop = &(af_info.histtop);
	mini_pos_info curr;

	int next_code = 0;
	int tryrewind_code = 0;

	af_run_stage next_stage = AF_RUN_STAGE_PREPARE;


	/* used for ispv1_focus_calc_edge(), set coarse flag or not */
	bool edge_calc_coarse = true;

	/* picture AF case use these */
	u32 focus_range = 0;
	u32 pos_offset = 0;

	bool vcm_stable = false;
	focus_position_e pos_part;

	u32 contrast_array[30];

	/*video/picture CAF move case use this. */
	u32 frame_count = 0;
	bool skip_frame = false;
	bool copy_ret = true;
	mini_effect_params *effect = get_effect_ptr();
	mini_focus_algo_s *this_focus_algo = &effect->af_param.focus_algo;

	/*init picture AF params */
	memset(&af_info, 0, sizeof(mini_af_run_param));

	memset(&curr_data, 0, sizeof(mini_focus_frame_stat_s));
	memset(&mean_data, 0, sizeof(mini_focus_frame_stat_s));

	/* first set edge_calc_coarse flag first */
	if ((preview_width * preview_height) > this_focus_algo->calc_coarse_size)
		edge_calc_coarse = true;
	else
		edge_calc_coarse = false;

	/*video CAF params init */
	curr.code = get_focus_code();
	curr.contrast = 0;

	top->code = curr.code;
	top->contrast = 0;
	histtop->code = curr.code;
	histtop->contrast = 0;

	schedule_case = ispv1_focus_need_schedule();
	print_info("enter %s, case %d ###########, current code 0x%x", __func__, schedule_case, curr.code);

	/*set k3focus_running flag is true */
	mini_afae_ctrl->k3focus_running = true;

	ispv1_free_af_run_sem();

	ispv1_af_flash_check_open();

	/* init params */
	sema_init(&sem_af_schedule, 0);

	enlarge_focus_window(&rect_large, preview_width, preview_height, mini_afae_ctrl->zoom);

	while ((schedule_case = ispv1_focus_need_schedule()) != -1) {
		ret = ispv1_wait_focus_schedule_timeout(120);
		if (ret != 0)
			continue;

		/* recheck again. */
		schedule_case = ispv1_focus_need_schedule();
		print_debug("af schedule waked up case %d ###########", schedule_case);

		switch (schedule_case) {
		case FOCUS_SCHEDULE_CASE_CAF_PICTURE_DETECT:
		case FOCUS_SCHEDULE_CASE_CAF_VIDEO_DETECT:
			result = mini_get_focus_result();
			if ((result == STATUS_FOCUSED) || (result == STATUS_OUT_FOCUS)) {
				if ((get_caf_forcestart() & CAF_FORCESTART_FORCE) == 0) {
					ispv1_focus_get_curr_data(&curr_data);
					ret = ispv1_focus_status_collect(&curr_data, &mean_data);
					if (ret != 0)
						break;
				}

				/* if diff too much and quiet, should force focus start. */
				check_result = ispv1_check_caf_need_trigger(&mini_afae_ctrl->compare_data, &mean_data, curr_data);
				if (check_result == CAF_DETECT_RESULT_TRIGGER
					&& mini_get_focus_state() == FOCUS_STATE_CAF_DETECTING) {
					mini_set_focus_state(FOCUS_STATE_CAF_RUNNING);
					ispv1_focus_status_reset();
					frame_count = 0;
					if (schedule_case == FOCUS_SCHEDULE_CASE_CAF_PICTURE_DETECT) {
						set_focus_stage(AF_RUN_STAGE_PREPARE);
						enlarge_flag = false;
						contrast_count = 0;
						rect_used = mini_afae_ctrl->cur_rect;
						rect_large = rect_used;
						enlarge_focus_window(&rect_large, preview_width, preview_height, mini_afae_ctrl->zoom);
					}
					else
						set_focus_stage(VCAF_RUN_STAGE_PREPARE);
				} else if (check_result == CAF_DETECT_RESULT_INFINITE) {
					if (curr.code != vcm->offsetInit) {
						curr.code = vcm->offsetInit;
						ispv1_setreg_vcm_code(curr.code);
						ispv1_focus_status_reset();

						/* should wait peace and force CAF */
						set_caf_forcestart(CAF_FORCESTART_FORCEWAIT);
						print_info("unpeace timeout, force go to infinite. !!!!!!!!!!!!!!!!!!!!!");
					}
				} else if (check_result == CAF_DETECT_RESULT_NOISE) {
					print_debug("%s, detected temperarily sudden changes of scene", __func__);
					mini_afae_ctrl->focus_stat_frames = this_focus_algo->caf_trigger.stat_skip_frame;
				}
			}

			break;

		case FOCUS_SCHEDULE_CASE_CAF_PICTURE_MOVE:
		case FOCUS_SCHEDULE_CASE_AF_MOVE:
		case FOCUS_SCHEDULE_CASE_VAF_MOVE:
			if ((get_focus_stage() == AF_RUN_STAGE_TRY) ||(get_focus_stage() == AF_RUN_STAGE_COARSE) ||(get_focus_stage() == AF_RUN_STAGE_FINE)) {
				if (skip_frame == true) {
					if (trip->step_cnt == 0)
						frame_count += 2;
					else if (frame_count ++ % 2 == 0)
						break;
				}
			}

			copy_ret = ispv1_copy_preview_data(pstat_data, rect);
			if (false == copy_ret) {
				break;
			}
			curr.contrast = ispv1_focus_calc_edge(pstat_data, rect, 0, edge_calc_coarse);

			if (schedule_case == FOCUS_SCHEDULE_CASE_CAF_PICTURE_MOVE) {
				frames = CAF_LARGE_FOCUS_WIN_TH;
			} else {
				frames = AF_LARGE_FOCUS_WIN_TH;
			}
			if (contrast_count < frames) {
				contrast_count++;
				if (top_contrast < curr.contrast)
					top_contrast = curr.contrast;
			}
			if (contrast_count == frames && top_contrast < CONTRAST_TH_FOR_SMALL_WIN) {
				enlarge_flag = true;
				contrast_count++;
			}
			if (mini_afae_ctrl->zoom == 0 && enlarge_flag) {
				copy_ret = ispv1_copy_preview_data(pstat_data, &rect_large);
				if (false == copy_ret) {
					break;
				}

				large_curr = ispv1_focus_calc_edge(pstat_data, &rect_large, 0, true);
			}

			print_info("PAF move stage %d, dir %d, [0x%3x->0x%3x], curr[0x%.3x, 0x%.3x], top[0x%.3x, 0x%.3x]######",
				get_focus_stage(), trip->direction, trip->start_pos, trip->end_pos, curr.code, curr.contrast, top->code, top->contrast);

			switch (get_focus_stage()) {
				case AF_RUN_STAGE_PREPARE:

					#ifdef AF_TIME_PRINT
						do_gettimeofday(&tv_start);
					#endif

					/* CAF need wait AEC/AGC stable; touch AF need not wait, but need lock AEC/AGC */
					if (get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_PICTURE) {
						//aec_stable = GETREG8(REG_ISP_AECAGC_STABLE);
						if (false == mini_ispv1_get_aec_state()) {
							break;
						}

					} else
						mini_ispv1_set_aecagc_mode(MANUAL_AECAGC);

					/* before move vcm, must calculate compare rate by current expo time and frame rate */
					skip_frame = ispv1_judge_skip_frame();

					/* touch AF need pre-move */
					if ((get_focus_mode() != CAMERA_FOCUS_CONTINUOUS_PICTURE)
						&& (get_focus_mode() != CAMERA_FOCUS_AUTO_VIDEO)) {
						pos_offset = 0;
					} else {
						pos_offset = curr.code - vcm->offsetInit;
					}
					focus_range = vcm->fullRange - vcm->offsetInit;

					/* next_stage just save next primary stage, in fact 'af_stage' should goto PREPARE_POST first */
					pos_part = check_postion_partition(pos_offset, focus_range);
					if (pos_part == FOCUS_POSITION_PART_CENTER_LEFT ||
						pos_part == FOCUS_POSITION_PART_CENTER_RIGHT) {
						next_stage = AF_RUN_STAGE_TRY;
						next_code = curr.code;
					} else if (pos_part == FOCUS_POSITION_PART_LEFT) {
						next_stage = AF_RUN_STAGE_COARSE;
						next_code = vcm->offsetInit;
						trip->direction = AF_RUN_DIRECTION_FORWARD;
					} else if (pos_part == FOCUS_POSITION_PART_RIGHT) {
						next_stage = AF_RUN_STAGE_COARSE;
						next_code = vcm->fullRange;
						trip->direction = AF_RUN_DIRECTION_BACKWARD;
					}

					set_focus_result(STATUS_FOCUSING);

					/*
					 * calculate init focus postion, and go to init position
					 * maybe offsetInit, maybe a little shift from current position
					 */
					next_code = af_adjust_curr_vcmcode(vcm, next_code);
					if (next_code != curr.code) {
						ispv1_setreg_vcm_code(next_code);
						curr.code = next_code;
						af_info.hold_cnt = 0; /* should hold some frames to wait stable */
						set_focus_stage(AF_RUN_STAGE_PREPARE_POST);
					} else {
						/* if do not need adjust vcm code, then go to TRY or COARSE stage directly */
						goto do_prepare_post;
					}
					break;

				case AF_RUN_STAGE_PREPARE_POST:
					af_info.hold_cnt++;
					vcm_stable = ispv1_af_need_wait_stable(get_focus_stage(), af_info.hold_cnt);
					/* if vcm not stable, should wait next frame */
					if (vcm_stable == false) {
						break;
					}
do_prepare_post:
					af_info.hold_cnt = 0; /* set zero for next stages */

					/* prepare top information for next stage */
					top->code = curr.code;
					top->contrast = 0;
					histtop->code = curr.code;
					histtop->contrast = 0;

					ispv1_af_range_cal(&af_info, &curr, next_stage);
					set_focus_stage(next_stage);
					break;

				case AF_RUN_STAGE_TRY:
					/* ensure top->contrast value is same with start point. */
					if (top->code == curr.code)
						top->contrast = curr.contrast;

					next_stage = ispv1_af_recognise_curve(&af_info, &curr, vcm);
					if (next_stage == AF_RUN_STAGE_COARSE) {
						set_focus_stage(AF_RUN_STAGE_TRY_POST);
					} else if (next_stage == AF_RUN_STAGE_FINE) {
						set_focus_stage(AF_RUN_STAGE_TRY_POST);
					} else if (next_stage == AF_RUN_STAGE_END) {
						set_focus_stage(AF_RUN_STAGE_END);
						goto af_end_out;
					}
					break;

				case AF_RUN_STAGE_TRY_POST:
					af_info.hold_cnt++;
					vcm_stable = ispv1_af_need_wait_stable(get_focus_stage(), af_info.hold_cnt);
					/* if vcm not stable, should wait next frame */
					if (vcm_stable == false) {
						break;
					}
					af_info.hold_cnt = 0; /* set zero for next stages */

					ispv1_af_range_cal(&af_info, top, next_stage);

					histtop->code = top->code;
					histtop->contrast = 0;
					set_focus_stage(next_stage);
					break;

				case AF_RUN_STAGE_COARSE:
					/* ensure top->contrast value is same with start point. */
					if (top->code == curr.code)
						top->contrast = curr.contrast;

					/* save contrast value to array */
					contrast_array[trip->step_cnt] = curr.contrast;

					if (mini_afae_ctrl->zoom == 0 && enlarge_flag) {
						large_contrast_array[trip->step_cnt].contrast = large_curr;
						large_contrast_array[trip->step_cnt].code = curr.code;
					}

					next_stage = ispv1_af_search_top(&af_info, &curr, vcm, true, contrast_array, top_contrast);
					if (next_stage == AF_RUN_STAGE_FINE) {
						/* analysis contrast value */
						if (analysis_contrast_value(contrast_array, &af_info)) {
							set_focus_stage(AF_RUN_STAGE_COARSE_POST);
						} else if (mini_afae_ctrl->zoom == 0 && enlarge_flag) {
							large_ret = analysis_large_contrast_value(&large_contrast_array[0], &af_info, &large_top);
							if (large_ret) {
								next_stage = AF_RUN_STAGE_FINE;
								af_info.top.code = large_top.code;
								curr.code = large_top.code;
								set_focus_stage(AF_RUN_STAGE_COARSE_POST);
							} else {
								set_focus_stage(AF_RUN_STAGE_END);
							}
						} else {
							set_focus_stage(AF_RUN_STAGE_END);
						}

						ispv1_setreg_vcm_code(curr.code);
					} else if (next_stage == AF_RUN_STAGE_END) {
						if (!analysis_contrast_value(contrast_array, &af_info) && mini_afae_ctrl->zoom == 0 && enlarge_flag) {
							large_ret = analysis_large_contrast_value(&large_contrast_array[0], &af_info, &large_top);
							if (large_ret) {
								next_stage = AF_RUN_STAGE_FINE;
								af_info.top.code = large_top.code;
								curr.code = large_top.code;
								set_focus_stage(AF_RUN_STAGE_COARSE_POST);
							} else {
								set_focus_stage(AF_RUN_STAGE_END);
							}
						} else {
							set_focus_stage(AF_RUN_STAGE_END);
						}

						ispv1_setreg_vcm_code(curr.code);
					}
					break;

				case AF_RUN_STAGE_COARSE_POST:
					af_info.hold_cnt++;
					vcm_stable = ispv1_af_need_wait_stable(get_focus_stage(), af_info.hold_cnt);
					/* if vcm not stable, should wait next frame */
					if (vcm_stable == false) {
						break;
					}
					af_info.hold_cnt = 0; /* set zero for next stages */

					ispv1_af_range_cal(&af_info, &curr, next_stage);

					top->code = curr.code;
					top->contrast = 0;
					histtop->code = curr.code;
					histtop->contrast = 0;

					set_focus_stage(next_stage);
					break;

				case AF_RUN_STAGE_FINE:
					next_stage = ispv1_af_search_top(&af_info, &curr, vcm, false, contrast_array, top_contrast);
					if (next_stage != AF_RUN_STAGE_FINE) {
						set_focus_stage(AF_RUN_STAGE_END);
						ispv1_setreg_vcm_code(curr.code);
						goto af_end_out;
					}
					break;

af_end_out:
				case AF_RUN_STAGE_END:
					result = ispv1_af_judge_result(&af_info);
					set_focus_result(result);
					rect_used = mini_afae_ctrl->cur_rect;
					contrast_count = 0;
					enlarge_flag = false;
					top_contrast = 0;

					if (af_info.af_analysis & 0x04) {
						curr.code = vcm->offsetInit;
						ispv1_setreg_vcm_code(curr.code);
					}

					#ifdef AF_TIME_PRINT
						do_gettimeofday(&tv_end);
						print_info("*****focus TIME: %.4dms******, result %d",
							(int)((tv_end.tv_sec - tv_start.tv_sec)*1000 + (tv_end.tv_usec - tv_start.tv_usec) / 1000), result);
					#endif

					set_focus_stage(AF_RUN_STAGE_PREPARE);
					if ((get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_PICTURE)
						&& (mini_get_focus_state() == FOCUS_STATE_CAF_RUNNING))
						mini_set_focus_state(FOCUS_STATE_CAF_DETECTING);
					else {
						mini_ispv1_set_aecagc_mode(AUTO_AECAGC);
						goto run_out;
					}
					break;
				case AF_RUN_STAGE_BREAK:
					set_focus_result(STATUS_OUT_FOCUS);
					print_info("picture AF_RUN_STAGE_BREAK");
					set_focus_stage(AF_RUN_STAGE_PREPARE);
					if (get_focus_mode() == CAMERA_FOCUS_CONTINUOUS_PICTURE)
						mini_set_focus_state(FOCUS_STATE_CAF_DETECTING);
					else {
						mini_ispv1_set_aecagc_mode(AUTO_AECAGC);
						goto run_out;
					}
					break;

				default:
					print_info("FOCUS_SCHEDULE_CASE_AF_PICTURE_MOVE wrong case");
					break;
			}
			break;

		case FOCUS_SCHEDULE_CASE_CAF_VIDEO_MOVE:

			if ((get_focus_stage() == VCAF_RUN_STAGE_TRY) || (get_focus_stage() == VCAF_RUN_STAGE_FORWARD)) {
				/* even frame should skip */
				if (frame_count++ % 2 == 0)
					break;
			}

		#ifdef YUV_EDGE_STAT_MODE  //use new k3 contrast calculate mode
			copy_ret = ispv1_copy_preview_data(pstat_data, rect);
			if (false == copy_ret)
				break;

			curr.contrast = ispv1_focus_calc_edge(pstat_data, rect, 0, edge_calc_coarse);
		#else //use ISP contrast mode
			if (get_focus_stage() == VCAF_RUN_STAGE_STARTUP) {
				if (frame_count++ % 2 == 0)
					break;
			}
			GETREG16(REG_ISP_FOCUS_CONTRAST(0), curr.contrast);
		#endif

			print_debug("VCAF move stage %d, dir %d, [0x%3x->0x%3x], curr[0x%.3x, 0x%.3x], top[0x%.3x, 0x%.3x]######",
				get_focus_stage(), trip->direction, trip->start_pos, trip->end_pos, curr.code, curr.contrast, top->code, top->contrast);

			switch (get_focus_stage()) {
			case VCAF_RUN_STAGE_PREPARE:
				#ifdef AF_TIME_PRINT
					do_gettimeofday(&tv_start);
				#endif
				/* CAF need wait AEC/AGC stable */
				//aec_stable = GETREG8(REG_ISP_AECAGC_STABLE);
				if (false == mini_ispv1_get_aec_state()) {
					break;
				}
				/*
				 * calculate init focus postion, and go to init position
				 * maybe offsetInit, maybe a little shift from current position
				 */
				next_code = curr.code;
				next_code = af_adjust_curr_vcmcode(vcm, next_code);
				if (next_code != curr.code) {
					ispv1_setreg_vcm_code(next_code);
					curr.code = next_code;
					af_info.hold_cnt = 0; /* should hold some frames to wait stable */
				}

			#ifdef YUV_EDGE_STAT_MODE  //use new k3 contrast calculate mode
				print_debug("STAGE_PREPARE:goto stage %d(startup)###########", VCAF_RUN_STAGE_STARTUP);

				/*in this mode, we need not break, can goto CAF_RUN_STAGE_STARTUP directly. */
				set_focus_stage(VCAF_RUN_STAGE_STARTUP);
				/* set this frame is first frame, next frame need skip for stable */
				frame_count = 0;
			#else
				copy_ret = ispv1_copy_preview_data(pstat_data, rect);
				if (false == copy_ret)
					break;

				ispv1_focus_update_threshold_ext(pstat_data, rect->width * rect->height);
				set_focus_stage(VCAF_RUN_STAGE_STARTUP);

				/* set this frame is first frame, next frame need skip for stable */
				frame_count = 0;
				break;
			#endif

			case VCAF_RUN_STAGE_STARTUP:
				top->code = curr.code;
				top->contrast = curr.contrast;
				histtop->code = curr.code;
				histtop->contrast = curr.contrast;

				ispv1_vcaf_range_cal(&af_info, &curr, VCAF_RUN_STAGE_TRY, result);

				set_focus_result(STATUS_FOCUSING);
				ispv1_focus_get_curr_data(&start_data);

				af_get_next_vcmcode(trip, curr.code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
				ispv1_setreg_vcm_code(next_code); /* need not judge this code */
				curr.code = next_code;

				set_focus_stage(VCAF_RUN_STAGE_TRY);
				break;

			case VCAF_RUN_STAGE_TRY:
				contrast_array[trip->step_cnt++] = curr.contrast;
				next_stage = ispv1_vcaf_recognise_curve(&af_info, &curr, vcm, &tryrewind_code);
				set_focus_stage(next_stage);
				if (next_stage == VCAF_RUN_STAGE_REWIND) {
					if ((top->contrast < histtop->contrast) ||
					((top->contrast == histtop->contrast) && (top->code > histtop->code))) {
						top->contrast = histtop->contrast;
						top->code = histtop->code;
					}
					analysis_contrast_value(contrast_array, &af_info);
					result = ispv1_af_judge_result(&af_info);
					ispv1_vcaf_range_cal(&af_info, &curr, VCAF_RUN_STAGE_REWIND, result);
				}
				break;

			case VCAF_RUN_STAGE_TRYREWIND:
				if (curr.code != tryrewind_code) {
					af_get_next_vcmcode(trip, curr.code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
					ispv1_setreg_vcm_code(next_code);
					curr.code = next_code;
				} else {
					set_focus_stage(VCAF_RUN_STAGE_FORWARD);
				}
				break;

			case VCAF_RUN_STAGE_FORWARD:
				contrast_array[trip->step_cnt++] = curr.contrast;
				next_stage = ispv1_vcaf_search_top(&af_info, &curr, vcm);
				set_focus_stage(next_stage);
				if (next_stage == VCAF_RUN_STAGE_REWIND) {
					analysis_contrast_value(contrast_array, &af_info);
					result = ispv1_af_judge_result(&af_info);
					ispv1_vcaf_range_cal(&af_info, &curr, VCAF_RUN_STAGE_REWIND, result);
				}
				break;

			case VCAF_RUN_STAGE_REWIND:
				if (curr.code != top->code) {
					af_get_next_vcmcode(trip, curr.code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
					curr.code = next_code;
					ispv1_setreg_vcm_code(curr.code);
				} else {
					top->contrast = curr.contrast;
					set_focus_stage(VCAF_RUN_STAGE_PREPARE);
					if (mini_get_focus_state() == FOCUS_STATE_CAF_RUNNING)
						mini_set_focus_state(FOCUS_STATE_CAF_DETECTING);
					set_focus_result(STATUS_FOCUSED);
					ispv1_focus_get_curr_data(&curr_data);
					restart = ispv1_check_caf_need_restart(&start_data, &curr_data);
					if (restart == true)
						set_caf_forcestart(CAF_FORCESTART_FORCEWAIT);

					#ifdef AF_TIME_PRINT
						do_gettimeofday(&tv_end);
						print_info("*****focus TIME: %.4dms******",
							(int)((tv_end.tv_sec - tv_start.tv_sec)*1000 + (tv_end.tv_usec - tv_start.tv_usec) / 1000));
					#endif
				}
				break;
			case AF_RUN_STAGE_BREAK:
				set_focus_result(STATUS_FOCUSED);
				print_info("video AF_RUN_STAGE_BREAK");
				set_focus_stage(VCAF_RUN_STAGE_PREPARE);
				mini_set_focus_state(FOCUS_STATE_CAF_DETECTING);
				break;

			default:
				print_info("error:unknow vcaf_stage %d ###########", get_focus_stage());
				break;
			}
			break;

		default:
			print_info("error:unknow af schedule waked up case %d ###########", schedule_case);
			goto run_out;
		}
	}
run_out:
	mini_afae_ctrl->k3focus_running = false;
	print_info("exit %s, ###########", __func__);
	return;
}

/*
 **************************************************************************
 * FunctionName: ispv1_af_need_wait_stable
 * Description : VCM steering required to waiting for several frames at the specified location,
                       in order to prevent the inaccuracy of contrast caused by lens jitter.;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       :
 **************************************************************************
 */
static bool ispv1_af_need_wait_stable(u8 stage, u8 hold_cnt)
{
	u8 hold_frames = 0;
	mini_effect_params *effect = get_effect_ptr();
	mini_focus_algo_s *this_focus_algo = &effect->af_param.focus_algo;

	switch(stage) {
		case AF_RUN_STAGE_PREPARE_POST:
			hold_frames = this_focus_algo->infinity_hold_frames;
			break;
		case AF_RUN_STAGE_TRY_POST:
		case AF_RUN_STAGE_COARSE_POST:
			hold_frames = this_focus_algo->rewind_hold_frames;
			break;
		default:
			print_info("enter %s, wrong stage", __func__);
			break;
	}

	if (hold_cnt < hold_frames) {
		return false;
	} else {
		return true;
	}
}

/*
 **************************************************************************
 * FunctionName: ispv1_af_judge_result;
 * Description : decide if there exists contrast peak during the AF process at last;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       :
 **************************************************************************
 */
static FOCUS_STATUS ispv1_af_judge_result(mini_af_run_param *af_info)
{
	FOCUS_STATUS result;

	print_debug("enter %s, af_info->af_analysis:0x%x", __func__, af_info->af_analysis);
	if (af_info->af_analysis != 0) {
		result = STATUS_OUT_FOCUS;
		if (af_info->af_analysis & 0x01) {
			print_warn("slope of curve is small");
		}
		if (af_info->af_analysis & 0x02) {
			print_warn("exist several top contrast value");
		}
		if (af_info->af_analysis & 0x04) {
			print_warn("contrast diff is too low or env too dark.");
		}
	} else {
		result = STATUS_FOCUSED;
		print_debug("focus stop:val_vcm_top:0x%.3x, val_contrast:0x%.3x",\
			af_info->top.code, af_info->top.contrast);
	}
	return result;
}

static int get_af_judge_threshold_low(int contrast)
{
	int threshold;
	int judge_base;
	mini_effect_params *effect = get_effect_ptr();
	mini_contrast_threshold *this_contrast_th = &effect->af_param.focus_algo.param_th;

	if (contrast <= this_contrast_th->ultralow) {
		judge_base = this_contrast_th->base_low;
	} else if (contrast <= this_contrast_th->low) {
		judge_base = (contrast - this_contrast_th->ultralow)
			* (this_contrast_th->base_high- this_contrast_th->base_low)
			/ (this_contrast_th->low- this_contrast_th->ultralow)
			+ this_contrast_th->base_low;
	} else {
		judge_base = this_contrast_th->base_high;
	}

	threshold = (contrast)  * (judge_base - 1) / judge_base;
	return threshold;
}

static int get_af_judge_threshold_high(int contrast)
{
	int threshold;
	int judge_base;
	mini_effect_params *effect = get_effect_ptr();
	mini_contrast_threshold *this_contrast_th = &effect->af_param.focus_algo.param_th;

	if (contrast <= this_contrast_th->ultralow) {
		judge_base = this_contrast_th->base_low;
	} else if (contrast <= this_contrast_th->low) {
		judge_base = (contrast - this_contrast_th->ultralow)
			* (this_contrast_th->base_high - this_contrast_th->base_low)
			/ (this_contrast_th->low - this_contrast_th->ultralow)
			+ this_contrast_th->base_low;
	} else {
		judge_base = this_contrast_th->base_high;
	}

	threshold = (contrast)  * (judge_base + 1) / judge_base;
	return threshold;
}

/*
 **************************************************************************
 * FunctionName: ispv1_af_range_cal;
 * Description : initialize the parameters of running each range;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_af_range_cal(mini_af_run_param *af_info, mini_pos_info *curr, af_run_stage next_stage)
{
	mini_vcm_info_s *vcm = get_vcm_ptr();

	mini_af_trip_info *trip = &(af_info->trip);
	mini_pos_info *top = &(af_info->top);

	u32 focus_range = vcm->fullRange - vcm->offsetInit;
	u32 pos_offset = curr->code - vcm->offsetInit;

	switch (next_stage) {
	case AF_RUN_STAGE_TRY:
		trip->start_pos = curr->code;

		/* decide move direction in try stage, we want to move more steps */
		if (pos_offset < focus_range / 2) {
			trip->end_pos = vcm->fullRange;
			trip->direction = AF_RUN_DIRECTION_FORWARD;
		} else {
			trip->end_pos = vcm->offsetInit;
			trip->direction = AF_RUN_DIRECTION_BACKWARD;
		}
		trip->step = vcm->coarseStep;
		trip->step_cnt = 0;
		break;

	case AF_RUN_STAGE_COARSE:
		trip->start_pos = curr->code;
		if (trip->direction == AF_RUN_DIRECTION_FORWARD) {
			trip->end_pos = vcm->fullRange;
		} else {
			trip->end_pos = vcm->offsetInit;
		}

		trip->step = vcm->coarseStep;
		trip->step_cnt = 0;
		break;

	case AF_RUN_STAGE_FINE:
		if (trip->direction == AF_RUN_DIRECTION_BACKWARD) {
			trip->start_pos = top->code + vcm->fineStep;
			trip->end_pos = top->code - vcm->fineStep;
			if (trip->end_pos < vcm->offsetInit) {
				trip->end_pos = vcm->offsetInit;
			}
			if (trip->start_pos > vcm->fullRange) {
				trip->start_pos = vcm->fullRange;
			}
		} else {
			trip->start_pos = top->code - vcm->fineStep;
			trip->end_pos = top->code + vcm->fineStep;
			if (trip->start_pos < vcm->offsetInit) {
				trip->start_pos = vcm->offsetInit;
			}
			if (trip->end_pos > vcm->fullRange) {
				trip->end_pos = vcm->fullRange;
			}
		}

		trip->step = vcm->fineStep;
		trip->step_cnt = 0;
		break;

	default:
		print_error("wrong af run stage");
		break;
	}

	print_debug("next stage %d, start_pos:0x%.3x, end_pos:0x%.3x",next_stage, trip->start_pos, trip->end_pos);
}


static void ispv1_vcaf_range_cal(mini_af_run_param *af_info, mini_pos_info *curr, af_run_stage next_stage, FOCUS_STATUS result)
{
	mini_vcm_info_s *vcm = get_vcm_ptr();
	mini_af_trip_info *trip = &(af_info->trip);
	mini_pos_info *top = &(af_info->top);

	switch (next_stage) {
	case VCAF_RUN_STAGE_TRY:
		trip->start_pos = curr->code;

		/* decide move direction in try stage, we want to move more steps */
		if (curr->code >= vcm->fullRange) {
			trip->end_pos = vcm->offsetInit;
			trip->direction = AF_RUN_DIRECTION_BACKWARD;
		} else {
			trip->end_pos = vcm->fullRange;
			trip->direction = AF_RUN_DIRECTION_FORWARD;
		}
		trip->step = vcm->coarseStep;
		trip->step_cnt = 0;
		break;

	/* other case is changed by ispv1_vcaf_recognise_curve() or ispv1_vcaf_search_top() */
	case VCAF_RUN_STAGE_TRYREWIND:
		break;

	case VCAF_RUN_STAGE_FORWARD:
		break;

	case VCAF_RUN_STAGE_REWIND:
		/* if out focus,than go to offsetinit position */
		if (result == STATUS_OUT_FOCUS) {
			top->code = vcm->offsetInit;
			trip->start_pos = curr->code;
			trip->end_pos = vcm->offsetInit;
			trip->direction = AF_RUN_DIRECTION_BACKWARD;
		}
		break;

	default:
		print_error("wrong video caf run stage");
		break;
	}

	print_debug("next stage %d, start_pos:0x%.3x, end_pos:0x%.3x",next_stage, trip->start_pos, trip->end_pos);
}

/*
 **************************************************************************
 * FunctionName: ispv1_af_recognise_curve;
 * Description : Used in the CAF "try" stage, identifying the rising or decling
 *	         trend of the contrast value;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : ret: 0-continue; 1-go to coarse stage; 2-go to fine stage;
 * Other       : NA;
 **************************************************************************
 */
static af_run_stage ispv1_af_recognise_curve(mini_af_run_param *af_info, mini_pos_info *curr, mini_vcm_info_s *vcm)
{
	mini_af_trip_info *trip = &(af_info->trip);
	mini_pos_info *top = &(af_info->top);
	mini_pos_info *histtop = &(af_info->histtop);

	u32 next_code = 0;
	bool code_found = false;
	af_run_stage next_stage = AF_RUN_STAGE_TRY;

	if (curr->contrast <= get_af_judge_threshold_low(top->contrast) ||
		(curr->contrast <= top->contrast  && check_vcmcode_is_edge(trip, curr->code) == true)) {
		/*
		 * should do following steps:
		 * (1) get actual top code;
		 * (2) turn back right direction, top code as start_pos;
		 * (3) go back to top code.
		 * (4) next_stage set as AF_RUN_STAGE_COARSE stage.
		 */

		if ((top->contrast < histtop->contrast) ||
			(top->contrast == histtop->contrast && top->code > histtop->code)) {
			top->contrast = histtop->contrast;
			top->code = histtop->code;
		}

		print_debug("try top code 0x%x found!!!!!!!", top->code);

		af_reverse_curr_trip(vcm, trip, top->code);
		curr->code = top->code;
		next_stage = AF_RUN_STAGE_COARSE;
	} else if (curr->contrast <= get_af_judge_threshold_high(top->contrast) &&
		check_vcmcode_is_edge(trip, curr->code) == false) {
		/* retry because diff is too small */
		next_stage = AF_RUN_STAGE_TRY;

		if (curr->contrast >= top->contrast && curr->contrast >= histtop->contrast) {
			histtop->contrast = curr->contrast;
			histtop->code = curr->code;
		}

		/* need not judge this code */
		(void)af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_COARSE, &next_code);
		trip->step_cnt++;
		curr->code = next_code;
	} else {
		/* update top info, set as stage FORWARD and goto next position. */
		top->contrast = curr->contrast;
		top->code = curr->code;

		code_found = af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_COARSE, &next_code);
		trip->step_cnt++;
		if (code_found == true) {
			next_stage = AF_RUN_STAGE_COARSE;
			curr->code = next_code;
			print_debug("%s line %d: go to STAGE COARSE!", __func__, __LINE__);
		} else {
			print_error("%s line %d:next vcmcode will out of range!!!!!!!", __func__, __LINE__);
			/* Top code is this, goto REWIND stage */
			next_stage = AF_RUN_STAGE_END;
			return next_stage;
		}
	}

	ispv1_setreg_vcm_code(curr->code);

	return next_stage;
}

static af_run_stage ispv1_vcaf_recognise_curve(mini_af_run_param *af_info, mini_pos_info *curr, mini_vcm_info_s *vcm, u32 *reserved)
{
	mini_af_trip_info *trip = &(af_info->trip);
	mini_pos_info *top = &(af_info->top);
	mini_pos_info *histtop = &(af_info->histtop);

	u32 next_code = 0;
	bool code_found = false;
	af_run_stage next_stage = VCAF_RUN_STAGE_TRY;

	if (curr->contrast <= get_af_judge_threshold_low(top->contrast) ||
		(curr->contrast <= top->contrast  && check_vcmcode_is_edge(trip, curr->code) == true)) {
		/*
		 * should do following steps:
		 * (1) get actual top code;
		 * (2) turn back right direction, top code as start_pos;
		 * (3) go back to top side code.
		 * (4) next_stage set as TRYREWIND stage.
		 */

		if ((top->contrast < histtop->contrast) ||
			(top->contrast == histtop->contrast && top->code > histtop->code)) {
			top->contrast = histtop->contrast;
			top->code = histtop->code;
		}

		print_debug("try top code 0x%x found!!!!!!!", top->code);

		af_reverse_curr_trip(vcm, trip, curr->code);
		print_info("trip [0x%x -> 0x%x, dir %d]!!!!!!!", trip->start_pos, trip->end_pos, trip->direction);

		code_found = af_get_next_vcmcode(trip, top->code, trip->direction, AF_CODE_STEP_VIDEO, reserved);
		if (code_found == true) {
			af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
			curr->code = next_code;
			print_info("try rewind to 0x%x!!!!!!!", *reserved);
			next_stage = VCAF_RUN_STAGE_TRYREWIND;
		} else {
			print_error("%s line %d:next vcmcode will out of range!!!!!!!", __func__, __LINE__);
			/* Top code is just top, set vcm to top and goto REWIND stage */
			curr->code = top->code;
			next_stage = VCAF_RUN_STAGE_REWIND;
		}
	} else if (curr->contrast <= get_af_judge_threshold_high(top->contrast) &&
		check_vcmcode_is_edge(trip, curr->code) == false) {
		/* retry because diff is too small */
		next_stage = VCAF_RUN_STAGE_TRY;

		if (curr->contrast >= top->contrast) {
			/* if current code is same as histtop, lower code has high priority */
			if ((curr->contrast > histtop->contrast) ||
				((curr->contrast == histtop->contrast) && (curr->code < histtop->code))) {
				histtop->contrast = curr->contrast;
				histtop->code = curr->code;
			}
		}

		/* need not judge this code */
		af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
		curr->code = next_code;
	} else {
		/* update top info, set as stage FORWARD and goto next position. */
		top->contrast = curr->contrast;
		top->code = curr->code;

		code_found = af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
		if (code_found == true) {
			next_stage = VCAF_RUN_STAGE_FORWARD;
			curr->code = next_code;
		} else {
			print_error("%s line %d:next vcmcode will out of range!!!!!!!", __func__, __LINE__);
			/* Top code is this, no need to set direction, goto REWIND stage */
			next_stage = VCAF_RUN_STAGE_REWIND;
			return next_stage;
		}
	}

	ispv1_setreg_vcm_code(curr->code);

	return next_stage;
}

/*
 **************************************************************************
 * FunctionName: ispv1_af_search_top;
 * Description : using for recognise top;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : ret 0: continuous; 1:change to next phase; 2: go to judge phase;
 * Other       :
 **************************************************************************
 */
static af_run_stage ispv1_af_search_top(mini_af_run_param *af_info, mini_pos_info *curr, mini_vcm_info_s *vcm, bool coarse, u32* contrast_array, int first_contrast)
{
	mini_af_trip_info *trip = &(af_info->trip);
	mini_pos_info *top = &(af_info->top);
	mini_pos_info *histtop = &(af_info->histtop);

	u32 next_code = 0;
	bool code_found = false;
	af_run_stage next_stage;

	static int down_hill = 0;

	/* set default next_stage value */
	if (coarse == true)
		next_stage = AF_RUN_STAGE_COARSE;
	else
		next_stage = AF_RUN_STAGE_FINE;

	/*
	 * "last_contrast" is the contrast calculated in last step. Adding the current contrast less than last
	 * contrast makes sure that after reach the top point, the contrast must be monontic decline.
	 */
	if (((curr->contrast <= get_af_judge_threshold_low(top->contrast))
	     && (!detect_local_maximum(af_info, contrast_array, first_contrast) || down_hill > 1))
	   || (curr->contrast <= top->contrast && check_vcmcode_is_edge(trip, curr->code) == true)) {
		/* valid range run over or top condition is found, than change to next stage */
		if ((top->contrast < histtop->contrast) ||
			(top->contrast == histtop->contrast && top->code > histtop->code)) {
			top->contrast = histtop->contrast;
			top->code = histtop->code;
		}

		print_debug("top code 0x%x found!!!!!!!", top->code);
		down_hill = 0;

		if (coarse == true) {
			/* same direction, get top hand fine code(same side with current) */
			af_get_next_vcmcode(trip, top->code, trip->direction, AF_CODE_STEP_FINE, &next_code);
			/* turn back */
			trip->direction = 0 - trip->direction;
			next_stage = AF_RUN_STAGE_FINE;
		} else {
			next_code = top->code;
			next_stage = AF_RUN_STAGE_END;
		}

		curr->code = next_code;
		trip->step_cnt++;
		//ispv1_setreg_vcm_code(curr->code);
	} else if (check_vcmcode_is_edge(trip, curr->code) == true) {
		/* reach edge code, no matter current is COARSE or FINE, stay here */
		/* valid range run over, last position is top position */
		print_debug("reach edge code, coarse flag %d, top code is current 0x%x !!!!!!!", coarse, curr->code);
		trip->step_cnt++;
		next_stage = AF_RUN_STAGE_END;
		top->code = curr->code;
		down_hill = 0;
	} else if (curr->contrast <= top->contrast) {
		if (curr->contrast <= get_af_judge_threshold_low(top->contrast)) {
			down_hill++;
		}

		/* retry and goto next position, because diff is too small. */
		if (coarse == true)
			code_found = af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_COARSE, &next_code);
		else
			code_found = af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_FINE, &next_code);

		if (code_found == true) {
			if (curr->contrast >= top->contrast && curr->contrast >= histtop->contrast) {
				histtop->contrast = curr->contrast;
				histtop->code = curr->code;
			}
			curr->code = next_code;
			trip->step_cnt++;
			ispv1_setreg_vcm_code(curr->code);
		} else {
			print_error("%s line %d:next vcmcode will out of range!!!!!!!", __func__, __LINE__);
			/* Top code found: (1) go to next stage if in coarse stage; (2)rewind and goto END if in fine stage; */
			if (coarse == true) {
				/* same direction, get top hand code(same side with current) */
				af_get_next_vcmcode(trip, top->code, trip->direction, AF_CODE_STEP_FINE, &next_code);
				/* turn back */
				trip->direction = 0 - trip->direction;
				next_stage = AF_RUN_STAGE_FINE;
			} else {
				next_code = top->code;
				next_stage = AF_RUN_STAGE_END;
			}
			trip->step_cnt++;
			curr->code = next_code;
			ispv1_setreg_vcm_code(curr->code);
		}
	} else {
		/* update top info and goto next position. */
		top->contrast = curr->contrast;
		top->code = curr->code;
		down_hill = 0;

		if (coarse == true)
			code_found = af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_COARSE, &next_code);
		else
			code_found = af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_FINE, &next_code);

		if (code_found == true) {
			curr->code = next_code;
			trip->step_cnt++;
			ispv1_setreg_vcm_code(curr->code);
		} else {
			print_error("%s line %d:next vcmcode will out of range!!!!!!!", __func__, __LINE__);
			/* Top code is this, END stage */
			next_stage = AF_RUN_STAGE_END;
		}
	}
	return next_stage;
}

static af_run_stage ispv1_vcaf_search_top(mini_af_run_param *af_info, mini_pos_info *curr, mini_vcm_info_s *vcm)
{
	mini_af_trip_info *trip = &(af_info->trip);
	mini_pos_info *top = &(af_info->top);
	mini_pos_info *histtop = &(af_info->histtop);

	u32 next_code = 0;
	bool code_found = false;
	af_run_stage next_stage = VCAF_RUN_STAGE_FORWARD;

	if (curr->contrast <= get_af_judge_threshold_low(top->contrast) ||
		(curr->contrast <= top->contrast  && check_vcmcode_is_edge(trip, curr->code) == true)) {
		/* Top code found, goto REWIND, in this case, should not go back by 1step. */

		if ((top->contrast < histtop->contrast) ||
			(top->contrast == histtop->contrast && top->code > histtop->code)) {
			top->contrast = histtop->contrast;
			top->code = histtop->code;
		}

		/* prepare next code for rewind. */
		if (abs(top->code - curr->code) >= get_af_large_step(vcm->coarseStep, vcm->videoStrideRatio)) {
			if (top->code > curr->code)
				trip->direction = AF_RUN_DIRECTION_FORWARD;
			else
				trip->direction = AF_RUN_DIRECTION_BACKWARD;

			af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
		} else
			next_code = top->code;

		curr->code = next_code;

		print_debug("top code 0x%x found!!!!!!!", top->code);

		/* rewind to next code. */
		ispv1_setreg_vcm_code(curr->code);
		next_stage = VCAF_RUN_STAGE_REWIND;
	} else if (check_vcmcode_is_edge(trip, curr->code) == true) {
		/* reach edge code, stay here */
		next_stage = VCAF_RUN_STAGE_REWIND;
		top->code = curr->code;
	} else if (curr->contrast <= top->contrast) {
		/* retry and goto next position, because diff is too small. */
		code_found = af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
		if (code_found == true) {
			if (curr->contrast >= top->contrast && curr->contrast >= histtop->contrast) {
				histtop->contrast = curr->contrast;
				histtop->code = curr->code;
			}
			curr->code = next_code;
			ispv1_setreg_vcm_code(curr->code);
		} else {
			print_error("%s line %d:next vcmcode will out of range!!!!!!!", __func__, __LINE__);
			/* Top code found, goto REWIND, in this case, should not go back by 1step. */

			/* prepare next code for rewind. */
			if (abs(top->code - curr->code) >= get_af_large_step(vcm->coarseStep, vcm->videoStrideRatio)) {
				if (top->code > curr->code)
					trip->direction = AF_RUN_DIRECTION_FORWARD;
				else
					trip->direction = AF_RUN_DIRECTION_BACKWARD;

				af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
			} else
				next_code = top->code;

			curr->code = next_code;
			/* rewind to next code. */
			ispv1_setreg_vcm_code(curr->code);
			next_stage = VCAF_RUN_STAGE_REWIND;
		}
	} else {
		/* update top info and goto next position. */
		top->contrast = curr->contrast;
		top->code = curr->code;

		code_found = af_get_next_vcmcode(trip, curr->code, trip->direction, AF_CODE_STEP_VIDEO, &next_code);
		if (code_found == true) {
			curr->code = next_code;
			ispv1_setreg_vcm_code(curr->code);
		} else {
			print_error("%s line %d:next vcmcode will out of range!!!!!!!", __func__, __LINE__);
			/* Top code is this, goto REWIND stage */
			next_stage = VCAF_RUN_STAGE_REWIND;
		}
	}

	return next_stage;
}

/*
 **************************************************************************
 * FunctionName: ispv1_check_caf_need_restart
 * Description : decide whether restart caf
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : ret: false - do not need restart CAF, true - need restart CAF.
 * Other       : NA;
 **************************************************************************
 */
static bool ispv1_check_caf_need_restart(mini_focus_frame_stat_s *start_data, mini_focus_frame_stat_s *end_data)
{
	u32 diff_x, diff_y, diff_z;
	u16 force_start = 0;
	mini_effect_params *effect = get_effect_ptr();
	mini_caf_trigger_s *this_caf_trigger = &effect->af_param.focus_algo.caf_trigger;

	diff_x = abs(start_data->xyz.x - end_data->xyz.x);
	diff_y = abs(start_data->xyz.y - end_data->xyz.y);
	diff_z = abs(start_data->xyz.z - end_data->xyz.z);

	/* If xyz diff too much, should force focus restart. */
	if (diff_x >= this_caf_trigger->restart_diff_xyz)
		force_start |= 0x01;
	if (diff_y >= this_caf_trigger->restart_diff_xyz)
		force_start |= 0x02;
	if (diff_z >= this_caf_trigger->restart_diff_xyz)
		force_start |= 0x04;

	if (force_start) {
		print_info("CAF need restart reason: 0x%x", force_start);
		return true;
	} else {
		return false;
	}
}


static bool enlarge_focus_window(mini_camera_rect_s *rect, int width, int height, int zoom)
{
	int center_x, center_y;
	int left, top, new_width, new_height;

	if (zoom == 0) {
		new_width = ((rect->width) << 1) + rect->width;
		new_height = ((rect->height) << 1) + rect->height;
	} else {
        return true;
	}

	center_x = rect->top + (rect->height >> 1);
	center_y = rect->left + (rect->width >> 1);

	new_width = new_width > width ? width : new_width;
	new_height = new_height > height ? height : new_height;

	/*
	 * Reason: when any of 'left' and 'top' is large close to the width and height
	 *         and the new_width or new_height is odd number, then left shifting of
	 *         these two number could not correctly calculate the half of them. Let
	 *         the new_height and width to be even number will correct the problem of
	 *         underflow and overflow.
	 */
	new_width = (new_width >> 1) << 1;
	new_height = (new_height >> 1) << 1;

	if (center_x - (new_height >> 1) < 0) {
		center_x += (new_height >> 1) - center_x;
	}

	if (center_y - (new_width >> 1) < 0) {
		center_y += (new_width >> 1) - center_y;
	}

	if (center_x + (new_height >> 1) >= height) {
		center_x -= (center_x + (new_height >> 1)) - height;
	}

	if (center_y + (new_width >> 1) >= width) {
		center_y -= (center_y + (new_width >> 1)) - width;
	}

	top = center_x - (new_height >> 1);
	left = center_y - (new_width >> 1);

	rect->height = new_height;
	rect->left = left;
	rect->top = top;
	rect->width = new_width;

	return true;
}

/*
 **************************************************************************
 * FunctionName: analysis_large_contrast_value;
 * Description : analysis contrast value of coarse step phase,
 				and judge focus result in this time
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static bool analysis_large_contrast_value(mini_pos_info *array, mini_af_run_param *af_info, mini_pos_info *top)
{
	mini_af_trip_info *trip = &(af_info->trip);
	u32 array_size = trip->step_cnt;
	u32 index = 0;
	u8  top_cnt = 0;
	u32 contrast_top = 0;
	u8 top_index = 0;
	bool ret = true;
	u8 start_index = 0;
	u32 contrast_threshold = 0;
	u32 focus_lum;

	/* search top contrast and count that */
	af_info->af_analysis = 0;

	/* search top contrast's index and count that */
	for (index = 0; index < array_size; index++) {
		if (contrast_top < array[index].contrast) {
			contrast_top = array[index].contrast;
			top_index = index;
			af_info->af_analysis = 0;
		} else if (contrast_top == array[index].contrast) {
			if ((index - top_index) > 2 ) {
				af_info->af_analysis |= 0x02;
			}
		}
	}

	top->code = array[top_index].code;
	top->contrast = array[top_index].contrast;

	if ((abs(contrast_top - array[0].contrast) < FOCUS_PARAM_JUDGE_ERROR_MINDIFF) &&
		(array_size > FOCUS_PARAM_JUDGE_ERROR_MINSTEPS) &&
		contrast_top < FOCUS_PARAM_JUDGE_LOW_CONTRAST) {
		af_info->af_analysis |= 0x04;
	}

	focus_lum = ispv1_focus_get_win_lum(&mini_afae_ctrl->lum_info);
	if (focus_lum <= FOCUS_PARAM_JUDGE_ERROR_LUM) {
		af_info->af_analysis |= 0x04;
	}

	contrast_threshold = contrast_top * CONTRAST_THRESHOLD_PERCENT / 100;
	/* analysis slope of curve */
	if (array_size > 10) {
		if (top_index < 3) {
			start_index = 0;
		} else if (top_index > array_size - 4) {
			start_index = array_size - 7;
		} else {
			start_index = top_index - 3;
		}

		for (index = start_index; index < start_index + 7; index++) {
			if (contrast_threshold < array[index].contrast) {
				top_cnt++;
			}
		}

		if (top_cnt > MAX_COUNT_FOR_SMOOTH_AREA) {
			af_info->af_analysis |= 0x01;
		}
	}

	if (af_info->af_analysis != 0) {
		ret = false;
	}

	return ret;
}


static bool detect_local_maximum(mini_af_run_param *af_info, u32* contrast_array, int contrast)
{
	bool result = false;
	mini_af_trip_info *trip = &(af_info->trip);
	mini_pos_info *top = &(af_info->top);
	int min_contrast = MIN_CONTRAST_INIT;
	int index, ratio;

	for (index = 0; index < trip->step_cnt; index++) {
		if (contrast_array[index] < min_contrast) {
			min_contrast = contrast_array[index];
		}
	}

	ratio = top->contrast / min_contrast;

	if (contrast > (top->contrast + (top->contrast >> 1)) ||
		trip->step_cnt < MIN_STEP_NEEDED ||
		ratio >= CONTRAST_RATIO) {
		result = true;
	}

	return result;
}

int mini_ispv1_set_vcm_dest_code(u32 dest_code)
{
	mini_vcm_info_s *vcm = get_vcm_ptr();

	print_info("dest_code=%d, vcm->infiniteDistance=%d, vcm->normalDistanceEnd=%d", dest_code, vcm->infiniteDistance, vcm->normalDistanceEnd);

	if(dest_code < vcm->infiniteDistance)
		dest_code = vcm->infiniteDistance;
	if(dest_code > vcm->normalDistanceEnd)
		dest_code = vcm->normalDistanceEnd;

	ispv1_setreg_vcm_code(dest_code);

	return 0;
}
int mini_ispv1_face_yuvrect_to_rawrect(void* face_area_s)
{
	face_rect_s* face_area = (face_rect_s*)face_area_s;
	mini_k3_isp_data *ispdata = mini_this_ispdata;
	u32 zoom = ispdata->zoom;
	u32 preview_width = ispdata->pic_attr[STATE_PREVIEW].out_width;
	u32 preview_height = ispdata->pic_attr[STATE_PREVIEW].out_height;

	mini_camera_rect_s yuv_rect, yuv_in_full, raw_rect;
	memset(&yuv_rect,0x00,sizeof(mini_camera_rect_s));
	memset(&yuv_in_full,0x00,sizeof(mini_camera_rect_s));
	memset(&raw_rect,0x00,sizeof(mini_camera_rect_s));

	memcpy(&yuv_rect,face_area,sizeof(face_rect_s));

	/* check width and height are valid, then adjust it. */
	if (yuv_rect.width == 0 || yuv_rect.height == 0) {
		ispv1_focus_get_default_yuvrect(&yuv_rect, preview_width, preview_height);
		print_info("default yuv rect:%d,%d,%d,%d",
		    yuv_rect.left, yuv_rect.top, yuv_rect.width, yuv_rect.height);
	}

	/* most case is just one focus rect. */
	if ((yuv_rect.left + yuv_rect.width) > preview_width || (yuv_rect.top + yuv_rect.height) > preview_height) {
		print_error("%s, line %d: rect area error!", __func__, __LINE__);
		return -1;
	}

	memcpy(&yuv_in_full, &yuv_rect, sizeof(mini_camera_rect_s));
	print_debug("face yuv rect to raw rect step1:[%d,%d:%d x %d], zoom %d", yuv_in_full.left, yuv_in_full.top, yuv_in_full.width, yuv_in_full.height, zoom);
	ispv1_get_yuvrect_of_full(&ispdata->pic_attr[STATE_PREVIEW], &yuv_in_full, zoom);
	print_debug("face yuv rect to raw rect step2:[%d,%d:%d x %d], zoom %d", yuv_in_full.left, yuv_in_full.top, yuv_in_full.width, yuv_in_full.height, zoom);

	/* adjust yuv rect. */
	ispv1_focus_adjust_yuvrect(&yuv_in_full, preview_width, preview_height, zoom);
	print_debug("face yuv rect to raw rect step3:[%d,%d:%d x %d], zoom %d", yuv_in_full.left, yuv_in_full.top, yuv_in_full.width, yuv_in_full.height, zoom);

	/* convert back to modified app rect for contrast calculate */
	memcpy(&yuv_rect, &yuv_in_full, sizeof(mini_camera_rect_s));
	ispv1_get_yuvrect_of_app(&ispdata->pic_attr[STATE_PREVIEW], &yuv_rect, zoom);
	print_debug("face yuv rect to raw rect step4:[%d,%d:%d x %d], zoom %d", yuv_rect.left, yuv_rect.top, yuv_rect.width, yuv_rect.height, zoom);

	/* convert yuv rect to raw rect. */
	mini_k3_isp_yuvrect_to_rawrect(&yuv_in_full, &raw_rect);

	memcpy(face_area,&raw_rect,sizeof(face_rect_s));
	print_info("face yuv rect [%d,%d :%d x %d] to raw rect [%d,%d :%d x %d], zoom %d",yuv_in_full.left,yuv_in_full.top,yuv_in_full.width,yuv_in_full.height,
		raw_rect.left,raw_rect.top,raw_rect.width,raw_rect.height,zoom);

	return 0;
}

int ispv1_gyro_status_collect(mini_focus_frame_stat_s *curr_data, mini_focus_frame_stat_s *mean_data)
{
	int loopi;
	u32 variance[5] = {0, 0, 0, 0, 0};
//	u32 contrast_diff = 0;
//	u32 lum_diff = 0;
	mini_axis_triple xyz_diff = {0, 0, 0};
	int stat_cnt;
	mini_ispv1_afae_ctrl *this_afae_ctrl = mini_afae_ctrl;
	mini_effect_params *effect = get_effect_ptr();
	mini_caf_trigger_s *this_caf_trigger = &effect->af_param.focus_algo.caf_trigger;
	int caf_stat_cmp_frames =
		this_caf_trigger->stat_cmp_end_frame - this_caf_trigger->stat_cmp_start_frame + 1;

	this_afae_ctrl->focus_stat_frames++;

	/* skip first frame, and get mean of next 4 frames contrast/gain/expo/lum value as compare data. */
	if ((this_afae_ctrl->focus_stat_frames >= this_caf_trigger->stat_cmp_start_frame)
		&& (this_afae_ctrl->focus_stat_frames <= this_caf_trigger->stat_cmp_end_frame)) {
		this_afae_ctrl->compare_data.xyz.x += curr_data->xyz.x;
		this_afae_ctrl->compare_data.xyz.y += curr_data->xyz.y;
		this_afae_ctrl->compare_data.xyz.z += curr_data->xyz.z;

		if (this_afae_ctrl->focus_stat_frames == this_caf_trigger->stat_cmp_end_frame) {
			this_afae_ctrl->compare_data.xyz.x /= caf_stat_cmp_frames;
			this_afae_ctrl->compare_data.xyz.y /= caf_stat_cmp_frames;
			this_afae_ctrl->compare_data.xyz.z /= caf_stat_cmp_frames;

			/*
			 * init all frame's contrast/gain/expo/lum array as compare data.
			 * used in preview tasklet to judge scene switch.
			 */
			for (loopi = 0; loopi < this_caf_trigger->stat_frame; loopi++) {
				memcpy(&this_afae_ctrl->frame_stat[loopi], &this_afae_ctrl->compare_data,
					sizeof(mini_focus_frame_stat_s));
			}
		}
	}

	if (this_afae_ctrl->focus_stat_frames <= this_caf_trigger->stat_skip_frame)
		return -1;

	if (curr_data->fps <= 20)
		stat_cnt = this_caf_trigger->stat_frame_low;
	else
		stat_cnt = this_caf_trigger->stat_frame;

	/* update new contrast/gain/expo/lum value array */
	memcpy(&this_afae_ctrl->frame_stat[0], &this_afae_ctrl->frame_stat[1],
		(stat_cnt - 1) * sizeof(mini_focus_frame_stat_s));

	memcpy(&this_afae_ctrl->frame_stat[stat_cnt - 1], curr_data,
		sizeof(mini_focus_frame_stat_s));

	/* calculate current mean contrast/gain/expo/lum */
	memset(mean_data, 0, sizeof(mini_focus_frame_stat_s));
	for (loopi = 0; loopi < stat_cnt; loopi++) {
		mean_data->xyz.x += this_afae_ctrl->frame_stat[loopi].xyz.x;
		mean_data->xyz.y += this_afae_ctrl->frame_stat[loopi].xyz.y;
		mean_data->xyz.z += this_afae_ctrl->frame_stat[loopi].xyz.z;
	}

	mean_data->xyz.x /= stat_cnt;
	mean_data->xyz.y /= stat_cnt;
	mean_data->xyz.z /= stat_cnt;

	for (loopi = 0; loopi < stat_cnt; loopi++) {
		/* use last stat data as base calculate value */
		variance[2] = abs(this_afae_ctrl->frame_stat[loopi].xyz.x - this_afae_ctrl->frame_stat[stat_cnt - 1].xyz.x);
		variance[3] = abs(this_afae_ctrl->frame_stat[loopi].xyz.y - this_afae_ctrl->frame_stat[stat_cnt - 1].xyz.y);
		variance[4] = abs(this_afae_ctrl->frame_stat[loopi].xyz.z - this_afae_ctrl->frame_stat[stat_cnt - 1].xyz.z);

		variance[2] *= variance[2];
		variance[3] *= variance[3];
		variance[4] *= variance[4];

		xyz_diff.x += variance[2];
		xyz_diff.y += variance[3];
		xyz_diff.z += variance[4];
	}
	xyz_diff.x /= stat_cnt;
	xyz_diff.y /= stat_cnt;
	xyz_diff.z /= stat_cnt;

	mean_data->xyz_var.x = xyz_diff.x;
	mean_data->xyz_var.y = xyz_diff.y;
	mean_data->xyz_var.z = xyz_diff.z;

	return 0;
}

u16 ispv1_calc_gyro_stat_diff(mini_focus_frame_stat_s *pre_data, mini_focus_frame_stat_s *cur_data)
{
	u16 ret_val = 0;
	mini_focus_frame_stat_s diff;
	mini_effect_params *effect = get_effect_ptr();
	mini_caf_trigger_s *this_caf_trigger = &effect->af_param.focus_algo.caf_trigger;

	diff.xyz.x = abs(pre_data->xyz.x - cur_data->xyz.x);
	diff.xyz.y = abs(pre_data->xyz.y - cur_data->xyz.y);
	diff.xyz.z = abs(pre_data->xyz.z - cur_data->xyz.z);

	if (diff.xyz.x >= this_caf_trigger->cmp_diff_xyz)
		ret_val |= 0x10;
	if (diff.xyz.y >= this_caf_trigger->cmp_diff_xyz)
		ret_val |= 0x20;
	if (diff.xyz.z >= this_caf_trigger->cmp_diff_xyz)
		ret_val |= 0x40;

	return ret_val;
}

/*
 * return boolean value, true: moving, false: static.
 */
bool ispv1_check_gyro_caf_need_trigger(mini_focus_frame_stat_s *compare_data, mini_focus_frame_stat_s *mean_data, mini_focus_frame_stat_s cur_data)
{
	u8 unpeace = 0;
	static u16 unpeace_ms;
	u16 force_start = get_caf_forcestart();
	u16 diff_val = 0;
//	u8 fps = 30;//this_ispdata->sensor->fps;
	bool trigger = false;
	mini_effect_params *effect = get_effect_ptr();
	mini_caf_trigger_s *this_caf_trigger = &effect->af_param.focus_algo.caf_trigger;
	mini_ispv1_afae_ctrl *this_afae_ctrl = mini_afae_ctrl;
	
	if (force_start == 0) {
		/* if diff too much, should force focus start. */
		diff_val = ispv1_calc_gyro_stat_diff(compare_data, mean_data);
		force_start = diff_val;
		set_caf_forcestart(force_start);
	} else if ((force_start & CAF_FORCESTART_FORCE) != 0) {
		unpeace_ms = 0;
		// return CAF_DETECT_RESULT_TRIGGER;
		return false;
	}

	if (force_start == 0)
		//return CAF_DETECT_RESULT_NONE;
		return false;

	if (mean_data->xyz_var.x > this_caf_trigger->var_diff_xyz)
		unpeace |= 0x10;
	if (mean_data->xyz_var.y > this_caf_trigger->var_diff_xyz)
		unpeace |= 0x20;
	if (mean_data->xyz_var.z > this_caf_trigger->var_diff_xyz)
		unpeace |= 0x40;

	print_debug("mean  xyz var [%d, %d, %d]",
		mean_data->xyz_var.x, mean_data->xyz_var.y, mean_data->xyz_var.z);

	if (force_start && unpeace == 0) {
			if ((this_afae_ctrl->focus_stat_frames > this_caf_trigger->stat_skip_frame)
	              && ((force_start & 0xff00) == 0)) {
				
				diff_val = ispv1_calc_gyro_stat_diff(compare_data, &cur_data);
				if (diff_val != 0)
					trigger = true;
			}
			unpeace_ms = 0;
			if (trigger == true) {
				print_info("CAF scene changed reason:  diff_val 0x%x!", diff_val);
				//return CAF_DETECT_RESULT_TRIGGER;
				return false;
			} else {
				set_caf_forcestart(CAF_FORCESTART_CLEAR);
				//return CAF_DETECT_RESULT_NOISE;
				return false;
			}
	} else {
#if 0
		print_debug("force_start 0x%x, but unpeace 0x%x, gsensor unpeace_ms %d", force_start, unpeace, unpeace_ms);

		/* if unpeace caused by Gsensor more than XX seconds, force VCM go to infinite. */
		if ((unpeace & 0xf0) != 0) {
			if (unpeace_ms < this_caf_trigger->goto_infinite_timeout) {
				unpeace_ms += 1000 / fps;
				return CAF_DETECT_RESULT_NONE;
			} else {
				/* if gsensor is unpeace than (XX * fps), force VCM go to infinite */
				unpeace_ms = 0;
				return CAF_DETECT_RESULT_INFINITE;
			}
		} else {
			/* if gsensor is stable, Gsensor unpeace count set zero and return RESULT_NONE. */
			unpeace_ms = 0;
			return CAF_DETECT_RESULT_NONE;
		}
#endif
		// camera is in moving condition
		return true;
	}
}


void misp_gyro_info(void)
{
	mini_focus_frame_stat_s curr_data;
	mini_focus_frame_stat_s mean_data;
	
	bool result = false;
	int ret =0;
	
	mini_ispv1_afae_ctrl *afae_ctrl_ptr = mini_afae_ctrl;
	
	curr_data.fps = mini_this_ispdata->meta_data->data.common_info.frame_rate;
	if(afae_ctrl_ptr->af_result == STATUS_FOCUSING)
	{
		ispv1_focus_status_reset();
		return;
	}

	memset(&curr_data, 0, sizeof(mini_focus_frame_stat_s));
	memset(&mean_data, 0, sizeof(mini_focus_frame_stat_s));
	
	curr_data.fps = curr_data.fps/100;
	if(curr_data.fps == 0)
		curr_data.fps = mini_this_ispdata->sensor->fps_max;
	memcpy(&curr_data.xyz, &mini_mXYZ, sizeof(mini_axis_triple));
	ret = ispv1_gyro_status_collect(&curr_data,&mean_data);	
	if (ret != 0)
		return;
	result = ispv1_check_gyro_caf_need_trigger(&mini_afae_ctrl->compare_data, &mean_data, curr_data);	
	if(!result)
	{
		print_info("%s result = %d",__func__,result);
		camera_agent_set_Motion_Detected(0);
	}
	else
	{
		camera_agent_set_Motion_Detected(1);
	}
}
