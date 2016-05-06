

#ifndef __ATCTXPACKET_H__
#define __ATCTXPACKET_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "v_id.h"
#include "AtTypeDef.h"
#include "MnClient.h"
#include "TafApsApi.h"
/* Added by wx270776 for OM融合, 2015-7-25, begin */
#include "TafNvInterface.h"
/* Added by wx270776 for OM融合, 2015-7-25, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define AT_IPV6_CAPABILITY_IPV4_ONLY            (1)
#define AT_IPV6_CAPABILITY_IPV6_ONLY            (2)
#define AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP  (4)
#define AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP  (8)

/* PS域呼叫最大个数 */
#define AT_PS_MAX_CALL_NUM              (3)


#define AT_PS_RABID_OFFSET              (5)                 /* RABID偏移 */
#define AT_PS_RABID_MAX_NUM             (11)                /* RABID数量 */
#define AT_PS_MIN_RABID                 (5)                 /* RABID最小值 */
#define AT_PS_MAX_RABID                 (15)                /* RABID最大值 */
#define AT_PS_INVALID_RABID             (0xFF)              /* RABID无效值 */
#define AT_PS_RABID_MODEM_1_MASK        (0x40)

#define IPV6_ADDRESS_TEST_MODE_ENABLE                    (0x55aa55aa)           /* 0x55aa55aa值IPV6地址为测试模式 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum AT_PDP_STATE_ENUM
{
    AT_PDP_STATE_IDLE                = 0,
    AT_PDP_STATE_ACTED               = 1,
    AT_PDP_STATE_ACTING              = 2,
    AT_PDP_STATE_DEACTING            = 3,
    AT_PDP_STATE_BUTT
};
typedef VOS_UINT8 AT_PDP_STATE_ENUM_U8;

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
 结构名称   : AT_DIAL_PARAM_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 保存用户拨号参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    VOS_UINT8                           ucPdpTypeValidFlag;

    VOS_UINT8                           ucAPNLen;                               /*APN长度*/
    VOS_UINT8                           aucAPN[TAF_MAX_APN_LEN + 1];             /*指向APN指针*/

    VOS_UINT16                          usUsernameLen;                          /*username长度*/
    VOS_UINT16                          usRsv3;
    VOS_UINT8                           aucUsername[TAF_MAX_GW_AUTH_USERNAME_LEN];  /*指向username指针*/
    VOS_UINT8                           ucRsv4;

    VOS_UINT16                          usPasswordLen;                          /*password长度*/
    VOS_UINT16                          usRsv5;
    VOS_UINT8                           aucPassword[TAF_MAX_GW_AUTH_PASSWORD_LEN];  /*指向password指针*/
    VOS_UINT8                           ucRsv6;

    VOS_UINT16                          usAuthType;
    VOS_UINT8                           aucRsv7[2];                             /*填充位*/

    VOS_UINT32                          ulIPv4ValidFlag;
    VOS_UINT8                           aucIPv4Addr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulPrimIPv4DNSValidFlag;
    VOS_UINT8                           aucPrimIPv4DNSAddr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulSndIPv4DNSValidFlag;
    VOS_UINT8                           aucSndIPv4DNSAddr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulPrimIPv4WINNSValidFlag;
    VOS_UINT8                           aucPrimIPv4WINNSAddr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulSndIPv4WINNSValidFlag;
    VOS_UINT8                           aucSndIPv4WINNSAddr[TAF_MAX_IPV4_ADDR_STR_LEN];

    VOS_UINT32                          ulPrimIPv6DNSValidFlag;
    VOS_UINT8                           aucPrimIPv6DNSAddr[TAF_IPV6_ADDR_LEN];

    VOS_UINT32                          ulSndIPv6DNSValidFlag;
    VOS_UINT8                           aucSndIPv6DNSAddr[TAF_IPV6_ADDR_LEN];

    VOS_UINT32                          ulPrimIPv6WINNSValidFlag;
    VOS_UINT8                           aucPrimIPv6WINNSAddr[TAF_IPV6_ADDR_LEN];

    VOS_UINT32                          ulSndIPv6WINNSValidFlag;
    VOS_UINT8                           aucSndIPv6WINNSAddr[TAF_IPV6_ADDR_LEN];

}AT_DIAL_PARAM_STRU;

/*****************************************************************************
 结构名    : AT_IPV6_DHCP_PARAM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6类型的PDP激活参数指结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv6PriDns   : 1;
    VOS_UINT32                          bitOpIpv6SecDns   : 1;
    VOS_UINT32                          bitOpIpv6PriPCSCF : 1;
    VOS_UINT32                          bitOpIpv6SecPCSCF : 1;
    VOS_UINT32                          bitOpIpv6ThiPCSCF : 1;
    VOS_UINT32                          bitOpIpv6Spare    : 27;

    VOS_UINT8                           ucRabId;                                /* RAB标识，取值范围:[5,15] */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucIpv6Addr[TAF_IPV6_ADDR_LEN];      /* 从 PDP上下文带来的IPV6地址长度，不包括":" */

    VOS_UINT8                           aucIpv6PrimDNS[TAF_IPV6_ADDR_LEN];   /* 从 PDP上下文带来的IPV6主DNS长度，不包括":" */
    VOS_UINT8                           aucIpv6SecDNS[TAF_IPV6_ADDR_LEN];    /* 从 PDP上下文带来的IPV6副DNS长度，不包括":" */
    VOS_UINT8                           aucPrimPcscfAddr[TAF_IPV6_ADDR_LEN]; /* IPV6的主P-CSCF，主机序 */
    VOS_UINT8                           aucSecPcscfAddr[TAF_IPV6_ADDR_LEN];  /* IPV6的副P-CSCF，主机序 */
    VOS_UINT8                           aucThiPcscfAddr[TAF_IPV6_ADDR_LEN];  /* IPV6的第三P-CSCF，主机序 */
}AT_IPV6_DHCP_PARAM_STRU;

/*****************************************************************************
 结构名    : AT_IPV4_DHCP_PARAM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV4类型的PDP激活参数指结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PriDns   : 1;
    VOS_UINT32                          bitOpIpv4SecDns   : 1;
    VOS_UINT32                          bitOpIpv4PriWINNS : 1;
    VOS_UINT32                          bitOpIpv4SecWINNS : 1;
    VOS_UINT32                          bitOpIpv4PriPCSCF : 1;
    VOS_UINT32                          bitOpIpv4Secpcscf : 1;
    VOS_UINT32                          bitOpIpv4Thipcscf : 1;
    VOS_UINT32                          bitOpSpare        : 25;

    VOS_UINT8                           ucRabId;                                /* RAB标识，取值范围:[5,15] */
    VOS_UINT8                           aucRsv1[3];
    VOS_UINT32                          ulIpv4Addr;                             /* IPV4的IP地址，主机序 */
    VOS_UINT32                          ulIpv4NetMask;                          /* IPV4的掩码，主机序 */
    VOS_UINT32                          ulIpv4GateWay;                          /* IPV4的网关地址，主机序 */


    VOS_UINT32                          ulIpv4PrimDNS;                          /* IPV4的主DNS，主机序 */
    VOS_UINT32                          ulIpv4SecDNS;                           /* IPV4的主DNS，主机序 */
    VOS_UINT32                          ulIpv4PrimWINNS;                        /* IPV4的主WINNS，主机序 */
    VOS_UINT32                          ulIpv4SecWINNS;                         /* IPV4的副WINNS，主机序 */
    VOS_UINT32                          ulIpv4PrimPCSCF;                        /* IPV4的主P-CSCF，主机序 */
    VOS_UINT32                          ulIpv4SecPCSCF;                         /* IPV4的副P-CSCF，主机序 */
    VOS_UINT32                          ulIpv4ThiPCSCF;                         /* IPV4的第三P-CSCF，主机序 */
    VOS_UINT8                           aucRsv2[4];
}AT_IPV4_DHCP_PARAM_STRU;


/*****************************************************************************
 结构名  : AT_PS_USER_INFO_STRU
 结构说明: PS域用户信息结构

  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增
*****************************************************************************/
typedef struct
{
    AT_CLIENT_TAB_INDEX_UINT8           enPortIndex;
    AT_CLIENT_TAB_INDEX_UINT8           enUserIndex;
    AT_USER_TYPE                        ucUsrType;
    VOS_UINT8                           ucUsrCid;
} AT_PS_USER_INFO_STRU;

/*****************************************************************************
 结构名称   : AT_IPV6_RA_INFO_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : RA消息中相关参数结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpLanAddr            : 1;
    VOS_UINT32                          bitOpPrefixAddr         : 1;
    VOS_UINT32                          bitOpMtuSize            : 1;
    VOS_UINT32                          bitOpPreferredLifetime  : 1;
    VOS_UINT32                          bitOpValidLifetime      : 1;
    VOS_UINT32                          bitOpSpare              : 27;


    VOS_UINT8                           aucLanAddr[TAF_IPV6_ADDR_LEN];       /* IPv6 路由器LAN端口地址 */
    VOS_UINT8                           aucPrefixAddr[TAF_IPV6_ADDR_LEN];    /* IPv6前缀 */
    VOS_UINT32                          ulPrefixBitLen;                         /* IPv6前缀长度 */
    VOS_UINT32                          ulMtuSize;                              /* RA消息中广播的IPv6的MTU的取值 */
    VOS_UINT32                          ulPreferredLifetime;                    /* IPv6前缀的Preferred lifetime */
    VOS_UINT32                          ulValidLifetime;                        /* IPv6前缀的Valid lifetime */
} AT_IPV6_RA_INFO_STRU;


/*消息处理函数指针*/
typedef VOS_VOID (*AT_PS_RPT_CONN_RSLT_FUNC)(\
    VOS_UINT8                           ucCid, \
    VOS_UINT8                           ucPortIndex, \
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType);

/*****************************************************************************
 结构名    : AT_PS_REPORT_CONN_RESULT_STRU
 结构说明  : 消息与对应处理函数的结构

  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增
*****************************************************************************/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_RPT_CONN_RSLT_FUNC            pRptConnRsltFunc;
}AT_PS_REPORT_CONN_RESULT_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/*消息处理函数指针*/
typedef VOS_VOID (*AT_PS_RPT_END_RSLT_FUNC)(\
    VOS_UINT8                           ucCid, \
    VOS_UINT8                           ucPortIndex, \
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType, \
    TAF_PS_CAUSE_ENUM_UINT32            enCause);

/*****************************************************************************
 结构名    : AT_PS_REPORT_END_RESULT_STRU
 结构说明  : 消息与对应处理函数的结构

  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增
*****************************************************************************/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_RPT_END_RSLT_FUNC             pRptEndRsltFunc;
}AT_PS_REPORT_END_RESULT_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/*消息处理函数指针*/
typedef VOS_VOID (*AT_PS_REG_FC_POINT_FUNC)(\
    VOS_UINT8                           ucCid, \
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent);

/*****************************************************************************
 结构名    : AT_PS_REG_FC_POINT_STRU
 结构说明  : 消息与对应处理函数的结构

  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增
*****************************************************************************/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_REG_FC_POINT_FUNC             pRegFcPoint;
}AT_PS_REG_FC_POINT_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/*消息处理函数指针*/
typedef VOS_VOID (*AT_PS_DEREG_FC_POINT_FUNC)(\
    VOS_UINT8                           ucCid, \
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent);

/*****************************************************************************
 结构名    : AT_PS_DEREG_FC_POINT_STRU
 结构说明  : 消息与对应处理函数的结构

  1.日    期   : 2013年4月26日
    作    者   : L60609
    修改内容   : C50 IPv6 项目新增
*****************************************************************************/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_DEREG_FC_POINT_FUNC           pDeRegFcPoint;
}AT_PS_DEREG_FC_POINT_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/*消息处理函数指针*/
typedef VOS_VOID (*AT_PS_SND_PDP_ACT_IND_FUNC)(\
    VOS_UINT8                           ucCid, \
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent, \
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType);

/*****************************************************************************
 结构名    : AT_PS_SND_PDP_ACT_IND_STRU
 结构说明  : 消息与对应处理函数的结构

  1.日    期   : 2013年4月26日
    作    者   : L60609
    修改内容   : C50 IPv6 项目新增
*****************************************************************************/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_SND_PDP_ACT_IND_FUNC          pSndPdpActInd;
}AT_PS_SND_PDP_ACT_IND_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/*消息处理函数指针*/
typedef VOS_VOID (*AT_PS_SND_PDP_DEACT_IND_FUNC)(\
    VOS_UINT8                           ucCid, \
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent, \
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType);

/*****************************************************************************
 结构名    : AT_PS_SND_PDP_DEACT_IND_STRU
 结构说明  : 消息与对应处理函数的结构

  1.日    期   : 2013年4月26日
    作    者   : L60609
    修改内容   : C50 IPv6 项目新增
*****************************************************************************/
/*lint -e958 -e959 修改人:l60609;原因:64bit*/
typedef struct
{
    AT_USER_TYPE                        ucUsrType;
    AT_PS_SND_PDP_DEACT_IND_FUNC        pSndPdpDeActInd;
}AT_PS_SND_PDP_DEACT_IND_STRU;
/*lint +e958 +e959 修改人:l60609;原因:64bit*/

/*****************************************************************************
 结构名    : AT_PS_DATA_CHANL_CFG_STRU
 结构说明  : AT^CHDATA配置的数传通道信息

  1.日    期   : 2013年4月24日
    作    者   : l60609
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsed;                                 /* 指定CID是否已经通过CHDATA配置了数传通道，VOS_TRUE:已经配置；VOS_FALSE:未配置 */
    VOS_UINT32                          ulRmNetId;                              /* 数据通道ID
                                                                                   HSIC通道 :UDI_ACM_HSIC_ACM1_ID，UDI_ACM_HSIC_ACM3_ID和UDI_ACM_HSIC_ACM5_ID，如果未配置则为无效值UDI_INVAL_DEV_ID
                                                                                   VCOM通道 :RNIC_RMNET_ID_0 ~ RNIC_RMNET_ID_4
                                                                                   */
    VOS_UINT32                          ulRmNetActFlg;                          /* 指定CID是否已经PDP激活，VOS_TRUE:已经激活；VOS_FALSE:未激活 */
}AT_PS_DATA_CHANL_CFG_STRU;

#if (FEATURE_ON == FEATURE_IPV6)

/*****************************************************************************
 结构名  : AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU
 结构说明: IPv4v6双栈拨号回退处理扩展原因值(PS Cause)结构体

  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCauseNum;
    VOS_UINT8                           aucReserved[4];
    TAF_PS_CAUSE_ENUM_UINT32            aenPsCause[TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM];
} AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU;
#endif

/*****************************************************************************
 结构名  : AT_PS_CALL_ENTITY_STRU
 结构说明: PS域呼叫实体结构

  1.日    期   : 2012年12月10日
    作    者   : Y00213812
    修改内容   : C50 IPv6 项目新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsedFlg;          /* 呼叫实体分配标志 */
    TAF_PDP_TYPE_ENUM_UINT8             enCurrPdpType;      /* 当前呼叫类型 */
    VOS_UINT8                           aucRsv1[3];         /* 保留位 */
    AT_PS_USER_INFO_STRU                stUserInfo;         /* 呼叫实体用户信息 */
    AT_DIAL_PARAM_STRU                  stUsrDialParam;     /* 呼叫实体拨号参数 */

    VOS_UINT8                           ucIpv4Cid;          /* IPv4 CID */
    AT_PDP_STATE_ENUM_U8                enIpv4State;        /* IPv4 状态 */
    VOS_UINT8                           aucRsv2[2];         /* 保留位 */
    AT_IPV4_DHCP_PARAM_STRU             stIpv4DhcpInfo;     /* IPv4 DHCP信息 */

#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           ucIpv6Cid;          /* IPv6 CID */
    AT_PDP_STATE_ENUM_U8                enIpv6State;        /* IPv6 状态 */
    VOS_UINT8                           aucRsv3[2];         /* 保留位 */
    AT_IPV6_RA_INFO_STRU                stIpv6RaInfo;       /* IPv6 路由公告信息 */
    AT_IPV6_DHCP_PARAM_STRU             stIpv6DhcpInfo;     /* IPv6 DHCP信息 */
#endif

    VOS_UINT8                           ucCdmaFlg;
    VOS_UINT8                           ucPppId;
    VOS_UINT8                           aucRsv4[6];         /* 保留 */

} AT_PS_CALL_ENTITY_STRU;

/*****************************************************************************
 结构名  : AT_COMM_PS_CTX_STRU
 结构说明: PS域公共上下文结构

  1.日    期   : 2013年4月24日
    作    者   : l60609
    修改内容   : V9R1 IPv6&TAF/SM接口优化项目新增
  2.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目修改
*****************************************************************************/
typedef struct
{
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           ucIpv6Capability;
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulIpv6AddrTestModeCfg;

    /* 保存用户定制的用于回退处理的PS域原因值 */
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU  stIpv6BackProcExtCauseTbl;
#endif

    VOS_UINT8                           ucSharePdpFlag;
    VOS_UINT8                           aucReserved2[7];

    VOS_INT32                           lSpePort;
    VOS_UINT32                          ulIpfPortFlg;

}AT_COMM_PS_CTX_STRU;

/*****************************************************************************
 结构名  : AT_MODEM_PS_CTX_STRU
 结构说明: PS域MODEM相关上下文结构

  1.日    期   : 2013年4月24日
    作    者   : l60609
    修改内容   : V9R1 IPv6&TAF/SM接口优化项目新增

  2.日    期   : 2013年11月11日
    作    者   : A00165503
    修改内容   : DTS2013110900839: 增加承载IP与RABID映射成员
*****************************************************************************/
typedef struct
{
    /* 保存和CID关联的PS域呼叫实体的索引 */
    VOS_UINT8                           aucCidToIndexTbl[TAF_MAX_CID + 1];

    /* PS域呼叫实体 */
    AT_PS_CALL_ENTITY_STRU              astCallEntity[AT_PS_MAX_CALL_NUM];

    /* CID与数传通道的对应关系 */
    AT_PS_DATA_CHANL_CFG_STRU           astChannelCfg[TAF_MAX_CID + 1];

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* PS域呼叫错误码 */
    TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    /* IP地址与RABID的映射表, IP地址为主机序 */
    VOS_UINT32                          aulIpAddrRabIdMap[AT_PS_RABID_MAX_NUM];

} AT_MODEM_PS_CTX_STRU;


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

#endif /* end of AtCtxPacket.h */
