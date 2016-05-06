/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_sleepmgr.c
  版 本 号   : 初稿
  作    者   : 刘永富 56193
  生成日期   : 2012年7月25日
  最近修改   :
  功能描述   : 低功耗睡眠管理
  函数列表   :
              pwrctrl_sleep_mgr_sleep_init
              pwrctrl_sleep_mgr_tele_vote_lock
              pwrctrl_sleep_mgr_tele_vote_unlock

  修改历史   :
  1.日    期   : 2012年7月25日
    作    者   : 刘永富 56193
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#ifndef WIN32
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/cpu.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <asm/memory.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <asm/mach/time.h>
#include <mach/irqs.h>
#include <mach/hipm.h>
#include <mach/early-debug.h>
#include <linux/android_pmem.h>
#include <asm/hardware/gic.h>
#include <asm/hardware/arm_timer.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <mach/io.h>
#include <mach/gpio.h>
#include <linux/clk.h>
#endif
#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_perimgr.h>
#include <mach/pwrctrl/pwrctrl_sleepmgr.h>
#include <mach/pwrctrl/pwrctrl_sleep.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
static struct platform_suspend_ops pwrctrl_ops = {
#ifndef WIN32
    .enter      = pwrctrl_deep_sleep,
    .valid      = suspend_valid_only_mem,
#else
    0
#endif
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : PWRCTRL_SleepMgrSleepInit
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_sleep_mgr_sleep_init( void_t)
{

    /*注册休眠回调*/
    suspend_set_ops(&pwrctrl_ops);
#if 0
    pm_idle = pwrctrl_arm_sleep;
#endif
    return RET_OK;
}

/*****************************************************************************
 函 数 名  : pwrctrl_sleep_mgr_tele_vote_lock
 功能描述  : 远程投票禁止睡眠接口
 输入参数  : teleModeId         远程模块ID
             enClientId         投票模块ID
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_sleep_mgr_tele_vote_lock(PWC_TELE_SLEEP_MODE_ID_E teleModeId, PWC_TELE_SLEEP_CLIENT_ID_E enClientId)
{
    if((enClientId < PWRCTRL_TELE_SLEEP_CSIGHT0 )||(enClientId >= PWRCTRL_TELE_CLIENT_BUTT))
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_tele_vote_lock enClientId param false. \n", 0, 0, 0, 0, 0, 0);
        return RET_ERR;
    }

    if( teleModeId > PWRCTRL_TELE_REV2 )
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_tele_vote_lock teleModeId param false. \n", 0, 0, 0, 0, 0, 0);
        return RET_ERR;
    }

    pwrctrl_sleep_tele_vote_lock(teleModeId,enClientId);

    return RET_OK;

}

/*****************************************************************************
 函 数 名  : pwrctrl_sleep_mgr_tele_vote_unlock
 功能描述  : 远程投票允许睡眠接口
 输入参数  : teleModeId         远程模块ID
             enClientId         投票模块ID
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
s32_t pwrctrl_sleep_mgr_tele_vote_unlock(PWC_TELE_SLEEP_MODE_ID_E teleModeId, PWC_TELE_SLEEP_CLIENT_ID_E enClientId)
{
    if((enClientId < PWRCTRL_TELE_SLEEP_CSIGHT0 )||(enClientId >= PWRCTRL_TELE_CLIENT_BUTT))
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_tele_vote_unlock: enClientId param false. \n", 0, 0, 0, 0, 0, 0);
        return RET_ERR;
    }

    if( teleModeId > PWRCTRL_TELE_REV2 )
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_tele_vote_unlock: teleModeId param false. \n", 0, 0, 0, 0, 0, 0);
        return RET_ERR;
    }

    pwrctrl_sleep_tele_vote_unlock(teleModeId,enClientId);

    return RET_OK;
}













#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

