#ifdef    __cplusplus
extern "C" {
#endif

#ifndef _PPP_INIT_H
#define _PPP_INIT_H

#define M_IMSI_LEN 16
#define CMP_CHECK_CPU_USAGE 60

#ifndef __LINUX_PLATFORM__
#define MAX_DMPU_ID MAX_DMPU_NUM
#else
#define MAX_DMPU_ID PPP_CPU_3_ON_SPU
#endif


#define HSGW_PRODUCT_VJ_USER_NUMBER_PER_SC                (HSGW_PRODUCT_VJ_USER_NUMBER/SC_NUM)
#define HSGW_PRODUCT_MPPC_PDP_NUMBER_PER_SC               (HSGW_PRODUCT_MPPC_PDP_NUMBER/SC_NUM)

/* PPP内部消息结构体 */
typedef struct
{
    VOS_UINT32 ulCurRenegoIndex;
}PPP_INNER_MSG_S;

typedef enum
{
    PPP_INNER_MSG_CODE_RENEGO = 1,
} PPP_INNER_MSG_CODE_E;



/* PPP控制块全量备份的结构体 */
typedef struct tagCKP_BACKUP_PPPALLINFO_S
{
    /*********************************/
    /*       指针定义              */
    /*********************************/
    //PPPCONFIGINFO_S* pstConfigInfo;         /* 配置信息 */
    //PPPCONFIGINFO_S* pstUsedConfigInfo;     /* 当前接口上用户输入的配置信息,只对配置可见接口有效 */
    //PPPRENOGOINFO*   pstPppRenegoInfo;      /* 重协商信息 */

    //VOID* pstLcpInfo;           /* LCP  控制块指针 */
    //VOID* pstPapInfo;           /* PAP  控制块指针 */
    //VOID* pstChapInfo;          /* CHAP 控制块指针 */
    //VOID* pstEapInfo;           /* EAP  控制块 */
    //VOID* pstIpcpInfo;          /* IPCP 控制块指针 */
    //VOID* pstIpV6cpInfo;        /* IPV6CP 控制块指针 */
    //VOID* pstVsncpInfo;         /* VSNCP 控制块指针 */
    //VOID* pstCcpInfo;           /* CCP  控制块指针 */
    //VOID* pL2tpPara;            /* L2TP需要的参数 */
    //VOID* pulCurrFsm;           /* 当前状态机 */

    PPP_LCP_OPTION_S  stLcpGotOptions;
    PPP_IPCP_OPTION_S stIpcpGotOptions;
    PPP_IPV6CP_OPTION_S stIpv6cpGotOptions;

    VOS_UINT32 bIsAsync          : 1,        /* 是否是异步口, 在LCP中判断是否协商ACCMAP */
          bSynAsyConvert    : 1,        /* 对于异步口，用于确定是否由PPP进行同/异步报文转换 */
          bLoopBacked       : 1,        /* 接口是否发生了自环 */
          bLowerIsUp        : 1,
          bIPReleaseFlg     : 1,        /* 0: 需要释放IP， 1: 不需要释放IP(MIP&L2tp用户)*/
          bIPTech           : 2,        /* 0: SIP; 1: MIP; 2: MIPAgent ;3 NIL*/
          bAuthServer       : 1,        /* PDSN产品形态仅支持server模式；0表示认证完毕或者免认证；1正在进行认证 */
          bAuthClient       : 1,        /* PDSN产品形态不支持client模式；该值始终为零 */
          bReNego           : 1,        /* 重协商标志 */
          bReNegoV6         : 1,        /* IPV6重协商标志 */
          bPppStateFlg      : 2,        /* 稳态连接标记 */
          bPppMode          : 1,        /* 终结模式为0，续传模式为1 */
          bPppClient        : 1,        /* 客户端模式为1，否则为0 */
          bPhaseFlag        : 2,        /* 0:LCP阶段，1:鉴权阶段，2:IPCP阶段 3:成功阶段 */
          bFailFlag         : 4,        /* 0:自己协商失败. 1:A11/GTPC通知删除. 2:用户要求下线. 3:L2TP通知删除 */
          bMppcFlag         : 1,        /* MPPC用户数统计标志 */
          bVjFlag           : 1,        /* VJ用户数统计标志 */
          bLzs0Flag         : 1,        /* Stac_Lzs0用户数统计 */
          bLzs1Flag         : 1,        /* Stac_Lzs1用户数统计 */
          bPpcAAAFlag       : 1,        /* add by g00127633 增加预付费用户是否需要到AAA鉴权 0不需要到AAA,1需要*/
          bPppSuccess       : 1,        /* PPP建立成功标记,用于PPP指标优化 */
          bAuthFlag         : 1,        /* 用于判断是否已经完成过chap或pap鉴权,若是VOS_TRUE,则重协商不再走AAA */
          bIpcpSucFlag      : 1,        /* PPP协商IPCP协商成功标记,该标记在重协商过程也不会改变 */
          bPppStateFlgV6    : 2,        /* IPV6稳态连接标记 */
          bPccFlag          : 1;        /* 是否为PCC用户标识*/

    VOS_UINT32 bRecvLcpMsgFlag   : 1,        /* 表示是否收到过LCP的消息*/
          bBit328SoftPara   : 1,        /* bit328软参配置 */
          bIpv6cpNoToPDN    : 1,        /* ipv6cp finish 时是否通知PDN, 0表示通知， 1为不通知 */
          bIpcpNoToPDN      : 1,        /* ipcp finish 时是否通知PDN, 0表示通知， 1为不通知 */
          bEhrpdUser        : 1,        /* 是否为eHRPD用户 */
          bMppc             : 1,        /* mppc压缩标志 */
          bEAPAuthFlag      : 1,        /* EAP是否已经成功过 */
          bIPCPNakHandFlag  : 1,        /* IPCP NAK HANDLING */
          bReservNew        : 24;       /* 注意修改为对齐 */


    /*********************************/
    /*       结构体定义              */
    /*********************************/
    //IMSI_S            stIMSI;

    //PPPDEBUGINFO_S stPppDebugInfo;    /* 调试信息 */
    //VOS_UINT32 ulPppRleaseCode;
    VOS_UINT32 ulRemoteAccm;         /* 对端ACCM控制字 */
    VOS_UINT32 ulLocalAccm;          /* 本端ACCM控制字 */
    //VOS_UINT32 ulRPIndex;
    VOS_UINT32 ulPcfIP;
    VOS_UINT32 ulIPAddr;             /* 本端IP地址，初始化为2.2.2.2 */
    VOS_UINT32 ulPeerIPAddr;         /* 保存RADIUS SERVER或DHCP发送的用户IP地址 */
    VOS_UINT32 ulDNSAddr1;
    VOS_UINT32 ulDNSAddr2;
    //ULONG64 ulNegoStartTime;      /* PPP协商开始时间 */
    //ULONG64 ulNegoEndTime;        /* 双栈ipv6先协商成功记录该值,问题单号:DTS2012051200799 */
    VOS_UINT32 ulNowUTCInSec;

    VOS_UINT16 usPeerId;                   /* 保存第一次发送服务器id */
    VOS_UINT16 usDynPeerId;                /* 保存第一次发送服务器id */
    UCHAR ucLcpPktId;
    UCHAR ucIpcpPktId;
    UCHAR ucAAAType;
    UCHAR aucRvs;
    UCHAR aucAAAHost[DIAM_AUTH_DRA_HOST_MAX_LENGTH + 1];        /* origin host */
    UCHAR aucAAARealm[DIAM_AUTH_REALM_OR_HOST_MAX_LENGTH + 1];       /* origin realm */
    //VOS_UINT16 usTokenId;

    //VOS_UINT16 usState;
    //VOS_UINT16 usPhase;
                                                /* PPP当前所处协商阶段,可以为如下值:
                                                 PPP_PHASE_DEAD
                                                 PPP_PHASE_ESTABLISH
                                                 PPP_PHASE_AUTHENTICATE
                                                 PPP_PHASE_CBCP
                                                 PPP_PHASE_NETWORK
                                                 PPP_PHASE_TERMINATE
                                               */
    VOS_UINT16 usCDBIndex;     /* GGSN:APNIndex PDSN:DomainIndex */
    VOS_UINT16 usVirtualDomainIdx;

    VOS_UINT16 usMtu;
    VOS_UINT16 usPcfIndex;

    VOS_UINT16 usIpv6Addr[IPV6_ADDR_LEN];     /*本端ipv6地址，初始化为:FE80::FFFF:FFFF:FFFF:FFFF*/
    VOS_UINT16 usPeerIPv6Addr[IPV6_ADDR_LEN]; /* 保存RADIUS SERVER或lap分配的用户IPv6地址包含前缀和接口id*/


    //UCHAR ucNAI[A11_MAX_NAI_LENGTH + 1];

    UCHAR  ucServiceOpt;
    UCHAR  ucFSMFailType;           /* FSM_CODE_E */
    UCHAR  ucDmpuId;                /* 压缩子卡CPU号, 0为CPU2, 1为CPU3 */
    UCHAR  ucDpeId;                 /* 子卡DPE号 */

    UCHAR  ucIpCapability;     /*ip能力，参见枚举 PDSN_PPP_IPTYE 定义 */
    UCHAR  ucEchoState;
    VOS_UINT16 usStac_historys;
} CKP_BACKUP_PPPALLINFO_S;

VOID PPP_PerfInc(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType, UCHAR ucEhrpdMode);
VOID PPP_PerfDec(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType, UCHAR ucEhrpdMode);
VOID IPV6_PerfInc(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType);
VOID IPV6_PerfDec(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType);

extern VOS_UINT32 g_ulDmpuMppcUser[MAX_DMPU_NUM]; /* 子卡MPPC用户数 */
extern VOS_UINT32 g_ulDmpuVjUser[MAX_DMPU_NUM];   /* 子卡VJ用户数 */
extern VOS_UINT32 g_ulPppSubBordStat[MAX_DMPU_NUM]; /* 子卡状态 */

#define PPP_ClearLCPCB(pstLcpInfo)    \
    if(pstLcpInfo != VOS_NULL_PTR)            \
    {                                 \
        PPP_ClearCB_LCP(pstLcpInfo);  \
        pstLcpInfo = VOS_NULL_PTR;            \
    }

#define PPP_ClearMipAgentCB(pstMipAgentInfo)   \
    if(pstMipAgentInfo != VOS_NULL_PTR)                \
    {                                          \
        PPP_ClearCB_MipAgent(pstMipAgentInfo); \
        pstMipAgentInfo = VOS_NULL_PTR;                \
    }

#define PPP_ClearPAPCB(pstPapInfo)   \
    if(pstPapInfo != VOS_NULL_PTR)           \
    {                                \
        PPP_ClearCB_PAP(pstPapInfo); \
        pstPapInfo = VOS_NULL_PTR;           \
    }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
#define PPP_ClearEAPCB(pstEAPInfo)   \
        if(pstEAPInfo != VOS_NULL_PTR)           \
        {                                \
            PPP_ClearCB_EAP(pstEAPInfo); \
            pstEAPInfo = VOS_NULL_PTR;           \
        }
#endif

#define PPP_ClearCHAPCB(pstChapInfo)   \
    if(pstChapInfo != VOS_NULL_PTR)            \
    {                                  \
        PPP_ClearCB_CHAP(pstChapInfo); \
        pstChapInfo = VOS_NULL_PTR;            \
    }

#define PPP_ClearIPCPCB(pstIpcpInfo)   \
    if(pstIpcpInfo != VOS_NULL_PTR)            \
    {                                  \
        PPP_ClearCB_IPCP(pstIpcpInfo); \
        pstIpcpInfo = VOS_NULL_PTR;            \
    }

#define PPP_ClearIPV6CPCB(pstIpv6cpInfo)   \
if(pstIpv6cpInfo != VOS_NULL_PTR)            \
{                                  \
    PPP_ClearCB_IPV6CP(pstIpv6cpInfo); \
    pstIpv6cpInfo = VOS_NULL_PTR;            \
}

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)

#define PPP_ClearMSIDCB(pstMsidInfo)   \
    if(pstMsidInfo != VOS_NULL_PTR)            \
    {                                  \
        PPP_ClearCB_MSID(pstMsidInfo); \
        pstMsidInfo = VOS_NULL_PTR;            \
    }


#define PPP_ClearCCPCB(pstCcpInfo)   \
    if(pstCcpInfo != VOS_NULL_PTR)           \
    {                                \
        /*lint -e746*/  \
        PPP_ClearCB_CCP(pstCcpInfo); \
        /*lint +e746*/ \
        pstCcpInfo = VOS_NULL_PTR;           \
    }


#define PPP_ClearMPLSCPCB(pstMplscpInfo)   \
    if(pstMplscpInfo != VOS_NULL_PTR)              \
    {                                      \
        PPP_ClearCB_MPLSCP(pstMplscpInfo); \
        pstMplscpInfo = VOS_NULL_PTR;              \
    }

#define PPP_ClearSTACCB(pstStacCompressInfo, pstStacDeCompressInfo)      \
    if((pstStacCompressInfo != VOS_NULL_PTR) || (pstStacDeCompressInfo != NULL)) \
    {                                                                     \
        PPP_ClearCB_STAC(pstStacCompressInfo, pstStacDeCompressInfo);     \
        pstStacCompressInfo = VOS_NULL_PTR;     \
        pstStacDeCompressInfo = VOS_NULL_PTR;   \
    }
#endif

#define PPP_ClearIPXCPCB(pstIpxcpInfo)   \
    if(pstIpxcpInfo != VOS_NULL_PTR)             \
    {                                    \
        PPP_ClearCB_IPXCP(pstIpxcpInfo); \
        pstIpxcpInfo = VOS_NULL_PTR;             \
    }

VOS_UINT32 PPP_GetDomainInfoByName(PPPINFO_S *pstPppInfo, UCHAR* pucName);
extern VOS_UINT32 PPP_GetIpAddrFromPacket(UCHAR *pPacket, VOS_UINT32 ulLen, VOS_UINT32 *pulIpAddr );
extern VOID PPP_EAP_NotifyDiamAuthRelease(PPPINFO_S *pstPppInfo);
extern VOID PPP_VSNCP_ClearALL(PPPINFO_S *pstPppInfo);
extern VOS_VOID PPP_VSNCP_StopRetransmitTimer(VOS_VOID);


extern VOID PPP_A11_GetBSIDFromBCD(UCHAR *pucDst, const UCHAR *pucSrc, VOS_UINT32 ulLength);

VOS_VOID PPP_CompRescSyn(VOS_VOID);

extern VOS_UINT32 PPP_CheckMppcLimit(VOS_VOID);
extern VOS_UINT32 A11_CompressStatistic(VOS_UINT32 ulValue, VOS_UINT8 ucOperateObject, VOS_UINT8 ucDmpuId,
                             VOS_UINT8 ucDpeId, VOS_UINT8 ucFlag);

extern VOID CDB_PppCompressCfgModNotify(CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR* pNewValue, UCHAR* pOldValue);
extern VOID CDB_PppCompressGetGlobalVar(PPP_COMPRESS_CFG *pstCompCfg);
extern VOID CDB_PppCompressCfgAddNotify(CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*  pValue);

extern VOS_VOID PPP_SendInnerMsg(VOS_UINT32 ulPara);
extern VOID PPP_ClearVjFlag(VOS_UINT32  ulRpIndex);

extern VOS_UINT32 PPP_ModDomainInfoForCMIP(VOS_UINT32 ulRpIndex, VOS_UINT16 usDomainIdx);
extern VOS_UINT32 PPP_USMNotifyRelease(PPP_A11MSG_S *pstA11Msg);
extern VOS_UINT32 Diam_AUTHBackupRebuildDynAAACB(VOS_UINT16 usNewPeerId, VOS_UINT16 usDynPeerId,
                                     UCHAR *pucAAAHost, UCHAR *pucAAARealm);

extern VOID PPP_PDNNegoListProc(VOID *pPara);
extern VOS_UINT32 PPP_CompCheckVjUserNum(UCHAR *pucDmpuId);
extern VOS_UINT32 PPP_CompCheckMppcUserNum(UCHAR *pucDmpuId);

#endif

#ifdef    __cplusplus
 }
#endif    /* end of __cplusplus */

