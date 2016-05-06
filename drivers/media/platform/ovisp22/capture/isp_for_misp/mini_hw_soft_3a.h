#ifndef __MINI_HW_SOFT_3A_H__
#define __MINI_HW_SOFT_3A_H__

#include "hw_soft_3a_comm.h"

typedef struct _mini_hw_3a_info	//for hdr_movie debug
{

}mini_hw_3a_info;

typedef struct _mini_hw_awb_otp {

	u8 awb_otp_support;
	u8 r_g_high;
	u8 r_g_low;
	u8 b_g_high;
	u8 b_g_low;
	u8 gb_gr_high;
	u8 gb_gr_low;
}mini_hw_awb_otp;

typedef struct _mini_hw_3a_mode_s {

	int (*support_awb_otp)(void);
	mini_hw_awb_otp  awb_otp_value;
}mini_hw_3a_mode;

typedef struct _mini_hw_3a_ae_param_s{

	u16  ae_enable;
	u16  ae_hist_shift;
	u16  ae_mean_shift;
	u16  ae_win_top;
	u16  ae_win_left;
	u16  ae_win_height;
	u16  ae_win_width;
	u16  ae_win_model;
}mini_hw_3a_ae_param;

typedef struct _mini_hw_3a_af_param_s{

	u16  af_enable;
	u16  af_shift;
	u16  af_win_top;
	u16  af_win_left;
	u16  af_win_height;
	u16  af_win_width;
	u16  af_win_vgap;
	u16  af_win_hgap;
	u16  af_win_num;
	u16  af_filter_shift;
	u16  af_odd_even_frame;
}mini_hw_3a_af_param;

typedef struct _mini_hw_3a_param_s{

	u16  blc_enable;
	u32 data_count;
	mini_hw_3a_ae_param  ae_param;
	mini_hw_3a_af_param   af_param;
}mini_hw_3a_param;

void mini_ispv1_hw_3a_switch(u8 on);

int mini_ispv1_set_hw_3a_param(mini_hw_3a_param* data_3a);

#endif /*__HW_SOFT_3A_H__ */
