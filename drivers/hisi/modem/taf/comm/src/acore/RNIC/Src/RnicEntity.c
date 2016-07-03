
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "v_typdef.h"
#include "ImmInterface.h"
#include "RnicProcMsg.h"
#include "RnicLog.h"
#include "RnicEntity.h"
#include "RnicDebug.h"
#include "RnicCtx.h"
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
#include "SdioInterface.h"
#endif
#include "RnicConfigInterface.h"
#include "product_config.h"
#if (VOS_WIN32 == VOS_OS_VER)
#include <stdio.h>
#endif
#include "mdrv.h"
#include "PppRnicInterface.h"


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

#define THIS_FILE_ID PS_FILE_ID_RNIC_ENTITY_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
*****************************************************************************/
VOS_UINT8                               g_ucRnicNetifRxType = 0;


/******************************************************************************
   5 函数实现
******************************************************************************/


VOS_VOID RNIC_SendULDataInPdpActive(
    IMM_ZC_STRU                        *pstImmZc,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt,
    VOS_UINT8                           ucRabId,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;
    RNIC_RMNET_ID_ENUM_UINT8            enRmNetId;
    VOS_UINT8                           ucSendAdsRabId;



    pstPriv   = pstNetCntxt->pstPriv;
    enRmNetId = pstNetCntxt->enRmNetId;

    /* 根据Modem Id组装RabId */
    if (MODEM_ID_0 == pstNetCntxt->enModemId)
    {
        ucSendAdsRabId = ucRabId;
    }
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    else if (MODEM_ID_1 == pstNetCntxt->enModemId)
    {
        ucSendAdsRabId = ucRabId | RNIC_RABID_TAKE_MODEM_1_MASK;
    }
#if (MULTI_MODEM_NUMBER == 3)
    else if (MODEM_ID_2 == pstNetCntxt->enModemId)
    {
        ucSendAdsRabId = ucRabId | RNIC_RABID_TAKE_MODEM_2_MASK;
    }
#endif
#endif
    else
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_MODEM_ID_UL_DISCARD_NUM(1, enRmNetId);
        pstPriv->stStats.tx_dropped++;
        return;
    }



    if (VOS_OK != ADS_UL_SendPacketEx(pstImmZc, enIpType, ucSendAdsRabId))
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_SEND_UL_PKT_FAIL_NUM(1, enRmNetId);
        pstPriv->stStats.tx_dropped++;
        return;
    }

    RNIC_DBG_SEND_UL_PKT_NUM(1, enRmNetId);

    /* 统计网卡发送信息 */
    pstPriv->stStats.tx_packets++;
    pstPriv->stStats.tx_bytes += pstImmZc->len;

    /* 统计上行数据 */
    pstNetCntxt->stDsFlowStats.ulPeriodSendPktNum++;
    pstNetCntxt->stDsFlowStats.ulTotalSendFluxLow += pstImmZc->len;

    return;
}


VOS_VOID RNIC_SendULIpv4Data(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
)
{
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    RNIC_RMNET_ID_ENUM_UINT8            enRmNetId;
    VOS_UINT8                           ucRabId;

    pstImmZc  = (IMM_ZC_STRU *)pstSkb;
    enRmNetId = pstNetCntxt->enRmNetId;

    /* 获取网卡映射的RABID */
    ucRabId = RNIC_GET_SPEC_NET_IPV4_RABID(enRmNetId);
    if (RNIC_RAB_ID_INVALID == ucRabId)
    {
        IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
        RNIC_DBG_RAB_ID_ERR_NUM(1, enRmNetId);
        return;
    }

    /* PDP激活的情况下数据的处理 */
    RNIC_SendULDataInPdpActive(pstImmZc, pstNetCntxt, ucRabId, ADS_PKT_TYPE_IPV4);

    return;
}


VOS_VOID RNIC_SendULIpv6Data(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
)
{
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    RNIC_RMNET_ID_ENUM_UINT8            enRmNetId;
    VOS_UINT8                           ucRabId;

    pstImmZc  = (IMM_ZC_STRU *)pstSkb;
    enRmNetId = pstNetCntxt->enRmNetId;

    /* 获取网卡映射的RABID */
    ucRabId = RNIC_GET_SPEC_NET_IPV6_RABID(enRmNetId);
    if (RNIC_RAB_ID_INVALID == ucRabId)
    {
        IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
        RNIC_DBG_RAB_ID_ERR_NUM(1, enRmNetId);
        return;
    }

    /* PDP激活的情况下数据的处理 */
    RNIC_SendULDataInPdpActive(pstImmZc, pstNetCntxt, ucRabId, ADS_PKT_TYPE_IPV6);

    return;
}


VOS_UINT32 RNIC_ProcDemDial(
    struct sk_buff                     *pstSkb
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_TIMER_STATUS_ENUM_UINT8        enTiStatus;
    VOS_UINT32                          ulIpAddr;

    /* 获取IP地址 */
    ulIpAddr = *((VOS_UINT32 *)((pstSkb->data) + RNIC_IP_HEAD_DEST_ADDR_OFFSET));

    /*如果是广播包，则不发起按需拨号，直接过滤调*/
    if (RNIC_IPV4_BROADCAST_ADDR == ulIpAddr)
    {
        RNIC_DBG_UL_RECV_IPV4_BROADCAST_NUM(1, RNIC_RMNET_ID_0);
        return VOS_ERR;
    }

    /* 获取按需拨号的模式以及时长的地址 */
    pstDialMode = RNIC_GetDialModeAddr();

    /* 获取当前拨号保护定时器的状态 */
    enTiStatus  = RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_PROTECT);

    /*为了防止按需拨号上报太快，启动一个两秒定时器，*/
    if (RNIC_TIMER_STATUS_STOP == enTiStatus)
    {
        /* 通知应用进行拨号操作 */
        if (RNIC_ALLOW_EVENT_REPORT == pstDialMode->enEventReportFlag)
        {
            if (VOS_OK == RNIC_SendDialEvent(DEVICE_ID_WAN, RNIC_DAIL_EVENT_UP))
            {
                /* 启动拨号保护定时器  */
                RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_PROTECT, TI_RNIC_DEMAND_DIAL_PROTECT_LEN);
                RNIC_DBG_SEND_APP_DIALUP_SUCC_NUM(1, RNIC_RMNET_ID_0);
                RNIC_NORMAL_LOG(ACPU_PID_RNIC, "RNIC_ProcDemDial: Send dial event succ.");
            }
            else
            {
                RNIC_DBG_SEND_APP_DIALUP_FAIL_NUM(1, RNIC_RMNET_ID_0);
                RNIC_WARNING_LOG(ACPU_PID_RNIC, "RNIC_ProcDemDial: Send dial event fail.");
            }

            RNIC_MNTN_TraceDialConnEvt();
        }
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

VOS_VOID RNIC_RcvOutsideModemUlData(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;
    VOS_UINT16                          usEthType;
    VOS_UINT8                           ucPdnId;
    VOS_ULONG                           ulRslt;
    VOS_UINT32                          ulDataLen;
    RNIC_RMNET_ID_ENUM_UINT8            enRmNetId;

    pstPriv     = pstNetCntxt->pstPriv;
    enRmNetId   = pstNetCntxt->enRmNetId;
    ulDataLen   = pstSkb->len;
    ulRslt      = SDIO_ERR;

    /* 获取以太帧类型 */
    usEthType   = VOS_NTOHS(((RNIC_ETH_HEADER_STRU *)(pstSkb->data))->usEtherType);

    /* IP报文类型判断 */
    switch(usEthType)
    {
        case RNIC_ETH_TYPE_IP:
            ucPdnId = RNIC_GET_SPEC_NET_IPV4_PDNID(enRmNetId);
            break;

        case RNIC_ETH_TYPE_IPV6:
            ucPdnId = RNIC_GET_SPEC_NET_IPV6_PDNID(enRmNetId);
            break;

        default:
            IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
            RNIC_DBG_RECV_UL_ERR_PKT_NUM(1, enRmNetId);
            pstPriv->stStats.tx_dropped++;
            return;
    }

    /* 非法Pdn Id */
    if (RNIC_PDN_ID_INVALID == ucPdnId)
    {
        IMM_ZcFree((IMM_ZC_STRU *)pstSkb);
        RNIC_DBG_PDN_ID_ERR_NUM(1, enRmNetId);
        return;
    }

    /* 移除MAC头 */
    if (VOS_OK != IMM_ZcRemoveMacHead(pstSkb))
    {
        IMM_ZcFree(pstSkb);
        RNIC_DBG_UL_RMV_MAC_HDR_FAIL_NUM(1, enRmNetId);
        return;
    }

    /* 写SDIO */
    ulRslt = SDIO_UL_SendPacket(pstSkb, ucPdnId);
    if (SDIO_OK != ulRslt)
    {
        IMM_ZcFree(pstSkb);
        RNIC_DBG_SEND_UL_PKT_FAIL_NUM(1, enRmNetId);
        pstPriv->stStats.tx_dropped++;
    }
    else
    {
        RNIC_DBG_SEND_UL_PKT_NUM(1, enRmNetId);
        pstPriv->stStats.tx_packets++;
        pstPriv->stStats.tx_bytes += ulDataLen;
    }

    return;
}
#endif

VOS_VOID RNIC_RcvInsideModemUlData(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;
    VOS_UINT16                          usEthType;
    RNIC_RMNET_ID_ENUM_UINT8            enRmNetId;

    pstPriv     = pstNetCntxt->pstPriv;
    enRmNetId   = pstNetCntxt->enRmNetId;

    /* 获取以太帧类型 */
    usEthType   = VOS_NTOHS(((RNIC_ETH_HEADER_STRU *)(pstSkb->data))->usEtherType);

    /* 流控检查 */
    if (RNIC_FLOW_CTRL_STATUS_START == RNIC_GET_FLOW_CTRL_STATUS(enRmNetId))
    {
        IMM_ZcFree(pstSkb);
        RNIC_DBG_FLOW_CTRL_UL_DISCARD_NUM(1, enRmNetId);
        return;
    }

    /* 移除MAC头 */
    if (VOS_OK != IMM_ZcRemoveMacHead(pstSkb))
    {
        IMM_ZcFree(pstSkb);
        RNIC_DBG_UL_RMV_MAC_HDR_FAIL_NUM(1, enRmNetId);
        pstPriv->stStats.tx_dropped++;
        return;
    }

    /* 只在网卡0上面才会触发按需拨号 */
    if ((RNIC_ETH_TYPE_IP == usEthType)
     && (RNIC_DIAL_MODE_DEMAND_DISCONNECT == RNIC_GET_DIAL_MODE())
     && (RNIC_PDP_REG_STATUS_DEACTIVE == RNIC_GET_SPEC_NET_IPV4_REG_STATE(enRmNetId))
     && (RNIC_RMNET_ID_0 == enRmNetId))
    {
        RNIC_SPE_MEM_UNMAP(pstSkb, RNIC_SPE_CACHE_HDR_SIZE);

        if (VOS_ERR == RNIC_ProcDemDial(pstSkb))
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_StartXmit, the data is discared!");
        }

        RNIC_SPE_MEM_MAP(pstSkb, RNIC_SPE_CACHE_HDR_SIZE);

        IMM_ZcFree(pstSkb);
        return;
    }

    /* IP报文类型判断 */
    switch(usEthType)
    {
        case RNIC_ETH_TYPE_IP:
            RNIC_SendULIpv4Data(pstSkb, pstNetCntxt);
            RNIC_DBG_RECV_UL_IPV4_PKT_NUM(1, enRmNetId);
            break;

        case RNIC_ETH_TYPE_IPV6:
            RNIC_SendULIpv6Data(pstSkb, pstNetCntxt);
            RNIC_DBG_RECV_UL_IPV6_PKT_NUM(1, enRmNetId);
            break;

        default:
            IMM_ZcFree(pstSkb);
            RNIC_DBG_RECV_UL_ERR_PKT_NUM(1, enRmNetId);
            break;
    }

    return;
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

VOS_VOID RNIC_ShowSdioDlData(
    VOS_UINT8                           ucPdnId,
    IMM_ZC_STRU                        *pstImmZc
)
{
    VOS_UINT32                          i;

    /* RNIC 上行数据打印开关，打印去mac头的数据 */
    if (VOS_TRUE == g_ulRnicPrintDlDataFlg)
    {
        PS_PRINTF("RNIC_ShowSdioDlData : dl data pdn id is %d. \r\n", ucPdnId);
        PS_PRINTF("RNIC_ShowSdioDlData : dl data len is %d. \r\n", pstImmZc->len);
        PS_PRINTF("RNIC_ShowSdioDlData : dl data content is: \r\n");

        for (i = 0; i < pstImmZc->len; i++)
        {
            if (pstImmZc->data[i] > 0xf)
            {
                PS_PRINTF("%x", pstImmZc->data[i]);
            }
            else
            {
                PS_PRINTF("0%x", pstImmZc->data[i]);
            }
        }
        PS_PRINTF("\r\n");
    }

    return;
}


VOS_UINT32 RNIC_RcvSdioDlData(
    VOS_UINT8                           ucPdnId,
    IMM_ZC_STRU                        *pstImmZc
)
{
    VOS_UINT8                           ucNetIndex;
    ADS_PKT_TYPE_ENUM_UINT8             enPktType;
    VOS_UINT8                           ucIpType;
    VOS_UINT32                          ulRet;

    /* 可谓可测，打印数据包内容和pdn id */
    RNIC_ShowSdioDlData(ucPdnId, pstImmZc);

    /* 根据PDNid获取对应的RMNETid */
    ucNetIndex     = RNIC_GET_RM_NET_ID_BY_PDN_ID(ucPdnId);

    /* 获取协议版本号 */
    ucIpType    = RNIC_GET_IP_VERSION(pstImmZc->data[0]);

    if (RNIC_IPV4_VERSION == ucIpType)
    {
        enPktType = ADS_PKT_TYPE_IPV4;
    }
    else if (RNIC_IPV6_VERSION == ucIpType)
    {
        enPktType = ADS_PKT_TYPE_IPV6;
    }
    else    /* 数据包类型与承载支持类型不一致 */
    {
        RNIC_DBG_RECV_DL_ERR_PKT_NUM(1, ucNetIndex);
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_RcvSdioDlData, Ip Type is !", ucIpType);

        /* 释放内存 */
        IMM_ZcFree(pstImmZc);

        return RNIC_PKT_TYPE_INVAL;
    }

    ulRet = RNIC_SendDlData(ucNetIndex, pstImmZc, enPktType);
    return ulRet;
}
#endif


VOS_UINT32  RNIC_RcvAdsDlData(
    VOS_UINT8                           ucExRabid,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType,
    VOS_UINT32                          ulExParam
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucRmNetId;

    ucRmNetId = RNIC_GET_RMNETID_FROM_EXPARAM(ulExParam);

    ulRet = RNIC_SendDlData(ucRmNetId, pstImmZc, enPktType);

    return ulRet;
}


VOS_UINT32 RNIC_SendDlData(
    RNIC_RMNET_ID_ENUM_UINT8            enRmNetId,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType
)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;

    if (!RNIC_RMNET_IS_VALID(enRmNetId))
    {
        IMM_ZcFree(pstImmZc);
        return RNIC_INVAL;
    }

    /* 获取网卡上下文 */
    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(enRmNetId);

#if (defined(CONFIG_BALONG_SPE))
    if (RNIC_INVALID_SPE_PORT != pstNetCntxt->lSpePort)
    {
        return RNIC_SpeRxData(pstNetCntxt, pstImmZc, enPktType);
    }
#endif

    return RNIC_NetRxData(pstNetCntxt, pstImmZc, enPktType);
}


unsigned int RNIC_StartFlowCtrl(unsigned char ucRmNetId)
{
    RNIC_SET_FLOW_CTRL_STATUS(RNIC_FLOW_CTRL_STATUS_START, ucRmNetId);
    return VOS_OK;
}


unsigned int RNIC_StopFlowCtrl(unsigned char ucRmNetId)
{
    RNIC_SET_FLOW_CTRL_STATUS(RNIC_FLOW_CTRL_STATUS_STOP, ucRmNetId);
    return VOS_OK;
}


unsigned long RNIC_ConfigRmnetStatus(
    RNIC_RMNET_CONFIG_STRU             *pstConfigInfo
)
{
    /*可维可测，输出配置信息*/
    RNIC_MNTN_SndRmnetConfigInfoMsg(pstConfigInfo);
    RNIC_DBG_CONFIGCHECK_ADD_TOTLA_NUM();

    /* 参数检查 */
    /* 内部modem需要检查 rab id是否异常 */
    if (RNIC_MODEM_TYPE_INSIDE == pstConfigInfo->enModemType)
    {
        if (!RNIC_RAB_ID_IS_VALID(pstConfigInfo->ucRabId))
        {
            RNIC_DBG_CONFIGCHECK_ADD_RABID_ERR_NUM();
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild RAB id !");
            return VOS_ERR;
        }
    }
    /* 外部modem需要检查 pdn id是否异常 */
    else if (RNIC_MODEM_TYPE_OUTSIDE == pstConfigInfo->enModemType)
    {
        if (!RNIC_PDN_ID_IS_VALID(pstConfigInfo->ucPdnId))
        {
            RNIC_DBG_CONFIGCHECK_ADD_PDNID_ERR_NUM();
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild Pdn id !");
            return VOS_ERR;
        }
    }
    /* 无效MODEM TYPE */
    else
    {
        RNIC_DBG_CONFIGCHECK_ADD_MODEMTYPE_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild modem type!");
        return VOS_ERR;
    }

    /* 网卡操作类型异常直接返回error */
    if (!RNIC_RMNET_STATUS_IS_VALID(pstConfigInfo->enRmnetStatus))
    {
        RNIC_DBG_CONFIGCHECK_ADD_RMNETSTATUS_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild Rmnet Status !");
        return VOS_ERR;
    }

    /* IP类型非法直接返回error */
    if (!RNIC_IP_TYPE_IS_VALID(pstConfigInfo->enIpType))
    {
        RNIC_DBG_CONFIGCHECK_ADD_IPTYPE_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: invaild IP type !");
        return VOS_ERR;
    }

    /* 发送内部消息 */
    if (VOS_OK != RNIC_SndRnicRmnetConfigReq(pstConfigInfo))
    {
        RNIC_DBG_CONFIGCHECK_ADD_SND_ERR_NUM();
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ConfigRmnetStatus: send pdp status ind fail !");
        return VOS_ERR;
    }

    RNIC_DBG_CONFIGCHECK_ADD_SUCC_NUM();
    return VOS_OK;
}


VOS_UINT32 RNIC_NetRxData(
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv    = VOS_NULL_PTR;
    VOS_UINT8                          *pucAddData = VOS_NULL_PTR;
    RNIC_RMNET_ID_ENUM_UINT8            enRmNetId;
    VOS_INT32                           lRnicNetifRxRst;

    pstPriv     = pstNetCntxt->pstPriv;
    enRmNetId   = pstNetCntxt->enRmNetId;

    /* 网卡设备检查 */
    if (VOS_NULL_PTR == pstPriv)
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_NETCAED_DL_DISCARD_NUM(1, enRmNetId);
        return RNIC_INVAL;
    }

    /* 网卡未打开 */
    if (RNIC_NETCARD_STATUS_CLOSED == pstPriv->enStatus)
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_DISCARD_DL_PKT_NUM(1, enRmNetId);
        pstPriv->stStats.rx_dropped++;
        return RNIC_OK;
    }

    /* 数据长度超出有效值(不包含MAC头) */
    if ((pstImmZc->len) > RNIC_MAX_PACKET)
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_RECV_DL_BIG_PKT_NUM(1, enRmNetId);
        pstPriv->stStats.rx_errors++;
        pstPriv->stStats.rx_length_errors++;
        return RNIC_OK;
    }

    /* 填充MAC帧头，调用ImmZc接口将MAC帧头填入ImmZc中 */
    if (ADS_PKT_TYPE_IPV4 == enPktType)
    {
        pucAddData = (VOS_UINT8*)&g_astRnicManageTbl[enRmNetId].stIpv4Ethhead;
        RNIC_DBG_RECV_DL_IPV4_PKT_NUM(1, enRmNetId);
    }
    else if (ADS_PKT_TYPE_IPV6 == enPktType)
    {
        pucAddData = (VOS_UINT8*)&g_astRnicManageTbl[enRmNetId].stIpv6Ethhead;
        RNIC_DBG_RECV_DL_IPV6_PKT_NUM(1, enRmNetId);
    }
    else   /* 数据包类型与承载支持类型不一致 */
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_RECV_DL_ERR_PKT_NUM(1, enRmNetId);
        return RNIC_PKT_TYPE_INVAL;
    }

    if (VOS_OK != IMM_ZcAddMacHead(pstImmZc, pucAddData))
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_ADD_DL_MACHEAD_FAIL_NUM(1, enRmNetId);
        return RNIC_ADDMAC_FAIL;
    }

    pstImmZc->protocol = eth_type_trans(pstImmZc, pstPriv->pstDev);

    /* 统计网卡接收数据信息 */
    pstPriv->stStats.rx_packets++;
    pstPriv->stStats.rx_bytes += pstImmZc->len;

    if (RNIC_NETIF_RX_NI == RNIC_GET_NETIF_RX_TYPE())
    {
        lRnicNetifRxRst = netif_rx_ni(pstImmZc);
    }
    else
    {
        lRnicNetifRxRst = netif_rx(pstImmZc);
    }

    if (NET_RX_SUCCESS != lRnicNetifRxRst)
    {
        RNIC_DBG_SEND_DL_PKT_FAIL_NUM(1, enRmNetId);
        pstPriv->stStats.rx_dropped++;
        return RNIC_RX_PKT_FAIL;
    }

    /* 增加下行发送数据统计 */
    RNIC_DBG_SEND_DL_PKT_NUM(1, enRmNetId);

    /* 统计收到的下行数据字节数，用于流量上报 */
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxLow += pstImmZc->len;

    return RNIC_OK;
}


VOS_VOID RNIC_ProcessTxDataByModemType(
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt,
    struct sk_buff                     *pstSkb
)
{
    RNIC_DBG_PRINT_UL_DATA(pstSkb);

    if (RNIC_MODEM_TYPE_INSIDE == pstNetCntxt->enModemType)
    {
        RNIC_RcvInsideModemUlData(pstSkb, pstNetCntxt);
    }
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    else if (RNIC_MODEM_TYPE_OUTSIDE == pstNetCntxt->enModemType)
    {
        RNIC_RcvOutsideModemUlData(pstSkb, pstNetCntxt);
    }
#endif
    else
    {
        IMM_ZcFree(pstSkb);
    }

    return;
}

#if (defined(CONFIG_BALONG_SPE))

VOS_UINT32 RNIC_IsSpeMem(IMM_ZC_STRU *pstImmZc)
{
    return (0 != pstImmZc->spe_own);
}


dma_addr_t RNIC_GetMemDma(IMM_ZC_STRU *pstImmZc)
{
    return RNIC_SPE_MEM_CB(pstImmZc)->ulDmaAddr;
}


VOS_VOID RNIC_SpeMemMapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen)
{
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    dma_addr_t                          ulDmaAddr;

    ulDmaAddr = RNIC_GetMemDma(pstImmZc);
    pucData   = phys_to_virt(ulDmaAddr);
    dma_map_single(VOS_NULL_PTR, pucData, ulLen, DMA_FROM_DEVICE);
    return;
}


VOS_VOID RNIC_SpeMemUnmapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen)
{
    dma_addr_t                          ulDmaAddr;

    ulDmaAddr = RNIC_GetMemDma(pstImmZc);
    dma_unmap_single(VOS_NULL_PTR, ulDmaAddr, ulLen, DMA_FROM_DEVICE);
    return;
}


VOS_VOID RNIC_SpeReadCB(
    VOS_INT32                           lPort,
    struct sk_buff                     *pstSkb
)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;

    pstNetCntxt = RNIC_GetNetCntxtBySpePort(lPort);
    if (VOS_NULL_PTR == pstNetCntxt)
    {
        IMM_ZcFree(pstSkb);
        RNIC_DBG_SPE_TX_PORTID_ERR_NUM(1);
        return;
    }

    /* 按MODEM类型分发处理数据 */
    RNIC_ProcessTxDataByModemType(pstNetCntxt, pstSkb);

    return;
}


VOS_UINT32 RNIC_SpeRxData(
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv    = VOS_NULL_PTR;
    VOS_UINT8                          *pucAddData = VOS_NULL_PTR;
    RNIC_RMNET_ID_ENUM_UINT8            enRmNetId;

    pstPriv     = pstNetCntxt->pstPriv;
    enRmNetId   = pstNetCntxt->enRmNetId;

    /* 网卡设备检查 */
    if (VOS_NULL_PTR == pstPriv)
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_NETCAED_DL_DISCARD_NUM(1, enRmNetId);
        return RNIC_INVAL;
    }

    /* 网卡未打开 */
    if (RNIC_NETCARD_STATUS_CLOSED == pstPriv->enStatus)
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_DISCARD_DL_PKT_NUM(1, enRmNetId);
        pstPriv->stStats.rx_dropped++;
        return RNIC_OK;
    }

    /* 数据长度超出有效值(不包含MAC头) */
    if ((pstImmZc->len) > RNIC_MAX_PACKET)
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_RECV_DL_BIG_PKT_NUM(1, enRmNetId);
        pstPriv->stStats.rx_errors++;
        pstPriv->stStats.rx_length_errors++;
        return RNIC_OK;
    }

    /* 填充MAC帧头，调用ImmZc接口将MAC帧头填入ImmZc中 */
    if (ADS_PKT_TYPE_IPV4 == enPktType)
    {
        pucAddData = (VOS_UINT8 *)&g_astRnicManageTbl[enRmNetId].stIpv4Ethhead;
        mdrv_spe_set_skb_ipv4(pstImmZc);
        RNIC_DBG_RECV_DL_IPV4_PKT_NUM(1, enRmNetId);
    }
    else if (ADS_PKT_TYPE_IPV6 == enPktType)
    {
        pucAddData = (VOS_UINT8 *)&g_astRnicManageTbl[enRmNetId].stIpv6Ethhead;
        mdrv_spe_set_skb_ipv6(pstImmZc);
        RNIC_DBG_RECV_DL_IPV6_PKT_NUM(1, enRmNetId);
    }
    else   /* 数据包类型与承载支持类型不一致 */
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_RECV_DL_ERR_PKT_NUM(1, enRmNetId);
        return RNIC_PKT_TYPE_INVAL;
    }

    if (VOS_TRUE == pstNetCntxt->ulIpfPortFlg)
    {
        IMM_ZcPush(pstImmZc, RNIC_MAC_HDR_LEN);
    }
    else
    {
        if (VOS_OK != IMM_ZcAddMacHead(pstImmZc, pucAddData))
        {
            IMM_ZcFree(pstImmZc);
            RNIC_DBG_ADD_DL_MACHEAD_FAIL_NUM(1, enRmNetId);
            return RNIC_ADDMAC_FAIL;
        }
    }

    /* 统计网卡接收数据信息 */
    pstPriv->stStats.rx_packets++;
    pstPriv->stStats.rx_bytes += pstImmZc->len;

    /* 数据递交成功由驱动负责释放, 递交失败由调用者释放 */
    if (MDRV_OK != mdrv_spe_wport_xmit(pstNetCntxt->lSpePort, pstImmZc))
    {
        IMM_ZcFree(pstImmZc);
        RNIC_DBG_SEND_DL_PKT_FAIL_NUM(1, enRmNetId);
        pstPriv->stStats.rx_dropped++;
        return RNIC_RX_PKT_FAIL;
    }

    /* 统计收到的下行数据流量 */
    RNIC_DBG_SEND_DL_PKT_NUM(1, enRmNetId);
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxLow += pstImmZc->len;

    return RNIC_OK;
}


VOS_VOID RNIC_SpeInit(VOS_VOID)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;
    spe_wport_attr_t                    stAttr;
    VOS_INT32                           lEthId;
    VOS_INT32                           lBypass;
    VOS_INT32                           lIpfPort;
    VOS_INT32                           lPort;

    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(RNIC_RMNET_ID_0);
    pstPriv     = pstNetCntxt->pstPriv;

    /*
     * 获取USB虚拟网卡模式
     * 1 --- 网卡为BYPASS模式(STICK)
     * 0 --- 网卡为LINUX网卡
     */
    lEthId      = 0;
    lIpfPort    = 1;
    lBypass     = mdrv_spe_usb_eth_is_bypass(lEthId);

    /* 打开LINUX网卡对应的SPE端口 */
    if (0 == lBypass)
    {
        /* 检查网卡设备 */
        if (VOS_NULL_PTR == pstPriv)
        {
            RNIC_DEV_ERR_PRINTK("RNIC_SpeInit: pstNetDev is null!");
            return;
        }

        /* 设置端口参数 */
        RNIC_SET_SPE_PORT_ATTR(&stAttr, lIpfPort, pstPriv->pstDev);

        /* 打开SPE端口 */
        lPort = mdrv_spe_wport_open(&stAttr);
        if (lPort > 0)
        {
            pstNetCntxt->lSpePort     = lPort;
            pstNetCntxt->ulIpfPortFlg = (1 == lIpfPort) ? VOS_TRUE : VOS_FALSE;

            mdrv_spe_wport_ioctl(pstNetCntxt->lSpePort,
                                 SPE_WPORT_IOCTL_SET_RX_CB,
                                 RNIC_SpeReadCB);

            mdrv_spe_wport_ioctl(pstNetCntxt->lSpePort,
                                 SPE_WPORT_IOCTL_SET_MAC,
                                 (VOS_VOID *)RNIC_GET_ETH_HDR_ADDR(RNIC_RMNET_ID_0));

            mdrv_spe_wport_ioctl(pstNetCntxt->lSpePort,
                                 SPE_WPORT_IOCTL_SET_PUSH_CB,
                                 ADS_IPF_SpeIntWakeupADS);

            mdrv_spe_wport_ioctl(pstNetCntxt->lSpePort,
                                 SPE_WPORT_IOCTL_SET_RECYCLE_CB,
                                 ADS_IPF_RecycleMem);

            ADS_IPF_RegSpeWPort(pstNetCntxt->lSpePort);
        }
        else
        {
            RNIC_DEV_ERR_PRINTK("RNIC_SpeInit: Open spe port failed!");
        }
    }

    return;
}
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
