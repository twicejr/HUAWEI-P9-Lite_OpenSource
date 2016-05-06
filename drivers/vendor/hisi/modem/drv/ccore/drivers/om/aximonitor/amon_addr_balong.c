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
#include "securec.h"
#include <stdlib.h>
#include <string.h>
#include "osl_irq.h"
#include "bsp_memmap.h"
#include "bsp_om_api.h"
#include "bsp_version.h"
#include <of.h>
#include "bsp_nvim.h"
#include "drv_nv_id.h"
#include "bsp_dump.h"
#include <bsp_shared_ddr.h>
#include "bsp_dpm.h"
#include <bsp_hardtimer.h>
#include "amon_balong.h"




/* AXI状态检查，是否正在运行，在运行时，不允许配置或者获取统计数据 */
#define AXI_CHECK_STATE(config) \
do{\
    if(MDRV_OK != amon_state_check(config))\
    {\
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: AXI %d is running\n", __FUNCTION__, config);\
        return MDRV_ERROR;\
    }\
}while(0)

/* axi monitor配置 */
amon_config_stru g_amon_config;
/* 监控统计 */
amon_stat_t g_amon_stat;
/* log记录 */
amon_buff_info_t g_amon_buff;
extern u32 g_amon_irq;
#ifdef BSP_CONFIG_PHONE_TYPE
#ifdef CONFIG_CCORE_PM
axi_reg_bak_t g_st_reg_bak;
#endif
#endif

struct amon_ctrl_struct g_amon_ctrl = {};

axi_state_enum_uint32 amon_get_state(axi_config_enum_uint32 config, axi_get_state_req_enum_uint32 state_req);
s32 amon_state_check(axi_config_enum_uint32 config);
void amon_config(axi_config_enum_uint32 config);
void amon_debug_reset(void);

void read_test(u32 addr);
void write_test(u32 addr);
void read_test(u32 addr)
{
    amon_debug("read 0x%x: 0x%x", addr, readl(addr));
}
void write_test(u32 addr)
{
    writel(0x9999aaaa, addr);
}


/* K3上在modem实现dpm, V7R2在M3实现 */
#ifdef BSP_CONFIG_PHONE_TYPE
#ifdef CONFIG_CCORE_PM
s32 amon_suspend(struct dpm_device *dev);
s32 amon_resume(struct dpm_device *dev);

struct dpm_device amon_dpm_device={
	.device_name = "amon_dpm",
	.prepare = NULL,
	.suspend_late = NULL,
	.suspend = amon_suspend,
	.resume = amon_resume,
	.resume_early = NULL,
	.complete = NULL,
};
#endif
#endif

/*****************************************************************************
 函 数 名  : amon_save_log
 功能描述  : 匹配到监控项，记录log
             保存格式: timestamp    soc/cpufast    id          port
                       masterid     rd/wr          addr_start  addr_end
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void amon_save_log(axi_config_enum_uint32 mode, u32 id, u32 opt_type, amon_config_t * config)
{
    u32 * data_wr = (u32 *)(g_amon_buff.buff + g_amon_buff.write_offset);
#ifdef BSP_CONFIG_PHONE_TYPE
    u32 value = 0;
    u32 reg_value;
    u32 mask;
#endif
    if((mode == AXI_CONFIG_BUTT)&&(!(g_amon_config.en_flag&AMON_SOC_MASK)))
    {
#ifdef BSP_CONFIG_PHONE_TYPE
        if( g_amon_buff.buff_size - g_amon_buff.write_offset < 14*sizeof(u32))
        {
            data_wr = (u32*)g_amon_buff.buff;
            g_amon_buff.write_offset = 0;
        }

        if(amon_stop(AXI_SOC_CONFIG))
        {
            amon_error("stop soc monitor fail\n");
            return;
        }
        *data_wr     = 0x5A5A5A5A;

        *(data_wr+1) = om_timer_get();
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_SRC, &value);
        *(data_wr+2) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_MASK, &value);
        *(data_wr+3) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_STAT, &value);
        *(data_wr+4) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(0), &value);
        *(data_wr+5) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(0), &value);
        *(data_wr+6) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(0), &value);
        *(data_wr+7) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(0), &value);
        *(data_wr+8) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(1), &value);
        *(data_wr+9) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(1), &value);
        *(data_wr+10) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(1), &value);
        *(data_wr+11) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(1), &value);
        *(data_wr+12) = value;

        *(data_wr+13) = 0x5B5B5B5B;

        g_amon_buff.write_offset = (g_amon_buff.write_offset + 14*sizeof(u32))%(g_amon_buff.buff_size);
           /* SOC靠靠靠 */
       AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_STAT, &reg_value);
       AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_MASK, &mask);
       AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, (reg_value | mask));
       AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_MON_INT_CLR, reg_value<<16);
       system_error(DRV_ERRNO_AMON_SOC_WR,0xABCD, 0, 0, 0);
#endif
    }
    else
    {
        if(!config)
        {
             amon_error("config info is NULL\n");
             return;
        }
        if( g_amon_buff.buff_size - g_amon_buff.write_offset < 0x20)
        {
            data_wr = (u32*)g_amon_buff.buff;
            g_amon_buff.write_offset = 0;
        }

        *data_wr     = om_timer_get();
        *(data_wr+1) = mode;
        *(data_wr+2) = id;
        *(data_wr+3) = config->port;
        *(data_wr+4) = config->master_id;
        *(data_wr+5) = opt_type;
        *(data_wr+6) = config->start_addr;
        *(data_wr+7) = config->end_addr;
        g_amon_buff.write_offset = (g_amon_buff.write_offset + 0x20)%(g_amon_buff.buff_size);
    }
}

/*****************************************************************************
 函 数 名  : amon_int_handler
 功能描述  : 中断处理函数，处理读写中断
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void amon_int_handler(void)
{
    u32 i;
    u32 reg_value;
    u32 mask;

#ifdef BSP_CONFIG_PHONE_TYPE
    amon_save_log(AXI_CONFIG_BUTT, 0, 0, NULL);
#endif
    /* SOC读写中断处理 */
    AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_STAT, &reg_value);
    AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_MASK, &mask);
    AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, (reg_value | mask));
    AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_MON_INT_CLR, reg_value<<16);
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        /*lint -save -e701*/
        /* 写中断 */
        if(reg_value & (1<<(i*2)))
        {
            g_amon_stat.soc_wr_cnt[i]++;
            amon_save_log(AXI_SOC_CONFIG, (u32)i, AMON_OPT_WRITE, &g_amon_config.soc_config[i]);
            if(g_amon_config.soc_config[i].reset_flag == 1)
            {
                amon_error("soc id 0x%x wr hit, reboot\n", i);
                /* 屏蔽所有读写中断 */
                AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xffff);
                system_error(DRV_ERRNO_AMON_SOC_WR, (u32)i, 0, 0, 0);
                return;
            }
            AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_ID_INT_MASK, (u32)i*2, 1, 0);
        }
        /* 读中断 */
        if(reg_value & (1<<(i*2+1)))
        {
            g_amon_stat.soc_rd_cnt[i]++;
            amon_save_log(AXI_SOC_CONFIG, (u32)i, AMON_OPT_READ, &g_amon_config.soc_config[i]);
            if(g_amon_config.soc_config[i].reset_flag == 1)
            {
                amon_error("soc id 0x%x rd hit, reboot\n", i);
                /* 屏蔽所有读写中断 */
                AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xffff);
                system_error(DRV_ERRNO_AMON_SOC_RD, (u32)i, 1, 0, 0);
                return;
            }

            AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_ID_INT_MASK, (u32)i*2+1, 1, 0);
        }
    }

#ifndef BSP_CONFIG_PHONE_TYPE
    /* CPUFAST读写中断处理 */
    AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_ID_INT_STAT, &reg_value);
    AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, &mask);
    AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, (mask | reg_value));
    AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_MON_INT_CLR, reg_value<<16);
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        /* 写中断 */
        if(reg_value & (1<<(i*2)))
        {
            g_amon_stat.cpufast_wr_cnt[i]++;
            amon_save_log(AXI_CPUFAST_CONFIG, (u32)i, AMON_OPT_WRITE, &g_amon_config.cpufast_config[i]);
            if(g_amon_config.cpufast_config[i].reset_flag == 1)
            {
                amon_error("cpufast id 0x%x wr hit, reboot\n", i);
                /* 屏蔽所有读写中断 */
                AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, 0xffff);
                system_error(DRV_ERRNO_AMON_CPUFAST_WR, (u32)i, 2, 0, 0);
                return;
            }
            AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, (u32)i*2, 1, 0);
        }
        /* 读中断 */
        if(reg_value & (1<<(i*2+1)))
        {
            g_amon_stat.cpufast_rd_cnt[i]++;
            amon_save_log(AXI_CPUFAST_CONFIG, (u32)i, AMON_OPT_READ, &g_amon_config.cpufast_config[i]);
            if(g_amon_config.cpufast_config[i].reset_flag == 1)
            {
                amon_error("cpufast id 0x%x rd hit, reboot\n", i);
                /* 屏蔽所有读写中断 */
                AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, 0xffff);
                system_error(DRV_ERRNO_AMON_CPUFAST_RD, (u32)i, 3, 0, 0);
                return;
            }
            AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, (u32)i*2+1, 1, 0);
        }
        /*lint -restore*/
    }
#endif
}
void amon_sc_reset(axi_config_enum_uint32 config)
{
    if(AXI_SOC_CONFIG == config)
    {
        amon_soc_soft_reset();
        /* 解复位 */
        amon_soc_rls_reset();
        return;
    }
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_soft_reset();
        /* 解复位 */
        amon_cpufast_rls_reset();
        return;
    }
}

s32 amon_get_info(amon_count_stru *count)
{
    u32 i = 0;
    u32 timeDelta = 0;
    u32 startTime = 0;
    u32 endTime = 0;
	u64 temp = 0;
	u64 timeFreq = 0;

    if(amon_stop(AXI_SOC_CONFIG))
    {
        amon_error("amon stop fail\n");
        return MDRV_ERROR;
    }

    for(i = 0; i < AXI_MAX_CONFIG_ID; i++)
    {
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(i), &(count->soc_read_count[i].low_count));
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(i),&(count->soc_read_count[i].hig_count));
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(i), &(count->soc_write_count[i].low_count));
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(i),&(count->soc_write_count[i].hig_count));
    }
    /*计算从上一次到本次之间该master 口可容纳的访问的总量*/
    startTime = g_amon_ctrl.busStressTime[AXI_SOC_CONFIG][AMON_START_TIME];
    endTime = g_amon_ctrl.busStressTime[AXI_SOC_CONFIG][AMON_END_TIME];
    timeDelta = endTime > startTime ? (endTime - startTime):((0xFFFFFFFF - startTime) + endTime);
	temp = (u64)((u64)timeDelta * (u64)MODEM_PORT_WITH);
	timeFreq = (u64)STRESS_TIME_FREQ;
    count->global_access_count = temp/timeFreq;
    count->monitor_time_delta = timeDelta;
	amon_error("timeDelta = 0x%x\n", timeDelta);
    if(MDRV_OK != amon_start(AXI_SOC_CONFIG))
    {
        amon_error("soc start fail\n");
        return MDRV_ERROR;
    }
#ifndef BSP_CONFIG_PHONE_TYPE
    if(amon_stop(AXI_CPUFAST_CONFIG))
    {
        amon_error("amon stop fail id = 0x%x\n", AXI_CPUFAST_CONFIG);
        return MDRV_ERROR;
    }


    for(i = 0; i < AXI_MAX_CONFIG_ID; i++)
    {
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_RD_BYTES_ID_LOW(i), &(count->fast_read_count[i].low_count));
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(i),&(count->fast_read_count[i].hig_count));
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_WR_BYTES_ID_LOW(i), &(count->fast_write_count[i].low_count));
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(i),&(count->fast_write_count[i].hig_count));
    }
    amon_cpufast_soft_reset();
    /* 解复位 */
    amon_cpufast_rls_reset();
    if(MDRV_OK != amon_reset(AXI_CPUFAST_CONFIG))
    {
        amon_error("soc reset fail\n");
        return MDRV_ERROR;
    }
    if(MDRV_OK != amon_start(AXI_CPUFAST_CONFIG))
    {
        amon_error("soc start fail\n");
        return MDRV_ERROR;
    }

#endif
    return MDRV_OK;

}

/*****************************************************************************
 函 数 名  : 下发配置
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
/* coverity[pass by value] */
s32 amon_set_config(amon_config_stru configinfo)
{

    (void)memcpy(&g_amon_config, &configinfo, sizeof(configinfo));

    if(g_amon_config.en_flag & AMON_SOC_MASK)
    {
        amon_soc_clk_enable();

        if(amon_stop(AXI_SOC_CONFIG))
        {
            amon_error("amon stop fail id = 0x%x\n", AXI_SOC_CONFIG);
            return MDRV_ERROR;
        }
        /* SOC系统控制器复位 */
        amon_sc_reset(AXI_SOC_CONFIG);
        /* monitor内部复位 */
        if(MDRV_OK != amon_reset(AXI_SOC_CONFIG))
        {
            amon_error("soc reset fail\n");
            return MDRV_ERROR;
        }
        /* 中断屏蔽 */
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
        AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 0xF);
        amon_config(AXI_SOC_CONFIG);
    }
#ifndef BSP_CONFIG_PHONE_TYPE
     /* CPUFAST初始化 */
    if(g_amon_config.en_flag & AMON_CPUFAST_MASK)
    {
		amon_cpufast_clk_enable();
        if(amon_stop(AXI_SOC_CONFIG))
        {
            amon_error("amon stop fail\n");
            return MDRV_ERROR;
        }
        /* CPUFAST系统控制器复位 */
        amon_sc_reset(AXI_CPUFAST_CONFIG);
        if(MDRV_OK != amon_reset(AXI_CPUFAST_CONFIG))
        {
            amon_error("cpufast reset fail id = 0x%x\n", AXI_CPUFAST_CONFIG);
            return MDRV_ERROR;
        }
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_CAPT_INT_MASK, 0xF);
        AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);
        amon_config(AXI_CPUFAST_CONFIG);
    }
#endif


    return MDRV_OK;
}
/*****************************************************************************
 函 数 名  : amon_get_state
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
axi_state_enum_uint32 amon_get_state(axi_config_enum_uint32 config, axi_get_state_req_enum_uint32 state_req)
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
 函 数 名  : amon_state_check
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
s32 amon_state_check(axi_config_enum_uint32 config)
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
 函 数 名  : amon_reset
 功能描述  : monitor内部软复位
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
s32 amon_reset(axi_config_enum_uint32 config)
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
    amon_error("reset 0x%x time out\n", config);
    return MDRV_ERROR;
}

/*****************************************************************************
 函 数 名  : amon_start
 功能描述  : 启动AXI monitor，由系统控制器启动
 输入参数  : axi_config_enum_uint32 config
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
s32 amon_start(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
#ifndef CONFIG_MODULE_BUSSTRESS
    amon_config_t * amon_config_local = NULL;
    u32 reg_value = 0xffff;
#endif
    u32 i = 0;

    amon_sc_reset(config);
    if(amon_reset(config))
    {
        amon_error("soft reset error 0x%x\n", config);
    }
    /* 检查运行状态 */
    AXI_CHECK_STATE(config);

    /* 清中断 */
    AXI_REG_WRITE(config, AXI_MON_INT_CLR, 0xFFFFFFFF);
#ifndef CONFIG_MODULE_BUSSTRESS
    if(config == AXI_SOC_CONFIG)
    {
        amon_config_local = (amon_config_t *)g_amon_config.soc_config;
    }
    else
    {
        amon_config_local = (amon_config_t *)g_amon_config.cpufast_config;
    }
    /*lint -save -e701*/
    /* 解除读写中断屏蔽，根据NV配置构造 */
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        /* ID i监控读操作 */
        if(amon_config_local->opt_type & AMON_OPT_READ)
        {
            reg_value = reg_value & (~(u32)(1<<(i*2+1)));
        }
        /* ID i监控写操作 */
        if(amon_config_local->opt_type & AMON_OPT_WRITE)
        {
            reg_value = reg_value & (~(u32)(1<<(i*2)));
        }
        amon_config_local++;
    }

    AXI_REG_WRITE(config, AXI_ID_INT_MASK, reg_value);
#endif

    /* 配置系统控制器启动Monitor */
    axi_sc_mon_start(config);
    g_amon_ctrl.busStressTime[config][AMON_START_TIME] = bsp_get_slice_value_hrt();

    /* 启动结束判定，等待启动标志置位 */
    i=0;
    do
    {
        axi_state = axi_get_state(config, AXI_GET_RUN_STATE_REQ);
        if(AXI_UNWIN_RUNNING == axi_state || AXI_WIN_RUNNING == axi_state)
        {
            return MDRV_OK;
        }
    }while(i++ < AXI_WAIT_CNT);
    /*lint -restore*/
    /* 启动超时异常 */
    amon_error("start 0x%x time out\n", config);
    return MDRV_ERROR;
}

/*****************************************************************************
 函 数 名  : amon_stop
 功能描述  : 停止AXI monitor，由系统控制器停止
 输入参数  : axi_config_enum_uint32 config
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
s32 amon_stop(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
    int i = 0;

    /* 屏蔽读写中断 */
    AXI_REG_WRITE(config, AXI_ID_INT_MASK, 0xFFFFF);

    /* 配置系统控制器停止Monitor */
    axi_sc_mon_stop(config);
    g_amon_ctrl.busStressTime[config][AMON_END_TIME] = bsp_get_slice_value_hrt();

    /* 停止结束判定 */
    do
    {
        axi_state = axi_get_state(config, AXI_GET_RUN_STATE_REQ);
        if(AXI_STOP == axi_state)
        {
            /* 停止之后，强制进入IDLE态 */
            AXI_REG_WRITE(config, AXI_MON_CNT_RESET, AXI_RESET_TO_IDLE);
            return MDRV_OK;
        }
        if(AXI_IDLE == axi_state)
        {
            return MDRV_OK;
        }
    }while(i++ < AXI_WAIT_CNT);

    /* 停止Monitor超时异常 */
    amon_error("stop 0x%x time out\n", config);
    return MDRV_ERROR;
}

/*****************************************************************************
 函 数 名  : amon_config
 功能描述  : 配置monitor监控ID
 输入参数  : axi_config_enum_uint32 config
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
void amon_config(axi_config_enum_uint32 config)
{
    u32 i;

    if(AXI_SOC_CONFIG == config)
    {
        for(i=0; i<AXI_MAX_CONFIG_ID; i++)
        {
            /* 配置端口 */
            AXI_REG_SETBITS(config, AXI_MON_PORT_SEL, i*3, 3, g_amon_config.soc_config[i].port&0x7);
            /* 配置masterid */
            AXI_REG_WRITE(config, AXI_MON_CNT_ID(i), g_amon_config.soc_config[i].master_id);
            /* 配置起始地址 */
            AXI_REG_WRITE(config, AXI_MON_ID_ADDR_DES(i), g_amon_config.soc_config[i].start_addr);
            /* 配置结束地址 */
            AXI_REG_WRITE(config, AXI_MON_ID_ADDR_DES_M(i), g_amon_config.soc_config[i].end_addr);
        }
    }

    if(AXI_CPUFAST_CONFIG == config)
    {
        for(i=0; i<AXI_MAX_CONFIG_ID; i++)
        {
            /* 配置端口 */
            AXI_REG_SETBITS(config, AXI_MON_PORT_SEL, i*3, 3, g_amon_config.cpufast_config[i].port&0x7);
            /* 配置masterid */
            AXI_REG_WRITE(config, AXI_MON_CNT_ID(i), g_amon_config.cpufast_config[i].master_id);
            /* 配置起始地址 */
            AXI_REG_WRITE(config, AXI_MON_ID_ADDR_DES(i), g_amon_config.cpufast_config[i].start_addr);
            /* 配置结束地址 */
            AXI_REG_WRITE(config, AXI_MON_ID_ADDR_DES_M(i), g_amon_config.cpufast_config[i].end_addr);
        }
    }
}
s32 amon_get_clk_node(void)
{
    /*soc 时钟*/
    g_amon_ctrl.soc_clk = clk_get(NULL, "amon_soc_clk");
    if(IS_ERR(g_amon_ctrl.soc_clk))
    {
        amon_error("get amon_soc_clk fail\n");
        return MDRV_ERROR;
    }
#ifndef BSP_CONFIG_PHONE_TYPE
    /*fast 时钟*/
    g_amon_ctrl.cpufast_clk = clk_get(NULL, "amon_cpufast_clk");
    if(IS_ERR(g_amon_ctrl.cpufast_clk))
    {
        amon_error("get amon_cpufast_clk fail\n");
        return MDRV_ERROR;
    }
#endif
    return MDRV_OK;
}
/*****************************************************************************
 函 数 名  : bsp_amon_init
 功能描述  : axi monitor初始化，读取NV配置监控ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : s32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : f
    修改内容   : 新生成函数

*****************************************************************************/
s32 bsp_amon_init(void)
{

    s32 ret = 0;

    /* 判断版本 */
	g_amon_ctrl.chip_version = bsp_get_version_info()->chip_type;;

    /* 读取NV配置 */
    if(MDRV_OK != bsp_nvm_read(NV_ID_DRV_AMON, (u8*)&g_amon_config, sizeof(amon_config_stru)))
    {
        amon_error("read nv 0x%x fail\n", NV_ID_DRV_AMON);
        return MDRV_ERROR;
    }

    ret = axi_get_irq_and_iomap();

    if(MDRV_ERROR == ret)
    {
        amon_error("%s: INT number get fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }
    ret = amon_get_clk_node();
    if(MDRV_ERROR == ret)
    {
        amon_error("amon_get_clk_node fail\n");
        return ret;
    }
    if(amon_soc_state()&&(!(g_amon_config.en_flag&AMON_SOC_MASK)))
    {
        g_amon_buff.buff = (char *)bsp_dump_register_field(DUMP_CP_AMON, "AMON", 0, 0, 0x1000, (AMON_MAIN_VERSION << 8) + AMON_MINOR_VERSION);
        if(BSP_NULL == g_amon_buff.buff)
        {
            amon_error("get buffer fail\n");
            return MDRV_ERROR;
        }
        g_amon_buff.buff_size = 0x1000;

        g_amon_buff.write_offset = 0;
        (void)memset_s(g_amon_buff.buff, g_amon_buff.buff_size, 0, g_amon_buff.buff_size);

        /* 挂中断 */
        if(MDRV_OK != request_irq(g_amon_irq, (irq_handler_t)amon_int_handler, 0, "AXI_MON_IRQ", NULL))
        {
            amon_error("INT connect fail\n");
            return MDRV_ERROR;
        }

        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xFFFFFFF0);
        /* 使能monitor，注册dpm */
#ifdef BSP_CONFIG_PHONE_TYPE
#ifdef CONFIG_CCORE_PM
        if(MDRV_OK != bsp_device_pm_add(&amon_dpm_device))
        {
            amon_error("add amon_dpm_device fail\n");
            return MDRV_ERROR;
        }
        (void)memset_s(&g_st_reg_bak, sizeof(axi_reg_bak_t), 0x0, sizeof(axi_reg_bak_t));
#endif
#endif
        return MDRV_OK;
/*lint -save -e525*/
   }
/*lint -restore*/

    /* 未使能，不初始化 */
    if(g_amon_config.en_flag == 0)
    {
        return MDRV_OK;
    }

    /* SOC初始化 */
    if(g_amon_config.en_flag & AMON_SOC_MASK)
    {
        amon_soc_clk_enable();
        /* SOC系统控制器复位 */
        amon_soc_soft_reset();
        amon_soc_rls_reset();
        /* monitor内部复位 */
        if(MDRV_OK != amon_reset(AXI_SOC_CONFIG))
        {
            amon_error("soc reset fail\n");
            return MDRV_ERROR;
        }
        /* 中断屏蔽 */
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
        AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 0xF);
    }

#ifndef BSP_CONFIG_PHONE_TYPE
     /* CPUFAST初始化 */
    if(g_amon_config.en_flag & AMON_CPUFAST_MASK)
    {
		amon_cpufast_clk_enable();
        /* CPUFAST系统控制器复位 */
        amon_cpufast_soft_reset();
        amon_cpufast_rls_reset();
        if(MDRV_OK != amon_reset(AXI_CPUFAST_CONFIG))
        {
            amon_error("cpufast reset fail\n");
            return MDRV_ERROR;
        }
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_CAPT_INT_MASK, 0xF);
        AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);
    }
#endif

    g_amon_buff.buff = (char *)bsp_dump_register_field(DUMP_CP_AMON, "AMON", 0, 0, 0x1000, (AMON_MAIN_VERSION << 8) + AMON_MINOR_VERSION);
    if(BSP_NULL == g_amon_buff.buff)
    {
        amon_error("get buffer fail\n");
        return MDRV_ERROR;
    }
    g_amon_buff.buff_size = 0x1000;

    g_amon_buff.write_offset = 0;
    (void)memset_s(g_amon_buff.buff, g_amon_buff.buff_size, 0, g_amon_buff.buff_size);

    /* 挂中断 */
    if(MDRV_OK != request_irq(g_amon_irq, (irq_handler_t)amon_int_handler, 0, "AXI_MON_IRQ", NULL))
    {
        amon_error("INT connect fail\n");
        return MDRV_ERROR;
    }

    /* 启动SOC监控 */
    if(g_amon_config.en_flag & AMON_SOC_MASK)
    {
        amon_config(AXI_SOC_CONFIG);
        if(!(g_amon_config.en_flag&AMON_ENABLE_MASK))
        {
            if(MDRV_OK != amon_start(AXI_SOC_CONFIG))
            {
                amon_error("soc start fail\n");
                return MDRV_ERROR;
            }
        }
    }

#ifndef BSP_CONFIG_PHONE_TYPE
    /* 启动CPUFAST监控 */
    if(g_amon_config.en_flag & AMON_CPUFAST_MASK)
    {
        amon_config(AXI_CPUFAST_CONFIG);
        if(!(g_amon_config.en_flag&AMON_ENABLE_MASK))
        {
            if(MDRV_OK != amon_start(AXI_CPUFAST_CONFIG))
            {
                amon_error("cpufast start fail\n");
                return MDRV_ERROR;
            }
        }
    }
#endif

    amon_debug("%s init ok\n", __FUNCTION__);

    return MDRV_OK;
}

s32 amon_soft_enable(void)
{

    if(g_amon_config.en_flag & AMON_SOC_MASK)
    {
        if(MDRV_OK != amon_reset(AXI_SOC_CONFIG))
        {
            return MDRV_ERROR;
        }
        if(MDRV_OK != amon_start(AXI_SOC_CONFIG))
        {
            amon_error("soc start fail\n");
            return MDRV_ERROR;
        }
    }
#ifndef BSP_CONFIG_PHONE_TYPE
    if(g_amon_config.en_flag & AMON_CPUFAST_MASK)
    {
        if(MDRV_OK != amon_reset(AXI_CPUFAST_CONFIG))
        {
            return MDRV_ERROR;
        }
        if(MDRV_OK != amon_start(AXI_CPUFAST_CONFIG))
        {
            amon_error("cpufast start fail\n");
            return MDRV_ERROR;
        }
    }
#endif
    return MDRV_OK;
}
void amon_debug_reset(void)
{
    int i;

    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        g_amon_stat.soc_rd_cnt[i]     = 0;
        g_amon_stat.soc_wr_cnt[i]     = 0;
#ifndef BSP_CONFIG_PHONE_TYPE
        g_amon_stat.cpufast_rd_cnt[i] = 0;
        g_amon_stat.cpufast_wr_cnt[i] = 0;
#endif
    }
}

#if 0
void SRE_SetMonitor(void)
{
#ifdef BSP_CONFIG_PHONE_TYPE
    u32 value = 0;
    u32 i = 0;

    /*开钟*/
    writel(0x400000, 0xE0200024);
    /*选择哪组资源监控哪个port*/
    writel(0x2D, 0xE047601C);
    /*配置地址使能id使能*/
    writel(0x40000000, 0xE0476100);
    /*起始地址*/
    writel(0x10000000, 0xE0476104);
    /*结束地址*/
    writel(0x37FFFFFF, 0xE0476108);
    /*master id*/
    writel(0x40000000, 0xE0476200);

    writel(0x40000000, 0xE0476204);

    writel(0xDFFFFFFF, 0xE0476208);

    /*软复位*/
    value = readl(0xE0476000);
    value = value|0x2;
    writel(value, 0xE0476000);

    /*等待复位成功*/
    i = 0;
    while(i++< 0x40000)
    {
        value = readl(0xE0476008);
        if(0x10 == (value&0x10))
        {
            break;
        }
    }
    /*复位*/
    writel(0x20000000, 0xE0200060);
    /*解复位*/
    writel(0x20000000, 0xE0200064);

    /*start*/
    value = readl(0xE020040C);
    value = value|0x400;
    writel(value, 0xE020040C);

    /*等待启动*/
    i = 0;
    while(i++< 0x40000)
    {
        value = readl(0xE0476008);
        if(0x8 == (value&0xC))
        {
            break;
        }
    }
#endif
    return;
}
#endif
void amon_debug_show(void)
{
    u32 i;
    u32 reg_value_low;
    u32 reg_value_high;

    /* SOC统计信息 */

    amon_soc_clk_enable();
    amon_debug("************SOC STAT************\n");
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(i), &reg_value_low);
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(i), &reg_value_high);
        amon_debug("=======ID %d statistics=======\n", i);
        amon_debug("rd int cnt       : 0x%x\n", g_amon_stat.soc_rd_cnt[i]);
        amon_debug("wr int cnt       : 0x%x\n", g_amon_stat.soc_wr_cnt[i]);
        amon_debug("rd total bytes(h): 0x%x\n", reg_value_high);
        amon_debug("rd total bytes(l): 0x%x\n", reg_value_low);
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(i), &reg_value_low);
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(i), &reg_value_high);
        amon_debug("wr total bytes(h): 0x%x\n", reg_value_high);
        amon_debug("wr total bytes(l): 0x%x\n", reg_value_low);
    }
    amon_soc_clk_disable();

    amon_debug("\n");

#ifndef BSP_CONFIG_PHONE_TYPE

    amon_cpufast_clk_enable();

    /* CPUFAST统计信息 */
    amon_debug("************CPUFAST STAT************\n");
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_RD_BYTES_ID_LOW(i), &reg_value_low);
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(i), &reg_value_high);
        amon_debug("=======ID %d statistics=======\n", i);
        amon_debug("rd int cnt: 0x%x\n", g_amon_stat.cpufast_rd_cnt[i]);
        amon_debug("wr int cnt: 0x%x\n", g_amon_stat.cpufast_wr_cnt[i]);
        amon_debug("rd total bytes(h): 0x%x\n", reg_value_high);
        amon_debug("rd total bytes(l): 0x%x\n", reg_value_low);
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_WR_BYTES_ID_LOW(i), &reg_value_low);
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(i), &reg_value_high);
        amon_debug("wr total bytes(h): 0x%x\n", reg_value_high);
        amon_debug("wr total bytes(l): 0x%x\n", reg_value_low);
    }
    amon_cpufast_clk_disable();

#endif
}

#ifdef BSP_CONFIG_PHONE_TYPE
#ifdef CONFIG_CCORE_PM
s32 amon_suspend(struct dpm_device *dev)
{
    u32 j;
    u32 reg_value;
    /*lint -save -e958*/
    unsigned long long data_cnt;
    /*lint -restore*/
    u32 data_low;
    u32 data_high;
    axi_reg_bak_t * reg_bak;

    /* 备份前，先停止monitor */
    axi_sc_mon_stop(AXI_SOC_CONFIG);

    reg_bak = &g_st_reg_bak;
    /* 控制寄存器备份 */
    axi_reg_read(AXI_SOC_CONFIG, AXI_MON_CNT_CTRL, &(reg_bak->ctrl_reg));
    axi_reg_read(AXI_SOC_CONFIG, AXI_MON_PORT_SEL, &(reg_bak->port_reg));
    axi_reg_read(AXI_SOC_CONFIG, AXI_ID_INT_MASK, &(reg_bak->int_mask));
    for(j=0; j<AXI_MAX_CONFIG_ID; j++)
    {
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_CNT_ID(j), &(reg_bak->id_reg[j]));
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_ID_ADDR_DES(j), &(reg_bak->addr_start_reg[j]));
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_ID_ADDR_DES_M(j), &(reg_bak->addr_end_reg[j]));
    }

    /* 统计寄存器累加 */
    for(j=0; j<AXI_MAX_CONFIG_ID; j++)
    {
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR1_ID(j), &reg_value);
        reg_bak->incr1_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR2_ID(j), &reg_value);
        reg_bak->incr2_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR4_ID(j), &reg_value);
        reg_bak->incr4_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR8_ID(j), &reg_value);
        reg_bak->incr8_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR16_ID(j), &reg_value);
        reg_bak->incr16_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_WRAP_ID(j), &reg_value);
        reg_bak->wrap_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_BURST_ID(j), &reg_value);
        reg_bak->burst_send_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_FINISH_ID(j), &reg_value);
        reg_bak->burst_fin_reg[j] += reg_value;
        /* 读写数据总量40bit长度，需要计算溢出值 */
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(j), &data_low);
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(j), &data_high);
        data_cnt = (unsigned long long)data_low + (unsigned long long)reg_bak->rd_cnt_low_reg[j];
        reg_bak->rd_cnt_high_reg[j] += data_high;
        if(data_cnt >> 32)
        {
            reg_bak->rd_cnt_high_reg[j] += 1;
        }
        reg_bak->rd_cnt_low_reg[j] = (u32)data_cnt;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(j), &data_low);
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(j), &data_high);
        data_cnt = (unsigned long long)data_low + (unsigned long long)reg_bak->wr_cnt_low_reg[j];
        reg_bak->wr_cnt_high_reg[j] += data_high;
        if(data_cnt >> 32)
        {
            reg_bak->wr_cnt_high_reg[j] += 1;
        }
        reg_bak->wr_cnt_low_reg[j] = (u32)data_cnt;
    }
    /* 关闭时钟 */
    amon_soc_clk_disable();
    return MDRV_OK;
}

s32 amon_resume(struct dpm_device *dev)
{
    u32 j;
    axi_reg_bak_t * reg_bak;

    reg_bak = &g_st_reg_bak;

    /* 先打开时钟 */
    amon_soc_clk_enable();

    axi_reset(AXI_SOC_CONFIG);

    /* 恢复配置寄存器 */
    axi_reg_write(AXI_SOC_CONFIG, AXI_MON_CNT_CTRL, reg_bak->ctrl_reg);
    axi_reg_write(AXI_SOC_CONFIG, AXI_MON_PORT_SEL, reg_bak->port_reg);
    axi_reg_write(AXI_SOC_CONFIG, AXI_ID_INT_MASK, reg_bak->int_mask);
    for(j=0; j<AXI_MAX_CONFIG_ID; j++)
    {
        axi_reg_write(AXI_SOC_CONFIG, AXI_MON_CNT_ID(j), reg_bak->id_reg[j]);
        axi_reg_write(AXI_SOC_CONFIG, AXI_MON_ID_ADDR_DES(j), reg_bak->addr_start_reg[j]);
        axi_reg_write(AXI_SOC_CONFIG, AXI_MON_ID_ADDR_DES_M(j), reg_bak->addr_end_reg[j]);
    }

    /* 启动monitor */
    axi_sc_mon_start(AXI_SOC_CONFIG);

    return MDRV_OK;
}
#endif
#endif


void amon_make_pclint_happy(void)
{
    amon_cpufast_start();
    amon_soc_start();
    amon_cpufast_stop();
    amon_soc_stop();
    amon_cpufast_clk_enable();
    amon_soc_clk_enable();
    amon_cpufast_clk_disable();
    amon_soc_clk_disable();
}
#if 0
void amon_test_for_porting(void)
{
    amon_config_stru amon_config = {};

    amon_config.soc_config[0].reset_flag = 0;
    amon_config.soc_config[0].opt_type = 0x3;
    amon_config.soc_config[0].port = 0;
    amon_config.soc_config[0].master_id = 0x40000000;
    amon_config.soc_config[0].start_addr = (u32)(SHM_BASE_ADDR + SHM_OFFSET_MEMMGR);
    amon_config.soc_config[0].end_addr = (u32)(SHM_BASE_ADDR + SHM_OFFSET_MEMMGR + 0x8);

    /* 读取NV配置 */
    if(MDRV_OK != bsp_nvm_write(NV_ID_DRV_AMON, (u8*)&amon_config, sizeof(amon_config_stru)))
    {
        amon_error("write nv 0x%x fail\n", NV_ID_DRV_AMON);
        return;
    }

    (void)bsp_amon_init();

    return;
}
#endif
#ifdef __cplusplus
}
#endif

