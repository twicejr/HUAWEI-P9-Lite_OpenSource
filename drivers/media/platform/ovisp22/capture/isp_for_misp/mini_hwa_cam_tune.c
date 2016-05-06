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
#include "mini_cam_log.h"
#include "mini_k3_isp.h"
#include "mini_k3_ispv1.h"
#include "mini_k3_ispv1_afae.h"
#include "../camera.h"
#include "mini_hwa_cam_tune.h"
#include "mini_hwa_cam_tune_common.h"

#include <media/v4l2-common.h>
#include <linux/fb.h>
#include "mini_k3_v4l2_capture.h"
#include "mini_sensor_common.h"
#include "mini_cam_dbg.h"
#include "mini_cam_util.h"
#include "mini_k3_isp_io.h"
#include "camera_agent.h"
extern mini_k3_isp_data *mini_this_ispdata;

int mini_hwa_v4l2_ioctl_g_ctrls(struct file *file, void *fh, struct v4l2_control *v4l2_param)
{
	int ret = 0;
	return ret;
}
int mini_hwa_v4l2_ioctl_s_ctrls(struct file *file, void *fh, struct v4l2_control *v4l2_param)
{
	int ret = 0;
	switch(v4l2_param->id)
	{
		case V4L2_CID_SET_VCM_DEST_CODE:
		{
			ret = mini_hwa_set_af_dest_code(v4l2_param->value);
			break;
		}
		case V4L2_CID_SET_META_DATA_VC_SWITCH:
		{
			ret = mini_isp_meta_data_vc_switch(v4l2_param->value);
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

int mini_ispv1_get_extra_coff(extra_coff *extra_data)
{
    extra_data->mean_y   = GETREG8(0x1c758);
    extra_data->motion_x = (s8)GETREG8(0x1cc7c);
    extra_data->motion_y = (s8)GETREG8(0x1cc7d);

    extra_data->focal_length = mini_ispv1_get_focus_distance();
    extra_data->af_window_change = GETREG8(0x1cdd2);

    return 0;
}

int mini_ispv1_get_ae_coff(ae_coff *ae_data)
{
    GETREG16(0x1c158, ae_data->exposure_max);
    GETREG16(0x1c15c, ae_data->exposure_min);
    GETREG16(0x1c150, ae_data->gain_max);
    GETREG16(0x1c154, ae_data->gain_min);
    ae_data->luma_target_high = GETREG8(REG_ISP_TARGET_Y_HIGH);
    ae_data->luma_target_low = GETREG8(REG_ISP_TARGET_Y_LOW);
    ae_data->exposure = get_writeback_expo() >> 4;
    ae_data->exposure_time = mini_ispv1_get_exposure_time();
    ae_data->gain = get_writeback_gain();
    ae_data->iso = mini_ispv1_get_actual_iso();

    return 0;
}

int mini_k3_isp_get_extra_coff(extra_coff *extra_data)
{
    int ret = 0;

    if (mini_this_ispdata->sensor->isp_location == CAMERA_USE_K3ISP)
        ret = mini_ispv1_get_extra_coff(extra_data);

    return ret;
}

int mini_k3_isp_get_ae_coff(ae_coff *ae_data)
{
    int ret = 0;

    if (mini_this_ispdata->sensor->isp_location == CAMERA_USE_K3ISP)
        ret = mini_ispv1_get_ae_coff(ae_data);

    return ret;
}


int mini_hwa_v4l2_ioctl_g_ext_ctrls(struct v4l2_ext_control **controls, __u32 cmd_id, __u32 cid_idx)
{
	int ret = 0;

	switch(cmd_id)
	{
		case V4L2_CID_GET_MULTI_ISP_REG:
		{
			mini_hwq_multi_reg_data *seq_data = NULL;
			seq_data = (mini_hwq_multi_reg_data *)(((*controls)[cid_idx]).string);

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

			if (NULL == mini_this_ispdata) {
				print_error("mini_this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(mini_this_ispdata->sensor->isp_location == CAMERA_USE_K3ISP){
				ret = mini_hwa_get_multi_isp_reg(seq_data);
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

			if (NULL == mini_this_ispdata) {
				print_error("mini_this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == mini_this_ispdata->sensor->isp_location){
				ret = mini_hwa_get_bracket_iso(iso);
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

			if (NULL == mini_this_ispdata) {
				print_error("mini_this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == mini_this_ispdata->sensor->isp_location){
				ret = mini_hwa_get_bracket_exp(exp);
			}
			break;
		}
		case V4L2_CID_GET_AE_COFF:
		{
			int data_size = sizeof(ae_coff);
                     ae_coff *ae_data;
			void *data_buf = kmalloc(data_size, GFP_KERNEL);
			if (!data_buf) {
				ret = -ENOMEM;
				print_error("fail to allocate buffer for ext controls");
				goto out;
			}
			if(copy_from_user(data_buf, ((*controls)[cid_idx]).string, data_size)){
                            ret =  -EFAULT;
                            goto out;
                     }
			ae_data = data_buf;
			ret = mini_k3_isp_get_ae_coff(ae_data);

			if(copy_to_user(((*controls)[cid_idx]).string, data_buf, data_size)){
                            ret =  -EFAULT;
                            goto out;
                     }
			kfree(data_buf);
			break;
		}
		case V4L2_CID_GET_EXTRA_COFF:
		{
			int data_size = sizeof(extra_coff);
			void *data_buf = kmalloc(data_size, GFP_KERNEL);
                     extra_coff *extra_data;
			if (!data_buf) {
				ret = -EINVAL;
				print_error("fail to allocate buffer for ext controls");
				goto out;
			}
			if(copy_from_user(data_buf, ((*controls)[cid_idx]).string, data_size)){
                            ret =  -EFAULT;
                            goto out;                
                     }
			extra_data = data_buf;
			ret = mini_k3_isp_get_extra_coff(extra_data);

			if(copy_to_user(((*controls)[cid_idx]).string, data_buf, data_size)){
                            ret =  -EFAULT;
                            goto out;
                     }
			kfree(data_buf);
			break;
		}
		case V4L2_CID_GET_LCD_COMPENSATION_SUPPORTED:
		{
			((*controls)[cid_idx]).value = mini_hwa_check_lcd_compensation_supported();
			break;
		}
		case V4L2_CID_GET_LCD_COMPENSATION_NEEDED:
		{
			((*controls)[cid_idx]).value = mini_hwa_check_lcd_compensation_needed();
			break;
		}
		case V4L2_CID_GET_HDR_MOVIE_SUPPORTED:
		{
			int *support_hdr_movie= NULL;
			support_hdr_movie = (int *)(((*controls)[cid_idx]).string);

			if(NULL == support_hdr_movie){
				ret = -EINVAL;
				print_error("support_hdr_movie is NULL");
				goto out;
			}

			if (NULL == mini_this_ispdata) {
				print_error("mini_this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == mini_this_ispdata->sensor->isp_location){
				if (mini_this_ispdata->sensor->sensor_hdr_movie.support_hdr_movie) {
					*support_hdr_movie = mini_this_ispdata->sensor->sensor_hdr_movie.support_hdr_movie();
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
				stats_data->stats_h = mini_this_ispdata->sensor->sensor_hdr_movie.stats_data.stats_h;
				stats_data->stats_v = mini_this_ispdata->sensor->sensor_hdr_movie.stats_data.stats_v;;
			}
			break;
		}
		case V4L2_CID_GET_AWB_OTP_INFO:
		{
			int support_awb_otp= AWB_OTP_NOT_SUPPORT;
			mini_hw_awb_otp *awb_otp = (mini_hw_awb_otp *)(((*controls)[cid_idx]).string);

			if (NULL == awb_otp || NULL == mini_this_ispdata) {
				print_error("awb_otp or mini_this_ispdata  is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == mini_this_ispdata->sensor->isp_location){
				if (mini_this_ispdata->sensor->sensor_hw_3a.support_awb_otp) {
					support_awb_otp = mini_this_ispdata->sensor->sensor_hw_3a.support_awb_otp();
				}
			}

			if(NULL != awb_otp && AWB_OTP_SUPPORT == support_awb_otp){
				awb_otp->awb_otp_support = AWB_OTP_SUPPORT;
				awb_otp->r_g_high = mini_this_ispdata->sensor->sensor_hw_3a.awb_otp_value.r_g_high;
				awb_otp->r_g_low = mini_this_ispdata->sensor->sensor_hw_3a.awb_otp_value.r_g_low;
				awb_otp->b_g_high = mini_this_ispdata->sensor->sensor_hw_3a.awb_otp_value.b_g_high;
				awb_otp->b_g_low = mini_this_ispdata->sensor->sensor_hw_3a.awb_otp_value.b_g_low;
				awb_otp->gb_gr_high = mini_this_ispdata->sensor->sensor_hw_3a.awb_otp_value.gb_gr_high;
				awb_otp->gb_gr_low = mini_this_ispdata->sensor->sensor_hw_3a.awb_otp_value.gb_gr_low;
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
		case V4L2_CID_GET_MINI_ISP_DEBUG_INFO:
		{
			mini_isp_debug_info_st *debug_info = (mini_isp_debug_info_st *)(((*controls)[cid_idx]).string);
                     int data_size;
			if(NULL == debug_info || NULL == debug_info->data) {
				print_error("debug_info or debug_info->mData is NULL");
				ret = -EINVAL;
				goto out;
			}
			if(NULL == mini_this_ispdata) {
				print_error("mini_this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}
			if(false == mini_this_ispdata->is_using_mini_isp) {
				print_error("this product don't support mini-isp");
				ret = -EINVAL;
				goto out;
			}
			if(false == mini_this_ispdata->meta_data) {
				print_error("meta_data is NULL");
				ret = -EINVAL;
				goto out;
			}

			data_size = sizeof(mini_this_ispdata->meta_data->data.debug_info);
			if(data_size > debug_info->size) {
				print_error("debug_info malloc size=%d in HAL is not enough!", debug_info->size);
				ret = -EINVAL;
				goto out;
			}
			if(copy_to_user(debug_info->data, mini_this_ispdata->meta_data->data.debug_info, data_size)){
                            ret =  -EFAULT;
                            goto out;
                     }
			debug_info->size = data_size;

			break;
		}
		default:
			break;
	}

out:
	return ret;
}

int mini_hwa_v4l2_ioctl_s_ext_ctrls(struct v4l2_ext_control **controls, __u32 cmd_id, __u32 cid_idx)
{
	int ret = 0;
	int func_ret = 0;
	
	switch(cmd_id)
	{
		case V4L2_CID_SET_MULTI_ISP_REG:
		{
			mini_hwq_multi_reg_data *seq_data = NULL;
			seq_data = (mini_hwq_multi_reg_data *)(((*controls)[cid_idx]).string);

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

			if (NULL == mini_this_ispdata) {
				print_error("mini_this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == mini_this_ispdata->sensor->isp_location){
				ret = mini_hwa_set_multi_isp_reg(seq_data);
			}

			break;
		}
		case V4L2_CID_SET_CAP_ISO_RATIO_VALUE:
		{
			int ratio = ((*controls)[cid_idx]).value;
			if(0 == ratio) {
				ret = -EINVAL;
				goto out;
			}
			ret = mini_hwa_set_cap_iso_ratio_value(ratio);

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

			if (NULL == mini_this_ispdata) {
				print_error("mini_this_ispdata is NULL");
				ret = -EINVAL;
				goto out;
			}

			if(CAMERA_USE_K3ISP == mini_this_ispdata->sensor->isp_location){
				ret = mini_hwa_set_hwscope(hwscope_data);
			}

			break;
		}
		case V4L2_CID_SET_HDR_MOVIE_MODE:
		{
			int hdr_movie_on =  ((*controls)[cid_idx]).value;
			if (!mini_this_ispdata->sensor->sensor_hdr_movie.set_hdr_movie_switch)
			{
				ret = -EINVAL;	
				goto  out;
			}
            if(hdr_movie_on != mini_this_ispdata->sensor->sensor_hdr_movie.get_hdr_movie_switch())
			{
				mini_this_ispdata->sensor->sensor_hdr_movie.set_hdr_movie_switch(hdr_movie_on);

				if(1 == hdr_movie_on ){
					mini_ispv1_hdr_movie_isp_vc_switch(1);
					mini_ispv1_hdr_movie_isp_ae_write_mode(0);/* 0 - AP write shutter&gain */
					mini_ispv1_hdr_movie_isp_ae_ctrl_mode(1);/* 1 - AP's ae */
				}else{
					mini_ispv1_hdr_movie_isp_vc_switch(0);
					mini_ispv1_hdr_movie_isp_ae_write_mode(1);/* 1 - ISP write sensor shutter&gain */
					mini_ispv1_hdr_movie_isp_ae_ctrl_mode(0);/* 0 - ISP ae */
				}
			}
			break;
		}
		case V4L2_CID_SET_HDR_MOVIE_AE_RESULT:
		{
			int data_size = sizeof(hdr_ae_algo_result);
			void *data_buf = kmalloc(data_size, GFP_KERNEL);
                     hdr_ae_algo_result *ae_result;
                     
			if (!data_buf) {
				ret = -ENOMEM;
				print_error("fail to allocate buffer for ext controls");
				goto  out;
			}
			if(copy_from_user(data_buf, (((*controls)[cid_idx]).string), data_size)){
                            ret = -EFAULT;
                            goto out;
            }
			ae_result = data_buf;
			func_ret = ispv1_set_hdr_movie_shutter_gain_to_sensor(ae_result);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			kfree(data_buf);
			break;
		}
		case V4L2_CID_SET_MINI_ISP_FACE_INFO:
		{
			face_win_info_s *face_info= NULL;
                     face_win_info_s *face_info_s;
			mini_focus_win_info_s face_area;
			int data_size = sizeof(face_win_info_s);
			int i    = 0;
			face_info = kmalloc(data_size,GFP_KERNEL);

			if (!face_info) {
				ret = -ENOMEM;
				print_error("fail to allocate buffer for ext controls");
				goto  out;
			}
			if(copy_from_user(face_info, (((*controls)[cid_idx]).string), data_size)){
                            ret = -EFAULT;
                            goto out;
                     }
			face_info_s = face_info;

			for(;i<face_info_s->face_number;++i){
				ret = mini_ispv1_face_yuvrect_to_rawrect(&(face_info_s->face_area[i]));
				if(ret < 0){
					ret = -EINVAL;
					print_error("fail to transfer face yuvrect to rawrect [index=%d]",i);
				}
			}
			face_area.left = face_info_s->face_area[face_info_s->index_max_face].left;
			face_area.top = face_info_s->face_area[face_info_s->index_max_face].top;
			face_area.width= face_info_s->face_area[face_info_s->index_max_face].width;
			face_area.height = face_info_s->face_area[face_info_s->index_max_face].height;
			camera_agent_set_focusarea(&face_area);
			camera_agent_set_facearea(face_info_s);
			kfree(face_info_s);
			break;
		}
		default:
			break;
	}

out:
	return ret;
}

int mini_hwa_get_bracket_iso(int *iso)
{
	u16 gain;
	int index;
	bool summary;
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;

	index = sensor->capture_frmsize_index;
	summary = sensor->frmsize_list[index].summary;

	GETREG16(ISP_FIRST_FRAME_GAIN, gain);
	iso[0] = mini_ispv1_gain2iso(gain, summary);

	GETREG16(ISP_SECOND_FRAME_GAIN, gain);
	iso[1] = mini_ispv1_gain2iso(gain, summary);

	GETREG16(ISP_THIRD_FRAME_GAIN, gain);
	iso[2] = mini_ispv1_gain2iso(gain, summary);

	print_debug("iso [%d] [%d] [%d]\n",iso[0],iso[1],iso[2]);

	return 0;
}

int mini_hwa_get_bracket_exp(int *exp)
{
	u32 expo, fps, vts;
	int index;
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	index = sensor->capture_frmsize_index;

	fps = sensor->frmsize_list[index].fps;
	vts = sensor->frmsize_list[index].vts;

	GETREG32(ISP_FIRST_FRAME_EXPOSURE, expo);
	expo >>= 4;
	if (0 == expo)
	{
		print_info("mini_hwa_get_bracket_exp exp[0]=0, reset expo to 0x22b00.");
		expo = (0x22b00 >> 4);
	}
	exp[0] = ispv1_expo_line2time(expo, fps, vts);

	GETREG32(ISP_SECOND_FRAME_EXPOSURE, expo);
	expo >>= 4;
	if (0 == expo)
	{
		print_info("mini_hwa_get_bracket_exp exp[1]=0, reset expo to 0x22b00.");
		expo = (0x22b00 >> 4);
	}
	exp[1] = ispv1_expo_line2time(expo, fps, vts);

	GETREG32(ISP_THIRD_FRAME_EXPOSURE, expo);
	expo >>= 4;
	if (0 == expo)
	{
		print_info("mini_hwa_get_bracket_exp exp[2]=0, reset expo to 0x22b00.");
		expo = (0x22b00 >> 4);
	}
	exp[2] = ispv1_expo_line2time(expo, fps, vts);

	print_debug("exp [%d] [%d] [%d]\n",exp[0],exp[1],exp[2]);

	return 0;
}
int mini_hwa_get_multi_isp_reg(mini_hwq_multi_reg_data *seq_data)
{
	int i = 0;
	int length = seq_data->length;
	int *reg = seq_data->reg;
	int *value = seq_data->value;

	for(i = 0; i < length; i++){
		value[i] = GETREG8(reg[i]);
		print_debug("mini_hwa_get_multi_isp_reg i = %d, get reg[0x%x] = 0x%x", i, reg[i], value[i]);
	}

	return 0;
}

int mini_hwa_set_multi_isp_reg(mini_hwq_multi_reg_data *seq_data)
{
	int i;
	int length = seq_data->length;
	int *reg = seq_data->reg;
	int *value = seq_data->value;

	for(i = 0; i < length; i++){
		SETREG8(reg[i], value[i]);
		print_debug("mini_hwa_set_multi_isp_reg i = %d, set reg[0x%x] = 0x%x", i, reg[i], value[i]);
	}

	return 0;
}


int mini_hwa_set_cap_iso_ratio_value(int ratio)
{
	int max_iso, min_iso;
	int max_gain, min_gain;
	mini_camera_sensor *sensor;
	mini_ae_params_s *this_ae;

	print_debug("enter %s", __func__);

	if (NULL == mini_this_ispdata) {
	print_info("mini_this_ispdata is NULL");
		return -1;
	}
	sensor = mini_this_ispdata->sensor;
	this_ae = &sensor->effect->ae_param;
	max_iso = this_ae->iso_max;
	min_iso = this_ae->iso_min;
	max_gain = max_iso * 0x10 / 100;
	min_gain = min_iso * 0x10 / 100;

	if( (sensor->frmsize_list[sensor->preview_frmsize_index].summary == false)&&(true == sensor->support_summary)){
		max_gain = max_gain * 2;
	}
	max_gain = max_gain*ratio;
	print_debug("%s max_gain : %d", __func__,max_gain);
	SETREG8(REG_ISP_MAX_GAIN, (max_gain & 0xff00) >> 8);
	SETREG8(REG_ISP_MAX_GAIN + 1, max_gain & 0xff);
	SETREG8(REG_ISP_MIN_GAIN, (min_gain & 0xff00) >> 8);
	SETREG8(REG_ISP_MIN_GAIN + 1, min_gain & 0xff);
	sensor->min_gain = min_gain;
	sensor->max_gain = max_gain;
	return 0;
}

hwa_hwscope_ctl hwa_hwscope;

int mini_hwa_set_hwscope(void *data)
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
	mini_pic_attr_t *attr = &mini_this_ispdata->pic_attr[state];
       int out_width;
       int out_height;
              
	print_info("%s, zoom=%d, in_width=%d, in_height=%d",
			__func__, mini_this_ispdata->zoom, *in_width, *in_height);

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

	out_width = attr->out_width * 10 / (mini_this_ispdata->zoom + 10) + hwa_hwscope.border * 2;
	out_width = (out_width + 16) & ~31;
	out_height = attr->out_height * 10 / (mini_this_ispdata->zoom + 10) + hwa_hwscope.border * 2;
	out_height = (out_height + 4) & ~7;

	if(out_width <= attr->out_width && out_height <= attr->out_height)
	{
		attr->crop_width = out_width * attr->in_width / attr->out_width;
		attr->crop_height = out_height * attr->in_width / attr->out_width;
		attr->out_width = out_width;
		attr->out_height = out_height;
	}
	else
		print_error("ISP CROP out %dx%d > %dx%d", out_width, out_height, attr->out_width, attr->out_height);

	attr->out_stride = attr->out_width;
	//mini_isp_hw_data.capture_uv_offset.uoffset = attr->out_width * attr->out_height;
	print_info("out_size = %dx%d, out_stride = %d", attr->out_width, attr->out_height, attr->out_stride);

	if (mini_this_ispdata->zoom != 0) {
		if (attr->crop_width & 0x03)
			attr->crop_width = (attr->crop_width & ~0x03) + 4;
		if (attr->crop_height & 0x03)
			attr->crop_height = (attr->crop_height & ~0x03) + 4;
	}
	attr->crop_x = (attr->yuv_in_width - attr->crop_width) / 2;
	attr->crop_y = (attr->yuv_in_height - attr->crop_height) / 2;

	/*make sure the crop start is even*/
	attr->crop_x = (attr->crop_x / 2) * 2;
	attr->crop_y = (attr->crop_y / 2) * 2;

	switch(attr->out_fmt) {
		case V4L2_PIX_FMT_NV21:
		case V4L2_PIX_FMT_NV12:
		{
			mini_isp_hw_data.capture_uv_offset.uoffset = attr->out_width * attr->out_height;
			mini_isp_hw_data.capture_uv_offset.voffset = mini_isp_hw_data.capture_uv_offset.uoffset;
			break;
		}
		case V4L2_PIX_FMT_YVU420:
		{
			mini_isp_hw_data.capture_uv_offset.voffset = attr->out_width * attr->out_height;
			mini_isp_hw_data.capture_uv_offset.uoffset = mini_isp_hw_data.capture_uv_offset.voffset + (((attr->out_width / 2) + 0xf) & (~0xf)) * attr->out_height / 2;
			break;
		}
		case V4L2_PIX_FMT_YUV420:
		{
			mini_isp_hw_data.capture_uv_offset.uoffset = attr->out_width * attr->out_height;
			mini_isp_hw_data.capture_uv_offset.voffset = mini_isp_hw_data.capture_uv_offset.uoffset + (((attr->out_width / 2) + 0xf) & (~0xf)) * attr->out_height / 2;
			break;
		}
		default:
			print_error("Invalid isp_data.out_fmt[%08x]", attr->out_fmt);
	}

	print_info("crop_width = %d, crop_height = %d, crop_x = %d, crop_y = %d",
		attr->crop_width, attr->crop_height, attr->crop_x, attr->crop_y);
}

static bool hwa_is_lcd_need_flash(mini_camera_sensor *sensor)
{
	mini_aec_data_t ae_data;
	u32 target_y_low = GETREG8(REG_ISP_TARGET_Y_LOW);
	bool ret = false;

	ae_data.lum = get_current_y();
	ae_data.gain = get_writeback_gain();

	if (mini_ae_is_need_flash(sensor, &ae_data, target_y_low) == true) {
		ret = true;
	}

	print_info("%s(), LCD need flash return: %s", __func__, ret?"true":"false");
	return ret;
}

int mini_hwa_check_lcd_compensation_supported(void)
{
	int ret = 0;

	if (NULL != mini_this_ispdata->sensor) {
		ret = mini_this_ispdata->sensor->lcd_compensation_supported;
	}

	print_info("%s(), LCD compensation supported: %d", __func__, ret);
	return ret;
}

int mini_hwa_check_lcd_compensation_needed(void)
{
	if (NULL == mini_this_ispdata->sensor) {
		print_error("%s(), isp_data.sensor is null.", __func__);
		return 0;
	}

	if (!mini_this_ispdata->sensor->lcd_compensation_supported) {
		print_error("%s(), don't support LCD compensation.", __func__);
		return 0;
	}

	if (CAMERA_USE_K3ISP != mini_this_ispdata->sensor->isp_location) {
		print_error("%s(), don't use k3 isp, cann't supported LCD compensation.");
		return 0;
	}

	return hwa_is_lcd_need_flash(mini_this_ispdata->sensor);
}

void mini_ispv1_hdr_movie_isp_vc_switch(u8 on)
{
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;

	u16 stats_size = sensor->sensor_hdr_movie.stats_data.stats_h*sensor->sensor_hdr_movie.stats_data.stats_v;

	print_debug("enter %s", __func__);
	print_info("stats_size=%d,on=%d",stats_size,on);

	if(on == 1)
	{	
		SETREG16(REG_ROI_MEM_WIDTH_1, stats_size);
		SETREG8(REG_FRAME_CTRL1, 0x05);
		SETREG16(REG_LINE_LENGTH_VC, stats_size >>1);// vc stats data count  
		SETREG16(REG_HEIGHT_VC, 1);// vc stats data height	
		SETREG8(REG_EN_CTRL_VC, 0x88);
	}
	else
	{
		SETREG8(REG_EN_CTRL_VC, 0x0);
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
void mini_ispv1_hdr_movie_isp_ae_write_mode(u8 on)
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
void mini_ispv1_hdr_movie_isp_ae_ctrl_mode(u8 on)
{
	print_debug("enter %s", __func__);
	SETREG8(REG_ISP_AE_CTRL_MODE,on&0x1);/* 1 - AP's ae . 0 - ISP ae. */	
}

int mini_hwa_set_af_dest_code(u32 dest_code)
{
	int ret = -1;

	if (mini_this_ispdata->sensor->af_enable)
		ret = mini_ispv1_set_vcm_dest_code(dest_code);
	else
		print_error("%s() sensor not support AF", __func__);

	return ret;
}

extern u32 misp_vc_control;
int mini_isp_meta_data_vc_switch(bool on)
{
	u16 meta_data_raw_size = sizeof(meta_data_st) * 2;

	print_info("enter %s, on=%d", __func__, on);

	if(NULL == mini_this_ispdata->meta_data || false == mini_this_ispdata->is_using_mini_isp) {
		print_error("%s error, don't support mini-isp or meta_data is NULL", __func__);
		return -EINVAL;
	}

	if(misp_vc_control==0)
		return 0;

	if(on == true) {
		SETREG16(REG_ROI_MEM_WIDTH_1, meta_data_raw_size);
		SETREG8(REG_FRAME_CTRL1, 0x05);
		SETREG16(REG_LINE_LENGTH_VC, meta_data_raw_size / 2);// vc stats data count
		SETREG16(REG_HEIGHT_VC, 1);// vc stats data height
		SETREG8(REG_EN_CTRL_VC, 0x88); 
	} else {
		SETREG8(REG_EN_CTRL_VC, 0x0);
	}

	mini_this_ispdata->meta_data_vc_on = on; 

	return 0;
}

/********************************** END **********************************************/
