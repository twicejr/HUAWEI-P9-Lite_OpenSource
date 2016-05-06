
/* kernel\drivers\video\msm\lcd_hw_debug.h
 * this file is used by the driver team to change the
 * LCD init parameters by putting a config file in the mobile,
 * this function can make the LCD parameter debug easier.
 *
 * Copyright (C) 2010 HUAWEI Technology Co., ltd.
 *
 * Date: 2010/12/10
 * By genghua
 *
 */

#ifndef __HW_LCD_DEBUG__
#define __HW_LCD_DEBUG__
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/debugfs.h>
#include <linux/gpio.h>
#include "hisi_fb.h"
#include "hisi_mipi_dsi.h"
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define HW_LCD_DEBUG	1

#define HW_LCD_INIT_TEST_PARAM "/data/hw_lcd_init_param.txt"
#define HW_LCD_CONFIG_TABLE_MAX_NUM 2*PAGE_SIZE

enum cmds_type {
	LCD_DBG_MIPI_CLK = 0,
	LCD_DBG_INIT_CODE,
	LCD_DBG_PANEL_VSP_VSN,
	LCD_DBG_ESD_ENABLE,
	LCD_DBG_ESD_RECOVER_TEST,
	LCD_DBG_ESD_RESET,
	LCD_DBG_ESD_BL_ENABLE,
	LCD_DBG_ESD_BL_SET,
	LCD_DBG_ESD_CHECK_REG,
	LCD_DBG_ESD_CHECK_VALUE,
	LCD_DBG_NUM_MAX,
};

typedef struct{
	char type;
	char pstr[100];
}lcd_dbg_cmds;

struct dsi_ctrl_hdr{
	char dtype;
	char vc;
	char wait;
	char waittype;
	char dlen;
};
struct dsi_panel_cmds{
	struct dsi_cmd_desc *cmds;
	char *bp;
	int cmd_cnt;
};

struct esd_debug {
	int esd_enable;
	char esd_check_reg[8];
	char esd_reg_value[8];
	int esd_bl_enable;
	int esd_bl_set;
	int check_count;
	int esd_recover_test;
};

extern struct esd_debug g_esd_debug;
extern struct dsi_panel_cmds g_panel_cmds;
extern struct hisi_fb_data_type *hisifd_dbg ;

int hw_parse_dsi_cmds(struct dsi_panel_cmds *pcmds);
bool hw_free_dsi_cmds(struct dsi_panel_cmds *pcmds);
int lcd_debugfs_init(void);
int is_enable_initcode_debug(void);
int is_enable_mipiclk_debug(void);
int is_enable_vsp_vsn_debug(void);
int get_mipiclk_debug(void);
void lcd_debug_set_vsp_vsn(struct vcc_desc* cmds, int cnt);

#endif


