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
#ifndef HISI_FB_H
#define HISI_FB_H


#include <linux/console.h>
#include <linux/uaccess.h>
#include <linux/leds.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/fb.h>
#include <linux/spinlock.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/raid/pq.h>
#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif
#include <linux/time.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/version.h>
#include <linux/backlight.h>
#include <linux/pwm.h>
#include <linux/pm_runtime.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/memblock.h>

#include <linux/spi/spi.h>

#include <linux/ion.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/gpio.h>

#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>

#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/pinctrl/consumer.h>
#include <linux/file.h>
#include <linux/dma-buf.h>
#include <linux/genalloc.h>
#include <linux/hisi/hisi-iommu.h>
#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif

#if defined (CONFIG_TEE_TUI)
#include "tui.h"
#endif

#if defined (CONFIG_ATFDRIVER)
#include "atfdriver.h"
#endif
//#include <linux/huawei/hisi_irq_affinity.h>

#include "hisi_fb_def.h"
#include "hisi_fb_panel.h"
#include "hisi_dss.h"
#include "hisi_mipi_dsi.h"
#include "hisi_overlay_cmdlist_utils.h"
#include "hisi_display_effect.h"
#include "hisi_dpe_utils.h"

#if defined (CONFIG_HISI_FB_3650)
#include "hisi_dss_regs_hi3650.h"
#include "hisi_overlay_utils_hi3650.h"
#endif
#if defined(CONFIG_HISI_FB_6250)
#include "hisi_dss_regs_hi3650.h"
#include "hisi_overlay_utils_hi6250.h"
#endif
#if defined(CONFIG_HISI_FB_3660)
#include "hisi_dss_regs_hi3660.h"
#include "hisi_overlay_utils_hi3660.h"
#endif

//#define CONFIG_HISI_FB_DUMP_DSS_REG
//#define CONFIG_HISI_FB_COLORBAR_USED
//#define CONFIG_HISI_FB_OV_BASE_USED
//#define CONFIG_HISI_FB_VSYNC_THREAD
#define CONFIG_HISI_FB_BACKLIGHT_DELAY
//#define CONFIG_FAKE_VSYNC_USED
#define CONFIG_BUF_SYNC_USED
//#define CONFIG_HISI_FB_HEAP_CARVEOUT_USED


//#define CONFIG_FIX_DSS_WCH_ISR_BUG
//#define CONFIG_FPGA_SDP_TEST
#define CONFIG_SMMU_RWERRADDR_USED
//#define CONFIG_DSS_MMBUF_FENCE_USED
//#define CONFIG_HISI_MIPI_NON_CONTINUE
#define CONFIG_DSS_MMBUF_CLK_USED
//#define CONFIG_PCLK_PCTRL_USED

#define CONFIG_BACKLIGHT_2048

#define HISI_DSS_COMPOSER_HOLD_TIME	(1000 * 3600 * 24 * 7)


#define HISI_FB0_NUM	(3)
#define HISI_FB1_NUM	(0)
#define HISI_FB2_NUM	(0)


#define HISI_FB_SYSFS_ATTRS_NUM	(64)

#define HISI_FB_MAX_DEV_LIST (32)
#define HISI_FB_MAX_FBI_LIST (32)

#define HISI_DSS_OFFLINE_MAX_NUM	(2)
#define HISI_DSS_OFFLINE_MAX_BLOCK	(64)
#define HISI_DSS_OFFLINE_MAX_LIST	(128)

#if defined (CONFIG_HUAWEI_DSM)
#define VACTIVE0_TIMEOUT_EXPIRE_COUNT	(6)
#define UNDERFLOW_EXPIRE_COUNT (6)
#define UNDERFLOW_INTERVAL (1000)
#endif

//esd check period-->5000ms
#define ESD_CHECK_TIME_PERIOD	(5000)

struct hisifb_vsync {
	wait_queue_head_t vsync_wait;
	ktime_t vsync_timestamp;
	int vsync_created;
	int vsync_enabled;
	int vsync_infinite;
	int vsync_infinite_count;

	int vsync_ctrl_expire_count;
	int vsync_ctrl_enabled;
	int vsync_ctrl_disabled_set;
	int vsync_ctrl_isr_enabled;
	int vsync_ctrl_offline_enabled;
	struct work_struct vsync_ctrl_work;
	spinlock_t spin_lock;

	struct mutex vsync_lock;
#ifdef CONFIG_HISI_FB_VSYNC_THREAD
	struct task_struct *vsync_thread;
#endif

	atomic_t buffer_updated;
	void (*vsync_report_fnc) (int buffer_updated);

	struct hisi_fb_data_type *hisifd;
};

enum dss_sec_event {
	DSS_SEC_DISABLE = 0,
	DSS_SEC_ENABLE,
};

enum dss_sec_status {
	DSS_SEC_IDLE = 0,
	DSS_SEC_RUNNING,
};

enum bl_control_mode {
	REG_ONLY_MODE = 1,
	PWM_ONLY_MODE,
	MUTI_THEN_RAMP_MODE,
	RAMP_THEN_MUTI_MODE,
};

struct hisifb_secure {
	uint32_t secure_created;
	uint32_t secure_status;
	uint32_t secure_event;
	uint32_t secure_blank_flag;
	uint32_t tui_need_switch;
	uint32_t tui_need_skip_report;

	struct mutex secure_lock;

	struct work_struct secure_ctrl_work;

	void (*secure_layer_config) (struct hisi_fb_data_type *hisifd, dss_layer_t *layer);
	void (*secure_layer_deconfig) (struct hisi_fb_data_type *hisifd, dss_layer_t *layer);
	void (*notify_secure_switch) (struct hisi_fb_data_type *hisifd);
	void (*set_reg) (uint32_t addr, uint32_t val, uint8_t bw, uint8_t bs);

	struct hisi_fb_data_type *hisifd;
};

/* esd func define */
struct hisifb_esd {
	int esd_inited;
	struct hrtimer esd_hrtimer;
	struct workqueue_struct *esd_check_wq;
	struct work_struct esd_check_work;
	struct task_struct *esd_handle_thread;
	wait_queue_head_t esd_handle_wait;

	struct hisi_fb_data_type *hisifd;
};

#ifdef CONFIG_BUF_SYNC_USED
#include <linux/sync.h>
#include <linux/sw_sync.h>
#endif

struct hisifb_buf_sync {
#ifdef CONFIG_BUF_SYNC_USED
	struct sw_sync_timeline *timeline;
	int timeline_max;
	int refresh;
	spinlock_t refresh_lock;
#endif

	struct workqueue_struct *free_layerbuf_queue;
	struct work_struct free_layerbuf_work;
	struct list_head layerbuf_list;
	bool layerbuf_flushed;
	spinlock_t layerbuf_spinlock;
};

struct hisifb_layerbuf {
	struct ion_handle *ion_handle;
	struct list_head list_node;
	int timeline;
	bool has_map_iommu;

	int32_t shared_fd;
	uint32_t frame_no;
	dss_mmbuf_t mmbuf;
	uint64_t vir_addr;
	int32_t chn_idx;
};

struct hisifb_backlight {
#ifdef CONFIG_HISI_FB_BACKLIGHT_DELAY
	struct delayed_work bl_worker;
#endif
	struct semaphore bl_sem;
	int bl_updated;
	int bl_level_old;
	int frame_updated;

	struct workqueue_struct *sbl_queue;
	struct work_struct sbl_work;
};


struct hisi_fb_data_type {
	uint32_t index;
	uint32_t ref_cnt;
	uint32_t fb_num;
	uint32_t fb_imgType;
	uint32_t bl_level;

	char __iomem *dss_base;
	char __iomem *peri_crg_base;
	char __iomem *sctrl_base;
	char __iomem *pctrl_base;
	char __iomem *noc_dss_base;
	char __iomem *mmbuf_crg_base;
#if defined(CONFIG_HISI_FB_3660)
	char __iomem *pmctrl_base;
#endif
	char __iomem *mmbuf_asc0_base;
	char __iomem *mipi_dsi0_base;
	char __iomem *mipi_dsi1_base;

	uint32_t dss_base_phy;

	uint32_t dpe_irq;
	uint32_t dsi0_irq;
	uint32_t dsi1_irq;
	uint32_t mmbuf_asc0_irq;

	struct regulator_bulk_data *dpe_regulator;
	struct regulator_bulk_data *mmbuf_regulator;

	const char *dss_axi_clk_name;
	const char *dss_pclk_dss_name;
	const char *dss_pri_clk_name;
	const char *dss_pxl0_clk_name;
	const char *dss_pxl1_clk_name;
	const char *dss_mmbuf_clk_name;
	const char *dss_pclk_mmbuf_name;
	const char *dss_dphy0_ref_clk_name;
	const char *dss_dphy1_ref_clk_name;
	const char *dss_dphy0_cfg_clk_name;
	const char *dss_dphy1_cfg_clk_name;
	const char *dss_pclk_dsi0_name;
	const char *dss_pclk_dsi1_name;
	const char *dss_pclk_pctrl_name;

	struct clk *dss_axi_clk;
	struct clk *dss_pclk_dss_clk;
	struct clk *dss_pri_clk;
	struct clk *dss_pxl0_clk;
	struct clk *dss_pxl1_clk;
	struct clk *dss_mmbuf_clk;
	struct clk *dss_pclk_mmbuf_clk;
	struct clk *dss_dphy0_ref_clk;
	struct clk *dss_dphy1_ref_clk;
	struct clk *dss_dphy0_cfg_clk;
	struct clk *dss_dphy1_cfg_clk;
	struct clk *dss_pclk_dsi0_clk;
	struct clk *dss_pclk_dsi1_clk;
	struct clk *dss_pclk_pctrl_clk;

	struct hisi_panel_info panel_info;
	bool panel_power_on;
	bool fb_shutdown;
	bool lcd_self_testing;
	bool video_ldi_dis_at_vac_start;
	struct semaphore blank_sem;
	struct semaphore blank_sem0;
	struct semaphore brightness_esd_sem;

	void (*sysfs_attrs_append_fnc) (struct hisi_fb_data_type *hisifd, struct attribute *attr);
	int (*sysfs_create_fnc) (struct platform_device *pdev);
	void (*sysfs_remove_fnc) (struct platform_device *pdev);
	void (*pm_runtime_register) (struct platform_device *pdev);
	void (*pm_runtime_unregister) (struct platform_device *pdev);
	void (*pm_runtime_get) (struct hisi_fb_data_type *hisifd);
	void (*pm_runtime_put) (struct hisi_fb_data_type *hisifd);
	void (*bl_register) (struct platform_device *pdev);
	void (*bl_unregister) (struct platform_device *pdev);
	void (*bl_update) (struct hisi_fb_data_type *hisifd);
	void (*bl_cancel) (struct hisi_fb_data_type *hisifd);
	int (*sbl_ctrl_fnc) (struct fb_info *info, int value);
	void (*sbl_isr_handler)(struct hisi_fb_data_type *hisifd);
	void (*vsync_register) (struct platform_device *pdev);
	void (*vsync_unregister) (struct platform_device *pdev);
	int (*vsync_ctrl_fnc) (struct fb_info *info, void __user *argp);
	void (*vsync_isr_handler) (struct hisi_fb_data_type *hisifd);
	void (*secure_register) (struct platform_device *pdev);
	void (*secure_unregister) (struct platform_device *pdev);
	void (*buf_sync_register) (struct platform_device *pdev);
	void (*buf_sync_unregister) (struct platform_device *pdev);
	void (*buf_sync_signal) (struct hisi_fb_data_type *hisifd);
	void (*buf_sync_suspend) (struct hisi_fb_data_type *hisifd);
	void (*esd_register) (struct platform_device *pdev);
	void (*esd_unregister) (struct platform_device *pdev);

	bool (*set_fastboot_fnc) (struct fb_info *info);
	int (*open_sub_fnc) (struct fb_info *info);
	int (*release_sub_fnc) (struct fb_info *info);
	int (*on_fnc) (struct hisi_fb_data_type *hisifd);
	int (*off_fnc) (struct hisi_fb_data_type *hisifd);
	int (*lp_fnc) (struct hisi_fb_data_type *hisifd, bool lp_enter);
	int (*frc_fnc) (struct hisi_fb_data_type *hisifd, int fps);
	int (*esd_fnc) (struct hisi_fb_data_type *hisifd);
	int (*pan_display_fnc) (struct hisi_fb_data_type *hisifd);
	int (*ov_ioctl_handler) (struct hisi_fb_data_type *hisifd, uint32_t cmd, void __user *argp);
	int (*ov_online_play) (struct hisi_fb_data_type *hisifd, void __user *argp);
	int (*ov_offline_play) (struct hisi_fb_data_type *hisifd, void __user *argp);
	void (*ov_wb_isr_handler) (struct hisi_fb_data_type *hisifd);
	void (*ov_vactive0_start_isr_handler) (struct hisi_fb_data_type *hisifd);
	void (*set_reg) (struct hisi_fb_data_type *hisifd,
		char __iomem *addr, uint32_t val, uint8_t bw, uint8_t bs);

	void (*crc_isr_handler)(struct hisi_fb_data_type *hisifd);

	void (*ov_ldi_underflow_isr_handle)(struct hisi_fb_data_type *hisifd);

	void (*sysfs_attrs_add_fnc)(struct hisi_fb_data_type*hisifd);
	int (*mipi_dsi_bit_clk_upt_isr_handler) (struct hisi_fb_data_type *hisifd);

	struct hisifb_backlight backlight;
	int sbl_enable;
	int sbl_lsensor_value;
	int sbl_level;
	dss_sbl_t sbl;

	int color_temperature_flag;

	dss_display_effect_t ce_ctrl;
	dss_ce_info_t acm_ce_info;
	dss_ce_info_t prefix_ce_info[DSS_CHN_MAX_DEFINE];
#ifdef CONFIG_HISI_FB_3660
	dss_hiace_info_t hiace_info;
#endif

	int sysfs_index;
	struct attribute *sysfs_attrs[HISI_FB_SYSFS_ATTRS_NUM];
	struct attribute_group sysfs_attr_group;

	struct hisifb_vsync vsync_ctrl;
	struct hisifb_buf_sync buf_sync_ctrl;
	struct dss_clk_rate dss_clk_rate;
	struct hisifb_secure secure_ctrl;
	struct hisifb_esd esd_ctrl;

#ifdef CONFIG_FAKE_VSYNC_USED
	bool fake_vsync_used;
	struct hrtimer fake_vsync_hrtimer;
#endif
	dss_module_reg_t dss_module;
	dss_overlay_t ov_req;
	dss_overlay_block_t ov_block_infos[HISI_DSS_OV_BLOCK_NUMS];
	dss_overlay_t ov_req_prev;
	dss_overlay_block_t ov_block_infos_prev[HISI_DSS_OV_BLOCK_NUMS];
	dss_overlay_t ov_req_prev_prev;
	dss_overlay_block_t ov_block_infos_prev_prev[HISI_DSS_OV_BLOCK_NUMS];

	dss_rect_t *ov_block_rects[HISI_DSS_OFFLINE_MAX_BLOCK];

	dss_cmdlist_data_t *cmdlist_data_tmp[HISI_DSS_CMDLIST_DATA_MAX];
	dss_cmdlist_data_t *cmdlist_data;
	dss_cmdlist_info_t *cmdlist_info;
	int32_t cmdlist_idx;

	struct gen_pool *mmbuf_gen_pool;
	dss_mmbuf_info_t mmbuf_infos[HISI_DSS_CMDLIST_DATA_MAX];
	dss_mmbuf_info_t *mmbuf_info;
	struct list_head *mmbuf_list;

	bool dss_module_resource_initialized;
	dss_module_reg_t dss_module_default;

	struct dss_rect dirty_region_updt;
	uint32_t esd_happened;

	struct ion_client *ion_client;
	struct ion_handle *ion_handle;
	struct iommu_map_format iommu_format;
	struct iommu_domain* hisi_domain;

	struct fb_info *fbi;
	struct platform_device *pdev;
#ifdef CONFIG_HAS_EARLYSUSPEND
	struct early_suspend early_suspend;
#endif

	wait_queue_head_t vactive0_start_wq;
	uint32_t vactive0_start_flag;
	uint32_t vactive0_end_flag;
	uint32_t ldi_data_gate_en;

	wait_queue_head_t crc_wq;
	uint32_t crc_flag;
	struct workqueue_struct *dss_debug_wq;
	struct work_struct dss_debug_work;

	struct workqueue_struct *ldi_underflow_wq;
	struct work_struct ldi_underflow_work;
#if defined (CONFIG_HUAWEI_DSM)
	struct workqueue_struct *dss_underflow_debug_workqueue;
	struct work_struct dss_underflow_debug_work;
#endif
	struct workqueue_struct *rch2_ce_end_wq;
	struct work_struct rch2_ce_end_work;
	struct workqueue_struct *rch4_ce_end_wq;
	struct work_struct rch4_ce_end_work;
	struct workqueue_struct *dpp_ce_end_wq;
	struct work_struct dpp_ce_end_work;
#ifdef CONFIG_HISI_FB_3660
	struct workqueue_struct *hiace_end_wq;
	struct work_struct hiace_end_work;
#endif

	dss_rect_t res_updt_rect;
	dss_rect_t resolution_rect;

	uint32_t frame_count;
	uint32_t frame_update_flag;
	bool fb_mem_free_flag;
	uint8_t color_temp_cal_enabled;

	uint32_t vsync_ctrl_type;
	struct notifier_block nb;
	struct notifier_block lcd_int_nb; //for clear lcd ocp interrupt
};


/******************************************************************************
** FUNCTIONS PROTOTYPES
*/
extern int g_debug_ldi_underflow;
extern int g_debug_ldi_underflow_clear;

extern int g_debug_mmu_error;
extern int g_debug_set_reg_val;
extern int g_debug_online_vsync;
extern int g_debug_ovl_online_composer;
extern int g_debug_ovl_online_composer_hold;
extern int g_debug_ovl_online_composer_return;
extern int g_debug_ovl_online_composer_timediff;
extern int g_debug_ovl_online_composer_time_threshold;

extern int g_debug_ovl_offline_composer;
extern int g_debug_ovl_block_composer;
extern int g_debug_ovl_offline_composer_hold;
extern int g_debug_ovl_offline_composer_timediff;
extern int g_debug_ovl_offline_composer_time_threshold;
extern int g_debug_ovl_offline_block_num;
extern int g_debug_ovl_cmdlist;
extern int g_dump_cmdlist_content;
extern int g_enable_ovl_cmdlist_online;
extern int g_enable_ovl_cmdlist_offline;
extern int g_rdma_stretch_threshold;
extern int g_enable_dirty_region_updt;
extern int g_debug_dirty_region_updt;
extern int g_enable_crc_debug;
extern int g_ldi_data_gate_en;
extern int g_debug_need_save_file;
extern int g_debug_ovl_credit_step;
extern int g_debug_layerbuf_sync;
extern int g_enable_dss_idle;
extern int g_dss_effect_sharpness1D_en;
extern int g_dss_effect_sharpness2D_en;
extern int g_dss_effect_acm_ce_en;
extern int g_debug_dump_mmbuf;

extern int g_err_status;

extern int g_primary_lcd_xres;
extern int g_primary_lcd_yres;
extern uint64_t g_pxl_clk_rate;

extern uint8_t g_prefix_ce_support;
extern uint8_t g_prefix_sharpness1D_support;
extern uint8_t g_prefix_sharpness2D_support;

extern uint32_t g_online_cmdlist_idxs;
extern uint32_t g_offline_cmdlist_idxs;

extern uint32_t g_fpga_flag;
extern uint32_t g_fastboot_enable_flag;
extern uint32_t g_fake_lcd_flag;
extern uint32_t g_dss_module_resource_initialized;
extern uint32_t g_logo_buffer_base;
extern uint32_t g_logo_buffer_size;
extern uint32_t g_underflow_stop_perf_stat;

extern uint32_t g_fastboot_already_set;

extern int g_debug_enable_lcd_sleep_in;

extern struct fb_info *fbi_list[HISI_FB_MAX_FBI_LIST];
extern struct hisi_fb_data_type *hisifd_list[HISI_FB_MAX_FBI_LIST];
#if defined (CONFIG_HUAWEI_DSM)
extern struct dsm_client *lcd_dclient;
#endif

uint32_t get_panel_xres(struct hisi_fb_data_type *hisifd);
uint32_t get_panel_yres(struct hisi_fb_data_type *hisifd);

bool is_fastboot_display_enable(void);
bool is_dss_idle_enable(void);


/* fb buffer */
unsigned long hisifb_alloc_fb_buffer(struct hisi_fb_data_type *hisifd);
void hisifb_free_fb_buffer(struct hisi_fb_data_type *hisifd);
void hisifb_free_logo_buffer(struct hisi_fb_data_type *hisifd);

/* dss secure */
void hisifb_secure_register(struct platform_device *pdev);
void hisifb_secure_unregister(struct platform_device *pdev);
int hisi_fb_blank_sub(int blank_mode, struct fb_info *info);

/* backlight */
void hisifb_backlight_update(struct hisi_fb_data_type *hisifd);
void hisifb_backlight_cancel(struct hisi_fb_data_type *hisifd);
void hisifb_backlight_register(struct platform_device *pdev);
void hisifb_backlight_unregister(struct platform_device *pdev);
void hisifb_sbl_isr_handler(struct hisi_fb_data_type *hisifd);
void hisifb_set_backlight(struct hisi_fb_data_type *hisifd, uint32_t bkl_lvl);

/* vsync */
void hisifb_frame_updated(struct hisi_fb_data_type *hisifd);
#ifdef CONFIG_FAKE_VSYNC_USED
enum hrtimer_restart hisifb_fake_vsync(struct hrtimer *timer);
#endif
void hisifb_set_vsync_activate_state(struct hisi_fb_data_type *hisifd, bool infinite);
void hisifb_activate_vsync(struct hisi_fb_data_type *hisifd);
void hisifb_deactivate_vsync(struct hisi_fb_data_type *hisifd);
int hisifb_vsync_ctrl(struct fb_info *info, void __user *argp);
int hisifb_vsync_resume(struct hisi_fb_data_type *hisifd);
int hisifb_vsync_suspend(struct hisi_fb_data_type *hisifd);
void hisifb_vsync_isr_handler(struct hisi_fb_data_type *hisifd);
void hisifb_vsync_register(struct platform_device *pdev);
void hisifb_vsync_unregister(struct platform_device *pdev);

void hisifb_esd_register(struct platform_device *pdev);
void hisifb_esd_unregister(struct platform_device *pdev);

/* buffer sync */
int hisifb_layerbuf_lock_offline(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req, struct list_head *plock_list);
void hisifb_layerbuf_unlock_offline(struct hisi_fb_data_type *hisifd,
	struct list_head *plock_list);
int hisifb_layerbuf_lock(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req, struct list_head *lock_list);
void hisifb_layerbuf_flush(struct hisi_fb_data_type *hisifd,
	struct list_head *lock_list);
void hisifb_layerbuf_unlock(struct hisi_fb_data_type *hisifd,
	struct list_head *pfree_list);
void hisifb_layerbuf_lock_exception(struct hisi_fb_data_type *hisifd,
	struct list_head *lock_list);

int hisifb_buf_sync_wait(int fence_fd);
int hisifb_buf_sync_handle_offline(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req);
int hisifb_buf_sync_handle(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req);
void hisifb_buf_sync_signal(struct hisi_fb_data_type *hisifd);
void hisifb_buf_sync_suspend(struct hisi_fb_data_type *hisifd);
int hisifb_buf_sync_create_fence(struct hisi_fb_data_type *hisifd, unsigned value);
void hisifb_buf_sync_register(struct platform_device *pdev);
void hisifb_buf_sync_unregister(struct platform_device *pdev);

/* control */
int hisifb_ctrl_fastboot(struct hisi_fb_data_type *hisifd);
int hisifb_ctrl_on(struct hisi_fb_data_type *hisifd);
int hisifb_ctrl_off(struct hisi_fb_data_type *hisifd);
int hisifb_ctrl_lp(struct hisi_fb_data_type *hisifd, bool lp_enter);
int hisifb_ctrl_sbl(struct fb_info *info, int value);
int hisifb_ctrl_dss_clk_rate(struct fb_info *info, void __user *argp);
int hisifb_ctrl_pixclk_rate(struct fb_info *info, void __user *argp);
int hisifb_ctrl_frc(struct hisi_fb_data_type *hisifd, int fps);
int hisifb_ctrl_esd(struct hisi_fb_data_type *hisifd);
void hisifb_sysfs_attrs_add(struct hisi_fb_data_type * hisifd);

void set_reg(char __iomem *addr, uint32_t val, uint8_t bw, uint8_t bs);
uint32_t set_bits32(uint32_t old_val, uint32_t val, uint8_t bw, uint8_t bs);
void hisifb_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *addr, uint32_t val, uint8_t bw, uint8_t bs);
uint32_t hisifb_line_length(int index, uint32_t xres, int bpp);
void hisifb_get_timestamp(struct timeval *tv);
uint32_t hisifb_timestamp_diff(struct timeval *lasttime, struct timeval *curtime);
int hisifb_sbl_pow_i(int base, int exp);
void hisifb_save_file(char *filename, char *buf, uint32_t buf_len);

struct platform_device *hisi_fb_device_alloc(struct hisi_fb_panel_data *pdata,
	uint32_t type, uint32_t id);
struct platform_device *hisi_fb_add_device(struct platform_device *pdev);
#if defined (CONFIG_HUAWEI_DSM)
void dss_underflow_debug_func(struct work_struct *work);
#endif

#ifdef CONFIG_HUAWEI_OCP
int hisi_lcd_ocp_recover(struct notifier_block *nb,
		unsigned long event, void *data);
#endif

#endif /* HISI_FB_H */
