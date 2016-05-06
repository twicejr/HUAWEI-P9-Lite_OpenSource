
#include <asm/io.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/stat.h>
#include <linux/uaccess.h>
#include "mini_k3_isp.h"
#include "mini_k3_ispv1.h"
#include "mini_cam_log.h"
#include <linux/workqueue.h>

#include "mini_sensor_common.h"
//#define HDR_MOVIE_DEBUG_MODE
extern mini_k3_isp_data *mini_this_ispdata;

unsigned short gain_time_table[GAIN_TABLE_LEN] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
66, 67, 68, 69, 71, 72, 73, 74, 76, 77,
79, 80, 82, 84, 85, 87, 89, 91, 93, 95,
98, 100, 102, 105, 108, 111, 114, 117,
120, 124, 128, 132, 137, 141, 146, 152,
158, 164, 171,178, 186, 195, 205, 216,
228, 241, 256};

unsigned short gain_db_table[GAIN_TABLE_LEN] = {7, 21, 34, 45, 56, 65, 73, 81, 88, 95,
101, 107, 112, 117, 121, 125, 129, 133, 137, 140,
143, 146, 149, 152, 154, 157, 159, 161, 163, 165,
167, 169, 171, 173, 174, 176, 177, 179, 180, 182,
183, 184, 185, 187, 188, 189, 190, 191, 192, 193,
194, 195, 196, 197, 198, 199, 200, 201, 202, 203,
204, 205, 206, 207, 208, 209, 210, 211, 212, 213,
214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
224, 225, 226, 227, 228, 229, 230, 231, 232, 233,
234, 235, 236, 237, 238, 239, 240};

ispv1_hdr_movie_ae_ctrl_s * hdr_movie_ae_ctrl;

#ifdef HDR_MOVIE_DEBUG_MODE
static int ispv1_load_sensor_setting(mini_camera_sensor *sensor,char *filename);//for hdr_movie debug
#endif
 void hdr_movie_stats_param_init(void)
 {
	hdr_movie_ae_ctrl->stats_min	= 8192;
	hdr_movie_ae_ctrl->stats_ave	= 0;
	hdr_movie_ae_ctrl->stats_max	= 0;
	hdr_movie_ae_ctrl->stats_diff = 0;
 }

 /*
  *************************************************************************
  * FunctionName: ispv1_hdr_parameter_init;
  * Description : the function that init struct 's number parameter.
  * Input			: NA
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
void ispv1_hdr_parameter_init(void)
{
	mini_camera_sensor * sensor = mini_this_ispdata->sensor;
	print_debug("enter %s",__func__);
	assert(mini_this_ispdata);
	assert(sensor);
	if(NULL == sensor) {
		return;
	}
	hdr_movie_ae_ctrl->hdr_ae_ratio 	= sensor->sensor_hdr_movie.ae_hdr_ratio;

	hdr_movie_ae_ctrl->ae_arith_method = HDR_AE_AVERAGE_MATH;

	hdr_movie_ae_ctrl->vts = sensor->frmsize_list[sensor->preview_frmsize_index].vts - 4;

	sensor->sensor_hdr_movie.hdrInfo.atr_on = ATR_ON;

	hdr_movie_stats_param_init();
}

 /*
  *************************************************************************
  * FunctionName: ispv1_hdr_ae_init;
  * Description : the function that init parameter for hdr movie
  * Input			: NA
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
int  ispv1_hdr_ae_init(void)
{
	hdr_movie_ae_ctrl = kmalloc(sizeof(ispv1_hdr_movie_ae_ctrl_s), GFP_KERNEL);

	if (!hdr_movie_ae_ctrl) {
		print_error("malloc is failed in %s function at line#%d\n", __func__, __LINE__);
		return -ENOMEM;
	}
	memset(hdr_movie_ae_ctrl, 0, sizeof(ispv1_hdr_movie_ae_ctrl_s));
	ispv1_hdr_parameter_init();
	return 0;
}

  /*
  *************************************************************************
  * FunctionName: ispv1_hdr_ae_exit;
  * Description : the function that is exit for hdr movie free resource.
  * Input			: NA
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
int ispv1_hdr_ae_exit(void)
{
       print_debug("enter %s", __func__);
	if(NULL != hdr_movie_ae_ctrl)
	{
		kfree(hdr_movie_ae_ctrl);
		hdr_movie_ae_ctrl = NULL;
	}
	return 0;
}
 
 /*
  *************************************************************************
  * FunctionName: ispv1_hdr_banding_step_change;
  * Description 	: the function that set banding step for hdr movie.
  * Input			: banding parameter{	CAMERA_ANTI_BANDING_50Hz,CAMERA_ANTI_BANDING_60Hz,}
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
u32 ispv1_hdr_banding_step_change(camera_anti_banding banding)
{
	u32 	hdr_banding_step = 0;
	mini_camera_sensor * sensor = mini_this_ispdata->sensor;
	if(_IS_DEBUG_AE)
	print_info("%s, anti-banding:%#x", __func__, banding);
	switch (banding) {
	case CAMERA_ANTI_BANDING_50Hz:
		hdr_banding_step	= sensor->frmsize_list[sensor->preview_frmsize_index].banding_step_50hz;
		break;
	case CAMERA_ANTI_BANDING_60Hz:
		hdr_banding_step  = sensor->frmsize_list[sensor->preview_frmsize_index].banding_step_60hz;
		break;
	default:
		hdr_banding_step	= sensor->frmsize_list[sensor->preview_frmsize_index].banding_step_50hz;
		print_error("%s, Unsupport anti-banding:%#x", __func__, banding);
		break;
	}
	return hdr_banding_step;
}

 /*
  *************************************************************************
  * FunctionName: 	hdr_gain_db_to_time;
  * Description 	: the function  switch gain db to gain time according to gain_time table and gain db table.
  * Input			: gain db value
  * Output		: gain time value;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
int hdr_gain_db_to_time(int gain_db)
{
	int gain_time = 0;
	int i;
	 for(i=0; i<GAIN_TABLE_LEN; i++)
	{
		if(gain_db<=gain_db_table[i])
		{
			if(i==0)
			{
			    gain_time = gain_time_table[0];
			}
			else
			{
				if((gain_db_table[i] - gain_db)>(gain_db - gain_db_table[i-1]))
				    gain_time = gain_time_table[i-1];
				       else
				    gain_time = gain_time_table[i];
			}
	   	break;
		}
	}

	 return gain_time;
}
 
int  ispv1_get_hdr_movie_ae_init_param(hdr_ae_constant_param * hdr_ae_param)
{
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	u32 C_shuter = 0;
	u16 C_gain = 0;
	u16 C_gain_db = 0;
	C_shuter = sensor->get_exposure();
	C_gain_db = sensor->get_gain();

	sensor->sensor_hdr_movie.get_hdr_movie_ae_param(hdr_ae_param);
	
	C_gain = hdr_gain_db_to_time(C_gain_db);// gain_db switch gain times

	print_info("enter %s",__func__);

	#ifdef HDR_MOVIE_DEBUG_MODE
	char *hdrfilename = "/data/hdr_sensor_debug.txt";
	ispv1_load_sensor_setting(sensor,hdrfilename);
	hdr_ae_param->hdr_ae_target  = sensor->sensor_hdr_movie.ae_target_high;
	sensor->sensor_hdr_movie.hdrInfo.ae_target = sensor->sensor_hdr_moive.ae_target_high;
	#else
	hdr_ae_param->hdr_ae_target  = HDR_AE_TARGET_HIGH;
	sensor->sensor_hdr_movie.hdrInfo.ae_target = HDR_AE_TARGET_HIGH;
	#endif
	hdr_ae_param->default_gain = C_gain;
	hdr_ae_param->default_shutter = C_shuter;
	print_info("hdr_ae_param->default_gain = %d ",hdr_ae_param->default_gain);
	return 0;
}

/****************************************************************************
* FunctionName	: ispv1_get_hdr_movie_ae_running_param;
* Description 		: Ae in the HAL get ae mean of stats lux and banding step by this interface from driver.;
* Input       		: the space of struct hdr_ae_volatile_param;
* Output      		: the value of ae mean and banding step;
* ReturnValue 	: NA;
* Other       		: NA;
***************************************************************************/
int ispv1_get_hdr_movie_ae_running_param(hdr_ae_volatile_param * output_param)
{
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;

	int banding_step = 0;
	int ae_target = 0;

	print_info("enter %s",__func__);

	assert(sensor);
	if(NULL == sensor) {
		return -EINVAL;
	}
	if(HDR_MOVIE_ON != sensor->sensor_hdr_movie.get_hdr_movie_switch() )
	//if(HDR_MOVIE_OFF == sensor->sensor_hdr_moive.get_hdr_movie_switch() )
	{
		output_param->ae_mean = 1;
		output_param->banding_step = 1;
		output_param->hdr_ae_target = 1;
		output_param->sensor_vts = 1;
		return 0;
	}
	ae_target = sensor->sensor_hdr_movie.hdrInfo.ae_target;

	hdr_movie_stats_param_init();

	banding_step = ispv1_hdr_banding_step_change(mini_this_ispdata->anti_banding);

	output_param->hdr_ae_target = sensor->sensor_hdr_movie.hdrInfo.ae_target;
	output_param->banding_step 	= banding_step;
	output_param->sensor_vts	= sensor->frmsize_list[sensor->preview_frmsize_index].vts;
	if(_IS_DEBUG_AE)
	{
		print_info(" ae_target: %d,banding_step = %d,sensor_vts = %d\n",ae_target, banding_step,output_param->sensor_vts);
	}

	return 0;
}

 /*
  *************************************************************************
  * FunctionName: ispv1_hdr_set_ATR_switch
  * Description : the function that turn on or off atr functio for hdr movie
  * Input			: on 1 on, 0 off
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
void ispv1_hdr_set_ATR_switch(int on)
{
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	print_info("enter %s ,switch = 0x%x", __func__,on);
	assert(sensor);
	if(NULL == sensor) {
		return;
	}
	if(sensor->sensor_hdr_movie.set_ATR_switch)
	{
	   sensor->sensor_hdr_movie.set_ATR_switch(on);
	}
}
 
int ispv1_awb_dynamic_ccm_gain(void)
{
	//mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	mini_awb_gain_t  awb_gain;
	u32 current_rbratio = 0x100;

	GETREG16(REG_ISP_AWB_ORI_GAIN_B, awb_gain.b_gain);
	GETREG16(REG_ISP_AWB_ORI_GAIN_R, awb_gain.r_gain);

	if ((awb_gain.b_gain != 0) && (awb_gain.r_gain != 0)) {
		current_rbratio = 0x8000 / (awb_gain.b_gain * 0x100 / awb_gain.r_gain);
	}

	return current_rbratio;
}

  /*
  *************************************************************************
  * FunctionName: 	hdr_movie_adjust_process;
  * Description 	: the function  that adjust ae arithmatic and atr curve of  sensor
  * Input			: ae result : the struct include long shutter ,short shutter long gain and short gain.
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
void hdr_movie_adjust_process(hdr_ae_algo_result *ae_result)
{
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	u16 N_gain = ae_result->N_gain;
	u16 N_gainBeforeAjust = ae_result->N_gainBeforeAjust;
	u16 atr_switch_gain = hdr_movie_ae_ctrl->hdr_atr_switch_gain;
	u16 gain_interval = 0;
	u32 wb_lmt = ae_result->N_wb_lmt;
	u32 ae_sat = ae_result->N_ae_sat;
	u16 rbratio =  ispv1_awb_dynamic_ccm_gain();
	if(rbratio < HDR_RBRATIO_THESHOLD)
	{
		atr_switch_gain = HDR_ATR_SWITCH_INDOOR;
		gain_interval = HDR_ATR_INTERVAL_INDOOR;
	}
	else
	{
		atr_switch_gain = HDR_ATR_SWITCH_OUTDOOR;
		gain_interval = HDR_ATR_INTERVAL_OUTDOOR;
	}
#ifdef HDR_MOVIE_DEBUG_MODE

	if(N_gainBeforeAjust > sensor->sensor_hdr_movie.ae_arithmatic_switch_gain)
	{
		hdr_movie_ae_ctrl->ae_arith_method = HDR_AE_AVERAGE_MATH;
	}
	else
	{
		hdr_movie_ae_ctrl->ae_arith_method = HDR_AE_WEIGHT_MATH;
	}

	if(rbratio < HDR_RBRATIO_THESHOLD)
	{
		atr_switch_gain = sensor->sensor_hdr_movie.gain_switch2;
		gain_interval = sensor->sensor_hdr_movie.gain_interval2;
	}
	else
	{
		atr_switch_gain = sensor->sensor_hdr_movie.gain_switch;
		gain_interval = sensor->sensor_hdr_movie.gain_interval;
	}
#endif

	if(N_gainBeforeAjust >=(atr_switch_gain + gain_interval))
	{
	        if(ATR_ON == sensor->sensor_hdr_movie.hdrInfo.atr_on)
	        {
	            ispv1_hdr_set_ATR_switch(0);
		     	if(sensor->sensor_hdr_movie.hdrInfo.atr_over_expo_on)
				sensor->sensor_hdr_movie.over_exposure_adjust(0,NULL);
	        }
		wb_lmt = 1023;
		ae_sat  = 960;
		ae_result->N_short_gain 	= ae_result->N_gain;
		ae_result->N_short_shuter	= ae_result->N_shuter;

	}else if(N_gainBeforeAjust < (atr_switch_gain - gain_interval))
	{
	        if( ATR_OFF == sensor->sensor_hdr_movie.hdrInfo.atr_on)
	        {
	            ispv1_hdr_set_ATR_switch(1);
	        }
	}
	if(_IS_DEBUG_AE)
	{
		print_info("N_gainBeforeAjust =%d,N_gain: %d, atr_switch_gain: %d,gain_interval: %d atr_on = %d ae_arithmatic_switch_gain = %d,rbratio=%d",N_gainBeforeAjust, N_gain,atr_switch_gain, gain_interval,sensor->sensor_hdr_movie.hdrInfo.atr_on,hdr_movie_ae_ctrl->ae_arith_method,rbratio);
		print_info("ae_sat = %08x,wb_lmt = %08x", ae_sat,wb_lmt);
	}
	if(sensor->sensor_hdr_movie.set_lmt_sat)
	{
		sensor->sensor_hdr_movie.set_lmt_sat(wb_lmt,ae_sat);
	}

	ae_result->N_wb_lmt	= wb_lmt;
	ae_result->N_ae_sat	= ae_sat;
}

 /*
  *************************************************************************
  * FunctionName: 	hdr_gain_time_to_db;
  * Description 	: the function  switch gain times to gain db according to gain_time table and gain db table
  * Input			: gain time value
  * Output		: gain db value;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
int hdr_gain_time_to_db(int gain_time)
{

	int gain_db = 0;
	int i;
	for(i=0; i<GAIN_TABLE_LEN; i++)
	{
		if(gain_time<=gain_time_table[i])
		{
			if(i==0)
				gain_db = gain_db_table[0];
			else
			{
				if(gain_time - gain_time_table[i-1] > gain_time_table[i] - gain_time)
					gain_db = gain_db_table[i];
				else
					gain_db = gain_db_table[i-1];
			}
			break;
		}
	}
	return gain_db;
}

 /*
  *************************************************************************
  * FunctionName: 	:ispv1_set_digital_gain;
  * Description 	: set digital gain to sensor's digital registers
  * Input			: the struct of digital_gain_st saving digital value
  * Output			: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
void ispv1_set_digital_gain(digital_gain_st * digital_gain)
{
	mini_camera_sensor * sensor = mini_this_ispdata->sensor;

	print_info("enter %s", __func__);
	sensor->sensor_hdr_movie.set_digital_gain(digital_gain);
}

 /*
  *************************************************************************
  * FunctionName: ispv1_hdr_set_analog_gain_exposure;
  * Description 	: the function that set long shutter ,short shutter , long gain and short gain to sensor and isp
  * Input			: the struct of hdr_ae_algo_result include 1.long exposure. 2 short exposure. 3 long gain 4 short gain
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
void ispv1_hdr_set_analog_gain_exposure(hdr_ae_algo_result * ae_result)
{
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	u16 isp_long_gain_db = 0;
	u16 isp_short_gain_db = 0;
	u8  digital_gain_h = 0;
	u8  digital_gain_l = 0;
	u16 long_gain_db = 0;
	u16 short_gain_db = 0;
	u32 expo_long = ae_result->N_shuter;
	u32 expo_short = ae_result->N_short_shuter;
	u16 global_gain = ae_result->N_gain;
	u16 gain_short = ae_result->N_short_gain;
	u16 N_gainBeforeAjust = ae_result->N_gainBeforeAjust;

	digital_gain_st digital_gain;

	print_info("enter %s",__func__);

	if(_IS_DEBUG_AE)
	{
		print_info("N_gainBeforeAjust = %d,global_gain = %d ,expo_long = %d,gain_short = %d,expo_short = %d", N_gainBeforeAjust,global_gain,expo_long,gain_short,expo_short);
//		u16 digital_gain_debug = ae_result->N_digital;
	}
	if(sensor->sensor_hdr_movie.set_hdr_exposure_gain)
	{
		digital_gain_h = ((ae_result->N_digital >> 8)&0xff);
		digital_gain_l = (ae_result->N_digital &0xff);
		digital_gain.digital_gain_h = digital_gain_h;
		digital_gain.digital_gain_l = digital_gain_l;
		ispv1_set_digital_gain(&digital_gain);
		long_gain_db = hdr_gain_time_to_db(global_gain);
		short_gain_db = hdr_gain_time_to_db(gain_short);
		sensor->sensor_hdr_movie.set_hdr_exposure_gain(expo_long, long_gain_db, expo_short, short_gain_db);
	}

	if(N_gainBeforeAjust != 0)
	isp_long_gain_db = 256 - (256 * 16) / N_gainBeforeAjust;
	if(gain_short != 0)
	 isp_short_gain_db = 256 - (256 * 16) / gain_short;

	 SETREG8(REG_ISP_LONG_TIME_H, (expo_long >> 8)&0xff);
	 SETREG8(REG_ISP_LONG_TIME_L, expo_long &0xff);
	 SETREG8(REG_ISP_LONG_TIME_DS_H, (expo_long >> 8)&0xff);
	 SETREG8(REG_ISP_LONG_TIME_DS_L, expo_long &0xff);
	 SETREG8(REG_ISP_LONG_GAIN, isp_long_gain_db&0xff);

	 SETREG8(REG_ISP_SHORT_TIME_WHT_H, (expo_short >> 8)&0xff);
	 SETREG8(REG_ISP_SHORT_TIME_WHT_L, expo_short &0xff);
	 SETREG8(REG_ISP_SHORT_TIME_WHT_DS_H, (expo_short >> 8)&0xff);
	 SETREG8(REG_ISP_SHORT_TIME_WHT_DS_L, expo_short &0xff);
	 SETREG8(REG_ISP_SHORT_GAIN, isp_long_gain_db&0xff);
}

 /*
  *************************************************************************
  * FunctionName   : hdr_movie_over_exposure_process;
  * Description 	: the function that adjust min stats, ave stats,max stats for atr corve for overexposure..
  * Input			: NA
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
static void hdr_movie_over_exposure_process(void)
{
	mini_camera_sensor *sensor = mini_this_ispdata->sensor;
	int frm_min = 0;
	int frm_max = 0;
	int frm_min_h = 0;
	int frm_min_l  = 0;
	int frm_ave_h = 0;
	int frm_ave_l  = 0;
	int frm_max_h = 0;
	int frm_max_l  = 0;

	int stats_diff_thl =  0;
	int stats_max_thl= 0;
	int stats_max = hdr_movie_ae_ctrl->stats_max;
	int stats_min	 = hdr_movie_ae_ctrl->stats_min;
	int stats_ave	 = hdr_movie_ae_ctrl->stats_ave;
	int stats_diff = hdr_movie_ae_ctrl->stats_diff;
	stats_hdr_frm stats_frm;
	frm_min = HDR_MOVIE_FRM_MIN_IN;
	frm_max = 959;
#ifdef HDR_MOVIE_DEBUG_MODE
	stats_diff_thl = sensor->sensor_hdr_movie.stats_diff_threshold;
	stats_max_thl = sensor->sensor_hdr_movie.stats_max_threshold;
#else
	stats_diff_thl = HDR_MOVIE_STATS_DIFF_TH;
	stats_max_thl = HDR_MOVIE_OVER_EXP_TH;
#endif
	print_info("enter %s",__func__);
	if(_IS_DEBUG_AE)
	print_info("stats_diff = %d,stats_max= %d,stats_ave=%d,stats_min=%d,stats_diff_thl=%d,stats_max_thl=%d",stats_diff,stats_max,stats_ave,stats_min,stats_diff_thl,stats_max_thl);
	if(stats_diff < stats_diff_thl)
	{
		if(stats_max < stats_max_thl)
		{
			if(frm_min > stats_min)
				frm_min = stats_min;
				frm_min_h = frm_min / 256;
				frm_min_l = frm_min - frm_min_h * 256;

				frm_ave_h = stats_ave / 256;
				frm_ave_l = stats_ave - frm_ave_h * 256;

			if (frm_max < stats_max)
				frm_max = stats_max;
				frm_max_h = frm_max / 256;
			       frm_max_l = frm_max - frm_max_h * 256;

				stats_frm.frm_ave_h = frm_ave_h;
				stats_frm.frm_ave_l = frm_ave_l;
				stats_frm.frm_min_h = frm_min_h;
				stats_frm.frm_min_l = frm_min_l;
				stats_frm.frm_max_h = frm_max_h;
				stats_frm.frm_max_l = frm_max_l;
				sensor->sensor_hdr_movie.over_exposure_adjust(1,&stats_frm);
	    	}
	    	else
	    	{
	    		if(sensor->sensor_hdr_movie.hdrInfo.atr_over_expo_on)
				sensor->sensor_hdr_movie.over_exposure_adjust(0,NULL);
		}
	}
	else
	{
		if(sensor->sensor_hdr_movie.hdrInfo.atr_over_expo_on)
			sensor->sensor_hdr_movie.over_exposure_adjust(0,NULL);
	}
}

/****************************************************************************
* FunctionName: ispv1_set_sensor_awb_gain;
* Description : NA;
* Input       : R,GR,GB,B gain from isp;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static void ispv1_set_sensor_awb_gain(void)
{
	u16 b_gain, gb_gain, gr_gain, r_gain;
	assert(mini_this_ispdata->sensor);
	if (mini_this_ispdata->sensor->sensor_hdr_movie.set_awb_gain)
	{
		GETREG16(MANUAL_AWB_GAIN_B, b_gain);
		GETREG16(MANUAL_AWB_GAIN_GB, gb_gain);
		GETREG16(MANUAL_AWB_GAIN_GR, gr_gain);
		GETREG16(MANUAL_AWB_GAIN_R, r_gain);

		b_gain = 2 * b_gain;
		gb_gain = 2 * gb_gain;
		gr_gain = 2 * gr_gain;
		r_gain = 2 * r_gain;

		mini_this_ispdata->sensor->sensor_hdr_movie.set_awb_gain(b_gain, gb_gain, gr_gain, r_gain);
	}
}

/****************************************************************************
* FunctionName	: ispv1_set_hdr_movie_shutter_gain_to_sensor;
* Description 		: the function that set long and short gain and shutter from HAL and then set it to sensor.
				: otherwise adjust hdr cuver and points for over exposure and awb gain.
* Input       		: the value of long shutter ,long gain ,short shutter short gain for sensor.
* Output      		: NA
* ReturnValue 	: NA;
* Other       		: NA;
***************************************************************************/
int ispv1_set_hdr_movie_shutter_gain_to_sensor(hdr_ae_algo_result * ae_result)
{
	mini_camera_sensor * sensor = mini_this_ispdata->sensor;
	int mean = 0;
	if(sensor->sensor_hdr_movie.get_hdr_movie_switch()== false)
		return 0;
	//mean = sensor->sensor_hdr_movie.hdrInfo.ae_target - ae_result->N_mean;
	mean = ae_result->N_mean;

	if(mean == 0)
	{
	    if(_IS_DEBUG_AE)
             print_info("******stable!******\n");
	     SETREG8(REG_ISP_AE_STATUS,0x1);//ispv1_hdr_set_ae_status(1); tell the status of ae to isp,the status of ae include  STEADY_STATUS and ADJUST_STATUS
	}
	else
	{
		 if(_IS_DEBUG_AE)
		print_info("******Not stable!******\n");
		
	      	SETREG8(REG_ISP_AE_STATUS,0x0);// ispv1_hdr_set_ae_status(0);tell the status of ae to isp,the status of ae include  STEADY_STATUS and ADJUST_STATUS
		   
		hdr_movie_adjust_process(ae_result);

		ispv1_hdr_set_analog_gain_exposure(ae_result);

		if(sensor->sensor_hdr_movie.hdrInfo.atr_on)
		{
			hdr_movie_over_exposure_process();
		}
		
	       ispv1_set_sensor_awb_gain();
	}

	return 0;
}

#ifdef HDR_MOVIE_DEBUG_MODE
static int atoi(char *s)
{
	char *p = s;
	char c;
	int ret = 0;

	if (s == NULL)
		return 0;
	while ((c = *p++) != '\0') {
		if ('0' <= c && c <= '9') {
				ret *= 10;
				ret += c - '0';
		}
		else{
			break;
		}
	}
	return ret;
}
#endif

/*
 **************************************************************************
 * FunctionName: ispv1_load_sensor_setting;
 * Description : load hdr debug file for hdr movie
 * Input       : mini_camera_sensor object and the name of debug;
 * Output      : error flag
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
extern int mini_atoi16(char *s);

#ifdef HDR_MOVIE_DEBUG_MODE
static int ispv1_load_sensor_setting(mini_camera_sensor *sensor,char *filename)
{
	struct kstat stat;
	mm_segment_t fs;
	struct file *fp = NULL;
	int file_flag = O_RDONLY;
	ssize_t ret = 0;
	u32 addr = 0;
	u16 value;
	char addr_array[8] = {0};
	char value_array[6] = {0};
	char temp;
	bool bRegStart = false;
	if (NULL == filename) {
		print_error("%s param error", __func__);
		return -EINVAL;
	}
	if (NULL == sensor) {
		print_error("%s sensor pointer is null", __func__);
		return -EINVAL;
	}
	print_info("enter %s", __func__);

	/* must have the following 2 statement */
	fs = get_fs();
	set_fs(KERNEL_DS);

	fp = filp_open(filename, file_flag, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		print_info("open file error!\n");
		return -1;
	}

	if (0 != vfs_stat(filename, &stat)) {
		print_error("failed to get file state!");
		goto ERROR;
	}
	print_info("file size : %d", (u32) stat.size);
	while (0 < vfs_read(fp, &temp, 1, &fp->f_pos)) {
		switch (temp) {
			case '{':
				bRegStart = true;
				if (0 == vfs_read(fp, addr_array, 6, &fp->f_pos))
					goto ERROR;
				addr = mini_atoi16(addr_array);
				break;

			case '}':
				bRegStart = false;
				break;

			case ',':
				if (bRegStart) {
					if (0 == vfs_read(fp, value_array, 4, &fp->f_pos))
						goto ERROR;
					value = mini_atoi16(value_array);
					bRegStart = false;

					/*write reg*/
					print_info("addr=0x%x, value=0x%x", addr, value);
					//sensor->sensor_write_reg(addr, value,0x0);
					SETREG8(addr, value);
				break;
			case '=':
					if (bRegStart) {
					if (0 == vfs_read(fp, value_array, 4, &fp->f_pos))
						goto ERROR;
					value = atoi(value_array);
					bRegStart = false;

					if(0x1 == addr)//0x1 is ae target flag in the hdr-sensor-debug.txt
					{
						sensor->sensor_hdr_movie.ae_target_high = value;
					}else if(0x2 == addr)//0x2 is gain switch flag in the hdr-sensor-debug.txt
					{
						sensor->sensor_hdr_movie.gain_switch = value;
					}else if(0x3 == addr)//0x3 is hdr funtion max gain flag in the hdr-sensor-debug.txt
					{
						sensor->sensor_hdr_movie.sensor_max_gain= value;
					}else if(0x5 == addr)//0x5 is atr off /on range of gain switch ,{gain switch + gain interval, gain switch - gain interval}
					{
						sensor->sensor_hdr_movie.gain_interval = value;
					}else if(0x6 == addr)//0x6 is stats_diff
					{
						sensor->sensor_hdr_movie.stats_diff_threshold = value;
					}else if(0x7 == addr)//0x7 is stats_max
					{
						sensor->sensor_hdr_movie.stats_max_threshold = value;
					}else if(0x8 == addr)//0x8 low target
					{
						sensor->sensor_hdr_movie.ae_target_low = value;
					}else if(0x12 == addr)
					{
						sensor->sensor_hdr_movie.gain_switch2 = value;
					}else if(0x13 == addr)
					{
						sensor->sensor_hdr_movie.gain_interval2 = value;
					}
					print_info("addr=0x%x, ae_target_low=%d,ae_target_low= %d,gain_switch = %d,max_gain = %d,gain_interval = %d", addr,sensor->sensor_hdr_movie.ae_target_low,sensor->sensor_hdr_movie.ae_target_high,sensor->sensor_hdr_movie.gain_switch,sensor->sensor_hdr_movie.sensor_max_gain,sensor->sensor_hdr_movie.gain_interval);
				}
				break;
			default:
				break;
			}
		}
	}
	/* must have the following 1 statement */
	set_fs(fs);

ERROR:
	if (NULL != fp)
		filp_close(fp, 0);
	return ret;
}
#endif

