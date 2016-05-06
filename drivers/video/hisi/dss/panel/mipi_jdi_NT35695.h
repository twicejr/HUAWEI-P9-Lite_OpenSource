#include "hisi_fb.h"

#ifndef MIPI_JDI_NT35695
#define MIPI_JDI_NT35695

enum {  
	LCD_BIST_CHECK_FAIL = -1,
	LCD_BIST_CHECK_TIMEOUT = -2,
	LCD_BIST_CHECK_PASS = 0,
}; 

#define LAST_4_STEPS_ONLY_FOR_BIST_CHECK

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
	0x24,
};

static char defect_step1_1[] = {
	0xE3,
	0x00,
};

static char defect_step1_2[] = {
	0xFB,
	0x01,
};

static char defect_step1_3[] = {
	0xFF,
	0x25,
};

static char defect_step1_4[] = {
	0x2F,
	0x03,
};

static char defect_step1_5[] = {
	0x30,
	0x0F,
};

static char defect_step1_6[] = {
	0xFB,
	0x01,
};

static char defect_step1_7[] = {
	0xFF,
	0x10,
};

static char defect_step1_8[] = {
	0x11,
	0x00,
};//delay 200

static char defect_step1_9[] = {
	0xFF,
	0xE0,
};

static char defect_step1_10[] = {
	0xB8,
	0XAD,
};

static char defect_step1_11[] = {
	0x2F,
	0xFF,
};

static char defect_step1_12[] = {
	0x30,
	0xFF,
};

static char defect_step1_13[] = {
	0x31,
	0x1F,
};

static char defect_step1_14[] = {
	0x34,
	0x10,
};

static char defect_step1_15[] = {
	0xB5,
	0xEE,
};

static char defect_step1_16[] = {
	0xFF,
	0xF0,
};

static char defect_step1_17[] = {
	0xBD,
	0X02,
};

static char defect_step2_0[] = {
	0xC6,
	0x80,
};

static char defect_step2_1[] = {
	0xB9,
	0xA2,
};//delay 800

static char defect_step2_2[] = {
	0xB9,
	0xA1,
};//delay 800
//REGR 0xD8,0xFF
//REGR 0xD9,0x3F
//REGR 0xBC,0x68

static char defect_step3_0[] = {
	0xB9,
	0x80,
};//delay 40

static char defect_step3_1[] = {
	0xC6,
	0x00,
};

static char defect_step3_2[] = {
	0xB3,
	0xFF,
};

static char defect_step3_3[] = {
	0xB4,
	0xFF,
};

static char defect_step3_4[] = {
	0xB5,
	0xFF,
};

static char defect_step3_5[] = {
	0xB6,
	0xFF,
};

static char defect_step3_6[] = {
	0xB7,
	0xFF,
};

static char defect_step3_7[] = {
	0xB8,
	0xFF,
};

static char defect_step3_8[] = {
	0xB9,
	0xA4,
};//delay 800
//REGR 0xD8,0xFF
//REGR 0xD9,0x3F
//REGR 0xBC,0x78

static char defect_step3_9[] = {
	0xB9,
	0x80,
};

static char defect_step3_10[] = {
	0xB9,
	0xA8,
};//delay 800

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
	0xA4,
};//delay 800

static char defect_step4_8[] = {
	0xB9,
	0x80,
};

static char defect_step4_9[] = {
	0xB9,
	0xA8,
};//delay 800
//step 5 test1
#ifdef LAST_4_STEPS_ONLY_FOR_BIST_CHECK
static char defect_step5_0[] = {
	0xB9,
	0x80,
};
#endif
static char defect_step5_1[] = {
	0xFF,
	0x24,
};

static char defect_step5_2[] = {
	0xE3,
	0x00,
};

static char defect_step5_no_reload[] = {
	0xFB,
	0x01,
};

static char defect_step5_3[] = {
	0xFF,
	0x25,
};

static char defect_step5_4[] = {
	0x2F,
	0x03,
};

static char defect_step5_5[] = {
	0x30,
	0x0F,
};

static char defect_step5_6[] = {
	0xFB,
	0x01,
};

static char defect_step5_7[] = {
	0xFF,
	0x10,
};

static char defect_step5_8[] = {
	0x11,
	0x00,
};

static char defect_step5_9[] = {
	0xFF,
	0xE0,
};

static char defect_step5_10[] = {
	0xB6,
	0x42,
};

static char defect_step5_11[] = {
	0xB8,
	0xAD,
};

static char defect_step5_12[] = {
	0x2F,
	0x00,
};

static char defect_step5_13[] = {
	0x30,
	0x00,
};

static char defect_step5_14[] = {
	0x31,
	0x10,
};

static char defect_step5_15[] = {
	0x34,
	0x70,
};

static char defect_step5_16[] = {
	0xB5,
	0xE6,
};

static char defect_step5_OSC_adj[] = {
	0xB3,
	0x08,
};

static char defect_step5_17[] = {
	0xFF,
	0xF0,
};

static char defect_step5_18[] = {
	0xBD,
	0x02,
};

static char defect_step5_19[] = {
	0xB3,
	0x55,
};

static char defect_step5_20[] = {
	0xB4,
	0x55,
};

static char defect_step5_21[] = {
	0xB5,
	0x55,
};

static char defect_step5_22[] = {
	0xB6,
	0xAA,
};

static char defect_step5_23[] = {
	0xB7,
	0xAA,
};

static char defect_step5_24[] = {
	0xB8,
	0xAA,
};

static char defect_step5_25[] = {
	0xB9,
	0xA4,
};

// step 5 test2
static char defect_step5_26[] = {
	0xB9,
	0x80,
};

static char defect_step5_27[] = {
	0xB3,
	0xAA,
};

static char defect_step5_28[] = {
	0xB4,
	0xAA,
};

static char defect_step5_29[] = {
	0xB5,
	0xAA,
};

static char defect_step5_30[] = {
	0xB6,
	0x55,
};

static char defect_step5_31[] = {
	0xB7,
	0x55,
};

static char defect_step5_32[] = {
	0xB8,
	0x55,
};
static char defect_step5_33[] = {
	0xB9,
	0xA4,
};

//step 6 test1
static char defect_step6_0[] = {
	0xB9,
	0x80,
};
static char defect_step6_1[] = {
	0xFF,
	0x24,
};

static char defect_step6_2[] = {
	0xE3,
	0x00,
};

static char defect_step6_3[] = {
	0xFB,
	0x01,
};

static char defect_step6_4[] = {
	0xFF,
	0x25,
};

static char defect_step6_5[] = {
	0x2F,
	0x03,
};

static char defect_step6_6[] = {
	0x30,
	0x0F,
};

static char defect_step6_7[] = {
	0xFB,
	0x01,
};

static char defect_step6_8[] = {
	0xFF,
	0x10,
};

static char defect_step6_9[] = {
	0x11,
	0x00,
};

static char defect_step6_10[] = {
	0xFF,
	0xE0,
};

static char defect_step6_11[] = {
	0xB8,
	0x2D,
};

static char defect_step6_12[] = {
	0x2F,
	0xFF,
};

static char defect_step6_13[] = {
	0x30,
	0xFF,
};

static char defect_step6_14[] = {
	0x31,
	0x1F,
};

static char defect_step6_15[] = {
	0x34,
	0x10,
};

static char defect_step6_16[] = {
	0xB5,
	0xEE,
};

static char defect_step6_17[] = {
	0xFF,
	0xF0,
};

static char defect_step6_18[] = {
	0xBD,
	0x02,
};

static char defect_step6_19[] = {
	0xC6,
	0xC0,
};

static char defect_step6_20[] = {
	0xB9,
	0xA2,
};

static char defect_step6_21[] = {
	0xB9,
	0xA1,
};

//step7 test1

static char defect_step7_0[] = {
	0xB9,
	0x80,
};

static char defect_step7_1[] = {
	0xC6,
	0x00,
};

static char defect_step7_2[] = {
	0xFF,
	0x24,
};

static char defect_step7_3[] = {
	0xE3,
	0x00,
};

static char defect_step7_4[] = {
	0xFB,
	0x01,
};

static char defect_step7_5[] = {
	0xFF,
	0x25,
};

static char defect_step7_6[] = {
	0x2F,
	0x03,
};

static char defect_step7_7[] = {
	0x30,
	0x0F,
};

static char defect_step7_8[] = {
	0xFB,
	0x01,
};

static char defect_step7_9[] = {
	0xFF,
	0x10,
};

static char defect_step7_10[] = {
	0x11,
	0x00,
};

static char defect_step7_11[] = {
	0xFF,
	0xE0,
};

static char defect_step7_12[] = {
	0xB8,
	0xAD,
};

static char defect_step7_13[] = {
	0x2F,
	0xFF,
};

static char defect_step7_14[] = {
	0x30,
	0xFF,
};

static char defect_step7_15[] = {
	0x31,
	0x1F,
};

static char defect_step7_16[] = {
	0x34,
	0x10,
};

static char defect_step7_17[] = {
	0xB5,
	0x7E,
};

static char defect_step7_18[] = {
	0xFF,
	0xF0,
};

static char defect_step7_19[] = {
	0xBD,
	0x30,
};

static char defect_step7_20[] = {
	0xB3,
	0xFF,
};

static char defect_step7_21[] = {
	0xB4,
	0xFF,
};

static char defect_step7_22[] = {
	0xB5,
	0xFF,
};

static char defect_step7_23[] = {
	0xB6,
	0xFF,
};

static char defect_step7_24[] = {
	0xB7,
	0xFF,
};

static char defect_step7_25[] = {
	0xB8,
	0xFF,
};

static char defect_step7_26[] = {
	0xB9,
	0xA4,
};

//step8 test1
static char defect_step8_0[] = {
	0xB9,
	0x80,
};

static char defect_step8_1[] = {
	0xFF,
	0x10,
};

static char defect_step8_2[] = {
	0x11,
	0x00,
};

static char defect_step8_3[] = {
	0xFF,
	0xE0,
};

static char defect_step8_4[] = {
	0xB8,
	0x2D,
};

static char defect_step8_5[] = {
	0x2F,
	0x00,
};

static char defect_step8_6[] = {
	0x30,
	0x00,
};

static char defect_step8_7[] = {
	0x31,
	0x10,
};

static char defect_step8_8[] = {
	0x34,
	0x70,
};

static char defect_step8_9[] = {
	0xB5,
	0x46,
};

static char defect_step8_10[] = {
	0xFF,
	0xF0,
};

static char defect_step8_11[] = {
	0xBD,
	0x33,
};

static char defect_step8_12[] = {
	0xB3,
	0x00,
};

static char defect_step8_13[] = {
	0xB4,
	0x00,
};

static char defect_step8_14[] = {
	0xB5,
	0x00,
};

static char defect_step8_15[] = {
	0xB6,
	0x00,
};

static char defect_step8_16[] = {
	0xB7,
	0x00,
};

static char defect_step8_17[] = {
	0xB8,
	0x00,
};

static char defect_step8_18[] = {
	0xB9,
	0xA4,
};

static char defect_end_0[] = {
	0xB9,
	0x80,
};

static char defect_end_1[] = {
	0xFF,
	0x10,
};

static char defect_end_2[] = {
	0xFF,
	0x24,
};

static char defect_end_3[] = {
	0xE3,
	0x02,
};

static char defect_end_4[] = {
	0xFB,
	0x01,
};

static char defect_end_5[] = {
	0xFF,
	0x25,
};

static char defect_end_6[] = {
	0x2F,
	0x00,
};

static char defect_end_7[] = {
	0x30,
	0x00,
};

static char defect_end_8[] = {
	0xFB,
	0x01,
};

static char defect_end_9[] = {
	0xFF,
	0x10,
};

static char defect_end_10[] = {
	0x10,
	0x00,
};

static char defect_end_11[] = {
	0xFF,
	0xE0,
};

static char defect_end_12[] = {
	0xB8,
	0XAD,
};

static char defect_end_13[] = {
	0x2F,
	0x00,
};

static char defect_end_14[] = {
	0x30,
	0x00,
};

static char defect_end_15[] = {
	0x31,
	0x16,
};

static char defect_end_16[] = {
	0x34,
	0x70,
};

static char defect_end_17[] = {
	0xB5,
	0xE6,
};

static char defect_end_18[] = {
	0xFF,
	0x10,
};

static char defect_end_19[] = {
	0x11,
	0x00,
};

static char defect_end_20[] = {
	0x29,
	0x00,
};

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
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step1_8), defect_step1_8},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_MS,
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
		sizeof(defect_step2_0), defect_step2_0},
	{DTYPE_DCS_WRITE1, 0, 1600, WAIT_TYPE_MS,
		sizeof(defect_step2_1), defect_step2_1},
	{DTYPE_DCS_WRITE1, 0, 1600, WAIT_TYPE_MS,
		sizeof(defect_step2_2), defect_step2_2},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds2[] = {
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step3_0), defect_step3_0},
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
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step3_8), defect_step3_8},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds3[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step3_9), defect_step3_9},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step3_10), defect_step3_10},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds4_1[] = {
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
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step4_7), defect_step4_7},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds4_2[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step4_8), defect_step4_8},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step4_9), defect_step4_9},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds5_1[] = {
#ifdef LAST_4_STEPS_ONLY_FOR_BIST_CHECK
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_0), defect_step5_0},
#endif
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
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step5_8), defect_step5_8},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_MS,
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
		sizeof(defect_step5_OSC_adj), defect_step5_OSC_adj},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_17), defect_step5_17},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_18), defect_step5_18},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_19), defect_step5_19},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_20), defect_step5_20},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_21), defect_step5_21},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_22), defect_step5_22},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_23), defect_step5_23},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_24), defect_step5_24},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step5_25), defect_step5_25},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds5_2[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_26), defect_step5_26},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_27), defect_step5_27},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_28), defect_step5_28},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_29), defect_step5_29},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_30), defect_step5_30},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_31), defect_step5_31},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step5_32), defect_step5_32},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step5_33), defect_step5_33},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds6[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_0), defect_step6_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_check_rst0), defect_check_rst0},
	{DTYPE_DCS_WRITE1, 0, 50, WAIT_TYPE_MS,
		sizeof(defect_check_rst1), defect_check_rst1},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_MS,
		sizeof(defect_check_rst2), defect_check_rst2},
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
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_7), defect_step6_7},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_8), defect_step6_8},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step6_9), defect_step6_9},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_MS,
		sizeof(defect_step6_10), defect_step6_10},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_11), defect_step6_11},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_12), defect_step6_12},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_13), defect_step6_13},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_14), defect_step6_14},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_15), defect_step6_15},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_16), defect_step6_16},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_17), defect_step6_17},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_18), defect_step6_18},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step6_19), defect_step6_19},
	{DTYPE_DCS_WRITE1, 0, 1600, WAIT_TYPE_MS,
		sizeof(defect_step6_20), defect_step6_20},
	{DTYPE_DCS_WRITE1, 0, 1600, WAIT_TYPE_MS,
		sizeof(defect_step6_21), defect_step6_21},
};

static struct dsi_cmd_desc jdi_display_bist_check_cmds7[] = {
	{DTYPE_DCS_WRITE1, 0, 150, WAIT_TYPE_MS,
		sizeof(defect_step7_0), defect_step7_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_1), defect_step7_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_check_rst0), defect_check_rst0},
	{DTYPE_DCS_WRITE1, 0, 50, WAIT_TYPE_MS,
		sizeof(defect_check_rst1), defect_check_rst1},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_MS,
		sizeof(defect_check_rst2), defect_check_rst2},
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
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_7), defect_step7_7},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_8), defect_step7_8},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_9), defect_step7_9},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step7_10), defect_step7_10},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_MS,
		sizeof(defect_step7_11), defect_step7_11},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_12), defect_step7_12},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_13), defect_step7_13},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_14), defect_step7_14},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_15), defect_step7_15},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_16), defect_step7_16},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_17), defect_step7_17},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_18), defect_step7_18},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_19), defect_step7_19},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_20), defect_step7_20},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_21), defect_step7_21},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_22), defect_step7_22},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_23), defect_step7_23},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_24), defect_step7_24},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_step7_25), defect_step7_25},
	{DTYPE_DCS_WRITE1, 0, 3200, WAIT_TYPE_MS,
		sizeof(defect_step7_26), defect_step7_26},
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
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_step8_2), defect_step8_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_MS,
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
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
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
	{DTYPE_DCS_WRITE1, 0, 4000, WAIT_TYPE_MS,
		sizeof(defect_step8_18), defect_step8_18},
};

static struct dsi_cmd_desc jdi_display_bist_check_end[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_0), defect_end_0},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_1), defect_end_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_2), defect_end_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_3), defect_end_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_4), defect_end_4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_5), defect_end_5},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_6), defect_end_6},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_7), defect_end_7},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_8), defect_end_8},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_9), defect_end_9},
	{DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_MS,
		sizeof(defect_end_10), defect_end_10},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_11), defect_end_11},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_12), defect_end_12},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_13), defect_end_13},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_14), defect_end_14},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_15), defect_end_15},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_16), defect_end_16},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_17), defect_end_17},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(defect_end_18), defect_end_18},
	{DTYPE_DCS_WRITE1, 0, 120, WAIT_TYPE_MS,
		sizeof(defect_end_19), defect_end_19},
	{DTYPE_DCS_WRITE1, 0, 50, WAIT_TYPE_MS,
		sizeof(defect_end_20), defect_end_20},
};

static struct dsi_cmd_desc* jdi_display_bist_check_cmds[] = {  
	jdi_display_bist_check_cmds1,  
	jdi_display_bist_check_cmds2,  
	jdi_display_bist_check_cmds3,  
	jdi_display_bist_check_cmds4_1,  
	jdi_display_bist_check_cmds4_2,  
	jdi_display_bist_check_cmds5_1,  
	jdi_display_bist_check_cmds5_2,  
	jdi_display_bist_check_cmds6,  
	jdi_display_bist_check_cmds7,  
	jdi_display_bist_check_cmds8,  
};  

static int bist_check_cmds_size[] = {  
	ARRAY_SIZE(jdi_display_bist_check_cmds1),  
	ARRAY_SIZE(jdi_display_bist_check_cmds2),  
	ARRAY_SIZE(jdi_display_bist_check_cmds3),  
	ARRAY_SIZE(jdi_display_bist_check_cmds4_1),  
	ARRAY_SIZE(jdi_display_bist_check_cmds4_2),  
	ARRAY_SIZE(jdi_display_bist_check_cmds5_1),  
	ARRAY_SIZE(jdi_display_bist_check_cmds5_2),  
	ARRAY_SIZE(jdi_display_bist_check_cmds6),  
	ARRAY_SIZE(jdi_display_bist_check_cmds7),  
	ARRAY_SIZE(jdi_display_bist_check_cmds8),  
};  
#endif
