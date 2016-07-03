/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
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
#ifndef __HW_LCD_PANEL_H_
#define __HW_LCD_PANEL_H_
/***********************************************************
*macro definition
***********************************************************/
#include "hw_lcd_debug.h"
#define CHECKSUM_SIZE   (8)
#define DTS_COMP_LCD_PANEL_TYPE     "huawei,lcd_panel_type"
#define PANEL_COMP_LENGTH       128
#define ESD_DEBUG   0
#define HW_LCD_POWER_STATUS_CHECK   1
#define BACKLIGHT_PRINT_TIMES	10

#define CABC_OFF	(0)
#define CABC_UI_MODE	(1)
#define CABC_STILL_MODE	(2)
#define CABC_MOVING_MODE	(3)

/*parse dirtyregion info node*/
#define OF_PROPERTY_READ_DIRTYREGION_INFO_RETURN(np, propname, ptr_out_value) \
	do { \
		of_property_read_u32(np, propname, ptr_out_value); \
		if( 0xffff == *ptr_out_value ) { \
			*ptr_out_value = -1; \
		} \
	} while (0)

/*parse dts node*/
#define OF_PROPERTY_READ_U32_RETURN(np, propname, ptr_out_value) \
	do { \
		if( of_property_read_u32(np, propname, ptr_out_value) ) { \
			HISI_FB_ERR("of_property_read_u32: %s, fail\n", propname); \
		} \
	} while (0)

/*parse dts node*/
#define OF_PROPERTY_READ_U8_RETURN(np, propname, ptr_out_value) \
	do { \
		int temp; \
		if( of_property_read_u32(np, propname, &temp) ) { \
			HISI_FB_ERR("of_property_read: %s, fail\n", propname); \
		} \
		*ptr_out_value = (char)temp; \
	} while (0)

/*parse dts node*/
#define OF_PROPERTY_READ_U32_DEFAULT(np, propname, ptr_out_value, default) \
	do { \
		if( of_property_read_u32(np, propname, ptr_out_value) ) { \
			HISI_FB_ERR("of_property_read_u32: %s, fail, use default: %d\n", propname, default); \
			*ptr_out_value = default;  \
		} \
	} while (0)

/*parse dts node*/
#define OF_PROPERTY_READ_U8_DEFAULT(np, propname, ptr_out_value, default) \
	do { \
		int temp; \
		if( of_property_read_u32(np, propname, &temp) ) { \
			HISI_FB_ERR("of_property_read: %s, fail, use default: %d\n", propname, default); \
			temp = default;  \
		} \
		*ptr_out_value = (char)temp; \
	} while (0)

/***********************************************************
*struct definition
***********************************************************/
/*dsi cmd struct*/
struct dsi_cmd_set {
	char* buf;
	int size_buf;
	struct dsi_cmd_desc* cmd_set;
	int cmd_cnt;
};

struct array_data {
	char* buf;
	int cnt;
};

struct hw_lcd_information {
	/*LcdanalogVcc*/
	u32 lcdanalog_vcc;
	/*LcdioVcc*/
	u32 lcdio_vcc;
	/*LcdBias*/
	u32 lcd_bias;
	/*LcdVsp*/
	u32 lcd_vsp;
	/*LcdVsn*/
	u32 lcd_vsn;
	/*reset hight*/
	u8 reset_step1_H;
	/*reset low*/
	u8 reset_L;
	/*reset hight*/
	u8 reset_step2_H;
	/*lcd on command*/
	struct dsi_cmd_set display_on_cmds;
	/*lcd off command*/
	struct dsi_cmd_set display_off_cmds;
	/*mipi tr inversion*/
	struct dsi_cmd_set dot_inversion_cmds;
	struct dsi_cmd_set column_inversion_cmds;
	/*lcd forword/revert scan test*/
	struct dsi_cmd_set forword_scan_cmds;
	struct dsi_cmd_set revert_scan_cmds;
	/*cabc off command*/
	struct dsi_cmd_set cabc_off_cmds;
	/*cabc ui command*/
	struct dsi_cmd_set cabc_ui_cmds;
	/*cabc still command*/
	struct dsi_cmd_set cabc_still_cmds;
	/*cabc moving command*/
	struct dsi_cmd_set cabc_moving_cmds;
	/*esd check*/
	struct array_data esd_reg;
	struct array_data esd_value;
	/*mipi tr check*/
	struct array_data mipi_check_reg;
	struct array_data mipi_check_value;
	/*backlight sem*/
	struct semaphore bl_sem;
	/*inversion mode*/
	int inversion_mode;
	/*scan mode*/
	int scan_mode;
	/*cabc function*/
	int cabc_mode;
	/*panel compatible*/
	char* lcd_type;
	/*panel name*/
	char* panel_name;
	/*otm1906c ic is need reset after iovcc power on*/
	u8 is_need_reset;
	/*nt35695 ic is need delay 200ms after panel off*/
	u8 is_need_delay;
	/*focal ic need lock cmd one to avoid esd disturb*/
	u8 lock_cmd_support;
	/*read lcd power status*/
	u8 read_power_status;
	/*ID0*/
	u32 lcd_id0;
	/*ID1*/
	u32 lcd_id1;
	/*esd set backlight*/
	u8 esd_set_bl;
};

enum {
	INVERSION_COLUMN,
	INVERSION_DOT,
};

enum {
	SCAN_TYPE_FORWORD = 0,
	SCAN_TYPE_REVERT,
};
/***********************************************************
*variable declaration
***********************************************************/
/*extern variable*/
extern bool gesture_func;
extern volatile bool g_lcd_control_tp_power;

static int g_debug_enable;

static struct hw_lcd_information lcd_info;

/************************************************************
 *
 * LCD VCC
 *
 ************************************************************/
#define VCC_BACKLIGHT_NAME      "lcd_backlight"
#define VCC_LCDBIAS_NAME        "vcc_lcdbias"
#define VCC_LCD_VSN_NAME        "lcd_vsn"
#define VCC_LCD_VSP_NAME        "lcd_vsp"

/* scharg regulator */
static struct regulator* lcd_bl_vcc;
static struct regulator* lcd_bias_vcc;
static struct regulator* lcd_vsn_vcc;
static struct regulator* lcd_vsp_vcc;

static struct vcc_desc hw_lcd_scharger_vcc_get_cmds[] = {
	/* vcc get */
	{DTYPE_VCC_GET, VCC_BACKLIGHT_NAME, &lcd_bl_vcc,   0, 0, 0, 0},
	{DTYPE_VCC_GET, VCC_LCDBIAS_NAME,   &lcd_bias_vcc, 0, 0, 0, 0},
	{DTYPE_VCC_GET, VCC_LCD_VSN_NAME,   &lcd_vsn_vcc,  0, 0, 0, 0},
	{DTYPE_VCC_GET, VCC_LCD_VSP_NAME,   &lcd_vsp_vcc,  0, 0, 0, 0},
};

static struct vcc_desc hw_lcd_scharger_vcc_set_cmds[] = {
	/* vcc set voltage */
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCDBIAS_NAME, &lcd_bias_vcc, 5400000, 5400000, 0, 0},
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCD_VSP_NAME, &lcd_vsp_vcc,  5400000, 5400000, 0, 0},
	{DTYPE_VCC_SET_VOLTAGE, VCC_LCD_VSN_NAME, &lcd_vsn_vcc,  5400000, 5400000, 0, 0},
};

static struct vcc_desc hw_lcd_scharger_vcc_put_cmds[] = {
	/* vcc put */
	{DTYPE_VCC_PUT, VCC_BACKLIGHT_NAME, &lcd_bl_vcc,   0, 0, 0, 0},
	{DTYPE_VCC_PUT, VCC_LCDBIAS_NAME,   &lcd_bias_vcc, 0, 0, 0, 0},
	{DTYPE_VCC_PUT, VCC_LCD_VSN_NAME,   &lcd_vsn_vcc,  0, 0, 0, 0},
	{DTYPE_VCC_PUT, VCC_LCD_VSP_NAME,   &lcd_vsp_vcc,  0, 0, 0, 0},
};

static struct vcc_desc hw_lcd_scharger_vcc_enable_cmds[] = {
	/* vcc enable */
	{DTYPE_VCC_ENABLE, VCC_LCDBIAS_NAME,   &lcd_bias_vcc, 0, 0, WAIT_TYPE_MS, 12},
	{DTYPE_VCC_ENABLE, VCC_LCD_VSP_NAME,   &lcd_vsp_vcc,  0, 0, WAIT_TYPE_MS, 10},
	{DTYPE_VCC_ENABLE, VCC_LCD_VSN_NAME,   &lcd_vsn_vcc,  0, 0, WAIT_TYPE_MS, 30},
};

static struct vcc_desc hw_lcd_scharger_vcc_disable_cmds[] = {
	/* vcc disable */
	{DTYPE_VCC_DISABLE, VCC_LCD_VSN_NAME,   &lcd_vsn_vcc,  0, 0, WAIT_TYPE_MS, 5},
	{DTYPE_VCC_DISABLE, VCC_LCD_VSP_NAME,   &lcd_vsp_vcc,  0, 0, WAIT_TYPE_MS, 5},
	{DTYPE_VCC_DISABLE, VCC_LCDBIAS_NAME,   &lcd_bias_vcc, 0, 0, WAIT_TYPE_MS, 1},
};

static struct vcc_desc hw_lcd_scharger_bl_enable_cmds[] = {
	/* backlight enable */
	{DTYPE_VCC_ENABLE, VCC_BACKLIGHT_NAME, &lcd_bl_vcc,   0, 0, WAIT_TYPE_MS, 10},
};

static struct vcc_desc hw_lcd_scharger_bl_disable_cmds[] = {
	/* backlight disable */
	{DTYPE_VCC_DISABLE, VCC_BACKLIGHT_NAME, &lcd_bl_vcc,  0, 0, WAIT_TYPE_MS, 1},
};

/*******************************************************************************
** LCD VCC
*/
#define HW_LCD_VCC_LCDIO_NAME       "lcdio-vcc"
#define HW_LCD_VCC_LCDANALOG_NAME   "lcdanalog-vcc"

static struct regulator* hw_lcd_vcc_lcdio;
static struct regulator* hw_lcd_vcc_lcdanalog;

static struct vcc_desc hw_lcdio_vcc_init_cmds[] = {
	/* vcc get */
	{DTYPE_VCC_GET, HW_LCD_VCC_LCDIO_NAME, &hw_lcd_vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	/* io set voltage */
	{DTYPE_VCC_SET_VOLTAGE, HW_LCD_VCC_LCDIO_NAME, &hw_lcd_vcc_lcdio, 1800000, 1800000, WAIT_TYPE_MS, 0},
};

static struct vcc_desc hw_lcdanalog_vcc_init_cmds[] = {
	/* vcc get */
	{DTYPE_VCC_GET, HW_LCD_VCC_LCDANALOG_NAME, &hw_lcd_vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},
	/* vcc set voltage */
	{DTYPE_VCC_SET_VOLTAGE, HW_LCD_VCC_LCDANALOG_NAME, &hw_lcd_vcc_lcdanalog, 2800000, 2800000, WAIT_TYPE_MS, 0},
};

static struct vcc_desc hw_lcd_vcc_finit_cmds[] = {
	/* vcc put */
	{DTYPE_VCC_PUT, HW_LCD_VCC_LCDIO_NAME, &hw_lcd_vcc_lcdio, 0, 0, WAIT_TYPE_MS, 0},
	{DTYPE_VCC_PUT, HW_LCD_VCC_LCDANALOG_NAME, &hw_lcd_vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 0},
};

static struct vcc_desc hw_lcdio_vcc_enable_cmds[] = {
	/* vcc enable */
	{DTYPE_VCC_ENABLE, HW_LCD_VCC_LCDIO_NAME, &hw_lcd_vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
};

static struct vcc_desc hw_lcdanalog_vcc_enable_cmds[] = {
	/* vcc enable */
	{DTYPE_VCC_ENABLE, HW_LCD_VCC_LCDANALOG_NAME, &hw_lcd_vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
};

static struct vcc_desc hw_lcdio_vcc_disable_cmds[] = {
	/* vcc disable */
	{DTYPE_VCC_DISABLE, HW_LCD_VCC_LCDIO_NAME, &hw_lcd_vcc_lcdio, 0, 0, WAIT_TYPE_MS, 3},
};

static struct vcc_desc hw_lcdanalog_vcc_disable_cmds[] = {
	/* vcc disable */
	{DTYPE_VCC_DISABLE, HW_LCD_VCC_LCDANALOG_NAME, &hw_lcd_vcc_lcdanalog, 0, 0, WAIT_TYPE_MS, 3},
};

/*******************************************************************************
** LCD IOMUX
*/
static struct pinctrl_data pctrl;

static struct pinctrl_cmd_desc hw_lcd_pinctrl_init_cmds[] = {
	{DTYPE_PINCTRL_GET, &pctrl, 0},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
	{DTYPE_PINCTRL_STATE_GET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc hw_lcd_pinctrl_normal_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_DEFAULT},
};

static struct pinctrl_cmd_desc hw_lcd_pinctrl_lowpower_cmds[] = {
	{DTYPE_PINCTRL_SET, &pctrl, DTYPE_PINCTRL_STATE_IDLE},
};

static struct pinctrl_cmd_desc hw_lcd_pinctrl_finit_cmds[] = {
	{DTYPE_PINCTRL_PUT, &pctrl, 0},
};


/*******************************************************************************
 ** LCD GPIO
 */

#define GPIO_LCD_RESET_NAME "gpio_lcd_reset"
#define GPIO_LCD_ID0_NAME	"gpio_lcd_id0"
#define GPIO_LCD_ID1_NAME	"gpio_lcd_id1"
static uint32_t gpio_lcd_reset;
static struct gpio_desc hw_lcd_gpio_request_cmds[] = {
	/* reset */
	{
		DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0
	},
};

static struct gpio_desc hw_lcd_gpio_free_cmds[] = {
	/* reset */
	{
		DTYPE_GPIO_FREE, WAIT_TYPE_US, 100,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0
	},
};

static struct gpio_desc hw_lcd_gpio_normal_cmds[] = {
	/* reset */
	{
		DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1
	},
	{
		DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0
	},
	{
		DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 15,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 1
	},
};

static struct gpio_desc hw_lcd_gpio_lowpower_cmds[] = {
	/* reset */
	{
		DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 5,
		GPIO_LCD_RESET_NAME, &gpio_lcd_reset, 0
	},
};

static struct gpio_desc hw_lcd_gpio_id_request_cmds[] = {
	/*id0*/
	{
		DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &lcd_info.lcd_id0, 0
	},
	/*id1*/
	{
		DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &lcd_info.lcd_id1, 0
	},
};

static struct gpio_desc hw_lcd_gpio_id0_low_cmds[] = {
	{
		DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &lcd_info.lcd_id0, 0
	},
};

static struct gpio_desc hw_lcd_gpio_id0_high_cmds[] = {
	{
		DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID0_NAME, &lcd_info.lcd_id0, 1
	},
};

static struct gpio_desc hw_lcd_gpio_id1_low_cmds[] = {
	{
		DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &lcd_info.lcd_id1, 0
	},
};

static struct gpio_desc hw_lcd_gpio_id1_high_cmds[] = {
	{
		DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_LCD_ID1_NAME, &lcd_info.lcd_id1, 1
	},
};

static struct gpio_desc hw_lcd_gpio_id0_input_cmds[] = {
	{
		DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_ID0_NAME, &lcd_info.lcd_id0, 0
	},
};

static struct gpio_desc hw_lcd_gpio_id1_input_cmds[] = {
	{
		DTYPE_GPIO_INPUT, WAIT_TYPE_US, 100,
		GPIO_LCD_ID1_NAME, &lcd_info.lcd_id1, 0
	},
};

/***********************************************************
*function declaration
***********************************************************/
static int hw_lcd_parse_array_data(struct device_node* np, char* name, struct array_data* out);
static int hw_lcd_parse_dcs_cmds(struct device_node* np, char* cmd_name, struct dsi_cmd_set* cmd_set);
static int hw_lcd_parse_dts(struct device_node* np);
static int hw_lcd_info_init(struct device_node* np, struct hisi_panel_info* pinfo);
static void hw_lcd_acm_init(struct device_node* np, struct hisi_panel_info* pinfo);
static void hw_lcd_init_vcc(struct vcc_desc* cmds, int cnt);
static int hw_lcd_on(struct platform_device* pdev);
static int hw_lcd_off(struct platform_device* pdev);
static int hw_lcd_remove(struct platform_device* pdev);
static int hw_lcd_set_backlight(struct platform_device* pdev, uint32_t bl_level);
static int hw_lcd_set_fastboot(struct platform_device* pdev);
static ssize_t hw_lcd_model_show(struct platform_device* pdev,
                                 char* buf);
static ssize_t hw_lcd_cabc_mode_show(struct platform_device* pdev,
                                     char* buf);
static ssize_t hw_lcd_cabc_mode_store(struct platform_device* pdev,
                                      const char* buf, size_t count);
static ssize_t hw_lcd_check_reg_show(struct platform_device* pdev, char* buf);
static ssize_t hw_lcd_mipi_detect_show(struct platform_device* pdev, char* buf);
static ssize_t hw_lcd_hkadc_debug_show(struct platform_device* pdev, char* buf);
static ssize_t hw_lcd_hkadc_debug_store(struct platform_device* pdev,
                                        const char* buf, size_t count);
static ssize_t hw_lcd_gram_check_show(struct platform_device* pdev, char* buf);
static ssize_t hw_lcd_gram_check_store(struct platform_device* pdev,
                                       const char* buf, size_t count);
static int hw_lcd_set_display_region(struct platform_device* pdev,
                                     struct dss_rect* dirty);
static int __init hw_lcd_probe(struct platform_device* pdev);
#endif
