/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_Msg.c
  Description  : MM消息处理
  Function List:
              MM_ComCheckIntegrityProtection
              MM_ComCheckLauIntegrityProtection
              MM_ComCheckNoOtherMmConnection
              MM_ComCmpLai
              MM_ComLaiOrTempIdJudge
              Mm_ComMsgAbortRcv
              Mm_ComMsgAuthFailSnd
              Mm_ComMsgAuthReqRcv
              Mm_ComMsgAuthRjctRcv
              Mm_ComMsgAuthRspSnd
              Mm_ComMsgCcMsgInteChk
              Mm_ComMsgChkProc
              Mm_ComMsgCmReEstReqSnd
              Mm_ComMsgCmSvcAbortSnd
              Mm_ComMsgCmSvcAcceptRcv
              Mm_ComMsgCmSvcReqOfRrEstReq
              Mm_ComMsgCmSvcReqSnd
              Mm_ComMsgCmSvcRjctRcv
              Mm_ComMsgIdReqRcv
              Mm_ComMsgIdRspSnd
              Mm_ComMsgImsiDetachIniSndOfDataReq
              Mm_ComMsgImsiDetachIniSndOfEstReq
              Mm_ComMsgLuAccptRcv
              Mm_ComMsgLuRejctRcv
              Mm_ComMsgLuReqSndOfDataReq
              Mm_ComMsgLuReqSndOfEstReq
              Mm_ComMsgMmInfoRcv
              Mm_ComMsgMmStatusRcv
              Mm_ComMsgMmStatusSnd
              Mm_ComMsgPagingRspSnd
              Mm_ComMsgSetMobileId
              Mm_ComMsgSvcPromptRcv
              Mm_ComMsgTmsiReallocCmdRcv
              Mm_ComMsgTmsiRelocCpltSnd
              Mm_ComSaveLai
              MM_IeChkAutn
              MM_IeChkCksn
              MM_IeChkDayLightSavTim
              MM_IeChkIdType
              MM_IeChkLai
              MM_IeChkLsaIdtfr
              MM_IeChkMblId
              MM_IeChkNtwkNam
              MM_IeChkPdAndSapi
              MM_IeChkPlmnLst
              MM_IeChkRand
              MM_IeChkSprHalfOctet
              MM_IeChkTimAndTimZone
              MM_IeChkTimZone
    History:
      1.  张志勇   2003.12.10   新版作成
      2.  s46746   2006.01.20   根据问题单A32D01550修改
      3.  l48197   2006.02.06   问题单号:A32D01680, 修改LAC解码错误。
      4.  日    期   : 2006年2月20日
          作    者   : liuyang id:48197
          修改内容   : 当Identity Type属于imperative message part，根据协议
                       24.008.8.5规定，当前应该返回#96，在程序中的
                       Mm_ComMsgIdReqRcv（）函数，判断IE错误返回时，应该返回#96
                       而不是#95,问题单号:A32D01694
      5.  s46746   2006.03.02   根据问题单A32D01911修改
      6.  s46746   2006.03.02   根据问题单A32D02233修改
      7.  s46746   2006.04.18   根据问题单A32D03196修改
      8.  s46746   2006-06-22   根据问题单A32D04409修改
      9.  x51137 2006/11/3 A32D06511
      10. x51137 2006/11/3 A32D06821
      11.日    期   : 2006年11月6日
         作    者   : s46746
         修改内容   : 问题单号:A32D06442
      12.日    期   : 2006年11月21日
         作    者   : luojian   id:60022475
         修改内容   : 去掉完整性检查判断,问题单号：A32D07459
      13.日    期   : 2006年11月22日
         作    者   : luojian   id:60022475
         修改内容   : 问题单号：A32D07583
      14.日    期   : 2007年05月11日
         作    者   : luojian id:60022475
         修改内容   : 问题单号:A32D10713
      15.日    期   : 2007年07月10日
         作    者   : s46746
         修改内容   : 根据问题单号：A32D12268
      16.日    期   : 2007年12月21日
         作    者   : l00107747
         修改内容   : 问题单号:A32D13951
      17.日    期   : 2008年08月1日
         作    者   : luojian id:00107747
         修改内容   : 根据问题单AT2D04837,依据 24.008 4.1.1.1，对L3消息统一进行完整性检查
      18.日    期   : 2009年02月28日
         作    者   : s46746
         修改内容   : 根据问题单AT2D09546,WCDMA单模下，A5/1能力设置为不支持
      19.日    期   : 2009年07月10日
         作    者   : x00115505
         修改内容   : 根据问题单AT2D12859,紧急呼过程中网侧查询IMSI，UE没有回复。
      20.日    期   : 2009年07月13日
         作    者   : x00115505
         修改内容   : 根据问题单AT2D12875,网侧查询IMEI，UE回复No Identity。
      21.日    期   : 2009年10月03日
         作    者   : x00115505
         修改内容   : 根据问题单AT2D14865,无卡开机发起了Lu
*******************************************************************************/

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "GmmExt.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

#include "NasUtranCtrlInterface.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */
#include "NasMmEcall.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */

/* Added by n00355355 for 呼叫重建, 2015-9-24, begin */
#include "NasMmlLib.h"
/* Added by n00355355 for 呼叫重建, 2015-9-24, end */

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_MSG_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/*******************************************************************************
  Module:      MM_ReportN2MOtaMsg
  Function:    在trace中勾取MM的空口消息
  Input:       VOS_UINT8       ucMsgType   SM msg type
               NAS_MSG_STRU*   pNasMsg     SM空口消息
  NOTE:
  Return:      VOS_VOID
  History:
      1. 鲁琳    2009.07.11   新规作成
      2. 日    期   : 2013年10月11日
         作    者   : z00161729
         修改内容  : DTS2013101007129:mm status ota消息有上行和下行之分需要用两个消息id
*******************************************************************************/
VOS_VOID MM_ReportN2MOtaMsg(VOS_UINT8 ucMsgType, NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "MM_ReportN2MOtaMsg:NORMAL: msg type is ", ucMsgType);

    switch(ucMsgType)
    {
        case MM_IE_MSG_TYPE_AUTH_REQ:                                           /* AUTHENTICATION REQUEST 消息              */
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_REQ;
            break;

        case MM_IE_MSG_TYPE_CM_SERV_REJ:                                        /* CM SERVICE REJECT 消息                   */
            usNasOtaMsyId = NAS_OTA_MSG_CM_SERV_REJECT;
            break;

        case MM_IE_MSG_TYPE_CM_SERV_ACP:                                        /* CM SERVICE ACCEPT 消息                   */
            usNasOtaMsyId = NAS_OTA_MSG_CM_SERV_ACCEPT;
            break;

        case MM_IE_MSG_TYPE_AUTH_REJ:                                           /* AUTHENTICATION REJECT 消息               */
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_REJECT;
            break;

        case MM_IE_MSG_TYPE_ABORT:                                              /* ABORT 消息                               */
            usNasOtaMsyId = NAS_OTA_MSG_ABORT;
            break;

        case MM_IE_MSG_TYPE_ID_REQ:                                             /* IDENTITY REQUEST 消息                    */
            usNasOtaMsyId = NAS_OTA_MSG_ID_REQ;
            break;

        case MM_IE_MSG_TYPE_MM_INFO:                                            /* MM INFORMATION 消息                      */
            usNasOtaMsyId = NAS_OTA_MSG_MM_INFO;
            break;

        case MM_IE_MSG_TYPE_MM_STA:                                             /* MM STATUS 消息                           */
            usNasOtaMsyId = NAS_OTA_MSG_MM_STA_N2M;
            break;

        case MM_IE_MSG_TYPE_TMSI_REALLOC_CMD:                                   /* TMSI REALLOCATION COMMAND 消息           */
            usNasOtaMsyId = NAS_OTA_MSG_TMSI_REALLOC_CMD;
            break;

        case MM_IE_MSG_TYPE_LU_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_LOCATION_UPDATE_ACCEPT;
            break;

        case MM_IE_MSG_TYPE_LU_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_LOCATION_UPDATE_REJECT;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "MM_ReportN2MOtaMsg:WARNING: invalid msg id");
            /*不属于MM模块的空口消息，不在trace中显示*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_MM, usNasOtaMsyId, NAS_OTA_DIRECTION_DOWN, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
}

/*******************************************************************************
  Module:   Mm_ComMsgAuthReqRcv
  Function: 存储消息AUTHENTICATION REQUEST
  Input:    VOS_VOID     *pMsg,  当前处理的消息
            VOS_UINT16    usMsgSize, 消息长度,以字节为单位
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.10   新版作成
      2.  s46746   2006-02-25   根据问题单A32D02193修改
      3.日    期   : 2014年10月20日
        作    者   : w00167002
        修改内容   : DTS2014102000868:在鉴权成功后才更新CKSN
*******************************************************************************/
VOS_UINT8 Mm_ComMsgAuthReqRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_AUTH_REQ;                               /* 事件ID                                   */
    VOS_UINT16      usIndex;

    PS_MEM_SET( &g_MmMsgAuthReq, 0, sizeof(MM_MSG_AUTHENTICATION_REQ_STRU));   /* 清零                                     */

    if (VOS_NULL_PTR == pucRcvMsg)
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: MSG VOS_NULL_PTR!");
    }
    else if ( usMsgSize < 19 )
    {
        ucEventId = MM_EVENT_ID_STATUS_96;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: RCV MM AUTHENTICATION REQ MSG WITH ERROR SIZE!");
    }
    else if (MM_FALSE == MM_IeChkCksn( &pucRcvMsg[2] ))
    {                                                                           /* CKSN为保留值                             */
        ucEventId = MM_EVENT_ID_STATUS_95;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: CKSN ERROR!");
    }
    else
    {
        g_MmMsgAuthReq.MmIeCKSN.ucCksn
            = (VOS_UINT8)(pucRcvMsg[2] & MM_IE_CKSN_KEY_SEQUENCE_MASK);         /* 存储CKSN                                 */


        if ( MM_FALSE == MM_IeChkRand( &pucRcvMsg[3] ) )
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: RAND ERROR!");
            return MM_EVENT_ID_STATUS_95;
        }
        PS_MEM_CPY(
                    g_MmMsgAuthReq.MmIeRAND.aucRandValue,
                    pucRcvMsg+3,
                    MM_RAND_VALUE_LENGTH
                    );                                                          /* 存储RAND                                 */
        usIndex = 19;
        while ( usIndex < usMsgSize )
        {                                                                       /* 消息里含有AUTN                           */
            if ( ( 0x20 == pucRcvMsg[usIndex] ) && ( usMsgSize > 36 ) )
            {                                                                   /* AUTN的IEI正确                            */
                usIndex++;
                if ( MM_FALSE == MM_IeChkAutn( &pucRcvMsg[usIndex] ) )
                {
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAuthReqRcv:WARNING: AUTN ERROR!");
                    return MM_EVENT_ID_STATUS_95;
                }
                if ( MM_IE_AUTN_PRESENT == g_MmMsgAuthReq.ucAutnFlg)
                {
                    ;
                }
                else
                {
                    g_MmMsgAuthReq.ucAutnFlg = MM_IE_AUTN_PRESENT;
                    g_MmMsgAuthReq.MmIeAUTN.ucAutnLen = pucRcvMsg[usIndex];     /* 获得AUTN的长度                           */
                    PS_MEM_CPY(
                                g_MmMsgAuthReq.MmIeAUTN.aucAutn,
                                &pucRcvMsg[usIndex + 1],
                                pucRcvMsg[usIndex]
                                );                                              /* 获得AUTN                                 */
                }
                usIndex = usIndex + pucRcvMsg[usIndex] + 1;
            }
            else
            {                                                                   /* AUTN的IEI不正确                          */
                usIndex = usMsgSize;
            }
        }
    }
    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgCcMsgInteChk
  Function: 对CC消息进行完整性检测
  Input:    RRMM_DATA_IND_STRU       *pMsg, RRMM_DATA_IND原语指针
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.11  新版作成
      2. 日    期   : 2006年11月21日
         作    者   : luojian   id:60022475
         修改内容   : 去掉完整性检查判断,问题单号：A32D07459
*******************************************************************************/
VOS_UINT8 Mm_ComMsgCcMsgInteChk (
                              RRMM_DATA_IND_FOR_PCLINT_STRU       *pMsg         /* 当前处理的消息                           */
                               )
{
    VOS_UINT8       ucEventId;                                                  /* 事件ID                                   */
    VOS_UINT8       i;                                                          /* 循环变量                                 */
    VOS_UINT8       j;                                                          /* 循环变量                                 */
    VOS_UINT8       ucCnt = 0;                                                  /* MM连接的存在个数                         */
    /*lint -e701*/
    for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_2; i++ )
    {
        for ( j = MM_CONST_NUM_0; j < MM_CONST_NUM_7; j++ )
        {
            if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[i] & (0x01 << j) ) )
            {                                                                   /* 统计MM连接的个数                         */
                ucCnt++;
            }
            if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                aucMMConnExtFlg[i] & (0x01 << j) ) )
            {                                                                   /* 统计MM连接的个数                         */
                ucCnt++;
            }
            if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                aucMMConnExtFlg[i] & (0x01 << j) ) )
            {                                                                   /* 统计MM连接的个数                         */
                ucCnt++;
            }
        }
    }
    /*lint +e701*/

    if ((MM_CONST_NUM_1 == ucCnt)
        &&(NO_MM_CONN_ESTING ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
        &&(MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg))
    {                                                                           /* 如果MM连接只有一条并且是紧急呼           */
        ucEventId = MM_EVENT_ID_CC_MESSAGE;                                     /* 获得事件ID                               */
    }

    else
    {
        ucEventId = MM_EVENT_ID_CC_MESSAGE;                                     /* 获得事件ID                               */
    }
    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgCmSvcAcceptRcv
  Function: 对CM SERVICE ACCEPT消息进行完整性检测
  Input:    RRMM_DATA_IND_STRU       *pMsg, RRMM_DATA_IND原语指针
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇    2003.12.11  新版作成
*******************************************************************************/
VOS_UINT8 Mm_ComMsgCmSvcAcceptRcv (
                                RRMM_DATA_IND_FOR_PCLINT_STRU       *pMsg       /* 当前处理的消息                           */
                                  )
{
    VOS_UINT8       ucEventId;                                                  /* 事件ID                                   */

    if ((MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
        &&(MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1])
        && (MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0])
        && (MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1])
        && (MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0])
        && (MM_CONST_NUM_0 ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1])
        &&(NO_MM_CONN_ESTING !=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
        &&(MM_TRUE ==
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg))
    {
        ucEventId = MM_EVENT_ID_CM_SVC_ACCEPT;                                  /* 获得事件ID                               */
    }
    else
    {
        ucEventId = MM_EVENT_ID_CM_SVC_ACCEPT;                                  /* 获得事件ID                               */
    }

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgAuthRjctRcv
  Function: 存储消息AUTHENTICATION REJECT
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.10   新版作成
      2. 日    期   : 2007年05月11日
         作    者   : luojian id:60022475
         修改内容   : 问题单号:A32D10713
	  3. 日    期   : 2014年2月18日
         作    者   : l00215384
         修改内容   : DTS2014021006453
*******************************************************************************/
VOS_UINT8 Mm_ComMsgAuthRjctRcv ()
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_AUTH_REJ;                               /* 事件ID                                   */
	NAS_MML_PLMN_ID_STRU *         pstCurrCampPlmnId;
	NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;
    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_TYPE_BUTT;

    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();
    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_AUTH_REJ,
                              NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    if (pstAuthRejInfo->ucHplmnCsAuthRejCounter < pstAuthRejInfo->ucMaxAuthRejNo)
    {
        if ((VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId))
        && (VOS_TRUE == pstAuthRejInfo->ucIgnoreAuthRejFlg))
        {
            pstAuthRejInfo->ucHplmnCsAuthRejCounter++;
            return MM_EVENT_ID_INVALID;
        }
    }

    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgCmSvcRjctRcv
  Function: 存储消息CM SERVICE REJECT
  Input:    VOS_UINT8    *pucRcvMsg, 当前处理的消息
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.10   新版作成
*******************************************************************************/
VOS_UINT8 Mm_ComMsgCmSvcRjctRcv (
                            VOS_UINT8      *pucRcvMsg,                          /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                           /* 消息长度,以字节为单位                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_CM_SVC_REJ;                         /* 事件ID                                   */

    if ( usMsgSize < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgCmSvcRjctRcv:WARNING: RCV MM CM SERVICE REJECT MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }
    g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause = pucRcvMsg[2];                    /* 存储Reject cause                         */

    g_MmGlobalInfo.ucRejectCause = pucRcvMsg[2];

    NAS_MM_ParseT3246IE(pucRcvMsg, usMsgSize, &(g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246));

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgAbortRcv
  Function: 存储消息ABORT
  Input:    VOS_UINT8    *pucRcvMsg, 当前处理的消息
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.10   新版作成
*******************************************************************************/
VOS_UINT8 Mm_ComMsgAbortRcv (
                            VOS_UINT8      *pucRcvMsg,                          /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                           /* 消息长度,以字节为单位                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_ABORT;                              /* 事件ID                                   */

    if ( usMsgSize < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgAbortRcv:WARNING: RCV MM ABORT MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }
    g_MmMsgAbort.MmIeRejCause.ucRejCause = pucRcvMsg[2];                        /* 存储Reject cause                         */

    g_MmGlobalInfo.ucRejectCause = pucRcvMsg[2];

    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgIdReqRcv
  Function: 存储消息 IDENTITY REQUEST
  Input:    VOS_UINT8    *pucRcvMsg, 当前处理的消息
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.10   新版作成

      2.日    期   : 2006年2月20日
        作    者   : liuyang id:48197
        修改内容   : 将IE错误的上报的原因值由95改为96,问题单号:A32D01694
*******************************************************************************/
VOS_UINT8 Mm_ComMsgIdReqRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_IDENTITY_REQ;                           /* 事件ID                                   */

    if ( usMsgSize < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgIdReqRcv:WARNING: RCV MM IDENTITY REQUEST MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }

    if ( MM_FALSE == MM_IeChkIdType( &pucRcvMsg[2] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgIdReqRcv:WARNING: ID TYPE ERROR!");
        return MM_EVENT_ID_STATUS_96;
    }
    g_MmMsgIdReq.MmIeIdType.ucIDType
        = (VOS_UINT8)(pucRcvMsg[2] & MM_IE_ID_TYPE_IDTYPE_MASK);                    /* 存储Id type                              */
    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgMmInfoRcv
  Function: 存储消息MM INFORMATION
  Input:    VOS_VOID     *pMsg,  当前处理的消息
            VOS_UINT16    usMsgSize, 消息长度,以字节为单位
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.10   新版作成
      2.日    期   : 2011年10月08日
        作    者   : s46746
        修改内容   : V7R1 phase II高优先级状态机实现
      3.日    期   : 2013年4月26日
        作    者   : z00161729
        修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
      4.日    期   : 2013年5月17日
        作    者   : l00167671
        修改内容   : NV项拆分项目, 将NV项数据用结构体描述

*******************************************************************************/
VOS_UINT8 Mm_ComMsgMmInfoRcv (
    VOS_UINT8                           *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    VOS_UINT8                           ucEventId;
    VOS_UINT16                          usIndex;
    VOS_UINT8                           ucShortNetWorkNameExist;
    VOS_UINT8                           ucLongNetWorkNameExist;
    MM_DECODE_RESULT_ENUM_U32           ucRst;
    NAS_MML_OPERATOR_NAME_INFO_STRU     stOldOperatorName;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    /* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
    NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU                    stNvimOperatorName;
    /* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */

    ucShortNetWorkNameExist = VOS_FALSE;
    ucLongNetWorkNameExist  = VOS_FALSE;
    ucEventId               = MM_EVENT_ID_MM_INFO;
    ucRst                   = MM_DECODE_SUCCESS;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();
    PS_MEM_CPY(&stOldOperatorName, pstCurrOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));

    PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

    if ( usMsgSize < MM_MSG_HEADER_LEN )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "Mm_ComMsgMmInfoRcv:WARNING: RCV MM INFORMATION MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }

    usIndex = MM_MSG_HEADER_LEN;
    while ( usIndex < usMsgSize )
    {
        switch (pucRcvMsg[usIndex])
        {
            case MM_IE_FULL_NAME_FOR_NETWORK:
                ucRst = NAS_MM_DecodeFullNameForNetworkIe(pucRcvMsg, usMsgSize,
                                                          &usIndex, &ucEventId,
                                                          &ucLongNetWorkNameExist);


                /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-26, begin */
                g_MmMsgMmInfo.ucFulNamFrNWFlg = VOS_TRUE;
                /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-26, end */

                break;
            case MM_IE_SHORT_NAME_FOR_NETWORK:
                ucRst = NAS_MM_DecodeShortNameForNetworkIe(pucRcvMsg, usMsgSize,
                                                          &usIndex, &ucEventId,
                                                          &ucShortNetWorkNameExist);

                /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-26, begin */
                g_MmMsgMmInfo.ucShortNamFrNWFlg = VOS_TRUE;
                /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-26, end */

                break;
            case MM_IE_LOCAL_TIME_ZONE:
                ucRst = NAS_MM_DecodeLocalTimeZoneIe(pucRcvMsg, usMsgSize,
                                             &usIndex, &ucEventId);
                break;
            case MM_IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE:
                ucRst = NAS_MM_DecodeUniversalTimeAndLocalTimeZoneIe(pucRcvMsg, usMsgSize,
                                                     &usIndex, &ucEventId);
                break;
            case MM_IE_LSA_IDENTITY:
                ucRst = NAS_MM_DecodeLocalizedServiceAreaIe(pucRcvMsg, usMsgSize,
                                                     &usIndex, &ucEventId);
                break;
            case MM_IE_NETWORK_DAYLIGHT_SAVING_TIME:
                ucRst = NAS_MM_DecodeNetworkDaylightSavingTimeIe(pucRcvMsg, usMsgSize,
                                                     &usIndex, &ucEventId);
                break;
            default:
                usIndex = usMsgSize;
                break;
        }

        /* 如果消息解析后的网络名与之前保存的内容不同,需要写NV */
        if (0 != VOS_MemCmp(pstCurrOperatorName, &stOldOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU)))
        {
            /* Modified by l00167671 for NV拆分项目 , 2013-05-17, begin */
            PS_MEM_CPY(&stNvimOperatorName, pstCurrOperatorName, sizeof(stNvimOperatorName));

            if (NV_OK != NV_Write(en_NV_Item_Network_Name_From_MM_Info,
                                  &stNvimOperatorName,
                                  sizeof(stNvimOperatorName)))
            {
                NAS_WARNING_LOG(WUEPS_PID_MM, "Mm_ComMsgMmInfoRcv:Write NV fail.");
            }
            /* Modified by l00167671 for NV拆分项目 , 2013-05-17, end */
        }

        if(MM_DECODE_END == ucRst)
        {
            return ucEventId;
        }
    }

    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgMmStatusRcv
  Function: 存储消息MM STATUS
  Input:    VOS_UINT8    *pucRcvMsg, 当前处理的消息
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.10   新版作成
*******************************************************************************/
VOS_UINT8 Mm_ComMsgMmStatusRcv (
                            VOS_UINT8      *pucRcvMsg,                          /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                           /* 消息长度,以字节为单位                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_MM_STATUS;                          /* 事件ID                                   */

    if ( usMsgSize < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgMmStatusRcv:WARNING: RCV MM STATUS MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }

    g_MmGlobalInfo.ucRejectCause = pucRcvMsg[2];

    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComSaveLai
  Function: 存储消息中的LAI
  Input:    VOS_UINT8            *pucLai, 消息中的LAI存放地址
            MM_LAI_STRU      *pLai,   LAI全局量的地址
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.15   新版作成
      2.  L48197   2006.01.12   A32D01680, LAC解码错误.根据协议24.008.10.5.1.3
*******************************************************************************/

VOS_VOID Mm_ComSaveLai(
                   VOS_UINT8            *pucLai,                                    /* 消息中的LAI存放地址                      */
                   MM_LAI_STRU      *pLai                                       /* LAI全局量的地址                          */
                   )
{
    pLai->PlmnId.ulMcc = pucLai[1] & MM_IE_LU_ID_MCC_DIGIT_3_MASK;              /* 存储LAI中的 MCC digit 3                  */
    pLai->PlmnId.ulMcc = (pLai->PlmnId.ulMcc << 8) | (pucLai[0] >> 4);          /* 存储LAI中的 MCC digit 2                  */
    pLai->PlmnId.ulMcc = (pLai->PlmnId.ulMcc << 8)
                         | (pucLai[0] & MM_IE_LU_ID_MCC_DIGIT_1_MASK);          /* 存储LAI中的 MCC digit 1                  */

    pLai->PlmnId.ulMnc = pucLai[1] >> 4;                                        /* 存储LAI中的 MNC digit 3                  */
    pLai->PlmnId.ulMnc = (pLai->PlmnId.ulMnc << 8) | (pucLai[2] >> 4);          /* 存储LAI中的 MNC digit 2                  */
    pLai->PlmnId.ulMnc = (pLai->PlmnId.ulMnc << 8)
                         | (pucLai[2] & MM_IE_LU_ID_MNC_DIGIT_1_MASK);          /* 存储LAI中的 MNC digit 1                  */
    pLai->ulLac = pucLai[3];
    pLai->ulLac = (pLai->ulLac << 8) | pucLai[4];

    if ( 0 == ( pLai->ulLac & 0x0000ffff ) )
    {
        pLai->ulLac = MM_INVALID_LAI;
    }

}

/*******************************************************************************
  Module:   Mm_ComMsgTmsiReallocCmdRcv
  Function: 存储消息TMSI REALLOCATION COMMAND
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.10   新版作成
      2.  日    期   : 2010年11月24日
          作    者   : l00167671
          修改内容   : MNC或者MCC范围检查错误后，记录日志，不做其他处理
*******************************************************************************/
VOS_UINT8 Mm_ComMsgTmsiReallocCmdRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_TMSI_REALLOC_CMD;                       /* 事件ID                                   */
    VOS_UINT8       i;                                                              /* 循环变量                                 */

    if ( usMsgSize < 9 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: RCV TMSI REALLOCATION COMMAND MSG WITH ERROR SIZE!");
        return MM_EVENT_ID_STATUS_96;
    }
    PS_MEM_SET(&g_MmMsgTmsiReallocCmd,0,sizeof(MM_MSG_TMSI_REALLOC_CMD_STRU)); /* 清零                                     */

    if ( MM_FALSE == MM_IeChkLai( &pucRcvMsg[2] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: LAI ERROR!");
    }
    Mm_ComSaveLai (pucRcvMsg + 2, &g_MmMsgTmsiReallocCmd.MmIeLAI.IeLai);        /* 存储消息中的LAI                          */

    if ( ( 0xF4 != pucRcvMsg[8] ) && ( 0x01 != (pucRcvMsg[8] & 0x0F) )
                                && ( 0x09 != (pucRcvMsg[8] & 0x0F) ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: MOBILE ID TYPE ERROR!");
        return MM_EVENT_ID_STATUS_95;
    }
    if ( MM_FALSE == MM_IeChkMblId( &pucRcvMsg[7] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: MOBILE ID ERROR!");
        return MM_EVENT_ID_STATUS_95;
    }
    switch ( pucRcvMsg[8] & MM_IE_MI_ID_TYPE_MASK )
    {                                                                           /* 判断MOBILE ID的类型                      */
    case MM_IE_MI_ID_TYPE_IMSI:                                                 /* IMSI                                     */
        g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg
            = MM_MS_ID_IMSI_PRESENT;                                            /* 置Mobile ID存在标志                      */
        break;
    case MM_IE_MI_ID_TYPE_TMSI:                                                 /* TMSI                                     */
        g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.ucMsIdFlg
            = MM_MS_ID_TMSI_PRESENT;                                            /* 置Mobile ID存在标志                      */
        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            g_MmMsgTmsiReallocCmd.MmIeMobileId.MobileID.aucTmsi[i]
                = pucRcvMsg[9+i];                                               /* 获得TMSI                                 */
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgTmsiReallocCmdRcv:WARNING: MOBILE IDENTITY TYPE Abnormal");
        break;
    }
    return ucEventId;                                                           /* 返回事件ID                               */
}

/*****************************************************************************
 函 数 名  : MM_ComCheckNoOtherMmConnection
 功能描述  :
 输出参数  : 无
 返 回 值  : MM_TRUE -- 当前除CC外不存在MM连接
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年8月4日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  MM_ComCheckNoOtherMmConnection()
{
    if ( (MM_CONST_NUM_0 ==  g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0])
      && (MM_CONST_NUM_0 ==  g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1])
      && (MM_CONST_NUM_0 ==  g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0])
      && (MM_CONST_NUM_0 ==  g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]))
    {
        return MM_TRUE;
    }
    else
    {
        return MM_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : MM_ComCmpLai
 功能描述  :
 输入参数  : MM_LAI_STRU stLai1
             MM_LAI_STRU stLai2
 输出参数  : 无
 返 回 值  : VOS_FALSE -- 两个LAI不同
             VOS_TRUE -- 两个LAI相同
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年8月4日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2014年4月18日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整返回值

*****************************************************************************/
VOS_UINT32 MM_ComCmpLai(
    MM_LAI_STRU                         stLai1,
    MM_LAI_STRU                         stLai2
)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-18, begin */
    if ((stLai1.ulLac        != stLai2.ulLac)
     || (stLai1.PlmnId.ulMnc != stLai2.PlmnId.ulMnc)
     || (stLai1.PlmnId.ulMcc != stLai2.PlmnId.ulMcc))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-18, end */
}


/*****************************************************************************
 函 数 名  : MM_ComCheckLauIntegrityProtection
 功能描述  : LAU ACCEPT消息完整性检查
 输入参数  : VOS_UINT8 *pucMsgContent
             VOS_UINT16  usMsgLen
 输出参数  : 无
 返 回 值  : MM_TRUE -- 完整性检查通过
             MM_FALSE -- 完整性检查不通过
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年8月4日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2011年3月3日
    作    者   : z00161729
    修改内容   : DTS2011021201997:PS、CS完整性保护是否开启由GMM和MM分开维护,MMC不再维护
  3.日    期   : 2014年04月03日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.CurLai替换成MML中的
*****************************************************************************/
VOS_UINT32 MM_ComCheckLauIntegrityProtection(VOS_UINT8 *pucMsgContent, VOS_UINT16  usMsgLen)
{
    MM_LAI_STRU                         stLuLai;
    VOS_UINT8                           aucLuTmsi[MM_TMSI_LENGTH];
    VOS_UINT8                           ucTmsiAvail;
    VOS_UINT8                           ucImsiAvail;
    VOS_UINT16                          usIeCount;
    VOS_UINT32                          ulIntegrityCheckResult;
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    MM_LAI_STRU                         stCurLai;

    PS_MEM_SET(&stCurLai, 0x0 ,sizeof(stCurLai));
    NAS_MM_ConvertMmlLaiFormatToMMFormat((NAS_MML_GetCurrCampLai()), &stCurLai);
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    /* 完整性保护已经启动 */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.MmShare.ucCsIntegrityProtect)
    {
        ulIntegrityCheckResult = MM_TRUE;
    }
    /* 完整性保护没有启动 */
    else
    {
        ulIntegrityCheckResult = MM_FALSE;

        /* 24.008 4.1.1.1  LOCATION UPDATING ACCEPT (at periodic location update with no change
        of location area or temporary identity) */
        if (MM_IE_LUT_PERIODIC_UPDATING != g_MmGlobalInfo.LuInfo.ucLuType)
        {
            return MM_FALSE;
        }

        /* 获取LAU ACCEPT消息LAI参数 */
        Mm_ComSaveLai( &pucMsgContent[2], &stLuLai );

        ucTmsiAvail = MM_FALSE;
        ucImsiAvail = MM_FALSE;
        PS_MEM_SET(aucLuTmsi, 0x00, MM_TMSI_LENGTH);

        /* 获取LAU ACCEPT消息TMSI参数 */
        for (usIeCount=7; usIeCount < usMsgLen; usIeCount++ )
        {
            if (MM_IEI_MOBILE_ID == pucMsgContent[usIeCount])
            {
                if ( MM_IE_MI_ID_TYPE_TMSI == (pucMsgContent[usIeCount+2] & 0x07) )
                {
                    ucTmsiAvail = MM_TRUE;
                    PS_MEM_CPY(aucLuTmsi, &pucMsgContent[usIeCount+3], MM_TMSI_LENGTH);
                }
                else if ( MM_IE_MI_ID_TYPE_IMSI == (pucMsgContent[usIeCount+2] & 0x07) )
                {
                    ucImsiAvail = MM_TRUE;
                }
                else
                {
                }
                break;
            }
        }

        /* LAI没有发生改变 */
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        if (VOS_TRUE == MM_ComCmpLai(stLuLai,stCurLai))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        {
            /* 没有分配TMSI */
            if (MM_FALSE == ucTmsiAvail)
            {
                if (!( (MM_TRUE == ucImsiAvail)
                      &&( MM_MS_ID_TMSI_PRESENT == ( g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg
                                                   & MM_MS_ID_TMSI_PRESENT ) ))
                   )
                {
                    ulIntegrityCheckResult = MM_TRUE;
                }
            }
            /* 分配的TMSI和以前相同 */
            else if ( 0 == VOS_MemCmp(aucLuTmsi,NAS_MML_GetUeIdTmsi(),MM_TMSI_LENGTH) )
            {
                ulIntegrityCheckResult = MM_TRUE;
            }
            else
            {
            }
        }
    }
    return ulIntegrityCheckResult;
}

/*****************************************************************************
 函 数 名  : MM_ComCheckIntegrityProtection
 功能描述  : 完整性检查
 输入参数  : VOS_UINT8 *pMsg
 输出参数  : 无
 返 回 值  : MM_TRUE -- 完整性检查通过
             MM_FALSE -- 完整性检查不通过
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年8月4日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2011年3月3日
    作    者   : z00161729
    修改内容   : DTS2011021201997:PS、CS完整性保护是否开启由GMM和MM分开维护,MMC不再维护

  3.日    期   : 2013年11月18日
    作    者   : w00167002
    修改内容   : DTS2013112006986:控制在3G TDD模式下是否需要开启SMC验证标记:中国移动拉萨网络设备在
                 TD下不发起SMC流程。
*****************************************************************************/
VOS_UINT32 MM_ComCheckIntegrityProtection(VOS_UINT8 *pucMsgContent, VOS_UINT16  usMsgLen)
{
    VOS_UINT8                           ucPD;
    VOS_UINT8                           ucMsgType;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* 快速接入模式属于测试模式，不进行完整性检查 */
    if ( VOS_TRUE == NAS_MML_IsQuickStartFlg())
    {
        return MM_TRUE;
    }

    /* 完整性检查仅适用于UMTS网络 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return MM_TRUE;
    }


    /* 在TDD模式时候，如果配置不需要进行SMC设置，则返回完整性保护通过 */
    if (VOS_FALSE == NAS_UTRANCTRL_IsUtranCsSmcNeeded())
    {
        return MM_TRUE;
    }

    ucPD = pucMsgContent[0] & 0x0f;

    /* 完整性保护已经启动 */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.MmShare.ucCsIntegrityProtect)
    {
        ulIntegrityCheckResult = MM_TRUE;
    }
    /* 完整性保护没有启动 */
    else
    {
        ulIntegrityCheckResult = MM_FALSE;

        /*
        24.008 4.1.1.1 Except the messages listed below, no layer 3 signalling
        messages shall be processed by the receiving MM and GMM entities or
        forwarded to the CM entities, unless the security mode control procedure
        is activated for that domain. */
        if (MM_IE_PD_MM_MSG == ucPD)
        {
            ucMsgType = pucMsgContent[1] & 0x3f;
            switch (ucMsgType)
            {
                case MM_IE_MSG_TYPE_AUTH_REQ:
                case MM_IE_MSG_TYPE_AUTH_REJ:
                case MM_IE_MSG_TYPE_ID_REQ:
                case MM_IE_MSG_TYPE_LU_REJECT:
                case MM_IE_MSG_TYPE_CM_SERV_REJ:
                case MM_IE_MSG_TYPE_ABORT:
                    ulIntegrityCheckResult = MM_TRUE;
                    break;
                case MM_IE_MSG_TYPE_LU_ACCEPT:
                    ulIntegrityCheckResult = MM_ComCheckLauIntegrityProtection(pucMsgContent,usMsgLen);
                    break;

                case MM_IE_MSG_TYPE_CM_SERV_ACP:
                    if ( (MM_TRUE == MM_ComCheckNoOtherMmConnection())
                      && (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucState)
                      && (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType) )
                    {
                        ulIntegrityCheckResult = MM_TRUE;
                    }
                    break;
                default:
                    break;
            }
        }
        else if(MM_IE_PD_CALL_CONTROL == ucPD)
        {
            /* 连接态没有其他MM连接，当前为紧急呼叫状态 */
            if ((MM_TRUE == MM_ComCheckNoOtherMmConnection())
             && (MM_CONNECTION_ACTIVE == g_MmGlobalInfo.ucState)
             && (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType) )
            {
                ulIntegrityCheckResult = MM_TRUE;
            }
        }
        else if (MM_IE_PD_TEST == ucPD)
        {
            ulIntegrityCheckResult = MM_TRUE;
        }
        else
        {
        }
    }
    return ulIntegrityCheckResult;
}

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */

/*****************************************************************************
 函 数 名  : NAS_MM_IsIdleState
 功能描述  : 判断MM主状态是否在IDLE态.
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年03月23日
    作    者   : 陈志敏 c00173809
    修改内容   : 新生成函数
  2.日    期   : 2012年10月24日
    作    者   : t00212959
    修改内容   : DTS2012102204240:无卡状态下从L重选到G，无法拨打紧急呼,增加了LOCATION_UPDATING_PENDING状态的判断
  3.日    期   : 2014年5月14日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
*****************************************************************************/
VOS_BOOL NAS_MM_IsIdleState()
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-30, begin */
    VOS_BOOL                            bIdle;

    bIdle = VOS_FALSE;

    switch (g_MmGlobalInfo.ucState)
    {
        case MM_IDLE_NO_CELL_AVAILABLE:
        case MM_IDLE_PLMN_SEARCH:
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case MM_IDLE_NO_IMSI:
        case LOCATION_UPDATING_PENDING:
        /* 增加新增的ecall inactive状态，也是一种IDLE态 */
        case MM_IDLE_ECALL_INACTIVE:
            bIdle = VOS_TRUE;
            break;

        default:

            break;
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-30, end */

    return bIdle;
}


/*****************************************************************************
 函 数 名  : NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd
 功能描述  : MM收到MMC转发的SYSINFO消息，对SYSINFO中携带的FORB标志进行处理
 输入参数  : ulCurFobidnFlg  -- 当前系统消息中携带的FORB标志
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月5日
    作    者   : w00167002
    修改内容   : 新生成函数
 23.日    期   : 2014年5月8日
    作    者   : z00161729
    修改内容   : DTS2014041806795:GCF 13.1.15 UE在lte下联合注册，收到网络cs的paging，重定向到tds的注册被bar的小区后ue没有发送paging response
*****************************************************************************/
VOS_VOID NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(
    VOS_UINT32                          ulCurFobidnFlg
)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-8, begin */
    if (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == (MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS & ulCurFobidnFlg))
    {
        if (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);

            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_SndMmcForbidenRslt();
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-8, end */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_SYS_INFO_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN);

    g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

    /* 对FORBIDEN的统一处理 */
    g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;

    Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_NULL);

    Mm_DealWithBuffMsg();

    return;
}



/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

/*******************************************************************************
  Module:   NAS_MM_ResetRejCauseChangedCounter
  Function: 收到LU Accept消息时reset计数器
  Input:
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期  : 2014年10月27日
        作    者  : h00285180
        修改内容  : 问题单号:DTS2014110307415
*******************************************************************************/
VOS_VOID NAS_MM_ResetRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_ResetHplmnCsRejCauseChangedCounter();
    NAS_MML_ResetVplmnCsRejCauseChangedCounter();
}



/*******************************************************************************
  Module:   NAS_MM_HandleHplmnRejCauseChange
  Function: 如果NV配置的CS域HPLMN拒绝原因值为#17，则判断是否需要替换
  Input:    VOS_UINT8    *pucRcvMsg, 当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期  : 2014年10月27日
        作    者  : h00285180
        修改内容  : 问题单号:DTS2014110307415
*******************************************************************************/
VOS_VOID NAS_MM_HandleHplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg
)
{
    VOS_UINT8                           ucAdaptCause = 0;

    ucAdaptCause = NAS_MML_GetHplmnChangeNWCause(enChangeRejType, pucRcvMsg[2]);
    if (ucAdaptCause == pucRcvMsg[2])
    {
        /* 未查找到替换后原因值，或替换后原因值不变 */
        return;
    }

    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucAdaptCause)
    {
        if (VOS_TRUE != NAS_MML_GetHplmnCsRejChangeTo17Flg())
        {
            /* 如果替换后原因值为#17，且替换次数是已经达到上限，则不再替换 */
            return;
        }

        /* 计数器+1 */
        NAS_MML_IncHplmnCsRejCauseChangedCounter();
    }

    /* 如果替换后的原因值非#17，或替换后的原因值为#17且替换次数未达到上限，则替换 */
    pucRcvMsg[2] = ucAdaptCause;
}

/*******************************************************************************
  Module:   NAS_MM_HandleVplmnRejCauseChange
  Function: 如果NV配置的CS域VPLMN拒绝原因值为#17，则判断是否需要替换
  Input:    VOS_UINT8    *pucRcvMsg, 当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期  : 2014年10月27日
        作    者  : h00285180
        修改内容  : 问题单号:DTS2014110307415
*******************************************************************************/
VOS_VOID NAS_MM_HandleVplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg
)
{
    VOS_UINT8                           ucAdaptCause = 0;

    ucAdaptCause = NAS_MML_GetVplmnChangeNWCause(enChangeRejType, pucRcvMsg[2]);
    if (ucAdaptCause == pucRcvMsg[2])
    {
        /* 未查找到替换后原因值，或替换后原因值不变 */
        return;
    }
    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucAdaptCause)
    {
        if (VOS_TRUE != NAS_MML_GetVplmnCsRejChangeTo17Flg())
        {
            /* 如果替换后原因值为#17，且替换次数是已经达到上限，则不再替换 */
            return;
        }

        /* 计数器+1 */
        NAS_MML_IncVplmnCsRejCauseChangedCounter();
    }

    /* 如果替换后的原因值非#17，或替换后的原因值为#17且替换次数未达到上限，则替换 */
    pucRcvMsg[2] = ucAdaptCause;
}

/*******************************************************************************
  Module:   NAS_MM_ChangeRegRejCauseAvoidInvalidSim
  Function: 网络拒绝原因值自适应
  Input:    VOS_UINT8    *pucRcvMsg, 当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期  : 2013年10月09日
        作    者  : l00208543
        修改内容  : 问题单号:DTS2013100904573
      2.日    期   : 2013年11月01日
        作    者   : l00208543
        修改内容   : 根据卡类型禁止网络制式
      3.日    期   : 2013年11月19日
        作    者   : l00208543
        修改内容   : 拒绝原因值补丁特性 DTS2013111904411
      4.日    期   : 2014年10月20日
        作    者   : h00285180
        修改内容   : 拒绝原因值PhaseII DTS2014110307415
*******************************************************************************/
VOS_VOID NAS_MM_ChangeRegRejCauseAvoidInvalidSim (
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* 增加测试卡保护，测试卡时不修改，直接返回 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeRegRejCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    if (3 > usMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeRegRejCauseAvoidInvalidSim:WARNING: RCV MM LU REJECT MSG WITH ERROR SIZE!");
        return;
    }
    NAS_MML_SetOriginalRejectCause(pucRcvMsg[2]);

    /* 取得当前驻留的PLMN类型 */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_MM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_CS_REG, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_MM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_CS_REG, pucRcvMsg);

    }
}

/*******************************************************************************
  Module:   NAS_MM_ChangeMmAbortCauseAvoidInvalidSim
  Function: MM Abort场景网络拒绝原因值自适应
  Input:    VOS_UINT8    *pucRcvMsg, 当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期  : 2014年10月20日
        作    者  : h00285180
        修改内容  : 问题单号:DTS2014110307415
*******************************************************************************/
VOS_VOID NAS_MM_ChangeMmAbortCauseAvoidInvalidSim (
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* 增加测试卡保护，测试卡时不修改，直接返回 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeMmAbortCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    if (3 > usMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeMmAbortCauseAvoidInvalidSim:WARNING: RCV MM ABORT MSG WITH ERROR SIZE!");
        return;
    }
    NAS_MML_SetOriginalRejectCause(pucRcvMsg[2]);
    /* 取得当前驻留的PLMN类型 */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_MM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_MM_ABORT, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_MM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_MM_ABORT, pucRcvMsg);
    }
}

/*******************************************************************************
  Module:   NAS_MM_ChangeCmSevRejCauseAvoidInvalidSim
  Function: CM Service Reject场景网络拒绝原因值自适应
  Input:    VOS_UINT8    *pucRcvMsg, 当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期  : 2014年10月20日
        作    者  : h00285180
        修改内容  : 问题单号:DTS2014110307415
*******************************************************************************/
VOS_VOID NAS_MM_ChangeCmSerRejCauseAvoidInvalidSim (
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* 增加测试卡保护，测试卡时不修改，直接返回 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeCmSerRejCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    if (3 > usMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_ChangeCmSerRejCauseAvoidInvalidSim:WARNING: RCV CM SERVICE REJECT MSG WITH ERROR SIZE!");
        return;
    }
    NAS_MML_SetOriginalRejectCause(pucRcvMsg[2]);
    /* 取得当前驻留的PLMN类型 */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_MM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_CM_SER_REJ, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_MM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_CM_SER_REJ, pucRcvMsg);
    }
}

/*******************************************************************************
  Module:   Mm_ComMsgChkProc
  Function: 解析消息类型
  Input:    RRMM_DATA_IND_STRU       *pMsg, RRMM_DATA_IND原语指针
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇   2003.12.10   新版作成
      2.日    期  : 2007年12月21日
        作    者  : l00107747
        修改内容  : 问题单号:A32D13951
      3.日    期   : 2012年12月19日
        作    者   : l00198894
        修改内容   : DTS2012121903140: LCS桩功能实现
      4.日    期  : 2013年03月13日
        作    者  : z00214637
        修改内容  : BodySAR项目
      5.日    期  : 2013年10月09日
        作    者  : l00208543
        修改内容  : DTS2013100904573
      6.日    期   : 2014年10月20日
        作    者   : h00285180
        修改内容   : 拒绝原因值优化PhaseII DTS2014110307415
*******************************************************************************/
VOS_UINT8 Mm_ComMsgChkProc(
                        RRMM_DATA_IND_FOR_PCLINT_STRU       *pMsg               /* 当前处理的消息                           */
                        )
{
    VOS_UINT8                          *pucRcvMsg = pMsg->RcvNasMsg.aucNasMsg;                             /* 获得消息指针                             */
    VOS_UINT16                          usMsgSize = (VOS_UINT16)pMsg->RcvNasMsg.ulNasMsgSize;                  /* 获得消息的Size                           */
    VOS_UINT8                           ucEventId;                                                         /* 事件ID                                   */
    MM_MSG_MM_STATUS_STRU               Msg;

    if ( usMsgSize < 2 )
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgChkProc:WARNING: RCV MSG TOO SHORT!");
    }

    /* 完整性保护检查 */
    if (MM_FALSE == MM_ComCheckIntegrityProtection(pucRcvMsg, usMsgSize))
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgChkProc:WARNING:  Integrity Check Fail!");
    }
    else
    {
        /*收到NAS层消息，置全局变量为TRUE*/
        g_MmGlobalInfo.stMmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;

        switch ( pucRcvMsg[0] & 0x0f )
        {                                                                           /* 判断PD                                   */
        case MM_IE_PD_CALL_CONTROL:                                                 /* CC的消息                                 */
            ucEventId = Mm_ComMsgCcMsgInteChk(pMsg);
            break;
        case MM_IE_PD_SMS_MSG:                                                      /* SMS的消息                                */
            ucEventId = MM_EVENT_ID_SMS_MESSAGE;
            break;
        case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SS的消息                                 */
        case MM_IE_PD_LOCATION_SRVC:                                                /* LCS的消息                                */
            ucEventId = MM_EVENT_ID_SS_MESSAGE;
            break;
        case MM_IE_PD_TEST:                                                         /* TC的消息                                 */
            ucEventId = MM_EVENT_ID_TC_MESSAGE;
            break;
        case MM_IE_PD_MM_MSG:                                                       /* MM的消息                                 */
            if ( 0 != ( pucRcvMsg[0] & 0xf0 ) )
            {
                ucEventId = MM_EVENT_ID_INVALID;
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgChkProc:WARNING: RCV MM MSG SKIP INDICATOR ERROR!");
                break;
            }

            MM_ReportN2MOtaMsg(pucRcvMsg[1] & 0x3f, (NAS_MSG_STRU *)(&(pMsg->RcvNasMsg)));


            switch ( pucRcvMsg[1] & 0x3f )
            {                                                                       /* 判断MM消息的类型                         */
            case MM_IE_MSG_TYPE_AUTH_REQ:                                           /* AUTHENTICATION REQUEST 消息              */
                ucEventId = Mm_ComMsgAuthReqRcv ( pucRcvMsg, usMsgSize );           /* 存储消息并获得事件ID                     */
                break;
            case MM_IE_MSG_TYPE_CM_SERV_REJ:                                        /* CM SERVICE REJECT 消息                   */
                NAS_MM_ChangeCmSerRejCauseAvoidInvalidSim (pucRcvMsg, usMsgSize);

                ucEventId = Mm_ComMsgCmSvcRjctRcv ( pucRcvMsg, usMsgSize );         /* 存储消息并获得事件ID                     */
                g_T3211Flag = 0;
                break;
            case MM_IE_MSG_TYPE_CM_SERV_ACP:                                        /* CM SERVICE ACCEPT 消息                   */
                ucEventId = Mm_ComMsgCmSvcAcceptRcv(pMsg);                          /* 获得事件ID                               */
                g_T3211Flag = 0;
                break;
            case MM_IE_MSG_TYPE_AUTH_REJ:                                           /* AUTHENTICATION REJECT 消息               */
                ucEventId = Mm_ComMsgAuthRjctRcv();                                 /* 获得事件ID                               */
                break;
            case MM_IE_MSG_TYPE_ABORT:                                              /* ABORT 消息                               */
                NAS_MM_ChangeMmAbortCauseAvoidInvalidSim (pucRcvMsg, usMsgSize);
                ucEventId = Mm_ComMsgAbortRcv ( pucRcvMsg, usMsgSize );             /* 存储消息并获得事件ID                     */
                break;
            case MM_IE_MSG_TYPE_ID_REQ:                                             /* IDENTITY REQUEST 消息                    */
                ucEventId = Mm_ComMsgIdReqRcv ( pucRcvMsg, usMsgSize );             /* 存储消息并获得事件ID                     */
                break;
            case MM_IE_MSG_TYPE_MM_INFO:                                            /* MM INFORMATION 消息                      */
                ucEventId = Mm_ComMsgMmInfoRcv ( pucRcvMsg, usMsgSize );        /* 存储消息并获得事件ID */
                break;
            case MM_IE_MSG_TYPE_MM_STA:                                             /* MM STATUS 消息                           */
                ucEventId = Mm_ComMsgMmStatusRcv ( pucRcvMsg, usMsgSize );      /* 存储消息并获得事件ID                     */
                break;
            case MM_IE_MSG_TYPE_TMSI_REALLOC_CMD:                                   /* TMSI REALLOCATION COMMAND 消息           */
                ucEventId =
                            Mm_ComMsgTmsiReallocCmdRcv ( pucRcvMsg, usMsgSize );    /* 存储消息并获得事件ID   */
                break;
            case MM_IE_MSG_TYPE_LU_ACCEPT:
                ucEventId = Mm_ComMsgLuAccptRcv( pucRcvMsg, usMsgSize  );
                break;
            case MM_IE_MSG_TYPE_LU_REJECT:
                NAS_MM_ChangeRegRejCauseAvoidInvalidSim( pucRcvMsg, usMsgSize );
                ucEventId = Mm_ComMsgLuRejctRcv( pucRcvMsg, usMsgSize  );
                break;
            case MM_IE_MSG_TYPE_CM_SERV_PROMPT:
                ucEventId = Mm_ComMsgSvcPromptRcv( pucRcvMsg, usMsgSize );
                break;
            default:
                ucEventId = MM_EVENT_ID_INVALID;                                    /* 无效的事件ID                             */

                Msg.MmIeRjctCause.ucRejCause =
                                NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE;
                Mm_ComMsgMmStatusSnd(&Msg);

                break;
            }
            break;
        default:
            ucEventId = MM_EVENT_ID_INVALID;                                        /* 无效的事件ID                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgChkProc:WARNING: RCV NAS MSG PD UNKNOW!");
            break;
        }
    }

    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgAuthRspSnd
  Function: 填充并发送 AUTHENTICATION RESPONSE 消息
  Input:    MM_MSG_AUTHENTICATION_RSP_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.10   新版作成
*******************************************************************************/
VOS_VOID Mm_ComMsgAuthRspSnd(
                          MM_MSG_AUTHENTICATION_RSP_STRU    *pMsg               /* 要发送的消息的指针                       */
                         )
{
    VOS_UINT8               i;                                                  /* 循环变量                                 */
    VOS_UINT16              usMsgSize = 20;                                     /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */

    if ( MM_IE_AUTN_EXT_PRESENT == pMsg->ucAutnRspParaExtFlg )
    {                                                                           /* AUTN Extention 存在                      */
        usMsgSize = (VOS_UINT16)(8 + pMsg->MmIeAuthRspParaExt.ucLength);
    }
    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgAuthRspSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_AUTH_RES;                                 /* 设置Message type                         */
        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            pucSndMsg[2+i] = pMsg->MmIeAuthRspPara.aucSgnfcntRES[i];            /* 设置AUTN                                 */
        }
        if ( MM_IE_AUTN_EXT_PRESENT == pMsg->ucAutnRspParaExtFlg )
        {                                                                       /* AUTN Extention 存在                      */
            pucSndMsg[6] = 0x21;                                                /* 设置AUTN Extention的IEI                  */
            pucSndMsg[7] = pMsg->MmIeAuthRspParaExt.ucLength;                   /* 设置Length of AUTN Extention             */
            for(i = MM_CONST_NUM_0; i < pMsg->MmIeAuthRspParaExt.ucLength; i++)
            {
                pucSndMsg[8+i] = pMsg->MmIeAuthRspParaExt.aucRES[i];            /* 设置AUTN Extention的内容                 */
            }
            usMsgSize = (VOS_UINT16)(8 + pMsg->MmIeAuthRspParaExt.ucLength);    /* 调整消息实际长度                         */
        }
        else
        {                                                                       /* AUTN Extention 不存在                    */
            usMsgSize = 6;                                                      /* 调整消息实际长度                         */
        }

        #ifdef GSM_GCF_RS_SIM_STUB
        pucSndMsg[2] = 0x11;
        pucSndMsg[3] = 0x10;
        pucSndMsg[4] = 0x13;
        pucSndMsg[5] = 0x12;
        usMsgSize    = 6;
        #endif
        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgAuthFailSnd
  Function: 填充并发送 AUTHENTICATION FAILURE 消息
  Input:    MM_MSG_AUTHENTICATION_FAIL_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.10   新版作成
*******************************************************************************/
VOS_VOID Mm_ComMsgAuthFailSnd(
                          MM_MSG_AUTHENTICATION_FAIL_STRU    *pMsg              /* 要发送的消息的指针                       */
                            )
{
    VOS_UINT8               i;                                                      /* 循环变量                                 */
    VOS_UINT16              usMsgSize = 19;                                         /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                                       /* 定义消息指针                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgAuthFailSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_AUTH_FAIL;                                /* 设置Message type                         */
        pucSndMsg[2] = pMsg->MmIeRejCause.ucRejCause;                           /* 设置Reject Cause                         */

        if ( NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE == pMsg->MmIeRejCause.ucRejCause )
        {                                                                       /* 拒绝原因为 Synch failure                 */
            pucSndMsg[3] = 0x22;                                                /* 设置Authentication Failure parameter的IE
                                                                                 * I                                        */
            pucSndMsg[4] = pMsg->MmIeAuthFailPara.ucLength;                     /* 设置Length of Authentication Failurepara
                                                                                 * meter contents                           */
            for (i = MM_CONST_NUM_0; i < pMsg->MmIeAuthFailPara.ucLength; i++)
            {
                pucSndMsg[5+i] = pMsg->MmIeAuthFailPara.aucAuthFailPara[i];     /* 设置Authentication Failure parameter     */
            }
        }
        else
        {                                                                       /* 拒绝原因为 MAC failure                   */
            usMsgSize = 3;                                                      /* 调整消息实际长度                         */
        }

        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgSetMobileId
  Function: 填充消息中的 MOBILE ID
  Input:
  Output:
  NOTE:
  Return:   MM_TRUE  成功
            MM_FALSE 失败
  History:
      1.张志勇   2003.12.11   新版作成
      2.王毛     2010.09.08   DTS2010081902050
      3.日    期   : 2010年9月30日
        作    者   : 欧阳飞 00132663
        修改内容   : 根据问题单号DTS2010092902368,TMSI只在等效PLMN内有效
      4.日    期   : 2010年12月05日
        作    者   : 欧阳飞 00132663
        修改内容   : 根据问题单号DTS2010120300932,开机时，卡中存在的分配TMSI的网络和
                     NV项中保存的等效PLMN不相同，即使当前驻留小区与卡中网络相同，也使
                     用IMSI进行注册，导致TIM网络注册失败。
      5.日    期   : 2012年11月9日
        作    者   : w00167002
        修改内容   : DTS2012102503890:删除根据EPLMN来进行TMSI的有效性判断,恢复
                     跟协议保持一致，否则TD:GCF:9.4.2.2.1/9.4.2.2.2通不过(开机在
                     00101上注册成功后，分配TMSI,再关机，再指定搜00102成功，
                     发起LAU时需要匹配TMSI,而BALONG 发起的是IMSI)。
*******************************************************************************/
VOS_UINT8 Mm_ComMsgSetMobileId(
                            VOS_UINT8                  *pucSndMsg,              /* 消息的首地址                             */
                            VOS_UINT16                 *pusMsgSize,             /* 消息目前的长度                           */
                            MM_MOBILE_ID_STRU          *pMobileId               /* 源数据指针                               */
                            )
{
    VOS_UINT8                           i;                                                  /* 循环变量                                 */
    VOS_UINT16                          usIndex = *pusMsgSize;                              /* 位置索引                                 */
    VOS_UINT8                          *pTmpImsi;

    /* TMSI有效，且当前驻留网络与分配该TMSI的网络为相同网络或等效PLMN。 */
    if (MM_MS_ID_TMSI_PRESENT == (pMobileId->ucMsIdFlg & MM_MS_ID_TMSI_PRESENT))
    {

        pucSndMsg[usIndex] = 0x05;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0 | MM_IE_MI_ID_TYPE_TMSI;                    /* 设置Type of identity 和奇偶标志位        */
        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            pucSndMsg[usIndex+2+i]
                = (VOS_UINT8)(pMobileId->aucTmsi[i]);                           /* 设置TMSI的内容                           */
        }
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }
    else if ( MM_MS_ID_IMSI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMSI_PRESENT) )
    {

        pTmpImsi = NAS_MML_GetSimImsi();
        PS_MEM_CPY(&pucSndMsg[usIndex],
                   pTmpImsi,
                   pTmpImsi[0]+1);

        *pusMsgSize = (VOS_UINT16)(usIndex + pTmpImsi[0] + 1);           /* 调整消息实际长度                         */
    }
    else if ( MM_MS_ID_IMEI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEI_PRESENT) )
    {
        pucSndMsg[usIndex] = 0x08;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImei[0] & 0xf0);       /* 设置pucSndMsg[usIndex+1]的高四位为digit1 */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEI | 0x08;                   /* 设置pucSndMsg[usIndex+1]低4位为奇偶标志
                                                                                 * 位和Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImei[i];                     /* 设置IMEI剩余的digits                     */
        }
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }
    else if ( MM_MS_ID_IMEISV_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEISV_PRESENT) )
    {
        pucSndMsg[usIndex] = 0x09;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImeisv[0] & 0xf0);     /* 设置pucSndMsg[usIndex+1]高四位为digit 1  */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEISV;                        /* 设置pucSndMsg[usIndex+1]低4位为奇偶标志
                                                                                   位和Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImeisv[i];                   /* 设置IMEISV剩余的digits                   */
        }
        pucSndMsg[usIndex+pucSndMsg[usIndex]] |= 0xf0;                          /* 设置消息最后一个字节的高四位为"1111"     */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }
    else
    {
        pucSndMsg[usIndex] = 0x01;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0;                                            /* 设置pucSndMsg[usIndex+1]低4位为奇偶标志
                                                                                   位和Typeof identity, 高四位为"1111"      */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }

    return MM_TRUE;                                                             /* 返回                                     */
}


/*****************************************************************************
 函 数 名  : NAS_MM_SetPagingRspMobileId
 功能描述  : 填充paging response消息中的 MOBILE ID
 输入参数  : pucSndMsg - 消息的首地址
             pusMsgSize - 消息长度
 输出参数  : pMobileId - mobile id内容
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月10日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2012年11月9日
    作    者   : w00167002
    修改内容   : DTS2012102503890:删除根据EPLMN来进行TMSI的有效性判断,恢复
                  跟协议保持一致，否则TD:GCF:9.4.2.2.1/9.4.2.2.2通不过(开机在
                  00101上注册成功后，分配TMSI,再关机，再指定搜00102成功，
                  发起LAU时需要匹配TMSI,而BALONG 发起的是IMSI)。

*****************************************************************************/
VOS_UINT8 NAS_MM_SetPagingRspMobileId(
    VOS_UINT8                          *pucSndMsg,
    VOS_UINT16                         *pusMsgSize,
    MM_MOBILE_ID_STRU                  *pMobileId
)
{
    VOS_UINT8                           i;                                                  /* 循环变量                                 */
    VOS_UINT16                          usIndex = *pusMsgSize;                             /* 位置索引                                 */
    VOS_UINT8                          *pTmpImsi;

    /* TMSI有效，且当前驻留网络与分配该TMSI的网络并不要求为相同网络或等效PLMN。 */
    if (((MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
      || (MM_STMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId))
     && (MM_MS_ID_TMSI_PRESENT == (pMobileId->ucMsIdFlg & MM_MS_ID_TMSI_PRESENT)))
    {
        pucSndMsg[usIndex] = 0x05;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0 | MM_IE_MI_ID_TYPE_TMSI;                    /* 设置Type of identity 和奇偶标志位        */
        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            pucSndMsg[usIndex+2+i]
                = (VOS_UINT8)(pMobileId->aucTmsi[i]);                           /* 设置TMSI的内容                           */
        }
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }
    else if ( MM_MS_ID_IMSI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMSI_PRESENT) )
    {

        pTmpImsi = NAS_MML_GetSimImsi();
        PS_MEM_CPY(&pucSndMsg[usIndex],
                   pTmpImsi,
                   pTmpImsi[0]+1);

        *pusMsgSize = (VOS_UINT16)(usIndex + pTmpImsi[0] + 1);           /* 调整消息实际长度                         */
    }
    else if ( MM_MS_ID_IMEI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEI_PRESENT) )
    {
        pucSndMsg[usIndex] = 0x08;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImei[0] & 0xf0);       /* 设置pucSndMsg[usIndex+1]的高四位为digit1 */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEI | 0x08;                   /* 设置pucSndMsg[usIndex+1]低4位为奇偶标志
                                                                                 * 位和Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImei[i];                     /* 设置IMEI剩余的digits                     */
        }
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }
    else if ( MM_MS_ID_IMEISV_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEISV_PRESENT) )
    {
        pucSndMsg[usIndex] = 0x09;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImeisv[0] & 0xf0);     /* 设置pucSndMsg[usIndex+1]高四位为digit 1  */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEISV;                        /* 设置pucSndMsg[usIndex+1]低4位为奇偶标志
                                                                                   位和Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImeisv[i];                   /* 设置IMEISV剩余的digits                   */
        }
        pucSndMsg[usIndex+pucSndMsg[usIndex]] |= 0xf0;                          /* 设置消息最后一个字节的高四位为"1111"     */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }
    else
    {
        pucSndMsg[usIndex] = 0x01;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0;                                            /* 设置pucSndMsg[usIndex+1]低4位为奇偶标志
                                                                                   位和Typeof identity, 高四位为"1111"      */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }

    return MM_TRUE;                                                             /* 返回                                     */
}


/*******************************************************************************
  Module:   Mm_ComMsgSetMobileIdForEmc
  Function: 紧急呼过程填充消息中的 MOBILE ID
  Input:
  Output:
  NOTE:
  Return:   MM_TRUE  成功
            MM_FALSE 失败
  History:
      1.  x00115505   2009.07.13   新版作成
*******************************************************************************/
VOS_UINT8 Mm_ComMsgSetMobileIdForEmc(
                            VOS_UINT8                  *pucSndMsg,              /* 消息的首地址                             */
                            VOS_UINT16                 *pusMsgSize,             /* 消息目前的长度                           */
                            MM_MOBILE_ID_STRU          *pMobileId               /* 源数据指针                               */
                            )
{
    VOS_UINT8               i;                                                  /* 循环变量                                 */
    VOS_UINT16              usIndex = *pusMsgSize;                              /* 位置索引                                 */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    VOS_UINT8              *pucIMSI;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-8, begin */
    if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-8, end */
      && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
      && (MM_MS_ID_TMSI_PRESENT == (pMobileId->ucMsIdFlg & MM_MS_ID_TMSI_PRESENT)))
    {
        pucSndMsg[usIndex] = 0x05;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = 0xf0 | MM_IE_MI_ID_TYPE_TMSI;                    /* 设置Type of identity 和奇偶标志位        */

        for ( i = MM_CONST_NUM_0; i < MM_CONST_NUM_4; i++ )
        {
            pucSndMsg[usIndex+2+i]
                = (VOS_UINT8)(pMobileId->aucTmsi[i]);                           /* 设置TMSI的内容                           */
        }

        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }

    else if (MM_MS_ID_IMSI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMSI_PRESENT))
    {

        pucIMSI = NAS_MML_GetSimImsi();

        pucSndMsg[usIndex] = pucIMSI[0];


        PS_MEM_CPY(&pucSndMsg[usIndex+1],
               pucIMSI + 1,
               pucIMSI[0]);

        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }

    else if (MM_MS_ID_IMEI_PRESENT ==
        (pMobileId->ucMsIdFlg & MM_MS_ID_IMEI_PRESENT))
    {
        pucSndMsg[usIndex] = 0x08;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = (VOS_UINT8)(pMobileId->aucImei[0] & 0xf0);       /* 设置pucSndMsg[usIndex+1]的高四位为digit1 */
        pucSndMsg[usIndex+1] |= MM_IE_MI_ID_TYPE_IMEI | 0x08;                   /* 设置pucSndMsg[usIndex+1]低4位为奇偶标志
                                                                                 * 位和Typeof identity                      */
        for ( i = MM_CONST_NUM_1; i < pucSndMsg[usIndex]; i++ )
        {
            pucSndMsg[usIndex+1+i] = pMobileId->aucImei[i];                     /* 设置IMEI剩余的digits                     */
        }

        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }

    else
    {
        pucSndMsg[usIndex] = 0x01;                                              /* 设置Length of mobile identity contents   */
        pucSndMsg[usIndex+1] = MM_IE_MI_ID_TYPE_NO_ID | 0x08;                   /* 设置pucSndMsg[usIndex+1]低4位为奇偶标志
                                                                                   位和Typeof identity, 高四位为"1111"      */
        *pusMsgSize = (VOS_UINT16)(usIndex + pucSndMsg[usIndex] + 1);           /* 调整消息实际长度                         */
    }

    return MM_TRUE;
}

/*******************************************************************************
  Module:   Mm_ComMsgCmSvcReqSnd
  Function: 填充并发送 CM SERVICE REQUEST 消息
  Input:    MM_MSG_CM_SVC_REQ_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.10   新版作成
      2.日    期   : 2006年11月6日
        作    者   : s46746
        修改内容   : 问题单号:A32D06442

      3.日    期   : 2015年3月3日
        作    者   : w00167002
        修改内容   : DTS2015030301449:增加携带CSMO标志
*******************************************************************************/
VOS_VOID Mm_ComMsgCmSvcReqSnd(
                          MM_MSG_CM_SVC_REQ_STRU    *pMsg                       /* 要发送的消息的指针                       */
                            )
{
    VOS_UINT16              usMsgSize = 19;                                     /* 消息长度,以字节为单位                    */

    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgCmSvcReqSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                 /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_CM_SERV_REQ;                              /* 设置Message type                         */

        pucSndMsg[2] = (VOS_UINT8)(pMsg->MmIeCmSvcType.ucCMSvcType & 0x0f);         /* 设置CM service type                      */
        pucSndMsg[2] = (VOS_UINT8)(pucSndMsg[2] | (pMsg->MmIeCKSN.ucCksn << 4));    /* 设置CKSN                                 */

        MM_Fill_IE_ClassMark2(&pucSndMsg[3]);

        usMsgSize = 7;                                                          /* 调整消息实际长度                         */
        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID))
        {
            if ( MM_TRUE == pMsg->ucPrioLeveFlg )
            {                                                                   /* 如果存在Priority                         */
                pucSndMsg[usMsgSize] = (VOS_UINT8)(0x80
                    | (pMsg->MmIePrio.ucPrioLeve & MM_IE_PRIO_LEVE_MASK));      /* 设置Priority的IEI和具体内容              */
                usMsgSize++;                                                    /* 调整消息实际长度                         */
            }

#if (FEATURE_ON == FEATURE_LTE)
            NAS_MM_SetCsfbAdditionalUpdateParameters(VOS_FALSE, NAS_MM_IsNeedSetCsmoFlg(), &usMsgSize, pucSndMsg);
#endif

            Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        }
        else
        {
            /*WUEPS_ASSERT(0);
 */
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                    /* 释放为发送消息申请的内存空间             */
        Mm_TimerStop(MM_TIMER_T3211);
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgCmSvcReqOfRrEstReq
  Function: 填充RRMM_EST_REQ原语中的 CM SERVICE REQUEST 消息
  Input:    MM_MSG_CM_SVC_REQ_STRU *pMsg,要发送的消息的指针
  Output:   VOS_UINT16                 *pusMsgSize,消息的长度
  NOTE:
  Return:   VOS_NULL_PTR 表示消息内存申请失败,否则为成功
  History:
      1.  张志勇   2003.12.11   新版作成
      2.日    期   : 2006年11月6日
        作    者   : s46746
        修改内容   : 问题单号:A32D06442
      3.日    期   : 2006年11月22日
        作    者   : luojian   id:60022475
        修改内容   : 问题单号：A32D07583
      4.日    期   : 2015年3月3日
        作    者   : w00167002
        修改内容   : DTS2015030301449:增加携带CSMO标志
*******************************************************************************/
VOS_UINT8* Mm_ComMsgCmSvcReqOfRrEstReq(
                                    MM_MSG_CM_SVC_REQ_STRU    *pMsg,            /* 要发送的消息的指针                       */
                                    VOS_UINT16                *pusMsgSize       /* 消息的长度指针                           */
                                    )
{
    VOS_UINT16              usMsgSize = 19;                                     /* 消息长度,以字节为单位                    */

    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */

    *pusMsgSize = 0;                                                            /* 消息长度初始化为0                        */

    pucSndMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR != pucSndMsg )
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_CM_SERV_REQ;                              /* 设置Message type                         */

        pucSndMsg[2] = (VOS_UINT8)(pMsg->MmIeCmSvcType.ucCMSvcType & 0x0f);     /* 设置CM service type                      */
        pucSndMsg[2] = (VOS_UINT8)(pucSndMsg[2] | (pMsg->MmIeCKSN.ucCksn << 4));/* 设置CKSN                                 */

        MM_Fill_IE_ClassMark2(&pucSndMsg[3]);

        usMsgSize = 7;                                                          /* 调整消息实际长度                         */

        if (MM_IE_CM_SVC_TYPE_EMG_CALL_EST == pMsg->MmIeCmSvcType.ucCMSvcType)
        {
            if (MM_TRUE == Mm_ComMsgSetMobileIdForEmc(pucSndMsg, &usMsgSize,
                                                    &pMsg->MmIeMobileId.MobileID))
            {
                if (MM_TRUE == pMsg->ucPrioLeveFlg)
                {                                                               /* 如果存在Priority                         */
                    pucSndMsg[usMsgSize] = (VOS_UINT8)(0x80
                        | (pMsg->MmIePrio.ucPrioLeve & MM_IE_PRIO_LEVE_MASK));  /* 设置Priority的IEI和具体内容              */
                    usMsgSize++;                                                /* 调整消息实际长度                         */
                }
                *pusMsgSize = usMsgSize;                                        /* 设置消息的长度,作输出参数使用            */
            }
            else
            {
                MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                  /* 释放为发送消息申请的内存空间             */
                pucSndMsg = VOS_NULL_PTR;                                       /* 指针赋空                                 */
                *pusMsgSize = 0;                                                /* 消息长度置为0                            */
            }
        }
        else
        {
            if (MM_TRUE == Mm_ComMsgSetMobileId(pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID))
            {
                if (MM_TRUE == pMsg->ucPrioLeveFlg)
                {                                                               /* 如果存在Priority                         */
                    pucSndMsg[usMsgSize] = (VOS_UINT8)(0x80
                        | (pMsg->MmIePrio.ucPrioLeve & MM_IE_PRIO_LEVE_MASK));  /* 设置Priority的IEI和具体内容              */
                    usMsgSize++;                                                /* 调整消息实际长度                         */
                }
                *pusMsgSize = usMsgSize;                                        /* 设置消息的长度,作输出参数使用            */
            }
            else
            {
                MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                  /* 释放为发送消息申请的内存空间             */
                pucSndMsg = VOS_NULL_PTR;                                       /* 指针赋空                                 */
                *pusMsgSize = 0;                                                /* 消息长度置为0                            */
            }
        }

        if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
        {
            Mm_TimerStop(MM_TIMER_T3211);
        }

#if (FEATURE_ON == FEATURE_LTE)
        NAS_MM_SetCsfbAdditionalUpdateParameters(VOS_FALSE, NAS_MM_IsNeedSetCsmoFlg(), pusMsgSize, pucSndMsg);
#endif

    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgCmSvcReqOfRrEstReq:ERROR: MALLOC ERROR!");
    }
    return pucSndMsg;                                                           /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgCmReEstReqSnd
  Function: 填充并发送 CM RE-ESTABLISHMENT REQUEST 消息
  Input:    MM_MSG_RE_EST_REQ_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.11   新版作成
      2.日    期   : 2006年11月6日
        作    者   : s46746
        修改内容   : 问题单号:A32D06442
      3.日    期   : 20012年11月15日
        作    者   : t00212959
        修改内容   : DTS2012041801803
*******************************************************************************/
VOS_VOID Mm_ComMsgCmReEstReqSnd(
                            MM_MSG_RE_EST_REQ_STRU    *pMsg                     /* 要发送的消息的指针                       */
                            )
{
    VOS_UINT16              usMsgSize = 23;                                     /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgCmReEstReqSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_REEST_REQ;                                /* 设置Message type                         */

        pucSndMsg[2]
            = (VOS_UINT8)(pMsg->MmIeCKSN.ucCksn & MM_IE_CKSN_KEY_SEQUENCE_MASK);/* 设置CKSN                                 */

        MM_Fill_IE_ClassMark2(&pucSndMsg[3]);

        usMsgSize = 7;                                                          /* 调整消息实际长度                         */
        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID))
        {
            if (MM_MS_ID_TMSI_PRESENT
                == ( MM_MS_ID_TMSI_PRESENT &
                pMsg->MmIeMobileId.MobileID.ucMsIdFlg ) )
            {                                                                   /* 如果Mobile Id为TMSI,接着要设置LAI        */
                pucSndMsg[usMsgSize] = 0x13;                                    /* 设置LAI的IEI                             */
                pucSndMsg[usMsgSize+1]
                    = (VOS_UINT8)((pMsg->MmIeLai.IeLai.PlmnId.ulMcc >> 4)
                                | pMsg->MmIeLai.IeLai.PlmnId.ulMcc );           /* 设置MCC digit 2,digit 1                  */
                pucSndMsg[usMsgSize+2]
                    = (VOS_UINT8)((pMsg->MmIeLai.IeLai.PlmnId.ulMcc >> 16)
                                | (pMsg->MmIeLai.IeLai.PlmnId.ulMnc >> 12));    /* 设置MNC digit 3, MCC digit 3             */
                pucSndMsg[usMsgSize+3]
                    = (VOS_UINT8)((pMsg->MmIeLai.IeLai.PlmnId.ulMnc >> 4)
                                | pMsg->MmIeLai.IeLai.PlmnId.ulMnc );           /* 设置MNC digit 2,digit 1                  */

                pucSndMsg[usMsgSize+4] = (VOS_UINT8)(pMsg->MmIeLai.IeLai.ulLac>>8);      /* 设置LAC高8位                             */
                pucSndMsg[usMsgSize+5] = (VOS_UINT8)pMsg->MmIeLai.IeLai.ulLac; /* 设置LAC低8位                             */

                usMsgSize += 6;                                                 /* 调整消息实际长度                         */

            }
            if (MMCC_EMERGENCY_CALL == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType)
            {
                Mm_SndRrEstReq( RRC_EST_CAUSE_EMERGENCY_CALL_RE_ESTABLISH, MM_FALSE,
                    usMsgSize, pucSndMsg );                                         /* 发送消息                                 */
            }
            else
            {
                Mm_SndRrEstReq( RRC_EST_CAUSE_CALL_RE_ESTABLISH, MM_FALSE,
                    usMsgSize, pucSndMsg );                                         /* 发送消息                                 */
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgCmReEstReqSnd:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgIdRspSnd
  Function: 填充并发送 IDENTITY RESPONSE 消息
  Input:    MM_MSG_ID_RSP_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.11   新版作成
*******************************************************************************/
VOS_VOID Mm_ComMsgIdRspSnd(
                          MM_MSG_ID_RSP_STRU    *pMsg                           /* 要发送的消息的指针                       */
                            )
{
    VOS_UINT16              usMsgSize = 12;                                     /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgIdRspSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_ID_RES;                                   /* 设置Message type                         */

        usMsgSize = 2;                                                          /* 调整消息实际长度                         */
        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID))
        {
            Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgIdRspSnd:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgMmStatusSnd
  Function: 填充并发送 MM STATUS 消息
  Input:    MM_MSG_MM_STATUS_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.11   新版作成
*******************************************************************************/
VOS_VOID Mm_ComMsgMmStatusSnd(
                          MM_MSG_MM_STATUS_STRU    *pMsg                        /* 要发送的消息的指针                       */
                            )
{
    VOS_UINT16              usMsgSize = 3;                                      /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgMmStatusSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_MM_STA;                                   /* 设置Message type                         */
        pucSndMsg[2] = pMsg->MmIeRjctCause.ucRejCause;                          /* 设置Reject Cause                         */

        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgTmsiRelocCpltSnd
  Function: 填充并发送 TMSI REALLOCATION COMPLETE 消息
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.11   新版作成
*******************************************************************************/
VOS_VOID Mm_ComMsgTmsiRelocCpltSnd( )
{
    VOS_UINT16              usMsgSize = 2;                                      /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgTmsiRelocCpltSnd:ERROR: MALLOC ERROR!");
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_TMSI_REALLOC_CPL;                         /* 设置Message type                         */

        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgPagingRspSnd
  Function: 填充并发送 PAGING RESPONSE 消息
  Input:    MM_MSG_PAGING_RSP_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.11   新版作成
      2.日    期   : 2012年3月26日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发,BBIT问题合入
      3.日    期   : 2012年10月10日
        作    者   : z00161729
        修改内容   : DTS2012101101736:mt csfb,paging response中mobile identity type与PAGING REQUEST message消息中不一致
      4.日    期   : 2013年3月30日
        作    者   : l00167671
        修改内容   : 主动上报AT命令控制下移至C核
*******************************************************************************/
VOS_VOID Mm_ComMsgPagingRspSnd(
                            MM_MSG_PAGING_RSP_STRU    *pMsg                     /* 要发送的消息的指针                       */
                            )
{
    VOS_UINT16              usMsgSize = 17;                                     /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */
    VOS_UINT8               ucEstCause  = 0;                                    /* RRC建立的原因                            */
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbService ;

    enCsfbService = NAS_MML_GetCsfbServiceStatus();

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgPagingRspSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */

        pucSndMsg[0] = MM_IE_PD_RRM_MSG;                                        /* 设置PD, Skip Indicator                   */

        pucSndMsg[1] = MM_IE_MSG_TYPE_PAGING_RSP;                               /* 设置Message type                         */

        pucSndMsg[2]
            = (VOS_UINT8)(pMsg->MmIeCksn.ucCksn & MM_IE_CKSN_KEY_SEQUENCE_MASK);    /* 设置CKSN                                 */

        MM_Fill_IE_ClassMark2(&pucSndMsg[3]);
        usMsgSize = 7;                                                          /* 调整消息实际长度                         */
        switch ( g_MmGlobalInfo.ucPagingCause )
            {                                                                   /* RRMM_PAGING_IND与RRMM_EST_REQ中cause转换 */
            case RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL:
                /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
                if ( (VOS_TRUE == NAS_MML_GetRelCauseCsfbHighPrioFlg())
                    && (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == enCsfbService) )
                {
                    ucEstCause = RRC_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL;
                }
                else
                {
                    ucEstCause = RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL;
                }
                /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
                break;
            case RRC_PAGE_CAUSE_TERMINAT_STREAM_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_STREAM_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_INTERACT_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_INTERACT_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_BACKGROUND_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_BACKGROUND_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_CAUSE_UNKNOWN:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN;
                break;
            default:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN;
                break;
            }

        if ( MM_TRUE == NAS_MM_SetPagingRspMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID) )
        {
            Mm_SndRrEstReq( ucEstCause, MM_TRUE,
                usMsgSize, pucSndMsg );                                         /* 发送消息                                 */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgPagingRspSnd:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgCmSvcAbortSnd
  Function: 填充并发送 CM SERVICE ABORT 消息
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.11   新版作成
*******************************************************************************/
VOS_VOID Mm_ComMsgCmSvcAbortSnd( )
{
    VOS_UINT16              usMsgSize = 2;                                      /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                          /* 定义消息指针                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgCmSvcAbortSnd:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_CM_SERV_ABO;                              /* 设置Message type                         */

        Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg, RRC_NAS_MSG_PRIORTY_HIGH);

        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgImsiDetachIniSndOfEstReq
  Function: 填充并使用RRMM_EST_REQ发送 IMSI DETACH INDICATION 消息
  Input:    MM_MSG_IMSI_DETACH_IND_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇      2004.03.17   新版作成
      2.日    期   : 2006年11月6日
        作    者   : s46746
        修改内容   : 问题单号:A32D06442
*******************************************************************************/
VOS_VOID Mm_ComMsgImsiDetachIniSndOfEstReq(
                                       MM_MSG_IMSI_DETACH_IND_STRU    *pMsg     /* 要发送的消息的指针                       */
                                       )
{
    VOS_UINT16              usMsgSize = 13;                                     /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgImsiDetachIniSndOfEstReq:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_IMSI_DETACH_INDICATION;                   /* 设置Message type                         */

        /* 设置Mobile station classmark1             */
        MM_Fill_IE_ClassMark1(&pucSndMsg[2]);

        usMsgSize = 3;                                                          /* 调整消息实际长度                         */

        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID) )
        {
            Mm_SndRrEstReq( RRC_EST_CAUSE_DETACH, MM_FALSE,
                usMsgSize, pucSndMsg );                                         /* 发送消息                                 */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgImsiDetachIniSndOfEstReq:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_ComMsgImsiDetachIniSndOfDataReq
  Function: 填充并使用RRMM_DATA_REQ发送 IMSI DETACH INDICATION 消息
  Input:    MM_MSG_IMSI_DETACH_IND_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇      2004.03.18   新版作成
      2.日    期   : 2006年11月6日
        作    者   : s46746
        修改内容   : 问题单号:A32D06442
*******************************************************************************/
VOS_VOID Mm_ComMsgImsiDetachIniSndOfDataReq(
                                       MM_MSG_IMSI_DETACH_IND_STRU    *pMsg     /* 要发送的消息的指针                       */
                                       )
{
    VOS_UINT16              usMsgSize = 13;                                     /* 消息长度,以字节为单位                    */
    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgImsiDetachIniSndOfDataReq:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[0] = MM_IE_PD_MM_MSG;                                         /* 设置PD, Skip Indicator                   */
        pucSndMsg[1] = MM_IE_MSG_TYPE_IMSI_DETACH_INDICATION;                   /* 设置Message type                         */

        /* 设置Mobile station classmark1             */
        MM_Fill_IE_ClassMark1(&pucSndMsg[2]);

        usMsgSize = 3;                                                          /* 调整消息实际长度                         */

        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID) )
        {
            Mm_SndRrDataReq((VOS_UINT32)usMsgSize, pucSndMsg,
                RRC_NAS_MSG_PRIORTY_HIGH );                                     /* 发送消息                                 */
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgImsiDetachIniSndOfDataReq:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }
    return;                                                                     /* 返回                                     */
}

/*lint -e438 -e830*/

/*****************************************************************************
 函 数 名  : NAS_MM_GetLocationUpdateRequestMsgIELength
 功能描述  : 填充的IE的长度，Table 9.2.17/3GPP TS 24.008: LOCATION UPDATING REQUEST message content
             该长度是所要填充IE的最大长度,IE的实际长度有后续字段负责
 输入参数  : 无
 输出参数  : 返回所要填充IE的最大长度
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT16  NAS_MM_GetLocationUpdateRequestMsgIELength( VOS_VOID )
{
    VOS_UINT16                          usMsgLen;

    usMsgLen = 0;

    /* Mobility management protocol discriminator IE长度1/2字节，Skip Indicator IE长度1/2字节 */
    usMsgLen += 1;

    /* Location Updating Request message type IE长度1字节 */
    usMsgLen += 1;

    /* Location updating type IE 长度1/2字节，Ciphering key sequence number IE长度1/2字节 */
    usMsgLen += 1;

    /*Location area identification IE长度5字节 */
    usMsgLen += 5;

    /* Mobile station classmark IE长度1字节 */
    usMsgLen += 1;

    /* Mobile identity IE长度2-9字节 */
    usMsgLen += 9;

    /* Mobile station classmark for UMTS IE长度5字节 */
    usMsgLen += 5;

    /* Additional update parameters IE长度1字节 */
    usMsgLen += 1;

    /* Device properties IE长度1字节 */
    usMsgLen += 1;

    /* MS network feature support  IE长度1字节 */
    usMsgLen += 1;

    return usMsgLen;
}


/*******************************************************************************
  Module:   Mm_ComMsgLuReqSndOfEstReq
  Function: 填充并使用RRMM_EST_REQ发送 LOCATION UPDATING REQUEST 消息
  Input:    MM_MSG_IMSI_DETACH_IND_STRU *pMsg,要发送的消息的指针
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇      2004.03.17   新版作成
  2.日    期   : 2006年11月6日
    作    者   : s46746
    修改内容   : 问题单号:A32D06442
  3.日    期   : 2009年9月18日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D14551,网络模式II下,从2G通过PCCO过程到3G后,在W下发起的RRC连接请求原因值不符合协议要求
  4.日    期   : 2011年7月12日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，替换g_MmSubLyrShare.MmSuspendShare的全局变量
  5.日    期   : 2012年2月14日
    作    者   : z00161729
    修改内容   : V7R1C50 支持CSFB特性修改,将消息长度由23调整为24
                TS24008 10.5.3.14 Additional update parameters value (octet 1, bit 1 to 4)
                CSMT (1 bit field)
                Bit 1
                0   No additional information.
                1   CS fallback mobile terminating call
                Bits 4 to 2 of octet 1 are spare and shall be all coded as zero.
  6.日    期   : 2012年2月14日
    作    者   : w00167002
    修改内容   : V7R1C50 支持CSFB特性修改,G下LAU时消息填写不正确.
  7.日    期   : 2012年10月22日
    作    者   : t00212959
    修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration

  8.日    期   : 2014年11月26日
    作    者   : w00167002
    修改内容   : DTS2014092806342:在L下被叫CSFB到GSM后，建联失败，后重选到新的位置区
                 发起LAU时候，没有携带CSMT标志，在华为网络上，网络会下发SETUP，被叫
                 成功；在非华为网络上，网络未下发SETUP。修改为携带CSMT标志。
  9.日    期   : 2015年3月3日
    作    者   : w00167002
    修改内容   : DTS2015030301449:增加携带CSMO标志
  10.日    期   : 2015年6月8日
     作    者   : z00161729
     修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Mm_ComMsgLuReqSndOfEstReq(
                               MM_MSG_LU_REQ_STRU    *pMsg                      /* 要发送的消息的指针                       */
                               )
{
    VOS_UINT16              usMsgSize;                                     /* 消息长度,以字节为单位                    */

    VOS_UINT8              *pucSndMsg = VOS_NULL_PTR;                           /* 定义消息指针                             */
    VOS_UINT16              usIdx = 0;
    VOS_UINT8               i;


    usMsgSize = NAS_MM_GetLocationUpdateRequestMsgIELength();

    pucSndMsg = (VOS_UINT8 *) MM_MEM_ALLOC(
                                      VOS_MEMPOOL_INDEX_MM,
                                      usMsgSize,
                                      WUEPS_MEM_NO_WAIT
                                       );                                       /* 申请发送的消息所用的最大内存空间         */
    /*lint -e961*/
    if ( VOS_NULL_PTR == pucSndMsg )
    {

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_ComMsgLuReqSndOfEstReq:ERROR: MALLOC ERROR!");
        return;
    }
    else
    {
        PS_MEM_SET( pucSndMsg, 0, usMsgSize );                                  /* 清零                                     */
        pucSndMsg[usIdx] =  MM_IE_PD_MM_MSG;                                    /* 设置PD                                   */
        pucSndMsg[usIdx++] &= 0x0f;                                             /* Skip Indicator                           */
        pucSndMsg[usIdx++] = MM_IE_MSG_TYPE_LU_REQUEST;                         /* 设置Message type                         */

        pucSndMsg[usIdx] =
            (VOS_UINT8)(pMsg->MmIeLuType.ucLUT & MM_IE_LU_TYPE_LUT_MASK);       /* 设置Location updating type               */
        pucSndMsg[usIdx] = (VOS_UINT8)(pucSndMsg[usIdx] |
                    (pMsg->MmIeLuType.ucFOR & MM_IE_LU_TYPE_FOR_MASK));         /* 设置The Follow-On Request                */
        pucSndMsg[usIdx] =
            (VOS_UINT8)(pucSndMsg[usIdx] | (pMsg->MmIeCksn.ucCksn << 4));       /* 设置CKSN                                 */
        usIdx++;

        pucSndMsg[usIdx]   |=
            (VOS_UINT8)(0x0000000f & pMsg->MmIeLAI.IeLai.PlmnId.ulMcc);
        pucSndMsg[usIdx++] |=
            (VOS_UINT8)((0x00000f00 & pMsg->MmIeLAI.IeLai.PlmnId.ulMcc) >> 4);
        pucSndMsg[usIdx]   |=
            (VOS_UINT8)((0x000f0000 & pMsg->MmIeLAI.IeLai.PlmnId.ulMcc) >> 16);
        pucSndMsg[usIdx++] |=
            (VOS_UINT8)((0x000f0000 & pMsg->MmIeLAI.IeLai.PlmnId.ulMnc) >> 12);
        pucSndMsg[usIdx]   |=
            (VOS_UINT8)(0x0000000f & pMsg->MmIeLAI.IeLai.PlmnId.ulMnc );
        pucSndMsg[usIdx++] |=
            (VOS_UINT8)((0x00000f00 & pMsg->MmIeLAI.IeLai.PlmnId.ulMnc) >> 4 );
        pucSndMsg[usIdx++] =
            (VOS_UINT8)( (0x0000ff00 & pMsg->MmIeLAI.IeLai.ulLac) >> 8 );
        pucSndMsg[usIdx++] =
            (VOS_UINT8)( 0x000000ff & pMsg->MmIeLAI.IeLai.ulLac );

        /* 设置Mobile station classmark1             */
        MM_Fill_IE_ClassMark1(&pucSndMsg[usIdx++]);

        usMsgSize = usIdx;                                                      /* 调整消息实际长度                         */

        if ( MM_TRUE == Mm_ComMsgSetMobileId (pucSndMsg, &usMsgSize,
                                                &pMsg->MmIeMobileId.MobileID) )
        {
            if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType() )
              && (MM_TRUE == pMsg->ucMsClsMskFrUMTSFlg) )
            {
                usIdx = usMsgSize;
                usMsgSize = usMsgSize + 5;
                pucSndMsg[usIdx++] = 0x33;
                pucSndMsg[usIdx++] = pMsg->MmIeMsClsMskFrUMTS.aucClassmark2[0];
                for( i = 0; i < pMsg->MmIeMsClsMskFrUMTS.aucClassmark2[0]; i++ )
                {
                    pucSndMsg[usIdx++] =
                        pMsg->MmIeMsClsMskFrUMTS.aucClassmark2[i + 1];
                }
            }

#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MM_IsNeedSetCsmoFlg())
            {
                NAS_MM_SetCsfbAdditionalUpdateParameters(VOS_FALSE,
                                                         VOS_TRUE,
                                                         &usMsgSize, pucSndMsg);
            }
            else if (VOS_TRUE == NAS_MM_IsNeedSetCsmtFlg())
            {
                NAS_MM_SetCsfbAdditionalUpdateParameters(VOS_TRUE,
                                                         VOS_FALSE,
                                                         &usMsgSize, pucSndMsg);
            }
            else
            {
            }
#endif

            if (VOS_TRUE == NAS_MM_IsNeedSetMsNetworkFeatureSupportIELauReq())
            {
                NAS_MM_SetMsNetworkFeatureSupportIE(&usMsgSize, pucSndMsg);
            }


            Mm_SndRrEstReq( RRC_EST_CAUSE_REGISTRATION, MM_FALSE,
                                                usMsgSize, pucSndMsg );
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuReqSndOfEstReq:WARNING: MSG SET MOBILE ID ERROR!");
        }
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucSndMsg);                          /* 释放为发送消息申请的内存空间             */
    }

    /*lint +e961*/
    return;                                                                     /* 返回                                     */
}

/*lint +e438 +e830*/

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeMobileId
 功能描述  : 解码mobile identity
 输入参数  : VOS_UINT16          *pusIndex
             VOS_UINT8           *pucRcvMsg
             VOS_UINT16          usMsgSize
             VOS_UINT8           *pucMobileIdFlg
             VOS_UINT8           *pucEventId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月3日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeMobileId(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize,
    VOS_UINT8           *pucMobileIdFlg,
    VOS_UINT8           *pucEventId)
{
    VOS_UINT16          usIndex;

    usIndex         = *pusIndex;

    /* 消息中包含IE类型，所以增加类型的长度 */
    usIndex++;

    /* 判断消息中是否包含长度字节信息 */
    if ( usMsgSize < (usIndex + 1) )
    {
        return MM_DECODE_END;
    }
    if (( 0 == pucRcvMsg[usIndex] ) || ( 9 < pucRcvMsg[usIndex] ))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: MOBILE IDENTITY LENGTH Abnormal");
        *pucEventId = MM_EVENT_ID_STATUS_95;
        return MM_DECODE_END;
    }

    /* 判断IE中是否包含mobile identity的完整信息 */
    if ( usMsgSize < (usIndex + pucRcvMsg[usIndex] + 1 ))
    {
        /* 不包含完整信息时，判断IE中是否包含mobile identity中type of identity信息，
           此处的判断是为了GCF用例 26.7.3.2。如果包含IMSI信息，需要删除原来的TMSI */
        if (usMsgSize >= (usIndex + 2))
        {
            if (1 == (pucRcvMsg[usIndex + 1] & MM_IE_MI_ID_TYPE_MASK))
            {
                g_MmMsgLuAccpt.ucMobileIDFlg            = MM_TRUE;
                g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                        = MM_MS_ID_IMSI_PRESENT;
            }
        }
        return MM_DECODE_END;
    }
    if ( MM_FALSE == (*pucMobileIdFlg) )
    {
        *pucMobileIdFlg = MM_TRUE;

        g_MmMsgLuAccpt.ucMobileIDFlg            = MM_TRUE;
        if ( MM_IE_MI_ID_TYPE_IMSI == (pucRcvMsg[usIndex + 1] & 0x07) )
        {
            g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                   = MM_MS_ID_IMSI_PRESENT;
        }
        else if ( MM_IE_MI_ID_TYPE_TMSI == (pucRcvMsg[usIndex + 1] & 0x07) )
        {
            g_MmMsgLuAccpt.MmIeMobileId.MobileID.ucMsIdFlg
                                       = MM_MS_ID_TMSI_PRESENT;
            PS_MEM_CPY(
                    g_MmMsgLuAccpt.MmIeMobileId.MobileID.aucTmsi,
                    &pucRcvMsg[usIndex + 2],
                    4);
        }
        else
        {
        }
        usIndex = usIndex + pucRcvMsg[usIndex] + 1;
    }
    else
    {
        usIndex = usIndex + pucRcvMsg[usIndex] + 1;
    }

    *pusIndex = usIndex;

    return MM_DECODE_SUCCESS;
}

/*lint -e438 -e830*/

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeEplmn
 功能描述  : 解码EPLMN信息
 输入参数  : VOS_UINT16          *pusIndex
             VOS_UINT8           *pucRcvMsg
             VOS_UINT16          usMsgSize
             VOS_UINT16          *pucEventId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月3日
    作    者   : l65478
    修改内容   : 新生成函数

  2.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : EPLMN更新到MML的CTX中
  3.日    期   : 2011年04月09日
    作    者   : C00173809
    修改内容   : DTS2011041800645,plmn list ie的content len异常时,LAU ACC被丢弃.
*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeEplmn(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize,
    VOS_UINT8           *pucEventId)
{
    VOS_UINT16          usIndex;
    VOS_UINT16          usEPLmnLen;
    VOS_UINT8           ucPlmnNum;
    VOS_UINT8           i;

    usIndex         = *pusIndex;

    if ( usMsgSize < (usIndex + 2) )
    {
        return MM_DECODE_END;
    }

    if ( pucRcvMsg[usIndex + 1] < 3 )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV MM LU ACCEPT MSG WITH PLMN LIST SIZE ERROR!");
        return MM_DECODE_END;
    }

    if ( usMsgSize < (usIndex + pucRcvMsg[usIndex + 1] + 2) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV MM LU ACCEPT MSG WITH PLMN LIST SIZE ERROR!");
        return MM_DECODE_END;
    }

    *pusIndex = *pusIndex + pucRcvMsg[usIndex + 1] + 2;

    if ( MM_FALSE == g_MmMsgLuAccpt.ucPlmnListFlg )
    {
        g_MmMsgLuAccpt.ucPlmnListFlg = MM_TRUE;
        usIndex++;
        usEPLmnLen = pucRcvMsg[usIndex];

        ucPlmnNum = pucRcvMsg[usIndex] / 3;
        if (ucPlmnNum > NAS_MAX_EQUPLMN_NUM)
        {
            ucPlmnNum = NAS_MAX_EQUPLMN_NUM;
        }

        g_MmMsgLuAccpt.MmIePlmnList.ucPlmnNum = ucPlmnNum;
        usIndex++;
        for ( i = 0; i < ucPlmnNum; i++ )
        {
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc
                = pucRcvMsg[usIndex + 1] &
                 MM_IE_LU_ID_MCC_DIGIT_3_MASK;                      /* 存储LAI中的 MCC digit 3                  */
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc
                = (g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc << 8)
                | (pucRcvMsg[usIndex] >> 4);                        /* 存储LAI中的 MCC digit 2                  */
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc
                = (g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMcc << 8)
                                 | (pucRcvMsg[usIndex] &
                                 MM_IE_LU_ID_MCC_DIGIT_1_MASK);     /* 存储LAI中的 MCC digit 1                  */

            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc
                = pucRcvMsg[usIndex + 1] >> 4;                      /* 存储LAI中的 MNC digit 3                  */
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc
                = (g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc << 8)
                | (pucRcvMsg[usIndex + 2] >> 4);                    /* 存储LAI中的 MNC digit 2                  */
            g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc
                = (g_MmMsgLuAccpt.MmIePlmnList.aPlmnId[i].ulMnc << 8)
                                 | (pucRcvMsg[usIndex + 2] &
                                 MM_IE_LU_ID_MNC_DIGIT_1_MASK);
            usIndex = usIndex + 3;
        }
        if (usEPLmnLen < (NAS_MAX_EQUPLMN_NUM*3))
        {
            usIndex = usIndex + (usEPLmnLen%3);
        }
        else
        {
        }
    }



    return MM_DECODE_SUCCESS;
}
/*lint +e438 +e830*/

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeOtherOptionalIE
 功能描述  : 解码消息中无法识别的可选IE
 输入参数  : VOS_UINT16          *pusIndex
             VOS_UINT8           *pucRcvMsg
             VOS_UINT16          usMsgSize
             VOS_UINT8           *pucEventId
 输出参数  : 无
 返 回 值  : MM_DECODE_RESULT_ENUM_U32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月3日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeOtherOptionalIE(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize,
    VOS_UINT8           *pucEventId)
{
    VOS_UINT16          usIndex;

    usIndex         = *pusIndex;

    if (0x0 == (pucRcvMsg[usIndex] & 0xF0))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: Unexpected IE type.");
        *pucEventId = MM_EVENT_ID_STATUS_96;
        return MM_DECODE_END;
    }

    else if (0x13 == pucRcvMsg[usIndex])
    {/* not code as comprehension required IEI but as LAI IEI in other MM protocal */
        if (usMsgSize < (usIndex + 1))
        {
            return MM_DECODE_END;
        }
        usIndex = usIndex + pucRcvMsg[usIndex+1] + 2;
    }
    else
    {/* not code as comprehension required IEI */
        usIndex = usIndex + 1;
    }

    *pusIndex = usIndex;

    return MM_DECODE_SUCCESS;
}

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeFollowOn
 功能描述  : 解码follow ON标志
 输入参数  : VOS_UINT16          *pusIndex
             VOS_UINT8           *pucRcvMsg
             VOS_UINT16          usMsgSize
 输出参数  : 无
 返 回 值  : MM_DECODE_RESULT_ENUM_U32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月3日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeFollowOn(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize)
{
    VOS_UINT16          usIndex;

    usIndex         = *pusIndex;

    if ( MM_FALSE == g_MmMsgLuAccpt.ucFollowOFlg )
    {
        g_MmMsgLuAccpt.ucFollowOFlg = MM_TRUE;
    }
    usIndex++;

    *pusIndex = usIndex;

    return MM_DECODE_SUCCESS;
}

/*****************************************************************************
 函 数 名  : NAS_MM_DecodeCTS
 功能描述  : 解码CTS信息
 输入参数  : VOS_UINT16          *pusIndex
             VOS_UINT8           *pucRcvMsg
             VOS_UINT16          usMsgSize
 输出参数  : 无
 返 回 值  : MM_DECODE_RESULT_ENUM_U32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月3日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
MM_DECODE_RESULT_ENUM_U32 NAS_MM_DecodeCTS(
    VOS_UINT16          *pusIndex,
    VOS_UINT8           *pucRcvMsg,
    VOS_UINT16          usMsgSize)
{
    VOS_UINT16          usIndex;

    usIndex         = *pusIndex;

    if ( MM_FALSE == g_MmMsgLuAccpt.ucCtsPermisFlg )
    {
        g_MmMsgLuAccpt.ucCtsPermisFlg = MM_TRUE;
    }
    usIndex++;

    *pusIndex = usIndex;

    return MM_DECODE_SUCCESS;
}

/*****************************************************************************
 函 数 名  : Mm_ComMsgLuAccptRcv
 功能描述  : 存储消息LU ACCEPT
 输入参数  : VOS_UINT8      *pucRcvMsg
             VOS_UINT16      usMsgSize
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月3日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2010年11月24日
    作    者   : l00167671
    修改内容   : MNC或者MCC范围检查错误后，记录日志，不做其他处理
  3.日    期   : 2010年11月26日
    作    者   : z00161729
    修改内容  : DTS2010112604710:周期性LAU accpet消息中如果LAI信息改变且合法，需更新相应全局变量的值
  4.日    期   : 2013年10月25日
    作    者   : w00167002
    修改内容   : DTS2013102201891:增加对紧急呼长度异常的处理。
                 1.按照紧急呼填写的总长度值解析，会超过整个消息的长度，则认为异常；
                 2.按照每个子紧急呼消息的长度值解析，超过了紧急呼填写的总长度值，则认为异常；

                 调整NAS_MM_DecodeEMC函数到MML中NAS_MML_DecodeEmergencyNumList，
                 供GMM/MM解码紧急呼列表使用。
  5.日    期   : 2013年11月19日
    作    者   : l00208543
    修改内容   : 拒绝原因值补丁特性
 9.日    期   : 2014年11月26日
   作    者   : w00167002
   修改内容   : DTS2014092806342:在L下被叫CSFB到GSM后，建联失败，后重选到新的位置区
                发起LAU时候，没有携带CSMT标志，在华为网络上，网络会下发SETUP，被叫
                成功；在非华为网络上，网络未下发SETUP。修改为携带CSMT标志。
 10.日    期   : 2015年03月04日
    作    者   : j00174725
    修改内容   :  DTS2015030306201
 11.日    期   : 2015年5月5日
    作    者   : w00167002
    修改内容   :  csmt修改
 12.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT8 Mm_ComMsgLuAccptRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            )
{
    VOS_UINT8       ucEventId;                              /* 事件ID                                   */
    VOS_UINT16      usIndex;
    VOS_UINT8       ucMobileIdFlg;
    VOS_UINT32      ulResult;

    NAS_MML_LAI_STRU                   *pstAllocT3212ValueLaiInfo = VOS_NULL_PTR;

    pstAllocT3212ValueLaiInfo = NAS_MM_GetAllocT3212ValueLaiInfo();

    /* 更新t3212时长类型为broadcast，如果lau accept中携带了新的t3212时长再更新*/
    NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_BROADCAST);

    usIndex         = 2;
    ucEventId       = MM_EVENT_ID_LU_ACCEPT;
    ucMobileIdFlg   = MM_FALSE;

    PS_MEM_SET( &g_MmMsgLuAccpt, 0, sizeof(MM_MSG_LU_ACCPT_STRU));             /* 清零                                     */

    if (VOS_NULL_PTR == pucRcvMsg)
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV VOS_NULL_PTR MM LU ACCEPT MSG!");
        return ucEventId;
    }

    if (usMsgSize < 7)
    {
        ucEventId = MM_EVENT_ID_STATUS_96;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV MM LU ACCEPT MSG WITH ERROR SIZE!");
        return ucEventId;
    }


    /* lau成功清除CSMT标志 */
    NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);


    /* 收到Accept消息时需要重置计数器 */
    NAS_MM_ResetRejCauseChangedCounter();
    if ( MM_FALSE == MM_IeChkLai( &pucRcvMsg[usIndex] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuAccptRcv:WARNING: RCV MM LU ACCEPT MSG WITH LAI ERROR!");
        g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac = MM_INVALID_LAI;                /* plmn非法*/
    }
    else
    {
        Mm_ComSaveLai( &pucRcvMsg[usIndex], &g_MmMsgLuAccpt.MmIeLAI.IeLai );
    }

    usIndex = usIndex + 5;

    g_MmMsgLuAccpt.ucFollowOFlg             = MM_FALSE;
    g_MmMsgLuAccpt.ucCtsPermisFlg           = MM_FALSE;
    g_MmMsgLuAccpt.ucMobileIDFlg            = MM_FALSE;
    g_MmMsgLuAccpt.ucPlmnListFlg            = MM_FALSE;
    g_MmMsgLuAccpt.ucEmcFlg                 = MM_FALSE;
    Mm_TimerStop(MM_TIMER_T3218);                                           /* 停T3218                                  */
    Mm_ComDelRandRes();                                                     /* 删除RAND和RES                            */

    while ( usIndex < usMsgSize )
    {
        if ( 0x17 == pucRcvMsg[usIndex] )
        {                                                                   /* 解码mobile identity */
            ulResult = NAS_MM_DecodeMobileId(&usIndex, pucRcvMsg, usMsgSize,
                            &ucMobileIdFlg, &ucEventId);
        }
        else if ( 0xa1 == pucRcvMsg[usIndex] )
        {                                                                   /* 解码follow on */
            ulResult = NAS_MM_DecodeFollowOn(&usIndex, pucRcvMsg, usMsgSize);
        }
        else if ( 0xa2 == pucRcvMsg[usIndex] )
        {                                                                   /* 解码CTS */
            ulResult = NAS_MM_DecodeCTS(&usIndex, pucRcvMsg, usMsgSize);
        }
        else if ( 0x4a == pucRcvMsg[usIndex] )
        {                                                                   /* 解码EPLMN */
            ulResult = NAS_MM_DecodeEplmn(&usIndex, pucRcvMsg,
                            usMsgSize, &ucEventId);
        }
        else if (0x34 == pucRcvMsg[usIndex])
        {                                                                   /* Emergency Number List                    */

            (VOS_VOID)NAS_MML_DecodeEmergencyNumList(&usIndex, pucRcvMsg, usMsgSize);

            g_MmMsgLuAccpt.ucEmcFlg = MM_TRUE;

            ulResult = MM_DECODE_SUCCESS;
        }
        else if (0x35 == pucRcvMsg[usIndex])
        {
            if (PS_PTL_VER_R11 <= NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS))
            {
                NAS_MM_UpdateT3212Value_RcvLauAccept(pucRcvMsg[usIndex + 2]);

                pstAllocT3212ValueLaiInfo->stPlmnId.ulMcc   = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMcc;
                pstAllocT3212ValueLaiInfo->stPlmnId.ulMnc   = g_MmMsgLuAccpt.MmIeLAI.IeLai.PlmnId.ulMnc;
                pstAllocT3212ValueLaiInfo->aucLac[0]        = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac >> NAS_MML_OCTET_MOVE_EIGHT_BITS) & (NAS_MML_BYTE_MASK);
                pstAllocT3212ValueLaiInfo->aucLac[1]        = (g_MmMsgLuAccpt.MmIeLAI.IeLai.ulLac) & (NAS_MML_BYTE_MASK);
                pstAllocT3212ValueLaiInfo->enCampPlmnNetRat = NAS_MML_GetCurrNetRatType();

                NAS_MM_SetNetworkT3212ValueType(NAS_MM_T3212_VALUE_TYPE_NONE_BROADCAST);
            }

            usIndex = usIndex + 3;

            ulResult = MM_DECODE_SUCCESS;
        }
        else
        {                                                                   /* 解码其它可选的IE */
            ulResult = NAS_MM_DecodeOtherOptionalIE(&usIndex, pucRcvMsg,
                            usMsgSize, &ucEventId);
        }

        if (MM_DECODE_END == ulResult)
        {
            break;
        }
    }
    return ucEventId;                                                           /* 返回事件ID                               */
}

/*******************************************************************************
  Module:   Mm_ComMsgLuRejctRcv
  Function: 存储消息LU ACCEPT
  Input:    VOS_VOID     *pMsg,  当前处理的消息
            VOS_UINT16    usMsgSize, 消息长度,以字节为单位
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇    2004.03.25   新版作成
      2. 日    期   : 2007年05月11日
         作    者   : luojian id:60022475
         修改内容   : 问题单号:A32D10713
*******************************************************************************/
VOS_UINT8 Mm_ComMsgLuRejctRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_LU_REJECT;                              /* 事件ID                                   */

    PS_MEM_SET( &g_MmMsgLuRjct, 0, sizeof(MM_MSG_LU_RJCT_STRU));               /* 清零                                     */

    if (VOS_NULL_PTR == pucRcvMsg)
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuRejctRcv:WARNING: RCV VOS_NULL_PTR MM LU REJECT MSG!");
    }
    else if (usMsgSize < 3)
    {
        ucEventId = MM_EVENT_ID_STATUS_96;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgLuRejctRcv:WARNING: RCV MM LU REJECT MSG WITH ERROR SIZE!");
    }
    else
    {
        g_MmMsgLuRjct.MmIeRejCause.ucRejCause = pucRcvMsg[2];
    }

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;

    return ucEventId;                                                           /* 返回事件ID                               */
}


/*******************************************************************************
  Module:   Mm_ComMsgSvcPromptRcv
  Function: 存储消息LU ACCEPT
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_UINT8,事件ID,详见MM_Def.h中关于事件的宏定义
  History:
      1.  张志勇      2004.04.14   新版作成
*******************************************************************************/
VOS_UINT8 Mm_ComMsgSvcPromptRcv (
                            VOS_UINT8      *pucRcvMsg,                              /* 当前处理的消息                           */
                            VOS_UINT16      usMsgSize                               /* 消息长度,以字节为单位                    */
                            )
{
    VOS_UINT8       ucEventId = MM_EVENT_ID_CM_SVC_PROMPT;                          /* 事件ID                                   */

    if (VOS_NULL_PTR == pucRcvMsg)
    {
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgSvcPromptRcv:WARNING: RCV VOS_NULL_PTR MM CM SVC PROMPT MSG!");
        return ucEventId;
    }
    else if (usMsgSize < 3)
    {
        ucEventId = MM_EVENT_ID_STATUS_96;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgSvcPromptRcv:WARNING: RCV MM CM SVC PROMPT MSG WITH ERROR SIZE!");
        return ucEventId;
    }
    else
    {

    }

    if ( MM_FALSE == MM_IeChkPdAndSapi( &pucRcvMsg[2] ) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgSvcPromptRcv:WARNING: RCV MM CM SVC PROMPT MSG WITH PD AND SAPI ERROR!");
        return MM_EVENT_ID_STATUS_95;
    }

    if ( MM_IE_PD_CALL_CONTROL != ( pucRcvMsg[2] & 0x0f ) )
    {                                                                           /* PD不合法                                 */
        ucEventId = MM_EVENT_ID_INVALID;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_ComMsgSvcPromptRcv:WARNING: RCV MM CM SVC PROMPT MSG WITH PD ERROR!");
    }

    return ucEventId;                                                           /* 返回事件ID                               */
}
/*******************************************************************************
  Module:   MM_IeChkLai
  Function: 检查IE LAI的正确性
  Input:    VOS_UINT8      *pucRcvIe  当前处理的消息
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  张志勇    2005.01.12   新版作成
*******************************************************************************/
VOS_UINT8 MM_IeChkLai (
                   VOS_UINT8      *pucRcvIe                                         /* 当前处理的消息                           */
                   )
{
    VOS_UINT8   ucIndex = 0;

    if( ( pucRcvIe[ucIndex] & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    if( ( ( pucRcvIe[ucIndex] >> 4 ) & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    if( ( pucRcvIe[ucIndex + 1] & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    if( ( ( ( pucRcvIe[ucIndex + 1] >> 4 ) & 0x0F ) > 9 ) &&
        ( ( ( pucRcvIe[ucIndex + 1] >> 4 ) & 0x0F ) != 0x0F ) )
    {
        return MM_FALSE;
    }
    if( ( pucRcvIe[ucIndex + 2] & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    if( ( ( pucRcvIe[ucIndex + 2] >> 4 ) & 0x0F ) > 9 )
    {
        return MM_FALSE;
    }
    return MM_TRUE;
}
/*******************************************************************************
  Module:   MM_IeChkMblId
  Function: 检查IE Mobile ID的正确性
  Input:    VOS_UINT8      *pucRcvIe  当前处理的消息
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  张志勇    2005.01.12   新版作成
      2.  s46746 2005.10.17   修改
*******************************************************************************/
VOS_UINT8 MM_IeChkMblId (
                   VOS_UINT8      *pucRcvIe                                         /* 当前处理的消息                           */
                   )
{
    VOS_UINT8   ucIndex = 0;
    VOS_UINT8   ucLength = 0;

    if( ( pucRcvIe[ucIndex + 1] & MM_IE_MI_ID_TYPE_MASK ) > 4 )
    {
        return MM_FALSE;
    }
    if ( ( MM_IE_MI_ID_TYPE_IMSI == ( pucRcvIe[ucIndex + 1] & \
     MM_IE_MI_ID_TYPE_MASK ) ) ||
       ( MM_IE_MI_ID_TYPE_IMEI == ( pucRcvIe[ucIndex + 1] &\
        MM_IE_MI_ID_TYPE_MASK ) ) ||
       ( MM_IE_MI_ID_TYPE_IMEISV == ( pucRcvIe[ucIndex + 1] & \
        MM_IE_MI_ID_TYPE_MASK ) ) )
    {
        if ( 0 == (pucRcvIe[ucIndex + 1] & 0x08) )
        {
            ucLength = pucRcvIe[ucIndex];
            if ((pucRcvIe[ucLength] & MM_IE_MI_ID_DIGIT_1_MASK ) != 0xF0)
            {
                return MM_FALSE;
            }
        }
    }
    else
    {
        if( ( pucRcvIe[ucIndex + 1] & MM_IE_MI_ID_DIGIT_1_MASK ) != 0xF0 )
        {
            return MM_FALSE;
        }
    }

    return MM_TRUE;
}
/*******************************************************************************
  Module:   MM_IeChkPlmnLst
  Function: 检查IE PLMN LIST的正确性
  Input:    VOS_UINT8      *pucRcvIe  当前处理的消息
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  张志勇    2005.01.13   新版作成
*******************************************************************************/
VOS_UINT8 MM_IeChkPlmnLst (
                   VOS_UINT8      *pucRcvIe                                         /* 当前处理的消息                           */
                   )
{
    VOS_UINT8   ucIndex = 0;
    VOS_UINT8   ucPlmnNum;

    if ( 0 != ( pucRcvIe[ucIndex] % 3 ) )
    {
        return MM_FALSE;
    }
    else
    {
        ucPlmnNum = pucRcvIe[ucIndex] / 3;
        if (ucPlmnNum > 15)
        {
            return MM_FALSE;
        }
    }

    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkCksn
  Function: 检查IE CKSN的正确性
  Input:    VOS_UINT8      *pucRcvIe  当前处理的消息
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  张志勇    2005.01.13   新版作成
*******************************************************************************/
VOS_UINT8 MM_IeChkCksn (
                   VOS_UINT8      *pucRcvIe                                         /* 当前处理的消息                           */
                   )
{
    return MM_TRUE;
}


/*******************************************************************************
  Module:   MM_IeChkSprHalfOctet
  Function: 检查IE Spare Half Octet的正确性
  Input:    VOS_UINT8      *pucRcvIe  当前处理的消息
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  张志勇    2005.01.13   新版作成
*******************************************************************************/
VOS_UINT8 MM_IeChkSprHalfOctet (
                   VOS_UINT8      *pucRcvIe                                         /* 当前处理的消息                           */
                   )
{
    if ( 0 != ( pucRcvIe[0] & 0xF0 ) )
    {
        return MM_FALSE;
    }

    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkRand
  Function: 检查IE RAND的正确性
  Input:    VOS_UINT8      *pucRcvIe  当前处理的消息
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  张志勇    2005.01.13   新版作成
*******************************************************************************/
VOS_UINT8 MM_IeChkRand (
                   VOS_UINT8      *pucRcvIe                                         /* 当前处理的消息                           */
                   )
{
    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkAutn
  Function: 检查IE AUTN的正确性
  Input:    VOS_UINT8      *pucRcvIe  当前处理的消息
            VOS_UINT8      ucflg       是否为可选项
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  张志勇    2005.01.13   新版作成
*******************************************************************************/
VOS_UINT8 MM_IeChkAutn (
                   VOS_UINT8      *pucRcvIe                                         /* 当前处理的消息                           */
                   )
{
    VOS_UINT8       ucIndex = 0;

    if ( 16 != pucRcvIe[ucIndex] )
    {
        return MM_FALSE;
    }
    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkIdType
  Function: 检查IE ID TYPE的正确性
  Input:    VOS_UINT8      *pucRcvIe  当前处理的消息
  Output:
  NOTE:
  Return:   MM_TRUE/MM_FALSE
  History:
      1.  张志勇    2005.01.13   新版作成
*******************************************************************************/
VOS_UINT8 MM_IeChkIdType (
                   VOS_UINT8      *pucRcvIe                                         /* 当前处理的消息                           */
                   )
{
    if( ( 1 != ( pucRcvIe[0] & MM_IE_ID_TYPE_IDTYPE_MASK) )&&
        ( 2 != ( pucRcvIe[0] & MM_IE_ID_TYPE_IDTYPE_MASK) )&&
        ( 3 != ( pucRcvIe[0] & MM_IE_ID_TYPE_IDTYPE_MASK) )&&
        ( 4 != ( pucRcvIe[0] & MM_IE_ID_TYPE_IDTYPE_MASK ) ) )
    {
        return MM_FALSE;
    }
    return MM_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkPdAndSapi
  Function: 对IE"PD and SAPI"检查
  Input:    VOS_UINT8 *pIePdAndSapi,  被检查IE首地址
  Output:
  NOTE:
  Return:   VOS_UINT8,检查结果,MM_TRUE/MM_FALSE,成功/失败
  History:
      1.  张志勇    2005.01.13   新版作成
*******************************************************************************/
VOS_UINT8 MM_IeChkPdAndSapi( VOS_UINT8 *pIePdAndSapi )
{
    VOS_UINT8 ucRet = MM_TRUE;
    VOS_UINT8 ucIndex = 0;
    VOS_UINT8 ucPd,ucSapi;

    ucSapi = ( pIePdAndSapi[ucIndex] & 0x30 ) >> 4;
    ucPd   = ( pIePdAndSapi[ucIndex] & 0x0f );
    if ( (0x00 != ucSapi) && (0x03 != ucSapi) )
    {
        ucRet = MM_FALSE;
    }
    else
    {
        ;
    }
    if ( MM_TRUE == ucRet )
    {
        if (  (0x07 == ucPd)
           || (0x0d == ucPd)
           || (0x0e == ucPd)
           || (0x0f == ucPd)
           )
        {
            ucRet = MM_FALSE;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
    return ucRet;
}

/*******************************************************************************
  Module:   MM_IeChkDayLightSavTim
  Function: 对IE"Daylight Saving Time"检查
  Input:    VOS_UINT8 *pIeDayLightSvTim,  被检查IE首地址
  Output:
  NOTE:
  Return:   VOS_UINT8,检查结果,MM_TRUE/MM_FALSE,成功/失败
  History:
    1.张志勇    2005.01.13   新版作成

    2.日    期   : 2010年3月22日
      作    者   : o00132663
      修改内容   : NAS R7协议升级，解析MM INFO消息的TIME ZONE字段
*******************************************************************************/
VOS_UINT8 MM_IeChkDayLightSavTim( VOS_UINT8* pIeDayLightSvTim )
{
    VOS_UINT8 ucRet = MM_TRUE;
    VOS_UINT8 ucIndex = 0;

    if ( 1 == pIeDayLightSvTim[ucIndex] )
    {
        ucIndex ++;
        if( (0x00 != pIeDayLightSvTim[ucIndex])
            && (0x01 != pIeDayLightSvTim[ucIndex])
            && (0x02 != pIeDayLightSvTim[ucIndex])
            )
        {
            ucRet = MM_FALSE;
        }
        else
        {
            g_MmMsgMmInfo.ucNWDyLitSavTmFlg = VOS_TRUE;
            g_MmMsgMmInfo.MmIeNWDyLitSavTm.ucValue = pIeDayLightSvTim[ucIndex];
        }
    }
    else
    {
        ucRet = MM_FALSE;
    }

    return ucRet;
}

/*******************************************************************************
  Module:   MM_IeChkLsaIdtfr
  Function: 对IE"LSA Identifier"检查
  Input:    VOS_UINT8 *pIeLsaIdTfr,  被检查IE首地址
  Output:
  NOTE:
  Return:   VOS_UINT8,检查结果,VOS_TRUE/VOS_FALSE,成功/失败
  History:
      1.  张志勇    2005.01.13   新版作成
*******************************************************************************/
VOS_UINT8 MM_IeChkLsaIdtfr( VOS_UINT8* pIeLsaIdTfr )
{
    VOS_UINT8 ucRet = VOS_TRUE;
    VOS_UINT8 ucIndex = 0;

    if ( pIeLsaIdTfr[ucIndex] <= 3 )
    {
        ;
    }
    else
    {
        ucRet = VOS_FALSE;
    }
    return ucRet;
}

/*******************************************************************************
  Module:   MM_IeChkTimAndTimZone
  Function: 对IE"Time Zone and Time"检查
  Input:    VOS_UINT8 *pIeTimAndTimZone,  被检查IE首地址
  Output:
  NOTE:
  Return:   VOS_UINT8,检查结果,MM_TRUE/MM_FALSE,成功/失败
  History:
    1.张志勇    2005.01.13   新版作成

    2.日    期   : 2010年3月22日
      作    者   : o00132663
      修改内容   : NAS R7协议升级，解析MM INFO消息的TIME & TIME ZONE字段
*******************************************************************************/
VOS_UINT8 MM_IeChkTimAndTimZone( VOS_UINT8 * pIeTimAndTimZone )
{
    VOS_INT8    cTimeZone;
    VOS_UINT8   ucDigit;

    /*格式转换: 网络下发的格式为BCD码，高字节为个位数，低字节为十位数, 如: 0x51 => 15 */
    /* 第一个字节为 Year */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucYear = ((pIeTimAndTimZone[0] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[0] & 0xf0) >> 4);
    if ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucYear > 99)
    {
        return VOS_FALSE;
    }

    /* 第二个字节为 Month */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMonth = ((pIeTimAndTimZone[1] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[1] & 0xf0) >> 4);
    if (  ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMonth > 12 )
        ||( 0 == g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMonth ) )
    {
        return VOS_FALSE;
    }

    /* 第三个字节为 Day */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucDay = ((pIeTimAndTimZone[2] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[2] & 0xf0) >> 4);
    if ( ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucDay > 31)
      || ( 0 == g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucDay ) )
    {
        return VOS_FALSE;
    }

    /* 第四个字节为 Hour */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucHour = ((pIeTimAndTimZone[3] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[3] & 0xf0) >> 4);
    if ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucHour >= 24)
    {
        return VOS_FALSE;
    }

    /* 第五个字节为 Minute */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMinute = ((pIeTimAndTimZone[4] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[4] & 0xf0) >> 4);
    if ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucMinute >= 60)
    {
        return VOS_FALSE;
    }

    /* 第六个字节为 Second */
    g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucSecond = ((pIeTimAndTimZone[5] & 0x0f) * 10)
                                                     +((pIeTimAndTimZone[5] & 0xf0) >> 4);
    if ( g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.ucSecond >= 60)
    {
        return VOS_FALSE;
    }

    /* 第七个字节为 TimeZone */
    ucDigit = (pIeTimAndTimZone[6] & 0xF0) >> 4;
    if ( ucDigit > 9 )
    {
        return VOS_FALSE;
    }
    cTimeZone = (VOS_INT8)(((pIeTimAndTimZone[6] & 0x07) * 10) + ucDigit);

    /* 判断时区的正负值 */
    if (pIeTimAndTimZone[6] & 0x08)
    {
        g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.cTimeZone = - cTimeZone;
    }
    else
    {
        g_MmMsgMmInfo.MmIeUnvrslTmAndLocalTmZone.cTimeZone = cTimeZone;
    }

    g_MmMsgMmInfo.ucUnvrslTmAndLocalTmZoneFlg = VOS_TRUE;

    return VOS_TRUE;
}
/*******************************************************************************
  Module:   MM_IeChkTimZone
  Function: 对IE"Time Zone"检查
  Input:    VOS_UINT8 *pIeTimZone,  被检查IE首地址
  Output:
  NOTE:
  Return:   无
  History:
      1.  张志勇    2005.01.13   新版作成

      2.日    期   : 2010年3月22日
        作    者   : o00132663
        修改内容   : NAS R7协议升级，解析MM INFO消息的TIME ZONE字段

      3.日    期   : 2010年7月1日
        作    者   : 欧阳飞
        修改内容   : DTS2010062801177,增加对IE值的有效性检查
*******************************************************************************/
VOS_UINT8 MM_IeChkTimZone( VOS_UINT8* pIeTimZone )
{
    VOS_INT8    cTimeZone;
    VOS_UINT8   ucDigit;

    ucDigit = ((*pIeTimZone) & 0xF0) >> 4;
    if ( ucDigit > 9 )
    {
        /* TimeZone 值非法 */
        return VOS_FALSE;
    }

    cTimeZone = (VOS_INT8)((((*pIeTimZone) & 0x07) * 10) + ucDigit);

    /* 保存Time Zone */
    g_MmMsgMmInfo.ucLocalTmZoneFlg = VOS_TRUE;

    /* 判断时区的正负值 */
    if ((*pIeTimZone) & 0x08)
    {
        g_MmMsgMmInfo.MmIeLocalTmZone.cTimeZone = - cTimeZone;
    }
    else
    {
        g_MmMsgMmInfo.MmIeLocalTmZone.cTimeZone = cTimeZone;
    }

    return VOS_TRUE;
}

/*******************************************************************************
  Module:   MM_IeChkNtwkNam
  Function: 对IE"Network Name"检查
  Input:    VOS_UINT8 *pIeNtWkNam,  被检查IE首地址
  Output:
  NOTE:
  Return:   VOS_UINT8,检查结果,VOS_TRUE/VOS_FALSE,成功/失败
  History:
      1.  张志勇    2005.01.13   新版作成
      2.  日    期   : 2009年06月23日
          作    者   : l00130025
          修改内容   : 问题单:AT2D12543,【IOT测试】mm info network name IE检查错误，RAU失败
*******************************************************************************/
VOS_UINT8 MM_IeChkNtwkNam( VOS_UINT8* pIeNtWkNam )
{
    VOS_UINT8 ucRet = VOS_TRUE;
    VOS_UINT8 ucIndex = 0;
    VOS_UINT8 ucIeLen,ucOctetN,ucCodScheme;

    /*lint -e961*/
    ucIeLen     = pIeNtWkNam[ucIndex++];
    /*lint +e961*/
    ucOctetN    = pIeNtWkNam[ucIeLen];
    ucCodScheme = ( 0x70 & pIeNtWkNam[ucIndex] ) >> 4;

    if ( ( (0 == ucCodScheme) || (1 == ucCodScheme) )
        && (0 != (0x80 & pIeNtWkNam[ucIndex])) )
    {
        switch( ( 0x07 & pIeNtWkNam[ucIndex] ) )
        {
        case 0:
            break;
        case 1:
            if ( 0 != ( 0x80 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 2:
            if ( 0 != ( 0xc0 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 3:
            if ( 0 != ( 0xe0 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 4:
            if ( 0 != ( 0xf0 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 5:
            if ( 0 != ( 0xf8 & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 6:
            if ( 0 != ( 0xfc & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        case 7:
            if ( 0 != ( 0xfe & ucOctetN ) )
            {
                ucRet = VOS_FALSE;
            }
            break;
        default:
            break;
        }
    }
    else
    {
        ucRet = VOS_FALSE;
    }

    return ucRet;
}
/*****************************************************************************
 函 数 名  : NAS_MM_CheckSigConnStatusAffectAttach
 功能描述  : 检查信令连接是否影响ATTACH
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月29日
    作    者   : w00166186
    修改内容   : 新生成函数
  2. 日    期   : 2013年6月18日
     作    者   : l65478
     修改内容   : 问题单号：DTS2013061406222,发起RAU时应该判断 CS的业务状态

*****************************************************************************/
VOS_UINT32 NAS_MM_CheckSigConnStatusAffectAttach(
    MMCMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    if(((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
      && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState ))
    && (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
    && ((GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg)
     || (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg)))
    {
        return VOS_TRUE;
    }


    if (( MMC_MM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType )
     && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState)
     && (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg))
    {
        return VOS_TRUE;
    }

    /* CS当前在专有过程中,直接返回注册结果 */
    if ((( MMC_MM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType )
     || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType))
     && (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg))
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_CheckSimStatusBeforeAttachAction
 功能描述  : 检查ATTACH类型和USIM状态的冲突
 输入参数  : MMCGMM_ATTACH_REQ_STRU              *pstAttachReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月5日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_CheckSimStatusBeforeAttachAction(
    MMCMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_SIM_STATUS_STRU            *pstUsimStatus = VOS_NULL_PTR;

    pstUsimStatus = NAS_MML_GetSimStatus();

    /* USIM CS域无效，直接回复ATTACH CNF */
    if ( ( MMC_MM_ATTACH_TYPE_GPRS  != pstAttachReq->enAttachType )
      && ( VOS_TRUE            != pstUsimStatus->ucSimCsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_CheckSimStatusAffectAttach:WARNING: CS USIM is invalid.");
        NAS_MM_SndMmcAttachCnf();
        return VOS_TRUE;
    }

    /* USIM PS域无效，MMC_GMM_ATTACH_TYPE_GPRS_IMSI类型转换为MMC_MM_ATTACH_TYPE_IMSI */
    if ( ( MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
      && ( VOS_TRUE                != pstUsimStatus->ucSimPsRegStatus ) )
    {
        pstAttachReq->enAttachType = MMC_MM_ATTACH_TYPE_IMSI;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConflictWithDetach
 功能描述  : 收到MMCMM_ATTACH_REQ消息后，判定当前是否存在detach操作，存在则
              返回VOS_TRUE
 输入参数  : ulAttachType:attach的类型
 输出参数  : 无
 返 回 值  : 事件ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月28日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_ConflictWithDetach(VOS_UINT32 ulAttachType)
{
    /* 当前MM的detach标志位为VOS_TRUE，ATTACH类型是MMC_MM_ATTACH_TYPE_IMSI
       或者MMC_MM_ATTACH_TYPE_GPRSIMSI ,返回VOS_TRUE */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo = VOS_NULL_PTR;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* 之前不存在DETACH流程 */
    if ( MM_WAIT_NULL_DETACH == g_MmGlobalInfo.stDetachInfo.enDetachType)
    {
        return VOS_FALSE;
    }

    /* A+I模式 */
    if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
      && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode ) )
    {
        /* 网络模式I下,存DETACH流程,直接回复CNF */
        if ( MMC_MM_ATTACH_TYPE_IMSI == (ulAttachType
                                        & MMC_MM_ATTACH_TYPE_IMSI))
        {
            NAS_MM_SndMmcAttachCnf();
        }
        return VOS_TRUE;
    }
    else
    {
        if ( ( (MMC_MM_ATTACH_TYPE_IMSI == ulAttachType )
             && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType
                                     & GMM_WAIT_CS_DETACH ) ) )
          || ( MMC_MM_ATTACH_TYPE_GPRS_IMSI == ulAttachType ) )
        {
            /* CS ATTACH 和DETACH冲突,直接回复CNF */
            NAS_MM_SndMmcAttachCnf();
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : NAS_MM_ConflictWithAttach
 功能描述  : 检查ATTACH冲突
 输入参数  : VOS_UINT32 enAttachType
             VOS_UINT32 ulOpID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年07月13日
   作    者   : W00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MM_IsAttachRepeated(
    VOS_UINT32                          ulAttachType,
    VOS_UINT32                          ulOpID)
{
    /* 之前存在CS ATTACH 收到CS ATTACH，更新OPID后直接返回 */
    if (  MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                              & MM_WAIT_CS_ATTACH))
    {
        g_MmGlobalInfo.stAttachInfo.ulOpid = ulOpID;
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_PreProcAttachReq
 功能描述  : 收到MMCMM_ATTACH_REQ消息后，判定是否在该预处理函数中处理掉
              MMCMM_ATTACH_REQ消息，不进各状态处理
 输入参数  : pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : 事件ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月28日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2011年11月16日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2011111402583,opid值错误，导致AT挂死
  3.日    期   : 2012年11月16日
    作    者   : W00176964
    修改内容   : DTS2012111301625:PS detach后进行联合attach时,收到系统消息错误触发LAU
  4.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  4.日    期   : 2015年9月1日
    作    者   : j00174725
    修改内容   : DTS2015090105057
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvMmcAttachReq_PreProc(
    VOS_VOID                           *pstRcvMsg
)
{
    MMCMM_ATTACH_REQ_STRU              *pstAttachReq;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstAttachReq    = (MMCMM_ATTACH_REQ_STRU*)pstRcvMsg;
    pstCampInfo     = NAS_MML_GetCurrCampPlmnInfo();

    /* 判定是否需要处理该消息，无效消息返函数返回MM_EVENT_ID_INVALID */
    if ((MMC_MM_ATTACH_TYPE_IMSI     != pstAttachReq->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS_IMSI!= pstAttachReq->enAttachType))
    {

        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_MM_RcvMmcAttachReq_PreProc:ATTACH TYPE INVALID");
        return MM_EVENT_ID_INVALID;
    }

    /* PS非接入禁止的情况,需要清除LIKEB标记，避免重复发起LAU */
    if (MM_TRUE == g_MmGlobalInfo.ucSysInfoFlg)
    {
        if ( ( (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
            || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType) )
         && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod) )
        {
            /* FobidnFlag 在MMC 已经做个判断，这里不需要加判断 */
            if ( (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
              && (MM_UNSUPPORT_GPRS != g_MmGlobalInfo.usRac) )
            {
                if((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
                || (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType))
                {
                    g_MmGlobalInfo.ucLikeB = MM_FALSE;
                }
            }
        }
    }


    g_MmGlobalInfo.stAttachInfo.ulOpid = pstAttachReq->ulOpid;

    if (VOS_TRUE == NAS_MM_CheckSigConnStatusAffectAttach(pstAttachReq))
    {
        NAS_MM_SndMmcAttachCnf();
        return MM_EVENT_ID_INVALID;
    }

    /* CS域卡无效，回复ATTACH_CNF，返回MM_EVENT_ID_INVALID */
    if (VOS_TRUE == NAS_MM_CheckSimStatusBeforeAttachAction(pstAttachReq))
    {
        return MM_EVENT_ID_INVALID;
    }

    /* 检查是否和之前的DETACH有冲突 */
    if (VOS_TRUE == NAS_MM_ConflictWithDetach(pstAttachReq->enAttachType))
    {
        return MM_EVENT_ID_INVALID;
    }

    /* 检查是否和之前的ATTACH有冲突 */
    if (VOS_TRUE == NAS_MM_IsAttachRepeated(pstAttachReq->enAttachType, pstAttachReq->ulOpid))
    {
        return MM_EVENT_ID_INVALID;
    }

    /* 网络模式II下更改ATTACH类型 */
    if ((NAS_MML_NET_MODE_II            == pstCampInfo->enNetworkMode)
     && (MMC_MM_ATTACH_TYPE_GPRS_IMSI   == pstAttachReq->enAttachType))
    {
        pstAttachReq->enAttachType = MMC_MM_ATTACH_TYPE_IMSI;
    }

    /* 如果当前ucCsAttachState的状态已经附着，则回复ATTACH_CNF，
       返回MM_EVENT_ID_INVALID */
    if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
    {
        NAS_MM_SndMmcAttachCnf();
        return MM_EVENT_ID_INVALID;
    }

    /* 设置等待ATTACH结果标志位，返回MM_EVENT_ID_ATTACH_REQ */
    g_MmGlobalInfo.stAttachInfo.enAttachType    = pstAttachReq->enAttachType;

    /* 置为CsAttachAllowFlg 为VOS_TRUE */
    NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);

    return MM_EVENT_ID_ATTACH_REQ;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvAttachReq_InterRatChange
 功能描述  : 在MM_INTER_RAT_CHANGE，收到MMCMM_ATTACH_REQ消息后的处理
 输入参数  : pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : 事件ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月28日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_RcvAttachReq_InterRatChange(
    VOS_VOID                          *pMsg
)
{
    /* 直接回复MMCMM_ATTACH_CNF */
    NAS_MM_SndMmcAttachCnf();

    /* 清除等待ATTACH结果标志位 */
    g_MmGlobalInfo.stAttachInfo.enAttachType    = MM_WAIT_NULL_ATTACH;

    /* 置为CsAttachAllowFlg 为VOS_TRUE */
    NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcCsDetach
 功能描述  : MM处理CS DETACH
 输入参数  : VOS_UINT32 ulOpID
 输出参数  : 无
 返 回 值  : VOS_TRUE:预处理完成,VOS_FALSE:预处理没完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月15日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2011年11月16日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2011111402583,opid值错误，导致AT挂死
  3. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
  4. 日    期   : 2012年5月30日
     作    者   : z00161729
     修改内容   : V7R1C50 GUL背景搜修改
   5.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

  6.日    期   : 2013年6月5日
    作    者   : w00167002
    修改内容   : SVLTE_优化:
    1. 当前有业务过程中，如果是SYSCFG触发的CS域DETACH,则直接返回。

    2.MM模块Detach预处理中NAS_MM_ProcCsDetach，判断网络模式II正在进行注册时，不
      处理Detach，此处需要修改，进行Detach的处理；

    3.MM模块Detach预处理中NAS_MM_ProcCsDetach，如果当前未注册，但正在进行紧急呼过程中，
    目前的处理是直接迁移状态到限制服务，此处需要修改，不需要迁移状态，
    如果迁移到MM_IDLE_LIMITED_SERVICE状态，则会丢弃CM SERVICE ACC消息；
    4. CS处于ATTACHED状态保留标志位,或者在联合注册过程中, 否则直接回复DETACH CNF。
       在联合注册过程中，MM可能不是attached状态，如果直接回复成功，则SVLTE在另一个MODEM
       发起注册，这个时候如果在另一个MODEM上注册成功，这边MODEM又发起联合注册，会
       导致SVLTE切换失败
  7.日    期   : 2014年6月4日
    作    者   : w00167002
    修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.
  8.日    期   : 2015年4月16日
    作    者   : y00245242
    修改内容   : iteration 13开发
*****************************************************************************/

VOS_UINT32 NAS_MM_ProcCsDetach(
    MMCMM_DETACH_REQ_STRU              *pstDetachReq
)
{
    VOS_UINT32                          ulState;

    /* 获取MM的状态 */
    ulState = Mm_GetState();



    g_MmGlobalInfo.stDetachInfo.ulOpid = pstDetachReq->ulOpid;


    NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());

    /* CS域有当前业务存在,syscfg设置引起的detach操作，不缓存，直接回复detach cnf带当前服务状态 */
    if ( VOS_TRUE == NAS_MML_GetCsServiceExistFlg() )
    {
        if ((MMC_MM_DETACH_REASON_RAT_OR_BAND_DETACH == pstDetachReq->enDetachReason)
         || (MMC_MM_DETACH_REASON_SRV_DOMAIN_DETACH  == pstDetachReq->enDetachReason))
        {
            NAS_MM_SndMmcDetachCnf(g_MmGlobalInfo.ucMmServiceState);
            return VOS_TRUE;
        }
    }

    if ( MM_WAIT_CS_ATTACH  == (g_MmGlobalInfo.stAttachInfo.enAttachType & MM_WAIT_CS_ATTACH) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcCsDetach:NORMAL: CS ATTACH is Running.");
        NAS_MM_SndMmcAttachCnf();

        g_MmGlobalInfo.stAttachInfo.enAttachType &= ~MM_WAIT_CS_ATTACH;
    }

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    /* ecall only模式在CS已经attach上的情况下不允许进行CS的detach,因为需要进行回呼 */
    if ((NAS_MML_ECALL_ONLY == NAS_MML_GetCallMode())
     && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState))
    {
        NAS_MM_SndMmcDetachCnf(g_MmGlobalInfo.ucMmServiceState);

        return VOS_TRUE;
    }
#endif
    /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-22, end */

    /* 非网络模式I下,在已注册或者LAU过程中，处理CS域的detach;
       网络模式I下,  在已注册或者联合注册过程中或者LAU过程中，处理CS域的detach  */
    if ( (MM_STATUS_ATTACHED                       == g_MmSubLyrShare.MmShare.ucCsAttachState)
      || (LOCATION_UPDATING_PENDING                == ulState)
      || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == ulState)
      || (LOCATION_UPDATING_INITIATED              == ulState))
    {
        g_MmGlobalInfo.stDetachInfo.enDetachType |= MM_WAIT_CS_DETACH;
    }
    else
    {
        g_MmGlobalInfo.stDetachInfo.enDetachType |= MM_WAIT_CS_DETACH;

        NAS_MM_LocalDetach();


        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcCsPsDetach
 功能描述  : MM处理CS+PS类型的DETACH
 输入参数  : VOS_UINT32 ulOpID
 输出参数  : 无
 返 回 值  : VOS_TRUE:预处理完成,VOS_FALSE:预处理没完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数
 2.日    期   : 2011年11月16日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2011111402583,opid值错误，导致AT挂死

  3.日    期   : 2013年6月5日
    作    者   : w00167002
    修改内容   : svlte:
                  MM模块Detach预处理中NAS_MM_ProcCsPsDetach，如果进行的是CS+PS
                  Detach，CS存在业务时的处理应该修改为与单独进行CS Detach一致，
                  回复Detach结果，清除Detach标志；
                  CS处于ATTACHED状态保留标志位,或者在联合注册过程中, 否则直接回复DETACH CNF

  4.日    期   : 2014年6月4日
    作    者   : w00167002
    修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU.
*****************************************************************************/
VOS_UINT32 NAS_MM_ProcCsPsDetach(
    MMCMM_DETACH_REQ_STRU              *pstDetachReq
)
{
    VOS_UINT32                          ulState;

    /* 获取MM的状态 */
    ulState = Mm_GetState();


    g_MmGlobalInfo.stDetachInfo.ulOpid = pstDetachReq->ulOpid;


    NAS_MM_InitLaiInfo(NAS_MM_GetAttemptUpdateLaiInfo());


    /* 当前存在CS域ATTACH标志，则先直接回复ATTACH CNF结果 */
    if ( MM_WAIT_CS_ATTACH  == (g_MmGlobalInfo.stAttachInfo.enAttachType & MM_WAIT_CS_ATTACH) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_ProcCsPsDetach:NORMAL: CS ATTACH is Running.");

        NAS_MM_SndMmcAttachCnf();

        g_MmGlobalInfo.stAttachInfo.enAttachType &= ~MM_WAIT_CS_ATTACH;
    }

    /* 清楚ATTACH等待标志 */
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    /* CS处于ATTACHED状态保留标志位,或者在联合注册过程中, 否则直接回复DETACH CNF*/
    if ( (MM_STATUS_ATTACHED                       == g_MmSubLyrShare.MmShare.ucCsAttachState)
      || (LOCATION_UPDATING_PENDING                == ulState)
      || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == ulState)
      || (LOCATION_UPDATING_INITIATED              == ulState))
    {
        g_MmGlobalInfo.stDetachInfo.enDetachType    = MM_WAIT_CS_PS_DETACH;

        return VOS_FALSE;
    }
    else
    {
        g_MmGlobalInfo.stDetachInfo.enDetachType |= MM_WAIT_CS_PS_DETACH;

        NAS_MM_LocalDetach();
        return VOS_TRUE;
    }
}


/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmcDetachReq_PreProc
 功能描述  : 收到MMCMM_DETACH_REQ消息后，判定是否在该预处理函数中处理掉
              MMCMM_DETACH_REQ消息，不进各状态处理
 输入参数  : pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : 事件ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月28日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2013年6月8日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:启动CS域保护定时器.
*****************************************************************************/
VOS_UINT8  NAS_MM_RcvMmcDetachReq_PreProc(
    VOS_VOID                           *pstRcvMsg
)
{
    MMCMM_DETACH_REQ_STRU              *pstDetachReq;

    pstDetachReq = (MMCMM_DETACH_REQ_STRU*)pstRcvMsg;

    switch (pstDetachReq->enDetachType)
    {
        case MMC_MM_PS_DETACH:
            return MM_EVENT_ID_INVALID;
        case MMC_MM_CS_DETACH:
            if (VOS_TRUE == NAS_MM_ProcCsDetach(pstDetachReq))
            {
                return MM_EVENT_ID_INVALID;
            }
            break;
        case MMC_MM_PS_CS_DETACH:
            if (VOS_TRUE == NAS_MM_ProcCsPsDetach(pstDetachReq))
            {
                return MM_EVENT_ID_INVALID;
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, LOG_LEVEL_WARNING,"DETACH TYPE INVALID");
            return MM_EVENT_ID_INVALID;
    }

    /* 启动CS域保护定时器  */
    NAS_MM_StartDetachProtectingTimer(pstDetachReq);

    return MM_EVENT_ID_DETACH_REQ;
}




/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmcLauReq
 功能描述  : 收到MMCMM_LAU_REQ消息后，尝试发起LAU
 输入参数  : pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月21日
   作    者   : w00167002
   修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。

*****************************************************************************/
VOS_VOID NAS_MM_RcvMmcLauReq(
    VOS_VOID                           *pstRcvMsg
)
{
    MMCMM_LAU_REQ_STRU                 *pstLauReq       = VOS_NULL_PTR;
    VOS_UINT8                           ucPsRestrictionFlg;

    pstLauReq               = (MMCMM_LAU_REQ_STRU*)pstRcvMsg;
    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    /* NMO1下,MM不需要进行注册 */
    if ((VOS_TRUE       == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I  == g_MmGlobalInfo.ucNewNtMod)
     && (MM_FALSE       == g_MmGlobalInfo.ucLikeB)
     && (VOS_FALSE      == ucPsRestrictionFlg))
    {
        return;
    }

    /* 检测是否被在当前网络上被拒#17(MMC已判断),且失败达到最大次数 */
    if ( g_MmGlobalInfo.LuInfo.ucLuAttmptCnt < MM_CONST_NUM_4 )
    {
        return;
    }

    if ( (MM_IDLE_ATTEMPTING_TO_UPDATE == Mm_GetState())
      && (MMC_MM_LAU_REQ_REASON_SOR == pstLauReq->enLauReqReason) )
    {
        /* 直接进行lau */
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
        Mm_ComLuOnly();
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmcRatChangeInd
 功能描述  : 接收到mmc CSFB过程中RAT change的处理
 输入参数  : pstMsg:CSFB过程中RAT change消息
 输出参数  : 无
 返 回 值  : 该消息对应的MM事件
 调用函数  :
 被调函数  :

1.日    期   : 2013年3月27日
  作    者   : y00176023
  修改内容   : DSDS GUNAS II项目新增函数
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvMmcRatChangeInd(
    VOS_VOID                           *pstRcvMsg
)
{
    MMCMM_RAT_CHANGE_IND_STRU          *pstRatChangeInd = VOS_NULL_PTR;

    pstRatChangeInd = (MMCMM_RAT_CHANGE_IND_STRU *)pstRcvMsg;

    /*刷新目标RAT*/
    g_MmGlobalInfo.stSuspendShare.enDestSuspendRat = pstRatChangeInd->enNetRatType;

    return MM_EVENT_ID_INVALID;

}


/* Added by n00355355 for 呼叫重建, 2015-9-17, end */
/*****************************************************************************
 函 数 名  : NAS_MM_RcvRrMmGetTransactionReq
 功能描述  : 收到接入查询当前业务状态标志的函数处理
 输入参数  : ulEventType:消息类型
              pstMsg:RRMM_TRANSACTION_INFO_ENQ消息
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成，不需要进状态机进行处理
              VOS_FALSE:消息处理未完成
 调用函数  :
 被调函数  :

 修改历史      :

  1.日    期   : 2015年9月17日
    作    者   : n00355355
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_RcvRrMmGetTransactionReq(
    RRMM_TRANSACTION_INFO_ENQ_STRU      *pMsgHeader
)
{
    /* MM给CC发送MMCC_GET_CALL_INFO_REQ */
    NAS_MM_SetTransactionEnqSenderPid(pMsgHeader->MsgHeader.ulSenderPid);

    NAS_Mm_SndCcGetCallInfoReq();

    return;
}
/* Added by n00355355 for 呼叫重建, 2015-9-17, end */



/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmcSrvccInfoNtf
 功能描述  : 处理MMC的SRVCC通知消息
 输入参数  : pstMsg MMC上报的srvcc通知消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : w00176964
    修改内容   : 新建
 2.日    期   : 2014年05月30日
   作    者   : s00217060
   修改内容   : ultra flash csfb时不需要通知cc模块srvcc开始
*****************************************************************************/
VOS_VOID NAS_MM_RcvMmcSrvccInfoNtf(
    VOS_VOID                           *pstRcvMsg
)
{
    /* 记录SRVCC标记到MM全局变量中 */
    NAS_MM_SetSrvccFlg(VOS_TRUE);

    if (VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* 通知CC模块SRVCC过程开始 */
        NAS_MM_SndCcSrvccStatusInd(NAS_MMCC_SRVCC_STATUS_START);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_RcvCcSrvccCallInfoNtf
 功能描述  : 处理CC模块通知MM的SRVCC的呼叫信息
 输入参数  : pstMsg CC上报的srvcc的呼叫消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : w00176964
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_RcvCcSrvccCallInfoNtf(
    MMCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstCcMsg
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucTI;

#if 0
    /* 如果MM不在INTER_RAT_CHANGE状态下收到,认为时序存在问题,丢弃该消息 */
    if (MM_INTER_RAT_CHANGE != g_MmGlobalInfo.ucState)
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"NAS_MM_RcvCcSrvccCallInfoNtf Unexpected msg!");

        return;
    }
#endif

    /* 边界检查，避免数组越界 */
    if (pstCcMsg->ucTiNum > NAS_MM_MAX_CC_CONNECTION_NUM)
    {
        pstCcMsg->ucTiNum = NAS_MM_MAX_CC_CONNECTION_NUM;
    }

    NAS_MM_SetRcvSrvccCallInfoFlg(VOS_TRUE);

    /* 按照协议规定，SRVCC成功到GU后,都当做MT CALL */
    for (i = 0; i < pstCcMsg->ucTiNum ; i++)
    {
        ucTI = pstCcMsg->aucTransactionId[i];

        /*lint -e701*/
        if (MM_CONST_NUM_7 > ucTI)
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] |=
                        (VOS_UINT8 )( 0x01 << ucTI );
        }
        else if ((MM_CONST_NUM_7 < ucTI)
              && (MM_CONST_NUM_15 > ucTI))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                        (VOS_UINT8 )( 0x01 << (ucTI - 8) );
        }
        else
        {
        }

        /*lint +e701*/
    }

    return;
}
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, end */

/*****************************************************************************
 函 数 名  : NAS_MM_RcvSysInfoAccessBar_ProcBufferedCsService
 功能描述  : 收到系统消息access bar场景处理缓存的cs业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月12日
    作    者   : z00161729
    修改内容   : DTS2014041806795:GCF 13.1.15 UE在lte下联合注册，收到网络cs的paging，重定向到tds的注册被bar的小区后ue没有发送paging response
*****************************************************************************/
VOS_VOID NAS_MM_RcvSysInfoAccessBar_ProcBufferedCsService(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucCsRestrictPagingFlg;
    VOS_UINT8                                               ucRestrictNormalService;
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enServiceStatus;
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;

    ucCsRestrictPagingFlg = VOS_FALSE;
#endif

    /* access bar时打紧急呼叫直接发起 */
    /* 判断紧急呼叫，不能光用RcvXXEstReq.ulCallType判断，前提条件是CC业务*/
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == Mm_ComJudgeCsServExist())
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState; /* 记录收到建立请求时的状态                 */

        NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    ucCsRestrictPagingFlg = NAS_MML_GetCsRestrictPagingFlg();
    enServiceStatus       = NAS_MM_GetLauUptNeededCsSrvStatus();
    enCsfbServiceStatus   = NAS_MML_GetCsfbServiceStatus();

    if ((NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == enCsfbServiceStatus)
     && (VOS_FALSE == ucCsRestrictPagingFlg)
     && ((MM_COM_SRVST_NORMAL_SERVICE == enServiceStatus)
      || (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)))
    {
        g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

        Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

        /* 在GU下，回复paging response */
        NAS_MM_ResponseLmmPagingInd_CSFB();

        /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
        NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
        return;
    }

    ucRestrictNormalService = NAS_MML_GetCsRestrictNormalServiceFlg();

    if ((MM_COM_SRVST_NORMAL_SERVICE == enServiceStatus)
     && (VOS_FALSE == ucRestrictNormalService))
    {
        if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST == enCsfbServiceStatus)
        {
            /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

            g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

            Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
        }
        else if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == enCsfbServiceStatus)
        {
            /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

            g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* 记录收到建立请求时的状态                 */

            Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

            NAS_MM_PerformBufferedSsService();
        }
        else
        {
        }
    }
#endif

    return;
}


#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_MM_ConvertMmccSessionTypeToRrcFormat
 功能描述  : 将MMCC的接口转换成接入层的接口
 输入参数  : enMmccSessionType:MMCC接口

 输出参数  : penRrcSessionType:GUAS接口的Session类型

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_ConvertMmccSessionTypeToRrcFormat(
    MMCC_SESSION_TYPE_ENUM_UINT8        enMmccSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *penRrcSessionType
)
{
    switch(enMmccSessionType)
    {
        case MMCC_SESSION_TYPE_MO_NORMAL_CALL:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_NORMAL_CALL;
            break;

        case MMCC_SESSION_TYPE_MO_EMERGENCY_CALL:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case MMCC_SESSION_TYPE_MT_NORMAL_CALL:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MT_NORMAL_CALL;
            break;

        default:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertMmssSessionTypeToRrcFormat
 功能描述  : 将MMSS的接口转换成接入层的接口
 输入参数  : enMmssSessionType:MMSS接口

 输出参数  : penRrcSessionType:GUAS接口的Session类型

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_ConvertMmssSessionTypeToRrcFormat(
    MMSS_SESSION_TYPE_ENUM_UINT8        enMmssSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *penRrcSessionType
)
{
    switch(enMmssSessionType)
    {
        case MMSS_SESSION_TYPE_MO_SS:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_SS;
            break;

        case MMSS_SESSION_TYPE_MT_SS:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MT_SS;
            break;

        default:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ConvertMmsmsSessionTypeToRrcFormat
 功能描述  : 将MMSMS的接口转换成接入层的接口
 输入参数  : enMmsmsSessionType:MMSMS接口

 输出参数  : penRrcSessionType:GUAS接口的Session类型

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_ConvertMmsmsSessionTypeToRrcFormat(
    MMSMS_SESSION_TYPE_ENUM_UINT8       enMmsmsSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *penRrcSessionType
)
{
    switch (enMmsmsSessionType)
    {
        case MMSMS_SESSION_TYPE_MO_SMS:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MO_SMS;
            break;

        case MMSMS_SESSION_TYPE_MT_SMS:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_CS_MT_SMS;
            break;

        default:
            *penRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmccBeginSessionNotify
 功能描述  : 处理CC的begin session notify消息
 输入参数  : pstMsg CC下发的begin session notify消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_RcvMmccBeginSessionNotify(
    MMCC_BEGIN_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMCC_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmccSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndBeginSessionNotify(enRrcSessionType);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmccEndSessionNotify
 功能描述  : 处理CC的end session notify消息
 输入参数  : pstMsg CC下发的end session notify消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_RcvMmccEndSessionNotify(
    MMCC_END_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMCC_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmccSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndEndSessionNotify(enRrcSessionType);
    }

    return;
}



/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmssBeginSessionNotify
 功能描述  : 处理SS的begin session notify消息
 输入参数  : pstMsg SS下发的begin session notify消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_RcvMmssBeginSessionNotify(
    MMSS_BEGIN_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMSS_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmssSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndBeginSessionNotify(enRrcSessionType);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmssEndSessionNotify
 功能描述  : 处理SS的end session notify消息
 输入参数  : pstMsg SS下发的end session notify消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_RcvMmssEndSessionNotify(
    MMSS_END_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMSS_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmssSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndEndSessionNotify(enRrcSessionType);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmsmsBeginSessionNotify
 功能描述  : 处理sms的begin session notify消息
 输入参数  : pstMsg SMS下发的begin session notify消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_RcvMmsmsBeginSessionNotify(
    MMSMS_BEGIN_SESSION_NOTIFY_STRU    *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMSMS_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmsmsSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndBeginSessionNotify(enRrcSessionType);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmsmsEndSessionNotify
 功能描述  : 处理SMS的end session notify消息
 输入参数  : pstMsg SMS下发的end session notify消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : w00242748
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MM_RcvMmsmsEndSessionNotify(
    MMSMS_END_SESSION_NOTIFY_STRU     *pstRcvMsg
)
{
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;

    if ( MMSMS_SESSION_TYPE_BUTT != pstRcvMsg->enSessionType )
    {
        NAS_MM_ConvertMmsmsSessionTypeToRrcFormat(pstRcvMsg->enSessionType, &enRrcSessionType);

        NAS_MM_SndEndSessionNotify(enRrcSessionType);
    }

    return;
}






#endif

/*****************************************************************************
 函 数 名  : NAS_MM_CheckCallStatusNtyValid
 功能描述  : 检查CALL STATUS NTY消息的正确性
 输入参数  : MMCC_CALL_STATUS_NTF_STRU          *pstCallStatusNty
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MM_CheckCallStatusNtyValid(
    MMCC_CALL_STATUS_NTF_STRU          *pstCallStatusNty
)
{
    /* CALL模块目前只会通知succ或fail，其他取值不需要处理 */
    if ((MNCC_CALL_STATUS_SETUP_SUCC != pstCallStatusNty->enCallStatus)
     && (MNCC_CALL_STATUS_SETUP_FAIL != pstCallStatusNty->enCallStatus))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_CheckSsStatusNtyValid
 功能描述  : 检查SS STATUS NTY消息的正确性
 输入参数  : MMSS_STATUS_NTF_STRU          *pstSsStatusNty
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月25日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MM_CheckSsStatusNtyValid(
    MMSS_STATUS_NTY_STRU               *pstSsStatusNty
)
{
    /* SS模块目前只会通知succ或fail，其他取值不需要处理 */
    if ((SSA_SS_STATUS_SETUP_SUCC   != pstSsStatusNty->enSsStatus)
     && (SSA_SS_STATUS_SETUP_FAIL   != pstSsStatusNty->enSsStatus))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmccCallStatusNty
 功能描述  : 收到MMCC_CALL_STATUS_NTY的处理
 输入参数  : MMCC_CALL_STATUS_NTF_STRU          *pstCallStatusNty
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2016年1月9日
    作    者   : z00359541
    修改内容   :DTS2015111402223:增加小区是否支持CSMO标识
*****************************************************************************/
VOS_VOID NAS_MM_RcvMmccCallStatusNty(
    MMCC_CALL_STATUS_NTF_STRU          *pstCallStatusNty
)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enCallStatus;
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTransStatus;

    enCallStatus    = NAS_MML_GetMoCallStatus();
    enTransStatus   = RRMM_TRANSACTION_FAIL;

    /* CALL模块目前只会通知succ或fail，其他取值不需要处理 */
    if (VOS_FALSE == NAS_MM_CheckCallStatusNtyValid(pstCallStatusNty))
    {
        return;
    }

    /* 呼叫建立标志为start时通知接入层链接释放之后FR，如果为fail或succ，前面已经通知过了，不需要再通知 */
    if (VOS_TRUE == NAS_MML_GetMoCallSetupFlg())
    {
        NAS_MM_ConvertCallStatusToTransactionStatus(pstCallStatusNty->enCallStatus, &enTransStatus);
        NAS_MM_SndTransactionStatusNotify(enTransStatus);
    }

    /* 如果MMC正在搜网时挂断电话，通知MMC停止搜GU，重新从LTE开始搜网;如果MMC处于ON PLMN启高优先级接入技术BG搜定时器 */
    if ( ((NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START  == enCallStatus)
       || (NAS_MML_CSFB_MO_EMC_CALL_SETUP_START     == enCallStatus))
      && (MNCC_CALL_STATUS_SETUP_FAIL               == pstCallStatusNty->enCallStatus) )
    {
        NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_CSFB_END);
    }

    /* 更新呼叫建立标志 */
    NAS_MM_UpdateCallStatus_RcvCallStatusNty(pstCallStatusNty->enCallStatus);

    NAS_NORMAL_LOG(WUEPS_PID_MM, "NAS_MM_RcvMmccCallStatusNty: Reset CellNotSupportCsmoFlg to FALSE");
    NAS_MML_SetCellNotSupportCsmoFlg(VOS_FALSE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmccGetCallInfoCnf
 功能描述  : MM收到MMCC_GET_CALL_INFO_CNF的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月17日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_RcvMmccGetCallInfoCnf(
    MMCC_GET_CALL_INFO_CNF_STRU        *pstMsg
)
{
    VOS_UINT32                          ucIndex;
    VOS_UINT8                           ucIsCallActive;
    RRC_NAS_CS_TRANSACTION_ENUM_UINT8   enCsTransactionStatus;
    VOS_UINT32                          ulRcvPid;

    ucIsCallActive  = VOS_FALSE;

    for (ucIndex = 0; ucIndex < NAS_CC_MAX_ENTITY_NUM; ucIndex++)
    {
        if (NAS_CC_CALL_STATE_U10 == pstMsg->astCallInfo[ucIndex].enCallState)
        {
            ucIsCallActive = VOS_TRUE;
            break;
        }
    }

    NAS_MML_GetMmlCsTransactionStatus(&enCsTransactionStatus);

    ulRcvPid = NAS_MM_GetTransactionEnqSenderPid();

    NAS_MM_SndAsCsTransactionStatus(enCsTransactionStatus, ulRcvPid, ucIsCallActive);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_RcvMmssStatusNty
 功能描述  : 收到MMSS_STATUS_NTY的处理
 输入参数  : MMSS_STATUS_NTY_STRU          *pstSsStatusNty
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_RcvMmssStatusNty(
    MMSS_STATUS_NTY_STRU               *pstSsStatusNty
)
{
    RRMM_TRANSACTION_STATUS_ENUM_UINT8  enTransStatus;
    NAS_MML_MO_SS_STATUS_ENUM_UINT8     enOldSsMoStatus;

    enOldSsMoStatus = NAS_MML_GetMoSsStatus();
    enTransStatus   = RRMM_TRANSACTION_FAIL;

    /* SS模块目前只会通知succ或fail，其他取值不需要处理 */
    if (VOS_FALSE == NAS_MM_CheckSsStatusNtyValid(pstSsStatusNty))
    {
        return;
    }

    /* 有业务建立标志时，通知AS，链接释放时可以FR */
    if (VOS_TRUE == NAS_MML_GetMoSsSetupFlg())
    {
        NAS_MM_ConvertSsStatusToTransactionStatus(pstSsStatusNty->enSsStatus, &enTransStatus);
        NAS_MM_SndTransactionStatusNotify(enTransStatus);
    }

    /* 如果MMC正在搜网时业务结束，通知MMC停止搜GU，重新从LTE开始搜网;如果MMC处于ON PLMN启高优先级接入技术BG搜定时器 */
    if ((NAS_MML_CSFB_MO_SS_SETUP_START == enOldSsMoStatus)
     && (SSA_SS_STATUS_SETUP_FAIL       == pstSsStatusNty->enSsStatus))
    {
        NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_CSFB_END);
    }

    /* 更新标志 */
    NAS_MM_UpdateSsStatus_RcvSsStatusNty(pstSsStatusNty->enSsStatus);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ParseT3246IE
 功能描述  : 解析CM SERVICE REJ消息中的T3246
 输入参数  : VOS_UINT8                          *pucRcvMsg
             VOS_UINT16                          usMsgSize
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月19日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ParseT3246IE(
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize,
    VOS_UINT8                          *pucIsT3246Exist
)
{
    VOS_UINT8                           ucIndex;

    /* 协议章节:
        3GPP 24008 9.2.6 CM service reject

        IEI     Information element             Type/Reference         Presence    Format     Length
                Mobility management         Protocol discriminator        M          V         1/2
                protocol discriminator      10.2

                Skip Indicator              Skip Indicator                M          V         1/2
                                            10.3.1

                CM Service Reject           Message type                  M          V          1
                message type                10.4

                Reject cause                Reject cause                  M          V          1
                                            10.5.3.6

        36      T3246 value                 MM timer                      O         TLV         3
                                            10.5.3.16


        3GPP 24008 10.5.3.16 MM Timer

        MM Timer IEI:               octet 1
        Length of MM Timer contents:octet 2
        MM Timer value:             octet 3

        Timer value (octet 3)

        Bits 5 to 1 represent the binary coded timer value.

        Bits 6 to 8 defines the timer value unit for the MM timer as follows:
        Bits
        8 7 6
        0 0 0  value is incremented in multiples of 2 seconds
        0 0 1  value is incremented in multiples of 1 minute
        0 1 0  value is incremented in multiples of decihours
        1 1 1  value indicates that the timer is deactivated.

        Other values shall be interpreted as multiples of 1 minute in this version of the protocol.

        The value indicated is contructed by multiplying the value in bits 5 to 1 with the timer value unit in bits 8 to 6,
        unless the timer value unit indicates the timer being deactivated.
    */

    /* 长度小于等于3，表示没有携带T3246 IE项 */
    if ( usMsgSize <= MM_CM_SRV_REJ_MIN_LEN )
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }

    /* 长度小于6，T3246 IE项异常 */
    if ( usMsgSize < MM_CM_SRV_REJ_MAX_LEN )
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }

    ucIndex = MM_CM_SRV_REJ_MIN_LEN;

    /* MM Timer IEI不对 */
    if (MM_IE_MM_TIMER != pucRcvMsg[ucIndex])
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }


    ucIndex++;

    /* Length of MM Timer contents为0 */
    if (0 == pucRcvMsg[ucIndex])
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }

    ucIndex++;

    /* bits 8 to 6:111 value indicates that the timer is deactivated  */
    if (0xE0 == (pucRcvMsg[ucIndex] & 0xE0))
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;
    }

    /* bits 5 to 1: 00000 timer value=0 */
    if (0 == (pucRcvMsg[ucIndex] & 0x1F) )
    {
        *pucIsT3246Exist    = VOS_FALSE;

        return;

    }

    *pucIsT3246Exist    = VOS_TRUE;

    return;

}



/*****************************************************************************
 函 数 名  : NAS_MM_RcvCspagingInd_PreProc
 功能描述  : 收到RRMM_PAGING_IND消息后的预处理
 输入参数  : pstRcvMsg:消息的首地址
 输出参数  : 无
 返 回 值  : 事件ID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月16日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   :2015年3月13日
    作    者   :zwx247453
    修改内容   :CHR 优化项目
*****************************************************************************/
VOS_UINT8 NAS_MM_RcvCspagingInd_PreProc(
    VOS_VOID                           *pstRcvMsg
)
{
#if (FEATURE_ON == FEATURE_PTM)
    NAS_MM_ParseErrLogCsPagingInfo(pstRcvMsg);
#endif

    switch (g_MmGlobalInfo.ucState)
    {
        case MM_IDLE_PLMN_SEARCH:
        case MM_IDLE_NORMAL_SERVICE:
        case MM_IDLE_LIMITED_SERVICE:
        case MM_IDLE_ATTEMPTING_TO_UPDATE:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case LOCATION_UPDATING_PENDING:

            return MM_EVENT_ID_PAGING_IND;

        default:
#if (FEATURE_ON == FEATURE_PTM)
            /* 判断为非IDLE状态，记录异常 */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_STATE_ERR);
#endif
            return MM_EVENT_ID_PAGING_IND;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetLauRequestInfo
 功能描述  : 提供给接入层获取LAU相关信息
 输入参数  : pstLauReqMsg: LAU消息内容，是 LAU 消息内容中，是NAS_EST_REQ中的NAS_MSG_STRU结构
 输出参数  : penLauType:LAU类型
             pucFollowOnFlg:是否有 follow on标志
             penAdditionUpdatePara: Additionupdate参数类型
 返 回 值  : VOS_OK:获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月12日
    作    者   : j00174725
    修改内容   : 新生成函数DTS2015040705043
*****************************************************************************/
VOS_UINT32 NAS_MM_GetLauRequestInfo(
    NAS_MSG_STRU                           *pstLauReqMsg,
    NAS_LAU_TYPE_ENUM_UINT8                *penLauType,
    VOS_UINT8                              *pucFollowOnFlg,
    NAS_ADDITION_UPDATE_PARA_ENUM_UINT8    *penAdditionUpdatePara
)
{
    VOS_UINT8                          *pucMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulMsgSize;
    VOS_UINT32                          ulPointer;

    /* 参数检查 */
    if ( (VOS_NULL_PTR == pstLauReqMsg)
      || (VOS_NULL_PTR == penLauType)
      || (VOS_NULL_PTR == pucFollowOnFlg)
      || (VOS_NULL_PTR == penAdditionUpdatePara) )
    {
        return VOS_ERR;
    }

    /* 初始化 */
    ulPointer   = (VOS_UINT32)pstLauReqMsg->aucNasMsg;
    pucMsg      = (VOS_UINT8 *)ulPointer;
    ulIndex     = 0;
    ulMsgSize   = pstLauReqMsg->ulNasMsgSize;

    /* LAU的消息长度最小为11  */
    if (ulMsgSize < 11)
    {
        return VOS_ERR;
    }

    /* 跳过 Mobility 和 Skip Indicator */
    ulIndex     = ulIndex + 1;

    /* 判断是否是LAU消息 */
    if(MM_IE_MSG_TYPE_LU_REQUEST != (pucMsg[ulIndex] & 0x3F))
    {
        return VOS_ERR;
    }
    /* 增加msg type  长度 */
    ulIndex     = ulIndex + 1;

    /* 解析LAU type 和 Follow */
    *penLauType  = pucMsg[ulIndex] & 0x03;

    /* 解析Follow */
    if ((pucMsg[ulIndex] & 0x8) > 0)
    {
        *pucFollowOnFlg = VOS_TRUE;
    }
    else
    {
        *pucFollowOnFlg = VOS_FALSE;
    }

    /* 直接跳到Mobile identity */
    ulIndex     = ulIndex + 7;

    /* 解析Mobile identity 长度 */
    if (( 0 == pucMsg[ulIndex] ) || ( 8 <  pucMsg[ulIndex] ))
    {
        return VOS_ERR;
    }
    else
    {
        ulIndex = ulIndex + pucMsg[ulIndex];
    }

    /* 去掉Mobilt identity length */
    ulIndex = ulIndex + 1;

    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_NONE;

    while (ulIndex < ulMsgSize)
    {
        if (0x33 == pucMsg[ulIndex])
        {
            ulIndex = ulIndex + 5;
        }
        else if (0xC0 == (pucMsg[ulIndex] & 0xF0 ))
        {
            switch (pucMsg[ulIndex] & 0x3)
            {
                case 1:
                    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_MT;
                    break;

                case 2:
                    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_MO;
                    break;

                case 3:
                    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_MO_MT;
                    break;

                default:
                    *penAdditionUpdatePara = NAS_ADDITION_UPDATE_PARA_NONE;
                    break;
            }
            break;
        }
        else if (0xD0 == (pucMsg[ulIndex] & 0xF0 ))
        {
            ulIndex = ulIndex + 1;
        }
        else if (0xE0 == (pucMsg[ulIndex] & 0xF0 ))
        {
            ulIndex = ulIndex + 1;
        }
        else
        {
            ulIndex = ulIndex + 1;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetL3ReqMsgPd
 功能描述  : 提供给接入层获取Req消息中的PD信息
 输入参数  : pstSendMsg: Data Req消息内容 RRMM_DATA_REQ_STRU结构
 输出参数  : ucPd: Data Req消息中所带的PD值

 返 回 值  : VOS_OK: 获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_GetL3ReqMsgPd(
    RRMM_DATA_REQ_STRU                     *pstSendMsg,
    VOS_UINT8                              *pucPd
)
{
    if ((VOS_NULL_PTR == pstSendMsg)
     || (VOS_NULL_PTR == pucPd))
    {
        return VOS_ERR;
    }

    if (RRMM_DATA_REQ   != pstSendMsg->MsgHeader.ulMsgName)
    {
        return VOS_ERR;
    }

    /* SenderPid检查 */
    if ((WUEPS_PID_MM   != pstSendMsg->MsgHeader.ulSenderPid)
     && (WUEPS_PID_GMM  != pstSendMsg->MsgHeader.ulSenderPid))
    {
        return VOS_ERR;
    }

    /* ReceiverPid检查 */
    if ((WUEPS_PID_WRR  != pstSendMsg->MsgHeader.ulReceiverPid)
     && (UEPS_PID_GAS   != pstSendMsg->MsgHeader.ulReceiverPid))
    {
        return VOS_ERR;
    }

    *pucPd = (pstSendMsg->SendNasMsg.aucNasMsg[0] & 0x0F);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetL3RcvMsgPd
 功能描述  : 提供给接入层获取Ind消息中的PD信息
 输入参数  : pstSendMsg: Data Ind消息内容 RRMM_DATA_IND_STRU结构
 输出参数  : ucPd: Data Ind消息中所带的PD值

 返 回 值  : VOS_OK: 获取成功
             VOS_ERR:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_GetL3RcvMsgPd(
    RRMM_DATA_IND_STRU                     *pstRcvMsg,
    VOS_UINT8                              *pucPd
)
{
    if ((VOS_NULL_PTR == pstRcvMsg)
     || (VOS_NULL_PTR == pucPd))
    {
        return VOS_ERR;
    }

    if (RRMM_DATA_IND   != pstRcvMsg->MsgHeader.ulMsgName)
    {
        return VOS_ERR;
    }

    /* SenderPid检查 */
    if ((WUEPS_PID_WRR  != pstRcvMsg->MsgHeader.ulSenderPid)
     && (UEPS_PID_GAS   != pstRcvMsg->MsgHeader.ulSenderPid))
    {
        return VOS_ERR;
    }

    /* ReceiverPid检查 */
    if ((WUEPS_PID_MM   != pstRcvMsg->MsgHeader.ulReceiverPid)
     && (WUEPS_PID_GMM  != pstRcvMsg->MsgHeader.ulReceiverPid))
    {
        return VOS_ERR;
    }

    *pucPd = (pstRcvMsg->RcvNasMsg.aucNasMsg[0] & 0x0F);

    return VOS_OK;
}


/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

