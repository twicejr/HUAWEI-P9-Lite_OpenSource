

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_CORE_Task.h"
#include "BST_OS_Thread.h"
#include "BST_SRV_TaskMng.h"
#include "BST_DBG_MemLeak.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_CORE_TASK_CPP
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


BST_CTask::BST_CTask ( BST_PROCID_T in_usProcId, BST_TASKID_T in_usTaskId )
          :m_usProcId ( in_usProcId ), m_usTaskId ( in_usTaskId )
{
    BST_OS_LOCKCNT_T                    tThreadLockCnt;
    tThreadLockCnt                      = BST_OS_ThreadLock ();
    m_enState                           = BST_TASK_STATE_STOPED;
    BST_OS_ThreadUnLock ( tThreadLockCnt );
    BST_DBG_ADD_TASK( m_usProcId, m_usTaskId );
}

BST_CTask::~BST_CTask ( BST_VOID )
{
    BST_DBG_RMV_TASK( m_usProcId, m_usTaskId );
    return;
}


BST_VOID BST_CTask::Start ( BST_VOID )
{
    m_enState                           = BST_TASK_STATE_START;
    BST_DBG_UPDATE_STATE( m_usProcId, m_usTaskId, m_enState);
    BST_RLS_LOG2("Task start: procid=%u, taskid=%u", m_usProcId, m_usTaskId );
}


BST_VOID BST_CTask::Stop ( BST_VOID )
{
    m_enState                           = BST_TASK_STATE_STOPED;
    BST_DBG_UPDATE_STATE( m_usProcId, m_usTaskId, m_enState);    
    BST_RLS_LOG2("Task stop: procid=%u, taskid=%u", m_usProcId, m_usTaskId );
}


BST_TASK_STATE_ENUM_UINT8 BST_CTask::GetState ( BST_VOID )
{
    return ( m_enState );
}

