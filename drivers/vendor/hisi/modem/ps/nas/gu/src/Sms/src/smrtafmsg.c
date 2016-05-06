/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SmrTafMsg.c
  Description  : 和上层消息的交互过程
  Function List:
               1.  SMS_RcvMnDataReq
               2.  SMS_RcvMnSmmaReq
               3.  SMS_RcvMnReportReq
               4.  SMS_SendMnDataReq
               5.  SMS_SendMnReportReq
  History:
      1.   张志勇      2004.03.09   新规作成
      2.   Date         : 2007-04-06
           Author       : h44270
           Modification : 问题单号:A32D10113
      3.   Date         : 2007-08-20
           Author       : z40661
           Modification : 问题单号:A32D12705
      4.   日    期     : 2008年6月5日
           作    者     : fuyingjun id:62575
           修改内容     : 注册状态在MN层的更新不正确，SMS的TAF层不能进入正常驻留状态,问题单号:AT2D03632
      5.   日    期   : 2009年3月23日
           作    者   : f62575
           修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
*******************************************************************************/

#include "smsinclude.h"
#include "NasGmmInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



VOS_UINT8 g_ucCurSendDomain;
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SMR_TAFMSG_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/
#define    SMS_RP_MR_FILL      0xff

/*lint -save -e958 */

/*******************************************************************************
  Module:   SMS_RcvMnDataReq
  Function: 收到SMRL_DATA_REQ原语的处理
  Input:    VOS_VOID        * pRcvMsg       收到的消息
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇   2004.03.09   新规作成
      2. Date         : 2007-04-06
         Author       : h44270
         Modification : 问题单号:A32D10113
      3. Date         :2008-02-22
         Author       :根据优化修改,SMS到TAF直接直接通过发送消息来实现
      5.日    期   : 2012年06月01日
        作    者   : f62575
        修改内容   : DTS2012052904375，解决搜网过程中接收到SMS的EST_REQ没有回复REL_IND问题
      6.日    期   : 2012年8月31日
        作    者   : z00161729
        修改内容   : DCM定制需求和遗留问题修改
      7.日    期   : 2013年07月11日
        作    者   : l00198894
        修改内容   : V9R1 STK升级项目
*******************************************************************************/

VOS_VOID SMS_RcvMnDataReq (
    const SMT_SMR_DATA_STRU             *pstData
)
{
    VOS_UINT8   aucTmpData[255];
    VOS_UINT8   ucSendDomain;

    ucSendDomain = pstData->aucData[0];
    switch (g_SmrEnt.SmrMo.ucState)
    {
    case SMR_IDLE:
        if (0 == pstData->ulDataLen)
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMS_RcvMnDataReq: invalid message,discard." );
            break;
        }

        /*注意: pstData->ulDataLen记录不包含aucData[0](发送域)的数据长度*/
        SMS_Memset( aucTmpData,0,255);
        aucTmpData[0] = (VOS_UINT8)pstData->ulDataLen;
        SMS_Memcpy(aucTmpData + 1,&pstData->aucData[1],pstData->ulDataLen);
        /*lint -e961*/
        g_SmrEnt.SmrMo.ucMr = ++ g_ucSmsMR;                                     /* 记录RP-MR                                   */
        /*lint +e961*/
        aucTmpData[2] = g_SmrEnt.SmrMo.ucMr;

#if (FEATURE_ON == FEATURE_LTE)
        if ((NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
         && (SMS_SEND_DOMAIN_PS != ucSendDomain))
        {
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            SMS_SendMnReportReq(SMR_SMT_ERROR_NO_SERVICE, VOS_NULL_PTR, 0);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMS_RcvMnDataReq: LTE not support CS SMS." );
            return;
        }
#endif

        SMC_SmrApiEstReq(ucSendDomain, aucTmpData, pstData->ulDataLen + 1);     /* 向SMC发送MNSMS_EST_REQ原语               */
        SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMS_RcvMnDataReq: g_SmcCsEnt.SmcMo.ucState.", g_SmcCsEnt.SmcMo.ucState);
        SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMS_RcvMnDataReq: g_SmcPsEnt.SmcMo.ucState.", g_SmcPsEnt.SmcMo.ucState);

        /* 启动定时器TR1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMS_RcvMnDataReq: TimerStart: TR1M" );
        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR1M ) )
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMS_RcvMnDataReq: TimerStart: TR1M Failed" );
            return;
        }

        g_SmrEnt.SmrMo.ucState                  = SMR_WAIT_FOR_RP_ACK;          /* 状态迁移到SMR_WAIT_FOR_RP_ACK            */

        NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_SENT,
                        &g_SmrEnt.SmrMo.ucMr, sizeof(g_SmrEnt.SmrMo.ucMr));
        break;
    default:

        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        SMS_SendMnReportReq(SMR_SMT_ERROR_STATE_NOT_COMPATIBLE, VOS_NULL_PTR, 0);
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

        SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMS_RcvMnDataReq: invalid message,discard." );
        break;
    }
}

/*******************************************************************************
  Module:   SMS_RcvMnCpAckReq
  Function: 收到SMT_SMR_CP_ACK_REQ原语的处理
  Input:    SMT_SMR_DATA_STRU             *pstData       收到的消息
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇   2004.03.09   新规作成
      2. Date         : 2007-04-06
         Author       : h44270
         Modification : 问题单号:A32D10113
      3. Date         :2008-02-22
         Author       :根据优化修改,SMS到TAF直接直接通过发送消息来实现
*******************************************************************************/

VOS_VOID SMS_RcvMnCpAckReq (
    const SMT_SMR_DATA_STRU             *pstData
)
{
    SMC_MoBufferCpAckSend();
    return;
}

/*******************************************************************************
  Module:   SMS_RcvMnSmmaReq
  Function: 收到SMRL_MEM_AVAIL_REQ原语的处理
  Input:    VOS_VOID        * pRcvMsg       收到的消息
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇   2004.03.09   新规作成
      2.日    期   : 2012年8月13日
        作    者   : z00161729
        修改内容   : DCM定制需求和遗留问题修改
*******************************************************************************/
VOS_VOID SMS_RcvMnSmmaReq(
    const SMT_SMR_SMMA_STRU             *pstData
                              )
{
    VOS_UINT8    aucTmpSmc[3];

    g_ucCurSendDomain = pstData->ucSendDomain;
    switch( g_SmrEnt.SmrMo.ucState )
    {
    case SMR_IDLE:
        if (SMT_SMR_ABORT_FLG_NO_EXIST == ((SMT_SMR_SMMA_STRU*) pstData)->ucAbortFlg )
        {                                                                       /* 原语中不含ABORT参数                      */
            g_SmrEnt.SmrMo.ucMemAvailFlg    = SMS_TRUE;                         /* 置标志位为1，表明为NOTIFICATION过程      */
            g_SmrEnt.SmrMo.ucRetransFlg     = SMR_RETRANS_PERMIT;
            /*lint -e961*/
            g_SmrEnt.SmrMo.ucMr             = ++ g_ucSmsMR;                        /* 记录mr                                   */
            /*lint +e961*/

            aucTmpSmc[0] = 2;                                                      /* 数据的长度                               */

            aucTmpSmc[1] = SMR_MTN_DATA_TYPE_RP_SMMA;                              /* 填写消息类型                             */
            aucTmpSmc[2] = g_ucSmsMR;
            SMC_SmrApiEstReq(pstData->ucSendDomain,aucTmpSmc,3);                                       /* 向SMC发送MNSMS_EST_REQ原语               */

            /* 启动定时器TR1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMS_RcvMnSmmaReq: TimerStart: TR1M" );
            if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR1M ) )
            {
                SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMS_RcvMnSmmaReq: TimerStart: TR1M Failed" );
                return;
            }
            g_SmrEnt.SmrMo.ucState                  = SMR_WAIT_FOR_RP_ACK;      /* 实体状态迁移到SMR_WAIT_FOR_RP_ACK        */
        }
        break;
    case SMR_WAIT_FOR_RETRANS_TIMER:
        if (SMT_SMR_ABORT_FLG_EXIST == ((SMT_SMR_SMMA_STRU*)pstData)->ucAbortFlg)
        {                                                                       /* 含有参数SMS_MEM_NOTIF_ABORT              */
            /* 停止timer TRAM */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMS_RcvMnSmmaReq: TimerStop: TRAM" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TRAM ) )
            {
                return;
            }


            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            SMS_SendMnReportReq(SMR_SMT_ERROR_USER_ABORT, VOS_NULL_PTR, 0);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

            g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;                  /* 清除RETRANS FLAG                         */
            g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;
            /* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
            g_SmrEnt.SmrMo.ucState       = SMR_IDLE;
            /* Added by f62575 for V9R1 STK升级, 2013-6-26, end */
        }
        break;
    default:
        break;
    }
}



/*******************************************************************************
Module:   SMS_RcvMnReportReq
Function: 收到SMRL_REPORT_REQ原语的处理
Input:    VOS_VOID        * pstData       收到的消息
Output:   VOS_VOID
NOTE:
Return:   VOS_VOID
History:
1.   张志勇   2004.03.10   新规作成
2.   Date         : 2006-04-26
     Author       : 郜东东
     Modification : 修改了无法连续接收多条短信的问题,问题单号:A32D02986
*******************************************************************************/
VOS_VOID SMS_RcvMnReportReq(
    const SMT_SMR_DATA_STRU             *pstData
)
{
    VOS_UINT8 ucLen = 0;                                                            /* 定义数据长度                             */
    VOS_UINT8 aucTmpData[255];

    if (SMR_WAIT_TO_SND_RP_ACK == g_SmrEnt.SmrMt.ucState)
    {
        /* 停止timer TR2M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMS_RcvMnReportReq: TimerStop: TR2M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR2M ) )
        {
            return;
        }

        ucLen = (VOS_UINT8)pstData->ulDataLen ;

        if ( ucLen <= 2 )
        {                                                                       /* 没有User Data 的 rp_ack                  */
            aucTmpData[0] = 2;                                                     /* 消息长度                                 */
            aucTmpData[1] = SMR_MTN_DATA_TYPE_RP_ACK;                              /* 消息类型                                 */
            aucTmpData[2] = g_SmrEnt.SmrMt.ucMr;                                   /* MR                                       */
        }
        else
        {
            SMS_Memset(aucTmpData,0,ucLen + 1);                                    /* 初始化清零                               */

            aucTmpData[0] = ucLen ;                                                /* 消息长度                                 */

            SMS_Memcpy( aucTmpData + 1,
                        pstData->aucData,
                        ucLen );
            aucTmpData[2] = g_SmrEnt.SmrMt.ucMr;                                /* MR                                       */
        }
        SMC_SmrApiDataReq( aucTmpData, (VOS_UINT16)(ucLen + 1) );               /* 向SMC发送MNSMS_DATA_REQ                  */

        SMC_SmrApiRelReq( SMR_SMC_REL_CAUSE_NORMAL,SMS_TRUE );                  /* 发送MNSMS_REL_REQ                        */

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMS_RcvMnReportReq:NORMAL:SMS state = SMR_IDLE");
        g_SmrEnt.SmrMt.ucState = SMR_IDLE;                                      /* 实体状态迁移到空闲                       */
    }
}

/*******************************************************************************
  Module:   SMS_SendMnDataReq
  Function: 做成并发送SMRL_DATA_IND原语
  Input:    VOS_UINT8       *pucData        数据首地址
            VOS_UINT32        ulLen          数据长度
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇   2004.03.10   新规作成
      2.日    期   : 2013年6月4日
        作    者   : s00217060
        修改内容   : for V9R1_SVLTE:接收短信时，把接收域是CS还是PS域带上去，MSG要用
                        修改函数名，原函数名为SMS_SendMnDataReq
*******************************************************************************/
VOS_VOID SMS_SendMnEstInd(
    VOS_UINT8                           *pucData,                               /* 数据首地址                               */
    VOS_UINT32                          ulSendLen,                               /* 数据长度                                 */
    VOS_UINT8                           ucRcvDomain                             /* 接收域是PS域还是CS域 */
)
{
    VOS_UINT32                          ulLen;
    SMR_SMT_EST_IND_STRU               *pstSendMsg ;

    ulLen = (ulSendLen + sizeof(SMR_SMT_EST_IND_STRU)) - 4;
    pstSendMsg = (SMR_SMT_EST_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,ulLen);
    if (VOS_NULL_PTR == pstSendMsg)
    {
        SMS_LOG(PS_LOG_LEVEL_WARNING,"SMS_SendMnDataReq:ERROR: VOS_AllocMsg fails");
        return ;
    }
    pstSendMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid = WUEPS_PID_SMS;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverPid = WUEPS_PID_TAF;
    pstSendMsg->ulMsgName = SMR_SMT_DATA_IND;
    pstSendMsg->ulDataLen = ulSendLen;
    pstSendMsg->ucRcvDomain = ucRcvDomain;
    PS_MEM_CPY(pstSendMsg->aucData,pucData,ulSendLen);

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendMsg ) )
    {
        SMS_LOG( PS_LOG_LEVEL_WARNING,"SMS_SendMnDataReq:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
    }
}

/*******************************************************************************
Module:   SMS_SendMnReportReq
Function: 做成并发送SMRL_REPORT_IND原语
Input:    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode   错误码
          VOS_UINT8                          *pucData       RPDU
          VOS_UINT32                          ulSendLen     RPDU长度
Output:   VOS_VOID
NOTE:
Return:   VOS_VOID
History:
1.   张志勇   2004.03.10   新规作成
2.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级
*******************************************************************************/
VOS_VOID SMS_SendMnReportReq(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulSendLen
)
{
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    SMR_SMT_MO_REPORT_STRU             *pstSendMsg = VOS_NULL_PTR;

    pstSendMsg = (SMR_SMT_MO_REPORT_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                        sizeof(SMR_SMT_MO_REPORT_STRU));
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    if (VOS_NULL_PTR == pstSendMsg)
    {
        SMS_LOG(PS_LOG_LEVEL_WARNING,"SMS_SendMnReportReq: VOS_AllocMsg fails");
        return ;
    }

    /* 填写消息头部信息 */
    pstSendMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid     = WUEPS_PID_SMS;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstSendMsg->ulMsgName       = SMR_SMT_REPORT_IND;

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    pstSendMsg->enErrorCode     = enErrorCode;

    /* 填写RPDU，接收到RP-ACK或RP-ERROR时有效 */
    PS_MEM_SET(&pstSendMsg->stRpduData, 0, sizeof(pstSendMsg->stRpduData));
    if (VOS_NULL_PTR != pucData)
    {
        pstSendMsg->stRpduData.ulDataLen    = ulSendLen;
        PS_MEM_CPY(pstSendMsg->stRpduData.aucData, pucData, ulSendLen);
    }
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendMsg ) )
    {
        SMS_LOG( PS_LOG_LEVEL_WARNING,"SMS_SendMnReportReq:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
    }

}

/*******************************************************************************
Module:   SMS_SendMnMtErrInd
Function: 做成并发送SMRL_TR2M_TIMEOUT_IND原语
Input:    ucRpStatus:Rp的状态,成功或失败
          ucRpCause:Rp的原因值
Output:   VOS_VOID
NOTE:
Return:   VOS_VOID
History:
1.   z40661   2008.03.19   新规作成
2.日    期   : 2013年07月11日
  作    者   : f62575
  修改内容   : V9R1 STK升级项目

*******************************************************************************/
VOS_VOID SMS_SendMnMtErrInd(SMR_SMT_ERROR_ENUM_UINT32 enErrorCode)
{
    SMR_SMT_MT_ERR_STRU                *pstSendMsg = VOS_NULL_PTR;

    pstSendMsg = (SMR_SMT_MT_ERR_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                                     sizeof(SMR_SMT_MT_ERR_STRU));
    if (VOS_NULL_PTR == pstSendMsg)
    {
        SMS_LOG(PS_LOG_LEVEL_WARNING,"SMS_SendMnMtErrInd:ERROR: VOS_AllocMsg fails");
        return ;
    }

    pstSendMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid     = WUEPS_PID_SMS;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstSendMsg->ulMsgName       = SMR_SMT_MT_ERR_IND;
    pstSendMsg->enErrorCode     = enErrorCode;

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendMsg ) )
    {
        SMS_LOG(PS_LOG_LEVEL_WARNING,"SMS_SendMnMtErrInd:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
    }
}

VOS_VOID SMS_AttachFlag(
    VOS_UINT8                           ucDomain,
    VOS_UINT8                           ucRegState
)
{
    VOS_UINT8                          ucLen;
    SMT_SMR_DATA_STRU                  *pstSendMsg ;
    VOS_BOOL                            bAttachFlag;
    SMR_SMT_ATTACH_STRU                *pstAttachData;

    ucLen = (sizeof(SMR_SMT_ATTACH_STRU) + sizeof(SMT_SMR_DATA_STRU)) - 4;
    pstSendMsg = (SMT_SMR_DATA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,ucLen);
    if (VOS_NULL_PTR == pstSendMsg)
    {
        SMS_LOG(PS_LOG_LEVEL_WARNING,"SMS_AttachFlag:ERROR: VOS_AllocMsg fails");
        return ;
    }

    pstSendMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid = WUEPS_PID_SMS;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverPid = WUEPS_PID_TAF;
    pstSendMsg->ulMsgName = SMR_SMT_ATTACH_IND;
    pstAttachData = (SMR_SMT_ATTACH_STRU *)pstSendMsg->aucData;
    pstAttachData->ucDomain = ucDomain;
    if (SMS_TRUE == ucRegState)
    {
        bAttachFlag = VOS_TRUE;
    }
    else
    {
        bAttachFlag = VOS_FALSE;
    }
    pstAttachData->bAttachFlag = bAttachFlag;

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendMsg ) )
    {
        SMS_LOG( PS_LOG_LEVEL_WARNING,"SMS_AttachFlag:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
    }
}

/*******************************************************************************
Module:   SMS_SendMnMoCpAckSent
Function: 做成并发送SMRL_CP_ACK_SENT_IND原语
Input:    VOS_VOID
Output:   VOS_VOID
NOTE:
Return:   VOS_VOID
History:
  1.日    期   : 2009年3月5日
    作    者   : f62575
    修改内容   : 新生成函数
*******************************************************************************/
VOS_VOID SMS_SendMnMoLinkCloseInd(VOS_VOID)
{
    VOS_UINT32                          ulLen;
    SMT_SMR_DATA_STRU                  *pstSendMsg ;

    ulLen = sizeof(SMT_SMR_DATA_STRU);
    pstSendMsg = (SMT_SMR_DATA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,ulLen);
    if (VOS_NULL_PTR == pstSendMsg)
    {
        SMS_LOG(PS_LOG_LEVEL_WARNING,"SMS_SendMnReportReq:ERROR: VOS_AllocMsg fails");
        return ;
    }

    pstSendMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid = WUEPS_PID_SMS;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverPid = WUEPS_PID_TAF;
    pstSendMsg->ulMsgName = SMR_SMT_LINK_CLOSE_IND;
    pstSendMsg->ulDataLen = 0;

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendMsg ) )
    {
        SMS_LOG( PS_LOG_LEVEL_WARNING,"SMS_SendMnReportReq:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
    }

}

VOS_VOID NAS_SMS_ProcMnMsg(
    const VOS_VOID                      *pRcvMsg
)
{
    switch (((SMT_SMR_DATA_STRU*)pRcvMsg)->ulMsgName)
    {
        case SMT_SMR_DATA_REQ:
            SMS_RcvMnDataReq((SMT_SMR_DATA_STRU*)pRcvMsg);
            break;
        case SMT_SMR_CP_ACK_REQ:
            SMS_RcvMnCpAckReq((SMT_SMR_DATA_STRU*)pRcvMsg);
            break;
        case SMT_SMR_REPORT_REQ:
            SMS_RcvMnReportReq((SMT_SMR_DATA_STRU*)pRcvMsg);
            break;
        case SMT_SMR_SMMA_REQ:
            SMS_RcvMnSmmaReq((SMT_SMR_SMMA_STRU*)pRcvMsg);
            break;

        default:
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:NAS_SMS_ProcMnMsg: Invalid Msg Type" );
            break;
    }
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

