/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
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
#include "hisi_rgb2mipi.h"


/*******************************************************************************
** GPIO
*/
#define BR_SPI_CS 168

 /* gpio resouce  */
#define GPIO_RGB2MIPI_POWER_1V2_NAME "bg_1.2v"
#define GPIO_RGB2MIPI_STANDBY_NAME "bg_lcd_standby"
#define GPIO_RGB2MIPI_RESETN_NAME "bg_lcd_resetn"
#define GPIO_RGB2MIPI_GATING_NAME "bg_gating"
#define GPIO_RGB2MIPI_PCLK_GATING_NAME "pclk_gating"
#define GPIO_RGB2MIPI_REFCLK_GATING_NAME "refclk_gating"
#define GPIO_RGB2MIPI_SPICS_NAME "bg_spi_cs"
#define GPIO_LCD_DRV_EN_NAME "lcd_drv_en"

static uint32_t gpio_rgb2mipi_power_1v2 = GPIO_LCD_POWER_1V2;
static uint32_t gpio_rgb2mipi_standby = GPIO_LCD_STANDBY;
static uint32_t gpio_rgb2mipi_resetn = GPIO_LCD_RESETN;
static uint32_t gpio_rgb2mipi_gating = GPIO_LCD_GATING;
static uint32_t gpio_rgb2mipi_pclk_gating = GPIO_LCD_PCLK_GATING;
static uint32_t gpio_rgb2mipi_refclk_gating = GPIO_LCD_REFCLK_GATING;
static uint32_t gpio_rgb2mipi_spics = GPIO_LCD_SPICS;
static uint32_t gpio_rgb2mipi_drv_en = GPIO_LCD_DRV_EN;

static struct gpio_desc rgb2mipi_gpio_request_cmds[] = {
	/*  power 1v2 */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_POWER_1V2_NAME, &gpio_rgb2mipi_power_1v2, 0},
	/* standby */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_STANDBY_NAME, &gpio_rgb2mipi_standby, 0},
	/* resetn */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_RESETN_NAME, &gpio_rgb2mipi_resetn, 0},
	/* bg gating */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_GATING_NAME, &gpio_rgb2mipi_gating, 0},
	/* ref clock gating */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_PCLK_GATING_NAME, &gpio_rgb2mipi_pclk_gating, 0},
	/* pclock gating */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_REFCLK_GATING_NAME, &gpio_rgb2mipi_refclk_gating, 0},
	/* spi cs */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_SPICS_NAME, &gpio_rgb2mipi_spics, 0},
	/* lcd drv enable */
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_DRV_EN_NAME, &gpio_rgb2mipi_drv_en, 0},
};

static struct gpio_desc rgb2mipi_gpio_free_cmds[] = {
	/*  power 1v2 */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_POWER_1V2_NAME, &gpio_rgb2mipi_power_1v2, 0},
	/* standby */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_STANDBY_NAME, &gpio_rgb2mipi_standby, 0},
	/* resetn */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_RESETN_NAME, &gpio_rgb2mipi_resetn, 0},
	/* bg gating */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_GATING_NAME, &gpio_rgb2mipi_gating, 0},
	/* ref clock gating */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_PCLK_GATING_NAME, &gpio_rgb2mipi_pclk_gating, 0},
	/* pclock gating */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_REFCLK_GATING_NAME, &gpio_rgb2mipi_refclk_gating, 0},
	/* spi cs */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_RGB2MIPI_SPICS_NAME, &gpio_rgb2mipi_spics, 0},
	/* lcd drv enable */
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_LCD_DRV_EN_NAME, &gpio_rgb2mipi_drv_en, 0},
};

static struct gpio_desc rgb2mipi_gpio_normal_cmds[] = {
	/* set bg gating*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 10,
		GPIO_RGB2MIPI_GATING_NAME,&gpio_rgb2mipi_gating, 1},
	/* set pclk gating to enable pclk */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 100,
		GPIO_RGB2MIPI_PCLK_GATING_NAME,&gpio_rgb2mipi_pclk_gating, 1},
	/* 1.2v en*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 10,
		GPIO_RGB2MIPI_POWER_1V2_NAME, &gpio_rgb2mipi_power_1v2, 1},
	/* set refclk gating to enable refclk */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 50,
		GPIO_RGB2MIPI_REFCLK_GATING_NAME,&gpio_rgb2mipi_refclk_gating, 1},
	/* standby,Enable Gated IO */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 10,
		GPIO_RGB2MIPI_STANDBY_NAME, &gpio_rgb2mipi_standby, 1},
	/* hardware reset */
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 10,
		GPIO_RGB2MIPI_RESETN_NAME, &gpio_rgb2mipi_resetn, 1},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 10,
		GPIO_RGB2MIPI_RESETN_NAME, &gpio_rgb2mipi_resetn, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 100,
		GPIO_RGB2MIPI_RESETN_NAME, &gpio_rgb2mipi_resetn, 1},
	/* set spi cs high*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 2,
		GPIO_RGB2MIPI_SPICS_NAME, &gpio_rgb2mipi_spics, 1},
	/* lcd drv enable*/
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 2,
		GPIO_LCD_DRV_EN_NAME, &gpio_rgb2mipi_drv_en, 1},
};

static struct gpio_desc rgb2mipi_gpio_lowpower_cmds[] = {
	/* set bg gating*/
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 10,
		GPIO_RGB2MIPI_GATING_NAME, &gpio_rgb2mipi_gating, 0},
	/* set pclk gating to enable pclk */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 100,
		GPIO_RGB2MIPI_PCLK_GATING_NAME,&gpio_rgb2mipi_pclk_gating, 0},
	/* 1.2v en*/
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 10,
		GPIO_RGB2MIPI_POWER_1V2_NAME, &gpio_rgb2mipi_power_1v2, 0},
	/* set refclk gating to enable refclk */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 50,
		GPIO_RGB2MIPI_REFCLK_GATING_NAME, &gpio_rgb2mipi_refclk_gating, 0},
	/* standby,Enable Gated IO */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 10,
		GPIO_RGB2MIPI_STANDBY_NAME, &gpio_rgb2mipi_standby, 0},
	/* hardware reset */
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 10,
		GPIO_RGB2MIPI_RESETN_NAME, &gpio_rgb2mipi_resetn, 0},
	/* set spi cs high*/
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 2,
		GPIO_RGB2MIPI_SPICS_NAME, &gpio_rgb2mipi_spics, 0},
	/* lcd drv enable*/
	{DTYPE_GPIO_INPUT, WAIT_TYPE_MS, 2,
		GPIO_LCD_DRV_EN_NAME, &gpio_rgb2mipi_drv_en, 0},
};


/*******************************************************************************
** RGB2MIPI BRIDGE CMDS
*/
/* rgb2mipi bridge setting cmds */
static struct rgb2mipi_spi_cmd_desc software_reset_cmds[] = {
	{0x0040, 0x01, 10, WAIT_TYPE_MS}, //s/w reset
	{0x0040, 0x00, 10, WAIT_TYPE_MS}, //s/w reset release
};

static struct rgb2mipi_spi_cmd_desc spi_host_setting_cmds[] = {
	{0x0008, 0x28, 0, WAIT_TYPE_US}, //spi host setting
};

static struct rgb2mipi_spi_cmd_desc pll_clock_setting_cmds[] = {
	{0x0020, 0x01, 0, WAIT_TYPE_US}, //pll input clock pre divider(PRD)
	{0x0021, 0x00, 0, WAIT_TYPE_US}, //pll setting 0
	{0x0022, 0x1F, 0, WAIT_TYPE_US}, //pll feadback divider(FBD)
	{0x0023, 0x80, 0, WAIT_TYPE_US}, //pll FRS,LBWS(HSCK=MHz)
	{0x0024, 0x00, 0, WAIT_TYPE_US},
	{0x0025, 0x02, 0, WAIT_TYPE_US}, //SYSCLK divider
	{0x0024, 0x01, 4, WAIT_TYPE_MS}, //pll enable :1
	{0x0024, 0x03, 0, WAIT_TYPE_US}, //CKEN = 1
	{0x0028, 0x01, 50, WAIT_TYPE_US}, //SYSCENA = 1 :10
};

static struct rgb2mipi_spi_cmd_desc picture_size_setting_cmds[] = {
	{0x0110, 0x00, 0, WAIT_TYPE_US}, //X left edge
	{0x0111, 0x00, 0, WAIT_TYPE_US},
	{0x0112, 0x1B, 0, WAIT_TYPE_US}, //X right edge
	{0x0113, 0x02, 0, WAIT_TYPE_US},
	{0x0114, 0x00, 0, WAIT_TYPE_US}, //Y top edge
	{0x0115, 0x00, 0, WAIT_TYPE_US},
	{0x0116, 0xBF, 0, WAIT_TYPE_US}, //Y bottom edge
	{0x0117, 0x03, 0, WAIT_TYPE_US},
};

static struct rgb2mipi_spi_cmd_desc dpi_input_setting_cmds[] = {
	{0x0140, 0x02, 0, WAIT_TYPE_US}, //dpi input format
	{0x0500, 0x01, 0, WAIT_TYPE_US}, //DPI module enable
	{0x0508, 0x1B, 0, WAIT_TYPE_US}, //TG HDP size
	{0x0509, 0x02, 0, WAIT_TYPE_US},
	{0x050A, 0x0A, 0, WAIT_TYPE_US}, //HSYNC width
	{0x050C, 0xB0, 0, WAIT_TYPE_US}, //hfp
	{0x050D, 0x00, 0, WAIT_TYPE_US},
	{0x050E, 0x31, 0, WAIT_TYPE_US}, //hbp;0x31
	{0x050F, 0x00, 0, WAIT_TYPE_US},
	{0x0514, 0xBF, 0, WAIT_TYPE_US}, //TG VDP size
	{0x0515, 0x03, 0, WAIT_TYPE_US},
	{0x0516, 0x03, 0, WAIT_TYPE_US}, //VSYNC width
	{0x0518, 0x1F, 0, WAIT_TYPE_US}, //vfp
	{0x0519, 0x00, 0, WAIT_TYPE_US},
	{0x051A, 0x1F, 0, WAIT_TYPE_US}, //vbp
	{0x051B, 0x00, 0, WAIT_TYPE_US},
	{0x0501, 0x07, 0, WAIT_TYPE_US}, //dpi input HSYNC,VSYNC,DE polarity
	{0x0520, 0x02, 0, WAIT_TYPE_US}, //line adjustment pixel count
	{0x0522, 0x03, 0, WAIT_TYPE_US}, //line adjustment byte count
};

static struct rgb2mipi_spi_cmd_desc dsi_param_setting_cmds[] = {
	{0x0900, 0x01, 0, WAIT_TYPE_US}, //dsi enable
	{0x1904, 0x1D, 0, WAIT_TYPE_US}, //IP reset
	{0x1905, 0x00, 0, WAIT_TYPE_US},
	{0x1906, 0x00, 0, WAIT_TYPE_US},
	{0x1907, 0x00, 0, WAIT_TYPE_US},
	{0x1C10, 0x70, 0, WAIT_TYPE_US}, //LINEINITCNT
	{0x1C11, 0x17, 0, WAIT_TYPE_US},
	{0x1C12, 0x00, 0, WAIT_TYPE_US},
	{0x1C13, 0x00, 0, WAIT_TYPE_US},
	{0x1C14, 0x07, 0, WAIT_TYPE_US}, //LPTXTIMECNT
	{0x1C15, 0x00, 0, WAIT_TYPE_US},
	{0x1C16, 0x00, 0, WAIT_TYPE_US},
	{0x1C17, 0x00, 0, WAIT_TYPE_US},
	{0x1C18, 0x06, 0, WAIT_TYPE_US}, //TCLK_HEADERCNT
	{0x1C19, 0x10, 0, WAIT_TYPE_US},
	{0x1C1A, 0x00, 0, WAIT_TYPE_US},
	{0x1C1B, 0x00, 0, WAIT_TYPE_US},
	{0x1C1C, 0x02, 0, WAIT_TYPE_US}, //TCLK_TRAILCNT :0x00
	{0x1C1D, 0x00, 0, WAIT_TYPE_US},
	{0x1C1E, 0x00, 0, WAIT_TYPE_US},
	{0x1C1F, 0x00, 0, WAIT_TYPE_US},
	{0x1C20, 0x06, 0, WAIT_TYPE_US}, //THS_HEADERCNT
	{0x1C21, 0x01, 0, WAIT_TYPE_US},
	{0x1C22, 0x00, 0, WAIT_TYPE_US},
	{0x1C23, 0x00, 0, WAIT_TYPE_US},
	{0x1C24, 0xB0, 0, WAIT_TYPE_US}, //TWAKEUPCNT
	{0x1C25, 0x36, 0, WAIT_TYPE_US},
	{0x1C26, 0x00, 0, WAIT_TYPE_US},
	{0x1C27, 0x00, 0, WAIT_TYPE_US},
	{0x1C28, 0x08, 0, WAIT_TYPE_US}, //TCLK_POSTCNT
	{0x1C29, 0x00, 0, WAIT_TYPE_US},
	{0x1C2A, 0x00, 0, WAIT_TYPE_US},
	{0x1C2B, 0x00, 0, WAIT_TYPE_US},
	{0x1C2C, 0x03, 0, WAIT_TYPE_US}, //THS_TRAILCNT
	{0x1C2D, 0x00, 0, WAIT_TYPE_US},
	{0x1C2E, 0x00, 0, WAIT_TYPE_US},
	{0x1C2F, 0x00, 0, WAIT_TYPE_US},
	{0x1C30, 0x05, 0, WAIT_TYPE_US}, //HSTXVREGCNT
	{0x1C31, 0x00, 0, WAIT_TYPE_US},
	{0x1C32, 0x00, 0, WAIT_TYPE_US},
	{0x1C33, 0x00, 0, WAIT_TYPE_US},
	{0x1C34, 0x07, 0, WAIT_TYPE_US}, //HSTXVREGEN enable
	{0x1C35, 0x00, 0, WAIT_TYPE_US},
	{0x1C36, 0x00, 0, WAIT_TYPE_US},
	{0x1C37, 0x00, 0, WAIT_TYPE_US},
	{0x1C3C, 0x07, 0, WAIT_TYPE_US}, //BTACNTRL1
	{0x1C3D, 0x00, 0, WAIT_TYPE_US},
	{0x1C3E, 0x07, 0, WAIT_TYPE_US},
	{0x1C3F, 0x00, 0, WAIT_TYPE_US},
	{0x1C04, 0x01, 0, WAIT_TYPE_US}, //STARTCNTRL
	{0x1C05, 0x00, 0, WAIT_TYPE_US},
	{0x1C06, 0x00, 0, WAIT_TYPE_US},
	{0x1C07, 0x00, 0, WAIT_TYPE_US},
	{0x0912, 0x09, 0, WAIT_TYPE_US}, //BLenable
	{0x0918, 0x76, 0, WAIT_TYPE_US}, //BL1[7:0]
	{0x0919, 0x00, 0, WAIT_TYPE_US}, //BL1[15:8]
	{0x091A, 0x86, 0, WAIT_TYPE_US}, //BL2[7:0]
	{0x091B, 0x00, 0, WAIT_TYPE_US}, //BL2[15:8]
	{0x091C, 0x5C, 0, WAIT_TYPE_US}, //BL3[7:0]
	{0x091D, 0x07, 0, WAIT_TYPE_US}, //BL3[15:8]
	{0x091E, 0x13, 0, WAIT_TYPE_US}, //BL4[7:0]
	{0x091F, 0x00, 0, WAIT_TYPE_US}, //BL4[15:8]
};

/*preparation for receiving dpi input*/
static struct rgb2mipi_spi_cmd_desc prep4rec_dpi_input_setting_cmds[] = {
	{0x1C38, 0x00, 0, WAIT_TYPE_US}, //CONTCLKMODE DSI clock enable/disable during LP  0x00
	{0x1C39, 0x00, 0, WAIT_TYPE_US},
	{0x1C3A, 0x00, 0, WAIT_TYPE_US},
	{0x1C3B, 0x00, 0, WAIT_TYPE_US},
	{0x180C, 0x82, 0, WAIT_TYPE_US}, //transmission mode
	{0x180D, 0x3F, 0, WAIT_TYPE_US},
	{0x180E, 0x00, 0, WAIT_TYPE_US},
	{0x180F, 0x00, 0, WAIT_TYPE_US},
	{0x0910, 0x01, 0, WAIT_TYPE_US}, //transmission mode
	{0x0911, 0x00, 0, WAIT_TYPE_US}, //RGB666 mode
	{0x01C0, 0x01, 0, WAIT_TYPE_US}, //image FIFO reset
	{0x0504, 0x01, 0, WAIT_TYPE_US}, //DPI capture start
};

static struct rgb2mipi_spi_cmd_desc display_stop_cmds[] = {
	{0x0504, 0x00, 20, WAIT_TYPE_MS}, //dpi capture stop
	{0x0028, 0x00, 00, WAIT_TYPE_US},	 //SYSCENA = 0, disable system clock output
	{0x0024, 0x01, 00, WAIT_TYPE_US},	 //CKEN = 0, disable pll clock output
	{0x0024, 0x00, 00, WAIT_TYPE_US},	 //reset pll function
	{0x0040, 0x01, 00, WAIT_TYPE_US}, //s/w reset
};


/*
**data read/write functions
*/
static struct rgb2mipi_spi_cmd_desc write_datatype_cmds[] = {
	{0x0924, 0x05, 00, WAIT_TYPE_US},
	{0x0925, 0x00, 00, WAIT_TYPE_US},
};

static struct rgb2mipi_spi_cmd_desc word_count_cmds[] = {
	{0x0926, 0x00, 00, WAIT_TYPE_US},
	{0x0927, 0x00, 00, WAIT_TYPE_US},
};

static struct rgb2mipi_spi_cmd_desc DCS_command_cmds[] = {
	{0x0928, 0x00, 00, WAIT_TYPE_US},
};

static struct rgb2mipi_spi_cmd_desc param_upto8_cmds[] = {
	{0x0929, 0x00, 00, WAIT_TYPE_US},
	{0x092A, 0x00, 00, WAIT_TYPE_US},
	{0x092B, 0x00, 00, WAIT_TYPE_US},
	{0x092C, 0x00, 00, WAIT_TYPE_US},
	{0x092D, 0x00, 00, WAIT_TYPE_US},
	{0x092E, 0x00, 00, WAIT_TYPE_US},
	{0x092F, 0x00, 00, WAIT_TYPE_US},
};

static struct rgb2mipi_spi_cmd_desc param_all_payload_cmds[] = {
	{0x01B0, 0x00, 00, WAIT_TYPE_US},
};

static struct rgb2mipi_spi_cmd_desc packet_trans_cmds[] = {
	{0x0920, 0x01, 00, WAIT_TYPE_US}
};


/*******************************************************************************
**
*/
static int rgb2mipi_spi_cmds_tx(struct spi_device *spi_dev,
	struct rgb2mipi_spi_cmd_desc *cmds, int cnt)
{
	char buf_addr[3] = {0};
	char buf_data[2] = {0};
	int i = 0;

	BUG_ON(spi_dev == NULL);
	BUG_ON(cmds == NULL);

	for (i = 0; i < cnt; i++) {
		gpio_direction_output(BR_SPI_CS, 0);

		buf_addr[0] = 0x40;
		buf_addr[1] = cmds[i].reg >> 8;
		buf_addr[2] = cmds[i].reg & 0xff;
		spi_write(spi_dev, buf_addr, 3);

		udelay(50);

		gpio_direction_output(BR_SPI_CS, 1);

		udelay(50);

		gpio_direction_output(BR_SPI_CS, 0);

		buf_data[0] = 0x80;
		buf_data[1] = cmds[i].value & 0xff;
		spi_write(spi_dev, buf_data, 2);

		udelay(50);

		gpio_direction_output(BR_SPI_CS, 1);

		udelay(50);

		if (cmds[i].delay) {
			if (cmds[i].delaytype == WAIT_TYPE_US)
				udelay(cmds[i].delay);
			else if (cmds[i].delaytype == WAIT_TYPE_MS)
				mdelay(cmds[i].delay);
			else
				mdelay(cmds[i].delay * 1000);
		}
	}

	return 0;
}

#if 0
static int rgb2mipi_spi_cmds_rx(struct spi_device *spi_dev,
	struct rgb2mipi_spi_cmd_desc *cmds, int cnt)
{
	char buf_addr[3] = {0};
	char buf_wdata[1] = {0};
	char buf_rdata[1] = {0};
	int i = 0;

	BUG_ON(spi_dev == NULL);
	BUG_ON(cmds == NULL);

	for(i = 0; i < cnt; i++) {
		gpio_direction_output(BR_SPI_CS, 0);

		/* address set */
		buf_addr[0] = 0x40;
		buf_addr[1] = cmds[i].reg >> 8;
		buf_addr[2] = cmds[i].reg & 0xff;
		spi_write(spi_dev, buf_addr, 3);

		udelay(50);
		gpio_direction_output(BR_SPI_CS, 1);

		mdelay(1);

		gpio_direction_output(BR_SPI_CS, 0);

		/* write then read command */
		buf_wdata[0] = 0xc0;
		spi_write_then_read(spi_dev, buf_wdata, 1, buf_rdata, 1);

		cmds[i].value = buf_rdata[0];

		mdelay(1);
		gpio_direction_output(BR_SPI_CS, 1);
		mdelay(1);

		if (cmds[i].delay) {
			if (cmds[i].delaytype == WAIT_TYPE_US)
				udelay(cmds[i].delay);
			else if (cmds[i].delaytype == WAIT_TYPE_MS)
				mdelay(cmds[i].delay);
			else
				mdelay(cmds[i].delay * 1000);
		}
	}

	return 0;
}
#endif

static int rgb2mipi_swrite(struct spi_device *spi_dev, struct dsi_cmd_desc *cm)
{
	int dataLength = 0;
	uint16_t cmds = 0;

	BUG_ON(spi_dev == NULL);
	BUG_ON(cm == NULL);

	dataLength = cm->dlen;
	if (dataLength == 1) {
		/* DCS Short Write (no parameters) */

		write_datatype_cmds[0].value= 0x05;
		rgb2mipi_spi_cmds_tx(spi_dev, write_datatype_cmds,
			ARRAY_SIZE(write_datatype_cmds));

		word_count_cmds[0].value= 0x00;
		word_count_cmds[1].value = 0x00;
		rgb2mipi_spi_cmds_tx(spi_dev, word_count_cmds,
			ARRAY_SIZE(word_count_cmds));

		cmds = (uint8_t)(*cm->payload);
		DCS_command_cmds[0].value = cmds;
		rgb2mipi_spi_cmds_tx(spi_dev, DCS_command_cmds,
			ARRAY_SIZE(DCS_command_cmds));

		param_upto8_cmds[0].value = 0x00;
		param_upto8_cmds[1].value = 0x00;
		param_upto8_cmds[2].value = 0x00;
		rgb2mipi_spi_cmds_tx(spi_dev, param_upto8_cmds, 3);

		packet_trans_cmds[0].value = 0x01;
		rgb2mipi_spi_cmds_tx(spi_dev, packet_trans_cmds,
			ARRAY_SIZE(packet_trans_cmds));
	} else if (dataLength == 2) {
		/* DCS Short Write (1 parameters) */

		write_datatype_cmds[0].value= 0x15;
		rgb2mipi_spi_cmds_tx(spi_dev, write_datatype_cmds,
			ARRAY_SIZE(write_datatype_cmds));

		word_count_cmds[0].value = 0x00;
		word_count_cmds[1].value = 0x00;
		rgb2mipi_spi_cmds_tx(spi_dev, word_count_cmds,
			ARRAY_SIZE(word_count_cmds));

		cmds = (uint8_t)(*cm->payload);
		DCS_command_cmds[0].value = cmds;
		rgb2mipi_spi_cmds_tx(spi_dev, DCS_command_cmds,
			ARRAY_SIZE(DCS_command_cmds));

		cmds =*( (uint8_t *)(cm->payload + 1));
		param_upto8_cmds[0].value = cmds;
		param_upto8_cmds[1].value = 0x00;
		param_upto8_cmds[2].value = 0x00;
		rgb2mipi_spi_cmds_tx(spi_dev, param_upto8_cmds, 3);

		packet_trans_cmds[0].value = 0x01;
		rgb2mipi_spi_cmds_tx(spi_dev, packet_trans_cmds,
			ARRAY_SIZE(packet_trans_cmds));
	} else {
		BUG_ON(1);
	}

	/* Wait until packet sending finish */
	mdelay(10);

	return dataLength;
}

static int rgb2mipi_lwrite(struct spi_device *spi_dev, struct dsi_cmd_desc *cm)
{
	int dataLength = 0;
	int i = 0;
	uint16_t cmds = 0;

	BUG_ON(spi_dev == NULL);
	BUG_ON(cm == NULL);
	dataLength = cm->dlen;
	BUG_ON(dataLength <= 2);

	if ((dataLength > 2) && (dataLength <= 8)) {
		/* DCS Short Write (upto 8 parameters) */

		write_datatype_cmds[0].value = 0x39;
		rgb2mipi_spi_cmds_tx(spi_dev, write_datatype_cmds,
			ARRAY_SIZE(write_datatype_cmds));

		word_count_cmds[0].value = dataLength;
		word_count_cmds[1].value = 0x00;
		rgb2mipi_spi_cmds_tx(spi_dev, word_count_cmds,
			ARRAY_SIZE(word_count_cmds));

		cmds = (uint8_t)(*cm->payload);
		DCS_command_cmds[0].value = cmds;
		rgb2mipi_spi_cmds_tx(spi_dev, DCS_command_cmds,
			ARRAY_SIZE(DCS_command_cmds));

		for(i = 0; i < dataLength - 1; i++){
			param_upto8_cmds[i].value =  *((uint8_t *)(cm->payload + i + 1));
		}
		for(i = dataLength - 1; i < 7; i++){
			param_upto8_cmds[i].value = 0x00;
		}
		rgb2mipi_spi_cmds_tx(spi_dev, param_upto8_cmds, dataLength -1);

		packet_trans_cmds[0].value = 0x0D;
		rgb2mipi_spi_cmds_tx(spi_dev, packet_trans_cmds,
			ARRAY_SIZE(packet_trans_cmds));
	} else {
		/* DCS long Write , all byte from payload FIFO */

		write_datatype_cmds[0].value = 0x39;
		rgb2mipi_spi_cmds_tx(spi_dev, write_datatype_cmds,
			ARRAY_SIZE(write_datatype_cmds));

		word_count_cmds[0].value = dataLength;
		word_count_cmds[1].value = 0x00;
		rgb2mipi_spi_cmds_tx(spi_dev, word_count_cmds,
			ARRAY_SIZE(word_count_cmds));

		for(i = 0; i < dataLength; i++) {
			param_all_payload_cmds[0].value =  *((uint8_t *)(cm->payload + i));
			rgb2mipi_spi_cmds_tx(spi_dev, param_all_payload_cmds,
				ARRAY_SIZE(param_all_payload_cmds));
		}

		packet_trans_cmds[0].value = 0x05;
		rgb2mipi_spi_cmds_tx(spi_dev, packet_trans_cmds,
			ARRAY_SIZE(packet_trans_cmds));
	}

	/* Wait until packet sending finish */
	mdelay(10);

	return dataLength;
}

static int rgb2mipi_cmd_add(struct spi_device *spi_dev, struct dsi_cmd_desc *cm)
{
	int len = 0;

	BUG_ON(spi_dev == NULL);
	BUG_ON(cm == NULL);

	switch (cm->dtype) {
	case DTYPE_GEN_WRITE:
	case DTYPE_GEN_WRITE1:
	case DTYPE_GEN_WRITE2:

	case DTYPE_DCS_WRITE:
	case DTYPE_DCS_WRITE1:
		len = rgb2mipi_swrite(spi_dev, cm);
		break;
	case DTYPE_GEN_LWRITE:
	case DTYPE_DCS_LWRITE:
		len = rgb2mipi_lwrite(spi_dev, cm);
		break;
	default:
		HISI_FB_ERR("dtype=%x NOT supported!\n", cm->dtype);
		break;
	}

	return len;
}

int rgb2mipi_cmds_tx(struct spi_device *spi_dev,
	struct dsi_cmd_desc *cmds, int cnt)
{
	struct dsi_cmd_desc *cm = NULL;
	int i = 0;

	BUG_ON(spi_dev == NULL);
	BUG_ON(cmds == NULL);

	cm = cmds;

	for (i = 0; i < cnt; i++) {
		rgb2mipi_cmd_add(spi_dev, cm);

		if (cm->wait) {
			if (cm->waittype == WAIT_TYPE_US)
				udelay(cm->wait);
			else if (cm->waittype == WAIT_TYPE_MS)
				mdelay(cm->wait);
			else
				mdelay(cm->wait * 1000);
		}
		cm++;
	}

	return cnt;
}


/*******************************************************************************
**
*/
static int rgb2mipi_init(struct hisi_fb_data_type *hisifd)
{
	struct spi_device *spi_dev = NULL;
	int ret = 0;

	BUG_ON(hisifd == NULL);
	spi_dev = hisifd->panel_info.spi_dev;
	BUG_ON(spi_dev == NULL);

	/* spi setup */
	spi_dev->mode = SPI_MODE_0;
	ret = spi_setup(spi_dev);
	if (ret < 0) {
		HISI_FB_ERR("ret = %d, spi_setup fail.\n", ret);
	}

	gpio_cmds_tx(rgb2mipi_gpio_request_cmds, \
		ARRAY_SIZE(rgb2mipi_gpio_request_cmds));

	gpio_cmds_tx(rgb2mipi_gpio_normal_cmds, \
		ARRAY_SIZE(rgb2mipi_gpio_normal_cmds));

	/* sending cmds via spi */
	rgb2mipi_spi_cmds_tx(spi_dev, software_reset_cmds,
		ARRAY_SIZE(software_reset_cmds));
	rgb2mipi_spi_cmds_tx(spi_dev, spi_host_setting_cmds,
		ARRAY_SIZE(spi_host_setting_cmds));
	rgb2mipi_spi_cmds_tx(spi_dev, pll_clock_setting_cmds,
		ARRAY_SIZE(pll_clock_setting_cmds));
	rgb2mipi_spi_cmds_tx(spi_dev, picture_size_setting_cmds,
		ARRAY_SIZE(picture_size_setting_cmds));
	rgb2mipi_spi_cmds_tx(spi_dev, dpi_input_setting_cmds,
		ARRAY_SIZE(dpi_input_setting_cmds));
	rgb2mipi_spi_cmds_tx(spi_dev, dsi_param_setting_cmds,
		ARRAY_SIZE(dsi_param_setting_cmds));

	return 0;
}

static int rgb2mipi_prep4Rec(struct hisi_fb_data_type *hisifd)
{
	struct spi_device *spi_dev = NULL;

	BUG_ON(hisifd == NULL);
	spi_dev = hisifd->panel_info.spi_dev;
	BUG_ON(spi_dev == NULL);

	/* TC358763XBG Preparation for receiving DPI input */
	rgb2mipi_spi_cmds_tx(spi_dev, prep4rec_dpi_input_setting_cmds,
		ARRAY_SIZE(prep4rec_dpi_input_setting_cmds));

	mdelay(5);

	return 0;
}

static int rgb2mipi_deinit(struct hisi_fb_data_type *hisifd)
{
	struct spi_device *spi_dev = NULL;

	BUG_ON(hisifd == NULL);
	spi_dev = hisifd->panel_info.spi_dev;
	BUG_ON(spi_dev == NULL);

	rgb2mipi_spi_cmds_tx(spi_dev, display_stop_cmds,
		ARRAY_SIZE(display_stop_cmds));

	gpio_cmds_tx(rgb2mipi_gpio_lowpower_cmds, \
		ARRAY_SIZE(rgb2mipi_gpio_lowpower_cmds));

	gpio_cmds_tx(rgb2mipi_gpio_free_cmds, \
		ARRAY_SIZE(rgb2mipi_gpio_free_cmds));

	return 0;
}


/*******************************************************************************
**
*/
static int rgb2mipi_set_fastboot(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_set_fastboot(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int rgb2mipi_on(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	hisifd->panel_info.lcd_init_step = LCD_INIT_POWER_ON;

	ret = panel_next_on(pdev);

	/* rgb2mipi bridge init */
	ret = rgb2mipi_init(hisifd);

	/* LCDD (Peripheral) Setting */
	ret = panel_next_on(pdev);

	/* rgb2mipi bridge prepare for receiving  */
	ret = rgb2mipi_prep4Rec(hisifd);

	ret = panel_next_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int rgb2mipi_off(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_off(pdev);

	rgb2mipi_deinit(hisifd);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int rgb2mipi_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_remove(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int rgb2mipi_set_backlight(struct platform_device *pdev, uint32_t bl_level)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_set_backlight(pdev, bl_level);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int rgb2mipi_vsync_ctrl(struct platform_device *pdev, int enable)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_vsync_ctrl(pdev, enable);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int rgb2mipi_frc_handle(struct platform_device *pdev, int fps)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_frc_handle(pdev, fps);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int rgb2mipi_esd_handle(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_esd_handle(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int rgb2mipi_probe(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct platform_device *dpe_dev = NULL;
	struct hisi_fb_panel_data *pdata = NULL;
	int ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	BUG_ON(hisifd->panel_info.spi_dev == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	/* alloc device */
	dpe_dev = platform_device_alloc(DEV_NAME_DSS_DPE, pdev->id);
	if (!dpe_dev) {
		HISI_FB_ERR("fb%d platform_device_alloc failed, error=%d!\n", hisifd->index, ret);
		ret = -ENOMEM;
		goto err_device_alloc;
	}

	/* link to the latest pdev */
	hisifd->pdev = dpe_dev;

	/* alloc panel device data */
	ret = platform_device_add_data(dpe_dev, dev_get_platdata(&pdev->dev),
		sizeof(struct hisi_fb_panel_data));
	if (ret) {
		HISI_FB_ERR("fb%d platform_device_add_data failed error=%d!\n", hisifd->index, ret);
		goto err_device_put;
	}

	/* data chain */
	pdata = dev_get_platdata(&dpe_dev->dev);
	pdata->set_fastboot = rgb2mipi_set_fastboot;
	pdata->on = rgb2mipi_on;
	pdata->off = rgb2mipi_off;
	pdata->remove = rgb2mipi_remove;
	pdata->set_backlight = rgb2mipi_set_backlight;
	pdata->vsync_ctrl = rgb2mipi_vsync_ctrl;
	pdata->frc_handle = rgb2mipi_frc_handle;
	pdata->esd_handle = rgb2mipi_esd_handle;
	pdata->next = pdev;

	/* get/set panel info */
	memcpy(&hisifd->panel_info, pdata->panel_info, sizeof(struct hisi_panel_info));

	/* set driver data */
	platform_set_drvdata(dpe_dev, hisifd);
	/* device add */
	ret = platform_device_add(dpe_dev);
	if (ret) {
		HISI_FB_ERR("fb%d platform_device_add failed, error=%d!\n", hisifd->index, ret);
		goto err_device_put;
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;

err_device_put:
	platform_device_put(dpe_dev);
err_device_alloc:
	return ret;
}

static struct platform_driver this_driver = {
	.probe = rgb2mipi_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = DEV_NAME_RGB2MIPI,
	},
};

static int __init rgb2mipi_driver_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(rgb2mipi_driver_init);
