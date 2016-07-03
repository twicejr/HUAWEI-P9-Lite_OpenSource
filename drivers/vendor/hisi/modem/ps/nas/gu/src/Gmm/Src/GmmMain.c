
#include "GmmInc.h"
#include "psprimitive.h"
#include "GmmCasGlobal.h"
#include "GmmCasMain.h"
#include "GmmCasComm.h"
#include "GmmCasSuspend.h"
#include "GmmCasGsm.h"
#include "GmmCasSend.h"
#include "NasCommDef.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "GmmLmmInterface.h"
#include "NasGmmProcLResult.h"
#endif
#include "GmmMmInterface.h"
#include "NasMmcSndOm.h"
#include "GmmExt.h"
#include "NasGmmSndOm.h"
#include "NasUsimmApi.h"

#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_MAIN_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

NAS_GMM_CTRL_STATUS_ENUM_UINT8  gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;

/*lint -save -e958 */

/*******************************************************************************
  Module:      GMM_ReportN2MOtaMsg
  Function:    在trace中勾取GMM的空口消息
  Input:       NAS_MSG_STRU*   pNasMsg     SM空口消息
  NOTE:
  Return:      VOS_VOID
  History:
      1. 鲁琳    2009.07.11   新规作成
*******************************************************************************/
VOS_VOID GMM_ReportN2MOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "GMM_ReportN2MOtaMsg:NORMAL: msg type is ", pNasMsg->aucNasMsg[1]);

    switch(pNasMsg->aucNasMsg[1])
    {
        case GMM_MSG_ATTACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_ACCEPT;
            break;

        case GMM_MSG_ATTACH_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_REJECT;
            break;

        case GMM_MSG_DETACH_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_REQ_BY_NET;
            break;

        case GMM_MSG_DETACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_ACCEPT;
            break;

        case GMM_MSG_RAU_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_ACCEPT;
            break;

        case GMM_MSG_RAU_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_REJECT;
            break;

        case GMM_MSG_SERVICE_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_ACC;
            break;

        case GMM_MSG_SERVICE_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_REJ;
            break;

        case GMM_MSG_P_TMSI_REALLOCATION_COMMAND:
            usNasOtaMsyId = NAS_OTA_MSG_P_TMSI_REALLOCATION;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_REQ;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_REJ;
            break;

        case GMM_MSG_IDENTITY_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_IDENTITY_REQUEST;
            break;

        case GMM_MSG_GMM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_STATUS;
            break;

        case GMM_MSG_GMM_INFORMATION:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_INFORMATION;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_ReportN2MOtaMsg:WARNING: invalid msg type!");
            /*不属于GMM模块的空口消息，不在trace中显示*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_GMM, usNasOtaMsyId, NAS_OTA_DIRECTION_DOWN, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8 *)pNasMsg);
}


#ifdef __PS_WIN32_RECUR__



VOS_VOID  NAS_GMM_SetGmmSigFunc(VOS_VOID)
{
    g_GmmImportFunc.RrmmDataReqFunc  = As_RrDataReq;
    g_GmmImportFunc.RrmmEstReqFunc   = NAS_GMM_AsEstReq;
    g_GmmImportFunc.RrmmRelReqFunc   = As_RrRelReq;
}



VOS_UINT32 NAS_GMM_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                 *pstRcMsg;
    VOS_UINT32                                               ulExpectCount;
    VOS_UINT32                                               ulCount;
    VOS_UINT32                                               ulItemCount;
    VOS_UINT8                                               *pucDest;
    VOS_UINT8                                               *pucSrc;
    VOS_UINT32                                               ulDestLen;
    VOS_UINT32                                               ulMsgAddrForSm;

    ulExpectCount = 0;
    ulCount       = 0;
    ulItemCount   = 0;
    ulExpectCount = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8) /* gucGmmInitState */
                  + sizeof(VOS_UINT8)                      /* g_GmmInterRatCellReselect */
                  + sizeof(GMM_CAS_CTRL_STRU)              /* gstGmmCasGlobalCtrl */
                  + sizeof(GMM_SUSPEND_CTRL_STRU)          /* gstGmmSuspendCtrl */
                  + sizeof(GMM_GLOBAL_CTRL_STRU)           /* g_GmmGlobalCtrl */
                  + sizeof(GMM_TIMER_STRU)                 /* g_GmmTimerMng */
                  + sizeof(GMM_ATTACH_CTRL_STRU)           /* g_GmmAttachCtrl*/
                  + sizeof(GMM_RAU_CTRL_STRU)              /* g_GmmRauCtrl */
                  + sizeof(GMM_DOWNLINK_NPDU_STRU)         /* g_GmmDownLinkNpduBake */
                  + sizeof(GMM_DETACH_CTRL_STRU)           /* g_GmmDetachCtrl */
                  + sizeof(GMM_AUTHEN_CTRL_STRU)           /* g_GmmAuthenCtrl */
                  + sizeof(GMM_REQ_CNF_MNG_STRU)           /* g_GmmReqCnfMng */
                  + sizeof(GMM_SR_CTRL_STRU);              /* g_GmmServiceCtrl */

    pstRcMsg = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pMsg;
    pucSrc   = pstRcMsg->aucData;

    /* 解析总长度 */
    PS_MEM_CPY(&ulCount, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    if( ulExpectCount != ulCount )
    {
        return VOS_FALSE;
    }

    /* gucGmmInitState目标地址 */
    pucDest     = (VOS_UINT8 *)&gucGmmInitState;
    ulDestLen   = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmInterRatCellReselect目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmInterRatCellReselect;
    ulDestLen   = sizeof(g_GmmInterRatCellReselect);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* gstGmmCasGlobalCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&gstGmmCasGlobalCtrl;
    ulDestLen   = sizeof(GMM_CAS_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* gstGmmSuspendCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&gstGmmSuspendCtrl;
    ulDestLen   = sizeof(GMM_SUSPEND_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmGlobalCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmGlobalCtrl;
    ulDestLen   = sizeof(GMM_GLOBAL_CTRL_STRU);

    /*GTR运行时GMM保存的SM请求数据包为地址，而与实际回放时SM的请求包地址不同，所以不需要恢复该地址。*/
    ulMsgAddrForSm = g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = ulMsgAddrForSm;
    pucSrc += (ulItemCount);

    /* g_GmmTimerMng目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmTimerMng;
    ulDestLen   = sizeof(GMM_TIMER_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmAttachCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmAttachCtrl;
    ulDestLen   = sizeof(GMM_ATTACH_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmRauCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmRauCtrl;
    ulDestLen   = sizeof(GMM_RAU_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmDownLinkNpduBake目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmDownLinkNpduBake;
    ulDestLen   = sizeof(GMM_DOWNLINK_NPDU_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmDetachCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmDetachCtrl;
    ulDestLen   = sizeof(GMM_DETACH_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmAuthenCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmAuthenCtrl;
    ulDestLen   = sizeof(GMM_AUTHEN_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmReqCnfMng目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmReqCnfMng;
    ulDestLen   = sizeof(GMM_REQ_CNF_MNG_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmServiceCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmServiceCtrl;
    ulDestLen   = sizeof(GMM_SR_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RestoreContextData - data is restored.");

    NAS_GMM_SetGmmSigFunc();

    return VOS_TRUE;
}
#endif


VOS_VOID NAS_GMM_SndOutsideContextData()
{
    VOS_UINT8                                              *pucCompressBuf;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstPcreplayCompressCtx;
    VOS_UINT32                                              ulCompressDataLen;
    VOS_UINT32                                              ulCount;
    VOS_UINT8                                              *pucEndBuf;
    VOS_UINT32                                              ulItemCount;
    VOS_UINT8                                              *pucDest;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCmLen;

    ulCount     = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8) /* gucGmmInitState */
                + sizeof(VOS_UINT8)                      /* g_GmmInterRatCellReselect */
                + sizeof(GMM_CAS_CTRL_STRU)              /* gstGmmCasGlobalCtrl */
                + sizeof(GMM_SUSPEND_CTRL_STRU)          /* gstGmmSuspendCtrl */
                + sizeof(GMM_GLOBAL_CTRL_STRU)           /* g_GmmGlobalCtrl */
                + sizeof(GMM_TIMER_STRU)                 /* g_GmmTimerMng */
                + sizeof(GMM_ATTACH_CTRL_STRU)           /* g_GmmAttachCtrl*/
                + sizeof(GMM_RAU_CTRL_STRU)              /* g_GmmRauCtrl */
                + sizeof(GMM_DOWNLINK_NPDU_STRU)         /* g_GmmDownLinkNpduBake */
                + sizeof(GMM_DETACH_CTRL_STRU)           /* g_GmmDetachCtrl */
                + sizeof(GMM_AUTHEN_CTRL_STRU)           /* g_GmmAuthenCtrl */
                + sizeof(GMM_REQ_CNF_MNG_STRU)           /* g_GmmReqCnfMng */
                + sizeof(GMM_SR_CTRL_STRU);              /* g_GmmServiceCtrl */

    ulItemCount = 0;

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_GMM, ulCompressDataLen);

    if (VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM,"NAS_GMM_SndOutsideContextData: Alloc Fail.");
        return;
    }

    pstPcreplayCompressCtx = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pucCompressBuf;

    /* 获取buf结尾地址，用于计算剩余空间*/
    pucEndBuf = pucCompressBuf + ulCompressDataLen;
    pucDest   = pstPcreplayCompressCtx->aucData;

    /* 原始数据大小 */
    PS_MEM_CPY(pucDest, &ulCount, sizeof(VOS_UINT32));
    pucDest += sizeof(VOS_UINT32);

    /* 压缩gucGmmInitState*/
    pucSrc      = (VOS_UINT8 *)&gucGmmInitState;
    ulItemCount = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmInterRatCellReselect */
    pucSrc      = (VOS_UINT8 *)&g_GmmInterRatCellReselect;
    ulItemCount = sizeof(g_GmmInterRatCellReselect);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩gstGmmCasGlobalCtrl */
    pucSrc      = (VOS_UINT8 *)&gstGmmCasGlobalCtrl;
    ulItemCount = sizeof(GMM_CAS_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩gstGmmSuspendCtrl */
    pucSrc      = (VOS_UINT8 *)&gstGmmSuspendCtrl;
    ulItemCount = sizeof(GMM_SUSPEND_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmGlobalCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmGlobalCtrl;
    ulItemCount = sizeof(GMM_GLOBAL_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmTimerMng */
    pucSrc      = (VOS_UINT8 *)&g_GmmTimerMng;
    ulItemCount = sizeof(GMM_TIMER_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmAttachCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmAttachCtrl;
    ulItemCount = sizeof(GMM_ATTACH_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmRauCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmRauCtrl;
    ulItemCount = sizeof(GMM_RAU_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmDownLinkNpduBake */
    pucSrc      = (VOS_UINT8 *)&g_GmmDownLinkNpduBake;
    ulItemCount = sizeof(GMM_DOWNLINK_NPDU_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmDetachCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmDetachCtrl;
    ulItemCount = sizeof(GMM_DETACH_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);


    /* 压缩g_GmmAuthenCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmAuthenCtrl;
    ulItemCount = sizeof(GMM_AUTHEN_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmReqCnfMng */
    pucSrc      = (VOS_UINT8 *)&g_GmmReqCnfMng;
    ulItemCount = sizeof(GMM_REQ_CNF_MNG_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmServiceCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmServiceCtrl;
    ulItemCount = sizeof(GMM_SR_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCtx);

    pstPcreplayCompressCtx->ulReceiverPid      = WUEPS_PID_GMM;
    pstPcreplayCompressCtx->ulSenderPid        = WUEPS_PID_GMM;
    pstPcreplayCompressCtx->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCtx->ulMsgName          = EVT_NAS_GMM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;
    DIAG_TraceReport(pstPcreplayCompressCtx);

    PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);

    return;
}


VOS_VOID NAS_GMM_MsgProcAtStatusNull(
    struct MsgCB                        *pMsg
)
{
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_ADMIN == pMsgHeader->ulSenderPid)
     && (WUEPS_START_REQ == pMsgHeader->ulMsgName))
    {
        #ifdef __PS_WIN32_RECUR__
        Gmm_TaskInit();
        #endif

        gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;
    }

    return;
}


VOS_VOID NAS_GMM_MsgProcAtStatusStartup(
    struct MsgCB                        *pMsg
)
{
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_MMC == pMsgHeader->ulSenderPid)
     && (MMCGMM_START_REQ == pMsgHeader->ulMsgName))
    {
        Gmm_TaskInit();
        Gmm_RcvMmcStartReq();
        gucGmmInitState = NAS_GMM_CTRL_STATUS_INSERVICE;

        #ifndef __PS_WIN32_RECUR__


        if ( VOS_TRUE == NAS_MML_IsSndOmPcRecurMsgValid() )
        {
            NAS_GMM_SndOutsideContextData();
        }

        #endif
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_MsgProcAtStatusStartup:Receive message at state NAS_GMM_CTRL_STATUS_STARTUP.");

        if ((WUEPS_PID_SM == pMsgHeader->ulSenderPid)
            && (GMMSM_ESTABLISH_REQ == pMsgHeader->ulMsgName))
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_STARTUP);
        }
        else if ((WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
            && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else
        {

        }
    }

    return;
}


VOS_VOID NAS_GMM_RcvMmCsConnectInd_PreProc(
    VOS_VOID                           *pstRcvMsg                               /* 接收消息使用的头地址定义                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstMmCmServiceInd;                      /* 定义原语类型指针                         */

    pstMmCmServiceInd = (MMGMM_CS_CONNECT_IND_STRU *)pstRcvMsg;                   /* 强制类型转换                             */

    if (MMGMM_CS_CONNECT_ESTING == pstMmCmServiceInd->enCsConnectStatus)
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_TRUE;                         /* 置CS通信中为真                           */
    }
    else if (MMGMM_CS_CONNECT_EXIST == pstMmCmServiceInd->enCsConnectStatus)
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_TRUE;
    }
    else
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;                        /* 置CS通信中为假                           */
    }

    return;                                                                     /* 返回                                     */
}




VOS_UINT8 NAS_GMM_MsgProcAtStatusInService(
    struct MsgCB                        *pMsg
)
{
    VOS_UINT8                           ucFollowOn;
    REL_TIMER_MSG                       *pTimerMsg;
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
     && (MMCGMM_START_REQ == pMsgHeader->ulMsgName))
    {
        Gmm_RcvMmcStartReq();
        return VOS_TRUE;
    }

    if ((WUEPS_PID_MM         == pMsg->ulSenderPid)
     && (MMGMM_CS_CONNECT_IND == pMsgHeader->ulMsgName))
    {
        NAS_GMM_RcvMmCsConnectInd_PreProc(pMsg);
    }

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
     && (MMCGMM_ATTACH_REQ == pMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcAttachReq_PreProc((MMCGMM_ATTACH_REQ_STRU*)pMsg))
        {
            return VOS_TRUE;
        }
    }

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
    && (MMCGMM_DETACH_REQ == pMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcDetachReq_PreProc((MMCGMM_DETACH_REQ_STRU*)pMsg))
        {
            return VOS_TRUE;
        }
    }

    if (WUEPS_PID_SMS == pMsg->ulSenderPid)
    {
        if (GMMSMS_BEGIN_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmsBeginSessionNotify_PreProc((GMMSMS_BEGIN_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }

        if (GMMSMS_END_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmsEndSessionNotify_PreProc((GMMSMS_END_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }
    }

    if (WUEPS_PID_SM == pMsg->ulSenderPid)
    {
        if (GMMSM_BEGIN_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmBeginSessionNotify_PreProc((GMMSM_BEGIN_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }

        if (GMMSM_END_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmEndSessionNotify_PreProc((GMMSM_END_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;

        }
    }

    if ((WUEPS_PID_RABM == pMsg->ulSenderPid)
    && (ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ == pMsgHeader->ulMsgName))
    {
        NAS_GMM_RcvRabmMmlProcStatusQryReq((struct MsgCB *)pMsg);
        return VOS_TRUE;
    }

    if (RRMM_GMM_PROC_ENQ == pMsgHeader->ulMsgName)
    {
        if ( (WUEPS_PID_WRR == pMsgHeader->ulSenderPid)
          || (UEPS_PID_GAS == pMsgHeader->ulSenderPid) )
        {
            NAS_GMM_SndRrmmGmmProcAns();
        }

        return VOS_TRUE;
    }

    GMM_CasMsgProc(pMsg, &ucFollowOn);

    if (VOS_FALSE == ucFollowOn)
    {
        return VOS_FALSE;
    }

    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        pTimerMsg = (REL_TIMER_MSG*)pMsg;

        Gmm_RcvTimerExpired((VOS_UINT8)pTimerMsg->ulName);
    }
    else if (WUEPS_PID_ADMIN == pMsg->ulSenderPid)
    {
        if (WUEPS_RESET_REQ == pMsgHeader->ulMsgName)
        {
            gucGmmInitState = NAS_GMM_CTRL_STATUS_NULL;
        }
    }
    else
    {
        if (WUEPS_PID_GMM == pMsgHeader->ulReceiverPid)
        {
            Gmm_MsgDistribute((VOS_VOID*)pMsg);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_MsgProcAtStatusInService: The message is not GMM message.");
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}

VOS_VOID GmmMsgProc(
    struct MsgCB*                       pMsg
)
{
    VOS_UINT8                ucResult;

#ifdef __PS_WIN32_RECUR__
    if ((WUEPS_PID_GMM == pMsg->ulSenderPid)
     && (WUEPS_PID_GMM == pMsg->ulReceiverPid))
    {
        NAS_GMM_RestoreContextData(pMsg);
    }
#endif


    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    switch (gucGmmInitState)
    {
        case NAS_GMM_CTRL_STATUS_NULL:
            NAS_GMM_MsgProcAtStatusNull(pMsg);
            break;

        case NAS_GMM_CTRL_STATUS_STARTUP:
            NAS_GMM_MsgProcAtStatusStartup(pMsg);
            break;

        case NAS_GMM_CTRL_STATUS_INSERVICE:
            ucResult = NAS_GMM_MsgProcAtStatusInService(pMsg);
            if (VOS_FALSE == ucResult)
            {
                return;
            }
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "GmmMsgProc:WARNING: gucGmmInitState is Abnormal!");
            break;
    }
/*
#ifndef __PS_WIN32_RECUR__
    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif
*/
    return;
}


VOS_UINT8 Gmm_MsgDistribute_GMM_TC_ACTIVE(
    VOS_VOID                           *pRcvMsg                                 /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    MMCGMM_DETACH_REQ_STRU             *pstDetachReq = VOS_NULL_PTR;

    pstDetachReq  = (MMCGMM_DETACH_REQ_STRU *)pRcvMsg;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    if ((WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
        || (WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
        || (WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg from AGENT,RABM,SM or SMS is Abnormal when GMM is in GMM_TC_ACTIVE");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
        && (RRMM_REL_IND != pNasMsgHeader->ulMsgName)
        && (RRMM_DATA_IND != pNasMsgHeader->ulMsgName)
        && (RRMM_PAGING_IND != pNasMsgHeader->ulMsgName))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg except RRMM_REL_IND,RRMM_DATA_IND is Abnormal when GMM is in GMM_TC_ACTIVE");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
           &&(MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName))
    {
        /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }

    else if ( (WUEPS_PID_MMC     == pNasMsgHeader->ulSenderPid)
           && (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName) )
    {
        /* 判断等待Detach标志是否存在，如果存在则发送detach */
        if ( GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType )
        {
            Gmm_MsInitNormalDetach(pstDetachReq->enDetachType);
        }

        /* 当前DETACH消息不需要再进行处理 */
        ucRst = GMM_FALSE;
    }
    else if (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
    {
        ucRst = NAS_Gmm_IsValidMmcMsg_GmmTcActive(pRcvMsg);
    }
    else
    {
    }
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: GMM is in GMM_TC_ACTIVE");


    /* 收到接入层PS域连接释放消息时，通知TC连接释放 */
    if ( (WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
      && (RRMM_REL_IND == pNasMsgHeader->ulMsgName) )
    {
        NAS_GMM_SndTcRrRelInd();
    }

    /* 从MMC收到COVERAGE LOST消息时，通知TC连接释放 */
    if ( (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
      && (MMCGMM_COVERAGE_LOST_IND == pNasMsgHeader->ulMsgName) )
    {
        NAS_GMM_SndTcRrRelInd();
    }


    return ucRst;
}


VOS_UINT8 Gmm_MsgDistribute_GMM_NULL(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    if (WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
    {
        if(ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
        }
        ucRst = GMM_FALSE;
    }
    else if(WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
    {
        if(GMMSM_ESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_NULL);
        }
        ucRst = GMM_FALSE;
    }
    else if(WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
    {
        if(PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else if(PMMSMS_UNITDATA_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else
        {
        }
        ucRst = GMM_FALSE;
    }

    else if (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
    {
        ucRst = Gmm_MsgDistribute_ProcMmcMsg_GmmNull(pRcvMsg);
    }
    else if(WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg from AGENT or RRC is Abnormal when GMM is in GMM_NULL");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_TC == pNasMsgHeader->ulSenderPid)
        && (TCGMM_TEST_REQ != pNasMsgHeader->ulMsgName))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive TCGMM_TEST_REQ Msg is Abnormal when  is in GMM_NULL");
        ucRst = GMM_FALSE;
    }
    else
    {
    }

    return ucRst;
}


VOS_UINT8 Gmm_MsgDistribute_SpecProc_Handling(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    if (GMM_ABORT_CURRENT_SERVICE == g_GmmGlobalCtrl.ucSpecProc)
    {
        if (WUEPS_PID_MMC != pNasMsgHeader->ulSenderPid)
        {
            if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
                && (RRMM_REL_IND == pNasMsgHeader->ulMsgName))
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
            }
            else
            {
                ucRst = GMM_FALSE;
            }
        }
    }

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {
        if (WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
        {
            if(ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
            }
            ucRst = GMM_FALSE;
        }
        else if(WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
        {
            if(GMMSM_ESTABLISH_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);
            }
            ucRst = GMM_FALSE;
        }
        else if(WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
        {
            if(PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
            }
            else if(PMMSMS_UNITDATA_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
            }
            else
            {
            }
            ucRst = GMM_FALSE;
        }
        else if((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
            || (WUEPS_PID_TC == pNasMsgHeader->ulSenderPid))
        {
            if (MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName)
            {

                /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
                if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                         & GMM_WAIT_PS_ATTACH))
                {
                    NAS_GMM_SndMmcAttachCnf();
                }
                g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
            }

            ucRst = GMM_FALSE;
        }
        else if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
            && (RRMM_EST_CNF != pNasMsgHeader->ulMsgName)
            && (RRMM_REL_IND != pNasMsgHeader->ulMsgName))
        {
            ucRst = GMM_FALSE;
        }
        else
        {
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_Rat_Handling
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: 不同接入技术下消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_Rat_Handling(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {/* 2G网络模式 */
        /* 不处理WRRC消息和SMS消息 */
        if (WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
        {
            ucRst = GMM_FALSE;
        }
        else if (WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
        {
            if ((RRMM_EST_CNF != pNasMsgHeader->ulMsgName)
                && (RRMM_REL_IND != pNasMsgHeader->ulMsgName)
                && (RRMM_INTER_RAT_HANDOVER_INFO_CNF != pNasMsgHeader->ulMsgName))
            {
                ucRst = GMM_FALSE;
            }
        }
        else
        {
        }
    }
    else
    {/* 3G网络模式 */
        /* 不处理GAS消息和LLC消息 */
        if (UEPS_PID_LL == pNasMsgHeader->ulSenderPid)
        {
            ucRst = GMM_FALSE;
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_USIM
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: USIM消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_USIM(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case USIMM_AUTHENTICATION_CNF:
        Gmm_RcvAgentUsimAuthenticationCnf(pRcvMsg);                         /* AGENT_USIM_AUTHENTICATION_CNF接收处理    */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from USIM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_RRCF
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: RRCF消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_RRCF(
    VOS_VOID                            *pRcvMsg
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch (pNasMsgHeader->ulMsgName)
    {
    case RRMM_PAGING_IND:
        Gmm_RcvRrmmPagingInd(pRcvMsg);
        break;
    case RRMM_EST_CNF:
        Gmm_RcvRrmmEstCnf(pRcvMsg);
        break;
    case RRMM_DATA_IND:
        Gmm_RcvRrmmDataInd(pRcvMsg);
        break;
    case RRMM_REL_IND:
        Gmm_RcvRrmmRelInd(pRcvMsg);
        break;
    case RRMM_SECURITY_IND:
        Gmm_RcvRrmmSecurityInd(pRcvMsg);
        break;
    case RRMM_INTER_RAT_HANDOVER_INFO_CNF:
        NAS_GMM_RcvInterRatHandoverInfoCnf(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from RRC is ignored");
        break;
    }

    return;
}


VOS_VOID Gmm_MsgDistribute_From_RABM(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case ID_RABM_GMM_REESTABLISH_REQ:
        Gmm_RcvRabmReestablishReq(pRcvMsg);                                 /* GMMRABM_REESTABLISH_REQ接收处理          */
        break;
    case ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP:
        NAS_GMM_RcvGmmRabmRoutingAreaUpdateRsp(pRcvMsg);
        break;
    case ID_RABM_GMM_RAB_REL_IND:
        Gmm_RcvRabRelInd();                                                 /* RAB释放指示接收处理                      */
        break;

    case ID_RABM_GMM_RAB_SETUP_IND:
        NAS_GMM_RcvRabmRabSetupInd((GMMRABM_RAB_SETUP_IND_STRU *)pRcvMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from RABM is ignored");
        break;
    }

    return;
}


VOS_VOID Gmm_MsgDistribute_From_MMC(
    VOS_VOID                            *pRcvMsg                                /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case MMCGMM_SYS_INFO_IND:
        Gmm_RcvMmcSysInfoInd(pRcvMsg);                                      /* MMCGMM_SYS_INFO_IND接收处理              */

        NAS_GMM_SyncNasInfoChange_RegisteredStatus(RRC_NAS_MASK_SYNC_WRR);


        /* 如果此时GMM需要获取LMM的安全上下文,可能会启动定时器,此时这个标记应该暂时不清除
           待收到LMM的安全上下文的回复或者定时器超时后再清除 */
        if ( VOS_FALSE == NAS_GMM_GetLmmSecInfoFlg())
        {
            /* 需要获取安全上下文时,挂起前的接入技术延迟更新 */
            gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_WCDMA;

            g_GmmInterRatCellReselect = 0;
        }


        break;
    case MMCGMM_COVERAGE_LOST_IND:
        Gmm_RcvMmcCoverageLostInd();                                        /* MMCGMM_COVERAGE_LOST_IND接收处理         */
        break;
    case MMCGMM_POWER_OFF_REQ:
        Gmm_RcvMmcPowerOffReq(pRcvMsg);                                     /* MMCGMM_POWER_OFF_REQ接收处理             */
        break;

    case MMCGMM_PLMN_SEARCH_INITIATED:
        Gmm_RcvMmcPlmnSearchInitiated();                                    /* MMCGMM_PLMN_SEARCH_INITIATED接收处理     */
        break;
    case MMCGMM_START_REQ:
        Gmm_RcvMmcStartReq();                                               /* MMCGMM_START_REQ接收处理                 */
        break;
    case MMCGMM_PLMN_USER_SEL_REQ:
        Gmm_RcvMmcPlmnUserSelReq();                                         /* MMCGMM_PLMN_USER_SEL_REQ接收处理         */
        break;
    case MMCGMM_DETACH_REQ:
        Gmm_RcvMmcDetachReq(pRcvMsg);                                       /* MMCGMM_DETACH_REQ接收处理                */
        break;
    case MMCGMM_MODE_CHANGE_REQ:
        Gmm_RcvMmcGmmModeChangeReq(pRcvMsg);                                /* MMCGMM_MODE_CHANGE_REQ接收处理           */
        break;
    case MMCGMM_ATTACH_REQ:
        Gmm_RcvMmcGmmAttachReq(pRcvMsg);                                    /* MMCGMM_ATTACH_REQ接收处理                */
        break;
    case MMCGMM_GSM_SYS_INFO_IND:
        GMM_RcvGasSysInfoInd(pRcvMsg);



        NAS_GMM_SyncNasInfoChange_RegisteredStatus(RRC_NAS_MASK_SYNC_GAS);


        break;
    case MMCGMM_SUSPEND_IND:
        GMM_RcvMmcSuspendInd(pRcvMsg);
        break;
    case MMCGMM_RESUME_IND:
        GMM_RcvMmcResumeInd(pRcvMsg);
        break;
    case MMCGMM_REL_REQ:
        GMM_RcvMmcRelReq(pRcvMsg);
        break;
    case MMCGMM_W_AC_INFO_CHANGE_IND:
        NAS_GMM_RcvMmcWasAcInfoChgInd((NAS_MSG_STRU *)pRcvMsg);
        break;
#if (FEATURE_ON == FEATURE_LTE)
    case MMCGMM_LTE_SYS_INFO_IND:
        NAS_GMM_RcvMmcLteSysInfoInd((MMC_GMM_LTE_SYS_INFO_IND_STRU*)pRcvMsg);
        gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_LTE;
        break;

    case MMCGMM_LMM_ATTACH_IND:
        NAS_GMM_RcvLmmAttachResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_TAU_RESULT_IND:
        NAS_GMM_RcvLmmTauResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_MT_DETACH_IND:
        NAS_GMM_RcvLmmMtDetachInd((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_SERVICE_RESULT_IND:
        NAS_GMM_RcvLmmServiceResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_MO_DETACH_IND:
        NAS_GMM_RcvLmmMoDetachInd((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_LOCAL_DETACH_IND:
        NAS_GMM_RcvLmmLocalDetachInd((struct MsgCB*)pRcvMsg);
        break;


    case MMCGMM_LMM_STATUS_IND:
        NAS_GMM_RcvMmcLmmStatusInd((MMCGMM_LMM_STATUS_IND_STRU*)pRcvMsg);
        break;

    case MMCGMM_LMM_TIMER_STATE_NOTIFY:
        NAS_GMM_RcvLmmTimerStateNotify((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_EMERGENCY_NUM_LIST_IND:
        NAS_GMM_RcvMmcEmergencyNumList((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY:
        NAS_GMM_RcvMmcVoiceDomainChangeNotify((struct MsgCB*)pRcvMsg);
        break;
#endif

    default :
        NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: The Msg from MMC is ignored, MsgId: ", pNasMsgHeader->ulMsgName);
        break;
    }

    return;
}


VOS_VOID NAS_GMM_RcvSmAbortReq(
    VOS_VOID                            *pRcvMsg)
{
    NAS_GMM_ClearBufferedSmDataReq();
}


VOS_VOID Gmm_MsgDistribute_From_SM(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case GMMSM_ESTABLISH_REQ:
        Gmm_RcvSmEstablishReq(pRcvMsg);                                     /* GMMSM_ESTABLISH_REQ接收处理              */
        break;
    case GMMSM_DATA_REQ:
        Gmm_RcvSmDataReq(pRcvMsg);                                          /* GMMSM_DATA_REQ接收处理                   */
        break;
    case GMMSM_PDP_STATUS_IND:
        Gmm_RcvSmPdpStatusInd(pRcvMsg);                                     /* GMMSM_PDP_STATUS_IND接收处理             */
        break;
    case GMMSM_PDP_DEACTIVATED_IND:
        NAS_GMM_RcvSmPdpDeactivatedInd(pRcvMsg);
        break;

    case GMMSM_ABORT_REQ:
        NAS_GMM_RcvSmAbortReq(pRcvMsg);
        break;

    case GMMSM_PDP_MODIFY_IND:
        NAS_GMM_RcvSmPdpModifyInd(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from SM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_SMS
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: SMS消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_SMS(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case PMMSMS_EST_REQ:
        Gmm_RcvSmsEstReq(pRcvMsg);                                          /* PMMSMS_EST_REQ接收处理                   */
        break;
    case PMMSMS_UNITDATA_REQ:
        Gmm_RcvSmsUnitdataReq(pRcvMsg);                                     /* GMMSM_DATA_REQ接收处理                   */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from SMS is ignored");
        break;
    }

    return;
}


VOS_VOID Gmm_MsgDistribute_From_LL(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case ID_LL_GMM_STATUS_IND:                                                  /* 上报LLC状态信息 */
        GMM_CasCellS0E45(pRcvMsg);
        break;
    case ID_LL_UNITDATA_IND:                                                    /* 直传数据请求 */
        GMM_RcvLlcDataInd(pRcvMsg);
        break;

    case ID_LL_UNITDATA_CNF:                                                    /* 直传数据请求 */
        NAS_GMM_RcvLlcDataCnf(pRcvMsg);
        break;

    case ID_LL_DATA_INFORM :
        Gmm_RcvLLCInform(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from LLC is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_TC
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: TC消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_TC(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case TCGMM_DATA_REQ:
        Gmm_RcvTcDataReq(pRcvMsg);                                          /* TCGMM_DATA_REQ接收处理                   */
        break;
    case TCGMM_TEST_REQ:
        Gmm_RcvTcTestReq(pRcvMsg);                                          /* TCGMM_TEST_REQ接收处理                   */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from TC is ignored");
        break;
    }

    return;
}


VOS_VOID Gmm_MsgDistribute_From_GAS(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
        case GRRMM_PAGING_IND:                                                  /* GAS寻呼请求 */
            GMM_RcvGasPagingInd(pRcvMsg);
            break;
        case RRMM_GPRS_SUSPENSION_IND:                                          /* GAS GPRS挂起指示 */
            GMM_RcvGasSuspensionInd(pRcvMsg);
            break;
        case RRMM_GPRS_RESUME_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvGasGprsResumeInd(pRcvMsg);
            break;
        case RRMM_CELL_RESELECT_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvCellReselectInd(pRcvMsg);
            break;
        case GRRGMM_TBF_REL_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvGasTbfRleInd(pRcvMsg);
            break;

        case GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvGasRadioAccessCapa(pRcvMsg);
            break;

        case RRMM_CLASSMARK_CHANGE_IND:
            GMM_RcvGasClassMarkChangeInd(pRcvMsg);
            break;

        case GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvGasTdsRadioAccessCapa(pRcvMsg);
            break;

        case GRRGMM_GPRS_ACCESS_RESULT_IND:
            NAS_GMM_RcvGprsAccessResultInd(pRcvMsg);
            break;

        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from GAS is ignored");
            break;
    }

    return;
}

#if   (FEATURE_ON == FEATURE_LTE)


VOS_VOID NAS_GMM_RcvLmmReselSecInfoCnf(
    VOS_VOID                             *pRcvMsg
)
{
    LMM_GMM_RESEL_SECU_INFO_CNF_STRU     *pstMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8       enCurrRat;

    pstMsg = (LMM_GMM_RESEL_SECU_INFO_CNF_STRU *)pRcvMsg;

    Gmm_TimerStop(GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF);

    NAS_GMM_GetGUSecContextFromEpsSecContextInReselect((struct MsgCB *)pstMsg);

    enCurrRat   = NAS_MML_GetCurrNetRatType();

    /* 从L模获取映射的安全上下文之后，通知GU模 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA  == enCurrRat)
    {
        NAS_GMM_SndWasInfoChangeReq(RRC_NAS_MASK_MAPPED_SECURITY_KEY);
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM  == enCurrRat)
    {
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_MAPPED_SECURITY_KEY);
    }
    else
    {
    }

    /* 从L模获取安全上下文后，如果当前状态不是ATTACH_INIT或RAU_INIT，不发attach/rau req
       对应场景为:LTE限制服务，启available timer,重选到GU过程中available timer超时触发搜网，
       GMM状态更新为PLMN_SRCH,搜网与RAU流程冲突 */
    if ( (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
      || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState) )
    {
        if (NAS_GMM_SPEC_PROC_RAU == NAS_GMM_GetSpecProcNeedSecInfo())
        {
            Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        }
        else
        {
            Gmm_SndAttachReq();
        }

        /* 需要获取安全上下文时,挂起前的接入技术延迟更新 */
        gstGmmSuspendCtrl.ucPreRat = enCurrRat;
    }

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    g_GmmInterRatCellReselect = 0;


    gstGmmSuspendCtrl.ucGetLteSecContext = VOS_TRUE;

    NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_BUTT);

}

VOS_VOID NAS_GMM_RcvLmmHoSecInfoCnf(
    VOS_VOID                            *pRcvMsg
)
{
    LMM_GMM_HO_SECU_INFO_CNF_STRU       *pstMsg;

    pstMsg = (LMM_GMM_HO_SECU_INFO_CNF_STRU *)pRcvMsg;

    Gmm_TimerStop(GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

    NAS_GMM_GetGUSecContextFromEpsSecContextInHandOver((struct MsgCB *)pstMsg);

    /* 如果此时在GMM的挂起状态，而且挂起发起方为LTE，则向MMC回复挂起回复 */
    if ( (NAS_MML_NET_RAT_TYPE_LTE      == NAS_MML_GetCurrNetRatType())
      && (GMM_SUSPENDED_NORMAL_SERVICE  == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();
    }
}



VOS_VOID Gmm_MsgDistribute_From_Lmm(
    VOS_VOID *pRcvMsg
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch (pNasMsgHeader->ulMsgName)
    {
        case ID_LMM_GMM_RESEL_SECU_INFO_CNF:
            NAS_GMM_RcvLmmReselSecInfoCnf(pRcvMsg);
            break;

        case ID_LMM_GMM_HO_SECU_INFO_CNF:
            NAS_GMM_RcvLmmHoSecInfoCnf(pRcvMsg);
            break;

        default :
            break;
    }

    return;
}

#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)

VOS_VOID NAS_GMM_ProcMtcRrcAreaLostInd(VOS_VOID  *pstRcvMsg)
{

    /* svlte特性开启时ps从modem0迁移到modem1，设置全局变量，后续gmm收到
       detach ps请求直接进行本地detach以减少时间 */
    NAS_MML_SetPsLocalDetachFlag(VOS_TRUE);

    return;
}



VOS_VOID NAS_GMM_ProcMtcMsg(VOS_VOID  *pstRcvMsg)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pstRcvMsg;

    switch (pstNasMsgHeader->ulMsgName)
    {
        case ID_MTC_GMM_RRC_AREA_LOST_IND:
            NAS_GMM_ProcMtcRrcAreaLostInd(pstRcvMsg);
            break;

        default :
            NAS_INFO_LOG1(WUEPS_PID_GMM, "NAS_GMM_ProcMtcMsg: The Msg from MTC is ignored, MsgId: ", pstNasMsgHeader->ulMsgName);
            break;
    }

    return;
}

#endif




VOS_VOID Gmm_MsgDistribute_From_MM(
    VOS_VOID                           *pstRcvMsg                                /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pstNasMsgHeader = (MSG_HEADER_STRU *)pstRcvMsg;                                 /* 得到消息头                               */

    switch (pstNasMsgHeader->ulMsgName)
    {
        case MMGMM_LU_RESULT_IND:
            NAS_GMM_ProcMmLuResult(pstRcvMsg);
            break;

        case MMGMM_CS_CONNECT_IND:
            NAS_GMM_RcvMmCsConnectInd(pstRcvMsg);                               /* MMGMM_CS_CONNECT_IND接收处理            */
            break;
        case MMGMM_CM_SERVICE_REJECT_IND:
            NAS_GMM_RcvMmCmServiceRejectInd(pstRcvMsg);                         /* MMGMM_CM_SERVICE_REJECT_IND接收处理     */
            break;

        case MMGMM_AUTHENTICATON_FAILURE_IND:
            NAS_GMM_RcvMmAuthenticationFailureInd();                            /* MMCGMM_AUTHENTICATON_FAILURE_IND接收处理 */
            break;

        case MMGMM_REGISTER_INITIATION:
            Gmm_RcvMmRegisterInitiation(pstRcvMsg);                              /* MMCGMM_REGISTER_INITIATION接收处理       */
            break;

        case MMGMM_CS_LOCAL_DETACH_IND:
            NAS_Gmm_RcvMmCsLocalDetachInd(pstRcvMsg);                           /* MMGMM_CS_LOCAL_DETACH_IND接收处理 */
            break;


        case MMGMM_T3211_TIMER_EXPIRED_NOTIFY:
            NAS_Gmm_RcvMmT3211ExpiredNotify(pstRcvMsg);
            break;

        default :
            NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: The Msg from MMC is ignored, MsgId: ", pstNasMsgHeader->ulMsgName);
            break;
    }

    return;
}


VOS_VOID Gmm_MsgDistribute(
    VOS_VOID                            *pRcvMsg                                /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */
    if (WUEPS_PID_GMM != pNasMsgHeader->ulReceiverPid)
    {                                                                           /* ulDestTskId不是GMM                       */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_MsgDistribute: Receive PID is not GMM.");
        return;
    }

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        ucRst = Gmm_MsgDistribute_GMM_TC_ACTIVE(pRcvMsg);
        if(GMM_FALSE == ucRst)
        {
            return;
        }
    }

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        ucRst = Gmm_MsgDistribute_GMM_NULL(pRcvMsg);
        if(GMM_FALSE == ucRst)
        {
            return;
        }
    }

    ucRst = Gmm_MsgDistribute_SpecProc_Handling(pRcvMsg);
    if(GMM_FALSE == ucRst)
    {
        return;
    }

    ucRst = Gmm_MsgDistribute_Rat_Handling(pRcvMsg);
    if(GMM_FALSE == ucRst)
    {
        return;
    }

    switch (pNasMsgHeader->ulSenderPid)
    {                                                                           /* 根据message class分发消息                */
    case WUEPS_PID_USIM:                                                        /* AGENT发送给GMM                           */
        Gmm_MsgDistribute_From_USIM(pRcvMsg);
        break;

    case WUEPS_PID_WRR:                                                        /* RRC发送给GMM                             */
        Gmm_MsgDistribute_From_RRCF(pRcvMsg);
        break;

    case WUEPS_PID_RABM:                                                        /* RABM发送给GMM                            */
        Gmm_MsgDistribute_From_RABM(pRcvMsg);
        break;

    case WUEPS_PID_MMC:                                                         /* MMC发送给GMM                             */
        Gmm_MsgDistribute_From_MMC(pRcvMsg);
        break;

    case WUEPS_PID_MM:                                                         /* SMS发送给GMM                             */
        Gmm_MsgDistribute_From_MM(pRcvMsg);
        break;

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    case UEPS_PID_MTC:
        NAS_GMM_ProcMtcMsg(pRcvMsg);
        break;
#endif

    case WUEPS_PID_SM:                                                          /* SM发送给GMM                              */
        Gmm_MsgDistribute_From_SM(pRcvMsg);
        break;

    case WUEPS_PID_SMS:                                                         /* SMS发送给GMM                             */
        Gmm_MsgDistribute_From_SMS(pRcvMsg);
        break;

    case WUEPS_PID_TC:                                                        /* TC发送给GMM                              */
        Gmm_MsgDistribute_From_TC(pRcvMsg);
        break;

    case UEPS_PID_LL:                                                           /* LLC发送给GMM */
        Gmm_MsgDistribute_From_LL(pRcvMsg);
        break;

    case UEPS_PID_GAS:                                                          /* GRR发送给GMM */
        Gmm_MsgDistribute_From_GAS(pRcvMsg);
        break;

#if   (FEATURE_ON == FEATURE_LTE)
    case PS_PID_MM:                                                          /* GRR发送给GMM */
        Gmm_MsgDistribute_From_Lmm(pRcvMsg);
        break;
#endif

    default :
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: Receive Message from unexpected PID, PID : ", pNasMsgHeader->ulSenderPid);
        break;
    }

    return;
}


VOS_VOID Gmm_ComVariantInit(VOS_VOID)
{
    VOS_UINT8                           ucLen;
    VOS_UINT16                          usNonDrxTimerLen;
    VOS_UINT8                           aucDefaultRac[] = {0x15, 0x17, 0x73, 0x43, 0x2b, 0x25, 0x96, 0x62, 0x00,
                                                           0x42, 0x68, 0x8b, 0x19, 0x88, 0x01, 0x0b, 0xa2,
                                                           0x8c, 0x66, 0x20, 0x04, 0x00};
    NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU    stRelConnAfterPdpDeact;
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  ulLength;

    NAS_MML_PLMN_WITH_RAT_STRU                  stPlmnWithRat;

    stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnWithRat.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;


    usNonDrxTimerLen = 0;

    /* 将GMM的全局变量初期化为0 */
    Gmm_MemSet(&g_GmmGlobalCtrl, 0, sizeof(GMM_GLOBAL_CTRL_STRU));
    Gmm_MemSet(&g_GmmReqCnfMng,  0, sizeof(GMM_REQ_CNF_MNG_STRU));
    Gmm_MemSet(&g_GmmAttachCtrl, 0, sizeof(GMM_ATTACH_CTRL_STRU));
    Gmm_MemSet(&g_GmmRauCtrl,    0, sizeof(GMM_RAU_CTRL_STRU));
    Gmm_MemSet(&g_GmmDetachCtrl, 0, sizeof(GMM_DETACH_CTRL_STRU));
    Gmm_MemSet(&g_GmmAuthenCtrl, 0, sizeof(GMM_AUTHEN_CTRL_STRU));
    Gmm_MemSet(&g_GmmServiceCtrl,0, sizeof(GMM_SR_CTRL_STRU));
    Gmm_MemSet(&g_MmSubLyrShare.GmmShare, 0, sizeof(GMM_SHARE_STRU));
    Gmm_MemSet(&g_GmmInterRatInfoCtrl, 0, sizeof(GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU));

    g_GmmTimerMng.ulTimerRunMask             = 0;
    g_GmmTimerMng.ulTimerSusMask             = 0;
    g_GmmTimerMng.ulTimerValMask             = 0;
    g_GmmTimerMng.ulTimerRunMaskEx           = 0;
    g_GmmTimerMng.ulTimerSusMaskEx           = 0;
    g_GmmTimerMng.ulTimerValMaskEx           = 0;    
    g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;

    GMM_InitCasGlobalVariable();

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());

    NAS_GMM_SetAllocT3302ValuePlmnWithRat(&stPlmnWithRat);

    g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg  = GMM_SUPPORT_INFORMATION_MSG;


    /* 从GAS维护的NV项中读取nonDRXTimer值 */
    if(NV_OK != NV_Read (en_NV_Item_GPRS_Non_Drx_Timer_Length, &usNonDrxTimerLen, sizeof(VOS_UINT16)))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_ComVariantInit():en_NV_Item_GPRS_Non_Drx_Timer_Length Error");
        usNonDrxTimerLen = 0;
    }

    NAS_MML_SetNonDrxTimer((VOS_UINT8)usNonDrxTimerLen);



    g_GmmGlobalCtrl.ucRelConnAfterPdpDeact = VOS_FALSE;
    PS_MEM_SET(&stRelConnAfterPdpDeact, 0x00, sizeof(NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU));

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT, &ulLength);
    if (ulLength > sizeof(stRelConnAfterPdpDeact))
    {
        return;
    }
    ulResult = NV_Read(en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT,
                       &stRelConnAfterPdpDeact,
                       ulLength);

    if (NV_OK == ulResult)
    {
        g_GmmGlobalCtrl.ucRelConnAfterPdpDeact = stRelConnAfterPdpDeact.ucRelFlg;
    }

    /*这里将记录上次attach或RAU是否携带Drx参数的变量enLatestAttachOrRauContainDrx 初始化*/
    g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx = NAS_MML_PS_REG_CONTAIN_BUTT;

    g_GmmGlobalCtrl.ucSuspendProc                = GMM_FALSE;
    g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult   = RRC_NAS_EST_RESULT_BUTT;
    Gmm_TimerStop(GMM_TIMER_ALL);

    g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;

    g_GmmInterRatCellReselect = 0;
    g_GmmGlobalCtrl.ucEventCause = GMM_EVENT_CAUSE_INVALID;
    /* 初始化为没有收到网侧detach消息 */
    g_GmmGlobalCtrl.ucRcvNetDetachFlg = VOS_FALSE;

    g_GmmGlobalCtrl.ucIsNeedStartT3340PdpExist = VOS_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
    /* 默认支持L能力 */
    g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs     = (VOS_UINT8)NAS_MML_IsSupportLteCapability();
    g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq = (VOS_UINT8)NAS_MML_IsSupportLteCapability();
    g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq          = NAS_MML_GetVoiceDomainPreference();
#endif

    /* 给RAC赋初始值 */
    ucLen = aucDefaultRac[0] + 1;
    PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucRadioCpb, aucDefaultRac, ucLen);

    /* 给RAC赋初始值 */
    ucLen = aucDefaultRac[0] + 1;
    PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb, aucDefaultRac, ucLen);

    /* 初始化3311定时器未超时 */
    g_GmmRauCtrl.ucT3311ExpiredFlg  = GMM_FALSE;

    return;
}


VOS_VOID Gmm_TaskInit(VOS_VOID)
{
    VOS_UINT8 i;

    Gmm_MemSet(&g_GmmTimerMng, 0, sizeof(GMM_TIMER_STRU));

    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3310].ulTimerVal = GMM_TIMER_T3310_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3311].ulTimerVal = GMM_TIMER_T3311_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3312].ulTimerVal = GMM_TIMER_T3312_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3316].ulTimerVal = GMM_TIMER_T3316_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3317].ulTimerVal = GMM_TIMER_T3317_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3318].ulTimerVal = GMM_TIMER_T3318_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3319].ulTimerVal = GMM_TIMER_T3319_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3320].ulTimerVal = GMM_TIMER_T3320_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3321].ulTimerVal = GMM_TIMER_T3321_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3330].ulTimerVal = GMM_TIMER_T3330_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_1S   ].ulTimerVal = GMM_TIMER_1S_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_DETACH_FOR_POWER_OFF].ulTimerVal = GMM_TIMER_DETACH_FOR_POWER_OFF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_PS_DETACH].ulTimerVal = GMM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;

    /* GCF测试,关机detach定时器时长为8S */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_DETACH_FOR_POWER_OFF].ulTimerVal = GMM_TIMER_DETACH_FOR_GCF_POWER_OFF_VALUE;
    }

    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT].ulTimerVal
            = GMM_TIMER_PROTECT_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_FOR_SIGNALING].ulTimerVal
            = GMM_TIMER_PROTECT_FOR_SIGNALING_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_SUSPENDED].ulTimerVal
            = GMM_TIMER_SUSPENDED_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_RAU_RSP].ulTimerVal
            = GMM_TIMER_RAU_RSP_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_OLD_TLLI].ulTimerVal
            = GMM_TIMER_PROTECT_OLD_TLLI_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF].ulTimerVal = GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF].ulTimerVal = GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF].ulTimerVal    = GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_CONNECT_REL].ulTimerVal    = GMM_TIMER_WAIT_CONNECT_REL_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_TC_DELAY_SUSPEND_RSP].ulTimerVal = GMM_TIMER_TC_DELAY_SUSPEND_RSP_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3323].ulTimerVal = GMM_TIMER_T3323_VALUE;


    /* GMM HO到GU后等系统消息的时长 */
    g_GmmTimerMng.aTimerInf[GMM_TIMER_HO_WAIT_SYSINFO].ulTimerVal = GMM_TIMER_WAIT_SYSINFO_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU].ulTimerVal = GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU_VALUE;


    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO].ulTimerVal = GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU].ulTimerVal = GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_PS_SMS_CONN_REL].ulTimerVal    = GMM_TIMER_DELAY_PS_SMS_CONN_REL_VALUE;
    
    for (i = 0; i < GMM_TIMER_NUM; i++)
    {
        g_GmmTimerMng.aTimerInf[i].ucMode = VOS_RELTIMER_NOLOOP;
        g_GmmTimerMng.aTimerInf[i].hTimer = VOS_NULL_PTR;
    }
    g_GmmImportFunc.RrmmDataReqFunc  = As_RrDataReq;
    g_GmmImportFunc.RrmmEstReqFunc   = NAS_GMM_AsEstReq;
    g_GmmImportFunc.RrmmRelReqFunc   = As_RrRelReq;

    Gmm_MemSet(&gstGmmSuspendCtrl, 0x0, sizeof(GMM_SUSPEND_CTRL_STRU));

    gstGmmSuspendCtrl.ucPreRat                    = NAS_MML_NET_RAT_TYPE_WCDMA;
    gstGmmSuspendCtrl.ucRauCause                  = GMM_RAU_FOR_NORMAL;
    gstGmmSuspendCtrl.ucT3312State                = GMM_T3312_NOT_TIMEOUT;
    gstGmmSuspendCtrl.ucNetModeChange             = GMM_FALSE;
    gstGmmSuspendCtrl.ucPowerOff                  = GMM_POWER_OFF_NOT_RCV;

    gstGmmSuspendCtrl.ucGetLteSecContext          = VOS_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_GMM_SetLteGutiValid(VOS_TRUE);
#endif

    Gmm_ComVariantInit();

    return;
}


MMCGMM_DETACH_REQ_STRU* NAS_GMM_MakeDetachMsg( VOS_UINT32  ulDetachCause )
{

    MMCGMM_DETACH_REQ_STRU* pSndMsg = VOS_NULL_PTR;                                     /* 定义原语类型指针                         */

    /*申请消息  */
    pSndMsg = (MMCGMM_DETACH_REQ_STRU*)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));

    if ( VOS_NULL_PTR == pSndMsg )
    {                                                                           /* 内存申请失败                             */
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mmc_SndGmmDetachReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_NULL_PTR;                                                                 /* 返回                                     */
    }

    Gmm_MemSet(pSndMsg, 0x00, sizeof(MMCGMM_DETACH_REQ_STRU));

    pSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pSndMsg->MsgHeader.ulLength          = sizeof(MMCGMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别                             */
    pSndMsg->MsgHeader.ulMsgName   = MMCGMM_DETACH_REQ;                         /* 填写消息名称                             */

    pSndMsg->enDetachType          = ulDetachCause;

    return pSndMsg;

}

VOS_VOID NAS_GMM_RcvSmPdpModifyInd(VOS_VOID *pRcvMsg)
{
#if (FEATURE_LTE == FEATURE_ON)
    GMMSM_PDP_MODIFY_IND_STRU          *pSmPdpModifyInd;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enCurrTinType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    VOS_UINT8                           ucNsapi;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pSmPdpModifyInd = (GMMSM_PDP_MODIFY_IND_STRU *)pRcvMsg;
    ucNsapi         =  pSmPdpModifyInd->ucNsapi;
    enCurrTinType   =  NAS_MML_GetTinType();
    enCurrRatType   =  NAS_MML_GetCurrNetRatType();
    pstRplmnCfgInfo =  NAS_MML_GetRplmnCfg();

    /* 3GPP 24008 6.3  Coordination between SM and GMM for supporting ISR章节描述：
       This subclause applies to a MS with its TIN set as "RAT related TMSI" for which ISR is activated.
       The MS shall change its TIN to "P-TMSI" to deactivate ISR:
       -   upon modification of any PDP context which was activated before the ISR is activated in the MS
    */
    if ((VOS_TRUE == NAS_MML_IsPsBearerExistBeforeIsrAct(ucNsapi))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enCurrTinType)
     && (NAS_MML_NET_RAT_TYPE_LTE != enCurrRatType))
    {
        NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }
#endif
    return;
}


VOS_VOID NAS_GMM_RcvSmPdpDeactivatedInd(VOS_VOID *pRcvMsg)
{
    GMMSM_PDP_DEACTIVATED_IND_STRU     *pSmPdpStatusInd;
    MMCGMM_DETACH_REQ_STRU             *ptr;
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8      enCurRat;

#if (FEATURE_LTE == FEATURE_ON)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    enCurRat = NAS_MML_GetCurrNetRatType();

    pstConnStatus   = NAS_MML_GetConnStatus();

    pSmPdpStatusInd = (GMMSM_PDP_DEACTIVATED_IND_STRU *)pRcvMsg;

    /* 没有短信时,清除follow on标志 */
    if (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    }


    /* 若以前有缓存消息,则释放掉，在TD下内部list搜时候，如果用户发起PDP激活，
       此时虽然ulMsgHoldMsk为空，但仍缓存了PS SERVICE标识，所以需要清楚掉 */
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvSmPdpDeactivatedInd(): Clear cached SM Data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }


    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        /* pSmPdpStatusInd->ulPdpContextStatus中仅用到了低十六位 */
        if (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
        {
            /* 已经没有激活的PDP */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                   "NAS_GMM_RcvSmPdpDeactivatedInd:Normal: Service is CS ONLY,Detach PS");

            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );

            /* 根据GMM状态做去注册还是做本地去注册 */
            if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
             || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
            {
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;

                ptr = NAS_GMM_MakeDetachMsg(NAS_MSCC_PIF_DETACH_TYPE_GPRS);

                if (VOS_NULL_PTR == ptr)
                {
                    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcDetachReq:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                    return;
                }
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)ptr;
            }
            else if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
            {
                Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
            }
            else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
                && (GMM_RRC_RRMM_EST_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
                {                                                               /* 无信令且正在建立信令连接                 */
                    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;

                    ptr = NAS_GMM_MakeDetachMsg(NAS_MSCC_PIF_DETACH_TYPE_GPRS);

                    if (VOS_NULL_PTR == ptr)
                    {
                        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcDetachReq:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                        return;
                    }
                    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)ptr;
                }
                else
                {
                    Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
                }
            }
            else if ((GMM_REGISTERED_PLMN_SEARCH== g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState))
            {   /* 本地将GMM状态迁到未注册状态,如果是出服务区则LL已经被挂起,进服务区时若t3312未超时
                   是否需要发起DETACH,待定*/
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
                NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );


                /* 通知GMM当前PS域DETACH完成 */
                NAS_GMM_SndMmGprsDetachComplete();

                Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);

                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    Gmm_TimerStop(GMM_TIMER_T3314);
                    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

                    /* default 44s */
                    gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif
                    Gmm_TimerStop(GMM_TIMER_T3312);
                    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);

                }
            }
            else
            {
            }
        }
    }


    /* W下PDP去激活且GMM处于正常服务状态或GMM_SERVICE_REQUEST_INITIATED且没有短信业务时需要启T3340,
       等待RRC链路释放,期间收到的PDP激活请求GMM将缓存等PDP去激活链路释放后再发起 */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
     && (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
     && (VOS_TRUE == g_GmmGlobalCtrl.ucRelConnAfterPdpDeact))
    {
        if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
         || ((GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
          && (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)))
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_WAIT_REL_PS_SIGNAL_VALUE;
            Gmm_TimerStart(GMM_TIMER_T3340);
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
        }
    }

    if ((VOS_FALSE == pstConnStatus->ucPsTbfStatusFlg)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        Gmm_SndMmcTBFRelInd();
    }

    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
    {
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (NAS_MML_NET_RAT_TYPE_LTE != enCurRat))
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
            Gmm_TimerStop(GMM_TIMER_T3323);

            /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
    }
#endif

    return;
}


VOS_VOID Gmm_RcvSmPdpStatusInd(
                           VOS_VOID *pRcvMsg                                    /* 接收消息使用的头地址定义                 */
                           )
{
    GMMSM_PDP_STATUS_IND_STRU          *pSmPdpStatusInd;                        /* 定义GMMSM_PDP_STATUS_IND_STRU类型指针    */
    VOS_UINT8                           ucPrePdpStatusFlg;                      /* 原来是否存在激活的PDP context标志        */
    VOS_UINT8                           ucCurPdpStatusFlg;                      /* 当前是否存在激活的PDP context标志        */
    NAS_MML_PS_BEARER_CONTEXT_STRU      stPsBearCtx;
    VOS_UINT32                          i;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();


    PS_MEM_SET(&stPsBearCtx, 0x00, sizeof(stPsBearCtx));

    ucCurPdpStatusFlg = MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST;

    pSmPdpStatusInd = (GMMSM_PDP_STATUS_IND_STRU *)pRcvMsg;                     /* 得到消息指针                             */

    ucPrePdpStatusFlg = pstConnStatus->ucPdpStatusFlg;

    /* 根据消息中pdp状态更新MML中全局变量 g_stNasMmlCtx.stNetworkInfo.astPsBearerContext*/
    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        stPsBearCtx.enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
        stPsBearCtx.enPsBearerState  = NAS_MML_PS_BEARER_STATE_INACTIVE;
        stPsBearCtx.ucPsActPending   = VOS_FALSE;
        stPsBearCtx.ucPsDeactPending = VOS_FALSE;

        if (GMMSM_PDP_STATE_ACTIVE == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.enPsBearerState = NAS_MML_PS_BEARER_STATE_ACTIVE;
            ucCurPdpStatusFlg           = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;

            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                stPsBearCtx.enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_AFTER_ISR_ACT;
            }
        }
        else if (GMMSM_PDP_STATE_ACTIVE_PENDING == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.ucPsActPending  = VOS_TRUE;
            ucCurPdpStatusFlg           = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;
        }
        else if (GMMSM_PDP_STATE_INACTIVE_PENDING == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.ucPsDeactPending = VOS_TRUE;
            ucCurPdpStatusFlg            = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;
        }
        else
        {
        }

        /* 驻留在L,由L更新pdp状态 */
        if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SetPsBearerCtx((VOS_UINT8)(i + NAS_MML_MIN_NSAPI), &stPsBearCtx);
        }
        /* LTE下时,只需要更新状态为PENDING的PDP状态 */
        else
        {
            NAS_Gmm_ClearPendingPdpStatus();
        }

    }

    if ( MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST == ucCurPdpStatusFlg)
    {
        pstConnStatus->ucPdpStatusFlg       = VOS_FALSE;
    }
    else
    {
        pstConnStatus->ucPdpStatusFlg       = VOS_TRUE;
    }

    if (ucPrePdpStatusFlg != pstConnStatus->ucPdpStatusFlg)
    {                                                                           /* PDP CONTEXT状态变化                      */
        Gmm_SndMmcPdpStatusInd(ucCurPdpStatusFlg);                              /* 通知MMC最新的PDP CONTEXT状态             */
    }

    /* PDP去激活后，通知LL和GRM清除缓存的用户和信令面数据 */
    if(MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST == ucCurPdpStatusFlg)
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_USER);
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_GMM_ConvertSmSessionTypeToRrc(
    GMMSM_SESSION_TYPE_ENUM_UINT8       enGmmSmSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *pucRrcSessionType
)
{
    switch (enGmmSmSessionType)
    {
        case GMMSM_SESSION_TYPE_CONVERSAT_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL;
            break;

        case GMMSM_SESSION_TYPE_STREAM_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_STREAM_CALL;
            break;

        case GMMSM_SESSION_TYPE_INTERACT_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL;
            break;

        case GMMSM_SESSION_TYPE_BACKGROUND_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL;
            break;

        case GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL;
            break;

        default:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }
    return;
}
#endif


VOS_VOID NAS_GMM_RcvSmBeginSessionNotify_PreProc(
    GMMSM_BEGIN_SESSION_NOTIFY_STRU    *pstBeginSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSM_SESSION_TYPE_BUTT != pstBeginSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmSessionTypeToRrc(pstBeginSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndBeginSessionNotify(enRrcSessionType);
    }
#endif     

    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_START);

    return;
}


VOS_VOID NAS_GMM_RcvSmEndSessionNotify_PreProc(
    GMMSM_END_SESSION_NOTIFY_STRU      *pstEndSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSM_SESSION_TYPE_BUTT != pstEndSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmSessionTypeToRrc(pstEndSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndEndSessionNotify(enRrcSessionType);
    }
#endif 

    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_FINISH);

    return;
}




VOS_VOID Gmm_ComPlmnSearchInit()
{
    if (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
    {
        /* 当前不为PS域卡无效 */
        if (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);                        /* 调用状态的公共处理                       */
            if (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
            {
                Gmm_TimerStop(GMM_TIMER_T3311);

            }
        }
    }
    else if ((0x20 == (g_GmmGlobalCtrl.ucState & 0xF0))
        && (GMM_REGISTERED_IMSI_DETACH_INITIATED != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
        && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
        && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM != g_GmmGlobalCtrl.ucPlmnSrchPreSta))
    {                                                                           /* REGISTERED状态下且非流程中               */
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);                              /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_T3311);

    }

    else if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }


        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }

    else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {   /*只有用户发起的detach过程才会进入GMM_DEREGISTERED_INITIATED*/
        /*不需要判断当前detach类型*/
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }

        else if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }
        else
        {

        }

        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }

    else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }

        if (GMM_MSG_HOLD_FOR_RAU
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
        {                                                                       /* 如果有保留的RAU原语                      */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;      /* 清除缓存标志                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau);   /* 读取RAU原语地址                          */
        }
        Gmm_ComCnfHandle();
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }

        Gmm_ComCnfHandle();
    }
    else if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_SUSPENDED);

        g_GmmRauCtrl.ucNpduCnt = 0x0;
        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        }
        else
        {
#if 0
            GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                           GMM_RABM_IMMEDIATELY_RAU);
#endif

            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        }
        GMM_BufferMsgDump();

        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }
    else if ( GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState )
    {
        /* 签到搜网状态 */
        if ( (0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
          || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState) )
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
        }

        /* GSM下的系统消息初始化 */
        NAS_GMM_FreeGsmSysInfo();

        /* 缓存内容的处理 */
        GMM_BufferMsgResume();
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* 清所有等待cnf                            */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清除当前流程                             */
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清除保留的过程                           */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;                   /* 清除记录的CS通信中流程                   */

}



VOS_VOID Gmm_RcvMmcPlmnUserSelReq(VOS_VOID)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_VOID            *pAddr;

    if (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* 判断是否有信令存在                       */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                   /* 释放信令                                 */
    }

    if (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
    }

    Gmm_ComPlmnSearchInit();

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* 如果有保留的power off原语                */
        pNasMsgHeader =
            (MSG_HEADER_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;    /* 得到消息头                               */

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            if (GMM_UEID_P_TMSI_SIGNATURE
                == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH成功且使用了P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* 清除P_TMSI_SIGNATURE                     */

                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
            }
            Gmm_ComStaChg(GMM_NULL);                     /* 调用状态的公共处理                       */
            Gmm_SndMmcPowerOffCnf();                                            /* 向MMC发送MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();
        }
        else
        {
            /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* 调用状态的公共处理                       */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* 清当前流程                               */
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);                /* 置SIM卡不存在标志                        */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;           /* 清除IMSI存在MASK                         */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;         /* 清除P_TMSI存在MASK                       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;      /* 清除P_TMSI_SIGNATURE存在MASK             */

            NAS_MML_InitUeIdPtmisInvalid();
            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                 /* 通知RRC NAS层信息变化                    */

#if (FEATURE_ON == FEATURE_PTM)
            /* 工程菜单打开后，PTMSI发生改变需要上报给OM */
            NAS_GMM_SndAcpuOmChangePtmsi();
#endif
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)VOS_NULL_PTR;
    }

    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */

    return;                                                                     /* 返回                                     */
}


VOS_UINT32 GMM_ComCheckRauIntegrityProtection(VOS_UINT8 *pucMsgContent,
                                                VOS_UINT32  ulMsgLen)
{
    GMM_RAI_STRU                        stRauRai;
    VOS_UINT8                           aucRauPtmsi[NAS_MML_MAX_PTMSI_LEN];
    VOS_UINT8                           ucPtmsiAvail;
    VOS_UINT32                          ulIeCount;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* 完整性保护已经启动 */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect)
    {
        ulIntegrityCheckResult = GMM_TRUE;
    }
    /* 完整性保护没有启动 */
    else
    {
        ulIntegrityCheckResult = GMM_FALSE;

        /*ROUTING AREA UPDATE ACCEPT (at periodic routing area update with no
        change of routing area or temporary identity)*/
        if (GMM_FALSE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {
            return GMM_FALSE;
        }

        /* 获取 RAU ACCEPT消息 RAI参数*/
        Gmm_FillRaiForRcv(&stRauRai, &pucMsgContent[4]);

        ucPtmsiAvail = GMM_FALSE;
        PS_MEM_SET(aucRauPtmsi, 0x00, NAS_MML_MAX_PTMSI_LEN);

        /* 获取 RAU ACCEPT消息 PTMSI参数*/
        for (ulIeCount=10; ulIeCount < ulMsgLen; ulIeCount++ )
        {
            if (GMM_IEI_P_TMSI_SIGNATURE == pucMsgContent[ulIeCount])
            {
                /* P-TMSI signature为4个字节，此处加3，For循环再加1 */
                ulIeCount += 3;
                continue;
            }

            if (GMM_IEI_ALLOCATED_PTMSI == pucMsgContent[ulIeCount])
            {
                if ( GMM_MOBILE_ID_TMSI_PTMSI == (pucMsgContent[ulIeCount+2] & 0x07) )
                {
                    ucPtmsiAvail = GMM_TRUE;
                    PS_MEM_CPY(aucRauPtmsi, &pucMsgContent[ulIeCount+3], NAS_MML_MAX_PTMSI_LEN);
                }
                break;
            }
        }

        /* 如果RAI没有发生改变 */
        if (GMM_TRUE == Gmm_Com_CmpRai(&stRauRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
        {
            /* 没有分配PTMSI */
            if (GMM_FALSE == ucPtmsiAvail)
            {
                ulIntegrityCheckResult = GMM_TRUE;
            }
            /* 分配的PTMSI和以前相同 */
            else if ( 0 == VOS_MemCmp(aucRauPtmsi,NAS_MML_GetUeIdPtmsi(),NAS_MML_MAX_PTMSI_LEN) )
            {
                ulIntegrityCheckResult = GMM_TRUE;
            }
            else
            {
            }
        }
    }
    return ulIntegrityCheckResult;
}


VOS_UINT32 GMM_ComCheckIntegrityProtection(VOS_UINT8 *pucMsgContent,
                                            VOS_UINT32  ulMsgLen)
{
    VOS_UINT8                           ucPD;
    VOS_UINT8                           ucMsgType;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* 快速接入模式属于测试模式，不进行完整性检查 */
    if ( VOS_TRUE == NAS_MML_IsQuickStartFlg())
    {
        return GMM_TRUE;
    }

    /* 完整性检查仅适用于UMTS网络 */


    /* 完整性检查仅适用于UMTS网络 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return GMM_TRUE;
    }

    if (VOS_FALSE == NAS_UTRANCTRL_IsUtranPsSmcNeeded())

    {
        return GMM_TRUE;
    }

    ucPD = pucMsgContent[0] & 0x0f;

    /* 完整性保护已经启动 */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect)
    {
        ulIntegrityCheckResult = GMM_TRUE;
    }
    /* 完整性保护没有启动 */
    else
    {
        ulIntegrityCheckResult = GMM_FALSE;

        /*
        24.008 4.1.1.1 Except the messages listed below, no layer 3 signalling
        messages shall be processed by the receiving MM and GMM entities or
        forwarded to the CM entities, unless the security mode control procedure
        is activated for that domain. */
        if (GMM_PD_GMM == ucPD)
        {
            ucMsgType = pucMsgContent[1];
            switch (ucMsgType)
            {
                case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
                case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
                case GMM_MSG_IDENTITY_REQUEST:
                case GMM_MSG_ATTACH_REJECT:
                case GMM_MSG_RAU_REJECT:
                case GMM_MSG_SERVICE_REJECT:
                    ulIntegrityCheckResult = GMM_TRUE;
                    break;
                case GMM_MSG_RAU_ACCEPT:
                    ulIntegrityCheckResult =
                     GMM_ComCheckRauIntegrityProtection(pucMsgContent,ulMsgLen);
                    break;

                case GMM_MSG_DETACH_ACCEPT:
                    /* DETACH ACCEPT (for non power-off) */
                    if ((GMM_GPRS_DETACH_POWEROFF != g_GmmGlobalCtrl.ucSpecProc)
                      && (GMM_COMBINED_DETACH_POWEROFF !=
                                            g_GmmGlobalCtrl.ucSpecProc))
                    {
                        ulIntegrityCheckResult = GMM_TRUE;
                    }
                    break;
                default:
                    break;
            }
        }
        else if (GMM_PD_RSV_FOR_TEST == ucPD)
        {
            ulIntegrityCheckResult = GMM_TRUE;
        }
        else
        {
        }
    }
    return ulIntegrityCheckResult;
}


VOS_UINT32 NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg (VOS_VOID)
{
    /* 24008 4.7.5.1.5 章节描述如下:
    Routing area updating and P-TMSI reallocation procedure collision
    - If the MS receives a P-TMSI REALLOCATION C0MMAND message before the routing area
    updating procedure has been completed, the P-TMSI reallocation procedure shall
    be aborted and the routing area updating procedure shall be progressed.*/
    if (NAS_GMM_SPEC_PROC_TYPE_RAU == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
    {
        return VOS_FALSE;
    }

    /* 24008_CR1941_(Rel-11)_C1-113955 24008 4.7.4.1.4章节描述如下:
    GPRS detach containing other causes than "power off" and containing detach type "IMSI detach":
    -   If the MS receives a message used in a GMM common procedure before the GPRS detach
    procedure has been completed, both the GMM common procedure and the GPRS detach procedure
    shall continue. detach流程中如果detach 类型不为imsi detach则不处理 */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}


VOS_UINT32 NAS_GMM_IsNeedProcStatusMsg (VOS_VOID)
{
    /* 24008_CR1941_(Rel-11)_C1-113955 24008 4.7.4.1.4章节描述如下:
    GPRS detach containing other causes than "power off" and containing detach type "IMSI detach":
    -   If the MS receives a message used in a GMM common procedure before the GPRS detach
    procedure has been completed, both the GMM common procedure and the GPRS detach procedure
    shall continue. */

    /* detach流程中如果detach 类型不为imsi detach则不处理 */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT32 NAS_GMM_IsNeedProcGmmInfoMsg (VOS_VOID)
{
    /* 24008_CR1941_(Rel-11)_C1-113955 24008 4.7.4.1.4章节描述如下:
    GPRS detach containing other causes than "power off" and containing detach type "IMSI detach":
    -   If the MS receives a message used in a GMM common procedure before the GPRS detach
    procedure has been completed, both the GMM common procedure and the GPRS detach procedure
    shall continue. */

    /* detach流程中如果detach 类型不为imsi detach则不处理 */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}




VOS_VOID Gmm_RcvRrmmDataInd(
                        VOS_VOID *pRcvMsg                                       /* 接收消息使用的头地址定义                 */
                        )
{
    RRMM_DATA_IND_FOR_PCLINT_STRU  *pRrmmDataInd;
    NAS_MSG_FOR_PCLINT_STRU        *pNasMsg;
    NAS_MSG_STRU                   *pGmmStatus;

    pRrmmDataInd = (RRMM_DATA_IND_FOR_PCLINT_STRU *)pRcvMsg;                    /* 得到消息的首地址                         */
    if ( RRC_NAS_CS_DOMAIN == pRrmmDataInd->ulCnDomainId )
    {                                                                           /* 错误的消息                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: CS data is received in RRMM_DATA_IND");
        return;
    }
    if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* 当前没有信令                             */
        if (GMM_FALSE == GMM_IsCasGsmMode())
        {                                                                       /*3G下如果当前没有信令，直接返回。2G下信令连接标志始终有效 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Signalling connection is not existed");
            return;
        }
    }

    pNasMsg = &pRrmmDataInd->RcvNasMsg;                                         /* 得到NAS消息结构的地址                    */
    if ((GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        && (GMM_PD_RSV_FOR_TEST != (pNasMsg->aucNasMsg[0] & 0x0F)))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: In TC_ACTIVE, other NT message than TC is omitted");
        Gmm_MemFree(pRcvMsg);                                                   /* 释放接收到的消息内存                     */
        return;
    }

    if (2 > pNasMsg->ulNasMsgSize)
    {                                                                           /* 消息过短                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Message from NT is too short");
        return;
    }

    if (GMM_FALSE == GMM_ComCheckIntegrityProtection(pNasMsg->aucNasMsg, pNasMsg->ulNasMsgSize))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Integrity Check Fail");
    }
    else
    {

        /* 收到了从网侧来的NAS层消息 */
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;

        switch (pNasMsg->aucNasMsg[0] & 0x0F)
        {                                                                       /* 按照Protocol discriminator分发           */
        case GMM_PD_GMM:
            if (0 != ( pNasMsg->aucNasMsg[0] & 0xF0))
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: NT message is invalid");
                return;
            }

            GMM_ReportN2MOtaMsg((NAS_MSG_STRU *)pNasMsg);


            switch (pNasMsg->aucNasMsg[1])
            {                                                                   /* 按照Message type分发                     */
            case GMM_MSG_ATTACH_ACCEPT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    /* 2G网络下，通知GAS层GMM过程完成，GRR将停止non_DRX状态 */



                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }

                Gmm_RcvAttachAcceptMsg(pNasMsg);                                /* 空口消息Attach accept的接收处理          */
                break;
            case GMM_MSG_ATTACH_REJECT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {/* 2G网络下，通知GAS层GMM过程完成，GRR将停止non_DRX状态 */



                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvAttachRejectMsg(pNasMsg);                                /* 空口消息Attach reject的接收处理          */
                break;
            case GMM_MSG_DETACH_REQUEST:
                if(GMM_TRUE == GMM_IsCasGsmMode())
                {
                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvDetachRequestMsg(pNasMsg);                               /* 空口消息Detach request的接收处理         */
                break;
            case GMM_MSG_DETACH_ACCEPT:
                Gmm_RcvDetachAcceptMsg(pNasMsg);                                /* 空口消息Detach accept的接收处理          */
                break;
            case GMM_MSG_RAU_ACCEPT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {


                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvRoutingAreaUpdateAcceptMsg(pNasMsg);                     /* 空口消息Routing area update accept的接收 */
                break;
            case GMM_MSG_RAU_REJECT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {


                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvRoutingAreaUpdateRejectMsg(pNasMsg);                     /* 空口消息Routing area update reject的接收 */
                break;
            case GMM_MSG_SERVICE_ACCEPT:
                Gmm_RcvServiceAcceptMsg(pNasMsg);                               /* 空口消息Service Accept的接收处理         */
                break;
            case GMM_MSG_SERVICE_REJECT:
                Gmm_RcvServiceRejectMsg(pNasMsg);                               /* 空口消息Service Reject的接收处理         */
                break;
            case GMM_MSG_P_TMSI_REALLOCATION_COMMAND:
                if (VOS_TRUE == NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg())
                {
                    Gmm_RcvPtmsiReallocationCommandMsg(pNasMsg);                /* 空口消息P-TMSI reallocation command接收  */
                }
                break;
            case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
                Gmm_RcvAuthenAndCipherRequestMsg(pNasMsg);                      /* Authentication and ciphering request接收 */
                break;
            case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
                Gmm_RcvAuthenAndCipherRejectMsg(pNasMsg);                       /* Authentication and ciphering reject接收  */
                break;
            case GMM_MSG_IDENTITY_REQUEST:
                Gmm_RcvIdentityRequestMsg(pNasMsg);                             /* 空口消息Identity request的接收处理       */
                break;
            case GMM_MSG_GMM_STATUS:
                if (VOS_TRUE == NAS_GMM_IsNeedProcStatusMsg())
                {
                    Gmm_RcvGmmStatusMsg(pNasMsg);                               /* 空口消息GMM Status的接收处理 */
                }
                break;
            case GMM_MSG_GMM_INFORMATION:
                if (VOS_TRUE == NAS_GMM_IsNeedProcGmmInfoMsg())
                {
                    Gmm_RcvGmmInformationMsg(pNasMsg);                          /* 空口消息GMM Information的接收处理 */
                }
                break;
            default :
                pGmmStatus = Gmm_GmmStatusMsgMake(
                    NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE);

                Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: The MsgType is Abnormal");
                break;
            }
            break;

        case GMM_PD_SM:
            Gmm_SndSmDataInd(pNasMsg);                                          /* 原语GMMSM_DATA_IND的发送处理             */
            break;

        case GMM_PD_SMS:
            if (GMM_NULL_PROCEDURE == g_GmmGlobalCtrl.ucSpecProc)
            {
                Gmm_SndSmsUnitdataInd(pNasMsg);                                 /* 原语PMMSMS_UNITDATA_IND的发送处理        */
            }
            break;

        case GMM_PD_RSV_FOR_TEST:
            Gmm_SndTcDataInd(pNasMsg);
            break;

        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Protocol discriminator is Error");
            break;
        }
    }

    return;
}


VOS_VOID GMM_RcvMmcRelReq(
    VOS_VOID                           *pMsg                                    /* 消息指针                                 */
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* GU下存在PS业务时，MMC向MM/GMM发送释放请求，
       GMM给接入层发送释放请求，连接释放后，下发SYSCFG */

    /* 通知WRR释放连接.当状态在搜网状态时,说明原来已经通知了连接释放,不需要重复通知 */
    if (((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
      || (GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
     && (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        Gmm_TimerStart(GMM_TIMER_WAIT_CONNECT_REL);
    }

    if ((VOS_TRUE == NAS_MML_GetPsTbfStatusFlg())
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        Gmm_TimerStart(GMM_TIMER_WAIT_CONNECT_REL);
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态分发                             */
        case GMM_REGISTERED_INITIATED:
            NAS_GMM_RcvMmcRelReq_RegInit();
            break;
        case GMM_DEREGISTERED_INITIATED:
            NAS_GMM_RcvMmcRelReq_DeregInit();
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            NAS_GMM_RcvMmcRelReq_RauInit();
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            NAS_GMM_RcvMmcRelReq_RegImsiDtchInit();
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo();
            break;
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            break;
        default:
            break;
    }

    if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
    }

    if (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
    {                                                                           /* 当前处于非注册状态                       */
        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }
    else
    {                                                                           /* 当前处于注册状态                         */
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    /* 挂起用户面，保证数据不再下发 */
    NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    return;
}


VOS_VOID NAS_GMM_RcvMmcRelReq_RegInit()
{
    /* 停止注册过程中的相关定时器 */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3310);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* 如果正在鉴权，则清除等待标志 */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }


    /* 收到MMC的rel req,认为注册失败，增加注册失败的处理，与RauInit状态时收到rel_ind的处理类似 */
    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);             /* 调用attach attempt counter的处理         */

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;

    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* 清除fallowon标志                         */

    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);



    return;
}


VOS_VOID NAS_GMM_RcvMmcRelReq_DeregInit()
{
    /* 停止去注册过程中的相关定时器 */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_RR_REL);

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif
    Gmm_TimerStop(GMM_TIMER_T3312);

    /* 如果正在鉴权，则清除等待标志 */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {
            /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
    }
    else
    {
        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 将流程清空                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_RcvMmcRelReq_DeregInit:INFO: specific procedure ended");

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}


VOS_VOID NAS_GMM_RcvMmcRelReq_RauInit()
{

    /* 停止路由区过程中的相关定时器 */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3330);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* 收到MMC的rel req,认为注册失败，增加注册失败的处理，与RauInit状态时收到rel_ind的处理类似 */

    /* 完整性保护标志置为DEACTIVE */
    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                    NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    /* 清除RAU和LU标志 */
    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    /* 如果正在鉴权，则清除等待标志 */
    NAS_GMM_ClearAuthInfo();


    /* 如果正在建链，清除等待标志 */
    if (GMM_RRC_RRMM_EST_CNF_FLG ==
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* 清等待响应标志                           */
    }

    Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);         /* 调用RAU attempt counter的处理            */

    /* free之前保存的系统消息 */
    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();


    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}


VOS_VOID NAS_GMM_RcvMmcRelReq_RegImsiDtchInit()
{
    /* 停止去注册过程中的相关定时器 */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    /* 如果正在鉴权，则清除等待标志 */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 存在被挂起的T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* 恢复T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* 存在被挂起的T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* 恢复T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* 起T3312                                  */
    }

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 将流程清空                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_RcvMmcRelReq_RegImsiDtchInit:INFO: specific procedure ended");

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

    return;
}


VOS_VOID NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo()
{
    /*异系统改变时通知RABM*/
    g_GmmRauCtrl.ucNpduCnt = 0x0;
    GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);
}



VOS_VOID Gmm_RcvMmcCoverageLostInd(VOS_VOID)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_VOID            *pAddr;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    /* 丢网时, 指示RABM当前系统模式, 并挂起RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    /* 停HO等待系统消息定时器 */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    /* 在GSM模式下，如果出服务区，此时需要挂起LLC，阻止用户面继续发送数据 */
    if(GMM_TRUE == GMM_IsCasGsmMode())
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_OUT_OF_SERVICE;
        }
    }

    if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }

    g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;

    g_GmmGlobalCtrl.ucCvrgAreaLostFlg     = GMM_TRUE;
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_FALSE;
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg   = GMM_FALSE;
    g_GmmGlobalCtrl.ucCipherStartFlg      = GMM_FALSE;

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停止T3310                                */
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停止T3317                                */
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停止T3321                                */
    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* 停止T3330                                */
    Gmm_TimerStop(GMM_TIMER_T3340);                                             /* 停止T3340                                */

    if (GMM_TIMER_PROTECT_FOR_SIGNALING_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_PROTECT_FOR_SIGNALING_FLG))

    {                                                                           /* 保护Timer是否在运行,是                   */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);                         /* 停保护Timer                              */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* 清等待cnf                                */
    }
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 如果T3311在运行                          */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停止T3311                                */
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerResumeForTc(GMM_TIMER_ALL);                                    /* 恢复所有被挂起的Timer                    */
    }

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态分发                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvCoverLost_RegInit();
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvCoverLost_DeregInit();
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvCoverLost_RauInit();
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvCoverLost_ServReqInit();
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
        Gmm_RcvCoverLost_RegNmlServ();
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvCoverLost_RegImsiDtchInit();
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvCoverLost_SuspendWaitForSys();
        break;
    default:
        break;
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }
    else
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* PS 域卡无效，状态不迁移 */
    if (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)
    {
        if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {                                                                       /* 当前处于非注册状态                       */
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);                  /* 调用状态的公共处理                       */
        }
        else
        {                                                                       /* 当前处于注册状态                         */
            Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);                    /* 调用状态的公共处理                       */
        }
    }

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* 如果有保留的power off原语                */
        pNasMsgHeader =
            (MSG_HEADER_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;    /* 得到消息头                               */

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            if (GMM_UEID_P_TMSI_SIGNATURE
                == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH成功且使用了P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* 清除P_TMSI_SIGNATURE                     */

                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
            }
            Gmm_ComStaChg(GMM_NULL);                     /* 调用状态的公共处理                       */
            Gmm_SndMmcPowerOffCnf();                                            /* 向MMC发送MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();
        }
        else
        {
            /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }
                NAS_GMM_SndMmcMmDetachInfo();
            }
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* 调用状态的公共处理                       */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* 清当前流程                               */
            NAS_MML_SetSimPresentStatus(VOS_FALSE);                             /* 置SIM卡不存在标志                        */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;           /* 清除IMSI存在MASK                         */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;         /* 清除P_TMSI存在MASK                       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;/* 清除P_TMSI_SIGNATURE存在MASK             */

            NAS_MML_InitUeIdPtmisInvalid();
            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                /* 通知RRC NAS层信息变化                    */

#if (FEATURE_ON == FEATURE_PTM)
            /* 工程菜单打开后，PTMSI发生改变需要上报给OM */
            NAS_GMM_SndAcpuOmChangePtmsi();
#endif
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* 清除保留标志                             */

        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)VOS_NULL_PTR;
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        switch (g_GmmGlobalCtrl.ucSpecProcHold)
        {                                                                       /* 保留的specific流程                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* 通知RABM结果                             */
            break;
        default:
            break;
        }
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* 清除保留流程                             */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_FALSE;                             /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    }

    Gmm_FreeBufferMsgWithoutSm();

    g_GmmReqCnfMng.ucCnfMask            = 0;                                    /* 清所有等待cnf                            */
    g_GmmGlobalCtrl.ucSpecProc          = GMM_NULL_PROCEDURE;                   /* 清除当前流程                             */
    g_GmmGlobalCtrl.ucSpecProcHold      = GMM_NULL_PROCEDURE;                   /* 清除保留的过程                           */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;                   /* 清除记录的CS通信中流程                   */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcCoverageLostInd:INFO: specific procedure ended");

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcPlmnSearchInitiated(VOS_VOID)
{

    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_FALSE;                          /* 设置系统消息无效的标志                   */

    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);
    }
    else
    {
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);


        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();
    }

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前状态为NULL状态                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcPlmnSearchInitiated:WARNING: GMM state is VOS_NULL_PTR(Gmm_RcvMmcPlmnSearchInitiated)");
        return;
    }

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    if ((GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
        {
            g_GmmGlobalCtrl.ucPlmnSrchPreSta = gstGmmSuspendCtrl.ucPreState;
        }
        else
        {
            g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
        }

        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                    VOS_FALSE,
                                    VOS_TRUE,
                                    VOS_TRUE);

        Gmm_ComPlmnSearchInit();
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcStartReq(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucTmpTmsi;
    VOS_UINT32                          ulInvalidCnt;
    VOS_UINT8                          *pucTmpTmsiSig;
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;
#endif

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;                           /* 当前驻留的网络接入技术 */

    enNetRatType = NAS_MML_GetCurrNetRatType();

    Gmm_ComReset();                                                             /* 调用reset公共处理 */

    GMM_CasChangSysMode(enNetRatType);


#if (FEATURE_ON == FEATURE_LTE)

    /* 记录开机时，MS Radio Capability对应的接入技术列表 */
    PS_MEM_CPY(&(g_GmmGlobalCtrl.UeInfo.stRadioCpbRelatedRatList),
               NAS_MML_GetMsPrioRatList(),
               sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
#endif


    /* 当前必然支持UMTS鉴权 */
    g_GmmAuthenCtrl.ucUmtsAuthFlg           = GMM_UMTS_AUTHEN_SUPPORTED;

    /* 当前必然支持GMM INFORMATION */
    g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg = GMM_SUPPORT_INFORMATION_MSG;

    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

#if (FEATURE_ON == FEATURE_ECALL)
    enCallMode = NAS_MML_GetCallMode();
#endif

    /* 设置当前PS域是否有效 */
    if ((VOS_TRUE == NAS_MML_GetSimPresentStatus())
#if (FEATURE_ON == FEATURE_ECALL)
     /* 根据3GPP 24.008 section 4.7:
     * 1. An eCall only mobile station shall not perform a normal or combined GPRS attach procedure.
     * 2. An eCall only mobile station shall not perform any kind of GPRS detach procedure.
     * 3. An eCall only mobile station shall not perform a normal or combined routing area updating procedure.
     * 这里，让GMM进入设置PS sim无效，使后续GMM进入NO_IMSI状态
     */

     && (NAS_MML_ECALL_ONLY != enCallMode)
#endif
       )
    {
        NAS_MML_SetSimPsRegStatus(VOS_TRUE);
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_IMSI;
    }
    else
    {
        NAS_MML_SetSimPsRegStatus(VOS_FALSE);
        Gmm_SndMmcStartCnf();
        return;
    }

    /* 根据当前存储的TMSI是否有效，设定是否存在PTMSI */
    ulInvalidCnt = 0;
    pucTmpTmsi = NAS_MML_GetUeIdPtmsi();
    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        if (GMM_PTMSI_INVALID == pucTmpTmsi[i])
        {
            ulInvalidCnt++;
        }
    }
    if (NAS_MML_MAX_PTMSI_LEN == ulInvalidCnt)
    {                                                                           /* P-TMSI 无效                              */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;
    }
    else
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;
    }

    ulInvalidCnt = 0;
    pucTmpTmsiSig = NAS_MML_GetUeIdPtmsiSignature();

    ulInvalidCnt = 0;
    for (i=0; i<NAS_MML_MAX_PTMSI_SIGNATURE_LEN; i++)
    {
        if (GMM_PTMSI_SIGNATURE_INVALID == pucTmpTmsiSig[i])
        {
            ulInvalidCnt++;
        }
    }
    if (NAS_MML_MAX_PTMSI_SIGNATURE_LEN == ulInvalidCnt)
    {                                                                           /* P-TMSI signature无效                     */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

    }
    else
    {                                                                           /* P-TMSI signature有效                     */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI_SIGNATURE;    /* 设置相应存在标识                         */
    }


    /* 为了防止使用测试号段避过IMSI的检查，使得能够使用TMSI进行注册，需要
       进行防卡贴的判定，在NV项激活的情况下，特殊号段TMSI置为无效
    */
    if (VOS_TRUE == NAS_PreventTestImsiRegFlg())
    {
        NAS_MML_InitUeIdPtmisInvalid();

        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;
    }


    Gmm_SndMmcStartCnf();

    return;                                                                     /* 返回                                     */
}


VOS_UINT32 NAS_GMM_CheckSimStatusAffectAttach(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_SIM_STATUS_STRU            *pstUsimStatus;

    pstUsimStatus = NAS_MML_GetSimStatus();

    /* USIM CS域无效，MMC_GMM_ATTACH_TYPE_GPRS_IMSI类型转换为MMC_GMM_ATTACH_TYPE_GPRS */
    if ( ( MMC_GMM_ATTACH_TYPE_GPRS != pstAttachReq->enAttachType )
      && ( VOS_TRUE != pstUsimStatus->ucSimCsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_IsAttachTypeConfictWithSimStatus:WARNING: CS USIM is invalid.");

        if ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
        {
            pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_GPRS;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    /* USIM PS域无效，直接回复ATTACH CNF */
    if ( ( MMC_GMM_ATTACH_TYPE_IMSI != pstAttachReq->enAttachType )
      && ( VOS_TRUE                 != pstUsimStatus->ucSimPsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM,"NAS_GMM_IsAttachTypeConfictWithSimStatus:WARNING: PS USIM is invalid.");

        NAS_GMM_SndMmcAttachCnf();

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_GMM_ModifyAttachType(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    if (NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode)
    {
        /* 非网络模式I下收到CS ATTACH，GMM不处理 */
        if (MMC_GMM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType)
        {
            return VOS_TRUE;
        }

        /* 非网络模式I下收到CS+PS ATTACH，改为GPRS ATTACH */
        if (MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
        {
            pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_GPRS;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_GMM_IsAttachRepeated(
    VOS_UINT32                          ulAttachType,
    VOS_UINT32                          ulOpID)
{
    /* 之前存在PS ATTACH 收到PS ATTACH，更新OPID后直接返回 */
    if ( ( GMM_WAIT_PS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
      && ( MMC_GMM_ATTACH_TYPE_GPRS == ulAttachType ) )
    {
        g_GmmGlobalCtrl.stAttachInfo.ulOpid = ulOpID;
        return VOS_TRUE;
    }

    /* 之前存在CS ATTACH 收到CS ATTACH，直接返回 */
    if ( ( GMM_WAIT_CS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
      && ( MMC_GMM_ATTACH_TYPE_IMSI == ulAttachType ) )
    {
        return VOS_TRUE;
    }

    if ( GMM_WAIT_CS_PS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
    {
        /* 之前存在PS ATTACH 收到CS+PS ATTACH，收到PS ATTACH更新OPID */
        if (MMC_GMM_ATTACH_TYPE_GPRS == (ulAttachType & MMC_GMM_ATTACH_TYPE_GPRS))
        {
            g_GmmGlobalCtrl.stAttachInfo.ulOpid = ulOpID;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_UINT32 NAS_GMM_IsDetachNotAcceptNeedAttach(VOS_VOID)
{
    if (GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
         && (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {
            NAS_GMM_SndMmGprsDetachComplete();

            NAS_GMM_SndMmcDetachCnf();
        }

        g_GmmGlobalCtrl.stDetachInfo.enDetachType &=~GMM_WAIT_PS_DETACH;


        /* GMM停止PS域的DETACH保护定时器 */
        Gmm_TimerStop(GMM_TIMER_PROTECT_PS_DETACH);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_GMM_IsAttachDetachConflicted(VOS_UINT32 ulAttachType)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* 之前不存在DETACH流程 */
    if ( GMM_WAIT_NULL_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        return VOS_FALSE;
    }

    /* A+I模式 */
    if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
      && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode ) )
    {
        /* 网络模式I下,存DETACH流程,直接回复CNF */
        if ( MMC_GMM_ATTACH_TYPE_GPRS == (ulAttachType
                                        & MMC_GMM_ATTACH_TYPE_GPRS))
        {
            if (VOS_TRUE == NAS_GMM_IsDetachNotAcceptNeedAttach() )
            {
                return VOS_FALSE;
            }

            NAS_GMM_SndMmcAttachCnf();
        }
        return VOS_TRUE;
    }

    /* 非A+I模式 */
    if ( ( ( MMC_GMM_ATTACH_TYPE_GPRS == ulAttachType )
        && (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType
                                 & GMM_WAIT_PS_DETACH ) ) )
      || ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == ulAttachType ) )
    {
        if (VOS_TRUE == NAS_GMM_IsDetachNotAcceptNeedAttach() )
        {
            return VOS_FALSE;
        }

        NAS_GMM_SndMmcAttachCnf();
        return VOS_TRUE;
    }

    /* IMSI ATTACH和之前的有冲突 */
    if ( (MMC_GMM_ATTACH_TYPE_IMSI == ulAttachType )
        && (GMM_WAIT_CS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType
                                 & GMM_WAIT_CS_DETACH ) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_UINT32 NAS_GMM_CheckSigConnStatusAffectAttach(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    /* 检查是否由专有流程存在 */
    if((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
    && ( MMC_MM_ATTACH_TYPE_GPRS == pstAttachReq->enAttachType )
    && (GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg))
    {
        return VOS_TRUE;
    }

    if(((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
      && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState ))
    && (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
    && ((GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg)
     || (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg)))
    {
        return VOS_TRUE;
    }


    if (( MMC_MM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType )
     && (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_UINT32 NAS_GMM_CheckAttachStatus(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_TRUE;

    if ( MMC_GMM_ATTACH_TYPE_IMSI != pstAttachReq->enAttachType )
    {                                                                           /* 要求ATTACH PS域                          */
        NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
        g_GmmGlobalCtrl.ucUserPsAttachFlag  = VOS_TRUE;

        /* GMM处于注册状态，直接回复PS CNF */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta )
         && (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
        {                                                                       /* PS域已经ATTACH                           */
            NAS_GMM_SndMmcAttachCnf();

            if ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
            {
                pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_IMSI;
                ulRet                      = VOS_FALSE;
            }
        }
        else
        {                                                                       /* PS域没有ATTACH                           */
            g_GmmGlobalCtrl.stAttachInfo.enAttachType |= GMM_WAIT_PS_ATTACH;
            g_GmmGlobalCtrl.stAttachInfo.ulOpid        = pstAttachReq->ulOpid;
            ulRet = VOS_FALSE;
        }
    }

    if ( MMC_GMM_ATTACH_TYPE_GPRS != pstAttachReq->enAttachType )
    {                                                                           /* 要求ATTACH CS域                          */
        /* CS 处于ATTACHED状态，修改GPRS_IMSI类型为GPRS ATTACH */
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {                                                                       /* CS域已经ATTACH                           */
            ulRet = VOS_TRUE;

            if ( NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
            {
                pstAttachReq->enAttachType  = MMC_GMM_ATTACH_TYPE_GPRS;
                ulRet                       = VOS_FALSE;
            }

        }
        else
        {                                                                       /* CS域没有ATTACH                           */
            g_GmmGlobalCtrl.stAttachInfo.enAttachType |= GMM_WAIT_CS_ATTACH;
            ulRet                                      = VOS_FALSE;
        }
    }

    return ulRet;
}



VOS_UINT32 NAS_GMM_RcvMmcAttachReq_PreProc(
    MMCGMM_ATTACH_REQ_STRU             *pstmsg
)
{
    /* 判定是否需要处理该消息，无效消息返函数返回 */
    if ((MMC_MM_ATTACH_TYPE_IMSI      != pstmsg->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS      != pstmsg->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS_IMSI != pstmsg->enAttachType))
    {

        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_MM_RcvMmcAttachReq_PreProc:ATTACH TYPE INVALID");
        return VOS_TRUE;
    }


    if (MMC_MM_ATTACH_TYPE_IMSI != pstmsg->enAttachType)
    {
        g_GmmGlobalCtrl.stAttachInfo.ulOpid = pstmsg->ulOpid;
    }


    /* 检查是否有业务存在 */
    if (VOS_TRUE == NAS_GMM_CheckSigConnStatusAffectAttach(pstmsg))
    {
        if (MMC_MM_ATTACH_TYPE_IMSI != pstmsg->enAttachType)
        {
            NAS_GMM_SndMmcAttachCnf();
        }

        return VOS_TRUE;
    }

    /* 检查ATTACH类型是否和SIM卡状态冲突 */
    if ( VOS_TRUE == NAS_GMM_CheckSimStatusAffectAttach(pstmsg) )
    {
        return VOS_TRUE;
    }

    /* 根据网络模式调整ATTACH类型 */
    if ( VOS_TRUE == NAS_GMM_ModifyAttachType(pstmsg) )
    {
        return VOS_TRUE;
    }

    /* 检查是否和之前存在DETACH有冲突 */
    if ( VOS_TRUE == NAS_GMM_IsAttachDetachConflicted(pstmsg->enAttachType) )
    {
        return VOS_TRUE;
    }

    /* 检查之前存在ATTACH */
    if ( VOS_TRUE == NAS_GMM_IsAttachRepeated(pstmsg->enAttachType, pstmsg->ulOpid) )
    {
        return VOS_TRUE;
    }

    /* 检查注册情况 */
    if ( VOS_TRUE == NAS_GMM_CheckAttachStatus(pstmsg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_GMM_CheckNeedBuffDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    MMCGMM_DETACH_REQ_STRU             *pstDetach;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    if ( GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        /* 已经有DETACH流程进行时，网络模式I下缓存DETACH消息 */
        if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
          && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode) )
        {
            pstDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
            if ( VOS_NULL_PTR == pstDetach )
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_CheckNeedBuffDetach:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                  return VOS_TRUE;
            }

            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* 置原语缓存标志                           */
            g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;

            Gmm_MemCpy(pstDetach, pstmsg, sizeof(MMCGMM_DETACH_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstDetach;       /* 缓存原语                                 */
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_GMM_ProcPsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{

    g_GmmGlobalCtrl.ucUserPsAttachFlag  = VOS_FALSE;


    g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());



    g_GmmGlobalCtrl.stAttachInfo.enAttachType &=~GMM_WAIT_PS_ATTACH;
    g_GmmGlobalCtrl.stDetachInfo.enDetachType |= GMM_WAIT_PS_DETACH;

    return VOS_FALSE;
}


VOS_UINT32 NAS_GMM_ProcCsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    /* 非网络模式I下，不处理，直接返回 */

    if (VOS_FALSE == NAS_GMM_IsNeedProcUserCsDetach())
    {
        return VOS_TRUE;
    }
    else
    {
        /* CS处于ATTACHED状态保留标志位, 否则直接回复DETACH CNF*/
        if ( (MM_STATUS_ATTACHED                  == g_MmSubLyrShare.MmShare.ucCsAttachState)
          || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
          || (GMM_REGISTERED_INITIATED            == g_GmmGlobalCtrl.ucState) )
        {
            if ( VOS_TRUE == NAS_MML_GetCsServiceExistFlg() )
            {
                /*  网络模式I下，CS当前有业务链接存在，syscfg设置引起的detach cs操作，则直接返回 */
                if (VOS_TRUE == g_GmmDetachCtrl.ucSysCfgDetachFlg)
                {
                    return VOS_TRUE;
                }
            }

            g_GmmGlobalCtrl.stAttachInfo.enAttachType &= ~MM_WAIT_CS_ATTACH;
            g_GmmGlobalCtrl.stDetachInfo.enDetachType |= MM_WAIT_CS_DETACH;
            g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_GMM_ProcCsPsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    /* 获取当前网络模式 */
    pstCampInfo     = NAS_MML_GetCurrCampPlmnInfo();

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());

    /* 非网络模式I下,只保留PS的标志位 */
    if (NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode)
    {
        g_GmmGlobalCtrl.stAttachInfo.enAttachType &= ~GMM_WAIT_PS_ATTACH;
        g_GmmGlobalCtrl.stDetachInfo.enDetachType |=  GMM_WAIT_PS_DETACH;

        g_GmmGlobalCtrl.stDetachInfo.ulOpid        = pstmsg->ulOpid;
    }
    else
    {
        /* 清楚ATTACH等待标志 */
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

        /* CS处于ATTACHED状态保留标志位 */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            g_GmmGlobalCtrl.stDetachInfo.enDetachType    |= GMM_WAIT_CS_DETACH;
        }

        g_GmmGlobalCtrl.stDetachInfo.enDetachType    |= GMM_WAIT_PS_DETACH;

        g_GmmGlobalCtrl.stDetachInfo.ulOpid           = pstmsg->ulOpid;
    }

    g_GmmGlobalCtrl.ucUserPsAttachFlag = VOS_FALSE;

    return VOS_FALSE;
}


VOS_UINT32 NAS_GMM_RcvMmcDetachReq_PreProc(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{

    /* 启动Detach流程保护定时器 */
    NAS_GMM_StartDetachProtectingTimer(pstmsg);

    /* 判断是否需要缓存DETACH */
    if ( VOS_TRUE == NAS_GMM_CheckNeedBuffDetach(pstmsg) )
    {
        return VOS_TRUE;
    }


    if ( (MMC_GMM_DETACH_CAUSE_RAT_OR_BAND_DETACH == pstmsg->enDetachReason)
      || (MMC_GMM_DETACH_CAUSE_SRV_DOMAIN_CHANGE  == pstmsg->enDetachReason) )
    {
        g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_TRUE;
    }
    else
    {
        g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_FALSE;
    }

    /*  根据DETACH类型分别处理 */
    switch ( pstmsg->enDetachType )
    {
        case MMC_GMM_PS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcPsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;

        case MMC_GMM_CS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcCsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;
        case MMC_GMM_PS_CS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcCsPsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;
        default:
            GMM_LOG_WARN("NAS_GMM_RcvMmcDetachReq_PreProc:DETACH TYPE INVALID!");
            return VOS_TRUE;
     }


    return VOS_FALSE;
}


VOS_VOID Gmm_ComReset(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_ALL);                                               /* 停所有Timer                              */
    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* 需要向SM回响应                           */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GMM_RESET);/* 通知SM GMM注册失败                       */

        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
    }
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {                                                                           /* SMS在等待响应                            */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }
    if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {                                                                           /* GMM当前状态为ATTACHED                    */
        GMM_CasFsmStateChangeTo(GMM_NULL);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_ComReset:NORMAL: STATUS IS GMM_NULL");

        Gmm_SndSmStatusInd();                                                   /* 发送原语GMMSM_STATUS_IND                 */
    }
    if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 需要向RABM回响应                         */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 发送GMMRABM_REESTABLISH_CNF(failure)     */
    }
    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* 有PS域信令                               */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                                    /* 释放信令                                 */
    }
    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */
    Gmm_ComVariantInit();                                                       /* GMM初始化                                */

    return;                                                                     /* 返回                                     */
}


VOS_UINT8 Gmm_DealWithBuffInProc(VOS_VOID)
{
    VOS_VOID               *pAddr;                                              /* 定义指针                                 */
    VOS_UINT8               ucRet;                                              /* 定义返回值                               */

    ucRet = GMM_FALSE;                                                          /* 返回值初始化为FALSE                      */

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* 如果有保留的power off原语                */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;       /* 读取power off原语地址                    */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        Gmm_HoldBufferFree();                                                   /* 将保留buffer中所有的消息释放             */
        ucRet = GMM_TRUE;
    }
    else if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* 如果有保留的paging(IMSI)原语             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* 读取paging(IMSI)原语地址                 */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        Gmm_HoldBufferFree();                                                   /* 将保留buffer中所有的消息释放             */
        ucRet = GMM_TRUE;
    }
    else if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* 如果有保留的RAU原语                      */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* 读取RAU原语地址                          */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        ucRet = GMM_TRUE;
    }

    else if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* 读取detach原语地址                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        NAS_GMM_FreeBufferCmMsg();
        ucRet = GMM_TRUE;
    }

    else if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* 如果有保留的attach原语                   */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* 读取attach原语地址                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        ucRet = GMM_TRUE;
    }
    else
    {
    }
    return ucRet;
}


VOS_VOID Gmm_DealWithBuffAfterProc(VOS_VOID)
{
    VOS_VOID                            *pMsg;
    GMMSM_DATA_REQ_STRU                 *ptr;
    GMMRABM_REESTABLISH_REQ_STRU        *pRabmReEst;

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除缓存标志                             */
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);  /* 保留的消息分发                           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的SR原语                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */

        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;

        /*构造分发消息*/
        pRabmReEst = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        if (VOS_NULL_PTR == pRabmReEst)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        Gmm_MemCpy(pRabmReEst, pMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        /*释放保存的RAMB消息*/
        Gmm_MemFree(pMsg);

        /*分发缓存的Service消息*/
        Gmm_MsgDistribute((VOS_VOID *)(pRabmReEst));

        /*释放新申请的内存*/
        Gmm_MemFree(pRabmReEst);
    }

    if (GMM_MSG_HOLD_FOR_SMS
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {                                                                           /* 如果有保留的SR原语                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;          /* 清除缓存标志                             */
        Gmm_MsgDistribute((VOS_VOID *)(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS)); /* 保留的消息分发                           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;

    }

    /* 对于SM消息，GMM处于暂态，需要两次缓存，第一次缓存等到GMM处于
    *  正常服务态才处理，这时先发起服务请求，消息需要第二次缓存
    *  等到安全模式完成后再处理。因是两次缓存使用同一变量记录消息地址，
    *  因此每次处理时都是重新申请空间，及时释放原申请空间。
    */
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        /*清除缓存SM消息的标志*/
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;

        if (VOS_NULL_PTR == pMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: GMM MSG HOLD FOR SM PTR IS NULL.");
            return;
        }
        /*申请缓存消息的内存*/
        if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
        {
            ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
        }
        else
        {
            ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
                   + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4);
        }
        if (VOS_NULL_PTR == ptr)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        /*把消息暂存到申请的内存中*/
        if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
        {
            Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
        }
        else
        {
            Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
                + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4));
        }
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_DealWithBuffAfterProc(): Process cached SM Data Req");
        /*释放保存的SM消息*/
        Gmm_MemFree(pMsg);
        /*分发缓存的SM消息*/
        Gmm_MsgDistribute((VOS_VOID *)(ptr));
        /*释放新申请的内存*/
        Gmm_MemFree(ptr);
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_HoldBufferFree(VOS_VOID)
{
    VOS_VOID                *pAddr;                                             /* 定义指针                                 */

    if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* 如果有保留的paging(IMSI)原语             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* 读取paging(IMSI)原语地址                 */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* 如果有保留的RAU原语                      */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* 清除缓存标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* 读取RAU原语地址                          */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* 读取detach原语地址                       */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* 如果有保留的attach原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* 读取attach原语地址                       */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的ServiceRequest原语           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* 读取ServiceRequest原语地址               */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {                                                                           /* 如果有保留的SmDataReq原语                */
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_HoldBufferFree(): Clear cached SM Data Req");

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;           /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;             /* 读取SmDataReq原语地址                    */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}


VOS_VOID NAS_GMM_RcvMmCmServiceRejectInd(
    VOS_VOID                           *pstMsg
)
{
    MMGMM_CM_SERVICE_REJECT_IND_STRU   *pstMmServRejInd;                      /* 定义指针                                 */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* 不是用户模式A且网络模式I                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcCmServiceRejectInd:WARNING: It is not A+I(Gmm_RcvMmcCmServiceRejectInd)");
        return;
    }

    pstMmServRejInd = (MMGMM_CM_SERVICE_REJECT_IND_STRU *)pstMsg;                 /* 初始化指针                               */

    if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR == pstMmServRejInd->enCause)
    {                                                                           /* 原因值为#4                               */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_TRUE;                               /* 设置MmcCmServiceRejectInd#4触发RAU的标志 */
    }

    return;
}


VOS_VOID NAS_GMM_RcvMmCsConnectInd_InProc(
    VOS_VOID                           *pstMsg                               /* 原语指针                                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstTmpMsg;

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前流程为RAU                            */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* 标记GMM不能进行RAU时要触发MM的LU过程     */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* 清除CS触发RAU的标志                      */
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前流程为ATTACH                            */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* 标记GMM不能进行RAU时要触发MM的LU过程     */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* 清除CS触发RAU的标志                      */
        return;
    }

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* 无信令且正在建立信令连接                 */
        pstTmpMsg = (MMGMM_CS_CONNECT_IND_STRU *)Gmm_MemMalloc(sizeof(MMGMM_CS_CONNECT_IND_STRU));
        if (VOS_NULL_PTR == pstTmpMsg)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcCmServiceInd_InProc:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(pstTmpMsg, pstMsg, sizeof(MMGMM_CS_CONNECT_IND_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)pstTmpMsg;              /* 保留该原语                               */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* 置保留标志                               */
    }
    else
    {                                                                           /* 有信令或没有信令且还没建信令             */
        if (GMM_TIMER_T3317_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3317_FLG))
        {                                                                       /* 如果T3317在运行                          */
            Gmm_TimerStop(GMM_TIMER_T3317);                                     /* 停T3317                                  */
        }
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                               /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 执行RAU                                  */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* 清除CS触发RAU的标志                      */
    }
    return;                                                                     /* 返回                                     */
}


VOS_VOID NAS_GMM_RcvMmCsConnectInd_RegNmlServ(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    /* 取得当前的链接信息 */
    pstConnStatus = NAS_MML_GetConnStatus();

    enCurrRatType = NAS_MML_GetCurrNetRatType();

    if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState )
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }

    /* CS业务结束，GS关联不存在，RRC存在，立即发起联合RAU，否则等上报系统消息，再发起联合rau*/
    if ((VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
     && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRatType)
     && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_RcvMmCsConnectInd_RrcConnExist();
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                                  /* 清除CS触发RAU的标志                      */
    }
    else
    {
    }
}


VOS_UINT32 NAS_GMM_IsRcvRrmmEstCnfMsgValid(
    RRMM_EST_CNF_STRU                  *pRrmmEstCnf
)
{
    if (RRC_NAS_PS_DOMAIN != pRrmmEstCnf->ulCnDomainId)
    {                                                                           /* 判断是PS域信息,否                        */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: It is not PS domain(Gmm_RcvRrmmEstCnf)");
        return VOS_FALSE;
    }
    if (GMM_RRC_RRMM_EST_CNF_FLG
        != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* 判断是否正在等该响应,否                  */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: RRMM_EST_CNF is unexpected");
        return VOS_FALSE;
    }
    if (g_GmmReqCnfMng.ucRrmmEstOpid != pRrmmEstCnf->ulOpId)
    {                                                                           /* OP ID不相等                              */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: RRMM_EST_CNF is unexpected(OPID is not same)");
        return VOS_FALSE;
    }

    if (RRC_EST_ESTING == pRrmmEstCnf->ulResult)
    {                                                                           /* 结果为正在建                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: The result is invalid(Gmm_RcvRrmmEstCnf)");
        return VOS_FALSE;
    }

    return VOS_TRUE;

}


VOS_VOID Gmm_RcvRrmmEstCnf(
                       VOS_VOID *pMsg                                           /* 原语指针                                 */
                       )
{
    RRMM_EST_CNF_STRU      *pRrEstCnf;                                          /* 定义指针                                 */

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* 初始化指针                               */

    if (VOS_FALSE == NAS_GMM_IsRcvRrmmEstCnfMsgValid(pRrEstCnf))
    {
        return;
    }

    if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
    {                                                                           /* 结果为已经存在                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: The result of RRMM_EST_CNF is unexpected");
    }

    switch(pRrEstCnf->ulResult)
    {
    case RRC_EST_RJ_CONGEST:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_CONGESTION;
        break;
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_UNSPECIFIED;
        break;
    case RRC_EST_OTHER_ACCESS_BARRED:
        g_GmmGlobalCtrl.ucRelCause =
                    RR_REL_CAUSE_ACCESS_BARRED_CAUSE_ACCESS_CLASS_CONTROL;
        break;
    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_NO_RF:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RR_CONNECTION_FAILURE;
        break;

    case RRC_EST_RJ_SNW:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RRC_SNW;
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: The result item of RRMM_EST_CNF Msg is SUCCESS");
        break;

    }

    g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                      /* 清等待响应标志                           */

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令建立成功                             */
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;                                 /* 置信令标志位                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: PS signatual exist");
        if (GMM_TIMER_T3312_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {                                                                       /* 如果T3312在运行                          */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* 停T3312                                  */
        }
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_PRESENT);         /* 通知MMC PS域信令连接存在                 */

#if (FEATURE_LTE == FEATURE_ON)
        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            Gmm_TimerStop(GMM_TIMER_T3323);
        }
#endif
        /* 24.008, 4.4.4.9, case f1, CR1099 update:
           W下更新GMM链路控制结构，并更新RRC链路状态 */
        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            /* 在收到RRMM_RESUME_IND时,没有停止T3314,是为了避免CCO失败回退
               所以在收到连接建立成功时需要停止此定时器 */
            Gmm_TimerStop(GMM_TIMER_T3314);

            NAS_MML_SetPsSigConnStatusFlg(VOS_TRUE);

            NAS_MML_SetRrcConnStatusFlg(VOS_TRUE);

            gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_WCDMA;

        }

    }
    else
    {
        /* 链路建立失败，清除GMM链路控制变量 */
        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            NAS_GMM_ClearGmmLinkCtrlStru();
        }

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;
    }


    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态分发                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvRrmmEstCnf_RegInit(pRrEstCnf);                                   /* 调用该状态下的处理                       */
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvRrmmEstCnf_DeregInit(pRrEstCnf);                                 /* 调用该状态下的处理                       */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvRrmmEstCnf_RauInit(pRrEstCnf);                                   /* 调用该状态下的处理                       */
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmEstCnf_ServReqInit(pRrEstCnf);                               /* 调用该状态下的处理                       */
        break;
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        Gmm_RcvRrmmEstCnf_DeregNmlServ(pRrEstCnf);                              /* 调用该状态下的处理                       */
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmEstCnf_RegImsiDtchInit(pRrEstCnf);                           /* 调用该状态下的处理                       */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmEstCnf:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return;
}


VOS_VOID Gmm_RcvRrmmEstCnf_RegInit(
                               VOS_VOID *pMsg                                   /* 原语指针                                 */
                               )
{
    RRMM_EST_CNF_STRU                      *pRrEstCnf;                          /* 定义指针                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* 初始化指针                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* 有消息保留                               */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RegInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3310);                                        /* 起T3310                                  */
    }
    else if (RRC_EST_REGISTER_ACCESS_BARRED == pRrEstCnf->ulResult)
    {                                                                           /* Access barred                            */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);                          /* 调用状态的公共处理                       */
        enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
        if ((GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_ATTACH_COMBINED         == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* 当前流程为combined attach                */
            NAS_GMM_SndMmCombinedAttachRejected(enCause);       /* 发送MMCGMM_COMBINED_ATTACH_REJECTED      */
        }
        else
        {                                                                       /* 当前流程为normal attach                  */
            NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                            enCause);                         /* 发送MMCGMM_GMM_ACTION_RESULT_IND         */
        }


        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);

        /* 事件上报 */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_ATTACH_FAIL,
                        &enCause,
                        NAS_OM_EVENT_ATTACH_FAIL_LEN
                        );

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_ACCESS_BARRED);      /* 通知SM GMM注册失败                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegInit:INFO: specific procedure ended");
    }
    else
    {                                                                           /* 信令连接建立失败                         */
        Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(pRrEstCnf->ulResult,&enCause);
        Gmm_AttachAttemptCounter(enCause);                                      /* 调用attach attempt counter的处理         */

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                     /* 清除正在进行的specific过程标志           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegInit:INFO: specific procedure ended");
    }
    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvRrmmEstCnf_DeregInit(
                                 VOS_VOID *pMsg                                 /* 原语指针                                 */
                                 )
{
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* 定义指针                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* 有其他消息保留                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_DeregInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* 起T3321                                  */
    }
    else
    {                                                                           /* 信令连接建立失败                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );         /* 设置PS域禁止注册标志                     */
        Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }



        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                      GMM_MMC_ACTION_RESULT_FAILURE,
                                      NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_DeregInit:INFO: specific procedure ended");
    }
    return;
}

  

VOS_VOID Gmm_RcvRrmmEstCnfAccessBar_RauInit( VOS_VOID )
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;

    Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);                            /* 调用状态的公共处理                       */
    Gmm_ComCnfHandle();
    enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;

    /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    if ((GMM_RAU_COMBINED          == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_RAU_WITH_IMSI_ATTACH  == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                       /* 如果当前流程是combined RAU               */
        NAS_GMM_SndMmCombinedRauRejected(enCause);          /* 发送MMCGMM_COMBINED_ATTACH_REJECTED      */
    }
    else
    {                                                                       /* 如果当前流程是normal RAU                 */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        enCause);                         /* 发送MMCGMM_GMM_ACTION_RESULT_IND         */
    }


    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 enCause);

    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_FAIL,
                    &enCause,
                    NAS_OM_EVENT_ATTACH_FAIL_LEN
                    );

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnfAccessBar_RauInit:INFO: specific procedure ended");

}


VOS_VOID Gmm_RcvRrmmEstCnf_RauInit(
                               VOS_VOID *pMsg                                   /* 原语指针                                 */
                               )
{
    RRMM_EST_CNF_STRU                      *pRrEstCnf;                          /* 定义指针                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;
    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* 初始化指针                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        if ((RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrEstCnf->ulResult))
        {
            GMM_RauFailureInterSys();
        }
    }
    else
    {
        if ((RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrEstCnf->ulResult))
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        }
    }


    /* 在RAU过程中，不处理Detach */
    if (0 != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & ~GMM_MSG_HOLD_FOR_DETACH) )
    {                                                                           /* 有其他消息保留                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RauInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3330);                                        /* 起T3330                                  */
    }
    else if (RRC_EST_REGISTER_ACCESS_BARRED == pRrEstCnf->ulResult)
    {                                                                           /* Access barred                            */
        /* 为降低函数复杂度，将建链Access bar的处理封装为如下的函数 */
        Gmm_RcvRrmmEstCnfAccessBar_RauInit();
    }
    else
    {
        /* TS24.008
        4.7.5.1.5 Abnormal cases in the MS
        g) Routing area updating and detach procedure collision
        GPRS detach containing detach type"re-attach required" or "re-attach not required":
        If the MS receives a DETACH REQUEST message before the routing area updating procedure has been
        completed, the routing area updating procedure shall be aborted and the GPRS detach procedure shall be
        progressed. If the DETACH REQUEST message contains detach type "re-attach not required" and GMM
        cause #2 "IMSI unknown in HLR", the MS will follow the procedure as described below for the detach type
        "IMSI detach".
        GPRS detach containing detach type "IMSI detach":
        If the MS receives a DETACH REQUEST message before the routing area updating procedure has been
        completed, the routing area updating procedure shall be progressed, i.e. the DETACH REQUEST message
        shall be ignored.


            4.7.4.1.4 Abnormal cases in the MS

            f) Change of cell into a new routing area
        If a cell change into a new routing area occurs before a DETACH ACCEPT message has been received, the
        GPRS detach procedure shall be aborted and re-initiated after successfully performing a routing area updating
        procedure. If the detach procedure is performed due to the removal of the SIM/USIM the MS shall abort the
        detach procedure and enter the state GMM-DEREGISTERED. */

        /* 信令连接建立失败                         */
        Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(pRrEstCnf->ulResult,&enCause);
        Gmm_RoutingAreaUpdateAttemptCounter(enCause);                           /* 调用RAU attempt counter的处理            */

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);


        /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }
    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvRrmmEstCnf_ServReqInit(
                                   VOS_VOID *pMsg                               /* 原语指针                                 */
                                   )
{
    VOS_UINT32           ulCause;                                               /* 定义局部变量                             */
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* 定义指针                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* 有其他消息保留                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_ServReqInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3317);                                        /* 起T3317                                  */
    }
    else
    {                                                                           /* 信令连接建立失败                         */
        if (RRC_EST_OTHER_ACCESS_BARRED == pRrEstCnf->ulResult)
        {                                                                       /* 接入阻塞                                 */
            ulCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;

            /* 当前是SM发起的 Service Request流程, 给SM 回复 Service Rej 消息，以释放上层应用。 */
            if ((GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
                && (GMM_TRUE == g_GmmServiceCtrl.ucSmFlg))
            {
                GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

                g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
            }
        }
        else
        {
            ulCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL;
        }

        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmEstCnf_ServReqInit(): call Gmm_ComCnfHandle to clear msg buffer");

        /* 此处不上报服务状态是因为接入层可能已经点了无服务的灯，如果上报会更改灯状态 */
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
        Gmm_ComCnfHandle();

        NAS_GMM_ProcSavedMmT3211ExpiredNotify();

        if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
        {                                                                       /* 状态是GMM-REGISTERED NORMAL-SERVICE      */
            if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
            {                                                                   /* 存在被挂起的T3311                        */
                Gmm_TimerResume(GMM_TIMER_T3311);                               /* 恢复T3311                                */
            }
            else if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* 存在被挂起的T3302                        */
                Gmm_TimerResume(GMM_TIMER_T3302);                               /* 恢复T3302                                */
            }
            else
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);                                /* 起T3312                                  */
            }
        }
        else if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucState)
        {
            if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
            {                                                                   /* 存在被挂起的T3311                        */
                Gmm_TimerResume(GMM_TIMER_T3311);                               /* 恢复T3311                                */
            }
            else if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* 存在被挂起的T3302                        */
                Gmm_TimerResume(GMM_TIMER_T3302);                               /* 恢复T3302                                */
            }
            else
            {
            }
        }
        else
        {
        }

        if ((VOS_TRUE == NAS_MML_GetDailRejectCfg())
         && (NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL == ulCause))
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_RRC_EST_FAIL);
            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }


        /* 如果当前是NO RF的建联失败，则通知SM需要重新发起PDP激活 */
        else if ( (GMM_FALSE         == GMM_IsCasGsmMode())
          && (RRC_EST_RJ_NO_RF  == pRrEstCnf->ulResult) )
        {
            Gmm_SndSmRelInd();
            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }
        else
        {

        }

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        ulCause);                             /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* 向MMC发送service request结果 */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                              (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)ulCause);
        /* 事件上报 */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REJ,
                        (VOS_VOID *)&ulCause,
                        NAS_OM_EVENT_SERVICE_REJ_LEN);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_ServReqInit:INFO: specific procedure ended");
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;
}


VOS_VOID Gmm_RcvRrmmEstCnf_DeregNmlServ(
                                    VOS_VOID *pMsg                              /* 原语指针                                 */
                                    )
{
    RRMM_EST_CNF_STRU      *pRrEstCnf;                                          /* 定义指针                                 */
    NAS_MSG_STRU           *pNasMsg;                                            /* 定义指针                                 */

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* 初始化指针                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为power off流程                  */
        if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                               /* DETACH REQUEST消息作成                   */

            Gmm_SndRrmmDataReq (RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);             /* 发送RRMM_EST_REQ                         */
        }
        else if (RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        {                                                                       /* 信令连接建立失败                         */
            g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult = pRrEstCnf->ulResult;
        }
        else
        {
        }
    }
    if ((GMM_DETACH_COMBINED_SIM_REMOVE  == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为SIM卡拔出的detach流程          */
        if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                               /* DETACH REQUEST消息作成                   */

            Gmm_SndRrmmDataReq (RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);             /* 发送RRMM_EST_REQ                         */
        }
        else if (RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        {                                                                       /* 信令连接建立失败                         */
            g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult = pRrEstCnf->ulResult;
        }
        else
        {
        }
    }
    return;
}


VOS_VOID Gmm_RcvRrmmEstCnf_RegImsiDtchInit(
                                       VOS_VOID *pMsg                               /* 原语指针                                 */
                                       )
{
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* 定义指针                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* 有其他消息保留                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RegImsiDtchInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
     || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* 起T3321                                  */
    }
    else
    {                                                                           /* 信令连接建立失败                         */
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                           /* 调用状态的公共处理                       */
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* 起T3312                                  */
        }
        g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;          /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegImsiDtchInit:INFO: specific procedure ended");
    }
    return;
}


VOS_VOID Gmm_RcvRrmmRelInd(
                       VOS_VOID *pMsg                                           /* 原语指针                                 */
                       )
{
    VOS_VOID                *pAddr;
    RRMM_REL_IND_STRU       *pRrRelInd;                                         /* 定义指针                                 */

    pRrRelInd = (RRMM_REL_IND_STRU *)pMsg;                                      /* 初始化指针                               */

    /* 如果不是PS域的，GMM丢弃不处理 */
    /* 如果是在以下几个状态等待est_cnf，并且rel cause为RRC_REL_CAUSE_NAS_DATA_ABSENT，丢弃不处理:
        GMM_REGISTERED_INITIATED:
        GMM_DEREGISTERED_INITIATED:
        GMM_ROUTING_AREA_UPDATING_INITIATED:
        GMM_SERVICE_REQUEST_INITIATED:
        GMM_REGISTERED_IMSI_DETACH_INITIATED:
    */
    if (VOS_FALSE == NAS_GMM_IsNeedProcRelInd(pRrRelInd))
    {
        return;
    }



    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                    NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    /* 清除鉴权相关全局变量 */
    NAS_GMM_ClearAuthInfo();

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3319);                                             /* 停止T3319                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    Gmm_TimerStop(GMM_TIMER_T3340);                                             /* 停止T3340                                */
        
    Gmm_TimerStop(GMM_TIMER_DELAY_PS_SMS_CONN_REL);                       


    if (GMM_RRC_RRMM_EST_CNF_FLG ==
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* 清等待响应标志                           */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    }

    /* 如果缓存有关机事件在收到REL_IND时需要处理 */
    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* 如果有保留的power off原语                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO:DEAL HOLD_POWEROFF_MSG");
        Gmm_TimerStop( GMM_TIMER_PROTECT_FOR_SIGNALING );
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;       /* 读取power off原语地址                    */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* 清除保留标志                             */
        Gmm_MsgDistribute( pAddr );                                             /* 保留的消息分发                           */
        Gmm_MemFree( pAddr );
        Gmm_HoldBufferFree();                                                   /* 将保留buffer中所有的消息释放             */
        return;
    }

    switch(pRrRelInd->ulRelCause)
    {
    case RRC_REL_CAUSE_RR_NORM_EVENT:
    case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
    case RRC_REL_CAUSE_T315_EXPIRED:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
        break;
    case RRC_REL_CAUSE_RR_UNSPEC:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_UNSPECIFIED;
        break;
    case RRC_REL_CAUSE_RR_PRE_EMPT_REL:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_PRE_EMPTIVE_RELEASE;
        break;
    case RRC_REL_CAUSE_RR_CONGEST:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_CONGESTION;
        break;
    case RRC_REL_CAUSE_RR_RE_EST_REJ:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RE_ESTABLISH_REJ;
        break;
    case RRC_REL_CAUSE_RR_USER_INACT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_USER_INACTIVITY;
        break;
    case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:
        g_GmmGlobalCtrl.ucRelCause =
                 RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT;
        break;
    case RRC_REL_CAUSE_NAS_REL_ABSENT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_ABORT_RR_UNEXIST_CONNECTION;
        break;
    case RRC_REL_CAUSE_NAS_REL_SUCCESS:
    case RRC_REL_CAUSE_NAS_ABORT:
    case RRC_REL_CAUSE_NAS_STOP_SETUP:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_ABORT_RR_NORMAL;
        break;
    default:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RR_CONNECTION_FAILURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: The Relase Cause is default");
        break;

    }

    g_GmmGlobalCtrl.ucCipherStartFlg = GMM_FALSE;

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;         /* 2G下信令连接标志始终有效 */
        }
        else
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;        /* 3G下信令连接标志清除 */
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: PS signatual nonexist");
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucTcPreSta)
        {
            g_GmmGlobalCtrl.ucTcPreSta = GMM_REGISTERED_NORMAL_SERVICE;
            g_GmmGlobalCtrl.ucSpecProc   = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucServPreSta = GMM_NULL;
        }
        if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucTcPreSta)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* 起T3312                                  */
            Gmm_TimerPauseForTc(GMM_TIMER_T3312);                               /* 挂起T3312                                */
        }
        return;
    }

    if (((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
          ||(GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
        &&(GMM_MSG_HOLD_FOR_SMS == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS)) )
    {   /* 当前有缓存的 SMS 消息,且当前过程正常结束,发起缓存的SMS呼叫 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: Buffered SMS Request will be handled.");
    }
    else
    {
        if (!((GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
            && (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)))
        {

            if (GMM_MSG_HOLD_FOR_SMS
                ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
            {
                Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)VOS_NULL_PTR;

                g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
            }


            /* GCF34.4.8.1测试不通过，由于在G下发短信时候收到T3314超时，此处通知SMS释放 */
            if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType() )
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                      /* 发送PMMSMS_ERROR_IND                     */
            }

        }
    }

    /* GMM收到接入层的连接释放指示，RABM也一定会收到接入层的连接释放指示，RABM
       收到释放指示后会终止当前的RAB重建过程，此时GMM就没有必要继续缓存RABM的
       重建消息了;此时WRR可能没有重建RB,需要GMM通知RABM 建链失败*/
    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的ServiceRequest原语           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);               /* 将保留buffer中所有的消息释放             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)VOS_NULL_PTR;

        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
    }
    if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
        &&(GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProcHold))
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;

        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;                                 /* 2G下信令连接标志始终有效 */
    }
    else
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;                                /* 3G下信令连接标志清除 */
        /* W下清除RRC信令状态 */
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);


        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        if (RRC_RRC_CONN_STATUS_ABSENT == pRrRelInd->ulRrcConnStatus)
        {
            NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
        }
    }

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: PS signatual nonexist");

    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        if (VOS_TRUE == NAS_GMM_ProcSavedWasSysInfo())
        {
            NAS_GMM_FreeWasSysInfo();
            return;
        }
    }
    NAS_GMM_FreeWasSysInfo();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态分发                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvRrmmRelInd_RegInit(pRrRelInd);
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvRrmmRelInd_DeregInit(pRrRelInd);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvRrmmRelInd_RauInit(pRrRelInd);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmRelInd_ServReqInit(pRrRelInd);
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
        Gmm_RcvRrmmRelInd_RegNmlServ(pRrRelInd);
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmRelInd_RegImsiDtchInit(pRrRelInd);
        break;
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        Gmm_RcvRrmmRelInd_DeregNmlServ();
        break;
    case GMM_REGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_RcvRrmmRelInd_PlmnSearch();
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmRelInd:WARNING: g_GmmGlobalCtrl.ucState is WRong");
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        break;
    }

    /* W下，链路释放后，清除GMM链路控制变量 */
    if (VOS_FALSE == GMM_IsCasGsmMode())
    {
        NAS_GMM_ClearGmmLinkCtrlStru();
    }

    /* 在连接释放后，如果缓存的有PS DETACH消息,进行PS detach */
    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);  /* 保留的消息分发                           */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除缓存标志                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();
    return;
}


VOS_VOID Gmm_RcvRrmmRelInd_DeregNmlServ(VOS_VOID)
{

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为power off流程                  */
        Gmm_TimerStop(GMM_TIMER_1S);                                            /* 停5s保护Timer                            */

        NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }

        if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_GMM_SndMmGprsDetachComplete();
        }

        Gmm_ComStaChg(GMM_NULL);
        Gmm_SndMmcPowerOffCnf();                                                /* 发送MMCGMM_POWER_OFF_CNF                 */
        /*Gmm_TimerDistroy();*/                                                     /* 销毁所有Timer                            */
        Gmm_ComVariantInit();                                                   /* 清除全局变量                             */
    }
    if ((GMM_DETACH_COMBINED_SIM_REMOVE  == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为SIM卡拔出的detach流程          */
        NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

        Gmm_TimerStop(GMM_TIMER_1S);                                            /* 停5s保护Timer                            */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_DeregNmlServ:INFO: specific procedure ended");
    }

}


VOS_VOID Gmm_RcvRrmmRelInd_RegInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    VOS_UINT8                           ucRst;

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停T3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    /* 检查是否需要重新发起Attach 流程*/
    ucRst = NAS_GMM_RetryAttachProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起Attach流程 */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            /* 记录标志位，在收到系统消息后重新发起attach流程 */
            g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    g_GmmAttachCtrl.ucRetryFlg = GMM_TRUE;                                      /* 设置换小区不进行attach标志               */


    Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                        /* 调用attach attempt counter的处理         */


    /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;


    g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                         /* 清除正在进行的specific过程标志           */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_RegInit:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* 清除fallowon标志                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvRrmmRelInd_DeregInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    VOS_UINT8                           ucRst;
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;

    ulRelCause = pRrRelInd->ulRelCause;

    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif
    Gmm_TimerStop(GMM_TIMER_T3312);

    if (VOS_OK !=
        Mm_StopRelTimer(WUEPS_PID_GMM, GMM_TIMER_PROTECT_FOR_RR_REL, &g_stGmmProtectRrRelTimer))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_StopRelTimer:WARNING: Stop timer unsuccessfully");
    }
    g_GmmTimerMng.ulTimerRunMask &= ~(0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST != ulRelCause)
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* 检查是否需要重新发起Detach 流程 */
    ucRst = NAS_GMM_RetryDetachProcedureCheck(ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起Detach流程 */
            Gmm_Com_MsInitNormalDetach();
        }
        else
        {
            /* 记录标志位，在收到系统消息后重新发起Detach流程 */
            g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    /*接收到了Detach Accept消息或之前未注册成功*/
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
    }
    else
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 将流程清空                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_DeregInit:INFO: specific procedure ended");

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvRrmmRelInd_RauInit(
                               RRMM_REL_IND_STRU *pRrRelInd                     /* RRMM_REL_IND_STRU类型指针                */
                               )
{
    VOS_UINT8                           ucRst;

    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* 停T3330                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {
        return;
    }

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    /* 检查是否需要重新发起RAU 流程*/
    ucRst = NAS_GMM_RetryRauProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起RAU流程 */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            /* 记录标志位，在收到系统消息后重新发起RAU流程 */
            g_GmmRauCtrl.ucRetryRauForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    /* RAU过程中收到SM请求，被缓存，如果RAU失败，判断当前是否有SM缓存请求，有则给SM发送REL消息 */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (GMM_MSG_HOLD_FOR_SM ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
     && (  (RRC_REL_CAUSE_RR_NORM_EVENT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_RR_USER_INACT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_CELL_UPDATE_FAIL  == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_T315_EXPIRED      == pRrRelInd->ulRelCause) ))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_RauInit(): RAU fail, notify SM when there's SM msg cached");

        Gmm_SndSmRelInd();
    }

    g_GmmRauCtrl.ucRetryFlg = GMM_TRUE;                                     /* 设置换小区需要进行RAU标志                */
    Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);         /* 调用RAU attempt counter的处理            */


    /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}


VOS_VOID Gmm_RcvRrmmRelInd_ServReqInit(
                                   RRMM_REL_IND_STRU *pRrRelInd
                                   )
{
    VOS_UINT8                           ucRst;
    NAS_MSG_STRU                       *pServiceReqMsg;
    VOS_UINT8                           ucDellRejectEnableFlg;
    VOS_UINT32                          ulIsTestCardFlg;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL;

    ulIsTestCardFlg = NAS_USIMMAPI_IsTestCard();

    /* 获取拨号被拒定制是否使能 */
    ucDellRejectEnableFlg = NAS_MML_GetDailRejectCfg();

    Gmm_TimerStop(GMM_TIMER_T3317);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    /* 检查是否需要重新发起SR流程*/
    ucRst = NAS_GMM_RetrySrProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起SR流程 */
            pServiceReqMsg = Gmm_ServiceRequestMsgMake();

            if (VOS_NULL_PTR != pServiceReqMsg)
            {
                Gmm_SndRrmmEstReq(g_GmmGlobalCtrl.ulEstCause,
                                  GMM_RRC_IDNNS_UNKNOWN,
                                  pServiceReqMsg);

                Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);

                /* 此时PS信令连接已经释放,因此过程应该是idle态进行数据业务请求 */
                g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_IDLE;
            }
        }
        else
        {
            /* 记录标志位，在收到系统消息后,根据g_GmmGlobalCtrl.MsgHold中的缓存，
                重新发起SR流程 */
            Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* 调用状态的公共处理                       */
            g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_TRUE;

        }
        return;
    }

    if (((RRC_REL_CAUSE_RR_NORM_EVENT       == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_RR_USER_INACT       == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_CELL_UPDATE_FAIL    == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_T315_EXPIRED        == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_NO_RF               == pRrRelInd->ulRelCause))
     && (GMM_SERVICE_REQUEST_PAGING_RSP != g_GmmGlobalCtrl.ucSpecProc)
     && (VOS_FALSE == ulIsTestCardFlg)
     && (VOS_FALSE == ucDellRejectEnableFlg))
    {
        Gmm_SndSmRelInd();
    }

    if (VOS_TRUE == ucDellRejectEnableFlg)
    {
        GMM_SndSmServiceRej(GMM_SM_CAUSE_UNKNOWN);

        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
    }

    Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* 调用状态的公共处理                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                         /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* 向MMC发送service request结果 */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID *)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_ServReqInit(): call Gmm_ComCnfHandle to clear msg buffer");

    Gmm_ComCnfHandle();

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 状态是GMM-REGISTERED NORMAL-SERVICE      */
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* 起T3312                                  */
        }
    }
    else if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucState)
    {
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
        }
    }
    else
    {
    }

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {                                                                           /* Directed signalling connection           *
                                                                                 * re-establishment                         */
    }
    else
    {                                                                           /* 其他原因                                 */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_ServReqInit:INFO: specific procedure ended");
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvRrmmRelInd_RegNmlServ(
                                  RRMM_REL_IND_STRU *pRrRelInd                  /* 消息指针                                 */
                                  )
{
    VOS_UINT32                          ulIsTestCardFlg;

    ulIsTestCardFlg = NAS_USIMMAPI_IsTestCard();

    /* 开机注册过程中，收到SM的激活请求，注册成功后，立即在原链路上将激活请求发给
        网侧，链路被释放，此时需要通知SM链路释放消息,以重新发起 */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (  (RRC_REL_CAUSE_RR_NORM_EVENT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_RR_USER_INACT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_CELL_UPDATE_FAIL  == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_T315_EXPIRED      == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_NO_RF             == pRrRelInd->ulRelCause))
     && (GMM_SERVICE_REQUEST_PAGING_RSP != g_GmmGlobalCtrl.ucSpecProc)
     && (VOS_FALSE == ulIsTestCardFlg)
     && (GMM_MSG_HOLD_FOR_SM
            != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                        GMM_MSG_HOLD_FOR_SM)))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_RegNmlServ(): Connection release, notify SM when there's SM msg cached");

        Gmm_SndSmRelInd();
    }

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {                                                                           /* 如果RRC释放原因为Directed signalling con
                                                                                 * nection re-establishment                 */
        /* 在正常状态下，只有可能有缓存的SR消息，所以此处只需要清除SR */
        if(GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
        {
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        }

        Gmm_TimerStart(GMM_TIMER_T3312);

        return;
    }
    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
    }
#endif

    Gmm_TimerStart(GMM_TIMER_T3312);                                            /* 起T3312                                  */

    if (GMM_RAU_FOR_INTERSYSTEM == gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauSuccessInterSys();
    }

    if(GMM_FALSE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
    {
        /* 当前REL后不需要发起RAU，可以处理缓存的流程 */
        NAS_GMM_HandleDelayedEvent();
    }

    return;
}


VOS_VOID Gmm_RcvRrmmRelInd_RegImsiDtchInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;
    VOS_UINT8                           ucRst;

    ulRelCause = pRrRelInd->ulRelCause;

    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST != ulRelCause)
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* 检查是否需要重新发起Detach 流程*/
    ucRst = NAS_GMM_RetryDetachProcedureCheck(ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起Detach流程 */
            Gmm_Com_MsInitNormalDetach();
        }
        else
        {
            /* 记录标志位，在收到系统消息后重新发起Detach流程 */
            g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* 调用状态的公共处理                       */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* 清除P_TMSI_SIGNATURE                     */

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 存在被挂起的T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* 恢复T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* 存在被挂起的T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* 恢复T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* 起T3312                                  */
    }
    g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;              /* 将流程清空                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_RegImsiDtchInit:INFO: specific procedure ended");

}


VOS_VOID Gmm_RcvRrmmRelInd_PlmnSearch()
{
    Gmm_TimerStop(GMM_TIMER_WAIT_CONNECT_REL);

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
}


VOS_VOID Gmm_RcvCoverLost_RegInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停T3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* 需要上报给SM                             */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_RRC_EST_FAIL);        /* 通知SM GMM注册失败                       */
        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* 清ucSmCnfFlg标志                         */
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
    }

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;                         /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvCoverLost_DeregInit()
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if ( VOS_OK !=
        Mm_StopRelTimer(WUEPS_PID_GMM, GMM_TIMER_PROTECT_FOR_RR_REL, &g_stGmmProtectRrRelTimer))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_StopRelTimer:WARNING: Stop timer unsuccessfully");
    }
    g_GmmTimerMng.ulTimerRunMask &= ~(0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 将流程清空                               */

    /* detach标记存在丢网时直接回复detach结果 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

    return;                                                                     /* 返回                                     */
}


VOS_VOID NAS_GMM_ProcRauHoldProcedure_RcvCoverLost(VOS_VOID)
{

    /* MMC在发送Coverage lost后自行处理Detach或Attach结果 */
    switch (g_GmmGlobalCtrl.ucSpecProcHold)
    {                                                                       /* 保留的specific流程                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* 通知RABM结果                             */
            break;

        case GMM_DETACH_COMBINED:

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }

                NAS_GMM_SndMmcMmDetachInfo();
            }
            break;

        case GMM_DETACH_NORMAL:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }

                NAS_GMM_SndMmcMmDetachInfo();
            }

            if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
            {
                NAS_GMM_SndMmGprsDetachComplete();
            }
            break;

        case GMM_DETACH_WITH_IMSI:

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }
            break;

        default:
            break;
    }

    g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_FALSE;                                 /* 清除followon标志                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清除正在进行的specific过程标志           */

    return;
}



VOS_VOID Gmm_RcvCoverLost_RauInit()
{
    NAS_MML_RAI_STRU                           *pstLastSuccRai;
    GMM_RAI_STRU                                stRai;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    pstLastSuccRai      = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stRai.Lai.PlmnId);
    stRai.Lai.aucLac[0] = pstLastSuccRai->stLai.aucLac[0];
    stRai.Lai.aucLac[1] = pstLastSuccRai->stLai.aucLac[1];
    stRai.ucRac         = pstLastSuccRai->ucRac;

    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* 停T3330                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    g_GmmRauCtrl.ucRauAttmptCnt++;                                              /* RAU Attempt Counter加1                   */

    if (5 > g_GmmRauCtrl.ucRauAttmptCnt)
    {                                                                           /* ucRauAttmptCnt小于5                      */
        enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

        if ((GMM_TRUE == Gmm_Com_CmpRai(&stRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
         && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus))
        {                                                                       /* RAI相等且更新状态是GU1                   */
        }
        else
        {                                                                       /* RAI不相等或者更新状态不是GU1             */
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
        Gmm_TimerStart(GMM_TIMER_T3311);
    }
    else
    {                                                                           /* ucRauAttmptCnt大于等于5                  */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);     /* 置更新状态为GU2                          */

        /* 在U2状态，保存当前的RAI信息 */
        NAS_GMM_SetAttemptUpdateRaiInfo(NAS_MML_GetCurrCampPlmnInfo());

        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;                             /* 流程结束，清除3312溢出标志               */
        g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }

        /* 24008_CR1904R1_(Rel-11)_C1-113602 Handling of timer T3302 24008 4.7.2.x章节描述如下:
        The MS shall apply this value in the routing area registered by the MS, until a new value is received.
        The default value of this timer is used in the following cases:
        -   ATTACH ACCEPT message, ROUTING AREA UPDATE ACCEPT message, ATTACH REJECT message, or ROUTING AREA UPDATE REJECT message is received without a value specified;
        -   In Iu mode, if the network provides a value in a non-integrity protected Iu mode GMM message and the MS is not attaching for emergency services or not attached for emergency services;
        -   the MS does not have a stored value for this timer; or
        -   a new PLMN which is not in the list of equivalent PLMNs has been entered, the routing area updating fails and the routing area updating attempt counter is equal to 5.
        注册失败达5次，且上次下发t3302定时器时长的网络同当前驻留网络不同，或接入技术不同，则t3302使用默认值。*/
        if (VOS_TRUE == NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax())
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
        }

        Gmm_TimerStart(GMM_TIMER_T3302);

    }



    NAS_GMM_ProcRauHoldProcedure_RcvCoverLost();

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

        GMM_BufferMsgDump();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_ServReqInit
  Function : 在GMM-SERVICE-REQUEST-INITIATED状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2009.8.19  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_ServReqInit()
{
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if ((GMM_SERVICE_REQUEST_DATA_IDLE   == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为SR_DATA                        */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucServPreSta)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucServPreSta))
    {                                                                           /* 状态是GMM-REGISTERED NORMAL-SERVICE      */
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RegNmlServ
  Function : 在GMM-REGISTER-NORMAL-SERVICE状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2009.8.19  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RegNmlServ()
{
    if ((GMM_TRUE == GMM_IsCasGsmMode())
     || (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg))
    {
        return;
    }
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
    }
#endif

    Gmm_TimerStart(GMM_TIMER_T3312);

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RegImsiDtchInit
  Function : 在GMM-REGISTER-IMSI-DETACH-INIT状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2009.8.19  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RegImsiDtchInit()
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 存在被挂起的T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* 恢复T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* 存在被挂起的T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* 恢复T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* 起T3312                                  */
    }

    return;
}


VOS_VOID Gmm_RcvCoverLost_SuspendWaitForSys()
{
    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    g_GmmRauCtrl.ucNpduCnt = 0x0;
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
    }
    else
    {
#if 0
        GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                       GMM_RABM_IMMEDIATELY_RAU);
#endif

        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
    }

    GMM_BufferMsgDump();
}


VOS_VOID Gmm_RcvSmDataReq(
                      VOS_VOID       *pMsg                                          /* 指向原语的指针                           */
                      )
{
    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucSigConFlg))
    {/* 当前PS域接入受限，回复SM失败 */
        GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

        return;
    }

    NAS_GMM_ClearBufferedSmDataReq();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态进行不同处理                     */
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM_DEREGISTERED_INITIATED状态           */
        break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        NAS_GMM_ProcSmDataReq_RAUInit(pMsg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:

        if (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
        {
            if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg); /* 发送 RRMM_DATA_REQ                       */
            }
            else
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
                Gmm_BufSmDataReqMsg(pMsg);
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
            Gmm_BufSmDataReqMsg(pMsg);
        }
        break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVICE            */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
        Gmm_RcvSmDataReq_RegNmlServ(pMsg);
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        Gmm_RcvCmServReq_RegAtmpToUpdt(pMsg);
        break;
    case GMM_REGISTERED_PLMN_SEARCH:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
        Gmm_BufSmDataReqMsg(pMsg);

        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_PDPACT);

        g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_PDPACT;
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
        if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);
        }
        else if (g_GmmGlobalCtrl.SysInfo.ucForbMask != MMCGMM_GSM_NO_FORBIDDEN)
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_FORBID_LA);
        }
        else
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_UNKNOWN);
        }
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_GMM_GetRegUptNeededPsSrvStatus())
        {
            /* 按照正常服务下处理 */
            Gmm_RcvSmDataReq_RegNmlServ(pMsg);
        }
        else
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

        }
        break;
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        break;

    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo(pMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmDataReq:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;                                                                     /* 返回                                     */
}



VOS_VOID NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
)
{
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return;
    }

    /* 在从G切换到W时,需要首先发起RAU恢复PS,然后处理缓冲的SM消息 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
    {
        Gmm_BufSmDataReqMsg(pMsg);

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;


        /* 如果等系统消息定时器在运行，则不下发RAU */
        if (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG == (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_BufferSmDataReq
  Function : 缓存SM发来的DATA_REQ消息
  Input    : VOS_VOID       *pMsg   指向原语的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞 2010.01.07  新规作成
*******************************************************************************/
VOS_VOID Gmm_BufferSmDataReq(VOS_VOID       *pMsg)
{
    GMMSM_DATA_REQ_STRU      *pGmmSmDataReq;                                         /* GMMSM_DATA_REQ_STRU类型指针              */
    GMMSM_DATA_REQ_STRU      *ptr;

    pGmmSmDataReq = (GMMSM_DATA_REQ_STRU *)pMsg;

    if (4 > pGmmSmDataReq->SmMsg.ulNasMsgSize)
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
               + pGmmSmDataReq->SmMsg.ulNasMsgSize) - 4);
    }
    if (VOS_NULL_PTR == ptr)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmDataReq_DeregInit:WARNING: VOS_NULL_PTR pointer in Gmm_RcvSmDataReq_DeregInit");
          return;
    }
    if (4 > pGmmSmDataReq->SmMsg.ulNasMsgSize)
    {
        Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
            + pGmmSmDataReq->SmMsg.ulNasMsgSize) - 4));
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_BufferSmDataReq(): Cache SM data Req");

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)ptr;               /* 保留SM消息                               */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk  |= GMM_MSG_HOLD_FOR_SM;           /* 置SM消息缓存标志                         */

    return;
}

VOS_VOID Gmm_RcvCmServReq_RegAtmpToUpdt(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pMsgHeader;

    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    GMM_LOG_INFO("Gmm_RcvSmDataReq_RegAtmpToUpdt.");

    if ( (WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
      && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
    {
        /* GMM-DEREGISTERED ATTEMPTING-TO-ATTACH状态下，当前版本不支持SMS发起发起PS服务请求 */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        return;
    }
    if ( (WUEPS_PID_SM == pMsgHeader->ulSenderPid)
      && (GMMSM_DATA_REQ == pMsgHeader->ulMsgName)
      && (VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo))
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */

        /* 停止Timer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* 停止Timer3311*/
        Gmm_TimerStop(GMM_TIMER_T3311);

        /*发起RAU过程*/
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

        /*缓存SM消息*/
        Gmm_BufSmDataReqMsg(pMsg);
        g_GmmGlobalCtrl.ulEstCause = ((GMMSM_DATA_REQ_STRU *)pMsg)->ulEstCause;
        return;
    }

    GMM_SndSmServiceRej(GMM_SM_CAUSE_PS_DETACH);
    return;
}


VOS_VOID Gmm_RcvCmServReq_DeregAtmpToAtch(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pMsgHeader;

    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;


    GMM_LOG_INFO("Gmm_RcvCmServReq_DeregAtmpToAtch.");

    if ( (WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
      && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
    {
        /* GMM-DEREGISTERED ATTEMPTING-TO-ATTACH状态下，当前版本不支持SMS发起发起PS服务请求 */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        return;
    }

    if ( (WUEPS_PID_SM == pMsgHeader->ulSenderPid)
      && (GMMSM_ESTABLISH_REQ == pMsgHeader->ulMsgName)
      && (VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo))
    {
        /*
        3gpp 24.008 4.7.3 : The GPRS attach attempt counter shall be reset when the
        MS is in substate ATTEMPTING-TO-ATTACH and
            - expiry of timer T3302;
            - a new routing area is entered; or
            - an attach is triggered by CM sublayer requests.
        */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;

        /* 置给SM回EST_CNF标志为TRUE */
        g_GmmAttachCtrl.ucSmCnfFlg        = GMM_TRUE;

        /* 设置follow on 标志 */
        g_GmmGlobalCtrl.ucFollowOnFlg     = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        /* 停止Timer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* 停止Timer3311 */
        Gmm_TimerStop(GMM_TIMER_T3311);

        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_ATTACH);

        /*发起ATTACH过程*/
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        return;
    }

    Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);

    return;
}


VOS_UINT8 NAS_GMM_GetGmmSmDataReqMsgType(NAS_MSG_STRU *pstMsg)
{
    VOS_UINT8                           ucMsgType;

    if (0x70 == (pstMsg->aucNasMsg[0] & 0x70))
    {
        /* 存在扩展TI时,消息类型取自aucNasMsg[2] */
        ucMsgType  = pstMsg->aucNasMsg[2];
    }
    else
    {
        /* 获取消息类型取自aucNasMsg[1] */
        ucMsgType  = pstMsg->aucNasMsg[1];
    }

    return ucMsgType;

}


VOS_UINT8 NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running(
    GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32                      enMsgType
)
{
    if ((SM_STATUS == enMsgType)
     || (SM_MOD_PDP_CONTEXT_ACC_M2N == enMsgType)
     || (SM_DEACT_PDP_CONTEXT_ACC == enMsgType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}




VOS_VOID Gmm_RcvSmDataReq_RegNmlServ(
                                 VOS_VOID       *pMsg                           /* 指向原语的指针                           */
)
{
    NAS_MSG_STRU                       *pNasMsg;                                /* 定义指针                                 */
    VOS_UINT32                          ulEstCause;                             /* RRC连接建立原因                          */
    GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32  ucMsgType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT8                           ucIsUtranSmcNeeded;

    ucIsUtranSmcNeeded = NAS_UTRANCTRL_IsUtranPsSmcNeeded();

    enCurRat  = NAS_MML_GetCurrNetRatType();
    pNasMsg   = VOS_NULL_PTR;                                                     /* 初始化指针                               */
    ucMsgType = NAS_GMM_GetGmmSmDataReqMsgType(&((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);

    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        Gmm_BufferSmDataReq(pMsg);
        return;
    }

    if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        && (!((NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
            && (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
            && (gstGmmCasGlobalCtrl.ucLastDataSender !=
                                    enCurRat))))
    {                                                                           /* 当前有信令连接                           */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
        {
            /* RESUME FAIL 需要做RAU时，先缓存SM的消息，RAU后再进行处理*/
            if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
            {
                Gmm_BufSmDataReqMsg(pMsg);
            }
            else
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* 发送 RRMM_DATA_REQ                       */
            }
        }


        /* FDD/TDD收到完整性保护或者TDD下不需要完整性保护，也可以发起业务 */
        else if ( ( (VOS_TRUE                              == ucIsUtranSmcNeeded)
                  && (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect) )
               || ( (NAS_MML_NET_RAT_TYPE_WCDMA            == enCurRat)
                 && (VOS_FALSE                             == ucIsUtranSmcNeeded) ) )

        {
            /*判断T3340 是否运行 */
            if ((VOS_FALSE == NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running(ucMsgType))
             && (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG)))
            {
                Gmm_BufferSmDataReq(pMsg);
            }
            else
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* 发送 RRMM_DATA_REQ                       */
            }
        }
        else
        {
            /*完整性保护未打开，需缓存SM消息。
              通过service request可以打开完整性保护
              在GMM_SERVICE_REQUEST_INITIATED状态下,
              收到RRMM_SECURITY_IND(RRC_SECURITY_PS_SMC_RCV)消息，置完整性保护标志位
              收到RRMM_SECURITY_IND(RRC_SECURITY_PS_SMC_CMPL)消息，处理缓存的SM消息*/
            g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

            GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

            g_GmmServiceCtrl.ucSmFlg        = GMM_TRUE;
            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
            g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_SIGNALLING;          /* 存储当前的流程                           */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ:INFO: SR(signaling) procedure started");

            Gmm_BufSmDataReqMsg(pMsg);
            /*Service request*/
            pNasMsg = Gmm_ServiceRequestMsgMake();                          /* 调用make函数                             */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

            Gmm_TimerStop(GMM_TIMER_T3340);
        }
    }
    else if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
          )
    {
        GMM_LOG_INFO("Gmm_RcvSmDataReq_RegNmlServ:Inter System change, Exec select RAU.");

        /*GMM_BufferMsgReceive(pMsg);*/
        Gmm_BufSmDataReqMsg(pMsg);
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    /* 如果此前GMM在建连接的过程中由于RAI改变而主动要求释放正在建立的连接，
       那么对于在等待接入层的连接释放指示以及连接释放指示之后上报的系统消息
       过程中收到的上层请求需要缓存*/
    else if ((GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
          || (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT ==
                                                    g_GmmGlobalCtrl.ucRelCause))
    {
        if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }
        Gmm_BufSmDataReqMsg(pMsg);
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
    {
        /* RESUME 需要做RAU时，先缓存SM的消息，RAU后再进行处理*/
        if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
        {
            Gmm_BufSmDataReqMsg(pMsg);
        }
        else
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* 发送 RRMM_DATA_REQ                       */

            g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
        }
    }
    else
    {                                                                           /* 当前没有信令连接                         */
        if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* Timer3302在运行中                        */
            Gmm_TimerPause(GMM_TIMER_T3302);                                    /* 挂起Timer3302                            */
        }
        else if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* Timer3311在运行中                        */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* 挂起Timer3311                            */
        }
        else
        {
        }
        g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

        GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

        g_GmmServiceCtrl.ucSmFlg        = GMM_TRUE;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_SIGNALLING;          /* 存储当前的流程                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ:INFO: SR(signaling) procedure started");

        /*缓存SM消息*/
        Gmm_BufSmDataReqMsg(pMsg);

        pNasMsg = Gmm_ServiceRequestMsgMake();                                  /* 调用service request制作函数              */

        switch (((GMMSM_DATA_REQ_STRU *)pMsg)->ulEstCause)
        {                                                                       /* 转换原因值                               */
        case GMM_SM_RRC_EST_CAUSE_ORG_CONV_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_STM_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_STREAM_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_INTER_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_INTERACT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_BG_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ():INFO: The RRC Connection Setup Cause is GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL");
            ulEstCause = RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL;
            break;
        }

        g_GmmGlobalCtrl.ulEstCause = ulEstCause;
        Gmm_SndRrmmEstReq(ulEstCause, GMM_RRC_IDNNS_UNKNOWN, pNasMsg);          /* 进行service request(signalling)          */
        Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REQ,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_RegInit(
                                  VOS_VOID    *pMsg,                                /* 消息指针                                 */
                                  VOS_UINT8   ucRaiChgFlg,                          /* RAI变化标志                              */
                                  VOS_UINT8   ucDrxLengthChgFlg,                    /* DRX length变化标志                       */
                                  VOS_UINT8   ucLaiChgFlg                           /* LAI变化标志                              */
                                  )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */
    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 初始化指针                               */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GPRS_NOT_SUPPORT);       /* 通知SM GMM注册失败                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegInit:INFO: specific procedure ended");

        if (((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
          && (GMM_FALSE == ucLaiChgFlg))
        {                                                                       /* LA没变,并且是A+I                         */
            NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* 通知SM GMM注册失败                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if ((GMM_TRUE == ucRaiChgFlg)
        || (VOS_TRUE == g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg))
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                    /* 标记GMM不能进行RAU时不需要触发MM的LU过程 */
    }
    else
    {
    }
    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_DeregInit(
                                    VOS_VOID    *pMsg,                              /* 消息指针                                 */
                                    VOS_UINT8   ucRaiChgFlg,                        /* RAI变化标志                              */
                                    VOS_UINT8   ucDrxLengthChgFlg,                  /* DRX length变化标志                       */
                                    VOS_UINT8   ucLaiChgFlg                         /* LAI变化标志                              */
                                    )
{
    VOS_UINT8                           ucDetachType;
    MMCGMM_SYS_INFO_IND_STRU            *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 初始化指针                               */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();

            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH) )
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
        }
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_DeregInit:INFO: specific procedure ended");
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else if (((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
        && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
    {                                                                           /* RA改变或者DRX改变                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (VOS_TRUE == g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg)
    {
        ucDetachType = NAS_GMM_GetDetachTypeFromProcName(g_GmmDetachCtrl.ucDetachProc);
        if (GMM_INVALID_DETACH_TYPE != ucDetachType)
        {
            Gmm_MsInitNormalDetach(ucDetachType);
        }
    }
    else
    {
    }
    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_RauInit(
                                  VOS_VOID    *pMsg,                                /* 消息指针                                 */
                                  VOS_UINT8   ucRaiChgFlg,                          /* RAI变化标志                              */
                                  VOS_UINT8   ucDrxLengthChgFlg,                    /* DRX length变化标志                       */
                                  VOS_UINT8   ucLaiChgFlg                           /* LAI变化标志                              */
                                  )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        /* 当前驻留的位置区与之前驻留的位置区LAI没改变,并且在网络模式I,并且T3312超时 */
        if ((GMM_FALSE == ucLaiChgFlg)
         && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                        /* 通知MM进行LU                             */
            }
            else
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
            }
        }
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_ComCnfHandle();

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RauInit:INFO: specific procedure ended");
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd_RauInit(): call Gmm_ComCnfHandle to clear msg buffer");

        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
             == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else if ((GMM_TRUE == ucRaiChgFlg)
        ||(VOS_TRUE == g_GmmRauCtrl.ucRetryRauForRelCtrlFlg))
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);                                    /* 更新状态设为GU2                          */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* 标记GMM不能进行RAU时要触发MM的LU过程     */
    }
    else
    {
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_ServReqInit(
                                      VOS_VOID    *pMsg,                            /* 消息指针                                 */
                                      VOS_UINT8   ucRaiChgFlg,                      /* RAI变化标志                              */
                                      VOS_UINT8   ucDrxLengthChgFlg,                /* DRX length变化标志                       */
                                      VOS_UINT8   ucLaiChgFlg                       /* LAI变化标志                              */
                                      )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_ComCnfHandle();
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_ServReqInit:INFO: specific procedure ended");
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */
    }
    else if ((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
    {                                                                           /* RA改变或者DRX改变                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }

        if (GMM_TRUE == ucRaiChgFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;        /* 保留被中断的SR流程                       */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else
    {
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_DeregNmlServ(
                                       VOS_VOID    *pMsg,                           /* 消息指针                                 */
                                       VOS_UINT8   ucLaiChgFlg                      /* LAI变化标志                              */
                                       )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* 原来SIM无效                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        if(MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                         /* 调用状态的公共处理                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not allow Attach");

        /* 此时可能有缓冲的SM注册请求消息 */
        GMM_BufferMsgResume();
        return;
    }
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if ((GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
            && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {                                                                       /* 前一个小区也不支持GPRS                   */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not support GPRS and No cell available");
            return;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_FORBID_LA);
    }
    else
    {                                                                           /* 小区改变                                 */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        NAS_GMM_HandleModeANOIWhenDeregister();
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch(
                                          VOS_VOID    *pMsg,                        /* 消息指针                                 */
                                          VOS_UINT8   ucRaiChgFlg,                  /* RAI变化标志                              */
                                          VOS_UINT8   ucDrxLengthChgFlg,            /* DRX length变化标志                       */
                                          VOS_UINT8   ucLaiChgFlg                   /* LAI变化标志                              */
                                          )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if ((GMM_TRUE == ucRaiChgFlg)
        &&  (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask))
        {
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                              /* attach attempt counter清0                */
        }
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */


        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter清0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else
    {
        if ((GMM_TRUE == g_GmmAttachCtrl.ucRetryFlg)
          &&(GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucCellChgFlg))
        {                                                                       /* 换小区需要进行attach                     */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                               /* 进行Attach                               */
            g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        }
        else
        {
            /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后一个判断，UE会一直发起ATTACH */
            if ((GMM_TIMER_T3302_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && ((GMM_TIMER_T3311_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
            {
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }
            else
            {


                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);


                if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    NAS_GMM_SndMmCombinedAttachInitiation();
                    NAS_GMM_SndMmCombinedAttachRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
            }
        }
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_RegNmlServ(
                                     VOS_VOID    *pMsg,                             /* 消息指针                                 */
                                     VOS_UINT8   ucRaiChgFlg,                       /* RAI变化标志                              */
                                     VOS_UINT8   ucDrxLengthChgFlg,                 /* DRX length变化标志                       */
                                     VOS_UINT8   ucLaiChgFlg                        /* LAI变化标志                              */
                                     )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;

    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

    VOS_UINT32                          ulIsAModeAndNetworkIFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;

    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ulIsAModeAndNetworkIFlg = NAS_GMM_IsAModeAndNetworkI();

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();
    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    /* GMM_REGISTERED_PLMN_SEARCH状态单独提取出一个函数处理 */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT == g_GmmGlobalCtrl.ucRelCause)
    {
        if( VOS_TRUE == RABM_IsExistBufferUplinkData() )
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }
#if (FEATURE_ON == FEATURE_LTE)
    /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后时长是否为0的判断，UE会一直发起ATTACH */
    else if (((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
            && (GMM_TIMER_T3311_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
            && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
          || (GMM_TRUE == ucRaiChgFlg))
#else
    else if (GMM_TRUE == ucRaiChgFlg)
#endif
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }

        /*4.2.5.1.7 Substate, ATTEMPTING-TO-UPDATE-MM
        - perform routing area update indicating "combined RA/LA updating with
        IMSI attach" when the routing area of the serving cell has changed and
        the location area this cell is belonging to is not in the list of forbidden LAs.*/

        if ( (VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
          && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState) )

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        /* GMM_REGISTERED_PLMN_SEARCH状态单独提取出一个函数处理 */
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    /* GMM_REGISTERED_PLMN_SEARCH状态单独提取出一个函数处理 */

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        /* 链路释放后，需要重新发起Service Request流程 */
        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        Gmm_DealWithBuffAfterProc();
    }


    else if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (VOS_TRUE == ulIsAModeAndNetworkIFlg)
          && (VOS_TRUE == ucCsAttachAllow)
          && (VOS_FALSE == ucCsRestrictionFlg))
    {

        /* cs exist service, GMM should not originate RAU when RAI no change  */
        if (GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CS通信中的normal RAU(A+I)                */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);      /* 进行RAU过程                              */
                }
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else if (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CS通信中的normal attach(A+I)             */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(
                                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);   /* 进行RAU过程                              */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else
        {
            NAS_GMM_HandleModeANOIWhenRAInotChange();

            if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* T3311不在运行时才发起RAU */
                if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            /* <==A32D12438 */
            /*
            当Rau、Sr、Detach过程建立信令连接的时候发生RAI改变，此时状态迁移到
            GMM_REGISTERED_NORMAL_SERVICE，等待底层释放连接，并上报系统信息，
            如果上报的系统信息显示又回到最初的小区，那么此时不会发起Rau，但是
            需要将前面被中断的流程进行完
            */
            else if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
            {
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                Gmm_RoutingAreaUpdateHandleFollowOn();
            }
            else if (GMM_SERVICE_REQ_NONE != g_GmmGlobalCtrl.enServReq)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    /*W接入层暂不支持搜网下接收到寻呼*/
                }
                else
                {
                    Gmm_DealWithBuffAfterProc();
                }
            }
            else
            {
            }

            if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
        }
    }

    /* GMM_REGISTERED_PLMN_SEARCH状态单独提取出一个函数处理 */

    else
    {
        /*
        当Rau、Sr、Detach过程建立信令连接的时候发生RAI改变，此时状态迁移到
        GMM_REGISTERED_NORMAL_SERVICE，等待底层释放连接，并上报系统信息，
        如果上报的系统信息显示又回到最初的小区，那么此时不会发起Rau，但是
        需要将前面被中断的流程进行完
        */

        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            if (VOS_FALSE == ucCsRestrictionFlg)
            {
                NAS_GMM_NotifyMmUnrealCombinedRauResult();
            }
            else
            {
                NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                   /* 发送MMCGMM_GMM_ACTION_RESULT_IND给MMC    */

            }
        }


        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
            && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            Gmm_RoutingAreaUpdateHandleFollowOn();
        }

        /* 原来T3312超时是在suspend wait for sysinfo状态处理的,因为L handover to W,
           状态迁到了register normal service状态,所以需要在此状态下处理T3312超时 */
        if ((VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
         && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
         && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }

    }

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
        {
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
        }
    }
    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;                                                                     /* 返回                                     */
}


VOS_VOID NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch(
                                     VOS_VOID    *pMsg,                             /* 消息指针                                 */
                                     VOS_UINT8   ucRaiChgFlg,                       /* RAI变化标志                              */
                                     VOS_UINT8   ucDrxLengthChgFlg,                 /* DRX length变化标志                       */
                                     VOS_UINT8   ucLaiChgFlg                        /* LAI变化标志                              */
                                     )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;

    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

    VOS_UINT32                          ulIsAModeAndNetworkIFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;

    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ulIsAModeAndNetworkIFlg = NAS_GMM_IsAModeAndNetworkI();

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();
    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_TRUE == ucRaiChgFlg)
    {
        if ( (GMM_REGISTERED_NO_CELL_AVAILABLE    == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta))
        {
            /* 在由ATTEMPT TO UPDATE或者REGISTERED_NO_CELL_AVAILABLE状态经过
               搜网后收到系统消息，需要清除ATTEMPT COUNTER */
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;
            }
        }
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
    }
    /* RAU被用户指定搜打断，后续搜到同一个RAI网络需要停T3311定时器并发起注册 */
    else if ((VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
          && (GMM_FALSE == ucRaiChgFlg)
          && (VOS_TRUE == pSysInfo->ulUserSrchFlg))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch: User NW Srch, need to stop T3311 and send RAU Req");
        /* 用户发起的指定搜网，强制发起注册 */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT == g_GmmGlobalCtrl.ucRelCause)
    {
        if( VOS_TRUE == RABM_IsExistBufferUplinkData() )
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }
#if (FEATURE_ON == FEATURE_LTE)
    /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后时长是否为0的判断，UE会一直发起ATTACH */
    else if (((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
            && (GMM_TIMER_T3311_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
            && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
          || (GMM_TRUE == ucRaiChgFlg))
#else
    else if (GMM_TRUE == ucRaiChgFlg)
#endif
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }

        if (VOS_TRUE == NAS_GMM_BackToOrgPlmnAfterCoverageLost(pMsg))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    else if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
    {
        NAS_GMM_IsrActiveRaiNoChg_InterSys();
    }

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        /* 链路释放后，需要重新发起Service Request流程 */
        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        Gmm_DealWithBuffAfterProc();
    }


    else if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (VOS_TRUE == ulIsAModeAndNetworkIFlg)
          && (VOS_TRUE == ucCsAttachAllow)
          && (VOS_FALSE == ucCsRestrictionFlg))
    {

        /* cs exist service, GMM should not originate RAU when RAI no change  */
        if (GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CS通信中的normal RAU(A+I)                */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);      /* 进行RAU过程                              */
                }
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else if (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CS通信中的normal attach(A+I)             */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(
                                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);   /* 进行RAU过程                              */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else
        {
            NAS_GMM_HandleModeANOIWhenRAInotChange();

            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* T3311不在运行时才发起RAU */
                if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
            /* <==A32D12438 */
            /*
            当Rau、Sr、Detach过程建立信令连接的时候发生RAI改变，此时状态迁移到
            GMM_REGISTERED_NORMAL_SERVICE，等待底层释放连接，并上报系统信息，
            如果上报的系统信息显示又回到最初的小区，那么此时不会发起Rau，但是
            需要将前面被中断的流程进行完
            */
            else if (GMM_SERVICE_REQ_NONE != g_GmmGlobalCtrl.enServReq)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    /*W接入层暂不支持搜网下接收到寻呼*/
                }
                else
                {
                    Gmm_DealWithBuffAfterProc();
                }
            }
            else
            {
            }

            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
    }
    else
    {
        if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }

        /* T3311未超时按如下流程处理 */
        else if (GMM_FALSE == g_GmmRauCtrl.ucT3311ExpiredFlg)
        {
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
            {
                if (GMM_FALSE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
                }
                else
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;


                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }



                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    {
                        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                        Gmm_RoutingAreaUpdateHandleFollowOn();
                    }
                }
            }
            else if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
            {
                /*
                3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
                reset when the MS is in substate ATTEMPTING-TO-UPDATE and
                    - a new routing area is entered;
                    - expiry of timer T3302; or
                    - at request from registration function.
                */
                g_GmmRauCtrl.ucRauAttmptCnt = 0;

                /* 停止Timer3302 */
                Gmm_TimerStop(GMM_TIMER_T3302);

                /* 停止Timer3311*/
                Gmm_TimerStop(GMM_TIMER_T3311);

                /* 发起RAU过程 */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                if ((GMM_TIMER_T3311_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
                 || (GMM_TIMER_T3302_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG)))
                {
                    Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }

                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }

            }

            if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
            {
                /*W接入层暂不支持搜网下接收到寻呼*/
            }
            else if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
            {
                Gmm_DealWithBuffAfterProc();
            }
            else
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
        }
        /* T3311超时在REGISTERED_PLMN_SRCH状态需要发起RAU */
        else if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
        }
    }

    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_RegUpdtNeed(
                                        VOS_VOID    *pMsg,                          /* 消息指针                                 */
                                        VOS_UINT8   ucLaiChgFlg                     /* LAI变化标志                              */
                                        )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */
    VOS_UINT8                    ucCsRestrictionFlg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */

        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
          && (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ();
    }
    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else
    {                                                                           /* 小区改变                                 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        if (VOS_TRUE == NAS_GMM_BackToOrgPlmnAfterCoverageLost(pMsg))
        {
            return;
        }

        if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            &&(GMM_FALSE == gstGmmCasGlobalCtrl.ucSysRauFlg))
        {
            ucCsRestrictionFlg = NAS_MML_GetCsRestrictRegisterFlg();

            if (!((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)))
            {                                                                   /* 非A+I                                    */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
                  || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
                  || (VOS_TRUE == ucCsRestrictionFlg))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else
            {                                                                   /* A+I                                      */
                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* 调用RAU过程combined RAU with IMSI attach */
            }
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
        }

    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt(
                                        VOS_VOID    *pMsg,                          /* 消息指针                                 */
                                        VOS_UINT8   ucRaiChgFlg,                    /* RAI变化标志                              */
                                        VOS_UINT8   ucDrxLengthChgFlg,              /* DRX length变化标志                       */
                                        VOS_UINT8   ucLaiChgFlg                     /* LAI变化标志                              */
                                        )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            }
        }
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter清0                   */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else
    {
        if ((GMM_TRUE == g_GmmRauCtrl.ucRetryFlg)
          &&(GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucCellChgFlg))
        {                                                                       /* 换小区需要进行RAU                        */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */
            g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        }

        else
        {
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            }

        }
    }

    return;                                                                     /* 返回                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_RegNoCell(
                                    VOS_VOID    *pMsg,                              /* 消息指针                                 */
                                    VOS_UINT8   ucRaiChgFlg,                        /* RAI变化标志                              */
                                    VOS_UINT8   ucDrxLengthChgFlg,                  /* DRX length变化标志                       */
                                    VOS_UINT8   ucLaiChgFlg                         /* LAI变化标志                              */
                                    )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsRestrictionFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
#endif

    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType         = NAS_MML_GetTinType();
#endif

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucSimCsRegStatus        = NAS_MML_GetSimCsRegStatus();

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

#if (FEATURE_ON == FEATURE_LTE)
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg)
        {
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;

            if (GMM_FALSE == ucLaiChgFlg)
            {
                if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                {
                    NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);             /* 通知MM进行LU                             */
                }
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
          && ((GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
           || (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState)))
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }
#endif
#if (FEATURE_ON == FEATURE_LTE)
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
           && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg)
           && (NAS_MML_TIN_TYPE_GUTI != enTinType))
#else
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
           && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg))
#endif
    {                                                                           /* 回到原来的RA并且DRX参数没有改变          */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
        {
            NAS_GMM_IsrActiveRaiNoChg_InterSys();
            return;
        }
#endif

        if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {                                                                       /* 出覆盖区时T3312未溢出                    */
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED
                == NAS_MML_GetPsUpdateStatus())
            {                                                                   /* 更新状态是GU1                            */

                /* T3311超时在REGISTERED_PLMN_SRCH状态需要发起RAU */
                if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }
                else
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;            /* 设置假流程标志                           */

                    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
                     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)
                     || (VOS_TRUE == ucCsRestrictionFlg))
                    {                                                               /* 非A+I                                    */
                        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);               /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                        }

                        /* 如果之前出服务区，T3312超时，启动了T3323,后重进服务区，需要停止T3323*/
                        Gmm_TimerStop(GMM_TIMER_T3323);
#endif
                        Gmm_TimerStart(GMM_TIMER_T3312);                            /* 启动T3312                                */
                        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                        /* 向MMC发送PS注册结果 */
                        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                                     NAS_MML_REG_FAIL_CAUSE_NULL);

                        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* 设置真流程标志                           */
                    }
                    else
                    {                                                               /* A+I                                      */
                        if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
                        {                                                           /* 更新状态是U1,并且Gs关联已存在            */
                            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);           /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                            {
                                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                            }
#endif
                            Gmm_TimerStart(GMM_TIMER_T3312);                        /* 启动T3312                                */
                            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                            {                                                       /* 需要给SM回EST_CNF                        */
                                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                                Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* 向SM回建立成功的响应                     */
                            }


                            /* 向MMC发送PS注册结果 */
                            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                                         NAS_MML_REG_FAIL_CAUSE_NULL);

                            if (VOS_TRUE == ucCsAttachAllow)
                            {                                                       /* CS域允许注册                             */
                                NAS_GMM_SndMmCombinedRauInitiation();
                                NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                                               NAS_MML_REG_FAIL_CAUSE_NULL,
                                                               VOS_NULL_PTR,
                                                               VOS_NULL_PTR);                                      /* 发送 MMCGMM_COMBINED_RAU_ACCEPTED        */

                                /*更新RAU记数器 */
                                if(5<=g_GmmRauCtrl.ucRauAttmptCnt)
                                {
                                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                                }
                            }
                            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* 设置真流程标志                           */
                        }
                        else
                        {                                                           /* 更新状态不是U1,或者Gs关联已经移除                           */
                            if ((VOS_TRUE != ucSimCsRegStatus)
                             || (VOS_FALSE == ucCsAttachAllow))
                            {                                                       /* sim无效或者CS域不允许注册                */
                                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);       /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                                {
                                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                                }
#endif
                                Gmm_TimerStart(GMM_TIMER_T3312);                    /* 启动T3312                                */
                                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                                {                                                   /* 需要给SM回EST_CNF                        */
                                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* 向SM回建立成功的响应                     */
                                }
                                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                                /* 向MMC发送PS注册结果 */
                                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                                             NAS_MML_REG_FAIL_CAUSE_NULL);

                                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                                g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* 设置真流程标志                           */
                            }
                            else
                            {
                                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_UPDATING_TYPE_INVALID);                     /* 调用RAU                                  */
                            }
                        }
                    }
                }
            }
            else
            {                                                                   /* 更新状态不是GU1                          */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* 调用RAU                                  */
            }

            if(GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            {
                if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
                {
                    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
                }
                if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
                {
                    Gmm_DealWithBuffAfterProc();
                    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;
                }
            }
        }
        else
        {                                                                       /* 出覆盖区时T3312溢出                      */
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                      /* 清除出覆盖区标志                         */
            if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
             || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* 非A+I                                    */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
                  || (VOS_TRUE == ucCsRestrictionFlg)
                  || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
            {/* A+I 模式，但CS域被 BAR, 或者 当前 CS 通话中 */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else
            {                                                                   /* A+I                                      */
                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* 调用RAU过程combined RAU with IMSI attach */
            }
        }
    }
    else
    {                                                                           /* RA改变或者DRX参数变化                    */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* 清除T3312溢出标记                        */

        if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* 非A+I                                    */
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 调用RAU过程                              */
        }
    }

    return;                                                                     /* 返回                                     */
}



VOS_VOID Gmm_RcvMmcSysInfoInd_SuspWaitSys(VOS_VOID* pRcvMsg,VOS_UINT8 ucRaiChgFlg,VOS_UINT8 ucLaiChgFlg)
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */
    VOS_VOID                           *pAddr;
    VOS_UINT8                           ucCsAttachAllow;

    VOS_UINT8                           ucSimCsRegStatus;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT8                           ucCsRestrictFlg;
    GMM_RAI_STRU                        stRai;


#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType         = NAS_MML_GetTinType();

    pstConnStatus             = NAS_MML_GetConnStatus();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                    NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();
    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                             /* 强制类型转换                             */

    pstCsSuccLai     = NAS_MML_GetCsLastSuccLai( );
    stRai.ucRac = pstCsSuccLai->ucRac;
    /* 填写LAC */
    stRai.Lai.aucLac[0] = pstCsSuccLai->aucLac[0];
    stRai.Lai.aucLac[1] = pstCsSuccLai->aucLac[1];                       /* LAC */
    /* 填写PLMN */
    stRai.Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    stRai.Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    stRai.Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    stRai.Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    stRai.Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    stRai.Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    stRai.Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == stRai.Lai.PlmnId.aucMncDigit[2])
    {
        stRai.Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* 原来SIM无效                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        GMM_LOG_INFO("Gmm_RcvMmcSysInfoInd_SuspWaitSys:the cell not support GPRS.");
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_REGSTER_AND_SHUTDOWN_TIMER);                                           /* 停所有Timer                              */

        /*异系统改变时通知RABM*/
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            }
        }

        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                 /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */


        /*异系统改变时通知RABM*/
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {/* 新的RA,处理网络模式变更 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter清0                   */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;

        if (GMM_NETMODE_CHG_NULL == gstGmmSuspendCtrl.ucNetModeChange)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */
        }
        else
        {
            GMM_ProcedureByNetMode(gstGmmSuspendCtrl.ucNetModeChange);
        }
    }
    else                                                                        /* RA 相同 */
    {
        /* reference to 23.401 10.5.1.3 L->GU handover时,RAI不改变不需要进行RAU; TIN指示为GUTI时需要进行RAU */






        if ((((GMM_IU_PMM_CONNECTED == gstGmmSuspendCtrl.ucPreSrvState)
           || (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause))
          && (NAS_MML_NET_RAT_TYPE_LTE != gstGmmSuspendCtrl.ucPreRat))
#if (FEATURE_ON == FEATURE_LTE)
         || (NAS_MML_TIN_TYPE_GUTI == enTinType)
#endif
         )

        {

            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);
            g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */

        }
        else if (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
        {
            /*异系统改变时通知RABM*/
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* G->W,G下不支持GPRS,到W下后,如果RAI不改变,重新调用下GMM_REGISTERED_UPDATE_NEEDED
               状态下接收到系统消息的处理函数. */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE== gstGmmSuspendCtrl.ucPreState)
             || (GMM_ROUTING_AREA_UPDATING_INITIATED== gstGmmSuspendCtrl.ucPreState))
            {
                Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                               ucRaiChgFlg,
                                               GMM_FALSE,
                                               ucLaiChgFlg);
            }
#if (FEATURE_ON == FEATURE_LTE)
                /* L重选到G,路由区未改变，ISR激活，无需做RAU时需要更新状态，
                  否则为register no cell available，后续无法做业务 */
            else if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))

            {
                NAS_GMM_IsrActiveRaiNoChg_InterSys();
            }
#endif
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
                if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
                }
                else
                {
                    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    {
                        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                    }
                    GMM_BufferMsgResume();
                }
            }
        }
        /* NMO1下,不通过手机模式判断是否需要进行联合注册 */
        else if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (VOS_TRUE == ucCsAttachAllow)
              && (GMM_RAU_NORMAL_CS_UPDATED == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
              && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        }
        else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);
            /* NMO1下,不通过手机模式判断是否需要进行联合注册 */
            if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
             && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && (VOS_TRUE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
        else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }

#endif
        else
        {
            /*异系统改变时通知RABM*/
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* G->W, G下接入禁止或者不支持GPRS，到W下后，如果RAC不改变，重新调用下GMM_REGISTERED_UPDATE_NEEDED
               状态下的系统消息处理函数 */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE == gstGmmSuspendCtrl.ucPreState))
            {

                if (MMC_SUSPEND_CAUSE_CELLRESELECT == gstGmmSuspendCtrl.ucSuspendCause)
                {
                    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
                }

                Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                               ucRaiChgFlg,
                                               GMM_FALSE,
                                               ucLaiChgFlg);

                gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

            }
            else
            {
                /* 在网络模式I下，Gs口不存在,并且接入不受限时,需要发起联合的RAU重建Gs口 */
                /* PS access bar已经在预处理中判断,所以此处不用判断PS接入禁止 */
                if ((VOS_FALSE                            == Gmm_Compare_Rai(&stRai, &(g_GmmGlobalCtrl.SysInfo.Rai)))
                 && (VOS_TRUE                             == ucCsAttachAllow)
                 && (GMM_NET_MODE_I                       == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_TRUE                             == ucSimCsRegStatus)
                 && (VOS_FALSE                            == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                 && (VOS_FALSE                            == ucCsRestrictFlg))
                {
                    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
                    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                    return;
                }

                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeSuccess();

#if (FEATURE_ON == FEATURE_LTE)
                /* L重选到G,路由区未改变，ISR激活，无需做RAU时需要更新状态，
                  否则为register no cell available，后续无法做业务 */
                if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
                 && (VOS_FALSE == pstConnStatus->ucPsSigConnStatusFlg))
                {
                    NAS_GMM_IsrActiveRaiNoChg_InterSys();
                }
                else
#endif
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }

                }


                if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    switch (g_GmmGlobalCtrl.ucSpecProcHold)
                    {                                                               /* 保留的specific流程                       */
                    case GMM_SERVICE_REQUEST_DATA_IDLE:
                    case GMM_SERVICE_REQUEST_DATA_CONN:
                        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);     /* 发送GMMRABM_REESTABLISH_CNF(fail)        */
                        break;
                    case GMM_SERVICE_REQUEST_SIGNALLING:
                        if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
                        {
                            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);              /* 发送PMMSMS_ERROR_IND                     */
                        }
                        if (GMM_MSG_HOLD_FOR_SM
                            ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                                    GMM_MSG_HOLD_FOR_SM))
                        {                                                           /* 如果有保留的SmDataReq原语                */
                            NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd_SuspWaitSys(): Clear cached SM data Req");

                            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &=
                                ~GMM_MSG_HOLD_FOR_SM;                               /* 清除保留标志                             */
                            pAddr =
                                (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm; /* 读取SmDataReq原语地址                    */
                            Gmm_MemFree(pAddr);                                     /* 释放保存的SM消息                         */
                        }
                        break;
                    default:
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:INFO: No Hold Procedure");
                        break;
                    }
                    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
                }
            }
        }
    }

    return;
}


/*******************************************************************************
  Module   : Gmm_ComCmpLai
  Function : LAI的比较
  Input    : GMM_LAI_STRU   *pMsg       指向LAI的指针
  Output   : 无
  NOTE     : 无
  Return   : GMM_TRUE    相同
             GMM_FALSE   不同
  History  :
    1. 张志勇  2003.12.10  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_ComCmpLai(
                    GMM_LAI_STRU *pMsg                                          /* 指向LAI的指针                            */
                    )
{
    VOS_UINT8 ucRet;                                                                /* 定义返回值                               */

    ucRet = GMM_FALSE;                                                          /* 初始化                                   */

    if (GMM_TRUE == Gmm_Com_CmpPlmnid(&pMsg->PlmnId))
    {                                                                           /* PLMN相同                                 */
        if ((pMsg->aucLac[0]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0])
            &&(pMsg->aucLac[1]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1]))
        {                                                                       /* LAC相同                                  */
            ucRet = GMM_TRUE;                                                   /* 赋返回值                                 */
        }
    }

    return ucRet;                                                               /* 返回                                     */
}


VOS_VOID NAS_GMM_RcvMmAuthenticationFailureInd(VOS_VOID)
{
    VOS_UINT8                           ucGmmPreState;
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态                             */
        case GMM_REGISTERED_INITIATED:
        case GMM_DEREGISTERED_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_DEREGISTERED_NO_IMSI:
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_UPDATE_NEEDED:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_REGISTERED_PLMN_SEARCH:
        case GMM_DEREGISTERED_PLMN_SEARCH:

            Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
            g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {                                                                       /* 需要向SM回响应                           */
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_AUTHENTICATION_FAIL); /* 通知SM GMM注册失败                       */
                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
            }
            if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
            {                                                                       /* SMS在等待响应                            */
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                          /* 发送PMMSMS_ERROR_IND                     */
                g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
            }
            if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                       /* 需要向RABM回响应                         */
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* 发送GMMRABM_REESTABLISH_CNF(failure)     */
            }
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前流程                             */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcAuthenticationFailureInd:INFO: specific procedure ended");
            g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* 清除保留流程                             */

            Gmm_HoldBufferFree();                                                   /* 清除保留消息                             */

            gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NO_IMSI;
            ucGmmPreState = g_GmmGlobalCtrl.ucState;
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* 调用状态的公共处理                       */

            if (GMM_REGISTERED_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }
            else if (GMM_ROUTING_AREA_UPDATING_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }
            else if (GMM_SERVICE_REQUEST_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                                      NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }

            else if (GMM_GPRS_SUSPENSION == ucGmmPreState)
            {
                Gmm_ComStaChg(GMM_GPRS_SUSPENSION);                                /* 调用状态的公共处理                       */
            }
            else if (GMM_SUSPENDED_GPRS_SUSPENSION == ucGmmPreState)
            {
                Gmm_ComStaChg(GMM_SUSPENDED_GPRS_SUSPENSION);                                /* 调用状态的公共处理                       */
            }
            else
            {
            }

            /* 清除相关标志 */
            NAS_GMM_ClearIMSIOfUeID();

            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* 更新状态更新为GU3 ROAMING NOT ALLOWED    */
            Gmm_DelPsLocInfoUpdateUsim();                                           /* 调用函数删除PS LOC INFO                  */
            break;                                                                  /* 跳出                                     */

        case GMM_NULL:
        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* 更新状态更新为GU3 ROAMING NOT ALLOWED    */
            Gmm_DelPsLocInfoUpdateUsim();                                           /* 调用函数删除PS LOC INFO                  */

        default:                                                                    /* 其他情况                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcAuthenticationFailureInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;                                                                  /* 跳出                                     */
    }
}


VOS_VOID NAS_GMM_RcvMmCsConnectInd(
    VOS_VOID                           *pstRcvMsg                               /* 接收消息使用的头地址定义                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstMmCmServiceInd;                      /* 定义原语类型指针                         */

    pstMmCmServiceInd = (MMGMM_CS_CONNECT_IND_STRU *)pstRcvMsg;                   /* 强制类型转换                             */

    if (MMGMM_CS_CONNECT_ESTING == pstMmCmServiceInd->enCsConnectStatus)
    {

    }
    else if (MMGMM_CS_CONNECT_EXIST == pstMmCmServiceInd->enCsConnectStatus)
    {
        NAS_GMM_FreeGsmSysInfo();
    }
    else
    {
        NAS_GMM_ProcSavedGsmSysInfo();

        NAS_GMM_ProcSavedMmT3211ExpiredNotify();

        NAS_GMM_FreeWasSysInfo();
    }

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I     != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* 不是用户模式A且网络模式I                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcCmServiceInd:NORMAL: It is not A+I(Gmm_RcvMmcCmServiceInd)");
        return;
    }

    if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
    {                                                                           /* 标记CS不在通信中                         */
        /* g_GmmRauCtrl.ucCsSpringRauFlg标识是否为CS触发的RAU。
           只有在CM SERVICE REJECT原因值为4时，
           g_GmmRauCtrl.ucCsSpringRauFlg置为TRUE。
        */
        /*CSFB过程中RAU被#10拒，发Attach，状态为GMM_ATTACH_NORMAL*/
        if( ( GMM_TRUE == g_GmmRauCtrl.ucCsSpringRauFlg )
            || ((VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
             || (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans))))
        {                                                                       /* CS触发RAU                                */
             switch (g_GmmGlobalCtrl.ucState)
             {                                                                  /* 根据状态分发                             */
             case GMM_REGISTERED_INITIATED:
             case GMM_ROUTING_AREA_UPDATING_INITIATED:
             case GMM_SERVICE_REQUEST_INITIATED:
                 NAS_GMM_RcvMmCsConnectInd_InProc(pstRcvMsg);                   /* 调用RAU/SR过程中的处理                   */
                 break;
             case GMM_REGISTERED_NORMAL_SERVICE:
             case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
             case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
                 NAS_GMM_RcvMmCsConnectInd_RegNmlServ();                        /* 调用该状态下的处理                       */
                 break;
             default:
                 PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcCmServiceInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
                 break;
             }
             g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;               /* 清除当前进行的specific 流程标志          */
        }

        /*CSFB过程中RAU被#10拒，发Attach，状态为GMM_ATTACH_NORMAL*/
        if (((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
          || (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans))
         && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;           /* 清除当前进行的specific 流程标志          */
        }
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_Compare_Plmnid
  Function : 比较两个PLMN ID 是否相同
  Input    : GMM_PLMN_ID_STRU *pPlmnId1
             GMM_PLMN_ID_STRU *pPlmnId2
  Output   : 无
  NOTE     : 无
  Return   : GMM_TRUE   相同
             GMM_FALSE  不同
  History  :
    1. 欧阳飞  2009.02.12  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Plmnid(GMM_PLMN_ID_STRU *pPlmnId1,
                             GMM_PLMN_ID_STRU *pPlmnId2 )
{
    VOS_UINT8           i;                                                      /* 定义临时变量                             */

    for (i=0; i<3; i++)
    {                                                                           /* 在MCC个数内判断                          */
        if (pPlmnId1->aucMccDigit[i] != pPlmnId2->aucMccDigit[i])
        {                                                                       /* MCC不相同                                */
            return GMM_FALSE;                                                   /* 返回GMM_FALSE                            */
        }
    }

    if (pPlmnId1->ucMncCnt != pPlmnId2->ucMncCnt)
    {                                                                           /* MNC个数不相同                            */
        return GMM_FALSE;                                                       /* 返回GMM_FALSE                            */
    }

    for (i=0; i<pPlmnId1->ucMncCnt; i++)
    {                                                                           /* 在MNC个数内判断                          */
        if (pPlmnId1->aucMncDigit[i] != pPlmnId2->aucMncDigit[i])
        {                                                                       /* MNC不相同                                */
            return GMM_FALSE;                                                   /* 返回GMM_FALSE                            */
        }
    }

    return GMM_TRUE;                                                            /* 返回GMM_TRUE                             */
}

/*******************************************************************************
  Module   : Gmm_Compare_Lai
  Function : LAI的比较
  Input    : GMM_LAI_STRU   *pLAI1
             GMM_LAI_STRU   *pLAI2
  Output   : 无
  NOTE     : 无
  Return   : GMM_TRUE    相同
             GMM_FALSE   不同
  History  :
    1. 欧阳飞  2009.02.12  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Lai(GMM_LAI_STRU *pLAI1,
                          GMM_LAI_STRU *pLAI2)
{
    VOS_UINT8 ucRet;                                                            /* 定义返回值                               */

    ucRet = GMM_FALSE;                                                          /* 初始化                                   */

    if (GMM_TRUE == Gmm_Compare_Plmnid(&pLAI1->PlmnId, &pLAI2->PlmnId))
    {                                                                           /* PLMN相同                                 */
        if (  (pLAI1->aucLac[0] == pLAI2->aucLac[0])
            &&(pLAI1->aucLac[1] == pLAI2->aucLac[1]))
        {                                                                       /* LAC相同                                  */
            ucRet = GMM_TRUE;                                                   /* 赋返回值                                 */
        }
    }

    return ucRet;
}

/*******************************************************************************
  Module   : Gmm_Com_CmpRai
  Function : RAI的比较
  Input    : GMM_RAI_STRU   *pRAI1
             GMM_RAI_STRU   *pRAI2
  Output   : 无
  NOTE     : 无
  Return   : GMM_TRUE    相同
             GMM_FALSE   不同
  History  :
    1. 欧阳飞  2009.02.12  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Rai(GMM_RAI_STRU  *pRAI1,
                          GMM_RAI_STRU  *pRAI2)
{
    VOS_UINT8 ucRet = GMM_FALSE;                                                /* 定义返回值                               */

    if (GMM_TRUE == Gmm_Compare_Lai(&pRAI1->Lai, &pRAI2->Lai))
    {                                                                           /* LAI一致                                  */
        if (pRAI1->ucRac == pRAI2->ucRac)
        {                                                                       /* RAC一致                                  */
            ucRet = GMM_TRUE;                                                   /* 赋返回值                                 */
        }
    }

    return ucRet;
}


 VOS_VOID Gmm_Get_Location_Change_info(
    GMM_RAI_STRU                       *pRai1,
    GMM_RAI_STRU                       *pRai2,
    VOS_UINT8                          *pucLaiChgFlg,
    VOS_UINT8                          *pucRaiChgFlg,
    VOS_UINT8                           ucNetMod
)
{
    VOS_UINT32                          ulT3302Status;

    ulT3302Status                = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

    if (GMM_FALSE == Gmm_Compare_Rai(pRai1, pRai2))
    {                                                                           /* 设置RAI是否变化标志                      */
        *pucRaiChgFlg = GMM_TRUE;
    }
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_Get_Location_Change_info, Gmm_Compare_Rai:rai not change");
        *pucRaiChgFlg = GMM_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
    {
        /* 3GPP 23401 4.3.5.6   Idle mode signalling reduction function:
           The Idle mode Signalling Reduction (ISR) function provides a
           mechanism to limit signalling during inter-RAT cell-reselection
           in idle mode (ECM-IDLE, PMM-IDLE, GPRS STANDBY states).
        */
        /* AT&T LTE-BTR-1-1824、LTE-BTR-1-1826和LTE-BTR-1-1828用例要求
           GMM在GU下attach无响应或被拒达最大次数启动T3302定时器，后续异系统
           或搜网到L下后无需停止，L下注册失败满足disable lte条件到GU下搜网
           回原失败小区时，等T3302超时后再做ps attach */
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI != NAS_MML_GetTinType())
         && (VOS_FALSE == ulT3302Status))

        {
            *pucRaiChgFlg = GMM_TRUE;
        }

        /* 如果网络模式I,从L异系统到GU,需要判断CS 的LAI是否改变，如果改变需要发起联合rau */
        if (GMM_TRUE == NAS_GMM_IsCsLaiChangeNeedRegister(ucNetMod))
        {
            *pucRaiChgFlg = GMM_TRUE;
        }
    }

#endif

    if (GMM_FALSE == Gmm_Compare_Lai(&(pRai1->Lai), &(pRai2->Lai)))
    {                                                                           /* 设置LAI是否变化标志                      */
        *pucLaiChgFlg = GMM_TRUE;
    }
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_Get_Location_Change_info: LAI not Change");
        *pucLaiChgFlg = GMM_FALSE;
    }

    return;
}


VOS_UINT8 Gmm_RcvMmcSysInfoInd_PS_BAR(
    VOS_UINT8                           ucLaiChgFlg
)
{
    VOS_UINT8                    ucRst = GMM_TRUE;

    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        if  ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
          && (GMM_FALSE == ucLaiChgFlg))
        {
            if ( ( GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState )
              || ( GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState )
              || ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState ))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }

        }

        if (GMM_DEREGISTERED_NO_IMSI == g_GmmGlobalCtrl.ucState)
        {

            g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            return ucRst;
        }
        else if(GMM_NULL == g_GmmGlobalCtrl.ucState)
        {
            ucRst = GMM_FALSE;
        }
        else if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            || (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0)))
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            ucRst = GMM_FALSE;
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
            ucRst = GMM_FALSE;
        }

        /* 如果当前业务受限，则清除缓存 */
        if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
        {
            Gmm_ComCnfHandle();
            GMM_BufferMsgDump();
        }
        else
        {
            GMM_BufferMsgResume();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    }

    return ucRst;
}


VOS_UINT8 Gmm_RcvMmcSysInfoIndRelEstingLink(VOS_VOID)
{
    VOS_UINT8                    ucRst = GMM_TRUE;
    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    if (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
    {
        /* T3340正在运行中，等链路释放后再处理系统消息 */
        g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
        ucRst = GMM_FALSE;
    }

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                       /* 无信令且正在建立信令连接                 */
        if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {                                                                   /* GMM_REGISTERED_INITIATED状态             */
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask  &= ~GMM_RRC_RRMM_EST_CNF_FLG;         /* 清除等待CNF标志                          */
            g_GmmGlobalCtrl.ucSpecProc =  GMM_NULL_PROCEDURE;               /* 清除当前进行的specific过程               */
            ucRst = GMM_FALSE;
        }
        else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            /*Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);*/

            /* GMM的更新状态在U1时,GMM为正常服务;否则GMM迁移到ATT-TO-UPDATE，启动3311进行尝试 */
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
            {
                g_GmmGlobalCtrl.SysInfo.Rai = stGmmRai;
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            }
            else
            {
                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
                Gmm_TimerStart(GMM_TIMER_T3311);
            }
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask  &= ~GMM_RRC_RRMM_EST_CNF_FLG;         /* 清除等待CNF标志                          */
            g_GmmGlobalCtrl.ucSpecProc =  GMM_NULL_PROCEDURE;               /* 清除当前进行的specific过程               */
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;          /* 清除等待CNF标志                          */

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;            /* 清除当前进行的specific过程               */
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else
        {
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp
 *  FUNCTION : Gmm_RcvMmcSysInfoInd函数降复杂度: pRaiTemp的赋值
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(GMM_RAI_STRU         *pRaiTemp,
                                            VOS_VOID             *pRcvMsg
                                            )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* 定义MMCGMM_SYS_INFO_IND_STRU类型指针     */

    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                          /* 得到原语指针                             */

    if (0 != pSysInfoInd->ulCnCommonSize)
    {                                                                           /* CnCommonInfo不为空                       */
        pRaiTemp->Lai.aucLac[0] = pSysInfoInd->aucCnCommonInfo[0];
        pRaiTemp->Lai.aucLac[1] = pSysInfoInd->aucCnCommonInfo[1];              /* LAC                                      */
    }

    if (MMC_GMM_SYS_MSK_PLMN == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PLMN))
    {
        pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMcc & 0x0F);                          /* MCC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 8) & 0x0F);                   /* MCC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 16) & 0x0F);                  /* MCC Digit 3                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMnc & 0x0F);                          /* MNC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 8) & 0x0F);                   /* MNC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 16) & 0x0F);                  /* MNC Digit 3                              */
        pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                      /* MNC Degit count                          */
        if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
        {
            pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                  /* MNC Degit count                          */
        }
    }
    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
          if (0 != pSysInfoInd->ulPsInfoSize)
          {
              pRaiTemp->ucRac = (VOS_UINT8)pSysInfoInd->aulPsInfo[0];               /* RAC                                      */
          }
    }

    return;
}


VOS_UINT8 Gmm_RcvMmcSysInfoInd_PreProcess_Handling(VOS_UINT8                    ucNetMod,
                                                   VOS_UINT8                    ucRaiChgFlg,
                                                   MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd,
                                                   VOS_UINT8                   *pucDrxLengthChgFlg
                                                )
{
    VOS_UINT8                           ucRst = GMM_TRUE;
    VOS_UINT8                           ucCsChanged2UnBarFlg;
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucPsAttachAllow;

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllow = NAS_MML_GetPsAttachAllowFlg();

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    if (g_GmmGlobalCtrl.ucNetMod != ucNetMod)
    {
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    }

    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN是否禁止                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */
    if (GMM_TRUE == *pucDrxLengthChgFlg)
    {                                                                           /* 系统信息中带有DRX length信息             */
        NAS_MML_SetWSysInfoDrxLen((VOS_UINT8)pSysInfoInd->ulPsDrxLength);       /* 存储DRX LENGTH                           */

        *pucDrxLengthChgFlg = GMM_FALSE;
    }

    ucCsChanged2UnBarFlg            =   pSysInfoInd->ucCsChanged2UnBarFlg;
    ucCsRestrictionFlg              =   NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg              =   NAS_MML_GetPsRestrictRegisterFlg();
    gstGmmCasGlobalCtrl.ucSysRauFlg = ucRaiChgFlg;
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        gstGmmCasGlobalCtrl.ucSysRauFlg = GMM_FALSE;
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
    }
    else
    {
        /* PS已注册，CS域从bar到不bar, 且Gs关联未建立,此时GMM需要发起联合RAU重建Gs关联。 */
        if (   (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
            && (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
            && (VOS_TRUE == ucCsAttachAllow)
            && (VOS_TRUE == ucPsAttachAllow)
            && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            if ( (VOS_FALSE == ucPsRestrictionFlg)
              && (VOS_FALSE == ucCsRestrictionFlg)
              && (VOS_TRUE == ucCsChanged2UnBarFlg)
              && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
              && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                ucRst = GMM_FALSE;
            }
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_CSPS_INFO
 *  FUNCTION : Gmm_RcvMmcSysInfoInd函数降复杂度: CSPS_INFO的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_CSPS_INFO(MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd,
                                        VOS_UINT8                   *pucNetMod
                                            )
{
    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
        if (0 != pSysInfoInd->ulPsInfoSize)
        {
            if (0 == (VOS_UINT8)(pSysInfoInd->aulPsInfo[0] >> 8))
            {
                *pucNetMod = GMM_NET_MODE_I;
            }
            else
            {
                *pucNetMod = GMM_NET_MODE_II;
            }
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_SUPPORT_GPRS;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is supported");
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;  /* 设置当前小区不支持GPRS标志                */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is not supported");
        }
    }
    else
    {
        g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;  /* 设置当前小区不支持GPRS标志                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is not supported");
    }

    return;
}


VOS_UINT8 Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling
(
    VOS_UINT8                           ucNetMod,
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfoInd,
    VOS_UINT8                          *pucLaiChgFlg,
    VOS_UINT8                          *pucRaiChgFlg
)
{
    VOS_UINT8                    ucRst = GMM_TRUE;

    if ((g_GmmGlobalCtrl.SysInfo.ucNetMod != ucNetMod)
        && (0 != g_GmmGlobalCtrl.SysInfo.ucNetMod))
    {                                                                           /* 网络模式变更                             */
        if ((GMM_TRUE == *pucLaiChgFlg)
         || (GMM_TRUE == *pucRaiChgFlg))
        {
            g_GmmRauCtrl.ucT3330outCnt = 0;

            if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
                && (0x10 != g_GmmGlobalCtrl.ucState))
            {                                                                       /* 用户模式为A,并且已经注册                 */
                if (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState)
                {/* 非异系统挂起过程等待小区系统消息状态 */
                    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
                     && (GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
                    {
                        (VOS_VOID)Gmm_RcvMmcSysInfoIndRelEstingLink();
                        ucRst = GMM_FALSE;
                        return ucRst;
                    }
                    else
                    {
                        /* 非异系统挂起过程等待小区系统消息状态 */
                        /* 同系统的小区系统消息处理 */
                        Gmm_ComNetModeChange(pSysInfoInd);                              /* 调用网络模式变换的公共处理               */
                        ucRst = GMM_FALSE;
                        return ucRst;
                    }
                }
            }
        }
        gstGmmSuspendCtrl.ucNetModeChange = GMM_CasGetNetChgType(ucNetMod);
    }
    else
    {
        gstGmmSuspendCtrl.ucNetModeChange = GMM_NETMODE_CHG_NULL;
    }

    return ucRst;
}


VOS_VOID Gmm_RcvMmcSysInfoInd_State_Distribute(
                                  VOS_VOID    *pRcvMsg,                                 /* 消息指针                                 */
                                  VOS_UINT8    ucRaiChgFlg,                          /* RAI变化标志                              */
                                  VOS_UINT8    ucDrxLengthChgFlg,                    /* DRX length变化标志                       */
                                  VOS_UINT8    ucLaiChgFlg                           /* LAI变化标志                              */
                                  )
{
    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
     && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {
        if(GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        }
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
    }

    gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = ucRaiChgFlg;
    gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg = ucDrxLengthChgFlg;

    /* 将原语MMCGMM_SYS_INFO_IND按照状态分发 */
    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvMmcSysInfoInd_RegInit(pRcvMsg,
                                     ucRaiChgFlg,
                                     ucDrxLengthChgFlg,
                                     ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvMmcSysInfoInd_DeregInit(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvMmcSysInfoInd_RauInit(pRcvMsg,
                                     ucRaiChgFlg,
                                     ucDrxLengthChgFlg,
                                     ucLaiChgFlg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvMmcSysInfoInd_ServReqInit(pRcvMsg,
                                         ucRaiChgFlg,
                                         ucDrxLengthChgFlg,
                                         ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_RcvMmcSysInfoInd_DeregNmlServ(pRcvMsg, ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch(pRcvMsg,
                                             ucRaiChgFlg,
                                             ucDrxLengthChgFlg,
                                             ucLaiChgFlg);
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:

        Gmm_RcvMmcSysInfoInd_RegNmlServ(pRcvMsg,
                                        ucRaiChgFlg,
                                        ucDrxLengthChgFlg,
                                        ucLaiChgFlg);
        break;

    case GMM_REGISTERED_PLMN_SEARCH:

        NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch(pRcvMsg,
                                        ucRaiChgFlg,
                                        ucDrxLengthChgFlg,
                                        ucLaiChgFlg);
        break;
    case GMM_REGISTERED_UPDATE_NEEDED:
        Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_REGISTERED_LIMITED_SERVICE:
        Gmm_RcvMmcSysInfoInd_RegUpdtNeed(pRcvMsg, ucLaiChgFlg);
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt(pRcvMsg,
                                           ucRaiChgFlg,
                                           ucDrxLengthChgFlg,
                                           ucLaiChgFlg);
        break;
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvMmcSysInfoInd_SuspWaitSys(pRcvMsg,ucRaiChgFlg,ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_NO_IMSI:
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd:WARNING:g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}


VOS_VOID Gmm_RcvMmcSysInfoInd(
                          VOS_VOID *pRcvMsg                                     /* 接收消息使用的头地址定义                 */
                          )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* 定义MMCGMM_SYS_INFO_IND_STRU类型指针     */
    VOS_UINT8                    ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucLaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucDrxLengthChgFlg = GMM_FALSE;
    GMM_RAI_STRU                *pRaiTemp = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod = g_GmmGlobalCtrl.ucNetMod;
    VOS_UINT32                   ulNewCellId;
    VOS_UINT8                    ucRst = GMM_TRUE;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    GMM_RAI_STRU                 stAttempUpdateRaiInfo;
    GMM_RAI_STRU                 stOldRai;
    NAS_MML_RAI_STRU            *pstAttemptUpdateRaiInfo = VOS_NULL_PTR;

    VOS_UINT8                           ucSimPsRegStatus;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    VOS_UINT32                          ulIsNeedDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;

    pstRplmnCfgInfo           = NAS_MML_GetRplmnCfg();
    enCurrNetType             = NAS_MML_GetCurrNetRatType();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    enCurRat = NAS_MML_GetCurrNetRatType();
    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                          /* 得到原语指针                             */

    NAS_GMM_LogGmmCtxInfo();

    Gmm_SndSmSysInfoInd(MMCGMM_SGSN_RELEASE99_ONWARDS);

    /* 收到W模系统消息, 指示RABM当前系统模式, 并恢复RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_FALSE,
                                VOS_TRUE);

    /* 停HO等待系统消息定时器 */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_FALSE;

    NAS_GMM_SuspendLlcForInterSys();

    g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_FALSE;

    Gmm_RcvMmcSysInfoInd_CSPS_INFO(pSysInfoInd, &ucNetMod);

    /* 在迁到W模式下是，需要清除加密指配标志，因为在指配加密时需要使用此标志 */
    if(NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
    {
        gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_FALSE;
        gstGmmCasGlobalCtrl.ucGprsCipher = VOS_FALSE;

        NAS_GMM_SndMmcCipherInfoInd();
    }
    /* 之前有异常释放,收到系统消息后清除这个标志 */
    if (RR_REL_CAUSE_ABORT_RR_NORMAL == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_RcvMmcSysInfoInd:ERROR: Alloc mem fail.");
        return;
    }

    Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(pRaiTemp, pRcvMsg);

    /*对于收到系统消息从G重选到W的情况，需要清除掉原来链接存在标记
 */
    /*此处处理需要在小区被BAR的处理之前，因为小区被BAR会返回
 */
    if((NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
       &&((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
          ||(GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)))
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);
        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);
#if (FEATURE_ON == FEATURE_LTE)
        /* L下丢网，搜网到GU后，需要判断如果有ISR激活后激活的pdp上下文，需要去激活ISR*/
        ulIsNeedDeactiveIsrFlg = NAS_GMM_IsNeedDeactiveIsr_InterSys(gstGmmSuspendCtrl.ucPreRat, enCurrNetType, MMC_SUSPEND_CAUSE_BUTT);

        if (VOS_TRUE == ulIsNeedDeactiveIsrFlg)
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);

            /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
#endif
    }

    /* 重选到PS被BARRED的小区,在网络模式I,并且T3312超时 */
    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        /*  suspend过程中收到T3312超时，若PS barred,不会再进入suspend的处理，转换为expiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
          && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ( (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
               && (GMM_NET_MODE_I == ucNetMod))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3412OrT3423_EXPIRED);
        }
        else
        {
        }
#endif
    }

    PS_MEM_SET(&stAttempUpdateRaiInfo, 0, sizeof(stAttempUpdateRaiInfo));
    pstAttemptUpdateRaiInfo = NAS_GMM_GetAttemptUpdateRaiInfo();

    NAS_GMM_ConvertPlmnIdToGmmFormat(&pstAttemptUpdateRaiInfo->stLai.stPlmnId, &stAttempUpdateRaiInfo.Lai.PlmnId);
    stAttempUpdateRaiInfo.Lai.aucLac[0] = pstAttemptUpdateRaiInfo->stLai.aucLac[0];
    stAttempUpdateRaiInfo.Lai.aucLac[1] = pstAttemptUpdateRaiInfo->stLai.aucLac[1];
    stAttempUpdateRaiInfo.ucRac         = pstAttemptUpdateRaiInfo->ucRac;

    stOldRai = g_GmmGlobalCtrl.SysInfo.Rai;

    if (VOS_TRUE == NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(pRaiTemp, &stAttempUpdateRaiInfo))
    {
        stOldRai = stAttempUpdateRaiInfo;
    }

    Gmm_Get_Location_Change_info(pRaiTemp, &stOldRai, &ucLaiChgFlg, &ucRaiChgFlg, ucNetMod);

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if ( (VOS_TRUE == ucSimPsRegStatus)
      && (MMC_GMM_NO_FORBIDDEN == pSysInfoInd->ulForbiddenMask) )
    {
        ucRst = Gmm_RcvMmcSysInfoInd_PS_BAR(ucLaiChgFlg);
        if(GMM_FALSE == ucRst)
        {
            g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN是否禁止                             */
            g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */

            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

            Gmm_MemFree(pRaiTemp);
            return;
        }
    }


    ulNewCellId = pSysInfoInd->ulCellId;

    g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;

    if (ulNewCellId != g_GmmGlobalCtrl.SysInfo.ulCellId)
    {
        g_GmmGlobalCtrl.SysInfo.ulCellId = ulNewCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_TRUE;
    }




    if (MMC_GMM_SYS_MSK_PS_DRX ==(pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PS_DRX))
    {
        /* 系统信息中带有DRX length信息             */
        if (NAS_MML_GetWSysInfoDrxLen() != (VOS_UINT8)pSysInfoInd->ulPsDrxLength)
        {                                                                       /* DRX LENGTH改变                           */
            ucDrxLengthChgFlg = GMM_TRUE;                                       /* 设置DRX length变化标志                   */
        }
    }

    if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变或者DRX改变                        */
        ucRst = Gmm_RcvMmcSysInfoIndRelEstingLink();
        if(GMM_FALSE == ucRst)
        {
            NAS_GMM_SaveWasSysInfo(pSysInfoInd);
            Gmm_MemFree(pRaiTemp);
            return;
        }
    }

    ucRst = Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling(ucNetMod, pSysInfoInd, &ucLaiChgFlg, &ucRaiChgFlg);
    if(GMM_FALSE == ucRst)
    {
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* 存储系统信息中的RAI                      */
    }
    else
    {
        /*  suspend过程中收到T3312超时，若GPRS NOT SUPPORT,不会再进入suspend的处理，转换为expiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }

    ucRst = Gmm_RcvMmcSysInfoInd_PreProcess_Handling(ucNetMod, ucRaiChgFlg, pSysInfoInd, &ucDrxLengthChgFlg);
    if(GMM_FALSE == ucRst)
    {
        Gmm_MemFree(pRaiTemp);
        return;
    }

    Gmm_RcvMmcSysInfoInd_State_Distribute(pRcvMsg,
                                          ucRaiChgFlg,
                                          ucDrxLengthChgFlg,
                                          ucLaiChgFlg);

    Gmm_MemFree(pRaiTemp);

    /* 链路释放控制: 收到系统消息，在处理完毕后，清除各流程的Retry标志 */
    g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg = VOS_FALSE;
    g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_FALSE;
    g_GmmRauCtrl.ucRetryRauForRelCtrlFlg = VOS_FALSE;
    g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_FALSE;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_GMM_RcvMmcLteSysInfoInd(
    MMC_GMM_LTE_SYS_INFO_IND_STRU      *pstLteSysInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    /* 在迁到L模式下，需要清除加密指配标志，因为在指配加密时需要使用此标志 */
    gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_FALSE;
    gstGmmCasGlobalCtrl.ucGprsCipher       = VOS_FALSE;

    gstGmmSuspendCtrl.ucGetLteSecContext   = VOS_FALSE;

    enCurRat = NAS_MML_GetCurrNetRatType();
    /* 收到L模系统消息, 指示RABM当前系统模式, 并挂起RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    /* 清除释放原因值 */
    g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;  

}



VOS_VOID NAS_GMM_RcvMmcLmmStatusInd(
    MMCGMM_LMM_STATUS_IND_STRU      *pstLmmStatusInd
)
{
    switch (pstLmmStatusInd->ulConnState)
    {
    case MMC_LMM_CONN_ESTING:
    case MMC_LMM_CONNECTED_SIG:
    case MMC_LMM_CONNECTED_DATA:

        gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_LTE;

        break;

    default:
        NAS_INFO_LOG1(WUEPS_PID_GMM, "pstLmmStatusInd->ulConnState =",pstLmmStatusInd->ulConnState);
        break;

    }

}


VOS_UINT32 NAS_GMM_IsCsLaiChangeNeedRegister(
    VOS_UINT8                           ucNetMod
)
{
    NAS_MML_MS_MODE_ENUM_UINT8          ucMsMode;
    VOS_UINT8                           ucCsSimRegStatus;
    VOS_UINT8                           ucCsRestrictRegFlg;
    VOS_UINT8                           ucCsAttachAllowFlg;

    ucMsMode           = NAS_MML_GetMsMode();
    ucCsSimRegStatus   = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictRegFlg = NAS_MML_GetCsRestrictRegisterFlg();
    ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();

    if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
     && (GMM_NET_MODE_I == ucNetMod)
     && (NAS_MML_MS_MODE_PS_CS == ucMsMode)
     && (VOS_TRUE == ucCsSimRegStatus)
     && (VOS_FALSE == ucCsRestrictRegFlg)
     && (VOS_TRUE == ucCsAttachAllowFlg))
    {
        return GMM_TRUE;
    }

    return GMM_FALSE;
}

#endif



VOS_VOID NAS_GMM_StopReadyTimer_DeregStat(VOS_VOID)
{

    if ((GMM_TRUE == GMM_IsCasGsmMode())
     && (g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
    }

}


VOS_VOID NAS_GMM_SetIdleSrvState_DeregStat(VOS_VOID)
{

    if ((GMM_TRUE == GMM_IsCasGsmMode())
     && (g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        if (GMM_AGB_GPRS_IDLE != gstGmmCasGlobalCtrl.GmmSrvState)
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
             NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }
    }

}


VOS_VOID Gmm_ComStaChg(VOS_UINT8 ucState)
{

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_GMM_NotifyRrmmChgNonDrxMode(g_GmmGlobalCtrl.ucState, ucState);
    }

#if(FEATURE_ON == FEATURE_DSDS)
    NAS_GMM_NotifySessionAccordingStateChg(g_GmmGlobalCtrl.ucState, ucState);
#endif

    g_GmmGlobalCtrl.ucState = ucState;                                          /* 保存要迁入的状态                         */

    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    GMM_PrintState();

    Gmm_SndSmStatusInd();

    Gmm_SndSmsServiceStatusInd();

    if(VOS_TRUE == g_GmmGlobalCtrl.ucNeedChgServiceStatus)
    {
        Gmm_Com_ServiceStatus_Handle();                                         /* 通知MMC服务状态                          */
    }
    /* 3GPP 24.008 4.7.2.2章节描述：
      If the periodic routeing area update timer expires and the MS is in state
      GMM-REGISTERED.NO-CELL-AVAILABLE, the MS shall start the GERAN/UTRAN Deactivate
      ISR timer T3323. The MS shall initiate the routeing area updating procedure
      and stop the timer T3323 when the MS enters the state GMM-REGISTERED.NORMAL-SERVICE
      before timer T3323 expires. */

    if (GMM_REGISTERED_NORMAL_SERVICE == ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }


    if (GMM_DEREGISTERED_NO_IMSI == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 状态迁入GMM_DEREGISTERED_NO_IMSI         */
        if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
        {                                                                       /* sim卡有效                                */
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;
        }
    }

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        Gmm_TimerStop(GMM_TIMER_T3319);                                         /* 停止3319                                 */
    }


    NAS_GMM_StopReadyTimer_DeregStat();

    NAS_GMM_SetIdleSrvState_DeregStat();


}

/*******************************************************************************
  Module   : Gmm_RcvMmRegisterInitiation
  Function : 原语MMGMM_REGISTER_INITIATION的接收处理
  Input    : VOS_VOID *pMsg  消息指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.02.03  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvMmRegisterInitiation(
    VOS_VOID                           *pMsg                                    /* 指向消息的指针                           */
)
{
    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
    {                                                                           /* A+I                                      */
        switch (g_GmmGlobalCtrl.ucState)
        {                                                                       /* 调用不同状态下的处理                     */
        case GMM_SERVICE_REQUEST_INITIATED:
            Gmm_RcvMmcRegisterInitiation_ServReqInit(pMsg);
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch();
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt();
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcRegisterInitiation:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;
        }
    }
    else
    {
    }
    return;
}


VOS_VOID Gmm_RcvMmcRegisterInitiation_ServReqInit(
                                              VOS_VOID *pMsg                        /* 指向消息的指针                           */
                                              )
{
    MMCGMM_REGISTER_INITIATION_STRU   *ptr;

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* 无信令且正在建立信令连接                 */
        ptr = (MMCGMM_REGISTER_INITIATION_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_REGISTER_INITIATION_STRU));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcRegisterInitiation_ServReqInit:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_REGISTER_INITIATION_STRU));

        if (GMM_MSG_HOLD_FOR_RAU ==
            (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
        {
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau);
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;              /* 存储消息首地址到 ulMsgAddrForRau         */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* 置消息保留标志                           */

        return;
    }
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask
            &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                          /* 清除原语等待标志                         */
    }
    g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;                /* 保留被中断的SR流程                       */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                                   /* 设置follow on标志                        */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);                   /* 进行RAU                                  */
    return;
}


VOS_VOID Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */
    /*
    3gpp 24.008 4.7.3 : The GPRS attach attempt counter shall be reset when the
    MS is in substate ATTEMPTING-TO-ATTACH and
        - expiry of timer T3302;
        - a new routing area is entered; or
        - an attach is triggered by CM sublayer requests.
    */
    if ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState )
    {
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
    }
    Gmm_AttachInitiate(GMM_ATTACH_COMBINED);                                                       /* 触发attach                               */
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt
  Function : 在GMM_REGISTERED_NORMAL_SERVICE/ATTEMPTING_TO_UPDATE_MM/
             ATTEMPTING_TO_UPDATE状态下收到原语MMCGMM_REGISTER_INITIATION的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.02.03  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */
    if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState)
    {
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter 清0                  */
    }

    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);

    return;
}

/*******************************************************************************
  Module   : Gmm_ComUnrealProc
  Function : 假流程的类型判断处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT8   ucGmmAction   假流程类型
  History  :
    1. 张志勇  2004.03.16  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_ComUnrealProc(VOS_VOID)
{
    VOS_UINT8       ucGmmAction = 0;                                                /* 定义局部变量                             */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_INITIATED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        ucGmmAction = GMM_ATTACH_NORMAL;
        break;
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_PLMN_SEARCH:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        ucGmmAction = GMM_RAU_NORMAL;
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
        {
            ucGmmAction = GMM_ATTACH_NORMAL;
        }
        else
        {
            ucGmmAction = GMM_RAU_NORMAL;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComUnrealProc:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return ucGmmAction;
}

VOS_UINT8 Gmm_ComGetFollowOnFlg(VOS_VOID)
{
    return  g_GmmGlobalCtrl.ucFollowOnFlg;
}


VOS_BOOL NAS_GMM_IsExistBufferService(VOS_VOID)
{
    if ((GMM_MSG_HOLD_FOR_SM == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
     || (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg))
    {
        return  VOS_TRUE;
    }

    if (GMM_MSG_HOLD_FOR_PAGING == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {
        return  VOS_TRUE;
    }

    if (GMM_MSG_HOLD_FOR_SERVICE == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {
        return  VOS_TRUE;
    }

    if ( VOS_TRUE == NAS_GMM_IsFollowOnPend() )
    {
        return  VOS_TRUE;
    }

    /* 还需判断是否有数据 */

    return  VOS_FALSE;

}

VOS_VOID Gmm_ComForbiddenList(
                          VOS_UINT32   ulForbiddenMask                               /* 所在forbidden列表的类型                  */
                          )
{
    if (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* 等待信令建立                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* 清除原语等待标志                         */
    }

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* 调用状态的公共处理                       */
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                      /* 调用状态的公共处理                       */
    }

    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;                          /* 设置真流程标志                           */
    g_GmmGlobalCtrl.ucSpecProc   = GMM_NULL_PROCEDURE;
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ComForbiddenList:INFO: specific procedure ended");
    return;
}


VOS_VOID Gmm_ComNetModeChange_NotSupportGprs_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucLaiChgFlg)
{
    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停T3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* 停T3330                                  */
    Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* 停保护Timer                              */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    g_GmmReqCnfMng.ucCnfMask = 0;

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* 网络模式                                 */
    Gmm_ComCnfHandle();
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清当前流程                               */

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_NotSupportGprs_Handling:WARNING: g_GmmGlobalCtrl.ucState is GMM_NULL");
        return;
    }

    if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
        || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
    }

    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
    }

    if (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
        }
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);                                         /* 停T3312                                  */
    }

    else
    {
        if (GMM_TRUE == ucLaiChgFlg)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* 停T3312                                  */
        }

        else
        {
            if (GMM_DEREGISTERED_NO_CELL_AVAILABLE
                == g_GmmGlobalCtrl.ucState)
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                }
#endif
                Gmm_TimerStop(GMM_TIMER_T3312);                                 /* 停T3312                                  */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }

            else
            {
                if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                {
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }
#endif
                    Gmm_TimerStart(GMM_TIMER_T3312);                                /* 起T3312                                  */
                }
            }
        }
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Netmode_I2II_Handling
  Function : Gmm_ComNetModeChange 降复杂度: 网络模式 I => II 的处理
  Input    : VOS_UINT8  ucNetMod,
             VOS_UINT8  ucRaiChgFlg
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞 2009.06.11  新规作成
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Netmode_I2II_Handling(
                                                  VOS_UINT8 ucNetMod,
                                                  VOS_UINT8 ucRaiChgFlg)
{

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* 网络模式                                 */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        /*
        Imsi Detach过程中从网络模式I变到网络模式II，终止该Detach，认为
        此次Detach失败。因为变化到网络模式II后，PS域不可能发起Imsi Detach
        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        /*
        Combined GPRS/IMSI Detach过程中网络模式由I变化到II，
        记录被中断的流程为Ps Detach，因为网络模式II下不能发起
        Combined GPRS/IMSI Detach.
        */
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_DETACH_NORMAL;                     /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前进行的specific过程               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前进行的specific过程               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* 停T3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* 停止T3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* 停止T3320                                */

            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    case GMM_REGISTERED_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3310);                                     /* 停T3310                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* 停止T3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* 停止T3320                                */

            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_Netmode_I2II_Handling:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}


VOS_VOID Gmm_ComNetModeChange_Netmode_II2I_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucRaiChgFlg)
{

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* 网络模式                                 */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */



        /* 增加CS禁止注册时候，不发联合ATTACH */
        if ( VOS_FALSE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm() )

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(
                                        GMM_COMBINED_RALAU_WITH_IMSI_ATTACH
                                          );
        }
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前进行的specific过程               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前进行的specific过程               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* 停T3330                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    case GMM_REGISTERED_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3310);                                     /* 停T3310                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_Netmode_II2I_Handling:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Fill_Rai
  Function : Gmm_ComNetModeChange 降复杂度: 给指针pRaiTemp赋值
  Input    : GMM_RAI_STRU                *pRaiTemp,
             MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞 2009.06.11  新规作成
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Fill_Rai(
                          GMM_RAI_STRU                *pRaiTemp,
                          MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd
                          )
{
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    if (0 != pSysInfoInd->ulCnCommonSize)
    {                                                                           /* CnCommonInfo不为空                       */
        pRaiTemp->Lai.aucLac[0] = pSysInfoInd->aucCnCommonInfo[0];
        pRaiTemp->Lai.aucLac[1] = pSysInfoInd->aucCnCommonInfo[1];              /* LAC                                      */
    }

    if (MMC_GMM_SYS_MSK_PLMN == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PLMN))
    {
        pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMcc & 0x0F);                      /* MCC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 8) & 0x0F);               /* MCC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 16) & 0x0F);              /* MCC Digit 3                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMnc & 0x0F);                      /* MNC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 8) & 0x0F);               /* MNC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 16) & 0x0F);              /* MNC Digit 3                              */
        pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                      /* MNC Degit count                          */

        if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
        {
            pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                  /* MNC Degit count                          */
        }
    }

    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
          if (0 != pSysInfoInd->ulPsInfoSize)
          {
            pRaiTemp->ucRac = (VOS_UINT8)pSysInfoInd->aulPsInfo[0];             /* RAC                                      */
          }
    }

    return;

}


VOS_VOID Gmm_ComNetModeChange(VOS_VOID  *pMsg)
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* 定义MMCGMM_SYS_INFO_IND_STRU类型指针     */
    VOS_UINT8                    ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucLaiChgFlg = GMM_FALSE;
    GMM_RAI_STRU                *pRaiTemp    = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod;

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));

    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChange:ERROR: alloc rai temp memory fail.");
        return;
    }

    Gmm_ComNetModeChange_Fill_Rai(pRaiTemp, pSysInfoInd);

    if (0 == (VOS_UINT8)(pSysInfoInd->aulPsInfo[0] >> 8))
    {
        ucNetMod = GMM_NET_MODE_I;
    }
    else
    {
        ucNetMod = GMM_NET_MODE_II;
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, ucNetMod))
    {                                                                           /* 设置RAI是否变化标志                      */
        ucRaiChgFlg                 = GMM_TRUE;
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }
    if (GMM_FALSE == Gmm_ComCmpLai(&(pRaiTemp->Lai)))
    {                                                                           /* 设置LAI是否变化标志                      */
        ucLaiChgFlg = GMM_TRUE;
    }

    Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* 存储系统信息中的RAI                      */
    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN是否禁止                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SetWSysInfoDrxLen((VOS_UINT8)pSysInfoInd->ulPsDrxLength);       /* 存储DRX LENGTH                           */
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_ComNetModeChange_NotSupportGprs_Handling(ucNetMod, ucLaiChgFlg);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (0 != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                            /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* 网络模式                                 */
        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmReqCnfMng.ucCnfMask = 0;
        g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                            /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* 网络模式                                 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_II == ucNetMod))
    {                                                                           /* 网络模式变更 I->II                       */
        Gmm_ComNetModeChange_Netmode_I2II_Handling(ucNetMod, ucRaiChgFlg);
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_I == ucNetMod))
    {                                                                           /* 网络模式变更                             */
        Gmm_ComNetModeChange_Netmode_II2I_Handling(ucNetMod, ucRaiChgFlg);
    }

    Gmm_MemFree(pRaiTemp);
}


VOS_VOID Gmm_ComNetModeChangeGsm(VOS_VOID  *pMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfoInd;
    VOS_UINT8                           ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                           ucLaiChgFlg = GMM_FALSE;
    GMM_RAI_STRU                       *pRaiTemp  = VOS_NULL_PTR;
    VOS_UINT8                           ucNetMod;
    MMCGMM_GSM_SYS_INFO_IND_ST         *ptr;

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    pSysInfoInd = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;
    if (((GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState))
        &&(0 != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* 正在建信令                               */
        ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChangeGsm:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;              /* 存储消息首地址到 ulMsgAddrForRau         */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* 置消息保留标志                           */
        return;
    }
    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        &&(0 != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {
        ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChange:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach = (VOS_UINT32)ptr;                /* 存储消息首地址到 ulMsgAddrForAttach      */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_ATTACH;        /* 置消息保留标志                           */
        return;
    }

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChangeGsm:ERROR: Memory is not allocated");
          return;
    }
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    /* 填写RAC */
    pRaiTemp->ucRac = pSysInfoInd->ucRac;
    /* 填写LAC */
    pRaiTemp->Lai.aucLac[1] = (VOS_UINT8)pSysInfoInd->usLac;       /* LAC */
    pRaiTemp->Lai.aucLac[0] = (VOS_UINT8)(pSysInfoInd->usLac >> 8);
    /* 填写PLMN */
    pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pSysInfoInd->stPlmnId.ulMcc & 0x0F);             /* MCC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMcc >> 8) & 0x0F);      /* MCC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMcc >> 16) & 0x0F);     /* MCC Digit 3                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pSysInfoInd->stPlmnId.ulMnc & 0x0F);             /* MNC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMnc >> 8) & 0x0F);      /* MNC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMnc >> 16) & 0x0F);     /* MNC Digit 3                              */
    pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                       /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
    {
        pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                  /* MNC Degit count                          */
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, pSysInfoInd->ucNetworkOperationMode))
    {                                                                           /* 设置RAI是否变化标志                      */
        ucRaiChgFlg                 = GMM_TRUE;
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }
    if (GMM_FALSE == Gmm_ComCmpLai(&(pRaiTemp->Lai)))
    {                                                                           /* 设置LAI是否变化标志                      */
        ucLaiChgFlg = GMM_TRUE;
    }

    ucNetMod = pSysInfoInd->ucNetworkOperationMode;

    Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* 存储系统信息中的RAI                      */
    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenFlg;   /* PLMN是否禁止                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */

    /* G下系统消息不带DRX LENGTH ，删除*/

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        if (GMM_NULL == g_GmmGlobalCtrl.ucState)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChangeGsm:WARNING: g_GmmGlobalCtrl.ucState is GMM_NULL");
            Gmm_MemFree(pRaiTemp);
            return;
        }
        if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* 调用状态的公共处理                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                      /* 调用状态的公共处理                       */
        }
        if (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* 停T3312                                  */
        }
        else
        {
            if (GMM_TRUE == ucLaiChgFlg)
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                }
#endif
                Gmm_TimerStop(GMM_TIMER_T3312);                                 /* 停T3312                                  */
            }
            else
            {
                if (GMM_DEREGISTERED_NO_CELL_AVAILABLE
                    == g_GmmGlobalCtrl.ucState)
                {
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif
                    Gmm_TimerStop(GMM_TIMER_T3312);                             /* 停T3312                                  */

                    NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
                }
                else
                {
                    if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                    {
#if (FEATURE_LTE == FEATURE_ON)
                        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                        }
#endif
                        Gmm_TimerStart(GMM_TIMER_T3312);                            /* 起T3312                                  */
                    }
                }
            }
        }
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (0 != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_II == ucNetMod))
    {                                                                           /* 网络模式变更 I->II                       */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_I_II, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
            return;
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_I == ucNetMod))
    {                                                                           /* 网络模式变更                             */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */

        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_II_I, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_III == ucNetMod))
    {/* 网络模式GSM I改变到网络模式GSM III */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_I_III, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_III == ucNetMod))
    {/* 网络模式GSM II改变到网络模式GSM III */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_II_III, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_III == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_I == ucNetMod))
    {/* 网络模式GSM III改变到网络模式GSM I */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_III_I, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_III == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_II == ucNetMod))
    {/* 网络模式GSM III改变到网络模式GSM II */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_III_II, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }
    Gmm_MemFree(pRaiTemp);
    return;
}



VOS_VOID Gmm_RcvMmcGmmModeChangeReq(
    VOS_VOID                           *pMsg                                   /* 消息指针                                 */
)
{
    MMCGMM_MODE_CHANGE_REQ_STRU        *pModeChg;                                   /* 定义指针                                 */

    pModeChg = (MMCGMM_MODE_CHANGE_REQ_STRU *)pMsg;                             /* 初始化指针                               */

    switch (pModeChg->enMsMode)
    {                                                                           /* 用户模式                                 */
    case NAS_MML_MS_MODE_NULL:
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {                                                                       /* PS域注册被禁止                           */
            /*Gmm_ComStaChg(GMM_NULL);*/                                            /* 状态迁移到GMM_NULL                       */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: MMCGMM_MODE_CHANGE_REQ is invalid");
        }
        break;
    case NAS_MML_MS_MODE_PS_CS:
        if ( (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_DEREGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_NULL == g_GmmGlobalCtrl.ucState) )
        {                                                                       /* GMM状态为NULL                            */
            if (GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
            {                                                                   /* MS当前驻留在小区上                       */
                if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
                {                                                               /* SIM不存在                                */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
                }
                else if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
                {                                                               /* SIM无效                                  */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                }
                else
                {                                                               /* SIM有效                                  */
                    if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* 状态迁移                                 */
                    }
                    else
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    }
                }
            }
            else
            {                                                                   /* 没有小区驻留                             */
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);              /* 状态迁移                                 */
            }
        }
        break;
    case NAS_MML_MS_MODE_PS_ONLY:
        if ( (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_DEREGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_NULL == g_GmmGlobalCtrl.ucState) )
        {                                                                       /* GMM状态为NULL                            */
            if (GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
            {                                                                   /* MS当前驻留在小区上                       */
                if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
                {                                                               /* SIM不存在                                */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
                }
                else if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
                {                                                               /* SIM无效                                  */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                }
                else
                {                                                               /* SIM有效                                  */
                    if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* 状态迁移                                 */
                    }
                    else
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    }

                }
            }
            else
            {                                                                   /* 没有小区驻留                             */
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);              /* 状态迁移                                 */
            }
        }
        break;
    case NAS_MML_MS_MODE_CS_ONLY:
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {                                                                       /* PS域注册被禁止                           */
            /*Gmm_ComStaChg(GMM_NULL);*/                                            /* 状态迁移到GMM_NULL                       */
            if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* 状态迁移                                 */
            }
            else
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: MMCGMM_MODE_CHANGE_REQ is invalid");
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: The MsMode is Abnormal");
        break;
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_GmmStatusMsgMake
  Function : GMM STATUS消息的作成
  Input    : VOS_UINT8    ucRejectCause                     错误原因
  Output   : 无
  NOTE     : 无
  Return   : NAS_MSG_STRU *pGmmStatus  指向NAS_MSG_STRU结构的指针
  History  :
    1. 张志勇  2004.04.14  新规作成
*******************************************************************************/
NAS_MSG_STRU *Gmm_GmmStatusMsgMake(
                                   VOS_UINT8    ucRejectCause                       /* 错误原因                                 */
                                   )
{
    NAS_MSG_STRU *pGmmStatus = VOS_NULL_PTR;                                            /* 指向NAS_MSG_STRU结构的指针变量           */

    pGmmStatus = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));           /* 申请内存空间                             */
    if (VOS_NULL_PTR == pGmmStatus)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_GmmStatusMsgMake:ERROR: Alloc mem fail.");
        return pGmmStatus;
    }
    Gmm_MemSet(pGmmStatus, 0, sizeof(NAS_MSG_STRU));                            /* 内存空间清0                              */

    /* 填写空口消息参数             */
    pGmmStatus->ulNasMsgSize = GMM_MSG_LEN_GMM_STATUS;                          /* 填写空口消息长度                         */
    pGmmStatus->aucNasMsg[0] = GMM_PD_GMM;                                      /* 填写Protocol discriminator               */
    pGmmStatus->aucNasMsg[1] = GMM_MSG_GMM_STATUS;                              /* 填写Attach complete message identity     */
    pGmmStatus->aucNasMsg[2] = ucRejectCause;                                   /* 填写GMM cause                            */

    return pGmmStatus;
}


VOS_VOID Gmm_RcvTcTestReq(
    VOS_VOID                           *pMsg                                    /* 指向原语的指针                           */
)
{
    TCGMM_TEST_REQ_STRU                *pTcTestReq = VOS_NULL_PTR;              /* 定义原语类型指针                         */

    pTcTestReq = (TCGMM_TEST_REQ_STRU *)pMsg;                                   /* 强制类型转换                             */

    if (TC_RB_TEST_ACTIVE == pTcTestReq->ulMode)
    {                                                                           /* TC激活                                   */
        g_GmmGlobalCtrl.ucTcPreSta = g_GmmGlobalCtrl.ucState;

        GMM_CasFsmStateChangeTo(GMM_TC_ACTIVE);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvTcTestReq:NORMAL: STATUS IS GMM_TC_ACTIVE");

        Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
        Gmm_TimerPauseForTc(GMM_TIMER_ALL);                                     /* 挂起所有运行中的Timer                    */


        /* 设置PS TC业务存在，以控制MMC不进行搜网等活动。
           通过PS域建立TC环回时，不会设置PS业务存在，故需在此处设置PS TC业务存在。

           通过CS域建立TC环回，收到接入层的PAGING消息时，即会设置CS业务存在，故
           TC环回建立时不需再单独设置CS业务存在。 */

        NAS_MML_SetPsTcServiceFlg(VOS_TRUE);

    }
    else if (TC_RB_TEST_DEACTIVE == pTcTestReq->ulMode)
    {                                                                           /* TC去激活                                 */
        GMM_CasFsmStateChangeTo(g_GmmGlobalCtrl.ucTcPreSta);

        PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvTcTestReq:NORMAL: STATUS IS ",g_GmmGlobalCtrl.ucState);

        Gmm_TimerResumeForTc(GMM_TIMER_ALL);                                    /* 恢复所有被挂起的Timer                    */


        /* 设置PS TC业务不存在 */
        NAS_MML_SetPsTcServiceFlg(VOS_FALSE);


    }
    else
    {
    }
}

/*******************************************************************************
  Module   : Gmm_RcvTcDataReq
  Function : 收到TCGMM_DATA_REQ原语的处理
  Input    : VOS_VOID *pMsg
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.06.18  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvTcDataReq(
                      VOS_VOID *pMsg                                            /* 指向原语的指针                           */
                      )
{

    TCGMM_DATA_REQ_STRU           *pTcDataReq;                                  /* 定义原语类型指针                         */
    NAS_MSG_STRU                  *pTcMsg;

    if (GMM_TC_ACTIVE != g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前状态不是GMM_TC_ACTIVE                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvTcDataReq:WARNING: TCGMM_DATA_REQ is unexpected");
        return;
    }
    pTcDataReq = (TCGMM_DATA_REQ_STRU *)pMsg;                                   /* 强制类型转换                             */

    pTcMsg = (NAS_MSG_STRU *)(&pTcDataReq->SendTcMsg);

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {
        Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH, pTcMsg);              /* 发送 RRMM_DATA_REQ                       */
    }
    return;
}
/*******************************************************************************
Module   : Gmm_RcvGmmStatusMsg
Function : 收到GMM STATUS消息的处理
Input    : NAS_MSG_STRU *pMsg
Output   : 无
NOTE     : 无
Return   : 无
History  :
    1. 张志勇  2005.01.25  新规作成(for agent)
*******************************************************************************/
VOS_VOID Gmm_RcvGmmStatusMsg(
                                          NAS_MSG_FOR_PCLINT_STRU *pMsg
                                         )
{
    NAS_MSG_STRU        *pGmmStatus;

    if (GMM_MSG_LEN_GMM_STATUS > pMsg->ulNasMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvGmmStatusMsg:WARNING: The length of GMM STATUS is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    return;
}
/* 废弃代码删除 */


VOS_VOID GRM_Inform_Gmm()
{
    LL_DATA_INFORM_MSG                 *pMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    if ((VOS_TRUE == NAS_MML_GetPsTbfStatusFlg())
     && (NAS_MML_NET_RAT_TYPE_GSM == gstGmmCasGlobalCtrl.ucLastDataSender))
    {
        /* 状态不对，过滤无需给gmm 发ID_LL_DATA_INFORM消息 */
        if ((g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
         && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
        {
            return;
        }

        /* ready timer定时器时长为0，过滤无需给gmm 发ID_LL_DATA_INFORM消息 */
        if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
        {
            return;
        }

        /* ready timer定时器时长为0xffffffff且已为ready态过滤，无需给gmm 发ID_LL_DATA_INFORM消息 */
        if ((0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue)
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            return;
        }

        /* TC状态t3314已启动且已为ready态过滤，无需给gmm 发ID_LL_DATA_INFORM消息 */
        if ((GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
         && (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            return;
        }

        /* 非TC状态t3314已启动且已为ready态过滤，无需给gmm 发ID_LL_DATA_INFORM消息 */
        if ((GMM_TC_ACTIVE != g_GmmGlobalCtrl.ucState)
         && (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
         && (VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].hTimer)
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
            Gmm_TimerStart(GMM_TIMER_T3314);

            return;
        }
    }

    pMsg = (LL_DATA_INFORM_MSG *)PS_ALLOC_MSG(UEPS_PID_LL,
                  sizeof(LL_DATA_INFORM_MSG) - VOS_MSG_HEAD_LENGTH );

    if (VOS_NULL_PTR == pMsg)
    {
        GMM_LOG_ERR("GRM_Inform_Gmm():Error: Failed in VOS_AllocMsg()");
        return;
    }

    /* 消息头固定的参数 */
    pMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = UEPS_PID_LL;
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid   = WUEPS_PID_GMM;

    /* 填写消息发送参数 */
    pMsg->ulMsgName = ID_LL_DATA_INFORM;

    ulRet = PS_SEND_MSG(UEPS_PID_LL, pMsg);

    if (VOS_OK != ulRet)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GRM_Inform_Gmm():Error: Failed in VOS_SendMsg()");
    }


    return;
}
/******************************************************************************
 * 函数名称 ： WuepsGmmPidInit
 * 功能描述 ： WUEPS GMM PID的初始化函数
 * 参数说明 ： 无
 * 备    注 ：
 * 返 回 值 ： VOS_UINT32 初始化结果：
 *             0  : 成功
 *             非0: 失败
 *
 * 变更历史 ：
 *           No.  姓名      变更                                    日   期
 *           1    张志勇    新建                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsGmmPidInit (enum VOS_INIT_PHASE_DEFINE ip)
{
    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}


VOS_VOID Gmm_RcvLLCInform( VOS_VOID *pMsg )
{
    /* 设置GSM模式下PS域存在业务或者在进行注册 */
    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);

    gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_GSM;


    if ((g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        return;
    }


    if (0 != gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        /*A32D12829==>*/
        if (0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue)
        {
            if (GMM_AGB_GPRS_READY != gstGmmCasGlobalCtrl.GmmSrvState)
            {
                /* 下面启动T3314，停止T3312 */
                if ( GMM_TIMER_T3312_FLG == (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask) )
                {
                    Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
                     NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
                }
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;

#if (FEATURE_LTE == FEATURE_ON)
                if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    Gmm_TimerStop(GMM_TIMER_T3323);
                }
#endif
                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
            }
            return;
        }
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;
        if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        {
            if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
            {
                Gmm_TimerStart(GMM_TIMER_T3314);
                Gmm_TimerPauseForTc(GMM_TIMER_T3314);                               /* 挂起T3312                                */
            }
        }
        else
        {
            if (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
            {                                                                           /* 该timer已经启动                          */
               if(VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].hTimer)
               {

                   Gmm_TimerStop(GMM_TIMER_T3314);
                   Gmm_TimerStart(GMM_TIMER_T3314);
               }
               else
               {
                   g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_T3314);         /* 清Timer的启动标志                        */
                   g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                   Gmm_TimerStart(GMM_TIMER_T3314);
               }
            }
            else
            {
                /*<==A32D12829*/
                g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                Gmm_TimerStart(GMM_TIMER_T3314);
            }

        }
        if (GMM_AGB_GPRS_READY != gstGmmCasGlobalCtrl.GmmSrvState)
        {

            /* 下面启动T3314，停止T3312 */
            if ( GMM_TIMER_T3312_FLG == (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask) )
            {
                Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
                 NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
            }
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;

#if (FEATURE_LTE == FEATURE_ON)
            if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                Gmm_TimerStop(GMM_TIMER_T3323);
            }
#endif
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_PrintState
 Description    : 打印GMM状态
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-10-17
    Author      : Roger Leo
    Modification: created
*****************************************************************************/
VOS_VOID GMM_PrintState(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_NULL:
            GMM_LOG_INFO("GMM State is GMM_NULL.");
            break;
        case GMM_REGISTERED_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_INITIATED.");
            break;
        case GMM_DEREGISTERED_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_INITIATED.");
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_ROUTING_AREA_UPDATING_INITIATED.");
            break;
        case GMM_SERVICE_REQUEST_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_SERVICE_REQUEST_INITIATED.");
            break;
        case GMM_TC_ACTIVE:
            GMM_LOG_INFO("GMM State is GMM_TC_ACTIVE.");
            break;
        case GMM_GPRS_SUSPENSION:
            GMM_LOG_INFO("GMM State is GMM_GPRS_SUSPENSION.");
            break;
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NORMAL_SERVICE.");
            break;
        case GMM_DEREGISTERED_LIMITED_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_LIMITED_SERVICE.");
            break;
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_ATTACH_NEEDED.");
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH.");
            break;
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NO_CELL_AVAILABLE.");
            break;
        case GMM_DEREGISTERED_PLMN_SEARCH:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_PLMN_SEARCH.");
            break;
        case GMM_DEREGISTERED_NO_IMSI:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NO_IMSI.");
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_NORMAL_SERVICE.");
            break;
        case GMM_REGISTERED_LIMITED_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_LIMITED_SERVICE.");
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_UPDATE_NEEDED.");
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_ATTEMPTING_TO_UPDATE.");
            break;
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_NO_CELL_AVAILABLE.");
            break;
        case GMM_REGISTERED_PLMN_SEARCH:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_PLMN_SEARCH.");
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM.");
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_IMSI_DETACH_INITIATED.");
            break;
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_NORMAL_SERVICE.");
            break;
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_GPRS_SUSPENSION.");
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_WAIT_FOR_SYSINFO.");
            break;
        default:
            GMM_LOG_WARN("GMM State is Error.");
            break;
    }
    return;
}


VOS_UINT8 GMM_GetSignalingStatus(VOS_VOID)
{
    VOS_UINT8      ucResult = MMC_GMM_SIGNALING_STATUS_ABSENT;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
        && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat))
    {
        ucResult = MMC_GMM_SIGNALING_STATUS_PRESENT;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetCurServiceStatus: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);
    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetCurServiceStatus: ucResult is ",(VOS_INT32)ucResult);

    return ucResult;
}


VOS_UINT32 NAS_GMM_IsRegisteredOrRegistering(VOS_VOID)
{
    if (  (GMM_REGISTERED_NORMAL_SERVICE            == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_INITIATED                == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED     == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH   == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE     == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM  == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED           == g_GmmGlobalCtrl.ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 GMM_IsServiceExist(VOS_VOID)
{
    VOS_UINT32      ulResult;

    if((VOS_TRUE == NAS_MML_IsPsBearerExist())
    || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        ulResult = GMM_TRUE;
    }
    else
    {
        ulResult = GMM_FALSE;
    }
    return ulResult;
}


VOS_UINT32 NAS_GMM_GetSignalingStatusInGsm(VOS_VOID)
{
    VOS_UINT32      ulResult = VOS_FALSE;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (( ( VOS_TRUE == NAS_MML_GetPsTbfStatusFlg() )
        || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        ulResult = VOS_TRUE;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsAttatchingOrRauInGsm: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);
    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsAttatchingOrRauInGsm: ucResult is ",(VOS_INT32)ulResult);

    return ulResult;
}


VOS_VOID Gmm_BufSmDataReqMsg( VOS_VOID *pMsg )
{
    GMMSM_DATA_REQ_STRU                 *ptr;

    /*申请缓存消息的内存*/
    if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
               + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4);
    }
    if (VOS_NULL_PTR == ptr)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "Gmm_RcvSmDataReq_RegNmlServ:WARNING: Gmm_MemMalloc fail !! ");
          return;
    }

    /*把消息暂存到申请的内存中*/
    if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
    {
        Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
            + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4));
    }
    /*该方法只缓存最新的一条消息,若以前有缓存消息,则释放掉*/
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_BufferSmDataReq(): Cache SM data Req");

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)ptr;
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SM;

    return;
}

VOS_VOID Gmm_ComCnfHandle(VOS_VOID)
{
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }

    if ((GMM_SERVICE_REQUEST_DATA_IDLE   == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为SR_DATA                        */
        if (RR_REL_CAUSE_RRC_SNW == g_GmmGlobalCtrl.ucRelCause)
        {
            g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_OOS);                 /* 通知RABM结果                             */
        }
        else
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
        }
    }


    if ((GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType)
     || (GMM_WAIT_CS_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType))
    {

        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        NAS_GMM_SndMmcMmDetachInfo();
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除保留标志                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SMS
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)VOS_NULL;
    }

    if (GMM_MSG_HOLD_FOR_SM
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_ComCnfHandle(): Clear cached SM data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)VOS_NULL;
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)VOS_NULL;
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        switch (g_GmmGlobalCtrl.ucSpecProcHold)
        {                                                                       /* 保留的specific流程                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* 通知RABM结果                             */
            break;

        case GMM_DETACH_COMBINED:
        case GMM_DETACH_NORMAL:
        case GMM_DETACH_WITH_IMSI:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }

            if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
            {
                /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
                NAS_GMM_SndMmGprsDetachComplete();
            }

            break;

        default:
            break;
        }
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* 清除保留流程                             */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    }
}

VOS_UINT32 Gmm_GetState()
{
    return g_GmmGlobalCtrl.ucState;
}

VOS_UINT32 Gmm_GetGprsState()
{
    VOS_UINT32  ulGprsState;
    if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if ((0x10 == (g_GmmGlobalCtrl.ucState&0xf0))
            ||(GMM_NULL == g_GmmGlobalCtrl.ucState))
        {
            ulGprsState = GMM_IU_PMM_DETACHED;
        }
        else if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            ulGprsState = GMM_IU_PMM_CONNECTED;
        }
        else
        {
            ulGprsState = GMM_IU_PMM_IDLE;
        }
    }
    else
    {
        ulGprsState = gstGmmCasGlobalCtrl.GmmSrvState;
    }
    return ulGprsState;
}


VOS_VOID Gmm_FillNasMmInfo_NetMod(NAS_OM_MM_IND_STRU       *pMsg)
{
    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_1;
    }
    else if (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_2;
    }
    else if (GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_3;
    }
    else
    {
        pMsg->enNetMode = NET_OPERATE_MODE_BUTT;
    }

    return;
}


VOS_VOID NAS_GMM_FillNasGmmState(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    pstMsg->enGmmSubState = GMM_SUB_STATE_BUTT;

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_NULL:
            pstMsg->enGmmState = STATE_GMM_NULL;
            break;
        case GMM_REGISTERED_INITIATED:
            pstMsg->enGmmState = REGISTERED_INITIATED;
            break;
        case GMM_DEREGISTERED_INITIATED:
            pstMsg->enGmmState = DEREGISTERED_INITIATED;
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            pstMsg->enGmmState = ROUTING_AREA_UPDATING_INITIATED;
            break;
        case GMM_SERVICE_REQUEST_INITIATED:
            pstMsg->enGmmState = SERVICE_REQUEST_INITIATED;
            break;
        case GMM_TC_ACTIVE:
            pstMsg->enGmmState = TC_ACTIVE;
            break;
        case GMM_GPRS_SUSPENSION:
            pstMsg->enGmmState = GPRS_SUSPENSION;
            break;
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NORMAL_SERVICE;
            break;
        case GMM_DEREGISTERED_LIMITED_SERVICE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_LIMITED_SERVICE;
            break;
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_ATTACH_NEEDED;
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_ATTEMPTING_TO_ATTACH;
            break;
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NO_CELL_AVAILABLE;
            break;
        case GMM_DEREGISTERED_PLMN_SEARCH:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_PLMN_SEARCH;
            break;
        case GMM_DEREGISTERED_NO_IMSI:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NO_IMSI;
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_NORMAL_SERVICE;
            break;
        case GMM_REGISTERED_LIMITED_SERVICE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_LIMITED_SERVICE;
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_UPDATE_NEEDED;
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_ATTEMPTING_TO_UPDATE;
            break;
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_NO_CELL_AVAILABLE;
            break;
        case GMM_REGISTERED_PLMN_SEARCH:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_PLMN_SEARCH;
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_ATTEMPTING_TO_UPDATE_MM;
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_IMSI_DETACH_INITIATED;
            break;
        case GMM_SUSPENDED_NORMAL_SERVICE:
            pstMsg->enGmmState = SUSPENDED_NORMAL_SERVICE;
            break;
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            pstMsg->enGmmState = SUSPENDED_GPRS_SUSPENSION;
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            pstMsg->enGmmState = SUSPENDED_WAIT_FOR_SYSINFO;
            break;
        default:
            pstMsg->enGmmState = GMM_STATE_BUTT;
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_FillNasMmInfo:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;
    }

    NAS_GMM_FillNasGmmGprsState(pstMsg);

    return;
}


VOS_VOID NAS_GMM_FillNasGmmGprsState(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    pstMsg->enGmmGprsState              = NAS_OM_GMM_GPRS_STATE_BUTT;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        switch(gstGmmCasGlobalCtrl.GmmSrvState)
        {
            case GMM_AGB_GPRS_IDLE:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_IDLE;
                break;
            case GMM_AGB_GPRS_STANDBY:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_STANDBY;
                break;
            case GMM_AGB_GPRS_READY:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_READY;
                break;
            default:
                break;
        }
    }

    return;
}


VOS_VOID Gmm_FillNasMmInfo_ucUpdateSta(NAS_OM_MM_IND_STRU     *pMsg)
{
    switch (NAS_MML_GetPsUpdateStatus())
    {
    case NAS_MML_ROUTING_UPDATE_STATUS_UPDATED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU1;
        break;
    case NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU2;
        break;
    case NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED:
    case NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU3;
        break;
    default:
        pMsg->enGmmUpdateStatus = GMM_UPDATE_STATUS_BUTT;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "Gmm_FillNasMmInfo:WARNING: PsUpdateStatus is Error");
    }

    return;
}




VOS_VOID Gmm_Com_ServiceStatus_Handle(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {         /* 以下状态需要上报服务状态    */
    case GMM_NULL:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_IMSI:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:


        /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
        break;

    default:
        break;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Com_ServiceStatus_Handle:INFO: g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);

    return;
}

NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 Gmm_ComServiceSts(VOS_VOID)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8       ucServiceSts = MM_COM_SRVST_NO_CHANGE;                     /* 定义临时变量                             */

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态置服务状态                       */
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        ucServiceSts = MM_COM_SRVST_NORMAL_SERVICE;
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        ucServiceSts = NAS_GMM_GetRegUptNeededPsSrvStatus();
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE;

        if (GMM_TRUE == g_GmmGlobalCtrl.ucLaNotAllowFlg)
        {
            ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE_REGION;
            g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_FALSE;
        }
        break;

    case GMM_DEREGISTERED_NO_IMSI:
        ucServiceSts = MM_COM_SRVST_NO_IMSI;
        break;

    case GMM_NULL:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        ucServiceSts = MM_COM_SRVST_NO_SERVICE;
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        if (5 == g_GmmRauCtrl.ucRauAttmptCnt)
        {
            ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE;
        }
        else
        {
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComServiceSts:WARNING: Unexpected g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);
        }
        break;
    default:
        PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComServiceSts:WARNING: Unexpected g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);
        break;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ComServiceSts:INFO: g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ucServiceSts;
}

VOS_UINT32 Gmm_GetServiceStatusForSms(VOS_VOID)
{
    GMM_STATE_TYPE_UINT8    ucState;
    VOS_UINT32              ulServiceSts = GMM_SMS_NO_SERVICE;                  /* 定义临时变量                             */

    if ((GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ucState = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        ucState = g_GmmGlobalCtrl.ucState;
    }

    switch (ucState)
    {                                                                           /* 根据状态置服务状态                       */
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        ulServiceSts = GMM_SMS_NORMAL_SERVICE;
        break;
    default:
        break;
    }

    return ulServiceSts;
}


VOS_VOID NAS_GMM_RcvInterRatHandoverInfoCnf(VOS_VOID *pMsg)
{
    RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU   *pRrmmInterRatInfoMsg = VOS_NULL_PTR;
    NAS_MSG_STRU                            *pSendNasMsg = VOS_NULL_PTR;

    pRrmmInterRatInfoMsg = (RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU *)pMsg;

    Gmm_TimerStop(GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF);

    g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg   = VOS_TRUE;
    g_GmmInterRatInfoCtrl.ucDataLen                 = (VOS_UINT8)pRrmmInterRatInfoMsg->usDataLen;

    if (0 == pRrmmInterRatInfoMsg->usDataLen)
    {
        /* WRR生成InterRatHandover失败 */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Msg Len is 0.");
    }
    else
    {
        /* InterRatHandoverInfo 信息保存到全局变量中 */
        PS_MEM_CPY(g_GmmInterRatInfoCtrl.aucData, pRrmmInterRatInfoMsg->aucData, g_GmmInterRatInfoCtrl.ucDataLen);
    }

    if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg)
    {
        if (VOS_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            /* ATTACH过程是由SM触发的,通知SM GMM注册成功,并清ucSmCnfFlg标志 */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
            g_GmmAttachCtrl.ucSmCnfFlg = VOS_FALSE;
        }

        /* 回复网络Attach Complete 消息 */
        pSendNasMsg = Gmm_AttachCompleteMsgMake();

        if (VOS_NULL_PTR == pSendNasMsg)
        {
            NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Make Attach Complete Msg Fail!");
            return;
        }
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);

    }
    else if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
    {
        /* 不需要等待RABM的回复消息，或者已经收到RABM的回复消息，进行RAU流程结束的相应处理 */
        if (   (VOS_FALSE == gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg)
            || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg))
        {
            NAS_GMM_RauCompleteHandling();
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Not Expected Msg Received.");
    }

    return;
}


VOS_UINT32 NAS_GMM_IsInHandoverProcedure(VOS_VOID)
{
    VOS_UINT32      ulResult = VOS_FALSE;

    if ((GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
        || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ulResult = VOS_TRUE;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsInHandoverProcedure: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ulResult;
}


VOS_UINT32  NAS_GMM_IsInRegisterProcedure(VOS_VOID)
{
    /* 判断当前是否在注册过程中 */
    if((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_VOID NAS_GMM_CnfSmNotAttach(
    GMM_SM_CAUSE_ENUM_UINT16            enCause                                 /* 注册失败原因值 */
)
{
    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, enCause);
        g_GmmAttachCtrl.ucSmCnfFlg            = GMM_FALSE;
        g_GmmGlobalCtrl.ucFollowOnFlg         = GMM_FALSE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
         && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
    }
}


VOS_UINT32 NAS_GMM_IsInRegOrDeregProcedure(VOS_VOID)
{
    VOS_UINT8      ucResult;

    ucResult = VOS_FALSE;

    /* WCDMA模式下，当在进行注册/去注册，或者在业务过程中时，认为存在连接；
      GSM模式下，当TBF存在时，认为存在连接 */
    if ( (GMM_REGISTERED_INITIATED             == g_GmmGlobalCtrl.ucState)
      || (GMM_DEREGISTERED_INITIATED           == g_GmmGlobalCtrl.ucState)
      || (GMM_ROUTING_AREA_UPDATING_INITIATED  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        ucResult = VOS_TRUE;
    }

    NAS_NORMAL_LOG1(WUEPS_PID_GMM, "NAS_GMM_IsInRegisterOrDeregisterProcedure: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ucResult;
}


VOS_UINT32 NAS_Gmm_IsInServiceProcedure(VOS_VOID)
{
    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32  NAS_MMC_GetGmmRegStateForInterPLmnList( VOS_VOID )
{
    VOS_UINT8                           ucTimerId;
    VOS_BOOL                            bTimerRunning;
    VOS_UINT32                          ulTimerRunMask;

    /* 小区被bar的情况 */
    if ( ( GMM_DEREGISTERED_ATTACH_NEEDED        == g_GmmGlobalCtrl.ucState)
      || ( GMM_REGISTERED_UPDATE_NEEDED          == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    ucTimerId   = GMM_TIMER_T3302;

    ulTimerRunMask = g_GmmTimerMng.ulTimerRunMask;

    /*lint -e701*/
    if (0 != ( ulTimerRunMask & ( 0x00000001 << ucTimerId )))
    /*lint +e701*/
    {
        bTimerRunning = VOS_TRUE;
    }
    else
    {
        bTimerRunning = VOS_FALSE;
    }

    if ( VOS_FALSE == bTimerRunning )
    {
        return VOS_ERR;
    }


    if ( ( GMM_REGISTERED_ATTEMPTING_TO_UPDATE   == g_GmmGlobalCtrl.ucState)
      || ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    if ( ( GMM_DEREGISTERED_NO_IMSI   == g_GmmGlobalCtrl.ucState)
      || ( GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}



VOS_VOID  NAS_GMM_ConvertPlmnIdToMmcFormat(
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId
)
{

    pstMmcPlmnId->ulMcc = pstGmmPlmnId->aucMccDigit[0]
                        | (pstGmmPlmnId->aucMccDigit[1] << 8)
                        | (pstGmmPlmnId->aucMccDigit[2] << 16);

    pstMmcPlmnId->ulMnc = pstGmmPlmnId->aucMncDigit[0]
                        | (pstGmmPlmnId->aucMncDigit[1] << 8)
                        | (pstGmmPlmnId->aucMncDigit[2] << 16);
}

VOS_VOID  NAS_GMM_ConvertPlmnIdToGmmFormat(
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId,
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId
)
{
    pstGmmPlmnId->aucMccDigit[0] =
        (VOS_UINT8)(pstMmcPlmnId->ulMcc & 0x0F);

    pstGmmPlmnId->aucMccDigit[1] =
        (VOS_UINT8)((pstMmcPlmnId->ulMcc >> 8) & 0x0F);

    pstGmmPlmnId->aucMccDigit[2] =
        (VOS_UINT8)((pstMmcPlmnId->ulMcc >> 16) & 0x0F);

    pstGmmPlmnId->ucMncCnt = 3;

    pstGmmPlmnId->aucMncDigit[0] =
        (VOS_UINT8)(pstMmcPlmnId->ulMnc & 0x0F);

    pstGmmPlmnId->aucMncDigit[1] =
        (VOS_UINT8)((pstMmcPlmnId->ulMnc >> 8) & 0x0F);

    pstGmmPlmnId->aucMncDigit[2] =
        (VOS_UINT8)((pstMmcPlmnId->ulMnc >> 16) & 0x0F);

    if (GMM_PLMNID_MNC3_INVALID == pstGmmPlmnId->aucMncDigit[2])
    {
        pstGmmPlmnId->ucMncCnt = 2;                                      /* MNC Degit count                          */
    }

}





VOS_UINT32 NAS_GMM_IsDeregisterState(
    GMM_STATE_TYPE_UINT8                ucState
)
{
    if ((GMM_REGISTERED_INITIATED == ucState)
     || (GMM_DEREGISTERED_NORMAL_SERVICE == ucState)
     || (GMM_DEREGISTERED_LIMITED_SERVICE == ucState)
     || (GMM_DEREGISTERED_ATTACH_NEEDED == ucState)
     || (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == ucState)
     || (GMM_DEREGISTERED_NO_CELL_AVAILABLE == ucState)
     || (GMM_DEREGISTERED_PLMN_SEARCH == ucState)
     || (GMM_DEREGISTERED_NO_IMSI == ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID Gmm_FreeBufferMsgWithoutSm(VOS_VOID)
{
    VOS_VOID                *pAddr;                                             /* 定义指针                                 */

    if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* 如果有保留的paging(IMSI)原语             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* 读取paging(IMSI)原语地址                 */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* 如果有保留的RAU原语                      */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* 清除缓存标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* 读取RAU原语地址                          */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* 读取detach原语地址                       */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* 如果有保留的attach原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* 读取attach原语地址                       */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的ServiceRequest原语           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* 读取ServiceRequest原语地址               */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}


VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiChg()
{
    g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* 清除T3312溢出标记                        */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                       /* 非A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
    }
    else
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 调用RAU过程                              */
    }
}

VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312Expire()
{
    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                   /* 非A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
          || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {                                                                   /* A+I                                      */
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* 调用RAU过程combined RAU with IMSI attach */
    }
}


VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312NotExpire()
{
    VOS_UINT8                           ucCsAttachAllow;

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();

    /* 当前PS更新状态为U1 */
    if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
    {
        /* 非网络模式I的处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
         || (VOS_TRUE != ucCsAttachAllow)
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
        else
        {
            /* CS更新状态为U1，且Gs连接存在 */
            if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                {
                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
                }

                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
            else                                                                /* CS更新状态不是U1,或者Gs关联已经移除 */
            {
                /* sim无效或者CS域不允许注册 */
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
                    }

                    GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);                     /* 调用RAU                                  */
                }
            }
        }
    }
    else
    {
        /* 更新状态不是GU1,发起RAU */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
}


VOS_VOID  NAS_GMM_ProcPsAcChgRegisterNetRaiNotChg()
{
    if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
    {
        /* T3312超时标志不存在　*/
        NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312NotExpire();
    }
    else
    {
        /* T3312超时标志存在　*/
        NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312Expire();
    }
}


VOS_VOID NAS_GMM_ComProcAcInfoChgInd(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    /* 重选到PS被BARRED的小区,在网络模式I,并且T3312超时 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
         && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
    }
    /* 当前业务受限，则清除业务缓存 */
    if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    {
        /* 清除缓存 */
        Gmm_ComCnfHandle();
        GMM_BufferMsgDump();
    }
}


VOS_VOID  NAS_GMM_RcvMmcWasAcInfoChgInd_Dereg(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    /* PS 注册从不受限到受限 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        if (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState)
        {
            /* 网络模式I */
            if  ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        /* 设置当前PS服务状态为限制服务 */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
    }
}


VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimitServ(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    /* PS 注册受限 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        /* 迁移当前GMM状态到GMM_REGISTERED_UPDATE_NEEDED */
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
    }
}

VOS_VOID  NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = NAS_MML_GetNetworkInfo();

    /* PS 注册从受限到不受限 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        g_GmmGlobalCtrl.SysInfo.ucSysValidFlg       = GMM_TRUE;
        g_GmmGlobalCtrl.SysInfo.ucNetMod            = pstNetworkInfo->stCampPlmnInfo.enNetworkMode;
        g_GmmGlobalCtrl.ucNetMod                    = g_GmmGlobalCtrl.SysInfo.ucNetMod;
        g_GmmGlobalCtrl.SysInfo.ucNtType            = NAS_MML_GetCurrNetRatType();
        g_GmmGlobalCtrl.SysInfo.ucPsDrxLen          = NAS_MML_GetWSysInfoDrxLen();
        if ( VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg )
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_SUPPORT_GPRS;
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_NOT_SUPPORT_GPRS;
        }

        g_GmmGlobalCtrl.SysInfo.Rai.ucRac = NAS_MML_GetCurrCampRac();
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[0];
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[1];
        g_GmmGlobalCtrl.SysInfo.ulCellId = pstNetworkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstNetworkInfo->stCampPlmnInfo.stLai.stPlmnId),&g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId);

        /* PS卡无效 */
        if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
        {                                                                           /* 原来SIM无效                              */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);
            return;
        }

        /* 当前用户设置不支持PS注册 */
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                         /* 调用状态的公共处理                       */

            GMM_BufferMsgResume();
            return;
        }

        /* 当前网络不支持GPRS，或者网络在禁止列表 */
        if ((GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
         || (MMC_GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask))
        {                                                                           /* 不支持GPRS                               */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        }
        else
        {                                                                           /* 小区改变                                 */
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
    }


}


VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    VOS_UINT8                           ucCsAttachAllow;                        /* CS域是否允许注册,VOS_TRUE:允许CS域注册,VOS_FALSE:不允许CS域注册 */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo = VOS_NULL_PTR;

    pstCampInfo         = NAS_MML_GetCurrCampPlmnInfo();
    ucCsAttachAllow     = NAS_MML_GetCsAttachAllowFlg();

    /* PS 注册不受限到受限 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);

        if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
        {
            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* 通知MM进行LU */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
            }
            else
            {
                 /* 通知MM进行LU */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
            }
        }
    }
    else
    {
        /* 网络模式I,手机模式A,CS卡有效,Gs连接标志不存在，且当前CS信令不存在，
        CS注册从受限变为不受限时需要发起联合注册 */
        if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
         && (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
         && (VOS_TRUE == ucCsAttachAllow)
         && (NAS_MML_NET_MODE_I == pstCampInfo->enNetworkMode)
         && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
    }
}


VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = NAS_MML_GetNetworkInfo();

    /* PS 注册从受限到不受限 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        g_GmmGlobalCtrl.SysInfo.ucNetMod            = pstNetworkInfo->stCampPlmnInfo.enNetworkMode;
        g_GmmGlobalCtrl.ucNetMod                    = g_GmmGlobalCtrl.SysInfo.ucNetMod;
        g_GmmGlobalCtrl.SysInfo.ucNtType            = NAS_MML_GetCurrNetRatType();
        g_GmmGlobalCtrl.SysInfo.ucPsDrxLen          = NAS_MML_GetWSysInfoDrxLen();
        if ( VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg )
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_SUPPORT_GPRS;
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_NOT_SUPPORT_GPRS;
        }
        g_GmmGlobalCtrl.SysInfo.Rai.ucRac = NAS_MML_GetCurrCampRac();
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[0];
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[1];
        g_GmmGlobalCtrl.SysInfo.ulCellId = pstNetworkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstNetworkInfo->stCampPlmnInfo.stLai.stPlmnId),&g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId);
        if (VOS_FALSE ==  NAS_MML_GetPsAttachAllowFlg())
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
        /* 当前网络不支持GPRS */
        else if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
        /* 当前网络在禁止列表 */
        else if (MMC_GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask)
        {
            Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        }
        else if (VOS_FALSE == NAS_MML_IsRaiChanged())
        {
            /* RAI没有改变 */
            NAS_GMM_ProcPsAcChgRegisterNetRaiNotChg();
        }
        else
        {
            /* RAI改变 */
            NAS_GMM_ProcPsAcChgRegisterNetRaiChg();
        }
    }

}


VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd(
    NAS_MSG_STRU                       *pstMsg
)
{
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd = (MMCGMM_W_AC_INFO_CHANGE_IND_STRU*)pstMsg;

    /* 将原语RRMM_W_INFO_CHANGE_IND按照状态分发 */
    switch (g_GmmGlobalCtrl.ucState)
    {
        /* DEREG状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            NAS_GMM_RcvMmcWasAcInfoChgInd_Dereg(pstAcInfoChangeInd);
            break;
        case GMM_DEREGISTERED_INITIATED:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_REGISTERED_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
            break;

        /* REG LIMITED SERVICE状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimitServ(pstAcInfoChangeInd);
            break;

        /* GMM_DEREGISTERED_ATTACH_NEEDED状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded(pstAcInfoChangeInd);
            break;

        /* REG NORMAL状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ(pstAcInfoChangeInd);
            break;

        /* GMM_REGISTERED_UPDATE_NEEDED状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_REGISTERED_UPDATE_NEEDED:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded(pstAcInfoChangeInd);
            break;
        default :
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd:WARNING:g_GmmGlobalCtrl.ucState is Error");
            break;
    }

    NAS_GMM_ComProcAcInfoChgInd(pstAcInfoChangeInd);

}

NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 NAS_GMM_GetRegUptNeededPsSrvStatus()
{
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

    /* 如果当前RAI和上次成功注册的RAI相同，UPDATE状态为U1，OTHER不受限为正常服务，否则为限制服务 */
    if ((VOS_FALSE == NAS_MML_IsRaiChanged())
     && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus))
    {
        return MM_COM_SRVST_NORMAL_SERVICE;
    }
    else
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucLaNotAllowFlg)
        {
            g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_FALSE;
            return MM_COM_SRVST_LIMITED_SERVICE_REGION;
        }
        else
        {
            return MM_COM_SRVST_LIMITED_SERVICE;
        }
    }
}


VOS_VOID NAS_GMM_ProcSmDataReq_RAUInit(
    VOS_VOID                           *pSmDataReqMsg
)
{
    VOS_UINT8                           ucMsgType;

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_GMM_ProcSmDataReq_RAUInit:NORMAL:Gmm receive SM Data Req.");

    /* 是去激活接受或者SM STATUS消息,有链接时立刻发给网络,没有链接时丢弃;
       否则缓存消息 */
    ucMsgType = NAS_GMM_GetGmmSmDataReqMsgType(&((GMMSM_DATA_REQ_STRU *)pSmDataReqMsg)->SmMsg);
    if ((SM_DEACT_PDP_CONTEXT_ACC == ucMsgType)
     || (SM_STATUS                == ucMsgType))
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &((GMMSM_DATA_REQ_STRU *)pSmDataReqMsg)->SmMsg);
        }
    }
    else
    {
        Gmm_BufSmDataReqMsg(pSmDataReqMsg);
    }
}

#if (FEATURE_ON == FEATURE_LTE)


VOS_UINT32 NAS_Gmm_IsPtmsiMappedFromGuti(VOS_VOID)
{
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;

    VOS_UINT32                          ulGetGutiRst;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* 判断GUPTMSI是否有效，VOS_TRUE:有效;VOS_FALSE:无效; */
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }
    else
    {
        ulLocalPtmsiFlg = VOS_FALSE;
    }

    /* 获取当前的Tin值和Mapped P-Tmsi */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
     && (VOS_OK == ulGetGutiRst) )
    {
        return VOS_TRUE;
    }

    if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
     && (VOS_FALSE == ulLocalPtmsiFlg)
     && (VOS_OK == ulGetGutiRst))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}
#endif





VOS_VOID NAS_GMM_FreeBufferCmMsg(VOS_VOID)
{
    VOS_VOID                           *pAddr;                                              /* 定义指针                                 */

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的ServiceRequest原语           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* 读取ServiceRequest原语地址               */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {                                                                           /* 如果有保留的SmDataReq原语                */
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_FreeBufferCmMsg(): Clear cached SM data Req");

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;           /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;             /* 读取SmDataReq原语地址                    */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }
}


VOS_UINT32 NAS_GMM_IsNeedEnableLte_AttachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)PS卡有效
    (3)USIM卡 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* 如果是SIM卡，不需要Enable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* disable 或enable lte不再判断syscfg是否支持L */

    /* PS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT8 NAS_GMM_GetAttachType(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictRegister;

    ucCsRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();

    /* ps不允许attach，不能做注册 */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return GMM_NULL_PROCEDURE;
    }

    /* 存在CS信令链接时，进行NORMAL ATTACH */
    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        /* 网络模式I, 若PS域单独注册成功后，收到系统消息后，需要再次触发COMBINED ATTACH */
        if ( GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod )
        {
            NAS_GMM_SetSpecProcInCsTrans(GMM_ATTACH_NORMAL);
        }

        return GMM_ATTACH_NORMAL;
    }

    if (((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
      || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)))
    {
        return GMM_ATTACH_NORMAL;
    }

    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* CS域SIM有效                              */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {                                                                       /* CS域已经注册                             */
            if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;       /* 清除CS通信中的流程                       */
                return GMM_ATTACH_NORMAL_CS_TRANS;
            }

            return GMM_ATTACH_WHILE_IMSI_ATTACHED;
        }

        if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
         || (VOS_TRUE == ucCsRestrictRegister))
        {
            /* CS域ATTACH被禁止 */
            return GMM_ATTACH_NORMAL;
        }

        /* CS域ATTACH没被禁止 */
        if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
        {
            /* CS域在通信中*/
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            return GMM_ATTACH_NORMAL_CS_TRANS;
        }

        /* CS域不在通信中 */
        return  GMM_ATTACH_COMBINED;

    }

    return GMM_ATTACH_NORMAL;

}


VOS_VOID NAS_GMM_RcvMmCsConnectInd_RrcConnExist(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsRestrictRegFlg;
    VOS_UINT8                           ucPsRestrictRegFlg;

    ucCsRestrictRegFlg = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictRegFlg = NAS_MML_GetPsRestrictRegisterFlg();
    ucSimCsRegStatus   = NAS_MML_GetSimCsRegStatus();
    enCurrNetRatType   = NAS_MML_GetCurrNetRatType();

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
     && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
     && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     && (NAS_MML_NET_RAT_TYPE_LTE != enCurrNetRatType)
     && (VOS_FALSE == ucCsRestrictRegFlg)
     && (VOS_TRUE == ucSimCsRegStatus)
     && (VOS_FALSE == ucPsRestrictRegFlg))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }
    return;
}


VOS_VOID NAS_GMM_FreeWasSysInfo(VOS_VOID)
{
    VOS_VOID                           *pAddr = VOS_NULL_PTR;

    if (GMM_MSG_HOLD_FOR_WAS_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_WAS_SYSINFO))
    {
        return;
    }

    /* 清除保留标志 */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_WAS_SYSINFO;

    /* 将保留buffer中所有的消息释放 */
    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo)
    {
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo = VOS_NULL_PTR;
    }

    return;
}


VOS_VOID NAS_GMM_SaveWasSysInfo(
    MMCGMM_SYS_INFO_IND_STRU         *pstSysInfo
)
{
    MMCGMM_SYS_INFO_IND_STRU         *pstHoldSysInfo = VOS_NULL_PTR;

    NAS_GMM_FreeWasSysInfo();

    pstHoldSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_SYS_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstHoldSysInfo)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SaveWasSysInfo:WARNING: Mem alloc fail.");
        return;
    }

    /* 置缓存标志 */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_WAS_SYSINFO;

    /* 保存系统消息 */
    Gmm_MemCpy(pstHoldSysInfo, pstSysInfo, sizeof(MMCGMM_SYS_INFO_IND_STRU));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo = (VOS_UINT32)pstHoldSysInfo;

    return;
}


VOS_UINT32 NAS_GMM_ProcSavedWasSysInfo()
{
    if (GMM_MSG_HOLD_FOR_WAS_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_WAS_SYSINFO))
    {
        return VOS_FALSE;
    }

    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo)
    {
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 Gmm_MsgDistribute_ProcMmcMsg_GmmNull(
    VOS_VOID                           *pRcvMsg                                 /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;        /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8                           ucRst;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                               /* 得到消息头                               */
    ucRst = GMM_TRUE;

    switch ( pstNasMsgHeader->ulMsgName )
    {
        case MMCGMM_START_REQ :
            break;

        case MMCGMM_COVERAGE_LOST_IND :
            break;

        case MMCGMM_MODE_CHANGE_REQ :
            break;

        case MMCGMM_PLMN_SEARCH_INITIATED :
            break;

        case MMCGMM_SYS_INFO_IND :
            break;

        case MMCGMM_GSM_SYS_INFO_IND :
            break;

        case MMCGMM_POWER_OFF_REQ :
            break;

        /* 下面消息认为异常消息 */
        case MMCGMM_DETACH_REQ :
            NAS_GMM_SndMmcDetachCnf();
            ucRst = GMM_FALSE;

            break;

        case MMCGMM_ATTACH_REQ :
            NAS_GMM_SndMmcAttachCnf();
            ucRst = GMM_FALSE;

            break;

        default:
            ucRst = GMM_FALSE;
            break;
    }

    return ucRst;
}




VOS_UINT8 NAS_Gmm_IsValidMmcMsg_GmmTcActive(
    VOS_VOID                           *pRcvMsg                                 /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;        /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8                           ucRst;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                               /* 得到消息头                               */
    ucRst = GMM_TRUE;

    switch ( pstNasMsgHeader->ulMsgName )
    {
        case MMCGMM_START_REQ :
            break;

        case MMCGMM_POWER_OFF_REQ :
            break;

        case MMCGMM_SUSPEND_IND :
            break;

        case MMCGMM_COVERAGE_LOST_IND :
            break;

        case MMCGMM_ATTACH_REQ :
            break;

        /* 否则认为消息非法，不处理 */
        default:
            ucRst = GMM_FALSE;
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_Gmm_IsInvalidMmcMsg_GmmTcActive:WARN:INVALID MSG");
            break;
    }

    return ucRst;
}



VOS_VOID NAS_Gmm_ClearPendingPdpStatus(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearCtx;
    VOS_UINT32                          i;

    pstPsBearCtx = NAS_MML_GetPsBearerCtx();

    /* 根据消息中pdp状态更新MML中全局变量 g_stNasMmlCtx.stNetworkInfo.astPsBearerContext*/
    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        if (VOS_TRUE == pstPsBearCtx[i].ucPsActPending)
        {
            pstPsBearCtx[i].ucPsActPending = VOS_FALSE;
        }

        if (VOS_TRUE == pstPsBearCtx[i].ucPsDeactPending)
        {
            pstPsBearCtx[i].ucPsDeactPending = VOS_FALSE;
        }
    }

    return;
}


VOS_VOID  NAS_GMM_ClearAuthInfo(VOS_VOID)
{
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;

    /* 24.008 4.7.7.2
    The RAND and RES values stored in the mobile station shall be deleted and timer T3316, if running, shall be stopped:
    -   if the mobile station enters the GMM states GMM-DEREGISTERED or GMM-NULL.
    */
    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* 将"RES存在标志 "置为0                    */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* 将"RAND存在标志 "置为0                   */
    Gmm_TimerStop(GMM_TIMER_T3316);

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG == (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG & g_GmmReqCnfMng.ucCnfMask))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
        Gmm_TimerStop(GMM_TIMER_PROTECT);
    }


    return;
}

/*lint -restore */


VOS_UINT32  NAS_GMM_IsNeedProcRelInd(
    RRMM_REL_IND_STRU       *pstRrRelInd
)
{

    /* 如果不是PS域,GMM不需要处理 */
    if (RRC_NAS_PS_DOMAIN != pstRrRelInd->ulCnDomainId)
    {
        return VOS_FALSE;
    }


    /* 如果是在以下几个状态等待est_cnf，并且rel cause为RRC_REL_CAUSE_NAS_DATA_ABSENT，丢弃不处理:
        GMM_REGISTERED_INITIATED:
        GMM_DEREGISTERED_INITIATED:
        GMM_ROUTING_AREA_UPDATING_INITIATED:
        GMM_SERVICE_REQUEST_INITIATED:
        GMM_REGISTERED_IMSI_DETACH_INITIATED:
    */

    /* 如果GMM没在等接入层的est_cnf，需要继续处理 */
    if (GMM_RRC_RRMM_EST_CNF_FLG !=
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        return VOS_TRUE;
    }

    /* 如果rel cause不是RRC_REL_CAUSE_NAS_DATA_ABSENT，需要继续处理 */
    if (RRC_REL_CAUSE_NAS_DATA_ABSENT != pstRrRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    /* 状态不是init状态，需要继续处理 */
    if ( (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_SERVICE_REQUEST_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_REGISTERED_IMSI_DETACH_INITIATED != g_GmmGlobalCtrl.ucState) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucFollowOn
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;

    pstNasMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if (MMCGMM_SUSPEND_IND == pstNasMsgHeader->ulMsgName)
    {
        GMM_LOG_INFO("NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension:Receive MMCGMM_SUSPEND_IND in GMM_GPRS_SUSPENSION state.");
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }
    else if (MMCGMM_POWER_OFF_REQ == pstNasMsgHeader->ulMsgName)
    {
        GMM_BufferMsgDump();
        Gmm_TimerStop(GMM_TIMER_ALL);
        Gmm_TimerStart(GMM_TIMER_1S);
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_RCV;
        g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt = 0;
        return VOS_TRUE;
    }
    else if ( MMCGMM_PLMN_SEARCH_INITIATED == pstNasMsgHeader->ulMsgName )
    {
        /* 进行后面的处理，迁移到搜网状态 */
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }
    else if ( MMCGMM_DETACH_REQ == pstNasMsgHeader->ulMsgName )
    {
        /* 进行后面的处理，迁移到搜网状态 */
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }


    /* 收到MMCGMM_ATTACH_REQ消息，则不进行缓存，而是直接回复Attach成功，
       待重新驻留可用网络后进行Attach */
    else if ( MMCGMM_ATTACH_REQ == pstNasMsgHeader->ulMsgName )
    {
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }

    else if (( MMCGMM_GSM_SYS_INFO_IND == pstNasMsgHeader->ulMsgName )
          || ( MMCGMM_SYS_INFO_IND == pstNasMsgHeader->ulMsgName ) )
    {
        /* 停HO等待系统消息定时器,缓存系统消息 */
        Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);
    }
    else
    {
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID  NAS_GMM_RcvMmcVoiceDomainChangeNotify(
    struct MsgCB                       *pRcvMsg
)
{
    /* 相关协议章节:
    3GPP 24008:
    4.7.5.1 Normal and periodic routing area updating procedure

    The normal routing area updating procedure is initiated:
    ......
    -    when the UE's usage setting or the voice domain preference for E-UTRAN change in the MS;
    ......
    */

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    VOS_INT8                            cVersion;

    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    pstConnStatus   = NAS_MML_GetConnStatus();

    if (cVersion < PS_PTL_VER_R9)
    {
        return;
    }

    /* voice domain和上次发起注册时的相同，不需要再做RAU */
    if (g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq == NAS_MML_GetVoiceDomainPreference())
    {
        return;
    }

    /* 当前已经运行时，重新启动 */
    if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU))
    {
        Gmm_TimerStop(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
        return;
    }

    /* 如果存在CS业务则直接返回 */
    if (VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return;
    }

    /* 如果正在发起CS业务则启动定时器，业务发起失败依靠定时器触发RAU，
       业务发起成功定时器超时时会直接返回 */
    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);

        return;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
    }

    return;
}
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
