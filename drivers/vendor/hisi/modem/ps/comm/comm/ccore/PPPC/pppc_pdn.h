/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pppc_pdn.h
  版 本 号   : 初稿
  作    者   : w00316385
  生成日期   : 2015年05月29日
  最近修改   :
  功能描述   : PDN相关的定义
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月29日
    作    者   : w00316385
    修改内容   : 创建文件

******************************************************************************/

#ifndef _PPPC_PDN_H_
#define _PPPC_PDN_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define PDN_IPV6ADDR_LEN        16      /* IPV6地址长度 */
/*每个PDN最多支持NetWrok子状态机数 */
#define MAX_STACK_PER_PDN  E_PDN_STACK_TYPE_BUTT
#define IP_POOL_NAME_LEN        31
#define PDN_MIP_SHAREKEY_LEN    32
#define PDN_USER_PROFILE_NAME_LENGTH 64
#define HSGW_MAX_APN_NAME_LEN   100
#define HSGW_MAX_PCO_LEN        253
#define RELTMR_T VOS_UINT32
#define A11_MAX_PDN_NUM         15      /* 每个RP最大允许的PDN个数 */
#define VSNCP_MAX_AMBR_LEN      8


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum
{
    E_PDN_STACK_TYPE_IPV4,
    E_PDN_STACK_TYPE_IPV6,

    E_PDN_STACK_TYPE_BUTT
}PDN_STACK_TYPE_E;

/*****************************************************************************
  4 UNION定义
*****************************************************************************/

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/* PPP通知PDN NCP UP时的参数 */
typedef struct
{
    VOS_UINT32 ulIpv4Addr;
    UCHAR aucIpV6Addr[PDN_IPV6ADDR_LEN];      /* IPv6CP协商的地址 */
}PDN_PPP_NCP_UP_S;

/* PDN的更新消息头 */
typedef struct
{
    VOS_UINT32 ulUpdateType;     /* 更新类型, PDN_UPDATE_TYPE_E */
    VOS_UINT32 ulUpdateMask;     /* 发生更新的掩码 */
}PDN_UPDATE_MSGHEAD_S;

/* PPP在收到PDN初始建立请求的VSNCP REQ消息时的接口参数 */
typedef struct
{
    PDN_UPDATE_MSGHEAD_S stHead;
    VOS_UINT32 ulIpAddr;

    VOS_UINT32 ulTotalMsgLen; /* vsncp消息总长度 */
    VOS_UINT16 usVsncpMsgBodyLen;        /* 原始的VSNCP请求消息长度 */

    UCHAR ucPdnId;
    UCHAR ucPdnType;
    UCHAR ucAttchType;
    UCHAR ucPcoLen;

    UCHAR ucErrorCode;

    UCHAR aucIpv6Addr[PDN_IPV6ADDR_LEN];

    UCHAR szApn[HSGW_MAX_APN_NAME_LEN + 1];
    UCHAR szPco[HSGW_MAX_PCO_LEN];

    UCHAR aucAMBR[VSNCP_MAX_AMBR_LEN];
    UCHAR ucAMBRLen;

    UCHAR aucIpv4DefaultRouterAddress[CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN];
    UCHAR ucAddressAllocCause;

    UCHAR aucVsncpMsgBody[1];       /* 终端请求的原始VSNCP消息 */
}PDN_PPP_VSNCP_REQ_S;

typedef struct
{
    HTIMER        ulTimeOutID;                /* config request报文的定时器 */
    VOS_UINT32           ulPmipv6UpdTimeOutID;       /* 获取PCO的定时器 */
    VOS_UINT32           ulReconnectDnsTimeOutID;    /* 重建PDN时等待DNS的定时器 */
    SHORT           sRetransmits;               /* config request报文重传次数 */
    UCHAR           ucState;                    /* 协议状态 */
    UCHAR           ucPktId;                    /* 本协议当前报文的ID */
    UCHAR           ucPDNID;
    UCHAR           ucPdnReleaseCode;
    UCHAR           ucUsedFlag : 1;
    UCHAR           ucRenegoFlag : 1;
    UCHAR           ucGetPCOFlag : 1;           /* 正在获取PCO的标记 */
    UCHAR           ucStartingFlag : 1;
    UCHAR           ucStoppingFlag : 1;
    VOS_UINT8       aucReserved[1];
}PDN_VSNCP_INFO_S;

typedef struct
{
    UCHAR  *pucVsncpReq;                        /* 缓存的VSNCP消息 */
    UCHAR  *pucFlowInfo;                        /* 缓存的RESV QosCheck消息内容 */
    UCHAR  *pucPcrfcReq;                        /* 缓存的PCRFC请求消息 PCRFC_REQ_LIST_INFO*/

    UCHAR  aucLmaAddrV6[PDN_IPV6ADDR_LEN];      /* PGW的IPv6地址 */
    UCHAR  aucLinkLocalAddr[PDN_IPV6ADDR_LEN];  /* 从PGW获取到的LinkLocalAddr */

    VOS_UINT32  ulLmaAddrV4;                 /* PGW的IPv4地址 */
    VOS_UINT32  ulRouterAddrV4;

    VOS_UINT32  ulChargingId;                /* PGW的ChargingId */
    VOS_UINT32  ulGreKey;                    /* PGW分配的下行GRE Key*/

    VOS_UINT32  ulApnAmbrUL;                 /* AAA授权的AMBR */
    VOS_UINT32  ulApnAmbrDL;                 /* AAA授权的AMBR */

    VOS_UINT32  ulWtQosCheckTimerId;         /* 等待PCRFC的QosCheck应答定时器 */

    VOS_UINT16 usApnIndex;                  /* APN配置索引 */
    VOS_UINT16 usChargeCharacter;           /* AAA授权的3GPP Charge character */
    UCHAR  ucPdnId;                     /* PDN ID, 0~14 */
    UCHAR  ucQci;                       /* AAA授权的QCI */
    UCHAR  ucArp;                       /* AAA授权的ARP */
    UCHAR  ucPdnIndicatorCause;
    UCHAR  ucPdnTypeIndicator   : 2,    /* PDN IP类型标识 */
           ucDelayFlag          : 1,    /* 延时分配标识 */
           ucLmaAddrType        : 1,    /* PGW地址类型标识 */
           ucDefAPNFlag         : 1,    /* 是否是default apn标识 */
           ucApnAmbrDLFlag      : 1,    /* AAA下发ambr dl标记 */
           ucApnAmbrULFlag      : 1,    /* AAA下发ambr ul标记 */
           ucNotifyDhcpRelFlag   : 1;    /* 通知DHCP删除标记 */
    UCHAR  ucAttchType;
    UCHAR  ucFQDNType;                  /* FQDN构造类型 */
    UCHAR  ucbit1L2CReconnectFlg : 1,  /* L切C场景重建PDN连接 */
           ucbit7Res             : 7;
    VOS_UINT32  ulSendDnsTimeStamp;

    CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_UINT8                  enAttachType;
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType;
    VOS_UINT8                                               ucAddressAllocCause;
    VOS_UINT8                                               aucReserved[1];
    CNAS_CTTF_EHRPD_APN_STRU                                stApn;
    CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU                        stPdnAddress;
    CNAS_CTTF_EHRPD_PCO_STRU                                stPco;
    VOS_UINT8                                               aucIpv4DefaultRouterAddress[CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN];

    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16 enErrorCode;
    VOS_UINT8                              aucReserved1[2];
    CNAS_CTTF_EHRPD_APN_AMBR_STRU          stApnAmbr;

    PDN_VSNCP_INFO_S stVSNCP;
}PDN_EHRPD_INFO_S;


typedef struct
{
    VOS_UINT16 usV4PoolIdx;
    UCHAR  ucV4AllocType;
    UCHAR  ucV4SectionNum;
    UCHAR  szV4PoolName[IP_POOL_NAME_LEN + 1];
    VOS_UINT16 usV6PoolIdx;
    UCHAR  ucV6AllocType;
    UCHAR  ucV6SectionNum;
    UCHAR  szV6PoolName[IP_POOL_NAME_LEN + 1];
    UCHAR  ucV4LapNo;
    UCHAR  ucV4StaticIpRouteType;
    UCHAR  ucV6LapNo;
    UCHAR  ucV6StaticIpRouteType;
}PDN_SIP_INFO_S;

typedef struct
{
    VOS_UINT32 ulFaIpAddr;

    /*.................以下部分下A10表需要，由luofang添加，待确认..............*/
    VOS_UINT32 ulMipKey;

    VOS_UINT32 ulHaAddr;    /*Home Agent address*/

    /* add by luofang for a10table */
    UCHAR ucGRESwitchFlag:1;      /*GRESwitchFlag*/
    UCHAR ucRevTunnelFlag: 1;     /*support reverse tunnel*/
    UCHAR ucMsSendMethodFlag: 1;  /*MS send method on reverse tunnel*/
    UCHAR ucMiniFlag:1;           /*Mini encapsulation type*/
    UCHAR ucGreFlag:1;            /*Gre encapsulation type*/
    UCHAR ucReserv:3;             /*Gre encapsulation type*/

    UCHAR aucResved11[3];         /* 保留位 */

}PDN_MIP_INFO_S;

typedef struct
{
    VOS_UINT32  ulSpi;                               /* 与LMA之间认证的SPI */

    UCHAR  aucLmaAddrV6[PDN_IPV6ADDR_LEN];      /* LMA的IPv6地址 */
    UCHAR  aucLinkLocalAddr[PDN_IPV6ADDR_LEN];  /* 从PGW获取到的LinkLocalAddr */
    UCHAR  aucShareKey[PDN_MIP_SHAREKEY_LEN];   /* 共享密钥 */
}PDN_MIPV6_INFO_S;

typedef struct
{
    VOS_UINT32   ulIfIndex;      /* LAC的本端PI接口索引 */
    VOS_UINT32   ulLnsAddr;      /* LNS地址 */
    VOS_UINT32   ulLacAddr;      /* LAC本端地址 */
    VOS_UINT16  usLocalTid;     /* 本端TunnelId */
    VOS_UINT16  usLocalSid;     /* 本端SessionId */
    VOS_UINT16  usPeerTid;      /* 对端TunnelId */
    VOS_UINT16  usPeerSid;      /* 对端SessionId */
}PDN_L2TP_INFO_S;

typedef struct tag_PDN_MSG_BUFF_S
{
    struct tag_PDN_MSG_BUFF_S *pstNext;     /* 缓存链表指针 */

    VOS_UINT32 ulEvent;                          /* 消息码, PDN_MSGCODE_E */
    VOS_UINT32 ulMsgLen;                         /* 消息长度 */
    UCHAR aucMsgBody[4];                    /* 消息体 */

}PDN_MSG_BUFF_S;

typedef struct
{
    UCHAR ucFsmId;
    UCHAR ucState;
    UCHAR ucRev[2];

    VOS_UINT32 ulStateTimerId;
}PDN_SUBNET_FSM_S;

typedef struct
{
    VOS_UINT32 ulPdnIndex;           /* PDN上下文索引 */
    VOS_UINT32 ulRpIndex;            /* 关联的RP上下文索引 */

    VOS_UINT32 ulIpV4Addr;                       /* PDN的IPv4地址 */
    UCHAR aucIpV6Addr[PDN_IPV6ADDR_LEN];    /* PDN的IPv6地址 */
    VOS_UINT16 usV4VpnId;
    VOS_UINT16 usV6VpnId;

    VOS_UINT16 usDomainIdx;         /* Domain索引 */
    UCHAR ucPdnState;           /* PDN状态机状态, PDN_STATE_E */
    UCHAR ucPdnType;            /* PDN类型, PDN_TYPE_E */

    VOS_UINT32 ulPdnStateTimerId;    /* PDN状态机保护定时器 */
    VOS_UINT32 ulWtIpcpTimerId;      /* SIP/CMIP未确定时启动定时器等待终端主动协商定时器 */
    VOS_UINT32 ulPriV4Dns;
    VOS_UINT32 ulSecV4Dns;

    UCHAR szPriV6Dns[PDN_IPV6ADDR_LEN];
    UCHAR szSecV6Dns[PDN_IPV6ADDR_LEN];

    ///TODO:注意:若有新添加的字段，请在此之后添加，前面的字段做了hash索引，否则会出现建hash失败!!!

    VOS_UINT32 ulMipIndex;           /* PMIPv6/FA上下文索引 */
    VOS_UINT32 ulIpv6Timer;          /* IPV6 定时器id*/
    VOS_UINT32 ulTeidc;               /* PDN?TEIDC */
    VOS_UINT32 ulGREkey;              /* ulGREkey */

    UCHAR ucIpcpRetryNum;       /* 主动发送IPCP次数 */
    UCHAR ucIpv6RouteMsgNum;    /* ipv6模块使用，用于决定RA消息的发送间隔及次数 */
    UCHAR ucPdnCapability   : 2,    /* PDN当前能力 */
          ucInitCapbility   : 2,    /* PDSN初始能力 */
          ucIPv4NotifyLap   : 1,
          ucIPv6NotifyLap   : 1,
          ucLapRecycleIPv4  : 1,
          ucLapRecycleIPv6  : 1;
    UCHAR bIpV4Used         : 1,    /* IPv4栈使用状态 */
          bIpV6Used         : 1,    /* IPv6栈使用状态 */
          bIpV4StaticIp     : 1,    /* IPv4地址是否为静态地址 */
          bIpV6StaticIp     : 1,    /* IPv6地址是否为静态地址 */
          bNotifyPcrf       : 1,    /* 是否已经通知PCRFC */
          bNotifyCm         : 1,    /* 是否已经通知CM */
          bUsmRelFlag       : 1,    /* 是否为USM发起的退网 */
          bNotifyNcp        : 1;    /* 是否已经通知过VSNCP */

    UCHAR bIpV4GipiFlag     : 1,    /* IPv4 gipi表下发标记 VOS_TRUE:下发；VOS_FALSE:未下发 此标志不需要备份*/
          bIpV6GipiFlag     : 1,    /* IPv4 gipi表下发标记 VOS_TRUE:下发；VOS_FALSE:未下发 此标志不需要备份*/
          bIpv6NumFlg       : 1,    /* 是否统计过ipv6单栈用户数标志 此标志不需要备份*/
          bIpv4v6NumFlg     : 1,    /* 是否统计过ipv6双栈用户数标志 此标志不需要备份*/
          bNotifySm         : 1,    /* 是否已经通知SM */
          bNotifyMip        : 1,    /* 是否已经通知FA/MIPv6 */
          bRuleUpdFlag      : 1,    /* PCRF规则更新标记 该标记携带给SM*/
          bL2tpChkFlg       : 1;

    UCHAR bSeqLinkNo : 3,      /*用于记录分配teidc绑定的sequece链索引*/
          bIpv4ActiveState:1,  /* v4栈激活成功标记 pdsn形态有效，不需要备份但需要在备板进行恢复 */
          bIpv6ActiveState:1,  /* v6栈激活成功标记 pdsn形态有效，不需要备份但需要在备板进行恢复 */
          bEhrpdPdnFlag : 1,   /* ehrpd pdn表下发标记 VOS_TRUE:下发；VOS_FALSE:未下发 */
          b2Bcm : 2;        /*MS Support of Network Requested Bearer Control indicator */

    UCHAR bit1OflChrgEnabled : 1,  /* 该字段cm维护 */
          bit1OnlChrgEnabled : 1,
          bit1FbcChrgEnabled : 1,
          bit1PostpaidEnabled : 1,
          bit1SgwOflChrgEnabled : 1,
          bit1ActByTauOrHo : 1,        /* 是否是切换过来的，仅对hsgw用户有效 */
          bit1PcrfReferUserprofileId :1,   /*PCC用户在激活时下发了USERPROFILE ID是置 1 否则 置0 DTS2013082908329 */
          bit1PcrfQciFlag : 1;   /*ehrpd PCC 用户 , 如果pcrfC消息通知了qci 置1*/

    UCHAR ucTFTNumbers;

    PDN_MSG_BUFF_S *pstMsgBuffHead; /* 消息缓存队列头 */
    UCHAR       *pstUpdateMsg;      /* 更新消息，PCC用户等待PCRFC状态时需要先保存到上下文 */
    VOS_UINT32       ulTFTIndexArray[8];
    UCHAR       ucTFTtype[8];

    PDN_SUBNET_FSM_S astSubNetFsm[MAX_STACK_PER_PDN];   /* 网络子状态机，支持双栈 */
    /*lint -e658*/
    union
    {
        ///TODO:注意:以下几个为联合体，必须根据ucPdnType才能访问特定结构
        PDN_SIP_INFO_S      stSip;
        PDN_MIP_INFO_S      stMip;
        PDN_MIPV6_INFO_S    stPmipv6;
        PDN_L2TP_INFO_S     stL2tp;
        PDN_EHRPD_INFO_S    stEhrpd;
    };
    /*lint +e658*/
    /*PCC使用*/
    VOS_UINT32   ulFilterPrecedenceBitMap;      /*DTS2013070106753 网络侧下发filter 优先级维护字段 0~~31*/
    UCHAR   ucExtenPrecedence;
    UCHAR   ucBitUECreateV4FilterFlag : 1;                /* UE 发起过创建v4filter */
    UCHAR   ucBitUECreateV6FilterFlag : 1;                /* UE 发起过创建v6filter */
    UCHAR   ucBitReserved6: 6;
    UCHAR   ucReserve2[2];

    /* 计费相关属性 */
    VOS_UINT32   ulBearerIndex;
    VOS_UINT32   ulSessionIndex;

    VOS_UINT32   ulAcctInterimInterval;
    VOS_UINT32   ulIdleTimeout;

    VOS_UINT16  usUserProfileID;           /* 该用户匹配的User Profile ID*/
    VOS_UINT16  usPcrfGrpIndex;

    UCHAR   ucPcrfLocalIndex;
    UCHAR   ucFilterID;
    UCHAR   ucChargePropertyFlag    : 4;    /*用户的计费属性 1:FBC, 2: PDP*/
    UCHAR   ucChargeMode            : 4;    /*计费属性，0:离线计费 , 1:在线计费*/
    UCHAR   ucPreparedFlag          : 2;    /* 是否是预付费用户 */
    UCHAR   ucPccMode               : 2;
    UCHAR   ucAnyToAnyFlag          : 1;    /*PCRF是否下发了Any to Any的规则*/
    UCHAR   ucActiveStopIndication  : 1;    /*Accounting-Stop-triggered-by-Active-Stop-Indication */
    UCHAR   ucSmNotifyQosUpdFlag    : 1;
    UCHAR   ucPdnUserNumFlg         : 1;    /*是否统计过用户数标志 此标志不需要备份*/

    VOS_UINT32 ulpdpActTimeStampHig;
    VOS_UINT32 ulpdpActTimeStampLow;
    VOS_UINT32 ulpdpDelTimeStampHig;
    VOS_UINT32 ulpdpDelTimeStampLow;

    /*========SM使用=======*/
    VOS_UINT16   usUserGroupID;                 /*用户组ID，同时也是用户组级BWM_CB数组的索引号*/
    VOS_UINT16   usUserProfileGroupID;          /* 该用户匹配的User Profile Group ID*/
    VOS_UINT32    ulUsageRptCBIndex;             /*Added by liupeng for SM pdsn10.1 同步*/

    UCHAR    ucGroupLevelServiceType;       /* 记录用户组级的业务类型， tos /non-tos*/
    UCHAR    szUserProfileName[PDN_USER_PROFILE_NAME_LENGTH + 1];    /*User Profile名称的字符串 即charge-rule-base-name*/

    UCHAR    ucBwmSubscriberEnable  : 2;    /* 用户组级BWM带宽使能标志*/
    UCHAR    ucBwmGroupEnable       : 2;    /* 用户级BWM带宽使能标志 */
    UCHAR    ucBwmGlobalEnable      : 2;    /* 全局级BWM带宽使能标志 */
    UCHAR    ucAliasMarking         : 1;    /* Alias Marking使能标识,0:未使能,1:使能 */
    UCHAR    ucDDosFlag             : 1;    /* 防DDOS攻击使能,0:未使能,1:使能 */

    UCHAR    ucAAAUserProfileFlag   : 1;    /* 0表示userprofile是本地分配；1表示AAA指定*/
    UCHAR    ucAAAUserGroupFlag     : 1;    /*0表示usergroup是本地分配；1表示AAA指定*/
    UCHAR    ucActionSupport        : 1;
    UCHAR    ucUserClassAAAFlag     : 1;
    UCHAR    ucPCCNumFlag           : 1;    /*是否统计过pcc用户 此标志不需要备份*/
    UCHAR    ucBitRedirectRptTriggerFlag : 1;  /*只有PDSN支持*/
    UCHAR    ucbit1BwmUserFlg      : 1;  /* 是否是BWM用户,需要备份,用于平滑时性能统计恢复 */
    UCHAR    ucbit1BwmUserPerfFlg   : 1;  /* 是否对BWM进行统计,不需要备份,防止平滑还没有恢复时用户去活IPN调接口减 */
    VOS_UINT32    ulSlaveActiveTimeStemp; /* 备板创建PDN的时间戳,平滑时重新下发转发表项使用 */

    VOS_UINT16   usReleaseCode;        /* 去活原因，AM_RELEASE_CODE_E */
    UCHAR    ucBit2SelectType    : 2;   /*PCC使用字段: 0 基于pcrfgrp选择service；1:基于全局realmIdex选择索引；2:基于apn下的realm选择索引; 3:初始化值(又AM保证)*/
    UCHAR    ucBitV4CanForwardData :1;  /* v4数据能否允许转发标记vos_true允许，用于重协商场景，备板重建 */
    UCHAR    ucBitV6CanForwardData :1;  /* v6数据能否允许转发标记vos_true允许，用于重协商场景，备板重建 */
    UCHAR    ucBitDelPDNBackupFlag :1;  /* PDN是否单独通知备板删除标记 */
    UCHAR    ucBit345678Resv     : 3;
    UCHAR    ucReserve;
}PDN_CONTEXT_S;           /* 384 bytes */




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pppc_pdn.h */
