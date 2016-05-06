/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  amon_balong.c
*
*   作    者 :  z00212940
*
*   描    述 :  可维可测AXI Monitor
*
*   修改记录 :  2013年6月6日  v1.00  z00212940  创建
*
*************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
#include <osl_bio.h>
#include <hi_syscrg_interface.h>
#include <hi_syssc_interface.h>
#include <bsp_sysctrl.h>
#include "amon_balong.h"
#include "printk.h"
#include "bsp_version.h"
#include <libfdt.h>

/* 备份恢复数据 */
axi_reg_bak_t * g_st_reg_bak = NULL;
/* 掉电前运行标志 */
u32 g_ul_running[2] = {false, false};
u32 g_ul_bak_flag[2] = {false, false};
u32 g_amon_base_addr[AXI_CTRL_ADDR_BUTT] = {};
struct amon_sysctrl_struct g_amon_sysctrl;
/*****************************************************************************
 函 数 名  : axi_reg_read
 功能描述  : AXI寄存器读操作, 一次只能读一类寄存器（CPUFAST/SOC）
 输入参数  : axi_config_enum_uint32 config
             u32 reg
 输出参数  : u32 * value
 返 回 值  : void
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
static void axi_reg_read(axi_config_enum_uint32 config, u32 reg, u32 * value)
{
    /* 根据配置目标读取相应寄存器 */
    switch(config)
    {
        /* 读取CPUFAST寄存器 */
        case AXI_CPUFAST_CONFIG:
            *value = readl(AXI_MON_CPUFAST_BASE_ADDR + reg);
            break;

        /* 读取SOC寄存器 */
        case AXI_SOC_CONFIG:
            *value = readl(AXI_MON_SOC_BASE_ADDR + reg);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : axi_reg_write
 功能描述  : AXI寄存器写操作，一次只能写一类寄存器（CPUFAST/SOC）
 输入参数  : axi_config_enum_uint32 config
             u32 reg
             u32 value
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
static void axi_reg_write(axi_config_enum_uint32 config, u32 reg, u32 value)
{
    /* 根据配置目标写入相应寄存器 */
    switch(config)
    {
        /* 写CPUFAST寄存器 */
        case AXI_CPUFAST_CONFIG:
            writel(value, AXI_MON_CPUFAST_BASE_ADDR + reg);
            break;

        /* 写SOC寄存器 */
        case AXI_SOC_CONFIG:
            writel(value, AXI_MON_SOC_BASE_ADDR + reg);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : axi_is_clk_enable
 功能描述  : 获取AXI monitor时钟状态
 输入参数  : axi_config_enum_uint32 config
 输出参数  : 无
 返 回 值  : u32 1 --- 时钟使能, 0 --- 时钟未使能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
static u32 axi_is_clk_enable(axi_config_enum_uint32 config)
{
    if(AXI_CPUFAST_CONFIG == config)
    {
        return amon_cpufast_get_clk_status();
    }

    if(AXI_SOC_CONFIG == config)
    {
        return amon_soc_get_clk_status();
    }

    return 1;
}

/*****************************************************************************
 函 数 名  : axi_clk_enable
 功能描述  : AXI monitor时钟使能
 输入参数  : axi_config_enum_uint32 config
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
static void axi_clk_enable(axi_config_enum_uint32 config)
{
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_clk_enable();
    }

    if(AXI_SOC_CONFIG == config)
    {
        amon_soc_clk_enable();
    }
}

/*****************************************************************************
 函 数 名  : axi_clk_disable
 功能描述  : AXI monitor去时钟
 输入参数  : axi_config_enum_uint32 config
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
static void axi_clk_disable(axi_config_enum_uint32 config)
{
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_clk_disable();
    }

    if(AXI_SOC_CONFIG == config)
    {
        amon_soc_clk_disable();
    }
}

/*****************************************************************************
 函 数 名  : axi_get_state
 功能描述  : 获取AXI monitor运行状态
 输入参数  : axi_config_enum_uint32 config
 输出参数  : 无
 返 回 值  : axi_state_enum_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
static axi_state_enum_uint32 axi_get_state(axi_config_enum_uint32 config)
{
    u32 reg_value = 0;

    /* 从状态寄存器获取运行状态 */
    axi_reg_read(config, AXI_MON_CNT_STATE_INT, &reg_value);

    return reg_value & 0xC;
}

/*****************************************************************************
 函 数 名  : axi_reset
 功能描述  : AXI monitor内部软复位
 输入参数  : axi_config_enum_uint32 config
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
static void axi_reset(axi_config_enum_uint32 config)
{
    /* 软复位 */
    axi_reg_write(config, AXI_MON_CNT_RESET, 0x2);
}

/*****************************************************************************
 函 数 名  : axi_sc_mon_start
 功能描述  : AXI Monitor启动通过系统控制器控制
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
static void axi_sc_mon_start(axi_config_enum_uint32 config)
{
    /* 启动CPUFAST */
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_start();
    }
    /* 启动SOC */
    else if(AXI_SOC_CONFIG == config)
    {
        amon_soc_start();
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 函 数 名  : axi_sc_mon_stop
 功能描述  : AXI Monitor停止通过系统控制器控制
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
static void axi_sc_mon_stop(axi_config_enum_uint32 config)
{
    /* 停止CPUFAST */
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_stop();
    }
    /* 停止SOC */
    else if(AXI_SOC_CONFIG == config)
    {
        amon_soc_stop();
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 函 数 名  : bsp_amon_suspend
 功能描述  : 掉电前数据备份
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void bsp_amon_suspend()
{
    u32 i;
    u32 j;
    u32 reg_value;
    /*lint -save -e958*/
    unsigned long long data_cnt;
    /*lint -restore*/
    u32 data_low;
    u32 data_high;
    axi_state_enum_uint32 state;
    u32 clk_status;
    axi_reg_bak_t * reg_bak;

    for(i=0; i<AXI_CONFIG_BUTT; i++)
    {
        reg_bak = &g_st_reg_bak[i];
        clk_status = axi_is_clk_enable(i);
        if(!clk_status)
        {
            axi_clk_enable(i);
        }

        state = axi_get_state(i);
        if(AXI_UNWIN_RUNNING != state)
        {
            g_ul_running[i] = false;

            if(!clk_status)
            {
                axi_clk_disable(i);
            }

            continue;
        }

        /* 备份前，先停止monitor */
        axi_sc_mon_stop(i);
        g_ul_running[i] = true;

        /* 控制寄存器备份 */
        axi_reg_read(i, AXI_MON_CNT_CTRL, &(reg_bak->ctrl_reg));
        axi_reg_read(i, AXI_MON_PORT_SEL, &(reg_bak->port_reg));
        axi_reg_read(i, AXI_ID_INT_MASK, &(reg_bak->int_mask));
        for(j=0; j<AXI_MAX_CONFIG_ID; j++)
        {
            axi_reg_read(i, AXI_MON_CNT_ID(j), &(reg_bak->id_reg[j]));
            axi_reg_read(i, AXI_MON_ID_ADDR_DES(j), &(reg_bak->addr_start_reg[j]));
            axi_reg_read(i, AXI_MON_ID_ADDR_DES_M(j), &(reg_bak->addr_end_reg[j]));
        }

        /* 第一次下电，清空备份区 */
        if(g_ul_bak_flag[i] == false)
        {
            g_ul_bak_flag[i] = true;
            for(j=0; j<AXI_MAX_CONFIG_ID; j++)
            {
                reg_bak->incr1_reg[j] = 0;
                reg_bak->incr2_reg[j] = 0;
                reg_bak->incr4_reg[j] = 0;
                reg_bak->incr16_reg[j] = 0;
                reg_bak->wrap_reg[j] = 0;
                reg_bak->burst_send_reg[j] = 0;
                reg_bak->burst_fin_reg[j] = 0;
                reg_bak->rd_cnt_high_reg[j] = 0;
                reg_bak->rd_cnt_low_reg[j] = 0;
                reg_bak->wr_cnt_high_reg[j] = 0;
                reg_bak->wr_cnt_low_reg[j] = 0;
            }
        }

        /* 统计寄存器累加 */
        for(j=0; j<AXI_MAX_CONFIG_ID; j++)
        {
            axi_reg_read(i, AXI_MON_INCR1_ID(j), &reg_value);
            reg_bak->incr1_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_INCR2_ID(j), &reg_value);
            reg_bak->incr2_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_INCR4_ID(j), &reg_value);
            reg_bak->incr4_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_INCR8_ID(j), &reg_value);
            reg_bak->incr8_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_INCR16_ID(j), &reg_value);
            reg_bak->incr16_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_WRAP_ID(j), &reg_value);
            reg_bak->wrap_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_BURST_ID(j), &reg_value);
            reg_bak->burst_send_reg[j] += reg_value;
            axi_reg_read(i, AXI_MON_FINISH_ID(j), &reg_value);
            reg_bak->burst_fin_reg[j] += reg_value;
            /* 读写数据总量40bit长度，需要计算溢出值 */
            axi_reg_read(i, AXI_MON_RD_BYTES_ID_LOW(j), &data_low);
            axi_reg_read(i, AXI_MON_RD_BYTES_ID_HIGH(j), &data_high);
            data_cnt = (unsigned long long)data_low + (unsigned long long)reg_bak->rd_cnt_low_reg[j];
            reg_bak->rd_cnt_high_reg[j] += data_high;
            if(data_cnt >> 32)
            {
                reg_bak->rd_cnt_high_reg[j] += 1;
            }
            reg_bak->rd_cnt_low_reg[j] = (u32)data_cnt;
            axi_reg_read(i, AXI_MON_WR_BYTES_ID_LOW(j), &data_low);
            axi_reg_read(i, AXI_MON_WR_BYTES_ID_HIGH(j), &data_high);
            data_cnt = (unsigned long long)data_low + (unsigned long long)reg_bak->wr_cnt_low_reg[j];
            reg_bak->wr_cnt_high_reg[j] += data_high;
            if(data_cnt >> 32)
            {
                reg_bak->wr_cnt_high_reg[j] += 1;
            }
            reg_bak->wr_cnt_low_reg[j] = (u32)data_cnt;
        }

        if(!clk_status)
        {
            axi_clk_disable(i);
        }
    }
}

/*****************************************************************************
 函 数 名  : bsp_amon_resume
 功能描述  : 上电恢复
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void bsp_amon_resume()
{
    u32 i;
    u32 j;
    u32 clk_status;
    axi_reg_bak_t * reg_bak;



    for(i=0; i<AXI_CONFIG_BUTT; i++)
    {
        /* 掉电前monitor未运行，不执行恢复操作 */
        if(false == g_ul_running[i])
        {
            continue;
        }

        reg_bak = &g_st_reg_bak[i];
        clk_status = axi_is_clk_enable(i);
        if(!clk_status)
        {
            axi_clk_enable(i);
        }

        axi_reset(i);

        axi_reg_write(i, AXI_MON_CNT_CTRL, reg_bak->ctrl_reg);
        axi_reg_write(i, AXI_MON_PORT_SEL, reg_bak->port_reg);
        axi_reg_write(i, AXI_ID_INT_MASK, reg_bak->int_mask);
        for(j=0; j<AXI_MAX_CONFIG_ID; j++)
        {
            axi_reg_write(i, AXI_MON_CNT_ID(j), reg_bak->id_reg[j]);
            axi_reg_write(i, AXI_MON_ID_ADDR_DES(j), reg_bak->addr_start_reg[j]);
            axi_reg_write(i, AXI_MON_ID_ADDR_DES_M(j), reg_bak->addr_end_reg[j]);
        }

        /* 启动monitor */
        axi_sc_mon_start(i);

        if(!clk_status)
        {
            axi_clk_disable(i);
        }
    }
}
s32 axi_init(void)
{
	struct device_node dev[AXI_CTRL_ADDR_BUTT] = {};
    struct device_node *node = NULL;
    char *reg_name[amon_soc_dts_butt] = {"amon_clk_en", "amon_clk_dis", "amon_clk_status", "amon_start", "dw_clk_en",
										"dw_clk_dis", "dw_clk_status"};
    u32 i = 0;
    u32 reg_addr[3] = {};

    /* 备份恢复数据 */
    g_st_reg_bak = (axi_reg_bak_t *)AXI_MON_BACK_ADDR;

    node = of_find_compatible_node(NULL, NULL, "hisilicon,amon_fast2_balong");
    if(node)
    {
        dev[AXI_FAST_ADDR_ENUM].offset = node->offset;
    }
    node = of_find_compatible_node(NULL, NULL, "hisilicon,amon_soc2_balong");
    if(node)
    {
        dev[AXI_SOC_ADDR_ENUM].offset = node->offset;
    }

	if((0 == dev[AXI_FAST_ADDR_ENUM].offset)||(0 == dev[AXI_SOC_ADDR_ENUM].offset))
	{
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: read dts error\n", __FUNCTION__);
		return BSP_ERROR;
	}
	g_amon_base_addr[AXI_FAST_ADDR_ENUM] = (u32)of_iomap(&dev[AXI_FAST_ADDR_ENUM], 0);
	g_amon_base_addr[AXI_SOC_ADDR_ENUM] = (u32)of_iomap(&dev[AXI_SOC_ADDR_ENUM], 0);

	if ((0 == g_amon_base_addr[AXI_FAST_ADDR_ENUM])||(0 == g_amon_base_addr[AXI_SOC_ADDR_ENUM]))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "remap amon fail\n fast base addr = 0x%x slow base addr = 0x%x\n", g_amon_base_addr[AXI_FAST_ADDR_ENUM], g_amon_base_addr[AXI_SOC_ADDR_ENUM]);
		return BSP_ERROR;
	}

    /*SOC相关系统控制器信息初始化*/
    for(i = 0; i < amon_soc_dts_butt; i++)
    {
        if(of_property_read_u32_array(&dev[AXI_SOC_ADDR_ENUM], reg_name[i], reg_addr, 3))
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "get soc dts fail\n");
            return BSP_ERROR;
        }
        g_amon_sysctrl.amon_sysctrl_soc[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_soc[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_soc[i].end_bit = reg_addr[AMON_END_BIT];
    }
    /*cpu fast相关系统控制器信息初始化*/
    for(i = 0; i < amon_cpufast_dts_butt; i++)
    {
        if(of_property_read_u32_array(&dev[AXI_FAST_ADDR_ENUM], reg_name[i], reg_addr, 3))
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "get fast dts fail\n");
            return BSP_ERROR;
        }
        g_amon_sysctrl.amon_sysctrl_fast[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_fast[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_fast[i].end_bit = reg_addr[AMON_END_BIT];
    }


    return BSP_OK;
}


#ifdef __cplusplus
}
#endif


