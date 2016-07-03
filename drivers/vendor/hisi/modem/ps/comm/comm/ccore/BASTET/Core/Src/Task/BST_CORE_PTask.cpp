

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


BST_ERR_ENUM_UINT8 BST_CORE_CPTask::ConfigCycleTicks ( BST_UINT32 ulTickFct )
{
    m_ulCycle                           = ulTickFct;
    BST_DBG_UPDATE_CYC_LEN( m_usProcId, m_usTaskId, m_ulCycle );
    return BST_NO_ERROR_MSG;
}


BST_CORE_CPTask::BST_CORE_CPTask ( BST_PROCID_T in_usProcId, BST_TASKID_T in_usTaskId )
                :BST_CTask ( in_usProcId, in_usTaskId )
{
    m_ulCycle                           = 0;
    m_ulSuspCounter                     = 0;
    m_ulBusyFlag                        = BST_FALSE;
    BST_SRV_ApiSendPTaskEvent( this, BST_SRV_T2S_TSK_ATTACH, 0 );
}


BST_VOID BST_CORE_CPTask::Suspend ( BST_VOID )
{
    m_enState                           = BST_TASK_STATE_SUSPEND;
    m_ulSuspCounter                     = 0;
    m_ulBusyFlag                        = BST_FALSE;
    BST_DBG_LOG2("Task suspend: procid=%u, taskid=%u", m_usProcId, m_usTaskId );
    BST_DBG_UPDATE_STATE( m_usProcId, m_usTaskId, m_enState );
}


BST_VOID BST_CORE_CPTask::Maintain( BST_VOID )
{
    m_enState                           = BST_TASK_STATE_MNTNING;
    m_ulSuspCounter                     = 0;
    m_ulBusyFlag                        = BST_FALSE;
    BST_DBG_LOG2("Task Maintain: procid=%u, taskid=%u", m_usProcId, m_usTaskId );
    BST_DBG_UPDATE_STATE( m_usProcId, m_usTaskId, m_enState );
}


BST_VOID BST_CORE_CPTask::Waiting( BST_VOID )
{
    m_enState                           = BST_TASK_STATE_WAINTING;
    m_ulSuspCounter                     = 0;
    m_ulBusyFlag                        = BST_FALSE;
    BST_DBG_LOG2("Task Waiting: procid=%u, taskid=%u", m_usProcId, m_usTaskId );
    BST_DBG_UPDATE_STATE( m_usProcId, m_usTaskId, m_enState );
}


BST_UINT32  BST_CORE_CPTask::IsBusy ( BST_VOID )
{
    return m_ulBusyFlag;
}


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


BST_VOID BST_CORE_CPTask::onUpdateCycle( BST_UINT16 ulDetCycle )
{
}


BST_VOID BST_CORE_CPTask::onCycleError( BST_VOID )
{
}


BST_CORE_CPTask::~BST_CORE_CPTask ( BST_VOID )
{
    BST_SRV_ApiSendPTaskEvent( this, BST_SRV_T2S_TSK_DETACH, 0 );
}

