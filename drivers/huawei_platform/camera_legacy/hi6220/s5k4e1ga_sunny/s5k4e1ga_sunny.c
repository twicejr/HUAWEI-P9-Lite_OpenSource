/*
 *  s5k4e1ga_sunny camera driver source file
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
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <asm/div64.h>
#include "sensor_common.h"

#include "cherryplus/s5k4e1ga_sunny_cherryplus.h"
#include "chm/s5k4e1ga_sunny_chm.h"
#include "alice/s5k4e1ga_sunny_alice.h"

#include <asm/bug.h>
#include <linux/device.h>

#include "video_config.h"
#include "effect.h"

#define LOG_TAG "S5K4E1GA_SUNNY"
#define DEBUG_DEBUG 1
#include "cam_log.h"
#include "cam_util.h"


#define S5K4E1GA_SUNNY_AP_WRITEAE_MODE

#define S5K4E1GA_MAX_ISO 			1550
#define S5K4E1GA_MIN_ISO                      100
#define S5K4E1GA_AUTOFPS_GAIN_LOW2MID		0x60
#define S5K4E1GA_AUTOFPS_GAIN_MID2HIGH		0x60
#define S5K4E1GA_AUTOFPS_GAIN_HIGH2MID		0x24
#define S5K4E1GA_AUTOFPS_GAIN_MID2LOW		0x24
#define S5K4E1GA_MAX_FRAMERATE         30
#define S5K4E1GA_MID_FRAMERATE         10
#define S5K4E1GA_MIN_FRAMERATE          10
#define S5K4E1GA_MIN_CAP_FRAMERATE  8
#define S5K4E1GA_FLASH_TRIGGER_GAIN 0xff
#define S5K4E1GA_SHARPNESS_PREVIEW  0x30
#define S5K4E1GA_SHARPNESS_CAPTURE  0x08

#define S5K4E1GA_SUNNY_SLAVE_ADDRESS 0x30
#define S5K4E1GA_SUNNY_EQUIVALENT_FOCUS		22 // 22mm
#define S5K4E1GA_SUNNY_CHIP_ID       (0x4e10)

#define S5K4E1GA_SUNNY_APERTURE_FACTOR    240   //F2.4

#if 0 /*not referenced, pclint fail, 20140509*/
#define S5K4E1GA_SUNNY_CAM_MODULE_SKIPFRAME     4

#define S5K4E1GA_SUNNY_HFLIP    0
#define S5K4E1GA_SUNNY_VFLIP    0

#define S5K4E1GA_SUNNY_NO_FLIP	0x00
#define S5K4E1GA_SUNNY_H_FLIP	0x01
#define S5K4E1GA_SUNNY_V_FLIP	0x02
#define S5K4E1GA_SUNNY_HV_FLIP	0x03
#endif

#define S5K4E1GA_FLIP		0x0101

#define S5K4E1GA_SUNNY_EXPOSURE_REG_H	0x0202
#define S5K4E1GA_SUNNY_EXPOSURE_REG_L	0x0203
#define S5K4E1GA_SUNNY_GAIN_REG_H		0x0204
#define S5K4E1GA_SUNNY_GAIN_REG_L		0x0205

#define S5K4E1GA_SUNNY_VTS_REG_H		0x0340
#define S5K4E1GA_SUNNY_VTS_REG_L		0x0341

#define S5K4E1GA_SUNNY_I2C_RETRY_TIMES 5
#define S5K4E1GA_ZSL    (0x00)//(1 << CAMERA_ZSL_OFF)

#ifdef S5K4E1GA_USE_OTP

struct  s5k4e1ga_otp_struct {
    u16 product_year;//product year
    u16 product_month;//product month
    u16 product_date;//product date
    u16 camera_id;//hw camera id
    u16 supplier_version_id;//supplier version code
    u16 version;//camera version
    u16 wb_rg;// r/g ratio
    u16 wb_bg;// b/g ratio
};

typedef enum _s5k4e1ga_otp_location{
    S5K4E1GA_OTP_BEGIN = 0,
    S5K4E1GA_OTP_310D_LSB,//reg 0x310d lsb
    S5K4E1GA_OTP_310E_MSB,//reg 0x310e msb
    S5K4E1GA_OTP_310E_LSB,//reg 0x310e lsb
    S5K4E1GA_OTP_310F_MSB,//reg 0x310f msb
    S5K4E1GA_OTP_310F_LSB,//reg 0x310f lsb
    S5K4E1GA_OTP_MAX,//no otp
}s5k4e1ga_otp_location;

#define S5K4E1GA_LSB  0x0f
#define S5K4E1GA_MSB  0xf0

//HUAWEIMODULE ID 23060132
#define CAMERA_ID 0x84//0xAA //HUAWEIMODULE ID 23060170

//supplier id: sunny is 0x2
#define CAMERA_SUPPLIER_ID 0x2

//awb otp start layer
#define S5K4E1GA_LAYER_AWB_START  18

//awb otp end layer
#define S5K4E1GA_LAYER_AWB_END  35

//number of AWB layers
#define S5K4E1GA_LAYER_AWB_NUMS  (S5K4E1GA_LAYER_AWB_END - S5K4E1GA_LAYER_AWB_START +1)

//R/G and B/G value of Golden Samples.
static const u16 RG_Ratio_Typical = 0x30c;//average of the three golden samples with 23060132
static const u16 BG_Ratio_Typical = 0x2b1;//average of the three golden samples with 23060132

//Final r/g/g gain
static u16 gR_gain = 0;
static u16 gG_gain = 0;
static u16 gB_gain = 0;

//OTP read indications
static  u8 s5k4e1ga_otp_read_flag = 0x00;

#define S5K4E1GA_OTP_VALID  0x01

static bool s5k4e1ga_update_otp(void);
static int s5k4e1ga_set_otp_awb_gain(u16 R_gain, u16 G_gain, u16 B_gain);

#endif  //S5K4E1GA_USE_OTP
extern u32 get_slave_sensor_id(void);

static const struct isp_reg_t isp_init_regs_s5k4e1ga_sunny[] = {
};

/*
 * should be calibrated, three lights, from 0x1c264
 * here is long exposure
 */
static char s5k4e1ga_sunny_lensc_param[86*3] = {
};

/* should be calibrated, 6 groups 3x3, from 0x1c1d8 */
static short s5k4e1ga_sunny_ccm_param[54] = {
};

static char s5k4e1ga_sunny_awb_param[] = {
};

/******************effect begin*************************/
static effect_params effect_s5k4e1ga_sunny_cherryplus = {
#include "cherryplus/effect_s5k4e1ga_sunny_cherryplus.h"
};

static effect_params effect_s5k4e1ga_sunny_chm = {
#include "chm/effect_s5k4e1ga_sunny_chm.h"
};

static effect_params effect_s5k4e1ga_sunny_alice = {
#include "alice/effect_s5k4e1ga_sunny_alice.h"
};
/*******************effect end*************************/
static const struct _sensor_reg_t s5k4e1ga_sunny_stream_off_regs[] = {
	{0x0100, 0x00}
};
static const sensor_config_s s5k4e1ga_sunny_config_settings[]= {
    {
        "cherryplus",
        {s5k4e1ga_sunny_cherryplus_init_array,  ARRAY_SIZE(s5k4e1ga_sunny_cherryplus_init_array) },
        {s5k4e1ga_sunny_cherryplus_framesizes, ARRAY_SIZE(s5k4e1ga_sunny_cherryplus_framesizes)},
        &effect_s5k4e1ga_sunny_cherryplus,
        NULL,
    },

    {
        "chm",
        {s5k4e1ga_sunny_chm_init_array,  ARRAY_SIZE(s5k4e1ga_sunny_chm_init_array) },
        {s5k4e1ga_sunny_chm_framesizes, ARRAY_SIZE(s5k4e1ga_sunny_chm_framesizes)},
        &effect_s5k4e1ga_sunny_chm,
        NULL,
    },

    {
        "alice",
        {s5k4e1ga_sunny_alice_init_array,  ARRAY_SIZE(s5k4e1ga_sunny_alice_init_array) },
        {s5k4e1ga_sunny_alice_framesizes, ARRAY_SIZE(s5k4e1ga_sunny_alice_framesizes)},
        &effect_s5k4e1ga_sunny_alice,
        NULL,
    },

    {
        "cherrypro",
        {s5k4e1ga_sunny_cherryplus_init_array,  ARRAY_SIZE(s5k4e1ga_sunny_cherryplus_init_array) },
        {s5k4e1ga_sunny_cherryplus_framesizes, ARRAY_SIZE(s5k4e1ga_sunny_cherryplus_framesizes)},
        &effect_s5k4e1ga_sunny_cherryplus,
        NULL,
    },
};
static const sensor_config_s* s5k4e1ga_sunny_config = s5k4e1ga_sunny_config_settings;

static camera_capability s5k4e1ga_cap[] = {
    {V4L2_CID_FOCAL_LENGTH, 238},//2.38mm
    {V4L2_CID_ZSL,S5K4E1GA_ZSL},
    {V4L2_CID_HORIZONTAL_VIEW_ANGLE, 7526},//add FOV angel
    {V4L2_CID_VERTICAL_VIEW_ANGLE, 5958},
};
static camera_sensor s5k4e1ga_sunny_sensor;
static void s5k4e1ga_sunny_set_default(void);

static int s5k4e1ga_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(s5k4e1ga_cap) / sizeof(s5k4e1ga_cap[0]); ++i) {
		if (id == s5k4e1ga_cap[i].id) {
			*value = s5k4e1ga_cap[i].value;
			break;
		}
	}
	return 0;
}
/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_read_reg;
 * Description : read s5k4e1ga_sunny reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(s5k4e1ga_sunny_sensor.i2c_config.index,
				 s5k4e1ga_sunny_sensor.i2c_config.addr, reg, (u16 *)val, s5k4e1ga_sunny_sensor.i2c_config.val_bits,s5k4e1ga_sunny_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_write_reg;
 * Description : write s5k4e1ga_sunny reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(s5k4e1ga_sunny_sensor.i2c_config.index,
			s5k4e1ga_sunny_sensor.i2c_config.addr, reg, val, s5k4e1ga_sunny_sensor.i2c_config.val_bits, mask,s5k4e1ga_sunny_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int s5k4e1ga_sunny_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(s5k4e1ga_sunny_sensor.i2c_config.index,
			s5k4e1ga_sunny_sensor.i2c_config.addr, seq, size, s5k4e1ga_sunny_sensor.i2c_config.val_bits, mask,s5k4e1ga_sunny_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void s5k4e1ga_sunny_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}

#ifdef S5K4E1GA_USE_OTP

/******************************************************************************
Function:        // s5k4e1ga_start_otp_read
Description:    // send command to IC to start OTP read process. Must call this function before
                     //OTP read!
Input:            //
Output:         //
Return:         //
Others:         //
******************************************************************************/
static void s5k4e1ga_start_otp_read(void)
{
    //OTP start read process
    s5k4e1ga_sunny_write_reg(0x30f9, 0x0f, 0x00);
    s5k4e1ga_sunny_write_reg(0x30fa, 0x0a, 0x00);
    s5k4e1ga_sunny_write_reg(0x30fb, 0x71, 0x00);
    s5k4e1ga_sunny_write_reg(0x30fb, 0x70, 0x00);

    mdelay(5);//must delay
}

/******************************************************************************
Function:        // s5k4e1ga_check_awb_otp_location
Description:    // find which location otp lays in
Input:            //
Output:         //
Return:         //location in which otp lays, or S5K4E1GA_OTP_NONE for no otp
Others:         //
******************************************************************************/
static s5k4e1ga_otp_location s5k4e1ga_check_awb_otp_location(void)
{
    u8 reg310D = 0;//reg 0x310d value
    u8 reg310E = 0;//reg 0x310e value
    u8 reg310F = 0;//reg 0x310f value


    s5k4e1ga_sunny_write_reg(0x310c, 18, 0x00);//use layer 18 to find which location OTP data lays in

    s5k4e1ga_sunny_read_reg(0x310d, &reg310D);
    s5k4e1ga_sunny_read_reg(0x310e, &reg310E);
    s5k4e1ga_sunny_read_reg(0x310f, &reg310F);

    print_debug("%s read layer 18: reg310D:0x%x, reg310E:0x%x, reg310F:0x%x \n", __func__, reg310D, reg310E, reg310F);

    //find which reg postion otp lays in, from right to left
    if (reg310D & S5K4E1GA_LSB)
    {
        return S5K4E1GA_OTP_310D_LSB;
    }
    else if (reg310E & S5K4E1GA_MSB)
    {
        return S5K4E1GA_OTP_310E_MSB;
    }
    else if (reg310E & S5K4E1GA_LSB)
    {
        return S5K4E1GA_OTP_310E_LSB;
    }
    else if (reg310F & S5K4E1GA_MSB)
    {
        return S5K4E1GA_OTP_310F_MSB;
    }
    else if (reg310F & S5K4E1GA_LSB)
    {
        return S5K4E1GA_OTP_310F_LSB;
    }
    else
    {
        print_error("%s Error! No data in OTP! \n", __func__);
        return S5K4E1GA_OTP_MAX;
    }
}
/******************************************************************************
Function:        // s5k4e1ga_read_otp_regs
Description:    // According the locaion, read the otp mem
Input:            //reg: regs to read otp, isMsb: msb or lsb
Output:         //current_otp:otp readed
Return:         //
Others:         //
******************************************************************************/
static void s5k4e1ga_read_otp_regs(struct s5k4e1ga_otp_struct *current_otp, u16 reg, bool isMsb)
{
    u8 layer =0;
    u8 i= 0;
    u8 regValues[S5K4E1GA_LAYER_AWB_NUMS] = {0xff};

    memset(regValues,0xff,S5K4E1GA_LAYER_AWB_NUMS);

    print_debug("%s reg:0x%x, isMsb:%d ", __func__, reg, isMsb);

    for (layer = S5K4E1GA_LAYER_AWB_START; layer <= S5K4E1GA_LAYER_AWB_END; layer++,i++)
    {
        s5k4e1ga_sunny_write_reg(0x310c, layer, 0x00);//set layer
        s5k4e1ga_sunny_read_reg(reg, &regValues[i]);//read specific reg value

        if (true == isMsb)//MSB
        {
            regValues[i] =  (regValues[i] & S5K4E1GA_MSB) >> 4 ;
        }
        else//LSB
        {
            regValues[i] =  regValues[i] & S5K4E1GA_LSB;
        }

        print_debug("%s regValues[%d]:0x%x", __func__, i, regValues[i]);
    }

    //copy the readed data into OTP struct according to otp map
    //awb 16bit
    current_otp->product_year        = (regValues[0] <<4) + regValues[1];
    current_otp->product_month       = (regValues[2] <<4) + regValues[3];
    current_otp->product_date        = (regValues[4] <<4) + regValues[5];
    current_otp->camera_id           = (regValues[6] <<4) + regValues[7];
    current_otp->supplier_version_id = regValues[8];
    current_otp->version             = regValues[9];

    current_otp->wb_rg               = (regValues[10] <<12) + (regValues[11] <<8)
                                               + (regValues[12] <<4) + regValues[13];
    current_otp->wb_bg               = (regValues[14] <<12) + (regValues[15] <<8)
                                               + (regValues[16] <<4) + regValues[17];
	return;
}


/******************************************************************************
Function:        // s5k4e1ga_read_awb_otp
Description:    // According the locaion, read the otp mem
Input:            //location: where otp lays in
Output:         //current_otp:otp readed
Return:         //
Others:         //
******************************************************************************/
static bool s5k4e1ga_read_awb_otp(s5k4e1ga_otp_location location, struct s5k4e1ga_otp_struct *current_otp)
{
    if (location >= S5K4E1GA_OTP_MAX)//invalid location
    {
        print_error("%s Error! Invalid OTP location:%d \n", __func__, location);
        return false;
    }
    print_debug("%s location:%d \n", __func__, location);
    //read otp regs according to the locations
    switch (location)
    {
        case S5K4E1GA_OTP_310D_LSB:
            s5k4e1ga_read_otp_regs(current_otp, 0x310d, false);
            break;
        case S5K4E1GA_OTP_310E_MSB:
            s5k4e1ga_read_otp_regs(current_otp, 0x310e, true);
            break;
        case S5K4E1GA_OTP_310E_LSB:
            s5k4e1ga_read_otp_regs(current_otp, 0x310e, false);
            break;
        case S5K4E1GA_OTP_310F_MSB:
            s5k4e1ga_read_otp_regs(current_otp, 0x310f, true);
            break;
        case S5K4E1GA_OTP_310F_LSB:
            s5k4e1ga_read_otp_regs(current_otp, 0x310f, false);
            break;
        default:
            return false;
    }

    return true;
}

/******************************************************************************
Function:        // s5k4e1ga_otp_debug
Description:    // print the otp content for debug
Input:            //otp_ptr: otp mem ptr
Output:         //NA
Return:         //NA
Others:         //NA
******************************************************************************/
static void s5k4e1ga_otp_debug(struct s5k4e1ga_otp_struct* otp_ptr)
{
    if(NULL == otp_ptr)
    {
        print_error("%s, FAILED. otp_ptr is NULL!!",__func__);
        return;
    }

    print_info("%s,otp_ptr->product_year:0x%x",__func__,otp_ptr->product_year);
    print_info("%s,otp_ptr->product_month:0x%x",__func__,otp_ptr->product_month);
    print_info("%s,otp_ptr->product_date:0x%x",__func__,otp_ptr->product_date);
    print_info("%s,otp_ptr->camera_id:0x%x",__func__,otp_ptr->camera_id);
    print_info("%s,otp_ptr->supplier_version_id:0x%x",__func__,otp_ptr->supplier_version_id);
    print_info("%s,otp_ptr->version:0x%x\n",__func__,otp_ptr->version);

    print_info("%s,otp_ptr->wb_rg:0x%x",__func__,otp_ptr->wb_rg);
    print_info("%s,otp_ptr->wb_bg:0x%x",__func__,otp_ptr->wb_bg);
    return;
}

/******************************************************************************
Function:        // s5k4e1ga_set_otp_awb_gain
Description:    // write otp rgb gain on the sensor
Input:            //R_gain: red gain  G_gain: green gain  B_gain: blue gain
Output:         //NA
Return:         //NA
Others:         //NA
******************************************************************************/
static int s5k4e1ga_set_otp_awb_gain(u16 R_gain, u16 G_gain, u16 B_gain)
{
    print_info("%s, R_gain:0x%x,G_gain:0x%x,B_gain:0x%x\n",__func__,R_gain,G_gain,B_gain);
    if (R_gain>=0x100) {
        s5k4e1ga_sunny_write_reg(0x0210, R_gain>>8, 0x00);
        s5k4e1ga_sunny_write_reg(0x0211, R_gain & 0x00ff, 0x00);
    }
    //G gain include Gr gain and Gb gain
    if (G_gain>=0x100) {
        s5k4e1ga_sunny_write_reg(0x020e, G_gain>>8, 0x00);
        s5k4e1ga_sunny_write_reg(0x020f, G_gain & 0x00ff, 0x00);

        s5k4e1ga_sunny_write_reg(0x0214, G_gain>>8, 0x00);
        s5k4e1ga_sunny_write_reg(0x0215, G_gain & 0x00ff, 0x00);
    }

    if (B_gain>=0x100) {
        s5k4e1ga_sunny_write_reg(0x0212, B_gain>>8, 0x00);
        s5k4e1ga_sunny_write_reg(0x0213, B_gain & 0x00ff, 0x00);
    }

    return 0;
}

/******************************************************************************
Function:        // s5k4e1ga_update_otp
Description:    // check read and update the OTP content.
Input:            //NA
Output:         //
Return:         //true: update successfully; false:no OTP
Others:         //
******************************************************************************/
static bool s5k4e1ga_update_otp(void)
{
    struct s5k4e1ga_otp_struct current_otp;

    u16 R_gain=0, G_gain=0, B_gain=0, G_gain_R=0, G_gain_B=0;
    u16 rg=0, bg=0;

    s5k4e1ga_otp_location awbOtpLocation = S5K4E1GA_OTP_MAX;

    memset(&current_otp, 0, sizeof(struct s5k4e1ga_otp_struct));

    print_debug("%s Start!\n", __func__);

    //send read commnad to IC
    s5k4e1ga_start_otp_read();

    //check AWB OTP location
    awbOtpLocation = s5k4e1ga_check_awb_otp_location();

    if (false == s5k4e1ga_read_awb_otp(awbOtpLocation, &current_otp))
    {
        print_error("%s Error!no data in OTP!\n", __func__);
        return false;
    }

    s5k4e1ga_otp_debug(&current_otp);

    //validate the OTP content, return false if invalid
    if( ( CAMERA_ID != current_otp.camera_id ) ||
		( CAMERA_SUPPLIER_ID != current_otp.supplier_version_id ) ||
	    ( 0 == current_otp.wb_rg ) ||
	    ( 0 == current_otp.wb_bg )  )
    {
        print_error("%s, INVALID OTP.camera_id:0x%x, camera_id:0x%x,supplier_id:0x%x,RG:0x%x,BG: 0x%x\n",__func__,
			current_otp.camera_id, current_otp.supplier_version_id, current_otp.wb_rg, current_otp.wb_bg);
        return false;
    }
    rg = current_otp.wb_rg;
    bg =  current_otp.wb_bg;

    //calculate RGB gain
    //0x100 = 1x gain
    if(bg < BG_Ratio_Typical) {
        if (rg< RG_Ratio_Typical) {
            G_gain = 0x100;
            B_gain = (0x100 * BG_Ratio_Typical) / bg;
            R_gain = (0x100 * RG_Ratio_Typical) / rg;
        }
        else {
            R_gain = 0x100;
            G_gain = (0x100 * rg) / RG_Ratio_Typical;
            B_gain = (G_gain * BG_Ratio_Typical) /bg;
        }
    }
    else {
        if (rg < RG_Ratio_Typical) {
            B_gain = 0x100;
            G_gain = (0x100 * bg) / BG_Ratio_Typical;
            R_gain = (G_gain * RG_Ratio_Typical) / rg;
        }
        else {
            G_gain_B = (0x100 * bg) / BG_Ratio_Typical;
            G_gain_R = (0x100 * rg) / RG_Ratio_Typical;

            if(G_gain_B > G_gain_R ) {
                B_gain = 0x100;
                G_gain = G_gain_B;
                R_gain = (G_gain * RG_Ratio_Typical) /rg;
            }
            else {
                R_gain = 0x100;
                G_gain = G_gain_R;
                B_gain = (G_gain * BG_Ratio_Typical) / bg;
            }
        }
    }

    print_debug("%s,: R_gain:0x%x,G_gain:0x%x,B_gain:0x%x\n", __func__,R_gain,G_gain,B_gain);

    gR_gain = R_gain;
    gG_gain = G_gain;
    gB_gain = B_gain;
    s5k4e1ga_otp_read_flag = S5K4E1GA_OTP_VALID;

    print_debug("%s END!", __func__);

    return true;
}
#endif //S5K4E1GA_USE_OTP
/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_enum_frame_intervals(struct v4l2_frmivalenum *fi)
{
	assert(fi);

	if(NULL == fi) {
		return -EINVAL;
	}

	print_debug("enter %s", __func__);
	if (fi->index >= CAMERA_MAX_FRAMERATE) {
		return -EINVAL;
	}

	fi->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fi->discrete.numerator = 1;
	fi->discrete.denominator = (fi->index+1);
	return 0;
}


/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY) {
		fmt->pixelformat = s5k4e1ga_sunny_sensor.fmt[STATE_PREVIEW];
	} else {
		fmt->pixelformat = s5k4e1ga_sunny_sensor.fmt[STATE_CAPTURE];
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;

	u32 this_max_index =   s5k4e1ga_sunny_config->framesizes.size-1;
	framesize_s * s5k4e1ga_sunny_framesizes = s5k4e1ga_sunny_config->framesizes.framesize_setting;
	assert(framesizes);

	if(NULL == framesizes) {
		return -EINVAL;
	}

	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > s5k4e1ga_sunny_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > s5k4e1ga_sunny_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = s5k4e1ga_sunny_framesizes[this_max_index].width;
	framesizes->discrete.height = s5k4e1ga_sunny_framesizes[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = s5k4e1ga_sunny_config->framesizes.size - 1;
	framesize_s * s5k4e1ga_sunny_framesizes =  s5k4e1ga_sunny_config->framesizes.framesize_setting;

	assert(framesizes);

	if(NULL == framesizes) {
		return -EINVAL;
	}

	print_debug("Enter Function:%s  ", __func__);


	if ((framesizes->discrete.width <= s5k4e1ga_sunny_framesizes[max_index].width)
	    && (framesizes->discrete.height <= s5k4e1ga_sunny_framesizes[max_index].height)) {
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
 * FunctionName: s5k4e1ga_sunny_init_isp_reg;
 * Description : load initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_init_isp_reg(void)
{
	int size = 0;

	camera_sensor *sensor = &s5k4e1ga_sunny_sensor;

        size = CAMERA_MAX_SETTING_SIZE;

        s5k4e1ga_sunny_write_isp_seq(sensor->effect->isp_settings, size);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_set_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type,bool zsl_preview)
{
	int i = 0;
	bool match = false;
	int size = 0;

	framesize_s * s5k4e1ga_sunny_framesizes = NULL;
	assert(fs);

	if(NULL == fs) {
		return -EINVAL;
	}

	print_debug("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
		    __func__, state, flag, fs->width, fs->height);

	size = s5k4e1ga_sunny_config->framesizes.size;
	s5k4e1ga_sunny_framesizes = s5k4e1ga_sunny_config->framesizes.framesize_setting;
	if (VIEW_FULL == view_type) {
		for (i = 0; i < size; i++) {
			if ((s5k4e1ga_sunny_framesizes[i].width >= fs->width)
			    && (s5k4e1ga_sunny_framesizes[i].height >= fs->height)
			    && (VIEW_FULL == s5k4e1ga_sunny_framesizes[i].view_type)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= s5k4e1ga_sunny_framesizes[i].resolution_type)) {
				fs->width = s5k4e1ga_sunny_framesizes[i].width;
				fs->height = s5k4e1ga_sunny_framesizes[i].height;
				match = true;
				break;
			}
		}
	}

	if (false == match) {
		for (i = 0; i < size; i++) {
			if ((s5k4e1ga_sunny_framesizes[i].width >= fs->width)
			    && (s5k4e1ga_sunny_framesizes[i].height >= fs->height)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= s5k4e1ga_sunny_framesizes[i].resolution_type)) {
				fs->width = s5k4e1ga_sunny_framesizes[i].width;
				fs->height = s5k4e1ga_sunny_framesizes[i].height;
				break;
			}
		}
	}

	if (i >= size) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW) {
		s5k4e1ga_sunny_sensor.preview_frmsize_index = i;
	} else {
		s5k4e1ga_sunny_sensor.capture_frmsize_index = i;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_get_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;
	framesize_s * s5k4e1ga_sunny_framesizes = NULL;

	assert(fs);

	if(NULL == fs) {
		return -EINVAL;
	}
	s5k4e1ga_sunny_framesizes = s5k4e1ga_sunny_config->framesizes.framesize_setting;
	if (state == STATE_PREVIEW) {
		frmsize_index = s5k4e1ga_sunny_sensor.preview_frmsize_index;
	} else if (state == STATE_CAPTURE) {
		frmsize_index = s5k4e1ga_sunny_sensor.capture_frmsize_index;
	} else {
		return -EINVAL;
	}
	fs->width = s5k4e1ga_sunny_framesizes[frmsize_index].width;
	fs->height = s5k4e1ga_sunny_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_init_reg(void)
{
	int size = 0;
	const sensor_reg_t* s5k4e1ga_sunny_init_regs = NULL;

	print_debug("Enter Function:%s  , initsize=%d",
		    __func__, s5k4e1ga_sunny_config->init_setting.settings[0].seq_size);
#if 0
         size = CAMERA_MAX_SETTING_SIZE;
	s5k4e1ga_sunny_write_isp_seq(sensor->effect->isp_settings, size);
#endif
	if (0 != k3_ispio_init_csi(s5k4e1ga_sunny_sensor.mipi_index,
				 s5k4e1ga_sunny_sensor.mipi_lane_count, s5k4e1ga_sunny_sensor.lane_clk)) {
		return -EFAULT;
	}

    //init dphy setting
	k3_ispio_config_lane_clk(s5k4e1ga_sunny_sensor.mipi_index, s5k4e1ga_sunny_sensor.mipi_lane_count, s5k4e1ga_sunny_sensor.lane_clk);

	size = s5k4e1ga_sunny_config->init_setting.settings[0].seq_size;
	s5k4e1ga_sunny_init_regs = s5k4e1ga_sunny_config->init_setting.settings[0].setting;

	if (0 != s5k4e1ga_sunny_write_seq(s5k4e1ga_sunny_init_regs, size, 0x00)) {
		print_error("fail to init s5k4e1ga_sunny sensor");
		return -EFAULT;
	}

	if(CAMERA_SENSOR_FLIP_TYPE_H_V == video_get_secondary_sensor_flip_type()) {
		s5k4e1ga_sunny_write_reg(S5K4E1GA_FLIP, 0x03, 0x00); //turn camera layout
		print_info("%s:change flip and mirror", __func__);
	}
#ifdef S5K4E1GA_USE_OTP
    if ( S5K4E1GA_OTP_VALID == s5k4e1ga_otp_read_flag ){
	  s5k4e1ga_set_otp_awb_gain(gR_gain, gG_gain, gB_gain);
    } else {
        print_error("%s:otp failed", __func__);
    }
#endif //S5K4E1GA_USE_OTP
	return 0;
}

static int s5k4e1ga_update_flip(u16 width, u16 height)
{
	u8 new_flip;
	u8 old_flip;

	print_info("Enter %s  ", __func__);

	new_flip = ((s5k4e1ga_sunny_sensor.vflip << 1) | s5k4e1ga_sunny_sensor.hflip);
	old_flip = s5k4e1ga_sunny_sensor.old_flip;
	if (old_flip != new_flip) { 
		k3_ispio_update_flip((s5k4e1ga_sunny_sensor.old_flip ^ new_flip) & 0x03, width, height, (old_flip ^ new_flip) & 0x03);
   		print_info("secondary_sensor_flip_type = %d", video_get_secondary_sensor_flip_type());

		if(CAMERA_SENSOR_FLIP_TYPE_H_V == video_get_secondary_sensor_flip_type()){
			s5k4e1ga_sunny_write_reg(S5K4E1GA_FLIP, s5k4e1ga_sunny_sensor.vflip ? 0x00 : 0x02, ~0x02);
			s5k4e1ga_sunny_write_reg(S5K4E1GA_FLIP, s5k4e1ga_sunny_sensor.hflip ? 0x00 : 0x01, ~0x01);
		}else{
			s5k4e1ga_sunny_write_reg(S5K4E1GA_FLIP, s5k4e1ga_sunny_sensor.vflip ? 0x02 : 0x00, ~0x02);
			s5k4e1ga_sunny_write_reg(S5K4E1GA_FLIP, s5k4e1ga_sunny_sensor.hflip ? 0x01 : 0x00, ~0x01);
		}
	s5k4e1ga_sunny_sensor.old_flip = new_flip;
	}
	return 0;
}

static int s5k4e1ga_sunny_get_sensor_aperture(void)
{
	return S5K4E1GA_SUNNY_APERTURE_FACTOR;
}

static int s5k4e1ga_sunny_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	s5k4e1ga_sunny_sensor.hflip = flip;
	return 0;
}
static int s5k4e1ga_sunny_get_hflip(void)
{
	print_debug("enter %s", __func__);

	return s5k4e1ga_sunny_sensor.hflip;
}
static int s5k4e1ga_sunny_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);

	s5k4e1ga_sunny_sensor.vflip = flip;

	return 0;
}
static int s5k4e1ga_sunny_get_vflip(void)
{
	print_debug("enter %s", __func__);
	return s5k4e1ga_sunny_sensor.vflip;
}

/* **************************************************************************
  * FunctionName: s5k4e1ga_foxconn_dump_reg_debug;
  * Description : dump standby, frame count, cap relate reg for debug
  * Input       : NA;
  * Output      : NA;
  * ReturnValue : NA;
  * Other       : NA;
  ***************************************************************************/
static void s5k4e1ga_sunny_dump_reg_debug(void)
{
      u16 reg = 0;
      u8 val = 0;

      reg=0x0100;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      //frame count
      reg=0x0005;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      // x_start
      reg=0x0344;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x0345;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      //y_start
      reg=0x0346;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x0347;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      //x_end
      reg=0x0348;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x0349;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      //y_end
      reg=0x034a;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x034b;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      //x_output size
      reg=0x034c;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x034d;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      //y_output size
      reg=0x034e;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x034f;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x301b;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x30a9;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x300e;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x0387;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x30c0;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x30c8;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x30c9;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x0340;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x0341;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x3098;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x309b;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
      reg=0x309c;s5k4e1ga_sunny_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_framesize_switch(camera_state state)
{
	u8 next_frmsize_index;
	u32 size = s5k4e1ga_sunny_config->framesizes.size;


	if (state == STATE_PREVIEW)
		next_frmsize_index = s5k4e1ga_sunny_sensor.preview_frmsize_index;
	else
		next_frmsize_index = s5k4e1ga_sunny_sensor.capture_frmsize_index;

	print_debug("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

	if (next_frmsize_index >= size){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -ETIME;
	}

	if (0 != s5k4e1ga_sunny_write_seq( s5k4e1ga_sunny_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		, s5k4e1ga_sunny_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init s5k4e1ga_sunny sensor");
		return -ETIME;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_stream_on;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_stream_on(camera_state state)
{
	print_debug("Enter Function:%s ", __func__);
	return s5k4e1ga_sunny_framesize_switch(state);
}


/*  **************************************************************************
* FunctionName: s5k4e1ga_sunny_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int s5k4e1ga_sunny_check_sensor(void)
{
	u8 idl = 0;
	u8 idh = 0;
	u16 id = 0;
	int retry = 0;
	msleep(3);
    for(retry = 0; retry < S5K4E1GA_SUNNY_I2C_RETRY_TIMES; retry++) {
    	s5k4e1ga_sunny_read_reg(0x0000, &idh);
    	s5k4e1ga_sunny_read_reg(0x0001, &idl);

    	id = ((idh << 8) | idl);
    	print_info("s5k4e1ga_sunny product id:0x%x, retrytimes:%d", id, retry);
        if(S5K4E1GA_SUNNY_CHIP_ID == id) {
            break;
        }
        udelay(100);
    }
	if (S5K4E1GA_SUNNY_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor s5k4e1ga_sunny");
		return -ENODEV;
	}
//get otp after check sensor
#ifdef S5K4E1GA_USE_OTP
    if ( S5K4E1GA_OTP_VALID != s5k4e1ga_otp_read_flag ){
        s5k4e1ga_update_otp();
    }
#endif


	return 0;
}

/****************************************************************************
* FunctionName: s5k4e1ga_sunny_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int s5k4e1ga_sunny_power(camera_power_state power)
{
	int ret = 0;

	if (power == POWER_ON) {
		//k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
		k3_socgpio_power_sensor(1, S_CAMERA_ANALOG_VDD);//for external AVDD LDO
		k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);//power on main sensor's DVDD

		k3_ispio_ioconfig(&s5k4e1ga_sunny_sensor, power);
	} else {
		k3_ispio_deinit_csi(s5k4e1ga_sunny_sensor.mipi_index);
		k3_ispio_ioconfig(&s5k4e1ga_sunny_sensor, power);

		k3_socgpio_power_sensor(0, S_CAMERA_ANALOG_VDD);//for external AVDD LDO
		k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
		//k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
		k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);//power off main sensor' DVDD
	}

	return ret;
}

static void s5k4e1ga_sunny_set_gain(u32 gain)
{
       if (gain == 0)
	{
              print_error("%s set gain error, gain value 0x%x", __func__, gain);
		return;
       }
	gain = gain << 1;
	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_GAIN_REG_L, gain & 0xff, 0x00);
}
static void s5k4e1ga_sunny_set_exposure_gain(u32 exposure, u32 gain)
{
	if(gain == 0)
	{
	       print_error("%s set gain error, gain value 0x%x", __func__, gain);
		return;
	}
	s5k4e1ga_sunny_write_reg(0x0104, 0x01, 0x00);//hold on

	//print_info("enter %s, gain: 0x%x, exposure: 0x%x", __func__, gain, exposure);

/*	
	if(s5k4e1ga_sunny_sensor.vts_change == 1)
	{
		vts = s5k4e1ga_sunny_sensor.vts_value;
		s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
		s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_VTS_REG_L, vts & 0xff, 0x00);
		s5k4e1ga_sunny_sensor.vts_change = 0;
	}
*/	
	gain = gain << 1;

	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_GAIN_REG_L, gain & 0xff, 0x00);

	exposure = exposure >> 4;
	//print_info("enter %s, expo:%d", __func__, exposure);
	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_EXPOSURE_REG_L, exposure & 0xff, 0x00);

	s5k4e1ga_sunny_write_reg(0x0104, 0x00, 0x00);//hold off

	return;
}

static void s5k4e1ga_sunny_set_exposure(u32 exposure)
{
	exposure = exposure >> 4;
	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_EXPOSURE_REG_L, exposure & 0xff, 0x00);
}

static void s5k4e1ga_sunny_set_vts(u16 vts)
{
	print_debug("Enter %s  ", __func__);
//	if(s5k4e1ga_sunny_sensor.vts_change != 1)
//	{
	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	s5k4e1ga_sunny_write_reg(S5K4E1GA_SUNNY_VTS_REG_L, vts & 0xff, 0x00);
//	}
//	s5k4e1ga_sunny_sensor.vts_value = vts;
}

/*
void s5k4e1ga_sunny_set_vts_change(u16 change)
{
	print_info("Enter %s change=%d ", __func__,change);
	s5k4e1ga_sunny_sensor.vts_change = change;
}
*/
static u32 s5k4e1ga_sunny_get_vts_reg_addr(void)
{
	return S5K4E1GA_SUNNY_VTS_REG_H;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_reset( camera_power_state power_state)
{
	print_info("%s  ", __func__);
	s5k4e1ga_sunny_sensor.old_flip = 0;
	if (POWER_ON == power_state) {
		k3_isp_io_enable_mclk(MCLK_ENABLE, s5k4e1ga_sunny_sensor.sensor_index);
		k3_ispgpio_reset_sensor(s5k4e1ga_sunny_sensor.sensor_index, power_state,
			      s5k4e1ga_sunny_sensor.power_conf.reset_valid);
		udelay(500);
	} else {
		k3_ispgpio_reset_sensor(s5k4e1ga_sunny_sensor.sensor_index, power_state,
			      s5k4e1ga_sunny_sensor.power_conf.reset_valid);
		udelay(10);
		k3_isp_io_enable_mclk(MCLK_DISABLE, s5k4e1ga_sunny_sensor.sensor_index);
	}

	return 0;
}


/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_init;
 * Description : s5k4e1ga_sunny init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1ga_sunny_init(void)
{
    static bool s5k4e1ga_check = false;
    int ret = 0;
    print_debug("%s  ", __func__);

    if (false == s5k4e1ga_check) {
        if (video_check_suspensory_camera("s5k4e1ga_sensor") != 1) {
            print_error("%s: product not have this sensor", __func__);
            return -ENODEV;     
        }

        ret = camera_get_matching_sensor_config(s5k4e1ga_sunny_config_settings, ARRAY_SIZE(s5k4e1ga_sunny_config_settings),&s5k4e1ga_sunny_config);
        if( ret < 0 ){
            print_error("%s: fail to match sensor config.", __func__);
           return -ENODEV;
        } else {
            print_info("%s: choose the %s's setting.",__func__,s5k4e1ga_sunny_config->product);
        }

        s5k4e1ga_sunny_sensor.frmsize_list = s5k4e1ga_sunny_config->framesizes.framesize_setting;
        s5k4e1ga_sunny_sensor.effect = s5k4e1ga_sunny_config->effect;
        s5k4e1ga_sunny_sensor.lane_clk = s5k4e1ga_sunny_config->framesizes.framesize_setting[0].lane_clk;

        s5k4e1ga_check = true;
    }

    k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - sec camera*/
    k3_ispio_power_init(S_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - sec camera*/
    //k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);	/*core 1.8V - sec camera*/
    k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_12V, LDO_VOLTAGE_12V);	/*core 1.05V - pri camera*/


    return 0;
}

static u32 s5k4e1ga_get_override_param(camera_override_type_t type)
{
	u32 ret_val = sensor_override_params[type];

	switch (type) {
	case OVERRIDE_ISO_HIGH:
		ret_val = S5K4E1GA_MAX_ISO;
		break;

	case OVERRIDE_ISO_LOW:
		ret_val = S5K4E1GA_MIN_ISO;
		break;

	/* increase frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_LOW2MID:
		ret_val = S5K4E1GA_AUTOFPS_GAIN_LOW2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2HIGH:
		ret_val = S5K4E1GA_AUTOFPS_GAIN_MID2HIGH;
		break;

	/* reduce frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_MID2LOW:
		ret_val = S5K4E1GA_AUTOFPS_GAIN_MID2LOW;
		break;
	case OVERRIDE_AUTOFPS_GAIN_HIGH2MID:
		ret_val = S5K4E1GA_AUTOFPS_GAIN_HIGH2MID;
		break;

	case OVERRIDE_FPS_MAX:
		ret_val = S5K4E1GA_MAX_FRAMERATE;
		break;

    case OVERRIDE_FPS_MID:
		ret_val = S5K4E1GA_MID_FRAMERATE;
		break;

	case OVERRIDE_FPS_MIN:
		ret_val = S5K4E1GA_MIN_FRAMERATE;
		break;

	case OVERRIDE_CAP_FPS_MIN:
		ret_val = S5K4E1GA_MIN_CAP_FRAMERATE;
		break;

	case OVERRIDE_FLASH_TRIGGER_GAIN:
		ret_val = S5K4E1GA_FLASH_TRIGGER_GAIN;
		break;

	case OVERRIDE_SHARPNESS_PREVIEW:
		ret_val = S5K4E1GA_SHARPNESS_PREVIEW;
		break;

	case OVERRIDE_SHARPNESS_CAPTURE:
		ret_val = S5K4E1GA_SHARPNESS_CAPTURE;
		break;

	default:
		print_error("%s:not override or invalid type %d, use default",__func__, type);
		break;
	}

	return ret_val;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_exit;
 * Description : s5k4e1ga_sunny exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void s5k4e1ga_sunny_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (s5k4e1ga_sunny_sensor.owner) {
		module_put(s5k4e1ga_sunny_sensor.owner);
	}
	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_shut_down;
 * Description : s5k4e1ga_sunny shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void s5k4e1ga_sunny_shut_down(void)
{
	print_debug("enter %s", __func__);
	k3_ispgpio_power_sensor(&s5k4e1ga_sunny_sensor, POWER_OFF);
}
/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_get_sensor_reg;
 * Description : read sensor's reg value;
 * Input       : reg, register to be read;
 * Output      : pvalue, value readed from reg;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static void s5k4e1ga_sunny_get_sensor_reg(int reg, int *pvalue)
{
	u8 value = 0;
	if (NULL == pvalue)
	{
		print_error("%s, NULL data pointer!", __func__);
		return;
	}
	s5k4e1ga_sunny_read_reg(reg, &value);
	*pvalue = value;
	//print_info("%s, reg:0x%x, value:0x%x", __func__, reg, *pvalue);
	return;
}
/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_set_sensor_reg;
 * Description : write sensor's reg value;
 * Input       : reg, register to be write;
 * Output      : value, value to be writen;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void s5k4e1ga_sunny_set_sensor_reg(int reg, int value)
{
	s5k4e1ga_sunny_write_reg(reg, value & 0xff, 0x00);
	return;
}
/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_check_otp;
 * Description : check otp's status;
 * Input       : NA;
 * Output      : current otp status;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void s5k4e1ga_sunny_check_otp(sensor_otp_status * status)
{
	if (NULL == status)
	{
		print_error("%s, NULL data pointer!", __func__);
		return;
	}
#ifdef S5K4E1GA_USE_OTP
	if( S5K4E1GA_OTP_VALID == s5k4e1ga_otp_read_flag ){
        *status = OTP_VALID;
    } else {
        *status = OTP_INVALID;
	}
#else
        *status = OTP_VALID;
#endif

	print_info("otp status:%d", *status);
}
static int s5k4e1ga_sunny_get_equivalent_focus(void)
{
	print_debug("enter %s", __func__);
	return S5K4E1GA_SUNNY_EQUIVALENT_FOCUS;
}
/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_set_default;
 * Description : init s5k4e1ga_sunny_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void s5k4e1ga_sunny_set_default(void)
{
	s5k4e1ga_sunny_sensor.init = s5k4e1ga_sunny_init;
	s5k4e1ga_sunny_sensor.exit = s5k4e1ga_sunny_exit;
	s5k4e1ga_sunny_sensor.shut_down = s5k4e1ga_sunny_shut_down;
	s5k4e1ga_sunny_sensor.reset = s5k4e1ga_sunny_reset;
	s5k4e1ga_sunny_sensor.check_sensor = s5k4e1ga_sunny_check_sensor;
	s5k4e1ga_sunny_sensor.power = s5k4e1ga_sunny_power;
	s5k4e1ga_sunny_sensor.init_reg = s5k4e1ga_sunny_init_reg;
	s5k4e1ga_sunny_sensor.init_isp_reg = s5k4e1ga_sunny_init_isp_reg;
	s5k4e1ga_sunny_sensor.stream_on = s5k4e1ga_sunny_stream_on;

	s5k4e1ga_sunny_sensor.get_format = s5k4e1ga_sunny_get_format;
	s5k4e1ga_sunny_sensor.set_flash = NULL;
	s5k4e1ga_sunny_sensor.get_flash = NULL;
	s5k4e1ga_sunny_sensor.set_scene = NULL;
	s5k4e1ga_sunny_sensor.get_scene = NULL;

	s5k4e1ga_sunny_sensor.enum_framesizes = s5k4e1ga_sunny_enum_framesizes;
	s5k4e1ga_sunny_sensor.try_framesizes = s5k4e1ga_sunny_try_framesizes;
	s5k4e1ga_sunny_sensor.set_framesizes = s5k4e1ga_sunny_set_framesizes;
	s5k4e1ga_sunny_sensor.get_framesizes = s5k4e1ga_sunny_get_framesizes;

	if(CAMERA_SENSOR_FLIP_TYPE_H_V == video_get_secondary_sensor_flip_type()) {
    	s5k4e1ga_sunny_sensor.sensor_rgb_type = SENSOR_GBRG;
    } else {
    	s5k4e1ga_sunny_sensor.sensor_rgb_type = SENSOR_GRBG;
    }
	s5k4e1ga_sunny_sensor.update_flip = s5k4e1ga_update_flip;

	s5k4e1ga_sunny_sensor.enum_frame_intervals = s5k4e1ga_sunny_enum_frame_intervals;
	s5k4e1ga_sunny_sensor.try_frame_intervals = NULL;
	s5k4e1ga_sunny_sensor.set_frame_intervals = NULL;
	s5k4e1ga_sunny_sensor.get_frame_intervals = NULL;

	s5k4e1ga_sunny_sensor.get_capability = NULL;

	strncpy(s5k4e1ga_sunny_sensor.info.name, "s5k4e1ga_sunny", 15);
	s5k4e1ga_sunny_sensor.interface_type = MIPI2;
	s5k4e1ga_sunny_sensor.mipi_lane_count = CSI_LINES_2;
	s5k4e1ga_sunny_sensor.mipi_index = CSI_INDEX_1;
	s5k4e1ga_sunny_sensor.sensor_index = CAMERA_SENSOR_SECONDARY;
	s5k4e1ga_sunny_sensor.skip_frames = 2; 

	s5k4e1ga_sunny_sensor.power_conf.pd_valid = LOW_VALID;
	s5k4e1ga_sunny_sensor.power_conf.reset_valid = LOW_VALID;
	s5k4e1ga_sunny_sensor.power_conf.vcmpd_valid = LOW_VALID;

	s5k4e1ga_sunny_sensor.i2c_config.index = I2C_SECONDARY;
	s5k4e1ga_sunny_sensor.i2c_config.speed = I2C_SPEED_400;
	s5k4e1ga_sunny_sensor.i2c_config.addr = S5K4E1GA_SUNNY_SLAVE_ADDRESS;
	s5k4e1ga_sunny_sensor.i2c_config.addr_bits = I2C_16BIT;
	s5k4e1ga_sunny_sensor.i2c_config.val_bits = I2C_8BIT;

	s5k4e1ga_sunny_sensor.preview_frmsize_index = 0;
	s5k4e1ga_sunny_sensor.capture_frmsize_index = 0;
	s5k4e1ga_sunny_sensor.frmsize_list = s5k4e1ga_sunny_config_settings[0].framesizes.framesize_setting;
	s5k4e1ga_sunny_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	s5k4e1ga_sunny_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;
#ifdef S5K4E1GA_SUNNY_AP_WRITEAE_MODE
	s5k4e1ga_sunny_sensor.aec_addr[0] = 0;
	s5k4e1ga_sunny_sensor.aec_addr[1] = 0;
	s5k4e1ga_sunny_sensor.aec_addr[2] = 0;
	s5k4e1ga_sunny_sensor.agc_addr[0] = 0;
	s5k4e1ga_sunny_sensor.agc_addr[1] = 0;
	s5k4e1ga_sunny_sensor.ap_writeAE_delay = 0;
#else
	s5k4e1ga_sunny_sensor.aec_addr[0] = 0x0000;
	s5k4e1ga_sunny_sensor.aec_addr[1] = 0x0202;
	s5k4e1ga_sunny_sensor.aec_addr[2] = 0x0203;
	s5k4e1ga_sunny_sensor.agc_addr[0] = 0x0204;
	s5k4e1ga_sunny_sensor.agc_addr[1] = 0x0205;
#endif
	s5k4e1ga_sunny_sensor.sensor_type = SENSOR_LIKE_SONY;
	s5k4e1ga_sunny_sensor.set_exposure_gain = s5k4e1ga_sunny_set_exposure_gain;

	s5k4e1ga_sunny_sensor.set_gain = s5k4e1ga_sunny_set_gain;
	s5k4e1ga_sunny_sensor.set_exposure = s5k4e1ga_sunny_set_exposure;
//	s5k4e1ga_sunny_sensor.set_vts_change =  s5k4e1ga_sunny_set_vts_change;
	s5k4e1ga_sunny_sensor.sensor_dump_reg = s5k4e1ga_sunny_dump_reg_debug;

	s5k4e1ga_sunny_sensor.set_vts =  s5k4e1ga_sunny_set_vts;
	s5k4e1ga_sunny_sensor.get_vts_reg_addr = s5k4e1ga_sunny_get_vts_reg_addr;

	s5k4e1ga_sunny_sensor.get_override_param = s5k4e1ga_get_override_param;

	s5k4e1ga_sunny_sensor.sensor_gain_to_iso = NULL;
	s5k4e1ga_sunny_sensor.sensor_iso_to_gain = NULL;

	s5k4e1ga_sunny_sensor.get_sensor_aperture = s5k4e1ga_sunny_get_sensor_aperture;
	s5k4e1ga_sunny_sensor.get_equivalent_focus = s5k4e1ga_sunny_get_equivalent_focus;
	s5k4e1ga_sunny_sensor.isp_location = CAMERA_USE_K3ISP;
	s5k4e1ga_sunny_sensor.sensor_tune_ops = NULL;

	s5k4e1ga_sunny_sensor.af_enable = 0;

	s5k4e1ga_sunny_sensor.image_setting.lensc_param = s5k4e1ga_sunny_lensc_param;
	s5k4e1ga_sunny_sensor.image_setting.ccm_param = s5k4e1ga_sunny_ccm_param;
	s5k4e1ga_sunny_sensor.image_setting.awb_param = s5k4e1ga_sunny_awb_param;

	s5k4e1ga_sunny_sensor.set_effect = NULL;

	s5k4e1ga_sunny_sensor.fps_max = 30;
	s5k4e1ga_sunny_sensor.fps_min = 16;
	s5k4e1ga_sunny_sensor.fps = 25;

	s5k4e1ga_sunny_sensor.owner = THIS_MODULE;

	s5k4e1ga_sunny_sensor.info.facing = CAMERA_FACING_FRONT;
	s5k4e1ga_sunny_sensor.info.orientation = 270;
	s5k4e1ga_sunny_sensor.info.focal_length = 238; /* 2.38mm*/
	s5k4e1ga_sunny_sensor.info.h_view_angle = 75;
	s5k4e1ga_sunny_sensor.info.v_view_angle = 60;
	s5k4e1ga_sunny_sensor.lane_clk = CLK_500M;
	s5k4e1ga_sunny_sensor.hflip = 0;
	s5k4e1ga_sunny_sensor.vflip = 0;
	s5k4e1ga_sunny_sensor.old_flip = 0;
	s5k4e1ga_sunny_sensor.effect =s5k4e1ga_sunny_config_settings[0].effect;
	s5k4e1ga_sunny_sensor.support_summary = false;
	//s5k4e1ga_sunny_sensor.vts_change = 0;
	s5k4e1ga_sunny_sensor.set_hflip = s5k4e1ga_sunny_set_hflip;
	s5k4e1ga_sunny_sensor.get_hflip = s5k4e1ga_sunny_get_hflip;
	s5k4e1ga_sunny_sensor.set_vflip = s5k4e1ga_sunny_set_vflip;
	s5k4e1ga_sunny_sensor.get_vflip = s5k4e1ga_sunny_get_vflip;
	s5k4e1ga_sunny_sensor.get_capability = s5k4e1ga_get_capability;

	s5k4e1ga_sunny_sensor.isp_idi_skip = false;

	s5k4e1ga_sunny_sensor.stream_off_setting = s5k4e1ga_sunny_stream_off_regs;
	s5k4e1ga_sunny_sensor.stream_off_setting_size = ARRAY_SIZE(s5k4e1ga_sunny_stream_off_regs);

    /*if there have different data rate of sensor resolution we need this config_dphy_clk 
	   otherwise if all resolution is same rate config_dphy_clk must to be null*/
	s5k4e1ga_sunny_sensor.config_dphy_clk = NULL;
	s5k4e1ga_sunny_sensor.get_sensor_reg = s5k4e1ga_sunny_get_sensor_reg;
	s5k4e1ga_sunny_sensor.set_sensor_reg = s5k4e1ga_sunny_set_sensor_reg;
	s5k4e1ga_sunny_sensor.check_otp_status = s5k4e1ga_sunny_check_otp;

}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int s5k4e1ga_sunny_module_init(void)
{
	s5k4e1ga_sunny_set_default();
	return register_camera_sensor(s5k4e1ga_sunny_sensor.sensor_index, &s5k4e1ga_sunny_sensor);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1ga_sunny_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit s5k4e1ga_sunny_module_exit(void)
{
	unregister_camera_sensor(s5k4e1ga_sunny_sensor.sensor_index, &s5k4e1ga_sunny_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(s5k4e1ga_sunny_module_init);
module_exit(s5k4e1ga_sunny_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/
