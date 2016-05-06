/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DRV_NET.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年05月04日
  最近修改   :
  功能描述   : 实现带网络参数的循环型任务类BST_CORE_PTask相关处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年05月13日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_DRV_Net.h"
#include "BST_DRV_As.h"
#include "BST_IP_Define.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Sync.h"
#include "BST_OS_Timer.h"
#include "BST_OS_Memory.h"
#include "BST_IP_PreProc.h"
#include "lwip/tcpip.h"
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
#include "lwip/sio.h"
#include "../netif/ppp/ppp_impl.h"
#endif
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DRV_NET_C
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
  3 函数声明
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DRV_NET_Initial         ( BST_VOID    *pvArg );
BST_ERR_ENUM_UINT8  BST_DRV_NET_IoCtrl          ( BST_UINT32   ulCmd,
                                                  BST_VOID    *pvData );
BST_ERR_ENUM_UINT8  BST_DRV_NET_GetTimeStamp    ( BST_UINT32  *pulTimeStamp );
BST_ERR_ENUM_UINT8  BST_DRV_NET_SetTimeStamp    ( BST_DRV_NET_TIME_CLBRT_STRU *pstTimeClbrt );
BST_VOID            BST_DRV_NET_Thread          ( BST_VOID     *pvArg );
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
extern err_t        pppifNetifInit              ( struct netif *netif);
extern void         pppForward                  ( BST_DRV_WRITE_T pfWrite,
                                                  struct pbuf  *pb,
                                                  u_short       protocol,
                                                  u_char        cs_id );
#endif
BST_ERR_ENUM_UINT8  BST_DRV_NET_CfgPktMode      ( BST_DRV_NET_PKT_MODE_ENUM_UINT32 *penPktMode );
BST_UINT32          BST_DRV_NET_Recv            ( BST_UINT32    ulLength,
                                                  BST_UINT8    *pucData );
extern BST_VOID     BST_IP_LwipLockInit         ( BST_VOID );
extern BST_VOID     BST_PAL_NetSendModemRabId   (
    BST_DRV_NET_MODEM_RABID_STRU *pstModemRabId );
extern BST_VOID     BST_DRV_LsItf_NetUsingModem(
    BST_UINT32              ulModemId );

extern BST_VOID BST_DRV_LsItf_NetSetDeviceState(
    BST_DRV_NET_STATE_ENUM_UINT32       ulNetDeviceStatus );
/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/
extern sys_mbox_t                       mbox;
BST_OS_MBX_T                           *g_pBstLwipThreadMbx     = BST_NULL_PTR;
BST_NETIF_T                             g_stMainNetDevice;
BST_NETIF_T                             g_stRbshNetDevice;
BST_UINT8                               g_SourceIpAddr[BST_IP_ADDR_LENTH] = {0U};
BST_DRV_NET_TIMESTAMP_STRU              g_BstDrvNetTimeStamp    = { 0U, 0U, 0U };
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
BST_DRV_NET_PKT_MODE_ENUM_UINT32        g_enBstPktMode          = BST_DRV_PKT_MODE_INVALID;
BST_INT32                               g_lBstDrvNetPppDesc     = BST_DRV_NET_INVALID_PPP_DESC;
#else
BST_DRV_NET_PKT_MODE_ENUM_UINT32        g_enBstPktMode          = BST_DRV_PKT_MODE_IP;
#endif
BST_DRV_STRU                            g_BstDrvNetHandle       =
{
    BST_DRV_NET_Initial,
    BST_DRV_NET_Send,
    BST_DRV_NET_Recv,
    BST_DRV_NET_IoCtrl,
    BST_FALSE
};
BST_DRV_NET_STATE_ENUM_UINT32           g_enNetDeviceStatus     = BST_DRV_NETINVALID;
BST_UINT32                              g_ulTrfcFlowLmt         = BST_IP_NO_TRFC_LMT;
/******************************************************************************
   6 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : BST_DRV_NET_Output
 功能描述  :
 输入参数  : BST_NETIF_T* pstNetif
             BST_NET_PBUF_T* p_stBuf
             BST_NET_IPADD_T* ipaddr
 输出参数  : 无
 返 回 值  : err_t
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
err_t BST_DRV_NET_Output( BST_NETIF_T* pstNetif, BST_NET_PBUF_T* p_stBuf, BST_NET_IPADD_T* ipaddr )
{
    BST_DRV_STRU                       *pstDriver;
    BST_NET_PBUF_T                     *pstCurBuf;
    BST_UINT8                          *pucData;
    BST_UINT16                          usTotalLen;
    BST_ERR_ENUM_UINT8                  enRtnVal;
    BST_UINT8                           ucDataType;
    BST_DRV_IP_DATA_STRU                stData;

    if ( BST_NULL_PTR == p_stBuf )
    {
        return ERR_MEM;
    }
    if ( BST_NULL_PTR == p_stBuf->payload )
    {
        return ERR_MEM;
    }

    ucDataType                          = BST_IP_GET_PRIORITY(p_stBuf->flags);

    BST_DRV_AsProcBstTxData( ucDataType );

    stData.ucDataType                   = ucDataType;

    pstDriver                           = BST_DRV_NetGetDvcHandle();
    if ( BST_NULL_PTR == p_stBuf->next )
    {
        BST_IP_ApiFastCheckUL( (BST_UINT8 *)p_stBuf->payload, p_stBuf->len );
        stData.pucData                  = ( BST_UINT8 *)p_stBuf->payload;
        enRtnVal                        = pstDriver->pfWrite(
                                          p_stBuf->len, ( BST_UINT8 *)&stData);
        if( BST_NO_ERROR_MSG != enRtnVal )
        {
            BST_RLS_LOG1( "BST_DRV_NET_Output Wirte-1 Fail, cause:", enRtnVal );
            return ERR_BUF;
        }
        return ERR_OK;
    }

    pstCurBuf                           = p_stBuf;
    usTotalLen                          = 0;
    for(;;)
    {
        if( LWIP_NULL_PTR == pstCurBuf )
        {
            break;
        }
        usTotalLen                     += pstCurBuf->len;
        pstCurBuf                       = pstCurBuf->next;
    }

    pucData                             = ( BST_UINT8 *)BST_OS_MALLOC( usTotalLen );
    if ( BST_NULL_PTR == pucData )
    {
        return ERR_MEM;
    }
    usTotalLen                          = pbuf_copy_partial( p_stBuf, pucData, usTotalLen, 0 );
    BST_IP_ApiFastCheckUL( pucData, usTotalLen );
    stData.pucData                      = pucData;

    enRtnVal                            = pstDriver->pfWrite( usTotalLen, (BST_UINT8 *)&stData );
    if( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_OS_FREE( pucData );
        BST_RLS_LOG1( "BST_DRV_NET_Output Wirte-2 Fail, cause:", enRtnVal );
        /*lint -e438*/
        return ERR_BUF;
        /*lint +e438*/
    }
    BST_OS_FREE( pucData );
    /*lint -e438*/
    return ERR_OK;
    /*lint +e438*/
}

/*****************************************************************************
 函 数 名  : BST_DRV_NetApiGetDeviceState
 功能描述  : 获取当前网络状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_BOOL BST_DRV_NetApiGetDeviceState( BST_VOID )
{
    if ( BST_DRV_NETSTATE_UP == g_enNetDeviceStatus )
    {
        return BST_TRUE;
    }
    else
    {
        return BST_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : BST_DRV_NetApiSetDeviceState
 功能描述  : 获取当前网络状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_NetApiSetDeviceState( BST_UINT32 ulNetState )
{
    BST_NETIF_T                *pstNetif;
    pstNetif                    = BST_DRV_NetGetMainIfHandle();

    BST_DRV_LsItf_NetSetDeviceState( ulNetState );

    if ( g_enNetDeviceStatus == ulNetState )
    {
        return;
    }

    g_enNetDeviceStatus         = ulNetState;

    if ( BST_DRV_NETSTATE_UP == ulNetState )
    {
        BST_PAL_NetSendNetStateMsg( ulNetState );
        BST_DRV_AsNetStateProc( BST_TRUE );
    }
    else if ( BST_DRV_NETSTATE_DOWN == ulNetState )
    {
        BST_PAL_NetSendNetStateMsg( ulNetState );
        netif_set_down(pstNetif);
        BST_DRV_AsNetStateProc( BST_FALSE );
    }
    else if ( BST_DRV_NETSTATE_UNKOWN == ulNetState )
    {
        BST_PAL_NetSendNetStateMsg( ulNetState );
        netif_set_down(pstNetif);
        BST_DRV_AsNetStateProc( BST_FALSE );
    }
    else
    {
        BST_RLS_LOG1( "BST_DRV_NetApiSetDeviceState error state:", ulNetState );
    }
    return;
}
/*****************************************************************************
 函 数 名  : BST_DRV_NET_CfgAddr
 功能描述  :
 输入参数  : NET_DRV_LOCAL_IP_INFO_STRU  *pstLocalIpInfo
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_NET_CfgAddr( NET_DRV_LOCAL_IP_INFO_STRU *pstLocalIpInfo )
{
    BST_NETIF_T                        *pstNetif;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;

    pstNetif                            = BST_DRV_NetGetMainIfHandle();
    if( BST_NULL_PTR == pstLocalIpInfo )
    {
        return BST_ERR_INVALID_PTR;
    }

    tThreadLockCnt                      = BST_OS_ThreadLock();
    netif_set_down(pstNetif);
    netif_set_ipaddr(pstNetif, (BST_NET_IPADD_T*)&pstLocalIpInfo->ulIp);
    netif_set_gw(pstNetif, (BST_NET_IPADD_T*)&pstLocalIpInfo->ulGateWay);
    netif_set_netmask(pstNetif, (BST_NET_IPADD_T*)&pstLocalIpInfo->ulMask);
    netif_set_up(pstNetif);
    netif_set_default(pstNetif);
    BST_DBG_CONFIG_LOCAL_IP( &pstLocalIpInfo->ulIp, BST_OS_SIZEOF(pstLocalIpInfo->ulIp) );
    BST_DRV_NetApiSetDeviceState( BST_DRV_NETSTATE_UP );
    BST_OS_ThreadUnLock( tThreadLockCnt );

    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_DRV_NET_SetTimeStamp
 功能描述  :
 输入参数  : BST_DRV_NET_TIME_CLBRT_STRU *pstTimeClbrt
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_NET_SetTimeStamp( BST_DRV_NET_TIME_CLBRT_STRU *pstTimeClbrt )
{
    BST_UINT32                          ulTimeUnit;
    BST_UINT32                          ulNowTime;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;
    BST_DRV_NET_TIMESTAMP_STRU         *pstTimeStamp;

    if( BST_NULL_PTR == pstTimeClbrt )
    {
        return BST_ERR_INVALID_PTR;
    }

    tThreadLockCnt                      = BST_OS_ThreadLock();
    pstTimeStamp                        = BST_DRV_NetGetTimeStampHandle();
    ulNowTime                           = BST_OS_TimerNowMs();

    if( pstTimeClbrt->ulTimeFreq > BST_OS_MS_IN_S )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return BST_ERR_ILLEGAL_PARAM;
    }
    else if( 0U == pstTimeClbrt->ulTimeFreq )
    {
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return BST_ERR_ILLEGAL_PARAM;
    }
    else
    {
        ulTimeUnit                      = BST_OS_MS_IN_S / pstTimeClbrt->ulTimeFreq;
    }

    pstTimeStamp->ulApStartTime         = pstTimeClbrt->ulTimeStmp;
    pstTimeStamp->ulBstStartTime        = ulNowTime;
    pstTimeStamp->ulApTimeUnitMs        = ulTimeUnit;

    BST_OS_ThreadUnLock( tThreadLockCnt );
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_DRV_NET_GetTimeStamp
 功能描述  :
 输入参数  : BST_UINT32 *pulTimeStamp
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_NET_GetTimeStamp( BST_UINT32 *pulTimeStamp )
{
    BST_UINT32                          ulTimeDiff;
    BST_UINT32                          ulNowTime;
    BST_DRV_NET_TIMESTAMP_STRU         *pstTimeStamp;

    pstTimeStamp                        = BST_DRV_NetGetTimeStampHandle();

    ulNowTime                           = BST_OS_TimerNowMs();

    if( BST_NULL_PTR == pulTimeStamp )
    {
        return BST_ERR_INVALID_PTR;
    }
    if( !BST_DRV_IsNetTimeStampValid() )
    {
       *pulTimeStamp                    = ulNowTime;
        return BST_NO_ERROR_MSG;
    }
    if( ulNowTime < pstTimeStamp->ulBstStartTime )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    ulTimeDiff                          = ulNowTime - pstTimeStamp->ulBstStartTime;
    if( ulTimeDiff < pstTimeStamp->ulApTimeUnitMs )
    {
        ulTimeDiff                      = 1U;
    }
    else
    {
        ulTimeDiff                      = ulTimeDiff / pstTimeStamp->ulApTimeUnitMs;
    }
   *pulTimeStamp                        = pstTimeStamp->ulApStartTime + ulTimeDiff;
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 函 数 名  : BST_DRV_NET_CmdResumeToAp
 功能描述  : 返还数据给AP
 输入参数  : BST_VOID *pvData   数据指针
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_NET_CmdResumeToAp( BST_VOID *pvData )
{
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
    if ( BST_DRV_PKT_MODE_PPP == BST_DRV_NetGetPktMode() )
    {
        pppForward( BST_DRV_NET_ForwardPPP,
                    ( struct pbuf *)pvData , PPP_IP, BST_IP_DEFAULT_CS_ID );//define marco
        return BST_NO_ERROR_MSG;
    }
    else
#endif
    {
        return BST_DRV_NET_ResumeToAp( pvData );
    }
}

/*****************************************************************************
 函 数 名  : BST_DRV_NET_CmdFreePacket
 功能描述  : 从数据队列删除一个IP Packet
 输入参数  : BST_VOID *pvData   该包数据对应指针
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_NET_CmdFreePacket( BST_VOID *pvData )
{
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
    if ( BST_DRV_PKT_MODE_PPP == BST_DRV_NetGetPktMode() )
    {
        return BST_NO_ERROR_MSG;
    }
    else
#endif
    {
        return BST_DRV_NET_FreePackt( pvData );
    }
}

/*****************************************************************************
 函 数 名  : BST_DRV_NET_IoCtrl
 功能描述  :
 输入参数  : BST_UINT32 ulCmd
             BST_VOID *pvData
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_NET_IoCtrl( BST_UINT32 ulCmd, BST_VOID *pvData )
{
    switch( ulCmd )
    {
    case BST_DRV_CMD_LOCAL_ADDR:
        return BST_DRV_NET_CfgAddr( (NET_DRV_LOCAL_IP_INFO_STRU *)pvData );

    case BST_DRV_CMD_RESUME_TO_AP:
        return BST_DRV_NET_CmdResumeToAp( pvData );

    case BST_DRV_CMD_SET_BEARER:
        break;

    case BST_DRV_CMD_SET_NET_TIMESTAMP:
        return BST_DRV_NET_SetTimeStamp( (BST_DRV_NET_TIME_CLBRT_STRU *)pvData );

    case BST_DRV_CMD_SET_TRFC_FLOW_LMT:
        BST_ASSERT_NULL_RTN( pvData, BST_ERR_INVALID_PTR );
        g_ulTrfcFlowLmt     = *( (BST_UINT32 *)pvData );
        BST_RLS_LOG1( " BST_Drv_Net, Set Traffic Flow Limit = %u Bytes ", g_ulTrfcFlowLmt );
        return BST_NO_ERROR_MSG;

    case BST_DRV_CMD_GET_NET_TIMESTAMP:
        return BST_DRV_NET_GetTimeStamp( (BST_UINT32 *)pvData );
    case BST_DRV_CMD_NET_DOWN:
        BST_DRV_NetApiSetDeviceState( BST_DRV_NETSTATE_DOWN );
        break;

    case BST_DRV_CMD_NET_UNKOWN:
        BST_DRV_NetApiSetDeviceState( BST_DRV_NETSTATE_UNKOWN );
        break;
    case BST_DRV_CMD_FREE_PACKET_ITEM:
        return BST_DRV_NET_CmdFreePacket( pvData );

    case BST_DRV_CMD_NET_PKT_MODE:
        return BST_DRV_NET_CfgPktMode( pvData );

    case BST_DRV_CMD_GET_NET_STATE:
        BST_ASSERT_NULL_RTN( pvData, BST_ERR_INVALID_PTR );
       *( (BST_BOOL *)pvData )     = BST_DRV_NetApiGetDeviceState();
        break;

    case BST_DRV_CMD_SET_MODEM_RABID:
        BST_PAL_NetSendModemRabId(
            ( BST_DRV_NET_MODEM_RABID_STRU *) pvData );
        BST_DRV_LsItf_NetUsingModem( 
            ( ( BST_DRV_NET_MODEM_RABID_STRU *) pvData )->usModemId );
        break;

    case BST_DRV_CMD_HPR_DATA_FINISH:
        BST_DRV_AsProcHpriDataFinish();
        break;

    default:
        return BST_ERR_PAR_UNKNOW;
    }
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_DRV_NET_IfInit
 功能描述  :
 输入参数  : BST_NETIF_T* pstNetif
 输出参数  : 无
 返 回 值  : err_t
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
err_t BST_DRV_NET_IfInit( BST_NETIF_T* pstNetif )
{
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
    BST_DRV_NET_PKT_MODE_ENUM_UINT32    enNetPacketMode;

    enNetPacketMode                     = BST_DRV_NetGetPktMode();
    if ( BST_DRV_PKT_MODE_IP != enNetPacketMode )
    {
        return ERR_OK;
    }
#endif
    if ( BST_NULL_PTR != pstNetif )
    {
        pstNetif->hwaddr_len            = 6U;
        pstNetif->name[0]               = 't';
        pstNetif->name[1]               = 'n';
        pstNetif->output                = BST_DRV_NET_Output;
        pstNetif->mtu                   = BST_IP_MTU_SIZE;
        return ERR_OK;
    }
    else
    {
        return ERR_MEM;
    }
}

/*****************************************************************************
 函 数 名  : 3GPP网络IP包接收函数，
 功能描述  :
 输入参数  : BST_UINT32   ulLength
             BST_UINT8   *pucData
 输出参数  : 无
 返 回 值  : BST_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_DRV_NET_Recv( BST_UINT32   ulLength,
                             BST_UINT8   *pucData )
{
    BST_DRV_STRU                    *pstNetDriver;
    BST_DRV_NET_PKT_MODE_ENUM_UINT32 enNetPacketMode;
    BST_UINT32                       ulRtnLength;

    pstNetDriver                    = BST_DRV_NetGetDvcHandle();
    ulRtnLength                     = 0U;

    if( BST_TRUE != pstNetDriver->ulIsInited )
    {
        BST_DBG_LOG("pstNetDriver is not init");
        return 0U;
    }

    enNetPacketMode                 = BST_DRV_NetGetPktMode();
    switch( enNetPacketMode )
    {
        case BST_DRV_PKT_MODE_IP:
            ulRtnLength             = BST_PAL_NetItfPacketRcvd( ulLength,
                                                                pucData );
            break;
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
        case BST_DRV_PKT_MODE_PPP:
            ulRtnLength             = BST_PAL_NetApiPacketPppRcvd( ulLength,
                                                                   pucData );
            break;
#endif
        default:
            BST_DBG_LOG1("enNetPacketMode = %d",enNetPacketMode);
            ulRtnLength             = 0U;
    }
    return ulRtnLength;
}

/*****************************************************************************
 函 数 名  : BST_DRV_NET_CfgPktMode
 功能描述  :
 输入参数  : BST_DRV_NET_PKT_MODE_ENUM_UINT32  *penPktMode
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_NET_CfgPktMode( BST_DRV_NET_PKT_MODE_ENUM_UINT32  *penPktMode )
{
    BST_DRV_NET_PKT_MODE_ENUM_UINT32    enNetPacketMode;
    BST_OS_LOCKCNT_T                    tThreadLockCnt;
    BST_DRV_STRU                       *pstDrvHandler;
    BST_ERR_ENUM_UINT8                  enRtnVal;

    pstDrvHandler                       = BST_DRV_NetGetDvcHandle();
    enRtnVal                            = BST_NO_ERROR_MSG;

    if( BST_NULL_PTR == penPktMode )
    {
        return BST_ERR_INVALID_PTR;
    }

    enNetPacketMode                     = *penPktMode;

    tThreadLockCnt                      = BST_OS_ThreadLock();

    if ( enNetPacketMode == BST_DRV_NetGetPktMode() )
    {
        BST_RLS_LOG1("The Packet mode is same as before: %d", enNetPacketMode );
        BST_OS_ThreadUnLock( tThreadLockCnt );
        return BST_NO_ERROR_MSG;
    }
    BST_RLS_LOG2( "Packet Mode %d to %d", g_enBstPktMode, enNetPacketMode );
    g_enBstPktMode                      = enNetPacketMode;

    if ( BST_TRUE == pstDrvHandler->ulIsInited )
    {
        switch( enNetPacketMode )
        {
            case BST_DRV_PKT_MODE_IP:
                BST_PAL_NetDeviceInitItf( BST_DRV_NetGetMainIfHandle() );
                break;

#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
            case BST_DRV_PKT_MODE_PPP:
                pppifNetifInit( BST_DRV_NetGetMainIfHandle() );
                break;
#endif

            default:
                enRtnVal                = BST_ERR_ILLEGAL_PARAM;
            break;
        }
    }
    netif_set_default( BST_DRV_NetGetMainIfHandle() );
    netif_set_up( BST_DRV_NetGetMainIfHandle() );
    BST_OS_ThreadUnLock( tThreadLockCnt );
    return enRtnVal;
}

#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
/*****************************************************************************
 函 数 名  : BST_DRV_NET_PppCb
 功能描述  :
 输入参数  : void *ctx
             int errCode
             void *arg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
void BST_DRV_NET_PppCb( void *ctx, int errCode, void *arg )
{

}
#endif

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
BST_ERR_ENUM_UINT8 BST_DRV_NET_RbshInitial( NET_DRV_LOCAL_IP_INFO_STRU* pstLocalIpInfo )
{
    NET_DRV_LOCAL_IP_INFO_STRU          stRubbishNetAddr;
    if ( BST_NULL_PTR == pstLocalIpInfo )
    {
        BST_RLS_LOG( "BST_DRV_NET_RbshInitial Error: BST_ERR_INVALID_PTR" );
        return BST_ERR_INVALID_PTR;
    }

    BST_OS_MEMCPY( &stRubbishNetAddr, pstLocalIpInfo,
                   BST_OS_SIZEOF( NET_DRV_LOCAL_IP_INFO_STRU ) );

    stRubbishNetAddr.ulIp               = BST_INVALID_IP_ADDR;
    netif_add( BST_DRV_NetGetRbshIfHandle(),
             ( BST_NET_IPADD_T *)&stRubbishNetAddr.ulIp,
             ( BST_NET_IPADD_T *)&stRubbishNetAddr.ulMask,
             ( BST_NET_IPADD_T *)&stRubbishNetAddr.ulGateWay,
               BST_NULL_PTR,
               BST_DRV_NetInitInterface,
               tcpip_input );
    netif_set_default( BST_DRV_NetGetRbshIfHandle() );
    netif_set_up( BST_DRV_NetGetRbshIfHandle() );
    BST_RLS_LOG( "BST_DRV_NET_RbshInitial Success!" );
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_DRV_NET_Initial
 功能描述  :
 输入参数  : BST_VOID *pvArg
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_NET_Initial( BST_VOID *pvArg )
{
    BST_DRV_STRU                       *pstDrvHandler;
    NET_DRV_LOCAL_IP_INFO_STRU         *pstLocalIpInfo;
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
    BST_INT32                           lPppDesc;
    BST_DRV_NET_PKT_MODE_ENUM_UINT32    enNetPacketMode;
#endif

    pstDrvHandler                       = BST_DRV_NetGetDvcHandle();
    pstLocalIpInfo                      = ( NET_DRV_LOCAL_IP_INFO_STRU *)pvArg;

    if( BST_NULL_PTR == pstLocalIpInfo )
    {
        return BST_ERR_INVALID_PTR;
    }

    if( BST_FALSE == pstDrvHandler->ulIsInited )
    {
        pstDrvHandler->ulIsInited       = BST_TRUE;
        tcpip_init(BST_NULL_PTR, BST_NULL_PTR);
        BST_DBG_CONFIG_LOCAL_IP( &pstLocalIpInfo->ulIp, BST_OS_SIZEOF(pstLocalIpInfo->ulIp) );
        netif_add( BST_DRV_NetGetMainIfHandle(),
                 ( BST_NET_IPADD_T *)&pstLocalIpInfo->ulIp,
                 ( BST_NET_IPADD_T *)&pstLocalIpInfo->ulMask,
                 ( BST_NET_IPADD_T *)&pstLocalIpInfo->ulGateWay,
                   BST_NULL_PTR,
                   BST_DRV_NetInitInterface,//BST_DRV_NET_IfInit,
                   tcpip_input );
        BST_DRV_NetApiSetDeviceState( BST_DRV_NETSTATE_UP );
        BST_DRV_NET_RbshInitial( pstLocalIpInfo );
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
        BST_OS_SleepMs( 1000U );
        pppInit();
        lPppDesc                        = pppOpen( BST_DRV_NetGetMainIfHandle(),\
                                                   BST_DRV_NET_Send,\
                                                   BST_DRV_NET_PppCb,\
                                                   NULL );
        BST_DRV_NetSetPppDesc( lPppDesc );

        if ( BST_DRV_IsPppDescValid() )
        {
            ppp_send_config( BST_DRV_NetGetPppDesc(),
                             BST_IP_MTU_SIZE, 0U, 1, 1 );
            /*                                  *
             * Set Mode To PPP Packet Mode      *
             *                                  */
            enNetPacketMode             = BST_DRV_NetGetPktMode();
            if ( BST_DRV_PKT_MODE_PPP == enNetPacketMode )
            {
                pppifNetifInit( BST_DRV_NetGetMainIfHandle() );
            }
        }
#endif
        netif_set_default( BST_DRV_NetGetMainIfHandle() );
        netif_set_up( BST_DRV_NetGetMainIfHandle() );
    }
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_DRV_InitNetThread
 功能描述  :
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
BST_VOID BST_DRV_InitNetThread( BST_VOID )
{
    BST_OS_CreateThread ( ( BST_INT8 *)"BST_IP_Thread",
                          ( BST_OS_THREAD_T)BST_DRV_NET_Thread,
                            BST_NULL_PTR,
                            BST_OS_STACK_SIZE_XL,
                            BST_OS_PRIO_MIDL );
    BST_IP_LwipLockInit();
}

/*****************************************************************************
 函 数 名  : BST_DRV_NET_Thread
 功能描述  :
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
BST_VOID BST_DRV_NET_Thread( BST_VOID *pvArg )
{
    lwip_thread_fn                      pfLwipThreadFun;
    BST_UINT32                          ulMbxRtn;

    BST_SetThreadInitFlag( BST_TCPIP_THREAD_FLAG );
    pfLwipThreadFun                     = BST_NULL_PTR;
    g_pBstLwipThreadMbx                 = BST_OS_CreateMbx  ( BST_NULL_PTR, BST_S_MBOX_SIZE);
    BST_ASSERT_NULL( g_pBstLwipThreadMbx );
    mbox                                = BST_OS_CreateMbx  ( BST_NULL_PTR, BST_L_MBOX_SIZE);
    BST_ASSERT_NULL( mbox );

    do{
    ulMbxRtn                            = BST_OS_RecvMail   ( g_pBstLwipThreadMbx,
                                                             (BST_VOID **)&pfLwipThreadFun,
                                                              (BST_UINT32)BST_OS_SYS_FOREVER );
    }while( ( BST_OS_SYS_TIMEOUT == ulMbxRtn )
          ||( BST_NULL_PTR == pfLwipThreadFun) );

    pfLwipThreadFun( BST_NULL_PTR );
}

/*****************************************************************************
 函 数 名  : BST_DRV_NetGetPktLen
 功能描述  : 获取数据包长度
 输入参数  : BST_VOID *pvPkt
 输出参数  : 无
 返 回 值  : BST_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_DRV_NetGetPktLen( BST_VOID *pvPkt )
{
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
    struct pbuf         *pstBuffer;
#endif
    if ( BST_NULL_PTR == pvPkt )
    {
        return 0U;
    }
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
    if ( BST_DRV_PKT_MODE_PPP == BST_DRV_NetGetPktMode() )
    {
        pstBuffer       = ( struct pbuf* )pvPkt;
        return pstBuffer->len;
    }
    else
#endif
    {//pc-lint 要求if else要有大括号
        return BST_PAL_NetApiPacketLen( pvPkt );
    }
}

/*****************************************************************************
 函 数 名  : BST_DRV_NetGetPktHead
 功能描述  : 获取数据包头部
 输入参数  : BST_VOID *pvPkt
 输出参数  : 无
 返 回 值  : BST_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT8 *BST_DRV_NetGetPktHead( BST_VOID *pvPkt )
{
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
    struct pbuf         *pstBuffer;
#endif
    if ( BST_NULL_PTR == pvPkt )
    {
        return BST_NULL_PTR;
    }
#if( BST_IP_SUPPORT_PPP == BST_FEATURE_ON )
    if ( BST_DRV_PKT_MODE_PPP == BST_DRV_NetGetPktMode() )
    {
        pstBuffer       = ( struct pbuf* )pvPkt;
        return pstBuffer->payload;
    }
    else
#endif
    {
        return BST_PAL_NetGetPacketHead( pvPkt );
    }
}

