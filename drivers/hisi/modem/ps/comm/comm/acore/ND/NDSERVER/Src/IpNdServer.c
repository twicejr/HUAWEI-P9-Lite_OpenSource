

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "IpNdServer.h"
#include "AdsDeviceInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IPNDSERVER_C
/*lint +e767*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/* ND SERVER数据信息 */
IP_NDSERVER_ADDR_INFO_STRU              g_astNdServerAddrInfo[IP_NDSERVER_ADDRINFO_MAX_NUM];
IP_NDSERVER_TE_DETECT_BUF_STRU          g_astNdServerTeDetectBuf;

/* ND SERVER本地保存的配置参数 */
VOS_UINT8                               g_ucMFlag;            /* M标识 */
VOS_UINT8                               g_ucOFlag;            /* O标识 */
VOS_UINT16                              g_usRouterLifetime;   /* Router Lifetime */
VOS_UINT32                              g_ulReachableTime;    /* Reachable Time */
VOS_UINT32                              g_ulRetransTimer;     /* Retrans Timer */

VOS_UINT32                              g_ulNsTimerLen;         /* 非周期性NS定时器时长 */
VOS_UINT32                              g_ulNsTimerMaxExpNum;   /* 非周期性NS最大超时次数 */
VOS_UINT32                              g_ulPeriodicNsTimerLen; /* 周期性NS定时器时长 */
VOS_UINT32                              g_ulPeriodicRaTimerLen; /* 周期性RA定时器时长，防止Router过期 */
VOS_UINT32                              g_ulFirstNsTimerLen;    /* 收到重复地址检测后等待的定时器时长 */
VOS_UINT32                              g_ulRaTimerLen;         /* 收到重复地址检测前周期发送RA定时器时长 */

/* 周期性发送RA时间计数器 */
VOS_UINT32                              g_aulPeriodicRaTimeCnt[IP_NDSERVER_ADDRINFO_MAX_NUM];

/* 用于存储解析后的ND报文数据 */
IP_ND_MSG_STRU                          g_stNdMsgData;

/* ND SERVER使用的发包缓冲区 */
VOS_UINT8                               g_aucSendMsgBuffer[IP_IPM_MTU];

/* ND SERVER报文统计信息 */
IP_NDSERVER_PACKET_STATISTICS_INFO_STRU g_astNdServerPktStatInfo[IP_NDSERVER_ADDRINFO_MAX_NUM];

VOS_UINT8 g_aucInvalidIpv6Addr[IP_IPV6_ADDR_LEN] = {0};

extern VOS_UINT32 g_ulNvMtu;

/*****************************************************************************
  3 Function
*****************************************************************************/
extern VOS_UINT8* Ndis_GetMacAddr( VOS_VOID );
extern VOS_UINT32 Ndis_SendMacFrm(const VOS_UINT8  *pucBuf, VOS_UINT32 ulLen, VOS_UINT8 ucRabId);
extern VOS_UINT32 Ndis_DlSendNcm(VOS_UINT8 ucRabId, ADS_PKT_TYPE_ENUM_UINT8 ucPktType, IMM_ZC_STRU *pstImmZc);

/*****************************************************************************
 函 数 名  : IP_NDSERVER_SaveTeDetectIp
 功能描述  : 临时保存Te IP地址，在TE不发重复地址检测的情况下用来获取TE MAC地
             址
 输入参数  : VOS_UINT8* pucTeGlobalAddr
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月17日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IP_NDSERVER_SaveTeDetectIp( const VOS_UINT8* pucTeGlobalAddr )
{
    VOS_UINT32  ulIndex = g_astNdServerTeDetectBuf.ulHead;

    if ((IP_IPV6_IS_LINKLOCAL_ADDR(pucTeGlobalAddr))
            || (IP_IPV6_64BITPREFIX_EQUAL_ZERO(pucTeGlobalAddr))
            || (IP_IPV6_IS_MULTICAST_ADDR(pucTeGlobalAddr)))
    {
        /* 不是Global IP */
        return;
    }

    /* 相同Prefix的地址是否已经存在 */
    while(ulIndex != g_astNdServerTeDetectBuf.ulTail)
    {
        /*lint -e960*/
        if((IP_TRUE == g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].ulValid)
            && (0 == IP_MEM_CMP(pucTeGlobalAddr, g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].aucTeGlobalAddr, ND_IP_IPV6_PREFIX_LENGTH)))
        /*lint +e960*/
            {
            /* 相同Prefix只保留一个地址 */
            IP_MEM_CPY(g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].aucTeGlobalAddr, pucTeGlobalAddr, IP_IPV6_ADDR_LEN);
            return;
        }
        ulIndex = TTF_MOD_ADD(ulIndex, 1, g_astNdServerTeDetectBuf.ulMaxNum);
    }

    if(g_astNdServerTeDetectBuf.ulHead == TTF_MOD_ADD(g_astNdServerTeDetectBuf.ulTail, 1, g_astNdServerTeDetectBuf.ulMaxNum))
    {
        /*IP_LOG1_WARN("IP_NDSERVER_SaveTeDetectIp: OverWrite TeAddr!", g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulHead].ulValid);
 */
        /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulHead].aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */
        /* BUF满时覆盖最老的地址 */
        g_astNdServerTeDetectBuf.ulHead = TTF_MOD_ADD(g_astNdServerTeDetectBuf.ulHead, 1, g_astNdServerTeDetectBuf.ulMaxNum);
    }

    /* 保存IP地址 */
    IP_MEM_CPY(g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulTail].aucTeGlobalAddr, pucTeGlobalAddr, IP_IPV6_ADDR_LEN);
    g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulTail].ulValid = IP_TRUE;

    g_astNdServerTeDetectBuf.ulTail = TTF_MOD_ADD(g_astNdServerTeDetectBuf.ulTail, 1, g_astNdServerTeDetectBuf.ulMaxNum);
}

/*****************************************************************************
 函 数 名  : IP_NDSERVER_GetTeDetectIp
 功能描述  : 获取临时保存的TE IP地址
 输入参数  : VOS_UINT8* pucPrefixAddr
 输出参数  : 无
 返 回 值  : VOS_UINT8*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月17日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8* IP_NDSERVER_GetTeDetectIp( const VOS_UINT8* pucPrefixAddr )
{
    VOS_UINT32  ulIndex = g_astNdServerTeDetectBuf.ulHead;
    while(ulIndex != g_astNdServerTeDetectBuf.ulTail)
    {
        /*lint -e960*/
        if((IP_TRUE == g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].ulValid)
            && (0 == IP_MEM_CMP(pucPrefixAddr, g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].aucTeGlobalAddr, ND_IP_IPV6_PREFIX_LENGTH)))
        /*lint +e960*/
        {
            g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].ulValid = IP_FALSE;

            /* Buf头部空隙处理 */
            while((g_astNdServerTeDetectBuf.ulHead != g_astNdServerTeDetectBuf.ulTail) &&
                (IP_FALSE == g_astNdServerTeDetectBuf.astTeIpBuf[g_astNdServerTeDetectBuf.ulHead].ulValid))
            {
                g_astNdServerTeDetectBuf.ulHead = TTF_MOD_ADD(g_astNdServerTeDetectBuf.ulHead, 1, g_astNdServerTeDetectBuf.ulMaxNum);
            }

            return g_astNdServerTeDetectBuf.astTeIpBuf[ulIndex].aucTeGlobalAddr;
        }
        ulIndex = TTF_MOD_ADD(ulIndex, 1, g_astNdServerTeDetectBuf.ulMaxNum);
    }

    return IP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SetLocalParam
 Description     : 设置本地网络参数
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli  00180715      2011-04-01  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_SetLocalParam( VOS_VOID )
{
    /* M标识，0，主机不能通过DHCPv6获取IPv6地址 */
    g_ucMFlag = 0;

    /* O标识，1，主机可以通过无状态DHCPv6获取其他参数，例如DNS服务器，SIP服务器； */
    g_ucOFlag = 1;

    /* Router Lifetime(秒) */
    g_usRouterLifetime = 9000;

    /* Reachable Time(毫秒) */
    g_ulReachableTime = 3600000;

    /* Retrans Timer(毫秒)，0，表示未知 */
    g_ulRetransTimer = 0;

    /* 非周期性NS定时器时长(毫秒) */
    g_ulNsTimerLen = 4000;

    /* 非周期性NS最大超时次数 */
    g_ulNsTimerMaxExpNum = 3;

    /* 周期性NS定时器时长(毫秒) */
    g_ulPeriodicNsTimerLen = 60000;

    /* 周期性RA，防止Router过期(毫秒) */
    g_ulPeriodicRaTimerLen = 3600000;

    /* 收到重复地址检测后等待的定时器时长(毫秒) */
    g_ulFirstNsTimerLen = 2000;

    /* 收到重复地址检测前周期发送RA的定时器时长(毫秒) */
    g_ulRaTimerLen = 15000;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_DebugInit
 Description     : 清除统计信息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_DebugInit(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM; ulIndex++)
    {
        IP_MEM_SET( IP_NDSERVER_GET_STATINFO_ADDR(ulIndex),
                    IP_NULL,
                    sizeof(IP_NDSERVER_PACKET_STATISTICS_INFO_STRU));
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_IsTimerNameValid
 Description     : 判断定时器名是否合法
 Input           : ulIndex     --- ND SERVER数据体索引号
                   enTimerType --- 定时器类型
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-02  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_IsTimerNameValid
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    switch(enTimerType)
    {
        case IP_ND_SERVER_TIMER_NS:
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
        case IP_ND_SERVER_TIMER_FIRST_NS:
        case IP_ND_SERVER_TIMER_RA:
        {
            if (ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM)
            {
                return IP_TRUE;
            }

            break;
        }
        default:
            break;
    }

    return IP_FALSE;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_GetTimer
 Description     : 获取定时器
 Input           : enTimerType------------------定时器类型
                   ulIndex----------------------定时器索引号
 Output          : None
 Return          : IP_TIMER_STRU*

 History         :
    1.sunli 00180715      2011-04-02  Draft Enact

*****************************************************************************/
IP_TIMER_STRU*  IP_NDSERVER_GetTimer
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    IP_TIMER_STRU                      *pstTimerInfo = VOS_NULL_PTR;

    /*根据定时器不同类型，获取定时器*/
    switch( enTimerType )
    {
        case IP_ND_SERVER_TIMER_NS:
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
        case IP_ND_SERVER_TIMER_FIRST_NS:
        case IP_ND_SERVER_TIMER_RA:
            pstTimerInfo = IP_NDSERVER_ADDRINFO_GET_TIMER(ulIndex);
            break;
        default :
            break;
    }

    return pstTimerInfo;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_GetTimerLen
 Description     : 获取定时器时长
 Input           : enTimerType------------------定时器类型
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-02  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_GetTimerLen
(
    NDSER_TIMER_ENUM_UINT32              enTimerType
)
{
    VOS_UINT32                  ulTimerLen   = IP_NULL;

    /*根据定时器不同类型，定时器时长不同*/
    switch( enTimerType )
    {
        case IP_ND_SERVER_TIMER_NS:
            ulTimerLen = g_ulNsTimerLen;
            break;
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
            ulTimerLen = g_ulPeriodicNsTimerLen;
            break;
        case IP_ND_SERVER_TIMER_FIRST_NS:
            ulTimerLen = g_ulFirstNsTimerLen;
            break;
        case IP_ND_SERVER_TIMER_RA:
            ulTimerLen = g_ulRaTimerLen;
            break;
        default :
            break;
    }

    return ulTimerLen;
}
/*lint -e550*/
/*****************************************************************************
 Function Name   : IP_NDSERVER_PrintTimeStartInfo
 Description     : 打印定时器启动信息
 Input           : enTimerType------------------定时器类型
                   ulIndex----------------------定时器索引号
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2010-04-02  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_PrintTimeStartInfo
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    VOS_UINT32      ulEpsbId;

    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);
    /*根据定时器不同类型，打印相应信息*/
    switch( enTimerType )
    {
        case IP_ND_SERVER_TIMER_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStartInfo:NORM:IP TimerStart(ulIndex): IP_ND_SERVER_TIMER_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStartInfo:NORM:IP TimerStart(ulIndex): IP_ND_SERVER_TIMER_PERIODIC_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_FIRST_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStartInfo:NORM:IP TimerStart(ulIndex): IP_ND_SERVER_TIMER_FIRST_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_RA:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStartInfo:NORM:IP TimerStart(ulIndex): IP_ND_SERVER_TIMER_RA", ulIndex, ulEpsbId);
            break;
        default :
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_PrintTimeStopInfo
 Description     : 打印定时器关闭信息
 Input           : enTimerType------------------定时器类型
                   ulIndex----------------------定时器索引号
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2010-04-02  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_PrintTimeStopInfo
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    VOS_UINT32     ulEpsbId;

    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);
    /*根据定时器不同类型，打印相应信息*/
    switch(enTimerType)
    {
        case IP_ND_SERVER_TIMER_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStopInfo:NORM:IP TimerStop(ulIndex): IP_ND_SERVER_TIMER_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStopInfo:NORM:IP TimerStop(ulIndex): IP_ND_SERVER_TIMER_PERIODIC_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_FIRST_NS:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStopInfo:NORM:IP TimerStop(ulIndex): IP_ND_SERVER_TIMER_FIRST_NS", ulIndex, ulEpsbId);
            break;
        case IP_ND_SERVER_TIMER_RA:
            IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_PrintTimeStopInfo:NORM:IP TimerStop(ulIndex): IP_ND_SERVER_TIMER_RA", ulIndex, ulEpsbId);
            break;
        default :
            break;
    }

    return;
}
/*lint +e550*/
/*****************************************************************************
 Function Name  : IP_NDSERVER_TimerStart
 Discription    : 启动某一承载的某种类型的定时器
 Input          : VOS_UINT32             ulIndex
                  NDSER_TIMER_ENUM_UINT32 enTimerType
 Output         : VOS_VOID
 Return         : None
 History:
      1.sunli 00180715      2011-04-02  Draft Enact
*****************************************************************************/
VOS_VOID IP_NDSERVER_TimerStart
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    VOS_UINT32                          ulTimerLen   = IP_NULL;
    IP_TIMER_STRU                      *pstTimerInfo = VOS_NULL_PTR;

    /*对ulIndex合法性判断*/
    if (IP_FALSE == IP_NDSERVER_IsTimerNameValid(ulIndex, enTimerType))
    {
        /*打印异常信息*/
        IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart: WARN: Input Para(ulIndex) err !", ulIndex, enTimerType);
        return;
    }

    /*根据消息对应的索引号和定时器类型,获取相关联的定时器*/
    pstTimerInfo = IP_NDSERVER_GetTimer(ulIndex, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*打印异常信息*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:ERROR: Get Timer failed.");
        return;
    }

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != pstTimerInfo->hTm)
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTm)))
        {
            /*打印异常信息*/
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:WARN: stop reltimer error!");
            return;
        }

        /*打印异常信息*/
        IPND_INFO_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:(TimerType) Timer not close!",pstTimerInfo->ulName, ulIndex);
    }

    /*根据定时器不同类型，定时器信息不同*/
    ulTimerLen = IP_NDSERVER_GetTimerLen(enTimerType);
    if (ulTimerLen == IP_NULL)
    {
        /*打印异常信息*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:ERROR: start unreasonable reltimer.");
        return;
    }

    /*设定定时器NAME,enTimerType设定定时器Para，打开失败则报警返回*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimerInfo->hTm),NDIS_NDSERVER_PID,\
                                ulTimerLen,(VOS_UINT32)enTimerType,\
                                ulIndex,VOS_RELTIMER_NOLOOP))
    {
          /*打印异常信息*/
          IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStart:WARN: start reltimer error!");
          return;
    }

    /* 更新定时器类别 */
    pstTimerInfo->ulName = enTimerType;

    /* 打印定时器启动信息 */
    IP_NDSERVER_PrintTimeStartInfo(ulIndex, enTimerType);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_TimerStop
 Discription    : 停止某一承载某种类型定时器
 Input          : VOS_UINT32             ulIndex
                  NDSER_TIMER_ENUM_UINT32 enTimerType
 Output         : VOS_VOID
 Return         : None
 History:
      1.sunli 00180715      2011-04-02  Draft Enact
*****************************************************************************/
VOS_VOID IP_NDSERVER_TimerStop
(
    VOS_UINT32                          ulIndex,
    NDSER_TIMER_ENUM_UINT32             enTimerType
)
{
    IP_TIMER_STRU                      *pstTimerInfo = VOS_NULL_PTR;

    /*对ulIndex合法性判断*/
    if (IP_FALSE == IP_NDSERVER_IsTimerNameValid(ulIndex, enTimerType))
    {
        /*打印异常信息*/
        IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStop: WARN: Input Para(ulIndex) err !", ulIndex, enTimerType);
        return;
    }

    /*根据消息对应的索引号和定时器类型,获取相关联的定时器*/
    pstTimerInfo = IP_NDSERVER_GetTimer(ulIndex, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*打印异常信息*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStop:ERROR:Get Timer failed.");
        return;
    }

    /*定时器处于打开状态，则关闭，否则，忽略*/
    if(VOS_NULL_PTR != pstTimerInfo->hTm)
    {
        if(enTimerType != pstTimerInfo->ulName)
        {
            /*打印异常信息*/
            IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStop: TimerType not match:", enTimerType, pstTimerInfo->ulName);
        }
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTm)))
        {
            /*打印异常信息*/
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerStop:WARN: stop reltimer error!");
            return;
        }

        /* 清除超时计数 */
        pstTimerInfo->ucLoopTimes = 0;

        /* 打印定时器关闭信息 */
        IP_NDSERVER_PrintTimeStopInfo(ulIndex, enTimerType);
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_Init
 Description     : ND SERVER模块的初始化
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli  00180715      2011-04-01  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_Init( VOS_VOID )
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usPayLoad = IP_IPV6_PAYLOAD;
    VOS_UINT32                          ulRtn;

    IP_NDSERVER_SetLocalParam();
    IP_NDSERVER_DebugInit();

    for (ulIndex = 0; ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM; ulIndex++)
    {
        IP_MEM_SET( IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex),
                    IP_NULL,
                    sizeof(IP_NDSERVER_ADDR_INFO_STRU));

        PS_MEM_CPY( IP_NDSERVER_ADDRINFO_GET_MACADDR(ulIndex),
                   (VOS_VOID*)Ndis_GetMacAddr(),
                   IP_MAC_ADDR_LEN);

        PS_MEM_CPY((IP_NDSERVER_ADDRINFO_GET_MACFRAME(ulIndex) + IP_MAC_ADDR_LEN),
                   (VOS_VOID*)Ndis_GetMacAddr(),
                   IP_MAC_ADDR_LEN);

        PS_MEM_CPY((IP_NDSERVER_ADDRINFO_GET_MACFRAME(ulIndex) + 2*IP_MAC_ADDR_LEN),
                   (VOS_UINT8*)(&usPayLoad),
                   2);

        g_aulPeriodicRaTimeCnt[ulIndex] = g_ulPeriodicRaTimerLen / g_ulPeriodicNsTimerLen;

        /*创建下行IP包缓存队列*/
        ulRtn = LUP_CreateQue(NDIS_NDSERVER_PID, &(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex)), ND_IPV6_WAIT_ADDR_RSLT_Q_LEN);
        if (PS_SUCC != ulRtn)
        {
            vos_printf("IP_NDSERVER_Init, LUP_CreateQue DlPktQue fail.\n");
            return;
        }
    }

    IP_MEM_SET(&g_astNdServerTeDetectBuf,
                IP_NULL,
                sizeof(IP_NDSERVER_TE_DETECT_BUF_STRU));

    g_astNdServerTeDetectBuf.ulHead = 0;
    g_astNdServerTeDetectBuf.ulTail = 0;
    g_astNdServerTeDetectBuf.ulMaxNum = 2*IP_NDSERVER_ADDRINFO_MAX_NUM;

    return;
}

/*****************************************************************************
 函 数 名  : APP_NdServer_Pid_InitFunc
 功能描述  : ND SERVER PID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ePhase
 输出参数  : 无
 返 回 值  : extern VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  APP_NdServer_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ePhase)
{
    switch( ePhase )
    {
        case   VOS_IP_LOAD_CONFIG:
            IP_NDSERVER_Init();
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
    return 0;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_Stop
 Description     : 清除ND SERVER相关信息
 Input           : ulIndex --- ND SERVER结构索引号
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli  00180715      2011-04-01  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_Stop(VOS_UINT32 ulIndex)
{
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr = IP_NULL_PTR;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pstInfoAddr->ucValidFlag = IP_FALSE;

    pstInfoAddr->ucEpsbId = 0;

    IP_MEM_SET(&pstInfoAddr->stIpv6NwPara, IP_NULL, sizeof(ESM_IP_IPV6_NW_PARA_STRU));

    if (IP_NDSERVER_TE_ADDR_INEXISTENT != pstInfoAddr->stTeAddrInfo.enTeAddrState)
    {
        IP_NDSERVER_SaveTeDetectIp(pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr);
    }

    /* 清除TE地址记录 */
    IP_MEM_SET( &pstInfoAddr->stTeAddrInfo,
                IP_NULL,
                sizeof(IP_NDSERVER_TE_ADDR_INFO_STRU));

    IP_NDSERVER_TimerStop(ulIndex, pstInfoAddr->stTimerInfo.ulName);

    IP_MEM_SET(&pstInfoAddr->stIpSndNwMsg, IP_NULL, sizeof(IP_SND_MSG_STRU));

    g_aulPeriodicRaTimeCnt[ulIndex] = g_ulPeriodicRaTimerLen / g_ulPeriodicNsTimerLen;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_ClearDlPktQue
 Description     : 释放下行缓存队列中的PKT
 Input           : VOS_UINT8 ucRabId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h00159435 00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ClearDlPktQue(VOS_UINT32 ulIndex)
{
    IMM_ZC_STRU                        *pstImmZc    = VOS_NULL_PTR;
    VOS_INT32                           lLockKey;

    while(PS_TRUE != (LUP_IsQueEmpty(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex))))
    {
        lLockKey = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex), (VOS_VOID**)(&pstImmZc)))
        {
            VOS_Splx(lLockKey);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ClearDlPktQue, LUP_DeQue return fail!");
            return;
        }
        VOS_Splx(lLockKey);
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
    }

    return;
}

/*****************************************************************************
 Function Name   : NdSer_Ipv6PdnRel
 Description     : 处理NDIS发来的Ipv6PdnRel
 Input           : VOS_UINT8 ucRabId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h00159435 00159435      2011-12-09  Draft Enact
    2.h00218138 00218138      2013-1-16  DSDA

*****************************************************************************/
VOS_VOID NdSer_Ipv6PdnRel(VOS_UINT8 ucExRabId)
{
    VOS_UINT32                          ulIndex;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnRel is entered.");

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);

    if (ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        IP_NDSERVER_Stop(ulIndex);

        IP_NDSERVER_ClearDlPktQue(ulIndex);           /*释放下行PKT缓存队列*/
    }
    else
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnRel: Invalid Input:", ulIndex, ucExRabId);
    }

    return;
}

/*****************************************************************************
 Function Name   : NdSer_Ipv6PdnValid
 Description     : 供NDIS调用，查询对应承载的ND SERVER实体是否还有效
 Input           : VOS_UINT8 ucRabId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.huibo 00159435      2011-12-06  Draft Enact

*****************************************************************************/
VOS_UINT32 NdSer_Ipv6PdnValid(VOS_UINT8 ucRabId)
{
    VOS_UINT32                          ulIndex;

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucRabId);
    if(ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 Function Name   : NdSer_GetMacFrm
 Description     : 供NDIS调用，获取ND SERVER对应实体的完整MAC帧头
 Input           : VOS_UINT8 ucIndex
 Output          : None
 Return          : VOS_UINT8*

 History         :
    1.huibo 00159435      2011-12-06  Draft Enact

*****************************************************************************/
VOS_UINT8* NdSer_GetMacFrm(VOS_UINT8 ucIndex, VOS_UINT8 *enTeAddrState)
{
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ucIndex);
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "pstInfoAddr ucValidFlag is not TRUE!", ucIndex);
        return VOS_NULL_PTR;
    }

    *enTeAddrState = pstInfoAddr->stTeAddrInfo.enTeAddrState;

    return IP_NDSERVER_ADDRINFO_GET_MACFRAME(ucIndex);
}

/*****************************************************************************
 Function Name   : NdSer_MacAddrInvalidProc
 Description     : 供NDIS调用，当未获得PC MAC地址时，缓存下行IP包
 Input           : VOS_UINT8 ucIndex
 Output          : None
 Return          : VOS_UINT8*

 History         :
    1.huibo 00159435      2011-12-06  Draft Enact

*****************************************************************************/
VOS_VOID NdSer_MacAddrInvalidProc(IMM_ZC_STRU *pstImmZc, VOS_UINT8 ucIndex)
{
    IMM_ZC_STRU                        *pstQueHead;
    VOS_INT32                           lLockKey;

    IP_NDSERVER_AddMacInvalidPktNum(ucIndex);

    /***********************下行IPV6数据包缓存*********************************/
    if (PS_TRUE == LUP_IsQueFull(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ucIndex)))
    {
        lLockKey = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ucIndex), (VOS_VOID**)(&pstQueHead)))
        {
            VOS_Splx(lLockKey);
            /*lint -e522*/
            IMM_ZcFree(pstImmZc);
            /*lint +e522*/
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_MacAddrInvalidProc, LUP_DeQue return NULL");
            return;
        }
        VOS_Splx(lLockKey);
        /*lint -e522*/
        IMM_ZcFree(pstQueHead);                         /*释放最早的IP包*/
        /*lint +e522*/
    }

    lLockKey = VOS_SplIMP();
    if (PS_SUCC != LUP_EnQue(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ucIndex), pstImmZc))    /*插入最新的IP包*/
    {
        VOS_Splx(lLockKey);
        /*lint -e522*/
        IMM_ZcFree(pstImmZc);
        /*lint +e522*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_MacAddrInvalidProc, LUP_EnQue return NULL");
        return;
    }
    VOS_Splx(lLockKey);

    IP_NDSERVER_AddEnquePktNum(ucIndex);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_FindIpv6EffectivePrefix
 Description    : 查找第一个可用的IPv6前缀
 Input          : pstConfigParaInd ---- ESM_IP_NW_PARA_IND_STRU消息指针
 Output         : pulPrefixIndex   ---- 前缀索引指针
 Return Value   : VOS_UINT32

 History        :
      1.sunli 00180715     2011-04-05  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_FindIpv6EffectivePrefix
(
    AT_NDIS_IPV6_PDN_INFO_STRU            *pstConfigParaInd,
    VOS_UINT32                            *pulPrefixIndex
)
{
    VOS_UINT32                          ulIndex         = IP_NULL;
    ND_IP_IPV6_PREFIX_STRU            *pstIpv6Prefix   = IP_NULL_PTR;

    /* 遍历前缀列表，查找A标识为1，前缀长度为64的前缀 */
    for (ulIndex = IP_NULL; ulIndex < pstConfigParaInd->ulPrefixNum; ulIndex++)
    {
        pstIpv6Prefix = (ND_IP_IPV6_PREFIX_STRU*)&pstConfigParaInd->astPrefixList[ulIndex];
        if ((IP_IPV6_OP_TRUE == pstIpv6Prefix->ulBitA)
            && ((ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH)*8 == pstIpv6Prefix->ulBitPrefixLen)
            && (!IP_IPV6_64BITPREFIX_EQUAL_ZERO(pstIpv6Prefix->aucPrefix))
            && (!IP_IPV6_IS_LINKLOCAL_ADDR(pstIpv6Prefix->aucPrefix))
            && (!IP_IPV6_IS_MULTICAST_ADDR(pstIpv6Prefix->aucPrefix)))
        {
            *pulPrefixIndex = ulIndex;
            return IP_SUCC;
        }
    }

    return IP_FAIL;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_GetNwPara
 Description     : 从ID_ESM_IP_NW_PARA_IND中获取网络参数
 Input           : pstNwParaInd--------------消息指针
 Output          : pstNwParamTmp-------------网络参数指针
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-05  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_GetNwPara
(
    ESM_IP_IPV6_NW_PARA_STRU           *pstNwParamTmp,
    AT_NDIS_IPV6_PDN_INFO_STRU         *pstNwParaInd
)
{
    VOS_UINT32                          ulPrefixIndex       = IP_NULL;
    VOS_UINT32                          ulRslt              = IP_NULL;

    IP_MEM_SET(pstNwParamTmp, IP_NULL, sizeof(ESM_IP_IPV6_NW_PARA_STRU));

    /* 获取HOP LIMIT */
    pstNwParamTmp->ucCurHopLimit = pstNwParaInd->ulBitCurHopLimit;

    /* 获取MTU */
    if (IP_IPV6_OP_TRUE == pstNwParaInd->ulBitOpMtu)
    {
        pstNwParamTmp->ulBitOpMtu = pstNwParaInd->ulBitOpMtu;
        pstNwParamTmp->ulMtu = pstNwParaInd->ulMtu;
    }

    /* 获取接口标识符 */
    IP_MEM_CPY( pstNwParamTmp->aucInterfaceId,
                pstNwParaInd->aucInterfaceId,
                ND_IP_IPV6_IFID_LENGTH);

    /* 保存地址前缀列表，目前只保存和使用第一个可用的IPv6前缀 */
    ulRslt = IP_NDSERVER_FindIpv6EffectivePrefix(pstNwParaInd, &ulPrefixIndex);

    if (IP_SUCC != ulRslt)
    {
        return IP_FAIL;
    }

    IP_MEM_CPY( &pstNwParamTmp->astPrefixList[IP_NULL],
                &pstNwParaInd->astPrefixList[ulPrefixIndex],
                sizeof(ND_IP_IPV6_PREFIX_STRU));

    pstNwParamTmp->ulPrefixNum = 1;

    /* 获取DNS服务器列表 */
    IP_MEM_CPY( pstNwParamTmp->stDnsSer.aucPriDnsServer,
                pstNwParaInd->stDnsSer.aucPriServer,
                IP_IPV6_ADDR_LEN);
    IP_MEM_CPY( pstNwParamTmp->stDnsSer.aucSecDnsServer,
                pstNwParaInd->stDnsSer.aucSecServer,
                IP_IPV6_ADDR_LEN);
    pstNwParamTmp->stDnsSer.ucDnsSerNum = pstNwParaInd->stDnsSer.ucSerNum;

    /* 获取SIP服务器列表 */
    IP_MEM_CPY( pstNwParamTmp->stSipSer.aucPriSipServer,
                pstNwParaInd->stPcscfSer.aucPriServer,
                IP_IPV6_ADDR_LEN);
    IP_MEM_CPY( pstNwParamTmp->stSipSer.aucSecSipServer,
                pstNwParaInd->stPcscfSer.aucSecServer,
                IP_IPV6_ADDR_LEN);
    pstNwParamTmp->stSipSer.ucSipSerNum = pstNwParaInd->stPcscfSer.ucSerNum;

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormRaHeaderMsg
 Description     : RA报文头固定部分设置
 Input           : ulIndex --- ND SERVER实体索引
 Output          : pucData --- 报文缓冲指针
 Return          :

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormRaHeaderMsg
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucData
)
{
    ESM_IP_IPV6_NW_PARA_STRU         *pstNwPara  = IP_NULL_PTR;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    pstNwPara = IP_NDSERVER_ADDRINFO_GET_NWPARA(ulIndex);

    /* 类型 */
    *pucData = IP_ICMPV6_TYPE_RA;
    pucData++;

    /* 代码 */
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /* 跳过校验和 */
    pucData += 2;

    /* 当前跳限制 */
    *pucData = pstNwPara->ucCurHopLimit;
    pucData++;

    /* 管理地址配置标志、其他有状态配置标志 */
    *pucData = (VOS_UINT8)(((g_ucMFlag & 0x1)<<7) | ((g_ucOFlag & 0x1)<<6));
    pucData++;

    /* 路由生存期 */
    IP_SetUint16Data(pucData, g_usRouterLifetime);
    pucData += 2;

    /* 可达时间 */
    IP_SetUint32Data(pucData, g_ulReachableTime);
    pucData += 4;

    /* 重发定时器 */
    IP_SetUint32Data(pucData, g_ulRetransTimer);
    pucData += 4;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormRaOptMsg
 Description     : RA报文选项部分设置
 Input           : ulIndex --- ND SERVER实体索引
                   pucMacAddr- 源链路层地址
 Output          : pucData --- 报文缓冲指针
                   pulLen ---- 报文长度指针
 Return          :

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormRaOptMsg
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *pucMacAddr,
    VOS_UINT8                          *pucData,
    VOS_UINT32                         *pulLen
)
{
    ESM_IP_IPV6_NW_PARA_STRU         *pstNwPara  = IP_NULL_PTR;
    VOS_UINT32                        ulCount    = IP_NULL;
    VOS_UINT32                        ulTmpMtu   = IP_NULL;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    pstNwPara = IP_NDSERVER_ADDRINFO_GET_NWPARA(ulIndex);

    /* 类型 */
    *pucData = IP_ICMPV6_OPT_SRC_LINK_LAYER_ADDR;
    pucData++;

    /* 长度 */
    *pucData = 1;
    pucData++;

    /* 链路层地址 */
    IP_MEM_CPY(pucData, pucMacAddr, IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    (*pulLen) += IP_ND_OPT_UNIT_LEN;

    if (IP_IPV6_OP_TRUE == pstNwPara->ulBitOpMtu)
    {
        /* 类型 */
        *pucData = IP_ICMPV6_OPT_MTU;
        pucData++;

        /* 长度 */
        *pucData = 1;
        pucData++;

        /* 保留 */
        pucData += 2;

        /*MTU: 取NV中的MTU和RA中的MTU的最小值作为发给PC的MTU*/
        ulTmpMtu = PS_MIN(g_ulNvMtu, pstNwPara->ulMtu);
        IP_SetUint32Data(pucData, ulTmpMtu);
        pucData += 4;

        (*pulLen) += IP_ND_OPT_UNIT_LEN;
    }

    for (ulCount = 0; ulCount < pstNwPara->ulPrefixNum; ulCount++)
    {
        /* 类型 */
        *pucData = IP_ICMPV6_OPT_PREFIX_INFO;
        pucData++;

        /* 长度 */
        *pucData = 4;
        pucData++;

        /* 前缀长度 */
        *pucData = (VOS_UINT8)(pstNwPara->astPrefixList[ulCount].ulBitPrefixLen);
        pucData++;

        /* 链路上标志、自治标志 */
        *pucData = (VOS_UINT8)(((pstNwPara->astPrefixList[ulCount].ulBitL & 0x1)<<7)
                                | ((pstNwPara->astPrefixList[ulCount].ulBitA & 0x1)<<6));
        pucData++;

        /* 有效生存期 */
        IP_SetUint32Data(pucData, pstNwPara->astPrefixList[ulCount].ulValidLifeTime);
        pucData += 4;

        /* 选用生存期 */
        IP_SetUint32Data(pucData, pstNwPara->astPrefixList[ulCount].ulPreferredLifeTime);
        pucData += 4;

        /* 保留字段 */
        pucData += 4;

        /* 前缀 */
        IP_MEM_CPY(pucData, pstNwPara->astPrefixList[ulCount].aucPrefix, IP_IPV6_ADDR_LEN);
        pucData += IP_IPV6_ADDR_LEN;

        (*pulLen) += (4 * IP_ND_OPT_UNIT_LEN);
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormEtherHeaderMsg
 Description     : IPv6报头设置
 Input           : aucSrcMacAddr --- 源MAC地址
                   aucDstMacAddr --- 目的MAC地址
 Output          : pucData --- 报文缓冲指针
 Return          :

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormEtherHeaderMsg
(
    const VOS_UINT8                    *aucSrcMacAddr,
    const VOS_UINT8                    *aucDstMacAddr,
    VOS_UINT8                          *pucData
)
{
    /* 目的MAC */
    IP_MEM_CPY( pucData,
                aucDstMacAddr,
                IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    /* 源MAC */
    IP_MEM_CPY( pucData,
                aucSrcMacAddr,
                IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    /* 类型 */
    IP_SetUint16Data(pucData, (VOS_UINT16)IP_GMAC_PAYLOAD_TYPE_IPV6);
    pucData += 2;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormRaMsg
 Description     : 生成路由公告消息
 Input           : ulIndex ------- 处理RA发包实体索引
                   pstNdMsgData -- 目的信息参数
 Output          : pucSendBuff --- 发送RA报文缓冲
                   pulSendLen ---- 发送报文长度

 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormRaMsg
(
    VOS_UINT32                          ulIndex,
    const IP_ND_MSG_STRU               *pstNdMsgData,
    VOS_UINT8                          *pucSendBuff,
    VOS_UINT32                         *pulSendLen
)
{
    VOS_UINT32                          ulPacketLen  = IP_NULL;
    VOS_UINT8                          *pucData      = pucSendBuff;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr = IP_NULL_PTR;

    /* 打印进入该函数 */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormRaMsg is entered.");

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pucData += IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /* 设置RA报头 */
    IP_NDSERVER_FormRaHeaderMsg(ulIndex, pucData);

    ulPacketLen += IP_ICMPV6_RA_HEADER_LEN;

    /* 根据自身MAC地址生成link-local地址 */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);
    IP_MEM_CPY(pstInfoAddr->aucUeLinkLocalAddr, aucSrcIPAddr, IP_IPV6_ADDR_LEN);

    /* 设置RA报文选项 */
    IP_NDSERVER_FormRaOptMsg(ulIndex, aucSrcMacAddr, (VOS_VOID *)(pucData + ulPacketLen), &ulPacketLen);

    /* 确定单播或组播方式 */
    if ((VOS_NULL_PTR != pstNdMsgData)
            && (IP_IPV6_IS_LINKLOCAL_ADDR(pstNdMsgData->aucSrcIp))
            && (1 == pstNdMsgData->uNdMsgStru.stRs.ucBitOpSrcLinkLayerAddr))
    {
        IP_MEM_CPY( aucDstIPAddr,
                    pstNdMsgData->aucSrcIp,
                    IP_IPV6_ADDR_LEN);

        IP_MEM_CPY( aucDstMacAddr,
                    pstNdMsgData->uNdMsgStru.stRs.aucSrcLinkLayerAddr,
                    IP_MAC_ADDR_LEN);
    }
    else
    {
        IP_MEM_CPY( aucDstIPAddr,
                    g_aucNdAllNodesMulticaseAddr,
                    IP_IPV6_ADDR_LEN);

        IP_MEM_CPY( aucDstMacAddr,
                    g_aucNdAllNodesMacAddr,
                    IP_MAC_ADDR_LEN);
    }

    pucData -= IP_IPV6_HEAD_LEN;

    /* 设置IPv6报头 */
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, ulPacketLen, pucData, IP_HEAD_PROTOCOL_ICMPV6);

    /* 生成ICMPv6报头校验和 */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pucData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormRaMsg: Build ICMPv6 Checksum failed.");
    }

    pucData -= IP_ETHERNET_HEAD_LEN;

    /* 设置以太报头 */
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pucData);

    /* 返回报文长度 */
    *pulSendLen = ulPacketLen + IP_IPV6_HEAD_LEN + IP_ETHERNET_HEAD_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SendRaMsg
 Description     : 发送路由公告消息
 Input           : ulIndex ------- 处理RA发包实体索引
                   pstNdMsgData -- 目的信息参数
 Output          :
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_SendRaMsg
(
    VOS_UINT32                          ulIndex,
    const IP_ND_MSG_STRU               *pstNdMsgData
)
{
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    VOS_UINT32                          ulSendLen    = IP_NULL;
    VOS_UINT32                          ulEpsbId;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, PS_FAIL);
    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    /* 调用形成RA消息函数 */
    IP_NDSERVER_FormRaMsg(ulIndex, pstNdMsgData, pucSendBuff, &ulSendLen);

    IP_NDSERVER_AddTransRaPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    /* 将RA消息发送到PC */
    return Ndis_SendMacFrm(pucSendBuff, ulSendLen, (VOS_UINT8)ulEpsbId);

}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNaHeaderMsg
 Description     : NA报文头固定部分设置
 Input           : pucTargetIPAddr --- 目的IP地址
                   ucSolicitFlag   --- 请求标志
 Output          : pucData --- 报文缓冲指针
 Return          :

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNaHeaderMsg
(
    const VOS_UINT8                    *pucTargetIPAddr,
    VOS_UINT8                           ucSolicitFlag,
    VOS_UINT8                          *pucData
)
{
    /* 类型 */
    *pucData = IP_ICMPV6_TYPE_NA;
    pucData++;

    /* 代码 */
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /* 跳过校验和 */
    pucData += 2;

    /* 路由器标志、请求标志、覆盖标志 */
    *pucData = (VOS_UINT8)(0xa0 | ((ucSolicitFlag & 0x1)<<6));
    pucData++;

    /* 保留 */
    pucData += 3;

    /* 目标地址 */
    IP_MEM_CPY( pucData,
                pucTargetIPAddr,
                IP_IPV6_ADDR_LEN);
    pucData += IP_IPV6_ADDR_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNaOptMsg
 Description     : NA报文选项部分设置
 Input           : pucMacAddr- 源链路层地址
 Output          : pucData --- 报文缓冲指针
                   pulLen ---- 报文长度指针
 Return          :

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNaOptMsg
(
    const VOS_UINT8                    *pucMacAddr,
    VOS_UINT8                          *pucData,
    VOS_UINT32                         *pulLen
)
{
    /* 类型 */
    *pucData = IP_ICMPV6_OPT_TGT_LINK_LAYER_ADDR;
    pucData++;

    /* 长度 */
    *pucData = 1;
    pucData++;

    /* 链路层地址 */
    IP_MEM_CPY(pucData, pucMacAddr, IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    (*pulLen) += IP_ND_OPT_UNIT_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNaMsg
 Description     : 生成邻居公告消息
 Input           : ulIndex ------- 处理NA发包实体索引
                   pstNdMsgData -- 目的信息参数
 Output          : pucSendBuff --- 发送NA报文缓冲
                   pulSendLen ---- 发送报文长度

 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNaMsg
(
    const IP_ND_MSG_STRU               *pstNdMsgData,
    VOS_UINT8                          *pucSendBuff,
    VOS_UINT32                         *pulSendLen
)
{
    VOS_UINT32                          ulPacketLen  = IP_NULL;
    VOS_UINT8                          *pucData      = pucSendBuff;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           ucSolicitFlag = IP_NULL;

    /* 打印进入该函数 */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormNaMsg is entered.");

    /* 根据自身MAC地址作为源MAC */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);

    if (VOS_NULL_PTR == pstNdMsgData)
    {
        /* 根据自身MAC地址生成link-local地址 */
        IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
        IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);
    }
    else
    {
        /* 使用目标地址作为源IP */
        IP_MEM_CPY( aucSrcIPAddr,
                    pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr,
                    IP_IPV6_ADDR_LEN);
    }


    /* 确定单播或组播方式 */
    if ((VOS_NULL_PTR != pstNdMsgData)
            && (!IP_IPV6_EQUAL_ALL_ZERO(pstNdMsgData->aucSrcIp))
            && (!IP_IPV6_IS_MULTICAST_ADDR(pstNdMsgData->aucSrcIp))
            && (1 == pstNdMsgData->uNdMsgStru.stNs.ucBitOpSrcLinkLayerAddr))
    {
        IP_MEM_CPY( aucDstIPAddr,
                    pstNdMsgData->aucSrcIp,
                    IP_IPV6_ADDR_LEN);

        IP_MEM_CPY( aucDstMacAddr,
                    pstNdMsgData->uNdMsgStru.stNs.aucSrcLinkLayerAddr,
                    IP_MAC_ADDR_LEN);

        ucSolicitFlag = 1;
    }
    else
    {
        IP_MEM_CPY( aucDstIPAddr,
                    g_aucNdAllNodesMulticaseAddr,
                    IP_IPV6_ADDR_LEN);

        IP_MEM_CPY( aucDstMacAddr,
                    g_aucNdAllNodesMacAddr,
                    IP_MAC_ADDR_LEN);
    }

    pucData += IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /* 设置NA报头 */
    IP_NDSERVER_FormNaHeaderMsg(aucSrcIPAddr, ucSolicitFlag, pucData);

    ulPacketLen += IP_ICMPV6_NA_HEADER_LEN;

    /* 设置NA可选项 */
    IP_NDSERVER_FormNaOptMsg(aucSrcMacAddr, (VOS_VOID *)(pucData + ulPacketLen), &ulPacketLen);

    pucData -= IP_IPV6_HEAD_LEN;

    /* 设置IPv6报头 */
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, ulPacketLen, pucData, IP_HEAD_PROTOCOL_ICMPV6);

    /* 生成ICMPv6校验和 */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pucData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormNaMsg: Build ICMPv6 Checksum failed.");
    }

    pucData -= IP_ETHERNET_HEAD_LEN;

    /* 设置以太报头 */
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pucData);

    /* 返回报文长度 */
    *pulSendLen = ulPacketLen + IP_IPV6_HEAD_LEN + IP_ETHERNET_HEAD_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SendNaMsg
 Description     : 发送邻居公告消息
 Input           : ulIndex ------- 处理NA发包实体索引
                   pstNdMsgData -- 目的信息参数
 Output          :
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_SendNaMsg
(
    VOS_UINT32                          ulIndex,
    const IP_ND_MSG_STRU               *pstNdMsgData
)
{
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    VOS_UINT32                          ulSendLen    = IP_NULL;
    VOS_UINT32                          ulEpsbId;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, PS_FAIL);
    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    /* 调用形成NA消息函数 */
    IP_NDSERVER_FormNaMsg(pstNdMsgData, pucSendBuff, &ulSendLen);

    IP_NDSERVER_AddTransNaPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    return Ndis_SendMacFrm(pucSendBuff, ulSendLen, (VOS_UINT8)ulEpsbId);
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNsHeaderMsg
 Description     : NS报文头固定部分设置
 Input           : ulIndex --- ND SERVER实体索引
 Output          : pucData --- 报文缓冲指针
 Return          :

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNsHeaderMsg
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucData,
    const VOS_UINT8                    *pstDstAddr
)
{
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    /* 类型 */
    *pucData = IP_ICMPV6_TYPE_NS;
    pucData++;

    /* 代码 */
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /* 跳过校验和 */
    pucData += 2;

    /* 保留 */
    pucData += 4;

    /* 目标地址 */
    IP_MEM_CPY( pucData,
                pstDstAddr,
                IP_IPV6_ADDR_LEN);

    pucData += IP_IPV6_ADDR_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNsOptMsg
 Description     : NS报文选项部分设置
 Input           : pucMacAddr- 源链路层地址
 Output          : pucData --- 报文缓冲指针
                   pulLen ---- 报文长度指针
 Return          :

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNsOptMsg
(
    const VOS_UINT8                    *pucMacAddr,
    VOS_UINT8                          *pucData,
    VOS_UINT32                         *pulLen
)
{
    /* 类型 */
    *pucData = IP_ICMPV6_OPT_SRC_LINK_LAYER_ADDR;
    pucData++;

    /* 长度 */
    *pucData = 1;
    pucData++;

    /* 链路层地址 */
    IP_MEM_CPY(pucData, pucMacAddr, IP_MAC_ADDR_LEN);
    pucData += IP_MAC_ADDR_LEN;

    (*pulLen) += IP_ND_OPT_UNIT_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormNsMsg
 Description     : 生成地址解析邻居请求消息
 Input           : ulIndex ------- 处理NS发包实体索引
 Output          : pucSendBuff --- 发送NS报文缓冲
                   pulSendLen ---- 发送报文长度

 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_FormNsMsg
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSendBuff,
    VOS_UINT32                         *pulSendLen,
    const VOS_UINT8                    *pstDstAddr
)
{
    VOS_UINT32                          ulPacketLen  = IP_NULL;
    VOS_UINT8                          *pucData      = pucSendBuff;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};

    /* 打印进入该函数 */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormNsMsg is entered.");

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    /* 根据自身MAC地址生成link-local地址 */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    /* 根据目的IP生成请求节点组播地址 */
    IP_ProduceSolicitedNodeMulticastIPAddr(aucDstIPAddr, pstDstAddr);
    IP_ProduceSolicitedNodeMulticastMacAddr(aucDstMacAddr, pstDstAddr);

    pucData += IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /* 设置NS报头 */
    IP_NDSERVER_FormNsHeaderMsg(ulIndex, pucData, pstDstAddr);

    ulPacketLen += IP_ICMPV6_NS_HEADER_LEN;

    /* 设置NS可选项 */
    IP_NDSERVER_FormNsOptMsg(aucSrcMacAddr, (VOS_VOID *)(pucData + ulPacketLen), &ulPacketLen);

    pucData -= IP_IPV6_HEAD_LEN;

    /* 设置IPv6报头 */
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, ulPacketLen, pucData, IP_HEAD_PROTOCOL_ICMPV6);

    /* 生成ICMPv6校验和 */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pucData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormNsMsg: Build ICMPv6 Checksum failed.");
    }

    pucData -= IP_ETHERNET_HEAD_LEN;

    /* 设置以太报头 */
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pucData);

    /* 返回报文长度 */
    *pulSendLen = ulPacketLen + IP_IPV6_HEAD_LEN + IP_ETHERNET_HEAD_LEN;

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SendNsMsg
 Description     : 发送地址解析邻居请求消息
 Input           : ulIndex ------- 处理NS发包实体索引
 Output          :
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_SendNsMsg
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *pstDstAddr
)
{
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    VOS_UINT32                          ulSendLen    = IP_NULL;
    VOS_UINT32                          ulEpsbId;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, PS_FAIL);
    ulEpsbId = IP_NDSERVER_GET_EPSBID(ulIndex);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    /* 调用形成NS消息函数 */
    IP_NDSERVER_FormNsMsg(ulIndex, pucSendBuff, &ulSendLen, pstDstAddr);

    IP_NDSERVER_AddTransNsPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    return Ndis_SendMacFrm(pucSendBuff, ulSendLen, (VOS_UINT8)ulEpsbId);
}


/*****************************************************************************
 函 数 名  : NdSer_GetAddrInfoIdx
 功能描述  : 根据ExRabId查找NDSERVER实体的索引
 输入参数  : VOS_UINT8 ucExRabId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : h00218138
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NdSer_GetAddrInfoIdx(VOS_UINT8 ucExRabId)
{
    VOS_UINT32 i = 0;

    /* 查询是否已存在相应Entity */
    do{
        if((PS_TRUE == g_astNdServerAddrInfo[i].ucValidFlag) && (ucExRabId == g_astNdServerAddrInfo[i].ucEpsbId))
        {
            /*找到相应实体*/
            return i;
        }

    }while((++i) < IP_NDSERVER_ADDRINFO_MAX_NUM);

    return IP_NDSERVER_ADDRINFO_MAX_NUM;
}

/*****************************************************************************
 函 数 名  : NdSer_AllocAddrInfo
 功能描述  : 分配一个空闲的NDSERVER实体
 输入参数  : 无
 输出参数  : ulIndex
 返 回 值  : IP_NDSERVER_ADDR_INFO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : h00218138
    修改内容   : 新生成函数

*****************************************************************************/
IP_NDSERVER_ADDR_INFO_STRU* NdSer_AllocAddrInfo(VOS_UINT32* pUlIndex)
{
    VOS_UINT32 i = 0;

    if(IP_NULL_PTR == pUlIndex)
    {
        return IP_NULL_PTR;
    }

    *pUlIndex = IP_NDSERVER_ADDRINFO_MAX_NUM;

    do{
        if(PS_FALSE == g_astNdServerAddrInfo[i].ucValidFlag)
        {
            /*找到空闲实体*/
            *pUlIndex = i;
            return &g_astNdServerAddrInfo[i];
        }

    }while((++i) < IP_NDSERVER_ADDRINFO_MAX_NUM);

    return IP_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : NdSer_CheckIpv6PdnInfo
 功能描述  : PDN IPV6地址信息检查
 输入参数  : AT_NDIS_IPV6_PDN_INFO_STRU
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月11日
    作    者   : h00159435
    修改内容   : 新生成函数

  2.日    期   : 2013年1月15日
    作    者   : h00218138
    修改内容   : DSDA开发，使用ExRabId来映射NdSer实体

*****************************************************************************/
VOS_UINT32 NdSer_CheckIpv6PdnInfo(AT_NDIS_IPV6_PDN_INFO_STRU *pstIpv6PdnInfo)
{
    VOS_UINT32                          ulIndex       = IP_NULL;
    ND_IP_IPV6_PREFIX_STRU             *pstIpv6Prefix = IP_NULL_PTR;

    /* 遍历前缀列表，查找A标识为1，前缀长度为64的前缀 */
    for (ulIndex = IP_NULL; ulIndex < pstIpv6PdnInfo->ulPrefixNum; ulIndex++)
    {
        pstIpv6Prefix = (ND_IP_IPV6_PREFIX_STRU*)&pstIpv6PdnInfo->astPrefixList[ulIndex];
        if ((PS_TRUE == pstIpv6Prefix->ulBitA)
            && ((ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH)*8 == pstIpv6Prefix->ulBitPrefixLen)
            && (!IP_IPV6_64BITPREFIX_EQUAL_ZERO(pstIpv6Prefix->aucPrefix))
            && (!IP_IPV6_IS_LINKLOCAL_ADDR(pstIpv6Prefix->aucPrefix))
            && (!IP_IPV6_IS_MULTICAST_ADDR(pstIpv6Prefix->aucPrefix)))
        {
            return PS_SUCC;
        }
    }

    return PS_FAIL;
}

/*****************************************************************************
 Function Name   : NdSer_Ipv6PdnInfoCfg
 Description     : 处理NDIS发来的Ipv6PdnInfoCfg
 Input           : VOS_UINT8 ucRabId, AT_NDIS_IPV6_PDN_INFO_STRU *pstIpv6PdnInfo
 Output          : None
 Return          : VOS_VOID

 History         :
    1.huibo 00159435      2011-12-09  Draft Enact
    1.houguoqiang 00218138      2013-1-16  Modified for DSDA
*****************************************************************************/
VOS_VOID NdSer_Ipv6PdnInfoCfg(VOS_UINT8 ucExRabId, AT_NDIS_IPV6_PDN_INFO_STRU *pstIpv6PdnInfo)
{
    VOS_UINT32                          ulIndex       = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr   = IP_NULL_PTR;
    ESM_IP_IPV6_NW_PARA_STRU            stNwParamTmp  = {IP_NULL};

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcEsmIpNwParaInd is entered.");

    /*通过扩展RabId查找NDSERVER实体，如果查找不到，则分配一个空闲的*/
    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);
    if(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    }
    else
    {
        /*分配一个AddrInfo结构体，并且获得Index*/
        pstInfoAddr = NdSer_AllocAddrInfo(&ulIndex);
    }

    if(IP_NULL_PTR == pstInfoAddr)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: Get ND Server Entity failed.", ucExRabId);
        return;
    }

    /* 获取网络参数 */
    if (IP_SUCC != IP_NDSERVER_GetNwPara(&stNwParamTmp, pstIpv6PdnInfo))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: Get Nw Param fail.");
        return;
    }

    /* 判断是否未分配过路由前缀 */
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        VOS_UINT8* pucIpV6;
        pucIpV6 = IP_NDSERVER_GetTeDetectIp(stNwParamTmp.astPrefixList[0].aucPrefix);

        /* MT关机再开机后，ND SERVER收到网侧RA前，可能先收到TE的重复地址检测NS */
        if(IP_NULL_PTR != pucIpV6)
        {
            IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: Using saved TeAddr to get MAC.");

            IP_MEM_CPY(pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr, pucIpV6, ND_IP_IPV6_ADDR_LENGTH);
            pstInfoAddr->stTeAddrInfo.enTeAddrState = IP_NDSERVER_TE_ADDR_INCOMPLETE;

            /* 启动收到重复地址检测后的等待定时器 */
            IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_FIRST_NS);
        }
        else
        {
            IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: None saved TeAddr.");

            /* 启动路由公告定时器 */
            IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_RA);
        }
    }
    /* 判断是否路由前缀发生了变化 */
    else if (0 != IP_MEM_CMP(    pstInfoAddr->stIpv6NwPara.astPrefixList[0].aucPrefix,
                                stNwParamTmp.astPrefixList[0].aucPrefix,
                                (ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH)))
    {
        IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_Ipv6PdnInfoCfg: Valid ND Server get new Nw Param.");

        /* 清除TE地址记录 */
        IP_MEM_SET( &pstInfoAddr->stTeAddrInfo,
                    IP_NULL,
                    sizeof(IP_NDSERVER_TE_ADDR_INFO_STRU));

        /* 启动路由公告定时器 */
        IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_RA);
    }

    /* 将stNwParamTmp中的内容拷贝到pstInfoAddr->stIpv6NwPara中 */
    IP_MEM_CPY( &pstInfoAddr->stIpv6NwPara,
                &stNwParamTmp,
                sizeof(ESM_IP_IPV6_NW_PARA_STRU));


    /* 设置承载号 */
    pstInfoAddr->ucEpsbId = ucExRabId;

    /* 置位ND SERVER结构体有效标志 */
    pstInfoAddr->ucValidFlag = IP_TRUE;

    /* 发送RA消息到PC */
    if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, VOS_NULL_PTR))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);/* [false alarm]:代码保证了不会越界 */
        IPND_ERROR_LOG(NDIS_NDSERVER_PID,"NdSer_Ipv6PdnInfoCfg:Send RA Msg failed.");
    }

    return;
}


/*****************************************************************************
 Function Name   : IP_NDSERVER_DecodeRsData
 Description     : 对RS包进行格式转换
 Input           : pucSrcData ----------- 源报文指针
                   pstDestData ---------- 目的转换结构指针
                   ulIcmpv6HeadOffset --- ICMPv6报头偏移量
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-07  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_DecodeRsData
(
    VOS_UINT8                          *pucSrcData,
    IP_ND_MSG_STRU                     *pstDestData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT32                          ulPayLoad;
    VOS_INT32                           remainLen;
    VOS_UINT32                          ulOptType;
    VOS_UINT32                          ulOptLen;
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    IP_ND_MSG_RS_STRU                  *pstRs = &pstDestData->uNdMsgStru.stRs;

    /* 获取PAYLOAD */
    IP_GetUint16Data(ulPayLoad, pucIpMsg + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    remainLen = (VOS_INT32)(ulPayLoad + IP_IPV6_HEAD_LEN - (ulIcmpv6HeadOffset + IP_ICMPV6_RS_HEADER_LEN));

    if (remainLen < 0)
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Invalid IPV6 PayLoad::!", ulPayLoad, ulIcmpv6HeadOffset);
        return IP_FAIL;
    }

    IP_MEM_CPY(pstDestData->aucSrcIp, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    IP_MEM_CPY(pstDestData->aucDesIp, pucIpMsg + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    pucIpMsg += ulIcmpv6HeadOffset + IP_ICMPV6_RS_HEADER_LEN;

    while (remainLen >= IP_ND_OPT_UNIT_LEN)
    {
        ulOptType = *pucIpMsg;
        ulOptLen = *(pucIpMsg + 1);

        if(0 == ulOptLen)
        {
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Invalid ND options length 0!");
            return IP_FAIL;
        }

        switch(ulOptType)
        {
            case IP_ICMPV6_OPT_SRC_LINK_LAYER_ADDR:
                {
                    if(1 == ulOptLen)
                    {
                        if(0 == pstRs->ucBitOpSrcLinkLayerAddr)
                        {
                            IP_MEM_CPY(pstRs->aucSrcLinkLayerAddr, pucIpMsg+2, IP_MAC_ADDR_LEN);
                            pstRs->ucBitOpSrcLinkLayerAddr = 1;
                        }
                        else
                        {
                            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Redundant Source Link-Layer Addr!");
                        }
                    }
                    else
                    {
                        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Invalid Source Link-Layer Addr Length:!", ulOptLen);
                    }
                }
                break;
            default:
                break;
        }

        remainLen -= (VOS_INT32)IP_GetNdOptionLen(ulOptLen);
        pucIpMsg += IP_GetNdOptionLen(ulOptLen);
    }

    if(0 != remainLen)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeRsData: Payload not match Package:!", remainLen);
    }

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_RsMsgProc
 Description     : 处理RS消息
 Input           : ulIndex  -------------- 处理消息实体索引
                   pucSrcData ------------ IP数据报
                   ulIcmpv6HeadOffset ---- ICMPv6报文头偏移量
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-06  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_RsMsgProc
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT8                          *pucIpMsg     = pucSrcData;
    IP_ND_MSG_STRU                     *pstNdMsgData = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_RsMsgProc is entered.");

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    IP_NDSERVER_AddRcvRsPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IP_NDSERVER_AddErrRsPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_RsMsgProc: ND Server info flag is invalid!");
        return ;
    }

    pstNdMsgData = IP_NDSERVER_GET_NDMSGDATA_ADDR();
    IP_MEM_SET(pstNdMsgData, IP_NULL, sizeof(IP_ND_MSG_STRU));

    if (IP_SUCC != IP_NDSERVER_DecodeRsData(pucIpMsg, pstNdMsgData, ulIcmpv6HeadOffset))
    {
        IP_NDSERVER_AddErrRsPktNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcessRsMsg: Invalid IPV6 RS Msg:!");
        return ;
    }

    /* 发送RA消息到PC */
    if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, pstNdMsgData))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_RsMsgProc:Send RA Msg failed.");
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_DecodeNsData
 Description     : 对NS包进行格式转换
 Input           : pucSrcData ----------- 源报文指针
                   pstDestData ---------- 目的转换结构指针
                   ulIcmpv6HeadOffset --- ICMPv6报头偏移量
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_DecodeNsData
(
    VOS_UINT8                          *pucSrcData,
    IP_ND_MSG_STRU                     *pstDestData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT32                          ulPayLoad;
    VOS_INT32                           remainLen;
    VOS_UINT32                          ulOptType;
    VOS_UINT32                          ulOptLen;
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    IP_ND_MSG_NS_STRU                  *pstNs = &pstDestData->uNdMsgStru.stNs;

    /* 获取PAYLOAD */
    IP_GetUint16Data(ulPayLoad, pucIpMsg + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    remainLen = (VOS_INT32)(ulPayLoad + IP_IPV6_HEAD_LEN - (ulIcmpv6HeadOffset + IP_ICMPV6_NS_HEADER_LEN));

    if (remainLen < 0)
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Invalid IPV6 PayLoad::!", ulPayLoad, ulIcmpv6HeadOffset);
        return IP_FAIL;
    }

    IP_MEM_CPY(pstDestData->aucSrcIp, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    IP_MEM_CPY(pstDestData->aucDesIp, pucIpMsg + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    IP_MEM_CPY( pstNs->aucTargetAddr,
                pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_TARGET_ADDR_OFFSET,
                IP_IPV6_ADDR_LEN);

    pucIpMsg += ulIcmpv6HeadOffset + IP_ICMPV6_NS_HEADER_LEN;

    while (remainLen >= IP_ND_OPT_UNIT_LEN)
    {
        ulOptType = *pucIpMsg;
        ulOptLen = *(pucIpMsg + 1);

        if(0 == ulOptLen)
        {
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Invalid ND options length 0!");
            return IP_FAIL;
        }

        switch(ulOptType)
        {
            case IP_ICMPV6_OPT_SRC_LINK_LAYER_ADDR:
                {
                    if(1 == ulOptLen)
                    {
                        if(0 == pstNs->ucBitOpSrcLinkLayerAddr)
                        {
                            IP_MEM_CPY(pstNs->aucSrcLinkLayerAddr, pucIpMsg+2, IP_MAC_ADDR_LEN);
                            pstNs->ucBitOpSrcLinkLayerAddr = 1;
                        }
                        else
                        {
                            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Redundant Source Link-Layer Addr!");
                        }
                    }
                    else
                    {
                        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Invalid Source Link-Layer Addr Length:!", ulOptLen);
                    }
                }
                break;
            default:
                break;
        }

        remainLen -= (VOS_INT32)IP_GetNdOptionLen(ulOptLen);
        pucIpMsg += IP_GetNdOptionLen(ulOptLen);
    }

    if(0 != remainLen)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNsData: Payload not match Package:!", remainLen);
    }

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_IsSelfIPAddr
 Description     : 判断是否是自己的IP地址
 Input           : ulIndex  -------------- 处理消息实体索引
                   aucIPAddr ------------  IP地址指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_IsSelfIPAddr
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucIPAddr
)
{
    VOS_UINT8                           aucLinkLocalIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucGlobalIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    ESM_IP_IPV6_NW_PARA_STRU           *pstNwPara  = IP_NULL_PTR;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, IP_FALSE);

    /* 根据自身MAC地址生成link-local地址 */
    IP_MEM_CPY( aucMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucLinkLocalIPAddr, aucMacAddr);
    IP_SetUint16Data(aucLinkLocalIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    IP_ProduceIfaceIdFromMacAddr(aucGlobalIPAddr, aucMacAddr);
    pstNwPara = IP_NDSERVER_ADDRINFO_GET_NWPARA(ulIndex);
    IP_MEM_CPY( aucGlobalIPAddr,
                pstNwPara->astPrefixList[0].aucPrefix,
                ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH);

    /*lint -e960*/
    if ((IP_NULL == IP_MEM_CMP(  aucIPAddr,
                                 aucLinkLocalIPAddr,
                                 IP_IPV6_ADDR_LEN))
        || (IP_NULL == IP_MEM_CMP(  aucIPAddr,
                                    aucGlobalIPAddr,
                                    IP_IPV6_ADDR_LEN)))

    /*lint +e960*/
    {
        return IP_TRUE;
    }
    else
    {
        return IP_FALSE;
    }
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_EqualAdvertisedPrefix
 Description     : 判断是否符合已公告的全球前缀
 Input           : ulIndex  -------------- 处理消息实体索引
                   aucIPAddr ------------  IP地址指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_EqualAdvertisedPrefix
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucIPAddr
)
{
    ESM_IP_IPV6_NW_PARA_STRU           *pstNwPara  = IP_NULL_PTR;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, IP_FALSE);
    pstNwPara = IP_NDSERVER_ADDRINFO_GET_NWPARA(ulIndex);

    if (IP_NULL == IP_MEM_CMP(  aucIPAddr,
                                pstNwPara->astPrefixList[0].aucPrefix,
                                ND_IP_IPV6_ADDR_LENGTH - ND_IP_IPV6_IFID_LENGTH))
    {
        return IP_TRUE;
    }
    else
    {
        return IP_FALSE;
    }
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_RcvTeDetectionAddr
 Description     : 收到重复地址检测地址
 Input           : ulIndex  -------------- ND SERVER实体索引
                   aucIPAddr ------------  IP地址指针
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_RcvTeDetectionAddr
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucIPAddr
)
{
    IP_NDSERVER_TE_ADDR_INFO_STRU       *pstTeInfo  = IP_NULL_PTR;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);
    /*lint -e960*/
    if ((IP_NDSERVER_TE_ADDR_REACHABLE == pstTeInfo->enTeAddrState)
            && (IP_NULL == IP_MEM_CMP(pstTeInfo->aucTeGlobalAddr, aucIPAddr, IP_IPV6_ADDR_LEN)))
    /*lint +e960*/
    {
        return;
    }

    IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_RcvTeDetectionAddr: Old Te Addr:", pstTeInfo->enTeAddrState);
    /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), pstTeInfo->aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */
    IP_MEM_CPY( pstTeInfo->aucTeGlobalAddr,
                aucIPAddr,
                IP_IPV6_ADDR_LEN);
    pstTeInfo->enTeAddrState = IP_NDSERVER_TE_ADDR_INCOMPLETE;

    IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_RcvTeDetectionAddr: New Te Addr:", pstTeInfo->enTeAddrState);
    /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), pstTeInfo->aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_NsMsgProc
 Description     : 处理NS消息
 Input           : ulIndex  -------------- 处理消息实体索引
                   pucSrcData ------------ IP数据报
                   ulIcmpv6HeadOffset ---- ICMPv6报文头偏移量
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_NsMsgProc
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT8                          *pucIpMsg     = pucSrcData;
    IP_ND_MSG_STRU                     *pstNdMsgData = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc is entered.");
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    IP_NDSERVER_AddRcvNsPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pstNdMsgData = IP_NDSERVER_GET_NDMSGDATA_ADDR();
    IP_MEM_SET(pstNdMsgData, IP_NULL, sizeof(IP_ND_MSG_STRU));

    if (IP_SUCC != IP_NDSERVER_DecodeNsData(pucIpMsg, pstNdMsgData, ulIcmpv6HeadOffset))
    {
        IP_NDSERVER_AddErrNsPktNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc: Invalid IPV6 NS Msg:!");
        return ;
    }

    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        /* MT关机再开机后，ND SERVER收到网侧RA前，可能先收到TE的重复地址检测NS */
        if ((IP_IPV6_EQUAL_ALL_ZERO(pstNdMsgData->aucSrcIp))
                && (0 == pstNdMsgData->uNdMsgStru.stNs.ucBitOpSrcLinkLayerAddr))
        {
            IP_NDSERVER_SaveTeDetectIp(pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr);
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc: receive DAD NS packet before RA.");
        }
        else
        {
            IP_NDSERVER_AddErrNsPktNum(ulIndex);
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc: ND Server info flag is invalid!");
        }
        return ;
    }

    if (IP_TRUE == IP_NDSERVER_IsSelfIPAddr(ulIndex, pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr))
    {
        /* 发送NA消息到PC */
        if (PS_SUCC != IP_NDSERVER_SendNaMsg(ulIndex, pstNdMsgData))
        {
            IP_NDSERVER_AddTransPktFailNum(ulIndex);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc:Send NA Msg failed.");
        }
    }
    else
    {
        /* 判断是否是重复地址检测NS */
        if ((IP_IPV6_EQUAL_ALL_ZERO(pstNdMsgData->aucSrcIp))
                && (0 == pstNdMsgData->uNdMsgStru.stNs.ucBitOpSrcLinkLayerAddr))
        {
            if (IP_TRUE == IP_NDSERVER_EqualAdvertisedPrefix(ulIndex, pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr))
            {
                IP_NDSERVER_RcvTeDetectionAddr(ulIndex, pstNdMsgData->uNdMsgStru.stNs.aucTargetAddr);

                /* 启动收到重复地址检测后的等待定时器 */
                IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_FIRST_NS);

                IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc:Receive duplicate addr detection packet.");
                return ;
            }
            else
            {
                IP_NDSERVER_AddErrNsPktNum(ulIndex);
                IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc:Duplicate addr detection IP don't equal Advertised Prefix, discard!");
                return ;
            }
        }
        else
        {
            IP_NDSERVER_AddErrNsPktNum(ulIndex);
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NsMsgProc:Target IP is not self addr, discard!");
            return ;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_DecodeNaData
 Description     : 对NA包进行格式转换
 Input           : pucSrcData ----------- 源报文指针
                   pstDestData ---------- 目的转换结构指针
                   ulIcmpv6HeadOffset --- ICMPv6报头偏移量
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_DecodeNaData
(
    VOS_UINT8                          *pucSrcData,
    IP_ND_MSG_STRU                     *pstDestData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT32                          ulPayLoad;
    VOS_INT32                           remainLen;
    VOS_UINT32                          ulOptType;
    VOS_UINT32                          ulOptLen;
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    IP_ND_MSG_NA_STRU                  *pstNa = &pstDestData->uNdMsgStru.stNa;

    /* 获取PAYLOAD */
    IP_GetUint16Data(ulPayLoad, pucIpMsg + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET);

    remainLen = (VOS_INT32)(ulPayLoad + IP_IPV6_HEAD_LEN - (ulIcmpv6HeadOffset + IP_ICMPV6_NA_HEADER_LEN));

    if (remainLen < 0)
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Invalid IPV6 PayLoad::!", ulPayLoad, ulIcmpv6HeadOffset);
        return IP_FAIL;
    }

    IP_MEM_CPY(pstDestData->aucSrcIp, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    IP_MEM_CPY(pstDestData->aucDesIp, pucIpMsg + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    pstNa->ucBitR = ((*(pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_NA_FLAG_OFFSET)) >> 7) & 0x01;
    pstNa->ucBitS = ((*(pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_NA_FLAG_OFFSET)) >> 6) & 0x01;
    pstNa->ucBitO = ((*(pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_NA_FLAG_OFFSET)) >> 5) & 0x01;

    IP_MEM_CPY( pstNa->aucTargetAddr,
                pucIpMsg + ulIcmpv6HeadOffset + IP_ICMPV6_TARGET_ADDR_OFFSET,
                IP_IPV6_ADDR_LEN);

    pucIpMsg += ulIcmpv6HeadOffset + IP_ICMPV6_NA_HEADER_LEN;

    while (remainLen >= IP_ND_OPT_UNIT_LEN)
    {
        ulOptType = *pucIpMsg;
        ulOptLen = *(pucIpMsg + 1);

        if(0 == ulOptLen)
        {
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Invalid ND options length 0!");
            return IP_FAIL;
        }

        switch(ulOptType)
        {
            case IP_ICMPV6_OPT_TGT_LINK_LAYER_ADDR:
                {
                    if(1 == ulOptLen)
                    {
                        if(0 == pstNa->ucBitOpTargetLinkLayerAddr)
                        {
                            IP_MEM_CPY(pstNa->aucTargetLinkLayerAddr, pucIpMsg+2, IP_MAC_ADDR_LEN);
                            pstNa->ucBitOpTargetLinkLayerAddr = 1;
                        }
                        else
                        {
                            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Redundant Target Link-Layer Addr!");
                        }
                    }
                    else
                    {
                        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Invalid Target Link-Layer Addr Length:!", ulOptLen);
                    }
                }
                break;
            default:
                break;
        }

        remainLen -= (VOS_INT32)IP_GetNdOptionLen(ulOptLen);
        pucIpMsg += IP_GetNdOptionLen(ulOptLen);
    }

    if(0 != remainLen)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_DecodeNaData: Payload not match Package:!", remainLen);
    }

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_EqualSavedTeAddr
 Description     : 判断是否是已保存的TE地址
 Input           : ulIndex  -------------  ND SERVER实体索引
                   aucIPAddr ------------  IP地址指针
                   aucMACAddr -----------  MAC地址指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_UINT32 IP_NDSERVER_EqualSavedTeAddr
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucIPAddr,
    const VOS_UINT8                    *aucMACAddr
)
{
    IP_NDSERVER_TE_ADDR_INFO_STRU       *pstTeInfo  = IP_NULL_PTR;

    IP_ASSERT_RTN(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM, IP_FALSE);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    /*lint -e960*/
    if ((IP_NDSERVER_TE_ADDR_REACHABLE == pstTeInfo->enTeAddrState)
            && (IP_NULL == IP_MEM_CMP(pstTeInfo->aucTeGlobalAddr, aucIPAddr, IP_IPV6_ADDR_LEN))
            && (IP_NULL == IP_MEM_CMP(pstTeInfo->aucTeLinkLayerAddr, aucMACAddr, IP_MAC_ADDR_LEN)))
    /*lint +e960*/
    {
        return IP_TRUE;
    }
    else
    {
        return IP_FALSE;
    }
}
/*****************************************************************************
 Function Name   : IP_NDSERVER_SendDlPkt
 Description     : 发送下行缓存的IPV6数据包
 Input           : ulIndex  -------------  ND SERVER实体索引
 Output          : None
 Return          : VOS_VOID

 History         :
    1.huibo 00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_SendDlPkt(VOS_UINT32 ulIndex)
{
    IMM_ZC_STRU                        *pstImmZc    = VOS_NULL_PTR;
    VOS_UINT8                           ucRabId     = 0;
    ADS_PKT_TYPE_ENUM_UINT8             ucPktType   = 0;
    VOS_UINT16                          usApp       = 0;
    VOS_INT32                           lLockKey;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    while(PS_TRUE != (LUP_IsQueEmpty(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex))))
    {
        lLockKey = VOS_SplIMP();
        if (PS_SUCC != LUP_DeQue(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex), (VOS_VOID**)(&pstImmZc)))
        {
            VOS_Splx(lLockKey);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDlPkt, LUP_DeQue return fail!");
            return;
        }
        VOS_Splx(lLockKey);

        /*从 ImmZc中取出RabId和enPdpType*/
        /*lint -e522*/
        usApp     = IMM_ZcGetUserApp(pstImmZc);
        ucRabId   = (VOS_UINT8)(usApp & 0xFF);  /*保存的值实际是 扩展RabId*/
        ucPktType = (VOS_UINT8)(usApp >> 8);

        if (PS_SUCC != Ndis_DlSendNcm(ucRabId, ucPktType, pstImmZc))
        {
            IMM_ZcFree(pstImmZc);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDlPkt, Ndis_DlSendNcm fail!");
        }
        /*lint +e522*/

        IP_NDSERVER_AddSendQuePktNum(ulIndex);
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_UpdateTeAddrInfo
 Description     : 收到重复地址检测地址
 Input           : ulIndex  -------------  ND SERVER实体索引
                   aucGlobalIPAddr ------  全球IP地址指针
                   aucMACAddr -----------  MAC地址指针
                   aucLinkLocalIPAddr ---  链路本地IP地址指针
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_UpdateTeAddrInfo
(
    VOS_UINT32                          ulIndex,
    const VOS_UINT8                    *aucGlobalIPAddr,
    const VOS_UINT8                    *aucMACAddr,
    const VOS_UINT8                    *aucLinkLocalIPAddr
)
{
    IP_NDSERVER_TE_ADDR_INFO_STRU       *pstTeInfo  = IP_NULL_PTR;

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_UpdateTeAddrInfo: Old Te Addr:", pstTeInfo->enTeAddrState);
    /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), pstTeInfo->aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */
    IP_MEM_CPY( pstTeInfo->aucTeGlobalAddr,
                aucGlobalIPAddr,
                IP_IPV6_ADDR_LEN);

    IP_MEM_CPY( pstTeInfo->aucTeLinkLayerAddr,
                aucMACAddr,
                IP_MAC_ADDR_LEN);

    /*更新完整MAC帧头中的目的MAC地址*/
    IP_MEM_CPY( IP_NDSERVER_ADDRINFO_GET_MACFRAME(ulIndex),
                aucMACAddr,
                IP_MAC_ADDR_LEN);

    if (IP_IPV6_IS_LINKLOCAL_ADDR(aucLinkLocalIPAddr))
    {
        IP_MEM_CPY( pstTeInfo->aucTeLinkLocalAddr,
                    aucLinkLocalIPAddr,
                    IP_IPV6_ADDR_LEN);
    }
    else
    {
        IP_MEM_SET( pstTeInfo->aucTeLinkLocalAddr,
                    IP_NULL,
                    IP_IPV6_ADDR_LEN);

    }

    pstTeInfo->enTeAddrState = IP_NDSERVER_TE_ADDR_REACHABLE;

    IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_UpdateTeAddrInfo: New Te Addr:", pstTeInfo->enTeAddrState);
    /*IP_PrintArray(IP_GET_IP_PRINT_BUF(), pstTeInfo->aucTeGlobalAddr, IP_IPV6_ADDR_LEN);
 */

    /*发送下行IP缓存队列中的数据包*/
    IP_NDSERVER_SendDlPkt(ulIndex);

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_NaMsgProc
 Description     : 处理NA消息
 Input           : ulIndex  -------------- 处理消息实体索引
                   pucSrcData ------------ IP数据报
                   ulIcmpv6HeadOffset ---- ICMPv6报文头偏移量
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-08  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_NaMsgProc
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT32                          ulIcmpv6HeadOffset
)
{
    VOS_UINT8                          *pucIpMsg     = pucSrcData;
    IP_ND_MSG_STRU                     *pstNdMsgData = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc is entered.");
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    IP_NDSERVER_AddRcvNaPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc: ND Server info flag is invalid!");
        return ;
    }

    pstNdMsgData = IP_NDSERVER_GET_NDMSGDATA_ADDR();
    IP_MEM_SET(pstNdMsgData, IP_NULL, sizeof(IP_ND_MSG_STRU));

    if (IP_SUCC != IP_NDSERVER_DecodeNaData(pucIpMsg, pstNdMsgData, ulIcmpv6HeadOffset))
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc: Invalid IPV6 NS Msg:!");
        return ;
    }

    if (0 == pstNdMsgData->uNdMsgStru.stNa.ucBitOpTargetLinkLayerAddr)
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc:Packet don't contain Target Linklayer Addr, discard!");
        return ;
    }

    if ((IP_TRUE != IP_NDSERVER_IsSelfIPAddr(ulIndex, pstNdMsgData->aucDesIp))
        && (!IP_IPV6_IS_MULTICAST_ADDR(pstNdMsgData->aucDesIp)))
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc:Destination IP don't contain self Addr, discard!");
        return ;
    }

    if (IP_TRUE != IP_NDSERVER_EqualAdvertisedPrefix(ulIndex, pstNdMsgData->uNdMsgStru.stNa.aucTargetAddr))
    {
        IP_NDSERVER_AddErrNaPktNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_NaMsgProc:Target IP don't equal Advertised Prefix, discard!");
        return ;
    }

    if (IP_TRUE != IP_NDSERVER_EqualSavedTeAddr(    ulIndex,
                                                    pstNdMsgData->uNdMsgStru.stNa.aucTargetAddr,
                                                    pstNdMsgData->uNdMsgStru.stNa.aucTargetLinkLayerAddr))
    {
        IP_NDSERVER_UpdateTeAddrInfo(   ulIndex,
                                        pstNdMsgData->uNdMsgStru.stNa.aucTargetAddr,
                                        pstNdMsgData->uNdMsgStru.stNa.aucTargetLinkLayerAddr,
                                        pstNdMsgData->aucSrcIp);

        /*MAC地址直接从ND SERVER实体里获得，不需要再配置APR模块*/
        /*IP_NDSERVER_ConfigArpInfo(  ulIndex,
                                    pstNdMsgData->uNdMsgStru.stNa.aucTargetAddr,
                                    pstNdMsgData->uNdMsgStru.stNa.aucTargetLinkLayerAddr);*/

    }

    IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_PERIODIC_NS);

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_BuildTooBigICMPPkt
 Description     : 形成向PC回复的超长包响应
 Input           : pucSrcData ----------- 源报文指针
                   pstDestData ---------- 目的转换结构指针
                   ulIcmpv6HeadOffset --- ICMPv6报头偏移量
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_BuildTooBigICMPPkt
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT8                          *pstDestData,
    VOS_UINT32                          ulDataLen
)
{
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    if  (ulDataLen <= (IP_IPV6_HEAD_LEN + IP_ICMPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_BuildTooBigICMPPkt: ulDataLen is too short.", ulDataLen);
        return IP_FAIL;
    }

    /* 根据自身MAC地址生成link-local地址 */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    /*得到目的IPV6地址*/
    IP_MEM_CPY(aucDstIPAddr, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    /*得到目的MAC地址*/
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);
    IP_MEM_CPY( aucDstMacAddr,
                pstTeInfo->aucTeLinkLayerAddr,
                IP_MAC_ADDR_LEN);

    /*指向ICMP首部 */
    pucData  = pstDestData + IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /*ICMP type域*/
    *pucData = IP_ICMPV6_PACKET_TOO_BIG;
    pucData++;

    /*ICMP code域*/
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /*ICMP 校验和域*/
    *(VOS_UINT16 *)(VOS_VOID*)pucData = 0;
    pucData += 2;

    /*MTU 域*/
    /*lint -e960*/
    *(VOS_UINT32 *)(VOS_VOID*)pucData = VOS_HTONL(ulDataLen);
    /*lint +e960*/
    pucData += 4;

    /*填写ICMP PayLoad部分*/
    IP_MEM_CPY(pucData, pucIpMsg,((ulDataLen-IP_IPV6_HEAD_LEN)- IP_ICMPV6_HEAD_LEN));

    /*指向IPV6首部*/
    pstDestData += IP_ETHERNET_HEAD_LEN;
    /*填写IPV6头部*/
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, (ulDataLen-IP_IPV6_HEAD_LEN), pstDestData, IP_HEAD_PROTOCOL_ICMPV6);

    /* 生成ICMPv6报头校验和 */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pstDestData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormRaMsg: Build ICMPv6 Checksum failed.");
        return IP_FAIL;
    }

    /* 设置以太报头 */
    pstDestData -= IP_ETHERNET_HEAD_LEN;
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pstDestData);

    return IP_SUCC;
}

/*****************************************************************************
 函 数 名  : IP_NDSERVER_ProcTooBigPkt
 功能描述  : 处理PC发送的超长包
 输入参数  : VOS_VOID  *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : 00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTooBigPkt(VOS_UINT8 ucRabId, VOS_UINT8 *pucSrcData, VOS_UINT32 ulDataLen)
{
    VOS_UINT32                           ulIndex;
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucRabId);
    if(ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTooBigPkt: ND Server info flag is invalid!");
        return ;
    }

    IP_NDSERVER_AddRcvBooBigPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    if (IP_SUCC != IP_NDSERVER_BuildTooBigICMPPkt(ulIndex, pucIpMsg, pucSendBuff, ulDataLen))
    {
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTooBigPkt: IP_NDSERVER_BuildTooBigICMPPkt FAIL!");
        return;
    }

    /* 将超长包响应发送到PC */
    if (PS_FAIL == Ndis_SendMacFrm(pucSendBuff, ulDataLen+IP_ETHERNET_HEAD_LEN, pstInfoAddr->ucEpsbId))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTooBigPkt:Send TooBigPkt failed.");
        return;
    }

    IP_NDSERVER_AddTransTooBigPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_FormEchoReply
 Description     : 形成向PC回复的ECHO REPLY
 Input           : pucSrcData ----------- 源报文指针
                   pstDestData ---------- 目的转换结构指针
                   ulIcmpv6HeadOffset --- ICMPv6报头偏移量
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_UINT32  IP_NDSERVER_FormEchoReply
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT8                          *pstDestData,
    VOS_UINT32                          ulDataLen
)
{
    VOS_UINT8                          *pucIpMsg = pucSrcData;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    if (ulDataLen <= IP_IPV6_HEAD_LEN)
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "IP_NDSERVER_FormEchoReply: ulDataLen is too short.", ulDataLen);
        return IP_FAIL;
    }

    /* 根据自身MAC地址生成link-local地址 */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    /*得到目的IPV6地址*/
    IP_MEM_CPY(aucDstIPAddr, pucIpMsg + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    /*得到目的MAC地址*/
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);
    IP_MEM_CPY( aucDstMacAddr,
                pstTeInfo->aucTeLinkLayerAddr,
                IP_MAC_ADDR_LEN);

    /*指向ICMP首部 */
    pucData  = pstDestData + IP_ETHERNET_HEAD_LEN + IP_IPV6_HEAD_LEN;

    /*填写ICMP报文*/
    pucIpMsg += IP_IPV6_HEAD_LEN;
    IP_MEM_CPY(pucData, pucIpMsg,(ulDataLen-IP_IPV6_HEAD_LEN));

    /*ICMP type域*/
    *pucData = IP_ICMPV6_TYPE_ECHOREPLY;
    pucData++;

    /*ICMP code域*/
    *pucData = IP_IPV6_ND_VALID_CODE;
    pucData++;

    /*ICMP 校验和域*/
    *(VOS_UINT16 *)(VOS_VOID*)pucData = 0;

    /*指向IPV6首部*/
    pstDestData += IP_ETHERNET_HEAD_LEN;
    /*填写IPV6头部*/
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr, (ulDataLen-IP_IPV6_HEAD_LEN), pstDestData, IP_HEAD_PROTOCOL_ICMPV6);

    /* 生成ICMPv6报头校验和 */
    if (IP_SUCC != IP_BuildIcmpv6Checksum(pstDestData, IP_IPV6_HEAD_LEN))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_FormEchoReply: Build ICMPv6 Checksum failed.");
        return IP_FAIL;
    }

    /* 设置以太报头 */
    pstDestData -= IP_ETHERNET_HEAD_LEN;
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pstDestData);

    return IP_SUCC;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_EchoRequestMsgProc
 Description     : 处理ECHO REQUEST消息
 Input           : ulIndex  -------------- 处理消息实体索引
                   pucSrcData ------------ IP数据报
                   ulIcmpv6HeadOffset ---- ICMPv6报文头偏移量
 Output          : None
 Return          : VOS_VOID

 History         :
    1.huibo 00159435      2011-12-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_EchoRequestMsgProc
(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT32                          ulDataLen
)
{
    VOS_UINT8                          *pucIpMsg     = pucSrcData;
    VOS_UINT8                          *pucSendBuff  = VOS_NULL_PTR;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    VOS_UINT8                           aucPktAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_EchoRequestMsgProc is entered.");

    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);
    IP_NDSERVER_AddRcvEchoPktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IP_NDSERVER_AddErrEchoPktNum(ulIndex);
        IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_EchoRequestMsgProc: ND Server info flag is invalid!");
        return ;
    }

    IP_MEM_CPY(aucPktAddr, pucIpMsg + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    if (IP_TRUE != IP_NDSERVER_IsSelfIPAddr(ulIndex, aucPktAddr))
    {
        IP_NDSERVER_AddErrEchoPktNum(ulIndex);
        return;
    }

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    if (IP_SUCC != IP_NDSERVER_FormEchoReply(ulIndex,pucIpMsg, pucSendBuff, ulDataLen))
    {
        IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_EchoRequestMsgProc: IP_NDSERVER_FormEchoReply fail!");
        return ;
    }

    /* 将ECHO REPLY发送到PC */
    if (PS_FAIL == Ndis_SendMacFrm(pucSendBuff, ulDataLen+IP_ETHERNET_HEAD_LEN, pstInfoAddr->ucEpsbId))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_EchoRequestMsgProc:Send ECHO REPLY failed.");
        return;
    }

    IP_NDSERVER_AddTransEchoPktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    return;
}

/*****************************************************************************
 Function Name   : NdSer_NdAndEchoPktProc
 Description     : 接收PC发送的ND和ECHO REQUEST报文
 Input           : pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.huibo 00159435      2011-12-09  Draft Enact
    2.h00218138          2013-1-15  DSDA

*****************************************************************************/
VOS_VOID NdSer_NdAndEchoPktProc(VOS_VOID *pRcvMsg)
{
    ADS_NDIS_DATA_IND_STRU             *pstAdsNdisMsg  = (ADS_NDIS_DATA_IND_STRU*)pRcvMsg;
    VOS_UINT32                          ulIcmpv6HeadOffset = IP_NULL;
    IP_ICMPV6_TYPE_ENUM_UINT32          enIcmpv6MsgType = IP_ICMPV6_TYPE_BUTT;
    VOS_UINT32                          ulIndex         = IP_NULL;
    VOS_UINT8                          *pucData;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           ucExRabId;
    IP_NDSERVER_ADDR_INFO_STRU*         pstNDSerAddrInfoTmp;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc is entered.");

    ulDataLen = IMM_ZcGetUsedLen(pstAdsNdisMsg->pstSkBuff);
    pucData   = IMM_ZcGetDataPtr(pstAdsNdisMsg->pstSkBuff);
    if (VOS_NULL_PTR == pucData)
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc, IMM_ZcGetDataPtr return NULL");
        return;
    }

    ucExRabId = ND_FORM_EXEPSID(pstAdsNdisMsg->enModemId, pstAdsNdisMsg->ucRabId);

    if (IP_SUCC != ND_CheckEpsIdValid(ucExRabId))
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc, IMM_ZcGetDataPtr return NULL", ucExRabId);
        return;
    }

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);
    if(ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        /* MT关机再开机后，ND SERVER收到网侧RA前，可能先收到TE的重复地址检测NS ，为了能够处理此类消息，
        此处临时申请一个ND Ser Addr Info*/
        IPND_INFO_LOG1(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc: Get Addr Info, will alloc new addr info for NS msg", pstAdsNdisMsg->ucRabId);
        pstNDSerAddrInfoTmp = NdSer_AllocAddrInfo(&ulIndex);
        if(IP_NULL_PTR == pstNDSerAddrInfoTmp)
        {
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_AllocAddrInfo: return NULL!");
            return;
        }
        pstNDSerAddrInfoTmp->ucValidFlag = IP_FALSE;
    }

    IP_NDSERVER_AddRcvPktTotalNum(ulIndex);

    /* 判断消息是否合法的ND消息 */
    if (IP_TRUE != IP_IsValidNdMsg(pucData, ulDataLen, &ulIcmpv6HeadOffset))
    {
        IP_NDSERVER_AddDiscPktNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc: Invalid ND Msg!");
        return ;
    }

    /* 取ICMPV6消息中的TYPE字段 */
    enIcmpv6MsgType = *(pucData + ulIcmpv6HeadOffset);

    switch(enIcmpv6MsgType)
    {
        case IP_ICMPV6_TYPE_RS:
            IP_NDSERVER_RsMsgProc(ulIndex, pucData, ulIcmpv6HeadOffset);
            break;
        case IP_ICMPV6_TYPE_NS:
            IP_NDSERVER_NsMsgProc(ulIndex, pucData, ulIcmpv6HeadOffset);
            break;
        case IP_ICMPV6_TYPE_NA:
            IP_NDSERVER_NaMsgProc(ulIndex, pucData, ulIcmpv6HeadOffset);
            break;
        case IP_ICMPV6_TYPE_ECHOREQUEST:
            IP_NDSERVER_EchoRequestMsgProc(ulIndex, pucData, ulDataLen);
            break;

        default:
            IP_NDSERVER_AddDiscPktNum(ulIndex);
            IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "NdSer_NdAndEchoPktProc: Ignored IPV6 ND Msg:!", enIcmpv6MsgType);
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_SendDhcp6Reply
 Description     : 组装并发送DHCPV6报文
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h00159435          2011-12-6  Draft Enact

*****************************************************************************/
/*lint -e778*/
/*lint -e572*/
VOS_UINT32  IP_NDSERVER_SendDhcp6Reply
(
    VOS_UINT32                          ulIndex,
    const ND_IP_IPV6_DNS_SER_STRU      *pstDnsSer,
    VOS_UINT8                          *pDhcpInfoReqData,
    VOS_UINT16                          usReqIp6PktLen
)
{
    NDIS_IP6_HDR_STRU                  *pstDhcpReplyIpv6Hdr;
    UDP_HEAD_ST                        *pstDhcpReplyUdpHdr;
    IPV6_DHCP_DNS_OPTION_STRU           stIpv6DhcpDnsOpt;
    IPV6_PKT_DHCP_OPT_HDR_STRU         *pstDhcpClientIdOpt;
    IPV6_PKT_DHCP_OPT_HDR_STRU         *pstDhcpRequestOpt;
    IPV6_PKT_DHCP_DUID_LL_OPT_STRU      stDhcpDuidLLOpt;
    VOS_UINT8                          *pDhcpReplyDhcpHdrOffset;/* 移动指针 */
    VOS_UINT16                          usReplyUdpDataLen;
    VOS_UINT16                          usDhcpReplyPktLen;
    VOS_UINT16                          usDnsOptLen             = 0;
    VOS_UINT16                          usReqDhcpOptLen;
    VOS_UINT16                          usDhcpClientIdOptLen    = 0;
    VOS_UINT16                          usDhcpRequestDnsOptLen  = 0;
    VOS_UINT32                          usDhcpReqOptCodeLoopCnt;
    IPV6_PKT_DHCP_OPT_HDR_STRU         *pstReqDhcpOptHdr;
    VOS_UINT8                           aucSrcIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucSrcMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    VOS_UINT8                           aucDstMacAddr[IP_MAC_ADDR_LEN] = {IP_NULL};
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;
    VOS_UINT8                          *pucSendBuff = VOS_NULL_PTR;
    VOS_UINT8                           ucEpsId;

    if ( usReqIp6PktLen <= ((IP_IPV6_HEAD_LEN + IP_UDP_HEAD_LEN) + IP_UDP_DHCP_HDR_SIZE))
    {
        /*PS_LOG(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_WARNING,
             "NDIS, TTF_NDIS_Ipv6RouterLanEthOutputDhcp6Reply, ERROR, No Option Len!");*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDhcp6Reply, No Option Len!");
        return PS_FAIL;
    }

    /*20160122 V722 coverity --begin*/
    IP_MEM_SET(&stIpv6DhcpDnsOpt, 0, sizeof(IPV6_DHCP_DNS_OPTION_STRU));
    IP_MEM_SET(&stDhcpDuidLLOpt, 0, sizeof(IPV6_PKT_DHCP_DUID_LL_OPT_STRU));
    /*20160122 V722 coverity --end*/

    usReqDhcpOptLen     = usReqIp6PktLen - ((IP_IPV6_HEAD_LEN + IP_UDP_HEAD_LEN) + IP_UDP_DHCP_HDR_SIZE) ;
    usReplyUdpDataLen   = IP_UDP_HEAD_LEN
                            + IP_UDP_DHCP_HDR_SIZE
                            + IP_IPV6_DHCP_OPT_CLIENT_ID_LEN;
    pstReqDhcpOptHdr    = (IPV6_PKT_DHCP_OPT_HDR_STRU *)(VOS_VOID*)(pDhcpInfoReqData
                            + IP_IPV6_HEAD_LEN
                            + IP_UDP_HEAD_LEN
                            + IP_UDP_DHCP_HDR_SIZE);


    /* 获取 DHCP Client ID Option */
    (VOS_VOID)TTF_NDIS_Ipv6GetDhcpOption(pstReqDhcpOptHdr,
                            usReqDhcpOptLen,
                            IP_IPV6_DHCP_OPT_CLIEND_ID,
                            (IPV6_PKT_DHCP_OPT_HDR_STRU **)&pstDhcpClientIdOpt,
                            0 );

    if ( VOS_NULL_PTR != pstDhcpClientIdOpt )
    {
        usDhcpClientIdOptLen    = VOS_NTOHS(pstDhcpClientIdOpt->usDhcpOptLen);
        usReplyUdpDataLen      += (usDhcpClientIdOptLen + 4);
    }

    /* 获取 DHCP Request Option */
    (VOS_VOID)TTF_NDIS_Ipv6GetDhcpOption(pstReqDhcpOptHdr,
                            usReqDhcpOptLen,
                            IP_IPV6_DHCP_OPT_REQUEST,
                            (IPV6_PKT_DHCP_OPT_HDR_STRU **)&pstDhcpRequestOpt,
                            0);

    if ( VOS_NULL_PTR != pstDhcpRequestOpt )
    {
        for (usDhcpReqOptCodeLoopCnt = 0; usDhcpReqOptCodeLoopCnt < (pstDhcpRequestOpt->usDhcpOptLen); usDhcpReqOptCodeLoopCnt +=2 )
        {
            if ( IP_IPV6_DHCP6_OPT_DNS_SERVERS == VOS_NTOHS(*((VOS_UINT16 *)(&(pstDhcpRequestOpt->aucDhcpOptData[usDhcpReqOptCodeLoopCnt])))) )
            {
                usDnsOptLen     = pstDnsSer->ucDnsSerNum;
                if ( (0 == usDnsOptLen) || (IP_IPV6_MAX_DNS_NUM < usDnsOptLen) )
                {
                    /*PS_LOG(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_WARNING,
                         "NDIS, TTF_NDIS_Ipv6RouterLanEthOutputDhcp6Reply, ERROR, DNS Option is err!");*/
                    IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDhcp6Reply, DNS Option is err!");
                    return PS_FAIL;
                }

                usDhcpRequestDnsOptLen  = (VOS_UINT16)(usDnsOptLen * sizeof(NDIS_IP6_ADDR_STRU));
                usReplyUdpDataLen      += (usDhcpRequestDnsOptLen +4);
                break;
            }
        }
    }

    if ( usReplyUdpDataLen <= (IP_UDP_HEAD_LEN + IP_UDP_DHCP_HDR_SIZE + IP_IPV6_DHCP_DUID_LL_OPT_LEN))
    {
        /*PS_LOG(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_ERROR,
             "NDIS, TTF_NDIS_Ipv6RouterLanEthOutputDhcp6Reply, No content need to reply!");*/
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_SendDhcp6Reply, No content need to reply!");
        return PS_SUCC;
    }

    usDhcpReplyPktLen    = IP_IPV6_HEAD_LEN + usReplyUdpDataLen;


    /* 根据自身MAC地址生成link-local地址 */
    IP_MEM_CPY( aucSrcMacAddr,
                (VOS_VOID*)Ndis_GetMacAddr(),
                IP_MAC_ADDR_LEN);
    IP_ProduceIfaceIdFromMacAddr(aucSrcIPAddr, aucSrcMacAddr);
    IP_SetUint16Data(aucSrcIPAddr, IP_IPV6_LINK_LOCAL_PREFIX);

    /*得到目的IPV6地址*/
    IP_MEM_CPY(aucDstIPAddr, pDhcpInfoReqData + IP_IPV6_SRC_ADDR_OFFSET, IP_IPV6_ADDR_LEN);

    /*得到目的MAC地址*/
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);
    IP_MEM_CPY( aucDstMacAddr,
                pstTeInfo->aucTeLinkLayerAddr,
                IP_MAC_ADDR_LEN);

    pucSendBuff = IP_NDSERVER_GET_SENDMSG_BUFFER();
    IP_MEM_SET(pucSendBuff, IP_NULL, IP_IPM_MTU);

    /*指向IPV6首部*/
    pucSendBuff += IP_ETHERNET_HEAD_LEN;

    pstDhcpReplyIpv6Hdr     = (NDIS_IP6_HDR_STRU*)(pucSendBuff);
    pstDhcpReplyUdpHdr      = (UDP_HEAD_ST*)(pstDhcpReplyIpv6Hdr + 1);
    pDhcpReplyDhcpHdrOffset = (VOS_UINT8 *)(pstDhcpReplyUdpHdr+1);

    /*=====================*//* 填充 IP 头 */
    IP_ND_FormIPv6HeaderMsg(aucSrcIPAddr, aucDstIPAddr,
                                  usReplyUdpDataLen, (VOS_UINT8 *)pstDhcpReplyIpv6Hdr, IP_HEAD_PROTOCOL_UDP);

    /*=====================*//* 填充 UDP 头 */
    (VOS_VOID)TTF_NDIS_InputUDPHead((VOS_UINT8 *)pstDhcpReplyUdpHdr,
                            IP_IPV6_DHCP6_UE_PORT,
                            IP_IPV6_DHCP6_PC_PORT,
                            usReplyUdpDataLen);

    /*=====================*//* 填充 DHCP reply 头 */
    (*pDhcpReplyDhcpHdrOffset) = IP_IPV6_DHCP6_TYPE_REPLY;
    pDhcpReplyDhcpHdrOffset   += 1;
    PS_MEM_CPY( pDhcpReplyDhcpHdrOffset,
                            ((pDhcpInfoReqData + IP_IPV6_HEAD_LEN) + IP_UDP_HEAD_LEN) + 1,
                            IP_IPV6_DHCP6_TRANS_ID_LEN );

    pDhcpReplyDhcpHdrOffset   += IP_IPV6_DHCP6_TRANS_ID_LEN;

    /*=====================*//* 填充 DHCP ServerID option (DUID 使用第三种方式即 DUID-LL)*/
    stDhcpDuidLLOpt.usDhcpDuidType      = VOS_HTONS(IP_IPV6_DHCP_DUID_LL_OPT_TYPE);
    stDhcpDuidLLOpt.usDhcpDuidHWType    = VOS_HTONS(IP_IPV6_HW_TYPE);
    PS_MEM_CPY(stDhcpDuidLLOpt.aucLinkLayerAddr,
                            aucSrcMacAddr,
                            IP_IPV6_DHCP_OPT_LINKADDR_SIZE);

    (*(VOS_UINT16 *)pDhcpReplyDhcpHdrOffset) = VOS_HTONS(IP_IPV6_DHCP_OPT_SERVER_ID);
    pDhcpReplyDhcpHdrOffset   += sizeof(VOS_UINT16);
    (*(VOS_UINT16 *)pDhcpReplyDhcpHdrOffset) = VOS_HTONS(IP_IPV6_DHCP_DUID_LL_OPT_LEN);
    pDhcpReplyDhcpHdrOffset   += sizeof(VOS_UINT16);
    PS_MEM_CPY(pDhcpReplyDhcpHdrOffset,
                            (VOS_UINT8 *)(&stDhcpDuidLLOpt),
                            IP_IPV6_DHCP_DUID_LL_OPT_LEN);

    pDhcpReplyDhcpHdrOffset   += IP_IPV6_DHCP_DUID_LL_OPT_LEN;


    /*=====================*//* 填充 DHCP CLient ID option */
    if ( VOS_NULL_PTR != pstDhcpClientIdOpt )
    {
        PS_MEM_CPY(pDhcpReplyDhcpHdrOffset,
                            (VOS_UINT8 *)pstDhcpClientIdOpt,
                            (VOS_NTOHS(pstDhcpClientIdOpt->usDhcpOptLen) + 4));
        pDhcpReplyDhcpHdrOffset += (VOS_NTOHS(pstDhcpClientIdOpt->usDhcpOptLen) + 4);
    }

    /*=====================*//* 填充 DHCP DNS OPTION */
    if ( 0 != usDhcpRequestDnsOptLen )
    {
        stIpv6DhcpDnsOpt.usOptionCode = VOS_HTONS(IP_IPV6_DHCP6_OPT_DNS_SERVERS);
        PS_MEM_CPY(&stIpv6DhcpDnsOpt.astIpv6DNS[0],
                            pstDnsSer->aucPriDnsServer,
                            (sizeof(NDIS_IP6_ADDR_STRU)));

        if (IP_IPV6_MAX_DNS_NUM == usDnsOptLen)
        {
            PS_MEM_CPY(&stIpv6DhcpDnsOpt.astIpv6DNS[1],
                                pstDnsSer->aucSecDnsServer,
                                (sizeof(NDIS_IP6_ADDR_STRU)));
        }
        stIpv6DhcpDnsOpt.usOptionLen  = VOS_HTONS((VOS_UINT16)(IP_IPV6_ADDR_LEN * usDnsOptLen)) ;
        PS_MEM_CPY(pDhcpReplyDhcpHdrOffset,
                            (VOS_UINT8 *)&stIpv6DhcpDnsOpt,
                            (4 + (usDnsOptLen * sizeof(NDIS_IP6_ADDR_STRU))));

        pDhcpReplyDhcpHdrOffset += (4 + (usDnsOptLen * sizeof(NDIS_IP6_ADDR_STRU)));

    }

    pstDhcpReplyUdpHdr->usCheck = TTF_NDIS_Ipv6_CalcCheckSum( (VOS_UINT8 *)pstDhcpReplyUdpHdr,
                            usReplyUdpDataLen,
                            &pstDhcpReplyIpv6Hdr->stSrc,
                            &pstDhcpReplyIpv6Hdr->stDst,
                            IP_HEAD_PROTOCOL_UDP);

    /*指向以太网首部*/
    pucSendBuff -= IP_ETHERNET_HEAD_LEN;
    IP_NDSERVER_FormEtherHeaderMsg(aucSrcMacAddr, aucDstMacAddr, pucSendBuff);

    usDhcpReplyPktLen += IP_ETHERNET_HEAD_LEN;

    IP_NDSERVER_AddTransDhcpv6PktNum(ulIndex);
    IP_NDSERVER_AddTransPktTotalNum(ulIndex);

    ucEpsId = IP_NDSERVER_ADDRINFO_GET_EPSID(ulIndex);

    /* 将DHCPV6 REPLY消息发送到PC */
    return Ndis_SendMacFrm(pucSendBuff, usDhcpReplyPktLen, ucEpsId);
}
/*lint +e778*/
/*lint +e572*/

/*****************************************************************************
 Function Name   : NdSer_DhcpV6PktProc
 Description     : 处理DHCPV6报文
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.h00159435          2011-12-6  Draft Enact
    2.h00218138          2013-1-15  DSDA

*****************************************************************************/
VOS_VOID NdSer_DhcpV6PktProc(VOS_VOID *pRcvMsg)
{
    VOS_UINT16                          usSrcPort;
    VOS_UINT16                          usDstPort;
    VOS_UINT8                           ucMsgType;
    VOS_UINT8                          *pucUdpData;

    ADS_NDIS_DATA_IND_STRU             *pstAdsNdisMsg  = (ADS_NDIS_DATA_IND_STRU*)pRcvMsg;
    VOS_UINT32                          ulIndex         = IP_NULL;
    VOS_UINT8                          *pucData;
    VOS_UINT32                          ulDataLen;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    ND_IP_IPV6_DNS_SER_STRU            *pstDnsSer;
    VOS_UINT8                           ucExRabId;

    IPND_INFO_LOG(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc is entered.");

    ulDataLen = IMM_ZcGetUsedLen(pstAdsNdisMsg->pstSkBuff);
    pucData   = IMM_ZcGetDataPtr(pstAdsNdisMsg->pstSkBuff);
    if (VOS_NULL_PTR == pucData)
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, IMM_ZcGetDataPtr return NULL!");
        return;
    }

    ucExRabId = ND_FORM_EXEPSID(pstAdsNdisMsg->enModemId, pstAdsNdisMsg->ucRabId);

    if (IP_SUCC != ND_CheckEpsIdValid(ucExRabId))
    {
        IPND_ERROR_LOG1(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, ucRabId is Invalid!", ucExRabId);
        return;
    }

    ulIndex = IP_NDSERVER_GET_ADDR_INFO_INDEX(ucExRabId);
    if(ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        IPND_ERROR_LOG2(NDIS_NDSERVER_PID,"NdSer_DhcpV6PktProc: Invalid Input:", ucExRabId, ulIndex);
        return;
    }

    IP_NDSERVER_AddRcvDHCPV6PktNum(ulIndex);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    pucUdpData  = pucData + IP_IPV6_HEAD_LEN;
    usSrcPort   = *(VOS_UINT16 *)(VOS_VOID*)pucUdpData;
    usDstPort   = *(VOS_UINT16 *)(VOS_VOID*)(pucUdpData + 2);

    if ( (IP_IPV6_DHCP6_PC_PORT != VOS_NTOHS(usSrcPort)) || (IP_IPV6_DHCP6_UE_PORT != VOS_NTOHS(usDstPort)) )
    {
        /*PS_LOG2(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "NdSer_DhcpV6PktProc, WARNING, usSrcPort<1>, usDstPort<2> is err.",
            usSrcPort, usDstPort);*/
        IP_NDSERVER_AddErrDhcpv6PktNum(ulIndex);
        IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, usSrcPort, usDstPort is err!", usSrcPort, usDstPort);
        return;
    }

    ucMsgType   = *(pucUdpData + IP_UDP_HEAD_LEN);
    if ( IP_IPV6_DHCP6_INFOR_REQ != ucMsgType )
    {
        /*PS_LOG1(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_INFO,
            "NdSer_DhcpV6PktProc, WARNING, ucMsgType<1> is err.",
            ucMsgType);*/
        IP_NDSERVER_AddErrDhcpv6PktNum(ulIndex);
        IPND_WARNING_LOG1(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, ucMsgType is err!", ucMsgType);
        return;
    }

    pstDnsSer = &(pstInfoAddr->stIpv6NwPara.stDnsSer);

    /* Nd Server没有DNS情况下收到Dhcpv6 information request,丢弃该报文 */
    if ( 0 == pstDnsSer->ucDnsSerNum )
    {
        /*PS_LOG(WUEPS_PID_NDIS, PS_SUBMOD_NULL, PS_PRINT_INFO,
            "NDIS, TTF_NDIS_Ipv6RouterLanEthInputDhcp6InfoReq, WARNING, No DNS information exists");*/
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "NdSer_DhcpV6PktProc, No DNS information exists");
        return;
    }

    (VOS_VOID)IP_NDSERVER_SendDhcp6Reply(ulIndex, pstDnsSer, pucData, (VOS_UINT16)ulDataLen);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_ProcTimerMsgNsExp
 Description    : 发送邻居请求后，等待邻居公告超时
 Input          : pMsg -------- 消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTimerMsgNsExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex      = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    /* 打印进入该函数 */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgNsExp is entered.");

    /* 从消息中取出ND SERVER索引 */
    ulIndex = IP_GetTimerPara(pMsg);
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    if ((IP_TRUE != pstInfoAddr->ucValidFlag)
            || (IP_NDSERVER_TE_ADDR_INEXISTENT == pstInfoAddr->stTeAddrInfo.enTeAddrState))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgNsExp: ND Server state err!");
        return ;
    }

    /* 判定超时次数是否小于规定超时次数 */
    if (pstInfoAddr->stTimerInfo.ucLoopTimes < g_ulNsTimerMaxExpNum)
    {
        /* 发送NS消息到PC */
        if (PS_SUCC != IP_NDSERVER_SendNsMsg(ulIndex, pstTeInfo->aucTeGlobalAddr))
        {
            IP_NDSERVER_AddTransPktFailNum(ulIndex);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgNsExp:Send NS Msg failed.");
        }

        /* 将定时器超时次数加1 */
        pstInfoAddr->stTimerInfo.ucLoopTimes++;

        /* 重启邻居请求定时器 */
        IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_NS);
    }
    else
    {
        /* 清除定时器信息 */
        pstInfoAddr->stTimerInfo.ucLoopTimes = 0;

        /* 如果未完成状态的TE地址不响应地址解析请求，则清除TE地址，重发RA */
        if (IP_NDSERVER_TE_ADDR_INCOMPLETE == pstInfoAddr->stTeAddrInfo.enTeAddrState)
        {
            pstInfoAddr->stTeAddrInfo.enTeAddrState = IP_NDSERVER_TE_ADDR_INEXISTENT;

            /* 发送RA消息到PC */
            if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, VOS_NULL_PTR))
            {
                IP_NDSERVER_AddTransPktFailNum(ulIndex);
                IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgNsExp:Send RA Msg failed.");
            }

            /* 启动路由公告定时器 */
            IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_RA);

            IP_NDSERVER_ClearDlPktQue(ulIndex);          /*清除下行缓存队列中的PKT*/
        }
        else
        {
            /* 启动周期性邻居请求定时器 */
            IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_PERIODIC_NS);
        }
    }

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_ProcTimerMsgPeriodicNsExp
 Description    : 周期性邻居请求超时
 Input          : pMsg -------- 消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTimerMsgPeriodicNsExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex      = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    /* 打印进入该函数 */
    IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgPeriodicNsExp is entered.");

    /* 从消息中取出ND SERVER索引 */
    ulIndex = IP_GetTimerPara(pMsg);
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    if ((IP_TRUE != pstInfoAddr->ucValidFlag)
            || (IP_NDSERVER_TE_ADDR_INEXISTENT == pstInfoAddr->stTeAddrInfo.enTeAddrState))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgPeriodicNsExp: ND Server state err!");
        return ;
    }

    /* 增加周期性发送RA计时，防止Router过期 */
    if (0 == g_aulPeriodicRaTimeCnt[ulIndex]--)
    {
        g_aulPeriodicRaTimeCnt[ulIndex] = g_ulPeriodicRaTimerLen / g_ulPeriodicNsTimerLen;;

        /* 发送RA消息到PC */
        if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, VOS_NULL_PTR))
        {
            IP_NDSERVER_AddTransPktFailNum(ulIndex);
            IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgPeriodicNsExp:Send RA Msg failed.");
        }
    }

    /* 发送NS消息到PC */
    if (PS_SUCC != IP_NDSERVER_SendNsMsg(ulIndex, pstTeInfo->aucTeGlobalAddr))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgPeriodicNsExp:Send NS Msg failed.");
    }

    /* 清除定时器信息 */
    pstInfoAddr->stTimerInfo.ucLoopTimes = 0;
    /* 启动邻居请求定时器 */
    IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_NS);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_ProcTimerMsgPeriodicNsExp
 Description    : 收到重复地址检测后等待定时器超时
 Input          : pMsg -------- 消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTimerMsgFirstNsExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex      = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    IP_NDSERVER_TE_ADDR_INFO_STRU      *pstTeInfo  = IP_NULL_PTR;

    /* 打印进入该函数 */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgFirstNsExp is entered.");

    /* 从消息中取出ND SERVER索引 */
    ulIndex = IP_GetTimerPara(pMsg);
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);
    pstTeInfo = IP_NDSERVER_ADDRINFO_GET_TEINFO(ulIndex);

    if ((IP_TRUE != pstInfoAddr->ucValidFlag)
            || (IP_NDSERVER_TE_ADDR_INEXISTENT == pstInfoAddr->stTeAddrInfo.enTeAddrState))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgFirstNsExp: ND Server state err!");
        return ;
    }

    /* 发送NS消息到PC */
    if (PS_SUCC != IP_NDSERVER_SendNsMsg(ulIndex, pstTeInfo->aucTeGlobalAddr))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgFirstNsExp:Send NS Msg failed.");
    }

    /* 清除定时器信息 */
    pstInfoAddr->stTimerInfo.ucLoopTimes = 0;
    /* 启动邻居请求定时器 */
    IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_NS);

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_ProcTimerMsgRaExp
 Description    : 收到重复地址检测前周期发送路由公告超时
 Input          : pMsg -------- 消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunli 00180715      2011-04-09  Draft Enact

*****************************************************************************/
VOS_VOID IP_NDSERVER_ProcTimerMsgRaExp
(
    const VOS_VOID                     *pMsg
)
{
    VOS_UINT32                          ulIndex      = IP_NULL;
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr  = IP_NULL_PTR;
    VOS_UINT8                           aucDstIPAddr[IP_IPV6_ADDR_LEN] = {IP_NULL};
    IMM_ZC_STRU                        *pstImmZc    = VOS_NULL_PTR;
#if (VOS_OS_VER != VOS_WIN32)
    VOS_UINT8                          *pucData;
    VOS_INT32                           lLockKey;
#endif
    /* 打印进入该函数 */
    IPND_INFO_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp is entered.");

    /* 从消息中取出ND SERVER索引 */
    ulIndex = IP_GetTimerPara(pMsg);
    IP_ASSERT(ulIndex < IP_NDSERVER_ADDRINFO_MAX_NUM);

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    if (IP_TRUE != pstInfoAddr->ucValidFlag)
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp: ND Server state err!");
        return ;
    }

    /* 发送RA消息到PC */
    if (PS_SUCC != IP_NDSERVER_SendRaMsg(ulIndex, VOS_NULL_PTR))
    {
        IP_NDSERVER_AddTransPktFailNum(ulIndex);
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp:Send RA Msg failed.");
    }

    /* 清除定时器信息 */
    pstInfoAddr->stTimerInfo.ucLoopTimes = 0;
    /* 启动路由公告定时器 */
    IP_NDSERVER_TimerStart(ulIndex, IP_ND_SERVER_TIMER_RA);

#if (VOS_OS_VER != VOS_WIN32)
    /************ 下行IP包的目的地址作为NS包的目标地址，进行地址解析 **********/
    /* send NS for Address Resolution */
    lLockKey = VOS_SplIMP();
    if (PS_SUCC != LUP_PeekQueHead(IP_NDSERVER_ADDRINFO_GET_DLPKTQUE(ulIndex), (VOS_VOID**)(&pstImmZc)))
    {
        VOS_Splx(lLockKey);
        return;
    }
    VOS_Splx(lLockKey);

    pucData   = IMM_ZcGetDataPtr(pstImmZc);
    if (VOS_NULL_PTR == pucData)
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp, IMM_ZcGetDataPtr return NULL");
        return;
    }

    /*得到目的IPV6地址，触发NS发送*/
    IP_MEM_CPY(aucDstIPAddr, pucData + IP_IPV6_DST_ADDR_OFFSET, IP_IPV6_ADDR_LEN);
    if (PS_SUCC != IP_NDSERVER_SendNsMsg(ulIndex, aucDstIPAddr))
    {
        IPND_ERROR_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_ProcTimerMsgRaExp, IP_NDSERVER_SendNsMsg return NULL");
        return;
    }
#endif

    return;
}

/*****************************************************************************
 Function Name  : IP_NDSERVER_TimerMsgDistr
 Description    : ND SERVER TIMER消息分发函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : NDSER_TIMER_ENUM_UINT32

 History        :
      1.sunli 00180715     2011-04-02  Draft Enact
*****************************************************************************/
NDSER_TIMER_ENUM_UINT32 IP_NDSERVER_TimerMsgDistr(const VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulIndex         = IP_NULL;
    NDSER_TIMER_ENUM_UINT32             enTimerType     = IP_ND_SERVER_TIMER_BUTT;
    IP_TIMER_STRU                      *pstTimerInfo    = VOS_NULL_PTR;

    /* 从消息中取出ulIndex和enTimerType */
    ulIndex = IP_GetTimerPara(pRcvMsg);
    enTimerType = (NDSER_TIMER_ENUM_UINT32)IP_GetTimerName(pRcvMsg);

    /* 判断合法性 */
    if (IP_FALSE == IP_NDSERVER_IsTimerNameValid(ulIndex, enTimerType))
    {
        /*打印异常信息*/
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerMsgDistr: Invalid Timer Name or Para !");
        return IP_MSG_DISCARD;
    }

    /*根据消息对应的索引号和定时器类型,获取相关联的定时器*/
    pstTimerInfo = IP_NDSERVER_GetTimer(ulIndex, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*打印异常信息*/
        IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerMsgDistr: Get Timer failed.");
        return IP_MSG_DISCARD;
    }

    /* 判断消息类型与定时器类型是否一致 */
    if(enTimerType != pstTimerInfo->ulName)
    {
        /*打印异常信息*/
        IPND_WARNING_LOG2(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerMsgDistr: TimerType not match:", enTimerType, pstTimerInfo->ulName);
        return IP_MSG_DISCARD;
    }

    /*定时器超时处理*/
    switch(enTimerType)
    {
        case IP_ND_SERVER_TIMER_NS:
            IP_NDSERVER_ProcTimerMsgNsExp(pRcvMsg);
            break;
        case IP_ND_SERVER_TIMER_PERIODIC_NS:
            IP_NDSERVER_ProcTimerMsgPeriodicNsExp(pRcvMsg);
            break;
        case IP_ND_SERVER_TIMER_FIRST_NS:
            IP_NDSERVER_ProcTimerMsgFirstNsExp(pRcvMsg);
            break;
        case IP_ND_SERVER_TIMER_RA:
            IP_NDSERVER_ProcTimerMsgRaExp(pRcvMsg);
            break;
        default:
            IPND_WARNING_LOG(NDIS_NDSERVER_PID, "IP_NDSERVER_TimerMsgDistr: Illegal Timer Type!");
            break;
    }

    return IP_MSG_HANDLED;
}

/*****************************************************************************
 函 数 名  : APP_NdServer_PidMsgProc
 功能描述  : PP NDIS上行PID消息处理函数
 输入参数  : MsgBlock* pMsgBlock
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月9日
    作    者   : h00159435
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID APP_NdServer_PidMsgProc(const MsgBlock *pRcvMsg)
{
    if (VOS_NULL_PTR == pRcvMsg)
    {
        vos_printf("Error:APP_Ndis_DLPidMsgProc Parameter pRcvMsg is NULL!");
        return ;
    }
    switch (pRcvMsg->ulSenderPid)
    {
        case DOPRA_PID_TIMER:
            (VOS_VOID)IP_NDSERVER_TimerMsgDistr(pRcvMsg);
            break;
        default:
            break;
    }

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_CmdHelp
 Description     : IP NDSERVER模块命令显示
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact
*****************************************************************************/
VOS_VOID  IP_NDSERVER_CmdHelp( VOS_VOID )
{
    vos_printf("\r\n");
    vos_printf("********************** IP NDSERVER 软调命令列表 *********************\r\n");
    vos_printf("%-30s : %s\r\n","IP_NDSERVER_ShowLocalNwParamInfo","显示本地保存的网络参数信息");
    vos_printf("%-30s : %s\r\n","IP_NDSERVER_ShowAddrInfo(index)","显示某实体地址参数信息(0)");
    vos_printf("%-30s : %s\r\n","IP_NDSERVER_ShowStatInfo(index)","显示某实体报文统计信息(0)");
    vos_printf("*******************************************************************\r\n");
    vos_printf("\r\n");

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_ShowLocalNwParamInfo
 Description     : 显示本地保存的网络参数信息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_ShowLocalNwParamInfo( VOS_VOID )
{
    vos_printf("************************本地保存的网络参数信息***********************\r\n");
    vos_printf("管理地址配置标识: %d\r\n",g_ucMFlag);
    vos_printf("其他有状态配置标识: %d\r\n",g_ucOFlag);
    vos_printf("路由器生存期(秒): %d\r\n",g_usRouterLifetime);
    vos_printf("可达时间(毫秒): %d\r\n",g_ulReachableTime);
    vos_printf("重发定时器(毫秒): %d\r\n",g_ulRetransTimer);
    vos_printf("邻居请求定时器时长(毫秒): %d\r\n",g_ulNsTimerLen);
    vos_printf("邻居请求最大超时次数: %d\r\n",g_ulNsTimerMaxExpNum);
    vos_printf("周期性邻居请求定时器时长(毫秒): %d\r\n",g_ulPeriodicNsTimerLen);
    vos_printf("周期性路由公告定时器时长(毫秒): %d\r\n",g_ulPeriodicRaTimerLen);
    vos_printf("收到重复地址检测后等待的定时器时长(毫秒): %d\r\n",g_ulFirstNsTimerLen);
    vos_printf("收到重复地址检测前路由公告定时器时长(毫秒): %d\r\n",g_ulRaTimerLen);

    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_ShowAddrInfo
 Description     : 显示某实体地址参数信息
 Input           : ulIndex --- 实体索引
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_ShowAddrInfo( VOS_UINT32 ulIndex )
{
    IP_NDSERVER_ADDR_INFO_STRU         *pstInfoAddr = IP_NULL_PTR;
    VOS_UINT32                          ulCnt       = IP_NULL;
    VOS_UINT32                          ulTmp       = IP_NULL;

    if (ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        ulTmp = IP_NDSERVER_ADDRINFO_MAX_NUM;
        vos_printf("IP_NDSERVER_ShowAddrInfo:输入参数的范围:0-%d\r\n", ulTmp-1);
        return ;
    }

    pstInfoAddr = IP_NDSERVER_ADDRINFO_GET_ADDR(ulIndex);

    vos_printf("**************************ND SERVER实体信息(%d)*************************\r\n", ulIndex);
    vos_printf("有效标志: %d\r\n",pstInfoAddr->ucValidFlag);
    vos_printf("承载号: %d\r\n",pstInfoAddr->ucEpsbId);

    vos_printf("************网络配置参数************\r\n");
    vos_printf("MTU: %d\r\n",pstInfoAddr->stIpv6NwPara.ulBitOpMtu?pstInfoAddr->stIpv6NwPara.ulMtu:0);
    vos_printf("当前跳限制: %d\r\n",pstInfoAddr->stIpv6NwPara.ucCurHopLimit);
    vos_printf("接口ID: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[0],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[1],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[2],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[3],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[4],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[5],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[6],
                                pstInfoAddr->stIpv6NwPara.aucInterfaceId[7]);

    vos_printf("************前缀列表************\r\n");
    vos_printf("前缀数量: %d\r\n",pstInfoAddr->stIpv6NwPara.ulPrefixNum);
    for (ulCnt = 0; ulCnt < pstInfoAddr->stIpv6NwPara.ulPrefixNum; ulCnt++)
    {
        vos_printf("前缀长度: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulBitPrefixLen);
        vos_printf("自治标志: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulBitA);
        vos_printf("链路上标志: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulBitL);
        vos_printf("有效生存期: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulValidLifeTime);
        vos_printf("选用生存期: %d\r\n",pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].ulPreferredLifeTime);
        vos_printf("前缀: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[0],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[1],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[2],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[3],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[4],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[5],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[6],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[7],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[8],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[9],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[10],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[11],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[12],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[13],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[14],
                                    pstInfoAddr->stIpv6NwPara.astPrefixList[ulCnt].aucPrefix[15]);
    }

    vos_printf("************DNS SERVER列表************\r\n");
    vos_printf("DNS SERVER数量: %d\r\n",pstInfoAddr->stIpv6NwPara.stDnsSer.ucDnsSerNum);
    if (pstInfoAddr->stIpv6NwPara.stDnsSer.ucDnsSerNum >= 1)
    {
        vos_printf("Prime DNS SERVER: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[0],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[1],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[2],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[3],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[4],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[5],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[6],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[7],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[8],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[9],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[10],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[11],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[12],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[13],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[14],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucPriDnsServer[15]);
    }
    if (pstInfoAddr->stIpv6NwPara.stDnsSer.ucDnsSerNum >= 2)
    {
        vos_printf("Second DNS SERVER: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[0],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[1],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[2],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[3],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[4],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[5],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[6],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[7],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[8],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[9],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[10],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[11],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[12],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[13],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[14],
                                    pstInfoAddr->stIpv6NwPara.stDnsSer.aucSecDnsServer[15]);
    }
    vos_printf("************SIP SERVER列表************\r\n");
    vos_printf("SIP SERVER数量: %d\r\n",pstInfoAddr->stIpv6NwPara.stSipSer.ucSipSerNum);
    if (pstInfoAddr->stIpv6NwPara.stSipSer.ucSipSerNum >= 1)
    {
        vos_printf("Prime SIP SERVER: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[0],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[1],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[2],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[3],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[4],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[5],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[6],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[7],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[8],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[9],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[10],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[11],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[12],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[13],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[14],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucPriSipServer[15]);
    }
    if (pstInfoAddr->stIpv6NwPara.stSipSer.ucSipSerNum >= 2)
    {
        vos_printf("Second SIP SERVER: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[0],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[1],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[2],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[3],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[4],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[5],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[6],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[7],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[8],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[9],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[10],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[11],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[12],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[13],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[14],
                                    pstInfoAddr->stIpv6NwPara.stSipSer.aucSecSipServer[15]);
    }

    vos_printf("************TE地址信息************\r\n");
    vos_printf("TE地址状态: %d\r\n",pstInfoAddr->stTeAddrInfo.enTeAddrState);
    vos_printf("全球地址: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[0],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[1],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[2],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[3],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[4],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[5],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[6],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[7],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[8],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[9],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[10],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[11],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[12],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[13],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[14],
                                pstInfoAddr->stTeAddrInfo.aucTeGlobalAddr[15]);
    vos_printf("链路层地址: %02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[0],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[1],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[2],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[3],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[4],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLayerAddr[5]);
    vos_printf("链路本地地址: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[0],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[1],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[2],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[3],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[4],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[5],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[6],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[7],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[8],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[9],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[10],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[11],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[12],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[13],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[14],
                                pstInfoAddr->stTeAddrInfo.aucTeLinkLocalAddr[15]);

    vos_printf("************定时器状态************\r\n");
    vos_printf("系统定时器地址: %p\r\n",pstInfoAddr->stTimerInfo.hTm);
    vos_printf("定时器类型: %d\r\n",pstInfoAddr->stTimerInfo.ulName);
    vos_printf("定时器超时次数: %d\r\n",pstInfoAddr->stTimerInfo.ucLoopTimes);
    vos_printf("周期性路由公告时间计数: %d\r\n",g_aulPeriodicRaTimeCnt[ulIndex]);

    vos_printf("************单板侧信息************\r\n");
    vos_printf("单板侧本地链路地址: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                                pstInfoAddr->aucUeLinkLocalAddr[0],
                                pstInfoAddr->aucUeLinkLocalAddr[1],
                                pstInfoAddr->aucUeLinkLocalAddr[2],
                                pstInfoAddr->aucUeLinkLocalAddr[3],
                                pstInfoAddr->aucUeLinkLocalAddr[4],
                                pstInfoAddr->aucUeLinkLocalAddr[5],
                                pstInfoAddr->aucUeLinkLocalAddr[6],
                                pstInfoAddr->aucUeLinkLocalAddr[7],
                                pstInfoAddr->aucUeLinkLocalAddr[8],
                                pstInfoAddr->aucUeLinkLocalAddr[9],
                                pstInfoAddr->aucUeLinkLocalAddr[10],
                                pstInfoAddr->aucUeLinkLocalAddr[11],
                                pstInfoAddr->aucUeLinkLocalAddr[12],
                                pstInfoAddr->aucUeLinkLocalAddr[13],
                                pstInfoAddr->aucUeLinkLocalAddr[14],
                                pstInfoAddr->aucUeLinkLocalAddr[15]);
    return;
}

/*****************************************************************************
 Function Name   : IP_NDSERVER_ShowStatInfo
 Description     : 显示报文统计信息
 Input           : ulIndex --- 实体索引
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunli 00180715      2011-04-11  Draft Enact

*****************************************************************************/
VOS_VOID  IP_NDSERVER_ShowStatInfo( VOS_UINT32 ulIndex )
{
    IP_NDSERVER_PACKET_STATISTICS_INFO_STRU    *pstPktStatInfo = IP_NULL_PTR;
    VOS_UINT32                                  ulTmp          = IP_NULL;

    if (ulIndex >= IP_NDSERVER_ADDRINFO_MAX_NUM)
    {
        ulTmp = IP_NDSERVER_ADDRINFO_MAX_NUM;
        vos_printf("IP_NDSERVER_ShowStatInfo:输入参数的范围:0-%d\r\n", ulTmp-1);
        return ;
    }

    pstPktStatInfo = IP_NDSERVER_GET_STATINFO_ADDR(ulIndex);

    vos_printf("****************************报文统计信息(%d)****************************\r\n", ulIndex);
    vos_printf("收到报文总数:           %d\r\n", pstPktStatInfo->ulRcvPktTotalNum);
    vos_printf("丢弃报文数:             %d\r\n", pstPktStatInfo->ulDiscPktNum);
    vos_printf("收到NS报文数:           %d\r\n", pstPktStatInfo->ulRcvNsPktNum);
    vos_printf("收到NA报文数:           %d\r\n", pstPktStatInfo->ulRcvNaPktNum);
    vos_printf("收到RS报文数:           %d\r\n", pstPktStatInfo->ulRcvRsPktNum);
    vos_printf("收到ECHO REQ报文数:     %d\r\n", pstPktStatInfo->ulRcvEchoPktNum);
    vos_printf("收到IPV6超长报文数:     %d\r\n", pstPktStatInfo->ulRcvTooBigPktNum);
    vos_printf("收到DHCPV6报文数:       %d\r\n", pstPktStatInfo->ulRcvDhcpv6PktNum);
    vos_printf("收到错误NS报文数:       %d\r\n", pstPktStatInfo->ulErrNsPktNum);
    vos_printf("收到错误NA报文数:       %d\r\n", pstPktStatInfo->ulErrNaPktNum);
    vos_printf("收到错误RS报文数:       %d\r\n", pstPktStatInfo->ulErrRsPktNum);
    vos_printf("收到错误ECHO REQ报文数: %d\r\n", pstPktStatInfo->ulErrEchoPktNum);
    vos_printf("收到错误IPV6超长报文数: %d\r\n", pstPktStatInfo->ulErrTooBigPktNum);
    vos_printf("收到错误DHCPV6报文数:   %d\r\n", pstPktStatInfo->ulErrDhcpv6PktNum);
    vos_printf("发送报文总数:           %d\r\n", pstPktStatInfo->ulTransPktTotalNum);
    vos_printf("发送报文失败数:         %d\r\n", pstPktStatInfo->ulTransPktFailNum);
    vos_printf("发送NS报文数:           %d\r\n", pstPktStatInfo->ulTransNsPktNum);
    vos_printf("发送NA报文数:           %d\r\n", pstPktStatInfo->ulTransNaPktNum);
    vos_printf("发送RA报文数:           %d\r\n", pstPktStatInfo->ulTransRaPktNum);
    vos_printf("发送ECHO REPLY报文数:   %d\r\n", pstPktStatInfo->ulTransEchoPktNum);
    vos_printf("发送超长包响应报文数:   %d\r\n", pstPktStatInfo->ulTransTooBigPktNum);
    vos_printf("发送DHCPV6 REPLY报文数: %d\r\n", pstPktStatInfo->ulTransDhcpv6PktNum);
    vos_printf("下行IP包发送时PC MAC地址无效的统计量: %d\r\n", pstPktStatInfo->ulMacInvalidPktNum);
    vos_printf("下行成功缓存的IP包个数:               %d\r\n", pstPktStatInfo->ulEnquePktNum);
    vos_printf("下行成功发送缓存的IP包个数:           %d\r\n", pstPktStatInfo->ulSendQuePktNum);

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


