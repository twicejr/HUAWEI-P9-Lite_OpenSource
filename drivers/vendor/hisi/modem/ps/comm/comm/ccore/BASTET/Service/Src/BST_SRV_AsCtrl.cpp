/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SRV_AsCtrl.cpp
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年07月01日
  最近修改   :
  功能描述   : 接入层控制相关处理处理类成员函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月01日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_SRV_AsCtrl.h"
#include "BST_DRV_As.h"
#include "BST_OS_Memory.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_TaskMng.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SRV_ASCTRL_CPP
/*lint +e767*/
/******************************************************************************
  3 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : GetInstance
 功能描述  : 获取BST_SRV_CAsCtrl实例
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_SRV_CAsCtrl *
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_SRV_CAsCtrl *BST_SRV_CAsCtrl::GetInstance( BST_VOID )
{
    static BST_SRV_CAsCtrl *pcAsCtrlPtr = BST_NULL_PTR;
    if ( BST_NULL_PTR == pcAsCtrlPtr )
    {
        pcAsCtrlPtr = new BST_SRV_CAsCtrl();
    }
    return pcAsCtrlPtr;
}

/*****************************************************************************
 函 数 名  : Control
 功能描述  : 处理接入层控制消息
 输入参数  : enCmd: RRC控制消息
             pvData:RRC参数
 输出参数  : 无
 返 回 值  : BST_BOOL
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_BOOL BST_SRV_CAsCtrl::Control( BST_PRTC_TYPE_ENUM_UINT32 enCmd, BST_VOID *pvData )
{
    BST_DRV_STRU                       *pAsDrvHandle;
    BST_ERR_ENUM_UINT8                  ucRtnVal;

    pAsDrvHandle                        = BST_DRV_AsGetDvcHandle();

    ucRtnVal                            = pAsDrvHandle->pfIoCtrl( enCmd, pvData );
    if( BST_NO_ERROR_MSG != ucRtnVal )
    {
        return BST_FALSE;
    }
    // TO DO, Call *.C File
    return BST_TRUE;
}

/*****************************************************************************
 函 数 名  : UsingRrcVote
 功能描述  : 使用RRC投票，记名投票
 输入参数  : ulVid: Vid
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
BST_VOID BST_SRV_CAsCtrl::UsingRrcVote( BST_UINT32 ulVid )
{
    BST_SRV_VOTEID_STRU *pstVoteId;

    /*
     * 如果当前投票拆链已经禁用，那么理解返回
     */
    if ( BST_FALSE == m_VoteRrcEnableFlag )
    {
        BST_RLS_LOG( "UsingRrcVote : EnableFlag is FALSE.");
        return;
    }

    /*
     * 遍历投票者名单，如果已经投票则不允许多次投票，立即返回
     */
    for ( pstVoteId  = ( BST_SRV_VOTEID_STRU *)lstFirst( &m_stVoteList );
          BST_NULL_PTR != pstVoteId ;
          pstVoteId  = ( BST_SRV_VOTEID_STRU *)lstNext( (NODE *) pstVoteId ) )
    {
        if ( ulVid == pstVoteId->ulName )
        {
            BST_RLS_LOG1 ( "App Vote Vid=%d already existed", ulVid );
            return;
        }
    }

    /*
     * 为投票记名申请资源
     */
    pstVoteId           = ( BST_SRV_VOTEID_STRU *)BST_OS_MALLOC
                          ( BST_OS_SIZEOF( BST_SRV_VOTEID_STRU ) );
    if ( BST_NULL_PTR == pstVoteId )
    {
        return;
    }
    pstVoteId->ulName   = ulVid;
    lstAdd( &m_stVoteList, (NODE *)pstVoteId );

    BST_RLS_LOG3 ( "App Vote RRC Using, ProcId=%u, TaskId=u%, New Voting-Count=U%",
                 ( ( ulVid>>16 ) & 0xFFFF ),
                 ( ( ulVid ) & 0xFFFF ),
                 lstCount( &m_stVoteList ) );
}
/*lint +e429*/
/*****************************************************************************
 函 数 名  : UsingRrcDeVote
 功能描述  : 退出RRC投票
 输入参数  : ulVid: Vid
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -e438*/
BST_VOID BST_SRV_CAsCtrl::UsingRrcDeVote( BST_UINT32 ulVid )
{
    BST_SRV_VOTEID_STRU *pstVoteId;

    /*
     * 如果投票拆链已经禁止，那么立即返回
     */
    if ( BST_FALSE == m_VoteRrcEnableFlag )
    {
        BST_RLS_LOG( "BST_SRV_CAsCtrl::UsingRrcDeVote : EnableFlag is disabled.");
        return;
    }

    /*
     * 遍历资源表查找撤票人是否已经存在
     */
    for ( pstVoteId  = ( BST_SRV_VOTEID_STRU *)lstFirst( &m_stVoteList );
          BST_NULL_PTR != pstVoteId ;
          pstVoteId  = ( BST_SRV_VOTEID_STRU *)lstNext( (NODE *) pstVoteId ) )
    {
        if ( ulVid == pstVoteId->ulName )
        {
            /*
             * 找到后，不仅仅要从名单删除，同时析构申请资源
             */
            lstDelete( &m_stVoteList, (NODE *)pstVoteId );
            BST_OS_FREE( pstVoteId );
            break;
        }
    }
    BST_RLS_LOG3( "BST_SRV_CAsCtrl::UsingRrcDeVote, ProcId=%u, TaskId=u%, New Voting-Count=U%",
                ( ( ulVid>>16 ) & 0xFFFF ),
                ( ( ulVid ) & 0xFFFF ),
                lstCount( &m_stVoteList ) );

    /*
     * 如果撤票完成后，结果为无人，则启动定时机制，定时器超时后拆链
     */
    if ( 0 == lstCount( &m_stVoteList ) )
    {
        if ( !BST_OS_IsTimerValid ( m_ulFdTimerId ) )
        {
            return;
        }
        BST_OS_TimerStart ( m_ulFdTimerId, BST_AS_REL_RRC_TIMER_LEN );
    }
}
/*lint +e438*/
/*****************************************************************************
 函 数 名  : ProcRrcEvent
 功能描述  : 处理RRC状态变化事件
 输入参数  :  BST_UINT32 ulLength,  参数长度
              BST_VOID *pvData      参数（RRC状态）内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CAsCtrl::ProcRrcEvent( BST_UINT32 ulLength, BST_VOID *pvData )
{
    BST_BOOL                            bReportAllowedFlag;
    BST_UINT32                          ulTrxRptFlag;
    BST_DRV_STRU                       *pAsDriver;
    BST_SRV_VOTEID_STRU                *pstVoteId;
    BST_SRV_VOTEID_STRU                *pstVoteIdNext;
    BST_UINT32                          bOldRrcState;

    pAsDriver               = BST_DRV_AsGetDvcHandle();
    if( BST_OS_SIZEOF( BST_UINT32 ) != ulLength )
    {
        return;
    }

    if( BST_NULL_PTR == pvData )
    {
        return;
    }

    bOldRrcState            = m_ulRrcState;

    BST_OS_MEMCPY( &m_ulRrcState, pvData, ulLength );

    /*如果连接状态没有变化，则无需处理*/
    if ( BST_AS_IsRrcConnected( bOldRrcState ) == BST_AS_IsRrcConnected( m_ulRrcState ) )
    {
        return;
    }

    /* 如果当前进入连接态，则立刻停止禁止上报定时器*/
    if ( BST_TRUE == BST_AS_IsRrcConnected( m_ulRrcState ) )
    {
        if ( BST_OS_IsTimerValid ( m_ulReportTimerId ) )
        {
            BST_OS_TimerStop( m_ulReportTimerId );
        }
        return;
    }

    /*
     * 下面为退出连接态过程，首先初始化投票使能开关
     */
    m_VoteRrcEnableFlag     = BST_TRUE;

    BST_RLS_LOG ( "BST_SRV_CAsCtrl::ProcRrcEvent : BST_AS_RRC_RELEASED EnableFlag is TRUE.");

    /*
     * 清除投票名单中全部资源
     */
    for ( pstVoteId = ( BST_SRV_VOTEID_STRU *)lstFirst( &m_stVoteList );
          BST_NULL_PTR != pstVoteId ;
          pstVoteId  = pstVoteIdNext )
    {
        pstVoteIdNext       = ( BST_SRV_VOTEID_STRU *)lstNext( (NODE *) pstVoteId );
        lstDelete( &m_stVoteList, (NODE *)pstVoteId );
        BST_OS_FREE( pstVoteId );
    }

    /*
     * 允许底层上报数据收发指示，默认不允许CP->AP上报消息
     */
    ulTrxRptFlag            = BST_TRUE;
    bReportAllowedFlag      = BST_TRUE;

    pAsDriver->pfIoCtrl( BST_DRV_CMD_SET_TX_ENABLE, &ulTrxRptFlag );
    pAsDriver->pfIoCtrl( BST_DRV_CMD_SET_RX_ENABLE, &ulTrxRptFlag );
    pAsDriver->pfIoCtrl( BST_DRV_CMD_GET_REPORT_FLAG, &bReportAllowedFlag );
    /*
     * 如果定时存在，那么暂时不允许上报，反之则打开开关，允许状态上报
     */
    if ( BST_OS_IsTimerValid ( m_ulReportTimerId )
     &&( BST_FALSE == bReportAllowedFlag ) )
    {
        BST_RLS_LOG( "BST_SRV_CAsCtrl::ProcRrcEvent: Report to AP will be Allowed after 3 Sec.");
        BST_OS_TimerStart( m_ulReportTimerId, BST_AS_REPORT_ALLOWED_TIMER_LEN );
    }
    return;
}

/*****************************************************************************
 函 数 名  : ProcDataTrs
 功能描述  : 处理数据收发指示事件
 输入参数  : ucTrsType  接收数据或者发送数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CAsCtrl::ProcDataTrs( BST_VOID )
{
    BST_DRV_STRU               *pAsDriver;
    BST_BOOL                    bReportAllowedFlag;
    BST_SRV_VOTEID_STRU        *pstVoteId;                     
    BST_SRV_VOTEID_STRU        *pstVoteIdNext;                     

    pAsDriver                   = BST_DRV_AsGetDvcHandle();
    bReportAllowedFlag          = BST_TRUE;
    m_VoteRrcEnableFlag         = BST_FALSE;

    for ( pstVoteId = ( BST_SRV_VOTEID_STRU *)lstFirst( &m_stVoteList );
          BST_NULL_PTR != pstVoteId ;
          pstVoteId  = pstVoteIdNext )
    {
        pstVoteIdNext           = ( BST_SRV_VOTEID_STRU *)lstNext( (NODE *) pstVoteId );
        lstDelete( &m_stVoteList, (NODE *)pstVoteId );
        BST_OS_FREE( pstVoteId );
    }

    if ( BST_OS_IsTimerValid ( m_ulReportTimerId ) )
    {
        BST_OS_TimerStop( m_ulReportTimerId );
    }

    /*
     * 通知底层，允许modem给AP上报事件
     */
    ( BST_VOID )pAsDriver->pfIoCtrl( BST_DRV_CMD_SET_REPORT_FLAG,&bReportAllowedFlag );
}
/*****************************************************************************
 函 数 名  : AsEventCallback
 功能描述  : 接入层事件处理回调函数
 输入参数  : enEvent: 事件
             ulLength: 参数长度
             pvData:事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CAsCtrl::AsEventCallback(
    BST_AS_EVT_ENUM_UINT32  enEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    switch( enEvent )
    {
        case BST_AS_EVT_L3_RRC_STATE:
            ProcRrcEvent( ulLength, pvData );
            break;

        case BST_AS_EVT_L3_AP_RX_RCV_IND:
            ProcDataTrs();
            break;

        case BST_AS_EVT_L3_AP_TX_SEND_IND:
            ProcDataTrs();
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : TimerExpired
 功能描述  : 定时器超时处理函数
 输入参数  : lId:定时器ID
             pvPara: 定时器相关的参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CAsCtrl::TimerExpired( BST_OS_TIMERID_T lId, BST_VOID* pvPara )
{
    BST_DRV_STRU                       *pAsDrvHandle;
    BST_BOOL                            bReportAllowedFlag;

    /*
     * 快速断链定时器到期，还是要检查名单中是否仍有使用者，是否允许拆链
     */
    if ( lId == m_ulFdTimerId )
    {
        if( ( 0 != lstCount( &m_stVoteList ) )
          ||( BST_FALSE == m_VoteRrcEnableFlag ) )
        {
            return;
        }

        pAsDrvHandle                    = BST_DRV_AsGetDvcHandle();
        if( BST_NULL_PTR == pAsDrvHandle->pfIoCtrl )
        {
            return;
        }
        pAsDrvHandle->pfIoCtrl( BST_DRV_CMD_RELEASE_RRC, BST_NULL_PTR );
        BST_RLS_LOG( "RRC Will Be released.");
    }
    /*
     * 上报控制定时器超时，则允许CP->AP正常上报AT事件
     */
    else if ( lId == m_ulReportTimerId )
    {
        pAsDrvHandle                    = BST_DRV_AsGetDvcHandle();
        bReportAllowedFlag              = BST_TRUE;
        if( BST_NULL_PTR != pAsDrvHandle->pfIoCtrl )
        {
            ( BST_VOID )pAsDrvHandle->pfIoCtrl( BST_DRV_CMD_SET_REPORT_FLAG,
                                                &bReportAllowedFlag );
        }
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_CAsCtrl
 功能描述  : 构造函数
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
BST_SRV_CAsCtrl::BST_SRV_CAsCtrl( BST_VOID )
    : BST_SRV_CAsRcver( BST_SRV_GetSysMsgHandle() ),
      m_ulFdTimerId( BST_OS_INVALID_TIMER_ID ),
      m_ulReportTimerId( BST_OS_INVALID_TIMER_ID )
{
    m_VoteRrcEnableFlag                 = BST_TRUE;
    m_ulFdTimerId                       = BST_OS_TimerCreateCpp( this,
                                                                 BST_NULL_PTR,
                                                                 BST_SRV_GetSysMsgHandle() );
    m_ulReportTimerId                   = BST_OS_TimerCreateCpp( this,
                                                                 BST_NULL_PTR,
                                                                 BST_SRV_GetSysMsgHandle() );
    m_ulRrcState                        = BST_RRC_STATE_BUTT;
    RegAsNotice( BST_AS_EVT_L3_RRC_STATE );
    RegAsNotice( BST_AS_EVT_L3_AP_RX_RCV_IND );
    RegAsNotice( BST_AS_EVT_L3_AP_TX_SEND_IND );
    lstInit( &m_stVoteList );
}

/*****************************************************************************
 函 数 名  : ~BST_SRV_CAsCtrl
 功能描述  : 析构函数
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
BST_SRV_CAsCtrl::~BST_SRV_CAsCtrl( BST_VOID )
{
    BST_RLS_LOG("BST_SRV_CAsCtrl destructor exception!");
}


