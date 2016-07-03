

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasEhsmMsgPrioCompare.h"
#include  "NasFsm.h"
#include  "CnasEhsmSndInternalMsg.h"
#include  "CnasCcb.h"
#include  "ehsm_hsd_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_CNAS_EHSM_MSG_PRIO_COMPARE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

CNAS_EHSM_MSG_COMPARE_STRU g_astEhsmMsgPrioCompareWithActivatingTbl[] =
{
    /* Activating过程中收到HSD的关机请求的消息优先级比较 */
    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_OFF_REQ),
                               CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating),

    /* Activating过程中收到HSD的关机请求的消息优先级比较 */
    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SUSPEND_IND),
                               CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(MSPS_PID_PPPC, ID_CTTF_CNAS_EHRPD_DETACH_IND),
                               CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ),
                               CNAS_EHSM_CompareTafPdnReconnReqWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnActivateReqWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DETACH_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SESSION_INFO_IND),
                               CNAS_EHSM_CompareHsmSessionInfoIndPrioWithActivating)/* ,

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_SAVE_REQ),
                               CNAS_EHSM_CompareHsdPowerSaveReqPrioWithActivating)*/
};


CNAS_EHSM_MSG_COMPARE_STRU g_astEhsmMsgPrioCompareWithDeactivatingTbl[] =
{
    /* Deactivating过程中收到HSD的关机请求的消息优先级比较 */
    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_OFF_REQ),
                               CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SUSPEND_IND),
                               CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(MSPS_PID_PPPC, ID_CTTF_CNAS_EHRPD_DETACH_IND),
                               CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ),
                               CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DETACH_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SESSION_INFO_IND),
                               CNAS_EHSM_CompareHsmSessionInfoIndPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_DISC_NOTIFY),
                               CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating)/* ,


    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_SAVE_REQ),
                               CNAS_EHSM_CompareHsdPowerSaveReqPrioWithDeactivating)*/

};




CNAS_EHSM_FSM_MSG_COMPARE_STRU g_astEhsmMsgCompareTbl[] =
{
    /* ACTIVATING 状态机比较函数表*/
    CNAS_EHSM_FSM_COMPARE_TBL_ITEM(CNAS_EHSM_FSM_ACTIVATING,
                                 g_astEhsmMsgPrioCompareWithActivatingTbl),

    /* DEACTIVATING 状态机比较函数表*/
    CNAS_EHSM_FSM_COMPARE_TBL_ITEM(CNAS_EHSM_FSM_DEACTIVATING,
                                 g_astEhsmMsgPrioCompareWithDeactivatingTbl),
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS, TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS_LEN);

    CNAS_EHSM_ClearAllCacheMsg();

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}



VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    REL_TIMER_MSG                          *pstTimerMsg;
    VOS_UINT32                              ulCacheMsgEventType;

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* 清除之前缓存的不需要处理的消息 */
    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if ((CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ)         == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ)   == ulCacheMsgEventType))
        {
            CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
        }
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT8                           ucCid;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU   *pstPdnDeactReq;

    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    pstPdnDeactReq  = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstMsg;
    ucCid           = CNAS_EHSM_GetCid_Activating();

    if (ucCid == pstPdnDeactReq->ucCid)
    {
        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
    }


    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 CNAS_EHSM_CompareTafPdnReconnReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}



VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    APS_EHSM_PDN_ACTIVATE_REQ_STRU         *pstPdnAct;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU       *pstPdnDeact;
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU    *pstLocPdnDeact;
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    REL_TIMER_MSG                          *pstTimerMsg;
    VOS_UINT32                              ulCacheMsgEventType;

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    pstLocPdnDeact  = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU*)pstMsg;
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* 查看缓存中有没有相同CID的操作，有的话，清除缓存 */
    for  (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        pstCacheMsgHdr          = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnAct = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnAct->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
                return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD;
            }
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnDeact = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnDeact->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
            }
        }
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}




VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS, TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS_LEN);

    CNAS_EHSM_ClearAllCacheMsg();

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}



VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    REL_TIMER_MSG                          *pstTimerMsg;
    VOS_UINT32                              ulCacheMsgEventType;

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* 清除之前缓存的不需要处理的消息 */
    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if ((CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ)         == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ)   == ulCacheMsgEventType))
        {
            CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
        }
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}



VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    APS_EHSM_PDN_ACTIVATE_REQ_STRU         *pstPdnAct;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU       *pstPdnDeact;
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU    *pstLocPdnDeact;
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    VOS_UINT32                              ulCacheMsgEventType;
    REL_TIMER_MSG                          *pstTimerMsg;

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    pstLocPdnDeact  = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU*)pstMsg;
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* 查看缓存中有没有相同CID的操作，有的话，清除缓存 */
    for  (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        pstCacheMsgHdr          = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnAct = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnAct->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
                return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD;
            }
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnDeact = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnDeact->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
            }
        }
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstSessionInfo = VOS_NULL_PTR;

    pstSessionInfo = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    if (EHSM_HSM_SESSION_TYPE_EHRPD != pstSessionInfo->enSessionType)
    {
        *penAbortType = CNAS_EHSM_ABORT_BUTT;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
    else
    {
        *penAbortType = CNAS_EHSM_ABORT_FSM_IMMEDIATELY;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }
}


VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstSessionInfo = VOS_NULL_PTR;

    pstSessionInfo = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    if (EHSM_HSM_SESSION_TYPE_EHRPD != pstSessionInfo->enSessionType)
    {
        *penAbortType   = CNAS_EHSM_ABORT_BUTT;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
    else
    {
        *penAbortType = CNAS_EHSM_ABORT_FSM_IMMEDIATELY;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }
}


VOS_UINT32 CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}



CNAS_EHSM_MSG_COMPARE_FUNC  CNAS_EHSM_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enFsmId
)
{
    CNAS_EHSM_FSM_MSG_COMPARE_STRU     *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astEhsmMsgCompareTbl)/sizeof(CNAS_EHSM_FSM_MSG_COMPARE_STRU);

    for ( i = 0 ; i < ulTblSize ; i++ )
    {
        if ( enFsmId == g_astEhsmMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astEhsmMsgCompareTbl[i];
            break;
        }
    }

    /* 未能找到该状态机的比较函数表,直接返回空指针 */
    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        /* 查找不同事件的比较函数 */
        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    /* 未找到处理函数直接返回空指针 */
    return VOS_NULL_PTR;
}




CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 CNAS_EHSM_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    CNAS_EHSM_MSG_COMPARE_FUNC                      pfCompareFunc;
    CNAS_EHSM_FSM_ID_ENUM_UINT32                    enCurrFsmId;
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32     enRslt;

    /*  获取当前状态机的ID */
    enCurrFsmId         = CNAS_EHSM_GetCurrFsmId();

    if (CNAS_EHSM_FSM_BUTT <= enCurrFsmId)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "ERROR:FsmId Error");
    }

    /*  获取比较函数 CNAS_EHSM_FindMsgPrioCompareFun() */
    pfCompareFunc       = CNAS_EHSM_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    /* 未找到处理函数,则默认消息丢弃 */
    if ( VOS_NULL_PTR == pfCompareFunc )
    {
        *penAbortType = CNAS_EHSM_ABORT_BUTT;
        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* 调用比较函数,返回优先级和打断类型 */
    enRslt = pfCompareFunc(ulEventType, pstMsg, penAbortType);

    return enRslt;

}


#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

