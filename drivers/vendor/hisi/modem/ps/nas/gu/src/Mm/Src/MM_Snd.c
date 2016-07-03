

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "NasMmlMsgProc.h"
#include        "GmmExt.h"
#include "NasUsimmApi.h"

#if (FEATURE_ON == FEATURE_LTE)
#include        "MmLmmInterface.h"
#endif
#include "NasUtranCtrlInterface.h"

#include "NasMmlLib.h"
#include "MmCcInterface.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_SND_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */


VOS_VOID MM_ReportM2NOtaMsg(VOS_UINT32 ulSize, VOS_UINT8 *pData)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;
    /*调用NAS_EventReport需要构造NAS_MSG_STRU*/
    NAS_MSG_STRU        *pNasMsg = VOS_NULL_PTR;
    VOS_UINT32          ulNasMsgLen;

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "MM_ReportM2NOtaMsg");

    if((0 == ulSize)||(VOS_NULL_PTR == pData))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "MM_ReportM2NOtaMsg:WARNING: Invalid para!");
        return;
    }


    if ( ( MM_IE_PD_MM_MSG != (pData[0] & 0x0f))
      && ( MM_IE_MSG_TYPE_PAGING_RSP != (pData[1])))
    {
        return;
    }

    if(ulSize > 4)
    {
        ulNasMsgLen = (sizeof(NAS_MSG_STRU) + ulSize) - 4;
    }
    else
    {
        ulNasMsgLen = sizeof(NAS_MSG_STRU);
    }

    /*MM模块MS给NET的空口消息不是NAS_MSG_STRU类型，需要构造该结构体*/
    pNasMsg = (NAS_MSG_STRU *)MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      ulNasMsgLen,
                                      WUEPS_MEM_NO_WAIT
                                       );
    if(VOS_NULL_PTR == pNasMsg)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "MM_ReportM2NOtaMsg:ERROR: pNasMsg is NULL");
    }
    else
    {
        PS_MEM_SET((VOS_VOID *)pNasMsg, 0x00, ulNasMsgLen);

        pNasMsg->ulNasMsgSize = ulSize;

        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "MM_ReportM2NOtaMsg:NORMAL: Msg Type is ", pData[1]);

        switch(pData[1])
        {
           case MM_IE_MSG_TYPE_IMSI_DETACH_INDICATION:
               usNasOtaMsyId = NAS_OTA_MSG_IMSI_DETACH_INDICATION;
               break;

           case MM_IE_MSG_TYPE_LU_REQUEST:
               usNasOtaMsyId = NAS_OTA_MSG_LOCATION_UPDATE_REQUEST;
               break;

           case MM_IE_MSG_TYPE_AUTH_RES:
               usNasOtaMsyId = NAS_OTA_MSG_AUTH_RSP;
               break;

           case MM_IE_MSG_TYPE_AUTH_FAIL:
               usNasOtaMsyId = NAS_OTA_MSG_AUTH_FAILURE;
               break;

           case MM_IE_MSG_TYPE_ID_RES:
               usNasOtaMsyId = NAS_OTA_MSG_ID_RES;
               break;

           case MM_IE_MSG_TYPE_TMSI_REALLOC_CPL:
               usNasOtaMsyId = NAS_OTA_MSG_TMSI_REALLOC_CPL;
               break;

           case MM_IE_MSG_TYPE_CM_SERV_REQ:
               usNasOtaMsyId = NAS_OTA_MSG_CM_SERV_REQUEST;
               break;

           case MM_IE_MSG_TYPE_CM_SERV_ABO:
               usNasOtaMsyId = NAS_OTA_MSG_CM_SERV_ABORT;
               break;

           case MM_IE_MSG_TYPE_PAGING_RSP:
               usNasOtaMsyId = NAS_OTA_MSG_PAGING_RSP;
               break;

           case MM_IE_MSG_TYPE_REEST_REQ:
               usNasOtaMsyId = NAS_OTA_MSG_REEST_REQ;
               break;

           case MM_IE_MSG_TYPE_MM_STA:
               usNasOtaMsyId = NAS_OTA_MSG_MM_STA_M2N;
               break;

           default:
               PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "MM_ReportM2NOtaMsg:WARNING: Invalid Msg id");
               MM_MEM_FREE(VOS_MEMPOOL_INDEX_MM, pNasMsg);
               return;
        }

        PS_MEM_CPY((VOS_VOID *)(pNasMsg->aucNasMsg), pData, pNasMsg->ulNasMsgSize);

        NAS_SendAirMsgToOM(WUEPS_PID_MM, usNasOtaMsyId, NAS_OTA_DIRECTION_UP, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);


        MM_MEM_FREE(VOS_MEMPOOL_INDEX_MM, pNasMsg);
    }
}






VOS_VOID Mm_SndMmcStartCnf()
{
    MMCMM_START_CNF_STRU                  *pMmcStartCnf     = VOS_NULL_PTR;     /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pMmcStartCnf    = (MMCMM_START_CNF_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_START_CNF_STRU));
    if ( VOS_NULL_PTR == pMmcStartCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "Mm_SndMmcStartCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pMmcStartCnf->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMmcStartCnf->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pMmcStartCnf->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMmcStartCnf->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pMmcStartCnf->MsgHeader.ulMsgName       = MMCMM_START_CNF;                      /* 消息名称                                 */
    pMmcStartCnf->MsgHeader.ulLength
        = sizeof(MMCMM_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pMmcStartCnf);

    return;

}



VOS_VOID Mm_SndMmcInfoInd(VOS_VOID)
{
    MMCMM_INFO_IND_STRU                   *pMmcInfoInd;

    /* 当前无可用信息直接返回不用通知MMC */
    if ( (VOS_FALSE == g_MmMsgMmInfo.ucLocalTmZoneFlg)
      && (VOS_FALSE == g_MmMsgMmInfo.ucUnvrslTmAndLocalTmZoneFlg)
      && (VOS_FALSE == g_MmMsgMmInfo.ucNWDyLitSavTmFlg)
      && (VOS_FALSE == g_MmMsgMmInfo.ucFulNamFrNWFlg)
      && (VOS_FALSE == g_MmMsgMmInfo.ucShortNamFrNWFlg))
    {
        NAS_INFO_LOG(WUEPS_PID_MM, "Mm_SndMmcInfoInd: No userful info");
        return;
    }

    /* 申请消息内存分配 */
    pMmcInfoInd     = (MMCMM_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pMmcInfoInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "Mm_SndMmcInfoInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    PS_MEM_SET(&pMmcInfoInd->stMmInfo, 0, sizeof(NAS_MM_INFO_IND_STRU));

    if (VOS_TRUE == g_MmMsgMmInfo.ucLocalTmZoneFlg)
    {
        pMmcInfoInd->stMmInfo.ucIeFlg |= NAS_MM_INFO_IE_LTZ;
        pMmcInfoInd->stMmInfo.cLocalTimeZone = g_MmMsgMmInfo.MmIeLocalTmZone.cTimeZone;
    }

    if (VOS_TRUE == g_MmMsgMmInfo.ucUnvrslTmAndLocalTmZoneFlg)
    {
        pMmcInfoInd->stMmInfo.ucIeFlg |= NAS_MM_INFO_IE_UTLTZ;
        pMmcInfoInd->stMmInfo.stUniversalTimeandLocalTimeZone.ucYear    = g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucYear;
        pMmcInfoInd->stMmInfo.stUniversalTimeandLocalTimeZone.ucMonth   = g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMonth;
        pMmcInfoInd->stMmInfo.stUniversalTimeandLocalTimeZone.ucDay     = g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucDay;
        pMmcInfoInd->stMmInfo.stUniversalTimeandLocalTimeZone.ucHour    = g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucHour;
        pMmcInfoInd->stMmInfo.stUniversalTimeandLocalTimeZone.ucMinute  = g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMinute;
        pMmcInfoInd->stMmInfo.stUniversalTimeandLocalTimeZone.ucSecond  = g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucSecond;
        pMmcInfoInd->stMmInfo.stUniversalTimeandLocalTimeZone.cTimeZone = g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.cTimeZone;
    }

    if (VOS_TRUE == g_MmMsgMmInfo.ucNWDyLitSavTmFlg)
    {
        pMmcInfoInd->stMmInfo.ucIeFlg |= NAS_MM_INFO_IE_DST;
        pMmcInfoInd->stMmInfo.ucDST = g_MmMsgMmInfo.MmIeNWDyLitSavTm.ucValue;
    }

    pMmcInfoInd->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMmcInfoInd->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pMmcInfoInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMmcInfoInd->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pMmcInfoInd->MsgHeader.ulMsgName       = MMCMM_INFO_IND;
    pMmcInfoInd->MsgHeader.ulLength
        = sizeof(MMCMM_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pMmcInfoInd);

    return;
}




VOS_VOID Mm_SndMmcCmSvcInd(
                       VOS_UINT32 ulCsServFlg                                        /* 输入参数CS域的服务标识                   */
                       )
{
    MMCMM_CM_SERVICE_IND_STRU             *pCmSvcInd;                    /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pCmSvcInd       = (MMCMM_CM_SERVICE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_CM_SERVICE_IND_STRU));
    if ( VOS_NULL_PTR == pCmSvcInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "Mm_SndMmcCmSvcInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pCmSvcInd->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pCmSvcInd->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pCmSvcInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCmSvcInd->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pCmSvcInd->MsgHeader.ulMsgName       = MMCMM_CM_SERVICE_IND;                 /* 消息名称                                 */
    pCmSvcInd->MsgHeader.ulLength
        = sizeof(MMCMM_CM_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pCmSvcInd->ulCsServFlg = ulCsServFlg;                                       /* 设置消息参数                             */

    pCmSvcInd->ulEmcFlg = MM_EMERGENCY_CALL_FALSE;
    if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
    {
        if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg)
        {
            pCmSvcInd->ulEmcFlg = MM_EMERGENCY_CALL_TRUE;

            if (MM_CS_SERV_NOT_EXIST == ulCsServFlg)
            {
                 /* 清除紧急呼叫存在标识 */
                 NAS_MML_SetCsEmergencyServiceFlg(VOS_FALSE);
            }

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_SndMmcCmSvcInd:INFO: PLMN search procedure start EMC!");
        }
    }

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pCmSvcInd);

    return;
}



VOS_VOID NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_ENUM_U32 enPlmnSearchType)
{
    MMCMM_PLMN_SEARCH_IND_STRU             *pstPlmnSearchInd;                    /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pstPlmnSearchInd  = (MMCMM_PLMN_SEARCH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_PLMN_SEARCH_IND_STRU));
    if ( VOS_NULL_PTR == pstPlmnSearchInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "Mm_SndMmcPlmnSearchInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstPlmnSearchInd->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstPlmnSearchInd->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstPlmnSearchInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstPlmnSearchInd->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstPlmnSearchInd->MsgHeader.ulMsgName       = MMCMM_PLMN_SEARCH_IND;    /* 消息名称 */
    pstPlmnSearchInd->MsgHeader.ulLength
        = sizeof(MMCMM_PLMN_SEARCH_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPlmnSearchInd->enPlmnSearchType          = enPlmnSearchType;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstPlmnSearchInd);

    return;
}



VOS_VOID NAS_MM_SndMmcCsfbAbortInd()
{
    MMCMM_CSFB_ABORT_IND_STRU          *pstPlmnSearchInd;                    /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pstPlmnSearchInd  = (MMCMM_CSFB_ABORT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_CSFB_ABORT_IND_STRU));
    if ( VOS_NULL_PTR == pstPlmnSearchInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndMmcCsfbAbortInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstPlmnSearchInd->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstPlmnSearchInd->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstPlmnSearchInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstPlmnSearchInd->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstPlmnSearchInd->MsgHeader.ulMsgName       = MMCMM_CSFB_ABORT_IND;    /* 消息名称 */
    pstPlmnSearchInd->MsgHeader.ulLength
        = sizeof(MMCMM_CSFB_ABORT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstPlmnSearchInd);

    return;
}



VOS_VOID Mm_SndMmcCmSvcRejInd(
                          VOS_UINT32 ulCause                                         /* 输入参数拒绝的原因值                     */
                          )
{
    MMCMM_CM_SERVICE_REJECT_IND_STRU      *pCmSvcRejInd;                 /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pCmSvcRejInd    = (MMCMM_CM_SERVICE_REJECT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_CM_SERVICE_REJECT_IND_STRU));
    if ( VOS_NULL_PTR == pCmSvcRejInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "Mm_SndMmcCmSvcRejInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pCmSvcRejInd->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pCmSvcRejInd->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pCmSvcRejInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCmSvcRejInd->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pCmSvcRejInd->MsgHeader.ulMsgName       = MMCMM_CM_SERVICE_REJECT_IND;          /* 消息名称                                 */
    pCmSvcRejInd->MsgHeader.ulLength
        = sizeof(MMCMM_CM_SERVICE_REJECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pCmSvcRejInd->ulCause = ulCause;                                            /* 设置消息参数                             */
    if ( NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR == ulCause )
    {
        pCmSvcRejInd->ulServiceStatus = MM_COM_SRVST_NORMAL_SERVICE;            /* 设置服务状态                             */
    }
    else if ( NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == ulCause )
    {
        pCmSvcRejInd->ulServiceStatus = MM_COM_SRVST_NO_IMSI;                   /* 设置服务状态                             */
    }
    else
    {

    }

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pCmSvcRejInd);
    return;
}

/* MM->CC */


VOS_VOID Mm_SndCcEstCnf(
                    VOS_UINT32 ulTransactionId,
                    VOS_UINT32 ulResult
                    )
{
    MMCC_EST_CNF_STRU                   *pCcEstCnf;                      /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;

    /* 因为即使在IDLE NORMAL状态下，在收到EST_REQ时，也始终把缓存标志设置了，
       所以在处理结束后，需要清除消息缓存标志  */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
        = MM_FALSE;

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    pCcEstCnf = (MMCC_EST_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMCC_EST_CNF_STRU));                    /* 申请内存                                 */
    if( VOS_NULL_PTR == pCcEstCnf )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcEstCnf:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pCcEstCnf->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCcEstCnf->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pCcEstCnf->MsgHeader.ulMsgName      = MMCC_EST_CNF;                         /* 消息名称                                 */

    pCcEstCnf->ulTransactionId = ulTransactionId;                               /* 设置消息参数                             */
    pCcEstCnf->ulResult = ulResult;

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pCcEstCnf);
    if (VOS_OK!=ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcEstCnf:ERROR: Send Message ERROR!");
        return;
    }

    /* G下，在已存在的链路上进行CC主被叫，此时由于链路已经建立，GAS不会在上报消息GAS_RR_CHAN_IND，
       导致MM也不会上CC上报MMCC_SYNC_IND消息，CS呼叫失败。
       因此，此处MM判断在当前链路上GAS是否已上报过有效的GAS_RR_CHAN_IND消息，如果是，则MM在发送了
       MMCC_EST_CNF后，立即再上报MMCC_SYNC_IND。*/
    if ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
      && (VOS_TRUE == g_MmGlobalInfo.ucGasRrChanIndMsgValidFlg))
    {
        Mm_SndCcSyncInd();
    }

    return;
}

/*******************************************************************************
  Module:   Mm_SndCcEstInd
  Function: 向CC发送MMCC_EST_IND的处理
  Input:    VOS_UINT32                   ulTransactionId
            VOS_UINT32                   ulSize
            VOS_UINT8                   *pucNasMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.11  新版做成
*******************************************************************************/

VOS_VOID Mm_SndCcEstInd(
                    VOS_UINT32                   ulTransactionId,
                    VOS_UINT32                   ulSize,
                    VOS_UINT8                   *pucCcMsg
                    )
{

    MMCC_EST_IND_STRU                   *pCcEstInd;                                /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;
    if ( ulSize >= 4 )
    {

        pCcEstInd = (MMCC_EST_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                      (sizeof(MMCC_EST_IND_STRU) -
                                        (4 * sizeof(VOS_UINT8))) + ulSize);            /* 申请内存                                 */


    }
    else
    {

        pCcEstInd = (MMCC_EST_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                      sizeof(MMCC_EST_IND_STRU));

    }
    if( VOS_NULL_PTR == pCcEstInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcEstInd:ERROR: MALLOC ERROR!");
        return;
    }

    pCcEstInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCcEstInd->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pCcEstInd->MsgHeader.ulMsgName = MMCC_EST_IND;                              /* 消息名称                                 */

    pCcEstInd->ulTransactionId = ulTransactionId;                               /* 设置消息参数                             */
    pCcEstInd->FisrtCcMsg.ulCcMsgSize = ulSize;
    PS_MEM_CPY( pCcEstInd->FisrtCcMsg.aucCcMsg, pucCcMsg, ulSize);

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pCcEstInd);
    if (VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcEstInd:ERROR: Send Message ERROR!");
        return;
    }

    /* G下，在已存在的链路上进行CC主被叫，此时由于链路已经建立，GAS不会在上报消息GAS_RR_CHAN_IND，
       导致MM也不会上CC上报MMCC_SYNC_IND消息，CS呼叫失败。
       因此，此处MM判断在当前链路上GAS是否已上报过有效的GAS_RR_CHAN_IND消息，如果是，则MM在发送了
       MMCC_EST_CNF后，立即再上报MMCC_SYNC_IND。*/
    if ( (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
      && (VOS_TRUE == g_MmGlobalInfo.ucGasRrChanIndMsgValidFlg))
    {
        Mm_SndCcSyncInd();
    }

    return;
}



VOS_VOID Mm_SndCcRelInd(
                    VOS_UINT32 ulTransactionId,
                    VOS_UINT32 ulRelCause
                    )
{
    MMCC_REL_IND_STRU                   *pCcRelInd;                                  /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;
    /*Mm_SndAgentProcedureInd(MM_SERVICE_FAILURE);*/

    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
        = MM_FALSE;

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    /* 清除mml中紧急呼叫标志 */
    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {
        NAS_MML_SetCsEmergencyServiceFlg(VOS_FALSE);
    }

    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();
    if ((NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST == enCsfbServiceStatus)
     || (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == enCsfbServiceStatus))
    {
#if (FEATURE_ON == FEATURE_LTE)
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
#endif

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
    }

    pCcRelInd = (MMCC_REL_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                        sizeof(MMCC_REL_IND_STRU));             /* 申请内存                                 */
    if( VOS_NULL_PTR == pCcRelInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcRelInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pCcRelInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCcRelInd->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pCcRelInd->MsgHeader.ulMsgName      = MMCC_REL_IND;                         /* 消息名称                                 */

    pCcRelInd->ulTransactionId = ulTransactionId;                               /* 设置消息参数                             */
    pCcRelInd->ulRelCause = ulRelCause;

    if (ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pCcRelInd);
    if (VOS_OK!=ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcRelInd:ERROR: Send Message ERROR!");
        return;
    }

    /*lint -e701*/
    if ( ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        & ( 0x01 << ulTransactionId ) ) )
        && ( MM_CONST_NUM_7 > ulTransactionId ) )
    {                                                                           /* 该TI的MM连接存在标识已经置上             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0]
                & ( ~(VOS_UINT8)( 0x01 << g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ) ) );       /* 清除MM连接存在标志                       */
    }
    else if ( ( MM_CONST_NUM_15 > ulTransactionId ) &&
        ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] &
        ( 0x01 << ( ulTransactionId - 8 ) ) ) ) &&
        ( MM_CONST_NUM_8 < ulTransactionId ) )
    {                                                                           /* 该TI的MM连接存在标识已经置上             */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1]
                & ( ~(VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI - 8 ) ) ) ); /* 清除MM连接存在标志                       */
    }
    else
    {

    }

    /*lint +e701*/
    return;
}

/*******************************************************************************
  Module:   Mm_SndCcDataInd
  Function: 向CC发送MMCC_DATA_IND的处理
  Input:    VOS_UINT32                   ulTransactionId
            VOS_UINT32                   ulSize
            VOS_UINT8                   *pucNasMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.11  新版做成
*******************************************************************************/

VOS_VOID Mm_SndCcDataInd(
                    VOS_UINT32                   ulTransactionId,
                    VOS_UINT32                   ulSize,
                    VOS_UINT8                   *pucCcMsg
                    )
{

    MMCC_DATA_IND_FOR_PCLINT_STRU       *pCcDataInd;
    MMCC_DATA_IND_STRU                  *pMsg;
    VOS_UINT32                           ulRst;
    if ( ulSize > 4 )
    {

        pMsg = (MMCC_DATA_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                      (sizeof(MMCC_DATA_IND_STRU)
                                        - (4 * sizeof(VOS_UINT8))) + ulSize);          /* 申请内存                                 */



    }
    else
    {
        pMsg = (MMCC_DATA_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                      sizeof(MMCC_DATA_IND_STRU));              /* 申请内存                                 */


    }
    if( VOS_NULL_PTR == pMsg )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcDataInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pCcDataInd = (MMCC_DATA_IND_FOR_PCLINT_STRU *)pMsg;

    pCcDataInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCcDataInd->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pCcDataInd->MsgHeader.ulMsgName     = MMCC_DATA_IND;                        /* 消息名称                                 */

    pCcDataInd->ulTransactionId = ulTransactionId;                              /* 设置消息参数                             */

    pCcDataInd->RcvCcMsg.ulCcMsgSize = ulSize;

    PS_MEM_CPY( pCcDataInd->RcvCcMsg.aucCcMsg, pucCcMsg, ulSize);

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pCcDataInd);
    if (VOS_OK!=ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcDataInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}

/*******************************************************************************
  Module:   Mm_SndCcSyncInd
  Function: 向CC发送MMCC_SYNC_IND的处理
  Input:    VOS_UINT32 ulTransactionId
            VOS_UINT32 ulRelCause
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇       2003.12.11  新版做成
*******************************************************************************/

VOS_VOID Mm_SndCcSyncInd(
                    VOS_VOID
                    )
{
    VOS_UINT8                               i;
    MMCC_SYNC_IND_STRU                   *pCcSyncInd;                           /* 定义原语类型指针                         */
    VOS_UINT32                            ulRst;
    pCcSyncInd = (MMCC_SYNC_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMCC_SYNC_IND_STRU));                   /* 申请内存                                 */
    if( VOS_NULL_PTR == pCcSyncInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcSyncInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pCcSyncInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCcSyncInd->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pCcSyncInd->MsgHeader.ulMsgName       = MMCC_SYNC_IND;                        /* 消息名称                                 */

    pCcSyncInd->enChannelMode             = g_RrMmSyncInd.ulChannelMode;

    pCcSyncInd->ulRabNum = 0;                                                     /* 设置消息参数                             */
    for ( i = 0; i < g_RrMmSyncInd.ulRabCnt; i++ )
    {
        if (RRC_NAS_CS_DOMAIN == g_RrMmSyncInd.NasSyncInfo[i].ulCnDomainId)
        {
            pCcSyncInd->syncInfo[i].ulRabId       =
                  g_RrMmSyncInd.NasSyncInfo[i].ulRabId;
            pCcSyncInd->syncInfo[i].ulRabSyncInfo =
                  g_RrMmSyncInd.NasSyncInfo[i].ulRabSyncInfo;
            pCcSyncInd->ulRabNum += 1;
        }
    }

    pCcSyncInd->enSyncReason = g_RrMmSyncInd.ulReason;

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pCcSyncInd);
    if (VOS_OK!=ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcSyncInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}

/*******************************************************************************
  Module:   Mm_SndCcReestCnf
  Function: 向CC发送MMCC_REEST_CNF的处理
  Input:    VOS_UINT32 ulTransactionId
            VOS_UINT32 ulResult
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.11  新版做成
*******************************************************************************/

VOS_VOID Mm_SndCcReestCnf(
                      VOS_UINT32 ulTransactionId,
                      VOS_UINT32 ulResult
                      )
{
    MMCC_REEST_CNF_STRU                 *pCcReestCnf;                           /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;
    if ( MMCC_REEST_SUCCESS == ulResult )
    {
        /*Mm_SndAgentProcedureInd(MM_SERVICE_SUCCESS);*/
    }

    pCcReestCnf = (MMCC_REEST_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMCC_REEST_CNF_STRU));                  /* 申请内存                                 */
    if( VOS_NULL_PTR == pCcReestCnf )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcReestCnf:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pCcReestCnf->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCcReestCnf->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pCcReestCnf->MsgHeader.ulMsgName    = MMCC_REEST_CNF;                       /* 消息名称                                 */

    pCcReestCnf->ulTransactionId = ulTransactionId;                             /* 设置消息参数                             */
    pCcReestCnf->ulResult = ulResult;

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pCcReestCnf);
    if (VOS_OK!=ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcReestCnf:ERROR: Send Message ERROR!");
        return;
    }
    return;
}



VOS_VOID Mm_SndCcErrInd(
    VOS_UINT32 ulTransactionId,
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enCause
)
{
    MMCC_ERR_IND_STRU                   *pCcErrInd;                             /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;

    pCcErrInd = (MMCC_ERR_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMCC_ERR_IND_STRU));                    /* 申请内存                                 */
    if( VOS_NULL_PTR == pCcErrInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcErrInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pCcErrInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCcErrInd->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pCcErrInd->MsgHeader.ulMsgName      = MMCC_ERR_IND;                         /* 消息名称                                 */

    pCcErrInd->ulTransactionId = ulTransactionId;                               /* 设置消息参数                             */
    pCcErrInd->enCause         = enCause;                                       /* 设置原因值                            */

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pCcErrInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcErrInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}


VOS_VOID NAS_Mm_SndCcGetCallInfoReq( VOS_VOID )
{
    MMCC_GET_CALL_INFO_REQ_STRU        *pstCcGetCallInfoReq = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstCcGetCallInfoReq = (MMCC_GET_CALL_INFO_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMCC_GET_CALL_INFO_REQ_STRU));                                  /* 申请内存                                 */

    if( VOS_NULL_PTR == pstCcGetCallInfoReq )
    {                                                                                                    /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcGetCallInfoReq:ERROR: MALLOC ERROR!");
        return;                                                                                          /* 返回                                     */
    }

    pstCcGetCallInfoReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCcGetCallInfoReq->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pstCcGetCallInfoReq->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCcGetCallInfoReq->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstCcGetCallInfoReq->MsgHeader.ulMsgName       = MMCC_GET_CALL_INFO_REQ;                              /* 消息名称                                 */

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pstCcGetCallInfoReq);
    if (VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_Mm_SndCcGetCallInfoReq:WARNING: Send msg fail.");
    }

    return;
}



VOS_VOID Mm_SndCcEmergencyNumberList(NAS_MML_EMERGENCY_NUM_LIST_STRU *pEmergencyList)
{
    MMCC_EMERGENCY_LIST_STRU            *pEmcNumLst = VOS_NULL;                            /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;

    if (VOS_NULL_PTR == pEmergencyList)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcEmergencyNumberList:ERROR:Receive Null Pointer!");
        return;                                                                 /* 返回                                     */
    }

    pEmcNumLst = (MMCC_EMERGENCY_LIST_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMCC_EMERGENCY_LIST_STRU));             /* 申请内存                                 */

    if (VOS_NULL_PTR == pEmcNumLst)
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcEmergencyNumberList:ERROR:MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pEmcNumLst->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pEmcNumLst->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pEmcNumLst->MsgHeader.ulMsgName       = MMCC_EMC_NUM_LST_IND;               /* 消息名称                                 */

    pEmcNumLst->ulMcc                     = pEmergencyList->ulMcc;

    pEmcNumLst->ucEmergencyNumber         = pEmergencyList->ucEmergencyNumber;

    PS_MEM_CPY(pEmcNumLst->astEmergencyLists, pEmergencyList->aucEmergencyList,
                ((pEmergencyList->ucEmergencyNumber) * sizeof(MMCC_EMERGENCY_CONTENT_STRU)));

    if (0 == pEmergencyList->ucEmergencyNumber)
    {
        pEmcNumLst->ulMcc = 0XFFFFFFFF;

        PS_MEM_SET(pEmcNumLst->astEmergencyLists,
                    0xFF,
                    MMCC_EMERGENCY_NUMBER_LISTS_MAX_NUMBER * sizeof(NAS_MML_EMERGENCY_NUM_STRU));
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pEmcNumLst);

    if (VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcEmergencyNumberList:ERROR:Send Message ERROR!");
        return;
    }

    return;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID NAS_MM_SndCcSrvccStatusInd(
    NAS_MMCC_SRVCC_STATUS_ENUM_UINT32   enSrvccSta
)
{
    MMCC_SRVCC_STATUS_IND_STRU         *pstSrvccStaInd = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSrvccStaInd = (MMCC_SRVCC_STATUS_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMCC_SRVCC_STATUS_IND_STRU));             /* 申请内存                                 */

    if (VOS_NULL_PTR == pstSrvccStaInd)
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MM_SndCcSrvccStatusInd:ERROR:MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pstSrvccStaInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSrvccStaInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pstSrvccStaInd->stMsgHeader.ulMsgName       = MMCC_SRVCC_STATUS_IND;               /* 消息名称                                */
    pstSrvccStaInd->enSrvccStatus               = enSrvccSta;

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pstSrvccStaInd);

    if (VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MM_SndCcSrvccStatusInd:ERROR:Send Message ERROR!");
        return;
    }

    return;
}
#endif
/* MM->RRC */
/*******************************************************************************
  Module:   Mm_SndRrRelReq
  Function: 向RRC发送RRMM_REL_REQ的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.12  新版做成
*******************************************************************************/

VOS_VOID Mm_SndRrRelReq(RRC_CELL_BAR_ENUM_UINT32  enBarValidFlg)
{
    VOS_UINT32                             ulRst;

    ulRst = (VOS_UINT32)g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc(RRC_NAS_CS_DOMAIN,
                                                                    enBarValidFlg);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndRrRelReq:ERROR: Send Message ERROR!");
        return;
    }

    return;
}


VOS_UINT8 NAS_MM_GetIdnnsType_CsfbMt(VOS_VOID)
{
    if (((MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
      || (MM_STMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId))
     && (MM_MS_ID_TMSI_PRESENT == (MM_MS_ID_TMSI_PRESENT & g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg)))
    {
        return RRC_IDNNS_CSFB_LOCAL_TMSI;
    }

    return RRC_IDNNS_CSFB_LOCAL_IMSI;

}




VOS_VOID Mm_SndRrEstReq(
    VOS_UINT32                          ulEstCause,
    VOS_UINT8                           ucPagingFlg,
    VOS_UINT32                          ulSize,
    VOS_UINT8                           *pFisrstMsg
)
{
    VOS_UINT32                          ulOpId;
    IDNNS_STRU                          IdnnsInfo;
    VOS_UINT32                          ulRst;
    NAS_MML_LAI_STRU                   *pstCsSuccLai     = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurCampPlmnId = VOS_NULL_PTR;
    VOS_UINT32                          ulCurCampLac;
    /* 删除根据EPLMN来进行TMSI的有效性判断,恢复跟协议保持一致 */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;

    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();
    enNetRatType        = NAS_MML_GetCurrNetRatType();
#endif

    pstCsSuccLai        = NAS_MML_GetCsLastSuccLai();
    ulCurCampLac        = NAS_MML_GetCurrCampLac();
    pstCurCampPlmnId    = NAS_MML_GetCurrCampPlmnId();


    MM_ReportM2NOtaMsg(ulSize, pFisrstMsg);

    g_MmGlobalInfo.ucRrEstReqOpid = (g_MmGlobalInfo.ucRrEstReqOpid + 1) % MM_MAX_OPID;
    ulOpId = g_MmGlobalInfo.ucRrEstReqOpid;

    if (MM_TRUE == ucPagingFlg)
    {
        g_MmGlobalInfo.ucPagingType = MM_MT_PAGING;
    }
    else
    {
        g_MmGlobalInfo.ucPagingType = MM_MO_PAGING;
    }

    /* 被叫csfb 到G需要通知RRC_IDNNS_CSFB_LOCAL_TMSI和RRC_IDNNS_CSFB_LOCAL_IMSI特定值 */
#if (FEATURE_ON == FEATURE_LTE)
        /* 3GPP 10.5.1.4描述:
            For the PAGING RESPONSE message sent as a response to a paging for CS fallback, the MS shall:
        -   select the TMSI as mobile identity type if the network has, in E-UTRAN,
        -   paged the MS for CS fallback using the S-TMSI; or
        -   indicated TMSI in the CS SERVICE NOTIFICATION message (see 3GPP TS 24.301 [120]);
        -   select the IMSI as mobile identity type if the network has, in E-UTRAN,
        -   paged the MS for CS fallback using the IMSI; or
        -   indicated IMSI in the CS SERVICE NOTIFICATION message (see 3GPP TS 24.301 [120]).
        */
    if ((NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == enCsfbServiceStatus)
     && (MM_TRUE == ucPagingFlg)
     && (NAS_MML_NET_RAT_TYPE_GSM == enNetRatType))
    {
        IdnnsInfo.ucIdnnsType = NAS_MM_GetIdnnsType_CsfbMt();
    }
    else
#endif
    {
        /* 如果TMSI有效，且处在分配该TMSI的所在的国家码内，即使使用IMSI寻呼，也使用TMSI响应
           GCF用例: 8.3.1.5 */
        if ( MM_MS_ID_TMSI_PRESENT ==
                  (MM_MS_ID_TMSI_PRESENT & g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg) )
        {

            if ((pstCurCampPlmnId->ulMcc != pstCsSuccLai->stPlmnId.ulMcc)
             || (pstCurCampPlmnId->ulMnc != pstCsSuccLai->stPlmnId.ulMnc))
            {
                IdnnsInfo.ucIdnnsType = RRC_IDNNS_TMSI_DIFFER_PLMN;
            }
            else if (ulCurCampLac != NAS_MML_GetCsLastSuccLac())
            {
                IdnnsInfo.ucIdnnsType = RRC_IDNNS_TMSI_DIFFER_LA;
            }
            else
            {
                IdnnsInfo.ucIdnnsType = RRC_IDNNS_LOCAL_TMSI;
            }
        }
        else if ( MM_MS_ID_IMSI_PRESENT ==
                    (MM_MS_ID_IMSI_PRESENT & g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg) )
        {
            if (MM_TRUE == ucPagingFlg)
            {
                IdnnsInfo.ucIdnnsType = RRC_IDNNS_IMSI_PAGE_RSP;
            }
            else
            {
                IdnnsInfo.ucIdnnsType = RRC_IDNNS_IMSI_UE_INIT;
            }
        }
        else
        {
            IdnnsInfo.ucIdnnsType = RRC_IDNNS_IMEI;
        }
    }

    if ( (0x0000ffff & pstCurCampPlmnId->ulMcc)
      == (0x0000ffff & pstCsSuccLai->stPlmnId.ulMcc))
    {
        IdnnsInfo.ucEnterPara = NAS_RRC_SPLMN_SAME_RPLMN;
    }
    else
    {
        IdnnsInfo.ucEnterPara = NAS_RRC_SPLMN_DIFF_RPLMN;
    }

    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ESTING );                             /* RR连接正在建立                           */

    ulRst = (VOS_UINT32)g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc(
        ulOpId,
        RRC_NAS_CS_DOMAIN,
        ulEstCause,
        &IdnnsInfo,
        (RRC_PLMN_ID_STRU *)pstCurCampPlmnId,
        ulSize,
        (VOS_INT8*)pFisrstMsg);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndRrEstReq:ERROR: Send Message ERROR!");
        return;
    }

    /* 更新链路释放控制结构 */
    NAS_MM_UpdateMmLinkCtrlStru();

    g_MmGlobalInfo.ucTime2Sndout = 1;         /* 设置导出全局变量标志。
 */

    g_MmGlobalInfo.bWaitingEstCnf = VOS_TRUE;


    return;

}

/*******************************************************************************
  Module:   Mm_SndRrDataReq
  Function: 向RRC发送   的处理
  Input:    VOS_UINT32           ulOpId
            VOS_UINT32           ulEstCause
            IDNNS_STRU      *pIdnnsInfo
            VOS_UINT32           ulSize
            VOS_INT8            *pFisrstMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.12  新版做成
*******************************************************************************/

VOS_VOID Mm_SndRrDataReq(
                     VOS_UINT32 ulSize,
                     VOS_UINT8 *pData,
                     VOS_UINT8 ucPrio
                     )
{
    VOS_UINT32                         ulRst;

    MM_ReportM2NOtaMsg(ulSize, pData);

    ulRst = (VOS_UINT32)g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc(
        RRC_NAS_CS_DOMAIN,
        ucPrio,
        ulSize,
        (VOS_INT8*)pData);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndRrDataReq:ERROR: Send Message ERROR!");
        return;
    }
    return;

}


RRC_NAS_ATTACH_STATUS_ENUM_UINT32  NAS_MM_GetAttachStatus(VOS_VOID)
{
    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {
        return RRC_NAS_ATTACH;
    }
    else
    {
        return RRC_NAS_NOT_ATTACH;
    }

}


VOS_VOID  NAS_MM_GetTmsiLai(
    NAS_INFO_TMSI_LAI_STRU             *pstTmsiLai
)
{
    pstTmsiLai->stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
    pstTmsiLai->stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
    pstTmsiLai->usLac          = (VOS_UINT16)NAS_MML_GetCsLastSuccLac();

    if ( VOS_FALSE == NAS_MML_GetSimCsRegStatus() )
    {

        PS_MEM_SET(pstTmsiLai->aucTmsi, 0xFF, NAS_MML_MAX_TMSI_LEN);
    }
    else
    {
        PS_MEM_CPY(pstTmsiLai->aucTmsi, NAS_MML_GetUeIdTmsi(), NAS_MML_MAX_TMSI_LEN);

    }

    return;
}


VOS_VOID  NAS_MM_SndGasInfoChangeReq(VOS_UINT32 ulMask)
{
    GRRMM_NAS_INFO_CHANGE_REQ_STRU     *pstNasInfoMsg = VOS_NULL_PTR;

    pstNasInfoMsg = (GRRMM_NAS_INFO_CHANGE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                     WUEPS_PID_MM, sizeof(GRRMM_NAS_INFO_CHANGE_REQ_STRU));

    if( VOS_NULL == pstNasInfoMsg )
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstNasInfoMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(GRRMM_NAS_INFO_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstNasInfoMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNasInfoMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pstNasInfoMsg->MsgHeader.ulMsgName       = GRRMM_NAS_INFO_CHANGE_REQ;                              /* 消息名称                                  */

    /* 设置发送域 */
    pstNasInfoMsg->stNasInfo.ulCnDomainId = RRC_NAS_CS_DOMAIN;

    /* Attach状态填充 */
    if (MM_NAS_INFO_ATTACH_FLG == (MM_NAS_INFO_ATTACH_FLG & ulMask))
    {
        pstNasInfoMsg->stNasInfo.bitOpAttach  = VOS_TRUE;
        pstNasInfoMsg->stNasInfo.ulAttach     = NAS_MM_GetAttachStatus();
    }

    /* GSM KC 信息填充 */
    if (MM_NAS_INFO_SK_FLG == ( MM_NAS_INFO_SK_FLG & ulMask ) )
    {
        pstNasInfoMsg->stNasInfo.bitOpSecurityKey = VOS_TRUE;

        /* aucKc 中存放 GSM 的 KC    */
        PS_MEM_CPY(pstNasInfoMsg->stNasInfo.stSecurityKey.aucKc,
                        NAS_MML_GetSimCsSecurityGsmKc(), NAS_MML_GSM_KC_LEN);

    }
    /* Del Key Op项设置 */
    if ( MM_NAS_INFO_DEL_KEY_FLG == (MM_NAS_INFO_DEL_KEY_FLG & ulMask ) )
    {
        pstNasInfoMsg->stNasInfo.bitOpDelKey = VOS_TRUE;
    }

    /* TMSI 或 LAI 信息发 填充 */
    if ( MM_NAS_INFO_LOCA_INFO_FLG == ( MM_NAS_INFO_LOCA_INFO_FLG & ulMask ) )
    {
        pstNasInfoMsg->stNasInfo.bitOpTmsiLai = VOS_TRUE;

        NAS_MM_GetTmsiLai(&(pstNasInfoMsg->stNasInfo.stTmsiLai));

    }

    /* 向GAS 发送结果 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MM, pstNasInfoMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndGasInfoChangeReq Snd pstNasInfoMsg fail!");
    }

    return;

}

VOS_VOID  NAS_MM_SndWasInfoChangeReq(VOS_UINT32 ulMask)
{
    RRMM_NAS_INFO_CHANGE_REQ_STRU      *pstNasInfoMsg = VOS_NULL_PTR;

    pstNasInfoMsg = (RRMM_NAS_INFO_CHANGE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                     WUEPS_PID_MM, sizeof(RRMM_NAS_INFO_CHANGE_REQ_STRU));

    if( VOS_NULL == pstNasInfoMsg )
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstNasInfoMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(RRMM_NAS_INFO_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstNasInfoMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNasInfoMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pstNasInfoMsg->MsgHeader.ulMsgName       = RRMM_NAS_INFO_CHANGE_REQ;                              /* 消息名称                                  */

    /* 设置发送域 */
    pstNasInfoMsg->ulCnDomainCnt            = MM_CONST_NUM_1;
    pstNasInfoMsg->aNasInfo[0].ulCnDomainId = RRC_NAS_CS_DOMAIN;

    /* Attach状态填充 */
    if (MM_NAS_INFO_ATTACH_FLG == (MM_NAS_INFO_ATTACH_FLG & ulMask))
    {
        pstNasInfoMsg->aNasInfo[0].bitOpAttach  = VOS_TRUE;
        pstNasInfoMsg->aNasInfo[0].ulAttach     = NAS_MM_GetAttachStatus();
    }

    /* UMTS CK IK 信息填充 */
    if (MM_NAS_INFO_SK_FLG == ( MM_NAS_INFO_SK_FLG & ulMask ) )
    {
        pstNasInfoMsg->aNasInfo[0].bitOpSecurityKey = VOS_TRUE;

        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucCk,
                   NAS_MML_GetSimCsSecurityUmtsCk(), NAS_MML_UMTS_CK_LEN);
        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucIk,
                   NAS_MML_GetSimCsSecurityUmtsIk(), NAS_MML_UMTS_IK_LEN);
    }

    /* Del Key Op项设置 */
    if ( MM_NAS_INFO_DEL_KEY_FLG == (MM_NAS_INFO_DEL_KEY_FLG & ulMask ) )
    {
        pstNasInfoMsg->aNasInfo[0].bitDelKey = VOS_TRUE;
    }

    /* TMSI 或 LAI 信息发 填充 */
    if ( MM_NAS_INFO_LOCA_INFO_FLG == ( MM_NAS_INFO_LOCA_INFO_FLG & ulMask ) )
    {
        pstNasInfoMsg->aNasInfo[0].bitOpTmsiLai = VOS_TRUE;
        NAS_MM_GetTmsiLai(&(pstNasInfoMsg->aNasInfo[0].TmsiLai));
    }

    /* 向Was 发送结果 */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MM, (struct MsgCB **)&pstNasInfoMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndWasInfoChangeReq Snd pstNasInfoMsg fail!");
    }

    return;

}


VOS_VOID Mm_SndRrNasInfoChgReq(VOS_UINT32 ulMask)
{
    if (MM_NAS_INFO_NULL_FLG == ulMask)
    {
        return;
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_MM_SndWasInfoChangeReq(ulMask);
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        NAS_MM_SndGasInfoChangeReq(ulMask);
    }
    else
    {

    }

    return;

}


VOS_VOID NAS_MM_NotifyAsInfoChgReq(VOS_VOID)
{
    NAS_MM_SndWasInfoChangeReq(MM_NAS_INFO_LOCA_INFO_FLG);

    NAS_MM_SndGasInfoChangeReq(MM_NAS_INFO_LOCA_INFO_FLG);

    return;
}


VOS_VOID NAS_MM_WriteCkIkInCard(VOS_VOID)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           *pucFileContent = VOS_NULL_PTR;
    VOS_UINT16                          usSn = 0;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;

    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    pucFileContent = (VOS_UINT8*)MM_MEM_ALLOC(
                                         VOS_MEMPOOL_INDEX_MM,
                                         MM_SIM_FILE_LEN_CKIK,
                                         WUEPS_MEM_NO_WAIT);

    if (VOS_NULL_PTR == pucFileContent)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM,
                 "Mm_SndAgentUsimUpdateFileReq:ERROR:Alloc Memory error!\r");
        return;
    }
    /*lint -e961*/
    pucFileContent[usSn++] = NAS_MML_GetSimCsSecurityCksn();
    /*lint +e961*/

    PS_MEM_CPY(&pucFileContent[usSn], NAS_MML_GetSimCsSecurityUmtsCk(), NAS_MML_UMTS_CK_LEN);
    usSn += NAS_MML_UMTS_CK_LEN;
    PS_MEM_CPY(&pucFileContent[usSn], NAS_MML_GetSimCsSecurityUmtsIk(), NAS_MML_UMTS_IK_LEN);

    usLength = MM_SIM_FILE_LEN_CKIK;

    NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_USIM_EFKEYS_ID,
                                    0,
                                    (VOS_UINT8)usLength,
                                    pucFileContent);

    (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_MM, 0, &stSetFileInfo);

    MM_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucFileContent );

     return;
}

VOS_VOID NAS_MM_WriteKCInCard(VOS_VOID)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           *pucFileContent = VOS_NULL_PTR;
    VOS_UINT16                          usSn = 0;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;

    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    pucFileContent = (VOS_UINT8*)MM_MEM_ALLOC(
                                         VOS_MEMPOOL_INDEX_MM,
                                         MM_SIM_FILE_LEN_CKIK,
                                         WUEPS_MEM_NO_WAIT);

    if (VOS_NULL_PTR == pucFileContent)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM,
                 "Mm_SndAgentUsimUpdateFileReq:ERROR:Alloc Memory error!\r");
        return;
    }

    PS_MEM_CPY(&pucFileContent[usSn],
               NAS_MML_GetSimCsSecurityGsmKc(),
               NAS_MML_GSM_KC_LEN);

    usSn += NAS_MML_GSM_KC_LEN;
    /*lint -e961*/
    pucFileContent[usSn++] = NAS_MML_GetSimCsSecurityCksn();
    /*lint +e961*/

    usLength = MM_SIM_FILE_LEN_KC;

;
    NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_GSM_EFKC_ID,
                                    0,
                                    (VOS_UINT8)usLength,
                                    pucFileContent);

    (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_MM, 0, &stSetFileInfo);

    MM_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucFileContent );

    return;
}




VOS_VOID NAS_MM_WriteLocaInCard(VOS_VOID)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           *pucFileContent = VOS_NULL_PTR;
    VOS_UINT16                          usSn = 0;
    VOS_UINT16                          usFileId;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;

    usFileId = USIMM_DEF_FILEID_BUTT;


    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));

    pucFileContent = (VOS_UINT8*)MM_MEM_ALLOC(
                                         VOS_MEMPOOL_INDEX_MM,
                                         MM_SIM_FILE_LEN_CKIK,
                                         WUEPS_MEM_NO_WAIT);

    if (VOS_NULL_PTR == pucFileContent)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM,
                 "Mm_SndAgentUsimUpdateFileReq:ERROR:Alloc Memory error!\r");
        return;
    }

    PS_MEM_SET(pucFileContent,0,MM_SIM_FILE_LEN_LOCA_INFO);
    if ( 0 == ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &
        MM_MS_ID_TMSI_PRESENT ) )
    {
        NAS_MML_InitUeIdTmsiInvalid();
    }

    PS_MEM_CPY(&pucFileContent[usSn],
               NAS_MML_GetUeIdTmsi(),
               NAS_MML_MAX_TMSI_LEN);
    usSn += NAS_MML_MAX_TMSI_LEN;

    /*lint -e961*/
    pucFileContent[usSn]
        = (VOS_UINT8)(NAS_MML_GetCsLastSuccMcc() &
        0x0000000f);
    pucFileContent[usSn++]
        |= (VOS_UINT8)((NAS_MML_GetCsLastSuccMcc() &
        0x00000f00) >> 4);
    pucFileContent[usSn]
        = (VOS_UINT8)((NAS_MML_GetCsLastSuccMcc() &
        0x000f0000) >> 16);
    pucFileContent[usSn++]
        |= (VOS_UINT8)((NAS_MML_GetCsLastSuccMnc() &
        0x000f0000) >> 12);
    pucFileContent[usSn]
        = (VOS_UINT8)(NAS_MML_GetCsLastSuccMnc() &
        0x0000000f);
    pucFileContent[usSn++]
        |= (VOS_UINT8)((NAS_MML_GetCsLastSuccMnc() &
        0x00000f00) >> 4);

    pucFileContent[usSn++]
        = (VOS_UINT8)(NAS_MML_GetCsLastSuccLac() >> 8);
    pucFileContent[usSn++]
        = (VOS_UINT8)(NAS_MML_GetCsLastSuccLac() & 0x000000ff);

    pucFileContent[usSn++] = 0;

    pucFileContent[usSn++] = NAS_MML_GetCsUpdateStatus();
    /*lint +e961*/
    usLength = MM_SIM_FILE_LEN_LOCA_INFO;

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFLOCI_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFLOCI_ID;
    }

    NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0,
                                    (VOS_UINT8)usLength,
                                    pucFileContent);

    NAS_MM_NotifyAsInfoChgReq();

    (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_MM, 0, &stSetFileInfo);

    MM_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucFileContent );

    return;
}

#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID NAS_MM_SndAcpuOmChangeTmsi(VOS_VOID)
{
    VOS_UINT8                          *pucTmsi      = VOS_NULL_PTR;
    OM_FTM_REPROT_IND_STRU             *pstFtmRptInd = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;
    NAS_FTM_TMSI_RPT_EVENT_STRU         stFtmTmsiRpt;
    VOS_UINT32                          ulContentAddr;

    PS_MEM_SET(&stFtmTmsiRpt, 0, sizeof(NAS_FTM_TMSI_RPT_EVENT_STRU));

    /* 如果工程菜单没有打开，则什么都不做 */
    if (VOS_FALSE == NAS_MML_GetFtmCtrlFlag())
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_SndAcpuOmTmsi:INFO: FTM CTRL OFF.");
        return;
    }

    pucTmsi = NAS_MML_GetUeIdTmsi();

    /* 如果当前PTMSI没有发生改变，则什么都不做 */
    if (0 == PS_MEM_CMP(pucTmsi, NAS_MML_GetSimCsLociFileContent(), NAS_MML_MAX_TMSI_LEN))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_SndAcpuOmTmsi:INFO: TMSI NOT CHANGE.");
        return;
    }

    NAS_COMM_BULID_FTM_HEADER_INFO(&stFtmTmsiRpt.stHeader,
                                   NAS_MML_MAX_TMSI_LEN,
                                   VOS_GetModemIDFromPid(WUEPS_PID_MM),
                                   NAS_FTM_PROJECT_TMSI_RPT)

    PS_MEM_CPY(stFtmTmsiRpt.aucTmsi, pucTmsi, NAS_MML_MAX_TMSI_LEN);

    /* 将TMSI的值发送给ACPU OM模块 */
    /* 申请消息结构内存 */
    /*lint -e961*/
    ulMsgLen     = sizeof(OM_FTM_REPROT_IND_STRU) - VOS_MSG_HEAD_LENGTH - 4 + sizeof(NAS_FTM_TMSI_RPT_EVENT_STRU);
    /*lint +e961*/
    pstFtmRptInd = (OM_FTM_REPROT_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_MM, ulMsgLen);
    if (VOS_NULL_PTR == pstFtmRptInd)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MM_SndAcpuOmTmsi:ERROR: Alloc msg fail.");
        return;
    }

    /* 构造消息结构体 */
    pstFtmRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFtmRptInd->ulSenderPid       = WUEPS_PID_MM;
    pstFtmRptInd->ulMsgName         = ID_OM_FTM_REPROT_IND;
    pstFtmRptInd->ulMsgType         = OM_ERR_LOG_MSG_FTM_REPORT;
    pstFtmRptInd->ulMsgSN           = 0;
    pstFtmRptInd->ulRptlen          = sizeof(NAS_FTM_TMSI_RPT_EVENT_STRU);

    ulContentAddr                   = (VOS_UINT32)pstFtmRptInd->aucContent;
    PS_MEM_CPY((VOS_UINT8 *)ulContentAddr, &stFtmTmsiRpt, sizeof(NAS_FTM_TMSI_RPT_EVENT_STRU));

    /* 发送消息到ACPU OM模块 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MM, pstFtmRptInd))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MM_SndAcpuOmTmsi:ERROR: SEND MSG FIAL.");
    }

    return;
}


VOS_VOID NAS_MM_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen,
    NAS_ERR_LOG_ALM_ID_ENUM_U16         usAlmId
)
{
    OM_FAULT_ERR_LOG_IND_STRU                              *pstFaultRptInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLen;
    VOS_UINT32                                              ulContentAddr;
    NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16                 enReportType;

    /* 申请消息结构内存 */
    /*lint -e961*/
    ulMsgLen     = sizeof(OM_FAULT_ERR_LOG_IND_STRU) - VOS_MSG_HEAD_LENGTH - 4 + ulDataLen;
    /*lint +e961*/
    pstFaultRptInd = (OM_FAULT_ERR_LOG_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_MM, ulMsgLen);
    if (VOS_NULL_PTR == pstFaultRptInd)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MM_SndAcpuOmFaultErrLogInd:ERROR: Alloc msg fail.");
        return;
    }

    /* 构造消息结构体 */
    pstFaultRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFaultRptInd->ulSenderPid       = WUEPS_PID_MM;
    pstFaultRptInd->ulMsgName         = ID_OM_FAULT_ERR_LOG_IND;

    enReportType = NAS_GetErrLogUnsoliReportType(usAlmId);

    if (NAS_ERR_LOG_FAULT_REPORT == enReportType)
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_FAULT_REPORT;
    }
    else if (NAS_ERR_LOG_ALARM_REPORT == enReportType)
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_ALARM_REPORT;
    }
    else
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_TYPE_BUTT;
    }

    pstFaultRptInd->ulMsgSN           = 0;
    pstFaultRptInd->ulRptlen          = ulDataLen;

    ulContentAddr                     = (VOS_UINT32)pstFaultRptInd->aucContent;
    PS_MEM_CPY((VOS_UINT8 *)ulContentAddr, pData, ulDataLen);

    /* 发送消息到ACPU OM模块 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MM, pstFaultRptInd))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MM_SndAcpuOmFaultErrLogInd:ERROR: SEND MSG FIAL.");
    }

    return;
}


VOS_VOID NAS_MM_CsPagingFailRecord(
    NAS_ERR_LOG_CS_PAGING_CAUSE_ENUM_U32    enCause
)
{
    NAS_ERR_LOG_CS_PAGING_FAIL_EVENT_STRU   stCsPagingFailEvt;
    VOS_UINT32                              ulLength;
    VOS_UINT16                              usLevel;
    VOS_UINT32                              ulIsLogRecord;
    VOS_UINT32                              ulResult;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CS_PAGING_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CS_PAGING_FAIL_EVENT_STRU);

    /* 填充CS PAGING失败异常信息 */
    PS_MEM_SET(&stCsPagingFailEvt, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsPagingFailEvt.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MM),
                                      NAS_ERR_LOG_ALM_CS_PAGING_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stCsPagingFailEvt.stPositionInfo);

    /* 填写错误原因值 */
    stCsPagingFailEvt.enCause   = enCause;

    stCsPagingFailEvt.ucCurrMmState     = g_MmGlobalInfo.ucState;
    stCsPagingFailEvt.ucCurrProcType    = g_MmGlobalInfo.ucProc;
    stCsPagingFailEvt.ucLastEstType     = g_MmGlobalInfo.ucPagingType;
    stCsPagingFailEvt.ucLastPagingCause = g_MmGlobalInfo.ucPagingCause;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        stCsPagingFailEvt.ucGMsIdType    = NAS_MML_GetErrLogGMsIdType();
        stCsPagingFailEvt.ucGPagingType  = NAS_MML_GetErrLogGPagingType();
    }
    else
    {
        stCsPagingFailEvt.ulWCnDomainId  = NAS_MML_GetErrLogWCnDomainId();
        stCsPagingFailEvt.ulWPagingType  = NAS_MML_GetErrLogWPagingType();
        stCsPagingFailEvt.ulWPagingCause = NAS_MML_GetErrLogWPagingCause();
        stCsPagingFailEvt.ulWPagingUeId  = NAS_MML_GetErrLogWPagingUeId();
    }

    NAS_MML_InitErrLogPagingInfo();

    /* 将CS PAGING失败信息发送给ACPU OM模块 */
    NAS_MM_SndAcpuOmFaultErrLogInd(&stCsPagingFailEvt, ulLength, NAS_ERR_LOG_ALM_CS_PAGING_FAIL);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stCsPagingFailEvt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndAcpuOmCsPagingFailInd(): Push buffer error.");
    }

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CS_PAGING_FAIL,
                           WUEPS_PID_MM,
                           (VOS_UINT8 *)&stCsPagingFailEvt,
                           sizeof(stCsPagingFailEvt));

    return;
}


VOS_VOID NAS_MM_CsfbMtFailRecord(VOS_VOID)
{
    NAS_ERR_LOG_CSFB_MT_CALL_FAIL_EVENT_STRU    stCsfbMtFailEvt;
    VOS_UINT32                                  ulLength;
    VOS_UINT16                                  usLevel;
    VOS_UINT32                                  ulIsLogRecord;
    VOS_UINT32                                  ulResult;
    NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32          enState;
    NAS_MNTN_POSITION_INFO_STRU                *pstPositionInfo = VOS_NULL_PTR;
    NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU        *pstStateInfo    = VOS_NULL_PTR;
    VOS_UINT32                                  i;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);
    enState       = NAS_MML_GetCsfbMtCurrState();

    /* 模块异常或状态不正确时，不保存异常信息 */
    if ((VOS_FALSE == ulIsLogRecord)
     || (NAS_ERR_LOG_CSFB_MT_STATE_NULL == enState)
     || (NAS_ERR_LOG_CSFB_MT_CALL_CAUSE_BUTT == enState))
    {
        return;
    }

    /* CSFB MT状态为业务消息已经接收到时，不保存异常信息，并清除CSFB MT的异常信息 */
    if (NAS_ERR_LOG_CSFB_MT_STATE_CM_SERVICE_MSG_RECEIVED == enState)
    {
        /* 清除CSFB的状态信息 */
        NAS_MML_InitCsfbMtInfo();
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CSFB_MT_CALL_FAIL_EVENT_STRU);

    /* 填充CS PAGING失败异常信息 */
    PS_MEM_SET(&stCsfbMtFailEvt, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsfbMtFailEvt.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MM),
                                      NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 填写错误原因值 */
    stCsfbMtFailEvt.enCurrState     = enState;
    stCsfbMtFailEvt.ulPositionNum   = NAS_MML_GetCsfbMtRecordPositionNum();
    stCsfbMtFailEvt.ulStateNum      = NAS_MML_GetCsfbMtRecordStateNum();

    for (i = 0; i < NAS_ERR_LOG_MAX_POSITION_RECORD_NUM; i++)
    {
        pstPositionInfo = &(NAS_MML_GetCsfbMtInfoAddr()->astPositionInfo[i]);
        PS_MEM_CPY(&(stCsfbMtFailEvt.stPositionInfo[i]),
                   pstPositionInfo,
                   sizeof(NAS_MNTN_POSITION_INFO_STRU));
    }

    for (i = 0; i < NAS_ERR_LOG_MAX_CSFB_MT_STATE_RECORD_NUM; i++)
    {
        pstStateInfo = &(NAS_MML_GetCsfbMtInfoAddr()->astStateInfo[i]);
        PS_MEM_CPY(&(stCsfbMtFailEvt.astStateInfo[i]),
                   pstStateInfo,
                   sizeof(NAS_ERR_LOG_CSFB_MT_STATE_INFO_STRU));
    }

    /* 不是在CSFB MT保护定时器超时状态收到REL IND状态，都需要清除CSFB的状态信息 */
    if (NAS_ERR_LOG_CSFB_MT_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND != enState)
    {
        NAS_MML_InitCsfbMtInfo();
    }

    /* 将CSFB MT失败信息发送给ACPU OM模块 */
    NAS_MM_SndAcpuOmFaultErrLogInd(&stCsfbMtFailEvt, ulLength, NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stCsfbMtFailEvt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndAcpuOmCsPagingFailInd(): Push buffer error.");
    }

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL,
                           WUEPS_PID_MM,
                           (VOS_UINT8 *)&stCsfbMtFailEvt,
                           sizeof(stCsfbMtFailEvt));

    return;

}



VOS_VOID NAS_MM_IDResInfoRecord(
    VOS_UINT8                           ucIDType
)
{
    NAS_ERR_LOG_PROCESS_INFO_IND_EVENT_STRU stProcInfoEvent;
    VOS_UINT32                              ulLength;
    VOS_UINT16                              usLevel;
    VOS_UINT32                              ulIsLogRecord;
    VOS_UINT32                              ulResult;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PORCESS_INFO_IND);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PROCESS_INFO_IND_EVENT_STRU);

    /* 填充过程信息 */
    PS_MEM_SET(&stProcInfoEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stProcInfoEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MM),
                                      NAS_ERR_LOG_ALM_PORCESS_INFO_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stProcInfoEvent.enInfoType              = NAS_ERR_LOG_PROCESS_INFO_TYPE_ID_RES;
    stProcInfoEvent.stIDResInfo.ucIDReqType = ucIDType;

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stProcInfoEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_IDResInfoRecord(): Push buffer error.");
    }

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PORCESS_INFO_IND,
                           WUEPS_PID_MM,
                           (VOS_UINT8 *)&stProcInfoEvent,
                           sizeof(stProcInfoEvent));

    return;
}

VOS_VOID NAS_MM_SrvccFailRecord(
    NAS_ERR_LOG_SRVCC_FAIL_CAUSE_ENUM_UINT8                 enSrvccFailCause
)
{
    NAS_ERR_LOG_SRVCC_FAIL_STRU             stSrvccFail;
    VOS_UINT32                              ulLength;
    VOS_UINT16                              usLevel;
    VOS_UINT32                              ulIsLogRecord;
    VOS_UINT32                              ulResult;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_SRVCC_FAIL_INFO);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_SRVCC_FAIL_STRU);

    /* 填充过程信息 */
    PS_MEM_SET(&stSrvccFail, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stSrvccFail.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MM),
                                      NAS_ERR_LOG_ALM_SRVCC_FAIL_INFO,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stSrvccFail.stPositionInfo);

    stSrvccFail.enSrvccFailCause = enSrvccFailCause;


    NAS_MM_SndAcpuOmFaultErrLogInd(&stSrvccFail, ulLength, NAS_ERR_LOG_ALM_SRVCC_FAIL_INFO);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stSrvccFail, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SrvccFailRecord(): Push buffer error.");
    }

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_SRVCC_FAIL_INFO,
                           WUEPS_PID_MM,
                           (VOS_UINT8 *)&stSrvccFail,
                           sizeof(stSrvccFail));

    return;
}
#endif


VOS_VOID Mm_SndAgentUsimUpdateFileReq( VOS_UINT16 usEfId )
{
    VOS_UINT16                          usLength = 0;
    VOS_UINT8*                          pucFileContent = VOS_NULL_PTR;
    VOS_UINT16                          usSn = 0;
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;

    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));



    switch ( usEfId )
    {
    case USIMM_USIM_EFKEYS_ID:
        pucFileContent = (VOS_UINT8*)MM_MEM_ALLOC(
                                             VOS_MEMPOOL_INDEX_MM,
                                             MM_SIM_FILE_LEN_CKIK,
                                             WUEPS_MEM_NO_WAIT);

        if (VOS_NULL_PTR == pucFileContent)
        {
            NAS_LOG(WUEPS_PID_MM, MM_ORIGIN, PS_LOG_LEVEL_ERROR,
                     "Mm_SndAgentUsimUpdateFileReq:ERROR:Alloc Memory error!\r");
            return;
        }

        /*lint -e961*/
        pucFileContent[usSn++] = NAS_MML_GetSimCsSecurityCksn();
        /*lint +e961*/
        PS_MEM_CPY(&pucFileContent[usSn],
                    NAS_MML_GetSimCsSecurityUmtsCk(),
                    NAS_MML_UMTS_CK_LEN);
        usSn += NAS_MML_UMTS_CK_LEN;
        PS_MEM_CPY(&pucFileContent[usSn],
                    NAS_MML_GetSimCsSecurityUmtsIk(),
                    NAS_MML_UMTS_IK_LEN);
        usLength = MM_SIM_FILE_LEN_CKIK;

        NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                        USIMM_GUTL_APP,
                                        usEfId,
                                        0,
                                        (VOS_UINT8)usLength,
                                        pucFileContent);
        (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_MM, 0, &stSetFileInfo);

        break;
    case USIMM_USIM_EFKC_ID:
    case USIMM_GSM_EFKC_ID: /* 更新 SIM 卡中 KC、CKSN */
        /* 分配空间 */
        pucFileContent = (VOS_UINT8*)MM_MEM_ALLOC(
                                             VOS_MEMPOOL_INDEX_MM,
                                             MM_SIM_FILE_LEN_KC,
                                             WUEPS_MEM_NO_WAIT);

        if (VOS_NULL_PTR == pucFileContent)
        {
            NAS_LOG(WUEPS_PID_MM, MM_ORIGIN, PS_LOG_LEVEL_ERROR,
                     "Mm_SndAgentUsimUpdateFileReq:ERROR: Alloc Memory error!\r " );
            return;
        }

        /* 取得 CKSN */
        /*pucFileContent[usSn++] = g_MmGlobalInfo.CsSecutityInfo.ucCksn;*/

        /* 取得 KC */
        PS_MEM_CPY(&pucFileContent[usSn],
                    NAS_MML_GetSimCsSecurityGsmKc(), NAS_MML_GSM_KC_LEN);
        usSn += NAS_MML_GSM_KC_LEN;

        /*lint -e961*/
        pucFileContent[usSn++] = NAS_MML_GetSimCsSecurityCksn();
        /*lint +e961*/
        usLength = MM_SIM_FILE_LEN_KC;

        NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                        USIMM_GUTL_APP,
                                        usEfId,
                                        0,
                                        (VOS_UINT8)usLength,
                                        pucFileContent);

        (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_MM, 0, &stSetFileInfo);
        break;
    case USIMM_USIM_EFLOCI_ID:
    case USIMM_GSM_EFLOCI_ID:
        /* IMSI Refresh, 不更新卡文件，直接返回 */
        if (VOS_TRUE == NAS_MML_GetImsiRefreshStatus())
        {
            NAS_LOG(WUEPS_PID_MM, MM_ORIGIN, PS_PRINT_INFO, "Mm_SndAgentUsimUpdateFileReq: IMSI Refresh, do not write EFLOCI file" );
            return;
        }

        pucFileContent = (VOS_UINT8*)MM_MEM_ALLOC(
                                             VOS_MEMPOOL_INDEX_MM,
                                             MM_SIM_FILE_LEN_LOCA_INFO,
                                             WUEPS_MEM_NO_WAIT);

        if (VOS_NULL_PTR == pucFileContent)
        {
            NAS_LOG(WUEPS_PID_MM, MM_ORIGIN, PS_LOG_LEVEL_ERROR,
                     "Mm_SndAgentUsimUpdateFileReq:ERROR: Alloc Memory error!\r " );
            return;
        }

        PS_MEM_SET(pucFileContent,0,MM_SIM_FILE_LEN_LOCA_INFO);                /* 初始化内存                               */

        if ( 0 == ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &
            MM_MS_ID_TMSI_PRESENT ) )
        {
            NAS_MML_InitUeIdTmsiInvalid();
        }

        PS_MEM_CPY(&pucFileContent[usSn],
                   NAS_MML_GetUeIdTmsi(),
                   NAS_MML_MAX_TMSI_LEN);
        usSn += NAS_MML_MAX_TMSI_LEN;

        /*lint -e961*/
        pucFileContent[usSn]
            = (VOS_UINT8)((NAS_MML_GetCsLastSuccMcc()) &
            0x0000000f);
        pucFileContent[usSn++]
            |= (VOS_UINT8)(((NAS_MML_GetCsLastSuccMcc()) &
            0x00000f00) >> 4);
        pucFileContent[usSn]
            = (VOS_UINT8)(((NAS_MML_GetCsLastSuccMcc()) &
            0x000f0000) >> 16);
        pucFileContent[usSn++]
            |= (VOS_UINT8)(((NAS_MML_GetCsLastSuccMnc()) &
            0x000f0000) >> 12);
        pucFileContent[usSn]
            = (VOS_UINT8)((NAS_MML_GetCsLastSuccMnc()) &
            0x0000000f);
        pucFileContent[usSn++]
            |= (VOS_UINT8)(((NAS_MML_GetCsLastSuccMnc()) &
            0x00000f00) >> 4);

        pucFileContent[usSn++]
            = (VOS_UINT8)(NAS_MML_GetCsLastSuccLac() >> 8);
        pucFileContent[usSn++]
            = (VOS_UINT8)(NAS_MML_GetCsLastSuccLac() & 0x000000ff);

        pucFileContent[usSn++] = 0;

        pucFileContent[usSn++] = NAS_MML_GetCsUpdateStatus();

        usLength = MM_SIM_FILE_LEN_LOCA_INFO;

        NAS_MM_NotifyAsInfoChgReq();

        /*lint +e961*/
#if (FEATURE_ON == FEATURE_PTM)
        /* 工程菜单打开后，TMSI发生改变需要上报给OM */
        NAS_MM_SndAcpuOmChangeTmsi();
#endif

        /*如果写入文件6F7E的数据和卡当前所存储的内容不相同，则执行写卡操作*/
        if (0 != PS_MEM_CMP(pucFileContent, NAS_MML_GetSimCsLociFileContent(), MM_SIM_FILE_LEN_LOCA_INFO))
        {
            NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                            USIMM_GUTL_APP,
                                            usEfId,
                                            0,
                                            (VOS_UINT8)usLength,
                                            pucFileContent);

            (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_MM, 0, &stSetFileInfo);
            NAS_MML_UpdateSimCsLociFileContent(pucFileContent);

        }

        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_SndAgentUsimUpdateFileReq:WARNING: File Id Abnormal");
        break;
    }


    if ( VOS_NULL_PTR != pucFileContent )
    {
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_NAS, pucFileContent );
        /*WUEPS_TRACE( MM_LOG_LEVEL_5, " \nMM:SEND VOS_NULL_PTR MSG!\r " );             */
        /*PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_SndAgentUsimUpdateFileReq:WARNING: SEND VOS_NULL_PTR MSG!");*/
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_SndAgentUsimUpdateFileReq:INFO: FREE THE PTR!");
    }
    return;
}




VOS_VOID Mm_SndAgentUsimAuthenReq()
{
    VOS_UINT8       *ucAutn;
    VOS_UINT8        ucTempOpId = 0;
    ucAutn = (VOS_UINT8*)MM_MEM_ALLOC(
                                 VOS_MEMPOOL_INDEX_MM,
                                 g_MmGlobalInfo.AuthenCtrlInfo.ucAutnLen + 1,
                                 WUEPS_MEM_NO_WAIT);
    if( VOS_NULL_PTR == ucAutn )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndAgentUsimAuthenReq:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    ucAutn[0] = g_MmGlobalInfo.AuthenCtrlInfo.ucAutnLen;
    PS_MEM_CPY(ucAutn + 1, g_MmGlobalInfo.AuthenCtrlInfo.aucAutn,
                g_MmGlobalInfo.AuthenCtrlInfo.ucAutnLen);

    g_MmGlobalInfo.ucRcvAgentFlg |= MM_RCV_AUTH_CNF_FLG;

    ucTempOpId = g_MmGlobalInfo.AuthenCtrlInfo.ucOpId;

    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId++;

    NAS_USIMMAPI_AuthReq(
        WUEPS_PID_MM,
        AUTHENTICATION_REQ_UMTS_CHALLENGE,
        g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
        /* g_MmGlobalInfo.AuthenCtrlInfo.aucAutn); */
        ucAutn,
        g_MmGlobalInfo.AuthenCtrlInfo.ucOpId);

    MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, ucAutn);
    return;
}



VOS_VOID NAS_MM_SndMmcDetachCnf(VOS_UINT8 ucServiceStatus)
{
    MMCMM_DETACH_CNF_STRU                 *pMmcDetachCnf = VOS_NULL_PTR;        /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pMmcDetachCnf   = (MMCMM_DETACH_CNF_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_DETACH_CNF_STRU));
    if ( VOS_NULL_PTR == pMmcDetachCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndMmcDetachCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pMmcDetachCnf->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMmcDetachCnf->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pMmcDetachCnf->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMmcDetachCnf->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pMmcDetachCnf->MsgHeader.ulMsgName       = MMCMM_DETACH_CNF;                      /* 消息名称                                 */
    pMmcDetachCnf->MsgHeader.ulLength
        = sizeof(MMCMM_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;


    pMmcDetachCnf->ulOpid = g_MmGlobalInfo.stDetachInfo.ulOpid;


    /* 设置服务状态                             */
    switch(ucServiceStatus)
    {
        case MM_NO_IMSI:
            pMmcDetachCnf->ulServiceStatus = MM_COM_SRVST_NO_IMSI;
            break;
        case MM_NO_SERVICE:
            pMmcDetachCnf->ulServiceStatus = MM_COM_SRVST_NO_SERVICE;
            break;
        /* 有cs业务时syscfg设置需要detach cs场景，mm不发起detach cs，mm回复detach cnf带当前的正常服务状态 */
        case MM_NORMAL_SERVICE:
            pMmcDetachCnf->ulServiceStatus = MM_COM_SRVST_NORMAL_SERVICE;
            break;
        default:
            pMmcDetachCnf->ulServiceStatus = MM_COM_SRVST_LIMITED_SERVICE;
            break;
    }

#if (FEATURE_ON == FEATURE_ECALL)
    /* ecall only模式配置为PS ONLY不影响CS的attach标记 */
    if (NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
    {
        Mm_TimerStop(MM_TIMER_PROTECT_CS_DETACH);

        /* 内部消息的发送 */
        NAS_MML_SndInternalMsg(pMmcDetachCnf);

        return;
    }
#endif

    NAS_MML_SetCsAttachAllowFlg( VOS_FALSE );

    Mm_TimerStop(MM_TIMER_PROTECT_CS_DETACH);

    pMmcDetachCnf->ulDetachType             = g_MmGlobalInfo.stDetachInfo.enDetachType;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pMmcDetachCnf);

    return;
}



VOS_VOID Mm_SndMmcPowerOffCnf()
{
    MMCMM_POWER_OFF_CNF_STRU              *pMmcPowerOffCnf;              /* 定义原语类型指针                         */
    extern VOS_UINT8 gucMmProcessFlg;

    /* 申请消息内存分配 */
    pMmcPowerOffCnf   = (MMCMM_POWER_OFF_CNF_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_POWER_OFF_CNF_STRU));
    if ( VOS_NULL_PTR == pMmcPowerOffCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "Mm_SndMmcPowerOffCnf,ERROR:ALLOC BUFFER WRONG!");
        gucMmProcessFlg = WAIT_FOR_MMCMM_START_REQ;
        return;
    }

    pMmcPowerOffCnf->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMmcPowerOffCnf->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pMmcPowerOffCnf->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMmcPowerOffCnf->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pMmcPowerOffCnf->MsgHeader.ulMsgName = MMCMM_POWER_OFF_CNF;                /* 消息名称                                 */
    pMmcPowerOffCnf->MsgHeader.ulLength
        = sizeof(MMCMM_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    NAS_MML_SetCsAttachAllowFlg( VOS_FALSE );

    gucMmProcessFlg = WAIT_FOR_MMCMM_START_REQ;

    /* ==>A32D12744 */
    Mm_TimerStop(MM_TIMER_STOP_ALL);
    /* <==A32D12744 */
    /*Mm_SndAgentProcedureInd(MM_DETACH_COMPLETE);*/

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pMmcPowerOffCnf);
    return;
}

/**************************************************
 ******    二期      begin    *********************
 **************************************************/


VOS_VOID Mm_SndMmcRrConnInfInd(
                        VOS_UINT32   ulRrConnFlg                                     /* RR连接状态                               */
                        )
{
    MMCMM_RR_CONN_INFO_IND_STRU         *pMmcRrConnInfInd = VOS_NULL_PTR;       /* 定义原语类型指针                         */
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus    = VOS_NULL_PTR;

    pstConnStatus   = NAS_MML_GetConnStatus();

    /* 申请消息内存分配 */
    pMmcRrConnInfInd  = (MMCMM_RR_CONN_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_RR_CONN_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pMmcRrConnInfInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "Mm_SndMmcRrConnInfInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pMmcRrConnInfInd->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMmcRrConnInfInd->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pMmcRrConnInfInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMmcRrConnInfInd->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pMmcRrConnInfInd->MsgHeader.ulMsgName       = MMCMM_RR_CONN_INFO_IND;       /* 消息名称                                 */
    pMmcRrConnInfInd->MsgHeader.ulLength
        = sizeof(MMCMM_RR_CONN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pMmcRrConnInfInd->ulRrConnFlg = ulRrConnFlg;                                /* RR连接状态                               */

    /* Modifeied by z40661 for V7R1 phase II , 2011-07-11, begin */
    if ( MMC_MM_RR_CONN_ABSENT == ulRrConnFlg )
    {
        g_MmSubLyrShare.MmShare.ucCsSpecificFlg = MM_SPECIFIC_OFF;
        pstConnStatus->ucCsSigConnStatusFlg     = VOS_FALSE;
    }
    else if ( ( MMC_MM_RR_CONN_ESTING == ulRrConnFlg ) ||
        ( MMC_MM_RR_CONN_ESTED == ulRrConnFlg ) )
    {
        g_MmSubLyrShare.MmShare.ucCsSpecificFlg = MM_SPECIFIC_ON;
        pstConnStatus->ucCsSigConnStatusFlg = VOS_TRUE;
        if ( MMC_MM_RR_CONN_ESTED == ulRrConnFlg )
        {
            pstConnStatus->ucRrcStatusFlg   = VOS_TRUE;
        }
    }
    else
    {

    }
    /* Modifeied by z40661 for V7R1 phase II , 2011-07-11, end */

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pMmcRrConnInfInd);
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_SndMmcDeRegisterInit
  Function: 向MMC发送MMCMM_DEREGISTER_INITIATION的处理
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  s46746       2009.06.24  新版做成
*******************************************************************************/
VOS_VOID Mm_SndMmcDeRegisterInit(  )
{
    MMCMM_DEREGISTER_INITIATION_STRU        *pMmcDeRegisterInit;
    VOS_UINT32                              ulRst;
    pMmcDeRegisterInit = ( MMCMM_DEREGISTER_INITIATION_STRU * )PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                sizeof( MMCMM_DEREGISTER_INITIATION_STRU ));
    if( VOS_NULL_PTR == pMmcDeRegisterInit )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndMmcDeRegisterInit:ERROR: MALLOC ERROR!");
        return;
    }

    pMmcDeRegisterInit->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMmcDeRegisterInit->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pMmcDeRegisterInit->MsgHeader.ulMsgName       = MMCMM_DEREGISTER_INITIATION;

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pMmcDeRegisterInit);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndMmcDeRegisterInit:ERROR: Send Message ERROR!");
        return;
    }

    return;
}

/*******************************************************************************
  Module:   Mm_SndCcPromptInd
  Function: 向CC发送MMCC_PROMPT_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇       2004.03.09  新版做成
*******************************************************************************/

VOS_VOID Mm_SndCcPromptInd(
                       VOS_VOID
                    )
{
    MMCC_PROMPT_IND_STRU                *pCcPromptInd;                          /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;
    pCcPromptInd = (MMCC_PROMPT_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMCC_PROMPT_IND_STRU));                 /* 申请内存                                 */
    if( VOS_NULL_PTR == pCcPromptInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcPromptInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pCcPromptInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pCcPromptInd->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pCcPromptInd->MsgHeader.ulMsgName       = MMCC_PROMPT_IND;                  /* 消息名称                                 */

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pCcPromptInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndCcPromptInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}



VOS_VOID Mm_SndSsEstCnf(
                    VOS_UINT32 ulTransactionId,
                    VOS_UINT32 ulResult
                    )
{
    MMSS_EST_CNF_STRU                   *pSsEstCnf;                               /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;

    /* 因为即使在IDLE NORMAL状态下，在收到EST_REQ时，也始终把缓存标志设置了，
       所以在处理结束后，需要清除消息缓存标志  */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
        = MM_FALSE;

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    pSsEstCnf = ( MMSS_EST_CNF_STRU * )PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof( MMSS_EST_CNF_STRU ));                  /* 申请内存                                 */
    if( VOS_NULL_PTR == pSsEstCnf )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSsEstCnf:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pSsEstCnf->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSsEstCnf->MsgHeader.ulReceiverPid   = WUEPS_PID_SS;
    pSsEstCnf->MsgHeader.ulMsgName      = MMSS_EST_CNF;                         /* 消息名称                                 */

    pSsEstCnf->ulTi     = ulTransactionId;                                      /* 设置消息参数                             */
    pSsEstCnf->ulResult = ulResult;                                             /* 建立结果                                 */

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pSsEstCnf);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSsEstCnf:ERROR: Send Message ERROR!");
        return;
    }
    return;
}


/*******************************************************************************
  Module:   Mm_SndSsEstInd
  Function: 向SS发送MMSS_EST_IND的处理
  Input:    VOS_UINT32       ulTransactionId
            VOS_UINT32       ulSize
            VOS_UINT8       *pucSsMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇       2004.03.09  新版做成
*******************************************************************************/

VOS_VOID Mm_SndSsEstInd(
                    VOS_UINT32                   ulTransactionId,
                    VOS_UINT32                   ulSize,
                    VOS_UINT8                   *pucSsMsg
                    )
{

    MMSS_EST_IND_STRU                   *pSsEstInd;                                 /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;
    if ( ulSize >= 4 )
    {

        pSsEstInd = (MMSS_EST_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 (sizeof(MMSS_EST_IND_STRU) -
                                      (4 * sizeof(VOS_UINT8))) + ulSize);              /* 申请内存                                 */

    }
    else
    {

        pSsEstInd = (MMSS_EST_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMSS_EST_IND_STRU));
    }
    if( VOS_NULL_PTR == pSsEstInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSsEstInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pSsEstInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSsEstInd->MsgHeader.ulReceiverPid   = WUEPS_PID_SS;
    pSsEstInd->MsgHeader.ulMsgName      = MMSS_EST_IND;                         /* 消息名称                                 */

    pSsEstInd->ulTi = ulTransactionId;                                          /* 设置消息参数                             */
    pSsEstInd->SsMsg.ulSsMsgSize = ulSize;
    PS_MEM_CPY( pSsEstInd->SsMsg.aucSsMsg, pucSsMsg, ulSize);

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pSsEstInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSsEstInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}


/*******************************************************************************
  Module:   Mm_SndSsDataInd
  Function: 向SS发送MMSS_DATA_IND的处理
  Input:    VOS_UINT32       ulTransactionId
            VOS_UINT32       ulSize
            VOS_UINT8       *pucSsMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇       2004.03.09  新版做成
*******************************************************************************/

VOS_VOID Mm_SndSsDataInd(
                    VOS_UINT32                   ulTransactionId,
                    VOS_UINT32                   ulSize,
                    VOS_UINT8                   *pucSSMsg
                    )
{

    MMSS_DATA_IND_FOR_PCLINT_STRU       *pSsDataInd;
    MMSS_DATA_IND_STRU                  *pMsg;
    VOS_UINT32                           ulRst;
    if ( ulSize > 4 )
    {

        pMsg = (MMSS_DATA_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 (sizeof(MMSS_DATA_IND_STRU)
                                      - (4 * sizeof(VOS_UINT8))) + ulSize);            /* 申请内存                                 */

    }
    else
    {
        pMsg = (MMSS_DATA_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMSS_DATA_IND_STRU));                   /* 申请内存                                 */

    }
    if( VOS_NULL_PTR == pMsg )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSsDataInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pSsDataInd = (MMSS_DATA_IND_FOR_PCLINT_STRU *)pMsg;

    pSsDataInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSsDataInd->MsgHeader.ulReceiverPid   = WUEPS_PID_SS;
    pSsDataInd->MsgHeader.ulMsgName     = MMSS_DATA_IND;                        /* 消息名称                                 */

    pSsDataInd->ulTi = ulTransactionId;                                         /* 设置消息参数                             */
    pSsDataInd->SsMsg.ulSsMsgSize = ulSize;
    PS_MEM_CPY( pSsDataInd->SsMsg.aucSsMsg, pucSSMsg, ulSize);

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pSsDataInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSsDataInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}


VOS_VOID Mm_SndSsRelInd(
    VOS_UINT32                          ulTransactionId,
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmssRelCause
)
{
    MMSS_REL_IND_STRU                   *pSsRelInd;                             /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;
    pSsRelInd = ( MMSS_REL_IND_STRU * )PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                        sizeof( MMSS_REL_IND_STRU ));           /* 申请内存                                 */
    if( VOS_NULL_PTR == pSsRelInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSsRelInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_FALSE;

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();


    if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST ==  NAS_MML_GetCsfbServiceStatus())
    {
#if (FEATURE_ON == FEATURE_LTE)
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
#endif

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
    }

    pSsRelInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSsRelInd->MsgHeader.ulReceiverPid   = WUEPS_PID_SS;
    pSsRelInd->MsgHeader.ulMsgName      = MMSS_REL_IND;                         /* 消息名称                                 */

    pSsRelInd->ulTi     = ulTransactionId;                                      /* 设置消息参数                             */

    pSsRelInd->enMmssRelCause = enMmssRelCause;

    if (ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pSsRelInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSsRelInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}



VOS_VOID Mm_SndSmsEstCnf(
                    VOS_UINT32 ulTransactionId
                    )
{
    MMSMS_EST_CNF_STRU                  *pSmsEstCnf;                            /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;

    /* 因为即使在IDLE NORMAL状态下，在收到EST_REQ时，也始终把缓存标志设置了，
       所以在处理结束后，需要清除消息缓存标志  */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
        = MM_FALSE;

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    pSmsEstCnf = ( MMSMS_EST_CNF_STRU * )PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof( MMSMS_EST_CNF_STRU ));                 /* 申请内存                                 */
    if( VOS_NULL_PTR == pSmsEstCnf )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsEstCnf:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pSmsEstCnf->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSmsEstCnf->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pSmsEstCnf->MsgHeader.ulMsgName     = MMSMS_EST_CNF;                        /* 消息名称                                 */

    pSmsEstCnf->ulTi     = ulTransactionId;                                     /* 设置消息参数                             */

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pSmsEstCnf);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsEstCnf:ERROR: Send Message ERROR!");
        return;
    }
    return;
}


/*******************************************************************************
  Module:   Mm_SndSmsEstInd
  Function: 向SMS发送MMSMS_EST_IND的处理
  Input:    VOS_UINT32       ulTransactionId
            VOS_UINT32       ulSize
            VOS_UINT8       *pucSmsMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇       2004.03.09  新版做成
*******************************************************************************/

VOS_VOID Mm_SndSmsEstInd(
                    VOS_UINT32                   ulTransactionId,
                    VOS_UINT32                   ulSize,
                    VOS_UINT8                   *pucSmsMsg
                    )
{

    MMSMS_EST_IND_STRU                   *pSmsEstInd;                               /* 定义原语类型指针                         */
    VOS_UINT32                            ulRst;

    if ( ulSize >= 4 )
    {

        pSmsEstInd = (MMSMS_EST_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 (sizeof(MMSMS_EST_IND_STRU) -
                                      (4 * sizeof(VOS_UINT8))) + ulSize);              /* 申请内存                                 */


    }
    else
    {

        pSmsEstInd = (MMSMS_EST_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMSMS_EST_IND_STRU));

    }
    if( VOS_NULL_PTR == pSmsEstInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsEstInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pSmsEstInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSmsEstInd->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pSmsEstInd->MsgHeader.ulMsgName     = MMSMS_EST_IND;                        /* 消息名称                                 */

    pSmsEstInd->ulTi = ulTransactionId;                                         /* 设置消息参数                             */

    pSmsEstInd->SmsMsg.ulNasMsgSize = ulSize;

    PS_MEM_CPY( pSmsEstInd->SmsMsg.aucNasMsg, pucSmsMsg, ulSize);

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pSmsEstInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsEstInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}

/*******************************************************************************
  Module:   Mm_SndSmsDataInd
  Function: 向SMS发送MMSMS_DATA_IND的处理
  Input:    VOS_UINT32       ulTransactionId
            VOS_UINT32       ulSize
            VOS_UINT8       *pucSsMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇       2004.03.09  新版做成
*******************************************************************************/

VOS_VOID Mm_SndSmsDataInd(
                    VOS_UINT32                   ulTransactionId,
                    VOS_UINT32                   ulSize,
                    VOS_UINT8                   *pucSmsMsg
                    )
{

    MMSMS_DATA_IND_FOR_PCLINT_STRU       *pSmsDataInd ;                         /* 定义原语类型指针                         */
    MMSMS_DATA_IND_STRU                  *pMsg;
    VOS_UINT32                            ulRst;
    if ( ulSize > 4 )
    {
        pMsg = (MMSMS_DATA_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 (sizeof(MMSMS_DATA_IND_STRU)
                                      - (4 * sizeof(VOS_UINT8))) + ulSize);            /* 申请内存                                 */

    }
    else
    {
        pMsg = (MMSMS_DATA_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMSMS_DATA_IND_STRU));                  /* 申请内存                                 */

    }
    if( VOS_NULL_PTR == pMsg )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsDataInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pSmsDataInd = (MMSMS_DATA_IND_FOR_PCLINT_STRU *)pMsg;

    pSmsDataInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSmsDataInd->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pSmsDataInd->MsgHeader.ulMsgName    = MMSMS_DATA_IND;                       /* 消息名称                                 */

    pSmsDataInd->ulTi = ulTransactionId;                                        /* 设置消息参数                             */
    pSmsDataInd->SmsMsg.ulNasMsgSize = ulSize;
    PS_MEM_CPY( pSmsDataInd->SmsMsg.aucNasMsg, pucSmsMsg, ulSize);

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pSmsDataInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsDataInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}



VOS_VOID Mm_SndSmsRelInd(
                    VOS_UINT32 ulTransactionId,
                    VOS_UINT32 ulRelCause
                    )
{
    MMSMS_REL_IND_STRU                  *pSmsRelInd;                              /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
        = MM_FALSE;

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    pSmsRelInd = ( MMSMS_REL_IND_STRU * )PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof( MMSMS_REL_IND_STRU ));                 /* 申请内存                                 */
    if( VOS_NULL_PTR == pSmsRelInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsRelInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pSmsRelInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSmsRelInd->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pSmsRelInd->MsgHeader.ulMsgName     = MMSMS_REL_IND;                        /* 消息名称                                 */

    pSmsRelInd->ulTi        = ulTransactionId;                                  /* 设置消息参数                             */
    pSmsRelInd->ulRelCause  = ulRelCause;                                       /* 设置释放原因                             */

    if (ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI)
    {
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pSmsRelInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsRelInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}



/*******************************************************************************
  Module:   Mm_SndTcDataInd
  Function: 向TC发送TCMM_DATA_IND的处理
  Input:    VOS_UINT32                   ulSize
            VOS_UINT8                   *pucTcMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.06.18  新版做成
*******************************************************************************/

VOS_VOID Mm_SndTcDataInd(
                    VOS_UINT32                   ulSize,
                    VOS_UINT8                   *pucTcMsg
                    )
{

    TCMM_DATA_IND_STRU                  *pTcDataInd;                                /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;
    if ( ulSize >= 4 )
    {

        pTcDataInd = (TCMM_DATA_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 (sizeof(TCMM_DATA_IND_STRU) -
                                      (4 * sizeof(VOS_UINT8))) + ulSize);              /* 申请内存                                 */

    }
    else
    {
        pTcDataInd = (TCMM_DATA_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(TCMM_DATA_IND_STRU));

    }
    if( VOS_NULL_PTR == pTcDataInd )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndTcDataInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pTcDataInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTcDataInd->MsgHeader.ulReceiverPid   = WUEPS_PID_TC;
    pTcDataInd->MsgHeader.ulMsgName = TCMM_DATA_IND;                            /* 消息名称                                 */

    pTcDataInd->RcvTcMsg.ulTcMsgSize = ulSize;

    PS_MEM_CPY( pTcDataInd->RcvTcMsg.aucTcMsg, pucTcMsg, ulSize);

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pTcDataInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndTcDataInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}



VOS_VOID Mm_SndSmsRegStsInd(
                        VOS_UINT8 ucRegSts
                        )
{
    MMSMS_REG_STATE_IND_STRU            *pSmsRegStsInd;                         /* 定义原语类型指针                         */
    VOS_UINT32                           ulRst;
    pSmsRegStsInd = ( MMSMS_REG_STATE_IND_STRU * )PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof( MMSMS_REG_STATE_IND_STRU ));           /* 申请内存                                 */
    if( VOS_NULL_PTR == pSmsRegStsInd )
    {                                                                           /* 内存申请失败                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsRegStsInd:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }

    pSmsRegStsInd->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSmsRegStsInd->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pSmsRegStsInd->MsgHeader.ulMsgName    = MMSMS_REG_STATE_IND;                /* 消息名称                                 */

    if ( MM_STATUS_ATTACHED == ucRegSts )
    {
        pSmsRegStsInd->ulRegSts = MM_SMS_REG_ATTACHED;
    }
    else
    {

        if ( MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState )
        {
            pSmsRegStsInd->ulRegSts = MM_SMS_REG_ATTACH_ATTEMPT_TO_UPDATE;
        }
        else
        {
            pSmsRegStsInd->ulRegSts = MM_SMS_REG_DETACHED;
        }
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pSmsRegStsInd);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_SndSmsRegStsInd:ERROR: Send Message ERROR!");
        return;
    }

    return;
}


/*****************************************************************************
 Prototype      : MM_SndSapi3EstReq
 Description    : GSM 下请求建立SAPI3的消息发送函数
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-10-22
    Author      : sxbo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 MM_SndSapi3EstReq()
{
    VOS_UINT32                          ulRet;

    GRRMM_EST_SAPI3_REQ_ST             *pMsg;

    /* 申请内存空间                              */
    pMsg = (GRRMM_EST_SAPI3_REQ_ST *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                    sizeof(GRRMM_EST_SAPI3_REQ_ST));

    /* 内存申请失败                              */
    if (VOS_NULL_PTR == pMsg)
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_SndSapi3EstReq: ERROR: Alloc memory fail.");

        /* 返回                                  */
        return MM_FALSE;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pMsg->MsgHeader.ulMsgName           = GRRMM_EST_SAPI3_REQ;

    /* 调用VOS发送原语                           */
    ulRet = PS_SEND_MSG(WUEPS_PID_MM, pMsg);

    /* 发送失败                                  */
    if (VOS_OK != ulRet)
    {
        /* 打印出错信息 */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_SndSapi3EstReq: ERROR: Send Msg fail.");

        return MM_FALSE;

    }

    /* 返回                                  */
    return MM_TRUE;
}


VOS_VOID MM_SndMmcRrRelInd(VOS_UINT32 ulRelCause)
{
    MMCMM_RR_REL_IND_ST  *pstMmcMmRelInd;

    /* 申请消息内存分配 */
    pstMmcMmRelInd    = (MMCMM_RR_REL_IND_ST *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_RR_REL_IND_ST));
    if ( VOS_NULL_PTR == pstMmcMmRelInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "MM_SndMmcRrRelInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMmcMmRelInd->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMmcMmRelInd->MsgHeader.ulSenderPid         = WUEPS_PID_MM;
    pstMmcMmRelInd->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMmcMmRelInd->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMmcMmRelInd->MsgHeader.ulMsgName           = MMCMM_RR_REL_IND;
    pstMmcMmRelInd->MsgHeader.ulLength
        = sizeof(MMCMM_RR_REL_IND_ST) - VOS_MSG_HEAD_LENGTH;
    pstMmcMmRelInd->ulRrcConnStatus               = RRC_RRC_CONN_STATUS_ABSENT;
    pstMmcMmRelInd->ulRelCause                    = ulRelCause;
    pstMmcMmRelInd->ulCnDomainId                  = RRC_NAS_CS_DOMAIN;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMmcMmRelInd);

    return;
}


VOS_VOID NAS_MM_SndMmcResumeRsp(VOS_VOID)
{
    MMCMM_RESUME_RSP_STRU              *pstMmcMmResumeRsp = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMmcMmResumeRsp = (MMCMM_RESUME_RSP_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_RESUME_RSP_STRU));
    if ( VOS_NULL_PTR == pstMmcMmResumeRsp)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndMmcResumeRsp,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMmcMmResumeRsp->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMmcMmResumeRsp->MsgHeader.ulSenderPid         = WUEPS_PID_MM;
    pstMmcMmResumeRsp->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMmcMmResumeRsp->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMmcMmResumeRsp->MsgHeader.ulMsgName           = MMCMM_RESUME_RSP;
    pstMmcMmResumeRsp->MsgHeader.ulLength
        = sizeof(MMCMM_RESUME_RSP_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMmcMmResumeRsp);

    return;
}




VOS_VOID NAS_MM_SndMmcAttachCnf(VOS_VOID)
{

    MMCMM_ATTACH_CNF_STRU              *pstMsg              = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg  = (MMCMM_ATTACH_CNF_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_ATTACH_CNF_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCMM_ATTACH_CNF;
    pstMsg->ulOpid                      = g_MmGlobalInfo.stAttachInfo.ulOpid;
    NAS_MM_ConvertToMmcServiceStatus(g_MmGlobalInfo.ucMmServiceState, &(pstMsg->ulServiceStatus));

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}



VOS_VOID NAS_MM_SndMmcCsRegResultInd(
    VOS_UINT32                          ulRealFlg,
    VOS_UINT32                          ulLuResult,
    VOS_UINT32                          ulCause
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRstInd;                       /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pstCsRegRstInd    = (MMMMC_CS_REG_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMMMC_CS_REG_RESULT_IND_STRU));
    if ( VOS_NULL_PTR == pstCsRegRstInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndMmcCsRegResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstCsRegRstInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCsRegRstInd->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstCsRegRstInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCsRegRstInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstCsRegRstInd->stMsgHeader.ulMsgName       = MMMMC_CS_REG_RESULT_IND;                    /* 消息名称                                 */
    pstCsRegRstInd->stMsgHeader.ulLength
        = sizeof(MMMMC_CS_REG_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    if ( MM_MMC_LU_PROC_TRUE == ulRealFlg )
    {
        if ( MM_MMC_LU_RESULT_SUCCESS == ulLuResult )
        {
            /*Mm_SndAgentProcedureInd(MM_LAU_SUCCESS);*/
            NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_SUCCESS,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
        }
        else
        {
            /*Mm_SndAgentProcedureInd(MM_LAU_FAILURE);*/
            NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                            &ulCause, NAS_OM_EVENT_LAU_FAIL_LEN);
        }
    }

    else
    {
        /* 目前代码中成功的假流程可以填两种原因值: NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL和NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC */
        /* 除NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC之外，其他原因值统一填为NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL */
        if ( MM_MMC_LU_RESULT_SUCCESS == ulLuResult )
        {
            if ( (NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC   != ulCause)
              && (NAS_MML_REG_FAIL_CAUSE_HO_WAIT_SYSINFO_TIMEOUT != ulCause) )                
            {
                ulCause = NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL;
            }
        }
    }

    pstCsRegRstInd->enLuResult       = ulLuResult;                              /* 设置LU的结果                             */
    pstCsRegRstInd->enNetType        = NAS_MML_GetCurrNetRatType();
    pstCsRegRstInd->enRegFailCause   = (VOS_UINT16)ulCause;                     /* 设置失败的原因值                         */
    pstCsRegRstInd->ulCsUpdateStatus = NAS_MML_GetCsUpdateStatus();             /* 设置更新状态                             */
    pstCsRegRstInd->ulLuAttemptCnt   = (VOS_UINT32)g_MmGlobalInfo.LuInfo.ucLuAttmptCnt;  /* 设置LU的Attempt Counter                  */

    NAS_MM_ConvertToMmcServiceStatus(g_MmGlobalInfo.ucMmServiceState, &(pstCsRegRstInd->ulServiceStatus));

    pstCsRegRstInd->stOldLai.PlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
    pstCsRegRstInd->stOldLai.PlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
    pstCsRegRstInd->stOldLai.ulLac        = NAS_MML_GetCsLastSuccLac();

    /* MM需要通知MMC此时是否在进行联合注册 */
    pstCsRegRstInd->ucIsComBined = g_MmGlobalInfo.ucIsComBined;

    /* 通知完后立即清除 */
    g_MmGlobalInfo.ucIsComBined = VOS_FALSE;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstCsRegRstInd);

    return;
}


VOS_VOID NAS_MM_SndMmcAbortInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enAbortCause
)
{
    MMMMC_ABORT_IND_STRU               *pstMmcAbortInd = VOS_NULL_PTR;

    /* 申请内存空间 */
    pstMmcAbortInd = (MMMMC_ABORT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMMMC_ABORT_IND_STRU));
    if ( VOS_NULL_PTR == pstMmcAbortInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndMmcAbortInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }
    /* 构造消息 */
    pstMmcAbortInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcAbortInd->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMmcAbortInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcAbortInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMmcAbortInd->stMsgHeader.ulMsgName       = MMMMC_ABORT_IND;              /* 消息名称 */
    pstMmcAbortInd->stMsgHeader.ulLength
        = sizeof(MMMMC_ABORT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcAbortInd->enAbortCause                = enAbortCause;     /* 设置失败的原因值 */

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMmcAbortInd);

    return;
}


VOS_VOID NAS_MM_SndGmmLuResultInd(
    VOS_UINT32                          ulLuResult,
    VOS_UINT32                          ulCause
)
{
    MMGMM_LU_RESULT_IND_STRU           *pstLuRstInd = VOS_NULL_PTR;             /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pstLuRstInd       = (MMGMM_LU_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMGMM_LU_RESULT_IND_STRU));
    if ( VOS_NULL_PTR == pstLuRstInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndGmmLuResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstLuRstInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstLuRstInd->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstLuRstInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLuRstInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstLuRstInd->stMsgHeader.ulMsgName       = MMGMM_LU_RESULT_IND;                    /* 消息名称                                 */
    pstLuRstInd->stMsgHeader.ulLength
        = sizeof(MMGMM_LU_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstLuRstInd->enLuResult = ulLuResult;                                      /* 设置LU的结果                             */
    pstLuRstInd->enCause    = (VOS_UINT16)ulCause;                                            /* 设置失败的原因值                         */

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstLuRstInd);
    return;

}




VOS_VOID NAS_MM_SndGmmAuthFailInd(VOS_VOID)
{
    MMGMM_AUTHENTICATON_FAILURE_IND_STRU  *pstAuthenFailInd = VOS_NULL_PTR;            /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pstAuthenFailInd  = (MMGMM_AUTHENTICATON_FAILURE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMGMM_AUTHENTICATON_FAILURE_IND_STRU));
    if ( VOS_NULL_PTR == pstAuthenFailInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndGmmAuthFailInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstAuthenFailInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstAuthenFailInd->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstAuthenFailInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstAuthenFailInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstAuthenFailInd->stMsgHeader.ulMsgName       = MMGMM_AUTHENTICATON_FAILURE_IND;/* 消息名称                                 */
    pstAuthenFailInd->stMsgHeader.ulLength
        = sizeof(MMGMM_AUTHENTICATON_FAILURE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstAuthenFailInd);

    return;
}


VOS_VOID NAS_MM_SndGmmCsConnectInd(
    MMGMM_CS_CONNECT_STATUS_ENUM_UINT32    enCsConnectStatus
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstCsConnectInd;

    /* 申请消息内存分配 */
    pstCsConnectInd       = (MMGMM_CS_CONNECT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMGMM_CS_CONNECT_IND_STRU));
    if ( VOS_NULL_PTR == pstCsConnectInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndGmmCsConnectInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstCsConnectInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCsConnectInd->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstCsConnectInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCsConnectInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstCsConnectInd->stMsgHeader.ulMsgName       = MMGMM_CS_CONNECT_IND;            /* 消息名称                                 */
    pstCsConnectInd->stMsgHeader.ulLength
        = sizeof(MMGMM_CS_CONNECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCsConnectInd->enCsConnectStatus           = enCsConnectStatus;                               /* 设置消息参数                             */

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstCsConnectInd);

    return;
}


VOS_VOID NAS_MM_SndGmmCsLocalDetachInd(VOS_VOID)
{
    MMGMM_CS_LOCAL_DETACH_IND_STRU     *pstCsLocalDetachInd = VOS_NULL_PTR;            /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pstCsLocalDetachInd = (MMGMM_CS_LOCAL_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMGMM_CS_LOCAL_DETACH_IND_STRU));
    if ( VOS_NULL_PTR == pstCsLocalDetachInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndGmmCsLocalDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstCsLocalDetachInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCsLocalDetachInd->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstCsLocalDetachInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCsLocalDetachInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstCsLocalDetachInd->stMsgHeader.ulMsgName       = MMGMM_CS_LOCAL_DETACH_IND;/* 消息名称                                 */
    pstCsLocalDetachInd->stMsgHeader.ulLength
        = sizeof(MMGMM_CS_LOCAL_DETACH_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstCsLocalDetachInd);

    return;
}



VOS_VOID NAS_MM_SndGmmT3211ExpiredNotify(
    VOS_UINT8                           ucRejectCause
)
{
    MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU                  *pstT3211ExpiredNotify = VOS_NULL_PTR;            /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pstT3211ExpiredNotify = (MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU));

    if ( VOS_NULL_PTR == pstT3211ExpiredNotify)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndGmmT3211ExpiredNotify,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstT3211ExpiredNotify->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstT3211ExpiredNotify->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstT3211ExpiredNotify->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstT3211ExpiredNotify->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstT3211ExpiredNotify->stMsgHeader.ulMsgName       = MMGMM_T3211_TIMER_EXPIRED_NOTIFY;
    pstT3211ExpiredNotify->stMsgHeader.ulLength
        = sizeof(MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    pstT3211ExpiredNotify->ucRejectCause = ucRejectCause;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstT3211ExpiredNotify);

    return;
}




VOS_VOID NAS_MM_SndGmmCmSvcRejInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    MMGMM_CM_SERVICE_REJECT_IND_STRU   *pstCmSvcRejInd;

    /* 申请消息内存分配 */
    pstCmSvcRejInd    = (MMGMM_CM_SERVICE_REJECT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMGMM_CM_SERVICE_REJECT_IND_STRU));
    if ( VOS_NULL_PTR == pstCmSvcRejInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndGmmCmSvcRejInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstCmSvcRejInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCmSvcRejInd->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstCmSvcRejInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCmSvcRejInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstCmSvcRejInd->stMsgHeader.ulMsgName       = MMGMM_CM_SERVICE_REJECT_IND;  /* 消息名称                                 */
    pstCmSvcRejInd->stMsgHeader.ulLength
        = sizeof(MMGMM_CM_SERVICE_REJECT_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCmSvcRejInd->enCause = enCause;                                          /* 设置消息参数                             */

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstCmSvcRejInd);

    return;
}


VOS_VOID NAS_MM_SndGmmRegisterInit( VOS_VOID  )
{
    MMGMM_REGISTER_INITIATION_STRU          *pstMmRegisterInit;                   /* 定义原语类型指针                         */

    /* 申请消息内存分配 */
    pstMmRegisterInit  = (MMGMM_REGISTER_INITIATION_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_REGISTER_INITIATION_STRU));
    if ( VOS_NULL_PTR == pstMmRegisterInit)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndGmmRegisterInit,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMmRegisterInit->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmRegisterInit->MsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstMmRegisterInit->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmRegisterInit->MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMmRegisterInit->MsgHeader.ulMsgName       = MMGMM_REGISTER_INITIATION;    /* 消息名称                                 */
    pstMmRegisterInit->MsgHeader.ulLength
        = sizeof(MMGMM_REGISTER_INITIATION_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMmRegisterInit);

    return;
}


/* MM_GetNasInfo移至mmc */


VOS_VOID NAS_MM_SndTcRrRelInd(VOS_VOID)
{
    TCMM_RR_REL_IND_STRU               *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 申请消息 */
    pstMsg = (TCMM_RR_REL_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                                  sizeof(TCMM_RR_REL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndTcRrRelInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 封装消息 */
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TC;
    pstMsg->stMsgHeader.ulLength        = sizeof(TCMM_RR_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = TCMM_RR_REL_IND;

    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_MM, pstMsg);
    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_SndTcRrRelInd,WARNING: Message sends fail");
        return;
    }
}



VOS_VOID NAS_MM_SndMmcSimAuthFailInfo(
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16   enSimFailValue
)
{
    MMCMM_SIM_AUTH_FAIL_IND_STRU        *pstMsg              = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg  = (MMCMM_SIM_AUTH_FAIL_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_SIM_AUTH_FAIL_IND_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCMM_SIM_AUTH_FAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCMM_SIM_AUTH_FAIL_IND;
    pstMsg->ucReservel                  = 0;

    pstMsg->enSimAuthFailValue          = enSimFailValue;
    pstMsg->enSrvDomain                 = MM_COM_SRVDOMAIN_CS;

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}




VOS_VOID NAS_MM_SndRrMmServiceAbortNotify(
    VOS_UINT32                          ulReceiverPid
)
{
    RRMM_SERVICE_ABORT_NOTIFY_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_SERVICE_ABORT_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                        sizeof(RRMM_SERVICE_ABORT_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndRrMmServiceAbortNotify: memery alloc failed.");

        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName       = RRMM_SERVICE_ABORT_NOTIFY;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;

    PS_MEM_SET(pstMsg->aucReserve, 0, sizeof(pstMsg->aucReserve));

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MM, (struct MsgCB **)&pstMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndRrMmServiceAbortNotify: send message failed.");
    }

    return;
}





#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MM_SndLmmCsfbServiceStartNotify(VOS_VOID)
{
    MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU                  *pstMsg = VOS_NULL_PTR;
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enNasCsfbServiceStatus;/* 标识当前是否在CSFB流程 */
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32                    enLmmCsfbSrvType;

    enNasCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();
    NAS_MML_ConvertMmlCsfbStatusToLmmCsfbStatus(enNasCsfbServiceStatus, &enLmmCsfbSrvType);

#if (VOS_WIN32 == VOS_OS_VER)

    /* 申请内存 */
    pstMsg = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM,
                                               sizeof(MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndLmmCsfbServiceStartNotify():ERROR:MALLOC MEMORY FAILURE");
        return ;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MM;
    pstMsg->ulLength                    = sizeof(MM_LMM_CSFB_SERVICE_START_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MM_LMM_CSFB_SERVICE_START_NOTIFY;
    pstMsg->ulOpId                      = 0;
    pstMsg->enCsfbSrvType               = enLmmCsfbSrvType;

#if (VOS_WIN32 == VOS_OS_VER)

    /* 调用VOS发送原语 */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MM, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndLmmCsfbServiceStartNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MM_SndLmmCsfbServiceAbortNotify(VOS_VOID)
{
    MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU                  *pstMsg = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 申请内存 */
    pstMsg = (MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM,
                                               sizeof(MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndLmmCsfbServiceAbortNotify():ERROR:MALLOC MEMORY FAILURE");
        return ;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MM;
    pstMsg->ulLength                    = sizeof(MM_LMM_CSFB_SERVICE_ABORT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MM_LMM_CSFB_SERVICE_ABORT_NOTIFY;
    pstMsg->ulOpId                      = 0;

#if (VOS_WIN32 == VOS_OS_VER)

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MM, pstMsg );
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif
    return;
}


VOS_VOID NAS_MM_SndLmmHoSecuInfoReq(VOS_VOID)
{
    MM_LMM_HO_SECU_INFO_REQ_STRU       *pstMsg = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)

    /* 申请内存 */
    pstMsg = (MM_LMM_HO_SECU_INFO_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM,
                                               sizeof(MM_LMM_HO_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MM_LMM_HO_SECU_INFO_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MM_LMM_HO_SECU_INFO_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndLmmHoSecuInfoReq():ERROR:MALLOC MEMORY FAILURE");
        return ;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(MM_LMM_HO_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MM;
    pstMsg->ulLength                    = sizeof(MM_LMM_HO_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MM_LMM_HO_SECU_INFO_REQ;
    pstMsg->ulOpId                      = 0;

#if (VOS_WIN32 == VOS_OS_VER)

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MM, pstMsg );
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MM_SndLmmSrvccStatusNotify(
    NAS_MMCC_SRVCC_STATUS_ENUM_UINT32   enSrvccStatus
)
{
    MM_LMM_SRVCC_STATUS_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;
    MM_LMM_SRVCC_STATUS_ENUM_UINT32     enlmmSrvccStatus;

    NAS_MM_ConvertToLmmSrvccStatus(enSrvccStatus, &enlmmSrvccStatus);

#if (VOS_WIN32 == VOS_OS_VER)

    /* 申请内存 */
    pstMsg = (MM_LMM_SRVCC_STATUS_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM,
                                               sizeof(MM_LMM_SRVCC_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MM_LMM_SRVCC_STATUS_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MM_LMM_SRVCC_STATUS_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndLmmSrvccStatusNotify():ERROR:MALLOC MEMORY FAILURE");
        return ;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(MM_LMM_SRVCC_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MM;
    pstMsg->ulLength                    = sizeof(MM_LMM_SRVCC_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MM_LMM_SRVCC_STATUS_NOTIFY;
    pstMsg->ulOpId                      = 0;
    pstMsg->enSrvccStatus               = enlmmSrvccStatus;

#if (VOS_WIN32 == VOS_OS_VER)

    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MM, pstMsg );
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}



#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_MM_ConvertRrcSessionTypeToLmmFormat(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType,
    MM_LMM_SESSION_TYPE_ENUM_UINT8     *puclmmSessionType
)
{
    switch (enRrcSessionType)
    {
        case RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MO_NORMAL_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MO_EMERGENCY_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SS:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MO_SS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_SMS:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MO_SMS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MT_NORMAL_CALL:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MT_NORMAL_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MT_SMS:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MT_SMS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MT_SS:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MT_SS;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CSFB:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MO_NORMAL_CSFB;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CSFB:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MO_EMERGENCY_CSFB;
            break;

        case RRC_NAS_SESSION_TYPE_CS_MT_CSFB:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_MT_CSFB;
            break;

        case RRC_NAS_SESSION_TYPE_CS_LAU:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_LAU;
            break;

        case RRC_NAS_SESSION_TYPE_CS_DETACH:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_DETACH;
            break;

        default:
            *puclmmSessionType = MM_LMM_SESSION_TYPE_BUTT;
            break;
    }
    return;
}


VOS_VOID NAS_MM_SndLmmBeginSessionNotify(
    MM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
)
{
    MM_LMM_BEGIN_SESSION_NOTIFY_STRU                       *pstBeginSessionNotify = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)
    /* 申请内存 */
    pstBeginSessionNotify = (MM_LMM_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM,
                                               sizeof(MM_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstBeginSessionNotify = (MM_LMM_BEGIN_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MM_LMM_BEGIN_SESSION_NOTIFY_STRU));
#endif

    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndLmmBeginSessionNotify(): Alloc msg fail!");
        return;
    }

    /* 结构体清零 */
    PS_MEM_SET((VOS_INT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(MM_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造消息结构体 */
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstBeginSessionNotify->stMsgHeader.ulLength        = sizeof(MM_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBeginSessionNotify->stMsgHeader.ulMsgName       = ID_MM_LMM_BEGIN_SESSION_NOTIFY;

    pstBeginSessionNotify->enSessionType               = enSessionType;

    /* 调用VOS发送原语 */
#if (VOS_WIN32 == VOS_OS_VER)
    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MM, pstBeginSessionNotify);
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstBeginSessionNotify);
#endif

    return;
}


VOS_VOID NAS_MM_SndLmmEndSessionNotify(
    MM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
)
{
    MM_LMM_END_SESSION_NOTIFY_STRU                         *pstEndSessionNotify = VOS_NULL_PTR;

    /* 申请消息结构内存 */
#if (VOS_WIN32 == VOS_OS_VER)
    /* 申请内存 */
    pstEndSessionNotify = (MM_LMM_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM,
                                               sizeof(MM_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstEndSessionNotify = (MM_LMM_END_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MM_LMM_END_SESSION_NOTIFY_STRU));
#endif

    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndLmmEndSessionNotify(): Alloc msg fail!");
        return;
    }

    /* 结构体清零 */
    PS_MEM_SET((VOS_INT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(MM_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造消息结构体 */
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid     = WUEPS_PID_MM;
    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstEndSessionNotify->stMsgHeader.ulLength        = sizeof(MM_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstEndSessionNotify->stMsgHeader.ulMsgName       = ID_MM_LMM_END_SESSION_NOTIFY;

    pstEndSessionNotify->enSessionType               = enSessionType;

    /* 调用VOS发送原语 */
        /* 调用VOS发送原语 */
#if (VOS_WIN32 == VOS_OS_VER)
    /* 调用VOS发送原语 */
    PS_SEND_MSG( WUEPS_PID_MM, pstEndSessionNotify);
#else
    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstEndSessionNotify);
#endif

    return;
}

#endif


#endif


VOS_VOID NAS_MM_SndMmcSuspendRsp(VOS_VOID)
{
    MMCMM_SUSPEND_RSP_ST               *pstucMmMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstucMmMsg      = (MMCMM_SUSPEND_RSP_ST *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_SUSPEND_RSP_ST));

    if (VOS_NULL_PTR == pstucMmMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndMmcSuspendRsp,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstucMmMsg->MsgHeader.ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstucMmMsg->MsgHeader.ulSenderPid           = WUEPS_PID_MM;
    pstucMmMsg->MsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstucMmMsg->MsgHeader.ulReceiverPid         = WUEPS_PID_MMC;
    pstucMmMsg->MsgHeader.ulMsgName             = MMCMM_SUSPEND_RSP;
    pstucMmMsg->MsgHeader.ulLength              = sizeof(MMCMM_SUSPEND_RSP_ST) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstucMmMsg);

    return;
}


#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_MM_SndAsBeginSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    VOS_UINT32                          ulResult;
    RRMM_BEGIN_SESSION_NOTIFY_STRU     *pstBeginSessionNotify = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    pstBeginSessionNotify       = (RRMM_BEGIN_SESSION_NOTIFY_STRU*)PS_ALLOC_MSG(WUEPS_PID_MM,
                                                                        sizeof(RRMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndAsBeginSessionNotify(): Alloc msg fail!");
        return;
    }

    /* 结构体清零 */
    PS_MEM_SET((VOS_INT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(RRMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造消息结构体 */
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid       = WUEPS_PID_MM;
    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid     = ulReceiverPid;
    pstBeginSessionNotify->stMsgHeader.ulMsgName         = RRMM_BEGIN_SESSION_NOTIFY;
    pstBeginSessionNotify->enSessionType                 = enSessionType;

    /* 调用VOS发送原语 */
    ulResult = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MM, (struct MsgCB **)&pstBeginSessionNotify);

    if(VOS_OK != ulResult)
    {
        /* 发送失败 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MM_SndAsBeginSessionNotify():WARNING:MMC SEND AS BEGIN SESSION FAILED!");
        return;
    }

    return;
}


VOS_VOID NAS_MM_SndAsEndSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType,
    VOS_UINT32                          ulDelayTime
)
{
    VOS_UINT32                          ulResult;
    RRMM_END_SESSION_NOTIFY_STRU       *pstEndSessionNotify = VOS_NULL_PTR;

    /* 申请消息结构内存 */
    pstEndSessionNotify       = (RRMM_END_SESSION_NOTIFY_STRU*)PS_ALLOC_MSG(WUEPS_PID_MM,
                                                                        sizeof(RRMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndAsEndSessionNotify(): Alloc msg fail!");
        return;
    }

    /* 结构体清零 */
    PS_MEM_SET((VOS_INT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(RRMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 构造消息结构体 */
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid       = WUEPS_PID_MM;
    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid     = ulReceiverPid;
    pstEndSessionNotify->stMsgHeader.ulMsgName         = RRMM_END_SESSION_NOTIFY;
    pstEndSessionNotify->enSessionType                 = enSessionType;
    pstEndSessionNotify->enCsRelAll                    = VOS_FALSE;
    pstEndSessionNotify->enPsRelAll                    = VOS_FALSE;
    pstEndSessionNotify->ulDelayTime                   = ulDelayTime;

    /* 调用VOS发送原语 */
    ulResult = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MM, (struct MsgCB **)&pstEndSessionNotify);

    if(VOS_OK != ulResult)
    {
        /* 发送失败 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MM_SndAsEndSessionNotify():WARNING:MMC SEND AS END SESSION failed!");
        return;
    }

    return;
}


VOS_VOID NAS_MM_SndBeginSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
)
{
    TAF_CTRL_STRU                       stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType;

#if(FEATURE_ON == FEATURE_LTE)
    MM_LMM_SESSION_TYPE_ENUM_UINT8      enLmmSessionType;
#endif

    NAS_MML_SESSION_TYPE_ENUM_UINT8     enMmlSessionType;

    enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));

    /* 平台支持W/TD，发送end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        NAS_MM_SndAsBeginSessionNotify(WUEPS_PID_WRR, enRrcSessionType);
    }

    /* 平台支持G，发送end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_MM_SndAsBeginSessionNotify(UEPS_PID_GAS, enRrcSessionType);
    }

#if(FEATURE_ON == FEATURE_LTE)
    NAS_MM_ConvertRrcSessionTypeToLmmFormat(enRrcSessionType, &enLmmSessionType);

    /* 平台支持LTE，发送end session */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportLte() )
    {
        NAS_MM_SndLmmBeginSessionNotify(enLmmSessionType);
    }
#endif

    if(VOS_OK == NAS_ConvertSessionTypeToMTCFormat(enRrcSessionType, &enMtcSessionType))
    {
        /* 填写CTL头 */
        stCtrl.ulModuleId = WUEPS_PID_MM;

        MTC_SetBeginSessionInfo(&stCtrl,enMtcSessionType);
    }

    if ( (RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL    == enRrcSessionType)
      || (RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL == enRrcSessionType)
      || (RRC_NAS_SESSION_TYPE_CS_MO_SS             == enRrcSessionType)
      || (RRC_NAS_SESSION_TYPE_CS_MO_SMS            == enRrcSessionType) )
    {
        NAS_MM_ConvertToMmlSessionType(enRrcSessionType, &enMmlSessionType);
        NAS_MML_SetCsMoSessionSndFlag(enMmlSessionType, VOS_TRUE);
    }

    return;
}


VOS_VOID NAS_MM_SndEndSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
)
{
    TAF_CTRL_STRU                                           stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8                             enMtcSessionType;

    NAS_MML_DSDS_END_SESSION_DELAY_STRU                    *pstEndDelay = VOS_NULL_PTR;
    VOS_UINT32                                              ulDelayTime;
#if(FEATURE_ON == FEATURE_LTE)
    MM_LMM_SESSION_TYPE_ENUM_UINT8                          enLmmSessionType;
#endif

    NAS_MML_SESSION_TYPE_ENUM_UINT8                         enMmlSessionType;

    enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));
    pstEndDelay = NAS_MML_GetDsdsSessionEndDelay();

    if (RRC_NAS_SESSION_TYPE_CS_LAU == enRrcSessionType)
    {
        ulDelayTime = pstEndDelay->ulCsRegEndSessionDelayTime;
    }
    else
    {
        ulDelayTime = 0;
    }

    /* 平台支持W/TD，发送end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        NAS_MM_SndAsEndSessionNotify(WUEPS_PID_WRR, enRrcSessionType, ulDelayTime);
    }

    /* 平台支持G，发送end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_MM_SndAsEndSessionNotify(UEPS_PID_GAS, enRrcSessionType, ulDelayTime);
    }

#if(FEATURE_ON == FEATURE_LTE)
    NAS_MM_ConvertRrcSessionTypeToLmmFormat(enRrcSessionType, &enLmmSessionType);

    /* 平台支持LTE，发送end session */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportLte() )
    {
        NAS_MM_SndLmmEndSessionNotify(enLmmSessionType);
    }
#endif

    if(VOS_OK == NAS_ConvertSessionTypeToMTCFormat(enRrcSessionType, &enMtcSessionType))
    {
        /* 填写CTL头 */
        stCtrl.ulModuleId = WUEPS_PID_MM;

        MTC_SetEndSessionInfo(&stCtrl,enMtcSessionType);
    }

    if ( (RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL    == enRrcSessionType)
      || (RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL == enRrcSessionType)
      || (RRC_NAS_SESSION_TYPE_CS_MO_SS             == enRrcSessionType)
      || (RRC_NAS_SESSION_TYPE_CS_MO_SMS            == enRrcSessionType) )
    {
        NAS_MM_ConvertToMmlSessionType(enRrcSessionType, &enMmlSessionType);
        NAS_MML_SetCsMoSessionSndFlag(enMmlSessionType, VOS_FALSE);
    }

    return;
}


VOS_VOID NAS_MM_NotifySessionAccordingStateChg(
    VOS_UINT8                           ucCurState,
    VOS_UINT8                           ucTargetState
)
{
    if ( ucCurState == ucTargetState )
    {
        return;
    }

    if ( WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == ucCurState )
    {
        /* LAU建联失败，导致需要发送END SESSION NOTIFY */
        if ( LOCATION_UPDATING_INITIATED != ucTargetState )
        {
            NAS_MM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_CS_LAU);
        }

        /* LAU建联过程中，下发DETACH，建联成功之后，DETACH请求直接通过DATE_REQ上去 */
        if (IMSI_DETACH_INITIATED == ucTargetState)
        {
            /* IMSI_DETACH开始，不需要建联过程的，导致需要发送BEGIN SESSION NOTIFY */
            NAS_MM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_CS_DETACH);
        }
        return;
    }

    if ( LOCATION_UPDATING_INITIATED == ucCurState )
    {
        /* LAU完成，成功或者失败，均导致需要发送END SESSION NOTIFY */
        NAS_MM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_CS_LAU);

        /* LAU建联完成后，下发DETACH，DETACH请求直接通过建立的链接直接用DATE_REQ发上去 */
        if (IMSI_DETACH_INITIATED == ucTargetState)
        {
            /* IMSI_DETACH开始，不需要建联过程的，导致需要发送BEGIN SESSION NOTIFY */
            NAS_MM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_CS_DETACH);
        }

        return;
    }

    if ( LOCATION_UPDATING_INITIATED == ucTargetState )
    {
        /* LAU开始，均导致需要发送BEGIN SESSION NOTIFY */
        NAS_MM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_CS_LAU);

        return;
    }

    if ( WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == ucTargetState )
    {
        /* LAU开始，均导致需要发送BEGIN SESSION NOTIFY */
        NAS_MM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_CS_LAU);

        return;
    }

    if ( WAIT_FOR_RR_CONNECTION_IMSI_DETACH == ucCurState )
    {
        /* IMSI_DETACH建联失败，导致需要发送END SESSION NOTIFY */
        if ( IMSI_DETACH_INITIATED != ucTargetState )
        {
            NAS_MM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_CS_DETACH);
        }

        return;
    }

    if ( IMSI_DETACH_INITIATED == ucCurState )
    {
        /* IMSI_DETACH结束，导致需要发送END SESSION NOTIFY */
        NAS_MM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_CS_DETACH);

        return;
    }

    if ( WAIT_FOR_RR_CONNECTION_IMSI_DETACH == ucTargetState )
    {
        /* IMSI_DETACH开始，需要建联过程的，导致需要发送BEGIN SESSION NOTIFY */
        NAS_MM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_CS_DETACH);

        return;
    }

    if (IMSI_DETACH_INITIATED == ucTargetState)
    {
        /* IMSI_DETACH开始，不需要建联过程的，导致需要发送BEGIN SESSION NOTIFY */
        NAS_MM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_CS_DETACH);

        return;
    }

    return;
}


#endif



VOS_VOID NAS_MM_SndTransactionStatusNotify(
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTranStatus
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRcvPid;

    /* 获取接收pid */
    ulRet   = NAS_MM_GetRrcPidFromCurrRatType(&ulRcvPid);

    if (VOS_OK == ulRet)
    {
        NAS_MM_SndRrcTransactionStatusNotify(ulRcvPid, enTranStatus);
    }

    return;
}


VOS_VOID NAS_MM_SndAsCsTransactionStatus(
    RRC_NAS_CS_TRANSACTION_ENUM_UINT8   enCsTransactionStatus,
    VOS_UINT32                          ulSenderEnqPid,
    VOS_UINT8                           ucIsCallActive
)
{
    /* 定义原语类型指针 */
    RRMM_TRANSACTION_INFO_ANS_STRU     *pstAsMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /*申请消息  */
    pstAsMsg = (RRMM_TRANSACTION_INFO_ANS_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                      WUEPS_PID_MM,
                                      sizeof(RRMM_TRANSACTION_INFO_ANS_STRU));

    /* 内存申请失败 */
    if( VOS_NULL_PTR == pstAsMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndAsCsTransactionStatus():ERROR:Alloc Msg fail");
        return;
    }

    pstAsMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstAsMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MM;
    pstAsMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstAsMsg->MsgHeader.ulReceiverPid     = ulSenderEnqPid;

    /* 消息名称 */
    pstAsMsg->MsgHeader.ulMsgName                  = RRMM_TRANSACTION_INFO_ANS;
    pstAsMsg->stCsTransactInfo.enCsTransactionType = enCsTransactionStatus;
    pstAsMsg->stCsTransactInfo.ucIsCallActive      = ucIsCallActive;

    PS_MEM_SET(pstAsMsg->stCsTransactInfo.aucReserve1, 0, sizeof(pstAsMsg->stCsTransactInfo.aucReserve1));
    PS_MEM_SET(pstAsMsg->stPsTransactInfo.aucReserve1, 0, sizeof(pstAsMsg->stPsTransactInfo.aucReserve1));

    /* 调用VOS发送原语 */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_MM, (struct MsgCB **)&pstAsMsg);

    if(VOS_OK != ulRet)
    {
        /* 发送失败 */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_SndAsCsTransactionStatus():WARNING:MM SEND RRMM_TRANSACTION_INFO_ANS failed!");
        return;
    }

    /* 返回 */
    return;
}



VOS_UINT32 NAS_GetTransactionInfo(
    RRC_NAS_CS_TRANSACTION_INFO_STRU *pstCsTransactInfo,
    RRC_NAS_PS_TRANSACTION_INFO_STRU *pstPsTransactInfo
)
{
    RRC_NAS_CS_TRANSACTION_ENUM_UINT8                       enCsTransactionstatus;
    MMCC_CALL_INFO_STRU                                     astCallInfo[NAS_CC_MAX_ENTITY_NUM];
    VOS_UINT8                                               ucIsCallActive;
    VOS_UINT8                                               ucIndex;

    ucIsCallActive  = VOS_FALSE;

    /* 将NAS维护的CS标志类型转换为AS格式的CS状态标志 */
    NAS_MML_GetMmlCsTransactionStatus(&enCsTransactionstatus);

    /* 对MMCC_CALL_INFO_STRU初始化 */
    for (ucIndex = 0; ucIndex < NAS_CC_MAX_ENTITY_NUM; ucIndex++)
    {
        astCallInfo[ucIndex].enCallState = NAS_CC_CALL_STATE_BUTT;
        astCallInfo[ucIndex].enCallType  = NAS_CC_CALL_TYPE_BUTT;
        astCallInfo[ucIndex].ucCallId    = NAS_CC_INVALID_CALL_ID;
        astCallInfo[ucIndex].ucTi        = NAS_CC_INVALID_TI_VALUE;
    }

    /* 获取Call Info */
    NAS_CC_GetCallInfo(astCallInfo);

    /* 查询当前呼叫实体是否处于active状态 */
    for (ucIndex = 0; ucIndex < NAS_CC_MAX_ENTITY_NUM; ucIndex++)
    {
        if (NAS_CC_CALL_STATE_U10 == astCallInfo[ucIndex].enCallState)
        {
            ucIsCallActive = VOS_TRUE;
            break;
        }
    }

    if ( VOS_NULL_PTR != pstCsTransactInfo)
    {
        pstCsTransactInfo->enCsTransactionType = enCsTransactionstatus;
        pstCsTransactInfo->ucIsCallActive      = ucIsCallActive;
    }

    if ( VOS_NULL_PTR != pstPsTransactInfo)
    {
        PS_MEM_SET(pstPsTransactInfo->aucReserve1, 0, sizeof(pstPsTransactInfo->aucReserve1));
    }

    return VOS_OK;
}



VOS_VOID NAS_MM_SndRrcTransactionStatusNotify(
    VOS_UINT32                          ulRcvPid,
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTranStatus
)
{
    RRMM_TRANSACTION_STATUS_NOTIFY_STRU    *pstTranStatus = VOS_NULL_PTR;
    VOS_UINT32                              ulLength;

    ulLength = sizeof(RRMM_TRANSACTION_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    pstTranStatus = (RRMM_TRANSACTION_STATUS_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM, ulLength);

    if (VOS_NULL_PTR == pstTranStatus)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndRrcTransactionStatusNotify,ERROR:ALLOC MSG ERR!");

        return;
    }

    /* 初始化 */
    PS_MEM_SET((VOS_UINT8 *)pstTranStatus + VOS_MSG_HEAD_LENGTH, 0x0, ulLength);

    pstTranStatus->stMsgHeader.ulReceiverPid    = ulRcvPid;
    pstTranStatus->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstTranStatus->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstTranStatus->stMsgHeader.ulSenderPid      = WUEPS_PID_MM;
    pstTranStatus->stMsgHeader.ulLength         = ulLength;
    pstTranStatus->stMsgHeader.ulMsgName        = RRMM_TRANSACTION_STATUS_NOTIFY;
    pstTranStatus->enTransActionStatus          = enTranStatus;

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg( WUEPS_PID_MM, (struct MsgCB **)&pstTranStatus ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MM_SndRrcTransactionStatusNotify,ERROR:SEND MSG ERR!");
    }

    return ;

}



VOS_VOID NAS_MM_SndCcRrcConnectRelInd(VOS_VOID)
{
    MMCC_RRC_CONN_REL_IND_STRU         *pstMmccConnRelMsg;
    VOS_UINT32                          ulRst;

    pstMmccConnRelMsg = (MMCC_RRC_CONN_REL_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                                 sizeof(MMCC_RRC_CONN_REL_IND_STRU));
    if(VOS_NULL_PTR == pstMmccConnRelMsg)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MM_SndCcRrcConnectRelInd:ERROR: MALLOC ERROR!");
        return;
    }

    pstMmccConnRelMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMmccConnRelMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_CC;
    pstMmccConnRelMsg->stMsgHeader.ulMsgName         = MMCC_RRC_CONN_REL_IND;

    PS_MEM_SET(pstMmccConnRelMsg->aucRcv, 0x0, sizeof(pstMmccConnRelMsg->aucRcv));

    ulRst = PS_SEND_MSG(WUEPS_PID_MM, pstMmccConnRelMsg);
    if( VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MM_SndCcRrcConnectRelInd:ERROR: Send Message ERROR!");
        return;
    }
    return;
}


/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

