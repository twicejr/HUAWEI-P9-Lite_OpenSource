/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SRV_Event.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年7月4日
  最近修改   :
  功能描述   : 服务程序事件处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月4日
    作    者   : d00173029
    修改内容   : 创建文件
  2.日    期   : 2015年1月10日
    作    者   : d00173029
    修改内容   : 维护支持升级V2.0版本，加入APP-Task独立线程处理

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_SRV_Event.h"
#include "BST_OS_Memory.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_AsEvnt.h"
#include "BST_SRV_AsCtrl.h"
#include "BST_DSPP_TrsLayer.h"
#include "BST_APP_MainTask.h"
#include "BST_DSPP_AppLayer.h"
#include "BST_CORE_Schd.h"
#include "lwip/tcpip.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SRV_EVENT_CPP
/*lint +e767*/

/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
  3 函数声明
*****************************************************************************/
extern "C" sys_mbox_t   mbox;
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
 函 数 名  : BST_SRV_InitInstance
 功能描述  : 初始化系统主要部件实例
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_InitInstance( BST_VOID )
{
    BST_SRV_CAsEvt::GetInstance();
    BST_SRV_CAsCtrl::GetInstance();
    BST_CTaskSchdler::GetInstance ();
    BST_APP_CMainTask::GetInstance();
    BST_IP_CAsRcver::GetInstance();
}

/*****************************************************************************
 函 数 名  : BST_SRV_ApiSendAcomRxEvent
 功能描述  : 接收DSPP数据
 输入参数  : ulLength:数据长度
             pucData:DSPP数据
 输出参数  : 无
 返 回 值  : BST_UINT32
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年01月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_ApiSendAcomRxEvent( BST_UINT32 ulLength, BST_UINT8 *pucData )
{
    BST_ACOM_EVT_STRU      *pstAcpuEvent;
    BST_OS_MBX_T           *pstEventMbx;
    BST_ERR_ENUM_UINT8      enSndResult;

    if( BST_NULL_PTR == pucData )
    {
        return 0;
    }
    if( 0 == ulLength )
    {
        return 0;
    }

    pstEventMbx             = BST_SRV_GetSysMsgHandle();
    if( BST_NULL_PTR == pstEventMbx )
    {
        return 0;
    }

    pstAcpuEvent            = (BST_ACOM_EVT_STRU *)
                               BST_OS_MALLOC( BST_OS_SIZEOF(BST_ACOM_EVT_STRU) );
    BST_ASSERT_NULL_RTN( pstAcpuEvent, BST_ERR_NO_MEMORY );

    pstAcpuEvent->pucData   = (BST_UINT8 *)BST_OS_MALLOC( ulLength );
    if ( BST_NULL_PTR == pstAcpuEvent->pucData )
    {
        BST_OS_FREE( pstAcpuEvent );
        return 0;
    }

    pstAcpuEvent->enId      = BST_SRV_ACOM_EVENT;
    pstAcpuEvent->ulLength  = ulLength;
    BST_OS_MEMCPY( pstAcpuEvent->pucData, pucData, ulLength );
    enSndResult             = BST_OS_SendMail( pstEventMbx, pstAcpuEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ulLength;
    }
    else
    {
        BST_OS_FREE( pstAcpuEvent->pucData );
        BST_OS_FREE( pstAcpuEvent );
        return 0;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_ApiSendPTaskEvent
 功能描述  : 处理PTASK超时事件
 输入参数  :
             BST_UINT16  enComdId   事件命令ID
             BST_VOID   *pvTask     任务类对象指针
             BST_UINT16  usContnt   事件具体内容
 输出参数  : 无
 返 回 值  : BST_UINT32 实际发送事件字节数
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_ApiSendPTaskEvent(
    BST_VOID               *pvTask,
    BST_UINT16              enComdId,
    BST_UINT16              usContnt )
{
    BST_PTASK_EVT_STRU             *pcPTaskEvent;
    BST_OS_MBX_T                   *pstMsgHandle;
    BST_CORE_CPTask                *pPtackIns;
    BST_ERR_ENUM_UINT8              enSndResult;

    pPtackIns                       = ( BST_CORE_CPTask *)pvTask;
    if( BST_NULL_PTR == pPtackIns )
    {
        return 0;
    }
    /**
     如果是schd发送到任务的，那么从任务队列取出消息句柄
    */
    if( BST_CORE_IS_S2T_CMD( enComdId ) )
    {
        pstMsgHandle                = BST_SRV_GetTaskMsgHandle
                                    ( pPtackIns->m_usProcId, pPtackIns->m_usTaskId );
    }
    /**
     如果是task发送到schd的，那么取系统消息句柄
    */
    else if( enComdId < BST_SRV_SCHD_EVEN_BUTT )
    {
        pstMsgHandle                = BST_SRV_GetSysMsgHandle();
    }
    else
    {
        pstMsgHandle                = BST_NULL_PTR;
    }
    if( BST_NULL_PTR == pstMsgHandle )
    {
        return 0;
    }

    pcPTaskEvent                    = ( BST_PTASK_EVT_STRU *)BST_OS_MALLOC
                                      ( BST_OS_SIZEOF(BST_PTASK_EVT_STRU) );
    BST_ASSERT_NULL_RTN( pcPTaskEvent, 0 );

    pcPTaskEvent->pucData           = ( BST_UINT8 *)pvTask;
    pcPTaskEvent->ulLength          = BST_OS_SIZEOF( BST_PTASK_EVT_STRU );
    pcPTaskEvent->enId              = BST_SRV_PTASK_EVENT;
    pcPTaskEvent->usContent         = usContnt;
    pcPTaskEvent->usMsgId           = enComdId;
    enSndResult                     = BST_OS_SendMail( pstMsgHandle, pcPTaskEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return BST_OS_SIZEOF( BST_PTASK_EVT_STRU );
    }
    else
    {
        BST_OS_FREE( pcPTaskEvent );
        return 0;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_ApiSendAsEvent
 功能描述  : 发送AS事件至相应APP对应线程
 输入参数  : 
             pcInAsRcver:事件接收线程消息句柄
             enAsEvent:事件ID
             ulLength:参数长度
             pvData:参数内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_ApiSendAsEvent(
    BST_VOID               *pcInAsRcver,
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    BST_SRV_CAsRcver       *pcAsRcver;
    BST_AS_EVT_STRU        *pstSendAsEvent;
    BST_ERR_ENUM_UINT8      enSndResult;

    pcAsRcver               = ( BST_SRV_CAsRcver *)pcInAsRcver;

    if( BST_NULL_PTR == pcAsRcver )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( pcAsRcver->m_pstRcvMbox == (BST_OS_MBX_T *)mbox )
    {
        BST_DBG_LOG("BST_SRV_ApiSendAsEvent");
        return BST_SRV_ApiSendLwipAsEvent( pcInAsRcver, enAsEvent, ulLength, pvData );
    }
    if( !BST_SRV_IsValidAsEvent( enAsEvent ) )
    {
        return BST_ERR_INVALID_PTR;
    }
    pstSendAsEvent          = (BST_AS_EVT_STRU *)
                               BST_OS_MALLOC( BST_OS_SIZEOF(BST_AS_EVT_STRU) );
    BST_ASSERT_NULL_RTN( pstSendAsEvent, BST_ERR_NO_MEMORY );

    pstSendAsEvent->pucData = ( BST_UINT8 *)BST_OS_MALLOC( ulLength );
    if ( BST_NULL_PTR == pstSendAsEvent->pucData )
    {
        BST_OS_FREE( pstSendAsEvent );
        return 0;
    }
    BST_OS_MEMCPY( pstSendAsEvent->pucData, pvData, ulLength );
    pstSendAsEvent->pcRcver = pcAsRcver;
    pstSendAsEvent->enMsgId = enAsEvent;
    pstSendAsEvent->ulLength= ulLength;
    pstSendAsEvent->enId    = BST_SRV_AS_EVENT;

    enSndResult             = BST_OS_SendMail( 
                            ( BST_OS_MBX_T * )pcAsRcver->m_pstRcvMbox,
                                              pstSendAsEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ( BST_UINT32 )BST_OS_SIZEOF( pcAsRcver );
    }
    else
    {
        BST_OS_FREE( pstSendAsEvent->pucData );
        BST_OS_FREE( pstSendAsEvent );
        return 0;
    }
}
/*****************************************************************************
 函 数 名  : BST_SRV_ApiSendLwipAsEvent
 功能描述  : 发送As事件到TCP/IP线程
 输入参数  : 
             pcInAsRcver:事件接收线程消息句柄
             enAsEvent:事件ID
             ulLength:参数长度
             pvData:参数内容
 输出参数  : 无
 返 回 值  : BST_UINT32 实际事件发送字节数
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年5月14日
      作    者   : z00220931
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_ApiSendLwipAsEvent(
    BST_VOID               *pcInAsRcver,
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    BST_SRV_CAsRcver           *pcAsRcver;
    struct tcpip_msg           *pstLwipMsg;
    BST_UINT8                  *pucData;
    BST_ERR_ENUM_UINT8          enSndResult;

    pcAsRcver               = ( BST_SRV_CAsRcver *)pcInAsRcver;

    if( BST_NULL_PTR == pcAsRcver )
    {
        return BST_ERR_INVALID_PTR;
    }

    if( !BST_SRV_IsValidAsEvent( enAsEvent ) )
    {
        return BST_ERR_INVALID_PTR;
    }

    pstLwipMsg                  = ( struct tcpip_msg *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF(struct tcpip_msg) );
    if ( BST_NULL_PTR == pstLwipMsg )
    {
        return 0;
    }

    pucData                     = ( BST_UINT8 *)BST_OS_MALLOC( ulLength );
    if ( BST_NULL_PTR == pucData )
    {
        BST_OS_FREE(pstLwipMsg);
        return 0;
    }
    BST_OS_MEMCPY( pucData, pvData, ulLength );
    pstLwipMsg->type            = TCPIP_MSG_BST_ASEVENT;
    pstLwipMsg->msg.bst_asevent.stAsEvent.pcRcver
                                = pcAsRcver;
    pstLwipMsg->msg.bst_asevent.stAsEvent.enMsgId
                                = enAsEvent;
    pstLwipMsg->msg.bst_asevent.stAsEvent.enId
                                = BST_SRV_AS_EVENT;
    pstLwipMsg->msg.bst_asevent.stAsEvent.pucData
                                = pucData;
    pstLwipMsg->msg.bst_asevent.stAsEvent.ulLength
                                = ulLength;

    enSndResult                 = BST_OS_SendMail( (BST_OS_MBX_T *)mbox, pstLwipMsg );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ( BST_UINT32 )BST_OS_SIZEOF( struct tcpip_msg );
    }
    else
    {
        BST_OS_FREE( pucData );
        BST_OS_FREE( pstLwipMsg );
        return 0;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_ApiSendLwipTimerEvent
 功能描述  : 发送LWIP定时超时事件至TCP/IP线程
 输入参数  : BST_OS_TIMERID_T ulTimerId 定时器ID
 输出参数  : 无
 返 回 值  : BST_UINT32 实际事件发送字节数
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_ApiSendLwipTimerEvent( BST_OS_TIMERID_T ulTimerId )
{
    struct tcpip_msg           *pstLwipMsg;
    BST_ERR_ENUM_UINT8          enSndResult;

    pstLwipMsg                  = ( struct tcpip_msg *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF(struct tcpip_msg) );
    if ( BST_NULL_PTR == pstLwipMsg )
    {
        return 0;
    }

    pstLwipMsg->type            = TCPIP_MSG_BST_TIMEOUT;
    pstLwipMsg->msg.bst_tmo.id  = ulTimerId;
    enSndResult                 = BST_OS_SendMail( (BST_OS_MBX_T *)mbox, pstLwipMsg );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ( BST_UINT32 )BST_OS_SIZEOF( struct tcpip_msg );
    }
    else
    {
        BST_OS_FREE( pstLwipMsg );
        return 0;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_ApiSendExpiredEvent
 功能描述  : 发送定时器超时消息
 输入参数  : 
             BST_OS_MBX_T       *pstRcvHandle 对应接收线程邮箱句柄
             BST_OS_TIMERID_T    ulTimerId定时器ID
 输出参数  : 无
 返 回 值  : BST_UINT32 实际事件发送字节数
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_ApiSendExpiredEvent(
    BST_VOID           *pstRcvHandle,
    BST_UINT32          ulTimerId )
{
    BST_TIMER_EVT_STRU                 *pstSendTimerEvent;
    BST_ERR_ENUM_UINT8                  enSndResult;

    BST_ASSERT_NULL_RTN( pstRcvHandle, BST_ERR_NO_MEMORY );

    if ( pstRcvHandle == (BST_VOID *)mbox )
    {
        return BST_SRV_ApiSendLwipTimerEvent( ulTimerId );
    }
    pstSendTimerEvent                   = ( BST_TIMER_EVT_STRU *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF(BST_TIMER_EVT_STRU) );
    BST_ASSERT_NULL_RTN( pstSendTimerEvent, BST_ERR_NO_MEMORY );

    pstSendTimerEvent->pucData          = ( BST_UINT8 *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF(ulTimerId) );
    if ( BST_NULL_PTR == pstSendTimerEvent->pucData )
    {
        BST_OS_FREE( pstSendTimerEvent );
        return 0;
    }

    pstSendTimerEvent->ulLength         = BST_OS_SIZEOF( ulTimerId );
    BST_OS_MEMCPY( pstSendTimerEvent->pucData,
                  &ulTimerId,
                   pstSendTimerEvent->ulLength );

    pstSendTimerEvent->enId             = BST_SRV_TIMER_EVENT;

    enSndResult                         = BST_OS_SendMail(
                                          (BST_OS_MBX_T *)pstRcvHandle,
                                                          pstSendTimerEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return BST_OS_SIZEOF(BST_OS_TIMER_STRU);
    }
    else
    {
        BST_OS_FREE( pstSendTimerEvent->pucData );
        BST_OS_FREE( pstSendTimerEvent );
        return 0;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_ApiSendTcpIpEvent
 功能描述  : 发送TCP/IP事件
 输入参数  : 
             BST_OS_MBX_T       *pstRcvHandle   对应接收线程邮箱句柄
             BST_IP_EVENT_STRU  *pstEvent       TCP/IP事件类型
 输出参数  : 无
 返 回 值  : BST_IP_ERR_T
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_ApiSendTcpIpEvent(
    BST_VOID           *pstRcver,
    BST_VOID           *pstEvent )
{
    BST_IP_EVENT_STRU                  *pstNetEvent;
    BST_ERR_ENUM_UINT8                  enSndResult;

    if ( BST_NULL_PTR == pstEvent )
    {
        return 0;
    }
    if ( BST_NULL_PTR == pstRcver )
    {
        pstRcver                        = BST_SRV_GetSysMsgHandle();
    }

    pstNetEvent                         = ( BST_IP_EVENT_STRU  *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF ( BST_IP_EVENT_STRU ) );
    if ( BST_NULL_PTR == pstNetEvent )
    {
        return 0;
    }

    BST_OS_MEMCPY ( pstNetEvent, pstEvent, BST_OS_SIZEOF ( BST_IP_EVENT_STRU ) );

    pstNetEvent->enId                   = BST_SRV_TCPIP_EVENT;
    pstNetEvent->pucData                = BST_NULL_PTR;
    pstNetEvent->ulLength               = 0;
    enSndResult                         = BST_OS_SendMail(
                                          (BST_OS_MBX_T *)pstRcver,
                                                          pstNetEvent );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return BST_OS_SIZEOF(BST_IP_EVENT_STRU);
    }
    else
    {
        BST_OS_FREE( pstNetEvent );
        return 0;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_ApiSendDsppEvent
 功能描述  : 接收DSPP处理命令
 输入参数  : 
             BST_UINT32             ulMsgId,            DSPP事件ID
             BST_DSPP_HEAD_STRU    *const pstDsppHead,  解析DSPP头信息
             BST_OS_MBX_T          *pstRcvHandle        对应接收线程邮箱句柄

 输出参数  : 无
 返 回 值  : BST_UINT32 实际事件发送字节数
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_ApiSendDsppEvent(
    BST_UINT32             ulMsgId,
    BST_UINT32             ulApVer,
    BST_UINT32             const ulBufLen,
    BST_VOID              *const pstHeadInfo,
    BST_VOID              *pstRcvHandle )
{
    BST_DSPP_EVT_STRU                  *pstEvent;
    BST_UINT8                          *pstHeadCopy;
    BST_ERR_ENUM_UINT8                  enSndResult;

    if ( BST_NULL_PTR == pstHeadInfo )
    {
        return 0;
    }
    if ( BST_NULL_PTR == pstRcvHandle )
    {
        return 0;
    }
    pstEvent                            = ( BST_DSPP_EVT_STRU *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF ( BST_DSPP_EVT_STRU ) );
    if ( BST_NULL_PTR == pstEvent )
    {
        return 0;
    }
    /*
     * 根据DSPP协议版本来确定使用内存分配方法 
     */
    if ( BST_DSPP_VER_C == ulApVer )
    {
        pstHeadCopy                         = ( BST_UINT8 *)pstHeadInfo;
    }
    else
    {
        pstHeadCopy                         = ( BST_UINT8 *)BST_OS_MALLOC( ulBufLen );
        if ( BST_NULL_PTR == pstHeadCopy )
        {
            BST_OS_FREE( pstEvent );
            return 0;
        }
        /*pstHeadInfo指向的是一个临时变量*/
        BST_OS_MEMCPY ( pstHeadCopy, pstHeadInfo, ulBufLen );
    }

    pstEvent->enId                      = BST_SRV_DSPP_EVENT;
    pstEvent->ulMsgId                   = ulMsgId;
    pstEvent->pucData                   = pstHeadCopy;
    pstEvent->ulLength                  = ulBufLen;
    pstEvent->ulAPVer                   = ulApVer;
    enSndResult                         = BST_OS_SendMail( (BST_OS_MBX_T *)pstRcvHandle, pstEvent );
    BST_DBG_LOG1( "CPC_PACKET_DROP BST_OS_SendMail Result", enSndResult );
    if( BST_NO_ERROR_MSG == enSndResult )
    {
        return ulBufLen;
    }
    else
    {
        BST_OS_FREE( pstEvent->pucData );
        BST_OS_FREE( pstEvent );
        return 0;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_EvtProcRxAcom
 功能描述  : 处理AP数据接口（主线程处理）
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_EvtProcRxAcom( BST_EVT_HEAD_STRU *pvInData )
{
    BST_DSPP_CTrsDlVa      *pcTrslayer;
    BST_ACOM_EVT_STRU      *pstEvtData;

    pstEvtData              = ( BST_ACOM_EVT_STRU * )pvInData;
    pcTrslayer              = BST_DSPP_CTrsDlVa::GetInstance();
    if ( BST_NULL_PTR == pcTrslayer )
    {
        return;
    }
    pcTrslayer->RxApi( pstEvtData->pucData, (BST_UINT16)pstEvtData->ulLength );
    pstEvtData->pucData     = BST_NULL_PTR;
    pstEvtData->ulLength    = 0;
}

/*****************************************************************************
 函 数 名  : BST_SRV_EvtProcRcvAs
 功能描述  : 处理AS事件（主线程/应用均有处理）
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_EvtProcRcvAs( BST_EVT_HEAD_STRU *pvInData )
{
    BST_AS_EVT_STRU        *pstEvtData;
    BST_SRV_CAsEvt         *pcAsMng;
    pcAsMng                 = BST_SRV_CAsEvt::GetInstance();
    pstEvtData              = ( BST_AS_EVT_STRU * )pvInData;

    pcAsMng->Forward( ( BST_SRV_CAsRcver *)pstEvtData->pcRcver,
                                           pstEvtData->enMsgId,
                                           pstEvtData->ulLength,
                               (BST_VOID *)pstEvtData->pucData );

}

/*****************************************************************************
 函 数 名  : BST_SRV_EvtProcExpired
 功能描述  : 处理定时器超时事件（主线程/应用均有处理，除IP线程）
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_EvtProcExpired( BST_EVT_HEAD_STRU *pvInData )
{
    BST_OS_TIMER_STRU                  *pstTimer;
    BST_TIMER_EVT_STRU                 *pstTimerEvt;
    BST_OS_TIMERID_T                    ulId;

    pstTimerEvt                         = (BST_TIMER_EVT_STRU *)pvInData;
    if( BST_OS_SIZEOF(ulId) != pstTimerEvt->ulLength )
    {
        return;
    }
    BST_OS_MEMCPY( &ulId, pstTimerEvt->pucData, BST_OS_SIZEOF(ulId) );

    pstTimer                            = BST_OS_TimerSrch( ulId );
    if( BST_NULL_PTR == pstTimer )
    {
        return;
    }
    if( BST_OS_TIMER_CB_CLASS == pstTimer->enCbMode )
    {
        if( BST_NULL_PTR == pstTimer->unCallBack.pc )
        {
            return;
        }
        pstTimer->unCallBack.pc->TimerExpired( pstTimer->ulId , pstTimer->pvPara );
    }
    else if( BST_OS_TIMER_CB_FUN == pstTimer->enCbMode )
    {
        if( BST_NULL_PTR == pstTimer->unCallBack.pf )
        {
            return;
        }
        pstTimer->unCallBack.pf( pstTimer->ulId , pstTimer->pvPara );
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_EvtProcLwipExpired
 功能描述  : 处理定时器超时事件（IP线程）
 输入参数  : tcpip_msg *pstLwipMs       LWIP格式事件信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_EvtProcLwipExpired( BST_VOID *pstLwipMsg )
{
    BST_OS_TIMER_STRU                  *pstTimer;
    if( BST_NULL_PTR == pstLwipMsg )
    {
        return;
    }
    pstTimer                            = BST_OS_TimerSrch(
                                          ( ( struct tcpip_msg *)pstLwipMsg )->msg.bst_tmo.id);
    if( BST_NULL_PTR == pstTimer )
    {
        BST_OS_FREE( pstLwipMsg );
        return;
    }
    if( BST_OS_TIMER_CB_CLASS == pstTimer->enCbMode )
    {
        if( BST_NULL_PTR == pstTimer->unCallBack.pc )
        {
            BST_OS_FREE( pstLwipMsg );
            return;
        }
        pstTimer->unCallBack.pc->TimerExpired( pstTimer->ulId , pstTimer->pvPara );
    }
    else if( BST_OS_TIMER_CB_FUN == pstTimer->enCbMode )
    {
        if( BST_NULL_PTR == pstTimer->unCallBack.pf )
        {
            BST_OS_FREE( pstLwipMsg );
            return;
        }
        pstTimer->unCallBack.pf( pstTimer->ulId , pstTimer->pvPara );
    }
    BST_OS_FREE( pstLwipMsg );
}
/*****************************************************************************
 函 数 名  : BST_SRV_EvtProcLwipAsEvent
 功能描述  : 处理定时器超时事件（IP线程）
 输入参数  : tcpip_msg *pstLwipMs       LWIP格式事件信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年5月14日
      作    者   : z00220931
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_EvtProcLwipAsEvent( BST_VOID *pstLwipMsg )
{
    BST_AS_EVT_STRU         stEvtData;
    BST_SRV_CAsEvt         *pcAsMng;
    pcAsMng                 = BST_SRV_CAsEvt::GetInstance();
    stEvtData               = ( (struct tcpip_msg *)pstLwipMsg )->msg.bst_asevent.stAsEvent;
    if ( BST_NULL_PTR == pcAsMng )
    {
        BST_OS_FREE( stEvtData.pucData );
        BST_OS_FREE( pstLwipMsg );
        return;
    }
    pcAsMng->Forward( ( BST_SRV_CAsRcver *)stEvtData.pcRcver,
                                           stEvtData.enMsgId,
                                           stEvtData.ulLength,
                               (BST_VOID *)stEvtData.pucData );
    BST_OS_FREE( stEvtData.pucData );
    BST_OS_FREE( pstLwipMsg );
}

/*****************************************************************************
 函 数 名  : BST_SRV_EvtProcStoT
 功能描述  : 处理Schd到Task的消息
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_EvtProcStoT( BST_EVT_HEAD_STRU *pstEvent )
{
    BST_PTASK_EVT_STRU         *pstPtskEvent;
    BST_CORE_CPTask            *pPtackIns;
    BST_OS_MBX_T               *pstMsgHandle;
    BST_DBG_LOG("BST_SRV_EvtProcStoT");


    pstPtskEvent                = ( BST_PTASK_EVT_STRU *)pstEvent;
    if( BST_NULL_PTR == pstPtskEvent )
    {
        return;
    }
    /**
     检查任务是否存在，避免任务删除后的错误操作
    */
    pPtackIns                   = ( BST_CORE_CPTask* )pstPtskEvent->pucData;

    if( BST_NULL_PTR == pPtackIns )
    {
        BST_DBG_LOG("pPtackIns is null");
        return;
    }
    
    pstMsgHandle                = BST_SRV_GetTaskMsgHandle
                                ( pPtackIns->m_usProcId, pPtackIns->m_usTaskId );
    if( BST_NULL_PTR == pstMsgHandle )
    {
    
        BST_DBG_LOG("pstMsgHandle is null");
        return;
    }
    
    BST_DBG_LOG1("pstPtskEvent->usMsgId:%d",pstPtskEvent->usMsgId);

    switch( pstPtskEvent->usMsgId )
    {
         /*schd通知task 执行周期任务*/        
        case BST_SRV_S2T_EXE_COMAND:
            pPtackIns->onExecute();
        break;

         /*schd通知task socket被异常关闭了*/  
        case BST_SRV_S2T_ERR_CLOSED:
            pPtackIns->onCycleError();
        break;

         /*schd通知task 周期被更新*/          
        case BST_SRV_S2T_CYC_UPDATE:
            pPtackIns->onUpdateCycle( pstPtskEvent->usContent );
        break;

        default:
        break;
    }
    pstPtskEvent->pucData       = BST_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : BST_SRV_EvtProcTtoS
 功能描述  : 处理Task到Schd的消息
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_EvtProcTtoS( BST_EVT_HEAD_STRU *pstEvent )
{
    BST_CTaskSchdler           *pcSchdler;
    BST_PTASK_EVT_STRU         *pstPtskEvent;

    pcSchdler                   = BST_CTaskSchdler::GetInstance();
    pstPtskEvent                = ( BST_PTASK_EVT_STRU *)pstEvent;

    if( BST_NULL_PTR == pstPtskEvent )
    {
        BST_RLS_LOG("BST_SRV_EvtProcTtoS pstPtskEvent is null");
        return;
    }

    if( BST_NULL_PTR == pcSchdler )
    {
        BST_RLS_LOG("BST_SRV_EvtProcTtoS pcSchdler is null");
        return;
    }

    if( BST_NULL_PTR == pstPtskEvent->pucData )
    {
        BST_RLS_LOG("BST_SRV_EvtProcTtoS pstPtskEvent->pucData is null");
        return;
    }

    switch( pstPtskEvent->usMsgId )
    {
         /*task通知schd 新任务创建并附着*/    
        case BST_SRV_T2S_TSK_ATTACH:
            pcSchdler->Attach( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

         /*task通知schd 任务去附着*/          
        case BST_SRV_T2S_TSK_DETACH:
            pcSchdler->Detach( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

         /*task通知schd 知会当前任务执行结果*/
        case BST_SRV_T2S_ACK_RESULT:
            pcSchdler->AckSendResult
                    ( (BST_CORE_CPTask *) pstPtskEvent->pucData, pstPtskEvent->usContent );
        break;

         /*task通知schd 任务被停止(仅探测器)*/
        case BST_SRV_T2S_RUN_STOPED:
            pcSchdler->TaskStoped( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

         /*task通知schd 任务恢复(仅探测器)*/  
        case BST_SRV_T2S_RUN_RESUME:
            pcSchdler->TaskStarted( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

         /*task通知schd 定义探测器任务ID*/    
        case BST_SRV_T2S_DEF_DETCET:
            pcSchdler->DefineDetector( (BST_CORE_CPTask *) pstPtskEvent->pucData );
        break;

        default:
        break;
    }
    pstPtskEvent->pucData       = BST_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : BST_SRV_EvtProcDsppCmd
 功能描述  : 线程接收处理DSPP相关事务
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_EvtProcDsppCmd( BST_EVT_HEAD_STRU *pstEvent )
{
    BST_DSPP_CAppDlVa          *pcApalayer;
    BST_DSPP_CAppDlVc          *pcApclayer;
    BST_DSPP_EVT_STRU          *pstDsppEvt;
    BST_DSPP_HEAD_STRU         *pstDsppHeadInfo;

    pstDsppEvt                  = ( BST_DSPP_EVT_STRU  *)pstEvent;
    if ( BST_NULL_PTR == pstDsppEvt )
    {
        return;
    }

    BST_DBG_LOG1( "CPC_PACKET_DROP BST_SRV_EvtProcDsppCmd Vesion", pstDsppEvt->ulAPVer );
    if( BST_DSPP_VER_C == pstDsppEvt->ulAPVer)
    {
        pcApclayer              = BST_DSPP_CAppDlVc::GetInstance();
        if ( BST_NULL_PTR == pcApclayer )
        {
            return;
        }
        pcApclayer->ProcAction( ( BST_SRV_CHNL_HEAD_STRU * )pstDsppEvt->pucData );
        /**
         * To avoid the thread free this data
         */
        pstDsppEvt->pucData     = BST_NULL_PTR;
    }
    else
    {
        pstDsppHeadInfo         = ( BST_DSPP_HEAD_STRU *)pstDsppEvt->pucData;
        if ( BST_NULL_PTR == pstDsppHeadInfo )
        {
            return;
        }
        pcApalayer              = BST_DSPP_CAppDlVa::GetInstance();
        if ( BST_NULL_PTR == pcApalayer )
        {
            return;
        }
        pcApalayer->ProcAction( ( BST_DSPP_HEAD_STRU *const )pstDsppHeadInfo,
                                pstDsppHeadInfo->stCpVerA.usOfstAddr,
                                pstDsppHeadInfo->stCpVerA.usObjtAddr );
   }
}

/*****************************************************************************
 函 数 名  : BST_SRV_EvtProcTCPIP
 功能描述  : 处理TCP/IP相关异步提醒事件（应用线程处理）
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_EvtProcTCPIP( BST_EVT_HEAD_STRU *pstEvent )
{
    BST_IP_EVENT_STRU          *pstNetEvt;

    pstNetEvt                   = ( BST_IP_EVENT_STRU  *)pstEvent;
    if( BST_NULL_PTR == pstEvent )
    {
        return;
    }
    switch ( pstNetEvt->ulMsgId )
    {
        case BST_IP_EVENT_RECV:
            BST_IP_ReceivedCB( pstNetEvt->lFd );
            break;

        case BST_IP_EVENT_CONNECTED:
            BST_IP_TcpConnectedCB( pstNetEvt->lFd );
            break;

        case BST_IP_EVENT_ERR:
            BST_IP_TcpErrorCB( pstNetEvt->lFd, pstNetEvt->lErrMsg );
            break;

        case BST_IP_EVENT_OVERFLOW:
            BST_IP_TcpOverFlowCB( pstNetEvt->lFd );
            break;

        case BST_IP_EVENT_ACKED:
            BST_IP_TcpAckedCB( pstNetEvt->lFd, pstNetEvt->ulMinNumber, pstNetEvt->ulMaxNumber );
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_ProcAppEvent
 功能描述  : 处理应用事件总入口
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_ProcAppEvent( BST_EVT_HEAD_STRU *pstEvent )
{
    switch( pstEvent->enId )
    {
        case BST_SRV_AS_EVENT:
            BST_SRV_EvtProcRcvAs( pstEvent );
            break;

        case BST_SRV_TIMER_EVENT:
            BST_SRV_EvtProcExpired( pstEvent );
            break;

        case BST_SRV_TCPIP_EVENT:
            BST_SRV_EvtProcTCPIP ( pstEvent );
            break;

        case BST_SRV_DSPP_EVENT:
            BST_SRV_EvtProcDsppCmd( pstEvent );
            break;

        case BST_SRV_PTASK_EVENT:
            BST_SRV_EvtProcStoT( pstEvent );
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : BST_SRV_ProcAppEvent
 功能描述  : 处理系统事件（含应用）总入口
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_ProcSysEvent( BST_EVT_HEAD_STRU *pstEvent )
{
    switch( pstEvent->enId )
    {
        case BST_SRV_ACOM_EVENT:
            BST_SRV_EvtProcRxAcom( pstEvent );
            break;

        case BST_SRV_AS_EVENT:
            BST_SRV_EvtProcRcvAs( pstEvent );
            break;

        case BST_SRV_TIMER_EVENT:
            BST_SRV_EvtProcExpired( pstEvent );
            break;

        case BST_SRV_TCPIP_EVENT:
            BST_SRV_EvtProcTCPIP ( pstEvent );
            break;

        case BST_SRV_DSPP_EVENT:
            BST_SRV_EvtProcDsppCmd( pstEvent );
            break;

        case BST_SRV_PTASK_EVENT:
            BST_SRV_EvtProcTtoS( pstEvent );
            break;

        default:
            break;
    }
}


/*****************************************************************************
 函 数 名  : BST_SRV_ProcChnlCtrEvent
 功能描述  : 处理信道消息入口
 输入参数  : BST_EVT_HEAD_STRU *pvInData    事件内容信息结构
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年1月14日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_ProcChnlCtrEvent( BST_EVT_HEAD_STRU *pstEvent )
{
    switch( pstEvent->enId )
    {
        case BST_SRV_AS_EVENT:
            BST_SRV_EvtProcRcvAs( pstEvent );
            break;

        case BST_SRV_TIMER_EVENT:
            BST_SRV_EvtProcExpired( pstEvent );
            break;

        case BST_SRV_TCPIP_EVENT:
            BST_SRV_EvtProcTCPIP ( pstEvent );
            break;

        case BST_SRV_DSPP_EVENT:
            BST_SRV_EvtProcDsppCmd( pstEvent );
            break;

        default:
            break;
    }
}

