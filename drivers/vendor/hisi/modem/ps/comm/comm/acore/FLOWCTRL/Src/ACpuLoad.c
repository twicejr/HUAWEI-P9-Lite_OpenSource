 

 #ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
   1 协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define THIS_FILE_ID                PS_FILE_ID_CPULOAD_C

#include "product_config.h"
#if(FEATURE_ON == FEATURE_ACPU_STAT)

/******************************************************************************
   头文件包含
******************************************************************************/

#include "vos_config.h"
#include "ACpuLoadInterface.h"
#include "ACpuLoad.h"
#include "NVIM_Interface.h"
#include "TTFTaskPriority.h"
#include "product_config.h"
#include "TtfNvInterface.h"

/*如果不是PC测试则要包含如下LINUX头文件*/
#if(VOS_WIN32 != VOS_OS_VER)
/*lint -e322 -e7*/
#include <linux/cpumask.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/irqnr.h>
#include <asm/cputime.h>
#include <linux/msa.h>
/*lint +e322 +e7*/
#else
#include "linuxstub.h"
#endif




/******************************************************************************
   2 外部函数变量声明
******************************************************************************/
/* 参考/fs/proc/stat.c实现 */
#ifndef arch_idle_time
#define arch_idle_time(cpu)         0
#endif


/*****************************************************************************
   3 私有定义
*****************************************************************************/

/*****************************************************************************
   4 全局变量定义
*****************************************************************************/

/* 根据Timer定时进行的CPU负载统计 */
CPULOAD_STAT_INFO_STRU  g_stRegularCpuLoad;

/* 实时响应用户进行的CPU负载统计 */
CPULOAD_STAT_INFO_STRU  g_stUserDefCpuLoad;

/*记录是否是第一次超时*/
VOS_INT32               g_ulFirstTimeout = VOS_TRUE;

/*回调函数指针数组*/
CPULOAD_RPT_HOOK_FUNC   g_pFunRptHooks[CPULOAD_MAX_HOOK_NUM];

/*CPU统计周期定时器*/
HTIMER                  g_stRegularCpuLoadTmr;

/*CPU LOAD NV 配置信息*/
CPULOAD_CFG_STRU        g_stNvCfg;

/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : CPULOAD_ReadCpuStat
 功能描述  : 调用系统接口读取CPU使用情况数据
 输入参数  : pstCpu -   记录两次CPU统计数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CPULOAD_ReadCpuStat(CPULOAD_STAT_INFO_STRU *pstCpu)
{
    /* V9R1项目中使用宏开关判断是否读取CPU使用情况数据 */
    /* 获取空闲任务的运行时间和总的运行时间 */
    msa_getcpu_idle(&(pstCpu->stCurrRecord.ulTotalTime), &(pstCpu->stCurrRecord.ulIdleTime));

    return;
}

/*****************************************************************************
 函 数 名  : CPULOAD_UpdateSavInfo
 功能描述  : 将上次CPU数据更新为当前数据，用于下次计算
 输入参数  : pstCpu -   记录两次CPU统计数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CPULOAD_UpdateSavInfo(CPULOAD_STAT_INFO_STRU *pstCpu)
{
    /* 更新保存的结果 */
    VOS_MemCpy(&(pstCpu->stPrevRecord), &(pstCpu->stCurrRecord), sizeof(CPULOAD_STAT_RECORD_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CPULOAD_CalLoad
 功能描述  : 计算两次读取CPU使用情况期间的CPU占用率
 输入参数  : pstCpu -   记录两次CPU统计数据
 输出参数  : 无
 返 回 值  : CPU占用率
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CPULOAD_CalLoad(CPULOAD_STAT_INFO_STRU *pstCpu)
{
    /* V9R1项目中使用宏开关进行打桩处理 */
    VOS_UINT32                          ulIdle;
    VOS_UINT32                          ulTotal;
    VOS_UINT32                          ulLoad;


    ulIdle      = MOD_SUB((pstCpu->stCurrRecord.ulIdleTime),(pstCpu->stPrevRecord.ulIdleTime),SLIENCE_MAX);
    ulTotal     = MOD_SUB((pstCpu->stCurrRecord.ulTotalTime),(pstCpu->stPrevRecord.ulTotalTime),SLIENCE_MAX);

    /* 异常保护，如果上报的tick值有问题，CPU load按照0处理，相当于把此功能off掉 */
    if (0 == ulTotal)
    {
        ulLoad = 0;

    }
    else
    {
        ulLoad = (100 * (ulTotal - ulIdle))/ulTotal;
    }

    /* 保存此次计算结果 */
    pstCpu->ulCpuLoad = ulLoad;

    return ulLoad;
}

/*****************************************************************************
 函 数 名  : CPULOAD_GetCpuLoad
 功能描述  : 返回LINUX当前CPU占用率
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CPU占用率
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CPULOAD_GetCpuLoad(VOS_VOID)
{
    /* 使用宏开关判断是否需要打桩处理 */
    return g_stRegularCpuLoad.ulCpuLoad;
}

/*****************************************************************************
 函 数 名  : CPULOAD_InvokeRtpHooks
 功能描述  : 执行注册的CPU贡载回调函数
 输入参数  : ulLoad -   当前CPU负载
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 注册的回调函数
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CPULOAD_InvokeRtpHooks(VOS_UINT32  ulLoad)
{
    VOS_UINT32                          ulHookLoop;


    for ( ulHookLoop = 0 ; ulHookLoop < CPULOAD_MAX_HOOK_NUM ; ulHookLoop++ )
    {
        if ( VOS_NULL_PTR != g_pFunRptHooks[ulHookLoop] )
        {
            g_pFunRptHooks[ulHookLoop](ulLoad);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CPULOAD_RegularTimeoutProc
 功能描述  : 计算定时时长内的CPU负载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 注册的回调函数
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CPULOAD_RegularTimeoutProc(VOS_VOID)
{
    CPULOAD_STAT_INFO_STRU             *pstCpu = &g_stRegularCpuLoad;
    VOS_UINT32                          ulLoad;

    /* 读取当前的CPU统计数据 */
    CPULOAD_ReadCpuStat(pstCpu);

    ulLoad = CPULOAD_CalLoad(pstCpu);

    /* 保存此次数据，用于与下次计算 */
    CPULOAD_UpdateSavInfo(pstCpu);

    /* 第一次收到TimeOut消息，由于上次记录为空，计算不准 */
    if ( VOS_TRUE == g_ulFirstTimeout )
    {
        g_ulFirstTimeout = VOS_FALSE;
        return;
    }

    CPULOAD_InvokeRtpHooks(ulLoad);

    return;
}

/*****************************************************************************
 函 数 名  : CPULOAD_RcvTimerExpireMsg
 功能描述  : 定时器超时消息处理
 输入参数  : pTimerMsg  -   超时消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CPULOAD_RcvTimerExpireMsg(REL_TIMER_MSG *pTimerMsg)
{
    switch (pTimerMsg->ulName)
    {
        case CPULOAD_REGULAR_TMR_NAME:
            CPULOAD_RegularTimeoutProc();
            break;
        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CPULOAD_Init
 功能描述  : 执行初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK     --  成功
             VOS_ERR    --  失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CPULOAD_Init(VOS_VOID)
{
    VOS_UINT32                          ulHookLoop;
    VOS_UINT32                          ulRtn;
    CPULOAD_CFG_STRU                   *pstNvCfg = &g_stNvCfg;

    /* CPU ID目前只有一个，赋值为0 */
    VOS_MemSet((VOS_VOID *)&g_stRegularCpuLoad, 0, sizeof(CPULOAD_STAT_INFO_STRU));
    VOS_MemSet((VOS_VOID *)&g_stUserDefCpuLoad, 0, sizeof(CPULOAD_STAT_INFO_STRU));

    for ( ulHookLoop = 0 ; ulHookLoop < CPULOAD_MAX_HOOK_NUM ; ulHookLoop++ )
    {
        g_pFunRptHooks[ulHookLoop] = VOS_NULL_PTR;
    }

    ulRtn = NV_ReadEx(MODEM_ID_0, en_NV_Item_Linux_CPU_Moniter_Timer_Len, pstNvCfg, sizeof(CPULOAD_CFG_STRU));


    /* 若读取en_NV_Item_Linux_CPU_Moniter_Timer_Len失败,或NV值非法，则使用默认值 */
    if( (NV_OK != ulRtn)
        || (CPULOAD_REGULAR_TMR_MIN_LEN > pstNvCfg->ulMonitorTimerLen)
        || (CPULOAD_REGULAR_TMR_MAX_LEN < pstNvCfg->ulMonitorTimerLen))
    {

        /*如果异常，则将定时器初始化为默认值400ms*/
        pstNvCfg->ulMonitorTimerLen = CPULOAD_REGULAR_TMR_DEF_LEN;
    }

    /* V9R1项目中使用宏开关判断是否需要启动定时器 */
    ulRtn = VOS_StartRelTimer(&g_stRegularCpuLoadTmr, ACPU_PID_CPULOAD,
                              pstNvCfg->ulMonitorTimerLen,
                              CPULOAD_REGULAR_TMR_NAME, 0,
                              VOS_RELTIMER_LOOP, VOS_TIMER_NO_PRECISION);
    if (VOS_OK != ulRtn)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CPULOAD_PidMsgProc
 功能描述  : CPU监测模块消息处理
 输入参数  : pRcvMsg    --  消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CPULOAD_PidMsgProc(MsgBlock *pRcvMsg)
{
    switch( pRcvMsg->ulSenderPid )
    {
        case VOS_PID_TIMER:
            CPULOAD_RcvTimerExpireMsg( (REL_TIMER_MSG *)pRcvMsg ); /* 接收到TIMER超时消息时的处理 */
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : CPULOAD_FidInit
 功能描述  : CPU监测FID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : l00164359
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CPULOAD_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32  ulResult = VOS_ERR;


    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:

            ulResult = VOS_RegisterPIDInfo(ACPU_PID_CPULOAD,
                                           (Init_Fun_Type)VOS_NULL_PTR,
                                           (Msg_Fun_Type)CPULOAD_PidMsgProc);
            if (VOS_OK != ulResult)
            {
                return VOS_ERR;
            }

            ulResult = VOS_RegisterTaskPrio(ACPU_FID_CPULOAD, TTF_ACPULOAD_TASK_PRIO);

            if (VOS_OK != ulResult)
            {
                return VOS_ERR;
            }

            ulResult = CPULOAD_Init();

            if (VOS_OK != ulResult)
            {
                return VOS_ERR;
            }

            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CPULOAD_RegRptHook
 功能描述  : CPU负载的回调函数注册接口
 输入参数  : pRptHook   --  回调函数
 输出参数  : 无
 返 回 值  : VOS_OK     --  成功
             VOS_ERR    --  失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CPULOAD_RegRptHook(CPULOAD_RPT_HOOK_FUNC pRptHook)
{
    VOS_UINT32                          ulHookLoop;
    VOS_INT32                           lLockKey;


    lLockKey = VOS_SplIMP();

    for ( ulHookLoop = 0 ; ulHookLoop < CPULOAD_MAX_HOOK_NUM ; ulHookLoop++ )
    {
        if ( VOS_NULL_PTR == g_pFunRptHooks[ulHookLoop] )
        {
            g_pFunRptHooks[ulHookLoop] = pRptHook;
            VOS_Splx(lLockKey);

            return VOS_OK;
        }
    }

    VOS_Splx(lLockKey);

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : CPULOAD_ResetUserDefLoad
 功能描述  : 用户控制监测时长，初始化接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CPULOAD_ResetUserDefLoad()
{
    CPULOAD_STAT_INFO_STRU             *pstCpu = &g_stUserDefCpuLoad;


    /* 读取当前的CPU统计数据 */
    CPULOAD_ReadCpuStat(pstCpu);

    /* 保存此次数据，用于与下次计算 */
    CPULOAD_UpdateSavInfo(pstCpu);

    return;
}

/*****************************************************************************
 函 数 名  : CPULOAD_GetUserDefLoad
 功能描述  : 用户控制监测时长，读取CPU负载接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 从初始化接口被调用至当前这段时期内的CPU负载
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CPULOAD_GetUserDefLoad()
{
    CPULOAD_STAT_INFO_STRU             *pstCpu = &g_stUserDefCpuLoad;
    VOS_UINT32                          ulLoad;


    /* 读取当前的CPU统计数据 */
    CPULOAD_ReadCpuStat(pstCpu);

    /* 与初始化时数据计算得到 */
    ulLoad = CPULOAD_CalLoad(pstCpu);

    /* 保存此次数据，用于与下次计算 */
    CPULOAD_UpdateSavInfo(pstCpu);

    return ulLoad;
}

/*****************************************************************************
 函 数 名  : CPULOAD_GetRegularTimerLen
 功能描述  : 返回常规定时器时长，单位毫秒
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 常规定时器时长
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CPULOAD_GetRegularTimerLen()
{
    return g_stNvCfg.ulMonitorTimerLen;
}

#else

/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "vos.h"

/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : CPULOAD_FidInit
 功能描述  : CPU监测FID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : l00164359
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CPULOAD_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    return VOS_OK;
}

#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

