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
#include "osl_malloc.h"
#include "of.h"
#include "securec.h"
#include "coresight-platform.h"
#include "coresight-dep.h"

/*lint --e{801, 830, 525, 534, 586, 522}*/

per_ctrl2_cfg_t g_perctrl2_reg = {0,};
modem_sysctrl_cfg_t  g_modem_sysctrl_cfg;

u32 g_perctrl_reg_val = 0;
u32 g_modem_sys_val[3] = {};




s32 coresight_perctrl2_memmap(void)
{
    char* name = "coresight,extern-status";    
    struct device_node* perctrl2_node    = NULL;
    
    unsigned int reg_data[2] = {0,};
    
    perctrl2_node = of_find_compatible_node(NULL, NULL, name);
    if(NULL == perctrl2_node)
    {
        cs_error("perctrl2_node error: of_find_compatible_node failed.\r\n");
        return BSP_ERROR;
    }

    if(of_property_read_u32_array(perctrl2_node, "reg", reg_data, 2))
    {
            cs_error(" cs get dts reg error\n");
            return BSP_ERROR;
    }
    g_perctrl2_reg.phy_addr = reg_data[0];
    g_perctrl2_reg.virt_addr = bsp_sysctrl_addr_get((void*)reg_data[0]);
    
    (void)of_property_read_u32_index(perctrl2_node, "offset", 0,&g_perctrl2_reg.offset);
    
    (void)of_property_read_u32_index(perctrl2_node, "pclkdbg_clkoff_sys", 0,&g_perctrl2_reg.pclkdbg_clkoff_sys);
    
    (void)of_property_read_u32_index(perctrl2_node, "atclkoff_sys", 0,&g_perctrl2_reg.atclkoff_sys);
    
    (void)of_property_read_u32_index(perctrl2_node, "pclkdbg_to_modem_clk_off_sys", 0,&g_perctrl2_reg.pclkdbg_to_modem_clk_off_sys);
    
    (void)of_property_read_u32_index(perctrl2_node, "atclk_to_modem_clkoff_sys", 0,&g_perctrl2_reg.atclk_to_modem_clkoff_sys);
    
    (void)of_property_read_u32_index(perctrl2_node, "modem_cssys_rst_req", 0,&g_perctrl2_reg.modem_cssys_rst_req);

    cs_error("phy_addr = 0x%x,virt_addr = 0x%x,g_perctrl2_reg.offset = 0x%x\n",g_perctrl2_reg.phy_addr ,g_perctrl2_reg.virt_addr,g_perctrl2_reg.offset );
    cs_error("pclkdbg_clkoff_sys = 0x%x\n",g_perctrl2_reg.pclkdbg_clkoff_sys);
    cs_error("atclkoff_sys = 0x%x\n",g_perctrl2_reg.atclkoff_sys);
    cs_error("pclkdbg_to_modem_clk_off_sys = 0x%x\n",g_perctrl2_reg.pclkdbg_to_modem_clk_off_sys);
    cs_error("modem_cssys_rst_req = 0x%x\n",g_perctrl2_reg.modem_cssys_rst_req );    
    cs_error("atclk_to_modem_clkoff_sys = 0x%x\n",g_perctrl2_reg.atclk_to_modem_clkoff_sys);

    return BSP_OK;

}

/* coresight intialization */

s32 coresight_modem_sysctrl_memmap(void)
{
    struct device_node* sysctrl_node = NULL;
    unsigned int reg_data[2] = {0,};
    unsigned int rst_data[3] = {0,};
    char* name = "modem,sysctrl_cfg";
    memset_s(&g_modem_sysctrl_cfg,sizeof(g_modem_sysctrl_cfg),'\0',sizeof(g_modem_sysctrl_cfg));
    sysctrl_node = of_find_compatible_node(NULL, NULL, name);
    if(sysctrl_node)
    {
        if(of_property_read_u32_array(sysctrl_node, "reg", reg_data, 2))
        {
            printk(" cs get dts reg error\n");
            return BSP_ERROR;
        }
        g_modem_sysctrl_cfg.mdm_ctrl_sys_phy_addr  = (reg_data[0]);
        g_modem_sysctrl_cfg.mdm_ctrl_sys_mem_size  = reg_data[1];
        g_modem_sysctrl_cfg.mdm_ctrl_sys_virt_addr = bsp_sysctrl_addr_get((void*)g_modem_sysctrl_cfg.mdm_ctrl_sys_phy_addr);

        if(of_property_read_u32_array(sysctrl_node, "clk", rst_data, 3))
        {
            memset_s(&g_modem_sysctrl_cfg,sizeof(g_modem_sysctrl_cfg),0,sizeof(g_modem_sysctrl_cfg));
            cs_error(" cs get dts clk error\n");
            return BSP_ERROR;
        }
        g_modem_sysctrl_cfg.clk.offset = (rst_data[0]);
        g_modem_sysctrl_cfg.clk.mcpu_dbg_clk_status = (rst_data[1]);
        g_modem_sysctrl_cfg.clk.mcpu_pd_clk_status = (rst_data[2]);

        memset_s(rst_data,sizeof(rst_data),0,sizeof(rst_data));
        if(of_property_read_u32_array(sysctrl_node, "reset", rst_data, 3))
        {
            memset_s(&g_modem_sysctrl_cfg,sizeof(g_modem_sysctrl_cfg),0,sizeof(g_modem_sysctrl_cfg));
            cs_error(" cs get dts reset error\n");
            return BSP_ERROR;
        }

        g_modem_sysctrl_cfg.rst.offset = (rst_data[0]);
        g_modem_sysctrl_cfg.rst.mdma9_pd_srst_status = (rst_data[1]);
        g_modem_sysctrl_cfg.rst.moda9_cpu_srst_status = (rst_data[2]);

        if(of_property_read_u32_array(sysctrl_node, "mtcmos", reg_data, 2))
        {
            memset_s(&g_modem_sysctrl_cfg,sizeof(g_modem_sysctrl_cfg),0,sizeof(g_modem_sysctrl_cfg));
            printk(" cs get dts tcmos error\n");
            return BSP_ERROR;
        }
        g_modem_sysctrl_cfg.mtcmos.offset = (reg_data[0]);
        g_modem_sysctrl_cfg.mtcmos.cpu_mtcmos_strl_status = (reg_data[1]);
    }
    else
    {
        printk("can not find dts\n");
        return BSP_OK;
    }

    cs_error("mdm_ctrl_sys_phy_addr = 0x%x,mdm_ctrl_sys_virt_addr = 0x%p\n",g_modem_sysctrl_cfg.mdm_ctrl_sys_phy_addr,g_modem_sysctrl_cfg.mdm_ctrl_sys_virt_addr);
    cs_error("clk.offset = 0x%x,clk.mcpu_dbg_clk_en = %d,clk.mcpu_pd_clk_en=%d\n",g_modem_sysctrl_cfg.clk.offset,g_modem_sysctrl_cfg.clk.mcpu_dbg_clk_status,g_modem_sysctrl_cfg.clk.mcpu_pd_clk_status);
    cs_error("rst.offset = 0x%x,rst.mdma9_pd_srst_en= %d,rst.moda9_cpu_srst_en =%d\n",g_modem_sysctrl_cfg.rst.offset,g_modem_sysctrl_cfg.rst.mdma9_pd_srst_status,g_modem_sysctrl_cfg.rst.moda9_cpu_srst_status);
    cs_error("mtcmos.offset=0x%x,mtcmos.cpu_mtcmos_strl_dis =%d\n",g_modem_sysctrl_cfg.mtcmos.offset,g_modem_sysctrl_cfg.mtcmos.cpu_mtcmos_strl_status);

    return BSP_OK;
}

s32 coresight_get_sysctrl_status(void)
{

    u32 clk = 0;
    u32 rst = 0;
    u32 tcmos = 0;

    if(g_modem_sysctrl_cfg.mdm_ctrl_sys_virt_addr == NULL)
    {
        printk("sys ctrl base addr is null\n");
        return BSP_ERROR;
    }
    clk = readl((u32)((u32)g_modem_sysctrl_cfg.mdm_ctrl_sys_virt_addr + g_modem_sysctrl_cfg.clk.offset));

    rst = readl((u32)((u32)g_modem_sysctrl_cfg.mdm_ctrl_sys_virt_addr + g_modem_sysctrl_cfg.rst.offset));

    tcmos = readl((u32)((u32)g_modem_sysctrl_cfg.mdm_ctrl_sys_virt_addr + g_modem_sysctrl_cfg.mtcmos.offset));

    g_modem_sys_val[0] = clk;
    g_modem_sys_val[1] = rst;
    g_modem_sys_val[2] = tcmos;


    if(!BVAL(clk, g_modem_sysctrl_cfg.clk.mcpu_dbg_clk_status))
    {
        cs_error("clk = %x,rst = %x,tcmos = %x\n",clk,rst,tcmos);
        cs_error("modem a9 mcpu_dbg_clk_status is disable,mcpu_dbg_clk_status=0x%x status=0x%x\n",g_modem_sysctrl_cfg.clk.mcpu_dbg_clk_status,clk);
        return BSP_ERROR;
    }
    if(!BVAL(clk, g_modem_sysctrl_cfg.clk.mcpu_pd_clk_status))
    {
        cs_error("clk = %x,rst = %x,tcmos = %x\n",clk,rst,tcmos);
        cs_error("modem a9 mcpu_pd_clk_status is disable,bit=0x%x status=0x%x\n",g_modem_sysctrl_cfg.clk.mcpu_pd_clk_status,clk);
        return BSP_ERROR;
    }
    if(BVAL(rst, g_modem_sysctrl_cfg.rst.mdma9_pd_srst_status))
    {
        cs_error("clk = %x,rst = %x,tcmos = %x\n",clk,rst,tcmos);
        cs_error("modem a9 mdma9_pd_srst_status is disable,bit=0x%x status =0x%x\n",g_modem_sysctrl_cfg.rst.mdma9_pd_srst_status,rst);
        return BSP_ERROR;
    }
    if(BVAL(rst, g_modem_sysctrl_cfg.rst.moda9_cpu_srst_status))
    {
        cs_error("clk = %x,rst = %x,tcmos = %x\n",clk,rst,tcmos);
        cs_error("modem a9 moda9_cpu_srst_status is disable,bit=0x%x status =0x%x\n",g_modem_sysctrl_cfg.rst.moda9_cpu_srst_status,rst);
        return BSP_ERROR;
    }
    if(!BVAL(tcmos, g_modem_sysctrl_cfg.mtcmos.cpu_mtcmos_strl_status))
    {
        cs_error("clk = %x,rst = %x,tcmos = %x\n",clk,rst,tcmos);
        cs_error("modem a9 moda9_cpu_srst_status is disable,bit=0x%x status = 0x%x",g_modem_sysctrl_cfg.mtcmos.cpu_mtcmos_strl_status,tcmos);
        return BSP_ERROR;
    }

    return BSP_OK;
}
s32 coresight_get_perctrl2_status(void)
{
    u32 status = 0;
    
    if(g_perctrl2_reg.virt_addr == 0)
    {     
        cs_error("base addr is  null.\r\n");
        return BSP_ERROR;
    }
    
    status = readl((u32)((u32)g_perctrl2_reg.virt_addr + g_perctrl2_reg.offset));
    g_perctrl_reg_val = status;
    if(!BVAL(status, g_perctrl2_reg.pclkdbg_clkoff_sys))
    {   
        cs_error("status = 0x%x \n",status);
        cs_error("g_perctrl2_reg.pclkdbg_clkoff_sys is 0\n");
        return BSP_ERROR;
    }
    if(!BVAL(status, g_perctrl2_reg.atclkoff_sys))
    {
        cs_error("status = 0x%x \n",status);
        cs_error("g_perctrl2_reg.atclkoff_sys is 0\n");
        return BSP_ERROR;
    }
    if(!BVAL(status, g_perctrl2_reg.pclkdbg_to_modem_clk_off_sys))
    {
        cs_error("status = 0x%x \n",status);
        cs_error("g_perctrl2_reg.pclkdbg_to_modem_clk_off_sys is 0\n");
        return BSP_ERROR;
    }
    if(!BVAL(status, g_perctrl2_reg.atclk_to_modem_clkoff_sys))
    {
        cs_error("status = 0x%x \n",status);
        cs_error("g_perctrl2_reg.atclk_to_modem_clkoff_sys is 0\n");
        return BSP_ERROR;
    }
    if(BVAL(status, g_perctrl2_reg.modem_cssys_rst_req))
    {
        cs_error("status = 0x%x \n",status);
        cs_error("g_perctrl2_reg.modem_cssys_rst_req is 1\n");
        return BSP_ERROR;
    }
    return BSP_OK;

}

s32 coresight_get_dep_cfg(void)
{
    s32 ret = BSP_ERROR;
    ret = coresight_modem_sysctrl_memmap();
    ret |=coresight_perctrl2_memmap();
    return ret;

}

s32 coresight_get_dep_status(void)
{
    s32 ret = BSP_ERROR;
    ret = coresight_get_perctrl2_status();
    ret |= coresight_get_sysctrl_status();
    return ret;
}

