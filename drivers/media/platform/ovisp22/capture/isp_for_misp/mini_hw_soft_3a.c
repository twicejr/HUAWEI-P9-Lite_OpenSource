
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

#include "mini_hw_soft_3a.h"

extern mini_k3_isp_data *mini_this_ispdata;

static mini_hw_3a_param						mini_hw_3a_data;
void mini_ispv1_hw_3a_switch(u8 on)
{
	u8 win_top_h,win_top_l;
	u8 win_left_h,win_left_l;
	u8 win_height;
	u8 win_width;
	u32 data_count = 0;
#if 0
	u8 hdr_movie_on = 0;
#endif

    print_info(" %s on = %d",__func__,on);

    if(on == HW_3A_ON)
    {
    #if 0
		if (mini_this_ispdata->sensor->sensor_hdr_movie.set_hdr_movie_switch)
		{
			hdr_movie_on = mini_this_ispdata->sensor->sensor_hdr_movie.get_hdr_movie_switch();
			if(hdr_movie_on)
			GETREG16(REG_ROI_MEM_WIDTH_3A,data_count);
		}
	#endif
		data_count = data_count + mini_hw_3a_data.data_count;
		SETREG16(REG_ROI_MEM_WIDTH_3A,data_count);
		win_top_l = mini_hw_3a_data.ae_param.ae_win_top;
		win_top_h = mini_hw_3a_data.ae_param.ae_win_top >> 8;

		win_left_l = mini_hw_3a_data.ae_param.ae_win_left;
		win_left_h = mini_hw_3a_data.ae_param.ae_win_left >> 8;

		win_height = mini_hw_3a_data.ae_param.ae_win_height;

		win_width = mini_hw_3a_data.ae_param.ae_win_width;

		SETREG8(HW_3A_HIST_SHIFT_REG,mini_hw_3a_data.ae_param.ae_hist_shift);//r_hist_shift
		SETREG8(HW_3A_MEAN_SHIFT_REG,mini_hw_3a_data.ae_param.ae_mean_shift);//r_mean_shift
		//aec agc awb:hist&mean
		SETREG8(HW_3A_WIN_TOP_REG_H,win_top_h);//r_window_top[11:8]
		SETREG8(HW_3A_WIN_TOP_REG_L,win_top_l);//r_window_top[7:0]
		SETREG8(HW_3A_WIN_LEFT_REG_H,win_left_h);//r_window_left[12:8]
		SETREG8(HW_3A_WIN_LEFT_REG_L,win_left_l);//r_window_left[7:0]
		SETREG8(HW_3A_WIN_HEIGHT_REG,win_height);//r_window_height
		SETREG8(HW_3A_WIN_WIDTH_REG,win_width);//r_window_width
		SETREG8(HW_3A_BLC_ENABLE_REG, mini_hw_3a_data.blc_enable); //BLC enable
		SETREG8(HW_3A_AECAGC_MODEL, mini_hw_3a_data.ae_param.ae_win_model);//aec agc &awb mode 0:16x16;1:8x8

		SETREG8(HW_3A_AF_ENABLE_REG, mini_hw_3a_data.af_param.af_enable); //AF stat enable

		SETREG8(HW_3A_AECAGC_ENABLE, mini_hw_3a_data.ae_param.ae_enable); //AEC&AGC&AWB stat enable

		SETREG8(HW_3A_ROI_ENABLE_REG,0x4);
		//SETREG8(HW_3A_FRAME_CTRL_REG,0x05);//ROI smode enable, dual source enable

		/* HW_3A_FRAME_CTRL_REG:bit[0 ] ROI smode enable, dual source enable*/
		SETREG8(HW_3A_FRAME_CTRL_REG,GETREG8(HW_3A_FRAME_CTRL_REG) | SHIFT_BIT_0);
		
		/*HW_3A_ENABLE bit[7][6]:gamma&tonemapping combined , bit[1]:3A  enalbe */
		SETREG8(HW_3A_ENABLE, GETREG8(HW_3A_ENABLE) |SHIFT_BIT_1);
		
		//SETREG8(HW_3A_RAM_ACCESS_ENABLE, 0x8);

    }
    else
    {

		SETREG8(HW_3A_ROI_ENABLE_REG,0x0);
		SETREG8(HW_3A_AECAGC_ENABLE, 0); //AEC&AGC&AWB stat enable 
		SETREG8(HW_3A_AECAGC_MODEL, 0);//aec agc &awb mode 0:16x16;1:8x8
		SETREG8(HW_3A_AF_ENABLE_REG, 0); //AF stat enable

		/*clear bit[0]  ROI smode enable, dual source enable*/
		SETREG8(HW_3A_FRAME_CTRL_REG,GETREG8(HW_3A_FRAME_CTRL_REG) & (~SHIFT_BIT_0));

		/*clear bit[1] ,bit[7]bit[6] for tonemapping&gamma ctrl.*/
		SETREG8(HW_3A_ENABLE, GETREG8(HW_3A_ENABLE) & (~SHIFT_BIT_1));//clear bit[1] //bit[7]bit[6] for tonemapping&gamma ctrl.
		SETREG8(HW_3A_BLC_ENABLE_REG, 0); //BLC enable
		//SETREG8(HW_3A_RAM_ACCESS_ENABLE, 0);
    }

	GETREG16(REG_ROI_MEM_WIDTH_3A,data_count);
	print_info("  total data count  %d,3a_count =%d",data_count,mini_hw_3a_data.data_count);

}

int mini_ispv1_set_hw_3a_param(mini_hw_3a_param*data_3a)
{
    if (NULL == data_3a){
        print_error("%s:data_3a is NULL.",__func__);
        return -EFAULT;
    }

	if(data_3a)
	{
		//strncpy(&mini_hw_3a_data, data_3a, sizeof(mini_hw_3a_param));
		mini_hw_3a_data.blc_enable 	= data_3a->blc_enable;
		mini_hw_3a_data.data_count   = data_3a->data_count;
		mini_hw_3a_data.ae_param.ae_enable = data_3a->ae_param.ae_enable;
		mini_hw_3a_data.ae_param.ae_hist_shift = data_3a->ae_param.ae_hist_shift;
		mini_hw_3a_data.ae_param.ae_mean_shift = data_3a->ae_param.ae_mean_shift;
		mini_hw_3a_data.ae_param.ae_win_top = data_3a->ae_param.ae_win_top;
		mini_hw_3a_data.ae_param.ae_win_left = data_3a->ae_param.ae_win_left;
		mini_hw_3a_data.ae_param.ae_win_height = data_3a->ae_param.ae_win_height;
		mini_hw_3a_data.ae_param.ae_win_width = data_3a->ae_param.ae_win_width;
		mini_hw_3a_data.ae_param.ae_win_model = data_3a->ae_param.ae_win_model;
	}

	print_info("%s, blc_enable = %d,data_count=%d,ae_enable=%d",__func__,mini_hw_3a_data.blc_enable,mini_hw_3a_data.data_count,mini_hw_3a_data.ae_param.ae_enable);

    return 0;
}
