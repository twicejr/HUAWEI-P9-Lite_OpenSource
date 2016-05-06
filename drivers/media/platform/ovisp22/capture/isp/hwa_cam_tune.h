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

#ifndef HWA_CAM_TUNE_H_INCLUDED
#define HWA_CAM_TUNE_H_INCLUDED

#include "hwa_cam_tune_comm.h"

#include "cam_log.h"
#include "../camera.h"

int hwa_v4l2_ioctl_g_ctrls(struct file *file, void *fh, struct v4l2_control *v4l2_param);
int hwa_v4l2_ioctl_s_ctrls(struct file *file, void *fh, struct v4l2_control *v4l2_param);
int hwa_v4l2_ioctl_g_ext_ctrls(struct v4l2_ext_control **controls, __u32 cmd_id, __u32 cid_idx);
int hwa_v4l2_ioctl_s_ext_ctrls(struct v4l2_ext_control **controls, __u32 cmd_id, __u32 cid_idx);

int hwa_get_multi_isp_reg(hwq_multi_reg_data *seq_data);
int hwa_set_multi_isp_reg(hwq_multi_reg_data *seq_data);
int hwa_get_bracket_iso(int *iso);
int hwa_get_bracket_exp(int *exp);
int hwa_set_cap_iso_ratio_value(int ratio);
int hwa_set_hwscope(void *data);
int hwa_check_lcd_compensation_supported(void);
int hwa_check_lcd_compensation_needed(void);

#if 0
void ispv1_hdr_movie_isp_vc_switch(u8 on);
void ispv1_hdr_movie_isp_ae_write_mode(u8 on);
void ispv1_hdr_movie_isp_ae_ctrl_mode(u8 on);
#endif
int hwa_set_af_dest_code(u32 dest_code);
void hwa_set_fast_shot_af_mode(bool fast_shoot);
int hwa_get_af_level(void);
int hwa_get_af_ramge_min(void);
int hwa_get_af_ramge_max(void);
int k3_isp_get_algorithm_iso(void);
int hwa_get_otp_status(void);
#endif /*HWA_CAM_TUNE_H_INCLUDED */

/********************************* END ***********************************************/
