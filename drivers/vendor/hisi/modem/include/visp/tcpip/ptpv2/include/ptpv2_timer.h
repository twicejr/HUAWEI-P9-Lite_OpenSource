/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_timer.h
*
*  Project Code:
*   Module Name: PTPV2 timer
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

#ifndef _PTPV2_TIMER_h_
#define _PTPV2_TIMER_h_

#ifdef __cplusplus
extern "C" {
#endif

/*PTPV2基定时器的时长，70ms，该取值对性能有直接影响*/
#define PTPV2_BASE_TIMER_LEN      70

#define PTPV2_WANRING_TIMER_INTERVAL   30000   /*30秒选不到源上报告警*/

/*逻辑定时器的最大数量*/
#define PTPV2_LOGIC_TIMER_MAX_NUM    256

/*逻辑定时器处理函数指针*/
typedef ULONG (*PTPV2_FUNC_LOGIC_TIMER)(VOID* pArg);

/*PTP逻辑定时器项数据结构*/
typedef struct tagPTPV2_LOGIC_TIMER_S
{
    DLL_NODE_S stDllNode;           /*用于结点的存储*/
    ULONG ulTimerId;                /*逻辑定时器ID*/
    ULONG ulPeriod;                 /*定时器周期*/
    ULONG ulEndTimeHigh;            /*Ann发送定时器的超时时间的HIGH位*/
    ULONG ulEndTimeLow;             /*Ann发送定时器的超时时间的LOW位*/
    VOID* pArg;                     /*回调函数的参数*/
    PTPV2_FUNC_LOGIC_TIMER pfFunc;  /*逻辑定时器处理函数*/
    ULONG ulDelFlag;                /*定时器删除标记，PTPV2_TIMER_DELETE为需要删除，PTPV2_TIMER_NOT_DELETE为无需删除*/
} PTPV2_LOGIC_TIMER_S;

/*******************************************************************************
*    Func Name: PTPV2_CreateLogicTimer
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: 创建PTPV2 逻辑定时器
*        Input: ULONG ulPeriod:
*               PTPV2_FUNC_LOGIC_TIMER pfFunc:
*               VOID* pArg:
*               ULONG* pulTimerId:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CreateLogicTimer(ULONG ulPeriod, PTPV2_FUNC_LOGIC_TIMER pfFunc, VOID* pArg, ULONG* pulTimerId);

ULONG PTPV2_ResetLogicTimer(ULONG ulTimerId);

/*******************************************************************************
*    Func Name: PTPV2_DeleteLogicTimer
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description: 删除PTP 逻辑定时器
*        Input: ULONG ulTimerId:定时器Id
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_DeleteLogicTimer(ULONG ulTimerId);

/*******************************************************************************
*    Func Name: PTPV2_BaseTimerProc
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description: PTPV2的基定时器
*        Input: VOID* pArg:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_BaseTimerProc(VOID* pArg);

ULONG PTPV2_AnnSndTimerOut(VOID* pArg);

/*******************************************************************************
*    Func Name: PTPV2_AnnRcvTimerOut
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:  announce接收定时器处理函数
*        Input: VOID* pArg:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_AnnRcvTimerOut(VOID* pArg);

ULONG PTPV2_CreateWarningTimer();

ULONG PTPV2_DeleteWarningTimer();

VOID PTPV2_TimerPrint(PTPV2_LOGIC_TIMER_S *pstLogicTimer);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _PTPV2_TIMER_h_ */

