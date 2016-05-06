/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_CORE_PTask.cpp
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年05月04日
  最近修改   :
  功能描述   : 实现循环型任务类BST_CORE_PTask相关处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年05月13日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_CORE_PTask.h"
#include "BST_CORE_Schd.h"
//#include "BST_DBG_MemLeak.h"
#include "BST_SRV_AsCtrl.h"
#include "BST_SRV_Event.h"
#include "BST_DSPP_Report.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_CORE_PTASK_CPP
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
  3 函数声明
*****************************************************************************/

/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/

/******************************************************************************
   6 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : ConfigCycleTicks
 功能描述  : 配置任务周期
 输入参数  : ulTickFct :配置任务周期大小
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_CORE_CPTask::ConfigCycleTicks ( BST_UINT32 ulTickFct )
{
    m_ulCycle                           = ulTickFct;
    BST_DBG_UPDATE_CYC_LEN( m_usProcId, m_usTaskId, m_ulCycle );
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_CORE_CPTask
 功能描述  : BST_CORE_CPTask类构造函数，初始化相关变量
 输入参数  : in_usProcId:  代理类型(Email/HeartBeat)
             in_usTaskId:  任务ID号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
    2.日    期   : 2015年05月27日
      作    者   : d00173029
      修改内容   : 修改了detach方法，由函数调用修改为消息传递
*****************************************************************************/
BST_CORE_CPTask::BST_CORE_CPTask ( BST_PROCID_T in_usProcId, BST_TASKID_T in_usTaskId )
                :BST_CTask ( in_usProcId, in_usTaskId )
{
    m_ulCycle                           = 0;
    m_ulSuspCounter                     = 0;
    m_ulBusyFlag                        = BST_FALSE;
    BST_SRV_ApiSendPTaskEvent( this, BST_SRV_T2S_TSK_ATTACH, 0 );
}

/*****************************************************************************
 函 数 名  : Suspend
 功能描述  : 挂起任务操作
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
BST_VOID BST_CORE_CPTask::Suspend ( BST_VOID )
{
    m_enState                           = BST_TASK_STATE_SUSPEND;
    m_ulSuspCounter                     = 0;
    m_ulBusyFlag                        = BST_FALSE;
    BST_DBG_LOG2("Task suspend: procid=%u, taskid=%u", m_usProcId, m_usTaskId );
    BST_DBG_UPDATE_STATE( m_usProcId, m_usTaskId, m_enState );
}

/*****************************************************************************
 函 数 名  : Maintain
 功能描述  : 开始维护任务
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
BST_VOID BST_CORE_CPTask::Maintain( BST_VOID )
{
    m_enState                           = BST_TASK_STATE_MNTNING;
    m_ulSuspCounter                     = 0;
    m_ulBusyFlag                        = BST_FALSE;
    BST_DBG_LOG2("Task Maintain: procid=%u, taskid=%u", m_usProcId, m_usTaskId );
    BST_DBG_UPDATE_STATE( m_usProcId, m_usTaskId, m_enState );
}

/*****************************************************************************
 函 数 名  : Waiting
 功能描述  : 开始维护任务
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
BST_VOID BST_CORE_CPTask::Waiting( BST_VOID )
{
    m_enState                           = BST_TASK_STATE_WAINTING;
    m_ulSuspCounter                     = 0;
    m_ulBusyFlag                        = BST_FALSE;
    BST_DBG_LOG2("Task Waiting: procid=%u, taskid=%u", m_usProcId, m_usTaskId );
    BST_DBG_UPDATE_STATE( m_usProcId, m_usTaskId, m_enState );
}

/*****************************************************************************
 函 数 名  : IsBusy
 功能描述  : 查询任务是否处于busy状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_TRUE   处于busy状态
             BST_FALSE  不处于busy状态
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32  BST_CORE_CPTask::IsBusy ( BST_VOID )
{
    return m_ulBusyFlag;
}

/*****************************************************************************
 函 数 名  : Finished
 功能描述  : 任务结束操作
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
BST_VOID BST_CORE_CPTask::Finished ( BST_VOID )
{
    BST_SRV_CAsCtrl                    *pcAsCtrl;
    BST_UINT32                          ulVid;
    BST_DBG_LOG2( "Proc=%d, Task=%d, Called Finished" , m_usProcId, m_usTaskId );

    ulVid                               = BST_SRV_MakeTaskVid( m_usProcId, m_usTaskId );
    m_ulBusyFlag                        = BST_FALSE;
    pcAsCtrl                            = BST_SRV_CAsCtrl::GetInstance ();
    BST_ASSERT_NULL ( pcAsCtrl );
    pcAsCtrl->UsingRrcDeVote ( ulVid );
}
/*****************************************************************************
 函 数 名  : TxStart
 功能描述  : 传输事件开始
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
BST_VOID BST_CORE_CPTask::TxStart( BST_VOID )
{
    BST_SRV_CAsCtrl                    *pcAsCtrl;
    BST_UINT32                          ulVid;

    ulVid                               = BST_SRV_MakeTaskVid( m_usProcId, m_usTaskId );
    pcAsCtrl                            = BST_SRV_CAsCtrl::GetInstance ();
    m_ulBusyFlag                        = BST_TRUE;

    BST_ASSERT_NULL ( pcAsCtrl );
    pcAsCtrl->UsingRrcVote ( ulVid );
}

/*****************************************************************************
 函 数 名  : PEntry
 功能描述  : 任务入口函数
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
BST_VOID BST_CORE_CPTask::onExecute ( BST_VOID )
{
    BST_DBG_LOG1("BST_CORE_CPTask,onExecute",m_ulCycle);

    if( BST_CORE_INVALID_CYC == m_ulCycle )
    {
        return;
    }
    TxStart();
    Entry ();
}

/*****************************************************************************
 函 数 名  : onUpdateCycle
 功能描述  : 回调函数，探测器明确时间后，告知应用更新时间
 输入参数  : BST_UINT16 ulDetCycle 探明的新周期数，单位为Cycle（1->5min）
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月24日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CORE_CPTask::onUpdateCycle( BST_UINT16 ulDetCycle )
{
}

/*****************************************************************************
 函 数 名  : onErrClosed
 功能描述  : 探测器发现该应用SOCKET已经异常断开
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月24日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_CORE_CPTask::onCycleError( BST_VOID )
{
}

/*****************************************************************************
 函 数 名  : ~BST_CORE_CPTask
 功能描述  : BST_CORE_CPTask类的析构函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
    2.日    期   : 2015年05月27日
      作    者   : d00173029
      修改内容   : 修改了detach方法，由函数调用修改为消息传递
*****************************************************************************/
BST_CORE_CPTask::~BST_CORE_CPTask ( BST_VOID )
{
    BST_SRV_ApiSendPTaskEvent( this, BST_SRV_T2S_TSK_DETACH, 0 );
}

