

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_IP_RcverMng.h"
#include "BST_IP_Socket.h"
#include "BST_IP_PreProc.h"
#include "BST_APP_MainTask.h"
#include "BST_DBG_MemLeak.h"
#include "lwip/tcp.h"
#include "lwip/sockets.h"
#include "BST_OS_Memory.h"
#include "BST_SRV_TaskMng.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_IP_RCVERMNG_CPP
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
const BST_SCKT_TYPE_ENUM_UINT32     g_BST_IP_SocketSupportTable[]
                                        = { BST_IP_SOCKET_SUPPORT_TABLE };
extern "C" BST_UINT16               g_BST_IP_usRtxPara;
/******************************************************************************
   6 函数实现
******************************************************************************/


BST_IP_ERR_T BST_IP_CheckSocketSupport( BST_SCKT_TYPE_ENUM_UINT32 enSocketType )
{
    BST_UINT16                          usTblLen, i;
    const BST_SCKT_TYPE_ENUM_UINT32    *penSupportTblHead;

    usTblLen                            = BST_OS_GetTableLength( g_BST_IP_SocketSupportTable );
    penSupportTblHead                   = BST_IP_SocketSupportTblHead();

    for( i=0; i<usTblLen; i++ )
    {
        if( penSupportTblHead[i] == enSocketType )
        {
            return BST_IP_ERR_OK;
        }
    }
    return BST_IP_ERR_ARG;
}


BST_IP_ERR_T BST_IP_TcpOverFlowCB( BST_UINT32 ulRealFlowValue )
{
    BST_APP_CMainTask                  *pMainTask;
    BST_ERR_ENUM_UINT8                  enRtnVal;

    pMainTask                           = BST_APP_CMainTask::GetInstance();
    if ( BST_NULL_PTR == pMainTask )
    {
        return BST_IP_ERR_MEM;
    }
    enRtnVal                            = pMainTask->TrafficOverFlow( ulRealFlowValue );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_RLS_LOG1( "BST_IP_TcpOverFlowCB Error=%u", enRtnVal );
        return BST_IP_ERR_BUF;
    }
    return BST_IP_ERR_OK;
}


BST_IP_ERR_T BST_IP_TcpConnectedCB( BST_INT32 lFd )
{
    err_t                               lErrType;
    BST_IP_CRcverMng                   *pcRcverMnger;

    pcRcverMnger                        = BST_IP_CRcverMng::GetInstance();
    BST_DBG_LOG( "BST_IP_Tcp connect successfully" );

    if ( BST_NULL_PTR == pcRcverMnger )
    {
        return ERR_MEM;
    }
    lErrType                            = pcRcverMnger->CnctedRcver( lFd );
    return lErrType;
}



BST_VOID BST_IP_TcpErrorCB( BST_INT32 lFd, BST_IP_ERR_T InIpErrMsg )
{
    BST_IP_CRcverMng                   *pcRcverMnger;

    pcRcverMnger                        = BST_IP_CRcverMng::GetInstance();
    BST_DBG_LOG( "BST_IP_Tcp BST_IP_TcpErrorCB" );

    if ( BST_NULL_PTR == pcRcverMnger )
    {
        return;
    }
    pcRcverMnger->ErrorRcver( lFd, InIpErrMsg );
}

/*lint -e438*/
BST_IP_ERR_T BST_IP_ReceivedCB( BST_INT32 lFd )
{
    BST_IP_CRcverMng                   *pcRcverMnger;
    BST_IP_PKTPROC_MODE_ENUM            enProcMode;

    pcRcverMnger                        = BST_IP_CRcverMng::GetInstance();
    enProcMode                          = BST_IP_PKT_REMOVE_PROC;

    if( BST_NULL_PTR == pcRcverMnger )
    {
        return                          ERR_MEM;
    }
    /*                                                                       *
    *The Received Message must put it here where is before call Application CB.
    *This can avoid app close socket in callback when the rcv_wnd != TCP_WND.
    *                                                                        */
    enProcMode                          = pcRcverMnger->PacketRcver( lFd );
    if ( BST_IP_PKT_NO_PROC == enProcMode )
    {
        return ERR_OK;
    }
    return ERR_OK;

}

BST_VOID BST_IP_TcpAckedCB(
    BST_INT32           lFd,
    const BST_UINT32    ulMinNumber,
    const BST_UINT32    ulMaxNumber )
{
    BST_IP_CRcverMng                   *pcRcverMnger;

    pcRcverMnger                        = BST_IP_CRcverMng::GetInstance();
    BST_DBG_LOG( "BST_IP_Tcp Acked successfully" );

    if ( BST_NULL_PTR == pcRcverMnger )
    {
        return;
    }
    pcRcverMnger->AckedRcver( lFd, ulMinNumber, ulMaxNumber );
}

BST_VOID  *BST_IP_CRcverMng::Attach(
    BST_IP_CNetRcver   *pcRawRcver,
    BST_IP_CSocket     *pcSocket )
{
    BST_IP_RCVER_BINDER_STRU   *pstRcvBinder;

    if( BST_NULL_PTR == pcRawRcver )
    {
        return BST_NULL_PTR;
    }
    if( BST_NULL_PTR == pcSocket )
    {
        return BST_NULL_PTR;
    }
    pstRcvBinder                = ( BST_IP_RCVER_BINDER_STRU *)
                                    BST_OS_MALLOC( BST_OS_SIZEOF(BST_IP_RCVER_BINDER_STRU) );
    if( BST_NULL_PTR == pstRcvBinder )
    {
        return BST_NULL_PTR;
    }
    pstRcvBinder->pcRcver       = pcRawRcver;
    pstRcvBinder->pcSocket      = pcSocket;
    lstAdd( &m_stRcverList, (NODE *)pstRcvBinder );
    return pstRcvBinder;
}

BST_VOID BST_IP_CRcverMng::Detach( BST_IP_CSocket *pcSocket )
{
    BST_IP_RCVER_BINDER_STRU   *pstRcverIdx;
    BST_IP_RCVER_BINDER_STRU   *pstRcverNextIdx;

    if ( BST_NULL_PTR == pcSocket )
    {
        return;
    }

    for ( pstRcverIdx = ( BST_IP_RCVER_BINDER_STRU *)lstFirst( &m_stRcverList );
          pstRcverIdx!= BST_NULL_PTR;
          pstRcverIdx = pstRcverNextIdx )
    {
        pstRcverNextIdx         = ( BST_IP_RCVER_BINDER_STRU *)
                                  lstNext( (NODE *)pstRcverIdx ) ;
        if ( pstRcverIdx->pcSocket == pcSocket )
        {
            lstDelete( &m_stRcverList, (NODE *)pstRcverIdx );
            BST_OS_FREE( pstRcverIdx );
            continue;
        }
    }
    return;
}

BST_IP_CRcverMng* BST_IP_CRcverMng::GetInstance( BST_VOID )
{
    static BST_IP_CRcverMng            *pcNetRcverMng = BST_NULL_PTR;

    if( BST_NULL_PTR == pcNetRcverMng )
    {
        pcNetRcverMng                   = new BST_IP_CRcverMng;
    }
    return pcNetRcverMng;
}

BST_IP_ERR_T BST_IP_CRcverMng::CnctedRcver( BST_INT32 fd  )
{
    BST_IP_RCVER_BINDER_STRU            *pRcvItem;

    if ( !BST_IP_IsFdValid( fd ) )
    {
        return BST_IP_ERR_ARG;
    }
    pRcvItem                            = FindRcver( fd );
    if ( BST_NULL_PTR == pRcvItem )
    {
        return BST_IP_ERR_OK;
    }
    if ( BST_IP_ERR_OK == pRcvItem->pcSocket->IoCtrl
                        ( BST_SCKT_CMD_CHK_CONNECTED, pRcvItem->pcSocket ) )
    {
        return pRcvItem->pcRcver->Connectd( pRcvItem->pcSocket );
    }
    else
    {
        return BST_IP_ERR_ARG;
    }
}


BST_VOID  BST_IP_CRcverMng::ErrorRcver ( BST_INT32 lFd, BST_IP_ERR_T InIpErrMsg )
{
    BST_IP_RCVER_BINDER_STRU            *pRcvItem;

    if( !BST_IP_IsFdValid( lFd ) )
    {
        return;
    }

    pRcvItem                            = FindRcver( lFd );
    if ( BST_NULL_PTR == pRcvItem )
    {
        return;
    }
    pRcvItem->pcRcver->IpErr( pRcvItem->pcSocket, InIpErrMsg );
}

BST_VOID BST_IP_CRcverMng::AckedRcver(
    BST_INT32           fd,
    const BST_UINT32    ulMinNumber,
    const BST_UINT32    ulMaxNumber )
{
    BST_IP_RCVER_BINDER_STRU            *pRcvItem;

    if ( !BST_IP_IsFdValid( fd ) )
    {
        return;
    }
    pRcvItem                            = FindRcver( fd );
    if ( BST_NULL_PTR == pRcvItem )
    {
        return;
    }
    pRcvItem->pcRcver->Acked( pRcvItem->pcSocket,ulMinNumber, ulMaxNumber );
}

BST_IP_PKTPROC_MODE_ENUM BST_IP_CRcverMng::PacketRcver(
        BST_INT32           fd )
{
    BST_IP_RCVER_BINDER_STRU           *pRcvItem;
    BST_IP_PKTPROC_MODE_ENUM            enProcMode;
    BST_UINT8                          *pucData;
    BST_INT32                           lLength;
    BST_IP_PKT_ID_T                     pPacketId;
    BST_DBG_LOG1( "BST_IP_CRcverMng::PacketRcver fd", fd );
    if ( !BST_IP_IsFdValid( fd ) )
    {
        BST_RLS_LOG("BST_IP_CRcverMng::PacketRcver fd is invalid");
        return BST_IP_PKT_NO_PROC;
    }
    pRcvItem                            = FindRcver( fd );
    if ( BST_NULL_PTR == pRcvItem )
    {
        BST_RLS_LOG("BST_IP_CRcverMng::PacketRcver pRcvItem is NULL");
        return BST_IP_PKT_NO_PROC;
    }
    enProcMode                          = BST_IP_PKT_REMOVE_PROC;
    pucData                             = ( BST_UINT8 *)BST_OS_MALLOC( BST_IP_MTU_SIZE );
    if( BST_NULL_PTR == pucData )
    {
        return BST_IP_PKT_NO_PROC;
    }
    lLength                             = pRcvItem->pcSocket->Read( pucData, BST_IP_MTU_SIZE );
    if( lLength <= 0 )
    {
        BST_RLS_LOG1("PacketRcver: pcSocket->Read len",lLength);
        BST_OS_FREE( pucData );
        return BST_IP_PKT_NO_PROC;
    }
    pPacketId                           = (BST_IP_PKT_ID_T)lwip_get_packetId( fd );
    if( BST_IP_IS_INVALID_PACKETID(pPacketId) )
    {
        BST_RLS_LOG("BST_IP_ReceivedCB: lwip_get_pbuf null.");
        BST_OS_FREE( pucData );
        return BST_IP_PKT_NO_PROC;
    }
    BST_IP_ApiRecordLastSktProp( pPacketId );

    enProcMode                          = pRcvItem->pcRcver->Received(
                                                pRcvItem->pcSocket,
                                                pucData,
                                                (const BST_UINT16)lLength );

    if( BST_IP_PKT_FORWARD_PROC == enProcMode )
    {
        BST_IP_ApiForwordPacket( pPacketId);
    }
    else
    {
        BST_DBG_LOG1("PacketRcver BST_IP_ApiUnRegistPacket",pPacketId);
        BST_IP_ApiUnRegistPacket( pPacketId );
    }
    BST_OS_FREE( pucData );
    return BST_IP_PKT_NO_PROC;
}

BST_IP_CRcverMng::BST_IP_CRcverMng( BST_VOID )
{
    lstInit( &m_stRcverList );
    return;
}

BST_IP_CRcverMng::~BST_IP_CRcverMng( BST_VOID )
{
    BST_RLS_LOG("BST_IP_CRcverMng: m_pstRcverTable Error");
}


BST_IP_RCVER_BINDER_STRU* BST_IP_CRcverMng::FindRcver( BST_INT32 fd )
{
    BST_IP_RCVER_BINDER_STRU    *pstRcverIdx;

    if( !BST_IP_IsFdValid(fd) )
    {
        return BST_NULL_PTR;
    }
    for ( pstRcverIdx = ( BST_IP_RCVER_BINDER_STRU *)lstFirst( &m_stRcverList );
          pstRcverIdx!= BST_NULL_PTR;
          pstRcverIdx = ( BST_IP_RCVER_BINDER_STRU *)lstNext( (NODE *)pstRcverIdx ) )
    {
        if ( BST_NULL_PTR == pstRcverIdx->pcRcver)
        {
            continue;
        }
        if ( BST_NULL_PTR == pstRcverIdx->pcSocket )
        {
            continue;
        }
        if( BST_IP_ERR_OK == pstRcverIdx->pcSocket->IoCtrl( BST_SCKT_CMD_CHK_FD, &fd ) )
        {
            return pstRcverIdx;
        }
    }
    return BST_NULL_PTR;
}

BST_IP_CAsRcver::BST_IP_CAsRcver( BST_VOID )
    :BST_SRV_CAsRcver( BST_SRV_GetSysMsgHandle() )
{
    m_ulOldRrcStatus    = BST_RRC_STATE_IDLE;
    g_BST_IP_usRtxPara  = TCP_RTX_INI_PARA;
    RegAsNotice( BST_AS_EVT_L3_RAT_STATE );
    RegAsNotice( BST_AS_EVT_L3_RRC_STATE );
}

BST_IP_CAsRcver::~BST_IP_CAsRcver( BST_VOID )
{
    DelEvent( BST_AS_EVT_L3_RAT_STATE );
    DelEvent( BST_AS_EVT_L3_RRC_STATE );
}


BST_IP_CAsRcver* BST_IP_CAsRcver::GetInstance( BST_VOID )
{
    static BST_IP_CAsRcver            *pcIPAsRcver = BST_NULL_PTR;

    if( BST_NULL_PTR == pcIPAsRcver )
    {
        pcIPAsRcver                   = new BST_IP_CAsRcver;
    }
    return pcIPAsRcver;
}



BST_VOID BST_IP_CAsRcver::AsEventCallback(
    BST_AS_EVT_ENUM_UINT32  enEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    BST_UINT32              ulRrcState;

    BST_DBG_LOG1("BST_IP_CAsRcver::AsEventCallback enEvent",enEvent);
    if ( BST_NULL_PTR == pvData )
    {
        return;
    }
    switch ( enEvent )
    {
        case BST_AS_EVT_L3_RAT_STATE:
            if ( ulLength != BST_OS_SIZEOF(m_ulCurrentRat) )
            {
                break;
            }

            BST_OS_MEMCPY( &m_ulCurrentRat, pvData, ulLength );

            BST_DBG_LOG1( "BST_IP_CAsRcver::AsEventCallback Bastet Support Rat=%d", m_ulCurrentRat );
            if ( BST_AS_RAT_GPRS == m_ulCurrentRat )
            {
                g_BST_IP_usRtxPara      = TCP_RTX_PARA_2G;
                lwip_update_rtx_para( TCP_RTX_PARA_2G );
            }
            break;

        case BST_AS_EVT_L3_RRC_STATE:
            if ( ulLength != BST_OS_SIZEOF(ulRrcState) )
            {
                break;
            }
            BST_OS_MEMCPY( &ulRrcState, pvData, ulLength );
            BST_DBG_LOG3( "BST_IP_CAsRcver::AsEventCallback RRC state,rat,oldrrc",
                          ulRrcState, m_ulCurrentRat,m_ulOldRrcStatus );
            /*
             * RRC建立的时候,再根据制式来更新重传时间，
             * 一种是已经建立的socket,通过lwip_update_rtx_para
             * 来更新,一种是未建立的socket,通过全局变量在创建
             * pcb时将重传时间确定。实际测试
             * rat      rrc建立前       rrc建立后
             * 4G       250ms左右       170ms左右
             * 3G       3s(IDLE->DCH)   200ms左右
             *          1.1s(PCH->DCH)
             * 2G       900ms左右       900ms左右
             */
            if ( BST_AS_IsRrcConnected( ulRrcState ) )/*rrc建立*/
            {
                if ( BST_AS_RAT_LTE == m_ulCurrentRat)  /*当前制式是4G*/
                {
                    BST_DBG_LOG("tiger debug AsEventCallback 1");
                    lwip_update_rtx_para( TCP_RTX_PARA_4G );
                    g_BST_IP_usRtxPara      = TCP_RTX_PARA_4G;
                }
                else /*当前制式是3G，因为2G不会报该事件，所以只有2种情况*/
                {
                    if( BST_RRC_STATE_IDLE == m_ulOldRrcStatus ) /*IDLE->DCH*/
                    {
                        BST_DBG_LOG("tiger debug AsEventCallback 2");
                        lwip_update_rtx_para( TCP_RTX_INI_PARA );/*3s*/
                    }
                    else /*PCH->DCH*/
                    {
                        BST_DBG_LOG("tiger debug AsEventCallback 3");
                        lwip_update_rtx_para( TCP_RTX_PARA_3G_BFRRC );/*1.5s*/
                    }
                    g_BST_IP_usRtxPara      = TCP_RTX_PARA_3G_AFRRC;
                }
            }
            else/*rrc释放恢复默认*/
            {
                BST_DBG_LOG("tiger debug AsEventCallback 4");
                lwip_update_rtx_para( TCP_RTX_INI_PARA );
                g_BST_IP_usRtxPara      = TCP_RTX_INI_PARA;
            }
            m_ulOldRrcStatus            = ulRrcState;
            break;

        default:
            break;
    }

}

