/*
 *  Hisilicon K3 soc camera ISP driver header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __MINI_CAM_DBG_H__
#define __MINI_CAM_DBG_H__

#include "cam_dbg_comm.h"

typedef struct _mini_cam_pwdn_status_t {
	u32 isp_pwdn_status;
	u32 csi_pwdn_status;
	u32 sensor_pwdn_status;
} mini_cam_pwdn_status_t;


typedef struct _mini_cam_dbg_info_t {

	u32 dbg_isp_base_addr;
	u32 dbg_csi0_base_addr;
	u32 dbg_csi1_base_addr;

	/* FIXME: add infomation we need here */

} mini_cam_dbg_info_t;


#ifdef ISP_DEBUG_ZSL
int mini_isp_debug_load_cfg(char *cfg_file,char *key_name,u8 *key_var);
int mini_isp_debug_load_reg(char *reg_file,u32 *reg_key,u32 reg_max,u32 *reg_cnt);
void mini_isp_debug_init_cmd_reg(void);
void mini_isp_debug_dump_cmd_reg(void);
void mini_isp_debug_print_cmd_reg(void);
void mini_isp_debug_init_irq_reg(void);
void mini_isp_debug_dump_irq_reg(void);
void mini_isp_debug_print_irq_reg(void);
int mini_isp_debug_init(void);
int mini_isp_debug_deinit(void);
extern int mini_atoi16(char *s);
#endif

void mini_register_cam_dbg_info(int dbg_info_type, void *context);
void mini_dump_queue(struct list_head *list_queue, u32 flag);
void mini_dump_file(char *filename, u32 addr, u32 size);
void mini_dump_cmd_reg(void);
void mini_dump_status_after_reg(void);
void mini_dump_ispzyk_reg(void);

void mini_dump_sensor_reg(u32 addr);
void mini_dump_size_reg(void);
void mini_dump_zoom_reg(void);
void mini_dump_isp_reg(int start, int size);

void mini_dump_scctrl_isp_reg(void);

u32 mini_get_cam_pwdn_status(int module);
void mini_set_cam_pwdn_status(int module, u32 status);
u32 mini_get_cam_dbgfs_pwdncfg(void);
#ifdef CONFIG_DEBUG_FS
u8 mini_get_cam_dbgfs_flash_timeout(void);
u8 mini_get_cam_dbgfs_flash_timeout_valid(void);
void mini_set_cam_dbgfs_flash_timeout_valid(u8 valid);
#endif

#endif /*__CAM_DBG_H__ */

/********************** END ***********************/
