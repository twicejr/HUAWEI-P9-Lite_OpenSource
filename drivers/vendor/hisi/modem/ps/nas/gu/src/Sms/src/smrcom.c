/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SmrCom.c
  Description  : SMR的公共处理
  Function List:
               3.  SMR_MemNotifyRetrans
               5.  SMR_TimerTr1mExpire
               6.  SMR_TimerTr2mExpire
               7.  SMR_TimerTramExpire
               8.  SMR_SmcChk
               9.  SMR_SndRpErrorReq
              10.  SMR_MkSndReportError
              11.
  History:
      1.   张志勇      2004.03.09   新规作成
      2.   Date         : 2007-04-06
           Author       : h44270
           Modification : 问题单号:A32D10113
      3.   Date         : 2007-08-20
           Author       : z40661
           Modification : 问题单号:A32D12705
      4.日    期   : 2009年3月23日
        作    者   : f62575
        修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
*******************************************************************************/
#include "smsinclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SMR_COM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*******************************************************************************
Module:   SMR_MemNotifyRetrans
Function: 根据重传标识进行重传或进入空闲
Input:    VOS_UINT8  ucRelCause           释放标志
                     enErrorType          错误类型
Output:
NOTE:
Return:   VOS_VOID
History:
1.   张志勇   2004.03.10   新规作成
2.日    期   : 2012年8月29日
  作    者   : z00161729
  修改内容   : DCM定制需求和遗留问题修改,增加入参enErrorType
3.日    期   : 2013年07月11日
  作    者   : f62575
  修改内容   : V9R1 STK升级项目
*******************************************************************************/
VOS_VOID SMR_MemNotifyRetrans(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulSendLen
)
{
    if ( SMR_RETRANS_PERMIT != g_SmrEnt.SmrMo.ucRetransFlg )
    {                                                                           /* RETRANS FLAG 置位                        */
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        SMS_SendMnReportReq(enErrorCode, pucData, ulSendLen);
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;                      /* 将RETRANS FLAG置0清除                    */
        g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;                               /* 清除标志位                               */

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_SmcApiDataInd:NORMAL:SMS state = SMR_IDLE");
        g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* 状态迁移到空闲状态                       */
    }
    else
    {
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        SMC_SmrApiRelReq((VOS_UINT8)enErrorCode, SMS_FALSE );                                   /* 发送MNSMS_REL_REQ,释放mm连接             */
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        /*清除前面的消息*/
        g_SmrEnt.SmrMo.ucRetransFlg = SMR_RETRANS_NO_PERMIT;                    /* 将RETRANS FLAG置0清除                    */

        /* 启动定时器TRAM */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_MemNotifyRetrans: TimerStart: TRAM" );
        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TRAM ) )
        {
            return;
        }

        g_SmrEnt.SmrMo.ucState                  = SMR_WAIT_FOR_RETRANS_TIMER;   /* 状态迁移                                 */

    }
}
/*******************************************************************************
Module:     SMR_TimerTr1mExpire
Function:   TR1M定时器溢出处理
Input:
Output:
NOTE:
Return:   VOS_VOID
History:
1.   张志勇   2004.03.10   新规作成
2.日    期   : 2012年8月31日
  作    者   : z00161729
  修改内容   : DCM定制需求和遗留问题修改

*******************************************************************************/
VOS_VOID SMR_TimerTr1mExpire()
{
    /* 停止timer TR1M */
    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_TimerTr1mExpire: TimerStop: TR1M" );
    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
    {
        return;
    }

    if ( SMR_WAIT_FOR_RP_ACK == g_SmrEnt.SmrMo.ucState )
    {
        if ( SMS_TRUE == g_SmrEnt.SmrMo.ucMemAvailFlg )
        {                                                                       /*是内存通知过程                            */
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            SMR_MemNotifyRetrans(SMR_SMT_ERROR_TR1M_TIMEOUT, VOS_NULL_PTR, 0);         /* 调用重发过程的处理                       */
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

            if (SMR_IDLE == g_SmrEnt.SmrMo.ucState)
            {
                SMC_SmrApiRelReq(SMR_SMC_REL_CAUSE_NORMAL, SMS_FALSE );             /* 释放当前正在建立的消息的资源 */
            }

        }
        else
        {
            SMC_SmrApiAbortReq(SMR_SMC_ABORT_CAUSE_TR1M_EXP);                   /* 向网侧报错                               */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_TimerTr1mExpire:NORMAL:SMS state = SMR_IDLE");
            g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                  /* 进入空闲                                 */

            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            SMS_SendMnReportReq(SMR_SMT_ERROR_TR1M_TIMEOUT, VOS_NULL_PTR, 0);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

        }
    }
}
/*******************************************************************************
Module:   SMR_TimerTr2mExpire
Function: TR2M定时器溢出处理
Input:
Output:
NOTE:
Return:   VOS_VOID
History:
1.   张志勇   2004.03.10   新规作成
2.
3.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级
*******************************************************************************/
VOS_VOID SMR_TimerTr2mExpire()
{
    /* 停止timer TR2M */
    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_TimerTr2mExpire: TimerStop: TR2M" );
    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR2M ) )
    {
        return;
    }

    /* g_SmrEnt.SmrMt.TimerInfo.ucTimerSta = SMS_TIMER_STATUS_STOP; */
    if (SMR_WAIT_TO_SND_RP_ACK == g_SmrEnt.SmrMt.ucState)
    {
        SMC_SmrApiAbortReq( SMR_SMC_ABORT_CAUSE_TR2M_EXP );                     /* 发送MNSMS_ABORT_REQ                      */
        /* SMR_MkSndReportError( g_SmrEnt.SmrMt.ucMr,SMR_ERR_CAUSE_TEMP_FAILURE );  发送SMRL_REPORT_IND                      */
        /*定时器超时后，还没有响应，通知AT修改+CNMI命令参数<mt>和<ds>置为0*/
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        SMS_SendMnMtErrInd(SMR_SMT_ERROR_TR2M_TIMEOUT);
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_TimerTr2mExpire:NORMAL:SMS state = SMR_IDLE");
        g_SmrEnt.SmrMt.ucState = SMR_IDLE;                                      /* 状态迁移到空闲状态                       */
    }
}
/*******************************************************************************
Module:   SMR_TimerTramExpire
Function: TRAM定时器溢出处理
Input:
Output:
NOTE:
Return:   VOS_VOID
History:
1.   张志勇   2004.03.10   新规作成
2.
*******************************************************************************/
VOS_VOID SMR_TimerTramExpire()
{
    VOS_UINT8     ErrData[3];    /*A32D00461,zzy,pclint*/                                                    /* 定义临时指向RP_SMMA的指针                */

    /* 停止timer TRAM */
    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_TimerTramExpire: TimerStop: TRAM" );
    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TRAM ) )
    {
        return;
    }

    /* g_SmrEnt.SmrMo.aTimerInfo[1].ucTimerSta = SMS_TIMER_STATUS_STOP; */

    if ( SMR_WAIT_FOR_RETRANS_TIMER == g_SmrEnt.SmrMo.ucState )
    {
        g_SmrEnt.SmrMo.ucRetransFlg = SMR_RETRANS_PROCESS;                      /* 将实体内的RetransFlg置为SMR_RETRANS_PROC
                                                                                 * ESS                                      */
        ErrData[0] = 2;                                                    /* 填写RP_SMMA的消息长度                    */
        ErrData[1] = SMR_MTN_DATA_TYPE_RP_SMMA;                            /* 填写RP_SMMA的消息类型                    */
        /*lint -e961*/
        g_SmrEnt.SmrMo.ucMr = ++g_ucSmsMR;
        /*lint +e961*/
        ErrData[2] = g_SmrEnt.SmrMo.ucMr;                              /* 填写RP_SMMA的MR                          */

        SMC_SmrApiEstReq(g_ucCurSendDomain,ErrData,3);                                           /* 发送MNSMS_EST_REQ                        */

        /* 启动定时器TR1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_TimerTramExpire: TimerStart: TR1M" );
        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR1M ) )
        {
            return;
        }

        /* g_SmrEnt.SmrMo.aTimerInfo[0].ucTimerSta = SMS_TIMER_STATUS_RUN; */

        g_SmrEnt.SmrMo.ucState                  = SMR_WAIT_FOR_RP_ACK;          /* 状态迁移到SMR_WAIT_FOR_RP_ACK状态        */
    }
}

/*******************************************************************************
Module:   SMR_SmcChk
Function: SMR消息检查函数
Input:    VOS_UINT8     *pucData        数据首地址
          VOS_UINT32     ulLen           数据长度
Output:
NOTE:
Return:   VOS_UINT8
History:
1.   张志勇   2004.03.10   新规作成
2.   Date         : 2007-04-06
     Author       : h44270
     Modification : 问题单号:A32D10113
*******************************************************************************/
VOS_UINT8 SMR_SmcChk(
                 VOS_UINT8     *pucData,                                            /* 数据首地址                               */
                 VOS_UINT32     ulLen                                                /* 数据长度                                 */
                 )
{
    VOS_UINT16 usSmsMsgLength;                                                      /* 定义存储消息的长度的变量                 */
    if (ulLen < 2)
    {                                                                           /* 检查消息过短                             */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_MSG_TOO_SHORT_ERROR ");
        return SMR_MSG_TOO_SHORT_ERROR;
    }
    switch(pucData[0])
    {
    case SMR_NTM_DATA_TYPE_RP_DATA:
        /*应该满足RP-Data的最小长度*/
        if (ulLen < SMR_MIN_RP_DATA_LEN)
        {
            SMS_LOG1(PS_LOG_LEVEL_ERROR, "SMR_SmcChk:RP DATA ulLen is too short", (VOS_INT32)ulLen);
            return SMR_MSG_TOO_SHORT_ERROR;
        }

        if ((*(pucData+2) < 2)||(*(pucData+2) > 11))
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ");
            return  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        usSmsMsgLength = 2+ *(pucData+2)+1;                                     /* 加上RP_Originator Address后的长度        */
        if (usSmsMsgLength >= ulLen)
        {                                                                       /* 消息的长度错误                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ");
            return  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        usSmsMsgLength += 1;                                                    /* 加上RP_Destination Address后的长度       */
        usSmsMsgLength += (pucData[usSmsMsgLength]+1);                          /* 加上RP_User Data后的长度                 */
        if (usSmsMsgLength > ulLen)
        {                                                                       /* 消息的长度错误                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ");
            return  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        break;
    case SMR_NTM_DATA_TYPE_RP_ACK:
        if (ulLen < SMR_MIN_RP_ACK_LEN)
        {
            SMS_LOG1(PS_LOG_LEVEL_ERROR, "SMR_SmcChk:RP ACK ulLen is too short", (VOS_INT32)ulLen);
            return SMR_MSG_TOO_SHORT_ERROR;
        }

        usSmsMsgLength = 2;                                                     /* 计算消息的长度                           */
        if ( 41 == *(pucData+2))
        {                                                                       /* 如果消息中包含USER DATA                  */
            usSmsMsgLength = usSmsMsgLength + 2 + *(pucData+3);
        }
        if (usSmsMsgLength > ulLen)
        {                                                                       /* 消息的长度错误                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ");
            return  SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        break;
    case SMR_NTM_DATA_TYPE_RP_ERR:
        if (ulLen < SMR_MIN_RP_ERROR_LEN)
        {
            SMS_LOG1(PS_LOG_LEVEL_ERROR, "SMR_SmcChk:RP ERROR ulLen is too short", (VOS_INT32)ulLen);
            return SMR_MSG_TOO_SHORT_ERROR;
        }

        usSmsMsgLength =  2 + *(pucData+2)+1;                                   /* 计算消息的长度                           */
        if (usSmsMsgLength > ulLen)
        {                                                                       /* 消息的长度错误                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR ");
            return  SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR;
        }
        else if(usSmsMsgLength < ulLen)
        {
            if ( 41 == *(pucData+ usSmsMsgLength))
            {                                                                   /* 如果消息中包含USER DATA                  */
                usSmsMsgLength = usSmsMsgLength +
                                  *(pucData + usSmsMsgLength+1)+2;
            }
            if (usSmsMsgLength > ulLen)
            {                                                                   /* 消息的长度错误                           */
                PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR ");
                return  SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR;
            }
        }
        else
        {

        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcChk:WARNING:SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST ");
        return SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST;
    }
    return SMR_MSG_CHK_SUCCESS;
}
/*******************************************************************************
Module:   SMR_SndRpErrorReq
Function: 做成并向下层发送RP_ERROR，用MNSMS_DATA_REQ
Input:    VOS_UINT8     ucMr     Message Reference
          VOS_UINT8     ucCause  RP_Cause的原因值
          VOS_UINT8     ucMtFlg  mt标志
Output:
NOTE:
Return:   VOS_UINT8
History:
1.   张志勇   2004.03.10   新规作成
2.
*******************************************************************************/
VOS_VOID SMR_SndRpErrorReq(
                       VOS_UINT8     ucMr,                                          /* Message Reference                        */
                       VOS_UINT8     ucCause,                                       /* RP_Cause的原因值                         */
                       VOS_UINT8     ucMtFlg                                        /* mt标志                                   */
                       )
{
    VOS_UINT8   ErrData[5];   /*A32D00461,zzy,pclint*/                                                          /* 定义临时指向错误信息的指针               */

    if(SMS_FALSE == ucMtFlg)
    {
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SndRpErrorReq:WARNING:ucMtFlg = SMS_FALSE");
        return;
    }

    ErrData[0]       = 4;                                                        /* 填写RP_ERROR的消息RPDU的长度             */
    ErrData[1] = SMR_ERR_CAUSE_MTI_MO_RP_ERROR;                            /* 填写RP_ERROR的消息类型 MS->N 值为4       */
    ErrData[2] = ucMr;                                                     /* 填写RP_ERROR的MR                         */
    ErrData[3] = 1;                                                        /* 填写RP_Cause的长度                       */
    ErrData[4] = ucCause;                                                  /* 填写RP_Cause的原因值                     */
    SMC_SmrApiDataReq(ErrData,5);                                              /* 调用发送API                              */
}

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Delete SMR_MkSndReportError */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

