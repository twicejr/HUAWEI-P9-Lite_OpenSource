/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SYS_MsgProc.c
  版 本 号   : 初稿
  作    者   : z00128442
  生成日期   : 2014年11月10日
  最近修改   :
  功能描述   : 处理不同模块之间消息分发
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月10日
    作    者   : z00128442
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
#include "BST_SYS_MsgProc.h"
#include "BST_DRV_As.h"
#include "BST_OS_Memory.h"
#include "MmaBastetInterface.h"
#include "BastetRabmInterface.h"
#include "BastetRrcInterface.h"
#include "BST_PAL_As.h"
#include "BastetWrrcinterface.h"
#include "BastetTrrcInterface.h"
#include "BastetWMacInterface.h"
#include "BastetWRlcInterface.h"
#include "BastetSnInterface.h"
#include "BST_DRV_LinkSta.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_MSGPROC_C
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/
#define BST_CONVERT_ENUM_TO_BOOL_TYPE(value)  ((value==PS_TRUE)? BST_TRUE : BST_FALSE)
/******************************************************************************
   3 私有定义
******************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/
extern BST_UINT32 BST_DRV_LsItf_InWriteNetStrength(
                  const BST_UINT32        ulModemId,
                  const BST_UINT32        ulRatMode,
                  const BST_UINT32        ulCellId,
                  const BST_INT16         sRscp,
                  const BST_INT16         sEcio );

extern BST_VOID BST_PAL_LsItf_ExtRegInquireFunc(
                  const BST_UINT32    ulPid, 
                  BST_VOID           *pfGetTrsFun,
                  BST_VOID           *pfGetQueFun);
/******************************************************************************
 5 全局变量定义
******************************************************************************/

/******************************************************************************
  6 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : BST_MSG_ProcMmaRecv
 功能描述  : 处理MMA模块发送过来的消息
 输入参数  : pstMsg,   消息结构体

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年11月02日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_MSG_ProcMmaRecv( MsgBlock *pstMsg, BST_MODEM_ID_ENUM_UINT32 enModemId )
{
    BST_UINT32                          ulAppData;
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;

    if ( BST_NULL_PTR == pstMsg )
    {
        BST_DBG_LOG( "BST_MSG_ProcMmaRecv, msg is null ptr");
        return ;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch( pstMsgHeader->ulMsgName )
    {
       case ID_MMA_BASTET_RAT_MODE_IND:
       {
            MMA_BASTET_RAT_MODE_IND_STRU  *pstCurRatMsg = (MMA_BASTET_RAT_MODE_IND_STRU *)pstMsg;
            switch ( pstCurRatMsg->enRatMode )
            {
                case BST_RATMODE_WCDMA:
                    BST_RLS_LOG( "Current Rat is WCDMA" );
                    ulAppData           = BST_AS_RAT_WCDMA;
                    break;

                case BST_RATMODE_LTE:
                    BST_RLS_LOG( "Current Rat is LTE" );
                    ulAppData           = BST_AS_RAT_LTE;
                    break;

                case BST_RATMODE_GSM:
                    BST_RLS_LOG( "Current Rat is GSM(GPRS)" );
                    ulAppData           = BST_AS_RAT_GPRS;
                    break;
                case BST_RATMODE_TDS:
                    BST_RLS_LOG( "Current Rat is TDS" );
                    ulAppData           = BST_AS_RAT_TDSCDMA;
                    break;
                default:
                    ulAppData           = BST_AS_RAT_NONE;
                    break;
            }
            BST_PAL_AsMsgSetRatModeInfo(enModemId,ulAppData);
            break;
       }
       case ID_MMA_BASTET_CS_SERVICE_IND:
       {
            MMA_BASTET_CS_SERVICE_IND_STRU  *pstCsSrvMsg = (MMA_BASTET_CS_SERVICE_IND_STRU *)pstMsg;
            BST_BOOL                         bCSConnected;
            bCSConnected   = BST_CONVERT_ENUM_TO_BOOL_TYPE(pstCsSrvMsg->bCSConnected);
            BST_PAL_AsMsgSetCsUsingInfo(enModemId, bCSConnected);
            break;
       }
       case ID_MMA_BASTET_SERVICE_STATUE_IND:
       {
            MMA_BASTET_SERVICE_STATUS_IND_STRU *pstSrvMsg = (MMA_BASTET_SERVICE_STATUS_IND_STRU *)pstMsg;
            BST_BOOL                            bCsInservice;
            BST_BOOL                            bPsInservice;

            bCsInservice   = BST_CONVERT_ENUM_TO_BOOL_TYPE(pstSrvMsg->bCsInservice);
            bPsInservice   = BST_CONVERT_ENUM_TO_BOOL_TYPE(pstSrvMsg->bPsInservice);

            BST_PAL_AsMsgSetServiceStatus(enModemId, bCsInservice, bPsInservice);
            break;
       }
       default:
           BST_RLS_LOG1( "MMA unexpect event:%d", pstMsgHeader->ulMsgName );
           return;

    }


    return;
}


/*****************************************************************************
 函 数 名  : BST_MSG_ProcWrrcRecv
 功能描述  : 处理WRR模块发送过来的消息
 输入参数  : pstMsg,   消息结构体

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年11月02日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_MSG_ProcWrrcRecv( MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;
    BST_UINT32                          ulRrcState;

    if ( BST_NULL_PTR == pstMsg )
    {
        BST_DBG_LOG( "BST_MSG_ProcWrrcRecv, msg is null ptr");
        return ;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch( pstMsgHeader->ulMsgName )
    {
       case ID_WRRC_BASTET_RRC_STATUS_IND:
       {
            WRRC_BASTET_STATUS_IND_STRU  *pstWrrcMsg = (WRRC_BASTET_STATUS_IND_STRU *)pstMsg;
            if(BST_MODEM_ID_1 != BST_PAL_AsApiGetPsModemId())
            {
                BST_RLS_LOG( "ID_WAS_BASTET_RRC_STATUS, current ps modem not for m0");
                break;
            }

            if(BST_AS_RAT_WCDMA != BST_PAL_AsApiGetModemRat(BST_MODEM_ID_1))
            {
                BST_RLS_LOG( "ID_WAS_BASTET_RRC_STATUS, current rat not wcdma");
                break;
            }
            BST_RLS_LOG1( "BST_MSG_ProcWrrcRecv, enRrcState:%d",pstWrrcMsg->enRrcState);
            if(BASTET_WRRC_STATE_CELL_DCH == pstWrrcMsg->enRrcState)
            {
                ulRrcState              = BST_RRC_STATE_DCH;
            }
            else if(BASTET_WRRC_STATE_CELL_FACH == pstWrrcMsg->enRrcState)
            {
                ulRrcState              = BST_RRC_STATE_FACH;
            }
            else if((BASTET_WRRC_STATE_CELL_PCH == pstWrrcMsg->enRrcState)
                 || (BASTET_WRRC_STATE_URA_PCH == pstWrrcMsg->enRrcState))
            {
                ulRrcState              = BST_RRC_STATE_PCH;
            }
            else if(BASTET_WRRC_STATE_IDLE == pstWrrcMsg->enRrcState)
            {
                ulRrcState              = BST_RRC_STATE_IDLE;
            }
            else
            {
                BST_RLS_LOG( "BST_MSG_ProcTrrcRecv, current rat not wcdma");
                break;
            }
            BST_PalAsEventRcvCb( BST_AS_EVT_L3_RRC_STATE,
                                 ( BST_UINT16 )BST_OS_SIZEOF(ulRrcState),
                                 &ulRrcState);
            break;
       }
       default:
           BST_RLS_LOG1( "Wrr unexpect event:%d", pstMsgHeader->ulMsgName );
           return;

    }
    return;
}



/*****************************************************************************
 函 数 名  : BST_MSG_ProcTrrcRecv
 功能描述  : 处理TRRC模块发送过来的消息
 输入参数  : pstMsg,   消息结构体

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年11月02日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_MSG_ProcTrrcRecv( MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;
    BST_UINT32                          ulRrcState;

    if ( BST_NULL_PTR == pstMsg )
    {
        BST_DBG_LOG( "BST_MSG_ProcTrrcRecv, msg is null ptr");
        return ;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch( pstMsgHeader->ulMsgName )
    {
       case ID_TRRC_BASTET_RRC_STATUS_IND:
       {
            TRRC_BASTET_STATUS_IND_STRU  *pstTrrcMsg = (TRRC_BASTET_STATUS_IND_STRU *)pstMsg;
            if(BST_MODEM_ID_1 != BST_PAL_AsApiGetPsModemId())
            {
                BST_RLS_LOG( "BST_MSG_ProcTrrcRecv, current ps modem not for m0");
                break;
            }

            if(BST_AS_RAT_TDSCDMA != BST_PAL_AsApiGetModemRat(BST_MODEM_ID_1))
            {
                BST_RLS_LOG( "BST_MSG_ProcTrrcRecv, current rat not tds");
                break;
            }
            BST_RLS_LOG1( "BST_MSG_ProcTrrcRecv, enRrcState:%d",pstTrrcMsg->enRrcState);
            if(BASTET_TRRC_STATE_CELL_DCH == pstTrrcMsg->enRrcState)
            {
                ulRrcState              = BST_RRC_STATE_DCH;
            }
            else if(BASTET_TRRC_STATE_CELL_FACH == pstTrrcMsg->enRrcState)
            {
                ulRrcState              = BST_RRC_STATE_FACH;
            }
            else if((BASTET_TRRC_STATE_CELL_PCH == pstTrrcMsg->enRrcState)
                 || (BASTET_TRRC_STATE_URA_PCH == pstTrrcMsg->enRrcState))
            {
                ulRrcState              = BST_RRC_STATE_PCH;
            }
            else if(BASTET_TRRC_STATE_IDLE == pstTrrcMsg->enRrcState)
            {
                ulRrcState              = BST_RRC_STATE_IDLE;
            }
            else
            {
                BST_RLS_LOG( "BST_MSG_ProcTrrcRecv, current rat not tds");
                break;
            }
            BST_PalAsEventRcvCb( BST_AS_EVT_L3_RRC_STATE,
                                 ( BST_UINT16 )BST_OS_SIZEOF(ulRrcState),
                                 &ulRrcState);
            break;
       }

       case ID_TRRC_BASTET_SERVICE_CELL_INFO_IND:
       {
           TRRC_BASTET_SERVICE_CELL_INFO_IND_STRU  *pstSrvCellInfo;

           pstSrvCellInfo               = ( TRRC_BASTET_SERVICE_CELL_INFO_IND_STRU* )pstMsg;

           BST_DRV_LsItf_InWriteNetStrength( BST_MODEM_ID_1,
                                             BST_AS_RAT_TDSCDMA,
                                             pstSrvCellInfo->ulCellId,
                                             pstSrvCellInfo->sRscp,
                                             BST_DRV_INVALID_ECI0 );
           break;
       }

       default:
           BST_RLS_LOG1( "TRRC unexpect event:%d", pstMsgHeader->ulMsgName );
           return;

    }

    return;
}



/*****************************************************************************
 函 数 名  : BST_MSG_ProcLrrcRecv
 功能描述  : 处理LRRC模块发送过来的消息
 输入参数  : pstMsg,   消息结构体

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年11月02日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_MSG_ProcLrrcRecv( MsgBlock *pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;
    BST_UINT32                          ulRrcState;

    if ( BST_NULL_PTR == pstMsg )
    {
        BST_DBG_LOG( "BST_MSG_ProcLrrcRecv, msg is null ptr");
        return ;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch( pstMsgHeader->ulMsgName )
    {
       case ID_LRRC_BASTET_RRC_STATUS_IND:
       {
            BASTET_RRC_LRRC_STATUS_IND_STRU  *pstRrcMsg
                = (BASTET_RRC_LRRC_STATUS_IND_STRU *)pstMsg;
            if(BST_MODEM_ID_1 != BST_PAL_AsApiGetPsModemId())
            {
                BST_RLS_LOG( "BST_MSG_ProcLrrcRecv, current ps modem not for m0");
                break;
            }

            if(BST_AS_RAT_LTE != BST_PAL_AsApiGetModemRat(BST_MODEM_ID_1))
            {
                BST_RLS_LOG( "BST_MSG_ProcLrrcRecv, current rat not lte");
                break;
            }

            BST_RLS_LOG1( "BST_MSG_ProcLrrcRecv, enRrcState:%d",pstRrcMsg->enRrcState);

            if(BASTET_LRRC_STATE_CONNECTED == pstRrcMsg->enRrcState)
            {
                ulRrcState              = BST_RRC_STATE_CONNECTED;
            }
            else
            {
                ulRrcState              = BST_RRC_STATE_IDLE;
            }
            BST_PalAsEventRcvCb( BST_AS_EVT_L3_RRC_STATE,
                                 ( BST_UINT16 )BST_OS_SIZEOF(ulRrcState),
                                 &ulRrcState);
            break;
       }

       case ID_LRRC_BASTET_SERVICE_CELL_INFO_IND:
       {
           LRRC_BASTET_SERVICE_CELL_INFO_IND_STRU  *pstSrvCellInfo;

           pstSrvCellInfo               = ( LRRC_BASTET_SERVICE_CELL_INFO_IND_STRU* )pstMsg;

           BST_DRV_LsItf_InWriteNetStrength( BST_MODEM_ID_1,
                                             BST_AS_RAT_LTE,
                                             pstSrvCellInfo->ulCellId,
                                             pstSrvCellInfo->sRsrp,
                                             pstSrvCellInfo->sRsrq );
           break;
       }

       default:
           BST_RLS_LOG1( "LRRC unexpect event:%d", pstMsgHeader->ulMsgName );
           return;

    }
    return;
}


/*****************************************************************************
 函 数 名  : BST_MSG_ProcWRlcRecv
 功能描述  : 处理WRLC模块发送过来的消息
 输入参数  : pstMsg,   消息结构体

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_MSG_ProcWRlcRecv( MsgBlock *pstMsg )
{
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;

    if ( BST_NULL_PTR == pstMsg )
    {
        BST_DBG_LOG( "BST_MSG_ProcWRlcRecv, msg is null ptr");
        return ;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch( pstMsgHeader->ulMsgName )
    {
       case ID_WRLC_BASTET_TRANS_INQUIRE:
       {
            BST_WRLC_REG_TRS_CB_STRU  *pstRlcMsg
                = (BST_WRLC_REG_TRS_CB_STRU *)pstMsg;

            BST_PAL_LsItf_ExtRegInquireFunc( pstRlcMsg->ulPid, pstRlcMsg->pfSendCb, pstRlcMsg->pfSendQueCb );
            break;
       }
       default:
           BST_RLS_LOG1( "WRLC unexpect event:%d", pstMsgHeader->ulMsgName );
           return;

    }
    return;
}


/*****************************************************************************
 函 数 名  : BST_MSG_ProcGRlcRecv
 功能描述  : 处理GRLC模块发送过来的消息
 输入参数  : pstMsg,   消息结构体

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_MSG_ProcGRlcRecv( MsgBlock *pstMsg )
{
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;

    if ( BST_NULL_PTR == pstMsg )
    {
        BST_DBG_LOG( "BST_MSG_ProcGRlcRecv, msg is null ptr");
        return ;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch( pstMsgHeader->ulMsgName )
    {
       case ID_GRLC_BASTET_TRANS_INQUIRE:
       {
            BST_GRLC_REG_TRS_CB_STRU  *pstRlcMsg
                = (BST_GRLC_REG_TRS_CB_STRU *)pstMsg;

            BST_PAL_LsItf_ExtRegInquireFunc( pstRlcMsg->ulPid, BST_NULL_PTR, pstRlcMsg->pfSendQueCb );
            break;
       }
       default:
           BST_RLS_LOG1( "GRLC unexpect event:%d", pstMsgHeader->ulMsgName );
           return;

    }
    return;
}


/*****************************************************************************
 函 数 名  : BST_MSG_ProcRrrcRealseSend
 功能描述  : 通知Rabm释放3G RRC连接
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年11月10日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID BST_MSG_ProcRrrcRealseSend(BST_VOID)
{
    BASTETRABM_RRC_REL_REQ_STRU         *pstSndMsg;
    VOS_UINT32                           ulRslt;
    VOS_UINT32                           ulReceiverPid;
    BST_MODEM_ID_ENUM_UINT32             enPsModemId;


    enPsModemId                              = BST_PAL_AsApiGetPsModemId();
    if(BST_MODEM_ID_1 == enPsModemId)
    {
        ulReceiverPid = I0_WUEPS_PID_RABM;
    }
    else
    {
        BST_DBG_LOG1("BST_MSG_ProcRrrcRealseSend:ERROR: Wrong modemId:%d",enPsModemId);
        return;
    }

    /* 申请内存  */
    pstSndMsg = (BASTETRABM_RRC_REL_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_BASTET,
                                               sizeof(BASTETRABM_RRC_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        /* 内存申请失败 */
        BST_DBG_LOG("BST_MSG_ProcRrrcRealseSend:ERROR: Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET( (VOS_CHAR*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0x00,
                (sizeof(BASTETRABM_RRC_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写相关参数 */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = ulReceiverPid;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(BASTETRABM_RRC_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_BASTET_RABM_SET_RELEASE_RRC_REQ;

    /* 调用VOS发送原语 */
    ulRslt = PS_SEND_MSG(UEPS_PID_BASTET, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        BST_DBG_LOG("BST_MSG_ProcRrrcRealseSend:ERROR:PS_SEND_MSG ");
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : BST_MSG_ProcLRrcRealseSend
 功能描述  : 通知LRRC释放LTE RRC连接
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年11月10日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_VOID BST_MSG_ProcLRrcRealseSend(BST_VOID)
{
    BASTET_RRC_LTE_TO_IDLE_REQ_STRU     *pstSndMsg;
    VOS_UINT32                           ulRslt;

    /* 申请内存  */
    pstSndMsg = (BASTET_RRC_LTE_TO_IDLE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_BASTET,
                 sizeof(BASTET_RRC_LTE_TO_IDLE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        /* 内存申请失败 */
        BST_DBG_LOG("BST_MSG_ProcRrrcRealseSend:ERROR: Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET((VOS_CHAR*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0x00,
               (sizeof(BASTET_RRC_LTE_TO_IDLE_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写相关参数 */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = PS_PID_ERRC;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(BASTET_RRC_LTE_TO_IDLE_REQ_STRU)
                                             - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_BASTET_LRRC_CON_TO_IDLE_NTF;

    /* 调用VOS发送原语 */
    ulRslt = PS_SEND_MSG(UEPS_PID_BASTET, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        BST_DBG_LOG("BST_MSG_ProcRrrcRealseSend:ERROR:PS_SEND_MSG ");
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : BST_MSG_ProcWChnlInfoSend
 功能描述  : 通知WMAC层数据分级相关的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年11月10日
      作    者   : z00128442
      修改内容   : 新生成函数
*****************************************************************************/

BST_UINT32 BST_MSG_SendWChnlModeInfo( BST_PAL_CHNLMODE_STRU *pStChnlInfo )
{
    BASTET_WMAC_CHNL_MODE_STRU          *pstSndMsg;
    BST_UINT32                           ulRslt;

    if(VOS_NULL_PTR == pStChnlInfo)
    {
        return BST_SEND_FAILED;
    }

    if( pStChnlInfo->enChnlMode >= BST_DRV_CHNLMODE_BUTT )
    {
        return BST_SEND_FAILED;
    }

    /* 申请内存  */
    pstSndMsg = (BASTET_WMAC_CHNL_MODE_STRU *)PS_ALLOC_MSG(UEPS_PID_BASTET,
                 sizeof(BASTET_WMAC_CHNL_MODE_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSndMsg )
    {
        /* 内存申请失败 */
        BST_DBG_LOG("BST_MSG_SendWChnlModeInfo:ERROR: Memory Alloc Error for pstMsg");
        return BST_SEND_FAILED;
    }

    PS_MEM_SET((VOS_CHAR*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0x00,
               (sizeof(BASTET_WMAC_CHNL_MODE_STRU) - VOS_MSG_HEAD_LENGTH));

    /* 填写相关参数 */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MAC;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(BASTET_WMAC_CHNL_MODE_STRU)
                                             - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_BASTET_WMAC_CHNL_MODE;

    if( BST_DRV_CHNLMODE_HPR == pStChnlInfo->enChnlMode )
    {
        pstSndMsg->enChnlMode                = BASTET_WMAC_CHNL_HPR;
    }
    else if( BST_DRV_CHNLMODE_LPM == pStChnlInfo->enChnlMode )
    {
        pstSndMsg->enChnlMode                = BASTET_WMAC_CHNL_LPM;
    }
    else
    {
        pstSndMsg->enChnlMode                = BASTET_WMAC_CHNL_NORMAL;
    }

    pstSndMsg->usLimit                       = pstSndMsg->usLimit;
    pstSndMsg->ucRbId                        = pstSndMsg->ucRbId;

    /* 调用VOS发送原语 */
    ulRslt = PS_SEND_MSG(UEPS_PID_BASTET, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        BST_DBG_LOG("BST_MSG_ProcRrrcRealseSend:ERROR:PS_SEND_MSG ");
        return BST_SEND_FAILED;
    }

    return BST_SEND_SUCCESS;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


