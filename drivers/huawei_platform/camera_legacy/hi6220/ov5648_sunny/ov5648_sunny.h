/*
 *  ov5648 camera driver head file
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

#ifndef _OV5648_SUNNY_H
#define _OV5648_SUNNY_H

#include "k3_isp_io.h"

#define INVMASK(v)              (0xff-v)

/***********************************************************************
 *
 * ov5648 init sensor registers list
 *
 ***********************************************************************/

const struct _sensor_reg_t ov5648_sunny_init_regs[] = {
    {0x0103, 0x01}, // soft reset
    {0x3001, 0x00}, // D[7:0] set to input
    {0x3002, 0x00}, // D[11:8] set to input
    {0x3011, 0x02}, // Drive strength 2x
    {0x3017, 0x05}, // AM05
    {0x3018, 0x4c}, // MIPI 2 lane
    {0x301c, 0xd2}, // AM05
    {0x3021, 0x22}, //                      //kenxu @ 20130912 to reduce the current change between active line period and line blanking
    {0x3022, 0x00},
    {0x3034, 0x1a}, // 10-bit mode
    {0x3035, 0x21}, // PLL                  //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x3036, 0x54}, // PLL                  //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x3037, 0x03}, // PLL
    {0x3038, 0x00}, // PLL
    {0x3039, 0x00}, // PLL
    {0x303a, 0x00}, // PLLS
    {0x303b, 0x1e}, // PLLS
    {0x303c, 0x11}, // PLLS
    {0x303d, 0x30}, // PLLS
    {0x3105, 0x11},
    {0x3106, 0x05}, // PLL
    {0x3304, 0x28},
    {0x3305, 0x41},
    {0x3306, 0x30},
    {0x3308, 0x00},
    {0x3309, 0xc8},
    {0x330a, 0x01},
    {0x330b, 0x90},
    {0x330c, 0x02},
    {0x330d, 0x58},
    {0x330e, 0x03},
    {0x330f, 0x20},
    {0x3300, 0x00},
    //{0x3500, 0x00}, // exposure [19:16]
    //{0x3501, 0x3d}, // exposure [15:8]
    //{0x3502, 0x00}, // exposure [7:0], exposure = 0x3d0 = 976
    {0x3503, 0x27}, // gain has no delay, manual agc/aec
    //{0x350a, 0x00}, // gain[9:8]
    //{0x350b, 0x40}, // gain[7:0], gain = 4x
    {0x3601, 0x33}, // analog control
    {0x3602, 0x00}, // analog control
    {0x3611, 0x0e}, // analog control
    {0x3612, 0x2b}, // analog control
    {0x3614, 0x50}, // analog control
    {0x3620, 0x33}, // analog control
    {0x3622, 0x00}, // analog control
    {0x3630, 0xad}, // analog control
    {0x3631, 0x00}, // analog control
    {0x3632, 0x94}, // analog control
    {0x3633, 0x17}, // analog control
    {0x3634, 0x14}, // analog control
    {0x3704, 0xc0}, // AM05
    {0x3705, 0x2a}, // analog control
    {0x3708, 0x66}, // analog control
    {0x3709, 0x52}, // analog control
    {0x370b, 0x23}, // analog control
    {0x370c, 0xcf}, // analog control
    {0x370d, 0x00}, // analog control
    {0x370e, 0x00}, // analog control
    {0x371c, 0x07}, // analog control
    {0x3739, 0xd2}, // analog control
    {0x373c, 0x00},
    {0x3800, 0x00}, // xstart = 0
    {0x3801, 0x00}, // xstart
    {0x3802, 0x00}, // ystart = 0
    {0x3803, 0x00}, // ystart
    {0x3804, 0x0a}, // xend = 2623
    {0x3805, 0x3f}, // yend
    {0x3806, 0x07}, // yend = 1955
    {0x3807, 0xa3}, // yend
    {0x3808, 0x05}, // x output size = 1280
    {0x3809, 0x00}, // x output size
    {0x380a, 0x03}, // y output size = 960
    {0x380b, 0xc0}, // y output size
    {0x380c, 0x05}, // 0xb00, hts = 1408  //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x380d, 0x80},                       //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x380e, 0x05}, // 0x418, vts = 1320  //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x380f, 0x28},                       //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x3810, 0x00}, // isp x win = 16
    {0x3811, 0x10}, // isp x win
    {0x3812, 0x00}, // isp y win = 10
    {0x3813, 0x0a}, // isp y win
    {0x3814, 0x31}, // x inc
    {0x3815, 0x31}, // y inc
    {0x3817, 0x00}, // hsync start
    {0x3820, 0x00}, // flip off, v bin off
    {0x3821, 0x06}, // mirror on, h bin on
    {0x3826, 0x03},
    {0x3829, 0x00},
    {0x382b, 0x0b},
    {0x3830, 0x00},
    {0x3836, 0x00},
    {0x3837, 0x00},
    {0x3838, 0x00},
    {0x3839, 0x04},
    {0x383a, 0x00},
    {0x383b, 0x01},
    {0x3b00, 0x00}, // strobe off
    {0x3b02, 0x08}, // shutter delay
    {0x3b03, 0x00}, // shutter delay
    {0x3b04, 0x04}, // frex_exp
    {0x3b05, 0x00}, // frex_exp
    {0x3b06, 0x04},
    {0x3b07, 0x08}, // frex inv
    {0x3b08, 0x00}, // frex exp req
    {0x3b09, 0x02}, // frex end option
    {0x3b0a, 0x04}, // frex rst length
    {0x3b0b, 0x00}, // frex strobe width
    {0x3b0c, 0x3d}, // frex strobe width
    {0x3f01, 0x0d},
    {0x3f0f, 0xf5},
    {0x4000, 0x89}, // blc enable
    {0x4001, 0x02}, // blc start line
    {0x4002, 0x45}, // blc auto, reset frame number = 5
    {0x4004, 0x02}, // black line number
    {0x4005, 0x18}, // blc normal freeze
    {0x4006, 0x08},
    {0x4007, 0x10},
    {0x4008, 0x00},
    {0x4050, 0x6e}, // AM05 blc level trigger
    {0x4051, 0x8f}, // blc level trigger
    {0x4300, 0xf8},
    {0x4303, 0xff},
    {0x4304, 0x00},
    {0x4307, 0xff},
    {0x4520, 0x00},
    {0x4521, 0x00},
    {0x4511, 0x22},
    {0x4801, 0x0f}, // AM05
    {0x4814, 0x2a}, // AM05
    {0x481f, 0x3c}, // MIPI clk prepare min
    {0x4823, 0x3c}, // AM05
    {0x481b, 0x3c}, // AM05
    {0x4826, 0x00}, // MIPI hs prepare min
    {0x4827, 0x32}, // AM05
    {0x4b00, 0x06},
    {0x4b01, 0x0a},
    {0x4b04, 0x10}, // AM05
    {0x5000, 0xff}, // bpc on, wpc on
    {0x5001, 0x00}, // awb disable
    {0x5002, 0x41}, // win enable, awb gain enable
    {0x5003, 0x0a}, // buf en, bin auto en
    {0x5004, 0x00}, // size man off
    {0x5043, 0x00},
    {0x5013, 0x00},
    {0x501f, 0x03}, // ISP output data
    {0x503d, 0x00}, // test pattern off
    {0x5180, 0x08}, // manual wb gain on
    {0x5a00, 0x08},
    {0x5b00, 0x01},
    {0x5b01, 0x40},
    {0x5b02, 0x00},
    {0x5b03, 0xf0},
    //kenxu @ 20130913 for strong DPC update -- Start
    {0x5780, 0xfc},
    {0x5781, 0x1f},
    {0x5782, 0x03},
    {0x5786, 0x20},
    {0x5787, 0x40},
    {0x5788, 0x08},
    {0x5789, 0x08},
    {0x578a, 0x02},
    {0x578b, 0x01},
    {0x578c, 0x01},
    {0x578d, 0x0c},
    {0x578e, 0x02},
    {0x578f, 0x01},
    {0x5790, 0x01},
    //kenxu @ 20130913 for strong DPC update -- End

//    {0x0100, 0x01},
    {0x4837, 0x23}, //0x17        //kenxu @ 20130913 to update mipi global timing
//    {0x0100, 0x01},
/*
//    {0x301a, 0xf1}, // MIPI stream off
//    {0x301c, 0xd6}, // clock lane in LP11 mode
    {0x350b, 0x80}, // gain = 8x
    {0x4837, 0x17}, // MIPI global timing
    {0x4802, 0x84},
    {0x4826, 0x00},
    {0x4827, 0x3e},
    {0x4818, 0x01},
    {0x4819, 0x00},
*/
};

/*1280x960*/
const struct _sensor_reg_t ov5648_sunny_framesize_quarter[] = {
    // 1280x960 30fps 2 lane MIPI 420Mbps/lane
    {0x0100, 0x00},
    //{0x3501, 0x3d}, // exposure
    //{0x3502, 0x00}, // exposure
    {0x3035, 0x21}, // PLL                 //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x3036, 0x54}, // PLL                 //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x3708, 0x66},
    {0x3709, 0x52},
    {0x370c, 0xcf},
    /*
    {0x3800, 0x00}, // xstart = 0
    {0x3801, 0x00}, // x start
    {0x3802, 0x00}, // y start = 0
    {0x3803, 0x00}, // y start
    {0x3804, 0x0a}, // xend = 2623
    {0x3805, 0x3f}, // xend
    {0x3806, 0x07}, // yend = 1955
    {0x3807, 0xa3}, // yend
    */
    {0x3808, 0x05}, // x output size = 1280
    {0x3809, 0x00}, // x output size
    {0x380a, 0x03}, // y output size = 960
    {0x380b, 0xc0}, // y output size
    {0x380c, 0x05}, // 0xb00, hts = 1408  //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x380d, 0x80},                       //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x380e, 0x05}, // 0x418, vts = 1320  //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x380f, 0x28},                       //kenxu @ 20130912 to reduce preview SCLK to 56M
  //  {0x3810, 0x00}, // isp x win = 16
    {0x3811, 0x10}, // isp x win
   // {0x3812, 0x00}, // isp y win = 10
    {0x3813, 0x0a}, // isp y win
    {0x3814, 0x31}, // x inc
    {0x3815, 0x31}, // y inc
   // {0x3817, 0x00}, // hsync start
    //{0x3820, 0x1e}, // flip off, v bin off
    //{0x3821, 0x01}, // mirror on, h bin on
    {0x4004, 0x02}, // black line number
    {0x4005, 0x18}, // blc level trigger
    //{0x350b, 0x80}, // gain = 8x
    {0x4837, 0x23}, //0x17        //kenxu @ 20130913 to update mipi global timing
    {0x0100, 0x01},
};

/*2592 1952 full size*/
const struct _sensor_reg_t ov5648_sunny_framesize_full[] = {
    // 2592x1952 15fps 2 lane MIPI 420Mbps/lane

    {0x0100, 0x00},
    //{0x3501, 0x7b}, // exposure
    //{0x3502, 0x00}, // exposure
    {0x3035, 0x11}, // PLL                 //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x3036, 0x42}, // PLL                 //kenxu @ 20130912 to reduce preview SCLK to 56M
    {0x3708, 0x63},
    {0x3709, 0x12},
    {0x370c, 0xcc},   //0xc0               //kenxu @ 20130913 to stabilize BLC result at full size
    /*
    {0x3800, 0x00}, // xstart = 0
    {0x3801, 0x00}, // xstart
    {0x3802, 0x00}, // ystart = 0
    {0x3803, 0x00}, // ystart
    {0x3804, 0x0a}, // xend = 2623
    {0x3805, 0x3f}, // xend
    {0x3806, 0x07}, // yend = 1955
    {0x3807, 0xa3}, // yend
    */
    {0x3808, 0x0a}, // x output size = 2592
    {0x3809, 0x20}, // x output size
    {0x380a, 0x07}, // y output size = 1952
    {0x380b, 0xa0}, // y output size
    {0x380c, 0x0b}, // hts = 2816
    {0x380d, 0x00}, // hts
    {0x380e, 0x08}, // vts = 1984
    {0x380f, 0x28}, // vts
   // {0x3810, 0x00}, // isp x win = 16
    {0x3811, 0x10}, // isp x win
   // {0x3812, 0x00}, // isp y win = 2
    {0x3813, 0x02}, // isp y win
    {0x3814, 0x11}, // x inc
    {0x3815, 0x11}, // y inc
    //{0x3817, 0x00}, // hsync start
    //{0x3820, 0x00}, // flip off, v bin off
    //{0x3821, 0x06}, // mirror on, v bin off
    {0x4004, 0x04}, // black line number
    {0x4005, 0x1a}, // blc level trigger
    //{0x350b, 0x40}, // gain = 8x
    {0x4837, 0x17},   //kenxu @ 20130913 to update mipi global timing
    {0x0100, 0x01},
};

#endif /* OV5648_SUNNY_H_INCLUDED */

/***************** END *******************/
