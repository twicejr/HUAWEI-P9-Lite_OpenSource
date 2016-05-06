/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name:          SmcSmrApi.c
  Description:        SMC和SMR的API函数
  Function List:
               1.  SMC_SmrApiDataReq
               2.  SMC_SmrApiEstReq
               3.  SMC_SmrApiAbortReq
               4.  SMC_SmrApiRelReq
               5.  SMR_SmcApiDataInd
               6.  SMR_SmcApiEstInd
               7.  SMR_SmcApiErrorInd
  History:
      1.   张志勇      2004.03.09   新规作成
      2.   张志勇   2005.06.28   对应测试记录06-19修改
  3. Date:          2006-08-17
     Author:        郜东东
     Modification:  OSA优化整改,问题单号:A32D05312
  4. Date:          2006-12-30
     Author:        x51137
     Modification:  A32D07797
  5. Date         : 2007-04-06
     Author       : h44270
     Modification : 问题单号:A32D10113
  6. Date         : 2007-04-23
     Author       : z40661
     Modification : 问题单号:A32D09426
  7. Date:          2007-08-20
     Author:        z40661
     Modification:  问题单号:A32D12705
  8. Date:          2008-12-11
     Author:        f62575
     Modification:  问题单号:AT2D07461,短信发送失败，但是在事件上报栏中上报成功
  9. Date:          2008-12-17
     Author:        f62575
     Modification:  问题单号:AT2D07651,PS域接收短信，用户确认超时错误的回复了CP-ERROR，应回复RP-ERROR
 10.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
 11.日    期   : 2009年3月25日
    作    者   : f62575
    修改内容   : AT2D10419, 由于启动CS域短信连发功能，但CS域短信发送失败时，通过PS域短信发送，SMC层错误的将发送域修改为CS层，并没有通过PS域发送；
 12.日    期   : 2009年5月23日
    作    者   : f62575
    修改内容   : AT2D10986, 2G下PS域发送短信连续两次发送失败后，
                 CP层再次超时事件与RP层超时事件同时到达SMS模块内存的错误操作，
                 导致单板的复位
 13.日    期   : 2009年5月10日
    作    者   : f62575
    修改内容   : AT2D12319, NAS R6升级；
 14.日    期   : 2010年1月9日
    作    者   : f62575
    修改内容   : 问题单号：AT2D16263，无效代码删除 Sms_IsAllowSleep SMC_SndEstReq

 15.日    期   : 2010年04月28日
    作    者   : z40661
    修改内容   : 问题单号AT2D16570
                 接收到DATA-IND消息的无效的消息类型，应回复CP-ERROR错误原因值97
                 接收到DATA-IND消息的无CP-USER-DATA，应回复CP-ERROR错误原因值96
                 非SMC_MO_WAIT_FOR_CP_ACK状态，应回复CP-ERROR错误原因值98
 16.日    期   : 2010年9月26日
    作    者   : 傅映君/f62575
    修改内容   : 问题单DTS2010092500635：GCF用例51010 34。2。8。2失败，原因
                 为第29步UE给SS的RP-ERROR没有发送
*******************************************************************************/
#include "smsinclude.h"
#include "NasGmmInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -save -e958 */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SMC_SMRAPI_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -e438 -e830*/

/***********************************************************************
*  MODULE   : SMR_SndReportReq
*  FUNCTION : 制作并发送SMRL_REPORT_REQ原语
*  INPUT    : VOS_UINT8 ucMti-------------消息类型指示
*             VOS_UINT8 ucCause-----------错误原因值
*             VOS_UINT8 ucRpCause---------Rp原因值
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : VOS_VOID
*  HISTORY  :
*  1.  张志勇   04-10-22  新规作成
*  2.  张志勇   05-01-12  对应接口修改
*  3.  Date         : 2006-04-26
*      Author       : 郜东东
*      Modification : 修改了无法连续接收多条短信的问题,问题单号:A32D02986
   4. Date         : 2007-04-07
      Author       : h44270
      Modification : 问题单号:A32D10113
   5.日    期   : 2009年3月23日
     作    者   : f62575
     修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
************************************************************************/
VOS_VOID SMR_SndReportReq(
    VOS_UINT8    ucMti,                                        /* 消息类型指示                             */
    VOS_UINT8    ucFcs,                                        /* 错误原因值                               */
    VOS_UINT8    ucRpCause,                                    /* Rp原因值                                 */
    VOS_UINT8    ucMoreMsg                                     /* 后面是否还有更多短消息的标志             */
)
{

    SMT_SMR_DATA_STRU    *pSndMsg;                                           /* 定义存放发送消息的指针                   */
    SMT_SMR_DATA_TEMP_STRU  *pTempMsg=VOS_NULL_PTR;
    VOS_UINT8            ucSndMsgLen;                                        /* 定义发送的原语的长度                     */

    if( MN_MSG_RP_MTI_UP_RP_ERR == ucMti )
    {                                                                           /* 发送的为RP-ERROR                         */
        ucSndMsgLen = (VOS_UINT8)sizeof( SMT_SMR_DATA_STRU ) + (VOS_UINT8)(sizeof( VOS_UINT8 ) * 5);     /* 计算数据长度                             */
        pSndMsg     = (SMT_SMR_DATA_STRU *)SMS_Malloc(ucSndMsgLen);        /* 申请发送原语的空间                       */
        if ( VOS_NULL_PTR == pSndMsg )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMR_SndReportReq:ERROR: Memory allocation fails" );
            return;
        }
        pTempMsg = (SMT_SMR_DATA_TEMP_STRU *)pSndMsg;
        SMS_Memset(pTempMsg,0,ucSndMsgLen);                                      /* 初始化清零                               */
        pTempMsg->ulDataLen   = (sizeof( VOS_UINT8 ) * 4) + (sizeof( VOS_UINT8 ) * 5);       /* 填写数据长度                             */
        pTempMsg->aucData[0]  = ucMti;                                           /* 填写消息类型                             */
        pTempMsg->aucData[2]  = 1;                                               /* 填写RP原因值长度                         */
        pTempMsg->aucData[3]  = ucRpCause;                                       /* 填写RP原因值                             */
        pTempMsg->aucData[4]  = MN_MSG_RP_USER_DATA_IEI;                            /* 填写用户数据类型                         */
        pTempMsg->aucData[5]  = sizeof( VOS_UINT8 ) * 3;                             /* 填写TPDU长度                             */
        pTempMsg->aucData[6]  = 0;                                               /* 填写TPDU消息类型                         */
        pTempMsg->aucData[6] |= MN_MSG_TP_MTI_DELIVER_REPORT;                       /* 填写TPDU消息类型                         */
        pTempMsg->aucData[7]  = ucFcs;                                           /* 填写TP原因值                             */
        pTempMsg->aucData[8]  = 0x00;                                            /* 填写参数指示TP-PI                        */
    }
    else
    {                                                                           /* 发送的为RP-ACK                           */
        pSndMsg = (SMT_SMR_DATA_STRU *)
                    SMS_Malloc( sizeof( SMT_SMR_DATA_STRU ) );               /* 申请发送原语的空间                       */
        if ( VOS_NULL_PTR == pSndMsg )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMR_SndReportReq:ERROR: Memory allocation fails" );
            return;
        }
        SMS_Memset(pSndMsg,0,sizeof( SMT_SMR_DATA_STRU ));                   /* 初始化清零                               */
        pSndMsg->ulDataLen  = 2;                                                /* 填写数据长度                             */
        pSndMsg->aucData[0] = ucMti;                                            /* 填写消息类型                             */
    }

    SMS_RcvMnReportReq(pSndMsg);                               /* 发送SMRL_REPORT_REQ原语                  */

    /*释放pSndMsg*/
    SMS_Free(pSndMsg);


}
/*lint +e438 +e830*/

/*******************************************************************************
  Module:   SMC_SmrApiDataReq
  Function: SMR指示SMC传输MT数据
  Input:    VOS_UINT8     *pucData     数据首地址
            VOS_UINT32     ulLen        数据长度
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.张志勇      2004.03.09   新规作成
      2.日    期   : 2010年9月26日
        作    者   : 傅映君/f62575
        修改内容   : 问题单DTS2010092500635：GCF用例51010 34。2。8。2失败，原因
                     为第29步UE给SS的RP-ERROR没有发送
      3.日    期   : 2011年12月26日
        作    者   : z00161729
        修改内容   : V7R1 PhaseIV支持L短信修改
      4.日    期   : 2014年6月24日
        作    者   : w00167002
        修改内容   : DSDS III项目
*******************************************************************************/
VOS_VOID SMC_SmrApiDataReq(
                        VOS_UINT8     *pucData,                                     /* 数据首地址                               */
                        VOS_UINT16    usLen                                         /* 数据长度                                 */
                      )
{
    VOS_UINT16   usMsgLen;                                                          /* 定义存储消息长度的变量                   */
    VOS_UINT32   TempAddr;
    VOS_UINT8    aucSndMsg[255];

    if(SMC_MT_WAIT_FOR_RP_ACK == g_SmcPsEnt.SmcMt.ucState)
    {
        /* PS域的实体在等待RP-ACK                   */
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
        {
            usMsgLen = ((sizeof(SMS_LMM_DATA_REQ_STRU) - 4)
                                       + usLen) + SMC_MSG_HDR_LEN;                          /* 获得消息的长度                           */
            if(usLen < SMC_SND_MSG_MIN_LEN)
            {                                                                   /* 消息的长度较小                           */
                usMsgLen = sizeof(SMS_LMM_DATA_REQ_STRU);
            }


            SMS_Memset( aucSndMsg,0,usMsgLen );                                 /* 初始化为零                               */

            ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[0]
                            = (VOS_UINT8)(g_SmcPsEnt.SmcMt.ucTi << 4) | 0x80;              /* 赋值TI                                   */
            ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[0]
                            |= NAS_PD_SMS;                                      /* 填写PD                                   */
            ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* 填写消息类型                             */
            TempAddr = (VOS_UINT32)(&(((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[2]));


            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* 复制消息                                 */

            ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.ulSmsMsgSize =
                      usLen + SMC_MSG_HDR_LEN;                                  /* 赋值消息长度                             */

            g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg     = SMS_Malloc(usMsgLen);        /* 申请内存                                 */
            if ( VOS_NULL_PTR == g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Memory allocation fails" );
                return;
            }
            SMS_Memset( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg,0,usMsgLen );          /* 初始化清零                               */

            SMS_Memcpy( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg,
                        aucSndMsg,
                        usMsgLen );                                             /* 缓存消息                                 */
            g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = usMsgLen;                    /* 缓存消息长度                             */

            /* 标记缓存的消息类型 */
            g_SmcPsEnt.SmcMt.enHoldSndMsgType       = NAS_SMS_HOLD_MSG_LTE_MT_RP_ACK;

            /* 启动timer tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiDataReq: TimerStart: tc1m" );
            if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_PS_TC1M_MT ) )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Start Tc1m fails" );
                SMS_Free( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg );                       /* 释放缓存的消息                           */
                g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                           /* 初始化消息长度                           */
                g_SmcPsEnt.SmcMt.enHoldSndMsgType       = NAS_SMS_HOLD_MSG_BUTT;
                return;
            }

            g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;

            NAS_SMS_ChangePsMtEntityState(SMC_MT_WAIT_FOR_CP_ACK);

            /* 发送CP-DATA消息 */
            if (VOS_FALSE == NAS_SMS_SndLmmCpDataReq(aucSndMsg, usMsgLen))
            {
                PS_MEM_FREE(WUEPS_PID_SMS, g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg);
                g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;
                g_SmcPsEnt.SmcMt.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
                return;
            }
        }
        else
#endif
        {                                                                       /* Message Reference相等                    */
            usMsgLen = ((sizeof(PMMSMS_UNITDATA_REQ_STRU) - 4)
                            + usLen) + SMC_MSG_HDR_LEN;                          /* 获得消息的长度                           */
            if(usLen < SMC_SND_MSG_MIN_LEN)
            {                                                                   /* 消息的长度较小                           */
                usMsgLen = sizeof(PMMSMS_UNITDATA_REQ_STRU);
            }


            SMS_Memset( aucSndMsg,0,usMsgLen );                                 /* 初始化为零                               */

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[0]
                            = (VOS_UINT8)(g_SmcPsEnt.SmcMt.ucTi << 4) | 0x80;              /* 赋值TI                                   */
            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[0]
                            |= NAS_PD_SMS;                                      /* 填写PD                                   */
            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* 填写消息类型                             */
            TempAddr = (VOS_UINT32)(&(((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[2]));


            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* 复制消息                                 */

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.ulNasMsgSize =
                      usLen + SMC_MSG_HDR_LEN;                                  /* 赋值消息长度                             */

            g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg     = SMS_Malloc(usMsgLen);        /* 申请内存                                 */
            if ( VOS_NULL_PTR == g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Memory allocation fails" );
                return;
            }
            SMS_Memset( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg,0,usMsgLen );          /* 初始化清零                               */

            SMS_Memcpy( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg,
                        aucSndMsg,
                        usMsgLen );                                             /* 缓存消息                                 */
            g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = usMsgLen;                    /* 缓存消息长度                             */

            /* 标记缓存的消息类型 */
            g_SmcPsEnt.SmcMt.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_GU_MT_RP_ACK;

            /* 启动timer tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiDataReq: TimerStart: tc1m" );
            if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_PS_TC1M_MT ) )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Start Tc1m fails" );
                SMS_Free( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg );                       /* 释放缓存的消息                           */
                g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                           /* 初始化消息长度                           */
                g_SmcPsEnt.SmcMt.enHoldSndMsgType       = NAS_SMS_HOLD_MSG_BUTT;
                return;
            }

            g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;

            NAS_SMS_ChangePsMtEntityState(SMC_MT_WAIT_FOR_CP_ACK);

            SMC_SndGmmMsg(aucSndMsg, PMMSMS_UNITDATA_REQ, usMsgLen);            /* 发送消息                                 */
        }
    }
    else if(SMC_MT_WAIT_FOR_RP_ACK == g_SmcCsEnt.SmcMt.ucState)
    {                                                                           /* CS域的实体在等待RP-ACK                   */
        {                                                                       /* Message Reference相等                    */
            usMsgLen = ((sizeof(MMSMS_DATA_REQ_STRU)-4) + usLen) + SMC_MSG_HDR_LEN; /* 获得消息的长度                           */
            if(usLen < SMC_SND_MSG_MIN_LEN)
            {                                                                   /* 消息的长度较小                           */
                usMsgLen = sizeof(MMSMS_DATA_REQ_STRU);
            }

            SMS_Memset(aucSndMsg,0,usMsgLen);                                   /* 初始化清零                               */

            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->ulTi = g_SmcCsEnt.SmcMt.ucTi;  /* 赋值TI                                   */
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[0]
                            = (VOS_UINT8)(g_SmcCsEnt.SmcMt.ucTi << 4) | 0x80;              /* 填写消息中cp_data的pd ti                 */
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[0]
                            |= NAS_PD_SMS;
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* 填写消息中cp_data的消息类型              */

           TempAddr = (VOS_UINT32)(&(((MMSMS_DATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[2]));

            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* 复制消息 填写来自TAF的rpdu               */

            ((MMSMS_DATA_REQ_STRU *)aucSndMsg)->SmsMsg.ulNasMsgSize =
                           usLen + SMC_MSG_HDR_LEN;                             /* 赋值消息长度                             */

            g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg     = (VOS_VOID *)SMS_Malloc(usMsgLen);/* 申请内存空间                             */
            if ( VOS_NULL_PTR == g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Memory allocation fails" );
                return;
            }
            SMS_Memcpy( g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg, aucSndMsg, usMsgLen); /* 缓存消息                                 */
            g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = usMsgLen;                    /* 缓存消息长度                             */

            /* 启动定时器tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiDataReq: TimerStart: tc1m" );
            if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_CS_TC1M_MT ) )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Start Tc1m fails" );
                SMS_Free(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg);
                g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                               /* 清除消息长度                             */
                return;
            }

            SMC_SndMmMsg(aucSndMsg, MMSMS_DATA_REQ, usMsgLen);                  /* 发送MM消息                               */

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_WAIT_FOR_CP_ACK);

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiDataReq:NORMAL:SMS state = SMC_MT_WAIT_FOR_CP_ACK");
        }
    }
    else if(SMR_WAIT_FOR_RP_ACK == g_SmrEnt.SmrMo.ucState)
    {
        /*判断是需要想PS域发送还是CS域发送*/
        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {
            usMsgLen = ((sizeof(MMSMS_DATA_REQ_STRU)-4) + usLen) + SMC_MSG_HDR_LEN; /* 获得消息的长度                           */
            if(usLen < SMC_SND_MSG_MIN_LEN)
            {                                                                   /* 消息的长度较小                           */
                usMsgLen = sizeof(MMSMS_DATA_REQ_STRU);
            }

            SMS_Memset(aucSndMsg,0,usMsgLen);                                   /* 初始化清零                               */


            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->ulTi = g_SmcCsEnt.SmcMo.ucTi;
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[0]
                            = (VOS_UINT8)(g_SmcCsEnt.SmcMo.ucTi&0x07)<<4;
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[0]
                            |= NAS_PD_SMS;
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* 填写消息中cp_data的消息类型              */

            TempAddr = (VOS_UINT32)(&(((MMSMS_DATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[2]));
            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );

            ((MMSMS_DATA_REQ_STRU *)aucSndMsg)->SmsMsg.ulNasMsgSize =
                           usLen + SMC_MSG_HDR_LEN;                             /* 赋值消息长度                             */

            SMC_SndMmMsg(aucSndMsg, MMSMS_DATA_REQ, usMsgLen);                  /* 发送MM消息                               */
        }
        else
        {
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                usMsgLen = ((sizeof(SMS_LMM_DATA_REQ_STRU) - 4)
                          + usLen) + SMC_MSG_HDR_LEN;                          /* 获得消息的长度                           */
                if(usLen < SMC_SND_MSG_MIN_LEN)
                {                                                                   /* 消息的长度较小                           */
                    usMsgLen = sizeof(SMS_LMM_DATA_REQ_STRU);
                }

                SMS_Memset( aucSndMsg,0,usMsgLen );                                 /* 初始化为零                               */

                ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[0]
                                = (VOS_UINT8)(g_SmcPsEnt.SmcMo.ucTi & 0x07)<<4;

                ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[0]
                                |= NAS_PD_SMS;                                      /* 填写PD                                   */
                ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[1]
                                = SMC_DATA_TYPE_CP_DATA;                            /* 填写消息类型                             */

                TempAddr = (VOS_UINT32)(&(((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[2]));

                SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* 复制消息                                 */

                ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.ulSmsMsgSize =
                          usLen + SMC_MSG_HDR_LEN;                                  /* 赋值消息长度                             */

                /* 发送CP-DATA消息 */
                (VOS_VOID)NAS_SMS_SndLmmCpDataReq(aucSndMsg, usMsgLen);
            }
            else
#endif
            {
                usMsgLen = ((sizeof(PMMSMS_UNITDATA_REQ_STRU) - 4)
                          + usLen) + SMC_MSG_HDR_LEN;                          /* 获得消息的长度                           */
                if(usLen < SMC_SND_MSG_MIN_LEN)
                {                                                                   /* 消息的长度较小                           */
                    usMsgLen = sizeof(PMMSMS_UNITDATA_REQ_STRU);
                }

            SMS_Memset( aucSndMsg,0,usMsgLen );                                 /* 初始化为零                               */

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[0]
                            = (VOS_UINT8)(g_SmcPsEnt.SmcMo.ucTi & 0x07)<<4;

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[0]
                            |= NAS_PD_SMS;                                      /* 填写PD                                   */
            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* 填写消息类型                             */

            TempAddr = (VOS_UINT32)(&(((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[2]));

            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* 复制消息                                 */

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.ulNasMsgSize =
                      usLen + SMC_MSG_HDR_LEN;                                  /* 赋值消息长度                             */

                SMC_SndGmmMsg(aucSndMsg, PMMSMS_UNITDATA_REQ, usMsgLen);
            }
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_ERROR, "SMC_SmrApiDataReq:ERROR:Invalid SMS-R state ");
    }
}

/*******************************************************************************
  Module:   SMC_SmrApiEstReq
  Function: 建立SMC实体及信令连接
  Input:    VOS_UINT8     *pucData     数据(包含RP-DATA长度和内容段)首地址
            VOS_UINT32     ulLen       数据长度
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇      2004.03.09   新规作成
      2.   张志勇   2005.06.28   对应测试记录06-19修改
      3. Date         : 2006-04-26
         Author       : 郜东东
         Modification : 修改了实际发送域和设置域不同的问题,问题单号:A32D03350
      4.日    期   : 2011年11月28日
        作    者   : z00161729
        修改内容   : 增加支持L模发短信的处理
      5.日    期  : 2013年03月13日
        作    者  : z00214637
        修改内容  : BodySAR项目
      6.日    期   : 2014年6月24日
        作    者   : w00167002
        修改内容   : DSDS III项目
*******************************************************************************/
VOS_VOID SMC_SmrApiEstReq(
    VOS_UINT8                           ucCurSendDomain,
    VOS_UINT8                           *pucData,                                       /* 数据首地址                               */
    VOS_UINT32                          ulLen                                           /* 数据长度                                 */
)
{
    VOS_UINT8           aucTempMsg[255];
    VOS_UINT8           ucTi;

    SMS_LOG(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: step into function.");
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: ucCurSendDomain.", ucCurSendDomain);
    /*****************************进行实际的发送******************************/
    if ((SMS_SEND_DOMAIN_CS != ucCurSendDomain)
     && ( SMS_SEND_DOMAIN_PS != ucCurSendDomain ))
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMC_SmrApiEstReq: invalid send domain." );
        return;
    }

    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: g_SmcCsEnt.SmcMo.ucState.", g_SmcCsEnt.SmcMo.ucState);
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: g_SmcPsEnt.SmcMo.ucState.", g_SmcPsEnt.SmcMo.ucState);

    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: ucCurSendDomain.", ucCurSendDomain);


    if ( SMS_SEND_DOMAIN_PS == ucCurSendDomain )
    {   /*如果是在PS域发送*/
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcCsEnt.SmcMo.ucState)
        {
            SMC_SndMmCpAckMsg(g_SmcCsEnt.SmcMo.ucTi);
            SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucTi);                                /* 指示MM释放MM连接                         */
            g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
            SMS_LOG(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);

            SMS_SendMnMoLinkCloseInd();
        }

        SMS_LOG1(PS_LOG_LEVEL_NORMAL,
                 "SMC_SmrApiEstReq: g_SmcPsEnt.SmcMo.ucState.",
                 g_SmcPsEnt.SmcMo.ucState);
        if ((SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState)
         && (SMC_MO_WAIT_TO_SND_CP_ACK != g_SmcPsEnt.SmcMo.ucState))
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMS:SMC_SmrApiEstReq: PS entity is inavailable." );
            return;
        }

        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcPsEnt.SmcMo.ucState)
        {
            g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
            SMS_SendMnMoLinkCloseInd();
        }

        /* 实体在空闲状态                           */
        g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg  = (VOS_VOID *)SMS_Malloc( ulLen );    /* 存储数据                                 */
        if ( VOS_NULL_PTR == g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMS:SMC_SmrApiEstReq: Memory allocation fails" );
            return;
        }
        SMS_Memcpy( g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg, pucData, ulLen );     /* 备份消息                                 */
        g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = ulLen;                       /* 存储数据长度                             */

        /* DSDS需要先资源申请再发est req建链请求 */
        NAS_SMS_ChangePsMoEntityState(SMC_MO_GMM_CONN_PENDING);

#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
        {
            /* 当前驻留在L模 */
            NAS_SMS_SndLmmEstReq(RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL);
        }
        else
#endif
        {
            SMS_Memset( aucTempMsg,0,sizeof(PMMSMS_EST_REQ_STRU) );             /* 初始化清零                               */
            ((PMMSMS_EST_REQ_STRU *)aucTempMsg)->ulEstCause = RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL;  /* 填写原因值                               */
            SMC_SndGmmMsg( aucTempMsg,
                           PMMSMS_EST_REQ,
                           sizeof(PMMSMS_EST_REQ_STRU) );                       /* 指示GMM建立信令连接                      */
        }

        SMS_LOG( PS_LOG_LEVEL_NORMAL,
                 "SMC_SmrApiEstReq: SMS state = SMC_MO_GMM_CONN_PENDING" );
    }
    else
    {   /*如果是在CS域发送*/
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcPsEnt.SmcMo.ucState)
        {
            SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ACK,
                               0XFF,
                               g_SmcPsEnt.SmcMo.ucTi );                         /* 向网侧回确认                             */
            g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
            SMS_LOG( PS_LOG_LEVEL_NORMAL,
                     "SMC_SmrApiEstReq: SMS state = SMC_MO_IDLE" );

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);

            SMS_SendMnMoLinkCloseInd();
        }

        /*确认C层状态是否可以发送消息*/
        if ((SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
         && (SMC_MO_WAIT_TO_SND_CP_ACK != g_SmcCsEnt.SmcMo.ucState))
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMC_SmrApiEstReq: CS entity is inavailable." );
            return;
        }

        /*备份RP-DATA数据段和长度到C层缓存；*/
        g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg  = (VOS_VOID *)SMS_Malloc( ulLen );
        if ( VOS_NULL_PTR == g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMS:SMC_SmrApiEstReq: Memory allocation fails" );
            return;
        }
        SMS_Memcpy(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg, pucData, ulLen);
        g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = ulLen;

        /*指示MM建立MM连接                    */
        /* 状态迁移                                 */
        SMS_Memset( aucTempMsg,0,sizeof(MMSMS_EST_REQ_STRU) );
        ucTi = (VOS_UINT8)(((g_SmcCsEnt.SmcMo.ucTi + 1) % 0x07) | 0x08);
        (( MMSMS_EST_REQ_STRU* )aucTempMsg)->ulTi       = ucTi;                      /* 填写Ti                                   */
        (( MMSMS_EST_REQ_STRU* )aucTempMsg)->ulEstCause = RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL;   /* 填写原因值                               */

        /* 备份前一个ti*/
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcCsEnt.SmcMo.ucState)
        {
            g_SmcCsEnt.SmcMo.ucPreTi = g_SmcCsEnt.SmcMo.ucTi;
        }

        NAS_SMS_ChangeCsMoEntityState(SMC_MO_MM_CONN_PENDING);

        SMC_SndMmMsg( aucTempMsg, MMSMS_EST_REQ, sizeof(MMSMS_EST_REQ_STRU) );

        g_SmcCsEnt.SmcMo.ucTi = ucTi;

        SMS_LOG( PS_LOG_LEVEL_NORMAL,
                 "SMC_SmrApiEstReq: SMS state = SMC_MO_MM_CONN_PENDING" );
    }
    return;
}
/*******************************************************************************
  Module:   SMC_SmrApiAbortReq
  Function: SMR指示终止SMS过程
  Input:    VOS_UINT8     ucCause     终止原因
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇      2004.03.09   新规作成
      2.   x51137      20061230    A32D07797
      3. Date         : 2007-04-06
         Author       : h44270
         Modification : 问题单号:A32D10113
      4. Date         : 2007-04-23
         Author       : z40661
         Modification : 问题单号:A32D09426
      5. Date         : 2012-11-29
         Author       : f62575
         Modification : 问题单号:DTS2012112902674，支持协议的ABORT流程
                        TR1M超时，非SMMA流程要求给网络先发CP-ERROR后发RELEASE消息
      6. Date         : 2013-01-03
         Author       : f62575
         Modification : 问题单号:DTS2012123101285, 支持协议的ABORT流程
                        TR1M超时，非SMMA流程要求给网络先发CP-ERROR后发RELEASE消息
      7.日    期   : 2014年6月24日
        作    者   : w00167002
        修改内容   : DSDS III项目

*******************************************************************************/
VOS_VOID SMC_SmrApiAbortReq(
                        VOS_UINT8     ucCause                                       /* 终止原因                                 */
                        )
{
    if(SMR_SMC_ABORT_CAUSE_TR1M_EXP == ucCause)
    {                                                                           /* 原因值为TR1M超时                         */
        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {
            /* TR1M超时，ABORT流程向网侧指示错误                           */
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_PROT_ERR_UNSPEC,
                              g_SmcCsEnt.SmcMo.ucTi );

            if(SMC_MO_MM_CONN_PENDING == g_SmcCsEnt.SmcMo.ucState)
            {                                                                   /* 实体的状态是SMC_MO_MM_CONN_PENDING       */
                if (0 != g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg);                     /* 释放消息                                 */
                    g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                       /* 清除消息长度                             */
                }
                SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucTi);                           /* 释放MM连接                               */
            }
            else
            {
                if(0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg);
                    g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
                }

                /* 停止timer tc1m */
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiAbortReq: TimerStop: TC1M" );
                if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
                {
                    return;
                }

                /* g_SmcCsEnt.SmcMo.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
                g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

                SMC_SndRelReq( g_SmcCsEnt.SmcMo.ucTi );                         /* 释放MM连接                               */
            }
            if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
            {
                g_SmcCsEnt.SmcMo.ucCpAckFlg              = SMS_FALSE;
                SMS_SendMnMoLinkCloseInd();
            }
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);
        }
        else
        {                                                                       /* PS域的SMC实体状态为非空                  */
            if(SMC_MO_GMM_CONN_PENDING == g_SmcPsEnt.SmcMo.ucState)
            {                                                                   /* 实体的状态SMC_MO_GMM_CONN_PENDING        */
                if (0 != g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg);                     /* 释放消息                                 */
                    g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                       /* 清除消息长度                             */
                }
            }
            else
            {
                if (0 != g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg);
                    g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
                    g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
                }

                /* 停止timer tc1m */
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiAbortReq: TimerStop: TC1M" );
                if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_PS_TC1M_MO ) )
                {
                    return;
                }

                /* g_SmcPsEnt.SmcMo.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
                g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

#if (FEATURE_ON == FEATURE_LTE)
                if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
                {
                    /* 当前驻留在L模,构造SMS_LMM_DATA_REQ消息，通过NAS_SMS_SndLmmDataReq发送 */
                    NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR, SMS_CP_ERR_PROT_ERR_UNSPEC, g_SmcPsEnt.SmcMo.ucTi);
                }
                else
#endif
                {
                    SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                                       SMS_CP_ERR_PROT_ERR_UNSPEC,
                                       g_SmcPsEnt.SmcMo.ucTi );                     /* 向网侧指示错误                           */
                }

            }
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);
        }
    }
    else if(SMR_SMC_ABORT_CAUSE_TR2M_EXP == ucCause)
    {                                                                           /* 原因值为TR2M超时                         */
        if(SMC_MT_MM_CONN_EST == g_SmcCsEnt.SmcMt.ucState)
        {                                                                       /* CS域的SMC实体状态为SMC_MT_MM_CONN_EST    */
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_PROT_ERR_UNSPEC,
                              g_SmcCsEnt.SmcMt.ucTi );                          /* 向网侧指示错误                           */
            SMC_SndRelReq( g_SmcCsEnt.SmcMt.ucTi );                             /* 释放MM连接                               */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MT_IDLE");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);
        }
        else if(SMC_MT_WAIT_FOR_RP_ACK == g_SmcCsEnt.SmcMt.ucState)
        {
            SMR_SndReportReq(MN_MSG_RP_MTI_UP_RP_ERR,
                             0xD2,
                             SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR,
                             0 );
            #if 0
            SMC_SndRelReq( g_SmcCsEnt.SmcMt.ucTi );                           /* 释放MM连接                               */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MT_IDLE");
            g_SmcCsEnt.SmcMt.ucState = SMC_MT_IDLE;
            #endif
        }
        else if(SMC_MT_WAIT_FOR_RP_ACK == g_SmcPsEnt.SmcMt.ucState )
        {
            SMR_SndReportReq( MN_MSG_RP_MTI_UP_RP_ERR,
                              0xD2,
                              SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR,
                              0 );
                        /* 向网侧指示错误                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MT_IDLE");

            NAS_SMS_ChangePsMtEntityState(SMC_MT_IDLE);
        }
        else
        {

        }
        /*end by zhoujun40661 2006-10-25 for CNMA*/
    }
    else
    {

    }
}
/*******************************************************************************
  Module:   SMC_SmrApiRelReq
  Function: SMR指示SMC释放MM连接
  Input:    VOS_UINT8     ucRelCause     终止原因
            VOS_UINT8     ucMtFlg        是MT过程
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   张志勇      2004.03.09   新规作成
      2. Date         : 2007-04-06
         Author       : h44270
         Modification : 问题单号:A32D10113
      3.日    期   : 2014年6月24日
        作    者   : w00167002
        修改内容   : DSDS III项目
*******************************************************************************/
VOS_VOID SMC_SmrApiRelReq(
                      VOS_UINT8     ucRelCause,                                     /* 释放原因                                 */
                      VOS_UINT8     ucMtFlg                                         /* 是MT过程                                 */
                      )
{
    VOS_UINT8   aucTempMsg[255];

    if(SMS_FALSE == ucMtFlg)
    {                                                                           /* 释放mo过程中的mm连接                     */
        if(SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
        {                                                                       /* 需要发送CP-ACK                           */
            SMS_Memset(aucTempMsg,0,sizeof(MMSMS_DATA_REQ_STRU));                /* 初始化清零                               */

            if(SMR_SMC_REL_CAUSE_PS_MULTI == ucRelCause)
            {
                ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->ulTi =
                                        g_SmcCsEnt.SmcMo.ucPreTi;               /* 赋值ti                                   */

                ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[0] =
                                       (g_SmcCsEnt.SmcMo.ucPreTi & 0x07) << 4;  /* 填写ti                                   */
            }
            else
            {
                ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->ulTi =
                                        g_SmcCsEnt.SmcMo.ucTi;                  /* 赋值ti                                   */

                ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[0] =
                                        (g_SmcCsEnt.SmcMo.ucTi & 0x07) << 4;    /* 填写ti                                   */
            }
            ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.ulNasMsgSize
                = SMC_MSG_HDR_LEN;                                              /* 赋值消息长度                             */
            ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[0]
                |= NAS_PD_SMS;                                                  /* 填写pd                                   */
            ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[1]
                = SMC_DATA_TYPE_CP_ACK;                                         /* 填写消息类型                             */
            SMC_SndMmMsg(aucTempMsg,MMSMS_DATA_REQ,sizeof(MMSMS_DATA_REQ_STRU)); /* 发送消息                                 */
        }


        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {                                                                       /* 实体在等待发送CP_ACK                     */
            if(0 != g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
            {                                                                   /* 有存储的接收消息                         */
                if(SMS_TRUE != g_SmcCsEnt.SmcMo.ucCpAckFlg)
                {
                    if (0 != g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                    {
                        SMS_Free(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg);                 /* 释放存储的消息                           */
                        g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                   /* 清除消息长度                             */
                    }
                }
                else
                {
                }
            }
            else if(0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
            {                                                                   /* 有存储的发送消息                         */
                SMS_Free(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg);                     /* 释放存储的消息                           */
                g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                       /* 清除消息长度                             */
            }
            else
            {

            }

            /* 停止timer tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: TimerStop: TC1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
            {
                    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: fail to stop TC1M." );
            }

            g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

            if (SMR_SMC_REL_CAUSE_PS_MULTI == ucRelCause)
            {
                SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucPreTi);                        /* 指示MM释放MM连接                         */
            }
            else
            {
                SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucTi);                           /* 指示MM释放MM连接                         */

                PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, ":NORMAL:SMS state = SMC_MO_IDLE");

                NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);
            }

            if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
            {
                g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
                SMS_SendMnMoLinkCloseInd();
            }
        }
        else if(SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState)
        {
            if(SMR_SMC_REL_CAUSE_PS_MULTI == ucRelCause)
            {

            }
            else
            {
                if(0 != g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg);
                    g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;
                }
                else if(0 != g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg);
                    g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
                    g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
                }
                else
                {

                }

                /* 停止timer tc1m */
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: TimerStop: TC1M" );
                if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_PS_TC1M_MO ) )
                {
                    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: fail to stop TC1M." );
                }

                /* g_SmcPsEnt.SmcMo.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
                g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

                PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiRelReq:NORMAL:SMS state = SMC_MO_IDLE");


                NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);
            }
        }
        else
        {

        }
    }
    else
    {
        if( (SMC_MT_WAIT_FOR_CP_ACK != g_SmcCsEnt.SmcMt.ucState)
                    && (SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState) )
        {
            /* 停止timer tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: TimerStop: TC1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
            {
                return;
            }

            /* g_SmcCsEnt.SmcMt.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
            g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;
        }
        if(SMC_MT_MM_CONN_EST == g_SmcCsEnt.SmcMt.ucState)
        {                                                                       /* 实体在等待高层的确认                     */
            SMC_SndRelReq( g_SmcCsEnt.SmcMt.ucTi );                             /* 指示MM释放MM连接                         */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiRelReq:NORMAL:SMS state = SMC_MT_IDLE");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);
        }

    }
}

/*******************************************************************************
Module:   SMR_SmcApiDataInd
Function: 向SMR上报RP-ACK/RP-ERROR
Input:    VOS_UINT8     *pucData        数据首地址
VOS_UINT32        ulLen          数据长度
Output:   VOS_VOID
NOTE:
Return:   VOS_VOID
History:
1.   张志勇   2004.03.10   新规作成
2.   Date         : 2007-04-06
     Author       : h44270
     Modification : 问题单号:A32D10113
3. 日   期   : 2012年8月29日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
4.日    期   :2014年9月28日
  作    者   :s00217060
  修改内容   :for cs_err_log
*******************************************************************************/
VOS_UINT32 SMR_SmcApiDataInd(
                       VOS_UINT8 *pucData,                                          /* 数据首地址                               */
                       VOS_UINT32  ulLen                                             /* 数据长度                                 */
                      )
{
    VOS_UINT32  ulRet = VOS_OK;
    NAS_OM_SMS_MO_REPORT_STRU stSmsMoReportPara;

    stSmsMoReportPara.ulCause = 0;
    stSmsMoReportPara.ucSmsMr = g_SmrEnt.SmrMo.ucMr;

    /*When a message is received that is too short to contain a complete message
    type information element and Message Reference, that message shall be ignored*/
    if(ulLen < 2)
    {                                                                       /* 不存在强制IE                             */
        SMR_SndRpErrorReq(g_SmrEnt.SmrMo.ucMr,
                         SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ,
                         SMS_TRUE );

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcApiDataInd:WARNING:NW->SMS SMS ERROR Len is too short!");
        return SMR_MSG_TOO_SHORT_ERROR;
    }

    if (SMR_WAIT_FOR_RP_ACK == g_SmrEnt.SmrMo.ucState)
    {                                                                           /* 实体在等待RP_ACK                         */
        switch(pucData[0])
        {
        case SMR_NTM_DATA_TYPE_RP_DATA:
            /* 向网侧指示错误          */
            SMR_SndRpErrorReq( g_SmrEnt.SmrMo.ucMr,
                               SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE,
                               SMS_TRUE );                                          /* 与协议状态不对应,发送RP_ERROR            */
            ulRet = SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE;
            break;

        case SMR_NTM_DATA_TYPE_RP_ACK:

            /*Whenever any RP ACK message is received specifying a Message Reference
            which is not associated with an active SM transfer, the mobile station
            shall discard the message and return an RP ERROR message with cause #81,
            "Invalid short message transfer reference value" using the received
            Message Reference, if an appropriate connection exists*/
            if(g_SmrEnt.SmrMo.ucMr != pucData[1])
            {
                SMR_SndRpErrorReq( pucData[1],
                               SMR_ERR_CAUSE_VALUE_INVALID_MR,
                               SMS_TRUE );
                ulRet = SMR_ERR_CAUSE_VALUE_INVALID_MR;
                break;
            }

            /* 停止timer TR1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiDataInd: TimerStop: TR1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiDataInd: TimerStop: TR1M Failed" );
            }

            if (SMS_TRUE == g_SmrEnt.SmrMo.ucMemAvailFlg)
            {                                                                   /* 此过程是mem avail过程                    */
                g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;                       /* 清除mem avail标志                        */
                g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;              /* 复位重发标志                             */
            }

            g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* 状态迁移到空闲状态                       */

            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            SMS_SendMnReportReq(SMR_SMT_ERROR_NO_ERROR, pucData, ulLen);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

            NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_MO_SUCC,
                            &stSmsMoReportPara, sizeof(stSmsMoReportPara));
            break;
        case SMR_NTM_DATA_TYPE_RP_ERR:

            /*When an RP ERROR message is received specifying a Message
            Reference which is not associated with an active SM transfer, the
            mobile station shall discard the message*/
            /*此处处理同消息长度过短，暂时返回SMR_MSG_TOO_SHORT_ERROR*/
            if(g_SmrEnt.SmrMo.ucMr != pucData[1])
            {
                ulRet = SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR;
                break;
            }

            /* 停止timer TR1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiDataInd: TimerStop: TR1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiDataInd: TimerStop: TR1M Failed" );
            }
            if (SMS_TRUE == g_SmrEnt.SmrMo.ucMemAvailFlg )
            {                                                                   /* 此过程是mem avail过程                    */
                if ((SMR_ERR_CAUSE_TEMP_FAILURE   == pucData[3])
                    || (SMR_ERR_CAUSE_CONGESTION  == pucData[3])
                    || (SMR_ERR_CAUSE_RES_UNAVAIL == pucData[3])
                    || (SMR_ERR_CAUSE_NET_OUT_OF_ORDER == pucData[3]))
                {                                                               /* 是temporary error                        */
                    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
                    SMR_MemNotifyRetrans((SMR_SMT_ERROR_RP_ERROR_BEGIN | pucData[NAS_SMS_RP_ERROR_OFFSET]),
                                        pucData,
                                        ulLen);         /* 调用重发过程的处理                       */
                    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
                }
                else
                {
                    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
                    SMS_SendMnReportReq((SMR_SMT_ERROR_RP_ERROR_BEGIN | pucData[NAS_SMS_RP_ERROR_OFFSET]),
                                        pucData,
                                        ulLen);                                 /* 向高层指示错误                           */
                    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
                    g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;                   /* 清除mem avail标志                        */
                    g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;          /* 复位重发标志                             */
                    PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_SmcApiDataInd:NORMAL:SMS state = SMR_IDLE");
                    g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* 状态迁移到空闲状态                       */
                }
            }
            else
            {                                                                   /* 此过程是MO过程                           */
                /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
                SMS_SendMnReportReq((SMR_SMT_ERROR_RP_ERROR_BEGIN | pucData[NAS_SMS_RP_ERROR_OFFSET]),
                                    pucData,
                                    ulLen);                           /* 向高层指示错误                           */
                /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
                PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_SmcApiDataInd:NORMAL:SMS state = SMR_IDLE");
                g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* 状态迁移到空闲状态                       */
            }
            /* 刚解析完消息，后面还会判断要不要重试，此处报SMS MO FAIL太早 */
            break;
        default:
            /* 向网侧指示错误          */
            SMR_SndRpErrorReq(pucData[1],
                              SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST,
                              SMS_TRUE);
            ulRet = SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST;
            break;
        }

    }
    else
    {
        SMR_SndRpErrorReq(pucData[1],
                          SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE,
                          SMS_TRUE);
        ulRet = SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE;
    }
    return ulRet;
}
/*******************************************************************************
Module:   SMR_SmcApiEstInd
Function: 指示SMR建立实体
Input:    VOS_UINT8     *pucData        数据首地址
          VOS_UINT32      ulLen          数据长度
Output:   VOS_VOID
NOTE:
Return:   VOS_VOID
History:
1.   张志勇   2004.03.10   新规作成

2.日    期   : 2010年8月21日
  作    者   : zhoujun /40661
  修改内容   : DTS2010081901387,网络下发的长度过短时,短信有可能内存越界
3.日    期   : 2013年6月4日
  作    者   : s00217060
  修改内容   : for V9R1_SVLTE:接收短信时，把接收域是CS还是PS域带上去，MSG要用
*******************************************************************************/
VOS_UINT32 SMR_SmcApiEstInd(
                      VOS_UINT8 *pucData,                                       /* 数据首地址           */
                      VOS_UINT32  ulLen,                                        /* 数据长度             */
                      VOS_UINT8   ucRcvDomain                                    /* 接收域是PS域还是CS域 */
                      )
{
    VOS_UINT8   ucChkError;                                                         /* 定义存储消息检查结果的变量               */
    VOS_UINT32  ulRet = VOS_OK;

    ucChkError      = SMR_SmcChk(pucData,ulLen);                                /* 调用消息检查                             */
    if (ucChkError != SMR_MSG_CHK_SUCCESS)
    {                                                                           /* 未通过消息检查                           */
        if(ucChkError == SMR_MSG_TOO_SHORT_ERROR)
        {                                                                       /* 消息过短                                 */
            SMR_SndRpErrorReq(g_SmrEnt.SmrMt.ucMr,SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ,SMS_TRUE );
        }
        else
        {
            SMR_SndRpErrorReq( pucData[1], ucChkError,SMS_TRUE );               /* 向网络侧发送错误消息                     */
            SMC_SmrApiRelReq( SMR_SMC_REL_CAUSE_DATA_ERR,SMS_TRUE );            /* 发送MNSMS_REL_REQ                        */
        }
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcApiEstInd:WARNING:ucChkError != SMR_MSG_CHK_SUCCESS ");
        return ucChkError;
    }

    if(SMR_IDLE == g_SmrEnt.SmrMt.ucState)
    {
        if ( SMR_NTM_DATA_TYPE_RP_DATA == pucData[0] )
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_SmcApiEstInd:NORMAL:SMS state = SMR_WAIT_TO_SND_RP_ACK");
            g_SmrEnt.SmrMt.ucState = SMR_WAIT_TO_SND_RP_ACK;                    /* 实体状态迁移                             */
            g_SmrEnt.SmrMt.ucMr    = pucData[1];

            /* 启动定时器TR2M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiEstInd: TimerStart: TR2M" );
            if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR2M ) )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiEstInd: TimerStart: TR2M failed" );
            }
            /* 关闭定时器TRRM */
            if( SMS_TIMER_STATUS_RUN == g_SmrEnt.SmrMt.RelTimerInfo.ucTimerSta )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiEstInd: TimerStop: TRRM" );
            }
            /* 原来的函数名为SMS_SendMnDataReq，现在修改为SMS_SendMnEstInd，入参增加发送域 */
            SMS_SendMnEstInd( pucData , ulLen, ucRcvDomain );                            /* 向TAF发送SMRL_DATA_IND(RP-DATA)          */
        }
        else if(SMR_NTM_DATA_TYPE_RP_ACK == pucData[0])
        {
            SMR_SndRpErrorReq( pucData[1],
                               SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE,
                               SMS_TRUE );                                      /* 与协议状态不对应,发送RP_ERROR            */
            ulRet = SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE;
        }
        else if (SMR_NTM_DATA_TYPE_RP_ERR == pucData[0])
        {
            /*When an RP ERROR message is received specifying a Message
            Reference which is not associated with an active SM transfer, the
            mobile station shall discard the message*/
            /*此处处理同消息长度过短，暂时返回SMR_MSG_TOO_SHORT_ERROR*/
            ulRet = SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        else
        {
            SMR_SndRpErrorReq(pucData[1],
                              SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST,
                              SMS_TRUE);
            ulRet = SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST;
        }
    }
    else
    {
        SMR_SndRpErrorReq( g_SmrEnt.SmrMo.ucMr,
                           SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE,
                           SMS_TRUE );                                          /* 与协议状态不对应,发送RP_ERROR            */
        ulRet = SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE;
    }
    return ulRet;
}

/*******************************************************************************
Module:   SMR_SmcApiErrorInd
Function: 向SMR上报错误
Input:    VOS_UINT8   *pucData      - 数据首地址
          VOS_UINT32   ulLen        - 数据长度
                       enErrorType  - 错误类型
Output:   VOS_VOID
NOTE:
Return:   VOS_VOID
History:
1.   张志勇   2004.03.10   新规作成
2. 日    期   : 2012年8月29日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改,增加函数入参enErrorType
3.日    期   : 2013年6月26日
  作    者   : f62575
  修改内容   : V9R1 STK升级
*******************************************************************************/
VOS_VOID SMR_SmcApiErrorInd(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                           ucMtFlag
)
{
    if (SMS_FALSE == ucMtFlag)
    {                                                                           /* 在MO过程                                 */
        if (SMR_IDLE != g_SmrEnt.SmrMo.ucState)
        {
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            SMS_SendMnReportReq(enErrorCode, VOS_NULL_PTR, 0);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
            g_SmrEnt.SmrMo.ucRetransFlg = 0;                                    /* 将RETRANS FLAG置零                       */

            /* 停止timer TR1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiErrorInd: TimerStop: TR1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
            {
                return;
            }

            /* 停止timer TRAM */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiErrorInd: TimerStop: TRAM" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TRAM ) )
            {
                return;
            }

            if(SMS_TRUE == g_SmrEnt.SmrMo.ucMemAvailFlg)
            {
                g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;
                g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;              /* 复位重发标志     */
            }
        }
        g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* 状态迁移到空闲状态                       */
    }
    else
    {
        if (SMR_WAIT_TO_SND_RP_ACK == g_SmrEnt.SmrMt.ucState)
        {
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
            SMS_SendMnMtErrInd(enErrorCode);
            /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

            /* 停止timer TR2M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiErrorInd: TimerStop: TR2M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR2M ) )
            {
                return;
            }

            /* g_SmrEnt.SmrMt.TimerInfo.ucTimerSta = SMS_TIMER_STATUS_STOP; */
            g_SmrEnt.SmrMt.ucState              = SMR_IDLE;                     /* 状态迁移到空闲状态                       */
        }
    }
    return;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

