/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSndCas.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年7月7日
  最近修改   :
  功能描述   : HSD发送给CAS的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsCommonDef.h"
#include  "CnasHsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasCcb.h"
#include  "CnasHsdCtx.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"
#include  "CnasHsdSysAcqStrategy.h"
#include  "hsd_mscc_pif.h"
#include  "NasMntn.h"
#include  "cas_hrpd_routeupdate_nas_pif.h"
#include  "CnasHsdAvoidStrategy.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_CAS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasStartReq
 功能描述  : 向CAS发送开机请求
 输入参数  : pstMsg - 开机接入技术
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

  2.日    期   : 2015年4月15日
    作    者   : y00245242
    修改内容   : iteration 13开发

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasStartReq(MSCC_HSD_START_REQ_STRU *pstMsg)
{
    CNAS_CAS_HRPD_START_REQ_STRU       *pstStartrReq;
    VOS_UINT32                          i;

    /* 分配消息 */
    pstStartrReq = (CNAS_CAS_HRPD_START_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,  sizeof(CNAS_CAS_HRPD_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstStartrReq)
    {
        return;
    }

    /* 填充消息 */
    pstStartrReq->ulReceiverPid         = UEPS_PID_HALMP;
    pstStartrReq->enMsgId               = ID_CNAS_CAS_HRPD_START_REQ;
    pstStartrReq->usOpId                = 0;
    pstStartrReq->enModemId             = pstMsg->enModemId;
    pstStartrReq->ucSuppRatNum          = pstMsg->ucSuppRatNum;

    for (i = 0; i < (sizeof(pstStartrReq->aenRatMode)/sizeof(pstStartrReq->aenRatMode[0])); i++)
    {
        pstStartrReq->aenRatMode[i] = VOS_RATMODE_BUTT;
    }

    for (i = 0; i < pstStartrReq->ucSuppRatNum; i++)
    {
        pstStartrReq->aenRatMode[i] = pstMsg->aenRatMode[i];
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStartrReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstStartrReq);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasPowerOffReq
 功能描述  : 向CAS发送关机请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasPowerOffReq(VOS_VOID)
{
    CNAS_CAS_HRPD_POWER_OFF_REQ_STRU     *pstPowerOffReq;

    /* 分配消息 */
    pstPowerOffReq = (CNAS_CAS_HRPD_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, sizeof(CNAS_CAS_HRPD_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstPowerOffReq)
    {
        return;
    }

    /* 填充消息 */
    pstPowerOffReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstPowerOffReq->enMsgId             = ID_CNAS_CAS_HRPD_POWER_OFF_REQ;
    pstPowerOffReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPowerOffReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstPowerOffReq);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasSysSyncReq
 功能描述  : 向CAS发送ID_CNAS_CAS_HSD_SYSTEM_SYNC_REQ消息
 输入参数  : ulFreqNum   : 下发搜网频点个数
             pstFreqList : 下发搜网频点地址

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数
  2.日    期   : 2015年1月19日
    作    者   : d00212987
    修改内容   : 增加每次下发搜网频点参数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSysSyncReq(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
)
{
    CNAS_CAS_HRPD_SYSTEM_SYNC_REQ_STRU *pstSysSyncReq;

    /* 分配消息 */
    pstSysSyncReq = (CNAS_CAS_HRPD_SYSTEM_SYNC_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,  sizeof(CNAS_CAS_HRPD_SYSTEM_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSysSyncReq)
    {
        return;
    }

    /* 填充消息 */
    pstSysSyncReq->ulReceiverPid   = UEPS_PID_HALMP;
    pstSysSyncReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSysSyncReq->enMsgId         = ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ;
    pstSysSyncReq->usOpId          = 0;

    PS_MEM_SET(pstSysSyncReq->astFreqList, 0x00, sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU) * CNAS_CAS_HRPD_MAX_FREQ_NUM);

    PS_MEM_CPY(pstSysSyncReq->astFreqList, pstFreqList, sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU) * ulFreqNum);

    pstSysSyncReq->ulFreqNum = ulFreqNum;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysSyncReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSysSyncReq);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasStopSysSyncReq
 功能描述  : 向CAS发送停止HRPD搜网请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasStopSysSyncReq(VOS_VOID)
{
    CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ_STRU                *pstStopSysAcqReq;

    /* 分配消息 */
    pstStopSysAcqReq = (CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, \
                                                                               sizeof(CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstStopSysAcqReq)
    {
        return;
    }

    /* 填充消息 */
    pstStopSysAcqReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstStopSysAcqReq->enMsgId             = ID_CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ;
    pstStopSysAcqReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStopSysAcqReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstStopSysAcqReq);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasOocNtf
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPD_OOC_NTF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月12日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasOocNtf(VOS_VOID)
{
    CNAS_CAS_HRPD_OOC_NTF_STRU          *pstOocNtf;

    /* 分配消息 */
    pstOocNtf = (CNAS_CAS_HRPD_OOC_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, sizeof(CNAS_CAS_HRPD_OOC_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstOocNtf)
    {
        return;
    }

    pstOocNtf->ulReceiverPid       = UEPS_PID_HALMP;
    pstOocNtf->enMsgId             = ID_CNAS_CAS_HRPD_OOC_NTF;
    pstOocNtf->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstOocNtf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstOocNtf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasPilotSearchSuccNtf
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasPilotSearchSuccNtf(VOS_VOID)
{
    CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF_STRU               *pstPilotSearchSuccNft;

    /* 分配消息 */
    pstPilotSearchSuccNft = (CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                                sizeof(CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPilotSearchSuccNft)
    {
        return;
    }

    pstPilotSearchSuccNft->ulReceiverPid       = UEPS_PID_HALMP;
    pstPilotSearchSuccNft->enMsgId             = ID_CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF;
    pstPilotSearchSuccNft->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPilotSearchSuccNft);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstPilotSearchSuccNft);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasPilotSearchFailNtf
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月15日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasPilotSearchFailNtf(VOS_VOID)
{
    CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF_STRU               *pstPilotSearchFailNft;

    /* 分配消息 */
    pstPilotSearchFailNft = (CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                                sizeof(CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPilotSearchFailNft)
    {
        return;
    }

    pstPilotSearchFailNft->ulReceiverPid       = UEPS_PID_HALMP;
    pstPilotSearchFailNft->enMsgId             = ID_CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF;
    pstPilotSearchFailNft->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPilotSearchFailNft);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstPilotSearchFailNft);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasSysCfgReq
 功能描述  : 向CAS发送ID_CNAS_CAS_SYS_CFG_SET_REQ消息
 输入参数  : pstSysCfg -- 系统配置请求消息地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月13日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSysCfgReq(
    MSCC_HSD_SYS_CFG_REQ_STRU          *pstSysCfg
)
{
    CNAS_CAS_HRPD_SYS_CFG_REQ_STRU     *pstSysCfgReq = VOS_NULL_PTR;

    /* 分配消息 */
    pstSysCfgReq = (CNAS_CAS_HRPD_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                                                  sizeof(CNAS_CAS_HRPD_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSysCfgReq)
    {
        return;
    }

    PS_MEM_SET(pstSysCfgReq, 0, sizeof(CNAS_CAS_HRPD_SYS_CFG_REQ_STRU));

    pstSysCfgReq->ulSenderPid     = UEPS_PID_HSD;
    pstSysCfgReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSysCfgReq->ulReceiverPid   = UEPS_PID_HALMP;
    pstSysCfgReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSysCfgReq->ulLength        = sizeof(CNAS_CAS_HRPD_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSysCfgReq->usOpId          = pstSysCfg->usOpId;
    pstSysCfgReq->enMsgId         = ID_CNAS_CAS_HRPD_SYS_CFG_REQ;

    pstSysCfgReq->stSuppBand.bitOpBC0_A  = pstSysCfg->stCdmaBand.bitOpBC0_A;
    pstSysCfgReq->stSuppBand.bitOpBC0_B  = pstSysCfg->stCdmaBand.bitOpBC0_B;
    pstSysCfgReq->stSuppBand.bitOpBC1    = pstSysCfg->stCdmaBand.bitOpBC1;
    pstSysCfgReq->stSuppBand.bitOpBC2    = pstSysCfg->stCdmaBand.bitOpBC2;
    pstSysCfgReq->stSuppBand.bitOpBC3    = pstSysCfg->stCdmaBand.bitOpBC3;
    pstSysCfgReq->stSuppBand.bitOpBC4    = pstSysCfg->stCdmaBand.bitOpBC4;
    pstSysCfgReq->stSuppBand.bitOpBC5    = pstSysCfg->stCdmaBand.bitOpBC5;
    pstSysCfgReq->stSuppBand.bitOpBC6    = pstSysCfg->stCdmaBand.bitOpBC6;
    pstSysCfgReq->stSuppBand.bitOpBC7    = pstSysCfg->stCdmaBand.bitOpBC7;
    pstSysCfgReq->stSuppBand.bitOpBC8    = pstSysCfg->stCdmaBand.bitOpBC8;
    pstSysCfgReq->stSuppBand.bitOpBC9    = pstSysCfg->stCdmaBand.bitOpBC9;
    pstSysCfgReq->stSuppBand.bitOpBC10   = pstSysCfg->stCdmaBand.bitOpBC10;
    pstSysCfgReq->stSuppBand.bitOpBC11   = pstSysCfg->stCdmaBand.bitOpBC11;
    pstSysCfgReq->stSuppBand.bitOpBC12   = pstSysCfg->stCdmaBand.bitOpBC12;
    pstSysCfgReq->stSuppBand.bitOpBC14   = pstSysCfg->stCdmaBand.bitOpBC14;
    pstSysCfgReq->stSuppBand.bitOpBC15   = pstSysCfg->stCdmaBand.bitOpBC15;

    pstSysCfgReq->ucSuppRatNum    = pstSysCfg->ucSuppRatNum;

    PS_MEM_CPY(&(pstSysCfgReq->aenRatMode[0]),
               &(pstSysCfg->aenRatMode[0]),
               VOS_RATMODE_BUTT * sizeof(VOS_RATMODE_ENUM_UINT32));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysCfgReq);


    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSysCfgReq);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasSuspendReq
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPD_SUSPEND_REQ消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月03日
    作    者   : h00300778
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSuspendReq(VOS_VOID)
{
    CNAS_CAS_HRPD_SUSPEND_REQ_STRU     *pstSuspendReq;

    /* 分配消息 */
    pstSuspendReq = (CNAS_CAS_HRPD_SUSPEND_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, sizeof(CNAS_CAS_HRPD_SUSPEND_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSuspendReq)
    {
        return;
    }

    pstSuspendReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstSuspendReq->enMsgId             = ID_CNAS_CAS_HRPD_SUSPEND_REQ;
    pstSuspendReq->usOpId              = 0;

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSuspendReq);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasDisableLteNtfReq
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPD_DISABLE_LTE_NTF消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasDisableLteNtf(VOS_VOID)
{
    CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU *pstDisableReq;

    /* 分配消息 */
    pstDisableReq = (CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstDisableReq)
    {
        return;
    }

    PS_MEM_SET(pstDisableReq, 0, sizeof(CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU));

    pstDisableReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstDisableReq->ulSenderPid         = UEPS_PID_HSD;
    pstDisableReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDisableReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstDisableReq->ulLength            = sizeof(CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstDisableReq->enMsgId             = ID_CNAS_CAS_HRPD_DISABLE_LTE_NTF;
    pstDisableReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstDisableReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstDisableReq);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasBsrLteReq
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPD_BSR_LTE_REQ消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasBsrLteReq(VOS_VOID)
{
    CNAS_CAS_HRPD_BSR_LTE_REQ_STRU *pstBsrLteReq;

    /* 分配消息 */
    pstBsrLteReq = (CNAS_CAS_HRPD_BSR_LTE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_BSR_LTE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstBsrLteReq)
    {
        return;
    }

    pstBsrLteReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstBsrLteReq->ulSenderPid         = UEPS_PID_HSD;
    pstBsrLteReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstBsrLteReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstBsrLteReq->ulLength            = sizeof(CNAS_CAS_HRPD_BSR_LTE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBsrLteReq->enMsgId             = ID_CNAS_CAS_HRPD_BSR_LTE_REQ;
    pstBsrLteReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstBsrLteReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstBsrLteReq);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasStopBsrLteReq
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPD_STOP_BSR_LTE_REQ消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasStopBsrLteReq(VOS_VOID)
{
    CNAS_CAS_HRPD_STOP_BSR_LTE_REQ_STRU                    *pstStopBsrLteReq;

    /* 分配消息 */
    pstStopBsrLteReq = (CNAS_CAS_HRPD_STOP_BSR_LTE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_STOP_BSR_LTE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstStopBsrLteReq)
    {
        return;
    }

    pstStopBsrLteReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstStopBsrLteReq->ulSenderPid         = UEPS_PID_HSD;
    pstStopBsrLteReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstStopBsrLteReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstStopBsrLteReq->ulLength            = sizeof(CNAS_CAS_HRPD_STOP_BSR_LTE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstStopBsrLteReq->enMsgId             = ID_CNAS_CAS_HRPD_STOP_BSR_LTE_REQ;
    pstStopBsrLteReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStopBsrLteReq);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstStopBsrLteReq);

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasFreqListReq
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF消息
 输入参数  : ulFreqNum   : 下发搜网频点个数
             pstFreqList : 下发搜网频点地址

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月16日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasFreqListCnf(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
)
{
    CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF_STRU             *pstFreqListCnf;

    /* 分配消息 */
    pstFreqListCnf = (CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstFreqListCnf)
    {
        return;
    }

    /* 填充消息 */
    pstFreqListCnf->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstFreqListCnf->ulSenderPid         = UEPS_PID_HSD;
    pstFreqListCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstFreqListCnf->ulReceiverPid       = UEPS_PID_HALMP;
    pstFreqListCnf->ulLength            = sizeof(CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstFreqListCnf->enMsgId             = ID_CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF;
    pstFreqListCnf->usOpId              = 0;

    PS_MEM_SET(pstFreqListCnf->astFreqList, 0x00, sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU) * CNAS_CAS_HRPD_MAX_FREQ_NUM);

    PS_MEM_CPY(pstFreqListCnf->astFreqList,
               pstFreqList,
               sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU) * ulFreqNum);

    pstFreqListCnf->ulFreqNum = ulFreqNum;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstFreqListCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstFreqListCnf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasSubnetIdChkCnf
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF消息
 输入参数  : enValidFlag   : subnetId是否有效

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSubnetIdChkCnf(
    PS_BOOL_ENUM_UINT8                  enIsValidFlag
)
{
    CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF_STRU                 *pstChkCnf;

    /* 分配消息 */
    pstChkCnf = (CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstChkCnf)
    {
        return;
    }

    /* 填充消息 */
    pstChkCnf->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstChkCnf->ulSenderPid              = UEPS_PID_HSD;
    pstChkCnf->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstChkCnf->ulReceiverPid            = UEPS_PID_HALMP;
    pstChkCnf->ulLength                 = sizeof(CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstChkCnf->enMsgId                  = ID_CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF;
    pstChkCnf->usOpId                   = 0;
    pstChkCnf->enSubnetIdIsValidFlag    = enIsValidFlag;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstChkCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstChkCnf);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasSuspendRsp
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPP_RESUME_RSP消息
 输入参数  : enValidFlag   : subnetId是否有效

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSuspendRsp(
    CAS_CNAS_HRPD_RSLT_ENUM_UINT16      enRslt
)
{
    CNAS_CAS_HRPD_SUSPEND_RSP_STRU      *pstSuspendRsp;

    /* 分配消息 */
    pstSuspendRsp = (CNAS_CAS_HRPD_SUSPEND_RSP_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSuspendRsp)
    {
        return;
    }

    /* 填充消息 */
    pstSuspendRsp->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSuspendRsp->ulSenderPid              = UEPS_PID_HSD;
    pstSuspendRsp->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSuspendRsp->ulReceiverPid            = UEPS_PID_HALMP;
    pstSuspendRsp->ulLength                 = sizeof(CNAS_CAS_HRPD_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSuspendRsp->enMsgId                  = ID_CNAS_CAS_HRPD_SUSPEND_RSP;
    pstSuspendRsp->usOpId                   = 0;
    pstSuspendRsp->enRslt                   = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSuspendRsp);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSuspendRsp);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasResumeRsp
 功能描述  : 向CAS发送ID_CNAS_CAS_HRPP_RESUME_RSP消息
 输入参数  : enValidFlag   : subnetId是否有效

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月02日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasResumeRsp(VOS_VOID)
{
    CNAS_CAS_HRPD_RESUME_RSP_STRU      *pstResumeRsp;

    /* 分配消息 */
    pstResumeRsp = (CNAS_CAS_HRPD_RESUME_RSP_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_RESUME_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstResumeRsp)
    {
        return;
    }

    /* 填充消息 */
    pstResumeRsp->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstResumeRsp->ulSenderPid              = UEPS_PID_HSD;
    pstResumeRsp->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstResumeRsp->ulReceiverPid            = UEPS_PID_HALMP;
    pstResumeRsp->ulLength                 = sizeof(CNAS_CAS_HRPD_RESUME_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstResumeRsp->enMsgId                  = ID_CNAS_CAS_HRPD_RESUME_RSP;
    pstResumeRsp->usOpId                   = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstResumeRsp);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstResumeRsp);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasCFreqLockNtf
 功能描述  : 向接入层发送CNAS_CAS_1X_FREQ_LOCK_NTF_STRU消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月14日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_SndCasCFreqLockNtf(MSCC_HSD_CFREQ_LOCK_NTF_STRU   *pstCFreqLockNtf)
{
    CNAS_CAS_HRPD_FREQ_LOCK_NTF_STRU     *pstCnasCasCFreqLockNtf   = VOS_NULL_PTR;

    pstCnasCasCFreqLockNtf =
            (CNAS_CAS_HRPD_FREQ_LOCK_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                        sizeof(CNAS_CAS_HRPD_FREQ_LOCK_NTF_STRU));

    if (VOS_NULL_PTR == pstCnasCasCFreqLockNtf)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCnasCasCFreqLockNtf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(CNAS_CAS_HRPD_FREQ_LOCK_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写消息头部信息 */
    pstCnasCasCFreqLockNtf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCnasCasCFreqLockNtf->ulSenderPid     = UEPS_PID_HSD;
    pstCnasCasCFreqLockNtf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCnasCasCFreqLockNtf->ulReceiverPid   = UEPS_PID_HALMP;
    pstCnasCasCFreqLockNtf->enMsgId         = ID_CNAS_CAS_HRPD_FREQ_LOCK_NTF;
    pstCnasCasCFreqLockNtf->usOpId          = 0;
    pstCnasCasCFreqLockNtf->enMode          = pstCFreqLockNtf->enFreqLockMode;
    pstCnasCasCFreqLockNtf->usBandClass     = pstCFreqLockNtf->usHrpdBandClass;
    pstCnasCasCFreqLockNtf->usFreq          = pstCFreqLockNtf->usHrpdFreq;
    pstCnasCasCFreqLockNtf->usPilotPn       = pstCFreqLockNtf->usHrpdPn;

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstCnasCasCFreqLockNtf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasBeginSessionNotify
 功能描述  : HSD通知CAS开始Session通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : x00306642
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasBeginSessionNotify(VOS_VOID)
{
    CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU                   *pstBeginSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstBeginSessionNotify = (CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* 构造消息结构体 */
    pstBeginSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulSenderPid      = UEPS_PID_HSD;
    pstBeginSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulReceiverPid    = UEPS_PID_HALMP;
    pstBeginSessionNotify->ulLength         = ulMsgLength;
    pstBeginSessionNotify->enMsgId          = ID_CNAS_CAS_HRPD_SESSION_BEGIN_NTF;
    pstBeginSessionNotify->enSessionType    = CNAS_CAS_HRPD_SESSION_TYPE_NETWORK_ACQ;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstBeginSessionNotify);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasEndSessionNotify
 功能描述  : HSD通知CAS开结束Session通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月15日
    作    者   : x00306642
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasEndSessionNotify(VOS_VOID)
{
    CNAS_CAS_HRPD_SESSION_END_NTF_STRU                     *pstEndSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_HRPD_SESSION_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEndSessionNotify = (CNAS_CAS_HRPD_SESSION_END_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* 构造消息结构体 */
    pstEndSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulSenderPid      = UEPS_PID_HSD;
    pstEndSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulReceiverPid    = UEPS_PID_HALMP;
    pstEndSessionNotify->ulLength         = ulMsgLength;
    pstEndSessionNotify->enMsgId          = ID_CNAS_CAS_HRPD_SESSION_END_NTF;
    pstEndSessionNotify->enSessionType    = CNAS_CAS_HRPD_SESSION_TYPE_NETWORK_ACQ;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstEndSessionNotify);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasHdrCsqSetReq
 功能描述  : HSD通知CAS hdr csq set req
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_SndCasHdrCsqSetReq(
    MSCC_HSD_HDR_CSQ_SET_REQ_STRU      *psrHdrSetReq
)
{
    CNAS_CAS_HRPD_SET_SIGNAL_QUALITY_REQ_STRU              *pstHdrcsqSetReq = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_HRPD_SET_SIGNAL_QUALITY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHdrcsqSetReq = (CNAS_CAS_HRPD_SET_SIGNAL_QUALITY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstHdrcsqSetReq)
    {
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8 *)pstHdrcsqSetReq + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* 构造消息结构体 */
    pstHdrcsqSetReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstHdrcsqSetReq->ulSenderPid      = UEPS_PID_HSD;
    pstHdrcsqSetReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstHdrcsqSetReq->ulReceiverPid    = UEPS_PID_HRUP;
    pstHdrcsqSetReq->ulLength         = ulMsgLength;

    pstHdrcsqSetReq->enMsgId                = ID_CNAS_CAS_HRPD_SET_SIGNAL_QUALITY_REQ;

    pstHdrcsqSetReq->ucRptRssiThreshold     = psrHdrSetReq->stHdrCsq.ucRssiThreshold;
    pstHdrcsqSetReq->ucTimeInterval         = psrHdrSetReq->stHdrCsq.ucTimeInterval;
    pstHdrcsqSetReq->ucRptSinrThreshold     = psrHdrSetReq->stHdrCsq.ucSnrThreshold;
    pstHdrcsqSetReq->ucRptEcIoThreshold     = psrHdrSetReq->stHdrCsq.ucEcioThreshold;

    /* SNR THRESHOLD 保留，以后迭代有可能会添加 */

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstHdrcsqSetReq);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SndCasSuspendRelReq
 功能描述  : HSD通知CAS ID_CNAS_CAS_HRPD_SUSPEND_REL_REQ消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月29日
    作    者   : g00256031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_SndCasSuspendRelReq(VOS_VOID)
{
    CNAS_CAS_HRPD_SUSPEND_REL_REQ_STRU *pstSuspendRelReq = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_HRPD_SUSPEND_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSuspendRelReq = (CNAS_CAS_HRPD_SUSPEND_REL_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstSuspendRelReq)
    {
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8 *)pstSuspendRelReq + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* 构造消息结构体 */
    pstSuspendRelReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstSuspendRelReq->ulSenderPid      = UEPS_PID_HSD;
    pstSuspendRelReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstSuspendRelReq->ulReceiverPid    = UEPS_PID_HALMP;
    pstSuspendRelReq->ulLength         = ulMsgLength;

    pstSuspendRelReq->enMsgId          = ID_CNAS_CAS_HRPD_SUSPEND_REL_REQ;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSuspendRelReq);

    return VOS_OK;
}


/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
