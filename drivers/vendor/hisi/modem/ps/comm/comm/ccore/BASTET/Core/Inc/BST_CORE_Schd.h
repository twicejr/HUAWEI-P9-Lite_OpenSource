/******************************************************************************

                  版权所有(C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_CORE_Schd.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年05月04日
  最近修改   :
  功能描述   : 定义任务调度器
  函数列表   :
  修改历史   :
  1.日    期   : 2014年05月13日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_CORE_SCHEDULER_H__
#define __BST_CORE_SCHEDULER_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_CORE_PTask.h"
#include "BST_OS_Timer.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Sync.h"
#include "BST_SRV_AsEvnt.h"

#if(BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_TASK_SYS_BASE_TIMELEN       (( BST_TASK_SYS_TICKS )* \
                                        BST_OS_MS_IN_S*BST_OS_S_IN_MIN )//2 minuts
#define BST_TASK_SYS_RETRY_TIMELEN      (( 5 )*BST_OS_MS_IN_S )         //5 Second

#define BST_TASK_RELATIVE_RATE          ( 10 )

#define BST_TASK_ABSLT_TIME_MS          ( 60000 )
#define BST_TASK_DELAY_TIME_MS          ( 30000 ) /*poor条件下心跳延时时间*/

#define BST_TASK_IsNearEnough(rm,cyc)   ( ((rm) <= \
                                          ((cyc) * BST_TASK_RELATIVE_RATE )/100 )\
                                        &&( (rm)<BST_TASK_ABSLT_TIME_MS ) )

#define BST_TASK_RRC_SEND_TIMER         ( BST_OS_TIMER_PRECISION * 2 )

/* Thread 名字的长度 */
#define BST_BLOCKED_THREAD_LEN          ( 25 )

#define BST_CORE_IS_S2T_CMD(cmd)        ( (cmd)<BST_SRV_T2S_TSK_ATTACH )

#define BST_CORE_INVALID_CYC            ( 0U )

#define BST_CORE_MAX_CYC_ERRNO          ( 2U )

#define BST_CORE_NO_ERR_BIT             ( 0xFFFFU )

#define BST_CORE_IsRuningDetector( ptask )\
     (   BST_SRV_CHbDetector::GetInstance()->IsTask( ptask ) \
     && BST_SRV_CHbDetector::GetInstance()->IsRuning() )

#define BST_CORE_MARK_CYC_BIT(flgs,cyc) \
    if( (cyc) <= BST_SRV_DTC_MAX_LEN )  \
    {                                   \
        (flgs) |= (0x01U<<(cyc));       \
    }

#define BST_CORE_CLR_CYC_BIT(flgs,cyc)  \
    if( (cyc) <= BST_SRV_DTC_MAX_LEN )  \
    {                                   \
        (flgs) &= (~(0x01U<<(cyc)));    \
    }

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
enum BST_SRV_SCHD_EVEN{
    BST_SRV_S2T_EXE_COMAND,     /*schd通知task 执行周期任务*/
    BST_SRV_S2T_ERR_CLOSED,     /*schd通知task socket被异常关闭了*/
    BST_SRV_S2T_CYC_UPDATE,     /*schd通知task 周期被更新*/
    BST_SRV_T2S_TSK_ATTACH,     /*task通知schd 新任务创建并附着*/
    BST_SRV_T2S_TSK_DETACH,     /*task通知schd 任务去附着*/
    BST_SRV_T2S_ACK_RESULT,     /*task通知schd 知会当前任务执行结果*/
    BST_SRV_T2S_RUN_STOPED,     /*task通知schd 任务被停止(仅探测器)*/
    BST_SRV_T2S_RUN_RESUME,     /*task通知schd 任务恢复(仅探测器)*/
    BST_SRV_T2S_DEF_DETCET,     /*task通知schd 定义探测器任务ID*/
    BST_SRV_SCHD_EVEN_BUTT
};
typedef BST_UINT16  BST_SRV_DET_STATE_ENUM_UINT16;

enum BST_APP_SEND_STATE_ENUM{
    /**BST_APP_SEND_STATE_FIRST
    该状态由Task自己设置.当任务首次加入到统一触发序列里面，第一次发送为该状态。
    因为未必是整数周期，因此成功/失败结果均不ACK到SCHD。
    */
    BST_APP_SEND_STATE_FIRST,

    /**BST_APP_SEND_STATE_BLOCK
    表明该触发在BLOCK结束后产生，由于超过了预期时间，因此成功则计入统计，失败不计入统计。
    */
    BST_APP_SEND_STATE_BLOCK,

    /**BST_APP_SEND_STATE_NORM
    正常收发，在整数周期处规律性触发。当应用成功收到一次心跳回应后进入此状态
    */
    BST_APP_SEND_STATE_NORM,

    BST_APP_SEND_STATE_BUTT
};
typedef BST_UINT8   BST_APP_SEND_STATE_ENUM_UNIT8;

enum BST_CORE_SCHD_ACK_ENUM{
    BST_CORE_SCHD_ACK_SUC,
    BST_CORE_SCHD_ACK_ERR,
    BST_CORE_SCHD_ACK_BUTT
};
typedef BST_UINT8   BST_CORE_SCHD_ACK_ENUM_UINT8;
/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
typedef struct
{
    NODE                                node;
    BST_CORE_CPTask                    *pcTask;         /* 任务对象 */
    BST_UINT32                          ulLastSendTime; /* 上次心跳发送时间（MS） */
    BST_APP_SEND_STATE_ENUM_UNIT8       enSendState;    /* 当前发送状态 */
    BST_CORE_SCHD_ACK_ENUM_UINT8        enLastErrType;  /* 上次运行失败原因 */
    BST_UINT16                          usSelfCyc;      /* 任务自运行周期，当按照系统探测TICKS及
                                                           设置周期CYC连续心跳不成功后，改为自运行周期，最小1*/
}BST_CORE_PTASK_NODE_STRU;

class BST_CTaskSchdler
    : BST_SRV_CAsRcver, BST_OS_CTimerCb
{
BST_PUBLIC:
    BST_VOID            Attach( BST_CORE_CPTask    *pC_PTask );
    BST_VOID            Detach( BST_CORE_CPTask    *pC_PTask );
    BST_VOID            Suspend( BST_VOID );
    static              BST_CTaskSchdler *GetInstance( BST_VOID );
    static              BST_CORE_CPTask  *GetPtaskIns( BST_UINT16 usProcId, BST_UINT16 usTaskId );
    BST_VOID            AckSendResult   ( BST_CORE_CPTask *pcPTask, BST_UINT16 ucResult );
    BST_VOID            TaskStarted     ( BST_CORE_CPTask *pcPTask );
    BST_VOID            TaskStoped      ( BST_CORE_CPTask *pcPTask );
    BST_VOID            DefineDetector  ( BST_CORE_CPTask *pcPTask );
    BST_VOID            onDetFinished   ( BST_UINT8 ucLongestCyc );

BST_PRIVATE:
                        BST_CTaskSchdler( BST_VOID );

    virtual            ~BST_CTaskSchdler( BST_VOID );

    BST_VOID            TimerExpired(
        BST_OS_TIMERID_T    ulId,
        BST_VOID* pvPara );

    BST_VOID            ScheduleTask( BST_CORE_PTASK_NODE_STRU *pTaskItem );

    BST_UINT32          NearRrcTrig(
        BST_UINT32 const        ulSysTimerRemainMs );

    BST_VOID            AsEventCallback(
        BST_AS_EVT_ENUM_UINT32  enEvent,
        BST_UINT32              ulLength,
        BST_VOID               *pvData );

    BST_VOID            LinkStateChgProc(
        BST_AS_NET_RANK_ENUM_UINT32 enNetRank );

    BST_CORE_PTASK_NODE_STRU* GetTaskItem( BST_CORE_CPTask *pcPTask );

    BST_UINT16          GetErrorCycle(
        const BST_UINT16    usErrorMsg );

    BST_UINT16          GetTaskCycle(
        BST_CORE_PTASK_NODE_STRU *pstTaskItem );

    BST_VOID            ProcAckSuc(
        BST_CORE_PTASK_NODE_STRU *pstTaskItem );

    BST_VOID            ProcAckErr(
        BST_CORE_PTASK_NODE_STRU *pstTaskItem );

    BST_VOID            ProcFinish( BST_VOID );
    BST_VOID            ScheduleBlockedTask( BST_VOID );
    BST_AS_NET_RANK_ENUM_UINT32     m_enLinkStaRank;
    BST_OS_TIMERID_T                m_ulTimerId;
    BST_OS_TIMERID_T                m_ulDelayTimerId;
    BST_UINT16                      m_usSysTickMax;         /* 按照系统心跳周期最大公倍数：1*2*3*4... */
    BST_UINT16                      m_usSysTickCnt;         /* 原 m_ulSystemTick，在m_ulSysTickMax环回 */
    BST_UINT16                      m_usSendingCnt;         /* 记录本轮心跳调度，共发送了多少个心跳数据*/
    BST_UINT16                      m_usCalledBitRecord;    /* 记录本轮心跳调度，有哪几种周期被调度 0001 0110表示：周期为1,2,4倍Tick的任务被调度了 */
    BST_UINT32                      m_ulRrcState;
};

/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if(BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
