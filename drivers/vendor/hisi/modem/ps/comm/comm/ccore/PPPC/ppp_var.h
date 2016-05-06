
/************************************************************************
 *                                                                      *
 *                             ppp_var.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/27                                      *
 *  Author:             Deng Yi Ou                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP模块私有全局变量的引用说明                   *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件包含了PPP模块对所有私有全局变量的应用说明                  *
 *   其他任何地方不能再出现对私有全局变量的extern引用                   *
 *                                                                      *
 ************************************************************************/

#ifndef      _PPP_VAR_H_
#define      _PPP_VAR_H_


#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

extern PTM_COMPONENT_INFO_S g_stPppCompInfo;
extern VOS_UINT64 g_ullPppLocalL2tpCsi;        /* 本板LAC组件CSI */
extern VOS_UINT64 g_ullPppAuthCsi;              /* AUTH的CSI */
extern VOS_UINT64 g_ullPppFACsi;               /* FA的CSI */
extern VOS_UINT64 g_ullPppDiamAuthCsi;              /* AUTH的CSI */
extern PPP_NEGO_NODE_S  *g_pstPppPDNNegoList;
extern PPP_NEGO_NODE_S  *g_pstPppRPNegoList;

extern VOS_UINT64 g_ullPPPLAP2Csi;               /* LAP2的CSI */

extern VOS_UINT64 g_ullPppA11Csi ;           /* A11的CSI */




extern VOS_UINT32 g_ulPppDBGStatisc[];

extern VOS_UINT32 g_ulPppVsncpGetPCO;  /* 是否获取PCO */

extern VOS_UINT32 g_ulStubDpeNo;
extern UCHAR g_ucStubDmpuId;

extern HTIMER g_ahNegoListTimeoutID[];
/*extern ULONG *g_ulPppFsmStat[5] ;*/ /* 各状态机消息和事件统计 */
extern VOS_UINT32 g_ulPppFsmStat[5][(VOS_UINT32)PPP_EVENT_FSM_BUTT * PPP_STATE_BUTT]; /* 各状态机消息和事件统计 */

extern PPP_DEBUG_INFO_S g_pstPppInnerDebugInfo[] ;
extern PPP_DEBUG_INFO_S g_pstPppErrorDebugInfo[] ;

extern VOS_UINT32 g_ulPppA11NotifyQueID ;/* A11通知PPP消息队列*/
extern VOS_VOID* g_pstPppLAPNotifyQueID  ;/* LAP通知PPP消息队列 */
extern VOS_VOID* g_pstPppL2TPNotifyQueID ;/* PPP通知L2TP消息队列 */
extern VOS_VOID* g_pstL2TPPppNotifyQueID ;/* L2TP通知PPP消息队列 */

/* 地址释放队列 共享内存消息队列*/
extern VOS_VOID* g_pstPppNegoQueID ;        /* 协商报文消息队列 */

extern VOS_UINT32 g_ulAuthPapOnoff;/*控制PAP鉴权*/
extern VOS_UINT32 g_ulAuthChapOnoff;/*控制CHAP鉴权*/

extern VOS_UINT32 g_ulPCompressOnoff;/*控制协议域压缩协商*/
extern VOS_UINT32 g_ulACompressOnoff ;/*控制地址域压缩协商*/
extern VOS_UINT32 g_ulPppEchoRetransmit;
extern VOS_UINT32 g_ulPppEchoTimeout; /* 处理时*1000后表示10秒 */

extern CHAR AuthMsgError[]  ;
extern CHAR AuthMsgSuccess[] ;

extern VOS_UINT32  *g_GTPC_pulPdpRejDueRes;
extern VOS_VOID* g_ulUSMSendLAP2ReqQueID;
extern VOID PPP_Shell_ReceiveDHCPPacket(USM_LAP2_MSG_S* pstMsg);



extern CHAR aucDataGram[];
extern VOS_UINT16 g_usPppVjUserNUm[MAX_DMPU_NUM][MAX_DPE_NUM_PDSN];    /*VJ压缩用户数,用于调试统计*/
extern VOS_UINT16 g_usPppMppcUserNum[MAX_DMPU_NUM][MAX_DPE_NUM_PDSN];  /*Mppc压缩的用户数,用于调试统计*/
extern VOS_UINT32 g_ulMaxDmpuDpeCpuRate ;                 /* 负荷最高DPE的CPU占用率 */
extern VOS_UINT32 g_ulMinDmpuDpeCpuRate ;                 /* 负荷最低DPE的CPU占用率 */
extern VOS_UINT32 g_ulDmpuDpeCpuRate[MAX_DMPU_NUM * MAX_DPE_NUM_PDSN];
extern VOS_UINT32 g_ulDmpuDpeNumber[MAX_DMPU_NUM];

extern VOS_UINT32 g_ulLastSelDmpuDpe ;                    /* 上次选择的DPE */
extern VOS_UINT32 g_ulPppReNegIndex ;                     /* 用于记录当前重协商的用户索引 */
extern VOS_UINT32 g_ulDmpuCpuThreshold;                 /* 子卡CPU占用率门限 */
extern VOS_UINT32 g_ulPppDiamAaaQueID;      /* AUTH消息队列 */
extern VOS_UINT8  g_ucUdpCheckSumFlag ; /*udp checksum 软参*/
extern VOS_UINT32 *g_aulDoStatiscTime;
extern VOS_UINT32 *g_aulNoStatiscTime;

extern LINKTCB_S        g_pstLocalLinkTcb[];

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
extern PPPC_HDLC_STRU   g_astHdlcPool[];
#endif

/* PPP内部可维可测勾包信息存储 */
extern CTTF_PPPC_TRACE_DATA_STRU   g_stPppInterMntnInfo;

/* PPP与CDS交互可维可测勾包信息存储 */
extern CTTF_PPPC_TRACE_DATA_STRU   g_stPppCdsMntnInfo;

/* PPP与RLP交互可维可测勾包信息存储 */
extern CTTF_PPPC_TRACE_DATA_STRU   g_stPppRlpMntnInfo;

/* extern PPPINFO_S        *g_astPppPool; */
extern PPPINFO_S        g_astPppPool[];

/* extern PPPLCPINFO_S     *g_astPppLcpPool ; */
extern PPPLCPINFO_S     g_astPppLcpPool[];

/* extern PPPIPCPINFO_S    *g_astPppIpcpPool; */
extern PPPIPCPINFO_S    g_astPppIpcpPool[];

/* extern PPPPAPINFO_S     *g_astPppPapPool ; */
extern PPPPAPINFO_S     g_astPppPapPool[] ;

/* extern PPPCHAPINFO_S    *g_astPppChapPool; */
extern PPPCHAPINFO_S    g_astPppChapPool[];

/* extern PPP_CCP_INFO_S   *g_astPppCcpPool ; */
extern PPP_CCP_INFO_S   g_astPppCcpPool[] ;

/* extern PPPCONFIGINFO_S  *g_astPppConfifPool; */
extern PPPCONFIGINFO_S  g_astPppConfifPool[];

extern PPP_NEGO_NODE_S  *g_pstPppNegoList;
/* extern PPPIPV6CPINFO_S  *g_astPppIpv6cpPool; */
extern PPPIPV6CPINFO_S  g_astPppIpv6cpPool[];

#if VRP_MODULE_LINK_PPP_EAP == VOS_YES
/* extern PPPC_EAP_INFO_STRU     *g_astPppEapPool; */
extern PPPC_EAP_INFO_STRU     g_astPppEapPool[];

#endif
extern PPPA11_AlarmLink_HEAD_S g_stPppA11AlarmLink;
extern PPP_FAIL_COUNTER g_stPPPFailCounter;
extern VOS_UINT32 ulOneSecondTimer;
extern PPPFSMCALLBACK_S g_stVsncpCallbacks;
extern VOS_UINT32 g_ulPPPTaskId;
#ifdef __PRODUCT_TYPE_PDSN80
extern VOS_UINT32 g_ulPppLicenseQueID;/* License消息队列 */
#endif
/* extern VSNCP_OPTION_DECODE *g_pVsncpOptionDecode; */
extern VSNCP_OPTION_DECODE g_pVsncpOptionDecode[];

extern VSNP_CONIFG_OPTION_FLAG_S g_stVsncpOptionFlag;
/* extern VSNCP_OPTION_ENCODE *g_pVsncpOptionEncode; */
extern VSNCP_OPTION_ENCODE g_pVsncpOptionEncode[];


extern VOS_UINT32 g_ulPppNegoQueID ;     /* 协商报文消息队列 */
extern VOS_UINT32 g_ulPppCompressQueID ;

 /* PPP日志级别 */
extern VOS_UINT32 g_ulPppLogLevelErr;
extern VOS_UINT32 g_ulPppAaaQueID;/* AUTH消息队列 */
extern VOS_UINT32 g_ulPppDhcpQueID;/* DHCP消息队列 */
extern VOS_UINT32 g_ulPppPcrfcQueID;
extern VOS_UINT32 g_ulPppTimeQueID;/* 定时器消息队列 */
extern VOS_UINT32 g_ulPppCcpQueID;       /* 压缩数据消息队列 */ /*WGGSN_B03_L2TP_PPPC_COMP*/
extern VOS_UINT32 g_ulPppGspcQueID;     /* 接收GSPC IPC消息队列 *//* Added by liutao 38563 at 2004-09-22 V800R002 for PPP压缩移植 */
extern LONG g_ulPppL2tpMaxUserNum; /* L2TP最大用户数 */
extern LONG g_ulPppCcpMaxUserNum;
extern LONG g_ulPppVjMaxUserNum;
extern VOS_UINT32 g_ulPPPLapFlowctrl;
extern VOS_UINT32 g_ulPPPA11Flowctrl;
extern VOS_UINT32 g_ulPPPTimerFlowctrl;
extern VOS_UINT32 g_ulPPPAAAFlowctrl;
extern VOS_UINT32 g_ulPPPNegoFlowctrl;
extern VOS_UINT32 g_ulPPPPcrfcFlowCtrl;

extern VOS_UINT32 g_ulPPPTmpTaskFlowCtrl;
extern VOS_UINT32 g_ulPppInnerMsgQueID;     /* added by luofang 临时任务消息队列 */
/* 控制块链表指针 */
/* debug开关使用的变量 */
extern struct tagPppDebugInfo g_stPppDebugInfo ;

/* debug使用的变量和数组 */

extern CHAR *g_cPPP_Debug_Protocol_Name[];
extern CHAR *g_cPPP_Debug_code[];
extern CHAR *g_cPPP_Debug_state[];
extern CHAR *g_cPPP_Debug_event[];
extern CHAR *g_cPPP_Debug_LcpOption[];
extern CHAR *g_cPPP_Debug_IpcpOption[] ;
/*------------- 性能统计使用的全局变量 -------------*/
extern PPPPERFSTATISTIC_S g_stPppPerfStatistic;
extern IPV6PERFSTATISTIC_S g_stIpv6PerfStatistic;
extern VOS_UINT32 g_aulIpv6Cnt[];

/*------------- 内部调试使用的全局变量 -----------------*/
extern IMSI_S g_stPppDebugImsi;        /* 单用户调试IMSI信息*/

/*------------- 备份倒换模块的全局变量 -----------------*/
extern UCHAR g_ucPppBkpFailFlg;            /* 备份过程状态标志,1失败,0成功 */
extern VOS_UINT32 g_ulPppRoutineBkpCurIndex;           /* 当前控制块索引*/
extern VOS_UINT32 g_ulPppRoutineBkpHeadIndex;          /* 头控制块索引*/
extern PPP_CHANGEDINFO_BKP_S*    g_stPppChangedInfoBkp;
extern VOS_UINT32 g_ulPppBackupTID;
extern VOS_UINT32 ulDealedNum;
extern VOS_UINT32 g_ulBackupControl;
extern VOS_UINT16 g_usPppLzs0UserNum;  /*LZS0压缩用户数*/
extern VOS_UINT16 g_usPppLzs1UserNum; /* LZS1压缩用户数 */
extern VOS_UINT8 g_ucPppCcpSwitch;
extern VOS_UINT8 g_ucPppCcpType;
extern VOS_UINT8 g_ucPppVjSwitch;
extern VOS_UINT16 * g_pusPppL2tpCallId;
extern PPP_CFG_INFO_REC_S g_stPppCfgInfo;
extern VOS_UINT32 g_ppp_ulTempLapBatchDelteTaskID2;
extern VOS_UINT32 g_ulLapReportTID;

extern VOS_UINT32 g_ulPppTaskTrace;

extern  struct Command_Group_S PppCommandGroup;
extern VOS_UINT32 g_ulPppDebugSwitch;

/* extern UCHAR *g_ucPppSendPacketHead; */
extern UCHAR g_ucPppSendPacketHead[];

/* extern UCHAR *g_ucPppRcvPacketHead; */
extern UCHAR g_ucPppRcvPacketHead[];




/* 以下用于PPP的软参 */
extern VOS_UINT32 g_ulSoftPara534;
extern VOS_UINT32 g_ulSoftPara562;
extern VOS_UINT32 g_ulSoftPara567;
extern VOS_UINT32 g_ulSoftPara571;
extern VOS_UINT32 g_ulSoftPara577;
extern VOS_UINT32 g_ulSoftPara537;
extern VOS_UINT32 g_ulSoftPara585;
extern VOS_UINT32 g_ulSoftPara586;
extern VOS_UINT32 g_ulSoftPara587;




extern VOS_UINT32 g_ulReNegoTaskId;
extern VOS_UINT32 g_ulPppAAAWritelogFlag;
extern VOS_UINT32 g_ulLap1RebuildingFlag;

extern VOS_UINT32 g_ulMaxVJNum;

extern VOS_UINT32 g_ulSpuId;        /* 本SPU板逻辑板号 */
/*当前spu板类型*/
extern CRM_SPU_BOARD_TYPE_ENUM g_enPppBoardType;

extern VOS_UINT32 g_ulPPPL2tpFlowctrl;

extern UCHAR g_ucPppSendPacketHead[PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER];


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_VAR_H_ */



