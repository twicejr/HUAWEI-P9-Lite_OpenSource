#ifndef __LI_AM_PUBLIC_H__
#define __LI_AM_PUBLIC_H__

/* 请注意该头文件一定要不能包含其他宏定义和结构体 */

#define AUTH_PAP_PPP 1
#define AUTH_CHAP_PPP 0

/*需要根据LI_TARGET_TYPE_E 来确定*/
#define  LI_USM_TARGET_TYPE_IMSI  1 /* 同LI_TARGET_TYPE_IMSI */
#define  LI_USM_TARGET_TYPE_ESN   3 /* 同LI_TARGET_TYPE_ESN */
#define  LI_USM_TARGET_TYPE_MDN   4 /* 同LI_TARGET_TYPE_MDN */
#define  LI_USM_TARGET_TYPE_MEID  5 /* 同LI_TARGET_TYPE_MEID */


typedef enum
{
    PDSN_SUCCESS =  0,
    PDSN_FAIL    
}A11_LI_PDSN_FLAG;

typedef enum
{
    PDSN_OPTION_SETUP = 0,       /* 分组会话建立事件*/
    PDSN_OPTION_RELEASE,         /* 分组会话释放事件 */
    PDSN_OPTION_HANDOFF,         /* 分组会话切换事件 */
    PDSN_OPTION_START_SESSION,   /* 开始监听分组会话事件 */
    PDSN_PACKET_FILTER           /* 分组数据过滤事件 */
} A11_LI_PDSN_OPTION_E;

typedef enum
{
    E_LI_A11_CHECK_OK    = 0,           /* Registration Accepted */
    E_LI_A11_REASON_UNSPECIFIED = 0x80, /* reason unspecified */
    E_LI_A11_ADMIN_PROHIBTED = 0x81,    /* administratively prohibited */
    E_LI_A11_INSUF_RES = 0x82,          /* insufficient resources */
    E_LI_A11_AUTHEN_FAILED = 0x83,      /*mobile node failed authentication */
    E_LI_A11_ID_MISMATCH = 0x85,        /* identification mismatch */
    E_LI_A11_POOR_FORM = 0x86,          /* poorly formed request */
    E_LI_A11_UNKNOWN_PDSN_IP = 0x88,    /* unknown PDSN address */
    E_LI_A11_TUNNELS_NOT_SET =0x89,
    E_LI_A11_T_BIT_NOT_SET = 0x8A,      /* reverse tunnel is mandatory and 'T' bit not set */
    E_LI_A11_UNSUPPORT_VEND_ID = 0x8D,  /* unsupported vendor ID */
    E_LI_A11_UNKNOWN_MSG_TYPE = 0X8E,
    E_LI_A11_RESEND_MSG = 0x8F,
    E_LI_A11_UNSUPPORT_SERVICEOPT_HRPD = 0X90,/* add by dongenjie for HRPD support */
    E_LI_RELEASE_REASON_UNSPECIFIED = 0xC1,
    E_LI_RELEASE_PPP_TIMEOUT  = 0xC2,
    E_LI_RELEASE_REGISTRATION_TIMEOUT = 0xC3,
    E_LI_RELEASE_PDSN_ERR = 0xC4,
    E_LI_RELEASE_inter_PCFHANDOFF  = 0xC5,
    E_LI_RELEASE_inter_PDSNHANDOFF = 0xC6,
    E_LI_RELEASE_PDSN_OM_INTERVENTION= 0xC7,
    E_LI_RELEASE_ACCT_ERR = 0xC8,
    E_LI_PPP_Negotiation_Fail = 0xD2,
    E_LI_A11_CHECK_LI_USED = 0xff    /* LI模块使用 */
} A11_LI_FAILORRELEASE_CAUSE_E;


typedef struct tagAU_INFO_S
{
    UCHAR    ucSubPasswordLen;
    UCHAR    szSubPassword[20];
    UCHAR    ucAuType;
    UCHAR    ucChapChallengeLen;
    UCHAR    szChapChallenge[16];

} AuInfo_S;

#define IMSIBCDLEN   8
#define ESNBCDLEN    4
#define MEIDBCDLEN   7
#define MDNBCDLEN    8
#define NAILEN      65

typedef struct 
{
    VOS_UINT16 usIriTargetMap;
    VOS_UINT16 usIdpTargetMap;
    UCHAR  ucLiFlag;
    UCHAR  ucRev;
}LI_USM_FLAG_S;


typedef struct tagLI_X2PACKET_FILTER_INFO
{
    struct  tagLI_X2PACKET_FILTER_INFO *next;
    VOS_UINT32 length;
    UCHAR value[100];
} LI_X2PACKET_FILTER_INFO;


typedef struct 
{        
    VOS_UINT32 ulPdpIndex;       /* RP 上下文索引 */
    VOS_UINT32 ulTeidc;           
    VOS_UINT32 ulPcfKey;         /* PCF标识 */
    VOS_UINT32 ulHaAddr;
    VOS_UINT32 ulCoAAddr;
    VOS_UINT32 ulSetUpTimeInSec;

    UCHAR szIMSI[IMSIBCDLEN];        /* 反序BCD码 */
    UCHAR szESN[ESNBCDLEN];          
    UCHAR szMEID[MEIDBCDLEN]; 
    UCHAR ucMeidLen;
    UCHAR szMDN[MDNBCDLEN];          /* 反序BCD码 */
    
    UCHAR szNAI[NAILEN];
    UCHAR ucNaiLen;
    UCHAR ucImsiLen;
    UCHAR ucEsnLen;
    
    UCHAR aucBsid[6];
    UCHAR ucMdnLen;      
    UCHAR ucBsidFlag;
    
    UCHAR szPdsnIpAddr[16];   /* DPSN地址 */
    UCHAR szSubIpAddr[16];    /* 分组网络为被控目标分配的IP地址 */
    
    UCHAR ucPdsnIpType;       /* 0:IPv4, 1:IPv6 */
    UCHAR ucSubIpType;        /* 0:IPv4, 1:IPv6 */
    UCHAR ucSIPorMIP;         /* 指出被控目标使用的是简单IP还是移动IP。SIP由PDSN或AAA分配，MIP由HA分配。 */
    UCHAR ucGotOldIpFlag;     /* 切换时是否还能获取到原PCF IP 0:获取不到,1:获取到*/

    UCHAR ucAccPcfIpType;     /* 0:IPv4, 1:IPv6 */
    UCHAR ucCurPcfIPType;
    UCHAR uchandOffType;      /* handoff 类型 */
    UCHAR ucOtherNetIdLen;

    UCHAR szAccPcfIpAddr[16]; /* 切换时表示原PCF IP */
    UCHAR szCurPcfIPAdd[16];  /* 切换时表示切换后PCF IP */
    UCHAR szOtherNetId[20];   /* handoff 场景 */
    
    UCHAR szCanId[10];        /* 当前接入网络标识 */
    UCHAR ucCanIdLen;
    UCHAR ucPanIdLen;
    
    UCHAR szPanId[10];        /* 切换前网络标识 */
    UCHAR ucSuccessFlag;
    UCHAR ucPacketFilterFlag; /*packerfilter 携带标记*/

    UCHAR ucAuType;           /* 被控目标接入分组网络时，在AAA中进行鉴权的方式 */
    UCHAR ucAuFlag;           /* 1:ucAuType有效， 0:ucAuType无效 */
    UCHAR ucSubPasswordLen;   
    UCHAR ucChapChallengeLen;
    
    UCHAR szSubPassword[20];  /* 被控目标的账户密码 */
    UCHAR szChapChallenge[16];/* 若采用CHAP认证时用户被给予的一个16比特的随机数 */

    VOS_UINT16 usFailureCause;    /* 激活或更新失败原因值 */
    VOS_UINT16 usReleaseCause;    /* 去活原因值 */

    VOS_UINT16 usIriTargetMap;    /*用于填充到上下文中的bitmap 值*/
    VOS_UINT16 usIdpTargetMap;    /*用于填充到上下文中的bitmap 值*/
    
    UCHAR ucPortType;         /*PPP用户还是IP 用户*/
    UCHAR ucSduVcpu;
    
    UCHAR ucRev[2];

    LI_X2PACKET_FILTER_INFO stX2PacketFilterInfo;

}LI_CDMA2000_PDPINFO_S;

#define PORTTYPE_PPP  2
#define PORTTYPE_IPV4 0


/*用户激活失败，且没有分配上下文的场景*/
extern VOID  LI_PdsnSetInfoWithoutContext(LI_CDMA2000_PDPINFO_S *pstPdpInfo, A11_LI_PDSN_OPTION_E enEvent, UCHAR ucCause);
/*上下文已经分配的场景*/
extern VOID  LI_PdsnSetInfo(LI_CDMA2000_PDPINFO_S *pstPdpInfo, A11_LI_PDSN_OPTION_E enEvent, A11_LI_PDSN_FLAG ucSuccessFlag);
extern VOID  USM_SetLiFlagToRpcontext(VOS_UINT32 ulRpindex, LI_USM_FLAG_S *pstLiUsmFlag);
extern VOS_UINT32 USM_LIGetContextByTargetID(UCHAR ucTargetIdType, UCHAR *pucTargetId, LI_CDMA2000_PDPINFO_S *pstLiPdpinfo);
extern VOS_UINT32 USM_LIGetContextByRpintexforBatchBackup(VOS_UINT32 ulRpIndex, LI_CDMA2000_PDPINFO_S *pstLiPdpinfo);
extern VOS_UINT32 LI_PdsnIsInterceptBan(LI_CDMA2000_PDPINFO_S *pstPdpInfo);
extern VOS_UINT32 USM_LIRelContextByTargetID(UCHAR ucTargetIdType, UCHAR * pucTargetId);

#endif /* __LI_AM_PUBLIC_H__ */

