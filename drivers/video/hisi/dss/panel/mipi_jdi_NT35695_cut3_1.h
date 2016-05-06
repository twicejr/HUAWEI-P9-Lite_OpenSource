#include "hisi_fb.h"

#ifndef MIPI_JDI_NT35695
#define MIPI_JDI_NT35695

enum {
	LCD_BIST_CHECK_FAIL = -1,
	LCD_BIST_CHECK_TIMEOUT = -2,
	LCD_BIST_CHECK_PASS = 0,
};

/******************************************
* LCD defect check code
*/
static char defect_check_rst0[] = {
	0xFF,
	0x10,
};

static char defect_check_rst1[] = {
	0x28,
	0x00,
};//delay 50

static char defect_check_rst2[] = {
	0x10,
	0x00,
};//delay 100

static char defect_step1_0[] = {
	0xFF,
	0xF0,
};

static char defect_step1_1[] = {
	0xB9,
	0xA0,
};

static char defect_step1_2[] = {
	0xFB,
	0x01,
};

static char defect_step1_3[] = {
	0xFF,
	0x24,
};

static char defect_step1_4[] = {
	0xE3,
	0x00,
};

static char defect_step1_5[] = {
	0x6E,
	0x10,
};

static char defect_step1_6[] = {
	0xC2,
	0x00,
};

static char defect_step1_7[] = {
	0xFB,
	0x01,
};

static char defect_step1_8[] = {
	0xFF,
	0x10,
};

static char defect_step1_9[] = {
	0x11,
	0x00,
};//delay 200

static char defect_step1_10[] = {
	0xB8,
	0XAD,
};

static char defect_step1_11[] = {
	0xB5,
	0x86,
};

static char defect_step1_12[] = {
	0xB6,
	0x77,
};

static char defect_step1_13[] = {
	0xFF,
	0xF0,
};

static char defect_step1_14[] = {
	0xBD,
	0x00,
};

static char defect_step1_15[] = {
	0xB3,
	0x55,
};

static char defect_step1_16[] = {
	0xB4,
	0xAA,
};

static char defect_step1_17[] = {
	0xB5,
	0x55,
};

static char defect_step1_18[] = {
	0xB6,
	0xAA,
};

static char defect_step1_19[] = {
	0xB7,
	0x55,
};

static char defect_step1_20[] = {
	0xB8,
	0xAA,
};

static char defect_step1_21[] = {
	0xB9,
	0xA8,
};

//delay 800
//REGR 0xD8,0x3F
//REGR 0xD9,0x00
//REGR 0xBC,0x70

static char defect_step2_0[] = {
	0xB9,
	0x80,
};

static char defect_step2_1[] = {
	0xB3,
	0x00,
};

static char defect_step2_2[] = {
	0xB4,
	0x00,
};

static char defect_step2_3[] = {
	0xB5,
	0x00,
};

static char defect_step2_4[] = {
	0xB6,
	0x00,
};

static char defect_step2_5[] = {
	0xB7,
	0x00,
};

static char defect_step2_6[] = {
	0xB8,
	0x00,
};

static char defect_step2_7[] = {
	0xB9,
	0xA4,
};

//delay 800
//REGR 0xD8,0x3F
//REGR 0xD9,0x00
//REGR 0xBC,0x70

static char defect_step3_0[] = {
	0xB9,
	0x80,
};//delay 40

//reset

static char defect_step3_1[] = {
	0xFF,
	0xF0,
};

static char defect_step3_2[] = {
	0xB9,
	0xA0,
};

static char defect_step3_3[] = {
	0xFB,
	0x01,
};

static char defect_step3_4[] = {
	0xFF,
	0x24,
};

static char defect_step3_5[] = {
	0xE3,
	0x00,
};

static char defect_step3_6[] = {
	0x6E,
	0x10,
};

static char defect_step3_7[] = {
	0xC2,
	0x00,
};

static char defect_step3_8[] = {
	0xFB,
	0x01,
};

static char defect_step3_9[] = {
	0xFF,
	0x10,
};

static char defect_step3_10[] = {
	0x11,
	0x00,
}; //delay 50

static char defect_step3_11[] = {
	0xB8,
	0xAD,
};

static char defect_step3_12[] = {
	0xB5,
	0x86,
};

static char defect_step3_13[] = {
	0xB6,
	0x77,
};

static char defect_step3_14[] = {
	0xFF,
	0xF0,
};

static char defect_step3_15[] = {
	0xBD,
	0x00,
};

static char defect_step3_16[] = {
	0xB3,
	0x55,
};

static char defect_step3_17[] = {
	0xB4,
	0xAA,
};

static char defect_step3_18[] = {
	0xB5,
	0x55,
};

static char defect_step3_19[] = {
	0xB6,
	0xAA,
};

static char defect_step3_20[] = {
	0xB7,
	0x55,
};

static char defect_step3_21[] = {
	0xB8,
	0xAA,
};

static char defect_step3_22[] = {
	0xB9,
	0xA4,
};

//delay 800
//REGR 0xD8,0x3F
//REGR 0xD9,0x00
//REGR 0xBC,0x70

static char defect_step4_0[] = {
	0xB9,
	0x80,
};

static char defect_step4_1[] = {
	0xB3,
	0x00,
};

static char defect_step4_2[] = {
	0xB4,
	0x00,
};

static char defect_step4_3[] = {
	0xB5,
	0x00,
};

static char defect_step4_4[] = {
	0xB6,
	0x00,
};

static char defect_step4_5[] = {
	0xB7,
	0x00,
};

static char defect_step4_6[] = {
	0xB8,
	0x00,
};

static char defect_step4_7[] = {
	0xB9,
	0xA8
};//delay 800

static char defect_step4_8[] = {
	0xB9,
	0xA8,
};

//delay 800
//REGR 0xD8,0x3F
//REGR 0xD9,0x00
//REGR 0xBC,0x70

//step 5 test1
static char defect_step5_0[] = {
	0xB9,
	0x80,
};

//reset

static char defect_step5_1[] = {
	0xFF,
	0xF0,
};

static char defect_step5_2[] = {
	0xB9,
	0xA0,
};

static char defect_step5_no_reload[] = {
	0xFB,
	0x01,
};

static char defect_step5_3[] = {
	0xFF,
	0x24,
};

static char defect_step5_4[] = {
	0xE3,
	0x00,
};

static char defect_step5_5[] = {
	0x6E,
	0x10,
};

static char defect_step5_6[] = {
	0xC2,
	0x00,
};

static char defect_step5_7[] = {
	0xFB,
	0x01,
};

static char defect_step5_8[] = {
	0xFF,
	0x10,
};

static char defect_step5_9[] = {
	0x11,
	0x00,
}; //delay 50

static char defect_step5_10[] = {
	0xB8,
	0XAD,
};

static char defect_step5_11[] = {
	0xB5,
	0x86,
};

static char defect_step5_12[] = {
	0xB6,
	0x77,
};

static char defect_step5_13[] = {
	0xFF,
	0xF0,
};

static char defect_step5_14[] = {
	0xBD,
	0x00,
};

static char defect_step5_15[] = {
	0xB3,
	0x55,
};

static char defect_step5_16[] = {
	0xB4,
	0xAA,
};

static char defect_step5_17[] = {
	0xB5,
	0x55,
};

static char defect_step5_18[] = {
	0xB6,
	0xAA,
};

static char defect_step5_19[] = {
	0xB7,
	0x55,
};

static char defect_step5_20[] = {
	0xB8,
	0xAA,
};

static char defect_step5_21[] = {
	0xB9,
	0xA2,
};

//delay 10

static char defect_step5_22[] = {
	0xB9,
	0xA1,
};

//delay 800
//REGR 0xD8,0x3F
//REGR 0xD9,0x00
//REGR 0xBC,0x68

//step 6 test1
static char defect_step6_0[] = {
	0xB9,
	0x80,
};

static char defect_step6_1[] = {
	0xB3,
	0xFF,
};

static char defect_step6_2[] = {
	0xB4,
	0x00,
};

static char defect_step6_3[] = {
	0xB5,
	0xFF,
};

static char defect_step6_4[] = {
	0xB6,
	0x00,
};

static char defect_step6_5[] = {
	0xB7,
	0xFF,
};

static char defect_step6_6[] = {
	0xB8,
	0x00,
};

static char defect_step6_7[] = {
	0xB9,
	0xA8,
};

//delay 800
//REGR 0xD8,0x3F
//REGR 0xD9,0x00
//REGR 0xBC,0x78

//step7 test1

static char defect_step7_0[] = {
	0xB9,
	0x80,
};

static char defect_step7_1[] = {
	0xB3,
	0xAA,
};

static char defect_step7_2[] = {
	0xB4,
	0xAA,
};

static char defect_step7_3[] = {
	0xB5,
	0xAA,
};

static char defect_step7_4[] = {
	0xB6,
	0x55,
};

static char defect_step7_5[] = {
	0xB7,
	0x55,
};

static char defect_step7_6[] = {
	0xB8,
	0x55,
};

static char defect_step7_7[] = {
	0xB9,
	0xA8,
};

//delay 800
//REGR 0xD8,0x3F
//REGR 0xD9,0x00
//REGR 0xBC,0x78

//step8 test1
static char defect_step8_0[] = {
	0xB9,
	0x80,
};

//reset

static char defect_step8_1[] = {
	0xFF,
	0xF0,
};

static char defect_step8_2[] = {
	0xB9,
	0xA0,
};

static char defect_step8_3[] = {
	0xFB,
	0x01,
};

static char defect_step8_4[] = {
	0xFF,
	0x24,
};

static char defect_step8_5[] = {
	0xE3,
	0x00,
};

static char defect_step8_6[] = {
	0x6E,
	0x10,
};

static char defect_step8_7[] = {
	0xC2,
	0x00,
};

static char defect_step8_8[] = {
	0xFB,
	0x01,
};

static char defect_step8_9[] = {
	0xFF,
	0x10,
};

static char defect_step8_10[] = {
	0x11,
	0x00,
};

//delay 50

static char defect_step8_11[] = {
	0xB8,
	0xAD,
};

static char defect_step8_12[] = {
	0xB5,
	0x86,
};

static char defect_step8_13[] = {
	0xB6,
	0x77,
};

static char defect_step8_14[] = {
	0xFF,
	0xF0,
};

static char defect_step8_15[] = {
	0xBD,
	0x00,
};

static char defect_step8_16[] = {
	0xB3,
	0xAA,
};

static char defect_step8_17[] = {
	0xB4,
	0x55,
};

static char defect_step8_18[] = {
	0xB5,
	0xAA,
};

static char defect_step8_19[] = {
	0xB6,
	0x55,
};

static char defect_step8_20[] = {
	0xB7,
	0xAA,
};

static char defect_step8_21[] = {
	0xB8,
	0x55,
};

static char defect_step8_22[] = {
	0xC7,
	0x80,
};

static char defect_step8_23[] = {
	0xB9,
	0xA0,
};

//delay 800
//REGR 0xBC,0x60

static char defect_end_0[] = {
	0xB9,
	0x80,
};

#if 0
static char defect_end_FF_10[] = {
	0xFF,
	0x10,
};

static char defect_end_sleep_out[] = {
	0x11,
	0x00,
};

static char defect_end_disp_on[] = {
	0x29,
	0x00,
};
#endif


static struct dsi_cmd_desc jdi_display_bist_check_cmds1[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_check_rst0), defect_check_rst0},
	{DTYPE_DCS_WRITE1, 0, 50, WAIT_TYPE_MS,
		sizeof(defect_check_rst1), defect_check_rst1},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_MS,
		sizeof(defect_check_rst2), defect_check_rst2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_0), defect_step1_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_1), defect_step1_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_2), defect_step1_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_3), defect_step1_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_4), defect_step1_4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_5), defect_step1_5},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_6), defect_step1_6},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_7), defect_step1_7},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_MS,
		sizeof(defect_step1_8), defect_step1_8},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step1_9), defect_step1_9},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_10), defect_step1_10},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_11), defect_step1_11},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_12), defect_step1_12},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_13), defect_step1_13},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_14), defect_step1_14},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_15), defect_step1_15},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_16), defect_step1_16},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_17), defect_step1_17},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_18), defect_step1_18},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_19), defect_step1_19},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step1_20), defect_step1_20},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step1_21), defect_step1_21},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds2[] = {
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step2_0), defect_step2_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step2_1), defect_step2_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step2_2), defect_step2_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step2_3), defect_step2_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step2_4), defect_step2_4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step2_5), defect_step2_5},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step2_6), defect_step2_6},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step2_7), defect_step2_7},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds3[] = {
	{DTYPE_DCS_WRITE1, 0, 40, WAIT_TYPE_MS,
		sizeof(defect_step3_0), defect_step3_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_check_rst0), defect_check_rst0},
	{DTYPE_DCS_WRITE1, 0, 50, WAIT_TYPE_MS,
		sizeof(defect_check_rst1), defect_check_rst1},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_MS,
		sizeof(defect_check_rst2), defect_check_rst2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_1), defect_step3_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_2), defect_step3_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_3), defect_step3_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_4), defect_step3_4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_5), defect_step3_5},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_6), defect_step3_6},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_7), defect_step3_7},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_8), defect_step3_8},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_9), defect_step3_9},
	{DTYPE_DCS_WRITE1, 0, 50, WAIT_TYPE_MS,
		sizeof(defect_step3_10), defect_step3_10},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_11), defect_step3_11},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_12), defect_step3_12},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_13), defect_step3_13},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_14), defect_step3_14},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_15), defect_step3_15},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_16), defect_step3_16},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_17), defect_step3_17},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_18), defect_step3_18},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_19), defect_step3_19},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_20), defect_step3_20},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_21), defect_step3_21},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step3_22), defect_step3_22},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds4[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step4_0), defect_step4_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step4_1), defect_step4_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step4_2), defect_step4_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step4_3), defect_step4_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step4_4), defect_step4_4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step4_5), defect_step4_5},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step4_6), defect_step4_6},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step4_7), defect_step4_7},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step4_8), defect_step4_8},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds5[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_0), defect_step5_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_check_rst0), defect_check_rst0},
	{DTYPE_DCS_WRITE1, 0, 50, WAIT_TYPE_MS,
		sizeof(defect_check_rst1), defect_check_rst1},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_MS,
		sizeof(defect_check_rst2), defect_check_rst2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_1), defect_step5_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_2), defect_step5_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_no_reload), defect_step5_no_reload},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_3), defect_step5_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_4), defect_step5_4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_5), defect_step5_5},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_6), defect_step5_6},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_7), defect_step5_7},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
		sizeof(defect_step5_8), defect_step5_8},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step5_9), defect_step5_9},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_10), defect_step5_10},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_11), defect_step5_11},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_12), defect_step5_12},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_13), defect_step5_13},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_14), defect_step5_14},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_15), defect_step5_15},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_16), defect_step5_16},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_17), defect_step5_17},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_18), defect_step5_18},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_19), defect_step5_19},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_20), defect_step5_20},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_MS,
		sizeof(defect_step5_21), defect_step5_21},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step5_22), defect_step5_22},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds6[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_0), defect_step6_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_1), defect_step6_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_2), defect_step6_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_3), defect_step6_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_4), defect_step6_4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_5), defect_step6_5},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_6), defect_step6_6},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step6_7), defect_step6_7},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds7[] = {
	{DTYPE_DCS_WRITE1, 0, 150, WAIT_TYPE_US,
		sizeof(defect_step7_0), defect_step7_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_1), defect_step7_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_2), defect_step7_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_3), defect_step7_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_4), defect_step7_4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_5), defect_step7_5},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_6), defect_step7_6},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step7_7), defect_step7_7},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds8[] = {
	{DTYPE_DCS_WRITE1, 0, 150, WAIT_TYPE_MS,
		sizeof(defect_step8_0), defect_step8_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_check_rst0), defect_check_rst0},
	{DTYPE_DCS_WRITE1, 0, 50, WAIT_TYPE_MS,
		sizeof(defect_check_rst1), defect_check_rst1},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_MS,
		sizeof(defect_check_rst2), defect_check_rst2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_1), defect_step8_1},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
		sizeof(defect_step8_2), defect_step8_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_3), defect_step8_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_4), defect_step8_4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_5), defect_step8_5},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_6), defect_step8_6},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_7), defect_step8_7},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_8), defect_step8_8},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_9), defect_step8_9},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step8_10), defect_step8_10},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_11), defect_step8_11},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_12), defect_step8_12},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_13), defect_step8_13},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_14), defect_step8_14},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_15), defect_step8_15},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_16), defect_step8_16},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_17), defect_step8_17},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_18), defect_step8_18},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_19), defect_step8_19},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_20), defect_step8_20},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_21), defect_step8_21},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step8_22), defect_step8_22},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step8_23), defect_step8_23},

};

static struct dsi_cmd_desc jdi_display_bist_check_end[] = {
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_end_0), defect_end_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_check_rst0), defect_check_rst0},
	{DTYPE_DCS_WRITE1, 0, 50, WAIT_TYPE_MS,
		sizeof(defect_check_rst1), defect_check_rst1},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_MS,
		sizeof(defect_check_rst2), defect_check_rst2},
#if 0
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_FF_10), defect_end_FF_10},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_sleep_out), defect_end_sleep_out},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_disp_on), defect_end_disp_on},
#endif
};

static struct dsi_cmd_desc* jdi_display_bist_check_cmds[] = {
	jdi_display_bist_check_cmds1,
	jdi_display_bist_check_cmds2,
	jdi_display_bist_check_cmds3,
	jdi_display_bist_check_cmds4,
	jdi_display_bist_check_cmds5,
	jdi_display_bist_check_cmds6,
	jdi_display_bist_check_cmds7,
	jdi_display_bist_check_cmds8,
};

static int bist_check_cmds_size[] = {
	ARRAY_SIZE(jdi_display_bist_check_cmds1),
	ARRAY_SIZE(jdi_display_bist_check_cmds2),
	ARRAY_SIZE(jdi_display_bist_check_cmds3),
	ARRAY_SIZE(jdi_display_bist_check_cmds4),
	ARRAY_SIZE(jdi_display_bist_check_cmds5),
	ARRAY_SIZE(jdi_display_bist_check_cmds6),
	ARRAY_SIZE(jdi_display_bist_check_cmds7),
	ARRAY_SIZE(jdi_display_bist_check_cmds8),
};
#endif
