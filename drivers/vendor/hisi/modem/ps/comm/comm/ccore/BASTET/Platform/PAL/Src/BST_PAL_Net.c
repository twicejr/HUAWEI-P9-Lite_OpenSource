/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DRV_NETDEVICE.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年05月04日
  最近修改   :
  功能描述   : 实现Bastet与无线3GPP协议栈IP包收发接口
  函数列表   :
  修改历史   :
  1.日    期   : 2014年05月13日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_PAL_Net.h"
#include "BST_DRV_Net.h"
#include "BST_DRV_As.h"
#include "BST_PAL_As.h"
#include "BST_IP_Define.h"
#include "BST_IP_PreProc.h"
#include "lwip/tcpip.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Memory.h"
#include "BST_OS_Sync.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_NET_C
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
  3 函数声明
*****************************************************************************/
BST_UINT32          BST_PAL_NetIpStackInput(
    const BST_UINT32    const ulLength,
    const BST_UINT8    *const pucData,
    const TTF_MEM_ST   *const pstPktItem );

BST_VOID            BST_PAL_NetProcDlPacket (
    const TTF_MEM_ST  *pstTtfPacket );

BST_VOID            BST_PAL_NetMsgCfgCallBack(
    const BST_CDS_SEND_CB_INFO_STRU    *pstMsg );

/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/
BST_PAL_NET_ENTITY_STRU                 g_BstPalNetEntity   =
    { BST_NULL_PTR, BST_NULL_PTR, BST_NULL_PTR };
/******************************************************************************
   6 函数实现
******************************************************************************/
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
/*****************************************************************************
 函 数 名  : BST_PAL_NetApiPackPppForwd
 功能描述  : 转发PPP包到AP侧
 输入参数  : BST_UINT32   ulLength,                 包长度
             BST_UINT8   *pucData                   包内容
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8 BST_ERR_NO_MEMORY   内存不足，发送失败
                                BST_NO_ERROR_MSG    发送成功
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_PAL_NetApiPackPppForwd(  BST_UINT32   ulLength,
                                            BST_UINT8   *pucData )
{
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetApiPacketPppRcvd
 功能描述  : PPP网络数据包接收函数
 输入参数  : BST_UINT32   ulLength,             包长度
             BST_UINT8   *pucData               包内容
 输出参数  : 无
 返 回 值  : BST_UINT32                         成功接收数据长度
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_PAL_NetApiPacketPppRcvd( BST_UINT32   ulLength,
                                  BST_UINT8   *pucData )
{
    if( BST_NULL_PTR == pucData )
    {
        return 0x00U;
    }
    if( BST_OS_SIZEOF( TTF_MEM_ST )!= ulLength )
    {
        return 0x00U;
    }
    BST_PAL_NetApiPacketFree( pucData );
    return ulLength;
}
#endif

/*****************************************************************************
 函 数 名  : BST_PAL_NetDLEvtProc
 功能描述  : BASTET dl消息处理函数。
 输入参数  :
 输出参数  :
 返 回 值  :

 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_PAL_NetDLEvtProc( BST_VOID )
{
    BST_UINT32                  ulCnt;
    BST_OS_LOCKCNT_T            tThreadLockCnt;
    TTF_MEM_ST                 *pstIpPkt;
    BST_PAL_NET_ENTITY_STRU    *pstBstNetEntity;

    tThreadLockCnt              = BST_OS_ThreadLock();
    pstBstNetEntity             = BST_PAL_NetGetEntity();

    for ( ulCnt = 0; ulCnt < BST_PAL_DL_QUE_SIZE; ulCnt ++ )
    {
        if ( LUP_DeQue( pstBstNetEntity->pstDlDataQue,
                        ( BST_VOID **)&pstIpPkt) )
        {
            BST_OS_ThreadUnLock( tThreadLockCnt );
            return;
        }
        BST_PAL_NetProcDlPacket( pstIpPkt );
    }
    BST_OS_ThreadUnLock( tThreadLockCnt );
    return;
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetMsgEntry
 功能描述  : IMSA消息处理函数。
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年07月31日
      作    者   : y00151394
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_PAL_NetMsgEntry( MsgBlock  *pstMsg )
{
    BST_UINT32                  ulTrsFlg;
    if ( BST_NULL_PTR == pstMsg )
    {
        BST_RLS_LOG( "BST_PAL_NetMsgEntry : Input NULL PTR." );
        return;
    }
    BST_RLS_LOG1( "BST_PAL_NetMsgEntry : MsgId", TTF_GET_MSG_NAME(pstMsg) );
    switch( TTF_GET_MSG_NAME(pstMsg) )
    {
        /* CDS发给BASTET的消息原语: 有其他IP包在运行中 */
        case ID_BST_CDS_RX_IND:
            ulTrsFlg            = BST_TRUE;
            BST_PalAsEventRcvCb( BST_AS_EVT_L3_AP_RX_RCV_IND,
                                 ( BST_UINT16 )BST_OS_SIZEOF(ulTrsFlg),
                                 &ulTrsFlg );
            break;

        /* CDS发给BASTET的消息原语: 当前MODEM数据业务使用的MODEM ID*/
        case ID_BST_CDS_CHANNEL_INFO_IND:
            BST_PAL_NetMsgCfgCallBack( (const BST_CDS_SEND_CB_INFO_STRU *)pstMsg );
            break;

        case ID_BST_CDS_TX_IND:
            ulTrsFlg            = BST_TRUE;
            BST_PalAsEventRcvCb( BST_AS_EVT_L3_AP_TX_SEND_IND,
                                 ( BST_UINT16 )BST_OS_SIZEOF(ulTrsFlg),
                                 &ulTrsFlg );
            break;

        default:
            BST_RLS_LOG( "BST_PAL_NetMsgEntry : Unknown Message." );
            break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetMsgCfgCallBack
 功能描述  : 将数据包转发到AP
 输入参数  : BST_CDS_SEND_CB_INFO_STRU *pstMsg Modem Id 消息结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_PAL_NetMsgCfgCallBack( const BST_CDS_SEND_CB_INFO_STRU *pstMsg  )
{
    BST_PAL_NET_ENTITY_STRU    *pstBstNetEntity;

    if ( BST_NULL_PTR == pstMsg )
    {
        BST_RLS_LOG( "BST_PAL_NetMsgCfgCallBack : pstMsg Is Null ." );
        return;
    }
    pstBstNetEntity             = BST_PAL_NetGetEntity();
    pstBstNetEntity->pfSndItf   = pstMsg->pSendCbFun;
    pstBstNetEntity->pfRsmItf   = pstMsg->pResmCbFun;
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetApiPacketSend
 功能描述  : 实现TCP/IP包向空口协议栈的发送功能
 输入参数  : BST_UINT32   ulLength,                 包长度
             BST_UINT8   *pucData                   包内容
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8 BST_ERR_PAR_LEN     数据长度有误
                                BST_ERR_PAR_UNKNOW  发送口参数异常
                                BST_ERR_NO_MEMORY   内存不足，无法发送
                                BST_NO_ERROR_MSG    发送成功
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_PAL_NetApiPacketSend(
    BST_UINT32   ulLength,
    BST_UINT8   *pucData)
{
    BST_PAL_NET_ENTITY_STRU            *pstBstNetEntity;
    BST_UINT8                           ucDataType;
    BST_DRV_IP_DATA_STRU                *pstData;

    if( BST_NULL_PTR == pucData )
    {
        BST_RLS_LOG( "BST_PAL_NetApiPacketSend:pucData is null" );
        return BST_ERR_UNREACHABLE;
    }
    
    pstBstNetEntity                     = BST_PAL_NetGetEntity();

    if( BST_NULL_PTR == pstBstNetEntity->pfSndItf )
    {
        BST_RLS_LOG( "BST_PAL_NetApiPacketSend: pfSndItf is Void." );
        return BST_ERR_UNREACHABLE;
    }

    pstData                             = (BST_DRV_IP_DATA_STRU*)pucData;
    if(pstData->ucDataType == BST_IP_HPRI_DATA)
    {
        ucDataType = CDS_BST_UL_DATA_HIGH_PRI;
    }
    else
    {
        ucDataType = CDS_BST_UL_DATA_NORMAL;
    }
    if( ulLength != pstBstNetEntity->pfSndItf( pstData->pucData, ulLength, ucDataType ) )
    {
        BST_RLS_LOG1( "BST_PAL_NetApiPacketSend: Send to OTA Error Len.", ulLength );
        return BST_ERR_PAR_LEN;
    }
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetApiPacketResume
 功能描述  : 将数据包转发到AP
 输入参数  : BST_VOID *pstItem              NET_DRV_PACKET_STRU格式数据包
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8             出错类型
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_PAL_NetApiPacketResume( BST_VOID *pstItem )
{
    BST_PAL_NET_ENTITY_STRU            *pstBstNetEntity;

    pstBstNetEntity                     = BST_PAL_NetGetEntity();
    if ( BST_NULL_PTR == pstItem )
    {
        BST_RLS_LOG( "BST_PAL_NetApiPacketResume : Mst Pointer Is Null ." );
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_NULL_PTR == pstBstNetEntity->pfRsmItf )
    {
        BST_RLS_LOG( "BST_PAL_NetApiPacketResume : pfRsmItf Pointer Is Null ." );
        return BST_ERR_INVALID_PTR;
    }
    if( 0 == pstBstNetEntity->pfRsmItf( (BST_UINT8 *)pstItem,
        (BST_UINT16)BST_OS_SIZEOF (TTF_MEM_ST ) ) )
    {
        BST_PAL_NetApiPacketFree( pstItem );
        return BST_ERR_ILLEGAL_PARAM;
    }
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 函 数 名  : BST_PAL_NetApiPacketFree
 功能描述  : 清除数据包
 输入参数  : BST_VOID *pstItem              NET_DRV_PACKET_STRU格式数据包
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8             出错类型
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_PAL_NetApiPacketFree( BST_VOID *pstItem )
{
    TTF_MEM_ST                        *pstTtfMem;

    if( BST_NULL_PTR == pstItem )
    {
        return BST_ERR_INVALID_PTR;
    }
    pstTtfMem                          = (TTF_MEM_ST *)pstItem;
    TTF_MemFree( UEPS_PID_BASTET, pstTtfMem );
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetApiPacketRcved
 功能描述  : 接收来自cds的下行IP包
 输入参数  : const BST_UINT8 *pData,    数据指针头
             const BST_UINT32 ulLen     数据长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_PAL_NetApiPacketRcved( const BST_UINT8 *pData, const BST_UINT32 ulLen )
{
    BST_OS_LOCKCNT_T            tThreadLockCnt;
    BST_PAL_NET_ENTITY_STRU    *pstBstNetEntity;

    pstBstNetEntity             = BST_PAL_NetGetEntity();
    /*入参判断*/
    if ( ulLen != BST_OS_SIZEOF(TTF_MEM_ST) )
    {
        BST_RLS_LOG( "BST_EnQueueOtaData: Wrong Size" );
        return 0;
    }
    if ( BST_NULL_PTR == pData )
    {
        BST_RLS_LOG( "BST_EnQueueOtaData: NULL pData" );
        return 0;
    }

    /*入队*/
    tThreadLockCnt          = BST_OS_ThreadLock();
    if ( PS_SUCC != LUP_EnQue( pstBstNetEntity->pstDlDataQue,
                               (BST_VOID *)pData ) )
    {
        BST_PAL_NetApiPacketFree( (BST_VOID *)pData );
        BST_OS_ThreadUnLock( tThreadLockCnt );
        BST_RLS_LOG( "BST_EnQueueOtaData: EnQueue Fail" );
        return 0;
    }
    BST_OS_ThreadUnLock( tThreadLockCnt );
    /*wakeup cds*/
    BST_SYS_ApiSndEvtToBastet( BST_CDS_EVENT_RCV_DL_PROC );
    return ulLen;
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetApiPacketLen
 功能描述  : 获取TTF格式包长度接口
 输入参数  : BST_VOID *pvArg    UnUsed
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年09月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_PAL_NetApiPacketLen( BST_VOID *pvPkt )
{
    return ( BST_UINT32 )TTF_MemGetLen( UEPS_PID_BASTET, ( TTF_MEM_ST *)pvPkt );
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetApiSetRxMsgEnable
 功能描述  : 设置是否允许CDS上报数据接收消息
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
BST_VOID BST_PAL_NetApiSetRxMsgEnable( BST_UINT32 ulEnableFlag )
{
    BST_CDS_TX_RX_RPT_ENABLE_STRU  *pstTrxEnableMsg;
    BST_UINT32                      ulMsgLen;

    ulMsgLen                        = sizeof( BST_CDS_TX_RX_RPT_ENABLE_STRU );
    pstTrxEnableMsg                 = BST_PAL_NetAllocMsgWithHdr( ulMsgLen );

    if (BST_NULL_PTR == pstTrxEnableMsg)
    {
        BST_RLS_LOG( "BST_PAL_NetApiSetTrxMsgEnable : Alloc Msg Fail. Size ." );
        return;
    }

    /*填写消息内容*/
    BST_PAL_NetCfgMsgHead( pstTrxEnableMsg, UEPS_PID_CDS );
    pstTrxEnableMsg->ulMsgId        = ID_BST_CDS_RX_RPT_CTRL_REQ;
    pstTrxEnableMsg->ulEnableFlag   = ulEnableFlag;

    /*发送消息*/
    BST_PAL_NetSendMsg( pstTrxEnableMsg );
}


/*****************************************************************************
 函 数 名  : BST_PAL_NetApiSetTxMsgEnable
 功能描述  : 设置是否允许CDS上报Tx数据发送消息
 输入参数  : ulEnableFlag   -- 是否允许上报，BST_TRUE 允许上报，BST_FALSE不允许上报
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月27日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_PAL_NetApiSetTxMsgEnable( BST_UINT32 ulEnableFlag )
{
    BST_CDS_TX_RX_RPT_ENABLE_STRU  *pstTrxEnableMsg;
    BST_UINT32                      ulMsgLen;

    ulMsgLen                        = sizeof( BST_CDS_TX_RX_RPT_ENABLE_STRU );
    pstTrxEnableMsg                 = BST_PAL_NetAllocMsgWithHdr( ulMsgLen );

    if (BST_NULL_PTR == pstTrxEnableMsg)
    {
        BST_RLS_LOG( "BST_PAL_NetApiSetTrxMsgEnable : Alloc Msg Fail. Size ." );
        return;
    }

    /*填写消息内容*/
    BST_PAL_NetCfgMsgHead( pstTrxEnableMsg, UEPS_PID_CDS );
    pstTrxEnableMsg->ulMsgId        = ID_BST_CDS_TX_RPT_CTRL_REQ;
    pstTrxEnableMsg->ulEnableFlag   = ulEnableFlag;

    /*发送消息*/
    BST_PAL_NetSendMsg( pstTrxEnableMsg );
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetIpStackInput
 功能描述  : 3GPP网络IP包接收函数
 输入参数  : BST_UINT32   ulLength,             包长度
             BST_UINT8   *pucData               包内容
 输出参数  : 无
 返 回 值  : BST_UINT32                         成功接收数据长度
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_PAL_NetIpStackInput(
    const BST_UINT32   const ulLength,
    const BST_UINT8  * const pucData,
    const TTF_MEM_ST * const pstPktItem )
{
    BST_NET_PBUF_T                 *pbuf;
    BST_NETIF_T                    *pstNetif;
    BST_INT32                       lRtnVal;
    BST_UINT16                      usPortNum;

    if( 0 == ulLength )
    {
        return 0x00U;
    }
    if( BST_NULL_PTR == pucData )
    {
        return 0x00U;
    }
    if( BST_NULL_PTR == pstPktItem )
    {
        return 0x00U;
    }

    pbuf                            = pbuf_alloc( PBUF_LINK, (BST_UINT16)ulLength, PBUF_RAM );
    if( BST_NULL_PTR == pbuf )
    {
        BST_RLS_LOG( "BST_PAL_NetIpStackInput, pbuf is null" );
        BST_PAL_NetApiPacketResume( (BST_VOID*)pstPktItem );
        return ulLength;
    }
    usPortNum                       = BST_IP_ApiRegistPacket(
                                    ( BST_IP_PKT_ID_T )pstPktItem, (BST_VOID*)pstPktItem );
    BST_DBG_UPDATE_RX_FLOW( usPortNum, ulLength );
    pbuf->packetid                  = ( BST_IP_PKT_ID_T )pstPktItem;
    ( BST_VOID )pbuf_take( pbuf, pucData, (BST_UINT16)ulLength );
    pstNetif                        = BST_DRV_NetGetMainIfHandle();
    lRtnVal                         = pstNetif->input( pbuf, pstNetif );
    if ( lRtnVal < 0 )
    {
        BST_RLS_LOG1( "BST_PAL_NetIpStackInput, Write to Lwip Error=%s", lRtnVal );
        BST_IP_ApiForwordPacket( ( BST_IP_PKT_ID_T )pstPktItem );
        pbuf_free( pbuf );
    }
    return ulLength;

}

/*****************************************************************************
 函 数 名  : BST_PAL_NetProcDlPacket
 功能描述  : 实现从空口接收下行IP数据包
 输入参数  : TTF_MEM_ST    *pstSrcMem          空口中取出的数据片Item
 输出参数  : 无
 返 回 值  : BST_BOOL       BST_FALSE           IP包非Bastet代理数据，不处理
                            BST_TRUE            IP包由Bastet取到
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_PAL_NetProcDlPacket( const TTF_MEM_ST  *pstTtfPacket )
{
    BST_IP_PKT_PROC_ENUM_INT8           enPktProcMode;
    BST_UINT8                          *pucTmpdata;
    BST_UINT32                          ulIsMalloced;
    BST_UINT32                          ulTotalBytes;

    pucTmpdata                          = BST_NULL_PTR;
    ulTotalBytes                        = 0x00U;
    ulIsMalloced                        = BST_FALSE;
    if ( BST_NULL_PTR == pstTtfPacket )
    {
        BST_RLS_LOG( "BST_PAL_NetProcDlPacket: pstTtfPacket Invalide" );
        return;
    }

    if( ( 0 == pstTtfPacket->usUsed )
      ||( BST_NULL_PTR == pstTtfPacket->pData ) )
    {
        BST_RLS_LOG2( "BST_PAL_NetProcDlPacket: No Data tot=%u, used=%u, pData=%p",
        pstTtfPacket->usUsed, pstTtfPacket->pData );
        return;
    }

    ulTotalBytes                        = BST_PAL_NetApiPacketLen( (BST_VOID*)pstTtfPacket );
    if ( BST_NULL_PTR == pstTtfPacket->pNext )
    {
        pucTmpdata                      = pstTtfPacket->pData;
        ulIsMalloced                    = BST_FALSE;
    }
    else
    {
        pucTmpdata                      = (BST_UINT8 *)BST_OS_MALLOC( ulTotalBytes );
        BST_ASSERT_NULL( pucTmpdata );
        if( TTF_MemGet( UEPS_PID_BASTET, ( TTF_MEM_ST *)pstTtfPacket,
                        0U, pucTmpdata, (BST_UINT16)ulTotalBytes ) )
        {
        /*lint -e438*/
            BST_OS_FREE( pucTmpdata );
            return;
        /*lint +e438*/
        }
        ulIsMalloced                    = BST_TRUE;
    }
    BST_DBG_LOG1( "BST_PAL_NetProcDlPacket: TolLen=%u", ulTotalBytes );
    enPktProcMode                       = BST_IP_ApiFastCheckDL( pucTmpdata, ulTotalBytes );
    if ( BST_IP_PKT_TO_AP == enPktProcMode)
    {
        BST_RLS_LOG( "BST_PAL_NetProcDlPacket: NOT Bastet Packet" );
        BST_PAL_NetApiPacketResume( (BST_VOID*)pstTtfPacket );
    }
    else
    {
        if ( BST_IP_PKT_FREE == enPktProcMode )
        {
            BST_RLS_LOG( "BST_PAL_NetProcDlPacket: Free Packet" );
            BST_PAL_NetApiPacketFree( (BST_VOID*)pstTtfPacket );
        }
        else
        {
            BST_RLS_LOG1( "BST_PAL_NetProcDlPacket: Bastet Packet, Length=", ulTotalBytes );
            if ( ulTotalBytes != BST_PAL_NetIpStackInput( ulTotalBytes, pucTmpdata, pstTtfPacket ) )
            {
                BST_RLS_LOG( "BST_PAL_NetProcDlPacket: BST_PAL_NetIpStackInput Error" );
                BST_PAL_NetApiPacketFree( (BST_VOID*)pstTtfPacket );
            }
        }
    }
    if ( BST_TRUE == ulIsMalloced )
    {
        BST_OS_FREE( pucTmpdata );
    }
/*lint -e429 -e438 */
}   /*pucTmpdata 是否free需要判断ulIsMalloced，如果指针不是Malloc的，则不需FREE*/
/*lint +e429 +e438*/
/*****************************************************************************
 函 数 名  : BST_PAL_NetSendNetStateMsg
 功能描述  : 设置NET状态
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
BST_VOID BST_PAL_NetSendNetStateMsg( BST_UINT32 ulNetState )
{
    BST_CDS_NET_DEVICE_STATE_STRU      *pstNetStateMsg;
    BST_UINT32                          ulMsgLen;

    ulMsgLen                            = sizeof( BST_CDS_NET_DEVICE_STATE_STRU );
    pstNetStateMsg                      = BST_PAL_NetAllocMsgWithHdr( ulMsgLen );

    if (BST_NULL_PTR == pstNetStateMsg)
    {
        BST_RLS_LOG( "BST_PAL_NetSendNetStateMsg : Alloc Msg Fail. Size ." );
        return;
    }

    /*填写消息内容*/
    BST_PAL_NetCfgMsgHead( pstNetStateMsg, UEPS_PID_CDS );
    pstNetStateMsg->ulMsgId             = ID_BST_CDS_NET_DEVICE_UP_IND;
    if ( BST_DRV_NETSTATE_UP == ulNetState )
    {
        pstNetStateMsg->ulNetDeviceState= CDS_BASTET_NET_DEVICE_UP;
        BST_DBG_LOG( "BST_PAL_NetSendNetStateMsg: Up. " );
    }
    else if ( BST_DRV_NETSTATE_DOWN == ulNetState )
    {
        pstNetStateMsg->ulNetDeviceState= CDS_BASTET_NET_DEVICE_DOWN;
        BST_DBG_LOG( "BST_PAL_NetSendNetStateMsg: Down. " );
    }
    else
    {
        pstNetStateMsg->ulNetDeviceState= CDS_BASTET_NET_DEVICE_UNKNOW;
        BST_DBG_LOG( "BST_PAL_NetSendNetStateMsg: Unknow. " );
    }

    /*发送消息*/
    BST_PAL_NetSendMsg( pstNetStateMsg );
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetSendNetStateMsg
 功能描述  : 设置NET状态
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
BST_VOID BST_PAL_NetSendModemRabId( BST_DRV_NET_MODEM_RABID_STRU *pstModemRabId )
{
    BST_CDS_NET_ACORE_MODEM_RABID_STRU *pstNetModemRabMsg;
    BST_MODEM_ID_ENUM_UINT32            enNewModemId;
    BST_UINT32                          ulMsgLen;

    ulMsgLen                            = sizeof( BST_CDS_NET_ACORE_MODEM_RABID_STRU );
    pstNetModemRabMsg                   = BST_PAL_NetAllocMsgWithHdr( ulMsgLen );

    if (BST_NULL_PTR == pstNetModemRabMsg)
    {
        BST_RLS_LOG( "BST_PAL_NetSendModemRabId : Alloc Msg Fail. Size ." );
        return;
    }

    if( MODEM_ID_0 == pstModemRabId->usModemId )
    {
        enNewModemId            =  BST_MODEM_ID_1;
    }
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if( MODEM_ID_1 == pstModemRabId->usModemId )
    {
        enNewModemId            = BST_MODEM_ID_2;
    }
#if ( 3 == MULTI_MODEM_NUMBER )
    else if( MODEM_ID_2 == pstModemRabId->usModemId )
    {
        enNewModemId            = BST_MODEM_ID_3;
    }
#endif
#endif 
    else
    {
        BST_RLS_LOG1( "BST_PAL_NetSendModemRabId : invalid modemId.",pstModemRabId->usModemId );
        return;
    }

    if( BST_PAL_AsApiGetPsModemId() != enNewModemId )
    {
        BST_PAL_AsMsgModemIdChanged( enNewModemId );
    }
    BST_PAL_AsMsgSetRabID( pstModemRabId->usRabId );

    /*填写消息内容*/
    BST_PAL_NetCfgMsgHead( pstNetModemRabMsg, UEPS_PID_CDS );
    pstNetModemRabMsg->ulMsgId          = ID_BST_CDS_NET_MODEM_RAB_IND;
    pstNetModemRabMsg->usModemId        = pstModemRabId->usModemId;
    pstNetModemRabMsg->usRabId          = pstModemRabId->usRabId;
    /*发送消息*/
    BST_PAL_NetSendMsg( pstNetModemRabMsg );
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetSendRegCbMsg
 功能描述  : 注册下行回调函数
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
BST_VOID BST_PAL_NetSendRegCbMsg( BST_VOID )
{
    BST_CDS_REG_RCV_CB_STRU    *pstRcvCbMsg;
    BST_UINT32                  ulMsgLen;

    ulMsgLen                    = sizeof( BST_CDS_REG_RCV_CB_STRU );
    pstRcvCbMsg                 = BST_PAL_NetAllocMsgWithHdr( ulMsgLen );

    /*填写消息内容*/
    BST_PAL_NetCfgMsgHead( pstRcvCbMsg, UEPS_PID_CDS );
    pstRcvCbMsg->ulMsgId        = ID_BST_CDS_REG_RCV_CB_REQ;
    pstRcvCbMsg->pfRcvCb        = BST_PAL_NetApiPacketRcved;
    pstRcvCbMsg->pfChkPortCb    = BST_IP_ApiChkPort;
    /*发送消息*/
    BST_PAL_NetSendMsg( pstRcvCbMsg );
}

/*****************************************************************************
 函 数 名  : BST_PAL_NetApiInitial
 功能描述  : 初始化IP包接收线程及消息邮箱
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
BST_VOID  BST_PAL_NetApiInitial( BST_VOID )
{
    BST_PAL_NET_ENTITY_STRU    *pstBstNetEntity;
#if defined(BST_PEAK_SPEED_TEST) || defined (BST_RUBBISH_DEBUG)|| defined (BST_MODEM_SELF)
    BST_UINT32                      i;
    extern BST_IP_FAST_CHECK_STRU   g_stBstIpFastPortCheck;
    g_stBstIpFastPortCheck.lCnt                 = BST_MAX_CNNT_NUMBER;
    for ( i=0; i<BST_MAX_CNNT_NUMBER; i++ )
    {
        g_stBstIpFastPortCheck.ausPortNum[i]    = 0;
        g_stBstIpFastPortCheck.ausProtocol[i]   = 0x02;
    }
    BST_PAL_NetSendNetStateMsg( BST_TRUE );
#endif
    pstBstNetEntity             = BST_PAL_NetGetEntity();
    if ( LUP_CreateQue( UEPS_PID_BASTET,
                        &pstBstNetEntity->pstDlDataQue,
                        BST_PAL_DL_QUE_SIZE) )
    {
        BST_RLS_LOG("BST_PAL_NetApiInitial : Create Bastet DL Que Fail.\n");
        return;
    }
    BST_PAL_NetSendRegCbMsg();
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

