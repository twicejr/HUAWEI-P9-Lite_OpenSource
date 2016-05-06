

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/ctype.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/clk.h>
#include <linux/videodev2.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/fb.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/unistd.h>
#include <linux/uaccess.h>
#include <asm/div64.h>
//#include <mach/hisi_mem.h>
//#include "mach/hardware.h"
#include <linux/hisi/hi6xxx-boardid.h>
//#include <mach/gpio.h>
#include "../isp/sensor_common.h"
#include <asm/bug.h>
#include <linux/device.h>

#define LOG_TAG "SONYIMX134_TUNE"
//#define DEBUG_DEBUG 1 
#include "../isp/cam_log.h"
#include <../isp/cam_util.h>

/*camera af param which are associated with sensor*/
#define SONYIMX134_AF_MIN_HEIGHT_RATIO	(5)
#define SONYIMX134_AF_MAX_FOCUS_STEP	(6)
#define SONYIMX134_AF_GSENSOR_INTERVAL_THRESHOLD	(50)
#define SONYIMX134_AF_WIDTH_PERCENT	(20)
#define SONYIMX134_AF_HEIGHT_PERCENT	(25)

#define SONYIMX134_STARTCODE_OFFSET             0x30

//#ifdef IMX134_OTP
/*
vcm_start:output vcm_start
vcm_end:output vcm_start
vcm:   input point to vcm struct
otp_vcm_start: input   value read from OTP
otp_vcm_end: input   value read from OTP
*/
void _sonyimx134_otp_get_vcm(u16 *vcm_start, u16 *vcm_end,vcm_info_s *vcm,u16 otp_vcm_start, u16 otp_vcm_end)
{
	if (0 == otp_vcm_start) {
		*vcm_start = vcm->infiniteDistance;
	} else {	
// *vcm_start = sonyimx134_vcm_start;
			 if (otp_vcm_start > vcm->startCurrentOffset)
				*vcm_start = otp_vcm_start - vcm->startCurrentOffset;
			else
				*vcm_start = 0;
	}

	if (0 == otp_vcm_end) {
		*vcm_end = vcm->normalDistanceEnd;
	} else {
		*vcm_end = otp_vcm_end;
	}

	print_debug("%s, start: %#x, end: %#x", __func__, otp_vcm_start, otp_vcm_end);	
}
//#endif

#if 0
int sonyimx134_get_af_param(camera_af_param_t type)
{
	int ret;

	switch(type){
	case AF_MIN_HEIGHT_RATIO:
		ret = SONYIMX134_AF_MIN_HEIGHT_RATIO;
		break;
	case AF_MAX_FOCUS_STEP:
		ret = SONYIMX134_AF_MAX_FOCUS_STEP;
		break;
	case AF_GSENSOR_INTERVAL_THRESHOLD:
		ret = SONYIMX134_AF_GSENSOR_INTERVAL_THRESHOLD;
		break;
	case AF_WIDTH_PERCENT:
		ret = SONYIMX134_AF_WIDTH_PERCENT;
		break;
	case AF_HEIGHT_PERCENT:
		ret = SONYIMX134_AF_HEIGHT_PERCENT;
		break;
	default:
		print_error("%s:invalid argument",__func__);
		ret = -1;
		break;
	}

	return ret;
}
#endif

static awb_gain_t flash_platform_awb[] =
{
	{0xbd, 0x80, 0x80, 0xdc}, /*EDGE*/
};

void sonyimx134_get_flash_awb(flash_platform_t type, awb_gain_t *flash_awb)
{
	*flash_awb = flash_platform_awb[0];
	print_info("sonyimx134_get_flash_awb: type 0x%x,", type);
}

