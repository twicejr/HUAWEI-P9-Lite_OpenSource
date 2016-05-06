/******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : R_ITF_FlowCtrl.c
  Author       : g45205
  Version      : V100R001
  Date         : 2006-05-17
  Description  :
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2006-05-17
     Author: g45205
     Modification:Create
******************************************************************************/


/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "R_ITF_FlowCtrl.h"
#include "NVIM_Interface.h"
#include "TTFMem.h"
#include "FcIntraMsg.h"
#include "PsCommonDef.h"
#include "Fc.h"
#include "TTFComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   2 外部函数变量声明
******************************************************************************/
extern VOS_UINT32 IPSCH_FeatureSwitchIsOn(VOS_VOID);

/******************************************************************************
   3 私有定义
******************************************************************************/
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID                    PS_FILE_ID_R_ITF_FLOW_CTRL_C


/******************************************************************************
   4 全局变量定义
******************************************************************************/
/* R接口流控实体定义 */
R_ITF_FLOW_CTRL_STRU                    g_stRItfFlowCtrl;
VOS_UINT32                              g_ulRItfFlowCtrlProTime = 0;
R_ITF_FLOW_CTRL_CONFIG_STRU             g_stRItfFlowCtrlConfig;
VOS_UINT32                              g_ulLteFlowCtrl  =   VOS_FALSE;

VOS_UINT32      g_ulRItfFlowCtrlCnt = 0;
VOS_UINT32      g_ulRItfClearCtrlCnt = 0;
VOS_UINT32      g_ulRItfFlowCtrlDiscardNum = 20;

#define         RITF_FLOWCTRL_WRED_THRESHOLD        (g_ulRItfFlowCtrlDiscardNum)


/******************************************************************************
   6 函数实现
******************************************************************************/
/*lint -save -e958 */
/******************************************************************************
 Prototype      : R_ITF_MntnFlowCtrlEvent
 Description    : 流控执行情况可维可测
 Input          : ulFlowCtrlType    -- 流控类型
                  ulNewLev          -- 该流控类型的最新值
                  ulFlowCtrlCmd     -- 流控指令，启动或停止
                  ulResult          -- 流控执行结果
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-04-14
    Author      : l00164359
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_MntnFlowCtrlEvent
(
    R_ITF_FLOW_CTRL_TYPE_ENUM_UINT32 ulFlowCtrlType,
    VOS_UINT32                       ulNewLev,
    R_ITF_FLOW_CTRL_CMD_ENUM_UINT32  ulFlowCtrlCmd,
    VOS_UINT32                       ulResult
)
{
    R_ITF_FLOW_CTRL_MNTN_INFO_STRU                stMntnInfo;


    stMntnInfo.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stMntnInfo.ulSenderPid     = WUEPS_PID_RLC;
    stMntnInfo.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stMntnInfo.ulReceiverPid   = WUEPS_PID_RLC;
    stMntnInfo.ulLength        = sizeof(R_ITF_FLOW_CTRL_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    stMntnInfo.enFlowCtrlType  = ulFlowCtrlType;
    stMntnInfo.ulNewLevel      = ulNewLev;
    stMntnInfo.enFlowCtrlCmd   = ulFlowCtrlCmd;
    stMntnInfo.ulResult        = ulResult;

    (VOS_VOID)DIAG_TraceReport(&stMntnInfo);

    return;
}

/******************************************************************************
 Prototype      : R_ITF_TtfMemAllocEvent
 Description    : 数传MEM申请回调函数
 Input          : ulMemUsedCnt  -- 内存块数
                  ulMemUsedSize -- 内存总大小
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-08-31
    Author      : 高财(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_TtfMemAllocEvent(VOS_UINT32 ulMemUsedCnt, VOS_UINT32 ulMemUsedSize)
{
    (VOS_VOID)R_ITF_SetFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_CNT, ulMemUsedCnt);
    (VOS_VOID)R_ITF_SetFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_SIZE, ulMemUsedSize);
} /* R_ITF_TtfMemAllocEvent */


/******************************************************************************
 Prototype      : R_ITF_TtfMemFreeEvent
 Description    : 数传MEM释放回调函数
 Input          : ulMemUsedCnt  -- 内存块数
                  ulMemUsedSize -- 内存总大小
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-08-31
    Author      : 高财(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_TtfMemFreeEvent(VOS_UINT32 ulMemUsedCnt, VOS_UINT32 ulMemUsedSize)
{
    (VOS_VOID)R_ITF_ClearFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_CNT, ulMemUsedCnt);
    (VOS_VOID)R_ITF_ClearFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_SIZE, ulMemUsedSize);
} /* R_ITF_TtfMemFreeEvent */


/*****************************************************************************
 函 数 名  : R_ITF_StartFlowCtrl
 功能描述  : 启动流控
 输入参数  : usMsgId - 消息ID
 输出参数  : 无
 返 回 值  : 操作成功与否, VOS_OK - 成功, 其它 - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : liukai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 R_ITF_StartFlowCtrl(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    FC_SET_FLOWCTRL_IND_STRU           *pstFcSetInd;


    pstFcSetInd = (FC_SET_FLOWCTRL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_FLOWCTRL_C, sizeof(FC_SET_FLOWCTRL_IND_STRU));

    /* 申请消息失败 */
    if (VOS_NULL_PTR == pstFcSetInd)
    {
        /* 告警打印 */
        (VOS_VOID)LogPrint("R_ITF_StartFlowCtrl, ERROR, alloc msg fail\r\n");
        return VOS_ERR;
    }

    /* 填写消息名字 */
    pstFcSetInd->usMsgName          = ID_FC_SET_FLOWCTRL_IND;
    pstFcSetInd->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstFcSetInd->ulReceiverPid      = UEPS_PID_FLOWCTRL_A;
    pstFcSetInd->enRateMode         = enRateMode;

    /* 发消息 */
    PS_SEND_MSG(UEPS_PID_FLOWCTRL_C, pstFcSetInd);

    return VOS_OK;
}    /* R_ITF_StartFlowCtrl */


/*****************************************************************************
 函 数 名  : R_ITF_FlowCtrlNotify
 功能描述  : 发送G模和X模流控启停通知消息
 输入参数  : usMsgId - 消息ID
 输出参数  : 无
 返 回 值  : 操作成功与否, VOS_OK - 成功, 其它 - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月10日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 R_ITF_FlowCtrlNotify(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    FC_FLOWCTRL_NOTIFY_STRU            *pstFcNotify;

    pstFcNotify = (FC_FLOWCTRL_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
        UEPS_PID_FLOWCTRL_C, sizeof(FC_FLOWCTRL_NOTIFY_STRU));

    /* 申请消息失败 */
    if (VOS_NULL_PTR == pstFcNotify)
    {
        /* 告警打印 */
        (VOS_VOID)LogPrint("R_ITF_FlowCtrlNotify, ERROR, alloc msg fail\r\n");
        return VOS_ERR;
    }

    /* 填写消息名字 */
    pstFcNotify->usMsgName              = ID_FC_C_FLOWCTRL_NOTIFY;
    pstFcNotify->enRateMode             = enRateMode;
    pstFcNotify->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstFcNotify->ulReceiverPid          = UEPS_PID_FLOWCTRL_C;


    /* 发消息 */
    PS_SEND_MSG(UEPS_PID_FLOWCTRL_C, pstFcNotify);

    return VOS_OK;

}

/******************************************************************************
 Prototype      : R_ITF_IPSCH_UpdateFlowCtrlCnt
 Description    : 流控统计计数更新
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-09-26
    Author      : g00178567 t00148005
    Modification: Created function
  2.Date        : 2012-12-19
    Author      : c00217042
    Modification: update function
******************************************************************************/
VOS_VOID R_ITF_UpdateFlowCtrlCnt(VOS_VOID)
{
    g_ulRItfFlowCtrlCnt++;
    return;
}

/******************************************************************************
 Prototype      : R_ITF_UpdateClearFlowCtrlCnt
 Description    : 解流控统计计数更新
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2016-01-20
    Author      : c00184031
    Modification: Created function
  2.Date        : 2012-12-19
    Author      : c00217042
    Modification: update function
******************************************************************************/
VOS_VOID R_ITF_UpdateClearFlowCtrlCnt(VOS_VOID)
{
    g_ulRItfClearCtrlCnt++;
    return;
}

/*****************************************************************************
 函 数 名  : R_Itf_FlowctrlGetStatCnt
 功能描述  : 获取统计流控次数
 输入参数  : *pulFcStatCnt
 输出参数  : 无
 返 回 值  : 操作成功与否, VOS_OK - 成功, 其它 - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : c00217042
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 R_Itf_FlowctrlGetStatCnt(VOS_UINT32 *pulFcStatCnt)
{
    *pulFcStatCnt = g_ulRItfFlowCtrlCnt;
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : R_Itf_FlowctrlSetStatCnt
 功能描述  : 设置统计流控次数
 输入参数  : pulFcStatCnt
 输出参数  : 无
 返 回 值  : 操作成功与否, VOS_OK - 成功, 其它 - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    作    者   : c00217042
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 R_Itf_FlowctrlSetStatCnt(VOS_UINT32 pulFcStatCnt)
{
    g_ulRItfFlowCtrlCnt = pulFcStatCnt;
    return VOS_OK;
}


/******************************************************************************
 Prototype      : R_ITF_IPSCH_FlowCtrlCntIsOverFlow
 Description    : 判断流控统计计数是否超过拥塞避免门限，超过则重置流控统计计数
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-09-26
    Author      : g00178567 t00148005
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_FlowCtrlCntIsOverFlow(VOS_VOID)
{
    VOS_INT32               lLockKey;

    if (RITF_FLOWCTRL_WRED_THRESHOLD < g_ulRItfFlowCtrlCnt)
    {
        /* 进入流控临界区 */
        lLockKey            = VOS_SplIMP();

        g_ulRItfFlowCtrlCnt = 0;

        VOS_Splx(lLockKey);
        return VOS_YES;
    }

    return VOS_NO;
}

/*****************************************************************************
 函 数 名  : R_ITF_StopFlowCtrl
 功能描述  : 停止流控
 输入参数  : usMsgId - 消息ID
 输出参数  : 无
 返 回 值  : 操作成功与否, VOS_OK - 成功, 其它 - 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : liukai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 R_ITF_StopFlowCtrl(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    FC_STOP_FLOWCTRL_IND_STRU          *pstFcStopInd;

    pstFcStopInd = (FC_STOP_FLOWCTRL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
        UEPS_PID_FLOWCTRL_C, sizeof(FC_STOP_FLOWCTRL_IND_STRU));

    /* 申请消息失败 */
    if (VOS_NULL_PTR == pstFcStopInd)
    {
        /* 告警打印 */
        (VOS_VOID)LogPrint("R_ITF_StopFlowCtrl, ERROR, alloc msg fail\r\n");
        return VOS_ERR;
    }

    /* 填写消息名字 */
    pstFcStopInd->usMsgName         = ID_FC_STOP_FLOWCTRL_IND;

    pstFcStopInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFcStopInd->ulReceiverPid     = UEPS_PID_FLOWCTRL_A;
    pstFcStopInd->enRateMode        = enRateMode;


    /* 发消息 */
    PS_SEND_MSG(UEPS_PID_FLOWCTRL_C, pstFcStopInd);

    return VOS_OK;
}   /* FC_StopFlowCtrl */

#if 0
/******************************************************************************
 Prototype      : R_ITF_ExcFlowCtrl
 Description    : 执行流控
 Input          : ulFlowCtrlType    -- 流控类型
                  ulNewLev          -- 该流控类型的最新值
                  ulFlowCtrlCmd     -- 流控指令，启动或停止
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-04-14
    Author      : l00164359
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_ExcFlowCtrl
(
    R_ITF_FLOW_CTRL_CMD_ENUM_UINT32  ulFlowCtrlCmd,
    VOS_UINT32                       ulFlowCtrlType,
    VOS_UINT32                      *pulNeedTrace
)
{
    VOS_UINT32      ulResult = VOS_OK;

    if ( R_ITF_FLOW_CTRL_START == ulFlowCtrlCmd )
    {
        /* PS融合后, 这里只监测内存, 而其余监测对象全部统一到FC的框架下 */
        if ((R_ITF_FLOW_CTRL_TYPE_MEM_CNT == ulFlowCtrlType)
            || (R_ITF_FLOW_CTRL_TYPE_MEM_SIZE == ulFlowCtrlType))
        {
            ulResult        = R_ITF_StartFlowCtrl();    /* 调用流控函数 */
            *pulNeedTrace   = PS_TRUE;
        }
    }
    else if ( R_ITF_FLOW_CTRL_STOP == ulFlowCtrlCmd )
    {
        /* PS融合后, 这里只监测内存, 而其余监测对象全部统一到FC的框架下 */
        if ((R_ITF_FLOW_CTRL_TYPE_MEM_CNT == ulFlowCtrlType)
            || (R_ITF_FLOW_CTRL_TYPE_MEM_SIZE == ulFlowCtrlType))
        {
            ulResult        = R_ITF_StopFlowCtrl();    /* 调用流控解除函数 */
            *pulNeedTrace   = PS_TRUE;
        }
    }
    else
    {
        (VOS_VOID)LogPrint1("R_ITF_ExcFlowCtrl, WARNING, Unknow flow control command %u\r\n",
                  (VOS_INT32)ulFlowCtrlCmd);

        return VOS_ERR;
    }

    return ulResult;
}
#endif

/******************************************************************************
 Prototype      : R_ITF_SetFlowCtrl
 Description    : 根据最新情况，判断是否需要进行流控
 Input          : ulFlowCtrlType    -- 流控类型
                  ulNewLev          -- 该流控类型的最新值
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : 高财(g45205)
    Modification: Created function
  2.Date        : 2011-04-15
    Author      : l00164359
    Modification: 重构流控执行函数，增加流控状态标志位设置保护
******************************************************************************/
VOS_UINT32 R_ITF_SetFlowCtrl
(
    VOS_UINT32                                  ulFlowCtrlType,
    VOS_UINT32                                  ulNewLev
)
{
    R_ITF_FLOW_LEV_STRU                 *pFlowLev;
    VOS_INT32                           lLockKey;
    VOS_UINT32                          ulOldMask;
    VOS_UINT32                          ulCurrTick;
    VOS_UINT32                          ulNeedExec;              /* 是否需要进行流控或者解除流控操作 */
    VOS_UINT32                          ulResult;                /* 流控执行结果 */


    if (R_ITF_FLOW_CTRL_TYPE_BUTT <= ulFlowCtrlType)
    {
        R_ITF_WARNING_LOG2("R_ITF_SetFlowCtrl", ulFlowCtrlType, ulNewLev);
        return VOS_ERR;
    }

    /* 进入流控临界区 */
    lLockKey            = VOS_SplIMP();

    ulNeedExec          = PS_FALSE;
    ulResult            = VOS_OK;
    pFlowLev            = &g_stRItfFlowCtrl.astFlowCtrl[ulFlowCtrlType];
    ulCurrTick          = VOS_GetTick();

    if (pFlowLev->ulMaxLev < ulNewLev)
    {
        pFlowLev->ulMaxLev = ulNewLev;
    }

    /* 流控实体里保存的当前值需要做互斥保护 */
    pFlowLev->ulCurrLev = ulNewLev;
    ulOldMask           = g_stRItfFlowCtrl.ulCtrlMask;

    /* 处于解流控状态时超过阀值, 启动流控 */
    if (ulNewLev >= pFlowLev->ulWarningLev)
    {
        if (0 == ulOldMask)
        {
            ulNeedExec  = PS_TRUE;

            g_stRItfFlowCtrl.ulLastOptTick  = ulCurrTick;
            g_stRItfFlowCtrl.ulCtrlMask    |=  pFlowLev->ulMask;

            g_stRItfFlowCtrl.ulCtrlFlag     = R_ITF_FLOW_CTRL_START;
        }
    }

    /* 离开流控临界区 */
    VOS_Splx(lLockKey);

    if (PS_TRUE == ulNeedExec)
    {
        /* 调用流控函数 */
        ulResult        = R_ITF_FlowCtrlNotify(g_stRItfFlowCtrl.enRateMode);

        R_ITF_UpdateFlowCtrlCnt();

        if (VOS_OK == ulResult)
        {
            /* 进行流控或者解除流控操作的同时, 进行可测可维 */
            R_ITF_MntnFlowCtrlEvent(ulFlowCtrlType, ulNewLev, R_ITF_FLOW_CTRL_START, ulResult);
        }
    }

    return ulResult;
} /* R_ITF_SetFlowCtrl */

/******************************************************************************
 Prototype      : R_ITF_ClearFlowCtrl
 Description    : 根据最新情况，判断是否需要解除流控
 Input          : ulFlowCtrlType    -- 流控类型
                  ulNewLev          -- 该流控类型的最新值
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : 高财(g45205)
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_ClearFlowCtrl(VOS_UINT32 ulFlowCtrlType, VOS_UINT32 ulNewLev)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;
    VOS_UINT32              ulCurrTick;
    VOS_UINT32              ulNeedExec;              /* 是否需要进行流控或者解除流控操作 */
    VOS_UINT32              ulResult;                /* 流控执行结果 */
    VOS_UINT32              ulUpdatedMask;


    if (R_ITF_FLOW_CTRL_TYPE_BUTT <= ulFlowCtrlType)
    {
        R_ITF_WARNING_LOG2("R_ITF_ClearFlowCtrl", ulFlowCtrlType, ulNewLev);
        return VOS_ERR;
    }

    /* 进入流控临界区 */
    lLockKey            = VOS_SplIMP();

    ulNeedExec          = PS_FALSE;
    ulResult            = VOS_OK;
    pFlowLev            = &g_stRItfFlowCtrl.astFlowCtrl[ulFlowCtrlType];
    ulCurrTick          = VOS_GetTick();

    /* 流控实体里保存的当前值需要做互斥保护 */
    pFlowLev->ulCurrLev = ulNewLev;

    /* 并没有因为该种类型导致流控, 无须解除流控 */
    if (0 == (g_stRItfFlowCtrl.ulCtrlMask & pFlowLev->ulMask))
    {
        VOS_Splx(lLockKey);
        return VOS_OK;
    }

    if (ulNewLev < pFlowLev->ulNormalLev)
    {
        if ((ulCurrTick - g_stRItfFlowCtrl.ulLastOptTick) >= g_ulRItfFlowCtrlProTime)
        {
            ulUpdatedMask = g_stRItfFlowCtrl.ulCtrlMask &  (~(pFlowLev->ulMask));

            /*所有流控条件都解除的情况下，执行解除流控操作*/
            if ( 0 == ulUpdatedMask )
            {
                ulNeedExec      = PS_TRUE;

                g_stRItfFlowCtrl.ulLastOptTick = ulCurrTick;
                g_stRItfFlowCtrl.ulCtrlMask   &=  ~(pFlowLev->ulMask);

                g_stRItfFlowCtrl.ulCtrlFlag    = R_ITF_FLOW_CTRL_STOP;
            }
        }
    }

    /* 离开流控临界区 */
    VOS_Splx(lLockKey);

    if (PS_TRUE == ulNeedExec)
    {
        /* 调用流控解除函数 */
        ulResult        = R_ITF_FlowCtrlNotify(g_stRItfFlowCtrl.enRateMode);

        R_ITF_UpdateClearFlowCtrlCnt();

        if (VOS_OK == ulResult)
        {
            /*流控事件可维可测*/
            R_ITF_MntnFlowCtrlEvent(ulFlowCtrlType, ulNewLev, R_ITF_FLOW_CTRL_STOP, ulResult);
        }
    }

    return ulResult;
} /* R_ITF_ClearFlowCtrl */


/******************************************************************************
 Prototype      : R_ITF_SetLFlowLev
 Description    : 业务切换为LTE模时，更改流控门限
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-04-01
    Author      : l00164359
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetLFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;

    /* PS融合后, L模在C核流控是在A核上控制, 因此在C核上将门限改为无穷大, 这样不再起流控 */

    /* 进入流控临界区 */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 600;
    pFlowLev->ulWarningLev  = 1200;
    pFlowLev->ulMaxLev      = 0;

    if ( VOS_FALSE == g_ulLteFlowCtrl )
    {
        pFlowLev->ulWarningLev  = 0xffffffff;
        pFlowLev->ulNormalLev   = 0xffffffff;
    }

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 900000;
    pFlowLev->ulWarningLev  = 1800000;
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_LTE;

    if ( VOS_FALSE == g_ulLteFlowCtrl )
    {
        pFlowLev->ulWarningLev  = 0xffffffff;
        pFlowLev->ulNormalLev   = 0xffffffff;
    }

    /* 离开流控临界区 */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* 到L模下, 内存在A核监测, 因此C核上不需要内存监测钩子 */
    (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, VOS_NULL_PTR, VOS_NULL_PTR);

    return;
}



/******************************************************************************
 Prototype      : R_ITF_SetWFlowLev
 Description    : 业务切换为W模时，更改流控门限
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2009-02-27
    Author      : 蔡鹏48156
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetWFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;


    /* PS融合后, W模在C核流控是在A核上控制, 因此在C核上将门限改为无穷大, 这样不再起流控 */
    /* 进入流控临界区 */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 0xffffffff;/*1000*/
    pFlowLev->ulWarningLev  = 0xffffffff;/*2000*/
    pFlowLev->ulMaxLev      = 0;

    /* PS融合后, W模由于使用A核内存, 因此将门限设置为无穷大, 避免内存起流控 */
    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 0xffffffff;/*1200000*/
    pFlowLev->ulWarningLev  = 0xffffffff;/*2000000*/
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_WCDMA;

    /* 离开流控临界区 */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* 到W模下, 内存在A核监测, 因此C核上不需要内存监测钩子 */
    (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, VOS_NULL_PTR, VOS_NULL_PTR);

    return;
}


/******************************************************************************
 Prototype      : R_ITF_SetGFlowLev
 Description    : 业务切换为G模时，更改流控门限
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2009-02-27
    Author      : 蔡鹏48156
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetGFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;


    /* 进入流控临界区 */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 600;
    pFlowLev->ulWarningLev  = 600;
    pFlowLev->ulMaxLev      = 0;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 30000;
    pFlowLev->ulWarningLev  = 30000;
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_GSM;

    /* 离开流控临界区 */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* V9R1中使用流控NV项中GPRS流控使能位来判断是否注册钩子函数 */
    if ( (FC_POLICY_MASK(FC_POLICY_ID_GPRS) == FC_POLICY_GetEnableMask(FC_POLICY_ID_GPRS) ))
    {
        /* 到G模下, A核内存需要拷贝到C核TTF_MEM中, 因此C核上需要内存监测钩子 */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, R_ITF_TtfMemAllocEvent, R_ITF_TtfMemFreeEvent);
    }
    else
    {
        /* V9R1中使用宏来判断，如果是V9R1,则不注册钩子函数 */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, VOS_NULL_PTR, VOS_NULL_PTR);
    }

    return;
}

/******************************************************************************
 Prototype      : R_ITF_Set1XFlowLev
 Description    : 业务切换为1X模时，更改流控门限
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2015-08-04
    Author      : c00184031
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_Set1XFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;

    /* 进入流控临界区 */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 300;
    pFlowLev->ulWarningLev  = 600;
    pFlowLev->ulMaxLev      = 0;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 390000;
    pFlowLev->ulWarningLev  = 900000;
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_1X;

    /* 离开流控临界区 */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* V9R1中使用流控NV项中GPRS流控使能位来判断是否注册钩子函数 */
    if ( (FC_POLICY_MASK(FC_POLICY_ID_CDMA) == FC_POLICY_GetEnableMask(FC_POLICY_ID_CDMA) ))
    {
        /* 到X模下, A核内存需要拷贝到C核TTF_MEM中, 因此C核上需要内存监测钩子 */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_IP_DATA, R_ITF_TtfMemAllocEvent, R_ITF_TtfMemFreeEvent);
    }
    else
    {
        /* V9R1中使用宏来判断，如果是V9R1,则不注册钩子函数 */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_IP_DATA, VOS_NULL_PTR, VOS_NULL_PTR);
    }

    return;
}

/******************************************************************************
 Prototype      : R_ITF_SetHrpdFlowLev
 Description    : 业务切换为HRPD模时，更改流控门限
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2015-08-04
    Author      : c00184031
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetHrpdFlowLev(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;


    /* 进入流控临界区 */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 300;
    pFlowLev->ulWarningLev  = 600;
    pFlowLev->ulMaxLev      = 0;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 390000;
    pFlowLev->ulWarningLev  = 900000;
    pFlowLev->ulMaxLev      = 0;

    g_stRItfFlowCtrl.enRateMode = VOS_RATMODE_HRPD;

    /* 离开流控临界区 */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* V9R1中使用流控NV项中GPRS流控使能位来判断是否注册钩子函数 */
    if ( (FC_POLICY_MASK(FC_POLICY_ID_CDMA) == FC_POLICY_GetEnableMask(FC_POLICY_ID_CDMA) ))
    {
        /* 到X模下, A核内存需要拷贝到C核TTF_MEM中, 因此C核上需要内存监测钩子 */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_IP_DATA, R_ITF_TtfMemAllocEvent, R_ITF_TtfMemFreeEvent);
    }
    else
    {
        /* V9R1中使用宏来判断，如果是V9R1,则不注册钩子函数 */
        (VOS_VOID)TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_IP_DATA, VOS_NULL_PTR, VOS_NULL_PTR);
    }

    return;
}

/******************************************************************************
 Prototype      : R_ITF_SetFlowLev
 Description    : 更改流控阀值
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2015-08-10
    Author      : c00184031
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetFlowLev
(
    VOS_RATMODE_ENUM_UINT32             enRateMode
)
{
    switch (enRateMode)
    {
        case VOS_RATMODE_GSM:

            R_ITF_SetGFlowLev(VOS_RATMODE_GSM);

            break;

        case VOS_RATMODE_WCDMA:

            R_ITF_SetWFlowLev(VOS_RATMODE_WCDMA);

            break;

        case VOS_RATMODE_LTE:

            R_ITF_SetLFlowLev(VOS_RATMODE_LTE);

            break;

        case VOS_RATMODE_1X:

            R_ITF_Set1XFlowLev(VOS_RATMODE_1X);

            break;

        case VOS_RATMODE_HRPD:

            R_ITF_SetHrpdFlowLev(VOS_RATMODE_HRPD);

            break;

        default:

            (VOS_VOID)LogPrint1("R_ITF_SetFlowLev, Invalid rate mode\r\n", (VOS_INT32)enRateMode);

            break;
    }

    return;
}/* R_ITF_SetFlowLev */

/******************************************************************************
 Prototype      : R_ITF_InitFlowCtrl
 Description    : 初始化流控实体
 Input          : ulFlowCtrlType    -- 流控类型
                  ulNewLev          -- 该流控类型的最新值
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : 高财(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_InitFlowCtrl(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    R_ITF_FLOW_CTRL_CONFIG_STRU        *pstRItfFlowCtrlConfig;
    R_ITF_FLOW_LEV_STRU                *pFlowLev;

    pstRItfFlowCtrlConfig               = &g_stRItfFlowCtrlConfig;

    /*Read the NV Config Value*/
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_RITF_FLOW_CTRL_Config, pstRItfFlowCtrlConfig, sizeof(R_ITF_FLOW_CTRL_CONFIG_STRU));

    /*Read NV Content is Failed , Configed the Vaule By Default Value*/
    if ( NV_OK != ulResult )
    {
        pstRItfFlowCtrlConfig->ulRateDismatchUsbEnable  = 1;
        pstRItfFlowCtrlConfig->ulRateDismatchWifiEnable = 0;
    }
    else
    {
        if ( 1 < pstRItfFlowCtrlConfig->ulRateDismatchUsbEnable )
        {
            pstRItfFlowCtrlConfig->ulRateDismatchUsbEnable  = 1;
        }

        if ( 1 < pstRItfFlowCtrlConfig->ulRateDismatchWifiEnable )
        {
            pstRItfFlowCtrlConfig->ulRateDismatchWifiEnable = 0;
        }
    }

    PS_MEM_SET(&g_stRItfFlowCtrl, 0, sizeof(g_stRItfFlowCtrl));

    g_stRItfFlowCtrl.ulCtrlMask     = 0;
    g_stRItfFlowCtrl.ulLastOptTick  = 0;
    g_stRItfFlowCtrl.ulCtrlFlag     = R_ITF_FLOW_CTRL_STOP;;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulMask        = R_ITF_FLOW_CTRL_MASK_MEM_CNT;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulMask        = R_ITF_FLOW_CTRL_MASK_MEM_SIZE;

    R_ITF_SetWFlowLev(VOS_RATMODE_WCDMA);


} /* R_ITF_InitFlowCtrl */


/******************************************************************************
 Prototype      : R_ITF_RateDismatchUsbEnable
 Description    :
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-03-11
    Author      : hefeng
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_RateDismatchUsbEnable(VOS_VOID)
{
    return g_stRItfFlowCtrlConfig.ulRateDismatchUsbEnable;
}


/******************************************************************************
 Prototype      : R_ITF_RateDismatchWifiEnable
 Description    :
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-03-11
    Author      : hefeng
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_RateDismatchWifiEnable(VOS_VOID)
{
    return g_stRItfFlowCtrlConfig.ulRateDismatchWifiEnable;
}


/******************************************************************************
 Prototype      : R_ITF_ResetMaxLev
 Description    :
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : 高财(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_ResetMaxLev(VOS_VOID)
{
    VOS_UINT32  ulLoop;


    for (ulLoop = 0; ulLoop < R_ITF_FLOW_CTRL_TYPE_BUTT; ulLoop++)
    {
        g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulMaxLev   = 0;
    }
} /* R_ITF_ResetMaxLev */

/******************************************************************************
 Prototype      : R_ITF_ResetFlowCtrl
 Description    : 更新流控状态
 Input          : VOID
                :
 Output         : VOID
 Return Value   : VOID
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-03-07
    Author      : s00164817
    Modification: Created function
***************************************************************************** */
VOS_VOID R_ITF_ResetFlowCtrl(VOS_VOID)
{
    VOS_UINT32  ulLoop;
    R_ITF_FLOW_LEV_STRU    *pFlowLev;


    for ( ulLoop = 0; ulLoop <= R_ITF_FLOW_CTRL_TYPE_MEM_SIZE; ++ulLoop )
    {
        pFlowLev = &g_stRItfFlowCtrl.astFlowCtrl[ulLoop];

        if ( pFlowLev->ulCurrLev >= pFlowLev->ulWarningLev )
        {
            (VOS_VOID)R_ITF_SetFlowCtrl(ulLoop, pFlowLev->ulCurrLev);
        }
        else
        {
            (VOS_VOID)R_ITF_ClearFlowCtrl(ulLoop, pFlowLev->ulCurrLev);
        }
    }

    return;

}

/* 临时测试代码，用来采集R接口流控的阀值，所以直接使用了 vos_printf */
/******************************************************************************
 Prototype      : R_ITF_Print
 Description    : 打印流控实体情况，临时测试使用
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : 高财(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_Print(VOS_VOID)
{
    VOS_UINT32  ulLoop;


    (VOS_VOID)vos_printf("\r\n");

    (VOS_VOID)vos_printf("start flow ctrl cnt:     %d\r\n", g_ulRItfFlowCtrlCnt);
    (VOS_VOID)vos_printf("stop flow ctrl cnt:      %d\r\n", g_ulRItfClearCtrlCnt);

    for (ulLoop = 0; ulLoop < R_ITF_FLOW_CTRL_TYPE_BUTT; ulLoop++)
    {
        (VOS_VOID)vos_printf("Type:%u, MaxLev=%u, CurrLev=%u, ulWarningLev=%u, ulNormalLev=%u\r\n",
            ulLoop,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulMaxLev,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulCurrLev,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulWarningLev,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulNormalLev );
    }
} /* R_ITF_Print */
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


