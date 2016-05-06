/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdSndCas.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年7月7日
  最近修改   :
  功能描述   : XSD发送给CAS的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsCommonDef.h"
#include  "CnasXsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasCcb.h"
#include  "CnasXsdCtx.h"
#include  "NasMntn.h"
#include  "cas_1x_idlectrl_proc_nas_pif.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_SND_CAS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasStartReq
 功能描述  : 向CAS发送开机请求
 输入参数  : ulResult - 开机结果
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年4月15日
    作    者   : y00245242
    修改内容   : iteration 13开发

  3.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCasStartReq(
    MSCC_XSD_START_REQ_STRU            *pstRcvMsg
)
{
    CNAS_CAS_1X_START_REQ_STRU         *pstStartrReq  = VOS_NULL_PTR;

    /* 分配消息 */
    pstStartrReq = (CNAS_CAS_1X_START_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD,
                      sizeof(CNAS_CAS_1X_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstStartrReq)
    {
        return;
    }

    /* 填充消息 */
    pstStartrReq->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstStartrReq->ulReceiverPid         = UEPS_PID_1XCASM;
    pstStartrReq->enModemId             = pstRcvMsg->enModemId;
    pstStartrReq->enMsgId               = ID_CNAS_CAS_1X_START_REQ;
    pstStartrReq->enUimStatus           = CNAS_CCB_GetCasCardStatus();
    pstStartrReq->ucSuppRatNum          = pstRcvMsg->ucSuppRatNum;

    NAS_MEM_CPY_S(pstStartrReq->aenRatMode,
                  sizeof(pstStartrReq->aenRatMode),
                  pstRcvMsg->aenRatMode,
                  VOS_RATMODE_BUTT * sizeof(VOS_RATMODE_ENUM_UINT32));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStartrReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstStartrReq);

    NAS_TRACE_HIGH("Send Msg!");
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasPowerOffReq
 功能描述  : 向CAS发送关机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCasPowerOffReq(VOS_VOID)
{
    CNAS_CAS_1X_POWER_OFF_REQ_STRU     *pstPowerOffReq  = VOS_NULL_PTR;

    /* 分配消息 */
    pstPowerOffReq = (CNAS_CAS_1X_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD,
                      sizeof(CNAS_CAS_1X_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstPowerOffReq)
    {
        return;
    }

    /* 填充消息 */
    pstPowerOffReq->ulReceiverPid       = UEPS_PID_1XCASM;
    pstPowerOffReq->enMsgId             = ID_CNAS_CAS_1X_POWER_OFF_REQ;
    pstPowerOffReq->usOpId              = 0;
    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPowerOffReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstPowerOffReq);

    NAS_TRACE_HIGH("Send Msg!");
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasSysSyncReq
 功能描述  : 向CAS发送ID_CNAS_CAS_1X_SYSTEM_SYNC_REQ消息
 输入参数  : VOS_UINT32                          ulFreqNum
             CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCasSysSyncReq(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
)
{
    CNAS_CAS_1X_SYSTEM_SYNC_REQ_STRU   *pstSysSyncReq  = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* 分配消息 */
    pstSysSyncReq = (CNAS_CAS_1X_SYSTEM_SYNC_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD,
                      sizeof(CNAS_CAS_1X_SYSTEM_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstSysSyncReq)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstSysSyncReq + VOS_MSG_HEAD_LENGTH,
                  sizeof(CNAS_CAS_1X_SYSTEM_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(CNAS_CAS_1X_SYSTEM_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstSysSyncReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSysSyncReq->ulSenderPid     = UEPS_PID_XSD;
    pstSysSyncReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSysSyncReq->ulReceiverPid   = UEPS_PID_1XCASM;
    pstSysSyncReq->ulLength        = sizeof(CNAS_CAS_1X_SYSTEM_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSysSyncReq->enMsgId         = ID_CNAS_CAS_1X_SYSTEM_SYNC_REQ;
    pstSysSyncReq->usOpId          = 0;

    pstSysSyncReq->ulFreqNum           = ulFreqNum;

    NAS_MEM_SET_S(pstSysSyncReq->astFreqList,
                  sizeof(pstSysSyncReq->astFreqList),
                  0x00,
                  sizeof(CNAS_CAS_1X_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    for (i = 0; i < CNAS_MIN(ulFreqNum, CNAS_CAS_1X_MAX_FREQ_NUM); i++)
    {
        pstSysSyncReq->astFreqList[i].usBandClass = pstFreqList[i].enBandClass;
        pstSysSyncReq->astFreqList[i].usChannel   = pstFreqList[i].usChannel;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysSyncReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysSyncReq);

}


/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasStopSysSyncReq
 功能描述  : 向CAS发送ID_CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCasStopSysSyncReq(VOS_VOID)
{
    CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ_STRU                  *pstStopSysSyncReq  = VOS_NULL_PTR;

    /* 分配消息 */
    pstStopSysSyncReq = (CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD,
                      sizeof(CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstStopSysSyncReq)
    {
        return;
    }

    NAS_MEM_SET_S(pstStopSysSyncReq->aucReserve, sizeof(pstStopSysSyncReq->aucReserve), 0x0, sizeof(VOS_UINT8) * 4);

    /* 填充消息 */
    pstStopSysSyncReq->ulReceiverPid       = UEPS_PID_1XCASM;
    pstStopSysSyncReq->enMsgId             = ID_CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ;
    pstStopSysSyncReq->usOpId              = 0;
    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStopSysSyncReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstStopSysSyncReq);

}


/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCas1xCampSyncedChannelNtf
 功能描述  : 向接入层发送ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCas1xCampSyncedChannelNtf(VOS_VOID)
{
    CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF_STRU               *pst1xCampSyncedChNtf  = VOS_NULL_PTR;

    /* 分配消息 */
    pst1xCampSyncedChNtf = (CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD,
                      sizeof(CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pst1xCampSyncedChNtf)
    {
        return;
    }

    /* 填充消息 */
    pst1xCampSyncedChNtf->ulReceiverPid       = UEPS_PID_1XCASM;
    pst1xCampSyncedChNtf->enMsgId             = ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF;
    pst1xCampSyncedChNtf->usOpId              = 0;

    NAS_MEM_SET_S(pst1xCampSyncedChNtf->aucReserve, sizeof(pst1xCampSyncedChNtf->aucReserve), 0, sizeof(pst1xCampSyncedChNtf->aucReserve));
    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pst1xCampSyncedChNtf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pst1xCampSyncedChNtf);

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasCdmaCsqSetReq
 功能描述  : 向接入层发送ID_CNAS_CAS_1X_1X_SET_SIGNAL_QUALITY_REQ消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00312079
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

  3.日    期   : 2015年10月16日
    作    者   : m00312079
    修改内容   : DTS2015101505057:添加ec/Io的上报门限

*****************************************************************************/
VOS_UINT32 CNAS_XSD_SndCasCdmaCsqSetReq(
    VOS_UINT8                                               ucRssiRptThreshold,
    VOS_UINT8                                               ucEcIoRptThreshold,
    VOS_UINT8                                               ucTimeInterval
)
{
    CNAS_CAS_1X_SET_SIGNAL_QUALITY_REQ_STRU                *pstSetCdmaCsqReq  = VOS_NULL_PTR;

    /* 分配消息 */
    pstSetCdmaCsqReq = (CNAS_CAS_1X_SET_SIGNAL_QUALITY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD,
                      sizeof(CNAS_CAS_1X_SET_SIGNAL_QUALITY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSetCdmaCsqReq)
    {
        return VOS_FALSE;
    }

    /* 填充消息 */
    pstSetCdmaCsqReq->ulReceiverPid       = UEPS_PID_1XCASM;
    pstSetCdmaCsqReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstSetCdmaCsqReq->ulSenderPid         = UEPS_PID_XSD;
    pstSetCdmaCsqReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstSetCdmaCsqReq->enMsgId             = ID_CNAS_CAS_1X_SET_SIGNAL_QUALITY_REQ;
    pstSetCdmaCsqReq->usOpId              = 0;
    pstSetCdmaCsqReq->ucRptRssiThreshold  = ucRssiRptThreshold;
    pstSetCdmaCsqReq->ucRptEcIoThreshold  = ucEcIoRptThreshold;
    pstSetCdmaCsqReq->ucTimeInterval      = ucTimeInterval;

    NAS_MEM_SET_S(pstSetCdmaCsqReq->aucReserve, sizeof(pstSetCdmaCsqReq->aucReserve), 0, sizeof(pstSetCdmaCsqReq->aucReserve));
    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSetCdmaCsqReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSetCdmaCsqReq);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasCFreqLockNtf
 功能描述  : 向接入层发送CNAS_CAS_1X_FREQ_LOCK_NTF_STRU消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : m00312079
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_UINT32 CNAS_XSD_SndCasCFreqLockNtf(MSCC_XSD_CFREQ_LOCK_NTF_STRU   *pstCFreqLockNtf)
{
    CNAS_CAS_1X_FREQ_LOCK_NTF_STRU     *pstCnasCasCFreqLockNtf   = VOS_NULL_PTR;

    pstCnasCasCFreqLockNtf =
            (CNAS_CAS_1X_FREQ_LOCK_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                                                                        sizeof(CNAS_CAS_1X_FREQ_LOCK_NTF_STRU));

    if (VOS_NULL_PTR == pstCnasCasCFreqLockNtf)
    {
        return VOS_FALSE;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstCnasCasCFreqLockNtf + VOS_MSG_HEAD_LENGTH),
                  (sizeof(CNAS_CAS_1X_FREQ_LOCK_NTF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (sizeof(CNAS_CAS_1X_FREQ_LOCK_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstCnasCasCFreqLockNtf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCnasCasCFreqLockNtf->ulSenderPid     = UEPS_PID_XSD;
    pstCnasCasCFreqLockNtf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCnasCasCFreqLockNtf->ulReceiverPid   = UEPS_PID_1XCASM;
    pstCnasCasCFreqLockNtf->enMsgId        = ID_CNAS_CAS_1X_FREQ_LOCK_NTF;
    pstCnasCasCFreqLockNtf->usOpId         = 0;
    pstCnasCasCFreqLockNtf->enMode         = pstCFreqLockNtf->enFreqLockMode;
    pstCnasCasCFreqLockNtf->usBandClass    = pstCFreqLockNtf->usCdmaBandClass;
    pstCnasCasCFreqLockNtf->usFreq         = pstCFreqLockNtf->usCdmaFreq;
    pstCnasCasCFreqLockNtf->usPilotPn      = pstCFreqLockNtf->usCdmaPn;
    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCnasCasCFreqLockNtf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCnasCasCFreqLockNtf);

    return VOS_TRUE;
}
#if 0
/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasNegativeSystemQueryRsp
 功能描述  : 向接入层发送ID_CNAS_CAS_1X_NEGATIVE_SYSTEM_QUERY_RSP消息
 输入参数  : pstCurrSystemId -- 当前系统ID
             pstNegativeFreqList -- negative系统频点列表
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月9日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_SndCasNegativeSystemQueryRsp(
    CNAS_CAS_1X_SYSTEM_IDENTITY_STRU   *pstCurrSystemId,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU    *pstNegativeFreqList
)
{
    CNAS_CAS_1X_NEGATIVE_SYSTEM_QUERY_RSP_STRU             *pstQueryRsp   = VOS_NULL_PTR;

    pstQueryRsp = (CNAS_CAS_1X_NEGATIVE_SYSTEM_QUERY_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                                                                sizeof(CNAS_CAS_1X_NEGATIVE_SYSTEM_QUERY_RSP_STRU));

    if (VOS_NULL_PTR == pstQueryRsp)
    {
        return VOS_FALSE;
    }

    NAS_MEM_SET_S(pstQueryRsp, 0x00, sizeof(CNAS_CAS_1X_NEGATIVE_SYSTEM_QUERY_RSP_STRU));

    /* 填写消息头部信息 */
    pstQueryRsp->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstQueryRsp->ulSenderPid         = UEPS_PID_XSD;
    pstQueryRsp->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstQueryRsp->ulReceiverPid       = UEPS_PID_1XCASM;
    pstQueryRsp->ulLength            = sizeof(CNAS_CAS_1X_NEGATIVE_SYSTEM_QUERY_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstQueryRsp->enMsgId             = ID_CNAS_CAS_1X_NEGATIVE_SYSTEM_QUERY_RSP;
    pstQueryRsp->usOpId              = 0;

    pstQueryRsp->stCurrSysId          = *pstCurrSystemId;
    pstQueryRsp->ulNegFreqNum        = pstNegativeFreqList->ulNum;

    PS_MEM_CPY(&pstQueryRsp->astNegFreqList[0],
               &pstNegativeFreqList->astFreqInfo[0],
               pstNegativeFreqList->ulNum * sizeof (CNAS_CAS_1X_FREQENCY_CHANNEL_STRU));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstQueryRsp);
    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_XSD, pstQueryRsp);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasSysCfgReq
 功能描述  : 向接入层发送ID_CNAS_CAS_1X_ SYS_CFG消息
 输入参数  : pstRcvMsg -- 收到的消息指针

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCasSysCfgReq(
    MSCC_XSD_SYS_CFG_REQ_STRU          *pstRcvMsg
)
{
    CNAS_CAS_1X_SYS_CFG_REQ_STRU       *pstSysCfgReqMsg  = VOS_NULL_PTR;

    /* 分配消息 */
    pstSysCfgReqMsg = (CNAS_CAS_1X_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD,
                      sizeof(CNAS_CAS_1X_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstSysCfgReqMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstSysCfgReqMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(CNAS_CAS_1X_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  sizeof(CNAS_CAS_1X_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstSysCfgReqMsg->ulReceiverPid       = UEPS_PID_1XCASM;
    pstSysCfgReqMsg->enMsgId             = ID_CNAS_CAS_1X_SYS_CFG_REQ;
    pstSysCfgReqMsg->usOpId              = pstRcvMsg->usOpId;

    pstSysCfgReqMsg->ucSuppRatNum        = pstRcvMsg->ucSuppRatNum;

    NAS_MEM_CPY_S(pstSysCfgReqMsg->aenRatMode,
                  sizeof(pstSysCfgReqMsg->aenRatMode),
                  pstRcvMsg->aenRatMode,
                  VOS_RATMODE_BUTT * sizeof(VOS_RATMODE_ENUM_UINT32));

    NAS_MEM_CPY_S(&(pstSysCfgReqMsg->stSupportBand),
                  sizeof(pstSysCfgReqMsg->stSupportBand),
                  &(pstRcvMsg->stCdmaBand),
                  sizeof(CNAS_CAS_1X_SUPPORT_BAND_STRU));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysCfgReqMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysCfgReqMsg);

}

/*****************************************************************************
Function Name   :   CNAS_XSD_SndCasOocReq
Description     :   The function is used to send OOC Request to CAS.
Input parameters:   None
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-04
        Author  :   a00295761
        Modify content :    Create

    2) 日    期 : 2015年08月20日
       作    者 : t00323010
       修改内容 : DTS2015081904804 clear coverity
*****************************************************************************/

VOS_VOID CNAS_XSD_SndCasSuspendReq(VOS_VOID)
{
    CNAS_CAS_1X_SUSPEND_REQ_STRU            *pstCnasCasSuspendReq   = VOS_NULL_PTR;

    pstCnasCasSuspendReq = (CNAS_CAS_1X_SUSPEND_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                                                                sizeof(CNAS_CAS_1X_SUSPEND_REQ_STRU));

    if (VOS_NULL_PTR == pstCnasCasSuspendReq)
    {
        return;
    }

    NAS_MEM_SET_S(pstCnasCasSuspendReq, sizeof(CNAS_CAS_1X_SUSPEND_REQ_STRU), 0x00, sizeof(CNAS_CAS_1X_SUSPEND_REQ_STRU));

    /* Construct the OOC Request */
    pstCnasCasSuspendReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstCnasCasSuspendReq->ulSenderPid         = UEPS_PID_XSD;
    pstCnasCasSuspendReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstCnasCasSuspendReq->ulReceiverPid       = UEPS_PID_1XCASM;
    pstCnasCasSuspendReq->ulLength            = sizeof(CNAS_CAS_1X_SUSPEND_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCnasCasSuspendReq->enMsgId             = ID_CNAS_CAS_1X_SUSPEND_REQ;
    pstCnasCasSuspendReq->usOpId              = 0;
    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCnasCasSuspendReq);

    /* Send the message to CAS */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCnasCasSuspendReq);

    return;
}
/*lint -restore*/

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndRrmRegisterInd
 功能描述  : NO RF时，向RRM发送ID_PS_RRM_REGISTER_IND消息
 输入参数  : enTaskType         :注册任务类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月19日
    作    者   : h00313353
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
)
{
    PS_RRM_REGISTER_IND_STRU           *pstMsg  = VOS_NULL_PTR;

    pstMsg = (PS_RRM_REGISTER_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_XSD,
                                                  sizeof(PS_RRM_REGISTER_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_REGISTER_IND;
    pstMsg->enModemId                       = CNAS_CCB_GetCdmaModeModemId();
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_1X;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndRrmDeRegisterInd
 功能描述  : 收到RF可用消息时，向RRM发送ID_PS_RRM_DEREGISTER_IND消息
 输入参数  : enTaskType         :注册任务类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月19日
    作    者   : h00313353
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndRrmDeRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
)
{
    PS_RRM_DEREGISTER_IND_STRU         *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_DEREGISTER_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_XSD,
                                                  sizeof(PS_RRM_DEREGISTER_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_XSD;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_DEREGISTER_IND;
    pstMsg->enModemId                       = CNAS_CCB_GetCdmaModeModemId();
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_1X;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasBeginSessionNotify
 功能描述  : XSD通知CAS开始Session通知
 输入参数  : enSessionType:XSD当前session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00133353
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCasBeginSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
)
{
    CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU                     *pstBeginSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstBeginSessionNotify = (CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    /* 构造消息结构体 */
    pstBeginSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulSenderPid      = UEPS_PID_XSD;
    pstBeginSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulReceiverPid    = UEPS_PID_1XCASM;
    pstBeginSessionNotify->ulLength         = ulMsgLength;
    pstBeginSessionNotify->enMsgId          = ID_CNAS_CAS_1X_SESSION_BEGIN_NTF;
    pstBeginSessionNotify->enSessionType    = enSessionType;
    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstBeginSessionNotify);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstBeginSessionNotify);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasEndSessionNotify
 功能描述  : XSD通知CAS结束Session通知
 输入参数  : enSessionType:XSD当前session类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00133353
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCasEndSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
)
{
    CNAS_CAS_1X_SESSION_END_NTF_STRU                       *pstEndSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_1X_SESSION_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEndSessionNotify = (CNAS_CAS_1X_SESSION_END_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    /* 构造消息结构体 */
    pstEndSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulSenderPid      = UEPS_PID_XSD;
    pstEndSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulReceiverPid    = UEPS_PID_1XCASM;
    pstEndSessionNotify->ulLength         = ulMsgLength;
    pstEndSessionNotify->enMsgId          = ID_CNAS_CAS_1X_SESSION_END_NTF;
    pstEndSessionNotify->enSessionType    = enSessionType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstEndSessionNotify);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstEndSessionNotify);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_SndCasAvailableCampQueryCnf
 功能描述  : 给CAS发送查询结果
 输入参数  : usOpId ----- opid
             ucIsAvailableCamp  ----- 能否驻留标记，0表示能够驻留，其他值表示不能驻留
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月30日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_SndCasAvailableCampQueryCnf(
    VOS_UINT16                          usOpId,
    PS_BOOL_ENUM_UINT8                  enIsCurSysCanCamp
)
{
    CNAS_CAS_1X_AVAILABLE_CAMP_QUERY_CNF_STRU              *pstQueryCnf = VOS_NULL_PTR;

    pstQueryCnf = (CNAS_CAS_1X_AVAILABLE_CAMP_QUERY_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD,
                      sizeof(CNAS_CAS_1X_AVAILABLE_CAMP_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstQueryCnf)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstQueryCnf + VOS_MSG_HEAD_LENGTH,
                  sizeof(CNAS_CAS_1X_AVAILABLE_CAMP_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  sizeof(CNAS_CAS_1X_AVAILABLE_CAMP_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息 */
    pstQueryCnf->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstQueryCnf->ulSenderPid         = UEPS_PID_XSD;
    pstQueryCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstQueryCnf->ulReceiverPid       = UEPS_PID_1XCASM;
    pstQueryCnf->enMsgId             = ID_CNAS_CAS_1X_AVAILABLE_CAMP_QUERY_CNF;
    pstQueryCnf->ulLength            = sizeof(CNAS_CAS_1X_AVAILABLE_CAMP_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstQueryCnf->usOpId              = usOpId;
    pstQueryCnf->enAvailableCampFlag = enIsCurSysCanCamp;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstQueryCnf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstQueryCnf);
    return;
}

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

