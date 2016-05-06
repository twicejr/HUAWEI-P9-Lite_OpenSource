


#ifndef __AT_DATA_PROC_H__
#define __AT_DATA_PROC_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "mdrv.h"

#include "AtCtx.h"
#include "AtInputProc.h"
#include "AtNdisInterface.h"
#include "AtRnicInterface.h"
/* Modified by m00217266 for L-C互操作项目, 2014-2-11, begin */
#include "RnicConfigInterface.h"
#include "AdsInterface.h"
/* Modified by m00217266 for L-C互操作项目, 2014-2-11, end */
#include "AtPppInterface.h"

#include "FcInterface.h"
#include "PppInterface.h"

#include "TafApsApi.h"

#include "AtCmdMsgProc.h"

#include "AtInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*lint -e778 */
/*lint -e572 */
#ifndef VOS_NTOHL                   /* 大小字节序转换*/
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define VOS_NTOHL(x)    (x)
#define VOS_HTONL(x)    (x)
#define VOS_NTOHS(x)    (x)
#define VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ffU) << 24) | \
             (((x) & 0x0000ff00U) <<  8) | \
             (((x) & 0x00ff0000U) >>  8) | \
             (((x) & 0xff000000U) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ffU) << 24) | \
             (((x) & 0x0000ff00U) <<  8) | \
             (((x) & 0x00ff0000U) >>  8) | \
             (((x) & 0xff000000U) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))
#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */
#endif
/*lint -e572 */
/*lint -e778 */

#define AT_PPP_CODE_REQ                 (1)
#define AT_PPP_CODE_ACK                 (2)
#define AT_PPP_DEF_ID                   (1)

#define AT_AP_PPP_CODE_CHALLENGE        (1)
#define AT_AP_PPP_CODE_RESPONSE         (2)

#define AT_AP_PPP_PRIMARY_DNS           (129)
#define AT_AP_PPP_PRIMARY_WINNS         (130)
#define AT_AP_PPP_SECONDARY_DNS         (131)
#define AT_AP_PPP_SECONDARY_WINNS       (132)

#define AT_AP_PPP_CHAP_CHALLENGE_LEN    (16)
#define AT_AP_PPP_CHAP_RESPONSE_LEN     (16)
#define AT_AP_MAX_IPV4_ADDR_LEN         (15)

#define AT_AP_AUTH_NO_PROTO             (0)
#define AT_AP_AUTH_PAP_PROTO            (1)
#define AT_AP_AUTH_CHAP_PROTO           (2)

#define AT_DEF_DISPLAY_SPEED            (81920000)                              /* 10 M*/

#define AT_MAX_IPV4_DNS_LEN             (16)
#define AT_MAX_IPV4_NBNS_LEN            (16)
#define AT_MAX_IPV6_DNS_LEN             (16)
#define AT_MAX_IPV6_NBNS_LEN            (16)

#define AT_MAX_IPV6_STR_DOT_NUM          (3)
#define AT_MAX_IPV4V6_STR_COLON_NUM      (6)
#define AT_MAX_IPV6_STR_COLON_NUM        (7)

#define AT_IPV6_STR_MAX_TOKENS                  (16)                            /* IPV6字符串格式使用的分隔符标记最大个数 */
#define AT_IPV4_STR_DELIMITER                   '.'                             /* RFC协议使用的IPV4文本表达方式使用的分隔符 */
#define AT_IPV6_STR_DELIMITER                   ':'                             /* RFC2373使用的IPV6文本表达方式使用的分隔符 */

#if (FEATURE_ON == FEATURE_IPV6)
#define AT_GetIpv6Capability()                  (AT_GetCommPsCtxAddr()->ucIpv6Capability)
#endif

#define AT_PS_GET_SHARE_PDP_FLG()               (AT_GetCommPsCtxAddr()->ucSharePdpFlag)

#define AT_APP_GetPdpEntInfoAddr()              (&g_stAtAppPdpEntity)

#define AT_APP_GetDailParaAddr()                (&g_stAtAppDialPara)

#define AT_APP_GetFirstActPdpType()             (g_enAtAppFirstActPdpType)
#define AT_APP_SetFirstActPdpType(ucPdpType)    (g_enAtAppFirstActPdpType = (ucPdpType))

#define AT_APP_GetActPdpType()                  (g_enAtAppActPdpType)
#define AT_APP_SetActPdpType(ucPdpType)         (g_enAtAppActPdpType = (ucPdpType))

/* 获取APP客户端ID */
#define AT_APP_GET_CLIENT_ID()          (gastAtClientTab[AT_CLIENT_TAB_APP_INDEX].usClientId)

/* 获取APP拨号端口索引 */
#define AT_APP_GET_USR_PORT_INDEX()     (g_stAtAppPdpEntity.stUsrInfo.enPortIndex)

/* 获取APP拨号用户下发的cid */
#define AT_APP_GET_USR_CID()            (g_stAtAppPdpEntity.stUsrInfo.ucUsrCid)


/* 获取NDIS拨号当前命令操作类型 */
#define AT_APP_GET_CURR_CMD_OPT()       (gastAtClientTab[AT_APP_GET_USR_PORT_INDEX()].CmdCurrentOpt)

#define AT_APP_GetRaInfoAddr()                  (&g_stAtAppRaInfo)

/*----------------------------------------------------------------------
   ^NDISSTAT: <stat>[,<err_code>[,<wx_stat>[,<PDP_type]]]
   <err_code> value defined as follows:
   0      - Unknown error/Unspecified error
   others - (E)SM Cause
            SM Cause is defined in TS 24.008 section 10.5.6.6
            ESM Cause is defined in TS 24.301 section 9.9.4.4
*---------------------------------------------------------------------*/
#define AT_NDISSTAT_ERR_UNKNOWN                 (0)

/* NDIS拨号命令NDISCONN，NDISDUP的输入参数的 index */
#define AT_NDIS_CID_IDX                         (0)
#define AT_NDIS_CONN_IDX                        (1)
#define AT_NDIS_APN_IDX                         (2)
#define AT_NDIS_NAME_IDX                        (3)
#define AT_NDIS_PWD_IDX                         (4)
#define AT_NDIS_AUTH_IDX                        (5)

#define AT_NDIS_GetPdpEntInfoAddr()             (&g_stAtNdisDhcpPara)

/* 获取NDIS客户端ID */
#define AT_NDIS_GET_CLIENT_ID()         (gastAtClientTab[AT_CLIENT_TAB_NDIS_INDEX].usClientId)

/* 获取NDIS拨号端口索引 */
#define AT_NDIS_GET_USR_PORT_INDEX()    (g_stAtNdisDhcpPara.stUsrInfo.enPortIndex)

/* 获取NDIS拨号用户下发的cid */
#define AT_NDIS_GET_USR_CID()           (g_stAtNdisDhcpPara.stUsrInfo.ucUsrCid)



/* 获取NDIS拨号当前命令操作类型 */
#define AT_NDIS_GET_CURR_CMD_OPT()      (gastAtClientTab[AT_NDIS_GET_USR_PORT_INDEX()].CmdCurrentOpt)

#define AT_GetNdisConnParaAddr()                (&g_stAtNdisConnPara)

#define AT_APS_IP6_ADDR_PREFIX_BYTE_LEN  (8)

#define AT_MAC_LEN                       (6)
#define AT_IPV6_ADDR_PREFIX_BYTE_LEN     (8)
#define AT_IPV6_ADDR_PREFIX_BIT_LEN      (64)

#define AT_REG_FC                        (1)
#define AT_DEREG_FC                      (0)

/* QOS_TRAFFIC_CLASS */
#define AT_QOS_TRAFFIC_CLASS_SUBSCRIBE                (0)
#define AT_QOS_TRAFFIC_CLASS_CONVERSATIONAL           (1)
#define AT_QOS_TRAFFIC_CLASS_STREAMING                (2)
#define AT_QOS_TRAFFIC_CLASS_INTERACTIVE              (3)
#define AT_QOS_TRAFFIC_CLASS_BACKGROUND               (4)

/* Deleted by m00217266 for L-C互操作项目, 2014-1-26, begin */
#if 0
/* APP QOS: */
#define AT_APP_QOS_TRAFFIC_CLASS_CONVERSATIONAL           (0)
#define AT_APP_QOS_TRAFFIC_CLASS_STREAMING                (1)
#define AT_APP_QOS_TRAFFIC_CLASS_INTERACTIVE              (2)
#define AT_APP_QOS_TRAFFIC_CLASS_BACKGROUND               (3)

/* APP QOS: Traffic Handling */
#define AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_1            (1)
#define AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_2            (2)
#define AT_APP_QOS_TRAFFIC_HANDLING_PRIORITY_3            (3)

/* APP QOS: Source Statistic Descriptor */
#define AT_APP_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN           (0)
#define AT_APP_QOS_SRC_STATS_DESCRIPTOR_SPEECH            (1)

/* APP QOS: Transfer Delay */
#define AT_APP_QOS_TRANSFER_DELAY_150MS                   (150)

/* APP QOS: Signal Ind */
#define AT_APP_QOS_SIGNAL_IND_NOT_OPTIMISE                (0)
#define AT_APP_QOS_SIGNAL_IND_OPTIMISE                    (1)
#endif
/* Deleted by m00217266 for L-C互操作项目, 2014-1-26, end */


#define AT_IPV6_STR_RFC2373_TOKENS                    (8)   /* 分隔符标记的最大个数 */



#define AT_IPPROTO_UDP                  (0x11)              /* IP头部中UDP协议号*/
#define AT_IP_VERSION                   (4)                 /* IP头部中IP V4版本号 */
#define AT_IP_DEF_TTL                   (0xFF)              /* IP头部中IP TTL缺省值 */
#define AT_IP_RAND_ID                   (61468)             /* IP头部ID值，随机取*/
#define AT_IP_HDR_LEN                   (20)                /* IP 头部长度 */
#define AT_UDP_HDR_LEN                  (8)                 /* UDP 头部长度 */

/* 定义用户的CID，目前应用只会下发1，2，3 */
#define AT_PS_USER_CID_1                (1)
#define AT_PS_USER_CID_2                (2)
#define AT_PS_USER_CID_3                (3)

/* PS域呼叫无效CID */
#define AT_PS_CALL_INVALID_CID          (0xFF)
#define AT_PS_CALL_INVALID_CALLID       (0xFF)

/* IPV6地址后8个字节全零，则认为是无效的 */
#define AT_PS_IS_IPV6_ADDR_IID_VALID(aucIpv6Addr)\
            !((aucIpv6Addr[8] == 0x00) && (aucIpv6Addr[9] == 0x00)\
             && (aucIpv6Addr[10] == 0x00) && (aucIpv6Addr[11] == 0x00)\
             && (aucIpv6Addr[12] == 0x00) && (aucIpv6Addr[13] == 0x00)\
             && (aucIpv6Addr[14] == 0x00) && (aucIpv6Addr[15] == 0x00))


#if (FEATURE_ON == FEATURE_IPV6)
/* IPv6 接口ID, 长度为64bit */
#define AT_PS_IPV6_IID_LEN              (8)
#define AT_PS_IPV6_IID_OFFSET           (8)

#endif

#define AT_PS_INVALID_RMNET_ID   (0xFFFF)

#if (FEATURE_ON == FEATURE_IPV6)
#define AT_PS_IS_PDP_TYPE_SUPPORT(pdptype)  \
            ( (TAF_PDP_IPV4 == (pdptype))   \
             || (TAF_PDP_IPV6 == (pdptype)) \
             || (TAF_PDP_IPV4V6 == (pdptype)))
#else
#define AT_PS_IS_PDP_TYPE_SUPPORT(pdptype)  \
            (TAF_PDP_IPV4 == (pdptype))
#endif

#define AT_PS_IS_RABID_VALID(ucRabId)\
    (((ucRabId) >= AT_PS_MIN_RABID) && ((ucRabId) <= AT_PS_MAX_RABID))

#define AT_PS_GET_CURR_CMD_OPT(index)   (gastAtClientTab[index].CmdCurrentOpt)
#define AT_PS_GET_CURR_DATA_MODE(index) (gastAtClientTab[index].DataMode)
#define AT_PS_GET_PPPID(index)          (gastAtClientTab[index].usPppId)

#define AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_PTR()      (g_astAtRptConnectedResultTab)
#define AT_PS_GET_RPT_CONN_RSLT_FUNC_TBL_SIZE()     (AT_ARRAY_SIZE(g_astAtRptConnectedResultTab))

#define AT_PS_GET_RPT_END_RSLT_FUNC_TBL_PTR()       (g_astAtRptEndedResultTab)
#define AT_PS_GET_RPT_END_RSLT_FUNC_TBL_SIZE()      (AT_ARRAY_SIZE(g_astAtRptEndedResultTab))

#define AT_PS_GET_REG_FC_POINT_FUNC_TBL_PTR()       (g_astAtRegFCPointTab)
#define AT_PS_GET_REG_FC_POINT_FUNC_TBL_SIZE()      (AT_ARRAY_SIZE(g_astAtRegFCPointTab))

#define AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_PTR()     (g_astAtDeRegFCPointTab)
#define AT_PS_GET_DEREG_FC_POINT_FUNC_TBL_SIZE()    (AT_ARRAY_SIZE(g_astAtDeRegFCPointTab))

#define AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_PTR()    (g_astAtSndPdpActIndTab)
#define AT_PS_GET_SND_PDP_ACT_IND_FUNC_TBL_SIZE()   (AT_ARRAY_SIZE(g_astAtSndPdpActIndTab))

#define AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_PTR()  (g_astAtSndPdpDeActIndTab)
#define AT_PS_GET_SND_PDP_DEACT_IND_FUNC_TBL_SIZE() (AT_ARRAY_SIZE(g_astAtSndPdpDeActIndTab))

#define AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_PTR()    (g_astAtChdataRnicRmNetIdTab)
#define AT_PS_GET_CHDATA_RNIC_RMNET_ID_TBL_SIZE()   (AT_ARRAY_SIZE(g_astAtChdataRnicRmNetIdTab))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum AT_PDP_STATUS_ENUM
{
    AT_PDP_STATUS_DEACT                    = 0,
    AT_PDP_STATUS_ACT                      = 1,
    AT_PDP_STATUS_BUTT
};
typedef VOS_UINT32 AT_PDP_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名称   : AT_PDP_TYPE_ENUM_ENUM
 协议表格   :
 ASN.1 描述 :
 枚举说明   : PDP类型
*****************************************************************************/
enum AT_PDP_TYPE_ENUM
{
    AT_PDP_IPV4                         = 1,
    AT_PDP_IPV6                         = 2,
    AT_PDP_IPV4V6                       = 3,
    AT_PDP_PPP                          = 4,
    AT_PDP_TYPE_BUTT
};
typedef VOS_UINT8 AT_PDP_TYPE_ENUM_ENUM_U8;

/*****************************************************************************
 结构名称   : AT_IPV6_STR_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : IPV6 String格式枚举
              HEX为RFC2373要求使用':'作为分隔符
              DEX为RFC要求使用'.'作为分隔符
*****************************************************************************/
enum AT_IPV6_STR_TYPE_ENUM
{
    AT_IPV6_STR_TYPE_HEX                = 0x01,
    AT_IPV6_STR_TYPE_DEC                = 0x02,

    AT_IPV6_STR_TYPE_BUTT               = 0xFF
};
typedef VOS_UINT8 AT_IPV6_STR_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称   : AT_IP_ADDR_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : 区分是SOURCE还是LOCAL的IP ADDR
*****************************************************************************/
enum AT_IP_ADDR_TYPE_ENUM
{
    AT_IP_ADDR_TYPE_SOURCE              = 0x01,
    AT_IP_ADDR_TYPE_LOCAL               = 0x02,

    AT_IP_ADDR_TYPE_BUTT                = 0xFF
};
typedef VOS_UINT8 AT_IP_ADDR_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名称   : AT_HILINK_MODE_ENUM
 协议表格   :
 ASN.1 描述 :
 枚举说明   : HiLink模式
*****************************************************************************/
enum AT_HILINK_MODE_ENUM
{
    AT_HILINK_NORMAL_MODE,
    AT_HILINK_GATEWAY_MODE,
    AT_HILINK_MODE_BUTT
};
typedef VOS_UINT8 AT_HILINK_MODE_ENUM_U8;

/* APP拨号状态*/
/*****************************************************************************
 枚举名称   : AT_APP_CONN_STATE_ENUM
 协议表格   :
 ASN.1 描述 :
 枚举说明   : APP拨号状态
*****************************************************************************/
enum AT_APP_CONN_STATE_ENUM
{
    AT_APP_DIALING,                     /*0: indicates is connecting*/
    AT_APP_DIALED,                      /*1: indicates connected*/
    AT_APP_UNDIALED,                    /*2: indicates disconnected*/
    AT_APP_BUTT
};
typedef VOS_UINT32 AT_APP_CONN_STATE_ENUM_U32;

/*****************************************************************************
 PPP拨号后的速率气泡显示，分两种情况处理:
 1.2G模式下，则根据当前驻留的小区模式是GSM/GPRS/EDGE来决定速率气泡的显示,对应如下:
     GSM          - 9600
     GPRS         - 85600
     GPRS Class33 - 107800
     EDGE         - 236800
     EDGE Class33 - 296000
     默认 -
 2.3g模式下，则根据RRC版本和HSDPA的category信息来决定速率气泡的显示，对应如下:
     RRC版本为R99   - 384000
     RRC版本为非R99 - 判断HSDPA的category信息
                   6  - 3600000
                   8  - 7200000
                   9  - 10200000
                   10 - 14400000
                   12 - 1800000
                   14 - 21600000
                   18 - 28800000
                   24 - 43200000
                   26 - 57600000
                   28 - 86400000
     有扩展的category的话，默认 - 21600000
     无扩展的category的话，默认 - 7200000
*****************************************************************************/
enum PPP_RATE_DISPLAY_ENUM
{
    PPP_RATE_DISPLAY_GSM = 0,
    PPP_RATE_DISPLAY_GPRS,
    PPP_RATE_DISPLAY_GPRS_CALSS33,
    PPP_RATE_DISPLAY_EDGE,
    PPP_RATE_DISPLAY_EDGE_CALSS33,

    PPP_RATE_DISPLAY_R99,
    PPP_RATE_DISPLAY_DPA_CATEGORY_6,
    PPP_RATE_DISPLAY_DPA_CATEGORY_8,
    PPP_RATE_DISPLAY_DPA_CATEGORY_9,
    PPP_RATE_DISPLAY_DPA_CATEGORY_10,
    PPP_RATE_DISPLAY_DPA_CATEGORY_12,
    PPP_RATE_DISPLAY_DPA_CATEGORY_14,
    PPP_RATE_DISPLAY_DPA_CATEGORY_18,
    PPP_RATE_DISPLAY_DPA_CATEGORY_24,
    PPP_RATE_DISPLAY_DPA_CATEGORY_26,
    PPP_RATE_DISPLAY_DPA_CATEGORY_28,

    PPP_RATE_DISPLAY_BUTT
};
typedef VOS_UINT32 PPP_RATE_DISPLAY_ENUM_UINT32;


/*****************************************************************************
 枚举名    : AT_CH_DATA_CHANNEL_ENUM
 结构说明  : AT^CHDATA命令设置的<datachannelid>的取值


  1.日    期   : 2013年05月07日
    作    者   : y00213812
    修改内容   : V9R1 IPv6&TAF/SM Project新增枚举

*****************************************************************************/
enum AT_CH_DATA_CHANNEL_ENUM
{
    AT_CH_DATA_CHANNEL_ID_1             = 1,
    AT_CH_DATA_CHANNEL_ID_2,
    AT_CH_DATA_CHANNEL_ID_3,
    AT_CH_DATA_CHANNEL_ID_4,
    AT_CH_DATA_CHANNEL_ID_5,
    AT_CH_DATA_CHANNEL_ID_6,
    AT_CH_DATA_CHANNEL_ID_7,

    AT_CH_DATA_CHANNEL_BUTT
};
typedef VOS_UINT32 AT_CH_DATA_CHANNEL_ENUM_UINT32;



/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDLEnqueuedPkts;                       /*下行数据包总个数*/
    VOS_UINT32                          ulDLDequeuedPkts;                       /*下行发送个数*/
    VOS_UINT32                          ulDLDroppedPkts;                        /*下行丢包个数*/
    VOS_UINT32                          ulDLMaxBlkPkts;                         /*下行队列最大阻塞个数*/
    VOS_UINT32                          ulDLMaxDequeueOnce;                     /*下行单次发送包个数最大值*/
} AT_AP_DL_DATA_Q_STAT_ST;


/* DHCP配置，全主机序*/
typedef struct
{
    VOS_UINT32                          ulIPAddr;                               /* IP 地址，网侧分配*/
    VOS_UINT32                          ulSubNetMask;                           /* 子网掩码地址，根据IP地址计算*/
    VOS_UINT32                          ulGateWay;                              /* 网关地址，也是本DHCP Server的地址*/
    VOS_UINT32                          ulPrimDNS;                              /* 主 DNS地址，网侧分配*/
    VOS_UINT32                          ulSndDNS;                               /* 次 DNS地址，网侧分配*/
}AT_DHCP_CONFIG_STRU;


typedef struct
{
    VOS_UINT16                          usClientID;                             /* Client ID*/
    VOS_UINT8                           ucRabID;                                /* Rab ID*/
    VOS_UINT8                           ucCid;                                  /* CID*/
    AT_PDP_STATE_ENUM_U8                enState;                                /* State*/
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulFlowCtrlState;                        /* Flow Ctrl State ; 1: flow ctrl ,0: no flow ctrl*/
    VOS_UINT32                          ulSpeed;                                /* Um Speed*/

    VOS_UINT32                          ulDLMaxRate;                            /* 理论最大下行速率*/
    VOS_UINT32                          ulULMaxRate;                            /* 理论最大上行速率*/
    VOS_UINT32                          ulDLCurrentRate;                        /* 当前下行速率*/
    VOS_UINT32                          ulULCurrentRate;                        /* 当前上行速率*/
    VOS_UINT32                          ulRateCalcPeriod;                       /* 速率统计周期*/
    AT_DHCP_CONFIG_STRU                 stDhcpCfg;
}AT_CTRL_ENTITY_STRU;

typedef struct AT_DHCP_PARA
{
    VOS_UINT16                          usClientID;                             /* Client ID*/
    VOS_UINT8                           ucRabID;                                /* Rab ID*/
    VOS_UINT8                           ucCid;                                  /* CID*/
    VOS_UINT32                          ulSpeed;                                /* Um Speed*/
    VOS_UINT32                          ulDLMaxRate;                            /* 理论最大下行速率*/
    VOS_UINT32                          ulULMaxRate;                            /* 理论最大上行速率*/
    AT_DHCP_CONFIG_STRU                 stDhcpCfg;
}AT_DHCP_PARA_STRU;

typedef struct
{
  VOS_UINT8                             ucCode;                                 /* Request code */
  VOS_UINT8                             ucId;                                   /* Identification */
  VOS_UINT16                            usLength;                               /* Length of packet */
}AT_PPP_FRAME_HEAD_STRU;

/* IP地址结构 U32类型，网络字节序存储*/
typedef struct
{
    VOS_UINT32                          ulIpAddr;                               /*U32类型，网络字节序存储*/
}IN_ADDR_ST;


typedef struct
{
    VOS_UINT8                           ucType;
    VOS_UINT8                           ucCode;
    VOS_UINT16                          usCheckSum;
    VOS_UINT16                          usId;
    VOS_UINT16                          usSeq;
}ICMP_ECHO_HEAD_ST;

typedef struct
{
    VOS_UINT32                          ulIPAddr;                               /* IP 地址*/
    VOS_UINT32                          ulPrimDNS;                              /* 主 DNS地址*/
    VOS_UINT32                          ulSndDNS;                               /* 次 DNS地址*/
    VOS_UINT32                          ulPrimWINNS;                            /* 鱓INNS*/
    VOS_UINT32                          ulSncWINNS;                             /* 副WINNS */
}AT_DHCP_SETUP_PARAM_ST;


/* DHCP 服务器信息结构*/
typedef struct
{
    AT_DHCP_CONFIG_STRU                 stDHCPConfig;                           /* DHCP服务器配置*/
    VOS_UINT32                          ulDHCPServerOn;                         /* DHCP是否已经打开*/
}AT_DHCP_ENTITY_ST;

/* PDP状态上报函数使用的结构体*/
typedef struct
{
    VOS_UINT32                          ulspeed;                                /* 连接速度，单位bps */
    AT_PDP_STATUS_ENUM_UINT32           enActiveSatus;                          /* 激活结果，0为成功，其他为失败 */
}AT_NDIS_PRO_STRU;

/*****************************************************************************
 结构名称   : AT_PDP_SAVE_STATE_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 保存拨号状态
*****************************************************************************/
typedef struct
{

    AT_PDP_STATE_ENUM_U8                enIpv4State;
    AT_PDP_STATE_ENUM_U8                enIpv6State;
    AT_PDP_STATE_ENUM_U8                enIpv4v6State;

} AT_PDP_SAVE_STATE_INFO_STRU;





/*****************************************************************************
 结构名    : AT_NDIS_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :

  1.日    期   : 2011年12月24日
    作    者   : o00132663
    修改内容   : PS融合项目，删除参数AT_NDIS_DHCPINFO_RPT_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucClientId;
    VOS_UINT8                           ucSysMode;
    VOS_UINT16                          usMsgSize;
    VOS_UINT32                          ulMsgId;
    union
    {
        AT_NDIS_PDNINFO_CFG_CNF_STRU    stNdisPdnInfoCfgCnf;
        AT_NDIS_PDNINFO_REL_CNF_STRU    stNdisPdnInfoRelCnf;
        AT_NDIS_USBABNORMAL_IND_STRU    stNdisUsbabnormalInd;
    }unMsg;
} AT_NDIS_MSG_STRU;

/*****************************************************************************
 结构名    : AT_NDISCONN_PARA_STRU
 结构说明  : 保存NDIS拨号的参数，供NDISCONN 查询命令时使用
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulConnectState;                                                 /* 拨号标志, 0 断开，1 连接 */
    VOS_UINT8   ucCID;                                                          /* AT 命令中输入的CID*/
    VOS_UINT8   aucAPN[TAF_MAX_APN_LEN+1];                                      /* AT命令中输入的APN */
    VOS_UINT8   aucUsername[TAF_MAX_GW_AUTH_USERNAME_LEN+1];                    /* username指针*/
    VOS_UINT8   aucPassword[TAF_MAX_GW_AUTH_PASSWORD_LEN+1];                    /* password指针*/
    VOS_UINT8   ucReserved;
    VOS_UINT16  usAuthType;
} AT_NDISCONN_PARA_STRU;

/*****************************************************************************
 结构名    : AT_CLINTID_RABID_MAP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :

  1.日    期   : 2012年2月18日
    作    者   : L47619
    修改内容   : AP-MODEM项目
  2.日    期   : 2013年04月15日
    作    者   : f00179208
    修改内容   : C核单独复位项目
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsed;   /* 指定FCID对应的结点是否有效，VOS_TRUE:有效，VOS_FALSE:无效 */
    VOS_UINT32                          ulRabIdMask;
    MODEM_ID_ENUM_UINT16                enModemId;
    FC_PRI_ENUM_UINT8                   enFcPri;
    VOS_UINT8                           aucReserve[1];                          /* 保留 */
} AT_FCID_MAP_STRU;

/*****************************************************************************
 结构名     : AT_IPHDR_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : IPv4 packet header 结构
  1.日    期   : 2012年6月12日
    作    者   : S62952
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
#if (VOS_LITTLE_ENDIAN == VOS_BYTE_ORDER)                   /* 小端字节序*/
    VOS_UINT8                           ucIpHdrLen  :4;     /* IP头部长度 */
    VOS_UINT8                           ucIpVer     :4;     /* IP版本号*/
#elif (VOS_BIG_ENDIAN == VOS_BYTE_ORDER)                    /* 大端字节序*/
    VOS_UINT8                           ucIpVer     :4;     /* IP版本号*/
    VOS_UINT8                           ucIpHdrLen  :4;     /* IP头部长度 */
#else
#error  "Please fix Macro VOS_BYTE_ORDER"                   /* VOS_BYTE_ORDER未定义*/
#endif
    VOS_UINT8                           ucServiceType;      /* IP TOS字段*/
    VOS_UINT16                          usTotalLen;         /* IP数据包总长度*/
    VOS_UINT16                          usIdentification;   /* IP数据包ID*/
    VOS_UINT16                          usOffset;           /* IP分片偏移量*/
    VOS_UINT8                           ucTTL;              /* IPTTL*/
    VOS_UINT8                           ucProtocol;         /* IP数据载荷部分协议*/
    VOS_UINT16                          usCheckSum;         /* IP头部校验和*/
    VOS_UINT32                          ulSrcAddr;          /* 源IP地址*/
    VOS_UINT32                          ulDstAddr;          /* 目的IP地址*/
} AT_IPHDR_STRU;

/*****************************************************************************
 结构名     : AT_UDP_HDR_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : UDP header 结构
  1.日    期   : 2012年6月12日
    作    者   : S62952
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSrcPort;          /* 源端口 */
    VOS_UINT16                          usDstPort;          /* 目的端口 */
    VOS_UINT16                          usLen;              /* UDP包长度 */
    VOS_UINT16                          usChecksum;         /* UDP校验和 */
} AT_UDP_HDR_STRU;

/*****************************************************************************
 结构名     : AT_UDP_PACKET_FORMAT_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : UDP packet 结构
  1.日    期   : 2012年6月12日
    作    者   : S62952
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{

    AT_IPHDR_STRU                       stIpHdr;            /* IP头 */
    AT_UDP_HDR_STRU                     stUdpHdr;           /* UDP头 */
    VOS_UINT32                          ulBody;
} AT_UDP_PACKET_FORMAT_STRU;

/*****************************************************************************
 结构名    : AT_PS_RMNET_ID_TAB
 结构说明  : PS域拨号网卡和ModemId,cid,FcId的映射表
   1.日    期   : 2012年12月18日
     作    者   : L60609
     修改内容   : 新建
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                enModemId;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           ucUsrCid;
}AT_PS_RMNET_ID_TAB;

/*****************************************************************************
 结构名称   : AT_PDP_ENTITY_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 拨号使用的PDP实体信息
*****************************************************************************/
typedef struct
{
    AT_PS_USER_INFO_STRU                stUsrInfo;
    VOS_UINT8                           ucIpv4Cid;
    VOS_UINT8                           ucIpv6Cid;
    VOS_UINT8                           ucIpv4v6Cid;
    AT_PDP_STATE_ENUM_U8                enIpv4State;
    AT_PDP_STATE_ENUM_U8                enIpv6State;
    AT_PDP_STATE_ENUM_U8                enIpv4v6State;
    VOS_UINT8                           aucRsv[2];

    AT_IPV4_DHCP_PARAM_STRU             stIpv4Dhcp;
    AT_IPV6_DHCP_PARAM_STRU             stIpv6Dhcp;

}AT_PDP_ENTITY_STRU;


/*****************************************************************************
 结构名    : AT_CHDATA_RNIC_RMNET_ID_STRU
 结构说明  : AT^CHDATA与RNIC网卡映射关系的结构

  1.日    期   : 2013年4月26日
    作    者   : L60609
    修改内容   : V9R1 IPv6&TAF/SM接口优化项目新增
*****************************************************************************/
typedef struct
{
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enChdataValue;
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId;

    VOS_UINT8                           aucReserved[3];
}AT_CHDATA_RNIC_RMNET_ID_STRU;


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/

/*记录闪电卡版本从上电到拨号成功启动时间，单位秒 */
extern VOS_UINT32                       g_ulLcStartTime;

extern AT_PDP_ENTITY_STRU               g_stAtNdisDhcpPara;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtFirstNdisActPdpType;

extern AT_NDISCONN_PARA_STRU            g_stAtNdisConnPara;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtNdisActPdpType;

extern AT_DIAL_PARAM_STRU               gstAtNdisAddParam;

extern AT_HILINK_MODE_ENUM_U8           g_enHiLinkMode;

extern AT_PDP_ENTITY_STRU               g_stAtAppPdpEntity;

extern AT_DIAL_PARAM_STRU               g_stAtAppDialPara;

extern AT_PDP_STATE_ENUM_U8             g_enAtAppSaveState;

extern AT_PDP_SAVE_STATE_INFO_STRU      g_stAtAppSaveStateInfo;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtAppActPdpType;

extern TAF_PDP_TYPE_ENUM_UINT8          g_enAtAppFirstActPdpType;

extern AT_IPV6_RA_INFO_STRU             g_stAtAppRaInfo;

extern AT_FCID_MAP_STRU                 g_stFcIdMaptoFcPri[];

extern AT_PS_RMNET_ID_TAB               g_astPsRmNetIdTab[];

extern AT_PS_REPORT_CONN_RESULT_STRU    g_astAtRptConnectedResultTab[];

extern AT_PS_REPORT_END_RESULT_STRU     g_astAtRptEndedResultTab[];

extern AT_PS_REG_FC_POINT_STRU          g_astAtRegFCPointTab[];


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : AT_GetDhcpPara
 功能描述  : 获取DHCP参数(DHCP参数为网络序)
 输入参数  : pstConfig                  - DHCP参数(网络序)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_GetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig,
    AT_IPV4_DHCP_PARAM_STRU            *pstIpv4Dhcp
);


/******************************************************************************
 函 数 名  : AT_GetDisplayRate
 功能描述  : 获取空口理论带宽，从NAS获取，且将字符串型式转为整形
 输入参数  : ulSpeed
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
******************************************************************************/
VOS_UINT32 AT_GetDisplayRate(
    VOS_UINT16                          usClientId,
    VOS_UINT32                         *ulSpeed
);


/******************************************************************************
 函 数 名  : AT_CtrlConnIndProc
 功能描述  : 需要解析激活上下文，设置DHCP服务器
 输入参数  : pstEvent指向TAF_PS_CALL_EVENT_INFO_STRU去激活的指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月23日
    作    者   : sunshaohua
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID AT_CtrlConnIndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_USER_TYPE                        ucUserType
);

/******************************************************************************
 Function:      AT_CtrlGetPDPAuthType
 Description:    获取PC设置的PDP上下文中对应类型的数据
 Calls:
 Data Accessed:
 Data Updated:
 Input:
                 usTotalLen     PDP上下文内存长度
 Output:
 Return:        0   no auth
                1   pap
                2   chap
******************************************************************************/
PPP_AUTH_TYPE_ENUM_UINT8 AT_CtrlGetPDPAuthType(
    VOS_UINT32                          Value,
    VOS_UINT16                          usTotalLen
);
/*****************************************************************************
 函 数 名  : AT_CtrlGetTapPdpAuthType
 功能描述  : CL模式下获取用户下发的ppp鉴权参数类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_PDP_AUTH_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月9日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
TAF_PDP_AUTH_TYPE_ENUM_UINT8 AT_ClGetPdpAuthType(
    VOS_UINT32                          Value,
    VOS_UINT16                          usTotalLen
);

/******************************************************************************
 Function:       AT_CtrlFreePCOContext
 Description:    释放PCO中的指针
 Calls:
 Data Accessed:
 Data Updated:
 Input:
                 usTotalLen     PDP上下文内存长度
 Output:
 Return:        0   no auth
                1   pap
                2   chap
******************************************************************************/
VOS_VOID AT_CtrlFreePCOContext(
    PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo
);


/******************************************************************************
 Function:       AT_CtrlMakePCOPapAuthInfo
 Description:    将AT中设置的用户名密码填入PCO结构
 Calls:
 Data Accessed:
 Data Updated:
 Input:         pstPppReqCfgInfo    指向设置给PCO信息的指针
                pucUserName         用户名
                usUserNameLen       用户名长度
                pucPassWord         密码
                usPassWordLen       密码长度
 Output:
 Return:        VOS_OK
                VOS_ERR
 Others:        pap帧格式
                1 byte    -- code
                1 byte    -- id
                2 byte    -- length (include "code", "id", "length")
                1 byte    -- username length
                x byte    -- username
                1 byte    -- password length
                x byte    -- password
                注意:本函数申请内存在TTF_NDIS_CtrlFreePCOContext中释放
******************************************************************************/
VOS_UINT32 AT_CtrlMakePCOPapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo,
    VOS_UINT8                           *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                           *pucPassWord,
    VOS_UINT16                          usPassWordLen
);


/******************************************************************************
 Function:       AT_CtrlMakePCOChapAuthInfo
 Description:    将AT中设置的用户名密码填入PCO结构
 Calls:
 Data Accessed:
 Data Updated:
 Input:         pstPppReqCfgInfo    指向设置给PCO信息的指针
                pucUserName         用户名
                usUserNameLen       用户名长度
                pucPassWord         密码
                usPassWordLen       密码长度
 Output:
 Return:
 Others:        chap challenge 帧格式
                1 byte    -- code
                1 byte    -- id
                2 byte    -- length (include "code", "id", "length")
                1 byte    -- challenge length   (16 bytes)
                x byte    -- challenge
                x byte    -- name               ("huawei.com" )
                chap response 帧格式
                1 byte    -- code
                1 byte    -- id
                2 byte    -- length (include "code", "id", "length")
                1 byte    -- response length    (16 bytes)
                x byte    -- response
                x byte    -- name               (from username)
******************************************************************************/
VOS_UINT32 AT_CtrlMakePCOChapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU            *pstPppReqCfgInfo,
    VOS_UINT8                           *pucUserName,
    VOS_UINT16                           usUserNameLen,
    VOS_UINT8                           *pucPassWord,
    VOS_UINT16                           usPassWordLen
);

/******************************************************************************
 函数名称: AT_Ipv4AddrAtoi
 功能描述: 把IPV4地址由字符串格式转换成数字格式

 参数说明:
   pcString [in] 字符串格式的IP地址,char * pcString="192.168.0.1"
   pucNumber [out] 数字格式的IP地址,char pucNumber[4]={192,168,0,1};

 返 回 值:
    TODO: ...

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2010-02-02]
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrAtoi(VOS_CHAR *pcString, VOS_UINT8 *pucNumber);

/******************************************************************************
 函数名称: AT_Ipv4AddrItoa
 功能描述: 把IPV4地址由数字格式转换成字符串格式

 参数说明:
   pcString [out] 字符串格式的IP地址,char * pcString="192.168.0.1"
   pucNumber [in] 数字格式的IP地址,char pucNumber[4]={192,168,0,1};

 返 回 值:
    TODO: ...

 调用要求: TODO: ...
 调用举例: TODO: ...
 作    者: 崔军强/00064416 [2010-02-02]
******************************************************************************/
VOS_UINT32 AT_Ipv4AddrItoa(VOS_CHAR *pcString, VOS_UINT8 *pucNumber);

/*****************************************************************************
 函 数 名  : AT_Ipv4Addr2Str
 功能描述  : IPV4类型的地址转换为字符串类型
 输入参数  : pucNumber      - IPV4地址
 输出参数  : pcString       - 字符串
 返 回 值  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_Ipv4Addr2Str(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
);

VOS_UINT32 AT_Ipv6AddrAtoi(VOS_CHAR *pcString, VOS_UINT8 *pucNumber);

/*****************************************************************************
 函 数 名  : AT_Ipv6LenStrToAddrProc
 功能描述  : 将字符串格式的IP地址转化为SM协议IP地址格式(IPV6).
 输入参数  : pucStr - 字符串格式的IP地址
             pucColonCount - 冒号个数
             pucDotCount   - 点号个数
 输出参数  : pucIpAddr - SM协议定义的IP地址
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_Ipv6LenStrToAddrProc(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount
);


/******************************************************************************
 函 数 名  : AT_Ipv6LenStrToAddrProcCompressed
 功能描述  : 将IPV6压缩字符串格式转化为非压缩格式.
 输入参数  : pucStr       - 字符串格式的IP地址
             ucColonCount - 冒号个数
             ucDotCount   - 点号个数
             ucStrlen     - 字符串长度
             ucIdxPos     - 补充冒号插入位置
 输出参数  : pucIpAddr - 非压缩格式的IP地址
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
******************************************************************************/
VOS_VOID  AT_Ipv6LenStrToAddrProcCompressed(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                           ucColonCount,
    VOS_UINT8                           ucDotCount,
    VOS_UINT8                           ucStrlen,
    VOS_UINT8                           ucIdxPos
);


/*****************************************************************************
 函 数 名  : AT_Ipv6LenStrToAddrAccess
 功能描述  : 遍历IPV6地址字符串，取得冒号、点号个数
 输入参数  : pucStr        - 字符串格式的IP地址
 输出参数  : pucColonCount - 冒号个数
             pucDotCount   - 点号个数
             pucStrlen     - IPV6字符串长度
             pucIdxPos     - 数组补充冒号索引
 返 回 值  : VOS_OK - 转化成功
             VOS_ERR - 转化失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_Ipv6LenStrToAddrAccess(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucColonCount,
    VOS_UINT8                          *pucDotCount,
    VOS_UINT8                          *pucStrlen,
    VOS_UINT8                          *pucIdxPos
);


/******************************************************************************
 函 数 名  : AT_Ipv6LenStrToAddr
 功能描述  : 将字符串格式的IP地址转化为SM协议IP地址格式(IPV6).
 输入参数  : pucStr - 字符串格式的IP地址
 输出参数  : pucIpAddr - SM协议定义的IP地址
 返 回 值  : VOS_OK  - 转化成功
             VOS_ERR - 转化失败
 调用函数  :
 被调函数  :
******************************************************************************/
VOS_UINT32  AT_Ipv6LenStrToAddr(
    VOS_UINT8                          *pucStr,
    VOS_UINT8                          *pucIpAddr
);

/*****************************************************************************
 函 数 名  : AT_Ipv6AddrToStr
 功能描述  : 将IPV6地址格式转换为字符串格式
 输入参数  : aucIpAddr[]    - IPV6地址(协议格式)
             enIpStrType    - IPV6字符串格式表达类型
 输出参数  : aucAddrStr[]   - IPV6地址(字符串格式)
 返 回 值  : VOS_OK         - 转换成功
             VOS_ERR        - 转换失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_Ipv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    AT_IPV6_STR_TYPE_ENUM_UINT8         enIpStrType
);

/*****************************************************************************
 函 数 名  : AT_Itoa
 功能描述  : 根据转换基数(10或16), 将整数转换为ASCII码, 将结果输出至字符串
 输入参数  : usValue    - 待转换为ASCII码的整数
             pcStr      - 输出结果的字符串
             usRadix    - 转换基数
 输出参数  : 无
 返 回 值  : VOS_CHAR*
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_CHAR* AT_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix
);

/******************************************************************************
 函 数 名  : AT_AtoI
 功能描述  : 字符串转整形
 输入参数  : pString 字符串
 输出参数  : 无
 返 回 值  : 整形 IP地址
 调用函数  :
 被调函数  :
******************************************************************************/
VOS_UINT32  AT_AtoI(
    VOS_UINT8                         *pString
);

/*****************************************************************************
 函 数 名  : AT_FindIpv6AddrZeroFieldsToBeCompressed
 功能描述  : 找出需要使用"::"表示的IP地址段的起始位置
 输入参数  : ausAddrValue[]     - IPV6地址段数组
             ucTokensNum        - 地址段个数
 输出参数  : pucZeroFieldStart  - 数值连续为0的IP地址段起始位置
             pucZeroFieldCount  - 数值连续为0的IP地址段个数
 返 回 值  : VOS_OK             - 成功
             VOS_ERR            - 失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_FindIpv6AddrZeroFieldsToBeCompressed(
    VOS_UINT8                          *pucZeroFieldStart,
    VOS_UINT8                          *pucZeroFieldCount,
    VOS_UINT16                          ausAddrValue[],
    VOS_UINT8                           ucTokensNum
);


/*****************************************************************************
 函 数 名  : AT_ConvertIpv6AddrToCompressedStr
 功能描述  : 将IPV6地址格式转换为字符串压缩格式
 输入参数  : aucIpAddr[]    - IPV6地址(协议格式)
             ucTokensNum    - 地址段个数
 输出参数  : aucAddrStr[]   - IPV6地址(字符串格式)
 返 回 值  : VOS_OK         - 转换成功
             VOS_ERR        - 转换失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_ConvertIpv6AddrToCompressedStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    VOS_UINT8                           ucTokensNum
);

VOS_UINT32 AT_GetLanAddr32(
  VOS_UINT8                            *pucAddr
);
TAF_UINT32 AT_DHCPGetIPMask(
    TAF_UINT32                          ulIpAddrHL
);
VOS_UINT32 AT_DHCPGetGateWay(
    VOS_UINT32                          ulIpAddrHL,
    VOS_UINT32                          ulMaskHL
);

/*****************************************************************************
 函 数 名  : AT_CalcIpHdrCRC16
 功能描述  : 计算IP头CRC校验和
 输入参数  : pucData    - IP头信息
             usSize     - IP头长度
 输出参数  : 无
 返 回 值  : ulCheckSum - CRC校验和
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT16 AT_CalcIpHdrCRC16(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usSize
);


/*****************************************************************************
 函 数 名  : AT_BuildUdpHdr
 功能描述  : 构造IP和UDP头部信息(用于构造测试使用的UDP包)
 输入参数  : pstUdpPkt  - UDP包信息
             usLen      - UDP包长度
             ulSrcAddr  - 源IP地址
             ulDstAddr  - 目标IP地址
             usSrcPort  - 源端口号
             usDstPort  - 目标端口号
 输出参数  : 无
 返 回 值  : VOS_OK     - 构造成功
             VOS_ERR    - 构造失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_BuildUdpHdr(
    AT_UDP_PACKET_FORMAT_STRU          *pstUdpPkt,
    VOS_UINT16                          usLen,
    VOS_UINT32                          ulSrcAddr,
    VOS_UINT32                          ulDstAddr,
    VOS_UINT16                          usSrcPort,
    VOS_UINT16                          usDstPort
);


/*****************************************************************************
 函 数 名  : AT_NidsGet3gppSmCauseByPsCause
 功能描述  : 将PS域呼叫错误码转换成3GPP协议定义的(E)SM Cause, 非3GPP协议定义
             的错误码统一转换成0(Unknown error/Unspecified error)
 输入参数  : enCause - PS域呼叫错误码
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_Get3gppSmCauseByPsCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


/*****************************************************************************
 函 数 名  : AT_SaveNdisConnDailPara
 功能描述  : 保存NDISCONN拨号时的参数，供NDISCONN查询命令使用
 输入参数  : AT_PARSE_PARA_TYPE_STRU            *pstParaList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_SaveNdisConnDailPara(
    AT_PARSE_PARA_TYPE_STRU            *pstParaList
);


/*****************************************************************************
 函 数 名  : AT_SendNdisRelReq
 功能描述  : 发送PDN配置释放消息
 输入参数  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_SendNdisRelReq(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_RcvNdisPdnInfoCfgCnf
 功能描述  : NDIS配置的结果处理
 输入参数  : AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoCfgCnf(
    AT_NDIS_PDNINFO_CFG_CNF_STRU       *pstNdisPdnInfoCfgCnf
);

/*****************************************************************************
 函 数 名  : AT_RcvNdisPdnInfoRelCnf
 功能描述  : NDIS释放应答处理
 输入参数  : AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_RcvNdisPdnInfoRelCnf(
    AT_NDIS_PDNINFO_REL_CNF_STRU       *pstNdisPdnInfoRelCnf
);



#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_NdisIpv6DhcpRest
 功能描述  : 清空IPV6地址参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_NdisIpv6DhcpRest(VOS_VOID);


/*****************************************************************************
 函 数 名  : AT_NdisCtrlConnIpv6IndProc
 功能描述  : 处理IPV6地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID  AT_NdisCtrlConnIpv6IndProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU         *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_NdisCheckIpv6PdpState
 功能描述  : 检查是否有满足IPv6状态的PDP连接
 输入参数  : enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_TRUE   - PDP连接存在
             VOS_FALSE  - PDP连接不存在
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);
#endif


/*****************************************************************************
 函 数 名  : AT_NdisStateChangeProc
 功能描述  : NDIS拨号时通知PC拨号状态改变
 输入参数  : ucPdpType --- PDP类型
             ulStat    --- NDIS连接状态:0-连接断开; 1-已连接
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_NdisStateChangeProc(
    VOS_UINT8                           ucPdpType,
    VOS_UINT32                          ulStat,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


/******************************************************************************
 函 数 名  : AT_NdisGetState
 功能描述  : 获取NDIS状态，激活态/非激活态
 输入参数  : ucIndex --- 用户索引
 输出参数  : 无
 返 回 值  : AT_PDP_STATE_ENUM_U8 当前状态 激活态/非激活态

 调用函数  :
 被调函数  :
******************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_NdisGetState(
    VOS_UINT8                           ucCid
);


/*****************************************************************************
 函 数 名  : AT_NdisCheckPdpIdleState
 功能描述  : 查找是否有idel或deacting的PDP
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_NdisCheckPdpIdleState(VOS_VOID);

/*****************************************************************************
 函 数 名  : AT_NdisAddrProc
 功能描述  : 处理NDIS地址参数
 输入参数  : pstConfig --- 指向DHCP参数的指针
             pstEvent  --- 上报事件
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_NdisAddrProc(
    AT_DHCP_CONFIG_STRU                 *pstConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_NdisCheckIpv6PdpState
 功能描述  : 检查是否有满足IPv4状态的PDP连接
 输入参数  : enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_TRUE   - PDP连接存在
             VOS_FALSE  - PDP连接不存在
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_NdisCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);


/*****************************************************************************
 函 数 名  : AT_NdisGetDhcpPara
 功能描述  : 获取DHCP参数
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_NdisGetDhcpPara(
    AT_DHCP_PARA_STRU                  *pstConfig
);


/*****************************************************************************
 函 数 名  : AT_NdisSetState
 功能描述  : 设置NDIS状态
 输入参数  : ucPdpType --- PDP类型
             enState   --- PDP状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_NdisSetState(
    VOS_UINT8                              ucPdpType,
    AT_PDP_STATE_ENUM_U8                   enState
);

/*****************************************************************************
 函 数 名  : AT_NdisPsRspPdpActEvtRejProc
 功能描述  : pdp激活失败，NDIS处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_NdisPsRspPdpActEvtCnfProc
 功能描述  : pdp激活成功，Ndis处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_NdisPsRspPdpDeactEvtCnfProc
 功能描述  : pdp去激活成功，Ndis处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_NdisPsRspPdpDeactivatedEvtProc
 功能描述  : pdp去激活成功，Ndis处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID  AT_NdisPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_NDIS_ParseUsrInfo
 功能描述  : 获取NDIS用户信息
 输入参数  : ucIndex     - 端口号(ClientId)索引
 输出参数  : pstUserInfo - 用户信息
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_NDIS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
);

VOS_VOID AT_NDIS_ConnStatusChgProc(NCM_IOCTL_CONNECT_STUS_E enStatus);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_CalcIpv6LanAddrFromIpv6Prefix
 功能描述  : 根据IPV6地址前缀产生IPV6全局地址
 输入参数  : pucPrefix
             ulPrefixByteLen
             pucIpv6LanAddr
             ulIpv6LanAddrLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_CalcIpv6LanAddrFromIpv6Prefix(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr,
    VOS_UINT32                          ulIpv6LanAddrLen
);


/*****************************************************************************
 函 数 名  : AT_AppRcvIpv6LanAddr
 功能描述  : NAS向HOST注册的回调函数，当HOST获取IPv6全局地址后，向NAS上报-
             IPv6全局地址，以及全局地址长度。
 输入参数  : aucLanAddr       - Ipv6全局地址
             ulLanAddrByteLen - 地址长度, 单位是BYTE
             ulPrefixBitLen   - 前缀长度, 单位是BIT
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LanAddr(
    VOS_UINT8                           aucLanAddr[],
    VOS_UINT32                          ulLanAddrByteLen,
    VOS_UINT32                          ulPrefixBitLen
);


/*****************************************************************************
 函 数 名  : AT_AppRcvIpV6Prefix
 功能描述  : NAS向HOST注册的回调函数，当HOST收到GGSN下发的RA之后，向NAS上报-
             IPv6地址前缀，以及地址前缀长度。
 输入参数  : VOS_UINT8  aucPrefix   Ipv6前缀
             VOS_UINT32 ulPrefixLen 前缀长度，单位是BIT
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6Prefix(
    VOS_UINT8                           aucPrefix[],
    VOS_UINT32                          ulPrefixBitLen
);


/*****************************************************************************
 函 数 名  : AT_AppRcvPrefixIpV6PreferredLifetime
 功能描述  : 主动上报PreferredLifetime
 输入参数  : ulPrefixPreferredLifetime - 前缀优先使用生存期
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6PreferredLifetime(
    VOS_UINT32                          ulPrefixPreferredLifetime
);


/*****************************************************************************
 函 数 名  : AT_RcvPrefixIpV6ValidLifetime
 功能描述  : 主动上报ValidLifetime
 输入参数  : ulValidLifetime - 前缀有效生存期
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppRcvPrefixIpv6ValidLifetime(
    VOS_UINT32                          ulValidLifetime
);


/*****************************************************************************
 函 数 名  : AT_RcvIpV6LinkMtu
 功能描述  : 接收到HOST模块的MTU数据的处理函数: 保存MTU数据到本地，同时主动上报给APP
             接收到RA数据后，HOST模块调用本函数通知NAS新的MTU数据
 输入参数  : ulMTU - MTU Size
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppRcvIpv6LinkMtu(
    VOS_UINT32                          ulMtu
);


/*****************************************************************************
 函 数 名  : AT_RcvEnableIpV6Prefix
 功能描述  : 通知应用启用新的IPV6前缀
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppRcvEnableIpv6Prefix(VOS_VOID);


/*****************************************************************************
 函 数 名  : AT_AppProcIpv6RaInfo
 功能描述  : 收到Router Advertisement IP报文, 进行处理和分发
 输入参数  : pstRaInfoNotifyInd         - RA报文信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd);


/*****************************************************************************
 函 数 名  : AT_AppCtrlConnIpv6IndProc
 功能描述  : 处理IPv6地址
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppCtrlConnIpv6IndProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_AppDhcpv6Reset
 功能描述  : 清空IPv6地址参数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppDhcpv6Reset(VOS_VOID);
#endif


/*****************************************************************************
 函 数 名  : AT_AppDhcpReset
 功能描述  : 清空APP的DHCP参数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppDhcpReset(VOS_VOID);

/*****************************************************************************
 函 数 名  : AT_AppPdpAddrProc
 功能描述  : 处理IPv4地址参数
 输入参数  : pstAppPdpEntity - PDP实体
             pstDhcpConfig   - DCHP信息
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppPdpAddrProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_AppCheckPdpIdleState
 功能描述  : 检查是否有处于IDLE或DEACTIVATING状态的PDP
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 存在满足条件的PDP
             VOS_FALSE - 不存在满足条件的PDP
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_AppCheckPdpIdleState(VOS_VOID);

/*****************************************************************************
 函 数 名  : AT_AppCheckIpv4PdpState
 功能描述  : 检查是否有满足IPv4状态的PDP连接
 输入参数  : enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_TRUE   - PDP连接存在
             VOS_FALSE  - PDP连接不存在
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv4PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_AppCheckIpv6PdpState
 功能描述  : 检查是否有满足IPv6状态的PDP连接
 输入参数  : enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_TRUE   - PDP连接存在
             VOS_FALSE  - PDP连接不存在
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_AppCheckIpv6PdpState(
    AT_PDP_STATE_ENUM_U8                enPdpState
);
#endif


/*****************************************************************************
 函 数 名  : AT_AppGetPdpState
 功能描述  : 获取APP的PDP状态，激活态/非激活态
 输入参数  : ucPdpType - PDP类型
 输出参数  : 无
 返 回 值  : AT_PDP_STATE_ENUM_U8
 调用函数  :
 被调函数  :
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_AppGetPdpState(
    VOS_UINT8                           ucPdpType
);


/*****************************************************************************
 函 数 名  : AT_AppSetPdpState
 功能描述  : 设置APP的PDP状态
 输入参数  : ucPdpType  - PDP类型
             enPdpState - PDP状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppSetPdpState(
    VOS_UINT8                           ucPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
);


/*****************************************************************************
 函 数 名  : AT_AppSndCallConnectedResult
 功能描述  : 上报连接结果^DCONN, 通知APP拨号成功
 输入参数  : ucCid                      - CID
             enPdpType                  - 拨号类型(IPv4/IPv6)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppSndCallConnectedResult(
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


/*****************************************************************************
 函 数 名  : AT_AppSndCallEndedResult
 功能描述  : 上报连接结果^DCONN, 通知APP拨号成功
 输入参数  : ucCid     - CID
             enCause   - 错误码
             enPdpType - 拨号类型(IPv4/IPv6)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppSndCallEndedResult(
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


/*****************************************************************************
 函 数 名  : AT_AppPdpActOrig
 功能描述  : 发起PDP激活
 输入参数  : usClientId - 客户端ID
             ucCid      - CID
             ucPdpType  - PDP类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_AppActCnfBackProc
 功能描述  : PDP激活成功后的回退处理
 输入参数  : pstEvent   - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
#endif


/*****************************************************************************
 函 数 名  : AT_AppIpv4ActCnfProc
 功能描述  : 处理IPV4的PDP激活成功的事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_AppIpv6ActCnfProc
 功能描述  : 处理IPV6的PDP激活成功的事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_AppIpv4v6ActCnfProc
 功能描述  : 处理IPv4v6的PDP激活成功的事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActCnfProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);
#endif

/*****************************************************************************
 函 数 名  : AT_AppIpv4DeactCnfProc
 功能描述  : 处理IPv4的PDP去激活事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_AppIpv6DeactCnfProc
 功能描述  : 处理IPv4的PDP去激活事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_AppIpv4v6DeactCnfProc
 功能描述  : 处理IPv4v6的PDP去激活事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpDeactivatedProc(
    AT_PDP_ENTITY_STRU                  *pstAppPdpEntity,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);
#endif


/*****************************************************************************
 函 数 名  : AT_AppIpv4v6PdpActRejProc
 功能描述  : 处理IPv4的PDP激活被拒事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppIpv4PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_AppIpv6PdpActRejProc
 功能描述  : 处理IPv6的PDP激活被拒事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppIpv6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_AppIpv4v6PdpActRejProc
 功能描述  : 处理IPv4的PDP激活被拒事件
 输入参数  : pstAppPdpEntity - PDP实体
             pstEvent        - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppIpv4v6PdpActRejProc(
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);
#endif


/*****************************************************************************
 函 数 名  : AT_AppPsRspPdpActEvtCnfProc
 功能描述  : PDP激活成功，APP处理
 输入参数  : ucIndex  - 客户标识号
             pstEvent - 上报事件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_AppPsRspPdpActEvtRejProc
 功能描述  : PDP激活失败，APP处理
 输入参数  : ucIndex  - 客户标识号
             pstEvent - 上报事件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpActRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_AppPsRspPdpDeactEvtCnfProc
 功能描述  : PDP去激活成功，APP处理
 输入参数  : ucIndex  - 客户标识号
             pstEvent - 上报事件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_AppPsRspPdpDeactivatedEvtProc
 功能描述  : 网侧去激活PDP, APP处理
 输入参数  : ucIndex  - 客户标识号
             pstEvent - 上报事件内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_AppPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_AppSetFlowCtrl
 功能描述  : 启动路由设备流控
 输入参数  : ulParam1   - 目前不使用
             ulParam2   - 目前不使用
 输出参数  : 无
 返 回 值  : VOS_OK     - 启动流控成功
             VOS_ERR    - 启动流控失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_AppSetFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);


/*****************************************************************************
 函 数 名  : AT_AppClearFlowCtrl
 功能描述  : 停止路由设备流控
 输入参数  : ulParam1   - 目前不使用
             ulParam2   - 目前不使用
 输出参数  : 无
 返 回 值  : VOS_OK     - 停止流控成功
             VOS_ERR    - 停止流控失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_AppClearFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);


/*****************************************************************************
 函 数 名  : AT_AppRegFCPoint
 功能描述  : 注册路由端口流控点
 输入参数  : FC_ID_ENUM_UINT8                    enFcId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_AppRegFCPoint(
    FC_ID_ENUM_UINT8                    enFcId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    VOS_UINT8                           ucRmNetId
);


/*****************************************************************************
 函 数 名  : AT_AppDeRegFCPoint
 功能描述  : 去注册路由设备流控点
 输入参数  : FC_ID_ENUM_UINT8                      enFcId,
             TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_OK     - 去注册流控点成功
             VOS_ERR    - 去注册流控点失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_AppDeRegFCPoint(
    FC_ID_ENUM_UINT8                     enFcId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_APP_ParseUsrInfo
 功能描述  : 获取APP用户信息
 输入参数  : ucIndex     - 端口号(ClientId)索引
 输出参数  : pstUserInfo - 用户信息
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_APP_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUsrInfo
);

/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

/*****************************************************************************
 函 数 名  : AT_ModemPsRspPdpActEvtRejProc
 功能描述  : pdp激活失败，AP MODEM处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtRejProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pEvent
);


/*****************************************************************************
 函 数 名  : AT_ModemPsRspPdpActEvtCnfProc
 功能描述  : pdp激活失败，Modem处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpActEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pEvent
);

/*****************************************************************************
 函 数 名  : AT_ModemPsRspPdpDeactEvtCnfProc
 功能描述  : pdp去激活成功，Modem处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactEvtCnfProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pEvent
);

/*****************************************************************************
 函 数 名  : AT_MODEM_ProcCallEndedEvent
 功能描述  : 处理PS_CALL_END_CNF事件
 输入参数  : ucIndex  - 端口索引
             pstEvent - ID_EVT_TAF_PS_CALL_END_CNF事件指针
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MODEM_ProcCallEndCnfEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_END_CNF_STRU           *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_MODEM_HangupCall
 功能描述  : 挂断PPP拨号连接
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX  - ATC返回码
*****************************************************************************/
VOS_UINT32 AT_MODEM_HangupCall(VOS_UINT8 ucIndex);


VOS_VOID  AT_AnswerPdpActInd(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_ModemPsRspPdpDeactivatedEvtProc
 功能描述  : pdp去激活成功，Modem处理
 输入参数  : ucIndex --- 已知的客户标识号
             pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月5日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  AT_ModemPsRspPdpDeactivatedEvtProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pEvent
);





/*****************************************************************************
 函 数 名  : AT_GetLCStartTime
 功能描述  : 获取从上电到拨号成功时间，单位秒
 输入参数  : 无
 输出参数  : 无
 返 回 值  :  启动时间，单位秒
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_GetLCStartTime(VOS_VOID);

/*****************************************************************************
函 数 名  : AT_SendRnicPdpDeactInd
功能描述  : APP端口拨号时通知虚拟网卡
输入参数  : VOS_UINT8 ucRabId
输出参数  : 无
返 回 值  : 成功
            失败
调用函数  :
被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_SendRnicPdpDeactInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
);

/*****************************************************************************
 函 数 名  : AT_DeRegModemPsDataFCPoint
 功能描述  : 去注册Modem端口流控点。
 输入参数  : MN_CLIENT_ID_T                      usClientID,
             VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_DeRegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucRabId
);

/*****************************************************************************
 函 数 名  : AT_RegModemPsDataFCPoint
 功能描述  : 注册Modem端口流控点。
 输入参数  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  *pstEvent
             FC_ID_ENUM_UINT8                      enFcId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_RegModemPsDataFCPoint(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
);

#if( FEATURE_ON == FEATURE_CSD )
/*****************************************************************************
 函 数 名  : AT_RegModemVideoPhoneFCPoint
 功能描述  : 注册Modem端口CST流控点。
 输入参数  : FC_ID_ENUM_UINT8                    enFcId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_RegModemVideoPhoneFCPoint(
    VOS_UINT8                           ucIndex,
    FC_ID_ENUM_UINT8                    enFcId
);

/*****************************************************************************
 函 数 名  : AT_DeRegModemVideoPhoneFCPoint
 功能描述  : 去注册Modem端口CST流控点。
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_DeRegModemVideoPhoneFCPoint(VOS_UINT8 ucIndex);
#endif


/*****************************************************************************
 函 数 名  : AT_ProcNdisRegFCPoint
 功能描述  : NDIS用户类型PDP状态改变为激活时的处理
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增

*****************************************************************************/
VOS_VOID  AT_ProcNdisRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 函 数 名  : AT_ProcNdisDeRegFCPoint
 功能描述  : NDIS用户类型PDP状态改变为去激活时的处理
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增

*****************************************************************************/
VOS_VOID  AT_ProcNdisDeRegFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 函 数 名  : AT_RegNdisFCPoint
 功能描述  : 注册NDIS端口流控点。
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_RegNdisFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId,
    MODEM_ID_ENUM_UINT16                enModemId
);

/*****************************************************************************
 函 数 名  : AT_DeRegNdisFCPoint
 功能描述  : 去注册NDIS端口流控点。
 输入参数  : VOS_UINT8                           ucRabId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_DeRegNdisFCPoint(
    VOS_UINT8                           ucRabId,
    MODEM_ID_ENUM_UINT16                enModemId
);

/*****************************************************************************
 函 数 名  : AT_NdisPdpActOrig
 功能描述  : 发起PDP激活
 输入参数  :  VOS_UINT16                  usClientId
              VOS_UINT8                   ucCid
              TAF_PDP_TYPE_ENUM_UINT8     ucPdpType
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_VOID AT_NdisPdpActOrig(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
);

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_NdisActCnfBackProc
 功能描述  : PDP激活成功后的回退处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_VOID  AT_NdisActCnfBackProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_SendNdisIPv6PdnInfoCfgReq
 功能描述  : 发送IPV6的PDN信息
 输入参数  : TAF_PS_IPV6_INFO_IND_STRU* pRaInfo
 输出参数  : 无
 返 回 值  : AT_APS_IPV6_RA_INFO_STRU* pIPv6RaInfo
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_SendNdisIPv6PdnInfoCfgReq(
           MODEM_ID_ENUM_UINT16                 enModemId,
           TAF_PS_IPV6_INFO_IND_STRU* pIPv6RaNotify);

/*****************************************************************************
 函 数 名  : AT_NdisIpv4ActCnfProc
 功能描述  : 处理IPV4的PDP激活成功的事件
 输入参数  : pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_VOID AT_NdisIpv4ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_NdisIpv6ActCnfProc
 功能描述  : 处理IPV6的PDP激活成功的事件
 输入参数  : pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_VOID AT_NdisIpv6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_NdisIpv4v6ActCnfProc
 功能描述  : 处理IPV4v6的PDP激活成功的事件
 输入参数  : pstEvent --- 事件内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_VOID AT_NdisIpv4v6ActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
#endif


/*****************************************************************************
 函 数 名  : AT_GetFCPriFromQos
 功能描述  : Qos转化为FC优先级
 输入参数  : TAF_UMTS_QOS_STRU                  *pstUmtsQos
 输出参数  : 无
 返 回 值  : FC_PRI_ENUM_UINT8
 调用函数  :
 被调函数  :
*****************************************************************************/
extern FC_PRI_ENUM_UINT8 AT_GetFCPriFromQos(
    TAF_UMTS_QOS_STRU                  *pstUmtsQos
);

/*****************************************************************************
 函 数 名  : AT_GetPsDialParamFromAtDialParam
 功能描述  : 获取拨号参数
 输入参数  : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_VOID AT_GetPsDialParamFromAtDialParam(
    TAF_PS_DIAL_PARA_STRU              *pstPsDialParam,
    AT_DIAL_PARAM_STRU                 *pstDialParam
);

/*****************************************************************************
 函 数 名  : AT_GetPdpContextFromAtDialParam
 功能描述  : 获取pdp上下文
 输入参数  : TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
             AT_DIAL_PARAM_STRU                 *pstDialParam
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :s
*****************************************************************************/
extern VOS_VOID AT_GetPdpContextFromAtDialParam(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt,
    AT_DIAL_PARAM_STRU                 *pstDialParam
);

/*****************************************************************************
 函 数 名  : AT_GetFcPriFromMap
 功能描述  : 获取指定FC ID的FC PRI
 输入参数  : FC_ID_ENUM_UINT8                   enFcId,
             AT_FCID_MAP_STRU                  *pstFcIdMap
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_GetFcPriFromMap(
    FC_ID_ENUM_UINT8                   enFcId,
    AT_FCID_MAP_STRU                  *pstFcIdMap
);


/*****************************************************************************
 函 数 名  : AT_NotifyFcWhenPdpModify
 功能描述  : 当发生PDP MODIFY(UE发起或网侧发起)时，向FC指示修改流控点
 输入参数  : pstEvt       TAF_PS_CALL_EVENT_INFO_STRU事件
             enFcId        流控实体ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月18日
    作    者   : L47619
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NotifyFcWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent,
    FC_ID_ENUM_UINT8                    enFcId
);

/* Deleted by m00217266 for L-C互操作项目, 2014-1-26, begin */
#if 0
/*****************************************************************************
 函 数 名  : AT_NotifyAdsWhenPdpModify
 功能描述  : 当发生PDP MODIFY(UE发起或网侧发起)时，向ADS指示发生了PDP修改
 输入参数  : pstEvt       TAF_PS_CALL_EVENT_STRU事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月18日
    作    者   : L47619
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID AT_NotifyAdsWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU   *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_NotifyAdsWhenPdpAvtivated
 功能描述  : 通知ADS承载激活
 输入参数  : pstEvent - 承载激活事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_NotifyAdsWhenPdpAvtivated(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_NotifyAdsWhenPdpDeactivated
 功能描述  : 通知ADS去承载激活
 输入参数  : pstEvent - 承载去激活事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID AT_NotifyAdsWhenPdpDeactivated(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_SendAdsPdpStatusInd
 功能描述  : AT向ADS发送消息
 输入参数  : VOS_UINT32                          ulPid,
             ADS_PDP_STATUS_IND_STRU            *pstAdsInd
 输出参数  : 无
 返 回 值  : 成功
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_SendAdsPdpStatusInd(
    VOS_UINT32                          ulPid,
    ADS_PDP_STATUS_IND_STRU            *pstAdsInd
);
#endif
/* Deleted by m00217266 for L-C互操作项目, 2014-1-26, end */

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_SaveIPv6Dns
 功能描述  : 保存IPV6的DNS到PDP实体中
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_VOID  AT_SaveIPv6Dns(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
);

/*****************************************************************************
 函 数 名  : AT_SaveIPv6Pcscf
 功能描述  : 保存IPV6的Pcscf到PDP实体中
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent,
             AT_PDP_ENTITY_STRU                 *pstPdpEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID  AT_SaveIPv6Pcscf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    AT_PDP_ENTITY_STRU                 *pstPdpEntity
);
#endif


/*****************************************************************************
 函 数 名  : AT_UsbEthHostAccumTuneCB
 功能描述  : 向FC(流控)模块注册的动态调整HOST端NCM/ECM组包参数的回调函数
 输入参数  : pstFcDrvAssemPara - NCM/ECM组包参数, 包含如下参数:
                                 1. HOST OUT组包时间
 输出参数  : 无
 返 回 值  : VOS_OK            - 调整成功
             VOS_ERR           - 调整失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_UsbEthHostAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
);


/*****************************************************************************
 函 数 名  : AT_UsbEthDeviceAccumTuneCB
 功能描述  : 向FC(流控)模块注册的动态调整DEVICE端NCM/ECM组包参数的回调函数
 输入参数  : pstFcDrvAssemPara - NCM/ECM组包参数, 包含如下参数:
                                 1. TX组包个数
                                 2. TX组包时间
                                 3. RX组包个数
                                 4. RX组包时间
 输出参数  : 无
 返 回 值  : VOS_OK            - 调整成功
             VOS_ERR           - 调整失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 AT_UsbEthDeviceAccumTuneCB(
    FC_DRV_ASSEM_PARA_STRU             *pstFcDrvAssemPara
);


/*****************************************************************************
 函 数 名  : AT_ChangeFCPoint
 功能描述  : 更改流控点优先级。
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent,
             FC_PRI_ENUM_UINT8                    enFCPri,
             FC_ID_ENUM_UINT8                     enFcId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
extern VOS_UINT32 AT_ChangeFCPoint(
    TAF_CTRL_STRU                       *pstCtrl,
    FC_PRI_ENUM_UINT8                    enFCPri,
    FC_ID_ENUM_UINT8                     enFcId
);

extern VOS_UINT32 AT_EnableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
);
extern VOS_UINT32 AT_DisableHsicFlowCtl(
    VOS_UINT32                          ulUdiHdl,
    VOS_UINT32                          ulParam2
);
extern VOS_UINT32 AT_RegHsicFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_UINT32 AT_DeRegHsicFCPoint(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_VOID  AT_HsicPsRspEvtPdpActCnfProc(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_VOID  AT_HsicPsRspEvtPdpDeactCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU        *pstEvent
);
extern VOS_VOID  AT_HsicPsRspEvtPdpDeactivatedProc(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);
/* Modified by l60609 for AP适配项目 ，2012-09-10 Begin */
extern VOS_VOID  AT_ProcAppPsRspEvtPdpActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);
extern VOS_VOID  AT_ProcAppPsRspEvtPdpDeActCnf(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);
/* Modified by l60609 for AP适配项目 ，2012-09-10 End */
extern VOS_VOID AT_ProcAppPsRspEvtPdpDeactivated(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU *pstEvent
);
extern VOS_VOID AT_NotifyFcWhenAppPdpModify(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
);

/*DTS2012041102190 : h00135900 start in 2011-04-11 AT代码融合*/
#if (FEATURE_ON == FEATURE_LTE)
/* AT模块给FTM 模块发送消息 */
extern VOS_UINT32 atSendFtmDataMsg(VOS_UINT32 TaskId, VOS_UINT32 MsgId, VOS_UINT32 ulClientId, VOS_VOID* pData, VOS_UINT32 uLen);
#endif
/*DTS2012041102190 : h00135900 end in 2011-04-11 AT代码融合*/

extern VOS_UINT32 AT_SendRnicCgactIpv4ActInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
);

/*****************************************************************************
 函 数 名  : AT_PS_AddIpAddrRabIdMap
 功能描述  : 添加承载IP与RABID的映射
 输入参数  : usClientId - 客户端ID
             pstEvent   - PS域呼叫事件
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_AddIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_PS_DeleteIpAddrRabIdMap
 功能描述  : 删除承载IP与RABID的映射
 输入参数  : usClientId - 客户端ID
             pstEvent   - PS域呼叫事件
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_DeleteIpAddrRabIdMap(
    VOS_UINT16                          usClientId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_PS_GetIpAddrByRabId
 功能描述  : 根据RABID获取承载IP地址
 输入参数  : usClientId - 客户端ID
             ucRabId    - RABID [5,15]
 输出参数  : 无
 返 回 值  : ulIpAddr   - IP地址(主机序)
*****************************************************************************/
VOS_UINT32 AT_PS_GetIpAddrByRabId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucRabId
);


extern VOS_UINT32 AT_PS_GetRmNetIdByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucRmNetId
);
extern VOS_VOID AT_PS_SetPsCallErrCause(
    VOS_UINT16                          usClientId,
    TAF_PS_CAUSE_ENUM_UINT32            enPsErrCause
);
extern TAF_PS_CAUSE_ENUM_UINT32 AT_PS_GetPsCallErrCause(
    VOS_UINT16                          usClientId
);

extern VOS_UINT32 AT_ResetFlowCtl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);
VOS_UINT32 AT_PS_GetRnicRmNetIdFromChDataValue(
    VOS_UINT8                           ucIndex,
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId,
    RNIC_RMNET_ID_ENUM_UINT8           *penRnicRmNetId
);

VOS_UINT32 AT_PS_GetChDataValueFromRnicRmNetId(
    RNIC_RMNET_ID_ENUM_UINT8            enRnicRmNetId,
    AT_CH_DATA_CHANNEL_ENUM_UINT32     *penDataChannelId
);

AT_PS_CALL_ENTITY_STRU* AT_PS_GetCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT8 AT_PS_TransCidToCallId(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
);

VOS_UINT32 AT_PS_IsCallIdValid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_VOID AT_PS_ReportDCONN(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID AT_PS_ReportDEND(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPortIndex,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID AT_PS_RegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_DeRegHsicFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID AT_PS_RegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_DeRegAppFCPoint(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID  AT_PS_SndDipcPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID  AT_PS_SndDipcPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID  AT_PS_SndRnicPdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_VOID AT_PS_SndRnicPdpDeactInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

#if (FEATURE_ON == FEATURE_IPV6)
VOS_UINT32 AT_PS_IsIpv6CapabilityValid(VOS_UINT8 ucCapability);

VOS_UINT32 AT_CheckIpv6Capability(
    VOS_UINT8                           ucPdpType
);

VOS_UINT32 AT_PS_GenIpv6LanAddrWithRadomIID(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr
);


VOS_VOID  AT_PS_SaveIPv6Dns(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID  AT_PS_SaveIPv6Pcscf(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcConnectedIpv6Addr(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv6RaInfo(TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd);


VOS_UINT32 AT_PS_MatchIpv4v6ConnFailFallbackCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


VOS_UINT32 AT_PS_SetupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


VOS_UINT32 AT_PS_HangupSingleStackConn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);


VOS_VOID AT_PS_ProcDualStackCallConn(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent
);


VOS_VOID AT_PS_ProcIpv6ConnSuccFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


VOS_UINT32 AT_PS_ProcIpv4ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);


VOS_UINT32 AT_PS_ProcIpv4v6ConnFailFallback(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);
#endif

VOS_VOID AT_PS_ProcIpv4CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID AT_PS_ProcIpv6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


VOS_VOID AT_PS_ProcIpv4v6CallConnected(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


VOS_VOID AT_PS_ProcIpv6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv4v6CallReject(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcIpv6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID AT_PS_ProcIpv4v6CallEnded(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_UINT8 AT_CalcIpv6PrefixLength(
    VOS_UINT8                           *pucLocalIpv6Mask
);

VOS_VOID AT_GetIpv6MaskByPrefixLength(
    VOS_UINT8                            ucLocalIpv6Prefix,
    VOS_UINT8                           *pucLocalIpv6Mask
);

#endif

VOS_VOID AT_PS_ProcCallConnectedEvent(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

VOS_VOID AT_PS_ProcCallRejectEvent(
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   *pstEvent
);

VOS_VOID AT_PS_ProcCallEndedEvent(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

VOS_VOID AT_PS_ProcCallOrigCnfEvent(TAF_PS_CALL_ORIG_CNF_STRU *pstCallOrigCnf);

VOS_VOID AT_PS_ProcCallEndCnfEvent(TAF_PS_CALL_END_CNF_STRU *pstCallEndCnf);

VOS_UINT32 AT_PS_ProcCallModifyEvent(
    VOS_UINT8                           ucIndex,
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
);

VOS_UINT32 AT_PS_AllocCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *pucCallId
);

VOS_VOID AT_PS_FreeCallEntity(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT32 AT_PS_ValidateDialParam(VOS_UINT8 ucIndex);

VOS_VOID AT_PS_ParseUsrInfo(
    VOS_UINT8                           ucIndex,
    AT_PS_USER_INFO_STRU               *pstUserInfo
);

TAF_PDP_TYPE_ENUM_UINT8 AT_PS_GetCurrCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT32 AT_PS_SetupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    AT_DIAL_PARAM_STRU                 *pstCallDialParam
);

VOS_UINT32 AT_PS_HangupCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

VOS_UINT32 AT_PS_ProcDialUp(VOS_UINT8 ucIndex);

VOS_UINT32 AT_PS_ProcDialDown(VOS_UINT8 ucIndex);

VOS_UINT32 AT_PS_ProcDialCmd(VOS_UINT8 ucIndex);


extern VOS_UINT32 AT_CheckApnFormat(
    VOS_UINT8                          *pucApn,
    VOS_UINT16                          usApnLen
);


VOS_VOID AT_PS_AssignCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucCallId
);

VOS_VOID AT_PS_FreeCallIdToCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
);


/*****************************************************************************
 函 数 名  : AT_PS_ProcDeactSharePdpState
 功能描述  : PDP状态变化时，Share PDP特性相关的处理
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID  AT_PS_ProcDeactSharePdpState(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 函 数 名  : AT_PS_ProcActSharePdpState
 功能描述  : PDP状态变化时，Share PDP特性相关的处理
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
             TAF_PDP_TYPE_ENUM_UINT8             enPdpType
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID  AT_PS_ProcActSharePdpState(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU   *pstEvent,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : AT_PS_ProcSharePdpIpv6RaInfo
 功能描述  : Share-PDP特性开启情况下，收到Router Advertisement IP报文, 存储相应PDN信息
 输入参数  : pstRaInfoNotifyInd         - RA报文信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增

*****************************************************************************/
VOS_VOID AT_PS_ProcSharePdpIpv6RaInfo(
    TAF_PS_IPV6_INFO_IND_STRU *pstRaInfoNotifyInd
);
#endif

/******************************************************************************
 函 数 名  : AT_PS_SaveRnicPdpDhcpPara
 功能描述  : 收到NDIS PDP激活成功消息后，保存DHCP信息到APP PDP实体中
 输入参数  : TAF_PDP_TYPE_ENUM_UINT8              ucPdpType,
              TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : z00214637
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID AT_PS_SaveRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/******************************************************************************
 函 数 名  : AT_PS_ResetRnicPdpDhcpPara
 功能描述  : 收到NDIS PDP去激活成功消息后，重置AppPdpEntity
 输入参数  : ucPdpType - PDP类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月5日
    作    者   : z00214637
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID AT_PS_ResetRnicPdpDhcpPara(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType
);

/*****************************************************************************
 函 数 名  : AT_PS_SendRnicPdnInfoCfgInd
 功能描述  : 向RNIC发送PDN连接信息
 输入参数  : TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
             VOS_UINT8                           ucRabId,
             AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目修改
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoCfgInd(
    TAF_PDP_TYPE_ENUM_UINT8             ucPdpType,
    VOS_UINT8                           ucRabId,
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
);

/*****************************************************************************
 函 数 名  : AT_PS_SendRnicPdnInfoRelInd
 功能描述  : 向RNIC发送PDN连接释放请求消息
 输入参数  : AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : z00214637
    修改内容   : V3R3 Share-PDP项目修改
*****************************************************************************/
VOS_UINT32 AT_PS_SendRnicPdnInfoRelInd(
    VOS_UINT8                           ucRabId
);

/*****************************************************************************
 函 数 名  : AT_PS_GetRptConnResultFunc
 功能描述  : 获取连接建立结果上报函数指针
 输入参数  : ucUsrType - 用户类型
 输出参数  : 无
 返 回 值  : AT_PS_RPT_CONN_RSLT_FUNC
*****************************************************************************/
AT_PS_RPT_CONN_RSLT_FUNC AT_PS_GetRptConnResultFunc(AT_USER_TYPE ucUsrType);

/*****************************************************************************
 函 数 名  : AT_PS_GetRptEndResultFunc
 功能描述  : 获取连接断开结果上报函数指针
 输入参数  : ucUsrType - 用户类型
 输出参数  : 无
 返 回 值  : AT_PS_RPT_END_RSLT_FUNC
*****************************************************************************/
AT_PS_RPT_END_RSLT_FUNC AT_PS_GetRptEndResultFunc(AT_USER_TYPE ucUsrType);


VOS_UINT32 AT_PS_SetQosPara(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucUserCid,
    VOS_UINT8                           ucActCid
);

/* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-17, begin */
VOS_UINT32 Taf_GetDisplayRate(
    VOS_UINT16                          usClientId,
    VOS_UINT8                          *ucSpeed
);
/* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-17, end */

/* Added by m00217266 for L-C互操作项目, 2014-1-26, begin */
#if 0
/*****************************************************************************
 函 数 名  : AT_QosParaTransferToQci
 功能描述  : 根据QOS参数转换为QCI等级
 输入参数  : TAF_UMTS_QOS_STRU                   *pQos
 输出参数  : 无
 返 回 值  : QCI类型

*****************************************************************************/
ADS_QCI_TYPE_ENUM_UINT8 AT_QosParaTransferToQci(
    TAF_UMTS_QOS_STRU                   *pQos
);
#endif
/* Added by m00217266 for L-C互操作项目, 2014-1-26, end */

/*****************************************************************************
 函 数 名  : AT_ProcAppRegFCPoint
 功能描述  : APP用户类型PDP状态改变为激活时的处理
 输入参数  : TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
 输出参数  : 无
 返 回 值  : VOS_VOID

*****************************************************************************/
VOS_VOID  AT_ProcAppRegFCPoint(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_SendRnicIpv4ActInd
 功能描述  : APP拨号时通知虚拟网卡IPV4激活
 输入参数  : VOS_UINT8 ucRmNetId
 输出参数  : 无
 返 回 值  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4ActInd(VOS_UINT8 ucRmNetId);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
函 数 名  : AT_SendRnicIpv6ActInd
功能描述  : APP拨号时通知虚拟网卡IPV6激活
输入参数  : VOS_UINT8 ucRmNetId
输出参数  : 无
返 回 值  : 成功
            失败
*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv6ActInd(VOS_UINT8 ucRmNetId);

/*****************************************************************************
函 数 名  : AT_SendRnicIpv4v6ActInd
功能描述  : APP拨号时通知虚拟网卡IPV4V6激活
输入参数  : VOS_UINT8 ucRmNetId
输出参数  : 无
返 回 值  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_SendRnicIpv4v6ActInd(VOS_UINT8 ucRmNetId);

#endif

/*****************************************************************************
 函 数 名  : AT_NdisIPv4DeactiveCnfProc
 功能描述  : IPV4类型的pdp去激活成功，Ndis处理
 输入参数  : pEvent  --- 事件内容
 输出参数  : 无
 返 回 值  : 无

*****************************************************************************/
VOS_VOID AT_NdisIPv4DeactiveCnfProc(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_DeActiveUsbNet
 功能描述  : 去激活USB虚拟网卡
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_DeActiveUsbNet(VOS_VOID);

/*****************************************************************************
 函 数 名  : AT_PS_GetDataChanlCfg
 功能描述  : 获取数传通道配置信息
 输入参数  : VOS_UINT16                          usClientId
             VOS_UINT8                           ucCid
 输出参数  : 无
 返 回 值  : AT_PS_DATA_CHANL_CFG_STRU*

*****************************************************************************/
AT_PS_DATA_CHANL_CFG_STRU* AT_PS_GetDataChanlCfg(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 函 数 名  : AT_PS_RegFCPoint
 功能描述  : 注册流控点
 输入参数  : ucCallId   - 拨号实体ID
             pstEvent   - 事件信息
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_RegFCPoint(
    VOS_UINT8                           ucCallId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_PS_GetCidByCallType
 功能描述  : 获取呼叫类型对应的CID
 输入参数  : usClientId - 端口ID
             ucCallId  - 呼叫实体索引
             enPdpType - PDP类型
 输出参数  : 无
 返 回 值  : VOS_UINT8 - CID

*****************************************************************************/
VOS_UINT8 AT_PS_GetCidByCallType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 函 数 名  : AT_PS_SetCallStateByType
 功能描述  : 根据PDP类型设置呼叫状态
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
             enPdpType  - PDP类型(IPv4, IPv6 or IPv4v6)
             enPdpState - PDP状态
 输出参数  : 无
*****************************************************************************/
VOS_VOID AT_PS_SetCallStateByType(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    AT_PDP_STATE_ENUM_U8                enPdpState
);

/*****************************************************************************
 函 数 名  : AT_PS_SndCallConnectedResult
 功能描述  : 连接建立状态上报
 输入参数  : ucCallId  - 呼叫实体索引
             enPdpType - PDP类型
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_SndCallConnectedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

/*****************************************************************************
 函 数 名  : AT_PS_SndCallEndedResult
 功能描述  : 上报连接状态^DEND
 输入参数  : ucCallId  - 呼叫实体索引
             enPdpType - PDP类型
             enCause   - 错误码
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_SndCallEndedResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

/*****************************************************************************
 函 数 名  : AT_PS_IsLinkGoingUp
 功能描述  : 判断拨号连接是否已建立/正在建立
 输入参数  : usClientId - 端口ID
             ucCallId  - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 连接已建立/正在建立
             VOS_FALSE - 连接未建立
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingUp(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 函 数 名  : AT_PS_IsLinkGoingDown
 功能描述  : 判断拨号连接是否正在断开
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_TRUE
             VOS_FALSE
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkGoingDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 函 数 名  : AT_PS_IsLinkDown
 功能描述  : 判断拨号连接是否已经断开
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 连接不存在
             VOS_FALSE - 连接存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_PS_IsLinkDown(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 函 数 名  : AT_PS_GetFcIdFromRnicByRmNetId
 功能描述  : 获取RNIC网卡的FCID
 输入参数  : VOS_UINT32                          ulRmNetId
 输出参数  : 无
 返 回 值  : FC_ID_ENUM_UINT8
*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdFromRnicByRmNetId(
    VOS_UINT32                          ulRmNetId
);

/*****************************************************************************
 函 数 名  : AT_PS_GetFcIdByUdiDeviceId
 功能描述  : 通过DIPC通道ID获得FCID
 输入参数  : UDI_DEVICE_ID                       enDataChannelId
 输出参数  : 无
 返 回 值  : FC_ID_ENUM_UINT8
*****************************************************************************/
FC_ID_ENUM_UINT8 AT_PS_GetFcIdByUdiDeviceId(
    UDI_DEVICE_ID_E                     enDataChannelId
);

/*****************************************************************************
 函 数 名  : AT_PS_ProcConflictDialUpWithCurrCall
 功能描述  : 处理拨号连接建立冲突
 输入参数  : ucIndex  - 端口号(ClientId)索引
             ucCallId - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_OK   - 成功
             VOS_ERR  - 失败
*****************************************************************************/
VOS_UINT32 AT_PS_ProcConflictDialUpWithCurrCall(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 函 数 名  : AT_PS_ReportCurrCallConnState
 功能描述  : 上报当前已建立的拨号连接状态
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallConnState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);


/*****************************************************************************
 函 数 名  : AT_PS_ReportCurrCallEndState
 功能描述  : 上报当前已断开的拨号连接状态
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_PS_ReportCurrCallEndState(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
 函 数 名  : AT_PS_IsIpv6Support
 功能描述  : 判断是否支持IPV6
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_PS_IsIpv6Support(VOS_VOID);

/*****************************************************************************
 函 数 名  : AT_PS_GetCallStateByCid
 功能描述  : 根据CID获取呼叫状态
 输入参数  : usClientId - 端口ID
             ucCallId   - 呼叫实体索引
             ucCid      - CID
 输出参数  : 无
 返 回 值  : AT_PDP_STATE_ENUM_U8
 调用函数  :
*****************************************************************************/
AT_PDP_STATE_ENUM_U8 AT_PS_GetCallStateByCid(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 函 数 名  : AT_PS_SndRnicIpv4PdpActInd
 功能描述  : 给RNIC发送PDP激活事件, IPv4类型
 输入参数  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv4PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_PS_SndRnicIpv6PdpActInd
 功能描述  : 给RNIC发送PDP激活事件, IPv6类型
 输入参数  : VOS_UINT8                           ucCid
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
 输出参数  : 无
 返 回 值  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_SndRnicIpv6PdpActInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);

/*****************************************************************************
 函 数 名  : AT_PS_SndDipcPdpDeactBearerTypeInd
 功能描述  : AT向DIPC通道发送PDP去激活消息
 输入参数  : TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
             DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpDeactBearerTypeInd(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
);

/*****************************************************************************
 函 数 名  : AT_PS_SndDipcPdpActBearerTypeInd
 功能描述  : AT向DIPC通道发送PDP激活消息
 输入参数  : ucCid          ----  CID
             pstEvent       ----  PsCallEventInfo
             enBearerType   ----  BearerType
 输出参数  : 无
 返 回 值  : 无

*****************************************************************************/
VOS_VOID  AT_PS_SndDipcPdpActBearerTypeInd(
    VOS_UINT8                           ucCid,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent,
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType
);

/******************************************************************************
 函 数 名  : AT_LenStr2IpAddr
 功能描述  : 将字符串格式的IP地址转化为SM协议IP地址格式.完全继承V100R001
 输入参数  : pucStr - 字符串格式的IP地址
 输出参数  : pucIpAddr - SM协议定义的IP地址
 返 回 值  : TAF_SUCCESS - 转化成功
             TAF_FAILURE - 转化失败
******************************************************************************/
VOS_UINT32  AT_LenStr2IpAddr(
    VOS_UINT8                           *pucStr,
    VOS_UINT8                           *pucIpAddr
);

/******************************************************************************
 函 数 名  : AT_DHCPServerSetUp
 功能描述  : 根据ptrDHCPParam参数配置DHCP Server的状态，并通过ptrDHCPConfig
                返回DHCP Server最终的配置(包括最后的网关、掩码等)
                当关闭DHCP Server时，允许最后两项参数为空
 输入参数  : pstEvent指向PDP去激活的指针
 输出参数  : AT_DHCP_SETUP_PARAM_ST *ptrDHCPCfg       DHCP配置参数
             AT_DHCP_CONFIG_STRU    *ptrDHCPConfig    返回DHCP所有配置
 返 回 值  : VOS_OK      正确
             VOS_ERR     错误
******************************************************************************/
VOS_UINT32  AT_DHCPServerSetUp(
    AT_DHCP_SETUP_PARAM_ST              *ptrDHCPParam,
    AT_DHCP_CONFIG_STRU                 *ptrDHCPConfig
);

/*****************************************************************************
 函 数 名  : AT_PS_ReportAllCallEndState
 功能描述  : 上报所有拨号连接断开状态
 输入参数  : ucIndex - 端口号(ClientId)索引
 输出参数  : 无
 返 回 值  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_ReportAllCallEndState(VOS_UINT8 ucIndex);

/*****************************************************************************
 函 数 名  : AT_PS_SetCid2CurrCall
 功能描述  : 设置当前呼叫CID
 输入参数  : usClientId - 端口ID
             ucCallId  - 呼叫实体索引
             enPdpType - PDP类型
             ucCid     - CID
 输出参数  : 无
 返 回 值  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_SetCid2CurrCall(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 函 数 名  : AT_PS_PdpAddrProc
 功能描述  : 处理IPv4地址参数
 输入参数  : ucCallId      - 呼叫实体索引
             pstDhcpConfig - DCHP信息
             pstEvent      - 上报事件
 输出参数  : 无
 返 回 值  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_PS_PdpAddrProc(
    VOS_UINT8                           ucCallId,
    AT_DHCP_CONFIG_STRU                *pstDhcpConfig,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);


/*****************************************************************************
 函 数 名  : AT_AppSndRnicPdpActInd
 功能描述  : APP拨号时根据PDP类型给RNIC发送激活消息
 输入参数  : enPdpType      PDP类型
 输出参数  : 无
 返 回 值  : VOS_VOID

*****************************************************************************/
VOS_VOID AT_AppSndRnicPdpActInd(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
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

#endif


