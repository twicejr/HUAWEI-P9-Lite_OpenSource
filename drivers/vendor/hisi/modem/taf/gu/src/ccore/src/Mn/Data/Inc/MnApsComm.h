/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnApsComm.h
  版 本 号   : 初稿
  作    者   : anhuiqing / 00165503
  生成日期   : 2011年04月10日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2011年04月10日
    作    者   : anhuiqing / 00165503
    修改内容   : 创建文件

******************************************************************************/
#ifndef _MN_APS_COMM_H_
#define _MN_APS_COMM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 获取指定PDPID的PDP实体地址 */
#define TAF_APS_GetPdpEntInfoAddr(ucPdpId)      (&g_PdpEntity[ucPdpId])

/* 获取指定PDPID的PDP实体对应的NSAPI */
#define TAF_APS_GetPdpEntNsapi(ucPdpId)         (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ucNsapi)

/* 获取指定PDPID的PDP实体对应的cliet info地址 */
#define TAF_APS_GetPdpEntClientInfoAddr(ucPdpId)  (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->stClientInfo))

/* 获取指定PDPID的PDP实体对应的CID */
#define TAF_APS_GetPdpEntCurrCid(ucPdpId)       (TAF_APS_GetPdpEntClientInfoAddr(ucPdpId)->ucCid)

/* 获取指定PDPID的PDP实体对应的APN有效标志 */
#define TAF_APS_GetPdpEntApnFlag(ucPdpId)       (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpApnFlag)

/* 获取指定PDPID的PDP实体对应的APN地址 */
#define TAF_APS_GetPdpEntApnInfoAddr(ucPdpId)   (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpApn))

/* 获取指定PDPID的PDP实体对应的APN长度 */
#define TAF_APS_GetPdpEntApnLen(ucPdpId)        (TAF_APS_GetPdpEntApnInfoAddr(ucPdpId)->ucLength)

/* 获取指定PDPID的PDP实体对应的APN内容 */
#define TAF_APS_GetPdpEntApnValue(ucPdpId)      (TAF_APS_GetPdpEntApnInfoAddr(ucPdpId)->aucValue)

/* 获取指定PDPID的PDP实体对应的PDP ADDRESS */
#define TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId) (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpAddr))

/* 获取指定PDPID的PDP实体对应的PDP TYPE */
#define TAF_APS_GetPdpEntPdpAddrType(ucPdpId)   (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum)

/* 获取指定PDPID的PDP实体对应的PDP ACT TYPE */
#define TAF_APS_GetPdpEntActType(ucPdpId)       (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ActType)

/* 获取指定PDPID的PDP实体对应的GPRS PARA */
#define TAF_APS_GetPdpEntGprsParaAddr(ucPdpId)  (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->GprsPara))

/* 获取指定PDPID的PDP实体对应的SNDCP激活标识 */
#define TAF_APS_GetPdpEntSndcpActFlg(ucPdpId)   (TAF_APS_GetPdpEntProcTrackAddr(ucPdpId)->ucSNDCPActOrNot)

/* 获取指定PDPID的PDP实体对应的PROC TRACK */
#define TAF_APS_GetPdpEntProcTrackAddr(ucPdpId) (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpProcTrack))

/* 获取指定PDPID的PDP实体对应的IPV6 DNS */
#define TAF_APS_GetPdpEntPdpIpV6DnsInfoAddr(ucPdpId) (&(TAF_APS_GetPdpEntInfoAddr(ucPdpId)->stPdpIpV6Dns))

/* 获取指定PDPID的PDP实体对应的LINKEDNSAPI */
#define TAF_APS_GetPdpEntLinkedNsapi(ucPdpId)   (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ucLinkedNsapi)

/* 获取指定PDPID的PDP实体对应的UsedFlg */
#define TAF_APS_GetPdpEntUsedFlg(ucPdpId)       (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ulUsedFlg)

/* 获取指定CID的CID TAB对应的IMS专有承载标示 */
#define TAF_APS_GetPdpEntImCnSigFlag(ucPdpId)   (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->enImCnSignalFlg)

/* 获取指定PDPID的PDP实体对应的PDP Addr有效标志 */
#define TAF_APS_GetPdpEntPdpAddrFlag(ucPdpId)   (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->PdpAddrFlag)

/* 获取指定PDPID的PDP实体对应的IP地址 */
#define TAF_APS_GetPdpEntPdpIpAddr(ucPdpId)     (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->aucIpAddr)

/* 获取指定PDPID的PDP实体对应的紧急承载标识 */
#define TAF_APS_GetPdpEntEmcFlg(ucPdpId)        (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->enEmergencyFlg)

/* 获取指定PDPID的PDP实体对应的CAUSE */
#define TAF_APS_GetPdpEntPdpCause(ucPdpId)     (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->enCause)

/* 获取指定CID的上下文地址 */
#define TAF_APS_GetTafCidInfoAddr(ucCid)        (&g_TafCidTab[ucCid])

/* 获取指定CID的上下文定义标识 */
#define TAF_APS_GetTafCidInfoUsedFlg(ucCid)     (TAF_APS_GetTafCidInfoAddr(ucCid)->ucUsed)

/* 获取指定CID的Primary PDP标识 */
#define TAF_APS_GetTafCidInfoPrimPdpFlg(ucCid)  (TAF_APS_GetTafCidInfoAddr(ucCid)->ucPriCidFlag)

/* 获取指定CID的Primary CID */
#define TAF_APS_GetTafCidInfoPrimCid(ucCid)     (TAF_APS_GetTafCidInfoAddr(ucCid)->ucPriCid)

/* 获取指定CID的CID TAB地址 */
#define TAF_APS_GetTafCidInfoCidTabAddr(ucCid)  (&(TAF_APS_GetTafCidInfoAddr(ucCid)->CidTab))

/* 获取指定CID的CID TAB对应的PDP类型 */
#define TAF_APS_GetTafCidInfoPdpAddr(ucCid)     (&(TAF_APS_GetTafCidInfoCidTabAddr(ucCid)->stPdpAddr))

/* 获取指定CID的CID TAB对应的PDP类型 */
#define TAF_APS_GetTafCidInfoPdpType(ucCid)     (TAF_APS_GetTafCidInfoPdpAddr(ucCid)->enPdpType)

/* 获取指定CID的CID TAB对应的IPv4地址 */
#define TAF_APS_GetTafCidInfoPdpIpv4Addr(ucCid) (&(TAF_APS_GetTafCidInfoPdpAddr(ucCid)->aucIpv4Addr[0]))

/* 获取指定CID的CID TAB对应的APN */
#define TAF_APS_GetTafCidInfoApn(ucCid)         (&(TAF_APS_GetTafCidInfoCidTabAddr(ucCid)->stApn))

/* 获取指定CID的CID TAB对应的APN长度 */
#define TAF_APS_GetTafCidInfoApnLen(ucCid)      (TAF_APS_GetTafCidInfoApn(ucCid)->ucLength)

/* 获取指定CID的CID TAB对应的APN字符串 */
#define TAF_APS_GetTafCidInfoApnData(ucCid)     (TAF_APS_GetTafCidInfoApn(ucCid)->aucValue)

/* 获取指定CID的CID TAB对应的紧急承载标识 */
#define TAF_APS_GetTafCidInfoEmcFlg(ucCid)      (TAF_APS_GetTafCidInfoCidTabAddr(ucCid)->enEmergencyInd)

/* 检查PDP IP地址类型是否满足IPv4 */
#define TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId)     \
        ( (APS_ADDR_DYNAMIC_IPV4 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum))  \
         || (APS_ADDR_STATIC_IPV4 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum)) \
         || (MN_APS_ADDR_IPV4V6 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum)) )

/* 检查PDP IP地址类型是否满足IPv6 */
#define TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)     \
        ( (MN_APS_ADDR_IPV6 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum))       \
         || (MN_APS_ADDR_IPV4V6 == (TAF_APS_GetPdpEntPdpAddrInfoAddr(ucPdpId)->ucPdpTypeNum)) )  \

/* 检查PDP是否为Primary PDP */
#define TAF_APS_CheckPrimaryPdp(ucPdpId)        (APS_PDP_ACT_PRI == (TAF_APS_GetPdpEntInfoAddr(ucPdpId)->ActType))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/




#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
