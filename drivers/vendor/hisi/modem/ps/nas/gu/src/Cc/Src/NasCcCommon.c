

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "NasCcInclude.h"
#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define    THIS_FILE_ID        PS_FILE_ID_NAS_CC_COMMON_C

/*****************************************************************************
  2 变量定义
*****************************************************************************/
/* 主叫时缓存的Setup或Emergency Setup消息 */
NAS_CC_AIR_MSG_BUF_STRU          g_stNasCcBufferedSetupMsg;

#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID NAS_CC_SndAcpuOmFaultErrLogInd(
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
    pstFaultRptInd = (OM_FAULT_ERR_LOG_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_CC, ulMsgLen);
    if (VOS_NULL_PTR == pstFaultRptInd)
    {
        PS_NAS_LOG(WUEPS_PID_CC, VOS_NULL, PS_LOG_LEVEL_ERROR, "MN_CALL_SndAcpuOmFaultErrLogInd:ERROR: Alloc msg fail.");
        return;
    }

    /* 构造消息结构体 */
    pstFaultRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFaultRptInd->ulSenderPid       = WUEPS_PID_CC;
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
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CC, pstFaultRptInd))
    {
        PS_NAS_LOG(WUEPS_PID_CC, VOS_NULL, PS_LOG_LEVEL_ERROR, "MN_CALL_SndAcpuOmFaultErrLogInd:ERROR: SEND MSG FIAL.");
    }

    return;
}


VOS_UINT32 NAS_CC_IsErrLogNeedRecord(VOS_UINT16 usLevel)
{
    /* Log开关关闭，不需要上报 */
    if (0 == NAS_CC_GetErrlogCtrlFlag())
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 模块log级别usLevel大于用户设置的log上报级别或usLevel无效，不需要上报 */
    if ((NAS_CC_GetErrlogAlmLevel() < usLevel)
     || (NAS_ERR_LOG_CTRL_LEVEL_NULL == usLevel))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_VOID NAS_CC_CsMtCallFailRecord(
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
)
{
    NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU  stCsMtCallFailEvt;
    VOS_UINT32                              ulLength;
    VOS_UINT16                              usLevel;
    VOS_UINT32                              ulIsLogRecord;
    VOS_UINT32                              ulResult;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL);
    ulIsLogRecord = NAS_CC_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU);

    /* 填充CS PAGING失败异常信息 */
    PS_MEM_SET(&stCsMtCallFailEvt, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsMtCallFailEvt.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_CC),
                                      NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stCsMtCallFailEvt.stPositionInfo);

    /* 填写错误原因值 */
    stCsMtCallFailEvt.enCause = enCause;

    /* 将CS MT CALL失败信息发送给ACPU OM模块 */
    NAS_CC_SndAcpuOmFaultErrLogInd(&stCsMtCallFailEvt, ulLength, NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_CC_PutErrLogRingBuf((VOS_CHAR *)&stCsMtCallFailEvt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_MM_SndAcpuOmCsPagingFailInd(): Push buffer error.");
    }

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,
                           WUEPS_PID_CC,
                           (VOS_UINT8 *)&stCsMtCallFailEvt,
                           sizeof(stCsMtCallFailEvt));

    return;
}

#endif


VOS_VOID  NAS_CC_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
)
{
    NAS_CC_LOG_BUFFER_MSG_INFO_STRU    *pstBufferMsg = VOS_NULL_PTR;
    NAS_CC_MSG_QUEUE_STRU              *pstMsgQueue  = VOS_NULL_PTR;

    pstBufferMsg = (NAS_CC_LOG_BUFFER_MSG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_CC,
                             sizeof(NAS_CC_LOG_BUFFER_MSG_INFO_STRU));
    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        NAS_CC_ERR_LOG("NAS_cc_LogBufferQueueMsg:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsgQueue                               = NAS_CC_GetCachMsgBufferAddr();
    pstBufferMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_CC;
    pstBufferMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pstBufferMsg->stMsgHeader.ulLength        = sizeof(NAS_CC_LOG_BUFFER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->stMsgHeader.ulMsgName       = CCOM_LOG_BUFFER_MSG_INFO_IND;
    pstBufferMsg->ulFullFlg                   = ulFullFlg;
    PS_MEM_CPY(&(pstBufferMsg->stMsgQueue), pstMsgQueue, sizeof(pstBufferMsg->stMsgQueue));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(WUEPS_PID_CC, pstBufferMsg);

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
