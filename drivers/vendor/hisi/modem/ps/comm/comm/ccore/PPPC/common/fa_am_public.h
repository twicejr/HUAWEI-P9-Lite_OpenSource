/*************************************************************************************
*
*                       fa_pub.h
*
*  项目代码：           WCDMA PDSN9660 V900R008
*  创建日期：           2011/10/24
*  作者：               wangxiaoyu 167726
*  修改历史列表：
*  参考文档：       
*  功能：               FA对外公开宏定义、全局变量、接口函数                
*  其他：                  
*
*-----------------------------------------------------------------------------------
*
*  Copyright  Beijing Institute HuaWei Tech, Inc.
*                     ALL RIGHTS RESERVED
*
*************************************************************************************/
#ifndef __FA_AM_PUBLIC_H__
#define __FA_AM_PUBLIC_H__

#ifdef      __cplusplus
}
#endif 

/*******************************************************************************************************/
/********************                          宏定义                           ************************/
/*******************************************************************************************************/
/*FA事件位*/
#define FA_SD_EVENT             0x01
#define FA_DPE_EVENT            0x02
#define FA_TIMER_EVENT          0x04
#define FA_PDN_EVENT            0x08
#define FA_AUTH_EVENT           0x20


/*长度定义*/
#define FA_AAA_CHALLENGE_LEN    253
#define FA_SHARED_KEY_MAX_LEN   128
#define FA_AAA_CHAP_PWD_LEN     255

#define FA_SKEY_MAX_LEN         18
#define FA_MIP_IMSI_LEN         15  /* IMSI最大长度 */
#define FA_CFG_KEY_LEN          16
#define PRE_SHARED_KEY_MAX_LEN 128
#define FA_CHALLENGE_LEN 16

/*MIP 消息码*/
#define MIP_REGISTRATION_REQUEST  0x01    /* MIP-Registration Request 消息 */
#define MIP_REGISTRATION_REPLY    0x03    /* MIP-Registration Reply   消息 */
#define MIP_REVOCATION_REQUEST    0x07    /* MIP-Revocation 消息 */
#define MIP_AGENT_SOLICITATION    0x0a    /* MIP-Agent Solicitation 消息 */
#define MIP_REVOCATION_ACK        0x0F    /* MIP-Revocation Ack消息 */
#define MIP_ADVERTISEMENT         0x10    /* MIP 代理广播消息 */



#define FA_MIPAGENT_GRP_MAXNUM 1000    /*MipAgent 可使用的最大组数*/
#define   FA_PDN_PMIP_RESPONSE   0

#define FA_AAA_CHALLENGE_LEN    253
#define FA_AAA_CHAP_PWD_LEN     255
#define PRE_SHARED_KEY_MAX_LEN 128

/*性能统计加操作*/
#define M_FA_MIPPER_ADD(x)  if ( VOS_NULL != (x) ) {(VOS_VOID)PerfSetFamPerfCounterByAddress((x), A11_PERF_OPERATOR_PLUS, 1); }

/*性能统计减操作*/
#define M_FA_MIPPER_DEC(x)  if ( VOS_NULL != (x) ) {(VOS_VOID)PerfSetFamPerfCounterByAddress((x), A11_PERF_OPERATOR_SUB, 1);  }

typedef enum
{
    FA_ENCAP_TYPE_IPINIP = 1,
    FA_ENCAP_TYPE_MINI,
    FA_ENCAP_TYPE_GRE,
} FA_ENCAP_TYPE_E;

typedef enum tagFA_MIP_MODE_E
{
    E_PMIP_HUAWEI = 0,   /* 按照华为私有属性，默认值 */
    E_PMIP_CNTEL,        /* 按照中国电信规范*/
    E_PMIP_BUTT
}VOS_PACKED FA_MIP_MODE_E;

/*PDN通知FA 的消息码*/
typedef enum
{
    FA_MSG_CODE_PMIP_CREATE,       /* PDN通知FA处理PMIP用户激活消息 */
    FA_MSG_CODE_PMIP_UPDATE,       /* PDN通知FA处理PMIP用户更新消息 */
    FA_MSG_CODE_PMIP_DEACTIVE,       /* PDN通知FA处理PMIP用户退网消息 */

    FA_MSG_CODE_CMIP_CREATE,       /* PDN通知FA处理CMIP用户激活消息 */
    FA_MSG_CODE_CMIP_DEACTIVE,       /* PDN通知FA处理CMIP用户退网消息 */

}FA_MSG_CODE_E;

/*FA发给PDN的消息码*/
typedef enum
{
    FA_PDN_MIP_SUCCESS = 0,    /*激活成功*/
    FA_PDN_MIP_FAIL,           /*激活失败或者去活*/ 
} FA_PDN_MIP_MSG_CODE_E;


/* PDN 模块发给FA的PMIP 用户激活请求时的消息结构*/
typedef struct tagFA_PDN_MIPAGENT_REQ_S
{
    VOS_UINT32   ulPdnIndex;         /* PDN上下文索引*/
    VOS_UINT32   ulHaAddr;           /*HA Ipaddress*/

    VOS_UINT32   ulHomeAddr;         /*Home address*/
    VOS_UINT32   ulSpi;              /*MN-HA SPI*/
    VOS_UINT32   ulPiSubIndex;
    VOS_UINT32   ulCofAddr;       /*COF address*/

    VOS_UINT32   ulUpdateMask;
    VOS_UINT16  usDomainIndex;     /*域索引*/
    VOS_UINT16  usLifetime;         /* MIP 链路的lifetime */
    
    VOS_UINT16  usVpnID;
    UCHAR   aucSKey[FA_SKEY_MAX_LEN];  /*MN-HA Key*/

    UCHAR   aucNai[A11_MAX_NAI_LENGTH + 1];

    VOS_UINT16  usReservr43667;
    UCHAR   ucStcValue;         /* AAA返回的stc */
    UCHAR   ucKeyLen;           /*MN-HA Key长度*/
} FA_PDN_MIPAGENT_REQ_S;
 
/*FA模块向PDN模块返回CMIP +PMIP 激活结果的消息接口*/
typedef struct tagFA_PDN_MIPAGENT_RSP_S
{
    VOS_UINT32     ulPdnIndex;      /* PDN上下文索引*/
    UCHAR     ucMsgCode;       /* 返回码, FA_PDN_MIP_MSG_CODE_E */
    UCHAR     ucReason;        /* :0 表示fa回复的响应消息，非0 表示退网原因值*/    
    UCHAR     ucEncapType;     /* 用户数据封装类型: 1 - IPinIp, 2 - Mini, 3 - GRE*/ 
    UCHAR     ucGRESwitchFlag:1;      /*GRESwitchFlag*/
    UCHAR     ucRevTunnelFlag: 1;    /*support reverse tunnel*/
    UCHAR     ucMsSendMethodFlag: 1;    /*MS send method on reverse tunnel*/
    UCHAR     ucReserd:5;
    VOS_UINT32     ulHomeAddr;      /* Home address*/
    VOS_UINT32     ulPriDnsIp;      /* 主DNS地址 */
    VOS_UINT32     ulSecDnsIp;      /* 从DNS地址 */
    VOS_UINT32     ulHaIp;          /* ha ip */    
    VOS_UINT32     ulFaIp;          /* fa ip */    
    VOS_UINT32     ulMipKey;
    VOS_UINT16    usDomainIndex;
    UCHAR     ucResv[2];     
} FA_PDN_MIPAGENT_RSP_S;

/* pdn 消息结构通知FA CMIP 用户入网/ 退网消息结构体 */
typedef struct tagFA_PDN_CMIP_MSG_S
{
    VOS_UINT32     ulPdnIndex;        /* PDN上下文索引*/
    UCHAR     ucReserv[2];
    VOS_UINT16    usTdormant;        /* PPP协商的Lifetime */
} FA_PDN_CMIP_MSG_S;

/*FA发送给AUTH 认证的消息结构*/
typedef struct tagFA_AAA_AUTHREQ_S
{
    VOS_UINT32     ulMsgType;        /* 消息类型 */
    VOS_UINT32     ulVistLstIndex;   /* Vistor List table Index*/
    VOS_UINT32     ulSdbIndex;    
    VOS_UINT32     ulPDNIndex;
    VOS_UINT32     ulCorrelationID;  /* correlation id*/
    VOS_UINT32     ulHaAddr;         /* HA address*/
    VOS_UINT32     ulFrameIPAddr;    /* Home address*/
    VOS_UINT16    usCDBIndex;       /* domain index*/
    UCHAR     ucPktID;          /* 用户认证请求包ID */
    UCHAR     ucReserv;         /* 四字节对齐*/
    
    UCHAR     ucUsernameLen;                        /* 用户名长度 */
    UCHAR     ucUsername[A11_MAX_NAI_LENGTH];       /* 用户名 */

    UCHAR     ucChapPwdLen;                         /* 密码长度 */
    UCHAR     ucChapPwd[FA_AAA_CHAP_PWD_LEN];       /* 密码 */

    UCHAR     ucChapChallengeLen;                   /* Response长度 */
    UCHAR     ucChapChallenge[FA_AAA_CHALLENGE_LEN];/* Chap-Challenge */
    UCHAR     ucResv[2];

    UCHAR     ucIMSI[8];                 /* IMSI */
} FA_AAA_AUTHREQ_S;


typedef struct tagFaAaaAuthRepMsg
{
    VOS_UINT32     ulMsgType;
    VOS_UINT32     ulSdbIndex;
    VOS_UINT32     ulVistLstIndex;
    VOS_UINT32     CorrelationID;
    VOS_UINT32     ulHaAddr;
    VOS_UINT32     ulFrameIPAddr;
    VOS_UINT32     SecurityLevel;
    VOS_UINT32     ReverseTunnel;
    VOS_UINT32     KeyID[5]; 

    VOS_UINT32 IpQoS; 
    VOS_UINT32 DiffServicesMarking1;        
    VOS_UINT32 DiffServicesMarking2;    
    VOS_UINT32 DiffServicesMarking3;    
    VOS_UINT32 ulPIMARY_DNS_SERVER;      
    VOS_UINT32 ulSECOND_DNS_SERVER;      
    VOS_UINT32 AlwaysOn;    
    VOS_UINT32 ServicesOptionProfile1;    
    VOS_UINT32 ServicesOptionProfile2;    
    VOS_UINT32 RemoteIPv4Addr;   
    VOS_UINT32 RemoteIPv4AddrMask;    
    VOS_UINT32 RemoteIPv6Addr1;   
    VOS_UINT32 RemoteIPv6Addr2;    
    VOS_UINT32 RemoteIPv6Addr3;    
    VOS_UINT32 RemoteIPv6Addr4;    
    VOS_UINT32 RemoteAddrTblIndex;    
    VOS_UINT32 MnAaaRemove;   
    VOS_UINT32 Deactivetime;    
    VOS_UINT32 ulSessionTime;

    UCHAR PreSharedSecret[PRE_SHARED_KEY_MAX_LEN];    
    
    UCHAR ucSecLen;
    UCHAR ucStcValue;
  
    UCHAR ucResult;    
    UCHAR ucPktID;    

    VOS_UINT32 ulInputPeakRate;  
    VOS_UINT32 ulOutputPeakRate; 
    VOS_UINT32 ulGuarantBitRateUp; 
    VOS_UINT32 ulGuarantBitRateDown; 

    UCHAR ucRateFlag;
    UCHAR uzReserv3[2];    
    UCHAR aucMdn[MDN_MAX_LEN+1];
    UCHAR aucVpnName[RD_HW_VPN_NAME_LEN_MAX + 1];
    
    VOS_UINT32   ulAcctInterimInterval;
    A11_QOS_INFO_S stA11QoS;
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
            bstAllowedDSCPMarkingFlag : 1, /* Allowed Differentiated Services Marking */
            bszUserProfileNameFlag :1;
    
    UCHAR  ucUserClassAAAFlag : 1;
    UCHAR  ucActiveStopIndication:1;     /*Accounting-Stop-triggered-by-Active-Stop-Indication */  
        
    UCHAR  szUserProfileName[PDN_USER_PROFILE_NAME_LENGTH + 1];    /*User Profile名称的字符串*/

} FA_AAA_AUTHREP_S;

typedef struct tagFA_SD_TABLE_MSG_S
{
    UCHAR ucScID;           /*Sc的逻辑VCPU ID*/
    UCHAR aucRes[3];        /**/
    VOS_UINT32 ulIdLow;          /*ID low*/
    UCHAR aucNai[A11_MAX_NAI_LENGTH + 1];       /*NAI*/
} VOS_PACKED FA_SD_TABLE_MSG_S;

/*FA传给NP的下行解隧道索引表*/
typedef struct tagFA_DOWN_TUNNEL_LEAF_S
{
    VOS_UINT32  ulMNaddrHigh;    /* MN's home address*/
    VOS_UINT32  ulMNaddrLow;     /* ipv4时填全F */
    VOS_UINT32  ulHAaddrHigh;    /* HA's address*/
    VOS_UINT32  ulHAaddrLow;     /* ipv4时填全F */
    VOS_UINT32  ulFAaddrHigh;    /* FA's address*/
    VOS_UINT32  ulFAaddrLow;     /* ipv4时填全F */
    VOS_UINT16 usVpnId;         /* VPN ID*/
    UCHAR  ucDpeId;         /* DPE ID*/
    UCHAR  ucResv; 
    VOS_UINT32  ulUserIndex;     /* PDP索引*/
} VOS_PACKED FA_DOWN_TUNNEL_LEAF_S;


/* 下发NP下行解隧道索引表项操作类型 */
typedef enum
{
    FA_ADD_NP_TBL = 0,   /* 增加表项 */

    FA_DEL_NP_TBL,       /* 删除表项 */

    FA_UPD_NP_TBL,       /* 更新表项 */

    FA_ASY_NP_DEL
} FA_NP_TBL_ACT_TYPE_E;  

/* PDN通知fa的操作类型 */
typedef enum
{
    PDN_FA_PMIP_START = 0,      /*start the Pmip service */
    PDN_FA_PMIP_DEACTIVE,       /*deactive the Pmip user*/
    PDN_FA_PMIP_UPDATE,
} PDN_FA_MSG_CODE_E;  

typedef struct tagFA_A11_INFO_S 
{

    VOS_UINT32  ulIndex;         /* 上下文索引 */
    VOS_UINT32  ulCofAddr;       /*COF address*/
    VOS_UINT32  ulHaAddr;        /*Home Agent address*/
    VOS_UINT32  ulPriDnsIp;
    VOS_UINT32  ulSecDnsIp;
    VOS_UINT16 usLifetime;      /* MIP Lifetime*/
    UCHAR  ucUserType;      /* 用户接入类型: 0 - CMIPv4, 1 - PMIPv4, 2 - CMIPv6, 3 - PMIPv6*/
} FA_A11_INFO_S;

/* 性能统计结构 */
typedef struct tagFA_PERFSTATISTIC_S
{
    VOS_SIZE_T pulRcvRrqNum; /* FA收到注册请求总数 */
    VOS_SIZE_T pulRelayRrq;  /* FA转发给HA的注册请求总数*/
    VOS_SIZE_T pulDenyUnknow;/* 因为未明原因，外地代理而拒绝注册请求的总数 */
    VOS_SIZE_T pulDenyAdmin;/* 因为管理上的禁止（代码：65）外地代理而拒绝注册请求的总数*/
    VOS_SIZE_T pulDenyResource;/* 因资源不足(Code 66)，外地代理而拒绝注册请求的总数 */
    VOS_SIZE_T pulDenyAaaAuth;/* 因移动节点认证失败(Code 67)，外地代理而拒绝注册请求的总数*/
    VOS_SIZE_T pulDenyLifeTime;/* 因请求的生命期限太长(Code 69).，外地代理而拒绝注册请求的总数*/
    VOS_SIZE_T pulDenyRrqForm; /*  因请求消息格式错误(Code 70)，外地代理而拒绝注册请求的总数 */
    VOS_SIZE_T pulDenyEncap; /* 因请求的封装无效(Code 72)，外地代理而拒绝注册请求的总数*/
    VOS_SIZE_T pulDenyRegTimeOut;  /* FA因注册超时而拒绝的注册请求总数（错误代码78） */
    VOS_SIZE_T pulRcvValidRrpNum;/* FA收到HA的注册应答总数*/
    VOS_SIZE_T pulRelayRrpNum;/* FA转发给MN的注册应答总数*/
    VOS_SIZE_T pulRcvInvalidRrp;/* FA收到的无效注册应答总数 */
    VOS_SIZE_T pulDenyHaAuth; /* 因HA的认证失败(Code 68)导致的外地代理拒绝注册应答的总数*/
    VOS_SIZE_T pulSendRevo;   /* FA发出的Revocation消息总数 */
    VOS_SIZE_T pulRcvRevo;  /* FA收到的Revocation消息总数 */
    VOS_SIZE_T pulMipCurUsrNum;/* 当前激活移动IP用户数 */
    
    VOS_SIZE_T pulPmipRrqNum;/* PMIP用户FA发送给HA的注册请求总数 */
    VOS_SIZE_T pulPmipRrpNum;/* PMIP用户FA收到HA的注册应答总数 */
    VOS_SIZE_T pulPmipSuccsRrpNum; /* PMIP用户FA收到HA的成功注册应答总数 */
    VOS_SIZE_T pulPmipCurUsrNum;/* 当前PMIP用户数 */
    VOS_SIZE_T pulPmipActReqNum;/* PMIP会话激活请求数 */
    VOS_SIZE_T pulPmipActSuccsNum;/* PMIP会话激活成功数 */
    VOS_SIZE_T pulDenyRrpForm ;/* 因应答消息的格式错误(Code 71)而产生的拒绝注册应答的总数 */
} FA_PERFSTATISTIC_S;

/*******************************************************************************************************/
/********************                        全局变量                           ************************/
/*******************************************************************************************************/
extern VOS_UINT32 g_ulFaTaskId;                  /* FA任务ID */

extern VOS_UINT32 g_ulTimerToFaQueId;            /* FA定时器消息队列 */
extern VOS_UINT32 g_ulPdnToFaQueId;              /* FA与PDN消息队列 */
extern VOS_UINT32 g_ulAuthToFaQueId;             /* FA与AUTH消息队列 */

extern MC_QUE_ID g_pDpeToFaQueID ;     /* 接收DPE发送到FA的RRQ信令队列*/
extern MC_QUE_ID g_pSdToFaQueID;            /* 接收SD到FA的共享消息队列 */
extern MC_QUE_ID g_pDpeToFaRvcQueID;

extern UCHAR g_ucPmipFaMode;                /* FA工作模式, 软参48 */


extern VOS_UINT32 g_ulFaMipUserCounter; /*mip license*/
extern VOS_UINT32 g_ulFaMaxMipUserNum; /*当前mip用户数*/
extern FA_PERFSTATISTIC_S g_stFaPerfStatistic;    /*性能统计数据*/

/*******************************************************************************************************/
/********************                        外部接口                           ************************/
/*******************************************************************************************************/
//extern VOS_UINT32   FA_SetA10Tbl(VOS_UINT32 ulRpIndex, DPS_CP_A10_CMDBLOCK_S* pstA10Tbl);
extern VOS_UINT32 FA_PrintMipData(VOS_UINT32 ulPdnIndex, UCHAR* pucBuff);    /*上下文MIP字段输出*/
extern VOS_UINT32 FA_GetContexSize(VOS_VOID);
extern VOS_UINT32 FA_GetContextInfoByPdnIndex(VOS_UINT32 ulPdnIndex , FA_A11_INFO_S* pstFaA11Info);
extern VOID FA_MipVpnInit(VOS_VOID);
extern VOID FA_MipPccInit(VOS_VOID);
extern VOS_UINT32 FA_GetSduIdByNaiHash (VOS_UINT32 ulHashTblNum, VOID* pData);
extern VOS_UINT32 FA_WhtherSendNaiTokenToSDU(SDB_PDSN_RP_CONTEXT_S *pstRpContext, UCHAR **ppucNai);
extern VOID FA_FreeResBeforeFreePdnRes(VOS_UINT32 ulPdnIndex);
extern VOS_UINT32 FA_BackupMasterCreUpdFaProc(VOS_UINT32 ulPdnIndex, VOS_UINT32 ulOperType, UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 FA_BackupSlaveCreUpdFaProc(UCHAR *pucCurrent);
extern VOS_UINT32 FA_BackupMasterUpdFaAdvSeqProc(VOS_UINT32 ulPdnIndex, VOS_UINT32 ulOperType, UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen);
extern VOS_UINT32 FA_BackupSlaveUpdFaAdvSeqProc(UCHAR *pucCurrent);

extern VOS_UINT32 FA_BackupSmoothFaContext(PDN_CONTEXT_S *pstPdnContext);
extern VOS_UINT32 FA_GetRpIndexByFaIndex(VOS_UINT32 ulFaIndex, VOS_UINT32 *pulRpIndex);
extern VOS_UINT32 FA_A11UpdateNpTable( VOS_UINT32 ulFaIndex );
extern VOS_UINT32 FA_PdnCheckPccSwitch(UCHAR ucPdnType);
extern VOS_UINT32 FA_ResCheckByFaContextIndex(VOS_UINT32 ulFaContextIndex);
extern VOS_UINT32 FA_OmInitial(VOID);
#ifdef      __cplusplus
}
#endif 

#endif
