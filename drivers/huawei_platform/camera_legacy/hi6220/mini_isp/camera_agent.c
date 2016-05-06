

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
#include <mach/boardid.h>
//#include <mach/gpio.h>
#include <linux/gpio.h>
#include "mini_sensor_common.h"
#include <asm/bug.h>
#include <linux/device.h>
#include "drv_regulator_user.h"
#include "hsad/config_interface.h"
#include <mach/pmussi_drv.h>
#include <mini_cam_util.h>
#include "mini_effect.h"
#include "mini_k3_isp.h"
#include "mini_k3_ispv1.h"
#include "mini_k3_ispv1_afae.h"
#include "mini_k3_isp_io.h"
#include "camera_agent.h"

#define LOG_TAG "camera_agent"
#define DEBUG_DEBUG 1
#include "mini_cam_log.h"


/*
 **************************************************************************
 * FunctionName: camera_agent_stream_on;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#define ERR_SUCCESS				0 // No error
#define SET_CMD					1
#define GET_CMD					0

typedef enum {
	MINIISP_FOCUS_FIXED = 0,
	MINIISP_FOCUS_AUTO,
	MINIISP_FOCUS_INFINITY,
	MINIISP_FOCUS_MACRO,
	MINIISP_FOCUS_CONTINUOUS_VIDEO,
	MINIISP_FOCUS_CONTINUOUS_PICTURE,
	MINIISP_FOCUS_EDOF,
	MINIISP_FOCUS_MAX,
} miniisp_focus_mode;

static int remap_sensor_index(sensor_index_t sensor_index)
{
	int ret= 0;

	switch (sensor_index) {
	case CAMERA_SENSOR_PRIMARY:
		ret = 0;
		break;
	case CAMERA_SENSOR_SECONDARY:
		ret = 1;
		break;
	default:
		break;
	}
	return ret;
}

static int remap_sensor_focus_mode(camera_focus mode)
{
	int ret= 0;

	switch (mode) {
	case CAMERA_FOCUS_AUTO:
		ret = MINIISP_FOCUS_AUTO;
		break;
	case CAMERA_FOCUS_INFINITY:
		ret = MINIISP_FOCUS_INFINITY;
		break;
	case CAMERA_FOCUS_MACRO:
		ret = MINIISP_FOCUS_MACRO;
		break;
	case CAMERA_FOCUS_FIXED:
		ret = MINIISP_FOCUS_FIXED ;
		break;
	case CAMERA_FOCUS_EDOF:
		ret = MINIISP_FOCUS_EDOF;
		break;
	case CAMERA_FOCUS_CONTINUOUS_VIDEO:
		ret = MINIISP_FOCUS_CONTINUOUS_VIDEO;
		break;
	case CAMERA_FOCUS_CONTINUOUS_PICTURE:
		ret = MINIISP_FOCUS_CONTINUOUS_PICTURE;
		break;
	//case CAMERA_FOCUS_AUTO_VIDEO:
	//       ret = ;
	//	break;
	//case CAMERA_FOCUS_CAF_FORCE_AF:
	//	ret = ;
	//	break;
	default:
		ret = MINIISP_FOCUS_AUTO;
		break;
	}
	return ret;
}

int camera_agent_streamonoff(sensor_index_t sensor_index, u8 state)
{
	u16 OpCode = ISPCMD_CAMERA_PREVIEWSTREAMONOFF;
	u32 cmd;
	u8 buf[3] = {0,0,0};
	int errorcode;

	print_info("Enter Function:%s=[%s]", __func__, state?"on":"off");

	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);

	buf[sensor_index] = state;

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_sensormode(sensor_index_t sensor_index,u8 size_index,u8 hv_flip)
{
	u16 OpCode = ISPCMD_CAMERA_SET_SENSORMODE;
	u32 cmd;
	u8 buf[7] ={0};
	int errorcode;

	print_info("Enter Function:%s mode=%d hv_flip = %x", __func__, size_index,hv_flip);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));

	sensor_index = remap_sensor_index(sensor_index);
	buf[sensor_index*2] = 1;//on
	buf[sensor_index*2+1] = size_index;
	buf[6] = hv_flip;
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_get_sensormode(sensor_index_t sensor_index,u8 *size_index)
{
	u16 OpCode = ISPCMD_CAMERA_GET_SENSORMODE;
	u32 cmd;
	u8 buf[6] = {0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,GET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
	 	print_error("%s fail, error code = %d", __func__, errorcode);
	 	return -1;
	}
	*size_index = buf[sensor_index*2+1];
	return 0;
}

int camera_agent_get_test_result(void)
{
	u16 OpCode = ISPCMD_GET_BULK_CHIPTEST_REPORT;
	u32 cmd;
	u8 buf[27] = {0};
	int errorcode;
	int i = 0;
	print_info("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,GET_CMD,sizeof(buf));
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	print_info("get result:");

	for(i = 0;i<27;i++)
		{
			if(buf[i] != 1) {
				print_info("buf[%d]=0x%0x  ",i,buf[i]);
				return 0;
				}
		}
	return 1;
}


int camera_agent_s1_lock(sensor_index_t sensor_index)
{
	u16 OpCode = ISPCMD_CAMERA_TAKES1LOCK;
	u32 cmd;
	u8	buf[3]={0};
	int errorcode;

	print_info("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	buf[0] = 1;//on
	buf[1] = 1;//on
	buf[2] = 1;//on
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_s1_lock_abort(void)
{
	u16 OpCode = 0x3035;
	u32 cmd;
	int errorcode;

	print_info("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,0);
	errorcode = misp_exec_cmd(cmd,NULL);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}
//onoff 0:disable s1 af 1:enable s1 af
int camera_agent_set_s1_AF_enable(sensor_index_t sensor_index,u8 onoff)
{
	u16 OpCode = 0x10a4;
	u32 cmd;
	u8	buf[3]={0};
	int errorcode;

	print_info("Enter Function:%s %s", __func__,onoff?"enable":"diable");
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	buf[0] = onoff;
	buf[1] = onoff;
	buf[2] = onoff;
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}
//exporuse: us , ad_gain; 100 means 1x
int camera_agent_take_pictures(sensor_index_t sensor_index, u8 size_index,u8 hv_flip, u32 exposure,u32 ad_gain)
{
	u16 OpCode = ISPCMD_CAMERA_TAKEPICTURES;
	u32 cmd;
	u8 buf[14]={0};
	int errorcode;

	print_info("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	buf[sensor_index] = 1;	//which sensor on
	buf[3] = 1;				//always continous mode
	buf[4] = size_index;	//sensor reslutiion size index
	buf[5] = hv_flip;
	buf[6] = exposure;
	buf[7] = exposure>>8;
	buf[8] = exposure>>16;
	buf[9] = exposure>>24;
	buf[10] = ad_gain;
	buf[11] = ad_gain>>8;
	buf[12] = ad_gain>>16;
	buf[13] = ad_gain>>24;

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_focusarea(mini_focus_win_info_s *win_info)
{
	u16 OpCode = ISPCMD_BASIC_SET_FOCUSAREA;
	u32 cmd;
	static u16 buf[25]={0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	if (((win_info->left+win_info->width/2) == (buf[0]+buf[2]/2))&&
		((win_info->top+win_info->height/2)==(buf[1]+buf[3]/2))) {
		print_debug("%s:same as last AF center point,ignore it!",__func__);
		print_debug("AF area[left top width height] [%d,%d,%d,%d] ", buf[0],buf[1],buf[2],buf[3]);
		return 0;
	}
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	buf[0] = win_info->left;
	buf[1] = win_info->top;
	buf[2] = win_info->width ;
	buf[3] = win_info->height ;
	buf[4] = 1000;
	print_debug("AF area[left top width height] [%d,%d,%d,%d] ", buf[0],buf[1],buf[2],buf[3]);

	errorcode = misp_exec_cmd(cmd, (u8 *)buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_focusmode(sensor_index_t sensor_index,camera_focus mode)
{
	u16 OpCode = ISPCMD_BASIC_SET_FOCUSMODE;
	u32 cmd;
	static u8 buf[3]={0};
	int errorcode;

	print_info("Enter Function:%s mode = %d", __func__,mode);
	sensor_index = remap_sensor_index(sensor_index);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	mode = remap_sensor_focus_mode(mode);

	buf[0] = mode;
	buf[1] = mode;
	buf[2] = mode;

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_meteringarea(mini_camera_rect_s *win_info)
{
	u16 OpCode = ISPCMD_BASIC_SET_METERINGAREA;
	u32 cmd;
	static u16 buf[25]={0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);

	if (((win_info->left+win_info->width/2) == (buf[0]+buf[2]/2))&&
		((win_info->top+win_info->height/2)==(buf[1]+buf[3]/2))) {
		print_debug("%s:same as last meteringarea center point,ignore it!",__func__);
		return 0;
	}

	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	buf[0] = win_info->left;
	buf[1] = win_info->top;
	buf[2] = win_info->width ;
	buf[3] = win_info->height ;
	buf[4] = 1000;
	print_debug("AE area[left top width height] [%d,%d,%d,%d] ", buf[0],buf[1],buf[2],buf[3]);
	errorcode = misp_exec_cmd(cmd,(u8 *)buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_facearea(face_win_info_s *win_info)
{
	u16 OpCode = ISPCMD_BASIC_SET_FACEAREA;
	u32 cmd;
	u16 buf[23]={0};
	int errorcode;
	u8  *buf_ptr,i;

	print_debug("Enter Function:%s ", __func__);

	if(win_info->face_number==0)
	{
		print_error("faces number is zero,just return");
		return 0;
	}
	if(win_info->face_number>MINIISP_MAX_FACE_WIN)
	{
		print_info("mini isp max support %d faces,app face is %d",MINIISP_MAX_FACE_WIN,win_info->face_number);
		win_info->face_number = MINIISP_MAX_FACE_WIN;
	}

	for(i=0;i<win_info->face_number;i++)
	{
		buf[2+i*4] = win_info->face_area[i].left;
		buf[3+i*4] = win_info->face_area[i].top;
		buf[4+i*4] = win_info->face_area[i].width;
		buf[5+i*4] = win_info->face_area[i].height;
	}

	buf[0] = win_info->width;
	buf[1] = win_info->height;

	buf_ptr = (u8 *)buf;
	*(buf_ptr+44) = win_info->face_number;
	*(buf_ptr+45) = win_info->index_max_face;

	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	errorcode = misp_exec_cmd(cmd, (u8 *)buf);
	if (errorcode){
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

//0:enable CAF picture 1:disable CAF picture
int camera_agent_set_PreviewAFLock(sensor_index_t sensor_index,u8 onoff)
{
	u16 OpCode = 0x3033;
	u32 cmd;
	u8 buf[2] ={0};
	int errorcode;

	print_debug("Enter Function:%s onoff = %s", __func__,onoff?"disable":"enable");
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	buf[0] = sensor_index;
	buf[1] = onoff;
	errorcode = misp_exec_cmd(cmd,buf);
	if(errorcode!=ERR_SUCCESS) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_PreviewAELock(sensor_index_t sensor_index,u8 onoff)
{
	u16 OpCode = 0x3032;
	u32 cmd;
	u8 buf[2] ={0};
	int errorcode;

	print_debug("Enter Function:%s onoff = %s", __func__,onoff?"disable":"enable");
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	buf[0] = sensor_index;
	buf[1] = onoff;
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_PreviewAWBLock(sensor_index_t sensor_index,u8 onoff)
{
	u16 OpCode = 0x3034;
	u32 cmd;
	u8 buf[2] ={0};
	int errorcode;

	print_debug("Enter Function:%s onoff = %s", __func__,onoff?"disable":"enable");
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	buf[0] = sensor_index;
	buf[1] = onoff;
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_GSensorInfo(mini_axis_triple *xyz)
{
	u16 OpCode = 0x1037;
	u32 cmd;
	static int buf[3]={0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	if((buf[0]==xyz->x)&&(buf[1]==xyz->y)&&(buf[2]==xyz->z))
	{
		print_debug("%s:same Gyro info as last time!",__func__);
		return 0;
	}
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	buf[0] = xyz->x;
	buf[1] = xyz->y;
	buf[2] = xyz->z ;

	print_debug("GyroSensorInfo[x y z] [%d,%d,%d] ", buf[0],buf[1],buf[2]);
	errorcode = misp_exec_cmd(cmd, (u8*)buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}
//flag 0:no motion 1:motion detected
int camera_agent_set_Motion_Detected(u8 flag)
{
	u16 OpCode = 0x10a5;
	u32 cmd;
	u8 buf[1]={0};
	int errorcode;

	print_debug("Enter Function:%s flag = %d ", __func__,flag);

	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	buf[0] = flag;
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_ANTIFLICKER(sensor_index_t sensor_index,camera_anti_banding banding)
{
	u16 OpCode = ISPCMD_BASIC_SET_ANTIFLICKER;
	u32 cmd;
	u8 buf[1]={0};
	u8 op;
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	switch (banding)
	{
		case CAMERA_ANTI_BANDING_50Hz:
			op = 0;
			break;

		case CAMERA_ANTI_BANDING_60Hz:
			op = 1;
			break;

		case CAMERA_ANTI_BANDING_AUTO:
		case CAMERA_ANTI_BANDING_OFF:
		default:
			op = 0;
			break;
	}

	buf[0]  = op;
	print_debug("banding = %d ", buf[0]);
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}



int camera_agent_get_ANTIFLICKER(sensor_index_t sensor_index)
{
	u16 OpCode = ISPCMD_BASIC_GET_ANTIFLICKER;
	u32 cmd;
	u8 buf[1]={0};
	u8 op;
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,GET_CMD,sizeof(buf));
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}

	switch (buf[0]) {
	case 0:
		op = CAMERA_ANTI_BANDING_AUTO;
		break;
	case 1:
		op = CAMERA_ANTI_BANDING_OFF;
		break;
	case 2:
		op = CAMERA_ANTI_BANDING_50Hz;
		break;
	case 3:
		op = CAMERA_ANTI_BANDING_60Hz;
		break;
	default:
		return -1;
	}

	print_debug("banding = %d ", buf[0]);
	return op;
}

int camera_agent_set_ISOLEVEL(sensor_index_t sensor_index,camera_iso iso)
{
	u16 OpCode = ISPCMD_BASIC_SET_ISOLEVEL;
	u32 cmd;
	u8 buf[3]={0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);

	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);

	buf[0]  = iso;
	buf[1]  = iso;
	buf[2]  = iso;
	print_debug("iso = %d ", buf[sensor_index]);
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_EV(sensor_index_t sensor_index,int ev)
{
	u16 OpCode = ISPCMD_BASIC_SET_EXPOSURECOMPENSATION;
	u32 cmd;
	u8 buf[3]={0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	ev = 3*ev+6;

	buf[0]  = ev;
	buf[1]  = ev;
	buf[2]  = ev;
	print_debug("ev = %d ", buf[sensor_index]);

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_awb(sensor_index_t sensor_index,camera_white_balance awb_mode)
{
	u16 OpCode = ISPCMD_BASIC_SET_WHITEBALANCE;
	u32 cmd;
	u8 buf[3]={0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	switch (awb_mode)
	{
		case CAMERA_WHITEBALANCE_AUTO:
			awb_mode = 0;
			break;
		case CAMERA_WHITEBALANCE_INCANDESCENT:
			awb_mode = 1;
			break;
		case CAMERA_WHITEBALANCE_FLUORESCENT:
			awb_mode = 2;
			break;
		case CAMERA_WHITEBALANCE_DAYLIGHT:
			awb_mode = 3;
			break;
		case CAMERA_WHITEBALANCE_CLOUDY_DAYLIGHT:
			awb_mode = 4;
			break;
		default:
			awb_mode = 0;
			break;
	}
	buf[0]  = awb_mode;
	buf[1]  = awb_mode;
	buf[2]  = awb_mode;
	print_debug("awb = %d ", buf[sensor_index]);

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}
#define debug_flicker 0
#define debug_ae_mode 0
#define debug_exposure_gain 0
#define debug_focus_mode  0

int camera_agent_set_flash_mode(camera_flash flash_mode)
{
	u16 OpCode = ISPCMD_BASIC_SET_FLASHLIGHTMODE;
	u32 cmd;
	u8 buf[1]={0};
	int errorcode;

#if debug_flicker
u8 mode = 0;
switch(flash_mode)
	{
		case CAMERA_FLASH_ON:
			mode = 0;
			break;
		case CAMERA_FLASH_TORCH:
			mode = 3;
			break;
		case CAMERA_FLASH_OFF:
			mode = 1;
			break;
		case CAMERA_FLASH_AUTO:
			mode = 2;
			break;
		default:
			buf[0] = 1;
			break;
	}
camera_agent_set_ANTIFLICKER(0,mode);
#endif
#if debug_focus_mode
u8 mode = 0;
switch(flash_mode)
	{
		case CAMERA_FLASH_ON:
			mode = 2;
			break;
		case CAMERA_FLASH_TORCH:
			mode = 1;
			break;
		case CAMERA_FLASH_OFF:
			mode = 4;//manual af
			break;
		case CAMERA_FLASH_AUTO:
			mode = 0;
			break;
		default:
			mode = 0;
			break;
	}
 camera_agent_set_focusmode(0,mode);
#endif

#if debug_ae_mode
u8 mode = 0;
switch(flash_mode)
	{
		case CAMERA_FLASH_ON:
			mode = 1;
			break;
		case CAMERA_FLASH_TORCH:
			mode = 2;
			break;
		case CAMERA_FLASH_OFF:
			mode = 3;
			break;
		case CAMERA_FLASH_AUTO:
			mode = 0;
			break;
		default:
			buf[0] = 1;
			break;
	}
camera_agent_set_ae_mode(0,mode);
#endif
#if debug_exposure_gain
u32 expo = 0;
u8 gain = 0;
switch(flash_mode)
	{
		case CAMERA_FLASH_ON:
			expo = 10000;
			gain = 100;
			break;
		case CAMERA_FLASH_TORCH:
			expo = 10000;
			gain = 100;
			break;
		case CAMERA_FLASH_OFF:
			expo = 10;
			gain = 100;
			break;
		case CAMERA_FLASH_AUTO:
			expo = 0;
			gain = 0;
			break;
		default:
			expo = 0;
			gain = 0;
			break;
	}
camera_agent_set_exposuretime(expo);
camera_agent_set_ADgain(gain);
#endif

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));

	switch(flash_mode)
	{
		case CAMERA_FLASH_ON:
			buf[0] = 8;
			break;
		case CAMERA_FLASH_TORCH:
			buf[0] = 1;
			break;
		case CAMERA_FLASH_OFF:
			buf[0] = 1;
			break;
		case CAMERA_FLASH_AUTO:
			buf[0] = 4;
			break;
		default:
			buf[0] = 4;
			break;
	}
	print_debug("flash_mode = %d ", buf[0]);

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	 return 0;
}

int camera_agent_set_AFflashon(void)
{
	u16 OpCode = ISPCMD_BASIC_SET_AFFLASHON;
	u32 cmd;
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,0);

	errorcode = misp_exec_cmd(cmd,NULL);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_Preflashon(void)
{
	u16 OpCode = ISPCMD_BASIC_SET_PREFLASHON;
	u32 cmd;
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,0);

	errorcode = misp_exec_cmd(cmd,NULL);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}


int camera_agent_set_AFlevel(sensor_index_t sensor_index,u8 level)
{
	u16 OpCode = 0x1038;
	u32 cmd;
	u8 buf[2] = {0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	buf[0] = level;
	buf[1] = sensor_index;

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_scene_mode(sensor_index_t sensor_index,camera_scene scene)
{
	u16 OpCode = ISPCMD_BASIC_SET_SCENEMODE;
	u32 cmd;
	u8 buf[3]={0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	if(scene>14)
	{
		print_error("unsupport sence mode = %d  set default sence auto",scene);
		scene = 0;
	}

	buf[0]  = scene;
	buf[1]  = scene;
	buf[2]  = scene;
	print_debug("awb = %d ", buf[sensor_index]);

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_exposuretime(u32 expotime)
{
	u16 OpCode = 0x0106;
	u32 cmd;
	u8 buf[4] = {0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	print_debug("expotime = %d ", expotime);
	*((u32 *)buf) = expotime;
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_ADgain(u16 gain)
{
	u16 OpCode = 0x0107;
	u32 cmd;
	u8 buf[2] = {0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	print_debug("gain = %d ", gain);
	*((u16 *)buf) = gain;
	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_set_ae_mode(sensor_index_t sensor_index,AE_mode mode)
{
	u16 OpCode = 0x1018;
	u32 cmd;
	u8 buf[3]={0};
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);
	if(mode>=MODE_MAX)
	{
		print_error("unsupport sence mode = %d  set default sence auto",mode);
		mode = AUTO_MODE;
	}

	buf[0]  = mode;
	buf[1]  = mode;
	buf[2]  = mode;
	print_debug("mode = %d ", buf[sensor_index]);

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

int camera_agent_take_ae_image(void)
{
	u16 OpCode = 0x10A0;
	u32 cmd;
	int errorcode;

	print_debug("Enter Function:%s ", __func__);
	cmd = misp_construct_opcode(OpCode,SET_CMD,0);
	errorcode = misp_exec_cmd(cmd,NULL);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}
//0:enable AE 1:disable AE
int camera_agent_set_auto_exposure(sensor_index_t sensor_index,u8 onoff)
{
	u16 OpCode = ISPCMD_BASIC_SET_AUTOEXPOSURE;
	u32 cmd;
	u8 buf[3] = {0};
	int errorcode;

	print_debug("Enter Function:%s=[%s]", __func__, onoff?"off":"on");
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);

	buf[0] = onoff;
	buf[1] = onoff;
	buf[2] = onoff;

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}
//0:ae lock when shoot  1:enable AE when shoot
int camera_agent_set_burst_shoot(u8 onoff)
{
	u16 OpCode = 0x101a;
	u32 cmd;
	u8 buf[1] = {0};
	int errorcode;

	print_debug("Enter Function:%s=[%s]", __func__, onoff?"on":"off");
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	buf[0] = onoff;

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}
//mode 0:off 1:on 2:auto
int camera_agent_set_hdr_mode(sensor_index_t sensor_index,u8 mode)
{
	u16 OpCode = 0x1096;
	u32 cmd;
	u8 buf[3] = {0};
	int errorcode;

	print_debug("Enter Function:%s=[%d]", __func__, mode);
	cmd = misp_construct_opcode(OpCode,SET_CMD,sizeof(buf));
	sensor_index = remap_sensor_index(sensor_index);

	buf[0] = mode;
	buf[1] = mode;
	buf[2] = mode;

	errorcode = misp_exec_cmd(cmd,buf);
	if (errorcode) {
		print_error("%s fail, error code = %d", __func__, errorcode);
		return -1;
	}
	return 0;
}

