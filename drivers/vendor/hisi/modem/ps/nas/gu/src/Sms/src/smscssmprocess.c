
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
#define    THIS_FILE_ID        PS_FILE_ID_SMS_CSSMPROCESS_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


extern VOS_UINT8  Smt_StartMemNotification( VOS_VOID );
extern VOS_VOID SMC_ReportM2NOtaMsg(NAS_MSG_STRU *pMsg);

/*lint -save -e958 */


VOS_UINT32 NAS_SMS_ResendCsRpData(VOS_UINT8 ucRetransFlg)
{
    VOS_UINT8                           ucRdPos;
    VOS_UINT8                           ucTpType;

    if ((VOS_NULL_PTR == g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg)
     || (0 == g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen))
    {
        return VOS_FALSE;
    }

    /* SUBMIT 短信且要求修改TP-RD，则修改TP-RD后发送 */
    if (SMS_TRUE != g_SmrEnt.SmrMo.ucMemAvailFlg)
    {
        ucRdPos  = (VOS_UINT8)(SMS_TPDU_MTI_CS + *((VOS_UINT8 *)g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg + SMS_TPDU_SCLEN_CS));
        ucTpType = (*((VOS_UINT8 *)g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg + ucRdPos)) & NAS_SMS_TP_MTI_MASK;

        if ((NAS_SMS_TP_MTI_SUBMIT == ucTpType)
         && (VOS_TRUE == ucRetransFlg))
        {
            *((VOS_UINT8 *)g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg + ucRdPos) |= SMT_TP_RD_RETRANS;
        }
    }

    SMC_SndMmMsg(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg,
                 MMSMS_DATA_REQ,
                 (VOS_UINT16)g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen);

    return VOS_TRUE;
}


VOS_UINT32 NAS_SMS_ResendCsRpReport(VOS_VOID)
{

    if ((VOS_NULL_PTR == g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg)
     || (0 == g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen))
    {
        return VOS_FALSE;
    }

    SMC_SndMmMsg(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg,
                 MMSMS_DATA_REQ,
                 (VOS_UINT16)g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen);

    return VOS_TRUE;
}



VOS_VOID NAS_SMS_RcvNackMsg(MMSMS_NACK_DATA_IND_STRU *pstNackMsg)
{
    VOS_UINT8                           ucPos;
    VOS_UINT8                           ucTiValue;
    VOS_UINT8                           ucTiFlag;
    VOS_UINT8                           ucCpType;
    VOS_UINT8                           ucRpType;
    VOS_UINT32                          ulRet;

    ucPos = 0;

    /* 获取TI，TI-flag和消息类型，*/
    ucTiFlag  = (VOS_UINT8)((pstNackMsg->stNackMsg.aucNasMsg[ucPos] & NAS_SMS_TI_FLAG_MASK) >> NAS_SMS_TI_FLAG_OFFSET);
    ucTiValue = (VOS_UINT8)((pstNackMsg->stNackMsg.aucNasMsg[ucPos] & NAS_SMS_TI_VALUE_MASK) >> NAS_SMS_TI_VALUE_OFFSET);

    ucPos++;

    /*
    未发送消息重传规则:
    CP-ACK消息不重传；
    SUBMIT或COMMAND消息，判断MO ENTITY的TI一致，TI-FLAG正确；
    DELIVER-REPORT消息，判断MT ENTITY的TI一致，TI-FLAG正确；
    其他情况，丢弃；
    */
    ucCpType = pstNackMsg->stNackMsg.aucNasMsg[ucPos];
    if (SMC_DATA_TYPE_CP_DATA != ucCpType)
    {
        return;
    }
    ucPos++;

    /* RPDU length */
    ucPos++;

    /* RPDU tag */
    ucRpType = pstNackMsg->stNackMsg.aucNasMsg[ucPos];

    /* SMMA SUBMIT或COMMAND消息，判断MO ENTITY的TI一致，TI-FLAG正确； */
    /* RP-ACK消息，判断MO ENTITY的TI一致，TI-FLAG正确； */
    /* SUBMIT 短信需要修改TP-RD后发送 */
    /* 其他，包括COMMAND或RP-ACK消息直接发送即可 */
    if ((SMR_MTN_DATA_TYPE_RP_ACK == ucRpType)
     || (SMR_MTN_DATA_TYPE_RP_ERR == ucRpType))
    {
        if (((g_SmcCsEnt.SmcMt.ucTi & NAS_SMS_LOCAL_TI_VALUE_MASK) != ucTiValue)
         || (NAS_SMS_TI_FLAG_MSG_SEND_TO_ORIG != ucTiFlag))
        {
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: g_SmcCsEnt.SmcMt.ucTi ", g_SmcCsEnt.SmcMt.ucTi);
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: ucTiValue ", ucTiValue);
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: ucTiFlag ", ucTiFlag);
            return;
        }

        ulRet = NAS_SMS_ResendCsRpReport();
        if (VOS_TRUE != ulRet)
        {
            return;
        }

        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            SMS_LOG( LOG_LEVEL_WARNING, "SMS:NAS_SMS_RcvNackMsg: fail to stop TC1M." );
        }

        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            SMS_LOG( LOG_LEVEL_WARNING, "SMS:NAS_SMS_RcvNackMsg: fail to stop TC1M." );
        }

        return;
    }
    else
    {
        if (((g_SmcCsEnt.SmcMo.ucTi  & NAS_SMS_LOCAL_TI_VALUE_MASK) != ucTiValue)
         || (NAS_SMS_TI_FLAG_MSG_SEND_FROM_ORIG != ucTiFlag))
        {
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: g_SmcCsEnt.SmcMt.ucTi ", g_SmcCsEnt.SmcMt.ucTi);
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: ucTiValue ", ucTiValue);
            PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_SMS_RcvNackMsg: ucTiFlag ", ucTiFlag);
            return;
        }

        ulRet = NAS_SMS_ResendCsRpData(VOS_TRUE);
        if (VOS_TRUE != ulRet)
        {
            return;
        }

        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
        {
            SMS_LOG( LOG_LEVEL_WARNING, "NAS_SMS_RcvNackMsg: fail to stop TC1M." );
        }

        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_CS_TC1M_MO ) )
        {
            SMS_LOG( LOG_LEVEL_WARNING, "NAS_SMS_RcvNackMsg: fail to stop TC1M." );
        }
    }

    return;
}



VOS_VOID SMC_RcvNwCsMtData(
                       VOS_UINT8*   pucCpdu,
                       VOS_UINT32    ulCpduLen
                      )
{
    VOS_UINT8  ucResult;
    VOS_UINT32 ulRet;
    SMC_ENTITY_STRU     g_OrgSmcEnt;
    ucResult = SMC_ComNwMsgChk( pucCpdu, ulCpduLen );                           /* 消息检查                                 */
    if(SMC_MSG_VALID != ucResult)
    {                                                                           /* 结果错误                                 */
        if(SMC_CP_ERR_MSG_INVALID != ucResult)
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR, ucResult,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* 向网侧回错误指示                         */
        }
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvNwCsMtData:WARNING:SMC_MSG_VALID != ucResult ");
        return;
    }

    switch(pucCpdu[1])
    {                                                                           /* 消息类型                                 */
    case SMC_DATA_TYPE_CP_DATA:
        SMS_Memcpy(&g_OrgSmcEnt, &g_SmcCsEnt, sizeof(SMC_ENTITY_STRU));
        if(g_SmcCsEnt.SmcMt.ucTi != (pucCpdu[0] >> 4))
        {
            if(SMC_MT_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMt.ucState)
            {
                /* It should be copied that receive the CP ACK at SMC_MT_WAIT_FOR_CP_ACK state */
                /* 停止timer TC1M */
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: TimerStop: TC1M" );
                if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
                {
                    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: TimerStop: TC1M failed" );
                }

                g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                       /* 清除timer超时次数                        */

                NAS_SMS_ChangeCsMtEntityState(SMC_MT_MM_CONN_EST);

                if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
                {
                    SMS_Free(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg);                     /* 释放缓存的消息                           */
                    g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                       /* 初始化消息长度                           */
                }
            }
            else
            {
                SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                                  SMS_CP_ERR_INVALID_TI,
                                  pucCpdu[0] >> 4 );                                /* 向网侧指示错误                           */

                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: Invalid Ti,ignore MSG" );
                return ;
            }
        }

        if(SMC_MT_MM_CONN_EST == g_SmcCsEnt.SmcMt.ucState)
        {                                                                       /* 实体状态是空闲或在等待网侧确认           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMtData:NORMAL:SMS state = SMC_MT_WAIT_FOR_RP_ACK");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_WAIT_FOR_RP_ACK);

            g_SmcCsEnt.SmcMt.ucTi = pucCpdu[0] >> 4;                            /* 存储ti                                   */

            g_SmcCsEnt.SmcMt.ucMr = pucCpdu[SMC_MSG_HDR_LEN + 2];               /* 存储mr                                   */

            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ACK,
                              0XFF,
                              g_SmcCsEnt.SmcMt.ucTi );                          /* 向网侧回确认                             */

            ulRet = SMR_SmcApiEstInd( &(pucCpdu[3]),
                                      (ulCpduLen - SMC_MSG_HDR_LEN) - 1,
                                      SMS_CN_CS );                /* 向高层提交数据                           */
            if(VOS_OK == ulRet)
            {
                if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
                {
                    SMC_ComCsWaitAckSta(SMS_TRUE);                                  /* 调用公共处理                             */
                }
            }
            else
            {
                SMS_Memcpy(&g_SmcCsEnt,&g_OrgSmcEnt, sizeof(SMC_ENTITY_STRU));
            }
        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                              pucCpdu[0] >> 4 );                                /* 向网侧指示错误                           */
        }
        break;
    case SMC_DATA_TYPE_CP_ACK:
        if(SMC_MT_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMt.ucState)
        {                                                                       /* 与实体的状态兼容                         */
            /* 停止timer TC1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: TimerStop: TC1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMtData: TimerStop: TC1M failed" );
            }

            g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                       /* 清除timer超时次数                        */

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_MM_CONN_EST);

            if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
            {
                SMS_Free(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg);                     /* 释放缓存的消息                           */
                g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                       /* 初始化消息长度                           */
            }

            SMC_SndRelReq(g_SmcCsEnt.SmcMt.ucTi);                           /* 释放mm连接                               */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMtData:NORMAL:SMS state = SMC_MT_IDLE");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);

        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* 向网侧指示错误                           */
        }
        break;
    case SMC_DATA_TYPE_CP_ERR:
        if( SMC_MT_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMt.ucState )
        {                                                                       /* 与实体的状态兼容                         */
            SMC_ComCsInitEnt(SMS_TRUE);                                         /* 初始化CS域的实体                         */
        }
        break;
    default:
        SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                          SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                          (pucCpdu[0] & 0xf0) >> 4 );                           /* 向网侧报错 未识别的消息类型              */
        break;
    }
    return;
}

VOS_VOID SMC_RcvMmEstInd(
                     VOS_UINT8*   pucCpdu,
                     VOS_UINT32    ulCpduLen
                     )
{
    VOS_UINT8  ucResult;
    VOS_UINT32 ulRet ;

    ucResult = SMC_ComNwMsgChk( pucCpdu, ulCpduLen );                           /* 消息检查                                 */

    if(SMC_MSG_VALID != ucResult)
    {                                                                           /* 结果错误                                 */
        if(SMC_CP_ERR_MSG_INVALID != ucResult)
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              ucResult,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* 向网侧回错误指示                         */

        }

        SMC_SndRelReq((pucCpdu[0] & 0xf0) >> 4);                                /* 释放mm连接                               */

        return;
    }

    if (SMC_MT_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMt.ucState)
    {                                                                       /* 与实体的状态兼容                         */
        /* 停止timer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvMmEstInd: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvMmEstInd: TimerStop: TC1M failed" );
        }

        g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                       /* 清除timer超时次数                        */

        NAS_SMS_ChangeCsMtEntityState(SMC_MT_MM_CONN_EST);

        if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
        {
            SMS_Free(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg);                     /* 释放缓存的消息                           */
            g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                       /* 初始化消息长度                           */
        }

        SMC_SndRelReq(g_SmcCsEnt.SmcMt.ucTi);                           /* 释放mm连接                               */

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvMmEstInd:NORMAL:SMS state = SMC_MT_IDLE");

        NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);

    }

    if(SMC_MT_IDLE == g_SmcCsEnt.SmcMt.ucState)
    {                                                                           /* 实体是空闲状态                           */
        if(SMC_DATA_TYPE_CP_DATA == pucCpdu[1])
        {                                                                       /* 数据类型是CP-DATA                        */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvMmEstInd:NORMAL:SMS state = SMC_MT_WAIT_FOR_RP_ACK");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_WAIT_FOR_RP_ACK);

            g_SmcCsEnt.SmcMt.ucTi    = pucCpdu[0] >> 4;                         /* 存储ti                                   */
            g_SmcCsEnt.SmcMt.ucMr    = pucCpdu[SMC_MSG_HDR_LEN + 2];            /* 存储mr                                   */

            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ACK,
                              0xff,
                              g_SmcCsEnt.SmcMt.ucTi );                          /* 向网侧回确认                             */

            ulRet = SMR_SmcApiEstInd( &(pucCpdu[3]),
                                       (ulCpduLen - SMC_MSG_HDR_LEN) - 1,
                                       SMS_CN_CS );                /* 向高层上报数据                           */
            if (VOS_OK != ulRet)
            {
                if (SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR == ulRet)
                {
                    SMC_SndRelReq(g_SmcCsEnt.SmcMt.ucTi);                           /* 释放mm连接                               */

                    NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);
                }
                else
                {
                    NAS_SMS_ChangeCsMtEntityState(SMC_MT_WAIT_FOR_CP_ACK);
                }
            }
        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* 向网侧回错误指示                         */
            SMC_SndRelReq((pucCpdu[0] & 0xf0) >> 4);                            /* 释放mm连接                               */
        }
    }
    else
    {
        SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                          SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                          (pucCpdu[0] & 0xf0) >> 4 );                           /* 向网侧回错误指示                         */
        SMC_SndRelReq((pucCpdu[0] & 0xf0) >> 4);                                /* 释放mm连接                               */
    }
    return;
}

VOS_VOID SMC_RcvNwCsMoData(
                       VOS_UINT8* pucCpdu,
                       VOS_UINT32  ulCpduLen
                      )
{
    VOS_UINT8  ucResult;
    VOS_UINT32 ulRet;

    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcCsEnt.SmcMo.ucState.", g_SmcCsEnt.SmcMo.ucState);
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcPsEnt.SmcMo.ucState.", g_SmcPsEnt.SmcMo.ucState);
    ucResult = SMC_ComNwMsgChk( pucCpdu, ulCpduLen );                           /* 消息检查                                 */
    if(SMC_MSG_VALID != ucResult)
    {                                                                           /* 结果错误                                 */
        if(SMC_CP_ERR_MSG_INVALID != ucResult)
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              ucResult,
                              (pucCpdu[0] & 0xf0)>>4);                          /* 向网侧回错误指示                         */
        }
        return;
    }

    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: event ", pucCpdu[1] );
    switch( pucCpdu[1] )
    {                                                                           /* 消息类型                                 */
    case SMC_DATA_TYPE_CP_DATA:
        if((SMC_MO_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMo.ucState)||
           (SMC_MO_MM_CONN_EST == g_SmcCsEnt.SmcMo.ucState))
        {                                                                       /* 状态正确                                 */
            if (ulCpduLen > (SMC_MSG_HDR_LEN + 1))
            {
                g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_TRUE;                             /* 设置需要发送CP-ACK标志                   */
                ulRet = SMR_SmcApiDataInd(&(pucCpdu[3]),
                                          (ulCpduLen - SMC_MSG_HDR_LEN) -1);                 /* 向高层提交数据                           */
                if(VOS_OK == ulRet )
                {
                    /*MO处于SMC_MO_WAIT_FOR_CP_ACK状态说明没有接收到CP-ACK直接接收RP-ACK/ERR*/
                    if (SMC_MO_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMo.ucState)
                    {
                        /* 停止timer TC1M */
                        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvNwCsMoData: TimerStop: TC1M" );
                        if (SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
                        {
                            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_RcvNwCsMoData: fail to Stop TC1M" );
                        }

                        if (0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
                        {                                                                   /* 有存储的发送消息                         */
                            SMS_Free(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg);                     /* 释放存储的消息                           */
                            g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                       /* 清除消息长度                             */
                        }

                        g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;                        /* 清除timer超时次数                        */
                    }

                    NAS_SMS_ChangeCsMoEntityState(SMC_MO_WAIT_TO_SND_CP_ACK);
                }
                else
                {
                    if (SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR != ulRet)
                    {
                        NAS_SMS_ChangeCsMoEntityState(SMC_MO_WAIT_FOR_CP_ACK);

                    }
                    else
                    {
                        NAS_SMS_ChangeCsMoEntityState(SMC_MO_WAIT_FOR_CP_DATA);
                    }
                    g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;                             /* 设置需要发送CP-ACK标志                   */
                }
            }
            else
            {
                SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                                  SMS_CP_ERR_MANDA_INFO_ELEM_ERR,
                                  (pucCpdu[0] & 0xf0) >> 4 );                       /* 向网侧回错误指示                         */
            }
        }
        else
        {
            if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
            {
                SMC_MoBufferCpAckSend();
                SMS_SendMnMoLinkCloseInd();
            }
            else
            {
                SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                                  SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                                  (pucCpdu[0] & 0xf0) >> 4);                        /* 向网侧回错误指示                         */
            }
        }
        SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcCsEnt.SmcMo.ucState.", g_SmcCsEnt.SmcMo.ucState);
        SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcPsEnt.SmcMo.ucState.", g_SmcPsEnt.SmcMo.ucState);
        break;
    case SMC_DATA_TYPE_CP_ACK:
        if( SMC_MO_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMo.ucState )
        {                                                                       /* 状态正确                                 */
            SMC_ComCsWaitAckSta( SMS_FALSE );                                   /* 调用公共处理                             */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData:NORMAL:SMS state = SMC_MO_MM_CONN_EST");

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_MM_CONN_EST);
        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* 向网侧回错误指示                         */
        }

        break;
    case SMC_DATA_TYPE_CP_ERR:
        if ( SMC_MO_WAIT_FOR_CP_ACK == g_SmcCsEnt.SmcMo.ucState )
        {                                                                       /* 状态正确                                 */
            SMC_ComCsInitEnt(SMS_FALSE);                                        /* 初始化CS域的实体                         */

            SMR_SmcApiErrorInd((SMR_SMT_ERROR_CP_ERROR_BEGIN | pucCpdu[2]) , SMS_FALSE);                        /* 向上层报错                               */
        }
        else
        {
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                              (pucCpdu[0] & 0xf0) >> 4 );                       /* 向网侧回错误指示                         */
        }

        break;
    default:
        SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                          SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                          (pucCpdu[0] & 0xf0) >> 4);                        /* 向网侧回错误指示                         */
        break;
    }
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcCsEnt.SmcMo.ucState.", g_SmcCsEnt.SmcMo.ucState);
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_RcvNwCsMoData: g_SmcPsEnt.SmcMo.ucState.", g_SmcPsEnt.SmcMo.ucState);
    return;
}

VOS_VOID SMC_RcvMmEstCnf(
                        MMSMS_EST_CNF_STRU * pRcvMsg                            /* 收到的消息首地址                         */
                    )
{
    VOS_UINT16 usMsgLen;                                                            /* 定义消息长度                             */
    VOS_UINT8 *pucData   = SMS_POINTER_NULL;                                        /* 定义存储消息数据首地址的指针             */
    VOS_UINT8  aucSnd[255];


    if(g_SmcCsEnt.SmcMo.ucTi != (VOS_UINT8)(pRcvMsg->ulTi))
    {                                                                           /* TI错误 忽略消息 返回                     */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvMmEstCnf:WARNING:g_SmcCsEnt.SmcMo.ucTi != (VOS_UINT8)(pRcvMsg->ulTi) ");
        return;
    }

    if(pRcvMsg->ulTi < 8)
    {                                                                           /* 如果TI小于8                              */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvMmEstCnf:WARNING:pRcvMsg->ulTi < 8");
        return;
    }

    if(g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen == 0)
    {                                                                           /* 有缓存的消息                             */
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvMmEstCnf:WARNING:none message to send.");
        return;
    }

    /* 前一MO的TI因缓存CP-ACK还没有释放, 此处需要发散缓存的CP-ACK并释放TI */
    if(SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
    {
        /*发送前一TI 的CP-ACK*/
        SMC_SndMmCpAckMsg(g_SmcCsEnt.SmcMo.ucPreTi);
        /*释放前一TI*/
        SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucPreTi);

        /* 清除需要发送CP-ACK标志并通知 T 层CP-ACK已发送 */
        g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
        SMS_SendMnMoLinkCloseInd();

    }

    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMC_RcvMmEstCnf: SMC_TIMER_ID_TR1M Timer stop fails" );
    }

    if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR1M ) )
    {
        SMS_LOG( PS_LOG_LEVEL_WARNING, "SMC_RcvMmEstCnf: TimerStart: TR1M Failed" );
    }

    g_SmcCsEnt.SmcMo.ucMr =
                 ((VOS_UINT8 *)(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg))[2];          /* 记录RP-MR                                   */
    g_SmrEnt.SmrMo.ucMr =
                 ((VOS_UINT8 *)(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg))[2];          /* 记录RP-MR                                   */

    /*发送g_SmcCsEnt.SmcMo.HoldRcvMsg缓存消息CP-DATA(RP-DATA)到MM*/
    usMsgLen = ((sizeof(MMSMS_DATA_REQ_STRU) - 4) +
               (VOS_UINT16)g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen) +
               SMC_MSG_HDR_LEN;                                                 /* 获得消息的长度                           */
                                                                                /*注意: (VOS_UINT16)g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen) + SMC_MSG_HDR_LEN为L3消息中aucSmsMsg长度*/
    if( g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen < SMC_SND_MSG_MIN_LEN )
    {                                                                           /* 消息的长度较小                           */
        usMsgLen = sizeof(MMSMS_DATA_REQ_STRU);                                 /* 计算消息的长度                           */
    }

    /* 异常保护 */
    if (usMsgLen > sizeof(aucSnd))
    {
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvMmEstCnf:WARNING:message len error.");
        SMS_Free( g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg );
        g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;
        return;
    }

    SMS_Memset( aucSnd,0,usMsgLen );

    pucData = ((MMSMS_DATA_REQ_STRU *)aucSnd)->SmsMsg.aucNasMsg;

    ((MMSMS_DATA_REQ_STRU *)aucSnd)->ulTi = pRcvMsg->ulTi;
    pucData[0] = (VOS_UINT8 )((pRcvMsg->ulTi & 0x07) << 4);                     /* 填写TI                                   */
    pucData[0] |= NAS_PD_SMS;                                                   /* 填写PD                                   */
    pucData[1] = SMC_DATA_TYPE_CP_DATA;                                         /* 填写消息类型                             */

    SMS_Memcpy( ( pucData + 2 ),
                g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg,
                g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen );

    ((MMSMS_DATA_REQ_STRU *)aucSnd)->SmsMsg.ulNasMsgSize =
                  g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen + SMC_MSG_HDR_LEN;

    SMS_Free( g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg );
    g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;

    /* 缓存待重传消息到C层的缓存HoldSndMsg中 */
    g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg     = (VOS_VOID *)SMS_Malloc( usMsgLen );  /* 申请内存                                 */
    if ( VOS_NULL_PTR == g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMC_RcvMmEstCnf: Memory allocation fails" );
        return;
    }
    SMS_Memcpy( g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg,
                aucSnd,
                usMsgLen );                                                     /* 缓存消息                                 */
    g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = usMsgLen;                        /* 缓存消息长度                             */

    /* 启动定时器TC1M */
    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvMmEstCnf: TimerStart: TC1M" );
    if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_CS_TC1M_MO ) )
    {
        SMS_Free(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg);
        g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                               /* 清除消息长度                             */
        return;
    }

    g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

    SMC_SndMmMsg( aucSnd, MMSMS_DATA_REQ, usMsgLen );                       /* 发送消息                                 */

    PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvMmEstCnf:NORMAL:SMS state = SMC_MO_WAIT_FOR_CP_ACK");

    NAS_SMS_ChangeCsMoEntityState(SMC_MO_WAIT_FOR_CP_ACK);

    return;
}

VOS_VOID SMC_ComCsMtErr(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                           ucTi
)
{
    /* TI相等                                   */
    if(g_SmcCsEnt.SmcMt.ucTi == ucTi)
    {
        /* 短信接收实体在空闲态不处理 */
        if (SMC_MT_IDLE == g_SmcCsEnt.SmcMt.ucState)
        {
            return;
        }

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_ComCsMtErr:NORMAL:SMS state = SMC_MT_IDLE");

        NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);

        SMC_ComCsInitEnt(SMS_TRUE);                                             /* 初始化CS域的实体                         */
        SMR_SmcApiErrorInd(enErrorCode, SMS_TRUE);                              /* 上报错误                                 */
    }
    return;
}

VOS_VOID SMC_ComCsMoErr(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                           ucTi
)
{
    if( g_SmcCsEnt.SmcMo.ucTi == ucTi )
    {                                                                           /* TI相等                                   */
        PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "SMC_ComCsMoErr: g_SmcCsEnt.SmcMo.ucState is ",
                g_SmcCsEnt.SmcMo.ucState);
        switch(g_SmcCsEnt.SmcMo.ucState)
        {                                                                       /* MO的实体的状态                           */
        case SMC_MO_WAIT_FOR_CP_ACK:
        case SMC_MO_WAIT_TO_SND_CP_ACK:
        case SMC_MO_MM_CONN_PENDING:
        case SMC_MO_MM_CONN_EST:
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_ComCsMoErr:NORMAL:SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);

            SMC_ComCsInitEnt(SMS_FALSE);                                        /* 初始化CS域的实体                         */
            SMR_SmcApiErrorInd(enErrorCode, SMS_FALSE);                             /* 上报错误                                 */
            break;
        default:
            break;
        }
    }
    return;
}
/*******************************************************************************
  Module:   SMC_ComCsWaitAckSta
  Function: 初始化相应的资源
  Input:    VOS_UINT8   ucMtFlg   MO,MT过程的标识
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇      2004.03.09   新规作成
      2.
*******************************************************************************/
VOS_VOID SMC_ComCsWaitAckSta(
                         VOS_UINT8   ucMtFlg                                        /* 是mt过程 判断MO,MT过程的标识             */
                         )
{
    if(SMS_FALSE == ucMtFlg)
    {                                                                           /* 不是mt过程   即MO过程                    */
        if (0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
        {
            SMS_Free( g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg );                           /* 释放缓存的消息                           */
            g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen        = 0;                        /* 初始化消息长度                           */
        }

        g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes    = 0;                        /* 清除timer超时次数                        */

        /* 停止timer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsWaitAckSta: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
        {
            return;
        }
    }
    else
    {
        if (0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen)
        {
            SMS_Free( g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg );                           /* 释放缓存的消息                           */
            g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen        = 0;                        /* 初始化消息长度                           */
        }

        g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes    = 0;                        /* 清除timer超时次数                        */

        /* 停止timer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsWaitAckSta: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            return;
        }
    }
    return;
}

VOS_VOID SMC_RcvMmRelInd(
                     MMSMS_REL_IND_STRU  *pRcvMsg                               /* 收到的消息                               */
                     )
{
    if( pRcvMsg->ulTi < 7 )
    {                                                                           /* SMC MT实体                               */
        if( SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState )
        {                                                                       /* SMC MT实体状态为非空                     */
            if( g_SmcCsEnt.SmcMt.ucTi == pRcvMsg->ulTi )
            {                                                                   /* TI相等                                   */
                SMC_ComCsMtErr( (SMR_SMT_ERROR_CS_ERROR_BEGIN | pRcvMsg->ulRelCause),
                                (VOS_UINT8)pRcvMsg->ulTi);                         /* 调用CS域MT实体的处理                     */
            }
        }
    }
    else
    {
        if( SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState )
        {                                                                       /* SMC MO实体状态为非空                     */
            if( g_SmcCsEnt.SmcMo.ucTi == pRcvMsg->ulTi )
            {                                                                   /* TI相等                                   */
                SMC_ComCsMoErr( (SMR_SMT_ERROR_CS_ERROR_BEGIN | pRcvMsg->ulRelCause),
                                (VOS_UINT8)pRcvMsg->ulTi);                         /* 调用CS域MO实体的处理                     */
            }
            else if ((SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
                  && (g_SmcCsEnt.SmcMo.ucPreTi == pRcvMsg->ulTi))
            {
                g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
                SMS_SendMnMoLinkCloseInd();
            }
            else
            {
            }
        }
    }
    return;
}

/*******************************************************************************
  Module:   SMC_SndMmDataReq
  Function: 向MM发送MMSMS_DATA_REQ
  Input:    VOS_UINT8     ucType   数据类型
            VOS_UINT8     ucCause  错误原因
            VOS_UINT8     ucTi     transaction id
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇      2004.03.11   新规作成
      2.
*******************************************************************************/
VOS_VOID SMC_SndMmDataReq(
                      VOS_UINT8     ucType,                                         /* 数据类型                                 */
                      VOS_UINT8     ucCause,                                        /* 错误原因                                 */
                      VOS_UINT8     ucTi                                            /* transaction id                           */
                     )
{
    VOS_UINT8               aucTempMsg[255];
    /* MMSMS_DATA_REQ_STRU  *pSndMsg = */
    /* (MMSMS_DATA_REQ_STRU *)Sms_AllocMsg( sizeof(MMSMS_DATA_REQ_STRU) );      申请空间                                 */
    SMS_Memset( aucTempMsg,0,sizeof(MMSMS_DATA_REQ_STRU) );                        /* 初始化清零                               */

    ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->ulTi                = ucTi;                                        /* 填写PD                                   */
    ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.aucNasMsg[0] = (VOS_UINT8)((ucTi ^ 0x08) << 4);                 /* 填写TI                                   */
    ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.aucNasMsg[0] |= NAS_PD_SMS;
    ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.aucNasMsg[1] = ucType;                                      /* 填写消息类型                             */

    if(SMC_DATA_TYPE_CP_ERR == ucType)
    {                                                                           /* 数据类型是cp-error                       */
        ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.ulNasMsgSize = SMC_CP_ERR_LEN;                          /* 赋值消息长度                             */
        ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.aucNasMsg[2] = ucCause;                                 /* 填写错误原因                             */
    }
    else
    {
        ((MMSMS_DATA_REQ_STRU* )aucTempMsg)->SmsMsg.ulNasMsgSize = SMC_CP_ACK_LEN;                          /* 赋值消息长度                             */
    }
    SMC_SndMmMsg(aucTempMsg,MMSMS_DATA_REQ,sizeof(MMSMS_DATA_REQ_STRU));  /* 发送mm消息                               */


    return;
}
/*******************************************************************************
  Module:   SMC_SndRelReq
  Function: 向MM发送MMSMS_REL_REQ
  Input:    VOS_UINT8     ucTi     transaction id
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇      2004.03.11   新规作成
      2.
*******************************************************************************/
VOS_VOID SMC_SndRelReq(
                   VOS_UINT8    ucTi                                                /* transaction id                           */
                  )
{
    /* MMSMS_REL_REQ_STRU  *pSndMsg = */
    /* (MMSMS_REL_REQ_STRU *)Sms_AllocMsg( sizeof(MMSMS_REL_REQ_STRU) );   申请内存空间                             */
    VOS_UINT8     aucTempMsg[255];

    SMS_Memset( aucTempMsg,0,sizeof(MMSMS_REL_REQ_STRU) );                         /* 初始化清零                               */

    ((MMSMS_REL_REQ_STRU* )aucTempMsg)->ulTi = ucTi;                                                       /* 赋值ti                                   */

    SMC_SndMmMsg(aucTempMsg, MMSMS_REL_REQ, sizeof(MMSMS_REL_REQ_STRU));  /* 发送GMM消息                              */


    return;
}

VOS_VOID SMC_SndMmMsg(
                  VOS_UINT8     *pucSnd,                                            /* 发送消息的首地址                         */
                  VOS_UINT8     ucType,                                             /* 消息类型                                 */
                  VOS_UINT16    usLen                                               /* 消息长度                                 */
                  )
{
    VOS_UINT32  ulRet;
    VOS_UINT8   *pucMsg;

    pucMsg = (VOS_UINT8* )PS_ALLOC_MSG( WUEPS_PID_SMS,
                            usLen - VOS_MSG_HEAD_LENGTH );
    if ( VOS_NULL_PTR == pucMsg )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMC_SndMmMsg: Message allocation fails" );
        return;
    }

    PS_MEM_CPY(pucMsg, pucSnd, usLen);

    ((MSG_HEADER_STRU * )pucMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;
    ((MSG_HEADER_STRU * )pucMsg)->ulSenderPid     = WUEPS_PID_SMS;
    ((MSG_HEADER_STRU * )pucMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;
    ((MSG_HEADER_STRU * )pucMsg)->ulReceiverPid   = WUEPS_PID_MM;
    ((MSG_HEADER_STRU * )pucMsg)->ulLength        = usLen - VOS_MSG_HEAD_LENGTH;
    ((MSG_HEADER_STRU * )pucMsg)->ulMsgName     = ucType;                       /* 填写消息名字                             */

    /*Report event begin*/
    if( MMSMS_DATA_REQ == ucType )
    {
        SMC_ReportM2NOtaMsg(&(((MMSMS_DATA_REQ_STRU *)pucSnd)->SmsMsg));

    }
    /*Report event end*/

    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pucMsg );
    if (VOS_OK != ulRet)
    {
        /* 打印错误信息 */
        SMS_LOG( PS_LOG_LEVEL_ERROR, "SMS:SMC_SndMmMsg:Error: Send msg fails" );
    }
}


VOS_VOID SMC_SndMmCpAckMsg(
                      VOS_UINT8     ucTi)
{
    VOS_UINT8                           aucTempMsg[255];
    VOS_UINT32                          ulMsgLen;
    MMSMS_DATA_REQ_STRU                 *pstCpAck;

    ulMsgLen = sizeof(MMSMS_DATA_REQ_STRU);

    SMS_Memset( aucTempMsg, 0, ulMsgLen);
    pstCpAck = (MMSMS_DATA_REQ_STRU *)aucTempMsg;

    pstCpAck->ulTi = ucTi;

    pstCpAck->SmsMsg.aucNasMsg[0] = (ucTi & 0x07) << 4;

    pstCpAck->SmsMsg.ulNasMsgSize = SMC_MSG_HDR_LEN;                                              /* 赋值消息长度                             */
    pstCpAck->SmsMsg.aucNasMsg[0] |= NAS_PD_SMS;                                                  /* 填写pd                                   */
    pstCpAck->SmsMsg.aucNasMsg[1]  = SMC_DATA_TYPE_CP_ACK;                                         /* 填写消息类型                             */

    SMC_SndMmMsg(aucTempMsg, MMSMS_DATA_REQ,sizeof(MMSMS_DATA_REQ_STRU));         /* 发送消息                                 */

    return;
}


VOS_VOID SMC_ComCsInitEnt(
                         VOS_UINT8   ucMtFlg                                        /* 判断MO,MT过程的标识                      */
                     )
{
    if(SMS_FALSE == ucMtFlg)
    {                                                                           /* 即MO过程                                 */
        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {
            SMC_SndRelReq( g_SmcCsEnt.SmcMo.ucTi );                             /* 指示MM释放MM连接                         */
        }
        if( 0 != g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen )
        {                                                                       /* 有存储的接收消息                         */
            SMS_Free( g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg );                       /* 释放存储的消息                           */
            g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                           /* 清除消息长度                             */
        }
        else if(0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
        {                                                                       /* 有存储的发送消息                         */
            SMS_Free( g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg );                       /* 释放存储的消息                           */
            g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                           /* 清除消息长度                             */
        }
        else
        {

        }

        /* 停止timer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsInitEnt: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: fail to stop TC1M." );
        }

        g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;
        if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
        {
            g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;                             /* 设置需要发送CP-ACK标志                   */
            SMS_SendMnMoLinkCloseInd();
        }

        NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);
    }
    else
    {
        if( SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState )
        {
            SMC_SndRelReq( g_SmcCsEnt.SmcMt.ucTi );                             /* 释放mm连接                               */
        }
        if( 0 != g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen )
        {
            SMS_Free( g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg );                       /* 释放缓存的消息                           */
            g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                           /* 初始化消息长度                           */
        }

        /* 停止timer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsInitEnt: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
        {
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComCsInitEnt: fail to stop SMC_TIMER_ID_CS_TC1M_MT." );
        }

        /* g_SmcCsEnt.SmcMt.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
        g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                           /* 清除timer超时次数                        */

        NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);

    }
    return;
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_SMS_SndMmBeginSessionNotify(
    MMSMS_SESSION_TYPE_ENUM_UINT8       enSessionType
)
{
    VOS_UINT32                          ulRet;
    MMSMS_BEGIN_SESSION_NOTIFY_STRU    *pstBeginSessionNotify = VOS_NULL_PTR;

    /* 申请内存  */
    pstBeginSessionNotify = (MMSMS_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SMS,
                                         sizeof(MMSMS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstBeginSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SMS, "NAS_SMS_SndMmBeginSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSMS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SMS;
    pstBeginSessionNotify->stMsgHeader.ulLength         = sizeof(MMSMS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBeginSessionNotify->stMsgHeader.ulMsgName        = MMSMS_BEGIN_SESSION_NOTIFY;
    pstBeginSessionNotify->enSessionType                = enSessionType;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pstBeginSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndMmBeginSessionNotify():WARNING:SEND SMS FAIL");
        return;
    }

    return;
}


VOS_VOID NAS_SMS_SndMmEndSessionNotify(
    MMSMS_SESSION_TYPE_ENUM_UINT8       enSessionType
)
{
    VOS_UINT32                          ulRet;
    MMSMS_END_SESSION_NOTIFY_STRU      *pstEndSessionNotify = VOS_NULL_PTR;

    /* 申请内存  */
    pstEndSessionNotify = (MMSMS_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SMS,
                                         sizeof(MMSMS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstEndSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SMS, "NAS_SMS_SndMmEndSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMSMS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SMS;
    pstEndSessionNotify->stMsgHeader.ulLength         = sizeof(MMSMS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstEndSessionNotify->stMsgHeader.ulMsgName        = MMSMS_END_SESSION_NOTIFY;
    pstEndSessionNotify->enSessionType                = enSessionType;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pstEndSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndMmEndSessionNotify():WARNING:SEND SMS FAIL");
        return;
    }

    return;
}


#endif


VOS_VOID SMC_RcvMmRegStaInd(
                       MMSMS_REG_STATE_IND_STRU  *pRcvMsg                       /* 收到的消息首地址                         */
                       )
{
    if( (MM_SMS_REG_ATTACHED == pRcvMsg->ulRegSts )
     || (MM_SMS_REG_ATTACH_ATTEMPT_TO_UPDATE == pRcvMsg->ulRegSts )
        )
    {                                                                           /* 状态为ATTACH                             */
        g_ucCsRegFlg = SMS_TRUE;                                                  /* 记录此状态                               */
        g_ucCurSendDomain = SMS_SEND_DOMAIN_CS;
    }
    else
    {
        g_ucCsRegFlg = SMS_FALSE;                                                 /* 记录此状态                               */

        SMC_ComCsMtErr( SMR_SMT_ERROR_NO_SERVICE, g_SmcCsEnt.SmcMt.ucTi);         /* 调用CS域MT实体的处理                     */
        SMC_ComCsMoErr( SMR_SMT_ERROR_NO_SERVICE, g_SmcCsEnt.SmcMo.ucTi);         /* 调用CS域MO实体的处理                     */
    }
    SMS_AttachFlag(SMS_SEND_DOMAIN_CS,g_ucCsRegFlg);

    return;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

