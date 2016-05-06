/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *	 * Redistributions of source code must retain the above copyright
 *	   notice, this list of conditions and the following disclaimer.
 *	 * Redistributions in binary form must reproduce the above
 *	   copyright notice, this list of conditions and the following
 *	   disclaimer in the documentation and/or other materials provided
 *	   with the distribution.
 *	 * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *	   contributors may be used to endorse or promote products derived
 *	   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "hisi_fb.h"


#define DTS_COMP_MIPI_CMI_NT35521	"hisilicon,mipi_cmi_NT35521"

#define CMI_CABC_ENABLED	(1)


/*--------cmi power on initial code -----------*/
static char cmi_power_on_param1[] =
{
    0xff,
    0xAA, 0x55, 0xA5, 0x80,
};

static char cmi_power_on_param2[] =
{
    0x6F,
    0x11, 0x00,
};

static char cmi_power_on_param3[] =
{
    0xF7,
    0x20, 0x00,
};

static char cmi_power_on_param4[] =
{
    0x6F,
    0x06,
};

static char cmi_power_on_param5[] =
{
    0xF7,
    0xA0,
};

static char cmi_power_on_param6[] =
{
    0x6F,
    0x19,
};

static char cmi_power_on_param7[] =
{
    0xF7,
    0x12,
};

static char cmi_power_on_paramF4[] =
{
    0xF4,
    0x03,
};

static char cmi_power_on_param8[] =
{
    0xF0,
    0x55, 0xAA, 0x52, 0x08, 0x00,
};

static char cmi_power_on_param9[] =
{
    0xC8,
    /*resolve esd result in lcd blank screen */
    0x80,//0x00,
};

static char cmi_power_on_param10[] =
{
    0xB1,
    0x68, 0x21,
};

static char cmi_power_on_param11[] =
{
    0xB6,
    0x08,
};

static char cmi_power_on_param12[] =
{
    0x6F,
    0x02,
};

static char cmi_power_on_param13[] =
{
    0xB8,
    0x08,
};

static char cmi_power_on_param14[] =
{
    0xBB,
    0x74, 0x44,
};

static char cmi_power_on_param15[] =
{
    0xBC,
    0x00, 0x00,
};

static char cmi_power_on_param16[] =
{
    0xBD,
    0x02, 0xB0, 0x1E, 0x1E, 0x00,
};

static char cmi_power_on_paramC5[] =
{
    0xC5,
    0x01, 0x07,
};

static char cmi_power_on_param17[] =
{
    0xF0,
    0x55, 0xAA, 0x52, 0x08, 0x01,
};

static char cmi_power_on_param18[] =
{
    0xB0,
    0x05, 0x05,
};

static char cmi_power_on_param19[] =
{
    0xB1,
    0x05, 0x05,
};

static char cmi_power_on_param20[] =
{
    0xBC,
    0xA0, 0x01,
};

static char cmi_power_on_param21[] =
{
    0xBD,
    0xA0, 0x01,
};

static char cmi_power_on_param22[] =
{
    0xCA,
    0x00,
};

static char cmi_power_on_param23[] =
{
    0xC0,
    0x04,
};
/* VCOM
static char cmi_power_on_param23[] = {
	0xBE,
    0x51,
};
*/

static char cmi_power_on_param24[] =
{
    0xB3,
    0x37, 0x37,
};

static char cmi_power_on_param25[] =
{
    0xB4,
    0x0F, 0x0F,
};

static char cmi_power_on_paramB6[] =
{
    0xB6,
    0x05, 0x05,
};

static char cmi_power_on_param26[] =
{
    0xB9,
    /*resolve esd result in lcd blank screen */
    0x36, 0x36,//0x46, 0x46,
};

static char cmi_power_on_param27[] =
{
    0xBA,
    0x25, 0x25,  //0x24,0x24
};

static char cmi_power_on_param28[] =
{
    0xF0,
    0x55, 0xAA, 0x52, 0x08, 0x02,
};

static char cmi_power_on_param29[] =
{
	0xEE,
	0x01,
};
static char cmi_power_on_param30[] =
{
    0xB0,
    0x00,0x00,0x00,0x42,0x00,0x88,0x00,0xA6,0x00,0xBF,0x00,0xE6,0x01,0x05,0x01,0x32,
};
static char cmi_power_on_param31[] =
{
    0xB1,
    0x01,0x58,0x01,0x94,0x01,0xC1,0x02,0x08,0x02,0x40,0x02,0x42,0x02,0x78,0x02,0xB4,
};
static char cmi_power_on_param32[] =
{
    0xB2,
    0x02,0xD9,0x03,0x0C,0x03,0x30,0x03,0x5F,0x03,0x7F,0x03,0xA5,0x03,0xC0,0x03,0xE0,
};
static char cmi_power_on_param33[] =
{
    0xB3,
    0x03,0xF6,0x03,0xFF,
};

static char cmi_power_on_param46[] =
{
    0xF0,
    0x55, 0xAA, 0x52, 0x08, 0x06,
};

static char cmi_power_on_param47[] =
{
    0xB0,
    0x29, 0x2A,
};

static char cmi_power_on_param48[] =
{
    0xB1,
    0x10, 0x12,
};

static char cmi_power_on_param49[] =
{
    0xB2,
    0x14, 0x16,
};

static char cmi_power_on_param50[] =
{
    0xB3,
    0x18, 0x1A,
};

static char cmi_power_on_param51[] =
{
    0xB4,
    0x08, 0x0A,
};

static char cmi_power_on_param52[] =
{
    0xB5,
    0x2E, 0x2E,
};

static char cmi_power_on_param53[] =
{
    0xB6,
    0x2E, 0x2E,
};

static char cmi_power_on_param54[] =
{
    0xB7,
    0x2E, 0x2E,
};

static char cmi_power_on_param55[] =
{
    0xB8,
    0x2E, 0x00,
};

static char cmi_power_on_param56[] =
{
    0xB9,
    0x2E, 0x2E,
};

static char cmi_power_on_param57[] =
{
    0xBA,
    0x2E, 0x2E,
};

static char cmi_power_on_param58[] =
{
    0xBB,
    0x01, 0x2E,
};

static char cmi_power_on_param59[] =
{
    0xBC,
    0x2E, 0x2E,
};

static char cmi_power_on_param60[] =
{
    0xBD,
    0x2E, 0x2E,
};

static char cmi_power_on_param61[] =
{
    0xBE,
    0x2E, 0x2E,
};

static char cmi_power_on_param62[] =
{
    0xBF,
    0x0B, 0x09,
};

static char cmi_power_on_param63[] =
{
    0xC0,
    0x1B, 0x19,
};

static char cmi_power_on_param64[] =
{
    0xC1,
    0x17, 0x15,
};

static char cmi_power_on_param65[] =
{
    0xC2,
    0x13, 0x11,
};

static char cmi_power_on_param66[] =
{
    0xC3,
    0x2A, 0x29,
};

static char cmi_power_on_param67[] =
{
    0xE5,
    0x2E, 0x2E,
};

static char cmi_power_on_param68[] =
{
    0xC4,
    0x29, 0x2A,
};

static char cmi_power_on_param69[] =
{
    0xC5,
    0x1B, 0x19,
};

static char cmi_power_on_param70[] =
{
    0xC6,
    0x17, 0x15,
};

static char cmi_power_on_param71[] =
{
    0xC7,
    0x13, 0x11,
};

static char cmi_power_on_param72[] =
{
    0xC8,
    0x01, 0x0B,
};

static char cmi_power_on_param73[] =
{
    0xC9,
    0x2E, 0x2E,
};

static char cmi_power_on_param74[] =
{
    0xCA,
    0x2E, 0x2E,
};
static char cmi_power_on_param75[] =
{
    0xCB,
    0x2E, 0x2E,
};


static char cmi_power_on_param76[] =
{
    0xCC,
    0x2E, 0x09,
};
static char cmi_power_on_param77[] =
{
    0xCD,
    0x2E, 0x2E,
};
static char cmi_power_on_param78[] =
{
    0xCE,
    0x2E, 0x2E,
};

static char cmi_power_on_param79[] =
{
    0xCF,
    0x08, 0x2E,
};

static char cmi_power_on_param80[] =
{
    0xD0,
    0x2E, 0x2E,
};

static char cmi_power_on_param81[] =
{
    0xD1,
    0x2E, 0x2E,
};

static char cmi_power_on_param82[] =
{
    0xD2,
    0x2E, 0x2E,
};

static char cmi_power_on_param83[] =
{
    0xD3,
    0x0A, 0x00,
};

static char cmi_power_on_param84[] =
{
    0xD4,
    0x10, 0x12,
};

static char cmi_power_on_param85[] =
{
    0xD5,
    0x14, 0x16,
};

static char cmi_power_on_param86[] =
{
    0xD6,
    0x18, 0x1A,
};

static char cmi_power_on_param87[] =
{
    0xD7,
    0x2A, 0x29,
};

static char cmi_power_on_param88[] =
{
    0xE6,
    0x2E, 0x2E,
};

static char cmi_power_on_param89[] =
{
    0xD8,
    0x00, 0x00, 0x00, 0x00, 0x00,
};

static char cmi_power_on_param90[] =
{
    0xD9,
    0x00, 0x00, 0x00, 0x00, 0x00,
};

static char cmi_power_on_param91[] =
{
    0xE7,
    0x00,
};

static char cmi_power_on_param92[] =
{
    0xF0,
    0x55, 0xAA, 0x52, 0x08, 0x03,
};

static char cmi_power_on_param93[] =
{
    0xB0,
    0x00, 0x00,
};

static char cmi_power_on_param94[] =
{
    0xB1,
    0x00, 0x00,
};

static char cmi_power_on_param95[] =
{
    0xB2,
    0x05, 0x00, 0x00, 0x00, 0x00,
};

static char cmi_power_on_param96[] =
{
    0xB6,
    0x05, 0x00, 0x00, 0x00, 0x00,
};

static char cmi_power_on_param97[] =
{
    0xB7,
    0x05, 0x00, 0x00, 0x00, 0x00,
};

static char cmi_power_on_param98[] =
{
    0xBA,
    0x57, 0x00, 0x00, 0x00, 0x00,
};

static char cmi_power_on_param99[] =
{
    0xBB,
    0x57, 0x00, 0x00, 0x00, 0x00,
};

static char cmi_power_on_param100[] =
{
    0xC0,
    0x00, 0x00, 0x00, 0x00,
};

static char cmi_power_on_param101[] =
{
    0xC1,
    0x00, 0x00, 0x00, 0x00,
};

static char cmi_power_on_param102[] =
{
    0xC4,
    0x60,
};

static char cmi_power_on_param103[] =
{
    0xC5,
    0x40,
};

static char cmi_power_on_param104[] =
{
    0xF0,
    0x55, 0xAA, 0x52, 0x08, 0x05,
};

static char cmi_power_on_param105[] =
{
    0xBD,
    0x03, 0x01, 0x03, 0x03, 0x03,
};

static char cmi_power_on_param106[] =
{
    0xB0,
    0x17, 0x06,
};

static char cmi_power_on_param107[] =
{
    0xB1,
    0x17, 0x06,
};

static char cmi_power_on_param108[] =
{
    0xB2,
    0x17, 0x06,
};

static char cmi_power_on_param109[] =
{
    0xB3,
    0x17, 0x06,
};

static char cmi_power_on_param110[] =
{
    0xB4,
    0x17, 0x06,
};

static char cmi_power_on_param111[] =
{
    0xB5,
    0x17, 0x06,
};

static char cmi_power_on_param112[] =
{
    0xB8,
    0x00,
};

static char cmi_power_on_param113[] =
{
    0xB9,
    0x00,
};

static char cmi_power_on_param114[] =
{
    0xBA,
    0x00,
};

static char cmi_power_on_param115[] =
{
    0xBB,
    0x02,
};

static char cmi_power_on_param116[] =
{
    0xBC,
    0x00,
};

static char cmi_power_on_param117[] =
{
    0xC0,
    0x07,
};

static char cmi_power_on_param118[] =
{
    0xC4,
    0x80,
};

static char cmi_power_on_param119[] =
{
    0xC5,
    0xA4,
};

static char cmi_power_on_param120[] =
{
    0xC8,
    0x05, 0x30,
};

static char cmi_power_on_param121[] =
{
    0xC9,
    0x01, 0x31,
};

static char cmi_power_on_param122[] =
{
    0xCC,
    0x00, 0x00, 0x3C,
};

static char cmi_power_on_param123[] =
{
    0xCD,
    0x00, 0x00, 0x3C,
};

static char cmi_power_on_param124[] =
{
    0xD1,
    0x00, 0x05, 0x09, 0x07, 0x10,
};

static char cmi_power_on_param125[] =
{
    0xD2,
    0x00, 0x05, 0x0E, 0x07, 0x10,
};

static char cmi_power_on_param126[] =
{
    0xE5,
    0x06,
};

static char cmi_power_on_param127[] =
{
    0xE6,
    0x06,
};

static char cmi_power_on_param128[] =
{
    0xE7,
    0x06,
};

static char cmi_power_on_param129[] =
{
    0xE8,
    0x06,
};

static char cmi_power_on_param130[] =
{
    0xE9,
    0x06,
};

static char cmi_power_on_param131[] =
{
    0xEA,
    0x06,
};

static char cmi_power_on_param132[] =
{
    0xED,
    0x30,
};

static char cmi_power_on_param133[] =
{
    0x6F,
    0x11,
};

static char cmi_power_on_param134[] =
{
    0xF3,
    0x01,
};

static char cmi_power_on_param135[] =
{
    0xF0,
    0x55, 0xAA, 0x52, 0x08, 0x00,
};

static char cmi_power_on_param136[] =
{
    0xD9,
    0x01, 0x01, //0x02, 0x04,
};

static char cmi_power_on_paramD1[] = {
    0xD1,
    0x00,0x02,0x06,0x0A,0x0E,0x12,0x15,0x18,0x18,0x18,0x16, 0x14,0x12,0x0A,0x04,0x00,
};
// Smart Color parameters
static char cmi_power_on_param137[] = {
    0xD7,
    0x24,0x23,0x22,0x21,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,
};

static char cmi_power_on_param138[] = {
    0xD8,
    0x00,0x00,0x00,0x00,0x00,0x00, 0x00, 0x00,0x00, 0x00, 0x23,0x22,0x00,
};
//Disable edge enhancement and close CE dimming function
static char cmi_power_on_param139[] =
{
	0xCC,
	0x40,0x36,0xBA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0xFF,0x00,
};
//set cabc PWM level in UI mode
static char cmi_power_on_param140[] = {
    0xE6,
    0xFF, 0xFF, 0xFA, 0xFA,
};
//write cabc minimum brightness
static char cmi_power_on_param141[] = {
    0x5E,
    0x28,
};
/*----------------Power ON Sequence(sleep mode to Normal mode)---------------------*/

/*static char soft_reset[] = {
	0x01,
};*/

static char bl_level_0[] =
{
    0x51,
    0x00,
};

static char bl_level[] =
{
    0x51,
    0xFF, //0xd0, //0xd0
};

static char bl_enable[] =
{
    0x53,
    0x24,
};

//CABC
#if  CMI_CABC_ENABLED
//Init cabc to UI mode when panel on
static char cabc_mode[] =
{
    0x55,
    0x81,
};
#endif

//TE
/*
static char te_enable[] = {
	0x35,
	0x00,
};
*/

static char exit_sleep[] =
{
    0x11,
};

static char display_on[] =
{
    0x29,
};

/*******************************************************************************
** Power OFF Sequence(Normal to power off)
*/
static char display_off[] =
{
    0x28,
};

static char enter_sleep[] =
{
    0x10,
};

static struct dsi_cmd_desc cmi_display_on_cmds[] =
{
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param1), cmi_power_on_param1
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param2), cmi_power_on_param2
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param3), cmi_power_on_param3
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param4), cmi_power_on_param4
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param5), cmi_power_on_param5
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param6), cmi_power_on_param6
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param7), cmi_power_on_param7
    },
	{
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_paramF4), cmi_power_on_paramF4
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param8), cmi_power_on_param8
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param9), cmi_power_on_param9
    },

    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param10), cmi_power_on_param10
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param11), cmi_power_on_param11
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param12), cmi_power_on_param12
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param13), cmi_power_on_param13
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param14), cmi_power_on_param14
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param15), cmi_power_on_param15
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param16), cmi_power_on_param16
    },

    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_paramC5), cmi_power_on_paramC5
    },

    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param17), cmi_power_on_param17
    },

    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param18), cmi_power_on_param18
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param19), cmi_power_on_param19
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param20), cmi_power_on_param20
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param21), cmi_power_on_param21
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param22), cmi_power_on_param22
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param23), cmi_power_on_param23
    },

    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param24), cmi_power_on_param24
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param25), cmi_power_on_param25
    },
	{
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_paramB6), cmi_power_on_paramB6
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param26), cmi_power_on_param26
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param27), cmi_power_on_param27
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param28), cmi_power_on_param28
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param29), cmi_power_on_param29
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param30), cmi_power_on_param30
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param31), cmi_power_on_param31
    },

    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param32), cmi_power_on_param32
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param33), cmi_power_on_param33
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param46), cmi_power_on_param46
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param47), cmi_power_on_param47
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param48), cmi_power_on_param48
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param49), cmi_power_on_param49
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param50), cmi_power_on_param50
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param51), cmi_power_on_param51
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param52), cmi_power_on_param52
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param53), cmi_power_on_param53
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param54), cmi_power_on_param54
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param55), cmi_power_on_param55
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param56), cmi_power_on_param56
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param57), cmi_power_on_param57
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param58), cmi_power_on_param58
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param59), cmi_power_on_param59
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param60), cmi_power_on_param60
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param61), cmi_power_on_param61
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param62), cmi_power_on_param62
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param63), cmi_power_on_param63
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param64), cmi_power_on_param64
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param65), cmi_power_on_param65
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param66), cmi_power_on_param66
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param67), cmi_power_on_param67
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param68), cmi_power_on_param68
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param69), cmi_power_on_param69
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param70), cmi_power_on_param70
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param71), cmi_power_on_param71
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param72), cmi_power_on_param72
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param73), cmi_power_on_param73
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param74), cmi_power_on_param74
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param75), cmi_power_on_param75
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param76), cmi_power_on_param76
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param77), cmi_power_on_param77
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param78), cmi_power_on_param78
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param79), cmi_power_on_param79
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param80), cmi_power_on_param80
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param81), cmi_power_on_param81
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param82), cmi_power_on_param82
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param83), cmi_power_on_param83
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param84), cmi_power_on_param84
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param85), cmi_power_on_param85
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param86), cmi_power_on_param86
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param87), cmi_power_on_param87
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param88), cmi_power_on_param88
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param89), cmi_power_on_param89
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param90), cmi_power_on_param90
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param91), cmi_power_on_param91
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param92), cmi_power_on_param92
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param93), cmi_power_on_param93
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param94), cmi_power_on_param94
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param95), cmi_power_on_param95
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param96), cmi_power_on_param96
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param97), cmi_power_on_param97
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param98), cmi_power_on_param98
    },
    {
        DTYPE_DCS_LWRITE, 0, 0, WAIT_TYPE_US,
        sizeof(cmi_power_on_param99), cmi_power_on_param99
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param100), cmi_power_on_param100
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param101), cmi_power_on_param101
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param102), cmi_power_on_param102
    },

    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param103), cmi_power_on_param103
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param104), cmi_power_on_param104
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param105), cmi_power_on_param105
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param106), cmi_power_on_param106
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param107), cmi_power_on_param107
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param108), cmi_power_on_param108
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param109), cmi_power_on_param109
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param110), cmi_power_on_param110
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param111), cmi_power_on_param111
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param112), cmi_power_on_param112
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param113), cmi_power_on_param113
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param114), cmi_power_on_param114
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param115), cmi_power_on_param115
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param116), cmi_power_on_param116
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param117), cmi_power_on_param117
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param118), cmi_power_on_param118
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param119), cmi_power_on_param119
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param120), cmi_power_on_param120
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param121), cmi_power_on_param121
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param122), cmi_power_on_param122
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param123), cmi_power_on_param123
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param124), cmi_power_on_param124
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param125), cmi_power_on_param125
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param126), cmi_power_on_param126
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param127), cmi_power_on_param127
    },

    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param128), cmi_power_on_param128
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param129), cmi_power_on_param129
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param130), cmi_power_on_param130
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param131), cmi_power_on_param131
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param132), cmi_power_on_param132
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param133), cmi_power_on_param133
    },
    {
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param134), cmi_power_on_param134
    },

    /*set pwm freq to 39.06KHz*/
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param135), cmi_power_on_param135
    },
    {
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param136), cmi_power_on_param136
    },

	{
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_paramD1), cmi_power_on_paramD1
    },
	{
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param137), cmi_power_on_param137
    },
	{
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param138), cmi_power_on_param138
    },
	//Disable edge enhancement
	{
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param139), cmi_power_on_param139
    },
	{
        DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param140), cmi_power_on_param140
    },
	{
        DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
        sizeof(cmi_power_on_param141), cmi_power_on_param141
    },
    {
        DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
        sizeof(bl_level), bl_level
    },
    {
        DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
        sizeof(bl_enable), bl_enable
    },
    #if  CMI_CABC_ENABLED
    {
    	DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
	 	sizeof(cabc_mode), cabc_mode
    },
    #endif
    //	{DTYPE_DCS_WRITE, 0, 10, WAIT_TYPE_MS,
    //		sizeof(te_enable), te_enable},
    {DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS, sizeof(exit_sleep), exit_sleep},
    {DTYPE_DCS_WRITE, 0, 20, WAIT_TYPE_MS, sizeof(display_on), display_on},
};

static struct dsi_cmd_desc cmi_display_off_cmds[] =
{
    {
        DTYPE_DCS_WRITE1, 0, 200, WAIT_TYPE_US,
        sizeof(bl_level_0), bl_level_0
    },
    {
        DTYPE_DCS_WRITE, 0, 20, WAIT_TYPE_MS,
        sizeof(display_off), display_off
    },
    {
        DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
        sizeof(enter_sleep), enter_sleep
    }
};


/*******************************************************************************
** LCD GPIO
*/
#define GPIO_LCD_BL_ENABLE_NAME	"gpio_lcd_bl_enable"
#define GPIO_LCD_VCC1V8_NAME	"gpio_lcd_vcc1v8"
#define GPIO_LCD_P5V5_ENABLE_NAME	"gpio_lcd_p5v5_enable"
#define GPIO_LCD_N5V5_ENABLE_NAME "gpio_lcd_n5v5_enable"
#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"

static uint32_t gpio_lcd_bl_enable;
static uint32_t gpio_lcd_vcc1v8;
static uint32_t gpio_lcd_p5v5_enable;
static uint32_t gpio_lcd_n5v5_enable;
static uint32_t gpio_lcd_reset;

static struct gpio_desc fpga_lcd_gpio_request_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* IOVCC _1.8V*/
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* reset */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};

static struct gpio_desc fpga_lcd_gpio_free_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* IOVCC _1.8V*/
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 0,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
	/* reset */
	{DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};

static struct gpio_desc fpga_lcd_gpio_normal_cmds[] = {
	/* IOVCC _1.8V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 12,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
	/* AVDD_5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 10,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 1},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 50,
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

static struct gpio_desc fpga_lcd_gpio_lowpower_cmds[] = {
	/* backlight enable */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_BL_ENABLE_NAME, &gpio_lcd_bl_enable, 0},
	/* AVEE_-5.5V */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_N5V5_ENABLE_NAME, &gpio_lcd_n5v5_enable, 0},
	/* AVDD_5.5V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_P5V5_ENABLE_NAME, &gpio_lcd_p5v5_enable, 0},
	/* IOVCC _1.8V*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
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
	/* IOVCC _1.8V input*/
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_VCC1V8_NAME, &gpio_lcd_vcc1v8, 0},
	/* reset input */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0},
};

static struct hisi_fb_panel_data g_panel_data;

/*******************************************************************************
**
*/
static int mipi_cmi_panel_set_fastboot(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	// lcd gpio request
	gpio_cmds_tx(fpga_lcd_gpio_request_cmds, \
		ARRAY_SIZE(fpga_lcd_gpio_request_cmds));

	// backlight on
	hisi_lcd_backlight_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_cmi_panel_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;
	uint32_t status = 0;
	uint32_t try_times = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);
	BUG_ON(pinfo == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	pinfo = &(hisifd->panel_info);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		pinfo->lcd_init_step = LCD_INIT_MIPI_LP_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_LP_SEND_SEQUENCE) {
		// lcd gpio request
		gpio_cmds_tx(fpga_lcd_gpio_request_cmds, \
			ARRAY_SIZE(fpga_lcd_gpio_request_cmds));
		// lcd gpio normal
		gpio_cmds_tx(fpga_lcd_gpio_normal_cmds, \
			ARRAY_SIZE(fpga_lcd_gpio_normal_cmds));
		// lcd display on sequence
		mipi_dsi_cmds_tx(cmi_display_on_cmds, \
			ARRAY_SIZE(cmi_display_on_cmds), mipi_dsi0_base);

		// check lcd power state
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

		pinfo->lcd_init_step = LCD_INIT_MIPI_HS_SEND_SEQUENCE;
	} else if (pinfo->lcd_init_step == LCD_INIT_MIPI_HS_SEND_SEQUENCE) {
        	// backlight on
        	hisi_lcd_backlight_on(pdev);
	} else {
		HISI_FB_ERR("failed to init lcd!\n");
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_cmi_panel_off(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *mipi_dsi0_base = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);
	BUG_ON(pinfo == NULL);
	mipi_dsi0_base = hisifd->mipi_dsi0_base;

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	// backlight off
	hisi_lcd_backlight_off(pdev);

       mipi_dsi_cmds_tx(cmi_display_off_cmds, \
			ARRAY_SIZE(cmi_display_off_cmds), mipi_dsi0_base);

	// lcd gpio lowpower
	gpio_cmds_tx(fpga_lcd_gpio_lowpower_cmds, \
		ARRAY_SIZE(fpga_lcd_gpio_lowpower_cmds));
	// lcd gpio free
	gpio_cmds_tx(fpga_lcd_gpio_free_cmds, \
		ARRAY_SIZE(fpga_lcd_gpio_free_cmds));

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_cmi_panel_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int mipi_cmi_panel_set_backlight(struct platform_device *pdev, uint32_t bl_level)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;

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

	if (hisifd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		ret = hisi_pwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_BLPWM) {
		ret = hisi_blpwm_set_backlight(hisifd, bl_level);
	} else if (hisifd->panel_info.bl_set_type & BL_SET_BY_SH_BLPWM) {
		ret = hisi_sh_blpwm_set_backlight(hisifd, bl_level);
	}  else if (hisifd->panel_info.bl_set_type & BL_SET_BY_MIPI) {
		bl_level_adjust[1] = bl_level * 255 / hisifd->panel_info.bl_max;
		mipi_dsi_cmds_tx(lcd_bl_level_adjust, \
			ARRAY_SIZE(lcd_bl_level_adjust), hisifd->mipi_dsi0_base);
	} else {
		HISI_FB_ERR("fb%d, not support this bl_set_type(%d)!\n",
			hisifd->index, hisifd->panel_info.bl_set_type);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}


/******************************************************************************/
static ssize_t mipi_cmi_panel_lcd_model_show(struct platform_device *pdev,
	char *buf)
{
	struct hisi_fb_data_type *hisifd = NULL;
	ssize_t ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = snprintf(buf, PAGE_SIZE, "mipi_cmi_NT35521\n");

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t mipi_cmi_panel_lcd_cabc_mode_show(struct platform_device *pdev,
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

static ssize_t mipi_cmi_panel_lcd_cabc_mode_store(struct platform_device *pdev,
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

static ssize_t mipi_cmi_panel_lcd_check_reg(struct platform_device *pdev,
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

static ssize_t mipi_cmi_panel_lcd_mipi_detect(struct platform_device *pdev,
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
	.set_fastboot = mipi_cmi_panel_set_fastboot,
	.on = mipi_cmi_panel_on,
	.off = mipi_cmi_panel_off,
	.remove = mipi_cmi_panel_remove,
	.set_backlight = mipi_cmi_panel_set_backlight,

	.lcd_model_show = mipi_cmi_panel_lcd_model_show,
	.lcd_cabc_mode_show = mipi_cmi_panel_lcd_cabc_mode_show,
	.lcd_cabc_mode_store = mipi_cmi_panel_lcd_cabc_mode_store,
	.lcd_check_reg = mipi_cmi_panel_lcd_check_reg,
	.lcd_mipi_detect = mipi_cmi_panel_lcd_mipi_detect,
	.set_display_region = NULL,
	.set_display_resolution = NULL,
};


/*******************************************************************************
**
*/
static int mipi_cmi_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	struct device_node *np = NULL;
    uint32_t bl_type = 0;
    uint32_t lcd_display_type = 0;
    uint32_t lcd_ifbc_type = 0;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_MIPI_CMI_NT35521);
	if (!np) {
		HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_MIPI_CMI_NT35521);
		goto err_return;
	}

    ret = of_property_read_u32(np, LCD_BL_TYPE_NAME, &bl_type);//8
	if (ret) {
		HISI_FB_ERR("get lcd_bl_type failed!\n");
		bl_type = BL_SET_BY_MIPI;
	}

    ret = of_property_read_u32(np, LCD_DISPLAY_TYPE_NAME, &lcd_display_type);
	if (ret) {
		HISI_FB_ERR("get lcd_display_type failed!\n");
		lcd_display_type = PANEL_MIPI_VIDEO;
	}

    ret = of_property_read_u32(np, LCD_IFBC_TYPE_NAME, &lcd_ifbc_type);
	if (ret) {
		HISI_FB_ERR("get ifbc_type failed!\n");
		lcd_ifbc_type = IFBC_TYPE_NONE;
	}

	HISI_FB_INFO("bl_type=0x%x.", bl_type);

	if (hisi_fb_device_probe_defer(lcd_display_type, bl_type)) {
		goto err_probe_defer;
	}

	HISI_FB_DEBUG("+.\n");

	HISI_FB_INFO("%s\n", DTS_COMP_MIPI_CMI_NT35521);

	gpio_lcd_vcc1v8 = of_get_named_gpio(np, "gpios", 0);			//gpio_6_2
	gpio_lcd_p5v5_enable = of_get_named_gpio(np, "gpios", 1); 	//gpio_6_0
	gpio_lcd_n5v5_enable = of_get_named_gpio(np, "gpios", 2);	//gpio_8_1
	gpio_lcd_reset = of_get_named_gpio(np, "gpios", 3); 			//gpio_7_3
	gpio_lcd_bl_enable = of_get_named_gpio(np, "gpios", 4); 		//gpio_8_6

	pdev->id = 1;
	/* init lcd panel info */
	pinfo = g_panel_data.panel_info;
	memset(pinfo, 0, sizeof(struct hisi_panel_info));
	pinfo->xres = 720;
	pinfo->yres = 1280;
	pinfo->width = 68;
	pinfo->height = 121;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = LCD_RGB888;
	pinfo->bgr_fmt = LCD_RGB;
	pinfo->bl_set_type = bl_type;

	pinfo->type = lcd_display_type;
	pinfo->ifbc_type = lcd_ifbc_type;

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

	//pinfo->spi_dev = g_spi_dev;

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;

	//sbl
	pinfo->sbl_support = 0;

	//ldi
	pinfo->ldi.h_back_porch = 32;//100;
	pinfo->ldi.h_front_porch = 169;//400;
	pinfo->ldi.h_pulse_width = 2;//20;
	pinfo->ldi.v_back_porch = 25;
	pinfo->ldi.v_front_porch = 25;
	pinfo->ldi.v_pulse_width = 2;

	//mipi
	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.max_tx_esc_clk = 10 * 1000000;//old version not have
	pinfo->mipi.burst_mode = DSI_BURST_SYNC_PULSES_1;

	pinfo->mipi.dsi_bit_clk = 120;
	pinfo->mipi.dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk;

	pinfo->pxl_clk_rate = 40 * 1000000UL;
	pinfo->pxl_clk_rate_div = 1;

	pinfo->vsync_ctrl_type = 0;
	pinfo->dirty_region_updt_support = 0;

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
		.compatible = DTS_COMP_MIPI_CMI_NT35521,
		.data = NULL,
	},
	{},
};

static struct platform_driver this_driver = {
	.probe = mipi_cmi_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_cmi_NT35521",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_panel_match_table),
	},
};

static int __init mipi_cmi_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_cmi_panel_init);
