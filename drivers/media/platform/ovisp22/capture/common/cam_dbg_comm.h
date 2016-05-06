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

#ifndef __CAM_DBG_COMM_H__
#define __CAM_DBG_COMM_H__

#include <linux/list.h>
/*#define DUMP_QUEUE */
/*#define DUMP_FILE */
/*#define DUMP_PREVIEW_FILE */
/*#define DUMP_SIZE_REG */
/*#define DUMP_CMD_REG */
#define REG_CSI_IRQ

/* dump SCCTRL/AO_SCCTRL/PMCTRL reg about ISP/CSI power on/off,
   rst en/dis and clk en/dis, 2013/05/06 */
#define DUMP_SCCTRL_ISP_REG
#define ISP_DEBUG_ZSL

enum cam_dbgfs_pwdn_module {
	DEBUGFS_PWDN_ISP = 0,
	DEBUGFS_PWDN_CSI,
	DEBUGFS_PWDN_SENSOR,
	DEBUGFS_PWDN_MAX
};

enum cam_dbg_info_type {
	DBG_INFO_ISP_BASE = 0,
	DBG_INFO_CSI0_BASE,
	DBG_INFO_CSI1_BASE,
};

#ifdef ISP_DEBUG_ZSL
enum cam_dbg_print_type {
	ISP_DBG_PRINT_NULL      = 0,
	ISP_DBG_PRINT_DIRECT    = 1,
	ISP_DBG_PRINT_TO_MEM    = 2,
};

#endif

#endif /*__CAM_DBG_H__ */

/********************** END ***********************/
