/******************************************************************************

                  版权所有(C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_IP_Socket.cpp
  版 本 号   : V1.1
  作    者   : d00173029
  生成日期   : 2014年5月10日
  最近修改   :
  功能描述   : 定义LWIP协议栈接口统一处理
  函数列表   :

  修改历史   :
  1.日    期   : 2014年05月10日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_IP_Socket.h"
#include "BST_IP_PreProc.h"
#include "lwip/sockets.h"
#include "lwip/memp.h"
#ifdef   BST_SSL_SUPPORT
#include "BST_OS_Openssl_Rename.h"
#include "openssl/ssl.h"
#endif
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_IP_SOCKET_CPP
/*lint +e767*/
/*****************************************************************************
  2 函数声明
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
 函 数 名  : BST_IP_CSocket
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
#if( BST_VER_TYPE == BST_DBG_VER )
BST_IP_CSocket::BST_IP_CSocket(
    BST_PROCID_T    usProcId,
    BST_TASKID_T    usTaskId ):m_usProcId ( usProcId ), m_usTaskId ( usTaskId )
{
    m_pSslContxt                        = BST_NULL_PTR;
    m_pSslHandle                        = BST_NULL_PTR;
    m_lFd                               = BST_INVALID_FD;
    m_enSocketType                      = BST_IP_INVALID_SOCKET_TYPE;
    m_TrafficPool.ulRxByte              = 0;
    m_TrafficPool.ulTxByte              = 0;
    BST_IP_InitIpAddress( &m_stIpAddress );
}
#else
BST_IP_CSocket::BST_IP_CSocket()
{
    m_pSslContxt                        = BST_NULL_PTR;
    m_pSslHandle                        = BST_NULL_PTR;
    m_lFd                               = BST_INVALID_FD;
    m_enSocketType                      = BST_IP_INVALID_SOCKET_TYPE;
    m_TrafficPool.ulRxByte              = 0;
    m_TrafficPool.ulTxByte              = 0;
    BST_IP_InitIpAddress( &m_stIpAddress );
}
#endif

/*****************************************************************************
 函 数 名  : ~BST_IP_CSocket
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
BST_IP_CSocket::~BST_IP_CSocket()
{
    BST_IP_PROTOCOL_TYPE                usProtocol;
    BST_IP_CRcverMng                   *RawRcvMng;

    RawRcvMng                           = BST_NULL_PTR;
    usProtocol                          = BST_IP_PROTOCOL_INVALID;

    BST_DBG_LOG( "BST_IP_CSocket::~BST_IP_CSocket" );
    if ( BST_INVALID_PORT != m_stIpAddress.usLocalPort )
    {
        usProtocol                  = GetProtoType();
        BST_IP_ApiRmvPort( usProtocol, m_stIpAddress.usLocalPort, BST_NULL_PTR );
    }
    RawRcvMng                       = BST_IP_CRcverMng::GetInstance();
    if( BST_NULL_PTR != RawRcvMng )
    {
        RawRcvMng->Detach( this );
    }

    m_lFd                               = BST_INVALID_FD;
    m_enSocketType                      = BST_IP_INVALID_SOCKET_TYPE;
}
/*****************************************************************************
 函 数 名  : Socket
 功能描述  : 处理socket
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_IP_ERR_T 返回成功或出错类型
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::Socket ( BST_OS_MBX_T *pstMsgHandle )
{
    SSL_METHOD             *pstMethod;

    if ( !BST_IP_IsValidSocketType( m_enSocketType ) )
    {
        BST_RLS_LOG1( "CSocket m_enSocketType=%d is invalid.", m_enSocketType );
        return BST_IP_ERR_ARG;
    }
    if( BST_SCKT_TYPE_UDP == m_enSocketType )
    {
        m_lFd                = socket( AF_INET, SOCK_DGRAM, 0 );
    }
    else
    {
        m_lFd                = socket( AF_INET, SOCK_STREAM, 0 );
    }

    if( !BST_IP_IsFdValid( m_lFd ) )
    {
        BST_RLS_LOG1( "BSD fd=%d is not valid.", m_lFd );
        return BST_IP_ERR_CONN;
    }

    ioctlsocket( m_lFd, FIONBST, pstMsgHandle );

    if( !BST_IP_IsSslConnection() )
    {
        return BST_IP_ERR_OK;
    }

    SSL_library_init();

    pstMethod               = ( SSL_METHOD * )TLSv1_client_method();

    if (BST_NULL_PTR == pstMethod)
    {
        BST_RLS_LOG( "BST_IP_SslInit TLSv1_client_method error" );
        return BST_NULL_PTR;
    }

    m_pSslContxt        = SSL_CTX_new( pstMethod );
    if ( BST_NULL_PTR == m_pSslContxt)
    {
        BST_RLS_LOG( "BST_IP_SslInit SSL_CTX_new error" );
        return BST_NULL_PTR;
    }

    SSL_CTX_set_verify( (SSL_CTX *)m_pSslContxt, SSL_VERIFY_NONE, BST_NULL_PTR );
    m_pSslHandle        = SSL_new( (SSL_CTX *)m_pSslContxt );

    if ( BST_NULL_PTR == m_pSslHandle )
    {
        BST_RLS_LOG( "BST_IP_SslInit error" );
        return BST_IP_ERR_MEM;
    }
    if ( BST_FALSE == SSL_set_fd( (SSL *)m_pSslHandle, m_lFd ) )
    {
        BST_RLS_LOG( "SSL_set_fd error" );
        return BST_IP_ERR_MEM;
    }
    return BST_IP_ERR_OK;
}
/*****************************************************************************
 函 数 名  : Connect
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_IP_ERR_T 返回出错类型
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::Connect( BST_VOID )
{
    struct sockaddr_in                  stRemoteAddr;
    BST_IP_ERR_T                        enIpErr;

    if( BST_IP_ERR_OK != CheckConfig() )
    {
        return BST_IP_ERR_ARG;
    }
    BST_IP_ApiAddPort( GetProtoType(), m_stIpAddress.usLocalPort );
    BST_IP_ApiSetPreprocWorking( GetProtoType(), m_stIpAddress.usLocalPort, BST_IP_PATH_MODE_SINGLE );

    if( !BST_IP_IsFdValid( m_lFd ) )
    {
        return BST_IP_ERR_MEM;
    }

    stRemoteAddr.sin_len                = BST_OS_SIZEOF(stRemoteAddr);
    stRemoteAddr.sin_family             = AF_INET;
    stRemoteAddr.sin_port               = htons( m_stIpAddress.usRemotePort );
    BST_IP_GetU32Addr( stRemoteAddr.sin_addr.s_addr,
                       m_stIpAddress.aucRemoteIp[3],
                       m_stIpAddress.aucRemoteIp[2],
                       m_stIpAddress.aucRemoteIp[1],
                       m_stIpAddress.aucRemoteIp[0] );
    enIpErr                             = connect( m_lFd,
                                (struct sockaddr*)&stRemoteAddr,
                                     BST_OS_SIZEOF(stRemoteAddr) );

    return enIpErr;
}

/*****************************************************************************
 函 数 名  : Clone
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_IP_ERR_T
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : l00242755
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::Clone( BST_VOID )
{
    struct sockaddr_in                  stRemoteAddr;
    BST_IP_ERR_T                        enIpErr;

    if( BST_IP_ERR_OK != CheckConfig() )
    {
        return BST_IP_ERR_ARG;
    }
    BST_IP_ApiAddPort( GetProtoType(), m_stIpAddress.usLocalPort );

    if( !BST_IP_IsFdValid( m_lFd ) )
    {
        return BST_IP_ERR_MEM;
    }

    stRemoteAddr.sin_len                = BST_OS_SIZEOF(stRemoteAddr);
    stRemoteAddr.sin_family             = AF_INET;
    stRemoteAddr.sin_port               = htons( m_stIpAddress.usRemotePort );
    BST_IP_GetU32Addr( stRemoteAddr.sin_addr.s_addr,
                       m_stIpAddress.aucRemoteIp[3],
                       m_stIpAddress.aucRemoteIp[2],
                       m_stIpAddress.aucRemoteIp[1],
                       m_stIpAddress.aucRemoteIp[0] );
    enIpErr                             = cloneconnect( m_lFd,
                                          (struct sockaddr*)&stRemoteAddr,
                                               BST_OS_SIZEOF(stRemoteAddr),
                                               m_stIpAddress.usLocalPort );

    return enIpErr;
}

/*****************************************************************************
 函 数 名  : FreePcb
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_IP_ERR_T
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年09月10日
      作    者   : l00231445
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::CloneClose( BST_VOID )    //cloneclose
{
    BST_IP_ApiRmvPort( GetProtoType(), m_stIpAddress.usLocalPort, BST_NULL_PTR );
    cloneclose( m_lFd );
    m_lFd                           = BST_INVALID_FD;
    m_pSslHandle                    = BST_NULL_PTR;
    m_pSslContxt                    = BST_NULL_PTR;
    return BST_IP_ERR_OK;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::Bind( BST_VOID )
{
    struct sockaddr_in                  stLocalAddr;
    BST_IP_ERR_T                        enIpError;
    socklen_t                           stAddrLen;

    if( BST_IP_ERR_OK != CheckConfig() )   //这里需要校验的是本地的端口号
    {
        return BST_IP_ERR_ARG;
    }

    if( !BST_IP_IsFdValid( m_lFd ) )
    {
        return BST_IP_ERR_ARG;
    }
    BST_DBG_LOG1( "BST_IP_CSocket::Bind usLocalPort=%u",
                  m_stIpAddress.usLocalPort );
    stLocalAddr.sin_len                 = BST_OS_SIZEOF(stLocalAddr);
    stLocalAddr.sin_family              = AF_INET;
    stLocalAddr.sin_port                = PP_HTONS( m_stIpAddress.usLocalPort );
    stLocalAddr.sin_addr.s_addr         = BST_IP_ADDRESS_ANY;
    enIpError                           = (BST_IP_ERR_T)bind
                                          ( m_lFd, ( struct sockaddr *)&stLocalAddr, BST_OS_SIZEOF(stLocalAddr) );
    if( BST_IP_ERR_OK != enIpError)
    {
        return enIpError;
    }
    /**
    *If we bind a port that is assigned by IP_Stack, We should get the real port value;
    */
    if( 0 == m_stIpAddress.usLocalPort )
    {
        stAddrLen                       = (socklen_t)BST_OS_SIZEOF(sockaddr);
        if( getsockname(m_lFd, (sockaddr *)&stLocalAddr, &stAddrLen) >= 0 )
        {
            m_stIpAddress.usLocalPort   = PP_NTOHS( stLocalAddr.sin_port );
        }
    }
    return BST_IP_ERR_OK;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::Close( BST_VOID )
{
    BST_IP_ERR_T                        usErrVal; 

    if ( BST_IP_ERR_OK != CheckConfig() )
    {
        return BST_IP_ERR_ARG;
    }

    if( !BST_IP_IsFdValid( m_lFd ) )
    {
        return BST_IP_ERR_MEM;
    }

    if( ( BST_IP_IsSslConnection() )
     && ( BST_NULL_PTR != m_pSslHandle ) )
    {
        SSL_shutdown( (SSL *)m_pSslHandle );
    }
    usErrVal                            = close( m_lFd );
    m_lFd                               = BST_INVALID_FD;
    if ( BST_IP_ERR_OK != usErrVal )
    {
        BST_RLS_LOG( "BST_IP_SslClose BST_IP_BsdClose is not OK" );
        return BST_IP_ERR_MEM;
    }
    if( !BST_IP_IsSslConnection() )
    {
        return BST_IP_ERR_OK;
    }
    if ( BST_NULL_PTR != m_pSslHandle )
    {
        SSL_set_session( (SSL *)m_pSslHandle, BST_NULL_PTR );
        SSL_free( (SSL *)m_pSslHandle );
    }
    if ( BST_NULL_PTR != m_pSslContxt)
    {
        SSL_CTX_free( (SSL_CTX *)m_pSslContxt );
    }
    m_pSslHandle                    = BST_NULL_PTR;
    m_pSslContxt                    = BST_NULL_PTR;
    return BST_IP_ERR_OK;
}
/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::Write( 
    const BST_UINT8    *pucSdu,
    BST_UINT16          usLength,
    BST_UINT16          usProcLevel,
    BST_UINT16          usFlags )
{
    BST_INT32               lRtnVal;

    if(( BST_NULL_PTR == pucSdu ) || (0 == usLength))
    {
       return BST_IP_ERR_ARG;
    }

    if( BST_IP_ERR_OK != CheckConfig() )
    {
        return BST_IP_ERR_ARG;
    }

    if( !BST_IP_IsFdValid( m_lFd ) )
    {
        return BST_IP_ERR_MEM;
    }

    if( BST_IP_IsSslConnection() )
    {
        if( BST_NULL_PTR == m_pSslHandle )
        {
            return BST_IP_ERR_CONN;
        }
        lRtnVal             = SSL_write( (SSL *)m_pSslHandle,
                                                pucSdu,
                                                usLength);
        lRtnVal             = SSL_get_error( (SSL *)m_pSslHandle,
                                                lRtnVal );
        if ( SSL_ERROR_NONE != lRtnVal)
        {
            BST_RLS_LOG1( "BST_IP_SslSend Err No. is %d", lRtnVal );
            lRtnVal         = BST_IP_ERR_VAL;
        }
        else
        {
            lRtnVal         = BST_IP_ERR_OK;
        }
    }
    else
    {
        usFlags             = BST_IP_SET_PRIORITY( usProcLevel, usFlags );
        lRtnVal             = ( BST_IP_ERR_T )send( m_lFd, pucSdu, usLength,
                                                    usFlags );
        BST_DBG_LOG3("BST_IP_Socket write send err, length, Flags",lRtnVal,usLength,usFlags);
        if ( lRtnVal > 0 )
        {
            lRtnVal         = BST_IP_ERR_OK;
        }
    }
    return lRtnVal;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_INT32 BST_IP_CSocket::Read( BST_UINT8 *pucSdu, BST_UINT16 usLength )
{
    BST_IP_ERR_T            lRtnVal;

    if ( BST_NULL_PTR == pucSdu )
    {
        return BST_IP_ERR_ARG;
    }
    if ( 0 == usLength )
    {
        return BST_IP_ERR_ARG;
    }
    if ( BST_IP_ERR_OK != CheckConfig() )
    {
        return BST_IP_ERR_ARG;
    }
    if( !BST_IP_IsFdValid( m_lFd ) )
    {
        return BST_IP_ERR_MEM;
    }
    if( BST_IP_IsSslConnection() )
    {
        if( BST_NULL_PTR == m_pSslHandle )
        {
            return BST_IP_ERR_CONN;
        }
        lRtnVal         = SSL_read( (SSL *)m_pSslHandle, pucSdu, usLength );
    }
    else
    {
        lRtnVal         = (BST_IP_ERR_T)read( m_lFd, pucSdu, usLength );
    }
    return lRtnVal;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::IoCtrl( BST_SCKT_CMD_ENUM_UINT32 enCmd, BST_VOID *pvPara )
{
    BST_IP_SOCKET_ADD_T               **ppSocketAddr;
    BST_SCKT_TYPE_ENUM_UINT32           ulSocketType;
    BST_IP_ERR_T                        enIpErr;
    BST_INT32                           lRtnVal;
    BST_UINT32                          ulTimeout;

    if ( BST_NULL_PTR == pvPara )
    {
        return BST_IP_ERR_ARG;
    }

    enIpErr                             = BST_IP_ERR_OK;
    switch (enCmd)
    {
    case BST_SCKT_CMD_GET_ADDRPTR:
        ppSocketAddr                    = ( BST_IP_SOCKET_ADD_T **)pvPara;
       *ppSocketAddr                    = &m_stIpAddress;
        break;

    case BST_SCKT_CMD_SET_ADDRESS:
        enIpErr                         = SetAddr( ( BST_IP_SOCKET_ADD_T *)pvPara );
        break;

    case BST_SCKT_CMD_SET_PROPERTY:
        enIpErr                         = SetPrpty( (BST_IP_SKT_PROPTY_STRU *)pvPara,
                                          BST_IP_SetPropPathFlag( BST_IP_SKT_PROP_TOTAL, BST_IP_PATH_MODE_SINGLE ) );
        break;

    case BST_SCKT_CMD_DBL_PROPERTY:
        enIpErr                         = SetPrpty( (BST_IP_SKT_PROPTY_STRU *)pvPara,
                                          BST_IP_SetPropPathFlag( BST_IP_SKT_PROP_TOTAL, BST_IP_PATH_MODE_DOUBLE ) );
        break;

    case BST_SCKT_CMD_SET_SEQNO:
        enIpErr                         = SetPrpty( (BST_IP_SKT_PROPTY_STRU *)pvPara,
                                          BST_IP_SetPropPathFlag( BST_IP_SKT_PROP_SEQNO, BST_IP_PATH_MODE_NO_CHG ) );
        break;

    case BST_SCKT_CMD_SET_SEQNO_TS:
        enIpErr                         = SetPrpty( (BST_IP_SKT_PROPTY_STRU *)pvPara,
                                          BST_IP_SetPropPathFlag( BST_IP_SKT_PROP_SEQNO_TS, BST_IP_PATH_MODE_NO_CHG ) );
        break;

    case BST_SCKT_CMD_GET_PROPERTY:
        enIpErr                         = GetPrpty( (BST_IP_SKT_PROPTY_STRU *)pvPara, BST_IP_PATH_MODE_STOP );
        break;

    case BST_SCKT_CMD_RPT_PROPERTY:
        BST_IP_ApiSetPreprocSuspend( BST_IP_PROTOCOL_TCP, m_stIpAddress.usLocalPort );
        enIpErr                         = GetPrpty( (BST_IP_SKT_PROPTY_STRU *)pvPara, BST_IP_PATH_MODE_STOP );
        break;

    case BST_SCKT_CMD_SYNC_PROPERTY_START:
        enIpErr                         = GetPrpty( (BST_IP_SKT_PROPTY_STRU *)pvPara, BST_IP_PATH_MODE_DOUBLE );
        break;

    case BST_SCKT_CMD_SYNC_PROPERTY_STOP:
        BST_IP_ApiSetPreprocStop( BST_IP_PROTOCOL_TCP, m_stIpAddress.usLocalPort );
        break;

    case BST_SCKT_CMD_GET_TRAFFIC_FLOW:
        enIpErr                         = GetTrafficFlow( (BST_IP_TRAFFIC_FLOW_STRU *)pvPara, BST_TRUE );
        break;

    case BST_SCKT_CMD_SET_TRAFFIC_FLOW:
        enIpErr                         = SetTrafficFlow( (BST_IP_TRAFFIC_FLOW_STRU *)pvPara );
        break;

    case BST_SCKT_CMD_REG_CALLBACK:
        enIpErr                         = RegCallBack( (BST_IP_CNetRcver *)pvPara );
        break;

    case BST_SCKT_CMD_CHK_FD:
        enIpErr                         = CheckFd( (BST_INT32 *)pvPara );
        break;

    case BST_SCKT_CMD_DEF_TYPE:
        BST_OS_MEMCPY( &ulSocketType, pvPara, BST_OS_SIZEOF(BST_SCKT_TYPE_ENUM_UINT32) );
        enIpErr                         = SetSocketType( ulSocketType );
        break;

    case BST_SCKT_CMD_CHK_CONNECTED:
        if( BST_IP_IsSslConnection() )
        {
            BST_INT32                   ulNonBlock;
            if( BST_NULL_PTR == m_pSslHandle )
            {
                BST_RLS_LOG( "BST_IP_SslConnect Err m_pSslHandle is NULL" );
                enIpErr                 = BST_IP_ERR_ARG;
                break;
            }
            ulTimeout                   = BST_IP_RX_TIME_OUT;
            ulNonBlock                  = 0;
            setsockopt( m_lFd, SOL_SOCKET, SO_RCVTIMEO, &ulTimeout, BST_OS_SIZEOF( ulTimeout ) );
            ioctlsocket( m_lFd, FIONBIO, &ulNonBlock );
            lRtnVal                     = SSL_connect( (SSL *)m_pSslHandle );
            /* 返回值等于1表示connect成功 */
            if ( 1 != lRtnVal )
            {
                enIpErr                 = BST_IP_ERR_VAL;
                lRtnVal                 = SSL_get_error( (SSL *)m_pSslHandle, lRtnVal );
                BST_RLS_LOG1( "BST_IP_SslConnect Err No. is %d", lRtnVal );
            }
            ulTimeout                   = 0;
            ulNonBlock                  = 1;
            setsockopt( m_lFd, SOL_SOCKET, SO_RCVTIMEO, &ulTimeout, BST_OS_SIZEOF( ulTimeout ) );
            ioctlsocket( m_lFd, FIONBIO, &ulNonBlock );
        }
        break;

    default:
        enIpErr                         = BST_IP_ERR_ARG;
        break;
    }
    return enIpErr;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::SetAddr( BST_IP_SOCKET_ADD_T *pstAddress )
{
    BST_IP_SOCKET_ADD_T                 stSockAddrTmp;
    BST_IP_TRAFFIC_FLOW_STRU            stPortTrfcFlow;
    BST_IP_PROTOCOL_TYPE                usProtocol;
    usProtocol                          = BST_IP_PROTOCOL_INVALID;

    BST_ASSERT_NULL_RTN( pstAddress, BST_IP_ERR_ARG );

    BST_DBG_LOG4( "BST_IP_CSocket::SetAddr IP Address %d.%d.%d.%d",\
                  pstAddress->aucRemoteIp[3],\
                  pstAddress->aucRemoteIp[2],\
                  pstAddress->aucRemoteIp[1],\
                  pstAddress->aucRemoteIp[0] );

    BST_DBG_LOG2( "BST_IP_CSocket::SetAddr Dst Port %d, Src Port %d",\
                  pstAddress->usRemotePort,\
                  pstAddress->usLocalPort );

    BST_OS_MEMCPY( &stSockAddrTmp, pstAddress, sizeof( BST_IP_SOCKET_ADD_T ) );

    /* 若两次相等，说明是重复下发*/
    if( 0 == BST_OS_Memcmp( &m_stIpAddress, &stSockAddrTmp, 
                            BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T ) ) )
    {
        return BST_IP_ERR_OK;
    }

    usProtocol                          = GetProtoType();
    if ( BST_INVALID_PORT != m_stIpAddress.usLocalPort )
    {
        stPortTrfcFlow.ulRxByte         = 0;
        stPortTrfcFlow.ulTxByte         = 0;
        BST_IP_ApiRmvPort( usProtocol, m_stIpAddress.usLocalPort, &stPortTrfcFlow );
        m_TrafficPool.ulRxByte         += stPortTrfcFlow.ulRxByte;
        m_TrafficPool.ulTxByte         += stPortTrfcFlow.ulTxByte;
    }
    if ( BST_INVALID_PORT != stSockAddrTmp.usLocalPort )
    {
        BST_IP_ApiAddPort( usProtocol, stSockAddrTmp.usLocalPort );
    }

    BST_OS_MEMCPY( &m_stIpAddress, &stSockAddrTmp, BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T ) );
    return BST_IP_ERR_OK;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::SetPrpty(
    BST_IP_SKT_PROPTY_STRU         *pstProperty,
    BST_IP_SKT_PROP_TYPE_ENUM_U8    enFlag )
{
    BST_IP_SKT_PROPTY_STRU              stSockProptyTmp = { 0u };

    if ( BST_NULL_PTR == pstProperty )
    {
        BST_DBG_LOG("SetPrpty pstProperty NULL");
        return BST_IP_ERR_ARG;
    }

    if( 0 == BST_OS_Memcmp( &stSockProptyTmp, pstProperty,
                            BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU ) ) )
    {
        return BST_IP_ERR_OK;
    }
    return cloneset( m_lFd, pstProperty, BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU ), enFlag );
}
/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::GetPrpty( BST_IP_SKT_PROPTY_STRU *pstProperty, BST_UINT8 bChgFlag )
{
    if( BST_NULL_PTR == pstProperty )
    {
        return BST_IP_ERR_ARG;
    }
    return cloneget( m_lFd, pstProperty, BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU ), bChgFlag );
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年09月22日
      作    者   : c00297028
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::GetTrafficFlow( BST_IP_TRAFFIC_FLOW_STRU *pstProperty, BST_UINT16  usIsReset)
{
    BST_ERR_ENUM_UINT8                  enRtnVal;
    BST_IP_TRAFFIC_FLOW_STRU            stTmpTrfcFlow;

    if ( ( BST_NULL_PTR == pstProperty ) )
    {
        return BST_IP_ERR_ARG;
    }

   /*
    * Get the traffic flow value from the buffer pool firstly
    */
    pstProperty->ulRxByte               = m_TrafficPool.ulRxByte;
    pstProperty->ulTxByte               = m_TrafficPool.ulTxByte;
    
    if ( ( 0 != m_TrafficPool.ulRxByte )
       ||( 0 != m_TrafficPool.ulTxByte ) )
    {
        BST_IP_ApiUpdateTrafficFlow ( BST_IP_TRAFFIC_DEC,
                                    ( m_TrafficPool.ulRxByte +
                                      m_TrafficPool.ulTxByte ) );
        m_TrafficPool.ulRxByte          = 0;
        m_TrafficPool.ulTxByte          = 0;
    }

   /*
    * Try to get the traffic flow value from the current port property
    */
    stTmpTrfcFlow.ulRxByte              = 0;
    stTmpTrfcFlow.ulTxByte              = 0;
    enRtnVal                            = BST_IP_ApiGetTrafficFlow( usIsReset,
                                                                    m_stIpAddress.usLocalPort,
                                                                   &stTmpTrfcFlow );
    if( BST_NO_ERROR_MSG == enRtnVal ) 
    {
        pstProperty->ulRxByte          += stTmpTrfcFlow.ulRxByte;
        pstProperty->ulTxByte          += stTmpTrfcFlow.ulTxByte;
        return BST_IP_ERR_OK;
    }
    else if( BST_ERR_ITEM_NOT_EXISTED == enRtnVal )
    {
        return BST_IP_ERR_OK;
    }
    else
    {
        BST_RLS_LOG1( "BST_IP_CSocket::GetTrafficFlow Error=u%", enRtnVal );
        return BST_IP_ERR_VAL;
    }
}
/*****************************************************************************
 函 数 名  : SetTrafficFlow
 功能描述  : 设置流量值
 输入参数  : 流量值结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::SetTrafficFlow( BST_IP_TRAFFIC_FLOW_STRU *pstProperty )
{
    if ( ( BST_NULL_PTR == pstProperty ) )
    {
        return BST_IP_ERR_ARG;
    }

    m_TrafficPool.ulRxByte              += pstProperty->ulRxByte;
    m_TrafficPool.ulTxByte              += pstProperty->ulTxByte;
    return BST_IP_ERR_OK;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::InqFlow( BST_UINT32 *pTx, BST_UINT32 *pRx )
{
    return BST_IP_ERR_OK;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::InqState( BST_VOID )    //查询的状态指的是什么？？？
{
    return BST_IP_ERR_OK;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::RegCallBack( BST_IP_CNetRcver *pC_CallBack )
{
    BST_IP_CRcverMng                   *RawRcvMng;
    BST_VOID                           *pvRtnVal;

    if ( BST_NULL_PTR == pC_CallBack )
    {
        return BST_IP_ERR_ARG;
    }

    RawRcvMng                           = BST_IP_CRcverMng::GetInstance();
    BST_ASSERT_NULL_RTN ( RawRcvMng, BST_IP_ERR_ARG );
    pvRtnVal                            = RawRcvMng->Attach( pC_CallBack, this );

    if( BST_NULL_PTR == pvRtnVal )
    {
        BST_RLS_LOG( "BST_IP_CSocket::RegCallBack Attach pvRtnVal=NULL" );
        return BST_IP_ERR_VAL;
    }
    return BST_IP_ERR_OK;
}
/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : z00220931
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::SetSocketType( BST_SCKT_TYPE_ENUM_UINT32 enSocketType )
{
    BST_DBG_LOG1("BST_IP_CSocket::SetSocketType enSocketType = %d.", enSocketType);
    if( !BST_IP_IsValidSocketType( enSocketType ) )
    {
        BST_RLS_LOG("BST_IP_CSocket::SetSocketType enSocketType is invalid.");
        return BST_IP_ERR_ARG;
    }
    if( BST_IP_ERR_OK != BST_IP_CheckSocketSupport( enSocketType ) )
    {
        BST_RLS_LOG("BST_IP_CSocket::SetSocketType enSocketType is not support.");
        return BST_IP_ERR_ARG;
    }
    m_enSocketType                  = enSocketType;
    return BST_IP_ERR_OK;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::CheckConfig( BST_VOID ) const
{
    if( !BST_IP_IsValidIpAddress( &m_stIpAddress ) )
    {
        return BST_IP_ERR_ARG;
    }
    if( !BST_IP_IsValidSocketType( m_enSocketType ) )
    {
        return BST_IP_ERR_ARG;
    }
    if( !BST_IP_IsFdValid( m_lFd ) )
    {
        return BST_IP_ERR_CONN;
    }
    return BST_IP_ERR_OK;
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_ERR_T BST_IP_CSocket::CheckFd ( const BST_INT32 *pfd ) const
{
    if ( BST_NULL_PTR == pfd )
    {
        return BST_IP_ERR_VAL;
    }
    if( !BST_IP_IsValidIpAddress( &m_stIpAddress ) )
    {
        return BST_IP_ERR_VAL;
    }

    if ( !BST_IP_IsValidSocketType( m_enSocketType ) )
    {
        return BST_IP_ERR_VAL;
    }
    if ( m_lFd == *pfd )
    {
        return BST_IP_ERR_OK;
    }
    else
    {
        return BST_IP_ERR_VAL;
    }
}

/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年09月10日
      作    者   : l00231445
      修改内容   : 新生成函数
*****************************************************************************/
BST_IP_PROTOCOL_TYPE BST_IP_CSocket::GetProtoType( BST_VOID )
{
    switch ( m_enSocketType )
    {
        case BST_SCKT_TYPE_TCP:
        case BST_SCKT_TYPE_SSL:
            return BST_IP_PROTOCOL_TCP;

        case BST_SCKT_TYPE_UDP:
            return BST_IP_PROTOCOL_UDP;

        default:
            return BST_IP_PROTOCOL_INVALID;
    }
}

