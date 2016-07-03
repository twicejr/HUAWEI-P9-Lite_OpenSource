
#include "smsinclude.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasGmmInterface.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SMC_COM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*lint -save -e958 */


VOS_VOID SMC_TimerTc1mExp(
                      VOS_UINT8       ucTimerId                                     /* TIMER ID                                 */
                      )
{
    VOS_BOOL                            bRetryFlag;
    VOS_UINT32                          ulRet;


    /* 停止当前的定时器 */
    if ( SMS_FALSE == SMS_TimerStop( ucTimerId ) )
    {
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: SMS_TimerStop fail." );;
    }

    switch(ucTimerId)
    {
    case SMC_TIMER_ID_PS_TC1M_MT:
        if (SMC_MT_IDLE == g_SmcPsEnt.SmcMt.ucState)
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: PS MT state is idle." );
            return;
        }

        if (0 == g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen)
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: buffer is null." );
            return;
        }

        SMS_GetTc1mTimeOutRetryFlag(g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes,
                                    &bRetryFlag);
        if (VOS_TRUE == bRetryFlag)
        {
            g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes++;

            ulRet = NAS_SMS_ResendPsRpReport();
            if (VOS_TRUE == ulRet)
            {


                /* 告警清理，增加对启动定时器返回值的判断 */
                if ( SMS_FALSE == SMS_TimerStart(SMC_TIMER_ID_PS_TC1M_MT) )
                {
                    SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: TimerStart: TR1M Failed" );
                }


                return;
            }
        }

        if(SMC_MT_IDLE != g_SmcPsEnt.SmcMt.ucState)
        {

            /* 启动非循环定时器,定时器已被停止 */

            g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                   /* 清除超时次数                             */

            if(0 != g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen)
            {                                                               /* 有存储的消息                             */
                SMS_Free( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg );
                g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;
                g_SmcPsEnt.SmcMt.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
            }

            NAS_SMS_ChangePsMtEntityState(SMC_MT_IDLE);

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_TimerTc1mExp:NORMAL:SMS state = SMC_MT_IDLE");

            SMR_SmcApiErrorInd( SMR_SMT_ERROR_TC1M_TIMEOUT, SMS_TRUE);                                 /* 上报错误                                 */
        }

        break;
    case SMC_TIMER_ID_PS_TC1M_MO:
        if (SMC_MO_IDLE == g_SmcPsEnt.SmcMo.ucState)
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: PS MO state is idle." );
            return;
        }

        if (0 == g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: buffer is null." );
            return;
        }

        SMS_GetTc1mTimeOutRetryFlag(g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes,
                                    &bRetryFlag);
        if (VOS_TRUE == bRetryFlag)
        {
            g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes++;

            ulRet = NAS_SMS_ResendPsRpData(VOS_TRUE);
            if (VOS_TRUE == ulRet)
            {


                /* 告警清理，增加对启动定时器返回值的判断 */
                if ( SMS_FALSE == SMS_TimerStart(SMC_TIMER_ID_PS_TC1M_MO) )
                {
                    SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: TimerStart: SMC_TIMER_ID_PS_TC1M_MO Failed" );
                }


                return;
            }
        }

        if(SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState)
        {

            /* 启动非循环定时器,定时器已被停止 */

            g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;                   /* 清除超时次数                             */

            if(0 != g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
            {                                                               /* 有存储的消息                             */
                SMS_Free( g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg );
                g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
                g_SmcPsEnt.SmcMo.enHoldSndMsgType       = NAS_SMS_HOLD_MSG_BUTT;
            }

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, ":NORMAL:SMS state = SMC_MO_IDLE");

            SMR_SmcApiErrorInd( SMR_SMT_ERROR_TC1M_TIMEOUT, SMS_FALSE);                                 /* 上报错误                                 */
        }

        break;
    case SMC_TIMER_ID_CS_TC1M_MT:
        if (SMC_MT_IDLE == g_SmcCsEnt.SmcMt.ucState)
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: CS MT state is idle." );
            return;
        }

        if (0 == g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen)
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: buffer is null." );
            return;
        }

        SMS_GetTc1mTimeOutRetryFlag(g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes,
                                    &bRetryFlag);
        if (VOS_TRUE == bRetryFlag)
        {
            g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes++;

            ulRet = NAS_SMS_ResendCsRpReport();
            if (VOS_TRUE == ulRet)
            {


                /* 告警清理，增加对启动定时器返回值的判断 */
                if ( SMS_FALSE == SMS_TimerStart(SMC_TIMER_ID_CS_TC1M_MT) )
                {
                    SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: TimerStart: SMC_TIMER_ID_CS_TC1M_MT Failed" );
                }


                return;
            }

        }

        if(SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState)
        {
            SMC_ComCsInitEnt( SMS_TRUE );                                   /* 初始化CS域的实体                         */

            SMR_SmcApiErrorInd( SMR_SMT_ERROR_TC1M_TIMEOUT, SMS_TRUE);                                 /* 上报错误                                 */
        }

        break;
    case SMC_TIMER_ID_CS_TC1M_MO:
        if (SMC_MO_IDLE == g_SmcCsEnt.SmcMo.ucState)
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_TimerTc1mExp: CS MO state is idle." );
            return;
        }

        if (0 == g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: buffer is null." );
            return;
        }

        SMS_GetTc1mTimeOutRetryFlag(g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes,
                                    &bRetryFlag);
        if (VOS_TRUE == bRetryFlag)
        {
            g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes++;

            ulRet = NAS_SMS_ResendCsRpData(VOS_TRUE);
            if (VOS_TRUE == ulRet)
            {


                /* 告警清理，增加对启动定时器返回值的判断 */
                if ( SMS_FALSE == SMS_TimerStart(SMC_TIMER_ID_CS_TC1M_MO) )
                {
                    SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_TimerTc1mExp: TimerStart: SMC_TIMER_ID_CS_TC1M_MO Failed" );
                }


                return;
            }
        }

        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {
            SMC_ComCsInitEnt( SMS_FALSE );                                  /* 初始化CS域的实体                         */

            SMR_SmcApiErrorInd( SMR_SMT_ERROR_TC1M_TIMEOUT, SMS_FALSE);                                 /* 上报错误                                 */
        }

        break;
    default:
        break;
    }
}


VOS_VOID  SMC_GetCpDataTiValidFlag(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            *pbValidFlag
)
{
    VOS_UINT8                           ucCmpTi;

    /* 表示接收的该消息正在MO过程中 */
    if ((ucTi & 0x80) != 0x80)
    {
        *pbValidFlag = VOS_TRUE;
        return;
    }

    ucCmpTi = ucTi >> 4;

    /* PS域的MO实体状态不为空                   */
    if(SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState)
    {
        /* TI相等                                   */
        if(ucCmpTi == g_SmcPsEnt.SmcMo.ucTi)
        {
            *pbValidFlag = VOS_TRUE;
            return;
        }
    }

    /* CS域的MO实体状态不为空                   */
    if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
    {
        /* TI相等                                   */
        if (ucCmpTi == g_SmcCsEnt.SmcMo.ucTi)
        {
            *pbValidFlag = VOS_TRUE;
            return;
        }

        if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
        {
            /* TI相等: MO过程中，网络重发RP-ACK时会走到该流程*/
            if (ucCmpTi == g_SmcCsEnt.SmcMo.ucPreTi)
            {
                *pbValidFlag = VOS_TRUE;
                return;
            }
        }
    }

    *pbValidFlag = VOS_FALSE;
    return;
}


VOS_UINT8 SMC_ComNwMsgChk(
                     VOS_UINT8* pucCpdu,
                     VOS_UINT32  ulCpduLen
                     )
{
    VOS_BOOL                            bTiValidFlag;

    /*24011 9.2.1 Message too short , 丢弃消息*/
    if(ulCpduLen < 2)
    {                                                                           /* 消息太短                                 */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS Message too short!");
        return SMC_CP_ERR_MSG_INVALID;
    }

    /*24011 9.2.2  TI value为0x111, 丢弃消息*/
    if (((pucCpdu[0] >> 4) & 0x07) == 0x07)
    {                                                                           /* TI错误                                   */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS TI ERROR!");
        return SMC_CP_ERR_MSG_INVALID;
    }

    if(SMC_DATA_TYPE_CP_DATA == pucCpdu[1])
    {
        /*UE收到来自接收实体的CP-DATA消息，若TI不一致则丢弃消息*/
        SMC_GetCpDataTiValidFlag(pucCpdu[0], &bTiValidFlag);
        if(VOS_TRUE != bTiValidFlag)
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS SMS MSG INVALID!");
            return SMC_CP_ERR_MSG_INVALID;
        }
        /* 不存在强制IE                             */
        if(ulCpduLen <= 2)
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS SMS MANDATORY INFO ERROR!");
            return SMS_CP_ERR_MANDA_INFO_ELEM_ERR;
        }
    }
    else if (SMC_DATA_TYPE_CP_ERR == pucCpdu[1])
    {
        if(ulCpduLen < 3)
        {                                                                       /* 不存在强制IE                             */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS SMS MSG INVALID!");
            return SMC_CP_ERR_MSG_INVALID;                                      /* 返回错误原因                             */
        }
        /*TI值不对时,ignore该消息*/
        if((((pucCpdu[0] & 0xf0)>>4) != g_SmcPsEnt.SmcMo.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcCsEnt.SmcMo.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcCsEnt.SmcMt.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcPsEnt.SmcMt.ucTi)
            )
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS Cp-err,invalid Ti!");
            return SMC_CP_ERR_MSG_INVALID;                                      /* 返回错误原因                             */
        }
    }
    else if (SMC_DATA_TYPE_CP_ACK == pucCpdu[1])
    {                                                                           /* 消息类型是CP-ACK                       */
        if((((pucCpdu[0] & 0xf0)>>4) != g_SmcPsEnt.SmcMo.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcCsEnt.SmcMo.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcCsEnt.SmcMt.ucTi)&&
           (((pucCpdu[0] & 0xf0)>>4) != g_SmcPsEnt.SmcMt.ucTi))
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS Cp-ACK,invalid Ti!");
            return SMS_CP_ERR_INVALID_TI;                                      /* 返回错误原因                             */
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ComNwMsgChk:WARNING:NW->SMS Sms-msg-type error!");
        return SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT;                                      /* 返回错误原因                             */
    }

    return SMC_MSG_VALID;
}


VOS_VOID SMC_MoBufferCpAckSend(VOS_VOID)
{
    if ((SMS_TRUE != g_SmcCsEnt.SmcMo.ucCpAckFlg)
     && (SMS_TRUE != g_SmcPsEnt.SmcMo.ucCpAckFlg))
    {
        PS_NAS_LOG(WUEPS_PID_SMS,
               VOS_NULL,
               PS_LOG_LEVEL_NORMAL,
               "SMC_MoBufferCpAckSend:INFO: no CP-ACK need to send.");
        return;
    }

    if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
    {
        g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcCsEnt.SmcMo.ucState)
        {
            SMC_SndMmCpAckMsg(g_SmcCsEnt.SmcMo.ucTi);
            SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucTi);                                /* 指示MM释放MM连接                         */

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);

            PS_NAS_LOG(WUEPS_PID_SMS,
                   VOS_NULL,
                   PS_LOG_LEVEL_NORMAL,
                   "SMC_MoBufferCpAckSend: SMS state = SMC_MO_IDLE");
        }
        else if (SMC_MO_MM_CONN_PENDING == g_SmcCsEnt.SmcMo.ucState)
        {
            if (g_SmcCsEnt.SmcMo.ucPreTi == g_SmcCsEnt.SmcMo.ucTi)
            {
                PS_NAS_LOG(WUEPS_PID_SMS,
                       VOS_NULL,
                       PS_LOG_LEVEL_WARNING,
                       "SMC_MoBufferCpAckSend: "
                       "Current TI and previous TI is indentical.");
                return;
            }
            SMC_SndMmCpAckMsg(g_SmcCsEnt.SmcMo.ucPreTi);
            SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucPreTi);                                /* 指示MM释放MM连接                         */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING,
                   "SMC_MoBufferCpAckSend:WARNING: CP-ACK indication and C layer"
                   "state not indentical.");
        }
    }
    else
    {
        g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcPsEnt.SmcMo.ucState)
        {
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                /* 当前驻留在L模,构造SMS_LMM_DATA_REQ消息，通过NAS_SMS_SndLmmDataReq发送 */
                NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ACK, 0XFF, g_SmcPsEnt.SmcMo.ucTi );
            }
            else
#endif
            {
                SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ACK,
                                   0XFF,
                                   g_SmcPsEnt.SmcMo.ucTi );                         /* 向网侧回确认                             */
            }
            PS_NAS_LOG(WUEPS_PID_SMS,
                   VOS_NULL,
                   PS_LOG_LEVEL_NORMAL,
                   "SMC_MoBufferCpAckSend: SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_SMS,
                   VOS_NULL,
                   PS_LOG_LEVEL_WARNING,
                   "SMC_MoBufferCpAckSend: CP-ACK indication and C layer"
                   "state not indentical.");
        }
    }

    return;
}
/*lint -restore */

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_SMS_NotifySessionAccordingCsMoEntityStateChg(VOS_UINT8  ucState)
{
    /* cs主叫实体状态从idle到非idle，申请资源 */
    if ((SMC_MO_IDLE == g_SmcCsEnt.SmcMo.ucState)
     && (SMC_MO_IDLE != ucState))
    {
        NAS_SMS_SndMmBeginSessionNotify(MMSMS_SESSION_TYPE_MO_SMS);
    }

    /* cs主叫实体从非idle到idle，释放资源 */
    if ((SMC_MO_IDLE == ucState)
     && (SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState))
    {
        NAS_SMS_SndMmEndSessionNotify(MMSMS_SESSION_TYPE_MO_SMS);
    }

    return;
}
#endif


VOS_VOID NAS_SMS_ChangeCsMoEntityState(VOS_UINT8  ucState)
{
    NAS_SMS_LogSmsStateInfo(g_SmcCsEnt.SmcMo.ucState);

#if (FEATURE_ON == FEATURE_DSDS)
    NAS_SMS_NotifySessionAccordingCsMoEntityStateChg(ucState);
#endif

    g_SmcCsEnt.SmcMo.ucState = ucState;

    NAS_SMS_LogSmsStateInfo(g_SmcCsEnt.SmcMo.ucState);

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_SMS_NotifySessionAccordingCsMtEntityStateChg(VOS_UINT8  ucState)
{
    /* cs mt实体状态从idle到非idle,申请被叫资源 */
    if ((SMC_MT_IDLE ==g_SmcCsEnt.SmcMt.ucState)
     && (SMC_MT_IDLE != ucState))
    {
        NAS_SMS_SndMmBeginSessionNotify(MMSMS_SESSION_TYPE_MT_SMS);
    }

    /* cs mt实体从非idle到idle，释放被叫资源 */
    if ((SMC_MT_IDLE == ucState)
     && (SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState))
    {
        NAS_SMS_SndMmEndSessionNotify(MMSMS_SESSION_TYPE_MT_SMS);
    }

    return;
}
#endif


VOS_VOID NAS_SMS_ChangeCsMtEntityState(VOS_UINT8  ucState)
{
    NAS_SMS_LogSmsStateInfo(g_SmcCsEnt.SmcMt.ucState);

#if (FEATURE_ON == FEATURE_DSDS)
    NAS_SMS_NotifySessionAccordingCsMtEntityStateChg(ucState);
#endif

    g_SmcCsEnt.SmcMt.ucState = ucState;

    NAS_SMS_LogSmsStateInfo(g_SmcCsEnt.SmcMt.ucState);

    return;
}


VOS_VOID NAS_SMS_NotifySessionAccordingPsMoEntityStateChg(VOS_UINT8  ucState)
{
    /* ps域主叫短信实体状态从idle到非idle，申请资源 */
    if ((SMC_MO_IDLE == g_SmcPsEnt.SmcMo.ucState)
     && (SMC_MO_IDLE != ucState))
    {
        NAS_SMS_SndGmmBeginSessionNotify(GMMSMS_SESSION_TYPE_MO_SMS);
    }

    /* ps域主叫短信实体状态从非idle到idle，释放资源 */
    if ((SMC_MO_IDLE == ucState)
     && (SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState))
    {
        NAS_SMS_SndGmmEndSessionNotify(GMMSMS_SESSION_TYPE_MO_SMS);
    }

    return;
}


VOS_VOID NAS_SMS_ChangePsMoEntityState(VOS_UINT8  ucState)
{
    NAS_SMS_LogSmsStateInfo(g_SmcPsEnt.SmcMo.ucState);

    NAS_SMS_NotifySessionAccordingPsMoEntityStateChg(ucState);

    g_SmcPsEnt.SmcMo.ucState = ucState;

    NAS_SMS_LogSmsStateInfo(g_SmcPsEnt.SmcMo.ucState);

    return;
}


VOS_VOID NAS_SMS_NotifySessionAccordingPsMtEntityStateChg(VOS_UINT8  ucState)
{
    /* ps域被叫短信实体状态从idle到非idle，申请资源 */
    if ((SMC_MT_IDLE == g_SmcPsEnt.SmcMt.ucState)
     && (SMC_MT_IDLE != ucState))
    {
        NAS_SMS_SndGmmBeginSessionNotify(GMMSMS_SESSION_TYPE_MT_SMS);
    }

    /* ps域被叫短信实体状态从非idle到idle，释放资源 */
    if ((SMC_MT_IDLE == ucState)
     && (SMC_MT_IDLE != g_SmcPsEnt.SmcMt.ucState))
    {
        NAS_SMS_SndGmmEndSessionNotify(GMMSMS_SESSION_TYPE_MT_SMS);
    }

    return;
}


VOS_VOID NAS_SMS_ChangePsMtEntityState(VOS_UINT8  ucState)
{
    NAS_SMS_LogSmsStateInfo(g_SmcPsEnt.SmcMt.ucState);

    NAS_SMS_NotifySessionAccordingPsMtEntityStateChg(ucState);

    g_SmcPsEnt.SmcMt.ucState = ucState;

    NAS_SMS_LogSmsStateInfo(g_SmcPsEnt.SmcMt.ucState);

    return;
}



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

