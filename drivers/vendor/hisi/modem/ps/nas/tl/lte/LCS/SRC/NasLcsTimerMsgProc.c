/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLcsTimerMsgProc.c
    Description : 处理定时器超时消息
    History     :
            1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "NasLcsOm.h"
#include    "NasLcsEmmMsgProc.h"
#include    "NasLcsMmMsgProc.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



#define    THIS_FILE_ID            PS_FILE_ID_NASLCSTIMERMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSTIMERMSGPROC_C

#if (FEATURE_LPP == FEATURE_ON)



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_LCS_RcvWaitNwRspTimerExp
 Discription    : 处理等待网络定时器超时
 Input          : ulIndex---------------实体索引
 Output         : None
 Return         : VOS_VOID
 History:
      1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_RcvWaitNwRspTimerExp
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG1("NAS_LCS_RcvWaitNwRspTimerExp:ulIndex= ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_InvalidEntityType, ulIndex);

    /* 是否为MOLR */
    if (PS_TRUE != NAS_LCS_IsMoLr(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitNwRspTimerExp:Is not MOLR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_InvalidEntityType);

        return ;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);
    if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitNwRspTimerExp:entity not exist!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_EntityNotExist);

        return ;
    }

    /* 状态是否为等待网络回复 */
    if (NAS_LCS_ENTITY_STATE_WAIT_NW_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitNwRspTimerExp:state invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_EntityStateInvalid);

        return ;
    }

    if (NAS_LCS_CONN_STATE_CONN == NAS_LCS_GetEntityConnState(ulIndex))
    {
        /* 编码RELEASE COMPLTE消息，发给网侧 */
        NAS_LCS_SndReleaseComplte(ulIndex);
    }

    NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_LCS_NW_TIMER_OUT);
}

/*****************************************************************************
 Function Name  : NAS_LCS_RcvWaitReestTimerExp
 Discription    : 处理重建链定时器超时
 Input          : ulIndex---------------索引
 Output         : None
 Return         : VOS_VOID
 History:
      1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_RcvWaitReestTimerExp
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG1("NAS_LCS_RcvWaitReestTimerExp:ulIndex= ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_RcvWaitReestTimerExp_ENUM, LNAS_LCS_InvalidEntityType, ulIndex);

    /* 是否为MOLR */
    if (PS_TRUE != NAS_LCS_IsMoLr(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitReestTimerExp:Is not MOLR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitReestTimerExp_ENUM, LNAS_LCS_InvalidEntityType);

        return ;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);
    if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitReestTimerExp:entity not exist!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitReestTimerExp_ENUM, LNAS_LCS_EntityNotExist);

        return ;
    }

    /* 状态是否为等待网络回复 */
    if (NAS_LCS_ENTITY_STATE_WAIT_NW_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitReestTimerExp:state invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitReestTimerExp_ENUM, LNAS_LCS_EntityStateInvalid);

        return ;
    }

    /* 给相应域发建链请求 */
    if (NAS_LCS_DOMAIN_TYPE_EPC_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
    {
        NAS_LCS_SndLmmEstReq(NAS_LCS_GetEntityTi(ulIndex));
    }
    else
    {
        NAS_LCS_SndMmEstReq(NAS_LCS_GetEntityTi(ulIndex));
    }

    /* 更新实体连接状态为建链过程中 */
    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_ESTING);
}

/*****************************************************************************
 Function Name  : NAS_LCS_RcvWaitPeriodIntervelTimerExp
 Discription    : 处理周期间隔定时器超时
 Input          : ulIndex---------------索引
 Output         : None
 Return         : VOS_VOID
 History:
      1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_RcvWaitPeriodIntervelTimerExp
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG1("NAS_LCS_RcvWaitPeriodIntervelTimerExp:ulIndex= ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_RcvWaitPeriodIntervelTimerExp_ENUM, LNAS_LCS_InvalidEntityType, ulIndex);

    /* 是否为TAF MOLR */
    if (NAS_LCS_MO_LR_TAF_INDEX != ulIndex)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitPeriodIntervelTimerExp:Is not TAF-MOLR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitPeriodIntervelTimerExp_ENUM, LNAS_LCS_InvalidIndex);

        return ;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);
    if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitPeriodIntervelTimerExp:entity not exist!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitPeriodIntervelTimerExp_ENUM, LNAS_LCS_EntityNotExist);

        return ;
    }

    /* 状态是否为周期间隔 */
    if (NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitPeriodIntervelTimerExp:state invalid!");
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_EntityStateInvalid, NAS_LCS_GetEntityState(ulIndex));

        return ;
    }

    /* 实体状态转到等待网络响应 */
    NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_WAIT_NW_RSP);

    /* 启动等待网侧响应定时器 */
    NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_WAIT_NW_RSP_TIMER);

    /* 如果是连接态，则编码FACILITY发给网侧；否则请求建链 */
    if (NAS_LCS_CONN_STATE_CONN == NAS_LCS_GetEntityConnState(ulIndex))
    {
        /* 编码FACILITY消息，发给网侧 */
        NAS_LCS_SndFacility(ulIndex);
    }
    else
    {
        /* 给相应域发建链请求 */
        if (NAS_LCS_DOMAIN_TYPE_EPC_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndLmmEstReq(NAS_LCS_GetEntityTi(ulIndex));
        }
        else
        {
            NAS_LCS_SndMmEstReq(NAS_LCS_GetEntityTi(ulIndex));
        }

        /* 更新实体连接状态为建链过程中 */
        NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_ESTING);

        /* 重置建链尝试次数 */
        NAS_LCS_ResetEntityEstRetryTimers(ulIndex);
    }
}

/*****************************************************************************
 Function Name  : NAS_LCS_RcvWaitUeRspTimerExp
 Discription    : 处理等待用户响应定时器超时
 Input          : ulIndex---------------索引
 Output         : None
 Return         : VOS_VOID
 History:
      1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_RcvWaitUeRspTimerExp
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG1("NAS_LCS_RcvWaitUeRspTimerExp:ulIndex= ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_RcvWaitUeRspTimerExp_ENUM, LNAS_LCS_InvalidEntityType, ulIndex);

    if ((ulIndex > NAS_LCS_MT_LR_ENTITY_INDEX_END) || (ulIndex < NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitUeRspTimerExp:is not mt-lr!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_InvalidEntityType);

        return ;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);
    if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitUeRspTimerExp:entity not exist!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitUeRspTimerExp_ENUM, LNAS_LCS_EntityNotExist);

        return ;
    }

    /* 状态是否为等待用户回复 */
    if (NAS_LCS_ENTITY_STATE_WAIT_USER_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitUeRspTimerExp:state invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitUeRspTimerExp_ENUM, LNAS_LCS_EntityStateInvalid);

        return ;
    }

    /* 通知MM可以释放与此TI相关的LCS实体信息, MTLR接入层会通知MM是否允许释放链路 */
    NAS_LCS_JudgeSndMmRelReq(ulIndex);

    /* 释放LCS实体 */
    NAS_LCS_ClearSingleLcsEntity(ulIndex, TAF_LCS_CAUSE_LCS_USER_TIMER_OUT);
}


/*****************************************************************************
Function Name  : NAS_LCS_TimerMsgDistr
Description    : LCS模块定时器超时消息处理函数
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-28  新开发
*****************************************************************************/
VOS_VOID NAS_LCS_TimerMsgDistr( VOS_VOID *pRcvMsg )
{

    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType  = TI_NAS_LCS_TIMER_BUTT;
    VOS_UINT32                          ulIndex         = 0;

    NAS_LCS_NORM_LOG("NAS_LCS_TimerMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_TimerMsgDistr_ENUM, LNAS_ENTRY);

    ulIndex         = PS_GET_REL_TIMER_NAME(pRcvMsg);
    enLcsTimerType  = (NAS_LCS_TIMER_ID_ENUM_UINT8)PS_GET_REL_TIMER_PARA(pRcvMsg);

    NAS_LCS_SndOmTimerExpire(ulIndex, enLcsTimerType);

    /*根据消息名，调用相应的消息处理函数*/
    switch(enLcsTimerType)
    {
        case TI_NAS_LCS_WAIT_NW_RSP_TIMER:
            NAS_LCS_RcvWaitNwRspTimerExp(ulIndex);
            break;

        case TI_NAS_LCS_WAIT_UE_RSP_TIMER:
            NAS_LCS_RcvWaitUeRspTimerExp(ulIndex);
            break;

        case TI_NAS_LCS_WATI_REEST_TIMER:
            NAS_LCS_RcvWaitReestTimerExp(ulIndex);
            break;

        case TI_NAS_LCS_PERIOD_INTERVAL_TIMER:
            NAS_LCS_RcvWaitPeriodIntervelTimerExp(ulIndex);
            break;

        default:
            NAS_LCS_WARN_LOG("NAS_LCS_TimerMsgDistr:NORM: Error TimerId!");
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_TimerMsgDistr_ENUM, LNAS_LCS_InvalidTimerId);
            break;
    }

    return;
}


#endif
#ifdef __cplusplus
#if __cplusplus
    }
    #endif
#endif
/* end of NasLcsTimerMsgProc.c */
