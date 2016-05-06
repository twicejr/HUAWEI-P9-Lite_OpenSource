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
/*lint -save -e514*/
#include "bbp_osl.h"
#include "bsp_hardtimer.h"
#include "bsp_version.h"
#include "bsp_memrepair.h"
#include "hi_bbp_reg.h"
#include "bbp_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct bbp_info g_bbpinfo;

unsigned int bbp_pwrctrl_is_enabled(u32 pwr_id)
{
    unsigned int state;

    /*独立电源阈，check cmos;非独立电源阈check clk/rst;*/
    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        state = bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_bit))\
               &bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_bit));
    }
    else
    {
        state = (!bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_bit)))\
               &bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_bit));
    }

    return state;
}
void bbp_pwrctrl_enable(u32 pwr_id)
{
    u32 value = 0;
    int ret = 0;

    /*非独立电源阈则不上电、解钳位*/
    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        /*配置上电*/
        bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_bit));

        /*等待上电完成*/
        do
        {
            value = bbp_bit_get(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_bit));
        }while(value==0);

        udelay(30);
    }

    /*配置解复位*/;
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.dis_bit));

    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        /*配置嵌位不使能*/
        bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.dis_bit));
    }
    /*mem repair*/
    if(g_bbpinfo.pwr.pwr_act[pwr_id].repair_id & 0x80000000)
    {
        ret = bsp_modem_memrepair(g_bbpinfo.pwr.pwr_act[pwr_id].repair_id & 0x7fffffff);
        if(BSP_OK != ret)
        {
            bbp_print_error("pwr_id %d memrepair fail !\n",pwr_id);
        }
    }

    /*配置时钟使能*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.en_bit));
}
void bbp_pwrctrl_disable(u32 pwr_id)
{
    /*配置时钟不使能*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.dis_bit));

    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        /*配置嵌位使能*/
        bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.en_bit));
    }

    /*配置复位*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.en_bit));

    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        /*配置掉电*/
        bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.dis_bit));
    }
}
unsigned int bbp_clkctrl_is_enabled(u32 clk_id)
{
    return bbp_bit_chk(g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.state_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.state_bit);
}
void bbp_clkctrl_enable(u32 clk_id)
{
    bbp_bit_set(g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.en_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.en_bit);
}
void bbp_clkctrl_disable(u32 clk_id)
{
    bbp_bit_set(g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.dis_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.dis_bit);
}
unsigned int bbp_rstctrl_is_enabled(u32 clk_id)
{
    return bbp_bit_chk(g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.state_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.state_bit);
}
void bbp_rstctrl_enable(u32 clk_id)
{
    bbp_bit_set(g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.en_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.en_bit);
}
void bbp_rstctrl_disable(u32 clk_id)
{
    bbp_bit_set(g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.dis_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.dis_bit);
}
unsigned int bbp_clkrst_is_enabled(u32 clk_id)
{
    return bbp_clkctrl_is_enabled(clk_id) & !bbp_rstctrl_is_enabled(clk_id);
}
void bbp_clkrst_enable(u32 clk_id)
{
    bbp_rstctrl_disable(clk_id);
    bbp_clkctrl_enable(clk_id);

}
void bbp_clkrst_disable(u32 clk_id)
{
    bbp_clkctrl_disable(clk_id);
    bbp_rstctrl_enable(clk_id);
}

/*debug使用*/
#if 1
/*电源阈复位状态*/
unsigned int bbp_pwr_rst_status(u32 pwr_id)
{
    return bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_bit));
}
/*电源阈钳位状态*/
unsigned int bbp_pwr_iso_status(u32 pwr_id)
{
    return bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.state_bit));
}
/*电源阈钳位状态*/
unsigned int bbp_pwr_clk_status(u32 pwr_id)
{
    return bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_bit));
}
/*电源阈电源状态*/
unsigned int bbp_pwr_cmos_status(u32 pwr_id)
{
    unsigned int state;

    state = bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_bit))\
           &bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_bit));

    return state;
}
/*for clear pclint*/
void bbp_disable(u32 clk_id)
{
    bbp_bit_clr(g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.dis_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.dis_bit);
}
#endif

#ifdef __cplusplus
}
#endif
/*lint -restore*/
