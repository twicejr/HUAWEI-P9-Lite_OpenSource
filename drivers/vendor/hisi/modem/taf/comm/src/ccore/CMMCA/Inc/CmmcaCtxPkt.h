/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaCtxPkt.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年1月13日
  最近修改   :
  功能描述   : CmmcaCtxPkt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月13日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CMMCACTXPKT_H__
#define __CMMCACTXPKT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafApsApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* APN字符串的最大长度 */
#define CMMCA_APN_LEN_MAX                                   (99)

/* IPV4地址长度 */
#define CMMCA_IPV4_ADDR_LEN                                 (4)

/* IPV6地址长度 */
#define CMMCA_IPV6_ADDR_LEN                                 (16)

/* IPV6 interface id的长度 */
#define CMMCA_IPV6_INTERFACE_ID_BYTE_LEN                    (8)
#define CMMCA_IPV6_INTERFACE_ID_BIT_LEN                     (64)

/* IPV6 前缀的长度 */
#define CMMCA_IPV6_PREFIX_BYTE_LEN                          (8)
#define CMMCA_IPV6_PREFIX_BIT_LEN                           (64)

/* 支持的地址最大个数 */
#define CMMCA_SUPPORTED_ADDR_NUM_MAX                        (4)

/* 应用支持的PDN个数 */
#define CMMCA_SUPPORTED_PDN_NUM_MAX                         (4)

/* 目前应用最多支持4个PDN,为了支持CMMC双栈回退,CMMCA定义的PDN实体个数乘2 */
#define CMMCA_PDN_CONN_ENTITY_NUM_MAX                       (2 * CMMCA_SUPPORTED_PDN_NUM_MAX)

/* PDN连接实体index无效值 */
#define CMMCA_PDN_CONN_ENTITY_INDEX_INVALID                 (0xFF)

/* PDN ID的最大值 */
#define CMMCA_PDN_ID_MAX                                    (20)

/* PDN ID的最小值*/
#define CMMCA_PDN_ID_MIN                                    (1)

/* PDN ID的无效值 */
#define CMMCA_PDN_ID_INVALID                                (0xFF)

/* PDN ID有效性判断 */
#define CMMCA_IS_VALID_PDN_ID(ucPdnId)\
    (((ucPdnId) >= CMMCA_PDN_ID_MIN) && ((ucPdnId) <= CMMCA_PDN_ID_MAX))

/* PDN TYPE有效性判断 */
#define CMMCA_IS_VALID_PDN_TYPE(ucPdnType)\
    (((ucPdnType) >= CMMCA_IP_TYPE_IPV4) && ((ucPdnType) <= CMMCA_IP_TYPE_IPV4V6))

/* PDN 激活类型有效性判断 */
#define CMMCA_IS_VALID_PDN_REQUEST_TYPE(ucRequestType)\
    ((CMMCA_PDN_REQUEST_TYPE_INITIAL == (ucRequestType)) || (CMMCA_PDN_REQUEST_TYPE_HANDOVER == (ucRequestType)))

/* APN字符有效性判断 */
#define CMMCA_IS_VALID_APN_CHAR(ucApnCharacter)\
    ((('A' <= (ucApnCharacter)) && ('Z' >= (ucApnCharacter))) \
    || (('a' <= (ucApnCharacter)) && ('z' >= (ucApnCharacter))) \
    || (('0' <= (ucApnCharacter)) && ('9' >= (ucApnCharacter))) \
    || ('-' == (ucApnCharacter)) \
    || ('.' == (ucApnCharacter)))

/* APN首尾字符有效性判断 */
#define CMMCA_IS_VALID_APN_FIRST_AND_LAST_CHAR(ucApnCharacter)\
    ((('A' <= (ucApnCharacter)) && ('Z' >= (ucApnCharacter))) \
    || (('a' <= (ucApnCharacter)) && ('z' >= (ucApnCharacter))) \
    || (('0' <= (ucApnCharacter)) && ('9' >= (ucApnCharacter))))



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名   :CMMCA_IP_TYPE_ENUM
 枚举说明 :IP类型
 1.日    期   : 2014年01月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_IP_TYPE_ENUM
{
    CMMCA_IP_TYPE_IPV4                  = 0x01,
    CMMCA_IP_TYPE_IPV6                  = 0x02,
    CMMCA_IP_TYPE_IPV4V6                = 0x03,

    CMMCA_IP_TYPE_BUTT
};

typedef VOS_UINT8 CMMCA_IP_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_PDN_REQUEST_TYPE_ENUM
 枚举说明 :PDN连接请求类型
 1.日    期   : 2014年01月08日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_PDN_REQUEST_TYPE_ENUM
{
    CMMCA_PDN_REQUEST_TYPE_INITIAL      = 0x01,
    CMMCA_PDN_REQUEST_TYPE_HANDOVER     = 0x03,

    CMMCA_PDN_REQUEST_TYPE_BUTT
};

typedef VOS_UINT8 CMMCA_PDN_REQUEST_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_PDP_STATE_ENUM_UINT8
 枚举说明 :PDP状态
 1.日    期   : 2014年01月17日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_PDP_STATE_ENUM
{
    CMMCA_PDP_STATE_INACTIVE            = 0,
    CMMCA_PDP_STATE_ACTIVE              = 1,

    CMMCA_PDP_STATE_BUTT
};
typedef VOS_UINT8  CMMCA_PDP_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_PDN_SEL_BEARER_CTRL_MODE_ENUM_UINT8
 枚举说明 :PDN承载控制模式
 1.日    期   : 2014年01月27日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_PDN_SEL_BEARER_CTRL_MODE_ENUM
{
    CMMCA_PDN_SEL_BEARER_CTRL_MODE_UE            = 1,
    CMMCA_PDN_SEL_BEARER_CTRL_MODE_NW_AND_UE     = 2,

    CMMCA_PDN_SEL_BEARER_CTRL_MODE_BUTT
};
typedef VOS_UINT8  CMMCA_PDN_SEL_BEARER_CTRL_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名   :CMMCA_CONN_STATUS_ENUM_UINT8
 枚举说明 :PDP的连接状态
 1.日    期   : 2014年01月17日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
enum CMMCA_CONN_STATUS_ENUM
{
    CMMCA_CONN_STATUS_CONNING,
    CMMCA_CONN_STATUS_CONNED,
    CMMCA_CONN_STATUS_DISCING,
    CMMCA_CONN_STATUS_INTERNAL_DISCING,                                         /* RA超时后，内部去激活 */
    CMMCA_CONN_STATUS_BUTT
};
typedef VOS_UINT8  CMMCA_CONN_STATUS_ENUM_UINT8;




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
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : CMMCA_IP_ADDRESS_STRU
 结构说明  : IP 地址
 1.日    期   : 2014年01月17日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    CMMCA_IP_TYPE_ENUM_UINT8            enIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[CMMCA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[CMMCA_IPV6_ADDR_LEN];
}CMMCA_IP_ADDRESS_STRU;

/*****************************************************************************
 结构名    : CMMCA_PDP_IPV4_DNS_STRU
 结构说明  : IPV4 DNS地址
 1.日    期   : 2014年01月17日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns   : 1;
    VOS_UINT32                          bitOpSecDns   : 1;
    VOS_UINT32                          bitOpSpare    : 30;

    VOS_UINT8                           aucPriDns[CMMCA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[CMMCA_IPV4_ADDR_LEN];
}CMMCA_PDP_IPV4_DNS_STRU;

/*****************************************************************************
 结构名    : CMMCA_PDP_IPV4_PCSCF_STRU
 结构说明  : IPV4 P-CSCF地址
 1.日    期   : 2014年01月17日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimPcscfAddr[CMMCA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[CMMCA_IPV4_ADDR_LEN];
}CMMCA_PDP_IPV4_PCSCF_STRU;

/*****************************************************************************
 结构名称: CMMCA_PDP_GATEWAY_STRU
 结构说明: 网关地址结构
 1.日    期   : 2014年01月17日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpGateWayAddr    : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           aucGateWayAddr[CMMCA_IPV4_ADDR_LEN];
}CMMCA_PDP_GATEWAY_STRU;

/*****************************************************************************
 结构名    : CMMCA_PDP_IPV6_DNS_STRU
 结构说明  : IPV6 DNS地址
 1.日    期   : 2014年01月17日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpSpare      : 30;

    VOS_UINT8                           aucPriDns[CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDns[CMMCA_IPV6_ADDR_LEN];
}CMMCA_PDP_IPV6_DNS_STRU;

/*****************************************************************************
 结构名    : CMMCA_PDP_IPV6_PCSCF_STRU
 结构说明  : IPV6 P-CSCF地址
 1.日    期   : 2014年01月17日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimPcscfAddr[CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[CMMCA_IPV6_ADDR_LEN];
}CMMCA_PDP_IPV6_PCSCF_STRU;


/*****************************************************************************
 结构名    : CMMCA_SEL_SDF_PARA_STRU
 结构说明  : 选中拨号的SDF信息
 1.日    期   : 2014年01月17日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLinkdCid       : 1;
    VOS_UINT32                          bitOpPdnType        : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpGwAuthInfo     : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpIpv4AddrAllocType: 1;
    VOS_UINT32                          bitOpPcscfDiscovery : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpSpare          : 24;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucLinkdCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdnType;
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAllocType;

    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           ucReserved;

    TAF_PDP_APN_STRU                    stApnInfo;
    TAF_GW_AUTH_STRU                    stGwAuthInfo;
}CMMCA_SEL_SDF_PARA_STRU;

/*****************************************************************************
 结构名    : CMMCA_PDP_INFO_STRU
 结构说明  : PDP信息
 1.日    期   : 2014年01月23日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitOpSpare          : 31;

    VOS_UINT8                           ucCid;                                  /* Cid */
    VOS_UINT8                           ucRabId;                                /* RabId */
    CMMCA_PDP_STATE_ENUM_UINT8          enPdpState;                             /* PDP 状态:激活，未激活 */
    VOS_UINT8                           aucReserved1[1];

    CMMCA_IP_ADDRESS_STRU               stPdpAddr;

    CMMCA_PDP_GATEWAY_STRU              stPdpGateWay;                           /* IPV4 Gateway信息 */
    CMMCA_PDP_IPV4_DNS_STRU             stPdpIpv4Dns;                           /* IPV4 DNS信息 */
    CMMCA_PDP_IPV4_PCSCF_STRU           stPdpIpv4Pcscf;                         /* IPV4 P-CSCF信息 */

    VOS_UINT8                           aucPdpIpv6IfId[CMMCA_IPV6_INTERFACE_ID_BYTE_LEN];   /* IPV6 Interface id信息 */

    CMMCA_PDP_IPV6_DNS_STRU             stPdpIpv6Dns;                           /* IPV6 DNS信息 */
    CMMCA_PDP_IPV6_PCSCF_STRU           stPdpIpv6Pcscf;                         /* IPV6 P-CSCF信息 */
}CMMCA_PDP_INFO_STRU;

/*****************************************************************************
 结构名    : CMMCA_PDN_CONN_ENTITY_STRU
 结构说明  : PDN连接实体
 1.日    期   : 2014年01月18日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsedFlg;                              /* 实体分配标志 */

    VOS_UINT8                           ucPdnId;                                /* 请求的PDN ID */
    CMMCA_IP_TYPE_ENUM_UINT8            enUserPdnType;                          /* 请求的PDN类型 */
    CMMCA_PDN_REQUEST_TYPE_ENUM_UINT8   enPdnReqType;                           /* 请求的request type */

    CMMCA_CONN_STATUS_ENUM_UINT8        enConnStatus;                           /* 记录连接状态 */

    VOS_UINT8                           aucReserved[3];

    CMMCA_SEL_SDF_PARA_STRU             stSelSdfPara;                           /* 选中拨号的SDF信息 */

    CMMCA_PDP_INFO_STRU                 stPdpInfo;
}CMMCA_PDN_CONN_ENTITY_STRU;

/*****************************************************************************
 结构名    : CMMCA_PKT_CTX_STRU
 结构说明  : PACKET DATA相关的上下文
 1.日    期   : 2014年01月18日
   作    者   : l60609
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    /* 保存和PDN关联的实体索引 */
    VOS_UINT8                           aucPdnToIndexTbl[CMMCA_PDN_ID_MAX + 1];

    VOS_UINT8                           aucReserved[3];

    /* PDN实体 */
    CMMCA_PDN_CONN_ENTITY_STRU          astPdnConnEntity[CMMCA_PDN_CONN_ENTITY_NUM_MAX];
}CMMCA_PKT_CTX_STRU;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/



VOS_VOID CMMCA_PKT_InitCtx(VOS_VOID);

CMMCA_PKT_CTX_STRU* CMMCA_PKT_GetCtxAddr(VOS_VOID);

CMMCA_PDN_CONN_ENTITY_STRU* CMMCA_PKT_GetPdnEntityAddr(
    VOS_UINT8                           ucIndex
);

CMMCA_CONN_STATUS_ENUM_UINT8 CMMCA_PKT_GetConnStatus(
    VOS_UINT8                           ucIndex
);

VOS_VOID CMMCA_PKT_SetConnStatus(
    VOS_UINT8                           ucIndex,
    CMMCA_CONN_STATUS_ENUM_UINT8        enConnStatus
);

VOS_VOID CMMCA_PKT_SetUserPdnType(
    VOS_UINT8                           ucIndex,
    CMMCA_IP_TYPE_ENUM_UINT8            enPdnType
);

CMMCA_IP_TYPE_ENUM_UINT8 CMMCA_PKT_GetUserPdnType(
    VOS_UINT8                           ucIndex
);

VOS_VOID CMMCA_PKT_SetPdnRequestType(
    VOS_UINT8                           ucIndex,
    CMMCA_PDN_REQUEST_TYPE_ENUM_UINT8   enPdnReqType
);

VOS_VOID CMMCA_PKT_SavePdpInfo(
   CMMCA_PDP_INFO_STRU                *pstPdpInfo,
   TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
);

VOS_VOID CMMCA_PKT_SaveIpv6RaInfo(
    CMMCA_PDP_INFO_STRU                *pstPdpInfo,
    TAF_PS_IPV6_INFO_IND_STRU          *pstIpv6InfoInd
);

VOS_VOID CMMCA_PKT_FreePdnConnEntity(
    VOS_UINT8                           ucPdnId
);

VOS_UINT8 CMMCA_PKT_FindPdnConnEntityIndex(
    VOS_UINT8                           ucPdnId
);

VOS_VOID CMMCA_PKT_SavePdnConnEntityIndex(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucIndex
);

VOS_VOID CMMCA_PKT_AssignPdnConnEntity(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                          *pucIndex
);


#endif


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

#endif /* end of CmmcaCtxPkt.h */

