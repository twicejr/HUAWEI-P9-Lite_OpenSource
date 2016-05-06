/*
 * PCIe host controller driver for Kirin 960 SoCs
 *
 * Copyright (C) 2015 Huawei Electronics Co., Ltd.
 *		http://www.huawei.com
 *
 * Author: Xiaowei Song <songxiaowei@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _PCIE_KIRIN_H
#define _PCIE_KIRIN_H

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/irqdomain.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/pci.h>
#include <linux/of_pci.h>
#include <linux/platform_device.h>
#include <linux/resource.h>
#include <linux/signal.h>
#include <linux/types.h>

#include "pcie-designware.h"

#define to_kirin_pcie(x)	container_of(x, struct kirin_pcie, pp)

struct kirin_pcie {
	void __iomem		*apb_base;
	void __iomem		*phy_base;
	void __iomem		*crg_base;
	void __iomem        *sctrl_base;
	void __iomem        *pmctrl_base;
	struct clk			*io_clk;
	struct clk			*apb_sys_clk;
	struct clk			*apb_phy_clk;
	struct clk			*phy_ref_clk;
	struct clk			*pcie_aclk;
	struct regulator	*vp_pcie;
	struct regulator	*vptxn_pcie;
	struct regulator	*avdd18_pcie;
	int					fpga_flag;
	int                 ep_flag;
	struct  pcie_port	pp;
};

#define PCIE_PR_ERR(fmt, args ...)	do{	printk(KERN_ERR "%s(%d):" fmt "\n", __FUNCTION__, __LINE__, ##args); } while(0)
#define PCIE_PR_INFO(fmt, args ...)	do{	printk(KERN_ERR "%s(%d):" fmt "\n", __FUNCTION__, __LINE__, ##args); } while(0)
#define PCIE_PR_DEBUG(fmt, args ...)	do{	printk(KERN_DEBUG "%s(%d):" fmt "\n", __FUNCTION__, __LINE__, ##args); } while(0)

#endif
