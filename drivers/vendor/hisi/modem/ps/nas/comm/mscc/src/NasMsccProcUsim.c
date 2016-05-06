

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccProcUsim.h"
#include "NasUsimmApi.h"
#include "NasMsccCtx.h"
#include "NasComm.h"
#include "NasMsccMlplMsplApi.h"
#include "NVIM_Interface.h"
#include "NasMsccComFunc.h"
#include "NasMsccMntn.h"
#include "NasMsccProcNvim.h"
#ifdef DMT
#include "tpl_nastimermsg.h"
#endif

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_PROC_USIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT8                               g_aucDefaultMlplBuffer[] =
{
    0x00, 0x39, 0x01, 0x00, 0x08, 0x01, 0x05, 0x07, 0x46, 0x0F, 0xFF, 0x01, 0x01, 0x20, 0x64, 0xF0,
    0xFF, 0x00, 0x01, 0x07, 0x45, 0x5F, 0xFF, 0x01, 0x01, 0x20, 0x54, 0xF5, 0xFF, 0x00, 0x01, 0x00,
    0x02, 0x07, 0x45, 0x0F, 0xFF, 0x01, 0x01, 0x20, 0x54, 0xF0, 0xFF, 0x00, 0x03, 0x07, 0x44, 0x0F,
    0xFF, 0x01, 0x01, 0x20, 0x44, 0xF0, 0xFF, 0x00, 0x03
};

VOS_UINT8                               g_aucDefaultMsplBuffer[] =
{
    0x00, 0x24, 0x01, 0x00, 0x08, 0x03, 0x01, 0x04, 0x07, 0x1F, 0x00, 0x0E, 0x00, 0x7D, 0x00, 0x1E,
    0x80, 0x20, 0x30, 0x61, 0xF0, 0x28, 0xF8, 0x07, 0xDC, 0x06, 0x08, 0x0C, 0x3E, 0x05, 0x1F, 0x00,
    0x0A, 0x00, 0x7D, 0xC0
};



VOS_VOID NAS_MSCC_ReadUsimmFile(
    USIMM_CARDAPP_ENUM_UINT32                               enCardApp,
    USIMM_DEF_FILEID_ENUM_UINT32                            enFileId

)
{
    NAS_USIMM_GETFILE_INFO_STRU                             stGetFileInfo;

    PS_MEM_SET(&stGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    NAS_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      enCardApp,
                                      (VOS_UINT16)(enFileId),
                                      0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(UEPS_PID_MSCC, 0, &stGetFileInfo);
}



VOS_VOID NAS_MSCC_ReadAndParseMlplMsplNvim(VOS_VOID)
{
    NAS_MSCC_NVIM_MLPL_MSPL_STRU                           *pstNvimMlplMspl = VOS_NULL_PTR;
    NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32                    enMlplParseRslt;
    NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32                    enMsplParseRslt;

    pstNvimMlplMspl = (NAS_MSCC_NVIM_MLPL_MSPL_STRU *)PS_MEM_ALLOC(
                                        UEPS_PID_MSCC, sizeof(NAS_MSCC_NVIM_MLPL_MSPL_STRU));

    if (VOS_NULL_PTR == pstNvimMlplMspl)
    {
        return;
    }

    PS_MEM_SET(pstNvimMlplMspl, 0, sizeof(NAS_MSCC_NVIM_MLPL_MSPL_STRU));

    if (VOS_TRUE == NAS_MSCC_ReadMlplMsplNvim(pstNvimMlplMspl))
    {
        if (VOS_TRUE == pstNvimMlplMspl->ucMlplMsplActiveFlag)
        {
            enMlplParseRslt = NAS_MSCC_ParseMlplFile(pstNvimMlplMspl->aucMlplBuf,
                                                     pstNvimMlplMspl->usMlplBufSize);

            NAS_MSCC_MNTN_LogMlplParseRslt(NAS_MSCC_MLPL_MSPL_SOURCE_NV, enMlplParseRslt);

            if (NAS_MSCC_PARSE_MLPL_RSLT_SUCCESS == enMlplParseRslt)
            {
                NAS_MSCC_SetMlplValidFlag(VOS_TRUE);
            }
            else
            {
                NAS_MSCC_SetMlplValidFlag(VOS_FALSE);

                PS_MEM_FREE(UEPS_PID_MSCC, pstNvimMlplMspl);

                return;
            }

            enMsplParseRslt = NAS_MSCC_ParseMsplFile(pstNvimMlplMspl->aucMsplBuf,
                                                     pstNvimMlplMspl->usMsplBufSize);

            NAS_MSCC_MNTN_LogMsplParseRslt(NAS_MSCC_MLPL_MSPL_SOURCE_NV, enMsplParseRslt);

            if (NAS_MSCC_PARSE_MSPL_RSLT_SUCCESS == enMsplParseRslt)
            {
                NAS_MSCC_SetMsplValidFlag(VOS_TRUE);
            }
            else
            {
                NAS_MSCC_SetMsplValidFlag(VOS_FALSE);
            }
        }
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstNvimMlplMspl);
}



VOS_VOID NAS_MSCC_ParseDefaultMlplMspl(VOS_VOID)
{
    VOS_UINT16                                              usBuffersize;
    NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32                    enMlplParseRslt;
    NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32                    enMsplParseRslt;

    usBuffersize = (sizeof(g_aucDefaultMlplBuffer)) / (sizeof(VOS_UINT8));

    enMlplParseRslt = NAS_MSCC_ParseMlplFile(g_aucDefaultMlplBuffer, usBuffersize);

    NAS_MSCC_MNTN_LogMlplParseRslt(NAS_MSCC_MLPL_MSPL_SOURCE_DEFAULT, enMlplParseRslt);

    if (NAS_MSCC_PARSE_MLPL_RSLT_SUCCESS == enMlplParseRslt)
    {
        NAS_MSCC_SetMlplValidFlag(VOS_TRUE);
    }
    else
    {
        NAS_MSCC_SetMlplValidFlag(VOS_FALSE);

        return;
    }

    usBuffersize = (sizeof(g_aucDefaultMsplBuffer)) / (sizeof(VOS_UINT8));

    enMsplParseRslt = NAS_MSCC_ParseMsplFile(g_aucDefaultMsplBuffer, usBuffersize);

    NAS_MSCC_MNTN_LogMsplParseRslt(NAS_MSCC_MLPL_MSPL_SOURCE_DEFAULT, enMsplParseRslt);

    if (NAS_MSCC_PARSE_MSPL_RSLT_SUCCESS == enMsplParseRslt)
    {
        NAS_MSCC_SetMsplValidFlag(VOS_TRUE);
    }
    else
    {
        NAS_MSCC_SetMsplValidFlag(VOS_FALSE);
    }
}



VOS_VOID  NAS_MSCC_RcvUsimmReadMlplFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
)
{
    NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32                    enMlplParseRslt;

#ifdef DMT
    /* DMT测试，发出读卡超时的消息 */
    if (NAS_MSCC_CARD_READ_STUB_TYPE_MSPL_NO_REPLY == genCardReadStubTypeForDmt)
    {
        NAS_MSCC_SendCardReadTimerExpireMsgForDmt();

        return;
    }
#endif

    /* Read file fail */
    if (VOS_OK != pstUsimmReadCnfMsg->stCmdResult.ulResult)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvUsimmReadMlplFileCnf:ERROR: Read CSIM MLPL FAIL");

        return;
    }

    enMlplParseRslt = NAS_MSCC_ParseMlplFile(pstUsimmReadCnfMsg->aucEf,
                                             pstUsimmReadCnfMsg->usEfLen);

    NAS_MSCC_MNTN_LogMlplParseRslt(NAS_MSCC_MLPL_MSPL_SOURCE_CARD, enMlplParseRslt);

    if (NAS_MSCC_PARSE_MLPL_RSLT_SUCCESS == enMlplParseRslt)
    {
        NAS_MSCC_SetMlplValidFlag(VOS_TRUE);
    }
}



VOS_VOID  NAS_MSCC_RcvUsimmReadMsplFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
)
{
    NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32                    enMsplParseRslt;

#ifdef DMT
    /* DMT测试，发出读卡超时的消息 */
    if (NAS_MSCC_CARD_READ_STUB_TYPE_MLPL_NO_REPLY == genCardReadStubTypeForDmt)
    {
        NAS_MSCC_SendCardReadTimerExpireMsgForDmt();

        return;
    }
#endif

    /* Read file fail */
    if (VOS_OK != pstUsimmReadCnfMsg->stCmdResult.ulResult)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvUsimmReadMsplFileCnf:ERROR: Read CSIM MSPL FAIL");

        return;
    }

    enMsplParseRslt = NAS_MSCC_ParseMsplFile(pstUsimmReadCnfMsg->aucEf, pstUsimmReadCnfMsg->usEfLen);

    NAS_MSCC_MNTN_LogMsplParseRslt(NAS_MSCC_MLPL_MSPL_SOURCE_CARD, enMsplParseRslt);

    if (NAS_MSCC_PARSE_MSPL_RSLT_SUCCESS == enMsplParseRslt)
    {
        NAS_MSCC_SetMsplValidFlag(VOS_TRUE);
    }
}



VOS_VOID  NAS_MSCC_RcvUsimmReadFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg,
    USIMM_DEF_FILEID_ENUM_UINT32                            enEfId
)
{
    switch (enEfId)
    {
        case USIMM_TELE_EFMLPL_ID:
            NAS_MSCC_RcvUsimmReadMlplFileCnf(pstUsimmReadCnfMsg);
            break;

        case USIMM_TELE_EFMSPL_ID:
            NAS_MSCC_RcvUsimmReadMsplFileCnf(pstUsimmReadCnfMsg);
            break;

        default:
            NAS_WARNING_LOG(UEPS_FID_MSCC, "NAS_MSCC_RcvUsimmReadFileCnf:WARNING: File Id Abnormal");
            break;
    }
}


#ifdef DMT
/*****************************************************************************
Function Name   :   NAS_MSCC_SendCardReadTimerExpireMsgForDmt
Description     :   发送读卡定时器超时，用于DTM测试
Input parameters:   None
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-28
        Author  :   y00174758
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SendCardReadTimerExpireMsgForDmt(VOS_VOID)
{
    NAS_TIMER_MSG_STRU                 *pstMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    ulLen = sizeof(NAS_TIMER_MSG_STRU);

    pstMsg = (NAS_TIMER_MSG_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = VOS_PID_TIMER;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = UEPS_PID_MSCC;
    pstMsg->ulLength                = sizeof(NAS_TIMER_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucType                  = 0;
    pstMsg->usRsv                   = 0;
    pstMsg->ulTimerId               = TI_NAS_MSCC_WAIT_CARD_READ_CNF;

    PS_MEM_SET(&pstMsg->stTimerMsgData, 0x0, sizeof(pstMsg->stTimerMsgData));

    pstMsg->stTimerMsgData.ulPara   = 0;

    VOS_SendMsg(VOS_PID_TIMER, pstMsg);
}
#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



