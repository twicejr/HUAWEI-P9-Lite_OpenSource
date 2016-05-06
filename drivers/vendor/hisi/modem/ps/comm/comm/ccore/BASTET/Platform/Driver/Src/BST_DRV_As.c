/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司
 ******************************************************************************
  文 件 名   : BST_DRV_As.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年7月3日
  最近修改   :
  功能描述   : 实现接入层相关处理驱动接口
  函数列表   :

  修改历史   :
  1.日    期   : 2014年07月3日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_PAL_As.h"
#include "BST_DRV_As.h"
#include "BST_OS_Memory.h"
#include "BST_PAL_Net.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DRV_AS_C
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/
BST_VOID    BST_DRV_BlockDataService(BST_UINT8 bitFlag);
BST_VOID    BST_DRV_UnBlockDataService(BST_UINT8 bitFlag);

/*****************************************************************************
  3 函数声明
*****************************************************************************/
BST_UINT32          BST_SRV_RcvAsEvent(
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData );

BST_ERR_ENUM_UINT8  BST_DRV_AsInit( BST_VOID *pvArg );

BST_VOID            BST_DRV_AsEventCallBack(
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData );

BST_ERR_ENUM_UINT8  BST_DRV_AsIoCtrl(
    BST_UINT32              ulCmd,
    BST_VOID               *pvData );

BST_VOID    BST_DRV_AsCsEvtProc( BST_BOOL bConflict );
BST_VOID    BST_DRV_AsPsSrvProc( BST_BOOL bInservice );
BST_VOID    BST_DRV_AsProcRrcState(BST_UINT32 ulRrcState);
BST_VOID    BST_DRV_AsProcApTxData( BST_VOID );


extern BST_VOID     BST_DRV_LsItf_AsRatMode(
    BST_UINT32              ulRatMode );

extern BST_VOID     BST_DRV_LsItf_AsRrcState(
    BST_UINT32              ulRrcState );

extern BST_VOID     BST_DRV_LsItf_AsBlockedState(
    BST_UINT32              ulIsBlocked );

extern BST_VOID     BST_DRV_LsItf_AsRxInd( BST_VOID );

/******************************************************************************
   4 私有定义
******************************************************************************/
BST_UINT32      g_ulBstDrvRrcState      = BST_RRC_STATE_BUTT;
BST_BOOL        g_BstReportFlag         = BST_TRUE;
BST_UINT8       g_ucDsBlockFlg          = BST_AS_BLOCKED_BY_NO_SERVICE;
BST_UINT32      g_BstDrvLayerRatMode    = BST_AS_RAT_NONE;

BST_DRV_CHNLMODE_ENUM_UINT32  g_ulBstDrvChnlMode = BST_DRV_CHNLMODE_INIT;

/******************************************************************************
   5 全局变量定义
******************************************************************************/
BST_DRV_STRU    g_BstDrvAsHandle =
{
    BST_DRV_AsInit,
    BST_NULL_PTR,
    BST_NULL_PTR,
    BST_DRV_AsIoCtrl,
    BST_FALSE
};

/******************************************************************************
   6 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : BST_DRV_AsInit
 功能描述  : BST_VOID *pvArg  NO USE
 输入参数  : 接入层驱动初始化
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_AsInit( BST_VOID *pvArg )
{
    BST_ERR_ENUM_UINT8                  ucRtnVal;
    if( BST_DRV_IsDeviceInited(BST_DRV_AsGetDvcHandle()) )
    {
        return BST_NO_ERROR_MSG;
    }
    ucRtnVal                            = BST_PAL_AsApiInitial( BST_DRV_AsEventCallBack );
    if( BST_NO_ERROR_MSG == ucRtnVal )
    {
        g_BstDrvAsHandle.ulIsInited     = BST_TRUE;
    }
    g_ucDsBlockFlg                      = BST_AS_BLOCKED_BY_NO_SERVICE;
    g_ulBstDrvRrcState                  = BST_RRC_STATE_BUTT;
    g_ulBstDrvChnlMode                  = BST_DRV_CHNLMODE_INIT;
    BST_DRV_AsSetReportFlag( BST_TRUE );
    return ucRtnVal;
}

/*****************************************************************************
 函 数 名  : BST_DRV_AsEventCallBack
 功能描述  : 就收接入层状态等信息的驱动
 输入参数  : BST_UINT32 ulLength     长度
             BST_UINT8 *pucData      RRC状态及制式参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_AsEventCallBack(
    BST_AS_EVT_ENUM_UINT32          enAsEvent,
    BST_UINT32                      ulLength,
    BST_VOID                       *pvData )
{
    BST_UINT32                      ulRrcState;
    switch( enAsEvent )
    {
        case BST_AS_EVT_L3_RRC_STATE:
            ulRrcState              = *( (BST_UINT32 *)pvData );
            if( ulRrcState == g_ulBstDrvRrcState )
            {
                return;
            }
            BST_DRV_AsProcRrcState( ulRrcState );
            BST_DRV_LsItf_AsRrcState( ulRrcState );
            break;

        case BST_AS_EVT_L3_SERVICE_STATE:
            BST_DRV_AsPsSrvProc(
                ((BST_SRV_UTRAN_SRV_STATE_STRU *)pvData)->bPsService);
            break;

        case BST_AS_EVT_L3_RAT_STATE:
            g_BstDrvLayerRatMode    = *( (BST_UINT32 *)pvData );
            BST_DRV_LsItf_AsRatMode( g_BstDrvLayerRatMode );
            break;

        case BST_AS_EVT_L3_CS_EVENT_STATE:
            BST_DRV_AsCsEvtProc( *(BST_BOOL *)pvData );
            break;

        case BST_AS_EVT_L3_AP_RX_RCV_IND:
            BST_DRV_LsItf_AsRxInd();
            break;

        case BST_AS_EVT_L3_AP_TX_SEND_IND:
            BST_DRV_AsProcApTxData();
            break;
        default:
            break;
    }
    BST_SRV_RcvAsEvent( enAsEvent, ulLength, pvData );
}

/*****************************************************************************
 函 数 名  : BST_DRV_AsIoCtrl
 功能描述  : 接入层的控制命令处理
 输入参数  : BST_UINT32 ulCmd  控制命令
             BST_VOID *pvData  NO USE
 输出参数  : 无
 返 回 值  : 返回出错信息
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_AsIoCtrl( BST_UINT32 ulCmd, BST_VOID *pvData )
{
    BST_ERR_ENUM_UINT8                  ucRtnVal = BST_NO_ERROR_MSG;
    switch( ulCmd )
    {
        case BST_DRV_CMD_GET_AS_STATE:
            BST_ASSERT_NULL_RTN( pvData, BST_ERR_INVALID_PTR );
           *( (BST_UINT8 *)pvData ) = g_ucDsBlockFlg;
            ucRtnVal                = BST_NO_ERROR_MSG;
            break;

        case BST_DRV_CMD_SET_REPORT_FLAG:
            BST_ASSERT_NULL_RTN( pvData, BST_ERR_INVALID_PTR );
            BST_DRV_AsSetReportFlag( *( (BST_UINT8*)pvData ) );
            ucRtnVal                = BST_NO_ERROR_MSG;
            break;

        case BST_DRV_CMD_GET_REPORT_FLAG:
            BST_ASSERT_NULL_RTN( pvData, BST_ERR_INVALID_PTR );
           *( (BST_BOOL *)pvData )  = g_BstReportFlag;
            ucRtnVal                = BST_NO_ERROR_MSG;
            break;

        case BST_DRV_CMD_GET_RAT_MODE:
            BST_ASSERT_NULL_RTN( pvData, BST_ERR_INVALID_PTR );
           *( (BST_UINT32*)pvData ) = g_BstDrvLayerRatMode;
            ucRtnVal                = BST_NO_ERROR_MSG;
            break;

        case BST_DRV_CMD_RELEASE_RRC:
            if ( !BST_DRV_AsIsRrcExisted() )
            {
                return BST_NO_ERROR_MSG;
            }
            ucRtnVal                = BST_PAL_AsApiReleaseRrcConn();
            break;

        case BST_DRV_CMD_SET_TX_ENABLE:
            BST_PAL_NetApiSetRxMsgEnable( *( (BST_UINT32 *)pvData ) );
            break;

        case BST_DRV_CMD_SET_RX_ENABLE:
            BST_PAL_NetApiSetTxMsgEnable( *( (BST_UINT32 *)pvData ) );
            break;

        default:
            break;
    }
    return ucRtnVal;
}



/*****************************************************************************
 函 数 名  :BST_DRV_AsSetReportFlag
 功能描述  :设置消息是否需要上报给AP
 输入参数  :bReportFlg  BST_TRUE  需要上报， BST_FALSE不需要上报
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年11月10日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID BST_DRV_AsSetReportFlag(BST_UINT8 ucReportFlg)
{
    BST_MODEM_ID_ENUM_UINT32            enPsModemId;

    enPsModemId                         = BST_PAL_AsApiGetPsModemId();

    if(g_BstReportFlag != ucReportFlg)
    {
        g_BstReportFlag = ucReportFlg;
        BST_RLS_LOG1( "Set Modem Report AP Flag: %d", g_BstReportFlag );
        BST_PAL_AsApiSndRptFlag(enPsModemId,ucReportFlg);
    }
}

/*****************************************************************************
 函 数 名  : BST_DRV_AsPsSrvProc
 功能描述  : PS域服务状态发生变化的处理函数
 输入参数  : BST_MODEM_ID_ENUM_UINT32  ulModemId  modem的ID号
             BST_DRV_AS_CS_EVENT_STRU *pstEvent   事件
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_AsCsEvtProc( BST_BOOL bConflict )
{
    if( BST_TRUE == bConflict )
    {
        BST_DRV_BlockDataService(BST_AS_BLOCKED_BY_CS_CONFLICT);
    }
    else
    {
        BST_DRV_UnBlockDataService(BST_AS_BLOCKED_BY_CS_CONFLICT);
    }
}
/*****************************************************************************
 函 数 名  : BST_DRV_AsPsSrvProc
 功能描述  : PS域服务状态发生变化的处理函数
 输入参数  : BST_MODEM_ID_ENUM_UINT32  ulModemId  modem的ID号
             BST_DRV_AS_CS_EVENT_STRU *pstEvent   事件
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_AsPsSrvProc( BST_BOOL bInservice )
{
    if( BST_FALSE == bInservice )
    {
        BST_DRV_BlockDataService(BST_AS_BLOCKED_BY_NO_SERVICE);
    }
    else
    {
        BST_DRV_UnBlockDataService(BST_AS_BLOCKED_BY_NO_SERVICE);
    }

}
/*****************************************************************************
 函 数 名  : BST_DRV_AsNetStateProc
 功能描述  : Net Device状态发生变化的处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年08月24日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_AsNetStateProc( BST_BOOL bNetDeviceUp )
{
    if( BST_FALSE == bNetDeviceUp )
    {
        BST_DRV_BlockDataService(BST_AS_BLOCKED_BY_NET_STATE);
    }
    else
    {
        BST_DRV_UnBlockDataService(BST_AS_BLOCKED_BY_NET_STATE);
    }
}
/*****************************************************************************
 函 数 名  : BST_DRV_BlockDataService
 功能描述  : block状态发生变化的处理函数
 输入参数  : BST_UINT8  bitFlag  新的block标志位 
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年03月13日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID BST_DRV_BlockDataService(BST_UINT8 bitFlag)
{
    BST_UINT8                           ucOldBlockFlag;
    BST_UINT32                          ulIsBlocked;

    ucOldBlockFlag                      = g_ucDsBlockFlg;
    g_ucDsBlockFlg                     |= bitFlag;
    BST_DBG_LOG2("BST_DRV_BlockDataService,old:, new:", ucOldBlockFlag, g_ucDsBlockFlg);
    if((BST_AS_UNBLOCKED == ucOldBlockFlag) && (BST_AS_UNBLOCKED != g_ucDsBlockFlg))
    {
        ulIsBlocked                    = BST_TRUE;
        BST_DRV_LsItf_AsBlockedState( ulIsBlocked );
    }
}

/*****************************************************************************
 函 数 名  : BST_DRV_UnBlockDataService
 功能描述  : unblock状态发生变化的处理函数
 输入参数  : BST_UINT8  bitFlag  新的unblock标志位 
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年03月13日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID BST_DRV_UnBlockDataService(BST_UINT8 bitFlag)
{
    BST_UINT8                           ucOldBlockFlag;
    BST_UINT32                          ulIsBlocked;

    ucOldBlockFlag                      = g_ucDsBlockFlg;

    g_ucDsBlockFlg &= (~bitFlag);
    BST_DBG_LOG2("BST_DRV_UnBlockDataService,old:,new:", ucOldBlockFlag, g_ucDsBlockFlg);

    if((BST_AS_UNBLOCKED != ucOldBlockFlag) && (BST_AS_UNBLOCKED == g_ucDsBlockFlg))
    {
        ulIsBlocked                    = BST_FALSE;
        BST_DRV_LsItf_AsBlockedState( ulIsBlocked );
    }
}

/*****************************************************************************
 函 数 名  : BST_DRV_AsSetChnlMode
 功能描述  : 设置As通道模式
 输入参数  : enChnlMode: 期望设置的模式
                           bSetByOrder: 是否需要根据信道模式的优先级进行判断
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月23日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_AsSetChnlMode( BST_DRV_CHNLMODE_ENUM_UINT32 enChnlMode, BST_BOOL bForceSet)
{
    BST_ERR_ENUM_UINT8                  enResult;


    if( enChnlMode ==  g_ulBstDrvChnlMode )
    {
        return;
    }
    
    /*如果收到高优先级数据，则进入高优先级信道模式
          如果收到低优先级数据，如果当前条件允许进入低功耗模式，则进入低功耗模式
                                                                       否则保持当前模式不变
          如果收到其他数据，如果当前是低功耗模式，则退出低功耗模式，进入NORMAL模式
          否则保持状态不变
       */


    if( ( enChnlMode <  g_ulBstDrvChnlMode ) && ( BST_FALSE == bForceSet ))
    {
        BST_DBG_LOG2("curr mode(:%d) high than new mode(:%d)",g_ulBstDrvChnlMode,enChnlMode);
        return;
    }
    
    /*仅在3G的PCH态允许设置低功耗模式*/
    if(( enChnlMode == BST_DRV_CHNLMODE_LPM) && ( BST_RRC_STATE_PCH != g_ulBstDrvRrcState ))
    {
        BST_DBG_LOG1("curr rrc state(%d) not pch state,not allowed set lpm mode",g_ulBstDrvRrcState);
        return;
    }

    enResult = BST_PAL_AsApiSetChnlMode( enChnlMode );
    if( BST_NO_ERROR_MSG != enResult )
    {
        BST_DBG_LOG1("BST_DRV_AsSetChnlMode failed:%d",enResult);
        return;
    }
    g_ulBstDrvChnlMode                  = enChnlMode;
}



/*****************************************************************************
 函 数 名  : BST_DRV_AsProcRrcState
 功能描述  : 
 输入参数  : 
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年03月13日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID BST_DRV_AsProcRrcState(BST_UINT32 ulRrcState)
{
    if( ulRrcState == g_ulBstDrvRrcState )
    {
        return;
    }

    /*如果状态进入DCH态，则停止低功耗信道控制*/
    if( ulRrcState == BST_RRC_STATE_DCH )
    {
        BST_DBG_LOG("BST_DRV_AsProcRrcState,BST_RRC_STATE_DCH");
        BST_DRV_AsSetChnlMode(BST_DRV_CHNLMODE_NORMAL, BST_FALSE);
    }
    else if ( ( BST_AS_IsRrcConnected( g_ulBstDrvRrcState ) )
        && ( !BST_AS_IsRrcConnected( ulRrcState ) ) )
    {
        /*如果状态进入非连接态态，需要将信道模式设置为init状态*/
        BST_DRV_AsSetChnlMode( BST_DRV_CHNLMODE_INIT, BST_TRUE );
    }
    else
    {
        //其他状态暂不需要处理
    }

    g_ulBstDrvRrcState   = ulRrcState;

}


/*****************************************************************************
 函 数 名  : BST_DRV_AsProcTxData
 功能描述  : 处理Data 数据收发消息
 输入参数  : 
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年03月13日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID BST_DRV_AsProcApTxData( BST_VOID )
{
    //BST_DBG_LOG("BST_DRV_AsProcRrcState,BST_DRV_AsProcTxData");
    //BST_DRV_AsSetChnlMode( BST_DRV_CHNLMODE_NORMAL, BST_FALSE );
}


/*****************************************************************************
 函 数 名  : BST_DRV_AsProcBstTxData
 功能描述  : 处理BST 内部数据收发指示事件
 输入参数  : ucDataType 收到的数据类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月23日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_AsProcBstTxData( BST_UINT8 ucDataType  )
{
    switch(ucDataType)
    {
        case BST_IP_HPRI_DATA:
            BST_DRV_AsSetChnlMode( BST_DRV_CHNLMODE_HPR, BST_FALSE );
            break;
        case BST_IP_LPWR_DATA:
            BST_DRV_AsSetChnlMode( BST_DRV_CHNLMODE_LPM, BST_FALSE );
            break;
        case BST_IP_BSTT_DATA:
            BST_DBG_LOG("BST_DRV_AsProcBstTxData,BST_IP_BSTT_DATA");
            BST_DRV_AsSetChnlMode( BST_DRV_CHNLMODE_NORMAL, BST_FALSE );
            break;
        default:
            break;
    }
}


/*****************************************************************************
 函 数 名  : BST_DRV_AsProcHpriDataFinish
 功能描述  : 处理BST 内部数据收发指示事件
 输入参数  : ucDataType 收到的数据类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月23日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_AsProcHpriDataFinish( BST_VOID )
{
    if(BST_DRV_CHNLMODE_HPR != g_ulBstDrvChnlMode)
    {
        BST_DBG_LOG("curr not in HPR CHNL");
        return;
    }
    BST_DBG_LOG1("BST_DRV_AsProcHpriDataFinish:%d",g_ulBstDrvChnlMode);
    BST_DRV_AsSetChnlMode( BST_DRV_CHNLMODE_NORMAL, BST_TRUE );
}



/*****************************************************************************
 函 数 名  : BST_DRV_AsMapRatToEnum
 功能描述  : rat mode类型转化
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年07月18日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_DRV_AS_RAT_ENUM_UINT32 BST_DRV_AsMapRatToEnum(
    BST_AS_RAT_MODE_UINT32  ulRatMode )
{
    switch( ulRatMode )
    {
        case BST_AS_RAT_CDMA:
            return BST_DRV_AS_RAT_INVALID_ENUM;

        case BST_AS_RAT_EVDO:
            return BST_DRV_AS_RAT_INVALID_ENUM;

        case BST_AS_RAT_GPRS:
            return BST_DRV_AS_RAT_GSM_ENUM;

        case BST_AS_RAT_WCDMA:
            return BST_DRV_AS_RAT_WCDMA_ENUM;

        case BST_AS_RAT_TDSCDMA:
            return BST_DRV_AS_RAT_TDSCDMA_ENUM;

        case BST_AS_RAT_LTE:
            return BST_DRV_AS_RAT_LTE_ENUM;

        default :
            return BST_DRV_AS_RAT_INVALID_ENUM;

    }
}


