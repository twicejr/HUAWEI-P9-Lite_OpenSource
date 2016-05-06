/*
 *  Hisilicon K3 soc camera v4l2 driver source file
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
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/ctype.h>
#include <linux/pagemap.h>
#include <linux/vmalloc.h>
#include <linux/types.h>
#include <linux/fb.h>
#include <linux/pci.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/mm.h>
#include <media/v4l2-common.h>
#include <media/v4l2-ioctl.h>
#include <linux/io.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
//#include <linux/android_pmem.h>
#include <linux/ioctl.h>
//#include <linux/device.h>
#include <linux/bug.h>
#include "mini_k3_v4l2_capture.h"
/*#define DEBUG_DEBUG 1 */
#define LOG_TAG "K3_V4L2"
#include "mini_cam_log.h"
#include "mini_cam_dbg.h"
#include "mini_hwa_cam_tune.h"

#include <trace/trace_kernel.h>
#include "camera_agent.h"

#include "isp_io_mutex.h"
#include <linux/fs.h>
#include "mini_ispregs.h"

#ifdef __KERNEL__
#define CAM_WAIT_DQBUF_IRQ_TIMEOUT      CONFIG_CAMERA_WAIT_DQBUF_IRQ_TIMEOUT
#endif

#ifndef CAM_WAIT_DQBUF_IRQ_TIMEOUT
/*FPGA for isp will take longer time than K3V2 so modify it from 2*HZ to 5*HZ*/
#define CAM_WAIT_DQBUF_IRQ_TIMEOUT   (5)
//#define CAM_WAIT_EVENT_IRQ_TIMEOUT   (2)
#endif
#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#endif

#include "mini_hwa_cam_tune.h"

#define CAM_DEF_WIDTH   640
#define CAM_DEF_HEIGHT  480

#define BUF_LEN	 80
//#define K3_V4L2_CAPTURE_TEST
/* #define DEBUG_WRITE_FILE 0 */

/* Camera control struct data */
static mini_v4l2_ctl_struct v4l2_ctl;
static int video_nr = -1;
static int back_test_result = 0;
#ifdef READ_BACK_RAW
static u8 buf_used = 0;

#endif
#ifdef CONFIG_DEBUG_FS
static struct dentry *debugfs_camera_dir;
static struct dentry *debugfs_isp_reg;
#endif

#define SAFE_GET_DRVDATA(cam, fh) \
		do { \
			if ((fh) == NULL) { \
				print_error("%s file handle is null", __func__); \
				return -EBADF; \
			} \
			cam = video_get_drvdata((struct video_device *)(fh)); \
			if (0 == (cam)) { \
				print_error("%s get video device fail", __func__); \
				return -EBADF; \
			} \
		} while (0)

#define CHECK_STATE(state) \
		do { \
			if (cam->running[(state)]) { \
				print_error("%s, camera running in state:%d", __func__, (state)); \
				return -EBUSY; \
			} \
		} while (0)
#define SAFE_DOWN(lock) \
		do { \
			if (down_interruptible((lock))) { \
				print_error("%s get busy_lock fail", __func__); \
				return -EINTR; \
			} \
		} while (0)
#define SAFE_UP(lock) up((lock))

/* function predeclaration */
static int k3_v4l2_set_camera(mini_v4l2_ctl_struct *cam, int new_sensor);
static int k3_v4l2_start_process(mini_v4l2_ctl_struct *cam, u8 mode);
static int k3_v4l2_stop_process(mini_v4l2_ctl_struct *cam, ipp_mode mode);

camera_state get_camera_state(enum v4l2_buf_type type)
{
	camera_state state;

	if (type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		state = STATE_CAPTURE;
	} else if (type == V4L2_BUF_TYPE_VIDEO_OVERLAY) {
		state = STATE_PREVIEW;
	} else if (type == V4L2_BUF_TYPE_PRIVATE) {
		state = STATE_IPP;
	} else {
		state = STATE_MAX;
		print_error("%s unkown buffer type", __func__);
	}
	return state;
}

/*
 **************************************************************************
 * FunctionName: set_default_fmt;
 * Description : set default value of v4l2_format struct;
 * Input       : NA;
 * Output      : fmt: format struct need to be filled;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static inline void k3_set_default_fmt(struct v4l2_format *fmt, camera_state state)
{
	print_debug("enter %s", __func__);


	switch (state) {
	case STATE_PREVIEW:
		fmt->type = V4L2_BUF_TYPE_VIDEO_OVERLAY;
		break;
	case STATE_CAPTURE:
		fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		break;
	case STATE_IPP:
		fmt->type = V4L2_BUF_TYPE_PRIVATE;
		break;
	default:
		fmt->type = V4L2_BUF_TYPE_VIDEO_OVERLAY;
		break;
	}

	fmt->fmt.pix.width = CAM_DEF_WIDTH;
	fmt->fmt.pix.height = CAM_DEF_HEIGHT;
	fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
	fmt->fmt.pix.bytesperline = fmt->fmt.pix.width;
	fmt->fmt.pix.sizeimage = fmt->fmt.pix.width * fmt->fmt.pix.height
	    * (mini_bits_per_pixel(fmt->fmt.pix.pixelformat)) / 8;
	return;
}

/*
 **************************************************************************
 * FunctionName: k3_fill_buffer;
 * Description : Set phyaddr and size of v4l2_buffer;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static inline void k3_register_buffer(mini_camera_frame_buf *a,
				      struct v4l2_buffer *b)
{

	a->index = b->index;
	a->size = b->length;
	a->phyaddr = b->m.offset;
	a->flags = 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_querycap;
 * Description : Fill device capabilities bits;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_querycap(struct file *file, void *fh,
				  struct v4l2_capability *cap)
{
	print_debug("enter %s", __func__);

	strncpy(cap->driver, "k3-cam-v4l2", sizeof(cap->driver));
	cap->card[0] = '\0';
	cap->bus_info[0] = '\0';
	cap->version = KERNEL_VERSION(0, 0, 1);
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE
				| V4L2_CAP_VIDEO_OVERLAY
				| V4L2_CAP_STREAMING;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_try_fmt_vid_capture;
 * Description : Empty function but needed by v4l2 architecture;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_try_fmt_vid_capture(struct file *file, void *fh,
					     struct v4l2_format *fmt)
{
	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_try_fmt_vid_preview;
 * Description : Empty function but needed by v4l2 architecture;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_try_fmt_vid_preview(struct file *file, void *fh,
					     struct v4l2_format *fmt)
{
	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_s_fmt_capture;
 * Description : Set format information of picture;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0: Success; Other: Fail;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_s_fmt_capture(struct file *file, void *fh,
				       struct v4l2_format *fmt)
{
	int ret = 0;
	mini_v4l2_ctl_struct *cam = NULL;
	mini_pic_fmt_s       pic_fmt;

	print_debug("enter %s", __func__);
	print_info("%s:capture_fmt->fmt.pix.width=%d,capture_fmt->fmt.pix.height=%d",__func__,fmt->fmt.pix.width,fmt->fmt.pix.height);

	SAFE_GET_DRVDATA(cam, fh);

	CHECK_STATE(STATE_CAPTURE);
	CHECK_STATE(STATE_IPP);


    /* if ZSL state is off */
	if (CAMERA_ZSL_ON != mini_k3_isp_get_zsl_state()){
    	ret = mini_k3_isp_try_fmt(fmt, STATE_CAPTURE, VIEW_FULL);
    	if (ret != 0)
    		return ret;
    }

	SAFE_DOWN(&cam->busy_lock);
	cam->fmt[STATE_CAPTURE] = *fmt;
	cam->fmt[STATE_IPP] = *fmt;
	SAFE_UP(&cam->busy_lock);

    print_info("%s:mini_k3_isp_zsl_try_fmt.",__func__);
	if (CAMERA_ZSL_ON == mini_k3_isp_get_zsl_state()) {
	    pic_fmt.preview_fmt = &(cam->fmt[STATE_PREVIEW]);
	    pic_fmt.capture_fmt = &(cam->fmt[STATE_CAPTURE]);
	    pic_fmt.ipp_fmt     = &(cam->fmt[STATE_IPP]);
	    pic_fmt.preview_view_type = cam->fmt[STATE_PREVIEW].fmt.pix.priv;
	    pic_fmt.capture_view_type = VIEW_FULL;

	    ret = mini_k3_isp_zsl_try_fmt(&pic_fmt,cam->running[STATE_PREVIEW]);
	    if (ret != 0) {
	        print_error("%s:mini_k3_isp_zsl_try_fmt fail.ret=%d",__func__,ret);
	        return ret;
	    }

        mini_k3_isp_set_zsl_cap_cmd(CAMERA_ZSL_CAP_CMD_START);
    }

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_s_fmt_preview;
 * Description : Set format information of preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0: Success; Other: Fail;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_s_fmt_preview(struct file *file, void *fh,
				       struct v4l2_format *fmt)
{
	int ret = 0;
	mini_v4l2_ctl_struct *cam = NULL;

	print_debug("enter %s", __func__);
    print_info("%s:preview_fmt->fmt.pix.width=%d,preview_fmt->fmt.pix.height=%d",__func__,fmt->fmt.pix.width,fmt->fmt.pix.height);

	SAFE_GET_DRVDATA(cam, fh);

	CHECK_STATE(STATE_PREVIEW);

    /* if ZSL mode is off */
    if (CAMERA_ZSL_ON != mini_k3_isp_get_zsl_state()){
        ret = mini_k3_isp_try_fmt(fmt, STATE_PREVIEW, fmt->fmt.pix.priv);
    	if (ret != 0)
    		return ret;
    }

	SAFE_DOWN(&cam->busy_lock);
	cam->fmt[STATE_PREVIEW] = *fmt;
	SAFE_UP(&cam->busy_lock);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_fmt_capture;
 * Description : Get format information of picture;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0: Success; Other: Fail;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_g_fmt_capture(struct file *file, void *fh,
				       struct v4l2_format *fmt)
{
	mini_v4l2_ctl_struct *cam = NULL;

	SAFE_GET_DRVDATA(cam, fh);

	*fmt = cam->fmt[STATE_CAPTURE];

	print_debug("%s pixelformat=%d, widht=%d, height=%d, bytesperline=%d",
		    __func__, fmt->fmt.pix.pixelformat, fmt->fmt.pix.width,
		    fmt->fmt.pix.height, fmt->fmt.pix.bytesperline);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_fmt_preview;
 * Description : Get preview information of preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : 0: Success; Other: Fail;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_g_fmt_preview(struct file *file, void *fh,
				       struct v4l2_format *fmt)
{
	mini_v4l2_ctl_struct *cam = NULL;

	SAFE_GET_DRVDATA(cam, fh);

	*fmt = cam->fmt[STATE_PREVIEW];

	print_debug("%s pixelformat=%d, widht=%d, height=%d, bytesperline=%d",
		    __func__, fmt->fmt.pix.pixelformat, fmt->fmt.pix.width,
		    fmt->fmt.pix.height, fmt->fmt.pix.bytesperline);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_fmt_private;
 * Description : for private work;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_g_fmt_private(struct file *file, void *fh,
				       struct v4l2_format *fmt)
{
	mini_v4l2_ctl_struct *cam = NULL;

	SAFE_GET_DRVDATA(cam, fh);

	*fmt = cam->fmt[STATE_IPP];

	print_debug("%s pixelformat=%d, widht=%d, height=%d, bytesperline=%d",
		    __func__, fmt->fmt.pix.pixelformat, fmt->fmt.pix.width,
		    fmt->fmt.pix.height, fmt->fmt.pix.bytesperline);
	return 0;
}

static int k3_isp_get_mini_test_result(void)
{
	int res = 0;
	res = camera_agent_get_test_result();
	if(res == 0)
		print_info("chip is wrong");
	return res;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_ctrl;
 * Description : Get control information of current sensor:
 *               white balance,
 *               brightness,
 *               contrast,
 *               ... ...
 *               1. If camera sensor does not support the function, return -EINVAL;
 *               2. Else return the current value of that control;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_g_ctrl(struct file *file, void *fh,
				struct v4l2_control *a)
{
	int ret = 0;
	mini_v4l2_ctl_struct *cam = NULL;
	int front_test_result = 0;
	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);

	/*
	 * get control of camera sensor:
	 * 1. check if set_xxx is set by sensor
	 * 2. YES: get current control value of sensor
	 * 3. NO: return -EINVAL(means this control is not supported by sensor)
	 */
	print_debug("v4l2 control id is %08x", a->id);
	if(a->id>=V4L2_CID_HWA_BASE && a->id<=V4L2_CID_HWA_MAX)
	{
		ret = mini_hwa_v4l2_ioctl_g_ctrls(file, fh, a);
		SAFE_UP(&cam->busy_lock);
		return ret;
	}
	switch (a->id) {

		/* auto white balance */
	case V4L2_CID_AUTO_WHITE_BALANCE:
		{
			print_info("get auto wb");
			a->value = mini_k3_isp_get_awb_mode();
			break;
		}

		/* manual white balance */
	case V4L2_CID_DO_WHITE_BALANCE:
		{
			print_info("get manual wb");
			a->value = mini_k3_isp_get_awb_mode();
			break;
		}

		/*anti-shaking: for video */
	case V4L2_CID_ANTI_SHAKING:
		{
			print_info("get anti-shaking");
			a->value = mini_k3_isp_get_anti_shaking();
			break;
		}

	case V4L2_CID_ISO:
		{
			print_info("get iso");
			a->value = mini_k3_isp_get_iso();
			break;
		}

	case V4L2_CID_EXPOSURE:
		{
			print_info("get ev");
			a->value = mini_k3_isp_get_ev();
			break;
		}

	case V4L2_CID_METERING:
		{
			print_info("get metering");
			a->value = mini_k3_isp_get_metering_mode();
			break;
		}

	case V4L2_CID_POWER_LINE_FREQUENCY:
		{
			print_info("get anti-flicker");
			a->value = mini_k3_isp_get_anti_banding();
			break;
		}

		/* sharpness */
	case V4L2_CID_SHARPNESS:
		{
			print_info("get sharpness");
			a->value = mini_k3_isp_get_sharpness();
			break;
		}

		/* saturation */
	case V4L2_CID_SATURATION:
		{
			print_info("get saturation");
			a->value = mini_k3_isp_get_saturation();
			break;
		}

	case V4L2_CID_GET_MINIISP_TEST_RESULT:
		{
			print_info("get miniisp test result:");
			front_test_result = k3_isp_get_mini_test_result();
			if(back_test_result < 0 ||front_test_result <0) {
				a->value = -1;
				goto end;
			}
			if(back_test_result && front_test_result)
				a->value = all_right;
			else if(back_test_result)
				a->value = back_right;
			else if(front_test_result)
				a->value = front_right;
			else
				a->value = all_wrong;
			end:
			print_info("get result value:%d",a->value);
			break;
		}
		/* contrast */
	case V4L2_CID_CONTRAST:
		{
			print_info("get contrast");
			a->value = mini_k3_isp_get_contrast();
			break;
		}

		/* scene */
	case V4L2_CID_SCENE:
		{
			print_info("get scene");
			a->value = mini_k3_isp_get_scene();
			break;
		}

		/* brightness */
	case V4L2_CID_BRIGHTNESS:
		{
			print_info("get brightness");
			a->value = mini_k3_isp_get_brightness();
			break;
		}
	case V4L2_CID_EFFECT:
		{
			print_info("get special effect");
			a->value = mini_k3_isp_get_effect();
			break;
		}

	case V4L2_CID_CAPTURE_MODE:
		{
			a->value = mini_k3_isp_get_process_mode();
			break;
		}
	case V4L2_CID_ZOOM_RELATIVE:
		{
			a->value = mini_k3_isp_get_zoom();
			break;
		}

	case V4L2_CID_FOCUS_MODE:
		{
			a->value = mini_k3_isp_get_focus_mode();
			break;
		}

	case V4L2_CID_MAX_FOCUS_AREA:
		{
			if (CAMERA_USE_SENSORISP == cam->sensor->isp_location || NULL == cam->sensor->vcm) {
				/* front camera do not support touch point focus */
				a->value = 0;
			} else {
				a->value = MAX_FOCUS_RECT;
			}
			break;
		}

	case V4L2_CID_MAX_METERING_AREA:
		{
			if (CAMERA_USE_SENSORISP == cam->sensor->isp_location) {
				/* front camera do not support metering */
				a->value = 0;
			} else {
				a->value = MAX_METERING_RECT;
			}
			break;
		}

	case V4L2_CID_FLASH_MODE:
		{
			a->value = mini_k3_isp_get_flash_mode();
			break;
		}
	case V4L2_CID_ACTUAL_ISO:
		{
			a->value = mini_k3_isp_get_actual_iso();
			break;
		}

	case V4L2_CID_ACTUAL_EXPOSURE:
		{
			a->value = mini_k3_isp_get_exposure_time();
			break;
		}

	case V4L2_CID_HFLIP:
		{
			a->value = mini_k3_isp_get_hflip();
			break;
		}
	case V4L2_CID_VFLIP:
		{
			a->value = mini_k3_isp_get_vflip();
			break;
		}
	case V4L2_CID_GET_METERING_FLASH_RESULT:
		{
			a->value = mini_k3_isp_get_flash_result();
			break;
		}

	case V4L2_CID_AUTO_EXPOSURE_LOCK_SUPPORTED:
	case V4L2_CID_AUTO_WHITE_BALANCE_LOCK_SUPPORTED:
		{
			a->value = 1;
			break;
		}

	case V4L2_CID_GET_FOCUS_DISTANCE:
		{
			a->value = mini_k3_isp_get_focus_distance();
			break;
		}
	case V4L2_CID_GET_CURRENT_VTS:
		{
			a->value = mini_k3_isp_get_current_vts();
			break;
		}
	case V4L2_CID_GET_CURRENT_FPS:
		{
			a->value = mini_k3_isp_get_current_fps();
			break;
		}
	case V4L2_CID_GET_BAND_THRESHOLD:
		{
			a->value = mini_k3_isp_get_band_threshold();
			break;
		}
	case V4L2_CID_GET_AWB_GAIN:
		{
			a->value = mini_k3_isp_get_awb_gain(1);
			break;
		}

	case V4L2_CID_GET_AWB_GAIN_ORI:
		{
			a->value = mini_k3_isp_get_awb_gain(0);
			break;
		}

	case V4L2_CID_GET_FOCUS_CODE:
		{
			a->value = mini_k3_isp_get_focus_code();
			break;
		}

	case V4L2_CID_GET_EXPO_LINE:
		{
			a->value = mini_k3_isp_get_expo_line();
			break;
		}

	case V4L2_CID_GET_SENSOR_VTS:
		{
			a->value = mini_k3_isp_get_sensor_vts();
			break;
		}

	case V4L2_CID_GET_CURRENT_CCM_RGAIN:
		{
			a->value = mini_k3_isp_get_current_ccm_rgain();
			break;
		}

	case V4L2_CID_GET_CURRENT_CCM_BGAIN:
		{
			a->value = mini_k3_isp_get_current_ccm_bgain();
			break;
		}

	case V4L2_CID_GET_APERTURE:
		{
			a->value = mini_k3_isp_get_sensor_aperture();
			break;
		}

	case V4L2_CID_GET_EQUIV_FOCUS:
		{
			a->value = mini_k3_isp_get_equivalent_focus();
			break;
		}

	default:
		{
			ret = -EINVAL;
			break;
		}
	}
	SAFE_UP(&cam->busy_lock);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_s_ctrl;
 * Description : SET control information of the current sensor;
 *               white balance,
 *               brightness,
 *               contrast,
 *               ... ...
 *               1. If camera sensor does not support the function, return -EINVAL;
 *               2. Else set the given value to sensor, and then it will take effect;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_s_ctrl(struct file *file, void *fh,
				struct v4l2_control *v4l2_param)
{
	int                 ret  = 0;
	mini_v4l2_ctl_struct     *cam = NULL;
	int retv = 0;
	struct semaphore    *lock= NULL;

	print_debug("enter %s", __func__);
	SAFE_GET_DRVDATA(cam, fh);

	print_debug("v4l2_control id=%08x", v4l2_param->id);

	lock = &cam->busy_lock;
	if ((V4L2_CID_CAP_RAW == v4l2_param->id) || (V4L2_CID_PROCESS_IMG == v4l2_param->id))
	{
		lock = &cam->busy_lock_capture;
	}

	SAFE_DOWN(lock);
	
	if(v4l2_param->id>=V4L2_CID_HWA_BASE && v4l2_param->id<=V4L2_CID_HWA_MAX)
	{
		ret = mini_hwa_v4l2_ioctl_s_ctrls(file, fh, v4l2_param);
		SAFE_UP(&cam->busy_lock);
		return ret;
	}

	switch (v4l2_param->id) {

		/* auto white balance */
	case V4L2_CID_AUTO_WHITE_BALANCE:
		{
			print_info("set auto wb: %d", v4l2_param->value);
			mini_k3_isp_set_awb_mode(v4l2_param->value);
			break;
		}

		/* manual white balance */
	case V4L2_CID_DO_WHITE_BALANCE:
		{
			print_info("set manual wb: %d", v4l2_param->value);
			mini_k3_isp_set_awb_mode(v4l2_param->value);
			break;
		}

		/*anti-shaking: for video */
	case V4L2_CID_ANTI_SHAKING:
		{
			print_info("set anti-shaking, %d", v4l2_param->value);
			mini_k3_isp_set_anti_shaking(v4l2_param->value);
			break;
		}

	case V4L2_CID_ISO:
		{
			print_info("set iso %d", v4l2_param->value);
			mini_k3_isp_set_iso(v4l2_param->value);
			break;
		}

	case V4L2_CID_EXPOSURE:
		{
			print_info("set ev %d", v4l2_param->value);
			if ((v4l2_param->value <= CAMERA_EXPOSURE_MAX)
			    && (v4l2_param->value >= -(CAMERA_EXPOSURE_MAX)))
				mini_k3_isp_set_ev(v4l2_param->value);
			break;
		}

	case V4L2_CID_METERING:
		{
			print_info("set metering, %d", v4l2_param->value);
			mini_k3_isp_set_metering_mode(v4l2_param->value);
			break;
		}

	case V4L2_CID_POWER_LINE_FREQUENCY:
		{
			print_info("set anti-banding, %d", v4l2_param->value);
			mini_k3_isp_set_anti_banding(v4l2_param->value);
			break;
		}

		/* sharpness */
	case V4L2_CID_SHARPNESS:
		{
			print_info("set sharpness, %d", v4l2_param->value);
			mini_k3_isp_set_sharpness(v4l2_param->value);
			break;
		}

		/* saturation */
	case V4L2_CID_SATURATION:
		{
			print_info("set saturation, %d", v4l2_param->value);
			mini_k3_isp_set_saturation(v4l2_param->value);
			break;
		}

		/* contrast */
	case V4L2_CID_CONTRAST:
		{
			print_info("set contrast, %d", v4l2_param->value);
			mini_k3_isp_set_contrast(v4l2_param->value);
			break;
		}

		/* scene */
	case V4L2_CID_SCENE:
		{
			print_info("set scene, %d", v4l2_param->value);
			mini_k3_isp_set_scene(v4l2_param->value);
			break;
		}

		/* brightness */
	case V4L2_CID_BRIGHTNESS:
		{
			print_info("set brightness, %d", v4l2_param->value);
			mini_k3_isp_set_brightness(v4l2_param->value);
			break;
		}
		/* effect */
	case V4L2_CID_EFFECT:
		{
			print_info("set effect, %d", v4l2_param->value);
			mini_k3_isp_set_effect(v4l2_param->value);
			break;
		}

		/* zoom */
	case V4L2_CID_ZOOM_RELATIVE:
		{
			print_info("set zoom, %d", v4l2_param->value);
			ret = mini_k3_isp_set_zoom(cam->running[STATE_PREVIEW], v4l2_param->value);
			break;
		}

		/* select a sensor to be used */
	case V4L2_CID_SET_SENSOR:
		{
			if (v4l2_param->value < 0 || v4l2_param->value >= CAMERA_SENSOR_MAX) {
				print_error("invalid camera sensor type [%d]",
					    v4l2_param->value);
				ret = -EINVAL;
				break;
			}
			ret = k3_v4l2_set_camera(&v4l2_ctl, v4l2_param->value);
			break;
		}
	case V4L2_CID_SET_MINIISP_TEST:
		{
			print_info("V4L2_CID_SET_MINIISP_TEST");

			retv = camera_agent_set_sensormode(0,99,0);
			if(retv !=0) {
				print_error("error : set_back_sensormode fail");
			}
			msleep(1000);
			back_test_result = k3_isp_get_mini_test_result();

			retv = camera_agent_set_sensormode(1,99,0);
			if(retv !=0) {
				print_error("error : set_front_sensormode fail");
			}
			msleep(1000);
			break;
		}

	case V4L2_CID_PROCESS_RAW_2_YUV:
		{
			if (v4l2_param->value == 1)
				ret = k3_v4l2_start_process(&v4l2_ctl, CAMERA_IPP_MODE_RAW_2_YUV);
			else if (v4l2_param->value == 0)
				ret = k3_v4l2_stop_process(&v4l2_ctl, CAMERA_IPP_MODE_RAW_2_YUV);
			else
				ret = -EINVAL;
			break;
		}
	case V4L2_CID_PROCESS_HDR:
		{
			if (v4l2_param->value == 1)
				ret = k3_v4l2_start_process(&v4l2_ctl, CAMERA_IPP_MODE_HDR);
			else if (v4l2_param->value == 0)
				ret = k3_v4l2_stop_process(&v4l2_ctl, CAMERA_IPP_MODE_HDR);
			else
				ret = -EINVAL;
			break;
		}
	case V4L2_CID_FOCUS_AUTO:
		{
			if (v4l2_param->value)
				mini_k3_isp_auto_focus(v4l2_param->value);
			else
				mini_k3_isp_auto_focus(FOCUS_STOP);
			break;
		}
		/* Set focus mode */
	case V4L2_CID_FOCUS_MODE:
		{
			ret = mini_k3_isp_set_focus_mode(v4l2_param->value);
			if (ret == -1) {
				ret = -EINVAL;
			}
			break;
		}
	case V4L2_CID_FLASH_MODE:
		{
			print_info("set flash mode [%d]", v4l2_param->value);
			if (v4l2_param->value < 0 || v4l2_param->value >= CAMERA_FLASH_MAX) {
				print_error("invalid camera flash mode [%d]", v4l2_param->value);
				ret = -EINVAL;
				break;
			} else {
				ret = mini_k3_isp_set_flash_mode(v4l2_param->value);
				if (ret < 0) {
					print_error("failed to set flash mode [%d]", v4l2_param->value);
					break;
				}
			}
			break;
		}
	case V4L2_CID_HFLIP:
		{
			print_info("set hflip, %d", v4l2_param->value);
			mini_k3_isp_set_hflip(v4l2_param->value);
			break;
		}
	case V4L2_CID_VFLIP:
		{
			print_info("set vflip, %d", v4l2_param->value);
			mini_k3_isp_set_vflip(v4l2_param->value);
			break;
		}
	case V4L2_CID_SET_METERING_FLASH:
		{
			print_info("set metering flash, %d", v4l2_param->value);
			mini_k3_isp_check_flash_level(v4l2_param->value);
			break;
		}

	case V4L2_CID_AUTO_EXPOSURE_LOCK:
		{
			print_info("set AE lock, %d", v4l2_param->value);
			mini_k3_isp_set_ae_lock(v4l2_param->value);
			break;
		}
	case V4L2_CID_AUTO_WHITE_BALANCE_LOCK:
		{
			print_info("set AWB lock, %d", v4l2_param->value);
			mini_k3_isp_set_awb_lock(v4l2_param->value);
			break;
		}
	case V4L2_CID_SET_FPS_LOCK:
		{
			print_info("set fps lock, %d", v4l2_param->value);
			mini_k3_isp_set_fps_lock(v4l2_param->value);
			break;
		}
	case V4L2_CID_SNAPSHOOT_MODE:
		{
			print_info("set snap shoot mode, %d", v4l2_param->value);
			mini_k3_isp_set_shoot_mode(v4l2_param->value);
			break;
		}
	case V4L2_CID_PM_MODE:
		{
			print_info("set PM_mode, %d", v4l2_param->value);
			mini_k3_isp_set_pm_mode(v4l2_param->value);
			break;
		}

    case V4L2_CID_ZSL:
        {
            print_info("set ZSL_state, %d", v4l2_param->value);
			mini_k3_isp_set_zsl_state(v4l2_param->value);
            break;
        }
    case V4L2_CID_CAP_RAW:
        {
            print_info("set ZSL cap raw, %d", v4l2_param->value);
            if(cam->running[(STATE_CAPTURE)]){
			    ret = mini_k3_isp_set_zsl_cap_raw(v4l2_param->value,&cam->fmt[STATE_CAPTURE].fmt.pix, &cam->buffer_arr[STATE_IPP]);
            } else {
			    print_warn("cap raw while cam->running[(STATE_CAPTURE)]=false.");
			    ret = -EPERM;
            }
            break;
        }
	case V4L2_CID_PROCESS_IMG:
		{
		    print_info("set ZSL proc img, %d", v4l2_param->value);
            if(cam->running[(STATE_CAPTURE)]){
    			if (v4l2_param->value != ZSL_PROC_IMG_STOP)
    				ret = k3_v4l2_start_process(&v4l2_ctl, v4l2_param->value);
    			else if (v4l2_param->value == ZSL_PROC_IMG_STOP)
    				ret = k3_v4l2_stop_process(&v4l2_ctl, ZSL_PROC_IMG_STOP);
    			else
    				ret = -EINVAL;
			} else {
			    print_warn("proc img while cam->running[(STATE_CAPTURE)]=false.");
    			ret = -EPERM;
            }
			break;
		}

	case V4L2_CID_SET_VIDEO_STABILIZATION:
		{
			print_info("set VIDEO_STABILIZATION, %d", v4l2_param->value);
			mini_k3_isp_set_video_stabilization(v4l2_param->value);
			break;
		}
	case V4L2_CID_SET_YUV_CROP_POS:
		{
			print_debug("set crop pos, %d", v4l2_param->value);
			mini_k3_isp_set_yuv_crop_pos(v4l2_param->value);
			break;
		}
    case V4L2_CID_CAPTURE_MODE:
        {
            print_info("set V4L2_CID_CAPTURE_MODE, %d", v4l2_param->value);
            mini_k3_isp_set_process_mode(v4l2_param->value);
            break;
        }
	case  V4L2_CID_SET_3A_MODE:
		{
			int hw_3a_switch =  v4l2_param->value;
			mini_k3_isp_set_hw_3a_mode(hw_3a_switch);
			break;
		}
    /* end */
	default:
	    print_info("warning:unknown CID,v4l2_param->id=%d", v4l2_param->id);
		break;
	}

	SAFE_UP(lock);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_caps;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static long k3_v4l2_ioctl_g_caps(struct file *file, void *fh, bool private,
				unsigned int cmd, void *arg)
{
	int i					= 0;
	long ret					= 0;
	int ext_ctls_size			= 0;
	void *mbuf				= NULL;
	void __user *user_ptr			= NULL;
	mini_v4l2_ctl_struct *cam			= NULL;
	struct v4l2_ext_controls *ext_ctls	= arg;
	struct v4l2_ext_control *controls	= NULL;

	print_debug("enter %s, cmd[%#x]", __func__, cmd);

	if (VIDIOC_CHECK_CAP != cmd) {
		print_error("invalid ioctl VIDIOC_CHECK_CAP=%#x, cmd = %08x",
			    VIDIOC_CHECK_CAP, cmd);
		return -EINVAL;
	}

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);

	if (ext_ctls->ctrl_class != V4L2_CTRL_CLASS_USER) {
		print_error("unsupported ctrl class!");
		goto out;
	}

	/* allocate buffer */
	user_ptr = (void __user *)ext_ctls->controls;
	ext_ctls_size = ext_ctls->count * sizeof(struct v4l2_ext_control);
	if (ext_ctls->count) {
		mbuf = kmalloc(ext_ctls_size, GFP_KERNEL);
		if (!mbuf) {
			ret = -ENOMEM;
			print_error("fail to allocate buffer for ext controls");
			goto out;
		}

		controls = (struct v4l2_ext_control *)mbuf;
		if (copy_from_user(mbuf, user_ptr, ext_ctls_size)) {
			print_error("fail to copy data from user space mem");
			ret = -EFAULT;
			goto out;
		}
	}

	for (i = 0; i < ext_ctls->count; ++i) {
		controls[i].value = 0;

		if(cam->sensor->isp_location == CAMERA_USE_K3ISP ||
			V4L2_CID_ZOOM_RELATIVE == controls[i].id)
			mini_k3_isp_get_k3_capability(controls[i].id, &controls[i].value);

		if(cam->sensor->get_capability)
			cam->sensor->get_capability(controls[i].id, &controls[i].value);
	}

	if (ext_ctls->count) {
		if (copy_to_user((void __user *)user_ptr, mbuf, ext_ctls_size)) {
			ret = -EFAULT;
			goto out;
		}
	}

out:
	if (mbuf) {
		kfree(mbuf);
		mbuf = NULL;
	}

	SAFE_UP(&cam->busy_lock);
	return ret;
}

static int k3_v4l2_ioctl_g_ext_ctrls(struct file *file, void *fh,
				     struct v4l2_ext_controls *arg)
{
	mini_v4l2_ctl_struct *cam			= NULL;
	u32 cid_idx;
	int ret					= 0;
	struct v4l2_ext_controls *ext_ctls	= arg;
	struct v4l2_ext_control *controls	= NULL;
	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);

	if (ext_ctls->ctrl_class != V4L2_CTRL_CLASS_CAMERA) {
		print_error("unsupported ctrl class!");
		ret = -EINVAL;
		goto out;
	}

	controls = (struct v4l2_ext_control *)ext_ctls->controls;

	for (cid_idx = 0; cid_idx < ext_ctls->count; cid_idx++) {
		if(controls[cid_idx].id>=V4L2_CID_HWA_BASE && controls[cid_idx].id<=V4L2_CID_HWA_MAX){
			ret = mini_hwa_v4l2_ioctl_g_ext_ctrls(&controls, controls[cid_idx].id,cid_idx);
			continue;
		}

		switch (controls[cid_idx].id) {
		/* get camera count */
		case V4L2_CID_SENSOR_COUNT:
		{
			controls[cid_idx].value =  mini_get_camera_count();
			break;
		}

		/* get camera infomation, include facing and orientation */
		case V4L2_CID_SENSOR_INFO:
		{
			u32 camera_id;
			mini_camera_sensor *psensor = NULL;
			camera_info_t *info = (struct camera_info *)(controls[cid_idx].string);
			camera_id = controls[cid_idx].size; /* reserved[0] in hal */

			psensor = mini_get_camera_sensor_from_array(camera_id);

			if (psensor == NULL) {
				print_error("fail to find sensor by id.");
				goto out;
			}
			if (NULL == info)
				print_error("info is NULL");
			else
				memcpy(info, &psensor->info, sizeof(camera_info_t));
			break;
		}

		/* get focus result */
		case V4L2_CID_FOCUS_RESULT:
		{
			mini_focus_result_s *result = (mini_focus_result_s *)(controls[cid_idx].string);
			mini_k3_isp_get_focus_result(result);
			break;
		}

		/* get focus rect information */
		case V4L2_CID_GET_FOCUS_RECT:
		{
			mini_camera_rect_s *rect = (mini_camera_rect_s *)(controls[cid_idx].string);
			mini_k3_isp_get_focus_rect(rect);
			break;
		}
		case V4L2_CID_GET_YUV_CROP_RECT:
		{
			mini_crop_rect_s *rect = (mini_crop_rect_s *)(controls[cid_idx].string);
			mini_k3_isp_get_yuv_crop_rect(rect);
			break;
		}

		default:
			break;

		}
	}

out:
	SAFE_UP(&cam->busy_lock);
	return ret;
}

static void k3_v4l2_set_sensor(sensor_index_t sensor_index, char *sensor_name)
{

	if (sensor_index >= CAMERA_SENSOR_MAX) {
		print_error("Unsuport sensor type : %d", sensor_index);
		return;
	}

    mini_relocate_camera_sensor_by_name(sensor_index,sensor_name);

	return;
}

static int k3_v4l2_ioctl_s_ext_ctrls(struct file *file, void *fh,
				     struct v4l2_ext_controls *arg)
{
	mini_v4l2_ctl_struct *cam 	= NULL;
	u32 cid_idx		= 0;
	int ret 		= 0;
	camera_state state;
	bool         reg_buf = false;

	/*
	 * For focus rect setting ,bracket setting and others...
	 */
	mini_focus_area_s *area = NULL;
	int  *bracket_ev = NULL;
	mini_metering_area_s *metering_area = NULL;
	mini_axis_triple *xyz = NULL;
	int func_ret = 0;

	struct v4l2_buffer vbuffer;
	struct v4l2_ext_controls *ext_ctls = arg;
	struct v4l2_ext_control *controls = NULL;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);
	SAFE_DOWN(&cam->busy_lock);

	if (ext_ctls->ctrl_class != V4L2_CTRL_CLASS_CAMERA) {
		print_error("unsupported ctrl class!");
		ret = -EINVAL;
		goto end;
	}

	/* allocate buffer */
	print_debug("user_ptr 0x%p, count %d", ext_ctls->controls, ext_ctls->count);
	controls = (struct v4l2_ext_control *)ext_ctls->controls;

	memset(&vbuffer, 0, sizeof(vbuffer));
	for (cid_idx = 0; cid_idx < ext_ctls->count; cid_idx++) {
		print_debug("cid_idx[%d], id[%d], value[0x%8x]", cid_idx,
			controls[cid_idx].id - V4L2_CID_PRIVACY, controls[cid_idx].value);
		if(controls[cid_idx].id>=V4L2_CID_HWA_BASE && controls[cid_idx].id<=V4L2_CID_HWA_MAX){
			ret =mini_hwa_v4l2_ioctl_s_ext_ctrls(&controls, controls[cid_idx].id,cid_idx);
			continue;
		}
		switch (controls[cid_idx].id) {
			/*get buffer type: video or capture */
		case V4L2_CID_BUFFER_TYPE:
			{
				vbuffer.type = controls[cid_idx].value;
				break;
			}

		case V4L2_CID_BUFFER_INDEX:
			{
				vbuffer.index = controls[cid_idx].value;
				break;
			}

			/*get buffer length */
		case V4L2_CID_BUFFER_LENGTH:
			{
				vbuffer.length = controls[cid_idx].value;
				break;
			}

			/*get buffer offset */
		case V4L2_CID_BUFFER_OFFSET:
			{
				if (controls[cid_idx].value == 0) {
					state = get_camera_state(vbuffer.type);
					if (state == STATE_MAX) {
						ret = -EINVAL;
						goto end;
					}
					print_info("clean up camera driver buffers, state:%d", state);
					mini_init_queue(&cam->data_queue, state);
					mini_camera_init_buffer(&cam->buffer_arr[state]);
					goto end;
				}

                if ( 0 != controls[cid_idx].value)
                                {
				        vbuffer.m.offset = controls[cid_idx].value;
				        reg_buf = true;
                                }
                                else
                                {
                                        print_error("fatal error phyaddr is null controls[cid_idx].value = 0x%x",controls[cid_idx].value);
                                        ret = -EINVAL;
                                        goto end;
                                }


				break;
			}
		case V4L2_CID_STATBUFFER_OFFSET:
			{
				state = get_camera_state(vbuffer.type);
				if (state == STATE_MAX) {
					ret = -EINVAL;
					goto end;
				}

				cam->buffer_arr[state].buffers[vbuffer.index].statphyaddr = controls[cid_idx].value;
				break;
			}
			/*
			 * below are used for focus rect definition
			 */
		case V4L2_CID_FOCUS_AREA_INFO:
			area = (mini_focus_area_s *) (controls[cid_idx].string);
			func_ret = mini_k3_isp_set_focus_area(area);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			goto end;
			break;

			/* For bracket information setting */
		case V4L2_CID_BRACKET_INFO:
			bracket_ev = (int *)(controls[cid_idx].string);
			func_ret = mini_k3_isp_set_bracket_info(bracket_ev);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			goto end;
			break;

		case V4L2_CID_METERING_AREA_INFO:
			metering_area = (mini_metering_area_s *)(controls[cid_idx].string);
			func_ret = mini_k3_isp_set_metering_area(metering_area);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			goto end;
			break;

		case V4L2_CID_SENSOR_INFO:
		{
			char * sensor_name;
			u8 cameraid;

			cameraid = controls[cid_idx].size;
			sensor_name = (char *)(controls[cid_idx].string);
			if (NULL != sensor_name)
				k3_v4l2_set_sensor(cameraid, sensor_name);
			break;
		}

		case V4L2_CID_SET_GSENSOR_STAT:
			xyz = (mini_axis_triple *)(controls[cid_idx].string);
			func_ret = mini_k3_isp_set_gsensor_stat(xyz);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			goto end;
			break;
		case  V4L2_CID_SET_HW_3A_PARAM:
		{
			mini_hw_3a_param *ae_result =  (mini_hw_3a_param*)(controls[cid_idx].string);
			func_ret = mini_ispv1_set_hw_3a_param(ae_result);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			break;
		}
		default:
			print_error("%s, id=%#x, value=%#x", __func__,
					controls[cid_idx].id, controls[cid_idx].value);
			ret = -EINVAL;
			goto end;
			break;

		}

	}

    if (reg_buf == true){
    	/* Only for register buffer start */
    	state = get_camera_state(vbuffer.type);
    	if (state == STATE_MAX) {
    		ret = -EINVAL;
    		goto end;
    	}
    	print_debug("state=%d, buf_count=%d", state, cam->buffer_arr[state].buf_count);
    	cam->buffer_arr[state].buf_count++;
    	k3_register_buffer(&(cam->buffer_arr[state].buffers[vbuffer.index]), &vbuffer);
    	INIT_LIST_HEAD(&(cam->buffer_arr[state].buffers[vbuffer.index].queue));


#ifdef DUMP_FILE
	if (state == STATE_CAPTURE)
		cam->buffer_arr[state].buffers[vbuffer.index].viraddr =
		    ioremap_nocache(vbuffer.m.offset, vbuffer.length);
#endif
	/* Only for register buffer end */
	}

end:

	SAFE_UP(&cam->busy_lock);
	return ret;

}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_reqbuffs;
 * Description : Allocate physical memory for camera;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int __attribute__((unused))  k3_v4l2_ioctl_reqbuffs(struct file *file, void *fh,
				  struct v4l2_requestbuffers *b)
{
	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_qbuf;
 * Description : Queue buffer into ready queue;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_qbuf(struct file *file, void *fh,
			      struct v4l2_buffer *b)
{
	int ret = 0;
	mini_v4l2_ctl_struct *cam = NULL;
	camera_state state;
	unsigned long lock_flags;

	print_debug("enter %s, type=%d, index=%d, phyaddr=%#x, size=%d, mem[%d]",
			__func__, b->type, b->index, b->m.offset, b->length, b->memory);

	SAFE_GET_DRVDATA(cam, fh);

	state = get_camera_state(b->type);
	if (state == STATE_MAX) {
		ret = -EINVAL;
		goto out;
	}

	if (b->index >= MAX_FRAME_NR) {
		print_error("%s buffer index invalid: %d", __func__, b->index);
		print_error("state=%d,buf_connt=%d", state, cam->buffer_arr[state].buf_count);
		ret = -EINVAL;
		goto out;
	}

	/* queue buffer to preview ready queue */
	if (V4L2_MEMORY_MMAP != b->memory) {
		cam->buffer_arr[state].buffers[b->index].phyaddr = b->m.offset;
		cam->buffer_arr[state].buffers[b->index].statphyaddr = b->reserved;
		cam->buffer_arr[state].buffers[b->index].size = b->length;
	}

	spin_lock_irqsave(&cam->data_queue.queue_lock, lock_flags);
	print_debug("%s, mini_isp_hw_data.cur_state = %d",  __func__,state);
	mini_add_to_queue(&cam->buffer_arr[state].buffers[b->index],
		     &cam->data_queue.ready_q[state], CAMERA_FLAG_READYQ);
	spin_unlock_irqrestore(&cam->data_queue.queue_lock, lock_flags);
out:
	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_dqbuf;
 * Description : Dequeue buffer from done queue.
 *               The calling process will be sleep until buffer is ready.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */

static int k3_v4l2_ioctl_dqbuf(struct file *file, void *fh,
			       struct v4l2_buffer *b)
{
	int ret = 0;
	mini_v4l2_ctl_struct *cam = NULL;
	mini_camera_frame_buf *frame = NULL;
	unsigned long lock_flags;
	camera_state state;
	signed long         wait_time;

	SAFE_GET_DRVDATA(cam, fh);
	/*print_debug("enter %s, cam 0x%x", __func__, (u32)cam); */

	state = get_camera_state(b->type);
	if (state == STATE_MAX) {
		ret = -EINVAL;
		goto out;
	}
	print_debug("enter %s, state=%d.", __func__, state);

	wait_time = CAM_WAIT_DQBUF_IRQ_TIMEOUT * HZ;

    /***************************************************************************
      capture in zsl offline mode ,need 4 multiple time at least to complete
      offline process.so we set 5.
    ***************************************************************************/
	if( (CAMERA_ZSL_ON == mini_k3_isp_get_zsl_state()) && (CAMERA_ZSL_OFFLINE == mini_k3_isp_get_zsl_proc())){
	    if (V4L2_BUF_TYPE_VIDEO_CAPTURE == b->type){
            wait_time = 5 * CAM_WAIT_DQBUF_IRQ_TIMEOUT * HZ;
        }
	}

    print_debug("wait_event_interruptible_timeout: %d",wait_time);
    if (!wait_event_interruptible_timeout(cam->data_queue.queue[state],
        (!list_empty(&cam->data_queue.done_q[state]) | !cam->running[state]),
        wait_time)) {
        if (!list_empty(&cam->data_queue.done_q[state])) {
            print_info("state:%d dequeue buffer time out <done_q(%d)>, but queue not empty.",
                    state, list_empty(&cam->data_queue.done_q[state]));
        } else {
            print_error("state:%d dequeue buffer time out <done_q(%d)>",
                    state, list_empty(&cam->data_queue.done_q[state]));
            ret = -ETIME;
            goto out;
        }
    } else if (signal_pending(current)) {
        print_error("%s %d signal_pending", __func__, __LINE__);
        ret = -ERESTARTSYS;
        goto out;
    }

	trace_dot(CAM, "14", 0);

	if (!cam->running[state]) {
		ret = -ECANCELED;
		goto out;
	}

    spin_lock_irqsave(&cam->data_queue.queue_lock, lock_flags);
    if (!list_empty(&cam->data_queue.done_q[state])) {
        frame = list_entry(cam->data_queue.done_q[state].next, mini_camera_frame_buf, queue);
        mini_del_from_queue(frame, CAMERA_FLAG_DONEQ);
    } else {
        ret = -ENOMEM;
        print_error("%s, line %d, done queue[%d] is empty.", __func__, __LINE__, state);
        spin_unlock_irqrestore(&cam->data_queue.queue_lock, lock_flags);
        goto out;
    }
    spin_unlock_irqrestore(&cam->data_queue.queue_lock, lock_flags);

	b->index = frame->index;
	b->bytesused = cam->fmt[state].fmt.pix.sizeimage;	/* FIXME already with stride */
	b->m.offset = frame->phyaddr;
	b->reserved= (u32)frame->statviraddr;
	memcpy(&(b->timestamp), &(frame->timestamp), sizeof(struct timeval));
#ifdef DUMP_FILE
	mini_dump_file("/data/yuv.yuv", frame->viraddr, 2592 * 1952 * 2);
#endif

	print_debug("exit %s, state=%d, index=%d, phyaddr is 0x%x", __func__, state,
		    b->index, frame->phyaddr);

#ifdef READ_BACK_RAW
	if (STATE_PREVIEW == state) {
		print_info("Line:%d, before update read ready++++++++++++", __LINE__);
		msleep(100);
		if (0 == buf_used) {
			buf_used = 1;
			mini_k3_isp_update_read_ready(buf_used);
		} else {
			buf_used = 0;
			mini_k3_isp_update_read_ready(buf_used);
		}
		print_info("Line:%d, after update read ready++++++++++++", __LINE__);
	}
#endif

out:

    return ret;

}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_streamon;
 * Description : Start isp to capture data for preview or picture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_streamon(struct file *file, void *fh,
				  enum v4l2_buf_type buf_type)
{
	int ret = -EINVAL;
	camera_state state;
	mini_v4l2_ctl_struct *cam = NULL;

	SAFE_GET_DRVDATA(cam, fh);

	/* if ZSL switch on */
	if (CAMERA_ZSL_ON == mini_k3_isp_get_zsl_state()){
        CHECK_STATE(STATE_IPP);
	}
	else{
        CHECK_STATE(STATE_PREVIEW);
        CHECK_STATE(STATE_CAPTURE);
        CHECK_STATE(STATE_IPP);
	}

	state = get_camera_state(buf_type);
	if (state == STATE_MAX) {
		return -EINVAL;
	}
	print_info("enter %s, state[%d],pid=%d", __func__, get_camera_state(buf_type),current->pid);

	SAFE_DOWN(&cam->busy_lock);

	ret = mini_k3_isp_stream_on(&cam->fmt[state].fmt.pix, buf_type, state,&cam->buffer_arr[STATE_IPP]);

    if (ret == 0)
    {
    	cam->pid[state] = current->pid;
    	cam->running[state] = 1;

        /* enable cap raw & proc img */
        if (CAMERA_ZSL_ON == mini_k3_isp_get_zsl_state() && (STATE_CAPTURE == state)){
            mini_k3_isp_set_zsl_proc_valid(true);
            mini_k3_isp_set_zsl_cap_valid(true);
        }

    #ifdef READ_BACK_RAW
    	if(STATE_PREVIEW == state)
    		buf_used = 0;
    #endif
    } else {
        print_error("%s:mini_k3_isp_stream_on fail.ret=%d.",__func__,ret);
    }

	SAFE_UP(&cam->busy_lock);
	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_streamoff;
 * Description : Stop isp to capture data for preivew or taking picture;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_streamoff(struct file *file, void *fh,
				   enum v4l2_buf_type buf_type)
{
	mini_v4l2_ctl_struct *cam = NULL;
	int ret = 0;
	camera_state state;
	struct semaphore *lock;

	print_info("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	state = get_camera_state(buf_type);
	if (state == STATE_MAX) {
		return -EINVAL;
	}

	lock = &cam->busy_lock;

    /* disable cap raw & proc img */
	if (CAMERA_ZSL_ON == mini_k3_isp_get_zsl_state() && (STATE_CAPTURE == state)){
	    /* hope zsl thread quit quickly */
    	mini_k3_isp_set_zsl_proc_valid(false);
    	mini_k3_isp_set_zsl_cap_valid(false);
    	lock = &cam->busy_lock_capture;
	}

	SAFE_DOWN(lock);

	ret = mini_k3_isp_stream_off(state);
	if (ret != 0 ){
	    print_error("%s:mini_k3_isp_stream_off fail.ret=%d.",__func__,ret);
	}

	/* disable isp to stop preview or capture */
	cam->running[state] = 0;
	cam->pid[state] = 0;
	wake_up_interruptible(&cam->data_queue.queue[state]);

	SAFE_UP(lock);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_start_process;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_start_process(mini_v4l2_ctl_struct *cam, u8 mode)
{
	int ret = -EINVAL;
	print_info("enter %s", __func__);

    if (CAMERA_ZSL_ON == mini_k3_isp_get_zsl_state())
    {
        print_info("zsl:do raw to yuv.");
    }
    else
    {
    	CHECK_STATE(STATE_PREVIEW);
    	CHECK_STATE(STATE_IPP);
	}

	ret = mini_k3_isp_start_process(&cam->fmt[STATE_CAPTURE].fmt.pix, mode,&(cam->buffer_arr[STATE_IPP]));
	if (ret != 0) {
		print_error("error : mini_k3_isp_start_process() faild!");
		return ret;
	}

    if (CAMERA_ZSL_ON != mini_k3_isp_get_zsl_state())
    {
    	cam->pid[STATE_IPP] = current->pid;
    	cam->running[STATE_IPP] = 1;
	}

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_start_process;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_stop_process(mini_v4l2_ctl_struct *cam, ipp_mode mode)
{
	int ret = -EINVAL;
	print_info("enter %s", __func__);

    if (CAMERA_ZSL_ON != mini_k3_isp_get_zsl_state()){
        CHECK_STATE(STATE_PREVIEW);
    }

    ret = mini_k3_isp_stop_process(mode);
    if (ret != 0) {
        print_error("error : mini_k3_isp_start_process() faild!");
        return ret;
    }

    if (CAMERA_ZSL_ON != mini_k3_isp_get_zsl_state()){
        cam->pid[STATE_IPP] = 0;
        cam->running[STATE_IPP] = 0;
    }
    return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_s_param;
 * Description : Set parameters for isp and now we only use it to set frame rate.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_s_param(struct file *file, void *fh,
				 struct v4l2_streamparm *a)
{
	mini_v4l2_ctl_struct *cam = NULL;
	struct v4l2_frmivalenum fi;
	mini_camera_sensor *sensor;
	u8 max_fps = CAMERA_MAX_FRAMERATE;
	u8 min_fps = CAMERA_MIN_FRAMERATE;
	u8 mid_fps = CAMERA_MID_FRAMERATE;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);
	/*CHECK_STATE(STATE_PREVIEW);
	   CHECK_STATE(STATE_CAPTURE);
	   CHECK_STATE(STATE_IPP); */

	/* check frame interval */
	memset(&fi, 0x00, sizeof(fi));
	fi.type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fi.discrete.denominator = a->parm.capture.timeperframe.denominator;
	fi.discrete.numerator = a->parm.capture.timeperframe.numerator;
	if (0 != mini_k3_isp_try_frameintervals(&fi))
		return -EINVAL;

	SAFE_DOWN(&cam->busy_lock);
	cam->frame_rate = a->parm.capture.timeperframe;

	sensor = cam->sensor;
	if (sensor->effect != NULL) {
		u32 *this_fps = sensor->effect->ae_param.fps;
		max_fps = this_fps[0];
        mid_fps = this_fps[1];
		min_fps = this_fps[2];
	}

	if (CAMERA_USE_K3ISP == sensor->isp_location) {
		if (0 != cam->frame_rate.denominator) {
			max_fps = cam->frame_rate.denominator / cam->frame_rate.numerator;
			min_fps = max_fps;
			mid_fps = max_fps;
		}

		mini_k3_isp_set_fps(CAMERA_FPS_MAX, max_fps);
		mini_k3_isp_set_fps(CAMERA_FPS_MIN, min_fps);
		mini_k3_isp_set_fps(CAMERA_FPS_MID, mid_fps);
	} else {
		if (sensor->update_framerate) {
			if (0 == cam->frame_rate.denominator) {
				sensor->update_framerate(CAMERA_FRAME_RATE_AUTO);
			} else {
				sensor->update_framerate(CAMERA_FRAME_RATE_FIX_MAX);
			}
		}
	}
	SAFE_UP(&cam->busy_lock);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_g_param;
 * Description : Get parameters of isp and now we only use it to get frame rate;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_g_param(struct file *file, void *fh,
				 struct v4l2_streamparm *streamparm)
{
	mini_v4l2_ctl_struct *cam = NULL;

	print_debug("enter %s", __func__);
	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);
	streamparm->parm.capture.timeperframe = cam->frame_rate;
	SAFE_UP(&cam->busy_lock);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_enum_framesizes;
 * Description : enumerate all frame sizes that supported by isp and
 *               camera sensors;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_enum_framesizes(struct file *file, void *fh,
					 struct v4l2_frmsizeenum *fsize)
{
	mini_v4l2_ctl_struct *cam = NULL;
	int ret = 0;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);
	ret = mini_k3_isp_enum_framesizes(fsize);
	SAFE_UP(&cam->busy_lock);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_enum_frameintervals;
 * Description : enumerate all frame intervals that supported by camera sensors;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_enum_frameintervals(struct file *file, void *fh,
					     struct v4l2_frmivalenum *fival)
{
	mini_v4l2_ctl_struct *cam = NULL;
	int ret = 0;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);
	/* FIXME: HAL do not need store capability of auto fps */
	if (fival->index == 0) {
		fival->index++;
	}
	ret = mini_k3_isp_enum_frameintervals(fival);
	SAFE_UP(&cam->busy_lock);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_enum_fmt_capture;
 * Description : enumerate all picture data format that supported camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_enum_fmt_capture(struct file *file, void *fh,
					  struct v4l2_fmtdesc *fmt)
{
	mini_v4l2_ctl_struct *cam = NULL;
	int ret = 0;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);
	ret = mini_k3_isp_enum_fmt(fmt, STATE_CAPTURE);
	SAFE_UP(&cam->busy_lock);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_ioctl_enum_fmt_preview;
 * Description : enumerate all preview data format that supported camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_ioctl_enum_fmt_preview(struct file *file, void *fh,
					  struct v4l2_fmtdesc *fmt)
{
	mini_v4l2_ctl_struct *cam = NULL;
	int ret = 0;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);
	ret = mini_k3_isp_enum_fmt(fmt, STATE_PREVIEW);
	SAFE_UP(&cam->busy_lock);

	return ret;
}
int k3_v4l2_check_camera(mini_camera_sensor **sensor, sensor_index_t type)
{
	int ret = -ENODEV;
	int index = 0;
	mini_camera_sensor *temp_sensor = NULL;

	if (type >= CAMERA_SENSOR_MAX) {
		print_error("Unsuport sensor type : %d", type);
		goto out;
	}

	for(; index < CAMERA_SENSOR_NUM_MAX; index ++) {
		temp_sensor = mini_get_camera_sensor_from_array(type);
		if (NULL == temp_sensor) {
			print_error("fail to get camera [%d]", type);
			ret = -ENODEV;
			break;
		}
		ret = mini_k3_isp_set_camera(temp_sensor, NULL, CAMERA_SENSOR_UNKNOWN);
		if (ret == -ENODEV) {
			mini_unregister_camera_sensor(temp_sensor->sensor_index, temp_sensor);
		} else {
			mini_clean_camera_sensor(type);
			mini_register_camera_sensor(type, temp_sensor);
			*sensor = temp_sensor;
			break;
		}
		msleep(10);
	}
out:
	return ret;
}
/*
 **************************************************************************
 * FunctionName: k3_v4l2_set_camera;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int k3_v4l2_set_camera(mini_v4l2_ctl_struct *cam, int new_sensor)
{
	int ret = 0;
	mini_camera_sensor *sensor = NULL;
	mini_camera_sensor **pri_sensor = NULL;
	mini_camera_sensor **sec_sensor = NULL;

	print_debug("enter %s, new_sensor=%d", __func__, new_sensor);

	/* get camera sensor */
	sensor = mini_get_camera_sensor_from_array(new_sensor);
	if (NULL == sensor) {
		print_error("fail to get camera [%d]", new_sensor);
		ret = -ENODEV;
		goto out;
	}

	/* set it to isp */
	if (0 != mini_k3_isp_hw_init_regs(sensor)) {
		print_error("fail to init isp hw register");
		ret = -ENODEV;
		goto out;
	}

	pri_sensor = mini_get_camera_sensor(CAMERA_SENSOR_PRIMARY);
	sec_sensor = mini_get_camera_sensor(CAMERA_SENSOR_SECONDARY);

	mini_camera_power_id_gpio(POWER_ON);


	if (CAMERA_SENSOR_PRIMARY == new_sensor) {
        k3_v4l2_check_camera(pri_sensor, CAMERA_SENSOR_PRIMARY);
		if (NULL == *pri_sensor) {
			print_error("Do not support sensor type:%d", new_sensor);
			ret = -ENODEV;
			goto out;
		}
        cam->sensor = *pri_sensor;

	} else {
	    k3_v4l2_check_camera(sec_sensor, CAMERA_SENSOR_SECONDARY);
		if (NULL == *sec_sensor) {
			print_error("Do not support sensor type:%d", new_sensor);
			ret = -ENODEV;
			goto out;
		}
        cam->sensor = *sec_sensor;


	}
	mini_camera_power_id_gpio(POWER_OFF);
    mini_set_camera_sensor(new_sensor,cam->sensor);

	cam->cur_sensor = new_sensor;
	print_info("set sensor to [%d, %s]", cam->cur_sensor, cam->sensor->info.name);

out:

	return ret;
}

#define K3_CAMERA_ENABLE_SYSFS
#ifdef	K3_CAMERA_ENABLE_SYSFS

static ssize_t k3_sensors_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int ret = 0;
	mini_camera_sensor **pri_sensor = NULL;
	mini_camera_sensor **sec_sensor = NULL;

	print_debug("enter %s", __FUNCTION__);
	pri_sensor = mini_get_camera_sensor(CAMERA_SENSOR_PRIMARY);
	sec_sensor = mini_get_camera_sensor(CAMERA_SENSOR_SECONDARY);
	if ((NULL != *pri_sensor) && (NULL != *sec_sensor)) {
		snprintf(buf, BUF_LEN, "front sensor:[%s]; back sensor:[%s]\n", (*sec_sensor)->info.name, (*pri_sensor)->info.name);
		ret += (strlen(buf) + 1);
	} else {
		snprintf(buf, BUF_LEN, "Please run Camera first\n");
		ret = strlen(buf) + 1;
	}
	return ret;
}
static DEVICE_ATTR(sensors, S_IRUGO, k3_sensors_show, NULL);


//misp debug start
u32 misp_cmd_delay_time = 5;
u32 misp_cmd_ae_mode = 0;
u32 misp_cmd_s1_lock = 0;
u32 misp_vc_control = 1;
u32 misp_skip_cap_frame = 1;
u32 misp_color_pattern = 1;
u32 misp_use_fixed_awb = 0;
u32 misp_meta_data_log = 0;
u32 misp_dump_meta_data = 0;
static ssize_t misp_debug_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int len;

	len = snprintf(buf, PAGE_SIZE, "modeied for misp:\n"
									"cmd_delay_time=%u\n"
									"cmd_ae_mode=%u\n"
									"cmd_s1_lock=%u\n"
									"vc_control=%u\n"
									"skip_cap_frame=%u\n"
									"color_pattern=%s\n"
									"use_fixed_awb=%u\n"
									"meta_data_log=%u\n"
									"misp_dump_meta_data=%u\n",
									misp_cmd_delay_time,
									misp_cmd_ae_mode,
									misp_cmd_s1_lock,
									misp_vc_control,
									misp_skip_cap_frame,
									(misp_color_pattern==1)?"BGGR(1)":"RGGB(0)",
									misp_use_fixed_awb,
									misp_meta_data_log,
									misp_dump_meta_data);

	return len;

}

static ssize_t misp_debug_store(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	const char *pos;

	print_info("buf=%s", buf);

	pos = buf;
	if( 0==strncmp("cmd_delay_time", pos, strlen("cmd_delay_time")) ){
		pos += strlen("cmd_delay_time");
		while (*pos) {
			if (isdigit(*pos))
				break;
			else
				pos++;
		}
		misp_cmd_delay_time = simple_strtoul(pos, NULL, 0);
	}else if( 0==strncmp("cmd_ae_mode", pos, strlen("cmd_ae_mode")) ){
		pos += strlen("cmd_ae_mode");
		while (*pos) {
			if (isdigit(*pos))
				break;
			else
				pos++;
		}
		misp_cmd_ae_mode = simple_strtoul(pos, NULL, 0);
	}else if( 0==strncmp("cmd_s1_lock", pos, strlen("cmd_s1_lock")) ){
		pos += strlen("cmd_s1_lock");
		while (*pos) {
			if (isdigit(*pos))
				break;
			else
				pos++;
		}
		misp_cmd_s1_lock = simple_strtoul(pos, NULL, 0);
		if (misp_cmd_s1_lock) {
			camera_agent_s1_lock(CAMERA_SENSOR_PRIMARY);
		} else {

		}
	}else if( 0==strncmp("vc_control", pos, strlen("vc_control")) ){
		pos += strlen("vc_control");
		while (*pos) {
			if (isdigit(*pos))
				break;
			else
				pos++;
		}
		misp_vc_control = simple_strtoul(pos, NULL, 0);
	}else if( 0==strncmp("skip_cap_frame", pos, strlen("skip_cap_frame")) ) {
		pos += strlen("skip_cap_frame");
		while (*pos) {
			if (isdigit(*pos))
				break;
			else
				pos++;
		}
		misp_skip_cap_frame = simple_strtoul(pos, NULL, 0);
	}else if( 0==strncmp("color_pattern", pos, strlen("color_pattern")) ) {
		pos += strlen("color_pattern");
		while (*pos) {
			if (isalpha(*pos))
				break;
			else
				pos++;
		}

		if( 0==strncmp("BGGR", pos, strlen("BGGR")) )
			misp_color_pattern = 1;
		else
			misp_color_pattern = 0;
	}else if( 0==strncmp("use_fixed_awb", pos, strlen("use_fixed_awb")) ) {
		pos += strlen("use_fixed_awb");
		while (*pos) {
			if (isdigit(*pos))
				break;
			else
				pos++;
		}
		misp_use_fixed_awb = simple_strtoul(pos, NULL, 0);
	}else if( 0==strncmp("meta_data_log", pos, strlen("meta_data_log")) ) {
		pos += strlen("meta_data_log");
		while (*pos) {
			if (isdigit(*pos))
				break;
			else
				pos++;
		}
		misp_meta_data_log = simple_strtoul(pos, NULL, 0);
	}else if( 0==strncmp("misp_dump_meta_data", pos, strlen("misp_dump_meta_data")) ) {
		pos += strlen("misp_dump_meta_data");
		while (*pos) {
			if (isdigit(*pos))
				break;
			else
				pos++;
		}
		misp_dump_meta_data = simple_strtoul(pos, NULL, 0);
	}

	return count;
}

static DEVICE_ATTR(misp_debug, 0644, misp_debug_show, misp_debug_store);
//misp debug end


static struct kobject *k3_camera_kobj;
static int k3_sensors_create_sysfs(void)
{
	int ret;
	k3_camera_kobj = kobject_create_and_add("k3_camera", NULL);
	if (k3_camera_kobj == NULL) {
		print_error("failed to create kobject");
		ret = -ENOMEM;
		return ret;
	}

	ret = sysfs_create_file(k3_camera_kobj, &dev_attr_sensors.attr);
	if (ret) {
		print_error("failed to create sysfs files");
		return ret;
	}

	ret = sysfs_create_file(k3_camera_kobj, &dev_attr_misp_debug.attr);
	if (ret) {
		print_error("failed to create sysfs files");
		return ret;
	}

	return 0;
}

static void k3_sensors_remove_sysfs(void)
{
	sysfs_remove_file(k3_camera_kobj, &dev_attr_sensors.attr);
	kobject_del(k3_camera_kobj);
}

#endif

/*
 **************************************************************************
 * FunctionName: k3_v4l2_open;
 * Description : Called by linux VFS when application call 'open':
 *               A. init isp when the device is opened for the first time.
 *               B. init and power on camera sensor for the first time.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_open(struct file *file)
{
	int ret = 0;
	struct video_device *dev = video_devdata(file);
	mini_v4l2_ctl_struct *cam = NULL;
    trace_dot(CAM, "1", 0);

	WARN_ON(dev == NULL);

	print_info("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, dev);
	if (!cam) {
		print_error("%s, cam is null", __func__);
		return -ENODEV;
	}

	SAFE_DOWN(&cam->busy_lock);

	if (0 == cam->open_count++) {
		mini_camera_flashlight *flashlight = NULL;
		cam->running[STATE_PREVIEW] = 0;
		cam->running[STATE_CAPTURE] = 0;
		cam->running[STATE_IPP] = 0;
		cam->pid[STATE_PREVIEW] = 0;
		cam->pid[STATE_CAPTURE] = 0;
		cam->pid[STATE_IPP] = 0;
		memset(&cam->fmt[STATE_PREVIEW], 0x00, sizeof(cam->fmt[STATE_PREVIEW]));
		memset(&cam->fmt[STATE_CAPTURE], 0x00, sizeof(cam->fmt[STATE_CAPTURE]));
		memset(&cam->fmt[STATE_IPP], 0x00, sizeof(cam->fmt[STATE_IPP]));
		memset(&cam->frame_rate, 0x00, sizeof(cam->frame_rate));

		/* init camera data struct here on first open */
		mini_init_queue(&cam->data_queue, STATE_PREVIEW);
		mini_init_queue(&cam->data_queue, STATE_CAPTURE);
		mini_init_queue(&cam->data_queue, STATE_IPP);
		mini_camera_init_buffer(&cam->buffer_arr[STATE_PREVIEW]);
		mini_camera_init_buffer(&cam->buffer_arr[STATE_CAPTURE]);
		mini_camera_init_buffer(&cam->buffer_arr[STATE_IPP]);

		k3_set_default_fmt(&cam->fmt[STATE_PREVIEW], STATE_PREVIEW);
		k3_set_default_fmt(&cam->fmt[STATE_CAPTURE], STATE_CAPTURE);
		k3_set_default_fmt(&cam->fmt[STATE_IPP], STATE_IPP);
		/* init isp controller */
		ret = mini_k3_isp_init(v4l2_ctl.pdev, &v4l2_ctl.data_queue);
		if (ret != 0) {
			print_error("error : fail to init ISP");
			cam->open_count = 0;
			mini_k3_isp_exit(cam);
			goto out;
		}
		flashlight = mini_get_camera_flash();
		if (flashlight)
			flashlight->init();
	} else {
		print_info("%s failed : camera already opened, open_count[%d]",
			   __func__, cam->open_count);
	}

out:
	file->private_data = dev;
	SAFE_UP(&cam->busy_lock);

    trace_dot(CAM, "2", 0);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_close;
 * Description : Called by linux VFS when application call 'close':
 *               A. power down camera sensor when the last process close the device.
 *               B. shut down the clock gating of isp when the last process close the device.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_close(struct file *file)
{
	struct video_device *dev = (struct video_device *)file->private_data;
	mini_v4l2_ctl_struct *cam = NULL;

	print_info("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, dev);

	SAFE_DOWN(&cam->busy_lock);

	if (--cam->open_count <= 0) {
		mini_camera_flashlight *flashlight = NULL;

		cam->open_count = 0;

		/* add close operation here */
		if (cam->running[STATE_CAPTURE]) {
			print_error("!!!!!!!!wicky, it should not happen!");
		}
		if (cam->running[STATE_CAPTURE]) {
			mini_k3_isp_stream_off(STATE_CAPTURE);
			cam->running[STATE_CAPTURE] = 0;
		} else if (cam->running[STATE_PREVIEW]) {
			mini_k3_isp_stream_off(STATE_PREVIEW);
			cam->running[STATE_PREVIEW] = 0;
		}

		mini_k3_isp_exit(cam);

		/* release dvfs block */
		/*
		   if (0 != cam->pm_profile_flag)
		   {
		   k3_release_dvfs_profile();
		   }
		 */
		flashlight = mini_get_camera_flash();
		if (flashlight)
			flashlight->exit();

		/* wake up user process */
		wake_up_interruptible(&cam->data_queue.queue[STATE_IPP]);
		wake_up_interruptible(&cam->data_queue.queue[STATE_CAPTURE]);
		wake_up_interruptible(&cam->data_queue.queue[STATE_PREVIEW]);
	}

	SAFE_UP(&cam->busy_lock);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_mmap;
 * Description : Map the given physical memory to user space;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
#ifdef K3_V4L2_CAPTURE_TEST
static int k3_v4l2_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct video_device *dev = (struct video_device *)file->private_data;
	mini_v4l2_ctl_struct *cam = NULL;

	unsigned long size;
	int ret = 0;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, dev);

	SAFE_DOWN(&cam->busy_lock);
	size = vma->vm_end - vma->vm_start;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	if (remap_pfn_range(vma, vma->vm_start,
			    vma->vm_pgoff, size, vma->vm_page_prot)) {
		print_error("%s, remap_pfn_range fail", __func__);
		ret = -ENOBUFS;
	} else {
		vma->vm_flags &= ~VM_IO;
		ret = 0;
	}

	SAFE_UP(&cam->busy_lock);
	return ret;
}
#endif

/* v4l2 function table */
static const struct v4l2_ioctl_ops k3_v4l2_ioctl_ops = {
	.vidioc_querycap 			= k3_v4l2_ioctl_querycap,
	.vidioc_try_fmt_vid_cap 		= k3_v4l2_ioctl_try_fmt_vid_capture,
	.vidioc_try_fmt_vid_overlay 		= k3_v4l2_ioctl_try_fmt_vid_preview,
	.vidioc_s_fmt_vid_cap 			= k3_v4l2_ioctl_s_fmt_capture,
	.vidioc_g_fmt_vid_cap 			= k3_v4l2_ioctl_g_fmt_capture,
	.vidioc_s_fmt_vid_overlay 		= k3_v4l2_ioctl_s_fmt_preview,
	.vidioc_g_fmt_vid_overlay 		= k3_v4l2_ioctl_g_fmt_preview,
	.vidioc_g_fmt_type_private 		= k3_v4l2_ioctl_g_fmt_private,
	.vidioc_querybuf 			= NULL,
	.vidioc_g_ctrl 				= k3_v4l2_ioctl_g_ctrl,
	.vidioc_s_ctrl 				= k3_v4l2_ioctl_s_ctrl,
	.vidioc_reqbufs 			= NULL,
	.vidioc_qbuf 				= k3_v4l2_ioctl_qbuf,
	.vidioc_streamon 			= k3_v4l2_ioctl_streamon,
	.vidioc_dqbuf 				= k3_v4l2_ioctl_dqbuf,
	.vidioc_streamoff 			= k3_v4l2_ioctl_streamoff,
	.vidioc_s_parm 				= k3_v4l2_ioctl_s_param,
	.vidioc_g_parm 				= k3_v4l2_ioctl_g_param,
	.vidioc_enum_fmt_vid_cap 		= k3_v4l2_ioctl_enum_fmt_capture,
	.vidioc_enum_fmt_vid_overlay 		= k3_v4l2_ioctl_enum_fmt_preview,
	.vidioc_enum_framesizes 		= k3_v4l2_ioctl_enum_framesizes,
	.vidioc_enum_frameintervals 		= k3_v4l2_ioctl_enum_frameintervals,
	.vidioc_default 			= k3_v4l2_ioctl_g_caps,
	.vidioc_g_ext_ctrls 			= k3_v4l2_ioctl_g_ext_ctrls,
	.vidioc_s_ext_ctrls 			= k3_v4l2_ioctl_s_ext_ctrls,
};

static struct v4l2_file_operations k3_v4l2_fops = {
	.owner = THIS_MODULE,
	.open = k3_v4l2_open,
	.release = k3_v4l2_close,
#ifdef K3_V4L2_CAPTURE_TEST
	.mmap = k3_v4l2_mmap,
#endif
	/* in ZSL mode,preview and capture will DQ at the same time. */
	.unlocked_ioctl = video_ioctl2,
};

/* video device template */
static struct video_device k3_v4l2_camera = {
	.name = "k3-camera",
	.minor = -1,
	/* .vfl_type   = VID_TYPE_CAPTURE, */
	.release = video_device_release,
	.fops = &k3_v4l2_fops,
	.ioctl_ops = &k3_v4l2_ioctl_ops,
};

/*
 **************************************************************************
 * FunctionName: k3_init_v4l2_ctl;
 * Description : Set default value of mini_v4l2_ctl_struct;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_init_v4l2_ctl(mini_v4l2_ctl_struct *v4l2_ctl)
{
	print_debug("enter %s", __func__);

	memset(v4l2_ctl, 0x00, sizeof(*v4l2_ctl));

	/* allocate a new video device and init it */
	v4l2_ctl->video_dev = video_device_alloc();
	if (!v4l2_ctl->video_dev) {
		print_error("fail to allocate video device !!");
		return -ENOMEM;
	}
	sema_init(&v4l2_ctl->busy_lock, 1);
	sema_init(&v4l2_ctl->busy_lock_capture, 1);
	spin_lock_init(&v4l2_ctl->data_queue.queue_lock);

	memcpy(v4l2_ctl->video_dev, &k3_v4l2_camera, sizeof(k3_v4l2_camera));
	video_set_drvdata(v4l2_ctl->video_dev, v4l2_ctl);

	print_debug("enter %s, cam 0x%x", __func__, (u32) v4l2_ctl);

	dev_set_drvdata(&k3_v4l2_camera.dev, (void *)v4l2_ctl);
	v4l2_ctl->video_dev->minor = -1;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: k3_deinit_v4l2_ctl;
 * Description : Deinit mini_v4l2_ctl_struct;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void k3_deinit_v4l2_ctl(mini_v4l2_ctl_struct *v4l2_ctl)
{
	print_debug("enter %s", __func__);

	if (v4l2_ctl->video_dev) {
		video_device_release(v4l2_ctl->video_dev);
		v4l2_ctl->video_dev = NULL;
	}

	return;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_probe;
 * Description : probe isp driver;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int k3_v4l2_probe(struct platform_device *pdev)
{
	int ret = -ENODEV;

	print_info("enter K3 camera v4l2 driver probe");

	/* init camera control struct */
	ret = k3_init_v4l2_ctl(&v4l2_ctl);
	if (ret != 0) {
		print_error("fail to init camera control struct !!");
		return ret;
	}

	ret = video_register_device(v4l2_ctl.video_dev, VFL_TYPE_GRABBER, video_nr);
	if (ret != 0) {
		print_error("fail to register video device !!");
		k3_deinit_v4l2_ctl(&v4l2_ctl);
		return ret;
	}
	v4l2_ctl.pdev = pdev;

#ifdef	K3_CAMERA_ENABLE_SYSFS
	k3_sensors_create_sysfs();
#endif

	print_info("K3 camera v4l2 driver init OK !!");
	return 0;

}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_remove;
 * Description : probe isp driver;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __exit int k3_v4l2_remove(struct platform_device *pdev)
{
	print_info("enter K3 camera v4l2 driver remove");
	k3_deinit_v4l2_ctl(&v4l2_ctl);

	if (v4l2_ctl.video_dev) {
		video_unregister_device(v4l2_ctl.video_dev);
		v4l2_ctl.video_dev = NULL;
	}
#ifdef	K3_CAMERA_ENABLE_SYSFS
	k3_sensors_remove_sysfs();
#endif
	return 0;
}

#ifdef	CONFIG_PM
/*
 **************************************************************************
 * FunctionName: k3_v4l2_resume;
 * Description : Resume camera isp and sensor to work state;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_resume(struct platform_device *pdev)
{
	int ret = 0;

	print_info("enter %s +", __func__);

	if (0 == v4l2_ctl.open_count) {
		/* power down all camera sensor */
		/*
		   camera_set_power(0, 0);
		   camera_set_power(1, 0);
		 */
	} else {
		print_error("BUG: should not be HERE !! [open_count=%d]",
			    v4l2_ctl.open_count);

        mini_k3_isp_lock_ddr_freq()/* req ddr freq lock */;

        mini_k3_isp_try_cpuidle_vote();

		/* init all queues */
		/* init camera data struct here on first open */
		mini_init_queue(&v4l2_ctl.data_queue, STATE_PREVIEW);
		mini_init_queue(&v4l2_ctl.data_queue, STATE_CAPTURE);
		mini_init_queue(&v4l2_ctl.data_queue, STATE_IPP);
		mini_camera_init_buffer(&v4l2_ctl.buffer_arr[STATE_PREVIEW]);
		mini_camera_init_buffer(&v4l2_ctl.buffer_arr[STATE_CAPTURE]);
		mini_camera_init_buffer(&v4l2_ctl.buffer_arr[STATE_IPP]);

		/* init camera controller */
		if (0 != mini_k3_isp_poweron()) {
			print_error("Failed to init isp while resuming");
			mini_k3_isp_poweroff();
			return -ENOMEM;
		}

		ret = k3_v4l2_set_camera(&v4l2_ctl, v4l2_ctl.cur_sensor);

		print_info("Camera resume successfully");
	}
	print_info("exit %s -", __func__);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: k3_v4l2_suspend;
 * Description : Suspend isp and camera sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_v4l2_suspend(struct platform_device *pdev, pm_message_t state)
{
	print_info("enter %s +", __func__);
	if (0 != v4l2_ctl.open_count) {
		print_error("BUG: should NOT be here [open_count=%d]",
			    v4l2_ctl.open_count);

		/* close camera & isp hardware */
		mini_k3_isp_poweroff();

        mini_k3_isp_unlock_ddr_freq()/* cancel and release ddr freq lock */;

        mini_k3_isp_cancel_cpuidle_vote();
	}
	print_info("Camera suspend successfully");
	print_info("exit %s -", __func__);
	return 0;
}
#endif /*CONFIG_PM */



static const struct of_device_id hisi_isp_dt_match[] = {
	{.compatible = "hisi,hisi_isp", },
	{}
};
MODULE_DEVICE_TABLE(of, hisi_isp_dt_match);

static struct platform_driver k3_v4l2_driver = {
	.probe = k3_v4l2_probe,
	.remove = /*__devexit_p*/(k3_v4l2_remove),

#ifdef	CONFIG_PM
	.suspend = k3_v4l2_suspend,
	.resume = k3_v4l2_resume,
#endif /*CONFIG_PM */

	.shutdown = NULL,

	.driver = {
		   .name = "hisi_isp",
		   .owner = THIS_MODULE,
		   .of_match_table = hisi_isp_dt_match
		   /*.bus = &platform_bus_type,*/
		   },
};
#ifdef CONFIG_DEBUG_FS
static int isp_reg_debug_open(struct inode *inode, struct file *file)
{
	file->private_data = inode->i_private;
	print_info("%s debug in %s\n", __func__, (char *) file->private_data);
	return 0;
}

extern void ispv1_read_isp_seq(struct mini_isp_reg_t *pseq, u32 seq_size);
static ssize_t isp_reg_debug_write(struct file *filp,
	const char __user *ubuf, size_t cnt, loff_t *ppos)
{
	struct file *dfilp = NULL;
    mm_segment_t fs;
    int i;
    char buf[32]={0};

	dfilp = filp_open("/data/ispregs", O_CREAT|O_WRONLY, 0666);
	if (IS_ERR_OR_NULL(dfilp)) {
		print_error("%s, failed to open file!", __func__);
		goto ERROR;
	}

    for(i=0; mini_isp_regs_list[i].subaddr!=0; i++){
        mini_isp_regs_list[i].value = 0;
    }

    ispv1_read_isp_seq(mini_isp_regs_list, sizeof(mini_isp_regs_list)/sizeof(mini_isp_regs_list[0]));

	fs = get_fs();
	set_fs(KERNEL_DS);

    for(i=0; mini_isp_regs_list[i].subaddr!=0; i++){
        memset(buf, 0x0, sizeof(buf));
        snprintf(buf, BUF_LEN,"\nreg[0x%x]=0x%x,", mini_isp_regs_list[i].subaddr, mini_isp_regs_list[i].value);
        vfs_write(dfilp, &buf[0], sizeof(buf), &dfilp->f_pos);
    }

	set_fs(fs);
	print_info("%s, write file OK.", __func__);

ERROR:
	if (NULL != dfilp) {
		filp_close(dfilp, NULL);
	}

    printk("%s exit.\n", __func__);
	return cnt;
}


//static ssize_t isp_reg_debug_read(struct file *filp, char __user *buffer,
//	size_t count, loff_t *ppos)
//{
//	return count;
//}


static const struct file_operations debugfs_isp_reg_fops = {
	.open = isp_reg_debug_open,
	.write = isp_reg_debug_write,
	//.read = isp_reg_debug_read,
};
#endif

#if 0
/*
 **************************************************************************
 * FunctionName: camera_init;
 * Description : module init function:
 *               A. register platform device and driver.
 *               B. init v4l2_ctl struct.
 *               C. init video device to kernel.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int camera_init(void)
{
	int ret = 0;
	print_info("\nK3 camera v4l2 driver init");

	ret = platform_driver_register(&k3_v4l2_driver);
	if (ret != 0) {
		print_error("fail to register platform driver !!");
	}

#ifdef CONFIG_DEBUG_FS
	debugfs_camera_dir = debugfs_create_dir("camera", NULL);
	debugfs_isp_reg = debugfs_create_file("isp_reg",
											S_IFREG |S_IWUSR|S_IWGRP,
											debugfs_camera_dir,
											(void *) "isp_reg",
											&debugfs_isp_reg_fops);
#endif
	return ret;
}

/*
 **************************************************************************
 * FunctionName: camera_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit camera_exit(void)
{
	if (v4l2_ctl.video_dev) {
		video_unregister_device(v4l2_ctl.video_dev);
		v4l2_ctl.video_dev = NULL;
	}

#ifdef CONFIG_DEBUG_FS
	if (NULL != debugfs_camera_dir) {
		debugfs_remove(debugfs_camera_dir);
	}
#endif
	print_info("K3 camera v4l2 driver exit !!");

	platform_driver_unregister(&k3_v4l2_driver);

	return;
}

module_init(camera_init);
module_exit(camera_exit);
module_param(video_nr, int, 0444);

MODULE_AUTHOR("HISILICON");
MODULE_DESCRIPTION("V4L2 capture driver for K3 based cameras");
MODULE_LICENSE("GPL");
MODULE_SUPPORTED_DEVICE("video");
#endif

/*
 **************************************************************************
 * FunctionName: camera_init;
 * Description : module init function:
 *               A. register platform device and driver.
 *               B. init v4l2_ctl struct.
 *               C. init video device to kernel.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_isp_camera_init(void)
{
	int ret = 0;
	print_info("\nK3 camera v4l2 driver init");

	ret = platform_driver_register(&k3_v4l2_driver);
	if (ret != 0) {
		print_error("fail to register platform driver !!");
	}

#ifdef CONFIG_DEBUG_FS
	debugfs_camera_dir = debugfs_create_dir("camera", NULL);
	debugfs_isp_reg = debugfs_create_file("isp_reg",
											S_IFREG |S_IWUSR|S_IWGRP,
											debugfs_camera_dir,
											(void *) "isp_reg",
											&debugfs_isp_reg_fops);
#endif
	return ret;
}

/*
 **************************************************************************
 * FunctionName: camera_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mini_isp_camera_exit(void)
{
	if (v4l2_ctl.video_dev) {
		video_unregister_device(v4l2_ctl.video_dev);
		v4l2_ctl.video_dev = NULL;
	}

#ifdef CONFIG_DEBUG_FS
	if (NULL != debugfs_camera_dir) {
		debugfs_remove(debugfs_camera_dir);
	}
#endif
	print_info("K3 camera v4l2 driver exit !!");

	platform_driver_unregister(&k3_v4l2_driver);

	return;
}
/********************************** END **********************************************/
