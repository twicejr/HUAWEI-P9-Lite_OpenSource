/* Copyright (c) 2008-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include "hisi_fb.h"

#define DTS_COMP_JDI_OTM1906A "hisilicon,mipi_jdi_OTM1906A"

static struct hisi_fb_panel_data g_panel_data;
static int g_lcd_fpga_flag= 0;
static int g_lcd_dirty_lines = 0;

#define LINE_BASE_8	(0)
#define LINE_BASE_16	(0)
#define LINE_BASE_32	(0)

#define LCD_POWER_STATUS_CHECK	(0)


/*******************************************************************************
** Power ON Sequence(sleep mode to Normal mode)
*/
static char adrsft0[] = {
	0x00,
	0x00,
};

static char adrsft1[] = {
	0xFF,
	0x19, 0x06, 0x01,
};

static char adrsft2[] = {
	0x00,
	0x80,
};

static char adrsft3[] = {
	0xFF,
	0x19, 0x06,
};

static char adrsft4[] = {
	0x00,
	0x80,
};

static char adrsft5[] = {
	0xc0,
	0x00, 0x7f, 0x00, 0x07, 0x08,
	0x00, 0x7f, 0x07, 0x08, 0x00,
	0x7f, 0x00, 0x08, 0x08,
};

static char adrsft6[] = {
	0x00,
	0xa0,
};

static char adrsft7[] = {
	0xc0,
	0x00, 0x00, 0x00, 0x00, 0x01,
	0x1a, 0x05, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

static char adrsft8[] = {
	0x00,
	0xd0,
};

static char adrsft9[] = {
	0xc0,
	0x00, 0x00, 0x00, 0x00, 0x01,
	0x1a, 0x05, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

static char adrsft10[] = {
	0x00,
	0x80,
};

static char adrsft11[] = {
	0xa4,
	0x88, 0x00, 0x00, 0x02, 0x00,
	0x82, 0x00,
};

static char adrsft12[] = {
	0x00,
	0x80,
};

static char adrsft13[] = {
	0xa5,
	0x0c, 0x00, 0x01, 0x08,
};

static char adrsft14[] = {
	0x00,
	0x80,
};

static char adrsft15[] = {
	0xc2,
	0x83, 0x01, 0x78, 0x61, 0x83,
	0x01, 0x78, 0x61, 0x00, 0x00,
	0x00, 0x00,
};

static char adrsft16[] = {
	0x00,
	0x90,
};

static char adrsft17[] = {
	0xc2,
	0x00,  0x00,  0x00,  0x00,  0x00,
	0x00,  0x00,  0x00,  0x00,  0x00,
	0x00,  0x00,
};

static char adrsft18[] = {
	0x00,
	0xa0,
};

static char adrsft19[] = {
	0xc2,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
};

static char adrsft20[] = {
	0x00,
	0xb0,
};

static char adrsft21[] = {
	0xc2,
	0x84, 0x06, 0x01, 0x00, 0x01,
	0x85, 0x05, 0x01, 0x00, 0x01,
	0x82, 0x08, 0x01, 0x00, 0x01,
};

static char adrsft22[] = {
	0x00,
	0xc0,
};

static char adrsft23[] = {
	0xc2,
	0x83, 0x03, 0x01, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

static char adrsft24[] = {
	0x00,
	0xd0,
};

static char adrsft25[] = {
	0xc2,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

static char adrsft26[] = {
	0x00,
	0xda,
};

static char adrsft27[] = {
	0xc2,
	0x33, 0x33, 0x33, 0x33, 0x00,
};

static char adrsft28[] = {
	0x00,
	0xe0,
};

static char adrsft29[] = {
	0xc2,
	0x85, 0x7c, 0x04, 0x01, 0x0a,
	0x84, 0x7c, 0x04, 0x01, 0x0a,
	0x14,
};

static char adrsft30[] = {
	0x00,
	0xf0,
};

static char adrsft31[] = {
	0xc2,
	0x00, 0x20, 0x01, 0x01, 0x0a,
	0x00, 0x20, 0x01, 0x01, 0x0a,
	0x00, 0x00, 0x00, 0x00, 0x01,
};

static char adrsft32[] = {
	0x00,
	0x80,
};

static char adrsft33[] = {
	0xc3,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x30, 0x00, 0x00,
};

static char adrsft34[] = {
	0x00,
	0xa0,
};

static char adrsft35[] = {
	0xc3,
	0x83, 0x01, 0x78, 0x61, 0x83,
	0x01, 0x78, 0x61, 0x00, 0x00,
	0x00, 0x00,
};

static char adrsft36[] = {
	0x00,
	0xb0,
};

static char adrsft37[] = {
	0xc3,
	0x00, 0x00, 0x00, 0x00, 0x84,
	0x06, 0x01, 0x00, 0x01, 0x85,
	0x05, 0x01, 0x00, 0x01,
};

static char adrsft38[] = {
	0x00,
	0xc0,
};

static char adrsft39[] = {
	0xc3,
	0x82, 0x08, 0x01, 0x00, 0x01,
	0x83, 0x03, 0x01, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

static char adrsft40[] = {
	0x00,
	0xd0,
};

static char adrsft41[] = {
	0xc3,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

static char adrsft42[] = {
	0x00,
	0xe0,
};

static char adrsft43[] = {
	0xc3,
	0x33, 0x33, 0x33, 0x33, 0x00,
	0x85, 0x7c, 0x04, 0x00, 0x0a,
	0x85, 0x7c, 0x04, 0x00, 0x0a,
};

static char adrsft44[] = {
	0x00,
	0xf0,
};

static char adrsft45[] = {
	0xc3,
	0x94, 0x00, 0x00, 0x00, 0x80,
	0x01, 0x00, 0x0a, 0x00, 0x80,
	0x01, 0x00, 0x0a, 0x00, 0x00,
};

static char adrsft46[] = {
	0x00,
	0x80,
};

static char adrsft47[] = {
	0xcb,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00,
};

static char adrsft48[] = {
	0x00,
	0x90,
};

static char adrsft49[] = {
	0xcb,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

static char adrsft50[] = {
	0x00,
	0xa0,
};

static char adrsft51[] = {
	0xcb,
	0x00, 0x00, 0x00, 0xbf, 0x00,
	0xff, 0x00, 0x00, 0x00, 0xff,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

static char adrsft52[] = {
	0x00,
	0xb0,
};

static char adrsft53[] = {
	0xcb,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x77, 0x77,
	0x00, 0x00,
};

static char adrsft54[] = {
	0x00,
	0xc0,
};

static char adrsft55[] = {
	0xcb,
	0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01,
};

static char adrsft56[] = {
	0x00,
	0xd0,
};

static char adrsft57[] = {
	0xcb,
	0x01, 0x01, 0x01, 0xff, 0x05,
	0xff, 0x01, 0x01, 0x01, 0xff,
	0x00, 0x01, 0x01, 0x01, 0x01,
};

static char adrsft58[] = {
	0x00,
	0xe0,
};

static char adrsft59[] = {
	0xcb,
	0x01, 0x01, 0x00, 0x01, 0x00,
	0x01, 0x00, 0x01, 0x77, 0x77,
	0x00, 0x00,
};

static char adrsft60[] = {
	0x00,
	0xf0,
};

static char adrsft61[] = {
	0xcb,
	0x00, 0xcc, 0xff, 0xff, 0xf5,
	0xfc, 0x0c, 0x33, 0x03, 0x00,
	0x22,
};

static char adrsft62[] = {
	0x00,
	0x80,
};

static char adrsft63[] = {
	0xcc,
	0x08, 0x09, 0x18, 0x19, 0x0c,
	0x0d, 0x0e, 0x0f, 0x07, 0x07,
	0x07, 0x07,
};

static char adrsft64[] = {
	0x00,
	0x90,
};

static char adrsft65[] = {
	0xcc,
	0x09, 0x08, 0x19, 0x18, 0x0f,
	0x0e, 0x0d, 0x0c, 0x07, 0x07,
	0x07, 0x07,
};

static char adrsft66[] = {
	0x00,
	0xa0,
};

static char adrsft67[] = {
	0xcc,
	0x14, 0x15, 0x16, 0x17, 0x1c,
	0x1d, 0x1e, 0x1f, 0x20, 0x01,
	0x02, 0x03, 0x07, 0x07, 0x00,
};

static char adrsft68[] = {
	0x00,
	0xb0,
};

static char adrsft69[] = {
	0xcc,
	0x01, 0x02, 0x03, 0x04, 0x05,
	0x06, 0x07, 0x07, 0x00,
};

static char adrsft70[] = {
	0x00,
	0x80,
};

static char adrsft71[] = {
	0xcd,
	0x02, 0x11, 0x12, 0x05, 0x07,
	0x1A, 0x19, 0x1A, 0x1A, 0x1A,
	0x24, 0x24, 0x24, 0x1d, 0x1e,
};

static char adrsft72[] = {
	0x00,
	0x90,
};

static char adrsft73[] = {
	0xcd,
	0x1f, 0x24, 0x24,
};

static char adrsft74[] = {
	0x00,
	0xa0,
};

static char adrsft75[] = {
	0xcd,
	0x01, 0x11, 0x12, 0x06, 0x08,
	0x1A, 0x19, 0x1A, 0x1A, 0x1A,
	0x24, 0x24, 0x24, 0x1d, 0x1e,
};

static char adrsft76[] = {
	0x00,
	0xb0,
};

static char adrsft77[] = {
	0xcd,
	0x1f, 0x24, 0x24,
};

static char adrsft78[] = {
	0x00,
	0x00,
};

static char adrsft79[] = {
	0xD8,
	0x22, 0x22,
};

static char adrsft80[] = {
	0x00,
	0x91,
};

static char adrsft81[] = {
	0xC5,
	0x1E, 0x28,
};

static char adrsft82[] = {
	0x00,
	0x00,
};

static char adrsft83[] = {
	0xE1,
	0x00, 0x0E, 0x19, 0x26, 0x30,
	0x37, 0x44, 0x55, 0x61, 0x72,
	0x7E, 0x86, 0x73, 0x6E, 0x69,
	0x5C, 0x4B, 0x3B, 0x2F, 0x29,
	0x21, 0x17, 0x13, 0x00,
};

static char adrsft84[] = {
	0x00,
	0x00,
};

static char adrsft85[] = {
	0x00,
	0x00,
};

static char adrsft86[] = {
	0xE2,
	0x00, 0x0E, 0x19, 0x26, 0x30,
	0x37, 0x44, 0x55, 0x61, 0x72,
	0x7E, 0x86, 0x73, 0x6E, 0x69,
	0x5C, 0x4B, 0x3B, 0x2F, 0x29,
	0x21, 0x17, 0x13, 0x00,
};

static char adrsft87[] = {
	0x00,
	0x00,
};

static char adrsft88[] = {
	0x00,
	0x00,
};

static char adrsft89[] = {
	0xE3,
	0x00, 0x0E, 0x19, 0x26, 0x30,
	0x37, 0x44, 0x55, 0x61, 0x72,
	0x7E, 0x86, 0x73, 0x6E, 0x69,
	0x5C, 0x4B, 0x3B, 0x2F, 0x29,
	0x21, 0x17, 0x13, 0x00,
};

static char adrsft90[] = {
	0x00,
	0x00,
};

static char adrsft91[] = {
	0x00,
	0x00,
};

static char adrsft92[] = {
	0xE4,
	0x00, 0x0E, 0x19, 0x26, 0x30,
	0x37, 0x44, 0x55, 0x61, 0x72,
	0x7E, 0x86, 0x73, 0x6E, 0x69,
	0x5C, 0x4B, 0x3B, 0x2F, 0x29,
	0x21, 0x17, 0x13, 0x00,
};

static char adrsft93[] = {
	0x00,
	0x00,
};

static char adrsft94[] = {
	0x00,
	0x00,
};

static char adrsft95[] = {
	0xE5,
	0x00, 0x0E, 0x19, 0x26, 0x30,
	0x37, 0x44, 0x55, 0x61, 0x72,
	0x7E, 0x86, 0x73, 0x6E, 0x69,
	0x5C, 0x4B, 0x3B, 0x2F, 0x29,
	0x21, 0x17, 0x13, 0x00,
};

static char adrsft96[] = {
	0x00,
	0x00,
};

static char adrsft97[] = {
	0x00,
	0x00,
};

static char adrsft98[] = {
	0xE6,
	0x00, 0x0E, 0x19, 0x26, 0x30,
	0x37, 0x44, 0x55, 0x61, 0x72,
	0x7E, 0x86, 0x73, 0x6E, 0x69,
	0x5C, 0x4B, 0x3B, 0x2F, 0x29,
	0x21, 0x17, 0x13, 0x00,
};

static char adrsft99[] = {
	0x00,
	0x00,
};

static char adrsft100[] = {
	0x00,
	0x00,
};

// VCOMDC
static char adrsft101[] = {
	0xD9,
	0x00, 0xc3, 0x00, 0xc3, 0x00,
	0xc3, 0x00, 0xc3,
};

// for video mode
static char adrsft102[] = {
	0x00,
	0xA0,
};

static char adrsft103[] = {
	0xC1,
	0x00, 0xc0, 0x11,
};

#if 0
static char adrsft104[] = {
	0x00,
	0x00,
};

// bypass
static char adrsft105[] = {
	0x1C,
	0x03,
};
#endif

// for ODC
static char adrsft106[] = {
	0x00,
	0xe0,
};

// frame base : adrsft107[1] = 0x1c
// line_8 base : adrsft107[1] = 0x5c
// line_16 base : adrsft107[1] = 0x9c
// line_32 base : adrsft107[1] = 0xdc
static char adrsft107[] = {
	0xB4,
	0x1c, 0x19, 0x3f, 0x01, 0x64,
	0x5c, 0x01, 0xa0, 0x5f, 0xa0,
};

// for ODC
static char adrsft108[] = {
	0x00,
	0xf0,
};

static char adrsft109[] = {
	0xb4,
	0xff,
};

// ODC 3X
// 0x00:disable_orise3x,  0x06:enable_orise3x
static char orise3x_disable0[] = {
	0x00,
	0x00,
};

static char orise3x_disable1[] = {
	0x1C,
	0x00,
};

static char orise3x_enable0[] = {
	0x00,
	0x00,
};

static char orise3x_enable1[] = {
	0x1C,
	0x06,
};

static char tear_no[] = {
	0x35,
	0x00,
};

static char exit_sleep[] = {
	0x11,
};

static char display_on[] = {
	0x29,
};


/*******************************************************************************
** Power OFF Sequence(Normal to power off)
*/
static char display_off[] = {
	0x28,
};

static char enter_sleep[] = {
	0x10,
};

static struct dsi_cmd_desc lcd_display_init_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft0), adrsft0},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft1), adrsft1},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft2), adrsft2},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft3), adrsft3},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft4), adrsft4},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft5), adrsft5},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft6), adrsft6},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft7), adrsft7},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft8), adrsft8},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft9), adrsft9},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft10), adrsft10},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft11), adrsft11},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft12), adrsft12},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft13), adrsft13},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft14), adrsft14},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft15), adrsft15},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft16), adrsft16},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft17), adrsft17},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft18), adrsft18},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft19), adrsft19},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft20), adrsft20},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft21), adrsft21},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft22), adrsft22},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft23), adrsft23},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft24), adrsft24},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft25), adrsft25},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft26), adrsft26},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft27), adrsft27},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft28), adrsft28},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft29), adrsft29},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft30), adrsft30},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft31), adrsft31},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft32), adrsft32},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft33), adrsft33},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft34), adrsft34},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft35), adrsft35},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft36), adrsft36},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft37), adrsft37},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft38), adrsft38},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft39), adrsft39},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft40), adrsft40},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft41), adrsft41},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft42), adrsft42},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft43), adrsft43},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft44), adrsft44},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft45), adrsft45},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft46), adrsft46},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft47), adrsft47},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft48), adrsft48},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft49), adrsft49},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft50), adrsft50},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft51), adrsft51},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft52), adrsft52},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft53), adrsft53},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft54), adrsft54},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft55), adrsft55},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft56), adrsft56},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft57), adrsft57},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft58), adrsft58},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft59), adrsft59},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft60), adrsft60},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft61), adrsft61},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft62), adrsft62},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft63), adrsft63},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft64), adrsft64},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft65), adrsft65},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft66), adrsft66},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft67), adrsft67},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft68), adrsft68},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft69), adrsft69},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft70), adrsft70},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft71), adrsft71},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft72), adrsft72},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft73), adrsft73},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft74), adrsft74},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft75), adrsft75},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft76), adrsft76},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft77), adrsft77},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft78), adrsft78},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft79), adrsft79},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft80), adrsft80},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft81), adrsft81},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft82), adrsft82},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft83), adrsft83},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft84), adrsft84},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft85), adrsft85},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft86), adrsft86},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft87), adrsft87},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft88), adrsft88},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft89), adrsft89},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft90), adrsft90},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft91), adrsft91},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft92), adrsft92},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft93), adrsft93},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft94), adrsft94},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft95), adrsft95},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft96), adrsft96},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft97), adrsft97},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft98), adrsft98},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft99), adrsft99},

	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft100), adrsft100},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft101), adrsft101},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft102), adrsft102},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft103), adrsft103},
	//{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft104), adrsft104},
	//{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft105), adrsft105},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft106), adrsft106},
	{DTYPE_DCS_LWRITE, 0, 1, WAIT_TYPE_MS, sizeof(adrsft107), adrsft107},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft108), adrsft108},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(adrsft109), adrsft109},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(tear_no), tear_no},
};

static struct dsi_cmd_desc lcd_ifbc_orise3x_dis_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(orise3x_disable0), orise3x_disable0},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(orise3x_disable1), orise3x_disable1},
};

static struct dsi_cmd_desc lcd_ifbc_orise3x_en_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(orise3x_enable0), orise3x_enable0},
	{DTYPE_DCS_WRITE1, 0, 1, WAIT_TYPE_MS, sizeof(orise3x_enable1), orise3x_enable1},
};

static struct dsi_cmd_desc lcd_display_on_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 150, WAIT_TYPE_MS, sizeof(exit_sleep), exit_sleep},
	{DTYPE_DCS_WRITE, 0, 0, WAIT_TYPE_MS, sizeof(display_on), display_on},
};

static struct dsi_cmd_desc lcd_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 150, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep},
	{DTYPE_DCS_WRITE, 0, 60, WAIT_TYPE_MS,
		sizeof(display_off), display_off},
};


/*******************************************************************************
** LCD VCC
*/
#define VCC_LCDIO_NAME		"lcdio-vcc"
#define VCC_LCDANALOG_NAME	"lcdanalog-vcc"

static struct regulator *vcc_lcdio;
static struct regulator *vcc_lcdanalog;

static struct vcc_desc lcd_vcc_init_cmds[] = {
	/* vcc get */
	{DTYPE_VCC_GET, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_GET, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},

	/* vcc set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 3100000, 3100000, WAIT_TYPE_MS, 0},
	/* io set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDIO_NAME, &vcc_lcdio, 1800000, 1800000, WAIT_TYPE_MS, 0},
};

static struct vcc_desc lcd_vcc_finit_cmds[] = {
	/* vcc put */
	{DTYPE_VCC_PUT, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_PUT, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},
};

static struct vcc_desc lcd_vcc_enable_cmds[] = {
	/* vcc enable */
	{DTYPE_VCC_ENABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_ENABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
};

static struct vcc_desc lcd_vcc_disable_cmds[] = {
	/* vcc disable */
	{DTYPE_VCC_DISABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_DISABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
};


/*******************************************************************************
** LCD IOMUX
*/
static struct pinctrl_data pctrl;

static struct pinctrl_cmd_desc lcd_pinctrl_init_cmds[] = {
	{DTYPE_PINCTRL_GET, &pctrl, 0},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc lcd_pinctrl_normal_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
};

static struct pinctrl_cmd_desc lcd_pinctrl_lowpower_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc lcd_pinctrl_finit_cmds[] = {
	{DTYPE_PINCTRL_PUT, &pctrl, 0},
};


/*******************************************************************************
** LCD GPIO
*/
#define GPIO_LCD_BL_ENABLE_NAME	"gpio_lcd_bl_enable"
#define GPIO_LCD_VCC1V8_NAME	"gpio_lcd_vcc1v8"
#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"
#define GPIO_LCD_P5V5_ENABLE_NAME	"gpio_lcd_p5v5_enable"
#define GPIO_LCD_N5V5_ENABLE_NAME	"gpio_lcd_n5v5_enable"

static uint32_t gpio_lcd_bl_enable;
static uint32_t gpio_lcd_vcc1v8;
static uint32_t gpio_lcd_reset;
static uint32_t gpio_lcd_p5v5_enable;
static uint32_t gpio_lcd_n5v5_enable;

static struct gpio_desc fpga_lcd_gpio_request_cmds[] = {
	/* vcc1v8 */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_US, 0,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
	/* reset */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
};

static struct gpio_desc fpga_lcd_gpio_free_cmds[] = {
	/* reset */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* vcc1v8 */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
};

static struct gpio_desc fpga_lcd_gpio_normal_cmds[] = {
	/* vcc1v8 enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 50,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 1},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 1},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 1},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 50,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 10,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
};

static struct gpio_desc fpga_lcd_gpio_lowpower_cmds[] = {
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* vcc1v8 disable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
	/* reset input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* AVEE_-5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* vcc1v8 disable */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
};

static struct gpio_desc asic_lcd_gpio_request_cmds[] = {
	/* AVDD_5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* reset */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	/* backlight enable */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
};

static struct gpio_desc asic_lcd_gpio_free_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* reset */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};

static struct gpio_desc asic_lcd_gpio_normal_cmds[] = {
	/* AVDD_5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 1},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 20,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 1},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 20,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 20,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 20,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1},
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 1},
};

static struct gpio_desc asic_lcd_gpio_lowpower_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},

	/* backlight enable input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* reset input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};


/*******************************************************************************
**
*/
static int mipi_jdi_panel_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (g_lcd_fpga_flag == 0) {
		// lcd pinctrl normal
		pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
			ARRAY_SIZE(lcd_pinctrl_normal_cmds));

		// lcd gpio request
		gpio_cmds_tx(asic_lcd_gpio_request_cmds,
			ARRAY_SIZE(asic_lcd_gpio_request_cmds));
	} else {
		// lcd gpio request
		gpio_cmds_tx(fpga_lcd_gpio_request_cmds,
			ARRAY_SIZE(fpga_lcd_gpio_request_cmds));
	}

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_jdi_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;

#if LCD_POWER_STATUS_CHECK
	uint32_t status = 0;
	uint32_t try_times = 0;
#endif

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		if (g_lcd_fpga_flag == 0) {
			// lcd vcc enable
			vcc_cmds_tx(pdev, lcd_vcc_enable_cmds,
				ARRAY_SIZE(lcd_vcc_enable_cmds));
		}

		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {
		if (g_lcd_fpga_flag == 0) {
			// lcd pinctrl normal
			pinctrl_cmds_tx(pdev, lcd_pinctrl_normal_cmds,
				ARRAY_SIZE(lcd_pinctrl_normal_cmds));

			// lcd gpio request
			gpio_cmds_tx(asic_lcd_gpio_request_cmds, \
				ARRAY_SIZE(asic_lcd_gpio_request_cmds));

			// lcd gpio normal
			gpio_cmds_tx(asic_lcd_gpio_normal_cmds, \
				ARRAY_SIZE(asic_lcd_gpio_normal_cmds));
		} else {
			// lcd gpio request
			gpio_cmds_tx(fpga_lcd_gpio_request_cmds, \
				ARRAY_SIZE(fpga_lcd_gpio_request_cmds));

			// lcd gpio normal
			gpio_cmds_tx(fpga_lcd_gpio_normal_cmds, \
				ARRAY_SIZE(fpga_lcd_gpio_normal_cmds));
		}

		// lcd color management sequence
		mipi_dsi_cmds_tx(lcd_display_init_cmds, \
			ARRAY_SIZE(lcd_display_init_cmds), mipi_dsi0_base);

		if (pinfo->ifbc_type == IFBC_TYPE_ORISE3X) {
			mipi_dsi_cmds_tx(lcd_ifbc_orise3x_en_cmds, \
				ARRAY_SIZE(lcd_ifbc_orise3x_en_cmds), mipi_dsi0_base);
		} else {
			mipi_dsi_cmds_tx(lcd_ifbc_orise3x_dis_cmds, \
				ARRAY_SIZE(lcd_ifbc_orise3x_dis_cmds), mipi_dsi0_base);
		}

		// lcd display on sequence
		mipi_dsi_cmds_tx(lcd_display_on_cmds, \
			ARRAY_SIZE(lcd_display_on_cmds), mipi_dsi0_base);

	#if LCD_POWER_STATUS_CHECK
		//check lcd power status
		outp32(mipi_dsi0_base + MIPIDSI_GEN_HDR_OFFSET, 0x0A06);
		status = inp32(mipi_dsi0_base + MIPIDSI_CMD_PKT_STATUS_OFFSET);
		while (status & 0x10) {
			udelay(50);
			if (++try_times > 100) {
				try_times = 0;
				HISI_FB_ERR("Read lcd power status timeout!\n");
				break;
			}

			status = inp32(mipi_dsi0_base + MIPIDSI_CMD_PKT_STATUS_OFFSET);
		}

		status = inp32(mipi_dsi0_base + MIPIDSI_GEN_PLD_DATA_OFFSET);
		HISI_FB_INFO("LCD Power State = 0x%x.\n", status);
	#endif

		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
		;
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_jdi_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +!\n", hisifd->index);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	// backlight off
	hisi_lcd_backlight_off(pdev);

	// lcd display off sequence
	mipi_dsi_cmds_tx(lcd_display_off_cmds, \
		ARRAY_SIZE(lcd_display_off_cmds), mipi_dsi0_base);

	if (g_lcd_fpga_flag == 0) {
		// lcd gpio lowpower
		gpio_cmds_tx(asic_lcd_gpio_lowpower_cmds, \
			ARRAY_SIZE(asic_lcd_gpio_lowpower_cmds));
		// lcd gpio free
		gpio_cmds_tx(asic_lcd_gpio_free_cmds, \
			ARRAY_SIZE(asic_lcd_gpio_free_cmds));

		// lcd pinctrl lowpower
		pinctrl_cmds_tx(pdev, lcd_pinctrl_lowpower_cmds,
			ARRAY_SIZE(lcd_pinctrl_lowpower_cmds));

		mdelay(3);
		// lcd vcc disable
		vcc_cmds_tx(pdev, lcd_vcc_disable_cmds,
			ARRAY_SIZE(lcd_vcc_disable_cmds));
	} else {
		// lcd gpio lowpower
		gpio_cmds_tx(fpga_lcd_gpio_lowpower_cmds, \
			ARRAY_SIZE(fpga_lcd_gpio_lowpower_cmds));
		// lcd gpio free
		gpio_cmds_tx(fpga_lcd_gpio_free_cmds, \
			ARRAY_SIZE(fpga_lcd_gpio_free_cmds));
	}

	HISI_FB_INFO("fb%d, -!\n", hisifd->index);

	return 0;
}

static int mipi_jdi_panel_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);

	if (!hisifd) {
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (g_lcd_fpga_flag == 0) {
		// lcd vcc finit
		vcc_cmds_tx(pdev, lcd_vcc_finit_cmds,
			ARRAY_SIZE(lcd_vcc_finit_cmds));

		// lcd pinctrl finit
		pinctrl_cmds_tx(pdev, lcd_pinctrl_finit_cmds,
			ARRAY_SIZE(lcd_pinctrl_finit_cmds));
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_jdi_panel_set_backlight(struct platform_device *pdev, uint32_t bl_level)
{
	int ret = 0;
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	char bl_level_adjust[2] = {
		0x51,
		0x00,
	};

	struct dsi_cmd_desc lcd_bl_level_adjust[] = {
		{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
			sizeof(bl_level_adjust), bl_level_adjust},
	};

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, bl_level=%d.\n", hisifd->index, bl_level);

	if (hisifd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		ret = hisi_pwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_BLPWM) {
		ret = hisi_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_SH_BLPWM) {
		ret = hisi_sh_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
		mipi_dsi0_base = hisifd->mipi_dsi0_base;

		bl_level_adjust[1] = bl_level*255 / hisifd->panel_info.bl_max;
		mipi_dsi_cmds_tx(lcd_bl_level_adjust, \
			ARRAY_SIZE(lcd_bl_level_adjust), mipi_dsi0_base);
	} else {
		HISI_FB_ERR("fb%d, not support this bl_set_type(%d)!\n",
			hisifd->index, hisifd->panel_info.bl_set_type);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static char lcd_disp_x[] = {
	0x2A,
	0x00, 0x00,0x04,0x37
};

static char lcd_disp_y[] = {
	0x2B,
	0x00, 0x00,0x07,0x7F
};

static struct dsi_cmd_desc set_display_address[] = {
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_x), lcd_disp_x},
	{DTYPE_DCS_LWRITE, 0, 5, WAIT_TYPE_US,
		sizeof(lcd_disp_y), lcd_disp_y},
};

static int mipi_jdi_panel_set_display_region(struct platform_device *pdev,
	struct dss_rect *dirty)
{
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL || dirty == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	mipi_dsi0_base = hisifd->mipi_dsi0_base;
	pinfo = &(hisifd->panel_info);

	BUG_ON(g_lcd_dirty_lines == 0);

	if ((dirty->x != 0) || (dirty->w != pinfo->xres) ||
		((dirty->y % g_lcd_dirty_lines) != 0) || ((dirty->h % g_lcd_dirty_lines) != 0) ||
		(dirty->x >= pinfo->xres) || (dirty->w > pinfo->xres) || ((dirty->x + dirty->w) > pinfo->xres) ||
		(dirty->y >= pinfo->yres) || (dirty->h > pinfo->yres) || ((dirty->y + dirty->h) > pinfo->yres)) {
		HISI_FB_ERR("dirty_region(%d,%d, %d,%d) , line_base=%d, not support!\n",
			dirty->x, dirty->y, dirty->w, dirty->h, g_lcd_dirty_lines);

		BUG_ON(1);
	}

	lcd_disp_x[1] = (dirty->x >> 8) & 0xff;
	lcd_disp_x[2] = dirty->x & 0xff;
	lcd_disp_x[3] = ((dirty->x + dirty->w - 1) >> 8) & 0xff;
	lcd_disp_x[4] = (dirty->x + dirty->w - 1) & 0xff;
	lcd_disp_y[1] = (dirty->y >> 8) & 0xff;
	lcd_disp_y[2] = dirty->y & 0xff;
	lcd_disp_y[3] = ((dirty->y + dirty->h - 1) >> 8) & 0xff;
	lcd_disp_y[4] = (dirty->y + dirty->h - 1) & 0xff;

	mipi_dsi_cmds_tx(set_display_address, \
		ARRAY_SIZE(set_display_address), mipi_dsi0_base);

	return 0;
}


/*******************************************************************************
**
*/
static struct hisi_panel_info g_panel_info = {0};
static struct hisi_fb_panel_data g_panel_data = {
	.panel_info = &g_panel_info,
	.set_fastboot = mipi_jdi_panel_set_fastboot,
	.on = mipi_jdi_panel_on,
	.off = mipi_jdi_panel_off,
	.remove = mipi_jdi_panel_remove,
	.set_backlight = mipi_jdi_panel_set_backlight,
	.set_display_region = mipi_jdi_panel_set_display_region,
};


/*******************************************************************************
**
*/
static int mipi_jdi_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;
	uint32_t bl_type = 0;
	uint32_t lcd_display_type = 0;
	uint32_t lcd_ifbc_type = 0;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_JDI_OTM1906A);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_JDI_OTM1906A);
		goto err_return;
	}

	ret = of_property_read_u32(np, LCD_DISPLAY_TYPE_NAME, &lcd_display_type);
	if (ret) {
		HISI_FB_ERR("get lcd_display_type failed!\n");
		lcd_display_type = PANEL_MIPI_CMD;
	}

	ret = of_property_read_u32(np, LCD_IFBC_TYPE_NAME, &lcd_ifbc_type);
	if (ret) {
		HISI_FB_ERR("get ifbc_type failed!\n");
		lcd_ifbc_type = IFBC_TYPE_NONE;
	}

	ret = of_property_read_u32(np, LCD_BL_TYPE_NAME, &bl_type);
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_MIPI;
	}
	HISI_FB_INFO("bl_type=0x%x.", bl_type);

	if (hisi_fb_device_probe_defer(lcd_display_type, bl_type)) {
		goto err_probe_defer;
	}

	HISI_FB_DEBUG("+.\n");

	HISI_FB_INFO("%s\n", DTS_COMP_JDI_OTM1906A);

	ret = of_property_read_u32(np, "fpga_flag", &g_lcd_fpga_flag);
	if (ret) {
		HISI_FB_WARNING("need to get g_lcd_fpga_flag resource in fpga, not needed in asic!\n");
	}

	if (g_lcd_fpga_flag == 1) {
		//gpio_5_3
		gpio_lcd_p5v5_enable = of_get_named_gpio(np, "gpios", 0);
		//gpio_5_7
		gpio_lcd_vcc1v8 = of_get_named_gpio(np, "gpios", 1);
		//gpio_9_4
		gpio_lcd_reset = of_get_named_gpio(np, "gpios", 3);
		//gpio_9_6
		gpio_lcd_n5v5_enable = of_get_named_gpio(np, "gpios", 5);
	} else {
		//gpio_1_1
		gpio_lcd_n5v5_enable = of_get_named_gpio(np, "gpios", 0);
		//gpio_1_2
		gpio_lcd_bl_enable = of_get_named_gpio(np, "gpios", 1);
		// gpio_1_7
		gpio_lcd_p5v5_enable = of_get_named_gpio(np, "gpios", 2);
		//gpio_2_4
		gpio_lcd_reset = of_get_named_gpio(np, "gpios", 3);
	}

	pdev->id = 1;
	// init lcd panel info
	pinfo = g_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 1080;
	pinfo->yres = 1920;
	pinfo->width = 69;
	pinfo->height = 122;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = bl_type;

	if (pinfo->bl_set_type == BL_SET_BY_BLPWM)
		pinfo->blpwm_input_ena = 0;

#ifdef CONFIG_BACKLIGHT_10000
	pinfo->bl_min = 157;
	pinfo->bl_max = 9960;
	pinfo->bl_default = 4000;
	pinfo->blpwm_precision_type = BLPWM_PRECISION_10000_TYPE;
#else
	pinfo->bl_min = 1;
	pinfo->bl_max = 255;
	pinfo->bl_default = 102;
#endif

	pinfo->type = lcd_display_type;
	pinfo->ifbc_type = lcd_ifbc_type;

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;

	//sbl
	pinfo->sbl_support = 0;
	pinfo->smart_bl.strength_limit = 0xff;
	pinfo->smart_bl.calibration_a = 0;
	pinfo->smart_bl.calibration_b = 0;
	pinfo->smart_bl.calibration_c = 0;
	pinfo->smart_bl.calibration_d = 0;
	pinfo->smart_bl.t_filter_control = 0;
	pinfo->smart_bl.backlight_min = 0;
	pinfo->smart_bl.backlight_max = 0;
	pinfo->smart_bl.backlight_scale = 0xffff;
	pinfo->smart_bl.ambient_light_min = 0;
	pinfo->smart_bl.filter_a = 0;
	pinfo->smart_bl.filter_b = 0;

	if (g_lcd_fpga_flag == 1) {
		//ldi
		pinfo->ldi.h_back_porch = 88; // 42
		pinfo->ldi.h_front_porch = 100;// 42
		pinfo->ldi.h_pulse_width = 4;
		pinfo->ldi.v_back_porch = 5;
		pinfo->ldi.v_front_porch = 6;
		pinfo->ldi.v_pulse_width = 1;

		//mipi
		pinfo->mipi.dsi_bit_clk = 120;
		pinfo->mipi.dsi_bit_clk_val1 = 110; //110.4
		pinfo->mipi.dsi_bit_clk_val2 = 120;
		pinfo->mipi.dsi_bit_clk_val3 = 130; //129.6
		pinfo->mipi.dsi_bit_clk_val4 = 140; //139.2
		pinfo->mipi.dsi_bit_clk_val5 = 150; //148.8
		pinfo->dsi_bit_clk_upt_support = 0;
		pinfo->mipi.dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk;

		pinfo->mipi.non_continue_en = 0;

		pinfo->pxl_clk_rate = 20 * 1000000; //40 * 1000000;
	} else {
		//ldi
		if (is_mipi_cmd_panel_ext(pinfo)) {
			//63fps
			pinfo->ldi.h_back_porch = 23;//88;
			pinfo->ldi.h_front_porch = 50;//100;
			pinfo->ldi.h_pulse_width = 20;//4;
			pinfo->ldi.v_back_porch = 12;//5;
			pinfo->ldi.v_front_porch = 14;//6;
			pinfo->ldi.v_pulse_width = 4;//1;
		} else {
			//60fps
			pinfo->ldi.h_back_porch = 23;
			pinfo->ldi.h_front_porch = 107;
			pinfo->ldi.h_pulse_width = 20;
			pinfo->ldi.v_back_porch = 12;
			pinfo->ldi.v_front_porch = 14;
			pinfo->ldi.v_pulse_width = 4;
		}

		//mipi
		pinfo->mipi.dsi_bit_clk = 480;
		pinfo->mipi.dsi_bit_clk_val1 = 471;
		pinfo->mipi.dsi_bit_clk_val2 = 480;
		pinfo->mipi.dsi_bit_clk_val3 = 490;
		pinfo->mipi.dsi_bit_clk_val4 = 500;
		//pinfo->mipi.dsi_bit_clk_val5 = ;
		pinfo->dsi_bit_clk_upt_support = 0;
		pinfo->mipi.dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk;

		pinfo->mipi.non_continue_en = 0;

		pinfo->pxl_clk_rate = 144 * 1000000UL;
	}

	//mipi
	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.max_tx_esc_clk = 10 * 1000000;
	pinfo->mipi.burst_mode = 0;

	pinfo->pxl_clk_rate_div = 1;

#if LINE_BASE_8
	adrsft107[1] = 0x5C;
	g_lcd_dirty_lines = 8;
#elif LINE_BASE_16
	adrsft107[1] = 0x9C;
	g_lcd_dirty_lines = 16;
#elif LINE_BASE_32
	adrsft107[1] = 0xDC;
	g_lcd_dirty_lines = 32;
#else
	adrsft107[1] = 0x1C;
	g_lcd_dirty_lines = 0;
#endif

	if (is_mipi_cmd_panel_ext(pinfo)) {
		pinfo->vsync_ctrl_type = 0;//VSYNC_CTRL_ISR_OFF | VSYNC_CTRL_MIPI_ULPS | VSYNC_CTRL_CLK_OFF;
		pinfo->dirty_region_updt_support = g_lcd_dirty_lines && 0;
		pinfo->dirty_region_info.left_align = -1;
		pinfo->dirty_region_info.right_align = -1;
		pinfo->dirty_region_info.top_align = g_lcd_dirty_lines;
		pinfo->dirty_region_info.bottom_align = g_lcd_dirty_lines;
		pinfo->dirty_region_info.w_align = -1;
		pinfo->dirty_region_info.h_align = -1;
		pinfo->dirty_region_info.w_min = pinfo->xres;
		pinfo->dirty_region_info.h_min = -1;
		pinfo->dirty_region_info.top_start = -1;
		pinfo->dirty_region_info.bottom_start = -1;
	} else {
		pinfo->mipi.burst_mode = DSI_BURST_SYNC_PULSES_1;
		pinfo->vsync_ctrl_type = 0;
		pinfo->dirty_region_updt_support = 0;
	}

	if (pinfo->ifbc_type == IFBC_TYPE_ORISE3X) {
		pinfo->ifbc_cmp_dat_rev0 = 0;
		pinfo->ifbc_cmp_dat_rev1 = 0;
		pinfo->ifbc_auto_sel = 1;
		pinfo->ifbc_orise_ctr = 1;

		//FIXME:
		pinfo->pxl_clk_rate_div = 3;

	#if LINE_BASE_8
		pinfo->ifbc_orise_ctl = IFBC_ORISE_CTL_8LINE;
	#elif LINE_BASE_16
		pinfo->ifbc_orise_ctl = IFBC_ORISE_CTL_16LINE;
	#elif LINE_BASE_32
		pinfo->ifbc_orise_ctl = IFBC_ORISE_CTL_32LINE;
	#else
		pinfo->ifbc_orise_ctl = IFBC_ORISE_CTL_FRAME;
	#endif
	}

	if (pinfo->pxl_clk_rate_div > 1) {
		pinfo->ldi.h_back_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_front_porch /= pinfo->pxl_clk_rate_div;
		pinfo->ldi.h_pulse_width /= pinfo->pxl_clk_rate_div;
	}

	if (g_lcd_fpga_flag == 0) {
		// lcd vcc init
		ret = vcc_cmds_tx(pdev, lcd_vcc_init_cmds,
			ARRAY_SIZE(lcd_vcc_init_cmds));
		if (ret != 0) {
			HISI_FB_ERR("LCD vcc init failed!\n");
			goto err_return;
		}

		// lcd pinctrl init
		ret = pinctrl_cmds_tx(pdev, lcd_pinctrl_init_cmds,
			ARRAY_SIZE(lcd_pinctrl_init_cmds));
		if (ret != 0) {
			HISI_FB_ERR("Init pinctrl failed, defer\n");
			goto err_return;
		}

		// lcd vcc enable
		if (is_fastboot_display_enable()) {
			vcc_cmds_tx(pdev, lcd_vcc_enable_cmds,
				ARRAY_SIZE(lcd_vcc_enable_cmds));
		}
	}

	// alloc panel device data
	ret = platform_device_add_data(pdev, &g_panel_data,
		sizeof(struct hisi_fb_panel_data));
	if (ret) {
		HISI_FB_ERR("platform_device_add_data failed!\n");
		goto err_device_put;
	}

	hisi_fb_add_device(pdev);

	HISI_FB_DEBUG("-.\n");

	return 0;

err_device_put:
	platform_device_put(pdev);
err_return:
	return ret;
err_probe_defer:
	return -EPROBE_DEFER;

	return ret;
}

static const struct of_device_id hisi_panel_match_table[] = {
	{
		.compatible = DTS_COMP_JDI_OTM1906A,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_panel_match_table);

static struct platform_driver this_driver = {
	.probe = mipi_jdi_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_jdi_OTM1906A",
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_jdi_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_jdi_panel_init);
