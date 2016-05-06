/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_EmailPacketProc.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2013年10月9日
  最近修改   :
  功能描述   : 邮箱的基类，包括设置账户信息以及开启邮箱代理
  函数列表   :

  修改历史   :
  1.日    期   : 2013年10月9日
    作    者   : d00173029
    修改内容   : 创建文件
  2.日    期   : 2014年4月17日
    作    者   : z00220931
    修改内容   :
******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_APP_EmailBaseProc.h"
#include "BST_APP_EmailPOP3.h"
#include "BST_APP_EmailIMAP.h"
#include "BST_APP_EmailExchange.h"
#include "BST_APP_EmailBox.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_TaskMng.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_APP_EMAILBASEPROC_CPP
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
函 数 名   : BST_APP_CEmailPacketProc
功能描述   : 构造函数,初始化成员变量
输入参数   : pstInAccountInfo: 账号信息
输出参数   : 无
返 回 值   : BST_VOID
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2013年10月9日
   作者    : d00173029
   修改内容: 新函数
*****************************************************************************/
BST_APP_CEmailPacketProc::BST_APP_CEmailPacketProc( const EMAIL_ACCOUNT_STRU *pstAccountInfo )
    : m_pstAccountInfo( const_cast<EMAIL_ACCOUNT_STRU *>(pstAccountInfo) )
{
    m_pstLastUID                        = BST_NULL_PTR;/*指针初始化*/
    m_pSyncSocket                       = BST_NULL_PTR;
    m_pcHostTask                        = BST_NULL_PTR;
    m_ulTimerId                         = BST_OS_INVALID_TIMER_ID;
    m_lServerState                      = BST_EMAIL_UNCONNECT;
    m_usRetryTimes                      = 0;
    m_usErrSocketTimes                  = 0;
}

/*****************************************************************************
函 数 名   : ~BST_APP_CEmailPacketProc
功能描述   : 析构函数
输入参数   : 无
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_APP_CEmailPacketProc::~BST_APP_CEmailPacketProc()
{
    if ( BST_NULL_PTR != m_pstLastUID )
    {
        BST_LIB_StrDelete( m_pstLastUID->pMailBoxFolder );
        BST_LIB_StrDelete( m_pstLastUID->pLastUid );
        BST_OS_FREE( m_pstLastUID );
    }
    if ( BST_NULL_PTR != m_pSyncSocket )
    {
        m_pSyncSocket->Close();
    }
    if ( !BST_OS_IsTimerValid(m_ulTimerId) )
    {
        return;
    }
    BST_OS_TimerRemove( m_ulTimerId );
    m_ulTimerId                         = BST_OS_INVALID_TIMER_ID;
    m_pstLastUID                        = BST_NULL_PTR;/*析构函数指针重新置空*/
    m_pSyncSocket                       = BST_NULL_PTR;
    m_pstAccountInfo                    = BST_NULL_PTR;
    m_pcHostTask                        = BST_NULL_PTR;
}

/*****************************************************************************
函 数 名   : InitEmailProc
功能描述   : 初始化
输入参数   : pTaskProp: 任务指针
输出参数   : 无
返 回 值   : FALSE 初始化失败
             TRUE  初始化成功
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年7月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_BOOL BST_APP_CEmailPacketProc::InitEmailProc( BST_CORE_CNPTask *pTaskProp )
{
    BST_OS_CTimerCb                    *pcTimerCb;
    BST_IP_CNetRcver                   *pNetReceiver;
    BST_CORE_CRegedit                  *pcRegedit;
    BST_IP_ERR_T                        enIpErr;
    BST_ERR_ENUM_UINT8                  enRtnVal;
    m_pstLastUID                        = ( BST_EMAIL_UID_INFO_STRU *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF( BST_EMAIL_UID_INFO_STRU ) );
    pcRegedit                           = BST_CORE_CRegedit::GetInstance();
    if ( BST_NULL_PTR == pcRegedit )
    {
        return BST_FALSE;
    }
    if ( BST_NULL_PTR == pTaskProp )
    {
        return BST_FALSE;
    }
    if ( BST_NULL_PTR == m_pstLastUID )
    {
        return BST_FALSE;
    }
    m_pstLastUID->pMailBoxFolder        = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    if ( BST_NULL_PTR == m_pstLastUID->pMailBoxFolder )
    {
        return BST_FALSE;
    }
    m_pstLastUID->pLastUid              = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    if ( BST_NULL_PTR == m_pstLastUID->pLastUid )
    {
        return BST_FALSE;
    }
    enRtnVal                            = pcRegedit->Regist( pTaskProp,
                                                             BST_PID_EMAIL_LAST_UID,
                                                             BST_OS_SIZEOF( BST_EMAIL_UID_INFO_STRU ),
                                                             m_pstLastUID );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_RLS_LOG1( "BST_APP_CEmailPacketProc::InitEmailProc enRtnVal=%d",
                      enRtnVal );
        return BST_FALSE;
    }
    m_pcHostTask                        = pTaskProp;
    m_pSyncSocket                       = pTaskProp->m_pSocket;

    /*
     *  创建定时器，注册接收回调函数
     */
    pNetReceiver                        = this;
    if ( BST_NULL_PTR == m_pSyncSocket )
    {
        return BST_FALSE;
    }

    enIpErr                             = m_pSyncSocket->IoCtrl( BST_SCKT_CMD_REG_CALLBACK,
                                                                 pNetReceiver );
    if ( BST_IP_ERR_OK != enIpErr )
    {
        BST_RLS_LOG( "BST_APP_CEmailPacketProc::InitEmailProc register callback error" );
        return BST_FALSE;
    }

    pcTimerCb                           = this;
    m_ulTimerId                         = BST_OS_TimerCreateCpp( pcTimerCb,
                                                                 BST_NULL_PTR,
                                                                 BST_SRV_GetTaskMsgHandle
                                                               ( pTaskProp->m_usProcId,
                                                                 pTaskProp->m_usTaskId ) );
    if ( !BST_OS_IsTimerValid(m_ulTimerId) )
    {
        BST_RLS_LOG( "BST_APP_CEmailPacketProc::InitEmailProc BST_OS_TimerCreateCpp error" );
        return BST_FALSE;
    }

    return BST_TRUE;
}

/*****************************************************************************
函 数 名   : TimerExpied
功能描述   : 定时器的回调函数
输入参数   : ulId: 定时器ID
             pvPara: 定时器参数
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_VOID BST_APP_CEmailPacketProc::TimerExpired(
    BST_OS_TIMERID_T ulId,
    BST_VOID        *pvPara )
{
    if( BST_EMAIL_UNCONNECT == m_lServerState )
    {
        FailProc( BST_ERR_SOCKET_CLSD );
    }
    else
    {
        FailProc( BST_APP_SERVER_TIMEOUT );
    }
    CloseConnection();
}

/*****************************************************************************
函 数 名   : EntryProc
功能描述   : 回调函数
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_VOID BST_APP_CEmailPacketProc::EntryProc( BST_VOID )
{
    BST_BOOL                            bRtnVal;

    BST_DBG_LOG( "BST_APP_CEmailPacketProc::EntryProc Called!" );
    ResetMachine();
    bRtnVal                             = CreateConnection();
    if ( BST_TRUE == bRtnVal )
    {
        if( !BST_OS_IsTimerValid(m_ulTimerId) )
        {
            return;
        }
        BST_DBG_LOG1( "BST_APP_CEmailPacketProc::EntryProc connecting...\n start timer %u", m_ulTimerId );
        BST_OS_TimerStart( m_ulTimerId, BST_APP_CONNECT_TIME_OUT );
    }
    else
    {
        FailProc( BST_ERR_UNREACHABLE );
        CloseConnection();
    }

    return;
}
/*****************************************************************************
函 数 名  : NewMailProc
功能描述  : 收到新邮件处理
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : d00173029
  修改内容: 新函数
*****************************************************************************/
BST_VOID BST_APP_CEmailPacketProc::NewMailProc( BST_VOID )
{
    if ( BST_NULL_PTR == m_pcHostTask )
    {
        BST_RLS_LOG( "BST_APP_CEmailPacketProc::NewMailProc m_pcHostTask=NULL" );
        return;
    }
    m_pcHostTask->Report( BST_NEW_EMAIL );
    BST_DBG_LOG2( "BST_APP_CEmailPacketProc::NewMailProc: New mail synced, ProcId=%u, TaskId=%u.",
                  m_pcHostTask->m_usProcId,  m_pcHostTask->m_usTaskId );
    m_usRetryTimes          = 0;
    m_usErrSocketTimes      = 0;
#ifndef BST_MODEM_SELF
    m_pcHostTask->Stop();
#endif
}
/*****************************************************************************
函 数 名  : FailProc
功能描述  : 出错异常处理
输入参数  : BST_ERR_ENUM_UINT8 enErrType    出错信息类型
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : d00173029
  修改内容: 新函数
*****************************************************************************/
BST_VOID BST_APP_CEmailPacketProc::FailProc( BST_ERR_ENUM_UINT8 enErrType )
{
    if ( BST_NULL_PTR == m_pcHostTask )
    {
        BST_RLS_LOG( "BST_APP_CEmailPacketProc::FailProc m_pcHostTask=NULL" );
        return;
    }
    BST_DBG_LOG4( "BST_APP_CEmailPacketProc::FailProc: Error=%u, ProcId=%u, TaskId=%u, State=%u.",
                 enErrType, m_pcHostTask->m_usProcId, m_pcHostTask->m_usTaskId, m_lServerState );
    if ( BST_APP_EMAIL_IsErgency( enErrType ) )
    {
        m_usRetryTimes      = BST_CON_FAIL_NUM;
    }
    else if ( BST_ERR_SOCKET_CLSD == enErrType )
    {
        BST_DBG_LOG1( "BST_APP_CEmailPacketProc::FailProc BST_ERR_SOCKET_CLSD times=%u",
                      m_usErrSocketTimes );
        m_usErrSocketTimes++;
    }
    else if ( BST_APP_SERVER_TIMEOUT != enErrType )
    {
        enErrType           = BST_EMAIL_OTHER_EXCEPIONT;
    }
    else
    {
    }
#ifndef BST_MODEM_SELF
    if ( m_usRetryTimes >= BST_CON_FAIL_NUM )
    {
        if ( m_usErrSocketTimes >= m_usRetryTimes )
        {
            enErrType       = BST_EMAIL_NOT_SUPPORT;
        }
        BST_DBG_LOG("BST_APP_CEmailPacketProc::FailProc: Retry exceed MAX!");
        ( BST_VOID )m_pcHostTask->Report( enErrType );
        m_usRetryTimes      = 0;
        m_usErrSocketTimes  = 0;
        m_pcHostTask->Suspend();
    }
    else
#endif
    {
        m_usRetryTimes++;
        BST_DBG_LOG2( "BST_APP_CEmailPacketProc::FailProc, RetryTimes++=%u, ErrSocketTimes=u%",
                      m_usRetryTimes, m_usErrSocketTimes );
    }
    if( BST_OS_IsTimerValid(m_ulTimerId) )
    {
        BST_OS_TimerStop( m_ulTimerId );
    }

    m_pcHostTask->Finished();
    BST_DBG_UPDATE_ERR_NUM( m_pcHostTask->m_usProcId, m_pcHostTask->m_usTaskId );
}

/*****************************************************************************
函 数 名  : Connectd
功能描述  : 协议栈在连接到服务器后触发的回调函数
输入参数  : fd: pSockedHandle socket句柄
输出参数  : 无
返 回 值  : BST_IP_ERR_T 协议栈信息
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_IP_ERR_T BST_APP_CEmailPacketProc::Connectd( BST_IP_CSocket *pcSocket )
{
    BST_ERR_ENUM_UINT8                  enErrMsg;

    if ( pcSocket != m_pSyncSocket )
    {
        BST_RLS_LOG("CEmailPacketProc::Connectd error m_pSyncSocket != pcSocket.");
        return BST_IP_ERR_ARG;
    }
    BST_DBG_LOG2( "Email ProcId=%u,TaskId=%u has connected!",
                  m_pcHostTask->m_usProcId, m_pcHostTask->m_usTaskId );
    if( BST_OS_IsTimerValid(m_ulTimerId) )
    {
        BST_OS_TimerStop( m_ulTimerId );
    }
    enErrMsg                            = FirstTrsProc();
    if( BST_NO_ERROR_MSG != enErrMsg )
    {
        FailProc( enErrMsg );
        CloseConnection();
        return BST_IP_ERR_VAL;
    }
    return BST_IP_ERR_OK;
}

/*****************************************************************************
函 数 名  : Received
功能描述  : 协议栈接收到数据后触发的回调函数
输入参数  : pSockedHandle socket: 句柄
            pucData: 数据指针
            usLength: 数据长度
输出参数  : 无
返 回 值  : BST_IP_ERR_T: 协议栈状态信息
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_IP_PKTPROC_MODE_ENUM BST_APP_CEmailPacketProc::Received(
        BST_IP_CSocket     *pcSocket,
        const BST_UINT8    *const pucData,
        const BST_UINT16    usLength )
{
    BST_ERR_ENUM_UINT8                  enRtnVal;

    BST_ASSERT_NULL_RTN( pucData, BST_IP_PKT_REMOVE_PROC );
    BST_ASSERT_0_RTN( usLength, BST_IP_PKT_REMOVE_PROC );
    BST_ASSERT_NULL_RTN( m_pSyncSocket, BST_IP_PKT_REMOVE_PROC );

    if ( pcSocket != m_pSyncSocket )
    {
        return BST_IP_PKT_REMOVE_PROC;
    }

    if( BST_OS_IsTimerValid(m_ulTimerId) )
    {
        BST_OS_TimerStop( m_ulTimerId );
    }

    enRtnVal                            = ParseResponse( ( BST_UINT8 *)( pucData ), usLength );
    if ( BST_NO_ERROR_MSG == enRtnVal )
    {
        enRtnVal                        = RunStateMachine();
    }
    switch( enRtnVal )
    {
        /*
         *No need to break after "BST_NEW_EMAIL", It's also a type of NO_ERR,
         *If the state machine is QUITED,then we can Close.Finish.Reset.
         */
        case BST_NEW_EMAIL:
            NewMailProc();
            if( BST_EMAIL_QUITED == m_lServerState )
            {
                CloseAndFinish();
                BST_DBG_UPDATE_SUC_NUM( m_pcHostTask->m_usProcId, m_pcHostTask->m_usTaskId );
            }
            break;

        case BST_NO_ERROR_MSG:
            if( BST_EMAIL_QUITED == m_lServerState )
            {
                CloseAndFinish();
                m_usRetryTimes          = 0;
                m_usErrSocketTimes      = 0;
                BST_DBG_UPDATE_SUC_NUM( m_pcHostTask->m_usProcId, m_pcHostTask->m_usTaskId );
            }
            break;

        default:
            FailProc( enRtnVal );
            CloseConnection();
            break;
    }

    return BST_IP_PKT_REMOVE_PROC;
}

/*****************************************************************************
函 数 名   : Closed
功能描述   : Remote端远程关闭了Socket
输入参数  :  fd: pSockedHandle socket句柄
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : d00173029
   修改内容: 新函数
*****************************************************************************/
BST_VOID BST_APP_CEmailPacketProc::IpErr( BST_IP_CSocket *pcSocket, BST_IP_ERR_T InIpErrMsg )
{
    /*
     * 正常Closed发生之后，客户端也会进行CloseConnection，
     * 将PCB释放，所以也要关掉定时器，以免定时器超时再次释放PCB
     */
    if( BST_OS_IsTimerValid(m_ulTimerId) )
    {
        BST_OS_TimerStop( m_ulTimerId );
    }
    if ( BST_NULL_PTR == m_pcHostTask )
    {
        return;
    }
    if ( pcSocket != m_pSyncSocket )
    {
        return;
    }
    BST_DBG_LOG3("BST_APP_CEmailPacketProc::IpErr ProcId=%u,TaskId=%u, ErrorId=%d",\
                 m_pcHostTask->m_usProcId,m_pcHostTask->m_usTaskId, InIpErrMsg );
    if( ( BST_EMAIL_UNCONNECT == m_lServerState )
    &&( ( BST_IP_ERR_RST  == InIpErrMsg )
     || ( BST_IP_ERR_CLSD == InIpErrMsg )
     || ( BST_IP_ERR_CONN == InIpErrMsg ) ) )
    {
        FailProc( BST_ERR_SOCKET_CLSD );
    }
    BST_DBG_LOG("BST_APP_CEmailPacketProc::IpErr: current socket is closed" );
    m_pcHostTask->Finished();
}

/*****************************************************************************
函 数 名   : CloseAndFinish
功能描述   : 关闭socket连接并且调用Finished接口
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : BST_TRUE  成功
             BST_FALSE 失败
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_VOID BST_APP_CEmailPacketProc::CloseAndFinish( BST_VOID )
{
    CloseConnection();
    if ( BST_NULL_PTR == m_pcHostTask )
    {
        BST_RLS_LOG("BST_APP_CEmailPacketProc m_pcHostTask is NULL!");
        return;
    }
    m_pcHostTask->Finished();
}

/*****************************************************************************
函 数 名   : CloseConnection
功能描述   : 关闭socket连接
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : BST_TRUE  成功
             BST_FALSE 失败
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_VOID BST_APP_CEmailPacketProc::CloseConnection( BST_VOID )
{
    BST_IP_ERR_T                        lRtnVal;

    if ( BST_NULL_PTR == m_pSyncSocket )
    {
        return;
    }
    if ( BST_NULL_PTR == m_pcHostTask )
    {
        return;
    }
    BST_DBG_LOG3( "ProcId=%d, TaskId=%d, m_pSyncSocket=%p close",
                  m_pcHostTask->m_usProcId,
                  m_pcHostTask->m_usTaskId,
                  m_pSyncSocket );
    lRtnVal                             = m_pSyncSocket->Close();
    if ( BST_IP_ERR_OK != lRtnVal )
    {
        BST_RLS_LOG("BST_APP_Email close error.");
        return;
    }
}

/*****************************************************************************
函 数 名  : CreateConnection
功能描述  : 创建socket连接
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : BST_TRUE  成功
            BST_FALSE 失败
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_BOOL BST_APP_CEmailPacketProc::CreateConnection( BST_VOID )
{
    BST_IP_ERR_T                        enIpErr;

    if ( BST_NULL_PTR == m_pSyncSocket )
    {
        BST_RLS_LOG("CEmailPacketProc::CreateConnection m_pSyncSocket = NULL.");
        return BST_FALSE;
    }

    enIpErr                             = m_pSyncSocket->Socket( BST_SRV_GetTaskMsgHandle
                                                               ( m_pcHostTask->m_usProcId,
                                                                 m_pcHostTask->m_usTaskId ) );
    if ( BST_IP_ERR_OK != enIpErr )
    {
        BST_RLS_LOG1("m_pSyncSocket %p create socket error", m_pSyncSocket);
        return BST_FALSE;
    }
    enIpErr                             = m_pSyncSocket->Bind();
    if (BST_IP_ERR_OK != enIpErr )
    {
        BST_RLS_LOG1( "m_pSyncSocket %p bind error", m_pSyncSocket );
        return BST_FALSE;
    }

    enIpErr                             = m_pSyncSocket->Connect();
    if ( BST_IP_ERR_OK != enIpErr)
    {
        BST_RLS_LOG1( "m_pSyncSocket %p connect error", m_pSyncSocket );
        return BST_FALSE;
    }

    return BST_TRUE;
}

/*****************************************************************************
函 数 名  : SendCommand
功能描述  : 发送邮箱协议的命令
输入参数  : cmd: 发送的命令指针
            length: 发送的命令长度
输出参数  : 无
返 回 值  : BST_ERR_ENUM_UINT8  
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailPacketProc::SendCommand(
    const BST_UINT8 *pucCmd,
    BST_UINT16       usLength )
{
    BST_IP_ERR_T                        lRtnVal;

    if ( BST_NULL_PTR == pucCmd )
    {
        BST_RLS_LOG( "BST_APP_CEmailPacketProc::SendCommand pucCmd=NULL");
        return BST_ERR_INVALID_PTR;
    }
    if ( 0 == usLength )
    {
        BST_RLS_LOG( "BST_APP_CEmailPacketProc::SendCommand usLength=0");
        return BST_ERR_PAR_LEN;
    }
    if ( BST_NULL_PTR == m_pSyncSocket )
    {
        BST_RLS_LOG( "BST_APP_CEmailPacketProc::SendCommand m_pSyncSocket=NULL");
        return BST_ERR_TASK_REMOVED;
    }

    lRtnVal                     = m_pSyncSocket->Write( ( BST_UINT8 *)(pucCmd), usLength,
                                                        BST_IP_BSTT_DATA, BST_IP_SEND_FLAG_VOID );
    if ( BST_IP_ERR_OK != lRtnVal )
    {
        BST_RLS_LOG1( "BST_APP_CEmailPacketProc::SendCommand Write lRtnVal=%d",
                     lRtnVal );
        return BST_ERR_UNREACHABLE;
    }
    if( !BST_OS_IsTimerValid(m_ulTimerId) )
    {
        return BST_NO_ERROR_MSG;
    }
    BST_DBG_LOG1("have sent data,waiting response ....\n start timer %u", m_ulTimerId );
    BST_OS_TimerStart( m_ulTimerId, BST_APP_RX_TIME_OUT );
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
函 数 名   : IsBasicConfigOk
功能描述   : 判断基本配置是否完成
输入参数   : 无
输出参数   : 无
返 回 值   : FALSE 配置失败 TRUE 配置成功
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_BOOL BST_APP_CEmailPacketProc::IsBasicConfigOk( BST_VOID ) const
{
    BST_DRV_STRU                       *pNetDrvHandle;
    BST_BOOL                            bNetState;

    pNetDrvHandle                       = BST_DRV_NetGetDvcHandle();
    pNetDrvHandle->pfIoCtrl( BST_DRV_CMD_GET_NET_STATE, &bNetState );

    if( ( BST_TRUE != pNetDrvHandle->ulIsInited )
     || ( BST_TRUE != bNetState ) )
    {
        BST_RLS_LOG("Email Box basic config is not OK: Net Device");
        return BST_FALSE;
    }

    if ( BST_NULL_PTR == m_pstAccountInfo )
    {
        BST_RLS_LOG("Email Box basic config is not OK: m_pstAccountInfo");
        return BST_FALSE;
    }

    if ( BST_NULL_PTR == m_pSyncSocket )
    {
        BST_RLS_LOG("Email Box basic config is not OK: m_pSyncSocket");
        return BST_FALSE;
    }

    if ( !BST_LIB_IsStringInit( m_pstAccountInfo->pUserName ) )
    {
        BST_RLS_LOG("Email Box basic config is not OK: pUserName");
        return BST_FALSE;
    }

    if ( !BST_LIB_IsStringInit( m_pstAccountInfo->pPassWord ) )
    {
        BST_RLS_LOG("Email Box basic config is not OK: pPassWord");
        return BST_FALSE;
    }

    if ( BST_APP_ENCRP_INVALID_TYPE == m_pstAccountInfo->enEcryptionType )
    {
        BST_RLS_LOG("Email Box basic config is not OK: enEcryptionType_invalid");
        return BST_FALSE;
    }

    if ( BST_APP_ENCRP_MODE_BUTT <= m_pstAccountInfo->enEcryptionType )
    {
        BST_RLS_LOG("Email Box basic config is not OK: enEcryptionType_but");
        return BST_FALSE;
    }

    return BST_TRUE;
}

/*****************************************************************************
函 数 名  : BST_APP_CEmailBox
功能描述  : 构造函数
输入参数  : ProcID: 类型id
            TaskID: 任务id
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数    :
修改历史    :
  1.日期    :
    作者    :
    修改内容:
*****************************************************************************/
BST_APP_CEmailBox::BST_APP_CEmailBox(
    BST_PROCID_T    usProcID,
    BST_TASKID_T    usTaskID )
    : BST_CORE_CNPTask( usProcID, usTaskID ),
      m_pstAccountInfo( BST_NULL_PTR ),
      m_PacktStrategy( BST_NULL_PTR )
{
    BST_CORE_CRegedit           *pcRegedit;
    BST_CTask                   *pTask;
    BST_ERR_ENUM_UINT8          enRtnVal;

    pcRegedit                   = BST_CORE_CRegedit::GetInstance();
    m_pstAccountInfo            = ( EMAIL_ACCOUNT_STRU *)BST_OS_MALLOC(
                                   BST_OS_SIZEOF(EMAIL_ACCOUNT_STRU) );
    pTask                       = this;

    if( BST_NULL_PTR == pcRegedit )
    {
        return;
    }

    if( BST_NULL_PTR == m_pstAccountInfo )
    {
        return;
    }
    m_pstAccountInfo->pUserName = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    m_pstAccountInfo->pPassWord = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    m_pstAccountInfo->pCipherKey= BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    if ( BST_NULL_PTR == m_pstAccountInfo->pUserName )
    {
        BST_RLS_LOG( "m_pstAccountInfo->pUserName=NULL" );
        return;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo->pPassWord )
    {
        BST_RLS_LOG( "m_pstAccountInfo->pPassWord=NULL" );
        return;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo->pCipherKey )
    {
        BST_RLS_LOG( "m_pstAccountInfo->pCipherKey=NULL" );
        return;
    }
    m_pstAccountInfo->enEcryptionType = BST_APP_ENCRP_NO_TYPE;
    m_pstAccountInfo->enMbxType       = MBX_TYPE_INVALID;
    m_pstAccountInfo->enSyncType      = SYNC_INTERVAL;/*默认是interval*/
    m_EmailCfgFlag                    = BST_EMAIL_CFGFLG_NONE;

    enRtnVal                          = pcRegedit->Regist(
                                            pTask,
                                            BST_PID_EMAIL_ACCOUNT,
                                            m_pstAccountInfo->pUserName->usUsed,
                                            m_pstAccountInfo->pUserName->pData );
    BST_ASSERT_NORM( BST_NO_ERROR_MSG != enRtnVal );
    enRtnVal                          = pcRegedit->Regist(
                                            pTask,
                                            BST_PID_EMAIL_PASSWORD,
                                            m_pstAccountInfo->pPassWord->usUsed,
                                            m_pstAccountInfo->pPassWord->pData );
    BST_ASSERT_NORM( BST_NO_ERROR_MSG != enRtnVal );
    enRtnVal                          = pcRegedit->Regist(
                                            pTask,
                                            BST_PID_CIPHER_MODE,
                                            BST_OS_SIZEOF(m_pstAccountInfo->enEcryptionType),
                                            &m_pstAccountInfo->enEcryptionType );
    BST_ASSERT_NORM( BST_NO_ERROR_MSG != enRtnVal );
    enRtnVal                            = pcRegedit->Regist(
                                            pTask,
                                            BST_PID_CIPHER_CODE,
                                            m_pstAccountInfo->pCipherKey->usUsed,
                                            m_pstAccountInfo->pCipherKey->pData );
    BST_ASSERT_NORM( BST_NO_ERROR_MSG != enRtnVal );
    enRtnVal                            = pcRegedit->Regist(
                                            pTask,
                                            BST_PID_EMAIL_PROTOCOL_TYPE,
                                            BST_OS_SIZEOF( m_pstAccountInfo->enMbxType ),
                                            &m_pstAccountInfo->enMbxType );
    BST_ASSERT_NORM( BST_NO_ERROR_MSG != enRtnVal );
    enRtnVal                            = pcRegedit->Regist(
                                            pTask,
                                            BST_PID_EMAIL_SYNC_TYPE,
                                            BST_OS_SIZEOF( m_pstAccountInfo->enSyncType ),
                                            &m_pstAccountInfo->enSyncType );
    BST_ASSERT_NORM( BST_NO_ERROR_MSG != enRtnVal );
}

/****************************************************************************
函 数 名   : ~BST_APP_CEmailBox
功能描述   : 析构函数,释放构造函数中申请的内存。
             注意new->delete,malloc->free的对应关系
输入参数   : BST_VOID
输出参数   : 无
返 回 值   :
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_APP_CEmailBox::~BST_APP_CEmailBox( BST_VOID )
{
    if ( BST_NULL_PTR == m_pstAccountInfo )
    {
        return;
    }

    BST_LIB_StrDelete( m_pstAccountInfo->pUserName );
    BST_LIB_StrDelete( m_pstAccountInfo->pPassWord );
    BST_LIB_StrDelete( m_pstAccountInfo->pCipherKey );

    BST_OS_FREE( m_pstAccountInfo );
    if ( BST_NULL_PTR != m_PacktStrategy )
    {
        delete m_PacktStrategy;
    }
}

/*****************************************************************************
函 数 名   : ConfigType
功能描述   : 配置邮箱的类型
输入参数   : pData 标识邮箱类型的数据
            usLen 数据的长度
输出参数   : 无
返 回 值   : 存储邮箱类型的地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 * BST_APP_CEmailBox::ConfigType(
    const BST_VOID *const pData,
    BST_UINT16      usLen )
{
    BST_CORE_CNPTask                    *pcNetTask;
    BST_BOOL                             bRtnVal;
    MAIL_BOX_TYPE_ENUM_UINT32            enPacketType;

    BST_ASSERT_NULL_RTN( pData, BST_NULL_PTR );
    BST_ASSERT_0_RTN( usLen, BST_NULL_PTR );
    if ( BST_EMAIL_IsInfoConfiged ( BST_EMAIL_CFGFLG_TYPE ) )
    {
        return BST_NULL_PTR;
    }
    BST_OS_MEMCPY( &enPacketType, pData, usLen );
    pcNetTask                            = this;

    if ( BST_NULL_PTR != m_PacktStrategy )
    {
        delete m_PacktStrategy;
    }
    BST_DBG_LOG1( "BST_APP_CEmailBox Config type:%d\n", enPacketType );

    switch ( enPacketType )
    {
        case MBX_TYPE_POP3:
            m_PacktStrategy             = new BST_APP_CEmailPOP3( m_pstAccountInfo );
            break;

        case MBX_TYPE_IMAP:
            m_PacktStrategy             = new BST_APP_CEmailIMAP( m_pstAccountInfo );
            break;

        case MBX_TYPE_EXCG:
            m_PacktStrategy             = new BST_APP_CEmailExchange( m_pstAccountInfo );
            break;

        default:
            m_PacktStrategy             = BST_NULL_PTR;
            break;
    }

    if ( BST_NULL_PTR == m_PacktStrategy )
    {
        return BST_NULL_PTR;
    }
    bRtnVal                             = m_PacktStrategy->InitEmailProc( pcNetTask );

    BST_ASSERT_NORM_RTN( (BST_FALSE == bRtnVal), BST_NULL_PTR );

    if ( BST_NULL_PTR == m_pstAccountInfo )
    {
        return BST_NULL_PTR;
    }

    m_pstAccountInfo->enMbxType         = enPacketType;
    BST_EMAIL_SetEmailConfigFlag ( BST_EMAIL_CFGFLG_TYPE );
    return (BST_UINT8 *)&m_pstAccountInfo->enMbxType;
}

/*****************************************************************************
函 数 名  : SetProtclType
功能描述  : 配置协议的类型
输入参数  : pData: 标识协议类型的数据指针
           usLen: 数据长度
输出参数  : 无
返 回 值  : BST_UINT8*
调用函数  :
被调函数    :
修改历史    :
    1.日期  :
      作者    :
      修改内容:
*****************************************************************************/
BST_UINT8 * BST_APP_CEmailBox::SetProtclType(
    const BST_VOID *const pData,
    BST_UINT16            usLen )
{
    BST_SCKT_TYPE_ENUM_UINT32   enSocketType;
    BST_IP_ERR_T                enIpErrMsg;

    BST_ASSERT_NULL_RTN( pData, BST_NULL_PTR );
    BST_ASSERT_0_RTN( usLen, BST_NULL_PTR );
    BST_OS_MEMCPY( &m_ProtolType, pData, usLen );

    switch ( m_ProtolType )
    {
        case BST_PRTC_TYPE_TCP_SHORT:
            enSocketType    = BST_SCKT_TYPE_TCP;
            break;
#ifdef BST_SSL_SUPPORT
        case BST_PRTC_TYPE_SSL:
            enSocketType    = BST_SCKT_TYPE_SSL;
            break;
#endif
        default:
            BST_RLS_LOG("SetProtclType Error ProtocolType!");
            break;
    }

    if( BST_NULL_PTR == m_pSocket )
    {
        return BST_NULL_PTR;
    }
    enIpErrMsg              = m_pSocket->IoCtrl ( BST_SCKT_CMD_DEF_TYPE,
                                                ( BST_VOID  *)&enSocketType );
    if( BST_IP_ERR_OK != enIpErrMsg )
    {
        return BST_NULL_PTR;
    }
    BST_SetConfigFlag( BST_CFGFLG_TYPE );
    return ( BST_UINT8 *)&m_ProtolType;
}

/*****************************************************************************
函 数 名  : SetUsername
功能描述  : 设置用户名
输入参数  : pucUserName: 用户名数据指针
            usLen: 用户名长度
输出参数  : 无
返 回 值  : BST_UINT8 *用户名存储的地址
调用函数  :
被调函数    :
修改历史    :
    1.日期  :
      作者    :z00220931
      修改内容:新增函数
*****************************************************************************/
BST_UINT8 * BST_APP_CEmailBox::SetUsername(
    BST_UINT8 *pucUserName,
    BST_UINT16 usLen ) const
{
    BST_ERR_ENUM_UINT8                  enRtnVal;
    BST_UINT8                          *pucRtnVal;

    if ( 0 == usLen )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == pucUserName )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo )
    {
        return BST_NULL_PTR;
    }

    if ( BST_NULL_PTR == m_pstAccountInfo->pUserName )
    {
        return BST_NULL_PTR;
    }

    enRtnVal        = BST_LIB_StrFill( m_pstAccountInfo->pUserName, pucUserName, usLen );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        return BST_NULL_PTR;
    }
    pucRtnVal       = (BST_UINT8 *)( m_pstAccountInfo->pUserName->pData );
    return pucRtnVal;
}

/*****************************************************************************
函 数 名   : SetPasswd
功能描述   : 设置密码
输入参数   : pucPasswd: 密码的指针
             usLen: 密码长度
输出参数   : 无
返 回 值   : BST_UINT8 *: 存储密码的地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 *BST_APP_CEmailBox::SetPasswd(
    BST_UINT8 *pucPasswd,
    BST_UINT16 usLen ) const
{
    BST_ERR_ENUM_UINT8                      enErrMsg;

    if ( 0 == usLen )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == pucPasswd )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo )
    {
        return BST_NULL_PTR;
    }

    if ( BST_NULL_PTR == m_pstAccountInfo->pPassWord )
    {
        return BST_NULL_PTR;
    }

    enErrMsg        = BST_LIB_StrFill(
                        m_pstAccountInfo->pPassWord, 
                        pucPasswd, 
                        usLen );
    if ( enErrMsg != BST_NO_ERROR_MSG )
    {
        return BST_NULL_PTR;
    }
    return ( BST_UINT8 *)(m_pstAccountInfo->pPassWord->pData);
}

/*****************************************************************************
函 数 名   : SetCipherkey
功能描述   : 设置加密算法的密钥
输入参数   : pucCipherKey: 密钥
             usLen: 密钥长度
输出参数   : 无
返 回 值   : BST_UINT8 *: 密钥存储的地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 * BST_APP_CEmailBox::SetCipherkey(
    BST_UINT8 *pucCipherKey,
    BST_UINT16 usLen ) const
{
    BST_ERR_ENUM_UINT8                      enErrMsg;

    if ( 0 == usLen )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == pucCipherKey )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo->pCipherKey )
    {
        return BST_NULL_PTR;
    }

    enErrMsg        = BST_LIB_StrFill( m_pstAccountInfo->pCipherKey,
                                       pucCipherKey, usLen );
    if ( enErrMsg != BST_NO_ERROR_MSG )
    {
        return BST_NULL_PTR;
    }
    return ( BST_UINT8 *)( m_pstAccountInfo->pCipherKey->pData );
}

/****************************************************************************
函 数 名   : SetEncryptType
功能描述   : 设置加密类型
输入参数   : pData: 标识加密类型数据的指针
            usLen: 数据的长度
输出参数   : 无
返 回 值   : BST_UINT8 *:存储加密类型的地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 *BST_APP_CEmailBox::SetEncryptType(
    const BST_VOID *const pData,
    BST_UINT16      usLen )
{
    BST_APP_ENCRP_MODE_ENUM_UINT32      enEncryptType;

    BST_ASSERT_NULL_RTN( pData, BST_NULL_PTR );
    BST_ASSERT_0_RTN( usLen, BST_NULL_PTR );

    BST_OS_MEMCPY( &enEncryptType, pData, usLen );

    if ( BST_APP_ENCRP_MODE_BUTT <= enEncryptType )
    {
        return BST_NULL_PTR;
    }
    if ( BST_APP_ENCRP_INVALID_TYPE == enEncryptType)
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo )
    {
        return BST_NULL_PTR;
    }

    m_pstAccountInfo->enEcryptionType   = enEncryptType;
    return (BST_UINT8 *)&m_pstAccountInfo->enEcryptionType;
}

/****************************************************************************
函 数 名   : SetSyncType
功能描述   : 设置exchange邮箱的同步类型，分为PUSH和周期性同步
输入参数   : pData: 标识同步类型的数据指针
            usLen: 数据长度
输出参数   : 无
返 回 值   : BST_UINT8 *:存储同步类型的地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 * BST_APP_CEmailBox::SetSyncType(
    const BST_VOID *const pData,
    BST_UINT16      usLen )
{
    SYNC_TYPE_ENUM_UINT32               enSyncType;

    BST_ASSERT_NULL_RTN( pData, BST_NULL_PTR );
    BST_ASSERT_0_RTN( usLen, BST_NULL_PTR );

    BST_OS_MEMCPY( &enSyncType, pData, usLen );

    if ( SYNC_TYPE_BUTT <= enSyncType )
    {
        return BST_NULL_PTR;
    }
    if ( SYNC_INVALID == enSyncType )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo )
    {
        return BST_NULL_PTR;
    }
    BST_DBG_LOG1( "SetSyncType In_SyncType: %d", enSyncType );
    m_pstAccountInfo->enSyncType        = enSyncType;
    return (BST_UINT8 *)&m_pstAccountInfo->enSyncType;
}
/****************************************************************************
函 数 名   : SetStrategyInfo
功能描述   : 设置不同Strategy所需要的独有的信息
输入参数   : enParamId: 设置的PID项的值
            usLen    : 数据长度
            pData    : 数据指针
输出参数   : 无
返 回 值   : BST_UINT8 *其他配置项的地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 * BST_APP_CEmailBox::SetStrategyInfo (
    BST_CORE_PID_ENUM_UINT16 enParamId,
    BST_UINT16         usLen,
    const BST_VOID    *const pData )
{
    BST_UINT8           *pucRtnPtr;

    BST_ASSERT_NULL_RTN( pData, BST_NULL_PTR );
    BST_ASSERT_0_RTN( usLen, BST_NULL_PTR );

    if ( BST_NULL_PTR == m_PacktStrategy )
    {
        return BST_NULL_PTR;
    }

    pucRtnPtr           = m_PacktStrategy->ConfigOtherInfo( enParamId, usLen, pData );

    return pucRtnPtr;
}
/****************************************************************************
函 数 名   : ConfigNoticeEx
功能描述   : 配置信息的入口函数，在此函数中分别调用具体的配置函数
输入参数   : enParamId   : 配置对应的PID
             usLen      : 数据长度
             pData      : 数据内容
             ulBaseCfged: 基础PID项设置的标志
             pucNewAddr : 存储新设置项的指针
输出参数   : 无
返 回 值   : BST_ERR_ENUM_UINT8
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailBox::PidConfiged(
    BST_CORE_PID_ENUM_UINT16 enParamId,
    BST_UINT16               usLen,
    const BST_VOID          *const pData,
    BST_UINT32               ulBaseCfged,
    BST_UINT8              **pucNewAddr)
{
    BST_ERR_ENUM_UINT8          enRtnVal;
    BST_UINT8                  *pucRptr;
    enRtnVal                    = BST_ERR_ILLEGAL_PARAM;
    pucRptr                     = BST_NULL_PTR;

    BST_ASSERT_NULL_RTN( pData, BST_ERR_ILLEGAL_PARAM );
    BST_ASSERT_0_RTN( usLen, BST_ERR_ILLEGAL_PARAM );
    switch ( enParamId )
    {
        case BST_PID_PROTOCOL_TYPE:
            pucRptr         = SetProtclType( pData, usLen );
            break;

        case BST_PID_EMAIL_ACCOUNT:
            pucRptr         = SetUsername(
                                static_cast<BST_UINT8 *>( const_cast<BST_VOID *>(pData) ),
                                usLen );
            break;

        case BST_PID_EMAIL_PASSWORD:
            pucRptr         = SetPasswd(
                                static_cast<BST_UINT8*>( const_cast<BST_VOID *>(pData) ),
                                usLen );
            break;

        case BST_PID_CIPHER_CODE:
            pucRptr         = SetCipherkey(
                                static_cast<BST_UINT8 *>( const_cast<BST_VOID *>(pData) ),
                                usLen );
            break;

        case BST_PID_CIPHER_MODE:
            pucRptr         = SetEncryptType( pData, usLen );
            break;

        case BST_PID_EMAIL_PROTOCOL_TYPE:
            pucRptr         = ConfigType( pData, usLen );
            break;

        case BST_PID_EMAIL_SYNC_TYPE:
            pucRptr         = SetSyncType( pData, usLen );
            break;

        default:
            pucRptr         = SetStrategyInfo( enParamId, usLen, pData );
            break;
    }
    SetStrategyInfo( enParamId, usLen, pData );
    if ( BST_NULL_PTR != pucRptr )
    {
        enRtnVal            = BST_NO_ERROR_MSG;
        *pucNewAddr         = pucRptr;
    }
    return enRtnVal;
}

/****************************************************************************
函 数 名  : Entry
功能描述  : 超时回调函数
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : BST_VOID
调用函数  :
被调函数  : TimerExpireProc
修改历史  :
1.日期    :
  作者    :
  修改内容: 新函数
*****************************************************************************/
BST_VOID BST_APP_CEmailBox::Entry( BST_VOID )
{
    BST_DBG_LOG( "Email Box base class called " );
    BST_BOOL                            bRtnVal;
    if ( BST_NULL_PTR == m_PacktStrategy )
    {
        BST_RLS_LOG("Entry strategy is not init");
        Finished();
        Suspend();
        return;
    }
    bRtnVal                             = m_PacktStrategy->IsConfigOk();

    if ( BST_TRUE != bRtnVal )
    {
        BST_RLS_LOG("Email Box configuration is not OK.");
        Finished();
        return;
    }

    BST_DBG_LOG3( "Email ProcId=%d,TaskId=%d,m_PacktStrategy=%p",
                  m_usProcId, m_usTaskId, m_PacktStrategy );
    m_PacktStrategy->EntryProc();
}
