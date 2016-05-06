/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                                ppp_core_hdr.h
*
*  Project Code: VR7C03
*   Module Name: ppp  
*  Date Created: 2009-02-28
*        Author: L00105073/Z00104483
*   Description: ppp体检报告
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-28   L00105073/Z00104483     Create
*
*******************************************************************************/

#ifndef _PPP_CORE_HDR_H_
#define _PPP_CORE_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif
/* PPP接口体检报告数据结构 */

/* PPP统计体检报告 */
typedef struct tagPPP_HEALTH_STATISTIC
{
    ULONG ulIfIndex;
    PPPSTATISTIC_S stPPPStatistic;
} PPP_HEALTH_STATISTIC_S;

/* PPP统计体检报告 */
typedef struct tagPPP_HEALTH_STATUSINFO
{
    ULONG ulIfIndex;
    ULONG ulPhase;
    ULONG ulMpChannelType;
}PPP_HEALTH_STATUSINFO_S;

/* ppp子协议信息体检报告 */
typedef struct tagPPP_HEALTH_SONPROTOCOL_INFO
{
    ULONG   ulIfIndex;
    ULONG   ulState;               /* 协议状态 */
    ULONG   ulDownReason;          /* 记录控制流(down或close事件)导致的PPP协议down原因 */
}PPP_HEALTH_SONPROTOCOL_INFO_S;

/* ppp子协议临终遗言信息 */
typedef struct tagPPP_LASTWORD_STATUS
{
    ULONG   ulIfIndex;          /* 接口索引 */
    UCHAR   ucPppPhase;         /* PPP的协商状态 */
    UCHAR   ucLcpState;         /* LCP的协商状态 */    
    UCHAR   ucLcpDownReason;    /* LCP DOWN 的原因 */      
    UCHAR   ucIpcpState;        /* IPCP的协商状态 */       
    UCHAR   ucIpcpDownReason;   /* IPCP DOWN 的原因 */  
    UCHAR   ucIp6cpState;        /* IP6CP的协商状态 */       
    UCHAR   ucIp6cpDownReason;   /* IP6CP DOWN 的原因 */       
    UCHAR   ucPPPMuxcpState;     /* PPPMuxCP的协商状态 */       
    UCHAR   ucPPPMuxcpDownReason;/* PPPMuxCP DOWN 的原因 */       
    UCHAR   ucRev[3];
}PPP_LASTWORD_STATUS_S;

extern VOID PPP_Health_BatchCheckup(VOID);
extern ULONG PPP_Health_StatisticCheckup(VOID);
extern ULONG PPP_Health_StatusInfoCheckup(VOID);
extern ULONG PPP_Health_LcpInfoCheckup(VOID);
extern ULONG PPP_Health_IpcpInfoCheckup(VOID);
extern ULONG PPP_Health_Ip6cpInfoCheckup(VOID);
extern ULONG PPP_Health_PPPMuxcpInfoCheckup(VOID);
extern ULONG PPP_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
extern ULONG PPP_LastWord_StatisticCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);

#ifdef  __cplusplus
}
#endif
#endif

