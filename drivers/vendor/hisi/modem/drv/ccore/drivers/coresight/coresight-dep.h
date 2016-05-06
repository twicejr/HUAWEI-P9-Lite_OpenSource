/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
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

#ifndef __CORESIGHT_DEP_H
#define __CORESIGHT_DEP_H
#include "bsp_sysctrl.h"

typedef struct perctrl2	
{	
    u32 phy_addr;	
    void* virt_addr;	
    u32 offset;	
    u32 pclkdbg_clkoff_sys;           /*bit 1*/	
    u32 atclkoff_sys;                 /*bit 7*/	
    u32 pclkdbg_to_modem_clk_off_sys; /*bit 17*/	
    u32 atclk_to_modem_clkoff_sys;    /*bit 16*/	
    u32 modem_cssys_rst_req;          /*bit 18*/	
    	
}per_ctrl2_cfg_t;	

typedef struct modem_sys_cfg	
{	
    void*           mdm_ctrl_sys_virt_addr;	     
	unsigned int   mdm_ctrl_sys_phy_addr;
    unsigned int   mdm_ctrl_sys_mem_size;	
    struct	
    {	
        u32 offset;	
        u32 mcpu_dbg_clk_status;	
        u32 mcpu_pd_clk_status;	
    }clk;	
    struct	
    {	
        u32 offset;	
        u32 mdma9_pd_srst_status;	
        u32 moda9_cpu_srst_status;	
    }rst;	
    struct	
    {	
        u32 offset;	
        u32 cpu_mtcmos_strl_status;	
    }mtcmos;	
}modem_sysctrl_cfg_t;

s32 coresight_get_dep_cfg(void);
s32 coresight_get_dep_status(void);

#endif
