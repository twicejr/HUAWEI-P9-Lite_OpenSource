


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImmInterface.h"
#include "NVIM_Interface.h"
#include "PsNdis.h"
#include "LUPQueue.h"
#include "Ipv4DhcpServer.h"
#include "PsCommonDef.h"
#include "msp_at.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "msp_diag.h"
#endif
#include "vos.h"
#include "IpNdServer.h"
#include "NasNvInterface.h"
#include "NdisDrv.h"
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PSNDIS_C
/*lint +e767*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#define C2A_QUE_SIZE                512        /*暂定512*/
#define USB_DATAREQ_QUE_SIZE        512        /*暂定512*/

#define NDIS_PERIOD_ARP_TMRNAME     1
#define NDIS_ARP_REQ_TMRNAME        2

/*****************************************************************************
  3 function
*****************************************************************************/
/*来自ADS的数据，存放队列*/
LUP_QUEUE_STRU  *g_pstC2ACoreQue        = VOS_NULL_PTR;
VOS_VOID        *p_aC2AQueBuf[C2A_QUE_SIZE];

/*来自USB数据的存放队列*/
LUP_QUEUE_STRU  *g_pstUsbDataReqQue     = VOS_NULL_PTR;
VOS_VOID        *p_aUsbQueBuf[USB_DATAREQ_QUE_SIZE];

/*arp请求中间部分固定的值*/
VOS_UINT8       g_aucArpReqFixVal[ETH_ARP_FIXED_MSG_LEN] = {0x00,0x01,0x08,0x00,0x06,0x04,0x00,0x01 };
/*arp响应中间部分固定的值*/
VOS_UINT8       g_aucArpRspFixVal[ETH_ARP_FIXED_MSG_LEN] = {0x00,0x01,0x08,0x00,0x06,0x04,0x00,0x02 };
/*广播地址，全1*/
VOS_UINT8       g_aucBroadCastAddr[ETH_MAC_ADDR_LEN]   = {0xff,0xff,0xff,0xff,0xff,0xff };

VOS_UINT8       g_aucInvalidAddr[IPV4_ADDR_LEN] = {0};

/*ARP周期*/
VOS_UINT32      g_ulPeriodicArpCyc      = 3000;   /*周期性ARP发送周期*/


/*统计信息*/
NDIS_STAT_INFO_STRU        g_stNdisStatStru = {0};

NDIS_ENTITY_STRU           g_astNdisEntity[NAS_NDIS_MAX_ITEM] = {{0}};
NDIS_ENTITY_STRU          *g_pstNdisEntity = g_astNdisEntity;

VOS_UINT32                 g_ulNvMtu = 1500;              /*IPV6 MTU默认取值*/

VOS_UINT32 g_ulNdisLomSwitch = 0;
SPE_MAC_ETHER_HEADER_STRU g_stSpeMacHeader = {{0x58,0x02,0x03,0x04,0x05,0x06},{0x00,0x11,0x09,0x64,0x01,0x01},0x00000000};     /*mac地址初始化为固定值*/

/*****************************************************************************
  3 Function
*****************************************************************************/
/*声明*/
extern VOS_VOID   PppMsgProc( struct MsgCB * pMsg );
extern VOS_UINT32 PppInit(enum VOS_INIT_PHASE_DEFINE InitPhase );
VOS_UINT32 Ndis_DlSpeSendNcm(NDIS_ENTITY_STRU *pstNdisEntity, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc);


extern VOS_UINT32 DIPC_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 DIPC_AtMsgProc( const MsgBlock *pMsgBlock );

extern VOS_UINT32 MUX_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 MUX_AtMsgProc( const MsgBlock *pMsgBlock );

/* ****************************************************************************
 函 数 名  : Ndis_GetMacAddr
 功能描述  : 获取MAC地址
 输入参数  : None
 输出参数  : None
 返 回 值  : VOS_UINT8*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : 翟鹏
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8* Ndis_GetMacAddr(VOS_VOID)
{
    /*LTE协议栈MAC地址*/
    static VOS_UINT8 g_ucMacAddressPstable[] =
    {
        0x4c, 0x54, 0x99, 0x45, 0xe5, 0xd5
    };

    return g_ucMacAddressPstable;
}

/* ****************************************************************************
 函 数 名  : Ndis_DlAdsDataRcv
 功能描述  : NDIS_ADS下行数据接收回调函数
 输入参数  : VOS_VOID *pBuf
             VOS_UINT32 ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : 惠博
    修改内容   : 新生成函数

  2.日    期   : 2013年1月16日
    作    者   : h00218138
    修改内容   : DSDA特性开发，入参修改为扩展承载ID

*****************************************************************************/
VOS_UINT32 Ndis_DlAdsDataRcv(VOS_UINT8 ucExRabId, IMM_ZC_STRU *pData, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam)
{
    if (VOS_NULL_PTR == pData)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlAdsDataRcv, recv NULL PTR!");
        return PS_FAIL;
    }

    if ((PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
             || (ADS_PKT_TYPE_BUTT <= enPktType))
    {
        /*lint -e522*/
        IMM_ZcFree(pData);
        /*lint +e522*/
        NDIS_ERROR_LOG2(NDIS_TASK_PID, "Ndis_DlAdsDataRcv, recv RabId or PktType fail!", ucExRabId, enPktType);
        NDIS_STAT_DL_DISCARD_ADSPKT(1);
        return PS_FAIL;
    }

    /*增加从ADS接收到的数据包个数统计*/
    NDIS_STAT_DL_RECV_ADSPKT_SUCC(1);

    Ndis_LomTraceRcvDlData();
    if (PS_SUCC != Ndis_DlSendNcm(ucExRabId, enPktType, pData))
    {
        /*lint -e522*/
        IMM_ZcFree(pData);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlAdsDataRcv, Ndis_DlSendNcm fail!");
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : AppNdis_UsbReadCb
 功能描述  : App核间USB通道
 输入参数  : VOS_VOID *pBuf
             VOS_UINT32 ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月31日
    作    者   : 韩磊
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AppNdis_UsbReadCb(UDI_HANDLE ulhandle, VOS_VOID *pPktNode)
{
    IMM_ZC_STRU            *pstImmZc = (IMM_ZC_STRU*)pPktNode;    /*目前ImmZc和sk_buff完全一致，直接强转*/

    VOS_UINT8                   ucExRabId;
    VOS_UINT16                  usFrameType;
    ETHFRM_IPV4_PKT_STRU       *pstIpPacket;
    VOS_UINT8                  *pucData;

    if (VOS_NULL_PTR == pstImmZc)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "AppNdis_UsbReadCb read NULL PTR!");
        return PS_FAIL;
    }

    pucData = IMM_ZcGetDataPtr(pstImmZc);
    if (VOS_NULL_PTR == pucData)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, IMM_ZcGetDataPtr fail!");
        NDIS_STAT_UL_DISCARD_USBPKT(1);
        return PS_FAIL;
    }

    pstIpPacket = (ETHFRM_IPV4_PKT_STRU  *)(VOS_VOID*)pucData;
    usFrameType = pstIpPacket->usFrameType;

    /*这里获取的是扩展RabId*/
    ucExRabId = Ndis_FindRabIdByHandle(ulhandle, usFrameType);

    if (PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, Ndis_ChkRabIdValid fail!");
        NDIS_STAT_UL_DISCARD_USBPKT(1);
        return PS_FAIL;
    }

    NDIS_STAT_UL_RECV_USBPKT_SUCC(1);

    Ndis_LomTraceRcvUlData();
    Ndis_UlNcmFrmProc(ucExRabId, pstImmZc);

    return PS_SUCC;
}
/*****************************************************************************
 函 数 名  : AppNdis_SpeReadCb
 功能描述  : App核间SPE通道
 输入参数  : VOS_VOID *pBuf
             VOS_UINT32 ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月31日
    作    者   : c00253308
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AppNdis_SpeReadCb(VOS_INT32 lSpePort, VOS_VOID *pPktNode)
{
    IMM_ZC_STRU            *pstImmZc = (IMM_ZC_STRU*)pPktNode;    /*目前ImmZc和sk_buff完全一致，直接强转*/

    VOS_UINT16                  usFrameType;
    ETHFRM_IPV4_PKT_STRU       *pstIpPacket;
    VOS_UINT8                  *pucData;
    VOS_UINT8                   ucExRabId;
    if (VOS_NULL_PTR == pstImmZc)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "AppNdis_UsbReadCb read NULL PTR!");
        return PS_FAIL;
    }

    pucData = IMM_ZcGetDataPtr(pstImmZc);
    if (VOS_NULL_PTR == pucData)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, IMM_ZcGetDataPtr fail!");
       // NDIS_STAT_UL_DISCARD_USBPKT(1);
        return PS_FAIL;
    }

    pstIpPacket = (ETHFRM_IPV4_PKT_STRU  *)(VOS_VOID*)pucData;
    usFrameType = pstIpPacket->usFrameType;

    /*这里获取的是扩展RabId*/
    ucExRabId = Ndis_FindRabIdBySpePort(lSpePort, usFrameType);

    if (PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, Ndis_ChkRabIdValid fail!");
        //NDIS_STAT_UL_DISCARD_USBPKT(1);
        return PS_FAIL;
    }

    //NDIS_STAT_UL_RECV_USBPKT_SUCC(1);

    Ndis_LomTraceRcvUlData();
    Ndis_UlNcmFrmProc(ucExRabId, pstImmZc);

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_InitRegToAt
 功能描述  : NDIS向AT注册Client
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月28日
    作    者   : LPDCP_CIPHERINFO_FOR_ACC
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  Ndis_InitRegToAt( VOS_VOID )
{
    MsgBlock                        *pMsgBlock = VOS_NULL_PTR;
    AT_FW_CLIENT_REGISTER_REQ_STRU  *pRegClient = VOS_NULL_PTR;
    AT_FW_MSG_STRU                  *pAtMsg = VOS_NULL_PTR;
    VOS_UINT32                       ulRslt;

    pMsgBlock = (MsgBlock*)PS_ALLOC_MSG(NDIS_TASK_PID, sizeof(MsgBlock)+sizeof(AT_FW_MSG_STRU)+sizeof(AT_FW_CLIENT_REGISTER_REQ_STRU));
    if (VOS_NULL_PTR == pMsgBlock)
    {
        return PS_FAIL;
    }

    pMsgBlock->ulReceiverPid = APP_AT_PID;
    pMsgBlock->ulSenderPid   = NDIS_TASK_PID;
    /*lint -e826*/
    pAtMsg                   = (AT_FW_MSG_STRU*)((VOS_VOID*)(pMsgBlock->aucValue));
    /*lint +e826*/
    pAtMsg->ulMsgId          = ID_MSG_AT_FW_CLIENT_REGISTER_REQ;

    pRegClient = (AT_FW_CLIENT_REGISTER_REQ_STRU*)((VOS_VOID*)(pAtMsg->pMsgParam));
    pRegClient->bRegister          = TRUE;
    pRegClient->pstDiscardUrc      = NULL;
    pRegClient->ucClientId         = EN_AT_FW_CLIENT_ID_NDIS;
    pRegClient->ucSysMode          = AT_FW_SYS_MODE_NULL;
    pRegClient->ucInterfaceCfg     = AT_FW_PACKET_FMT_BINARY;

    ulRslt = PS_SEND_MSG(NDIS_TASK_PID, pMsgBlock);

    if (VOS_OK != ulRslt)
    {
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_NvItemInit
 功能描述  : A核NDIS读取NV项的初始化函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月24日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Ndis_NvItemInit(VOS_VOID)
{
    VOS_UINT32     ulRtn;
    VOS_UINT32     ulDhcpLeaseHour;
    VOS_UINT32     ulIpv6Mtu;
    NDIS_NV_DHCP_LEASE_HOUR_STRU   stNdisDhcpLeaseHour;
    NDIS_NV_IPV6_MTU_STRU          stNdisIPv6Mtu;

    /*
        DHCP Lease Time, 设定范围为[1, 8784]小时
        Vodafone    24小时
        其他        72小时

        时间经过DHCP Lease Time一半时，PC会主动发起续租，
        如果DHCP租约超期，则从PC通过NDIS通道发往单板的数据会出现目的不可达错误
        目前测试，当DHCP Lease Time小于等于4S时，对于数传影响较大，所以定义最小租约为1小时
        目前没有遇到超过8天的DHCP Lease Time，暂定上限为8784小时(366天)
        */

    /* 从NV读取流控配置信息 */
    /*lint -e718*/
    /*lint -e732*/
	/*lint -e746*/
    ulRtn = Ndis_NvimItem_Read(en_NV_Item_NDIS_DHCP_DEF_LEASE_TIME,\
                                    &stNdisDhcpLeaseHour,\
                                    sizeof(NDIS_NV_DHCP_LEASE_HOUR_STRU));
    if (PS_SUCC != ulRtn)
    {
        PS_PRINTF("Ndis_NvItemInit, Fail to read NV DHCP_LEASE_TIME: %d\n", ulRtn);
        return PS_FAIL;
    }
    else
    {
        /* NV值合法性判断 */
        ulDhcpLeaseHour = stNdisDhcpLeaseHour.ulDhcpLeaseHour;
        if((0 < ulDhcpLeaseHour) && (ulDhcpLeaseHour <= TTF_NDIS_DHCP_MAX_LEASE_HOUR))
        {
            /* hour -> second */
            g_ulLeaseTime = ulDhcpLeaseHour * 3600;
        }
    }

    /* 从NV读取IPV6 MTU信息 */
    ulRtn = Ndis_NvimItem_Read(en_NV_Item_IPV6_ROUTER_MTU,\
                                    &stNdisIPv6Mtu,\
                                    sizeof(NDIS_NV_IPV6_MTU_STRU));
	/*lint +e746*/
    /*lint +e732*/
    /*lint +e718*/

    if (PS_SUCC != ulRtn)
    {
        PS_PRINTF( "Ndis_NvItemInit, Fail to read NV IPV6_MTU: %d\n!", ulRtn);
        return PS_FAIL;
    }
    else
    {
        /* NV值合法性判断 */
        ulIpv6Mtu = stNdisIPv6Mtu.ulIpv6Mtu;
        if(0 == ulIpv6Mtu)
        {
            g_ulNvMtu = TTF_NDIS_IPV6_MTU_DEFAULT;
        }
        else
        {
            g_ulNvMtu = ulIpv6Mtu;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_Init
 功能描述  : APP核NDIS功能的初始化函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月10日
    作    者   : h00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Ndis_Init( VOS_VOID )
{
    VOS_UINT32     ulLoop;
    VOS_UINT8     *pucMacAddr;
    VOS_UINT16     usPayLoad;
    NDIS_ARP_PERIOD_TIMER_STRU    *pstArpPeriodTimer;

    #if (VOS_OS_VER != VOS_WIN32)
    #ifndef MSP_GUNAS_AT_UNITE
    if (PS_SUCC != Ndis_InitRegToAt())
    {
        PS_PRINTF("Ndis_Init, Reg to AT Fail!\n");
        return PS_FAIL;
    }
    #endif
    #endif

    /*lint -e746*/
    pucMacAddr = (VOS_UINT8 *)Ndis_GetMacAddr();                                 /*获得单板MAC地址*/
    /*lint -e746*/

    if (VOS_NULL_PTR == pucMacAddr)
    {
        PS_PRINTF("Ndis_Init, Ndis_GetMacAddr Fail!\n");
        return PS_FAIL;
    }

    usPayLoad = IP_PAYLOAD;
    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
        g_astNdisEntity[ulLoop].ucRabType  =  NDIS_RAB_NULL;
        g_astNdisEntity[ulLoop].ulHandle   =  NDIS_INVALID_HANDLE;
        g_astNdisEntity[ulLoop].ucRabId    =  NDIS_INVALID_RABID;
        g_astNdisEntity[ulLoop].enUsed     =  PS_FALSE;
        g_astNdisEntity[ulLoop].lSpePort   =  NDIS_INVALID_SPEPORT;
        g_astNdisEntity[ulLoop].ulSpeIpfFlag = PS_FALSE;
        PS_MEM_CPY(g_astNdisEntity[ulLoop].stIpV4Info.aucMacFrmHdr+ETH_MAC_ADDR_LEN,pucMacAddr,ETH_MAC_ADDR_LEN);
        PS_MEM_CPY(g_astNdisEntity[ulLoop].stIpV4Info.aucMacFrmHdr+(2*ETH_MAC_ADDR_LEN),(VOS_UINT8*)(&usPayLoad),2);

        /*周期性ARP定时器初始化*/
        pstArpPeriodTimer = &(g_astNdisEntity[ulLoop].stIpV4Info.stArpPeriodTimer);
        pstArpPeriodTimer->hTm          = VOS_NULL_PTR;
        pstArpPeriodTimer->ulName       = NDIS_PERIOD_ARP_TMRNAME;
        pstArpPeriodTimer->ulTimerValue = g_ulPeriodicArpCyc;
    }

    if (PS_SUCC != Ndis_NvItemInit())             /*NV项初始化*/
    {
        PS_PRINTF("Ndis_Init, Ndis_NvItemInit Fail!\n");
        return PS_FAIL;
    }

    return PS_SUCC;
}
/*****************************************************************************
 函 数 名  : Ndis_DlSendNcm
 功能描述  : 下行方向的NCM数据的发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月11日
    作    者   : h00133115
    修改内容   : 新生成函数
     2.日    期   : 2015年2月11日
    作    者   : c00253308
    修改内容   : SPE
*****************************************************************************/
VOS_UINT32 Ndis_DlSendNcm(VOS_UINT8 ucExRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT32                     ulResult;
    NDIS_ENTITY_STRU              *pstNdisEntity;
    #if (defined(CONFIG_BALONG_SPE))
    VOS_INT32                      lSpePort;
    #endif
    //UDI_HANDLE                     ulHandle;

        /*使用ExRabId获取NDIS实体*/
    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(IP_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, NDIS_GetEntityByRabId fail!");
        return PS_FAIL;
    }

   // ulHandle      = pstNdisEntity->ulHandle;

    #if (defined(CONFIG_BALONG_SPE))

    lSpePort      = pstNdisEntity->lSpePort;
    if (NDIS_INVALID_SPEPORT != lSpePort)
    {
        ulResult = Ndis_DlSpeSendNcm(pstNdisEntity,ucPktType,pstImmZc);
    }
    else
    {
        ulResult = Ndis_DlUsbSendNcm(ucExRabId, ucPktType, pstImmZc);
    }
    #else
    ulResult = Ndis_DlUsbSendNcm(ucExRabId, ucPktType, pstImmZc);
    #endif
    return ulResult;
}
#if (defined(CONFIG_BALONG_SPE))
/*****************************************************************************
 函 数 名  : Ndis_DlSpeSendNcm
 功能描述  : 下行方向的NCM数据发送到SPE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : c00253308
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 Ndis_DlSpeSendNcm(NDIS_ENTITY_STRU *pstNdisEntity, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc)
{

    VOS_INT32                      lSpePort;
    IMM_ZC_STRU                    *pstBuff;


    lSpePort = pstNdisEntity->lSpePort;

    if (PS_TRUE == pstNdisEntity->ulSpeIpfFlag)
    {
        IMM_ZcPush(pstImmZc,IMM_MAC_HEADER_RES_LEN);
        if ((ADS_PKT_TYPE_IPV4 == ucPktType)     /*包类型枚举*/
                  && (NDIS_ENTITY_IPV4 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV4)))
        {
             NDIS_SPE_SET_SKB_IPV4(pstImmZc);

        }
        else if ((ADS_PKT_TYPE_IPV6 == ucPktType)
                && (NDIS_ENTITY_IPV6 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV6)))
        {
             NDIS_SPE_SET_SKB_IPV6(pstImmZc);
        }
        else   /*数据包类型与承载支持类型不一致*/
        {
            NDIS_ERROR_LOG2(NDIS_TASK_PID, "Ndis_DlSendNcm, Rab is different from PktType!", pstNdisEntity->ucRabType, ucPktType);
            NDIS_STAT_DL_PKT_DIFF_RAB_NUM(1);
            return PS_FAIL;
        }
    }
    else
    {
        pstBuff = pstImmZc;
    }

    if (0 != NDIS_SPE_WPORT_XMIT(lSpePort, pstImmZc))
    {
        return PS_FAIL;
    }
    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NDIS_IsSpeMem
 功能描述  : 检查SPE内存
 输入参数  : pstImmZc --- imm memory
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NDIS_IsSpeMem(IMM_ZC_STRU *pstImmZc)
{
    return (0 != pstImmZc->spe_own);
}

/*****************************************************************************
 函 数 名  : NDIS_GetMemDma
 功能描述  : 获取SPE内存的物理地址
 输入参数  : pstImmZc --- imm memory
 输出参数  : 无
 返 回 值  : dma_addr_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
dma_addr_t NDIS_GetMemDma(IMM_ZC_STRU *pstImmZc)
{
    return NDIS_SPE_MEM_CB(pstImmZc)->ulDmaAddr;
}

/*****************************************************************************
 函 数 名  : RNIC_SpeMemMapRequset
 功能描述  : cache invalidate
 输入参数  : pstImmZc --- imm memory
             ulLen    --- cache size
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NDIS_SpeMemMapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen)
{
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    dma_addr_t                          ulDmaAddr;

    ulDmaAddr = NDIS_GetMemDma(pstImmZc);
    pucData   = phys_to_virt(ulDmaAddr);
    dma_map_single(VOS_NULL_PTR, pucData, ulLen, DMA_FROM_DEVICE);
    return;
}

/*****************************************************************************
 函 数 名  : RNIC_SpeMemUnmapRequset
 功能描述  : cache invalidate
 输入参数  : pstImmZc --- imm memory
             ulLen    --- cache size
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NDIS_SpeMemUnmapRequset(IMM_ZC_STRU *pstImmZc, VOS_UINT32 ulLen)
{
    dma_addr_t                          ulDmaAddr;

    ulDmaAddr = NDIS_GetMemDma(pstImmZc);
    dma_unmap_single(VOS_NULL_PTR, ulDmaAddr, ulLen, DMA_FROM_DEVICE);
    return;
}
#endif

/*****************************************************************************
 函 数 名  : Ndis_DlSendNcm
 功能描述  : 下行方向的NCM数据的发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月11日
    作    者   : h00133115
    修改内容   : 新生成函数

  2.日    期   : 2013年1月17日
    作    者   : h00218138
    修改内容   : DSDA开发，使用ExRabId获取NDIS实体

  3.日    期   : 2014年11月17日
    作    者   : c00253308
    修改内容   : SPE特性，把USB和SPE分开处理

*****************************************************************************/
VOS_UINT32 Ndis_DlUsbSendNcm(VOS_UINT8 ucExRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT8                      ucIndex;
    VOS_UINT8                     *pucAddData = VOS_NULL_PTR;
    UDI_HANDLE                     ulHandle;
    VOS_UINT32                     ulSize;
    NDIS_ENTITY_STRU              *pstNdisEntity;
    VOS_UINT8                      enTeAddrState;
    VOS_UINT16                     usApp = 0;
    VOS_UINT16                     usTmpApp = 0;

    /*使用ExRabId获取NDIS实体*/
    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(IP_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, NDIS_GetEntityByRabId fail!");
        return PS_FAIL;
    }

    ulHandle      = pstNdisEntity->ulHandle;

    /*填充MAC帧头，调用ImmZc接口将MAC帧头填入ImmZc中*/
    if ((ADS_PKT_TYPE_IPV4 == ucPktType)     /*包类型枚举*/
           && (NDIS_ENTITY_IPV4 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV4)))
    {
        pucAddData = pstNdisEntity->stIpV4Info.aucMacFrmHdr;
    }
    else if ((ADS_PKT_TYPE_IPV6 == ucPktType)
           && (NDIS_ENTITY_IPV6 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV6)))
    {
        ucIndex = (VOS_UINT8)IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);
        if (ucIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
        {
            NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, IP_NDSERVER_GET_ADDR_INFO_INDEX fail!");
            return PS_FAIL;
        }

        pucAddData = NdSer_GetMacFrm(ucIndex, &enTeAddrState);
        if (VOS_NULL_PTR == pucAddData)
        {
            NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, NdSer_GetMacFrm fail!");
            NDIS_STAT_DL_GET_IPV6MAC_FAIL(1);
            return PS_FAIL;
        }

        if (IP_NDSERVER_TE_ADDR_REACHABLE != enTeAddrState)
        {
            /*将ucExRabId和数据包类型放入ImmZc的私有数据域中*/
            usTmpApp = (ucPktType & 0xFF);
            usApp    = ((VOS_UINT16)(usTmpApp << 8)) | (ucExRabId);
            IMM_ZcSetUserApp(pstImmZc, usApp);

            NdSer_MacAddrInvalidProc(pstImmZc, ucIndex);
            return PS_SUCC;
        }
    }
    else   /*数据包类型与承载支持类型不一致*/
    {
        NDIS_ERROR_LOG2(NDIS_TASK_PID, "Ndis_DlSendNcm, Rab is different from PktType!", pstNdisEntity->ucRabType, ucPktType);
        NDIS_STAT_DL_PKT_DIFF_RAB_NUM(1);
        return PS_FAIL;
    }

    if (VOS_OK != IMM_ZcAddMacHead(pstImmZc, pucAddData))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DlSendNcm, IMM_ZcAddMacHead fail!");
        NDIS_STAT_DL_ADDMACFRM_FAIL(1);
        return PS_FAIL;
    }

    ulSize = IMM_ZcGetUsedLen(pstImmZc);         /*加上以太网帧头的长度*/

    /*lint -e718*/
    if (0 != NDIS_UDI_WRITE(ulHandle, pstImmZc, ulSize))
    {
        NDIS_STAT_DL_SEND_USBPKT_FAIL(1);
        return PS_FAIL;
    }
    /*lint +e718*/

    NDIS_STAT_DL_SEND_USBPKT_SUCC(1);
    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_ProcTmrMsg
 功能描述  : 处理TmerMsg
 输入参数  : MsgBlock *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

  1.日    期   : 2012年4月28日
    作    者   : h00159435
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID Ndis_ProcARPTimerExp(VOS_VOID)
{
    VOS_UINT32                   ulLoop;
    NDIS_ENTITY_STRU            *pstNdisEntity;
    NDIS_IPV4_INFO_STRU         *pstIpV4Info;
    NDIS_ARP_PERIOD_TIMER_STRU  *pstArpPeriodTimer;

    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
        pstNdisEntity = &g_astNdisEntity[ulLoop];
        if (NDIS_ENTITY_IPV4 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV4))
        {
            pstIpV4Info = &(pstNdisEntity->stIpV4Info);
            pstArpPeriodTimer = &(pstIpV4Info->stArpPeriodTimer);

            if (PS_TRUE == pstIpV4Info->ulArpInitFlg)
            {
                #if (VOS_OS_VER != VOS_WIN32)
                Ndis_StopARPTimer(pstArpPeriodTimer);
                #endif
            }
            else
            {
                (VOS_VOID)Ndis_SendRequestArp(&(pstNdisEntity->stIpV4Info), pstNdisEntity->ucRabId);
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : Ndis_ProcTmrMsg
 功能描述  : 处理TmerMsg
 输入参数  : MsgBlock *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2012年4月28日
    作    者   : h00159435
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID Ndis_ProcTmrMsg(const REL_TIMER_MSG *pRcvMsg)
{
    switch(pRcvMsg->ulName)
    {
        case NDIS_PERIOD_ARP_TMRNAME:
            Ndis_ProcARPTimerExp();
            break;
        default:
            NDIS_INFO_LOG1(NDIS_TASK_PID, "Ndis_ProcTmrMsg, Recv other Timer", pRcvMsg->ulName);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Ndis_DHCPPkt_Proc
 功能描述  : DHCP处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月11日
    作    者   : h00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Ndis_DHCPPkt_Proc(VOS_VOID *pRcvMsg)
{
    ADS_NDIS_DATA_IND_STRU  *pstAdsNdisMsg  = (ADS_NDIS_DATA_IND_STRU*)pRcvMsg;
    VOS_UINT8               *pucData;
    NDIS_ENTITY_STRU        *pstNdisEntity;
    VOS_UINT8                ucExRabId;

    pucData  = IMM_ZcGetDataPtr(pstAdsNdisMsg->pstSkBuff);
    if (VOS_NULL_PTR == pucData)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DHCPPkt_Proc, IMM_ZcGetDataPtr fail!");
        return;
    }

    ucExRabId = NDIS_FORM_EXBID(pstAdsNdisMsg->enModemId, pstAdsNdisMsg->ucRabId);
    if (PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DHCPPkt_Proc, Ndis_ChkRabIdValid fail!");
        return;
    }

    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DHCPPkt_Proc, NDIS_GetEntityByRabId fail!");
        return;
    }

    if (NDIS_ENTITY_IPV4 != (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV4))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_DHCPPkt_Proc, Rab not support IPV4!");
        return;
    }

    /*DHCP处理*/
    NDIS_STAT_UL_RECV_DHCPPKT(1);
    IPV4_DHCP_ProcDhcpPkt(pucData, ucExRabId);

    return;
}
/*****************************************************************************
 函 数 名  : Ndis_FindRabIdBySpePort
 功能描述  : 根据SpePort查找RabId
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : c00253308
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 Ndis_FindRabIdBySpePort(VOS_INT32 lPort, VOS_UINT16 usFrameType)
{
    VOS_UINT32                      ulLoop;
    VOS_UINT8                       ucTmpRabType;
    NDIS_ENTITY_STRU               *pstNdisEntity;

    switch(usFrameType)
    {
        case ARP_PAYLOAD:
            ucTmpRabType = NDIS_ENTITY_IPV4;    /*ARP包也经过SPE*/
            break;
        case IP_PAYLOAD:
            ucTmpRabType = NDIS_ENTITY_IPV4;
            break;
        case IPV6_PAYLOAD:
            ucTmpRabType = NDIS_ENTITY_IPV6;
            break;
        default:
            NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_FindRabIdByHandle, FrameType Error!", usFrameType);
            return NDIS_INVALID_RABID;
    }
    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
         pstNdisEntity = &g_astNdisEntity[ulLoop];

         if ((lPort == pstNdisEntity->lSpePort)
                && (ucTmpRabType == (pstNdisEntity->ucRabType & ucTmpRabType)))   /*数据包类型与承载类型一致*/
         {
             return pstNdisEntity->ucRabId;
         }
    }

    return NDIS_INVALID_RABID;

}

/*****************************************************************************
 函 数 名  : Ndis_FindRabIdByHandle
 功能描述  : 根据Handle查找RabId
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 Ndis_FindRabIdByHandle(UDI_HANDLE ulhandle, VOS_UINT16 usFrameType)
{
    VOS_UINT32                      ulLoop;
    VOS_UINT8                       ucTmpRabType;
    NDIS_ENTITY_STRU               *pstNdisEntity;

    if ((ARP_PAYLOAD == usFrameType) || (IP_PAYLOAD == usFrameType))
    {
        ucTmpRabType = NDIS_ENTITY_IPV4;
    }
    else if (IPV6_PAYLOAD == usFrameType)
    {
        ucTmpRabType = NDIS_ENTITY_IPV6;
    }
    else
    {
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_FindRabIdByHandle, FrameType Error!", usFrameType);
        return NDIS_INVALID_RABID;
    }

    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
         pstNdisEntity = &g_astNdisEntity[ulLoop];

         if ((ulhandle == pstNdisEntity->ulHandle)
              && (ucTmpRabType == (pstNdisEntity->ucRabType & ucTmpRabType)))   /*数据包类型与承载类型一致*/
         {
             return pstNdisEntity->ucRabId;
         }
    }

    return NDIS_INVALID_RABID;

}

/*****************************************************************************
 函 数 名  : Ndis_UlNcmFrmProc
 功能描述  : 对上行NCM帧的处理
 输入参数  : UDI_HANDLE ulhandle, IMM_ZC_STRU *pstImmZc
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月11日
    作    者   : h00133115
    修改内容   : 新生成函数

  2.日    期   : 2013年1月16日
    作    者   : h00218138
    修改内容   : DSDA开发

*****************************************************************************/
VOS_VOID Ndis_UlNcmFrmProc(VOS_UINT8 ucExRabId, IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT16                  usFrameType;
    ETHFRM_IPV4_PKT_STRU       *pstIpPacket;
    ETH_IPFIXHDR_STRU          *pstIpFixHdr;
    VOS_UINT8                  *pucData;
    VOS_UINT32                  ulDataLen;
    VOS_UINT32                  ulIpLen;
    VOS_UINT32                  ulIpv4Flag = 0;
    VOS_UINT32                  ulCacheLen;

    pucData = IMM_ZcGetDataPtr(pstImmZc);
    if (VOS_NULL_PTR == pucData)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, IMM_ZcGetDataPtr fail!");
        NDIS_STAT_UL_DISCARD_USBPKT(1);
        return;
    }

    pstIpPacket = (ETHFRM_IPV4_PKT_STRU  *)(VOS_VOID*)pucData;
    usFrameType = pstIpPacket->usFrameType;

    /*ARP处理*/
    if(ARP_PAYLOAD == usFrameType)
    {
        /*ARP处理函数入参中增加RabId，后续以RabId作为Ndis实体遍历索引*/
        (VOS_VOID)Ndis_ProcArpMsg((ETH_ARP_FRAME_STRU*)(VOS_VOID*)pstIpPacket, ucExRabId);

        /*处理完ARP后调用Imm_ZcFree释放ImmZc*/
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/

        return;
    }
     /*IPV6超长包处理*/
    if (IPV6_PAYLOAD == usFrameType)
    {
        ulDataLen = IMM_ZcGetUsedLen(pstImmZc);

        if ((ulDataLen - ETH_MAC_HEADER_LEN) > g_ulNvMtu)
        {
            NDIS_SPE_MEM_UNMAP(pstImmZc, ulDataLen);

            IP_NDSERVER_ProcTooBigPkt(ucExRabId,
                                      ((VOS_UINT8*)pstIpPacket + ETH_MAC_HEADER_LEN),
                                      g_ulNvMtu);

            NDIS_SPE_MEM_MAP(pstImmZc, ulDataLen);

            /*调用Imm_ZcFree释放ImmZc*/
            /*lint -e522*/
            IMM_ZcFree(pstImmZc);
            /*lint +e522*/

            return;
        }
    }

    if (IP_PAYLOAD == usFrameType)
    {
        ulIpv4Flag = 1;
        ulDataLen  = IMM_ZcGetUsedLen(pstImmZc);
        ulCacheLen = (ulDataLen < NDIS_SPE_CACHE_HDR_SIZE) ?
                        ulDataLen : NDIS_SPE_CACHE_HDR_SIZE;
    }

    /*经MAC层过滤后剩余的IP包发送，去掉MAC帧头后递交ADS*/
    if (VOS_OK != IMM_ZcRemoveMacHead(pstImmZc))
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, IMM_ZcRemoveMacHead fail!");
        return;
    }

    /*检查IPV4包长度和实际Skb长度，如果不一致，则修改Skb长度为实际IP包长度*/
    if (1 == ulIpv4Flag)
    {
        pucData = IMM_ZcGetDataPtr(pstImmZc);
        if (VOS_NULL_PTR == pucData)
        {
            /*lint -e522*/
            IMM_ZcFree(pstImmZc);
            /*lint +e522*/
            return;
        }

        NDIS_SPE_MEM_UNMAP(pstImmZc, ulCacheLen);

        pstIpFixHdr = (ETH_IPFIXHDR_STRU *)((VOS_VOID*)pucData);
        ulIpLen = IP_NTOHS(pstIpFixHdr->usTotalLen);
        if (ulIpLen < pstImmZc->len)
        {
            pstImmZc->tail -= (pstImmZc->len - ulIpLen);
            pstImmZc->len  = ulIpLen;
        }

        NDIS_SPE_MEM_MAP(pstImmZc, ulCacheLen);
    }

    if (VOS_OK != ADS_UL_SendPacket(pstImmZc, ucExRabId))
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_UlNcmFrmProc, ADS_UL_SendPacket fail!");
        return;
    }

    NDIS_STAT_UL_SEND_ADSPKT(1);

    return;
}

/*****************************************************************************
 函 数 名  : APP_Ndis_DLPid_InitFunc
 功能描述  : APP NDIS下行PID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ePhase
 输出参数  : 无
 返 回 值  : extern VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月15日
    作    者   : h00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  APP_Ndis_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ePhase)
{
    VOS_UINT32  ulResult = PS_FAIL;

    switch( ePhase )
    {
        case   VOS_IP_LOAD_CONFIG:

            ulResult = Ndis_Init();

            if (PS_SUCC != ulResult)
            {
                PS_PRINTF("APP_Ndis_Pid_InitFunc, Ndis_Init fail!\n");
                return VOS_ERR;
            }
            break;
        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Ndis_SendMacFrm
 功能描述  : 发送以太网帧接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月14日
    作    者   : h00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Ndis_SendMacFrm(const VOS_UINT8  *pucBuf, VOS_UINT32 ulLen, VOS_UINT8 ucExRabId)
{
    IMM_ZC_STRU      *pstImmZc = VOS_NULL_PTR;
    VOS_INT32         lRtn;
    UDI_HANDLE        ulHandle;
    VOS_UINT8        *ucPdata;
    NDIS_ENTITY_STRU *pstNdisEntity;

    if (VOS_NULL_PTR == pucBuf)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, pucBuf is NULL!");
        return PS_FAIL;
    }

    pstImmZc = IMM_ZcStaticAlloc(ulLen);
    if (VOS_NULL_PTR == pstImmZc)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, IMM_ZcStaticAlloc fail!");
        return PS_FAIL;
    }

    ucPdata = (VOS_UINT8*)IMM_ZcPut(pstImmZc, ulLen);             /*与yinweidong确认的*/
    if (VOS_NULL_PTR == ucPdata)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, IMM_ZcPut fail!");
        return PS_FAIL;
    }

    PS_MEM_CPY(ucPdata,pucBuf,ulLen);

    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if (VOS_NULL_PTR == pstNdisEntity)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, NDIS_GetEntityByRabId fail!");
        return PS_FAIL;
    }

    ulHandle      = pstNdisEntity->ulHandle;

    /*数据发送*/
    lRtn = NDIS_UDI_WRITE(ulHandle, pstImmZc, ulLen);

    if (0 != lRtn)
    {
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_SendMacFrm, udi_write fail!");
        NDIS_STAT_DL_SEND_ARPDHCPPKT_FAIL(1);
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_ProcReqArp
 功能描述  : 处理ARP Request 帧
 输入参数  :

 输出参数  : 无
 返 回 值  : 成功返回PS_SUCC;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月11日
    作    者   : h00133115
    修改内容   : 新生成函数
  2.日    期   : 2013年1月22日
  作    者   : h00218138
  修改内容   : DSDA

*****************************************************************************/

VOS_UINT32 Ndis_ProcReqArp(ETH_ARP_FRAME_STRU *pstReqArp, VOS_UINT8 ucRabId)
{
    VOS_UINT32                  ulTgtIpAddr  = pstReqArp->unTargetIP.ulIpAddr;
    NDIS_ENTITY_STRU           *pstNdisEntity = VOS_NULL_PTR;
    NDIS_IPV4_INFO_STRU        *pstArpV4Info  = VOS_NULL_PTR;

    pstNdisEntity = NDIS_GetEntityByRabId(ucRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_ProcReqArp,  NDIS_GetEntityByRabId Error!", ucRabId);
        NDIS_STAT_PROC_ARP_FAIL(1);
        return PS_FAIL;
    }

    pstArpV4Info  = &pstNdisEntity->stIpV4Info;

    /*目标地址既不是网关地址， 也不和网关地址在同一网段内*/
    if ( (ulTgtIpAddr != pstArpV4Info->unGwIpInfo.ulIpAddr)
        && ((ulTgtIpAddr & pstArpV4Info->unNmIpInfo.ulIpAddr) !=
           (pstArpV4Info->unGwIpInfo.ulIpAddr & pstArpV4Info->unNmIpInfo.ulIpAddr)))  /*目标地址和网关地址在同一网段*/
    {
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_ProcReqArp,  TargetIpaddr Error!", ulTgtIpAddr);
        NDIS_STAT_PROC_ARP_FAIL(1);
        return PS_FAIL;
    }

    if ((0 != pstReqArp->unSenderIP.ulIpAddr)     /*兼容MAC OS 免费ARP类型,其Sender IP为0*/
           && (pstArpV4Info->unUeIpInfo.ulIpAddr != pstReqArp->unSenderIP.ulIpAddr))
    {
        /*源UE IP与网侧配置不符，这种情况不处理*/
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_ProcReqArp,  SenderIP Error!", pstReqArp->unSenderIP.ulIpAddr);
        NDIS_STAT_PROC_ARP_FAIL(1);
        return PS_SUCC;
    }

    /*更新PC MAC地址*/
    PS_MEM_CPY(pstArpV4Info->aucUeMacAddr,pstReqArp->aucSenderAddr,ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(pstArpV4Info->aucMacFrmHdr,pstReqArp->aucSenderAddr,ETH_MAC_ADDR_LEN);

    pstArpV4Info->ulArpInitFlg  = PS_TRUE;

    PS_MEM_CPY(g_stSpeMacHeader.aucSrcAddr,(pstArpV4Info->aucMacFrmHdr + ETH_MAC_ADDR_LEN),ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(g_stSpeMacHeader.aucDstAddr,pstReqArp->aucSrcAddr,ETH_MAC_ADDR_LEN);

    #if (defined(CONFIG_BALONG_SPE))
    if (PS_TRUE == pstNdisEntity->ulSpeIpfFlag)
    {
        if (VOS_OK != NDIS_SPE_WPORT_IOCTL(pstNdisEntity->lSpePort, SPE_WPORT_IOCTL_SET_MAC, (VOS_VOID *)&g_stSpeMacHeader))
        {
             NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_ProcReqArp, Set MAC header fail!");
             return PS_FAIL;
        }
    }
    #endif

    /*免费ARP不回复响应*/
    if ((pstReqArp->unTargetIP.ulIpAddr == pstReqArp->unSenderIP.ulIpAddr)
        || (0 == pstReqArp->unSenderIP.ulIpAddr))
    {
        return PS_SUCC;
    }

    /*发送响应*/
    PS_MEM_CPY(pstReqArp->aucDstAddr,pstReqArp->aucSrcAddr,ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(pstReqArp->aucTargetAddr,pstReqArp->aucSrcAddr,ETH_MAC_ADDR_LEN);
    pstReqArp->unTargetIP.ulIpAddr = pstReqArp->unSenderIP.ulIpAddr;

    PS_MEM_CPY(pstReqArp->aucSrcAddr, (pstArpV4Info->aucMacFrmHdr + ETH_MAC_ADDR_LEN), ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(pstReqArp->aucSenderAddr, (pstArpV4Info->aucMacFrmHdr + ETH_MAC_ADDR_LEN), ETH_MAC_ADDR_LEN);

    pstReqArp->unSenderIP.ulIpAddr = ulTgtIpAddr;

    /*opcode*/
    pstReqArp->usOpCode = ETH_ARP_RSP_TYPE;

    /*发送ARP Reply*/
    NDIS_STAT_DL_SEND_ARP_REPLY(1);
    (VOS_VOID)Ndis_SendMacFrm((VOS_UINT8*)pstReqArp,sizeof(ETH_ARP_FRAME_STRU),ucRabId);

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_ProcReplyArp
 功能描述  : 处理ARP Reply 帧,更新PC的MAC地址
 输入参数  :

 输出参数  : 无
 返 回 值  : 成功返回PS_SUCC;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月31日
    作    者   : y00151394
    修改内容   : 新生成函数
  2.日    期   : 2013年1月22日
    作    者   : h00218138
    修改内容   : DSDA
*****************************************************************************/
VOS_UINT32 Ndis_ProcReplyArp(const ETH_ARP_FRAME_STRU *pstRspArp, VOS_UINT8 ucRabId)
{
    NDIS_IPV4_INFO_STRU         *pstArpV4Info = VOS_NULL_PTR;
    VOS_UINT32                   ulTargetIP   = pstRspArp->unTargetIP.ulIpAddr;
    NDIS_ENTITY_STRU            *pstNdisEntity;

    pstNdisEntity = NDIS_GetEntityByRabId(ucRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        NDIS_ERROR_LOG1(NDIS_TASK_PID, "Ndis_ProcReplyArp,  NDIS_GetEntityByRabId Error!", ucRabId);
        return PS_FAIL;
    }

    pstArpV4Info  = &pstNdisEntity->stIpV4Info;

    if (ulTargetIP == pstNdisEntity->stIpV4Info.unGwIpInfo.ulIpAddr)
    {
        /*更新PC MAC地址*/
        PS_MEM_CPY(pstArpV4Info->aucUeMacAddr,pstRspArp->aucSenderAddr,ETH_MAC_ADDR_LEN);
        PS_MEM_CPY(pstArpV4Info->aucMacFrmHdr,pstRspArp->aucSenderAddr,ETH_MAC_ADDR_LEN);
        pstArpV4Info->ulArpInitFlg  = PS_TRUE;

        pstArpV4Info->ulArpRepFlg = PS_TRUE;

        return PS_SUCC;
    }

    return PS_FAIL;
}

/*****************************************************************************
 函 数 名  : Ndis_Ipv4PdnInfoCfg
 功能描述  : IPV4 PDN信息配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月15日
    作    者   : h00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  Ndis_Ipv4PdnInfoCfg(const AT_NDIS_IPV4_PDN_INFO_STRU *pstNasNdisInfo,
                                           NDIS_ENTITY_STRU  *pstNdisEntity)
{
    NDIS_IPV4_INFO_STRU         *pstIpV4Info    = &(pstNdisEntity->stIpV4Info);

    pstIpV4Info->ulArpInitFlg = PS_FALSE;
    pstIpV4Info->ulArpRepFlg  = PS_FALSE;

    PS_MEM_CPY(pstIpV4Info->unUeIpInfo.aucIPAddr,
               pstNasNdisInfo->stPDNAddrInfo.aucIpV4Addr,
               IPV4_ADDR_LEN);

    PS_MEM_CPY(pstIpV4Info->unGwIpInfo.aucIPAddr,
               pstNasNdisInfo->stGateWayAddrInfo.aucIpV4Addr,
               IPV4_ADDR_LEN);

    PS_MEM_CPY(pstIpV4Info->unNmIpInfo.aucIPAddr,
               pstNasNdisInfo->stSubnetMask.aucIpV4Addr,
               IPV4_ADDR_LEN);

    /*使能则配置DNS*/
    if (PS_TRUE == pstNasNdisInfo->bitOpDnsPrim)
    {
        PS_MEM_CPY(pstIpV4Info->unPrimDnsAddr.aucIPAddr,
                   pstNasNdisInfo->stDnsPrimAddrInfo.aucIpV4Addr,
                   IPV4_ADDR_LEN);
    }
    else
    {
        pstIpV4Info->unPrimDnsAddr.ulIpAddr = 0;
    }

    /*使能则配置辅DNS*/
    if (PS_TRUE == pstNasNdisInfo->bitOpDnsSec)
    {
        PS_MEM_CPY(pstIpV4Info->unSecDnsAddr.aucIPAddr,
                   pstNasNdisInfo->stDnsSecAddrInfo.aucIpV4Addr,
                   IPV4_ADDR_LEN);
    }
    else
    {
        pstIpV4Info->unSecDnsAddr.ulIpAddr = 0;
    }

    /*使能则配置主WINS*/
    if (PS_TRUE == pstNasNdisInfo->bitOpWinsPrim)
    {
        PS_MEM_CPY(pstIpV4Info->unPrimWinsAddr.aucIPAddr,
                   pstNasNdisInfo->stWinsPrimAddrInfo.aucIpV4Addr,
                   IPV4_ADDR_LEN);
    }
    else
    {
        pstIpV4Info->unPrimWinsAddr.ulIpAddr = 0;
    }

    /*使能则配置辅WINS*/
    if (PS_TRUE == pstNasNdisInfo->bitOpWinsSec)
    {
        PS_MEM_CPY(pstIpV4Info->unSecWinsAddr.aucIPAddr,
                   pstNasNdisInfo->stWinsSecAddrInfo.aucIpV4Addr,
                   IPV4_ADDR_LEN);
    }
    else
    {
        pstIpV4Info->unSecWinsAddr.ulIpAddr = 0;
    }

    /*PCSCF暂时不操作,待需求描述*/

    pstIpV4Info->ulIpAssignStatus = IPV4_DHCP_ADDR_STATUS_FREE;

    return;
}

/*****************************************************************************
 函 数 名  : Ndis_StartARPTimer
 功能描述  : NDIS启动周期性ARP定时器
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月19日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Ndis_StartARPTimer(NDIS_ENTITY_STRU *pstNdisEntity)
{
    #if (VOS_OS_VER != VOS_WIN32)
    VOS_UINT32                      ulRtn;
    NDIS_ARP_PERIOD_TIMER_STRU     *pstArpPeriodTimer;

    /*入参指针判断*/
    if (VOS_NULL_PTR == pstNdisEntity)
    {
        return PS_FAIL;
    }

    /*检查是否需要启动ARP定时器*/
    if ((NDIS_ENTITY_IPV4 != (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV4))
            || (PS_TRUE == pstNdisEntity->stIpV4Info.ulArpInitFlg))
    {
        return PS_SUCC;
    }

    pstArpPeriodTimer = &(pstNdisEntity->stIpV4Info.stArpPeriodTimer);

    /*如果还在运行，则停掉*/
    if (VOS_NULL_PTR != pstArpPeriodTimer->hTm)
    {
        Ndis_StopARPTimer(pstArpPeriodTimer);
    }

    ulRtn = VOS_StartRelTimer(&(pstArpPeriodTimer->hTm),PS_PID_APP_NDIS,pstArpPeriodTimer->ulTimerValue,
                               pstArpPeriodTimer->ulName,0, VOS_RELTIMER_LOOP, VOS_TIMER_PRECISION_0);
    if (VOS_OK != ulRtn)
    {
        pstArpPeriodTimer->hTm = VOS_NULL_PTR;
        return PS_FAIL;
    }
    #endif

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_StopARPTimer
 功能描述  : NDIS停止周期性ARP定时器
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月19日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Ndis_StopARPTimer(NDIS_ARP_PERIOD_TIMER_STRU *pstArpPeriodTimer)
{
    if (VOS_NULL_PTR != pstArpPeriodTimer->hTm)
    {
        if (VOS_OK != VOS_StopRelTimer(&(pstArpPeriodTimer->hTm)))
        {
            NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_StopARPTimer, VOS_StopRelTimer fail!");
        }
        pstArpPeriodTimer->hTm = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Ndis_SndMsgToAt
 功能描述  : 发送Cnf消息到AT
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月16日
    作    者   : h00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Ndis_SndMsgToAt(const VOS_UINT8 *pucBuf,VOS_UINT16 usMsgLen,VOS_UINT32 ulMsgId)
{
    VOS_UINT32                    ulAllocSize;
    AT_FW_MSG_STRU               *pstFwMsg    = VOS_NULL_PTR;
    AT_FW_CMD_BINARY_MSG_STRU    *pstAtCnf    = VOS_NULL_PTR;
    MsgBlock                     *pstMsgBlock = VOS_NULL_PTR;

    /*消息体比实际大了一点，处理方便*/
    ulAllocSize = sizeof(MsgBlock) + sizeof(AT_FW_MSG_STRU)
                  + sizeof(AT_FW_CMD_BINARY_MSG_STRU) + usMsgLen;

    pstMsgBlock = PS_ALLOC_MSG(NDIS_TASK_PID,ulAllocSize);
    if (VOS_NULL_PTR == pstMsgBlock)
    {
        return PS_FAIL;
    }

    /*lint -e826*/
    pstFwMsg          = (AT_FW_MSG_STRU *)(VOS_VOID*)(pstMsgBlock->aucValue);
    pstFwMsg->ulMsgId = ID_MSG_AT_FW_CMD_BINARY_MSG;

    pstAtCnf  = (AT_FW_CMD_BINARY_MSG_STRU  *)((VOS_VOID*)pstFwMsg->pMsgParam);
    /*lint +e826*/
    pstAtCnf->usMsgSize  = usMsgLen;
    pstAtCnf->ulMsgId    = ulMsgId;
    pstAtCnf->ucClientId = EN_AT_FW_CLIENT_ID_NDIS;   /*待MSP完整头文件*/
    pstAtCnf->ucSysMode  = AT_FW_SYS_MODE_NULL;

    pstMsgBlock->ulSenderPid   = NDIS_TASK_PID;
    pstMsgBlock->ulReceiverPid = APP_AT_PID;

    PS_MEM_CPY(pstAtCnf->pMsg,pucBuf,usMsgLen);

    if(VOS_OK != PS_SEND_MSG(NDIS_TASK_PID, pstMsgBlock))
    {
        /*异常打印*/
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_ChkRabIdValid
 功能描述  : Ndis检查ExRabId取值是否在合法范围内
 输入参数  :

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月7日
    作    者   : h00159435
    修改内容   : 新生成函数

  2.日    期   : 2013年1月15日
    作    者   : h00218138
    修改内容   : DSDA特性开发:对ModemID和RabId均做检查

*****************************************************************************/
VOS_UINT32 Ndis_ChkRabIdValid(VOS_UINT8 ucExRabId)
{
    VOS_UINT16 usModemId;
    VOS_UINT8 ucRabId;

    usModemId = NDIS_GET_MODEMID_FROM_EXBID(ucExRabId);
    if (usModemId >= MODEM_ID_BUTT)
    {
        return PS_FAIL;
    }

    ucRabId = NDIS_GET_BID_FROM_EXBID(ucExRabId);
    if ((ucRabId < MIN_VAL_EPSID) || (ucRabId > MAX_VAL_EPSID))
    {
        return PS_FAIL;
    }

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : NDIS_GetEntityByRabId
 功能描述  : 根据ExRabId查找NDIS实体
 输入参数  : VOS_UINT8 ucExRabId
 输出参数  : 无
 返 回 值  : NDIS_ENTITY_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : h00218138
    修改内容   : 新生成函数

*****************************************************************************/
NDIS_ENTITY_STRU* NDIS_GetEntityByRabId(VOS_UINT8 ucExRabId)
{
    VOS_UINT16 i = 0;

    /* 查询是否已存在相应Entity */
    do{
        if((PS_TRUE == g_astNdisEntity[i].enUsed) && (ucExRabId == g_astNdisEntity[i].ucRabId))
        {
            /*找到相应实体*/
            return &g_astNdisEntity[i];
        }

    }while((++i) < NAS_NDIS_MAX_ITEM);

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : NDIS_AllocEntity
 功能描述  : 分配一个空闲的NDIS实体
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NDIS_ENTITY_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : h00218138
    修改内容   : 新生成函数

*****************************************************************************/
NDIS_ENTITY_STRU* NDIS_AllocEntity(VOS_VOID)
{
    VOS_UINT16 i = 0;

    /* 返回第一个空闲的实体*/
    do{
        if(PS_FALSE == g_astNdisEntity[i].enUsed)
        {
            /*找到空闲实体*/
            return &g_astNdisEntity[i];
        }

    }while((++i) < NAS_NDIS_MAX_ITEM);

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : Ndis_CheckIpv4PdnInfo
 功能描述  : PDN IPV4地址信息检查
 输入参数  : AT_NDIS_IPV4_PDN_INFO_STRU
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月11日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Ndis_CheckIpv4PdnInfo(const AT_NDIS_IPV4_PDN_INFO_STRU *pstIpv4PdnInfo)
{
    if (PS_FALSE == pstIpv4PdnInfo->bitOpPdnAddr)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_CheckIpv4PdnInfo,  pstIpv4PdnInfo->bitOpPdnAddr is false!");
        return PS_FAIL;
    }

    /*PDN地址和网关地址如果为全0，则也失败*/
    if (0 == VOS_MemCmp(pstIpv4PdnInfo->stPDNAddrInfo.aucIpV4Addr, g_aucInvalidAddr, IPV4_ADDR_LEN))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_CheckIpv4PdnInfo,  stPDNAddrInfo all zero!");
        return PS_FAIL;
    }

    if (0 == VOS_MemCmp(pstIpv4PdnInfo->stGateWayAddrInfo.aucIpV4Addr, g_aucInvalidAddr, IPV4_ADDR_LEN))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_CheckIpv4PdnInfo,  stGateWayAddrInfo all zero!");
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_PdnCheckParaValid
 功能描述  : 检查参数配置参数是否合法
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月23日
    作    者   : LPDCP_CIPHERINFO_FOR_ACC
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  Ndis_PdnV4PdnCfg( const AT_NDIS_PDNINFO_CFG_REQ_STRU *pstNasNdisInfo,
                                     NDIS_ENTITY_STRU  *pstNdisEntity)
{
    /*IPV4地址检查*/
    if (PS_FALSE == pstNasNdisInfo->bitOpIpv4PdnInfo)  /*原语指示IPV4信息无效 */
    {
        NDIS_INFO_LOG(NDIS_TASK_PID, "Ndis_PdnV4PdnCfg,  bitOpIpv4PdnInfo is false!");
        return PS_FAIL;
    }

    if (PS_SUCC != Ndis_CheckIpv4PdnInfo(&(pstNasNdisInfo->stIpv4PdnInfo)))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnV4PdnCfg,  Ndis_CheckIpv4PdnInfo fail!");
        return PS_FAIL;
    }

    Ndis_Ipv4PdnInfoCfg(&(pstNasNdisInfo->stIpv4PdnInfo),pstNdisEntity);

    /*更新NDIS实体承载属性*/
    pstNdisEntity->ucRabType |= NDIS_ENTITY_IPV4;

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_PdnV6PdnCfg
 功能描述  : IPV6 PDN信息配置
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月23日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  Ndis_PdnV6PdnCfg( AT_NDIS_PDNINFO_CFG_REQ_STRU *pstNasNdisInfo,
                                     NDIS_ENTITY_STRU  *pstNdisEntity)
{
    VOS_UINT8                       ucExRabId;

    /*IPV6地址检查*/
    if (PS_FALSE == pstNasNdisInfo->bitOpIpv6PdnInfo)  /*原语指示IPV6信息无效*/
    {
        NDIS_INFO_LOG(NDIS_TASK_PID, "Ndis_PdnV6PdnCfg,  bitOpIpv6PdnInfo is false!");
        return PS_FAIL;
    }

    ucExRabId = NDIS_FORM_EXBID(pstNasNdisInfo->enModemId, pstNasNdisInfo->ucRabId);

    if (PS_SUCC != NdSer_CheckIpv6PdnInfo(&(pstNasNdisInfo->stIpv6PdnInfo)))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnV6PdnCfg,  NdSer_CheckIpv6PdnInfo fail!");
        return PS_FAIL;
    }

    /*调ND SERVER API  配置IPV6地址信息给ND SERVER*/
    NdSer_Ipv6PdnInfoCfg(ucExRabId, &(pstNasNdisInfo->stIpv6PdnInfo));

    /*更新NDIS实体属性*/
    pstNdisEntity->ucRabType |= NDIS_ENTITY_IPV6;

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_AtCnfResultProc
 功能描述  : NDIS向AT返回的配置确认结果处理
 输入参数  :

 输出参数  : 无
 返 回 值  : 成功返回PS_SUCC;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 Ndis_AtCnfResultProc(const AT_NDIS_PDNINFO_CFG_REQ_STRU *pstNasNdisInfo, VOS_UINT32 ulV4Ret, VOS_UINT32 ulV6Ret)
{
    VOS_UINT8  enResult;

    /*根据配置结果向AT返回配置CNF原语*/
    if ((PS_TRUE == pstNasNdisInfo->bitOpIpv4PdnInfo) &&(PS_TRUE == pstNasNdisInfo->bitOpIpv6PdnInfo))
    {
        if ((PS_SUCC == ulV4Ret) &&(PS_SUCC == ulV6Ret))        /*IPV4和IPV6配置都成功*/
        {
            enResult = AT_NDIS_PDNCFG_CNF_SUCC;
        }
        else if (PS_SUCC == ulV4Ret)                             /*只有IPV4配置成功*/
        {
            enResult = AT_NDIS_PDNCFG_CNF_IPV4ONLY_SUCC;
        }
        else                                                     /*只有IPV6配置成功*/
        {
            enResult = AT_NDIS_PDNCFG_CNF_IPV6ONLY_SUCC;
        }
    }
    else if (PS_TRUE == pstNasNdisInfo->bitOpIpv4PdnInfo)  /*只配置了IPV4*/
    {
        enResult = AT_NDIS_PDNCFG_CNF_IPV4ONLY_SUCC;
    }
    else                                                   /*只配置了IPV6*/
    {
        enResult = AT_NDIS_PDNCFG_CNF_IPV6ONLY_SUCC;
    }

    return enResult;
}
/*****************************************************************************
 函 数 名  : Ndis_PdnInfoCfgProc
 功能描述  : PDN地址信息参数配置
 输入参数  :

 输出参数  : 无
 返 回 值  : 成功返回PS_SUCC;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月31日
    作    者   : h00159435
    修改内容   : 新生成函数

  2.日    期   : 2013年1月15日
    作    者   : h00218138
    修改内容   : DSDA特性，主要增加对接口消息中ModemId的处理

*****************************************************************************/
VOS_VOID Ndis_PdnInfoCfgProc(const AT_FW_CMD_BINARY_MSG_STRU *pstAtReq)
{
    VOS_UINT8                       ucExRabId;
    UDI_HANDLE                      ulHandle;
    NDIS_ENTITY_STRU               *pstNdisEntity;
    AT_NDIS_PDNINFO_CFG_CNF_STRU    stCfgCnf;
    VOS_UINT32                      ulV4Ret;
    VOS_UINT32                      ulV6Ret;
    VOS_INT32                       lSpePort;
    VOS_UINT32                      ulSpeIpfFlag;
    /*lint -e826*/
    AT_NDIS_PDNINFO_CFG_REQ_STRU   *pstNasNdisInfo = (AT_NDIS_PDNINFO_CFG_REQ_STRU *)pstAtReq->pMsg;
    /*lint +e826*/

    NDIS_INFO_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc entered!");

    /*生成扩展的RabId*/
    ucExRabId  = NDIS_FORM_EXBID(pstNasNdisInfo->enModemId, pstNasNdisInfo->ucRabId);
    ulHandle = pstNasNdisInfo->ulHandle;
    lSpePort = pstNasNdisInfo->lSpePort;
    ulSpeIpfFlag = pstNasNdisInfo->ulIpfFlag;

    stCfgCnf.enResult  = AT_NDIS_PDNCFG_CNF_FAIL;
    stCfgCnf.ucRabId   = pstNasNdisInfo->ucRabId;
    stCfgCnf.enModemId = pstNasNdisInfo->enModemId;

    /*ExRabId参数范围有效性检查。若检查失败，则直接向AT回复配置失败*/
    if (PS_SUCC != Ndis_ChkRabIdValid(ucExRabId))
    {
        (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stCfgCnf,sizeof(AT_NDIS_PDNINFO_CFG_CNF_STRU),ID_AT_NDIS_PDNINFO_CFG_CNF);
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc,  Ndis_ChkRabIdValid fail!");
        return;
    }

    /*如果根据ExRabId查找不到NDIS实体，则分配一个空闲的NDIS实体*/
    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        /*如果分配不到空闲的NDIS实体，则返回*/
        pstNdisEntity = NDIS_AllocEntity();
        if(VOS_NULL_PTR == pstNdisEntity)
        {
            /*向AT回复PDN配置失败*/
            (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stCfgCnf,sizeof(AT_NDIS_PDNINFO_CFG_CNF_STRU),ID_AT_NDIS_PDNINFO_CFG_CNF);
            NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc,  NDIS_AllocEntity failed!");
            return;
        }

        /*该承载之前没有对应的NDIS实体，故填无效值*/
        pstNdisEntity->ucRabType= NDIS_RAB_NULL;
        pstNdisEntity->ulHandle = NDIS_INVALID_HANDLE;
        pstNdisEntity->lSpePort = NDIS_INVALID_SPEPORT;
        pstNdisEntity->ulSpeIpfFlag= PS_FALSE;
    }

    ulV4Ret = Ndis_PdnV4PdnCfg(pstNasNdisInfo,pstNdisEntity);
    ulV6Ret = Ndis_PdnV6PdnCfg(pstNasNdisInfo,pstNdisEntity);

    if ((PS_FAIL == ulV6Ret) && (PS_FAIL == ulV4Ret))   /*如果IPV4和IPV6配置指示信息都无效，也认为配置失败*/
    {
        /*向AT回复PDN配置失败*/
        (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stCfgCnf,sizeof(AT_NDIS_PDNINFO_CFG_CNF_STRU),ID_AT_NDIS_PDNINFO_CFG_CNF);
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc,  Ipv4 and Ipv6 Cfg all fail!");
        return;
    }

    pstNdisEntity->enUsed = PS_TRUE;      /*设置该NDIS实体为使用状态*/
    pstNdisEntity->ucRabId  = ucExRabId;  /*将扩展RabId存到对应NDIS实体中*/
    pstNdisEntity->ulHandle = ulHandle;   /*保存Handle到NDIS实体中*/
    pstNdisEntity->lSpePort = lSpePort;   /*保存SPE Port到NDIS实体中*/
    pstNdisEntity->ulSpeIpfFlag = ulSpeIpfFlag;

    stCfgCnf.enResult  = Ndis_AtCnfResultProc(pstNasNdisInfo, ulV4Ret, ulV6Ret);
    stCfgCnf.ucRabType = pstNdisEntity->ucRabType;

    /*启动周期发送ARP的定时器*/
    if (PS_SUCC != Ndis_StartARPTimer(pstNdisEntity))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_ConfigArpInfo StartTmr Failed!");
        return;
    }

    #if (defined(CONFIG_BALONG_SPE))
    if (PS_TRUE == pstNdisEntity->ulSpeIpfFlag)
    {
        if (VOS_OK != NDIS_SPE_WPORT_IOCTL(pstNdisEntity->lSpePort, SPE_WPORT_IOCTL_SET_MAC, (VOS_VOID *)&g_stSpeMacHeader))
        {
             NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc, Set MAC header fail!");
             return;
        }
    }

    /*向底软注册上行数据接收回调*/
    if (VOS_OK != NDIS_SPE_WPORT_IOCTL (pstNdisEntity->lSpePort, SPE_WPORT_IOCTL_SET_RX_CB, AppNdis_SpeReadCb))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc, regist AppNdis_SpeReadCb fail!");
        return;
    }
    #else
    pstNdisEntity->lSpePort = NDIS_INVALID_SPEPORT;
    #endif
    /*向ADS注册下行回调:只注册一次*/
    if (VOS_OK != (ADS_DL_RegDlDataCallback(ucExRabId, Ndis_DlAdsDataRcv, 0)))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc, ADS_DL_RegDlDataCallback fail!");
        return;
    }

    /*lint -e718*/
    if (VOS_OK != NDIS_UDI_IOCTL (pstNdisEntity->ulHandle, NCM_IOCTL_REG_UPLINK_RX_FUNC, AppNdis_UsbReadCb))
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnInfoCfgProc, regist AppNdis_UsbReadCb fail!");
        return;
    }
    /*lint +e718*/

    (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stCfgCnf,sizeof(AT_NDIS_PDNINFO_CFG_CNF_STRU),ID_AT_NDIS_PDNINFO_CFG_CNF);

    return;
}

/*****************************************************************************
 函 数 名  : Ndis_PdnRel
 功能描述  : PDN释放
 输入参数  :

 输出参数  : 无
 返 回 值  : 成功返回PS_SUCC;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : h00159435
    修改内容   : 用户面融合修改

  1.日    期   : 2013年1月15日
    作    者   : h00218138
    修改内容   : DSDA特性开发:

*****************************************************************************/
VOS_VOID Ndis_PdnRel(const AT_FW_CMD_BINARY_MSG_STRU *pstAtReq)
{
    VOS_UINT8                      ucExRabId;
    NDIS_ENTITY_STRU              *pstNdisEntity;
    NDIS_ARP_PERIOD_TIMER_STRU    *pstArpPeriodTimer;
    /*lint -e826*/
    AT_NDIS_PDNINFO_REL_REQ_STRU  *pstNasNdisRel = (AT_NDIS_PDNINFO_REL_REQ_STRU  *)pstAtReq->pMsg;
    /*lint +e826*/
    AT_NDIS_PDNINFO_REL_CNF_STRU   stRelCnf;

    NDIS_INFO_LOG(NDIS_TASK_PID, "Ndis_PdnRel entered!");

    stRelCnf.enResult  = AT_NDIS_FAIL;
    stRelCnf.ucRabId   = pstNasNdisRel->ucRabId;
    stRelCnf.enModemId = pstNasNdisRel->enModemId;

    ucExRabId = NDIS_FORM_EXBID(pstNasNdisRel->enModemId, pstNasNdisRel->ucRabId);
    if (PS_FAIL == Ndis_ChkRabIdValid(ucExRabId))
    {
        (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stRelCnf,sizeof(AT_NDIS_PDNINFO_REL_CNF_STRU),ID_AT_NDIS_PDNINFO_REL_CNF);
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnRel,  Ndis_ChkRabIdValid fail!");
        return;
    }

    pstNdisEntity = NDIS_GetEntityByRabId(ucExRabId);
    if(VOS_NULL_PTR == pstNdisEntity)
    {
        (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stRelCnf,sizeof(AT_NDIS_PDNINFO_REL_CNF_STRU),ID_AT_NDIS_PDNINFO_REL_CNF);
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_PdnRel,  NDIS_GetEntityByRabId failed!");
        return;
    }

    pstArpPeriodTimer = &(pstNdisEntity->stIpV4Info.stArpPeriodTimer);

    stRelCnf.ucRabType = pstNdisEntity->ucRabType;

    /*如果周期性ARP定时器还在运行，则停掉*/
    Ndis_StopARPTimer(pstArpPeriodTimer);

    /*调用ND SERVER API 释放该RabId对应ND SERVER实体*/
    if (NDIS_ENTITY_IPV6 == (pstNdisEntity->ucRabType & NDIS_ENTITY_IPV6))
    {
        NdSer_Ipv6PdnRel(ucExRabId);
    }

    /*更新该RabId对应NDIS实体为空*/
    pstNdisEntity->ucRabType = NDIS_RAB_NULL;
    pstNdisEntity->ucRabId   = NDIS_INVALID_RABID;
    pstNdisEntity->ulHandle  = NDIS_INVALID_HANDLE;
    pstNdisEntity->enUsed    = PS_FALSE;
    pstNdisEntity->lSpePort = NDIS_INVALID_SPEPORT;
    pstNdisEntity->ulSpeIpfFlag = PS_FALSE;

    /*NDIS向AT回复释放确认原语*/
    stRelCnf.enResult  = AT_NDIS_SUCC;
    (VOS_VOID)Ndis_SndMsgToAt((VOS_UINT8*)&stRelCnf,sizeof(AT_NDIS_PDNINFO_REL_CNF_STRU),ID_AT_NDIS_PDNINFO_REL_CNF);

    return;
}

/*NDIS ARP PROC Begin*/
/*****************************************************************************
 函 数 名  : Ndis_SendRequestArp
 功能描述  : 发送ARP Request 帧到Ethenet上
 输入参数  :

 输出参数  : 无
 返 回 值  : 成功返回PS_SUCC;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月31日
    作    者   : y00151394
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  Ndis_SendRequestArp(NDIS_IPV4_INFO_STRU  *pstArpInfoItem, VOS_UINT8 ucExRabId)
{
    ETH_ARP_FRAME_STRU  stArpReq;

    /*之前一次发送的Req尚未受到Reply反馈*/
    if (PS_FALSE == pstArpInfoItem->ulArpRepFlg)
    {
        NDIS_STAT_ARPREPLY_NOTRECV(1);
        /*做一次告警日志*/
    }

    PS_MEM_SET((VOS_UINT8*)&stArpReq, 0, sizeof(ETH_ARP_FRAME_STRU));

    /*组ARP Request*/
    PS_MEM_CPY(stArpReq.aucDstAddr,g_aucBroadCastAddr,ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(stArpReq.aucSrcAddr,pstArpInfoItem->aucMacFrmHdr+ETH_MAC_ADDR_LEN, ETH_MAC_ADDR_LEN);
    stArpReq.usFrameType = ARP_PAYLOAD;

    /*请求的固定部分*/
    PS_MEM_CPY(((VOS_UINT8*)&stArpReq + ETH_MAC_HEADER_LEN),g_aucArpReqFixVal, ETH_ARP_FIXED_MSG_LEN);

    /*Payload部分的MAC地址设置*/
    PS_MEM_SET(stArpReq.aucTargetAddr,0,ETH_MAC_ADDR_LEN);
    PS_MEM_CPY(stArpReq.aucSenderAddr,pstArpInfoItem->aucMacFrmHdr+ETH_MAC_ADDR_LEN,ETH_MAC_ADDR_LEN);

    /*单板IP*/
    stArpReq.unSenderIP.ulIpAddr = pstArpInfoItem->unGwIpInfo.ulIpAddr;
    stArpReq.unTargetIP.ulIpAddr = pstArpInfoItem->unUeIpInfo.ulIpAddr;

    if (PS_SUCC != Ndis_SendMacFrm((VOS_UINT8*)&stArpReq,sizeof(ETH_ARP_FRAME_STRU),ucExRabId))
    {
        pstArpInfoItem->ulArpRepFlg = PS_TRUE;
        NDIS_STAT_DL_SEND_ARP_REQUEST_FAIL(1);
        return PS_FAIL;
    }

    NDIS_STAT_DL_SEND_ARP_REQUEST_SUCC(1);

    pstArpInfoItem->ulArpRepFlg = PS_FALSE;

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Ndis_ProcArpMsg
 功能描述  : 处理底软发送上来的ARP帧
 输入参数  :

 输出参数  : 无
 返 回 值  : 成功返回PS_SUCC;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月31日
    作    者   : y00151394
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Ndis_ProcArpMsg(ETH_ARP_FRAME_STRU* pstArpMsg, VOS_UINT8 ucRabId)
{
    /*Arp Request*/
    if(0 == VOS_MemCmp((VOS_UINT8*)pstArpMsg + ETH_MAC_HEADER_LEN,g_aucArpReqFixVal, ETH_ARP_FIXED_MSG_LEN))
    {
        NDIS_STAT_UL_RECV_ARP_REQUEST(1);
        return Ndis_ProcReqArp(pstArpMsg, ucRabId);
    }
    /*ARP Reply*/
    else if(0 == VOS_MemCmp((VOS_UINT8*)pstArpMsg + ETH_MAC_HEADER_LEN,g_aucArpRspFixVal,ETH_ARP_FIXED_MSG_LEN))
    {
        NDIS_STAT_DL_RECV_ARP_REPLY(1);
        return Ndis_ProcReplyArp(pstArpMsg, ucRabId);
    }
    else
    {
        NDIS_STAT_PROC_ARP_FAIL(1);
        return PS_FAIL;
    }
}

/*****************************************************************************
 函 数 名  : Ndis_AtMsgProc
 功能描述  :
 输入参数  : const MsgBlock *pMsgBlock
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月16日
    作    者   : h00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Ndis_AtMsgProc( const MsgBlock *pMsgBlock )
{
    /*lint -e826*/
    AT_FW_MSG_STRU                   *pstAtFw  = (AT_FW_MSG_STRU *)((VOS_VOID*)(pMsgBlock->aucValue));
    /*lint +e826*/
    AT_FW_CMD_BINARY_MSG_STRU        *pstAtMsg;
    AT_NDIS_MSG_TYPE_ENUM_UINT32      ulMsgId;

    if (ID_MSG_AT_FW_CMD_BINARY_MSG != pstAtFw->ulMsgId)
    {
        PS_PRINTF("Ndis_AtMsgProc: Fw msg type Error,ID is %x!",pstAtFw->ulMsgId);
        return;
    }
    pstAtMsg  = (AT_FW_CMD_BINARY_MSG_STRU*)(VOS_VOID*)pstAtFw->pMsgParam;
    ulMsgId  = pstAtMsg->ulMsgId;

    switch (ulMsgId)
    {
        case ID_AT_NDIS_PDNINFO_CFG_REQ :/*根据消息的不同处理AT不同的请求*/
            Ndis_PdnInfoCfgProc(pstAtMsg);
            break;

        case ID_AT_NDIS_PDNINFO_REL_REQ :
            Ndis_PdnRel(pstAtMsg);
            break;

        default:
            NDIS_WARNING_LOG(NDIS_TASK_PID, "Ndis_AtMsgProc:Error Msg!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : Ndis_AdsMsgProc
 功能描述  : NDIS接收ADS消息处理函数
 输入参数  : MsgBlock* pMsgBlock
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Ndis_AdsMsgProc(const MsgBlock* pMsgBlock )
{
    ADS_NDIS_DATA_IND_STRU  *pstAdsNdisMsg  = (ADS_NDIS_DATA_IND_STRU*)(VOS_VOID*)pMsgBlock;

    if (VOS_NULL_PTR == pstAdsNdisMsg->pstSkBuff)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_AdsMsgProc recv NULL PTR!");
        return;
    }

    if (ID_ADS_NDIS_DATA_IND != pstAdsNdisMsg->enMsgId)
    {
        /*lint -e522*/
        IMM_ZcFree(pstAdsNdisMsg->pstSkBuff);
        /*lint +e522*/
        NDIS_ERROR_LOG(NDIS_TASK_PID, "Ndis_AdsMsgProc, MsgId error!");
        return;
    }

    switch (pstAdsNdisMsg->enIpPacketType)
    {
        case ADS_NDIS_IP_PACKET_TYPE_DHCPV4:                                     /*DHCP包*/
             Ndis_DHCPPkt_Proc(pstAdsNdisMsg);
             break;
        case ADS_NDIS_IP_PACKET_TYPE_DHCPV6:                                     /*DHCPV6包*/
             NdSer_DhcpV6PktProc(pstAdsNdisMsg);
             break;
        case ADS_NDIS_IP_PACKET_TYPE_ICMPV6:                                     /*ND和ECHO REQUEST包*/
             NdSer_NdAndEchoPktProc(pstAdsNdisMsg);
             break;

        default:
             NDIS_WARNING_LOG1(NDIS_TASK_PID, "Ndis_AdsMsgProc:Other Msg!", pstAdsNdisMsg->enIpPacketType);
             break;
    }

     /*处理完成后释放ImmZc*/
     /*lint -e522*/
     IMM_ZcFree(pstAdsNdisMsg->pstSkBuff);
     /*lint +e522*/

    return;
}

/*****************************************************************************
 函 数 名  : APP_Ndis_PidMsgProc
 功能描述  : NDIS接收各模块消息处理函数
 输入参数  : MsgBlock* pMsgBlock
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月15日
    作    者   : h00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID APP_Ndis_PidMsgProc(const MsgBlock* pMsgBlock )
{
    if (VOS_NULL_PTR == pMsgBlock)
    {
        PS_PRINTF("Error:APP_Ndis_DLPidMsgProc Parameter pRcvMsg is NULL!");
        return ;
    }

    switch (pMsgBlock->ulSenderPid)
    {
        case DOPRA_PID_TIMER:
            /*lint -e826*/
            Ndis_ProcTmrMsg((REL_TIMER_MSG *)pMsgBlock);
            /*lint +e826*/
            break;

        case APP_AT_PID:
            Ndis_AtMsgProc(pMsgBlock);
            break;

        case ACPU_PID_ADS_UL:          /*ADS通过OSA消息发送DHCP和ND SERVER包给NDIS模块*/
            Ndis_AdsMsgProc(pMsgBlock);
            break;

        default:
            NDIS_WARNING_LOG(NDIS_TASK_PID,"Warning:APP_Ndis_PidMsgProc Recv not expected msg!");
            break;
    }

    return ;
}

/*lint -e40*/
/*****************************************************************************
 函 数 名  : APP_NDIS_FidInit
 功能描述  : NDIS的FID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年9月17日
    作    者   : d00130305
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 APP_NDIS_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32  ulResult = PS_FAIL;

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:

            /*注册NDIS PID*/
            ulResult = VOS_RegisterPIDInfo(NDIS_TASK_PID,
                                           (Init_Fun_Type)APP_Ndis_Pid_InitFunc,
                                           (Msg_Fun_Type)APP_Ndis_PidMsgProc);
            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register NDIS PID fail!\n");
                return VOS_ERR;
            }

            /*注册PPP PID*/
            ulResult = VOS_RegisterPIDInfo(PS_PID_APP_PPP,
                                (Init_Fun_Type)PppInit,
                                (Msg_Fun_Type)PppMsgProc);
            
            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register PPP PID fail!\n");
                return VOS_ERR;
            }

            
            /*注册ND SERVER PID*/
            ulResult = VOS_RegisterPIDInfo(NDIS_NDSERVER_PID,
                                                       (Init_Fun_Type)APP_NdServer_Pid_InitFunc,
                                                       (Msg_Fun_Type)APP_NdServer_PidMsgProc);
            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register NDSERVER PID fail!\n");
                return VOS_ERR;
            }

            /*注册DIPC PID*/
            ulResult = VOS_RegisterPIDInfo(PS_PID_APP_DIPC,
                        (Init_Fun_Type)DIPC_Pid_InitFunc,
                        (Msg_Fun_Type)DIPC_AtMsgProc);

            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register DIPC PID fail!\n");
                return VOS_ERR;
            }

            /*注册MUX PID*/
            ulResult = VOS_RegisterPIDInfo(PS_PID_APP_MUX,
                        (Init_Fun_Type)MUX_Pid_InitFunc,
                        (Msg_Fun_Type)MUX_AtMsgProc);

            if (VOS_OK != ulResult)
            {
                PS_PRINTF("APP_NDIS_FidInit, register MUX PID fail!\n");
                return VOS_ERR;
            }

            ulResult = VOS_RegisterMsgTaskPrio(NDIS_TASK_FID, VOS_PRIORITY_P4);
            if( VOS_OK != ulResult )
            {
                PS_PRINTF("APP_NDIS_FidInit, register priority fail!\n");
                return VOS_ERR;
            }
            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return PS_SUCC;
}
/*lint +e40*/

#if (FEATURE_ON ==FEATURE_LTE)
/*****************************************************************************
 Function Name  : Ndis_MsgHook
 Discription    :
 Input          : None
 Output         : None
 Return         : None

 History:
      1. z0103912   2010-05-20  初稿

*****************************************************************************/
VOS_UINT32 Ndis_MsgHook (VOS_UINT8 *pucData,VOS_UINT32 ulLength,
     AT_NDIS_MSG_TYPE_ENUM_UINT32 enMsgId)
{
/* OM融合二阶段,HOOK接口变更，入参为标准OSA消息 */

    DIAG_TraceReport((VOS_VOID *)pucData);
    return VOS_OK;

}
#endif
VOS_UINT32 g_ulGUNdisOMSwitch = PS_FALSE;
VOS_VOID GU_NDIS_OM_SWITCH_ON(VOS_VOID)
{
    g_ulGUNdisOMSwitch = PS_TRUE;
    return;
}

VOS_VOID GU_NDIS_OM_SWITCH_OFF(VOS_VOID)
{
    g_ulGUNdisOMSwitch = PS_FALSE;
    return;
}

/*======================================统计信息==============================*/
/*****************************************************************************
 函 数 名  : Ndis_ShowAppDataInfo
 功能描述  : 显示收发的业务数据信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年6月16日
    作    者   : 韩磊 00133115
    修改内容   : 新生成函数
修改历史      :
  2.日    期   : 2013年1月22日
    作    者   : h00218138
    修改内容   : DSDA

*****************************************************************************/
VOS_VOID Ndis_ShowStat(VOS_VOID)
{
    PS_PRINTF("上行丢弃的数据包个数:                %d\n", g_stNdisStatStru.ulDicardUsbFrmNum);
    PS_PRINTF("上行成功收到USB的包个数:             %d\n", g_stNdisStatStru.ulRecvUsbPktSuccNum);
    PS_PRINTF("上行发送到ADS成功的包个数:           %d\n", g_stNdisStatStru.ulSendPktToAdsSucNum);
    PS_PRINTF("下行丢弃的ADS业务数据包个数:         %d\n", g_stNdisStatStru.ulDicardAdsPktNum);
    PS_PRINTF("下行成功收到ADS业务数据包个数:       %d\n", g_stNdisStatStru.ulRecvAdsPktSuccNum);
    PS_PRINTF("下行获取IPV6 MAC帧头失败个数:        %d\n", g_stNdisStatStru.ulGetIpv6MacFailNum);
    PS_PRINTF("下行数据包类型和承载类型不一致个数:  %d\n", g_stNdisStatStru.ulDlPktDiffRabNum);
    PS_PRINTF("下行添加MAC头失败个数:               %d\n", g_stNdisStatStru.ulAddMacHdrFailNum);
    PS_PRINTF("下行发送业务数据包失败个数:          %d\n", g_stNdisStatStru.ulDlSendPktFailNum);
    PS_PRINTF("下行发送业务数据包成功个数:          %d\n", g_stNdisStatStru.ulDlSendPktSuccNum);

    PS_PRINTF("\n收到DHCP包个数:                      %d\n", g_stNdisStatStru.ulRecvDhcpPktNum);
    PS_PRINTF("收到ARP Request包个数:               %d\n", g_stNdisStatStru.ulRecvArpReq);
    PS_PRINTF("收到ARP Reply  包个数:               %d\n", g_stNdisStatStru.ulRecvArpReply);
    PS_PRINTF("处理错误 ARP   包个数:               %d\n", g_stNdisStatStru.ulProcArpError);
    PS_PRINTF("发送ARP Request包成功个数:           %d\n", g_stNdisStatStru.ulSendArpReqSucc);
    PS_PRINTF("发送ARP Request包失败个数:           %d\n", g_stNdisStatStru.ulSendArpReqFail);
    PS_PRINTF("发送ARP Req未收到ARP Reply个数:      %d\n", g_stNdisStatStru.ulArpReplyNotRecv);
    PS_PRINTF("发送ARP Reply包 个数:                %d\n", g_stNdisStatStru.ulSendArpReply);
    PS_PRINTF("发送ARP或DHCP或ND包失败个数:         %d\n", g_stNdisStatStru.ulSendArpDhcpNDFailNum);

    return;
}

/*****************************************************************************
 函 数 名  : Ndis_PrintIpAddr
 功能描述  : 打印IP地址信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年6月16日
    作    者   : 韩磊 00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Ndis_PrintIpv4Addr(const VOS_UINT8 *pIpaddr)
{
    if ((pIpaddr[0] == 0) && (pIpaddr[1] == 0) && (pIpaddr[2] == 0) && (pIpaddr[3] == 0) )
    {
         PS_PRINTF("                      地址未配置  %d\n");
         return;
    }

    PS_PRINTF("                      IPV4地址被配置为: %d.%d.%d.%d\n",(VOS_UINT32)pIpaddr[0],
                        (VOS_UINT32)pIpaddr[1],(VOS_UINT32)pIpaddr[2],(VOS_UINT32)pIpaddr[3]);

    return;
}

/*****************************************************************************
 函 数 名  : Ndis_ShowValidEntity
 功能描述  : 显示有效的实体信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月16日
    作    者   : 韩磊 00133115
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Ndis_ShowValidEntity(VOS_UINT16 usModemId, VOS_UINT8 ucRabId)
{
    NDIS_ENTITY_STRU     *pstEntity;
    VOS_UINT8            ucExRabId;

    ucExRabId = NDIS_FORM_EXBID(usModemId, ucRabId);
    pstEntity  =  NDIS_GetEntityByRabId(ucExRabId);
    if(VOS_NULL_PTR == pstEntity)
    {
        PS_PRINTF("             没有对应的NDIS实体    \n");
        return;
    }

    PS_PRINTF("                 ModemID:  %d\n", NDIS_GET_MODEMID_FROM_EXBID(pstEntity->ucRabId));
    PS_PRINTF("                 EPS承载ID:  %d\n", NDIS_GET_BID_FROM_EXBID(pstEntity->ucRabId));
    PS_PRINTF("             ARP已获得标志:  %d\n", pstEntity->stIpV4Info.ulArpInitFlg);
    PS_PRINTF(" ARP请求发送后收到回复标志:  %d\n", pstEntity->stIpV4Info.ulArpRepFlg);

    PS_PRINTF("             PDN地址配置为:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unUeIpInfo.aucIPAddr);

    PS_PRINTF("             网关地址配置为:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unGwIpInfo.aucIPAddr);

    PS_PRINTF("             子网地址配置为:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unNmIpInfo.aucIPAddr);

    PS_PRINTF("            主DNS地址配置为:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unPrimDnsAddr.aucIPAddr);

    PS_PRINTF("            辅DNS地址配置为:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unSecDnsAddr.aucIPAddr);

    PS_PRINTF("            主WINS地址配置为:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unPrimWinsAddr.aucIPAddr);

    PS_PRINTF("            辅WINS地址配置为:    \n");
    Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unSecWinsAddr.aucIPAddr);

    PS_PRINTF("              DHCP分配标志位:  %d\n",pstEntity->stIpV4Info.ulIpAssignStatus);

    PS_PRINTF("               PC侧MAC地址为:  %x-%x-%x-%x-%x-%x\n",pstEntity->stIpV4Info.aucUeMacAddr[0],
               pstEntity->stIpV4Info.aucUeMacAddr[1],pstEntity->stIpV4Info.aucUeMacAddr[2],
               pstEntity->stIpV4Info.aucUeMacAddr[3],pstEntity->stIpV4Info.aucUeMacAddr[4],
               pstEntity->stIpV4Info.aucUeMacAddr[5]);
    PS_PRINTF("          下行包以太网帧头为:  目的MAC: %x-%x-%x-%x-%x-%x,源MAC: %x-%x-%x-%x-%x-%x,帧类型:0x%x\n",
               pstEntity->stIpV4Info.aucMacFrmHdr[0],pstEntity->stIpV4Info.aucMacFrmHdr[1],
               pstEntity->stIpV4Info.aucMacFrmHdr[2],pstEntity->stIpV4Info.aucMacFrmHdr[3],
               pstEntity->stIpV4Info.aucMacFrmHdr[4],pstEntity->stIpV4Info.aucMacFrmHdr[5],
               pstEntity->stIpV4Info.aucMacFrmHdr[6],pstEntity->stIpV4Info.aucMacFrmHdr[7],
               pstEntity->stIpV4Info.aucMacFrmHdr[8],pstEntity->stIpV4Info.aucMacFrmHdr[9],
               pstEntity->stIpV4Info.aucMacFrmHdr[10],pstEntity->stIpV4Info.aucMacFrmHdr[11],
               *(VOS_UINT16 *)(&pstEntity->stIpV4Info.aucMacFrmHdr[12]));

    PS_PRINTF("\n======================================================\n");

}

/*****************************************************************************
 函 数 名  : Ndis_ShowAllEntity
 功能描述  : 显示所有的实体信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月18日
    作    者   : h00133115
    修改内容   : 新生成函数

  2.日    期   : 2013年1月16日
    作    者   : h00218138
    修改内容   : DSDA

*****************************************************************************/
VOS_VOID Ndis_ShowAllEntity(VOS_VOID)
{
    VOS_UINT32            ulLoop;
    NDIS_ENTITY_STRU     *pstEntity;

    for(ulLoop=0; ulLoop<NAS_NDIS_MAX_ITEM; ulLoop++)
    {
        pstEntity  =  &g_pstNdisEntity[ulLoop];
        if (PS_FALSE == pstEntity->enUsed)
        {
            PS_PRINTF("                 ModemID:  %d\n", NDIS_GET_MODEMID_FROM_EXBID(pstEntity->ucRabId));
            PS_PRINTF("                 EPS承载ID %d 未激活\n", NDIS_GET_BID_FROM_EXBID(pstEntity->ucRabId));
            continue;
        }

        PS_PRINTF("                 ModemID:  %d\n", NDIS_GET_MODEMID_FROM_EXBID(pstEntity->ucRabId));
        PS_PRINTF("                 EPS承载ID:  %d\n", NDIS_GET_BID_FROM_EXBID(pstEntity->ucRabId));
        PS_PRINTF("             ARP已获得标志:  %d\n", pstEntity->stIpV4Info.ulArpInitFlg);
        PS_PRINTF(" ARP请求发送后收到回复标志:  %d\n", pstEntity->stIpV4Info.ulArpRepFlg);

        PS_PRINTF("             PDN地址配置为:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unUeIpInfo.aucIPAddr);

        PS_PRINTF("             网关地址配置为:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unGwIpInfo.aucIPAddr);

        PS_PRINTF("             子网地址配置为:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unNmIpInfo.aucIPAddr);

        PS_PRINTF("            主DNS地址配置为:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unPrimDnsAddr.aucIPAddr);

        PS_PRINTF("            辅DNS地址配置为:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unSecDnsAddr.aucIPAddr);

        PS_PRINTF("            主WINS地址配置为:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unPrimWinsAddr.aucIPAddr);

        PS_PRINTF("            辅WINS地址配置为:    \n");
        Ndis_PrintIpv4Addr(pstEntity->stIpV4Info.unSecWinsAddr.aucIPAddr);

        PS_PRINTF("              DHCP分配标志位:  %d\n",pstEntity->stIpV4Info.ulIpAssignStatus);

        PS_PRINTF("               PC侧MAC地址为:  %x-%x-%x-%x-%x-%x\n",pstEntity->stIpV4Info.aucUeMacAddr[0],
                   pstEntity->stIpV4Info.aucUeMacAddr[1],pstEntity->stIpV4Info.aucUeMacAddr[2],
                   pstEntity->stIpV4Info.aucUeMacAddr[3],pstEntity->stIpV4Info.aucUeMacAddr[4],
                   pstEntity->stIpV4Info.aucUeMacAddr[5]);
        PS_PRINTF("          下行包以太网帧头为:  目的MAC: %x-%x-%x-%x-%x-%x,源MAC: %x-%x-%x-%x-%x-%x,帧类型:0x%x\n",
                   pstEntity->stIpV4Info.aucMacFrmHdr[0],pstEntity->stIpV4Info.aucMacFrmHdr[1],
                   pstEntity->stIpV4Info.aucMacFrmHdr[2],pstEntity->stIpV4Info.aucMacFrmHdr[3],
                   pstEntity->stIpV4Info.aucMacFrmHdr[4],pstEntity->stIpV4Info.aucMacFrmHdr[5],
                   pstEntity->stIpV4Info.aucMacFrmHdr[6],pstEntity->stIpV4Info.aucMacFrmHdr[7],
                   pstEntity->stIpV4Info.aucMacFrmHdr[8],pstEntity->stIpV4Info.aucMacFrmHdr[9],
                   pstEntity->stIpV4Info.aucMacFrmHdr[10],pstEntity->stIpV4Info.aucMacFrmHdr[11],
                   *(VOS_UINT16 *)(&pstEntity->stIpV4Info.aucMacFrmHdr[12]));

        PS_PRINTF("\n======================================================\n");
    }
}




/*****************************************************************************
 Function Name  : lpsver
 Discription    : 查询版本信息
 Input          : None
 Output         : None
 Return         : None

 History:
      1. Lishangfeng 55206   2010-05-20  初稿

*****************************************************************************/
/*VOS_VOID lpsver (VOS_VOID)
{
    PS_PRINTF("************^U^*************\r\n");
    PS_PRINTF("Version :APP PS V%dR%03dC%02dB%03d\r\n", 700,
                                                          1,
                                                          10,
                                                          60
                                    );
    PS_PRINTF("Date    : %s \r\n", (VOS_UINT8 *)__DATE__);
    PS_PRINTF("Time    : %s \r\n", (VOS_UINT8 *)__TIME__);
    PS_PRINTF("************^U^*************\r\n");
}*/

/*****************************************************************************
 Function Name  : NDIS_OpenLatency
 Discription    : UserPlane Latency
 Input          : None
 Output         : None
 Return         : None

 History:
      1. huibo 00159435   2012-06-18  初稿
*****************************************************************************/
VOS_VOID NDIS_OpenLatency(VOS_VOID)
{
    g_ulNdisLomSwitch = 1;
    return;
}

/*****************************************************************************
 Function Name  : NDIS_CloseLatency
 Discription    : UserPlane Latency
 Input          : None
 Output         : None
 Return         : None

 History:
      1. huibo 00159435   2012-06-18  初稿
*****************************************************************************/
VOS_VOID NDIS_CloseLatency(VOS_VOID)
{
    g_ulNdisLomSwitch = 0;
    return;
}

/*****************************************************************************
 Function Name  : Ndis_LomTraceRcvUlData
 Discription    : UserPlane Latency
 Input          : None
 Output         : None
 Return         : None

 History:
      1. huibo 00159435   2012-06-18  初稿
*****************************************************************************/
VOS_VOID Ndis_LomTraceRcvUlData(VOS_VOID)
{
    if (1 == g_ulNdisLomSwitch)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "User plane latency trace: NDIS rcv UL data");
    }
    return;
}

/*****************************************************************************
 Function Name  : Ndis_LomTraceRcvDlData
 Discription    : UserPlane Latency
 Input          : None
 Output         : None
 Return         : None

 History:
      1. huibo 00159435   2012-06-18  初稿
*****************************************************************************/
VOS_VOID Ndis_LomTraceRcvDlData(VOS_VOID)
{
    if (1 == g_ulNdisLomSwitch)
    {
        NDIS_ERROR_LOG(NDIS_TASK_PID, "User plane latency trace: NDIS rcv DL data");
    }
    return;
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

