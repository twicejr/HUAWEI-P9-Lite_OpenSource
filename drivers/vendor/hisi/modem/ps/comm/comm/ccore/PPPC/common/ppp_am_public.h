#ifndef __PPP_AM_PUBLIC_H__
#define __PPP_AM_PUBLIC_H__

/************************* 报文类型 **********************************/
#define PPP_MP 0x003d
#define PPP_IP 0x0021
#define PPP_IP6 0x0057
#define PPP_VSNP 0x005b
#define PPP_OSI 0x0023
#define PPP_IPX 0x002b

/*地址分配*/
#define PPP_LOCAL_ALLOTADDR 1
#define PPP_RADIUS_ALLOTADDR 2
#define PPP_RADIUSPRI_ALLOTADDR 5

#define PPP_EAP_USER_NAME_256BYTE  256
#define VSNCP_RESERVED_LEN 500

/* EAP PACKET CODE */
#define EAP_PACKET_CODE_REQUEST        1
#define EAP_PACKET_CODE_RESPONSE       2
#define EAP_PACKET_CODE_SUCCESS        3
#define EAP_PACKET_CODE_FAILURE        4

/* PPP */
#define A11_SUBNET_LENGTH 37 /* SUBNET */
#define IMSI_S A11_IMSI_S

#define PPP_A11_ALARM_IMSI_LENGTH   15
#define PPP_A11_ALARM_BSID_LENGTH   12
#define PPP_A11_ALARM_BSID_BCD_LEN  6
#define PPP_A11_ALARM_SUBNET_LENGTH 74
#define PPP_A11_ALARM_MAX_NUM        500
#define IPV6_ADDR_LEN 8         /*IPV6地址长度(ushort类型)*/

#define Authentication_Fail 0x83
#define PPP_Negotiation_Fail 0xD2
#define RM_MAX_RADIUSGROUP_NUM 1000
#define AAA_DEFAULT_DOMAIN_INDEX 0xFFFF

#define M_DIAMAUTH_DYNAAA_AAA     1
#define M_DIAMAUTH_STATIC_AAA     0
/* 第一次发送 DIAMETER 消息标志 */
#define DIAM_AUTH_FIRST_SEND      1
#define DIAM_AUTH_NO_FIRST_SEND   0


/*  与PPP间的消息类型  */
#define PPP_DIAM_AAA_CREAT_REQ       1    /* 鉴权请求 */
#define DIAM_AAA_PPP_CREAT_RSP       2    /* 鉴权响应 */
#define PPP_DIAM_AAA_RELEASE_REQ     3    /* release请求 */

/*定义具体的ppp用户类型*/
#define PPP_USERTYPE_SIP 0
#define PPP_USERTYPE_MIP 1
#define PPP_USERTYPE_MIPAGENT 2
#define PPP_USERTYPE_NULL 3
#define VSNCP_OPTION_ATTACHTYPE_INIT     1
#define VSNCP_OPTION_ATTACHTYPE_HANDOFF  3
#define VSNCP_OPTION_ATTACHTYPE_LEN 3

typedef enum
{
    A11_SEND_ECHO,
    A11_STOP_ECHO
}A11_ECHO_E;

/* BEGIN: Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */
typedef enum
{
    PPP_NEGO_LIST_NODE_LCP_START = 1,
    PPP_NEGO_LIST_NODE_VSNCP_RENEGO_START = 2,
    PPP_NEGO_LIST_NODE_MS_RELEASE_START = 3,
    PPP_NEGO_LIST_NODE_RP_RELEASE_START = 4,
    PPP_NEGO_LIST_NODE_TYPE_BUTT
} PPP_NEGO_LIST_NODE_TYPE_E;

/* END:   Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */


/*VSNCP Configure Reject错误码*/
typedef enum
{
    PPP_VSNCP_GENERAL_ERROR = 0,
    PPP_VSNCP_UNAUTHORIZEDN_APN,
    PPP_VSNCP_EXCEED_PDN_LIMIT,
    PPP_VSNCP_NO_PGW,
    PPP_VSNCP_PGW_UNREACHABLE,
    PPP_VSNCP_PGW_REJECT = 5,
    PPP_VSNCP_INSUFFICIENT_PARAS,
    PPP_VSNCP_RES_UNAVAILABLE,
    PPP_VSNCP_ADMIN_PROHIBITED,
    PPP_VSNCP_PDN_INUSE,
    PPP_VSNCP_SUBSCRIPTION_LIMIT = 10,
    PPP_VSNCP_APN_EXIST,
    /* 下面的code值是私有的 */
    PPP_VSNCP_DECODE_OK,
}PPP_VSNCP_REJECT_ERRCODE_E;


/* 鉴权响应 */
typedef struct tagDIAMAuthRspMsg
{
    VOS_UINT32 ulMsgCode;                                                    /* 消息码 */
    VOS_UINT32 ulSDBIndex;                                                   /* context索引 即SDB索引 */
    VOS_UINT32 ulQosProfileID;                                               /* qos profile id */
    VOS_UINT32 ulSessionTimeout;                                             /* session timeout */
    VOS_UINT32 ulAccountInterval;                                            /* Accounting-Interim-Interval */
    VOS_UINT32 ulDefaultAPNId;                                               /* default APN id */
    VOS_UINT32 ulULMaxBw;                                                    /* 上行最大请求带宽 */
    VOS_UINT32 ulDLMaxBw;                                                    /* 下行最大请求带宽 */
    VOS_UINT32 ulResultCode;                                                 /* result code */
    VOS_UINT32 ulEAPLen;                                                     /* EAP LEN */
    DIAM_AUTH_APN_INFO_S stApnInfo[DIAM_AUTH_APN_INFO_MAX_NUMBER];      /* APN CONFIGURATION */
    VOS_UINT16 usPeerId;                                                    /* PEER ID */
    VOS_UINT16 us3GPPCC;                               /* 计费属性 */
    UCHAR aucUsername[DIAM_AUTH_USERNAME_MAX_LEN + 1];                       /* 用户名 */
    UCHAR aucMnId[DIAM_AUTH_MNID_MAX_LENGTH + 1];                           /* Mobile-Node-Identifier */
    UCHAR ucUsernameLen;                                                /* 用户名长度 */
    UCHAR ucResult;                                                     /* 鉴权结果 */
    UCHAR ucApnInfoNum;                                                 /* APN INFO个数 */
    UCHAR ucStateLen;                                                   /* APN INFO个数 */
    UCHAR aucState[DIAM_AUTH_STATE_LEN];                                    /* state */
    UCHAR aucMSK[DIAM_AUTH_MSK_LEN];                                    /* MSK */
    UCHAR aucMdn[MDN_MAX_LEN+1];                                        /* 电信MDN需求 */
    UCHAR aucEAP[4];                                                    /* EAP */
}DIAM_AUTHRSP_S;

/* diam鉴权请求 */
typedef struct tagPppDiamAuthMsg
{
    VOS_UINT32 ulMsgType;            /* 消息类型 */
    VOS_UINT32 ulRpIndex;            /* SDB索引 */
    VOS_UINT32 ulNowUTCInSec;
    VOS_UINT32 ulReleaseCode;
    VOS_UINT16 usPeerID;            /* diameter aaa server ID */
    VOS_UINT16 usEAPlen;            /* EAP len */
    VOS_UINT16 usTokenId;           /* 上下文的TOKEN ID */
    VOS_UINT16 usDynLocalPeerId;    /* 动态aaa，但是属于local配置 */
    UCHAR ucAAAType;
    UCHAR ucRsv;
    UCHAR ucStateLen;
    UCHAR ucFirstSendFlag;
    A11_IMSI_S stIMSI;
    UCHAR aucUserName[DIAM_AUTH_USERNAME_MAX_LEN + 1];
    UCHAR aucState[DIAM_AUTH_STATE_LEN];                                    /* state */
    UCHAR aucAAAHost[DIAM_AUTH_DRA_HOST_MAX_LENGTH + 1];        /* origin host */
    UCHAR aucAAARealm[DIAM_AUTH_REALM_OR_HOST_MAX_LENGTH + 1];       /* origin realm */
    UCHAR aucEAP[4];
}PPP_DIAM_AUTH_MSG_S;



enum enumPPPFailedFlag
{
    PPPNEGOFAIL = 0,
    PPPLOWEDOWN,
    PPPUSERDOWN,
    PPPL2TPDOWN,
    LAPRECYCLE,
    /* Added start by c00127007 at 2010-03-30 PDSNV9R7C05 for 整改优化 */
    PPPA11DOWN,
    PPPFADOWN,
    PPPPCRFCFAIL, /*pcrfc处理失败*/
    PPPLICESEERROR,
    PPPA11DOWNNOLCPTER, /*不需要发送lcp termination*/
    /* Added end by c00127007 at 2010-03-30 PDSNV9R7C05 for 整改优化 */
};


/* PPP_A11_Alarm配置结构 */
typedef struct tagAlarmLink
{
    VOS_UINT32 ulPDSNIP;     /* PDSN IP */
    VOS_UINT32 ulPcfIP;      /* PCF IP */
    UCHAR ucIMSI[PPP_A11_ALARM_IMSI_LENGTH + 1];   /* IMSI */
    VOS_UINT32 ulTimestamp;  /* Timestamp */
    UCHAR ucErrorCode;  /* Error Code */
    UCHAR ucBSID[PPP_A11_ALARM_BSID_LENGTH + 1];   /* BSID */
    UCHAR aucSubnet[PPP_A11_ALARM_SUBNET_LENGTH + 1]; /* SUBNET */
    #ifdef __LINUX_PLATFORM__
    UCHAR ucReserve456567[3];
    #endif
}VOS_PACKED PPPA11_AlarmLink_S;


/* up时的参数 */
typedef struct tagPppLUpPara    /* 底层UP带的参数 */
{
    IMSI_S stIMSI;              /* IMSI */
    VOS_UINT32  ulPcfIP;
    VOS_UINT16 usPcfIndex;
    VOS_UINT16 usTokenId;
    UCHAR  ucServiceOpt;
    UCHAR  beHRPDMode:1,
           bReserv:7;
    UCHAR  ucBSID[6];
    UCHAR  aucSubnet[A11_SUBNET_LENGTH + 1];      /*Subnet For HRPD d7*/
} PPP_LUPPARA_S;



/* down时的参数 */
typedef struct tagPppLDownPara    /* 底层UP带的参数 */
{
    VOS_UINT32 ulLcpSendFlag;
} PppLDownPara;

/* AAA和PPPC的消息 */
typedef struct tagPppcAaaAuthReq
{
    MSG_HDR_S stMsgHdr;             /* NE80头 */
    VOS_UINT32     ulMsgType;            /* 消息类型 */
    VOS_UINT32     ulSDBIndex;            /* SDB索引 */

    VOS_UINT16 usCDBIndex;                /* GGSN:APNIndex PDSN:DomainIndex */
    UCHAR  ucPktID;                 /* 用户认证请求包ID */
    UCHAR  ucUsernameLen;           /* 用户名长度 */

    UCHAR ucUsername[A11_MAX_NAI_LENGTH + 1]; /* 用户名 */
    UCHAR ucPwd[18];                /* 密码 */
    UCHAR ucPwdLen;                    /* 密码长度 */
    UCHAR ucChapResponseLen;        /* Chap-Response长度 */

    UCHAR ucChapResponse[256];        /* Chap-Response */
    UCHAR ucChapChallenge[256];        /* Chap-Challenge */

    UCHAR  ucChapChallengeLen;       /* Response长度 */
    UCHAR  ucRes;
    VOS_UINT16 usVPNID;                 /* VPN ID */

    VOS_UINT32  ulIp;                       /* IP地址 */
    UCHAR ucIMSI[8];                /* IMSI */
    VOS_UINT32  ulIpMask;                   /* IP地址子网掩码 */
    VOS_UINT32  ulG4EvtTime;               /* Event Time */
    UCHAR  aucC2CorLID[8];           /* Correlation ID */
    VOS_UINT32  ulCurVolume;         /* 流量值 */
    VOS_UINT32  ulCurDuration;       /* 时间值 */
    VOS_UINT32  ulVUATS;                /* 费率切换点之后的用户流量 */
    VOS_UINT16 usGroupIndex;                    /* test 消息专用 */
    UCHAR  ucPreparedFlag;   /* 使用A11_PPC_TYPE_E定义 */
    UCHAR  ucUpdateReason;  /* 更新原因 */
    UCHAR  ucRenegoFlag;    /* 重协商标记 */
    UCHAR  ucPPPFlag;       /*携带标志位，值为 1，AUTH判断是PPP或PPC消息*/
    UCHAR  ucReserved[6];

}PPPC_AAA_AUTH_REQ_S ;

typedef enum
{
    LCP_INFOR = 1,   /* LCP 信息 */

    IPCP_INFOR,      /* IPCP 信息 */

    SCP_INFOR,

    IPCPV6_INFOR,     /* IPV6 IPCP 信息 */

    VSNCP_INFOR,      /* VSNCP 信息 */

    MAGICNUM_INVALID, /* magic number 无效标志 */
} PPPC_USR_INFOR_FLAG_E;    /* PPPC发送用户信息时使用的标志 */

#define PPP_CPU_2_ON_SPU 2
#define PPP_SET_IPTECH(pppinfo, iptech) \
        if (PPP_USERTYPE_NULL == pppinfo->bIPTech ) \
        {\
            pppinfo->bIPTech = (iptech);\
        }



#define PPP_SELF_SGID      g_stPppCompInfo.ullSelfSgId

#define PPP_CPU_OFFLINE  0  /* CPU不在位 */
#define PPP_CPU_ONLINE   1  /* CPU在位 */


VOS_UINT32 PPP_Shell_OutPut(VOS_UINT32 ulRpindex, PMBUF_S *pstPMBuffNew, VOS_UINT16 usProtocol);
VOS_UINT32 PPP_StartIPV4CP(VOS_UINT32 ulRpIdx, VOS_UINT32 ulIpAddr, VOS_UINT32 ulPriDns, VOS_UINT32 ulSecDns);
VOS_UINT32 PPP_StartIPV6CP(VOS_UINT32 ulRpIdx, UCHAR* szIpV6Addr, UCHAR* szPriDns, UCHAR* szSecDns);
VOS_UINT32 PPP_StopIPV4CP(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_StopIPV6CP(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_ReleaseIPV4CP(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_ReleaseIPV6CP(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_SendFakeIPV4CPReqMsg(VOS_UINT32 ulRpIndex);
VOS_UINT32 PPP_SendFakeIPV6CPReqMsg(VOS_UINT32 ulRpIndex);

VOS_UINT32 PPP_ipv6_addr_check(VOS_UINT16 *pstIpv6addr);
VOS_UINT32 PPP_GetNowUTCInSec(VOS_UINT32 ulRpIndex);
extern VOS_UINT32 PPP_SubPDNNotifyVSNCPStop(VOS_UINT32 ulRpIdx, UCHAR ucPDNId, VOS_UINT32 ulReleaseCode);
extern VOS_UINT32 PPP_SubPDNNotifyVSNCPStart(VOS_UINT32 ulRpIdx, UCHAR ucPDNId, UCHAR *pucPacket);
extern VOS_UINT32 PPP_SubPDNNotifyVSNCPRenegoStart(VOS_UINT32 ulRpIdx, UCHAR ucPDNId);
extern VOS_UINT32 PPP_GetRetryInterval(VOID);
extern VOS_UINT32 PPP_Shell_L2tpProc(VOS_UINT32 ulRpIdx, L2TP_PPPPARA_S *pstL2tpPara);
extern VOS_UINT32 PPP_Shell_NotifyL2tpDown(PDN_CONTEXT_S *pstPdnContext, UCHAR ucMsgCode);
extern VOID PPP_PDNSendVSNCPReject(VOS_UINT32 ulRPIndex, UCHAR *pucMsg, UCHAR ucErrCode);
extern VOS_UINT32 PPP_GetIpV6Capbility(VOID);
extern VOID PPP_PDNClearVSNCP(PDN_CONTEXT_S *pstPDNContext);
extern VOS_UINT32 A11_PPPC_EchoSet(A11_ECHO_E ucFlag, VOS_UINT32 ulRPIndex);
extern VOS_UINT32 AM_PPP_SendMsgToLap2(USM_LAP2_MSG_S* pstMsg);
extern VOS_UINT32 InsertAlarmLink(PPPA11_AlarmLink_S *pstAlarmLink);
extern VOS_UINT32 PPP_SendRtMsg(VOS_UINT64 ullSrtCsi,VOS_UINT64 ullDstCsi, VOS_UINT32 ulMsgType, VOS_UINT32 ulMsgCode, UCHAR *pucMsg, VOS_UINT32 ulMsgLen );
extern VOS_UINT32 PPP_GetPeerID(VOS_UINT32 ulRpIndex, VOS_UINT16 *pusPeerId);
extern VOS_UINT32 PPP_GetAAAType(VOS_UINT32 ulRpIndex, UCHAR *pucAAAType);
extern VOID PPP_SetSendSTRFlag(VOS_UINT32 ulRpIndex, VOS_UINT32 ulAuthSessionState);
extern VOS_UINT32 PPP_GetIpAddrByBufReq( VOS_UINT32 ulRpIndex, VOS_UINT32 *pulReqIpAddr );
extern VOS_UINT32 PPP_BackupMasterCreUpdPppProc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulOperType,
                                                  UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 PPP_BackupSlaveCreUpdPppProc(UCHAR *pucCurrent);

extern VOS_UINT64 PPP_GetLocalL2tpCsi(VOID);
extern VOID PPP_BackupRestoreVsncp(PDN_CONTEXT_S *pstPdnContext, UCHAR ucPDNID, UCHAR ucPktId);
extern VOID PPP_BackupSlaveDelResource(VOS_UINT32 ulRpIndex);
extern VOS_UINT32 PPP_BackupSmoothPppInfo(SDB_PDSN_RP_CONTEXT_S *pstRpContext);

VOID PPP_BackupSmoothSubBoardDown(VOID);


extern VOID PPP_IpcpTimeOutProcForPdn(VOS_UINT32 ulRpIndex);
extern VOID PPP_UpdatePcfInfo(VOS_UINT32 ulRpIndex, VOS_UINT32 ulPcfIp, VOS_UINT16 usPcfIndex);




extern VOS_UINT32 PPP_USMStartVsncp(UCHAR *pucVsncpMsg, VOS_UINT32 ulRpIndex);
extern VOS_UINT32 PPP_RPNodeDelete(VOS_UINT32 ulRPIndex);
extern VOID PPP_RPNegoListProc(VOID* pPara);
extern VOS_UINT32 PPP_RPNodeAdd(VOS_UINT32 ulRpIndex, VOS_UINT32 ulReleaseCode, UCHAR ucNodeType);
extern VOS_UINT32 PPP_A11_GetSubBoardStat( UCHAR ucDmpuId);

#endif


