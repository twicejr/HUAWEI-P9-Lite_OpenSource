/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SYS_Mntn.c
  版 本 号   : 初稿
  作    者   : s00211350
  生成日期   : 2014年09月16日
  最近修改   :
  功能描述   : Bastet可维可测公共处理部分
  函数列表   :

  修改历史   :
  1.日    期   : 2014年09月16日
    作    者   : s00211350
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_SYS_Mntn.h"
#include "BST_OS_Thread.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SYSMNTN_C
/*lint +e767*/

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/
BST_OS_MBX_T   *BST_SRV_GetSysMsgHandle( BST_VOID );

/******************************************************************************
   3 私有定义
******************************************************************************/
BST_VOID BST_SYS_MntnTimerExpired(
    BST_OS_TIMERID_T                ulTimerId,
    BST_VOID                       *pvArg );

BST_UINT32 BST_SYS_MntnBuildAgentInfoInd(
    OM_BST_APP_INFO_STRU           *pstAgentInfo,
    const BST_UINT16                usAppNumber );

BST_UINT8* BST_SYS_MntnGetSendExternalMsgBuffAddr(
    BST_UINT32                      ulPid,
    BST_UINT32                      ulBuffSize );

OM_BST_APP_INFO_STRU *BST_SYS_MntnSrchAppByTask(
    BST_UINT16                      usType,
    BST_UINT16                      usTaskId );

OM_BST_APP_INFO_STRU *BST_SYS_MntnSrchAppByPort(
    BST_UINT16                      usLocalPortNumber );

BST_VOID BST_SYS_MntnChangedInd( BST_VOID );

BST_VOID BST_SYS_MntnTrigReport( BST_VOID );

/******************************************************************************
   4 全局变量定义
******************************************************************************/
BST_STATIC  BST_SYS_MNTN_ENTITY_STRU        g_stBstMntnEntity;
/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : BST_SYS_MntnInit
 功能描述  : 初始化Maintain相关变量属性
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年09月16日
      作    者   : s00211350
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnInit( BST_VOID )
{
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    tThreadLockCnt                      = BST_OS_ThreadLock();
    g_stBstMntnEntity.stReportTimer     = BST_OS_TimerCreate
                                        ( BST_SYS_MntnTimerExpired,
                                          BST_NULL_PTR,
                                          BST_SRV_GetSysMsgHandle() );
    lstInit( &g_stBstMntnEntity.stAppList );
    BST_OS_MEMSET( &g_stBstMntnEntity.aucLocalIp[0],
                   0, OM_BST_IP_ADDR_LEN );
    g_stBstMntnEntity.ucChanged         = BST_FALSE;
    g_stBstMntnEntity.ucIsInit          = BST_TRUE;
    BST_RLS_LOG( "[Mntn] Initial System" );
    BST_OS_ThreadUnLock( tThreadLockCnt );
    return;
}


/*****************************************************************************
 函 数 名  : BST_SYS_MntnInit
 功能描述  : 初始化Maintain相关变量属性
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年09月16日
      作    者   : s00211350
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnCofigLoacalIpAddress(
    BST_UINT8      *aucLocalIp,
    BST_UINT16      usBufLen )
{
    if ( BST_NULL_PTR == aucLocalIp )
    {
        BST_RLS_LOG( "[Mntn] BST_SYS_MntnCofigLoacalIpAddress Error Pointer" );
        return;
    }
    if ( OM_BST_IP_ADDR_LEN > usBufLen )
    {
        BST_RLS_LOG1( "[Mntn] BST_SYS_MntnCofigLoacalIpAddress Error Size:", usBufLen );
        return;
    }
    BST_OS_MEMCPY( &g_stBstMntnEntity.aucLocalIp[0],
                   aucLocalIp, OM_BST_IP_ADDR_LEN );
    return;
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnChangedInd
 功能描述  : 当外部接口操作发生过程中，提示变化，启动上报定时
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年09月16日
      作    者   : s00211350
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnChangedInd( BST_VOID )
{
    BST_SYS_MNTN_SetMntnMsgChgFlag();

    if ( BST_TRUE == BST_OS_TimerIsStop( BST_SYS_MNTN_GetTimerId() ) )
    {
        BST_OS_TimerStart( BST_SYS_MNTN_GetTimerId(),
                           BST_SYS_MNTN_REPORT_TIMER_LEN );
    }
    return;
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnAddTask
 功能描述  : 把新增的APP信息添加到链表
 输入参数  : BST_UINT16 usType
             BST_UINT16 usTaskId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年09月16日
      作    者   : s00211350
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnAddTask(
    BST_UINT16  usType,
    BST_UINT16  usTaskId )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppInfoNode;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }

    if ( (BST_UINT32)BST_SYS_MNTN_GetAppNumber() >= BST_SYS_MNTN_MAX_APP_NUMBER )
    {
        return;
    }

    tThreadLockCnt                      = BST_OS_ThreadLock();
    if ( BST_NULL_PTR != BST_SYS_MntnSrchAppByTask( usType, usTaskId ) )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }
    pstAppInfoNode                      = ( BST_SYS_MNTN_APP_NODE_STRU *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF(BST_SYS_MNTN_APP_NODE_STRU) );
    if ( BST_NULL_PTR == pstAppInfoNode )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }
    BST_OS_MEMSET( &(pstAppInfoNode->stAppInfo),
                   0,
                   BST_OS_SIZEOF(OM_BST_APP_INFO_STRU) );

    pstAppInfoNode->stAppInfo.usAppType = usType;
    pstAppInfoNode->stAppInfo.usTaskId  = usTaskId;

    lstAdd( BST_SYS_MNTN_GetAppListHead(), (NODE *)pstAppInfoNode );
    BST_RLS_LOG3( "[Mntn] Add Task: TypeId=, TaskId=, Total=",
                  usType, usTaskId, BST_SYS_MNTN_GetAppNumber() );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
/*lint -e429*/
}
/*lint +e429*/
/*****************************************************************************
 函 数 名  : BST_SYS_MntnUpdateState
 功能描述  : 根据应用类型和Task Id更新任务状态信息
 输入参数  : BST_UINT16 usType    应用类型
             BST_UINT16 usTaskId  任务ID
             BST_UINT16 usState   任务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年11月14日
      作    者   : l00220658
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnUpdateState(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_UINT16  usState )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }
    pstAppInfo->usTaskState = usState;
    BST_RLS_LOG3( "[Mntn] State Updated: TypeId=, TaskId=, NewState=",
                  usType, usTaskId, usState );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnUpdateIpInfo
 功能描述  : 根据应用类型和Task Id更新IP地址信息
 输入参数  : BST_UINT16 usType    应用类型
             BST_UINT16 usTaskId  任务ID
             BST_IP_SOCKET_ADD_T* pstIpInfo  IP地址信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年11月14日
      作    者   : l00220658
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnUpdateIpInfo(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_VOID   *pstIpInfo )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_IP_SOCKET_ADD_T                *pstSocketInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    if ( BST_NULL_PTR == pstIpInfo )
    {
        return;
    }
    pstSocketInfo                       = ( BST_IP_SOCKET_ADD_T *)pstIpInfo;
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->usLocalPort             = pstSocketInfo->usLocalPort;
    pstAppInfo->usRemotePort            = pstSocketInfo->usRemotePort;

    BST_OS_MEMCPY( &pstAppInfo->aucLocalIp[0],
                   BST_SYS_MNTN_GetLocalIpHead(), OM_BST_IP_ADDR_LEN );

    BST_OS_MEMCPY( &pstAppInfo->aucRemoteIp[0],
                   &pstSocketInfo->aucRemoteIp[0], OM_BST_IP_ADDR_LEN );

    BST_RLS_LOG4( "[Mntn] Socket Configed_01: TypeId=, TaskId=, LocalPort=, RemotePort=",
            usType, usTaskId, (pstSocketInfo)->usLocalPort, (pstSocketInfo)->usRemotePort );

    BST_RLS_LOG4( "[Mntn] Socket Configed_02: Remote Ip Address",
            (pstAppInfo)->aucRemoteIp[3], (pstAppInfo)->aucRemoteIp[2],
            (pstAppInfo)->aucRemoteIp[1], (pstAppInfo)->aucRemoteIp[0]);

    BST_RLS_LOG4( "[Mntn] Socket Configed_02: Local Ip Address",
            (pstAppInfo)->aucLocalIp[3], (pstAppInfo)->aucLocalIp[2],
            (pstAppInfo)->aucLocalIp[1], (pstAppInfo)->aucLocalIp[0]);

    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnUpdateCycleLen
 功能描述  : 根据应用类型和Task Id更新循环长度
 输入参数  : BST_UINT16 usType      应用类型
             BST_UINT16 usTaskId    任务ID
             BST_UINT16 usCycleLen  循环长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年11月14日
      作    者   : l00220658
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnUpdateCycleLen(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_UINT16  usCycleLen )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->usCycleLen              = usCycleLen;
    BST_RLS_LOG3("[Mntn] Periodic Configed: TypeId=, TaskId=, Cycle=",
                 usType, usTaskId, usCycleLen );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnUpdateSuccNum
 功能描述  : 根据应用类型和Task Id更新连接成功次数
 输入参数  : BST_UINT16 usType      应用类型
             BST_UINT16 usTaskId    任务ID
             BST_UINT16 usSuccNum   连接成功次数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年11月14日
      作    者   : l00220658
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnUpdateSuccNum(
    BST_UINT16  usType,
    BST_UINT16  usTaskId )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->usSuccNum++;
    BST_RLS_LOG3("[Mntn] Task Run Success: TypeId=, TaskId=",
                 usType, usTaskId, pstAppInfo->usSuccNum );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnUpdateErrorNum
 功能描述  : 根据应用类型和Task Id更新连接失败次数
 输入参数  : BST_UINT16 usType      应用类型
             BST_UINT16 usTaskId    任务ID
             BST_UINT16 usErrorNum  连接失败次数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年11月14日
      作    者   : l00220658
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnUpdateErrorNum(
    BST_UINT16  usType,
    BST_UINT16  usTaskId )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByTask( usType, usTaskId );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->usErrorNum++;
    BST_RLS_LOG3("[Mntn] Task Run Fail: TypeId=, TaskId=",
                 usType, usTaskId, pstAppInfo->usErrorNum );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnUpdateTxFlow
 功能描述  : 根据本地IP端口更新发送流量信息
 输入参数  : BST_UINT16 usType      应用类型
             BST_UINT16 usTaskId    任务ID
             BST_UINT32 ulTxFlow    发送流量信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年11月14日
      作    者   : l00220658
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnUpdateTxFlow(
    BST_UINT16  usLocalPort,
    BST_UINT32  ulTxFlow )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByPort( usLocalPort );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->ulTxFlow               += ulTxFlow;
    pstAppInfo->ulTxFlow               &= BST_SYS_MNTN_MAX_TRAFFIC_FLOW;
    BST_RLS_LOG4( "[Mntn] Local Port Tx Flow New:  TypeId=, TaskId=, PortNumber=, TrafficeFlow=",
                  pstAppInfo->usAppType, pstAppInfo->usTaskId, usLocalPort, ulTxFlow );
    BST_OS_ThreadUnLock( tThreadLockCnt );
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnUpdateRxFlow
 功能描述  : 根据本地IP端口更新接收流量信息
 输入参数  : BST_UINT16 usType      应用类型
             BST_UINT16 usTaskId    任务ID
             BST_UINT32 ulRxFlow    接收流量信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年11月14日
      作    者   : l00220658
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnUpdateRxFlow(
    BST_UINT16  usLocalPort,
    BST_UINT32  ulRxFlow )
{
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstAppInfo                          = BST_SYS_MntnSrchAppByPort( usLocalPort );
    if ( BST_NULL_PTR == pstAppInfo )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    pstAppInfo->ulRxFlow               += ulRxFlow;
    pstAppInfo->ulRxFlow               &= BST_SYS_MNTN_MAX_TRAFFIC_FLOW;
    BST_RLS_LOG4( "[Mntn] Local Port Rx Flow New:  TypeId=, TaskId=, PortNumber=, TrafficeFlow=",
                  pstAppInfo->usAppType, pstAppInfo->usTaskId, usLocalPort, ulRxFlow );
    BST_OS_ThreadUnLock( tThreadLockCnt );
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnRemoveTask
 功能描述  : 将指定的APP从链表中删除
 输入参数  : BST_UINT16 usType
             BST_UINT16 usTaskId

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年09月16日
      作    者   : s00211350
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnRemoveTask(
    BST_UINT16  usType,
    BST_UINT16  usTaskId )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppNode;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( !BST_SYS_MNTN_IsMntnInited() )
    {
        return;
    }
    tThreadLockCnt                      = BST_OS_ThreadLock();
    /* 查找链表中是否已经存在该Task信息 */
    for ( pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstFirst(BST_SYS_MNTN_GetAppListHead());
          pstAppNode != BST_NULL_PTR;
          pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstNext( (NODE *)pstAppNode ) )
    {
        if ( ( usTaskId == pstAppNode->stAppInfo.usTaskId )
          && ( usType == pstAppNode->stAppInfo.usAppType ) )
        {
            break;
        }
    }

    if ( BST_NULL_PTR == pstAppNode )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return;
    }

    lstDelete( BST_SYS_MNTN_GetAppListHead(), (NODE *)pstAppNode );
    BST_OS_FREE( pstAppNode );
    BST_RLS_LOG3( "[Mntn] Remove Task: TypeId=, TaskId=, Total=",
                  usType, usTaskId, BST_SYS_MNTN_GetAppNumber() );
    BST_SYS_MntnChangedInd();
    BST_OS_ThreadUnLock( tThreadLockCnt );
/*lint -e438*/
}
/*lint +e438*/
/*****************************************************************************
 函 数 名  : BST_SYS_MntnBuildAgentInfoInd
 功能描述  : 填写需要发送的代理消息
 输入参数  : BST_SYS_MNTN_BUILD_TYPE_ENUM_UINT16 enType
             BST_UINT16                      usIndex

 输出参数  :
 返 回 值  : BST_UINT32
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年09月16日
      作    者   : s00211350
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT32 BST_SYS_MntnBuildAgentInfoInd(
    OM_BST_APP_INFO_STRU   *pstAgentInfo,
    const BST_UINT16        usAppNumber )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppNode;
    BST_UINT16                          usAppCounter;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    if ( BST_NULL_PTR == pstAgentInfo )
    {
        return BST_FALSE;
    }

    tThreadLockCnt                      = BST_OS_ThreadLock();
    usAppCounter                        = 0;
    /* 查找链表中是否已经存在该Task信息 */
    for ( pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstFirst(BST_SYS_MNTN_GetAppListHead());
          pstAppNode != BST_NULL_PTR;
          pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstNext( (NODE *)pstAppNode ) )
    {
        if ( ID_BST_OM_TASK_TYPE_MAIN == pstAppNode->stAppInfo.usAppType )
        {
            continue;
        }

        BST_OS_MEMCPY( &pstAgentInfo[usAppCounter],
                       &(pstAppNode->stAppInfo),
                       BST_OS_SIZEOF(OM_BST_APP_INFO_STRU) );
        usAppCounter++;
        if ( usAppCounter >= usAppNumber )
        {
            break;
        }
    }
    BST_OS_ThreadUnLock( tThreadLockCnt );
    return BST_TRUE;
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnGetSendExternalMsgBuffAddr
 功能描述  : 分配消息所需空间
 输入参数  : BST_UINT32 ulBuffSize

 输出参数  :
 返 回 值  : (BST_UINT8 *)
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年09月16日
      作    者   : s00211350
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT8* BST_SYS_MntnGetSendExternalMsgBuffAddr( BST_UINT32  ulPid,
                                                   BST_UINT32  ulBuffSize )
{
    BST_VOID                   *pMsgBuff;

    BST_ALLOC_MSG(ulPid, pMsgBuff, ulBuffSize);

    if( BST_NULL_PTR == pMsgBuff )
    {
        BST_DBG_LOG1("BST_SYS_MNTN_BuildMntnAgentInfoInd, Alloc Msg Buff Fail, buffersize",
                     ulBuffSize);
        return BST_NULL_PTR;
    }

    return (BST_UINT8 *)pMsgBuff;
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnTrigReport
 功能描述  : 向OM发送需要显示的代理信息
 输入参数  : BST_VOID

 输出参数  :
 返 回 值  : BST_VOID
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年09月16日
      作    者   : s00211350
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID BST_SYS_MntnTrigReport( BST_VOID )
{
    OM_BST_MSG_STRU                    *pstBstOmIndMsg;
    OM_BST_AGENT_APP_NUM_STRU          *pstBstAppNum;
    BST_UINT32                          ulRslt;
    BST_UINT32                          ulLength;
    BST_UINT16                          usAppNum;
    OM_BST_APP_INFO_STRU               *pstAppInfo;
    DIAG_TRANS_IND_STRU                 stTransData;
    MODEM_ID_ENUM_UINT16                enModemId;

    ulRslt                              = BST_TRUE;

    /* 申请的大小等于消息头BST_OM_MSG_STRU -4个字节的指针占位 + 实际代理信息大小 */
    usAppNum                            = (BST_UINT16)BST_SYS_MNTN_GetAppNumber();
    ulLength                            = (BST_OS_SIZEOF(OM_BST_MSG_STRU) - 4)
                                          + (BST_OS_SIZEOF(OM_BST_AGENT_APP_NUM_STRU));
    pstBstOmIndMsg                      = (OM_BST_MSG_STRU *)BST_SYS_MntnGetSendExternalMsgBuffAddr(UEPS_PID_BASTET, ulLength);
    if (BST_NULL_PTR == pstBstOmIndMsg)
    {
        BST_DBG_LOG1("BST_SYS_MntnTrigReport, Agent Info Msg Alloc Mem Fail",
                      0);
        return;
    }

    pstBstAppNum                        = (OM_BST_AGENT_APP_NUM_STRU *)(pstBstOmIndMsg->aucData);
    pstBstAppNum->usAgentAppNum         = usAppNum;
    pstAppInfo                          = ( (OM_BST_APP_INFO_STRU *)(pstBstAppNum->stBstAppList ) );

    ulRslt                              = BST_SYS_MntnBuildAgentInfoInd( pstAppInfo, usAppNum );

    if (BST_TRUE != ulRslt)
    {
        BST_DBG_LOG1("BST_SYS_MntnTrigReport, Get Bst Agent Info Error: ulRslt",
                      ulRslt);

        /* 释放传入的消息包 */
        BST_FREE_MSG( UEPS_PID_BASTET, pstBstOmIndMsg );

        return;
    }

    pstBstOmIndMsg->usPrimId    = ID_BST_OM_AGENT_INFO_IND;
    pstBstOmIndMsg->usToolId    = 0;

    enModemId                   = VOS_GetModemIDFromPid(UEPS_PID_BASTET);

    /* 填充信息 */
    stTransData.ulPid           = UEPS_PID_BASTET;
    stTransData.ulMsgId         = ID_BST_OM_AGENT_INFO_IND;
    stTransData.ulModule        = DIAG_GEN_MODULE(enModemId, DIAG_MODE_UMTS);
    stTransData.ulLength        = ulLength;
    stTransData.pData           = (VOS_VOID *)pstBstOmIndMsg;

    if ( VOS_OK != DIAG_TransReport((DIAG_TRANS_IND_STRU *)&stTransData) )
    {
        BST_RLS_LOG( "[Mntn] Send Maintain Message Fail:" );
    }
    else
    {
        BST_RLS_LOG( "[Mntn] Send Maintain Message Success" );
    }

    /* 释放传入的消息包 */
    BST_FREE_MSG( UEPS_PID_BASTET, pstBstOmIndMsg );

    return;
}
/*****************************************************************************
 函 数 名  : BST_SYS_MntnSrchAppByTask
 功能描述  : 根据TaskId查找AppInfo指针头
 输入参数  : BST_UINT16 usType, BST_UINT16 usTaskId 任务属性
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
OM_BST_APP_INFO_STRU *BST_SYS_MntnSrchAppByTask(
    BST_UINT16                      usType,
    BST_UINT16                      usTaskId )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppNode;

    /* 查找链表中是否已经存在该Task信息 */
    for ( pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstFirst(BST_SYS_MNTN_GetAppListHead());
          pstAppNode != BST_NULL_PTR;
          pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstNext( (NODE *)pstAppNode ) )
    {
        if ( ( usTaskId == pstAppNode->stAppInfo.usTaskId )
          && ( usType == pstAppNode->stAppInfo.usAppType ) )
        {
            return &pstAppNode->stAppInfo;
        }
    }
    return BST_NULL_PTR;
}
/*****************************************************************************
 函 数 名  : BST_SYS_MntnSrchAppByPort
 功能描述  : 根据PortNumber查找AppInfo指针头
 输入参数  : BST_UINT16 usLocalPortNumber 端口号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
OM_BST_APP_INFO_STRU *BST_SYS_MntnSrchAppByPort( BST_UINT16 usLocalPortNumber )
{
    BST_SYS_MNTN_APP_NODE_STRU             *pstAppNode;
    /* 查找链表中是否已经存在该Port信息 */
    for ( pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstFirst(BST_SYS_MNTN_GetAppListHead());
          pstAppNode != BST_NULL_PTR;
          pstAppNode = ( BST_SYS_MNTN_APP_NODE_STRU *)lstNext( (NODE *)pstAppNode ) )
    {
        if ( usLocalPortNumber == pstAppNode->stAppInfo.usLocalPort )
        {
            return &pstAppNode->stAppInfo;
        }
    }
    return BST_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : BST_SYS_MntnTimerExpired
 功能描述  : 定时器超时回调函数
 输入参数  : BST_OS_TIMERID_T ulTimerId
             BST_VOID* pvArg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SYS_MntnTimerExpired(
    BST_OS_TIMERID_T                ulTimerId,
    BST_VOID                       *pvArg )
{
    if ( BST_SYS_MNTN_IsMntnMsgChanged() )
    {
        BST_SYS_MNTN_ClrMntnMsgChgFlag();
        BST_OS_TimerStart( BST_SYS_MNTN_GetTimerId(),
                           BST_SYS_MNTN_REPORT_TIMER_LEN );
    }
    else
    {
        BST_RLS_LOG( "[Mntn] Send Maintain Message Triged" );
        BST_SYS_MntnTrigReport();
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



