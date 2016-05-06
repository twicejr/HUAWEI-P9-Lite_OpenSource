/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : HeartBeat.cpp
  版 本 号   : 初稿
  作    者   : l00242755
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : 实现长连接应用Modem代理的基本接口
  函数列表   :

  修改历史   :
  1.日    期   : 2013年12月9日
    作    者   : l00242755
    修改内容   : 创建文件
******************************************************************************/
#include "BST_APP_HeartBeat.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_TaskMng.h"
#include "BST_SRV_ChnlCtrl.h"
#include "BST_DSPP_AppLayer.h"
#include "BST_CORE_Schd.h"
#include "BST_SRV_Event.h"
#include "BST_DRV_LinkSta.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_APP_HEARTBEAT_CPP
static int ini_flag     = 0;
/*lint +e767*/
/*****************************************************************************
 函 数 名  : HeartBeat
 功能描述  : 构造函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
HeartBeat::HeartBeat( BST_PROCID_T usInProcID, BST_TASKID_T usInTaskID )
    : BST_CORE_CNPTask( usInProcID, usInTaskID ),
      BST_SRV_CAsRcver( BST_SRV_GetTaskMsgHandle( usInProcID, usInTaskID ) )
{
    m_pstHbPktContent                       = BST_NULL_PTR;
    m_ulHbSerNum                            = 0;
    m_ChnlTimerId                           = BST_OS_INVALID_TIMER_ID;
    m_stHbTxRetry.ulTimerId                 = BST_OS_INVALID_TIMER_ID;
    m_stHbTxRetry.usRetryNum                = 0;
    m_stHbTxRetry.stRetryInfo.ulMaxReTimes  = BST_HB_DEFAULT_RETRY_TIMES;
    m_stHbTxRetry.stRetryInfo.ulIntervals   = BST_APP_RX_TIME_OUT;
    m_pstChnlLinker                         = BST_NULL_PTR;
    m_ulIsDetector                          = BST_FALSE;
    m_ulIsReLinkEn                          = BST_FALSE;
    RegAsNotice( BST_AS_EVT_L3_NET_RANK );
}

/*****************************************************************************
 函 数 名  : ~HeartBeat
 功能描述  : 析构函数

 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
HeartBeat::~HeartBeat( BST_VOID )
{
    if ( BST_OS_IsTimerValid( m_stHbTxRetry.ulTimerId ) )
    {
        BST_OS_TimerRemove( m_stHbTxRetry.ulTimerId );
        m_stHbTxRetry.ulTimerId         = BST_OS_INVALID_TIMER_ID;
    }
    if ( BST_OS_IsTimerValid( m_ChnlTimerId ) )
    {
        BST_OS_TimerRemove( m_ChnlTimerId );
        m_ChnlTimerId                   = BST_OS_INVALID_TIMER_ID;
    }
    if ( BST_NULL_PTR == m_pstHbPktContent )
    {
        BST_RLS_LOG( "Memory leak occured" );
        return;
    }
    if ( BST_NULL_PTR != m_pstChnlLinker )
    {
        ChnlCtrlClear();
        BST_OS_FREE( m_pstChnlLinker );
    }
    if ( BST_NULL_PTR != m_pSocket )
    {
#if ( BST_OS_VER == BST_WIN32 && BST_VER_TYPE == BST_DBG_VER )
        m_pSocket->Close();
        ini_flag        = 0;
#else
        m_pSocket->CloneClose();
#endif
    }
    BST_LIB_StrDelete( m_pstHbPktContent->pFixedContent );
    BST_LIB_StrDelete( m_pstHbPktContent->pRespContent );
    BST_LIB_StrDelete( m_pstHbPktContent->pCipherKey );
    if ( BST_NULL_PTR != m_pstHbPktContent->pstSnInfoPkt )
    {
        BST_OS_FREE( m_pstHbPktContent->pstSnInfoPkt );
    }

    BST_OS_FREE( m_pstHbPktContent );
}

/*****************************************************************************
 函 数 名  : Entry
 功能描述  : 应用心跳间隔超时回调函数

 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID HeartBeat::Entry( BST_VOID )
{
    BST_IP_ERR_T                        lSockRtnVal;
    BST_ERR_ENUM_UINT8                  enRtnVal;
    BST_BOOL                            bRtnVal;
    BST_CORE_CPTask                    *pcPtask;
    BST_UINT32                          ulSocketEst;

    lSockRtnVal                         = BST_IP_ERR_OK;
    bRtnVal                             = BST_FALSE;

    if ( BST_FALSE == IsConfigOk() )
    {
        BST_DBG_LOG("HeartBeat not config");
        Finished();
        return;
    }

    switch ( m_ProtolType )
    {
        case BST_PRTC_TYPE_TCP_LONG:

#if ( BST_OS_VER == BST_WIN32 && BST_VER_TYPE == BST_DBG_VER )
            {
                if ( 0== ini_flag )
                {
                    ini_flag            = 1;
                    m_pSocket->Bind();
                    m_pSocket->Connect();
                    Finished();
                    return;
                }
            }
#endif
            if ( BST_TASK_STATE_START != GetState() )
            {
                BST_DBG_LOG("HeartBeat::Entry is not BST_TASK_STATE_START");
                pcPtask                 = this;
                BST_SRV_ApiSendPTaskEvent( pcPtask, BST_SRV_T2S_ACK_RESULT, BST_CORE_SCHD_ACK_SUC );
                return;
            }
            bRtnVal                     = SendHbPkt();
            if ( ( BST_TRUE == bRtnVal ) && ( BST_OS_IsTimerValid( m_stHbTxRetry.ulTimerId ) ) )
            {
                BST_OS_TimerStart( m_stHbTxRetry.ulTimerId, m_stHbTxRetry.stRetryInfo.ulIntervals );
                m_stHbTxRetry.usRetryNum
                                        = 0;
            }
            else
            {
                BST_RLS_LOG2( "Heartbeat::Entry ProcId=%d, TaskId=%d, Send Heartbeat packet failed",
                              m_usProcId, m_usTaskId );
                Finished();
                Suspend();
                ulSocketEst             = BST_APP_CONN_TYPE_CP_ERR_CLS;
                enRtnVal                = m_pExptReport->Report( BST_PID_LH_SOCKET_EST, 
                                            ( BST_UINT16 )BST_OS_SIZEOF(BST_UINT32), &ulSocketEst );

                ulSocketEst             = BST_APP_CONN_TYPE_BEST_CONN_POINT;
                enRtnVal                = m_pExptReport->Report( BST_PID_LH_SOCKET_EST, 
                                            ( BST_UINT16 )BST_OS_SIZEOF(BST_UINT32), &ulSocketEst );
                if ( BST_NO_ERROR_MSG != enRtnVal )
                {
                    BST_RLS_LOG3( "Heartbeat::Entry ProcId=%d, TaskId=%d, Entry Report Error: %u",
                                  m_usProcId, m_usTaskId, enRtnVal );
                }
                return;
            }
            break;

        case BST_PRTC_TYPE_TCP_SHORT:
            BST_ASSERT_NULL( m_pSocket );
            lSockRtnVal                 = m_pSocket->Bind();
            BST_ASSERT_NORM( BST_IP_ERR_OK != lSockRtnVal );
            lSockRtnVal                 = m_pSocket->Connect();
            BST_ASSERT_NORM( BST_IP_ERR_OK != lSockRtnVal );
            break;

        default:
            break;
    }
#if ( BST_OS_VER == BST_WIN32 && BST_VER_TYPE == BST_DBG_VER )
    Finished();
#endif
}
/*****************************************************************************
 函 数 名  : SendHbPkt
 功能描述  : 发送数据包到服务器

 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
/*lint -e438*/
BST_BOOL HeartBeat::SendHbPkt( BST_VOID )
{
    BST_UINT8               *pucSndData;
    BST_UINT16              usSndLength;
    BST_UINT16              usPktLength;
    BST_UINT8               *pucRtnVal;
    BST_IP_ERR_T            lRtnVal;

    pucSndData              = BST_NULL_PTR;
    lRtnVal                 = BST_IP_ERR_OK;

    usSndLength             = 0;

    if ( ( BST_NULL_PTR == m_pstHbPktContent ) || ( BST_NULL_PTR == m_pSocket ) )
    {
        return BST_FALSE;
    }

    usPktLength             = m_pstHbPktContent->usHbPktLength;
    pucSndData              = ( BST_UINT8 * )BST_OS_MALLOC( usPktLength );
    if ( BST_NULL_PTR == pucSndData )
    {
        return BST_FALSE;
    }

    pucRtnVal               = ComposeHbPkt( pucSndData, &usSndLength, usPktLength );
    if ( BST_NULL_PTR == pucRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::SendHbPkt ProcId=%d, TaskId=%d, Composing packet failed",
                      m_usProcId, m_usTaskId );
        BST_OS_FREE( pucSndData );
        return BST_FALSE;
    }

    lRtnVal                 = m_pSocket->Write( pucSndData, usSndLength,
                                                BST_IP_BSTT_DATA,
                                                BST_IP_SEND_FLAG_VOID );
    if ( BST_IP_ERR_OK != lRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::SendHbPkt ProcId=%d, TaskId=%d, socket writing failed",
                      m_usProcId, m_usTaskId );
        BST_OS_FREE( pucSndData );
        return BST_FALSE;
    }

#if ( BST_VER_TYPE == BST_RLS_VER )
    {
        BST_UINT16          i;
        for ( i = 0; i < usSndLength; i++ )
        {
            BST_DBG_LOG4( "Heartbeat::SendHbPkt ProcId=%d, TaskId=%d, Write Data:pucSndData[%d] = 0x%02x",
                          m_usProcId, m_usTaskId, i, pucSndData[i] );
        }
    }
#endif

    BST_DBG_LOG2( "Heartbeat::SendHbPkt ProcId=%d, TaskId=%d, heartbeat packet is sent",
                  m_usProcId, m_usTaskId );
    BST_OS_FREE( pucSndData );
    return BST_TRUE;
}
/*lint +e438*/
/*****************************************************************************
 函 数 名  : Connectd
 功能描述  : tcp_connect的回调函数

 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T HeartBeat::Connectd( BST_IP_CSocket *pcSocket )
{
    BST_ERR_ENUM_UINT8                  enRtnVal = BST_NO_ERROR_MSG;
#if ( BST_OS_VER == BST_WIN32 && BST_VER_TYPE == BST_DBG_VER )
    BST_BOOL                            bRtnVal;

    bRtnVal                             = BST_FALSE;
    if ( pcSocket != m_pSocket )
    {
        BST_RLS_LOG("HeartBeat::Connectd error m_pSocket != pcSocket.");
        return BST_IP_ERR_ARG;
    }

    BST_DBG_LOG2( "Heartbeat::Connectd ProcId=%d, TaskId=%d, Connection is built",
                  m_usProcId, m_usTaskId );
    if ( BST_PRTC_TYPE_TCP_SHORT != m_ProtolType )
    {
        return BST_IP_ERR_OK;
    }
    bRtnVal                             = SendHbPkt();
    if ( BST_TRUE != bRtnVal )
    {
        BST_RLS_LOG2( "Heartbeat::Connectd ProcId=%d, TaskId=%d, Send heartbeat packet Error",
                      m_usProcId, m_usTaskId );
    }
#endif
#ifdef BST_IP_REBUILD_IN_MODEM
    if( BST_TASK_STATE_MNTNING == GetState() )
    {    
        enRtnVal                        = ReportSocketProperty() )
        ProcEstState( BST_APP_CONN_TYPE_CP_NORMAL_EST );
    }
    if( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_RLS_LOG2( "Heartbeat::Connectd ProcId=%d, TaskId=%d, Get Property Error",
                      m_usProcId, m_usTaskId );
        return BST_IP_ERR_CLSD;
    }   
#endif
    return enRtnVal;
}

/*****************************************************************************
 函 数 名  : Received
 功能描述  : tcp_recv函数的回调函数
 输入参数  : fd      :socket句柄
            pucData :接收到的数据包
            usLength:接收到数据包的长度
 输出参数  : 无
 返 回 值  : BST_IP_PKTPROC_MODE_ENUM
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_IP_PKTPROC_MODE_ENUM HeartBeat::Received(
    BST_IP_CSocket     *pcSocket,
    const BST_UINT8    *const pucData,
    const BST_UINT16    usLength )
{
    BST_ERR_ENUM_UINT8              ucRtnVal;
    BST_CORE_CPTask                *pcPtask;

    ucRtnVal                        = BST_NO_ERROR_MSG;
    BST_DBG_LOG3( "HeartBeat::Received len,state,busy", usLength, GetState(),IsBusy() );
    if( BST_TASK_STATE_START != GetState() )
    {
        return BST_IP_PKT_REMOVE_PROC;
    }
    /*
     * 如果没有发过心跳包则判断数据肯定是push的数据，
     * 则直接转发给AP,防止push数据和心跳回复包一样发生误判
     */
    if ( BST_FALSE == IsBusy() )
    {
        Stop();
        BST_SRV_ApiSendPTaskEvent( this, BST_SRV_T2S_RUN_STOPED, 0 );
        ucRtnVal                = Report( BST_NOT_HEARTBEAT_PACK );
        if ( BST_NO_ERROR_MSG != ucRtnVal )
        {
            BST_RLS_LOG3( "HeartBeat::ParsePkt ProcId=%d,TaskId=%d, ParsePkt Report Error: %u",
                          m_usProcId, m_usTaskId, ucRtnVal );
        }
        return BST_IP_PKT_FORWARD_PROC;
    }
    if ( pcSocket != m_pSocket )
    {
        BST_RLS_LOG("HeartBeat::Received error m_pSocket != pcSocket.");
        return BST_IP_ERR_ARG;
    }

    Finished();
    if ( ( 0 == usLength ) || ( BST_NULL_PTR == pucData ) )
    {
        return BST_IP_PKT_REMOVE_PROC;
    }
    if ( BST_OS_IsTimerValid( m_stHbTxRetry.ulTimerId ) )
    {
        /**
         * 每次心跳都会启动超时定时，据此判断是否心跳发送引起
         */
        if( BST_FALSE == BST_OS_TimerIsStop( m_stHbTxRetry.ulTimerId ) )
        {
            pcPtask                 = this;
            BST_SRV_ApiSendPTaskEvent( pcPtask, BST_SRV_T2S_ACK_RESULT, BST_CORE_SCHD_ACK_SUC );
        }
        BST_OS_TimerStop( m_stHbTxRetry.ulTimerId );
        m_stHbTxRetry.usRetryNum    = 0;
    }

    ucRtnVal                        = ParsePkt( pucData, usLength );
    if ( BST_NO_ERROR_MSG == ucRtnVal )           /*说明是心跳包回复*/
    {
        return BST_IP_PKT_REMOVE_PROC;
    }
    return BST_IP_PKT_FORWARD_PROC;
}

/*****************************************************************************
 函 数 名  : Closed
 功能描述  : 解析接收到的数据包是否为非心跳数据包
 输入参数  : fd socket句柄
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID HeartBeat::IpErr ( BST_IP_CSocket *pcSocket, BST_IP_ERR_T InIpErrMsg )
{
    BST_ERR_ENUM_UINT8              ucRtnVal;
    BST_DSPP_CAppUlVc              *pstDsppUl;
    BST_CORE_CPTask                *pcPtask;

    if ( BST_NULL_PTR == m_pSocket)
    {
        return;
    }
    if( m_pSocket != pcSocket )
    {
        return;
    }
    ucRtnVal                        = BST_NO_ERROR_MSG;
    pstDsppUl                       = BST_DSPP_CAppUlVc::GetInstance();
    Finished();
    m_pSocket->Close();
    ProcEstState( BST_APP_CONN_TYPE_CP_ERR_CLS );
    if ( BST_OS_IsTimerValid( m_stHbTxRetry.ulTimerId ) )
    {
        /*只有在push心跳过程中出现socket断开或者服务器主动断开的场景，才通知探测器心跳失败*/
        if( (BST_FALSE == BST_OS_TimerIsStop( m_stHbTxRetry.ulTimerId ) )
           || ( BST_IP_ERR_CLSD == InIpErrMsg ))
        {
            BST_DBG_LOG3( "HeartBeat::notify detector task run failed,IpErr:%u",
                          m_usProcId, m_usTaskId,InIpErrMsg );
            pcPtask                 = this;
            BST_SRV_ApiSendPTaskEvent( pcPtask, BST_SRV_T2S_ACK_RESULT, BST_CORE_SCHD_ACK_ERR );
        }
        BST_OS_TimerStop( m_stHbTxRetry.ulTimerId );
        m_stHbTxRetry.usRetryNum    = 0;
    }

    BST_DBG_UPDATE_ERR_NUM( m_usProcId, m_usTaskId );
    /* 通知AP清除该Socket记录 */
    if( !BST_SRV_IsChnlEmpty( GetChnlInstance() ) )
    {
       /*前面已经上报过*/
        ucRtnVal                    = pstDsppUl->Report( BST_DSPP_FLG_CMD_CLOSE, m_usProcId, m_usTaskId );
        if ( BST_NO_ERROR_MSG != ucRtnVal )
        {
            BST_RLS_LOG3( "Heartbeat::Closed ProcId=%d, TaskId=%d, IpErr Report IpErr: %u",
                          m_usProcId, m_usTaskId, ucRtnVal );
        }
    }
    BST_DBG_LOG3( "HeartBeat::IpErr ProcId=%d, TaskId=%d, Connection is closed,IpErr:%u",
                  m_usProcId, m_usTaskId,InIpErrMsg );
}

/***************************************************************
 函 数 名   : Acked
 功能描述   : 处理Ack响应IP包事件
 输入参数   : 无
 输出参数   : 无
 返 回 值   : 无
 被调函数   :
 调用函数   :

 修改历史   :
 修改历史   :
 1.日    期 : 2015年05月10日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_VOID HeartBeat::Acked (
    BST_IP_CSocket             *pcSocket,
    const BST_UINT32            ulMinNumber,
    const BST_UINT32            ulMaxNumber )
{
    BST_SRV_CHNL_LINK_STRU     *pstChnlLinker;
    BST_DSPP_CAppUlVc          *pstDsppUl;
    BST_UINT32                  ulVoidProp = 0;
    BST_ERR_ENUM_UINT8          enRtnVal;
    BST_IP_ERR_T                enIpErrMsg  = BST_IP_ERR_CONN;

    pstChnlLinker               = GetChnlInstance();
    if( BST_SRV_IsChnlEmpty( pstChnlLinker ) )
    {
        return;
    }
    enRtnVal                    = BST_SRV_CHNL_Acked( pstChnlLinker, ulMinNumber, ulMaxNumber );
    if( BST_ERR_SOCKET_CLSD == enRtnVal )/*Socket is closed*/
    {
        ChnlCtrlClose();
        return;
    }

    if( BST_SRV_IsChnlEmpty( pstChnlLinker ) )
    {
        pstDsppUl               = BST_DSPP_CAppUlVc::GetInstance();
        pstDsppUl->Report( BST_DSPP_FLG_CMD_SEND, m_usProcId, m_usTaskId );
        pstChnlLinker->ulIsPropSet
                                = BST_FALSE;
        Finished();

        ulVoidProp              = 0;
        enIpErrMsg              = m_pSocket->IoCtrl ( BST_SCKT_CMD_SYNC_PROPERTY_STOP,
                                                    ( BST_VOID  *)&ulVoidProp );
        if( BST_IP_ERR_OK != enIpErrMsg )
        {
            BST_RLS_LOG1( "HeartBeat::ChnlCtrlSend SYNC_PROPERTY_STOP enIpErrMsg=%d",
                      enIpErrMsg );
        }
        BST_DBG_LOG("ChnlCtrlSend_TASK SYNC_PROPERTY_STOP1" );
        enRtnVal                = m_pExptReport->Report ( BST_PID_SYNC_PROPERTY_STOP,
                                                          BST_OS_SIZEOF(BST_UINT32),
                                                         &ulVoidProp );
        if ( BST_NO_ERROR_MSG != enRtnVal )
        {
            BST_RLS_LOG1( "HeartBeat::ChnlCtrlSend SYNC_PROPERTY_STOP enRtnVal=%d",
                      enRtnVal );
        }
    }
}

/*****************************************************************************
 函 数 名  : ParsePkt
 功能描述  : 解析接收到的数据包是否为非心跳数据包
 输入参数  : pucRcvData: 接收到的数据的指针
            usLength  : 接收到的数据长度
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_ERR_ENUM_UINT8 HeartBeat::ParsePkt(
    const BST_UINT8    *pucRcvData,
    const BST_UINT16    usLength )
{
    BST_UINT16                  usRespLength;
    BST_UINT8                  *pucRespTmp;
    BST_BOOL                    bRtnVal;
    BST_ERR_ENUM_UINT8          ucRtnVal;
    usRespLength                = 0;
    bRtnVal                     = BST_FALSE;
    ucRtnVal                    = BST_NO_ERROR_MSG;
    pucRespTmp                  = BST_NULL_PTR;

    if ( ( BST_NULL_PTR == pucRcvData ) || ( 0 == usLength ) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    if ( BST_NULL_PTR == m_pstHbPktContent )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_NULL_PTR == m_pstHbPktContent->pRespContent )
    {
        return BST_ERR_INVALID_PTR;
    }
    usRespLength                = m_pstHbPktContent->pRespContent->usUsed;
    pucRespTmp                  = ( BST_UINT8 * )m_pstHbPktContent->pRespContent->pData;

    bRtnVal                     = IsRespPkt( pucRcvData, pucRespTmp, usLength, usRespLength );

    if ( BST_FALSE == bRtnVal )
    {
        BST_RLS_LOG2( "HeartBeat::ParsePkt ProcId=%d,TaskId=%d, This is not a heartbeat reply",
                       m_usProcId, m_usTaskId );
        Stop();
        BST_SRV_ApiSendPTaskEvent( this, BST_SRV_T2S_RUN_STOPED, 0 );
        ucRtnVal                = Report( BST_NOT_HEARTBEAT_PACK );
        if ( BST_NO_ERROR_MSG != ucRtnVal )
        {
            BST_RLS_LOG3( "HeartBeat::ParsePkt ProcId=%d,TaskId=%d, ParsePkt Report Error: %u",
                          m_usProcId, m_usTaskId, ucRtnVal );
        }

        return BST_NOT_HEARTBEAT_PACK;
    }
    else
    {
        BST_RLS_LOG2( "HeartBeat::ParsePkt ProcId=%d, TaskId=%d, This is a heartbeat reply.",
                      m_usProcId, m_usTaskId );
        if ( BST_HB_IsHbSnUsed( m_pstHbPktContent ) )
        {
            m_ulHbSerNum       += m_pstHbPktContent->pstSnInfoPkt->ulSnStep;
        }

        BST_DBG_UPDATE_SUC_NUM( m_usProcId, m_usTaskId );
        return BST_NO_ERROR_MSG;
    }
}

/*****************************************************************************
 函 数 名  : ComposeHbPkt
 功能描述  : 根据AP侧下发的心跳包信息，在应用中组包
 输入参数  : 无
 输出参数  : pucCmpsData:需要发送的心跳包
             pusSndLength:心跳包的长度
 返 回 值  : BST_BOOL
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
/*lint -e438 -e429*/
BST_UINT8 *HeartBeat::ComposeHbPkt(
    BST_UINT8  *pucCmpsData,
    BST_UINT16 *pusSndLen,
    BST_UINT16  usCmpsLen )
{
    BST_UINT16                      usCopyedLen;
    BST_UINT16                      usFixedLen;
    SERNO_HB_INFO_STRU             *pstHbSnInfo;
    BST_UINT8                      *pucFixedContent;
    BST_UINT8                      *ucCharTmp;
    BST_UINT32                      ulHbSnNum;

    pstHbSnInfo                     = BST_NULL_PTR;
    pucFixedContent                 = BST_NULL_PTR;
    ucCharTmp                       = (BST_UINT8 *)(&ulHbSnNum);
    usCopyedLen                     = 0;

    BST_ASSERT_0_RTN( usCmpsLen, BST_NULL_PTR );
    BST_ASSERT_NULL_RTN( pucCmpsData, BST_NULL_PTR );
    BST_ASSERT_NULL_RTN( pusSndLen, BST_NULL_PTR );
    BST_ASSERT_NULL_RTN( m_pstHbPktContent, BST_NULL_PTR );
    BST_ASSERT_NULL_RTN( m_pstHbPktContent->pFixedContent, BST_NULL_PTR );
    BST_ASSERT_NULL_RTN( m_pstHbPktContent->pstSnInfoPkt, BST_NULL_PTR );

    usFixedLen                      = m_pstHbPktContent->pFixedContent->usUsed;
    pucFixedContent                 = ( BST_UINT8 *)( m_pstHbPktContent->pFixedContent->pData);

    if ( usCmpsLen < usFixedLen )            /*内存拷贝越界检查*/
    {
        BST_RLS_LOG2( "HeartBeat::ComposeHbPkt ProcId=%d, TaskId=%d, out of memory",
                      m_usProcId, m_usTaskId );
        return BST_NULL_PTR;
    }
    BST_OS_MEMCPY( pucCmpsData, pucFixedContent, usFixedLen );
    usCopyedLen                    += usFixedLen;

    if( BST_HB_IsHbSnUsed( m_pstHbPktContent ) )
    {
        if ( usCmpsLen < ( usCopyedLen + BST_OS_SIZEOF( m_ulHbSerNum ) ) )
        {
            BST_RLS_LOG2( "HeartBeat::ComposeHbPkt ProcId=%d, TaskId=%d, out of memory",
                          m_usProcId, m_usTaskId );
            return BST_NULL_PTR;
        }

        pstHbSnInfo                 = m_pstHbPktContent->pstSnInfoPkt;
        if ( !BST_HB_IsHbSeqValid( m_ulHbSerNum, pstHbSnInfo ) )
        {
            m_ulHbSerNum            = pstHbSnInfo->ulSnMin;
        }

        BST_HB_U32TOU8( ucCharTmp[3], ucCharTmp[2], ucCharTmp[1], ucCharTmp[0], m_ulHbSerNum );
        BST_OS_MEMCPY( pucCmpsData + usCopyedLen, &ucCharTmp[0], BST_OS_SIZEOF( m_ulHbSerNum ) );
        usCopyedLen                += BST_OS_SIZEOF( m_ulHbSerNum );
    }

   *pusSndLen                       = usCopyedLen;
    BST_DBG_LOG2( "Heartbeat::ComposeHbPkt ProcId=%d, TaskId=%d, Composing Packet finished",
                  m_usProcId, m_usTaskId );
    return pucCmpsData;
}
/*lint +e438 +e429*/
/*****************************************************************************
 函 数 名  : IsRespPkt
 功能描述  : 解析接收到的数据包是否为非心跳数据包
 输入参数  : pucData:接收到的心跳回复包，
             pRespData:待比较的数据包，
             usDataLen:接收到心跳包的长度，
             usRespLen:待比较心跳包的长度
 输出参数  : 无
 返 回 值  : BST_BOOL
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年12月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_BOOL HeartBeat::IsRespPkt(
    const BST_UINT8 *pucData,
    BST_UINT8 *pucRespData,
    BST_UINT16 usDataLen,
    BST_UINT16 usRespLen ) const
{
    if ( ( 0 == usDataLen )
      || ( 0 == usRespLen ) )
    {
        return BST_FALSE;
    }
    if ( ( BST_NULL_PTR == pucData )
      || ( BST_NULL_PTR == pucRespData ) )
    {
        return BST_FALSE;
    }
    if ( usDataLen != usRespLen )
    {
        return BST_FALSE;
    }

    if ( 0 != BST_OS_MEMCMP( pucData, pucRespData, usDataLen ) )
    {
        return BST_FALSE;
    }

    return BST_TRUE;
}

/*****************************************************************************
 函 数 名  : IsConfigOk
 功能描述  : 判断配置是否完成
 输入参数  :无
 输出参数  :无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_BOOL HeartBeat::IsConfigOk( BST_VOID ) const
{
    BST_DRV_STRU                       *pNetDrvHandle;
    BST_BOOL                            bNetState;

    pNetDrvHandle                       = BST_DRV_NetGetDvcHandle();
    pNetDrvHandle->pfIoCtrl( BST_DRV_CMD_GET_NET_STATE, &bNetState );

    if( ( BST_TRUE != pNetDrvHandle->ulIsInited )
     || ( BST_TRUE != bNetState ) )
    {
        BST_RLS_LOG2( "HeartBeat::IsConfigOk ProcId=%d, TaskId=%d, config is not OK: Net Device",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }
    if ( BST_NULL_PTR == m_pstHbPktContent )
    {
        BST_RLS_LOG2( "HeartBeat::IsConfigOk ProcId=%d, TaskId=%d, config is not OK: m_pstHbPktContent",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    if ( !BST_LIB_IsStringInit(m_pstHbPktContent->pFixedContent) )
    {
        BST_RLS_LOG2( "HeartBeat::IsConfigOk ProcId=%d, TaskId=%d, config is not OK: pFixedContent",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    if ( !BST_LIB_IsStringInit( m_pstHbPktContent->pRespContent ) )
    {
        BST_RLS_LOG2( "HeartBeat::IsConfigOk ProcId=%d, TaskId=%d, config is not OK: pRespContent",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    return BST_TRUE;
}

/*****************************************************************************
 函 数 名  : RxAnsTimerProc
 功能描述  : 重传定时器超时回调函数
 输入参数  : pvPara
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年5月29日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID HeartBeat::RxAnsTimerProc( BST_VOID *pvPara )
{
    BST_CORE_CPTask                    *pcPtask;

    if( BST_HB_INVALID_RETRY_TIMES == m_stHbTxRetry.stRetryInfo.ulMaxReTimes )
    {
        return;
    }

    m_stHbTxRetry.usRetryNum++;

    if ( m_stHbTxRetry.stRetryInfo.ulMaxReTimes <= m_stHbTxRetry.usRetryNum )
    {
        BST_RLS_LOG2( "HeartBeat::TimerExpired ProcId=%d, TaskId=%d, Tx retry is finished",
                      m_usProcId, m_usTaskId );
        if ( BST_OS_IsTimerValid( m_stHbTxRetry.ulTimerId ) )
        {
            BST_OS_TimerStop( m_stHbTxRetry.ulTimerId );
            m_stHbTxRetry.usRetryNum= 0;
        }
        Finished();
        ProcEstState( BST_APP_CONN_TYPE_CP_ERR_CLS );
        pcPtask                         = this;
        BST_SRV_ApiSendPTaskEvent( pcPtask, BST_SRV_T2S_ACK_RESULT, BST_CORE_SCHD_ACK_ERR );
        /*应用层定时器超时后，要断开socket，防止协议栈重传*/
        if ( BST_NULL_PTR != m_pSocket )
        {
            m_pSocket->CloneClose();
        }
    }
    else
    {
        BST_DBG_LOG4( "HeartBeat::TimerExpired ProcId=%d, TaskId=%d, Tx retry, timerId:%u, usRetryNum:%u",
                      m_usProcId, m_usTaskId, m_stHbTxRetry.ulTimerId, m_stHbTxRetry.usRetryNum );
        SendHbPkt();
        BST_OS_TimerStart( m_stHbTxRetry.ulTimerId, m_stHbTxRetry.stRetryInfo.ulIntervals );
        BST_DBG_UPDATE_ERR_NUM( m_usProcId, m_usTaskId );
    }
}

/*****************************************************************************
 函 数 名  : ChnlCtrlTimerProc
 功能描述  : 信道控制超时重试事件
 输入参数  : pvPara
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年5月29日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID HeartBeat::ChnlCtrlTimerProc( BST_VOID *pvPara )
{
    BST_SRV_CHNL_LINK_STRU             *pstChnlLinker;
    BST_DSPP_CAppUlVc                  *pstDsppUl;
    BST_UINT32                          ulVoidProp = 0;

    pstChnlLinker                       = GetChnlInstance();
    if( BST_NULL_PTR == pstChnlLinker )
    {
        return;
    }
    if( pstChnlLinker->ulRetryTimes > BST_SRV_CHNL_RTX_MAX )
    {
        pstDsppUl                       = BST_DSPP_CAppUlVc::GetInstance();
        pstDsppUl->Report( BST_DSPP_FLG_CMD_CLEAR, m_usProcId, m_usTaskId );
        BST_SRV_CHNL_Clear( pstChnlLinker );
        pstChnlLinker->ulRetryTimes     = 0;
        BST_OS_TimerStop( m_ChnlTimerId );
        m_pSocket->IoCtrl( BST_SCKT_CMD_SYNC_PROPERTY_STOP, ( BST_VOID  *)&ulVoidProp );
        BST_RLS_LOG( "HeartBeat::ChnlCtrlSend SYNC_PROPERTY_STOP 2" );
        m_pExptReport->Report( BST_PID_SYNC_PROPERTY_STOP,
                               BST_OS_SIZEOF(BST_UINT32),
                              &ulVoidProp );
    }
    else
    {
        BST_SRV_CHNL_ProcInCB( pstChnlLinker );
    }
}
/*****************************************************************************
 函 数 名  : TimerExpied
 功能描述  : 重传定时器超时回调函数
 输入参数  : lId:定时器ID号
             pvPara
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年6月18日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID HeartBeat::TimerExpired(
    BST_OS_TIMERID_T ulId,
    BST_VOID        *pvPara )
{
    if( ulId == m_stHbTxRetry.ulTimerId )
    {
        RxAnsTimerProc( pvPara );
    }
    else if( ulId == m_ChnlTimerId )
    {
        ChnlCtrlTimerProc( pvPara );
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 函 数 名  : PidInquired
 功能描述  : AP信息下发到应用的配置函数

 输入参数  : enParamId ：PID的值
            usDataSize：数据长度
            pData     ：数据指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年9月4日
      作    者   : l00231445
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT16 HeartBeat::PidInquired(
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usDataSize,
    BST_VOID                 *const pData )
{
    BST_CORE_CPTask          *pcPtask;

    switch ( enParamId )
    {
        case BST_PID_SOCKET_PROPERTY:
            /* 当AP要查询当前TCP属性时，暂停当前的心跳发送及其定时器*/
            if ( BST_TRUE == m_ulBusyFlag )
            {
                Finished();
                if ( BST_OS_IsTimerValid( m_stHbTxRetry.ulTimerId ) )
                {
                    BST_OS_TimerStop( m_stHbTxRetry.ulTimerId );
                    m_stHbTxRetry.usRetryNum
                                        = 0;
                }
            }
            pcPtask                     = this;
            BST_SRV_ApiSendPTaskEvent( pcPtask, BST_SRV_T2S_RUN_STOPED, 0 );
            return ( BST_OS_SIZEOF ( BST_IP_SKT_PROPTY_STRU ) );

        default:
            return 0;
    }
}

/*****************************************************************************
 函 数 名  : PidConfiged
 功能描述  : AP信息下发到应用的配置函数

 输入参数  : enParamId：PID
            usLen    ：对应PID的数据长度
            pData    ：数据指针
            ulBaseCfged：基础项配置的标志
            pucNewAddr：PID项存储的地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_ERR_ENUM_UINT8 HeartBeat::PidConfiged(
    BST_CORE_PID_ENUM_UINT16     enParamId,
    BST_UINT16                   usLen,
    const BST_VOID              *const pData,
    BST_UINT32                   ulBaseCfged,
    BST_UINT8                  **pucNewAddr )
{
    BST_UINT8                          *pucRptr;
    BST_CORE_CPTask                    *pcPtask;
    BST_UINT32                          ulNewState;

#if ( BST_OS_VER != BST_WIN32 || BST_VER_TYPE != BST_DBG_VER )
    BST_IP_ERR_T                        enIpErrMsg;
#endif
    pucRptr                             = BST_NULL_PTR;
    ulNewState                          = BST_FALSE;
    BST_ASSERT_NULL_RTN( pData, BST_ERR_ILLEGAL_PARAM );

    switch ( enParamId )
    {
        case BST_PID_HB_RESP_CONTENT:
            pucRptr                     = SetRespContent( ( BST_UINT8 * )pData, usLen );
            break;

        case BST_PID_HB_SEND_CONTENT:
            pucRptr                     = SetFixedContent( ( BST_UINT8 * )pData, usLen );
            break;

        case BST_PID_HB_SERIAL_NUM:
            pucRptr                     = SetHbSnInfo( pData, usLen );
            break;

        case BST_PID_PROTOCOL_TYPE:
            pucRptr                     = ConfigType( pData, usLen );
            if ( BST_NULL_PTR != pucRptr )
            {
                BST_SetConfigFlag( BST_CFGFLG_TYPE );
            }
#if ( BST_OS_VER != BST_WIN32 || BST_VER_TYPE != BST_DBG_VER )
            BST_HB_CLONE_SOCKET( enIpErrMsg, pucRptr );
#endif
            break;
        case BST_PID_SOCKET_INFO:
#if ( BST_OS_VER != BST_WIN32 || BST_VER_TYPE != BST_DBG_VER )
            if( (BST_TASK_STATE_MNTNING == GetState())
                || (BST_TASK_STATE_WAINTING == GetState()))
            {
                return BST_ERR_ILLEGAL_PARAM;
            }
            BST_HB_CLONE_SOCKET( enIpErrMsg, pucRptr );
#endif
            break;

        case BST_PID_HB_TX_RETRY_MAX:
            pucRptr                     = SetAppTxRetry( pData, usLen );
            break;

        case BST_PID_LH_RELINK_ENABLE:
            if ( usLen != BST_OS_SIZEOF( BST_UINT32 ) )
            {
                return BST_ERR_ILLEGAL_PARAM;
            }
            pucRptr                     = ( BST_UINT8 *)&ulNewState;
            BST_OS_MEMCPY( pucRptr, pData, usLen );
            BST_DBG_LOG3( "Heartbeat::Config Relink ProcId=%d, TaskId=%d, Value=%u",
                          m_usProcId, m_usTaskId, ulNewState );
            m_ulIsReLinkEn              = ulNewState;
            break;

        case BST_PID_LH_SOCKET_EST:
            if ( usLen != BST_OS_SIZEOF( BST_UINT32 ) )
            {
                return BST_ERR_ILLEGAL_PARAM;
            }
            pucRptr                     = ( BST_UINT8 *)&m_ulConnEstState;
            BST_OS_MEMCPY( pucRptr, pData, usLen );
            BST_DBG_LOG3( "Heartbeat::Config Socket Established ProcId=%d, TaskId=%d, New=%u",
                          m_usProcId, m_usTaskId, m_ulConnEstState );
            ProcEstState( m_ulConnEstState );
            break;

        case BST_PID_LH_IS_DETECTOR:
            if ( usLen != BST_OS_SIZEOF( BST_UINT32 ) )
            {
                return BST_ERR_ILLEGAL_PARAM;
            }
            pucRptr                     = ( BST_UINT8 *)&m_ulIsDetector;
            BST_OS_MEMCPY( pucRptr, pData, usLen );
            BST_DBG_LOG3( "Heartbeat::Config Detector ProcId=%d, TaskId=%d, Value=%u",
                          m_usProcId, m_usTaskId, m_ulIsDetector );
            if( BST_TRUE == m_ulIsDetector )
            {
                pcPtask                 = this;
                BST_SRV_ApiSendPTaskEvent( pcPtask, BST_SRV_T2S_DEF_DETCET, 0 );
            }
            break;

        default:
            pucRptr                     = BST_NULL_PTR;
            break;
    }
    /*此处包含了property的下发判断，若想要测试无seq同步的，修改宏*/
    if ( BST_HB_IsBaseCfged( m_CfgedFlag ) )
    {
        pcPtask                         = this;
        BST_SRV_ApiSendPTaskEvent( pcPtask, BST_SRV_T2S_RUN_RESUME, 0 );
        Start();
    }
   *pucNewAddr                          = pucRptr;

    if ( BST_NULL_PTR == pucRptr )
    {
       return BST_ERR_ILLEGAL_PARAM;
    }
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : SetSocketInfo
 功能描述  : 设置socket类的属性

 输入参数  : enSocketType：socket类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_BOOL HeartBeat::SetSocketInfo( BST_SCKT_TYPE_ENUM_UINT32 enSocketType )
{
    BST_IP_ERR_T                enIpErrMsg;
    BST_IP_CNetRcver           *pNetRcver;

    pNetRcver                   = this;
    if ( BST_NULL_PTR == m_pSocket )
    {
        return BST_FALSE;
    }

    enIpErrMsg                  = m_pSocket->IoCtrl( BST_SCKT_CMD_DEF_TYPE,
                                                    ( BST_VOID * )&enSocketType );
    if ( BST_IP_ERR_OK != enIpErrMsg )
    {
        BST_RLS_LOG2( "HeartBeat::SetSocketInfo ProcId=%d, TaskId=%d, DEF_TYPE Err",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    if ( !BST_IsInfoConfiged( BST_CFGFLG_TYPE ) )
    {
        enIpErrMsg              = m_pSocket->IoCtrl( BST_SCKT_CMD_REG_CALLBACK,
                                                     pNetRcver );
        if( BST_IP_ERR_OK != enIpErrMsg )
        {
            BST_RLS_LOG2( "HeartBeat::SetSocketInfo ProcId=%d, TaskId=%d, REG_CALLBACK Err",
                          m_usProcId, m_usTaskId );
            return BST_FALSE;
        }
    }

    enIpErrMsg                  = m_pSocket->Socket( BST_SRV_GetTaskMsgHandle
                                                   ( m_usProcId, m_usTaskId ) );
    if( BST_IP_ERR_OK != enIpErrMsg )
    {
        return BST_FALSE;
    }
    return BST_TRUE;
}
/*****************************************************************************
 函 数 名  : ConfigType
 功能描述  : 设置应用类型

 输入参数  : enPrtcType 协议类型
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT8 *HeartBeat::ConfigType(
    const BST_VOID *const pData,
    BST_UINT16            usLen )
{
    BST_PRTC_TYPE_ENUM_UINT32           enPrtcType;
    BST_SCKT_TYPE_ENUM_UINT32           enSocketType;
    BST_UINT8                          *pucRtnPtr;
    BST_BOOL                            bRtnVal;
    if ( BST_IP_IsTypeInited ( m_ProtolType ) )
    {
        return BST_NULL_PTR;
    }
    if ( BST_FALSE == InitHeartBeat() )
    {
        return BST_NULL_PTR;
    }
    BST_ASSERT_NULL_RTN( pData, BST_NULL_PTR );
    BST_ASSERT_0_RTN( usLen, BST_NULL_PTR );
    BST_OS_MEMCPY( &enPrtcType, pData, usLen );

    pucRtnPtr                           = BST_NULL_PTR;

    switch ( enPrtcType )
    {
        case BST_PRTC_TYPE_TCP_LONG:
            enSocketType                = BST_SCKT_TYPE_TCP;
            break;

        case BST_PRTC_TYPE_TCP_SHORT:
            enSocketType                = BST_SCKT_TYPE_TCP;
            break;

        case BST_PRTC_TYPE_UDP:
            enSocketType                = BST_SCKT_TYPE_UDP;
            break;

        case BST_PRTC_TYPE_SSL:
            enSocketType                = BST_SCKT_TYPE_SSL;
            break;

        default:
            return BST_NULL_PTR;
    }
    bRtnVal                             = SetSocketInfo( enSocketType );
    if ( BST_FALSE == bRtnVal )
    {
        BST_RLS_LOG2( "HeartBeat::ConfigType ProcId=%d, TaskId=%d, SetSocketInfo Err",
                      m_usProcId, m_usTaskId );
        return BST_NULL_PTR;
    }
    m_ProtolType                        = enPrtcType;
    pucRtnPtr                           = (BST_UINT8 *)&m_ProtolType;
    return pucRtnPtr;
}

/*****************************************************************************
 函 数 名  : SetHbSnInfo
 功能描述  : 设置心跳序列信息
 输入参数  : pstHbSnPkt:心跳信息数据的指针
            usLength：数据长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT8 *HeartBeat::SetHbSnInfo(
    const BST_VOID *const pData,
    BST_UINT16            usLen )
{
    SERNO_HB_INFO_STRU                  stHbSnPkt;
    BST_UINT8                          *pucRtnPtr;

    pucRtnPtr                           = BST_NULL_PTR;

    if ( usLen != BST_OS_SIZEOF( SERNO_HB_INFO_STRU ) )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == pData )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstHbPktContent )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstHbPktContent->pstSnInfoPkt )
    {
        return BST_NULL_PTR;
    }

    BST_OS_MEMCPY( &stHbSnPkt, pData, usLen );

    m_pstHbPktContent->usHbPktLength   += usLen;
    m_pstHbPktContent->bSnUsed          = BST_TRUE;
   *(m_pstHbPktContent->pstSnInfoPkt)   = stHbSnPkt;
    m_ulHbSerNum                        = stHbSnPkt.ulSnBegin;/*给心跳包序列号赋值*/
    pucRtnPtr                           = (BST_UINT8 *)m_pstHbPktContent->pstSnInfoPkt;

#if ( BST_VER_TYPE == BST_DBG_VER )

    BST_DBG_LOG4( "HeartBeat::SetHbSnInfo ulSnMin:%u, ulSnMax:%u, ulSnBegin:%u, ulSnStep:%u",
                   stHbSnPkt.ulSnMin, stHbSnPkt.ulSnMax,
                   stHbSnPkt.ulSnBegin, stHbSnPkt.ulSnStep );

#endif
    return pucRtnPtr;
}

/*****************************************************************************
 函 数 名  : InitHeartBeat
 功能描述  : 初始化应用心跳的注册表信息

 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_BOOL HeartBeat::InitHeartBeat()
{
    if ( BST_NULL_PTR == m_pSocket )
    {
        BST_RLS_LOG2( "HeartBeat::InitHeartBeat ProcId=%d, TaskId=%d, m_pSocket=NULL",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    m_stHbTxRetry.ulTimerId             = BST_OS_TimerCreateCpp( this,
                                                                 BST_NULL_PTR,
                                                                 BST_SRV_GetTaskMsgHandle
                                                               ( m_usProcId, m_usTaskId ) );
    if ( !BST_OS_IsTimerValid( m_stHbTxRetry.ulTimerId ) )
    {
        BST_RLS_LOG2( "HeartBeat::InitHeartBeat ProcId=%d, TaskId=%d, create timer failed",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    m_pstHbPktContent                   = ( HB_PCKT_CONTENT_STRU * )BST_OS_MALLOC
                                            ( BST_OS_SIZEOF( HB_PCKT_CONTENT_STRU ) );
    if ( BST_NULL_PTR == m_pstHbPktContent )
    {
        BST_RLS_LOG2( "HeartBeat::InitHeartBeat ProcId=%d, TaskId=%d, m_pstHbPktContent=NULL",
                      m_usProcId, m_usTaskId );
        BST_OS_TimerRemove(m_stHbTxRetry.ulTimerId);
        m_stHbTxRetry.ulTimerId         = BST_OS_INVALID_TIMER_ID;
        return BST_FALSE;
    }

    m_pstHbPktContent->pstSnInfoPkt     = BST_NULL_PTR;
    m_pstHbPktContent->pRespContent     = BST_NULL_PTR;
    m_pstHbPktContent->pFixedContent    = BST_NULL_PTR;
    m_pstHbPktContent->pCipherKey       = BST_NULL_PTR;

    m_pstHbPktContent->pstSnInfoPkt     = ( SERNO_HB_INFO_STRU * )BST_OS_MALLOC
                                            ( BST_OS_SIZEOF( SERNO_HB_INFO_STRU ) );
    if ( BST_NULL_PTR == m_pstHbPktContent->pstSnInfoPkt )
    {
        BST_RLS_LOG2( "HeartBeat::InitHeartBeat ProcId=%d, TaskId=%d, pstSnInfoPkt=NULL",
                      m_usProcId, m_usTaskId );
        BST_OS_TimerRemove(m_stHbTxRetry.ulTimerId);
        m_stHbTxRetry.ulTimerId         = BST_OS_INVALID_TIMER_ID;
        BST_OS_FREE( m_pstHbPktContent );
        return BST_FALSE;
    }
    BST_OS_MEMSET( m_pstHbPktContent->pstSnInfoPkt, 0, BST_OS_SIZEOF( SERNO_HB_INFO_STRU ) );

    m_pstHbPktContent->pRespContent     = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    if ( BST_NULL_PTR == m_pstHbPktContent->pRespContent )
    {
        BST_RLS_LOG2( "HeartBeat::InitHeartBeat ProcId=%d, TaskId=%d, pRespContent=NULL",
                      m_usProcId, m_usTaskId );
        BST_OS_TimerRemove(m_stHbTxRetry.ulTimerId);
        m_stHbTxRetry.ulTimerId         = BST_OS_INVALID_TIMER_ID;
        BST_OS_FREE( m_pstHbPktContent->pstSnInfoPkt );
        BST_OS_FREE( m_pstHbPktContent );
        return BST_FALSE;
    }
    m_pstHbPktContent->pFixedContent    = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    if ( BST_NULL_PTR == m_pstHbPktContent->pFixedContent )
    {
        BST_RLS_LOG2( "HeartBeat::InitHeartBeat ProcId=%d, TaskId=%d, pFixedContent=NULL",
                      m_usProcId, m_usTaskId );
        BST_OS_TimerRemove(m_stHbTxRetry.ulTimerId);
        m_stHbTxRetry.ulTimerId         = BST_OS_INVALID_TIMER_ID;
        BST_LIB_StrDelete( m_pstHbPktContent->pRespContent );
        BST_OS_FREE( m_pstHbPktContent->pstSnInfoPkt );
        BST_OS_FREE( m_pstHbPktContent );
        return BST_FALSE;
    }
    m_pstHbPktContent->pCipherKey       = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    if ( BST_NULL_PTR == m_pstHbPktContent->pCipherKey )
    {
        BST_RLS_LOG2( "HeartBeat::InitHeartBeat ProcId=%d, TaskId=%d, pCipherKey=NULL",
                      m_usProcId, m_usTaskId );
        BST_OS_TimerRemove(m_stHbTxRetry.ulTimerId);
        m_stHbTxRetry.ulTimerId         = BST_OS_INVALID_TIMER_ID;
        BST_LIB_StrDelete( m_pstHbPktContent->pFixedContent );
        BST_LIB_StrDelete( m_pstHbPktContent->pRespContent );
        BST_OS_FREE( m_pstHbPktContent->pstSnInfoPkt );
        BST_OS_FREE( m_pstHbPktContent );
        return BST_FALSE;
    }

    m_pstHbPktContent->usHbPktLength    = 0;
    m_pstHbPktContent->enSecMode        = BST_APP_ENCRP_INVALID_TYPE;
    m_pstHbPktContent->enCheckType      = BST_APP_HB_INVALID_CHK_TYPE;
    m_pstHbPktContent->bSnUsed          = BST_FALSE;

    if ( BST_FALSE == InitRegedit() )
    {
        BST_RLS_LOG2( "HeartBeat::InitHeartBeat ProcId=%d, TaskId=%d, Regist failed",
                      m_usProcId, m_usTaskId );
        BST_OS_TimerRemove(m_stHbTxRetry.ulTimerId);
        m_stHbTxRetry.ulTimerId         = BST_OS_INVALID_TIMER_ID;
        BST_LIB_StrDelete( m_pstHbPktContent->pFixedContent );
        BST_LIB_StrDelete( m_pstHbPktContent->pRespContent );
        BST_LIB_StrDelete( m_pstHbPktContent->pCipherKey );
        BST_OS_FREE( m_pstHbPktContent->pstSnInfoPkt );
        BST_OS_FREE( m_pstHbPktContent );
        return BST_FALSE;
    }

    return BST_TRUE;
}

/*****************************************************************************
 函 数 名  : InitRegedit
 功能描述  : 初始化应用心跳的注册表信息

 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_BOOL HeartBeat::InitRegedit( BST_VOID )
{
    BST_CORE_CRegedit                  *pcRegedit;
    BST_CORE_CAPCCallBack              *pcApcInterface;
    BST_ERR_ENUM_UINT8                  enRtnVal;
    pcRegedit                           = BST_CORE_CRegedit::GetInstance();
    if ( BST_NULL_PTR == pcRegedit )
    {
        BST_RLS_LOG2( "HeartBeat::InitRegedit ProcId=%d, TaskId=%d, pcRegedit=NULL",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }
    pcApcInterface                      = this;
    pcRegedit->Regist ( this, pcApcInterface, BST_DSPP_VER_C );

    enRtnVal                            = pcRegedit->Regist( this,
                                                             BST_PID_HB_RESP_CONTENT,
                                                             m_pstHbPktContent->pRespContent->usUsed,
                                                             m_pstHbPktContent->pRespContent->pData );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_HB_RESP_CONTENT error",\
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    enRtnVal                            = pcRegedit->Regist ( this, 
                                                              BST_PID_SYNC_PROPERTY_START,
                                                              BST_OS_SIZEOF ( BST_IP_SKT_PROPTY_STRU ),
                                                              BST_NULL_PTR );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_SYNC_PROPERTY_START error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }
    BST_RLS_LOG( "HeartBeat::ChnlCtrlSend SYNC_PROPERTY_STOP 3" );

    enRtnVal                            = pcRegedit->Regist ( this, 
                                                              BST_PID_SYNC_PROPERTY_STOP,
                                                              BST_OS_SIZEOF ( BST_UINT32 ),
                                                              BST_NULL_PTR );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_SYNC_PROPERTY_STOP error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    enRtnVal                            = pcRegedit->Regist( this,
                                                             BST_PID_HB_SEND_CONTENT,
                                                             m_pstHbPktContent->pFixedContent->usUsed,
                                                             m_pstHbPktContent->pFixedContent->pData );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_HB_SEND_CONTENT error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }
    enRtnVal                            = pcRegedit->Regist( this,
                                                             BST_PID_CIPHER_CODE,
                                                             m_pstHbPktContent->pCipherKey->usUsed,
                                                             m_pstHbPktContent->pCipherKey->pData );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_CIPHER_CODE error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }
    enRtnVal                            = pcRegedit->Regist( this,
                                                             BST_PID_HB_SERIAL_NUM,
                                                             BST_OS_SIZEOF( SERNO_HB_INFO_STRU ),
                                                             m_pstHbPktContent->pstSnInfoPkt );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_HB_SERIAL_NUM error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }
    enRtnVal                            = pcRegedit->Regist( this,
                                                             BST_PID_CIPHER_MODE,
                                                             BST_OS_SIZEOF( m_pstHbPktContent->enSecMode ),
                                                             &m_pstHbPktContent->enSecMode );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_CIPHER_MODE error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }
    enRtnVal                            = pcRegedit->Regist( this,
                                                             BST_PID_HB_TX_RETRY_MAX,
                                                             BST_OS_SIZEOF( BST_HB_RETRY_INFO ),
                                                             &m_stHbTxRetry.stRetryInfo );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_HB_TX_RETRY_MAX error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    enRtnVal                            = pcRegedit->Regist( this,
                                                             BST_PID_LH_IS_DETECTOR,
                                                             BST_OS_SIZEOF( BST_UINT32 ),
                                                             &m_ulIsDetector );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_LH_IS_DETECTOR error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }


    enRtnVal                            = pcRegedit->Regist( this,
                                                             BST_PID_LH_SOCKET_EST,
                                                             BST_OS_SIZEOF( BST_UINT32 ),
                                                             &m_ulConnEstState );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_LH_SOCKET_EST error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }

    enRtnVal                            = pcRegedit->Regist( this,
                                                             BST_PID_LH_RELINK_ENABLE,
                                                             BST_OS_SIZEOF( BST_UINT32 ),
                                                             &m_ulIsReLinkEn );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_DBG_LOG2( "Heartbeat::InitRegedit ProcId=%d, TaskId=%d, Regist BST_PID_LH_RELINK_ENABLE error",
                      m_usProcId, m_usTaskId );
        return BST_FALSE;
    }
    return BST_TRUE;
}

/*****************************************************************************
 函 数 名  : SetCipherKey
 功能描述  : 设置密钥

 输入参数  : pucCipherKey：密钥数据的指针
            usLength    ：密钥的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT8 *HeartBeat::SetCipherKey(
    BST_UINT8 *pucCipherKey,
    BST_UINT16 usLength )
{
    BST_DBG_LOG( "HeartBeat::SetCipherKey is not implemented" );
    return BST_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : SetEncrypType
 功能描述  : 设置加密类型

 输入参数  : pData：加密类型的数据指针
            usLen：数据的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT8 *HeartBeat::SetEncrypType(
    BST_UINT8 *pData,
    BST_UINT16 usLen )
{
    BST_APP_ENCRP_MODE_ENUM_UINT32      enEncryptType;
    BST_OS_MEMCPY( &enEncryptType, pData, BST_OS_SIZEOF( BST_APP_ENCRP_MODE_ENUM_UINT32 ) );

    BST_DBG_LOG( "HeartBeat::SetEncrypType is not implemented" );
    return BST_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : SetCheckType
 功能描述  : 设置校验类型

 输入参数  : pData：校验类型的数据指针
            usLen：数据的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT8 *HeartBeat::SetCheckType(
    BST_UINT8 *pData,
    BST_UINT16 usLen )
{
    BST_APP_HB_CHECK_TYPE_ENUM_UINT32 enCheckType;
    BST_OS_MEMCPY( &enCheckType, pData, usLen );

    BST_DBG_LOG( "HeartBeat::SetCheckType is not implemented" );
    return BST_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : SetFixedContent
 功能描述  : 设置心跳固定字段的内容

 输入参数  : pucFixContent：固定字段的数据指针
            usFixLength   ：数据的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT8 *HeartBeat::SetFixedContent(
    BST_UINT8  *pucFixContent,
    BST_UINT16  usFixLength )
{
    BST_UINT8                          *pucRtnPtr;

    pucRtnPtr                           = BST_NULL_PTR;
    if ( BST_HB_MAX_CONFIG_BYTES < usFixLength )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == pucFixContent )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstHbPktContent )
    {
        BST_DBG_LOG("SetFixedContent m_pstHbPktContent is NULL");
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstHbPktContent->pFixedContent )
    {
        return BST_NULL_PTR;
    }

    BST_DBG_LOG3( "Heartbeat::SetFixedContent ProcId=%d, TaskId=%d, SetFixedContent length: %d",
                  m_usProcId, m_usTaskId, usFixLength );
    BST_LIB_StrFill( m_pstHbPktContent->pFixedContent, pucFixContent, usFixLength );
    m_pstHbPktContent->usHbPktLength   += usFixLength;
    pucRtnPtr                           = (BST_UINT8 *)m_pstHbPktContent->pFixedContent->pData;

    return pucRtnPtr;
}

/*****************************************************************************
 函 数 名  : SetRespContent
 功能描述  : 设置心跳服务器回复的内容

 输入参数  : pucRespContent：回复的内容
            usFixLength   ：回复包的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年3月9日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT8 *HeartBeat::SetRespContent(
    BST_UINT8  *pucRespContent,
    BST_UINT16  usRespLength )
{
    BST_UINT8                          *pucRtnPtr;

    pucRtnPtr                           = BST_NULL_PTR;

    if( BST_HB_MAX_CONFIG_BYTES < usRespLength )
    {
        return BST_NULL_PTR;
    }
    if( BST_NULL_PTR == pucRespContent )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstHbPktContent )
    {
        BST_DBG_LOG("SetRespContent m_pstHbPktContent is NULL");
        return BST_NULL_PTR;
    }
    if( BST_NULL_PTR == m_pstHbPktContent->pRespContent )
    {
        return BST_NULL_PTR;
    }

    BST_DBG_LOG3( "Heartbeat::SetRespContent ProcId=%d, TaskId=%d, SetRespContent length: %d",
                  m_usProcId, m_usTaskId, usRespLength );
    BST_LIB_StrFill( m_pstHbPktContent->pRespContent, pucRespContent, usRespLength );

    pucRtnPtr                           = (BST_UINT8 *)m_pstHbPktContent->pRespContent->pData;

    return pucRtnPtr;
}

/*****************************************************************************
 函 数 名  : SetAppTxRetry
 功能描述  : 设置应用层发送重传的定时器信息

 输入参数  : pstRetryInfo:重传的相关信息
            usLen:下发数据段的长度
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年7月17日
      作    者   : l00242755
      修改内容   : 新生成函数

*****************************************************************************/
BST_UINT8 *HeartBeat::SetAppTxRetry(
    const BST_VOID *const pData,
    BST_UINT16            usLen )
{
    BST_HB_RETRY_INFO                   stHbRetryInfo;
    BST_UINT8                          *pucRtnPtr;

    pucRtnPtr                           = BST_NULL_PTR;

    if ( usLen != BST_OS_SIZEOF( BST_HB_RETRY_INFO ) )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == pData )
    {
        return BST_NULL_PTR;
    }

    BST_OS_MEMCPY( &stHbRetryInfo, pData, usLen );
    /**
     * 接口保留，但是不再使用AP配置的重试策略，一次超时就算失败，没必要重试   
    m_stHbTxRetry.stRetryInfo           = stHbRetryInfo;*/
    pucRtnPtr                           = (BST_UINT8 *)&m_stHbTxRetry.stRetryInfo;
#if ( BST_VER_TYPE == BST_DBG_VER )

    BST_DBG_LOG4( "Heartbeat::SetAppTxRetry ProcId=%d, TaskId=%d, Set retry info, ulIntervals:%u, ulMaxReTimes:%u",
                  m_usProcId, m_usTaskId, stHbRetryInfo.ulIntervals, stHbRetryInfo.ulMaxReTimes );

#endif
    return pucRtnPtr;
}
/*****************************************************************************
 函 数 名  : ReBuildLink
 功能描述  : 重建连接
 输入参数  : BST_UINT32 ulNeedReport 重建的同时，是否需要上报给AP，Socket已经断开了
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年5月29日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID HeartBeat::ReBuildLink( BST_UINT32 ulNeedReport )
{
    BST_UINT32                      ulSocketEst = BST_APP_CONN_TYPE_AP_ERR_CLS;
    BST_TASK_STATE_ENUM_UINT8       enTaskState;
    BST_DRV_STRU                   *pstLsDriver;
    BST_AS_NET_RANK_ENUM_UINT32     enNewRank;

    enTaskState                     = GetState();
    if( ( BST_TASK_STATE_MNTNING == enTaskState )
      ||( BST_TASK_STATE_WAINTING== enTaskState ) )
    {
        return;
    }

    pstLsDriver                     = BST_DRV_LsGetDvcHandle();
    if( BST_NULL_PTR != pstLsDriver->pfRead )
    {
        pstLsDriver->pfRead( BST_OS_SIZEOF(enNewRank), (BST_UINT8 *)&enNewRank );
    }
    else
    {
        enNewRank                   = BST_AS_NET_RANK_GOOD;
    }

    /**
     * 如果代理重联在运行，需要汇报AP-BASTET，socket已经断开，否则按照原有方式直接上报到APP
     */
    if( BST_TRUE == ulNeedReport )
    {
        if( BST_TRUE == m_ulIsReLinkEn )
        {
            ulSocketEst    = BST_APP_CONN_TYPE_CP_ERR_CLS;
            m_pExptReport->Report( BST_PID_LH_SOCKET_EST, 
                ( BST_UINT16 )BST_OS_SIZEOF(BST_UINT32), &ulSocketEst );
        }
        else
        {
            Report( BST_ERR_SOCKET_CLSD );
        }
    }

    if( BST_TRUE == m_ulIsReLinkEn )
    {
        if( enNewRank >= BST_AS_NET_RANK_POOR )
        {
            ProcEstState( BST_APP_CONN_TYPE_BEST_CONN_POINT );
            Maintain();
        }
        else
        {
            Waiting();
        }
    }
}
/*****************************************************************************
 函 数 名  : onErrClosed
 功能描述  : 探测器发现任务Socket中断后的处理流程
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年5月29日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
BST_VOID HeartBeat::onCycleError( BST_VOID )
{
    ProcEstState( BST_APP_CONN_TYPE_CP_ERR_CLS );
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
BST_VOID HeartBeat::onUpdateCycle( BST_UINT16 ulDetCycle )
{
    BST_UINT32              ulNewCycle;

    if ( BST_NULL_PTR == m_pExptReport )
    {
        BST_RLS_LOG( "BST_CORE_CNPTask::onUpdateCycle m_pExptReport=NULL" );
        return;
    }
    ulNewCycle              = ulDetCycle;
    m_pExptReport->Report( BST_PID_HB_CONF_CYC, BST_OS_SIZEOF( BST_UINT32 ), &ulNewCycle );
}

/*****************************************************************************
 函 数 名  : onErrClosed
 功能描述  : 处理EST状态标识
 输入参数  : 当前EST状态
 输出参数  : 无
 返 回 值  : BST_TASK_STATE_ENUM_UINT8 处理后的任务状态
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2015年5月29日
      作    者   : d00173029
      修改内容   : 新生成函数

*****************************************************************************/
BST_TASK_STATE_ENUM_UINT8 HeartBeat::ProcEstState(
    BST_APP_CONN_EST_TYPE_ENUM_UINT32 enNewSta )
{
    BST_TASK_STATE_ENUM_UINT8       enOldTaskState;
    BST_CORE_CPTask                *pcPtask;

    enOldTaskState                  = GetState();
    switch( enNewSta )
    {
        case BST_APP_CONN_TYPE_AP_ERR_CLS:
            Stop();
            BST_ResetPrptyFlag();
            ReBuildLink( BST_FALSE );
            break;

        case BST_APP_CONN_TYPE_AP_NORMAL_EST:
            /**
             * 如果Modem重建维护过程中，AP建立完成，那么立即停止一切行为，清空当前Socket，等待配置参数
             */
            if( ( BST_TASK_STATE_MNTNING == enOldTaskState )
              ||( BST_TASK_STATE_WAINTING== enOldTaskState ) )
            {
                m_pSocket->CloneClose();
                m_pSocket->Socket( BST_SRV_GetTaskMsgHandle( m_usProcId, m_usTaskId ) );
#if ( BST_OS_VER != BST_WIN32 || BST_VER_TYPE != BST_DBG_VER )
                m_pSocket->Clone();
#endif
            }
            Stop();
            BST_ResetPrptyFlag();
            break;

#ifdef BST_IP_REBUILD_IN_MODEM
        case BST_APP_CONN_TYPE_CP_NORMAL_EST:
#endif
        case BST_APP_CONN_TYPE_BEST_CONN_POINT:
            m_pExptReport->Report( BST_PID_LH_SOCKET_EST, 
                            ( BST_UINT16 )BST_OS_SIZEOF(BST_UINT32), &enNewSta );
            Stop();
            BST_ResetPrptyFlag();
            break;

        case BST_APP_CONN_TYPE_CP_ERR_CLS:
            /**
             * 如果Modem重建中失败，那么可以采用计数、重试机制，这里只连接1次，连不上就退出，不管了
             */
            if( BST_TASK_STATE_START != GetState() )
            {
                break;
            }
            BST_ResetPrptyFlag();
            if( BST_TRUE == m_ulIsReLinkEn )
            {
                ReBuildLink( BST_TRUE );
            }
            else
            {
                Report( BST_ERR_SOCKET_CLSD );
                Suspend();
            }
            break;
    default:
        break;
    }
    if( ( BST_TASK_STATE_START != GetState() )
      &&( BST_TASK_STATE_START == enOldTaskState ) )
    {
        pcPtask                     = this;
        BST_SRV_ApiSendPTaskEvent( pcPtask, BST_SRV_T2S_RUN_STOPED, 0 );
    }
    return GetState();
}

/***************************************************************
 函 数 名   : ChnlCtrlInit
 功能描述   : 信道控制发送接口
 输入参数   : 无
 输出参数   : 无
 返 回 值   : 无
 被调函数   :
 调用函数   :

 修改历史   :
 修改历史   :
 1.日    期 : 2015年05月10日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_SRV_CHNL_LINK_STRU *HeartBeat::GetChnlInstance( BST_VOID )
{
    if( BST_NULL_PTR != m_pstChnlLinker )
    {
        return m_pstChnlLinker;
    }
    BST_ASSERT_NULL_RTN( m_pSocket, BST_NULL_PTR );

    m_pstChnlLinker                     = (BST_SRV_CHNL_LINK_STRU *)BST_OS_MALLOC
                                          (BST_OS_SIZEOF(BST_SRV_CHNL_LINK_STRU));

    BST_ASSERT_NULL_RTN( m_pstChnlLinker, BST_NULL_PTR );

    m_ChnlTimerId                       = BST_OS_TimerCreateCpp( this,
                                                                 BST_NULL_PTR,
                                                                 BST_SRV_GetTaskMsgHandle
                                                               ( m_usProcId, m_usTaskId ) );

    if(BST_OS_INVALID_TIMER_ID == m_ChnlTimerId)
    {
        BST_OS_FREE(m_pstChnlLinker);
        return BST_NULL_PTR;
    }
    

    BST_SRV_CHNL_InitLink( m_pstChnlLinker, m_pSocket, m_ChnlTimerId );
    m_pstChnlLinker->ulAddrType         = BST_DSPP_FLG_ADDTYPE_TASK;
    m_pstChnlLinker->stDspp.usProcId    = m_usProcId;
    m_pstChnlLinker->stDspp.usTaskId    = m_usTaskId;
    return m_pstChnlLinker;
}

/***************************************************************
 函 数 名   : ChnlCtrlSend
 功能描述   : 信道控制发送接口
 输入参数   :
    BST_SRV_CHNL_HEAD_STRU *const pstChnHead,   链路分级数据入口

 输出参数   : 无
 返 回 值   : 无
 被调函数   :
 调用函数   :

 修改历史   :
 修改历史   :
 1.日    期 : 2015年05月10日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_VOID HeartBeat::ChnlCtrlSend(
    BST_SRV_CHNL_HEAD_STRU     *pstPktItem )
{
    BST_SRV_CHNL_LINK_STRU     *pstChnlLinker;
    BST_CORE_CPTask            *pcPtask;
    BST_IP_ERR_T                enIpErrMsg  = BST_IP_ERR_CONN;
    BST_ERR_ENUM_UINT8          enRtnVal;

    BST_ASSERT_NULL( pstPktItem );
    pstChnlLinker               = GetChnlInstance();

    if( BST_NULL_PTR == pstChnlLinker )
    {
        goto err_drop;
    }

    if( !BST_IsInfoConfiged( BST_CFGFLG_ADDR ) )
    {
        BST_DBG_LOG("ChnlCtrlSend BST_CFGFLG_ADDR not configed");
        goto err_drop;
    }
#if ( BST_OS_VER != BST_WIN32 || BST_VER_TYPE != BST_DBG_VER )
    if( !BST_HB_IsCloned() )
    {
        if( BST_IP_SKT_PROP_NONE == pstPktItem->ucPropType )
        {
            goto err_drop;
        }
        if ( BST_NULL_PTR == m_pSocket )
        {
            goto err_drop;
        }
        enIpErrMsg              = m_pSocket->Clone();
        if( BST_IP_ERR_OK != enIpErrMsg )
        {
            goto err_drop;
        }
        BST_SetConfigFlag( BST_CFGFLG_CLON );
    }
#endif
    /**
     *如果当前处于start状态，说明seq就在Modem侧，不设置任何形式的socket property
     */
    BST_DBG_LOG1("ChnlCtrlSend_TASK GetState", GetState());

    if( BST_TASK_STATE_START == GetState() )
    {
        enIpErrMsg              = m_pSocket->IoCtrl ( BST_SCKT_CMD_SYNC_PROPERTY_START,
                                                    ( BST_VOID  *)&pstPktItem->stProp );
        if( BST_IP_ERR_OK != enIpErrMsg )
        {
            BST_RLS_LOG1( "HeartBeat::ChnlCtrlSend SYNC_PROPERTY_START enIpErrMsg=%d",
                      enIpErrMsg );
            goto err_drop;
        }
        enRtnVal                = m_pExptReport->Report ( BST_PID_SYNC_PROPERTY_START,
                                                          BST_OS_SIZEOF ( BST_IP_SKT_PROPTY_STRU ),
                                                         &pstPktItem->stProp );
        if ( BST_NO_ERROR_MSG != enRtnVal )
        {
            BST_RLS_LOG1( "HeartBeat::ChnlCtrlSend SYNC_PROPERTY_START enRtnVal=%d",
                      enRtnVal );
            goto err_drop;
        }
        BST_DBG_LOG1( "ChnlCtrlSend set currentseq(Modem)", pstPktItem->stProp.ulSeqNum );
        pstChnlLinker->ulCurrentSeq = pstPktItem->stProp.ulSeqNum;
        pstPktItem->ucPropType      = BST_IP_SKT_PROP_NONE;
        pstChnlLinker->ulIsPropSet  = BST_TRUE;
        Stop();
        BST_SRV_ApiSendPTaskEvent( this, BST_SRV_T2S_RUN_STOPED, 0 );
    }

    /**
     *如果包含完整的seq信息，那么激活端口
     */
    BST_DBG_LOG1("ChnlCtrlSend_TASK ucPropType", pstPktItem->ucPropType);

    if( BST_IP_SKT_PROP_TOTAL == pstPktItem->ucPropType )
    {
        BST_UnsetConfigFlag( BST_CFGFLG_PRTY );
        /* 设置为double 状态端口*/
        enIpErrMsg              = m_pSocket->IoCtrl ( BST_SCKT_CMD_DBL_PROPERTY,
                                                    ( BST_VOID  *)&pstPktItem->stProp );
        if( BST_IP_ERR_OK != enIpErrMsg )
        {
            BST_RLS_LOG1( "HeartBeat::ChnlCtrlSend SET_PROPERTY enIpErrMsg=%d",
                      enIpErrMsg );
            goto err_drop;
        }
        BST_SetConfigFlag ( BST_CFGFLG_PRTY );
        BST_DBG_LOG1( "ChnlCtrlSend set currentseq(AP)", pstPktItem->stProp.ulSeqNum );
        pstChnlLinker->ulCurrentSeq = pstPktItem->stProp.ulSeqNum;
        pstPktItem->ucPropType      = BST_IP_SKT_PROP_NONE;
        pstChnlLinker->ulIsPropSet  = BST_TRUE;
    }
#if ( BST_OS_VER != BST_WIN32 || BST_VER_TYPE != BST_DBG_VER )
    if( !BST_IsInfoConfiged( BST_CFGFLG_PRTY ) )
    {
        goto err_drop;
    }
#endif
    BST_DBG_LOG1( "ChnlCtrlSend_TASK BST_SRV_IsChnlEmpty", BST_SRV_IsChnlEmpty( pstChnlLinker ) );
    /* 如果是第一包且busy，说明刚发生心跳 */
    if( BST_SRV_IsChnlEmpty( pstChnlLinker )  )
    {
        if( IsBusy() )
        {
            pcPtask             = this;
            BST_SRV_ApiSendPTaskEvent( pcPtask, BST_SRV_T2S_ACK_RESULT, BST_CORE_SCHD_ACK_SUC );
        }
        TxStart();
        BST_OS_TimerStop( m_stHbTxRetry.ulTimerId );
    }

    enRtnVal                        = BST_SRV_CHNL_Send( pstChnlLinker, pstPktItem );
    if( BST_ERR_SOCKET_CLSD == enRtnVal )/*Socket is closed*/
    {
        ChnlCtrlClose();
    }
    return;

err_drop:
    BST_SRV_FreeIpBlock( pstPktItem );
    return;
}

/***************************************************************
 函 数 名   : ChnlCtrlClose
 功能描述   : 关闭信道连接入口
 输入参数   : 无
 输出参数   : 无
 返 回 值   : 无
 被调函数   :
 调用函数   :

 修改历史   :
 修改历史   :
 1.日    期 : 2015年05月10日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_VOID HeartBeat::ChnlCtrlClose( BST_VOID )
{
    BST_SRV_CHNL_LINK_STRU     *pstChnlLinker;
    BST_ERR_ENUM_UINT8          ucRtnVal;
    BST_UINT32                  ulVoidProp = 0;

    pstChnlLinker               = GetChnlInstance();
    BST_ASSERT_NULL( pstChnlLinker );
    Finished();
    Stop();
    BST_SRV_ApiSendPTaskEvent( this, BST_SRV_T2S_RUN_STOPED, 0 );
    BST_SRV_CHNL_Close( pstChnlLinker );
    BST_SRV_CHNL_Clear( pstChnlLinker );
    /* 通知AP清除该Socket记录 */
    ucRtnVal                    = Report( BST_ERR_SOCKET_CLSD );
    if ( BST_NO_ERROR_MSG != ucRtnVal )
    {
        BST_RLS_LOG3( "Heartbeat::Closed ProcId=%d, TaskId=%d, IpErr Report IpErr: %u",
                      m_usProcId, m_usTaskId, ucRtnVal );
    }
    m_pSocket->IoCtrl( BST_SCKT_CMD_SYNC_PROPERTY_STOP, ( BST_VOID  *)&ulVoidProp );
    BST_RLS_LOG( "HeartBeat::ChnlCtrlSend SYNC_PROPERTY_STOP 4" );
    m_pExptReport->Report( BST_PID_SYNC_PROPERTY_STOP,
                           BST_OS_SIZEOF(BST_UINT32),
                          &ulVoidProp );
}

/***************************************************************
 函 数 名   : ChnlCtrlClear
 功能描述   : 清除信道数据入口
 输入参数   : 无
 输出参数   : 无
 返 回 值   : 无
 被调函数   :
 调用函数   :

 修改历史   :
 修改历史   :
 1.日    期 : 2015年05月10日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_VOID HeartBeat::ChnlCtrlClear( BST_VOID )
{
    BST_SRV_CHNL_LINK_STRU     *pstChnlLinker;
    BST_UINT32                  ulVoidProp = 0;

    pstChnlLinker               = GetChnlInstance();
    BST_ASSERT_NULL( pstChnlLinker );
    Finished();
    BST_SRV_CHNL_Clear( pstChnlLinker );
    m_pSocket->IoCtrl( BST_SCKT_CMD_SYNC_PROPERTY_STOP, ( BST_VOID  *)&ulVoidProp );
    BST_RLS_LOG( "HeartBeat::ChnlCtrlSend SYNC_PROPERTY_STOP 5" );
    m_pExptReport->Report( BST_PID_SYNC_PROPERTY_STOP,
                           BST_OS_SIZEOF(BST_UINT32),
                          &ulVoidProp );
}

/***************************************************************
 函 数 名   : AsEventCallback
 功能描述   : 清除信道数据入口
 输入参数   : 无
 输出参数   : 无
 返 回 值   : 无
 被调函数   :
 调用函数   :

 修改历史   :
 修改历史   :
 1.日    期 : 2015年05月10日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_VOID HeartBeat::AsEventCallback(
        BST_AS_EVT_ENUM_UINT32    enEvent,
        BST_UINT32                ulLength,
        BST_VOID                 *pvData )
{
    BST_AS_NET_RANK_ENUM_UINT32     enNewRank;
    BST_TASK_STATE_ENUM_UINT8       enTaskState;

    switch( enEvent )
    {
        case BST_AS_EVT_L3_NET_RANK:
            enTaskState             = GetState();
            BST_RLS_LOG1("BST_CTaskSchdler::AsEventCallback enTaskState = %u:", enTaskState );
            if ( BST_TASK_STATE_WAINTING != enTaskState )
            {
                return;
            }
                
            if ( BST_OS_SIZEOF(BST_AS_NET_RANK_ENUM_UINT32) != ulLength )
            {
                BST_RLS_LOG1("BST_CTaskSchdler::AsEventCallback Error Net Rank Length = %u:", ulLength );
                break;
            }
            enNewRank               = *( (BST_AS_NET_RANK_ENUM_UINT32 *)pvData );

            if( enNewRank >= BST_AS_NET_RANK_POOR )
            {
                ProcEstState( BST_APP_CONN_TYPE_BEST_CONN_POINT );
                Maintain();
            }
            break;

        default:
            break;
    }

}
