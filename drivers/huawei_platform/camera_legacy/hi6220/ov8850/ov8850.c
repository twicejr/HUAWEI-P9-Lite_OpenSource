/*
 *  OV8850 camera driver source file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *	Author :
 *  Version:  1.2
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
#include <mach/hisi_mem.h>
#include "mach/hardware.h"
#include <mach/boardid.h>
#include <mach/gpio.h>
#include "../isp/sensor_common.h"
#include "ov8850.h"
/*#include "../isp/k3_isp_io.h"*/
#include <asm/bug.h>
#include <linux/device.h>
#include <../isp/cam_util.h>

#define LOG_TAG "ov8850"
/* #define DEBUG_DEBUG 1 */
#include "../isp/cam_log.h"
#include <hsad/config_interface.h>

#define OV8850_APERTURE_FACTOR		240 // F2.4, LG 9569A3
#define OV8850_EQUIVALENT_FOCUS		35  // 35mm,视角相当于35mm焦距的相机

//module id, TBD
#define OV8850_FOXCONN_FACTORY_ID	0x00	//use this module
#define OV8850_SUNNY_FACTORY_ID		0x01
#define OV8850_SAMSUNG_FACTORY_ID	0x02

#define OV8850_SLAVE_ADDRESS_20 0x20
#define OV8850_SLAVE_ADDRESS_6C 0x6c	//SID is HIGH connected to DOVDD
#define OV8850_CHIP_ID       (0x8850)	//chip id

#define OV8850_NO_FLIP	0x00
#define OV8850_H_FLIP	0x01
#define OV8850_V_FLIP	0x02
#define OV8850_HV_FLIP	0x03

#define OV8850_EXPOSURE_REG_0	0x3500	//AEC_LONG_EXPO
#define OV8850_EXPOSURE_REG_1	0x3501
#define OV8850_EXPOSURE_REG_2	0x3502
#define OV8850_GAIN_REG_H		0x350a	//AEC_AGC_ADJ  gain[10:8]
#define OV8850_GAIN_REG_L		0x350b	//AEC_AGC_ADJ gain[7:0]

#define OV8850_HTS_REG_H		0x380c	//TIMING_HTS high
#define OV8850_HTS_REG_L		0x380d	//TIMING_HTS low
#define OV8850_VTS_REG_H		0x380e	//TIMING_VTS high
#define OV8850_VTS_REG_L		0x380f	//TIMING_VTS low

#define OV8850_APERTURE_FACTOR		240 // F2.4
#define OV8850_EQUIVALENT_FOCUS		35  // view-angle equivalent to 35mm camera

//#define OV8850_AP_WRITEAE_MODE

#define OV8850_ISO	(\
				(1 << CAMERA_ISO_AUTO) | \
				(1 << CAMERA_ISO_100) | \
				(1 << CAMERA_ISO_200) | \
				(1 << CAMERA_ISO_400) | \
				(1 << CAMERA_ISO_800) | \
				(1 << CAMERA_ISO_1600) \
			)

static camera_capability ov8850_cap[] = {
	{V4L2_CID_FLASH_MODE, THIS_FLASH},
	{V4L2_CID_FOCUS_MODE, THIS_FOCUS_MODE},
	{V4L2_CID_ISO, OV8850_ISO},
};
/*camera sensor supported iso upper and lower limit definition*/
#define OV8850_ISO_UPPER_LIMIT		(1550)
#define OV8850_ISO_LOWER_LIMIT	(100)


const struct isp_reg_t isp_init_regs_ov8850_foxconn[] = {
/* BLC */
	{0x1c58b, 0x40}, //avoid false contour Richard@0323
	{0x1c58c, 0x40}, //avoid false contour Richard@0323

/* AEC */
	{0x1c146, 0x2c},//ori0x30 low AE target,should close
	{0x1c14a, 0x03},
	{0x1c14b, 0x0a},
	{0x1c14c, 0x0a},//aec fast step//
	{0x1c14e, 0x08},//slow step//08
	{0x1c140, 0x01},//banding
	{0x1c13e, 0x02},//real gain mode for ov8850
	
	{0x66401, 0x00},//window weight
	{0x66402, 0x20},//StatWin_Left
	{0x66403, 0x00},
	{0x66404, 0x20},//StatWin_Top
	{0x66405, 0x00},
	{0x66406, 0x20},//StatWin_Right
	{0x66407, 0x00},
	{0x66408, 0x28},//StatWin_Bottom
	{0x66409, 0x00},//definiton ofthe center 3x3 window
	{0x6640a, 0xc8},//nWin_Left
	{0x6640d, 0x00},
	{0x6640e, 0x96},//nWin_Top
	{0x66411, 0x04},
	{0x66412, 0xb0},//nWin_Width
	{0x66415, 0x03},
	{0x66416, 0x84},//nWin_Height
	{0x6642e, 0x01},//nWin_Weight_0 weight pass
	{0x6642f, 0x01},//nWin_Weight_1
	{0x66430, 0x01},//nWin_Weight_2
	{0x66431, 0x01},//nWin_Weight_3
	{0x66432, 0x02},//nWin_Weight_4
	{0x66433, 0x02},//nWin_Weight_5
	{0x66434, 0x02},//nWin_Weight_6
	{0x66435, 0x02},//nWin_Weight_7
	{0x66436, 0x04},//nWin_Weight_8
	{0x66437, 0x02},//nWin_Weight_9
	{0x66438, 0x02},//nWin_Weight_10
	{0x66439, 0x02},//nWin_Weight_11
	{0x6643a, 0x02},//nWin_Weight_12
	{0x6644e, 0x03},//nWin_Weight_Shift
	{0x6644f, 0x04},//black level
	{0x66450, 0xf8},//saturate level
	{0x6645b, 0x1a},//black weight1
	{0x6645d, 0x1a},//black weight2
	{0x66460, 0x04},//saturate per1
	{0x66464, 0x0a},//saturate per2
	{0x66467, 0x14},//saturate weight1
	{0x66469, 0x14},//saturate weight2
	//auto AE control
	
/* Raw Stretch */
	{0x65020, 0x01},//RAW Stretch Target
	{0x66500, 0x28},
	{0x66501, 0x00},
	{0x66502, 0xff},
	{0x66503, 0x0f},
	{0x1c1b0, 0xff},
	{0x1c1b1, 0xff},
	{0x1c1b2, 0x01},
	{0x65905, 0x08},
	{0x66301, 0x02},//high level step
	{0x66302, 0xd0},//ref bin
	{0x66303, 0x0a},//PsPer0
	{0x66304, 0x10},//PsPer1
	{0x1c5a4, 0x01},//use new high stretch
	{0x1c5a5, 0x20},//stretch low step
	{0x1c5a6, 0x20},//stretch high step
	{0x1c5a7, 0x08},//stretch slow range
	{0x1c5a8, 0x02},//stretch slow step
	{0x1c1b8, 0x10},//ratio scale
	
	{0x1c5a0, 0x4c},//AE target high
	{0x1c5a2, 0x04},//target stable range
	{0x1c5a3, 0x06},//stretch target slow range
	
/* De-noise */
	{0x65604, 0x00},//Richard for new curve 0314
	{0x65605, 0x00},//Richard for new curve 0314
	{0x65606, 0x00},//Richard for new curve 0314
	{0x65607, 0x00},//Richard for new curve 0314

	{0x65510, 0x0f},//G dns slope change from 0x4 to 0xf Richard 0320
	{0x6551a, 0x00},//Raw G Dns improve white pixel 20120728
	{0x6551b, 0x00},//
	{0x6551c, 0x04},//
	{0x6551d, 0x05},//
	{0x6551e, 0x05},//
	{0x6551f, 0x16},//
	{0x65520, 0x16},//

	{0x65522, 0x00},//RAW BR De-noise
	{0x65523, 0x02},
	{0x65524, 0x00},
	{0x65525, 0x04},
	{0x65526, 0x00},
	{0x65527, 0x08},
	{0x65528, 0x00},
	{0x65529, 0x10},
	{0x6552a, 0x00},
	{0x6552b, 0x20},
	{0x6552c, 0x00},
	{0x6552d, 0x20},
	{0x6552e, 0x00},
	{0x6552f, 0x20},
	
	{0x65c00, 0x03},//UV De-noise
	{0x65c01, 0x05},
	{0x65c02, 0x08},
	{0x65c03, 0x1f},
	{0x65c04, 0x1f},
	{0x65c05, 0x1f},
	

/* sharpeness */   
	{0x65600, 0x00},
	{0x65601, 0x10},//0319
	{0x65602, 0x00},
	{0x65603, 0x60},
	{0x65608, 0x06},
	{0x65609, 0x20},
	{0x6560c, 0x00},//high gain sharpness
	{0x6560d, 0x30},//low gain sharpness, 20120814 0x20->0x30
	{0x6560e, 0x10},//MinSharpenTp
	{0x6560f, 0x60},//MaxSharpenTp
	{0x65610, 0x10},//MinSharpenTm
	{0x65611, 0x60},//MaxSharpenTm
	{0x65613, 0x10},
	{0x65615, 0x08},//HFreq_thre
	{0x65617, 0x06},//HFreq_coef	

/* auto uv saturation */
	{0x1c4e8, 0x01},//Enable
	{0x1c4e9, 0x40},
	{0x1c4ea, 0x78},
	{0x1c4eb, 0x80}, //keep back for new cmx 0310
	{0x1c4ec, 0x68}, //keep back for new cmx 0310

/* Global Gamma */
	{0x1c49b, 0x01},
	{0x1c49c, 0x02},
	{0x1c49d, 0x01}, //gamma 2.0 0310
	{0x1c49e, 0x02},
	{0x1c49f, 0x01}, //gamma 2.0 0310
	{0x1c4a0, 0x00},
	{0x1c4a1, 0x18},
	{0x1c4a2, 0x00},
	{0x1c4a3, 0x88}, //gamma 2.0 0310 //avoid false contour Richard@0323


/* Tone Mapping */
	//contrast curve change for skin over exposure 20120728
	{0x1C4C0, 0x1a},
	{0x1C4C1, 0x29},
	{0x1C4C2, 0x35},
	{0x1C4C3, 0x41},
	{0x1C4C4, 0x4d},
	{0x1C4C5, 0x58},
	{0x1C4C6, 0x64},
	{0x1C4C7, 0x70},
	{0x1C4C8, 0x7c},
	{0x1C4C9, 0x89},
	{0x1C4CA, 0x96},
	{0x1C4CB, 0xa4},
	{0x1C4CC, 0xb5},
	{0x1C4CD, 0xc9},
	{0x1C4CE, 0xe2},	{0x1c4d4, 0x20},//EDR scale
	{0x1c4d5, 0x20},//EDR scale
	{0x1c4cf, 0x80},
	{0x65a00, 0x1b},
	{0x65a01, 0xc0}, //huiyan 0801

	//dark boost
	{0x1c4b0, 0x02},
	{0x1c4b1, 0x80},

	//curve gain control
	{0x1c1b3, 0x30}, //Gain thre1
	{0x1c1b4, 0x70}, //Gain thre2 
	{0x1c1b5, 0x01}, //EDR gain control
	{0x1c1b6, 0x01}, //Curve Gain control
	{0x1c1b7, 0x40}, //after gamma cut ratio

	//Manual UV curve
	{0x1C998, 0x01},
	{0x1C999, 0x27},
	{0x1C99A, 0x01},
	{0x1C99B, 0x3b},
	{0x1C99C, 0x01},
	{0x1C99D, 0x40},
	{0x1C99E, 0x01},
	{0x1C99F, 0x40},
	{0x1C9A0, 0x01},
	{0x1C9A1, 0x40},
	{0x1C9A2, 0x01},
	{0x1C9A3, 0x40},
	{0x1C9A4, 0x01},
	{0x1C9A5, 0x40},
	{0x1C9A6, 0x01},
	{0x1C9A7, 0x40},
	{0x1C9A8, 0x01},
	{0x1C9A9, 0x40},
	{0x1C9AA, 0x01},
	{0x1C9AB, 0x40},
	{0x1C9AC, 0x01},
	{0x1C9AD, 0x40},
	{0x1C9AE, 0x01},
	{0x1C9AF, 0x3E},
	{0x1C9B0, 0x01},
	{0x1C9B1, 0x31},
	{0x1C9B2, 0x01},
	{0x1C9B3, 0x13},
	{0x1C9B4, 0x00},
	{0x1C9B5, 0xE6},
	{0x1C9B6, 0x00},
	{0x1C9B7, 0xAA},

/* LENC */
	{0x1c247, 0x00},//one profile
	{0x1c24c, 0x00},
	{0x1c24d, 0x40},
	{0x1c24e, 0x00},
	{0x1c24f, 0x80},
	{0x1c248, 0x40},
	{0x1c24a, 0x20},
	{0x1c574, 0x00},
	{0x1c575, 0x20},
	{0x1c576, 0x00},
	{0x1c577, 0xf0},
	{0x1c578, 0x40},

	{0x65200, 0x0d},
	{0x65206, 0x3c},
	{0x65207, 0x04},
	{0x65208, 0x3c}, //new shading params revised 20120816
	{0x65209, 0x04},
	{0x6520a, 0x33},
	{0x6520b, 0x0c},
	{0x65214, 0x28},
	{0x65216, 0x20},
	{0x1d93d, 0x08},
	{0x1d93e, 0x00},
	{0x1d93f, 0x40},
	{0x1d940, 0xfc},
	{0x1d942, 0x04},
	{0x1d941, 0xfc},
	{0x1d943, 0x04},

	{0x1d944, 0x00},
	{0x1d946, 0x00},
	{0x1d945, 0xfc},
	{0x1d947, 0x04},


	/* OVISP LENC setting for DAY light Long Exposure (HDR/3D) */
	{0x1c264, 0x0a},
	{0x1c265, 0x05},
	{0x1c266, 0x05},
	{0x1c267, 0x05},
	{0x1c268, 0x05},
	{0x1c269, 0x06},
	{0x1c26a, 0x04},
	{0x1c26b, 0x04},
	{0x1c26c, 0x02},
	{0x1c26d, 0x03},
	{0x1c26e, 0x04},
	{0x1c26f, 0x05},
	{0x1c270, 0x04},
	{0x1c271, 0x01},
	{0x1c272, 0x00},
	{0x1c273, 0x00},
	{0x1c274, 0x02},
	{0x1c275, 0x04},
	{0x1c276, 0x03},
	{0x1c277, 0x01},
	{0x1c278, 0x00},
	{0x1c279, 0x00},
	{0x1c27a, 0x01},
	{0x1c27b, 0x04},
	{0x1c27c, 0x04},
	{0x1c27d, 0x03},
	{0x1c27e, 0x02},
	{0x1c27f, 0x02},
	{0x1c280, 0x03},
	{0x1c281, 0x06},
	{0x1c282, 0x08},
	{0x1c283, 0x05},
	{0x1c284, 0x05},
	{0x1c285, 0x05},
	{0x1c286, 0x05},
	{0x1c287, 0x0a},
	
	{0x1c288, 0x21},
	{0x1c289, 0x20},
	{0x1c28a, 0x1f},
	{0x1c28b, 0x21},
	{0x1c28c, 0x21},
	{0x1c28d, 0x20},
	{0x1c28e, 0x21},
	{0x1c28f, 0x21},
	{0x1c290, 0x20},
	{0x1c291, 0x20},
	{0x1c292, 0x21},
	{0x1c293, 0x21},
	{0x1c294, 0x1f},
	{0x1c295, 0x21},
	{0x1c296, 0x20},
	{0x1c297, 0x20},
	{0x1c298, 0x20},
	{0x1c299, 0x21},
	{0x1c29a, 0x20},
	{0x1c29b, 0x20},
	{0x1c29c, 0x20},
	{0x1c29d, 0x20},
	{0x1c29e, 0x1f},
	{0x1c29f, 0x20},
	{0x1c2a0, 0x20},
	
	{0x1c2a1, 0x22},
	{0x1c2a2, 0x23},
	{0x1c2a3, 0x23},
	{0x1c2a4, 0x23},
	{0x1c2a5, 0x23},
	{0x1c2a6, 0x23},
	{0x1c2a7, 0x22},
	{0x1c2a8, 0x22},
	{0x1c2a9, 0x22},
	{0x1c2aa, 0x22},
	{0x1c2ab, 0x23},
	{0x1c2ac, 0x21},
	{0x1c2ad, 0x1f},
	{0x1c2ae, 0x21},
	{0x1c2af, 0x23},
	{0x1c2b0, 0x22},
	{0x1c2b1, 0x22},
	{0x1c2b2, 0x22},
	{0x1c2b3, 0x22},
	{0x1c2b4, 0x22},
	{0x1c2b5, 0x22},
	{0x1c2b6, 0x24},
	{0x1c2b7, 0x23},
	{0x1c2b8, 0x23},
	{0x1c2b9, 0x23},

/* AWB */
	{0x66201, 0x52},
	{0x66203, 0x14},//crop window
	{0x66211, 0xe8},//awb top limit
	{0x66212, 0x04},//awb bottom limit	

	{0x1c17c, 0x01},//CT mode, should close
	{0x1c182, 0x04},
	{0x1c183, 0x00},//MinNum
	{0x1c184, 0x04},//AWB Step		
	{0x1c58d, 0x00},//LimitAWBAtD65Enable

	{0x1c1be, 0x00},//AWB offset
	{0x1c1bf, 0x00},
	{0x1c1c0, 0x00},
	{0x1c1c1, 0x00},

	{0x1c1aa, 0x00},//avgAllEnable	
	{0x1c1ad, 0x02},//weight of A
	{0x1c1ae, 0x08},//weight of D65
	{0x1c1af, 0x04},//weight of CWF

	{0x1c5ac, 0x80},//pre-bgain, apply on CCM
	{0x1c5ad, 0x80},//pre-ggain
	{0x1c5ae, 0x80},//pre-rgain

	{0x1ccce, 0x02},//ori0x02 awb shift
	{0x1cccf, 0xf8},//B gain for A
	{0x1ccd0, 0x20},//R gain for A
	{0x1c5b8, 0x00},//B gain for C outdoor
	{0x1c5b9, 0x10},//R gain for C outdoor
	{0x1ccd1, 0x00},
	{0x1ccd2, 0x10},//R gain for C indoor
	{0x1ccd3, 0xf8},
	{0x1ccd4, 0x08},//R gain for D indoor
	{0x1cccc, 0xf8},//B gain for D outdoor
	{0x1cccd, 0x08},//R gain for D outdoor

	{0x1c5b4, 0x02},//C indoor/outdoor switch lum 1 Richard@0517
	{0x1c5b5, 0xff},//C indoor/outdoor switch lum 1 Richard@0517
	{0x1c5b6, 0x04},//C indoor/outdoor switch lum 2 Richard@0517
	{0x1c5b7, 0xff},//C indoor/outdoor switch lum 2 Richard@0517

	{0x1ccd5, 0x43},//CT_A
	{0x1ccd6, 0x70},//CT_C
	{0x1ccd7, 0xbc},//CT_D

	{0x1c5cd, 0x01},//ori0x01 high light awb shift, modified by Jiangtao to avoid blurish when high CT 0310
	{0x1c5ce, 0x00},
	{0x1c5cf, 0xf0},
	{0x1c5d0, 0x01},
	{0x1c5d1, 0x20},
	{0x1c5d2, 0x03},
	{0x1c5d3, 0x00},
	{0x1c5d4, 0x40},//
	{0x1c5d5, 0xa0},//
	{0x1c5d6, 0xb0},//
	{0x1c5d7, 0xe8},//
	{0x1c5d8, 0x40},//
	{0x1c1c2, 0x00},
	{0x1c1c3, 0x20},

	//OVISP CTAWB setting for Long Exposure (HDR/3D) 
	{0x66206 ,0x0c},
	{0x66207 ,0x0f},
	{0x66208 ,0x11},
	{0x66209 ,0x7c},
	{0x6620a ,0x64},
	{0x6620b ,0xda},
	{0x6620c ,0xb9},
	{0x6620d ,0x4c},
	{0x6620e ,0x37},
	{0x6620f ,0x6c},
	{0x66210 ,0x54},
	{0x66201 ,0x52},
	{0x1c1c8 ,0x01},
	{0x1c1c9 ,0x00},
	{0x1c1cc ,0x00},
	{0x1c1cd ,0xb3},
	{0x1c1d0 ,0x01},
	{0x1c1d1 ,0xe2},
	{0x1c254 ,0x00},
	{0x1c255 ,0xc4},
	{0x1c256 ,0x00},
	{0x1c257 ,0xe2},
	{0x1c258 ,0x01},
	{0x1c259 ,0x58},
	{0x1c25a ,0x01},
	{0x1c25b ,0xb0},


/* Color matrix */
	{0x1C1d8, 0x02},//center matrix, for color accuracy 20120728 
	{0x1C1d9, 0x52},
	{0x1C1da, 0xfe},
	{0x1C1db, 0xae},
	{0x1C1dc, 0x00},
	{0x1C1dd, 0x00},
	{0x1C1de, 0xff},
	{0x1C1df, 0xe0},
	{0x1C1e0, 0x01},
	{0x1C1e1, 0x72},
	{0x1C1e2, 0xff},
	{0x1C1e3, 0xae},
	{0x1C1e4, 0x00},
	{0x1C1e5, 0x12},
	{0x1C1e6, 0xfe},
	{0x1C1e7, 0xde},
	{0x1C1e8, 0x02},
	{0x1C1e9, 0x10},		

	{0x1C1FC, 0xff},//cmx left delta
	{0x1C1FD, 0xcf},
	{0x1C1FE, 0x00},
	{0x1C1FF, 0x1f},
	{0x1C200, 0x00},
	{0x1C201, 0x12},
	{0x1C202, 0xff},
	{0x1C203, 0xba},
	{0x1C204, 0x00},
	{0x1C205, 0x06},
	{0x1C206, 0x00},
	{0x1C207, 0x40},
	{0x1C208, 0xff},
	{0x1C209, 0xef},
	{0x1C20A, 0x00},
	{0x1C20B, 0x49},
	{0x1C20C, 0xff},
	{0x1C20D, 0xc8},

	{0x1C220, 0x00},//cmx right delta
	{0x1C221, 0xae},
	{0x1C222, 0xff},
	{0x1C223, 0x7d},
	{0x1C224, 0xff},
	{0x1C225, 0xd5},
	{0x1C226, 0xff},
	{0x1C227, 0xde},
	{0x1C228, 0x00},
	{0x1C229, 0x1d},
	{0x1C22A, 0x00},
	{0x1C22B, 0x05},
	{0x1C22C, 0xff},
	{0x1C22D, 0xc3},
	{0x1C22E, 0x00},
	{0x1C22F, 0xd5},
	{0x1C230, 0xff},
	{0x1C231, 0x68},

	/* dpc */
	{0x65409, 0x04},
	{0x6540a, 0x02},
	{0x6540b, 0x01},
	{0x6540c, 0x01},
	{0x6540d, 0x04},
	{0x6540e, 0x02},
	{0x6540f, 0x01},
	{0x65410, 0x01},
	{0x65408, 0x0b},

	//high gain curve for dark color change 20120728
   	{0x1d963, 0x1c},
	{0x1d964, 0x2d},
	{0x1d965, 0x3b},
	{0x1d966, 0x48},
	{0x1d967, 0x55},
	{0x1d968, 0x60},
	{0x1d969, 0x6b},
	{0x1d96a, 0x77},
	{0x1d96b, 0x83},
	{0x1d96c, 0x8f},
	{0x1d96d, 0x9b},
	{0x1d96e, 0xa7},
	{0x1d96f, 0xb7},
	{0x1d970, 0xc9},
	{0x1d971, 0xe2},                 
	{0x1d8fe, 0x01}, //UV cut gain control
	{0x1d8ff, 0x50}, //low gain thres
	{0x1d900, 0x70}, //high gain thres
	{0x1d97f, 0x14}, //UV cut low bright thres
	{0x1d973, 0x20}, //UV cut high bright thres
	{0x1d972, 0x01}, //adaptive gamma enable
	{0x1d974, 0x01}, //low gain gamma
	{0x1d975, 0xe6},
	{0x1d976, 0x01}, //high gain gamma
	{0x1d977, 0xc0},
	{0x1d978, 0x01}, //dark image gamma
	{0x1d979, 0xb3},
	{0x1d97a, 0x88}, //low gain slope
	{0x1d97b, 0x50}, //high gain slope
	{0x1d97c, 0x38}, //dark image slope
	{0x1d97d, 0x14}, //low bright thres
	{0x1d97e, 0x20}, //high bright thres

	{0x1d99e, 0x01}, //dynamic UV curve, huiyan 20120803 for dark uv noise
	//low gain UV curve 1/2
	{0x1d904, 0x8b},
	{0x1d905, 0x95},
	{0x1d906, 0x98},
	{0x1d907, 0x98},
	{0x1d908, 0x98},
	{0x1d909, 0x98},
	{0x1d90a, 0x98},
	{0x1d90b, 0x98},
	{0x1d90c, 0x98},
	{0x1d90d, 0x98},
	{0x1d90e, 0x98},
	{0x1d90f, 0x97},
	{0x1d910, 0x94},
	{0x1d911, 0x89},
	{0x1d912, 0x72},
	{0x1d913, 0x55},
	//high gain UV curve 1/2
	{0x1d914, 0x46},
	{0x1d915, 0x70},
	{0x1d916, 0x88},
	{0x1d917, 0x92},
	{0x1d918, 0x96},
	{0x1d919, 0x98},
	{0x1d91a, 0x98},
	{0x1d91b, 0x98},
	{0x1d91c, 0x98},
	{0x1d91d, 0x98},
	{0x1d91e, 0x98},
	{0x1d91f, 0x97},
	{0x1d920, 0x94},
	{0x1d921, 0x89},
	{0x1d922, 0x72},
	{0x1d923, 0x55},

	{0x1d924, 0x01}, //enable
	{0x1d950, 0x00}, //Br thres
	{0x1d951, 0x20}, //Br thres	
	{0x1d952, 0x30}, //Br Ratio
	{0x1d8dc, 0x00}, //Br thres0
	{0x1d8dd, 0xf0},
	{0x1d8de, 0x44},
	{0x1d8df, 0x34},
	{0x1d8da, 0x10}, //Br Ratio0
	{0x1d8db, 0x06}, //Br Ratio1
	{0x1d949, 0x0c}, //super highlight cwf thres //66206
	{0x1d925, 0x0c}, //highlight cwf thres //66206
	{0x1d926, 0x13},//middlelight cwf thres
	{0x1d927, 0x15}, //lowlight cwf thres
	{0x1d94a, 0x11}, //super highlight A thres //66207
	{0x1d928, 0x11}, //highlight A thres //66207
	{0x1d929, 0x18}, //middlelight A thres
	{0x1d92a, 0x1d}, //lowlight A thres	
	{0x1d94b, 0x14}, //super highlight D thres //66208
	{0x1d92b, 0x14}, //highlight D thres //66208
	{0x1d92c, 0x14}, //middlelight D thres
	{0x1d92d, 0x1d}, //lowlight D thres	
	{0x1d94c, 0x55}, //super highlight D limit //6620d
	{0x1d92e, 0x4a}, //highlight D limit //6620d
	{0x1d92f, 0x45}, //middlelight D limit
	{0x1d930, 0x40}, //lowlight D limit		
	{0x1d94d, 0x48}, //super highlight A limit //6620e
	{0x1d931, 0x48}, //highlight A limit //6620e
	{0x1d932, 0x36}, //middlelight A limit
	{0x1d933, 0x32}, //lowlight A limit		
	{0x1d94e, 0x6e}, //super highlight D split //6620f
	{0x1d934, 0x6e}, //highlight D split //6620f
	{0x1d935, 0x6e}, //middlelight D split
	{0x1d936, 0x6e}, //lowlight D split
	{0x1d94f, 0x60},	//super highlight A split //66210
	{0x1d937, 0x60}, //highlight A split //66210
	{0x1d938, 0x60}, //middlelight A split
	{0x1d939, 0x60}, //lowlight A split	

};


const struct isp_reg_t isp_init_regs_ov8850_samsung[] = {
	/* AEC */ 
	{0x1c146, 0x30},//ori0x30 low AE target,should close
	{0x1c14a, 0x03},
	{0x1c14b, 0x0a},
	{0x1c14c, 0x0a},//aec fast step//
	{0x1c14e, 0x08},//slow step//08
	{0x1c140, 0x01},//banding
	{0x1c13f, 0x02},
	{0x1c164, 0x14},//60Hz banding step
	{0x1c165, 0xa0},
	{0x1c166, 0x18},//50Hz banding step
	{0x1c167, 0xd0},
	{0x1c176, 0x05},//VTS
	{0x1c177, 0x28},	
	{0x1c150, 0x00},//max gain
	{0x1c151, 0x80},
	{0x1c154, 0x00},//min gain
	{0x1c155, 0x10},
	{0x1c158, 0x52},//max exposure
	{0x1c159, 0x20},
	{0x1c15c, 0x00},//min expousre
	{0x1c15d, 0x20},
	{0x1c13e, 0x02},//real gain mode for ov8850
	
	{0x66401, 0x00},//window weight
	{0x66402, 0x20},//StatWin_Left
	{0x66403, 0x00},
	{0x66404, 0x20},//StatWin_Top
	{0x66405, 0x00},
	{0x66406, 0x20},//StatWin_Right
	{0x66407, 0x00},
	{0x66408, 0x28},//StatWin_Bottom
	{0x66409, 0x00},//definiton ofthe center 3x3 window
	{0x6640a, 0xc8},//nWin_Left
	{0x6640d, 0x00},
	{0x6640e, 0x96},//nWin_Top
	{0x66411, 0x04},
	{0x66412, 0xb0},//nWin_Width
	{0x66415, 0x03},
	{0x66416, 0x84},//nWin_Height
	{0x6642e, 0x01},//nWin_Weight_0 weight pass
	{0x6642f, 0x01},//nWin_Weight_1
	{0x66430, 0x01},//nWin_Weight_2
	{0x66431, 0x01},//nWin_Weight_3
	{0x66432, 0x02},//nWin_Weight_4
	{0x66433, 0x02},//nWin_Weight_5
	{0x66434, 0x02},//nWin_Weight_6
	{0x66435, 0x02},//nWin_Weight_7
	{0x66436, 0x04},//nWin_Weight_8
	{0x66437, 0x02},//nWin_Weight_9
	{0x66438, 0x02},//nWin_Weight_10
	{0x66439, 0x02},//nWin_Weight_11
	{0x6643a, 0x02},//nWin_Weight_12
	{0x6644e, 0x03},//nWin_Weight_Shift
	{0x6644f, 0x04},//black level
	{0x66450, 0xf8},//saturate level
	{0x6645b, 0x1a},//black weight1
	{0x6645d, 0x1a},//black weight2
	{0x66460, 0x04},//saturate per1
	{0x66464, 0x0a},//saturate per2
	{0x66467, 0x14},//saturate weight1
	{0x66469, 0x14},//saturate weight2
	//auto AE control
	
/* Raw Stretch */
	{0x65020, 0x01},//RAW Stretch Target
	{0x66500, 0x28},
	{0x66501, 0x00},
	{0x66502, 0xff},
	{0x66503, 0x0f},
	{0x1c1b0, 0xff},
	{0x1c1b1, 0xff},
	{0x1c1b2, 0x01},
	{0x65905, 0x08},
	{0x66301, 0x02},//high level step
	{0x66302, 0xd0},//ref bin
	{0x66303, 0x0a},//PsPer0
	{0x66304, 0x10},//PsPer1
	{0x1c5a4, 0x01},//use new high stretch
	{0x1c5a5, 0x20},//stretch low step
	{0x1c5a6, 0x20},//stretch high step
	{0x1c5a7, 0x08},//stretch slow range
	{0x1c5a8, 0x02},//stretch slow step
	{0x1c1b8, 0x10},//ratio scale
	
	{0x1c5a0, 0x4c},//AE target high
	{0x1c5a2, 0x04},//target stable range
	{0x1c5a3, 0x06},//stretch target slow range
/* De-noise */	
        {0x65604, 0x00},//Richard for new curve 0314
	{0x65605, 0x00},//Richard for new curve 0314
	{0x65606, 0x00},//Richard for new curve 0314
	{0x65607, 0x00},//Richard for new curve 0314

	{0x65510, 0x0f},//G dns slope change from 0x4 to 0xf Richard 0320
	{0x6551a, 0x00},//Raw G Dns, Richard 0320
	{0x6551b, 0x00},//Richard for new curve 0320
	{0x6551c, 0x04},//Richard for new curve 0320
	{0x6551d, 0x05},//Richard for new curve 0320
	{0x6551e, 0x05},//Richard for new curve 0320
	{0x6551f, 0x16},//Richard for new curve 0314
	{0x65520, 0x16},//Richard for new curve 0314
	{0x65522, 0x00},//RAW BR De-noise
	{0x65523, 0x00},
	{0x65524, 0x00},
	{0x65525, 0x03},
	{0x65526, 0x00},
	{0x65527, 0x08},
	{0x65528, 0x00},
	{0x65529, 0x10},
	{0x6552a, 0x00},
	{0x6552b, 0x20},
	{0x6552c, 0x00},
	{0x6552d, 0x20},
	{0x6552e, 0x00},
	{0x6552f, 0x20},
	
	{0x65c00, 0x03},//UV De-noise
	{0x65c01, 0x05},
	{0x65c02, 0x08},
	{0x65c03, 0x1f},
	{0x65c04, 0x1f},
	{0x65c05, 0x1f},
	

/* sharpeness */   
	{0x65600, 0x00},
	{0x65601, 0x10},//0319
	{0x65602, 0x00},
	{0x65603, 0x60},
	{0x65608, 0x06},
	{0x65609, 0x20},
	{0x6560c, 0x00},
	{0x6560d, 0x30}, //low gain sharpness, 20120814 0x20->0x30
	{0x6560e, 0x10},//MinSharpenTp
	{0x6560f, 0x60},//MaxSharpenTp
	{0x65610, 0x10},//MinSharpenTm
	{0x65611, 0x60},//MaxSharpenTm
	{0x65613, 0x10},//SharpenAlpha
	{0x65615, 0x08},//HFreq_thre
	{0x65617, 0x06},//HFreq_coef	

/* auto uv saturation */
	{0x1c4e8, 0x01},//Enable
	{0x1c4e9, 0x40},
	{0x1c4ea, 0x78},
	{0x1c4eb, 0x80}, //keep back for new cmx 0310
	{0x1c4ec, 0x68}, //keep back for new cmx 0310
	

/* Global Gamma */
	{0x1c49b, 0x01},
	{0x1c49c, 0x02},
	{0x1c49d, 0x01}, //gamma 2.0 0310
	{0x1c49e, 0x02},
	{0x1c49f, 0x01}, //gamma 2.0 0310
	{0x1c4a0, 0x00},
	{0x1c4a1, 0x18},
	{0x1c4a2, 0x00},
	{0x1c4a3, 0x88}, //gamma 2.0 0310 //avoid false contour Richard@0323
	
/* BLC */
	{0x1c58b, 0x40},//avoid false contour Richard@0323
	{0x1c58c, 0x40},//avoid false contour Richard@0323	

/* Tone Mapping */
	//contrast curve change for skin over exposure 20120728
	{0x1C4C0, 0x1a},
	{0x1C4C1, 0x29},
	{0x1C4C2, 0x35},
	{0x1C4C3, 0x41},
	{0x1C4C4, 0x4d},
	{0x1C4C5, 0x58},
	{0x1C4C6, 0x64},
	{0x1C4C7, 0x70},
	{0x1C4C8, 0x7c},
	{0x1C4C9, 0x89},
	{0x1C4CA, 0x96},
	{0x1C4CB, 0xa4},
	{0x1C4CC, 0xb5},
	{0x1C4CD, 0xc9},
	{0x1C4CE, 0xe2},
	{0x1c4d4, 0x20},//EDR scale
	{0x1c4d5, 0x20},//EDR scale
	{0x1c4cf, 0x80},
	{0x65a00, 0x1b},
	{0x65a01, 0xc0},

	//dark boost
	{0x1c4b0, 0x02},
	{0x1c4b1, 0x80},
	
	//curve gain control
	{0x1c1b3, 0x30}, //Gain thre1
	{0x1c1b4, 0x70},	//Gain thre2 
	{0x1c1b5, 0x01}, //EDR gain control
	{0x1c1b6, 0x01}, //Curve Gain control
	{0x1c1b7, 0x40}, //after gamma cut ratio
		
	//Manual UV curve 22
	{0x1C998, 0x01},
	{0x1C999, 0x00},
	{0x1C99A, 0x01},
	{0x1C99B, 0x00},
	{0x1C99C, 0x01},
	{0x1C99D, 0x00},
	{0x1C99E, 0x01},
	{0x1C99F, 0x00},
	{0x1C9A0, 0x01},
	{0x1C9A1, 0x00},
	{0x1C9A2, 0x01},
	{0x1C9A3, 0x00},
	{0x1C9A4, 0x01},
	{0x1C9A5, 0x00},
	{0x1C9A6, 0x01},
	{0x1C9A7, 0x00},
	{0x1C9A8, 0x01},
	{0x1C9A9, 0x00},
	{0x1C9AA, 0x01},
	{0x1C9AB, 0x00},
	{0x1C9AC, 0x01},
	{0x1C9AD, 0x00},
	{0x1C9AE, 0x01},
	{0x1C9AF, 0x00},
	{0x1C9B0, 0x01},
	{0x1C9B1, 0x00},
	{0x1C9B2, 0x01},
	{0x1C9B3, 0x00},
	{0x1C9B4, 0x01},
	{0x1C9B5, 0x00},
	{0x1C9B6, 0x01},
	{0x1C9B7, 0x00},
                
/* LENC */      
	{0x1c247, 0x00},//one profile
	{0x1c24c, 0x00},
	{0x1c24d, 0x40},
	{0x1c24e, 0x00},
	{0x1c24f, 0x80},
	{0x1c248, 0x40},
	{0x1c24a, 0x20},
	{0x1c574, 0x00},
	{0x1c575, 0x20},
	{0x1c576, 0x00},
	{0x1c577, 0xf0},
	{0x1c578, 0x40},

	{0x65200, 0x0d},
	{0x65206, 0x3c},
	{0x65207, 0x04},
	{0x65208, 0x3c}, //new shading params revised 20120816
	{0x65209, 0x04},
	{0x6520a, 0x33},
	{0x6520b, 0x0c},
	{0x65214, 0x28},
	{0x65216, 0x20},
	
	{0x1d93d, 0x08},
	{0x1d93e, 0x00},
	{0x1d93f, 0x40},

	{0x1d940, 0xfc},
	{0x1d942, 0x04},
	{0x1d941, 0xfc},
	{0x1d943, 0x04},

	{0x1d944, 0x00},
	{0x1d946, 0x00},
	{0x1d945, 0xfc},
	{0x1d947, 0x04},
	/* OVISP LENC setting for DAY light Long Exposure (HDR/3D) */
	{0x1c264,0x08},
	{0x1c265,0x06},
	{0x1c266,0x06},
	{0x1c267,0x06},
	{0x1c268,0x06},
	{0x1c269,0x08},
	{0x1c26a,0x05},
	{0x1c26b,0x04},
	{0x1c26c,0x03},
	{0x1c26d,0x03},
	{0x1c26e,0x04},
	{0x1c26f,0x05},
	{0x1c270,0x04},
	{0x1c271,0x02},
	{0x1c272,0x00},
	{0x1c273,0x00},
	{0x1c274,0x02},
	{0x1c275,0x04},
	{0x1c276,0x04},
	{0x1c277,0x02},
	{0x1c278,0x00},
	{0x1c279,0x00},
	{0x1c27a,0x01},
	{0x1c27b,0x04},
	{0x1c27c,0x05},
	{0x1c27d,0x04},
	{0x1c27e,0x03},
	{0x1c27f,0x03},
	{0x1c280,0x04},
	{0x1c281,0x05},
	{0x1c282,0x08},
	{0x1c283,0x06},
	{0x1c284,0x06},
	{0x1c285,0x06},
	{0x1c286,0x06},
	{0x1c287,0x08},
	        
	{0x1c288,0x20},
	{0x1c289,0x1f},
	{0x1c28a,0x1f},
	{0x1c28b,0x1f},
	{0x1c28c,0x20},
	{0x1c28d,0x20},
	{0x1c28e,0x20},
	{0x1c28f,0x20},
	{0x1c290,0x20},
	{0x1c291,0x1f},
	{0x1c292,0x1f},
	{0x1c293,0x20},
	{0x1c294,0x20},
	{0x1c295,0x20},
	{0x1c296,0x1f},
	{0x1c297,0x20},
	{0x1c298,0x20},
	{0x1c299,0x20},
	{0x1c29a,0x20},
	{0x1c29b,0x20},
	{0x1c29c,0x20},
	{0x1c29d,0x1f},
	{0x1c29e,0x1f},
	{0x1c29f,0x20},
	{0x1c2a0,0x20},
	
	{0x1c2a1,0x22},
	{0x1c2a2,0x23},
	{0x1c2a3,0x24},
	{0x1c2a4,0x23},
	{0x1c2a5,0x22},
	{0x1c2a6,0x23},
	{0x1c2a7,0x23},
	{0x1c2a8,0x22},
	{0x1c2a9,0x23},
	{0x1c2aa,0x23},
	{0x1c2ab,0x23},
	{0x1c2ac,0x21},
	{0x1c2ad,0x1f},
	{0x1c2ae,0x21},
	{0x1c2af,0x23},
	{0x1c2b0,0x23},
	{0x1c2b1,0x23},
	{0x1c2b2,0x22},
	{0x1c2b3,0x23},
	{0x1c2b4,0x23},
	{0x1c2b5,0x22},
	{0x1c2b6,0x23},
	{0x1c2b7,0x24},
	{0x1c2b8,0x23},
	{0x1c2b9,0x22},

/* AWB */
	{0x66201, 0x52},
	{0x66203, 0x14},//crop window
	{0x66211, 0xe8},//awb top limit
	{0x66212, 0x04},//awb bottom limit	
	
	{0x1c17c, 0x01},//CT mode, should close
	{0x1c182, 0x04},
	{0x1c183, 0x00},//MinNum
	{0x1c184, 0x04},//AWB Step		
	{0x1c58d, 0x00},//LimitAWBAtD65Enable
	
	{0x1c1be, 0x00},//AWB offset
	{0x1c1bf, 0x00},
	{0x1c1c0, 0x00},
	{0x1c1c1, 0x00},

	{0x1c1aa, 0x01},//avgAllEnable	
	{0x1c1ad, 0x02},//weight of A
	{0x1c1ae, 0x10},//weight of D65
	{0x1c1af, 0x04},//weight of CWF
	              
	{0x1c5ac, 0x80},//pre-bgain, apply on CCM
	{0x1c5ad, 0x80},//pre-ggain
	{0x1c5ae, 0x80},//pre-rgain

	{0x1ccce, 0x02},//awb shift	
	{0x1cccf, 0xf8},//B gain for A
	{0x1ccd0, 0x18},//R gain for A
	{0x1c5b8, 0x10},//B gain for C outdoor
	{0x1c5b9, 0x08},//R gain for C outdoor
	{0x1ccd1, 0x18},
	{0x1ccd2, 0x14},//R gain for C indoor
	{0x1ccd3, 0x1c},
	{0x1ccd4, 0x10},//R gain for D indoor
	{0x1cccc, 0x10},//B gain for D outdoor
	{0x1cccd, 0x00},//R gain for D outdoor
	
	{0x1c5b4, 0x02},//C indoor/outdoor switch lum 1 Richard@0517
	{0x1c5b5, 0xff},//C indoor/outdoor switch lum 1 Richard@0517
	{0x1c5b6, 0x04},//C indoor/outdoor switch lum 2 Richard@0517
	{0x1c5b7, 0xff},//C indoor/outdoor switch lum 2 Richard@0517
		
	{0x1ccd5, 0x35},//CT_A
	{0x1ccd6, 0x60},//CT_C
	{0x1ccd7, 0xab},//CT_D

	{0x1c5cd, 0x01},//high light awb shift, modified by Jiangtao to avoid blurish when high CT 0310
	{0x1c5ce, 0x00},//nAWBBrTh0 
	{0x1c5cf, 0xf0},
	{0x1c5d0, 0x01},//nAWBBrTh1
	{0x1c5d1, 0x20},
	{0x1c5d2, 0x03},//nBrD65Th
	{0x1c5d3, 0x00},
	{0x1c5d4, 0x40},//nAWBBrShiftCT0 
	{0x1c5d5, 0x90},//nAWBBrShiftCT1
	{0x1c5d6, 0xa2},//nAWBBrCTd65[2] 
	{0x1c5d7, 0xe2},//nAWBBrCTd65[2] 
	{0x1c5d8, 0x40},//nAWBMaxBrShift 
	{0x1c1c2, 0x00},
	{0x1c1c3, 0x20},
	
	{0x66206, 0x11},  //center(cwf) window threshold D0
	{0x66207, 0x14},  //A threshold, range DX  0x15    
	{0x66208, 0x12},  //day threshold, range DY 0xd    
	{0x66209, 0x78},  //CWF X                          
	{0x6620a, 0x62},  //CWF Y                          
	{0x6620b, 0xda},  //K_A_X2Y, a slop                
	{0x6620c, 0xb9},  //K_D65_Y2X, d slop              
	{0x6620d, 0x50},  //D65 Limit                      
	{0x6620e, 0x35},  //A Limit                        
	{0x6620f, 0x6b},  //D65 split                      
	{0x66210, 0x55},  //A split                        
	{0x66201, 0x52},                                   
	              
	{0x1c1c8, 0x01},  //center CT, CWF 
	{0x1c1c9, 0x53},                   
	{0x1c1cc, 0x00},  //d65 min D      
	{0x1c1cd, 0xbd},                   
	{0x1c1d0, 0x02},  //A              
	{0x1c1d1, 0x5d},  
	{0x1c254, 0x00},
	{0x1c255, 0xca},
	{0x1c256, 0x00},
	{0x1c257, 0xe4},
	{0x1c258, 0x01},
	{0x1c259, 0x65},
	{0x1c25a, 0x01},
	{0x1c25b, 0xca},
	

/* Color matrix */
	{0x1C1d8, 0x02},//center matrix,     
	{0x1C1d9, 0x59},                     
	{0x1C1da, 0xfe},                     
	{0x1C1db, 0xa1},                     
	{0x1C1dc, 0x00},                     
	{0x1C1dd, 0x06},                     
	                                    
	{0x1C1de, 0x00},                     
	{0x1C1df, 0x01},                     
	{0x1C1e0, 0x01},                     
	{0x1C1e1, 0x49},                     
	{0x1C1e2, 0xff},                     
	{0x1C1e3, 0xb6},                     
	                                    
	{0x1C1e4, 0x00},                     
	{0x1C1e5, 0x23},                     
	{0x1C1e6, 0xfe},                     
	{0x1C1e7, 0xe4},                     
	{0x1C1e8, 0x01},                     
	{0x1C1e9, 0xf9},		     
	                                     
	{0x1C1FC, 0xff},//cmx left delt
	{0x1C1FD, 0xad},                      
	{0x1C1FE, 0x00},                      
	{0x1C1FF, 0x43},                      
	{0x1C200, 0x00},                      
	{0x1C201, 0x10},                      
	                                     
	{0x1C202, 0xff},                      
	{0x1C203, 0xb6},                      
	{0x1C204, 0x00},                      
	{0x1C205, 0x15},                      
	{0x1C206, 0x00},                      
	{0x1C207, 0x35},                      
	                                     
	{0x1C208, 0xff},                      
	{0x1C209, 0xe8},                      
	{0x1C20A, 0x00},                      
	{0x1C20B, 0x4f},                      
	{0x1C20C, 0xff},                      
	{0x1C20D, 0xc9},                      
	
	{0x1C220, 0x00},//cmx right delta     
	{0x1C221, 0xbf},                      
	{0x1C222, 0xff},                      
	{0x1C223, 0x70},                      
	{0x1C224, 0xff},                      
	{0x1C225, 0xd1},                      
	                                     
	{0x1C226, 0xff},	                     
	{0x1C227, 0xe4},                      
	{0x1C228, 0x00},                      
	{0x1C229, 0x26},                      
	{0x1C22A, 0xff},                      
	{0x1C22B, 0xf6},                      
	                                     
	{0x1C22C, 0xff},                      
	{0x1C22D, 0xce},                      
	{0x1C22E, 0x00},                      
	{0x1C22F, 0xc6},                      
	{0x1C230, 0xff},                      
	{0x1C231, 0x6c},                      

	/* dpc */
	{0x65409, 0x04},
	{0x6540a, 0x02},
	{0x6540b, 0x01},
	{0x6540c, 0x01},
	{0x6540d, 0x04},
	{0x6540e, 0x02},
	{0x6540f, 0x01},
	{0x65410, 0x01},
	{0x65408, 0x0b},


	//high gain curve
	{0x1d963, 0x1c},
	{0x1d964, 0x2d},
	{0x1d965, 0x3b},
	{0x1d966, 0x48},
	{0x1d967, 0x55},
	{0x1d968, 0x60},
	{0x1d969, 0x6b},
	{0x1d96a, 0x77},
	{0x1d96b, 0x83},
	{0x1d96c, 0x8f},
	{0x1d96d, 0x9b},
	{0x1d96e, 0xa7},
	{0x1d96f, 0xb7},
	{0x1d970, 0xc9},
	{0x1d971, 0xe2},           
	{0x1d8fe, 0x01}, //UV cut gain control
	{0x1d8ff, 0x50}, //low gain thres
	{0x1d900, 0x70}, //high gain thres
	{0x1d97f, 0x14}, //UV cut low bright thres
	{0x1d973, 0x20}, //UV cut high bright thres
	{0x1d972, 0x01}, //adaptive gamma enable
	{0x1d974, 0x01}, //low gain gamma
	{0x1d975, 0xe6},                
	{0x1d976, 0x01}, //high gain gamma
	{0x1d977, 0xc0},
	{0x1d978, 0x01}, //dark image gamma
	{0x1d979, 0xb3},
	{0x1d97a, 0x88}, //low gain slope
	{0x1d97b, 0x50}, //high gain slope
	{0x1d97c, 0x38}, //dark image slope
	{0x1d97d, 0x14}, //low bright thres
	{0x1d97e, 0x20}, //high bright thres
	
	{0x1d99e, 0x01}, //dynamic UV curve
	//low gain UV curve 1/2
	{0x1d904, 0x8b},
	{0x1d905, 0x95},
	{0x1d906, 0x98},
	{0x1d907, 0x98},
	{0x1d908, 0x98},
	{0x1d909, 0x98},
	{0x1d90a, 0x98},
	{0x1d90b, 0x98},
	{0x1d90c, 0x98},
	{0x1d90d, 0x98},
	{0x1d90e, 0x98},
	{0x1d90f, 0x97},
	{0x1d910, 0x94},
	{0x1d911, 0x89},
	{0x1d912, 0x72},
	{0x1d913, 0x55},
	//high gain UV curve 1/2
	{0x1d914, 0x46},
	{0x1d915, 0x70},
	{0x1d916, 0x88},
	{0x1d917, 0x92},
	{0x1d918, 0x96},
	{0x1d919, 0x98},
	{0x1d91a, 0x98},
	{0x1d91b, 0x98},
	{0x1d91c, 0x98},
	{0x1d91d, 0x98},
	{0x1d91e, 0x98},
	{0x1d91f, 0x97},
	{0x1d920, 0x94},
	{0x1d921, 0x89},
	{0x1d922, 0x72},
	{0x1d923, 0x55},
	
	//dynamic CT AWB 
	{0x1d924, 0x01}, //enable
	
	{0x1d950, 0x00}, //Br thres
	{0x1d951, 0x20}, //Br thres
	
	{0x1d8dc, 0x00}, //Br thres0
	{0x1d8dd, 0xf0}, //Br thres0
	               
	{0x1d8de, 0x44}, //Br thres1
	{0x1d8df, 0x34}, //Br thres1
		
	{0x1d952, 0x30}, //Br Ratio
	{0x1d8da, 0x10}, //Br Ratio0
	{0x1d8db, 0x06}, //Br Ratio1
	
	{0x1d949, 0x0c}, //super highlight cwf thres //66206
	{0x1d94c, 0x57}, //super highlight D limit //6620d
	{0x1d94a, 0x11}, //super highlight A thres //66207
	{0x1d94d, 0x48}, //super highlight A limit //6620e
	{0x1d94b, 0x14}, //super highlight D thres //66208
	{0x1d94e, 0x6e}, //super highlight D split //6620f
	{0x1d94f, 0x60},	//super highlight A split //66210
	
	{0x1d925, 0x0c}, //highlight cwf thres //66206
	{0x1d928, 0x11}, //highlight A thres //66207
	{0x1d92b, 0x14}, //highlight D thres //66208
	{0x1d92e, 0x4d}, //highlight D limit //6620d
	{0x1d931, 0x48}, //highlight A limit //6620e
	{0x1d934, 0x6e}, //highlight D split //6620f
	{0x1d937, 0x60}, //highlight A split //66210
	
	{0x1d926, 0x13}, //middlelight cwf thres
	{0x1d929, 0x18}, //middlelight A thres
	{0x1d92c, 0x14}, //middlelight D thres
	{0x1d92f, 0x43}, //middlelight D limit
	{0x1d932, 0x36}, //middlelight A limit
	{0x1d935, 0x6e}, //middlelight D split
	{0x1d938, 0x60}, //middlelight A split
	
	{0x1d927, 0x15}, //lowlight cwf thres
	{0x1d92a, 0x1d}, //lowlight A thres
	{0x1d92d, 0x1d}, //lowlight D thres	
	{0x1d930, 0x40}, //lowlight D limit		
	{0x1d933, 0x32}, //lowlight A limit		
	{0x1d936, 0x6e}, //lowlight D split
	{0x1d939, 0x60}, //lowlight A split		

};

static u16 ov8850_vcm_start = 0;
static u16 ov8850_vcm_end = 0;
static int ov8850_otp_index = -1;
static u8 factory_id = 0;

/*the framesize should be sorted by size, so must be modified in furture*/
/*new setting is for ov8850, so delete invalid framesizes setting for ov8830*/
static framesize_s ov8850_framesizes[] = {
#if 1
	/* 1600x1200*/
	//{0, 0, 1600, 1200, 3608, 1848, 28, 25, 0x22a, 0x1cd, 0x100, VIEW_FULL, RESOLUTION_4_3, true, false, {ov8850_framesize_1600x1200_new, ARRAY_SIZE(ov8850_framesize_1600x1200_new)} },
	{0, 0, 1600, 1200, 7216, 1228, 5, 1, 0x22a, 0x1cd, 0x100, VIEW_FULL, RESOLUTION_4_3, true, false, {ov8850_framesize_1600x1200_new, ARRAY_SIZE(ov8850_framesize_1600x1200_new)} },
	/* 1632x1224, just close with quarter size */
	//{0, 0, 1632, 1224, 3608, 2028, 30, 25, 0x246, 0x1e5, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false, {ov8850_framesize_1632x1224, ARRAY_SIZE(ov8850_framesize_1632x1224)} },
	/* 3264x2448 */
	//{0, 0, 3264, 2448, 3788, 2637, 15, 13, 0x18b, 0x149, 0x16d, VIEW_FULL, RESOLUTION_4_3, false, false, {ov8850_framesize_3264x2448_new, ARRAY_SIZE(ov8850_framesize_3264x2448_new)} },
	{0, 0, 3264, 2448, 3788, 5278, 1, 1, 0x18b, 0x149, 0x16d, VIEW_FULL, RESOLUTION_4_3, false, false, {ov8850_framesize_3264x2448_new, ARRAY_SIZE(ov8850_framesize_3264x2448_new)} },
#else
	#ifndef READ_BACK_RAW
	/* 1600x1200, just close with quarter size */
	{0, 0, 1600, 1200, 3608, 1956, 30, 25, 0x246, 0x1e5, 0x100, VIEW_FULL, RESOLUTION_4_3, true, false, {ov8850_framesize_1600x1200, ARRAY_SIZE(ov8850_framesize_1600x1200)} },

	/* 1080P, 1920*1088 y36721 0221 change to 24fps */
	{0, 0, 1920, 1088, 3608, 2456, 25, 21, 0x261, 0x1fc, 0x218, VIEW_FULL, RESOLUTION_16_9, false, false, {ov8850_framesize_1080p, ARRAY_SIZE(ov8850_framesize_1080p)} },

	/* 2048x1536 */
	{0, 0, 2048, 1536, 3608, 2456, 25, 21, 0x261, 0x1fc, 0x218, VIEW_FULL, RESOLUTION_4_3, false, false, {ov8850_framesize_2048x1536, ARRAY_SIZE(ov8850_framesize_2048x1536)} },

	/* 1080p eis 2112*1200 */
	{0, 0, 2112, 1200, 3864, 2296, 25, 21, 0x239, 0x1da, 0x1f4, VIEW_FULL, RESOLUTION_16_9, false, false, {ov8850_framesize_1080pEIS, ARRAY_SIZE(ov8850_framesize_1080pEIS)} },

	/* 3264x1836 */
	{0, 0, 3264, 1840, 3788, 2083, 19, 16, 0x18b, 0x149, 0x15c, VIEW_FULL, RESOLUTION_16_9, false, false, {ov8850_framesize_3264x1840, ARRAY_SIZE(ov8850_framesize_3264x1840)} },
	#endif
	/* 8M */
	{0, 0, 3264, 2448, 3788, 2637, 15, 13, 0x18b, 0x149, 0x15c, VIEW_FULL, RESOLUTION_4_3, false, false, {ov8850_framesize_full_15fps, ARRAY_SIZE(ov8850_framesize_full_15fps)} },
#endif
};
static camera_sensor ov8850_sensor;
static vcm_info_s ov8850_vcm;	//sensor_common.c DW9714
static void ov8850_set_default(void);
static void ov8850_get_vcm_otp(u16 *vcm_start, u16 *vcm_end);
bool ov8850_read_otp_vcm(u16 index, u8 *vcm_start, u8 *vcm_end);

/*
 **************************************************************************
 * FunctionName: ov8850_read_reg;
 * Description : read ov8850 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(ov8850_sensor.i2c_config.index, ov8850_sensor.i2c_config.addr,
                reg, (u16*)val,ov8850_sensor.i2c_config.val_bits, ov8850_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov8850_write_reg;
 * Description : write ov8850 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(ov8850_sensor.i2c_config.index, ov8850_sensor.i2c_config.addr,
                reg, val, ov8850_sensor.i2c_config.val_bits, mask, ov8850_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov8850_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ov8850_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(ov8850_sensor.i2c_config.index, ov8850_sensor.i2c_config.addr,
                seq, size, ov8850_sensor.i2c_config.val_bits, mask, ov8850_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov8850_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ov8850_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}

/*
 **************************************************************************
 * FunctionName: ov8850_read_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ov8850_read_isp_seq(struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_read_isp_seq(seq, size);
}

static u32 ov8850_read_isp_reg(u32 reg_addr, u32 size)
{
	struct isp_reg_t reg_seq[4];
	int i = 0;
	u32 reg_value = 0x00;
	print_debug("Enter %s, size=%d", __func__, size);
	/*initialize buffer */
	for (i = 0; i < size; i++) {
		reg_seq[i].subaddr = reg_addr;
		reg_seq[i].value = 0x00;
		reg_seq[i].mask = 0x00;
		reg_addr++;
	}
	/*read register of isp for ov8850 */
	ov8850_read_isp_seq(reg_seq, size);
	/*construct return value */
	do {
		i--;
		reg_value = reg_value << 8;
		reg_value |= reg_seq[i].value;
		print_debug("reg_seq[%d].value:%x", i, reg_seq[i].value);
	} while (i > 0);
	return reg_value;
}

static void ov8850_write_isp_reg(u32 reg_addr, u32 data, u32 size)
{
	struct isp_reg_t reg_seq[4];
	int i = 0;
	print_debug("Enter %s, size=%d", __func__, size);
	print_debug("data:%x", data);
	/*initialize buffer */
	for (i = 0; i < size; i++) {
		reg_seq[i].subaddr = reg_addr;
		reg_seq[i].value = data & 0xFF;
		reg_seq[i].mask = 0x00;
		reg_addr++;
		data = data >> 8;
		print_debug("reg_seq[%d].subaddr:%x", i, reg_seq[i].subaddr);
		print_debug("reg_seq[%d].value:%x", i, reg_seq[i].value);
	}
	/*write register of isp for ov8850 */
	ov8850_write_isp_seq(reg_seq, size);
}
/*
 **************************************************************************
 * FunctionName: ov8850_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_enum_frame_intervals(struct v4l2_frmivalenum *fi)
{
	assert(fi);

	print_debug("enter %s", __func__);
	if (fi->index > CAMERA_MAX_FRAMERATE) {
		return -EINVAL;
	}

	fi->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fi->discrete.numerator = 1;
	/* y36721:if denominator=0, means sensor support auto frame rate control. */
	fi->discrete.denominator = fi->index;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov8850_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY) {
		fmt->pixelformat = ov8850_sensor.fmt[STATE_PREVIEW];
	} else {
		fmt->pixelformat = ov8850_sensor.fmt[STATE_CAPTURE];
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov8850_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;
	u32 this_max_index = ARRAY_SIZE(ov8850_framesizes) - 1;

	assert(framesizes);

	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > ov8850_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > ov8850_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = ov8850_framesizes[this_max_index].width;
	framesizes->discrete.height = ov8850_framesizes[this_max_index].height;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov8850_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = ARRAY_SIZE(ov8850_framesizes) - 1;

	assert(framesizes);

	print_debug("Enter Function:%s  ", __func__);

	if ((framesizes->discrete.width <= ov8850_framesizes[max_index].width)
	    && (framesizes->discrete.height <= ov8850_framesizes[max_index].height)) {
		print_debug("===========width = %d", framesizes->discrete.width);
		print_debug("===========height = %d", framesizes->discrete.height);
		return 0;
	}

	print_error("frame size too large, [%d,%d]",
		    framesizes->discrete.width, framesizes->discrete.height);
	return -EINVAL;
}

/*
 **************************************************************************
 * FunctionName: ov8850_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_set_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type)
{
	int i = 0;
	bool match = false;

	assert(fs);

	print_debug("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
		    __func__, state, flag, fs->width, fs->height);

	if (VIEW_FULL == view_type) {
		for (i = 0; i < ARRAY_SIZE(ov8850_framesizes); i++) {
			if ((ov8850_framesizes[i].width >= fs->width)
			    && (ov8850_framesizes[i].height >= fs->height)
			    && (VIEW_FULL == ov8850_framesizes[i].view_type)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= ov8850_framesizes[i].resolution_type)) {
				fs->width = ov8850_framesizes[i].width;
				fs->height = ov8850_framesizes[i].height;
				match = true;
				break;
			}
		}
	}

	if (false == match) {
		for (i = 0; i < ARRAY_SIZE(ov8850_framesizes); i++) {
			if ((ov8850_framesizes[i].width >= fs->width)
			    && (ov8850_framesizes[i].height >= fs->height)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= ov8850_framesizes[i].resolution_type)) {
				fs->width = ov8850_framesizes[i].width;
				fs->height = ov8850_framesizes[i].height;
				break;
			}
		}
	}

	if (i >= ARRAY_SIZE(ov8850_framesizes)) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}
	if (state == STATE_PREVIEW) {
		ov8850_sensor.preview_frmsize_index = i;
	} else {
		ov8850_sensor.capture_frmsize_index = i;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov8850_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_get_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;

	assert(fs);

	if (state == STATE_PREVIEW) {
		frmsize_index = ov8850_sensor.preview_frmsize_index;
	} else if (state == STATE_CAPTURE) {
		frmsize_index = ov8850_sensor.capture_frmsize_index;
	} else {
		return -EINVAL;
	}
	fs->width = ov8850_framesizes[frmsize_index].width;
	fs->height = ov8850_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov8850_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_init_reg(void)
{
	int size = 0, i;
	print_debug("Enter Function:%s  , initsize=%d",
		    __func__, sizeof(ov8850_init_regs_new));

	if (0 != k3_ispio_init_csi(ov8850_sensor.mipi_index,
				 ov8850_sensor.mipi_lane_count, ov8850_sensor.lane_clk)) {
		return -EFAULT;
	}

	ov8850_write_reg(0x0100, 0x00, 0x00);
	ov8850_write_reg(0x0103, 0x01, 0x00);
	msleep(5);
	size = ARRAY_SIZE(ov8850_init_regs_new);
	if (0 != ov8850_write_seq(ov8850_init_regs_new, size, 0x00)) {
		print_error("fail to init ov8850 sensor");
		return -EFAULT;
	}

	/*make sure sensor stream on before OTP read/write*/
	ov8850_write_reg(0x0100, 0x01, 0x00);
	if (ov8850_otp_index != -1) {
		ov8850_update_otp_wb(ov8850_otp_index);
		ov8850_update_otp_lenc(ov8850_otp_index);
	} else {
		print_info("Failed to read ov8850 sensor otp!");
	}
	ov8850_update_blc();
	ov8850_write_reg(0x0100, 0x00, 0x00);
	return 0;
}
static int ov8850_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(ov8850_cap) / sizeof(ov8850_cap[0]); ++i) {
		if (id == ov8850_cap[i].id) {
			*value = ov8850_cap[i].value;
			break;
		}
	}
	return 0;
}

static int ov8850_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	ov8850_sensor.hflip = flip;
	return 0;
}
static int ov8850_get_hflip(void)
{
	print_debug("enter %s", __func__);

	return ov8850_sensor.hflip;
}
static int ov8850_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);

	ov8850_sensor.vflip = flip;

	return 0;
}
static int ov8850_get_vflip(void)
{
	print_debug("enter %s", __func__);
	return ov8850_sensor.vflip;
}
static int ov8850_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((ov8850_sensor.vflip << 1) | ov8850_sensor.hflip);
    int flip_type = E_CAMERA_SENSOR_FLIP_TYPE_NONE;
	
	print_debug("Enter %s  ", __func__);
	if(OV8850_FOXCONN_FACTORY_ID == factory_id)
	{
		flip_type = E_CAMERA_SENSOR_FLIP_TYPE_H;
	}
	k3_ispio_update_flip((ov8850_sensor.old_flip ^ new_flip) & 0x03, width, height, PIXEL_ORDER_NO_CHANGED);

	ov8850_sensor.old_flip = new_flip;
	print_debug("%s:flip_type = %d, new_flip = %d", __func__, flip_type, new_flip);

    switch (flip_type) {
	case E_CAMERA_SENSOR_FLIP_TYPE_NONE:
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT1, ov8850_sensor.vflip ? 0x42 : 0x00, ~0x42);
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT2, ov8850_sensor.hflip ? 0x06 : 0x00, ~0x06);
		break;
	case E_CAMERA_SENSOR_FLIP_TYPE_H_V:
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT1, ov8850_sensor.vflip ? 0x00 : 0x42, ~0x42);
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT2, ov8850_sensor.hflip ? 0x00 : 0x06, ~0x06);
		break;
    case E_CAMERA_SENSOR_FLIP_TYPE_H:
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT1, ov8850_sensor.vflip ? 0x42 : 0x00, ~0x42);
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT2, ov8850_sensor.hflip ? 0x00 : 0x06, ~0x06);
		break;
    case E_CAMERA_SENSOR_FLIP_TYPE_V:
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT1, ov8850_sensor.vflip ? 0x00 : 0x42, ~0x42);
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT2, ov8850_sensor.hflip ? 0x06 : 0x00, ~0x06);
		break;
	default:
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT1, ov8850_sensor.vflip ? 0x42 : 0x00, ~0x42);
    	ov8850_write_reg(OV8850REG_TIMING_FORMAT2, ov8850_sensor.hflip ? 0x06 : 0x00, ~0x06);
		break;
	}

	return 0;
}
void ov8850_set_vts(u16 vts)
{
	print_debug("Enter %s  ", __func__);
	ov8850_write_reg(OV8850_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	ov8850_write_reg(OV8850_VTS_REG_L, vts & 0xff, 0x00);
}

/*
 **************************************************************************
 * FunctionName: ov8850_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_framesize_switch(camera_state state)
{
	u8 next_frmsize_index;
	u16 vts;

	if (state == STATE_PREVIEW)
		next_frmsize_index = ov8850_sensor.preview_frmsize_index;
	else
		next_frmsize_index = ov8850_sensor.capture_frmsize_index;

	print_info("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

	if (next_frmsize_index >= ARRAY_SIZE(ov8850_framesizes)){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -ETIME;
	}

	if (0 != ov8850_write_seq(ov8850_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		,ov8850_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init ov8850 sensor");
		return -ETIME;
	}
	msleep(3);

	/* use auto fps level at coolboot */
	vts = ov8850_sensor.frmsize_list[next_frmsize_index].vts *
		ov8850_sensor.frmsize_list[next_frmsize_index].fps / ov8850_sensor.fps;
	ov8850_set_vts(vts);
	ov8850_update_flip(ov8850_framesizes[next_frmsize_index].width,
			   ov8850_framesizes[next_frmsize_index].height);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov8850_stream_on;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_stream_on(camera_state state)
{
	print_debug("Enter Function:%s ", __func__);
	return ov8850_framesize_switch(state);
}

static u16 ov8850_i2c_addr[] = {
	OV8850_SLAVE_ADDRESS_20,
	OV8850_SLAVE_ADDRESS_6C,
};
static awb_gain_t ov8850_flash_awb[FLASH_PLATFORM_MAX][OV8850_MODULE_MAX] = {
	/* u9510 */
	{
		{0xcd, 0x80, 0x80, 0xf5}, /* SAMSUNG */
		{0xc8, 0x80, 0x80, 0x104}, /* FOXCONN and others */
	},

	/* 9510E: U9510E/T9510E */
	{
		{0xdc, 0x80, 0x80, 0xf5}, /* SAMSUNG */
		{0xd6, 0x80, 0x80, 0x104}, /* FOXCONN and others */
	},

	/* s10 */
	{
		{0xd5, 0x80, 0x80, 0xf6}, /* SAMSUNG */
		{0xd0, 0x80, 0x80, 0x100}, /* FOXCONN and others */
	},
	//G710 just use this setting so far, and will be update in furture
	/* D2 */
	{
		{0xd5, 0x80, 0x80, 0xf6}, /* SAMSUNG */
		{0xd0, 0x80, 0x80, 0x100}, /* FOXCONN and others */
	},
};
static void ov8850_get_flash_awb(flash_platform_t type, awb_gain_t *flash_awb)
{
	if (factory_id == OV8850_SAMSUNG_FACTORY_ID) {
		*flash_awb = ov8850_flash_awb[type][OV8850_MODULE_SAMSUNG];
	} else {
		*flash_awb = ov8850_flash_awb[type][OV8850_MODULE_FOXCONN];
	}
	print_info("ov8850_flash_awb OV8850_MODULE_FOXCONN:0x%x,0x%x,", type,factory_id);
}

static ccm_gain_t cap_gain[FRAMESIZE_BINNING_MAX] = {{0x80, 0x80, 0x80}, {0x85, 0x80, 0x85}};
static ccm_gain_t preview_gain ={0x80, 0x80, 0x80};

#define OV8850_AE_TH_HIGH	481120 /* 496640 1940 * 0x80 *2, max AE_value in 720P@30fps, binning should x2 */
#define OV8850_AE_TH_LOW	62000 /* 62000 is 4band(1vts)@0x10 gain, binning should x2. */

#define CCM_GAIN_ORI 	0x80
#define R_GAIN_SHIFT	0x85
#define B_GAIN_SHIFT	0x85

#define R_GAIN_MAX	0xd0
#define B_GAIN_MIN	0x60

static void ov8850_awb_dynamic_ccm_gain(u32 frame_index, u32 ae, awb_gain_t  *awb_gain, ccm_gain_t *ccm_gain)
{
	u32 gain_delta;

	u32 ae_value = ae;
	u32 current_rbratio = 0x100;
	bool binning;

	u32 a_light_rbratio = 0x50;
	u32 h_light_rbratio =0x30;

	u32 r_gain_base = CCM_GAIN_ORI;
	u32 b_gain_base = CCM_GAIN_ORI;

	if (frame_index >= ARRAY_SIZE(ov8850_framesizes)) {
		print_error("Unsupport sensor setting index: %d", frame_index);
		return;
	}

	binning = ov8850_framesizes[frame_index].binning;

	if ((awb_gain->b_gain != 0) && (awb_gain->r_gain != 0)) {
		current_rbratio = 0x8000 / (awb_gain->b_gain * 0x100 / awb_gain->r_gain);
	}

	if (binning == true) {
		ae_value *= 2;
		r_gain_base = R_GAIN_SHIFT;
		b_gain_base = B_GAIN_SHIFT;
	}

	/* adjust current ae value */
	ae_value = (ae_value > OV8850_AE_TH_HIGH) ? OV8850_AE_TH_HIGH : ae_value;

	if ((current_rbratio >= a_light_rbratio) || (ae_value < OV8850_AE_TH_LOW)) {
	/* (1) R/B larger than A' light or expo_line*GAIN lower than TH_LOW */
			ccm_gain->r_gain = r_gain_base;
			ccm_gain->b_gain = b_gain_base;
	} else if ((current_rbratio < h_light_rbratio) && (ae_value >= OV8850_AE_TH_LOW)) {
	/* (2)R/B lower than H light and expo_line*GAIN larger than TH_LOW*/
		gain_delta = (ae_value -OV8850_AE_TH_LOW) * (R_GAIN_MAX - r_gain_base) / (OV8850_AE_TH_HIGH - OV8850_AE_TH_LOW);
		ccm_gain->r_gain = gain_delta + r_gain_base;

		gain_delta = (ae_value -OV8850_AE_TH_LOW) * (b_gain_base - B_GAIN_MIN) / (OV8850_AE_TH_HIGH - OV8850_AE_TH_LOW);
		ccm_gain->b_gain = b_gain_base - gain_delta;
 	} else if ((current_rbratio <= a_light_rbratio) && (current_rbratio >= h_light_rbratio)) {
	/* (3)R/B is between A' light and H light*/
		gain_delta = (a_light_rbratio - current_rbratio) * (R_GAIN_MAX -r_gain_base) /(a_light_rbratio -h_light_rbratio);
		ccm_gain->r_gain = gain_delta * (ae_value -OV8850_AE_TH_LOW) / (OV8850_AE_TH_HIGH - OV8850_AE_TH_LOW) + r_gain_base;

		gain_delta = (a_light_rbratio - current_rbratio) * (b_gain_base - B_GAIN_MIN) /(a_light_rbratio -h_light_rbratio);
		ccm_gain->b_gain = b_gain_base - gain_delta * (ae_value -OV8850_AE_TH_LOW) / (OV8850_AE_TH_HIGH - OV8850_AE_TH_LOW);
	} else {
		print_info("NO COVERRING SCENE.\n");
		return;
	}

	//for preview
	preview_gain.r_gain = ccm_gain->r_gain;
	preview_gain.b_gain = ccm_gain->b_gain;

	print_debug("CURRENT SCENE : r_gain = 0x%x, b_gain = 0x%x, current_value = %d\n\n",
		ccm_gain->r_gain, ccm_gain->b_gain, ae_value);

	//for capture
	if (current_rbratio >= a_light_rbratio) {
		cap_gain[FRAMESIZE_NOBINNING].r_gain = CCM_GAIN_ORI;
		cap_gain[FRAMESIZE_NOBINNING].b_gain = CCM_GAIN_ORI;
		cap_gain[FRAMESIZE_BINNING].r_gain = R_GAIN_SHIFT;
		cap_gain[FRAMESIZE_BINNING].b_gain = B_GAIN_SHIFT;
	} else {
		/* check preview size is binning or not. */
		if (binning == true) {
			cap_gain[FRAMESIZE_NOBINNING].r_gain = ccm_gain->r_gain - (R_GAIN_SHIFT - CCM_GAIN_ORI);
			cap_gain[FRAMESIZE_NOBINNING].b_gain = ccm_gain->b_gain - (B_GAIN_SHIFT - CCM_GAIN_ORI);
			cap_gain[FRAMESIZE_BINNING].r_gain = ccm_gain->r_gain;
			cap_gain[FRAMESIZE_BINNING].b_gain = ccm_gain->b_gain;
		} else {
			cap_gain[FRAMESIZE_NOBINNING].r_gain = ccm_gain->r_gain;
			cap_gain[FRAMESIZE_NOBINNING].b_gain = ccm_gain->b_gain;
			cap_gain[FRAMESIZE_BINNING].r_gain = ccm_gain->r_gain + (R_GAIN_SHIFT - CCM_GAIN_ORI);
			cap_gain[FRAMESIZE_BINNING].b_gain = ccm_gain->b_gain + (B_GAIN_SHIFT - CCM_GAIN_ORI);
		}
	}

	print_debug("cap_gain[NOBINNING] = 0x%x, 0x%x; cap_gain[BINNING] = 0x%x, 0x%x\n",
		cap_gain[FRAMESIZE_NOBINNING].r_gain, cap_gain[FRAMESIZE_NOBINNING].b_gain,
		cap_gain[FRAMESIZE_BINNING].r_gain, cap_gain[FRAMESIZE_BINNING].b_gain);
}

static void ov8850_get_ccm_pregain(camera_state state, u32 frame_index, u8 *bgain, u8 *rgain)
{
	bool binning;

	if (state >= STATE_MAX)
		return;

	if (frame_index >= ARRAY_SIZE(ov8850_framesizes)) {
		print_error("Unsupport sensor setting index: %d", frame_index);
		return;
	}

	binning = ov8850_framesizes[frame_index].binning;

	if (state == STATE_PREVIEW) {
		*bgain = preview_gain.b_gain;
		*rgain = preview_gain.r_gain;
	} else if (state == STATE_CAPTURE) {
		/* check capture size is binning or not. */
		if (binning == true) {
			*bgain = cap_gain[FRAMESIZE_BINNING].b_gain;
			*rgain = cap_gain[FRAMESIZE_BINNING].r_gain;
		} else {
			*bgain = cap_gain[FRAMESIZE_NOBINNING].b_gain;
			*rgain = cap_gain[FRAMESIZE_NOBINNING].r_gain;
		}
	} else
		return;
}

/*  **************************************************************************
* FunctionName: ov8850_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int ov8850_check_sensor(void)
{
	u8 regl = 0;
	u8 regh = 0;
	u16 id = 0;
	int size;
	int i;

	ov8850_read_reg(0x300A, &regh);
	ov8850_read_reg(0x300B, &regl);

	id = ((regh << 8) | regl);
	print_info("ov8850 product id:0x%x", id);
	if (OV8850_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor ov8850");
		return -ENODEV;
	}

	/*
	 * check ov8850 module vendor.
	 * GPIO2 --- R303E[2]
	 * GPIO1 --- R303E[3]
	 * GPIO0 --- R303F[3]
	 * Sunny:   gpio[2]=0;gpio[1]=0;gpio[0]=0;
	 * Foxconn: gpio[2]=0;gpio[1]=0;gpio[0]=1;
	 * Samsung:  gpio[2]=0;gpio[1]=1;gpio[0]=0;
	 */

	/* Frist should out LP11 */
	ov8850_write_reg(0x0100, 0x01, 0x00);
	/* Read gpio register. */
	ov8850_read_reg(0x303e, &regh);
	ov8850_read_reg(0x303f, &regl);

	factory_id = (regh & 0x4) | ((regh & 0x8) >> 2) | ((regl & 0x8) >> 3);
	ov8850_sensor.vcm = &ov8850_vcm;

 	if (factory_id == OV8850_FOXCONN_FACTORY_ID) {
		print_info("Vendor GPIO id:0x%x, it is Foxconn", factory_id);
		memcpy(ov8850_sensor.vcm, &vcm_dw9714, sizeof(vcm_info_s));
	} else if (factory_id == OV8850_SUNNY_FACTORY_ID) {
		print_info("vendor GPIO id:0x%x, it is Sunny", factory_id);
		memcpy(ov8850_sensor.vcm, &vcm_dw9714, sizeof(vcm_info_s));
	} else  if (factory_id == OV8850_SAMSUNG_FACTORY_ID) {
		print_error("Vendor GPIO id:0x%x, it is Samsung", factory_id);
		memcpy(ov8850_sensor.vcm, &vcm_dw9714, sizeof(vcm_info_s));
	} else {
		print_error("Vendor GPIO id:0x%x, not supported yet, use default Sunny", factory_id);
		memcpy(ov8850_sensor.vcm, &vcm_dw9714, sizeof(vcm_info_s));
	}

	ov8850_sensor.vcm->get_vcm_otp = ov8850_get_vcm_otp;
	/* h00206029_20120320 check otp available*/
	ov8850_otp_index = -1;
	for (i = 2; i >=0; i--) {
		if (1 == ov8850_check_otp_group(i)) {
			ov8850_read_otp_vcm(i, &ov8850_vcm_start, &ov8850_vcm_end);
			print_info("Successfully read ov8850 otp_index %d, vcm start 0x%x, vcm end 0x%x",
				i, ov8850_vcm_start, ov8850_vcm_end);
			ov8850_otp_index = i;
			break;
		}
	}
	/* then enter LP11 again */
	ov8850_write_reg(0x0100, 0x00, 0x00);


#ifndef OVISP_DEBUG_MODE	///cam_util.h:38
	//camera modules switch from factory_id
	if (factory_id == OV8850_FOXCONN_FACTORY_ID) {
		size = ARRAY_SIZE(isp_init_regs_ov8850_foxconn);
		ov8850_write_isp_seq(isp_init_regs_ov8850_foxconn, size);
	} else if (factory_id == OV8850_SAMSUNG_FACTORY_ID) {
		size = ARRAY_SIZE(isp_init_regs_ov8850_samsung);
		ov8850_write_isp_seq(isp_init_regs_ov8850_samsung, size);
	} else {
		size = ARRAY_SIZE(isp_init_regs_ov8850_foxconn);
		ov8850_write_isp_seq(isp_init_regs_ov8850_foxconn, size);
	}
#endif

	return 0;
}

/****************************************************************************
* FunctionName: ov8850_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
int ov8850_power(camera_power_state power)
{
	int ret = 0;
	print_debug("enter %s", __func__);

#if 0
	if (power == POWER_ON) {

		k3_ispldo_power_sensor(power, "pri-cameralog-vcc");	//avdd-ldo19

		k3_ispldo_power_sensor(power, "camera-vcc");		//iovdd-ldo18


		k3_ispgpio_power_sensor(&ov8850_sensor, power);	//pwdn and af vcm

		k3_ispio_ioconfig(&ov8850_sensor, power);			//isp i2c, rst, 

		ret = camera_power_core_ldo(power);				//core ldo, gpio073,

		k3_ispldo_power_sensor(power, "cameravcm-vcc");	//af vdd-ldo20

		k3_ispldo_power_sensor(power, "sec-cameralog-vcc");//scam avdd-ldo11
		msleep(2); 
	} else {
		k3_ispio_deinit_csi(ov8850_sensor.mipi_index);

		k3_ispldo_power_sensor(power, "sec-cameralog-vcc");
		k3_ispldo_power_sensor(power, "cameravcm-vcc");
		camera_power_core_ldo(power);
		udelay(200);

		k3_ispio_ioconfig(&ov8850_sensor, power);
		k3_ispgpio_power_sensor(&ov8850_sensor, power);

		k3_ispldo_power_sensor(power, "camera-vcc");
		udelay(10);
		k3_ispldo_power_sensor(power, "pri-cameralog-vcc");
	}
#else
    if (power == POWER_ON) {
        k3_socgpio_power_sensor(0, CAMERA_ANALOG_VDD);
        k3_socgpio_power_sensor(0, CAMERA_IO_VCC);

        k3_ispgpio_power_sensor(&ov8850_sensor, power);
        //k3_ispio_ioconfig(&ov8850_sensor, power);

        k3_socgpio_power_sensor(1, CAMERA_CORE_VDD);

        k3_socgpio_power_sensor(1, CAMERA_VCM_VCC);
        // block in B050  k3_ispldo_power_sensor(power, "sec-cameralog-vcc");
    } else {
        k3_ispio_deinit_csi(ov8850_sensor.mipi_index);

        // block in B050 k3_ispldo_power_sensor(power, "sec-cameralog-vcc");
        k3_socgpio_power_sensor(0, CAMERA_VCM_VCC);
        k3_socgpio_power_sensor(0, CAMERA_CORE_VDD);
        udelay(200);

        //k3_ispio_ioconfig(&ov8850_sensor, power);
        k3_ispgpio_power_sensor(&ov8850_sensor, power);

        k3_socgpio_power_sensor(1, CAMERA_IO_VCC);
        udelay(10);
        k3_socgpio_power_sensor(1, CAMERA_ANALOG_VDD);
    }
#endif

	return ret;
}
/*
 * Here gain is in unit 1/16 of sensor gain,
 * y36721 todo, temporarily if sensor gain=0x10, ISO is 100
 * in fact we need calibrate an ISO-ET-gain table.
 */
u32 ov8850_gain_to_iso(int gain)
{
	return (gain * 100) / 0x10;
}

u32 ov8850_iso_to_gain(int iso)
{
	return (iso * 0x10) / 100;
}

void ov8850_set_gain(u32 gain)
{
	ov8850_write_reg(OV8850_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	ov8850_write_reg(OV8850_GAIN_REG_L, gain & 0xff, 0x00);
}

u32 ov8850_get_gain(void)
{
	u8 gain_h = 0;
	u8 gain_l = 0;
	u32 gain;
	ov8850_read_reg(OV8850_GAIN_REG_H, &gain_h);
	ov8850_read_reg(OV8850_GAIN_REG_L, &gain_l);
	gain = (gain_h << 8) | gain_l;
	return gain;
}

/* begin: import sensor8850 from G710, camear_iso_limit_t isn't defined*/
#if 0
int ov8850_get_iso_limit(camear_iso_limit_t type )
{
	if( ISO_UPPER_LIMIT == type){
		return OV8850_ISO_UPPER_LIMIT;
	}else if( ISO_LOWER_LIMIT == type){
		return OV8850_ISO_LOWER_LIMIT;
	}else{
		print_error("%s: invaid camear_iso_limit argument.\n", __func__);
		return -1;
	}
}
#endif
/* end: import sensor8850 from G710, camear_iso_limit_t isn't defined*/

u32 ov8850_get_vts_reg_addr(void)
{
	return OV8850_VTS_REG_H;
}

void ov8850_set_exposure(u32 exposure)
{
	ov8850_write_reg(OV8850_EXPOSURE_REG_0, (exposure >> 16) & 0x0f, 0x00);
	ov8850_write_reg(OV8850_EXPOSURE_REG_1, (exposure >> 8) & 0xff, 0x00);
	ov8850_write_reg(OV8850_EXPOSURE_REG_2, exposure & 0xf0, 0x00);	/*fraction part not used */
}

u32 ov8850_get_exposure(void)
{
	u8 exposure[3] = { 0, 0, 0 };
	u32 expo;

	ov8850_read_reg(OV8850_EXPOSURE_REG_0, &exposure[0]);
	ov8850_read_reg(OV8850_EXPOSURE_REG_1, &exposure[1]);
	ov8850_read_reg(OV8850_EXPOSURE_REG_2, &exposure[2]);
	expo = (exposure[0] << 16) | (exposure[1] << 8) | exposure[2];

	return expo;
}

/*
 **************************************************************************
 * FunctionName: ov8850_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_reset(camera_power_state power_state)
{
	print_debug("enter %s", __func__);

	if (POWER_ON == power_state) {
		k3_isp_io_enable_mclk(MCLK_ENABLE, ov8850_sensor.sensor_index);
		k3_ispgpio_reset_sensor(ov8850_sensor.sensor_index, power_state,
					ov8850_sensor.power_conf.reset_valid);
		
	} else {
		k3_ispgpio_reset_sensor(ov8850_sensor.sensor_index, power_state,
					ov8850_sensor.power_conf.reset_valid);
		udelay(20);
		k3_isp_io_enable_mclk(MCLK_DISABLE, ov8850_sensor.sensor_index);
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov8850_init;
 * Description : ov8850 init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int ov8850_init(void)
{
	static bool ov8850_check = false;
	print_debug("enter %s", __func__);

	if (false == ov8850_check)
	{
/*begin: only used in 8850 drv, G710, defined in huawei\hsad\Config_interface.c, 20130312*/
#if 0   
		if (check_suspensory_camera("OV8850") != 1)
		{
			return -ENODEV;
		}
#endif
/*end: only used in 8850 drv, G710, defined in huawei\hsad\Config_interface.c, 20130312*/

		ov8850_check = true;
	}

	if (!camera_timing_is_match(1)) {
		print_error("%s: sensor timing don't match.\n", __func__);
		return -ENODEV;
	}

	if (ov8850_sensor.owner && !try_module_get(ov8850_sensor.owner)) {
		print_error("%s: try_module_get fail", __func__);
		return -ENOENT;
	}

#if 0                  /* del for B05X */
	k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V */
	k3_ispio_power_init(CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V */
	k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V */
	k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_12V, LDO_VOLTAGE_12V);	/*CORE 1.2V */
#endif

	print_debug("exit %s", __func__);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov8850_exit;
 * Description : ov8850 exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov8850_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (ov8850_sensor.owner) {
		module_put(ov8850_sensor.owner);
	}
	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: ov8850_shut_down;
 * Description : ov8850 shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov8850_shut_down(void)
{
	print_debug("enter %s", __func__);
	k3_ispgpio_power_sensor(&ov8850_sensor, POWER_OFF);
}

/*
 **************************************************************************
 * FunctionName: ov8850_check_otp_group;
 * Description : check whether the group of index is valid;
 * Input       : index of otp group. (0, 1, 2);
 * Output      : 0, group of index is empty;
 *				 1, group of index has valid data;
 *				-1, unexpected error;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
int ov8850_check_otp_group(u16 index)
{
	u8 temp1 = 0;
	u8 temp2 = 0;
	u8 i;
	u8 bank;

	switch (index) {
		case 0:
			bank = 1;
			break;
		case 1:
			bank = 6;
			break;
		case 2:
			bank = 11;
			break;
		default:
			return -1;
	}

	/* select bank  */
	ov8850_write_reg(0x3d84, 0xc0 | bank, 0x00);
	/* load otp to buffer */
	ov8850_write_reg(0x3d81, 0x01, 0x00);
	/* delay 10ms if needed */
	mdelay(1);
	/* disable otp read */
	ov8850_write_reg(0x3d81, 0x00, 0x00);

	ov8850_read_reg(0x3d06, &temp1);
	ov8850_read_reg(0x3d08, &temp2);

	if (temp1 | temp2)
		return 1;
	else
		return 0;
}

/*
 **************************************************************************
 * FunctionName: ov8850_read_otp_mi_wb_vcm;
 * Description : read out calibration datas of module info, wb and vcm;
 * Input       : index of otp group. (0, 1, 2);
 * Output      : true, ok;
 *				 false, unexpected error;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
void ov8850_read_otp_mi_wb_vcm(u16 index, struct otp_struct *potp)
{
	u8 i;
	u8 bank;

	switch (index) {
		case 0:
			bank = 1;
			break;
		case 1:
			bank = 6;
			break;
		case 2:
			bank = 11;
			break;
		default:
			return;
	}

	/* select bank */
	ov8850_write_reg(0x3d84, 0xc0 | bank, 0x00);
	/* load otp to buffer */
	ov8850_write_reg(0x3d81, 0x01, 0x00);
	/* delay 10ms if needed */
	mdelay(1);
	/* disable otp read */
	ov8850_write_reg(0x3d81, 0x00, 0x00);

	//ov8850_read_reg(0x3d00, &(potp->year));
	//ov8850_read_reg(0x3d01, &(potp->month));
	//ov8850_read_reg(0x3d02, &(potp->day));
	//ov8850_read_reg(0x3d03, &(potp->user_id_1));
	//ov8850_read_reg(0x3d04, &(potp->user_id_2));
	//ov8850_read_reg(0x3d05, &(potp->user_id_3));
	//ov8850_read_reg(0x3d06, &(potp->cam_code));
	ov8850_read_reg(0x3d07, &(potp->vendor_version));
	//ov8850_read_reg(0x3d08, &(potp->rg_h));
	//ov8850_read_reg(0x3d09, &(potp->rg_l));
	//ov8850_read_reg(0x3d0a, &(potp->bg_h));
	//ov8850_read_reg(0x3d0b, &(potp->bg_l));
	//ov8850_read_reg(0x3d0c, &(potp->gbgr_h));
	//ov8850_read_reg(0x3d0d, &(potp->gbgr_l));
	//ov8850_read_reg(0x3d0e, &(potp->start_curr));
	//ov8850_read_reg(0x3d0f, &(potp->end_curr));
}

/*
 **************************************************************************
 * FunctionName: ov8850_read_otp_wb;
 * Description : read out calibration datas of wb;
 * Input       : index of otp group. (0, 1, 2);
 * Output      : true, ok;
 *				 false, unexpected error;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
bool ov8850_read_otp_wb(u16 index, struct otp_struct *potp)
{
	u8 i;
	u8 bank;

	switch (index) {
		case 0:
			bank = 1;
			break;
		case 1:
			bank = 6;
			break;
		case 2:
			bank = 11;
			break;
		default:
			return false;
	}

	/* select bank */
	ov8850_write_reg(0x3d84, 0xc0 | bank, 0x00);
	/* load otp to buffer */
	ov8850_write_reg(0x3d81, 0x01, 0x00);
	/* delay 10ms if needed */
	mdelay(1);
	/* disable otp read */
	ov8850_write_reg(0x3d81, 0x00, 0x00);

	ov8850_read_reg(0x3d08, &(potp->rg_h));
	ov8850_read_reg(0x3d09, &(potp->rg_l));
	ov8850_read_reg(0x3d0a, &(potp->bg_h));
	ov8850_read_reg(0x3d0b, &(potp->bg_l));

	//select bank 5
	ov8850_write_reg(0x3d84, 0xc0 | (bank + 4), 0x00);
	// load otp to buffer
	ov8850_write_reg(0x3d81, 0x01, 0x00);
	mdelay(1);
	// disable otp read
	ov8850_write_reg(0x3d81, 0x00, 0x00);
	ov8850_read_reg(0x3d0e, &(potp->rg_coff));
	ov8850_read_reg(0x3d0f, &(potp->bg_coff));

	return true;
}

bool ov8850_read_otp_vcm(u16 index, u8 *vcm_start, u8 *vcm_end)
{
	u8 bank;

	switch (index) {
		case 0:
			bank = 1;
			break;
		case 1:
			bank = 6;
			break;
		case 2:
			bank = 11;
			break;
		default:
			return false;
	}

	/* select bank */
	ov8850_write_reg(0x3d84, 0xc0 | bank, 0x00);
	/* load otp to buffer */
	ov8850_write_reg(0x3d81, 0x01, 0x00);
	/* delay 10ms if needed */
	mdelay(1);
	/* disable otp read */
	ov8850_write_reg(0x3d81, 0x00, 0x00);

	ov8850_read_reg(0x3d0e, vcm_start);
	ov8850_read_reg(0x3d0f, vcm_end);

	return true;
}

/*
 **************************************************************************
 * FunctionName: ov8850_read_otp_lenc;
 * Description : read out calibration datas of lenc;
 * Input       : index of otp group. (0, 1, 2);
 * Output      : true, ok;
 *				 false, unexpected error;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
bool ov8850_read_otp_lenc(u16 index, struct otp_struct *potp)
{
	u8 i, bank;
	u8 otp_part;
	switch (index) {
		case 0:
			bank = 2;
			break;
		case 1:
			bank = 7;
			break;
		case 2:
			bank = 12;
			break;
		default:
			return false;
	}

	/*
	 * read out part 1
	 * clear otp buffer
	 */
	for (otp_part = 0; otp_part < 4; otp_part++) {
		/* select bank */
		ov8850_write_reg(0x3d84, 0xc0 | (bank + otp_part), 0x00);
		/* load otp to buffer */
		ov8850_write_reg(0x3d81, 0x01, 0x00);
		/* delay 10ms if needed */
		mdelay(1);
		/* disable otp read */
		ov8850_write_reg(0x3d81, 0x00, 0x00);

		if (otp_part < 3) {
			for (i = 0; i < 16; i++)
				ov8850_read_reg(OTP_BUFFER_START_ADDRESS + i, &(potp->lenc[i + 16 * otp_part]));
		} else {
			for (i = 0; i < 14; i++)
				ov8850_read_reg(OTP_BUFFER_START_ADDRESS + i, &(potp->lenc[i + 16 * otp_part]));
		}
	}

	return true;
}

/*
 **************************************************************************
 * FunctionName: ov8850_update_wb_gain;
 * Description : NA;
 * Input       : R_gain: red gain of sensor MWB, 0x400 = 1;
 *				 G_gain: green gain of sensor MWB, 0x400 = 1;
 *				 B_gain: blue gain of sensor MWB, 0x400 = 1;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
void ov8850_update_wb_gain(u16 R_gain, u16 G_gain, u16 B_gain)
{
	u8 temp = 0;
	if (R_gain > 0x400) {
		ov8850_write_reg(0x3400, R_gain>>8, 0x00);
		ov8850_write_reg(0x3401, R_gain & 0x00ff, 0x00);
	}

	if (G_gain > 0x400) {
		ov8850_write_reg(0x3402, G_gain>>8, 0x00);
		ov8850_write_reg(0x3403, G_gain & 0x00ff, 0x00);
	}

	if (B_gain > 0x400) {
		ov8850_write_reg(0x3404, B_gain>>8, 0x00);
		ov8850_write_reg(0x3405, B_gain & 0x00ff, 0x00);
	}

	/* enable mwb */
	ov8850_read_reg(0x3406, &temp);
	ov8850_write_reg(0x3406, temp|0x01, 0x00);
}

void ov8850_update_lenc(unsigned char *plenc)
{
	u16 i;
	u8 temp = 0;

	for(i=0; i<62; i++) {
		ov8850_write_reg(0x5800+i, *(plenc+i), 0x00);
	}
	/*enable LenC*/
	ov8850_read_reg(0x5000, &temp);
	ov8850_write_reg(0x5000, temp|0x80, 0x00);
}


void ov8850_update_otp_wb(u16 otp_index)
{
#if 0
	/* isp method */
	/* need fix */
	u32 RG_Ratio_typical = 0x267; //RG_TYPICAL;
	u32 BG_Ratio_typical = 0x261; //BG_TYPICAL;
	/* need fix */

	struct otp_struct current_otp;
	u32 rg_ratio, bg_ratio;
	int delta_x50, delta_y50;
	u32 d65_limit_new, d65_split_new, d65_limit_cur, d65_split_cur;
	u32 a_limit_new, a_split_new, a_limit_cur, a_split_cur;
	u32 cwf_x_new, cwf_y_new, cwf_x_cur, cwf_y_cur;
	u32 k_y2x_cur, k_x2y_cur;
	u32 CT_a_cur, CT_cwf_cur, CT_d_cur, CT_a_new, CT_cwf_new, CT_d_new;
	u32 CT_hligt_1_cur, CT_hligt_2_cur, CT_hligt_1_new, CT_hligt_2_new;
	u32 CT_hligt_d50_b_cur, CT_hligt_d50_b_new, CT_hligt_d50_r_cur, CT_hligt_d50_r_new;
	u32 center_CT_new, left_CT_new, right_CT_new, center_CT_cur, left_CT_cur, right_CT_cur;
	/*u32 x_left_new, x_right_new;
	u32 y_left_new, y_right_new;*/
	u32 CT_d50_typical, CT_d50_new;

	print_info("Enter function %s", __func__);
	/* R/G and B/G of current camera module is read out from sensor OTP */
	ov8850_read_otp_wb(otp_index, &current_otp);
	rg_ratio = ((current_otp.rg_h << 8) & 0xff00) | (current_otp.rg_l & 0xff);/* OTP_RG' */
	bg_ratio = ((current_otp.bg_h << 8) & 0xff00) | (current_otp.bg_l & 0xff);/* OTP_BG' */

	if (current_otp.rg_coff != 0)
		rg_ratio = rg_ratio * (current_otp.rg_coff + 128) / 256;

	if (current_otp.bg_coff != 0)
		bg_ratio = bg_ratio * (current_otp.bg_coff + 128) / 256;

	delta_x50 = (1024 << 6) * (BG_Ratio_typical - bg_ratio) / (bg_ratio * BG_Ratio_typical);
	delta_y50 = (1024 << 6) * (RG_Ratio_typical - rg_ratio ) / (rg_ratio * RG_Ratio_typical);

	d65_limit_cur = ov8850_read_isp_reg(REG_D65_LIMIT, 1) & 0xFF;
	d65_split_cur = ov8850_read_isp_reg(REG_D65_SPLIT, 1) & 0xFF;

	a_limit_cur = ov8850_read_isp_reg(REG_A_LIMIT, 1) & 0xFF;
	a_split_cur = ov8850_read_isp_reg(REG_A_SPLIT, 1) & 0xFF;

	cwf_x_cur = ov8850_read_isp_reg(REG_CWF_X, 1) & 0xFF;
	cwf_y_cur = ov8850_read_isp_reg(REG_CWF_Y, 1) & 0xFF;

	k_y2x_cur = ov8850_read_isp_reg(REG_K_Y2X, 1) & 0xFF;
	k_x2y_cur = ov8850_read_isp_reg(REG_K_X2Y, 1) & 0xFF;

	left_CT_cur = ((ov8850_read_isp_reg(REG_LEFT_CT, 1) & 0xff) << 8) |(ov8850_read_isp_reg(REG_LEFT_CT + 1, 1) & 0xff);
	center_CT_cur = ((ov8850_read_isp_reg(REG_CENTER_CT, 1) & 0xff) << 8) |(ov8850_read_isp_reg(REG_CENTER_CT + 1, 1) & 0xff);
	right_CT_cur =((ov8850_read_isp_reg(REG_RIGHT_CT, 1) & 0xff) << 8) |(ov8850_read_isp_reg(REG_RIGHT_CT + 1, 1) & 0xff);

	CT_a_cur = ov8850_read_isp_reg(REG_CT_A, 1) & 0xFF;
	CT_cwf_cur = ov8850_read_isp_reg(REG_CT_CWF, 1) & 0xFF;
	CT_d_cur = ov8850_read_isp_reg(REG_CT_D, 1) & 0xFF;

	CT_hligt_1_cur = ov8850_read_isp_reg(REG_CT_HIGH_LIGHT_1, 1) & 0xFF;
	CT_hligt_2_cur = ov8850_read_isp_reg(REG_CT_HIGH_LIGHT_2, 1) & 0xFF;

	CT_hligt_d50_b_cur = ov8850_read_isp_reg(REG_CT_HIGH_LIGHT_D50_B, 1) & 0xFF;
	CT_hligt_d50_r_cur = ov8850_read_isp_reg(REG_CT_HIGH_LIGHT_D50_R, 1) & 0xFF;

	#if 0
	/* ISP AWB setting transform */
	/* calculate new d65_limit */
	d65_limit_new = d65_limit_cur + delta_x50;
	/* calculate new d65_split */
	d65_split_new = d65_split_cur + delta_x50;
	/* calculate new a_limit */
	a_limit_new = a_limit_cur + delta_y50;
	/* calculate new a_split */
	a_split_new = a_split_cur + delta_y50;
	/* calculate new cwf_x */
	cwf_x_new = cwf_x_cur + delta_x50;
	/* calculate new cwf_y */
	cwf_y_new = cwf_y_cur + delta_y50;
	#endif

	/* ISP AWB setting transform */
	/* calculate new d65_limit */
	d65_limit_new = d65_limit_cur * BG_Ratio_typical / bg_ratio;
	/* calculate new d65_split */
	d65_split_new = d65_split_cur * BG_Ratio_typical / bg_ratio;
	/* calculate new a_limit */
	a_limit_new = a_limit_cur  * RG_Ratio_typical / rg_ratio;
	/* calculate new a_split */
	a_split_new = a_split_cur * RG_Ratio_typical / rg_ratio;
	/* calculate new cwf_x */
	cwf_x_new = cwf_x_cur * BG_Ratio_typical / bg_ratio;
	/* calculate new cwf_y */
	cwf_y_new = cwf_y_cur * RG_Ratio_typical / rg_ratio;


	CT_d50_typical = 256 * RG_Ratio_typical / BG_Ratio_typical;
	CT_d50_new = 256 * rg_ratio / bg_ratio;

	center_CT_new = center_CT_cur * CT_d50_new / CT_d50_typical;
	left_CT_new = left_CT_cur * CT_d50_new / CT_d50_typical;
	right_CT_new = right_CT_cur * CT_d50_new / CT_d50_typical;

	CT_a_new = CT_a_cur * bg_ratio * RG_Ratio_typical / (rg_ratio * BG_Ratio_typical);
	CT_cwf_new = CT_cwf_cur * bg_ratio * RG_Ratio_typical / (rg_ratio * BG_Ratio_typical);
	CT_d_new = CT_d_cur * bg_ratio * RG_Ratio_typical / (rg_ratio * BG_Ratio_typical);
	if(CT_d_new > 0xff)
		CT_d_new = 0xff;

	CT_hligt_1_new = CT_hligt_1_cur * bg_ratio * RG_Ratio_typical / (rg_ratio * BG_Ratio_typical);
	CT_hligt_2_new = CT_hligt_2_cur * bg_ratio * RG_Ratio_typical / (rg_ratio * BG_Ratio_typical);
	if(CT_hligt_2_new > 0xff)
		CT_hligt_2_new = 0xff;

	CT_hligt_d50_b_new = CT_hligt_d50_b_cur * BG_Ratio_typical / bg_ratio;
	CT_hligt_d50_r_new = CT_hligt_d50_r_cur * RG_Ratio_typical / rg_ratio;
	if(CT_hligt_d50_r_new > 0xff) {
		/* CT_hligt_d50_b_new = CT_hligt_d50_b_new * 0xff / CT_hligt_d50_r_new; */
		CT_hligt_d50_r_new = 0xff;
	}
	#if 0
	//ori method
	/* ISP CT setting transform */
	/* calculate new center_CT */
	center_CT_new = (cwf_x_new << 8) / cwf_y_new;
	/* calculate new X_left
	 * X_Left’=((128* CWF_X/ K_Y2X- CWF_Y)/(128/ K_Y2X-256/ LeftCT)+ delta_x50
	 * X_Left’ = (128 * CWF_X - CWF_Y * K_Y2X) * LeftCT/(128*(LeftCT - 2 * K_Y2X))
	*/
	x_left_new = ((cwf_x_cur << 7) - cwf_y_cur * k_y2x_cur) * left_CT_cur / ((left_CT_cur - (k_y2x_cur << 1) ) << 7) + delta_x50;
	/* calculate new y_left
	 * Y_Left’=256*(128*CWF_X/K_Y2X-CWF_Y)/(128/K_Y2X-256/LeftCT)/LeftCT+delta_y50
	 * Y_Left’=256*(X_Left’-delta_x50)/LeftCT+delta_y50
	*/
	y_left_new = ((x_left_new - delta_x50) << 8) /left_CT_cur+ delta_y50;
	/*calculate new LeftCT*/
	left_CT_new = (x_left_new << 8) / y_left_new;
	/* calculate new x_right
	 * X_Right’=((CWF_X*K_X2Y/128- CWF_Y)/( K_X2Y/128-256/RightCT)+ delta_x50
	 * X_Right’=(CWF_X*K_X2Y-CWF_Y*128)*RightCT/(K_X2Y*RightCT-256*128)
	*/
	x_right_new = (cwf_x_cur * k_x2y_cur - cwf_y_cur  << 7) * right_CT_cur / (k_x2y_cur * right_CT_cur - (256 << 7)) + delta_x50;
	/* calculate new y_right
	 * Y_Right’=256*(CWF_X* K_X2Y/128-CWF_Y)/(K_X2Y/128-256/RightCT)/RightCT+ delta_y50
	 * Y_Right’=256*(X_Right -delta_x50) / RightCT +delta_y50
	*/
	y_right_new = ((x_right_new - delta_x50) << 8) / right_CT_cur + delta_y50;
	/* calculate new right_CT
	 * RightCT’=256* X_Right’/ Y_Right’;
	*/
	right_CT_new = (x_right_new << 8) / y_right_new;
	#endif

	print_debug("rg_ratio && bg_ration of golden_sample is 0x%x && 0x%x", RG_Ratio_typical, BG_Ratio_typical);
	print_debug("rg_ratio && bg_ration of this sample is 0x%x && 0x%x", rg_ratio, bg_ratio);

	print_debug("delta_x50 = %d, delta_y50 = %d", delta_x50, delta_y50);
	print_debug("k_y2x_cur = 0x%x, k_x2y_cur = 0x%x", k_y2x_cur, k_x2y_cur);

	print_debug("d65_limit_cur = 0x%x, d65_split_cur = 0x%x", d65_limit_cur, d65_split_cur);
	print_debug("d65_limit_new = 0x%x, d65_split_new = 0x%x", d65_limit_new, d65_split_new);

	print_debug("a_limit_cur = 0x%x, a_split_cur = 0x%x", a_limit_cur, a_split_cur);
	print_debug("a_limit_new = 0x%x, a_split_new = 0x%x", a_limit_new, a_split_new);

	print_debug("cwf_x_cur = 0x%x, cwf_y_cur = 0x%x", cwf_x_cur, cwf_y_cur);
	print_debug("cwf_x_new = 0x%x, cwf_y_new = 0x%x", cwf_x_new, cwf_y_new);

	/* print_debug("x_left_new = 0x%x, y_left_new = 0x%x, x_right_new = 0x%x,  y_right_new = 0x%x", x_left_new, y_left_new, x_right_new, y_right_new); */
	print_debug("left_CT_cur = 0x%x, center_CT_cur = 0x%x, right_CT_cur = 0x%x", left_CT_cur, center_CT_cur, right_CT_cur);
	print_debug("left_CT_new = 0x%x, center_CT_new = 0x%x, right_CT_new = 0x%x", left_CT_new, center_CT_new, right_CT_new);

	print_debug("CT_a_cur = 0x%x, CT_cwf_cur = 0x%x, CT_d_cur = 0x%x", CT_a_cur, CT_cwf_cur, CT_d_cur);
	print_debug("CT_a_new = 0x%x, CT_cwf_new = 0x%x, CT_d_new = 0x%x", CT_a_new, CT_cwf_new, CT_d_new);

	print_debug("CT_hligt_1_cur = 0x%x, CT_hligt_1_new = 0x%x", CT_hligt_1_cur, CT_hligt_1_new);
	print_debug("CT_hligt_2_cur = 0x%x, CT_hligt_2_new = 0x%x", CT_hligt_2_cur, CT_hligt_2_new);

	print_debug("CT_hligt_d50_b_cur = 0x%x, CT_hligt_d50_b_new = 0x%x", CT_hligt_d50_b_cur, CT_hligt_d50_b_new);
	print_debug("CT_hligt_d50_r_cur = 0x%x, CT_hligt_d50_r_new = 0x%x", CT_hligt_d50_r_cur, CT_hligt_d50_r_new);

	/* write new value to each related register */
	ov8850_write_isp_reg(REG_D65_LIMIT, d65_limit_new, 1);
	ov8850_write_isp_reg(REG_D65_SPLIT, d65_split_new, 1);
	ov8850_write_isp_reg(REG_A_LIMIT, a_limit_new, 1);
	ov8850_write_isp_reg(REG_A_SPLIT, a_split_new, 1);
	ov8850_write_isp_reg(REG_CWF_X, cwf_x_new, 1);
	ov8850_write_isp_reg(REG_CWF_Y, cwf_y_new, 1);
	ov8850_write_isp_reg(REG_CENTER_CT, center_CT_new, 2);
	ov8850_write_isp_reg(REG_LEFT_CT, (left_CT_new >> 8)&0xff, 1);
	ov8850_write_isp_reg(REG_LEFT_CT + 1, left_CT_new & 0xff, 1);
	ov8850_write_isp_reg(REG_CENTER_CT, (center_CT_new >> 8)&0xff, 1);
	ov8850_write_isp_reg(REG_CENTER_CT + 1, center_CT_new & 0xff, 1);
	ov8850_write_isp_reg(REG_RIGHT_CT, (right_CT_new >> 8)&0xff , 1);
	ov8850_write_isp_reg(REG_RIGHT_CT + 1, right_CT_new & 0xff , 1);

	ov8850_write_isp_reg(REG_CT_A, CT_a_new, 1);
	ov8850_write_isp_reg(REG_CT_CWF, CT_cwf_new, 1);
	ov8850_write_isp_reg(REG_CT_D, CT_d_new, 1);

	ov8850_write_isp_reg(REG_CT_HIGH_LIGHT_1, CT_hligt_1_new, 1);
	ov8850_write_isp_reg(REG_CT_HIGH_LIGHT_2, CT_hligt_2_new, 1);

	ov8850_write_isp_reg(REG_CT_HIGH_LIGHT_D50_B, CT_hligt_d50_b_new, 1);
	ov8850_write_isp_reg(REG_CT_HIGH_LIGHT_D50_R, CT_hligt_d50_r_new, 1);

#else
	/* sensor method */

	struct otp_struct current_otp;

	u32 rg_ratio, bg_ratio;
	u32 R_gain, G_gain, B_gain, G_gain_R, G_gain_B;

	u32 RG_Ratio_typical; //RG_TYPICAL;
	u32 BG_Ratio_typical; //BG_TYPICAL;

	if (factory_id == OV8850_SAMSUNG_FACTORY_ID) {
		RG_Ratio_typical = 0x250;
		BG_Ratio_typical = 0x261;
	} else {
		RG_Ratio_typical = 0x267;
		BG_Ratio_typical = 0x261;
	}

	/* R/G and B/G of current camera module is read out from sensor OTP */
	ov8850_read_otp_wb(otp_index, &current_otp);
	rg_ratio = ((current_otp.rg_h << 8) & 0xff00) | (current_otp.rg_l & 0xff);/* OTP_RG' */
	bg_ratio = ((current_otp.bg_h << 8) & 0xff00) | (current_otp.bg_l & 0xff);/* OTP_BG' */

	if (current_otp.rg_coff != 0)
		rg_ratio = rg_ratio * (current_otp.rg_coff + 128) / 256;

	if (current_otp.bg_coff != 0)
		bg_ratio = bg_ratio * (current_otp.bg_coff + 128) / 256;

	//calculate gain
	//0x400 = 1x gain
	if (bg_ratio < BG_Ratio_typical) {
		if (rg_ratio < RG_Ratio_typical) {
			// bg_ratio < BG_Ratio_typical &&
			// rg_ratio < RG_Ratio_typical
			G_gain = 0x400;
			B_gain = 0x400 * BG_Ratio_typical / bg_ratio;
			R_gain = 0x400 * RG_Ratio_typical / rg_ratio;
		} else {
			// bg_ratio < BG_Ratio_typical &&
			// rg_ratio >= RG_Ratio_typical
			R_gain = 0x400;
			G_gain = 0x400 * rg_ratio / RG_Ratio_typical;
			B_gain = G_gain * BG_Ratio_typical / bg_ratio;
		}
	} else {
		if (rg_ratio < RG_Ratio_typical) {
			// bg_ratio >= BG_Ratio_typical &&
			// rg_ratio < RG_Ratio_typical
			B_gain = 0x400;
			G_gain = 0x400 * bg_ratio / BG_Ratio_typical;
			R_gain = G_gain * RG_Ratio_typical / rg_ratio;
		} else {
			// bg_ratio >= BG_Ratio_typical &&
			// rg_ratio >= RG_Ratio_typical
			G_gain_B = 0x400 * bg_ratio / BG_Ratio_typical;
			G_gain_R = 0x400 * rg_ratio / RG_Ratio_typical;

			if (G_gain_B > G_gain_R) {
				B_gain = 0x400;
				G_gain = G_gain_B;
				R_gain = G_gain * RG_Ratio_typical / rg_ratio;
			} else {
				R_gain = 0x400;
				G_gain = G_gain_R;
				B_gain = G_gain * BG_Ratio_typical / bg_ratio;
			}
    		}
	}

	// write sensor wb gain to registers
	ov8850_update_wb_gain(R_gain, G_gain, B_gain);
#endif
}

/*
 **************************************************************************
 * FunctionName: ov8850_update_otp_lenc;
 * Description : call this function after ov8850 initialization to calibrate lens correction;
 * Input       : R_gain: red gain of sensor MWB, 0x400 = 1;
 *				 G_gain: green gain of sensor MWB, 0x400 = 1;
 *				 B_gain: blue gain of sensor MWB, 0x400 = 1;
 * Output      : NA;
 * ReturnValue : 1 update success
 *				 0, no OTP
 *				 -1, unexpected error;
 * Other       : NA;
 **************************************************************************
*/
void ov8850_update_otp_lenc(u16 otp_index)
{
	struct otp_struct current_otp;

	print_debug("Enter function %s", __func__);
	ov8850_read_otp_lenc(otp_index, &current_otp);

	ov8850_update_lenc(current_otp.lenc);
}

void ov8850_update_blc(void)
{
	u8 blc_check = 0;

	/* clear otp buffer */
	ov8850_write_reg(0x3d0a, 0x00, 00);
	ov8850_write_reg(0x3d0b, 0x00, 00);

	ov8850_write_reg(0x3d84, 0xdf, 00);
	ov8850_write_reg(0x3d81, 0x01, 00);
	mdelay(1);
	ov8850_read_reg(0x3d0b, &blc_check);
	if (0 == blc_check) {
		ov8850_write_reg(0x4000, 0x18, 00);
		mdelay(1);
		ov8850_read_reg(0x3d0a, &blc_check);
		mdelay(1);
		print_debug("%s, blc not calculated 0x3d0a = %x", __func__, blc_check);
		ov8850_write_reg(0x4006, blc_check, 00);
	} else {
		ov8850_write_reg(0x4000, 0x10, 0x00);
		print_debug("%s, blc calculated ", __func__);
	}
	ov8850_write_reg(0x4009, 0x10, 0x00);
}


#define OV8850_VCM_V2H_OFFSET	0xa0

static void ov8850_get_vcm_otp(u16 *vcm_start, u16 *vcm_end)
{
	if (ov8850_vcm_start > (OV8850_VCM_V2H_OFFSET >> 2))
		*vcm_start = (ov8850_vcm_start << 2) - OV8850_VCM_V2H_OFFSET;
	else
		*vcm_start = 0;

	if (ov8850_vcm_end > (OV8850_VCM_V2H_OFFSET >> 2))
		*vcm_end = (ov8850_vcm_end << 2) - OV8850_VCM_V2H_OFFSET;
	else
		*vcm_end = 0;
}

static int ov8850_get_sensor_aperture()
{
	print_info("enter %s", __func__);
	return OV8850_APERTURE_FACTOR;
}

static int ov8850_get_equivalent_focus()
{
	print_info("enter %s", __func__);
	return OV8850_EQUIVALENT_FOCUS;
}

/*
 **************************************************************************
 * FunctionName: ov8850_set_default;
 * Description : init ov8850_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov8850_set_default(void)
{
	unsigned int chip_id;
	int i;
	ov8850_sensor.init = ov8850_init;
	ov8850_sensor.exit = ov8850_exit;
	
	ov8850_sensor.shut_down = ov8850_shut_down;
	
	ov8850_sensor.reset = ov8850_reset;
	
	ov8850_sensor.power = ov8850_power;
	
	ov8850_sensor.check_sensor = ov8850_check_sensor;
	ov8850_sensor.init_reg = ov8850_init_reg;
	//ov8850_sensor.init_isp_reg = ov8850_init_isp_reg;
	ov8850_sensor.stream_on = ov8850_stream_on;

	ov8850_sensor.set_flash = NULL;
	ov8850_sensor.get_flash = NULL;

	ov8850_sensor.set_scene = NULL;
	ov8850_sensor.get_scene = NULL;

	ov8850_sensor.set_hflip = ov8850_set_hflip;
	ov8850_sensor.get_hflip = ov8850_get_hflip;
	ov8850_sensor.set_vflip = ov8850_set_vflip;
	ov8850_sensor.get_vflip = ov8850_get_vflip;
	ov8850_sensor.update_flip = ov8850_update_flip;
	ov8850_sensor.hflip = 0;
	ov8850_sensor.vflip = 0;
	ov8850_sensor.old_flip = 0;

	ov8850_sensor.get_format = ov8850_get_format;

	ov8850_sensor.enum_framesizes = ov8850_enum_framesizes;
	ov8850_sensor.try_framesizes = ov8850_try_framesizes;
	ov8850_sensor.set_framesizes = ov8850_set_framesizes;
	ov8850_sensor.get_framesizes = ov8850_get_framesizes;

	ov8850_sensor.enum_frame_intervals = ov8850_enum_frame_intervals;
	ov8850_sensor.try_frame_intervals = NULL;
	ov8850_sensor.set_frame_intervals = NULL;
	ov8850_sensor.get_frame_intervals = NULL;

	ov8850_sensor.get_capability = ov8850_get_capability;

	ov8850_sensor.skip_frames = 0;
	
	ov8850_sensor.interface_type = MIPI1;
#ifdef MIPI_4LANE
	ov8850_sensor.mipi_lane_count = CSI_LINES_4;
#else
	ov8850_sensor.mipi_lane_count = CSI_LINES_2;
#endif
	ov8850_sensor.mipi_index = CSI_INDEX_0;
	ov8850_sensor.power_conf.pd_valid = LOW_VALID;//LOW_VALID;
	ov8850_sensor.power_conf.reset_valid = LOW_VALID;	//TBD, may be opposite	//LOW_VALID
	ov8850_sensor.power_conf.vcmpd_valid = LOW_VALID;
	ov8850_sensor.sensor_index = CAMERA_SENSOR_PRIMARY;
	
	ov8850_sensor.i2c_config.index = I2C_PRIMARY;
	ov8850_sensor.i2c_config.speed = I2C_SPEED_400;
	ov8850_sensor.i2c_config.addr = OV8850_SLAVE_ADDRESS_6C;	//for FOXCONN module
	ov8850_sensor.i2c_config.addr_bits = I2C_16BIT;
	ov8850_sensor.i2c_config.val_bits = I2C_8BIT;

	ov8850_sensor.sensor_type = SENSOR_OV;

	ov8850_sensor.aec_addr[0] = OV8850_EXPOSURE_REG_0;
	ov8850_sensor.aec_addr[1] = OV8850_EXPOSURE_REG_1;
	ov8850_sensor.aec_addr[2] = OV8850_EXPOSURE_REG_2;
	ov8850_sensor.agc_addr[0] = OV8850_GAIN_REG_H;
	ov8850_sensor.agc_addr[1] = OV8850_GAIN_REG_L;

	ov8850_sensor.isp_location = CAMERA_USE_K3ISP;
	ov8850_sensor.sensor_tune_ops = NULL;

	ov8850_sensor.sensor_gain_to_iso = ov8850_gain_to_iso;
	ov8850_sensor.sensor_iso_to_gain = ov8850_iso_to_gain;
	ov8850_sensor.get_ccm_pregain = ov8850_get_ccm_pregain;
	ov8850_sensor.get_flash_awb = ov8850_get_flash_awb;

	ov8850_sensor.set_gain = ov8850_set_gain;
	ov8850_sensor.get_gain = ov8850_get_gain;
	ov8850_sensor.set_exposure = ov8850_set_exposure;
	ov8850_sensor.get_exposure = ov8850_get_exposure;
	//ov8850_sensor.set_awb_gain = ov8850_set_awb_gain;

	ov8850_sensor.set_vts = ov8850_set_vts;
	ov8850_sensor.get_vts_reg_addr = ov8850_get_vts_reg_addr;

	ov8850_sensor.set_effect = NULL;
	ov8850_sensor.set_awb = NULL;
	
	//ov8850_sensor.set_anti_banding = ov8850_set_anti_banding;

	//ov8850_sensor.update_framerate = ov8850_update_frame_rate;
	
#ifndef OVISP_DEBUG_MODE
	ov8850_sensor.awb_dynamic_ccm_gain = ov8850_awb_dynamic_ccm_gain;
#else
	ov8850_sensor.awb_dynamic_ccm_gain = NULL;
#endif

	ov8850_sensor.get_sensor_aperture = ov8850_get_sensor_aperture;
	ov8850_sensor.get_equivalent_focus = ov8850_get_equivalent_focus;

	ov8850_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	ov8850_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;
	ov8850_sensor.preview_frmsize_index = 0;
	ov8850_sensor.capture_frmsize_index = 1;
	ov8850_sensor.frmsize_list = ov8850_framesizes;

	//ov8850_sensor.pclk= ???;
	
	ov8850_sensor.fps_max = 20;	//30 ??
	ov8850_sensor.fps_min = 1;	//15 ??
	ov8850_sensor.fps = 1;		//24 ??

    /*begin: import sensor8850 from G710, the var "get_iso_limit" is only used in 8850 drv, 20130312*/
	/*ov8850_sensor.get_iso_limit = ov8850_get_iso_limit;*/
    /*end: import sensor8850 from G710, the var "get_iso_limit" is only used in 8850 drv, 20130312*/

	/* auto focus parameters and image settings remove to function check_sensor() */
	ov8850_sensor.af_enable = 0;
	ov8850_sensor.vcm = &vcm_dw9714;	//which may be changed in check_sensor

	//ov8850_sensor.image_setting.lensc_param = ov8850_lensc_param;
	//ov8850_sensor.image_setting.ccm_param = ov8850_ccm_param;
	//ov8850_sensor.image_setting.awb_param = ov8850_awb_param;

	ov8850_sensor.owner = THIS_MODULE;

	/* Following parameters should be revised according to sensor */
	ov8850_sensor.info.facing = CAMERA_FACING_BACK;
	ov8850_sensor.info.orientation = 270;
	ov8850_sensor.info.focal_length = 439;	/* 4.39mm */
	ov8850_sensor.info.h_view_angle = 63;	/*  66.1 degree */	//63.2
	ov8850_sensor.info.v_view_angle = 50;	//49.7
	strcpy(ov8850_sensor.info.name,"23060108FA-OV-F");
	ov8850_sensor.lane_clk = CLK_800M;	//CLK_800M
	chip_id = get_chipid();

	if (chip_id == DI_CHIP_ID) {
		for (i = 0; i < (ARRAY_SIZE(ov8850_framesizes)); i++) {
			ov8850_framesizes[i].fps = ov8850_framesizes[i].fps_es;
		}

		/* full size, add by y36721 */
		i = ARRAY_SIZE(ov8850_framesizes) - 1;
		ov8850_framesizes[i].sensor_setting.setting = ov8850_framesize_full_es;
		ov8850_framesizes[i].sensor_setting.seq_size= ARRAY_SIZE(ov8850_framesize_full_es);
	}

	ov8850_sensor.support_summary		= true;
}

/*
 **************************************************************************
 * FunctionName: ov8850_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int ov8850_module_init(void)
{
	ov8850_set_default();
	return register_camera_sensor(ov8850_sensor.sensor_index, &ov8850_sensor);
}

/*
 **************************************************************************
 * FunctionName: ov8850_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit ov8850_module_exit(void)
{
	unregister_camera_sensor(ov8850_sensor.sensor_index, &ov8850_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(ov8850_module_init);
module_exit(ov8850_module_exit);
MODULE_LICENSE("GPL");
/********************************** END **********************************************/
