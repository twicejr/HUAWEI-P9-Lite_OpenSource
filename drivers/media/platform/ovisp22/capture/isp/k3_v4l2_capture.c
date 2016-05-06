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
#include <linux/device.h>
#include <linux/bug.h>
#include <linux/proc_fs.h>
#include "k3_v4l2_capture.h"
/*#define DEBUG_DEBUG 1 */
#define LOG_TAG "K3_V4L2"
#include "cam_log.h"
#include "cam_dbg.h"
#include "hwa_cam_tune.h"

#include <trace/trace_kernel.h>

#include <linux/compat.h>
#include <linux/module.h>
#include <linux/videodev2.h>
#include <linux/v4l2-subdev.h>
#include <media/v4l2-dev.h>
#include <media/v4l2-ioctl.h>



#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#endif

#include "hwa_cam_tune.h"

#include "soc_ao_sctrl_interface.h"
#include "soc_baseaddr_interface.h"

#include "video_config.h"
#include "video_reg_ops.h"

#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif

#define CAM_DEF_WIDTH   640
#define CAM_DEF_HEIGHT  480

#define BUF_LEN	 80
/*#define K3_V4L2_CAPTURE_TEST*/
/* #define DEBUG_WRITE_FILE 0 */

/* Camera control struct data */
static v4l2_ctl_struct v4l2_ctl;
camera_frame_buf *isp_rsv_frame[STATE_MAX];


static int video_nr = -1;
#ifdef READ_BACK_RAW
static u8 buf_used = 0;

#endif
#ifdef CONFIG_DEBUG_FS
static struct dentry *debugfs_camera_dir;
static struct dentry *debugfs_isp_reg;
static struct dentry *debugfs_sensor_reg;//sensor reg read/write interface
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
				print_error("%s, camera running in _state:%d", __func__, (state)); \
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


#if defined (CONFIG_HUAWEI_DSM)
static struct dsm_dev dsm_ovisp22 = {
    .name = "dsm_ovisp22",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
    .fops = NULL,
    .buff_size = 1024,
};

struct dsm_client *client_ovisp22 = NULL;
#endif

/* function predeclaration */
static int k3_v4l2_set_camera(v4l2_ctl_struct *cam, int new_sensor);
static int k3_v4l2_start_process(v4l2_ctl_struct *cam, u8 mode);
static int k3_v4l2_stop_process(v4l2_ctl_struct *cam, ipp_mode mode);

static camera_state get_camera_state(enum v4l2_buf_type type)
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
	    * (bits_per_pixel(fmt->fmt.pix.pixelformat)) / 8;
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
static inline void k3_register_buffer(camera_frame_buf *a,
				      struct v4l2_buffer *b, struct ion_client *ion_client, int share_fd)
{
	struct iommu_map_format iommu_format;
        memset(&iommu_format, 0, sizeof(iommu_format));

	a->index = b->index;
	a->size = b->length;
	a->flags = 0;
	a->share_fd = share_fd;

	/* get new handle to protect */
	a->ion_handle = ion_import_dma_buf(ion_client, a->share_fd);
	if (IS_ERR(a->ion_handle) || a->ion_handle == NULL) {
		print_error("%s, ion_import_dma_buf fail.ion_handle=%d.ion_client=%d,a->share_fd=%d.\n",
					__func__, a->ion_handle, ion_client, a->share_fd);
		return;
	}
	print_info("%s, frame ion_handle=%p", __func__, a->ion_handle);
	
	iommu_format.is_tile = 0;
	if (0 != ion_map_iommu(ion_client,a->ion_handle,&iommu_format)){
		print_error("%s: viraddr null, ion_map_kernel fail.", __func__);
	}
	a->phyaddr = iommu_format.iova_start;
	
	a->viraddr = ion_map_kernel(ion_client, a->ion_handle);
	if(NULL == a->viraddr) {
		print_error("%s: viraddr null, ion_map_kernel fail.", __func__);
		ion_free(ion_client, a->ion_handle);
		a->ion_handle = NULL;
		return;
	}
	print_debug("%s: frame phyaddr=0x%x, viraddr=%p", __func__, a->phyaddr, a->viraddr);
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
	v4l2_ctl_struct *cam = NULL;
	pic_fmt_s       pic_fmt;

	print_debug("enter %s", __func__);
	print_info("%s:capture_fmt->fmt.pix.width=%d,capture_fmt->fmt.pix.height=%d",__func__,fmt->fmt.pix.width,fmt->fmt.pix.height);

	SAFE_GET_DRVDATA(cam, fh);

	CHECK_STATE(STATE_CAPTURE);
	CHECK_STATE(STATE_IPP);


    /* if ZSL state is off */
	if (CAMERA_ZSL_ON != k3_isp_get_zsl_state()){
    	ret = k3_isp_try_fmt(fmt, STATE_CAPTURE, VIEW_FULL);
    	if (ret != 0)
    		return ret;
    }

	SAFE_DOWN(&cam->busy_lock);
	cam->fmt[STATE_CAPTURE] = *fmt;
	cam->fmt[STATE_IPP] = *fmt;
	SAFE_UP(&cam->busy_lock);

    print_info("%s:k3_isp_zsl_try_fmt.",__func__);
	if (CAMERA_ZSL_ON == k3_isp_get_zsl_state()) {
	    pic_fmt.preview_fmt = &(cam->fmt[STATE_PREVIEW]);
	    pic_fmt.capture_fmt = &(cam->fmt[STATE_CAPTURE]);
	    pic_fmt.ipp_fmt     = &(cam->fmt[STATE_IPP]);
	    pic_fmt.preview_view_type = cam->fmt[STATE_PREVIEW].fmt.pix.priv;
	    pic_fmt.capture_view_type = VIEW_FULL;

	    ret = k3_isp_zsl_try_fmt(&pic_fmt,cam->running[STATE_PREVIEW]);
	    if (ret != 0) {
	        print_error("%s:k3_isp_zsl_try_fmt fail.ret=%d",__func__,ret);
	        return ret;
	    }

        k3_isp_set_zsl_cap_cmd(CAMERA_ZSL_CAP_CMD_START);
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
	v4l2_ctl_struct *cam = NULL;

	print_debug("enter %s", __func__);
    print_info("%s:preview_fmt->fmt.pix.width=%d,preview_fmt->fmt.pix.height=%d",__func__,fmt->fmt.pix.width,fmt->fmt.pix.height);

	SAFE_GET_DRVDATA(cam, fh);

	CHECK_STATE(STATE_PREVIEW);

    /* if ZSL mode is off */
    if (CAMERA_ZSL_ON != k3_isp_get_zsl_state()){
        ret = k3_isp_try_fmt(fmt, STATE_PREVIEW, fmt->fmt.pix.priv);
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
	v4l2_ctl_struct *cam = NULL;

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
	v4l2_ctl_struct *cam = NULL;

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
	v4l2_ctl_struct *cam = NULL;

	SAFE_GET_DRVDATA(cam, fh);

	*fmt = cam->fmt[STATE_IPP];

	print_debug("%s pixelformat=%d, widht=%d, height=%d, bytesperline=%d",
		    __func__, fmt->fmt.pix.pixelformat, fmt->fmt.pix.width,
		    fmt->fmt.pix.height, fmt->fmt.pix.bytesperline);
	return 0;
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
	v4l2_ctl_struct *cam = NULL;
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
		ret = hwa_v4l2_ioctl_g_ctrls(file, fh, a);
		SAFE_UP(&cam->busy_lock);
		return ret;
	}
	switch (a->id) {

		/* auto white balance */
	case V4L2_CID_AUTO_WHITE_BALANCE:
		{
			print_info("get auto wb");
			a->value = k3_isp_get_awb_mode();
			break;
		}

		/* manual white balance */
	case V4L2_CID_DO_WHITE_BALANCE:
		{
			print_info("get manual wb");
			a->value = k3_isp_get_awb_mode();
			break;
		}

		/*anti-shaking: for video */
	case V4L2_CID_ANTI_SHAKING:
		{
			print_info("get anti-shaking");
			a->value = k3_isp_get_anti_shaking();
			break;
		}

	case V4L2_CID_ISO:
		{
			print_info("get iso");
			a->value = k3_isp_get_iso();
			break;
		}

	case V4L2_CID_EXPOSURE:
		{
			print_info("get ev");
			a->value = k3_isp_get_ev();
			break;
		}

	case V4L2_CID_METERING:
		{
			print_info("get metering");
			a->value = k3_isp_get_metering_mode();
			break;
		}

	case V4L2_CID_POWER_LINE_FREQUENCY:
		{
			print_info("get anti-flicker");
			a->value = k3_isp_get_anti_banding();
			break;
		}

		/* sharpness */
	case V4L2_CID_SHARPNESS:
		{
			print_info("get sharpness");
			a->value = k3_isp_get_sharpness();
			break;
		}

		/* saturation */
	case V4L2_CID_SATURATION:
		{
			print_info("get saturation");
			a->value = k3_isp_get_saturation();
			break;
		}

		/* contrast */
	case V4L2_CID_CONTRAST:
		{
			print_info("get contrast");
			a->value = k3_isp_get_contrast();
			break;
		}

		/* scene */
	case V4L2_CID_SCENE:
		{
			print_info("get scene");
			a->value = k3_isp_get_scene();
			break;
		}

		/* brightness */
	case V4L2_CID_BRIGHTNESS:
		{
			print_info("get brightness");
			a->value = k3_isp_get_brightness();
			break;
		}
	case V4L2_CID_EFFECT:
		{
			print_info("get special effect");
			a->value = k3_isp_get_effect();
			break;
		}

	case V4L2_CID_CAPTURE_MODE:
		{
			a->value = k3_isp_get_process_mode();
			break;
		}
	case V4L2_CID_ZOOM_RELATIVE:
		{
			a->value = k3_isp_get_zoom();
			break;
		}

	case V4L2_CID_FOCUS_MODE:
		{
			a->value = k3_isp_get_focus_mode();
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
			a->value = k3_isp_get_flash_mode();
			break;
		}
	case V4L2_CID_ACTUAL_ISO:
		{
			a->value = k3_isp_get_actual_iso();
			break;
		}

	case V4L2_CID_ACTUAL_EXPOSURE:
		{
			a->value = k3_isp_get_exposure_time();
			break;
		}

	case V4L2_CID_HFLIP:
		{
			a->value = k3_isp_get_hflip();
			break;
		}
	case V4L2_CID_VFLIP:
		{
			a->value = k3_isp_get_vflip();
			break;
		}
	case V4L2_CID_GET_METERING_FLASH_RESULT:
		{
			a->value = k3_isp_get_flash_result();
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
			a->value = k3_isp_get_focus_distance();
			break;
		}
	case V4L2_CID_GET_CURRENT_VTS:
		{
			a->value = k3_isp_get_current_vts();
			break;
		}
	case V4L2_CID_GET_CURRENT_FPS:
		{
			a->value = k3_isp_get_current_fps();
			break;
		}
	case V4L2_CID_GET_BAND_THRESHOLD:
		{
			a->value = k3_isp_get_band_threshold();
			break;
		}
	case V4L2_CID_GET_AWB_GAIN:
		{
			a->value = k3_isp_get_awb_gain(1);
			break;
		}

	case V4L2_CID_GET_AWB_GAIN_ORI:
		{
			a->value = k3_isp_get_awb_gain(0);
			break;
		}

	case V4L2_CID_GET_FOCUS_CODE:
		{
			a->value = k3_isp_get_focus_code();
			break;
		}

	case V4L2_CID_GET_EXPO_LINE:
		{
			a->value = k3_isp_get_expo_line();
			break;
		}

	case V4L2_CID_GET_SENSOR_VTS:
		{
			a->value = k3_isp_get_sensor_vts();
			break;
		}

	case V4L2_CID_GET_CURRENT_CCM_RGAIN:
		{
			a->value = k3_isp_get_current_ccm_rgain();
			break;
		}

	case V4L2_CID_GET_CURRENT_CCM_BGAIN:
		{
			a->value = k3_isp_get_current_ccm_bgain();
			break;
		}

	case V4L2_CID_GET_APERTURE:
		{
			a->value = k3_isp_get_sensor_aperture();
			break;
		}

	case V4L2_CID_GET_EQUIV_FOCUS:
		{
			a->value = k3_isp_get_equivalent_focus();
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
	v4l2_ctl_struct     *cam = NULL;
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
		ret = hwa_v4l2_ioctl_s_ctrls(file, fh, v4l2_param);
		SAFE_UP(&cam->busy_lock);
		return ret;
	}

	switch (v4l2_param->id) {

		/* auto white balance */
	case V4L2_CID_AUTO_WHITE_BALANCE:
		{
			print_info("set auto wb: %d", v4l2_param->value);
			k3_isp_set_awb_mode(v4l2_param->value);
			break;
		}

		/* manual white balance */
	case V4L2_CID_DO_WHITE_BALANCE:
		{
			print_info("set manual wb: %d", v4l2_param->value);
			k3_isp_set_awb_mode(v4l2_param->value);
			break;
		}

		/*anti-shaking: for video */
	case V4L2_CID_ANTI_SHAKING:
		{
			print_info("set anti-shaking, %d", v4l2_param->value);
			k3_isp_set_anti_shaking(v4l2_param->value);
			break;
		}

	case V4L2_CID_ISO:
		{
			print_info("set iso %d", v4l2_param->value);
			k3_isp_set_iso(v4l2_param->value);
			break;
		}

	case V4L2_CID_EXPOSURE:
		{
			print_info("set ev %d", v4l2_param->value);
			if ((v4l2_param->value <= CAMERA_EXPOSURE_MAX)
			    && (v4l2_param->value >= -(CAMERA_EXPOSURE_MAX)))
				k3_isp_set_ev(v4l2_param->value);
			break;
		}

	case V4L2_CID_METERING:
		{
			print_info("set metering, %d", v4l2_param->value);
			k3_isp_set_metering_mode(v4l2_param->value);
			break;
		}

	case V4L2_CID_POWER_LINE_FREQUENCY:
		{
			print_info("set anti-banding, %d", v4l2_param->value);
			k3_isp_set_anti_banding(v4l2_param->value);
			break;
		}

		/* sharpness */
	case V4L2_CID_SHARPNESS:
		{
			print_info("set sharpness, %d", v4l2_param->value);
			k3_isp_set_sharpness(v4l2_param->value);
			break;
		}

		/* saturation */
	case V4L2_CID_SATURATION:
		{
			print_info("set saturation, %d", v4l2_param->value);
			k3_isp_set_saturation(v4l2_param->value);
			break;
		}

		/* contrast */
	case V4L2_CID_CONTRAST:
		{
			print_info("set contrast, %d", v4l2_param->value);
			k3_isp_set_contrast(v4l2_param->value);
			break;
		}

		/* scene */
	case V4L2_CID_SCENE:
		{
			print_info("set scene, %d", v4l2_param->value);
			k3_isp_set_scene(v4l2_param->value);
			break;
		}

		/* brightness */
	case V4L2_CID_BRIGHTNESS:
		{
			print_info("set brightness, %d", v4l2_param->value);
			k3_isp_set_brightness(v4l2_param->value);
			break;
		}
		/* effect */
	case V4L2_CID_EFFECT:
		{
			print_info("set effect, %d", v4l2_param->value);
			k3_isp_set_effect(v4l2_param->value);
			break;
		}

		/* zoom */
	case V4L2_CID_ZOOM_RELATIVE:
		{
			print_info("set zoom, %d", v4l2_param->value);
			ret = k3_isp_set_zoom(cam->running[STATE_PREVIEW], v4l2_param->value);
			break;
		}

	/* zoom center*/
	case V4L2_CID_SET_ZOOM_CENTER:
		{
			print_info("set zoom center, %d", v4l2_param->value);
			ret = k3_isp_set_zoom_center(cam->running[STATE_PREVIEW], v4l2_param->value);
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
				k3_isp_auto_focus(v4l2_param->value);
			else
				k3_isp_auto_focus(FOCUS_STOP);
			break;
		}
		/* Set focus mode */
	case V4L2_CID_FOCUS_MODE:
		{
			ret = k3_isp_set_focus_mode(v4l2_param->value);
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
				ret = k3_isp_set_flash_mode(v4l2_param->value);
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
			k3_isp_set_hflip(v4l2_param->value);
			break;
		}
	case V4L2_CID_VFLIP:
		{
			print_info("set vflip, %d", v4l2_param->value);
			k3_isp_set_vflip(v4l2_param->value);
			break;
		}
	case V4L2_CID_SET_METERING_FLASH:
		{
			print_info("set metering flash, %d", v4l2_param->value);
			k3_isp_check_flash_level(v4l2_param->value);
			break;
		}

	case V4L2_CID_AUTO_EXPOSURE_LOCK:
		{
			print_info("set AE lock, %d", v4l2_param->value);
			k3_isp_set_ae_lock(v4l2_param->value);
			break;
		}
	case V4L2_CID_AUTO_WHITE_BALANCE_LOCK:
		{
			print_info("set AWB lock, %d", v4l2_param->value);
			k3_isp_set_awb_lock(v4l2_param->value);
			break;
		}
	case V4L2_CID_SET_FPS_LOCK:
		{
			print_info("set fps lock, %d", v4l2_param->value);
			k3_isp_set_fps_lock(v4l2_param->value);
			break;
		}
	case V4L2_CID_SNAPSHOOT_MODE:
		{
			print_info("set snap shoot mode, %d", v4l2_param->value);
			k3_isp_set_shoot_mode(v4l2_param->value);
			break;
		}
	case V4L2_CID_PM_MODE:
		{
			print_info("set PM_mode, %d", v4l2_param->value);
			k3_isp_set_pm_mode(v4l2_param->value);
			break;
		}

    case V4L2_CID_ZSL:
        {
            print_info("set ZSL_state, %d", v4l2_param->value);
			k3_isp_set_zsl_state(v4l2_param->value);
            break;
        }
    case V4L2_CID_CAP_RAW:
        {
            print_info("set ZSL cap raw, %d", v4l2_param->value);
            if(cam->running[(STATE_CAPTURE)]){
			    ret = k3_isp_set_zsl_cap_raw(v4l2_param->value,&cam->fmt[STATE_CAPTURE].fmt.pix, &cam->buffer_arr[STATE_IPP]);
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
			k3_isp_set_video_stabilization(v4l2_param->value);
			break;
		}
	case V4L2_CID_SET_YUV_CROP_POS:
		{
			print_debug("set crop pos, %d", v4l2_param->value);
			k3_isp_set_yuv_crop_pos(v4l2_param->value);
			break;
		}
    case V4L2_CID_CAPTURE_MODE:
        {
            print_info("set V4L2_CID_CAPTURE_MODE, %d", v4l2_param->value);
            k3_isp_set_process_mode(v4l2_param->value);
            break;
        }
	case  V4L2_CID_SET_3A_MODE:
		{
			int hw_3a_switch =  v4l2_param->value;
			k3_isp_set_hw_3a_mode(hw_3a_switch);
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
	v4l2_ctl_struct *cam			= NULL;
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
		controls[i].value = 0;   /* [false alarm]:controls[i]²»»áÎªNULL  */

		if(cam->sensor->isp_location == CAMERA_USE_K3ISP ||
			V4L2_CID_ZOOM_RELATIVE == controls[i].id)
			k3_isp_get_k3_capability(controls[i].id, &controls[i].value);

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
	v4l2_ctl_struct *cam			= NULL;
	u32 cid_idx;
	int ret					= 0;
	struct v4l2_ext_controls *ext_ctls	= arg;
	struct v4l2_ext_control *controls	= NULL;

	void * data_buf                     = NULL;

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
			ret = hwa_v4l2_ioctl_g_ext_ctrls(&controls, controls[cid_idx].id,cid_idx);
			continue;
		}

		switch (controls[cid_idx].id) {
		/* get camera count */
		case V4L2_CID_SENSOR_COUNT:
		{
			controls[cid_idx].value =  get_camera_count();
			break;
		}

		/* get camera infomation, include facing and orientation */
		case V4L2_CID_SENSOR_INFO:
		{
			u32 camera_id;
			camera_sensor *psensor = NULL;
			void __user *info = controls[cid_idx].string;
			camera_id = controls[cid_idx].size; /* reserved[0] in hal */

			psensor = get_camera_sensor_from_array(camera_id);

			if (psensor == NULL) {
				print_error("fail to find sensor by id.");
				goto out;
			}
			if (NULL == info){
				print_error("info is NULL");
			} else {
				if(copy_to_user(info, &psensor->info, sizeof(camera_info_t))){
                    print_error("V4L2_CID_SENSOR_INFO mem error! %s", __FUNCTION__);
                }
			}
			break;
		}

		/* get focus result */
		case V4L2_CID_FOCUS_RESULT:
		{
			void __user *result = controls[cid_idx].string;
            if (NULL == result)
            {
            	ret = -EFAULT;
            	print_error("NULL parameter");
            	goto out;
            }
            data_buf = kmalloc(sizeof(focus_result_s), GFP_KERNEL);
            if (!data_buf) {
            	ret = -ENOMEM;
            	print_error("fail to allocate buffer");
            	goto out;
            }
			k3_isp_get_focus_result((focus_result_s *)data_buf);
            if(copy_to_user(result, data_buf, sizeof(focus_result_s))){
                print_error("V4L2_CID_FOCUS_RESULT mem error! %s", __FUNCTION__);
            }
			break;
		}

		/* get focus rect information */
		case V4L2_CID_GET_FOCUS_RECT:
		{
			void __user *rect = controls[cid_idx].string;

            if (NULL == rect)
            {
            	ret = -EFAULT;
            	print_error("NULL parameter");
            	goto out;
            }
            data_buf = kmalloc(sizeof(camera_rect_s), GFP_KERNEL);
            if (!data_buf) {
            	ret = -ENOMEM;
            	print_error("fail to allocate buffer");
            	goto out;
            }
			k3_isp_get_focus_rect((camera_rect_s *)data_buf);
            if(copy_to_user(rect, data_buf, sizeof(camera_rect_s))){
                print_error("V4L2_CID_GET_FOCUS_RECT mem error! %s", __FUNCTION__);
            }
			break;
		}
		case V4L2_CID_GET_YUV_CROP_RECT:
		{
			void __user *rect = controls[cid_idx].string;

            if (NULL == rect)
            {
            	ret = -EFAULT;
            	print_error("NULL parameter");
            	goto out;
            }
            data_buf = kmalloc(sizeof(crop_rect_s), GFP_KERNEL);
            if (!data_buf) {
            	ret = -ENOMEM;
            	print_error("fail to allocate buffer");
            	goto out;
            }
			k3_isp_get_yuv_crop_rect((crop_rect_s *)data_buf);
            if(copy_to_user(rect, data_buf, sizeof(crop_rect_s))){
                print_error("V4L2_CID_GET_YUV_CROP_RECT mem error! %s", __FUNCTION__);
            }
			break;
		}

		default:
			break;

		}

    	if(NULL != data_buf){
    		kfree(data_buf);
    		data_buf = NULL;
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

    relocate_camera_sensor_by_name(sensor_index,sensor_name);

    return;

}

static int k3_v4l2_ioctl_s_ext_ctrls(struct file *file, void *fh,
				     struct v4l2_ext_controls *arg)
{
	v4l2_ctl_struct *cam 	= NULL;
	u32 cid_idx		= 0;
	int ret 		= 0;
	camera_state state;
	bool         reg_buf = false;

	int func_ret = 0;


	/*
	 * For focus rect setting ,bracket setting and others...
	 */

	void *data_buf					  = NULL;
	void __user *area                 = NULL;
	void __user *bracket_ev           = NULL;
	void __user *metering_area        = NULL;
	void __user *xyz                  = NULL;

	int share_fd = 0;

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
			ret =hwa_v4l2_ioctl_s_ext_ctrls(&controls, controls[cid_idx].id,cid_idx);
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

		case V4L2_CID_BUFFER_SHARE_FD:
			{
				share_fd = (int)controls[cid_idx].value;
				print_info("%s shared_fd = %d.", __func__, share_fd);
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
					init_queue(&cam->data_queue, state);
					camera_free_ion_handle(cam->ion_client,&cam->buffer_arr[state]);
					camera_init_buffer(&cam->buffer_arr[state]);
					isp_rsv_frame[state] = NULL;
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
        {
			area = controls[cid_idx].string;

            data_buf = kmalloc(sizeof(focus_area_s), GFP_KERNEL);
            if (!data_buf) {
            	ret = -ENOMEM;
            	print_error("fail to allocate buffer");
            	goto end;
            }
            if(copy_from_user(data_buf, area, sizeof(focus_area_s))){
                print_error("set V4L2_CID_FOCUS_AREA_INFO mem error! %s", __FUNCTION__);
            }

			func_ret = k3_isp_set_focus_area((focus_area_s *)data_buf);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			goto end;
			break;
		}
			/* For bracket information setting */
		case V4L2_CID_BRACKET_INFO:
        {
			bracket_ev = controls[cid_idx].string;

            data_buf = kmalloc(sizeof(int) * MAX_BRACKET_COUNT, GFP_KERNEL);
            if (!data_buf) {
            	ret = -ENOMEM;
            	print_error("fail to allocate buffer");
            	goto end;
            }
            if(copy_from_user(data_buf, bracket_ev, sizeof(int) * MAX_BRACKET_COUNT)){
                print_error("set V4L2_CID_BRACKET_INFO mem error! %s", __FUNCTION__);
            }
			func_ret = k3_isp_set_bracket_info((int *)data_buf);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			goto end;
			break;
		}
		case V4L2_CID_METERING_AREA_INFO:
        {
			metering_area = controls[cid_idx].string;

            data_buf = kmalloc(sizeof(metering_area_s), GFP_KERNEL);
            if (!data_buf) {
            	ret = -ENOMEM;
            	print_error("fail to allocate buffer");
            	goto end;
            }
            if(copy_from_user(data_buf, metering_area, sizeof(metering_area_s))){
                print_error("set V4L2_CID_METERING_AREA_INFO mem error! %s", __FUNCTION__);
            }
			func_ret = k3_isp_set_metering_area((metering_area_s *)data_buf);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			goto end;
			break;
		}
		case V4L2_CID_SENSOR_INFO:
		{
			char sensor_name[SENSOR_NAME_MAX_LENTH] = {0};
			u8 cameraid;

			cameraid = controls[cid_idx].size;
//			sensor_name = (char *)(controls[cid_idx].string);
            if(copy_from_user(sensor_name, (void __user *)controls[cid_idx].string, (SENSOR_NAME_MAX_LENTH - 1))){
                print_error("set V4L2_CID_SENSOR_INFO mem error! %s", __FUNCTION__);
            }

			if ('\0' != sensor_name[0])
				k3_v4l2_set_sensor(cameraid, sensor_name);
			break;

		}

		case V4L2_CID_SET_GSENSOR_STAT:
        {
			xyz = controls[cid_idx].string;

			data_buf = kmalloc(sizeof(axis_triple), GFP_KERNEL);
			if (!data_buf) {
				ret = -ENOMEM;
				print_error("fail to allocate buffer");
				goto end;
			}

			if(copy_from_user(data_buf, xyz, sizeof(axis_triple))){
                print_error("set V4L2_CID_SET_GSENSOR_STAT mem error! %s", __FUNCTION__);
            }
			func_ret = k3_isp_set_gsensor_stat((axis_triple *)data_buf);
			if (func_ret != 0) {
				ret = -EINVAL;
			}
			goto end;
			break;
		}
		case  V4L2_CID_SET_HW_3A_PARAM:
		{
			hw_3a_param *ae_result =  (hw_3a_param*)(controls[cid_idx].string);
			func_ret = ispv1_set_hw_3a_param(ae_result);
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
    	k3_register_buffer(&(cam->buffer_arr[state].buffers[vbuffer.index]), &vbuffer, cam->ion_client, share_fd);
    	INIT_LIST_HEAD(&(cam->buffer_arr[state].buffers[vbuffer.index].queue));

        /* save buffers[0] as rsv buf in preview mode */
        if ((state ==STATE_PREVIEW) && (vbuffer.index == CAMERA_BUF_RSV_BUF_IDX))
        {
            isp_rsv_frame[state] = &(cam->buffer_arr[STATE_PREVIEW].buffers[CAMERA_BUF_RSV_BUF_IDX]);
        }

#ifdef DUMP_FILE
	if (state == STATE_CAPTURE)
		cam->buffer_arr[state].buffers[vbuffer.index].viraddr =
		    ioremap_nocache(vbuffer.m.offset, vbuffer.length);
#endif
	/* Only for register buffer end */
	}

end:
	if(NULL != data_buf){
		kfree(data_buf);
		data_buf = NULL;
    }

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
	v4l2_ctl_struct *cam = NULL;
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

	/* first buf reserved for drop,not to queue to ready-queue. */
	if ((CAMERA_BUF_RSV_BUF_IDX == b->index) && (STATE_PREVIEW == state))
	{
	    print_info("reserved buf:state=%d,index=%d,phyaddr=0x%p",STATE_PREVIEW, CAMERA_BUF_RSV_BUF_IDX,cam->buffer_arr[state].buffers[b->index].phyaddr);
	    return 0;
	}

	/* queue buffer to preview ready queue */
	if (V4L2_MEMORY_MMAP != b->memory) {
		cam->buffer_arr[state].buffers[b->index].phyaddr = b->m.offset;
		cam->buffer_arr[state].buffers[b->index].statphyaddr = b->reserved;
		cam->buffer_arr[state].buffers[b->index].size = b->length;
	}

	spin_lock_irqsave(&cam->data_queue.queue_lock, lock_flags);
	print_debug("%s, isp_hw_data.cur_state = %d",  __func__,state);
	add_to_queue(&cam->buffer_arr[state].buffers[b->index],
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
	v4l2_ctl_struct *cam = NULL;
	camera_frame_buf *frame = NULL;
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

    /*for common image, z62576, 20140429, begin*/
	wait_time = (long)(cam->dqbuf_irq_timeout) * HZ;
    /*for common image, z62576, 20140429, end*/

    /***************************************************************************
      capture in zsl offline mode ,need 4 multiple time at least to complete
      offline process.so we set 5.
    ***************************************************************************/
	if( (CAMERA_ZSL_ON == k3_isp_get_zsl_state()) && (CAMERA_ZSL_OFFLINE == k3_isp_get_zsl_proc())){
	    if (V4L2_BUF_TYPE_VIDEO_CAPTURE == b->type){
            /*for common image, z62576, 20140429, begin*/
            wait_time = 5 * ((long)(cam->dqbuf_irq_timeout) * HZ);
            /*for common image, z62576, 20140429, end*/
        }
	}

    print_debug("wait_event_interruptible_timeout: %d",wait_time);
    /*lint -e666*/
    if (!wait_event_interruptible_timeout(cam->data_queue.queue[state],
        ((!list_empty(&cam->data_queue.done_q[state])) | (!cam->running[state])),
        wait_time)) /*lint +e666*/{
        if (!list_empty(&cam->data_queue.done_q[state])) {
            if((cam->sensor !=NULL) &&(cam->sensor->sensor_dump_reg != NULL)){
		        cam->sensor->sensor_dump_reg();
            }
            dump_isp_size_reg();
            dump_isp_cmd_reg();
            dump_isp_mac_size_reg();

            print_info("state:%d dequeue buffer time out <done_q(%d)>, but queue not empty.",
                    state, list_empty(&cam->data_queue.done_q[state]));
        } else {
	     if((cam->sensor !=NULL) &&(cam->sensor->sensor_dump_reg != NULL)){
		        cam->sensor->sensor_dump_reg();
            }
            dump_isp_size_reg();
            dump_isp_cmd_reg();
            dump_isp_mac_size_reg();
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

	#ifndef CONFIG_ARM64
	trace_dot(CAM, "14", 0);
	#endif

	if (!cam->running[state]) {
		ret = -ECANCELED;
		goto out;
	}

    spin_lock_irqsave(&cam->data_queue.queue_lock, lock_flags);
    if (!list_empty(&cam->data_queue.done_q[state])) {
        frame = list_entry(cam->data_queue.done_q[state].next, camera_frame_buf, queue);
        del_from_queue(frame, CAMERA_FLAG_DONEQ);
    } else {
        ret = -ENOMEM;
        print_error("%s, line %d, done queue[%d] is empty.", __func__, __LINE__, state);
        spin_unlock_irqrestore(&cam->data_queue.queue_lock, lock_flags);
        goto out;
    }
    spin_unlock_irqrestore(&cam->data_queue.queue_lock, lock_flags);

	b->index = frame->index;
	memcpy(&(b->timestamp), &(frame->timestamp), sizeof(struct timeval));
#ifdef DUMP_FILE
	dump_file("/data/yuv.yuv", frame->viraddr, 2592 * 1952 * 2);
#endif

	print_debug("exit %s, state=%d, index=%d, phyaddr is 0x%p", __func__, state,
		    b->index, frame->phyaddr);

#ifdef READ_BACK_RAW
	if (STATE_PREVIEW == state) {
		print_info("Line:%d, before update read ready++++++++++++", __LINE__);
		msleep(100);
		if (0 == buf_used) {
			buf_used = 1;
			k3_isp_update_read_ready(buf_used);
		} else {
			buf_used = 0;
			k3_isp_update_read_ready(buf_used);
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
	v4l2_ctl_struct *cam = NULL;

	SAFE_GET_DRVDATA(cam, fh);

	/* if ZSL switch on */
	if (CAMERA_ZSL_ON == k3_isp_get_zsl_state()){
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

	ret = k3_isp_stream_on(&cam->fmt[state].fmt.pix, buf_type, state,&cam->buffer_arr[STATE_IPP]);

    if (ret == 0)
    {
    	cam->pid[state] = current->pid;
    	cam->running[state] = 1;

        /* enable cap raw & proc img */
        if (CAMERA_ZSL_ON == k3_isp_get_zsl_state() && (STATE_CAPTURE == state)){
            k3_isp_set_zsl_proc_valid(true);
            k3_isp_set_zsl_cap_valid(true);
        }

    #ifdef READ_BACK_RAW
    	if(STATE_PREVIEW == state)
    		buf_used = 0;
    #endif
    } else {
        print_error("%s:k3_isp_stream_on fail.ret=%d.",__func__,ret);
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
	v4l2_ctl_struct *cam = NULL;
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
	if (CAMERA_ZSL_ON == k3_isp_get_zsl_state() && (STATE_CAPTURE == state)){
	    /* hope zsl thread quit quickly */
    	k3_isp_set_zsl_proc_valid(false);
    	k3_isp_set_zsl_cap_valid(false);
    	lock = &cam->busy_lock_capture;
	}

	SAFE_DOWN(lock);

	ret = k3_isp_stream_off(state);
	if (ret != 0 ){
	    print_error("%s:k3_isp_stream_off fail.ret=%d.",__func__,ret);
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
static int k3_v4l2_start_process(v4l2_ctl_struct *cam, u8 mode)
{
	int ret = -EINVAL;
	print_info("enter %s", __func__);

    if (CAMERA_ZSL_ON == k3_isp_get_zsl_state())
    {
        print_info("zsl:do raw to yuv.");
    }
    else
    {
    	CHECK_STATE(STATE_PREVIEW);
    	CHECK_STATE(STATE_IPP);
	}

	ret = k3_isp_start_process(&cam->fmt[STATE_CAPTURE].fmt.pix, mode,&(cam->buffer_arr[STATE_IPP]));
	if (ret != 0) {
		print_error("error : k3_isp_start_process() faild!");
		return ret;
	}

    if (CAMERA_ZSL_ON != k3_isp_get_zsl_state())
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
static int k3_v4l2_stop_process(v4l2_ctl_struct *cam, ipp_mode mode)
{
	int ret = -EINVAL;
	print_info("enter %s", __func__);

    if (CAMERA_ZSL_ON != k3_isp_get_zsl_state()){
        CHECK_STATE(STATE_PREVIEW);
    }

    ret = k3_isp_stop_process(mode);
    if (ret != 0) {
        print_error("error : k3_isp_start_process() faild!");
        return ret;
    }

    if (CAMERA_ZSL_ON != k3_isp_get_zsl_state()){
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
	v4l2_ctl_struct *cam = NULL;
	struct v4l2_frmivalenum fi;
	camera_sensor *sensor;
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
	if (0 != k3_isp_try_frameintervals(&fi))
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

		k3_isp_set_fps(CAMERA_FPS_MAX, max_fps);
		k3_isp_set_fps(CAMERA_FPS_MIN, min_fps);
		k3_isp_set_fps(CAMERA_FPS_MID, mid_fps);
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
	v4l2_ctl_struct *cam = NULL;

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
	v4l2_ctl_struct *cam = NULL;
	int ret = 0;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);
	ret = k3_isp_enum_framesizes(fsize);
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
	v4l2_ctl_struct *cam = NULL;
	int ret = 0;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);
	/* FIXME: HAL do not need store capability of auto fps */
	if (fival->index == 0) {
		fival->index++;
	}
	ret = k3_isp_enum_frameintervals(fival);
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
	v4l2_ctl_struct *cam = NULL;
	int ret = 0;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);
	ret = k3_isp_enum_fmt(fmt, STATE_CAPTURE);
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
	v4l2_ctl_struct *cam = NULL;
	int ret = 0;

	print_debug("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, fh);

	SAFE_DOWN(&cam->busy_lock);
	ret = k3_isp_enum_fmt(fmt, STATE_PREVIEW);
	SAFE_UP(&cam->busy_lock);

	return ret;
}
static int k3_v4l2_check_camera(camera_sensor **sensor, sensor_index_t type)
{
	int ret = -ENODEV;
	int index = 0;
	camera_sensor *temp_sensor = NULL;

	if (type >= CAMERA_SENSOR_MAX) {
		print_error("Unsuport sensor type : %d", type);
		goto out;
	}

	for(; index < CAMERA_SENSOR_NUM_MAX; index ++) {
		temp_sensor = get_camera_sensor_from_array(type);
		if (NULL == temp_sensor) {
			print_error("fail to get camera [%d]", type);
			ret = -ENODEV;
			break;
		}
		ret = k3_isp_set_camera(temp_sensor, NULL);
		if (ret == -ENODEV) {
			unregister_camera_sensor(temp_sensor->sensor_index, temp_sensor);
		} else {
			clean_camera_sensor(type);
			register_camera_sensor(type, temp_sensor);
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
int k3_v4l2_set_camera(v4l2_ctl_struct *cam, int new_sensor)
{
	int ret = 0;
	camera_sensor *sensor = NULL;
	camera_sensor **pri_sensor = NULL;
	camera_sensor **sec_sensor = NULL;

	print_debug("enter %s, new_sensor=%d", __func__, new_sensor);

	/* get camera sensor */
	sensor = get_camera_sensor_from_array(new_sensor);
	if (NULL == sensor) {
		print_error("fail to get camera [%d]", new_sensor);
		ret = -ENODEV;
		goto out;
	}

	/* set it to isp */
	if (0 != k3_isp_hw_init_regs(sensor)) {
		print_error("fail to init isp hw register");
		ret = -ENODEV;
		goto out;
	}

	pri_sensor = get_camera_sensor_array(CAMERA_SENSOR_PRIMARY);
	sec_sensor = get_camera_sensor_array(CAMERA_SENSOR_SECONDARY);

	camera_power_id_gpio(POWER_ON);

	if (CAMERA_SENSOR_PRIMARY == new_sensor) {
        k3_v4l2_check_camera(pri_sensor, CAMERA_SENSOR_PRIMARY);
		if (NULL == *pri_sensor) {
			print_error("Do not support sensor type:%d", new_sensor);
			#if defined (CONFIG_HUAWEI_DSM)
			if (!dsm_client_ocuppy(client_ovisp22)){
			    dsm_client_record(client_ovisp22,"[%s]Do not support canera sensor type %d\n",__func__, new_sensor);
			    dsm_client_notify(client_ovisp22, DSM_ISP22_SENSOR_PRIMARY_ERROR_NO);
			}
			#endif
			ret = -ENODEV;
			goto out;
		}
        cam->sensor = *pri_sensor;
	} else {
	    k3_v4l2_check_camera(sec_sensor, CAMERA_SENSOR_SECONDARY);
		if (NULL == *sec_sensor) {
			print_error("Do not support sensor type:%d", new_sensor);
			#if defined (CONFIG_HUAWEI_DSM)
			if (!dsm_client_ocuppy(client_ovisp22)){
			    dsm_client_record(client_ovisp22,"[%s]Do not support canera sensor type %d\n",__func__, new_sensor);
			    dsm_client_notify(client_ovisp22, DSM_ISP22_SENSOR_SECONDARY_ERROR_NO);
			}
			#endif
			ret = -ENODEV;
			goto out;
		}
        cam->sensor = *sec_sensor;
	}

	camera_power_id_gpio(POWER_OFF);

    set_camera_sensor(new_sensor,cam->sensor);

	cam->cur_sensor = new_sensor;
	print_info("set sensor to [%d, %s]", cam->cur_sensor, cam->sensor->info.name);

out:

	return ret;
}

#define K3_CAMERA_ENABLE_SYSFS
#ifdef	K3_CAMERA_ENABLE_SYSFS

static ssize_t k3_pri_sensor_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int ret = 0;
    camera_sensor **pri_sensor = NULL;

    print_debug("enter %s", __FUNCTION__);
    pri_sensor = get_camera_sensor(CAMERA_SENSOR_PRIMARY);

        if(NULL != *pri_sensor){
            snprintf(buf, BUF_LEN, "%s", (*pri_sensor)->info.name);
        }
	else{
            print_error("%s: NULL pri_sensor", __FUNCTION__);
            snprintf(buf, BUF_LEN, "Please run Camera first");
        }

        ret = strlen(buf) + 1 ;
	 return ret;
}
static DEVICE_ATTR(pri_sensor, S_IRUGO, k3_pri_sensor_show, NULL);

static ssize_t k3_sec_sensor_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int ret = 0;
    camera_sensor **sec_sensor = NULL;

    print_debug("enter %s", __FUNCTION__);
    sec_sensor = get_camera_sensor(CAMERA_SENSOR_SECONDARY);

        if(NULL != *sec_sensor){
            snprintf(buf, BUF_LEN, "%s", (*sec_sensor)->info.name);
        }
	else{
            print_error("%s: NULL sec_sensor", __FUNCTION__);
            snprintf(buf, BUF_LEN, "Please run Camera first");
        }

        ret = strlen(buf) + 1 ;
	 return ret;
}
static DEVICE_ATTR(sec_sensor, S_IRUGO, k3_sec_sensor_show, NULL);

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

	ret = sysfs_create_file(k3_camera_kobj, &dev_attr_pri_sensor.attr);
	if (ret) {
		print_error("failed to create sysfs files in pri_sensor");
		return ret;
	}

	ret = sysfs_create_file(k3_camera_kobj, &dev_attr_sec_sensor.attr);
	if (ret) {
		print_error("failed to create sysfs files in sec_sensor");
		return ret;
	}
	return 0;
}

static void k3_sensors_remove_sysfs(void)
{
	sysfs_remove_file(k3_camera_kobj, &dev_attr_pri_sensor.attr);
	sysfs_remove_file(k3_camera_kobj, &dev_attr_sec_sensor.attr);
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
	v4l2_ctl_struct *cam = NULL;
	struct ion_device *ion_dev;

    #ifndef CONFIG_ARM64
    trace_dot(CAM, "1", 0);
    #endif

	WARN_ON(dev == NULL);

	print_info("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, dev);
	if (!cam) {
		print_error("%s, cam is null", __func__);
		return -ENODEV;
	}

	SAFE_DOWN(&cam->busy_lock);

	if (0 == cam->open_count++) {
		camera_flashlight *flashlight = NULL;
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
		init_queue(&cam->data_queue, STATE_PREVIEW);
		init_queue(&cam->data_queue, STATE_CAPTURE);
		init_queue(&cam->data_queue, STATE_IPP);
		camera_init_buffer(&cam->buffer_arr[STATE_PREVIEW]);
		camera_init_buffer(&cam->buffer_arr[STATE_CAPTURE]);
		camera_init_buffer(&cam->buffer_arr[STATE_IPP]);

		memset(&isp_rsv_frame[0], 0x00, sizeof(isp_rsv_frame));

		k3_set_default_fmt(&cam->fmt[STATE_PREVIEW], STATE_PREVIEW);
		k3_set_default_fmt(&cam->fmt[STATE_CAPTURE], STATE_CAPTURE);
		k3_set_default_fmt(&cam->fmt[STATE_IPP], STATE_IPP);
		/* init isp controller */
		ret = k3_isp_init(v4l2_ctl.pdev, &v4l2_ctl.data_queue);
		if (ret != 0) {
			print_error("error : fail to init ISP");
			cam->open_count = 0;
			k3_isp_exit(cam);
			goto out;
		}
		flashlight = get_camera_flash();
		if (flashlight)
			flashlight->init();

        ion_dev = get_ion_device();
	    if (NULL == ion_dev) {
	        print_error("%s, fail to get ion device.\n", __func__);
	        ret = -EFAULT;
	        goto out;
	    }

	    cam->ion_client = ion_client_create(ion_dev, "isp");
	    if (IS_ERR(cam->ion_client) || cam->ion_client == NULL) {
	        print_error("%s, fail to create ion client.\n", __func__);
	        ret = -EFAULT;
	        goto out;
	    }

	    print_info("ion_dev=%p,ion_client=%p",ion_dev,cam->ion_client);
	} else {
		print_info("%s failed : camera already opened, open_count[%d]",
			   __func__, cam->open_count);
	}

out:
	file->private_data = dev;
	SAFE_UP(&cam->busy_lock);

    #ifndef CONFIG_ARM64
    trace_dot(CAM, "2", 0);
    #endif

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
	v4l2_ctl_struct *cam = NULL;

	print_info("enter %s", __func__);

	SAFE_GET_DRVDATA(cam, dev);

	SAFE_DOWN(&cam->busy_lock);

	if (--cam->open_count <= 0) {
		camera_flashlight *flashlight = NULL;

		cam->open_count = 0;

		if (cam->running[STATE_CAPTURE]) {
			print_error("cam->running[STATE_CAPTURE]=%d.",cam->running[STATE_CAPTURE]);
			k3_isp_stream_off(STATE_CAPTURE);
			cam->running[STATE_CAPTURE] = 0;
		}

		if (cam->running[STATE_PREVIEW]) {
			print_error("cam->running[STATE_PREVIEW]=%d.",cam->running[STATE_PREVIEW]);
			k3_isp_stream_off(STATE_PREVIEW);
			cam->running[STATE_PREVIEW] = 0;
		}

		k3_isp_exit(cam);

		/* release dvfs block */
		/*
		   if (0 != cam->pm_profile_flag)
		   {
		   k3_release_dvfs_profile();
		   }
		 */
		flashlight = get_camera_flash();
		if (flashlight)
			flashlight->exit();

		/* wake up user process */
		wake_up_interruptible(&cam->data_queue.queue[STATE_IPP]);
		wake_up_interruptible(&cam->data_queue.queue[STATE_CAPTURE]);
		wake_up_interruptible(&cam->data_queue.queue[STATE_PREVIEW]);

        /* when power off,destroy ion client */
        print_info("isp ion_client_destroy.");
        if ((!IS_ERR(cam->ion_client)) && (cam->ion_client != NULL)) {
            ion_client_destroy(cam->ion_client);
            cam->ion_client = NULL;
        }
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
	v4l2_ctl_struct *cam = NULL;

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



#ifdef CONFIG_COMPAT
static inline int ctrl_is_pointer(u32 id)
{
	switch (id) {
	case V4L2_CID_RDS_TX_PS_NAME:
	case V4L2_CID_RDS_TX_RADIO_TEXT:
		return 1;
	default:
		return 0;
	}
}


static int get_v4l2_ext_controls32(struct v4l2_ext_controls *kp, struct v4l2_ext_controls32 __user *up)
{
	struct v4l2_ext_control32 __user *ucontrols;
	struct v4l2_ext_control __user *kcontrols;
	int n;
	compat_caddr_t p;
    //dump_stack();

	if (!access_ok(VERIFY_READ, up, sizeof(struct v4l2_ext_controls32)) ||
		get_user(kp->ctrl_class, &up->ctrl_class) ||
		get_user(kp->count, &up->count) ||
		get_user(kp->error_idx, &up->error_idx) ||
		copy_from_user(kp->reserved, up->reserved, sizeof(kp->reserved)))
			return -EFAULT;
	n = kp->count;
	if (n == 0) {
		kp->controls = NULL;
		return 0;
	}
	if (get_user(p, &up->controls))
		return -EFAULT;
	ucontrols = compat_ptr(p);
	if (!access_ok(VERIFY_READ, ucontrols,
			n * sizeof(struct v4l2_ext_control32)))
		return -EFAULT;
	kcontrols = compat_alloc_user_space(n * sizeof(struct v4l2_ext_control));
	kp->controls = kcontrols;
	while (--n >= 0) {
		if (copy_in_user(kcontrols, ucontrols, sizeof(*ucontrols)))
			return -EFAULT;
		if (ctrl_is_pointer(kcontrols->id)) {
			void __user *s;

			if (get_user(p, &ucontrols->string))
				return -EFAULT;
			s = compat_ptr(p);
			if (put_user(s, &kcontrols->string))
				return -EFAULT;
		}
		ucontrols++;
		kcontrols++;
	}
	return 0;
}

static int put_v4l2_ext_controls32(struct v4l2_ext_controls *kp, struct v4l2_ext_controls32 __user *up)
{
	struct v4l2_ext_control32 __user *ucontrols;
	struct v4l2_ext_control __user *kcontrols = kp->controls;
	int n = kp->count;
	compat_caddr_t p;

	if (!access_ok(VERIFY_WRITE, up, sizeof(struct v4l2_ext_controls32)) ||
		put_user(kp->ctrl_class, &up->ctrl_class) ||
		put_user(kp->count, &up->count) ||
		put_user(kp->error_idx, &up->error_idx) ||
		copy_to_user(up->reserved, kp->reserved, sizeof(up->reserved)))
			return -EFAULT;
	if (!kp->count)
		return 0;

	if (get_user(p, &up->controls))
		return -EFAULT;
	ucontrols = compat_ptr(p);
	if (!access_ok(VERIFY_WRITE, ucontrols,
			n * sizeof(struct v4l2_ext_control32)))
		return -EFAULT;

	while (--n >= 0) {
		unsigned size = sizeof(*ucontrols);

		/* Do not modify the pointer when copying a pointer control.
		   The contents of the pointer was changed, not the pointer
		   itself. */
		if (ctrl_is_pointer(kcontrols->id))
			size -= sizeof(ucontrols->value64);
		if (copy_in_user(ucontrols, kcontrols, size))
			return -EFAULT;
		ucontrols++;
		kcontrols++;
	}
	return 0;
}


static long k3_v4l2_compat_ioctl32(struct file *file, unsigned int cmd, unsigned long arg)
{
	union {
		struct v4l2_ext_controls v2ecs;
		unsigned long vx;
		int vi;
	} karg;

	long ret = -ENOIOCTLCMD;
	void __user *up = compat_ptr(arg);
	int compatible_arg = 1;
	long err = 0;



    print_info("%s cmd=0x%x\n",__func__,cmd);

	if (!file->f_op->unlocked_ioctl)
	{
        return ret;
    }

    switch (cmd) {
        case VIDIOC_CHECK_CAP_32: cmd = VIDIOC_CHECK_CAP; break;
    }

    switch (cmd) {
        case VIDIOC_CHECK_CAP:
		err = get_v4l2_ext_controls32(&karg.v2ecs, up);
		compatible_arg = 0;
		break;
#if 0
        case VIDIOC_S_FMT_EX:
        err = copy_from_user(kp, up, sizeof(struct v4l2_pix_format));
        break;
#endif
    }
	if (err)
		return err;

    err = k3_v4l2_ioctl_g_caps(file, file->private_data,0,cmd,&karg.v2ecs);

    if (err)
		return err;

    switch (cmd) {
    case VIDIOC_CHECK_CAP:
        if (put_v4l2_ext_controls32(&karg.v2ecs, up))
            err = -EFAULT;
        break;
    }

    return err;
}
#endif
static struct v4l2_file_operations k3_v4l2_fops = {
	.owner = THIS_MODULE,
	.open = k3_v4l2_open,
	.release = k3_v4l2_close,
#ifdef K3_V4L2_CAPTURE_TEST
	.mmap = k3_v4l2_mmap,
#endif
	/* in ZSL mode,preview and capture will DQ at the same time. */
	.unlocked_ioctl = video_ioctl2,
#ifdef CONFIG_COMPAT
   .compat_ioctl32 = k3_v4l2_compat_ioctl32,
#endif
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
 * Description : Set default value of v4l2_ctl_struct;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int k3_init_v4l2_ctl(v4l2_ctl_struct *v4l2_ctl)
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
 * Description : Deinit v4l2_ctl_struct;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void k3_deinit_v4l2_ctl(v4l2_ctl_struct *v4l2_ctl)
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
static /*__init*/ int k3_v4l2_probe(struct platform_device *pdev)
{
	int ret = -ENODEV;

	print_info("enter K3 camera v4l2 driver probe");

    /* V8R2B020 not support isp, z62576, 20140412, begin */
    if(0 == video_get_support_isp()) {
        print_error("k3_v4l2_probe, platform not support isp.\n");
        return -EINVAL;
    }
    /* V8R2B020 not support isp, z62576, 20140412, end */

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

    /*for common image, z62576, 20140429, begin*/
	if (of_property_read_u32(pdev->dev.of_node, "DQBUF_IRQ_TIMEOUT", &(v4l2_ctl.dqbuf_irq_timeout))){
		print_error("%s: read DQBUF_IRQ_TIMEOUT error.\n", __func__);
    } else {
        print_info("%s: read DQBUF_IRQ_TIMEOUT: %u.\n", __func__, v4l2_ctl.dqbuf_irq_timeout);
    }
    /*for common image, z62576, 20140429, end*/

#ifdef	K3_CAMERA_ENABLE_SYSFS
	k3_sensors_create_sysfs();
#endif

       #if defined (CONFIG_HUAWEI_DSM)
       if (!client_ovisp22) {
           client_ovisp22 = dsm_register_client(&dsm_ovisp22);
       }
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
static /*__exit*/ int k3_v4l2_remove(struct platform_device *pdev)
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

        //k3_isp_lock_ddr_freq()/* req ddr freq lock */;

		/* init all queues */
		/* init camera data struct here on first open */

		//init_queue(&v4l2_ctl.data_queue, STATE_PREVIEW);
		//init_queue(&v4l2_ctl.data_queue, STATE_CAPTURE);
		//init_queue(&v4l2_ctl.data_queue, STATE_IPP);
		//camera_init_buffer(&v4l2_ctl.buffer_arr[STATE_PREVIEW]);
		//camera_init_buffer(&v4l2_ctl.buffer_arr[STATE_CAPTURE]);
		//camera_init_buffer(&v4l2_ctl.buffer_arr[STATE_IPP]);

		//memset(&isp_rsv_frame[0], 0x00, sizeof(isp_rsv_frame));
		/* init camera controller */
		if (0 != k3_isp_poweron()) {
			print_error("Failed to init isp while resuming");
			k3_isp_poweroff();
			return -ENOMEM;
		}
#ifdef REG_CSI_IRQ
                k3_ispio_csi_isr_enable();
#endif
		//ret = k3_v4l2_set_camera(&v4l2_ctl, v4l2_ctl.cur_sensor);
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
#ifdef REG_CSI_IRQ
                k3_ispio_csi_isr_disable();
#endif
		/* close camera & isp hardware */
		k3_isp_poweroff();

        k3_isp_unlock_ddr_freq()/* cancel and release ddr freq lock */;
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
#include "isp_io_mutex.h"
#include <linux/fs.h>
#include "ispregs.h"
extern void ispv1_read_isp_seq(struct isp_reg_t *pseq, u32 seq_size);
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
		goto error_out;
	}

    for(i=0; isp_regs_list[i].subaddr!=0; i++){
        isp_regs_list[i].value = 0;
    }

    ispv1_read_isp_seq(isp_regs_list, sizeof(isp_regs_list)/sizeof(isp_regs_list[0]));

	fs = get_fs();
	set_fs(KERNEL_DS);

    for(i=0; isp_regs_list[i].subaddr!=0; i++){
        memset(buf, 0x0, sizeof(buf));
        snprintf(buf, sizeof(buf),"\nreg[0x%x]=0x%x,", isp_regs_list[i].subaddr, isp_regs_list[i].value);
        vfs_write(dfilp, &buf[0], sizeof(buf), &dfilp->f_pos);
    }

	set_fs(fs);
	print_info("%s, write file OK.", __func__);

error_out:
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

static struct proc_dir_entry *camera_dir = NULL;//camera dir in proc
static struct proc_dir_entry *otp_entry = NULL; //sensor_otp entry
/*
 **************************************************************************
 * FunctionName: sensor_otp_proc_show;
 * Description : otp status read interface
 * Input       : NA;
 * Output      : seq, output buffer;
 * ReturnValue : 0 for sucess;
 * Other       : NA;
 **************************************************************************
 */
static int sensor_otp_proc_show(struct seq_file *seq, void *v)
{
	sensor_otp_status status =OTP_INVALID;

	if (0 == v4l2_ctl.open_count)
	{
		print_error("camera not opended yet!!");
		return -EFAULT;
	}

	if ((NULL==v4l2_ctl.sensor)||(NULL==v4l2_ctl.sensor->check_otp_status))
	{
		print_error("sensor or check_otp_status is NULL! sensor:%p", v4l2_ctl.sensor);
		return -EFAULT;
	}

	v4l2_ctl.sensor->check_otp_status(&status);

	print_info("otp check result:%d", status);
	seq_printf(seq, "%d",status);

	return 0;

}
/*
 **************************************************************************
 * FunctionName: sensor_otp_proc_open;
 * Description : otp open function.
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int sensor_otp_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, sensor_otp_proc_show, NULL);
}
//fops to get otp status
static const struct file_operations sensor_otp_proc_fops = {
	.open        = sensor_otp_proc_open,
	.read        = seq_read,
	.llseek        = seq_lseek,
	.release    = single_release,
};

//reg to be read
static int regRead;

/*
 **************************************************************************
 * FunctionName: sensor_reg_debug_write;
 * Description : otp status write interface
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t sensor_reg_debug_write(struct file *filp,
	const char __user *ubuf, size_t cnt, loff_t * ppos)
{
	char buf[30]={'\0'};
	int reg = 0, value =0;
	int bufSize = (cnt < (sizeof(buf)-1) ) ? (cnt) : (sizeof(buf) - 1);

	if (0 == v4l2_ctl.open_count)
	{
		print_error("camera not opended yet!!");
		return -EFAULT;
	}
	if (copy_from_user(buf, ubuf, bufSize))
	{
		print_error("%s, copy data error!", __func__);
		return -EFAULT;
	}
	if ( 2 == sscanf(buf, "%x %x", &reg, &value))//write reg
	{
		if ((v4l2_ctl.sensor) && (v4l2_ctl.sensor->set_sensor_reg))
		{
			v4l2_ctl.sensor->set_sensor_reg(reg, value);
			print_info(" %s reg 0x%x, value 0x%x", __func__, reg, value);
		}
		else
		{
			print_error("sensor or set_sensor_reg is NULL! sensor:%p", v4l2_ctl.sensor);
			return -EFAULT;
		}

	}
	else if (1 == sscanf(buf, "%x", &reg))//read reg
	{
		regRead = reg;
	}
	else
	{
		print_error("wrong reg format!");
	}
	return cnt;
}

/*
 **************************************************************************
 * FunctionName: sensor_reg_debug_read;
 * Description : otp status read interface
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static ssize_t sensor_reg_debug_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	char buf[40] = {'\0'};
	int len = 0, value =0;
	ssize_t ret = 0;

	if (0 == v4l2_ctl.open_count)
	{
		print_error("camera not opended yet!!");
		return -EFAULT;
	}
	if ((NULL==v4l2_ctl.sensor)||(NULL==v4l2_ctl.sensor->get_sensor_reg))
	{
		print_error("sensor or get sensor_reg is NULL! sensor:%p", v4l2_ctl.sensor);
		return -EFAULT;
	}

	v4l2_ctl.sensor->get_sensor_reg(regRead, &value);
	len = snprintf(buf, sizeof(buf), "reg0x%x:value0x%x", regRead, value);
	//print_info("%s, reg 0x%x : value 0x%x", __func__, regRead, value );
	ret =  simple_read_from_buffer(buffer, count, ppos, (void*)buf, len);
	if (ret < 0)
	{
		print_error("%s simple_read_from_buffer fail!", __func__);
	}
	return ret;
}
//sensor reg read/write interface
static const struct file_operations debugfs_sensor_reg_fops = {
	//.open = sensor_reg_debug_open,
	.write = sensor_reg_debug_write,
	.read = sensor_reg_debug_read,
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
int camera_init(void)
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
	debugfs_sensor_reg =  debugfs_create_file("sensor_reg", 0664, debugfs_camera_dir,
										 NULL, &debugfs_sensor_reg_fops);
#endif

	camera_dir = proc_mkdir("camera", NULL);//create proc/camera dir
	if (NULL != camera_dir)
	{
		//create proc/camera/sensor_otp entry
		otp_entry = proc_create ("sensor_otp", 0444, camera_dir, &sensor_otp_proc_fops);
		if (NULL == otp_entry)
		{
			print_error("fail to register sensor otp proc entry !!");
			//remove proc/camera dir when fail to create otp entry.
			remove_proc_entry("camera", NULL);
		}
	}
	else
	{
		print_error("fail to register camera proc dir !!");
	}

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
void camera_exit(void)
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
	remove_proc_entry("sensor_otp", camera_dir);
	remove_proc_entry("camera", NULL);
	print_info("K3 camera v4l2 driver exit !!");

	platform_driver_unregister(&k3_v4l2_driver);

	return;
}

/********************************** END **********************************************/
