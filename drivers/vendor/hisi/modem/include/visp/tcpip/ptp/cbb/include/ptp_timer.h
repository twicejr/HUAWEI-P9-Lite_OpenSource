/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_timer.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP PKT
*  Date Created: 2008-06-02
*        Author: lishenchuan
*   Description: PTP PKT模块函数头文件声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-06-02      Lishenchuan       Create
*
*******************************************************************************/

#ifndef _PTP_TIMER_H_
#define _PTP_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif


/*Mod By t00110672/z00146309  10-1-11,支持路由器关于实现最新草案的需求 */
/*PTP基定时器的时长，65ms,暂时修改，后续需要根据在产品测试性能结果来定*/
#define PTP_BASE_TIMER_LEN          70

/*PTP逻辑定时器规格数*/
#define PTP_LOGIC_TIMER_LEN         15000


/*逻辑定时器处理函数指针*/
typedef ULONG (*PTP_FUNC_LOGIC_TIMER)(VOID *pArg);

/*PTP逻辑定时器项数据结构*/
typedef struct tagPTP_LOGIC_TIMER_S
{
    UINTPTR ulTimerId;             /*逻辑定时器ID*/
    ULONG ulPeriod;                /*定时器周期*/
    ULONG ulEndTimeHigh;           /*Ann发送定时器的超时时间的HIGH位*/
    ULONG ulEndTimeLow;        /*Ann发送定时器的超时时间的LOW位*/
    VOID  *pArg;                   /*回调函数的参数*/
    PTP_FUNC_LOGIC_TIMER pfFunc;   /*逻辑定时器处理函数*/
    struct tagPTP_LOGIC_TIMER_S *pstNext; /*定时器链表按超时的顺序排序，时间从小到大*/
    struct tagPTP_LOGIC_TIMER_S *pstPrev;
}PTP_LOGIC_TIMER_S;


/*PTP逻辑定时器头节点的数据结构，头节点直接采用，存储有效数据*/
/*Begin mod by heyijun KF37287 for DTS2011031604476 修改定时器头结点为结构体形式*/
typedef struct tagPTP_LOGIC_TIMER_H_S
{
    ULONG ulTimerNumber;
    PTP_LOGIC_TIMER_S stLogicTimer;
}PTP_LOGIC_TIMER_H_S;

ULONG PTP_CreateLogicTimer(ULONG ulPeriod,PTP_FUNC_LOGIC_TIMER pfFunc, VOID* pArg,ULONG* pulTimerId);
ULONG PTP_DeleteLogicTimer(ULONG ulTimerId);
ULONG PTP_ResetLogicTimer(ULONG ulTimerId);
VOID PTP_LogicTimerProc();

ULONG PTP_ProcAnnReqQueryTimerOut(VOID *pArg);
ULONG PTP_ProcAnnCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcDelayRespQueryTimerOut(VOID *pArg);
ULONG PTP_ProcSyncReqQueryTimerOut(VOID *pArg);
ULONG PTP_ProcDelayRespCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcSyncCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcMDelayRespCancelQueryTimerOut(VOID *pArg);
VOID PTP_BaseTimerProc(VOID *pArg);
ULONG PTP_ProcAnnSndTimerOut(VOID *pArg);
ULONG PTP_DelAllTimerRes(VOID);
ULONG PTP_DelUniMasterTabTimerRes(VOID);
ULONG PTP_DelUniMasterNodeTimerRes(PTP_UNI_MASTER_NODE_S *pstUniMaster);
ULONG PTP_DelUniSlaveTabTimerRes(PTP_PORT_S *pstPtpPort);
ULONG PTP_DelUniSlaveNodeTimerRes(PTP_UNI_SLAVE_NODE_S *pstUniSlave);
ULONG PTP_ProcAnnMultiRecvTimerOut(VOID * pArg);
ULONG PTP_ProcAnnRecvTimerOut(VOID *pArg);
ULONG PTP_ProcMSyncCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcMAnnCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcLiveSndTimerOut(VOID *pArg);
ULONG PTP_ProcLiveRcvTimerOut(VOID *pArg);
ULONG PTP_SlaveSyncDurationTimerOut(VOID *pArg);
ULONG PTP_SlaveDelayDurationTimerOut(VOID *pArg);

ULONG PTP_AcceptMasterDetect(VOID *pArg);

/*Add By t00110672  10-1-8支持路由器关于实现最新草案的需求 */
ULONG PTP_ProcMulticastAnnSndTimerOut(VOID *pArg);
ULONG PTP_ProcUnicastAnnSndTimerOut(VOID *pArg);

ULONG PTP_UpdateTimerValue(ULONG ulTimerId, ULONG ulValue);


ULONG PTP_SlaveAnnDurationTimerOut(VOID *pArg);

extern ULONG PTP_DelUniMasterCancelTimer(PTP_UNI_MASTER_NODE_S *pstUniMaster);

extern ULONG PTP_MasterSyncDurationTimerOut(VOID *pArg);
extern ULONG PTP_MasterDleayDurationTimerOut(VOID *pArg);

/* Add by chixiang 198096 for DTS2011122301481 at 2011-12-22 定时器日志增加时间戳打印*/
VOID PTP_PrintDebug(ULONG ulDebugType, CHAR *pcDebugMsg);

/*Added by guo00178934, 删除单播Master端Annc相关定时器, 2012/1/12   问题单号:DTS2012011005305  */
/*******************************************************************************
*    Func Name: PTP_DelUniMasterAnnTimer
* Date Created: 2012-01-12
*       Author: guo00178934
*  Description: 删除单播Master端Annc相关定时器
*        Input: PTP_UNI_MASTER_NODE_S *pstUniMaster:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-12   guo00178934             Create
*
*******************************************************************************/
ULONG PTP_DelUniMasterAnncTimer(PTP_UNI_MASTER_NODE_S *pstUniMaster);
/* End of Added by guo00178934, 2012/1/12   问题单号:DTS2012011005305  */

#ifdef __cplusplus
}
#endif

#endif
