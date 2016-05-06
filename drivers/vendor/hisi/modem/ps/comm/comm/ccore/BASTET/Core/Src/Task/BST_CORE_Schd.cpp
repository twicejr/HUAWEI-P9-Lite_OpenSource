/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_CORE_Schd.cpp
  版 本 号   : V1.1
  作    者   : d00173029
  生成日期   : 2014年6月10日
  最近修改   :
  功能描述   : 实现周期性任务调度器
  函数列表   :

  修改历史   :
  1.日    期   : 2014年06月10日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_CORE_Schd.h"
#include "BST_OS_Thread.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_TaskMng.h"
#include "BST_SRV_Event.h"
#include "BST_DRV_LinkSta.h"
#include "BST_DSPP_Define.h"
#include "BST_SRV_HbDetector.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_CORE_SCHD_CPP
/*lint +e767*/
/*****************************************************************************
  2 函数声明
*****************************************************************************/

/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/
LIST        g_stPTaskList;
BST_UINT8   g_aucCycErrCnt[ BST_SRV_DTC_MAX_LEN ];
/******************************************************************************
   6 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : Attach
 功能描述  : 将任务附着到任务链表中并开启基础定时器
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -e429*/
BST_VOID BST_CTaskSchdler::Attach ( BST_CORE_CPTask *pC_PTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_UINT32                  ulSysTickMs;

    if ( !BST_OS_IsTimerValid (m_ulTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::Attach m_ulTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }
    if ( BST_NULL_PTR == pC_PTask )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Attach pC_PTask=NULL" );
        return;
    }
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if( pstPtaskNode->pcTask == pC_PTask )
        {
            return;
        }
    }
    /*
     * 申请链表节点资源，用于存储任务
     */
    pstPtaskNode                = ( BST_CORE_PTASK_NODE_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF( BST_CORE_PTASK_NODE_STRU ) );
    if( BST_NULL_PTR == pstPtaskNode )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Attach pstPtaskNode=NULL" );
        return;
    }
    /*
     * 初始化任务数据，添加如任务列表
     */
    pC_PTask->m_ulSuspCounter   = 0;
    pstPtaskNode->pcTask        = pC_PTask;
    pstPtaskNode->ulLastSendTime= 0;
    pstPtaskNode->enSendState   = BST_APP_SEND_STATE_FIRST;   
    pstPtaskNode->enLastErrType = BST_CORE_SCHD_ACK_SUC; 
    pstPtaskNode->usSelfCyc     = BST_CORE_INVALID_CYC;     

    lstAdd( &g_stPTaskList, (NODE *)pstPtaskNode );
    /*
     * 如果此时系统TICK定时已经关闭，且PS域服务状态正常，那么需要再次启动定时
     */
    if( BST_TRUE == BST_OS_TimerIsStop( m_ulTimerId ) )
    {
        m_usSysTickCnt          = 0;
        ulSysTickMs             = BST_SRV_CHbDetector::GetInstance()->GetCurrentTick();
        BST_OS_TimerStart ( m_ulTimerId, ulSysTickMs );
        BST_DBG_LOG1( "BST_CTaskSchdler::Attach Start Scheduler Timer:%u",
                      ulSysTickMs );
    }
}
/*lint +e429*/
/*****************************************************************************
 函 数 名  : Detach
 功能描述  : 将任务从任务链表中删除，并检查任务链表，链表为空时，停止基础定时器
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -e438*/
BST_VOID BST_CTaskSchdler::Detach ( BST_CORE_CPTask *pC_PTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( !BST_OS_IsTimerValid (m_ulTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::Detach m_ulTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }
    if ( BST_NULL_PTR == pC_PTask )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Detach pC_PTask=NULL" );
        return;
    }
    /*
     * 遍历列表，找到pctask相符的任务，从链表删除，释放资源
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if( pstPtaskNode->pcTask != pC_PTask )
        {
            continue;
        }
        lstDelete( &g_stPTaskList, (NODE *)pstPtaskNode );
        if( BST_SRV_CHbDetector::GetInstance()->IsTask( pstPtaskNode->pcTask ) )
        {
            BST_SRV_CHbDetector::GetInstance()->ClrTask();
        }
        BST_OS_FREE( pstPtaskNode );
        break;
    }
    /*
     * 注销后，如果认为列表为空，则直接关闭定时器，不进行任何调度
     */
    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        BST_DBG_LOG( "BST_CTaskSchdler::Detach Stop Scheduler Timer" );
        BST_OS_TimerStop ( m_ulTimerId );
        BST_OS_TimerStop ( m_ulDelayTimerId );
    }
}
/*lint +e438*/
/*****************************************************************************
 函 数 名  : Suspend
 功能描述  : 将任务挂起
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::Suspend ( BST_VOID )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Suspend g_stPTaskList count=0" );
        return;
    }
    /*
     * 遍历任务表，找到相关任务对齐进行挂起
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        if ( BST_TASK_STATE_START == pstPtaskNode->pcTask->GetState () )
        {
            pstPtaskNode->pcTask->Suspend();
        }
    }
}

/*****************************************************************************
 函 数 名  : GetInstance
 功能描述  : 获取任务调度器的实例
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回任务调度器实例指针
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_CTaskSchdler* BST_CTaskSchdler::GetInstance ( BST_VOID )
{
    static BST_CTaskSchdler    *pTaskScheduler = BST_NULL_PTR;

    if ( BST_NULL_PTR == pTaskScheduler )
    {
        pTaskScheduler          = new BST_CTaskSchdler;
    }
    return pTaskScheduler;
}

/*****************************************************************************
 函 数 名  : BST_CTaskSchdler
 功能描述  : BST_CTaskSchdler类构造函数,创建基础定时器和应用线程以及初始化相关变量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_CTaskSchdler::BST_CTaskSchdler ( BST_VOID ) 
    : BST_SRV_CAsRcver( BST_SRV_GetSysMsgHandle() )
{
    BST_UINT16              usMaxCnt;
    BST_DRV_STRU           *pstLsDriver;

    m_ulTimerId             = BST_OS_TimerCreateCpp ( this,
                                                      BST_NULL_PTR,
                                                      BST_SRV_GetSysMsgHandle() );
    m_ulDelayTimerId        = BST_OS_TimerCreateCpp ( this,
                                                      BST_NULL_PTR,
                                                      BST_SRV_GetSysMsgHandle() );
    m_usSysTickCnt          = 0;
    
    m_usSysTickMax          = 1;
    usMaxCnt                = BST_SRV_DTC_MAX_LEN;
    /**
     * 计算可能出现周期的最大公倍数，作为tick计数循环的最大点
     */
    for(;;)
    {
        m_usSysTickMax     *= usMaxCnt;
        usMaxCnt--;
        if( usMaxCnt <= 1)
        {
            break;
        }
    }
    for( usMaxCnt = 0; usMaxCnt < BST_SRV_DTC_MAX_LEN; usMaxCnt++ )
    {
        g_aucCycErrCnt[usMaxCnt] = 0;
    }
    m_usSendingCnt          = 0;
    m_usCalledBitRecord     = 0;

    pstLsDriver             = BST_DRV_LsGetDvcHandle();
    if( BST_NULL_PTR != pstLsDriver->pfRead )
    {
        pstLsDriver->pfRead( BST_OS_SIZEOF(m_enLinkStaRank), (BST_UINT8 *)&m_enLinkStaRank );
    }
    else
    {
        m_enLinkStaRank     = BST_AS_NET_RANK_MIDDLE;
    }

    BST_DBG_LOG1("BST_CTaskSchdler:%d",m_enLinkStaRank);

    lstInit( &g_stPTaskList );
    RegAsNotice( BST_AS_EVT_L3_RRC_STATE );
    RegAsNotice( BST_AS_EVT_L3_NET_RANK );
}

/*****************************************************************************
 函 数 名  : ~BST_CTaskSchdler
 功能描述  : BST_CTaskSchdler类的析构函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_CTaskSchdler::~BST_CTaskSchdler ( BST_VOID )
{
    if ( BST_OS_IsTimerValid( m_ulTimerId ) )
    {
        BST_OS_TimerRemove( m_ulTimerId );
        m_ulTimerId                     = BST_OS_INVALID_TIMER_ID;
    }
    if ( BST_OS_IsTimerValid( m_ulDelayTimerId ) )
    {
        BST_OS_TimerRemove( m_ulDelayTimerId );
        m_ulDelayTimerId                = BST_OS_INVALID_TIMER_ID;
    }
}

/*****************************************************************************
 函 数 名  : TimerExpired
 功能描述  : 基础定时器超时回调函数
 输入参数  : ulId: 定时器ID类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::TimerExpired(
    BST_OS_TIMERID_T    ulId,
    BST_VOID           *pvPara)
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNodeNext;
    BST_UINT32                  ulSysTickMs;

    if ( !BST_OS_IsTimerValid (m_ulTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::TimerExpired m_ulTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }
    if ( !BST_OS_IsTimerValid (m_ulDelayTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::TimerExpired m_ulDelayTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }

    if ( ulId == m_ulDelayTimerId )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::delay TimerExpired m_enLinkStaRank:%d",m_enLinkStaRank );
        if( BST_AS_NET_RANK_INVALID != m_enLinkStaRank )
        {
            ScheduleBlockedTask();
        }
        return;
    }

    if ( ulId != m_ulTimerId )
    {
        BST_RLS_LOG2( "BST_CTaskSchdler::TimerExpired ulId=%u,m_ulTimerId=%u",
                      ulId, m_ulTimerId );
        return;
    }
    /*
     * 更新系统TICK值
     */
    m_usSysTickCnt++;
    m_usCalledBitRecord         = 0;
    m_usSendingCnt              = 0;

    BST_DBG_LOG1 ( "BST_CTaskSchdler::TimerExpired Scheduler TimeOut, Tick=%d ",
                   m_usSysTickCnt );

    if( m_usSysTickCnt >= m_usSysTickMax )
    {
        /*
         * 超过最大值以后环回，避免计数溢出
         */
        m_usSysTickCnt         = 0;
    }

    /*
     * 遍历任务列表，获取任务并进行相应调度
     */
    for ( pstPtaskNode = ( BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = pstPtaskNodeNext )
    {
        pstPtaskNodeNext    = ( BST_CORE_PTASK_NODE_STRU *)
                              lstNext((NODE *)pstPtaskNode);
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        /*
         * 如果任务不为空，则根据状态进行调度
         */
        ScheduleTask( pstPtaskNode );
    }
    /*
     * 再次启动系统TICK定时器
     */
    ulSysTickMs             = BST_SRV_CHbDetector::GetInstance()->GetCurrentTick();
    BST_OS_TimerStart ( m_ulTimerId, ulSysTickMs );
}

/*****************************************************************************
 函 数 名  : SelectPtaskIns
 功能描述  : 获取任务对象
 输入参数  : BST_UINT16 usProcId,   任务类型ID
             BST_UINT16 usTaskId,   任务编号ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_CORE_CPTask* BST_CTaskSchdler::GetPtaskIns( BST_UINT16 usProcId, BST_UINT16 usTaskId )
{
    BST_CORE_CPTask            *pC_PTask;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        return BST_NULL_PTR;
    }
    pC_PTask                    = BST_NULL_PTR;
    /*
     * 遍历任务表，找到相关任务运行
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }

        if( ( pstPtaskNode->pcTask->m_usProcId == usProcId )
          &&( pstPtaskNode->pcTask->m_usTaskId == usTaskId ) )
        {
            pC_PTask            = pstPtaskNode->pcTask;
            break;
        }
    }
    return pC_PTask;
}

/*****************************************************************************
 函 数 名  : ScheduleTask
 功能描述  : 任务调度函数
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID    BST_CTaskSchdler::ScheduleTask( BST_CORE_PTASK_NODE_STRU *pTaskItem )
{
    BST_SRV_CTaskMng                   *pcTaskManager;
    BST_CORE_CPTask                    *pTask;
    BST_TASK_STATE_ENUM_UINT8           enTaskState;
    BST_UINT16                          usRealCyc;

    pcTaskManager                       = BST_SRV_CTaskMng::GetInstance ();
    BST_ASSERT_NULL( pcTaskManager );

    /*
     * 入口检查
     */
    BST_ASSERT_NULL( pTaskItem );
    pTask                               = pTaskItem->pcTask;

    BST_ASSERT_NULL( pTask );

    if( BST_CORE_IsRuningDetector( pTask ) )
    {
        BST_RLS_LOG2( "BST_CTaskSchdler::ScheduleTask ProcId=%u ,TaskId=%u is Runing Detector",
                      pTask->m_usProcId, pTask->m_usTaskId );
        return;
    }
    /*
     * 如果上次执行的事件尚未完成，本次不运行
     */
    if ( BST_TRUE == pTask->IsBusy () )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::ScheduleTask pTask Is Busy" );
        return;
    }
    usRealCyc                           = GetTaskCycle( pTaskItem );
    if( BST_CORE_INVALID_CYC == usRealCyc )
    {
        return;
    }
    /*
     * 如果系统TICK可以被任务周期整除，说明到了整数倍对齐时间
     */
    if ( 0 != m_usSysTickCnt % usRealCyc )
    {
        return;
    }

    enTaskState                         = pTask->GetState ();
    switch ( enTaskState )
    {
        /*
         * 如果任务停止，只设置suspendCounter为0，不做任何事情
         */
        case BST_TASK_STATE_STOPED:
            pTask->m_ulSuspCounter      = 0;
            break;

        /*
         * 如果任务挂起超过最大限度，则立即删除之
         */
        case BST_TASK_STATE_SUSPEND:
            pTask->m_ulSuspCounter ++;
            if ( pTask->m_ulSuspCounter >= BST_TASK_MAX_SYSPEND )
            {
                pcTaskManager->Remove ( pTask->m_usProcId, pTask->m_usTaskId );
            }
            break;
        /*
         * 如果认为处于运行态，则调度执行
         */
        case BST_TASK_STATE_START:

            BST_DBG_LOG1( "BST_CTaskSchdler::ScheduleTask m_enLinkStaRank:%d",m_enLinkStaRank );
            if( BST_AS_NET_RANK_INVALID == m_enLinkStaRank )
            {
                pTaskItem->enSendState  = BST_APP_SEND_STATE_BLOCK;
                break;
            }

            if( BST_AS_NET_RANK_MIDDLE > m_enLinkStaRank )
            {
                pTaskItem->enSendState  = BST_APP_SEND_STATE_BLOCK;
                if( BST_TRUE == BST_OS_TimerIsStop( m_ulDelayTimerId ) )
                {
                    BST_DBG_LOG( "BST_CTaskSchdler::Task start delay timer" );
                    BST_OS_TimerStart ( m_ulDelayTimerId, BST_TASK_DELAY_TIME_MS );
                }
                break;
            }
            BST_SRV_ApiSendPTaskEvent( pTask, BST_SRV_S2T_EXE_COMAND, 0 );
            pTaskItem->ulLastSendTime   = BST_OS_TimerNowMs();

            if( BST_APP_SEND_STATE_NORM == pTaskItem->enSendState )
            {
                BST_CORE_MARK_CYC_BIT( m_usCalledBitRecord, usRealCyc );
                m_usSendingCnt++;
            }
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : ProcServiceStateChange
 功能描述  : 接入系统服务状态变化处理
 输入参数  : BST_SRV_UTRAN_SRV_STATE_STRU 实际句柄
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::LinkStateChgProc( BST_AS_NET_RANK_ENUM_UINT32 enNetRank )
{
    BST_DBG_LOG2( "BST_CTaskSchdler::LinkStateChgProc RANK_Old=u%, RANK_NEW=u%",
                  m_enLinkStaRank,
                  enNetRank );
    if ( m_enLinkStaRank == enNetRank )
    {
        return;
    }
    m_enLinkStaRank          = enNetRank;

    if ( m_enLinkStaRank <= BST_AS_NET_RANK_POOR )
    {
        BST_SRV_CHbDetector::GetInstance()->onBlock();
    }
    else
    {
        BST_SRV_CHbDetector::GetInstance()->onUnBlock();
        /*在调度所有block任务之前，先停止心跳延时的定时器*/
        if( BST_FALSE == BST_OS_TimerIsStop( m_ulDelayTimerId ) )
        {
            BST_DBG_LOG( "BST_CTaskSchdler::Task exec, stop delay time" );
            BST_OS_TimerStop ( m_ulDelayTimerId );
        }
        
        /*遍历任务列表，获取任务并进行相应调度 */
        ScheduleBlockedTask();
    }

}

/*****************************************************************************
 函 数 名  : AsEventCallback
 功能描述  : AS事件回调函数
 输入参数  : enEvent  :AS事件类型
             ulLength :长度
             pvData   :传入参数,RRC状态类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::AsEventCallback(
    BST_AS_EVT_ENUM_UINT32    enEvent,
    BST_UINT32                ulLength,
    BST_VOID                 *pvData )
{
    BST_UINT32          ulPara;
    BST_UINT32          ulOldRrcState;

    switch( enEvent )
    {
        /*
         * 仅处理RRC状态信息，当RRC连接成功时，查看当前剩余时间是否靠近
         */
        case BST_AS_EVT_L3_RRC_STATE:
            if ( BST_OS_SIZEOF(ulPara) != ulLength )
            {
                break;
            }
            if ( BST_NULL_PTR == pvData )
            {
                break;
            }
            ulOldRrcState   = m_ulRrcState;
            BST_OS_MEMCPY( &m_ulRrcState, pvData, ulLength );

            if((BST_TRUE == BST_AS_IsRrcConnected(m_ulRrcState))
                && (BST_FALSE == BST_AS_IsRrcConnected(ulOldRrcState)))
            {
                ulPara      = BST_OS_TimerIsStop( m_ulTimerId );
                if ( BST_TRUE == ulPara )
                {
                    break;
                }
                ulPara      = BST_OS_TimeGetRemain( m_ulTimerId );
                if ( 0 == ulPara )
                {
                    break;
                }
                ulPara      = NearRrcTrig ( ulPara );
                BST_OS_TimerStart( m_ulTimerId, ulPara );
            }
            break;
        case BST_AS_EVT_L3_NET_RANK:
            if ( BST_OS_SIZEOF(BST_AS_NET_RANK_ENUM_UINT32) != ulLength )
            {
                BST_RLS_LOG1("BST_CTaskSchdler::AsEventCallback Error Net Rank Length = %u:", ulLength );
                break;
            }
            LinkStateChgProc( *( (BST_AS_NET_RANK_ENUM_UINT32 *)pvData ) );
            break;
        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : NearRrcTrig
 功能描述  : 如果任务起来的时间在靠近已经建立RRC连接的时间点，则随着刚才的RRC连接进行查询，
             否则还是按原有时间点进行查询
 输入参数  : ulSysTimerRemainMs : 系统定时器剩余时长
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_CTaskSchdler::NearRrcTrig ( BST_UINT32 const ulSysTimerRemainMs )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_UINT32                  ulNextSysTick;
    BST_UINT32                  ulNextLongCycle;
    BST_UINT16                  usRealCyc;

    ulNextLongCycle             = 0;
    ulNextSysTick               = m_usSysTickCnt;
    /*
     * 遍历任务列表，找出所有有效任务
     */
    for( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
         pstPtaskNode!= BST_NULL_PTR;
         pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        if( 0 == pstPtaskNode->pcTask->m_ulCycle )
        {
            continue;
        }
        if( BST_TRUE == pstPtaskNode->pcTask->IsBusy () )
        {
            continue;
        }
        if( BST_TASK_STATE_START != pstPtaskNode->pcTask->GetState () )
        {
            continue;
        }
        if( BST_CORE_IsRuningDetector( pstPtaskNode->pcTask ) )
        {
            continue;
        }
        /*
         * 查看是否有任务周期与Tick整除项，代码周期到来
         */
        usRealCyc                   = GetTaskCycle( pstPtaskNode );
        if( BST_CORE_INVALID_CYC == usRealCyc )
        {
            continue;
        }
        if( 0 == ( ulNextSysTick % usRealCyc ) )
        {
            if( usRealCyc > ulNextLongCycle )
            {
                ulNextLongCycle = usRealCyc;
            }
        }
    }
    /*
     * 获取当前系统周期，并取比例，如果剩余时间低于该值，则说明足够靠近
     */
    ulNextLongCycle             = BST_CORE_GetCycleToMs( ulNextLongCycle );
    if( BST_TASK_IsNearEnough( ulSysTimerRemainMs, ulNextLongCycle ) )
    {
        BST_RLS_LOG("BST_CTaskSchdler::NearRrcTrig Closing To RRC Enough, Periodic Runing after 200Ms");
        return BST_TASK_RRC_SEND_TIMER;
    }
    else
    {
        return ulSysTimerRemainMs;
    }
}

/*****************************************************************************
 函 数 名  : AckSendResult
 功能描述  : 收到任务发送结果知会
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::AckSendResult(
    BST_CORE_CPTask *pcPTask, BST_UINT16 ucResult )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    pstPtaskNode                = GetTaskItem( pcPTask );
    if ( BST_NULL_PTR == pstPtaskNode )
    {
        return;
    }
    /**
     * 非探测器应用，且上次发送属于正常发送的，则在此--
     */
    if( ( BST_APP_SEND_STATE_NORM == pstPtaskNode->enSendState )
     && ( !BST_CORE_IsRuningDetector( pcPTask ) ) )
    {
        m_usSendingCnt--;
    }

    if( BST_CORE_SCHD_ACK_SUC == ucResult )
    {
        ProcAckSuc( pstPtaskNode );
    }
    else
    {
        ProcAckErr( pstPtaskNode );
    }

    if( 0 == m_usSendingCnt )
    {
        ProcFinish();
    }

}

/*****************************************************************************
 函 数 名  : ProcAckSuc
 功能描述  : 处理接收成功事件
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::ProcAckSuc( BST_CORE_PTASK_NODE_STRU *pstTaskItem )
{
    BST_UINT16                  usUsingCycle;

    /*
     * 首次心跳发送，可能不到一个心跳周期，不做任何处理，置位正常周期发送状态
     */
    if( BST_APP_SEND_STATE_FIRST == pstTaskItem->enSendState )
    {
        pstTaskItem->enSendState       = BST_APP_SEND_STATE_NORM;
        return;
    }
    if( BST_CORE_IsRuningDetector( pstTaskItem->pcTask ) )
    {
        BST_SRV_CHbDetector::GetInstance()->AckSendResult( BST_CORE_SCHD_ACK_SUC );
        return;
    }
    /*
     * 阻塞后发送的心跳，结果如何都不计入最终记录
     */
    if( BST_APP_SEND_STATE_BLOCK == pstTaskItem->enSendState )
    {
        pstTaskItem->enSendState       = BST_APP_SEND_STATE_NORM;
        return;
    }
    pstTaskItem->enLastErrType          = BST_CORE_SCHD_ACK_SUC;
    usUsingCycle                        = GetTaskCycle( pstTaskItem );

    if( ( usUsingCycle <= BST_SRV_DTC_MAX_LEN )&&( usUsingCycle != BST_CORE_INVALID_CYC ) )
    {        
        g_aucCycErrCnt[ usUsingCycle ]  = 0;
        BST_CORE_CLR_CYC_BIT( m_usCalledBitRecord, usUsingCycle );
    }
}

/*****************************************************************************
 函 数 名  : ProcAckErr
 功能描述  : 处理接收失败事件
 输入参数  : pC_PTask : 任务指针
 输出参数  : BOOL 处理结果是否计入
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::ProcAckErr( BST_CORE_PTASK_NODE_STRU *pstTaskItem )
{
    pstTaskItem->ulLastSendTime    = 0;
    /*
     * 阻塞后发送的心跳，结果如何都不计入最终记录?
     */
    if( BST_APP_SEND_STATE_BLOCK == pstTaskItem->enSendState )
    {
        pstTaskItem->enSendState       = BST_APP_SEND_STATE_NORM;
        return;
    }
    if( BST_CORE_IsRuningDetector( pstTaskItem->pcTask) )
    {
        BST_SRV_CHbDetector::GetInstance()->AckSendResult( BST_CORE_SCHD_ACK_ERR );
        return;
    }
    /*
     * 如果上次心跳就没有成功，那么就要注重考虑
     */
    if( pstTaskItem->enLastErrType != BST_CORE_SCHD_ACK_SUC )
    {
        /*
         * 如果上次采用的是系统心跳没成功，那么后面就要回退一个周期
         */
        if( BST_CORE_INVALID_CYC == pstTaskItem->usSelfCyc )
        {
            pstTaskItem->usSelfCyc  = BST_SRV_CHbDetector::GetInstance()
                                    ->GetConfCyc( pstTaskItem->pcTask->m_ulCycle );
        }
        if( pstTaskItem->usSelfCyc > 1 )
        {
            pstTaskItem->usSelfCyc--;
        }
    }
    pstTaskItem->enLastErrType = BST_CORE_SCHD_ACK_ERR;
}

/*****************************************************************************
 函 数 名  : ProcFinish
 功能描述  : 本来发送都相应完毕，处理结果
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::ProcFinish( BST_VOID )
{
    BST_UINT16                      usCounter;
    BST_CORE_PTASK_NODE_STRU       *pstPtaskNode;
    
    /*
     * 全部周期心跳无论成功还是失败，都回应完成，但是某些周期的心跳没有成功
     */
    for( ;; )
    {
        if( 0 == m_usCalledBitRecord )
        {
            break;
        }
        usCounter                   = GetErrorCycle( m_usCalledBitRecord );
        BST_CORE_CLR_CYC_BIT( m_usCalledBitRecord, usCounter );
        if( ( usCounter <= BST_SRV_DTC_MAX_LEN )&&( usCounter != BST_CORE_INVALID_CYC ) )
        {
            g_aucCycErrCnt[usCounter]++;
            /*
             * 隶属于某个周期的全部心跳已经连续两轮失败了, 说明目前最大周期存在问题，需要重新探测
             */
            if( g_aucCycErrCnt[usCounter] >= BST_CORE_MAX_CYC_ERRNO )
            {
                m_usCalledBitRecord = 0;
                for( usCounter = 0; usCounter < BST_SRV_DTC_MAX_LEN; usCounter++ )
                {
                    g_aucCycErrCnt[usCounter]   = 0;
                }
                /*
                 * 遍历任务表，清除所有任务自探周期
                 */
                for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
                      pstPtaskNode!= BST_NULL_PTR;
                      pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
                {
                    pstPtaskNode->usSelfCyc     = BST_CORE_INVALID_CYC;
                }
                BST_SRV_CHbDetector::GetInstance()->ReStart();
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : TaskStarted
 功能描述  : 处理任务开始事件通知消息
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::TaskStarted( BST_CORE_CPTask *pcPTask )
{
    BST_CORE_PTASK_NODE_STRU       *pTaskItem;

    if( BST_TRUE == BST_SRV_CHbDetector::GetInstance()->IsTask( pcPTask ) )
    {
        BST_SRV_CHbDetector::GetInstance()->Resume();
    }
    else
    {
        pTaskItem                   = GetTaskItem( pcPTask );
        if( BST_NULL_PTR == pTaskItem )
        {
            return;
        }
        pTaskItem->enSendState      = BST_APP_SEND_STATE_FIRST;
        pTaskItem->ulLastSendTime   = 0;
    }
}
/*****************************************************************************
 函 数 名  : TaskStoped
 功能描述  : 处理任务结束事件通知消息
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::TaskStoped( BST_CORE_CPTask *pcPTask )
{
    if( BST_TRUE == BST_SRV_CHbDetector::GetInstance()->IsTask( pcPTask ) )
    {
        BST_SRV_CHbDetector::GetInstance()->Pause();
    }
}
/*****************************************************************************
 函 数 名  : DefineDetector
 功能描述  : 任务指明自己身份为探测器知会通知
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::DefineDetector( BST_CORE_CPTask *pcPTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    pstPtaskNode                = GetTaskItem( pcPTask );
    if ( BST_NULL_PTR == pstPtaskNode )
    {
        BST_DBG_LOG("DefineDetector,pstPtaskNode is null");
        return;
    }
    BST_SRV_CHbDetector::GetInstance()->DefTask( pstPtaskNode );
}

/*****************************************************************************
 函 数 名  : GetTaskItem
 功能描述  : 根据任务查找任务记录条目
 输入参数  : pC_PTask : 任务指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_CORE_PTASK_NODE_STRU* BST_CTaskSchdler::GetTaskItem( BST_CORE_CPTask *pcPTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    
    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        return BST_NULL_PTR;
    }
    /*
     * 遍历任务表，找到相关任务运行
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        if( pstPtaskNode->pcTask == pcPTask )
        {
            return pstPtaskNode;
        }
    }
    return BST_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : GetTaskCycle
 功能描述  : 获取任务实际使用周期数
 输入参数  : BST_CORE_PTASK_NODE_STRU pstTaskItem : 任务记录指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT16 BST_CTaskSchdler::GetTaskCycle( BST_CORE_PTASK_NODE_STRU *pstTaskItem )
{
    BST_UINT16              usTaskCycle;

    if( BST_CORE_INVALID_CYC ==  pstTaskItem->pcTask->m_ulCycle )
    {
        return BST_CORE_INVALID_CYC;
    }
    /*
     * 如果self周期有效，那么优先用任务自己的self周期
     */
    if( BST_CORE_INVALID_CYC != pstTaskItem->usSelfCyc )
    {
        return pstTaskItem->usSelfCyc;
    }

    usTaskCycle             = BST_SRV_CHbDetector::GetInstance()
                            ->GetConfCyc( pstTaskItem->pcTask->m_ulCycle );
    return usTaskCycle;
}

/*****************************************************************************
 函 数 名  : onDetFinished
 功能描述  : 回调Det完成，可以通知应用修改周期
 输入参数  : ( BST_UINT8 ucLongestCyc )系统探明的最高周期
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::onDetFinished( BST_UINT8 ucLongestCyc )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        return;
    }
    /*
     * 遍历任务表，找到相关任务运行
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        BST_DBG_LOG2("onDetFinished,m_ulCycle:%d,ucLongestCyc:%d", 
        pstPtaskNode->pcTask->m_ulCycle,ucLongestCyc);
        if( pstPtaskNode->pcTask->m_ulCycle > ucLongestCyc )
        {
            BST_SRV_ApiSendPTaskEvent( pstPtaskNode->pcTask,
                                       BST_SRV_S2T_CYC_UPDATE,
                                       ucLongestCyc );
        }
    }
}

/*****************************************************************************
 函 数 名  : GetErrorBitAdd
 功能描述  : 获取出错的最低周期位
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月25日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT16 BST_CTaskSchdler::GetErrorCycle( const BST_UINT16 usErrorMsg )
{
    BST_UINT16  usCnt;
    
    for( usCnt=0; usCnt<16; usCnt++ )
    {
        if( ( usErrorMsg & (~(0x01<<usCnt) ) ) != usErrorMsg )
        {
            return usCnt;
        }
    }
    return BST_CORE_NO_ERR_BIT;
}


/*****************************************************************************
 函 数 名  : ScheduleBlockedTask
 功能描述  : 调度所有前面被blocked task执行一次
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年08月21日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CTaskSchdler::ScheduleBlockedTask(BST_VOID )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNodeNext;
    BST_DBG_LOG( "BST_CTaskSchdler::ScheduleBlockedTask" );

    /*
     * 遍历任务列表，获取任务并进行相应调度
     */

    for ( pstPtaskNode = ( BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = pstPtaskNodeNext )
    {
        pstPtaskNodeNext    = ( BST_CORE_PTASK_NODE_STRU *)
                              lstNext((NODE *)pstPtaskNode);
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }

        if( BST_CORE_IsRuningDetector( pstPtaskNode->pcTask ) )
        {
            BST_DBG_LOG2( "ScheduleBlockedTask:: ProcId=%u ,TaskId=%u is Runing Detector",
                 pstPtaskNode->pcTask->m_usProcId, pstPtaskNode->pcTask->m_usTaskId );
            continue;
        }

        if( BST_APP_SEND_STATE_BLOCK != pstPtaskNode->enSendState )
        {
            BST_DBG_LOG3( "ScheduleBlockedTask:: ProcId=%u ,TaskId=%u enSendState=%u",
                 pstPtaskNode->enSendState, pstPtaskNode->pcTask->m_usProcId, pstPtaskNode->pcTask->m_usTaskId );
            continue;
        }
        if( BST_TRUE == pstPtaskNode->pcTask->IsBusy() )
        {
            BST_DBG_LOG2( "ScheduleBlockedTask:: ProcId=%u ,TaskId=%u is Busy",
                 pstPtaskNode->pcTask->m_usProcId, pstPtaskNode->pcTask->m_usTaskId );
            continue;
        }
        if( BST_TASK_STATE_START != pstPtaskNode->pcTask->GetState() )
        {
            continue;
        }

        BST_DBG_LOG2( "ScheduleBlockedTask:: ProcId=%u ,TaskId=%u",
             pstPtaskNode->pcTask->m_usProcId, pstPtaskNode->pcTask->m_usTaskId ); 

        BST_SRV_ApiSendPTaskEvent( pstPtaskNode->pcTask, BST_SRV_S2T_EXE_COMAND, 0 );
        pstPtaskNode->ulLastSendTime      = BST_OS_TimerNowMs();
    }
}

