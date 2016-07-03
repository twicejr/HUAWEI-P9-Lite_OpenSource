

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_DSPP_TrsLayer.h"
#include "BST_DSPP_CtrLayer.h"
#include "BST_DRV_Acom.h"
#include "BST_OS_Memory.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_Event.h"
#include "BST_SRV_TaskMng.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DSPP_TRSLAYER_CPP
/*lint +e767*/
/*****************************************************************************
  2 函数实现
******************************************************************************/


BST_DSPP_CTrsDlVa::BST_DSPP_CTrsDlVa ( BST_VOID )
    : BST_DSPP_CDlLayerBase ( BST_DSPP_LAYER_TRS, BST_DSPP_VER_A )
{
    lstInit( &m_stRcvPktList );
}

BST_DSPP_CTrsDlVa::~BST_DSPP_CTrsDlVa ( BST_VOID )
{
    BST_RLS_LOG("BST_DSPP_CTrsDlVa::~BST_DSPP_CTrsDlVa Error");
}


BST_DSPP_CTrsDlVa *BST_DSPP_CTrsDlVa::GetInstance ( BST_VOID )
{
    static BST_DSPP_CTrsDlVa           *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance                     = new BST_DSPP_CTrsDlVa ();
    }

    return s_pInstance;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CTrsDlVa::CheckPicNumber(
    BST_DSPP_TP_PACKET_STRU *pstRcvInfo,
    BST_DSPP_PKTPC_T         usPicNum )
{
    BST_DSPP_PIC_STRU                  *pstPicItem;

    if ( BST_NULL_PTR == pstRcvInfo )
    {
        return BST_ERR_UNREACHABLE;
    }
    if ( usPicNum > pstRcvInfo->stRcvMng.ucPicAmount )
    {
        return BST_ERR_UNREACHABLE;
    }

    for( pstPicItem = (BST_DSPP_PIC_STRU *)lstFirst( &pstRcvInfo->stPicList );
         pstPicItem != BST_NULL_PTR;
         pstPicItem = (BST_DSPP_PIC_STRU *)lstNext( (NODE *)pstPicItem ) )
    {
        if ( pstPicItem->usPicNum == usPicNum )
        {
            BST_RLS_LOG1( "BST_DSPP_CTrsDlVa::CheckPicNumber usPicNum=%u exist",
                         usPicNum );
            return BST_ERR_UNREACHABLE;
        }
    }
    return BST_NO_ERROR_MSG;
}


BST_BOOL BST_DSPP_CTrsDlVa::CheckValidLength( BST_UINT16 usLen )
{
    if ( ( usLen >= ( BST_DSPP_TPA_FLAG_LEN + BST_DSPP_TPA_HEAD_LEN ) )
      && ( usLen <= BST_ACOM_PACKET_SIZE ) )
    {
        return BST_TRUE;
    }
    else
    {
        return BST_FALSE;
    }
}

BST_DSPP_VERION_ENUM_UINT8  BST_DSPP_CTrsDlVa::ProcRequest(
    BST_DSPP_HEAD_STRU      *const pstDsppHead,
    BST_DSPP_TP_PKTMSG_STRU *stPktPicMsg,
    BST_UINT8               *pucSdu,
    BST_UINT16               usSduLen )
{
    BST_UINT16                          usCpyCnt;
    BST_DSPP_TP_PACKET_STRU            *pstBufQueue;
    BST_DSPP_PIC_STRU                  *pstPicItem;
    BST_ERR_ENUM_UINT8                  ucRrnVal;

    ucRrnVal                    = BST_NO_ERROR_MSG;
    usCpyCnt                    = 0;
    pstBufQueue                 = BST_NULL_PTR;
    ucRrnVal                    = BST_NO_ERROR_MSG;

    /*
     *非分片包，DSPP运作在ZERO-COPY模式，提升传输效率
     */
    if ( 1 == stPktPicMsg->ucPicAmount )
    {
        pstDsppHead->usLength   = usSduLen - BST_DSPP_TPA_HEAD_LEN;
        if ( pstDsppHead->usLength )
        {
            pstDsppHead->pucData= pucSdu + BST_DSPP_TPA_HEAD_LEN;
        }
        else
        {
            pstDsppHead->pucData= BST_NULL_PTR;
        }
        pstDsppHead->enTpVer    = BST_DSPP_VER_A;
        pstDsppHead->enCpVer    = ( BST_DSPP_VERION_ENUM_UINT8 )pucSdu[BST_DSPP_TP_CPL_VER];;
        pstDsppHead->usPktNum   = stPktPicMsg->usPktNum;
        return pstDsppHead->enCpVer;
    }

    pstBufQueue                 = Joint ( stPktPicMsg,
                                          pucSdu,
                                          usSduLen );
    BST_OS_FREE( pstDsppHead->pucSource);
    if ( BST_NULL_PTR == pstBufQueue )
    {
        BST_RLS_LOG( "BST_DSPP_CTrsDlVa::ProcRequest pstBufQueue=NULL" );
        return BST_DSPP_VER_INVALID;
    }
    ucRrnVal                    = ParseHeadInfo ( pstDsppHead,
                                 ( BST_UINT8 * )&pstBufQueue->stRcvMng,
                                                BST_OS_SIZEOF ( BST_DSPP_TP_PKTMSG_STRU ) );
    if ( BST_NO_ERROR_MSG != ucRrnVal )
    {
        BST_RLS_LOG1( "BST_DSPP_CTrsDlVa::ProcRequest ParseHeadInfo Err=%u",
                      ucRrnVal );
        return BST_DSPP_VER_INVALID;
    }

    pstDsppHead->pucSource      = ( BST_UINT8 * )BST_OS_MALLOC ( pstDsppHead->usLength );
    if ( BST_NULL_PTR == pstDsppHead->pucSource )
    {
        BST_RLS_LOG( "BST_DSPP_CTrsDlVa::ProcRequest No Mem" );
        ClrRcvManager ( stPktPicMsg->usPktNum );
        return BST_DSPP_VER_INVALID;
    }
    pstDsppHead->pucData        = pstDsppHead->pucSource;
    for( pstPicItem = (BST_DSPP_PIC_STRU *)lstFirst( &pstBufQueue->stPicList );
         pstPicItem != BST_NULL_PTR;
         pstPicItem = (BST_DSPP_PIC_STRU *)lstNext( (NODE *)pstPicItem ) )
    {
        if ( usCpyCnt + pstPicItem->usLength  > pstDsppHead->usLength )
        {
            BST_OS_FREE ( pstDsppHead->pucData );
            ClrRcvManager ( pstBufQueue->stRcvMng.usPktNum );
            return BST_DSPP_VER_INVALID;
        }

        BST_OS_MEMCPY ( pstDsppHead->pucData + usCpyCnt,
                        pstPicItem->pucData, pstPicItem->usLength );
        usCpyCnt               += pstPicItem->usLength;
    }
    ClrRcvManager ( pstBufQueue->stRcvMng.usPktNum );
    return ( pstDsppHead->enCpVer );
}


BST_DSPP_VERION_ENUM_UINT8  BST_DSPP_CTrsDlVa::ParsePrimitive(
    BST_DSPP_HEAD_STRU      *const pstDsppHead,
    BST_DSPP_TP_PKTMSG_STRU *stPktPicMsg,
    BST_UINT8               *pucSdu,
    BST_UINT16               usSduLen )
{
    BST_DSPP_CTrsUlVa      *pTrsUlVerA;

    pTrsUlVerA              = BST_NULL_PTR;

    if ( BST_NULL_PTR == pstDsppHead )
    {
        return BST_DSPP_VER_INVALID;
    }

    if ( BST_NULL_PTR == stPktPicMsg )
    {
        return BST_DSPP_VER_INVALID;
    }
    if ( ( BST_NULL_PTR == pucSdu )
       ||( 0 == usSduLen ) )
    {
        return BST_DSPP_VER_INVALID;
    }
    switch ( stPktPicMsg->enPrimitive )
    {
        case BST_DSPP_PRMTV_REQUEST:
        {
            return( ProcRequest( pstDsppHead, stPktPicMsg, pucSdu, usSduLen ) );
        }
        case BST_DSPP_PRMTV_ACK:
        {
            pTrsUlVerA      = BST_DSPP_CTrsUlVa::GetInstance ();
            if ( BST_NULL_PTR == pTrsUlVerA )
            {
                return BST_DSPP_VER_INVALID;
            }

            pTrsUlVerA->RxAck( stPktPicMsg->usPktNum, stPktPicMsg->ucPicNum );
            BST_OS_FREE( pstDsppHead->pucSource );
            return BST_DSPP_VER_VOID;
        }

        default:
            return BST_DSPP_VER_INVALID;
    }
}


BST_ERR_ENUM_UINT8  BST_DSPP_CTrsDlVa::UnpackInternal (
    BST_DSPP_HEAD_STRU         *const pstDsppHead,
    BST_DSPP_VERION_ENUM_UINT8 *const penNextVer )
{
    BST_UINT16                  usLen;
    BST_DSPP_TP_PKTMSG_STRU     stPktPicMsg;
    BST_UINT8                  *pucData;
    BST_ERR_ENUM_UINT8          ucRrnVal;
    BST_BOOL                    bRtnVal;

    BST_DBG_LOG ( "BST_DSPP_CTrsDlVa UnpackInternal" );
    usLen                       = 0;
    pucData                     = BST_NULL_PTR;
    ucRrnVal                    = BST_NO_ERROR_MSG;

    if ( BST_NULL_PTR == penNextVer )
    {
        return BST_ERR_LAYER_VER;
    }
    if ( BST_NULL_PTR == pstDsppHead )
    {
        return BST_ERR_LAYER_VER;
    }
    if ( BST_NULL_PTR == pstDsppHead->pucData )
    {
        return BST_ERR_LAYER_VER;
    }
    bRtnVal                    = CheckValidLength ( pstDsppHead->usLength );
    if ( BST_TRUE != bRtnVal )
    {
        BST_RLS_LOG1( "BST_DSPP_CTrsDlVa::UnpackInternal CheckValidLength Err=%d",
                      bRtnVal );
        return BST_ERR_LAYER_VER;
    }
    pucData                     = pstDsppHead->pucData
                                + BST_DSPP_TPA_BEGIN_FLAG_LEN;
    usLen                       = pstDsppHead->usLength
                                - BST_DSPP_TPA_FLAG_LEN;
    ucRrnVal                    = GetPktPicInfo ( &stPktPicMsg, pucData, usLen );
    if ( BST_NO_ERROR_MSG != ucRrnVal )
    {
        BST_RLS_LOG1( "BST_DSPP_CTrsDlVa::UnpackInternal GetPktPicInfo Err=%u",
                      ucRrnVal );
        return BST_ERR_LAYER_VER;
    }
    *penNextVer                 = ParsePrimitive( pstDsppHead,
                                                 &stPktPicMsg,
                                                  pucData,
                                                  usLen );
    if( BST_DSPP_VER_INVALID == *penNextVer )
    {
        return BST_ERR_LAYER_VER;
    }
    else
    {
        return BST_NO_ERROR_MSG;
    }
}


BST_DSPP_TP_PACKET_STRU *BST_DSPP_CTrsDlVa::CreatRcvManager(
    BST_DSPP_TP_PKTMSG_STRU *pstPacketInfo )
{
    BST_DSPP_TP_PACKET_STRU            *pstPktRcvBuf;

    if( BST_NULL_PTR == pstPacketInfo )
    {
        return BST_NULL_PTR;
    }
    pstPktRcvBuf    = ( BST_DSPP_TP_PACKET_STRU * )BST_OS_MALLOC
                      ( BST_OS_SIZEOF ( BST_DSPP_TP_PACKET_STRU ) );

    if ( BST_NULL_PTR == pstPktRcvBuf )
    {
        return BST_NULL_PTR;
    }
    BST_OS_MEMCPY ( &pstPktRcvBuf->stRcvMng,
                    pstPacketInfo, BST_OS_SIZEOF ( BST_DSPP_TP_PKTMSG_STRU ) );
    pstPktRcvBuf->stRcvMng.ucPicNum     = BST_DSPP_TP_FIRST_PIECE_NUMBER;
    pstPktRcvBuf->stRcvMng.usAmountLen  = 0;
    lstInit( &pstPktRcvBuf->stPicList );
    pstPktRcvBuf->stRcvMng.enCpVer      = BST_DSPP_VER_INVALID;
    pstPktRcvBuf->ulTimerId             = BST_OS_TimerCreateCpp ( this,
                                                                  BST_NULL_PTR,
                                                                  BST_SRV_GetSysMsgHandle() );
    return pstPktRcvBuf;
}


BST_VOID BST_DSPP_CTrsDlVa::ClrRcvManager ( BST_DSPP_PKTSN_T usPktNum )
{
    BST_DSPP_PIC_STRU          *pstPicNode;
    BST_DSPP_PIC_STRU          *pstPicNodeNext;
    BST_DSPP_TP_PACKET_STRU    *pstPacketNode;
    BST_DSPP_TP_PACKET_STRU    *pstPacketNodeNext;

    for( pstPacketNode = (BST_DSPP_TP_PACKET_STRU *)lstFirst( &m_stRcvPktList );
         pstPacketNode!= BST_NULL_PTR;
         pstPacketNode = pstPacketNodeNext )
    {
        pstPacketNodeNext       = (BST_DSPP_TP_PACKET_STRU *)
                                  lstNext((NODE *)pstPacketNode);
        if ( pstPacketNode->stRcvMng.usPktNum != usPktNum )
        {
            continue;
        }

        for ( pstPicNode  = (BST_DSPP_PIC_STRU *)lstFirst( &pstPacketNode->stPicList );
              pstPicNode != BST_NULL_PTR;   /*here pstPicNode is not NULL*/
              pstPicNode  = pstPicNodeNext )
        {
            pstPicNodeNext      = (BST_DSPP_PIC_STRU *)
                                  lstNext( (NODE *) pstPicNode );

            lstDelete( &pstPacketNode->stPicList,
                        (NODE *)pstPicNode );
            BST_OS_FREE ( pstPicNode->pucData );
            BST_OS_FREE ( pstPicNode );
        }
        BST_OS_TimerRemove ( pstPacketNode->ulTimerId );
        lstDelete( &m_stRcvPktList, (NODE *)pstPacketNode );
        BST_OS_FREE ( pstPacketNode );
    }
}


BST_DSPP_TP_PACKET_STRU *BST_DSPP_CTrsDlVa::FindRcvInfo(
    BST_DSPP_PKTSN_T usInPktNumber )
{
    BST_DSPP_TP_PACKET_STRU    *pstPacketNode;

    for( pstPacketNode = (BST_DSPP_TP_PACKET_STRU *)lstFirst( &m_stRcvPktList );
         pstPacketNode!= BST_NULL_PTR;
         pstPacketNode = (BST_DSPP_TP_PACKET_STRU *)lstNext((NODE *)pstPacketNode) )
    {
        if ( pstPacketNode->stRcvMng.usPktNum != usInPktNumber )
        {
            continue;
        }
        return( pstPacketNode );
    }
    BST_RLS_LOG( "BST_DSPP_CTrsDlVa::FindRcvInfo No packet before" );
    return BST_NULL_PTR;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CTrsDlVa::GetPktPicInfo(
    BST_DSPP_TP_PKTMSG_STRU *pstPacketInfo,
    BST_UINT8 const         *pucData,
    BST_UINT16               usLength )
{
    if ( usLength < BST_DSPP_TPA_HEAD_LEN )
    {
        return BST_ERR_PAR_UNKNOW;
    }

    if ( ( BST_NULL_PTR == pucData )
      || ( BST_NULL_PTR == pstPacketInfo ) )
    {
        return BST_ERR_INVALID_PTR;
    }
    pstPacketInfo->ucDeviceId   = pucData[BST_DSPP_TP_DVC_ID];
    pstPacketInfo->usPktNum     = BST_DSPP_U8_TO_U16
                                ( pucData[BST_DSPP_TP_PKT_NUM_L],
                                  pucData[BST_DSPP_TP_PKT_NUM_H] );
    pstPacketInfo->ucPicAmount  = pucData[BST_DSPP_TP_PIC_AMT];
    pstPacketInfo->ucPicNum     = pucData[BST_DSPP_TP_PIC_NUM];
    pstPacketInfo->enPrimitive  = ( BST_DSPP_PRIMITIVE_ENUM_UINT8 )
                                  pucData[BST_DSPP_TP_PRMIMTV];
    return BST_NO_ERROR_MSG;
}


BST_DSPP_CDlLayerBase *BST_DSPP_CTrsDlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    switch ( enNextVer )
    {
        case BST_DSPP_VER_A:
            return ( BST_DSPP_CCtrDlVa::GetInstance() );
        case BST_DSPP_VER_C:
            return ( BST_DSPP_CCtrDlVc::GetInstance() );
        default:
            break;
    }

    return BST_NULL_PTR;
}

BST_ERR_ENUM_UINT8  BST_DSPP_CTrsDlVa::ParseHeadInfo(
    BST_DSPP_HEAD_STRU   *const pstDsppHead,
    BST_UINT8 const      *pucData,
    BST_UINT16            usLength )
{
    BST_DSPP_TP_PKTMSG_STRU    *pMsg;

    if ( BST_DSPP_TPA_HEAD_LEN > usLength )
    {
        return BST_ERR_PAR_UNKNOW;
    }
    if ( ( BST_NULL_PTR == pucData )
      || ( BST_NULL_PTR == pstDsppHead ) )
    {
        return BST_ERR_INVALID_PTR;
    }

    pMsg                        = ( BST_DSPP_TP_PKTMSG_STRU * )pucData;
    pstDsppHead->enTpVer        = BST_DSPP_VER_A;
    pstDsppHead->enCpVer        = pMsg->enCpVer;
    pstDsppHead->usPktNum       = pMsg->usPktNum;
    pstDsppHead->usLength       = pMsg->usAmountLen;
    return BST_NO_ERROR_MSG;
}


/*lint -e438*/
BST_DSPP_TP_PACKET_STRU *BST_DSPP_CTrsDlVa::Joint(
    BST_DSPP_TP_PKTMSG_STRU *pstPacketInfo,
    BST_UINT8 const         *pucData,
    BST_UINT16               usInLen )
{
    BST_UINT16                  usLen;
    BST_DSPP_TP_PACKET_STRU    *pstRcvItem;
    BST_DSPP_CTrsUlVa          *pTrsUlVerA;
    BST_DSPP_PIC_STRU          *pstPieceInfo;
    BST_ERR_ENUM_UINT8          ucRrnVal;

    usLen                       = usInLen;
    pstRcvItem                  = BST_NULL_PTR;
    ucRrnVal                    = BST_NO_ERROR_MSG;

    if ( ( BST_NULL_PTR == pstPacketInfo )
      || ( BST_NULL_PTR == pucData ) )
    {
        return BST_NULL_PTR;
    }
    BST_DBG_LOG1( "BST_DSPP_CTrsDlVa::Joint pktNum", pstPacketInfo->usPktNum );
    pstRcvItem                  = FindRcvInfo ( pstPacketInfo->usPktNum );
    if ( BST_NULL_PTR == pstRcvItem )
    {
        pstRcvItem              = CreatRcvManager ( pstPacketInfo );
        if ( BST_NULL_PTR == pstRcvItem )
        {
            BST_RLS_LOG( "BST_DSPP_CTrsDlVa::Joint CreatRcvManager pstRcvItem=NULL" );
            return BST_NULL_PTR;
        }
        pstRcvItem->stRcvMng.enCpVer    = ( BST_DSPP_VERION_ENUM_UINT8 )
                                            pucData[BST_DSPP_TP_CPL_VER];
        lstAdd( &m_stRcvPktList, (NODE *)pstRcvItem );
    }

    ucRrnVal                    = CheckPicNumber ( pstRcvItem, pstPacketInfo->ucPicNum );
    if ( BST_NO_ERROR_MSG != ucRrnVal)
    {
        BST_RLS_LOG1( "BST_DSPP_CTrsDlVa::Joint CheckPicNumber Err=%u",
                      ucRrnVal );
        return BST_NULL_PTR;
    }

    pTrsUlVerA                  = BST_DSPP_CTrsUlVa::GetInstance ();
    pstPieceInfo                = ( BST_DSPP_PIC_STRU * )
                                  BST_OS_MALLOC ( BST_OS_SIZEOF ( BST_DSPP_PIC_STRU ) );
    if ( BST_NULL_PTR == pstPieceInfo )
    {
        ClrRcvManager ( pstPacketInfo->usPktNum );
        return BST_NULL_PTR;
    }

    if ( BST_DSPP_TP_FIRST_PIECE_NUMBER == pstPacketInfo->ucPicNum )
    {
        pstRcvItem->stRcvMng.enCpVer    = ( BST_DSPP_VERION_ENUM_UINT8 )pucData[BST_DSPP_TP_CPL_VER];
    }

    usLen                      -= BST_DSPP_TPA_HEAD_LEN;
    pucData                    += BST_DSPP_TPA_HEAD_LEN;
    pstPieceInfo->usLength      = usLen;
    pstPieceInfo->usPicNum      = pstPacketInfo->ucPicNum;

    pstPieceInfo->pucData       = ( BST_UINT8 * )BST_OS_MALLOC ( usLen );
    if ( BST_NULL_PTR == pstPieceInfo->pucData )
    {
        BST_RLS_LOG( "BST_DSPP_CTrsDlVa::Joint pstPieceInfo->pucData=NULL" );
        ClrRcvManager ( pstPacketInfo->usPktNum );
        BST_OS_FREE( pstPieceInfo );
        return BST_NULL_PTR;
    }

    BST_OS_MEMCPY ( pstPieceInfo->pucData, pucData, usLen );

    pstRcvItem->stRcvMng.usAmountLen   += usLen;
    if ( pstRcvItem->stRcvMng.usAmountLen > BST_DSPP_TPA_MAX_LENGTH )
    {
        ClrRcvManager ( pstPacketInfo->usPktNum );
        BST_OS_FREE( pstPieceInfo->pucData );
        BST_OS_FREE( pstPieceInfo );
        return BST_NULL_PTR;
    }
    lstAdd( &pstRcvItem->stPicList, (NODE *)pstPieceInfo );
    pTrsUlVerA->TxAck ( pstPacketInfo );
    if ( BST_OS_IsTimerValid (pstRcvItem->ulTimerId) )
    {
        BST_OS_TimerStart ( pstRcvItem->ulTimerId,
                            BST_ACOM_RCV_EXPD_TIME );
    }

    if ( pstRcvItem->stRcvMng.ucPicAmount
         == lstCount( &pstRcvItem->stPicList ) )
    {
        BST_OS_TimerStop ( pstRcvItem->ulTimerId );
        return pstRcvItem;
    }
    else if( pstRcvItem->stRcvMng.ucPicAmount
             < lstCount( &pstRcvItem->stPicList ) )
    {
        ClrRcvManager ( pstPacketInfo->usPktNum );
    }
    return BST_NULL_PTR;
}
/*lint +e438*/

BST_VOID BST_DSPP_CTrsDlVa::RxApi(
    BST_UINT8 const *pucData,
    BST_UINT16       usLength )
{
    BST_DSPP_HEAD_STRU                  stRxHeadInfo;

    if ( BST_NULL_PTR == pucData )
    {
        return;
    }
    stRxHeadInfo.pucData    = ( BST_UINT8 *)pucData;
    stRxHeadInfo.pucSource  = ( BST_UINT8 *)pucData;
    stRxHeadInfo.usLength   = usLength;
    UnPack ( &stRxHeadInfo );
}


BST_VOID BST_DSPP_CTrsDlVa::TimerExpired( BST_OS_TIMERID_T ulId, BST_VOID* pvPara )
{
    BST_DSPP_PIC_STRU          *pstPicNode;
    BST_DSPP_PIC_STRU          *pstPicNodeNext;
    BST_DSPP_TP_PACKET_STRU    *pstPacketNode;
    BST_DSPP_TP_PACKET_STRU    *pstPacketNodeNext;

    for( pstPacketNode = (BST_DSPP_TP_PACKET_STRU *)lstFirst( &m_stRcvPktList );
         pstPacketNode!= BST_NULL_PTR;
         pstPacketNode = pstPacketNodeNext )
    {
        pstPacketNodeNext       = (BST_DSPP_TP_PACKET_STRU *)
                                  lstNext((NODE *)pstPacketNode);
        if ( pstPacketNode->ulTimerId != ulId )
        {
            continue;
        }

        for ( pstPicNode = (BST_DSPP_PIC_STRU *)lstFirst( &pstPacketNode->stPicList );
              pstPicNode!= BST_NULL_PTR;/*here pstPicNode is not NULL*/
              pstPicNode = pstPicNodeNext )
        {
            pstPicNodeNext      = (BST_DSPP_PIC_STRU *)
                                  lstNext( (NODE *) pstPicNode );

            lstDelete( &pstPacketNode->stPicList,
                        (NODE *)pstPicNode );
            BST_OS_FREE ( pstPicNode->pucData );
            BST_OS_FREE ( pstPicNode );
        }
        BST_OS_TimerRemove ( pstPacketNode->ulTimerId );
        lstDelete( &m_stRcvPktList, (NODE *)pstPacketNode );
        BST_OS_FREE ( pstPacketNode );
    }
}



BST_DSPP_CTrsUlVa::BST_DSPP_CTrsUlVa ( BST_VOID )
    : BST_DSPP_CUlLayerBase ( BST_DSPP_LAYER_TRS, BST_DSPP_VER_A )
{
    m_ReportPktNumSeq   = BST_DSPP_TP_MIN_S2M_PKTNUM;
}


BST_DSPP_CTrsUlVa::~BST_DSPP_CTrsUlVa ( BST_VOID )
{
    return;
}


BST_DSPP_CTrsUlVa *BST_DSPP_CTrsUlVa::GetInstance ()
{
    static BST_DSPP_CTrsUlVa   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CTrsUlVa ();
    }

    return s_pInstance;
}


BST_UINT16 BST_DSPP_CTrsUlVa::BuildTpAHead(
    BST_DSPP_TP_PKTMSG_STRU *pstPacketInfo,
    BST_UINT8               *pucBuffer,
    BST_UINT16               usSduLen )
{
    BST_UINT16          usTotLen;
    BST_UINT8          *pucBuf;

    if ( BST_ACOM_PACKET_SIZE
     < ( BST_DSPP_TPA_HEAD_LEN + BST_DSPP_TPA_FLAG_LEN + usSduLen) )
    {
        return 0;
    }
    if ( BST_NULL_PTR == pucBuffer )
    {
        return 0;
    }
    usTotLen                            = 0;
    pucBuf                              = &pucBuffer[ BST_DSPP_TPA_BEGIN_ADDR ];
    pucBuf[0]                           = BST_DSPP_TP_VERA_HEAD;
    pucBuf                             += BST_DSPP_TPA_BEGIN_FLAG_LEN;
    usTotLen                           += BST_DSPP_TPA_BEGIN_FLAG_LEN;
    pucBuf[ BST_DSPP_TP_DVC_ID ]        = pstPacketInfo->ucDeviceId;
    pucBuf[ BST_DSPP_TP_PKT_NUM_L ]     = BST_DSPP_U16_TO_U8L
                                        ( pstPacketInfo->usPktNum );
    pucBuf[ BST_DSPP_TP_PKT_NUM_H ]     = BST_DSPP_U16_TO_U8H
                                        ( pstPacketInfo->usPktNum );
    pucBuf[ BST_DSPP_TP_PIC_AMT ]       = pstPacketInfo->ucPicAmount;
    pucBuf[ BST_DSPP_TP_PIC_NUM ]       = pstPacketInfo->ucPicNum;

    if ( BST_DSPP_TP_FIRST_PIECE_NUMBER == pstPacketInfo->ucPicNum )
    {
        pucBuf[ BST_DSPP_TP_CPL_VER ]   = ( BST_UINT8 )pstPacketInfo->enCpVer;
    }
    else
    {
        pucBuf[ BST_DSPP_TP_CPL_VER ]   = BST_DSPP_VER_VOID;
    }

    pucBuf[ BST_DSPP_TP_PRMIMTV ]       = pstPacketInfo->enPrimitive;
    pucBuf                             += ( BST_DSPP_TPA_HEAD_LEN + usSduLen );
    usTotLen                           += ( BST_DSPP_TPA_HEAD_LEN + usSduLen );
    pucBuf[ BST_DSPP_TPA_ERR_CODE_L ]   = 0;
    pucBuf[ BST_DSPP_TPA_ERR_CODE_H ]   = 0;
    pucBuf                             += BST_DSPP_TPA_ERR_LEN;
    usTotLen                           += BST_DSPP_TPA_ERR_LEN;
    pucBuf[0]                           = BST_DSPP_TP_VERA_TAIL;
    usTotLen                           += BST_DSPP_TPA_FINISH_FLAG_LEN;
    return usTotLen;
}


/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_DSPP_CTrsUlVa::SendMultiPacket (
    BST_DSPP_HEAD_STRU *const   pstTxHeadInfo )
{
    BST_ERR_ENUM_UINT8          ucRtnVal;
    BST_UINT16                  usSduLen;
    BST_UINT16                  usWantSize;
    BST_UINT16                  usSentLen;
    BST_DSPP_TP_PKTMSG_STRU     stPktPicMsg;
    BST_UINT8                  *pstBuffer;
    BST_UINT8                  *pucSdu;

    pucSdu                      = pstTxHeadInfo->pucData;
    usSduLen                    = pstTxHeadInfo->usLength;
    ucRtnVal                    = BST_NO_ERROR_MSG;

    stPktPicMsg.usPktNum        = pstTxHeadInfo->usPktNum;
    stPktPicMsg.ucPicNum        = BST_DSPP_TP_FIRST_PIECE_NUMBER;
    stPktPicMsg.enPrimitive     = pstTxHeadInfo->enPrmvType;
    stPktPicMsg.enCpVer         = pstTxHeadInfo->enCpVer;
    stPktPicMsg.ucPicAmount     = usSduLen / BST_DSPP_TPA_MAX_SDU;
    stPktPicMsg.ucDeviceId      = 0;
    if ( 0 != ( usSduLen % BST_DSPP_TPA_MAX_SDU ) )
    {
        stPktPicMsg.ucPicAmount+= 1;
    }
    pstBuffer                   = ( BST_UINT8 *)BST_OS_MALLOC
                                  ( BST_DSPP_TPA_TAIL_LEN );
    if ( BST_NULL_PTR == pstBuffer )
    {
        return BST_ERR_NO_MEMORY;
    }
    /*
     *先以最大吞吐能力组包
     */
    usWantSize                  = BST_DSPP_TPA_MAX_SDU;
    for ( ;; )
    {
        /*
         *Copy SDU 内容到Buffer
         */
        BST_OS_MEMCPY(  pstBuffer,
                        &pucSdu[ usWantSize + BST_DSPP_TPA_OFFSET_ADDR ],
                        BST_DSPP_TPA_TAIL_LEN );
        /*
         *构建包头
         */
        usSentLen               = BuildTpAHead( &stPktPicMsg,
                                                pucSdu,
                                                usWantSize );
        if( 0x0U == usSentLen )
        {
            ucRtnVal            = BST_ERR_LAYER_VER;
            break;
        }
        usSentLen               = TxApi( pucSdu,
                                         usSentLen );
        if ( 0 == usSentLen )
        {
            ucRtnVal            = BST_ERR_UNREACHABLE;
            break;
        }

        usSduLen               -= usWantSize;
        pucSdu                 += usWantSize;
        if( 0x0U == usSduLen )
        {
            /*
             *发送完成，跳出
             */
            ucRtnVal            = BST_NO_ERROR_MSG;
            break;
        }
        BST_OS_MEMCPY( &pucSdu[ BST_DSPP_TPA_OFFSET_ADDR ],
                        pstBuffer,
                        BST_DSPP_TPA_TAIL_LEN );
        if( usSduLen < BST_DSPP_TPA_MAX_SDU )
        {
            /*
             *不足一包，按照实际长度拷贝
             */
            usWantSize          = usSduLen;
        }
        else
        {
            usWantSize          = BST_DSPP_TPA_MAX_SDU;
        }
        stPktPicMsg.ucPicNum   += 1;
    }
    BST_OS_FREE( pstBuffer );
    return ucRtnVal;
}
/*lint +e438*/

BST_ERR_ENUM_UINT8  BST_DSPP_CTrsUlVa::SendPacket(
    BST_DSPP_HEAD_STRU *const       pstTxHeadInfo,
    BST_DSPP_PRIMITIVE_ENUM_UINT8   enPrm )
{
    BST_ERR_ENUM_UINT8                  ucRtnVal;
    BST_UINT16                          usSentLen;
    BST_DSPP_TP_PKTMSG_STRU             stPktPicMsg;

    if ( BST_NULL_PTR == pstTxHeadInfo )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_NULL_PTR == pstTxHeadInfo->pucData )
    {
        return BST_ERR_INVALID_PTR;
    }

    ucRtnVal                        = BST_NO_ERROR_MSG;
    pstTxHeadInfo->enPrmvType       = enPrm;
    /*
     *如果包长小于TP-A层最大承载能力，那么一包可以承载
     */
    if ( pstTxHeadInfo->usLength <= BST_DSPP_TPA_MAX_SDU )
    {
        stPktPicMsg.ucPicAmount     = 1;
        stPktPicMsg.ucDeviceId      = 0xaa;/*暂时无实际意义*/
        stPktPicMsg.usPktNum        = pstTxHeadInfo->usPktNum;
        stPktPicMsg.ucPicNum        = BST_DSPP_TP_FIRST_PIECE_NUMBER;
        stPktPicMsg.enPrimitive     = pstTxHeadInfo->enPrmvType;
        stPktPicMsg.enCpVer         = pstTxHeadInfo->enCpVer;
        usSentLen                   = BuildTpAHead( &stPktPicMsg,
                                      pstTxHeadInfo->pucData,
                                      pstTxHeadInfo->usLength );
        if( 0 == usSentLen )
        {
            BST_RLS_LOG( "BST_DSPP_CTrsUlVa::SendPacket BuildTpAHead Err" );
            BST_OS_FREE( pstTxHeadInfo->pucData );
            return BST_ERR_LAYER_VER;
        }
        usSentLen                   = TxApi( pstTxHeadInfo->pucData,
                                             usSentLen );
        if ( 0 == usSentLen )
        {
            BST_RLS_LOG( "BST_DSPP_CTrsUlVa::SendPacket TxApi Err" );
            BST_OS_FREE( pstTxHeadInfo->pucData );
            return BST_ERR_UNREACHABLE;
        }
    }
    else
    {
        ucRtnVal                    = SendMultiPacket( pstTxHeadInfo );

    }
    BST_OS_FREE( pstTxHeadInfo->pucData );

    return ucRtnVal;
}


BST_VOID  BST_DSPP_CTrsUlVa::RxAck(
    BST_DSPP_PKTSN_T usPktNum,
    BST_DSPP_PKTPC_T usPicNum )
{
    return;
}


/*lint -e438*/
BST_ERR_ENUM_UINT8 BST_DSPP_CTrsUlVa::TxAck ( BST_DSPP_TP_PKTMSG_STRU *pstAckPktMsg )
{
    BST_UINT8                  *pucTmpBuf;
    BST_DSPP_TP_PKTMSG_STRU     stPacketMsg;
    BST_UINT16                  usDataLen;

    if ( BST_NULL_PTR == pstAckPktMsg )
    {
        return BST_ERR_INVALID_PTR;
    }
    pucTmpBuf                   = BST_NULL_PTR;
    usDataLen                   = BST_DSPP_TPA_PKT_LENGTH ( 0 );
    pucTmpBuf                   = ( BST_UINT8 * )BST_OS_MALLOC ( usDataLen );
    if ( BST_NULL_PTR == pucTmpBuf )
    {
        return BST_ERR_NO_MEMORY;
    }

    stPacketMsg.enCpVer         = BST_DSPP_VER_VOID;
    stPacketMsg.usPktNum        = pstAckPktMsg->usPktNum;
    stPacketMsg.ucPicAmount     = pstAckPktMsg->ucPicAmount;
    stPacketMsg.ucPicNum        = pstAckPktMsg->ucPicNum;
    stPacketMsg.enPrimitive     = BST_DSPP_PRMTV_ACK;
    usDataLen                   = BuildTpAHead ( &stPacketMsg, pucTmpBuf, 0 );
    usDataLen                   = TxApi ( pucTmpBuf, usDataLen );
    BST_OS_FREE ( pucTmpBuf );

    if ( 0 == usDataLen )
    {
        return BST_ERR_UNREACHABLE;
    }

    return BST_NO_ERROR_MSG;
}
/*lint +e438*/

BST_UINT16 BST_DSPP_CTrsUlVa::TxApi ( const BST_UINT8 *pucData, BST_UINT16 usLen )
{
    BST_ERR_ENUM_UINT8  ucRtnVal;
    BST_DRV_STRU       *pAcomDrv;

    pAcomDrv            = BST_DRV_AcomGetDvcHandle ();
    if ( BST_NULL_PTR == pAcomDrv->pfWrite )
    {
        return 0;
    }

    ucRtnVal            = pAcomDrv->pfWrite( usLen, const_cast<BST_UINT8 *>(pucData));
    if ( BST_NO_ERROR_MSG != ucRtnVal )
    {
        return 0;
    }
    return usLen;
}


BST_ERR_ENUM_UINT8 BST_DSPP_CTrsUlVa::PackInternal(
    BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const pstNextVer )
{
    BST_DSPP_PRIMITIVE_ENUM_UINT8   ucPrmvType;
    BST_ERR_ENUM_UINT8              ucRtnVal;

    if ( BST_NULL_PTR == pstTxHeadInfo )
    {
        return BST_ERR_INVALID_PTR;
    }

    ucRtnVal                        = BST_NO_ERROR_MSG;
    ucPrmvType                      = pstTxHeadInfo->enPrmvType;

    if ( BST_DSPP_PRMTV_REPORT == ucPrmvType )
    {
        pstTxHeadInfo->usPktNum     = m_ReportPktNumSeq;
        ucRtnVal                    = SendPacket
                                    ( pstTxHeadInfo, BST_DSPP_PRMTV_REPORT );

        if ( BST_NO_ERROR_MSG == ucRtnVal )
        {
            m_ReportPktNumSeq++;
            if ( BST_DSPP_TP_MAX_S2M_PKTNUM <= m_ReportPktNumSeq )
            {
                m_ReportPktNumSeq   = BST_DSPP_TP_MIN_S2M_PKTNUM;
            }
        }
    }
    else
    {
        ucRtnVal                    = SendPacket
                                      ( pstTxHeadInfo, BST_DSPP_PRMTV_RESPONSE );
    }
    return ucRtnVal;
}


BST_DSPP_CUlLayerBase *BST_DSPP_CTrsUlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 ucNextVer )
{
    return BST_NULL_PTR;
}
