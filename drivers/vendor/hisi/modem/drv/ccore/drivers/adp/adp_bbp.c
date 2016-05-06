/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bbp_balong.c
*
*   作    者    :  x00195528
*
*   描    述    :  本文件主要实现BBP 为上层模块提供的接口。
*                  BBP模块编译时为实际实现，否则都是打桩。
*
*   修改记录 :  2013年2月20日 创建
*************************************************************************/
/*lint --e{537}*/
//#include "mdrv_bbp.h"
//#include "mdrv_pm.h"
#include "osl_bio.h"
#include <bsp_version.h>
#include "hi_bbp.h"

#include "bsp_bbp.h"
#include "bbp_balong.h"

#ifdef CONFIG_BBP
/*上层模块调用*/
/*****************************************************************************
* 函数  : mdrv_bbp_register_lte_intr_cb
* 功能  : 被PS调用，用来向底软注册lte 1ms定时子帧中断的回调
* 输入  : pfunc
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_register_lte_intr_cb (BSPBBPIntTimerFunc pFunc)
{
    bbp_int_ltetf_regcb(pFunc);
}

/*****************************************************************************
* 函 数: mdrv_bbp_enable_lte_intr
* 功 能: 被PS调用，用来打开lte 1ms定时子帧中断
* 输入 : void
* 输出 : void
* 返回 : int
*****************************************************************************/
int mdrv_bbp_enable_lte_intr(void)
{
    return bbp_int_ltetf_enable();
}

/*****************************************************************************
* 函 数: mdrv_bbp_disable_lte_intr
* 功 能: 被PS调用，用来关闭lte 1ms定时子帧中断
* 输入 : void
* 输出 : void
* 返 回: void
*****************************************************************************/
void mdrv_bbp_disable_lte_intr(void)
{
    bbp_int_ltetf_disable();
}

/*****************************************************************************
* 函 数: mdrv_bbp_clear_lte_intr
* 功 能: 被PS调用，用来清除lte 1ms定时子帧中断
* 输入 : void
* 输出 : void
* 返 回: void
*****************************************************************************/
void mdrv_bbp_clear_lte_intr(void)
{
    bbp_int_ltetf_clear();
}
/*****************************************************************************
* 函数  : mdrv_bbp_get_lte_sysfrm
* 功能  : get system frame num
* 输入  : void
* 输出  : void
* 返回  : u16
*****************************************************************************/
unsigned short mdrv_bbp_get_lte_sysfrm(void)
{
    return bbp_get_lte_sysframe();
}

/*****************************************************************************
* 函数  : mdrv_bbp_get_lte_subfrm
* 功能  : get system sub frame num
* 输入  : void
* 输出  : void
* 返回  : u16
*****************************************************************************/
unsigned short mdrv_bbp_get_lte_subfrm(void)
{
    return bbp_get_lte_subframe();
}

/*****************************************************************************
* 函数  : mdrv_bbp_get_tds_subfrm
* 功能  : get tds system sub frame num
* 输入  : void
* 输出  : void
* 返回  : u32
*****************************************************************************/
unsigned short mdrv_bbp_get_tds_subfrm(void)
{
    return bbp_get_tds_subframe();
}
/*****************************************************************************
* 函数  : mdrv_bbp_set_tds_subfrm_offset
* 功能  : set tds system sub frame offset
* 输入  : void
* 输出  : void
* 返回  : u32
*****************************************************************************/
unsigned short mdrv_bbp_set_tds_subfrm_offset(unsigned short usOffset)
{
    return bbp_set_tds_subframe_offset(usOffset);
}
/*****************************************************************************
* 函数  : mdrv_bbp_get_sleep_period
* 功能  : get sleep period(
* 输入  : void
* 输出  : void
* 返回  : u32
*****************************************************************************/
unsigned int mdrv_bbp_get_sleep_period(void)
{
    return bbp_get_tds_sleeptime();
}

/*****************************************************************************
* 函数  : mdrv_bbp_register_tdstf_intr_cb
* 功能  : regist callback
* 输入  : void
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_register_tdstf_intr_cb(BSPBBPIntTdsFunc pFunc)
{
    bbp_int_tdstf_regcb(pFunc);
}

/*****************************************************************************
* 函数  : mdrv_bbp_enable_tdstf_intr
* 功能  : enable tdstf
* 输入  : void
* 输出  : viod
* 返回  : u32
*****************************************************************************/
int mdrv_bbp_enable_tdstf_intr(void)
{
    return bbp_int_tdstf_enable();
}

/*****************************************************************************
* 函数  : mdrv_bbp_disable_tdstf_intr
* 功能  : disable tdstf
* 输入  : void
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_disable_tdstf_intr(void)
{
    bbp_int_tdstf_disable();
}

/*****************************************************************************
* 函数  : BSP_GetTdsClkSwitchStatus
* 功能  : get tdsclk switch
* 输入  : void
* 输出  : 0表示切换到系统时钟，1表示切换到32k时钟
* 返回  : void
*****************************************************************************/
unsigned int mdrv_bbp_get_tds_clkswitchflag(void)
{
    return bbp_get_tds_clkswitch();
}

/*****************************************************************************
* 函数  : mdrv_bbp_enable_wakeup_intr
* 功能  : enable bbp wakeup int
* 输入  : void
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_E mode)
{
    bbp_int_wakeup_enable(mode);
}

/*****************************************************************************
* 函数  : mdrv_bbp_disable_wakeup_intr
* 功能  : disable bbp wakeup int
* 输入  : void
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_E mode)
{
    bbp_int_wakeup_disable(mode);
}

/*****************************************************************************
* 函数  : mdrv_bbp_clear_wakeup_intr
* 功能  : clear bbp wakeup int
* 输入  : void
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_E mode)
{
    bbp_int_wakeup_clear(mode);
}

/*****************************************************************************
* 函数  : mdrv_bbp_get_wakeup_intr_src
* 功能  : get bbp wakeup int src state
* 输入  : mode
* 输出  : 0:int not occure ; not 0:int occure
* 返回  : void
*****************************************************************************/
int mdrv_bbp_get_wakeup_intr_src(PWC_COMM_MODE_E mode)
{
    return bbp_int_wakeup_getsrc(mode);
}

/*****************************************************************************
Function:   mdrv_bbp_get_measure_flag
Description:GET CTU MEASURE FLAG
Input:
Output:     the means flag value;
Return:
Others:
*****************************************************************************/
int mdrv_bbp_get_measure_flag(PWC_COMM_MODE_E enCommMode)
 {
    return bbp_get_meansflag(enCommMode);
 }
/*****************************************************************************
* 函数  : mdrv_bbp_register_dltb_intr_cb
* 功能  : 被PS调用，用来向底软注册下行数据译码完成中断的回调
* 输入  : pfunc
* 输出  : void
* 返回  : void
* 说明  :v7r5中该中断不在arm中处理，故直接打桩
*****************************************************************************/
void mdrv_bbp_register_dltb_intr_cb(BSPBBPIntDlTbFunc pFunc)
{
    return;
}
/*****************************************************************************
* 函 数 : bsp_bbp_lps_get_ta
* 功 能 : 被lps调用,查看上行子帧头相对系统子帧头的提前量
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
int mdrv_bbp_get_lte_ta(void)
{
    return bbp_lps_get_ta();
}
/*****************************************************************************
* 函 数 : int mdrv_bbp_init_intr
* 功 能 : 挂接BBP子帧中断(T 和L)
* 输 入 : void
* 输 出 : void
* 返 回 : 0为成功，-1失败
* 说 明 :
*****************************************************************************/
int mdrv_bbp_init_intr(PWC_COMM_MODE_E mode)
{
    return bbp_int_timer_init(mode);
}
/*****************************************************************************
* 函 数 名  : mdrv_bbp_get_wakeup_time
*
* 功能描述  : 获取dsp唤醒时间
*
* 输入参数  : mode:模式 lte or tds
* 输出参数  : void
*
* 返 回 值  : 单位为32.768KHz时钟计数
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_bbp_get_wakeup_time(PWC_COMM_MODE_E mode)
{
    return bbp_get_wakeup_time(mode);
}
/*****************************************************************************
* 函 数 名  : mdrv_bbp_get_timing_val
*
* 功能描述  : L模的系统时间和32K定时查询
*
* 输入参数  : pstTiming结构体指针
* 输出参数  : pstTiming结构体定时值
*
* 返 回 值  : 0成功，其他失败
*
* 其它说明  :内部锁中断，保证锁存流程不被打断
*
*****************************************************************************/
int mdrv_bbp_get_timing_val (BBP_TIMING_STRU *pstTiming)
{
    return bbp_get_timing_val(pstTiming);
}

/***************************************************************************
 函 数 名  : DRV_PWRCTRL_BBPCLKENABLE()
 功能描述  : 打开bbp相关时钟
 输入参数  : enModeId      协议模式
             enModuleId    操作模块
             enModemId     卡号
             enChannel     channel编号
 输出参数  : 无
 返 回 值  : BBP_OK         成功
             其他           失败
**************************************************************************/
int mdrv_pm_enable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return bbp_clk_enable(enModeId, enModuleId, enModemId);
}
/***************************************************************************
 函 数 名  : mdrv_pm_disable_bbpclk()
 功能描述  : 通信模块控制BBP模块关钟
 输入参数  : enModeId      协议模式
             enModuleId    操作模块
             enModemId     卡号
             enChannel     channel编号
 输出参数  : 无
 返 回 值  : BBP_OK         成功
             其他           失败
**************************************************************************/
int mdrv_pm_disable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return bbp_clk_disable(enModeId, enModuleId, enModemId);
}
/***************************************************************************
 函 数 名  : mdrv_pm_gbbp_select_clksrc()
 功能描述  : gbbp通道选择
 输入参数  : enModemId     卡号(0/2--g0;1--g1;其他返回失败)
             enChannel     channel编号(0--chan0,1--chan1,有效，其他返回失败)
 输出参数  : 无
 返 回 值  : BBP_OK         成功
             其他           失败
**************************************************************************/
int mdrv_pm_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    return bbp_gbbp_select_clksrc(enModemId,enChannel);
}
/*不编译此模块打桩*/
#else
/*上层模块调用桩接口*/
/*****************************************************************************
* 函数  : mdrv_bbp_register_lte_intr_cb
* 功能  : 被PS调用，用来向底软注册lte 1ms定时子帧中断的回调
* 输入  : pfunc
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_register_lte_intr_cb (BSPBBPIntTimerFunc pFunc)
{
    return ;
}

/*****************************************************************************
* 函 数: mdrv_bbp_clear_lte_intr
* 功 能: 被PS调用，用来清除lte 1ms定时子帧中断
* 输入 : void
* 输出 : void
* 返 回: void
*****************************************************************************/
void mdrv_bbp_clear_lte_intr(void)
{
    return ;
}

/*****************************************************************************
* 函 数: mdrv_bbp_enable_lte_intr
* 功 能: 被PS调用，用来打开lte 1ms定时子帧中断
* 输入 : void
* 输出 : void
* 返回 : int
*****************************************************************************/
int mdrv_bbp_enable_lte_intr(void)
{
    return (BSP_S32)-1;
}

/*****************************************************************************
* 函 数: mdrv_bbp_disable_lte_intr
* 功 能: 被PS调用，用来关闭lte 1ms定时子帧中断
* 输入 : void
* 输出 : void
* 返 回: void
*****************************************************************************/
void mdrv_bbp_disable_lte_intr(void)
{
    return ;
}

/*****************************************************************************
* 函数  : mdrv_bbp_register_tdstf_intr_cb
* 功能  : regist callback
* 输入  : void
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_register_tdstf_intr_cb(BSPBBPIntTdsFunc pFunc)
{
    return ;
}

/*****************************************************************************
* 函数  : mdrv_bbp_enable_tdstf_intr
* 功能  : enable tdstf
* 输入  : void
* 输出  : viod
* 返回  : u32
*****************************************************************************/
int mdrv_bbp_enable_tdstf_intr(void)
{
    return (BSP_S32)0;
}

/*****************************************************************************
* 函数  : mdrv_bbp_disable_tdstf_intr
* 功能  : disable tdstf
* 输入  : void
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_disable_tdstf_intr(void)
{
    return ;
}
/*****************************************************************************
* 函数  : mdrv_bbp_get_lte_sysfrm
* 功能  : get system frame num
* 输入  : void
* 输出  : void
* 返回  : u32
*****************************************************************************/
unsigned short mdrv_bbp_get_lte_sysfrm(void)
{
    return (BSP_U16)0;
}

/*****************************************************************************
* 函数  : mdrv_bbp_get_lte_subfrm
* 功能  : get system sub frame num
* 输入  : void
* 输出  : void
* 返回  : u32
*****************************************************************************/
unsigned short mdrv_bbp_get_lte_subfrm(void)
{
    return (BSP_U16)0;
}

/*****************************************************************************
* 函数  : BSP_GetTdsSubFrame
* 功能  : get tds system sub frame num
* 输入  : void
* 输出  : void
* 返回  : u32
*****************************************************************************/
unsigned short mdrv_bbp_get_tds_subfrm(void)
{
    return (BSP_U16)0;
}
/*****************************************************************************
* 函数  : bsp_bbp_set_tds_subframe_offset
* 功能  : set tds system sub frame offset
* 输入  : void
* 输出  : void
* 返回  : u32
*****************************************************************************/
unsigned short mdrv_bbp_set_tds_subfrm_offset(unsigned short usOffset)
{
    return (BSP_U16)0;
}
/*****************************************************************************
* 函数  : mdrv_bbp_get_sleep_period
* 功能  : set tds system sub frame offset
* 输入  : void
* 输出  : void
* 返回  : u32
*****************************************************************************/
unsigned int mdrv_bbp_get_sleep_period(void)
{
    return 0;
}

/*****************************************************************************
* 函数  : mdrv_bbp_get_tds_clkswitchflag
* 功能  : get tdsclk switch
* 输入  : void
* 输出  : 0表示切换到系统时钟，1表示切换到32k时钟
* 返回  : void
*****************************************************************************/
unsigned int mdrv_bbp_get_tds_clkswitchflag(void)
{
    return -1;
}

/***************************************************************************
 函 数 名  : void mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_E mode)
 功能描述  : 打开bbp相关时钟
 输入参数  : enModeId      通信模式
                             enModuleId    通信模块
                             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
                         RET_ERR        失败
**************************************************************************/
void mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_E mode)
{
    return ;
}

/*****************************************************************************
* 函数  : mdrv_bbp_disable_wakeup_intr
* 功能  : disable bbp wakeup int
* 输入  : void
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_E mode)
{
    return ;
}

/*****************************************************************************
* 函数  : mdrv_bbp_clear_wakeup_intr
* 功能  : clear bbp wakeup int
* 输入  : void
* 输出  : void
* 返回  : void
*****************************************************************************/
void mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_E mode)
{
    return ;
}

/*****************************************************************************
* 函数  : mdrv_bbp_get_wakeup_intr_src
* 功能  : get bbp wakeup int src state
* 输入  : mode
* 输出  : 0:int not occure ; not 0:int occure
* 返回  : void
*****************************************************************************/
int mdrv_bbp_get_wakeup_intr_src(PWC_COMM_MODE_E mode)
{
    return 0;
}

/*****************************************************************************
Function:   mdrv_bbp_get_measure_flag(PWC_COMM_MODE_E enCommMode)
Description:
Input:
Output:     the means flag value;
Return:
Others:
*****************************************************************************/
int mdrv_bbp_get_measure_flag(PWC_COMM_MODE_E enCommMode)
{
    return (BSP_S32)0;
}
/*****************************************************************************
* 函数  : BSP_BBPIntDlTbRegCb
* 功能  : 被PS调用，用来向底软注册下行数据译码完成中断的回调
* 输入  : pfunc
* 输出  : void
* 返回  : void
* 说明  :v7r5中该中断不在arm中处理，故直接打桩
*****************************************************************************/
void mdrv_bbp_register_dltb_intr_cb(BSPBBPIntDlTbFunc pFunc)
{
    return ;
}
/*****************************************************************************
* 函 数 : BSP_BBPIntDmaInit
* 功 能 : 挂接bbp dma 中断
* 输 入 : void
* 输 出 : void
* 返 回 : 0为成功，-1失败
* 说 明 :本中断不再在arm中处理，打桩
*****************************************************************************/
int bsp_bbp_dma_int_init(void)
{
    return 0;
}
/*****************************************************************************
* 函 数 : bsp_bbp_dma_int_enable
* 功 能 : 使能bbp dma 中断
* 输 入 : void
* 输 出 : void
* 返 回 : 0为成功，-1失败
* 说 明 :
*****************************************************************************/
int bsp_bbp_dma_int_enable(void)
{
    return 0;
}

/*****************************************************************************
* 函 数 : mdrv_bbp_get_lte_ta
* 功 能 : 被lps调用,查看上行子帧头相对系统子帧头的提前量
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
int mdrv_bbp_get_lte_ta(void)
{
    return 0;
}
/*****************************************************************************
* 函 数 : mdrv_bbp_init_intr
* 功 能 : 挂接BBP子帧中断(T 和L)
* 输 入 : void
* 输 出 : void
* 返 回 : 0为成功，-1失败
* 说 明 :
*****************************************************************************/
int mdrv_bbp_init_intr(PWC_COMM_MODE_E mode)
{
    return 0;
}
/*****************************************************************************
* 函 数 名  : mdrv_bbp_get_wakeup_time
*
* 功能描述  : 获取dsp唤醒时间
*
* 输入参数  : mode:模式 lte or tds
* 输出参数  : void
*
* 返 回 值  : 单位为32.768KHz时钟计数
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_bbp_get_wakeup_time(PWC_COMM_MODE_E mode)
{
    return 0;
}
/***************************************************************************
 函 数 名  : DRV_PWRCTRL_BBPCLKENABLE()
 功能描述  : 打开bbp相关时钟
 输入参数  : enModeId      协议模式
             enModuleId    操作模块
             enModemId     卡号
             enChannel     channel编号
 输出参数  : 无
 返 回 值  : BBP_OK         成功
             其他           失败
**************************************************************************/
int mdrv_pm_enable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
/***************************************************************************
 函 数 名  : mdrv_pm_disable_bbpclk()
 功能描述  : 通信模块控制BBP模块关钟
 输入参数  : enModeId      协议模式
             enModuleId    操作模块
             enModemId     卡号
             enChannel     channel编号
 输出参数  : 无
 返 回 值  : BBP_OK         成功
             其他           失败
**************************************************************************/
int mdrv_pm_disable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}

/*****************************************************************************
* 函 数 名  : mdrv_bbp_get_timing_val
*
* 功能描述  : L模的系统时间和32K定时查询
*
* 输入参数  : pstTiming结构体指针
* 输出参数  : pstTiming结构体定时值
*
* 返 回 值  : 0成功，其他失败
*
* 其它说明  :内部锁中断，保证锁存流程不被打断
*
*****************************************************************************/
int mdrv_bbp_get_timing_val (BBP_TIMING_STRU *pstTiming)
{
    return 0;
}

/***************************************************************************
 函 数 名  : mdrv_pm_gbbp_select_clksrc()
 功能描述  : gbbp通道选择
 输入参数  : enModemId     卡号(0/2--g0;1--g1;其他返回失败)
             enChannel     channel编号(0--chan0,1--chan1,有效，其他返回失败)
 输出参数  : 无
 返 回 值  : BBP_OK         成功
             其他           失败
**************************************************************************/
int mdrv_pm_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
#endif

