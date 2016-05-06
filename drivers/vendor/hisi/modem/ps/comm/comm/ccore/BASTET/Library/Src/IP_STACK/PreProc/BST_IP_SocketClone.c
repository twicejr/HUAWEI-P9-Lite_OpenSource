/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_IP_SocketClone.c
  版 本 号   : 初稿
  作    者   : D00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : 这个文件实现了复制SOCKET所使用的函数
  函数列表   :

  修改历史   :
  1.日    期 : 2014年04月16日
    作    者 : d00173029
    修改内容 : 创建文件
******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "lwip/tcp_impl.h"
#include "lwip/snmp.h"
#include "lwip/memp.h"
#include "BST_IP_PreProc.h"
#include "BST_IP_SocketClone.h"
#include "BST_OS_Thread.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_IP_SOCKETCLONE_C
/*lint +e767*/
/*****************************************************************************
  2 外部函数声明
*****************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
******************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : BST_IP_IsInPcbSet
 功能描述  :
 输入参数  : tcp_pcb *pstPcb
             tcp_pcb *pstPcbSet
 输出参数  : 无
 返 回 值  : BST_FALSE 成功
             BST_TRUE  失败
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : l00242755
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC BST_UINT32 BST_IP_IsInPcbSet( const struct tcp_pcb *pstPcb, const struct tcp_pcb *pstPcbSet )
{
    const struct tcp_pcb               *pstTmpPcbSet;

    if ( LWIP_NULL_PTR == pstPcb )
    {
        BST_DBG_LOG( "BST_IP_IsInPcbSet No" );
        return BST_FALSE;
    }
    if ( LWIP_NULL_PTR == pstPcbSet )
    {
        BST_DBG_LOG( "BST_IP_IsInPcbSet No" );
        return BST_FALSE;
    }

    pstTmpPcbSet                        = pstPcbSet;
    for (;;)
    {
        if ( pstTmpPcbSet == pstPcb )
        {
            BST_DBG_LOG( "BST_IP_IsInPcbSet Yes" );
            return BST_TRUE;
        }
        pstTmpPcbSet                    = pstTmpPcbSet->next;
        if ( LWIP_NULL_PTR == pstTmpPcbSet )
        {
            BST_DBG_LOG( "BST_IP_IsInPcbSet No" );
            return BST_FALSE;
        }
    }
}

/*****************************************************************************
 函 数 名  : BST_IP_TcpCloneConn
 功能描述  : 克隆一个TCP连接
 输入参数  : tcp_pcb *pstPcb
             ip_addr *pstIpAddr
             tcp_connected_fn connected
             BST_UINT16 port
 输出参数  : 无
 返 回 值  : 返回成功或出错信息
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月12日
      作    者   : l00242755
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_TcpCloneConn( struct tcp_pcb *pstPcb, struct  ip_addr *pstIpAddr, tcp_connected_fn connected, BST_UINT16 port )
{
    err_t                               ret;

    ret                                 = ERR_OK;
    if( NULL == pstPcb )
    {
        return BST_IP_ERR_VAL;
    }

    if ( pstIpAddr != NULL )
    {
        pstPcb->remote_ip               = *pstIpAddr;
    }
    else
    {
        return BST_IP_ERR_VAL;
    }

    pstPcb->remote_port                 = port;

    /* check if we have a route to the remote host */
    if ( IPADDR_ANY == pstPcb->local_ip.addr )
    {
        /* no local IP address set, yet. */
        struct netif *netif             = ip_route( &( pstPcb->remote_ip ) );

        if ( netif == NULL )
        {
            /* Don't even try to send a SYN packet if we have no route
               since that will fail. */
            return BST_IP_ERR_RTE;
        }

        /* Use the netif's IP address as local address. */
        ip_addr_copy( pstPcb->local_ip, netif->ip_addr );
    }

    if ( !BST_IP_IsPortValid( pstPcb->local_port ) )
    {
        return BST_IP_ERR_VAL;
    }

    pstPcb->state                       = ESTABLISHED;
    pstPcb->rcv_wnd                     = (BST_UINT16)TCP_WND;
    pstPcb->rcv_ann_wnd                 = (BST_UINT16)TCP_WND;
    pstPcb->rcv_ann_right_edge          = pstPcb->rcv_nxt;
    pstPcb->snd_wnd_max                 = (BST_UINT16)TCP_WND;
    pstPcb->flags                      |= TF_NODELAY;

    /* As initial send MSS, we use TCP_MSS but limit it to 536.
       The send MSS is updated when an MSS option is received. */

    pstPcb->mss                         = (BST_UINT16)TCP_MSS;

    pstPcb->cwnd                        = (BST_UINT16)TCP_SND_BUF;
    pstPcb->ssthresh                    = (BST_UINT16)( pstPcb->mss * (BST_UINT16)10 );
    pstPcb->connected                   = connected;

    BST_DBG_LOG1( "BST_IP_TcpCloneConn TCP_EVENT_CONNECTED ret=%d",
                   ret );
    snmp_inc_tcpactiveopens();

    if ( BST_FALSE == BST_IP_IsInPcbSet ( pstPcb, tcp_active_pcbs ) )
    {
        TCP_REG_ACTIVE( pstPcb );
    }

    return BST_IP_ERR_OK;
}

/*****************************************************************************
 函 数 名  : BST_IP_ApiRecordTcpProperty
 功能描述  : 记录TCP的属性
 输入参数  : BST_IP_PKT_ID_T stPktId
             tcp_pcb *pstPcb
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月12日
      作    者   : l00242755
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID  BST_IP_ApiRecordTcpProperty(
    BST_IP_PKT_ID_T             stPktId,
    struct tcp_pcb             *pstPcb )
{
    BST_IP_PKT_INFO_STRU               *pstPktLstMem;
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;

    BST_ASSERT_NULL( pstPcb );
    BST_ASSERT_NULL( stPktId );

    pstPortPreproc                      = BST_IP_SrchPreprocByPort( BST_IP_PROTOCOL_TCP, pstPcb->local_port );

    /*如果没有找到，那么证明已经删除，直接返回*/
    if ( BST_NULL_PTR == pstPortPreproc )
    {
        return;
    }

    if ( !BST_IP_IsPrprocWorking( pstPortPreproc ) )
    {
        return;
    }

    pstPktLstMem                        = BST_IP_SrchPackItem( stPktId );

    if ( BST_NULL_PTR == pstPktLstMem )
    {
        return;
    }

    BST_IP_ReadFromPcbPropertey( &( pstPktLstMem->stCurrentSktProperty ), pstPcb );
}

/*****************************************************************************
 函 数 名  : BST_IP_ApiRecordTcpProperty
 功能描述  : 设置TCP的属性
 输入参数  : tcp_pcb *pstPcb
             BST_IP_SKT_PROPTY_STRU *pstCurrentProperty
 输出参数  : 返回出错类型
 返 回 值  : BST_NO_ERROR_MSG
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月12日
      作    者   : l00242755
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_IP_ApiSetTcpPcbProperty(
    struct tcp_pcb                 *pstPcb,
    BST_IP_SKT_PROPTY_STRU         *pstCurrentProperty,
    BST_UINT8                       ucFlag )
{
    BST_IP_SKT_PROP_TYPE_ENUM_U8    enPropType;
    BST_IP_SKT_PATH_MODE_ENUM_U8    enPathMode;

    BST_ASSERT_NULL_RTN( pstCurrentProperty, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstPcb, BST_ERR_INVALID_PTR );
    BST_DBG_LOG4( "BST_IP_ApiSetTcpPcbProperty pstCurrentProperty seq,ack,sndwnd,scale",
                  pstCurrentProperty->ulSeqNum,
                  pstCurrentProperty->ulAckNum,
                  pstCurrentProperty->ulSndWnd,
                  pstCurrentProperty->usSndWscale );

    enPropType                      = BST_IP_GetPropType( ucFlag );
    enPathMode                      = BST_IP_GetPathMode( ucFlag );
    BST_DBG_LOG2( "BST_IP_ApiSetTcpPcbProperty enPropType",
                  enPropType,
                  enPathMode );

    switch( enPropType )
    {
        case BST_IP_SKT_PROP_NONE:        /* 0 没有property */
        break;

        case BST_IP_SKT_PROP_SEQNO:       /* 1 只有seqno */
            pstPcb->snd_nxt     = pstCurrentProperty->ulSeqNum;
        break;

        case BST_IP_SKT_PROP_SEQNO_TS:    /* 2 只有seqno+timestamp */
            pstPcb->snd_nxt     = pstCurrentProperty->ulSeqNum;
            pstPcb->ts_offset   = pstCurrentProperty->ulTsCurrent - sys_timestamp();
        break;

        case BST_IP_SKT_PROP_TOTAL:       /* 3 完整property */
            BST_IP_WriteToPcbPropertey( pstPcb, pstCurrentProperty );
#if LWIP_TCP_TIMESTAMPS
            if ( ( BST_INVALID_TIMESTAMP != pstCurrentProperty->ulTsRecent )
                && ( BST_INVALID_TIMESTAMP != pstCurrentProperty->ulTsCurrent ) )
            {
                pstPcb->flags  |= TF_TIMESTAMP;
            }
#endif
        break;

        default:                            /*4 无效*/
             return BST_ERR_PAR_UNKNOW;
    }

    if( BST_IP_PATH_MODE_NO_CHG != enPathMode )
    {
        BST_IP_ApiSetPreprocWorking( BST_IP_PROTOCOL_TCP,
                                     pstPcb->local_port,
                                     enPathMode );
    }
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_IP_ApiGetTcpPcbProperty
 功能描述  : 根据同步的发起方，从相应的AP或协议栈获得TCP的属性
 输入参数  : tcp_pcb *pstPcb
             BST_IP_SKT_PROPTY_STRU *pstCurrentProperty
 输出参数  : 返回出错类型
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月12日
      作    者   : l00242755
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_IP_ApiGetTcpPcbProperty(
    struct tcp_pcb             *pstPcb,
    BST_IP_SKT_PROPTY_STRU     *pstCurrentProperty,
    BST_UINT8                   ucFlag )
{
    BST_IP_PORT_PREPROC_STRU           *pstPortPreproc;

    BST_ASSERT_NULL_RTN( pstCurrentProperty, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( pstPcb, BST_ERR_INVALID_PTR );

    pstPortPreproc                       = BST_IP_SrchPreprocByPort( BST_IP_PROTOCOL_TCP, pstPcb->local_port );

    /*如果没有找到，那么证明已经删除，直接返回*/
    if( BST_NULL_PTR == pstPortPreproc )
    {
        return BST_ERR_INVALID_PTR;
    }
    /*如果端口处于活动状态，那么说明同步由AP发起，从协议栈直接读取*/
    if( BST_IP_IsPrprocWorking(pstPortPreproc) )
    {
        //从协议栈pcb读取property
        BST_IP_ReadFromPcbPropertey( pstCurrentProperty, pstPcb );
        pstCurrentProperty->ulRxByte    = pstPortPreproc->stLastSktProperty.ulRxByte;
        pstCurrentProperty->ulTxByte    = pstPortPreproc->stLastSktProperty.ulTxByte;
        if( BST_IP_PATH_MODE_STOP == ucFlag )
        {
            /*确认哪个是ACK NUM*/
            BST_DBG_LOG4( "bastet socket info:  snd_nxt:%u, snd_wl1:%u, snd_wl2:%u, snd_lbb:%u",\
                        pstPcb->snd_nxt, pstPcb->snd_wl1, pstPcb->snd_wl2, pstPcb->snd_lbb);

            /*modem在刚发送心跳包出去尚未收到ack时，AP请求SEQ的处理*/
            BST_IP_ApiResetTcpPcb( pstPcb );
        }
    }
    /*如果端口已经挂起，那么说明同步由Modem发起，从预处理取属性值并从协议栈取seq和timestamp*/
    else if ( BST_IP_IsPrprocSuspend(pstPortPreproc) )
    {
       *pstCurrentProperty                  = pstPortPreproc->stLastSktProperty;
        pstCurrentProperty->ulSeqNum        = pstPcb->snd_nxt;
        pstCurrentProperty->ulTsRecentStamp = sys_timestamp() + pstPcb->ts_offset;
    }
    else
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    /**
     * 取走SEQ后，如果仍然需要使用(NO STOP)，那么更新端口状态模式
     */
    if( BST_IP_PATH_MODE_STOP == ucFlag )
    {
        BST_IP_ApiSetPreprocStop ( BST_IP_PROTOCOL_TCP, pstPcb->local_port );
    }
    else
    {
        if( BST_IP_PATH_MODE_NO_CHG != ucFlag )
        {
            BST_IP_ApiSetPreprocWorking( BST_IP_PROTOCOL_TCP, pstPcb->local_port, ucFlag );
        }
    }

    BST_DBG_LOG3( "BST_IP_ApiGetTcpPcbProperty ulTxByte: %d ulRxByte: %d",\
                  pstPortPreproc->stLastSktProperty.ulTxByte,\
                  pstPortPreproc->stLastSktProperty.ulRxByte,\
                  ucFlag );
    /*清空流量统计值*/
    BST_IP_ApiUpdateTrafficFlow( BST_IP_TRAFFIC_DEC,
                                 pstPortPreproc->stLastSktProperty.ulRxByte );
    BST_IP_ApiUpdateTrafficFlow( BST_IP_TRAFFIC_DEC,
                                 pstPortPreproc->stLastSktProperty.ulTxByte );
    pstPortPreproc->stLastSktProperty.ulRxByte
                                        = 0U;
    pstPortPreproc->stLastSktProperty.ulTxByte
                                        = 0U;
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_IP_ApiDropTcpPcb
 功能描述  :
 输入参数  : tcp_pcb *pstPcb
             BST_UINT32 ulBeRmv
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年09月02日
      作    者   : z00220931
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_IP_ApiDropTcpPcb( struct tcp_pcb *pstPcb )
{
    if ( BST_NULL_PTR == pstPcb )
    {
        return;
    }

    /* Avoid the Freed pcb live in any PCBS */
    if ( BST_TRUE == BST_IP_IsInPcbSet ( pstPcb, tcp_active_pcbs ) )
    {
        TCP_RMV_ACTIVE( pstPcb );
    }
    if ( BST_TRUE == BST_IP_IsInPcbSet ( pstPcb, tcp_bound_pcbs ) )
    {
        tcp_pcb_remove( &tcp_bound_pcbs, pstPcb);
    }
    if ( BST_TRUE == BST_IP_IsInPcbSet ( pstPcb, tcp_listen_pcbs.pcbs ) )
    {
        tcp_pcb_remove( &tcp_listen_pcbs.pcbs, pstPcb );
    }
    if ( BST_TRUE == BST_IP_IsInPcbSet ( pstPcb, tcp_tw_pcbs ) )
    {
        tcp_pcb_remove( &tcp_tw_pcbs, pstPcb);
    }
    memp_free( MEMP_TCP_PCB, pstPcb );
}

/*****************************************************************************
 函 数 名  : BST_IP_ApiResetTcpPcb
 功能描述  : 重置Tcp pcb的状态
 输入参数  : tcp_pcb *pstPcb
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年9月20日
      作    者   : l00231445
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_IP_ApiResetTcpPcb( struct tcp_pcb *pstPcb )
{
    if ( BST_NULL_PTR == pstPcb )
    {
        return;
    }

    if ( ( BST_NULL_PTR == pstPcb->unacked ) && ( BST_NULL_PTR == pstPcb->unsent ) )
    {
        /* No need to reset */
        return;
    }

    BST_RLS_LOG( "Reset Tcp pcb Notice" );

    pstPcb->snd_wl1                     = pstPcb->rcv_nxt;
    pstPcb->snd_wl2                     = pstPcb->snd_nxt;

    /* Reset the "IN Fast Retransmit" flag, since we are no longer
    in fast retransmit. Also reset the congestion window to the
    slow start threshold. */
    if ( pstPcb->flags & TF_INFR )
    {
        pstPcb->flags                  &= ~TF_INFR;
        pstPcb->cwnd                    = pstPcb->ssthresh;
    }

    /* Reset the number of retransmissions. */
    pstPcb->nrtx                        = 0;
    /* Reset the retransmission time-out. */
    pstPcb->rto                         = ( ((BST_UINT16)pstPcb->sa) >> 3 ) + pstPcb->sv;

    /* Update the send buffer space. Diff between the two can never exceed 64K? */
    pstPcb->acked                       = ( u16_t )( pstPcb->snd_nxt - pstPcb->lastack );
    pstPcb->snd_buf                    += pstPcb->acked;

    /* Reset the fast retransmit variables. */
    pstPcb->dupacks                     = 0;
    pstPcb->lastack                     = pstPcb->snd_nxt;

    tcp_pcb_purge(pstPcb);
    /* After clear unsent and unacked segs, reset snd_queuelen 0 */
    pstPcb->snd_queuelen                = 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


