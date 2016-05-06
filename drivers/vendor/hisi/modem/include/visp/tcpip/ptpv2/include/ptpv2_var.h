/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_var.h
*
*  Project Code:
*   Module Name: PTPV2 var
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_VAR_H_
#define _PTPV2_VAR_H_

#ifdef __cplusplus
extern "C" {
#endif

/*控制只进行一次初始化*/
extern ULONG g_ulPtpV2InitFlag;

/*定义PTP模块的信号量全局变量*/
extern ULONG g_ulPTPV2Sem;

/*PTP 模式: OC 或者BC、目前不支持TC*/
extern ULONG g_ulPtpV2ClockType;

/*PTPV2定时器队列ID*/
extern ULONG g_ulPtpV2TimerQId;

/*PTPV2报文队列的ID*/
extern ULONG g_ulPtpV2PktQId;

/*PTPV2任务ID*/
extern ULONG g_ulPtpV2TaskId;

/*PTP基定时器ID，VOS定时器,100ms*/
extern ULONG g_ulPtpV2BaseTimerId;

#define PTPV2_INVALID_SOCKEID  (-1)

/*PTP报文接收的事件ID，外围Shell可根据自身的情况进行适配*/
extern ULONG g_ulPtpV2PktRcvEventId;


extern AVL3_TREE_INFO_S g_PtpV2TreeInfo;


extern AVL3_TREE_S g_PtpV2Tree; /*全局PTP 端口树结构*/


extern DLL_S  g_GlobalForeignMasterList; /*全局的备用master*/


extern PTPV2_GLOBAL_INFO_S  *g_pstPtpGlobalInfo;/*默认按1588选源*/

extern PTPV2_PORT_MANAGE_S *g_pstPortManageInfo;

extern DLL_S  g_PtpV2TimerList; /*全局的定时器链表*/

extern const UCHAR g_szMacPTPV2_E2E[PTPV2_MACADDRLEN];
extern const UCHAR g_szMacPTPV2_P2P[PTPV2_MACADDRLEN];

extern PTPV2_PORT_SUB_INFO_S  *g_pstOCPortSubInfo;

/* 处理PTP报文并释放 */
extern ULONG (*g_pfETH_PTPV2_HOOK)(MBUF_S*);

/*用于PTP卸载的同步信号量*/
extern ULONG g_ulSynsemId;

extern TCPIP_PTP_PPI_HOOK_FUNC g_pfPtpV2PpiHookFunc;

/*当前选中的时钟源*/
extern PTPV2_FOREIGN_MASTER_S *g_pstBmcEbest; 

extern ULONG g_ulPtpCompVersion;

/* 告警消息输出函数指针类型定义 */
extern TCPIP_PTP_WARN_OUTPUT_FUNC  g_pfPtpV2WarnOutput;

/*全局报文捕获函数指针*/
extern TCPIP_PTP_CAPTURE_PACKET_FUNC g_pfPtpV2CapturePktFunc;

/*全局报文统计*/
extern TCPIP_PTP_PKT_STAT_S g_stGlobalPtpV2PktStat;

/*PTP选到时钟源的标记*/
extern UCHAR g_ucPtpGotTimeSourceFlag;

/* 30秒选不到源的一个告警定时器*/
extern ULONG g_ulPtpWarningTimerId;

/*调试开关,用于维测 , 默认全部开关关闭*/
extern ULONG g_ulPtpV2GlobalDbgSwitch;

/*虚拟D0 的master*/
extern PTPV2_FOREIGN_MASTER_S  *g_pstVirtualD0;

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTPV2_VAR_h_   */
