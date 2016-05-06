/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsSndMm.c
  Description  : 发送MM消息的处理
  Function List:
      1.  Ss_SndMmMsg                 SS向MM发送消息
      2.  Ss_SndMmssEstReq            SS通知MM建立MM连接
      3.  Ss_SndMmssDataReq           向MM发送数据
      4.  Ss_SndMmssRelReq            SS用该原语要求MM释放MM连接
  History:
      1.  张志勇 2004.03.09   新版作成
      2.日    期   : 2007年06月04日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D11456
*******************************************************************************/

#include "SsInclude.h"
#include "NasOmInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_SNDMM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_SS_ReportM2NOtaMsg
 功能描述  : 对trace中勾取SS的空口消息
 输入参数  : pNasMsg - 消息内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    作    者   : l00198894
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_SS_ReportM2NOtaMsg(
    SS_MSG_STRU                         *pNasMsg
)
{
    NAS_OTA_MSG_ID_ENUM_UINT16          enNasOtaMsyId;
    VOS_UINT8                           ucMsgType;

    enNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    /* Message Type字段在消息中的所在位置 */
    ucMsgType = pNasMsg->aucSsMsg[1];

    SS_NORM_LOG1("NAS_SS_ReportM2NOtaMsg: [MsgType]", pNasMsg->aucSsMsg[1]);

    /* 把NAS上行空口消息ID和上报给OM的消息ID对应，并通过OM进行勾取显示 */
    switch(ucMsgType)
    {
        case SS_MSG_REGISTER:
            enNasOtaMsyId = NAS_OTA_MSG_SS_REGISTER_UP;
            break;
        case SS_MSG_FACILITY:
            enNasOtaMsyId = NAS_OTA_MSG_SS_FACILITY_UP;
            break;
        case SS_MSG_RELCMPL:
            enNasOtaMsyId = NAS_OTA_MSG_SS_RELCMPL_UP;
            break;
        default:
            break;
    }

    if (NAS_OTA_MSG_ID_BUTT == enNasOtaMsyId)
    {
        SS_WARN_LOG1("NAS_SS_ReportN2MOtaMsg: invalid msg type!", enNasOtaMsyId);
        /* 不属于SS模块的空口消息，不在trace中显示 */
        return;
    }

    /*上报空口消息给OM*/
    NAS_SendAirMsgToOM(WUEPS_PID_SS,
                       enNasOtaMsyId,
                       NAS_OTA_DIRECTION_UP,
                       pNasMsg->ulSsMsgSize + 4,
                       (VOS_UINT8*)pNasMsg);

    return;
}

/***********************************************************************
*  MODULE   : Ss_SndMmssEstReq
*  FUNCTION : SS通知MM建立MM连接
*  INPUT    : VOS_UINT8     ucTi         对应的MM连接的TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
************************************************************************/

VOS_VOID Ss_SndMmssEstReq(
    VOS_UINT8                           ucTi,                                   /* 对应的MM连接的TI                         */
    VOS_UINT8                           ucRedialFlg
)
{
    VOS_VOID    *pMsg;                                                              /* 定义消息中数据                           */

    pMsg = PS_ALLOC_MSG(WUEPS_PID_SS, sizeof(MMSS_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pMsg )
    {
        return;
    }


    (( MMSS_EST_REQ_STRU *)pMsg )->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    (( MMSS_EST_REQ_STRU *)pMsg )->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;       /* 设置消息组名                             */
    (( MMSS_EST_REQ_STRU *)pMsg )->MsgHeader.ulMsgName = MMSS_EST_REQ;          /* 设置消息名称                             */
    (( MMSS_EST_REQ_STRU *)pMsg )->ulTi = ucTi;                                 /* 设置对应的MM连接的TI                     */
    (( MMSS_EST_REQ_STRU *)pMsg )->ucRedialFlg  = ucRedialFlg;                  /* 重拨标志 */
    (( MMSS_EST_REQ_STRU *)pMsg )->aucReserve[0]= 0;
    (( MMSS_EST_REQ_STRU *)pMsg )->aucReserve[1]= 0;
    (( MMSS_EST_REQ_STRU *)pMsg )->aucReserve[2]= 0;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SS, pMsg))                                               /* 向MM发送                                 */
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssEstReq():WARNING:SEND MSG FIAL");
    }
}

/***********************************************************************
*  MODULE   : Ss_SndMmssDataReq
*  FUNCTION : 向MM发送数据
*  INPUT    : VOS_UINT8     ucTi            对应的MM连接的TI
*             VOS_UINT8     *pucSsMsg       待发送数据（动态内存，内部释放）
*             VOS_UINT32     ulSsMsgSize     消息长度
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇   04-03-09  新版作成
*     2.  张志勇   05-01-14  删除对指针pucSsMsg的释放
      3.日    期   : 2007年06月04日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D11456
	  4.日    期   : 2012年12月11日
	    作    者   : l00167671
	    修改内容   : DTS2012121802573, TQE清理
      5.日    期   : 2012年12月29日
        作    者   : l00198894
        修改内容   : DTS2012122702627: 增加SS空口消息可维可测
************************************************************************/
VOS_VOID Ss_SndMmssDataReq(
                       VOS_UINT8 ucTi,                                              /* 对应的MM连接的TI                         */
                       VOS_UINT8 *pucSsMsg,                                         /* 待发送数据                               */
                       VOS_UINT32 ulSsMsgSize                                        /* 消息长度                                 */
                       )
{
    VOS_VOID            *pMsg;                                                  /* 定义消息中数据                           */
    MMSS_DATA_REQ_STRU  *pSndMsg;
    VOS_UINT32   ulMsgLen;                                                           /* 定义消息长度变量                         */

    ulMsgLen = (sizeof( MMSS_DATA_REQ_STRU ) + ulSsMsgSize) - 4;                  /* 设置消息长度                             */
    if ( ulMsgLen < sizeof( MMSS_DATA_REQ_STRU ) )
    {
        ulMsgLen = sizeof( MMSS_DATA_REQ_STRU );
    }

    pMsg = PS_ALLOC_MSG(WUEPS_PID_SS, ulMsgLen - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pMsg )
    {
        return;
    }
    pSndMsg = (MMSS_DATA_REQ_STRU *)pMsg;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;                       /* 设置消息组名                             */
    pSndMsg->MsgHeader.ulMsgName = MMSS_DATA_REQ;                               /* 设置消息名称                             */
    pSndMsg->ulTi = ucTi;                                                       /* 设置对应的MM连接的TI                     */
    pSndMsg->SsMsg.ulSsMsgSize = ulSsMsgSize;                                   /* 设置消息长度                             */
    Ss_MemCpy(pSndMsg->SsMsg.aucSsMsg,
        pucSsMsg, ulSsMsgSize );                                                /* 设置消息中的数据                         */

    /* 通过OM勾取SS空口消息 */
    NAS_SS_ReportM2NOtaMsg(&pSndMsg->SsMsg);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SS, pSndMsg))                           /* 向MM发送                                 */
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssRelReq():WARNING:SEND MSG FIAL");
    }
}

/***********************************************************************
*  MODULE   : Ss_SndMmssRelReq
*  FUNCTION : SS用该原语要求MM释放MM连接
*  INPUT    : VOS_UINT8     ucTi        对应的MM连接的TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
*     1.  张志勇 04-03-09  新版作成
      2.日    期   : 2007年06月04日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D11456
	  3.日    期   : 2012年12月11日
	    作    者   : l00167671
	    修改内容   : DTS2012121802573, TQE清理
************************************************************************/

VOS_VOID Ss_SndMmssRelReq(
                      VOS_UINT8 ucTi                                                /* 对应的MM连接的TI                         */
                      )
{
    VOS_VOID    *pMsg;                                                              /* 定义消息中数据                           */

    pMsg = PS_ALLOC_MSG(WUEPS_PID_SS, sizeof(MMSS_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pMsg )
    {
        NAS_MSG_FAIL();
        return;
    }
    /*A32D11456==>*/
    (( MMSS_REL_REQ_STRU *)pMsg )->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    (( MMSS_REL_REQ_STRU *)pMsg )->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;       /* 设置消息组名                             */
    /*<==A32D11456*/
    (( MMSS_REL_REQ_STRU *)pMsg )->MsgHeader.ulMsgName = MMSS_REL_REQ;          /* 设置消息名称                             */
    (( MMSS_REL_REQ_STRU *)pMsg )->ulTi = ucTi;                                 /* 设置对应的MM连接的TI                     */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SS, pMsg))                                               /* 向MM发送                                 */
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssRelReq():WARNING:SEND MSG FIAL");
    }                                                        /* 向MM发送                                 */
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_SS_SndMmBeginSessionNotify
 功能描述  : 向MM发送begin session notify
 输入参数  : enSessionType - session type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月16日
    作    者   : z00161729
    修改内容   : DSDS III新增

*****************************************************************************/
VOS_VOID NAS_SS_SndMmBeginSessionNotify(
    MMSS_SESSION_TYPE_ENUM_UINT8        enSessionType
)
{
    VOS_UINT32                          ulRet;
    MMSS_BEGIN_SESSION_NOTIFY_STRU     *pstBeginSessionNotify = VOS_NULL_PTR;

    /* 申请内存  */
    pstBeginSessionNotify = (MMSS_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SS,
                                         sizeof(MMSS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstBeginSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SS, "NAS_SS_SndMmBeginSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SS;
    pstBeginSessionNotify->stMsgHeader.ulLength         = sizeof(MMSS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBeginSessionNotify->stMsgHeader.ulMsgName        = MMSS_BEGIN_SESSION_NOTIFY;
    pstBeginSessionNotify->enSessionType                = enSessionType;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_SS, pstBeginSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "NAS_SS_SndMmBeginSessionNotify():WARNING:SEND FAIL");
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_SS_SndMmEndSessionNotify
 功能描述  : 向MM发送end session notify
 输入参数  : enSessionType - session type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月16日
    作    者   : z00161729
    修改内容   : DSDS III新增

*****************************************************************************/
VOS_VOID NAS_SS_SndMmEndSessionNotify(
    MMSS_SESSION_TYPE_ENUM_UINT8        enSessionType
)
{
    VOS_UINT32                          ulRet;
    MMSS_END_SESSION_NOTIFY_STRU       *pstEndSessionNotify = VOS_NULL_PTR;

    /* 申请内存  */
    pstEndSessionNotify = (MMSS_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SS,
                                         sizeof(MMSS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstEndSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SS, "NAS_SS_SndMmEndSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SS;
    pstEndSessionNotify->stMsgHeader.ulLength         = sizeof(MMSS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstEndSessionNotify->stMsgHeader.ulMsgName        = MMSS_END_SESSION_NOTIFY;
    pstEndSessionNotify->enSessionType    = enSessionType;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_SS, pstEndSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "NAS_SS_SndMmEndSessionNotify():WARNING:SEND FAIL");
        return;
    }

    return;
}

#endif


/*****************************************************************************
 函 数 名  : Ss_SndMmssSsStatusNty
 功能描述  : 向MM发送end session notify
 输入参数  : enSessionType - session type
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Ss_SndMmssSsStatusNty(
    MMSS_STATUS_ENUM_UINT8              enSsStatus
)
{
    VOS_UINT32                          ulRet;
    MMSS_STATUS_NTY_STRU               *pstSsStatusNty = VOS_NULL_PTR;

    /* 申请内存  */
    pstSsStatusNty = (MMSS_STATUS_NTY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SS,
                                         sizeof(MMSS_STATUS_NTY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstSsStatusNty )
    {
        NAS_ERROR_LOG(WUEPS_PID_SS, "Ss_SndMmssSsStatusNty():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstSsStatusNty + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSS_STATUS_NTY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSsStatusNty->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstSsStatusNty->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstSsStatusNty->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstSsStatusNty->stMsgHeader.ulSenderPid      = WUEPS_PID_SS;
    pstSsStatusNty->stMsgHeader.ulLength         = sizeof(MMSS_STATUS_NTY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSsStatusNty->stMsgHeader.ulMsgName        = MMSS_SS_STATUS_NOTIFY;
    pstSsStatusNty->enSsStatus                   = enSsStatus;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_SS, pstSsStatusNty );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssSsStatusNty():WARNING:SEND FAIL");
        return;
    }

    return;
}

/***********************************************************************
*  MODULE   : Ss_SndMmssAbortReq
*  FUNCTION : SS用该原语要求MM释放MM连接
*  INPUT    : VOS_UINT8     ucTi        对应的MM连接的TI
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 无
*  HISTORY  :
      1.日    期   : 2008年05月09日
        作    者   : 胡文
        修改内容   : 问题单号:AT2D03224
	  2.日    期   : 2012年12月11日
	    作    者   : l00167671
	    修改内容   : DTS2012121802573, TQE清理
************************************************************************/
VOS_VOID Ss_SndMmssAbortReq(
                      VOS_UINT8 ucTi                                                /* 对应的MM连接的TI                         */
                      )
{
    VOS_VOID    *pMsg;                                                              /* 定义消息中数据                           */

    pMsg = PS_ALLOC_MSG(WUEPS_PID_SS, sizeof(MMSS_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pMsg )
    {
        NAS_MSG_FAIL();
        return;
    }
    (( MMSS_ABORT_REQ_STRU *)pMsg )->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    (( MMSS_ABORT_REQ_STRU *)pMsg )->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;   /* 设置消息组名                             */
    (( MMSS_ABORT_REQ_STRU *)pMsg )->MsgHeader.ulMsgName = MMSS_ABORT_REQ;          /* 设置消息名称                             */
    (( MMSS_ABORT_REQ_STRU *)pMsg )->ulTransactionId = ucTi;                        /* 设置对应的MM连接的TI                     */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SS, pMsg))                                               /* 向MM发送                                 */
    {
        NAS_WARNING_LOG(WUEPS_PID_SS, "Ss_SndMmssAbortReq():WARNING:SEND MSG FIAL");
    }
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

