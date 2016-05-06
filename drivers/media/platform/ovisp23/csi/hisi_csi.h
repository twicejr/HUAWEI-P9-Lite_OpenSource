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

#ifndef _HISI_CSI_H
#define _HISI_CSI_H


#include "../sensor/hisi_sensor.h"
struct csi_hw_info
{
	u32 csi_base_offset[CSI_INDEX_CNT];
	u32 csi_irq[CSI_INDEX_CNT];
	struct clk* phyclk[CSI_INDEX_CNT];
};

struct hisi_csi_pad
{
	bool csi_inited[CSI_INDEX_CNT];
	struct csi_hw_info info;
	int (*hisi_csi_enable)(csi_index_t csi_index, int csi_lane, int csi_mipi_clk);
	int (*hisi_csi_disable)(csi_index_t csi_index);
	int (*hisi_csi_config)(csi_index_t csi_index, int csi_lane, int csi_mipi_clk);
};

extern struct hisi_csi_pad csi_pad;

#endif