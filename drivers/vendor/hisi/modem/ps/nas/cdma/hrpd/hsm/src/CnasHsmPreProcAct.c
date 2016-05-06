


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "CnasHsmCtx.h"
#include  "PsCommonDef.h"
#include  "CnasHsmPreProcAct.h"
#include  "CnasHsmPreProcTbl.h"
#include  "CnasHsmFsmTbl.h"
#include  "NasFsm.h"
#include  "CnasHsmSndHsd.h"
#include  "CnasHsmCtx.h"
#include  "CnasHsmTimer.h"
#include  "CnasHsmSndAps.h"
#include  "CnasHsmComFunc.h"
#include  "CnasHsmSndAs.h"
#include  "hsm_aps_pif.h"
#include  "CnasHsmSndTtf.h"
#include  "CnasHsmEncode.h"
#include  "CnasHsmDecode.h"
#include  "nas_cttf_hrpd_rsnp_pif.h"
#include  "CnasHsmSndHlu.h"
#include  "CnasMntn.h"
#include  "CnasHsmMntn.h"
#include  "CnasHsmSndInternalMsg.h"
#include  "PsRrmInterface.h"
#include  "CnasHsmSndEhsm.h"
#include  "CnasHsmFsmSessionAct.h"
#include  "CnasHsmKeepAlive.h"
#include  "CnasHsmCtx.h"
#include  "CnasTimerMgmt.h"

#include  "CnasHsmSndEhsm.h"
#include  "CnasHsmFsmMain.h"

#include  "CnasHsmProcUsim.h"

#include "CnasHsmFsmUatiRequest.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_PREPROC_ACT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 Type Define
*****************************************************************************/

/*****************************************************************************
  3 The Global Variable Define
*****************************************************************************/

/*****************************************************************************
  4 The Function Define
*****************************************************************************/

/*****************************************************************************
Function Name   :   CNAS_HSM_ConvertCasStatusToHsm_PreProc
Description     :   Covert Cas status to local
Input parameters:   CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16 enPreHrpdOrigCasStatus  ---保存的上一次原始的cas状态
                    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16 enCurHrpdCasStatus      ---现在上报的cas的状态

Outout parameters:  None
Return Value    :   CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16;

Modify History  :
1)  Date           : 2015-10-28
    Author         : m00312079
    Modify content : DTS2015102803041 Create
2)  Date           : 2015-12-28
    Author         : y00307564
    Modify content : DTS2015111903421 Create
*****************************************************************************/
CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16 CNAS_HSM_ConvertCasStatusToHsm_PreProc(
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enPreHrpdOrigCasStatus,
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enCurHrpdCasStatus
)
{
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enCovertRlst;

    enCovertRlst = CNAS_HSM_HRPD_CAS_STATUS_ENUM_BUTT;

    /********************************************************************************************************
        1、由于CAS上报给CNAS的IDLE态时并没有解完系统消息(包含INIT->IDLE)，不能发建链和信令，
        所以CNAS需要在收到CAS上报的OHM消息后才能发送建链和信令，所以此处如果CAS上报的状态为CAS_CNAS_HRPD_CAS_STATUS_ENUM_IDLE态，
        CNAS将本地存储的CAS状态设置为CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT，收到OHM消息后再将本地的CAS的状态设置为CNAS_HSM_HRPD_CAS_STATUS_ENUM_IDLE，
        此时CNAS才可发建链和信令。
        2、conn->idle，此时hsm认为其实此时cas的状态为idle，可以发送空口消息，将cas状态转换为idle，cttf同时需要有保护机制，若是idle态，需收到ovhd后，
        才能发送空口消息
    *********************************************************************************************************/

    switch (enCurHrpdCasStatus)
    {
        case CAS_CNAS_HRPD_CAS_STATUS_ENUM_NONE:
        case CAS_CNAS_HRPD_CAS_STATUS_ENUM_INIT:
            enCovertRlst = CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT;
            break;

        case CAS_CNAS_HRPD_CAS_STATUS_ENUM_IDLE:
            if (CAS_CNAS_HRPD_CAS_STATUS_ENUM_CONN == enPreHrpdOrigCasStatus)
            {
                enCovertRlst = CNAS_HSM_HRPD_CAS_STATUS_ENUM_IDLE;
            }
            else
            {
                enCovertRlst = CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT;
            }
            break;

        case CAS_CNAS_HRPD_CAS_STATUS_ENUM_CONN:
            enCovertRlst = CNAS_HSM_HRPD_CAS_STATUS_ENUM_CONN;
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_CovertCasStatusToHsm_PreProc: unkonwn cas status");
            break;
    }

    return enCovertRlst;
}


HSM_HSD_HRPD_CAS_STATUS_ENUM_UINT16 CNAS_HSM_ConvertCasStatusToHsd_PreProc(
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enCasStatus)
{
    HSM_HSD_HRPD_CAS_STATUS_ENUM_UINT16                     enCovertRlst;

    enCovertRlst = HSM_HSD_HRPD_CAS_STATUS_ENUM_BUTT;

    switch (enCasStatus)
    {
        case CAS_CNAS_HRPD_CAS_STATUS_ENUM_NONE:
            enCovertRlst = HSM_HSD_HRPD_CAS_STATUS_NONE;
            break;

        case CAS_CNAS_HRPD_CAS_STATUS_ENUM_INIT:
            enCovertRlst = HSM_HSD_HRPD_CAS_STATUS_INIT;
            break;

        case CAS_CNAS_HRPD_CAS_STATUS_ENUM_IDLE:
            enCovertRlst = HSM_HSD_HRPD_CAS_STATUS_IDLE;
            break;

        case CAS_CNAS_HRPD_CAS_STATUS_ENUM_CONN:
            enCovertRlst = HSM_HSD_HRPD_CAS_STATUS_CONN;
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_CovertCasStatusToHsd_PreProc: unkonwn cas status");
            break;
    }

    return enCovertRlst;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvCasHrpdCasStatusInd_PreProc
Description     :   Process the Cas status
Input parameters:   VOS_UINT32                          ulEventType,
                    struct MsgCB                       *pstMsg
Outout parameters:  None
Return Value    :   VOS_UINT32;

Modify History  :
1)  Date           : 2015-02-04
    Author         : m00312079
    Modify content : Create

2)  Date           : 2015-10-28
    Author         : m00312079
    Modify content : DTS2015102803041，CAS上报的状态如果为CAS_CNAS_HRPD_CAS_STATUS_ENUM_IDLE(包含INIT->IDLE和CONN->IDLE),
                     CNAS不能发建链和信令，只有等到OHM消息后才可发建链和信令。
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvCasHrpdCasStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_CAS_STATUS_IND_STRU                      *pstHrpdCasStatusInd;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enHrpdConvertedCasStatus;
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enPreHrpdOrigCasStatus;
    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;

    pstHrpdCasStatusInd = (CAS_CNAS_HRPD_CAS_STATUS_IND_STRU*)pstMsg;

    if (CAS_CNAS_HRPD_CAS_STATUS_ENUM_INIT == pstHrpdCasStatusInd->enCasStatus)
    {
        /* 丢网后，如果此时缓存中有残留的系统消息则清除掉，因为此时的系统消息已经过时，如果由过时的系统消息触发流程，可能会出错 */
        ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSD, (VOS_UINT16)ID_HSD_HSM_OVERHEAD_MSG_IND);

        ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

        if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
        {
            CNAS_HSM_ClearCacheMsgByIndex(ucIndex);
        }
    }

    enPreHrpdOrigCasStatus = CNAS_HSM_GetHrpdOriginalCasStatus();

    CNAS_HSM_SaveHrpdOriginalCasStatus(pstHrpdCasStatusInd->enCasStatus);

    enHrpdConvertedCasStatus = CNAS_HSM_ConvertCasStatusToHsm_PreProc(enPreHrpdOrigCasStatus,
                                                                      pstHrpdCasStatusInd->enCasStatus);

    CNAS_HSM_SaveHrpdConvertedCasStatus(enHrpdConvertedCasStatus);

    CNAS_HSM_SndHsdHrpdCasStatusInd(CNAS_HSM_ConvertCasStatusToHsd_PreProc(pstHrpdCasStatusInd->enCasStatus));

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdSessionNegStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvCasHrpdSessionNegRsltInd_PreProc
Description     :   Process ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND
                    如果CAS主动发的协商结果中的结果为失败，先发内部消息ID_CNAS_HSM_HSM_SESSION_CLOSE_IND，
                    给网络发SessionClose。然后处理内部消息ID_CNAS_HSM_HSM_SESSION_CLOSE_IND。
                    如果在open vacant状态收到ID_CNAS_HSM_HSM_SESSION_CLOSE_IND，直接处理。
                    如果在非open vacant状态收到ID_CNAS_HSM_HSM_SESSION_CLOSE_IND消息，先缓存，
                    然后退状态机开始deactive流程，deactive流程完成之后，处理缓存的
                    ID_CNAS_HSM_HSM_SESSION_CLOSE_IND消息。
Input parameters:   VOS_UINT32                          ulEventType,
                    struct MsgCB                       *pstMsg
Outout parameters:  None
Return Value    :   VOS_UINT32;

Modify History  :
1)  Date           : 2015-06-10
    Author         : y00174758
    Modify content : Create
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvCasHrpdSessionNegRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND_STRU                *pstNegRsltInd;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM_UINT8       enCloseReasonSendAn;
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enCurrSessionRelType;
    CNAS_HSM_SESSION_CLOSE_MSG_STRU                         stSessionClose;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubState;
    CNAS_HSM_HSM_SESSION_NEG_RSLT_INFO                      stSessionNegRsltInfo;

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_FALSE);

    enSubState = CNAS_HSM_GetCurrSubState();

    /* 在deactive流程中收到该消息，忽略 */
    if ((CNAS_HSM_SS_SESSION_DEACT_WAIT_SESSION_CLOSE_SNP_DATA_CNF        == enSubState)
     || (CNAS_HSM_SS_SESSION_DEACT_WAIT_CONN_CLOSE_IND                    == enSubState)
     || (CNAS_HSM_SS_SESSION_DEACT_WAIT_SCP_DEACTIVE_CNF                  == enSubState))
    {
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    pstNegRsltInd = (CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND_STRU *)pstMsg;

    if (CAS_CNAS_HRPD_SCP_NEG_RSLT_SUCCESS == pstNegRsltInd->enResult)
    {
        enCurrSessionRelType = CNAS_HSM_ConvertCasSessionRelTypeToHsmSessionRelType(
                                                    pstNegRsltInd->enSessionReleaseType);

        CNAS_HSM_SetCurrSessionRelType(enCurrSessionRelType);

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SUCCESS,
                                           VOS_TRUE,
                                           enCurrSessionRelType);

    }
    else
    {
        /* 如果是在连接子状态机中，在预处理发送SessionClose到网络，否则在Deactive流程中发SessionClose到网络 */
        if ((CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND  == enSubState)
         || (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND == enSubState))
        {
            /* 将ID_CNAS_HSM_HSM_SESSION_CLOSE_IND消息的场景设置成IN_CONN_MNMT
              * 处理ID_CNAS_HSM_HSM_SESSION_CLOSE_IND消息时，将deactive raeson原因值设置为:
              * CNAS_HSM_SESSION_DEACT_REASON_INTERNAL_SESSION_CLOSE_IN_CONN_MNMT，
              * 在deactive流程中通过该原因值判断是否已经发送过SessionClose到网络
              */

            /* Convert SCP reason to HSM reason */
            enSessionDeactReason = CNAS_HSM_ConvertScpActiveFailReasonToSessionDeactReason(
                                                                        pstNegRsltInd->enResult);

            CNAS_HSM_GetCloseReasonSendAnByDeactReason(enSessionDeactReason,
                                                       &enCloseReasonSendAn);

            if (CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_BUTT != enCloseReasonSendAn)
            {
                CNAS_HSM_SndInternalSessionCloseInd(
                                    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_IN_CONN_MNMT_SENT_SESSION_CLOSE,
                                    VOS_NULL_PTR);

                NAS_MEM_SET_S(&stSessionClose, sizeof(stSessionClose), 0x00, sizeof(CNAS_HSM_SESSION_CLOSE_MSG_STRU));

                stSessionClose.enCloseReason = enCloseReasonSendAn;

                if (PS_TRUE == pstNegRsltInd->enProtocolTypeVaildFlag)
                {
                    stSessionClose.usType    = pstNegRsltInd->usProtocolType;
                    stSessionClose.usSubType = pstNegRsltInd->usProtocolSubType;
                }

                CNAS_HSM_SndCasHrpdSessionBeginNtf(CNAS_CAS_HRPD_SESSION_TYPE_SESSION_CLOSE);

                CNAS_HSM_SndSessionCloseMsg(&stSessionClose);

                CNAS_HSM_StartTimer(TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF,
                                    TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);
            }
            else
            {
                NAS_MEM_SET_S(&stSessionNegRsltInfo, sizeof(stSessionNegRsltInfo), 0, sizeof(CNAS_HSM_HSM_SESSION_NEG_RSLT_INFO));

                stSessionNegRsltInfo.enResult                = pstNegRsltInd->enResult;
                stSessionNegRsltInfo.enProtocolTypeVaildFlag = pstNegRsltInd->enProtocolTypeVaildFlag;
                stSessionNegRsltInfo.usProtocolType          = pstNegRsltInd->usProtocolType;
                stSessionNegRsltInfo.usProtocolSubType       = pstNegRsltInd->usProtocolSubType;

                CNAS_HSM_SndInternalSessionCloseInd(
                                        CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_RCV_CAS_NEG_RSLD_IND,
                                        &stSessionNegRsltInfo);
            }
        }
        else
        {
            NAS_MEM_SET_S(&stSessionNegRsltInfo, sizeof(stSessionNegRsltInfo), 0, sizeof(CNAS_HSM_HSM_SESSION_NEG_RSLT_INFO));

            stSessionNegRsltInfo.enResult                = pstNegRsltInd->enResult;
            stSessionNegRsltInfo.enProtocolTypeVaildFlag = pstNegRsltInd->enProtocolTypeVaildFlag;
            stSessionNegRsltInfo.usProtocolType          = pstNegRsltInd->usProtocolType;
            stSessionNegRsltInfo.usProtocolSubType       = pstNegRsltInd->usProtocolSubType;

            CNAS_HSM_SndInternalSessionCloseInd(
                                    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_RCV_CAS_NEG_RSLD_IND,
                                    &stSessionNegRsltInfo);
        }
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_ProcAmpMsg_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd
)
{
    VOS_UINT8                           ucMsgType;

    ucMsgType = CNAS_HSM_AMP_MESSAGE_TYPE_BUTT;

    CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                           pstSnpDataInd->stMsgData.aucMsgData,
                           &ucMsgType);

    if (CNAS_HSM_AMP_MSG_TYPE_HARDWAREID_REQ == ucMsgType)
    {
        return CNAS_HSM_ProcHardWareIdReqFromAN_PreProc(pstSnpDataInd);
    }

    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}



VOS_UINT32 CNAS_HSM_ProcSmpMsg_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd
)
{
    VOS_UINT8                               ucMsgType;

    ucMsgType = CNAS_HSM_SMP_MESSAGE_TYPE_BUTT;
    CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                           pstSnpDataInd->stMsgData.aucMsgData,
                           &ucMsgType);

    if (CNAS_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_REQ == ucMsgType)
    {
        return CNAS_HSM_ProcKeepAliveReqFromAN_PreProc(pstSnpDataInd);
    }

    if (CNAS_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_RESP == ucMsgType)
    {
        return CNAS_HSM_ProcKeepAliveRspFromAN_PreProc(pstSnpDataInd);
    }
    if (CNAS_HSM_SMP_MESSAGE_TYPE_SESSION_CLOSE == ucMsgType)
    {
        return CNAS_HSM_ProcSessionClose_PreProc(pstSnpDataInd);
    }


    /* There is no PreProc SMP message to be handled in iteration 8 */
    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfHrpdSnpDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd = VOS_NULL_PTR;
    CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16                     enProtocolType;
    CNAS_HSM_EVENT_HANDLED_STATUES_ENUM_UINT32              enRlst;

    pstSnpDataInd = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU*)pstMsg;

    enProtocolType = pstSnpDataInd->enProtocolType;

    if (CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL == enProtocolType)
    {
        enRlst = CNAS_HSM_ProcAmpMsg_PreProc(pstSnpDataInd);
    }
    else if (CTTF_HRPD_SNP_SESSION_MANAGEMENT_PROTOCOL == enProtocolType)
    {
        enRlst = CNAS_HSM_ProcSmpMsg_PreProc(pstSnpDataInd);
    }
    else
    {
        enRlst = CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    return enRlst;
}


VOS_UINT32 CNAS_HSM_RcvApsOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_HSM_ORIG_REQ_STRU                                  *pstCallOrigMsg;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enSessionStatus;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubSta;

    enSessionStatus = CNAS_HSM_GetSessionStatus();

    enSessionType  = CNAS_HSM_GetNegoSessionType();

    pstCallOrigMsg = (APS_HSM_ORIG_REQ_STRU *)pstMsg;

    /* Get Current CAS and Session status, before sending connection open request to CAS. */
    enConvertedCasStatus         = CNAS_HSM_GetHrpdConvertedCasStatus();

    enSubSta                     = CNAS_HSM_GetCurrSubState();

    CNAS_HSM_LogConnMnmtStatusInfo();

    /* closing/opening the hrpd connection procedure,enter the fsm to buffer the current event */
    if ((CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND == enSubSta)
     || (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND == enSubSta))
    {
        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_SndApsOrigCnf(pstCallOrigMsg->ucCallId, HSM_APS_CAUSE_HRPD_SLAVE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    if ((CNAS_HSM_SESSION_STATUS_CLOSE == enSessionStatus)
     || (CNAS_HSM_SESSION_TYPE_HRPD != enSessionType))
    {
        CNAS_HSM_SndApsOrigCnf(pstCallOrigMsg->ucCallId, HSM_APS_CAUSE_SESSION_NOT_EXIST);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    if (VOS_TRUE == CNAS_HSM_IsInUatiProcedure())
    {
        CNAS_HSM_SndApsOrigCnf(pstCallOrigMsg->ucCallId, HSM_APS_CAUSE_IN_UATI_PROCEDURE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    if (VOS_TRUE == CNAS_HSM_IsInScpProcedure())
    {
        CNAS_HSM_SndApsOrigCnf(pstCallOrigMsg->ucCallId, HSM_APS_CAUSE_IN_SCP_PROCEDURE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* If CAS status is in INIT. */
    if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus)
    {
        CNAS_HSM_SndApsOrigCnf(pstCallOrigMsg->ucCallId, HSM_APS_CAUSE_CAN_NOT_EST_CONN);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* include UATI procedure and vacant in open state*/
    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvApsDiscReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enSessionStatus;
    APS_HSM_DISC_REQ_STRU                                  *pstDiscReq;
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;

    pstDiscReq      = (APS_HSM_DISC_REQ_STRU *)pstMsg;

    enSessionStatus = CNAS_HSM_GetSessionStatus();
    enConnStatus    = CNAS_HSM_GetConnStatus();

    CNAS_HSM_LogConnMnmtStatusInfo();

    /* establishing procedure,enter the fsm to buffer the current event */
    if (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND == CNAS_HSM_GetCurrSubState())
    {
        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    if ((CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
     || (CNAS_HSM_HRPD_CONN_STATUS_OPEN != enConnStatus)
     || (CNAS_HSM_SESSION_STATUS_CLOSE == enSessionStatus))
    {
        CNAS_HSM_SndApsDiscCnf(pstDiscReq->ucCallId, HSM_APS_CAUSE_SUCCESS);

        CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* include UATI procedure and vacant in open state*/
    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvEhsmConnEstReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enSessionStatus;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubSta;

    enSessionStatus = CNAS_HSM_GetSessionStatus();
    enSessionType   = CNAS_HSM_GetNegoSessionType();

    /* Get Current CAS and Session status, before sending connection open request to CAS. */
    enConvertedCasStatus     = CNAS_HSM_GetHrpdConvertedCasStatus();
    enSubSta                 = CNAS_HSM_GetCurrSubState();

    CNAS_HSM_LogConnMnmtStatusInfo();

    /* closing/opening the hrpd connection procedure,enter the fsm to buffer the current event */
    if ((CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND == enSubSta)
     || (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND  == enSubSta))
    {
        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_HRPD_SLAVE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    if ((CNAS_HSM_SESSION_STATUS_CLOSE == enSessionStatus)
     || (CNAS_HSM_SESSION_TYPE_EHRPD != enSessionType))
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_SESSION_NOT_EXIST);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    if (VOS_TRUE == CNAS_HSM_IsInUatiProcedure())
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_IN_UATI_PROCEDURE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    if (VOS_TRUE == CNAS_HSM_IsInScpProcedure())
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_IN_SCP_PROCEDURE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* If CAS status is Init. */
    if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_CAN_NOT_EST_CONN);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* include UATI procedure and vacant in open state*/
    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enSessionStatus;
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;

    /* Get Current CAS and Session status and CallID,
       before sending connection open request to CAS. */
    enSessionStatus = CNAS_HSM_GetSessionStatus();
    enConnStatus    = CNAS_HSM_GetConnStatus();

    CNAS_HSM_LogConnMnmtStatusInfo();

    /* establishing procedure,enter the fsm to buffer the current event */
    if (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND == CNAS_HSM_GetCurrSubState())
    {
        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    if ((CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
     || (CNAS_HSM_HRPD_CONN_STATUS_OPEN != enConnStatus)
     || (CNAS_HSM_SESSION_STATUS_CLOSE == enSessionStatus))
    {
        CNAS_HSM_SndEhsmDiscCnf();

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* include UATI procedure and vacant in open state*/
    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}





VOS_UINT32 CNAS_HSM_RcvCasSysTimeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SYSTEM_TIME_IND_STRU *pstSysTimeInd = VOS_NULL_PTR;

    pstSysTimeInd = (CAS_CNAS_HRPD_SYSTEM_TIME_IND_STRU *)pstMsg;

    /* Save the CDMA Sys time and current tick */
    CNAS_HSM_SaveSysTimeAndCurSysTick(pstSysTimeInd->aulSystemTime);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvApsConnRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_HSM_CONNECT_RSP_STRU           *pstConnRspMsg;

    pstConnRspMsg = (APS_HSM_CONNECT_RSP_STRU *)pstMsg;

    CNAS_HSM_SaveHsmCallId(pstConnRspMsg->ucCallId);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvAps1xToHrpdHandOffReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_HSM_1X_TO_HRPD_HANDOFF_REQ_STRU     *pstApsHandOffMsg;

    pstApsHandOffMsg = (APS_HSM_1X_TO_HRPD_HANDOFF_REQ_STRU *)pstMsg;

    CNAS_HSM_SndHluHandOffReq(pstApsHandOffMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHlu1xToHrpdHandOffCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU     *pstHluHandOffCnf;
    HSM_APS_CAUSE_ENUM_UINT32                enCause;

    pstHluHandOffCnf = (HLU_HSM_1X_TO_HRPD_HANDOFF_CNF_STRU *)pstMsg;

    if (CNAS_HLU_HSM_HANDOFF_SUCCESS == pstHluHandOffCnf->ulCause)
    {
        enCause = HSM_APS_CAUSE_SUCCESS;
    }
    else
    {
        enCause = HSM_APS_CAUSE_HANDOFF_FAIL;
    }

    CNAS_HSM_SndApsHandOffCnf(enCause);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHluLocChngdInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HLU_HSM_LOC_CHANGED_IND_STRU       *pstHluLocChngMsg;

    pstHluLocChngMsg = (HLU_HSM_LOC_CHANGED_IND_STRU *)pstMsg;

    CNAS_HSM_SndApsLocChngdInd(pstHluLocChngMsg);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvCasHrpdConnOpenInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_CONN_OPEN_IND_STRU                       *pstConnOpenIndMsg;
    VOS_UINT8                                               ucIsSessionNegOnGoing;
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enConnOpenIndRsltConvert;

    pstConnOpenIndMsg = (CAS_CNAS_HRPD_CONN_OPEN_IND_STRU *)pstMsg;

    if ( CAS_CNAS_HRPD_CONN_OPEN_RSLT_SUCC == pstConnOpenIndMsg->enRslt)
    {
        CNAS_HSM_SetConnStatus(CNAS_HSM_HRPD_CONN_STATUS_OPEN);
    }

    ucIsSessionNegOnGoing = CNAS_HSM_GetSessionNegOngoingFlag();

    if ((VOS_FALSE                                          == ucIsSessionNegOnGoing)
     || ((VOS_TRUE                                          == ucIsSessionNegOnGoing)
      && ((CAS_CNAS_HRPD_CONN_OPEN_RSLT_PERSIST_FAIL        == pstConnOpenIndMsg->enRslt)
       || (CAS_CNAS_HRPD_CONN_OPEN_RSLT_MAX_PROBE           == pstConnOpenIndMsg->enRslt)
       || (CAS_CNAS_HRPD_CONN_OPEN_RSLT_PREFER_CH_NOT_VALID == pstConnOpenIndMsg->enRslt))))
    {
        enConnOpenIndRsltConvert = CNAS_HSM_ConvertConnOpenRsltFromCasToHsm(pstConnOpenIndMsg->enRslt);

        CNAS_HSM_SndHsdConnOpenInd(enConnOpenIndRsltConvert);
    }

    /* 目前只在该状态处理这个消息 */
    if (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND == CNAS_HSM_GetCurrSubState())
    {
        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    /* hsm发送建链后，收到掉网消息，此时cas会回复建链失败，此时不能给aps/ehsm上报该结果 */
    if (CAS_CNAS_HRPD_CONN_OPEN_RSLT_SUCC != pstConnOpenIndMsg->enRslt)
    {
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* scp激活过程中,cas会上报建链断链操作，此时并无session，不需要上报给aps/ehsm */
    if (CNAS_HSM_SESSION_STATUS_OPEN != CNAS_HSM_GetSessionStatus())
    {
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    if (CNAS_CCB_PS_RATTYPE_HRPD == CNAS_CCB_GetCurrPsRatType())
    {
        CNAS_HSM_SndApsConnInd(CNAS_HSM_CALL_ID_INVALID);
    }
    else if (CNAS_CCB_PS_RATTYPE_EHRPD == CNAS_CCB_GetCurrPsRatType())
    {
        CNAS_HSM_SndEhsmConnInd();
    }
    else
    {

    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdConnCloseInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_L1_STA_ENUM_UINT32                             enCurrMainState;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubSta;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CAS_CNAS_HRPD_CONN_CLOSE_IND_STRU                      *pstConnCloseInd;

    enSubSta = CNAS_HSM_GetCurrSubState();

    enCurrMainState = CNAS_HSM_GetCurrMainState();

    pstConnCloseInd = (CAS_CNAS_HRPD_CONN_CLOSE_IND_STRU *)pstMsg;

    if (CNAS_HSM_L1_STA_OPEN == enCurrMainState)
    {
        CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_CONN_CLOSE);
    }

    CNAS_HSM_SetConnStatus(CNAS_HSM_HRPD_CONN_STATUS_CLOSE);

    if (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND != enSubSta)
    {
        enSessionType = CNAS_HSM_GetNegoSessionType();

        if (CNAS_HSM_SESSION_TYPE_HRPD == enSessionType)
        {
            ucCallId = CNAS_HSM_GetHsmCallId();

            if (ucCallId != CNAS_HSM_CALL_ID_INVALID)
            {
                if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == CNAS_HSM_ConvertCasCloseReasonToHsmCause(pstConnCloseInd->enConnCloseReason))
                {
                    CNAS_HSM_SndApsDiscInd(ucCallId, HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X);
                }
                else
                {
                    CNAS_HSM_SndApsDiscInd(ucCallId, HSM_APS_CAUSE_SUCCESS);
                }
            }

            CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
        }
        else if (CNAS_HSM_SESSION_TYPE_EHRPD == enSessionType)
        {
            CNAS_HSM_SndEhsmDiscInd();
        }
        else
        {
            /* 无session不通知APS/EHSM */
        }
     }

    /* HSM state machine might have initiated connection close, and it may have been
       waiting for CLOSE_IND from CAS, so pass to state machine too. */
    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasDataServiceAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SndApsHrpdAvailableInd();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvCasIdleHoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_L1_STA_ENUM_UINT32         enCurrMainState;

    enCurrMainState = CNAS_HSM_GetCurrMainState();

    if (CNAS_HSM_L1_STA_OPEN == enCurrMainState)
    {
        CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_IDLE_HO);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvTiKeepAliveTimerExpired
Description     :   Handles the Keep alive timer expired message.
Input parameters:   VOS_UINT32                          ulEventType,
                    struct MsgCB                       *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History  :
1)  Date           : 2015-05-30
    Author         : a00295761
    Modify content : Create
2)  日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
3)  Date           : 2015-10-08
    Author         : w00351686
    Modify content : DTS2015092201636: package fuction when no forward traffic
                     channel data was received during the time ulKeepAliveTimerLen
*****************************************************************************/

VOS_UINT32 CNAS_HSM_RcvTiKeepAliveTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulSysTickFwdTrafChan;
    VOS_UINT32                          ulOldSysTickFwdTrafChan;


    VOS_UINT32                          ulTotalTimerRunCount;
    VOS_UINT32                          ulTimerExpiredCount;

    /* First, HSM must judge if the Required Keep Alive Timer has fully expired, as the Keep Alive timer length maybe
        greater than the Maximum timer length */

    /* Get the Total Timer Run count and total Time Expired count */
    ulTotalTimerRunCount = CNAS_HSM_GetKeepAliveTimerTotalRunCount();
    ulTimerExpiredCount  = CNAS_HSM_GetKeepAliveTimerExpiredCount();

    /* Increment the Total Timer Expired Count and save to the Keep alive timer ctx global variable */
    ulTimerExpiredCount++;
    CNAS_HSM_SetKeepAliveTimerExpiredCount(ulTimerExpiredCount);

    if (ulTimerExpiredCount != ulTotalTimerRunCount)
    {
        /* If the timer expired count is not equal to total timer run count, the required Keep Alive timer len is not
             complete. The function will restart the Keep Alive timer. */
        CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_TIMER_NOT_FULLY_EXPIRED);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* Get the system tick updated by Forward Traffic channel monitor Callback function and the previously stored
        System Tick */
    ulSysTickFwdTrafChan       = CNAS_HSM_GetSysTickFwdTrafficChan();
    ulOldSysTickFwdTrafChan    = CNAS_HSM_GetOldSysTickFwdTrafChan();

    if (ulSysTickFwdTrafChan == ulOldSysTickFwdTrafChan)
    {
        /* If the Two System Tick values are same, then no forward traffic channel data was received during the time
             ulKeepAliveTimerLen */


        CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_FWD_TRAF_DATA_NOT_RCVD);
        return CNAS_HSM_FSM_EVENT_HANDLED;

    }
    else
    {
        /* If the two system Ticks are not equal, then AT has received forward traffic channel data from AN. The function
             starts the keep alive timer with Timer Len calculated based on ulSysTickFwdTrafChan */
        CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_FWD_TRAF_DATA_RCVD);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }
}




VOS_UINT32 CNAS_HSM_ProcKeepAliveReqFromAN_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstKeepAliveReq
)
{
    CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU    stKeepAliveReq;
    VOS_UINT32                          ulDecodeRslt;

    /* If Keep alive timer is not running, then do not process the Keep alive req */
    if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_KEEP_ALIVE_TIMER, 0))
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcKeepAliveReqFromAN_PreProc: Keep alive timer is not running! ");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    NAS_MEM_SET_S(&stKeepAliveReq, sizeof(stKeepAliveReq), 0x0, sizeof(CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU));

    ulDecodeRslt = CNAS_HSM_DecodeKeepAliveReq(pstKeepAliveReq->stMsgData.aucMsgData,
                                               pstKeepAliveReq->stMsgData.usMsgBitLen,
                                               (VOS_VOID*)&stKeepAliveReq);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                          NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_REQ_DOWN,
                          UEPS_PID_HSM,
                          (VOS_UINT32)(pstKeepAliveReq->stMsgData.usMsgBitLen),
                          pstKeepAliveReq->stMsgData.aucMsgData);


    if (CNAS_HSM_DECODE_SUCCESS != ulDecodeRslt)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcKeepAliveReqFromAN_PreProc: Decode msg content fail");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_SndCasHrpdSessionBeginNtf(CNAS_CAS_HRPD_SESSION_TYPE_MT_KEEP_ALIVE);

    CNAS_HSM_SndKeepAliveRspMsg(stKeepAliveReq.ucTransId);

    CNAS_HSM_StartTimer(TI_CNAS_HSM_MT_KEEP_ALIVE_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);

    CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_RCV_KEEP_ALIVE_MSG);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_ProcKeepAliveRspFromAN_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstKeepAliveRsp
)
{
    CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU   stKeepAliveRsp;
    VOS_UINT32                          ulDecodeRslt;

    NAS_MEM_SET_S(&stKeepAliveRsp, sizeof(stKeepAliveRsp), 0x0, sizeof(CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU));

    ulDecodeRslt = CNAS_HSM_DecodeKeepAliveResp(pstKeepAliveRsp->stMsgData.aucMsgData,
                                                pstKeepAliveRsp->stMsgData.usMsgBitLen,
                                                (VOS_VOID*)&stKeepAliveRsp);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                          NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_RESP_DOWN,
                          UEPS_PID_HSM,
                          (VOS_UINT32)(pstKeepAliveRsp->stMsgData.usMsgBitLen),
                          pstKeepAliveRsp->stMsgData.aucMsgData);

    if (CNAS_HSM_DECODE_SUCCESS != ulDecodeRslt)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcKeepAliveRspFromAN_PreProc: Decode msg content fail");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    if (stKeepAliveRsp.ucTransId != CNAS_HSM_GetKeepAliveReqTransId())
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcKeepAliveRspFromAN_PreProc: trans id not matched");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_KEEP_ALIVE_RSP);

    CNAS_HSM_VoteEnterSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_KEEP_ALIVE_PROCEDURE);

    CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_RCV_KEEP_ALIVE_MSG);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_ProcHardWareIdReqFromAN_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstHardWareIdReq
)
{
    CNAS_HSM_HARDWARE_ID_REQ_MSG                            stHareWareIdReq;
    CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU                  stHardWareId;
    CNAS_HSM_HARDWARE_ID_INFO_STRU                         *pstHwid;
    VOS_UINT32                                              ulDecodeRslt;

    ulDecodeRslt = CNAS_HSM_DecodeHardwareIdRequest(pstHardWareIdReq->stMsgData.aucMsgData,
                                                    pstHardWareIdReq->stMsgData.usMsgBitLen,
                                                    (VOS_VOID*)&stHareWareIdReq);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                          NAS_OTA_MSG_HSM_AMP_MSG_TYPE_HARDWAREID_REQ,
                          UEPS_PID_HSM,
                          (VOS_UINT32)(pstHardWareIdReq->stMsgData.usMsgBitLen),
                          pstHardWareIdReq->stMsgData.aucMsgData);


    if (CNAS_HSM_DECODE_SUCCESS != ulDecodeRslt)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcHardWareIdReqFromAN_PreProc: Decode msg content fail");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    pstHwid = CNAS_HSM_GetHardwareIdInfo();

    NAS_MEM_SET_S(&stHardWareId, sizeof(stHardWareId), 0x0, sizeof(CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU));
    stHardWareId.ulEsn             = pstHwid->ulEsn;
    stHardWareId.enHwidType        = pstHwid->enHwidType;
    stHardWareId.ucTransactionId   = stHareWareIdReq.ucTransactionId;

    NAS_MEM_CPY_S(stHardWareId.aucMeId, sizeof(stHardWareId.aucMeId), pstHwid->aucMeId, sizeof(pstHwid->aucMeId));

    CNAS_HSM_SndCasHrpdSessionBeginNtf(CNAS_CAS_HRPD_SESSION_TYPE_HARD_ID);

    CNAS_HSM_StartTimer(TI_CNAS_HSM_HARDWARE_ID_RSP_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);

    CNAS_HSM_SndHardWareIdRspMsg(&stHardWareId);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}




VOS_UINT32 CNAS_HSM_RcvTiMoKeepAliveWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiMoKeepAliveWaitSnpDataCnfExpired_PreProc: timer out");

    CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_MO_KEEP_ALIVE);

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_KEEP_ALIVE_RSP);

    CNAS_HSM_VoteEnterSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_KEEP_ALIVE_PROCEDURE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvTiWaitKeepAliveRspExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiWaitKeepAliveProcedureFinishExpired_PreProc: timer out");

    CNAS_HSM_VoteEnterSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_KEEP_ALIVE_PROCEDURE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvTiMtKeepAliveWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiMtKeepAliveWaitSnpDataCnfExpired_PreProc: timer out");

    CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_MT_KEEP_ALIVE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvTiHardWareIdRspWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiHardWareIdRspWaitSnpDataCnfExpired_PreProc: timer out");

    CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_HARD_ID);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvTiSessionCloseRspWaitSnpDataCnfExpired_PreProc
Description     :   Handles the session close timer expired message.
Input parameters:   VOS_UINT32                          ulEventType,
                    struct MsgCB                       *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History  :
1)  Date           : 2015-06-08
    Author         : y00307564
    Modify content : Create
2)  Date           : 2015-06-016
    Author         : t00323010
    Modify content : Iteration 12: session close wait snp data cnf子状态进状态机
*****************************************************************************/

VOS_UINT32 CNAS_HSM_RcvTiSessionCloseRspWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiSessionCloseRspWaitSnpDataCnfExpired_PreProc: timer out");

    if (CNAS_HSM_SS_SESSION_DEACT_WAIT_SESSION_CLOSE_SNP_DATA_CNF == CNAS_HSM_GetCurrSubState())
    {
        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }
    else
    {
        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_SESSION_CLOSE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }


}


#ifdef DMT


VOS_UINT32 CNAS_HSM_RcvHsmModifySessionSeedReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_MODIFY_SESSION_SEED_REQ_STRU              *pstModifySeedReq;

    pstModifySeedReq = (CNAS_HSM_HSM_MODIFY_SESSION_SEED_REQ_STRU *)pstMsg;

    g_ulCurSessionSeed  = pstModifySeedReq->ulSessionSeed;

    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsmModifyCurSysTickReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_MODIFY_CUR_SYS_TICK_REQ_STRU              *pstModifyTickReq;

    pstModifyTickReq = (CNAS_HSM_HSM_MODIFY_CUR_SYS_TICK_REQ_STRU *)pstMsg;

    g_ulCurTick = pstModifyTickReq->ulCurSysTick;

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsmFwdTrafChanDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HSM will directly call the function registered to CTTF to monitor traffic channel data */
    CNAS_HSM_ProcTrafficFlowOnForwardChannel();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsmModifyAmpSmpAttrReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_MODIFY_SMP_AMP_ATTR_REQ_STRU              *pstModifyAmpSmpAttrReq;

    pstModifyAmpSmpAttrReq = (CNAS_HSM_HSM_MODIFY_SMP_AMP_ATTR_REQ_STRU *)pstMsg;

    NAS_MEM_CPY_S(&g_stAmpNegAttribs, sizeof(g_stAmpNegAttribs), &(pstModifyAmpSmpAttrReq->stHsmAmpNegAttribs), sizeof(CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU));

    NAS_MEM_CPY_S(&g_stSmpNegAttribs, sizeof(g_stSmpNegAttribs), &(pstModifyAmpSmpAttrReq->stHsmSmpNegAttribs), sizeof(CAS_HRPD_DEFAULT_SMP_ATTRIB_STRU));

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

#endif


VOS_VOID CNAS_HSM_StoreAmpNegAttrib_PreProc(
    CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU   *pstAmpNegAttribs
)
{
    CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU                      *pstHsmAmpNegAttrib;

    pstHsmAmpNegAttrib = CNAS_HSM_GetHrpdAmpNegAttribAddr();

    pstHsmAmpNegAttrib->usHardwareSeparableFromSession    = pstAmpNegAttribs->usHardwareSeparableFromSession;
    pstHsmAmpNegAttrib->usMaxNoMonitorDistance            = pstAmpNegAttribs->usMaxNoMonitorDistance;
    pstHsmAmpNegAttrib->usReducedSubnetMaskOffset         = pstAmpNegAttribs->usReducedSubnetMaskOffset;
    pstHsmAmpNegAttrib->usSupportGAUPMaxNoMonitorDistance = pstAmpNegAttribs->usSupportGAUPMaxNoMonitorDistance;
    pstHsmAmpNegAttrib->usSupportSecondaryColorCodes      = pstAmpNegAttribs->usSupportSecondaryColorCodes;

    return;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdCommitInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU    stAmpNegAttribs;
    CAS_HRPD_DEFAULT_SMP_ATTRIB_STRU    stSmpNegAttribs;
    CNAS_HSM_AMP_NEG_ATTRIB_STRU        stHsmAmpNegAttribs;
    CNAS_HSM_SMP_NEG_ATTRIB_STRU        stHsmSmpNegAttribs;

    NAS_MEM_SET_S(&stAmpNegAttribs, sizeof(stAmpNegAttribs), 0x00, sizeof(CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU));

    NAS_MEM_SET_S(&stSmpNegAttribs, sizeof(stSmpNegAttribs), 0x00, sizeof(CAS_HRPD_DEFAULT_SMP_ATTRIB_STRU));

    NAS_MEM_SET_S(&stHsmAmpNegAttribs, sizeof(stHsmAmpNegAttribs), 0x00, sizeof(CNAS_HSM_AMP_NEG_ATTRIB_STRU));

    NAS_MEM_SET_S(&stHsmSmpNegAttribs, sizeof(stHsmSmpNegAttribs), 0x00, sizeof(CNAS_HSM_SMP_NEG_ATTRIB_STRU));

    /* achieve amp neg atrrs */
    CAS_HRPD_HSCP_GetDefaultAmpAttr(&stAmpNegAttribs);

    /* achieve smp neg attrs */
    CAS_HRPD_HSCP_GetDefaultSmpAttr(&stSmpNegAttribs);

    /* store AMP neg attribs  */
    CNAS_HSM_StoreAmpNegAttrib_PreProc(&stAmpNegAttribs);

    /* store SMP neg attrib */
    /* If the TsmpClose has changed from previous value, process the keep alive timer */
    if (VOS_TRUE == CNAS_HSM_IsTsmpCloseValueChanged(stSmpNegAttribs.usTsmpClose))
    {
        /* Update the new Tsmpclose value to the context */
        CNAS_HSM_SetTsmpClose(stSmpNegAttribs.usTsmpClose);

        CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_TSMP_CLOSE_CHANGED);

    }

    stHsmAmpNegAttribs.usMaxNoMonitorDistance            = stAmpNegAttribs.usMaxNoMonitorDistance;
    stHsmAmpNegAttribs.usHardwareSeparableFromSession    = stAmpNegAttribs.usHardwareSeparableFromSession;
    stHsmAmpNegAttribs.usSupportGAUPMaxNoMonitorDistance = stAmpNegAttribs.usSupportGAUPMaxNoMonitorDistance;
    stHsmAmpNegAttribs.usReducedSubnetMaskOffset         = stAmpNegAttribs.usReducedSubnetMaskOffset;
    stHsmAmpNegAttribs.usSupportSecondaryColorCodes      = stAmpNegAttribs.usSupportSecondaryColorCodes;

    stHsmSmpNegAttribs.usTsmpClose                       = stSmpNegAttribs.usTsmpClose;

    /* hook a msg */
    CNAS_HSM_LogAmpSmpNegAttribInfoInd(&stHsmAmpNegAttribs, &stHsmSmpNegAttribs);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfSnpDataCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_CNF_STRU                       *pstCttfSnpDataCnf;
    VOS_UINT16                                              usSessionCloseRespOpId;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enCurrSubState;
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_REASON_UNION              unDiscardMsgReason;

    pstCttfSnpDataCnf   = (CTTF_CNAS_HRPD_SNP_DATA_CNF_STRU *)pstMsg;

    enCurrSubState      = CNAS_HSM_GetCurrSubState();

    unDiscardMsgReason.stDiscardSnpDataCnfReason.enMainState    = CNAS_HSM_GetCurrMainState();
    unDiscardMsgReason.stDiscardSnpDataCnfReason.enSubState     = enCurrSubState;
    unDiscardMsgReason.stDiscardSnpDataCnfReason.usRcvOpId      = pstCttfSnpDataCnf->usOpId;

    if (VOS_TRUE == CNAS_HSM_IsHardWareIdResSnpDataCnf(pstCttfSnpDataCnf->usOpId))
    {
        CNAS_HSM_StopTimer(TI_CNAS_HSM_HARDWARE_ID_RSP_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_HARD_ID);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    unDiscardMsgReason.stDiscardSnpDataCnfReason.usSndOpId      = CNAS_HSM_GetHardWareIdRspSnpDataReqOpId();

    if (VOS_TRUE == CNAS_HSM_IsKeepAliveReqSnpDataCnf(pstCttfSnpDataCnf->usOpId))
    {
        CNAS_HSM_StopTimer(TI_CNAS_HSM_MO_KEEP_ALIVE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_MO_KEEP_ALIVE);

        if (CTTF_HRPD_SNP_RSLT_FAIL == pstCttfSnpDataCnf->enRslt)
        {
            CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_KEEP_ALIVE_RSP);

            CNAS_HSM_VoteEnterSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_KEEP_ALIVE_PROCEDURE);
        }

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    unDiscardMsgReason.stDiscardSnpDataCnfReason.usSndOpId = CNAS_HSM_GetKeepAliveReqSnpDataReqOpId();

    if (VOS_TRUE == CNAS_HSM_IsKeepAliveResSnpDataCnf(pstCttfSnpDataCnf->usOpId))
    {
        CNAS_HSM_StopTimer(TI_CNAS_HSM_MT_KEEP_ALIVE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_MT_KEEP_ALIVE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    unDiscardMsgReason.stDiscardSnpDataCnfReason.usSndOpId = CNAS_HSM_GetKeepAliveRspSnpDataReqOpId();

    usSessionCloseRespOpId  = CNAS_HSM_GetSessionCloseSnpDataReqOpId();

    /* session deact子状态在状态机中处理snp data cnf, 预处理函数直接跳过 */
    if ((CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF, 0))
     && (CNAS_HSM_SS_SESSION_DEACT_WAIT_SESSION_CLOSE_SNP_DATA_CNF != enCurrSubState))
    {
        if (usSessionCloseRespOpId == pstCttfSnpDataCnf->usOpId)
        {
            CNAS_HSM_StopTimer(TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF);

            CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_SESSION_CLOSE);

            if (CTTF_HRPD_SNP_RLST_SUCC == pstCttfSnpDataCnf->enRslt)
            {
                CNAS_HSM_SndTtfHrpdPASessionCloseInd();
            }

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        unDiscardMsgReason.stDiscardSnpDataCnfReason.usSndOpId      = usSessionCloseRespOpId;
    }

    if (VOS_TRUE == CNAS_HSM_IsUatiCmplSnpDataCnf(pstCttfSnpDataCnf->usOpId))
    {
        CNAS_HSM_RcvUatiCmplSnpDataCnf_PreProc(pstCttfSnpDataCnf->enRslt, pstCttfSnpDataCnf->enFailReason);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    unDiscardMsgReason.stDiscardSnpDataCnfReason.usSndOpId      = CNAS_HSM_GetUatiCmplSnpDataReqOpId();

    if ((enCurrSubState != CNAS_HSM_SS_UATI_REQUEST_WAIT_SNP_DATA_CNF)
     && (enCurrSubState != CNAS_HSM_SS_SESSION_DEACT_WAIT_SESSION_CLOSE_SNP_DATA_CNF))
    {
        /* 打印丢弃snp data cnf场景 */
        CNAS_HSM_LogDiscardMsgInfo(CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ERROR_SNP_DATA_CNF, &unDiscardMsgReason);

        return CNAS_HSM_FSM_EVENT_HANDLED;

    }

    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvEhsmLteRegSuccessInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SetRegLteSuccFlag(VOS_TRUE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvRrmStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRM_PS_STATUS_IND_STRU             *pstRrmStatusInd;

    pstRrmStatusInd = (RRM_PS_STATUS_IND_STRU *)pstMsg;

    CNAS_HSM_SndRrmDeRegisterInd(pstRrmStatusInd->enTaskType, VOS_RATMODE_HRPD);

    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubState;

     CNAS_HSM_ClearRelativeCtx_PreProc();

    /* in other substate, Suspend will be cached, and after current procedure finish
       will go on process the cached suspend ind in vacant substate, at that time we
       will send suspend ind to EHSM */
    if (CNAS_HSM_SS_VACANT == CNAS_HSM_GetCurrSubState())
    {
        CNAS_HSM_SndEhsmSuspendInd();
    }

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, 0))
    {
        CNAS_HSM_ResetUatiCompleteRetryTimes();

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
    }

    enConnStatus    = CNAS_HSM_GetConnStatus();

    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN == enConnStatus)
    {
        enSubState     = CNAS_HSM_GetCurrSubState();

        CNAS_HSM_SetConnStatus(CNAS_HSM_HRPD_CONN_STATUS_CLOSE);

        if (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND == enSubState)
        {
            return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
        }

        enSessionType  = CNAS_HSM_GetNegoSessionType();

        if (CNAS_HSM_SESSION_TYPE_EHRPD == enSessionType)
        {
            CNAS_HSM_SndEhsmDiscInd();
        }
        else if (CNAS_HSM_SESSION_TYPE_HRPD == enSessionType)
        {
            ucCallId = CNAS_HSM_GetHsmCallId();

            if (ucCallId != CNAS_HSM_CALL_ID_INVALID)
            {
                CNAS_HSM_SndApsDiscInd(ucCallId, HSM_APS_CAUSE_HRPD_SLAVE);
            }

            CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
        }
        else
        {
            /* do noting */
        }

    }

    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_ClearRelativeCtx_PreProc();

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, 0))
    {
        CNAS_HSM_ResetUatiCompleteRetryTimes();

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
    }

    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_ClearRelativeCtx_PreProc();

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, 0))
    {
        CNAS_HSM_ResetUatiCompleteRetryTimes();

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
    }

    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvTiAddressTimerExp_PreProc
Description     :   Process the TI_CNAS_HSM_ADDRESS_TIMER
Input parameters:   VOS_UINT32                          ulEventType,
                    struct MsgCB                       *pstMsg
Outout parameters:  None
Return Value    :   None;

Modify History  :
1)  Date           : 2015-05-31
    Author         : m00312079
    Modify content : Create
2)  Date           : 2015-09-07
    Author         : m00312079
    Modify content : DTS2015081801520:发送更新后的receive ATI List给cttf
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvTiAddressTimerExp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_ATI_LIST_INFO_STRU                            *pstPubRcvATIList;
    VOS_UINT8                                               ucLoop;
    VOS_UINT32                                              ulTimerRunLen;
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enSessionStatus;

    enSessionStatus = CNAS_HSM_GetSessionStatus();

    if (CNAS_HSM_SESSION_STATUS_OPEN != enSessionStatus)
    {
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    pstPubRcvATIList    = CNAS_HSM_GetReceivedATIListAddr();

    /* address timer is running ,the ATI rec num must larger than 3;
      else ignore this abnormal message */
    if (pstPubRcvATIList->ulATIRecordNum < 3)
    {
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    ulTimerRunLen       =  pstPubRcvATIList->astATIEntry[2].ulAddrTimerLen;
    /* delete the older entry
     struct of ReceiveATIList
     -------- -------- -------- -------- --------
    |   BATI | UATI0  | UATI1  | UATI2  | UATI3  |
    |        |        |        |        |        |
     -------- -------- -------- -------- --------
    */
    pstPubRcvATIList->ulATIRecordNum--;
    for (ucLoop = 1; ucLoop < pstPubRcvATIList->ulATIRecordNum; ucLoop++)
    {
        NAS_MEM_CPY_S(&(pstPubRcvATIList->astATIEntry[ucLoop]),
                      sizeof(CNAS_HSM_ATI_RECORD_STRU),
                      &(pstPubRcvATIList->astATIEntry[ucLoop + 1]),
                      sizeof(CNAS_HSM_ATI_RECORD_STRU));

        /* refresh the address timer length of remain entry in RecATIList */
        pstPubRcvATIList->astATIEntry[ucLoop].ulAddrTimerLen -= ulTimerRunLen;
    }

    NAS_MEM_SET_S(&(pstPubRcvATIList->astATIEntry[ucLoop]),
                sizeof(CNAS_HSM_ATI_RECORD_STRU),
                0x00,
                sizeof(CNAS_HSM_ATI_RECORD_STRU));

    pstPubRcvATIList->astATIEntry[ucLoop].enATIType = CNAS_HSM_ATI_TYPE_INACTIVE;

    if (pstPubRcvATIList->ulATIRecordNum >= 3)
    {
        /* restart the address timer */
        CNAS_HSM_StartTimer(TI_CNAS_HSM_ADDRESS_TIMER, pstPubRcvATIList->astATIEntry[2].ulAddrTimerLen);
    }

    /* 添加钩包ReceiveATIList */
    CNAS_HSM_LogReceiveATIListInfo(pstPubRcvATIList);

    CNAS_HSM_SndMacReceiveAtiNotify(pstPubRcvATIList);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasSessionChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SESSION_CHANGE_IND_STRU                  *pstSessionChgInd;
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enCurrSessionRelType;

    pstSessionChgInd = (CAS_CNAS_HRPD_SESSION_CHANGE_IND_STRU *)pstMsg;

    enCurrSessionRelType = CNAS_HSM_ConvertCasSessionRelTypeToHsmSessionRelType(pstSessionChgInd->enSessionReleaseType);

    CNAS_HSM_SetCurrSessionRelType(enCurrSessionRelType);

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SUCCESS,
                                       VOS_TRUE, /* new session */
                                       enCurrSessionRelType);
    return CNAS_HSM_FSM_EVENT_HANDLED;
}



/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsdOhmInd_PreProc
Description     :   process ID_HSD_HSM_OVERHEAD_MSG_IND msg in PreProc
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED-------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED---the current event need to further process

Modify History  :
1)  Date           : 2015-06-10
    Author         : m00312079
    Modify content : Create

2)  Date           : 2015-10-28
    Author         : m00312079
    Modify content : DTS2015102803041,收到OHM消息后 如果HSM存储的CAS状态为CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT，
                     则将CAS的状态设置为CNAS_HSM_HRPD_CAS_STATUS_ENUM_IDLE
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_HSM_OVERHEAD_MSG_IND_STRU                          *pstOverHeadMsgInd;
    CNAS_HSM_L1_STA_ENUM_UINT32                             enCurrMainState;
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;
    CNAS_HSM_HRPD_SYS_INFO_STRU                            *pstHprdSysInfo;
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enCurrSessionRelType;
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enSessionStatus;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enCurrSessionType;

    VOS_UINT32                                              ulHsmEventType;
    VOS_UINT8                                               ucIndex;

    pstOverHeadMsgInd    = (HSD_HSM_OVERHEAD_MSG_IND_STRU *)pstMsg;
    /* DTS2015102803041,收到OHM消息后 如果HSM存储的CAS状态为CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT，
       则将CAS的状态设置为CNAS_HSM_HRPD_CAS_STATUS_ENUM_IDLE */
    if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_SaveHrpdConvertedCasStatus(CNAS_HSM_HRPD_CAS_STATUS_ENUM_IDLE);
    }

    enConnStatus    = CNAS_HSM_GetConnStatus();

    enCurrMainState = CNAS_HSM_GetCurrMainState();

    /* 只更新除经纬度外的系统消息,原因是由于经纬度信息主要是为了计算MaxNoMonitorDistance，按照协议只有在session
        open的时候才计算 */
    CNAS_HSM_UpdateHrpdSysInfo(pstOverHeadMsgInd);

    /* 更新位置信息有以下两种场景:
        1:HSM的主状态为OPEN态
        2:SCP在recovery过程中 */
    if (CNAS_HSM_L1_STA_OPEN == enCurrMainState)
    {
        pstHprdSysInfo                                  = CNAS_HSM_GetHrpdSysInfoAddr();

        pstHprdSysInfo->lLatitude                       = pstOverHeadMsgInd->lLatitude;
        pstHprdSysInfo->lLongitude                      = pstOverHeadMsgInd->lLongitude;
    }

    /* 若缓存中有ohm消息，收到新的ohm消息后，使用新的ohm消息更新缓存中的，防止session deactive流程
       中收到ohm缓存了，后续uati流程中又收到新的ohm消息，未更新缓存中的ohm消息，导致后续open态处理
       旧的ohm，导致重新触发uati流程 */
    ulHsmEventType = CNAS_BuildEventType(UEPS_PID_HSD, (VOS_UINT16)ID_HSD_HSM_OVERHEAD_MSG_IND);

    ucIndex = CNAS_HSM_GetCacheIndexByEventType(ulHsmEventType);

    if (CNAS_HSM_INVAILD_CACHE_INDEX != ucIndex)
    {
        CNAS_HSM_SaveCacheMsg(ulEventType, pstMsg);
    }

    /* CAS链接状态只更新系统消息，不进状态机处理 */
    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN == enConnStatus)
    {
        /* 如果有数传业务，掉网后，cas可能会将page消息发到cnas，然后才发送ovhd消息到hsd，
           导致hsm在连接态不能及时给hsm回复neg rslt ind，导致不能及时上报^mode,掉网后回3g慢 */

        enSessionStatus      = CNAS_HSM_GetSessionStatus();
        if (CNAS_HSM_SESSION_STATUS_OPEN == enSessionStatus)
        {
            enCurrSessionRelType = CNAS_HSM_GetCurrSessionRelType();
            enCurrSessionType    = CNAS_HSM_GetNegoSessionType();

            /* TQE告警屏蔽 */
            if (CNAS_HSM_SESSION_TYPE_BUTT == enCurrSessionType)
            {
                CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvHsdOhmInd_PreProc: Curr Session Type is BUTT!");
            }

            CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SUCCESS,
                                               VOS_FALSE,/* old session */
                                               enCurrSessionRelType);

            CNAS_HSM_SndEhsmSessionInfoInd(enCurrSessionType);
        }

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubState;

    enConnStatus    = CNAS_HSM_GetConnStatus();

    enSessionType  = CNAS_HSM_GetNegoSessionType();

    /* 发生掉网，需要去注册资源 */
    CNAS_HSM_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_HRPD_SESSION_NEG, VOS_RATMODE_HRPD);

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, 0))
    {
        CNAS_HSM_ResetUatiCompleteRetryTimes();

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
    }

    CNAS_HSM_ClearRelativeCtx_PreProc();

    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN == enConnStatus)
    {
        enSubState = CNAS_HSM_GetCurrSubState();

        CNAS_HSM_SetConnStatus(CNAS_HSM_HRPD_CONN_STATUS_CLOSE);

        if (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND == enSubState)
        {
            return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
        }

        if (CNAS_HSM_SESSION_TYPE_EHRPD == enSessionType)
        {
            CNAS_HSM_SndEhsmDiscInd();
        }
        else if (CNAS_HSM_SESSION_TYPE_HRPD == enSessionType)
        {
            ucCallId = CNAS_HSM_GetHsmCallId();

            if (ucCallId != CNAS_HSM_CALL_ID_INVALID)
            {
                CNAS_HSM_SndApsDiscInd(ucCallId, HSM_APS_CAUSE_HRPD_NETWORK_LOST);
            }

            CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
        }
        else
        {
            /* do noting */
        }
    }

    return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdOhmNotCurrentInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Set OhmParameterUpToDate to 0 */
    CNAS_HSM_SetOhmParameterUpToDate(0);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_ProcSessionClose_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstSessionClose
)
{
    CNAS_HSM_SESSION_CLOSE_MSG_STRU                         stSessionClose;
    CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32                  ulDecodeRslt;
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubState;

    if (VOS_TRUE == CNAS_HSM_IsNeedDiscardSessionClose_PreProc())
    {
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    ulDecodeRslt = CNAS_HSM_DecodeSessionClose((VOS_UINT8 *)(&(pstSessionClose->stMsgData.aucMsgData[0])),
                                               pstSessionClose->stMsgData.usMsgBitLen,
                                               (VOS_VOID *)&stSessionClose);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                          NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_SESSION_CLOSE_DOWN,
                          UEPS_PID_HSM,
                          (VOS_UINT32)(pstSessionClose->stMsgData.usMsgBitLen),
                          pstSessionClose->stMsgData.aucMsgData);

    if (CNAS_HSM_DECODE_SUCCESS != ulDecodeRslt)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ProcSessionClose_PreProc: Decode msg content fail");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    enMainState = CNAS_HSM_GetCurrMainState();
    enSubState  = CNAS_HSM_GetCurrSubState();

    if (CNAS_HSM_L1_STA_SETUP == enMainState)
    {
        CNAS_HSM_SndInternalSessionCloseInd(
                            CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_SETUP,
                            VOS_NULL_PTR);
    }
    else if ((CNAS_HSM_L1_STA_OPEN                        == enMainState)
          && (CNAS_HSM_SS_SESSION_ACT_WAIT_SCP_ACTIVE_CNF == enSubState))
    {
        CNAS_HSM_SndInternalSessionCloseInd(
                            CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_OPEN_SESSION_ACT,
                            VOS_NULL_PTR);
    }
    /* 如果是在连接子状态机中，在预处理发送SessionClose到网络，否则在Deactive流程中发SessionClose到网络 */
    else if ((CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND  == enSubState)
          || (CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND == enSubState))
    {
        /* 将ID_CNAS_HSM_HSM_SESSION_CLOSE_IND消息的场景设置成IN_CONN_MNMT
          * 处理ID_CNAS_HSM_HSM_SESSION_CLOSE_IND消息时，将deactive raeson原因值设置为:
          * CNAS_HSM_SESSION_DEACT_REASON_INTERNAL_SESSION_CLOSE_IN_CONN_MNMT，
          * 在deactive流程中通过该原因值判断是否已经发送过SessionClose到网络
          */
        CNAS_HSM_SndInternalSessionCloseInd(
                            CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_IN_CONN_MNMT_SENT_SESSION_CLOSE,
                            VOS_NULL_PTR);

        stSessionClose.enCloseReason = CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_REPLY;

        CNAS_HSM_SndCasHrpdSessionBeginNtf(CNAS_CAS_HRPD_SESSION_TYPE_SESSION_CLOSE);

        CNAS_HSM_SndSessionCloseMsg(&stSessionClose);

        CNAS_HSM_StartTimer(TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF, TI_CNAS_HSM_WAIT_SNP_DATA_CNF_LEN);
    }
    else
    {
        CNAS_HSM_SndInternalSessionCloseInd(
                            CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_OPEN_NOT_SESSION_ACT,
                            VOS_NULL_PTR);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_IsNeedDiscardSessionClose_PreProc(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32         enMainState;
    CNAS_HSM_SS_ID_ENUM_UINT32          enSubState;

    enMainState = CNAS_HSM_GetCurrMainState();

    if ((CNAS_HSM_L1_STA_NULL     == enMainState)
     || (CNAS_HSM_L1_STA_INACTIVE == enMainState))
    {
        return VOS_TRUE;
    }

    enSubState = CNAS_HSM_GetCurrSubState();
    if ((CNAS_HSM_SS_SESSION_DEACT_WAIT_SESSION_CLOSE_SNP_DATA_CNF     == enSubState)
     || (CNAS_HSM_SS_SESSION_DEACT_WAIT_CONN_CLOSE_IND                 == enSubState)
     || (CNAS_HSM_SS_SESSION_DEACT_WAIT_SCP_DEACTIVE_CNF               == enSubState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 CNAS_HSM_IsCurCsimUimCardPresent(
    USIMM_CARD_STATUS_STRU             *pstCsimUimInfo
)
{
    /* USIMM_CARD_SERVICE_SUBNET_LOCK、 USIMM_CARD_SERVICE_GID1_LOCK、USIMM_CARD_SERVICE_GID2_LOCK认为是有卡的，
       与MMA处理usim card status ind时，处理保持一致。目前这三种原因值暂时未用到 */
    if (((USIMM_CARD_UIM                 == pstCsimUimInfo->enCardType)
      || (USIMM_CARD_CSIM                == pstCsimUimInfo->enCardType))
     && ((USIMM_CARD_SERVIC_AVAILABLE    == pstCsimUimInfo->enCardService)
      || (USIMM_CARD_SERVICE_SUBNET_LOCK == pstCsimUimInfo->enCardService)
      || (USIMM_CARD_SERVICE_GID1_LOCK   == pstCsimUimInfo->enCardService)
      || (USIMM_CARD_SERVICE_GID2_LOCK   == pstCsimUimInfo->enCardService)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvPihUsimStatusInd_PreProc
Description     :   Process the USIMM_CARDSTATUS_IND
Input parameters:   VOS_UINT32                          ulEventType,
                    struct MsgCB                       *pstMsg
Outout parameters:  None
Return Value    :   VOS_UINT32;

Modify History  :
1)  Date           : 2015-10-30
    Author         : y00307564
    Modify content : Create
2)  Date           : 2015-11-09
    Author         : y00307564
    Modify content : 清理stCsimUimInfo未初始化TQE告警
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvPihUsimStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_CARDSTATUS_IND_STRU                              *pstUsimMsg           = VOS_NULL_PTR;
    CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU                  *pstCardStatusChgInfo = VOS_NULL_PTR;
    USIMM_CARD_STATUS_STRU                                  stCsimUimInfo;

    pstUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)pstMsg;

    stCsimUimInfo.enCardType    = USIMM_CARD_TYPE_BUTT;
    stCsimUimInfo.enCardService = USIMM_CARD_SERVIC_BUTT;

    NAS_MEM_CPY_S(&stCsimUimInfo, sizeof(stCsimUimInfo), &(pstUsimMsg->stCsimUimInfo), sizeof(USIMM_CARD_STATUS_STRU));

    pstCardStatusChgInfo = CNAS_HSM_GetCardStatusChangeInfoAddr();

    if (VOS_TRUE == CNAS_HSM_IsCurCsimUimCardPresent(&stCsimUimInfo))
    {
        pstCardStatusChgInfo->ucIsCurCardPresent = VOS_TRUE;
    }
    else
    {
        pstCardStatusChgInfo->ucIsCurCardPresent = VOS_FALSE;
    }

    /* 目前只需要关注无卡到有卡的变化，目前不需要将pre状态设置为cur的，等到完成判断ESN_MEID_ME是否改变时，再设置为cur的状态 */
    if ((VOS_FALSE == pstCardStatusChgInfo->ucIsPreCardPresent) && (VOS_TRUE == pstCardStatusChgInfo->ucIsCurCardPresent))
    {
        CNAS_HSM_SndReadUsimmStoreEsnMeidRsltReq();

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* 有卡到无卡、无卡到无卡和有卡到有卡的状态可以不用考虑，只需将pre状态设置为cur的 */
    pstCardStatusChgInfo->ucIsPreCardPresent = pstCardStatusChgInfo->ucIsCurCardPresent;

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvUsimStoreEsnMeidRsltCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_QUERYESNMEIDRSLT_CNF_STRU    *pstStoreEsnMeidRsltCnf = VOS_NULL_PTR;
    CNAS_HSM_STORE_ESN_MEID_RSLT_STRU  *pstStoreEsnMeidRslt;

    pstStoreEsnMeidRsltCnf = (USIMM_QUERYESNMEIDRSLT_CNF_STRU *)pstMsg;

    pstStoreEsnMeidRslt = CNAS_HSM_GetStoreEsnMeidRsltAddr();

    if (VOS_OK != pstStoreEsnMeidRsltCnf->stCmdResult.ulResult)
    {
        pstStoreEsnMeidRslt->ucIsStored = VOS_FALSE;
    }
    else
    {
        pstStoreEsnMeidRslt->ucIsStored    = pstStoreEsnMeidRsltCnf->ucIsStored;

        /* 根据协议C.S0023-D section4.6.1, 卡回复的response中，仅bit1指示ESN_MEID_ME
        *  是否改变，若为1表示改变，0为未改变 */
        if (VOS_TRUE == pstStoreEsnMeidRsltCnf->ucIsStored)
        {
            if (0 == (pstStoreEsnMeidRsltCnf->ucStoreResult & 1))
            {
                pstStoreEsnMeidRslt->ucIsChanged = VOS_FALSE;
            }
            else
            {
                pstStoreEsnMeidRslt->ucIsChanged = VOS_TRUE;
            }
        }
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfHprdPaAccAuthStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_PA_ACCESS_AUTH_STATUS_IND_STRU          *pstAccessAuthStatusInd;
    CNAS_HSM_SESSION_CLOSE_INFO_STRU                       *pstSessionCloseInfo;
    CNAS_HSM_HRPD_SYS_INFO_STRU                            *pstHprdSysInfo;
    VOS_UINT8                                               aucCurrSubnet[CNAS_HSM_SUBNET_ID_MAX_LENGTH];

    NAS_MEM_SET_S(aucCurrSubnet, sizeof(aucCurrSubnet), 0x00, CNAS_HSM_SUBNET_ID_MAX_LENGTH);

    pstAccessAuthStatusInd    = (CTTF_CNAS_HRPD_PA_ACCESS_AUTH_STATUS_IND_STRU *)pstMsg;

    pstSessionCloseInfo = CNAS_HSM_GetSessionCloseInfoCtxAddr();

    if (pstAccessAuthStatusInd->ulResult != VOS_OK)
    {
        /* 根据CDG143.同一子网AN鉴权连续失败3次，需要Avoid该频点10分钟 */
        if (CTTF_HRPD_PA_ACCESS_AUTH_REJECT == pstAccessAuthStatusInd->enReason)
        {

            pstHprdSysInfo      = CNAS_HSM_GetHrpdSysInfoAddr();

            CNAS_HSM_GetSubnet(aucCurrSubnet,
                               pstHprdSysInfo->aucSectorId,
                               pstHprdSysInfo->ucSubNetMask);

            if (0 == pstSessionCloseInfo->ucCount)
            {
                pstSessionCloseInfo->ucCount++;

                NAS_MEM_CPY_S(pstSessionCloseInfo->aucSubnet,
                              sizeof(pstSessionCloseInfo->aucSubnet),
                              aucCurrSubnet,
                              CNAS_HSM_SUBNET_ID_MAX_LENGTH);
            }
            else
            {
                if (VOS_TRUE == CNAS_HSM_IsSubnetEqual(pstSessionCloseInfo->aucSubnet,
                                                       aucCurrSubnet))
                {
                    pstSessionCloseInfo->ucCount++;
                }
                else
                {
                    NAS_MEM_SET_S(pstSessionCloseInfo, sizeof(CNAS_HSM_SESSION_CLOSE_INFO_STRU), 0x00, sizeof(CNAS_HSM_SESSION_CLOSE_INFO_STRU));

                    pstSessionCloseInfo->ucCount++;

                    NAS_MEM_CPY_S(pstSessionCloseInfo->aucSubnet,
                                  sizeof(pstSessionCloseInfo->aucSubnet),
                                  aucCurrSubnet,
                                  CNAS_HSM_SUBNET_ID_MAX_LENGTH);

                }
            }
        }
    }
    else
    {
        NAS_MEM_SET_S(pstSessionCloseInfo,
                      sizeof(CNAS_HSM_SESSION_CLOSE_INFO_STRU),
                      0x00,
                      sizeof(CNAS_HSM_SESSION_CLOSE_INFO_STRU));
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_ClearRelativeCtx_PreProc
Description     :   异常场景下清除相关的上下文信息，比如停掉相关定时器，发送session_end_ntf,清理相关
                    全局变量等
Input parameters:   VOS_VOID
Outout parameters:  None
Return Value    :   VOS_VOID;

Modify History  :
1)  Date           : 2015-12-12
    Author         : m00312079
    Modify content : Create
*****************************************************************************/
VOS_VOID CNAS_HSM_ClearRelativeCtx_PreProc(VOS_VOID)
{
    CNAS_HSM_SS_ID_ENUM_UINT32                              enCurrSubState;

    enCurrSubState      = CNAS_HSM_GetCurrSubState();

    CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_KEEP_ALIVE_RSP);
    CNAS_HSM_VoteEnterSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_KEEP_ALIVE_PROCEDURE);

    CNAS_HSM_VoteEnterSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_UATI_REQ_PROCEDURE);

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_MO_KEEP_ALIVE_WAIT_SNP_DATA_CNF, 0))
    {
         CNAS_HSM_StopTimer(TI_CNAS_HSM_MO_KEEP_ALIVE_WAIT_SNP_DATA_CNF);

         CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_MO_KEEP_ALIVE);
    }

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_MT_KEEP_ALIVE_WAIT_SNP_DATA_CNF, 0))
    {
         CNAS_HSM_StopTimer(TI_CNAS_HSM_MT_KEEP_ALIVE_WAIT_SNP_DATA_CNF);

         CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_MT_KEEP_ALIVE);
    }

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_HARDWARE_ID_RSP_WAIT_SNP_DATA_CNF, 0))
    {
         CNAS_HSM_StopTimer(TI_CNAS_HSM_HARDWARE_ID_RSP_WAIT_SNP_DATA_CNF);

         CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_HARD_ID);
    }

    if ((CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF, 0))
     && (CNAS_HSM_SS_SESSION_DEACT_WAIT_SESSION_CLOSE_SNP_DATA_CNF != enCurrSubState))
    {
        CNAS_HSM_StopTimer(TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_SESSION_CLOSE);
    }

}


VOS_UINT32 CNAS_HSM_RcvTiUatiCmplWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvTiUatiCompleteWaitSnpDataCnfExpired_PreProc: timer out");

    CNAS_HSM_ResetUatiCompleteRetryTimes();

    CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_VOID CNAS_HSM_RcvUatiCmplSnpDataCnf_PreProc(
    CTTF_HRPD_SNP_RSLT_ENUM_UINT32                          enSnpDataCnfRslt,
    CTTF_HRPD_SNP_DATA_FAIL_REASON_ENUM_UINT32              enSnpDataCnfFailReason
)
{
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;

    enConvertedCasStatus     = CNAS_HSM_GetHrpdConvertedCasStatus();

    if (CTTF_HRPD_SNP_RLST_SUCC == enSnpDataCnfRslt)
    {
        CNAS_HSM_ResetUatiCompleteRetryTimes();

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);

        return;
    }

    /* 失败原因为CAN_NOT_TX和GENERIC_ERROR                                -- 不再重发
        失败原因为SLP_RESET和AC_CHANNEL_NOT_EXIST                          -- 重发
        失败原因为CONN_CLOSE和RELEASE_ALL，若CNAS维护的CAS状态为INIT       --不再重发
        失败原因为CONN_CLOSE和RELEASE_ALL，若CNAS维护的CAS状态为IDLE或CONN --重发      */
    switch (enSnpDataCnfFailReason)
    {
        case CTTF_HRPD_SNP_DATA_FAIL_REASON_CAN_NOT_TX:
        case CTTF_HRPD_SNP_DATA_FAIL_REASON_GENERIC_ERROR:

            CNAS_HSM_ResetUatiCompleteRetryTimes();

            CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

            CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);

            break;

        case CTTF_HRPD_SNP_DATA_FAIL_REASON_SLP_RESET:
        case CTTF_HRPD_SNP_DATA_FAIL_REASON_AC_CHANNEL_NOT_EXIST:

            if (CNAS_HSM_UAIT_COMPLETE_MAX_RETRY_CNT <= CNAS_HSM_GetUatiCompleteRetryTimes())
            {
                CNAS_HSM_ResetUatiCompleteRetryTimes();

                CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

                CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
            }
            else
            {
                CNAS_HSM_SndUatiCmplMsg();

                CNAS_HSM_IncreaseUatiCompleteRetryTimes();
            }

            break;

       case CTTF_HRPD_SNP_DATA_FAIL_REASON_CONN_CLOSE:
       case CTTF_HRPD_SNP_DATA_FAIL_REASON_RELEASE_ALL:

            if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus)
            {
                CNAS_HSM_ResetUatiCompleteRetryTimes();

                CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

                CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
            }
            else if ((CNAS_HSM_HRPD_CAS_STATUS_ENUM_IDLE == enConvertedCasStatus)
                  || (CNAS_HSM_HRPD_CAS_STATUS_ENUM_CONN == enConvertedCasStatus))
            {
                if (CNAS_HSM_UAIT_COMPLETE_MAX_RETRY_CNT <= CNAS_HSM_GetUatiCompleteRetryTimes())
                {
                    CNAS_HSM_ResetUatiCompleteRetryTimes();

                    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

                    CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
                }
                else
                {
                    CNAS_HSM_SndUatiCmplMsg();

                    CNAS_HSM_IncreaseUatiCompleteRetryTimes();
                }

            }
            else
            {
                /* CNAS维护的CAS状态为BUTT, 不作处理 */
            }

            break;

      default:

            CNAS_HSM_ResetUatiCompleteRetryTimes();

            CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

            CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);

            return;

    }

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



