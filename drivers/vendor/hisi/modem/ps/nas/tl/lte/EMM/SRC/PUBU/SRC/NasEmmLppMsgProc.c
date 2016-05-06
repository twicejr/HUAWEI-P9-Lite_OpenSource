





/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "PsCommonDef.h"
#include    "NasEmmLppMsgProc.h"
#include    "NasLmmPubMOsa.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmMrrcPubInterface.h"
#include    "NasLmmPubMOm.h"
#include    "NasEmmAttDetInclude.h"
#if (FEATURE_LPP == FEATURE_ON)
#include    "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMLPPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMLPPMSGPROC_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_VOID NAS_EMM_SendLppEstCnf
(
   LMM_LPP_EST_RESULT_ENUM_UINT32      enEstCnfRst
)
{
    LMM_LPP_EST_CNF_STRU               *pstEmmLppEstCnf = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendLppEstCnf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendLppEstCnf_ENUM, LNAS_LPP_Func_Enter);

    pstEmmLppEstCnf   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_EST_CNF_STRU));
    if (NAS_EMM_NULL_PTR == pstEmmLppEstCnf)
    {
        return;
    }

    NAS_EMM_LPP_MSG_HEADER(pstEmmLppEstCnf,
                           (sizeof(LMM_LPP_EST_CNF_STRU)-
                            NAS_EMM_LEN_VOS_MSG_HEADER));

    pstEmmLppEstCnf->ulMsgId  = ID_LMM_LPP_EST_CNF;

    pstEmmLppEstCnf->ulOpId = 0;

    pstEmmLppEstCnf->ulEstRst = enEstCnfRst;

    NAS_LMM_SEND_MSG(pstEmmLppEstCnf);
}


VOS_VOID NAS_EMM_SendLppDataCnf
(
    LMM_LPP_SEND_RSLT_ENUM_UINT32       enDataCnfRst,
    VOS_UINT32                          ulOpId
)
{
    LMM_LPP_DATA_CNF_STRU               *pstEmmLppDataCnf = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendLppDataCnf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendLppDataCnf_ENUM, LNAS_LPP_Func_Enter);

    pstEmmLppDataCnf   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_DATA_CNF_STRU));
    if (NAS_EMM_NULL_PTR == pstEmmLppDataCnf)
    {
        return;
    }

    NAS_EMM_LPP_MSG_HEADER(pstEmmLppDataCnf,
                           (sizeof(LMM_LPP_DATA_CNF_STRU)-
                            NAS_EMM_LEN_VOS_MSG_HEADER));

    pstEmmLppDataCnf->ulMsgId  = ID_LMM_LPP_DATA_CNF;

    pstEmmLppDataCnf->ulOpId = ulOpId;

    pstEmmLppDataCnf->enDataCnfRst = enDataCnfRst;

    NAS_LMM_SEND_MSG(pstEmmLppDataCnf);
}


VOS_VOID NAS_EMM_SndLppStartInd(  VOS_VOID )
{
    LMM_LPP_START_IND_STRU               *pstEmmLppStartInd = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendLppStartInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndLppStartInd_ENUM, LNAS_LPP_Func_Enter);

    pstEmmLppStartInd   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_START_IND_STRU));
    if (NAS_EMM_NULL_PTR == pstEmmLppStartInd)
    {
        return;
    }

    NAS_EMM_LPP_MSG_HEADER(pstEmmLppStartInd,
                           (sizeof(LMM_LPP_START_IND_STRU)-
                            NAS_EMM_LEN_VOS_MSG_HEADER));

    pstEmmLppStartInd->ulMsgId  = ID_LMM_LPP_START_IND;

    NAS_LMM_SEND_MSG(pstEmmLppStartInd);
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndLppStopInd
 Description     : 通知LPP系统关机
 Input           :
 Output          : None
 Return          : VOS_VOID
 History         : lifuxin  00253982   2015-08-026  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SndLppStopInd(  VOS_VOID )
{
    LMM_LPP_STOP_IND_STRU               *pstEmmLppStopInd = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SndLppStopInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndLppStopInd_ENUM, LNAS_LPP_Func_Enter);

    pstEmmLppStopInd   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_STOP_IND_STRU));
    if (NAS_EMM_NULL_PTR == pstEmmLppStopInd)
    {
        return;
    }

    NAS_EMM_LPP_MSG_HEADER(pstEmmLppStopInd,
                           (sizeof(LMM_LPP_STOP_IND_STRU)-
                            NAS_EMM_LEN_VOS_MSG_HEADER));

    pstEmmLppStopInd->ulMsgId  = ID_LMM_LPP_STOP_IND;

    NAS_LMM_SEND_MSG(pstEmmLppStopInd);
}


VOS_VOID NAS_EMM_SndLppCnf
(
    VOS_UINT32                          ulMsgId,
    LMM_LPP_EST_RESULT_ENUM_UINT32      ulEstRst,
    LMM_LPP_SEND_RSLT_ENUM_UINT32       enDataCnfRst,
    VOS_UINT32                          ulOpId
)
{
    if(ID_LPP_LMM_EST_REQ == ulMsgId)
    {
        NAS_EMM_SendLppEstCnf(ulEstRst);
    }
    else
    {
        NAS_EMM_SendLppDataCnf(enDataCnfRst, ulOpId);
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_SomeStateRcvLppMsgCommProc
 Description     :
                   REG.NORMAL_SERVICE
                   REG.ATTEMPTING_TO_UPDATE_MM
 Input           : ulMsgId------------------消息ID
                   ulOpId-------------------OPID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin 00253982      2015-08-01  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_SomeStateRcvLppMsgCommProc
(
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulOpId
)
{
    if (EMM_MS_DEREG == NAS_EMM_CUR_MAIN_STAT)
    {
        if (EMM_SS_DEREG_NO_IMSI == NAS_EMM_CUR_SUB_STAT)
        {
            NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_USIM_PS_INVALID,
                                LMM_LPP_SEND_RSLT_FAIL_USIM_PS_INVALID, ulOpId);
            return  NAS_LMM_MSG_HANDLED;
        }

        if ((EMM_SS_DEREG_ATTEMPTING_TO_ATTACH == NAS_EMM_CUR_SUB_STAT)
            && (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411)))
        {
            NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_3411_RUNNING,
                                LMM_LPP_SEND_RSLT_FAIL_3411_RUNNING, ulOpId);
            return  NAS_LMM_MSG_HANDLED;
        }

        if ((EMM_SS_DEREG_ATTEMPTING_TO_ATTACH == NAS_EMM_CUR_SUB_STAT)
            && (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402)))
        {
            NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_3402_RUNNING,
                                LMM_LPP_SEND_RSLT_FAIL_3402_RUNNING, ulOpId);
            return  NAS_LMM_MSG_HANDLED;
        }

        if (NAS_EMM_AUTO_ATTACH_NOT_ALLOW == NAS_EMM_GetPsAttachAllowFlg())
        {
            NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_PS_ATTACH_NOT_ALLOWED,
                                LMM_LPP_SEND_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED, ulOpId);
            return  NAS_LMM_MSG_HANDLED;
        }

        NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_PS_NOT_ATTACHED,
                            LMM_LPP_SEND_RSLT_FAIL_PS_NOT_ATTACHED, ulOpId);

        return NAS_LMM_MSG_HANDLED;
    }

    if (EMM_MS_REG == NAS_EMM_CUR_MAIN_STAT)
    {
        if (EMM_SS_REG_WAIT_ACCESS_GRANT_IND == NAS_EMM_CUR_SUB_STAT)
        {
            NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_ACCESS_BARRED,
                                LMM_LPP_SEND_RSLT_FAIL_ACCESS_BARRED, ulOpId);
            return  NAS_LMM_MSG_HANDLED;
        }

        if ((EMM_SS_REG_ATTEMPTING_TO_UPDATE == NAS_EMM_CUR_SUB_STAT)
            && (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411)))
        {
            NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_3411_RUNNING,
                                LMM_LPP_SEND_RSLT_FAIL_3411_RUNNING, ulOpId);
            return  NAS_LMM_MSG_HANDLED;
        }

        if ((EMM_SS_REG_ATTEMPTING_TO_UPDATE == NAS_EMM_CUR_SUB_STAT)
            && (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402)))
        {
            NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_3402_RUNNING,
                                LMM_LPP_SEND_RSLT_FAIL_3402_RUNNING, ulOpId);
            return  NAS_LMM_MSG_HANDLED;
        }

        NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_STATE_CANNOT_SERVICE,
                            LMM_LPP_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST, ulOpId);

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_SndLppCnf(   ulMsgId, LMM_LPP_EST_RESULT_FAIL_OTHERS,
                        LMM_LPP_SEND_RSLT_OHTERS, ulOpId);

    return NAS_LMM_MSG_HANDLED;
}



VOS_UINT32 NAS_EMM_RcvLppMsgEstReq(MsgBlock *  pMsg)
{
    VOS_UINT32                          ulCurEmmStat;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_RcvLppMsgEstReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvLppMsgEstReq_ENUM, LNAS_LPP_Func_Enter);
    TLPS_PRINT2LAYER_WARNING1(NAS_EMM_RcvLppMsgEstReq_ENUM, LNAS_LPP_MainStat, NAS_EMM_CUR_MAIN_STAT);
    TLPS_PRINT2LAYER_WARNING1(NAS_EMM_RcvLppMsgEstReq_ENUM, LNAS_LPP_SubStat, NAS_EMM_CUR_SUB_STAT);
    TLPS_PRINT2LAYER_WARNING1(NAS_EMM_RcvLppMsgEstReq_ENUM, LNAS_LPP_ConnStat, NAS_EMM_GetConnState());

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);

    if (NAS_EMM_SUCC == NAS_EMM_CheckLcsOrLppMsgNeedHighPrioStore())
    {
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_RcvLppMsgEstReq_ENUM, LNAS_LPP_HighPrioStore);
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    if (NAS_EMM_SUCC == NAS_EMM_CheckLcsOrLppMsgNeedLowPrioStore())
    {
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_RcvLppMsgEstReq_ENUM, LNAS_LPP_LowPrioStore);
        return NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    /* REG + EMM_SS_REG_NORMAL_SERVICE, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM*/
    if ((ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
        || (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
        || (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF)))
    {

        if((NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
            || (NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()))
        {
            NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_SUCC);

            return NAS_LMM_MSG_HANDLED;
        }

        return NAS_LMM_MSG_DISCARD;
    }
    else
    {
        return NAS_EMM_SomeStateRcvLppMsgCommProc(  ID_LPP_LMM_EST_REQ,
                                                    NAS_LPP_LMM_OPID_INVALID);
    }
}


VOS_VOID    NAS_EMM_SendMrrcDataReq_LppData(LPP_LMM_DATA_REQ_STRU *pstLppLmmDataReq)
{
    NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU  *pstUplinkMsg;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_RcvLppMsgEstReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMrrcDataReq_LppData_ENUM, LNAS_LPP_Func_Enter);

    pstUplinkMsg = (NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU));
    if(NAS_EMM_NULL_PTR == pstUplinkMsg)
    {
        return  ;
    }

    NAS_LMM_MEM_SET_S(  pstUplinkMsg,
                        sizeof(NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU),
                        0,
                        sizeof(NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU));

    pstUplinkMsg->ucContainerType = NAS_EMM_LPP_MSG;

    pstUplinkMsg->stContainer.usMsgLen = (VOS_UINT16)(pstLppLmmDataReq->stLppMsg.ulLppMsgSize);

    NAS_LMM_MEM_CPY_S(  pstUplinkMsg->stContainer.aucMsg,
                        NAS_EMM_CN_MSGCON_MAX_LEN,
                        pstLppLmmDataReq->stLppMsg.aucLppMsg,
                        pstUplinkMsg->stContainer.usMsgLen);

    pstUplinkMsg->bitOpAdditionalInfo = NAS_EMM_BIT_SLCT;
    pstUplinkMsg->stAdditionalInfo.ucMsgLen = 4;

    NAS_LMM_MEM_CPY_S(  pstUplinkMsg->stAdditionalInfo.aucMsg,
                        256,
                        &(pstLppLmmDataReq->ulSessionId),
                        4);

    NAS_EMM_SendMrrcDataReq_UplinkGenericNasTransport(  pstUplinkMsg,
                                                        pstLppLmmDataReq->ulOpId,
                                                        0);
    NAS_LMM_MEM_FREE(pstUplinkMsg);
    return;
}


VOS_UINT32 NAS_EMM_RcvLppMsgDataReq(MsgBlock *  pMsg)
{
    VOS_UINT32                          ulCurEmmStat;
    LPP_LMM_DATA_REQ_STRU              *pstLppLmmDataReq = NAS_EMM_NULL_PTR;

    pstLppLmmDataReq = (LPP_LMM_DATA_REQ_STRU*)pMsg;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_RcvLppMsgDataReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RcvLppMsgDataReq_ENUM, LNAS_LPP_Func_Enter);
    TLPS_PRINT2LAYER_WARNING1(NAS_EMM_RcvLppMsgDataReq_ENUM, LNAS_LPP_MainStat, NAS_EMM_CUR_MAIN_STAT);
    TLPS_PRINT2LAYER_WARNING1(NAS_EMM_RcvLppMsgDataReq_ENUM, LNAS_LPP_SubStat, NAS_EMM_CUR_SUB_STAT);
    TLPS_PRINT2LAYER_WARNING1(NAS_EMM_RcvLppMsgDataReq_ENUM, LNAS_LPP_ConnStat, NAS_EMM_GetConnState());

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);
    if (NAS_EMM_SUCC == NAS_EMM_CheckLcsOrLppMsgNeedHighPrioStore())
    {
        return NAS_LMM_STORE_HIGH_PRIO_MSG;
    }

    if (NAS_EMM_SUCC == NAS_EMM_CheckLcsOrLppMsgNeedLowPrioStore())
    {
        return NAS_LMM_STORE_LOW_PRIO_MSG;
    }

    /* REG + EMM_SS_REG_NORMAL_SERVICE, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM*/
    if ((ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE))
        || (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM))
        || (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF)))
    {
        if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState())
          ||(NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
        {
            NAS_EMM_SendMrrcDataReq_LppData(pstLppLmmDataReq);
        }
        else
        {
            NAS_EMM_SendLppDataCnf( LMM_LCS_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST,
                                    pstLppLmmDataReq->ulOpId);
        }

        return NAS_LMM_MSG_HANDLED;
    }
    else
    {
        return NAS_EMM_SomeStateRcvLppMsgCommProc(  ID_LPP_LMM_DATA_REQ,
                                                    pstLppLmmDataReq->ulOpId);
    }
}


/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_EMM_CompUplinkGenericNasTransportMsg(VOS_UINT8 *pMsgBuf,
                                                  VOS_UINT32 *pulIndex,
                                                  const NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU *pMsgStruct)
{
    VOS_UINT32 ulIndex = 0;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_CompUplinkGenericNasTransportMsg enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CompUplinkGenericNasTransportMsg_ENUM,LNAS_ENTRY);

    if ((NAS_LMM_NULL == pMsgBuf) || (NAS_LMM_NULL == pMsgStruct))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_CompUplinkGenericNasTransportMsg: invalid input!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_CompUplinkGenericNasTransportMsg_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* encode PD and Security header type */
    pMsgBuf[ulIndex++] = EMM_CN_MSG_PD_EMM;

    /* encode message type */
    pMsgBuf[ulIndex++] = NAS_EMM_CN_MT_UPLINK_GENERIC_NAS_TRANSPORT;

    /* encode Generic message container type */
    pMsgBuf[ulIndex++] = pMsgStruct->ucContainerType;

    /* encode Generic message container */
    pMsgBuf[ulIndex++] = (pMsgStruct->stContainer.usMsgLen >> NAS_EMM_MOVEMENT_8_BITS) & NAS_EMM_FIRST_BYTE_F;
    pMsgBuf[ulIndex++] = (pMsgStruct->stContainer.usMsgLen) & NAS_EMM_FIRST_BYTE_F;/* [false alarm]:代码保证了不会越界 */

    NAS_LMM_MEM_CPY_S(  pMsgBuf + ulIndex,
                        pMsgStruct->stContainer.usMsgLen,
                        pMsgStruct->stContainer.aucMsg,
                        pMsgStruct->stContainer.usMsgLen);

    ulIndex += pMsgStruct->stContainer.usMsgLen;

    /* encode Additional Information if necessary */
    if (pMsgStruct->bitOpAdditionalInfo)
    {
        /* encode IEI of Additional Information */
        pMsgBuf[ulIndex++] = NAS_EMM_ADDITIONAL_INFO_IEI;/* [false alarm]:代码保证了不会越界 */

        /* encode length of Additional Information */
        pMsgBuf[ulIndex++] = pMsgStruct->stAdditionalInfo.ucMsgLen;/* [false alarm]:代码保证了不会越界 */

        /* copy content of Additional Information */

        NAS_LMM_MEM_CPY_S(  pMsgBuf + ulIndex,
                            pMsgStruct->stAdditionalInfo.ucMsgLen,
                            pMsgStruct->stAdditionalInfo.aucMsg,
                            pMsgStruct->stAdditionalInfo.ucMsgLen);

        ulIndex += pMsgStruct->stAdditionalInfo.ucMsgLen;
    }

    *pulIndex = ulIndex;
}


VOS_VOID NAS_EMM_SendMrrcDataReq_UplinkGenericNasTransport
(
    const NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU    *pstUplinkMsg,
    VOS_UINT32                                          ulEmmLppOrSsOpId,
    VOS_UINT32                                          ulLppSsFlag
)
{
    NAS_EMM_MRRC_DATA_REQ_STRU *pIntraMsg = NAS_LMM_NULL;
    VOS_UINT32 ulDataReqMsgLenNoHeader = 0;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SendMrrcDataReq_LppData enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMrrcDataReq_UplinkGenericNasTransport_ENUM,LNAS_ENTRY);

    if (NAS_LMM_NULL == pstUplinkMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendMrrcDataReq_LppData: invalid input");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMrrcDataReq_UplinkGenericNasTransport_ENUM,LNAS_NULL_PTR);
        return;
    }

    pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);
    if (NAS_LMM_NULL == pIntraMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendMrrcDataReq_LppData: alloc msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMrrcDataReq_UplinkGenericNasTransport_ENUM,LNAS_FAIL);
        return;
    }

    NAS_EMM_CompUplinkGenericNasTransportMsg(pIntraMsg->stNasMsg.aucNasMsg,
                                             &(pIntraMsg->stNasMsg.ulNasMsgSize),
                                             pstUplinkMsg);

    ulDataReqMsgLenNoHeader = NAS_EMM_CountMrrcDataReqLen(pIntraMsg->stNasMsg.ulNasMsgSize);
    if (NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqMsgLenNoHeader)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendMrrcDataReq_LppData: size too long!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMrrcDataReq_UplinkGenericNasTransport_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_MEM_FREE(pIntraMsg);
        return;
    }

    EMM_COMP_MM_MSG_HEADER(pIntraMsg, ulDataReqMsgLenNoHeader);

    pIntraMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    pIntraMsg->enEstCaue    = LRRC_LNAS_EST_CAUSE_MO_DATA;
    pIntraMsg->enCallType   = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
    pIntraMsg->enEmmMsgType = NAS_EMM_NAS_UPLINK_GENERIC_NAS_TRANSPORT;
    pIntraMsg->enDataCnf    = LRRC_LMM_DATA_CNF_NEED;
    pIntraMsg->ulEmmLppOrSsOpId = ulEmmLppOrSsOpId;
    pIntraMsg->ulLppSsFlag  = ulLppSsFlag;

    /*report air message UPLINK GENERIC NAS TRANSPORT*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT,(NAS_MSG_STRU *)&(pIntraMsg->stNasMsg));

    /*report key event UPLINK GENERIC NAS TRANSPORT*/
    NAS_LMM_SendOmtKeyEvent(EMM_OMT_KE_EMM_UPLINK_GENERIC_NAS_TRANSPORT);

    NAS_EMM_SndUplinkNasMsg(pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);

}

/*****************************************************************************
 Function Name   : NAS_EMM_SndUplinkGenericTransportSuccProc
 Description     : UplinkGenericTransport发送成功的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : lifuxin  00253982   2015-07-17  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_SndUplinkGenericTransportSuccProc(VOS_VOID* pMsg)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf    = NAS_EMM_NULL_PTR;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData   = NAS_EMM_NULL_PTR;

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndUplinkGenericTransportSuccProc_ENUM, LNAS_LPP_Func_Enter);

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);
    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }

    if (0 == pEmmMrrcMgmtData->ulLppSsFlag)
    {
        NAS_EMM_SendLppDataCnf( LMM_LPP_SEND_RSLT_SUCCESS,
                                pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
    }
    else
    {
        NAS_EMM_SndLcsDataCnf(   LMM_LCS_SEND_RSLT_SUCCESS,
                                pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
    }

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndUplinkGenericTransportFailProc
 Description     : Uplink Generic Transport发送失败的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : lifuxin  00253982   2015-03-12  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_SndUplinkGenericTransportFailProc(VOS_VOID* pMsg, VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf    = NAS_EMM_NULL_PTR;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData   = NAS_EMM_NULL_PTR;

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SndUplinkGenericTransportFailProc!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndUplinkGenericTransportFailProc_ENUM, LNAS_LPP_Func_Enter);

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);
    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }

    *pulIsDelBuff = VOS_TRUE;

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_TRUE;
            *pulIsDelBuff = VOS_FALSE;

            break;

        case LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL:
        case LRRC_LMM_SEND_RSLT_FAILURE_CTRL_NOT_CONN:

            if (0 == pEmmMrrcMgmtData->ulLppSsFlag)
            {
                NAS_EMM_SendLppDataCnf( LMM_LPP_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST,
                                        pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
            }
            else
            {
                NAS_EMM_SndLcsDataCnf(   LMM_LCS_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST,
                                        pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
            }

            break;

        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
        case LRRC_LMM_SEND_RSLT_NO_RF:

            if (0 == pEmmMrrcMgmtData->ulLppSsFlag)
            {
                NAS_EMM_SendLppDataCnf( LMM_LPP_SEND_RSLT_LOW_LAYER_FAIL,
                                        pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
            }
            else
            {
                NAS_EMM_SndLcsDataCnf(   LMM_LCS_SEND_RSLT_FAIL_LOW_LAYER,
                                        pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
            }

            break;

        default:
            break;
    }

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendLppCellChangeInd
 Description     : 当LRRC驻留的物理小区ID发生变化的时候，发送给LPP
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         : lifuxin  00253982   2015-07-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SendLppCellChangeInd
(
    VOS_UINT32          ulCellId,
    VOS_UINT32          ulEarfcn,
    VOS_UINT16          usPhyCellId,
    VOS_UINT8          *pucPlmnId
)
{
    LMM_LPP_CELL_CHANGE_IND             *pstEmmLppCellChangeInd = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendLppCellChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendLppCellChangeInd_ENUM, LNAS_LPP_Func_Enter);

    /*申请消息内存*/
    pstEmmLppCellChangeInd   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_CELL_CHANGE_IND));
    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pstEmmLppCellChangeInd)
    {
        return;
    }

    /*构造ID_LMM_LPP_CELL_CHANGE_IND消息*/
    /*填充消息头*/
    NAS_EMM_LPP_MSG_HEADER(pstEmmLppCellChangeInd,
                           (sizeof(LMM_LPP_CELL_CHANGE_IND)-
                            NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pstEmmLppCellChangeInd->ulMsgId  = ID_LMM_LPP_CELL_CHANGE_IND;

    /*填充小区ID*/
    pstEmmLppCellChangeInd->ulCellId        = ulCellId;
    pstEmmLppCellChangeInd->ulEarfcn        = ulEarfcn;
    pstEmmLppCellChangeInd->usPhyCellId     = usPhyCellId;
    pstEmmLppCellChangeInd->aucPlmnId[0]    = pucPlmnId[0];
    pstEmmLppCellChangeInd->aucPlmnId[1]    = pucPlmnId[1];
    pstEmmLppCellChangeInd->aucPlmnId[2]    = pucPlmnId[2];

    /*向LPP发送ID_LMM_LPP_CELL_CHANGE_IND消息*/
    NAS_LMM_SEND_MSG(pstEmmLppCellChangeInd);
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendLppRelInd
 Description     : 当LRRC释放链路之后，也需要透传给LPP，方便起测量业务的连续性
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         : lifuxin  00253982   2015-07-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SendLppRelInd()
{
    LMM_LPP_REL_IND_STRU                *pstEmmLppRelInd = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendLppRelInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendLppRelInd_ENUM, LNAS_LPP_Func_Enter);

    /*申请消息内存*/
    pstEmmLppRelInd   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_REL_IND_STRU));
    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pstEmmLppRelInd)
    {
        return;
    }

    /*构造ID_LMM_LPP_REL_IND消息*/
    /*填充消息头*/
    NAS_EMM_LPP_MSG_HEADER(pstEmmLppRelInd,
                           (sizeof(LMM_LPP_REL_IND_STRU)-
                            NAS_EMM_LEN_VOS_MSG_HEADER));

    /*填充消息ID*/
    pstEmmLppRelInd->ulMsgId  = ID_LMM_LPP_REL_IND;

    /*向LPP发送ID_LMM_LPP_REL_IND消息*/
    NAS_LMM_SEND_MSG(pstEmmLppRelInd);
}

#endif

/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

