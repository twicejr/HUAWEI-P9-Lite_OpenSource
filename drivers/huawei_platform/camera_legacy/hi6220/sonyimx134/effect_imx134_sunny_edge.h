#ifndef __EFFECT_IMX134_SUNNY_H__

#define __EFFECT_IMX134_SUNNY_H__

{
    /* global */
    {0x65000, 0x3f},// [0]AWB gain enable [1]Black pixel canceling enable DPC [2]White pixel canceling enable [3]Raw normal enable [4]Lens online control [5]Lens Shading Enable [6]Raw scale enable [7]binning corrention enable
    {0X65001, 0X6f},//open recursive denoise
    {0x6502b, 0x8a},//disable RGBH dns, enable jpeg ycbcr convertion matrix
    {0x65603, 0x08},

    /* AEC */
    {0x1c594, 0x01},//AdvancedAecEnable
    {0x1c596, 0x50},//y-target-high
    {0x1c146, 0x30},//y-target
    {0x1c14a, 0x03},
    {0x1c14b, 0x0a},
    {0x1c14c, 0x0f},//aec fast step//
    {0x1c14e, 0x08},//slow step//08
    {0x1c140, 0x01},//banding enable
    {0x1c13e, 0x02},//real gain mode for OV8830
    {0x66401, 0x00},//window weight
    {0x66402, 0x20},//StatWin_Left
    {0x66403, 0x00},
    {0x66404, 0x20},//StatWin_Top
    {0x66405, 0x00},
    {0x66406, 0x20},//StatWin_Right
    {0x66407, 0x00},
    {0x66408, 0x28}, //StatWin_Bottom
    {0x66409, 0x01}, //definiton ofthe center 3x3 window
    {0x6640a, 0x00}, //nWin_Left
    {0x6640d, 0x00},
    {0x6640e, 0xc0}, //nWin_Top
    {0x66411, 0x06},
    {0x66412, 0x00}, //nWin_Width
    {0x66415, 0x04},
    {0x66416, 0x80}, //nWin_Height
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

    /*  auto level */// raw strech mode 2
    {0x66f00, 0x01},
    {0x66f01, 0x01},
    {0x66f02, 0x00}, //minlowlevel = blc
    {0x66f03, 0x01},
    {0x66f04, 0x8f}, //maxlowlevel //0x40 before
    {0x66f05, 0x0f},
    {0x66f06, 0xff}, //high level = 255, disable high level
    {0x66f09, 0x0b}, //psthres1
    {0x66f0a, 0x10}, //psthres2
    {0x66f0b, 0x02}, //minnum??
    {0x66f0c, 0x00},
    {0x66f0d, 0x10}, //target_offset
    //CT-AWB
    /* AWB */
    {0x66201, 0x52},//
    {0x66203, 0x14},//crop window
    {0x66211, 0xe8},//awb top limit
    {0x66212, 0x04},//awb bottom limit

    {0x1c190, 0x01},//CT mode
    {0x1c19a, 0x04},
    {0x1c19b, 0x00},//MinNum
    {0x1c192, 0x04},//AWB Step

    {0x1c19c, 0x00},//AWB offset
    {0x1c19d, 0x00},
    {0x1c19e, 0x00},
    {0x1c19f, 0x00},

    {0x1c1a0, 0x00},//avg ALL enable
    {0x1c1a1, 0x02},//weight of A
    {0x1c1a2, 0x10},//d65
    {0x1c1a3, 0x04},//CWF

    {0x1c1c5, 0x80},//pre-gain
    {0x1c1c6, 0x80},
    {0x1c1c7, 0x80},

    {0x1d8e8, 0x00}, //0x01: Enable AWB Shift, 0x02: Enable Br Shift, 0x04: enable Multiple Map, turn off awb shift for test
    {0x1d8e9, 0xf8}, //A low  B
    {0x1d8ea, 0x08}, //   R
    {0x1dbfe, 0x00}, //A  high  B
    {0x1dbff, 0x00}, //A        R

    {0x1d8eb, 0x00}, //C low  B
    {0x1d8ec, 0x00}, //   R
    {0x1d8f8, 0x00}, //C high B
    {0x1d8f9, 0x00}, //   R

    {0x1d8ed, 0x00}, //D low  B
    {0x1d8ee, 0x00}, //   R
    {0x1d8ef, 0x00}, //D high B
    {0x1d8f0, 0x00}, //   R

    {0x1d8f4, 0x00}, //c indoor/outdoor switch lum 1
    {0x1d8f5, 0x80}, //c indoor/outdoor switch lum 1 nAWBBrTh2
    {0x1d8f6, 0x02}, //c indoor/outdoor switch lum 2
    {0x1d8f7, 0x80}, //c indoor/outdoor switch lum 2 nAWBBrTh3

    {0x1d8f1, 0x20}, //CT_A
    {0x1d8f2, 0x80}, //CT_C
    {0x1d8f3, 0x90}, //CT_D

    {0x1d908, 0x01}, //what?
    {0x1d909, 0x00},
    {0x1d8fa, 0x00},
    {0x1d8fb, 0x80},
    {0x1d8fc, 0x01},
    {0x1d8fd, 0x80},
    {0x1d8fe, 0xf8}, //A high B
    {0x1d8ff, 0x08}, //   R

    {0x1d900, 0x40}, //what?
    {0x1d901, 0x70},
    {0x1d902, 0x20},
    {0x1d903, 0xa0},
    {0x1d904, 0xe0},
    {0x1d905, 0x70},
    {0x1d906, 0x60},
    {0x1d907, 0x60},

    {0x1d90a, 0xc2},
    {0x1d90b, 0xe9},

    {0x1d8de, 0x00},
    {0x1d8df, 0x80},

    {0x66206, 0x12}, //center(cwf) window threshold D0
    {0x66207, 0x24}, //A threshold, range DX  0x15
    {0x66208, 0x15}, //day threshold, range DY 0xd
    {0x66209, 0x83}, //CWF X
    {0x6620a, 0x6a}, //CWF Y
    {0x6620b, 0xe3}, //K_A_X2Y, a slop
    {0x6620c, 0xa5}, //K_D65_Y2X, d slop
    {0x6620d, 0x53}, //D65 Limit
    {0x6620e, 0x37}, //A Limit
    {0x6620f, 0x75}, //D65 split
    {0x66210, 0x5c}, //A split

    /* De-noise */
    {0x65604, 0x00},//Richard for new curve 0314
    {0x65605, 0x00},//Richard for new curve 0314
    {0x65606, 0x00},//Richard for new curve 0314
    {0x65607, 0x00},//Richard for new curve 0314

    {0x65510, 0x0F}, //G dns slope change from 0x4 to 0xf Richard 0320
    {0x65511, 0x1F}, //G dns slope change from 0x4 to 0xf Richard 0320
    {0x6551a, 0x01},//Raw G Dns improve white pixel 20120728
    {0x6551b, 0x02},//gain  2X
    {0x6551c, 0x04},//gain  4X
    {0x6551d, 0x04},//gain  8X
    {0x6551e, 0x04},//gain 16X
    {0x6551f, 0x04},//gain 32X
    {0x65520, 0x04},//gain 64X
    {0x65522, 0x00},//RAW BR De-noise
    {0x65523, 0x01},//gain 1X
    {0x65524, 0x00},
    {0x65525, 0x02},//gain 2X
    {0x65526, 0x00},
    {0x65527, 0x06},//gain 4X
    {0x65528, 0x00},
    {0x65529, 0x06},//gain 8X
    {0x6552a, 0x00},
    {0x6552b, 0x06},//gain 16X
    {0x6552c, 0x00},
    {0x6552d, 0x06},//gain 32X
    {0x6552e, 0x00},
    {0x6552f, 0x06},//gain 64X

    {0x65c00, 0x03},//UV De-noise: gain 1X
    {0x65c01, 0x05},//gain 2X
    {0x65c02, 0x08},//gain 4X
    {0x65c03, 0x1f},//gain 8X
    {0x65c04, 0x1f},//gain 16X
    {0x65c05, 0x1f},//gain 32X

    //Raw&UV Denoise Setting
    {0x67300, 0x0f},
    {0x67301, 0x0f},
    {0x67302, 0x10},
    {0x67303, 0x10},
    {0x67304, 0x10},
    {0x67305, 0x10},
    {0x67306, 0x10},
    {0x67307, 0x12},
    {0x67308, 0x14},
    {0x67309, 0x15},
    {0x6730a, 0x16},
    {0x6730b, 0x18},
    {0x6730c, 0x0c},
    {0x6730d, 0x0e},
    {0x6730e, 0x10},
    {0x6730f, 0x12},
    {0x67310, 0x13},
    {0x67311, 0x14},
    {0x65c00, 0x00},
    {0x65c01, 0x01},
    {0x65c02, 0x03},
    {0x65c03, 0x04},
    {0x65c04, 0x05},
    {0x65c05, 0x06},



    /* dpc */
    {0x65409, 0x08},
    {0x6540a, 0x08},
    {0x6540b, 0x08},
    {0x6540c, 0x08},
    {0x6540d, 0x0c},
    {0x6540e, 0x08},
    {0x6540f, 0x08},
    {0x65410, 0x08},
    {0x65408, 0x0b},

    /* sharpeness */
    {0x65600, 0x00},
    {0x65601, 0x30},//0319
    {0x65602, 0x00},
    {0x65603, 0xC0},
    {0x65608, 0x08},
    {0x65609, 0x20},
    {0x6560c, 0x04},
    {0x6560d, 0x0A}, //low gain sharpness, 20120814 0x20->0x30
    {0x6560e, 0x10},//MinSharpenTp
    {0x6560f, 0x60},//MaxSharpenTp
    {0x65610, 0x10},//MinSharpenTm
    {0x65611, 0x60},//MaxSharpenTm
    {0x65613, 0x10},//SharpenAlpha
    {0x65615, 0x04},//HFreq_thre
    {0x65617, 0x08},//HFreq_coef

    /* auto uv saturation */ //modified by Richard for test
    {0x1c4e8, 0x01},//Enable
    {0x1c4e9, 0xbf},// gain threshold1 40-->0b
    {0x1c4ea, 0xf7},//gain threshold2 78-->0d
    {0x1c4eb, 0x78}, //keep back for new cmx 0310
    {0x1c4ec, 0x70}, //keep back for new cmx 0310

    /* gamma */
    {0x1d984, 0x00}, //adaptive gamma,disable for test by Richard@07092013
    {0x1c49b, 0x01}, //ManualGamma enable //??

    {0x1c49c, 0x01}, //ManualGamma [15:8], gamma value = current value/256
    {0x1c49d, 0x01}, //ManualGamma [7:0]
    {0x1c49e, 0x01}, //RGB Gamma [15:8]
    {0x1c49f, 0x01}, //RGB Gamma [7:0]   Manual gamma and RGB gamma should be same
    {0x1c4a2, 0x00}, //Max RGB Gamma Gain [15:8]//??? should be checked by Richard
    {0x1c4a3, 0x40}, //Max RGB Gamma Gain [7:0]//??? should be checked by Richard

    //these settings should be removed when adaptive gamma is disabled
    //{0x1d994, 0x01}, //low gain gamma
    //{0x1d995, 0xe6},
    //{0x1d996, 0x01}, //high gain gamma
    //{0x1d997, 0xc0},
    //{0x1d998, 0x01}, //dark image gamma
    //{0x1d999, 0xb3},
    //{0x1d99a, 0x88}, //low gain slope
    //{0x1d99b, 0x50}, //high gain slope
    //{0x1d99c, 0x38}, //dark image slope
    //{0x1d99d, 0x14}, //low bright thres
    //{0x1d99e, 0x20}, //high bright thres

    {0x1c591, 0x01},//enable adaptive curve
    {0x1c592, 0x40},//low gain threshold
    {0x1c593, 0x70},//high gain threshold
    /* Tone Mapping curve */

    {0x1C4C0, 0x7 },
    {0x1C4C1, 0xD },
    {0x1C4C2, 0x13},
    {0x1C4C3, 0x19},
    {0x1C4C4, 0x1F},
    {0x1C4C5, 0x26},
    {0x1C4C6, 0x2E},
    {0x1C4C7, 0x36},
    {0x1C4C8, 0x3F},
    {0x1C4C9, 0x4A},
    {0x1C4CA, 0x58},
    {0x1C4CB, 0x69},
    {0x1C4CC, 0x82},
    {0x1C4CD, 0xA3},
    {0x1C4CE, 0xCD},

    {0x1d985, 0x9 },//high gain curve 00
    {0x1d986, 0x10},//high gain curve 01
    {0x1d987, 0x17},
    {0x1d988, 0x1E},
    {0x1d989, 0x25},
    {0x1d98a, 0x2D},
    {0x1d98b, 0x34},
    {0x1d98c, 0x3C},
    {0x1d98d, 0x46},
    {0x1d98e, 0x51},
    {0x1d98f, 0x60},
    {0x1d990, 0x72},
    {0x1d991, 0x8C},
    {0x1d992, 0xAB},
    {0x1d993, 0xD3},//high gain curve 15


    //=================EDR=============
    {0x1c4d4, 0x00},//EDR scale, disable edr with 0
    {0x1c4d5, 0x00},//EDR scale, disable edr with 0
    {0x1c4cf, 0xff},//disable edr with 0xff

    {0x65a00, 0x1b}, //bit[4]????RGB ?1¨º?YUV  bi[0] h_dark_en
    {0x65a01, 0xc0}, //h_dark_th[6:0]

    //YUV curve gain control,expoure frist
    //{0x1c1b3, 0x20}, //Gain thre1 ?
    //{0x1c1b4, 0x50}, //Gain thre2

    //{0x1c1b5, 0x01}, //EDR gain control
    //{0x1c1b6, 0x01}, //Curve Gain control
    //{0x1c1b7, 0x40}, //after gamma cut ratio

    /* LENC */
    {0x65102, 0x07},
    {0x65103, 0x87},
    {0x65104, 0x0a},
    {0x65105, 0x0a},
    {0x65106, 0x0a},
    {0x65107, 0x0a},
    {0x65108, 0x06},
    {0x65109, 0xb1},

    {0x1c244, 0x01},
    {0x1c248, 0x40},//repeat
    {0x1c24a, 0x10},//repeat
    {0x1c24c, 0x00},//repeat
    {0x1c24d, 0x20},//repeat
    {0x1c24e, 0x00},//repeat
    {0x1c24f, 0xff},//repeat

    {0x1c245, 0x00},//three profile,color temperature based lens shading correction mode 1: enable 0: disable
    {0x1c24c, 0x00},
    {0x1c24d, 0x40},
    {0x1c24e, 0x00},
    {0x1c24f, 0x80},
    {0x1c248, 0x40},
    {0x1c24a, 0x20},

    {0x1c254, 0x0 },//lens profile switch
    {0x1c255, 0xce},
    {0x1c256, 0x0 },
    {0x1c257, 0xe7},
    {0x1c258, 0x1 },
    {0x1c259, 0x69},
    {0x1c25a, 0x1 },
    {0x1c25b, 0xd2},


    /* OVISP LENC setting for D65 Long Exposure (HDR/3D) */
    {0x1c264, 0x14},//Y1
    {0x1c265, 0xb },
    {0x1c266, 0x8 },
    {0x1c267, 0x8 },
    {0x1c268, 0xb },
    {0x1c269, 0x12},
    {0x1c26a, 0x7 },//Y2
    {0x1c26b, 0x4 },
    {0x1c26c, 0x2 },
    {0x1c26d, 0x2 },
    {0x1c26e, 0x4 },
    {0x1c26f, 0x7 },
    {0x1c270, 0x3 },//Y3
    {0x1c271, 0x1 },
    {0x1c272, 0x0 },
    {0x1c273, 0x0 },
    {0x1c274, 0x1 },
    {0x1c275, 0x3 },
    {0x1c276, 0x3 },//Y4
    {0x1c277, 0x1 },
    {0x1c278, 0x0 },
    {0x1c279, 0x0 },
    {0x1c27a, 0x1 },
    {0x1c27b, 0x3 },
    {0x1c27c, 0x5 },//Y5
    {0x1c27d, 0x3 },
    {0x1c27e, 0x2 },
    {0x1c27f, 0x2 },
    {0x1c280, 0x3 },
    {0x1c281, 0x6 },
    {0x1c282, 0x12},//Y6
    {0x1c283, 0x9 },
    {0x1c284, 0x6 },
    {0x1c285, 0x7 },
    {0x1c286, 0xa },
    {0x1c287, 0xf },
    {0x1c288, 0x20},//Cb1
    {0x1c289, 0x20},
    {0x1c28a, 0x20},
    {0x1c28b, 0x20},
    {0x1c28c, 0x20},
    {0x1c28d, 0x20},//Cb2
    {0x1c28e, 0x20},
    {0x1c28f, 0x20},
    {0x1c290, 0x20},
    {0x1c291, 0x20},
    {0x1c292, 0x20},//Cb3
    {0x1c293, 0x20},
    {0x1c294, 0x20},
    {0x1c295, 0x20},
    {0x1c296, 0x20},
    {0x1c297, 0x20},//Cb4
    {0x1c298, 0x20},
    {0x1c299, 0x20},
    {0x1c29a, 0x20},
    {0x1c29b, 0x20},
    {0x1c29c, 0x20},//Cb5
    {0x1c29d, 0x20},
    {0x1c29e, 0x20},
    {0x1c29f, 0x20},
    {0x1c2a0, 0x20},
    {0x1c2a1, 0x1e}, //Cr1
    {0x1c2a2, 0x1f},
    {0x1c2a3, 0x1f},
    {0x1c2a4, 0x1f},
    {0x1c2a5, 0x1e},
    {0x1c2a6, 0x1f}, //Cr2
    {0x1c2a7, 0x20},
    {0x1c2a8, 0x20},
    {0x1c2a9, 0x20},
    {0x1c2aa, 0x1f},
    {0x1c2ab, 0x1f}, //Cr3
    {0x1c2ac, 0x20},
    {0x1c2ad, 0x20},
    {0x1c2ae, 0x20},
    {0x1c2af, 0x1f},
    {0x1c2b0, 0x1f}, //Cr4
    {0x1c2b1, 0x20},
    {0x1c2b2, 0x20},
    {0x1c2b3, 0x20},
    {0x1c2b4, 0x1f},
    {0x1c2b5, 0x1e}, //cr5
    {0x1c2b6, 0x1f},
    {0x1c2b7, 0x1f},
    {0x1c2b8, 0x1f},
    {0x1c2b9, 0x1e},

    //add ccm detect parameter according 0x1c734~0x1c736
    {0x1c1c8 ,0x01}, //center CT, CWF
    {0x1c1c9 ,0x3f},
    {0x1c1cc, 0x00},//daylight
    {0x1c1cd, 0xbd},
    {0x1c1d0, 0x02},//a
    {0x1c1d1, 0x2a},


    /* Color matrix */
    {0x1C1d8, 0x01},//center matrix,
    {0x1C1d9, 0x97},
    {0x1C1da, 0xFF},
    {0x1C1db, 0x63},
    {0x1C1dc, 0x00},
    {0x1C1dd, 0x04},
    {0x1C1de, 0xFF},
    {0x1C1df, 0xDC},
    {0x1C1e0, 0x01},
    {0x1C1e1, 0x7B},
    {0x1C1e2, 0xFF},
    {0x1C1e3, 0xA8},
    {0x1C1e4, 0xFF},
    {0x1C1e5, 0xFA},
    {0x1C1e6, 0xFE},
    {0x1C1e7, 0xF3},
    {0x1C1e8, 0x02},
    {0x1C1e9, 0x12},

    {0x1C1FC, 0xFF},//cmx left delta,daylight
    {0x1C1FD, 0xCD},
    {0x1C1FE, 0x00},
    {0x1C1FF, 0x30},
    {0x1C200, 0x00},
    {0x1C201, 0x01},
    {0x1C202, 0xFF},
    {0x1C203, 0xB4},
    {0x1C204, 0x00},
    {0x1C205, 0x2b},
    {0x1C206, 0x00},
    {0x1C207, 0x20},
    {0x1C208, 0xFF},
    {0x1C209, 0xE0},
    {0x1C20A, 0x00},
    {0x1C20B, 0x3A},
    {0x1C20C, 0xFF},
    {0x1C20D, 0xE5},

    {0x1C220, 0x00},//cmx right delta,a light
    {0x1C221, 0xD8},
    {0x1C222, 0xFF},
    {0x1C223, 0x6C},
    {0x1C224, 0xFF},
    {0x1C225, 0xBC},
    {0x1C226, 0xFF},
    {0x1C227, 0xD1},
    {0x1C228, 0x00},
    {0x1C229, 0x4F},
    {0x1C22A, 0xFF},
    {0x1C22B, 0xE0},
    {0x1C22C, 0xFF},
    {0x1C22D, 0xB7},
    {0x1C22E, 0x00},
    {0x1C22F, 0xFF},
    {0x1C230, 0xFF},
    {0x1C231, 0x4A},

    //===========AF=======
    {0x1cd0a, 0x00},
    //===========BLC======
    {0x6500c, 0x01},
    {0x6500d, 0x00},
    {0x6500e, 0x01},
    {0x6500f, 0x00},

    //Awb Setting
    {0X1c190, 0X02},//1, CT; 2, Curve
    {0X1d8e8, 0X07},//0x01: Enable AWB Shift, 0x02: Enable Br Shift, 0x04: enable Multiple Map
    {0X1d914, 0X05}, //D65 weight
    {0X1d915, 0X04}, //CWF weight
    {0X1d916, 0X03}, //a weight
    //X_OFF
    {0X66280, 0X0e},
    {0X66281, 0X0f},
    //Y_OFF
    {0X66282, 0X0e},
    {0X66283, 0X3c},
    //KX
    {0X1d8e2, 0X00},
    {0X1d8e3, 0X4e},
    //KY
    {0X1d8e4, 0X00},
    {0X1d8e5, 0X16},
    //LowMap
    {0X1d800, 0X21},
    {0X1d801, 0X33},
    {0X1d802, 0X33},
    {0X1d803, 0X33},
    {0X1d804, 0X33},
    {0X1d805, 0Xc3},
    {0X1d806, 0Xcc},
    {0X1d807, 0X3c},
    {0X1d808, 0X21},
    {0X1d809, 0Xc3},
    {0X1d80a, 0Xcc},
    {0X1d80b, 0Xcc},
    {0X1d80c, 0Xcc},
    {0X1d80d, 0Xcc},
    {0X1d80e, 0Xcc},
    {0X1d80f, 0Xcc},
    {0X1d810, 0X21},
    {0X1d811, 0Xc3},
    {0X1d812, 0Xcc},
    {0X1d813, 0Xcc},
    {0X1d814, 0Xcc},
    {0X1d815, 0Xcc},
    {0X1d816, 0Xcc},
    {0X1d817, 0X3c},
    {0X1d818, 0X32},
    {0X1d819, 0Xcc},
    {0X1d81a, 0Xcc},
    {0X1d81b, 0Xcc},
    {0X1d81c, 0Xc3},
    {0X1d81d, 0Xcc},
    {0X1d81e, 0Xcc},
    {0X1d81f, 0X3c},
    {0X1d820, 0X32},
    {0X1d821, 0Xcc},
    {0X1d822, 0Xcc},
    {0X1d823, 0Xcc},
    {0X1d824, 0Xc3},
    {0X1d825, 0Xcc},
    {0X1d826, 0Xcc},
    {0X1d827, 0X3c},
    {0X1d828, 0X32},
    {0X1d829, 0Xcc},
    {0X1d82a, 0Xcc},
    {0X1d82b, 0Xcc},
    {0X1d82c, 0Xcc},
    {0X1d82d, 0Xcc},
    {0X1d82e, 0Xcc},
    {0X1d82f, 0X23},
    {0X1d830, 0Xd4},
    {0X1d831, 0Xdd},
    {0X1d832, 0Xdd},
    {0X1d833, 0X4d},
    {0X1d834, 0Xdd},
    {0X1d835, 0Xdd},
    {0X1d836, 0Xdd},
    {0X1d837, 0X24},
    {0X1d838, 0Xd4},
    {0X1d839, 0Xdd},
    {0X1d83a, 0Xdd},
    {0X1d83b, 0X4d},
    {0X1d83c, 0Xdd},
    {0X1d83d, 0Xdd},
    {0X1d83e, 0Xdd},
    {0X1d83f, 0X24},
    {0X1d840, 0Xd4},
    {0X1d841, 0Xdd},
    {0X1d842, 0Xdd},
    {0X1d843, 0X4d},
    {0X1d844, 0Xdd},
    {0X1d845, 0Xdd},
    {0X1d846, 0Xdd},
    {0X1d847, 0X24},
    {0X1d848, 0Xd4},
    {0X1d849, 0Xdd},
    {0X1d84a, 0Xdd},
    {0X1d84b, 0Xdd},
    {0X1d84c, 0Xdd},
    {0X1d84d, 0Xdd},
    {0X1d84e, 0X4d},
    {0X1d84f, 0X12},
    {0X1d850, 0Xee},
    {0X1d851, 0Xee},
    {0X1d852, 0Xee},
    {0X1d853, 0Xe5},
    {0X1d854, 0Xee},
    {0X1d855, 0Xee},
    {0X1d856, 0X5e},
    {0X1d857, 0X12},
    {0X1d858, 0Xee},
    {0X1d859, 0Xee},
    {0X1d85a, 0Xee},
    {0X1d85b, 0Xe5},
    {0X1d85c, 0Xee},
    {0X1d85d, 0Xee},
    {0X1d85e, 0X5e},
    {0X1d85f, 0X12},
    {0X1d860, 0Xee},
    {0X1d861, 0Xee},
    {0X1d862, 0Xee},
    {0X1d863, 0Xe5},
    {0X1d864, 0Xee},
    {0X1d865, 0Xee},
    {0X1d866, 0X5e},
    {0X1d867, 0X12},
    {0X1d868, 0Xee},
    {0X1d869, 0Xee},
    {0X1d86a, 0Xee},
    {0X1d86b, 0Xee},
    {0X1d86c, 0Xee},
    {0X1d86d, 0Xee},
    {0X1d86e, 0X25},
    {0X1d86f, 0X01},
    {0X1d870, 0X55},
    {0X1d871, 0X55},
    {0X1d872, 0X55},
    {0X1d873, 0X55},
    {0X1d874, 0Xee},
    {0X1d875, 0Xee},
    {0X1d876, 0X25},
    {0X1d877, 0X01},
    {0X1d878, 0X22},
    {0X1d879, 0X22},
    {0X1d87a, 0X22},
    {0X1d87b, 0X22},
    {0X1d87c, 0X22},
    {0X1d87d, 0X22},
    {0X1d87e, 0x22},
    {0X1d87f, 0x01},
    //MiddleMask
    {0X1d880, 0x00},
    {0X1d881, 0x00},
    {0X1d882, 0x00},
    {0X1d883, 0x00},
    {0X1d884, 0x00},
    {0X1d885, 0x00},
    {0X1d886, 0x00},
    {0X1d887, 0x00},
    {0X1d888, 0x00},
    {0X1d889, 0x1c},
    {0X1d88a, 0x00},
    {0X1d88b, 0x1c},
    {0X1d88c, 0x00},
    {0X1d88d, 0x1e},
    {0X1d88e, 0x00},
    {0X1d88f, 0x1e},
    {0X1d890, 0x00},
    {0X1d891, 0x1f},
    {0X1d892, 0x00},
    {0X1d893, 0x1f},
    {0X1d894, 0x00},
    {0X1d895, 0x1f},
    {0X1d896, 0x80},
    {0X1d897, 0x1f},
    {0X1d898, 0x80},
    {0X1d899, 0x1f},
    {0X1d89a, 0xc0},
    {0X1d89b, 0x1f},
    {0X1d89c, 0xc0},
    {0X1d89d, 0x1f},
    {0X1d89e, 0x00},
    {0X1d89f, 0x00},
    //HighMask
    {0X1d8a0, 0x00},
    {0X1d8a1, 0x00},
    {0X1d8a2, 0x00},
    {0X1d8a3, 0x00},
    {0X1d8a4, 0x00},
    {0X1d8a5, 0x00},
    {0X1d8a6, 0x00},
    {0X1d8a7, 0x00},
    {0X1d8a8, 0x00},
    {0X1d8a9, 0x1c},
    {0X1d8aa, 0x00},
    {0X1d8ab, 0x1c},
    {0X1d8ac, 0x00},
    {0X1d8ad, 0x1e},
    {0X1d8ae, 0x00},
    {0X1d8af, 0x1e},
    {0X1d8b0, 0x00},
    {0X1d8b1, 0x1f},
    {0X1d8b2, 0X00},
    {0X1d8b3, 0X1f},
    {0X1d8b4, 0X00},
    {0X1d8b5, 0X1f},
    {0X1d8b6, 0X80},
    {0X1d8b7, 0X1f},
    {0X1d8b8, 0X00},
    {0X1d8b9, 0X00},
    {0X1d8ba, 0X00},
    {0X1d8bb, 0X00},
    {0X1d8bc, 0X00},
    {0X1d8bd, 0X00},
    {0X1d8be, 0X00},
    {0X1d8bf, 0X00},
    //======for AWB shift======
    {0X1d8ed, 0X00},
    {0X1d8ee, 0X00},
    {0X1d8eb, 0X00},
    {0X1d8ec, 0X00},
    {0X1d8e9, 0X00},
    {0X1d8ea, 0X00},
    {0X1d8ef, 0X00},
    {0X1d8f0, 0X00},
    {0X1d8f8, 0X00},
    {0X1d8f9, 0X00},
    {0X1d8fe, 0X00},
    {0X1d8ff, 0X00},
    //====AWB shift End=======
    {0x6502b, 0x88}, //not use RGBH DNS(old ISP2.0)
    {0x65063, 0x0c},
},

/* ae_params_s */
{
	/* ae_target_s */
	{
        {0xd, 0xf},
		{0x1a, 0x1c},
		{0x2c, 0x4c},
		{0x61, 0x62},
		{0x76, 0x78},
        /* end */
	},

		/* ae_win_params */
	{

		/* win2x2*/
		{85, 85},
		/* win3x3 */
		{{60, 60}, {60, 60}, {100, 100},},
		/* roi_enable */
		false,
		/* default_stat_win weights */
		//{1, 1, 1, 1, 9, 9, 9, 9, 18, 9, 9, 9, 9},
		{1, 1, 1, 1, 2, 2, 2, 2, 4, 2, 2, 2, 2},

		3,
		/* enhanced_stat_win */
		{1, 1, 1, 1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},

		8,
	},
	/* max_expo_gap */
	14,
	/* iso_max */
	3100,
	/* iso_min */
	100,
{
	/* low2mid */
	0xE0,
	/* mid2high */
	0x48,
	/* high2mid */
	0xC0,
	/* mid2low */
	0x1D0,
},
{
	/* low2mid manual iso*/
	310,
	/* mid2high manual iso*/
	180,
	/* high2mid manual iso*/
	120,
	/* mid2low manual iso*/
	120,
},
	{
	/* preview_fps_max */
	30,
	/* preview_fps_middle */
	15,
	/* preview_fps_min */
	10,
	/* capture_fps_min */
	8,
	},
	/* expo_night */
	5,
	/* expo_action */
	100,
	/* cap_expo_table */
	{
		{30, 100}, /* max expo is 3 band(50Hz), 4band(60Hz) */
		//{23, 180}, /* max expo is 4 band(50Hz), 5band(60Hz) */
		{20, 200}, /* max expo is 5 band(50Hz), 6band(60Hz) */

		/* Below is Lower capture frame rate (or larger exposure) than normal frame rate. */
		{14, 600}, /* max expo is 7 band(50Hz), 8band(60Hz) */
		{10, 800}, /* max expo is 10 band(50Hz),  12band(60Hz)*/
		{8, 8000}, /* max expo is 12 band(50Hz), 15band(60Hz) */
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
	},
	/* ev_numerator */
	635,
	/* u32 ev_denominator */
	1000,

},

/* af_param */
{
	/*focus_area*/
	{
		/* percent_w */
		25,
		/* percent_w */
		20,
		/* max_zoom_ratio */
		0x200,
		/* min_height_ratio */
		5,
		/* weight[25] */
		{0},
	},
	/* focus_algo_s */
	{
		/* contrast_stat_mode */
		YUV_EDGE_STAT,
		/* contrast_threshold */
		{0x04, 0x10, 0x80, 0x140},
		/* param_judge */
		{0x18, 0x08, 0xc0, 0x04, 95},
		/* infinity_hold_frames */
		2,
		/* rewind_hold_frames */
		1,
		/* try_dir_range */
		5,
		/* param_caf_trigger */
		{3, 3, 4, 10, 0x28, 25, 16, 100, 0xc, 4, 4, 2000, 2, 6, 15, 6, 4, 0x40},
		/* calc_coarse_size */
		(1280 * 720),
	},
},

/* manual_wb_param */
{
	/* b_gai   gb_gain  gr_gain r_gain */
	{0x0000, 0x0000, 0x0000, 0x0000}, /* AWB not care about it */
	{0x012c, 0x0080, 0x0080, 0x0089}, /* INCANDESCENT 2800K */
	{0x00f2, 0x0080, 0x0080, 0x00b9}, /* FLUORESCENT 4200K */
	{0x00a0, 0x00a0, 0x00a0, 0x00a0}, /* WARM_FLUORESCENT, y36721 todo */
	{0x00d1, 0x0080, 0x0080, 0x00d2}, /* DAYLIGHT 5000K */
	{0x00b0, 0x0080, 0x0080, 0x00ec}, /* CLOUDY_DAYLIGHT 6500K*/
	{0x00a0, 0x00a0, 0x00a0, 0x00a0}, /* TWILIGHT, y36721 todo */
	{0x0168, 0x0080, 0x0080, 0x0060}, /* CANDLELIGHT, 2300K */
},


/* rcc */
{
	/* rcc_enable */
	false,
	/* frame_interval */
	8,
	/* detect_range */
	50,
	/* rect_row_num */
	5,
	/* rect_col_num */
	5,
	/* preview_width_high */
	960,
	/* preview_width_low */
	320,
	/* uv_resample_high */
	8,
	/* uv_resample_middle */
	4,
	/* uv_resample_low */
	2,
	/* refbin_low */
	0x80,
	/* refbin_high */
	0xf0,
	/* v_th_high */
	160,
	/* v_th_low */
	130,
},


/* sharpness_cfg */
{
	{
		/* preview_shapness */
		0x0A,    //hefei modify for imx134 sensor
		/* cap_shapness */
		0x0A,
	},

},


/* dns */
{
    /*raw_dns_coff*/
    {{0x06,0x0C,0x16,0x20,0x20,0x20},{0x0C,0x0E,0x10,0x12,0x13,0x14},{0x08,0x0a,0x0c,0x0d,0x0e,0x0e}},
    {{0x0A,0x0C,0x16,0x24,0x36,0x50},{0x10,0x12,0x14,0x15,0x16,0x18},{0x10,0x12,0x14,0x15,0x16,0x18}},
    {{0x0A,0x0C,0x16,0x24,0x36,0x50},{0x10,0x12,0x14,0x15,0x16,0x18},{0x10,0x12,0x14,0x15,0x16,0x18}},
    /*g_dns_caputure_1_band*/
    0x0A,
    /*g_dns_flash_1_band*/
    0x0A,
    {0x03,0x05,0x08,0x1f,0x1f,0x1f},
    {0x03,0x05,0x08,0x1f,0x1f,0x1f},
    {0x03,0x05,0x08,0x1f,0x1f,0x1f},
},


/* scene_param: uv_saturation */
{
	0x80, /* CAMERA_SCENE_AUTO */
	0x80, /* CAMERA_SCENE_ACTION */
	0x90, /* CAMERA_SCENE_PORTRAIT */
	0x98, /* CAMERA_SCENE_LANDSPACE */
	0x80, /* CAMERA_SCENE_NIGHT */
	0x90, /* CAMERA_SCENE_NIGHT_PORTRAIT */
	0x70, /* CAMERA_SCENE_THEATRE */
	0x80, /* CAMERA_SCENE_BEACH */
	0x80, /* CAMERA_SCENE_SNOW */
	0x80, /* CAMERA_SCENE_SUNSET */
	0x80, /* CAMERA_SCENE_STEADYPHOTO */
	0x80, /* CAMERA_SCENE_FIREWORKS */
	0x80, /* CAMERA_SCENE_SPORTS */
	0x80, /* CAMERA_SCENE_PARTY */
	0x80, /* CAMERA_SCENE_CANDLELIGHT */
	0x80, /* CAMERA_SCENE_BARCODE */
	0x80, /* CAMERA_SCENE_FLOWERS */
},

/* flash_param */
{
	/* gain */
	{0xc2, 0x80, 0x80, 0xe8},

	/* aceawb_step */
	{0x06, 0x18, 0x18, 0x10, 0x0c},
	/* videoflash_level */
	LUM_LEVEL2,
	/* assistant_af_params*/
	{0xA0, 0x10, 0x30, 30, LUM_LEVEL1},
	/* flash_capture */
	{0x70, LUM_LEVEL2, LUM_LEVEL5, 0x04, 0x30, 30, 0xe0, 0x20, 0x140},
},

#endif //__EFFECT_IMX134_SUNNY_H__

