

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "RnicCtx.h"
#include "RnicEntity.h"
#include "PsCommonDef.h"
#include "AtRnicInterface.h"
#include "RnicProcMsg.h"
#include "RnicDemandDialFileIO.h"
#include "RnicLog.h"
#include "RnicDebug.h"
#include "NVIM_Interface.h"
#include "TafNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_CTX_C
/*lint +e960*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* RNIC CTX,用于保存RNIC的全局变量 */
RNIC_CTX_STRU                           g_stRnicCtx;

extern RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];

extern VOS_UINT8                               g_ucRnicNetifRxType;



VOS_VOID RNIC_InitCtx(
    RNIC_CTX_STRU                      *pstRnicCtx
)
{
    VOS_UINT8                           ucIndex;

    PS_MEM_SET(g_astRnicStats, 0, sizeof(g_astRnicStats));

    PS_MEM_SET((VOS_VOID *)&g_stRnicRmnetConfigCheckInfo, 0, sizeof(g_stRnicRmnetConfigCheckInfo));

    for (ucIndex = 0 ; ucIndex < RNIC_NET_ID_MAX_NUM ; ucIndex++)
    {
        /* 初始化RNIC流量统计 */
        RNIC_ClearNetDsFlowStats(ucIndex);

        /* 初始化RNIC PDP上下文 */
        RNIC_InitPdpCtx(&(pstRnicCtx->astSpecCtx[ucIndex].stPdpCtx), ucIndex);

        /* 初始化流控状态 */
        pstRnicCtx->astSpecCtx[ucIndex].enFlowCtrlStatus = RNIC_FLOW_CTRL_STATUS_STOP;

        /* 初始化模块ID */
        /* 初始化的时候就已经确定了哪张网卡对应哪个MODEM */
        pstRnicCtx->astSpecCtx[ucIndex].enModemId        = RNIC_GET_MODEM_ID_BY_NET_ID(ucIndex);

        pstRnicCtx->astSpecCtx[ucIndex].enModemType      = RNIC_MODEM_TYPE_INSIDE;

        pstRnicCtx->astSpecCtx[ucIndex].enRmNetId        = ucIndex;
        pstRnicCtx->astSpecCtx[ucIndex].lSpePort         = RNIC_INVALID_SPE_PORT;
        pstRnicCtx->astSpecCtx[ucIndex].ulIpfPortFlg     = VOS_FALSE;
    }

    /* 初始化RABID信息 */
    for (ucIndex = 0 ; ucIndex < RNIC_MODEM_ID_MAX_NUM ; ucIndex++)
    {
        RNIC_InitRabidInfo(&pstRnicCtx->astRabIdInfo[ucIndex]);
    }

    /* 初始化PDNID信息 */
    RNIC_InitPdnIdInfo(&pstRnicCtx->stPdnIdInfo);

    /* 初始化RNIC定时器上下文 */
    RNIC_InitAllTimers(pstRnicCtx->astTimerCtx);

    /* 初始化拨号模式信息 */
    RNIC_InitDialMode(&(pstRnicCtx->stDialMode));

    /* 初始化拨号断开定时器超时次数参数统计 */
    RNIC_ClearTiDialDownExpCount();

    RNIC_SetTimer4WakeFlg(VOS_FALSE);

    /* 初始化复位信号量 */
    RNIC_InitResetSem();

    /* 获得使用netif_rx内核函数的类型 */
    RNIC_GetRnicNetifRxType();

    return;
}


VOS_VOID RNIC_InitRabidInfo(
    RNIC_RABID_INFO_STAU               *pstRabIdInfo
)
{

    PS_MEM_SET(pstRabIdInfo->aucRmNetId,
               RNIC_RMNET_ID_BUTT,
               RNIC_RAB_ID_MAX_NUM);

    return;
}


VOS_VOID RNIC_InitPdnIdInfo(
    RNIC_PDNID_INFO_STAU               *pstPdnIdInfo
)
{

    PS_MEM_SET(pstPdnIdInfo->aucRmNetId,
               RNIC_RMNET_ID_BUTT,
               RNIC_PDN_ID_MAX);

    return;
}



VOS_VOID RNIC_InitPdpCtx(
    RNIC_PDP_CTX_STRU                  *pstPdpCtx,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_InitIpv4PdpCtx(&(pstPdpCtx->stIpv4PdpInfo));
    RNIC_InitIpv6PdpCtx(&(pstPdpCtx->stIpv6PdpInfo));
    RNIC_InitIpv4v6PdpCtx(&(pstPdpCtx->stIpv4v6PdpInfo), ucRmNetId);

    return;
}


VOS_VOID RNIC_ResetDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
)
{
    pstDialMode->enDialMode             = RNIC_DIAL_MODE_MANUAL;
    pstDialMode->ulIdleTime             = RNIC_DIAL_DEMA_IDLE_TIME;
    pstDialMode->enEventReportFlag      = RNIC_FORBID_EVENT_REPORT;

    return;
}


VOS_VOID RNIC_InitDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
)
{
    VOS_UINT32                          ulRlst;

    pstDialMode->enDialMode             = RNIC_DIAL_MODE_MANUAL;
    pstDialMode->ulIdleTime             = RNIC_DIAL_DEMA_IDLE_TIME;
    pstDialMode->enEventReportFlag      = RNIC_FORBID_EVENT_REPORT;

    ulRlst                              = RNIC_InitDemandDialFile();

    if ( VOS_ERR == ulRlst)
    {
       RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialMode:RNIC_InitDemandDialFile ERR!");
    }

    return;
}


VOS_VOID RNIC_InitIpv4PdpCtx(
    RNIC_IPV4_PDP_INFO_STRU            *pstIpv4PdpCtx
)
{
    pstIpv4PdpCtx->enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstIpv4PdpCtx->ucRabId     = RNIC_RAB_ID_INVALID;
    pstIpv4PdpCtx->ucPdnId     = RNIC_PDN_ID_INVALID;
    pstIpv4PdpCtx->ulIpv4Addr  = 0;


    return;
}


VOS_VOID RNIC_InitIpv6PdpCtx(
    RNIC_IPV6_PDP_INFO_STRU            *pstIpv6PdpCtx
)
{
    pstIpv6PdpCtx->enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstIpv6PdpCtx->ucRabId     = RNIC_RAB_ID_INVALID;
    pstIpv6PdpCtx->ucPdnId     = RNIC_PDN_ID_INVALID;

    PS_MEM_SET(pstIpv6PdpCtx->aucIpv6Addr,
               0x00,
               RNIC_MAX_IPV6_ADDR_LEN);


    return;
}


VOS_VOID RNIC_InitIpv4v6PdpCtx(
    RNIC_IPV4V6_PDP_INFO_STRU          *pstIpv4v6PdpCtx,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* 获取PDP上下文地址 */
    pstPdpAddr                              = RNIC_GetPdpCtxAddr(ucRmNetId);

    pstIpv4v6PdpCtx->enRegStatus            = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstIpv4v6PdpCtx->ucRabId                = RNIC_RAB_ID_INVALID;
    pstIpv4v6PdpCtx->ucPdnId                = RNIC_PDN_ID_INVALID;

    pstPdpAddr->stIpv4PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;

    pstIpv4v6PdpCtx->ulIpv4Addr             = 0;

    PS_MEM_SET(pstIpv4v6PdpCtx->aucIpv6Addr,
               0x00,
               RNIC_MAX_IPV6_ADDR_LEN);


}


VOS_VOID RNIC_InitResetSem(VOS_VOID)
{
    g_stRnicCtx.hResetSem  = VOS_NULL_PTR;

    /* 分配二进制信号量 */
    if (VOS_OK != VOS_SmBCreate( "RNIC", 0, VOS_SEMA4_FIFO, &g_stRnicCtx.hResetSem))
    {
        PS_PRINTF("Create rnic acpu cnf sem failed!\r\n");
        RNIC_DBG_SET_SEM_INIT_FLAG(VOS_FALSE);
        RNIC_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);

        return;
    }
    else
    {
        RNIC_DBG_SAVE_BINARY_SEM_ID(g_stRnicCtx.hResetSem);
    }

    RNIC_DBG_SET_SEM_INIT_FLAG(VOS_TRUE);

    return;
}


VOS_VOID RNIC_GetRnicNetifRxType(VOS_VOID)
{
    TAF_NV_RNIC_NETIF_RX_TYPE_STRU              stRnicNetifRxType;

    /* 读取NV项 */
    if (NV_OK != NV_Read(en_NV_Item_Rnic_Netif_Rx_Type,
                         &stRnicNetifRxType,
                         sizeof(TAF_NV_RNIC_NETIF_RX_TYPE_STRU)))
    {
        return;
    }

    RNIC_SET_NETIF_RX_TYPE(stRnicNetifRxType.ucRnicNetifRxType);

    return;
}


VOS_VOID RNIC_ClearNetDsFlowStats(RNIC_RMNET_ID_ENUM_UINT8 enRmNetId)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;

    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(enRmNetId);

    pstNetCntxt->stDsFlowStats.ulCurrentRecvRate   = 0;
    pstNetCntxt->stDsFlowStats.ulPeriodRecvPktNum  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxLow  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxHigh = 0;

    pstNetCntxt->stDsFlowStats.ulCurrentSendRate   = 0;
    pstNetCntxt->stDsFlowStats.ulPeriodSendPktNum  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalSendFluxLow  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalSendFluxHigh = 0;

    return;
}


RNIC_CTX_STRU* RNIC_GetRnicCtxAddr(VOS_VOID)
{
    return &(g_stRnicCtx);
}


VOS_UINT32 RNIC_GetTiDialDownExpCount( VOS_VOID)
{
    return (g_stRnicCtx.ulTiDialDownExpCount);
}



VOS_VOID RNIC_IncTiDialDownExpCount( VOS_VOID)
{
    (g_stRnicCtx.ulTiDialDownExpCount)++;

    return;
}


VOS_VOID RNIC_ClearTiDialDownExpCount( VOS_VOID)
{
    g_stRnicCtx.ulTiDialDownExpCount = 0;

    return;
}


VOS_UINT32 RNIC_GetCurrentUlRate(VOS_UINT8 ucRmNetId)
{
    return (g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentSendRate);
}


VOS_VOID RNIC_SetCurrentUlRate(
    VOS_UINT32                          ulULDataRate,
    VOS_UINT8                           ucRmNetId
)
{
    g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentSendRate = ulULDataRate;

    return;
}



VOS_UINT32 RNIC_GetCurrentDlRate(VOS_UINT8 ucRmNetId)
{
    return (g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentRecvRate);
}


VOS_VOID RNIC_SetCurrentDlRate(
    VOS_UINT32                          ulDLDataRate,
    VOS_UINT8                           ucRmNetId
)
{
    g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentRecvRate = ulDLDataRate;

    return;
}


RNIC_DIAL_MODE_STRU* RNIC_GetDialModeAddr(VOS_VOID)
{
    return &(g_stRnicCtx.stDialMode);
}


RNIC_PDP_CTX_STRU* RNIC_GetPdpCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId].stPdpCtx);
}


RNIC_TIMER_CTX_STRU*  RNIC_GetTimerAddr( VOS_VOID )
{
    return g_stRnicCtx.astTimerCtx;
}


VOS_UINT32 RNIC_GetTimer4WakeFlg(VOS_VOID)
{
    return g_stRnicCtx.ulSetTimer4WakeFlg;
}


VOS_VOID RNIC_SetTimer4WakeFlg(VOS_UINT32 ulFlg)
{
    g_stRnicCtx.ulSetTimer4WakeFlg = ulFlg;
}


RNIC_SPEC_CTX_STRU *RNIC_GetSpecNetCardCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId]);
}


RNIC_SPEC_CTX_STRU* RNIC_GetNetCntxtByRmNetId(RNIC_RMNET_ID_ENUM_UINT8 enRmNetId)
{
    if (enRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return VOS_NULL_PTR;
    }

    return RNIC_GET_SPEC_NET_CTX(enRmNetId);
}

#if defined(CONFIG_BALONG_SPE)

RNIC_SPEC_CTX_STRU* RNIC_GetNetCntxtBySpePort(VOS_INT32 lPort)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    VOS_UINT8                           i;

    for (i = 0 ; i < RNIC_NET_ID_MAX_NUM; i++)
    {
        pstNetCntxt = RNIC_GET_SPEC_NET_CTX(i);
        if (lPort == pstNetCntxt->lSpePort)
        {
            return pstNetCntxt;
        }
    }

    return VOS_NULL_PTR;
}
#endif


VOS_SEM RNIC_GetResetSem(VOS_VOID)
{
    return g_stRnicCtx.hResetSem;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
