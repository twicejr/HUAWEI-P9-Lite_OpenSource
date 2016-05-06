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


#include <linux/io.h>
#include "cam_log.h"
#include "k3_isp.h"
#include "k3_ispv1.h"
#include "k3_ispv1_afae.h"
#include "../camera.h"
#include "hwa_cam_tune.h"
#include "hwa_cam_tune_common.h"

#include <media/v4l2-common.h>
#include <linux/fb.h>
#include "k3_v4l2_capture.h"
#include "sensor_common.h"
#include "cam_dbg.h"
#include "cam_util.h"
#include "k3_isp_io.h"

extern k3_isp_data *this_ispdata;


int hwa_v4l2_ioctl_g_ctrls(struct file *file, void *fh, struct v4l2_control *v4l2_param)
{
	int ret = 0;

	switch(v4l2_param->id)
	{
		case V4L2_CID_GET_ALGORITHM_ISO	:
		{
			v4l2_param->value = k3_isp_get_algorithm_iso();
			break;
		}
		case V4L2_CID_FLASH_STATUS:
		{
			v4l2_param->value = this_ispdata->flash_flow;
			break;
		}
                case V4L2_CID_GET_FOCUS_FRAME_CNT:
                {
                    v4l2_param->value = this_ispdata->zsl_ctrl.focused_frame_cnt;
                    break;
                }
                case V4L2_CID_GET_AF_LEVEL:
                {
                     v4l2_param->value = hwa_get_af_level();
                     break;
                }
                case V4L2_CID_GET_AF_RANGE_MIN:
                {
                     v4l2_param->value = hwa_get_af_ramge_min();
                     break;
		  }
                case V4L2_CID_GET_AF_RANGE_MAX:
                {
                     v4l2_param->value = hwa_get_af_ramge_max();
                     break;
                }
                case V4L2_CID_GET_OTP_STATUS://get opt info from sensor
                {
                    v4l2_param->value = hwa_get_otp_status();
                    break;
                }
		default:
			break;
	}
	return ret;
}
int hwa_v4l2_ioctl_s_ctrls(struct file *file, void *fh, struct v4l2_control *v4l2_param)
{
	int ret = 0;
	switch(v4l2_param->id)
	{
		case V4L2_CID_SET_VCM_DEST_CODE:
		{
			ret = hwa_set_af_dest_code(v4l2_param->value);
			break;
		}
		case V4L2_CID_SET_FAST_SNAPSHOT_MODE:
		{
			hwa_set_fast_shot_af_mode(v4l2_param->value);
			break;
		}
		default:
			break;
	}
	return ret;
}

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef struct ae_coff {
    u32 exposure_max;
    u32 exposure_min;
    u32 gain_max;
    u32 gain_min;
    u32 luma_target_high;
    u32 luma_target_low;
    u32 exposure;
    u32 exposure_time;
    u32 gain;
    u32 iso;
}ae_coff;

typedef struct extra_coff {
    u32 mean_y;
    s32 motion_x;
    s32 motion_y;
    u32 focal_length;
    u32 af_window_change;
}extra_coff;

static int ispv1_get_extra_coff(extra_coff *extra_data)
{
    extra_data->mean_y   = GETREG8(0x1c758);
    extra_data->motion_x = (s8)GETREG8(0x1cc7c);
    extra_data->motion_y = (s8)GETREG8(0x1cc7d);

    extra_data->focal_length = ispv1_get_focus_distance();
    extra_data->af_window_change = GETREG8(0x1cdd2);

    return 0;
}

static int ispv1_get_ae_coff(ae_coff *ae_data)
{
    GETREG16(0x1c158, ae_data->exposure_max);
    GETREG16(0x1c15c, ae_data->exposure_min);
    GETREG16(0x1c150, ae_data->gain_max);
    GETREG16(0x1c154, ae_data->gain_min);
    ae_data->luma_target_high = GETREG8(REG_ISP_TARGET_Y_HIGH);
    ae_data->luma_target_low = GETREG8(REG_ISP_TARGET_Y_LOW);
    ae_data->exposure = get_writeback_expo() >> 4;
    ae_data->exposure_time = ispv1_get_exposure_time();
    ae_data->gain = get_writeback_gain();
    ae_data->iso = k3_isp_get_algorithm_iso();

    return 0;
}

static int k3_isp_get_extra_coff(extra_coff *extra_data)
{
    int ret = 0;

    if (this_ispdata->sensor->isp_location == CAMERA_USE_K3ISP)
        ret = ispv1_get_extra_coff(extra_data);

    return ret;
}

static int k3_isp_get_ae_coff(ae_coff *ae_data)
{
    int ret = 0;

    if (this_ispdata->sensor->isp_location == CAMERA_USE_K3ISP)
        ret = ispv1_get_ae_coff(ae_data);

    return ret;
}

int k3_isp_get_algorithm_iso(void)
{
	camera_sensor *sensor = this_ispdata->sensor;
	u16 gain;
	int iso;
	int index;
	bool summary;

	if (isp_hw_data.cur_state == STATE_PREVIEW) {
		index = sensor->preview_frmsize_index;
		gain = get_writeback_gain();
	} else {
		index = sensor->capture_frmsize_index;
		gain = get_writeback_cap_gain();
	}
	summary = sensor->frmsize_list[index].summary;

	iso = ispv1_gain2iso(gain, summary);
	return iso;
}


int hwa_v4l2_ioctl_g_ext_ctrls(struct v4l2_ext_control **controls, __u32 cmd_id, __u32 cid_idx)
{
	int ret = 0;

	switch(cmd_id)
	{
		case V4L2_CID_GET_MULTI_ISP_REG:
		{
			hwq_multi_reg_data *seq_data = NULL;
			seq_data = (hwq_multi_reg_data *)(((*controls)[cid_idx]).string);

			if(NULL == seq_data || NULL == seq_data->reg || NULL == seq_data->value){
				ret = -EINVAL;
				print_error("seq_data is NULL");
				goto out;
			}

			if(seq_data->length <= 0 || seq_data->length >= 1000){
				ret = -EINVAL;
				print_error("V4L2_CID_GET_MULTI_ISP_REG seq_data->length error!");
				goto out;
			}

			if (NULL == this_ispdata) {
				print_error("this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(this_ispdata->sensor->isp_location == CAMERA_USE_K3ISP){
				ret = hwa_get_multi_isp_reg(seq_data);
			}

			break;
		}
		case V4L2_CID_GET_BRACKET_ISO_VALUE:
		{
			int *iso = NULL;
			iso = (int *)(((*controls)[cid_idx]).string);

			if(NULL == iso){
				ret = -EINVAL;
				print_error("iso is NULL");
				goto out;
			}

			if (NULL == this_ispdata) {
				print_error("this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == this_ispdata->sensor->isp_location){
				ret = hwa_get_bracket_iso(iso);
			}

			break;
		}
		case V4L2_CID_GET_BRACKET_EXP_VALUE:
		{
			int *exp = NULL;
			exp = (int *)(((*controls)[cid_idx]).string);

			if(NULL == exp){
				ret = -EINVAL;
				print_error("exp is NULL");
				goto out;
			}

			if (NULL == this_ispdata) {
				print_error("this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == this_ispdata->sensor->isp_location){
				ret = hwa_get_bracket_exp(exp);
			}
			break;
		}
		case V4L2_CID_GET_AE_COFF:
		{
			int data_size = sizeof(ae_coff);
			ae_coff *ae_data = NULL;
			void *data_buf = kmalloc(data_size, GFP_KERNEL);
			if (!data_buf) {
				ret = -ENOMEM;
				print_error("fail to allocate buffer for ext controls");
				goto out;
			}
			if(copy_from_user(data_buf, ((*controls)[cid_idx]).string, data_size)){
				ret = -EFAULT;
				kfree(data_buf);
				print_error("%s: V4L2_CID_GET_AE_COFF  copy_from_user   failed",__FUNCTION__);
				goto out;
			}
			ae_data = data_buf;
			ret = k3_isp_get_ae_coff(ae_data);
			if(copy_to_user(((*controls)[cid_idx]).string, data_buf, data_size)){
				ret =  -EFAULT;
				kfree(data_buf);
				print_error("%s: V4L2_CID_GET_AE_COFF  copy_to_user   failed",__FUNCTION__);
				goto out;
			}
			kfree(data_buf);
			break;
		}
		case V4L2_CID_GET_EXTRA_COFF:
		{
			int data_size = sizeof(extra_coff);
			extra_coff *extra_data = NULL;
			void *data_buf = kmalloc(data_size, GFP_KERNEL);
			if (!data_buf) {
				ret = -ENOMEM;
				print_error("fail to allocate buffer for ext controls");
				goto out;
			}
			if( copy_from_user(data_buf, ((*controls)[cid_idx]).string, data_size)){
				ret = -EFAULT;
				kfree(data_buf);
				print_error("%s :V4L2_CID_GET_EXTRA_COFF copy_from_user   failed",__FUNCTION__);
				goto out;
			}
			extra_data = data_buf;
			ret = k3_isp_get_extra_coff(extra_data);
			if(copy_to_user(((*controls)[cid_idx]).string, data_buf, data_size)){
				ret =  -EFAULT;
				kfree(data_buf);
				print_error("%s :V4L2_CID_GET_EXTRA_COFF copy_to_user   failed",__FUNCTION__);
				goto out;
			}
			kfree(data_buf);
			break;
		}
		case V4L2_CID_GET_LCD_COMPENSATION_SUPPORTED:
		{
			((*controls)[cid_idx]).value = hwa_check_lcd_compensation_supported();
			break;
		}
		case V4L2_CID_GET_LCD_COMPENSATION_NEEDED:
		{
			((*controls)[cid_idx]).value = hwa_check_lcd_compensation_needed();
			break;
		}
#if 0
		case V4L2_CID_GET_HDR_MOVIE_SUPPORTED:
		{
			int *support_hdr_movie= NULL;
			support_hdr_movie = (int *)(((*controls)[cid_idx]).string);

			if(NULL == support_hdr_movie){
				ret = -EINVAL;
				print_error("support_hdr_movie is NULL");
				goto out;
			}

			if (NULL == this_ispdata) {
				print_error("this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == this_ispdata->sensor->isp_location){
				if (this_ispdata->sensor->sensor_hdr_movie.support_hdr_movie) {
					*support_hdr_movie = this_ispdata->sensor->sensor_hdr_movie.support_hdr_movie();
				}
			}
			break;
		}
		case V4L2_CID_GET_HDR_MOVIE_CONSTANT_PARAM:
		{
			hdr_ae_constant_param *result = (hdr_ae_constant_param *)(((*controls)[cid_idx]).string);
			ispv1_get_hdr_movie_ae_init_param(result);
			break;
		}

		case V4L2_CID_GET_HDR_MOVIE_VOLATILE_PARAM:
		{
			hdr_ae_volatile_param *result = (hdr_ae_volatile_param *)(((*controls)[cid_idx]).string);
			
			ispv1_get_hdr_movie_ae_running_param(result);
			break;
		}
		case  V4L2_CID_GET_HDR_STATS_INFO:
		{
			stats_info *stats_data = (stats_info *)(((*controls)[cid_idx]).string);
			if(stats_data != NULL)
			{
				stats_data->stats_h = this_ispdata->sensor->sensor_hdr_movie.stats_data.stats_h;
				stats_data->stats_v = this_ispdata->sensor->sensor_hdr_movie.stats_data.stats_v;;
			}
			break;
		}
#endif
		case V4L2_CID_GET_AWB_OTP_INFO:
		{
			int support_awb_otp= AWB_OTP_NOT_SUPPORT;
			hw_awb_otp *awb_otp = (hw_awb_otp *)(((*controls)[cid_idx]).string);

			if (NULL == awb_otp || NULL == this_ispdata) {
				print_error("awb_otp or this_ispdata  is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == this_ispdata->sensor->isp_location){
				if (this_ispdata->sensor->sensor_hw_3a.support_awb_otp) {
					support_awb_otp = this_ispdata->sensor->sensor_hw_3a.support_awb_otp();
				}
			}

			if(NULL != awb_otp && AWB_OTP_SUPPORT == support_awb_otp){
				awb_otp->awb_otp_support = AWB_OTP_SUPPORT;
				awb_otp->r_g_high = this_ispdata->sensor->sensor_hw_3a.awb_otp_value.r_g_high;
				awb_otp->r_g_low = this_ispdata->sensor->sensor_hw_3a.awb_otp_value.r_g_low;
				awb_otp->b_g_high = this_ispdata->sensor->sensor_hw_3a.awb_otp_value.b_g_high;
				awb_otp->b_g_low = this_ispdata->sensor->sensor_hw_3a.awb_otp_value.b_g_low;
				awb_otp->gb_gr_high = this_ispdata->sensor->sensor_hw_3a.awb_otp_value.gb_gr_high;
				awb_otp->gb_gr_low = this_ispdata->sensor->sensor_hw_3a.awb_otp_value.gb_gr_low;
			}
			else{
				awb_otp->awb_otp_support = AWB_OTP_NOT_SUPPORT;
				awb_otp->r_g_high = 0;
				awb_otp->r_g_low =  0;
				awb_otp->b_g_high = 0;
				awb_otp->b_g_low =  0;
				awb_otp->gb_gr_high = 0;
				awb_otp->gb_gr_low = 0;
			}
			break;
		}
		default:
			break;
	}

out:
	return ret;
}

int hwa_v4l2_ioctl_s_ext_ctrls(struct v4l2_ext_control **controls, __u32 cmd_id, __u32 cid_idx)
{
	int ret = 0;
	//int func_ret = 0;
	
	switch(cmd_id)
	{
		case V4L2_CID_SET_MULTI_ISP_REG:
		{
			hwq_multi_reg_data *seq_data = NULL;
			seq_data = (hwq_multi_reg_data *)(((*controls)[cid_idx]).string);

			if(NULL == seq_data || NULL == seq_data->reg || NULL == seq_data->value){
				ret = -EINVAL;
				print_error("seq_data is NULL");
				goto out;
			}

			if(seq_data->length <= 0 || seq_data->length >= 1000){
				ret = -EINVAL;
				print_error("V4L2_CID_SET_MULTI_ISP_REG seq_data->length error!");
				goto out;
			}

			if (NULL == this_ispdata) {
				print_error("this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == this_ispdata->sensor->isp_location){
				ret = hwa_set_multi_isp_reg(seq_data);
			}

			break;
		}
		case V4L2_CID_SET_CAP_ISO_RATIO_VALUE:
		{
			int ratio = ((*controls)[cid_idx]).value;
			if(1000 > ratio) {
				ret = -EINVAL;
				goto out;
			}
			ret = hwa_set_cap_iso_ratio_value(ratio);

			break;
		}
		case V4L2_CID_HWSCOPE:
		{
			void *hwscope_data = (void *)(((*controls)[cid_idx]).string);

			if(NULL == hwscope_data){
				ret = -EINVAL;
				print_error("hwscope_data is NULL");
				goto out;
			}

			if (NULL == this_ispdata) {
				print_error("this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == this_ispdata->sensor->isp_location){
				ret = hwa_set_hwscope(hwscope_data);
			}

			break;
		}
#if 0
		case V4L2_CID_SET_HDR_MOVIE_MODE:
		{
			int hdr_movie_on =  ((*controls)[cid_idx]).value;
			if (!this_ispdata->sensor->sensor_hdr_movie.set_hdr_movie_switch)
			{
				ret = -EINVAL;	
				goto  out;
			}
            if(hdr_movie_on != this_ispdata->sensor->sensor_hdr_movie.get_hdr_movie_switch())
			{
				this_ispdata->sensor->sensor_hdr_movie.set_hdr_movie_switch(hdr_movie_on);

				if(1 == hdr_movie_on ){
					ispv1_hdr_movie_isp_vc_switch(1);
					ispv1_hdr_movie_isp_ae_write_mode(0);/* 0 - AP write shutter&gain */			
					ispv1_hdr_movie_isp_ae_ctrl_mode(1);/* 1 - AP's ae */			
				}else{
					ispv1_hdr_movie_isp_vc_switch(0);
					ispv1_hdr_movie_isp_ae_write_mode(1);/* 1 - ISP write sensor shutter&gain */
					ispv1_hdr_movie_isp_ae_ctrl_mode(0);/* 0 - ISP ae */
				}
			}
			break;
		}
		case V4L2_CID_SET_HDR_MOVIE_AE_RESULT:
		{
			int data_size = sizeof(hdr_ae_algo_result);
			void *data_buf = kmalloc(data_size, GFP_KERNEL);
			if (!data_buf) {
				ret = -ENOMEM;
				print_error("fail to allocate buffer for ext controls");
				goto  out;
			}
			if(copy_from_user(data_buf, (((*controls)[cid_idx]).string), data_size)){
				ret = -EFAULT;
				kfree(data_buf);
				print_error("%s :V4L2_CID_SET_HDR_MOVIE_AE_RESULT  copy_from_user   failed",__FUNCTION__);
				goto out;
			}
			hdr_ae_algo_result *ae_result = data_buf;
			func_ret = ispv1_set_hdr_movie_shutter_gain_to_sensor(ae_result);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			kfree(data_buf);
			break;
		}
		case V4L2_CID_SET_ALC_AWB_SATUS:
        {
            this_ispdata->alc_awb_status = ((*controls)[cid_idx]).value;
            break;
        }
#endif
		default:
			break;
	}

out:
	return ret;
}

int hwa_get_bracket_iso(int *iso)
{
	u16 gain;
	int index;
	bool summary;
	camera_sensor *sensor = this_ispdata->sensor;

	index = sensor->capture_frmsize_index;
	summary = sensor->frmsize_list[index].summary;

	GETREG16(ISP_FIRST_FRAME_GAIN, gain);
	iso[0] = ispv1_gain2iso(gain, summary);

	GETREG16(ISP_SECOND_FRAME_GAIN, gain);
	iso[1] = ispv1_gain2iso(gain, summary);

	GETREG16(ISP_THIRD_FRAME_GAIN, gain);
	iso[2] = ispv1_gain2iso(gain, summary);

	print_debug("iso [%d] [%d] [%d]\n",iso[0],iso[1],iso[2]);

	return 0;
}

int hwa_get_bracket_exp(int *exp)
{
	u32 expo, fps, vts;
	int index;
	camera_sensor *sensor = this_ispdata->sensor;
	index = sensor->capture_frmsize_index;

	fps = sensor->frmsize_list[index].fps;
	vts = sensor->frmsize_list[index].vts;

	GETREG32(ISP_FIRST_FRAME_EXPOSURE, expo);
	expo >>= 4;
	if (0 == expo)
	{
		print_info("hwa_get_bracket_exp exp[0]=0, reset expo to 0x22b00.");
		expo = (0x22b00 >> 4);
	}
	exp[0] = ispv1_expo_line2time(expo, fps, vts);

	GETREG32(ISP_SECOND_FRAME_EXPOSURE, expo);
	expo >>= 4;
	if (0 == expo)
	{
		print_info("hwa_get_bracket_exp exp[1]=0, reset expo to 0x22b00.");
		expo = (0x22b00 >> 4);
	}
	exp[1] = ispv1_expo_line2time(expo, fps, vts);

	GETREG32(ISP_THIRD_FRAME_EXPOSURE, expo);
	expo >>= 4;
	if (0 == expo)
	{
		print_info("hwa_get_bracket_exp exp[2]=0, reset expo to 0x22b00.");
		expo = (0x22b00 >> 4);
	}
	exp[2] = ispv1_expo_line2time(expo, fps, vts);

	print_debug("exp [%d] [%d] [%d]\n",exp[0],exp[1],exp[2]);

	return 0;
}
int hwa_get_multi_isp_reg(hwq_multi_reg_data *seq_data)
{
	int i = 0;
	int length = seq_data->length;
	int *reg = seq_data->reg;
	int *value = seq_data->value;

	for(i = 0; i < length; i++){
		value[i] = GETREG8(reg[i]);
		print_debug("hwa_get_multi_isp_reg i = %d, get reg[0x%x] = 0x%x", i, reg[i], value[i]);
	}

	return 0;
}

int hwa_set_multi_isp_reg(hwq_multi_reg_data *seq_data)
{
	int i;
	int length = seq_data->length;
	int *reg = seq_data->reg;
	int *value = seq_data->value;

	for(i = 0; i < length; i++){
		SETREG8(reg[i], value[i]);
		print_debug("hwa_set_multi_isp_reg i = %d, set reg[0x%x] = 0x%x", i, reg[i], value[i]);
	}

	return 0;
}


int hwa_set_cap_iso_ratio_value(int ratio)
{
	int max_iso, min_iso;
	int max_gain, min_gain;
	camera_sensor *sensor;
	ae_params_s *this_ae;

	print_debug("enter %s", __func__);

	if (NULL == this_ispdata) {
	print_info("this_ispdata is NULL");
		return -1;
	}
	sensor = this_ispdata->sensor;
	this_ae = &sensor->effect->ae_param;
	max_iso = this_ae->iso_max;
	min_iso = this_ae->iso_min;
	max_gain = max_iso * 0x10 / 100;
	min_gain = min_iso * 0x10 / 100;

	if( (sensor->frmsize_list[sensor->preview_frmsize_index].summary == false)&&(true == sensor->support_summary)){
		max_gain = max_gain * 2;
	}
	max_gain = max_gain*ratio/1000;
	print_debug("%s max_gain : %d", __func__,max_gain);
	SETREG8(REG_ISP_MAX_GAIN, (max_gain & 0xff00) >> 8);
	SETREG8(REG_ISP_MAX_GAIN + 1, max_gain & 0xff);
	SETREG8(REG_ISP_MIN_GAIN, (min_gain & 0xff00) >> 8);
	SETREG8(REG_ISP_MIN_GAIN + 1, min_gain & 0xff);
	sensor->min_gain = min_gain;
	sensor->max_gain = max_gain;
	if (1000 == ratio) // reset digital gain to 1x
	{
		if (sensor->set_gain)
		{
			sensor->set_gain(0);
		}
	}
	return 0;
}

hwa_hwscope_ctl hwa_hwscope;

int hwa_set_hwscope(void *data)
{
	hwa_hwscope_ctl *hwscope_data = data;

	print_debug("enter %s", __func__);

	if(hwscope_data->mode == HW_SCOPE_ON)
	{
		print_info("%s HW_SCOPE_ON", __func__);
		hwa_hwscope.mode = HW_SCOPE_ON;
	}
	else if(hwscope_data->mode == HW_SCOPE_OFF)
	{
		print_info("%s HW_SCOPE_OFF", __func__);
		hwa_hwscope.mode = HW_SCOPE_OFF;
	}
	else
	{
		print_error("%s mode=%d error", __func__, hwscope_data->mode);
	}
	hwa_hwscope.border = hwscope_data->border;

	return 0;
}

#define	WIDTH_ALIGN			0x0f	/* step = 16 */
#define	HEIGHT_ALIGN		0x07	/* step = 8 */

void hwa_calc_zoom_with_crop(camera_state state, scale_strategy_t scale_strategy, u32 *in_width, u32 *in_height)
{
	u32 scale_width;
	u32 scale_height;
	u32 temp_width;
	u32 temp_height;
	u32 scale;
	u32 ratio;
	u32 temp;
	u32 steps;
	int out_width;
	int out_height;
	pic_attr_t *attr = &this_ispdata->pic_attr[state];

	print_info("%s, zoom=%d, in_width=%d, in_height=%d",
			__func__, this_ispdata->zoom, *in_width, *in_height);

	if ((0 != (*in_width & WIDTH_ALIGN)) || (0 != (*in_height & HEIGHT_ALIGN))) {
		print_error("width %d is not 16x or height %d is not 4x", *in_width, *in_height);
		return;
	}

	if ((*in_height) * (attr->out_width) > (*in_width) * (attr->out_height)) {
		/*do raw height crop*/
		temp_height = (*in_width) * (attr->out_height) / (attr->out_width);
		temp_width = temp_height * (attr->out_width) / (attr->out_height);
	} else {
		/*do raw width crop */
		temp_width = (*in_height) * (attr->out_width) / (attr->out_height);
		temp_height = temp_width * (attr->out_height) / (attr->out_width);
	}

	/* do not support float compute, so multiple YUV_SCALE_DIVIDEND */
	scale_width = (YUV_SCALE_DIVIDEND * temp_width) / attr->out_width;
	scale_height = (YUV_SCALE_DIVIDEND * temp_height) / attr->out_height;
	scale = (scale_width < scale_height) ? scale_width : scale_height;
	print_debug("scale_width = %d, scale_height = %d, scale = %d",
			scale_width, scale_height, scale);

	/* we do not need raw scale down */
	attr->raw_scale_down = 1;
	attr->yuv_in_width = *in_width;
	attr->yuv_in_height = *in_height;

	temp = ZOOM_BASE;
	/* we need scale down, and we get scale down ratio */
	ratio = (scale * ZOOM_BASE) / temp;
	print_debug("scale down ratio is = %d", ratio);

	if (ratio >= (2 * YUV_SCALE_DIVIDEND)) {
		/* we need YUV_DCW_Fliter */
		print_debug("we need YUV_DCW_Fliter");
		if (ratio >= (8 * YUV_SCALE_DIVIDEND))
			attr->yuv_dcw = 8;	/*distortion */
		else if (ratio >= (4 * YUV_SCALE_DIVIDEND))
			attr->yuv_dcw = 4;
		else
			attr->yuv_dcw = 2;
	} else {
		attr->yuv_dcw = 1;
	}

	/* we need YUVDownScaleFliter */
	attr->yuv_down_scale_nscale = ratio / attr->yuv_dcw;
	attr->yuv_up_scale_nscale = YUV_SCALE_DIVIDEND;
	print_info("yuv_dcw=%d, yuv_down_scale_nscale = %d, yuv_up_scale_nscale=%d",
		attr->yuv_dcw, attr->yuv_down_scale_nscale,
		attr->yuv_up_scale_nscale);

	out_width = attr->out_width * 10 / (this_ispdata->zoom + 10) + hwa_hwscope.border * 2;
	out_width = (out_width + 16) & ~31;
	out_height = attr->out_height * 10 / (this_ispdata->zoom + 10) + hwa_hwscope.border * 2;
	/*
	ov Kevin:
	Format NV12 or NV21
		a = ceil (width/256)
		if a%2 != 0, height should be 16x
		else if a%2 == 0, height can be 8x
		else if a%4 == 0, height can be 4x
	*/
	print_info("crop size updated version");
	if (V4L2_PIX_FMT_NV12 == attr->out_fmt || V4L2_PIX_FMT_NV21 == attr->out_fmt)
	{
		steps = (out_width + 255) / 256;
		if (steps % 2 != 0) out_height = (out_height + 8) & ~15;
		//else if (steps % 4) out_height = (out_height + 4) & ~7;
		//else out_height = (out_height + 2) & ~3;
		else out_height = (out_height + 4) & ~7;
	}
	else
		out_height = (out_height + 4) & ~7;
	if(out_width <= attr->out_width && out_height <= attr->out_height)
	{
		attr->crop_width = out_width * scale / YUV_SCALE_DIVIDEND;
		if ((attr->crop_width * YUV_SCALE_DIVIDEND) < (out_width * scale))
			attr->crop_width++;
		attr->crop_height = out_height * scale / YUV_SCALE_DIVIDEND;
		if ((attr->crop_height * YUV_SCALE_DIVIDEND) < (out_height * scale))
			attr->crop_height++;
		attr->out_width = out_width;
		attr->out_height = out_height;
	}
	else
		print_error("ISP CROP out %dx%d > %dx%d", out_width, out_height, attr->out_width, attr->out_height);

	attr->out_stride = attr->out_width;
	//isp_hw_data.capture_uv_offset.uoffset = attr->out_width * attr->out_height;
	print_info("out_size = %dx%d, out_stride = %d", attr->out_width, attr->out_height, attr->out_stride);

	attr->crop_x = (attr->yuv_in_width - attr->crop_width) / 2;
	attr->crop_y = (attr->yuv_in_height - attr->crop_height) / 2;

	/*make sure the crop start is even*/
	attr->crop_x = (attr->crop_x / 2) * 2;
	attr->crop_y = (attr->crop_y / 2) * 2;

	switch(attr->out_fmt) {
		case V4L2_PIX_FMT_NV21:
		case V4L2_PIX_FMT_NV12:
		{
			isp_hw_data.capture_uv_offset.uoffset = attr->out_width * attr->out_height;
			isp_hw_data.capture_uv_offset.voffset = isp_hw_data.capture_uv_offset.uoffset;
			break;
		}
		case V4L2_PIX_FMT_YVU420:
		{
			isp_hw_data.capture_uv_offset.voffset = attr->out_width * attr->out_height;
			isp_hw_data.capture_uv_offset.uoffset = isp_hw_data.capture_uv_offset.voffset + (((attr->out_width / 2) + 0xf) & (~0xf)) * attr->out_height / 2;
			break;
		}
		case V4L2_PIX_FMT_YUV420:
		{
			isp_hw_data.capture_uv_offset.uoffset = attr->out_width * attr->out_height;
			isp_hw_data.capture_uv_offset.voffset = isp_hw_data.capture_uv_offset.uoffset + (((attr->out_width / 2) + 0xf) & (~0xf)) * attr->out_height / 2;
			break;
		}
		default:
			print_error("Invalid isp_data.out_fmt[%08x]", attr->out_fmt);
	}

	print_info("crop_width = %d, crop_height = %d, crop_x = %d, crop_y = %d",
		attr->crop_width, attr->crop_height, attr->crop_x, attr->crop_y);
}

static bool hwa_is_lcd_need_flash(camera_sensor *sensor)
{
	aec_data_t ae_data;
	u32 target_y_low = GETREG8(REG_ISP_TARGET_Y_LOW);
	bool ret = false;

	ae_data.lum = get_current_y();
	ae_data.gain = get_writeback_gain();

	if (ae_is_need_flash(sensor, &ae_data, target_y_low) == true) {
		ret = true;
	}

	print_info("%s(), LCD need flash return: %s", __func__, ret?"true":"false");
	return ret;
}

int hwa_check_lcd_compensation_supported(void)
{
	if (NULL == this_ispdata->sensor) {
		print_error("%s(), isp_data.sensor is null, supported return 0.", __func__);
		return 0;
	}

	if (CAMERA_USE_K3ISP == this_ispdata->sensor->isp_location) {
		print_info("%s(), Front camera uses K3 isp, LCD compensation supported return 1.", __func__);
		return 1;
	}

	print_info("%s(), LCD compensation supported return 0.", __func__);
	return 0;
}

int hwa_check_lcd_compensation_needed(void)
{
	if (NULL == this_ispdata->sensor) {
		print_error("%s(), isp_data.sensor is null.", __func__);
		return 0;
	}

	if (CAMERA_USE_K3ISP != this_ispdata->sensor->isp_location) {
		print_error("%s(), don't use k3 isp, cann't supported LCD compensation.");
		return 0;
	}

	return hwa_is_lcd_need_flash(this_ispdata->sensor);
}

#if 0
void ispv1_hdr_movie_isp_vc_switch(u8 on)
{
	print_debug("enter %s", __func__);

	camera_sensor *sensor = this_ispdata->sensor;

	u16 stats_size = sensor->sensor_hdr_movie.stats_data.stats_h*sensor->sensor_hdr_movie.stats_data.stats_v;
	print_info("stats_size=%d,on=%d",stats_size,on);

	if(on == 1)
	{	
		SETREG16(REG_ROI_MEM_WIDTH_1, stats_size);
		SETREG16(REG_LINE_LENGTH_VC, stats_size >>1);// vc stats data count  
		SETREG16(REG_HEIGHT_VC, 1);// vc stats data height	

		SETREG8(REG_FRAME_CTRL1, FRAME_CTRL1_BIT2|FRAME_CTRL1_BIT0);//FRAME_CTRL1_BIT4 is changed zero when fiweware change to non_zsl_mode
		SETREG8(REG_EN_CTRL_VC, EN_CTRL_VC_BIT7|EN_CTRL_VC_BIT3);
	}
	else
	{
		SETREG8(REG_FRAME_CTRL1, FRAME_CTRL1_BIT4|FRAME_CTRL1_BIT3|FRAME_CTRL1_BIT2);	//FRAME_CTRL1_BIT4 is changed one when fiweware change to zsl_mode
		SETREG8(REG_EN_CTRL_VC, EN_CTRL_VC_BIT6);
	}
}
 /*
  *************************************************************************
  * FunctionName: ispv1_isp_ae_write_mode;
  * Description 	: the function  control that the shutter and gain is writed by sensor or isp,if 1 ,isp write sensor, 0 driver ae will write.
  * Input			: 1 ,isp write sensor shutter and gain; 0 driver ae will write shutter and gain.
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
void ispv1_hdr_movie_isp_ae_write_mode(u8 on)
{
	print_debug("enter %s", __func__);
	SETREG8(REG_ISP_AE_WRITE_MODE,on&0x1); 
}

 /*
  *************************************************************************
  * FunctionName: ispv1_isp_ae_ctrl;
  * Description : the function that turn on or off the switch of isp, if value is 1 , the ae arithmatic of isp is used, otherwise ae of dirver is used.
  * Input			: 1 the isp's ae arithmatic . 0 . the driver of ae.
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
void ispv1_hdr_movie_isp_ae_ctrl_mode(u8 on)
{
	print_debug("enter %s", __func__);
	SETREG8(REG_ISP_AE_CTRL_MODE,on&0x1);/* 1 - AP's ae . 0 - ISP ae. */	
}
#endif
 /*
  *************************************************************************
  * FunctionName: hwa_set_fast_shot_af_mode;
  * Description : set fast shot mode, true:fastshot, false,normalmode
  * Input			: NA;
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
void hwa_set_fast_shot_af_mode(bool fast_shoot)
{
	ispv1_af_set_fast_shoot(fast_shoot);
}
int hwa_set_af_dest_code(u32 dest_code)
{
	int ret = -1;

	if (this_ispdata->sensor->af_enable)
		ret = ispv1_set_vcm_dest_code(dest_code);
	else
		print_error("%s() sensor not support AF", __func__);

	return ret;
}
 /*
  *************************************************************************
  * FunctionName: hwa_get_af_level;
  * Description : the function call ispv1_get_af_code that get the current af code
  * Input			: NA;
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
int hwa_get_af_level(void)
{
     int ret = 0;

     if (this_ispdata->sensor->af_enable)
         ret = ispv1_get_af_code();
     else
	  print_error("%s() sensor not support AF", __func__);

     return ret;
}

 /*
  *************************************************************************
  * FunctionName: hwa_get_af_ramge_min;
  * Description : the function call ispv1_get_af_range_min that get the af min code
  * Input			: NA;
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
int hwa_get_af_ramge_min(void)
{
     int ret = 0;

    if (this_ispdata->sensor->af_enable)
         ret = ispv1_get_af_range_min();
    else
	  print_error("%s() sensor not support AF", __func__);

     return ret;
}

 /*
  *************************************************************************
  * FunctionName: hwa_get_af_ramge_max;
  * Description : the function call ispv1_get_af_range_min that get the af max code
  * Input			: NA;
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
int hwa_get_af_ramge_max(void)
{
     int ret = 0;

     if (this_ispdata->sensor->af_enable)
         ret = ispv1_get_af_range_max();
     else
	  print_error("%s() sensor not support AF", __func__);

     return ret;
}

 /*
  *************************************************************************
  * FunctionName: hwa_get_otp_status;
  * Description : get the sensor's otp status
  * Input          : NA;
  * Output        : NA;
  * ReturnValue: 0 for otp valid, 1 for af invalid, 2 for awb invalid, 3 for total invalid;
  * Other          :
  **************************************************************************
  */
int hwa_get_otp_status(void)
{
    sensor_otp_status  status   = OTP_INVALID;

    if (this_ispdata->sensor->check_otp_status)
    {
        //get otp status info from driver
        this_ispdata->sensor->check_otp_status(&status);
    }
    else//interface not implement
    {
        print_error("%s() sensor check_otp_status in NULL", __func__);
        return OTP_VALID_USER;//for some sensors don't have otp
    }
    print_info("%s() status:%d", __func__, status);
    if (status == OTP_INVALID)
    {
        return OTP_ALL_INVALID_USER;
    }
    else
    {
        return OTP_VALID_USER;
    }
}
 

/********************************** END **********************************************/
