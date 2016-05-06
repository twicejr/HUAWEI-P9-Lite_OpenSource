 /* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "hisi_fb.h"
#include "hisi_overlay_utils.h"
#include <huawei_platform/log/log_jank.h>
#include "hisi_display_effect.h"
#include <linux/init.h>

#if defined (CONFIG_HUAWEI_DSM)
static struct dsm_dev dsm_lcd = {
	.name = "dsm_lcd",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = NULL,
	.buff_size = 1024,
};

struct dsm_client *lcd_dclient = NULL;
#endif

u8 color_temp_cal_buf[32] = {0};
#if 0
/dev/graphics/fb0
/sys/class/graphics/fb0
/sys/devices/platform/
#endif

static int hisi_fb_resource_initialized;
static struct platform_device *pdev_list[HISI_FB_MAX_DEV_LIST] = {0};

static int pdev_list_cnt;
struct fb_info *fbi_list[HISI_FB_MAX_FBI_LIST] = {0};
static int fbi_list_index;

struct hisi_fb_data_type *hisifd_list[HISI_FB_MAX_FBI_LIST] = {0};
static int hisifd_list_index;

#define HISI_FB_ION_CLIENT_NAME	"hisi_fb_ion"

uint32_t g_dts_resouce_ready = 0;
uint32_t g_fastboot_enable_flag = 0;
uint32_t g_fake_lcd_flag = 0;
uint32_t g_dss_base_phy = 0;
uint32_t g_dss_module_resource_initialized = 0;
uint32_t g_logo_buffer_base = 0;
uint32_t g_logo_buffer_size = 0;

uint32_t g_fastboot_already_set = 0;

struct iommu_domain* g_hisi_domain = NULL;

static char __iomem *hisifd_dss_base;
static char __iomem *hisifd_peri_crg_base;
static char __iomem *hisifd_sctrl_base;
static char __iomem *hisifd_pctrl_base;
static char __iomem *hisifd_noc_dss_base;
static char __iomem *hisifd_mmbuf_crg_base;
static char __iomem *hisifd_mmbuf_asc0_base;
#if defined(CONFIG_HISI_FB_3660)
static char __iomem *hisifd_pmctrl_base;
#endif

static uint32_t hisifd_irq_pdp;
static uint32_t hisifd_irq_sdp;
static uint32_t hisifd_irq_adp;
static uint32_t hisifd_irq_dsi0;
static uint32_t hisifd_irq_dsi1;
static uint32_t hisifd_irq_mmbuf_asc0;

#define MAX_DPE_NUM	(2)
static struct regulator_bulk_data g_dpe_regulator[MAX_DPE_NUM] =
	{{0}, {0}};

static const char *g_dss_axi_clk_name;
static const char *g_dss_pclk_dss_name;
static const char *g_dss_pri_clk_name;
static const char *g_dss_pxl0_clk_name;
static const char *g_dss_pxl1_clk_name;
static const char *g_dss_mmbuf_clk_name;
static const char *g_dss_pclk_mmbuf_clk_name;
static const char *g_dss_dphy0_ref_clk_name;
static const char *g_dss_dphy1_ref_clk_name;
static const char *g_dss_dphy0_cfg_clk_name;
static const char *g_dss_dphy1_cfg_clk_name;
static const char *g_dss_pclk_dsi0_name;
static const char *g_dss_pclk_dsi1_name;
static const char *g_dss_pclk_pctrl_name;


int g_primary_lcd_xres = 0;
int g_primary_lcd_yres = 0;
uint64_t g_pxl_clk_rate = 0;
uint8_t g_prefix_ce_support = 0;
uint8_t g_prefix_sharpness1D_support = 0;
uint8_t g_prefix_sharpness2D_support = 0;

int g_debug_enable_lcd_sleep_in = 0;

/*
** for debug, S_IRUGO
** /sys/module/hisifb/parameters
*/
unsigned hisi_fb_msg_level = 7;
module_param_named(debug_msg_level, hisi_fb_msg_level, int, 0644);
MODULE_PARM_DESC(debug_msg_level, "hisi fb msg level");

int g_debug_mmu_error = 0;
module_param_named(debug_mmu_error, g_debug_mmu_error, int, 0644);
MODULE_PARM_DESC(debug_mmu_error, "hisi mmu error debug");

int g_debug_ldi_underflow = 0;
module_param_named(debug_ldi_underflow, g_debug_ldi_underflow, int, 0644);
MODULE_PARM_DESC(debug_ldi_underflow, "hisi ldi_underflow debug");

int g_debug_ldi_underflow_clear = 1;
module_param_named(debug_ldi_underflow_clear, g_debug_ldi_underflow_clear, int, 0644);
MODULE_PARM_DESC(debug_ldi_underflow_clear, "hisi ldi_underflow_clear debug");

int g_debug_set_reg_val = 0;
module_param_named(debug_set_reg_val, g_debug_set_reg_val, int, 0644);
MODULE_PARM_DESC(debug_set_reg_val, "hisi set reg val debug");

int g_debug_online_vsync = 0;
module_param_named(debug_online_vsync, g_debug_online_vsync, int, 0644);
MODULE_PARM_DESC(debug_online_vsync, "hisi online vsync debug");

int g_debug_ovl_online_composer = 0;
module_param_named(debug_ovl_online_composer, g_debug_ovl_online_composer, int, 0644);
MODULE_PARM_DESC(debug_ovl_online_composer, "hisi overlay online composer debug");

int g_debug_ovl_online_composer_hold = 0;
module_param_named(debug_ovl_online_composer_hold, g_debug_ovl_online_composer_hold, int, 0644);
MODULE_PARM_DESC(debug_ovl_online_composer_hold, "hisi overlay online composer hold debug");

int g_debug_ovl_online_composer_return = 0;
module_param_named(debug_ovl_online_composer_return, g_debug_ovl_online_composer_return, int, 0644);
MODULE_PARM_DESC(debug_ovl_online_composer_return, "hisi overlay online composer return debug");

int g_debug_ovl_online_composer_timediff = 0;
module_param_named(debug_ovl_online_composer_timediff, g_debug_ovl_online_composer_timediff, int, 0644);
MODULE_PARM_DESC(debug_ovl_online_composer_timediff, "hisi overlay online composer timediff debug");

int g_debug_ovl_online_composer_time_threshold = 6000;  //us
module_param_named(debug_ovl_online_composer_time_threshold, g_debug_ovl_online_composer_time_threshold, int, 0644);
MODULE_PARM_DESC(debug_ovl_online_composer_time_threshold, "hisi overlay online composer time threshold debug");

int g_debug_ovl_offline_composer = 0;
module_param_named(debug_ovl_offline_composer, g_debug_ovl_offline_composer, int, 0644);
MODULE_PARM_DESC(debug_ovl_offline_composer, "hisi overlay offline composer debug");

int g_debug_ovl_block_composer = 0;
module_param_named(debug_ovl_block_composer, g_debug_ovl_block_composer, int, 0644);
MODULE_PARM_DESC(debug_ovl_block_composer, "hisi overlay block composer debug");

int g_debug_ovl_offline_composer_hold = 0;
module_param_named(debug_ovl_offline_composer_hold, g_debug_ovl_offline_composer_hold, int, 0644);
MODULE_PARM_DESC(debug_ovl_offline_composer_hold, "hisi overlay offline composer hold debug");

int g_debug_ovl_offline_composer_timediff = 0;
module_param_named(debug_ovl_offline_composer_timediff, g_debug_ovl_offline_composer_timediff, int, 0644);
MODULE_PARM_DESC(debug_ovl_offline_composer_timediff, "hisi overlay offline composer timediff debug");

int g_debug_ovl_offline_composer_time_threshold = 12000;  //us
module_param_named(debug_ovl_offline_composer_time_threshold, g_debug_ovl_offline_composer_time_threshold, int, 0644);
MODULE_PARM_DESC(debug_ovl_offline_composer_time_threshold, "hisi overlay offline composer time threshold debug");

int g_debug_ovl_offline_block_num = -1;
module_param_named(debug_ovl_offline_block_num, g_debug_ovl_offline_block_num, int, 0644);
MODULE_PARM_DESC(debug_ovl_offline_block_num, "hisi overlay offline composer block debug");

int g_debug_ovl_cmdlist = 0;
module_param_named(debug_ovl_cmdlist, g_debug_ovl_cmdlist, int, 0644);
MODULE_PARM_DESC(debug_ovl_cmdlist, "hisi overlay cmdlist debug");

int g_dump_cmdlist_content = 0;
module_param_named(dump_cmdlist_content, g_dump_cmdlist_content, int, 0644);
MODULE_PARM_DESC(dump_cmdlist_content, "hisi overlay dump cmdlist content");

int g_enable_ovl_cmdlist_online = 1;
module_param_named(enable_ovl_cmdlist_online, g_enable_ovl_cmdlist_online, int, 0644);
MODULE_PARM_DESC(enable_ovl_cmdlist_online, "hisi overlay cmdlist online enable");

int g_enable_ovl_cmdlist_offline = 1;
module_param_named(enable_ovl_cmdlist_offline, g_enable_ovl_cmdlist_offline, int, 0644);
MODULE_PARM_DESC(enable_ovl_cmdlist_offline, "hisi overlay cmdlist offline enable");

int g_rdma_stretch_threshold = RDMA_STRETCH_THRESHOLD;
module_param_named(rdma_stretch_threshold, g_rdma_stretch_threshold, int, 0644);
MODULE_PARM_DESC(rdma_stretch_threshold, "hisi rdma stretch threshold");

int g_enable_dirty_region_updt = 1;
module_param_named(enable_dirty_region_updt, g_enable_dirty_region_updt, int, 0644);
MODULE_PARM_DESC(enable_dirty_region_updt, "hisi dss dirty_region_updt enable");

int g_debug_dirty_region_updt = 0;
module_param_named(debug_dirty_region_updt, g_debug_dirty_region_updt, int, 0644);
MODULE_PARM_DESC(debug_dirty_region_updt, "hisi dss dirty_region_updt debug");

int g_enable_crc_debug = 0;
module_param_named(enable_crc_debug, g_enable_crc_debug, int, 0644);
MODULE_PARM_DESC(enable_crc_debug, "hisi dss crc debug enable");

int g_ldi_data_gate_en = 1;
module_param_named(enable_ldi_data_gate, g_ldi_data_gate_en, int, 0644);
MODULE_PARM_DESC(enable_ldi_data_gate, "hisi dss ldi data gate enable");

int g_debug_need_save_file = 0;
module_param_named(debug_need_save_file, g_debug_need_save_file, int, 0644);
MODULE_PARM_DESC(debug_need_save_file, "hisi dss debug need to save file");

int g_debug_ovl_credit_step = 0;
module_param_named(debug_ovl_credit_step, g_debug_ovl_credit_step, int, 0644);
MODULE_PARM_DESC(debug_ovl_credit_step, "hisi overlay debug_ovl_credit_step");

int g_debug_layerbuf_sync = 0;
module_param_named(debug_layerbuf_sync, g_debug_layerbuf_sync, int, 0644);
MODULE_PARM_DESC(debug_layerbuf_sync, "hisi dss debug_layerbuf_sync");

int g_enable_dss_idle = 1;
module_param_named(enable_dss_idle, g_enable_dss_idle, int, 0644);
MODULE_PARM_DESC(enable_dss_idle, "hisi dss enable_dss_idle");

int g_dss_effect_sharpness1D_en = 1;
module_param_named(dss_effect_sharpness1D_en, g_dss_effect_sharpness1D_en, int, 0644);
MODULE_PARM_DESC(dss_effect_sharpness1D_en, "hisi dss display effect sharpness1D");

int g_dss_effect_sharpness2D_en = 0;
module_param_named(dss_effect_sharpness2D_en, g_dss_effect_sharpness2D_en, int, 0644);
MODULE_PARM_DESC(dss_effect_sharpness2D_en, "hisi dss display effect sharpness2D");

int g_dss_effect_acm_ce_en = 1;
module_param_named(dss_effect_acm_ce_en, g_dss_effect_acm_ce_en, int, 0644);
MODULE_PARM_DESC(dss_effect_acm_ce_en, "hisi dss display effect acm ce");

unsigned int g_dss_smmu_outstanding = DSS_SMMU_OUTSTANDING_VAL + 1;
module_param_named(dss_smmu_outstanding, g_dss_smmu_outstanding, int, 0644);
MODULE_PARM_DESC(dss_smmu_outstanding, "hisi dss smmu outstanding");

int g_debug_dump_mmbuf = 0;
module_param_named(debug_dump_mmbuf, g_debug_dump_mmbuf, int, 0644);
MODULE_PARM_DESC(debug_dump_mmbuf, "hisi dump mmbuf debug");

uint32_t g_underflow_stop_perf_stat = 0;
module_param_named(underflow_stop_perf, g_underflow_stop_perf_stat, int, 0600);
MODULE_PARM_DESC(underflow_stop_perf, "hisi underflow stop perf stat");


int g_err_status = 0;


/******************************************************************************
** FUNCTIONS PROTOTYPES
*/
static int hisi_fb_register(struct hisi_fb_data_type *hisifd);

static int hisi_fb_open(struct fb_info *info, int user);
static int hisi_fb_release(struct fb_info *info, int user);
static int hisi_fb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info);
static int hisi_fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info);
static int hisi_fb_set_par(struct fb_info *info);
static int hisi_fb_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg);
#ifndef CONFIG_HISI_FB_HEAP_CARVEOUT_USED
static int hisi_fb_mmap(struct fb_info *info, struct vm_area_struct * vma);
#endif

static int hisi_fb_suspend_sub(struct hisi_fb_data_type *hisifd);
static int hisi_fb_resume_sub(struct hisi_fb_data_type *hisifd);
#ifdef CONFIG_HAS_EARLYSUSPEND
static void hisifb_early_suspend(struct early_suspend *h);
static void hisifb_early_resume(struct early_suspend *h);
#endif

#ifdef CONFIG_PM_RUNTIME
static void hisifb_pm_runtime_get(struct hisi_fb_data_type *hisifd);
static void hisifb_pm_runtime_put(struct hisi_fb_data_type *hisifd);
static void hisifb_pm_runtime_register(struct platform_device *pdev);
static void hisifb_pm_runtime_unregister(struct platform_device *pdev);
#endif


/*******************************************************************************
**
*/
struct platform_device *hisi_fb_add_device(struct platform_device *pdev)
{
	struct hisi_fb_panel_data *pdata = NULL;
	struct platform_device *this_dev = NULL;
	struct fb_info *fbi = NULL;
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t type = 0;
	uint32_t id = 0;

	BUG_ON(pdev == NULL);
	pdata = dev_get_platdata(&pdev->dev);
	BUG_ON(pdata == NULL);

	if (fbi_list_index >= HISI_FB_MAX_FBI_LIST) {
		HISI_FB_ERR("no more framebuffer info list!\n");
		return NULL;
	}

	id = pdev->id;
	type = pdata->panel_info->type;

	/* alloc panel device data */
	this_dev = hisi_fb_device_alloc(pdata, type, id);
	if (!this_dev) {
		HISI_FB_ERR("failed to hisi_fb_device_alloc!\n");
		return NULL;
	}

	/* alloc framebuffer info + par data */
	fbi = framebuffer_alloc(sizeof(struct hisi_fb_data_type), NULL);
	if (fbi == NULL) {
		HISI_FB_ERR("can't alloc framebuffer info data!\n");
		platform_device_put(this_dev);
		return NULL;
	}

	hisifd = (struct hisi_fb_data_type *)fbi->par;
	memset(hisifd, 0, sizeof(struct hisi_fb_data_type));
	hisifd->fbi = fbi;

	hisifd->fb_imgType = HISI_FB_PIXEL_FORMAT_BGRA_8888;
	hisifd->index = fbi_list_index;
	hisifd->dss_base = hisifd_dss_base;
	hisifd->peri_crg_base = hisifd_peri_crg_base;
	hisifd->sctrl_base = hisifd_sctrl_base;
	hisifd->pctrl_base = hisifd_pctrl_base;
	hisifd->noc_dss_base = hisifd_noc_dss_base;
	hisifd->mmbuf_crg_base = hisifd_mmbuf_crg_base;
	hisifd->mmbuf_asc0_base = hisifd_mmbuf_asc0_base;
#if defined(CONFIG_HISI_FB_3660)
	hisifd->pmctrl_base = hisifd_pmctrl_base;
#endif
	hisifd->mipi_dsi0_base = hisifd->dss_base + DSS_MIPI_DSI0_OFFSET;
	hisifd->mipi_dsi1_base = hisifd->dss_base + DSS_MIPI_DSI1_OFFSET;

	hisifd->dss_base_phy = g_dss_base_phy;

	hisifd->dss_axi_clk_name = g_dss_axi_clk_name;
	hisifd->dss_pclk_dss_name = g_dss_pclk_dss_name;
	hisifd->dss_pri_clk_name = g_dss_pri_clk_name;
	hisifd->dss_pxl0_clk_name = g_dss_pxl0_clk_name;
	hisifd->dss_pxl1_clk_name = g_dss_pxl1_clk_name;
	hisifd->dss_mmbuf_clk_name = g_dss_mmbuf_clk_name;
	hisifd->dss_pclk_mmbuf_name = g_dss_pclk_mmbuf_clk_name;
	hisifd->dss_dphy0_ref_clk_name = g_dss_dphy0_ref_clk_name;
	hisifd->dss_dphy1_ref_clk_name = g_dss_dphy1_ref_clk_name;
	hisifd->dss_dphy0_cfg_clk_name = g_dss_dphy0_cfg_clk_name;
	hisifd->dss_dphy1_cfg_clk_name = g_dss_dphy1_cfg_clk_name;
	hisifd->dss_pclk_dsi0_name = g_dss_pclk_dsi0_name;
	hisifd->dss_pclk_dsi1_name = g_dss_pclk_dsi1_name;
	hisifd->dss_pclk_pctrl_name = g_dss_pclk_pctrl_name;

	hisifd->dsi0_irq = hisifd_irq_dsi0;
	hisifd->dsi1_irq = hisifd_irq_dsi1;
	hisifd->mmbuf_asc0_irq = hisifd_irq_mmbuf_asc0;
	if (hisifd->index == PRIMARY_PANEL_IDX) {
		hisifd->fb_num = HISI_FB0_NUM;
		hisifd->dpe_irq = hisifd_irq_pdp;
		hisifd->dpe_regulator = &(g_dpe_regulator[0]);
		hisifd->mmbuf_regulator = &(g_dpe_regulator[1]);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		hisifd->fb_num = HISI_FB1_NUM;
		hisifd->dpe_irq = hisifd_irq_sdp;
		hisifd->dpe_regulator = &(g_dpe_regulator[0]);
		hisifd->mmbuf_regulator = &(g_dpe_regulator[1]);
	} else if (hisifd->index == AUXILIARY_PANEL_IDX) {
		hisifd->fb_num = HISI_FB2_NUM;
		hisifd->dpe_irq = hisifd_irq_adp;
		hisifd->dpe_regulator = &(g_dpe_regulator[0]);
		hisifd->mmbuf_regulator = &(g_dpe_regulator[1]);
	} else {
		HISI_FB_ERR("fb%d not support now!\n", hisifd->index);
		platform_device_put(this_dev);
		framebuffer_release(fbi);
		return NULL;
	}

	/* link to the latest pdev */
	hisifd->pdev = this_dev;

	hisifd_list[hisifd_list_index++] = hisifd;
	fbi_list[fbi_list_index++] = fbi;

	 /* get/set panel info */
	memcpy(&hisifd->panel_info, pdata->panel_info, sizeof(struct hisi_panel_info));

	/* set driver data */
	platform_set_drvdata(this_dev, hisifd);

	if (platform_device_add(this_dev)) {
		HISI_FB_ERR("failed to platform_device_add!\n");
		framebuffer_release(fbi);
		platform_device_put(this_dev);
		hisifd_list_index--;
		fbi_list_index--;
		return NULL;
	}

	return this_dev;
}

int hisi_fb_blank_sub(int blank_mode, struct fb_info *info)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;
	int curr_pwr_state = 0;

	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);

	down(&hisifd->blank_sem);
	down(&hisifd->blank_sem0);
	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		if (!hisifd->panel_power_on) {
			ret = hisifd->on_fnc(hisifd);
			if (ret == 0) {
				hisifd->panel_power_on = true;
			}
		}
		break;

	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_NORMAL:
	case FB_BLANK_POWERDOWN:
	default:
		if (hisifd->panel_power_on) {
			if (hisifd->secure_ctrl.secure_status == DSS_SEC_RUNNING) {
				hisifd->secure_ctrl.secure_blank_flag = 1;
				break;
			}

			curr_pwr_state = hisifd->panel_power_on;
			down(&hisifd->brightness_esd_sem);
			hisifd->panel_power_on = false;
			up(&hisifd->brightness_esd_sem);

			if (hisifd->bl_cancel) {
				hisifd->bl_cancel(hisifd);
			}

			ret = hisifd->off_fnc(hisifd);
			if (ret)
				hisifd->panel_power_on = curr_pwr_state;

			if(hisifd->buf_sync_suspend)
				hisifd->buf_sync_suspend(hisifd);
		}
		break;
	}
	up(&hisifd->blank_sem);
	up(&hisifd->blank_sem0);

	return ret;
}

int fastboot_set_needed = 0;

static bool hisi_fb_set_fastboot_needed(struct fb_info *info)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);

	if (fastboot_set_needed == 1) {
		hisifb_ctrl_fastboot(hisifd);

		hisifd->panel_power_on = true;
		if (info->screen_base && (info->fix.smem_len > 0))
			memset(info->screen_base, 0x0, info->fix.smem_len);

		fastboot_set_needed = 0;
		return true;
	}

	return false;
}

static int hisi_fb_open_sub(struct fb_info *info)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;
	bool needed = false;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);

	if (hisifd->set_fastboot_fnc) {
		needed = hisifd->set_fastboot_fnc(info);
	}

	if (!needed) {
		ret = hisi_fb_blank_sub(FB_BLANK_UNBLANK, info);
		if (ret != 0) {
			HISI_FB_ERR("can't turn on display!\n");
			return ret;
		}
	}

	return 0;
}

static int hisi_fb_release_sub(struct fb_info *info)
{
	int ret = 0;

	BUG_ON(info == NULL);

	ret = hisi_fb_blank_sub(FB_BLANK_POWERDOWN, info);
	if (ret != 0) {
		HISI_FB_ERR("can't turn off display!\n");
		return ret;
	}

	return 0;
}


/*******************************************************************************
**
*/
static int hisi_fb_blank(int blank_mode, struct fb_info *info)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	pinfo = &(hisifd->panel_info);

	if (hisifd->panel_info.fake_hdmi && (hisifd->index == EXTERNAL_PANEL_IDX)) {
		HISI_FB_INFO("it is fake, blank it fail \n");
		return -EINVAL;
	}

#if 0
	if (blank_mode == FB_BLANK_POWERDOWN) {
		struct fb_event event;
		event.info = info;
		event.data = &blank_mode;
		fb_notifier_call_chain(FB_EVENT_BLANK, &event);
	}
#endif

	if (hisifd->index == AUXILIARY_PANEL_IDX) {
		HISI_FB_DEBUG("fb%d, blank_mode(%d) +.\n", hisifd->index, blank_mode);
	} else {
		HISI_FB_INFO("fb%d, blank_mode(%d) +.\n", hisifd->index, blank_mode);
	}

	if (FB_BLANK_UNBLANK == blank_mode) {
		if (hisifd->secure_ctrl.secure_blank_flag && hisifd->panel_power_on) {
			// wait for blank
			HISI_FB_INFO(" wait for tui blank \n");
			while (hisifd->panel_power_on) mdelay(1);
		}
	}

	ret = hisi_fb_blank_sub(blank_mode, info);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, blank_mode(%d) failed!\n", hisifd->index, blank_mode);
		return ret;
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		if (pinfo->acm_ce_support || pinfo->prefix_ce_support) {
			if (blank_mode == FB_BLANK_UNBLANK) {
				HISI_FB_INFO("[effect] blank_mode is FB_BLANK_UNBLANK, call ce_service_init\n");
				hisifb_ce_service_init();
			} else {
				HISI_FB_INFO("[effect] blank_mode is FB_BLANK_POWERDOWN, call ce_service_deinit\n");
				hisifb_ce_service_deinit();
			}
		}
	}

	if (hisifd->index == AUXILIARY_PANEL_IDX) {
		HISI_FB_DEBUG("fb%d, blank_mode(%d) -.\n", hisifd->index, blank_mode);
	} else {
		HISI_FB_INFO("fb%d, blank_mode(%d) -.\n", hisifd->index, blank_mode);
	}

	return 0;
}

static int hisi_fb_open(struct fb_info *info, int user)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (hisifd->panel_info.fake_hdmi && (hisifd->index == EXTERNAL_PANEL_IDX)) {
		HISI_FB_INFO("fb%d, is fake, open it fail \n", hisifd->index);
		return -EINVAL;
	}

	if (!hisifd->ref_cnt) {
		HISI_FB_DEBUG("fb%d, +!\n", hisifd->index);
		if (hisifd->open_sub_fnc) {
			LOG_JANK_D(JLID_KERNEL_LCD_OPEN, "%s", "JL_KERNEL_LCD_OPEN 3650");
			ret = hisifd->open_sub_fnc(info);
		}
		HISI_FB_DEBUG("fb%d, -!\n", hisifd->index);
	}

	hisifd->ref_cnt++;

	return ret;
}

static int hisi_fb_release(struct fb_info *info, int user)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (hisifd->panel_info.fake_hdmi && (hisifd->index == EXTERNAL_PANEL_IDX)) {
		HISI_FB_INFO("fb%d, is fake, release it fail \n", hisifd->index);
		return -EINVAL;
	}

	if (!hisifd->ref_cnt) {
		HISI_FB_INFO("try to close unopened fb%d!\n", hisifd->index);
		return -EINVAL;
	}

	hisifd->ref_cnt--;

	if (!hisifd->ref_cnt) {
		HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
		if (hisifd->release_sub_fnc) {
			ret = hisifd->release_sub_fnc(info);
		}
		HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

		if (hisifd->index == PRIMARY_PANEL_IDX) {
			if (hisifd->fb_mem_free_flag)
				hisifb_free_fb_buffer(hisifd);
		}
	}

//	if (hisifd->pm_runtime_put)
//		hisifd->pm_runtime_put(hisifd);

	return ret;
}

static int hisi_fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	if (var->rotate != FB_ROTATE_UR) {
		HISI_FB_ERR("error rotate %d!\n", var->rotate);
		return -EINVAL;
	}

	if (var->grayscale != info->var.grayscale) {
		HISI_FB_DEBUG("error grayscale %d!\n", var->grayscale);
		return -EINVAL;
	}

	if ((var->xres_virtual <= 0) || (var->yres_virtual <= 0)) {
		HISI_FB_ERR("xres_virtual=%d yres_virtual=%d out of range!",
			var->xres_virtual, var->yres_virtual);
		return -EINVAL;
	}

#if 0
	if (info->fix.smem_len <
		(hisifb_line_length(hisifd->index, var->xres_virtual, (var->bits_per_pixel >> 3)) *
		var->yres_virtual)) {
		HISI_FB_ERR("fb%d smem_len=%d is out of range!\n", hisifd->index, info->fix.smem_len);
		return -EINVAL;
	}
#endif

	if ((var->xres == 0) || (var->yres == 0)) {
		HISI_FB_ERR("xres=%d, yres=%d is invalid!\n", var->xres, var->yres);
		return -EINVAL;
	}

	if (var->xoffset > (var->xres_virtual - var->xres)) {
		HISI_FB_ERR("xoffset=%d(xres_virtual=%d, xres=%d) out of range!\n",
			var->xoffset, var->xres_virtual, var->xres);
		return -EINVAL;
	}

	if (var->yoffset > (var->yres_virtual - var->yres)) {
		HISI_FB_ERR("yoffset=%d(yres_virtual=%d, yres=%d) out of range!\n",
			var->yoffset, var->yres_virtual, var->yres);
		return -EINVAL;
	}

	return 0;
}

static int hisi_fb_set_par(struct fb_info *info)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct fb_var_screeninfo *var = NULL;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}

	var = &info->var;

	hisifd->fbi->fix.line_length = hisifb_line_length(hisifd->index, var->xres_virtual,
		var->bits_per_pixel >> 3);

	return 0;
}

static int hisi_fb_pan_display(struct fb_var_screeninfo *var,
	struct fb_info *info)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == var || NULL == info) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL ==  hisifd) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	down(&hisifd->blank_sem);

	if (!hisifd->panel_power_on) {
		HISI_FB_INFO("fb%d, panel power off!\n", hisifd->index);
		ret = -EPERM;
		goto err_out;
	}

	if (var->xoffset > (info->var.xres_virtual - info->var.xres)) {
		ret = -EINVAL;
		goto err_out;
	}

	if (var->yoffset > (info->var.yres_virtual - info->var.yres)) {
		ret = -EINVAL;
		goto err_out;
	}

	if (info->fix.xpanstep)
		info->var.xoffset =
		(var->xoffset / info->fix.xpanstep) * info->fix.xpanstep;

	if (info->fix.ypanstep)
		info->var.yoffset =
		(var->yoffset / info->fix.ypanstep) * info->fix.ypanstep;

	if (hisifd->pan_display_fnc)
		hisifd->pan_display_fnc(hisifd);
	else
		HISI_FB_ERR("fb%d pan_display_fnc not set!\n", hisifd->index);

	up(&hisifd->blank_sem);

	if (hisifd->bl_update) {
		hisifd->bl_update(hisifd);
	}

	return ret;

err_out:
	up(&hisifd->blank_sem);
	return 0;
}

static int hisifb_lcd_dirty_region_info_get(struct fb_info *info, void __user *argp)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	if (copy_to_user(argp, &(hisifd->panel_info.dirty_region_info),
		sizeof(struct lcd_dirty_region_info))) {
		HISI_FB_ERR("copy to user fail");
		return -EFAULT;
	}

	return 0;
}

static int hisifb_dirty_region_updt_set(struct fb_info *info, void __user *argp)
{
	int enable = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);

	if (g_enable_dirty_region_updt
		&& hisifd->panel_info.dirty_region_updt_support
		&& !hisifd->sbl_enable
		&& !hisifd->color_temperature_flag
		&& hisifd->ce_ctrl.ctrl_enabled != 1
		&& (DSS_SEC_DISABLE == hisifd->secure_ctrl.secure_event)) {
		enable = 1;
	}

	hisifd->dirty_region_updt_enable = enable;

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	if (copy_to_user(argp, &enable, sizeof(enable))) {
		HISI_FB_ERR("copy to user fail");
		return -EFAULT;
	}

	return 0;
}

static int hisifb_idle_is_allowed(struct fb_info *info, void __user *argp)
{
	int is_allowed = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);

	is_allowed = (hisifd->frame_update_flag == 1) ? 0 : 1;

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer\n");
		return -EINVAL;
	}
	if (copy_to_user(argp, &is_allowed, sizeof(is_allowed))) {
		HISI_FB_ERR("copy to user fail");
		return -EFAULT;
	}

	return 0;
}

static int hisifb_dss_mmbuf_alloc(struct fb_info *info, void __user *argp)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_fb_panel_data *pdata = NULL;
	dss_mmbuf_t mmbuf_info;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);
	pdata = dev_get_platdata(&hisifd->pdev->dev);
	BUG_ON(pdata == NULL);

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	ret = copy_from_user(&mmbuf_info, argp, sizeof(dss_mmbuf_t));
	if (ret) {
		HISI_FB_ERR("fb%d, copy for user failed!ret=%d.", hisifd->index, ret);
		ret = -EINVAL;
		goto err_out;
	}

	if (mmbuf_info.size <= 0 || mmbuf_info.size > MMBUF_SIZE_MAX ) {
		HISI_FB_ERR("fb%d, mmbuf size is invalid. size : %d", hisifd->index, mmbuf_info.size);
		ret = -EINVAL;
		goto err_out;
	}

	mmbuf_info.addr = hisi_dss_mmbuf_alloc(hisifd->mmbuf_gen_pool, mmbuf_info.size);
	if (mmbuf_info.addr < MMBUF_BASE) {
		mmbuf_info.addr = 0;
	}

	ret = copy_to_user(argp, &mmbuf_info, sizeof(dss_mmbuf_t));
	if (ret) {
		HISI_FB_ERR("fb%d, copy to user failed!ret=%d.", hisifd->index, ret);
		hisi_dss_mmbuf_free(hisifd->mmbuf_gen_pool, mmbuf_info.addr, mmbuf_info.size);
		ret = -EFAULT;
		goto err_out;
	}

	return 0;

err_out:
	return ret;
}

static int hisifb_dss_mmbuf_free(struct fb_info *info, void __user *argp)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_fb_panel_data *pdata = NULL;
	dss_mmbuf_t mmbuf_info;

	BUG_ON(info == NULL);
	hisifd = (struct hisi_fb_data_type *)info->par;
	BUG_ON(hisifd == NULL);
	pdata = dev_get_platdata(&hisifd->pdev->dev);
	BUG_ON(pdata == NULL);

#ifdef CONFIG_DSS_MMBUF_FENCE_USED
	return 0;
#endif
	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}

	ret = copy_from_user(&mmbuf_info, argp, sizeof(dss_mmbuf_t));
	if (ret) {
		HISI_FB_ERR("fb%d, copy for user failed!ret=%d.", hisifd->index, ret);
		ret = -EINVAL;
		goto err_out;
	}

	if ((mmbuf_info.addr <= 0) || (mmbuf_info.size <= 0)) {
		HISI_FB_ERR("fb%d, addr=0x%x, size=%d is invalid!\n",
			hisifd->index, mmbuf_info.addr, mmbuf_info.size);
		ret = -EINVAL;
		goto err_out;
	}

	hisi_dss_mmbuf_free(hisifd->mmbuf_gen_pool, mmbuf_info.addr, mmbuf_info.size);

	return 0;

err_out:
	return ret;
}

static int hisifb_dss_get_platform_type(struct fb_info *info, void __user *argp)
{
	int type;
	int ret = 0;

	type = HISIFB_DSS_PLATFORM_TYPE;

	if (NULL == argp) {
		HISI_FB_ERR("NULL Pointer!\n");
		return -EINVAL;
	}
	ret = copy_to_user(argp, &type, sizeof(type));
	if (ret) {
		HISI_FB_ERR("copy to user failed! ret=%d.", ret);
		ret = -EFAULT;
	}

	return ret;
}

static int hisi_fb_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg)
{
	int ret = -ENOSYS;
	struct hisi_fb_data_type *hisifd = NULL;
	void __user *argp = (void __user *)arg;
	//sigset_t setmask;
	//sigset_t oldmask;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer");
		return -EINVAL;
	}

	//sigemptyset(&setmask);
	//sigaddset(&setmask, SIGSTOP);
	//sigprocmask(SIG_SETMASK, &setmask, &oldmask);

	switch (cmd) {
	case HISIFB_VSYNC_CTRL:
		if (hisifd->vsync_ctrl_fnc) {
			ret = hisifd->vsync_ctrl_fnc(info, argp);
		}
		break;

	case HISIFB_IDLE_IS_ALLOWED:
		ret = hisifb_idle_is_allowed(info, argp);
		break;

	case HISIFB_DSS_CLK_RATE_SET:
		ret = hisifb_ctrl_dss_clk_rate(info, argp);
		break;
#if 0
	case HISIFB_PIXCLK_RATE_SET:
		ret = hisifb_ctrl_pixclk_rate(info, argp);
		break;
#endif
	case HISIFB_LCD_DIRTY_REGION_INFO_GET:
		ret = hisifb_lcd_dirty_region_info_get(info, argp);
		break;
	case HISIFB_DIRTY_REGION_UPDT_SET:
		ret = hisifb_dirty_region_updt_set(info, argp);
		break;

	case HISIFB_DSS_MMBUF_ALLOC:
		ret = hisifb_dss_mmbuf_alloc(info, argp);
		break;
	case HISIFB_DSS_MMBUF_FREE:
		ret = hisifb_dss_mmbuf_free(info, argp);
		break;
	case HISIFB_PLATFORM_TYPE_GET:
		ret = hisifb_dss_get_platform_type(info, argp);
		break;

	case HISIFB_CE_SUPPORT_GET:
		ret = hisifb_ce_service_get_support(info, argp);
		break;
	case HISIFB_CE_SERVICE_LIMIT_GET:
		ret = hisifb_ce_service_get_limit(info, argp);
		break;
	case HISIFB_CE_HIST_GET:
		unlock_fb_info(info);
		ret = hisifb_ce_service_get_hist(argp);
		lock_fb_info(info);
		break;
	case HISIFB_CE_LUT_SET:
		ret = hisifb_ce_service_set_lut(info, argp);
		break;

	default:
		if (hisifd->ov_ioctl_handler)
			ret = hisifd->ov_ioctl_handler(hisifd, cmd, argp);
		break;
	}

	//sigprocmask(SIG_SETMASK, &oldmask, NULL);

	if (ret == -ENOSYS)
		HISI_FB_ERR("unsupported ioctl (%x)\n", cmd);

	return ret;
}

#ifndef CONFIG_HISI_FB_HEAP_CARVEOUT_USED
static int hisi_fb_mmap(struct fb_info *info, struct vm_area_struct * vma)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct sg_table *table = NULL;
	struct scatterlist *sg = NULL;
	struct page *page = NULL;
	unsigned long remainder = 0;
	unsigned long len = 0;
	unsigned long addr = 0;
	unsigned long offset = 0;
	int i = 0;
	int ret = 0;

	if (NULL == info) {
		HISI_FB_ERR("NULL Pointer");
		return -EINVAL;
	}

	hisifd = (struct hisi_fb_data_type *)info->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer");
		return -EINVAL;
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		if (hisifd->fb_mem_free_flag) {
			if (!hisifb_alloc_fb_buffer(hisifd)) {
				HISI_FB_ERR("fb%d, hisifb_alloc_buffer failed!\n", hisifd->index);
				return -ENOMEM;
			}
		}
	} else {
		HISI_FB_ERR("fb%d, no fb buffer!\n", hisifd->index);
		return -EFAULT;;
	}

	table = ion_sg_table(hisifd->ion_client, hisifd->ion_handle);
	BUG_ON(table == NULL);

	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	addr = vma->vm_start;
	offset = vma->vm_pgoff * PAGE_SIZE;

	for_each_sg(table->sgl, sg, table->nents, i) {
		page = sg_page(sg);
		remainder = vma->vm_end - addr;
		len = sg->length;

		if (offset >= sg->length) {
			offset -= sg->length;
			continue;
		} else if (offset) {
			page += offset / PAGE_SIZE;
			len = sg->length - offset;
			offset = 0;
		}
		len = min(len, remainder);
		ret = remap_pfn_range(vma, addr, page_to_pfn(page), len,
			vma->vm_page_prot);
		if (ret != 0) {
			HISI_FB_ERR("fb%d, failed to remap_pfn_range! ret=%d\n", hisifd->index, ret);
		}

		addr += len;
		if (addr >= vma->vm_end)
			return 0;
	}

	return 0;
}
#endif

unsigned long hisifb_alloc_fb_buffer(struct hisi_fb_data_type *hisifd)
{
	struct fb_info *fbi = NULL;
	struct ion_client *client = NULL;
	struct ion_handle *handle = NULL;
	size_t buf_len = 0;
	unsigned long buf_addr = 0;

	BUG_ON(hisifd == NULL);
	fbi = hisifd->fbi;
	BUG_ON(fbi == NULL);

	if (hisifd->ion_handle != NULL)
		return fbi->fix.smem_start;

	client = hisifd->ion_client;
	if (IS_ERR_OR_NULL(client)) {
		HISI_FB_ERR("failed to create ion client!\n");
		goto err_return;
	}

	buf_len = fbi->fix.smem_len;

#ifdef CONFIG_HISI_FB_HEAP_CARVEOUT_USED
	handle = ion_alloc(client, buf_len, PAGE_SIZE, ION_HEAP(ION_GRALLOC_HEAP_ID), 0);
#else
	handle = ion_alloc(client, buf_len, PAGE_SIZE, ION_HEAP(ION_SYSTEM_HEAP_ID), 0);
#endif
	if (IS_ERR_OR_NULL(handle)) {
		HISI_FB_ERR("failed to ion_alloc!\n");
		goto err_return;
	}

	fbi->screen_base = ion_map_kernel(client, handle);
	if (!fbi->screen_base) {
		HISI_FB_ERR("failed to ion_map_kernel!\n");
		goto err_ion_map;
	}

#ifdef CONFIG_HISI_FB_HEAP_CARVEOUT_USED
	if (ion_phys(client, handle, &buf_addr, &buf_len) < 0) {
		HISI_FB_ERR("failed to get ion phys!\n");
		goto err_ion_get_addr;
	}
#else
	if (ion_map_iommu(client, handle, &(hisifd->iommu_format))) {
		HISI_FB_ERR("failed to ion_map_iommu!\n");
		goto err_ion_get_addr;
	}

	buf_addr = hisifd->iommu_format.iova_start;
#endif

	fbi->fix.smem_start = buf_addr;
	fbi->screen_size = fbi->fix.smem_len;
	//memset(fbi->screen_base, 0xFF, fbi->screen_size);

	hisifd->ion_handle = handle;

	return buf_addr;

err_ion_get_addr:
	ion_unmap_kernel(hisifd->ion_client, handle);
err_ion_map:
	ion_free(hisifd->ion_client, handle);
err_return:
	return 0;
}

void hisifb_free_fb_buffer(struct hisi_fb_data_type *hisifd)
{
	struct fb_info *fbi = NULL;

	BUG_ON(hisifd == NULL);
	fbi = hisifd->fbi;
	BUG_ON(fbi == NULL);

	if (hisifd->ion_client != NULL &&
		hisifd->ion_handle != NULL) {
	#ifndef CONFIG_HISI_FB_HEAP_CARVEOUT_USED
		ion_unmap_iommu(hisifd->ion_client, hisifd->ion_handle);
	#endif
		ion_unmap_kernel(hisifd->ion_client, hisifd->ion_handle);
		ion_free(hisifd->ion_client, hisifd->ion_handle);
		hisifd->ion_handle = NULL;

		fbi->screen_base = 0;
		fbi->fix.smem_start = 0;
	}
}

void hisifb_free_logo_buffer(struct hisi_fb_data_type *hisifd)
{
	int i;
	struct fb_info *fbi = NULL;
	uint32_t logo_buffer_base_temp = 0;

	BUG_ON(hisifd == NULL);
	fbi = hisifd->fbi;
	BUG_ON(fbi == NULL);

	logo_buffer_base_temp = g_logo_buffer_base;
	for (i = 0; i < (g_logo_buffer_size / PAGE_SIZE); i++) {
		free_reserved_page(phys_to_page(logo_buffer_base_temp));
	#ifdef CONFIG_HIGHMEM
		if (PageHighMem(phys_to_page(logo_buffer_base_temp)))
			totalhigh_pages += 1;
	#endif
		logo_buffer_base_temp += PAGE_SIZE;
	}
	memblock_free(g_logo_buffer_base, g_logo_buffer_size);

	g_logo_buffer_size = 0;
	g_logo_buffer_base = 0;
}

/*******************************************************************************
** fb sys fs
*/
static void hisifb_sysfs_init(struct hisi_fb_data_type *hisifd)
{
	int i = 0;

	BUG_ON(hisifd == NULL);

	hisifd->sysfs_index = 0;
	for (i = 0; i < HISI_FB_SYSFS_ATTRS_NUM; i++) {
		hisifd->sysfs_attrs[i] = NULL;
	}
	hisifd->sysfs_attr_group.attrs = hisifd->sysfs_attrs;
}

static void hisifb_sysfs_attrs_append(struct hisi_fb_data_type *hisifd, struct attribute *attr)
{
	BUG_ON(hisifd == NULL);
	BUG_ON(attr == NULL);

	if (hisifd->sysfs_index >= HISI_FB_SYSFS_ATTRS_NUM) {
		HISI_FB_ERR("fb%d, sysfs_atts_num(%d) is out of range(%d)!\n",
			hisifd->index, hisifd->sysfs_index, HISI_FB_SYSFS_ATTRS_NUM);
		BUG_ON(1);
		return ;
	}

	hisifd->sysfs_attrs[hisifd->sysfs_index] = attr;
	hisifd->sysfs_index++;
}

static int hisifb_sysfs_create(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	ret = sysfs_create_group(&hisifd->fbi->dev->kobj, &(hisifd->sysfs_attr_group));
	if (ret) {
		HISI_FB_ERR("fb%d sysfs group creation failed, error=%d!\n",
			hisifd->index, ret);
	}

	return ret;
}

static void hisifb_sysfs_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	sysfs_remove_group(&hisifd->fbi->dev->kobj, &(hisifd->sysfs_attr_group));

	hisifb_sysfs_init(hisifd);
}


/*******************************************************************************
**
*/
#define HISI_ESD_RECOVER_MAX_COUNT	(5)
#define HISI_ESD_CHECK_MAX_COUNT	(3)

#if defined (CONFIG_HUAWEI_DSM)
int dsm_lcd_esd_recover = -1;
#endif

static void hisifb_esd_recover(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;
	uint32_t bl_level_cur = 0;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null");
		return ;
	}

	bl_level_cur = hisifd->bl_level;
	down(&hisifd->brightness_esd_sem);
	hisifb_set_backlight(hisifd, 0);
	up(&hisifd->brightness_esd_sem);

	down(&hisifd->blank_sem);
	if (!hisifd->panel_power_on) {
		HISI_FB_ERR("panel is off\n");
		up(&hisifd->blank_sem);
		return ;
	}

	hisifb_activate_vsync(hisifd);
	/*lcd panel off*/
	ret = panel_next_off(hisifd->pdev);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, blank_mode(%d) failed!\n", hisifd->index, FB_BLANK_POWERDOWN);
	}
	/*lcd panel on*/
	ret = panel_next_on(hisifd->pdev);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, blank_mode(%d) failed!\n", hisifd->index, FB_BLANK_UNBLANK);
	}
	/*cmd panel need to update frame*/
	if (is_mipi_cmd_panel(hisifd)) {
		single_frame_update(hisifd);
	}
	hisifb_deactivate_vsync(hisifd);
	up(&hisifd->blank_sem);

	/*backlight on*/
	mdelay(100);
	down(&hisifd->brightness_esd_sem);
	hisifb_set_backlight(hisifd, bl_level_cur);
	up(&hisifd->brightness_esd_sem);

	return ;
}

static void hisifb_frame_end_wq_handler(struct work_struct *work)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;
	int recover_count = 0;
	int esd_check_count = 0;

	hisifd = container_of(work, struct hisi_fb_data_type, frame_end_work);
	BUG_ON(hisifd == NULL);

	if (!hisifd->panel_info.esd_enable)
		return ;

	while (recover_count < HISI_ESD_RECOVER_MAX_COUNT) {
		if (esd_check_count < HISI_ESD_CHECK_MAX_COUNT) {
			if (DSS_SEC_RUNNING == hisifd->secure_ctrl.secure_status)
				break;

			if ((DSS_SEC_IDLE == hisifd->secure_ctrl.secure_status)
				&& (DSS_SEC_ENABLE == hisifd->secure_ctrl.secure_event))
				break;

			ret = hisifb_ctrl_esd(hisifd);
			if (ret) {
				esd_check_count++;
				HISI_FB_INFO("esd check abnormal, esd_check_count:%d!\n", esd_check_count);
			} else {
				break;
			}
		} else {
			HISI_FB_ERR("esd recover panel, recover_count:%d!\n",recover_count);
			hisifb_esd_recover(hisifd);
			esd_check_count = 0;
			recover_count++;
		#if 0
		#if defined (CONFIG_HUAWEI_DSM)
			if (dsm_lcd_esd_recover >= 0) {
				dsm_client_record(lcd_dclient,"[%s]ESD recovery count: %d.\n",
					__func__, recover_count);
				dsm_lcd_esd_recover++;
			}
		#endif
		#endif
		}
	}

	// recover count equate 5, we disable esd check function
	if (recover_count >= HISI_ESD_RECOVER_MAX_COUNT) {
		hrtimer_cancel(&hisifd->esd_hrtimer);
		hisifd->panel_info.esd_enable = 0;
		HISI_FB_ERR("esd recover %d count, disable esd function\n", HISI_ESD_RECOVER_MAX_COUNT);
	}
}

static enum hrtimer_restart hisifb_esd_hrtimer_fnc(struct hrtimer *timer)
{
	struct hisi_fb_data_type *hisifd = NULL;

	hisifd  = container_of(timer, struct hisi_fb_data_type, esd_hrtimer);
	BUG_ON(hisifd == NULL);

	if (hisifd->panel_info.esd_enable) {
		if (hisifd->frame_end_wq) {
			queue_work(hisifd->frame_end_wq, &(hisifd->frame_end_work));
		}
	}
	hrtimer_start(&hisifd->esd_hrtimer, ktime_set(ESD_CHECK_TIME_PERIOD / 1000,
		(ESD_CHECK_TIME_PERIOD % 1000) * 1000000), HRTIMER_MODE_REL);

	return HRTIMER_NORESTART;
}

/*******************************************************************************
**
*/
static struct fb_ops hisi_fb_ops = {
	.owner = THIS_MODULE,
	.fb_open = hisi_fb_open,
	.fb_release = hisi_fb_release,
	.fb_read = NULL,
	.fb_write = NULL,
	.fb_cursor = NULL,
	.fb_check_var = hisi_fb_check_var,
	.fb_set_par = hisi_fb_set_par,
	.fb_setcolreg = NULL,
	.fb_blank = hisi_fb_blank,
	.fb_pan_display = hisi_fb_pan_display,
	.fb_fillrect = NULL,
	.fb_copyarea = NULL,
	.fb_imageblit = NULL,
	.fb_rotate = NULL,
	.fb_sync = NULL,
	.fb_ioctl = hisi_fb_ioctl,
	.fb_compat_ioctl = hisi_fb_ioctl,
#ifndef CONFIG_HISI_FB_HEAP_CARVEOUT_USED
	.fb_mmap = hisi_fb_mmap,
#else
	.fb_mmap = NULL,
#endif
};

#ifdef CONFIG_HISI_FB_6250
extern int scharger_register_notifier(struct notifier_block *nb);
int hisifb_fastboot_power_on(struct notifier_block *nb,
		unsigned long event, void *data)
{
	struct hisi_fb_panel_data *pdata = NULL;
	/* primary panel */
	struct hisi_fb_data_type *hisifd = hisifd_list[PRIMARY_PANEL_IDX];
	BUG_ON(hisifd == NULL);

	pdata = (struct hisi_fb_panel_data *)hisifd->pdev->dev.platform_data;
	if (pdata && pdata->set_fastboot && !g_fastboot_already_set) {
		pdata->set_fastboot(hisifd->pdev);
		g_fastboot_already_set = 1;
	}
	return 0;
}
#endif

static int hisi_fb_register(struct hisi_fb_data_type *hisifd)
{
	int bpp = 0;
	struct hisi_panel_info *panel_info = NULL;
	struct fb_info *fbi = NULL;
	struct fb_fix_screeninfo *fix = NULL;
	struct fb_var_screeninfo *var = NULL;

	BUG_ON(hisifd == NULL);
	panel_info = &hisifd->panel_info;
	BUG_ON(panel_info == NULL);

	/*
	 * fb info initialization
	 */
	fbi = hisifd->fbi;
	fix = &fbi->fix;
	var = &fbi->var;

	fix->type_aux = 0;
	fix->visual = FB_VISUAL_TRUECOLOR;
	fix->ywrapstep = 0;
	fix->mmio_start = 0;
	fix->mmio_len = 0;
	fix->accel = FB_ACCEL_NONE;

	var->xoffset = 0;
	var->yoffset = 0;
	var->grayscale = 0;
	var->nonstd = 0;
	var->activate = FB_ACTIVATE_VBL;
	var->height = panel_info->height;
	var->width = panel_info->width;
	var->accel_flags = 0;
	var->sync = 0;
	var->rotate = 0;

	switch (hisifd->fb_imgType) {
	case HISI_FB_PIXEL_FORMAT_BGR_565:
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->xpanstep = 1;
		fix->ypanstep = 1;
		var->vmode = FB_VMODE_NONINTERLACED;

		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 11;
		var->transp.offset = 0;

		var->blue.length = 5;
		var->green.length = 6;
		var->red.length = 5;
		var->transp.length = 0;

		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		break;

	case HISI_FB_PIXEL_FORMAT_BGRX_4444:
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->xpanstep = 1;
		fix->ypanstep = 1;
		var->vmode = FB_VMODE_NONINTERLACED;

		var->blue.offset = 0;
		var->green.offset = 4;
		var->red.offset = 8;
		var->transp.offset = 0;

		var->blue.length = 4;
		var->green.length = 4;
		var->red.length = 4;
		var->transp.length = 0;

		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		break;

	case HISI_FB_PIXEL_FORMAT_BGRA_4444:
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->xpanstep = 1;
		fix->ypanstep = 1;
		var->vmode = FB_VMODE_NONINTERLACED;

		var->blue.offset = 0;
		var->green.offset = 4;
		var->red.offset = 8;
		var->transp.offset = 12;

		var->blue.length = 4;
		var->green.length = 4;
		var->red.length = 4;
		var->transp.length = 4;

		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		break;

	case HISI_FB_PIXEL_FORMAT_BGRX_5551:
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->xpanstep = 1;
		fix->ypanstep = 1;
		var->vmode = FB_VMODE_NONINTERLACED;

		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 10;
		var->transp.offset = 0;

		var->blue.length = 5;
		var->green.length = 5;
		var->red.length = 5;
		var->transp.length = 0;

		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		break;

	case HISI_FB_PIXEL_FORMAT_BGRA_5551:
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->xpanstep = 1;
		fix->ypanstep = 1;
		var->vmode = FB_VMODE_NONINTERLACED;

		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 10;
		var->transp.offset = 15;

		var->blue.length = 5;
		var->green.length = 5;
		var->red.length = 5;
		var->transp.length = 1;

		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		break;

	case HISI_FB_PIXEL_FORMAT_BGRA_8888:
		fix->type = FB_TYPE_PACKED_PIXELS;
		fix->xpanstep = 1;
		fix->ypanstep = 1;
		var->vmode = FB_VMODE_NONINTERLACED;

		var->blue.offset = 0;
		var->green.offset = 8;
		var->red.offset = 16;
		var->transp.offset = 24;

		var->blue.length = 8;
		var->green.length = 8;
		var->red.length = 8;
		var->transp.length = 8;

		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;

		bpp = 4;
		break;

	case HISI_FB_PIXEL_FORMAT_YUV_422_I:
		fix->type = FB_TYPE_INTERLEAVED_PLANES;
		fix->xpanstep = 2;
		fix->ypanstep = 1;
		var->vmode = FB_VMODE_NONINTERLACED;

		/* FIXME: R/G/B offset? */
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 11;
		var->transp.offset = 0;

		var->blue.length = 5;
		var->green.length = 6;
		var->red.length = 5;
		var->transp.length = 0;

		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;

		bpp = 2;
		break;

	default:
		HISI_FB_ERR("fb%d, unkown image type!\n", hisifd->index);
		return -EINVAL;
	}

	//for resolution update
	memset(&(hisifd->resolution_rect), 0, sizeof(dss_rect_t));
	memset(&(hisifd->res_updt_rect), 0, sizeof(dss_rect_t));

	var->xres = panel_info->xres;
	var->yres = panel_info->yres;
	var->xres_virtual = var->xres;
	var->yres_virtual = var->yres * hisifd->fb_num;
	var->bits_per_pixel = bpp * 8;

	snprintf(fix->id, sizeof(fix->id), "hisifb%d", hisifd->index);
	fix->line_length = hisifb_line_length(hisifd->index, var->xres_virtual, bpp);
	fix->smem_len = roundup(fix->line_length * var->yres_virtual, PAGE_SIZE);
	fix->smem_start = 0;

	fbi->screen_base = 0;
	fbi->fbops = &hisi_fb_ops;
	fbi->flags = FBINFO_FLAG_DEFAULT;
	fbi->pseudo_palette = NULL;

	fix->reserved[0] = is_mipi_cmd_panel(hisifd) ? 1 : 0;

	hisifd->ion_client = hisi_ion_client_create(HISI_FB_ION_CLIENT_NAME);
	if (IS_ERR_OR_NULL(hisifd->ion_client)) {
		HISI_FB_ERR("failed to create ion client!\n");
		return -ENOMEM;
	}
	hisifd->ion_handle = NULL;
	memset(&hisifd->iommu_format, 0, sizeof(struct iommu_map_format));

	if (fix->smem_len > 0) {
		if (!hisifb_alloc_fb_buffer(hisifd)) {
			HISI_FB_ERR("hisifb_alloc_buffer failed!\n");
			return -ENOMEM;
		}
	}

	hisifd->ref_cnt = 0;
	hisifd->panel_power_on = false;
	sema_init(&hisifd->blank_sem, 1);
	sema_init(&hisifd->blank_sem0, 1);
	sema_init(&hisifd->brightness_esd_sem, 1);

	hisifb_sysfs_init(hisifd);

	hisifd->on_fnc = hisifb_ctrl_on;
	hisifd->off_fnc = hisifb_ctrl_off;

	hisifd->color_temp_cal_enabled = color_temp_cal_buf[0];
	hisifd->hisi_domain = g_hisi_domain;

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		hisifd->fb_mem_free_flag = false;

		//for offline composer
		g_primary_lcd_xres = var->xres;
		g_primary_lcd_yres = var->yres;
		g_pxl_clk_rate = panel_info->pxl_clk_rate;
		g_prefix_ce_support = panel_info->prefix_ce_support;
		g_prefix_sharpness1D_support = panel_info->prefix_sharpness1D_support;
		g_prefix_sharpness2D_support = panel_info->prefix_sharpness2D_support;

		hisifd->lp_fnc = hisifb_ctrl_lp;
		if (g_fastboot_enable_flag == 1) {
			hisifd->set_fastboot_fnc = hisi_fb_set_fastboot_needed;
			fastboot_set_needed = 1;
		} else {
			hisifd->set_fastboot_fnc = NULL;
		}
		hisifd->open_sub_fnc = hisi_fb_open_sub;
		hisifd->release_sub_fnc = hisi_fb_release_sub;
		hisifd->frc_fnc = hisifb_ctrl_frc;
		hisifd->esd_fnc = hisifb_ctrl_esd;
		hisifd->sbl_ctrl_fnc = hisifb_ctrl_sbl;
		hisifd->sysfs_attrs_add_fnc = hisifb_sysfs_attrs_add;
		hisifd->sysfs_attrs_append_fnc = hisifb_sysfs_attrs_append;
		hisifd->sysfs_create_fnc = hisifb_sysfs_create;
		hisifd->sysfs_remove_fnc = hisifb_sysfs_remove;
		hisifd->mipi_dsi_bit_clk_upt_isr_handler = mipi_dsi_bit_clk_upt_isr_handler;

	#ifdef CONFIG_PM_RUNTIME
		hisifd->pm_runtime_register = hisifb_pm_runtime_register;
		hisifd->pm_runtime_unregister = hisifb_pm_runtime_unregister;
		hisifd->pm_runtime_get = hisifb_pm_runtime_get;
		hisifd->pm_runtime_put = hisifb_pm_runtime_put;
	#else
		hisifd->pm_runtime_register = NULL;
		hisifd->pm_runtime_unregister = NULL;
		hisifd->pm_runtime_get = NULL;
		hisifd->pm_runtime_put = NULL;
	#endif
		hisifd->bl_register = hisifb_backlight_register;
		hisifd->bl_unregister = hisifb_backlight_unregister;
		hisifd->bl_update = hisifb_backlight_update;
		hisifd->bl_cancel = hisifb_backlight_cancel;
		hisifd->vsync_register = hisifb_vsync_register;
		hisifd->vsync_unregister = hisifb_vsync_unregister;
		hisifd->vsync_ctrl_fnc = hisifb_vsync_ctrl;
		hisifd->vsync_isr_handler = hisifb_vsync_isr_handler;
		hisifd->buf_sync_register = hisifb_buf_sync_register;
		hisifd->buf_sync_unregister = hisifb_buf_sync_unregister;
		hisifd->buf_sync_signal = hisifb_buf_sync_signal;
		hisifd->buf_sync_suspend = hisifb_buf_sync_suspend;
	#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
		hisifd->secure_register = hisifb_secure_register;
		hisifd->secure_unregister = hisifb_secure_unregister;
	#elif defined(CONFIG_HISI_FB_3660)
		hisifd->secure_register = NULL;
		hisifd->secure_unregister = NULL;
	#endif
		if (hisifd->panel_info.esd_enable) {
			hisifd->frame_end_wq= create_singlethread_workqueue("dss_frame_end");
			if (!hisifd->frame_end_wq)
				HISI_FB_ERR("create dss frame end failed\n");
			INIT_WORK(&hisifd->frame_end_work, hisifb_frame_end_wq_handler);

			/* hrtimer for ESD timing */
			hrtimer_init(&hisifd->esd_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
			hisifd->esd_hrtimer.function = hisifb_esd_hrtimer_fnc;
				hrtimer_start(&hisifd->esd_hrtimer, ktime_set(ESD_CHECK_TIME_PERIOD / 1000,
					(ESD_CHECK_TIME_PERIOD % 1000) * 1000000), HRTIMER_MODE_REL);
		}

#if defined (CONFIG_HUAWEI_DSM)
		hisifd->dss_underflow_debug_workqueue= create_singlethread_workqueue("dss_underflow_debug");
		if (!hisifd->dss_underflow_debug_workqueue)
			HISI_FB_ERR("create dss underflow debug workqueue failed\n");
		INIT_WORK(&hisifd->dss_underflow_debug_work, dss_underflow_debug_func);
#endif
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		hisifd->fb_mem_free_flag = true;

		hisifd->lp_fnc = NULL;
		hisifd->set_fastboot_fnc = NULL;
		hisifd->open_sub_fnc = NULL;
		hisifd->release_sub_fnc = hisi_fb_release_sub;
		hisifd->frc_fnc = NULL;
		hisifd->esd_fnc = NULL;
		hisifd->sbl_ctrl_fnc = NULL;
		hisifd->sysfs_attrs_add_fnc = NULL;
		hisifd->sysfs_attrs_append_fnc = NULL;
		hisifd->sysfs_create_fnc = NULL;
		hisifd->sysfs_remove_fnc = NULL;
		hisifd->mipi_dsi_bit_clk_upt_isr_handler = NULL;

	#ifdef CONFIG_PM_RUNTIME
		hisifd->pm_runtime_register = hisifb_pm_runtime_register;
		hisifd->pm_runtime_unregister = hisifb_pm_runtime_unregister;
		hisifd->pm_runtime_get = hisifb_pm_runtime_get;
		hisifd->pm_runtime_put = hisifb_pm_runtime_put;
	#else
		hisifd->pm_runtime_register = NULL;
		hisifd->pm_runtime_unregister = NULL;
		hisifd->pm_runtime_get = NULL;
		hisifd->pm_runtime_put = NULL;
	#endif
		hisifd->bl_register = hisifb_backlight_register;
		hisifd->bl_unregister = hisifb_backlight_unregister;
		hisifd->bl_update = hisifb_backlight_update;
		hisifd->bl_cancel = hisifb_backlight_cancel;
		hisifd->vsync_register = hisifb_vsync_register;
		hisifd->vsync_unregister = hisifb_vsync_unregister;
		hisifd->vsync_ctrl_fnc = hisifb_vsync_ctrl;
		hisifd->vsync_isr_handler = hisifb_vsync_isr_handler;
		hisifd->buf_sync_register = hisifb_buf_sync_register;
		hisifd->buf_sync_unregister = hisifb_buf_sync_unregister;
		hisifd->buf_sync_signal = hisifb_buf_sync_signal;
		hisifd->buf_sync_suspend = hisifb_buf_sync_suspend;
		hisifd->secure_register = NULL;
		hisifd->secure_unregister = NULL;
	} else {
		hisifd->fb_mem_free_flag = true;

		hisifd->lp_fnc = NULL;
		hisifd->set_fastboot_fnc = NULL;
		hisifd->open_sub_fnc = NULL;
		hisifd->release_sub_fnc = NULL;
		hisifd->frc_fnc = NULL;
		hisifd->esd_fnc = NULL;
		hisifd->sbl_ctrl_fnc = NULL;
		hisifd->sysfs_attrs_add_fnc = NULL;
		hisifd->sysfs_attrs_append_fnc = NULL;
		hisifd->sysfs_create_fnc = NULL;
		hisifd->sysfs_remove_fnc = NULL;
		hisifd->mipi_dsi_bit_clk_upt_isr_handler = NULL;

		hisifd->pm_runtime_register = NULL;
		hisifd->pm_runtime_unregister = NULL;
		hisifd->pm_runtime_get = NULL;
		hisifd->pm_runtime_put = NULL;
		hisifd->bl_register = NULL;
		hisifd->bl_unregister = NULL;
		hisifd->bl_update = NULL;
		hisifd->bl_cancel = NULL;
		hisifd->vsync_register = NULL;
		hisifd->vsync_unregister = NULL;
		hisifd->vsync_ctrl_fnc = NULL;
		hisifd->vsync_isr_handler = NULL;
		hisifd->buf_sync_register = NULL;
		hisifd->buf_sync_unregister = NULL;
		hisifd->buf_sync_signal = NULL;
		hisifd->buf_sync_suspend = NULL;
		hisifd->secure_register = NULL;
		hisifd->secure_unregister = NULL;
	}

#ifdef CONFIG_HISI_FB_6250
	if (g_fastboot_enable_flag == 1) {
		hisifd->nb.notifier_call = hisifb_fastboot_power_on;
		scharger_register_notifier(&hisifd->nb);
	}
#endif

	if (hisi_overlay_init(hisifd)) {
		HISI_FB_ERR("unable to init overlay!\n");
		return -EPERM;
	}

	if (register_framebuffer(fbi) < 0) {
		HISI_FB_ERR("fb%d failed to register_framebuffer!", hisifd->index);
		return -EPERM;
	}

	if (hisifd->sysfs_attrs_add_fnc) {
		hisifd->sysfs_attrs_add_fnc(hisifd);
	}

	/* backlight register */
	if (hisifd->bl_register)
		hisifd->bl_register(hisifd->pdev);
	/* vsync register */
	if (hisifd->vsync_register)
		hisifd->vsync_register(hisifd->pdev);
	/* secure register */
	if (hisifd->secure_register)
		hisifd->secure_register(hisifd->pdev);
	/* buf_sync register */
	if (hisifd->buf_sync_register)
		hisifd->buf_sync_register(hisifd->pdev);
	/* pm runtime register */
	if (hisifd->pm_runtime_register)
		hisifd->pm_runtime_register(hisifd->pdev);
	/* fb sysfs create */
	if (hisifd->sysfs_create_fnc)
		hisifd->sysfs_create_fnc(hisifd->pdev);

	HISI_FB_INFO("FrameBuffer[%d] %dx%d size=%d bytes phy_addr=%lu virt_addr=%p "
		"is registered successfully!\n",
		hisifd->index, var->xres, var->yres, fbi->fix.smem_len,
		fix->smem_start, fbi->screen_base);

	return 0;
}


/*******************************************************************************
**
*/
static int hisi_fb_enable_iommu(struct platform_device *pdev)
{
	struct iommu_domain *hisi_domain = NULL;
	struct device *dev = NULL;

	BUG_ON(pdev == NULL);

	dev = &pdev->dev;

	/* create iommu domain */
	hisi_domain = iommu_domain_alloc(dev->bus);
	if (!hisi_domain) {
		HISI_FB_ERR("iommu_domain_alloc failed!\n");
		return -EINVAL;
	}

	iommu_attach_device(hisi_domain, dev);

	g_hisi_domain = hisi_domain;

	return 0;
}

static int hisi_fb_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct device_node *np = NULL;

	if (!hisi_fb_resource_initialized) {
		HISI_FB_DEBUG("initialized=%d, +.\n", hisi_fb_resource_initialized);

		pdev->id = 0;

		np = of_find_compatible_node(NULL, NULL, DTS_COMP_FB_NAME);
		if (!np) {
			HISI_FB_ERR("NOT FOUND device node %s!\n", DTS_COMP_FB_NAME);
			return -ENXIO;
		}

		ret = of_property_read_u32(np, "fpga_flag", &g_fpga_flag);
		if (ret) {
			HISI_FB_ERR("failed to get fpga_flag resource.\n");
			return -ENXIO;
		}
		HISI_FB_INFO("g_fpga_flag=%d.\n", g_fpga_flag);

		ret = of_property_read_u32(np, "fastboot_enable_flag", &g_fastboot_enable_flag);
		if (ret) {
			HISI_FB_ERR("failed to get fastboot_display_flag resource.\n");
			return -ENXIO;
		}
		HISI_FB_INFO("g_fastboot_enable_flag=%d.\n", g_fastboot_enable_flag);

		ret = of_property_read_u32(np, "fake_lcd_flag", &g_fake_lcd_flag);
		if (ret) {
			HISI_FB_ERR("failed to get fake_lcd_flag resource.\n");
			return -ENXIO;
		}
		HISI_FB_INFO("g_fake_lcd_flag=%d.\n", g_fake_lcd_flag);

		ret = of_property_read_u32(np, "dss_base_phy", &g_dss_base_phy);
		if (ret) {
			HISI_FB_ERR("failed to get dss_base_phy.\n");
			return -ENXIO;
		}
		HISI_FB_INFO("g_dss_base_phy=0x%x.\n", g_dss_base_phy);

		/* get irq no */
		hisifd_irq_pdp = irq_of_parse_and_map(np, 0);
		if (!hisifd_irq_pdp) {
			HISI_FB_ERR("failed to get hisifd_irq_pdp resource.\n");
			return -ENXIO;
		}

		hisifd_irq_sdp = irq_of_parse_and_map(np, 1);
		if (!hisifd_irq_sdp) {
			HISI_FB_ERR("failed to get hisifd_irq_sdp resource.\n");
			return -ENXIO;
		}

		hisifd_irq_adp = irq_of_parse_and_map(np, 2);
		if (!hisifd_irq_sdp) {
			HISI_FB_ERR("failed to get hisifd_irq_sdp resource.\n");
			return -ENXIO;
		}

		hisifd_irq_dsi0 = irq_of_parse_and_map(np, 3);
		if (!hisifd_irq_dsi0) {
			HISI_FB_ERR("failed to get hisifd_irq_dsi0 resource.\n");
			return -ENXIO;
		}

		hisifd_irq_dsi1 = irq_of_parse_and_map(np, 4);
		if (!hisifd_irq_dsi1) {
			HISI_FB_ERR("failed to get hisifd_irq_dsi1 resource.\n");
			return -ENXIO;
		}

		#ifdef CONFIG_HISI_FB_6250
		hisifd_irq_mmbuf_asc0 = irq_of_parse_and_map(np, 5);
		if (!hisifd_irq_mmbuf_asc0) {
			HISI_FB_ERR("failed to get hisifd_irq_mmbuf_asc0 resource.\n");
			return -ENXIO;
		}
		#endif
		/* get dss reg base */
		hisifd_dss_base = of_iomap(np, 0);
		if (!hisifd_dss_base) {
			HISI_FB_ERR("failed to get hisifd_dss_base resource.\n");
			return -ENXIO;
		}

		hisifd_peri_crg_base = of_iomap(np, 1);
		if (!hisifd_peri_crg_base) {
			HISI_FB_ERR("failed to get hisifd_peri_crg_base resource.\n");
			return -ENXIO;
		}

		hisifd_sctrl_base = of_iomap(np, 2);
		if (!hisifd_sctrl_base) {
			HISI_FB_ERR("failed to get hisifd_sctrl_base resource.\n");
			return -ENXIO;
		}

		hisifd_pctrl_base = of_iomap(np, 3);
		if (!hisifd_pctrl_base) {
			HISI_FB_ERR("failed to get hisifd_pctrl_base resource.\n");
			return -ENXIO;
		}

		hisifd_noc_dss_base = of_iomap(np, 4);
		if (!hisifd_noc_dss_base) {
			HISI_FB_ERR("failed to get hisifd_noc_dss_base resource.\n");
			return -ENXIO;
		}

		hisifd_mmbuf_crg_base = of_iomap(np, 5);
		if (!hisifd_mmbuf_crg_base) {
			HISI_FB_ERR("failed to get hisifd_mmbuf_crg_base resource.\n");
			return -ENXIO;
		}

	#ifdef CONFIG_HISI_FB_3660
		hisifd_pmctrl_base = of_iomap(np, 6);
		if (!hisifd_pmctrl_base) {
			HISI_FB_ERR("failed to get hisifd_pmctrl_base resource.\n");
			return -ENXIO;
		}
	#elif defined CONFIG_HISI_FB_6250
		hisifd_mmbuf_asc0_base = of_iomap(np, 6);
		if (!hisifd_mmbuf_asc0_base) {
			HISI_FB_ERR("failed to get hisifd_mmbuf_asc0_base resource.\n");
			return -ENXIO;
		}
	#endif

		/* get regulator resource */
		g_dpe_regulator[0].supply = REGULATOR_PDP_NAME;
		g_dpe_regulator[1].supply = REGULATOR_MMBUF;
		ret = devm_regulator_bulk_get(&(pdev->dev),
			ARRAY_SIZE(g_dpe_regulator), g_dpe_regulator);
		if (ret) {
			HISI_FB_ERR("failed to get regulator resource! ret=%d.\n", ret);
			return -ENXIO;
		}

		/* get dss clk resource */
		ret = of_property_read_string_index(np, "clock-names", 0, &g_dss_axi_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get axi_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 1, &g_dss_pclk_dss_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get pclk_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 2, &g_dss_pri_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get pri_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 3, &g_dss_pxl0_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get pxl0_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 4, &g_dss_pxl1_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get pxl1_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}

		ret = of_property_read_string_index(np, "clock-names", 5, &g_dss_mmbuf_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get mmbuf_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 6, &g_dss_pclk_mmbuf_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get pclk_mmbuf_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}

		ret = of_property_read_string_index(np, "clock-names", 7, &g_dss_dphy0_ref_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get dphy0_ref_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 8, &g_dss_dphy1_ref_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get dphy1_ref_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 9, &g_dss_dphy0_cfg_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get dphy0_cfg_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 10, &g_dss_dphy1_cfg_clk_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get dphy1_cfg_clk resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 11, &g_dss_pclk_dsi0_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get dss_pclk_dsi0 resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 12, &g_dss_pclk_dsi1_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get dss_pclk_dsi1 resource! ret=%d.\n", ret);
			return -ENXIO;
		}
		ret = of_property_read_string_index(np, "clock-names", 13, &g_dss_pclk_pctrl_name);
		if (ret != 0) {
			HISI_FB_ERR("failed to get dss_pclk_pctrl resource! ret=%d.\n", ret);
			return -ENXIO;
		}

		ret = hisi_fb_enable_iommu(pdev);
		if (ret != 0) {
			HISI_FB_ERR("failed to hisi_fb_enable_iommu! ret=%d.\n", ret);
			return -ENXIO;
		}

		/* find and get logo-buffer base */
		np = of_find_node_by_path(DTS_PATH_LOGO_BUFFER);
		if (!np) {
			HISI_FB_ERR("NOT FOUND dts path: %s!\n", DTS_PATH_LOGO_BUFFER);
			//return -ENXIO;
		}
	#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
		ret = of_property_read_u32_index(np, "reg", 1, &g_logo_buffer_base);
		if (ret != 0) {
			HISI_FB_ERR("failed to get g_logo_buffer_base resource! ret=%d.\n", ret);
			g_logo_buffer_base = 0;
		}
		ret = of_property_read_u32_index(np, "reg", 3, &g_logo_buffer_size);
		if (ret != 0) {
			HISI_FB_ERR("failed to get g_logo_buffer_size resource! ret=%d.\n", ret);
			g_logo_buffer_size = 0;
		}
	#endif
		HISI_FB_INFO("g_logo_buffer_base = 0x%x, g_logo_buffer_size = 0x%x. \n", g_logo_buffer_base, g_logo_buffer_size);

		hisi_fb_resource_initialized = 1;

		hisi_fb_device_set_status0(DTS_FB_RESOURCE_INIT_READY);

		HISI_FB_DEBUG("initialized=%d, -.\n", hisi_fb_resource_initialized);
		return 0;
	}

	if (pdev->id < 0) {
		HISI_FB_ERR("WARNING: id=%d, name=%s!\n", pdev->id, pdev->name);
		return 0;
	}

	if (!hisi_fb_resource_initialized) {
		HISI_FB_ERR("fb resource not initialized!\n");
		return -EPERM;
	}

	if (pdev_list_cnt >= HISI_FB_MAX_DEV_LIST) {
		HISI_FB_ERR("too many fb devices, num=%d!\n", pdev_list_cnt);
		return -ENOMEM;
	}

	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = hisi_fb_register(hisifd);
	if (ret) {
		HISI_FB_ERR("fb%d hisi_fb_register failed, error=%d!\n", hisifd->index, ret);
		return ret;
	}

	/* config earlysuspend */
#ifdef CONFIG_HAS_EARLYSUSPEND
	hisifd->early_suspend.suspend = hisifb_early_suspend;
	hisifd->early_suspend.resume = hisifb_early_resume;
	hisifd->early_suspend.level = EARLY_SUSPEND_LEVEL_DISABLE_FB - 2;
	register_early_suspend(&hisifd->early_suspend);
#endif

	pdev_list[pdev_list_cnt++] = pdev;

	/* set device probe status */
	hisi_fb_device_set_status1(hisifd);

#if defined (CONFIG_HUAWEI_DSM)
	if(!lcd_dclient) {
		lcd_dclient = dsm_register_client(&dsm_lcd);
	}
#endif

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int hisi_fb_remove(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	/* pm_runtime unregister */
	if (hisifd->pm_runtime_unregister)
		hisifd->pm_runtime_unregister(pdev);

	/* stop the device */
	if (hisi_fb_suspend_sub(hisifd) != 0)
		HISI_FB_ERR("fb%d hisi_fb_suspend_sub failed!\n", hisifd->index);

	/* overlay destroy */
	hisi_overlay_deinit(hisifd);

	/* free framebuffer */
	hisifb_free_fb_buffer(hisifd);
	if (hisifd->ion_client) {
		ion_client_destroy(hisifd->ion_client);
		hisifd->ion_client = NULL;
	}

	/* remove /dev/fb* */
	unregister_framebuffer(hisifd->fbi);

	/* unregister buf_sync */
	if (hisifd->buf_sync_unregister)
		hisifd->buf_sync_unregister(pdev);
	/* unregister vsync */
	if (hisifd->vsync_unregister)
		hisifd->vsync_unregister(pdev);
	/* unregister backlight */
	if (hisifd->bl_unregister)
		hisifd->bl_unregister(pdev);
	/* fb sysfs remove */
	if (hisifd->sysfs_remove_fnc)
		hisifd->sysfs_remove_fnc(hisifd->pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static int hisi_fb_suspend_sub(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;

	BUG_ON(hisifd == NULL);

	ret = hisi_fb_blank_sub(FB_BLANK_POWERDOWN, hisifd->fbi);
	if (ret) {
		HISI_FB_ERR("fb%d can't turn off display, error=%d!\n", hisifd->index, ret);
		return ret;
	}

	return 0;
}

static int hisi_fb_resume_sub(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;

	BUG_ON(hisifd == NULL);

	ret = hisi_fb_blank_sub(FB_BLANK_UNBLANK, hisifd->fbi);
	if (ret) {
		HISI_FB_ERR("fb%d can't turn on display, error=%d!\n", hisifd->index, ret);
	}

	return ret;
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void hisifb_early_suspend(struct early_suspend *h)
{
	struct hisi_fb_data_type *hisifd = NULL;

	hisifd = container_of(h, struct hisi_fb_data_type, early_suspend);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	hisi_fb_suspend_sub(hisifd);

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);
}

static void hisifb_early_resume(struct early_suspend *h)
{
	struct hisi_fb_data_type *hisifd = NULL;

	hisifd = container_of(h, struct hisi_fb_data_type, early_suspend);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	hisi_fb_resume_sub(hisifd);

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);
}
#endif

#if defined(CONFIG_PM) && !defined(CONFIG_HAS_EARLYSUSPEND)
static int hisi_fb_suspend(struct platform_device *pdev, pm_message_t state)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	console_lock();
	fb_set_suspend(hisifd->fbi, FBINFO_STATE_SUSPENDED);
	ret = hisi_fb_suspend_sub(hisifd);
	if (ret != 0) {
		HISI_FB_ERR("fb%d hisi_fb_suspend_sub failed, error=%d!\n", hisifd->index, ret);
		fb_set_suspend(hisifd->fbi, FBINFO_STATE_RUNNING);
	} else {
		pdev->dev.power.power_state = state;
	}
	console_unlock();

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);

	return ret;
}

static int hisi_fb_resume(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	console_lock();
	ret = hisi_fb_resume_sub(hisifd);
	pdev->dev.power.power_state = PMSG_ON;
	fb_set_suspend(hisifd->fbi, FBINFO_STATE_RUNNING);
	console_unlock();

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);

	return ret;
}
#else
#define hisi_fb_suspend NULL
#define hisi_fb_resume NULL
#endif


/*******************************************************************************
** pm_runtime
*/
#ifdef CONFIG_PM_RUNTIME
static int hisi_fb_runtime_suspend(struct device *dev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Poniter\n");
		return 0;
	}

	hisifd = dev_get_drvdata(dev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Poniter\n");
		return 0;
	}

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	ret = hisi_fb_suspend_sub(hisifd);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, failed to hisi_fb_suspend_sub! ret=%d\n", hisifd->index, ret);
	}

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);

	return 0;
}

static int hisi_fb_runtime_resume(struct device *dev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Poniter\n");
		return 0;
	}

	hisifd = dev_get_drvdata(dev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Poniter\n");
		return 0;
	}

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	ret = hisi_fb_resume_sub(hisifd);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, failed to hisi_fb_resume_sub! ret=%d\n", hisifd->index, ret);
	}

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);

	return 0;
}

static int hisi_fb_runtime_idle(struct device *dev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Poniter\n");
		return 0;
	}

	hisifd = dev_get_drvdata(dev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Poniter\n");
		return 0;
	}

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);

	return 0;
}

static void hisifb_pm_runtime_get(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;

	BUG_ON(hisifd == NULL);

	ret = pm_runtime_get_sync(hisifd->fbi->dev);
	if (ret < 0) {
		HISI_FB_ERR("fb%d, failed to pm_runtime_get_sync! ret=%d.", hisifd->index, ret);
	}
}

static void hisifb_pm_runtime_put(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;

	BUG_ON(hisifd == NULL);

	ret = pm_runtime_put(hisifd->fbi->dev);
	if (ret < 0) {
		HISI_FB_ERR("fb%d, failed to pm_runtime_put! ret=%d.", hisifd->index, ret);
	}
}

static void hisifb_pm_runtime_register(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	ret = pm_runtime_set_active(hisifd->fbi->dev);
	if (ret < 0)
		HISI_FB_ERR("fb%d failed to pm_runtime_set_active.\n", hisifd->index);
	pm_runtime_enable(hisifd->fbi->dev);
}

static void hisifb_pm_runtime_unregister(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pm_runtime_disable(hisifd->fbi->dev);
}
#endif

#ifdef CONFIG_PM_SLEEP
static int hisi_fb_pm_suspend(struct device *dev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Poniter\n");
		return 0;
	}

	hisifd = dev_get_drvdata(dev);
	if (!hisifd)
		return 0;

	if (hisifd->index != PRIMARY_PANEL_IDX)
		return 0;

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	ret = hisi_fb_suspend_sub(hisifd);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, failed to hisi_fb_suspend_sub! ret=%d\n", hisifd->index, ret);
	}

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);

	return 0;
}

#if 0
static int hisi_fb_pm_resume(struct device *dev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	int ret = 0;

	hisifd = dev_get_drvdata(dev);
	if (!hisifd)
		return 0;

	if (hisifd->index != PRIMARY_PANEL_IDX)
		return 0;

	HISI_FB_INFO("fb%d, +.\n", hisifd->index);

	ret = hisi_fb_resume_sub(hisifd);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, failed to hisi_fb_resume_sub! ret=%d\n", hisifd->index, ret);
	}

	HISI_FB_INFO("fb%d, -.\n", hisifd->index);

	return 0;
}
#endif
#endif

static void hisi_fb_shutdown(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("pdev NULL Pointer\n");
		return;
	}

	hisifd = platform_get_drvdata(pdev);
	if (!hisifd) {
		if (pdev->id) {
			HISI_FB_ERR("hisifd NULL Pointer,pdev->id=%d\n", pdev->id);
		}
		return;
	}

	if (hisifd->index != PRIMARY_PANEL_IDX) {
		HISI_FB_DEBUG("fb%d do not shutdown\n", hisifd->index);
		return;
	}

	HISI_FB_INFO("fb%d shutdown +\n", hisifd->index);
	hisifd->fb_shutdown = true;

	ret = hisi_fb_blank_sub(FB_BLANK_POWERDOWN, hisifd->fbi);
	if (ret) {
		HISI_FB_ERR("fb%d can't turn off display, error=%d!\n", hisifd->index, ret);
	}

	HISI_FB_INFO("fb%d shutdown -\n", hisifd->index);
}


/*******************************************************************************
**
*/
static struct dev_pm_ops hisi_fb_dev_pm_ops = {
#ifdef CONFIG_PM_RUNTIME
	.runtime_suspend = hisi_fb_runtime_suspend,
	.runtime_resume = hisi_fb_runtime_resume,
	.runtime_idle = hisi_fb_runtime_idle,
#endif
#ifdef CONFIG_PM_SLEEP
	.suspend = hisi_fb_pm_suspend,
	.resume = NULL,
#endif
};

static const struct of_device_id hisi_fb_match_table[] = {
	{
		.compatible = DTS_COMP_FB_NAME,
		.data = NULL,
	},
	{},
};
MODULE_DEVICE_TABLE(of, hisi_fb_match_table);

static struct platform_driver hisi_fb_driver = {
	.probe = hisi_fb_probe,
	.remove = hisi_fb_remove,
#ifndef CONFIG_HAS_EARLYSUSPEND
	.suspend = hisi_fb_suspend,
	.resume = hisi_fb_resume,
#endif
	.shutdown = hisi_fb_shutdown,
	.driver = {
		.name = DEV_NAME_FB,
		.owner  = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_fb_match_table),
		.pm = &hisi_fb_dev_pm_ops,
	},
};

static int __init hisi_fb_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&hisi_fb_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

static int __init early_parse_color_temp_cal_cmdline(char *arg)
{
	int len = 0;
	u8 color_temp_cal = 0;
	memset(color_temp_cal_buf, 0, sizeof(color_temp_cal_buf));
	if (arg) {
		len = strlen(arg);

		if (len > (sizeof(color_temp_cal_buf)-1)) {
			len = sizeof(color_temp_cal_buf)-1;
		}
		memcpy(color_temp_cal_buf, arg, len);
	} else {
		HISI_FB_ERR("%s : arg is NULL\n", __func__);
		color_temp_cal_buf[0] = 0;
	}

	color_temp_cal = (u8)simple_strtol(color_temp_cal_buf, NULL, 10);
	HISI_FB_INFO("color_temp_cal_buf = %s, color_temp_cal = %d\n", color_temp_cal_buf, color_temp_cal);
	color_temp_cal_buf[0] = color_temp_cal;
	return 0;
}
early_param("COLOR_TMP", early_parse_color_temp_cal_cmdline);

module_init(hisi_fb_init);

MODULE_DESCRIPTION("Hisilicon Framebuffer Driver");
MODULE_LICENSE("GPL v2");
