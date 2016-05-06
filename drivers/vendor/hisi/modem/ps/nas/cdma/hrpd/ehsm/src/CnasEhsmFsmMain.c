


/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "CnasEhsmFsmMain.h"
#include "CnasEhsmFsmMainTbl.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmTimerMgmt.h"
#include "PsLogdef.h"
#include "CnasEhsmSndAps.h"
#include "CnasEhsmSndHsd.h"
#include "CnasEhsmSndEsm.h"
#include "CnasEhsmSndInternalMsg.h"
#include "CnasEhsmSndPpp.h"
#include "CnasEhsmSndHsm.h"
#include "CnasEhsmComFunc.h"
#include "CnasEhsmDecode.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_FSM_MAIN_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 CNAS_EHSM_RcvHsdStartReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*Init Context*/
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_EHSM_InitCtx(CNAS_EHSM_INIT_CTX_STARTUP);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    /* send start confirm to HSD */
    CNAS_EHSM_SndHsdStartCnf(EHSM_HSD_START_RESULT_SUCC);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstHsmSessionInd = VOS_NULL_PTR;
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enCurrPsRatType;

    pstHsmSessionInd    = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;
    CNAS_EHSM_SetSessionType(pstHsmSessionInd->enSessionType);

    enCurrPsRatType     = CNAS_CCB_GetCurrPsRatType();

    /* Not LTE->EHRPD, Just Return */
    if ((CNAS_CCB_PS_RATTYPE_1X == enCurrPsRatType)
     || (CNAS_CCB_PS_RATTYPE_HRPD == enCurrPsRatType))
    {
        return VOS_TRUE;
    }

    /* If there is any PDN active, just clear Local PDN and notify ESM module */
    if ((VOS_TRUE == CNAS_EHSM_CheckLtePdnIsActive())
     && (EHSM_HSM_SESSION_TYPE_HRPD == pstHsmSessionInd->enSessionType))
    {
        CNAS_EHSM_SndEsmClearAllNtf();

        CNAS_EHSM_ClearAllLteLocalPdnInfo();

        return VOS_TRUE;
    }

    if (EHSM_HSM_SESSION_TYPE_EHRPD == pstHsmSessionInd->enSessionType)
    {
        /* 存在LTE模的PDN承载时，做HANDOVER ATTACH，否则做INITIAL ATTACH */
        if (VOS_TRUE == CNAS_EHSM_CheckLtePdnIsActive())
        {
            if (1 == CNAS_EHSM_GetLteActivePdnNum())
            {
                if (VOS_TRUE != CNAS_EHSM_GetEhrpdAutoAttachFlag())
                {
                    CNAS_EHSM_ClearLteLocalPdnInfo(CNAS_EHSM_DEFAULT_CID);
                }

                /* 上一步删除的恰好是LTE的默认承载 */
                if (0 == CNAS_EHSM_GetLteActivePdnNum())
                {
                    /* 通知LTE清除L的承载 */
                    CNAS_EHSM_SndEsmClearAllNtf();

                    return VOS_TRUE;
                }
            }

            CNAS_EHSM_SndInternalAttachReq(CNAS_EHSM_ATTACH_REASON_HANDOVER_ATTACH);
        }
        else
        {
            /* 只有自动Attach功能使能，才发送内部消息出来 */
            if (VOS_TRUE == CNAS_EHSM_GetEhrpdAutoAttachFlag())
            {
                CNAS_EHSM_SndInternalAttachReq(CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH);
            }
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmAttachReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Init the Activating Sub FSM */
    CNAS_EHSM_InitFsmL2(CNAS_EHSM_FSM_ACTIVATING);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEsmSyncPdnInfoInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucLteIndex;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstSynPdnInfo = VOS_NULL_PTR;

    pstSynPdnInfo = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU *)pstMsg;

    ucCid = CNAS_EHSM_GetCidFromLteBitCid(pstSynPdnInfo->ulBitCid);

    if (CNAS_EHSM_INVALID_CID != ucCid)
    {
        switch (pstSynPdnInfo->enPdnOption)
        {
            case EHSM_ESM_PDN_OPT_CONNECTED:
                /* if the first lte pdn attach,clear the local lte pdn info */
                if (VOS_TRUE == pstSynPdnInfo->ulAttachFlag)
                {
                    CNAS_EHSM_ClearAllLteLocalPdnInfo();
                    /* 清一下retry apn 的信息 */
                    CNAS_EHSM_InitApnRetryInfo();
                }

                ucLteIndex = CNAS_EHSM_GetLtePdnUnusedIndex();
                if (ucLteIndex < CNAS_EHSM_MAX_PDN_NUM)
                {
                    CNAS_EHSM_SaveLteLocalPdnInfo(ucLteIndex, pstSynPdnInfo);

                    if (VOS_TRUE == pstSynPdnInfo->ulAttachFlag)
                    {
                        CNAS_EHSM_SndHsmLteRegSuccessInd();
                    }
                }

                break;

            case EHSM_ESM_PDN_OPT_MODIFIED:
                ucLteIndex = CNAS_EHSM_GetLtePdnInfoIndexByEpsbId(pstSynPdnInfo->ulEpsbId);
                if (CNAS_EHSM_INVALID_PDN_ID != ucLteIndex)
                {
                    CNAS_EHSM_SaveLteLocalPdnInfo(ucLteIndex, pstSynPdnInfo);
                }
                break;

            case EHSM_ESM_PDN_OPT_DISCONNECTED:
                CNAS_EHSM_ClearLteLocalPdnInfo(ucCid);
                break;

            default:
                CNAS_WARNING_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_RcvEsmSyncPdnInfoInd_Inactive: wrong Pdn Option:", pstSynPdnInfo->enPdnOption);
                break;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvApsPsRatTypeNotify_Inactive
 功能描述  : Process APS Message Notifying EHSM the Rat of PS service changed
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月1日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvApsPsRatTypeNotify_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU   *pstPsRat;
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enCurrPsRatType;

    pstPsRat = (APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU*)pstMsg;
    enCurrPsRatType = CNAS_CCB_GetCurrPsRatType();

    if (CNAS_CCB_PS_RATTYPE_BUTT == enCurrPsRatType)
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_RcvApsPsRatTypeNotify_Inactive: PsRatType is BUTT");
    }

    /* If rat type is NULL, it means no ps service currently.
        If session type is EHRPD, Ue begin to Initial attach*/
    if ((EHSM_HSM_SESSION_TYPE_EHRPD == CNAS_EHSM_GetSessionType())
     && (APS_EHSM_PS_RATTYPE_NULL == pstPsRat->enPsRatType))
    {
        /* 只有自动Attach功能使能，才发送内部消息出来 */
        if (VOS_TRUE == CNAS_EHSM_GetEhrpdAutoAttachFlag())
        {
            CNAS_EHSM_SndInternalAttachReq(CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH);
        }
    }

    if (VOS_TRUE == CNAS_EHSM_IsPsRatTypeChanged(enCurrPsRatType, pstPsRat->enPsRatType))
    {
        CNAS_CCB_SetPrevRatType(enCurrPsRatType);
        CNAS_CCB_SetCurrPsRatType(CNAS_EHSM_MapApsPsRatTypeToCcb(pstPsRat->enPsRatType));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvApsPdnAttachReq_Inactive
 功能描述  : EHSM Inactive状态下收到TAF APS发送的Attach请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvApsPdnAttachReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Init the Activating Sub FSM */
    CNAS_EHSM_InitFsmL2(CNAS_EHSM_FSM_ACTIVATING);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvApsReconnReq_Inactive
 功能描述  : 对冲场景保护
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvApsReconnReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_RECONN_REQ_STRU           *pstReconnReq = VOS_NULL_PTR;

    pstReconnReq = (APS_EHSM_RECONN_REQ_STRU *)pstMsg;

    CNAS_EHSM_SndApsReconnCnf(EHSM_APS_CAUSE_UNKNOWN,
                              pstReconnReq->ucPdnId,
                              pstReconnReq->ucCid);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvApsReconnReq_Inactive
 功能描述  : 对冲场景保护
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvApsPdnDeactivateReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU   *pstDeactReq = VOS_NULL_PTR;

    pstDeactReq = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU *)pstMsg;

    CNAS_EHSM_SndApsPdnDeactivateCnf(pstDeactReq->ucPdnId,
                                     pstDeactReq->ucCid,
                                     EHSM_APS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvEhsmLocalDetachAllReq_Inactive
 功能描述  : 本地去激活的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvEhsmLocalDetachAllReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_SndEsmClearAllNtf();
    CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();
    CNAS_EHSM_ClearAllLteLocalPdnInfo();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvApsLocalDeactiveNtf_Inactive
 功能描述  : 处理APS通知的localDeactive消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月12日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvApsLocalDeactiveNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU *pstLocDeactNtf = VOS_NULL_PTR;

    pstLocDeactNtf = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU *)pstMsg;

    /* 清除EHSM保存的LTE的PDN信息 */
    CNAS_EHSM_ClearLteLocalPdnInfo(pstLocDeactNtf->ucCid);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvHsdPowerOffReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Send power off confirm result */
    CNAS_EHSM_SndHsdPowerOffCnf();

    /* Clear Ehrpd local PDN Info */
    CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();

    /* Clear LTE local PDN info*/
    CNAS_EHSM_ClearAllLteLocalPdnInfo();

    CNAS_EHSM_SndCttfEhrpdDetachInd();

    /* Stop Protect Timer for Power Off */
    if (CNAS_EHSM_TIMER_STATUS_RUNING == CNAS_EHSM_GetTimerStatus(TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS))
    {
        CNAS_EHSM_StopTimer(TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS);
    }

    /* INit the context */
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
    CNAS_EHSM_InitCtx(CNAS_EHSM_INIT_CTX_POWEROFF);
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

    return VOS_TRUE;
}

VOS_UINT32 CNAS_EHSM_RcvEhsmActivatingRsltCnf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU                *pstActivatingCnf    = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                                     *pstEhsmCtx          = VOS_NULL_PTR;
    VOS_UINT32                                              ulLoop;

    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    pstActivatingCnf   = (CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU *)pstMsg;

    /*If activating is success */
    if (CNAS_EHSM_ACTIVATING_RESULT_SUCCESS == pstActivatingCnf->enRslt)
    {
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_ACTIVE);
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_ACTIVE_STA);
    }

    if (VOS_FALSE == pstActivatingCnf->ucIsPermanentFail)
    {
        for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
        {
            if (VOS_TRUE == pstEhsmCtx->astLtePdnBearInfo[ulLoop].ucInUsed)
            {
                CNAS_EHSM_SndPdnSetupReq(ulLoop);
                break;
            }
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsPdnActivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Init the Activating Sub FSM */
    CNAS_EHSM_InitFsmL2(CNAS_EHSM_FSM_ACTIVATING);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_SetAirLinkExistFlag(VOS_FALSE);
    CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_DORMANT_STA);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsPdnDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU   *pstPdnDeactReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;

    pstPdnDeactReq = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstMsg;

    ucPdnId = CNAS_EHSM_GetPdnIdByCid(pstPdnDeactReq->ucCid);

    if (CNAS_EHSM_INVALID_PDN_ID == ucPdnId)
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_RcvApsPdnDeactivateReq_Active: Invalid PDN ID");
    }

    /* 判断当前对应的pdn，是否已经激活 */
    if (VOS_FALSE == CNAS_EHSM_IsPdnActived(ucPdnId))
    {
        CNAS_EHSM_SndApsPdnDeactivateCnf(pstPdnDeactReq->ucPdnId,
                                         pstPdnDeactReq->ucCid,
                                         EHSM_APS_CAUSE_SUCCESS);
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_EHSM_GetEhrpdAutoAttachFlag())
    {
        /* Auto Attach如果打开，需要保留EHRPD下的默认承载 */
        if (1 == CNAS_EHSM_GetLocalActivePdnConnNum())
        {
            CNAS_EHSM_SndApsPdnDeactivateCnf(pstPdnDeactReq->ucPdnId,
                                             pstPdnDeactReq->ucCid,
                                             EHSM_APS_CAUSE_LAST_PDN);
            return VOS_TRUE;
        }
    }

    /* Init the deactivating Sub FSM */
    CNAS_EHSM_InitFsmL2(CNAS_EHSM_FSM_DEACTIVATING);
    return VOS_TRUE;

}


VOS_UINT32 CNAS_EHSM_RcvHsdPowerOffReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Init the Activating Sub FSM */
    CNAS_EHSM_InitFsmL2(CNAS_EHSM_FSM_DEACTIVATING);
    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmActivatingRsltCnf_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU                *pstActivatingCnf    = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                                     *pstEhsmCtx          = VOS_NULL_PTR;
    VOS_UINT32                                              ulLoop;


    pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();

    pstActivatingCnf   = (CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU *)pstMsg;

    /*If activating is success */
    if (VOS_FALSE == pstActivatingCnf->ucIsPermanentFail)
    {
        for (ulLoop = 0; ulLoop < CNAS_EHSM_MAX_PDN_NUM; ulLoop++)
        {
            if (VOS_TRUE == pstEhsmCtx->astLtePdnBearInfo[ulLoop].ucInUsed)
            {
                CNAS_EHSM_SndPdnSetupReq(ulLoop);
                break;
            }
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmDeactivatingRsltCnf_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulPdnConnNum;

    ulPdnConnNum  = CNAS_EHSM_GetLocalActivePdnConnNum();

    /* If there is no PDN connection then move the state to CNAS_EHSM_L1_STA_INACTIVE */
    if (0 == ulPdnConnNum)
    {

        /* Set the current state as inactive */
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);
    }

    return VOS_TRUE;
}




VOS_UINT32 CNAS_EHSM_RcvApsReConnReq_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_RECONN_REQ_STRU           *pstApsReconnReq = VOS_NULL_PTR;

    pstApsReconnReq = (APS_EHSM_RECONN_REQ_STRU *)pstMsg;

    CNAS_EHSM_SndApsReconnCnf(EHSM_APS_CAUSE_EHRPD_SUSPEND,
                              pstApsReconnReq->ucPdnId,
                              pstApsReconnReq->ucCid);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsPdnDeactivateReq_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU   *pstApsDeactReq   = VOS_NULL_PTR;

    pstApsDeactReq      = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU *)pstMsg;

    CNAS_EHSM_SndApsPdnDeactivateCnf(pstApsDeactReq->ucPdnId,
                                     pstApsDeactReq->ucCid,
                                     EHSM_APS_CAUSE_EHRPD_SUSPEND);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsdPowerOffReq_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                  ulIndex;
    CNAS_EHSM_CTX_STRU                         *pstEhsmCtx        = VOS_NULL_PTR;
    VOS_UINT8                                   ucCid;
    VOS_UINT8                                   ucPdnId;

    pstEhsmCtx             = CNAS_EHSM_GetEhsmCtxAddr();
    ulIndex = 0;
    while (ulIndex < CNAS_EHSM_MAX_PDN_NUM)
    {
        if (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[ulIndex].ucInUsed)
        {
            ucPdnId = pstEhsmCtx->astLocalPdnBearInfo[ulIndex].ucPdnId;
            ucCid   = pstEhsmCtx->astLocalPdnBearInfo[ulIndex].ucCid;

            CNAS_EHSM_SndApsPdnDeactivateInd(ucPdnId, ucCid, EHSM_APS_CAUSE_POWER_OFF);
        }
        ulIndex++;
    }
    CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();

    CNAS_EHSM_SndCttfEhrpdDetachInd();

    CNAS_EHSM_SndEsmClearAllNtf();

    CNAS_EHSM_SndHsdPowerOffCnf();

    CNAS_EHSM_ClearCtx(CNAS_EHSM_INIT_CTX_POWEROFF);

    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsPdnActivateReq_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PDN_ACTIVATE_REQ_STRU     *pstPdnActReq;

    pstPdnActReq = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstMsg;

    CNAS_EHSM_SndApsPdnActivateCnf(pstPdnActReq->ucCid, EHSM_APS_CAUSE_EHRPD_SUSPEND);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvApsLocDetachNotify_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Loction detach */
    CNAS_EHSM_SndCttfEhrpdDetachInd();

    CNAS_EHSM_SndEsmClearAllNtf();

    CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();

    CNAS_EHSM_SetSessionType((VOS_UINT32)EHSM_HSM_SESSION_TYPE_NULL);

    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);

    CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsPsRatTypeNty_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU   *pstPsRatNty = VOS_NULL_PTR;
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enCurrPsRatType;

    enCurrPsRatType = CNAS_CCB_GetCurrPsRatType();

    if (CNAS_CCB_PS_RATTYPE_BUTT == enCurrPsRatType)
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_RcvApsPsRatTypeNty_Suspend: PsRatType is BUTT");
    }

    pstPsRatNty = (APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_EHSM_IsPsRatTypeChanged(enCurrPsRatType, pstPsRatNty->enPsRatType))
    {
        CNAS_CCB_SetPrevRatType(enCurrPsRatType);
        CNAS_CCB_SetCurrPsRatType(CNAS_EHSM_MapApsPsRatTypeToCcb(pstPsRatNty->enPsRatType));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvApsLocDeactivateNty_Suspend
 功能描述  : 收到ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月21日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvApsLocDeactivateNty_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU    *pstLocDeact;
    VOS_UINT8                               ucPdnId;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU     *pstPdnInfo = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                     *pstEhsmCtx = VOS_NULL_PTR;

    pstLocDeact = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU*)pstMsg;

    ucPdnId = CNAS_EHSM_GetPdnIdByCid(pstLocDeact->ucCid);

    /* 当前如果有有效的PDN，则清除该PDN */
    if (CNAS_EHSM_INVALID_PDN_ID != ucPdnId)
    {
        /* 判断是否是最后一个承载 */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            /* Loction detach */
            CNAS_EHSM_SndCttfEhrpdDetachInd();

            CNAS_EHSM_SndEsmClearAllNtf();

            CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();

            CNAS_EHSM_SetSessionType((VOS_UINT32)EHSM_HSM_SESSION_TYPE_NULL);

            CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);

            CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);
        }
        else
        {
            pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();
            pstPdnInfo = &(pstEhsmCtx->astLocalPdnBearInfo[ucPdnId]);

            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(ucPdnId);

            CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_FALSE, EHSM_ESM_PDN_OPT_DISCONNECTED);

            CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);
        }
    }

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvApsLocDetachNotify_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Loction detach */
    CNAS_EHSM_SndCttfEhrpdDetachInd();

    CNAS_EHSM_SndEsmClearAllNtf();

    CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();

    CNAS_EHSM_ClearAllLteLocalPdnInfo();

    CNAS_EHSM_SetSessionType((VOS_UINT32)EHSM_HSM_SESSION_TYPE_NULL);

    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);

    CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU  *pstPdnDiscInd = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucPdnId;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo = VOS_NULL_PTR;

    pstPdnDiscInd                       = (CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU *)pstMsg;
    pstEhsmCtx                          = CNAS_EHSM_GetEhsmCtxAddr();
    ucPdnId                             = pstPdnDiscInd->ucPdnId;
    ucCid                               = pstEhsmCtx->astLocalPdnBearInfo[ucPdnId].ucCid;
    pstPdnInfo                          = &(pstEhsmCtx->astLocalPdnBearInfo[ucPdnId]);

    if (VOS_TRUE != CNAS_EHSM_IsPdnActived(ucPdnId))
    {
        return VOS_TRUE;
    }

    /* Send the PDN deactivate Indication to APS */
    CNAS_EHSM_SndApsPdnDeactivateInd(ucPdnId, ucCid, EHSM_APS_CAUSE_NW_DISC_IND);

    /* Send The Sync PDN info to ESM */
    CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_FALSE, EHSM_ESM_PDN_OPT_DISCONNECTED);

    CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdDetachInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulIndex;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucPdnId;

    pstEhsmCtx                          = CNAS_EHSM_GetEhsmCtxAddr();
    ucPdnId                             = 0;
    ucCid                               = 0;

    /*clear local used pdn info*/
    for (ulIndex = 0; ulIndex < CNAS_EHSM_MAX_PDN_NUM; ulIndex++)
    {
        if (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[ulIndex].ucInUsed)
        {
            ucPdnId = pstEhsmCtx->astLocalPdnBearInfo[ulIndex].ucPdnId;
            ucCid = pstEhsmCtx->astLocalPdnBearInfo[ulIndex].ucCid;
            CNAS_EHSM_SndApsPdnDeactivateInd(ucPdnId, ucCid, EHSM_APS_CAUSE_PPP_DETACH);
        }

    }
    CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();
    CNAS_EHSM_SndEsmClearAllNtf();

    /* Set the current state as inactive */
    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);
    CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);

    /* 只有自动Attach功能使能，才发送内部消息出来 */
    if (VOS_TRUE == CNAS_EHSM_GetEhrpdAutoAttachFlag())
    {
        /* 重新做INITTIAL ATTACH */
        CNAS_EHSM_SndInternalAttachReq(CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH);
    }

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstHsmSessionInd = VOS_NULL_PTR;
    VOS_UINT32                          i;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx   = VOS_NULL_PTR;

    pstEhsmCtx          = CNAS_EHSM_GetEhsmCtxAddr();
    pstHsmSessionInd    = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    CNAS_EHSM_SetSessionType(pstHsmSessionInd->enSessionType);

    if (EHSM_HSM_SESSION_TYPE_HRPD == pstHsmSessionInd->enSessionType)
    {
        /* send local pdn disconnect ind to PPP */
        CNAS_EHSM_SndCttfEhrpdDetachInd();

        for (i = 0; i < CNAS_EHSM_MAX_PDN_NUM; i++)
        {
            if (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[i].ucInUsed)
            {
                /* NOtify APS */
                CNAS_EHSM_SndApsPdnDeactivateInd(pstEhsmCtx->astLocalPdnBearInfo[i].ucPdnId,
                                                 pstEhsmCtx->astLocalPdnBearInfo[i].ucCid,
                                                 EHSM_APS_CAUSE_NOT_SUPPORT_EHRPD);
            }
        }

        /* Clear PDN info */
        CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();

        /* Notify ESM */
        CNAS_EHSM_SndEsmClearAllNtf();

        /* Set the current state as inactive */
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);

    }
    else if (EHSM_HSM_SESSION_TYPE_EHRPD == pstHsmSessionInd->enSessionType)
    {
        /* Change the state to Active */
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_ACTIVE);

        if (VOS_TRUE == CNAS_EHSM_GetAirLinkExistFlag())
        {
            CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_ACTIVE_STA);
        }
        else
        {
            CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_DORMANT_STA);
        }
    }
    else
    {

    }

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvEsmSyncPdnInfoInd_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucLteIndex;

    ucLteIndex = CNAS_EHSM_GetLtePdnUnusedIndex();
    if (ucLteIndex >= CNAS_EHSM_MAX_PDN_NUM)
    {
        return VOS_TRUE;
    }

    pstPdnInfo = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU *)pstMsg;

    /* if LTE handover attach success, the ulAttachFlag should be TRUE */
    if (VOS_TRUE != pstPdnInfo->ulAttachFlag)
    {
        return VOS_TRUE;
    }

    /* Notify Hsm Lte register Success */
    CNAS_EHSM_SndHsmLteRegSuccessInd();

    /* Clear local PDN info */
    CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();

    /*save the sync pdn info in index */
    CNAS_EHSM_SaveLteLocalPdnInfo(ucLteIndex, (ESM_EHSM_SYNC_PDN_INFO_IND_STRU *)pstMsg);

    /* Set the current state as inactive */
    CNAS_EHSM_SetSessionType((VOS_UINT32)EHSM_HSM_SESSION_TYPE_NULL);
    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);
    CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvEhsmPdnSetupReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Init the Activating Sub FSM */
    CNAS_EHSM_InitFsmL2(CNAS_EHSM_FSM_ACTIVATING);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsReConnReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_RECONN_REQ_STRU           *pstApsReconnReq = VOS_NULL_PTR;

    pstApsReconnReq = (APS_EHSM_RECONN_REQ_STRU *)pstMsg;
    if (VOS_TRUE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        CNAS_EHSM_SndApsReconnCnf(EHSM_APS_CAUSE_SUCCESS,pstApsReconnReq->ucPdnId, pstApsReconnReq->ucCid);
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_EHSM_IsPdnActived(pstApsReconnReq->ucPdnId))
    {
        /* Init activating Sub FSM */
        CNAS_EHSM_InitFsmL2(CNAS_EHSM_FSM_ACTIVATING);
    }
    else
    {
        CNAS_EHSM_SndApsReconnCnf(EHSM_APS_CAUSE_INVALID_PDN_ID, pstApsReconnReq->ucPdnId, pstApsReconnReq->ucCid);
    }
    /* To Do Need to decide error value in failure case */

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsPsRatTypeNty_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU   *pstPsRatNty = VOS_NULL_PTR;
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enCurrPsRatType;

    enCurrPsRatType = CNAS_CCB_GetCurrPsRatType();

    if (CNAS_CCB_PS_RATTYPE_BUTT == enCurrPsRatType)
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_RcvApsPsRatTypeNty_Active: PsRatType is BUTT");
    }

    pstPsRatNty = (APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_EHSM_IsPsRatTypeChanged(enCurrPsRatType, pstPsRatNty->enPsRatType))
    {
        CNAS_CCB_SetPrevRatType(enCurrPsRatType);
        CNAS_CCB_SetCurrPsRatType(CNAS_EHSM_MapApsPsRatTypeToCcb(pstPsRatNty->enPsRatType));
    }

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsmSuspendInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_SUSPEND);
    CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_SUSPEND_STA);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsLocDeactivateNty_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU    *pstLocDeact;
    VOS_UINT8                               ucPdnId;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU     *pstPdnInfo = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                     *pstEhsmCtx = VOS_NULL_PTR;

    pstLocDeact = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU*)pstMsg;

    ucPdnId = CNAS_EHSM_GetPdnIdByCid(pstLocDeact->ucCid);

    /* 当前如果有有效的PDN，则清除该PDN */
    if (CNAS_EHSM_INVALID_PDN_ID != ucPdnId)
    {
        /* 判断是否是最后一个承载 */
        if (1 == CNAS_EHSM_GetLocalAllocatedPdnIdNum())
        {
            /* Loction detach */
            CNAS_EHSM_SndCttfEhrpdDetachInd();

            CNAS_EHSM_SndEsmClearAllNtf();

            CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();

            CNAS_EHSM_SetSessionType((VOS_UINT32)EHSM_HSM_SESSION_TYPE_NULL);

            CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);

            CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);
        }
        else
        {
            pstEhsmCtx = CNAS_EHSM_GetEhsmCtxAddr();
            pstPdnInfo = &(pstEhsmCtx->astLocalPdnBearInfo[ucPdnId]);

            CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(ucPdnId);

            CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_FALSE, EHSM_ESM_PDN_OPT_DISCONNECTED);

            CNAS_EHSM_ClearEhrpdLocalPdnInfo(ucPdnId);
        }


    }

    return VOS_TRUE;
}



VOS_UINT32 CNAS_EHSM_RcvEhsmLocalDetachAllReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU   *pstLocalDetach;
    VOS_UINT32                                  i;

    pstLocalDetach = (CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU*)pstMsg;

    for (i = 0; i < CNAS_EHSM_MAX_PDN_NUM; i++)
    {
        if (VOS_TRUE  == CNAS_EHSM_IsPdnActived((VOS_UINT8)i))
        {
            CNAS_EHSM_SndApsPdnDeactivateInd((VOS_UINT8)i,
                                             CNAS_EHSM_GetCidByPdnId((VOS_UINT8)i),
                                             pstLocalDetach->enCause);
        }
    }

    CNAS_EHSM_SndCttfEhrpdDetachInd();
    CNAS_EHSM_SndEsmClearAllNtf();
    CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();
    CNAS_EHSM_ClearAllLteLocalPdnInfo();
    CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);
    CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvApsDiscNotify_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Init the deactivating Sub FSM */
    CNAS_EHSM_InitFsmL2(CNAS_EHSM_FSM_DEACTIVATING);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstHsmSessionInd = VOS_NULL_PTR;
    VOS_UINT32                          i;
    CNAS_EHSM_CTX_STRU                 *pstEhsmCtx   = VOS_NULL_PTR;

    pstEhsmCtx          = CNAS_EHSM_GetEhsmCtxAddr();
    pstHsmSessionInd    = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    CNAS_EHSM_SetSessionType(pstHsmSessionInd->enSessionType);

    if (EHSM_HSM_SESSION_TYPE_HRPD == pstHsmSessionInd->enSessionType)
    {
        for (i = 0; i < CNAS_EHSM_MAX_PDN_NUM; i++)
        {
            if (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[i].ucInUsed)
            {
                /* Notify APS */
                CNAS_EHSM_SndApsPdnDeactivateInd(pstEhsmCtx->astLocalPdnBearInfo[i].ucPdnId,
                                                 pstEhsmCtx->astLocalPdnBearInfo[i].ucCid,
                                                 EHSM_APS_CAUSE_NOT_SUPPORT_EHRPD);
            }
        }

        CNAS_EHSM_SndCttfEhrpdDetachInd();
        CNAS_EHSM_SndEsmClearAllNtf();
        CNAS_EHSM_ClearAllEhrpdLocalPdnInfo();
        CNAS_EHSM_ClearAllLteLocalPdnInfo();
        CNAS_EHSM_SetCurrFsmState(CNAS_EHSM_L1_STA_INACTIVE);
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_INACTIVE_STA);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvPppModifyInd_Active
 功能描述  : ehsm 在active状态下收到ppp发送的ip地址变化的消息处理
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvPppModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_MODIFY_IND_STRU    *pstModifyInd;
    EHSM_APS_PDN_CHANGE_INFO_STRU       stPdnChgInfo;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstEhrpdPdnAddr = VOS_NULL_PTR;
    CNAS_EHSM_PDN_ADDR_STRU             stPdnAddr;

    /* 初始化, 获取消息内容 */
    pstModifyInd    = (CTTF_CNAS_EHRPD_MODIFY_IND_STRU*)pstMsg;
    pstEhrpdPdnAddr = CNAS_EHSM_GetEhrpdLocPdnAddr(pstModifyInd->ucPdnId);
    NAS_MEM_SET_S(&stPdnChgInfo, sizeof(EHSM_APS_PDN_CHANGE_INFO_STRU), 0X00, sizeof(EHSM_APS_PDN_CHANGE_INFO_STRU));
    NAS_MEM_SET_S(&stPdnAddr, sizeof(CNAS_EHSM_PDN_ADDR_STRU), 0X00, sizeof(CNAS_EHSM_PDN_ADDR_STRU));

    if (CNAS_EHSM_CAUSE_SUCCESS != CNAS_EHSM_DecodeNwPDNValue(0,
                                                             (VOS_UINT8 *)&(pstModifyInd->stPdnAddress),
                                                             &stPdnAddr))
    {
       CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_RcvPppModifyInd_Active:Wrong Msg Entry");
       return VOS_TRUE;
    }

    stPdnChgInfo.stPdnAddr.enPdnType        = stPdnAddr.enPdnType;
    pstEhrpdPdnAddr->enPdnType              = stPdnAddr.enPdnType;
    pstEhrpdPdnAddr->stPdnAddr.enPdnType    = stPdnAddr.enPdnType;

    NAS_MEM_CPY_S(stPdnChgInfo.stPdnAddr.aucIpv4Addr, EHSM_APS_IPV4_ADDR_LEN, stPdnAddr.aucIpv4Addr, CNAS_CTTF_EHRPD_IPV4_ADDR_LEN);
    NAS_MEM_CPY_S(pstEhrpdPdnAddr->stPdnAddr.aucIpv4Addr, CNAS_EHSM_IPV4_ADDR_LEN, stPdnAddr.aucIpv4Addr, CNAS_CTTF_EHRPD_IPV4_ADDR_LEN);


    NAS_MEM_CPY_S(stPdnChgInfo.stPdnAddr.aucIpv6Addr, EHSM_APS_IPV6_ADDR_LEN, stPdnAddr.aucIpv6Addr, CNAS_CTTF_EHRPD_IPV6_ADDR_LEN);
    NAS_MEM_CPY_S(pstEhrpdPdnAddr->stPdnAddr.aucIpv6Addr, CNAS_EHSM_IPV6_ADDR_LEN, stPdnAddr.aucIpv6Addr, CNAS_CTTF_EHRPD_IPV6_ADDR_LEN);

    stPdnChgInfo.usMtu        = pstModifyInd->usMtu;
    pstEhrpdPdnAddr->usMtu      = pstModifyInd->usMtu;

    CNAS_EHSM_SndApsPdnChgInd(&stPdnChgInfo, pstModifyInd->ucPdnId);

    return VOS_TRUE;
}



#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



