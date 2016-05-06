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
#include <linux/io.h>
#include <linux/bug.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
//#include <linux/android_pmem.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/clk.h>
#include <linux/time.h>
#include <linux/ktime.h>

#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <mach/irqs.h>
#include <mach/boardid.h>

#include <mach/clk_name_interface.h>
#include "reg_ops.h"
#include "soc_ao_sctrl_interface.h"
#include "soc_pmctrl_interface.h"
#include "soc_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "drv_regulator_user.h"

#include <trace/trace_kernel.h>
//#include <mach/gpio.h>
#include <linux/gpio.h>
#include "mini_cam_util.h"
#include "mini_cam_dbg.h"
#include "mini_k3_isp.h"
#include "mini_k3_ispv1.h"
#include "mini_k3_ispv1_afae.h"
#include "mini_k3_isp_io.h"
#include "mini_hwa_cam_tune_common.h"
#include "mini_cam_log.h"

#include "camera_agent.h"  // add by zhoutian for mini-ISP flash

#define DEBUG_DEBUG 0
#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "miniisp_agent"
#endif


extern mini_k3_isp_data *mini_this_ispdata;
extern mini_ispv1_afae_ctrl *mini_afae_ctrl;
extern u32 misp_meta_data_log;
void mini_ov_set_wb_value(mini_isp_meta_data *meta_data)
{
	u16 b_gain,gb_gain,gr_gain,r_gain;

	b_gain = meta_data->data.awb_info.b_gain;
	gb_gain = meta_data->data.awb_info.g_gain;
	gr_gain = meta_data->data.awb_info.g_gain;
	r_gain = meta_data->data.awb_info.r_gain;

	if (unlikely(gb_gain != 0x100 || gr_gain != 0x100)){
		print_error("invalid awb gain:b_gain=0x%x,gb_gain=0x%x,gr_gain=0x%x,r_gain=0x%x",
					b_gain,gb_gain,gr_gain,r_gain);
		return;
	}

	b_gain >>= 1;
	r_gain >>= 1;
	gb_gain = 0x80;
	gr_gain = 0x80;
	SETREG16(MANUAL_AWB_GAIN_B, b_gain);
	SETREG16(MANUAL_AWB_GAIN_GB, gb_gain);
	SETREG16(MANUAL_AWB_GAIN_GR, gr_gain);
	SETREG16(MANUAL_AWB_GAIN_R, r_gain);

}

void mini_ov_set_ae_value(mini_isp_meta_data *meta_data)
{
	u16 expo_line;
	u16 gain;

	expo_line = meta_data->data.ae_info.expo_line;
	gain = meta_data->data.ae_info.gain;

	if (expo_line==0 || gain==0)
		return;

	expo_line <<=4;
	gain <<=4;
	gain = gain/100;
	SETREG16(REG_ISP_MANUAL_GAIN,gain);
	SETREG32(REG_ISP_MANUAL_EXPOSURE,expo_line);

}

void mini_ov_set_af_status(mini_isp_meta_data *meta_data)
{
	u8 result;
	mini_ispv1_afae_ctrl *afae_ctrl_ptr = mini_afae_ctrl;

	result = meta_data->data.af_info.converge_state;
	print_debug("%s result = %d",__func__,result);

	if((afae_ctrl_ptr->focus_state == FOCUS_STATE_AF_PREPARING)){
		if(result !=0x12){
			afae_ctrl_ptr->af_result = STATUS_FOCUSING;
			return;
		}
	}
	if((afae_ctrl_ptr->focus_state == FOCUS_STATE_S1_ABORT)){
		if(result != 0x13)
		{
			afae_ctrl_ptr->af_result = STATUS_OUT_FOCUS;
			return;
		}
	}

	switch(result) {
	case 0x12:
	case 0x02:
		afae_ctrl_ptr->af_result = STATUS_FOCUSING;
		afae_ctrl_ptr->focus_state = FOCUS_STATE_AF_RUNNING;
		break;
	case 0:
	case 0x10:
		afae_ctrl_ptr->af_result = STATUS_FOCUSED;
		afae_ctrl_ptr->focus_state = FOCUS_STATE_STOPPED;
		break;
	case 0x11:
	case 0x01:
		afae_ctrl_ptr->af_result = STATUS_OUT_FOCUS;
		afae_ctrl_ptr->focus_state = FOCUS_STATE_STOPPED;
		break;
	case 0x04:
		break;
	default:
		print_error("mini isp AF result should not reach here,set to STATUS_OUT_FOCUS,result = 0x%x",result);
		afae_ctrl_ptr->af_result = STATUS_OUT_FOCUS;
		afae_ctrl_ptr->focus_state = FOCUS_STATE_STOPPED;
		break;
	}
	return;
}


//#define META_DATA_DEBUG

void mini_isp_meta_data_print_for_debug(mini_isp_meta_data *meta_data_ptr)
{
	meta_data_st *data = &meta_data_ptr->data;

	print_info("meta_data common frame_index=%d, frame_rate=%d, scene_mode=%d, scene_change_flg=%d",
		data->common_info.frame_index, data->common_info.frame_rate, data->common_info.scene_mode, data->common_info.scene_change_flg);
	print_info("digital_zoom=%d, filcker_detect_reslut=%d, module_id=%d, frame_type=%d",
		data->common_info.digital_zoom, data->common_info.filcker_detect_reslut, data->common_info.module_id, data->common_info.frame_type);
	print_info("meta_data AE result_BV=%d, expo_time=%d, expo_line=%d, iso=%d, gain=%d, avg_raw_lum=%d",
		data->ae_info.result_BV, data->ae_info.expo_time, data->ae_info.expo_line, data->ae_info.iso, data->ae_info.gain, data->ae_info.avg_raw_lum);
	print_info("meta_data AE target=%d, manual_ev_comp=%d, mode=%d, flash_turnon_flag=%d, converge_state=%d",
		data->ae_info.target, data->ae_info.manual_ev_comp, data->ae_info.mode, data->ae_info.flash_turnon_flag, data->ae_info.converge_state);
	print_info("meta_data AWB converge_state=%d, mode=%d, r_gain=%d, g_gain=%d, b_gain=%d, light_source=%d",
		data->awb_info.converge_state, data->awb_info.mode, data->awb_info.r_gain, data->awb_info.g_gain, data->awb_info.b_gain, data->awb_info.light_source);
	print_info("meta_data AF converge_state=%d, assist_flash_turnon_flag=%d, code=%d, mode=%d, final_peak_step=%d, bar_level=%d",
		data->af_info.converge_state, data->af_info.assist_flash_turnon_flag, data->af_info.code, data->af_info.mode, data->af_info.final_peak_step, data->af_info.bar_level);
	print_info("meta_data FE preflash1_state=%d, ae_image_cal_ready=%d, preflash1_cal_ready=%d, preflash2_cal_ready=%d, mainflash_led_enerage=%d",
		data->fe_info.preflash1_state, data->fe_info.ae_image_cal_ready, data->fe_info.preflash1_cal_ready, data->fe_info.preflash2_cal_ready, data->fe_info.mainflash_led_enerage);
}

void mini_dump_file(char *filename, u32 addr, u32 size);
extern mini_isp_hw_data_t 				mini_isp_hw_data;
extern u32 						misp_dump_meta_data;
void mini_isp_meta_data_parser(void *statphyaddr, void *meta_data_ptr)
{
	void *viraddr = NULL;
	u8 *data_src = NULL;
	u8 *data_dst = NULL;
	int i = 0;
	meta_data_st *meta_data = NULL;
	meta_data_st *meta_data_buff = NULL;
	int meta_data_size = 0;
	u8 name[100];

	if(NULL == statphyaddr) {
		print_error("%s statphyaddr is NULL", __func__);
		return;
	}

	if(NULL == meta_data_ptr) {
		print_error("%s meta_data_ptr is NULL", __func__);
		return;
	}

	meta_data = &((mini_isp_meta_data *)meta_data_ptr)->data;
	meta_data_buff = &((mini_isp_meta_data *)meta_data_ptr)->data_buff;
	meta_data_size = sizeof(meta_data_st);

	viraddr = ioremap_nocache((phys_addr_t)statphyaddr, meta_data_size * 2);
	if(viraddr) {
		data_src = (u8 *)viraddr;
		data_dst = (u8 *)meta_data_buff;
		for(i = 0; i < meta_data_size; i++) {
			*data_dst = (*data_src >> 6) | (*(data_src+1) << 2);
			data_dst++;
			data_src += 2;
		}
		memcpy(meta_data, meta_data_buff, meta_data_size);
		if(misp_meta_data_log==1){
			mini_isp_meta_data_print_for_debug((mini_isp_meta_data *)meta_data_ptr);
		}
		if(misp_dump_meta_data == 1){
			snprintf(name, sizeof(name),"/data/meta_test/meta_data_raw_%d",mini_isp_hw_data.frame_count);
			mini_dump_file(name, viraddr, meta_data_size * 2);
		}
		iounmap(viraddr);
	} else
		print_error("%s statphyaddr ioremap_nocache error", __func__);

}


void mini_isp_meta_data_exit(void **meta_data_ptr)
{
	mini_isp_meta_data *meta_data;

	print_info("enter %s", __func__);

	if(NULL == meta_data_ptr) {
		print_error("%s meta_data_ptr is NULL", __func__);
		return;
	}

	meta_data = *meta_data_ptr;

	if(meta_data) {
		kfree(meta_data);
		meta_data = NULL;
	}
}


void mini_isp_meta_data_init(mini_isp_meta_data **meta_data_ptr)
{
	mini_isp_meta_data *meta_data;

	print_info("enter %s", __func__);

	if(NULL == meta_data_ptr)
		return;

	meta_data = kmalloc(sizeof(mini_isp_meta_data), GFP_KERNEL);
	if(meta_data) {
		memset(meta_data, 0, sizeof(mini_isp_meta_data));
		meta_data->exit = mini_isp_meta_data_exit;
		meta_data->parse = mini_isp_meta_data_parser;
	} else {
		print_error("%s kmalloc meta_data error", __func__);
	}

	*meta_data_ptr = meta_data;
}


int mini_ov_get_band_threshold(mini_camera_sensor *sensor, camera_anti_banding banding)
{
	u32 banding_time = 0;
	u32 expo_time = 0;
	int hz;
	mini_k3_isp_data *thisispdata=mini_this_ispdata;

	print_debug("enter %s banding = %d", __func__,banding);
       hz =  banding;
	 if(hz == CAMERA_ANTI_BANDING_50Hz)
	 {
	 	banding_time = 10000;
	 }
	 else if(hz == CAMERA_ANTI_BANDING_60Hz)
	 {
	 	banding_time = 1000000/120;
	 }
	 else
	 {
	 	banding_time = 0;
	 }

	if (0 == banding_time)
		return 0;

	expo_time = thisispdata->meta_data->data.ae_info.expo_time;
	print_debug("banding_time = %d expo_time =%d",banding_time,expo_time);
	if(expo_time == 0)
		return 0;

	return (expo_time >= banding_time);
}
int mini_ov_get_val_meta_data(mini_isp_meta_data *meta_data)
{
	u8 banding;
	mini_k3_isp_data *thisispdata=mini_this_ispdata;

	banding = meta_data->data.common_info.filcker_detect_reslut;
	if(banding == 0)
		thisispdata->anti_banding = CAMERA_ANTI_BANDING_50Hz;
	else if(banding == 1)
		thisispdata->anti_banding = CAMERA_ANTI_BANDING_60Hz;
	else
		thisispdata->anti_banding = CAMERA_ANTI_BANDING_60Hz;

	thisispdata->sensor->fps = thisispdata->meta_data->data.common_info.frame_rate;
	if(thisispdata->sensor->fps == 0)
	{
		thisispdata->sensor->fps = thisispdata->sensor->fps_max;
	}

	return 0;
}


enum {
	S0_converge_state_OK = 0x00,
	S0_converge_state_FAIL = 0x01,
	S0_converge_state_RUNNING = 0x02,
	S0_converge_state_ABORT = 0x03,
	S1_converge_state_OK = 0x10,
	S1_converge_state_FAIL = 0x11,
	S1_converge_state_RUNNING = 0x12,
	S1_converge_state_ABORT = 0x13,
};

bool mini_isp_check_s1_lock_need_af(void)
{
	mini_k3_isp_data *thisispdata=mini_this_ispdata;

	print_info("%s: AF_state = %#x", __func__, thisispdata->meta_data->data.af_info.converge_state);
	if (thisispdata->meta_data->data.af_info.converge_state == S0_converge_state_OK
		|| thisispdata->meta_data->data.af_info.converge_state == S1_converge_state_OK) {
		print_info("%s: AF already ok, disable AF", __func__);
		camera_agent_set_s1_AF_enable(CAMERA_SENSOR_PRIMARY, 0);
		return false;
	}

	camera_agent_set_s1_AF_enable(CAMERA_SENSOR_PRIMARY, 1);
	return true;
}

camera_flash mini_isp_check_af_flash_mode(void)
{
	mini_k3_isp_data *thisispdata=mini_this_ispdata;

	if (thisispdata->flash_mode == CAMERA_FLASH_AUTO
		|| thisispdata->flash_mode == CAMERA_FLASH_ON)
		return CAMERA_FLASH_AUTO;

	return CAMERA_FLASH_OFF;
}

camera_flash mini_isp_check_pre_flash_mode(void)
{
	mini_k3_isp_data *thisispdata=mini_this_ispdata;

	if (thisispdata->shoot_mode != CAMERA_SHOOT_SINGLE)
		return CAMERA_FLASH_OFF;

	if (thisispdata->flash_mode == CAMERA_FLASH_ON)
		return CAMERA_FLASH_ON;

	if (thisispdata->flash_mode == CAMERA_FLASH_AUTO)
		return CAMERA_FLASH_AUTO;

	return CAMERA_FLASH_OFF;
}

void mini_isp_flash_controller(mini_isp_meta_data *meta_data)
{
	mini_camera_flashlight *flashlight = NULL;
	bool need_to_turn_on = false;
	mini_k3_isp_data *thisispdata=mini_this_ispdata;

	print_debug("enter %s", __func__);

	flashlight = mini_get_camera_flash();
	if (NULL == flashlight) {
		print_error("get_camera_flash return NULL");
		return;
	}

	if (thisispdata->sensor->sensor_index != CAMERA_SENSOR_PRIMARY)
		thisispdata->s1_3a_state = S1_3A_LOCKED;

	if (thisispdata->s1_3a_state == S1_3A_LOCKED)
		return;

	print_info("meta_data AE_state=%#x, AE_image_cal_ready=%#x, flash_turnon_flag=%#x, assist_flash_turnon_flag=%#x",
		meta_data->data.ae_info.converge_state, meta_data->data.fe_info.ae_image_cal_ready,
		meta_data->data.ae_info.flash_turnon_flag, meta_data->data.af_info.assist_flash_turnon_flag);
	print_info("meta_data AF_state=%#x, preflash1_state=%#x, preflash1_cal_ready=%#x, mainflash_led_enerage=%d",
		meta_data->data.af_info.converge_state, meta_data->data.fe_info.preflash1_state,
		meta_data->data.fe_info.preflash1_cal_ready, meta_data->data.fe_info.mainflash_led_enerage);

	mutex_lock(&thisispdata->mini_isp_flash_period_lock);
	switch(thisispdata->mini_isp_flash_period)
	{
		case FLASH_IDLE:
		{
			if (meta_data->data.ae_info.converge_state == S1_converge_state_RUNNING) {
				print_info("FLASH_IDLE --> FLASH_WAIT");
				thisispdata->mini_isp_flash_period = FLASH_WAIT;
			} else {
				print_info("FLASH_WAIT");
				break;
			}
		}
		case FLASH_WAIT:
		{
			if (meta_data->data.ae_info.converge_state == S1_converge_state_RUNNING
				|| !meta_data->data.fe_info.ae_image_cal_ready
				|| meta_data->data.af_info.assist_flash_turnon_flag == 2
				|| meta_data->data.ae_info.flash_turnon_flag == 2)
				break;

			if (thisispdata->s1_3a_state == S1_3A_UNLOCKED_BY_TAF) {
				if (thisispdata->flash_mode == CAMERA_FLASH_ON || thisispdata->flash_mode == CAMERA_FLASH_AUTO)
					if (meta_data->data.af_info.assist_flash_turnon_flag || meta_data->data.ae_info.flash_turnon_flag)
						need_to_turn_on = true;
			} else {
				if (thisispdata->flash_mode == CAMERA_FLASH_ON)
					need_to_turn_on = true;
				else if (thisispdata->flash_mode == CAMERA_FLASH_AUTO)
					if (meta_data->data.af_info.assist_flash_turnon_flag || meta_data->data.ae_info.flash_turnon_flag)
						need_to_turn_on = true;
			}

			if (need_to_turn_on) {
				flashlight->turn_on(TORCH_MODE, LUM_LEVEL4);
				thisispdata->flash_on = true;
				camera_agent_set_Preflashon();
				if (thisispdata->s1_3a_state == S1_3A_UNLOCKED_BY_TAF) {
					print_info("turn on TAF_FLASH, FLASH_WAIT --> TAF_FLASH");
					thisispdata->mini_isp_flash_period = TAF_FLASH;
				} else {
					print_info("turn on PRE_FLASH, FLASH_WAIT --> PRE_FLASH");
					thisispdata->mini_isp_flash_period = PRE_FLASH;
				}
				break;
			} else {
				print_info("need't flash, FLASH_WAIT --> NO_FLASH");
				thisispdata->mini_isp_flash_period = NO_FLASH;
			}

		}
		case NO_FLASH:
		{
			u8 af_state = meta_data->data.af_info.converge_state;
			if (af_state == S1_converge_state_OK || af_state == S1_converge_state_FAIL) {
				print_info("NO_FLASH --> FLASH_IDLE, S1_3A_LOCKED");
				thisispdata->mini_isp_flash_period = FLASH_IDLE;
				thisispdata->s1_3a_state = S1_3A_LOCKED;
			}
			break;
		}
		case TAF_FLASH:
		case PRE_FLASH:
		{
			if (thisispdata->s1_3a_state == S1_3A_UNLOCKED_BY_PRE_WITH_AF
				|| thisispdata->s1_3a_state == S1_3A_UNLOCKED_BY_TAF) {  //need to wait AF done
				u8 af_state = meta_data->data.af_info.converge_state;
				if (af_state != S1_converge_state_OK && af_state != S1_converge_state_FAIL)
					break;
			}

			if (meta_data->data.fe_info.preflash1_cal_ready
				&& meta_data->data.fe_info.preflash1_state
				&& meta_data->data.fe_info.mainflash_led_enerage) {

				if (thisispdata->mini_isp_flash_period == TAF_FLASH) {
					flashlight->turn_off();
					thisispdata->flash_on = false;
					print_info("turn_off TAF_FLASH --> FLASH_IDLE, S1_3A_LOCKED");
					thisispdata->mini_isp_flash_period = FLASH_IDLE;
				} else {
					print_info("PRE_FLASH --> MAIN_FLASH, S1_3A_LOCKED");
					thisispdata->mini_isp_flash_period = MAIN_FLASH;
				}
				thisispdata->s1_3a_state = S1_3A_LOCKED;
			}
			break;
		}
		case MAIN_FLASH:
		{

			break;
		}
	}
	mutex_unlock(&thisispdata->mini_isp_flash_period_lock);

}
