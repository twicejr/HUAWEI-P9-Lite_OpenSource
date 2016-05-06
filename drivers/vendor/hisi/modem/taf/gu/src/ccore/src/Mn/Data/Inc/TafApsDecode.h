/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsDecode.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2011年12月16日
  最近修改   :
  功能描述   : TafApsDecode.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月16日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSDECODE_H__
#define __TAFAPSDECODE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "AtPppInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*解码处理函数指针*/
typedef VOS_UINT32 (*TAF_APS_DECODE_IPCP_PROC_FUNC)(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
);

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : TAF_APS_DECODE_IPCP_PROC_STRU
 结构说明  : 类型与对应处理函数的结构

  1.日    期   : 2012年08月21日
    作    者   : f00179208
    修改内容   : Added for LTE PPP
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOptType;
    TAF_APS_DECODE_IPCP_PROC_FUNC       pDecIpcpProcFunc;
}TAF_APS_DECODE_IPCP_PROC_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 TAF_APS_DecodeIpcpIpAddr(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
);
VOS_UINT32 TAF_APS_DecodeIpcpPriDns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
);
VOS_UINT32 TAF_APS_DecodeIpcpPriNbns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
);
VOS_UINT32 TAF_APS_DecodeIpcpSecDns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
);
VOS_UINT32 TAF_APS_DecodeIpcpSecNbns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
);
TAF_APS_DECODE_IPCP_PROC_FUNC TAF_APS_GetIpcpDecFuncByOptType(VOS_UINT8 ucOptType);
VOS_UINT32 TAF_APS_DecodeIpcpConfigReqPkt(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usPktLen
);
VOS_UINT32 TAF_APS_DecodeIpcpPkt(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucIpcpPkt,
    VOS_UINT16                          usIpcpPktLen
);
VOS_UINT32 TAF_APS_DecodePapInfo(
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    VOS_UINT8                           aucPapReqBuf[],
    VOS_UINT16                          usPapReqLen
);
VOS_UINT32 TAF_APS_DecodeChapInfo(
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    VOS_UINT8                           aucChapChallengeBuf[],
    VOS_UINT16                          usChapChallengeLen,
    VOS_UINT8                           aucChapResponseBuf[],
    VOS_UINT16                          usChapResponseLen
);
VOS_UINT32 TAF_APS_DecodeAuthInfo(
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU  *pstPppAuthConfig
);

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

#endif /* end of TafApsDecode.h */
