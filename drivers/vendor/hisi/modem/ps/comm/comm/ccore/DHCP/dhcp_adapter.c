/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcp_adapter.c
  版 本 号   : 初稿
  作    者   : w00316385
  生成日期   : 2015年04月25日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2015年04月25日
    作    者   : w00316385
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "v_int.h"
#include "VosTaskPrioDef.h"
#include "dhcp_adapter.h"
#include "dhcpc_dbg.h"
#include "dhcpv6_def.h"
#include "dhcpv6c_pkt.h"
#include "dhcpv6c_fsm.h"
#include "TTFMem.h"
#include "TtfDrvInterface.h"
#include "CdsDhcpInterface.h"
#include "AdsDhcpInterface.h"
#include "DhcpLog.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID          PS_FILE_ID_DHCP_ADAPTER_C


/*****************************************************************************
  2 全局变量声明
*****************************************************************************/

/* DHCP的上下文信息 */
DHCP_ENTITY_STRU                        g_stDhcpEntity[DHCP_ENTITY_MAX_NUM + 1];
VOS_UINT32                              g_aulDhcpEntityCnt[MODEM_ID_BUTT] = {0};
VOS_UINT8                               g_ucDhcpv6cSendBuff[DHCPV6C_SEND_MSG_MAXLEN] = {0};
VOS_UINT32                              g_ulDhcpRtrSolicitationInterval   = 1000; /* milliseconds */
VOS_UINT32                              g_ulDhcpMaxRtrRSTimes             = 15;
VOS_UINT8                               g_aucDhcpAllRoutersMulticaseAddr[IP_IPV6_ADDR_LEN] =
                                                           {0xff, 0x02, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x02};


CTTF_DHCP_TRACE_DATA_STRU               g_stDhcpTraceData;


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : DHCP_StartFilter
 功能描述  : 通知CDS开启过滤规则
 输入参数  : VOS_UINT16 usModemId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月18日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_StartFilter(VOS_UINT16 usModemId)
{
    DHCP_CDS_START_FILTER_REQ_STRU    *pstStartFilterReq;


    /*入参判断*/
    if (usModemId >= MODEM_ID_BUTT)
    {
        DHCP_WARNING_LOG1("DHCP_StartFilter: Input ModemId Error.\n",usModemId);
        return;
    }

    /* 申请消息内存 */
    pstStartFilterReq = (DHCP_CDS_START_FILTER_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_DHCP, sizeof(DHCP_CDS_START_FILTER_REQ_STRU));
    if (VOS_NULL_PTR == pstStartFilterReq)
    {
        DHCP_WARNING_LOG("Alloc Get start filter req Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstStartFilterReq + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(DHCP_CDS_START_FILTER_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    pstStartFilterReq->enMsgId               = ID_DHCP_CDS_START_FILTER_REQ;
    pstStartFilterReq->enModemId             = usModemId;
    pstStartFilterReq->ulReceiverPid         = UEPS_PID_CDS;
    pstStartFilterReq->ulReceiverCpuId       = VOS_LOCAL_CPUID;

    /* 发送响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_DHCP, pstStartFilterReq))
    {
        DHCP_WARNING_LOG("Warning:Send ID_DHCP_CDS_START_FILTER_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_StopFilter
 功能描述  : 通知CDS关闭过滤规则
 输入参数  : VOS_UINT16 usModemId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月18日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_StopFilter(VOS_UINT16 usModemId)
{
    DHCP_CDS_STOP_FILTER_REQ_STRU     *pstStopFilterReq;


    /*入参判断*/
    if (usModemId >= MODEM_ID_BUTT)
    {
        DHCP_WARNING_LOG1("DHCP_StopFilter: Input ModemId Error.\n",usModemId);
        return;
    }

    /* 申请消息内存 */
    pstStopFilterReq = (DHCP_CDS_STOP_FILTER_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_DHCP, sizeof(DHCP_CDS_STOP_FILTER_REQ_STRU));
    if (VOS_NULL_PTR == pstStopFilterReq)
    {
        DHCP_WARNING_LOG("Alloc Get stop filter req Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstStopFilterReq + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(DHCP_CDS_STOP_FILTER_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    pstStopFilterReq->enMsgId               = ID_DHCP_CDS_STOP_FILTER_REQ;
    pstStopFilterReq->enModemId             = usModemId;
    pstStopFilterReq->ulReceiverPid         = UEPS_PID_CDS;
    pstStopFilterReq->ulReceiverCpuId       = VOS_LOCAL_CPUID;

    /* 发送响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_DHCP, pstStopFilterReq))
    {
        DHCP_WARNING_LOG("Warning:Send ID_DHCP_CDS_STOP_FILTER_REQ msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_IPUnit16Sum
 功能描述  : 计算16bit SUM
 输入参数  : VOS_UINT8 *pucData
             VOS_UINT32 ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DHCP_IPUnit16Sum(const VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT32    ulCheckSum  = 0;
    VOS_UINT16   *pBuffer;


    if (VOS_NULL_PTR == pucData)
    {
        DHCP_WARNING_LOG("pucData is NULL.\n");
        return 0;
    }

    if (0 == ulLen)
    {
        DHCP_WARNING_LOG("ulLen is 0.\n");
        return 0;
    }

    pBuffer = (VOS_UINT16 *)(VOS_VOID*)pucData;

    while(ulLen > 1)
    {
        ulCheckSum += *(pBuffer ++);
        ulLen      -= 2;
    }

    if (0 != ulLen)
    {
        ulCheckSum += *(VOS_UINT8*)pBuffer;
    }

    return ulCheckSum;
}

/*****************************************************************************
 函 数 名  : DHCP_IPv6Checksum
 功能描述  : 基于pseduo-header和upper-layer protocal计算checksum
 输入参数  : VOS_VOID                *pucPseduoHeader
             VOS_UINT8               *pucData
             VOS_UINT32              ulLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 DHCP_IPv6Checksum
(
    const VOS_VOID                     *pucPseduoHeader,
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulCheckSum  = 0;


    if (VOS_NULL_PTR == pucPseduoHeader)
    {
        DHCP_WARNING_LOG("pucPseduoHeader is NULL.\n");
        return 0;
    }

    if (VOS_NULL_PTR == pucData)
    {
        DHCP_WARNING_LOG("pucData is NULL.\n");
        return 0;
    }

    if (0 == ulLen)
    {
        DHCP_WARNING_LOG("ulLen is 0.\n");
        return 0;
    }

    /* pseduo-header求和 */
    ulCheckSum += DHCP_IPUnit16Sum(pucPseduoHeader, sizeof(IPV6_PSEDUOHEADER_STRU));

    /* IPV6 Upper-layer package求和 */
    ulCheckSum += DHCP_IPUnit16Sum(pucData, ulLen);

    while(ulCheckSum >> 16)
    {
        ulCheckSum  = (ulCheckSum >> 16) + (ulCheckSum & 0xffff);
    }

    return (VOS_UINT16)(~ulCheckSum);

}

/*****************************************************************************
 函 数 名  : DHCP_BuildLinkLocalAddr
 功能描述  : 构造link-local地址
 输入参数  : VOS_UINT8 *pucLinkLocalAddr
             VOS_UINT8 *pucIfId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_BuildLinkLocalAddr
(
    VOS_UINT8                          *pucLinkLocalAddr,
    const VOS_UINT8                    *pucIfId
)
{
    /* 构造link-local address */
    DHCP_MemZero(pucLinkLocalAddr, DHCP_IPV6_IF_OFFSET + DHCP_IPV6_IF_LEN);
    IP_SetUint16Data(pucLinkLocalAddr, IP_IPV6_LINK_LOCAL_PREFIX);
    VOS_MemCpy(&pucLinkLocalAddr[DHCP_IPV6_IF_OFFSET], pucIfId, DHCP_IPV6_IF_LEN);
}

/*****************************************************************************
 函 数 名  : DHCP_StopTimer
 功能描述  : stop Timer
 输入参数  : DHCP_TIMER_STRU    *pstTimerInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_StopTimer
(
    DHCP_TIMER_STRU                    *pstTimerInfo
)
{
    if (VOS_NULL_PTR != pstTimerInfo->hTm)
    {
        if(VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTm)))
        {
            DHCP_WARNING_LOG("DHCP_StopTimer: Error to stop RealTimer");
        }
        pstTimerInfo->hTm = VOS_NULL_PTR;
    }
}

/*****************************************************************************
 函 数 名  : DHCP_ReleaseResendResourse
 功能描述  : 释放重传相关信息
 输入参数  : DHCP_ENTITY_STRU *pstDhcpEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_ReleaseResendResourse
(
    DHCP_ENTITY_STRU                   *pstDhcpEntity
)
{
    /* 停止定时器 */
    DHCP_StopTimer(&pstDhcpEntity->stTimerInfo);
    pstDhcpEntity->stTimerInfo.ucLoopTimes = 0;

    pstDhcpEntity->enMsgType = ID_TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_BUTT;

    /* 释放重发缓存消息内存 */
    if(VOS_NULL_PTR != pstDhcpEntity->stIpSndNwMsg.pucSendMsg)
    {
        DHCP_Free(MSPS_PID_DHCP,pstDhcpEntity->stIpSndNwMsg.pucSendMsg);
        pstDhcpEntity->stIpSndNwMsg.pucSendMsg = VOS_NULL_PTR;

    }
}

/*****************************************************************************
 函 数 名  : DHCP_GetTimerLen
 功能描述  : 获取定时器时长
 输入参数  : DHCP_TIMER_ENUM_UINT32     enTimerType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  DHCP_GetTimerLen
(
    DHCP_TIMER_ENUM_UINT32              enTimerType
)
{
    VOS_UINT32                          ulTimerLen = 0;

    /*根据定时器不同类型，定时器时长不同*/
    switch(enTimerType)
    {
        case DHCP_TIMER_RS:
            ulTimerLen = g_ulDhcpRtrSolicitationInterval;
            break;
        default :
            break;
    }

    return ulTimerLen;
}

/*****************************************************************************
 函 数 名  : DHCP_CheckEpsIdValid
 功能描述  : 检查EpsId
 输入参数  : VOS_UINT8 ucExEpsId 高2bit为ModemID，低6bit为EpsbId。
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月10日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DHCP_CheckEpsIdValid(VOS_UINT8 ucExEpsId)
{
    VOS_UINT8                           ucEpsId;
    VOS_UINT16                          usModemId;

    usModemId = DHCP_GET_MODEMID_FROM_EXEPSID(ucExEpsId);
    if (usModemId >= MODEM_ID_BUTT)
    {
        return VOS_ERR;
    }

    ucEpsId = DHCP_GET_EPSID_FROM_EXEPSID(ucExEpsId);
    if ((ucEpsId < DHCP_MIN_EPSB_ID) || (ucEpsId > DHCP_MAX_EPSB_ID))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCP_BuildUdpHeader
 功能描述  : 为DHCPv6报文设置初始UDP头，checksum 置0
 输入参数  : VOS_UINT8    *pucUdp
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月10日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_BuildDhcpv6UdpHeader
(
    VOS_UINT8                          *pucUdp,
    VOS_UINT16                          usUdpLen
)
{
    VOS_UINT16                          usInitChecksum = IP_UDP_INIT_CHECKSUM;

    /* 设置UDP消息中的Source Port字段 */
    IP_SetUint16Data(pucUdp + IP_UDP_SOURCE_PORT_OFFSET, DHCPV6_CLIENT_UDP_PORT);

    /* 设置UDP消息中的Dest Port字段 */
    IP_SetUint16Data(pucUdp + IP_UDP_DEST_PORT_OFFSET, DHCPV6_SERVER_UDP_PORT);

    /* 设置UDP消息中的Length字段 */
    IP_SetUint16Data(pucUdp + IP_UDP_LEN_OFFSET, usUdpLen);

    /* 设置UDP消息中的checksum字段 */
    IP_SetUint16Data(pucUdp + IP_UDP_CHECKSUM_OFFSET, usInitChecksum);
}

/*****************************************************************************
 函 数 名  : DHCP_BuildIPv6Header
 功能描述  : 为ICMPv6消息构造IP header，不支持扩展头
 输入参数  :
             VOS_UINT8                  *pucIpv6
             IPV6_PSEDUOHEADER_STRU     *pstPseduoHeader
             VOS_UINT8                  *pucInterfaceId
             VOS_UINT32                 ulUpperLength
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_BuildIPv6Header
(
    VOS_UINT8                          *pucIpv6,
    IPV6_PSEDUOHEADER_STRU             *pstPseduoHeader,
    const VOS_UINT8                    *pucInterfaceId,
    VOS_UINT32                          ulUpperLength
)
{
    VOS_UINT8                           aucLinkLocalAddr[IP_IPV6_ADDR_LEN] = {0};

    /* 构造link-local address */
    DHCP_BuildLinkLocalAddr(aucLinkLocalAddr, pucInterfaceId);

    /* 设置IP版本号 */
    *pucIpv6    = IP_VERSION_6 << IP_BITMOVE_4;
    *pucIpv6   += (VOS_UINT8)((IP_IPV6_TRAFFIC_CLASS & 0xF0) >> IP_BITMOVE_4);

    /* 设置Payload，没有扩展头 */
    IP_SetUint16Data(pucIpv6 + IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET, ulUpperLength);

    /* 设置next header */
    *(pucIpv6 + IP_IPV6_BASIC_HEAD_NEXT_HEAD_OFFSET) = IPV6_UDP_PRO;

    /* Hop Limit 255 */
    *(pucIpv6 + IP_IPV6_BASIC_HOP_LIMIT_OFFSET) = IP_IPV6_DHCP_HOP_LIMIT;

    (VOS_VOID)VOS_MemCpy(pucIpv6 + IP_IPV6_SRC_ADDR_OFFSET, aucLinkLocalAddr, IP_IPV6_ADDR_LEN);
    (VOS_VOID)VOS_MemCpy(pucIpv6 + IP_IPV6_DST_ADDR_OFFSET, g_aucDhcpAllRoutersMulticaseAddr, IP_IPV6_ADDR_LEN);

    /* 为计算checksum构造pseudo-header */
    PS_MEM_CPY(pstPseduoHeader->aucIPSrc, aucLinkLocalAddr, IP_IPV6_ADDR_LEN);
    PS_MEM_CPY(pstPseduoHeader->aucIPDes, g_aucDhcpAllRoutersMulticaseAddr, IP_IPV6_ADDR_LEN);
    IP_SetUint32Data((VOS_UINT8*)&pstPseduoHeader->ulUpperLength, ulUpperLength);
    pstPseduoHeader->ucNextHead = IPV6_UDP_PRO;

}

/*****************************************************************************
 函 数 名  : DHCP_GetEntity
 功能描述  : 根据EpsbId查找DHCP实体
 输入参数  : VOS_UINT8 ucEpsbId
 输出参数  : 无
 返 回 值  : DHCP_ENTITY_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
DHCP_ENTITY_STRU* DHCP_GetEntity
(
    VOS_UINT8                           ucEpsbId
)
{
    VOS_UINT32                          ulIndex = 0;


    /* 查询是否已存在相应Entity */
    do{
        if((0 != g_stDhcpEntity[ulIndex].ucflag) && (ucEpsbId == g_stDhcpEntity[ulIndex].ucEpsbId))
        {
            /*找到相应实体*/
            return &g_stDhcpEntity[ulIndex];
        }

    }while((++ulIndex) < DHCP_ENTITY_MAX_NUM);

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : DHCP_AllocEntity
 功能描述  : 分配实体，不做实体重复性判断
 输入参数  : VOS_UINT8 ucEpsbId
 输出参数  : 无
 返 回 值  : DHCP_ENTITY_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
DHCP_ENTITY_STRU* DHCP_AllocEntity(VOS_UINT8  ucExRabId)
{
    VOS_UINT32                          ulIndex = 0;


    /* 查询是否存在空闲Enity */
    do{
        if(0 == g_stDhcpEntity[ulIndex].ucflag)
        {
            /*找到空闲实体*/
            (VOS_VOID)VOS_MemSet(&g_stDhcpEntity[ulIndex], 0, sizeof(DHCP_ENTITY_STRU));

            g_stDhcpEntity[ulIndex].ucflag = 1;
            g_stDhcpEntity[ulIndex].ucEpsbId = ucExRabId;
            g_stDhcpEntity[ulIndex].ucWaitRspTimeOutNum = 0;
            g_stDhcpEntity[ulIndex].ucResendTimeout     = 1;
            /*增加实体个数*/
            DHCP_AddEntityNum(DHCP_GET_MODEMID_FROM_EXEPSID(ucExRabId));

            return &g_stDhcpEntity[ulIndex];
        }

    }while(++ulIndex < DHCP_ENTITY_MAX_NUM);

    return VOS_NULL_PTR;

}

/*****************************************************************************
 函 数 名  : DHCP_RelEntity
 功能描述  : 释放DHCP实体
 输入参数  : DHCP_ENTITY_STRU *pstDhcpEntity
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_RelEntity
(
    DHCP_ENTITY_STRU                   *pstDhcpEntity
)
{
    if (VOS_NULL_PTR == pstDhcpEntity)
    {
        DHCP_WARNING_LOG("pstDhcpEntity is NULL.");
        return;
    }
    if (0 == pstDhcpEntity->ucflag)
    {
        DHCP_WARNING_LOG("pstDhcpEntity->ucflag is 0.");
        return;
    }

    /*减小实体计数*/
    DHCP_SubEntityNum(DHCP_GET_MODEMID_FROM_EXEPSID(pstDhcpEntity->ucEpsbId));

    /* 释放重传资源 */
    DHCP_ReleaseResendResourse(pstDhcpEntity);

    VOS_MemSet(pstDhcpEntity, 0, sizeof(DHCP_ENTITY_STRU));
    pstDhcpEntity->ucflag = 0;
    pstDhcpEntity->enMsgType = ID_TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_BUTT;

    return;
}


/*****************************************************************************
 函 数 名  : DHCP_InitEntityNum
 功能描述  : 重新初始化DHCP实体计数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_InitEntityNum(VOS_VOID)
{
    (VOS_VOID)VOS_MemSet(g_aulDhcpEntityCnt, 0, sizeof(g_aulDhcpEntityCnt));
    return;
}

/*****************************************************************************
 函 数 名  : DHCP_AddEntityNum
 功能描述  : 增加对应ModemId的DHCP实体计数
 输入参数  : VOS_UINT16 usModemId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_AddEntityNum(VOS_UINT16 usModemId)
{
    if (usModemId >= MODEM_ID_BUTT)
    {
        DHCP_WARNING_LOG1("DHCP_AddEntityNum: Input ModemId Error.",usModemId);
        return;
    }

    g_aulDhcpEntityCnt[usModemId]++;

    if (1 == g_aulDhcpEntityCnt[usModemId])
    {
        DHCP_StartFilter(usModemId);
        DHCP_INFO_LOG1("MSPS_PID_DHCP: Start IPv6 Filter.",usModemId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_SubEntityNum
 功能描述  : 减小对应ModemId的DHCP实体计数
 输入参数  : VOS_UINT16 usModemId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_SubEntityNum(VOS_UINT16 usModemId)
{
    if (usModemId >= MODEM_ID_BUTT)
    {
        DHCP_WARNING_LOG1("DHCP_SubEntityNum: Input ModemId Error.",usModemId);
        return;
    }

    if (0 == g_aulDhcpEntityCnt[usModemId])
    {
        DHCP_WARNING_LOG1("DHCP_SubEntityNum: Ative ND Entity Already 0.",usModemId);
        return;
    }

    g_aulDhcpEntityCnt[usModemId]--;

    if (0 == g_aulDhcpEntityCnt[usModemId])
    {
        DHCP_StopFilter(usModemId);
        DHCP_INFO_LOG1("DHCP_SubEntityNum: Stop IPv6 Filter.",usModemId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_TraceDataToCds
 功能描述  : 勾包DHCP给CDS的IP数据
 输入参数  : TTF_MEM_ST *pstTtfMem
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月12日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_TraceDataToCds
(
    TTF_MEM_ST                         *pstTtfMem
)
{
    CTTF_DHCP_TRACE_DATA_STRU          *pstSendMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMinLen;


    if ((VOS_NULL_PTR == pstTtfMem) || (pstTtfMem->usUsed > DHCPV6C_SEND_MSG_MAXLEN))
    {
        DHCP_WARNING_LOG("parm is error!\r\n");
        return;
    }

    PS_MEM_SET(&g_stDhcpTraceData, 0, sizeof(g_stDhcpTraceData));
    pstSendMsg  = &g_stDhcpTraceData;

    ulMinLen    = (VOS_UINT32)PS_MIN(pstTtfMem->usUsed, DHCPV6C_SEND_MSG_MAXLEN);
    pstSendMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid     = MSPS_PID_DHCP;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverPid   = MSPS_PID_DHCP;
    pstSendMsg->ulLength        = ulMinLen + DHCP_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstSendMsg->enMsgId         = ID_CTTF_DHCP_TRACE_IP_DATA_TO_CDS;
    pstSendMsg->usLen           = (VOS_UINT16)ulMinLen;
    (VOID)PS_MEM_CPY(pstSendMsg->aucValue, pstTtfMem->pData, ulMinLen);

    CTTF_DHCP_TRACE_DATA_MSG(pstSendMsg);

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_SendIpToCds
 功能描述  : 发送缓存数据包
 输入参数  : DHCP_ENTITY_STRU *pstDhcpEntity
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 DHCP_SendIpToCds
(
    DHCP_ENTITY_STRU                   *pstDhcpEntity
)
{
    TTF_MEM_ST                         *pstSdu;
    DHCP_TIMER_STRU                    *pstTimerInfo;
    VOS_UINT32                          ulTimerLen = 0;
    DHCP_CDS_DATA_REQ_STRU             *pstDataReq = VOS_NULL_PTR;

    if(ID_TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_BUTT == pstDhcpEntity->enMsgType)
    {
        /* Timer停不掉，或者停的时候Timer消息已发出 */
        DHCP_WARNING_LOG("DHCP_SendIpToCds: Msg released!\n");
        return VOS_ERR;
    }

    pstTimerInfo = &pstDhcpEntity->stTimerInfo;

    /* 停止定时器 */
    DHCP_StopTimer(pstTimerInfo);

    /* 无论发送成功与否，当做完成一次重发 */
    pstTimerInfo->ucLoopTimes++;

    /* 发送缓存的IP包 */
    pstSdu = TTF_MemBlkAlloc(MSPS_PID_DHCP,
                             TTF_MEM_POOL_ID_UL_DATA,
                             (VOS_UINT16)(pstDhcpEntity->stIpSndNwMsg.ulSendMsgSize + IP_PACKAGE_HEADER_RESERVE));
    if(VOS_NULL_PTR == pstSdu)
    {
        DHCP_ERROR_LOG("DHCP_SendIpToCds: Fail to malloc memory for RS!\n");
    }
    else
    {
        VOS_MemSet(pstSdu->pData, 0, (pstDhcpEntity->stIpSndNwMsg.ulSendMsgSize + IP_PACKAGE_HEADER_RESERVE));
        pstSdu->pData += IP_PACKAGE_HEADER_RESERVE;
        pstSdu->usLen -= IP_PACKAGE_HEADER_RESERVE;
        VOS_MemCpy(pstSdu->pData, pstDhcpEntity->stIpSndNwMsg.pucSendMsg, pstDhcpEntity->stIpSndNwMsg.ulSendMsgSize);
        pstSdu->usUsed = (VOS_UINT16)pstDhcpEntity->stIpSndNwMsg.ulSendMsgSize;

        DHCP_TraceDataToCds(pstSdu);

        /*分配空间并检验分配是否成功*/
        pstDataReq = (DHCP_CDS_DATA_REQ_STRU *)
                            PS_ALLOC_MSG_WITH_HEADER_LEN(MSPS_PID_DHCP, sizeof(DHCP_CDS_DATA_REQ_STRU));

        if ( VOS_NULL_PTR == pstDataReq )
        {
            TTF_MemFree(MSPS_PID_DHCP, pstSdu);
            DHCP_ReleaseResendResourse(pstDhcpEntity);
            /*打印异常信息*/
            DHCP_ERROR_LOG("DHCP_SendIpToCds: Alloc Msg fail!\n");
            return VOS_ERR;
        }

        pstDataReq->enModemId   = DHCP_GET_MODEMID_FROM_EXEPSID(pstDhcpEntity->ucEpsbId);
        pstDataReq->ucRabId     = DHCP_GET_EPSID_FROM_EXEPSID(pstDhcpEntity->ucEpsbId);
        pstDataReq->pstIpPacket = pstSdu;

        /*填写消息头*/
        pstDataReq->enMsgId         = ID_DHCP_CDS_DATA_REQ;
        pstDataReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstDataReq->ulSenderPid     = MSPS_PID_DHCP;
        pstDataReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstDataReq->ulReceiverPid   = UEPS_PID_CDS;

        /* 调用消息发送函数 */
        if (VOS_OK != PS_SEND_MSG(MSPS_PID_DHCP, pstDataReq))
        {
            TTF_MemFree(MSPS_PID_DHCP, pstSdu);
            DHCP_ReleaseResendResourse(pstDhcpEntity);
            /*打印异常信息*/
            DHCP_WARNING_LOG("DHCP_SendIpToCds::send RS Pkt fail!\n");
            return VOS_ERR;
        }

#ifdef DMT
        TTF_MemFree(MSPS_PID_DHCP, pstSdu);
        pstSdu = VOS_NULL_PTR;
#endif

    }

    /* 重传处理 */
    ulTimerLen = DHCP_GetTimerLen(pstTimerInfo->ulName);
    if (ulTimerLen == 0)
    {
        /*打印异常信息*/
        DHCP_WARNING_LOG1("DHCP_SendIpToCds: ERROR to get TimerLen:%d \n", pstTimerInfo->ulName);
        DHCP_ReleaseResendResourse(pstDhcpEntity);
        return VOS_ERR;
    }

    if (VOS_OK != PS_START_REL_TIMER(&pstTimerInfo->hTm,MSPS_PID_DHCP,\
                                ulTimerLen,pstTimerInfo->ulName,\
                                pstDhcpEntity->ucEpsbId,VOS_RELTIMER_NOLOOP))
    {
        DHCP_WARNING_LOG("DHCP_SendIpToCds: Fail to Start Timer, halt to send msg! \n");
        pstTimerInfo->hTm= VOS_NULL_PTR;
        DHCP_ReleaseResendResourse(pstDhcpEntity);
        return VOS_ERR;
    }

    DHCP_INFO_LOG("DHCP start RS Timer!\n");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCP_RespApsGetDnsIpv6Fail
 功能描述  : DHCP回复APS GetDnsIpv6失败
 输入参数  : pstPppActReq   APS_PPP_ACT_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-07-20
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_RespApsGetDnsIpv6Fail
(
    APS_DHCP_DNS_IPV6_REQ_STRU         *pstDhcpDnsReq
)
{
    DHCP_APS_DNS_IPV6_CNF_STRU         *pstApsDnsIpv6Cnf;


    /* 申请响应消息内存 */
    pstApsDnsIpv6Cnf    = (DHCP_APS_DNS_IPV6_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_DHCP, sizeof(DHCP_APS_DNS_IPV6_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDnsIpv6Cnf)
    {
        DHCP_ERROR_LOG("Alloc pstApsDnsIpv6Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsDnsIpv6Cnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(DHCP_APS_DNS_IPV6_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsDnsIpv6Cnf->ulReceiverPid         = pstDhcpDnsReq->ulSenderPid;
    pstApsDnsIpv6Cnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsDnsIpv6Cnf->enMsgId               = ID_DHCP_APS_GET_DNS_IPV6_CNF;
    pstApsDnsIpv6Cnf->usOpId                = pstDhcpDnsReq->usOpId;
    pstApsDnsIpv6Cnf->ulResult              = VOS_ERR;
    pstApsDnsIpv6Cnf->ucRabId               = pstDhcpDnsReq->ucRabId;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_DHCP, pstApsDnsIpv6Cnf))
    {
        DHCP_WARNING_LOG("Warning:Send ID_DHCP_APS_GET_DNS_IPV6_CNF msg fail!\n");
    }

    DHCP_INFO_LOG("Succeed to send ID_DHCP_APS_GET_DNS_IPV6_CNF!!!\n");
    return;
}

/*****************************************************************************
 函 数 名  : DHCP_ProcDnsIpv6Req
 功能描述  : 创建实体信息，申请IPv6地址
 输入参数  : VOS_VOID        *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_ProcDnsIpv6Req
(
    APS_DHCP_DNS_IPV6_REQ_STRU         *pstDhcpDnsReq
)
{
    DHCP_ENTITY_STRU                   *pstDhcpEntity   = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucExRabId;


    enModemId = VOS_GetModemIDFromPid(pstDhcpDnsReq->ulSenderPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        DHCP_RespApsGetDnsIpv6Fail(pstDhcpDnsReq);
        DHCP_WARNING_LOG1("DHCP_ProcDnsIpv6Req: Invalid ModemId:%d\n", enModemId);
        return ;
    }

    ucExRabId = DHCP_FORM_EXEPSID(enModemId, pstDhcpDnsReq->ucRabId);

    if (VOS_OK != DHCP_CheckEpsIdValid(ucExRabId))
    {
        DHCP_RespApsGetDnsIpv6Fail(pstDhcpDnsReq);
        DHCP_WARNING_LOG1("DHCP_ProcDnsIpv6Req: Invalid EpsbId:%d\n", ucExRabId);
        return;
    }

    /* 查询是否已存在相应Entity */
    pstDhcpEntity = DHCP_GetEntity(ucExRabId);
    if(VOS_NULL_PTR != pstDhcpEntity)
    {
        /* 释放相应Entity */
        DHCP_RelEntity(pstDhcpEntity);
    }

    pstDhcpEntity = DHCP_AllocEntity(ucExRabId);
    if(VOS_NULL_PTR == pstDhcpEntity)
    {
        DHCP_RespApsGetDnsIpv6Fail(pstDhcpDnsReq);
        DHCP_WARNING_LOG("DHCP_ProcDnsIpv6Req: too many Entity!\n");
        return;
    }

    pstDhcpEntity->enMsgType = ID_APS_DHCP_GET_DNS_IPV6_REQ;

    (VOS_VOID)VOS_MemCpy(pstDhcpEntity->aucInterfaceId, pstDhcpDnsReq->aucIdentifierId, TAF_APS_DHCP_IPV6_IFID_LEN);

    if (VOS_OK != DHCP_SendInfoReqPacket(pstDhcpEntity))
    {
        DHCP_RespApsGetDnsIpv6Fail(pstDhcpDnsReq);
        DHCP_WARNING_LOG("DHCP_ProcDnsIpv6Req: Send Req failed!\n");
        /* 释放相应Entity */
        DHCP_RelEntity(pstDhcpEntity);
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : DHCP_ProcDeActInd
 功能描述  :
 输入参数  : VOS_VOID         *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_ProcDeActInd(APS_DHCP_DEACT_IND_STRU *pstDeActInd)
{
    DHCP_ENTITY_STRU                   *pstDhcpEntity = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucExRabId;


    enModemId = VOS_GetModemIDFromPid(pstDeActInd->ulSenderPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        DHCP_WARNING_LOG1("DHCP_ProcDeActInd: Invalid ModemId:", enModemId);
        return ;
    }

    ucExRabId = DHCP_FORM_EXEPSID(enModemId, pstDeActInd->ucRabId);

    if (VOS_OK != DHCP_CheckEpsIdValid(ucExRabId))
    {
        DHCP_WARNING_LOG1("DHCP_ProcDeActInd: Invalid EpsbId:", ucExRabId);
        return;
    }

    DHCP_INFO_LOG2("DHCP receive deact.ModemId,RabId", enModemId,pstDeActInd->ucRabId);

    /* 查询是否已存在相应Entity */
    pstDhcpEntity = DHCP_GetEntity(ucExRabId);
    if(VOS_NULL_PTR == pstDhcpEntity)
    {
        DHCP_WARNING_LOG1("DHCP_ProcDeActInd: Fail to find the Entity:!", ucExRabId);
        return;
    }

    /* 释放相应Entity */
    DHCP_RelEntity(pstDhcpEntity);

    return;
}

/*****************************************************************************
 函数名称  : DHCP_FillElapTimeOption
 功能描述  : 填充Elapsed_Time Option
 输入参数  : DHCP_ENTITY_STRU                   *pstDhcpEntity
 输出参数  : UCHAR *pucMsgBuff, VOS_UINT32 *pulOffset
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_FillElapTimeOption
(
    DHCP_ENTITY_STRU                   *pstDhcpEntity,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulOffset
)
{
    VOS_UINT16                          usTryTime = 0;
    VOS_UINT16                          usOptionLen = 0;
    DHCPV6C_TLV_OPTION_S               *pstElapTimeOption;
    VOS_UINT16                          usElapsedTime = DHCPV6_MSG_OPTION_ELAPSED_TIME;


    usTryTime = (pstDhcpEntity->ucWaitRspTimeOutNum) * (pstDhcpEntity->ucResendTimeout);

    pstElapTimeOption = (DHCPV6C_TLV_OPTION_S *)pucMsgBuff;
    /* 用变量来代替宏是为了消除pclint错误 */
    pstElapTimeOption->usType = VOS_HTONS(usElapsedTime);

    *(VOS_UINT16*)pstElapTimeOption->ucData = VOS_HTONS(usTryTime);
    usOptionLen += sizeof(VOS_UINT16);
    pstElapTimeOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    if (pstDhcpEntity->ucWaitRspTimeOutNum == 0)
    {
        pstDhcpEntity->ucWaitRspTimeOutNum = 0x64;
    }

    return;
}

/*****************************************************************************
 函数名称  : DHCP_GetCiDuidData
 功能描述  : 获取CI-DUID-DATA
 输入参数  : DHCP_ENTITY_STRU                   *pstDhcpEntity
 输出参数  : VOS_UINT8                          *pucData
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_GetCiDuidData
(
    DHCP_ENTITY_STRU                   *pstDhcpEntity,
    VOS_UINT8                          *pucData
)
{
    /* 优先使用MSISDN，其次使用IMSI，再次使用IMEI */
    if((VOS_NULL_DWORD != pstDhcpEntity->aulMSISDN[0])
        || (VOS_NULL_DWORD != pstDhcpEntity->aulMSISDN[1]))
    {
        VOS_MemCpy(pucData, (UCHAR *)pstDhcpEntity->aulMSISDN, DHCP_MAX_MSISDN_LEN);
    }
    else if ((VOS_NULL_DWORD != pstDhcpEntity->aulIMSI[0])
        || (VOS_NULL_DWORD != pstDhcpEntity->aulIMSI[1]))
    {
        VOS_MemCpy(pucData, (UCHAR *)pstDhcpEntity->aulIMSI, DHCP_MAX_MSISDN_LEN);
    }
    else if ((VOS_NULL_DWORD != pstDhcpEntity->aulIMEI[0])
        || (VOS_NULL_DWORD != pstDhcpEntity->aulIMEI[1]))
    {
        VOS_MemCpy(pucData, (UCHAR *)pstDhcpEntity->aulIMEI, DHCP_MAX_MSISDN_LEN);
    }
    else
    {
        /* nothing */
    }

    return;
}

/*****************************************************************************
 函数名称  : DHCP_FillClientIdOption
 功能描述  : 填充Client Identifier Option
 输入参数  : DHCP_ENTITY_STRU                   *pstDhcpEntity
 输出参数  : VOS_UINT8 *pucMsgBuff, VOS_UINT32 *pulOffset
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_FillClientIdOption
(
    DHCP_ENTITY_STRU                   *pstDhcpEntity,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulOffset
)
{
    VOS_UINT16                          usOptionLen = 0;
    DHCPV6C_TLV_OPTION_S               *pstClientIdOption = (DHCPV6C_TLV_OPTION_S *)pucMsgBuff;
    DHCPV6C_DUID_EN_OPTION_S           *pstDuidEn = (DHCPV6C_DUID_EN_OPTION_S *)pstClientIdOption->ucData;
    VOS_UINT16                          ucOptionClientId  = DHCPV6_MSG_OPTION_CLIENTID;
    VOS_UINT16                          ucOptionDuid      = DHCPV6_MSG_OPTION_DUID_EN;
    VOS_UINT32                          ulEnterprisenum   = DHCPV6_HUAWEI_ENTERPRISENUM;


    /* 用变量来代替宏是为了消除pclint错误 */
    pstClientIdOption->usType   = VOS_HTONS(ucOptionClientId);
    pstDuidEn->usType           = VOS_HTONS(ucOptionDuid);
    pstDuidEn->ulEnterpriseNum  = VOS_HTONL(ulEnterprisenum);
    usOptionLen                += sizeof(DHCPV6C_DUID_EN_OPTION_S);

    /* 获取CI-DUID-DATA,BCD码-不需要字节序转换 */
    DHCP_GetCiDuidData(pstDhcpEntity, pstDuidEn->ucData);
    usOptionLen             += DHCP_MAX_MSISDN_LEN;

    pstClientIdOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset              += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    return;
}

/*****************************************************************************
 函数名称  : DHCP_FillOROption
 功能描述  : 填充Option Request Option
 输入参数  : DHCP_ENTITY_STRU                   *pstDhcpEntity
 输出参数  : UCHAR *pucMsgBuff, VOS_UINT32 *pulOffset
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOID DHCP_FillOROption(UCHAR *pucMsgBuff, VOS_UINT32 *pulOffset)
{
    VOS_UINT16                         usOptionLen = 0;
    DHCPV6C_TLV_OPTION_S               *pstOROption = (DHCPV6C_TLV_OPTION_S *)pucMsgBuff;
    VOS_UINT16                         usOptionOro = DHCPV6_MSG_OPTION_ORO;
    VOS_UINT16                         usOptionDns = DHCPV6_MSG_OPTION_DNS_SERVERS;


    /* 用变量来代替宏是为了消除pclint错误 */
    pstOROption->usType = VOS_HTONS(usOptionOro);

    /* 请求快速流程和DNS */
    /* Deleted start by y00170683 at 2012-07-27 UGW10.0-DHCPV6C特性 for CR20120726042 rapid-commit-option作为单独的option携带 */
    /* Deleted end by y00170683 at 2012-07-27 UGW10.0-DHCPV6C特性 for CR20120726042 rapid-commit-option作为单独的option携带 */
    /* 用变量来代替宏是为了消除pclint错误 */
    *(VOS_UINT16*)(pstOROption->ucData) = VOS_HTONS(usOptionDns);
    usOptionLen += sizeof(VOS_UINT16);
    pstOROption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    return;
}

/*****************************************************************************
 *  函数名称:       DHCP_GetMagicNumber
 *  初稿完成:       2015-09-22
 *  作    者:       w00316385
 *  函数功能:       生成Magic Number
 *  输入参数:       无
 *  输出参数:       无
 *  返回类型:       VOS_UINT32
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOS_UINT32 DHCP_GetMagicNumber(VOS_VOID)
{
    VOS_UINT32                          ulRetVal = 0;
    VOS_UINT32                          ulSeed;
    VOS_UINT32                          ulRandVal;
#ifdef DHCP_ST
    static VOS_UINT32                   ulMagicNumber = 0x00724c47;             /* 为了用例, 魔数设为定值，需删除*/
#endif


    while (ulRetVal == 0)
    {
        /* 获取时间tick数作为种子 */
        ulSeed = VOS_GetTick();
        VOS_SetSeed(ulSeed);

        /* 生成随机数 */
        ulRandVal   = VOS_Rand(0x00ffffff);
        ulRetVal    = ulRandVal + ulSeed;

#ifdef DHCP_ST
        ulRetVal = ++ulMagicNumber;                                             /* 为了用例, 魔数设为定值，需删除*/
#endif
    }

    return ulRetVal;
}

/*****************************************************************************
 *  函数名称:       DHCP_FillInfoReqMsg
 *  初稿完成:       2015-05-06
 *  作    者:       w00316385
 *  函数功能:       填充消息
 *  输入参数:       DHCP_ENTITY_STRU                   *pstDhcpEntity,
 *  输出参数:       VOS_UINT8 *pucMsgBuff,  VOS_UINT32 *pulMsgLen
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOS_UINT32 DHCP_FillInfoReqMsg
(
    DHCP_ENTITY_STRU                   *pstDhcpEntity,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulMsgLen
)
{
    DHCPV6C_MSG_S                      *pstDhcpv6Msg    = VOS_NULL_PTR;


    /* 填充消息头 */
    pstDhcpv6Msg = (DHCPV6C_MSG_S *)pucMsgBuff;
    pstDhcpv6Msg->ulMsgTypeBit8 = DHCPV6_MSG_TYPE_INFORMATION_REQUEST;
    /* PV6C_CalcuTransId(pstDhcpv6Msg, pstDhcpcContext->ulTEIDC, pstDhcpcContext->usSeqNum); */
    /* pstDhcpv6Msg->ulTransIdBit24  = pstDhcpEntity->usSeqNum;
    pstDhcpv6Msg->ulTransIdBit24 = VOS_HTONBIT24(pstDhcpv6Msg->ulTransIdBit24);*/
    pstDhcpv6Msg->ulTransIdBit24 = DHCP_GetMagicNumber();
    *pulMsgLen += sizeof(DHCPV6C_MSG_S);

    /* 填充Elapsed_Time Option */
    DHCP_FillElapTimeOption(pstDhcpEntity, &(pucMsgBuff[*pulMsgLen]), pulMsgLen);

    /* 填充ClientId Option */
    DHCP_FillClientIdOption(pstDhcpEntity, &(pucMsgBuff[*pulMsgLen]), pulMsgLen);

    /* 填充option request Option 请求DNS */
    DHCP_FillOROption(&(pucMsgBuff[*pulMsgLen]), (VOS_UINT32 *)pulMsgLen);

    return VOS_OK;

}

/*****************************************************************************
 *  函数名称:       DHCP_SendInfoReqPacket
 *  初稿完成:       2015-05-07
 *  作    者:       w00316385
 *  函数功能:       封装消息发包
 *  输入参数:       DHCP_ENTITY_STRU                   *pstDhcpEntity
 *  输出参数:       无
 *  返回类型:       VOS_UINT32
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOS_UINT32 DHCP_SendInfoReqPacket
(
    DHCP_ENTITY_STRU                   *pstDhcpEntity
)
{
    VOS_UINT32                          ulRet           = VOS_OK;
    VOS_UINT32                          ulMsgLen        = 0;
    VOS_UINT8                          *pucRs = VOS_NULL_PTR;
    VOS_UINT16                          usCheckSum;
    IPV6_PSEDUOHEADER_STRU              stPseduoHeader;
    VOS_UINT16                          usUdpMsgLen;
    VOS_UINT32                          ulTotalLen;


    DHCP_MemZero(g_ucDhcpv6cSendBuff, DHCPV6C_SEND_MSG_MAXLEN);
    DHCP_MemZero(&stPseduoHeader, sizeof(IPV6_PSEDUOHEADER_STRU));

    /* 填充消息 */
    if (VOS_OK != DHCP_FillInfoReqMsg(pstDhcpEntity, g_ucDhcpv6cSendBuff, &ulMsgLen))
    {
        DHCP_WARNING_LOG("DHCP_FillInfoReqMsg fail.\n");
        return VOS_ERR;
    }

    ulTotalLen = ulMsgLen + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;
    pucRs = (VOS_UINT8 *)DHCP_Malloc(MSPS_PID_DHCP, ulTotalLen);
    if(VOS_NULL_PTR == pucRs)
    {
        DHCP_WARNING_LOG("DHCP_SendInfoReqPacket: Fail to alloc memory for RS\n");
        return VOS_ERR;
    }
    DHCP_MemZero(pucRs, ulTotalLen);

    /* 保存消息缓存 */
    pstDhcpEntity->stIpSndNwMsg.pucSendMsg = pucRs;
    pstDhcpEntity->stIpSndNwMsg.ulSendMsgSize = ulTotalLen;

    /* 填写UDP头内容 UDP头中长度应该是UDP头长度+消息长度 */
    usUdpMsgLen = (VOS_UINT16)(ulMsgLen + UDPV6_HEADER_LEN);
    DHCP_BuildDhcpv6UdpHeader(pucRs + IPV6_HEADER_LEN, usUdpMsgLen);

    /* 构造IPv6 header for RS */
    DHCP_BuildIPv6Header(pucRs, &stPseduoHeader, pstDhcpEntity->aucInterfaceId,
                         (VOS_UINT32)(ulMsgLen + UDPV6_HEADER_LEN));

    VOS_MemCpy(pucRs + IPV6_HEADER_LEN + UDPV6_HEADER_LEN, g_ucDhcpv6cSendBuff, ulMsgLen);

    usCheckSum = DHCP_IPv6Checksum(&stPseduoHeader, pucRs + IPV6_HEADER_LEN, ulMsgLen + UDPV6_HEADER_LEN);

    *(VOS_UINT16 *)(VOS_VOID*)(pucRs + IPV6_HEADER_LEN + IP_UDP_CHECKSUM_OFFSET) = usCheckSum;

    pstDhcpEntity->stTimerInfo.ucLoopTimes = 0;
    pstDhcpEntity->stTimerInfo.ulName = DHCP_TIMER_RS;

    /* 发送消息 */
    ulRet = DHCP_SendIpToCds(pstDhcpEntity);

    return ulRet;
}

/*****************************************************************************
 函数名称  : DHCPV6C_CheckServerMsgType
 功能描述  : 检查收到的消息类型
 输入参数  : VOS_UINT8 ucMsgType
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : W00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DHCP_CheckServerMsgType(VOS_UINT8 ucMsgType)
{
    VOS_UINT32                          ulRet = VOS_OK;


    /* 消息计数 */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_REPLY :
            break;

        default:
            ulRet = VOS_ERR;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函数名称  : DHCP_IaAddrOptionDecode
 功能描述  : 解析IaAddrOption
 输入参数  : VOS_UINT8 *pucMsg,  VOS_UINT32 ulMsgLen
 输出参数  : DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-11
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_IaAddrOptionDecode
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulMsgLen,
    DHCPV6C_OPTION_INFO_S              *pstDhcpv6cOption
)
{
    VOS_UINT32                          ulOffset = 0;
    VOS_UINT32                          ulExtnLen = 0;
    DHCPV6C_TLV_OPTION_S               *pstTmpTlvExt = VOS_NULL;


    while(ulOffset < ulMsgLen)
    {
        pstTmpTlvExt = (DHCPV6C_TLV_OPTION_S*)&(pucMsg[ulOffset]);
        ulExtnLen = VOS_NTOHS(pstTmpTlvExt->usLen) + DHCPV6_OPT_HEADER_LEN;

        /* OPTION长度大于消息长度,说明当前信元错误不能解析使用,应该直接退出 */
        if (ulOffset + ulExtnLen > ulMsgLen)
        {
            DHCP_WARNING_LOG4("ulOffset = %u, type = %u, len = %u, ulMsgLen = %u",
                               ulOffset, VOS_NTOHS(pstTmpTlvExt->usType),
                               VOS_NTOHS(pstTmpTlvExt->usLen), ulMsgLen);
            break;
        }

        switch (VOS_NTOHS(pstTmpTlvExt->usType))
        {
            case DHCPV6_MSG_OPTION_STATUS_CODE:
            {
                pstDhcpv6cOption->pstIaAddrStatusCodeOption = (DHCPV6C_STATUS_CODE_OPTION_S *)pstTmpTlvExt;
                break;
            }
            default:     /* ignore unknow extension */
            {
                break;
            }
        }
        ulOffset += ulExtnLen;
    }

    return;
}

/*****************************************************************************
 函数名称  : DHCP_IaNaOptionDecode
 功能描述  : 解析IaNaOption
 输入参数  : VOS_UINT8 *pucMsg,  VOS_UINT32 ulMsgLen
 输出参数  : DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-11
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_IaNaOptionDecode
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulMsgLen,
    DHCPV6C_OPTION_INFO_S              *pstDhcpv6cOption
)
{
    VOS_UINT32                          ulOffset = 0;
    VOS_UINT32                          ulExtnLen = 0;
    VOS_UINT16                          usIaAddrLen = 0;
    VOS_UINT16                          usIaAddrDataLen = 0;
    VOS_UINT8                          *pucIaAddrData = VOS_NULL_PTR;
    DHCPV6C_TLV_OPTION_S               *pstTmpTlvExt = VOS_NULL_PTR;

    while(ulOffset < ulMsgLen)
    {
        pstTmpTlvExt = (DHCPV6C_TLV_OPTION_S*)&(pucMsg[ulOffset]);
        ulExtnLen = VOS_NTOHS(pstTmpTlvExt->usLen) + DHCPV6_OPT_HEADER_LEN;

        /* OPTION长度大于消息长度,说明当前信元错误不能解析使用,应该直接退出 */
        if (ulOffset + ulExtnLen > ulMsgLen)
        {
            DHCP_WARNING_LOG4("ulOffset = %u, type = %u, len = %u, ulMsgLen = %u",
                               ulOffset, VOS_NTOHS(pstTmpTlvExt->usType),
                               VOS_NTOHS(pstTmpTlvExt->usLen), ulMsgLen);
            break;
        }

        switch (VOS_NTOHS(pstTmpTlvExt->usType))
        {
            case DHCPV6_MSG_OPTION_IAADDR:
            {
                pstDhcpv6cOption->pstIaAddrOption = (DHCPV6C_IAADDR_OPTION_S *)pstTmpTlvExt;

                /* 解析IANA-data 可能含有staus-code */
                pucIaAddrData = pstDhcpv6cOption->pstIaAddrOption->ucData;
                usIaAddrLen = VOS_NTOHS(pstDhcpv6cOption->pstIaAddrOption->usLen);
                if (usIaAddrLen > (sizeof(DHCPV6C_IAADDR_OPTION_S) - DHCPV6_OPT_HEADER_LEN))
                {
                    usIaAddrDataLen = usIaAddrLen
                                    - (sizeof(DHCPV6C_IAADDR_OPTION_S) - DHCPV6_OPT_HEADER_LEN);
                    DHCP_IaAddrOptionDecode(pucIaAddrData, (VOS_UINT32)usIaAddrDataLen, pstDhcpv6cOption);
                }
                break;
            }
            case DHCPV6_MSG_OPTION_STATUS_CODE:
            {
                pstDhcpv6cOption->pstIaNaStatusCodeOption = (DHCPV6C_STATUS_CODE_OPTION_S *)pstTmpTlvExt;
                break;
            }
            default:     /* ignore unknow extension */
            {
                break;
            }
        }
        ulOffset += ulExtnLen;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_OptionDecode
 功能描述  : 解析Option
 输入参数  : VOS_UINT8 *pucMsg,  VOS_UINT32 ulMsgLen
 输出参数  : DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-11
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_OptionDecode
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulMsgLen,
    DHCPV6C_OPTION_INFO_S              *pstDhcpv6cOption
)
{
    VOS_UINT32                          ulOffset = 0;
    VOS_UINT32                          ulExtnLen = 0;
    VOS_UINT16                          usIaNaLen = 0;
    VOS_UINT16                          usIaNaDataLen = 0;
    VOS_UINT8                          *pucIaNaData = VOS_NULL_PTR;
    DHCPV6C_TLV_OPTION_S               *pstTmpTlvExt = VOS_NULL_PTR;


    while(ulOffset < ulMsgLen)
    {
        pstTmpTlvExt = (DHCPV6C_TLV_OPTION_S*)&(pucMsg[ulOffset]);
        ulExtnLen = VOS_NTOHS(pstTmpTlvExt->usLen) + DHCPV6_OPT_HEADER_LEN;

        /* OPTION长度大于消息长度,说明当前信元错误不能解析使用,应该直接退出 */
        if (ulOffset + ulExtnLen > ulMsgLen)
        {
            DHCP_WARNING_LOG4("ulOffset = %u, type = %u, len = %u, ulMsgLen = %u",
                               ulOffset, VOS_NTOHS(pstTmpTlvExt->usType),
                               VOS_NTOHS(pstTmpTlvExt->usLen), ulMsgLen);
            break;
        }

        switch (VOS_NTOHS(pstTmpTlvExt->usType))
        {
            case DHCPV6_MSG_OPTION_CLIENTID:
            {
                pstDhcpv6cOption->pstClientIdOption = pstTmpTlvExt;
                if ((DHCPV6C_MAX_DUID_LEN == VOS_NTOHS(pstTmpTlvExt->usLen))
                    && (DHCPV6_MSG_OPTION_DUID_EN == VOS_NTOHS(*(VOS_UINT16*)pstTmpTlvExt->ucData)))
                {
                    pstDhcpv6cOption->pstCiDuidEn = (DHCPV6C_DUID_EN_OPTION_S *)(pstTmpTlvExt->ucData);
                }
                break;
            }
            case DHCPV6_MSG_OPTION_SERVERID:
            {
                pstDhcpv6cOption->pstServerIdOption = pstTmpTlvExt;
                break;
            }
            case DHCPV6_MSG_OPTION_IA_NA:
            {
                pstDhcpv6cOption->pstIaNaOption = (DHCPV6C_IANA_OPTION_S*)pstTmpTlvExt;

                /* 解析IANA-data 可能含有ia-addr, staus-code */
                pucIaNaData = pstDhcpv6cOption->pstIaNaOption->ucData;
                usIaNaLen = VOS_NTOHS(pstDhcpv6cOption->pstIaNaOption->usLen);
                if (usIaNaLen > (sizeof(DHCPV6C_IANA_OPTION_S) - DHCPV6_OPT_HEADER_LEN))
                {
                    usIaNaDataLen = usIaNaLen - (sizeof(DHCPV6C_IANA_OPTION_S) - DHCPV6_OPT_HEADER_LEN);
                    DHCP_IaNaOptionDecode(pucIaNaData, (VOS_UINT32)usIaNaDataLen, pstDhcpv6cOption);
                }
                break;
            }
            case DHCPV6_MSG_OPTION_DNS_SERVERS:
            {
                /* CR20120726042 DNS-option只取最后一个的前两个地址作为主备DNS */
                pstDhcpv6cOption->pstDnsOption = pstTmpTlvExt;
                break;
            }
            case DHCPV6_MSG_OPTION_STATUS_CODE:
            {
                pstDhcpv6cOption->pstMsgStatusCodeOption = (DHCPV6C_STATUS_CODE_OPTION_S *)pstTmpTlvExt;
                break;
            }
            default:     /* ignore unknow extension */
            {
                break;
            }
        }
        ulOffset += ulExtnLen;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : DHCP_ConvertDnsToHomeOrder
 功能描述  : 将dns-option中字段转换为本地序
 输入参数  : DHCPV6C_TLV_OPTION_S **ppstDnsOption
 输出参数  : DHCPV6C_DNS_OPTION_S **ppstDnsOption, UCHAR *pucMainDnsFlg, UCHAR *pucSecdDnsFlg
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-11
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_ConvertDnsToHomeOrder
(
    DHCPV6C_TLV_OPTION_S              **ppstDnsOption,
    VOS_UINT8                          *pucMainDnsFlg,
    VOS_UINT8                          *pucSecdDnsFlg
)
{
    in6_addr                            stDnsAddr[DHCPV6C_MAX_DNS_NUM];


    (*ppstDnsOption)->usLen = VOS_NTOHS((*ppstDnsOption)->usLen);

    /* 携带多于两个地址 */
    if ((*ppstDnsOption)->usLen >= (DHCPV6C_MAX_DNS_NUM * sizeof(in6_addr)))
    {
        *pucMainDnsFlg = VOS_TRUE;
        *pucSecdDnsFlg = VOS_TRUE;
        VOS_MemCpy(stDnsAddr, (*ppstDnsOption)->ucData, DHCPV6C_MAX_DNS_NUM * sizeof(in6_addr));
        VOS_MemCpy((*ppstDnsOption)->ucData, stDnsAddr, DHCPV6C_MAX_DNS_NUM * sizeof(in6_addr));
    }
    /* 只携带一个地址 */
    else if((*ppstDnsOption)->usLen >= sizeof(in6_addr))
    {
        *pucMainDnsFlg = VOS_TRUE;
        *pucSecdDnsFlg = VOS_FALSE;
        VOS_MemCpy(stDnsAddr, (*ppstDnsOption)->ucData,  sizeof(in6_addr));
        VOS_MemCpy((*ppstDnsOption)->ucData, stDnsAddr,  sizeof(in6_addr));
    }
    /* 其他情况,DNS信元错误 */
    else
    {
        *pucMainDnsFlg = VOS_FALSE;
        *pucSecdDnsFlg = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_ConvertToHomeOrder
 功能描述  : 将option中字段转换为本地序
 输入参数  : DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 输出参数  : DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-11
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_ConvertToHomeOrder(DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption)
{
    /* clientId */
    if (VOS_NULL != pstDhcpv6cOption->pstClientIdOption)
    {
        pstDhcpv6cOption->pstClientIdOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstClientIdOption->usLen);
    }

    /* CiDuId */
    if (VOS_NULL != pstDhcpv6cOption->pstCiDuidEn)
    {
        pstDhcpv6cOption->pstCiDuidEn->ulEnterpriseNum = VOS_NTOHL(pstDhcpv6cOption->pstCiDuidEn->ulEnterpriseNum);
    }

    /* ServerId */
    if (VOS_NULL != pstDhcpv6cOption->pstServerIdOption)
    {
        pstDhcpv6cOption->pstServerIdOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstServerIdOption->usLen);
    }

    /* IaNa */
    if (VOS_NULL != pstDhcpv6cOption->pstIaNaOption)
    {
        pstDhcpv6cOption->pstIaNaOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstIaNaOption->usLen);
        pstDhcpv6cOption->pstIaNaOption->ulId = VOS_NTOHL(pstDhcpv6cOption->pstIaNaOption->ulId);
        pstDhcpv6cOption->pstIaNaOption->ulT1 = VOS_NTOHL(pstDhcpv6cOption->pstIaNaOption->ulT1);
        pstDhcpv6cOption->pstIaNaOption->ulT2 = VOS_NTOHL(pstDhcpv6cOption->pstIaNaOption->ulT2);
    }

    /* IaAddr */
    if (VOS_NULL != pstDhcpv6cOption->pstIaAddrOption)
    {
        pstDhcpv6cOption->pstIaAddrOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstIaAddrOption->usLen);
        pstDhcpv6cOption->pstIaAddrOption->ulPreTime = VOS_NTOHL(pstDhcpv6cOption->pstIaAddrOption->ulPreTime);
        pstDhcpv6cOption->pstIaAddrOption->ulValidTime = VOS_NTOHL(pstDhcpv6cOption->pstIaAddrOption->ulValidTime);
    }

    /* Dns CR20120726042 DNS-option只取最后一个的前两个地址作为主备DNS */

    if (VOS_NULL != pstDhcpv6cOption->pstDnsOption)
    {
        DHCP_ConvertDnsToHomeOrder(&(pstDhcpv6cOption->pstDnsOption),
            &(pstDhcpv6cOption->ucMainDnsFlg), &(pstDhcpv6cOption->ucSecdDnsFlg));
    }

    /* StatusCode */
    if (VOS_NULL != pstDhcpv6cOption->pstMsgStatusCodeOption)
    {
        pstDhcpv6cOption->pstMsgStatusCodeOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstMsgStatusCodeOption->usLen);
        pstDhcpv6cOption->pstMsgStatusCodeOption->usCode = VOS_NTOHS(pstDhcpv6cOption->pstMsgStatusCodeOption->usCode);
    }

    if (VOS_NULL != pstDhcpv6cOption->pstIaNaStatusCodeOption)
    {
        pstDhcpv6cOption->pstIaNaStatusCodeOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstIaNaStatusCodeOption->usLen);
        pstDhcpv6cOption->pstIaNaStatusCodeOption->usCode = VOS_NTOHS(pstDhcpv6cOption->pstIaNaStatusCodeOption->usCode);
    }

    if (VOS_NULL != pstDhcpv6cOption->pstIaAddrStatusCodeOption)
    {
        pstDhcpv6cOption->pstIaAddrStatusCodeOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstIaAddrStatusCodeOption->usLen);
        pstDhcpv6cOption->pstIaAddrStatusCodeOption->usCode = VOS_NTOHS(pstDhcpv6cOption->pstIaAddrStatusCodeOption->usCode);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_MsgDecode
 功能描述  : 消息解码
 输入参数  : DHCPV6C_MSG_INFO_S *pstMsgInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-11
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DHCP_MsgDecode(DHCPV6C_MSG_INFO_S *pstMsgInfo)
{
    VOS_UINT32                          ulOffset = sizeof(DHCPV6C_MSG_S);


    /* 消息长度检查 */
    if(pstMsgInfo->ulMsgLen < ulOffset)
    {
        DHCP_WARNING_LOG1("DHCP_MsgDecode:ulMsgLen = %u", pstMsgInfo->ulMsgLen);
        return VOS_ERR;
    }

    /* 解析OPTION */
    DHCP_OptionDecode(pstMsgInfo->pucMsg + ulOffset,
                        pstMsgInfo->ulMsgLen - ulOffset,
                        &(pstMsgInfo->stDhcpv6cOptionInfo));

    /* 网络序转化为主机序 */
    DHCP_ConvertToHomeOrder(&(pstMsgInfo->stDhcpv6cOptionInfo));

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCP_AdsDataIndProc
 *  初稿完成:       2015-05-07
 *  作    者:       w00316385
 *  函数功能:       处理ADS返回C核的消息
 *  输入参数:       VOS_VOID *pRcvMsg
 *  输出参数:       无
 *  返回类型:       VOS_VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOS_VOID DHCP_AdsDataIndProc(VOS_VOID *pRcvMsg)
{
    ADS_DHCP_DATA_IND_STRU             *pstDataInd;
    DHCPV6C_MSG_INFO_S                  stMsgInfo;
    in6_addr                            stDnsAddr[DHCPV6C_MAX_DNS_NUM];
    VOS_UINT32                          ulRet     = VOS_OK;
    VOS_UINT8                           ucMsgType;
    VOS_UINT8                          *pucDhcpMsg;
    VOS_UINT16                          usDhcpMsgLen;
    VOS_UINT8                           ucExRabId;
    DHCP_ENTITY_STRU                   *pstDhcpEntity   = VOS_NULL_PTR;


    /* 前面已经保证pRcvMsg非空 */

    pstDataInd = (ADS_DHCP_DATA_IND_STRU*)pRcvMsg;
    ucExRabId = DHCP_FORM_EXEPSID(pstDataInd->enModemId, pstDataInd->ucRabId);

    if (VOS_OK != DHCP_CheckEpsIdValid(ucExRabId))
    {
        DHCP_WARNING_LOG1("DHCP_AdsDataIndProc: Invalid Para.ModemId,RabId,ExRabId:",
                        ucExRabId);
        return;
    }

    /* 查询是否已存在相应Entity */
    pstDhcpEntity = DHCP_GetEntity(ucExRabId);
    if(VOS_NULL_PTR == pstDhcpEntity)
    {
        return;
    }

    if (pstDataInd->usLen <= (IPV6_HEADER_LEN + UDPV6_HEADER_LEN))
    {
        DHCP_RespApsDnsIpv6ReqCmd(VOS_NULL_PTR, ucExRabId, VOS_ERR);
        DHCP_ReleaseResendResourse(pstDhcpEntity);
        return;
    }

    pucDhcpMsg = (VOS_UINT8 *)((VOS_SIZE_T)(pstDataInd->aucData) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN);
    usDhcpMsgLen = pstDataInd->usLen - IPV6_HEADER_LEN - UDPV6_HEADER_LEN;
    ucMsgType = (VOS_UINT8)DHCPV6C_GET_MSG_TYPE(pucDhcpMsg);
    ulRet = DHCP_CheckServerMsgType(ucMsgType);
    if (VOS_OK != ulRet)
    {
        DHCP_RespApsDnsIpv6ReqCmd(VOS_NULL_PTR, ucExRabId, VOS_ERR);
        DHCP_ReleaseResendResourse(pstDhcpEntity);
        return;
    }

    /* 消息解码 */
    VOS_MemSet(&stMsgInfo, 0, sizeof(DHCPV6C_MSG_INFO_S));
    stMsgInfo.pucMsg = pucDhcpMsg;
    stMsgInfo.ulMsgLen = usDhcpMsgLen;
    ulRet = DHCP_MsgDecode(&stMsgInfo);

    /* 解码失败 */
    if (VOS_OK != ulRet)
    {
        DHCP_RespApsDnsIpv6ReqCmd(VOS_NULL_PTR, ucExRabId, VOS_ERR);
        DHCP_ReleaseResendResourse(pstDhcpEntity);
        return;
    }

    /* 给TAF发送消息 */
    VOS_MemSet(stDnsAddr, 0, sizeof(in6_addr)*DHCPV6C_MAX_DNS_NUM);
    VOS_MemCpy(stDnsAddr, stMsgInfo.stDhcpv6cOptionInfo.pstDnsOption->ucData,
                sizeof(in6_addr)*DHCPV6C_MAX_DNS_NUM);
    DHCP_RespApsDnsIpv6ReqCmd(stDnsAddr, ucExRabId, VOS_OK);
    DHCP_ReleaseResendResourse(pstDhcpEntity);

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_CdsStartFilterCnfProc
 功能描述  : 处理DHCPv6过滤启动确认消息
 输入参数  : VOS_VOID    *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月7日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_CdsStartFilterCnfProc
(
    CDS_DHCP_START_FILTER_CNF_STRU     *pstStartFilterCnf
)
{
    if(DHCP_CDS_RESULT_SUCC != pstStartFilterCnf->enRslt)
    {
        DHCP_WARNING_LOG1("DHCP_CdsStartFilterCnfProc: Fail to Start DHCPv6 Filter! ModemId=%d",
                          pstStartFilterCnf->enModemId);
    }
    else
    {
        DHCP_WARNING_LOG1("DHCP_CdsStartFilterCnfProc: Start DHCPv6 Filter Successfully! ModemId=%d",
                       pstStartFilterCnf->enModemId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_CdsStopFilterCnfProc
 功能描述  : 处理DHCPv6过滤停止确认消息
 输入参数  : VOS_VOID    *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月7日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_CdsStopFilterCnfProc
(
    CDS_DHCP_STOP_FILTER_CNF_STRU      *pstStopFilterCnf
)
{
    if(DHCP_CDS_RESULT_SUCC != pstStopFilterCnf->enRslt)
    {
        DHCP_WARNING_LOG1("DHCP_CdsStopFilterCnfProc: Fail to Stop DHCPv6 Filter! ModemId=%d",
                          pstStopFilterCnf->enModemId);
    }
    else
    {
        DHCP_WARNING_LOG1("DHCP_CdsStopFilterCnfProc: Stop DHCPv6 Filter Successfully! ModemId=%d",
                          pstStopFilterCnf->enModemId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_MsgTimerProc
 功能描述  : DHCP模块中的定时器消息处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-05
    作    者   : W00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_MsgTimerProc(const REL_TIMER_MSG *pRcvMsg)
{
    VOS_UINT32                          ulTmrId;
    DHCP_ENTITY_STRU                   *pstDhcpEntity;
    VOS_UINT8                           ucExEpsbId;

    ulTmrId = IP_GetTimerName(pRcvMsg);
    ucExEpsbId = (VOS_UINT8)IP_GetTimerPara(pRcvMsg);

    if (VOS_OK != DHCP_CheckEpsIdValid(ucExEpsbId))
    {
        DHCP_WARNING_LOG1("DHCP_MsgTimerProc: Invalid EpsbId:%d\n", ucExEpsbId);
        return;
    }


    pstDhcpEntity = DHCP_GetEntity(ucExEpsbId);
    if(VOS_NULL_PTR == pstDhcpEntity)
    {
        DHCP_WARNING_LOG("DHCP_MsgTimerProc: Fail to get specific Entity\n");
        return;
    }

    switch(ulTmrId)
    {
        case DHCP_TIMER_RS:

            pstDhcpEntity->stTimerInfo.hTm = VOS_NULL_PTR;

            if(pstDhcpEntity->stTimerInfo.ucLoopTimes < g_ulDhcpMaxRtrRSTimes)
            {
                if(VOS_OK == DHCP_SendIpToCds(pstDhcpEntity))
                {
                    DHCP_INFO_LOG1("DHCP_MsgTimerProc: succeed to trigger RS RESEND:%d\n", pstDhcpEntity->stTimerInfo.ucLoopTimes);
                }
                else
                {
                    DHCP_RespApsDnsIpv6ReqCmd(VOS_NULL_PTR, ucExEpsbId, VOS_ERR);
                    DHCP_ReleaseResendResourse(pstDhcpEntity);
                }
            }
            else
            {
                DHCP_WARNING_LOG("DHCP_MsgTimerProc: Fail to get RA by RS.\n");
                DHCP_RespApsDnsIpv6ReqCmd(VOS_NULL_PTR, ucExEpsbId, VOS_ERR);
                DHCP_ReleaseResendResourse(pstDhcpEntity);
            }

            break;

        default:
        {
            DHCP_WARNING_LOG1("unknow timer!\r\n", ulTmrId);
        }
    }


    return;
}

/*****************************************************************************
 函 数 名  : DHCP_MsgTafProc
 功能描述  : DHCP模块处理TAF命令
 输入参数  : pMsg    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-05
    作    者   : W00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_MsgTafProc(struct MsgCB * pMsg)
{
    Taf_aps_dhcp_pif_MSG                   *pstApsPublicInfo;
    TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_UINT16   enMsgType;
    APS_DHCP_DNS_IPV6_REQ_STRU             *pstDnsReq;
    APS_DHCP_DEACT_IND_STRU                *pstDeactInd;


    /* 前面已经保证pMsg非空 */

    pstApsPublicInfo            = (Taf_aps_dhcp_pif_MSG *)pMsg;
    enMsgType                   = pstApsPublicInfo->stMsgData.enMsgId;

    switch(enMsgType)
    {
        case ID_APS_DHCP_GET_DNS_IPV6_REQ:

            pstDnsReq = (APS_DHCP_DNS_IPV6_REQ_STRU *)pMsg;
            DHCP_ProcDnsIpv6Req(pstDnsReq);

            break;

        case ID_APS_DHCP_DEACT_IND:

            pstDeactInd = (APS_DHCP_DEACT_IND_STRU *)pMsg;

            DHCP_ProcDeActInd(pstDeactInd);

            break;

        default:

            DHCP_WARNING_LOG1("Invalid Aps Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_MsgAdsProc
 功能描述  : DHCP模块接收处理ADS模块发送的消息
 输入参数  : pMsg    CDS消息
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-06
    作    者   : W00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_MsgAdsProc(struct MsgCB * pMsg)
{
    VOS_UINT32                              ulMsgId;


    ulMsgId = TTF_GET_MSG_NAME(pMsg);

    switch(ulMsgId)
    {
        case ID_ADS_DHCP_DATA_IND:

            DHCP_INFO_LOG("receive ID_ADS_DHCP_DATA_IND");
            DHCP_AdsDataIndProc(pMsg);

            break;

        default:

            DHCP_WARNING_LOG1("Invalid msg", ulMsgId);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_MsgCdsProc
 功能描述  : DHCP接收处理CDS模块发送的消息
 输入参数  : const MsgBlock *pMsgBlock
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : W00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID DHCP_MsgCdsProc(struct MsgCB *pMsg )
{
    CDS_DHCP_MSG_INFO_STRU             *pstCdsDhcpPublicInfo;
    VOS_UINT16                          enMsgType;
    CDS_DHCP_START_FILTER_CNF_STRU     *pstStartFilterCnf;
    CDS_DHCP_STOP_FILTER_CNF_STRU      *pstStopFilterCnf;


    /* 前面已经保证pMsg非空 */

    pstCdsDhcpPublicInfo         = (CDS_DHCP_MSG_INFO_STRU *)pMsg;
    enMsgType                    = pstCdsDhcpPublicInfo->enMsgId;

    switch (enMsgType)
    {
        case ID_CDS_DHCP_START_FILTER_CNF :

            pstStartFilterCnf = (CDS_DHCP_START_FILTER_CNF_STRU *)pMsg;
            DHCP_CdsStartFilterCnfProc(pstStartFilterCnf);

            break;

        case ID_CDS_DHCP_STOP_FILTER_CNF :

            pstStopFilterCnf = (CDS_DHCP_STOP_FILTER_CNF_STRU *)pMsg;
            DHCP_CdsStopFilterCnfProc(pstStopFilterCnf);

            break;

        default:
            DHCP_WARNING_LOG("DHCP_MsgCdsProc:Error Msg!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_Init
 功能描述  : DHCP模块初始化
 输入参数  : VOS_INIT_PHASE_DEFINE
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-04-25
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DHCP_Init(enum VOS_INIT_PHASE_DEFINE InitPhase)
{
    VOS_UINT32                          ulNumber;


    /*******************************************************************
      资源类初始化(BEGIN): 资源类的初始化放在最前面
    *******************************************************************/
    CTTF_DHCP_INIT_LOG_ENT();

    /* 初始化 */
    (VOS_VOID)VOS_MemSet(g_stDhcpEntity, 0, DHCP_ENTITY_MAX_NUM*sizeof(DHCP_ENTITY_STRU));
    for(ulNumber = 0; ulNumber < DHCP_ENTITY_MAX_NUM; ulNumber++)
    {
        g_stDhcpEntity[ulNumber].ucflag = 0;
        g_stDhcpEntity[ulNumber].enMsgType = ID_TAF_APS_DHCP_PIF_MSG_TYPE_ENUM_BUTT;
    }

    DHCP_InitEntityNum();

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : DHCP_MsgProc
 功能描述  : DHCP模块中的消息处理函数。
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-06
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_MsgProc(struct MsgCB * pMsg)
{
    if(VOS_NULL_PTR == pMsg)
    {
        DHCP_WARNING_LOG("DHCP_MsgProc pMsg is NULL!\r\n");
        return;
    }

#if defined (CTTF_PC_ST_SWITCH)
    CTTF_HookMsg(pMsg);
#endif

    switch (pMsg->ulSenderPid)
    {
        /*如果是定时器发来的消息*/
        case VOS_PID_TIMER:
            /*lint -e826*/
            DHCP_MsgTimerProc((REL_TIMER_MSG *)pMsg);
            /*lint +e826*/

            break;

        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:

            DHCP_MsgTafProc((VOS_VOID *)pMsg);

            break;

        case ACPU_PID_ADS_DL:

            DHCP_MsgAdsProc((VOS_VOID *)pMsg);

            break;

        case UEPS_PID_CDS:

            DHCP_MsgCdsProc((VOS_VOID *)pMsg);

            break;

        default:

            DHCP_WARNING_LOG1("DHCP_MsgProc Sender Pid is Invalid! SenderPid:0x%x\n", pMsg->ulSenderPid);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : DHCP_RespApsDnsIpv6ReqCmd
 功能描述  : DHCP回复APS
 输入参数  : pDhcpInfo      DHCP信息，激活失败时填VOS_NULL_PTR,否则非空
             ulResult       VOS_OK/VOS_ERR
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-05
    作    者   : W00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID DHCP_RespApsDnsIpv6ReqCmd
(
    VOS_VOID                           *pDhcpDNSInfo,
    VOS_UINT8                           ucEpsId,
    VOS_UINT32                          ulResult
)
{
    DHCP_APS_DNS_IPV6_CNF_STRU         *pstApsDnsIpv6Cnf;
    in6_addr                           *pstAddrInfo;
    VOS_UINT16                          usModemId;


    /* 申请响应消息内存 */
    pstApsDnsIpv6Cnf = (DHCP_APS_DNS_IPV6_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_DHCP, sizeof(DHCP_APS_DNS_IPV6_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDnsIpv6Cnf)
    {
        DHCP_WARNING_LOG1("Alloc Get dns ipv6 Cnf Mem Fail!\r\n", ulResult);

        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsDnsIpv6Cnf + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(DHCP_APS_DNS_IPV6_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsDnsIpv6Cnf->enMsgId               = ID_DHCP_APS_GET_DNS_IPV6_CNF;
    pstApsDnsIpv6Cnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsDnsIpv6Cnf->ulResult              = ulResult;

    usModemId = DHCP_GET_MODEMID_FROM_EXEPSID(ucEpsId);
    pstApsDnsIpv6Cnf->ucRabId = DHCP_GET_EPSID_FROM_EXEPSID(ucEpsId);

    /*填写消息头*/
    if (MODEM_ID_0 == usModemId)
    {
        pstApsDnsIpv6Cnf->ulReceiverPid = I0_WUEPS_PID_TAF;
    }
    else
    {
        pstApsDnsIpv6Cnf->ulReceiverPid = I1_WUEPS_PID_TAF;
    }


    if (VOS_NULL_PTR != pDhcpDNSInfo)
    {
        /* 非空说明应该是成功，需要把DNS填入 */
        pstAddrInfo                     = (in6_addr *)pDhcpDNSInfo;
        pstApsDnsIpv6Cnf->stIpv6Dns.bitOpIpv6PrimDNS  = 1;
        pstApsDnsIpv6Cnf->stIpv6Dns.bitOpIpv6SecDNS   = 1;
        PS_MEM_CPY(pstApsDnsIpv6Cnf->stIpv6Dns.aucIpv6PrimDNS, pstAddrInfo,
            sizeof(pstApsDnsIpv6Cnf->stIpv6Dns.aucIpv6PrimDNS));
        pstAddrInfo++;
        PS_MEM_CPY(pstApsDnsIpv6Cnf->stIpv6Dns.aucIpv6SecDNS, pstAddrInfo,
            sizeof(pstApsDnsIpv6Cnf->stIpv6Dns.aucIpv6SecDNS));
    }

    /* 发送响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_DHCP, pstApsDnsIpv6Cnf))
    {
        DHCP_WARNING_LOG("Warning:Send ID_DHCP_APS_GET_DNS_IPV6_CNF msg fail!");
    }

    return;
}



/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
