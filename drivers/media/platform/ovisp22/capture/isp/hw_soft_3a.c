
#include <asm/io.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/stat.h>
#include <linux/uaccess.h>
#include "k3_isp.h"
#include "k3_ispv1.h"
#include "cam_log.h"
#include <linux/workqueue.h>

#include "sensor_common.h"

#include "hw_soft_3a.h"

extern k3_isp_data *this_ispdata;

static hw_3a_param						hw_3a_data;
void ispv1_hw_3a_switch(u8 on)
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
		if (this_ispdata->sensor->sensor_hdr_movie.set_hdr_movie_switch)
		{
			hdr_movie_on = this_ispdata->sensor->sensor_hdr_movie.get_hdr_movie_switch();
			if(hdr_movie_on)
			GETREG16(REG_ROI_MEM_WIDTH_3A,data_count);
		}
	#endif
		data_count = data_count + hw_3a_data.data_count;
		SETREG16(REG_ROI_MEM_WIDTH_3A,data_count);
		win_top_l = hw_3a_data.ae_param.ae_win_top;
		win_top_h = hw_3a_data.ae_param.ae_win_top >> 8;

		win_left_l = hw_3a_data.ae_param.ae_win_left;
		win_left_h = hw_3a_data.ae_param.ae_win_left >> 8;

		win_height = hw_3a_data.ae_param.ae_win_height;

		win_width = hw_3a_data.ae_param.ae_win_width;

		SETREG8(HW_3A_HIST_SHIFT_REG,hw_3a_data.ae_param.ae_hist_shift);//r_hist_shift
		SETREG8(HW_3A_MEAN_SHIFT_REG,hw_3a_data.ae_param.ae_mean_shift);//r_mean_shift
		//aec agc awb:hist&mean
		SETREG8(HW_3A_WIN_TOP_REG_H,win_top_h);//r_window_top[11:8]
		SETREG8(HW_3A_WIN_TOP_REG_L,win_top_l);//r_window_top[7:0]
		SETREG8(HW_3A_WIN_LEFT_REG_H,win_left_h);//r_window_left[12:8]
		SETREG8(HW_3A_WIN_LEFT_REG_L,win_left_l);//r_window_left[7:0]
		SETREG8(HW_3A_WIN_HEIGHT_REG,win_height);//r_window_height
		SETREG8(HW_3A_WIN_WIDTH_REG,win_width);//r_window_width
		SETREG8(HW_3A_BLC_ENABLE_REG, hw_3a_data.blc_enable); //BLC enable
		SETREG8(HW_3A_AECAGC_MODEL, hw_3a_data.ae_param.ae_win_model);//aec agc &awb mode 0:16x16;1:8x8

		SETREG8(HW_3A_AF_ENABLE_REG, hw_3a_data.af_param.af_enable); //AF stat enable

		SETREG8(HW_3A_AECAGC_ENABLE, hw_3a_data.ae_param.ae_enable); //AEC&AGC&AWB stat enable

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
	print_info("  total data count  %d,3a_count =%d",data_count,hw_3a_data.data_count);

}

int ispv1_set_hw_3a_param(hw_3a_param*data_3a)
{
    if (NULL == data_3a){
        print_error("%s:data_3a is NULL.",__func__);
        return -EFAULT;
    }

	//strncpy(&hw_3a_data, data_3a, sizeof(hw_3a_param));

	hw_3a_data.blc_enable 	= data_3a->blc_enable;
	hw_3a_data.data_count   = data_3a->data_count;
	hw_3a_data.ae_param.ae_enable = data_3a->ae_param.ae_enable;
	hw_3a_data.ae_param.ae_hist_shift = data_3a->ae_param.ae_hist_shift;
	hw_3a_data.ae_param.ae_mean_shift = data_3a->ae_param.ae_mean_shift;
	hw_3a_data.ae_param.ae_win_top = data_3a->ae_param.ae_win_top;
	hw_3a_data.ae_param.ae_win_left = data_3a->ae_param.ae_win_left;
	hw_3a_data.ae_param.ae_win_height = data_3a->ae_param.ae_win_height;
	hw_3a_data.ae_param.ae_win_width = data_3a->ae_param.ae_win_width;
	hw_3a_data.ae_param.ae_win_model = data_3a->ae_param.ae_win_model;

	print_info("%s, blc_enable = %d,data_count=%d,ae_enable=%d",__func__,hw_3a_data.blc_enable,hw_3a_data.data_count,hw_3a_data.ae_param.ae_enable);

    return 0;
}
