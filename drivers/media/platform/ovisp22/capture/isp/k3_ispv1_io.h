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

#ifndef __K3_ISPV1_IO__
#define __K3_ISPV1_IO__

#include "k3_ispv1_io_comm.h"

#include "k3_isp_io.h"

typedef struct _isp_io_hw {

	struct platform_device *pdev;

	u32 csi0_irq;
	u32 csi1_irq;

	struct clk *csi0_clk;
	struct clk *csi2_clk;

	struct clk *phy1_clk;
	struct clk *phy2_clk;

	u8 __iomem * csi0_base;
	u8 __iomem * csi1_base;

	sensor_ldo_t ldo[SENSOR_LDO_COUNT];

	u32 ldo_count;

#if 0 /* k3 code */
	struct iomux_block *block_i2c;
	struct iomux_block *block_isp;
	struct iomux_block *block_dvp;
	struct iomux_block *block_rst;
	struct block_config *block_conf_i2c;
	struct block_config *block_conf_isp;
	struct block_config *block_conf_dvp;
	struct block_config *block_conf_rst;
#endif


	/* pinctrl */
	struct pinctrl *isp_pinctrl;
	struct pinctrl_state *pinctrl_def;
	struct pinctrl_state *pinctrl_idle;
	int  csi_index;
} ispio_hw_t;

#endif /* __K3_ISPV1_IO__ */
