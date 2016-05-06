#ifndef _AUTH_AM_PUBLIC_H_H_H_
#define _AUTH_AM_PUBLIC_H_H_H_

#include "a11_ip_public.h"

#define BUFF_2048BYTE              2048
#define AAA_PPPC_AUTH_EVENTBIT              0x1<<4


#define AAA_L2TP_LNS_NUM 2
#define RD_TUNNEL_STR_MAX_LENG 32
#define RD_FRAMED_POOL_MAX_LENG 31

/* 以下定义AAA模块中的错误原因值，适用于g_RDA_ulErrCode */
#define RDA_SUCCESS        0         /* 成功 */
#define RDA_FAIL           1         /* 失败 */
#define RDA_UNKNOW_ERR     3         /* 流程出错，不应该发生的地方使用的返回值 */
#define RDA_AUTH_FAIL      4
#define RDA_CREAT_PACKET_FAIL              20   /* 逻辑包创建失败 */
#define RDA_GET_NAS_IP_FAIL                21   /* 得到NAS IP失败 */
#define RDA_NO_MEMORY                      22   /* 没有内存       */

#define RDA_DNS_CFG_LOCAL     0
#define RDA_DNS_CFG_RADIUS    1
#define RDA_DNS_CFG_DHCP     2

/*  与PPPC间的消息类型  */
#define    PPPC_AAA_CREAT_REQ                0    /* 鉴权请求 */
#define    AAA_PPPC_CREAT_RSP                1    /* 鉴权响应 */

/*  鉴权应答原因值  */
#define  AAA_AUTH_SUCCESS           0  /* 鉴权成功 */
#define  AAA_AUTH_FAIL              1  /* 鉴权拒绝 */
#define  AAA_AUTH_SRV_ERR           2  /* 服务器故障或与服务器通信异常 */
#define  AAA_AUTH_CLT_ERR           3  /* RDA模块内资源耗尽等异常 */
#define  AAA_AUTH_MSG_FMT_ERR       4  /* 消息格式错误 */
#define  AAA_AUTH_IP_ERR            5  /* IP地址分配有误 */
#define  AAA_POD_DELETE            6  /* POD去活 */
#define NAI_NAME_LEN            63/* Modified by zhudaoming 62333 at 2007-12-05 GGSN9811V9R7C01B02 for L2TP/PPP V9移植 */
#define RD_FRAMED_INTERFACE_ID_LEN  8
#define RD_FRAMED_IPV6_PREFIX_LEN   16
#define RD_FRAMED_IPV6_PREFIX_BIT_LEN   64
#define HSGW_MAX_CLASS_LEN               128

#define NEMC_AAA_BASE    0xa500

/*定义有关MipAgent的标记位*/
#define AAA_MIPAGENT_FLAGBIT_S  0x80
#define AAA_MIPAGENT_FLAGBIT_D  0x20
#define AAA_MIPAGENT_FLAGBIT_R  0x04
#define AAA_MIPAGENT_FLAGBIT_T  0x02
#define AAA_MIPAGENT_FLAGBIT_X  0x01

#define AAA_MIPAGENT_FLAGBIT_ALL  0x6f
#define AAA_TELE_MIPAGENT_FLAGBIT_ALL  0x49

#define RD_HW_MIPAGENT_MNHA_SECRET_MAXLEN   18
#define RD_MIPV6AGENT_MNHA_SECRET_LEN 32

/*定义用户类型*/
#define FA_USERTYPE_SIP         0
#define FA_USERTYPE_MIP         1
#define FA_USERTYPE_MIPAGENT    2

#define RD_MIPAGENT_USERTYPE_BIT 0x01
#define RD_MIPAGENT_FLAGS_BIT 0x02
#define RD_MIPAGENT_LIFETIME_BIT 0x04
#define RD_MIPAGENT_HAADDR_BIT 0x08
#define RD_MIPAGENT_HOMEADDR_BIT 0x10
#define RD_MIPAGENT_SPI_BIT 0x20
#define RD_MIPAGENT_SECRET_BIT 0x40



typedef enum
{
    A11_NO_SEND = 0,

    A11_FIRST_TIME,

    A11_SECOND_TIME,

    A11_PPP_RENEGO

}A10_TBL_SEND_TIME_E;     /* A10表发送次数（需要分两次发送）*/

enum AAA_MsgCode
{
    NEMC_AAA_DUMMY = NEMC_AAA_BASE,
    NEMC_AAA_AUTH_GTPC_REQ,             /* GTPC鉴权请求消息 0xf201*/
    NEMC_AAA_GTPC_DEL_REQ,              /* AAA发起去活消息  0xf203*/
    NEMC_AAA_PPPC_AUTH_REQ,             /* PPPC鉴权请求消息 0xf204*/
    NEMC_AAA_SERVER_TO_AAA,           /* Server发送给AAA的消息*/
    AAA_GET_SERVER_STATUS
};

typedef struct
{
    VOS_UINT32 ulIpQos;
    VOS_UINT32 ulSessionTimeOut;
    VOS_UINT32 ulAAAindex;
    VOS_UINT32 ulInputPeakRate;      /* 上行峰值速率, 单位为bps*/
    VOS_UINT32 ulOutputPeakRate;     /* 下行峰值速率, 单位为bps*/
    VOS_UINT32 ulGuarantBitRateUp;   /* PDSN用户上行保证速率 (bps)*/
    VOS_UINT32 ulGuarantBitRateDown; /* PDSN用户下行保证速率(bps) */
    UCHAR ucRateFlag;
    UCHAR ucPreparedFlag;
    UCHAR ucResv[2];
    /* ucRateFlag后4位标志接收了哪些速率信息（0表示没有，1表示收到）：
    0000***1                第0位表示是否收到ulInputPeakRate
    0000**1*                第1位表示是否收到ulOutputPeakRate
    0000*1**                第2位表示是否收到ulGuarantBitRateUp
    00001***                第3位表示是否收到ulGuarantBitRateDown */
}VOS_PACKED QOS_ACCOUNT_INFOR;


typedef struct tagMIPAGENT_SHARESECRET_S
{
    UCHAR ucLen;
    UCHAR ucSecret[RD_HW_MIPAGENT_MNHA_SECRET_MAXLEN];  /* 隧道密码 */
	UCHAR ucResv;
} MIPAGENT_SHARESECRET_S;




/*MIP Agent返回属性的暂存结构*/
typedef struct tagRD_MIPAGENT_VSA_S
{
    UCHAR                  ucVsaFlag;
    UCHAR                  ucCdmaUserType;/*0-SIP, 1---MIP, 2---MIP Agent*/
    VOS_UINT16                 usMipAgentLifetime;   /* LNS地址 */
    VOS_UINT32                  ulMipAgentHaAddr;
    VOS_UINT32                  ulMipAgentHomeAddr;
    VOS_UINT32                  ulMipAgentSpi;
    MIPAGENT_SHARESECRET_S stMipAgentSecret;  /* 隧道密码 */
    UCHAR                  ucMipAgentFlag;
    UCHAR                  ucResv[3];
} RD_MIPAGENT_VSA_S;


#define AAA_AUTHRSP_S AAA_PPPC_AUTH_RSP_S



#define A11_USER_PROFILE_NAME_LENGTH 64

/* 鉴权响应 */
typedef struct tagAaaAuthRspMsg
{
    MSG_HDR_S stNeMsgHdr;             /* NE80头 */
    VOS_UINT32 ulMsgType;                /* 消息类型 */
    VOS_UINT32 ulSDBIndex;               /* context索引 即SDB索引 */

    UCHAR ucStcValue;

    UCHAR ucResv;
    UCHAR ucResult;                 /* 鉴权结果 */
    UCHAR ucUsernameLen;            /* 用户名长度 */
    UCHAR ucUsername[NAI_NAME_LEN+1]; /* 用户名 */
    QOS_ACCOUNT_INFOR stQosAccInfo; /* 计费信息 */
    VOS_UINT32 ulIdleTimeout;            /* 会话超时时间 */
    VOS_UINT32 ulIPMTU;                  /* MTU参数 */
    VOS_UINT32 ulIp;                     /* IP地址 */
    VOS_UINT32 ulIpMask;                 /* IP地址子网掩码 */
    VOS_UINT32 ulPIMARY_DNS_SERVER;      /* 主DNS SERVER */
    VOS_UINT32 ulSECOND_DNS_SERVER;      /* 从DNS SERVER */
    VOS_UINT32 ulAlwaysOn;               /*r002*/
    /* Added start by liaomin 00130175, 2008/12/19 PDSN V900R007 问题单号: CR20081215006 */
    VOS_UINT32 ulMNAAAFlag;
    /* Added end by liaomin 00130175, 2008/12/19 PDSN V900R007 问题单号: CR20081215006 */
    VOS_UINT32 ulAcctInterimInterval;
     /* L2TP */
    /* Modified start by liaomin 00130175, 2008/11/26 PDSN V900R007 问题单号: AP8D05808 */
    VOS_UINT16 usTunnelType[AAA_L2TP_LNS_NUM];                 /* 隧道类型，目前只支持L2TP */
    VOS_UINT16 usTunnelMediaType[AAA_L2TP_LNS_NUM];            /* 公共网类型，目前只支持IP */
    VOS_UINT32  ulTunnelServer[AAA_L2TP_LNS_NUM];                   /* LNS地址 */
    VOS_UINT32  ulTunnelPreference[AAA_L2TP_LNS_NUM];
    UCHAR  ucTunnelClientAuthId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];   /* LAC名 */
    UCHAR  ucTunnelServerAuthId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];  /* LNS名 */
    UCHAR  ucTunnelPrivateGroupId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];          /* 隧道GroupID */
    UCHAR  ucTunnelAssignId[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG];         /* 隧道ID */
    UCHAR  ucPassword[AAA_L2TP_LNS_NUM][RD_TUNNEL_STR_MAX_LENG+1];   /* 隧道密码 */
    /* Modified end by liaomin 00130175, 2008/11/26 PDSN V900R007问题单号: AP8D05808 */
    UCHAR ucAAANotReturnIP;
    UCHAR ucRes;

    UCHAR  ucFramedPool[RD_FRAMED_POOL_MAX_LENG+1];  /* AAA 返回的地址池名framed-pool */
    UCHAR ucReplyMsg[NAI_NAME_LEN+1];

    UCHAR ucNaiMsid[NAI_NAME_LEN+1];
    UCHAR  ucCdmaUserType;                /*0-SIP, 1---MIP, 2---MIP Agent*/
    UCHAR  ucMipAgentFlag;
    VOS_UINT16 usMipAgentLifetime;
    VOS_UINT32  ulMipAgentHaAddr;
    VOS_UINT32  ulMipAgentHomeAddr;
    VOS_UINT32  ulMipAgentSpi;                       /* PMIPv4用户与HA间安全联盟SPI */
    VOS_UINT32  ulPmipV6Spi;                         /* PMIPv6用户与LMA间安全联盟SPI */

    MIPAGENT_SHARESECRET_S stMipAgentSecret;                   /* PMIPv4安全联盟 */
    UCHAR aucPmipV6Secret[RD_MIPV6AGENT_MNHA_SECRET_LEN];      /* PMIPv6安全联盟 */
    UCHAR ucMdn[MDN_MAX_LEN+1];/* Added by l61463 at 2008-06-18 PDSN V9 for 电信MDN需求 */
    UCHAR ucResv3;
    VOS_UINT16  bulIpQosFlag : 1,                  /* IP Qos */
            bulInputPeakRateFlag : 1,  /*上行峰值速率， 单位为bps*/
            bulOutputPeakRateFlag : 1, /*下行峰值速率， 单位为bps*/
            bulGuarantBitRateUpFlag : 1, /*PDSN用户上行保证速率 (bps)*/
            bulGuarantBitRateDownFlag : 1, /* PDSN用户下行保证速率(bps) */
            bulAllowed_AB_BETFlag : 1, /*bps*/
            bulMaxConnectionFlag : 1,
            bucRateFlagFlag : 1,
            bucAllowed_PTFTsFlag : 1,  /* Allowed Persistent TFTs */
            bucMaxPerFlowPriorityforUserFlag : 1,        /* Maximum Per Flow Priority for the User  */
            bucInterUserPriorityFlag : 1,                /* Inter-User Priority */
            bstA11SOProfileFlag : 1,
            bstAuthFlowProfileIDFlag : 1,     /* Authorized Flow Profile IDs for the User */
            bstAllowedDSCPMarkingFlag : 1; /* Allowed Differentiated Services Marking */

    A11_QOS_INFO_S stA11QoS;
    UCHAR szUserProfileName[A11_USER_PROFILE_NAME_LENGTH + 1]; /*User Profile名称的字符串*/
    UCHAR ucResv4[3];

    UCHAR aucVpnName[RD_HW_VPN_NAME_LEN_MAX + 1]; /* vpn name */
    /* BEGIN: Added for PN:重定向 by wangyong 00138171, 2009/9/27 */
    UCHAR ucFilterID;
    UCHAR ucIPType;
    UCHAR ucIPTypeFlag; /* 用于区分是否携带了RD_3GPP2_IP_SERVICES_AUTHORIZED属性，1：携带。0：未携带 */
    UCHAR ucActiveStopIndication:1;
    UCHAR ucUserClassAAAFlag:1;
    UCHAR ucResrved:6;
    /* END:   Added for PN:重定向 by wangyong 00138171, 2009/9/27 */
    UCHAR ucFramedInterfaceID[RD_FRAMED_INTERFACE_ID_LEN];
    UCHAR ucFramedIPV6Pool[RD_FRAMED_POOL_MAX_LENG + 1];
    UCHAR ucFramedIPV6Prefix[RD_FRAMED_IPV6_PREFIX_LEN];
    UCHAR ucLmaAddr[RD_FRAMED_IPV6_PREFIX_LEN];         /* PMIPv6 LMA地址 */
    VOS_UINT32 ulIpv6Mask;                     //扩展字段
    in6_addr stPriDNSIP;
    in6_addr stSecDNSIP;

}AAA_PPPC_AUTH_RSP_S;

#define CHARGE_RULE_BASE_NAME_MAX_LEN  32

/* COA_USM消息属性结构 */
typedef struct tagCOA_UPDATE_S
{
    A11_SQOS_DSCP_S stAllowedDSCPMarking;
    VOS_UINT32 ulAllowed_AB_BET;

    UCHAR aucChargeRuleName[CHARGE_RULE_BASE_NAME_MAX_LEN];
    UCHAR ucInterUserPriority;
    UCHAR ucFilterID;

    UCHAR bucAllowed_AB_BETFlag : 1;
    UCHAR bucAllowedDSCPMarkingFlag : 1;
    UCHAR bucInterUserPriorityFlag : 1;
    UCHAR bucFilterIDFlag : 1;
    UCHAR baucChargeRuleNameFlag : 1;

} COA_UPDATE_S;

extern VOS_UINT32  RDA_GetApnDNSCfg(VOS_UINT16 usApnIndex, DOMAINDNS_S *pstApn);
extern VOS_UINT32  RDA_GetApnDNSIpv6Cfg(VOS_UINT16 usApnIndex, DOMAINDNS_S *pstApn);
extern VOS_UINT32 RDA_CheckRadiusGroupForVirtualDomain(VOS_UINT16 usDomainIndex, VOS_UINT16 usGroupId, UCHAR *pucStatus);
extern VOID hmac_md5(UCHAR *text, int text_len, UCHAR *key, int key_len, UCHAR *digest);
extern VOS_UINT32 AUTH_GetVpnNameByIdx(VOS_UINT32 ulVpnIndex, UCHAR *uzVpnName);
extern VOS_UINT32 HSGW_AUTHOmInitial(VOID);
#endif


