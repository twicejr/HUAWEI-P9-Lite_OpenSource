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

#ifndef MINI_HWA_CAM_TUNE_H_INCLUDED
#define MINI_HWA_CAM_TUNE_H_INCLUDED

#include "hwa_cam_tune_comm.h"

#include <mach/boardid.h>
#include "mini_cam_log.h"
#include "camera.h"


typedef struct mini_hwq_multi_reg_data{
	u32 length;
	u32 *reg;
	u32 *value;
}mini_hwq_multi_reg_data;

typedef struct mini_isp_debug_info_st{
	unsigned char* data;
	unsigned int size;
}mini_isp_debug_info_st;
int mini_hwa_v4l2_ioctl_g_ctrls(struct file *file, void *fh, struct v4l2_control *v4l2_param);
int mini_hwa_v4l2_ioctl_s_ctrls(struct file *file, void *fh, struct v4l2_control *v4l2_param);
int mini_hwa_v4l2_ioctl_g_ext_ctrls(struct v4l2_ext_control **controls, __u32 cmd_id, __u32 cid_idx);
int mini_hwa_v4l2_ioctl_s_ext_ctrls(struct v4l2_ext_control **controls, __u32 cmd_id, __u32 cid_idx);

int mini_hwa_get_multi_isp_reg(mini_hwq_multi_reg_data *seq_data);
int mini_hwa_set_multi_isp_reg(mini_hwq_multi_reg_data *seq_data);
int mini_hwa_get_bracket_iso(int *iso);
int mini_hwa_get_bracket_exp(int *exp);
int mini_hwa_set_cap_iso_ratio_value(int ratio);
int mini_hwa_set_hwscope(void *data);
int mini_hwa_check_lcd_compensation_supported(void);
int mini_hwa_check_lcd_compensation_needed(void);

int mini_hwa_get_expo_max_time_value(struct v4l2_control *v4l2_param);
int mini_hwa_set_expo_max_time_value(int time);
void mini_ispv1_hdr_movie_isp_vc_switch(u8 on);
void mini_ispv1_hdr_movie_isp_ae_write_mode(u8 on);
void mini_ispv1_hdr_movie_isp_ae_ctrl_mode(u8 on);
int mini_hwa_set_af_dest_code(u32 dest_code);

int mini_isp_meta_data_vc_switch(bool on);  //add by zhoutian for mini-ISP meta data

#endif /*HWA_CAM_TUNE_H_INCLUDED */

/********************************* END ***********************************************/
