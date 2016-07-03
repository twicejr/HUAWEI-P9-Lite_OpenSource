

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"
#include "rabminclude.h"
#include "NasRabmMain.h"
#include "NasRabmMsgProc.h"
#include "AtRabmInterface.h"

#include "NasUtranCtrlCommFunc.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#if (FEATURE_ON == FEATURE_BASTET)
#include "BastetRabmInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_RABM_MGR_C



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 当前系统模式 */
GMM_RABM_NET_RAT_ENUM_UINT32            g_enNasRabmSysMode;

/* 基于系统模式的函数处理指针表 */
NAS_RABM_PROC_FUNC_TBL_STRU            *g_pstNasRabmProcFuncTbl[NAS_MML_NET_RAT_TYPE_BUTT];

NAS_RABM_VOICEPREFER_CTX_STRU g_stNasRabmVoicePreferCtx;

/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_VOID NAS_RABM_RegProcFuncTbl(
    GMM_RABM_NET_RAT_ENUM_UINT32         enSysMode,
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFucTbl
)
{
    /* 系统模式有效性检查 */
    if (NAS_MML_NET_RAT_TYPE_BUTT == enSysMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RegProcFuncTbl: Wrong system mode.");
        return;
    }

    NAS_RABM_SetProFuncTblAddr(enSysMode, pstProcFucTbl);

}


VOS_VOID NAS_RABM_CtxInit(VOS_VOID)
{
    VOS_UINT32                          i;

#if (FEATURE_ON == FEATURE_LTE)
    /* 初始化系统模式: 默认为LTE */
    NAS_RABM_SetSysMode(NAS_MML_NET_RAT_TYPE_LTE);
#else
    /* 初始化系统模式: 默认为WCDMA */
    NAS_RABM_SetSysMode(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* 初始化函数处理指针表为NULL */
    for ( i = 0; i < NAS_MML_NET_RAT_TYPE_BUTT; i++)
    {
        NAS_RABM_SetProFuncTblAddr(i, VOS_NULL_PTR);
    }

    /* 初始化RABM实体 */
    Rabm_Init();
    NAS_Rabm2GInit();

    /* 初始化挂起标志 */
    NAS_RABM_ClearDataSuspendFlg();

    /* 初始化处理函数表 */
    NAS_RABM_InitProcFuncTbl();

}


VOS_VOID NAS_RABM_MsgProc(
    struct MsgCB                       *pMsg
)
{
    MSG_HEADER_STRU                    *pstMsg;
    struct MsgCB                       *pstDestMsg;


    pstDestMsg = VOS_NULL_PTR;

    /* 入口消息非空检查 */
    if (VOS_NULL_PTR == pMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM,
            "NAS_RABM_MsgProc: Message is NULL.");
        return;
    }

    /* 支持TD-SCDMA特性时，需对消息进行适配处理，将TD模的发送PID适配为W模的PID */
    if ( VOS_TRUE == NAS_UTRANCTRL_MsgProc(pMsg, &pstDestMsg) )
    {
        /* 消息在UTRANCTRL模块处理完成，直接返回，不进入后续处理 */
        return;
    }

    /* 替换消息指针 */
    pstMsg = (MSG_HEADER_STRU*)pstDestMsg;

    /* 处理消息 */
    switch (pstMsg->ulSenderPid)
    {
        case WUEPS_PID_SM:
            NAS_RABM_RcvSmMsg(pstDestMsg);
            break;

        case WUEPS_PID_GMM:
            NAS_RABM_RcvGmmMsg(pstDestMsg);
            break;

        case WUEPS_PID_AT:
            NAS_RABM_RcvAtMsg(pstDestMsg);
            break;

        case UEPS_PID_CDS:
            NAS_RABM_RcvCdsMsg(pstDestMsg);
            break;
#if (FEATURE_ON == FEATURE_BASTET)
        case UEPS_PID_BASTET:
            NAS_RABM_RcvBastetMsg(pstDestMsg);
            break;
#endif
        default:
            NAS_RABM_RcvCommMsg(pstDestMsg);
            break;
    }
}


VOS_VOID NAS_RABM_RcvSmMsg(
    struct MsgCB                       *pMsg
)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch (pstMsg->ulMsgName)
    {
        case RABMSM_ACTIVATE_IND:
            NAS_RABM_RcvSmActivateInd((RABMSM_ACTIVATE_IND_STRU*)pMsg);
            break;

        case RABMSM_DEACTIVATE_IND:
            NAS_RABM_RcvSmDeactivateInd((RABMSM_DEACTIVATE_IND_STRU*)pMsg);
            break;

        case RABMSM_MODIFY_IND:
            NAS_RABM_RcvSmModifyInd((RABMSM_MODIFY_IND_STRU*)pMsg);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case ID_SM_RABM_BEARER_ACTIVATE_IND:
            NAS_RABM_RcvSmBearerActivateInd((SM_RABM_BEARER_ACTIVATE_IND_STRU*)pMsg);
            break;

        case ID_SM_RABM_BEARER_DEACTIVATE_IND:
            NAS_RABM_RcvSmBearerDeactivateInd((SM_RABM_BEARER_DEACTIVATE_IND_STRU*)pMsg);
            break;

        case ID_SM_RABM_BEARER_MODIFY_IND:
            NAS_RABM_RcvSmBearerModifyInd((SM_RABM_BEARER_MODIFY_IND_STRU*)pMsg);
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_RcvSmMsg: Unknown message from SM.");
            break;
    }
}


VOS_VOID NAS_RABM_RcvGmmMsg(
    struct MsgCB                       *pMsg
)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch (pstMsg->ulMsgName)
    {
        case ID_GMM_RABM_REESTABLISH_CNF:
            NAS_RABM_RcvGmmReestablishCnf((GMMRABM_REESTABLISH_CNF_STRU*)pMsg);
            break;

        case ID_GMM_RABM_SYS_SRV_CHG_IND:
            NAS_RABM_RcvGmmSysSrvChgInd((GMM_RABM_SYS_SRV_CHG_IND_STRU*)pMsg);
            break;

        case ID_GMM_RABM_MML_PROC_STATUS_QRY_CNF:
            NAS_RABM_RcvGmmMmlProcStatusQryCnf(pMsg);
            break;

        default:
            NAS_RABM_RcvCommMsg(pMsg);
            break;
    }
}


VOS_VOID NAS_RABM_RcvSmActivateInd(
    RABMSM_ACTIVATE_IND_STRU           *pstSmActivateInd
)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFuncTbl;
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 判断当前的系统模式是否有效 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();
    if (NAS_MML_NET_RAT_TYPE_BUTT == enCurrentSysMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvSmActivateInd: Invalid System Mode.");
        return;
    }

    /* 根据当前系统模式获取对应的处理函数表的指针 */
    pstProcFuncTbl = NAS_RABM_GetProFuncTblAddr(enCurrentSysMode);

    /* 确认函数处理表已经注册 */
    if (VOS_NULL_PTR != pstProcFuncTbl)
    {
        if (VOS_NULL_PTR != pstProcFuncTbl->pSmActivateIndProcFunc)
        {
            /* 调用对应模式的处理函数 */
            pstProcFuncTbl->pSmActivateIndProcFunc(pstSmActivateInd);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_RcvSmActivateInd: pSmActivateIndProcFunc is not registered.");
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvSmActivateInd: Msg is received in wrong system mode.");
    }
}


VOS_VOID NAS_RABM_RcvSmDeactivateInd(
    RABMSM_DEACTIVATE_IND_STRU         *pstSmDeactivateInd
)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFuncTbl;
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 判断当前的系统模式是否有效 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();
    if (NAS_MML_NET_RAT_TYPE_BUTT == enCurrentSysMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvSmDeactivateInd: Invalid System Mode.");
        return;
    }

    /* 根据当前系统模式获取对应的处理函数表的指针 */
    pstProcFuncTbl = NAS_RABM_GetProFuncTblAddr(enCurrentSysMode);

    /* 确认函数处理表已经注册 */
    if (VOS_NULL_PTR != pstProcFuncTbl)
    {
        if (VOS_NULL_PTR != pstProcFuncTbl->pSmDeactivateIndProcFunc)
        {
            /* 调用对应模式的处理函数 */
            pstProcFuncTbl->pSmDeactivateIndProcFunc(pstSmDeactivateInd);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_RcvSmDeactivateInd: pSmDeactivateIndProcFunc is not registered.");
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvSmDeactivateInd: Msg is received in wrong system mode.");
    }
}


VOS_VOID NAS_RABM_RcvSmModifyInd(
    RABMSM_MODIFY_IND_STRU             *pstSmModifyInd
)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFuncTbl;
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 判断当前的系统模式是否有效 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();
    if (NAS_MML_NET_RAT_TYPE_BUTT == enCurrentSysMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvSmModifyInd: Invalid System Mode.");
        return;
    }

    /* 根据当前系统模式获取对应的处理函数表的指针 */
    pstProcFuncTbl = NAS_RABM_GetProFuncTblAddr(enCurrentSysMode);

    /* 确认函数处理表已经注册 */
    if (VOS_NULL_PTR != pstProcFuncTbl)
    {
        if (VOS_NULL_PTR != pstProcFuncTbl->pSmModifyIndProcFunc)
        {
            /* 调用对应模式的处理函数 */
            pstProcFuncTbl->pSmModifyIndProcFunc(pstSmModifyInd);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_RcvSmModifyInd: pSmModifyIndProcFunc is not registered.");
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvSmModifyInd: Msg is received in wrong system mode.");
    }
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_RABM_RcvSmBearerActivateInd(
    SM_RABM_BEARER_ACTIVATE_IND_STRU   *pstSmBearerActivateInd
)
{
    RABM_ENTITY_PS_STRU                *pstPsEnt;
    VOS_UINT8                           ucEntId;

    /* 获取PS域RABM实体指针 */
    ucEntId  = (VOS_UINT8)(pstSmBearerActivateInd->ulNsapi - RABM_NSAPI_OFFSET);
    pstPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);

    /* 更新QOS */
    pstPsEnt->QoS.ulQosLength   = pstSmBearerActivateInd->stQos.ulLength;
    PS_MEM_CPY(pstPsEnt->QoS.aucQosValue,
               pstSmBearerActivateInd->stQos.aucQosValue,
               NAS_RABM_MAX_QOS_LEN);

    /* 更新PPP标识 */
    pstPsEnt->ucPppFlg          = RABM_SM_IP_PROT;

    /* 创建RAB_MAP实体 */
    NAS_RABM_CreateRabMapEntity((VOS_UINT8)pstSmBearerActivateInd->ulNsapi,
                                (VOS_UINT8)pstSmBearerActivateInd->ulLinkdNsapi,
                                (VOS_UINT8)pstSmBearerActivateInd->ulNsapi);

    /* 更新RABM状态至挂起状态 */
    RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);

    return;
}


VOS_VOID NAS_RABM_RcvSmBearerModifyInd(
    SM_RABM_BEARER_MODIFY_IND_STRU     *pstSmBearerModifyInd
)
{
    RABM_ENTITY_PS_STRU                *pstPsEnt;
    VOS_UINT8                           ucEntId;

    /* 获取PS域RABM实体索引 */
    ucEntId = (VOS_UINT8)(pstSmBearerModifyInd->ulNsapi - RABM_NSAPI_OFFSET);

    /* 检查PS域RABM实体状态是否正确 */
    if (RABM_NULL == NAS_RABM_GetWPsEntState(ucEntId))
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_RcvSmBearerModifyInd: Wrong state of RABM entity. NSAPI:",
            pstSmBearerModifyInd->ulNsapi);
        return;
    }

    /* 获取PS域RABM实体指针 */
    pstPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);

    /* 更新QOS */
    pstPsEnt->QoS.ulQosLength = pstSmBearerModifyInd->stQos.ulLength;
    PS_MEM_CPY(pstPsEnt->QoS.aucQosValue,
               pstSmBearerModifyInd->stQos.aucQosValue,
               NAS_RABM_MAX_QOS_LEN);

    return;
}


VOS_VOID NAS_RABM_RcvSmBearerDeactivateInd(
    SM_RABM_BEARER_DEACTIVATE_IND_STRU *pstSmBearerDeactivateInd
)
{
    VOS_UINT8                           ucEntId;

    /* 获取PS域RABM实体指针 */
    ucEntId = (VOS_UINT8)(pstSmBearerDeactivateInd->ulNsapi - RABM_NSAPI_OFFSET);

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_RABM_GetCurrentSysMode())
    {
        /* G实体状态置为RABM_2G_NULL */
        RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_2G_NULL);

        /* 清除G实体信息 */
        NAS_RABM_ClearRabmGPsEnt(ucEntId);
    }
    else
    {
        /* W实体状态置为RABM_NULL */
        RABM_SetWState(ucEntId, RABM_NULL);

        /* 清除G实体信息 */
        NAS_RABM_ClearRabmWPsEnt(ucEntId);
    }

    /* 删除RAB_MAP实体 */
    RABM_DelRabMap((VOS_UINT8)pstSmBearerDeactivateInd->ulNsapi);
}
#endif


VOS_VOID NAS_RABM_RcvGmmReestablishCnf(
    GMMRABM_REESTABLISH_CNF_STRU       *pstGmmReestablishCnf
)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFuncTbl;
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 判断当前的系统模式是否有效 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();
    if (NAS_MML_NET_RAT_TYPE_BUTT == enCurrentSysMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvGmmReestablishCnf: Invalid System Mode.");
        return;
    }

    /* 根据当前系统模式获取对应的处理函数表的指针 */
    pstProcFuncTbl = NAS_RABM_GetProFuncTblAddr(enCurrentSysMode);

    /* 确认函数处理表已经注册 */
    if (VOS_NULL_PTR != pstProcFuncTbl)
    {
        if (VOS_NULL_PTR != pstProcFuncTbl->pGmmReestablishCnfProcFunc)
        {
            /* 调用对应模式的处理函数 */
            pstProcFuncTbl->pGmmReestablishCnfProcFunc(pstGmmReestablishCnf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_RcvGmmReestablishCnf: pGmmReestablishCnfProcFunc is not registered.");
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvGmmReestablishCnf: Message is received in wrong system mode.");
    }
}


VOS_VOID NAS_RABM_RcvGmmSysSrvChgInd(
    GMM_RABM_SYS_SRV_CHG_IND_STRU      *pstGmmSysSrvChgInd
)
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode;

    /* 判断当前的系统模式是否有效 */
    enOldSysMode = NAS_RABM_GetCurrentSysMode();

    /* 根据挂起指示标志是否设置, 执行挂起或恢复处理 */
    if (VOS_TRUE == pstGmmSysSrvChgInd->bDataSuspendFlg)
    {
        NAS_RABM_RcvDataSuspendInd(pstGmmSysSrvChgInd->bRatChangeFlg);
        NAS_RABM_RcvSysModeChgInd(pstGmmSysSrvChgInd->enSysMode);
    }
    else
    {
        NAS_RABM_RcvSysModeChgInd(pstGmmSysSrvChgInd->enSysMode);

        /* GMM通知RABM模块进行恢复时需要通知RABM模块是否需要进行RAB的恢复，
           RABM模块进行恢复时，判断是否需要等待接入层进行RAB恢复 */
        NAS_RABM_RcvDataResumeInd(pstGmmSysSrvChgInd->ucRebuildRabFlag);
    }

    NAS_RABM_SysModeChgProcFastDorm(enOldSysMode,pstGmmSysSrvChgInd->enSysMode);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    /* 离开或进入W模需要启动VP判决 */
    if  ( (NAS_MML_NET_RAT_TYPE_WCDMA == enOldSysMode)
        || (NAS_MML_NET_RAT_TYPE_WCDMA == pstGmmSysSrvChgInd->enSysMode))
    {
        NAS_RABM_VoicePreferActivateJudgeStepOne();
    }
#endif
}


VOS_VOID NAS_RABM_RcvDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFuncTbl;
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 判断当前的系统模式是否有效 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();
    if (NAS_MML_NET_RAT_TYPE_BUTT == enCurrentSysMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvDataSuspendInd: Invalid System Mode.");
        return;
    }

    /* 根据当前系统模式获取对应的处理函数表的指针 */
    pstProcFuncTbl = NAS_RABM_GetProFuncTblAddr(enCurrentSysMode);

    /* 确认函数处理表已经注册 */
    if (VOS_NULL_PTR != pstProcFuncTbl)
    {
        if (VOS_NULL_PTR != pstProcFuncTbl->pDataSuspendIndProcFunc)
        {
            /* 调用对应模式的处理函数 */
            pstProcFuncTbl->pDataSuspendIndProcFunc(bRatChangeFlg);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_RcvDataSuspendInd: pDataSuspendIndProcFunc is not registered.");
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvDataSuspendInd: Message is received in wrong system mode.");
    }
}


VOS_VOID NAS_RABM_RcvDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFuncTbl;
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 判断当前的系统模式是否有效 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();
    if (NAS_MML_NET_RAT_TYPE_BUTT == enCurrentSysMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvDataResumeInd: Invalid System Mode.");
        return;
    }

    /* 根据当前系统模式获取对应的处理函数表的指针 */
    pstProcFuncTbl = NAS_RABM_GetProFuncTblAddr(enCurrentSysMode);

    /* 确认函数处理表已经注册 */
    if (VOS_NULL_PTR != pstProcFuncTbl)
    {
        if (VOS_NULL_PTR != pstProcFuncTbl->pDataResumeIndProcFunc)
        {
            /* 调用对应模式的处理函数 */
            pstProcFuncTbl->pDataResumeIndProcFunc(ucRebuildRabFlag);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_RcvDataResumeInd: pDataResumeIndProcFunc is not registered.");
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvDataResumeInd: Message is received in wrong system mode.");
    }
}


VOS_VOID NAS_RABM_RcvSysModeChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFuncTbl;
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode;

    /* 判断当前的系统模式是否有效 */
    enOldSysMode = NAS_RABM_GetCurrentSysMode();

    /* 检测系统模式有效性, 若无效, 不更新系统模式 */
    if (NAS_MML_NET_RAT_TYPE_BUTT == enNewSysMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvSysModeChgInd: Invalid System Mode.");
        return;
    }

    /* 更新系统模式 */
    NAS_RABM_SetSysMode(enNewSysMode);

    /* 根据当前系统模式获取对应的处理函数表的指针 */
    pstProcFuncTbl = NAS_RABM_GetProFuncTblAddr(enOldSysMode);

    /* 确认函数处理表已经注册 */
    if (VOS_NULL_PTR != pstProcFuncTbl)
    {
        if (VOS_NULL_PTR != pstProcFuncTbl->pSysModeChgIndProcFunc)
        {
            /* 调用对应模式的处理函数 */
            pstProcFuncTbl->pSysModeChgIndProcFunc(enOldSysMode, enNewSysMode);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_RcvSysModeChgInd: pDataResumeIndProcFunc is not registered.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM,
            "NAS_RABM_RcvSysModeChgInd: Message is received in wrong system mode.");
    }
}


VOS_VOID NAS_RABM_RcvCommMsg(
    struct MsgCB                       *pMsg
)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFuncTbl;
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 判断当前的系统模式是否有效 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();
    if (NAS_MML_NET_RAT_TYPE_BUTT == enCurrentSysMode)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_ProcSysSrvChgInd: Invalid System Mode.");
        return;
    }

    /* 根据当前系统模式获取对应的处理函数表的指针 */
    pstProcFuncTbl = NAS_RABM_GetProFuncTblAddr(enCurrentSysMode);
    if (VOS_NULL_PTR != pstProcFuncTbl)
    {
        if (VOS_NULL_PTR != pstProcFuncTbl->pTaskEntry)
        {
            /* 调用对应模式的处理函数 */
            pstProcFuncTbl->pTaskEntry(pMsg);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_ProcessCommMsg: TaskEntry is not registered.");
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_ProcessCommMsg: Msg is received in wrong system mode.");
    }
}


VOS_VOID NAS_RABM_RcvAtMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    switch (pstMsgHeader->ulMsgName)
    {
        case ID_AT_RABM_SET_FASTDORM_PARA_REQ:
            NAS_RABM_RcvSetFastDormParaReq((AT_RABM_SET_FASTDORM_PARA_REQ_STRU*)pstMsg);
            break;

        case ID_AT_RABM_QRY_FASTDORM_PARA_REQ:
            NAS_RABM_RcvGetFastDormParaReq((AT_RABM_QRY_FASTDORM_PARA_REQ_STRU*)pstMsg);
            break;

        case ID_AT_RABM_SET_RELEASE_RRC_REQ:
            NAS_RABM_RcvReleaseRrcReq((AT_RABM_RELEASE_RRC_REQ_STRU *)pstMsg);
            break;

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
        case ID_AT_RABM_SET_VOICEPREFER_PARA_REQ:
            NAS_RABM_RcvSetVoicePreferParaReq((AT_RABM_SET_VOICEPREFER_PARA_REQ_STRU*)pstMsg);
            break;

        case ID_AT_RABM_QRY_VOICEPREFER_PARA_REQ:
            NAS_RABM_RcvGetVoicePreferParaReq((AT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU*)pstMsg);
            break;
#endif
        default:
            break;
    }
}


VOS_VOID NAS_RABM_RcvCdsMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    switch (pstMsgHeader->ulMsgName)
    {
        case ID_CDS_RABM_SERVICE_IND:
            NAS_RABM_RcvCdsServiceInd((CDS_RABM_SERVICE_IND_STRU *)pstMsg);
            break;

        default:
            break;
    }
}


VOS_UINT32 NAS_RABM_IsDataServiceRequestPending(VOS_VOID)
{
    if (VOS_TRUE == NAS_RABM_GetRabRsestTimerFlg())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_RABM_IsRabReestablishPending(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    if (VOS_TRUE == NAS_RABM_GetRabRsestTimerFlg())
    {
        return VOS_FALSE;
    }

    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(ucEntId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID NAS_RABM_RcvCdsServiceInd(
    CDS_RABM_SERVICE_IND_STRU          *pstCdsServiceInd
)
{
    /* 检查RABID有效性 */
    if (!RAB_MAP_RAB_IS_VALID(pstCdsServiceInd->ucRabId))
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_RcvCdsServiceInd: Invalid RABID. <RABID>", pstCdsServiceInd->ucRabId);
        return;
    }

    switch (NAS_RABM_GetWPsEntState(pstCdsServiceInd->ucRabId - RABM_NSAPI_OFFSET))
    {
        case RABM_NSAPI_ACTIVE_WITH_RAB:
            NAS_NORMAL_LOG1(WUEPS_PID_RABM,
                "NAS_RABM_RcvCdsServiceInd: RABID is already active. <RABID>", pstCdsServiceInd->ucRabId);
            NAS_RABM_SndCdsSendBuffDataInd(pstCdsServiceInd->ucRabId, CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
            break;

        case RABM_NSAPI_ACTIVE_NO_RAB:
            if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(pstCdsServiceInd->ucRabId - RABM_NSAPI_OFFSET))
            {
                NAS_NORMAL_LOG1(WUEPS_PID_RABM,
                    "NAS_RABM_RcvCdsServiceInd: Reestablish is in process. <RABID>", pstCdsServiceInd->ucRabId);
            }
            else if (VOS_TRUE == NAS_RABM_IsDataServiceRequestPending())
            {
                NAS_NORMAL_LOG1(WUEPS_PID_RABM,
                    "NAS_RABM_RcvCdsServiceInd: Data service request is sent, set reestablish flag. <RABID>", pstCdsServiceInd->ucRabId);
                NAS_RABM_SetWPsEntRabReestFlg(pstCdsServiceInd->ucRabId - RABM_NSAPI_OFFSET);
            }
            else if (VOS_TRUE == NAS_RABM_IsRabReestablishPending())
            {
                NAS_NORMAL_LOG1(WUEPS_PID_RABM,
                    "NAS_RABM_RcvCdsServiceInd: Start RB setup protect timer. <RABID>", pstCdsServiceInd->ucRabId);
                NAS_RABM_SetWPsEntRabReestFlg(pstCdsServiceInd->ucRabId - RABM_NSAPI_OFFSET);
                NAS_RABM_StartReestRabPendingTmr(pstCdsServiceInd->ucRabId);
            }
            else
            {
                NAS_NORMAL_LOG1(WUEPS_PID_RABM,
                    "NAS_RABM_RcvCdsServiceInd: Send data service request.  <RABID>", pstCdsServiceInd->ucRabId);
                NAS_RABM_SetWPsEntRabReestFlg(pstCdsServiceInd->ucRabId - RABM_NSAPI_OFFSET);
                NAS_RABM_SetRabRsestTimerFlg();

                RABM_TimerStart(RABM_REESTABLISH_REQ_SENT, RABM_RABM_REEST_PROT_TIMER_LEN);
                RABM_SndRabReestReq();
            }
            break;

        default:
            NAS_WARNING_LOG1(WUEPS_PID_RABM,
                "NAS_RABM_RcvCdsServiceInd: Can't reestablish RAB. <RABID>", pstCdsServiceInd->ucRabId);
            NAS_RABM_SndCdsFreeBuffDataInd(pstCdsServiceInd->ucRabId);
            break;
    }

    return;
}

#if (FEATURE_ON == FEATURE_HUAWEI_VP)

VOS_UINT32 NAS_RABM_VoicePreferGetVpStatus(VOS_VOID)
{
    return g_stNasRabmVoicePreferCtx.ulCpVoicePreferActiveFlag;
}


VOS_VOID NAS_RABM_VoicePreferSetVpStatus(VOS_UINT32 ulVpStatus)
{
    g_stNasRabmVoicePreferCtx.ulCpVoicePreferActiveFlag = ulVpStatus;

    return;
}


VOS_UINT8 NAS_RABM_VoicePreferGetNvEnableFlag(VOS_VOID)
{
    return g_stNasRabmVoicePreferCtx.ucVoicePreferNvimEnableFlag;
}


VOS_UINT8 NAS_RABM_VoicePreferGetReQryGmmCnt(VOS_VOID)
{
    return g_stNasRabmVoicePreferCtx.ucVoicePreferReQryGmmCnt;
}


VOS_VOID NAS_RABM_VoicePreferClrReQryGmmCnt(VOS_VOID)
{
    g_stNasRabmVoicePreferCtx.ucVoicePreferReQryGmmCnt = 0;

    return;
}


VOS_VOID NAS_RABM_VoicePreferIncReQryGmmCnt(VOS_VOID)
{
    g_stNasRabmVoicePreferCtx.ucVoicePreferReQryGmmCnt ++;

    return;
}


VOS_UINT32 NAS_RABM_VoicePreferGetVoiceCallExsitFlag(VOS_VOID)
{
    return g_stNasRabmVoicePreferCtx.ulVoiceCallExsitFlag;
}


VOS_UINT32 NAS_RABM_VoicePreferGetStopVpFlag(VOS_VOID)
{
    return g_stNasRabmVoicePreferCtx.ulReceiveApVoicePreferStopFlag;
}

VOS_VOID NAS_RABM_VoicePreferSetStopVpFlag(VOS_UINT32 ulStopVpFlag)
{
    g_stNasRabmVoicePreferCtx.ulReceiveApVoicePreferStopFlag = ulStopVpFlag;

    return;
}


VOS_UINT32 NAS_RABM_VoicePreferGetApStatusMask(VOS_VOID)
{
    return g_stNasRabmVoicePreferCtx.ulApVoicePreferStatusMask;
}


VOS_VOID NAS_RABM_VoicePreferSetApStatusMask(VOS_UINT32 ulApStatusMask)
{
    g_stNasRabmVoicePreferCtx.ulApVoicePreferStatusMask = ulApStatusMask;

    return;
}

VOS_VOID NAS_RABM_InitVoicePreferCtx(VOS_VOID)
{
    g_stNasRabmVoicePreferCtx.ulApVoicePreferStatusMask  = 0xFFFFFFFF;
    g_stNasRabmVoicePreferCtx.ulVoiceCallExsitFlag  = VOS_FALSE;

    g_stNasRabmVoicePreferCtx.ulCpVoicePreferActiveFlag = VOS_FALSE;
    g_stNasRabmVoicePreferCtx.ulReceiveApVoicePreferStopFlag  = VOS_FALSE;

    g_stNasRabmVoicePreferCtx.ulCurCampMcc = 0xFFFFFFFF;
    g_stNasRabmVoicePreferCtx.ulCurCampMnc = 0xFFFFFFFF;

    g_stNasRabmVoicePreferCtx.ucVoicePreferReQryGmmCnt = 0;

    /* 读取NV */
    NAS_RABM_ReadVoicePreferNvim();

    return;
}


VOS_VOID NAS_RABM_ReadVoicePreferNvim(VOS_VOID)
{
    NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU                   stVoicePreferCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stVoicePreferCfg, 0x00, sizeof(NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU));

    /* 读NV失败，认为不允许VoicePrefer */
    (VOS_VOID)NV_GetLength(en_NV_Item_Wcdma_Voice_Prefer_Cfg, &ulLength);

    if (ulLength > sizeof(NAS_RABM_NVIM_WCDMA_VOICE_PREFER_STRU))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_ReadVoicePreferNvim:WARNING:NV_GetLength ulLength fail!");
        g_stNasRabmVoicePreferCtx.ucVoicePreferNvimEnableFlag = VOS_FALSE;
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_Wcdma_Voice_Prefer_Cfg, &stVoicePreferCfg,
                          ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_ReadVoicePreferNvim:WARNING:NV_Read faild!");
        g_stNasRabmVoicePreferCtx.ucVoicePreferNvimEnableFlag = VOS_FALSE;
        return;
    }

    g_stNasRabmVoicePreferCtx.ucVoicePreferNvimEnableFlag = stVoicePreferCfg.ucEnableFlag;
    g_stNasRabmVoicePreferCtx.ulNvTestMcc = stVoicePreferCfg.ulMcc;
    g_stNasRabmVoicePreferCtx.ulNvTestMnc = stVoicePreferCfg.ulMnc;

    return;
}


VOS_VOID NAS_RABM_RcvSetVoicePreferParaReq(AT_RABM_SET_VOICEPREFER_PARA_REQ_STRU *pstVoicePreferPara)
{
    /* NV配置使能VP*/
    if (VOS_TRUE != NAS_RABM_VoicePreferGetNvEnableFlag())
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_RcvSetVoicePreferParaReq:WARNING:NV disable VP!");
        NAS_RABM_SndAtSetVoicePreferParaCnf(pstVoicePreferPara->usClientId,pstVoicePreferPara->ucOpId,AT_RABM_PARA_SET_RSLT_FAIL);
        return;
    }

    NAS_RABM_VoicePreferSetApStatusMask(pstVoicePreferPara->ulVoicePreferApStatus);

    NAS_RABM_SndAtSetVoicePreferParaCnf(pstVoicePreferPara->usClientId,pstVoicePreferPara->ucOpId,AT_RABM_PARA_SET_RSLT_SUCC);

    /* 启动VP生效判决*/
    NAS_RABM_VoicePreferActivateJudgeStepOne();

    return;
}


VOS_VOID NAS_RABM_RcvGetVoicePreferParaReq(
    AT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU *pstVoicePreferPara)
{
    /* 回复查询结果 */
    NAS_RABM_SndAtQryVoicePreferParaCnf(pstVoicePreferPara->usClientId,
                                     pstVoicePreferPara->ucOpId,
                                     (VOS_UINT32)NAS_RABM_VoicePreferGetNvEnableFlag());

    return;
}


VOS_VOID NAS_RABM_RcvVoicePreferCsExistInd(VOS_VOID *pstMsg)
{
    CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU                 *pstVoiceInd;

    pstVoiceInd = (CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU*)pstMsg;

    /* NV配置使能VP*/
    if (VOS_TRUE != NAS_RABM_VoicePreferGetNvEnableFlag())
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_RcvVoicePreferCsExistInd:WARNING:NV disable VP!");
        return;
    }

    /*保存CALL 传过来的参数*/
    g_stNasRabmVoicePreferCtx.ulVoiceCallExsitFlag = pstVoiceInd->ulVoiceFlag;
    g_stNasRabmVoicePreferCtx.ulCurCampMcc = pstVoiceInd->ulCampMcc;
    g_stNasRabmVoicePreferCtx.ulCurCampMnc = pstVoiceInd->ulCampMnc;

    /* 启动VP激活判断*/
    NAS_RABM_VoicePreferActivateJudgeStepOne();

    return;
}


VOS_UINT32 NAS_RABM_VoicePreferIsPdpActive(VOS_VOID)
{
    VOS_UINT32                          ulEntId;
    VOS_UINT8                           ucState;

    for (ulEntId = 0; ulEntId < RABM_3G_PS_MAX_ENT_NUM; ulEntId++)
    {
        ucState = NAS_RABM_GetWPsEntState(ulEntId);
        if ( (RABM_NSAPI_ACTIVE_NO_RAB == ucState)
          || (RABM_NSAPI_ACTIVE_WITH_RAB == ucState) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_RABM_VoicePreferApStatusMatch(VOS_VOID)
{
    VOS_UINT32      ulAgpsStatus;
    VOS_UINT32      ulMmsStatus;
    VOS_UINT32      ulTetheringStatus;
    VOS_UINT32      ulWifiHotSpotStatus;
    VOS_UINT32      ulBtSharingStatus;
    VOS_UINT32      ulApScreenStatus;
    VOS_UINT32      ulVpEnableStatus;

    VOS_UINT32      ulStoredApMask;

    ulStoredApMask = NAS_RABM_VoicePreferGetApStatusMask();

    ulAgpsStatus =           (ulStoredApMask & VP_AGPS_STATUS_MASK) >> 1;
    ulMmsStatus =            (ulStoredApMask & VP_MMS_STATUS_MASK) >> 2;
    ulTetheringStatus =      (ulStoredApMask & VP_TETHERING_STATUS_MASK) >> 4;
    ulWifiHotSpotStatus =    (ulStoredApMask & VP_WIFI_HOTSPOT_STATUS_MASK) >> 5;
    ulBtSharingStatus =      (ulStoredApMask & VP_BT_SHARING_STATUS_MASK) >> 6;
    ulApScreenStatus =       (ulStoredApMask & VP_SCREEN_STATUS_MASK) >> 7;
    ulVpEnableStatus =       (ulStoredApMask & VP_ENABLE_MASK) >> 8;

    /* AP 侧VP开关需要打开*/
    if (VOS_FALSE == ulVpEnableStatus)
    {
        return VOS_FALSE;
    }

    /* VP生效需要灭屏状态*/
    if (VOS_TRUE == ulApScreenStatus)
    {
        return VOS_FALSE;
    }

    /* VP生效不能存在列外程序*/
    if (ulAgpsStatus || ulMmsStatus || ulTetheringStatus || ulWifiHotSpotStatus || ulBtSharingStatus)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_RABM_VoicePreferPlmnMatch(VOS_VOID)
{
    VOS_UINT32      ulHexMcc;/*十六进制形式的PLMN*/
    VOS_UINT32      ulHexMnc;


    ulHexMcc = g_stNasRabmVoicePreferCtx.ulCurCampMcc;
    ulHexMnc = g_stNasRabmVoicePreferCtx.ulCurCampMnc;

    /* china unicom */
    if ((0x460 == ulHexMcc) && ((0xF01 == ulHexMnc) || (0xF06 == ulHexMnc) ))
    {
        return VOS_TRUE;
    }

    /* CHT,FET,TCC@Taiwan */
    if ((0x466 == ulHexMcc) && ((0xF92 == ulHexMnc) || (0xF97 == ulHexMnc) || (0xF01 == ulHexMnc)))
    {
        return VOS_TRUE;
    }

    /* 测试网络*/
    if ((g_stNasRabmVoicePreferCtx.ulNvTestMcc == ulHexMcc) && (g_stNasRabmVoicePreferCtx.ulNvTestMnc == ulHexMnc))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_UINT32 NAS_RABM_IsVpActivateMatchInStepOne(VOS_VOID)
{
    /* NV配置使能VP*/
    if (VOS_TRUE != NAS_RABM_VoicePreferGetNvEnableFlag())
    {
        return VOS_FALSE;
    }

    /* VP生效仅在W模下 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_RABM_GetCurrentSysMode())
    {
       return VOS_FALSE;
    }
    if (NAS_UTRANCTRL_UTRAN_MODE_FDD != NAS_UTRANCTRL_GetCurrUtranMode())
    {
       return VOS_FALSE;
    }

    /* VP 生效需要存在语音业务*/
    if (VOS_TRUE != NAS_RABM_VoicePreferGetVoiceCallExsitFlag())
    {
        return VOS_FALSE;
    }

    /* VP 生效需要PDP 处于激活态*/
    if (VOS_TRUE != NAS_RABM_VoicePreferIsPdpActive())
    {
       return VOS_FALSE;
    }

    /* AP满足VP生效条件 */
    if (VOS_TRUE != NAS_RABM_VoicePreferApStatusMatch())
    {
       return VOS_FALSE;
    }

    /* VP生效需要当前的注册网络是已经测试过的网络或制定测试网络*/
    if (VOS_TRUE != NAS_RABM_VoicePreferPlmnMatch())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}


VOS_VOID NAS_RABM_VoicePreferActivateJudgeStepOne(VOS_VOID)
{
    VOS_UINT32      ulVpActMatch;
    VOS_UINT32      ulOldVpStatus;

    ulVpActMatch = NAS_RABM_IsVpActivateMatchInStepOne();
    ulOldVpStatus = NAS_RABM_VoicePreferGetVpStatus();

    /* 不满足初步激活条件*/
    if (VOS_FALSE == ulVpActMatch)
    {
        /* 定时器超时事件可能在队列中，就处理了AP 下发的停止VoicePrefer ,延迟超时处理中需要判断该标志 */
        NAS_RABM_VoicePreferSetStopVpFlag(VOS_TRUE);
        /* 把延迟激活和重试查询GMM定时器停止,函数里面会判断定时器是否启动 */
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_VOICEPREFER_DELAY);
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY);

        /* 当前已经处于激活状态*/
        if (VOS_TRUE == ulOldVpStatus)
        {
            /* 使VP去激活，并通知其他模块*/
            NAS_RABM_VoicePreferSetVpStatus(VOS_FALSE);
            NAS_RABM_SendVpActIndToOtherModule(VOS_FALSE);
        }
        /* 当前不处于激活状态,前面已经处理，这里不再进行任何操作*/
    }
    /* 满足初步激活条件 */
    else
    {   /*满足初步激活条件并且已经处于激活态不需要任何操作*/
        if(VOS_TRUE == ulOldVpStatus)
        {
            NAS_NORMAL_LOG(WUEPS_PID_RABM,
             "NAS_RABM_VoicePreferActivateJudgeStepOne: VP Already Activated");
        }
        /* 满足初步激活条件但是当前并没有处于激活状态 */
        else
        {
            /* 如果延迟定时器没有启动,启动延迟定时器*/
            if(NAS_RABM_TIMER_STATUS_STOP
                == NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_COMMON,RABM_TIMER_VOICEPREFER_DELAY))
            {
                NAS_RabmStartTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_VOICEPREFER_DELAY);
                /* 延迟激活定时器启动时应停止延迟查询GMM定时器 */
                NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY);

                NAS_RABM_VoicePreferSetStopVpFlag(VOS_FALSE);
            }
            /* 如果延迟定时器已经启动,保持原来定时器不重新启动*/
        }
    }

    return;
}

VOS_VOID NAS_RABM_VoicePreferActivateJudgeStepTwo(VOS_VOID)
{
    VOS_UINT32      ulVpActMatchInStepOne;

    ulVpActMatchInStepOne = NAS_RABM_IsVpActivateMatchInStepOne();

    /* 初步激活条件不再满足不激活VP */
    if (VOS_FALSE == ulVpActMatchInStepOne)
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_VoicePreferActivateJudgeStepTwo: ulVpActStepOne Not Matched,So Cannot Act VP");
    }
    /* 初步激活条件仍然满足需要激活VP */
    else
    {
        NAS_RABM_VoicePreferSetVpStatus(VOS_TRUE);
        /*给其他模块发送VP激活指示*/
        NAS_RABM_SendVpActIndToOtherModule(VOS_TRUE);
    }
    return;
}

VOS_VOID NAS_RABM_VoicePreferDelayExpired(VOS_VOID)
{
    /* 停止定时器 */
    NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_VOICEPREFER_DELAY);
    /* 定时器超时事件可能在队列中，就处理了AP 下发的停止VoicePrefer ,这种
        场景不再激活VP */
    if (VOS_TRUE == NAS_RABM_VoicePreferGetStopVpFlag())
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_VoicePreferDelayExpired: Have Receive AP Stop VoicePrefer,So Donot Send Gmm Qry!");
        return;
    }
    /* 查询是否存在GMM专有流程 */
    NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_VOICEPREFER_ENUM);
   /* 初次查询清重试查询次数*/
    NAS_RABM_VoicePreferClrReQryGmmCnt();

    return;
}

VOS_VOID NAS_RABM_VoicePreferReQryGmmDelayExpired(VOS_VOID)
{
    /* 停止定时器*/
    NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY);
    NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_VOICEPREFER_ENUM);
    NAS_RABM_VoicePreferIncReQryGmmCnt();

    return;
}


VOS_VOID NAS_RABM_RcvGmmVoicePreferMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU                   *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    if ( (VOS_TRUE != pstProcStatus->stMmlProcStatus.bitOpGmmSpecificProcedure)
      && (VOS_TRUE != pstProcStatus->stMmlProcStatus.bitOpPsSmsService)
      && (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpCsSignal))
    {
        NAS_RABM_VoicePreferActivateJudgeStepTwo();
    }
    /* 条件不满足,如果不超过最大重试查询次数延迟后再次查询*/
    else if (NAS_RABM_VoicePreferGetReQryGmmCnt() < VP_REQRY_GMM_MAX_TIMES)
    {
        NAS_RabmStartTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_VOICEPREFER_REQRY_GMM_DELAY);
    }
    else
    {

    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_BASTET)

VOS_VOID NAS_RABM_RcvBastetMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader;
    GMM_RABM_NET_RAT_ENUM_UINT32         enCurrentSysMode;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    switch (pstMsgHeader->ulMsgName)
    {
        case ID_BASTET_RABM_SET_RELEASE_RRC_REQ:
            enCurrentSysMode = NAS_RABM_GetCurrentSysMode();

            /* 如果不在W网络下，则不能释放RRC连接 */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrentSysMode)
            {
                NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_RELEASE_RRC_ENUM);
            }
            break;

        default:
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


