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


#define DTS_COMP_MIPI_TIANMA_OTM9608A	"hisilicon,mipi_tianma_OTM9608A"

static int g_lcd_fpga_flag = 0;


/********************************tianma_OTM9608A*****start***********************
**Power ON Sequence(sleep mode to Normal mode)
*/

// Enable cmd
static char tianma_OTM9608A_power_on_param1[] = {
	0xff,
	0x96, 0x08, 0x01,
};

static char tianma_OTM9608A_power_on_param2[] = {
	0x00,
	0x80,
};

static char tianma_OTM9608A_power_on_param3[] = {
	0xff,
	0x96, 0x08,
};

static char tianma_OTM9608A_power_on_param4[] = {
	0x00,
	0x00,
};

static char tianma_OTM9608A_power_on_param5[] = {
	0xa0,
	0x00,
};

static char tianma_OTM9608A_power_on_param6[] = {
	0x00,
	0x80,
};

static char tianma_OTM9608A_power_on_param7[] = {
	0xb3,
	0x00, 0x00, 0x20, 0x00,
	0x00,
};

static char tianma_OTM9608A_power_on_param8[] = {
	0x00,
	0xc0,
};

static char tianma_OTM9608A_power_on_param9[] = {
	0xb3,
	0x09,
};

static char tianma_OTM9608A_power_on_param10[] = {
	0x00,
	0x80,
};

static char tianma_OTM9608A_power_on_param11[] = {
	0xc0,
	0x00, 0x48, 0x00, 0x0f,
	0x11, 0x00, 0x48, 0x0f,
	0x11,
};

static char tianma_OTM9608A_power_on_param12[] = {
	0x00,
	0x92,
};

static char tianma_OTM9608A_power_on_param13[] = {
	0xc0,
	0x00, 0x10, 0x00, 0x13,
};

static char tianma_OTM9608A_power_on_param14[] = {
	0x00,
	0xa2,
};

static char tianma_OTM9608A_power_on_param15[] = {
	0xc0,
	0x0c, 0x05, 0x02,
};

static char tianma_OTM9608A_power_on_param16[] = {
	0x00,
	0xb3,
};

static char tianma_OTM9608A_power_on_param17[] = {
	0xc0,
	0x00, 0x50,
};

static char tianma_OTM9608A_power_on_param18[] = {
	0x00,
	0x81,
};

//refresh rate 0x55->60Hz
static char tianma_OTM9608A_power_on_param19[] = {
	0xc1,
	0x55,
};

static char tianma_OTM9608A_power_on_param20[] = {
	0x00,
	0x80,
};

//0xc480 = 0x30 source output GND during porch and non-display area
static char tianma_OTM9608A_power_on_param21[] = {
	0xc4,
	0x30, 0x84,
};

static char tianma_OTM9608A_power_on_param22[] = {
	0x00,
	0xa0,
};

static char tianma_OTM9608A_power_on_param23[] = {
	0xc4,
	0x33, 0x09, 0x90, 0x2b,
	0x33, 0x09, 0x90, 0x54,
};

static char tianma_OTM9608A_power_on_param24[] = {
	0x00,
	0x80,
};

static char tianma_OTM9608A_power_on_param25[] = {
	0xc5,
	0x08, 0x00, 0xa0, 0x11,
};

static char tianma_OTM9608A_power_on_param26[] = {
	0x00,
	0x90,
};

static char tianma_OTM9608A_power_on_param27[] = {
	0xc5,
	0x96, 0x19, 0x01, 0x79,
	0x33, 0x33, 0x34,
};

static char tianma_OTM9608A_power_on_param28[] = {
	0x00,
	0xa0,
};

static char tianma_OTM9608A_power_on_param29[] = {
	0xc5,
	0x96, 0x16, 0x00, 0x79,
	0x33, 0x33, 0x34,
};

static char tianma_OTM9608A_power_on_param30[] = {
	0x00,
	0x00,
};
static char tianma_OTM9608A_power_on_param31[] = {
	0xd8,
	0x5f, 0x5f,
};

//gamma 2.5 parameter
static char tianma_OTM9608A_power_on_param32[] = {
	0x00,
	0x00,
};

static char tianma_OTM9608A_power_on_param33[] = {
	0xe1,
	0x01, 0x0e, 0x15, 0x0E,
	0x07, 0x13, 0x0C, 0x0B,
	0x03, 0x06, 0x09, 0x07,
	0x0C, 0x0D, 0x08, 0x01,
};

//GOA ECLK Setting and GOA Other Options1 and GOA Signal Toggle Option Setting
static char tianma_OTM9608A_power_on_param34[] = {
	0x00,
	0x00,
};

static char tianma_OTM9608A_power_on_param35[] = {
	0xe2,
	0x01, 0x0e, 0x15, 0x0E,
	0x07, 0x13, 0x0C, 0x0B,
	0x03, 0x06, 0x09, 0x07,
	0x0C, 0x0D, 0x08, 0x01,
};

static char tianma_OTM9608A_power_on_param36[] = {
	0x00,
	0xb0,
};

static char tianma_OTM9608A_power_on_param37[] = {
	0xc5,
	0x04, 0xa8,
};

static char tianma_OTM9608A_power_on_param38[] = {
	0x00,
	0x80,
};

static char tianma_OTM9608A_power_on_param39[] = {
	0xc6,
	0x64,
};

static char tianma_OTM9608A_power_on_param40[] = {
	0x00,
	0xb0,
};

static char tianma_OTM9608A_power_on_param41[] = {
	0xc6,
	0x03, 0x10, 0x00, 0x1f,
	0x12,
};

static char tianma_OTM9608A_power_on_param42[] = {
	0x00,
	0xb7,
};

static char tianma_OTM9608A_power_on_param43[] = {
	0xb0,
	0x10,
};

static char tianma_OTM9608A_power_on_param44[] = {
	0x00,
	0xc0,
};

static char tianma_OTM9608A_power_on_param45[] = {
	0xb0,
	0x55,
};

static char tianma_OTM9608A_power_on_param46[] = {
	0x00,
	0xb1,
};

static char tianma_OTM9608A_power_on_param47[] = {
	0xb0,
	0x03,
};

//increase mipi clk width , or display overturn probability
static char tianma_OTM9608A_power_on_param48[] = {
	0x00,
	0xb2,
};

static char tianma_OTM9608A_power_on_param49[] = {
	0xb0,
	0x06,
};

static char tianma_OTM9608A_power_on_param50[] = {
	0x00,
	0x80,
};

static char tianma_OTM9608A_power_on_param51[] = {
	0xcb,
	0x05, 0x00, 0x00, 0x00, 0x00,
	0x05, 0x00, 0x00, 0x00, 0x00,
};

static char tianma_OTM9608A_power_on_param52[] = {
	0x00,
	0x90,
};

static char tianma_OTM9608A_power_on_param53[] = {
	0xcb,
	0x55,0x55,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param54[] = {
	0x00,
	0xa0,
};

static char tianma_OTM9608A_power_on_param55[] = {
	0xcb,
	0x00,0x00,0x00,0x00,0x00,
	0x55,0x55,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param56[] = {
	0x00,
	0xb0,
};

static char tianma_OTM9608A_power_on_param57[] = {
	0xcb,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param58[] = {
	0x00,
	0xc0,
};

static char tianma_OTM9608A_power_on_param59[] = {
	0xcb,
	0x55,0x55,0x00,0x00,0x00,
	0x04,0x00,0x04,0x00,0x04,
	0x00,0x04,0x04,0x04,0x00,
};

static char tianma_OTM9608A_power_on_param60[] = {
	0x00,
	0xd0,
};

static char tianma_OTM9608A_power_on_param61[] = {
	0xcb,
	0x04,0x00,0x00,0x00,0x00,
	0x55,0x55,0x00,0x00,0x00,
	0x04,0x00,0x04,0x00,0x04,
};

static char tianma_OTM9608A_power_on_param62[] = {
	0x00,
	0xe0,
};

static char tianma_OTM9608A_power_on_param63[] = {
	0xcb,
	0x00,0x04,0x04,0x04,0x00,
	0x04,0x00,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param64[] = {
	0x00,
	0xf0,
};

static char tianma_OTM9608A_power_on_param65[] = {
	0xcb,
	0x0f,0x00,0xcc,0x00,0x00,
	0x0f,0x00,0xcc,0xc3,0x00,
};

static char tianma_OTM9608A_power_on_param66[] = {
	0x00,
	0x80,
};

static char tianma_OTM9608A_power_on_param67[] = {
	0xcc,
	0x25,0x26,0x00,0x00,0x00,
	0x0c,0x00,0x0a,0x00,0x10,
};

static char tianma_OTM9608A_power_on_param68[] = {
	0x00,
	0x90,
};

static char tianma_OTM9608A_power_on_param69[] = {
	0xcc,
	0x00,0x0e,0x02,0x04,0x00,
	0x06,0x00,0x00,0x00,0x00,
	0x25,0x26,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param70[] = {
	0x00,
	0xa0,
};

static char tianma_OTM9608A_power_on_param71[] = {
	0xcc,
	0x0b,0x00,0x09,0x00,0x0f,
	0x00,0x0d,0x01,0x03,0x00,
	0x05,0x00,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param72[] = {
	0x00,
	0xb0,
};

static char tianma_OTM9608A_power_on_param73[] = {
	0xcc,
	0x26,0x25,0x00,0x00,0x00,
	0x0d,0x00,0x0f,0x00,0x09,
};

static char tianma_OTM9608A_power_on_param74[] = {
	0x00,
	0xc0,
};

static char tianma_OTM9608A_power_on_param75[] = {
	0xcc,
	0x00,0x0b,0x03,0x01,0x00,
	0x05,0x00,0x00,0x00,0x00,
	0x26,0x25,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param76[] = {
	0x00,
	0xd0,
};

static char tianma_OTM9608A_power_on_param77[] = {
	0xcc,
	0x0e,0x00,0x10,0x00,0x0a,
	0x00,0x0c,0x04,0x02,0x00,
	0x06,0x00,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param78[] = {
	0x00,
	0x80,
};

static char tianma_OTM9608A_power_on_param79[] = {
	0xce,
	0x8a,0x03,0x28,0x89,
	0x03,0x28,0x88,0x03,
	0x28,0x87,0x03,0x28,
};

static char tianma_OTM9608A_power_on_param80[] = {
	0x00,
	0x90,
};

static char tianma_OTM9608A_power_on_param81[] = {
	0xce,
	0x38,0x0f,0x28,0x38,0x0e,
	0x28,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param82[] = {
	0x00,
	0xa0,
};

static char tianma_OTM9608A_power_on_param83[] = {
	0xce,
	0x38,0x06,0x03,0xc1,0x00,
	0x28,0x00,0x38,0x05,0x03,
	0xc2,0x00,0x28,0x00,
};

static char tianma_OTM9608A_power_on_param84[] = {
	0x00,
	0xb0,
};

static char tianma_OTM9608A_power_on_param85[] = {
	0xce,
	0x38,0x04,0x03,0xc3,0x00,
	0x28,0x00,0x38,0x03,0x03,
	0xc4,0x00,0x28,0x00,
};

static char tianma_OTM9608A_power_on_param86[] = {
	0x00,
	0xc0,
};

static char tianma_OTM9608A_power_on_param87[] = {
	0xce,
	0x38,0x02,0x03,0xc5,0x00,
	0x28,0x00,0x38,0x01,0x03,
	0xc6,0x00,0x28,0x00,
};

static char tianma_OTM9608A_power_on_param88[] = {
	0x00,
	0xd0,
};

static char tianma_OTM9608A_power_on_param89[] = {
	0xce,
	0x38,0x00,0x03,0xc7,0x00,
	0x28,0x00,0x30,0x00,0x03,
	0xc8,0x00,0x28,0x00,
};

static char tianma_OTM9608A_power_on_param90[] = {
	0x00,
	0x80,
};

static char tianma_OTM9608A_power_on_param91[] = {
	0xcf,
	0xf0,0x00,0x00,0x10,0x00,
	0x00,0x00,0xf0,0x00,0x00,
	0x10,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param92[] = {
	0x00,
	0x90,
};

static char tianma_OTM9608A_power_on_param93[] = {
	0xcf,
	0xf0,0x00,0x00,0x10,0x00,
	0x00,0x00,0xf0,0x00,0x00,
	0x10,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param94[] = {
	0x00,
	0xa0,
};

static char tianma_OTM9608A_power_on_param95[] = {
	0xcf,
	0xf0,0x00,0x00,0x10,0x00,
	0x00,0x00,0xf0,0x00,0x00,
	0x10,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param96[] = {
	0x00,
	0xb0,
};

static char tianma_OTM9608A_power_on_param97[] = {
	0xcf,
	0xf0,0x00,0x00,0x10,0x00,
	0x00,0x00,0xf0,0x00,0x00,
	0x10,0x00,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param98[] = {
	0x00,
	0xc0,
};

static char tianma_OTM9608A_power_on_param99[] = {
	0xcf,
	0x01,0x01,0x20,0x20,0x00,
	0x00,0x02,0x01,0x00,0x00,
};

static char tianma_OTM9608A_power_on_param100[] = {
	0x35,
	0x00,
};

static char tianma_OTM9608A_power_on_param101[] = {
	0x53,
	0x24,
};

static char tianma_OTM9608A_power_on_param102[] = {
	0x55,
	0x00,
};

// exit sleep mode
static char tianma_OTM9608A_exit_sleep[] = {
	0x11,
};

// set display on
static char tianma_OTM9608A_display_on[] = {
	0x29,
};

/*
**Power OFF Sequence(Normal to power off)
*/
static char tianma_OTM9608A_display_off[] = {
	0x28,
};

static char tianma_OTM9608A_enter_sleep[] = {
	0x10,
};

static struct dsi_cmd_desc tianma_OTM9608A_display_on_cmds[] = {
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param1), tianma_OTM9608A_power_on_param1},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param2), tianma_OTM9608A_power_on_param2},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param3), tianma_OTM9608A_power_on_param3},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param4), tianma_OTM9608A_power_on_param4},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param5), tianma_OTM9608A_power_on_param5},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param6), tianma_OTM9608A_power_on_param6},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param7), tianma_OTM9608A_power_on_param7},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param8), tianma_OTM9608A_power_on_param8},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param9), tianma_OTM9608A_power_on_param9},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param10), tianma_OTM9608A_power_on_param10},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param11), tianma_OTM9608A_power_on_param11},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param12), tianma_OTM9608A_power_on_param12},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param13), tianma_OTM9608A_power_on_param13},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param14), tianma_OTM9608A_power_on_param14},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param15), tianma_OTM9608A_power_on_param15},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param16), tianma_OTM9608A_power_on_param16},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param17), tianma_OTM9608A_power_on_param17},

	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param18), tianma_OTM9608A_power_on_param18},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param19), tianma_OTM9608A_power_on_param19},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param20), tianma_OTM9608A_power_on_param20},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param21), tianma_OTM9608A_power_on_param21},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param22), tianma_OTM9608A_power_on_param22},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param23), tianma_OTM9608A_power_on_param23},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param24), tianma_OTM9608A_power_on_param24},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param25), tianma_OTM9608A_power_on_param25},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param26), tianma_OTM9608A_power_on_param26},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param27), tianma_OTM9608A_power_on_param27},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param28), tianma_OTM9608A_power_on_param28},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param29), tianma_OTM9608A_power_on_param29},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param30), tianma_OTM9608A_power_on_param30},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param31), tianma_OTM9608A_power_on_param31},

	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param32), tianma_OTM9608A_power_on_param32},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param33), tianma_OTM9608A_power_on_param33},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param34), tianma_OTM9608A_power_on_param34},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param35), tianma_OTM9608A_power_on_param35},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param36), tianma_OTM9608A_power_on_param36},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param37), tianma_OTM9608A_power_on_param37},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param38), tianma_OTM9608A_power_on_param38},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param39), tianma_OTM9608A_power_on_param39},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param40), tianma_OTM9608A_power_on_param40},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param41), tianma_OTM9608A_power_on_param41},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param42), tianma_OTM9608A_power_on_param42},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param43), tianma_OTM9608A_power_on_param43},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param44), tianma_OTM9608A_power_on_param44},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param45), tianma_OTM9608A_power_on_param45},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param46), tianma_OTM9608A_power_on_param46},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param47), tianma_OTM9608A_power_on_param47},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param48), tianma_OTM9608A_power_on_param48},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param49), tianma_OTM9608A_power_on_param49},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param50), tianma_OTM9608A_power_on_param50},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param51), tianma_OTM9608A_power_on_param51},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param52), tianma_OTM9608A_power_on_param52},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param53), tianma_OTM9608A_power_on_param53},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param54), tianma_OTM9608A_power_on_param54},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param55), tianma_OTM9608A_power_on_param55},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param56), tianma_OTM9608A_power_on_param56},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param57), tianma_OTM9608A_power_on_param57},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param58), tianma_OTM9608A_power_on_param58},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param59), tianma_OTM9608A_power_on_param59},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param60), tianma_OTM9608A_power_on_param60},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param61), tianma_OTM9608A_power_on_param61},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param62), tianma_OTM9608A_power_on_param62},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param63), tianma_OTM9608A_power_on_param63},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param64), tianma_OTM9608A_power_on_param64},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param65), tianma_OTM9608A_power_on_param65},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param66), tianma_OTM9608A_power_on_param66},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param67), tianma_OTM9608A_power_on_param67},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param68), tianma_OTM9608A_power_on_param68},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param69), tianma_OTM9608A_power_on_param69},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param70), tianma_OTM9608A_power_on_param70},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param71), tianma_OTM9608A_power_on_param71},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param72), tianma_OTM9608A_power_on_param72},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param73), tianma_OTM9608A_power_on_param73},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param74), tianma_OTM9608A_power_on_param74},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param75), tianma_OTM9608A_power_on_param75},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param76), tianma_OTM9608A_power_on_param76},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param77), tianma_OTM9608A_power_on_param77},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param78), tianma_OTM9608A_power_on_param78},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param79), tianma_OTM9608A_power_on_param79},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param80), tianma_OTM9608A_power_on_param80},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param81), tianma_OTM9608A_power_on_param81},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param82), tianma_OTM9608A_power_on_param82},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param83), tianma_OTM9608A_power_on_param83},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param84), tianma_OTM9608A_power_on_param84},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param85), tianma_OTM9608A_power_on_param85},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param86), tianma_OTM9608A_power_on_param86},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param87), tianma_OTM9608A_power_on_param87},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param88), tianma_OTM9608A_power_on_param88},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param89), tianma_OTM9608A_power_on_param89},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param90), tianma_OTM9608A_power_on_param90},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param91), tianma_OTM9608A_power_on_param91},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param92), tianma_OTM9608A_power_on_param92},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param93), tianma_OTM9608A_power_on_param93},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param94), tianma_OTM9608A_power_on_param94},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param95), tianma_OTM9608A_power_on_param95},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param96), tianma_OTM9608A_power_on_param96},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param97), tianma_OTM9608A_power_on_param97},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param98), tianma_OTM9608A_power_on_param98},
	{DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param99), tianma_OTM9608A_power_on_param99},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param100), tianma_OTM9608A_power_on_param100},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param101), tianma_OTM9608A_power_on_param101},
	{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_power_on_param102), tianma_OTM9608A_power_on_param102},

	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_exit_sleep), tianma_OTM9608A_exit_sleep},
	{DTYPE_DCS_WRITE, 0, 20, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_display_on), tianma_OTM9608A_display_on},
};

static struct dsi_cmd_desc tianma_OTM9608A_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_display_off), tianma_OTM9608A_display_off},

	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(tianma_OTM9608A_enter_sleep), tianma_OTM9608A_enter_sleep},
};
/********************************tianma_OTM9608A*****end*************************/


/********************************tianma_RAMLess*****start**************************
** Power ON Sequence(sleep mode to Normal mode)
*/
static char tianma_RAMLess_power_on_param1[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_power_on_param2[] = {
	0xFF,
	0x96,0x05,0x01,
};

static char tianma_RAMLess_power_on_param3[] = {
	0x00,
	0x80,
};

static char tianma_RAMLess_power_on_param4[] = {
	0xFF,0x96,0x05
};

static char tianma_RAMLess_power_on_param5[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_power_on_param6[] = {
	0xA0,
	0x00,
};

static char tianma_RAMLess_power_on_param7[] = {
	0x00,
	0xB4,
};

static char tianma_RAMLess_power_on_param8[] = {
	0xC0,
	0x50,
};

static char tianma_RAMLess_power_on_param9[] = {
	0x00,
	0x80,
};

static char tianma_RAMLess_power_on_param10[] = {
	0xC1,
	0x36,0x66,
};

static char tianma_RAMLess_power_on_param11[] = {
	0x00,
	0x89,
};

static char tianma_RAMLess_power_on_param12[] = {
	0xC0,
	0x01,
};

static char tianma_RAMLess_power_on_param13[] = {
	0x00,
	0x80,
};

static char tianma_RAMLess_power_on_param14[] = {
	0xC4,
	0x9C,
};

static char tianma_RAMLess_power_on_param15[] = {
	0x00,
	0xA0,
};

static char tianma_RAMLess_power_on_param16[] = {
	0xC1,
	0x00,
};

static char tianma_RAMLess_power_on_param17[] = {
	0x00,
	0xC0,
};

static char tianma_RAMLess_power_on_param18[] = {
	0xC5,
	0x00,
};

static char tianma_RAMLess_power_on_param19[] = {
	0x00,
	0xC5,
};

static char tianma_RAMLess_power_on_param20[] = {
	0xB0,
	0x03,
};

static char tianma_RAMLess_power_on_param21[] = {
	0x00,
	0x90,
};

static char tianma_RAMLess_power_on_param22[] = {
	0xc5,
	0x96,0x19,0x01,0x79,0x33,
	0x33,0x34,
};

static char tianma_RAMLess_power_on_param23[] = {
	0x00,
	0xA0,
};

static char tianma_RAMLess_power_on_param24[] = {
	0xC5,
	0x96,0x16,0x00,0x79,0x33,
	0x33,0x34,
};

static char tianma_RAMLess_power_on_param25[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_power_on_param26[] = {
	0xD8,
	0x5F,0x5F,
};

static char tianma_RAMLess_power_on_param27[] = {
	0x00,
	0x00,
};
static char tianma_RAMLess_power_on_param28[] = {
	0xD9,
	0x3b,
};

static char tianma_RAMLess_power_on_param29[] = {
	0x00,
	0xB0,
};

static char tianma_RAMLess_power_on_param30[] = {
	0xC5,
	0x04,0x28,
};

static char tianma_RAMLess_power_on_param31[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_power_on_param32[] = {
	0xE1,
	0x01,0x0D,0x14,0x0E,0x07,
	0x13,0x0B,0x0A,0x02,0x06,
	0x08,0x08,0x0e,0x12,0x0f,
	0x0b,
};

//GOA ECLK Setting and GOA Other Options1 and GOA Signal Toggle Option Setting
static char tianma_RAMLess_power_on_param33[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_power_on_param34[] = {
	0xE2,
	0x01,0x0D,0x14,0x0E,0x07,
	0x13,0x0B,0x0A,0x02,0x06,
	0x08,0x08,0x0e,0x12,0x0f,
	0x0b,
};

static char tianma_RAMLess_power_on_param35[] = {
	0x00,
	0x80,
};
static char tianma_RAMLess_power_on_param36[] = {
	0xCB,
	0x05,0x00,0x00,0x00,0x00,
	0x05,0x00,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param37[] = {
	0x00,
	0x90,
};

static char tianma_RAMLess_power_on_param38[] = {
	0xCB,
	0x55,0x55,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param39[] = {
	0x00,
	0xA0,
};

static char tianma_RAMLess_power_on_param40[] = {
	0xCB,
	0x00,0x00,0x00,0x00,0x00,
	0x55,0x55,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param41[] = {
	0x00,
	0xB0,
};

static char tianma_RAMLess_power_on_param42[] = {
	0xCB,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param43[] = {
	0x00,
	0xC0,
};

static char tianma_RAMLess_power_on_param44[] = {
	0xCB,
	0x55,0x55,0x00,0x00,0x00,
	0x04,0x00,0x04,0x00,0x04,
	0x00,0x04,0x04,0x04,0x00,
};

static char tianma_RAMLess_power_on_param45[] = {
	0x00,
	0xD0,
};

static char tianma_RAMLess_power_on_param46[] = {
	0xCB,
	0x04,0x00,0x00,0x00,0x00,
	0x55,0x55,0x00,0x00,0x00,
	0x04,0x00,0x04,0x00,0x04,
};

static char tianma_RAMLess_power_on_param47[] = {
	0x00,
	0xE0,
};

static char tianma_RAMLess_power_on_param48[] = {
	0xCB,
	0x00,0x04,0x04,0x04,0x00,
	0x04,0x00,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param49[] = {
	0x00,
	0xF0,
};

static char tianma_RAMLess_power_on_param50[] = {
	0xCB,
	0x0F,0x00,0xCC,0x00,0x00,
	0x0F,0x00,0xCC,0xC3,0x00,
};

static char tianma_RAMLess_power_on_param51[] = {
	0x00,
	0x80,
};

static char tianma_RAMLess_power_on_param52[] = {
	0xCC,
	0x25,0x26,0x00,0x00,0x00,
	0x0C,0x00,0x0A,0x00,0x10,
};

static char tianma_RAMLess_power_on_param53[] = {
	0x00,
	0x90,
};

static char tianma_RAMLess_power_on_param54[] = {
	0xCC,
	0x00,0x0E,0x02,0x04,0x00,
	0x06,0x00,0x00,0x00,0x00,
	0x25,0x26,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param55[] = {
	0x00,
	0xA0,
};

static char tianma_RAMLess_power_on_param56[] = {
	0xCC,
	0x0B,0x00,0x09,0x00,0x0F,
	0x00,0x0D,0x01,0x03,0x00,
	0x05,0x00,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param57[] = {
	0x00,
	0xB0,
};

static char tianma_RAMLess_power_on_param58[] = {
	0xCC,
	0x26,0x25,0x00,0x00,0x00,
	0x0D,0x00,0x0F,0x00,0x09,
};

static char tianma_RAMLess_power_on_param59[] = {
	0x00,
	0xC0,
};

static char tianma_RAMLess_power_on_param60[] = {
	0xCC,
	0x00,0x0B,0x03,0x01,0x00,
	0x05,0x00,0x00,0x00,0x00,
	0x26,0x25,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param61[] = {
	0x00,
	0xD0,
};

static char tianma_RAMLess_power_on_param62[] = {
	0xCC,
	0x0E,0x00,0x10,0x00,0x0A,
	0x00,0x0C,0x04,0x02,0x00,
	0x06,0x00,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param63[] = {
	0x00,
	0x80,
};

static char tianma_RAMLess_power_on_param64[] = {
	0xCE,
	0x8B,0x03,0x27,0x8A,0x03,
	0x28,0x89,0x03,0x27,0x88,
	0x03,0x28,
};

static char tianma_RAMLess_power_on_param65[] = {
	0x00,
	0x90,
};

static char tianma_RAMLess_power_on_param66[] = {
	0xCE,
	0x39,0x0F,0x27,0x39,0x0E,
	0x28,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param67[] = {
	0x00,
	0xA0,
};

static char tianma_RAMLess_power_on_param68[] = {
	0xCE,
	0x38,0x07,0x03,0xC0,0x00,
	0x28,0x00,0x38,0x06,0x03,
	0xC1,0x00,0x28,0x00,
};

static char tianma_RAMLess_power_on_param69[] = {
	0x00,
	0xB0,
};

static char tianma_RAMLess_power_on_param70[] = {
	0xCE,
	0x38,0x05,0x03,0xC2,0x00,
	0x28,0x00,0x38,0x04,0x03,
	0xC3,0x00,0x28,0x00,
};

static char tianma_RAMLess_power_on_param71[] = {
	0x00,
	0xC0,
};

static char tianma_RAMLess_power_on_param72[] = {
	0xCE,
	0x38,0x03,0x03,0xC4,0x00,
	0x28,0x00,0x38,0x02,0x03,
	0xC5,0x00,0x28,0x00,
};

static char tianma_RAMLess_power_on_param73[] = {
	0x00,
	0xD0,
};

static char tianma_RAMLess_power_on_param74[] = {
	0xCE,
	0x38,0x01,0x03,0xC6,0x00,
	0x28,0x00,0x38,0x00,0x03,
	0xC7,0x00,0x28,0x00,
};

static char tianma_RAMLess_power_on_param75[] = {
	0x00,
	0x80,
};

static char tianma_RAMLess_power_on_param76[] = {
	0xCF,
	0xF0,0x00,0x00,0x10,0x00,
	0x00,0x00,0xF0,0x00,0x00,
	0x10,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param77[] = {
	0x00,
	0x90,
};

static char tianma_RAMLess_power_on_param78[] = {
	0xCF,
	0xF0,0x00,0x00,0x10,0x00,
	0x00,0x00,0xF0,0x00,0x00,
	0x10,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param79[] = {
	0x00,
	0xA0,
};

static char tianma_RAMLess_power_on_param80[] = {
	0xCF,
	0xF0,0x00,0x00,0x10,0x00,
	0x00,0x00,0xF0,0x00,0x00,
	0x10,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param81[] = {
	0x00,
	0xB0,
};

static char tianma_RAMLess_power_on_param82[] = {
	0xCF,
	0xF0,0x00,0x00,0x10,0x00,
	0x00,0x00,0xF0,0x00,0x00,
	0x10,0x00,0x00,0x00,
};

static char tianma_RAMLess_power_on_param83[] = {
	0x00,
	0xC0,
};

static char tianma_RAMLess_power_on_param84[] = {
	0xCF,
	0x01,0x01,0x20,0x20,0x00,
	0x00,0x02,0x01,0x00,0x00,
};

static char tianma_RAMLess_power_on_param85[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_power_on_param86[] = {
	0xFF,
	0xFF,0xFF,0xFF,
};

static char tianma_RAMLess_exit_sleep1[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_exit_sleep2[] = {
	0x11,
	0x00,
};

static char tianma_RAMLess_display_on1[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_display_on2[] = {
	0x29,
	0x00,
};

/*
**Power OFF Sequence(Normal to power off)
*/
static char tianma_RAMLess_display_off1[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_display_off2[] = {
	0x28,
	0x00,
};

static char tianma_RAMLess_enter_sleep1[] = {
	0x00,
	0x00,
};

static char tianma_RAMLess_enter_sleep2[] = {
	0x10,
	0x00,
};

static struct dsi_cmd_desc tianma_RAMLess_display_on_cmds[] = {
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param1), tianma_RAMLess_power_on_param1},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param2), tianma_RAMLess_power_on_param2},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param3), tianma_RAMLess_power_on_param3},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param4), tianma_RAMLess_power_on_param4},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param5), tianma_RAMLess_power_on_param5},
	{DTYPE_GEN_WRITE2, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param6), tianma_RAMLess_power_on_param6},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param7), tianma_RAMLess_power_on_param7},
	{DTYPE_GEN_WRITE2, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param8), tianma_RAMLess_power_on_param8},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param9), tianma_RAMLess_power_on_param9},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param10), tianma_RAMLess_power_on_param10},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param11), tianma_RAMLess_power_on_param11},
	{DTYPE_GEN_WRITE2, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param12), tianma_RAMLess_power_on_param12},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param13), tianma_RAMLess_power_on_param13},
	{DTYPE_GEN_WRITE2, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param14), tianma_RAMLess_power_on_param14},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param15), tianma_RAMLess_power_on_param15},
	{DTYPE_GEN_WRITE2, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param16), tianma_RAMLess_power_on_param16},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param17), tianma_RAMLess_power_on_param17},
	{DTYPE_GEN_WRITE2, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param18), tianma_RAMLess_power_on_param18},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param19), tianma_RAMLess_power_on_param19},
	{DTYPE_GEN_WRITE2, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param20), tianma_RAMLess_power_on_param20},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param21), tianma_RAMLess_power_on_param21},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param22), tianma_RAMLess_power_on_param22},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param23), tianma_RAMLess_power_on_param23},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param24), tianma_RAMLess_power_on_param24},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param25), tianma_RAMLess_power_on_param25},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param26), tianma_RAMLess_power_on_param26},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param27), tianma_RAMLess_power_on_param27},
	{DTYPE_GEN_WRITE2, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param28), tianma_RAMLess_power_on_param28},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param29), tianma_RAMLess_power_on_param29},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param30), tianma_RAMLess_power_on_param30},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param31), tianma_RAMLess_power_on_param31},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param32), tianma_RAMLess_power_on_param32},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param33), tianma_RAMLess_power_on_param33},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param34), tianma_RAMLess_power_on_param34},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param35), tianma_RAMLess_power_on_param35},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param36), tianma_RAMLess_power_on_param36},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param37), tianma_RAMLess_power_on_param37},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param38), tianma_RAMLess_power_on_param38},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param39), tianma_RAMLess_power_on_param39},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param40), tianma_RAMLess_power_on_param40},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param41), tianma_RAMLess_power_on_param41},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param42), tianma_RAMLess_power_on_param42},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param43), tianma_RAMLess_power_on_param43},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param44), tianma_RAMLess_power_on_param44},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param45), tianma_RAMLess_power_on_param45},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param46), tianma_RAMLess_power_on_param46},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param47), tianma_RAMLess_power_on_param47},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param48), tianma_RAMLess_power_on_param48},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param49), tianma_RAMLess_power_on_param49},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param50), tianma_RAMLess_power_on_param50},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param51), tianma_RAMLess_power_on_param51},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param52), tianma_RAMLess_power_on_param52},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param53), tianma_RAMLess_power_on_param53},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param54), tianma_RAMLess_power_on_param54},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param55), tianma_RAMLess_power_on_param55},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param56), tianma_RAMLess_power_on_param56},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param57), tianma_RAMLess_power_on_param57},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param58), tianma_RAMLess_power_on_param58},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param59), tianma_RAMLess_power_on_param59},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param60), tianma_RAMLess_power_on_param60},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param61), tianma_RAMLess_power_on_param61},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param62), tianma_RAMLess_power_on_param62},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param63), tianma_RAMLess_power_on_param63},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param64), tianma_RAMLess_power_on_param64},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param65), tianma_RAMLess_power_on_param65},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param66), tianma_RAMLess_power_on_param66},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param67), tianma_RAMLess_power_on_param67},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param68), tianma_RAMLess_power_on_param68},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param69), tianma_RAMLess_power_on_param69},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param70), tianma_RAMLess_power_on_param70},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param71), tianma_RAMLess_power_on_param71},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param72), tianma_RAMLess_power_on_param72},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param73), tianma_RAMLess_power_on_param73},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param74), tianma_RAMLess_power_on_param74},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param75), tianma_RAMLess_power_on_param75},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param76), tianma_RAMLess_power_on_param76},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param77), tianma_RAMLess_power_on_param77},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param78), tianma_RAMLess_power_on_param78},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param79), tianma_RAMLess_power_on_param79},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param80), tianma_RAMLess_power_on_param80},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param81), tianma_RAMLess_power_on_param81},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param82), tianma_RAMLess_power_on_param82},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param83), tianma_RAMLess_power_on_param83},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param84), tianma_RAMLess_power_on_param84},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param85), tianma_RAMLess_power_on_param85},
	{DTYPE_GEN_LWRITE, 0, 1, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_power_on_param86), tianma_RAMLess_power_on_param86},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_exit_sleep1), tianma_RAMLess_exit_sleep1},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_exit_sleep2), tianma_RAMLess_exit_sleep2},
	{DTYPE_GEN_WRITE2, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_display_on1), tianma_RAMLess_display_on1},
	{DTYPE_GEN_WRITE2, 0, 120, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_display_on2), tianma_RAMLess_display_on2},
};

static struct dsi_cmd_desc tianma_RAMLess_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_display_off1), tianma_RAMLess_display_off1},
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_display_off2), tianma_RAMLess_display_off2},
	{DTYPE_DCS_WRITE, 0, 0, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_enter_sleep1), tianma_RAMLess_enter_sleep1},
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(tianma_RAMLess_enter_sleep2), tianma_RAMLess_enter_sleep2},
};
/********************************tianma_RAMLess*****end*************************/

/*******************************************************************************
** LCD VCC
*/
#define VCC_LCDIO_NAME		"lcdio-vcc"
#define VCC_LCDANALOG_NAME	"lcdanalog-vcc"

static struct regulator *vcc_lcdio;
static struct regulator *vcc_lcdanalog;

static struct vcc_desc tianma_lcd_vcc_init_cmds[] = {
	/* vcc get */
	{DTYPE_VCC_GET, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_GET, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},

	/* vcc set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 2800000, 2800000, WAIT_TYPE_MS, 0},
};

static struct vcc_desc tianma_lcd_vcc_finit_cmds[] = {
	/* vcc put */
	{DTYPE_VCC_PUT, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_PUT, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},
};

static struct vcc_desc tianma_lcd_vcc_enable_cmds[] = {
	/* vcc enable */
	{DTYPE_VCC_ENABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_ENABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
};

static struct vcc_desc tianma_lcd_vcc_disable_cmds[] = {
	/* vcc disable */
	{DTYPE_VCC_DISABLE, VCC_LCDANALOG_NAME, &vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
	{DTYPE_VCC_DISABLE, VCC_LCDIO_NAME, &vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
};


/*******************************************************************************
** LCD GPIO
*/
#define GPIO_LCD_POWER_2V85_EN0_NAME	"LCD_2V85_EN0"
#define GPIO_LCD_POWER_2V85_EN1_NAME	"LCD_2V85_EN1"
#define GPIO_LCD_POWER_1V8_EN0_NAME	"LCD_1V8_EN0"
#define GPIO_LCD_POWER_1V8_EN1_NAME	"LCD_1V8_EN1"
#define GPIO_LCD_RST_NAME	"LCD_RST"
#define GPIO_LCD_ID1_NAME	"LCD_ID1"

static uint32_t gpio_lcd_power_2v85_en0;
static uint32_t gpio_lcd_power_1v8_en0;
static uint32_t gpio_lcd_power_2v85_en1;
static uint32_t gpio_lcd_power_1v8_en1;
static uint32_t gpio_lcd_rst;
static uint32_t gpio_lcd_id1;

static struct gpio_desc tianma_lcd_gpio_request_cmds[] = {
	/* power 2.85v */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_2V85_EN0_NAME, &gpio_lcd_power_2v85_en0, 0},
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_2V85_EN1_NAME, &gpio_lcd_power_2v85_en1, 0},
	/* power 1.8v */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_1V8_EN0_NAME, &gpio_lcd_power_1v8_en0, 0},
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_1V8_EN1_NAME, &gpio_lcd_power_1v8_en1, 0},
	/* reset */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_RST_NAME, &gpio_lcd_rst, 0},
	/* lcd_id1 */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &gpio_lcd_id1, 0},
};

static struct gpio_desc tianma_lcd_gpio_free_cmds[] = {
	/* lcd_id1 */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &gpio_lcd_id1, 0},
	/* reset */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_RST_NAME, &gpio_lcd_rst, 0},
	/* power 1.8v */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_1V8_EN0_NAME, &gpio_lcd_power_1v8_en0, 0},
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_1V8_EN1_NAME, &gpio_lcd_power_1v8_en1, 0},
	/* power 2.85v */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_2V85_EN0_NAME, &gpio_lcd_power_2v85_en0, 0},
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_2V85_EN1_NAME, &gpio_lcd_power_2v85_en1, 0},
};

static struct gpio_desc tianma_lcd_gpio_normal_cmds[] = {
	/*power 1.8v  */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_1V8_EN0_NAME, &gpio_lcd_power_1v8_en0, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_1V8_EN1_NAME, &gpio_lcd_power_1v8_en1, 1},
	/* power 2.85v */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 25,
		GPIO_LCD_POWER_2V85_EN0_NAME, &gpio_lcd_power_2v85_en0, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 25,
		GPIO_LCD_POWER_2V85_EN1_NAME, &gpio_lcd_power_2v85_en1, 1},
	/* reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 50,
		GPIO_LCD_RST_NAME, &gpio_lcd_rst, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_US, 50,
		GPIO_LCD_RST_NAME, &gpio_lcd_rst, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 25,
		GPIO_LCD_RST_NAME, &gpio_lcd_rst, 1},
	/*lcd_id1 */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 100,
		GPIO_LCD_ID1_NAME, &gpio_lcd_id1, 0},
};

static struct gpio_desc tianma_lcd_gpio_lowpower_cmds[] = {
	/* reset */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 50,
		GPIO_LCD_RST_NAME, &gpio_lcd_rst, 0},
	/* power 2.85v */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 25,
		GPIO_LCD_POWER_2V85_EN0_NAME, &gpio_lcd_power_2v85_en0, 0},
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 25,
		GPIO_LCD_POWER_2V85_EN1_NAME, &gpio_lcd_power_2v85_en1, 0},
	/*power 1.8v  */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_1V8_EN0_NAME, &gpio_lcd_power_1v8_en0, 0},
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_POWER_1V8_EN1_NAME, &gpio_lcd_power_1v8_en1, 0},
};


static struct hisi_fb_panel_data g_panel_data;


/*******************************************************************************
** ACM
*/
#if 0
static uint32_t ACM_LUT_HUE_TABLE[] = {
	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
	0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001e, 0x001f, 0x0020,
	0x0022, 0x0023, 0x0024, 0x0026, 0x0027, 0x0028, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f, 0x0030, 0x0031, 0x0032, 0x0033,
	0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003c, 0x003d, 0x003e, 0x003f, 0x003f, 0x0040, 0x0041,
	0x0042, 0x0042, 0x0043, 0x0044, 0x0045, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
	0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
	0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
	0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
	0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f,
	0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f,
	0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7, 0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
	0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7, 0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
	0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7, 0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
	0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7, 0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
	0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7, 0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
	0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7, 0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff,
	0x0100, 0x0101, 0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010a, 0x010b, 0x010c, 0x010d, 0x010e, 0x010f,
	0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119, 0x011a, 0x011b, 0x011c, 0x011d, 0x011e, 0x011f,
	0x0120, 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126, 0x0127, 0x0128, 0x0129, 0x012a, 0x012b, 0x012c, 0x012d, 0x012e, 0x012f,
	0x0130, 0x0131, 0x0132, 0x0133, 0x0134, 0x0135, 0x0136, 0x0137, 0x0138, 0x0139, 0x013a, 0x013b, 0x013c, 0x013d, 0x013e, 0x013f,
	0x0140, 0x0141, 0x0142, 0x0143, 0x0144, 0x0145, 0x0146, 0x0147, 0x0148, 0x0149, 0x014a, 0x014b, 0x014c, 0x014d, 0x014e, 0x014f,
	0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0156, 0x0157, 0x0158, 0x0159, 0x015a, 0x015b, 0x015c, 0x015d, 0x015e, 0x015f,
	0x0160, 0x0161, 0x0162, 0x0163, 0x0164, 0x0165, 0x0166, 0x0167, 0x0168, 0x0169, 0x016a, 0x016b, 0x016c, 0x016d, 0x016e, 0x016f,
	0x0170, 0x0171, 0x0172, 0x0173, 0x0174, 0x0175, 0x0176, 0x0177, 0x0178, 0x0179, 0x017a, 0x017b, 0x017c, 0x017d, 0x017e, 0x017f,
	0x0180, 0x0181, 0x0182, 0x0183, 0x0184, 0x0185, 0x0186, 0x0187, 0x0188, 0x0189, 0x018a, 0x018b, 0x018c, 0x018d, 0x018e, 0x018f,
	0x0190, 0x0191, 0x0192, 0x0193, 0x0194, 0x0195, 0x0196, 0x0197, 0x0198, 0x0199, 0x019a, 0x019b, 0x019c, 0x019d, 0x019e, 0x019f,
	0x01a0, 0x01a1, 0x01a2, 0x01a3, 0x01a4, 0x01a5, 0x01a6, 0x01a7, 0x01a8, 0x01a9, 0x01aa, 0x01ab, 0x01ac, 0x01ad, 0x01ae, 0x01af,
	0x01b0, 0x01b1, 0x01b2, 0x01b3, 0x01b4, 0x01b5, 0x01b6, 0x01b7, 0x01b8, 0x01b9, 0x01ba, 0x01bb, 0x01bc, 0x01bd, 0x01be, 0x01bf,
	0x01c0, 0x01c1, 0x01c2, 0x01c3, 0x01c4, 0x01c5, 0x01c6, 0x01c7, 0x01c8, 0x01c9, 0x01ca, 0x01cb, 0x01cc, 0x01cd, 0x01ce, 0x01cf,
	0x01d0, 0x01d1, 0x01d2, 0x01d3, 0x01d4, 0x01d5, 0x01d6, 0x01d7, 0x01d8, 0x01d9, 0x01da, 0x01db, 0x01dc, 0x01dd, 0x01de, 0x01df,
	0x01e0, 0x01e1, 0x01e2, 0x01e3, 0x01e4, 0x01e5, 0x01e6, 0x01e7, 0x01e8, 0x01e9, 0x01ea, 0x01eb, 0x01ec, 0x01ed, 0x01ee, 0x01ef,
	0x01f0, 0x01f1, 0x01f2, 0x01f3, 0x01f4, 0x01f5, 0x01f6, 0x01f7, 0x01f8, 0x01f9, 0x01fa, 0x01fb, 0x01fc, 0x01fd, 0x01fe, 0x01ff,
	0x0200, 0x0201, 0x0202, 0x0203, 0x0204, 0x0205, 0x0206, 0x0207, 0x0208, 0x0209, 0x020a, 0x020b, 0x020c, 0x020d, 0x020e, 0x020f,
	0x0210, 0x0211, 0x0212, 0x0213, 0x0214, 0x0215, 0x0216, 0x0217, 0x0218, 0x0219, 0x021a, 0x021b, 0x021c, 0x021d, 0x021e, 0x021f,
	0x0220, 0x0221, 0x0222, 0x0223, 0x0224, 0x0225, 0x0226, 0x0227, 0x0228, 0x0229, 0x022a, 0x022b, 0x022c, 0x022d, 0x022e, 0x022f,
	0x0230, 0x0231, 0x0232, 0x0233, 0x0234, 0x0235, 0x0236, 0x0237, 0x0238, 0x0239, 0x023a, 0x023b, 0x023c, 0x023d, 0x023e, 0x023f,
	0x0240, 0x0241, 0x0242, 0x0243, 0x0244, 0x0245, 0x0246, 0x0247, 0x0248, 0x0249, 0x024a, 0x024b, 0x024c, 0x024d, 0x024e, 0x024f,
	0x0250, 0x0251, 0x0252, 0x0253, 0x0254, 0x0255, 0x0256, 0x0257, 0x0258, 0x0259, 0x025a, 0x025b, 0x025c, 0x025d, 0x025e, 0x025f,
	0x0260, 0x0261, 0x0262, 0x0263, 0x0264, 0x0265, 0x0266, 0x0267, 0x0268, 0x0269, 0x026a, 0x026b, 0x026c, 0x026d, 0x026e, 0x026f,
	0x0270, 0x0271, 0x0272, 0x0273, 0x0274, 0x0275, 0x0276, 0x0277, 0x0278, 0x0279, 0x027a, 0x027b, 0x027c, 0x027d, 0x027e, 0x027f,
	0x0280, 0x0281, 0x0282, 0x0283, 0x0284, 0x0285, 0x0286, 0x0287, 0x0288, 0x0289, 0x028a, 0x028b, 0x028c, 0x028d, 0x028e, 0x028f,
	0x0290, 0x0291, 0x0292, 0x0293, 0x0294, 0x0295, 0x0296, 0x0297, 0x0298, 0x0299, 0x029a, 0x029b, 0x029c, 0x029d, 0x029e, 0x029f,
	0x02a0, 0x02a1, 0x02a2, 0x02a3, 0x02a4, 0x02a5, 0x02a6, 0x02a7, 0x02a8, 0x02a9, 0x02aa, 0x02ab, 0x02ac, 0x02ad, 0x02ae, 0x02af,
	0x02b0, 0x02b1, 0x02b2, 0x02b3, 0x02b4, 0x02b5, 0x02b6, 0x02b7, 0x02b8, 0x02b9, 0x02ba, 0x02bb, 0x02bc, 0x02bd, 0x02be, 0x02bf,
	0x02c0, 0x02c1, 0x02c2, 0x02c3, 0x02c4, 0x02c5, 0x02c6, 0x02c7, 0x02c8, 0x02c9, 0x02ca, 0x02cb, 0x02cc, 0x02cd, 0x02ce, 0x02cf,
	0x02d0, 0x02d1, 0x02d2, 0x02d3, 0x02d4, 0x02d5, 0x02d6, 0x02d7, 0x02d8, 0x02d9, 0x02da, 0x02db, 0x02dc, 0x02dd, 0x02de, 0x02df,
	0x02e0, 0x02e1, 0x02e2, 0x02e3, 0x02e4, 0x02e5, 0x02e6, 0x02e7, 0x02e8, 0x02e9, 0x02ea, 0x02eb, 0x02ec, 0x02ed, 0x02ee, 0x02ef,
	0x02f0, 0x02f1, 0x02f2, 0x02f3, 0x02f4, 0x02f5, 0x02f6, 0x02f7, 0x02f8, 0x02f9, 0x02fa, 0x02fb, 0x02fc, 0x02fd, 0x02fe, 0x02ff,
	0x0300, 0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0306, 0x0307, 0x0308, 0x0309, 0x030a, 0x030b, 0x030c, 0x030d, 0x030e, 0x030f,
	0x0310, 0x0311, 0x0312, 0x0313, 0x0314, 0x0315, 0x0316, 0x0317, 0x0318, 0x0319, 0x031a, 0x031b, 0x031c, 0x031d, 0x031e, 0x031f,
	0x0320, 0x0321, 0x0322, 0x0323, 0x0324, 0x0325, 0x0326, 0x0327, 0x0328, 0x0329, 0x032a, 0x032b, 0x032c, 0x032d, 0x032e, 0x032f,
	0x0330, 0x0331, 0x0332, 0x0333, 0x0334, 0x0335, 0x0336, 0x0337, 0x0338, 0x0339, 0x033a, 0x033b, 0x033c, 0x033d, 0x033e, 0x033f,
	0x0340, 0x0341, 0x0342, 0x0343, 0x0344, 0x0345, 0x0346, 0x0347, 0x0348, 0x0349, 0x034a, 0x034b, 0x034c, 0x034d, 0x034e, 0x034f,
	0x0350, 0x0351, 0x0352, 0x0353, 0x0354, 0x0355, 0x0356, 0x0357, 0x0358, 0x0359, 0x035a, 0x035b, 0x035c, 0x035d, 0x035e, 0x035f,
	0x0360, 0x0361, 0x0362, 0x0363, 0x0364, 0x0365, 0x0366, 0x0367, 0x0368, 0x0369, 0x036a, 0x036b, 0x036c, 0x036d, 0x036e, 0x036f,
	0x0370, 0x0371, 0x0372, 0x0373, 0x0374, 0x0375, 0x0376, 0x0377, 0x0378, 0x0379, 0x037a, 0x037b, 0x037c, 0x037d, 0x037e, 0x037f,
	0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x0386, 0x0387, 0x0388, 0x0389, 0x038a, 0x038b, 0x038c, 0x038d, 0x038e, 0x038f,
	0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 0x0398, 0x0399, 0x039a, 0x039b, 0x039c, 0x039d, 0x039e, 0x039f,
	0x03a0, 0x03a1, 0x03a2, 0x03a3, 0x03a4, 0x03a5, 0x03a6, 0x03a7, 0x03a8, 0x03a9, 0x03aa, 0x03ab, 0x03ac, 0x03ad, 0x03ae, 0x03af,
	0x03b0, 0x03b1, 0x03b2, 0x03b3, 0x03b4, 0x03b5, 0x03b6, 0x03b7, 0x03b8, 0x03b9, 0x03ba, 0x03bb, 0x03bc, 0x03bd, 0x03be, 0x03bf,
	0x03c0, 0x03c1, 0x03c2, 0x03c3, 0x03c4, 0x03c5, 0x03c6, 0x03c7, 0x03c8, 0x03c9, 0x03ca, 0x03cb, 0x03cc, 0x03cd, 0x03ce, 0x03cf,
	0x03d0, 0x03d1, 0x03d2, 0x03d3, 0x03d4, 0x03d5, 0x03d6, 0x03d7, 0x03d8, 0x03d9, 0x03da, 0x03db, 0x03dc, 0x03dd, 0x03de, 0x03df,
	0x03e0, 0x03e1, 0x03e2, 0x03e3, 0x03e4, 0x03e5, 0x03e6, 0x03e7, 0x03e8, 0x03e9, 0x03ea, 0x03eb, 0x03ec, 0x03ed, 0x03ee, 0x03ef,
	0x03f0, 0x03f1, 0x03f2, 0x03f3, 0x03f4, 0x03f5, 0x03f6, 0x03f7, 0x03f8, 0x03f9, 0x03fa, 0x03fb, 0x03fc, 0x03fd, 0x03fe, 0x03ff,
};

static uint32_t ACM_LUT_VALUE_TABLE[] = {
	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f,
	0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f,
	0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
	0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
	0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
	0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
	0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
	0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f,
	0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f,
	0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f,
	0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7, 0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af,
	0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7, 0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf,
	0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7, 0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
	0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7, 0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df,
	0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7, 0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
	0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7, 0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff,
};

static uint32_t ACM_LUT_SATA_TABLE[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

static uint32_t ACM_LUT_SATR_TABLE[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
#endif


/*******************************************************************************
**
*/
static int mipi_tianma_panel_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	// lcd gpio request
	gpio_cmds_tx(tianma_lcd_gpio_request_cmds, \
		ARRAY_SIZE(tianma_lcd_gpio_request_cmds));

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_tianma_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);
	BUG_ON(pinfo == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		// lcd vcc enable
		vcc_cmds_tx(NULL, tianma_lcd_vcc_enable_cmds, \
			ARRAY_SIZE(tianma_lcd_vcc_enable_cmds));

		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {
		// lcd gpio request
		gpio_cmds_tx(tianma_lcd_gpio_request_cmds, \
			ARRAY_SIZE(tianma_lcd_gpio_request_cmds));
		// lcd gpio normal
		gpio_cmds_tx(tianma_lcd_gpio_normal_cmds, \
			ARRAY_SIZE(tianma_lcd_gpio_normal_cmds));

		if (gpio_get_value(gpio_lcd_id1) == 1) {
			HISI_FB_INFO("fb%d, tianma_OTM9608A.\n", hisifd->index);
			rgb2mipi_cmds_tx(pinfo->spi_dev, tianma_OTM9608A_display_on_cmds, \
				ARRAY_SIZE(tianma_OTM9608A_display_on_cmds));
		} else {
			HISI_FB_INFO("fb%d, tianma_RAMLess.\n", hisifd->index);
			rgb2mipi_cmds_tx(pinfo->spi_dev, tianma_RAMLess_display_on_cmds, \
				ARRAY_SIZE(tianma_RAMLess_display_on_cmds));
		}

		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
		;
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_tianma_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);
	BUG_ON(pinfo == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	// backlight off
	hisi_lcd_backlight_off(pdev);

	// lcd display off sequence
	if (gpio_get_value(gpio_lcd_id1) == 1) {
		HISI_FB_INFO("fb%d, tianma_OTM9608A.\n", hisifd->index);
		rgb2mipi_cmds_tx(pinfo->spi_dev, tianma_OTM9608A_display_off_cmds, \
			ARRAY_SIZE(tianma_OTM9608A_display_off_cmds));
	} else {
		HISI_FB_INFO("fb%d, tianma_RAMLess.\n", hisifd->index);
		rgb2mipi_cmds_tx(pinfo->spi_dev, tianma_RAMLess_display_off_cmds, \
			ARRAY_SIZE(tianma_RAMLess_display_off_cmds));
	}

	// lcd gpio lowpower
	gpio_cmds_tx(tianma_lcd_gpio_lowpower_cmds, \
		ARRAY_SIZE(tianma_lcd_gpio_lowpower_cmds));
	// lcd gpio free
	gpio_cmds_tx(tianma_lcd_gpio_free_cmds, \
		ARRAY_SIZE(tianma_lcd_gpio_free_cmds));

	// lcd vcc disable
	vcc_cmds_tx(NULL, tianma_lcd_vcc_disable_cmds, \
		ARRAY_SIZE(tianma_lcd_vcc_disable_cmds));

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_tianma_panel_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	// lcd vcc finit
	vcc_cmds_tx(pdev, tianma_lcd_vcc_finit_cmds, \
		ARRAY_SIZE(tianma_lcd_vcc_finit_cmds));

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_tianma_panel_set_backlight(struct platform_device *pdev, uint32_t bl_level)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (hisifd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		ret = hisi_pwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_BLPWM) {
		ret = hisi_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_SH_BLPWM) {
		ret = hisi_sh_blpwm_set_backlight(hisifd, bl_level);
	} else {
		;
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}


/******************************************************************************/
static ssize_t mipi_tianma_panel_lcd_model_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "mipi_tianma_OTM9608A\n");

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_tianma_panel_lcd_cabc_mode_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_tianma_panel_lcd_cabc_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_tianma_panel_lcd_check_reg(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_tianma_panel_lcd_mipi_detect(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static struct hisi_panel_info g_panel_info = {0};
static struct hisi_fb_panel_data g_panel_data = {
	.panel_info = &g_panel_info,
	.set_fastboot = mipi_tianma_panel_set_fastboot,
	.on = mipi_tianma_panel_on,
	.off = mipi_tianma_panel_off,
	.remove = mipi_tianma_panel_remove,
	.set_backlight = mipi_tianma_panel_set_backlight,

	.lcd_model_show = mipi_tianma_panel_lcd_model_show,
	.lcd_cabc_mode_show = mipi_tianma_panel_lcd_cabc_mode_show,
	.lcd_cabc_mode_store = mipi_tianma_panel_lcd_cabc_mode_store,
	.lcd_check_reg = mipi_tianma_panel_lcd_check_reg,
	.lcd_mipi_detect = mipi_tianma_panel_lcd_mipi_detect,
	.set_display_region = NULL,
	.set_display_resolution = NULL,
};


/*******************************************************************************
**
*/
static int mipi_tianma_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;
	uint32_t bl_type = 0;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_MIPI_TIANMA_OTM9608A);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_MIPI_TIANMA_OTM9608A);
		goto err_return;
	}

	ret = of_property_read_u32(np, LCD_BL_TYPE_NAME, &bl_type);
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_BLPWM;
	}
	HISI_FB_INFO("bl_type=0x%x.", bl_type);

	if (hisi_fb_device_probe_defer(PANEL_RGB2MIPI, bl_type)) {
		goto err_probe_defer;
	}

	HISI_FB_DEBUG("+.\n");

	HISI_FB_INFO("%s\n", DTS_COMP_MIPI_TIANMA_OTM9608A);

	//GPIO_6_2
	gpio_lcd_power_2v85_en1 = of_get_named_gpio(np, "gpios", 0);
	//GPIO_6_3
	gpio_lcd_power_2v85_en0 = of_get_named_gpio(np, "gpios", 1);
	//GPIO_6_4
	gpio_lcd_power_1v8_en0 = of_get_named_gpio(np, "gpios", 2);
	//GPIO_6_5
	gpio_lcd_power_1v8_en1 = of_get_named_gpio(np, "gpios", 3);
	//GPIO_8_4
	gpio_lcd_rst = of_get_named_gpio(np, "gpios", 4);
	//GPIO_4_1
	gpio_lcd_id1 = of_get_named_gpio(np, "gpios", 6);

	ret = of_property_read_u32(np, "fpga_flag", &g_lcd_fpga_flag);
	if (ret) {
		HISI_FB_WARNING("need to get g_lcd_fpga_flag resource in fpga, not needed in asic!\n");
	}

	pdev->id = 1;
	/* init lcd panel info */
	pinfo = g_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 540;
	pinfo->yres = 960;
	pinfo->width = 62;
	pinfo->height = 110;
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

	pinfo->spi_dev = g_spi_dev;

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;

	//sbl
	pinfo->sbl_support = 0;

	//ldi
	pinfo->ldi.h_back_porch = 50;
	pinfo->ldi.h_front_porch = 697; //177
	pinfo->ldi.h_pulse_width = 11;
	pinfo->ldi.v_back_porch = 32;
	pinfo->ldi.v_front_porch = 32;
	pinfo->ldi.v_pulse_width = 4;
	pinfo->ldi.hsync_plr = 1;
	pinfo->ldi.vsync_plr = 1;
	pinfo->ldi.pixelclk_plr = 0;
	pinfo->ldi.data_en_plr = 0;

	//mipi
	pinfo->mipi.lane_nums = DSI_2_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.max_tx_esc_clk = 10 * 1000000;
	pinfo->mipi.burst_mode = 0;

	pinfo->mipi.dsi_bit_clk = 241;

	pinfo->pxl_clk_rate = 40 * 1000000UL;

	pinfo->type = PANEL_RGB2MIPI;
	pinfo->mipi.burst_mode = DSI_BURST_SYNC_PULSES_1;
	pinfo->ifbc_type = IFBC_TYPE_NONE;
	pinfo->vsync_ctrl_type = 0;
	pinfo->dirty_region_updt_support = 0;

	if (g_lcd_fpga_flag == 0) {
		// lcd vcc init
		ret = vcc_cmds_tx(pdev, tianma_lcd_vcc_init_cmds, \
			ARRAY_SIZE(tianma_lcd_vcc_init_cmds));
		if (ret != 0) {
			HISI_FB_ERR("LCD vcc init failed!\n");
			goto err_return;
		}

		// lcd vcc enable
		if (is_fastboot_display_enable()) {
			vcc_cmds_tx(pdev, tianma_lcd_vcc_enable_cmds,
				ARRAY_SIZE(tianma_lcd_vcc_enable_cmds));
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
}

static const struct of_device_id hisi_panel_match_table[] = {
	{
		.compatible = DTS_COMP_MIPI_TIANMA_OTM9608A,
		.data = NULL,
	},
	{},
};

static struct platform_driver this_driver = {
	.probe = mipi_tianma_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_tianma_OTM9608A",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_tianma_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_tianma_panel_init);
