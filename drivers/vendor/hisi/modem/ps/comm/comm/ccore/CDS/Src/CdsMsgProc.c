/******************************************************************************
                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsMsgProc.c
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月12日
  最近修改   :
  功能描述   : 实现消息接收、发送处理
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "CDS.h"
#include "CdsUlProc.h"
#include "CdsIpfCtrl.h"
#include "CdsMsgProc.h"
#include "FcFlowCtrlMana.h"
#include "QosFcRabStatus.h"
#include "CdsImsProc.h"
#include "CdsDebug.h"
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
#include "CdsBastetProc.h"
#endif

/*lint -e767*/
/*lint -e524*/
/*lint -e653*/

#define    THIS_FILE_ID        PS_FILE_ID_CDS_MSG_PROC_C
/*lint +e524*/
/*lint +e653*/
/*lint +e767*/

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
******************************************************************************/
VOS_UINT32      g_astUlIpfBidToNdisType[] = {
                        CDS_ADS_IP_PACKET_TYPE_DHCP_SERVERV4,
                        CDS_ADS_IP_PACKET_TYPE_ND_SERVERDHCPV6,
                        CDS_ADS_IP_PACKET_TYPE_BUTT,
                        CDS_ADS_IP_PACKET_TYPE_ICMPV6,
                        CDS_ADS_IP_PACKET_TYPE_LINK_FE80,
                        CDS_ADS_IP_PACKET_TYPE_LINK_FF,
                        CDS_ADS_IP_PACKET_TYPE_BUTT};

/*从BID获得IP包类型.注意数组越界*/
#define  CDS_UL_GET_IPPKT_TYPE_BY_BID(UlIpfBid)    \
                       (g_astUlIpfBidToNdisType[(UlIpfBid) - CDS_UL_IPF_BEARER_ID_DHCPV4])


/******************************************************************************
   5 函数实现
******************************************************************************/



/*****************************************************************************
 函 数 名  : CDS_UlDataIndToAds
 功能描述  : 向ADS上报数据
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
/*lint -e524*/
/*lint -e653*/

VOS_VOID CDS_UlDataIndToAds(TTF_MEM_ST *pstIpPkt)
{
    CDS_ADS_DATA_IND_STRU                *pstDataInd;
    VOS_UINT32                            ulMsgLen;
    IPF_RESULT_STRU                      *pstIpfRlst;
    VOS_UINT16                            usIpfResult;

    if (VOS_NULL_PTR == pstIpPkt)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_UlDataIndToAds : Input Para Error.");
        CDS_PRINT_ERROR(CDS_UlDataIndToAds_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    /*申请消息内存*/
    ulMsgLen = sizeof(CDS_ADS_DATA_IND_STRU) + (pstIpPkt->usUsed - 4);
    pstDataInd = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstDataInd)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_UlDataIndToAds : Alloc Msg Fail. Size=.",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_UlDataIndToAds_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        TTF_MemFree(UEPS_PID_CDS,pstIpPkt);
        return;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstDataInd,ACPU_PID_ADS_UL);
    pstDataInd->enMsgId     = ID_CDS_ADS_IP_PACKET_IND;

    /*填写ModemId/RabId/Len*/
    pstDataInd->usLen       = pstIpPkt->usUsed;
    pstDataInd->enModemId   = CDS_UL_GET_MODEMID_FROM_TTF(pstIpPkt);
    pstDataInd->ucRabId     = CDS_UL_GET_RABID_FROM_TTF(pstIpPkt);

    /*根据IPF结果的BEEARID来填写类型*/
    usIpfResult = CDS_UL_GET_IPF_RESULT_FORM_TTF(pstIpPkt);
    pstIpfRlst = (IPF_RESULT_STRU *)(&usIpfResult);
    if ((CDS_UL_IPF_BEARER_ID_DHCPV4 <= pstIpfRlst->usBearedId)
         &&(CDS_UL_IPF_BEARER_ID_LL_FF >= pstIpfRlst->usBearedId))
    {
        pstDataInd->enIpPacketType = (VOS_UINT8)CDS_UL_GET_IPPKT_TYPE_BY_BID(pstIpfRlst->usBearedId);
    }
    else
    {
        pstDataInd->enIpPacketType = CDS_ADS_IP_PACKET_TYPE_BUTT;
    }

    /*内容拷贝，释放源内存*/
    PS_MEM_CPY(pstDataInd->aucData,pstIpPkt->pData,pstIpPkt->usUsed);
    TTF_MemFree(UEPS_PID_CDS,pstIpPkt);

    /*发送消息*/
    CDS_SEND_MSG(pstDataInd);

    CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_UlDataIndToAds: Send Data Succ.Type ",pstIpfRlst->usBearedId);
    CDS_PRINT_INFO1(CDS_UlDataIndToAds_ENUM,CDS_PRINT_SENT_DATA_TO_ADS_INFO,pstIpfRlst->usBearedId);

    return;
}



/*****************************************************************************
 函 数 名  : CDS_GetRanMode
 功能描述  : 获得当前接入模式。默认返回Modem0上的接入模式。
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  CDS_GetRanMode(VOS_VOID)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    /*获得CDS对应实体信息*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return MMC_CDS_MODE_BUTT;
    }

    /*返回CDS实体的模式信息*/
    return pstCdsEntity->enRanMode;
}

/*****************************************************************************
 函 数 名  : CDS_ChangeRanModeToNULL
 功能描述  : 将当前接入模式切换到NULL
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ChangeRanModeToNULL(CDS_ENTITY_STRU *pstCdsEntity)
{

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_ChangeRanModeToNULL.ModemId, PreRanMode :",pstCdsEntity->usModemId,pstCdsEntity->enRanMode);
    CDS_PRINT_INFO2(CDS_ChangeRanModeToNULL_ENUM,LL2_PTR_NULL,pstCdsEntity->usModemId,pstCdsEntity->enRanMode);

    /* 流控进入NULL模式处理 */
    /*DTS2014050601430,只对MODEM0做流控切换*/
    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        Fc_SwitchToNull();
    }

    /*设置接入模式*/
    pstCdsEntity->enRanMode = MMC_CDS_MODE_NULL;

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*重置GU SR标志*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*启动10ms周期性定时器*/
    if (PS_SUCC != CDS_StartTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ChangeRanModeToNULL:Start Tmr Fail.");
        CDS_PRINT_ERROR(CDS_ChangeRanModeToNULL_ENUM, CDS_PRINT_START_TIMER_FAIL);
        return;
    }

    CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,PS_FALSE);
    CDS_ERROR_LOG(UEPS_PID_CDS,"Leave CDS_ChangeRanModeToNULL Succ.");
    CDS_PRINT_ERROR(CDS_ChangeRanModeToNULL_ENUM, CDS_PRINT_PROC_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ChangeRanModeToLTE
 功能描述  : 将当前接入模式切换到LTE
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ChangeRanModeToLTE(CDS_ENTITY_STRU *pstCdsEntity)
{

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_ChangeRanModeToLTE. ModemId,PreRanMode :",pstCdsEntity->usModemId,pstCdsEntity->enRanMode);
    CDS_PRINT_INFO2(CDS_ChangeRanModeToLTE_ENUM,CDS_PRINT_PROC_INFO,pstCdsEntity->usModemId,pstCdsEntity->enRanMode);

    /*DTS2014050601430,只对MODEM0做流控切换*/
    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        if (PS_FALSE == pstCdsEntity->ulTestModeFlg)
        {
            Fc_SwitchToLte();
        }
        else
        {
            /* 流控进入环回模式处理 */
            Fc_SwitchToNull();
        }
    }

    /*设置接入模式*/
    pstCdsEntity->enRanMode = MMC_CDS_MODE_LTE;

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*重置GU SR标志*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*停止NULL下行10ms周期性定时器*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR);

    /*发送上行缓存数据*/
    CDS_SendUlBuffData(pstCdsEntity);

    CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,PS_FALSE);

    CDS_ERROR_LOG(UEPS_PID_CDS,"Leave CDS_ChangeRanModeToLTE Succ.");
    CDS_PRINT_ERROR(CDS_ChangeRanModeToLTE_ENUM, CDS_PRINT_PROC_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ChangeRanModeToGU
 功能描述  : 将当前接入模式切换到GU
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

    2.日    期   : 2011年02月02日
      作    者   : y00151394
      修改内容   : 将GU周期性定时器修改为NULL模式下独有，在切换到GU后停止下行周期性定时器。

    3.日    期   : 2011年04月24日
      作    者   : y00151394
      修改内容   : 删除发送上行缓存功能。见问题单DTS2012033006483.

*****************************************************************************/
VOS_VOID CDS_ChangeRanModeToGU(CDS_ENTITY_STRU *pstCdsEntity)
{

    CDS_ASSERT(VOS_NULL_PTR != pstCdsEntity);

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_ChangeRanModeToGU. ModemId,PreRanMode :",pstCdsEntity->usModemId,pstCdsEntity->enRanMode);
    CDS_PRINT_INFO2(CDS_ChangeRanModeToGU_ENUM,CDS_PRINT_PROC_INFO,pstCdsEntity->usModemId,pstCdsEntity->enRanMode);

    /*DTS2014050601430,只对MODEM0做流控切换*/
    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        if (PS_FALSE == pstCdsEntity->ulTestModeFlg)
        {
            Fc_SwitchToGu();
        }
        else
        {
            /* 流控进入环回模式处理 */
            Fc_SwitchToNull();
        }
    }

    /*设置接入模式*/
    pstCdsEntity->enRanMode = MMC_CDS_MODE_GU;

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*将上行缓存发送到RABM*/
    CDS_SendUlBuffDataToRabm(pstCdsEntity,CDS_NAS_ALL_BEARER_ID);

    /*重置GU SR标志*/
    CDS_CLR_GU_ALL_RAB_SR_FLG(pstCdsEntity);

    /*停止NULL下行10ms周期性定时器*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR);

    CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,PS_FALSE);

    CDS_ERROR_LOG(UEPS_PID_CDS,"Leave CDS_ChangeRanModeToGU Succ.");
    CDS_PRINT_ERROR(CDS_ChangeRanModeToGU_ENUM, CDS_PRINT_PROC_INFO);

    return;
}


/*****************************************************************************
 函 数 名  : CDS_MMC_MsgProc
 功能描述  : 处理收到的MMC消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_MMC_MsgProc(MsgBlock  *pstMsg)
{
    MMC_CDS_MODE_CHANGE_IND_STRU        *pstModeChangeInd;
    CDS_ENTITY_STRU                     *pstCdsEntity;
    VOS_UINT16                           usModemId;

    /*入参有效性判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_MMC_MsgProc : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_MMC_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    /*Proc Msg*/
    pstModeChangeInd = (MMC_CDS_MODE_CHANGE_IND_STRU *)((VOS_UINT32)pstMsg);

    /*根据Pid获得ModemId,根据ModemId获得Cds实体指针*/
    usModemId = VOS_GetModemIDFromPid(pstModeChangeInd->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,
                       "CDS_MMC_MsgProc : CDS_GetCdsEntity Fail.SenderPid,ModemId",
                       pstModeChangeInd->ulSenderPid,
                       usModemId);
        CDS_PRINT_ERROR2(CDS_MMC_MsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstModeChangeInd->ulSenderPid,
                       usModemId);
        return;
    }

    switch(pstModeChangeInd->enMode)
    {
    case MMC_CDS_MODE_NULL:
        CDS_ChangeRanModeToNULL(pstCdsEntity);
        break;

    case MMC_CDS_MODE_GU:
        CDS_ChangeRanModeToGU(pstCdsEntity);
        break;

    case MMC_CDS_MODE_LTE:
        CDS_ChangeRanModeToLTE(pstCdsEntity);
        break;

    default:
        CDS_ERROR_LOG2(UEPS_PID_CDS,
                       "CDS_MMC_MsgProc:Change Ran Mode Error.ModemId,RanMode:",
                       pstCdsEntity->usModemId,
                       pstModeChangeInd->enMode);
        CDS_PRINT_ERROR2(CDS_MMC_MsgProc_ENUM,CDS_PRINT_GET_ACCESS_MODE_FAIL, pstCdsEntity->usModemId,
                       pstModeChangeInd->enMode);
        break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : CDS_NdStartFilterMsgProc
 功能描述  : 处理ND Client发送的启动下行过滤消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_NdStartFilterMsgProc(const MsgBlock  *pstMsg)
{
    NDCLIENT_CDS_START_FILTER_REQ_STRU   *pstReqMsg;
    CDS_NDCLIENT_START_FILTER_CNF_STRU   *pstCnfMsg;
    VOS_UINT32                            ulMsgLen;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_NdStartFilterMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_NdStartFilterMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstReqMsg = (NDCLIENT_CDS_START_FILTER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->enModemId >= CDS_MAX_MODEM_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdStartFilterMsgProc : ModemId Error. ModemID.",pstReqMsg->enModemId);
        CDS_PRINT_ERROR1(CDS_NdStartFilterMsgProc_ENUM,CDS_PRINT_MODEM_ID_ERR,pstReqMsg->enModemId);
        return;
    }

    ulMsgLen = sizeof(CDS_NDCLIENT_START_FILTER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdStartFilterMsgProc : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_NdStartFilterMsgProc_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        return;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstCnfMsg,UEPS_PID_NDCLIENT);
    pstCnfMsg->ulMsgId = ID_CDS_NDCLIENT_START_FILTER_CNF;

    /*增加ModemId*/
    pstCnfMsg->enModemId = pstReqMsg->enModemId;
    pstCnfMsg->enRslt    = CDS_EnableDlIPFFilter(pstReqMsg->enModemId);

    /*发送消息*/
    CDS_SEND_MSG(pstCnfMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"CDS_NdStartFilterMsgProc: Send Cnf Msg Succ.");
    CDS_PRINT_ERROR(CDS_NdStartFilterMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    return;
}


/*****************************************************************************
 函 数 名  : CDS_NdStopFilterMsgProc
 功能描述  : 处理ND Client发送的停止下行过滤消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_NdStopFilterMsgProc(const MsgBlock  *pstMsg)
{
    NDCLIENT_CDS_STOP_FILTER_REQ_STRU    *pstReqMsg;
    CDS_NDCLIENT_STOP_FILTER_CNF_STRU    *pstCnfMsg;
    VOS_UINT32                            ulMsgLen;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_NdStopFilterMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_NdStopFilterMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstReqMsg = (NDCLIENT_CDS_STOP_FILTER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->enModemId >= CDS_MAX_MODEM_NUM)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdStopFilterMsgProc : ModemId Error. ModemID.",pstReqMsg->enModemId);
        CDS_PRINT_ERROR1(CDS_NdStopFilterMsgProc_ENUM,CDS_PRINT_MODEM_ID_ERR,pstReqMsg->enModemId);
        return;
    }

    ulMsgLen = sizeof(CDS_NDCLIENT_STOP_FILTER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdStopFilterMsgProc : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_NdStopFilterMsgProc_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        return;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstCnfMsg,UEPS_PID_NDCLIENT);
    pstCnfMsg->ulMsgId = ID_CDS_NDCLIENT_STOP_FILTER_CNF;

    /*增加ModemId*/
    pstCnfMsg->enModemId = pstReqMsg->enModemId;
    pstCnfMsg->enRslt    = CDS_DisableDlIPFFilter(pstReqMsg->enModemId);

    /*发送消息*/
    CDS_SEND_MSG(pstCnfMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"CDS_NdStopFilterMsgProc: Send Cnf Msg Succ.");

    CDS_PRINT_ERROR(CDS_NdStopFilterMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    return;

}

/*****************************************************************************
 函 数 名  : CDS_NdDataReqMsgProc
 功能描述  : 处理ND Client发送的数据请求消息，CDS将RS等类型数据转发到核心网
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_NdDataReqMsgProc(MsgBlock  *pstMsg)
{
    NDCLIENT_CDS_DATA_REQ_STRU      *pstDataReq;
    CDS_ENTITY_STRU                 *pstCdsEntity;
    TTF_MEM_ST                      *pstNdPkt;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_NdDataReqMsgProc: Input Para Error.");
        CDS_PRINT_ERROR(CDS_NdDataReqMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstDataReq = (NDCLIENT_CDS_DATA_REQ_STRU *)((VOS_UINT32)pstMsg);

    /*消息内容有效判断*/
    if (VOS_NULL_PTR == pstDataReq->pstIpPacket)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_NdDataReqMsgProc: Packet Pointer NULL.");
        CDS_PRINT_ERROR(CDS_NdDataReqMsgProc_ENUM,LL2_PTR_NULL);
        return;
    }

    if ((CDS_NAS_MIN_BEARER_ID > pstDataReq->ucRabId)
         || (CDS_NAS_MAX_BEARER_ID < pstDataReq->ucRabId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDataReq->pstIpPacket);
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdDataReqMsgProc: Rab Id Error.",pstDataReq->ucRabId);
        CDS_PRINT_ERROR1(CDS_NdDataReqMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,pstDataReq->ucRabId);
        return;
    }

    CDS_DBG_UL_RECV_ND_PKT_NUM(1);

    /*根据ModemId获取CDS实体*/
    pstCdsEntity = CDS_GetCdsEntity(pstDataReq->enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        TTF_MemFree(UEPS_PID_CDS,pstDataReq->pstIpPacket);
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_NdDataReqMsgProc: CDS_GetCdsEntity Error.",pstDataReq->enModemId);
        CDS_PRINT_ERROR1(CDS_NdDataReqMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstDataReq->enModemId);
        return;
    }

    /*将相关信息保存到TTF,在这里RabId就作为过滤的结果*/
    pstNdPkt = pstDataReq->pstIpPacket;
    CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstNdPkt,
                                             pstDataReq->ucRabId,
                                             pstDataReq->enModemId,
                                             pstDataReq->ucRabId);

    /*将ND CLIENT数据作为高优先级数据保存，供PDCP入队使用 by c00253308 20151024 begin*/
    pstNdPkt->ucDataPriority  = TTF_PS_DATA_PRIORITY_HIGH;
    /*将ND CLIENT数据作为高优先级数据保存，供PDCP入队使用 by c00253308 end*/

    CDS_DBG_UL_REC_IP_PKT_INFO(pstNdPkt);
    CDS_DBB_NDCLIENT_DATA_REQ_HOOK(pstNdPkt);

    /*调用接口将数据发送到空口*/
    CDS_UlDispatchDataByRanMode(pstCdsEntity,pstNdPkt);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_NDCLIENT_MsgProc
 功能描述  : 处理收到的NDCLIENT消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_NDCLIENT_MsgProc(MsgBlock  *pstMsg)
{
    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_NDCLIENT_MsgProc : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_NDCLIENT_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_NDCLIENT_CDS_START_FILTER_REQ:
        /*启动下行过滤*/
        CDS_NdStartFilterMsgProc(pstMsg);
        break;

    case ID_NDCLIENT_CDS_STOP_FILTER_REQ:
        /*关闭下行过滤*/
        CDS_NdStopFilterMsgProc(pstMsg);
        break;

    case ID_NDCLIENT_CDS_DATA_REQ:
        /*转发数据到空口*/
        CDS_NdDataReqMsgProc(pstMsg);
        break;

    default:
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_NDCLIENT_MsgProc: Msg Id Error.MsgID=",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_INFO1(CDS_NDCLIENT_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;

    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_RabmSerivceRequestNotify
 功能描述  : CDS通知RABM发起SERVICE REQUEST
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_RabmSerivceRequestNotify(VOS_UINT8 ucRabId, CDS_ENTITY_STRU *pstCdsEntity)
{
    CDS_RABM_SERVICE_IND_STRU   *pstIndMsg;
    VOS_UINT32                   ulMsgLen;

    /*入参判断*/
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_RabmSerivceRequestNotify Input Para Error.");
        CDS_PRINT_ERROR(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return ;
    }

    if ((CDS_NAS_MIN_BEARER_ID > ucRabId) || (CDS_NAS_MAX_BEARER_ID < ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmSerivceRequestNotify: Rab Id Error.",ucRabId);
        CDS_PRINT_ERROR1(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_RAB_ID_ERR,ucRabId);
        return;
    }

    /*已经触发，直接返回*/
    if (PS_TRUE == CDS_GET_GU_RAB_SR_FLG(pstCdsEntity,ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmSerivceRequestNotify: Has Trigger SR..",ucRabId);
        CDS_PRINT_ERROR1(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_TRIGGER_SR_ALREADY,ucRabId);
        return;
    }

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_RabmSerivceRequestNotify.ModemId,RabId",pstCdsEntity->usModemId,ucRabId);
    CDS_PRINT_INFO2(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_PROC_INFO,pstCdsEntity->usModemId,ucRabId);

    ulMsgLen = sizeof(CDS_RABM_SERVICE_IND_STRU);
    pstIndMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstIndMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmSerivceRequestNotify : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        return;
    }

    /*填写消息内容*/
    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        CDS_CFG_MSG_HDR(pstIndMsg,I0_WUEPS_PID_RABM);
    }
    else
    {
        CDS_CFG_MSG_HDR(pstIndMsg,I1_WUEPS_PID_RABM);
    }

    pstIndMsg->enMsgId = ID_CDS_RABM_SERVICE_IND;
    pstIndMsg->ucRabId = ucRabId;

    /*发送消息*/
    CDS_SEND_MSG(pstIndMsg);

    /*设置SR标志*/
    CDS_SET_GU_RAB_SR_FLG(pstCdsEntity,ucRabId);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_RabmSerivceRequestNotify: Send Service Ind Msg Succ.");
    CDS_PRINT_INFO(CDS_RabmSerivceRequestNotify_ENUM,CDS_PRINT_PROC_INFO);

    return;

}

/*****************************************************************************
 函 数 名  : CDS_ProcRabmSendBuffIndMsg
 功能描述  : 处理收到的RABM 发送缓存数据消息，GU不启动二次过滤
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

    2.日    期   : 2012年04月24日
      作    者   : y00151394
      修改内容   : 发送数据前需要先查询GU RABM状态，根据状态操作。
                   见问题单DTS2012033006483.

    3.日    期   : 2012年05月16日
      作    者   : y00151394
      修改内容   : 如果当前为IDLE态且缓存为空应该设置为NORMAL态。
                   见问题单DTS2012051405418.
*****************************************************************************/
VOS_VOID CDS_RabmSendBuffIndMsgProc(const MsgBlock  *pstMsg)
{
    VOS_UINT16                           usModemId;
    CDS_ENTITY_STRU                     *pstCdsEntity;
    CDS_RABM_SEND_BUFF_DATA_IND_STRU    *pstIndMsg;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_RabmSendBuffIndMsgProc.");

    CDS_PRINT_INFO(CDS_RabmSendBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RabmSendBuffIndMsgProc : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_RabmSendBuffIndMsgProc_ENUM,LL2_PTR_NULL);
        return;
    }

    /*根据Pid获得ModemId,根据ModemId获得Cds实体指针*/
    usModemId = VOS_GetModemIDFromPid(pstMsg->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmSendBuffIndMsgProc : Get CDS Enttiy Fail.",usModemId);
        CDS_PRINT_ERROR1(CDS_RabmSendBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,usModemId);
        return;
    }

    pstIndMsg = (CDS_RABM_SEND_BUFF_DATA_IND_STRU *)((VOS_UINT32)pstMsg);

    /*RABID判断*/
    if ((CDS_NAS_MIN_BEARER_ID > pstIndMsg->ucRabId)
         || (CDS_NAS_MAX_BEARER_ID < pstIndMsg->ucRabId))
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_RabmSendBuffIndMsgProc : Rab Id Error.ModemId,RbId",usModemId,pstIndMsg->ucRabId);
        CDS_PRINT_ERROR2(CDS_RabmSendBuffIndMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,usModemId,pstIndMsg->ucRabId);
        return;
    }

    /*清除RAB SR标志*/
    /*lint -e701*/
    CDS_CLR_GU_RAB_SR_FLG(pstCdsEntity,pstIndMsg->ucRabId);
    /*lint +e701*/

    /*将上行缓存发送到RABM*/
    CDS_SendUlBuffDataToRabm(pstCdsEntity,pstIndMsg->ucRabId);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_RabmSendBuffIndMsgProc. ModemId:",usModemId);
    CDS_PRINT_INFO1(CDS_RabmSendBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO,usModemId);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ProcRabmFreeBuffIndMsg
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 功能：处理RABM清空缓存数据消息

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_RabmFreeBuffIndMsgProc(const MsgBlock  *pstMsg)
{
    VOS_UINT16                           usModemId;
    CDS_ENTITY_STRU                     *pstCdsEntity;
    CDS_RABM_FREE_BUFF_DATA_IND_STRU    *pstIndMsg;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_RabmFreeBuffIndMsgProc.");
    CDS_PRINT_INFO(CDS_RabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RabmFreeBuffIndMsgProc : Input Null Para.");
        CDS_PRINT_ERROR(CDS_RabmFreeBuffIndMsgProc_ENUM,LL2_PTR_NULL);
        return;
    }

    /*根据Pid获得ModemId,根据ModemId获得Cds实体指针*/
    usModemId = VOS_GetModemIDFromPid(pstMsg->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RabmFreeBuffIndMsgProc : Get CDS Entity Fail.",usModemId);
        CDS_PRINT_ERROR1(CDS_RabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,usModemId);
        return;
    }

    pstIndMsg = (CDS_RABM_FREE_BUFF_DATA_IND_STRU *)((VOS_UINT32)pstMsg);

    /*RABID判断*/
    if ((CDS_NAS_MIN_BEARER_ID > pstIndMsg->ucRabId)
         || (CDS_NAS_MAX_BEARER_ID < pstIndMsg->ucRabId))
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_RabmFreeBuffIndMsgProc : Rab Id Error.ModemId,RabId",usModemId,pstIndMsg->ucRabId);
        CDS_PRINT_ERROR2(CDS_RabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,usModemId,pstIndMsg->ucRabId);
        return;
    }

    /*清除指定RABID SR标志*/
    /*lint -e701*/
    CDS_CLR_GU_RAB_SR_FLG(pstCdsEntity,pstIndMsg->ucRabId);
    /*lint +e701*/

    /*清空指定RABID上行缓存*/
    CDS_UlGUClearBuffData(pstCdsEntity,pstIndMsg->ucRabId);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_RabmFreeBuffIndMsgProc.ModemID:",usModemId);

    CDS_PRINT_INFO1(CDS_RabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO,usModemId);

    return;
}


/*****************************************************************************
 函 数 名  : CDS_ProcRabmVoicePreferActIndMsg
 功能描述  : 处理RABM VP激活指示
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年12月26日
      作    者   : s00273135
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ProcRabmVoicePreferActIndMsg(const MsgBlock  *pstMsg)
{
    VOS_UINT16                          usModemId;
    CDS_ENTITY_STRU                    *pstCdsEntity;
    RABM_CDS_VOICEPREFER_ACT_IND_STRU  *pstIndMsg;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_ProcRabmVoicePreferActIndMsg.");
    CDS_PRINT_INFO(CDS_ProcRabmVoicePreferActIndMsg_ENUM,CDS_PRINT_PROC_INFO);

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ProcRabmVoicePreferActIndMsg : Input Null Para.");
        CDS_PRINT_ERROR(CDS_ProcRabmVoicePreferActIndMsg_ENUM,LL2_PTR_NULL);
        return;
    }

    /*根据Pid获得ModemId,根据ModemId获得Cds实体指针*/
    usModemId = VOS_GetModemIDFromPid(pstMsg->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ProcRabmVoicePreferActIndMsg : Get CDS Entity Fail.",usModemId);
        CDS_PRINT_ERROR1(CDS_ProcRabmVoicePreferActIndMsg_ENUM,CDS_PRINT_GET_ENTITY_FAIL,usModemId);
        return;
    }

    pstIndMsg = (RABM_CDS_VOICEPREFER_ACT_IND_STRU *)((VOS_UINT32)pstMsg);


    /* 保存VoicePrefer激活标志*/
    CDS_SET_VOICEPREFER_ACT_FLAG(pstCdsEntity,pstIndMsg->ulVoicePreferActInd);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_ProcRabmVoicePreferActIndMsg.ModemID:",usModemId);
    CDS_PRINT_INFO1(CDS_ProcRabmVoicePreferActIndMsg_ENUM,CDS_PRINT_PROC_INFO,usModemId);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_RABM_MsgProc
 功能描述  : 处理收到的RABM消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_RABM_MsgProc(const MsgBlock  *pstMsg)
{
    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RABM_MsgProc : Input Para Null.");
        CDS_PRINT_ERROR(CDS_RABM_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_RABM_CDS_FREE_BUFF_DATA_IND:
        CDS_RabmFreeBuffIndMsgProc(pstMsg);
        break;

    case ID_RABM_CDS_SEND_BUFF_DATA_IND:
        CDS_RabmSendBuffIndMsgProc(pstMsg);
        break;

    case ID_QOS_FC_RABM_RAB_CREATE_IND:
        QosFc_RabCreate(pstMsg);
        break;

    case ID_QOS_FC_RABM_RAB_RELEASE_IND:
        QosFc_RabRelease(pstMsg);
        break;

    case ID_RABM_CDS_VOICEPREFER_ACT_IND:
        CDS_ProcRabmVoicePreferActIndMsg(pstMsg);
        break;

    default:
        CDS_INFO_LOG1(UEPS_PID_CDS,"CDS_RABM_MsgProc : Recv Rabm Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_INFO1(CDS_RABM_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_TmrMsgProc
 功能描述  : 处理定时器消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_TmrMsgProc(const MsgBlock  *pstMsg)
{
    REL_TIMER_MSG         *pstTmrMsg;

    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_TmrMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_TmrMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstTmrMsg = (REL_TIMER_MSG *)((VOS_UINT32)pstMsg);

    switch(pstTmrMsg->ulName)
    {
    case CDS_TMR_ID_DL_10MS_PERIODIC_TMR:
        CDS_Dl10msPeridicTmrTimeoutProc(pstTmrMsg);
        break;

    case CDS_TMR_ID_FC_CHECK_TMR:
        /* 流控状态check */
        QosFc_FlowCtrl();
        break;

    case CDS_TMR_ID_LB_MODE_B_TMR:
        CDS_LoopBackModeBTimeoutProc(pstTmrMsg);
        break;

    case CDS_TMR_ID_ADQ_EMPTY_PROCTECT:
        CDS_AdqEmptyProctectTimeOutProc();
        break;

    case CDS_TMR_ID_UL_DATA_PROCTECT:
        CDS_UlDataProtectTmrTimeoutProc(pstTmrMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_TmrMsgProc : Tmr Msg Name Error.",pstTmrMsg->ulName);
        break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : CDS_DhcpDataReqMsgProc
 功能描述  : 处理DHCP发送的数据请求消息，CDS将RS等类型数据转发到核心网
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月10日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DhcpDataReqMsgProc(MsgBlock  *pstMsg)
{
    DHCP_CDS_DATA_REQ_STRU          *pstDataReq;
    CDS_ENTITY_STRU                 *pstCdsEntity;
    TTF_MEM_ST                      *pstDhcpPkt;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstDataReq = (DHCP_CDS_DATA_REQ_STRU *)((VOS_UINT32)pstMsg);

    /*消息内容有效判断*/
    if (VOS_NULL_PTR == pstDataReq->pstIpPacket)
    {
        return;
    }

    if ((CDS_NAS_MIN_BEARER_ID > pstDataReq->ucRabId)
         || (CDS_NAS_MAX_BEARER_ID < pstDataReq->ucRabId))
    {
        TTF_MemFree(UEPS_PID_CDS,pstDataReq->pstIpPacket);
        return;
    }

    CDS_DBG_UL_RECV_DHCP_PKT_NUM(1);

    /*根据ModemId获取CDS实体*/
    pstCdsEntity = CDS_GetCdsEntity(pstDataReq->enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        TTF_MemFree(UEPS_PID_CDS,pstDataReq->pstIpPacket);
        return;
    }

    /*将相关信息保存到TTF,在这里RabId就作为过滤的结果*/
    pstDhcpPkt = pstDataReq->pstIpPacket;
    CDS_UL_SAVE_IPFRSLT_MODEMID_RABID_TO_TTF(pstDhcpPkt,
                                             pstDataReq->ucRabId,
                                             pstDataReq->enModemId,
                                             pstDataReq->ucRabId);

    /*将DHCP数据作为高优先级数据保存，供PDCP入队使用 by c00253308 20151024 begin*/
    pstDhcpPkt->ucDataPriority  = TTF_PS_DATA_PRIORITY_HIGH;
    /*将DHCP数据作为高优先级数据保存，供PDCP入队使用 by c00253308 20151024 end*/

    CDS_DBG_UL_REC_IP_PKT_INFO(pstDhcpPkt);
    CDS_DBG_DHCP_DATA_REQ_HOOK(pstDhcpPkt);

    /*调用接口将数据发送到空口*/
    CDS_UlDispatchDataByRanMode(pstCdsEntity,pstDhcpPkt);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_DhcpStartFilterMsgProc
 功能描述  : 处理DHCP发送的启动下行过滤消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月10日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DhcpStartFilterMsgProc(MsgBlock  *pstMsg)
{
    DHCP_CDS_START_FILTER_REQ_STRU       *pstReqMsg;
    CDS_DHCP_START_FILTER_CNF_STRU       *pstCnfMsg;
    VOS_UINT32                            ulMsgLen;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstReqMsg = (DHCP_CDS_START_FILTER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->enModemId >= CDS_MAX_MODEM_NUM)
    {
        return;
    }

    ulMsgLen = sizeof(CDS_DHCP_START_FILTER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        return;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstCnfMsg,UEPS_PID_DHCP);
    pstCnfMsg->enMsgId = ID_CDS_DHCP_START_FILTER_CNF;

    /*增加ModemId*/
    pstCnfMsg->enModemId = pstReqMsg->enModemId;
    pstCnfMsg->enRslt    = CDS_EnableDlIPFFilter(pstReqMsg->enModemId);

    /*发送消息*/
    CDS_SEND_MSG(pstCnfMsg);


    return;
}


/*****************************************************************************
 函 数 名  : CDS_DhcpStopFilterMsgProc
 功能描述  : 处理DHCP发送的停止下行过滤消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月10日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DhcpStopFilterMsgProc(MsgBlock  *pstMsg)
{
    DHCP_CDS_STOP_FILTER_REQ_STRU        *pstReqMsg;
    CDS_DHCP_STOP_FILTER_CNF_STRU        *pstCnfMsg;
    VOS_UINT32                            ulMsgLen;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstReqMsg = (DHCP_CDS_STOP_FILTER_REQ_STRU *)((VOS_UINT32)pstMsg);
    if (pstReqMsg->enModemId >= CDS_MAX_MODEM_NUM)
    {
        return;
    }

    ulMsgLen = sizeof(CDS_DHCP_STOP_FILTER_CNF_STRU);
    pstCnfMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstCnfMsg)
    {
        return;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstCnfMsg,UEPS_PID_DHCP);
    pstCnfMsg->enMsgId = ID_CDS_DHCP_STOP_FILTER_CNF;

    /*增加ModemId*/
    pstCnfMsg->enModemId = pstReqMsg->enModemId;
    pstCnfMsg->enRslt    = CDS_DisableDlIPFFilter(pstReqMsg->enModemId);

    /*发送消息*/
    CDS_SEND_MSG(pstCnfMsg);


    return;

}

/*****************************************************************************
 函 数 名  : CDS_DHCP_MsgProc
 功能描述  : 处理收到的DHCP消息
 输入参数  : const MsgBlock  *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年06月10日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DHCP_MsgProc(MsgBlock  *pstMsg)
{
    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_DHCP_CDS_DATA_REQ:
        CDS_DhcpDataReqMsgProc(pstMsg);
        break;

    case ID_DHCP_CDS_START_FILTER_REQ:
        CDS_DhcpStartFilterMsgProc(pstMsg);
        break;

    case ID_DHCP_CDS_STOP_FILTER_REQ:
        CDS_DhcpStopFilterMsgProc(pstMsg);
        break;

    default:
        break;
    }
    return;
}


#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
/*****************************************************************************
 函 数 名  : CDS_ERabmSerivceRequestNotify
 功能描述  : CDS通知ERABM发起SERVICE REQUEST
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ERabmSerivceRequestNotify(VOS_UINT8 ucEpsbId)
{
    CDS_ERABM_SERVICE_NOTIFY_STRU   *pstNotifyMsg;
    VOS_UINT32                       ulMsgLen;

    /*入参判断*/
    if ((CDS_NAS_MIN_BEARER_ID > ucEpsbId) || (CDS_NAS_MAX_BEARER_ID < ucEpsbId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ERabmSerivceRequestNotify: EpsbId Error.",ucEpsbId);
        CDS_PRINT_ERROR1(CDS_ERabmSerivceRequestNotify_ENUM,CDS_PRINT_EPSB_ID_ERR,ucEpsbId);
        return;
    }

    CDS_INFO_LOG1(UEPS_PID_CDS,"Enter CDS_ERabmSerivceRequestNotify.EpsbId:",ucEpsbId);
    CDS_PRINT_INFO1(CDS_ERabmSerivceRequestNotify_ENUM,CDS_PRINT_PROC_INFO,ucEpsbId);

    ulMsgLen = sizeof(CDS_ERABM_SERVICE_NOTIFY_STRU);
    pstNotifyMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstNotifyMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ERabmSerivceRequestNotify : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_ERabmSerivceRequestNotify_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
       return;
    }

    /*填写消息内容*/
    CDS_CFG_MSG_HDR(pstNotifyMsg,PS_PID_RABM);
    pstNotifyMsg->ulMsgId = ID_CDS_ERABM_SERVICE_NOTIFY;

    pstNotifyMsg->ucRabId = ucEpsbId;

    /*发送消息*/
    CDS_SEND_MSG(pstNotifyMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_ERabmSerivceRequestNotify: Send Service Ind Msg Succ.");
    CDS_PRINT_INFO(CDS_ERabmSerivceRequestNotify_ENUM,CDS_PRINT_PROC_INFO);

    return;


}

/*****************************************************************************
 函 数 名  : CDS_ProcERabmSendBuffIndMsg
 功能描述  : 处理收到的ERABM 发送缓存数据消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ERabmSendBuffIndMsgProc(MsgBlock  *pstMsg)
{
    ERABM_CDS_SEND_BUFF_DATA_IND_STRU    *pstSendBufInd;
    CDS_ENTITY_STRU                      *pstCdsEntity;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERabmSendBuffIndMsgProc : Input Null Para.");
        CDS_PRINT_ERROR(CDS_ERabmSendBuffIndMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstSendBufInd = (ERABM_CDS_SEND_BUFF_DATA_IND_STRU*)((VOS_UINT32)pstMsg);

    CDS_INFO_LOG1(UEPS_PID_CDS,
                  "CDS_ERabmSendBuffIndMsgProc: Send Data Allowed Type .",
                  pstSendBufInd->enSndBuffDataAllowedType);
    CDS_PRINT_INFO1(CDS_ERabmSendBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO,pstSendBufInd->enSndBuffDataAllowedType);

    /*根据ModemId获得CDS实体指针，LNAS默认部署在Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERabmSendBuffIndMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_ERabmSendBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return;
    }

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*发送上行缓存数据*/
    CDS_SendUlBuffData(pstCdsEntity);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ProcERabmFreeBuffIndMsg
 功能描述  : 处理ERABM 清空缓存数据消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ERabmFreeBuffIndMsgProc(const MsgBlock  *pstMsg)
{
    CDS_ENTITY_STRU                      *pstCdsEntity;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERabmFreeBuffIndMsgProc : Input Null Para");
        CDS_PRINT_ERROR(CDS_ERabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_ERabmFreeBuffIndMsgProc");
    CDS_PRINT_INFO(CDS_ERabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_PROC_INFO);

    /*根据ModemId获得CDS实体指针，LNAS默认部署在Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERabmFreeBuffIndMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_ERabmFreeBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return;
    }

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*清空上行缓存数据*/
    CDS_ClearUlBuffData(pstCdsEntity);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ERABM_MsgProc
 功能描述  : 处理收到的ERABM消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ERABM_MsgProc(MsgBlock  *pstMsg)
{
    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ERABM_MsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_ERABM_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_ERABM_CDS_FREE_BUFF_DATA_IND:
        CDS_ERabmFreeBuffIndMsgProc(pstMsg);
        break;

    case ID_ERABM_CDS_SEND_BUFF_DATA_IND:
        CDS_ERabmSendBuffIndMsgProc(pstMsg);
        break;

    case ID_QOS_FC_ERABM_RAB_CREATE_IND:
        QosFc_RabCreate(pstMsg);
        break;

    case ID_QOS_FC_ERABM_RAB_RELEASE_IND:
        QosFc_RabRelease(pstMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ERABM_MsgProc : Recv Erabm Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_ERROR1(CDS_ERABM_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : CDS_GetTestMode
 功能描述  : 获得当前测试模式
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
CDS_TEST_MODE_ENUM_UINT32 CDS_GetTestMode(VOS_VOID)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    /*根据ModemId获得CDS实体指针，LB默认部署在Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_GetTestMode : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_GetTestMode_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return CDS_TEST_MODE_BUTT;
    }

    /*返回CDS实体的环回模式*/
    if (PS_TRUE == pstCdsEntity->ulTestModeFlg)
    {
        return CDS_TEST_MODE_ACTIVATED;
    }
    else
    {
        return CDS_TEST_MODE_DEACTIVATED;
    }
}

/*****************************************************************************
 函 数 名  : CDS_ActLookBackMsgProc
 功能描述  : 激活环回模式消息处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ActLookBackMsgProc(const MsgBlock  *pstMsg)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    /*入参有效性判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ActLookBackMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_ActLookBackMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_ActLookBackMsgProc");
    CDS_PRINT_INFO(CDS_ActLookBackMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    /*根据ModemId获得CDS实体指针，LB默认部署在Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ActLookBackMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_ActLookBackMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return ;
    }

    /* 流控进入环回模式处理 */
    Fc_SwitchToNull();

    /*设置环回模式标志位为PS_TRUE*/
    pstCdsEntity->ulTestModeFlg = PS_TRUE;
    pstCdsEntity->ulLoopBackState = CDS_LB_STATE_ACTIVE;

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*清空上行缓存*/
    CDS_ClearUlBuffData(pstCdsEntity);

    /*清空环回队列*/
    CDS_ClearLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_ActLookBackMsgProc");
    CDS_PRINT_INFO(CDS_ActLookBackMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_DeactLookBackMsgProc
 功能描述  : 去激活环回模式消息处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DeactLookBackMsgProc(const MsgBlock  *pstMsg)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    /*入参有效性判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_DeactLookBackMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_DeactLookBackMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_DeactLookBackMsgProc");

    CDS_PRINT_INFO(CDS_DeactLookBackMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    /*根据ModemId获得CDS实体指针，LB默认部署在Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_DeactLookBackMsgProc : Get CDS Entity Fail.");
        CDS_PRINT_ERROR(CDS_DeactLookBackMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL);
        return ;
    }

    /* 流控退出环回模式处理 */
    if (MMC_CDS_MODE_LTE == pstCdsEntity->enRanMode)
    {
        Fc_SwitchToLte();
    }
    else if (MMC_CDS_MODE_GU == pstCdsEntity->enRanMode)
    {
        Fc_SwitchToGu();
    }
    else
    {
        /* 不处理 */
    }

    /*设置环回模式标志位为PS_FALSE*/
    pstCdsEntity->ulTestModeFlg = PS_FALSE;
    pstCdsEntity->ulLoopBackState = CDS_LB_STATE_DEACTIVE;

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*清空上行缓存*/
    CDS_ClearUlBuffData(pstCdsEntity);

    /*清空环回队列*/
    CDS_ClearLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_DeactLookBackMsgProc");

    CDS_PRINT_INFO(CDS_DeactLookBackMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_LBStartTestLoopMsgProc
 功能描述  : 处理环回Test Loop Start消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年09月17日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_StartLBTestLoopMsgProc(const MsgBlock  *pstMsg)
{
    ETC_CDS_START_TEST_LOOP_NOTIFY_STRU  *pstStartTLMsg;
    CDS_ENTITY_STRU                      *pstCdsEntity;

    /*入参有效性判断*/
    CDS_ASSERT(VOS_NULL_PTR != pstMsg);

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_StartLBTestLoopMsgProc");

    CDS_PRINT_INFO(CDS_StartLBTestLoopMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    /*根据ModemId获得CDS实体指针，LB默认部署在Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_StartLBTestLoopMsgProc : Get CDS_GetCdsEntity Fail.ModemId:",MODEM_ID_0);
        CDS_PRINT_ERROR1(CDS_StartLBTestLoopMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,MODEM_ID_0);
        return ;
    }

    pstStartTLMsg = (ETC_CDS_START_TEST_LOOP_NOTIFY_STRU*)((VOS_VOID*)pstMsg);

    CDS_INFO_LOG2(UEPS_PID_CDS,"CDS_StartLBTestLoopMsgProc : LB Mode,Timer Len.",pstStartTLMsg->ulLBMode,pstStartTLMsg->ulLBModeBTmrLen);

    CDS_PRINT_INFO2(CDS_StartLBTestLoopMsgProc_ENUM,CDS_PRINT_PROC_INFO,pstStartTLMsg->ulLBMode,pstStartTLMsg->ulLBModeBTmrLen);

    /*保持环回模式信息*/
    if (CDS_ETC_LB_MODE_B == pstStartTLMsg->ulLBMode)
    {
        pstCdsEntity->ulLoopBackMode = CDS_LB_MODE_B;
        if (0 != pstStartTLMsg->ulLBModeBTmrLen)
        {
            CDS_SET_TMR_LEN(pstCdsEntity,
                            CDS_TMR_ID_LB_MODE_B_TMR,
                            pstStartTLMsg->ulLBModeBTmrLen * 1000);
        }
        else
        {
            /*定时器时长为0，则按10ms计算*/
            CDS_SET_TMR_LEN(pstCdsEntity,
                            CDS_TMR_ID_LB_MODE_B_TMR,
                            CDS_TMR_LEN);
        }
    }
    else
    {
        pstCdsEntity->ulLoopBackMode = CDS_LB_MODE_A;
        CDS_SET_TMR_LEN(pstCdsEntity,CDS_TMR_ID_LB_MODE_B_TMR,0);
    }

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;
    pstCdsEntity->ulLoopBackState = CDS_LB_STATE_START;

    /*清空环回队列*/
    CDS_ClearLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_StartLBTestLoopMsgProc");
     CDS_PRINT_INFO(CDS_StartLBTestLoopMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_StopLBTestLoopMsgProc
 功能描述  : 处理环回Test Loop Stop消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年09月17日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_StopLBTestLoopMsgProc(const MsgBlock  *pstMsg)
{
    CDS_ENTITY_STRU                      *pstCdsEntity;

    /*入参有效性判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_StopLBTestLoopMsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_StopLBTestLoopMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_StopLBTestLoopMsgProc");
    CDS_PRINT_INFO(CDS_StopLBTestLoopMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    /*根据ModemId获得CDS实体指针，LB默认部署在Modem0*/
    pstCdsEntity = CDS_GetCdsEntity(MODEM_ID_0);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_StartLBTestLoopMsgProc : Get CDS_GetCdsEntity Fail.ModemId:",MODEM_ID_0);
        CDS_PRINT_ERROR1(CDS_StopLBTestLoopMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,MODEM_ID_0);
        return ;
    }

    /*获得LB对应信息*/
    pstCdsEntity->ulLoopBackMode = CDS_LB_MODE_BUTT;
    CDS_SET_TMR_LEN(pstCdsEntity,CDS_TMR_ID_LB_MODE_B_TMR,0);

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;
    pstCdsEntity->ulLoopBackState = CDS_LB_STATE_STOP;

    /*清空环回队列*/
    CDS_ClearLoopBackQue(pstCdsEntity);

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_StopLBTestLoopMsgProc");
    CDS_PRINT_INFO(CDS_StopLBTestLoopMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_ETC_MsgProc
 功能描述  : 处理收到的ETC消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ETC_MsgProc(const MsgBlock  *pstMsg)
{
    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ETC_MsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_ETC_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_ETC_CDS_ACT_TEST_MODE_NOTIFY:
        CDS_ActLookBackMsgProc(pstMsg);
        break;

    case ID_ETC_CDS_DEACT_TEST_MODE_NOTIFY:
        CDS_DeactLookBackMsgProc(pstMsg);
        break;

    case ID_ETC_CDS_START_TEST_LOOP_NOTIFY:
        CDS_StartLBTestLoopMsgProc(pstMsg);
        break;

    case ID_ETC_CDS_STOP_TEST_LOOP_NOTIFY:
        CDS_StopLBTestLoopMsgProc(pstMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_ETC_MsgProc : Recv ETC Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_ERROR1(CDS_ETC_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}

#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
/*****************************************************************************
 函 数 名  : CDS_APSServiceRequestNotify
 功能描述  : CDS通知APS发起SERVICE REQUEST
 输入参数  : VOS_UINT8 ucRabId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年10月25日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_APSServiceRequestNotify(CDS_ENTITY_STRU *pstCdsEntity, VOS_UINT8 ucRabId)
{
    CDS_APS_CDATA_SERVICE_IND_STRU                *pstNotifyMsg;
    VOS_UINT32                                     ulMsgLen;

    /*入参判断*/
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_APSServiceRequestNotify Input Para Error.");
        CDS_PRINT_ERROR(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return ;
    }

    if ((CDS_NAS_MIN_BEARER_ID > ucRabId) || (CDS_NAS_MAX_BEARER_ID < ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_APSServiceRequestNotify: ucRabId Error.",ucRabId);
        CDS_PRINT_ERROR1(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_RAB_ID_ERR,ucRabId);
        return;
    }

    /*已经触发，直接返回*/
    if (PS_TRUE == CDS_GET_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_APSServiceRequestNotify: Has Trigger SR..",ucRabId);
        CDS_PRINT_ERROR1(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_TRIGGER_SR_ALREADY,ucRabId);
        return;
    }

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_APSServiceRequestNotify.ModemId,RabId",pstCdsEntity->usModemId,ucRabId);
    CDS_PRINT_INFO2(CDS_APSServiceRequestNotify_ENUM, CDS_PRINT_ENTER_FUC_INFO,pstCdsEntity->usModemId,ucRabId);


    ulMsgLen = sizeof(CDS_APS_CDATA_SERVICE_IND_STRU);
    pstNotifyMsg = CDS_ALLOC_MSG_WITH_HDR(ulMsgLen);
    if (VOS_NULL_PTR == pstNotifyMsg)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_APSServiceRequestNotify : Alloc Msg Fail. Size .",ulMsgLen);
        CDS_PRINT_ERROR1(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_MEM_ALLOC_FAIL,ulMsgLen);
        return;
    }

    /*填写消息内容*/
    if (MODEM_ID_0 == pstCdsEntity->usModemId)
    {
        CDS_CFG_MSG_HDR(pstNotifyMsg, I0_WUEPS_PID_TAF);
    }
    else if (MODEM_ID_1 == pstCdsEntity->usModemId)
    {
        CDS_CFG_MSG_HDR(pstNotifyMsg, I1_WUEPS_PID_TAF);
    }
    else
    {
        CDS_CFG_MSG_HDR(pstNotifyMsg, I2_WUEPS_PID_TAF);
    }
    pstNotifyMsg->enMsgId = ID_CDS_APS_CDATA_SERVICE_IND;
    pstNotifyMsg->ucRabId = ucRabId;

    /*发送消息*/
    CDS_SEND_MSG(pstNotifyMsg);

    /*设置SR标志*/
    CDS_SET_CDMA_RAB_SR_FLG(pstCdsEntity,ucRabId);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_APSServiceRequestNotify: Send Service Ind Msg Succ.");
    CDS_PRINT_INFO(CDS_APSServiceRequestNotify_ENUM,CDS_PRINT_PROC_INFO);
    return;

}

/*****************************************************************************
 函 数 名  : CDS_APSSendBuffIndMsgProc
 功能描述  : 处理APS 发送缓存数据消息
 输入参数  : MsgBlock  *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年10月25日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_APSSendBuffIndMsgProc(MsgBlock  *pstMsg)
{
    APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU         *pstSendBufInd;
    CDS_ENTITY_STRU                               *pstCdsEntity;
    VOS_UINT16                                     enModemId;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_APSSendBuffIndMsgProc : Input Null Para.");
        CDS_PRINT_ERROR(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_APSSendBuffIndMsgProc");
    CDS_PRINT_INFO(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    pstSendBufInd = (APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU*)((VOS_UINT32)pstMsg);

    /* 根据Pid 获得ModemId, 根据ModemId 获得CDS实体指针*/
    enModemId = VOS_GetModemIDFromPid(pstSendBufInd->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_APSSendBuffIndMsgProc : Get CDS Entity Fail.SenderPid,ModemId",
                       pstSendBufInd->ulSenderPid,
                       enModemId);
        CDS_PRINT_ERROR2(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstSendBufInd->ulSenderPid,
                       enModemId);
        return;
    }

    /*RABID判断*/
    if ((CDS_NAS_MIN_BEARER_ID > pstSendBufInd->ucRabId) || (CDS_NAS_MAX_BEARER_ID < pstSendBufInd->ucRabId))
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_APSSendBuffIndMsgProc : Rab Id Error.ModemId,RabId",enModemId,pstSendBufInd->ucRabId);
        CDS_PRINT_ERROR2(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,enModemId,pstSendBufInd->ucRabId);
        return;
    }

    /*清空指定RAB SR标志*/
    CDS_CLR_CDMA_RAB_SR_FLG(pstCdsEntity,pstSendBufInd->ucRabId);

    /*发送指定RAB 上行缓存*/
    CDS_CDMASendUlBuffData(pstCdsEntity,pstSendBufInd->ucRabId);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_APSSendBuffIndMsgProc. ModemId:",enModemId);
    CDS_PRINT_INFO1(CDS_APSSendBuffIndMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO,enModemId);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_APSFreeBuffIndMsgProcs
 功能描述  : 处理APS清空缓存数据消息
 输入参数  : MsgBlock  *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年10月25日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_APSFreeBuffIndMsgProc(const MsgBlock  *pstMsg)
{
    APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU          *pstFreeBufInd;
    CDS_ENTITY_STRU                                *pstCdsEntity;
    VOS_UINT16                                      enModemId;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_APSFreeBuffIndMsgProc : Input Null Para.");
        CDS_PRINT_ERROR(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter CDS_APSFreeBuffIndMsgProc");
    CDS_PRINT_INFO(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_ENTER_FUC_INFO);

    pstFreeBufInd = (APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *)((VOS_UINT32)pstMsg);

    /* 根据Pid 获得ModemId, 根据ModemId 获得CDS实体指针*/
    enModemId = VOS_GetModemIDFromPid(pstFreeBufInd->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_APSFreeBuffIndMsgProc : Get CDS Entity Fail.SenderPid,ModemId",
                       pstFreeBufInd->ulSenderPid,
                       enModemId);
        CDS_PRINT_ERROR2(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstFreeBufInd->ulSenderPid,
                       enModemId);
        return;
    }

    /*RABID判断*/
    if ((CDS_NAS_MIN_BEARER_ID > pstFreeBufInd->ucRabId) || (CDS_NAS_MAX_BEARER_ID < pstFreeBufInd->ucRabId))
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_APSFreeBuffIndMsgProc : Rab Id Error.ModemId,RabId",enModemId,pstFreeBufInd->ucRabId);
        CDS_PRINT_ERROR2(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_RAB_ID_ERR,enModemId,pstFreeBufInd->ucRabId);
        return;
    }

    /*清空指定RAB SR标志*/
    CDS_CLR_CDMA_RAB_SR_FLG(pstCdsEntity,pstFreeBufInd->ucRabId);

    /*清空指定RAB 上行缓存数据*/
    CDS_UlGUClearBuffData(pstCdsEntity,pstFreeBufInd->ucRabId);

    CDS_INFO_LOG1(UEPS_PID_CDS,"Leave CDS_APSFreeBuffIndMsgProc. ModemId:",enModemId);

    CDS_PRINT_INFO1(CDS_APSFreeBuffIndMsgProc_ENUM,CDS_PRINT_LEAVE_FUC_INFO,enModemId);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ChangeRanModeToCDMA
 功能描述  : 将当前接入模式切换到CDMA
 输入参数  : MsgBlock  *pstMsgS
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年10月25日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ChangeRanModeToCDMA(CDS_ENTITY_STRU *pstCdsEntity,APS_CDS_MODE_ENUM_UINT32 enMode)
{
    //APS_CDS_MODE_ENUM_UINT32               PreRanMode;

    /*入参判断*/
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_INFO_LOG(UEPS_PID_CDS,"CDS_ChangeRanModeToCDMA Input Para Error.");
        CDS_PRINT_ERROR(CDS_ChangeRanModeToCDMA_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return ;
    }

    CDS_INFO_LOG2(UEPS_PID_CDS,"Enter CDS_ChangeRanModeToCDMA. ModemId,PreRanMode :",pstCdsEntity->usModemId,pstCdsEntity->enRanMode);
    CDS_PRINT_INFO2(CDS_ChangeRanModeToCDMA_ENUM,CDS_PRINT_ENTER_FUC_INFO,pstCdsEntity->usModemId,pstCdsEntity->enRanMode);

    //PreRanMode = pstCdsEntity->enRanMode;
    pstCdsEntity->enRanMode = enMode;

    /*清空Service Request标志*/
    pstCdsEntity->ulServiceReqFlg = PS_FALSE;

    /*重置CDMA RAB SR标志*/
    CDS_CLR_CDMA_ALL_RAB_SR_FLG(pstCdsEntity);

    /*停止NULL下行10ms周期性定时器*/
    CDS_StopTimer(pstCdsEntity,CDS_TMR_ID_DL_10MS_PERIODIC_TMR);

    /*发送所有承载的上行缓存数据*/
    CDS_CDMASendUlBuffData(pstCdsEntity,CDS_NAS_ALL_BEARER_ID);

    CDS_INFO_LOG(UEPS_PID_CDS,"Leave CDS_ChangeRanModeToCDMA Succ.");
    CDS_PRINT_INFO(CDS_ChangeRanModeToCDMA_ENUM,CDS_PRINT_LEAVE_FUC_INFO);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_APS_ChangeRanModeMsgProc
 功能描述  : 处理收到的接入模式变更消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年 11月 05日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_APS_ChangeRanModeMsgProc(MsgBlock  *pstMsg)
{
    APS_CDS_MODE_CHANGE_IND_STRU        *pstModeChangeInd;
    CDS_ENTITY_STRU                     *pstCdsEntity;
    VOS_UINT16                           usModemId;

    /*入参有效性判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_ChangeRanModeMsgProc : Input NULL Para.");
        CDS_PRINT_ERROR(CDS_APS_ChangeRanModeMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    /*Proc Msg*/
    pstModeChangeInd = (APS_CDS_MODE_CHANGE_IND_STRU *)((VOS_UINT32)pstMsg);

    /*根据Pid获得ModemId,根据ModemId获得Cds实体指针*/
    usModemId = VOS_GetModemIDFromPid(pstModeChangeInd->ulSenderPid);
    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        CDS_ERROR_LOG2(UEPS_PID_CDS,
                       "CDS_ChangeRanModeMsgProc : CDS_GetCdsEntity Fail.SenderPid,ModemId",
                       pstModeChangeInd->ulSenderPid,
                       usModemId);
        CDS_PRINT_ERROR2(CDS_APS_ChangeRanModeMsgProc_ENUM,CDS_PRINT_GET_ENTITY_FAIL,pstModeChangeInd->ulSenderPid,
                       usModemId);
        return;
    }

    switch(pstModeChangeInd->enMode)
    {
    case APS_CDS_MODE_NULL:
        CDS_ChangeRanModeToNULL(pstCdsEntity);
        break;

    case APS_CDS_MODE_GU:
        CDS_ChangeRanModeToGU(pstCdsEntity);
        break;

    case APS_CDS_MODE_LTE:
        CDS_ChangeRanModeToLTE(pstCdsEntity);
        break;

    case APS_CDS_MODE_1X:
    case APS_CDS_MODE_EVDO:
        CDS_ChangeRanModeToCDMA(pstCdsEntity,pstModeChangeInd->enMode);
        break;

    default:
        CDS_ERROR_LOG2(UEPS_PID_CDS,"CDS_ChangeRanModeMsgProc:Change Ran Mode Error.ModemId,RanMode:",
                       pstCdsEntity->usModemId,
                       pstModeChangeInd->enMode);
        CDS_PRINT_ERROR2(CDS_APS_ChangeRanModeMsgProc_ENUM,CDS_PRINT_GET_ACCESS_MODE_FAIL, pstCdsEntity->usModemId,
                       pstModeChangeInd->enMode);
        break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_APS_MsgProc
 功能描述  : 处理收到的APS消息
 输入参数  : MsgBlock  *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年10月25日
      作    者   : l00304941
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_APS_MsgProc(MsgBlock  *pstMsg)
{
    APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU         *pstSendBufInd;

    /*入参判断*/
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_APS_MsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_APS_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    pstSendBufInd = (APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU*)((VOS_UINT32)pstMsg);

    switch(pstSendBufInd->enMsgId)
    {
    case ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND:
        CDS_APSSendBuffIndMsgProc(pstMsg);
        break;

    case ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND:
        CDS_APSFreeBuffIndMsgProc(pstMsg);
        break;

    case ID_APS_CDS_MODE_CHANGE_IND:
        CDS_APS_ChangeRanModeMsgProc(pstMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_APS_MsgProc : Recv APS Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_ERROR1(CDS_APS_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}

#endif

/*****************************************************************************
 函 数 名  : CDS_UMTS_TrigEvenTresMsgProc
 功能描述  : 获取消息开会中的ulDlTrigEventThres
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年6月14日
      作    者   : t148005
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_UMTS_TrigEvenTresMsgProc(const MsgBlock  *pstMsg)
{
    (VOS_VOID)pstMsg;
    return;
}

/*****************************************************************************
 函 数 名  : CDS_UMTS_TrigEvenTresMsgProc
 功能描述  : FcACore消息处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年6月14日
      作    者   : t148005
      修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CDS_FcACore_MsgProc(const MsgBlock  *pstMsg)
{
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_FcA_MsgProc : Input Para Error.");
        CDS_PRINT_ERROR(CDS_FcACore_MsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_NAME(pstMsg))
    {
    case ID_FC_CDS_DL_THRES_CHG_IND:
        /*lint -e522*/
        CDS_UMTS_TrigEvenTresMsgProc(pstMsg);
        /*lint +e522*/
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_FcA_MsgProc : Recv FcACore Msg Id Error.",TTF_GET_MSG_NAME(pstMsg));
        CDS_PRINT_ERROR1(CDS_FcACore_MsgProc_ENUM,CDS_PRINT_GET_MSG_ID_FAIL,TTF_GET_MSG_NAME(pstMsg));
        break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : CDS_RecvMsgProc
 功能描述  : 对CDS收到的消息进行分发处理
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_RecvMsgProc(MsgBlock  *pstMsg)
{
    if (VOS_NULL_PTR == pstMsg)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"CDS_RecvMsgProc : Input Para NULL.");
        CDS_PRINT_ERROR(CDS_RecvMsgProc_ENUM,CDS_PRINT_PARA_INPUT_ERR);
        return;
    }

    switch(TTF_GET_MSG_SENDER_PID(pstMsg))
    {
    case I0_WUEPS_PID_MMC:
    case I1_WUEPS_PID_MMC:
    case I2_WUEPS_PID_MMC:
        CDS_MSG_HOOK(pstMsg);
        CDS_MMC_MsgProc(pstMsg);
        break;

    case UEPS_PID_NDCLIENT:
        CDS_MSG_HOOK(pstMsg);
        CDS_NDCLIENT_MsgProc(pstMsg);
        break;

    case I0_WUEPS_PID_RABM:
    case I1_WUEPS_PID_RABM:
    case I2_WUEPS_PID_RABM:
        CDS_MSG_HOOK(pstMsg);
        CDS_RABM_MsgProc(pstMsg);
        break;

    case DOPRA_PID_TIMER:
        CDS_TmrMsgProc(pstMsg);
        break;

    case ACPU_PID_FC:
        CDS_FcACore_MsgProc(pstMsg);
        break;

    case PS_PID_IMSA:
        CDS_MSG_HOOK(pstMsg);
        CDS_IMSA_MsgProc(pstMsg);
        break;

#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
    case UEPS_PID_BASTET:
        CDS_MSG_HOOK(pstMsg);
        CDS_BST_MsgProc(pstMsg);
        break;
#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
    case PS_PID_RABM:
        CDS_MSG_HOOK(pstMsg);
        CDS_ERABM_MsgProc(pstMsg);
        break;

    case PS_PID_TC:
        CDS_MSG_HOOK(pstMsg);
        CDS_ETC_MsgProc(pstMsg);
        break;
#endif

#if (CDS_FEATURE_ON == CDS_FEATURE_CDMA)
    case I0_WUEPS_PID_TAF:
    case I1_WUEPS_PID_TAF:
    case I2_WUEPS_PID_TAF:
        CDS_MSG_HOOK(pstMsg);
        CDS_APS_MsgProc(pstMsg);
        break;
#endif

    case UEPS_PID_DHCP:
        CDS_MSG_HOOK(pstMsg);
        CDS_DHCP_MsgProc(pstMsg);
        break;

    default:
        CDS_ERROR_LOG1(UEPS_PID_CDS,"CDS_RecvMsgProc : CDS Msg Proc Error : Unkown Sender.",TTF_GET_MSG_SENDER_PID(pstMsg));
        CDS_PRINT_ERROR1(CDS_RecvMsgProc_ENUM,CDS_PRINT_GET_MSG_SENDER_ERR,TTF_GET_MSG_SENDER_PID(pstMsg));
        break;
    }

    return;
}
/*lint +e653*/
/*lint +e767*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



