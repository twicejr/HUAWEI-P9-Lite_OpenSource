/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

******************************************************************************
  文 件 名   : hsgw_pmipv6_am_public.h
  版 本 号   : 初稿
  作    者   : yangfangwei 00170683
  生成日期   : 2013年1月15日
  最近修改   :
  功能描述   : pmipv6模块提供给AM子系统的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年1月15日
    作    者   : yangfangwei 00170683
    修改内容   : 创建文件
******************************************************************************/

#ifndef __HSGW_PMIPV6_AM_PUBLIC_H__
#define  __HSGW_PMIPV6_AM_PUBLIC_H__

/*******************************************************************************************************/
/********************                          宏定义                           ************************/
/*******************************************************************************************************/

#define PMIPV6_MAX_V6ADDR_LEN 16   /* V6地址最大长度 */
#define PMIPV6_MAX_PREFIX_LEN 8    /* V6地址前缀最大长度 */
#define PMIPV6_MAX_V4ADDR_LEN 4    /* V4地址最大长度 */
#define PMIPV6_MAX_MNID_LEN 63     /* MNID最大长度 */
#define PMIPV6_MAX_MSISDN_LEN 8     /* MSISDN最大长度 */
#define PMIPV6_MAX_3GPP_PCO_VALUE_TOTAL_LEN     253   /* PCO最大长度253 */
#define PMIPV6_MAX_3GPP_PCO1_VALUE_LEN     248   /* PCO最大长度248 参考29282协议 */
#define PMIPV6_MAX_3GPP_PCO1_EXTERN_LEN     254   
#define PMIPV6_MAX_3GPP_PCO2_VALUE_LEN     5   /* 第二个PCO扩展最大长度 */
#define PMIPV6_MAX_3GPP_PCO2_EXTERN_LEN     11   
#define PMIPV6_MAX_KEY_LEN 32 /* PDSN用户填充authentication扩展 */

/* ipv4封装时PMIPV6端口号定义 */
#define PMIPV6_IPV4_SRC_PORT    5436
#define PMIPV6_IPV4_DST_PORT    5436

/* 消息缓存长度 */
#define PMIPV6_REV_MSG_MAXLEN 4096  /* 接收消息最大长度 */
#define PMIPV6_SEND_MSG_MAXLEN 1024  /* 发送消息最大长度 PCO 253字节 */
#define PMIPV6_CHECKSUM_MAXLEN PMIPV6_REV_MSG_MAXLEN + 40  /* 接收消息最大长度 */

/* PMIPV6消息头定义 */
#define PMIPV6_NEXTHDR_MH    135
#define PMIPV6_NEXTHDR_NONEXTHEADER    59

/* PMIPV6事件位 */
#define PMIPV6_PBA_EVENT             0x01
#define PMIPV6_BRI_EVENT             0x02
#define PMIPV6_HEART_EVENT           0x04
#define PMIPV6_PDN_EVENT            0x08
#define PMIPV6_TIMER_EVENT          0x10
#define PMIPV6_INNER_HIGH_EVENT     0x20
#define PMIPV6_INNER_LOW_EVENT      0x40

/* 用户类型 */
typedef enum
{
    PMIPV6_USER_TYPE_PDSN,  /* PDSN */
    PMIPV6_USER_TYPE_HSGW,  /* HSGW */

    PMIPV6_USER_TYPE_BUTT
} PMIPV6_USER_TYPE_E;

/* 地址类型 */
typedef enum
{
    PMIPV6_ADDR_TYPE_NONE = 0,  /* 地址类型非法 */
    PMIPV6_ADDR_TYPE_V4 = 1,  /* V4单栈 */
    PMIPV6_ADDR_TYPE_V6 = 2,  /* V6单栈 */
    PMIPV6_ADDR_TYPE_V4V6,   /* 双栈 */

    PMIPV6_ADDR_TYPE_BUTT
} PMIPV6_ADDR_TYPE_E;



/* PGW拒绝的地址类型 */
typedef enum
{
    PMIPV6_PDN_INDIC_V4 = 1,  /* V4 */
    PMIPV6_PDN_INDIC_V6,      /* V6 */

    PMIPV6_PDN_INDIC_BUTT
} PMIPV6_PDN_INDIC_E;

/* Handoff Indicator */
 typedef enum
 {
    PMIPV6_HI_RESERVED    = 0,
    PMIPV6_HI_NEW_INTER   = 1,
    PMIPV6_HI_DIFFERNT    = 2,
    PMIPV6_HI_SAME        = 3,
    PMIPV6_HI_UNKNOWN     = 4,
    PMIPV6_HI_NO_CHANGE   = 5,
    
    PMIPV6_HI_BUTT
 }PMIPV6_HI_TYPE_E;


/* PDN发送给PMIPV6的请求消息消息码 */
typedef enum
{
     E_AM_PDN_PMIPV6_REG_REQ,       /* 0 初始注册时使用 */
     E_AM_PDN_PMIPV6_ALLOC_IPV4_REQ,/* 1 申请V4单栈 */
     E_AM_PDN_PMIPV6_ALLOC_IPV6_REQ,/* 2 申请V6单栈 --只有pdsn存在 */
     E_AM_PDN_PMIPV6_REL_IPV4_REQ,  /* 3 释放V4单栈 --只有pdsn存在 */
     E_AM_PDN_PMIPV6_REL_IPV6_REQ,  /* 4 释放V6单栈 --只有pdsn存在 */
     E_AM_PDN_PMIPV6_REL_REQ,        /* 5 释放用户 */
     E_AM_PDN_PMIPV6_UPDATE_WIRELESS,  /* 6 无线参数更新 --只有pdsn存在 */
     E_AM_PDN_PMIPV6_UPDATE_VSNCP,      /* 7 PCO更新 --只有hsgw存在 */     
     
     E_AM_PDN_PMIPV6_MSGCODE_BUTT,
} PDN_PMIPV6_MSGCODE_E;

/* PMIPV6发送给PDN的消息码 */
typedef enum
{
    /* 响应 */
    E_AM_PMIPV6_PDN_REG_RSP,  
    E_AM_PMIPV6_PDN_ALLOC_IPV4_RSP,  
    E_AM_PMIPV6_PDN_ALLOC_IPV6_RSP, /* 2 申请V6单栈 --只有pdsn存在 */  
    E_AM_PMIPV6_PDN_UPDATE_VSNCP_RSP, /* 3 PCO更新响应 --只有hsgw存在 */  

    /* 需要封装消息体的消息码放在该消息码之前 */
    E_AM_PMIPV6_PDN_REL_IPV4_RSP,  /* 4 释放V4单栈 --只有pdsn存在 */  
    E_AM_PMIPV6_PDN_REL_IPV6_RSP,  /* 5 释放V6单栈 --只有pdsn存在 */   

    /* 请求 */
    E_AM_PMIPV6_PDN_REL,/* 释放请求和释放响应使用一个消息码*/
    E_AM_PMIPV6_PDN_REL_IP_REQ,/* 通知PDN释放单栈 释放类型由PMIPV6_PDN_MSG_S--ucbit2RelAddrType携带 */

    E_AM_PMIPV6_PDN_MSGCODE_BUTT,
} PMIPV6_PDN_MSGCODE_E;

/*******************************************************************************************************/
/********************                          结构体                           ************************/
/*******************************************************************************************************/

/* 发送消息使用的地址信息 */
typedef struct tagPMIPV6_IP_INFO
{
    VOS_UINT32 ulMagSubId;
    VOS_UINT32 ulMagIfId;    
    VOS_UINT32 ulMoudleId;
    VOS_UINT16 usMagVpnId;
    UCHAR ucEncapeType;
    UCHAR ucDpeId;
    VOS_UINT32 ulMagIpv4Addr;    
    UCHAR aucMagIpv6Addr[PMIPV6_MAX_V6ADDR_LEN]; 
    UCHAR aucLmaAddr[PMIPV6_MAX_V6ADDR_LEN]; 
}PMIPV6_IP_INFO_S;

/* PDN发送给PMIPV6的请求消息结构体 */
typedef struct tagPDN_PMIPV6_REQ
{
    A11_IMSI_S stImsi;                     /* IMSI */

    VOS_UINT32 ulPdnIndex;                     /* PDN索引 */
    VOS_UINT32 ulPmipv6Index;                  /* PMIPV6索引 */

    VOS_UINT32 ulLmaAddrV4;                         /* LMA-v4地址 */
    VOS_UINT32 ulHomeAddrV4;                        /* IPV4 address */

    VOS_UINT32 ulUpdateMask;                          /* 发生更新的掩码--只有pdsn存在 */    
    VOS_UINT16 usApnIndex;                           /* 从DEA消息获取APN对应的索引--只有hsgw存在 */    
    UCHAR ucDpeId;
    UCHAR ucbit2AddrType:2;                   /* 1-v4, 2-v6, 3-双栈 PMIPV6_ADDR_TYPE_E */
    UCHAR ucbit1UserType:1;                   /* 用户类型 0-HSGW,1-PDSN PMIPV6_USER_TYPE_E */
    UCHAR ucbit3HandOffFlg:3;                 /* 是否发生HSGW切换--PMIPV6_HI_TYPE_E */
    UCHAR ucbit2Reserved:2;

    UCHAR aucHomeAddrV6[PMIPV6_MAX_V6ADDR_LEN];  /* IPV6 address */
    UCHAR aucLmaAddrV6[PMIPV6_MAX_V6ADDR_LEN];   /* LMA-v6地址 */
    UCHAR aucShareKey[PMIPV6_MAX_KEY_LEN];       /* PMN-LMA */
    
    UCHAR auc3GppPco[PMIPV6_MAX_3GPP_PCO_VALUE_TOTAL_LEN];
    UCHAR uc3GppPcoLen;
    VOS_UINT16 us3GppChargingChara;                 /* chargingchara 为字符--只有hsgw存在 */

    VOS_UINT32 ulSpi;                                  /* 只有pdsn存在 */
    UCHAR aucRes4[4];
} PDN_PMIPV6_REQ_S;

/* PMIPV6发送给PDN的消息结构体 */
typedef struct tagPMIPV6_PDN_MSG
{
    VOS_UINT32 ulPdnIndex;                /* PDN索引 */
    VOS_UINT32 ulPmipv6Index;            /* Pmipv6索引 */    
    VOS_UINT32 ulResultCode;             /* 消息码 0-success */
    UCHAR aucReserved[4];

    UCHAR ucbit2PdnIndicator :2;   /* 1-v4,2-v6 PMIPV6_PDN_INDIC_E--只有hsgw存在 */
    UCHAR ucbit1DelayFlg :1;       /* V4延迟分配标志--只有hsgw存在 */
    UCHAR ucbit1SigEncapeType:1;   /* 信令封装格式 0-v4,1-v6 PMIPV6_SIG_ENCAPE_TYPE_E*/
    UCHAR ucbit2RelAddrType :2;    /* 释放的栈类型 PMIPV6_ADDR_TYPE_E */
    UCHAR ucbit2Resved :2;    
    UCHAR ucPdnIndicatorCause;  /* PDN Type Indication-cause值--只有hsgw存在 */
    UCHAR ucPmipv6ErrCode;      /* 3GPP Specific PMIPv6 Error Code--只有hsgw存在  */
    UCHAR ucReserved;
    
    VOS_UINT32 ulHomeAddrV4;                             /*IPV4 address */
    VOS_UINT32 ulRouterAddrV4;                           /*router address--只有hsgw存在 */
    VOS_UINT32 ulPriDnsIp;                               /*IPV4 Primary DNS--只有pdsn存在 */
    VOS_UINT32 ulSecDnsIp;                               /*IPV4 Secondary DNS--只有pdsn存在 */

    UCHAR aucLmaAddr[PMIPV6_MAX_V6ADDR_LEN];        /*LMA address--只有pdsn存在(CSN功能)*/    
    UCHAR aucHomeAddrV6[PMIPV6_MAX_V6ADDR_LEN];     /*IPV6 address*/
    UCHAR aucLinkLocalAddr[PMIPV6_MAX_V6ADDR_LEN];  /*Link local address*/
    UCHAR aucPriV6DnsIp[PMIPV6_MAX_V6ADDR_LEN];     /*IPV6 Primary DNS--只有pdsn存在 */
    UCHAR aucSecV6DnsIp[PMIPV6_MAX_V6ADDR_LEN];     /*IPV6 Secondary DNS--只有pdsn存在 */

    VOS_UINT32 ulGreKey;                                  /* 只有hsgw存在 */
    VOS_UINT32 ulChargingId;                              /* 只有hsgw存在 */
    
    UCHAR auc3GppPco[PMIPV6_MAX_3GPP_PCO_VALUE_TOTAL_LEN]; /* 只有hsgw存在 */
    UCHAR uc3GppPcoLen;                              /* 只有hsgw存在 */
    VOS_UINT16 usVpn6Index;
}PMIPV6_PDN_MSG_S;

/*******************************************************************************************************/
/********************                          函数声明                           ************************/
/*******************************************************************************************************/
extern VOS_UINT32 PMIPV6_MsgParse(UCHAR *pucMsg, VOS_UINT32 ulMsgLen, UCHAR *pucImsi, UCHAR *pucUserType);
extern VOS_UINT16 PMIPV6_GetSubIdByEncapeType(UCHAR ucSigEncapeType, UCHAR ucUserType);
extern VOS_UINT32 PMIPV6_GetContexSize(VOID);
extern VOS_UINT32 PMIPV6_CreatProcess(PDN_PMIPV6_REQ_S *pstPdnReqMsg); 
extern VOS_UINT32 PMIPV6_CheckMnIdByImsi(UCHAR *pucMnId, A11_IMSI_S stImsi);
extern VOS_UINT32 PMIPV6_GetImsiFromMnId(UCHAR *pucMnId, VOS_UINT32 ulMnIdLen, UCHAR aucImsi[]); 
extern VOS_UINT32 PMIPV6_CheckImsiFromMnIdForUsm(UCHAR aucImsi[]); 
extern VOS_UINT32 PMIPV6_GetHsgwRpContextByImsi(UCHAR **ppucRpContext, A11_IMSI_S *pstImsi);
extern VOS_VOID PMIPV6_GetDataEncapeValidFlg(UCHAR *pucChecksumFlg, UCHAR *pucSequenceFlg);
extern VOS_UINT32 PMIPV6_GetIpInfoByPdnIndex(PMIPV6_IP_INFO_S *pstPmipv6IpInfo, VOS_UINT32 ulPdnIndex);
extern VOS_UINT32 PHGW_SendMsgToLma(UCHAR *pucMsg, VOS_UINT32 ulMsgLen, VOS_UINT32 ulPdnIndex);
extern VOS_UINT32 PMIPV6_GetS2AIntfType(VOID);
extern VOS_UINT32 PMIPV6_GetIndexByMcc(A11_IMSI_S stImsi);
extern VOS_UINT32 PMIPV6_BackupMasterCreUpdPmipv6Proc(VOS_UINT32 ulPmipv6Index, VOS_UINT32 ulOperType, 
                                               UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 PMIPV6_BackupSlaveCreUpdPmipv6Proc(UCHAR *pucCurrent);

extern VOID PMIPV6_FreeResBeforeFreePdnRes(VOS_UINT32 ulMipIndex);
extern VOS_UINT32 Pmipv6_BackupSmoothPmipv6Context(PDN_CONTEXT_S *pstPdnContext);
extern VOS_UINT32 PMIPV6_GetRpIndexByPmipv6Index(VOS_UINT32 ulPmipv6Index, VOS_UINT32 *pulRpIndex);
extern VOS_UINT32 PMIPV6_CheckPfTable(VOS_UINT32 ulPmipv6Index);
extern VOS_UINT32 PMIPV6_ResCheckByPmipv6Index(VOS_UINT32 ulPmipv6Index);
extern VOS_VOID PMIPV6_InitPerfCounterAddr(VOS_VOID);


#endif
