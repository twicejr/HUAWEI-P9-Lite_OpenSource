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
#include <media/v4l2-common.h>
#include <media/v4l2-ioctl.h>
#include <linux/io.h>
#include <linux/bug.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
//#include <linux/android_pmem.h>
#include <linux/device.h>
#include <linux/kernel.h>

#include <linux/time.h>
#include <linux/hisi/hi6xxx-boardid.h>
#include <linux/pm_qos.h>
#include "k3_v4l2_capture.h"
#include "k3_isp.h"

#include "soc_baseaddr_interface.h"
#include "isp_io_mutex.h"


#include "hw_soft_3a.h"
#define DEBUG_DEBUG 0
#define LOG_TAG "K3_ISP"
#include "cam_log.h"

#include "hwa_cam_tune_common.h"

/* MACRO DEFINITION */
#define	WIDTH_ALIGN		0x0f	/* step = 16 */
#define	HEIGHT_ALIGN		0x03	/* step = 4 */
/* #define HEIGHT_ALIGN  0x0f   step = 16  not support 1080p  */

#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
#define DDR_PREVIEW_MIN_PROFILE 360000
#define DDR_CAPTURE_MIN_PROFILE 360000
#define GPU_INIT_BLOCK_PROFILE 120000
#define GPU_BLOCK_PROFILE 360000
#endif

#define DDR_VALID_FREQ_BUF_MAX_LEN      (128)
#define DDR_VALID_FREQ_PATH     "/sys/class/devfreq/ddrfreq/available_frequencies"
#define DDR_CURR_BANDWIDTH_PATH "/sys/class/devfreq/ddrfreq/ddr_bandwidth"

/* VARIABLES AND ARRARYS */
static k3_isp_data isp_data;
static isp_hw_controller *isp_hw_ctl;
static isp_tune_ops *camera_tune_ops;
static camera_flash_state flash_exif = FLASH_OFF;


static camera_capability k3_cap[] = {
	{V4L2_CID_AUTO_WHITE_BALANCE, THIS_AUTO_WHITE_BALANCE},
	{V4L2_CID_DO_WHITE_BALANCE, THIS_WHITE_BALANCE},
	{V4L2_CID_BRIGHTNESS, THIS_BRIGHTNESS},
	{V4L2_CID_CONTRAST, THIS_CONTRAST},
	{V4L2_CID_SCENE, THIS_SCENE},
	{V4L2_CID_SATURATION, THIS_SATURATION},
	{V4L2_CID_ISO, THIS_ISO},
	{V4L2_CID_EFFECT, THIS_EFFECT},
	{V4L2_CID_EXPOSURE_MAX, THIS_EXPOSURE},
	{V4L2_CID_EXPOSURE_STEP, THIS_EXPOSURE_STEP},
	{V4L2_CID_SHARPNESS, THIS_SHARPNESS},
	{V4L2_CID_METERING, THIS_METERING},
	{V4L2_CID_HFLIP, THIS_HFLIP},
	{V4L2_CID_VFLIP, THIS_VFLIP},
	{V4L2_CID_POWER_LINE_FREQUENCY, THIS_ANTI_BANDING},
	{V4L2_CID_ZSL, THIS_ZSL},
};

/* FUNCTION DECLEARATION */
static void k3_isp_set_default(void);
static void k3_isp_calc_zoom(camera_state state, scale_strategy_t scale_strategy, u32 *in_width, u32 *in_height);

#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
static struct pm_qos_request_list g_specialpolicy;
#endif

/*
 **************************************************************************
 * FunctionName: k3_isp_check_config;
 * Description : Set yuv offset according to width, height and format;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_check_config(struct v4l2_pix_format *pixfmt, camera_state state)
{
	print_debug("enter %s", __func__);

	/* calculate U and V offset accroding to ISP out format */
	return isp_hw_ctl->isp_check_config(pixfmt,state);
}

int k3_isp_get_process_mode(void)
{
    #if 0
	isp_hw_ctl->isp_set_process_mode(isp_data.pic_attr[STATE_CAPTURE].sensor_width,
					isp_data.pic_attr[STATE_CAPTURE].sensor_height);
    #endif
	return (int)isp_hw_ctl->isp_get_process_mode();
}


int k3_isp_get_k3_capability(u32 id, u32 *value)
{
	int i;
	print_debug("enter %s", __func__);

	if (V4L2_CID_ZOOM_RELATIVE == id) {
		/* higt byte: 0x10 for zoom_ratio(100,110,120...400) */
		/* low byte: ZOOM_STEPS(1, 1.1, 1.2...4.0) */
		*value = 0x0A001E;
		return 0;
	}

	for (i = 0; i < sizeof(k3_cap) / sizeof(k3_cap[0]); ++i) {
		if (id == k3_cap[i].id) {
			*value = k3_cap[i].value;
			break;
		}
	}

	return 0;
}

void k3_isp_check_flash_level(camera_flash_state state)
{
	camera_flashlight *flashlight = get_camera_flash();
    flash_lum_level preflash_level;
	if(isp_data.sensor->effect != NULL){
		preflash_level =
			isp_data.sensor->effect->flash.flash_capture.preflash_level;
	}else{
		preflash_level = LUM_LEVEL2;
	}

	if (NULL == flashlight) {
		isp_data.flash_flow = FLASH_DONE;
		isp_data.flash_on = false;
		isp_data.flash_state = FLASH_OFF;
		flash_exif = FLASH_OFF;
		return;
	}
#if 0
	if (isp_data.flash_on == true)
		/* now flash light is on, isp is taking a picture */
		return;
#endif

/* disable flash in burst capture mode */
#if 0// def SUPPORT_ZSL_FLASH
	print_info("isp_data.shoot_mode = %d  isp_data.flash_mode = %d this_ispdata->zsl_state = %d state = %d\n",isp_data.shoot_mode,isp_data.flash_mode,k3_isp_get_zsl_state(),state);
	if ((isp_data.sensor->sensor_index == CAMERA_SENSOR_PRIMARY) && (flashlight != NULL) && ((CAMERA_SHOOT_SINGLE == isp_data.shoot_mode)||(CAMERA_ZSL_ON == k3_isp_get_zsl_state()))) {
#else
	if ((isp_data.sensor->sensor_index == CAMERA_SENSOR_PRIMARY) && (flashlight != NULL) && (CAMERA_SHOOT_SINGLE == isp_data.shoot_mode)) {
#endif
		if (FLASH_ON == state) {
			if (((isp_data.flash_mode == CAMERA_FLASH_AUTO) && (true == isp_hw_ctl->isp_is_need_flash(isp_data.sensor))) ||
				isp_data.flash_mode == CAMERA_FLASH_ON) {
				

				isp_data.flash_flow = FLASH_TESTING;
				flashlight->turn_on(TORCH_MODE, preflash_level);
				isp_data.flash_state = state;
				isp_data.flash_on = true;
				isp_hw_ctl->isp_check_flash_prepare();
				flash_exif = FLASH_ON;
				return;
			}
		} else if ((FLASH_OFF == state) && (FLASH_ON == isp_data.flash_state)) {
			isp_data.flash_state = state;
			return;
		}
	}

	isp_data.flash_flow = FLASH_DONE;
	isp_data.flash_on = false;
	isp_data.flash_state = FLASH_OFF;
	flash_exif = FLASH_OFF;
}

int k3_isp_get_flash_result(void)
{
	int ret;
	if ((FLASH_PREFLASH_DONE == isp_data.flash_flow) || (FLASH_DONE == isp_data.flash_flow))
		ret = 0;
	else
		ret = -1;
	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_hw_init_reg;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_hw_init_regs(camera_sensor *sensor)
{
	print_debug("enter %s", __func__);

	if (NULL == sensor) {
		print_error("%s par is NULL", __func__);
		return -EINVAL;
	}

	isp_hw_ctl->isp_hw_init_regs(sensor->interface_type);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_set_camera;
 * Description : Set a new camera sensor to isp;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_set_camera(camera_sensor *open_sensor, camera_sensor *close_sensor)
{
	int ret = 0;

	/* power off the current sensor and exit it */
	if (isp_data.sensor) {
		isp_data.sensor->reset(POWER_OFF);
		isp_data.sensor->power(POWER_OFF);
		isp_data.sensor->exit();
		isp_data.sensor = NULL;
	}

	/* switch to new sensor */
	isp_data.sensor = open_sensor;

	if (isp_data.sensor->init && (0 != isp_data.sensor->init())) {
		print_error("%s: fail to init sensor", __func__);
		ret = -ENODEV;
		goto init_fail;
	}

	if (isp_hw_ctl->set_i2c)
		isp_hw_ctl->set_i2c(&isp_data.sensor->i2c_config);

	if (isp_data.sensor->power && (0 != isp_data.sensor->power(POWER_ON))) {
		print_error("%s: fail to power sensor", __func__);
		ret = -ENODEV;
		goto fail;
	}

	if (isp_data.sensor->reset && (0 != isp_data.sensor->reset(POWER_ON))) {
		print_error("%s: fail to reset sensor", __func__);
		ret = -ENODEV;
		goto fail;
	}

	/* make sure sensor is stable */
	msleep(10);

	if ((isp_data.sensor->check_sensor && (0 != isp_data.sensor->check_sensor()))) {
        print_error("%s: fail to check_sensor", __func__);
		ret = -ENODEV;
		goto fail;
	}

#ifndef OVISP_DEBUG_MODE
	if ((isp_data.sensor->init_isp_reg && (0 != isp_data.sensor->init_isp_reg()))) {
        print_error("%s: fail to init_isp_reg", __func__);
		ret = -ENODEV;
		goto fail;
	}
#endif

    if (isp_data.sensor->isp_location == CAMERA_USE_SENSORISP)
        camera_tune_ops = isp_data.sensor->sensor_tune_ops;
    else
        camera_tune_ops = isp_hw_ctl->isp_tune_ops;

    isp_hw_ctl->refresh_support_fmt(&isp_data.support_pixfmt, &isp_data.pixfmt_count);


    if (isp_data.sensor->get_frame_intervals)
        isp_data.sensor->get_frame_intervals(&isp_data.frame_rate);

    /* y36721 2012-04-12 change. */
    ret = isp_hw_ctl->isp_tune_ops_init(&isp_data);
    if(ret) {
        print_error("%s: fail to isp_tune_ops_init", __func__);
        goto fail;
    }

    return 0;
fail:

	/* sensor not existed */
	isp_data.sensor->reset(POWER_OFF);
	isp_data.sensor->power(POWER_OFF);
	isp_data.sensor->exit();
init_fail:
	isp_data.sensor = NULL;
	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_enum_fmt;
 * Description : enumerate preview format(s) that supported by isp;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_enum_fmt(struct v4l2_fmtdesc *fmt, camera_state state)
{
	print_debug("enter %s", __func__);

	if (fmt->index >= isp_data.pixfmt_count
	    || 0 == isp_data.support_pixfmt[fmt->index]) {
		print_info(" %s invalided parameters, index=%d, max_index=%d",
			   __func__, fmt->index, isp_data.pixfmt_count);
		return -EINVAL;
	}

	fmt->pixelformat = isp_data.support_pixfmt[fmt->index];
	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_enum_framesizes;
 * Description : Enumerate all frame size(s) that supported by camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	print_debug("enter %s()", __func__);

	if (isp_data.sensor->enum_framesizes)
		return isp_data.sensor->enum_framesizes(framesizes);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_enum_frameintervals;
 * Description : Enumerate all frame rate(s) that supported by camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_enum_frameintervals(struct v4l2_frmivalenum *fi)
{
	print_debug("enter %s()", __func__);
	if (isp_data.sensor->enum_frame_intervals)
		return isp_data.sensor->enum_frame_intervals(fi);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_try_frameintervals;
 * Description : Test whether the given frame rate is supported by camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_try_frameintervals(struct v4l2_frmivalenum *fi)
{
	print_debug("enter %s()", __func__);

	if (isp_data.sensor->try_frame_intervals)
		return isp_data.sensor->try_frame_intervals(fi);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_refresh_fmt;
 * Description : refresh pic_attr info according to idi;
 * Input       : struct v4l2_format *fmt,camera_state state;
 * Output      : NA;
 * ReturnValue : int;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_refresh_fmt(struct v4l2_format *fmt,camera_state state)
{
    u32                                 pix_clk;
    u32                                 index;


    print_info("k3_isp_refresh_fmt:");


    if (STATE_PREVIEW == state){
        index = isp_data.sensor->preview_frmsize_index;
    }
    else if (STATE_CAPTURE == state){
        index = isp_data.sensor->capture_frmsize_index;
    }
    else{
        return 0;
    }

    pix_clk = isp_data.sensor->frmsize_list[index].width
            * isp_data.sensor->frmsize_list[index].height
            * isp_data.sensor->frmsize_list[index].fps ;

    /* pix_clk = pix_clk * 1.05 * 1.1 ; */
    pix_clk = pix_clk + pix_clk/10 + pix_clk/20 ;

    print_info("k3_isp_refresh_fmt:v=%d",pix_clk);

    if (pix_clk > isp_data.isp_clk_freq){
        if (fmt->fmt.pix.width <= (isp_data.pic_attr[state].sensor_width / 2)){
            print_info("IDI_SCALEDOWN_2");
            isp_data.pic_attr[state].idi = IDI_SCALE_DOWN_ENABLE | IDI_SCALE_DOWN_2_2;
            isp_data.pic_attr[state].sensor_width  = ((isp_data.pic_attr[state].sensor_width /32)*32);
            isp_data.pic_attr[state].sensor_height = ((isp_data.pic_attr[state].sensor_height /8)*8);
            isp_data.pic_attr[state].startx        = (isp_data.pic_attr[state].startx + 1) / 2;
            isp_data.pic_attr[state].starty        = (isp_data.pic_attr[state].starty + 1) / 2;
            isp_data.pic_attr[state].in_width      = (isp_data.pic_attr[state].sensor_width / 2) ;
            isp_data.pic_attr[state].in_height     = (isp_data.pic_attr[state].sensor_height / 2);
        }
        else if (fmt->fmt.pix.width <= (isp_data.pic_attr[state].sensor_width * 6 / 10)){
            print_info("IDI_SCALEDOWN_1667");
            /* for preview 1080p,cap 6M */
            isp_data.pic_attr[state].idi = IDI_SCALE_DOWN_ENABLE | IDI_SCALE_DOWN_1667_1667;
            isp_data.pic_attr[state].sensor_width  = ((isp_data.pic_attr[state].sensor_width /80)*80);
            isp_data.pic_attr[state].sensor_height =((isp_data.pic_attr[state].sensor_height /20)*20);
            isp_data.pic_attr[state].startx        = (isp_data.pic_attr[state].startx + 1) / 2;
            isp_data.pic_attr[state].starty        = (isp_data.pic_attr[state].starty + 1) / 2;
            isp_data.pic_attr[state].in_width      = (isp_data.pic_attr[state].sensor_width * 6 / 10) ;
            isp_data.pic_attr[state].in_height     = (isp_data.pic_attr[state].sensor_height * 6 /10);
        }
        else {
            print_error("IDI_DISABLE");
            isp_data.pic_attr[state].idi = IDI_SCALE_DOWN_DISABLE;
			return -EINVAL;
        }
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_try_fmt;
 * Description : Test whether the given format is supported by isp and
 *               camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_try_fmt(struct v4l2_format *fmt, camera_state state, camera_setting_view_type view_type)
{
	int i = 0;
	int ret = 0;
	u8 frame_index;
	struct v4l2_frmsizeenum fs;
	struct v4l2_frmsize_discrete sensor_frmsize;
	memset(&fs, 0x00, sizeof(fs));
	memset(&sensor_frmsize, 0x00, sizeof(sensor_frmsize));

	/* check format */
	print_info("%s:fmt->fmt.pix.width=%d,fmt->fmt.pix.height=%d",__func__,fmt->fmt.pix.width,fmt->fmt.pix.height);
	print_info("%s, pixfmt_count[%d], pixelformat[%d], NV12[%d],NV21[%d], YUYV[%d],YUV420[%d]",
		__func__, isp_data.pixfmt_count, fmt->fmt.pix.pixelformat,
	     V4L2_PIX_FMT_NV12, V4L2_PIX_FMT_NV21, V4L2_PIX_FMT_YUYV,V4L2_PIX_FMT_YUV420);
	for (i = 0; i < isp_data.pixfmt_count; ++i) {
		/* format is supported by isp and camera sensor */
		if (fmt->fmt.pix.pixelformat == isp_data.support_pixfmt[i])
			break;
	}
	if (i >= isp_data.pixfmt_count) {
		print_error("%s failed: invalid parameters", __func__);
		return -EINVAL;
	}

	/* check resulotion, small than sensor's max resulotion */
	fs.type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fs.discrete.width = fmt->fmt.pix.width;
	fs.discrete.height = fmt->fmt.pix.height;
	ret = isp_data.sensor->try_framesizes(&fs);
	if (ret != 0) {
		print_error("%s:fail to try sensor framesize, width = %d, height= %d",
		     __func__, fs.discrete.width, fs.discrete.height);
		return -EINVAL;
	}

	sensor_frmsize.width = fs.discrete.width;
	sensor_frmsize.height = fs.discrete.height;
	if (CAMERA_ZSL_ON == k3_isp_get_zsl_state()) {
		ret = isp_data.sensor->set_framesizes(STATE_PREVIEW, &sensor_frmsize, 0, view_type, true);
	} else {
	    ret = isp_data.sensor->set_framesizes(state, &sensor_frmsize, 0, view_type, false);
	}
	if (ret != 0) {
		print_error("%s:fail to set sensor framesize, width = %d, height= %d",
		     __func__, fs.discrete.width, fs.discrete.height);
		return -EINVAL;
	}

	if (state == STATE_PREVIEW)
		frame_index = isp_data.sensor->preview_frmsize_index;
	else
		frame_index = isp_data.sensor->capture_frmsize_index;

	isp_data.pic_attr[state].startx = isp_data.sensor->frmsize_list[frame_index].left;
	isp_data.pic_attr[state].starty = isp_data.sensor->frmsize_list[frame_index].top;

	print_info("startx=%d,starty=%d.\n",isp_data.pic_attr[state].startx,isp_data.pic_attr[state].starty);

	isp_data.pic_attr[state].sensor_width = sensor_frmsize.width;
	isp_data.pic_attr[state].sensor_height = sensor_frmsize.height;

    /* init idi disable to void error from ZSL to non-ZSL.when zsl enable,idi value will be updated.  */
	isp_data.pic_attr[state].idi = IDI_SCALE_DOWN_DISABLE;

	isp_data.pic_attr[state].in_width = (sensor_frmsize.width) & (~WIDTH_ALIGN);
	isp_data.pic_attr[state].in_height = (sensor_frmsize.height) & (~HEIGHT_ALIGN);

	isp_data.pic_attr[state].in_fmt = isp_data.sensor->fmt[state];
	print_debug("==state:%d sensor_width:%d", state, isp_data.pic_attr[state].sensor_width);
	print_debug("==state:%d sensor_height:%d", state, isp_data.pic_attr[state].sensor_height);
	print_debug("==state:%d in_width:%d\n", state, isp_data.pic_attr[state].in_width);
	print_debug("==state:%d in_height:%d\n", state, isp_data.pic_attr[state].in_height);

	/* save view mode for ZOOM_VIEW_MODE */
	isp_data.zoom_ext.view_mode = fmt->fmt.pix.priv;

	if (CAMERA_ZSL_OFF == k3_isp_get_zsl_state()) {
	    ret = k3_isp_refresh_fmt(fmt,state);
	    if (ret != 0) {
    		print_warn("%s:k3_isp_refresh_fmt fail, ret=%d",__func__,ret);
    		return -EINVAL;
	    }
    }

	/* update format info */
	isp_hw_ctl->isp_fill_fmt_info(&fmt->fmt.pix);
	if (state == STATE_CAPTURE)
		memcpy(&isp_data.pic_attr[STATE_IPP], &isp_data.pic_attr[STATE_CAPTURE], sizeof(isp_data.pic_attr[STATE_IPP]));
	/* buffer size */
	fmt->fmt.pix.priv = fmt->fmt.pix.sizeimage;
	if (state == STATE_CAPTURE && ISP_CAPTURE_OFFLINE == k3_isp_get_process_mode()) {
		u32 tmp;
		u32 bitspp = bits_per_pixel(isp_data.pic_attr[state].in_fmt);
		tmp = isp_data.pic_attr[state].sensor_width * isp_data.pic_attr[state].sensor_height * bitspp / 8;
		if (tmp > fmt->fmt.pix.priv) {
			fmt->fmt.pix.priv = tmp;
		}
	}
	print_debug("buffersize exported is %#x", fmt->fmt.pix.priv);

	return 0;
}

#ifdef READ_BACK_RAW
void k3_isp_update_read_ready(u8 buf_used)
{
	isp_hw_ctl->update_read_ready(buf_used);
}
#endif

/*
 **************************************************************************
 * FunctionName: k3_isp_stream_on;
 * Description : Set isp registers according to the parmeters that have been
 *		 set before for preview.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_stream_on(struct v4l2_pix_format *pixfmt,
		     enum v4l2_buf_type buf_type, camera_state state,buffer_arr_t *buf_arr)
{
	struct v4l2_fmtdesc fd;
	int ret = 0;
	flash_lum_level capflash_level;

	if (CAMERA_ZSL_ON == k3_isp_get_zsl_state()) {
        /*for common image, z62576, 20140429, begin*/
		k3_isp_lock_ddr_freq(isp_data.capture_ddr_min_freq);
        /*for common image, z62576, 20140429, end*/

        k3_isp_change_prioty();
	}else{
		k3_isp_try_ddr_freq(pixfmt->sizeimage, state);
	}

	if(isp_data.sensor->effect != NULL){
		capflash_level =
			isp_data.sensor->effect->flash.flash_capture.capflash_level;
	}else{
		capflash_level = LUM_LEVEL5;
	}
	print_debug("enter %s,state=%d", __func__,state);

	memset(&fd, 0x00, sizeof(fd));
	if (k3_isp_check_config(pixfmt, state)) {
		print_error("error : k3_isp_check_config failed!");
		return -EINVAL;
	}

	fd.index = 0;
	fd.type = buf_type;
	if (isp_data.sensor->get_format) {
		isp_data.sensor->get_format(&fd);
		isp_data.pic_attr[state].in_fmt = fd.pixelformat;
	}

	/* FIXME : do we need set sensor's frame intervals,
	 * preview framesize and data format here?
	 */
	if (isp_data.sensor->set_frame_intervals)
		isp_data.sensor->set_frame_intervals(&isp_data.frame_rate);

	isp_data.pic_attr[state].out_width = pixfmt->width;
	isp_data.pic_attr[state].out_height = pixfmt->height;
	isp_data.pic_attr[state].out_stride = pixfmt->width;
	isp_data.pic_attr[state].out_fmt = pixfmt->pixelformat;
	print_debug("out_width=%d, out_height=%d", pixfmt->width, pixfmt->height);

	/*update zoom*/
	k3_isp_calc_zoom(state, YUV_SCALE_FIRST, &isp_data.pic_attr[state].in_width,
			 &isp_data.pic_attr[state].in_height);
	if (CAMERA_ZSL_OFF == k3_isp_get_zsl_state()
		&& hwa_hwscope.mode == HW_SCOPE_ON
		&& state == STATE_CAPTURE) {
		hwa_calc_zoom_with_crop(state, YUV_SCALE_FIRST, &isp_data.pic_attr[state].in_width,
			&isp_data.pic_attr[state].in_height);
	}

    isp_data.zoom_ext.zoom = isp_data.zoom;
    isp_data.zoom_ext.zoom_view_center_xy = (isp_data.pic_attr[STATE_PREVIEW].out_width/2 << 16) | (isp_data.pic_attr[STATE_PREVIEW].out_height/2);
    isp_data.zoom_ext.zoom_view_center_x  = isp_data.pic_attr[STATE_PREVIEW].out_width/2;
    isp_data.zoom_ext.zoom_view_center_y  = isp_data.pic_attr[STATE_PREVIEW].out_height/2;
    isp_data.zoom_ext.full_view_center_x  = isp_data.pic_attr[STATE_PREVIEW].out_width/2;
    isp_data.zoom_ext.full_view_center_y  = isp_data.pic_attr[STATE_PREVIEW].out_height/2;
    isp_data.zoom_ext.raw_view_center_x   = isp_data.pic_attr[STATE_PREVIEW].in_width / 2;
    isp_data.zoom_ext.raw_view_center_y   = isp_data.pic_attr[STATE_PREVIEW].in_height / 2;

	if (isp_data.sensor->isp_location == CAMERA_USE_K3ISP)
		isp_hw_ctl->isp_tune_ops_prepare(state);

	if (isp_data.cold_boot == false) {
		if (isp_data.sensor->update_flip)
			isp_data.sensor->update_flip(isp_data.pic_attr[state].in_width, isp_data.pic_attr[state].in_height);
	}

	if ((isp_data.sensor->config_dphy_clk)&&(false == isp_data.cold_boot)){
		if(isp_data.sensor->reset_dphy){
			isp_data.sensor->reset_dphy();
		}

		isp_data.sensor->config_dphy_clk(state);
	}

	if (state == STATE_PREVIEW) {
#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
		/* pm_qos_update_request(&isp_data.qos_request, DDR_PREVIEW_MIN_PROFILE); */
#endif
		ret = isp_hw_ctl->start_preview(&isp_data.pic_attr[state], isp_data.sensor, isp_data.cold_boot, isp_data.scene);
	} else if (state == STATE_CAPTURE) {
		camera_flashlight *flashlight = get_camera_flash();
		if ((isp_data.sensor->sensor_index == CAMERA_SENSOR_PRIMARY) && (flashlight != NULL)) {
			if (true == isp_data.flash_on) {
				flashlight->turn_on(FLASH_MODE, capflash_level);
			}
		}
#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
		/* pm_qos_update_request(&isp_data.qos_request, DDR_CAPTURE_MIN_PROFILE); */
#endif


        if (CAMERA_ZSL_ON == k3_isp_get_zsl_state())
        {
            isp_data.zsl_ctrl.history_buf_cnt = buf_arr->buf_count;
        }

		ret = isp_hw_ctl->start_capture(&isp_data.pic_attr[state], isp_data.sensor, isp_data.bracket_ev, isp_data.flash_on, isp_data.scene,buf_arr);
	} else {
		print_error("state error for streamon");
		return -EINVAL;
	}

	if (isp_data.cold_boot) {
		if (isp_data.sensor->init_reg && (0 != isp_data.sensor->init_reg())) {
			ret = -EFAULT;
		}

		if (isp_data.sensor->stream_on)
			isp_data.sensor->stream_on(state);

		if (isp_hw_ctl->cold_boot_set)
			isp_hw_ctl->cold_boot_set(isp_data.sensor);

		isp_data.cold_boot = false;
	}
	return ret;
}

int k3_isp_stream_off(camera_state state)
{
	int ret = 0;
	camera_flashlight *flashlight = get_camera_flash();

	/* Mao FIXME */
	if (CAMERA_ZSL_OFF == k3_isp_get_zsl_state()){
	    isp_hw_ctl->isp_set_aecagc_mode(MANUAL_AECAGC);
	}

	if (state == STATE_PREVIEW) {
		if (isp_data.sensor->isp_location == CAMERA_USE_K3ISP)
			isp_hw_ctl->isp_tune_ops_withdraw(state);
		ret = isp_hw_ctl->stop_preview();
		if (true == isp_data.flash_on && flashlight)
			flashlight->turn_off();
	} else {
		ret = isp_hw_ctl->stop_capture();	
		if ((isp_data.sensor->sensor_index == CAMERA_SENSOR_PRIMARY) && (flashlight != NULL)) {
			if (true == isp_data.flash_on && flashlight) {
				flashlight->turn_off();
				if (CAMERA_ZSL_OFF == k3_isp_get_zsl_state()){
				    isp_data.flash_on = false;
				}
			}
		}	
	}

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_set_back_idx;
 * Description : set zsl back index;
 * Input       : buffer_arr_t *ipp_buf_arr
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
inline static int k3_isp_set_back_idx(u8 raw_buf_cnt)
{

    isp_data.zsl_ctrl.history_buf_cnt = raw_buf_cnt;

    /* FIXME:we init back idx to max,however it should be adjusted according
    to frame rate. */

    if (isp_data.zsl_ctrl.focused_frame_cnt >= raw_buf_cnt)
        isp_data.zsl_ctrl.zsl_back_idx = raw_buf_cnt - 1;
    else {
        if (isp_data.zsl_ctrl.focused_frame_cnt > 0)
            isp_data.zsl_ctrl.zsl_back_idx = isp_data.zsl_ctrl.focused_frame_cnt - 1;
        else
            isp_data.zsl_ctrl.zsl_back_idx = 0;
    }


    /* zsl_proc_idx will be changed after execute proc_img_with_preview,we
    allow execute proc_img_with_preview after stop_zap_raw_with_preview.*/
    isp_data.zsl_ctrl.zsl_proc_idx = isp_data.zsl_ctrl.zsl_back_idx;
#ifdef ISP_DEBUG_ZSL
    if (ZSL_IMAGE_BACK_IDX < isp_data.zsl_ctrl.zsl_proc_idx){
        this_ispdata->zsl_ctrl.zsl_proc_idx = ZSL_IMAGE_BACK_IDX;
    }
    else {
        print_warn("%s:ZSL_IMAGE_BACK_IDX=%d,zsl_back_idx=%d",__func__,ZSL_IMAGE_BACK_IDX,zsl_back_idx);
    }
#endif

    print_debug("%s:focused_frame_cnt=%d,zsl_back_idx=%d,zsl_proc_idx=%d",
                __func__,
                isp_data.zsl_ctrl.focused_frame_cnt,
                isp_data.zsl_ctrl.zsl_back_idx,
                isp_data.zsl_ctrl.zsl_proc_idx);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_start_process;
 * Description :
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_start_process(struct v4l2_pix_format *pixfmt, u8 mode,buffer_arr_t *ipp_buf_arr)
{
	pic_attr_t attr_backup;
	int ret;
    memset(&attr_backup, 0, sizeof(pic_attr_t));
	print_debug("enter %s", __func__);
#if 0
	if (k3_isp_check_config(pixfmt)) {
		print_error("check_config fail");
		return -EINVAL;
	}

	isp_data.out_width = pixfmt->width;
	isp_data.out_height = pixfmt->height;
	isp_data.out_stride = pixfmt->bytesperline;
	isp_data.capture_fmt = pixfmt->pixelformat;

	/* update zoom */
	k3_isp_calc_zoom(YUV_SCALE_FIRST, &isp_data.capture_in_width,
			 &isp_data.capture_in_height);
#endif
	/* if ZSL switch on */
    if (CAMERA_ZSL_ON == k3_isp_get_zsl_state()){

        /* we should calc zoom again,because zoom param may be changed after capture stream. */
        if(hwa_hwscope.mode == HW_SCOPE_ON){
            memcpy(&attr_backup, &isp_data.pic_attr[STATE_CAPTURE], sizeof(attr_backup));
            hwa_calc_zoom_with_crop(STATE_CAPTURE,
                                    YUV_SCALE_FIRST,
                                    &isp_data.pic_attr[STATE_CAPTURE].in_width,
                                    &isp_data.pic_attr[STATE_CAPTURE].in_height);
        }
        else{
            k3_isp_calc_zoom(STATE_CAPTURE,
                             YUV_SCALE_FIRST,
                             &isp_data.pic_attr[STATE_CAPTURE].in_width,
                             &isp_data.pic_attr[STATE_CAPTURE].in_height);
        }

        k3_isp_set_zsl_proc_img(mode);

	}

    ret = isp_hw_ctl->start_process(&isp_data.pic_attr[STATE_CAPTURE], mode,ipp_buf_arr);
    if (CAMERA_ZSL_ON == k3_isp_get_zsl_state()){
        if(hwa_hwscope.mode == HW_SCOPE_ON){
            memcpy(&isp_data.pic_attr[STATE_CAPTURE], &attr_backup, sizeof(attr_backup));
        }
    }
    return ret;

}

/*
 **************************************************************************
 * FunctionName: k3_isp_stop_process;
 * Description :
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_stop_process(u8 mode)
{
	print_debug("enter %s", __func__);

    if (CAMERA_ZSL_ON == k3_isp_get_zsl_state()){
        k3_isp_set_zsl_proc_img(mode);
    }
	return isp_hw_ctl->stop_process(mode);
}

/*
 **************************************************************************
 * FunctionName: k3_isp_init;
 * Description : Init isp;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_init(struct platform_device *pdev, data_queue_t *data_queue)
{
	int ret = 0;
	print_debug("enter %s", __func__);

	/* init isp_data struct */
	k3_isp_set_default();

    /*for common image, z62576, 20140429, begin*/
	if (of_property_read_u32(pdev->dev.of_node, "DDR_MIN_PROFILE_PREVIEW", &(isp_data.preview_ddr_min_freq))){
		print_error("%s: read DDR_MIN_PROFILE_PREVIEW error\n", __func__);
    } else {
        print_info("%s: read DDR_MIN_PROFILE_PREVIEW: %u.\n", __func__, isp_data.preview_ddr_min_freq);
    }

	if (of_property_read_u32(pdev->dev.of_node, "DDR_MIN_PROFILE_CAPTURE", &(isp_data.capture_ddr_min_freq))){
		print_error("%s: read DDR_MIN_PROFILE_CAPTURE error\n", __func__);
    } else {
        print_info("%s: read DDR_MIN_PROFILE_CAPTURE: %u.\n", __func__, isp_data.capture_ddr_min_freq);
    }

	if (of_property_read_u32(pdev->dev.of_node, "OV_ISP_CLK_FREQ", &(isp_data.isp_clk_freq))){
		print_error("%s: read OV_ISP_CLK_FREQ error\n", __func__);
    } else {
        print_info("%s: read OV_ISP_CLK_FREQ: %u.\n", __func__, isp_data.isp_clk_freq);
    }

	if (of_property_read_u32(pdev->dev.of_node, "WAIT_FOCUS_TIMEOUT", &(isp_data.focus_timeout))){
		print_error("%s: read WAIT_FOCUS_TIMEOUT error\n", __func__);
    } else {
        print_info("%s: read WAIT_FOCUS_TIMEOUT: %u.\n", __func__, isp_data.focus_timeout);
    }
    /*for common image, z62576, 20140429, end*/

    /* req ddr freq lock */
    //k3_isp_lock_ddr_freq();

#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
	pm_qos_add_request(&g_specialpolicy, PM_QOS_IPPS_POLICY, PM_QOS_IPPS_POLICY_DEFAULT_VALUE);
	pm_qos_add_request(&isp_data.qos_request, PM_QOS_DDR_MIN_PROFILE, DDR_PREVIEW_MIN_PROFILE);
	pm_qos_add_request(&isp_data.qos_request_gpu, PM_QOS_GPU_PROFILE_BLOCK, GPU_INIT_BLOCK_PROFILE);
#endif
	/* init registers */
	isp_hw_ctl = get_isp_hw_controller();

	ret = isp_hw_ctl->isp_hw_init(pdev, data_queue);
	if (0 != ret) {
		print_error("%s isp_hw_init failed", __func__);
		goto fail;
	}
	/*int csi/clk */
	ret = k3_ispio_init(pdev);
	if (0 != ret) {
		print_error("%s k3_ispio_init failed ", __func__);
		goto fail;
	}

	ret = k3_isp_poweron();
	if (0 != ret)
		print_error("%s k3_isp_poweron failed ", __func__);

fail:
	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_exit;
 * Description : Deinit isp;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_exit(void *par)
{
	print_debug("enter %s", __func__);
	if (NULL != isp_data.sensor && isp_data.sensor->isp_location == CAMERA_USE_K3ISP)
		if (isp_hw_ctl->isp_tune_ops_exit)
			isp_hw_ctl->isp_tune_ops_exit();
#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
	pm_qos_update_request(&g_specialpolicy, PM_QOS_IPPS_POLICY_DEFAULT_VALUE);
#endif

	if (isp_data.sensor) {
		isp_data.sensor->reset(POWER_OFF);
		isp_data.sensor->power(POWER_OFF);
		isp_data.sensor->exit();
		isp_data.sensor = NULL;
	}
	k3_isp_poweroff();
	k3_ispio_deinit();
	isp_hw_ctl->isp_hw_deinit();

#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
	pm_qos_remove_request(&isp_data.qos_request);
	pm_qos_remove_request(&g_specialpolicy);
	pm_qos_remove_request(&isp_data.qos_request_gpu);
#endif

    /* cancel and release ddr freq lock */
    k3_isp_unlock_ddr_freq();
	k3_isp_resume_prioty();
	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_poweron;
 * Description : isp device poweroff;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_poweron(void)
{
	print_debug("enter %s", __func__);
	if (isp_data.powered) {
		print_warn("%s, isp aready poweron", __func__);
		return 0;
	}
	isp_data.cold_boot = true;
	isp_data.powered = true;

	return isp_hw_ctl->isp_poweron();
}

/*
 **************************************************************************
 * FunctionName: k3_isp_poweroff;
 * Description : isp device poweroff;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void k3_isp_poweroff(void)
{
	print_debug("enter %s", __func__);
	if (isp_data.powered == false) {
		print_warn("%s, isp is not poweron", __func__);
		return;
	}
	isp_data.powered = false;

	return isp_hw_ctl->isp_poweroff();
}

void k3_isp_auto_focus(int flag)
{
	print_debug("enter %s", __func__);

	
	if (isp_data.sensor->af_enable) {
		camera_tune_ops->isp_auto_focus(flag);
	}
}

int k3_isp_set_focus_mode(camera_focus mode)
{
	print_debug("enter %s", __func__);

	if (isp_data.sensor->af_enable) {
		if (-1 == camera_tune_ops->isp_set_focus_mode(mode))
			return -EINVAL;
		isp_data.focus = mode;
	}
	return 0;
}

int k3_isp_get_focus_mode(void)
{
	print_debug("enter %s", __func__);
	return isp_data.focus;
}

int k3_isp_set_focus_area(focus_area_s *area)
{
	print_debug("enter %s", __func__);
	if (isp_data.sensor->af_enable) {
		if (-1 == camera_tune_ops->isp_set_focus_area(area, isp_data.zoom))
			return -EINVAL;
	}
	return 0;
}

void k3_isp_get_focus_result(focus_result_s *result)
{
	if (isp_data.sensor->af_enable) {
		camera_tune_ops->isp_get_focus_result(result);
	} else {
		result->status = STATUS_FOCUSED;
		result->each_status[0] = STATUS_FOCUSED;
	}
}

/* For bracket information settings */
int k3_isp_set_bracket_info(int *ev)
{
	print_debug("enter %s", __func__);
	if (ev == NULL)
		return -EINVAL;
	memcpy(&isp_data.bracket_ev, ev, sizeof(isp_data.bracket_ev));
	return 0;
}

/* for anti-shaking */
int k3_isp_set_anti_shaking(camera_anti_shaking flag)
{
	int ret = 0;

	print_debug("enter %s", __func__);
	if (isp_data.sensor->isp_location == CAMERA_USE_K3ISP) {
		ret = camera_tune_ops->isp_set_anti_shaking(flag);
		if (!ret)
			isp_data.anti_shaking_enable = flag;
	} else {
		isp_data.anti_shaking_enable = flag;
	}

	return ret;
}

int k3_isp_get_anti_shaking(void)
{
	print_debug("enter %s", __func__);
	return isp_data.anti_shaking_enable;
}

int k3_isp_set_anti_shaking_block(int block)
{
	print_debug("enter %s", __func__);
	if (isp_data.sensor->isp_location == CAMERA_USE_K3ISP) {
		return camera_tune_ops->isp_set_anti_shaking_block(block);
	} else {
		return 0;
	}
}

int k3_isp_get_anti_shaking_coordinate(coordinate_s *coordinate)
{
	print_debug("enter %s", __func__);
	if (isp_data.sensor->isp_location == CAMERA_USE_K3ISP) {
		return camera_tune_ops->isp_get_anti_shaking_coordinate(coordinate);
	} else {
		return 0;
	}
}

/* for awb */
int k3_isp_set_awb_mode(camera_white_balance awb_mode)
{
	int ret = 0;

	print_debug("enter %s", __func__);

	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_awb)
			ret = camera_tune_ops->set_awb(awb_mode);
	if (!ret)
		isp_data.awb_mode = awb_mode;

	return ret;
}

int k3_isp_get_awb_mode(void)
{
	print_debug("enter %s", __func__);
	return isp_data.awb_mode;
}

/* for awb */
int k3_isp_set_awb_lock( int awb_lock)
{
	int ret = 0;

	print_debug("enter %s", __func__);

	if (NULL != isp_hw_ctl)
		if (isp_hw_ctl->isp_set_awb_mode)
			isp_hw_ctl->isp_set_awb_mode((awb_mode_t)awb_lock);

		isp_data.awb_lock = (awb_mode_t)awb_lock;

	return ret;
}
/* for iso */
int k3_isp_get_iso(void)
{
	print_debug("enter %s", __func__);
	return isp_data.iso;
}

int k3_isp_set_iso(camera_iso iso)
{
	int ret = 0;

	print_debug("enter %s", __func__);

	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_iso)
			ret = camera_tune_ops->set_iso(iso);
	if (!ret)
		isp_data.iso = iso;
	return ret;
}

/* for ev */
int k3_isp_set_ev(int ev)
{
	int ret = 0;

	print_debug("enter %s", __func__);

	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_ev)
			ret = camera_tune_ops->set_ev(ev);
	if (!ret)
		isp_data.ev = ev;
	return ret;
}

int k3_isp_get_ev(void)
{
	print_debug("enter %s", __func__);
	return isp_data.ev;
}

/* For metering area information settings */
int k3_isp_set_metering_area(metering_area_s *area)
{
	int ret = 0;
	print_debug("enter %s", __func__);

	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_metering_area) {
			ret |= camera_tune_ops->set_metering_area(area, isp_data.zoom);
			memcpy(&isp_data.ae_area, area, sizeof(metering_area_s));
		}
	return ret;
}

/* for metering mode */
int k3_isp_set_metering_mode(camera_metering metering)
{
	int ret = 0;

	print_debug("enter %s", __func__);
	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_metering_mode)
			ret = camera_tune_ops->set_metering_mode(metering);
	if (!ret)
		isp_data.metering = metering;

	return ret;
}

int k3_isp_get_metering_mode(void)
{
	print_debug("enter %s", __func__);
	return isp_data.metering;
}

int k3_isp_set_gsensor_stat(axis_triple *xyz)
{
	print_debug("enter %s", __func__);

	if (isp_data.sensor->isp_location == CAMERA_USE_K3ISP) {
		return camera_tune_ops->set_gsensor_stat(xyz);
	} else {
		return 0;
	}
}

/* for anti-banding */
int k3_isp_set_anti_banding(camera_anti_banding banding)
{
	int ret = 0;

	print_debug("enter %s", __func__);
	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_anti_banding)
			ret = camera_tune_ops->set_anti_banding(banding);
	if (!ret)
		isp_data.anti_banding = banding;

	return ret;
}

int k3_isp_get_anti_banding(void)
{
	camera_anti_banding banding = CAMERA_ANTI_BANDING_AUTO;

	print_debug("enter %s", __func__);
	if (NULL != camera_tune_ops)
		if (camera_tune_ops->get_anti_banding)
			banding = camera_tune_ops->get_anti_banding();
	if (CAMERA_ANTI_BANDING_AUTO < banding)
		isp_data.anti_banding = banding;

	return isp_data.anti_banding;
}

/* for sharpness */
int k3_isp_set_sharpness(camera_sharpness sharpness)
{
	int ret = 0;

	print_debug("enter %s", __func__);
	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_sharpness)
			ret = camera_tune_ops->set_sharpness(sharpness);
	if (!ret)
		isp_data.sharpness = sharpness;
	return ret;
}

int k3_isp_get_sharpness(void)
{
	print_debug("enter %s", __func__);
	return isp_data.sharpness;
}

/* for saturation */
int k3_isp_set_saturation(camera_saturation saturation)
{
	int ret = 0;

	print_debug("enter %s", __func__);

	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_saturation)
			ret = camera_tune_ops->set_saturation(saturation);
	if (!ret)
			isp_data.saturation = saturation;

	return ret;
}

int k3_isp_get_saturation(void)
{
	print_debug("enter %s", __func__);
	return isp_data.saturation;
}

/* for contrast */
int k3_isp_set_contrast(camera_contrast contrast)
{
	int ret = 0;

	print_debug("enter %s", __func__);

	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_contrast)
			ret = camera_tune_ops->set_contrast(contrast);
	if (!ret)
		isp_data.contrast = contrast;
	return ret;
}

int k3_isp_get_contrast(void)
{
	print_debug("enter %s", __func__);
	return isp_data.contrast;
}

/* for scene */
int k3_isp_set_scene(camera_scene scene)
{
	int ret = 0;

	print_debug("enter %s", __func__);
	if (isp_data.sensor->isp_location == CAMERA_USE_K3ISP) {
		ret = camera_tune_ops->set_scene(scene);
		if (!ret)
			isp_data.scene = scene;
	} else {
		isp_data.scene = scene;
	}

	return ret;
}

int k3_isp_get_scene(void)
{
	print_debug("enter %s", __func__);
	return isp_data.scene;
}

/* for brightness */
int k3_isp_set_brightness(camera_brightness brightness)
{
	int ret = 0;

	print_debug("enter %s", __func__);

	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_brightness)
			ret = camera_tune_ops->set_brightness(brightness);
	if (!ret)
		isp_data.brightness = brightness;
	return ret;
}

int k3_isp_get_brightness(void)
{
	print_debug("enter %s", __func__);
	return isp_data.brightness;
}

/* for effect */
int k3_isp_set_effect(camera_effects effect)
{
	int ret = 0;

	print_debug("enter %s", __func__);
	if (NULL != camera_tune_ops)
		if (camera_tune_ops->set_effect)
			ret = camera_tune_ops->set_effect(effect);
	if (!ret)
		isp_data.effect = effect;

	return ret;
}

int k3_isp_get_effect(void)
{
	print_debug("enter %s", __func__);
	return isp_data.effect;
}

/* for flash mode */
int k3_isp_set_flash_mode(camera_flash flash_mode)
{
	camera_flashlight *flashlight = get_camera_flash();
    flash_lum_level lum_level = isp_data.sensor->effect->flash.videoflash_level;
	print_debug("enter %s", __func__);
	if (isp_data.sensor->sensor_index != CAMERA_SENSOR_PRIMARY) {
		print_error("only primary camera support flash");
		return 0;
	}

	if (flashlight == NULL) {
		print_error("failed to find flash light device");
		return -ENODEV;
	}

	switch (flash_mode) {
	case CAMERA_FLASH_TORCH:
		{
			print_info("set camera flash TORCH MODE");
			flashlight->turn_on(TORCH_MODE, lum_level);
			isp_hw_ctl->isp_set_auto_flash(0, flash_mode);
			break;
		}
	case CAMERA_FLASH_OFF:
		{
			print_info("set camera flash OFF MODE");
			if (((isp_data.flash_mode == CAMERA_FLASH_TORCH) || (isp_data.flash_mode == CAMERA_FLASH_AUTO) || (isp_data.flash_mode == CAMERA_FLASH_ON)
				) && flashlight) {
				flashlight->turn_off();
			}

			isp_hw_ctl->isp_set_auto_flash(0, flash_mode);

			break;
		}
	case CAMERA_FLASH_AUTO:
		{
			if (isp_data.flash_mode == CAMERA_FLASH_TORCH
				&& flashlight) {
				flashlight->turn_off();
			}
			print_info("set camera flash AUTO MODE");
			isp_hw_ctl->isp_set_auto_flash(1, flash_mode);
			break;
		}
	case CAMERA_FLASH_ON:
		{
			if (isp_data.flash_mode == CAMERA_FLASH_TORCH
				&& flashlight) {
				flashlight->turn_off();
			}
			isp_hw_ctl->isp_set_auto_flash(0, flash_mode);
			print_info("set camera flash ON MODE");
			break;
		}
	default:
		{
			print_error("invalid parameter");
			return -EINVAL;
		}
	}

	isp_data.flash_mode = flash_mode;

	return 0;

}

int k3_isp_get_flash_mode(void)
{
	print_debug("enter %s", __func__);
	return flash_exif;
}
/*
 **************************************************************************
 * FunctionName: k3_isp_get_zoom;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : current zoom step;
 * Other       : NA;
 **************************************************************************
*/
int k3_isp_get_zoom(void)
{
	print_debug("Enter Function:%s ", __func__);
	return isp_data.zoom;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_set_zoom;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0:success  other:failed;
 * Other       : NA;
 **************************************************************************
*/
int k3_isp_set_zoom(char preview_running, u32 zoom)
{
	int ret = 0;

    ret = k3_isp_set_zoom_and_center(preview_running,
                                     zoom,
                                     isp_data.zoom_ext.zoom_view_center_x,
                                     isp_data.zoom_ext.zoom_view_center_y);

    if (ret != 0)
    {
        print_warn("%s:k3_isp_set_zoom_and_center fail.ret=%d.",__func__,ret);
        return ret;
    }

    return 0;
}
/*
 **************************************************************************
 * FunctionName: k3_isp_set_zoom_center;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0:success  other:failed;
 * Other       : NA;
 **************************************************************************
*/
int k3_isp_set_zoom_center(char preview_running, u32 zoom_view_center_xy)
{
    u32 zoom_view_center_x = zoom_view_center_xy >> 16;
    u32 zoom_view_center_y = zoom_view_center_xy & 0x0000ffff;

    if ((zoom_view_center_x > isp_data.pic_attr[STATE_PREVIEW].out_width)
    || (zoom_view_center_y > isp_data.pic_attr[STATE_PREVIEW].out_height))
    {
        print_error("overflow.zoom_view_center_x=%d,zoom_view_center_y=%d.",zoom_view_center_x,zoom_view_center_y);
        return 0;
    }


    if (zoom_view_center_xy != isp_data.zoom_ext.zoom_view_center_xy)
    {
        isp_data.zoom_ext.zoom_view_center_xy = zoom_view_center_xy;
        isp_data.zoom_ext.zoom_view_center_x = zoom_view_center_x;
        isp_data.zoom_ext.zoom_view_center_y = zoom_view_center_y;
        print_debug("isp_data.zoom_ext.zoom_view_center_xy=%d,isp_data.zoom_ext.zoom_view_center_x=%d,isp_data.zoom_ext.zoom_view_center_y=%d.",
                   isp_data.zoom_ext.zoom_view_center_xy,
                   isp_data.zoom_ext.zoom_view_center_x,
                   isp_data.zoom_ext.zoom_view_center_y);

    }

    return 0;
}

/*
********************************************************************************
* FunctionName: k3_isp_update_zoom_center;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : 0:success  other:failed;
* Other       : NA;
********************************************************************************
*/
int k3_isp_update_zoom_center(
                            u32             zoom,
                            u32             zoom_view_center_x,
                            u32             zoom_view_center_y)
{
	camera_rect_s full_view_rect;
	camera_rect_s raw_view_rect;

	u32 full_view_center_x;
    u32 full_view_center_y;
    u32 full_view_width_min;
    u32 full_view_height_min;
	u32 full_view_center_x_min;
    u32 full_view_center_y_min;
    u32 full_view_center_x_max;
    u32 full_view_center_y_max;

	u32 raw_view_center_x;
    u32 raw_view_center_y;
	u32 raw_view_center_x_min;
    u32 raw_view_center_y_min;
    u32 raw_view_center_x_max;
    u32 raw_view_center_y_max;
    u32 raw_view_width_min;
    u32 raw_view_height_min;
    int   ret = 0;

    zoom_t     *zoom_ext = &isp_data.zoom_ext;
    pic_attr_t *pic_attr = &isp_data.pic_attr[STATE_PREVIEW];


    if ((zoom_view_center_x ==0) && (zoom_view_center_y ==0))
	{
	    print_error("invalid para.");
	    return -EINVAL;
	}


	print_debug("mirror:old:zoom_ext->zoom=%d,zoom_ext->full_view_center_x=%d,zoom_ext->full_view_center_y=%d,zoom_ext->raw_view_center_x=%d,zoom_ext->raw_view_center_y=%d",
	            zoom_ext->zoom,
	            zoom_ext->full_view_center_x,
	            zoom_ext->full_view_center_y,
	            zoom_ext->raw_view_center_x,
	            zoom_ext->raw_view_center_y);

    /* get full view new center */
    full_view_center_x = zoom_ext->full_view_center_x + zoom_view_center_x*10/(zoom_ext->zoom+10)-((pic_attr->out_width / 2)*10)/(zoom_ext->zoom+10);
    full_view_center_y = zoom_ext->full_view_center_y + zoom_view_center_y*10/(zoom_ext->zoom+10)-((pic_attr->out_height/ 2)*10)/(zoom_ext->zoom+10);
	print_debug("mirror:before:full_view_center_x=%d,full_view_center_y=%d",
	            full_view_center_x,
	            full_view_center_y);

    /* get full view min window */
	full_view_width_min  = ((pic_attr->out_width* 10)/(zoom+10));
	full_view_height_min = ((pic_attr->out_height* 10)/(zoom+10));
	print_debug("mirror:full_view_width_min=%d,full_view_height_min=%d",
	           full_view_width_min,
	           full_view_height_min);

    /* check full view min and max center */
	full_view_center_x_min = full_view_width_min/2;
	full_view_center_y_min = full_view_height_min/2;
	full_view_center_x_max = pic_attr->out_width - full_view_width_min/2;
	full_view_center_y_max = pic_attr->out_height - full_view_height_min/2;
    if (full_view_center_x < full_view_center_x_min) full_view_center_x = full_view_center_x_min;
    if (full_view_center_x > full_view_center_x_max) full_view_center_x = full_view_center_x_max;
    if (full_view_center_y < full_view_center_y_min) full_view_center_y = full_view_center_y_min;
    if (full_view_center_y > full_view_center_y_max) full_view_center_y = full_view_center_y_max;
	print_debug("mirror:full_view_center_x_min=%d,full_view_center_x_max=%d,full_view_center_y_min=%d,full_view_center_y_max=%d",
	            full_view_center_x_min,
	            full_view_center_x_max,
	            full_view_center_y_min,
	            full_view_center_y_max);
	print_debug("mirror:after:zoom_new.full_view_center_x=%d,zoom_new.full_view_center_y=%d",
	            full_view_center_x,
	            full_view_center_y);

    /* convert full view rect to full view rect */
	full_view_rect.left    = 0;
	full_view_rect.top     = 0;
	full_view_rect.width   = full_view_center_x;
	full_view_rect.height  = full_view_center_y;
	ret = k3_isp_yuvrect_to_rawrect2(&full_view_rect, &raw_view_rect);
	if (ret) {
			print_error("k3_isp_yuvrect_to_rawrect2() error=%d.", ret);
			return ret;
	}

	print_debug("mirror:raw_view_rect.width=%d,raw_view_rect.height=%d",
	            raw_view_rect.width,
	            raw_view_rect.height);
	print_debug("mirror:pic_attr->crop_width_for_view_angle=%d,pic_attr->crop_height_for_view_angle=%d",
	            pic_attr->crop_width_for_view_angle,
	            pic_attr->crop_height_for_view_angle);

    /* get raw view new center */
	raw_view_center_x = pic_attr->in_width / 2 - pic_attr->crop_width_for_view_angle / 2 + raw_view_rect.width;
	raw_view_center_y = pic_attr->in_height / 2 - pic_attr->crop_height_for_view_angle / 2 + raw_view_rect.height;
	print_debug("mirror:raw_view_center_x=%d,raw_view_center_y=%d",
	            raw_view_center_x,
	            raw_view_center_y);

    /* check raw view center */
	raw_view_width_min  =((pic_attr->crop_width_for_view_angle * 10)/(zoom+10));
	raw_view_height_min =((pic_attr->crop_height_for_view_angle * 10)/(zoom+10));
	print_debug("mirror:raw_view_width_min=%d,raw_view_height_min=%d",
	           raw_view_width_min,
	           raw_view_height_min);

	raw_view_center_x_min = (raw_view_width_min+1)/2 + 4;//we need to reserve border for firmware
	raw_view_center_y_min = (raw_view_height_min+1)/2 + 4;//we need to reserve border for firmware
	raw_view_center_x_max = pic_attr->in_width - (raw_view_width_min+1)/2 - 4;//we need to reserve border for firmware
	raw_view_center_y_max = pic_attr->in_height - (raw_view_height_min+1)/2 - 4;//we need to reserve border for firmware
    if (raw_view_center_x < raw_view_center_x_min) raw_view_center_x = raw_view_center_x_min;
    if (raw_view_center_x > raw_view_center_x_max) raw_view_center_x = raw_view_center_x_max;
    if (raw_view_center_y < raw_view_center_y_min) raw_view_center_y = raw_view_center_y_min;
    if (raw_view_center_y > raw_view_center_y_max) raw_view_center_y = raw_view_center_y_max;
	print_debug("mirror:raw_view_center_x_min=%d,raw_view_center_x_max=%d,raw_view_center_y_min=%d,raw_view_center_y_max=%d",
	            raw_view_center_x_min,
	            raw_view_center_x_max,
	            raw_view_center_y_min,
	            raw_view_center_y_max);
	print_debug("mirror:after:raw_view_center_x=%d,raw_view_center_y=%d",
	            raw_view_center_x,
	            raw_view_center_y);


    /* save the new */
	zoom_ext->zoom                  = zoom;
	zoom_ext->zoom_view_center_x    = (pic_attr->out_width / 2);//reset to zoom view center
	zoom_ext->zoom_view_center_y    = (pic_attr->out_height/ 2);//reset to zoom view center
	zoom_ext->zoom_view_center_xy   = ((zoom_ext->zoom_view_center_x << 16) | zoom_ext->zoom_view_center_y);
	zoom_ext->full_view_center_x    = full_view_center_x;
	zoom_ext->full_view_center_y    = full_view_center_y;
	zoom_ext->raw_view_center_x     = raw_view_center_x;
	zoom_ext->raw_view_center_y     = raw_view_center_y;
	print_debug("mirror:new:zoom_ext->zoom=%d,zoom_ext->full_view_center_x=%d,zoom_ext->full_view_center_y=%d,zoom_ext->raw_view_center_x=%d,zoom_ext->raw_view_center_y=%d",
	            zoom_ext->zoom,
	            zoom_ext->full_view_center_x,
	            zoom_ext->full_view_center_y,
	            zoom_ext->raw_view_center_x,
	            zoom_ext->raw_view_center_y);

    return 0;
}
/*
 **************************************************************************
 * FunctionName: k3_isp_set_zoom_and_center;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0:success  other:failed;
 * Other       : NA;
 **************************************************************************
*/
int k3_isp_set_zoom_and_center(
                                char    preview_running,
                                u32     zoom,
                                u32     zoom_view_center_x,
                                u32     zoom_view_center_y)
{
	int ret = 0;

#ifdef ISP_ZSL_ZOOM_FIX
	if (CAMERA_ZSL_ON == k3_isp_get_zsl_state())
	{
	    if ((isp_data.pic_attr[STATE_PREVIEW].sensor_width == 1920)
         && (isp_data.pic_attr[STATE_PREVIEW].sensor_height == 1088))
	    {
	        if (isp_data.sensor)
    	    {
    	        if (strncmp(isp_data.sensor->info.name,"sonyimx135",10) == 0)
        	    {
                    print_info("sonyimx135 zoom:%d",zoom);
            	    if ((isp_data.pic_attr[STATE_CAPTURE].out_width == 1920)
        	        && (isp_data.pic_attr[STATE_CAPTURE].out_height == 1088)
             	    && (isp_data.pic_attr[STATE_PREVIEW].out_width == 1280)
             	    && (isp_data.pic_attr[STATE_PREVIEW].out_height == 720))
             	    {
             	        if (zoom == 13)
        	                zoom = 14;
        	        }

        	        if ((isp_data.pic_attr[STATE_CAPTURE].out_width == 480)
        	        && (isp_data.pic_attr[STATE_CAPTURE].out_height == 320)
             	    && (isp_data.pic_attr[STATE_PREVIEW].out_width == 800)
             	    && (isp_data.pic_attr[STATE_PREVIEW].out_height == 480))
             	    {
             	        if (zoom == 8)
        	                zoom = 9;
             	        if (zoom == 17)
        	                zoom = 18;
             	        if (zoom == 21)
        	                zoom = 22;
             	        if (zoom == 28)
        	                zoom = 29;
                    }
            	}
            }
        }
	}
#endif
	print_debug("Enter Function:%s	zoom:%d", __func__, zoom);

	isp_data.zoom = zoom;

    if (VIEW_ZOOM_MODE == isp_data.zoom_ext.view_mode)
    {
        print_debug("mirror:zoom=%d,zoom_view_center_x=%d,zoom_view_center_y=%d",zoom,zoom_view_center_x,zoom_view_center_y);

    	ret = k3_isp_update_zoom_center(zoom,zoom_view_center_x,zoom_view_center_y);
    	if (ret != 0)
    	{
    	    print_warn("%s:k3_isp_update_zoom_center fail.ret=%d.",__func__,ret);
    	}
	}
    isp_data.zoom_ext.zoom = zoom;

	if (preview_running) {
		k3_isp_calc_zoom(STATE_PREVIEW, YUV_SCALE_FIRST,
			&isp_data.pic_attr[STATE_PREVIEW].in_width, &isp_data.pic_attr[STATE_PREVIEW].in_height);
		ret |= isp_hw_ctl->isp_set_zoom(&isp_data.zoom_ext, HIGH_QUALITY_MODE);
		if (isp_data.sensor->af_enable)
			ret |= camera_tune_ops->isp_set_focus_zoom(zoom);
		if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
			ret |= camera_tune_ops->set_metering_area(&isp_data.ae_area, zoom);
			ret |= camera_tune_ops->isp_set_sharpness_zoom(zoom);
		}
	}

#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
	if (0 == ret) {
		if (zoom > 10) { // total is 30 steps
			pm_qos_update_request(&isp_data.qos_request_gpu, GPU_BLOCK_PROFILE);
		} else {
			pm_qos_update_request(&isp_data.qos_request_gpu, GPU_INIT_BLOCK_PROFILE);
		}
	}
#endif
	return ret;
}

int k3_isp_set_ae_lock(int mode)
{
	int ret = 0;

	print_info("enter %s mode = %d", __func__,mode);

	isp_data.ae_lock = mode;

	isp_hw_ctl->isp_set_ae_lock((aecagc_mode_t)mode);

	return ret;
}
int k3_isp_get_exposure_time(void)
{
	int ret = 0;
	print_debug("enter %s", __func__);

	if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
		ret = camera_tune_ops->isp_get_exposure_time();
	} else if (CAMERA_USE_SENSORISP == isp_data.sensor->isp_location) {
		if (isp_data.sensor->get_exposure)
			ret = 1000000 / isp_data.sensor->get_exposure();
	}
	return ret;
}
int k3_isp_get_fps(camera_fps fps)
{
	print_debug("enter %s", __func__);
	return isp_hw_ctl->isp_get_fps(isp_data.sensor, fps);
}

int k3_isp_set_fps(camera_fps fps, u8 value)
{
	int ret = 0;
	print_debug("enter %s", __func__);
	ret = isp_hw_ctl->isp_set_fps(isp_data.sensor, fps, value);
	if ((CAMERA_FPS_MIN == fps) && (CAMERA_SCENE_ACTION == isp_data.scene
					|| CAMERA_SCENE_NIGHT == isp_data.scene
		|| CAMERA_SCENE_NIGHT_PORTRAIT == isp_data.scene
		|| CAMERA_SCENE_THEATRE == isp_data.scene
		|| CAMERA_SCENE_FIREWORKS == isp_data.scene
		|| CAMERA_SCENE_CANDLELIGHT == isp_data.scene)) {
		ret |= k3_isp_set_scene(isp_data.scene);
	}

	return ret;
}

int k3_isp_get_actual_iso(void)
{
	int ret = 0;
	print_debug("enter %s", __func__);

	if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
		ret = camera_tune_ops->isp_get_actual_iso();
	} else if (CAMERA_USE_SENSORISP == isp_data.sensor->isp_location) {
		if (isp_data.sensor->get_gain) {
			ret = isp_data.sensor->get_gain() * 100 / 0x10;
			ret = ((ret / 2) + 5) / 10 * 10;
		}
	}
	return ret;
}

int k3_isp_get_focus_distance(void)
{
	print_debug("enter %s", __func__);
	return camera_tune_ops->isp_get_focus_distance();
}


int k3_isp_get_awb_gain(int withShift)
{
	int ret = 0;

	if (CAMERA_USE_SENSORISP == isp_data.sensor->isp_location) {
		ret = 0;
	} else if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
		ret = camera_tune_ops->isp_get_awb_gain(withShift);
	}
	return ret;
}


int k3_isp_get_focus_code(void)
{
	int ret = 0;

	if (CAMERA_USE_SENSORISP == isp_data.sensor->isp_location) {
		ret = 0;
	} else if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
		ret = camera_tune_ops->isp_get_focus_code();
	}
	return ret;
}

int k3_isp_get_focus_rect(camera_rect_s *rect)
{
	int ret = 0;

	if (CAMERA_USE_SENSORISP == isp_data.sensor->isp_location) {
		ret = 0;
	} else if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
		ret = camera_tune_ops->isp_get_focus_rect(rect);
	}
	return ret;
}

int k3_isp_get_expo_line(void)
{
	int ret = 0;

	if (CAMERA_USE_SENSORISP == isp_data.sensor->isp_location) {
		ret = 0;
	} else if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
		ret = camera_tune_ops->isp_get_expo_line();
	}
	return ret;
}

int k3_isp_get_sensor_vts(void)
{
	int ret = 0;

	if (CAMERA_USE_SENSORISP == isp_data.sensor->isp_location) {
		ret = 0;
	} else if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
		ret = camera_tune_ops->isp_get_sensor_vts();
	}
	return ret;
}

int k3_isp_get_sensor_aperture(void)
{
	if (isp_data.sensor->get_sensor_aperture) {
		return isp_data.sensor->get_sensor_aperture();
	}

	return 0;
}

int k3_isp_get_equivalent_focus(void)
{
	if (isp_data.sensor->get_equivalent_focus) {
		return isp_data.sensor->get_equivalent_focus();
	}

	return 0;
}

int k3_isp_get_current_ccm_rgain(void)
{
	int ret = 0;

	if (CAMERA_USE_SENSORISP == isp_data.sensor->isp_location) {
		ret = 0;
	} else if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
		ret = camera_tune_ops->isp_get_current_ccm_rgain();
	}
	return ret;
}

int k3_isp_get_current_ccm_bgain(void)
{
	int ret = 0;

	if (CAMERA_USE_SENSORISP == isp_data.sensor->isp_location) {
		ret = 0;
	} else if (CAMERA_USE_K3ISP == isp_data.sensor->isp_location) {
		ret = camera_tune_ops->isp_get_current_ccm_bgain();
	}
	return ret;
}

/*
 * YUV windows to RAW windows(after RAW DCW)
 * this function is useful for anti_shaking, aec/agc metering and focus
 * Here we just consider aec/agc metering and focus, focus configure as after RAW DCW.
 * yuv is application defined rect
 */

int k3_isp_yuvrect_to_rawrect(camera_rect_s *yuv, camera_rect_s *raw)
{
	pic_attr_t *attr = &isp_data.pic_attr[STATE_PREVIEW];

	/*scale up */
	if (attr->yuv_up_scale_nscale < YUV_SCALE_DIVIDEND) {
		raw->left = yuv->left * attr->yuv_up_scale_nscale / YUV_SCALE_DIVIDEND  + attr->crop_x;
		raw->top = yuv->top * attr->yuv_up_scale_nscale / YUV_SCALE_DIVIDEND  + attr->crop_y;
		raw->width = yuv->width * attr->yuv_up_scale_nscale / YUV_SCALE_DIVIDEND;
		raw->height = yuv->height * attr->yuv_up_scale_nscale / YUV_SCALE_DIVIDEND;
	} else {
		raw->left = yuv->left * attr->yuv_dcw * attr->yuv_down_scale_nscale / YUV_SCALE_DIVIDEND + attr->crop_x;
		raw->top = yuv->top * attr->yuv_dcw * attr->yuv_down_scale_nscale / YUV_SCALE_DIVIDEND + attr->crop_y;
		raw->width = yuv->width * attr->yuv_dcw * attr->yuv_down_scale_nscale / YUV_SCALE_DIVIDEND;
		raw->height = yuv->height * attr->yuv_dcw * attr->yuv_down_scale_nscale / YUV_SCALE_DIVIDEND;
	}

	return 0;
}


int k3_isp_yuvrect_to_rawrect2(camera_rect_s *yuv, camera_rect_s *raw)
{
	u32 crop_width,	crop_height; /* cropped size of original raw rect */
	u32 scale;
	pic_attr_t *attr = &isp_data.pic_attr[STATE_PREVIEW];

    if ((NULL == yuv) || (NULL == raw)) {
        print_error("%s: yuv == NULL or raw == NULL", __func__);
        return -EINVAL;
    }

	if (attr->in_height * attr->out_width > attr->in_width * attr->out_height) {
		/* do height crop */
		crop_height = attr->in_width * attr->out_height / attr->out_width;
		crop_width = crop_height * attr->out_width / attr->out_height;
	} else {
		/* do width crop */
		crop_width = attr->in_height * attr->out_width / attr->out_height;
		crop_height = crop_width * attr->out_height / attr->out_width;
	}

	scale = (YUV_SCALE_DIVIDEND * crop_width) / attr->out_width;

	/* convert YUV rect to raw rect */
	raw->width = scale * yuv->width / YUV_SCALE_DIVIDEND;
	raw->height = scale * yuv->height / YUV_SCALE_DIVIDEND;
	raw->left = scale * yuv->left / YUV_SCALE_DIVIDEND + (attr->in_width - crop_width) / 2;
	raw->top = scale * yuv->top / YUV_SCALE_DIVIDEND + (attr->in_height - crop_height) / 2;

	return 0;
}


int k3_isp_rawrect_to_yuvrect(camera_rect_s *yuv, camera_rect_s *raw)
{
	pic_attr_t *attr = &isp_data.pic_attr[STATE_PREVIEW];

	if ((raw->left < attr->crop_x) || (raw->top < attr->crop_y)) {
		print_error("raw rect in the croped area");
		return -1;
	}

	/*scale up, fixme: */
	if (attr->yuv_up_scale_nscale < YUV_SCALE_DIVIDEND) {
		yuv->left = (raw->left - attr->crop_x) * YUV_SCALE_DIVIDEND / attr->yuv_up_scale_nscale;
		yuv->top = (raw->top - attr->crop_y) * YUV_SCALE_DIVIDEND / attr->yuv_up_scale_nscale;
		yuv->width = raw->width * YUV_SCALE_DIVIDEND / attr->yuv_up_scale_nscale;
		yuv->height = raw->height * YUV_SCALE_DIVIDEND / attr->yuv_up_scale_nscale;
	} else {
		yuv->left = (raw->left - attr->crop_x) * YUV_SCALE_DIVIDEND / (attr->yuv_dcw * attr->yuv_down_scale_nscale);
		yuv->top = (raw->top - attr->crop_y) * YUV_SCALE_DIVIDEND / (attr->yuv_dcw * attr->yuv_down_scale_nscale);
		yuv->width = raw->width * YUV_SCALE_DIVIDEND / (attr->yuv_dcw * attr->yuv_down_scale_nscale);
		yuv->height =  raw->height * YUV_SCALE_DIVIDEND / (attr->yuv_dcw * attr->yuv_down_scale_nscale);
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_antishaking_rect_out2stat;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_antishaking_rect_out2stat(camera_rect_s *out, camera_rect_s *stat)
{
	pic_attr_t *attr = &isp_data.pic_attr[STATE_PREVIEW];
	print_debug("enter %s", __func__);

	/*scale up */
	if (attr->yuv_up_scale_nscale < YUV_SCALE_DIVIDEND) {
		/*x and y are both 0 */
		stat->left = out->left * attr->yuv_up_scale_nscale / YUV_SCALE_DIVIDEND;
		stat->top = out->top * attr->yuv_up_scale_nscale / YUV_SCALE_DIVIDEND;
		stat->width = out->width * attr->yuv_up_scale_nscale / YUV_SCALE_DIVIDEND;
		stat->height = out->height * attr->yuv_up_scale_nscale / YUV_SCALE_DIVIDEND;
	} else {
		stat->left = out->left;
		stat->top = out->top;
		stat->width = out->width;
		stat->height = out->height;
	}

	return 0;
}


int k3_isp_antishaking_rect_stat2out(camera_rect_s *out, camera_rect_s *stat)
{
	pic_attr_t *attr = &isp_data.pic_attr[STATE_PREVIEW];
	print_debug("enter %s", __func__);

	/*scale up */
	if (attr->yuv_up_scale_nscale < YUV_SCALE_DIVIDEND) {
		/*width and height are both 0 */
		out->left = stat->left * YUV_SCALE_DIVIDEND  / attr->yuv_up_scale_nscale;
		out->top = stat->top * YUV_SCALE_DIVIDEND  / attr->yuv_up_scale_nscale;
		out->width = stat->width * YUV_SCALE_DIVIDEND / attr->yuv_up_scale_nscale;
		out->height = stat->height * YUV_SCALE_DIVIDEND / attr->yuv_up_scale_nscale;
	} else {
		out->left = stat->left;
		out->top = stat->top;
		out->width = stat->width;
		out->height = stat->height;
	}
	return 0;
}


/*
 **************************************************************************
 * FunctionName: k3_isp_calc_zoom;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void k3_isp_calc_zoom(camera_state state, scale_strategy_t scale_strategy, u32 *in_width, u32 *in_height)
{
	u32 scale_width;
	u32 scale_height;
	u32 temp_width;
	u32 temp_height;
	u32 scale;
	u32 ratio;
	u32 temp;
	pic_attr_t *attr = &isp_data.pic_attr[state];

	print_debug("%s, zoom=%d, in_width=%d, in_height=%d",
		    __func__, isp_data.zoom, *in_width, *in_height);

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

	attr->crop_width_for_view_angle = temp_width;
	attr->crop_height_for_view_angle = temp_height;

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

	temp = isp_zoom_to_ratio(isp_data.zoom, isp_data.video_stab);

	/* if scale down ratio < zoom in ratio ,
	   we need crop and yuv scale up */
	if (scale * ZOOM_BASE <= YUV_SCALE_DIVIDEND * temp) {
		/* first we get zoom in ratio */
		attr->yuv_up_scale_nscale = (scale * ZOOM_BASE) / temp;
		print_debug("yuv_up_scale_nscale = %d", attr->yuv_up_scale_nscale);
		/* we do not need yuv scale down*/
		attr->yuv_dcw = 1;
		attr->yuv_down_scale_nscale = YUV_SCALE_DIVIDEND;
		print_debug("raw_scale_down = %d, yuv_down_scale_nscale = %d",
			    attr->raw_scale_down, attr->yuv_down_scale_nscale);
	} else {
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
		print_debug("yuv_dcw=%d, yuv_down_scale_nscale = %d, yuv_up_scale_nscale=%d",
			attr->yuv_dcw, attr->yuv_down_scale_nscale,
			attr->yuv_up_scale_nscale);
	}

	attr->crop_width = temp_width * ZOOM_BASE / temp;
	attr->crop_height = temp_height * ZOOM_BASE / temp;

	if ((attr->crop_width * temp) < (temp_width * ZOOM_BASE))
		attr->crop_width++;
	if ((attr->crop_height * temp) < (temp_height * ZOOM_BASE))
		attr->crop_height++;

	if (isp_data.zoom != 0) {
		if ((YUV_SCALE_DIVIDEND !=  attr->yuv_up_scale_nscale)
		||(YUV_SCALE_DIVIDEND !=  attr->yuv_down_scale_nscale)
		||(1 != attr->yuv_dcw)){


			/*To avoid edge color anomalies need more 4 pixel in zoom mode*/
			attr->crop_width = (attr->crop_width & ~0x03) + 4;
			attr->crop_height = (attr->crop_height & ~0x03) + 4;

		}else{
			if(attr->crop_width&0x03)
			attr->crop_width = (attr->crop_width & ~0x03) + 4;
			if(attr->crop_height&0x03)
			attr->crop_height = (attr->crop_height & ~0x03) + 4;
		}

	}
	attr->crop_x = (attr->yuv_in_width - attr->crop_width) / 2;
	attr->crop_y = (attr->yuv_in_height - attr->crop_height) / 2;


        /*make sure the crop start is even*/
        attr->crop_x = (attr->crop_x / 2) * 2;
        attr->crop_y = (attr->crop_y / 2) * 2;

	print_info("crop_width = %d, crop_height = %d, crop_x = %d, crop_y = %d",
	     attr->crop_width, attr->crop_height, attr->crop_x, attr->crop_y);
}

int k3_isp_set_hflip(int flip)
{
	print_debug("enter %s", __func__);

	if (isp_data.sensor->set_hflip)
		return isp_data.sensor->set_hflip(flip);

	return 0;
}
int k3_isp_get_hflip(void)
{
	print_debug("enter %s()", __func__);

	if (isp_data.sensor->get_hflip)
		return isp_data.sensor->get_hflip();
	return 0;
}
int k3_isp_set_vflip(int flip)
{
	print_debug("enter %s", __func__);

	if (isp_data.sensor->set_vflip)
		return isp_data.sensor->set_vflip(flip);
	return 0;
}
int k3_isp_get_vflip(void)
{
	print_debug("enter %s()", __func__);

	if (isp_data.sensor->get_vflip)
		return isp_data.sensor->get_vflip();
	return 0;
}


void k3_isp_set_shoot_mode(camera_shoot_mode shoot_mode)
{
	print_info("enter %s, shot mode is %d", __func__, shoot_mode);
	isp_data.shoot_mode = shoot_mode;
}

void k3_isp_set_pm_mode(u8 pm_mode)
{
#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
	pm_qos_update_request(&g_specialpolicy, pm_mode);
#endif
}

int k3_isp_get_current_vts(void)
{
	print_debug("enter %s()", __func__);
	return isp_hw_ctl->isp_get_current_vts(isp_data.sensor);
}

int k3_isp_get_current_fps(void)
{
	print_debug("enter %s()", __func__);
	return isp_hw_ctl->isp_get_current_fps(isp_data.sensor);
}
int k3_isp_get_band_threshold(void)
{
	print_debug("enter %s()", __func__);
	return isp_hw_ctl->isp_get_band_threshold(isp_data.sensor, isp_data.anti_banding);
}

void k3_isp_set_fps_lock(int lock)
{
	print_debug("enter %s()", __func__);
	camera_tune_ops->isp_set_fps_lock(lock);
}

/*
 **************************************************************************
 * FunctionName: k3_isp_set_zsl_state;
 * Description : turn ZSL or turn off ZSL;
 * Input       : zsl_state;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void k3_isp_set_zsl_state(camera_zsl zsl_state)
{
	print_debug("enter %s, ZSL state:old is %d,new is %d.", __func__, isp_data.zsl_ctrl.zsl_state, zsl_state);
	isp_data.zsl_ctrl.zsl_state = zsl_state;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_get_zsl_state;
 * Description : get zsl state;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
camera_zsl k3_isp_get_zsl_state()
{
	return isp_data.zsl_ctrl.zsl_state;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_set_zsl_proc;
 * Description : set zsl proc type ;
 * Input       : zsl_proc;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void k3_isp_set_zsl_proc(camera_zsl_proc zsl_proc)
{
	print_info("enter %s, ZSL process type:old is %d,new is %d.", __func__, isp_data.zsl_ctrl.zsl_proc_mode, zsl_proc);
	isp_data.zsl_ctrl.zsl_proc_mode = zsl_proc;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_get_zsl_proc;
 * Description : get zsl proc;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : camera_zsl_proc;
 * Other       : NA;
 **************************************************************************
 */
camera_zsl_proc k3_isp_get_zsl_proc()
{
	return isp_data.zsl_ctrl.zsl_proc_mode;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_set_zsl_cap_raw;
 * Description : start cap raw or stop cap raw;if raw_buf_cnt=0,stop cap raw,else start cap raw
 * Input       : raw_buf_cnt,;
 * Output      : NA;
 * ReturnValue : void;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_set_zsl_cap_raw(u8 raw_buf_cnt,struct v4l2_pix_format *pixfmt,buffer_arr_t *buf_arr)
{
    u8                                  cnt = 0;
    int                                 ret = 0;

    if (CAMERA_ZSL_ON != k3_isp_get_zsl_state()){
        print_error("%s:zsl_state is off.",__func__);
        return -EINVAL;
    }

    if (false == isp_data.zsl_ctrl.zsl_cap_valid){
        print_warn("%s:zsl_cap_valid=false.",__func__);
        return -EPERM;
    }

    if (raw_buf_cnt >= 1){
        /* if ZSL switch on,need to restart capture data. */
        print_debug("%s:restart capture raw.reset raw buf=%d",__func__,raw_buf_cnt);
        buf_arr->buf_count = raw_buf_cnt;

        if (CAMERA_ZSL_ONLINE == k3_isp_get_zsl_proc()){
            k3_isp_set_zsl_cap_cmd(CAMERA_ZSL_CAP_CMD_RESUME);
        }
        else
        {
            k3_isp_set_zsl_cap_cmd(CAMERA_ZSL_CAP_CMD_START);
        }

        ret = k3_isp_stream_on(pixfmt, V4L2_BUF_TYPE_VIDEO_CAPTURE, STATE_CAPTURE,buf_arr);
        if (ret != 0){
            print_warn("%s:k3_isp_stream_on fail,ret=%d.",__func__,ret);
        }

        if (false == isp_data.zsl_ctrl.zsl_cap_valid){
            print_warn("%s:zsl_cap_valid=false.",__func__);
            ret = -EPERM;
        }

        return ret;
    } else {
        /* set zsl back index and proc back idx*/
        k3_isp_set_back_idx(buf_arr->buf_count);

        /* we should stream off capturing stream at first. */
        if (CAMERA_ZSL_ONLINE == k3_isp_get_zsl_proc()){
            isp_data.zsl_ctrl.zsl_cap_cmd = CAMERA_ZSL_CAP_CMD_SUSPEND;
        }
        else{
            isp_data.zsl_ctrl.zsl_cap_cmd = CAMERA_ZSL_CAP_CMD_STOP;
        }

        while (cnt < CAPTURE_STREAM_TRY_MAX_TIMES) {
            if (false == isp_data.zsl_ctrl.zsl_cap_valid)
            {
                break;
            }

            cnt = cnt+1;

            if(isp_data.flash_on == false){
            	ret = k3_isp_stream_off(STATE_CAPTURE);
	    }
            if (ret != 0)
            {
                print_error("%s:k3_isp_stream_off fail,ret=%d,cnt=%d,max=%d",__func__,ret,cnt,CAPTURE_STREAM_TRY_MAX_TIMES);

                if (false == isp_data.zsl_ctrl.zsl_cap_valid)
                {
                    break;
                }

                if (cnt == CAPTURE_STREAM_TRY_MAX_TIMES)
                {
                    print_error("%s:k3_isp_stream_off,reach cnt=%d",__func__,CAPTURE_STREAM_TRY_MAX_TIMES);
                    break;
                }

                ret = k3_isp_stream_on(pixfmt, V4L2_BUF_TYPE_VIDEO_CAPTURE, STATE_CAPTURE, buf_arr);
                if (ret != 0){
                    print_error("%s:k3_isp_stream_on fail,ret=%d",__func__,ret);
                }
            } else {
                break;
            }
        }

        if (false == isp_data.zsl_ctrl.zsl_cap_valid){
            print_warn("%s:zsl_cap_valid = false.cancel cap.",__func__);
            ret = -EPERM;
        }

        return ret;

    }
}



/*
 **************************************************************************
 * FunctionName: k3_isp_get_zsl_proc_img;
 * Description : get zsl process image type;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : u8;
 * Other       : NA;
 **************************************************************************
 */
u8 k3_isp_get_zsl_proc_img()
{
	return isp_data.zsl_ctrl.zsl_proc_type;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_set_zsl_proc_img;
 * Description : set zsl process image type;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : void;
 * Other       : NA;
 **************************************************************************
 */
void k3_isp_set_zsl_proc_img(u8 zsl_proc_img)
{
    isp_data.zsl_ctrl.zsl_proc_type = zsl_proc_img;
}


/*
 **************************************************************************
 * FunctionName: k3_isp_set_zsl_cap_cmd;
 * Description : set zsl cap stream cmd;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : camera_zsl_cap_cmd;
 * Other       : NA;
 **************************************************************************
 */
void k3_isp_set_zsl_cap_cmd(camera_zsl_cap_cmd zsl_cap_cmd)
{
	print_info("enter %s.old cmd=%d,new cmd=%d.", __func__,isp_data.zsl_ctrl.zsl_cap_cmd,zsl_cap_cmd);
	isp_data.zsl_ctrl.zsl_cap_cmd = zsl_cap_cmd;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_set_zsl_proc_valid;
 * Description : disable zsl_proc_valid;
 * Input       : zsl_proc_valid;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void k3_isp_set_zsl_proc_valid(bool zsl_proc_valid)
{
	print_debug("enter %s, zsl_proc_valid:old is %d,new is %d.", __func__, isp_data.zsl_ctrl.zsl_proc_valid, zsl_proc_valid);
	isp_data.zsl_ctrl.zsl_proc_valid = zsl_proc_valid;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_set_zsl_cap_valid;
 * Description : disable zsl_cap_valid;
 * Input       : zsl_cap_valid;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void k3_isp_set_zsl_cap_valid(bool zsl_cap_valid)
{
	print_debug("enter %s, zsl_cap_valid:old is %d,new is %d.", __func__, isp_data.zsl_ctrl.zsl_cap_valid, zsl_cap_valid);
	isp_data.zsl_ctrl.zsl_cap_valid = zsl_cap_valid;
}


void k3_isp_set_video_stabilization(int bStabilization)
{
	print_debug("enter %s()", __func__);
	isp_data.video_stab = bStabilization;
}

void k3_isp_get_yuv_crop_rect(crop_rect_s *rect)
{
	print_debug("enter %s()", __func__);
	isp_hw_ctl->isp_get_yuv_crop_rect(rect);
}

void k3_isp_set_yuv_crop_pos(int point)
{
	print_debug("enter %s()", __func__);
	isp_hw_ctl->isp_set_yuv_crop_pos(point);
}

void k3_isp_set_process_mode(capture_type process_mode)
{
 	print_info("enter %s()", __func__);
	isp_hw_ctl->isp_set_process_mode(process_mode);
}
void k3_isp_set_hw_3a_mode(int mode)
{
	print_info("hw_3a_switch current = %d,new = %d",isp_data.hw_3a_switch,mode);
	if(isp_data.hw_3a_switch != mode)
	{
	   	 isp_data.hw_3a_switch = mode;
		ispv1_hw_3a_switch(isp_data.hw_3a_switch);
	}
}



/*
 **************************************************************************
 * FunctionName: k3_isp_set_default;
 * Description : Set default value of v4l2_callback & isp_data struct;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void k3_isp_set_default(void)
{
	camera_state state = 0;
	/* init data struct */
	memset(&isp_data.bracket_ev, 0, sizeof(isp_data.bracket_ev));
	for (state = STATE_PREVIEW; state < STATE_MAX; state++) {
		isp_data.pic_attr[state].sensor_width		= 640;
		isp_data.pic_attr[state].sensor_height		= 480;
		isp_data.pic_attr[state].idi            = IDI_SCALE_DOWN_DISABLE;
		isp_data.pic_attr[state].in_width		= 640;
		isp_data.pic_attr[state].in_height		= 480;
		isp_data.pic_attr[state].startx			= 0;
		isp_data.pic_attr[state].starty			= 0;
		isp_data.pic_attr[state].out_width		= 640;
		isp_data.pic_attr[state].out_height		= 480;
		isp_data.pic_attr[state].raw_scale_down		= 1;
		isp_data.pic_attr[state].yuv_dcw		= 1;
		isp_data.pic_attr[state].yuv_in_width		= 640;
		isp_data.pic_attr[state].yuv_in_height		= 480;
		isp_data.pic_attr[state].yuv_down_scale_nscale	= YUV_SCALE_DIVIDEND;
		isp_data.pic_attr[state].yuv_up_scale_nscale	= YUV_SCALE_DIVIDEND;
		isp_data.pic_attr[state].crop_x		= 0; /* isp_data.pic_attr[state].startx; */
		isp_data.pic_attr[state].crop_y		= 0; /* isp_data.pic_attr[state].starty; */
		isp_data.pic_attr[state].crop_width		= isp_data.pic_attr[state].in_width;
		isp_data.pic_attr[state].crop_height		= isp_data.pic_attr[state].in_height;
		isp_data.pic_attr[state].in_fmt			= V4L2_PIX_FMT_RAW10;
		isp_data.pic_attr[state].out_fmt		= V4L2_PIX_FMT_NV12;
		isp_data.video_stab = 0;
	}
	isp_data.zoom				= 0;
	isp_data.zoom_ext.zoom      = 0;

	isp_data.sensor				= NULL;
	isp_data.support_pixfmt			= NULL;
	isp_data.pixfmt_count			= 0;

	isp_data.fps_mode	=	CAMERA_FRAME_RATE_AUTO;
	isp_data.assistant_af_flash = false;
	isp_data.af_need_flash = false;

	isp_data.shoot_mode = CAMERA_SHOOT_SINGLE;

	isp_data.zsl_ctrl.zsl_state              = CAMERA_ZSL_OFF;
 	isp_data.zsl_ctrl.zsl_online_enable      = true;/* zsl_online_enable to control wethler use online when capture small picture. */
	isp_data.zsl_ctrl.zsl_proc_mode          = CAMERA_ZSL_OFFLINE;
	isp_data.zsl_ctrl.zsl_cap_cmd            = CAMERA_ZSL_CAP_CMD_START;
	isp_data.zsl_ctrl.zsl_cap_int            = 1;	/* frame interval in capture stream */
	isp_data.zsl_ctrl.zsl_proc_type          = 0;   /* process image type */
	isp_data.zsl_ctrl.zsl_back_idx           = 0;	/* zsl image back index */
    isp_data.zsl_ctrl.zsl_proc_idx           = 0;   /* zsl image process index */
	isp_data.zsl_ctrl.history_buf_cnt        = 0;   /* zsl history buffer cnt */
	isp_data.zsl_ctrl.history_buf_idx        = 0;   /* zsl capture buffer index */
	isp_data.zsl_ctrl.focused_frame_cnt      = 1;
	isp_data.hw_3a_switch					 = HW_3A_OFF;

	isp_data.ae_lock                         = AUTO_AECAGC;
	isp_data.awb_lock                        = AUTO_AWB;

	isp_data.ddr_lock_freq		= 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_zsl_try_fmt;
 * Description : set ZSL format;
 * Input       : struct v4l2_format *preview_fmt,
                 struct v4l2_format *capture_fmt,
                 camera_setting_view_type preview_view_type,
                 camera_setting_view_type capture_view_type
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_zsl_try_fmt(pic_fmt_s *pic_fmt,char preview_state)
{

    struct v4l2_format       *preview_fmt = pic_fmt->preview_fmt;
    struct v4l2_format       *capture_fmt = pic_fmt->capture_fmt;
    struct v4l2_format       *ipp_fmt     = pic_fmt->ipp_fmt;
    camera_setting_view_type preview_view_type = pic_fmt->preview_view_type;
    camera_setting_view_type capture_view_type = pic_fmt->capture_view_type;

    camera_state                        state_try;
    camera_setting_view_type            view_type_try;
    struct v4l2_format                  *fmt_try;
    camera_state                        state_refresh;
    camera_setting_view_type            view_type_refresh;
    struct v4l2_format                  *fmt_refresh;
    int                                 ret;

    print_info("enter %s.",__func__);
    print_info("%s:capture_fmt->fmt.pix.width=%d,capture_fmt->fmt.pix.height=%d",__func__,capture_fmt->fmt.pix.width,capture_fmt->fmt.pix.height);
    print_info("%s:preview_fmt->fmt.pix.width=%d,preview_fmt->fmt.pix.height=%d",__func__,preview_fmt->fmt.pix.width,preview_fmt->fmt.pix.height);

    /* FIXME:switch between zsl online and offline while preview is running. */
    if (0 == preview_state)
    {
        /* judge which fmt to try sensor output resolution */
        if ((capture_fmt->fmt.pix.width * capture_fmt->fmt.pix.height) >
            (preview_fmt->fmt.pix.width * preview_fmt->fmt.pix.height) )
        {
            print_info("%s:try capture.",__func__);
            state_try           = STATE_CAPTURE;
            view_type_try       = capture_view_type;
            fmt_try             = capture_fmt;

            state_refresh       = STATE_PREVIEW;
            view_type_refresh   = preview_view_type;
            fmt_refresh         = preview_fmt;
        } else {
            print_info("%s:try preview.",__func__);
            state_try           = STATE_PREVIEW;
            view_type_try       = preview_view_type;
            fmt_try             = preview_fmt;

            state_refresh       = STATE_CAPTURE;
            view_type_refresh   = capture_view_type;
            fmt_refresh         = capture_fmt;
        }

        /* try sensor output resolution */
        ret = k3_isp_try_fmt(fmt_try, state_try, view_type_try);
        if (ret != 0) {
            print_error("%s:k3_isp_try_fmt fail.ret = %d.",__func__,ret);
            return ret;
        }

    	/* when pre 1920x1080,cap 6M,we need 3280x1840 */
    	if( (isp_data.pic_attr[state_try].sensor_width == 3264)  && (fmt_refresh->fmt.pix.width == 1920)){
       		 int  width = fmt_try->fmt.pix.width;
    		 fmt_try->fmt.pix.width = 3280;
    		 print_info("%s:reset fmt_try->fmt.pix.width = %d.",__func__,fmt_try->fmt.pix.width);
    	        /* try sensor output resolution */
    	        ret = k3_isp_try_fmt(fmt_try, state_try, view_type_try);
    	        if (ret != 0) {
    	            print_error("%s:k3_isp_try_fmt fail.ret = %d.",__func__,ret);
    	            return ret;
    	        }
    		 fmt_try->fmt.pix.width = width;

    	}
    }
    else {
        print_info("preview already running,try preview.");
        state_try           = STATE_PREVIEW;
        view_type_try       = preview_view_type;
        fmt_try             = preview_fmt;

        state_refresh       = STATE_CAPTURE;
        view_type_refresh   = capture_view_type;
        fmt_refresh         = capture_fmt;
    }

    /* refresh another fmt */
    ret = k3_isp_zsl_refresh_fmt(preview_fmt, fmt_try, fmt_refresh, state_try, state_refresh);
    if (ret != 0) {
        print_error("%s:k3_isp_zsl_refresh_fmt fail.ret = %d.",__func__,ret);
        return ret;
    }

    /* set private fmt  */
    ret = k3_isp_zsl_set_private_fmt(ipp_fmt);
    if (ret != 0) {
        print_error("%s:k3_isp_zsl_set_private_fmt fail.ret = %d.",__func__,ret);
        return ret;
    }

    print_info("leave %s.",__func__);
    return 0;

}
/*
 **************************************************************************
 * FunctionName: k3_isp_zsl_set_private_fmt;
 * Description : set private format for capture RAW buffer;
 * Input       : void
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
 int k3_isp_zsl_set_private_fmt(struct v4l2_format *fmt_private)
 {
    if (NULL == fmt_private)
    {
        return -EINVAL;
    }

    print_debug("enter %s.",__func__);

    fmt_private->fmt.pix.pixelformat    = isp_data.pic_attr[STATE_CAPTURE].in_fmt;
    fmt_private->fmt.pix.width          = isp_data.pic_attr[STATE_CAPTURE].sensor_width;
    fmt_private->fmt.pix.height         = isp_data.pic_attr[STATE_CAPTURE].sensor_height;

	isp_hw_ctl->isp_fill_fmt_info(&fmt_private->fmt.pix);
	fmt_private->fmt.pix.priv = fmt_private->fmt.pix.sizeimage;

	return 0;
 }



/*
 **************************************************************************
 * FunctionName: k3_isp_zsl_calc_idi;
 * Description : calc idi;
 * Input       : struct v4l2_format *preview_fmt,
                 struct v4l2_format *fmt_try,
                 camera_setting_view_type preview_view_type,
                 camera_setting_view_type capture_view_type,
 * Output      : int                *isp_idi_scale_down;
 * ReturnValue : int;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_zsl_calc_idi(struct v4l2_format *preview_fmt,
                             struct v4l2_format *fmt_try,
                             camera_state        state_try,
                             camera_state        state_refresh,
                             int                *isp_idi_scale_down)
{
    u32                                 pix_clk;

    print_info("%s:fmt_try->fmt.pix.width=%d,isp_data.pic_attr[state_try].sensor_width=%d.",
               __func__,
               fmt_try->fmt.pix.width,
               isp_data.pic_attr[state_try].sensor_width);

    pix_clk = isp_data.sensor->frmsize_list[isp_data.sensor->preview_frmsize_index].width
            * isp_data.sensor->frmsize_list[isp_data.sensor->preview_frmsize_index].height
            * isp_data.sensor->frmsize_list[isp_data.sensor->preview_frmsize_index].fps ;
#if 0
    /* sensor use scale down to output the frame */
    if ((isp_data.sensor->frmsize_list[isp_data.sensor->preview_frmsize_index].width==1920)
      && (isp_data.sensor->frmsize_list[isp_data.sensor->preview_frmsize_index].view_type==VIEW_FULL))
    {
        pix_clk = (pix_clk*3/5);
    }
#endif
    /* pix_clk = pix_clk * 1.05 * 1.1 ; */
    pix_clk = pix_clk + pix_clk/10 + pix_clk/20 ;
    print_debug("change hts*vts*1.05*1.1");
    print_debug("%s:pix_clk=%dM",__func__,pix_clk/1000000);


#ifdef ISP_DEBUG_ZSL
    isp_data.zsl_ctrl.zsl_online_enable = zsl_online_enable;
#endif

    /* small than isp clk */
    if ((true == isp_data.zsl_ctrl.zsl_online_enable) && (pix_clk < isp_data.isp_clk_freq))/*for common image, z62576, 20140429*/
    {
        isp_data.zsl_ctrl.zsl_proc_mode  = CAMERA_ZSL_ONLINE;
        print_info("CAMERA_ZSL_ONLINE");
        if (fmt_try->fmt.pix.width <= (isp_data.pic_attr[state_try].sensor_width / 2)){
            print_info("IDI_SCALEDOWN_2");
            *isp_idi_scale_down = IDI_SCALEDOWN_2;
        }
        else if (fmt_try->fmt.pix.width <= (isp_data.pic_attr[state_try].sensor_width * 6 / 10)){
            print_info("IDI_SCALEDOWN_1667");
            *isp_idi_scale_down = IDI_SCALEDOWN_1667;
        }
        else {
            print_info("IDI_DISABLE");
            *isp_idi_scale_down = IDI_DISABLE;
        }
    }
    /* if isp output less than half of sensor output */
    else if ((true == isp_data.zsl_ctrl.zsl_online_enable)
           && ((pix_clk < (isp_data.isp_clk_freq*2))  /*for common image, z62576, 20140429*/
           && (fmt_try->fmt.pix.width <= (isp_data.pic_attr[state_try].sensor_width / 2))))
    {
        print_info("CAMERA_ZSL_ONLINE,IDI_SCALEDOWN_2");
        isp_data.zsl_ctrl.zsl_proc_mode  = CAMERA_ZSL_ONLINE;
        *isp_idi_scale_down = IDI_SCALEDOWN_2;
    }
    /* if isp output less than 6/10 of sensor output */
    else if ((true == isp_data.zsl_ctrl.zsl_online_enable)
           && ((pix_clk < (isp_data.isp_clk_freq/5/5*3*3*2)) /*for common image, z62576, 20140429*/
           && (fmt_try->fmt.pix.width <= (isp_data.pic_attr[state_try].sensor_width * 3 / 5))))
    {
        print_info("CAMERA_ZSL_ONLINE,IDI_SCALEDOWN_1667");
        isp_data.zsl_ctrl.zsl_proc_mode  = CAMERA_ZSL_ONLINE;
        *isp_idi_scale_down = IDI_SCALEDOWN_1667;
    }
    else if (state_refresh == STATE_CAPTURE)
    {
        print_info("CAMERA_ZSL_OFFLINE,IDI_DISABLE");
        isp_data.zsl_ctrl.zsl_proc_mode  = CAMERA_ZSL_OFFLINE;
        *isp_idi_scale_down = IDI_DISABLE;
    }
    else
    {
        print_info("CAMERA_ZSL_OFFLINE");
        isp_data.zsl_ctrl.zsl_proc_mode  = CAMERA_ZSL_OFFLINE;
        if (preview_fmt->fmt.pix.width <=
            (isp_data.pic_attr[STATE_CAPTURE].sensor_width / 2)) {
            print_info("IDI_SCALEDOWN_2");
            *isp_idi_scale_down = IDI_SCALEDOWN_2;
        } else if (preview_fmt->fmt.pix.width <=
            (isp_data.pic_attr[STATE_CAPTURE].sensor_width * 3 / 5) ){
            print_info("IDI_SCALEDOWN_1667");
            *isp_idi_scale_down = IDI_SCALEDOWN_1667;
        } else {
            print_info("IDI_DISABLE");
            *isp_idi_scale_down = IDI_DISABLE;
        }
    }

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_isp_zsl_refresh_fmt;
 * Description : set ZSL format;
 * Input       : struct v4l2_format *preview_fmt,
                 struct v4l2_format *capture_fmt,
                 camera_setting_view_type preview_view_type,
                 camera_setting_view_type capture_view_type
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_isp_zsl_refresh_fmt(struct v4l2_format *preview_fmt,
                                  struct v4l2_format *fmt_try,
                                  struct v4l2_format *fmt_refresh,
                                  camera_state        state_try,
                                  camera_state        state_refresh)
{
    int                                 isp_idi_scale_down = IDI_DISABLE;

    /* calc idi value */
    k3_isp_zsl_calc_idi(preview_fmt,fmt_try,state_try,state_refresh,&isp_idi_scale_down);

    if (isp_idi_scale_down == IDI_DISABLE){
		isp_data.pic_attr[state_try].sensor_width = ((isp_data.pic_attr[state_try].sensor_width /16)*16);
		isp_data.pic_attr[state_try].sensor_height=((isp_data.pic_attr[state_try].sensor_height /4)*4);
    	}

    if (isp_idi_scale_down == IDI_SCALEDOWN_1667){
		/* for preview 1080p,cap 6M */

		isp_data.pic_attr[state_try].sensor_width = ((isp_data.pic_attr[state_try].sensor_width /80)*80);
		isp_data.pic_attr[state_try].sensor_height=((isp_data.pic_attr[state_try].sensor_height /20)*20);
    	}

    if (isp_idi_scale_down == IDI_SCALEDOWN_2){
		isp_data.pic_attr[state_try].sensor_width = ((isp_data.pic_attr[state_try].sensor_width /32)*32);
		isp_data.pic_attr[state_try].sensor_height=((isp_data.pic_attr[state_try].sensor_height /8)*8);
    	}


    isp_data.pic_attr[state_try].in_width      = isp_data.pic_attr[state_try].sensor_width;
    isp_data.pic_attr[state_try].in_height     = isp_data.pic_attr[state_try].sensor_height;

    /* refresh another channel's sensor width and height */
    isp_data.pic_attr[state_refresh].sensor_width  = isp_data.pic_attr[state_try].sensor_width;
    isp_data.pic_attr[state_refresh].sensor_height = isp_data.pic_attr[state_try].sensor_height;

    /* calc isp input width and height according idi */
    if (isp_idi_scale_down == IDI_DISABLE){
        isp_data.pic_attr[state_try].idi           = IDI_SCALE_DOWN_DISABLE;
        isp_data.pic_attr[state_refresh].idi       = isp_data.pic_attr[state_try].idi;
        isp_data.pic_attr[state_refresh].startx    = isp_data.pic_attr[state_try].startx;
        isp_data.pic_attr[state_refresh].starty    = isp_data.pic_attr[state_try].starty;
        isp_data.pic_attr[state_refresh].in_width  = isp_data.pic_attr[state_refresh].sensor_width;
        isp_data.pic_attr[state_refresh].in_height = isp_data.pic_attr[state_refresh].sensor_height;
    }
    if (isp_idi_scale_down == IDI_SCALEDOWN_1667){
        isp_data.pic_attr[state_try].idi           = IDI_SCALE_DOWN_ENABLE | IDI_SCALE_DOWN_1667_1667;
        isp_data.pic_attr[state_refresh].idi       = isp_data.pic_attr[state_try].idi;
        isp_data.pic_attr[state_refresh].startx    = (isp_data.pic_attr[state_try].startx + 1) / 2;
        isp_data.pic_attr[state_refresh].starty    = (isp_data.pic_attr[state_try].starty + 1) / 2;
        isp_data.pic_attr[state_refresh].in_width  = (isp_data.pic_attr[state_refresh].sensor_width * 6 / 10);
        isp_data.pic_attr[state_refresh].in_height = (isp_data.pic_attr[state_refresh].sensor_height * 6 /10);

        if (CAMERA_ZSL_ONLINE == isp_data.zsl_ctrl.zsl_proc_mode){
            isp_data.pic_attr[state_try].startx    = (isp_data.pic_attr[state_try].startx + 1) / 2;
            isp_data.pic_attr[state_try].starty    = (isp_data.pic_attr[state_try].starty + 1) / 2;
            isp_data.pic_attr[state_try].in_width  = (isp_data.pic_attr[state_try].sensor_width * 6 / 10) ;
            isp_data.pic_attr[state_try].in_height = (isp_data.pic_attr[state_try].sensor_height * 6 /10);
       }
    }
    if (isp_idi_scale_down == IDI_SCALEDOWN_2){
        isp_data.pic_attr[state_try].idi           = IDI_SCALE_DOWN_ENABLE | IDI_SCALE_DOWN_2_2;
        isp_data.pic_attr[state_refresh].idi       = isp_data.pic_attr[state_try].idi;
        isp_data.pic_attr[state_refresh].startx    = (isp_data.pic_attr[state_try].startx + 1) / 2;
        isp_data.pic_attr[state_refresh].starty    = (isp_data.pic_attr[state_try].starty + 1) / 2;
        isp_data.pic_attr[state_refresh].in_width  = (isp_data.pic_attr[state_refresh].sensor_width / 2);
        isp_data.pic_attr[state_refresh].in_height = (isp_data.pic_attr[state_refresh].sensor_height / 2) ;

        if (CAMERA_ZSL_ONLINE == isp_data.zsl_ctrl.zsl_proc_mode){
            isp_data.pic_attr[state_try].startx    = (isp_data.pic_attr[state_try].startx + 1) / 2;
            isp_data.pic_attr[state_try].starty    = (isp_data.pic_attr[state_try].starty + 1) / 2;
            isp_data.pic_attr[state_try].in_width  = (isp_data.pic_attr[state_try].sensor_width / 2) ;
            isp_data.pic_attr[state_try].in_height = (isp_data.pic_attr[state_try].sensor_height / 2);
        }
    }

    /* set the input format */
    isp_data.pic_attr[state_refresh].in_fmt = isp_data.pic_attr[state_try].in_fmt;

    /* update format info */
	isp_hw_ctl->isp_fill_fmt_info(&fmt_refresh->fmt.pix);
	if (state_refresh == STATE_CAPTURE)
		memcpy(&isp_data.pic_attr[STATE_IPP], &isp_data.pic_attr[STATE_CAPTURE], sizeof(isp_data.pic_attr[STATE_IPP]));
	/* buffer size */
	fmt_refresh->fmt.pix.priv = fmt_refresh->fmt.pix.sizeimage;
	if (state_refresh == STATE_CAPTURE && ISP_CAPTURE_OFFLINE == k3_isp_get_process_mode()) {
		u32 tmp;
		u32 bitspp = bits_per_pixel(isp_data.pic_attr[state_refresh].in_fmt);
		tmp = isp_data.pic_attr[state_refresh].sensor_width * isp_data.pic_attr[state_refresh].sensor_height * bitspp / 8;
		if (tmp > fmt_refresh->fmt.pix.priv) {
			fmt_refresh->fmt.pix.priv = tmp;
		}
	}

    print_info("isp_idi_scale_down=%d.",isp_idi_scale_down);
    print_info("isp_data.pic_attr[state_try].sensor_width=%d.",isp_data.pic_attr[state_try].sensor_width);
    print_info("isp_data.pic_attr[state_try].sensor_height=%d.",isp_data.pic_attr[state_try].sensor_height);
    print_info("isp_data.pic_attr[state_try].startx=%d.",isp_data.pic_attr[state_try].startx);
    print_info("isp_data.pic_attr[state_try].starty=%d.",isp_data.pic_attr[state_try].starty);
    print_info("isp_data.pic_attr[state_try].in_width=%d.",isp_data.pic_attr[state_try].in_width);
    print_info("isp_data.pic_attr[state_try].in_height=%d.",isp_data.pic_attr[state_try].in_height);
    print_info("isp_data.pic_attr[state_refresh].sensor_width=%d.",isp_data.pic_attr[state_refresh].sensor_width);
    print_info("isp_data.pic_attr[state_refresh].sensor_height=%d.",isp_data.pic_attr[state_refresh].sensor_height);
    print_info("isp_data.pic_attr[state_refresh].startx=%d.",isp_data.pic_attr[state_refresh].startx);
    print_info("isp_data.pic_attr[state_refresh].starty=%d.",isp_data.pic_attr[state_refresh].starty);
    print_info("isp_data.pic_attr[state_refresh].in_width=%d.",isp_data.pic_attr[state_refresh].in_width);
    print_info("isp_data.pic_attr[state_refresh].in_height=%d.",isp_data.pic_attr[state_refresh].in_height);

    print_info("leave %s.",__func__);

	return 0;
}

int get_ddr_valid_maxfreq(void)
{
    int             len = 0;
    int             count = 0;
    char            buf[DDR_VALID_FREQ_BUF_MAX_LEN] = {0};
    int             ddr_freq = 0;
    int             freq = 0;
    struct file    *fp  = NULL;
    mm_segment_t    fs;
    loff_t          pos = 0;
    char           *token = NULL;
    char           *dup_buf = NULL;
    char           *s = NULL;

    fp = (struct file *) filp_open(DDR_VALID_FREQ_PATH, O_RDONLY, 0);
    if (IS_ERR(fp)) {
        print_error("filp_open %s error, fp = 0x%p !", DDR_VALID_FREQ_PATH, fp);
        return -EEXIST;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);
    len = vfs_read(fp, buf, DDR_VALID_FREQ_BUF_MAX_LEN, &pos);
    filp_close(fp, NULL);
    set_fs(fs);

    if (len <= 0) {
        print_error("read file %s error, read %d byte.", DDR_VALID_FREQ_PATH, len);
        return -EIO;
    }

    buf[len-1] = '\0';
    print_debug("%s: ddr valid freq list = %s, len = %d.", __func__, buf, len);

    dup_buf = kstrdup(buf, GFP_KERNEL);
    if (NULL == dup_buf) {
        print_error("%s, alloc dup buffer fail.", __func__);
        return -ENOMEM;
    }

    s = strstrip(dup_buf);

    token = strsep(&s, " ");
    while (NULL != token) {
        if ('\0' == *token) {
            continue;
        }

        count = sscanf(token, "%d", &freq);
        if ((count > 0) && (freq > ddr_freq)) {
            ddr_freq = freq;
        }
        print_debug("%s: ddr valid freq = %d.", __func__, freq);

        token = strsep(&s, " ");
    }
    kfree(dup_buf);

    print_info("%s: %d.", __func__, ddr_freq);

    return ddr_freq;
}

int get_ddr_curr_bandwidth(void)
{
    int             len = 0;
    int             count = 0;
    char            buf[DDR_VALID_FREQ_BUF_MAX_LEN] = {0};
    int             ddr_bandwidth = 0;
    struct file    *fp  = NULL;
    mm_segment_t    fs;
    loff_t          pos = 0;
    char           *s = NULL;

    fp = (struct file *) filp_open(DDR_CURR_BANDWIDTH_PATH, O_RDONLY, 0);
    if (IS_ERR(fp)) {
        print_error("filp_open %s error, fp = 0x%p !", DDR_CURR_BANDWIDTH_PATH, fp);
        return -EEXIST;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);
    len = vfs_read(fp, buf, DDR_VALID_FREQ_BUF_MAX_LEN, &pos);
    filp_close(fp, NULL);
    set_fs(fs);

    if (len <= 0) {
        print_error("read file %s error, read %d byte.", DDR_CURR_BANDWIDTH_PATH, len);
        return -EIO;
    }

    buf[len-1] = '\0';
    print_debug("%s: ddr bandwidth = %s, len = %d.", __func__, buf, len);

    s = strstrip(buf);

    count = sscanf(s, "%d", &ddr_bandwidth);
    if (count <= 0) {
        return -1;
    }

    print_info("%s: %d.", __func__, ddr_bandwidth);

    return ddr_bandwidth;
}

int k3_isp_check_ddr_freq(int bandwidth)
{
    int result = 0;
    int count = 0;
    int delay = 30;/*ms*/

    result = get_ddr_curr_bandwidth();
    while ((count < delay) && (result < bandwidth)) {
		print_warn("%s, curr ddr bandwidth %d < vote bandwidth %d.", __func__, result, bandwidth);
        msleep(3);
        result = get_ddr_curr_bandwidth();
        count += 3;
    }

    if (count >= delay) {
		print_error("%s, after %d ms, curr ddr bandwidth %d < vote bandwidth %d.",
            __func__, delay, result, bandwidth);
        return -1;
    }

    return 0;
}

void k3_isp_try_ddr_freq(u32 sizeimage, camera_state state)
{
	int ddr_freq;

	print_info("%s state = %d", __func__, state);
	if (STATE_CAPTURE == state){
        /*for common image, z62576, 20140429, begin*/
		ddr_freq = isp_data.capture_ddr_min_freq;
        /*for common image, z62576, 20140429, end*/
	} else if (STATE_PREVIEW == state){
        /*for common image, z62576, 20140429, begin*/
		ddr_freq = isp_data.preview_ddr_min_freq;
        /*for common image, z62576, 20140429, end*/
	} else {
		print_error("%s wrong state do nothing", __func__);
		return;
	}

	k3_isp_lock_ddr_freq(ddr_freq);
}

void k3_isp_lock_ddr_freq(int freq)
{
    int max_freq = 0;
    int ddr_freq = 0;
    int bandwidth = 0;

    /*for common image, z62576, 20140429, begin*/
    max_freq = get_ddr_valid_maxfreq();
    if ((max_freq <= 0) || (max_freq > isp_data.capture_ddr_min_freq)) {
        print_error("get ddr valid max freq (%d) failed, use default freq %d!\n",
            max_freq, (int)isp_data.capture_ddr_min_freq);
        max_freq = isp_data.capture_ddr_min_freq;
    }
    /*for common image, z62576, 20140429, end*/

    ddr_freq = (max_freq < freq) ? max_freq : freq;
    print_debug("%s lock_freq = %d isp_data.ddr_lock_freq = %d ",__func__, ddr_freq, isp_data.ddr_lock_freq);

    bandwidth = (((ddr_freq/1000/1000)*8-8)*60-59)/100;
    if (!pm_qos_request_active(&isp_data.qos_req_ddr_min_profile)) {
        isp_data.qos_req_ddr_min_profile.pm_qos_class = 0;
        pm_qos_add_request(&isp_data.qos_req_ddr_min_profile, PM_QOS_MEMORY_THROUGHPUT, bandwidth);
        print_info("%s, lock ddr freq %d, bandwidth %d.", __func__, ddr_freq, bandwidth);
        isp_data.ddr_lock_freq = ddr_freq;
        if (k3_isp_check_ddr_freq(bandwidth)) {
            print_error("%s, lock ddr freq %d, bandwidth %d, failed!", __func__, ddr_freq, bandwidth);
        }
    } else {
        if (ddr_freq == isp_data.ddr_lock_freq) {
            print_info("%s, ddr freq %d not change, do nothing.", __func__, ddr_freq);
        } else {
            pm_qos_update_request(&isp_data.qos_req_ddr_min_profile, bandwidth);
            print_info("%s, update lock ddr freq %d, bandwidth %d.", __func__, ddr_freq, bandwidth);
            isp_data.ddr_lock_freq = ddr_freq;
            if (k3_isp_check_ddr_freq(bandwidth)) {
                print_error("%s, update lock ddr freq %d, bandwidth %d, failed!", __func__, ddr_freq, bandwidth);
            }
        }
    }
}

void k3_isp_unlock_ddr_freq(void)
{
    if (!pm_qos_request_active(&isp_data.qos_req_ddr_min_profile)) {
        print_warn("%s, now ddr freq hasn't been locked.",__func__);
        return;
    }

    pm_qos_remove_request(&isp_data.qos_req_ddr_min_profile);
    print_info("%s, unlock ddr freq %d.", __func__, isp_data.ddr_lock_freq);
    isp_data.ddr_lock_freq = 0;
}
void k3_isp_resume_prioty(void)
{
    u8 __iomem *ddrc_axi_base;
    /* set isp ddr port prioty */
    ddrc_axi_base = ioremap(SOC_MDDRC_AXI_BASE_ADDR, PAGE_ALIGN(SZ_2K));
	if (!ddrc_axi_base) {
        print_error("failed to map ddrc_axi_base)");
		return ;
	}
	else{
		print_info("%s !!!!!!!!!!!!!!",__func__);

        iowrite32_mutex(0x1d0007,ddrc_axi_base+0x400);
        iounmap(ddrc_axi_base);
	}
}
void k3_isp_change_prioty(void)
{
    u8 __iomem *ddrc_axi_base;
    /* set isp ddr port prioty */
    ddrc_axi_base = ioremap(SOC_MDDRC_AXI_BASE_ADDR, PAGE_ALIGN(SZ_2K));
	if (!ddrc_axi_base) {
        print_error("failed to map ddrc_axi_base)");
		return ;
	}
	else{
		print_info("%s !!!!!!!!!!!!!!",__func__);
        iowrite32_mutex(0x1d0005,ddrc_axi_base+0x400);
        iounmap(ddrc_axi_base);
	}
}
/************************ END **************************/
