/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  hi_bbp.c
*
*   作    者 :  x00195528
*
*   描    述 :
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/
/*lint -save -e537 -e656 -e801*/
#include <string.h>
#include <of.h>
#include <bsp_sysctrl.h>
#include "hi_bbp.h"
#include <bsp_version.h>
#include "bbp_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*of_bbp_init_cb_t)(struct device_node *);
extern struct bbp_info g_bbpinfo;

void  bbp_part_setup(struct device_node *dev_node)
{
    struct device_node *child_node = NULL;
    u32 id = 0;
    u32 phy_base = 0;
	u32 reg_offset = 0;
    void* reg_base = NULL;
    int ret = 0;

    if(NULL == dev_node)
    {
        bbp_print_error("dev_node is null!\n");
        return;
    }

    reg_base = of_iomap(dev_node, 0);

    if (NULL == reg_base)
    {
        bbp_print_error("remap bbp reg base fail\n");
        goto out;
    }

    ret = of_property_read_u32_index(dev_node,"reg",0,&phy_base);
    if(ret)
    {
        bbp_print_error("get bbp reg phybase fail\n");
        goto out;
    }

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node, "part_id", 0, &id);
        if(ret)
        {
            bbp_print_error("get bbp part id fail\n");
            goto out;
        }
        g_bbpinfo.part[id].id = id;

        ret = of_property_read_string_index(child_node,"part_name",0,&g_bbpinfo.part[id].name);

        ret |= of_property_read_u32_index(child_node, "reg_offset_size", 0, &reg_offset);
        g_bbpinfo.part[id].reg_base = (u32)reg_base + reg_offset;
        g_bbpinfo.part[id].reg_phyaddr= phy_base + reg_offset;
        ret |= of_property_read_u32_index(child_node, "reg_offset_size", 1, &g_bbpinfo.part[id].size);

        if(ret)
        {
            bbp_print_error("get bbp part id %d information fail!\n",id);
            goto out;
        }
    }
out:
    return;
}
void  bbp_sftpart_setup(struct device_node *dev_node)
{
    struct device_node *child_node = NULL;
    u32 id = 0;
    u32 phy_base= 0;
	u32 reg_offset = 0;
    void* reg_base = NULL;
    int ret = 0;

    if(NULL == dev_node)
    {
        bbp_print_error("dev_node is null!\n");
        return;
    }

    (void)of_property_read_u32_index(dev_node,"reg_base",0,&phy_base);
    reg_base = (void*)phy_base;

    if (NULL == reg_base)
    {
        bbp_print_error("get bbp reg base fail\n");
        goto out;
    }

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node, "part_id", 0, &id);
        if(ret)
        {
            bbp_print_error("get bbp part id fail\n");
            goto out;
        }
        g_bbpinfo.part[id].id = id;

        ret = of_property_read_string_index(child_node,"part_name",0,&g_bbpinfo.part[id].name);

        ret |= of_property_read_u32_index(child_node, "reg_offset_size", 0, &reg_offset);
        g_bbpinfo.part[id].reg_base = (u32)reg_base + reg_offset;
        g_bbpinfo.part[id].reg_phyaddr= phy_base + reg_offset;
        ret |= of_property_read_u32_index(child_node, "reg_offset_size", 1, &g_bbpinfo.part[id].size);

        if(ret)
        {
            bbp_print_error("get bbp part id %d information fail!\n",id);
            goto out;
        }
    }
out:
    return;
}
void  bbp_pwr_setup(struct device_node *dev_node)
{
    int ret = BSP_OK;
    struct device_node *child_node = NULL;
    u32 id = 0;
    u32 cri_size = sizeof(struct bbp_cri_ctrl)/4;/*dts 每个寄存器子节点的大小*/
    u32 mos_size = sizeof(struct bbp_mos_ctrl)/4;/*dts 每个寄存器子节点的大小*/
    u32 reg_from = 0;
    u32 reg_base;

    ret = of_property_read_u32_index(dev_node,"reg_from",0,&reg_from);
    if(ret)
    {
        bbp_print_error("get pwr reg_from from dts failed!\n",id);
        goto out;
    }
    if(!reg_from)/*来自于soc sctrl的空间*/
        reg_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    else/*来自于bbp sctrl的空间*/
        reg_base = (u32)bbp_part_addr_get(BBP_SCTRL);

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node, "pwr_id", 0, &id);
        if(ret)
        {
            bbp_print_error("get pwr_id form dts failed!\n",id);
            goto out;
        }
        g_bbpinfo.pwr.pwr_act[id].pwr_id = id;

        /*get repair id*/
        (void)of_property_read_u32_index(child_node, "repair_id", 0, &g_bbpinfo.pwr.pwr_act[id].repair_id);

        ret = of_property_read_string_index(child_node,"pwr_name",0,&g_bbpinfo.pwr.pwr_act[id].name);
        ret |= of_property_read_u32_array(child_node, "clk_reg_offset_bit",(u32 *)&(g_bbpinfo.pwr.pwr_act[id].clk_ctrl),cri_size);
        ret |= of_property_read_u32_array(child_node, "rst_reg_offset_bit",(u32 *)&(g_bbpinfo.pwr.pwr_act[id].rst_ctrl),cri_size);
        ret |= of_property_read_u32_array(child_node, "iso_reg_offset_bit",(u32 *)&(g_bbpinfo.pwr.pwr_act[id].iso_ctrl),cri_size);
        ret |= of_property_read_u32_array(child_node, "mos_reg_offset_bit",(u32 *)&(g_bbpinfo.pwr.pwr_act[id].mos_ctrl),mos_size);

        if(ret)
        {
            bbp_print_error("get pwr %d ctrl from dts failed!\n",id);
            goto out;
        }

        g_bbpinfo.pwr.pwr_act[id].clk_ctrl.en_reg    += reg_base;
        g_bbpinfo.pwr.pwr_act[id].clk_ctrl.dis_reg   += reg_base;
        g_bbpinfo.pwr.pwr_act[id].clk_ctrl.state_reg += reg_base;
        g_bbpinfo.pwr.pwr_act[id].rst_ctrl.en_reg    += reg_base;
        g_bbpinfo.pwr.pwr_act[id].rst_ctrl.dis_reg   += reg_base;
        g_bbpinfo.pwr.pwr_act[id].rst_ctrl.state_reg += reg_base;
        g_bbpinfo.pwr.pwr_act[id].iso_ctrl.en_reg    += reg_base;
        g_bbpinfo.pwr.pwr_act[id].iso_ctrl.dis_reg   += reg_base;
        g_bbpinfo.pwr.pwr_act[id].iso_ctrl.state_reg += reg_base;
        g_bbpinfo.pwr.pwr_act[id].mos_ctrl.en_reg    += reg_base;
        g_bbpinfo.pwr.pwr_act[id].mos_ctrl.dis_reg   += reg_base;
        g_bbpinfo.pwr.pwr_act[id].mos_ctrl.rdy_reg   += reg_base;
        g_bbpinfo.pwr.pwr_act[id].mos_ctrl.state_reg += reg_base;
    }
 out:
    return;
}
void  bbp_clk_setup(struct device_node *dev_node)
{
    int ret = BSP_OK;
    struct device_node *child_node = NULL;
    u32 id = 0;
    u32 cri_size = sizeof(struct bbp_cri_ctrl)/4;/*dts 每个寄存器子节点的大小*/
    u32 reg_from = 0;
    u32 reg_base;

    if(NULL == dev_node)
    {
        bbp_print_error("dev_node is null!\n");
        return;
    }

    ret = of_property_read_u32_index(dev_node,"reg_from",0,&reg_from);
    if(ret)
    {
        bbp_print_error("get clk reg_from from dts failed!\n",id);
        goto out;
    }
    if(!reg_from)/*来自于soc sctrl的空间*/
        reg_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    else/*来自于bbp sctrl的空间*/
        reg_base = (u32)bbp_part_addr_get(BBP_SCTRL);

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node, "clk_id", 0, &id);
        if(ret)
        {
            bbp_print_error("get clk_id form dts failed!\n",id);
            goto out;
        }
        g_bbpinfo.clk.clk_act[id].clk_id = id;

        ret = of_property_read_string_index(child_node,"clk_name",0,&g_bbpinfo.clk.clk_act[id].name);
        ret |= of_property_read_u32_array(child_node, "clk_reg_offset_bit",(u32 *)&(g_bbpinfo.clk.clk_act[id].clk_ctrl),cri_size);
        ret |= of_property_read_u32_array(child_node, "rst_reg_offset_bit",(u32 *)&(g_bbpinfo.clk.clk_act[id].rst_ctrl),cri_size);

        if(ret)
        {
            bbp_print_error("get clk %d ctrl from dts failed!\n",id);
            goto out;
        }

        g_bbpinfo.clk.clk_act[id].clk_ctrl.en_reg    += reg_base;
        g_bbpinfo.clk.clk_act[id].clk_ctrl.dis_reg   += reg_base;
        g_bbpinfo.clk.clk_act[id].clk_ctrl.state_reg += reg_base;
        g_bbpinfo.clk.clk_act[id].rst_ctrl.en_reg    += reg_base;
        g_bbpinfo.clk.clk_act[id].rst_ctrl.dis_reg   += reg_base;
        g_bbpinfo.clk.clk_act[id].rst_ctrl.state_reg += reg_base;
    }

out:
    return;
}

void  bbp_pwcmap_setup(struct device_node *dev_node)
{
    int ret = BSP_OK;

    if(NULL == dev_node)
    {
        bbp_print_error("dev_node is null!\n");
        return;
    }
    /*lint -save -e545*/
    ret  =  of_property_read_u32_array(dev_node, "pwr_map_list",(u32 *)&(g_bbpinfo.pwr.pwr_list),BBP_VOTE_PWR_NUM*BBP_MODE_NUM*BBP_MODEM_NUM*BBP_MODULE_NUM);
    if(ret)
    {
        bbp_print_error("get pwr_map_list from dts failed!\n");
        goto out;
    }
    ret  =  of_property_read_u32_array(dev_node, "clk_map_list",(u32 *)&(g_bbpinfo.clk.clk_list),BBP_VOTE_CLK_NUM*BBP_MODE_NUM*BBP_MODEM_NUM*BBP_MODULE_NUM);
    if(ret)
    {
        bbp_print_error("get clk_map_list from dts failed!\n");
        goto out;
    }
    /*lint -restore*/
 out:
    return;
}

static const struct of_device_id g_bbp_of_device_init[] =
{
        { .compatible = "hisilicon,balong_bbp_part",    .data = bbp_part_setup, },
        { .compatible = "hisilicon,balong_bbp_drxpart", .data = bbp_part_setup, },
        { .compatible = "hisilicon,balong_bbp_pwr",     .data = bbp_pwr_setup, },
        { .compatible = "hisilicon,balong_bbp_clk",     .data = bbp_clk_setup, },
        { .compatible = "hisilicon,balong_bbp_pwcmap",     .data = bbp_pwcmap_setup, },
        {},/*end*/
};
static const struct of_device_id g_bbp_of_sftgul_init[] =
{
        { .compatible = "hisilicon,balong_bbpsftgul_part",    .data = bbp_sftpart_setup, },
        {},
};

void  of_bbp_init(const struct of_device_id *matches)
{
    struct device_node *np;
    if (!matches)
    {
        return ;
    }

    for_each_matching_node(np, matches)
    {
        if (!(strcmp("bbp_last_node", np->name)))
        {
            break;
        }

        const struct of_device_id *match = of_match_node(matches, np);
        of_bbp_init_cb_t bbp_init_cb = match->data;/*lint !e158*/
        bbp_init_cb(np);
    }

    return ;
}
int bbp_dts_init(void)
{
    int ret = BSP_OK;
    struct device_node *dev_node = NULL;
    const char *name ="hisilicon,bbp_balong";
    u32 int_cells = 0;
    u32 i=0;

    dev_node = of_find_compatible_node(NULL, NULL, name);
    if(NULL == dev_node)
    {
        bbp_print_error("bbp device node not found\n");
        ret = BSP_ERROR;
        goto out;
    }
    ret = of_property_read_u32_index(dev_node, "int_cells", 0,&int_cells);
    if(ret)
    {
        bbp_print_error("read bbp int_cells form dts failed!\n");
        ret = BSP_ERROR;
        goto out;
    }
    /*通过dts获取中断号*/
    for(i = 0;i < int_cells;i++)
    {
        g_bbpinfo.bbpint[i].irq = irq_of_parse_and_map(dev_node, (int)i);
    }

    /*数据保存及恢复使用方式，1:dma,0:memcpy*/
    ret  = of_property_read_u32_index(dev_node, "dpm_dma_chan", 0, &g_bbpinfo.dpm.dma_chan);
    ret |= of_property_read_u32_index(dev_node, "dpm_ctu_savesize", 0, &g_bbpinfo.dpm.ctu_save_size);
    /*bbp电默认状态*/
    ret |= of_property_read_u32_index(dev_node, "pwr_default", 0, &g_bbpinfo.dpm.pwr_default);
    /*上下电接口可维可测是否开启*/
    ret |= of_property_read_u32_index(dev_node, "dbg_pwc", 0, &g_bbpinfo.dbg.pwc_debug);
    /*开启clk的时候是否需要解复位*/
    ret |= of_property_read_u32_index(dev_node, "clk_rst_flag", 0, &g_bbpinfo.clk.rst_flag);
    if(ret)
    {
        bbp_print_error("read bbp config form dts failed!\n");
        ret = BSP_ERROR;
        goto out;
    }

    of_bbp_init(g_bbp_of_device_init);

    if(bsp_get_version_info()->board_type == BSP_BOARD_TYPE_SFT)
    {

        of_bbp_init(g_bbp_of_sftgul_init);
    }
out:
    return ret;
}

#ifdef __cplusplus
}
#endif
/*lint -restore*/