/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : usm_am_public.h
  版 本 号   : 初稿
  作    者   : z00136627
  生成日期   : 2012年11月20日
  最近修改   :
  功能描述   : USM提供给其他模块的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月20日
    作    者   : z00136627
    修改内容   : 创建文件

******************************************************************************/

#ifndef __USM_API_H__
#define __USM_API_H__

#include "li_am_public.h"

extern PTM_COMPONENT_INFO_S g_stHsgwUsmCompInfo;
#define USM_SELF_CSI       g_stHsgwUsmCompInfo.ullSelfCsi
#define USM_SELF_CMPIDX    g_stHsgwUsmCompInfo.ulSelfCmpIdx
#define USM_SELF_SGID_INOS      g_stHsgwUsmCompInfo.ullSelfSgId
#define USM_SELF_CMPID_INSG      g_stHsgwUsmCompInfo.ulSelfCmpIdxInSG

/* Diameter Auth和USM之间的消息类型 */
#define USM_DIAM_AAA_REAUTHOR_REQ      1
#define DIAM_AAA_USM_REAUTHOR_RSP      2
#define DIAM_AAA_USM_REAUTHOR_NOTIFY   3

#define USM_EHRPD_SESSION_TIMEOUT_MIN             300
#define USM_EHRPD_REAUTH_TIME_AMOUNT_IN_ADVANCE   120

typedef enum
{
    USM_INNER_MSG_CODE_EXIT,  /* 内部队列退网消息 */
    USM_INNER_MSG_CODE_PHASE_RESULT, /* 内部队列状态机处理过程其他模块通知阶段完成消息 */
    USM_INNER_MSG_CODE_PDN_RELEASE,
    USM_INNER_MSG_CODE_PDN_RECONNECT,
    USM_INNER_MSG_CODE_BACKUP_BATCH,
    USM_INNER_MSG_CODE_BACKUP_SMOOTH,
    USM_INNER_MSG_DPS_CHECK,
    USM_INNER_MSG_CODE_BUTT

}USM_INNER_MSG_CODE_E;

typedef struct tagHSGW_TOKEN_STATE_S
{
    UCHAR ucLockFlag;
    UCHAR ucTerminateFlag;
    UCHAR ucRsv[2];
}HSGW_TOKEN_STATE_S;

typedef struct tagHSGW_DEA_RP_INFO_S
{
    VOS_UINT32  ulRPIndex;   //记录最后一次去活的上下文Index
    VOS_UINT16 usTokenId;    //记录去活的Token id
    UCHAR  ucDeaCause;   //记录去活原因
    UCHAR  ucReserved;
}HSGW_DEA_RP_INFO_S;

/* A11通知USM激活请求消息结构体 */
typedef struct
{
    A11_IMSI_S stIMSI;
    VOS_UINT32 ulRelReason;       /* 用户去活的原因码 */
}USM_A112USM_NEWREG_S;


/* A11 link up以后通知USM的结构体 */
typedef struct
{
    VOS_UINT32 ulRpIndex;
    VOS_UINT32 ulResultCode;
    VOS_UINT32 ulMsgType;
}USM_A11_LINKUP_RESULT_S;

typedef struct
{
    VOS_UINT32 ulRpIndex;
    /* LCP */
    VOS_UINT32 ulMagicNum;                /* Magic-Number */
    VOS_UINT32 ulAccm;
    VOS_UINT16 usMtu;
    UCHAR ucPPPMode;
    UCHAR ucReserve;
}USM_PPPC_LCPUP_USERINFO_S;      /* LCP OK后PPPC发往USM的用户信息结构 */

typedef struct
{
    VOS_UINT32 ulRpIndex;
    /* IPCP */
    VOS_UINT32 ulPppFlag;
    UCHAR ucPPPConFlag;
    UCHAR ucDmpuId;
    UCHAR ucDmpuDpeId;
   /* IPV6CP */

   /* CCP */

}USM_PPPC_IPCPUP_USERINFO_S;    /* IPV4V6CP OK 后PPPC发往USM的用户信息结构 */


/* diam授权请求 */
typedef struct tagUSMDiamAuthMsg
{
    VOS_UINT32 ulMsgType;            /* 消息类型 */
    VOS_UINT32 ulRpIndex;            /* SDB索引 */
    VOS_UINT32 ulNowUTCInSec;
    VOS_UINT16 usPeerID;            /* diameter aaa server ID */
    VOS_UINT16 usTokenId;           /* 上下文的TOKEN ID */
    A11_IMSI_S stIMSI;
    UCHAR aucUserName[DIAM_AUTH_USERNAME_MAX_LEN + 1];
    UCHAR ucAAAType;
}USM_DIAM_AUTH_MSG_S;

typedef struct tagDiamAuthUSMMsg
{
    VOS_UINT32 ulMsgType;                                                    /* 消息类型 */
    VOS_UINT32 ulRpIndex;                                                    /* context索引 即SDB索引 */
    VOS_UINT32 ulQosProfileID;                                               /* qos profile id */
    VOS_UINT32 ulSessionTimeout;                                             /* session timeout */
    VOS_UINT32 ulAccountInterval;                                            /* Accounting-Interim-Interval */
    VOS_UINT32 ulDefaultAPNId;                                               /* default APN id */
    DIAM_AUTH_APN_INFO_S stApnInfo[DIAM_AUTH_APN_INFO_MAX_NUMBER];      /* APN CONFIGURATION */
    VOS_UINT16 us3GPPCC;                               /* 计费属性 */
    UCHAR aucMdn[MDN_MAX_LEN+1];                                        /* 电信MDN需求 */
    UCHAR ucResult;                                                     /* 授权结果 */
    UCHAR ucApnInfoNum;                                                 /* APN INFO个数 */
    UCHAR aucRsv[3];
}DIAM_AUTH_USM_MSG_S;

/* PPP link up以后通知USM的结构体 */
typedef struct
{
    UCHAR *pucMsg; /* ppp根据用户类型需要挂AAA_AUTHRSP_S或者EAP鉴权响应结构体 */
    VOS_UINT32 ulRpIndex;
    VOS_UINT32 ulResultCode;
    VOS_UINT16 usDomainIndex;
    VOS_UINT16 usVirtualDomainIndex;
    UCHAR  aucNAI[A11_MAX_NAI_LENGTH + 1];                /* NAI */
}USM_PPP_LINKUP_RESULT_S;

/* Added start by y00170683 at 2013-03-25 PS10.1 for 3.2.5	PSR.UGWV9R10C01.PDSNPMIPv6.FUNC.005 支持IPv4单栈地址的PMIPv6会话注册 */
/* PMIPv6模块PDSN时需要使用的字段----NVSE扩展和NAI */
typedef struct tagUSM_PMIPV6_CONTEXT_DATA
{
    /* PDSN需要使用的信息 */
    UCHAR aucNai[A11_MAX_NAI_LENGTH +1];                /* NAI */

    VOS_UINT32 ulPcfIP;
    VOS_UINT32 ulCorrelationID;

    UCHAR aucSubnet[A11_AIR_REC_MAX_SUBNET_LEN];      /*Subnet For HRPD d7*/
    UCHAR ucSubnetLen;
    UCHAR aucBsId[A11_MSID_LEN];
    UCHAR aucEsn[A11_AIR_REC_MAX_ESN_LEN/2];

    UCHAR ucServiceOption;
    UCHAR bBsidFlagPmipv6:1;  /* BSID是否携带标记 */
    UCHAR aucReserved3[2];

    /* HSGW需要使用的信息 */
    GTP_MSISDN szMsisdn; /* MSISDN */
    UCHAR aucMnId[DIAM_AUTH_MNID_MAX_LENGTH + 1];    /* 从DEA消息的Mobile-Node-Identifier字段获取 */

    VOS_UINT32 ulMagGreKey; /* HSGW */
    VOS_UINT32 ulLmaGreKey;
}USM_PMIPV6_CONTEXT_DATA_S;
/* Added end by y00170683 at 2013-03-25 PS10.1 for 3.2.5	PSR.UGWV9R10C01.PDSNPMIPv6.FUNC.005 支持IPv4单栈地址的PMIPv6会话注册 */
typedef enum
{
    EHRPD_VSNCP_PRO_OK = 0,                 /* 正常处理 */
    EHRPD_VSNCP_PRO_ERR = 1,                /* 异常处理 */
    EHRPD_VSNCP_PRO_COPY = 2,               /* 缓存处理 */
    EHRPD_VSNCP_PRO_BUTT
}EHRPD_VSNCP_PRO_CODE_E;


typedef enum
{
    USM_STATE_INIT = 1,                 /* 1 初始状态 */
    USM_STATE_WT_A11_SETUP,             /* 2 等待A11链路建立完成 */
    USM_STATE_WT_PPP_SETUP,             /* 3 等待PPP链路建立完成 */
    USM_STATE_WT_PDN_SETUP,             /* 4 等待PDN建立完成 */
    USM_STATE_ACTIVE,                   /* 5 激活态 */
    USM_STATE_DIFF_HANDOFF,             /* 6 切换态 */
    USM_STATE_WT_DIAM_AUTHORIZE,        /* 7 等待获取授权信息 */
    USM_STATE_WT_PPP_RELEASE,           /* 8 等待PPP链路释放完成 */
    USM_STATE_WT_A11_RELEASE,           /* 9 等待A11链路释放完成 */
    USM_STATE_WT_PDN_RELEASE,           /* 10 等待PDN链路释放完成 */

    USM_STATE_BUTT
}USM_STATE_E;



/* 其他模块通知USM的消息码 */
typedef enum tagUSM_OTHER2USM_MSGTYPE_E
{
    E_USM_MSGTYPE_A112USM_SETUP = 200, /* A11通知USM建立完成的消息码 */
    E_USM_MSGTYPE_PPP2USM_SETUP,       /* PPP通知USM建立完成的消息码 */
    E_USM_MSGTYPE_PDN2USM_SETUP,       /* PDN通知USM建立完成的消息码 */
    E_USM_MSGTYPE_PPP2USM_RELEASE,     /* PPP通知USM去活完成的消息码 */
    E_USM_MSGTYPE_A112USM_RELEASE,     /* A11通知USM去活完成的消息码 */
    E_USM_MSGTYPE_PDN2USM_RELEASE,     /* PDN通知USM去活完成的消息码 */
    E_USM_MSGTYPE_BUTT,

}USM_OTHER2USM_MSGTYPE_E;

/* USM状态机事件定义，注意要和g_pszUsmEventName保持一致 */
typedef enum
{
    USM_EVENT_A11_NEW_REG        = 1,   /* 新用户激活事件 */
    USM_EVENT_A11_SETUP_OK,             /* A11链路创建成功事件 */
    USM_EVENT_A11_SETUP_FAIL,           /* A11链路创建失败事件 */
    USM_EVENT_A11_RELEASE_OK,           /* 用户去活时A11侧链路释放完成事件 */
    USM_EVENT_A11_UPDATE         = 5,   /* A11发起的参数更新事件 */
    USM_EVENT_PPP_SETUP_OK,             /* PPP链路创建成功事件 */
    USM_EVENT_PPP_SETUP_FAIL,           /* PPP链路协商失败事件 */
    USM_EVENT_PPP_RELEASE_OK,           /* 用户去活时PPP侧链路释放完成事件 */
    USM_EVENT_PDN_SETUP_OK,             /* PDN建立成功事件 */
    USM_EVENT_PDN_SETUP_FAIL     = 10,  /* PDN建立失败事件 */
    USM_EVENT_PDN_RELEASE_OK,           /* 用户去活时PDN释放完成事件 */
    USM_EVENT_RELEASE_USER,             /* 各模块发起的去活事件 */
    USM_EVENT_A11_LINK_DOWN,            /* pcf发起的去活事件 */
    USM_EVENT_LMA_RELEASE_DIFFHAND,     /* LMA因为用户在网络间切换释放PDN */
    USM_EVENT_DIAM_REAUTHOR_NOTIFY,     /* AAA发起重授权，成功后Diameter Auth通知USM更新事件 */
    USM_EVENT_DIAM_REAUTHOR_OK,         /* USM发起重授权，Diameter Auth重授权成功事件 */
    USM_EVENT_DIAM_REAUTHOR_FAIL,       /* USM发起重授权，Diameter Auth重授权失败事件 */

    USM_EVENT_A11_SETUP_TIMEOUT,        /* 等待A11链路创建完成超时 */
    USM_EVENT_PPP_SETUP_TIMEOUT,        /* 等待PPP链路创建完成超时 */
    USM_EVENT_PDN_SETUP_TIMEOUT,        /* 等待PDN链路创建完成超时 */
    USM_EVENT_A11_RELEASE_TIMEOUT,      /* 等待A11链路释放完成超时 */
    USM_EVENT_PPP_RELEASE_TIMEOUT,      /* 等待PPP链路释放完成超时 */
    USM_EVENT_PDN_RELEASE_TIMEOUT,      /* 等待PDN链路释放完成超时 */
    USM_EVENT_DIAM_REAUTHOR_TIMEOUT,    /* 等待Diameter Auth重授权完成超时 */
    USM_EVENT_CON_MAINTAIN_TIMEOUT,     /* 网间切换资源保留定时器超时 */
    USM_EVENT_REAUTH_TIMEOUT,           /* 重鉴权定时器超时 */

    USM_EVENT_INNER_ERR,                /* USM状态机内部异常事件 */

    USM_EVENT_COA_UPD,                  /* auth通知COA更新事件 */

    /*Added by liushuang for qos-update*/
    USM_EVENT_SM_QOSUPD,             /*sm 通知qos更新*/
    /*End of liushuang*/
    USM_EVENT_BUTT
}USM_EVENT_E;


typedef enum enumUSM_BLACK_BOX_STRING_CODE_E
{
    USM_BLACK_BOX_STRING_A11_T_BIT_ERR = 1,

    USM_BLACK_BOX_STRING_CODE_BULT_E,
}USM_BLACK_BOX_STRING_CODE_E;

typedef struct
{
    A11_IMSI_S stImsi;
    VOS_UINT32   ulPeerSigAddr;
    VOS_UINT32    ulPeerTeidc;
    UCHAR *pucDomain;  /* domain 或者 apn */

    VOS_UINT32 ulImsiFlg :1;
    VOS_UINT32 ulPeerSigAddrFlg :1;
    VOS_UINT32 ulPeerTeidcFlg   :1;
    VOS_UINT32 uleHRPDMode      :1;
    UCHAR *pucReason;
    UCHAR *pucSuggestion;
}HSGW_EMS_ARGUMENT_S;

typedef enum
{
    HSGW_EMS_MODULE_USM,
    HSGW_EMS_MODULE_A11,
    HSGW_EMS_MODULE_PPP,
    HSGW_EMS_MODULE_PDN,
    HSGW_EMS_MODULE_FA,
    HSGW_EMS_MODULE_PMIPV6,
    HSGW_EMS_MODULE_AUTH,
    HSGW_EMS_MODULE_DIAM_AUTH,
    HSGW_EMS_MODULE_RESV,
    HSGW_EMS_MODULE_DHCP,
    HSGW_EMS_MODULE_HSGWSDU,

    HSGW_EMS_MODULE_BULT,
}HSGW_EMS_MODULE_E;

typedef enum
{
    EMS_USM_0_EHRPD_USER_LIMIT,
    EMS_USM_1_HRPD_1XUSER_LICE_LIMIT,
    EMS_USM_2_HRPD_DOUSER_LICE_LIMIT,
    EMS_USM_3_HRPD_RPUSER_LICE_LIMIT,
    EMS_USM_4_CREATE_RPCONTEXT_FAIL,
    EMS_USM_5_ALLOC_CHARGEID_FAIL,
    EMS_USM_6_HSGW_AUTH_FAIL_NO_APN,
    EMS_USM_7_HSGW_REAUTH_FAIL_NO_APN,
    EMS_USM_8_USER_RELEASE_CODE,
    EMS_USM_9_HSGW_IMSI_MISMATCH,
    EMS_USM_10_HSGW_MNID_IMSI_INVALID,
    EMS_USM_11_HSGW_NO_APN_RESOURCE,
    EMS_USM_12_NOT_ENOUGH_HSGW_PDN_LICENSE,
    EMS_USM_BULT,
};

typedef enum
{
    EMS_A11_0_LOCK,
    EMS_A11_1_TIMESTAMP_NOTIN_RANGE,
    EMS_A11_2_PCF_NOT_CONFIG,
    EMS_A11_3_AUTH_CHECK_FAIL,
    EMS_A11_4_PCFIP_KEY_CONFLICT,
    EMS_A11_5_ENTRY_NO_AUXA10,
    EMS_A11_6_ENTRY_NO_SETUP,
    EMS_A11_7_HSGW_SO_ERR,
    EMS_A11_8_UPD_SO_ERR,
    EMS_A11_9_NO_ACT_CREATE_AUX,
    EMS_A11_10_L2TP_NO_AUX,
    EMS_A11_11_PREPAID_NO_AUX,
    EMS_A11_12_NVSE_ERR,
    EMS_A11_13_CVSE_ERR,
    EMS_A11_14_IMSI_MSID_ERR,
    EMS_A11_15_FLAG_ERR,
    EMS_A11_16_HA_NOT_0,
    EMS_A11_17_HAGENT_ERR,
    EMS_A11_18_SO33_AUX_ERR,
    EMS_A11_19_AUX_TOO_MUCH,
    EMS_A11_20_HRPD_NO_VERCHG,
    EMS_A11_21_VERCHG_LIS_LIMIT,
    EMS_A11_22_EHRPD_NO_VERCHG,
    EMS_A11_23_VERCHG_LIS_LIMIT,
    EMS_A11_24_KEY_ERR,
    EMS_A11_25_EHRPD_SO_ERR,
    EMS_A11_26_A10_TOO_MUCH,
    EMS_A11_27_HSGW_A10_LIS_LIMIT,
    EMS_A11_28_EVDO_A10_LIS_LIMIT,
    EMS_A11_29_CRTEAT_10_ERR,
    EMS_A11_30_UPD_A10_ERR,
    EMS_A11_31_CREATE_A10_ERR,
    EMS_A11_32_WAIT_2ND_RRQ_FAIL,
    EMS_A11_33_AUX_SO_ERR,
    EMS_A11_34_SQOS_NO_64,
    EMS_A11_35_SQOS_NO_67,
    EMS_A11_36_NO_FLOW_ID,
    EMS_A11_37_FILL_QOS_ERR,
    EMS_A11_38_NO_FLOW_ID,
    EMS_A11_39_NO_FLOW_ID,
    EMS_A11_40_ENTRY_SO_ERR,
    EMS_A11_41_FLOWLICENSE_OVER_ERR,
    EMS_A11_42_FLOWLICENSE_IS_ZERO,
    EMS_A11_43_A11_MSG_AUTHEXT_NOT_EXIST,
    EMS_A11_44_A11_MSG_UNKNOW_EXT,

    EMS_A11_BULT,
};

typedef enum
{
    EMS_PPP_0,
    EMS_PPP_1,
    EMS_PPP_2,
    EMS_PPP_3,
    EMS_PPP_4,
    EMS_PPP_5,
    EMS_PPP_6,
    EMS_PPP_7,
    EMS_PPP_8,
    EMS_PPP_9,
    EMS_PPP_10,
    EMS_PPP_11,
    EMS_PPP_12,
    EMS_PPP_13,
    EMS_PPP_14,
    EMS_PPP_15,
    EMS_PPP_16,
    EMS_PPP_17,
    EMS_PPP_18,
    EMS_PPP_19,
    EMS_PPP_20,
    EMS_PPP_21,
    EMS_PPP_22,
    EMS_PPP_23,
    EMS_PPP_24,
    EMS_PPP_25,
    EMS_PPP_26,
    EMS_PPP_27,
    EMS_PPP_28,
    EMS_PPP_29,
    EMS_PPP_30,
    EMS_PPP_31,
    EMS_PPP_32,
    EMS_PPP_33,
    EMS_PPP_34,
    EMS_PPP_35,
    EMS_PPP_36,
    EMS_PPP_37,
    EMS_PPP_38,
    EMS_PPP_39,
    EMS_PPP_40,
    EMS_PPP_41,
    EMS_PPP_42,
    EMS_PPP_43,
    EMS_PPP_44,
    EMS_PPP_45,
    EMS_PPP_46,
    EMS_PPP_47,
    EMS_PPP_48,
    EMS_PPP_49,
    EMS_PPP_50,
    EMS_PPP_BULT,
};

typedef enum
{
    EMS_PDN_0_NO_AAA_IPV6,
    EMS_PDN_1_STATIC_IP_TOO_MUCH,
    EMS_PDN_2_NO_FREE_IP,
    EMS_PDN_3_CONFLICT,
    EMS_PDN_4_NOT_IN_RANGE,
    EMS_PDN_5_NO_FREE_IP,
    EMS_PDN_6_IP_TYPE_ERR,
    EMS_PDN_7_IPCP_TIMEOUT,
    EMS_PDN_8,
    EMS_PDN_9,
    EMS_PDN_10_TOO_MUCH_PDN,
    EMS_PDN_11_APN_NOT_CONFIGURED,
    EMS_PDN_12_APN_AAA_NOT,
    EMS_PDN_13_PDN_TYPE_NOT_INDICATED,
    EMS_PDN_14_FQDN_NOT_FIND,
    EMS_PDN_15_HOST_NOT_FIND,
    EMS_PDN_16_SELECT_DNS_ERR,
    EMS_PDN_17_NO_PDSN_PCC_LIS,
    EMS_PDN_18_NO_HSGW_PCC_LIC,
    EMS_PDN_19_GET_PGW_FAIL,
    EMS_PDN_20_NO_IPV4,
    EMS_PDN_21_NO_IPV6,
    EMS_PDN_22_IPV6_ERR,
    EMS_PDN_23_DEA_CALL_BY_LNS,
    EMS_PDN_24_DEA_TUN_BY_LNS,
    EMS_PDN_25_DEA_TUN_BY_FAULT,
    EMS_PDN_26_DEA_TUN_CHAP_ERR,
    EMS_PDN_27_NO_VPN,
    EMS_PDN_28_NO_PIIF,
    EMS_PDN_29_NO_PMIP_LIC,
    EMS_PDN_30_GET_PARA_FAIL,
    EMS_PDN_31_HA_ADDR_ERR,
    EMS_PDN_32_IPV6_LIC_LIMIT,
    EMS_PDN_33_NO_POOL,
    EMS_PDN_34_CONFLICT,
    EMS_PDN_35_NOT_IN_RANGE,
    EMS_PDN_36_ALLOC_FAIL,
    EMS_PDN_37_MIP_LIC_LIMIT,
    EMS_PDN_38_NO_HSGW_PDN_LICENSE,
    EMS_PDN_39_PDN_HAS_SETUP,
    EMS_PDN_40_DEA_BY_L2TP,
    EMS_PDN_41_NO_HSGW_DUALSTACK_LICENSE,
    EMS_PDN_42_NO_PMIPV6_LICENSE,
    EMS_PDN_43_DNS_SORT_ERR,
    EMS_PDN_44_DNS_NO_CLIENT_IP,
    EMS_PDN_45_NO_DNS_SERVER,
    EMS_PDN_46_DNS_INSERT_TARGET_FAIL,
    EMS_PDN_47_DNS_TARGET_TIMEOUT,
    EMS_PDN_48_DNS_REMOTE_QRY_FAIL,
    EMS_PDN_49_VSNCP_RECONNECT_REL,

    EMS_PDN_BULT,
};


typedef enum
{
    EMS_FA_0_NO_FA_HA_SA,
    EMS_FA_1,
    EMS_FA_2,
    EMS_FA_3,
    EMS_FA_4,
    EMS_FA_5,
    EMS_FA_6,
    EMS_FA_7,
    EMS_FA_8,
    EMS_FA_9,
    EMS_FA_10,
    EMS_FA_11,
    EMS_FA_12,
    EMS_FA_13,
    EMS_FA_14,
    EMS_FA_15,
    EMS_FA_16,
    EMS_FA_17,
    EMS_FA_18,
    EMS_FA_19,
    EMS_FA_20,
    EMS_FA_21,
    EMS_FA_22,
    EMS_FA_23,
    EMS_FA_24,
    EMS_FA_25,
    EMS_FA_26,
    EMS_FA_27,
    EMS_FA_28,
    EMS_FA_29,
    EMS_FA_30,
    EMS_FA_31,
    EMS_FA_32,
    EMS_FA_33,
    EMS_FA_34,
    EMS_FA_35,
    EMS_FA_36,
    EMS_FA_37,
    EMS_FA_38,
    EMS_FA_39,
    EMS_FA_40,
    EMS_FA_41,
    EMS_FA_42,
    EMS_FA_43,
    EMS_FA_44,
    EMS_FA_45,
    EMS_FA_46,
    EMS_FA_47,
    EMS_FA_48,
    EMS_FA_49,
    EMS_FA_50,
    EMS_FA_51,
    EMS_FA_52,
    EMS_FA_53,
    EMS_FA_54,
    EMS_FA_55,
    EMS_FA_56,
    EMS_FA_57,
    EMS_FA_58,
    EMS_FA_59,
    EMS_FA_60,
    EMS_FA_61,
    EMS_FA_62,
    EMS_FA_63,
    EMS_FA_64,
    EMS_FA_65,
    EMS_FA_66,
    EMS_FA_67,
    EMS_FA_68,
    EMS_FA_69,
    EMS_FA_70,
    EMS_FA_71,
    EMS_FA_72,
    EMS_FA_73,
    EMS_FA_74,
    EMS_FA_75,

    EMS_FA_BULT,
};

typedef enum
{
    EMS_PMIPV6_0_LMA_IFADDRESS_NOMATCH,
    EMS_PMIPV6_1_PBA_MNAUTH_LENTH_SHORT,
    EMS_PMIPV6_2_PBA_LAST_ISNOT_MNAUTH,
    EMS_PMIPV6_3_PBA_MNAUTHSUB_ISNOT_MNHA,
    EMS_PMIPV6_4_PBA_SPI_NOTMATCH,
    EMS_PMIPV6_5_PBA_AUTHEN_NOPASS,
    EMS_PMIPV6_6_PBA_STATUS_ABNORMAL,
    EMS_PMIPV6_7_UPDPBA_IPV4ADDR_INVALID,
    EMS_PMIPV6_8_UPDPBA_IPV6ADDR_INVALID,
    EMS_PMIPV6_9_PBA_NO_TIMESSTAMP,
    EMS_PMIPV6_10_PDSN_NO_MNID,
    EMS_PMIPV6_11_PDSN_HANDOFFID_ERR,
    EMS_PMIPV6_12_PDSN_ACCESSTECH_ERR,
    EMS_PMIPV6_13_PDSN_TIMESSTAMP_ERR,
    EMS_PMIPV6_14_PDSN_CORRID_ERR,
    EMS_PMIPV6_15_HSGW_MNID_ERR,
    EMS_PMIPV6_16_HSGW_HANDOFFID_ERR,
    EMS_PMIPV6_17_HSGW_ACCESSTECH_ERR,
    EMS_PMIPV6_18_HSGW_TIMESSTAMP_ERR,
    EMS_PMIPV6_19_HSGW_SSM_ERR,
    EMS_PMIPV6_20_HSGW_GREKEY_ERR,
    EMS_PMIPV6_21_HSGW_CHARGINGID_ERR,
    EMS_PMIPV6_22_PBA_IPADDR_NOMATCH,
    EMS_PMIPV6_23_PBA_LINKLOCAL_ERR,
    EMS_PMIPV6_24_PBA_DEFUALTROUTER_ERR,
    EMS_PMIPV6_25_IPV4ADDR_ERR,
    EMS_PMIPV6_26_IPV6ADDR_ERR,
    EMS_PMIPV6_27_NOT_IPBOTH,
    EMS_PMIPV6_28_GREKEY_CHANGE,
    EMS_PMIPV6_29_LIFETIME_ERR,
    EMS_PMIPV6_30_LIFETIME_ERR,
    EMS_PMIPV6_31_LIFETOUT,
    EMS_PMIPV6_32_PBA_REG_LIFETOUT,
    EMS_PMIPV6_33_RELV6_ERR,
    EMS_PMIPV6_34_RELV4_ERR,
    EMS_PMIPV6_35_PBA_STATUS_128,
    EMS_PMIPV6_36_PBA_STATUS_129,
    EMS_PMIPV6_37_PBA_STATUS_130,
    EMS_PMIPV6_38_PBA_STATUS_131,
    EMS_PMIPV6_39_PBA_STATUS_132,
    EMS_PMIPV6_40_PBA_STATUS_133,
    EMS_PMIPV6_41_PBA_STATUS_134,
    EMS_PMIPV6_42_PBA_STATUS_135,
    EMS_PMIPV6_43_PBA_STATUS_136,
    EMS_PMIPV6_44_PBA_STATUS_137,
    EMS_PMIPV6_45_PBA_STATUS_138,
    EMS_PMIPV6_46_PBA_STATUS_139,
    EMS_PMIPV6_47_PBA_STATUS_140,
    EMS_PMIPV6_48_PBA_STATUS_141,
    EMS_PMIPV6_49_PBA_STATUS_142,
    EMS_PMIPV6_50_PBA_STATUS_143,
    EMS_PMIPV6_51_PBA_STATUS_144,
    EMS_PMIPV6_52_PBA_STATUS_145,
    EMS_PMIPV6_53_PBA_STATUS_146,
    EMS_PMIPV6_54_PBA_STATUS_147,
    EMS_PMIPV6_55_PBA_STATUS_148,
    EMS_PMIPV6_56_PBA_STATUS_149,
    EMS_PMIPV6_57_PBA_STATUS_150,
    EMS_PMIPV6_58_PBA_STATUS_151,
    EMS_PMIPV6_59_PBA_STATUS_152,
    EMS_PMIPV6_60_PBA_STATUS_153,
    EMS_PMIPV6_61_PBA_STATUS_154,
    EMS_PMIPV6_62_PBA_STATUS_155,
    EMS_PMIPV6_63_PBA_STATUS_156,
    EMS_PMIPV6_64_PBA_STATUS_157,
    EMS_PMIPV6_65_PBA_STATUS_158,
    EMS_PMIPV6_66_PBA_STATUS_159,
    EMS_PMIPV6_67_PBA_STATUS_160,
    EMS_PMIPV6_68_PBA_STATUS_161,
    EMS_PMIPV6_69_PBA_STATUS_162,
    EMS_PMIPV6_70_PBA_STATUS_163,
    EMS_PMIPV6_71_PBA_STATUS_164,
    EMS_PMIPV6_72_PBA_STATUS_165,
    EMS_PMIPV6_73_PBA_STATUS_166,
    EMS_PMIPV6_74_PBA_STATUS_167,
    EMS_PMIPV6_75_PBA_STATUS_168,
    EMS_PMIPV6_76_PBA_STATUS_169,
    EMS_PMIPV6_77_PBA_STATUS_170,
    EMS_PMIPV6_78_PBA_STATUS_171,
    EMS_PMIPV6_79_PBA_STATUS_172,
    EMS_PMIPV6_80_PBA_STATUS_173,
    EMS_PMIPV6_81_PBA_STATUS_174,
    EMS_PMIPV6_82_PBA_STATUS_175,
    EMS_PMIPV6_83_PBA_STATUS_176,
    EMS_PMIPV6_84_PBA_STATUS_OTHER,
    EMS_PMIPV6_85_NO_VALID_PIIF,
    EMS_PMIPV6_86_NO_VALID_LMA,
    EMS_PMIPV6_87_NO_VALID_LMA,

    EMS_PMIPV6_BULT,
};


typedef enum
{
    EMS_AUTH_0_NO_SERVER,
    EMS_AUTH_1_GET_SERVER_FAIL,
    EMS_AUTH_2_GET_SRCIP_FAIL,
    EMS_AUTH_3_DECODE_FAIL,
    EMS_AUTH_4_CHECK_AUTH_FAIL,
    EMS_AUTH_5_CHECK_PCC_FAIL,
    EMS_AUTH_6_AAA_REJECT,
    EMS_AUTH_7_NO_SERVER,
    EMS_AUTH_8_CHECK_MIP_FAIL,
    EMS_AUTH_9_GET_APN_FAIL,
    EMS_AUTH_10_GET_PASSWORD_FAIL,
    EMS_AUTH_11_CHECK_L2TP_FAIL,
    EMS_AUTH_BULT,
};

typedef enum
{
    EMS_DIAM_AUTH_0,
    EMS_DIAM_AUTH_1,
    EMS_DIAM_AUTH_2,
    EMS_DIAM_AUTH_3,
    EMS_DIAM_AUTH_4,
    EMS_DIAM_AUTH_5,
    EMS_DIAM_AUTH_6,
    EMS_DIAM_AUTH_7,
    EMS_DIAM_AUTH_8,
    EMS_DIAM_AUTH_9,
    EMS_DIAM_AUTH_10,
    EMS_DIAM_AUTH_11,
    EMS_DIAM_AUTH_12,
    EMS_DIAM_AUTH_13,
    EMS_DIAM_AUTH_14,
    EMS_DIAM_AUTH_15,
    EMS_DIAM_AUTH_16,
    EMS_DIAM_AUTH_17,
    EMS_DIAM_AUTH_18,
    EMS_DIAM_AUTH_19,

    EMS_DIAM_AUTH_20,
    EMS_DIAM_AUTH_21,
    EMS_DIAM_AUTH_22,
    EMS_DIAM_AUTH_23,
    EMS_DIAM_AUTH_24,
    EMS_DIAM_AUTH_25,
    EMS_DIAM_AUTH_26,
    EMS_DIAM_AUTH_27,
    EMS_DIAM_AUTH_28,
    EMS_DIAM_AUTH_29,
    EMS_DIAM_AUTH_BULT,
};

typedef enum
{
    EMS_RESV_0,

    EMS_RESV_BULT,
};

typedef enum
{
    EMS_DHCP_0_NO_RELAY_FLAG,
    EMS_DHCP_1_MSG_INVALID,
    EMS_DHCP_2_ACKMSG_IP_INCORRECT,
    EMS_DHCP_BULT,
};

typedef enum
{
    EMS_HSGWSDU_0_SEL_TOKEN_FAIL,
    EMS_HSGWSDU_1_ADD_NODE_FAIL,

    EMS_HSGWSDU_BULT,
};

typedef enum
{
    USM_BLACKBOX_CODE_0,
    USM_BLACKBOX_CODE_1,
    USM_BLACKBOX_CODE_2,
    USM_BLACKBOX_CODE_3,
    USM_BLACKBOX_CODE_4,
    USM_BLACKBOX_CODE_5,/* not used from here */

    USM_BLACKBOX_CODE_BULT = 20,
}USM_BLACKBOX_CODE_E;



#define M_STATE_IS_DELETPROCESS(enstate)    \
    ((USM_STATE_WT_PDN_RELEASE == enstate) \
    || (USM_STATE_WT_PPP_RELEASE == enstate) \
    || (USM_STATE_WT_A11_RELEASE == enstate))

#define M_STATE_IS_ENTERPROCESS(enstate)    \
    ((USM_STATE_INIT == enstate)   \
    ||(USM_STATE_WT_A11_SETUP == enstate) \
    ||(USM_STATE_WT_PPP_SETUP == enstate) \
    ||(USM_STATE_WT_PDN_SETUP == enstate)) \

#define M_STATE_IS_ACTIVE(enstate) \
    ((USM_STATE_ACTIVE == enstate)   \
    ||(USM_STATE_DIFF_HANDOFF == enstate) \
    ||(USM_STATE_WT_DIAM_AUTHORIZE == enstate)) \

#define M_STATE_IS_TEMP(enstate) (!M_STATE_IS_ACTIVE(enstate))

#define M_USM_SETLI_HANDOFF_INFO(Option, HandOffPcfInfo, RpContext, LiContextInfo) \
    if ((PDSN_OPTION_HANDOFF == (Option)) && ((HandOffPcfInfo) != NULL)) \
    { \
        (LiContextInfo).uchandOffType = 1; \
        (LiContextInfo).ucGotOldIpFlag = VOS_TRUE; \
        (LiContextInfo).ucCanIdLen = A11_MAX_ANID_LENGTH; \
        (LiContextInfo).ucPanIdLen = A11_MAX_ANID_LENGTH; \
        VOS_MemCpy((LiContextInfo).szPanId, (RpContext)->ucPanid, (LiContextInfo).ucPanIdLen); \
        VOS_MemCpy((LiContextInfo).szCanId, (RpContext)->ucCanid, (LiContextInfo).ucCanIdLen); \
        VOS_MemCpy((VOID *)(LiContextInfo).szAccPcfIpAddr, (VOID *)&((HandOffPcfInfo)->ulPrePcfIp), sizeof(VOS_UINT32)); \
        VOS_MemCpy((VOID *)(LiContextInfo).szCurPcfIPAdd, (VOID *)&((HandOffPcfInfo)->ulCurPcfIp), sizeof(VOS_UINT32)); \
    }

#define M_USM_SETLI_ESN_INFO(Esn, LiContextInfo) \
    if( 0 == VOS_StrLen(Esn) ) \
    { \
        (LiContextInfo)->ucEsnLen = 0; \
    } \
    else \
    { \
        (LiContextInfo)->ucEsnLen = ESNBCDLEN; \
        VOS_MemCpy((LiContextInfo)->szESN, (Esn), ESNBCDLEN); \
    }

#define  M_USM_SETLI_MEID_INFO(RpContext, LiContextInfo) \
    if( VOS_FALSE == (RpContext)->bMEIDValidFlg )  \
    { \
        (LiContextInfo)->ucMeidLen = 0; \
    } \
    else \
    { \
        (LiContextInfo)->ucMeidLen = MEIDBCDLEN; \
        VOS_MemCpy((LiContextInfo)->szMEID, ((RpContext)->aucMEID), MEIDBCDLEN); \
    }

#define  M_USM_SETLI_MDN_INFO(RpContext, LiContextInfo) \
    if ( VOS_FALSE == (RpContext)->ucMsisdnFlag) \
    { \
        (LiContextInfo)->ucMdnLen = 0;       \
    } \
    else \
    { \
        (LiContextInfo)->ucMdnLen = MDNBCDLEN; \
        VOS_MemCpy((LiContextInfo)->szMDN, (RpContext)->szMsisdn, MDNBCDLEN); \
    }

#define  M_USM_SETLI_BSID_INFO(RpContext, LiContextInfo) \
    if ((RpContext)->bBsidFlag) \
    { \
        (LiContextInfo)->ucBsidFlag = (RpContext)->bBsidFlag ; \
        VOS_MemCpy((LiContextInfo)->aucBsid, (RpContext)->ucBsId, AM_BSID_LEN); \
    }

#define  M_USM_SETLI_FAIL_INFO(Flag, Option, ResultCode, LiContextInfo) \
       if ((PDSN_FAIL == (Flag)) && (PDSN_OPTION_SETUP == (Option))) \
       { \
           if ( E_LI_A11_ADMIN_PROHIBTED == (ResultCode) ) \
           { \
               (LiContextInfo).usFailureCause = 0xD2; \
           } \
           else \
           { \
               (LiContextInfo).usFailureCause = (ResultCode); \
           } \
       }

#define  M_USM_SETLI_RELEASE_INFO(Option, ResultCode, LiContextInfo) \
       if (PDSN_OPTION_RELEASE == (Option)) \
       { \
           (LiContextInfo).usReleaseCause = (ResultCode); \
       }

#define M_USM_SETLI_PACKETFILTER_INFO(PfContext, LiContextInfo) \
    if (NULL != (PfContext)) \
    { \
        (LiContextInfo).stX2PacketFilterInfo.next   = NULL; \
        if ( (PfContext)->ucLength <= 100 ) \
        { \
            (LiContextInfo).stX2PacketFilterInfo.length = (PfContext)->ucLength; \
        } \
        else \
        { \
            (LiContextInfo).stX2PacketFilterInfo.length = 100; \
        } \
        VOS_MemCpy((LiContextInfo).stX2PacketFilterInfo.value, PfContext, (LiContextInfo).stX2PacketFilterInfo.length);  \
    }


extern UCHAR *g_pucLiReleaseCvt;

/*  获取监听的退网原因值 */
#define M_USM_GETLI_RELEASE_CODE(ReleaseCode)  (AM_RELCODE_BUTT <= (ReleaseCode))? E_LI_RELEASE_PDSN_ERR : g_pucLiReleaseCvt[ReleaseCode]

#define A11_MAX_QOSCAR_RATE_BPS     14*1024*1024
#define A11_MAX_QOSCAR_RATE_KBPS    14*1024

#define USM_SPU_RPODUCT_TYPE g_ulHsgwUsmProductType

extern VOS_UINT32 g_ulHsgwUsmProductType;
extern CRM_SPU_BOARD_TYPE_ENUM g_ulHsgwUsmSpuType;
extern VOS_UINT32 g_ulHsgwSduNum;
extern VOS_UINT64 *g_pullHsgwSduCsi;
extern VOS_UINT32 g_ulUsmDelSduNaiResFlg;
extern VOS_UINT32 g_ulUsmDelL2tpResFlg;
extern VOS_UINT32 g_ulHsgwDbgEmsFlg;
extern VOS_UINT32 g_ulUsmSgRestartAtActiveBoardFlg;

extern VOS_UINT32 USM_GetCmReleaseCode( VOS_UINT32 ulRelCode );
extern VOS_UINT32 USM_NotifyReleaseUserMsg(VOS_UINT32 ulRpIndex, VOS_UINT32 ulReleaseCode);
extern VOS_UINT32 USM_NotifyReleaseUserFunc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulReleaseCode, UCHAR* pucMsg);
extern VOS_UINT32 USM_NotifyPhaseResultFunc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulMsgtype, VOS_VOID *pResultInfo);
extern VOS_UINT32 USM_NotifyPhaseResultMsg(VOS_UINT32 ulRpIndex, VOS_UINT32 ulMsgtype);
extern VOS_BOOL USM_IsDefaultApn(VOS_UINT32 ulRpIndex, VOS_UINT16 usApnIndex);
extern VOS_UINT32 USM_GetApnCfgByApnName(UCHAR *pucApnName, HSGW_APN_INFO_S **ppstHsgwApn);
extern VOS_UINT32 USM_GetApnCfgByApnIndex(VOS_UINT16 usApnIndex, HSGW_APN_INFO_S **ppstHsgwApn);
extern VOS_UINT32 USM_Pmipv6GetRpDataByPdnIndex(VOS_UINT32 ulPdnIndex,
                                                        USM_PMIPV6_CONTEXT_DATA_S *pstPmipv6RpContextData);
extern VOS_UINT32 USM_Pmipv6GetDataForPfTable(VOS_UINT32 ulPdnIndex,
                                                VOS_UINT32 *pulTeidc,
                                                UCHAR *pucDpeId);
extern DIAM_AUTH_APN_INFO_S* USM_GetDiamApnInfo(VOS_UINT32 ulRpIndex, VOS_UINT16 usApnIndex);
extern DIAM_AUTH_APN_INFO_S* USM_GetApnWithCorrectFunction(VOS_UINT32 ulRpIndex, VOS_UINT16 usApnIndex, VOS_UINT32* pulFlag);
extern VOS_UINT32 USM_GetApnIndexByApnName(UCHAR *pucApnName, VOS_UINT16 *pusApnIndex);
extern VOS_UINT32 USM_GetPcrfcReleaseCode( VOS_UINT32 ulRelCode );
extern VOS_UINT32 USM_GetSduCsiBySduId(VOS_UINT32 ulSduId, VOS_UINT64 *pullSduCsi);
extern VOID USM_DebugOut(VOS_UINT32 ulLevel, CHAR* pszFile, VOS_UINT32 ulLineNo, CHAR *pszFuncName, CHAR *pszFormat, ...);
extern VOS_UINT32 USM_A11NotifyUpdateReg( SDB_PDSN_RP_CONTEXT_S *pstRpContext, UCHAR *pucMsg);
extern VOS_UINT32 USM_A11NotifyNewReg(A11_IMSI_S stIMSI , UCHAR *pucMsg);
extern UCHAR USM_GetA11ReleaseCode( VOS_UINT32 ulRelCode );
extern VOS_UINT32 USM_NotifyReconnectPDNMsg(UCHAR *pucMsg, VOS_UINT32 ulRpIndex, VOS_UINT32 ulReleaseCode);
extern VOS_UINT32 USM_NotifyReleasePDNMsg(VOS_UINT32 ulRpIndex, VOS_UINT32 ulReleaseCode);
extern VOS_UINT32 USM_GetVsncpNegoFlag(VOS_UINT32 ulRpIndex);


extern VOS_UINT32 USM_BackupSlaveCreUpdRpProc(UCHAR *pucCurrent);
extern VOS_UINT32 USM_BackupSlaveUpdateApnProc(UCHAR *pucCurrent);
extern VOS_UINT32 USM_BackupMasterCreUpdRpProc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulOperType, UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 USM_BackupMasterUpdateApnProc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulOperType, UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 USM_BackupMasterDelRpProc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulOperType, UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 USM_BackupSlaveDelRpProc(UCHAR * pucCurrent);
extern VOID USM_SendInnerLowMsg( VOS_UINT32 ulMsgType, VOS_UINT32  ulPara );
extern VOS_UINT32 USM_BackupSmoothSingleUser(SDB_PDSN_RP_CONTEXT_S *pstRpContext);
extern VOID OM_EncryptPrivacyData(const VOS_CHAR * strIn, VOS_INT32 lenIn, VOS_CHAR * strOut);

extern VOS_BOOL USM_IsActiveState(VOS_UINT32 ulRpIndex);
extern VOS_BOOL USM_IsEntryState(VOS_UINT32 ulRpIndex);
extern VOS_BOOL USM_IsReleaseState(VOS_UINT32 ulRpIndex);
extern VOID USM_PdnNotifyUpdateFinishProc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulUpdateType);
extern VOS_UINT32 USM_GetEhrpdModeFromRp(VOS_UINT32 ulRpIndex, UCHAR *pucEhrpdMode);
extern VOID USM_BackupSlaveDelAllResource(VOS_UINT32 ulRpIndex);
extern VOID USM_NotiyLIWithoutContextForPDSN(UCHAR ucCause, A11_PRE_PARSER_S *pstPreParser, A11_LI_PDSN_OPTION_E enOp);

extern VOID USM_NotifyLIForPDSN(VOS_UINT32 ulRpindex,
                                VOS_UINT16 usResultCode,
                                A11_RESV_PF_CONTENT_S *pstPfContext,
                                A11_LI_PCF_CONTEXT_S *pstHandOffPcfInfo,
                                A11_LI_PDSN_OPTION_E ulOption,
                                A11_LI_PDSN_FLAG ulFlag);
extern VOID USM_SetLiFlagToRpcontext(VOS_UINT32 ulRpindex,LI_USM_FLAG_S *pstLiUsmFlag);
extern VOS_UINT32 USM_LIGetContextByTargetID(UCHAR ucTargetIdType,UCHAR *pucTargetId,LI_CDMA2000_PDPINFO_S *pstLiPdpinfo);
extern VOID PPP_LI_SetAuInfo(LI_CDMA2000_PDPINFO_S *pstLiContextInfo, VOS_UINT32 ulRpindex);
extern VOS_UINT32 USM_LIGetContextByRpintexforBatchBackup(VOS_UINT32 ulRpIndex,LI_CDMA2000_PDPINFO_S *pstLiPdpinfo);
extern VOS_UINT32 USM_LICheckInEnterProcess(VOS_UINT32 ulRpindex);

extern VOS_UINT32 USM_GetDiamauthReleaseCode( VOS_UINT32 ulRelCode );
VOID HSGW_EmsTraceByA11ParserNoContext(A11_PRE_PARSER_S *pstPreParser, VOS_UINT32 ulModule, VOS_UINT32 ulCode);
VOS_VOID HSGW_EmsTraceByRpIndex(VOS_UINT32 ulRpIndex, VOS_UINT32 ulModule, VOS_UINT32 ulCode);
VOID HSGW_EmsTraceByRpContext(SDB_PDSN_RP_CONTEXT_S *pstRpContext,
                              HSGW_EMS_ARGUMENT_S *pstArgs,
                              HSGW_EMS_MODULE_E enInnerModuleType, VOS_UINT32 ulCode);
VOS_VOID HSGW_EmsTraceByPdnIndex(VOS_UINT32 ulPdnIndex, VOS_UINT32 ulModule, VOS_UINT32 ulCode);
extern VOS_UINT32 HSGW_RegEmsAtSduSG(VOID);
extern VOID USM_LiImsiToString( A11_IMSI_S stImsi ,UCHAR*szTemp);
extern void USM_LiStringToBCD(CHAR *strSrc, UCHAR DstArr[], UCHAR ucMaxNum);
extern VOS_UINT32 USM_LIRelContextByTargetID(UCHAR ucTargetIdType,UCHAR * pucTargetId);
extern VOS_UINT32 USM_GetContextTokenNumOfCurSg(VOID);
extern VOID HSGW_EmsTraceByRpContextAndSuggArgus(SDB_PDSN_RP_CONTEXT_S *pstRpContext,
                                          HSGW_EMS_ARGUMENT_S *pstArgs,
                                          HSGW_EMS_MODULE_E enInnerModuleType, VOS_UINT32 ulCode, UCHAR *pszFormat, ...);

extern VOS_UINT32 USM_GetDeaSingleUserMaxTime(VOID);

#endif /* __USM_API_H__ */
