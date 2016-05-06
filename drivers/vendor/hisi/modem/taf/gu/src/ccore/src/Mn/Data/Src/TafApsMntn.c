/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsMntn.c
  版 本 号   : 初稿
  作    者   : Y00213812
  生成日期   : 2013年12月08日
  最近修改   :
  功能描述   : TAF APS模块可维可测处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月08日
    作    者   : Y00213812
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsMntn.h"
#include "TafLog.h"
#include "MnComm.h"
#include "MnApsComm.h"
#include "TafApsApi.h"
#include "TafApsCtx.h"
#include "TafApsProcEpdszid.h"
#include "TafFsm.h"
#include "TafApsComFunc.h"
#include "msp_diag_comm.h"

#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_APS_MNTN_C
/*lint +e767*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_APS_TraceSyncMsg
 功能描述  : 将TAFAPSAPI同步消息勾出
 输入参数  : ulMsgId       消息ID,
             ulLength      消息长度,
             *pucData      消息
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月17日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID  TAF_APS_TraceMsg(
    VOS_VOID                           *pMsg
)
{
    /* 消息勾包 */
    DIAG_TraceReport(pMsg);
}

/*****************************************************************************
 函 数 名  : TAF_APS_TraceSyncMsg
 功能描述  : 将TAFAPSAPI同步消息勾出
 输入参数  : ulMsgId       消息ID,
             ulLength      消息长度,
             *pucData      消息
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月17日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID  TAF_APS_TraceSyncMsg(
    VOS_UINT32                          ulMsgId,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLength
)
{
    TAF_PS_MSG_STRU                    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    if (ulLength >= 4)
    {
        ulMsgLength = ulLength - 4;
    }
    else
    {
        ulMsgLength = 0;
    }

    pstMsg = (TAF_PS_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                  sizeof(TAF_PS_MSG_STRU) + ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_APS_TraceSyncMsg:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 勾包消息赋值 */
    pstMsg->stHeader.ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstMsg->stHeader.ulSenderPid        = WUEPS_PID_TAF;
    pstMsg->stHeader.ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stHeader.ulReceiverPid      = WUEPS_PID_TAF;

    pstMsg->stHeader.ulLength           = ulMsgLength + 8;
    pstMsg->stHeader.ulMsgName          = ulMsgId;

    PS_MEM_CPY(pstMsg->aucContent, pucData, ulLength);

    /* 消息勾包 */
    TAF_APS_TraceMsg(pstMsg);
    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_TraceApsEvt
 功能描述  : TAF 将 PS事件消息头发送给 OM
 输入参数  : ulEvtId       消息ID,
             ulLength      消息长度,
             *pucData      消息
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月17日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID  TAF_APS_TraceApsEvt(
    VOS_UINT32                          ulEvtId,
    VOS_UINT32                          ulLength,
    VOS_UINT8                          *pucData
)
{
    TAF_PS_EVT_STRU                    *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_PS_EVT_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                  (sizeof(TAF_PS_EVT_STRU) + ulLength) - 4);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_APS_TraceApsEvt:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 勾包消息赋值 */
    pstMsg->stHeader.ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstMsg->stHeader.ulSenderPid        = WUEPS_PID_TAF;
    pstMsg->stHeader.ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stHeader.ulReceiverPid      = WUEPS_PID_TAF;

    pstMsg->stHeader.ulLength           = ulLength + 8;
    pstMsg->stHeader.ulMsgName          = ulEvtId;
    pstMsg->ulEvtId                     = ulEvtId;

    PS_MEM_CPY(pstMsg->aucContent, pucData, ulLength);

    /* 消息勾包 */
    TAF_APS_TraceMsg(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_TraceTimer
 功能描述  : 发送消息给OM模块，APS定时器运行状态
 输入参数  : enTimerStatus - 定时器状态
             enTimerId     - 定时器ID
             ulLen         - 定时器时长
             ucPdpId       - 定时器关联PDPID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月13日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2013年12月18日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseIII，修改参数
*****************************************************************************/
VOS_VOID  TAF_APS_TraceTimer(
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus,
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulPara
)
{
    TAF_APS_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_APS_TIMER_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                             sizeof(TAF_APS_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"TAF_APS_TraceTimer:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(TAF_APS_TIMER_INFO_STRU));

    /* 定时器勾包消息赋值 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_APS_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->ulPara                      = ulPara;
    pstMsg->ulLen                       = ulLen;

    /* 定时器消息勾包 */
    TAF_APS_TraceMsg(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

}

/*****************************************************************************
 函 数 名  : TAF_APS_ShowPdpEntityInfo
 功能描述  : 显示PDP实体关键信息
 输入参数  : VOS_UINT8                           ucPdpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ShowPdpEntityInfo(
    VOS_UINT8                           ucPdpId
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("*****************************\n");
    (VOS_VOID)vos_printf("*BearerInfo: bitCid      %d\n", pstPdpEntity->stClientInfo.ulBitCidMask);
    (VOS_VOID)vos_printf("*BearerInfo: Cid         %d\n", pstPdpEntity->stClientInfo.ucCid);
    (VOS_VOID)vos_printf("*BearerInfo: ModuleId    %d\n", pstPdpEntity->stClientInfo.aulModuleId[pstPdpEntity->stClientInfo.ucCid]);
    (VOS_VOID)vos_printf("*BearerInfo: PdpType     %d\n", pstPdpEntity->stClientInfo.aenPdpType[pstPdpEntity->stClientInfo.ucCid]);
    (VOS_VOID)vos_printf("*BearerInfo: RabId       %d\n", pstPdpEntity->ucNsapi);
    (VOS_VOID)vos_printf("*BearerInfo: LinkedNsapi %d\n", pstPdpEntity->ucLinkedNsapi);
    (VOS_VOID)vos_printf("*BearerInfo: PdpType     %d\n", pstPdpEntity->PdpAddr.ucPdpTypeNum);
    (VOS_VOID)vos_printf("*BearerInfo: Apn         %s\n", pstPdpEntity->PdpApn.aucValue);
    (VOS_VOID)vos_printf("*****************************\n");

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_ShowCidSdfParaInfo
 输入参数  : ucCid                      - CID
             ucPfId                     - Packet Filter ID
 输入参数  : ucCid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ShowCidSdfParaInfo(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPfId
)
{
    APS_L4A_SDF_PARA_STRU              *pstSdfParaInfo;

    pstSdfParaInfo = (APS_L4A_SDF_PARA_STRU*)PS_MEM_ALLOC(
                            WUEPS_PID_TAF,
                            sizeof(APS_L4A_SDF_PARA_STRU));
    if (VOS_NULL_PTR == pstSdfParaInfo)
    {
        (VOS_VOID)vos_printf("TAF_APS_ShowCidSdfParaInfo: ALLOC NULL PTR\n");
        return;
    }

    PS_MEM_SET(pstSdfParaInfo, 0x00, sizeof(APS_L4A_SDF_PARA_STRU));

    (VOS_VOID)TAF_APS_GetCidSdfParaInfo(ucCid, pstSdfParaInfo);

    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("****************** SDF INFO ********************************\n");
    (VOS_VOID)vos_printf("* CID                                       %d\n", pstSdfParaInfo->ulCid);
    (VOS_VOID)vos_printf("* bitOpPdnType                              %d\n", pstSdfParaInfo->bitOpPdnType);
    (VOS_VOID)vos_printf("* bitOpApn                                  %d\n", pstSdfParaInfo->bitOpApn);
    (VOS_VOID)vos_printf("* bitOpSdfQos                               %d\n", pstSdfParaInfo->bitOpSdfQos);
    (VOS_VOID)vos_printf("* bitOpLinkdCId                             %d\n", pstSdfParaInfo->bitOpLinkdCId);
    (VOS_VOID)vos_printf("* bitIpv4AddrAllocType                      %d\n", pstSdfParaInfo->bitIpv4AddrAllocType);
    (VOS_VOID)vos_printf("* bitOpGwAuthInfo                           %d\n", pstSdfParaInfo->bitOpGwAuthInfo);
    (VOS_VOID)vos_printf("************************************************************\n");
    (VOS_VOID)vos_printf("* LinkdCid                                  %d\n", pstSdfParaInfo->ulLinkdCid);
    (VOS_VOID)vos_printf("* PdnType                                   %d\n", pstSdfParaInfo->enPdnType);
    (VOS_VOID)vos_printf("* Ipv4AddrAllocType                         %d\n", pstSdfParaInfo->enIpv4AddrAllocType);
    (VOS_VOID)vos_printf("* BearerCntxtType                           %d\n", pstSdfParaInfo->enBearerCntxtType);
    (VOS_VOID)vos_printf("* aucApnName                                %s\n", pstSdfParaInfo->stApnInfo.aucApnName);
    (VOS_VOID)vos_printf("* ucApnLen                                  %d\n", pstSdfParaInfo->stApnInfo.ucApnLen);
    (VOS_VOID)vos_printf("************************************************************\n");
    (VOS_VOID)vos_printf("* enGwAuthType (0:PAP 1:CHAP)               %d\n", pstSdfParaInfo->stGwAuthInfo.enGwAuthType);
    (VOS_VOID)vos_printf("* aucUserName                               %s\n", pstSdfParaInfo->stGwAuthInfo.aucUserName);
    (VOS_VOID)vos_printf("* ucUserNameLen                             %d\n", pstSdfParaInfo->stGwAuthInfo.ucUserNameLen);
    (VOS_VOID)vos_printf("* aucPwd                                    %s\n", pstSdfParaInfo->stGwAuthInfo.aucPwd);
    (VOS_VOID)vos_printf("* ucPwdLen                                  %d\n", pstSdfParaInfo->stGwAuthInfo.ucPwdLen);
    (VOS_VOID)vos_printf("************************************************************\n");
    (VOS_VOID)vos_printf("* PfNum                                     %d\n", pstSdfParaInfo->ulPfNum);
    (VOS_VOID)vos_printf("* bitOpRmtIpv4AddrAndMask                   %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpRmtIpv4AddrAndMask);
    (VOS_VOID)vos_printf("* bitOpRmtIpv6AddrAndMask                   %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpRmtIpv6AddrAndMask);
    (VOS_VOID)vos_printf("* bitOpLocalIpv4AddrAndMask                 %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpLocalIpv4AddrAndMask);
    (VOS_VOID)vos_printf("* bitOpLocalIpv6AddrAndMask                 %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpLocalIpv6AddrAndMask);
    (VOS_VOID)vos_printf("* bitOpProtocolId                           %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpProtocolId);
    (VOS_VOID)vos_printf("* bitOpSingleLocalPort                      %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpSingleLocalPort);
    (VOS_VOID)vos_printf("* bitOpLocalPortRange                       %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpLocalPortRange);
    (VOS_VOID)vos_printf("* bitOpSingleRemotePort                     %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpSingleRemotePort);
    (VOS_VOID)vos_printf("* bitOpRemotePortRange                      %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpRemotePortRange);
    (VOS_VOID)vos_printf("* bitOpSecuParaIndex                        %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpSecuParaIndex);
    (VOS_VOID)vos_printf("* bitOpTypeOfService                        %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].bitOpTypeOfService);
    (VOS_VOID)vos_printf("* ucPacketFilterId                          %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].ucPacketFilterId);
    (VOS_VOID)vos_printf("* ucNwPacketFilterId                        %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].ucNwPacketFilterId);
    (VOS_VOID)vos_printf("* enDirection                               %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].enDirection);
    (VOS_VOID)vos_printf("* ucPrecedence                              %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].ucPrecedence);
    (VOS_VOID)vos_printf("* ucProtocolId                              %d\n", pstSdfParaInfo->astCntxtTftInfo[ucPfId].ucProtocolId);
    (VOS_VOID)vos_printf("************************************************************\n");

    PS_MEM_FREE(WUEPS_PID_TAF, pstSdfParaInfo);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_APS_ShowDsFlowInfo
 功能描述  : 流量统计可维可测信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_ShowDsFlowInfo(VOS_VOID)
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx = VOS_NULL_PTR;

    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();

    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("AP流量上报标识              %d\n", pstApsDsflowCtx->ulFluxThresRptFlg);
    (VOS_VOID)vos_printf("AP流量上报阈值(KByte)       %u\n", pstApsDsflowCtx->ulFluxThresKByte);
    (VOS_VOID)vos_printf("AP流量上报阈值(Byte)        0x%08X%08X\n", pstApsDsflowCtx->ulFluxThresHigh, pstApsDsflowCtx->ulFluxThresLow);
    (VOS_VOID)vos_printf("AP流量累计值(Byte)          0x%08X%08X\n", pstApsDsflowCtx->ulTotalFluxHigh, pstApsDsflowCtx->ulTotalFluxLow);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_Help
 功能描述  : 软调信息
 输入参数  : ucCid                      - CID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月14日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_Help(
    VOS_UINT8                           ucCid
)
{
    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("****************** APS软调信息**********************************\n");
    (VOS_VOID)vos_printf("* TAF_APS_ShowCidSdfParaInfo   显示SDF参数(参数1:CID 参数2:PfId)\n");
    (VOS_VOID)vos_printf("* TAF_APS_ShowPdpEntityInfo    显示APS实体信息(参数:APS实体索引)\n");
    (VOS_VOID)vos_printf("****************************************************************\n");

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndOmDfsInfo
 功能描述  : 发送消息给OM模块，APS DDR调频信息
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月17日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_APS_SndOmDfsInfo(TAF_APS_SWITCH_DDR_RATE_INFO_STRU *pstSwitchDdrInfo)
{
    TAF_APS_MNTN_DFS_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_APS_MNTN_DFS_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                             sizeof(TAF_APS_MNTN_DFS_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndOmDfsInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 定时器勾包消息赋值 */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = sizeof(TAF_APS_MNTN_DFS_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_MSG_TAF_PS_APS_MNTN_DFS_INFO;

    PS_MEM_CPY(&pstMsg->stDfsInfo, pstSwitchDdrInfo, sizeof(TAF_APS_SWITCH_DDR_RATE_INFO_STRU));

    /* 消息勾包 */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

}


/*****************************************************************************
 函 数 名  : TAF_APS_TraceMntnMsg
 功能描述  : APS可维可测勾包
 输入参数  : VOS_UINT32                          ulMsgId
             VOS_UINT32                          ulLength
             VOS_UINT8                          *pucData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月17日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_TraceMntnMsg(
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulLength,
    VOS_UINT8                          *pucData
)
{
    TAF_PS_MSG_STRU                    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    if (ulLength >= 4)
    {
        ulMsgLength = ulLength - 4;
    }
    else
    {
        ulMsgLength = 0;
    }

    pstMsg = (TAF_PS_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                  sizeof(TAF_PS_MSG_STRU) + ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_APS_TraceMntnMsg:ERROR:Alloc Mem Fail.");
        return;
    }

    /* 勾包消息赋值 */
    pstMsg->stHeader.ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstMsg->stHeader.ulSenderPid        = WUEPS_PID_TAF;
    pstMsg->stHeader.ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stHeader.ulReceiverPid      = WUEPS_PID_TAF;

    pstMsg->stHeader.ulLength           = ulMsgLength + 4;
    pstMsg->stHeader.ulMsgName          = ulMsgId;

    PS_MEM_CPY(pstMsg->aucContent, pucData, ulLength);

    /* 消息勾包 */
    TAF_APS_TraceMsg(pstMsg);
    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_LogPdpEntityInfo
 功能描述  :
 输入参数  : VOS_UINT8                           ucPdpId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年03月28日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  TAF_APS_LogPdpEntityInfo(
    VOS_UINT8                           ucPdpId
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity = VOS_NULL_PTR;
    TAF_APS_PDP_ENTITY_STRU            *pstMsg       = VOS_NULL_PTR;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (VOS_TRUE != pstPdpEntity->ulUsedFlg)
    {
        return;
    }

    pstMsg = (TAF_APS_PDP_ENTITY_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_APS_PDP_ENTITY_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_LogPdpEntityInfo: ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_APS_PDP_ENTITY_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = sizeof(TAF_APS_PDP_ENTITY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_MSG_TAF_PS_APS_PDP_ENTITY;

    pstMsg->ucPdpId         = ucPdpId;
    pstMsg->enActType       = pstPdpEntity->ActType;
    pstMsg->ucRabId         = pstPdpEntity->ucNsapi;
    pstMsg->ucLinkedNsapi   = pstPdpEntity->ucLinkedNsapi;

    pstMsg->enCurrCdataServiceMode  = TAF_APS_GetCurrPdpEntityDataServiceMode();
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    pstMsg->ucDoQuickAcqProtect     = TAF_APS_GetDoQuickAcqProtectFlag(ucPdpId);
    pstMsg->enAirLinkStatus         = TAF_APS_GetCdmaAirLinkStatus(ucPdpId);
#endif

    PS_MEM_CPY(&(pstMsg->stClientInfo), &(pstPdpEntity->stClientInfo), sizeof(TAF_APS_CLIENT_INFO_STRU));

    PS_MEM_CPY(&(pstMsg->PdpAddr), &(pstPdpEntity->PdpAddr), sizeof(APS_PDP_ADDR_ST));

    TAF_APS_TraceMsg(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_LogFsmMntnInfo
 功能描述  : 输出消息进状态机处理前状态机的信息和处理后状态机的信息
 输入参数  : TAF_APS_FSM_STATUS_INFO_STRU       *stPriFsmInfo,
             TAF_APS_FSM_STATUS_INFO_STRU       *stCurrFsmInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年03月28日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_LogFsmMntnInfo(
    TAF_APS_FSM_STATUS_INFO_STRU       *pstPriFsmInfo,
    TAF_APS_FSM_STATUS_INFO_STRU       *pstCurrFsmInfo
)
{
    TAF_APS_FSM_MNTN_INFO_STRU         *pstMsg       = VOS_NULL_PTR;

    pstMsg = (TAF_APS_FSM_MNTN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_APS_FSM_MNTN_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_LogFsmMntnInfo: ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_APS_FSM_MNTN_INFO_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = sizeof(TAF_APS_FSM_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_MSG_TAF_PS_APS_FSM_INFO;

    pstMsg->ucPdpId                  = TAF_APS_GetCurrFsmEntityPdpId();
    pstMsg->enRatType                = TAF_APS_GetCurrPdpEntityRatType();
    pstMsg->ucSuspendStatus          = TAF_APS_GET_CDATA_SUSPEND_STATUS();

#if (FEATURE_ON == FEATURE_LTE)
    pstMsg->ucAllowDefPdnTeardownFlg = TAF_APS_GetAllowDefPdnTeardownFlg();
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    pstMsg->ulExist1XService         = TAF_APS_Get1XPsServiceStatus();
    pstMsg->ulClDelaySearch          = TAF_APS_GetClDelaySearch();
    pstMsg->ulIsHrpdDisabled         = TAF_APS_GetIsHrpdDisabledFlag();

#endif

    if (VOS_NULL_PTR != pstPriFsmInfo)
    {
        pstMsg->stPriFsmInfo.enFsmId     = pstPriFsmInfo->enFsmId;
        pstMsg->stPriFsmInfo.ulState     = pstPriFsmInfo->ulState;
    }

    if (VOS_NULL_PTR != pstCurrFsmInfo)
    {
        pstMsg->stCurrFsmInfo.enFsmId    = pstCurrFsmInfo->enFsmId;
        pstMsg->stCurrFsmInfo.ulState    = pstCurrFsmInfo->ulState;
    }

    TAF_APS_TraceMsg(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_LogOldNewPdpRatType
 功能描述  : 输出消息进状态机处理前状态机的信息和处理后状态机的信息
 输入参数  : TAF_APS_RAT_TYPE_ENUM_UINT32            enRatType
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年11月09日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_LogOldNewPdpRatType(
    TAF_APS_RAT_TYPE_ENUM_UINT32            enNewRatType,
    TAF_APS_RAT_TYPE_ENUM_UINT32            enOldRatType
)
{
    TAF_APS_OLD_NEW_PDP_RATTYPE_INFO_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_APS_OLD_NEW_PDP_RATTYPE_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_APS_OLD_NEW_PDP_RATTYPE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_LogOldNewPdpRatType: ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_APS_OLD_NEW_PDP_RATTYPE_INFO_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = sizeof(TAF_APS_OLD_NEW_PDP_RATTYPE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_MSG_TAF_PS_OLD_NEW_PDP_RATTYPE_INFO;

    pstMsg->enNewRatType    = enNewRatType;
    pstMsg->enOldRatType    = enOldRatType;

    TAF_APS_TraceMsg(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_APS_TraceEpdszidInfo
 功能描述  : 输出当前EPDSZID中的信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_TraceEpdszidInfo(VOS_VOID)
{
    TAF_APS_CDATA_EPDSZID_CTX_STRU            *pstEpdszid = VOS_NULL_PTR;

    pstEpdszid = TAF_APS_GetEpdszidCtx();

    /* 消息勾包 */
    TAF_APS_TraceMntnMsg(ID_MSG_TAF_PS_CDATA_EPDSZID_CHANGED,
                        sizeof(TAF_APS_CDATA_EPDSZID_CTX_STRU),
                        (VOS_UINT8 *)pstEpdszid);

}


/*****************************************************************************
 函 数 名  : TAF_APS_LogReadNVInfo
 功能描述  : 勾取读取的NV信息上报 可维可测
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_LogReadNVInfo(
    VOS_UINT16                              enNvItem,
    VOS_UINT16                              usNvDataLength,
    VOS_UINT32                              ulPid,
    VOS_UINT8                              *pucData
)
{
    TAF_APS_LOG_READ_NV_INFO_IND_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_APS_LOG_READ_NV_INFO_IND_STRU*)PS_MEM_ALLOC(ulPid,
                             sizeof(TAF_APS_LOG_READ_NV_INFO_IND_STRU) + usNvDataLength - 4);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulPid;
    pstMsg->ulLength        = sizeof(TAF_APS_LOG_READ_NV_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH + usNvDataLength - 4;
    pstMsg->enMsgId         = ID_MSG_TAF_APS_LOG_READ_NV_INFO_IND;
    pstMsg->enNvItem        = enNvItem;
    pstMsg->usNvDataLength  = usNvDataLength;
    PS_MEM_CPY(pstMsg->aucNvInfo, pucData, usNvDataLength);


    DIAG_TraceReport((VOS_VOID *)pstMsg);


    PS_MEM_FREE(ulPid, pstMsg);
    return;
}


#endif
/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

