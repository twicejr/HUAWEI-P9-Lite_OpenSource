/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _HW_CSI_H
#define _HW_CSI_H
#include "../platform/hi3635/platform_cfg.h"
#include <linux/irq.h>

typedef irqreturn_t (*csi_irq_handle)(int irq, void *dev_id);

struct csi_hw_info
{
	u32 csi_base_offset[CSI_INDEX_CNT];
	u32 csi_irq[CSI_INDEX_CNT];
	csi_irq_handle irq_pfn[CSI_INDEX_CNT];
	struct clk* phyclk[CSI_INDEX_CNT];
	u32 dsi_csi_used;
};

struct hw_csi_pad
{
	bool csi_inited[CSI_INDEX_CNT];
	struct csi_hw_info info;
	int (*hw_csi_enable)(csi_index_t csi_index, int csi_lane, int csi_mipi_clk);
	int (*hw_csi_disable)(csi_index_t csi_index);
	int (*hw_csi_config)(csi_index_t csi_index, int csi_lane, int csi_mipi_clk);
};

extern struct hw_csi_pad hw_csi_pad;
void hisi_csi_clear_dmd_counter(void);
#endif
