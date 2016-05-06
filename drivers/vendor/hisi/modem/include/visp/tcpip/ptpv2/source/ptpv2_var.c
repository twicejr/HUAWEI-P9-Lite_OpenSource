/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_var.c
*
*  Project Code:
*   Module Name: PTPV2 var
*  Date Created: 2014-03-03
*        Author: luoagwoei
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03    luoagwoei               Create
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"

/*控制只进行一次初始化*/
ULONG g_ulPtpV2InitFlag = PTPV2_NO;

/*定义PTP模块的信号量全局变量*/
ULONG g_ulPTPV2Sem = 0;

/*PTP 模式: OC 或者BC、目前不支持TC*/
ULONG g_ulPtpV2ClockType = PTPV2_CLOCK_TYPE_NULL;

/*PTPV2定时器队列ID*/
ULONG g_ulPtpV2TimerQId = 0;

/*PTPV2报文队列的ID*/
ULONG g_ulPtpV2PktQId = 0;

/*PTPV2任务ID*/
ULONG g_ulPtpV2TaskId = 0;

/*PTP基定时器ID，VOS定时器,100ms*/
ULONG g_ulPtpV2BaseTimerId = 0;

/*PTP报文接收的事件ID，外围Shell可根据自身的情况进行适配*/
ULONG g_ulPtpV2PktRcvEventId = SE_ASYNC | PTPV2_IEEE8023MSG_EVENT_ID;


AVL3_TREE_INFO_S g_PtpV2TreeInfo =
{
    PTPV2_Port_Tree_Compare,
    0,
    PTPV2_Tree_offset(PTPV2_PORT_S, stPtpPortNode)
};


AVL3_TREE_S g_PtpV2Tree =
{
    NULL,
    NULL,
    NULL
}; /*全局PTP 端口树结构*/


DLL_S  g_GlobalForeignMasterList; /*全局的备用master*/

TCPIP_PTP_PPI_HOOK_FUNC g_pfPtpV2PpiHookFunc = NULL;

PTPV2_GLOBAL_INFO_S*  g_pstPtpGlobalInfo = NULL;/*默认按1588选源*/

PTPV2_PORT_MANAGE_S* g_pstPortManageInfo = NULL;

/*全局的定时器链表*/
DLL_S  g_PtpV2TimerList; 

const UCHAR g_szMacPTPV2_E2E[PTPV2_MACADDRLEN] = {0x01, 0x1B, 0x19, 0x00, 0x00, 0x00};
const UCHAR g_szMacPTPV2_P2P[PTPV2_MACADDRLEN] = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E};

PTPV2_PORT_SUB_INFO_S*  g_pstOCPortSubInfo = NULL;

/*用于PTP卸载的同步信号量*/
ULONG g_ulSynsemId = 0;

/*当前选中的时钟源*/
PTPV2_FOREIGN_MASTER_S *g_pstBmcEbest  = NULL; 

/*虚拟D0 的master*/
PTPV2_FOREIGN_MASTER_S  *g_pstVirtualD0 = NULL;

/*PTP选到时钟源的标记*/
UCHAR g_ucPtpGotTimeSourceFlag = PTPV2_NO; 

/* 30秒选不到源的一个告警定时器*/
ULONG g_ulPtpWarningTimerId = NULL;

/* 告警消息输出函数指针类型定义 */
TCPIP_PTP_WARN_OUTPUT_FUNC g_pfPtpV2WarnOutput = NULL;

/*全局报文捕获函数指针*/
TCPIP_PTP_CAPTURE_PACKET_FUNC g_pfPtpV2CapturePktFunc = NULL;

/*全局报文统计*/
TCPIP_PTP_PKT_STAT_S g_stGlobalPtpV2PktStat = {0};

/*调试开关,用于维测 , 默认全部开关关闭*/
ULONG g_ulPtpV2GlobalDbgSwitch = 0;

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
