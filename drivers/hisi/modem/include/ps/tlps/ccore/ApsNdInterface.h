/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ApsNdInterface.h
  版 本 号   : 初稿
  作    者   : h00159435
  生成日期   : 2011年12月9日
  最近修改   :
  功能描述   : APS与ND CLIENT之间的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月9日
    作    者   : h00159435
    修改内容   : 创建文件

******************************************************************************/
#ifndef __APSNDINTERFACE_H__
#define __APSNDINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "PsTypeDef.h"
#include "mdrv.h"
#include "LPSCommon.h"
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define  APS_ND_MSG_HDR                     (PS_MSG_ID_APS_TO_ND_BASE)
#define  ND_APS_MSG_HDR                     (PS_MSG_ID_ND_TO_APS_BASE)



#define APS_NDCLIENT_IPV6_IFID_LENGTH         (8)
#define NDCLIENT_APS_IPV6_ADDR_LENGTH         (16)
#define NDCLIENT_APS_MAX_PREFIX_NUM_IN_RA     (6)

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
/*****************************************************************************
枚举名    : APS_NDCLIENT_MSG_TYPE_ENUM
协议表格  :
ASN.1描述 :
结构说明  : APS和ND CLIENT之间的消息ID定义
*****************************************************************************/
enum APS_NDCLIENT_MSG_TYPE_ENUM
{
    /* APS发给NDCLIENT的原语 */
    ID_APS_NDCLIENT_PDP_ACT_IND          = (APS_ND_MSG_HDR + 0x00),
    ID_APS_NDCLIENT_PDP_DEACT_IND        = (APS_ND_MSG_HDR + 0x01),
    ID_APS_NDCLIENT_REL_IND              = (APS_ND_MSG_HDR + 0x02),

    /* NDCLIENT发给APS的原语 */
    ID_NDCLIENT_APS_PARA_INFO_NOTIFY     = (ND_APS_MSG_HDR + 0x00),

    ID_APS_NDCLIENT_MSG_TYPE_BUTT
};
typedef VOS_UINT32  APS_NDCLIENT_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : APS_NDCLIENT_PDP_ACT_IND
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6类型的PDP激活指示结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* 消息头 */        /*_H2ASN_Skip*/
    APS_NDCLIENT_MSG_TYPE_ENUM_UINT32       ulMsgId;            /* 消息类型 */      /*_H2ASN_Skip*/
    VOS_UINT8                               ucRabId;            /* RAB标识，取值范围:[5,15] */
    VOS_UINT8                               aucRev[3];
    /*IPv6接口标示符，由网络分配，用于UE IPv6 Link local 地址的生成,aucIpv6InterfacId[0]为接口标示符高字节,aucIpv6InterfacId[7]为接口标示符低字节，0,0,0,0,0,0,0,0为无效接口标示符*/
    VOS_UINT8                               aucIpv6InterfacId[APS_NDCLIENT_IPV6_IFID_LENGTH];
} APS_NDCLIENT_PDP_ACT_IND;

/*****************************************************************************
 结构名    : APS_NDCLIENT_PDP_DEACT_IND
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6类型的PDP去激活指示结构
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
   APS_NDCLIENT_MSG_TYPE_ENUM_UINT32    ulMsgId;            /*_H2ASN_Skip*/
   VOS_UINT8                            ucRabId;
   VOS_UINT8                            aucRev[3];
} APS_NDCLIENT_PDP_DEACT_IND;

/*****************************************************************************
 结构名    : APS_NDCLIENT_REL_IND
 协议表格  :
 ASN.1描述 :
 结构说明  : 释放所有实体资源指示结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    APS_NDCLIENT_MSG_TYPE_ENUM_UINT32   ulMsgId;            /*_H2ASN_Skip*/
} APS_NDCLIENT_REL_IND_STRU;

/*****************************************************************************
 结构名    : NDCLIENT_APS_IPV6_PREFIX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6前缀信息指示结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitL          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ulBitA          :1;
    VOS_UINT32                          ulBitPrefixLen  :8;
    VOS_UINT32                          ulBitRsv        :22;

    VOS_UINT32                          ulValidLifeTime;
    VOS_UINT32                          ulPreferredLifeTime;
    VOS_UINT8                           aucPrefix[NDCLIENT_APS_IPV6_ADDR_LENGTH];
}NDCLIENT_APS_IPV6_PREFIX_STRU;

/*****************************************************************************
 结构名    : NDCLIENT_APS_IPV6_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6参数信息指示结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitOpMtu              :1;
    VOS_UINT32                          ulBitRsv1               :31;

    VOS_UINT32                          ulBitCurHopLimit        :8;
    VOS_UINT32                          ulBitM                  :1;
    VOS_UINT32                          ulBitO                  :1;
    VOS_UINT32                          ulBitRsv2               :22;

    VOS_UINT32                          ulMtu;
    VOS_UINT32                          ulPrefixNum;
    NDCLIENT_APS_IPV6_PREFIX_STRU       astPrefixList[NDCLIENT_APS_MAX_PREFIX_NUM_IN_RA];
} NDCLIENT_APS_IPV6_INFO_STRU;

/*****************************************************************************
 结构名    : NDCLIENT_APS_PARA_INFO_NOTIFY
 协议表格  :
 ASN.1描述 :
 结构说明  : ND CLIENT向APS上报IPV6信息指示结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    APS_NDCLIENT_MSG_TYPE_ENUM_UINT32   ulMsgId;

    VOS_UINT8                           ucRabId;            /* 承载号*/
    VOS_UINT8                           aucRev[3];          /* 消息结构体对齐*/

    NDCLIENT_APS_IPV6_INFO_STRU         stIpv6Info;
} NDCLIENT_APS_PARA_INFO_NOTIFY_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/



/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of ApsNdInterface.h */

