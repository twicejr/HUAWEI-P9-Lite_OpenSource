/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcAtMsg.c
  Description     : 该C文件给出了IMSA模块处理AT命令的实现
  History           :
     1.leili 00132387      2013-10-12  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "ImsaProcAtMsg.h"
#include    "ImsaEntity.h"
#include    "ImsaPublic.h"
#include    "ImsaServiceManagement.h"
#include    "ImsaConnManagement.h"
#include    "ImsaImsAdaption.h"
#include    "ImsaProcOmMsg.h"
#include    "omnvinterface.h"
#include    "SysNvId.h"
/*lint -e767*/
#define    THIS_FILE_ID    PS_FILE_ID_IMSAPROCOMMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
#if (FEATURE_ON == FEATURE_PTM)

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/


/*****************************************************************************
 函 数 名  : IMSA_RcvAcpuOmErrLogCtrlInd
 功能描述  : IMSA处理Acpu om发来的ERROR LOG控制指示
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月04日
    作    者   : w00209181
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID IMSA_RcvAcpuOmErrLogCtrlInd
(
    VOS_VOID                           *pMsg
)
{
    OM_ERROR_LOG_CTRL_IND_STRU         *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (OM_ERROR_LOG_CTRL_IND_STRU*)pMsg;

    /* 更新ERRLOG控制标识 */
    if ((VOS_FALSE != pstRcvMsg->ucAlmStatus)
     && (VOS_TRUE  != pstRcvMsg->ucAlmStatus))
    {
        return;
    }

    IMSA_SetErrlogCtrlFlag(pstRcvMsg->ucAlmStatus);

    if ((pstRcvMsg->ucAlmLevel >= IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (pstRcvMsg->ucAlmLevel <= IMSA_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        IMSA_SetErrlogAlmLevel(pstRcvMsg->ucAlmLevel);
    }

    return;
}
/*****************************************************************************
 函 数 名  : IMSA_ReadErrlogCtrlInfoNvim
 功能描述  : 根据NV:en_NV_Item_ErrLogCtrlInfo初始化ErrlogInfo
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月13日
    作    者   : w00209181
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID IMSA_ReadErrlogCtrlInfoNvim(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    NV_ID_ERR_LOG_CTRL_INFO_STRU        stErrorLogCtrlInfo;

    IMSA_MEM_SET_S( &stErrorLogCtrlInfo,
                    sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU),
                    0x00,
                    sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));

    ulResult = IMSA_NV_Read(en_NV_Item_ErrLogCtrlInfo,
                           &stErrorLogCtrlInfo,
                           sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));

    if (ulResult == VOS_OK)
    {
        IMSA_SetErrlogCtrlFlag(stErrorLogCtrlInfo.ucAlmStatus);
        IMSA_SetErrlogAlmLevel(stErrorLogCtrlInfo.ucAlmLevel);
    }
    else
    {
        IMSA_SetErrlogCtrlFlag(VOS_FALSE);
        IMSA_SetErrlogAlmLevel(IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL);
        IMSA_ERR_LOG("IMSA_ReadErrlogCtrlInfoNvim:read en_NV_Item_ErrLogCtrlInfo failed");
        TLPS_PRINT2LAYER_ERROR(IMSA_ReadErrlogCtrlInfoNvim_ENUM, LNAS_FAIL);
    }

    return;
}

/*****************************************************************************
 函 数 名  : IMSA_SndAcpuOmErrLogRptCnf
 功能描述  : 发送ID_OM_ERR_LOG_REPORT_CNF消息给ACPU OM
 输入参数  : pbuffer:数据内容
             ulBufUseLen:数据长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月05日
    作    者   : W00209181
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID IMSA_SndAcpuOmErrLogRptCnf
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
)
{
    IMSA_ERR_LOG_REPORT_CNF_STRU         *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* 上报的消息总长度 */
    ulMsgLen  = (sizeof(IMSA_ERR_LOG_REPORT_CNF_STRU) - 4) + ulBufUseLen;

    /* 消息空间申请 */
    pstQryCnf = (IMSA_ERR_LOG_REPORT_CNF_STRU *)IMSA_ALLOC_MSG(ulMsgLen);
    if (VOS_NULL_PTR == pstQryCnf)
    {
        IMSA_ERR_LOG("IMSA_SndAcpuOmErrLogRptCnf: alloc msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndAcpuOmErrLogRptCnf_ENUM, LNAS_NULL_PTR);
        return;
    }

    pstQryCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQryCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstQryCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstQryCnf->ulSenderPid      = PS_PID_IMSA;
    pstQryCnf->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstQryCnf->ulMsgType        = IMSA_ERR_LOG_MSG_ERR_REPORT;
    pstQryCnf->ulMsgSN          = 0;
    pstQryCnf->ulRptlen         = ulBufUseLen;

    /* buffer不为空时，len也是不会为空的 */
    if (VOS_NULL_PTR != pbuffer)
    {
        IMSA_MEM_CPY_S(pstQryCnf->aucContent, ulBufUseLen, pbuffer, ulBufUseLen);
    }

    IMSA_SND_MSG(pstQryCnf);

    return;

}

/*****************************************************************************
 函 数 名  : IMSA_RcvAcpuOmErrLogRptReq
 功能描述  : IMSA处理Acpu om发来的ERROR LOG故障上报请求
 输入参数  : pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月04日
    作    者   : W00209181
    修改内容   : 商用ErrLog上报及工程模式扩展目新增函数
*****************************************************************************/
VOS_VOID IMSA_RcvAcpuOmErrLogRptReq
(
    VOS_VOID                           *pMsg
)
{
    VOS_CHAR                           *pbuffer   = VOS_NULL_PTR;
    VOS_UINT32                          ulBufUseLen;
    VOS_UINT32                          ulRealLen;
    VOS_UINT32                          ulTotalLen;
    IMSA_ERR_LOG_MNTN_EVENT_STRU        stNasErrLogMntnEvent;

    /* 查询一下RING BUFFER中有多少数据，以便分配内存 */
    ulBufUseLen = IMSA_GetErrLogRingBufferUseBytes();
    ulTotalLen = ulBufUseLen + sizeof(IMSA_ERR_LOG_MNTN_EVENT_STRU);

    pbuffer = (VOS_CHAR *)IMSA_MEM_ALLOC(ulTotalLen);
    if (VOS_NULL_PTR == pbuffer)
    {
        /* 发送ID_OM_ERR_LOG_REPORT_CNF内容为空的消息给OM */
        IMSA_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        return;
    }

    IMSA_MEM_SET_S(pbuffer, ulTotalLen, 0, ulTotalLen);

    /* 获取RING BUFFER的内容 */
    ulRealLen = IMSA_GetErrLogRingBufContent(pbuffer, ulBufUseLen);
    if (ulRealLen != ulBufUseLen)
    {
        /* 发送ID_OM_ERR_LOG_REPORT_CNF内容为空的消息给OM */
        IMSA_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        IMSA_MEM_FREE(pbuffer);
        return;
    }

    /* 将缓冲区溢出次数信息追加在RingBuf后面 */
    IMSA_WRITE_ERRLOG_HEADER_INFO(&stNasErrLogMntnEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_MNTN,
                                  IMSA_ERR_LOG_CTRL_LEVEL_MAJOR,
                                  VOS_GetSlice(),
                                  (sizeof(IMSA_ERR_LOG_MNTN_EVENT_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stNasErrLogMntnEvent.ulCount = IMSA_GetErrlogOverflowCnt();

    IMSA_MEM_CPY_S( pbuffer + ulBufUseLen,
                    sizeof(stNasErrLogMntnEvent),
                    &stNasErrLogMntnEvent,
                    sizeof(stNasErrLogMntnEvent));

    /* 获取完了后需要将RINGBUFFER清空 */
    IMSA_CleanErrLogRingBuf();

    /* 重置溢出计数 */
    IMSA_SetErrlogOverflowCnt(0);

    /* 可维可测BUF溢出的勾包 */
    /*NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_MNTN,
                           UEPS_PID_MTA,
                           (VOS_UINT8 *)&stNasErrLogMntnEvent,
                           sizeof(stNasErrLogMntnEvent));*/

    /* 发送ID_OM_ERR_LOG_REPORT_CNF消息给ACPU OM */
    IMSA_SndAcpuOmErrLogRptCnf(pbuffer, ulTotalLen);

    IMSA_MEM_FREE(pbuffer);

    return;
}

#endif
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcAtMsg.c */





