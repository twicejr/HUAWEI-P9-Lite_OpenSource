/************************************************************************
*                                                                      *
*                             ppp_var.c                                *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/03/27                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP模块的全局变量定义                           *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了PPP模块的所有全局变量                                *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* PPP内部可维可测勾包信息存储 */
CTTF_PPPC_TRACE_DATA_STRU   g_stPppInterMntnInfo;

/* PPP与CDS交互可维可测勾包信息存储 */
CTTF_PPPC_TRACE_DATA_STRU   g_stPppCdsMntnInfo;

/* PPP与RLP交互可维可测勾包信息存储 */
CTTF_PPPC_TRACE_DATA_STRU   g_stPppRlpMntnInfo;

PTM_COMPONENT_INFO_S g_stPppCompInfo = { 0 };
VOS_UINT64 g_ullPppLocalL2tpCsi = 0;        /* 本板LAC组件CSI */
VOS_UINT64 g_ullPppAuthCsi = 0;              /* AUTH的CSI */
VOS_UINT64 g_ullPppFACsi = 0;               /* FA的CSI */
VOS_UINT64 g_ullPppDiamAuthCsi = 0;              /* AUTH的CSI */

VOS_UINT64 g_ullPPPLAP2Csi = 0;               /* LAP2的CSI */

VOS_UINT64 g_ullPppA11Csi = 0 ;           /* A11的CSI */
VOS_UINT32 *g_aulDoStatiscTime = VOS_NULL_PTR;
VOS_UINT32 *g_aulNoStatiscTime = VOS_NULL_PTR;


HTIMER g_ahNegoListTimeoutID[] = {VOS_NULL_PTR, VOS_NULL_PTR};

/* VOS_UINT32 *g_ulPppFsmStat[5] = { VOS_NULL_PTR }; */ /* 各状态机消息和事件统计 */
VOS_UINT32 g_ulPppFsmStat[5][PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT]; /* 各状态机消息和事件统计 */

/* PPP_DEBUG_INFO_S *g_pstPppInnerDebugInfo = VOS_NULL_PTR; */
PPP_DEBUG_INFO_S g_pstPppInnerDebugInfo[PPP_INNER_COUTNER_END];

/* PPP_DEBUG_INFO_S *g_pstPppErrorDebugInfo = VOS_NULL_PTR; */
PPP_DEBUG_INFO_S g_pstPppErrorDebugInfo[PPP_ERROR_COUNTER_END];

VOS_UINT32 g_ulPppA11NotifyQueID = 0;/* A11通知PPP消息队列*/
VOS_VOID * g_pstPppLAPNotifyQueID  = VOS_NULL_PTR;/* LAP通知PPP消息队列 */
VOS_VOID * g_pstPppL2TPNotifyQueID = VOS_NULL_PTR;/* PPP通知L2TP消息队列 */
VOS_VOID * g_pstL2TPPppNotifyQueID = VOS_NULL_PTR;/* L2TP通知PPP消息队列 */

/* 地址释放队列 共享内存消息队列*/
VOS_VOID *g_pstPppNegoQueID = VOS_NULL_PTR;        /* 协商报文消息队列 */

VOS_UINT32 g_ulAuthPapOnoff = 0;/*控制PAP鉴权*/
VOS_UINT32 g_ulAuthChapOnoff = 0;/*控制CHAP鉴权*/

VOS_UINT32 g_ulPCompressOnoff = 0;/*控制协议域压缩协商*/
VOS_UINT32 g_ulACompressOnoff = 0;/*控制地址域压缩协商*/
VOS_UINT32 g_ulPppEchoRetransmit = PPP_DEFMAXCONFREQS;
VOS_UINT32 g_ulPppEchoTimeout = 10; /* 处理时*1000后表示10秒 */
VOS_UINT32 g_ulPppVsncpGetPCO = VOS_FALSE;  /* 是否获取PCO */

CHAR AuthMsgError[]   = "Invalid user name or password.";
CHAR AuthMsgSuccess[] = "Welcome to ggsn.";

/* Add by h50774, 压缩支持子卡负荷分担 */
VOS_UINT32 g_ulPppSubBordStat[MAX_DMPU_NUM] = { 0 };  /* 子卡状态 */
VOS_UINT32 g_ulDmpuMppcUser[MAX_DMPU_NUM] = { 0 }; /* 子卡MPPC用户数 */
VOS_UINT32 g_ulDmpuVjUser[MAX_DMPU_NUM] = { 0 };   /* 子卡VJ用户数 */
VOS_UINT32 g_ulDmpuDpeNumber[MAX_DMPU_NUM] = { 14,14 };
VOS_UINT32 g_ulMaxDmpuDpeCpuRate = 0;                 /* 负荷最高DPE的CPU占用率 */
VOS_UINT32 g_ulMinDmpuDpeCpuRate = 0;                 /* 负荷最低DPE的CPU占用率 */
/*lint -e785*/
VOS_UINT32 g_ulDmpuDpeCpuRate[MAX_DMPU_NUM * MAX_DPE_NUM_PDSN] = {10};
/*lint +e785*/
VOS_UINT32 g_ulLastSelDmpuDpe = 0;                    /* 上次选择的DPE */
VOS_UINT32 g_ulPppReNegIndex = 0;                     /* 用于记录当前重协商的用户索引 */
VOS_UINT32 g_ulDmpuCpuThreshold = 80;                 /* 子卡CPU占用率门限 */
VOS_UINT32 g_ulMaxVJNum = 6000;
VOS_UINT32 g_ulMipLicMsgQueID = 0;
VOS_UINT32 g_ulStubDpeNo = VOS_FALSE; /* 打桩指定选择的子卡DPE号 */
UCHAR g_ucStubDmpuId = 0; /* 打桩指定子卡ID */
VOS_UINT8  g_ucUdpCheckSumFlag = 0; /*udp checksum 软参*/

/* VSNCP_OPTION_DECODE *g_pVsncpOptionDecode = VOS_NULL_PTR; */
VSNCP_OPTION_DECODE g_pVsncpOptionDecode[PPP_VSNCP_CO_BUTT];

/* VSNCP_OPTION_ENCODE *g_pVsncpOptionEncode = VOS_NULL_PTR; */
VSNCP_OPTION_ENCODE g_pVsncpOptionEncode[PPP_VSNCP_CO_BUTT];

VSNP_CONIFG_OPTION_FLAG_S g_stVsncpOptionFlag = {0};

LINKTCB_S        g_pstLocalLinkTcb[PPP_MAX_USER_NUM + 1];

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
PPPC_HDLC_STRU   g_astHdlcPool[PPP_MAX_USER_NUM + 1];
#endif

/* PPPINFO_S        *g_astPppPool     = VOS_NULL_PTR;*/
PPPINFO_S        g_astPppPool[PPP_MAX_USER_NUM + 1];

/* PPPLCPINFO_S     *g_astPppLcpPool  = VOS_NULL_PTR; */
PPPLCPINFO_S     g_astPppLcpPool[PPP_MAX_USER_NUM + 1];

/* PPPIPCPINFO_S    *g_astPppIpcpPool = VOS_NULL_PTR; */
PPPIPCPINFO_S    g_astPppIpcpPool[PPP_MAX_USER_NUM + 1];

/* PPPPAPINFO_S     *g_astPppPapPool  = VOS_NULL_PTR; */
PPPPAPINFO_S     g_astPppPapPool[PPP_MAX_USER_NUM + 1];

/* PPPCHAPINFO_S    *g_astPppChapPool = VOS_NULL_PTR; */
PPPCHAPINFO_S    g_astPppChapPool[PPP_MAX_USER_NUM + 1];

/* PPP_CCP_INFO_S   *g_astPppCcpPool  = VOS_NULL_PTR; */
PPP_CCP_INFO_S   g_astPppCcpPool[PPP_MAX_USER_NUM + 1];

/* PPPCONFIGINFO_S  *g_astPppConfifPool  = VOS_NULL_PTR; */
PPPCONFIGINFO_S  g_astPppConfifPool[PPP_MAX_USER_NUM + 1];

PPP_NEGO_NODE_S  *g_pstPppNegoList = VOS_NULL_PTR;
/* BEGIN: Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */
PPP_NEGO_NODE_S  *g_pstPppPDNNegoList = VOS_NULL_PTR;
PPP_NEGO_NODE_S  *g_pstPppRPNegoList = VOS_NULL_PTR;
/* END:   Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */
/* PPPIPV6CPINFO_S  *g_astPppIpv6cpPool = VOS_NULL_PTR; */
PPPIPV6CPINFO_S  g_astPppIpv6cpPool[PPP_MAX_USER_NUM + 1];

#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
/* PPPC_EAP_INFO_STRU     *g_astPppEapPool = VOS_NULL_PTR; */
PPPC_EAP_INFO_STRU     g_astPppEapPool[PPP_MAX_USER_NUM + 1];

#endif
VOS_UINT32 ulOneSecondTimer = 0;

PPPA11_AlarmLink_HEAD_S g_stPppA11AlarmLink = {0};

VOS_UINT32 g_ulPPPTaskId = 0;
VOS_UINT32 g_ulPPPLapFlowctrl = 35;
VOS_UINT32 g_ulPPPA11Flowctrl = 25;
VOS_UINT32 g_ulPPPTimerFlowctrl = 55;
VOS_UINT32 g_ulPPPAAAFlowctrl = 25;
VOS_UINT32 g_ulPPPNegoFlowctrl = 50;
VOS_UINT32 g_ulPPPPcrfcFlowCtrl = 25;
VOS_UINT32 g_ulPPPTmpTaskFlowCtrl = 25;

VOS_UINT32 g_ulPPPL2tpFlowctrl = 25;


VOS_UINT32 g_ulPppDiamAaaQueID;      /* AUTH消息队列 */
VOS_UINT32 g_ulPppNegoQueID;     /* 协商报文消息队列 */
VOS_UINT32 g_ulPppAaaQueID;      /* AUTH消息队列 */
VOS_UINT32 g_ulPppDhcpQueID;     /* DHCP消息队列 */
VOS_UINT32 g_ulPppTimeQueID;     /* 定时器消息队列 */
VOS_UINT32 g_ulPppCcpQueID; /* 压缩数据消息队列 */ /*WGGSN_B03_L2TP_PPPC_COMP*/
VOS_UINT32 g_ulPppCompressQueID;
VOS_UINT32 g_ulPppGspcQueID;     /* Added by liutao 38563 at 2004-09-21 V800R002 for PPP压缩移植 */
VOS_UINT32 g_ulPppPcrfcQueID;    /*与PCRFC交互消息队列*/
LONG g_ulPppL2tpMaxUserNum;/* L2TP最大用户数 */
LONG g_ulPppCcpMaxUserNum;
LONG g_ulPppVjMaxUserNum;
VOS_UINT32 g_ulPppLicenseQueID;      /* License消息队列 */

VOS_UINT32 g_ulPppInnerMsgQueID = 0;   /* added by luofang 临时任务消息队列 */

/*当前spu板类型*/
CRM_SPU_BOARD_TYPE_ENUM g_enPppBoardType = CRM_BOARD_TYPE_UNKNOWN;


/* debug开关使用的变量 */
struct tagPppDebugInfo g_stPppDebugInfo;

/*------------- 性能统计使用的全局变量 -------------*/
PPPPERFSTATISTIC_S g_stPppPerfStatistic;
IPV6PERFSTATISTIC_S g_stIpv6PerfStatistic = {0};
VOS_UINT32 g_aulIpv6Cnt[E_IPV6_CNT_END] = {0};          /*分支统计计数*/

/*------------- 内部调试使用的全局变量 -----------------*/
IMSI_S g_stPppDebugImsi;        /* 单用户调试IMSI信息*/

/*------------- 备份倒换模块的全局变量 -----------------*/
UCHAR g_ucPppBkpFailFlg;            /* 备份过程状态标志,1失败,0成功 */
VOS_UINT32 g_ulPppRoutineBkpCurIndex;           /* 定时当前控制块索引*/
VOS_UINT32 g_ulPppRoutineBkpHeadIndex;          /* 定时头控制块索引*/
PPP_CHANGEDINFO_BKP_S*    g_stPppChangedInfoBkp;

VOS_UINT32 g_ulPppBackupTID = 0;
VOS_UINT32 ulDealedNum = 0;
VOS_UINT32 g_ulBackupControl = 20;

VOS_UINT32 g_ulPppTaskTrace = 0;

VOS_UINT16 g_usPppVjUserNUm[MAX_DMPU_NUM][MAX_DPE_NUM_PDSN] = { {0},{0} };    /*VJ压缩用户数,用于调试统计*/
VOS_UINT16 g_usPppMppcUserNum[MAX_DMPU_NUM][MAX_DPE_NUM_PDSN] = { {0},{0} };  /*Mppc压缩的用户数,用于调试统计*/

VOS_UINT16 g_usPppLzs0UserNum;  /*LZS0压缩用户数*/
VOS_UINT16 g_usPppLzs1UserNum; /* LZS1压缩用户数 */
VOS_UINT8 g_ucPppCcpSwitch;    /*STAC和MPPC压缩开关*/
VOS_UINT8 g_ucPppCcpType;      /*CCP压缩类型，MPPC:0, STAC:1*/
VOS_UINT8 g_ucPppVjSwitch;     /*VJ压缩开关*/
VOS_UINT16* g_pusPppL2tpCallId;  /*PPP的index与L2TP的call转换表*/
PPP_CFG_INFO_REC_S g_stPppCfgInfo;

/* debug使用的变量和数组 */

CHAR *g_cPPP_Debug_Protocol_Name[] =
{
    "IP",
    "LCP",
    "PAP",
    "CHAP",
    "IPCP",
    "IPXCP",
    "MP",
    "BCP",
    "BRIDGE",
    "VJComp",
    "VJUnComp",
    "IPX",
    "CCP",
    "MCCP",
    "SCP",
    "MCP",
    "MPLSCP",
    "MPLS-UNICAST",
    "MPLS-MULTICAST",
    "OSICP",
    "OSI-NPDU",
    "VSNCP",
    "EAP",
    "IPV6CP"
};

CHAR *g_cPPP_Debug_code[] =
{
    "Reserved",      /* 0 */
    "ConfReq",      /* 1 */
    "ConfAck",      /* 2 */
    "ConfNak",      /* 3 */
    "ConfRej",      /* 4 */
    "TermReq",      /* 5 */
    "TermAck",      /* 6 */
    "CodeRej",      /* 7 */
    "ProtoRej",     /* 8 */
    /* Modified by VendrunChen for spelling mistake */
    /* D16845 on 20020930 */
    "EchoRequest",    /* 9 */
    "EchoReply",    /* 10 */
    "DiscrReq",     /* 11 */
    "Identific",    /* 12 */
    "TimeRemain",   /* 13 */
    "ResetReq",     /* 14 */
    "ResetAck"      /* 15 */
};

CHAR *g_cPPP_Debug_state[] =
{
    "initial",
    "starting",
    "closed",
    "stopped",
    "closing",
    "stopping",
    "reqsent",
    "ackrcvd",
    "acksent",
    "opened",
    "initial"
};

CHAR *g_cPPP_Debug_event[] =
{
    "Up   ",
    "Down ",
    "Open ",
    "Close",
    "TO+  ",
    "TO-  ",
    "RCR+ ",
    "RCR- ",
    "RCA  ",
    "RCN  ",
    "RTR  ",
    "RTA  ",
    "RUC  ",
    "RXJ+ ",
    "RXJ- ",
    "RXR  "
};

CHAR *g_cPPP_Debug_LcpOption[] =
{
    "RESERVED",      /* 0 */
    "MRU",           /* 1 */
    "ACCMAP",        /* 2 */
    "AuthProto", /* 3 */
    "QualityProto", /* 4 */
    "MagicNumber",   /* 5 */
    "",              /* 6 */
    "PFC",           /* 7 */
    "ACFC",          /* 8 */
    "MRRU",          /* 9 */
    "SSNHF",     /* 10 */
    "Discri",       /* 11 */
    "Callback"       /* 12 */
};

CHAR *g_cPPP_Debug_IpcpOption[] =
{
    "RESERVED",
    "IP Addresses",
    "IP CompressProt",
    "IP Address",
    "Primary DNS Server Address",
    "Primary NBNS Server Address",
    "Secondary DNS Server Address",
    "Secondary NBNS Server Address"
};


PPP_FAIL_COUNTER g_stPPPFailCounter;


VOS_UINT32 g_ulPppDebugSwitch = VRP_NO;
/* UCHAR *g_ucPppSendPacketHead = VOS_NULL_PTR; */
UCHAR g_ucPppSendPacketHead[PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER];

/* UCHAR *g_ucPppRcvPacketHead = VOS_NULL_PTR; */
UCHAR g_ucPppRcvPacketHead[PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER];

VOS_UINT32 g_ppp_ulTempLapBatchDelteTaskID2 = 0;
VOS_UINT32 g_ulLapReportTID = 0;
VOS_UINT32 g_ulLap1RebuildingFlag = 0;

VOS_UINT32 g_ulPppDBGStatisc[PPP_DBG_BUTT];

/* 以下用于PPP的软参 */
VOS_UINT32 g_ulSoftPara534 = 0;
VOS_UINT32 g_ulSoftPara562 = 0;
VOS_UINT32 g_ulSoftPara567 = 0;
VOS_UINT32 g_ulSoftPara571 = 0;
VOS_UINT32 g_ulSoftPara577 = 0;
VOS_UINT32 g_ulSoftPara537 = 0;
VOS_UINT32 g_ulSoftPara585 = 0;
VOS_UINT32 g_ulSoftPara586 = 0;
VOS_UINT32 g_ulSoftPara587 = 0;


VOS_UINT32 g_ulReNegoTaskId = 0;

VOS_UINT32 g_ulPppAAAWritelogFlag = 0;


 /* PPP日志级别 */
 VOS_UINT32 g_ulPppLogLevelErr = 0;


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
