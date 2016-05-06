#ifndef __HDR_MOVIE_COMM_H__
#define __HDR_MOVIE_COMM_H__

#define _IS_DEBUG_AE	1

#define HDR_STATS_ARRAY_SIZE     				(16)
#define HDR_AE_TARGET_LOW						(40*4) // 8bit *4 = 10bit
#define HDR_AE_TARGET_HIGH					(56*4) // 8bit *4 = 10bit(56*4)
#define HDR_AE_THRESHOLD						(10)
#define REG_ISP_AE_SWITCH                       			0x1d9d0//0x1d9a0
#define REG_ISP_LONG_TIME_H                   			0x1d9d6//0x1d9a1
#define REG_ISP_LONG_TIME_L                    			0x1d9d7
#define REG_ISP_LONG_TIME_DS_H             			0x1d9d8
#define REG_ISP_LONG_TIME_DS_L              		0x1d9d9
#define REG_ISP_LONG_GAIN                        			0x1d9d5//0x1d9a5
#define REG_ISP_SHORT_TIME_WHT_H         		0x1d9d6//0x1d9a6
#define REG_ISP_SHORT_TIME_WHT_L          		0x1d9d7
#define REG_ISP_SHORT_TIME_WHT_DS_H   		0x1d9d8
#define REG_ISP_SHORT_TIME_WHT_DS_L    		0x1d9d9
#define REG_ISP_SHORT_GAIN                       		0x1d9da//0x1d9aa

#define REG_ISP_AE_STATUS                         		0x1d9dc//0x1d9ac

#define REG_ISP_AE_CTRL                             		0x1d9dd//0x1d9ad

#define DEFAULT_SAT_LMT_8                			0x1DF8

#define HDR_ATR_SWITCH_GAIN_DEFAULT			100

#define GAIN_TABLE_LEN 							97

#define HDR_MOVIE_STATS_DIFF_TH 				0//200 ,why modified from 0 to 200 ?
#define HDR_MOVIE_OVER_EXP_TH 				400
#define HDR_MOVIE_FRM_MIN_IN 					60

#define HDR_RBRATIO_THESHOLD					130
#define HDR_ATR_SWITCH_OUTDOOR				250
#define HDR_ATR_INTERVAL_OUTDOOR				40
#define HDR_ATR_SWITCH_INDOOR				200
#define HDR_ATR_INTERVAL_INDOOR				30

#define MAX_LUX_TABLE_SIZE 					257 //16*16+1

typedef enum _hdr_movie_ATR_status{
	ATR_OFF = 0,
	ATR_ON,
}hdr_movie_ATR_status;

typedef enum {
	HDR_MOVIE_OFF  = 0,
	HDR_MOVIE_ON,
} hdr_movie_switch;

typedef enum{
	HDR_MOVIE_NOT_SUPPORT = 0,
	HDR_MOVIE_SUPPORT = 1,
}hdr_movie_func;

typedef enum{
	HDR_AE_AVERAGE_MATH = 0,
	HDR_AE_WEIGHT_MATH,
}ae_arithmatic_method;

typedef struct _ispv1_hdr_movie_ae_ctrl_s
{
	int hdr_ae_ratio ;

	int hdr_atr_switch_gain;
	int ae_arith_method;
	u32 banding_step;
	int  vts;

	int stats_min;
	int stats_ave;
	int stats_max;
	int stats_diff;
}ispv1_hdr_movie_ae_ctrl_s;

typedef struct _hdr_ae_volatile_param
{
	int ae_mean;
	int sensor_vts;
	unsigned short  banding_step;
	unsigned short  hdr_ae_target;
}hdr_ae_volatile_param;

typedef struct _hdr_ae_constant_param
{
	u16 hdr_ae_target;
	u16 hdr_ae_ratio;
	u16 sensor_min_gain;
	u16 sensor_max_gain;
	u16 max_analog_gain;
	u16 default_shutter;
	u16 default_gain;
}hdr_ae_constant_param;

typedef struct _hdr_ae_algo_result
{
	u16 N_shuter;
	u16 N_gain;
	u16 N_short_shuter;
	u16 N_short_gain;
	u16 N_gainBeforeAjust;
	u16 N_wb_lmt;
	u16 N_ae_sat;
	u16 N_digital;
	unsigned short N_mean;
}hdr_ae_algo_result;

typedef struct _stats_hdr_frm
{
	u16 frm_min_h;
	u16 frm_min_l;
	u16 frm_ave_h;
	u16 frm_ave_l;
	u16 frm_max_h;
	u16 frm_max_l;
}stats_hdr_frm;

typedef struct _digital_gain_st
{
	u8 digital_gain_h;
	u8 digital_gain_l;
}digital_gain_st;

typedef struct _stats_info
{
	u16 stats_h;
	u16 stats_v;
}stats_info;

typedef struct _atr_ctrl_point	//for hdr_movie debug
{
	u32 tc_out_noise;
	u32 tc_out_mid;
	u32 tc_out_sat;
	u32 tc_noise_brate;
	u32 tc_mid_brate;
	u32 tc_sat_brate;
	u32 ae_sat;
	u32 wb_lmt;
}atr_ctrl_points;

typedef struct _hdr_info	//for hdr_movie debug
{
	u32	hdr_on;
	u32	atr_on;
	u32	gain;
	u32	expo;
	u32 	short_gain;
	u32	short_expo;
	u32  ae_target;
	u32	avgLux_ave;
	u32	avgLux_weight;
	u32	stats_max;
	u32	stats_diff;
	u32	atr_over_expo_on;
	u32 	gainBeforeAjust;
	u32 	wb_lmt;
	u32	ae_sat;
	u32	N_digital_h;
	u32	N_digital_l;
}hdr_info;

typedef struct _lux_stat_matrix_table	//for hdr_movie debug
{
    u32  size;
    u32  matrix_table[MAX_LUX_TABLE_SIZE];
}lux_stat_matrix_t;//lux_stat_matrix_tbl

typedef struct _sensor_hdr_movie_s {
	u16 ae_hdr_ratio ;
	void(*set_ATR_switch) (int on);
	void(*set_hdr_exposure_gain)(u32 expo_long,u16 gain_global,u32 expo_short,u16 short_gain);
	int (*support_hdr_movie)(void);	
	int (*get_hdr_movie_switch)(void);	
	void(*set_hdr_movie_switch)(hdr_movie_switch on);	
	void(*over_exposure_adjust)(int on,stats_hdr_frm * frm_stats);
	void (*set_lmt_sat)(u32 lmt_value,u32 sat_value);
	int (*get_hdr_movie_ae_param)(hdr_ae_constant_param * hdr_ae_param);
	void(*set_digital_gain)(digital_gain_st * digital_gain);
	void(*get_digital_gain)(digital_gain_st * digital_gain);
	void (*set_awb_gain)(u16 b_gain, u16 gb_gain, u16 gr_gain, u16 r_gain);	
	hdr_info hdrInfo;
	stats_info  stats_data;

	/*the below parmeters  for hdr_movie debug */
	u16 sensor_max_gain;
	u16 sensor_max_analog_gain;
	u16 sensor_min_gain;
	u16 ae_arithmatic_switch_gain;
	u16 stats_diff_threshold;
	u16 stats_max_threshold;
	u16 ae_target_low;
	u16 ae_target_high;
	u16 gain_switch;
	u16 gain_interval;
	u16 gain_switch2;
	u16 gain_interval2;
	atr_ctrl_points  hdr_points;
	lux_stat_matrix_t  lux_matrix;
}sensor_hdr_movie_s;

#endif /*__HDR_MOVIE_AE_H__ */
