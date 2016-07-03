

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_CORE_NPTask.h"
#include "BST_OS_Memory.h"
#include "BST_DBG_MemLeak.h"
#include "BST_APP_MainTask.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_CORE_NPTASK_CPP
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


BST_CORE_CNPTask::BST_CORE_CNPTask(
    BST_PROCID_T      in_usProcId,
    BST_TASKID_T      in_usTaskId ) :BST_CORE_CPTask ( in_usProcId, in_usTaskId )
{
    BST_CORE_CRegedit                  *pcRegedit;
    BST_APP_CMainTask                  *pcMainTask;
    BST_CORE_CAPACallBack              *pcApaInterface;

    pcRegedit                           = BST_CORE_CRegedit::GetInstance();
    pcMainTask                          = BST_APP_CMainTask::GetInstance();
    BST_ASSERT_NULL( pcRegedit );

    m_CfgedFlag                         = BST_CFGFLG_NONE;
    m_pExptReport                       = new BST_DSPP_CReport ( in_usProcId, in_usTaskId );
#if( BST_VER_TYPE == BST_DBG_VER )
    m_pSocket                           = new BST_IP_CSocket ( in_usProcId, in_usTaskId );
#else
    m_pSocket                           = new BST_IP_CSocket();
#endif
    m_ProtolType                        = BST_PRTC_TYPE_INVALID;

    pcApaInterface                      = this;
    pcRegedit->Regist ( this, pcApaInterface, BST_DSPP_VER_A );

    pcRegedit->Regist ( this, BST_PID_PERIODIC, BST_OS_SIZEOF ( BST_TICK_T ),
                        BST_NULL_PTR);
    pcRegedit->Regist ( this, BST_PID_PROTOCOL_TYPE, BST_OS_SIZEOF ( BST_SCKT_TYPE_ENUM_UINT32 ),
                        BST_NULL_PTR );
    pcRegedit->Regist ( this, BST_PID_SOCKET_INFO, BST_OS_SIZEOF ( BST_IP_SOCKET_ADD_T ),
                        BST_NULL_PTR );
    pcRegedit->Regist ( this, BST_PID_SOCKET_PROPERTY, BST_OS_SIZEOF ( BST_IP_SKT_PROPTY_STRU),
                        BST_NULL_PTR )  ;
    pcRegedit->Regist ( this, BST_PID_TRAFFIC_FLOW, BST_OS_SIZEOF ( BST_IP_TRAFFIC_FLOW_STRU),
                        BST_NULL_PTR );/*注册EMAIL流量查询*/
    if ( BST_NULL_PTR != pcMainTask )
    {
        pcMainTask->Attach( this );
    }
}

BST_CORE_CNPTask::~BST_CORE_CNPTask ( BST_VOID )
{
    BST_CORE_CRegedit                  *pcRegedit;
    BST_APP_CMainTask                  *pcMainTask;

    BST_ERR_ENUM_UINT8                  ucRtnVal;

    BST_DBG_LOG( "BST_CORE_CNPTask::~BST_CORE_CNPTask in" );
    pcRegedit                       = BST_CORE_CRegedit::GetInstance();
    pcMainTask                      = BST_APP_CMainTask::GetInstance();
    
    if ( BST_NULL_PTR != m_pExptReport )
    {
        ucRtnVal                    = Report ( BST_TRAFFIC_FLOW_REPORT );
        if ( BST_NO_ERROR_MSG != ucRtnVal )
        {
            BST_RLS_LOG1( "BST_CORE_CNPTask::~BST_CORE_CNPTask Report Traffic Error: %u", ucRtnVal );
        }
        ucRtnVal                    = Report ( BST_ERR_TASK_REMOVED );
        if ( BST_NO_ERROR_MSG != ucRtnVal )
        {
            BST_RLS_LOG1( "BST_CORE_CNPTask::~BST_CORE_CNPTask Report Removed Error: %u", ucRtnVal );
        }
        delete m_pExptReport;
    }
    if ( BST_NULL_PTR != pcRegedit )
    {
        pcRegedit->unRegist ( this );
    }
    if ( BST_NULL_PTR != pcMainTask )
    {
        pcMainTask->Detach ( this );
    }
    BST_DBG_LOG1( "BST_CORE_CNPTask::~BST_CORE_CNPTask m_pSocket=%p",
                  m_pSocket );
    if ( BST_NULL_PTR != m_pSocket )
    {
        delete m_pSocket;
    }
}

BST_ERR_ENUM_UINT8  BST_CORE_CNPTask::ReportSocketProperty( BST_VOID )
{
    BST_ERR_ENUM_UINT8          enRtnVal;
    BST_IP_ERR_T                enIpErr;
    BST_IP_SKT_PROPTY_STRU      stSktProperty;
    enRtnVal                    = BST_ERR_UNREACHABLE;
    enIpErr                     = m_pSocket->IoCtrl ( BST_SCKT_CMD_RPT_PROPERTY,
                                                     &stSktProperty );
    if ( BST_IP_ERR_OK == enIpErr )
    {
        BST_ResetPrptyFlag();
        enRtnVal                = m_pExptReport->Report ( BST_PID_SOCKET_PROPERTY,
                                                          BST_OS_SIZEOF ( BST_IP_SKT_PROPTY_STRU ),
                                                         &stSktProperty );
        if ( BST_NO_ERROR_MSG == enRtnVal )
        {
            return enRtnVal;
        }
    }
    BST_RLS_LOG2( "BST_CORE_CNPTask::Report Get Propery Error, Ip_Err =%u, Rpt_Err=%u",\
                   enIpErr, enRtnVal );
    return BST_ERR_UNREACHABLE;
    
}

BST_ERR_ENUM_UINT8  BST_CORE_CNPTask::ReportTrafficFlow( BST_VOID )
{
    BST_ERR_ENUM_UINT8          enRtnVal;
    BST_IP_ERR_T                enIpErr;
    BST_IP_TRAFFIC_FLOW_STRU    stSktTrFlow;

    enRtnVal                    = BST_ERR_UNREACHABLE;
    stSktTrFlow.ulRxByte        = 0;
    stSktTrFlow.ulTxByte        = 0;
    enIpErr                     = m_pSocket->IoCtrl ( BST_SCKT_CMD_GET_TRAFFIC_FLOW,
                                                      &stSktTrFlow );
    if ( BST_IP_ERR_OK == enIpErr )
    {
        if( ( 0 != stSktTrFlow.ulRxByte ) || ( 0 != stSktTrFlow.ulTxByte ) )
        {
            enRtnVal            = m_pExptReport->Report ( BST_PID_TRAFFIC_FLOW,
                                                          BST_OS_SIZEOF ( BST_IP_TRAFFIC_FLOW_STRU ),
                                                         &stSktTrFlow );
        }
        if ( BST_NO_ERROR_MSG == enRtnVal )
        {
            return enRtnVal;
        }
    }
    BST_RLS_LOG2( "BST_CORE_CNPTask::Report Traffic Flow, Ip_Err =%u, Rpt_Err=%u",\
                   enIpErr, enRtnVal );
    return BST_ERR_UNREACHABLE;
}

BST_ERR_ENUM_UINT8  BST_CORE_CNPTask::Report ( BST_ERR_ENUM_UINT8  enErrVal )
{
    if ( BST_NULL_PTR == m_pExptReport )
    {
        BST_RLS_LOG( "BST_CORE_CNPTask::Report m_pExptReport=NULL" );
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_NULL_PTR == m_pSocket )
    {
        BST_RLS_LOG( "BST_CORE_CNPTask::Report m_pSocket=NULL" );
        return BST_ERR_INVALID_PTR;
    }
    if ( !IsValidReportException ( enErrVal ))
    {
        BST_RLS_LOG( "BST_CORE_CNPTask::Report enErrVal is invalid" );
        return BST_ERR_ILLEGAL_PARAM;
    }
    BST_DBG_LOG1( "BST_CORE_CNPTask::Report enErrVal=%d",
                  enErrVal );
    if ( BST_NOT_HEARTBEAT_PACK == enErrVal )
    {
        return ReportSocketProperty();
    }
    else if ( BST_TRAFFIC_FLOW_REPORT == enErrVal )
    {
        return ReportTrafficFlow();
    }
    else
    {
        return ( m_pExptReport->Report ( enErrVal ) );
    }
}


BST_UINT16 BST_CORE_CNPTask::InquiredSocketProperty(
    BST_UINT16  usDataSize,
    BST_VOID   *const pData )
{
    BST_IP_ERR_T                        enIpErr;

    BST_DBG_LOG ( " BST_CORE_CNPTask::InquiredSocketProperty Enter.");
    if ( usDataSize < BST_OS_SIZEOF ( BST_IP_SKT_PROPTY_STRU ) )
    {
        BST_RLS_LOG1 ( "BST_CORE_CNPTask::InquiredSocketProperty usDataSize=%d",
                       usDataSize );
        return BST_CORE_INVALID_INQUIRED_LEN;
    }
    Stop();
    /*如果没有收到心跳回复，说明任务还在运行，这个时候不清理pcb*/
    enIpErr                     = m_pSocket->IoCtrl ( BST_SCKT_CMD_GET_PROPERTY, pData );

    BST_ResetPrptyFlag();
    ( BST_VOID )PidInquired ( BST_PID_SOCKET_PROPERTY, usDataSize, pData );
    if ( BST_IP_ERR_OK == enIpErr )
    {
        return ( BST_OS_SIZEOF ( BST_IP_SKT_PROPTY_STRU ) );
    }
    else
    {
        return BST_CORE_INVALID_INQUIRED_LEN;
    }
}


BST_UINT16 BST_CORE_CNPTask::InquiredTrafficFlow(
    BST_UINT16  usDataSize,
    BST_VOID   *const pData )
{
    BST_IP_ERR_T                        enIpErr;

    BST_DBG_LOG( "BST_CORE_CNPTask::InquiredTrafficFlow email traffic flow info");
    if ( usDataSize < BST_OS_SIZEOF ( BST_IP_TRAFFIC_FLOW_STRU ) )
    {
        BST_RLS_LOG1( "BST_CORE_CNPTask::InquiredTrafficFlow usDataSize=%u",
                      usDataSize );
        return BST_CORE_INVALID_INQUIRED_LEN;
    }
    enIpErr                     = m_pSocket->IoCtrl ( BST_SCKT_CMD_GET_TRAFFIC_FLOW, pData );
    ( BST_VOID )PidInquired ( BST_PID_TRAFFIC_FLOW, usDataSize, pData );
    if ( BST_IP_ERR_OK == enIpErr )
    {
        return ( BST_OS_SIZEOF ( BST_IP_TRAFFIC_FLOW_STRU ) );
    }
    else
    {
        return BST_CORE_INVALID_INQUIRED_LEN;
    }
}


BST_UINT16 BST_CORE_CNPTask::Inquired(
    BST_CORE_PID_ENUM_UINT16 enParamId,
    BST_UINT16               usDataSize,
    BST_VOID                *const pData )
{

    if ( !BST_CORE_IsPidValid ( enParamId ) )
    {
        BST_RLS_LOG1( "BST_CORE_CNPTask::Inquired enParamId=%u is invalid",
                      usDataSize );
        return BST_CORE_INVALID_INQUIRED_LEN;
    }

    if ( ( BST_NULL_PTR == pData ) || ( 0 == usDataSize ) )
    {
        BST_RLS_LOG2( "BST_CORE_CNPTask::Inquired pData=%p,usDataSize=%u",
                      pData, usDataSize );
        return BST_CORE_INVALID_INQUIRED_LEN;
    }

    if ( BST_NULL_PTR == m_pSocket )
    {
        BST_RLS_LOG( "BST_CORE_CNPTask::Inquired m_pSocket=NULL" );
        return BST_CORE_INVALID_INQUIRED_LEN;
    }

    switch ( enParamId )
    {
        case BST_PID_SOCKET_PROPERTY:
           return InquiredSocketProperty( usDataSize, pData );

        case BST_PID_TRAFFIC_FLOW:
           return InquiredTrafficFlow( usDataSize, pData );

        default:
            return PidInquired ( enParamId, usDataSize, pData );
    }
}

BST_ERR_ENUM_UINT8 BST_CORE_CNPTask::ConfigedPriodic(
    BST_UINT16                  usLen,
    const BST_VOID             *const pData,
    BST_UINT8                 **pucNewAddr )
{
    BST_UINT32                          ulTimerTicks;
    BST_ERR_ENUM_UINT8                  ucRtnVal;

    if ( usLen < BST_OS_SIZEOF ( BST_UINT32 ) )
    {
        BST_RLS_LOG1( "BST_CORE_CNPTask::ConfigedPriodic usLen=%u",
                      usLen );
        return BST_ERR_PAR_LEN;
    }
    BST_OS_MEMCPY( &ulTimerTicks, pData, BST_OS_SIZEOF(BST_UINT32) );
    ucRtnVal                    = ConfigCycleTicks ( ulTimerTicks );
    if ( ucRtnVal == BST_NO_ERROR_MSG )
    {
       *pucNewAddr              = ( BST_UINT8 * )&m_ulCycle;
        BST_SetConfigFlag ( BST_CFGFLG_CYCL );
    }
    else
    {
       *pucNewAddr              = BST_NULL_PTR;
    }
    return ucRtnVal;
}


BST_ERR_ENUM_UINT8 BST_CORE_CNPTask::ConfigedSockeInfo(
    BST_UINT16                  usLen,
    const BST_VOID             *const pData,
    BST_UINT8                 **pucNewAddr )
{
    BST_IP_ERR_T                        enIpErrMsg;
    BST_ERR_ENUM_UINT8                  ucRtnVal;

    if ( usLen < BST_OS_SIZEOF ( BST_IP_SOCKET_ADD_T ) )
    {
        BST_RLS_LOG1( "BST_CORE_CNPTask::ConfigedPriodic usLen=%u",
                      usLen );
        return BST_ERR_PAR_LEN;
    }

    if ( !BST_IP_IsValidIpAddress( ( BST_IP_SOCKET_ADD_T * )pData ) )
    {
        Report( BST_TRAFFIC_FLOW_REPORT );
    }
    enIpErrMsg                  = m_pSocket->IoCtrl ( BST_SCKT_CMD_SET_ADDRESS,
                                                    ( BST_VOID  *)pData );
    BST_DBG_UPDATE_IP_INFO( m_usProcId, m_usTaskId, (( BST_IP_SOCKET_ADD_T * )pData) );
    if ( BST_IP_ERR_OK == enIpErrMsg )
    {
        enIpErrMsg              = m_pSocket->IoCtrl ( BST_SCKT_CMD_GET_ADDRPTR,
                                                    ( BST_VOID  *)pucNewAddr );
        if ( BST_IP_ERR_OK == enIpErrMsg )
        {
            if ( BST_IP_IsValidIpAddress( ( BST_IP_SOCKET_ADD_T * )( *pucNewAddr ) ) )
            {
                BST_SetConfigFlag ( BST_CFGFLG_ADDR );
            }
            else
            {
                /* 清除Config， 防止Socket进行Clone，并挂起任务 */
                BST_UnsetConfigFlag ( BST_CFGFLG_ADDR );
                BST_UnsetConfigFlag ( BST_CFGFLG_CLON );
                Suspend();
            }
            ucRtnVal            = BST_NO_ERROR_MSG;
        }
        else
        {
            BST_UnsetConfigFlag ( BST_CFGFLG_ADDR );
            BST_UnsetConfigFlag ( BST_CFGFLG_CLON );
            ucRtnVal            = BST_ERR_ILLEGAL_PARAM;
        }
    }
    else
    {
        ucRtnVal                = BST_ERR_ILLEGAL_PARAM;
    }
    return ucRtnVal;
}


BST_ERR_ENUM_UINT8 BST_CORE_CNPTask::ConfigedSockeProperty(
    BST_UINT16                  usLen,
    const BST_VOID             *const pData,
    BST_UINT8                 **pucNewAddr )
{
    BST_IP_ERR_T                        enIpErrMsg;
    BST_ERR_ENUM_UINT8                  ucRtnVal;

    if ( BST_NULL_PTR == m_pSocket )
    {
        BST_RLS_LOG( "BST_CORE_CNPTask::ConfigedSockeProperty m_pSocket=NULL" );
        return BST_ERR_ILLEGAL_PARAM;
    }

    if ( usLen < BST_OS_SIZEOF ( BST_IP_SKT_PROPTY_STRU ) )
    {
        BST_RLS_LOG1( "BST_CORE_CNPTask::ConfigedSockeProperty usLen=%u",
                      usLen );
        return BST_ERR_PAR_LEN;
    }

    enIpErrMsg                  = m_pSocket->IoCtrl ( BST_SCKT_CMD_SET_PROPERTY,
                                                    ( BST_VOID  *)pData );
    BST_DBG_LOG1( "BST_CORE_CNPTask::ConfigedSockeProperty enIpErrMsg=%d",
                  enIpErrMsg );
    if( BST_IP_ERR_OK == enIpErrMsg )
    {
        BST_SetConfigFlag ( BST_CFGFLG_PRTY );
        ucRtnVal                = BST_NO_ERROR_MSG;
    }
    else
    {
        ucRtnVal                = BST_ERR_ILLEGAL_PARAM;
    }
    return ucRtnVal;
}


BST_ERR_ENUM_UINT8 BST_CORE_CNPTask::Configed(
    BST_CORE_PID_ENUM_UINT16    enParamId,
    BST_UINT16                  usLen,
    const BST_VOID             *const pData,
    BST_UINT8                 **pucNewAddr )
{
    BST_ERR_ENUM_UINT8      ucRtnVal;

    if ( !BST_CORE_IsPidValid ( enParamId ) )
    {
        BST_RLS_LOG1( "BST_CORE_CNPTask::Configed enParamId=%d",
                      enParamId );
        return BST_ERR_PAR_UNKNOW;
    }

    if ( BST_NULL_PTR == pData )
    {
        BST_RLS_LOG( "BST_CORE_CNPTask::Configed pData=NULL" );
        return BST_ERR_INVALID_PTR;
    }

    if ( BST_NULL_PTR == pucNewAddr )
    {
        BST_RLS_LOG( "BST_CORE_CNPTask::Configed pucNewAddr=NULL" );
        return BST_ERR_INVALID_PTR;
    }

    ucRtnVal                    = BST_NO_ERROR_MSG;
   *pucNewAddr                  = BST_NULL_PTR;

    switch ( enParamId )
    {
        case BST_PID_PERIODIC:
            ucRtnVal            = ConfigedPriodic( usLen, pData, pucNewAddr);
            break;

        case BST_PID_SOCKET_INFO:
            ucRtnVal            = ConfigedSockeInfo( usLen, pData, pucNewAddr);
            break;

        case BST_PID_SOCKET_PROPERTY:
            ucRtnVal            = ConfigedSockeProperty( usLen, pData, pucNewAddr);
            break;

        default:
            ucRtnVal            = BST_ERR_PAR_UNKNOW;
            break;
    }

    switch ( ucRtnVal )
    {
        case BST_NO_ERROR_MSG:
            PidConfiged ( enParamId,
                          usLen,
                          pData,
                          m_CfgedFlag,
                          pucNewAddr );
            break;

        case BST_ERR_PAR_UNKNOW:
            ucRtnVal    = PidConfiged ( enParamId,
                                        usLen,
                                        pData,
                                        m_CfgedFlag,
                                        pucNewAddr );
            break;

        default:
            break;
    }

    return ucRtnVal;
}


BST_UINT16 BST_CORE_CNPTask::PidInquired (
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usDataSize,
    BST_VOID                 *const pData )
{
    return 0;
}

BST_ERR_ENUM_UINT8 BST_CORE_CNPTask::PidConfiged(
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usLen,
    const BST_VOID           *const pData,
    BST_UINT32                ulBaseCfged,
    BST_UINT8               **pucNewAddr )
{
    return BST_ERR_PAR_UNKNOW;
}
