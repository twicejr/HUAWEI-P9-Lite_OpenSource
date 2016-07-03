
/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "CmmcaMntn.h"
#include "CmmcaCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 修改人: l60609; */
#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_MNTN_C
/*lint +e767 修改人: l60609; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
VOS_UINT8                               g_ucCmmcaParseDbg = VOS_FALSE;

CMMCA_MNTN_CTX_STRU                     stCmmcaMntnCtx;

/*****************************************************************************
  3 外部函数声明
*****************************************************************************/

/*****************************************************************************
  4 函数定义
*****************************************************************************/

VOS_VOID CMMCA_DEBUG_InitCtx(VOS_VOID)
{
    PS_MEM_SET(&stCmmcaMntnCtx, 0x0, sizeof(stCmmcaMntnCtx));

    return ;
}


CMMCA_MNTN_MSG_RECORD_INFO_STRU* CMMCA_DEBUG_GetMsgRecoredInfoAddr(VOS_VOID)
{
    return &stCmmcaMntnCtx.stMsgRecordInfo;
}



VOS_VOID CMMCA_DEBUG_RecordMsgInfo(VOS_UINT32 ulSendPid, VOS_UINT32 ulMsgId)
{
    CMMCA_MNTN_MSG_RECORD_INFO_STRU    *pstMsgInfoAddr;
    VOS_UINT32                          ulIndex;

    pstMsgInfoAddr = CMMCA_DEBUG_GetMsgRecoredInfoAddr();

    ulIndex = pstMsgInfoAddr->ulIndex % CMMCA_DEBUG_MSG_RECORD_NUM;

    pstMsgInfoAddr->astMsgRecord[ulIndex].ulMsgId     = ulMsgId;
    pstMsgInfoAddr->astMsgRecord[ulIndex].ulSendPid   = ulSendPid;
    pstMsgInfoAddr->astMsgRecord[ulIndex].ulRcvTime   = VOS_GetSlice();
    pstMsgInfoAddr->ulIndex++;

    if (0 == pstMsgInfoAddr->ulIndex % CMMCA_DEBUG_MSG_RECORD_NUM)
    {
        CMMCA_DEBUG_TraceMsgRecordInfo();
        PS_MEM_SET(pstMsgInfoAddr, 0x0, sizeof(CMMCA_MNTN_MSG_RECORD_INFO_STRU));
    }

    return;
}



VOS_VOID CMMCA_DEBUG_TraceEvent(VOS_VOID *pMsg)
{

   DIAG_TraceReport(pMsg);
    return;
}


VOS_VOID CMMCA_DEBUG_TraceMsgRecordInfo(VOS_VOID)
{
    CMMCA_MNTN_MSG_RECORD_INFO_STRU    *pstMsgInfoAddr;
    CMMCA_MNTN_MSG_RECORD_IND_STRU      stCmmcaRecordMsgInfo;

    pstMsgInfoAddr = CMMCA_DEBUG_GetMsgRecoredInfoAddr();

    /* 填写消息头 */
    CMMCA_DEBUG_CFG_MSG_HDR(&stCmmcaRecordMsgInfo,
                            WUEPS_PID_CMMCA,
                            WUEPS_PID_CMMCA,
                            sizeof(CMMCA_MNTN_MSG_RECORD_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /*  填写Debug 消息ID */
    stCmmcaRecordMsgInfo.enMsgId = CMMCA_MNTN_MSG_RECORD_IND;

    /* 填写消息内容 */
    PS_MEM_CPY(&(stCmmcaRecordMsgInfo.stMsgRecordInfo), pstMsgInfoAddr, sizeof(CMMCA_MNTN_MSG_RECORD_INFO_STRU));

    /* 发送消息 */
    CMMCA_DEBUG_TraceEvent(&stCmmcaRecordMsgInfo);

    return;
}



VOS_VOID CMMCA_Debug_SetParseDbg(VOS_UINT8 ucParseDbg)
{
    g_ucCmmcaParseDbg = ucParseDbg;
}


VOS_VOID CMMCA_Debug_PrintPdnId(VOS_UINT8 ucPdnId)
{
    if (g_ucCmmcaParseDbg)
    {
        (VOS_VOID)vos_printf("CMMCA_Debug_PrintPdnId: ucPdnId is %d\r\n", ucPdnId);
    }
}


VOS_VOID CMMCA_Debug_PrintPdnType(VOS_UINT8 ucPdnType)
{
    if (g_ucCmmcaParseDbg)
    {
        (VOS_VOID)vos_printf("CMMCA_Debug_PrintPdnType: ucPdnType is %d\r\n", ucPdnType);
    }
}


VOS_VOID CMMCA_Debug_PrintApn(
    VOS_UINT8                          *pucApn,
    VOS_UINT16                          usApnLen
)
{
    if (g_ucCmmcaParseDbg)
    {
        (VOS_VOID)vos_printf("CMMCA_Debug_PrintApn: usApnLen is %d\r\n, apn is %s\r\n", usApnLen, pucApn);
    }
}


VOS_VOID CMMCA_Debug_PrintRatId(
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId,
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId
)
{
    if (g_ucCmmcaParseDbg)
    {
        (VOS_VOID)vos_printf("CMMCA_Debug_PrintRatId: enCmdId is %d\r\n, usDataLen is %d\r\n", enCmdId, enRatId);
    }
}


VOS_VOID CMMCA_Debug_PrintDataIndLenErr(
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId,
    VOS_UINT32                          ulDataLen
)
{
    if (g_ucCmmcaParseDbg)
    {
        (VOS_VOID)vos_printf("CMMCA_Debug_PrintCmdDataLenErr: enCmdId is %d\r\n, usDataLen is %d\r\n", enCmdId, ulDataLen);
    }
}


VOS_VOID CMMCA_Debug_PrintPdnAuthTypeErr(
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId,
    VOS_UINT8                           ucAuthType
)
{
    if (g_ucCmmcaParseDbg)
    {
        (VOS_VOID)vos_printf("CMMCA_Debug_PrintPdnAuthTypeErr: enCmdId is %d\r\n, ucAuthType is %d\r\n", enCmdId, ucAuthType);
    }
}



VOS_VOID  CMMCA_LogBuffFullInd(VOS_VOID)
{
    CMMCA_MNTN_BUFF_FULL_IND_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (CMMCA_MNTN_BUFF_FULL_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_CMMCA,
                              sizeof(CMMCA_MNTN_BUFF_FULL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CMMCA_ERROR_LOG("CMMCA_LogBuffFullInd:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_CMMCA;
    pstMsg->ulReceiverPid   = WUEPS_PID_CMMCA;
    pstMsg->ulLength        = sizeof(CMMCA_MNTN_BUFF_FULL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = CMMCA_MNTN_BUFF_FULL_IND;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_CMMCA, pstMsg);

    return;
}

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif





