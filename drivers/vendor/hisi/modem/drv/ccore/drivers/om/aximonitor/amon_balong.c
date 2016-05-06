/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  amon_balong.c
*
*   作    者 :  z00212940
*
*   描    述 :  可维可测AXI Monitor
*
*   修改记录 :  2013年1月29日  v1.00  z00212940  创建
*
*************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
/*lint -save -e537*/
#include <securec.h>
#include "osl_irq.h"
#include <osl_thread.h>
#include <osl_malloc.h>
#include "bsp_memmap.h"
#include "bsp_socp.h"
#include "bsp_sysctrl.h"
#include "bsp_om_api.h"
#include "bsp_version.h"
#include "amon_balong.h"
#include "osl_malloc.h"
#include "of.h"
#include "bsp_om_api.h"
#include "securec.h"
#include <socp_balong.h>
#include "bsp_socp.h"

/*lint -restore*/
/******************************全局变量定义***********************************/
/*lint -save -e40*/
u32 g_amon_base_addr[AXI_CTRL_ADDR_BUTT];
u32 g_amon_irq = 0;
struct amon_sysctrl_struct g_amon_sysctrl;

/**********************************宏定义***********************************/
/* 初始化检查宏定义 */
/* AXI状态检查，是否正在运行，在运行时，不允许配置或者获取统计数据 */
#define AXI_CHECK_STATE(config) \
do{\
    if(MDRV_OK != axi_state_check(config))\
    {\
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: AXI %d is running\n", __FUNCTION__, config);\
        return MDRV_ERROR;\
    }\
}while(0)

/* MODE检查，只支持SOC、CPUFAST */


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
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void axi_reg_read(axi_config_enum_uint32 config, u32 reg, u32 * value)
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
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void axi_reg_write(axi_config_enum_uint32 config, u32 reg, u32 value)
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
 函 数 名  : axi_reg_getbits
 功能描述  : AXI寄存器读位操作，一次只能读一类寄存器（CPUFAST/SOC）
 输入参数  : axi_config_enum_uint32 config
             u32 reg
             u32 pos
             u32 bits
 输出参数  : u32 * value
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void axi_reg_getbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 * value)
{
    u32 reg_value = 0;

    /* 根据配置目标读取相应寄存器 */
    axi_reg_read(config, reg, &reg_value);
    /* 根据寄存器值取相应位 */
    *value = (reg_value >> pos) & (((u32)1 << (bits)) - 1);
}

/*****************************************************************************
 函 数 名  : axi_reg_setbits
 功能描述  : AXI寄存器写位操作，一次只能写一类寄存器（CPUFAST/SOC）
 输入参数  : axi_config_enum_uint32 config
             u32 reg
             u32 pos
             u32 bits
             u32 value
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void axi_reg_setbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 value)
{
    u32 reg_value = 0;

    /* 根据配置目标读取相应寄存器 */
    axi_reg_read(config, reg, &reg_value);
    /* 计算写入寄存器的目标值 */
    reg_value = (reg_value & (~((((u32)1 << (bits)) - 1) << (pos)))) | ((u32)((value) & (((u32)1 << (bits)) - 1)) << (pos));
    /* 写入目的寄存器 */
    axi_reg_write(config, reg, reg_value);
}
/*****************************************************************************
 函 数 名  : axi_sc_mon_start
 功能描述  : AXI Monitor启动通过系统控制器控制
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void axi_sc_mon_start(axi_config_enum_uint32 config)
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
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void axi_sc_mon_stop(axi_config_enum_uint32 config)
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
 函 数 名  : axi_get_state
 功能描述  : 获取AXI monitor运行/软复位状态，不能同时获取CPUFAST/SOC状态
 输入参数  : axi_config_enum_uint32 config
             axi_get_state_req_enum_uint32 state_req
 输出参数  : 无
 返 回 值  : axi_state_enum_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
axi_state_enum_uint32 axi_get_state(axi_config_enum_uint32 config, axi_get_state_req_enum_uint32 state_req)
{
    u32 reg_value = 0;

    /* 从状态寄存器获取运行状态 */
    AXI_REG_READ(config, AXI_MON_CNT_STATE_INT, &reg_value);
    /* 获取运行状态请求 */
    if(AXI_GET_RUN_STATE_REQ == state_req)
    {
        reg_value = reg_value & AXI_RUN_STATE_MASK;
    }
    /* 获取软复位状态请求 */
    else if(AXI_GET_RESET_STATE_REQ == state_req)
    {
        reg_value = reg_value & AXI_RESET_STATE_MASK;
    }
    /* 无效请求 */
    else
    {
        return (axi_state_enum_uint32)AXI_STATE_BUTT;
    }

    return reg_value;
}

/*****************************************************************************
 函 数 名  : axi_state_check
 功能描述  : 状态判定函数，是否正在运行
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
s32 axi_state_check(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;

    axi_state = axi_get_state(config, AXI_GET_RUN_STATE_REQ);
    /* AXI monitor正在运行 */
    if(axi_state != AXI_IDLE && axi_state != AXI_STOP)
    {
        return MDRV_ERROR;
    }

    return MDRV_OK;
}
/*****************************************************************************
 函 数 名  : axi_reset
 功能描述  : AXI monitor软复位
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
s32 axi_reset(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
    int i = 0;

    /* 检查运行状态 */
    AXI_CHECK_STATE(config);

    /* 软复位 */
    AXI_REG_WRITE(config, AXI_MON_CNT_RESET, AXI_SOFT_RESET);
    /* 软复位结束判定，AXI monitor状态寄存器指示软复位结束 */
    do
    {
        axi_state = axi_get_state(config, AXI_GET_RESET_STATE_REQ);
        if(AXI_RESET_FINISH == axi_state)
        {
            return MDRV_OK;
        }
    }while(i++ < AXI_WAIT_CNT);

    /* 软复位超时异常 */
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: time out\n", __FUNCTION__);
    return MDRV_ERROR;
}
s32 axi_get_irq_and_iomap(void)
{
	struct device_node *dev[AXI_CTRL_ADDR_BUTT] = {};
	const char *name[AXI_CTRL_ADDR_BUTT] = {"hisilicon,amon_fast1_balong", "hisilicon,amon_soc1_balong"};
#ifndef BSP_CONFIG_PHONE_TYPE
    char fast_reg_name[amon_cpufast_dts_butt][32] = {"amon_cpufast_srst_en","amon_cpufast_srst_dis", "amon_cpufast_monitor_start"};
#endif
    char soc_reg_name[amon_soc_dts_butt][32] = {"amon_soc_srst_en","amon_soc_srst_dis", "amon_soc_monitor_start"};
    u32 i = 0;
    u32 reg_addr[3] = {};
#ifdef BSP_CONFIG_PHONE_TYPE
    if(g_amon_base_addr[AXI_SOC_ADDR_ENUM] != 0)
    {
        return MDRV_OK;
    }

    dev[AXI_SOC_ADDR_ENUM] = of_find_compatible_node(NULL, NULL, name[AXI_SOC_ADDR_ENUM]);

    if(NULL == dev[AXI_SOC_ADDR_ENUM])
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: device node not found\n", __FUNCTION__);
        return MDRV_ERROR;
    }
    g_amon_base_addr[AXI_SOC_ADDR_ENUM] = (u32)of_iomap(dev[AXI_SOC_ADDR_ENUM], 0);

    if (0 == g_amon_base_addr[AXI_SOC_ADDR_ENUM])
    {
        amon_error("remap amon fail\n fast base addr = 0x%x soc base addr = 0x%x\n", g_amon_base_addr[AXI_FAST_ADDR_ENUM], g_amon_base_addr[AXI_SOC_ADDR_ENUM]);
        return MDRV_ERROR;
    }

    g_amon_irq = irq_of_parse_and_map(dev[AXI_SOC_ADDR_ENUM], 0);
    /*SOC相关系统控制器信息初始化*/
    for(i = 0; i < amon_soc_dts_butt; i++)
    {
        if(of_property_read_u32_array(dev[AXI_SOC_ADDR_ENUM], soc_reg_name[i], reg_addr, 3))
        {
            amon_error("Get amon dts fail, i = 0x%x\n", i);
            return MDRV_ERROR;
        }
        g_amon_sysctrl.amon_sysctrl_soc[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_soc[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_soc[i].end_bit = reg_addr[AMON_END_BIT];
    }
#else

    if((g_amon_base_addr[AXI_FAST_ADDR_ENUM] != 0)&&(g_amon_base_addr[AXI_SOC_ADDR_ENUM] != 0))
    {
        return MDRV_OK;
    }
    dev[AXI_FAST_ADDR_ENUM] = of_find_compatible_node(NULL, NULL, name[AXI_FAST_ADDR_ENUM]);
    dev[AXI_SOC_ADDR_ENUM] = of_find_compatible_node(NULL, NULL, name[AXI_SOC_ADDR_ENUM]);

    if((NULL == dev[AXI_FAST_ADDR_ENUM])||(NULL == dev[AXI_SOC_ADDR_ENUM]))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: device node not found\n", __FUNCTION__);
        return MDRV_ERROR;
    }
    g_amon_base_addr[AXI_FAST_ADDR_ENUM] = (u32)of_iomap(dev[AXI_FAST_ADDR_ENUM], 0);
    g_amon_base_addr[AXI_SOC_ADDR_ENUM] = (u32)of_iomap(dev[AXI_SOC_ADDR_ENUM], 0);

    if ((0 == g_amon_base_addr[AXI_FAST_ADDR_ENUM])||(0 == g_amon_base_addr[AXI_SOC_ADDR_ENUM]))
    {
        amon_error("remap amon fail\n fast base addr = 0x%x soc base addr = 0x%x\n", g_amon_base_addr[AXI_FAST_ADDR_ENUM], g_amon_base_addr[AXI_SOC_ADDR_ENUM]);
        return MDRV_ERROR;
    }

    g_amon_irq = irq_of_parse_and_map(dev[AXI_FAST_ADDR_ENUM], 0);
    /*SOC相关系统控制器信息初始化*/
    for(i = 0; i < amon_soc_dts_butt; i++)
    {
        if(of_property_read_u32_array(dev[AXI_SOC_ADDR_ENUM], soc_reg_name[i], reg_addr, 3))
        {
            amon_error("soc of_property_read_u32_array error\n");
            return MDRV_ERROR;
        }
        /* coverity[uninit_use_in_call] */
        g_amon_sysctrl.amon_sysctrl_soc[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_soc[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_soc[i].end_bit = reg_addr[AMON_END_BIT];
    }
    /*cpu fast相关系统控制器信息初始化*/
    for(i = 0; i < amon_cpufast_dts_butt; i++)
    {
        if(of_property_read_u32_array(dev[AXI_FAST_ADDR_ENUM], fast_reg_name[i], reg_addr, 3))
        {
            amon_error("fast of_property_read_u32_array error\n");
            return MDRV_ERROR;
        }
        /* coverity[uninit_use_in_call] */
        g_amon_sysctrl.amon_sysctrl_fast[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_fast[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_fast[i].end_bit = reg_addr[AMON_END_BIT];
    }
#endif
    return MDRV_OK;
}

/*lint -restore +e40*/
/*****************************************************************************
 函 数 名  : axi_capt_config
 功能描述  : 数采功能测试
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
*****************************************************************************/
void axi_capt_config(axi_config_enum_uint32 axi_mode,  u32 port,u32 capt_id)
{
    u32 value = 0;

    /*配置*/
    if(axi_mode == AXI_SOC_CONFIG)
    {
        amon_soc_clk_enable();
    }
    else if(axi_mode == AXI_CPUFAST_CONFIG)
    {
		amon_cpufast_clk_enable();
    }

    axi_reg_write(axi_mode, AXI_MON_CNT_RESET, 0x4);

    do{
        axi_reg_read(axi_mode, AXI_MON_CNT_RESET, &value);
    }while((value&0x4) == 0x4);

    amon_sc_reset(axi_mode);

    /*采集port 几的数据*/
    axi_reg_write(axi_mode, AXI_CAPT_TRAN_CONFIG, port);
    /*使能对id1进行数据采集 */
    axi_reg_write(axi_mode, AXI_CAPT_ID_EN, 0x1);
    /*数据采集id号掩码*/
    axi_reg_write(axi_mode, AXI_CAPT_ID(0), capt_id);
    /*屏蔽中断*/
    axi_reg_write(axi_mode, AXI_CAPT_INT_MASK, 0xFF);
    /*请中断*/
    axi_reg_write(axi_mode, AXI_CAPT_INT_CLR, 0xFF);
}
/*****************************************************************************
 函 数 名  : axi_capt_start
 功能描述  : 启动数采功能测试
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
*****************************************************************************/
void axi_capt_start(axi_config_enum_uint32 axi_mode)
{

    axi_reg_write(axi_mode, AXI_CAPT_INT_CLR, 0xFFFF);

    axi_reg_write(axi_mode, AXI_CAPT_CTRL, 0x1);
}
/*****************************************************************************
 函 数 名  : axi_capt_stop
 功能描述  : 停止数采功能测试
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
*****************************************************************************/
void axi_capt_stop(axi_config_enum_uint32 axi_mode)
{
    axi_reg_write(axi_mode, AXI_CAPT_CTRL, 0x2);
}


#if 0
extern SOCP_GBL_STATE g_strSocpStat;
void * g_dstBuf = NULL;
void * g_srcBuf = NULL;

void axi_capt_socp_config(void)
{
    u32 socpbase = g_strSocpStat.baseAddr;

    if(!g_dstBuf)
    {
        g_dstBuf = osl_malloc(0x400);
        if(!g_dstBuf)
        {
            amon_error("malloc error \n");
            return;
        }
        else
        {
            amon_error("dst buf addr = 0x%x\n", (u32)g_dstBuf);
        }
    }


    if(!g_srcBuf)
    {
        g_srcBuf = osl_malloc(0x100);
        if(!g_srcBuf)
        {
            amon_error("malloc error \n");
            return;
        }
        else
        {
            amon_error("src buf addr = 0x%x\n", (u32)g_srcBuf);
        }
    }

    /*dst*/
    writel((u32)g_dstBuf, socpbase + 0x900 + 0x20 * 2);
    writel((u32)g_dstBuf, socpbase + 0x904 + 0x20 * 2);
    writel((u32)g_dstBuf, socpbase + 0x908 + 0x20 * 2);
    writel((u32)0x400,  socpbase + 0x90C + 0x20 * 2);

    /*src*/
    writel((u32)g_srcBuf, socpbase + 0x100 + 0x40 * 11);
    writel((u32)g_srcBuf, socpbase + 0x104 + 0x40 * 11);
    writel((u32)g_srcBuf, socpbase + 0x108 + 0x40 * 11);
    writel((u32)0x100,  socpbase + 0x10C + 0x40 * 11);


}

void axi_capt_socp_start(u32 times)
{
    u32 socpbase = g_strSocpStat.baseAddr;
    u32 i = 0;

    /*start*/
    writel((u32)0x21,  socpbase + 0x110 + 0x40 * 11);

    for(i = 0; i < times; i++)
    {
        writel((u32)g_dstBuf, socpbase + 0x900 + 0x20 * 2);
        writel((u32)g_dstBuf, socpbase + 0x904 + 0x20 * 2);

        writel(0x48495349, (u32)g_srcBuf);/*hisi*/
        writel(0xF8, (u32)g_srcBuf + 0x4);/*len*/

        writel((u32)g_srcBuf + 0x100, socpbase + 0x100 + 0x40 * 11);
        writel((u32)g_srcBuf,  socpbase + 0x104 + 0x40 * 11);
    }

    /*stop*/
    writel((u32)0x20,  socpbase + 0x110 + 0x40 * 11);

    return;
}

u32 g_axi_capt_edma = 0x80204000;
void axi_capt_edma_config(u32 times)
{

    /*v722  0x80204000*/
    u32 edma_base = g_axi_capt_edma;
    /*Chicago*/
    /*u32 edma_base = 0xE0204000;*/
    u32 i = 0;

    for(i = 0; i < times; i++)
    {
        writel(0x100, edma_base + 0x810);
        writel((u32)SHM_OFFSET_MEMMGR, edma_base + 0x814);
        writel((u32)SHM_OFFSET_MEMMGR + 0x100, edma_base + 0x818);
        writel(0xC0000001, edma_base + 0x81C);
    }

    return;
}
#endif
#ifdef __cplusplus
}
#endif

