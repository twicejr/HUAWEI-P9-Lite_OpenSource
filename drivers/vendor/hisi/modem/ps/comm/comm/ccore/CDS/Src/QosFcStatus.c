/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : QosFcStatus.c
  版 本 号   : 初稿
  作    者   : w00145177
  生成日期   : 2011年12月23日
  最近修改   :
  功能描述   : QoS流控状态管理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月23日
    作    者   : w00145177
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "CDS.h"
#include "QosFcCommon.h"
#include "QosFcStatus.h"
#include "QosFcRabStatus.h"
#include "QosFcChannelFlowCtrl.h"
#include "FcFlowCtrlMana.h"


/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_QOS_FC_STATUS_C
/*lint +e767*/

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/
extern  FLOWCTRL_CDS_CONFIG_STRU        g_stFcCdsConfig;
VOS_VOID QosFc_FlowCtrlProc(VOS_UINT32 ulMemRemain, VOS_UINT32 *pRestoreCnt);
/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
******************************************************************************/
QOS_FC_CONTROL_STRU g_stQosFcCtrl = {0};

/******************************************************************************
   5 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : QosFc_RestartCheckTmr
 功能描述  : 重启流控检查触发定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月27日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 QosFc_RestartCheckTmr(VOS_VOID)
{
    /*已运行*/
    if (VOS_NULL_PTR != g_stQosFcCtrl.hTimer)
    {
        (VOS_VOID)PS_STOP_REL_TIMER(&(g_stQosFcCtrl.hTimer));
    }

    if (VOS_OK != PS_START_REL_TIMER(&(g_stQosFcCtrl.hTimer),
                                    UEPS_PID_CDS,
                                    g_stQosFcCtrl.ulTimerLen,
                                    CDS_TMR_ID_FC_CHECK_TMR,
                                    0,
                                    VOS_RELTIMER_NOLOOP))
    {
        /*ERROR LOG*/
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_RestartCheckTmr : Fail to Start FC Tmr.");
        CDS_PRINT_ERROR(QosFc_RestartCheckTmr_ENUM,CDS_START_TIMER_ERROR);
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : QosFc_FlowCtrl
 功能描述  : 流控新周期内存检查
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_FlowCtrl(VOS_VOID)
{
    static VOS_UINT32 ulRestoreCnt = 0;
    VOS_UINT32 ulMemRemain;

    if(VOS_TRUE != g_stQosFcCtrl.bQosFcEnable)
    {
        /* 流控没打开，不进流控状态 */
        return;
    }

    ulMemRemain = TTF_GetUlIpFreeMemCnt();

    /* 快速处理 */
    if(g_stQosFcCtrl.ulRandomDiscardThres <= ulMemRemain)
    {
        if(QOS_FC_STATE_NORMAL == g_stQosFcCtrl.enFlowCtrl)
        {
            /* 无需任何流控操作 */
            return;
        }
        else
        {
            /* 优先级小于6的承载首先恢复正常数传 */
            if(PS_SUCC == QosFc_RestoreHighPriRab())
            {
                /* 下一次流控触发 */
                (VOS_VOID)QosFc_RestartCheckTmr();
                return;
            }
        }
    }

    /*流控操作*/
    QosFc_FlowCtrlProc(ulMemRemain, &ulRestoreCnt);

    /* 退出流控状态后不做周期性检查 */
    if(QOS_FC_STATE_FLOWCTRL == g_stQosFcCtrl.enFlowCtrl)
    {
        /* 启动流控检查定时器 */
        (VOS_VOID)QosFc_RestartCheckTmr();
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 函 数 名  : QosFc_FlowCtrlProc
 功能描述  : 流控操作
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月30日
    作    者   : q00208938
    修改内容   : 封装成函数

*****************************************************************************/
VOS_VOID QosFc_FlowCtrlProc(VOS_UINT32 ulMemRemain, VOS_UINT32 *pRestoreCnt)
{
    /* 流控操作 */
    if (g_stQosFcCtrl.ulWarningThres > ulMemRemain)
    {
        (VOS_VOID)QosFc_DiscardAllDataFlow();
        g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_FLOWCTRL;
        *pRestoreCnt = 0;
    }
    else if (g_stQosFcCtrl.ulDiscardThres > ulMemRemain)
    {
        (VOS_VOID)QosFc_DiscardDataFlow();
        g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_FLOWCTRL;
        *pRestoreCnt = 0;
    }
    else if (g_stQosFcCtrl.ulRandomDiscardThres > ulMemRemain)
    {
        (VOS_VOID)QosFc_RandomDiscardDataFlow();
        g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_FLOWCTRL;
        *pRestoreCnt = 0;
    }
    else if (g_stQosFcCtrl.ulRestoreThres < ulMemRemain)
    {
        if (QOS_FC_STATE_FLOWCTRL == g_stQosFcCtrl.enFlowCtrl)
        {
            (*pRestoreCnt)++;

            if (QOS_FC_SLOW_UP <= (*pRestoreCnt))
            {
                /*  慢恢复 */
                *pRestoreCnt = 0;
                if (PS_SUCC != QosFc_RestoreDataFlow())
                {
                    /* 一次流控过程结束 */
                    g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_NORMAL;
                }
            }
        }
    }
    else
    {
    }
    return;
}

/*****************************************************************************
 函 数 名  : QosFcCtrlInit
 功能描述  : 流控控制结构初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFcCtrlInit(VOS_VOID)
{
    /* 基于NV填充控制结构 */
    if(0 == (QOS_FC_ENABLED_MASK & g_stFcCdsConfig.ulFcEnableMask))
    {
        g_stQosFcCtrl.bQosFcEnable = VOS_FALSE;
    }
    else
    {
        g_stQosFcCtrl.bQosFcEnable = VOS_TRUE;
    }

    if(0 == (QOS_FC_HIGHEST_FC_ENABLED_MASK & g_stFcCdsConfig.ulFcEnableMask))
    {
        g_stQosFcCtrl.bHighFcEnable = VOS_FALSE;
    }
    else
    {
        g_stQosFcCtrl.bHighFcEnable = VOS_TRUE;
    }

    if(0 == (QOS_FC_HIGHEST_NOTDISCARD_ENABLED_MASK & g_stFcCdsConfig.ulFcEnableMask))
    {
        g_stQosFcCtrl.bHighDiscardEnable = VOS_TRUE;
    }
    else
    {
        g_stQosFcCtrl.bHighDiscardEnable = VOS_FALSE;
    }

    g_stQosFcCtrl.hTimer = VOS_NULL_PTR;
    g_stQosFcCtrl.enFlowCtrl = QOS_FC_STATE_NORMAL;

    g_stQosFcCtrl.ulPktCntLimit = g_stFcCdsConfig.stQosFcConfig.ulPktCntLimit;
    g_stQosFcCtrl.ulTimerLen = g_stFcCdsConfig.stQosFcConfig.ulTimerLen;

    g_stQosFcCtrl.ulRandomDiscardRate = g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardRate;
    g_stQosFcCtrl.ulDiscardRate = g_stFcCdsConfig.stQosFcConfig.ulDiscardRate;

    g_stQosFcCtrl.ulWarningThres = g_stFcCdsConfig.stQosFcConfig.ulWarningThres;
    g_stQosFcCtrl.ulDiscardThres = g_stFcCdsConfig.stQosFcConfig.ulDiscardThres;
    g_stQosFcCtrl.ulRandomDiscardThres = g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardThres;
    g_stQosFcCtrl.ulRestoreThres = g_stFcCdsConfig.stQosFcConfig.ulRestoreThres;

    return;

}

/*****************************************************************************
 函 数 名  : QosFc_Init
 功能描述  : 流控模块初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID QosFc_Init(VOS_VOID)
{
    QosFcCtrlInit();    /* 暂时本地赋值，后面要从NV读取 */
    QosFcRabInit();
    QosFcChannelInit();

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



