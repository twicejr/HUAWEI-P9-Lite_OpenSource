/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SmSend.c
  Description  :
  Function List:
              1.  SM_ComGetTI
              2.  SM_SndPdpActReqMsg
              3.  SM_SndReqPdpActRejMsg
              4.  SM_SndPdpDeActReqMsg
              5.  SM_SndPdpModAccMsg
              6.  SM_SndPdpModReqMsg
              7.  SM_SndPdpActSecReqMsg
              8.  SM_SndPdpDeActAccMsg
              9.  NAS_SM_SndGmmPdpStatusInd
             10.  NAS_SM_SndGmmEstablishReq
             11.  SM_SndTafSmPdpMsg
             12.  SM_SndTafSmPdpActivateRej
             13.  SM_SndTafSmPdpActivateInd
             14.  SM_SndTafSmPdpActivateCnf
             15.  SM_SndTafSmPdpDeActCnf
             16.  SM_SndTafSmPdpDeActInd
             17.  SM_SndTafSmPdpModifyInd
             18.  SM_SndTafSmPdpModifyCnf
             19.  SM_SndTafSmPdpModifyRej
             20.  SM_SndTafSmPdpActSecCnf
             21.  SM_SndTafSmPdpActSecRej
             22.  SM_SndRabmSmActivateInd
             23.  SM_SndRabmSmModifyInd
             24.  SM_SndRabmSmDeactivateInd
             25.  SM_SndNwStatusMsg
             26.  SM_MemFree
             27.  SM_GetMostHighPri
             28.  SM_SndTafMsg
             29.  SM_SndStatusMsg
  History:
      1.   张志勇      2003.12.09   新规作成
*******************************************************************************/
#include "SmInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SM_SEND_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*******************************************************************************
  Module:      SM_ReportM2NOtaMsg
  Function:    在trace中勾取SM的空口消息
  Input:       NAS_MSG_STRU*   pNasMsg   SM空口消息
  NOTE:
  Return:      VOS_VOID
  History:
      1. 鲁琳    2009.07.11   新规作成
*******************************************************************************/
VOS_VOID SM_ReportM2NOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;
    VOS_UINT8            ucMsgType;

    /*TI长度不同，msg type在aucNasMsg的index也不一样*/
    if((pNasMsg->aucNasMsg[0]&0x70)==0x70 )
    {
        ucMsgType = pNasMsg->aucNasMsg[2];
    }
    else
    {
        ucMsgType = pNasMsg->aucNasMsg[1];
    }

    PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_ReportM2NOtaMsg:NORMAL: msg type is", ucMsgType);

    switch(ucMsgType)
    {
        case SM_ACT_PDP_CONTEXT_REQ:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_PDP_CONTEXT_REQ;
            break;

        case SM_REQ_PDP_CONTEXT_REJ:
            usNasOtaMsyId = NAS_OTA_MSG_REQ_PDP_CONTEXT_REJ;
            break;

        case SM_DEACT_PDP_CONTEXT_REQ:
            usNasOtaMsyId = NAS_OTA_MSG_DEACT_PDP_CONTEXT_REQ;
            break;

        case SM_DEACT_PDP_CONTEXT_ACC:
            usNasOtaMsyId = NAS_OTA_MSG_DEACT_PDP_CONTEXT_MS_ACC;
            break;

        case SM_MOD_PDP_CONTEXT_ACC_M2N:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_ACC_M2N;
            break;

        case SM_MOD_PDP_CONTEXT_REQ_M2N:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_REQ_M2N;
            break;

        case SM_ACT_SEC_PDP_CONTEXT_REQ:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_SEC_PDP_CONTEXT_REQ;
            break;

        case SM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_SM_MS_STATUS;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ReportM2NOtaMsg:WARNING: Invalid Msg id");
            /*不属于SM的空口消息，在trace中不显示*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_SM, usNasOtaMsyId, NAS_OTA_DIRECTION_UP, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
}

/*******************************************************************************
  Module:      SM_ComGetTI
  Function:    取得Transaction identifier
  Input:       VOS_UINT8                  ucSMIndex        SM索引
               VOS_UINT8                  *pTemp           存储TI的指针
               VOS_UINT32                  *ulSum           计数器
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
VOS_VOID SM_ComGetTI(
                       VOS_UINT8                  ucSMIndex,                        /* SM索引                                   */
                       VOS_UINT8                  **pTemp,                          /* 存储TI的指针                             */
                       VOS_UINT32                  *ulSum                            /* 计数器                                   */
                )
{
    VOS_UINT8           ucTi;                                                       /* 定义临时变量                             */

    if(SM_TI_NET_ORG != g_SmEntity.aPdpCntxtList[ucSMIndex].ucTiFlg)
    {                                                                           /* 不是网侧形成的情况                       */
        if(0x80 == (g_SmEntity.aPdpCntxtList[ucSMIndex].ucTi & 0x80))
        {
            ucTi = g_SmEntity.aPdpCntxtList[ucSMIndex].ucTi & 0x7f;             /* 取得Transaction identifier               */
        }
        else
        {
            ucTi = g_SmEntity.aPdpCntxtList[ucSMIndex].ucTi & 0x07;             /* 取得Transaction identifier               */
        }
    }
    else
    {
        ucTi = g_SmEntity.aPdpCntxtList[ucSMIndex].ucTi;                        /* 取得Transaction identifier               */
    }
    if( ucTi < 0x07 )
    {                                                                           /* TI占用1/2字节，TI无扩展                  */
        if( g_SmEntity.aPdpCntxtList[ucSMIndex].ucTiFlg
            == SM_TI_NET_ORG )
        {                                                                       /* 网侧形成                                 */
            **pTemp = ((ucTi << 4) & 0x70) | 0x80;                              /* 获得TI,Ti Flag置1                        */
            **pTemp = (**pTemp) | NAS_PD_SM;                                    /* 设定PD                                   */
        }
        else
        {                                                                       /* MS形成                                   */
            **pTemp = (ucTi << 4) & 0x70;                                       /* 获得TI,Ti Flag置0                        */
            **pTemp = (**pTemp) | NAS_PD_SM;                                    /* 设定PD                                   */
        }
        (*pTemp)++;                                                             /* 更新指针偏移的长度                       */
        *ulSum += 1;                                                            /* 计数器加1                                */
    }
    else
    {                                                                           /* TI占用3/2字节，TI有扩展                  */
        if( SM_TI_NET_ORG == g_SmEntity.aPdpCntxtList[ucSMIndex].ucTiFlg )
        {                                                                       /* 网侧形成                                 */
            **pTemp = 0xF0;                                                     /* Ti Flag置1                               */
            **pTemp = (**pTemp) | NAS_PD_SM;                                    /* 设定PD                                   */
            (*pTemp)++;                                                         /* 更新指针偏移的长度                       */
            **pTemp = ucTi | 0x80;                                              /* 获得TI                                   */
        }
        else
        {                                                                       /* MS形成                                   */
            **pTemp = 0x70;                                                     /* Ti Flag置0                               */
            **pTemp = (**pTemp) | NAS_PD_SM;                                    /* 设定PD                                   */
            (*pTemp)++;                                                         /* 更新指针偏移的长度                       */
            **pTemp = ucTi | 0x80;                                              /* 获得TI                                   */
        }
        (*pTemp)++;                                                             /* 更新指针偏移的长度                       */
        *ulSum += 2;                                                            /* 计数器加2                                */
    }
    return;
}

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpActReqMsg
  Function:    将TAF发给SM的TAFSM_PDP_ACTIVATE_REQ消息转换成数据流发送
  Input:       SMREG_PDP_ACTIVATE_REQ_STRU         *pMsgIE,
               VOS_UINT8                            ucSMIndex
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.09   新规作成
      2.日    期  : 2013年03月13日
        作    者  : z00214637
        修改内容  : BodySAR项目

      3.日    期   : 2013年4月23日
        作    者   : L47619
        修改内容   : V9R1 IPv6&TAF/SM接口优化项目修改

*******************************************************************************/
VOS_VOID SM_SndPdpActReqMsg(
   SMREG_PDP_ACTIVATE_REQ_STRU         *pMsgIE,
   VOS_UINT8                            ucSMIndex
)
{
    VOS_UINT8           *pTemp;                                                 /* 定义UCHAR型临时指针                      */
    VOS_UINT8           *pSendMsg;                                              /* 定义UCHAR型指针                          */
    VOS_UINT32           ulSum;                                                 /* 定义计数器                               */
    VOS_UINT8            ucInitType;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* 申请最大内存                             */
    if(VOS_NULL_PTR == pTemp)
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpActReqMsg:ERROR: alloc msg fail!\r");
        return;
    }
    pSendMsg = pTemp;                                                           /* 指向临时指针                             */
    ulSum = 0;                                                                  /* 计数器初始值置0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* 调用函数存储TI及TI Flag                  */
    *pTemp = SM_ACT_PDP_CONTEXT_REQ;                                            /* 添加消息类型，更新指针偏移的长度         */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */
    *pTemp = ucSMIndex + SM_NSAPI_OFFSET;                                       /* Requested NSAPI赋值,更新指针偏移的长度   */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */

    if (pMsgIE->bitOpSapi)
    {
        *pTemp = pMsgIE->ucSapi;                                                /*V200中激活时申请的SAPI一律为3*/
    }
    else
    {
        *pTemp = SM_SAPI_NOT_ASSIGN;                                           /* Requested LLC SAPI赋值更新指针偏移的长度 */
    }

    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */

    *pTemp = (VOS_UINT8)(pMsgIE->stReqQos.ulQosLen);                            /* 添加Requested QoS长度                    */

    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    SM_MemCpy(pTemp,
        (const VOS_VOID *)pMsgIE->stReqQos.aucQos, pMsgIE->stReqQos.ulQosLen);  /* 添加Requested QoS内容                    */

    pTemp += pMsgIE->stReqQos.ulQosLen;                                         /* 更新指针偏移的长度                       */
    ulSum += pMsgIE->stReqQos.ulQosLen + 1;                                     /* 更新计数器                               */

    *pTemp = (VOS_UINT8)(pMsgIE->stReqPdpAddr.ulPdpAddrLen);                    /* 添加Requested PDP address长度            */

    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    SM_MemCpy(pTemp, pMsgIE->stReqPdpAddr.aucPdpAddr,
              pMsgIE->stReqPdpAddr.ulPdpAddrLen);                               /* 添加Requested PDP address内容            */
    pTemp += pMsgIE->stReqPdpAddr.ulPdpAddrLen;                                 /* 更新指针偏移的长度                       */
    ulSum += pMsgIE->stReqPdpAddr.ulPdpAddrLen + 1;                             /* 更新计数器                               */
    if( SM_TRUE == pMsgIE->bitOpAcsPointName )
    {                                                                           /* Access point name存在                    */
        *pTemp = 0x28;                                                          /* 添加IEI                                  */
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stAcsPointName.ulApnLen);                  /* 添加Access point name长度                */
        SM_MemCpy((pTemp + 1), pMsgIE->stAcsPointName.aucApnAddr,
            pMsgIE->stAcsPointName.ulApnLen);                                   /* 添加Access point name内容                */
        pTemp += pMsgIE->stAcsPointName.ulApnLen + 1;                           /* 更新指针偏移的长度                       */
        ulSum += pMsgIE->stAcsPointName.ulApnLen + 2;                           /* 更新计数器                               */
    }
    if( SM_TRUE == pMsgIE->bitOpProtCfgOpt )
    {                                                                           /* Protocol configuration options存在       */
        *pTemp = 0x27;                                                          /* 添加IEI                                  */
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stProtCfgOpt.ulPcoLen);                    /* 添加Protocol configuration options长度   */
        SM_MemCpy(pTemp + 1, pMsgIE->stProtCfgOpt.aucProtCfgOpt,
            pMsgIE->stProtCfgOpt.ulPcoLen);                                     /* 添加Protocol configuration options内容   */
        pTemp += pMsgIE->stProtCfgOpt.ulPcoLen + 1;                             /* 更新指针偏移的长度                       */
        ulSum += pMsgIE->stProtCfgOpt.ulPcoLen + 2;                             /* 更新计数器                               */
    }

    SM_SndTafMsg(pSendMsg, ucSMIndex,ulSum,SM_GetMostHighPri(), SM_TRUE);       /* 将待发送的空口消息发送给GMM              */
    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Activate PDP context request\r");
    ucInitType = ACTIVE_REQUEST_INIT_TYPE_MO;
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_ACTIVE_REQ,
                    (VOS_VOID *)&ucInitType,
                    NAS_OM_EVENT_PDP_ACTIVE_REQ_LEN);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndReqPdpActRejMsg
  Function:    将TAF发给SM的TAFSM_PDP_ACTIVATE_REJ_RSP消息转换成数据流发送
  Input:       SMREG_PDP_ACTIVATE_REJ_RSP_STRU   *pMsgIE      消息指针
               VOS_UINT8                          ucTi         Transaction identifier
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.张志勇      2003.12.09   新规作成

  2.日    期   : 2012年8月27日
    作    者   : m00217266
    修改内容   : 修改原因值类型，并转换原因值
*******************************************************************************/
VOS_VOID SM_SndReqPdpActRejMsg(
                       SMREG_PDP_ACTIVATE_REJ_RSP_STRU   *pMsgIE,               /* 消息指针                                 */
                       VOS_UINT8                          ucTi                  /* Transaction identifier                   */
                          )
{
    VOS_UINT8           *pTemp;                                                 /* 定义UCHAR型临时指针                      */
    VOS_UINT8           *pSendMsg;                                              /* 定义UCHAR型指针                          */
    VOS_UINT32           ulSum;                                                 /* 定义计数器                               */
    VOS_UINT8            ucSmCause;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* 申请最大内存                             */
    if ( VOS_NULL_PTR == pTemp )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndReqPdpActRejMsg:ERROR:Alloc msg fail!" );
        return;
    }

    pSendMsg = pTemp;                                                           /* 指向临时指针                             */
    ulSum = 0;                                                                  /* 计数器初始值置0                          */

    if( SM_INVALID_NSAPI != g_TiMapToNsapi[ucTi] )
    {                                                                           /* 实体存在                                 */
        SM_ComGetTI(g_TiMapToNsapi[ucTi], &pTemp, &ulSum);                      /* 调用函数存储TI及TI Flag                  */
    }
    else
    {                                                                           /* 实体不存在                               */
        if( ucTi < 0x07 )
        {                                                                       /* TI占用1/2字节                            */
            *pTemp = ((ucTi << 4) & 0x70) | 0x80;                               /* 获得TI,Ti Flag置1                        */
            *pTemp = *pTemp | NAS_PD_SM;                                        /* 设定PD                                   */
            pTemp++;                                                            /* 更新指针偏移的长度                       */
            ulSum += 1;                                                         /* 计数器加1                                */
        }
        else
        {                                                                       /* TI占用3/2字节                            */
            *pTemp = 0xF0;                                                      /* Ti Flag置1                               */
            *pTemp = *pTemp | NAS_PD_SM;                                        /* 设定PD                                   */
            pTemp++;                                                            /* 更新指针偏移的长度                       */
            *pTemp = ucTi | 0x80;                                               /* 获得TI                                   */
            pTemp++;                                                            /* 更新指针偏移的长度                       */
            ulSum += 2;                                                         /* 计数器加2                                */
        }
    }
    *pTemp = SM_REQ_PDP_CONTEXT_REJ;                                            /* 添加消息类型，更新指针偏移的长度         */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */
    if( SM_NULL != pMsgIE )
    {                                                                           /* 消息不为空                               */
        *pTemp = NAS_SM_TRANS_TAF_CAUSE(pMsgIE->enCause);                                             /* 添加SM cause                             */
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        ulSum += 1;                                                             /* 计数器加1                                */
    }
    else
    {
        *pTemp = TAF_SM_REJ_CAUSE_INSUFF_RESOURCE;                              /* 添加SM cause                             */
        ulSum += 1;                                                             /* 计数器加1                                */
    }

    SM_SndTafMsg(pSendMsg, g_TiMapToNsapi[ucTi], ulSum, SM_GetMostHighPri(),
        SM_FALSE);                                                              /* 将待发送的空口消息发送给GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Request PDP context activation reject\r");
    if( SM_NULL != pMsgIE )
    {
        ucSmCause = NAS_SM_TRANS_TAF_CAUSE(pMsgIE->enCause);

        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL,
                        (VOS_VOID *)&ucSmCause,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL_LEN);
    }

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpDeActReqMsg
  Function:    将TAF发给SM的TAFSM_PDP_DEACTIVATE_REQ消息转换成数据流发送
  Input:       SMREG_PDP_DEACTIVATE_REQ_STR   *pMsgIE          消息指针
               VOS_UINT8                      ucSMIndex        SM索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1. 张志勇      2003.12.09   新规作成
  2.日    期   : 2010年02月01日
    作    者   : l65478
    修改内容   : AT2D16503,发送去激活消息时，如果tear down值为0，不需要带IE“tear down”

  3.日    期   : 2012年8月27日
    作    者   : m00217266
    修改内容   : 修改原因值类型，并转换原因值
*******************************************************************************/
VOS_VOID SM_SndPdpDeActReqMsg(
                       SMREG_PDP_DEACTIVATE_REQ_STRU *pMsgIE,                      /* 消息指针                                 */
                       VOS_UINT8                      ucSMIndex                     /* SM索引                                   */
                         )
{
    VOS_UINT8           *pTemp;                                                     /* 定义UCHAR型临时指针                      */
    VOS_UINT8           *pSendMsg;                                                  /* 定义UCHAR型指针                          */
    VOS_UINT32           ulSum;                                                      /* 定义计数器                               */
    VOS_UINT8            ucInitType;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                             /* 申请最大内存                             */
    if ( VOS_NULL_PTR == pTemp )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpDeActReqMsg:ERROR:Alloc msg fail!" );
        return;
    }

    pSendMsg = pTemp;                                                           /* 指向临时指针                             */
    ulSum = 0;                                                                  /* 计数器初始值置0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* 调用函数存储TI及TI Flag                  */
    *pTemp = SM_DEACT_PDP_CONTEXT_REQ;                                          /* 添加消息类型，更新指针偏移的长度         */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */
    if( SM_NULL != pMsgIE )
    {                                                                           /* 消息不为空                               */
        *pTemp = NAS_SM_TRANS_TAF_CAUSE(pMsgIE->enCause);                                             /* 添加SM cause                             */
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        ulSum += 1;                                                             /* 计数器加1                                */
        if( SM_TRUE == pMsgIE->bitOpTearDownInd )
        {                                                                       /* Tear down indicator存在                  */
            /* 0:tear down not requested;1:tear down requested.
               0时不需要带此IE*/
            if (0 != (pMsgIE->ucTearDownInd ))
            {
                *pTemp = 0x90 | (pMsgIE->ucTearDownInd);                        /* 添加IEI,TDI flag                         */
                pTemp++;                                                            /* 更新指针偏移的长度                       */
                ulSum += 1;                                                         /* 计数器加1                                */
            }
        }
    }
    else
    {
        *pTemp = TAF_SM_REJ_CAUSE_INSUFF_RESOURCE;                              /* 添加SM cause                             */
        ulSum += 1;                                                             /* 计数器加1                                */
    }

    SM_SndTafMsg(pSendMsg, ucSMIndex, ulSum,
                GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_TRUE);                   /* 将待发送的空口消息发送给GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Deactivate PDP context request\r");
    ucInitType = DEACTIVE_REQUEST_INIT_TYPE_MO;
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_DEACTIVE_REQ,
                    (VOS_VOID *)&ucInitType,
                    NAS_OM_EVENT_PDP_DEACTIVE_REQ_LEN);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpModAccMsg
  Function:    将TAF发给SM的TAFSM_PDP_MODIFY_RSP消息转换成数据流发送
  Input:       SMREG_PDP_MODIFY_RSP_STRU     *pMsgIE          消息指针
               VOS_UINT8                      ucSMIndex        SM索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.09   新规作成
*******************************************************************************/
VOS_VOID SM_SndPdpModAccMsg(
                       SMREG_PDP_MODIFY_RSP_STRU  *pMsgIE,                      /* 消息指针                                 */
                       VOS_UINT8                   ucSMIndex                    /* SM索引                                   */
                       )
{
    VOS_UINT8           *pTemp;                                                 /* 定义UCHAR型临时指针                      */
    VOS_UINT8           *pSendMsg;                                              /* 定义UCHAR型指针                          */
    VOS_UINT32           ulSum;                                                 /* 定义计数器                               */

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* 申请最大内存                             */
    if ( VOS_NULL_PTR == pTemp )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpModAccMsg:ERROR:Alloc msg fail!" );
        return;
    }
    pSendMsg = pTemp;                                                           /* 指向临时指针                             */
    ulSum = 0;                                                                  /* 计数器初始值置0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* 调用函数存储TI及TI Flag                  */
    *pTemp = SM_MOD_PDP_CONTEXT_ACC_M2N;                                        /* 添加消息类型，更新指针偏移的长度         */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */

    SM_SndTafMsg(pSendMsg,ucSMIndex, ulSum,
                GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_FALSE);                  /* 将待发送的空口消息发送给GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Modify PDP context accept (MS to network direction)\r");
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_SUCC,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*****************************************************************************
 函 数 名  : NAS_SM_SndPdpModRejMsg
 功能描述  : 将TAF发给SM的TAFSM_PDP_MODIFY_REJ_RSP消息转换成数据流发送
 输入参数  : SMREG_PDP_MODIFY_REJ_RSP_STRU    *pMsgIE
             VOS_UINT8                         ucSMIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月9日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年8月27日
    作    者   : m00217266
    修改内容   : 修改原因值类型，并转换原因值
*****************************************************************************/
VOS_VOID NAS_SM_SndPdpModRejMsg(
    SMREG_PDP_MODIFY_REJ_RSP_STRU      *pstMsgIE,
    VOS_UINT8                           ucSMIndex
)
{
    VOS_UINT8                           *pucTemp;
    VOS_UINT8                           *pucSendMsg;
    VOS_UINT32                          ulSum;

    pucTemp = (VOS_UINT8*)SM_Malloc(SM_MAX_SND_MSG_LEN);                        /* 申请最大内存                             */
    if (VOS_NULL_PTR == pucTemp)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM, "NAS_SM_SndPdpModRejMsg:ERROR:Alloc msg fail!\r\n");
        return;
    }

    pucSendMsg  = pucTemp;                                                      /* 指向临时指针                             */
    ulSum       = 0;                                                            /* 计数器初始值置0                          */

    SM_ComGetTI(ucSMIndex, &pucTemp, &ulSum);                                   /* 调用函数存储TI及TI Flag                  */
    *pucTemp = SM_MOD_PDP_CONTEXT_REJ;                                          /* 添加消息类型，更新指针偏移的长度         */
    pucTemp++;                                                                  /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */

    if (VOS_NULL_PTR != pstMsgIE)
    {
        *pucTemp = NAS_SM_TRANS_TAF_CAUSE(pstMsgIE->enCause);                                         /* 添加SM cause                             */
/* 消息不为空                               */
        pucTemp++;                                                              /* 更新指针偏移的长度                       */
        ulSum += 1;                                                             /* 计数器加1                                */
    }
    else
    {
        *pucTemp = TAF_SM_REJ_CAUSE_INSUFF_RESOURCE;                            /* 添加SM cause                             */
        ulSum += 1;                                                             /* 计数器加1                                */
    }

    SM_SndTafMsg(pucSendMsg, ucSMIndex, ulSum,
                GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_FALSE);                  /* 将待发送的空口消息发送给GMM              */

    NAS_NORMAL_LOG(WUEPS_PID_SM,
        "NAS_SM_SndPdpModRejMsg: SM->NW: Modify PDP context reject\r\n");

    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpModReqMsg
  Function:    将TAF发给SM的TAFSM_PDP_MODIFY_REQ消息转换成数据流发送
  Input:       SMREG_PDP_MODIFY_REQ_STRU    *pMsgIE           消息指针
               VOS_UINT8                     ucSMIndex        SM索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.09   新规作成
*******************************************************************************/
VOS_VOID SM_SndPdpModReqMsg(
                       SMREG_PDP_MODIFY_REQ_STRU *pMsgIE,                       /* 消息指针                                 */
                       VOS_UINT8                  ucSMIndex                     /* SM索引                                   */
                       )
{
    VOS_UINT8           *pTemp;                                                 /* 定义UCHAR型临时指针                      */
    VOS_UINT8           *pSendMsg;                                              /* 定义UCHAR型指针                          */
    VOS_UINT32           ulSum;                                                 /* 定义计数器                               */
    VOS_UINT8            ucInitType;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* 申请最大内存                             */
    if(VOS_NULL_PTR == pTemp)
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpModReqMsg:ERROR: alloc msg fail!\r");
        return;
    }
    pSendMsg = pTemp;                                                           /* 指向临时指针                             */
    ulSum = 0;                                                                  /* 计数器初始值置0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* 调用函数存储TI及TI Flag                  */
    *pTemp = SM_MOD_PDP_CONTEXT_REQ_M2N;                                        /* 添加消息类型，更新指针偏移的长度         */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */
    *pTemp         = 0x32;                                                      /* 填写Requested LLC SAPI的IEI              */

    if ( pMsgIE->bitOpSapi)
    {
        *( pTemp + 1 ) = pMsgIE->ucSapi;
    }
    else
    {
        *( pTemp + 1 ) = SM_SAPI_NOT_ASSIGN;                                    /* 填写Requested LLC SAPI的VALUE            */
    }


    pTemp += 2;                                                                 /* 更新指针偏移的长度                       */
    ulSum += 2;                                                                 /* 计数器加1                                */
    if( SM_TRUE == pMsgIE->bitOpRequestedNewQos )
    {                                                                           /* Requested new QoS存在                    */
        *pTemp = 0x30;                                                          /* 添加IEI                                  */
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stRequestedNewQos.ulQosLen);               /* 添加Requested new QoS长度                */
        SM_MemCpy(pTemp+1, pMsgIE->stRequestedNewQos.aucQos,
            pMsgIE->stRequestedNewQos.ulQosLen);                                /* 添加Requested new QoS内容                */
        pTemp += pMsgIE->stRequestedNewQos.ulQosLen + 1;                        /* 更新指针偏移的长度                       */
        ulSum += pMsgIE->stRequestedNewQos.ulQosLen + 2;                        /* 更新计数器                               */
    }
    if( SM_TRUE == pMsgIE->bitOpNewtft )
    {                                                                           /* New TFT存在                              */
        *pTemp = 0x31;                                                          /* 添加IEI                                  */
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stNewtft.ulTftLen);                        /* 添加New TFT长度                          */
        SM_MemCpy(pTemp + 1,
                  pMsgIE->stNewtft.aucNewtft,
                  pMsgIE->stNewtft.ulTftLen);                                   /* 添加New TFT内容                          */
        pTemp += pMsgIE->stNewtft.ulTftLen + 1;                                 /* 更新指针偏移的长度                       */
        ulSum += pMsgIE->stNewtft.ulTftLen + 2;                                 /* 更新计数器                               */
    }

    SM_SndTafMsg(pSendMsg, ucSMIndex,ulSum,
                GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_TRUE);                   /* 将待发送的空口消息发送给GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Modify PDP context request (MS to network direction)\r");
    ucInitType = MODIFY_REQUEST_INIT_TYPE_MO;
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ,
                    (VOS_VOID *)&ucInitType,
                    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ_LEN);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpActSecReqMsg
  Function:    将TAF发给SM的TAFSM_PDP_ACTIVATE_SEC_REQ消息转换成数据流发送
  Input:       SMREG_PDP_ACTIVATE_SEC_REQ_STRU  *pMsgIE          消息指针
               VOS_UINT8                         ucSMIndex        SM索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.09   新规作成
      2.  CBJ      2005.02.18   modify
*******************************************************************************/
VOS_VOID SM_SndPdpActSecReqMsg(
                       SMREG_PDP_ACTIVATE_SEC_REQ_STRU     *pMsgIE,                       /* 消息指针                                 */
                       VOS_UINT8                            ucSMIndex                     /* SM索引                                   */
                          )
{
    VOS_UINT8           *pTemp;                                                 /* 定义UCHAR型临时指针                      */
    VOS_UINT8           *pSendMsg;                                              /* 定义UCHAR型指针                          */
    VOS_UINT32           ulSum;                                                 /* 定义计数器                               */
    VOS_UINT8           ucTi;
    VOS_UINT8           ucTiIndex;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* 申请最大内存                             */
    if(VOS_NULL_PTR == pTemp)
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpActSecReqMsg:ERROR: alloc msg fail!\r");
        return;
    }
    pSendMsg = pTemp;                                                           /* 指向临时指针                             */
    ulSum = 0;                                                                  /* 计数器初始值置0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* 调用函数存储TI及TI Flag                  */
    *pTemp = SM_ACT_SEC_PDP_CONTEXT_REQ;                                        /* 添加消息类型，更新指针偏移的长度         */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */
    *pTemp = ucSMIndex + SM_NSAPI_OFFSET;                                       /* Requested NSAPI赋值,更新指针偏移的长度   */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */

    if ( pMsgIE->bitOpSapi)
    {
        *pTemp = pMsgIE->ucSapi;
    }
    else
    {
        *pTemp = SM_SAPI_NOT_ASSIGN;                                            /* Requested LLC SAPI赋值更新指针偏移的长度 */
    }

    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */

    *pTemp = (VOS_UINT8)(pMsgIE->stRequestedQos.ulQosLen);                      /* 添加Requested QoS长度                    */

    SM_MemCpy(pTemp + 1,
            pMsgIE->stRequestedQos.aucQos, pMsgIE->stRequestedQos.ulQosLen);    /* 添加Requested QoS内容                    */
    pTemp += pMsgIE->stRequestedQos.ulQosLen + 1;                               /* 更新指针偏移的长度                       */
    ulSum += pMsgIE->stRequestedQos.ulQosLen + 1;                               /* 更新计数器                               */
    ucTi = g_SmEntity.aPdpCntxtList[pMsgIE->ucPrimNsapi
        - SM_NSAPI_OFFSET].ucTi & 0x7f;                                         /* 取得Transaction identifier               */
    ucTiIndex = g_SmEntity.aPdpCntxtList[pMsgIE->ucPrimNsapi
        - SM_NSAPI_OFFSET].ucTi;                                                /* 获得g_TiMapToNsapi的下标                 */
    if( ucTi < 0x07 )
    {                                                                           /* Linked TI占用2字节                       */
        *pTemp = 1;                                                             /* Linked TI长度赋为1                       */
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        if( SM_TI_NET_ORG
             == g_SmEntity.aPdpCntxtList[g_TiMapToNsapi[ucTiIndex]].ucTiFlg )
        {                                                                       /* 网侧形成                                 */
            *pTemp = ((ucTi << 4) & 0x70) | 0x80;                               /* 获得TI,Ti Flag置1                        */
        }
        else
        {                                                                       /* MS形成                                   */
            *pTemp = (ucTi << 4) & 0x70;                                        /* 获得TI,Ti Flag置0                        */
        }
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        ulSum += 2;                                                             /* 计数器加2                                */
    }
    else
    {                                                                           /* Linked TI占用3字节                       */
        *pTemp = 2;                                                             /* Linked TI长度赋为2                       */
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        if( SM_TI_NET_ORG
             == g_SmEntity.aPdpCntxtList[g_TiMapToNsapi[ucTiIndex]].ucTiFlg )
        {                                                                       /* 网侧形成                                 */
            *pTemp = 0xF0;                                                      /* Ti Flag置1                               */
            pTemp++;                                                            /* 更新指针偏移的长度                       */
            *pTemp = ucTi|0x80;                                                 /* 获得TI                                   */
        }
        else
        {                                                                       /* MS形成                                   */
            *pTemp = 0x70;                                                      /* Ti Flag置0                               */
            pTemp++;                                                            /* 更新指针偏移的长度                       */
            *pTemp = ucTi|0x80;                                                 /* 获得TI                                   */
        }
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        ulSum += 3;                                                             /* 计数器加3                                */
    }
    if( SM_TRUE == pMsgIE->bitOpTft )
    {                                                                           /* TFT存在                                  */
        *pTemp = 0x36;                                                          /* 添加IEI                                  */
        pTemp++;                                                                /* 更新指针偏移的长度                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stTft.ulTftLen);                           /* 添加TFT长度                              */
        SM_MemCpy(pTemp + 1, pMsgIE->stTft.aucNewtft, pMsgIE->stTft.ulTftLen);  /* 添加TFT内容                              */
        pTemp += pMsgIE->stTft.ulTftLen + 1;                                    /* 更新指针偏移的长度                       */
        ulSum += pMsgIE->stTft.ulTftLen + 2;                                    /* 更新计数器                               */
    }

    SM_SndTafMsg(pSendMsg, ucSMIndex, ulSum, SM_GetMostHighPri(), SM_TRUE);     /* 将待发送的空口消息发送给GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Activate Secondary PDP Context Request\r");

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpDeActAccMsg
  Function:    发送DEACTIVATE PDP CONTEXT ACCEPT给GMM
  Input:       VOS_UINT8      ucSMIndex        SM索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.09   新规作成
*******************************************************************************/
VOS_VOID SM_SndPdpDeActAccMsg(VOS_UINT8   ucSMIndex)
{
    VOS_UINT8           *pTemp;                                                 /* 定义UCHAR型临时指针                      */
    VOS_UINT8           *pSendMsg;                                              /* 定义UCHAR型指针                          */
    VOS_UINT32           ulSum;                                                 /* 定义计数器                               */

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* 申请最大内存                             */
    if(VOS_NULL_PTR == pTemp)
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpDeActAccMsg:ERROR: alloc msg fail!\r");
        return;
    }
    pSendMsg = pTemp;                                                           /* 指向临时指针                             */
    ulSum = 0;                                                                  /* 计数器初始值置0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* 调用函数存储TI及TI Flag                  */
    *pTemp = SM_DEACT_PDP_CONTEXT_ACC;                                          /* 添加消息类型，更新指针偏移的长度         */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */

    SM_SndTafMsg(pSendMsg, ucSMIndex,
                ulSum,GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_FALSE);            /* 将待发送的空口消息发送给GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Deactivate PDP context accept\r");

    return;
}
/*lint +e438 +e830*/

/*******************************************************************************
  Module:      SM_SndTafSmPdpActivateRej
  Function:    作成和发送TAFSM_PDP_ACTIVATE_REJ消息
  Input:       VOS_UINT8           ucCr              Call Reference
               VOS_UINT8           ucSmCause         网侧原因
               VOS_UINT8           ucMtCause         内部原因
               SM_OCT_VARY_STRU   *pProtCfgOpt       Protocol configuration options
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.10   新规作成
  2.日    期   : 2012年6月16日
    作    者   : l60609
    修改内容   : AT&T&DCM:增加尝试次数

  3.日    期  : 2012年08月24日
    作    者  : m00217266
    修改内容  : 删除ucMtCause，修改SmCause类型
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpActivateRej(
                               VOS_UINT8                        ucCr,                           /* Call Reference                           */
                               SM_TAF_CAUSE_ENUM_UINT16         enCause,                        /* 网侧原因                                 */
                               SM_OCT_VARY_STRU                *pProtCfgOpt                     /* Protocol configuration options           */
                              )
{
    SMREG_PDP_ACTIVATE_REJ_STRU        *pActRejMsg = VOS_NULL_PTR;              /* 定义TAF结构指针                          */

    pActRejMsg = (SMREG_PDP_ACTIVATE_REJ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_REJ_STRU));
    if ( VOS_NULL_PTR == pActRejMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActivateRej:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pActRejMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pActRejMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActRejMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActRejMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_REJ;

    pActRejMsg->ucConnectId = ucCr;                                             /* 设定CR                                   */

    pActRejMsg->enCause = enCause;                                              /* 填写参数SmCause                          */
    if( (SM_NULL == pProtCfgOpt) || (0 == pProtCfgOpt->ulCnt) )
    {                                                                           /* ProtCfgOpt不存在长度为0                  */
        pActRejMsg->bitOpProtCfgOpt = 0;                                        /* 设为不存在                               */
    }
    else
    {
        pActRejMsg->bitOpProtCfgOpt = 1;                                        /* 设为存在                                 */

        pActRejMsg->stProtCfgOpt.ulPcoLen = pProtCfgOpt->ulCnt;                 /* 记录ProtCfgOpt长度                       */

        SM_MemCpy(pActRejMsg->stProtCfgOpt.aucProtCfgOpt,
                  pProtCfgOpt->pOcts,
                  pProtCfgOpt->ulCnt);                                          /* 记录ProtCfgOpt内容                       */
    }
    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* Nsapi值为0xFF                            */
        pActRejMsg->bitOpNsapi = 0;                                             /* 设为不存在                               */
    }
    else
    {
        pActRejMsg->bitOpNsapi = 1;                                             /* 设为存在                                 */

        pActRejMsg->ucNsapi = g_CrMapToNsapi[ucCr] + SM_NSAPI_OFFSET;           /* 记录Nsapi                                */
    }

    /* 填写T3380超时次数 */
    pActRejMsg->ucExpiredCount
        = g_SmEntity.aPdpCntxtList[g_CrMapToNsapi[ucCr]].TimerInfo.ucExpireTimes;


    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActRejMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActivateRej:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpActivateInd
  Function:    作成和发送TAFSM_PDP_ACTIVATE_IND消息
  Input:       SM_NW_MSG_STRU   *pMsgIe         收到的消息
               VOS_UINT8            ucCnxtIndex     Context索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.10   新规作成
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpActivateInd(
                               SM_NW_MSG_STRU   *pMsgIe,                        /* 收到的消息                               */
                               VOS_UINT8            ucCnxtIndex                     /* Context索引                              */
                              )
{
    SMREG_PDP_ACTIVATE_IND_STRU        *pActIndMsg = VOS_NULL_PTR;              /* 定义TAF结构指针                          */

    pActIndMsg = (SMREG_PDP_ACTIVATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_IND_STRU));
    if ( VOS_NULL_PTR == pActIndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActivateInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pActIndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pActIndMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActIndMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActIndMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_IND;

    pActIndMsg->ucConnectId = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;       /* 设定CR                                   */

    pActIndMsg->stOfferPdpAddr.ulPdpAddrLen = pMsgIe->PdpAddr.ucLen;            /* 记录OfferPdpAddr长度                     */

    SM_MemCpy(pActIndMsg->stOfferPdpAddr.aucPdpAddr,
              pMsgIe->PdpAddr.pValue,
              ( VOS_UINT32 )pMsgIe->PdpAddr.ucLen);                             /* 记录OfferPdpAddr内容                     */

    if( 0 == pMsgIe->Apn.ucLen )
    {                                                                           /* pAcsPointName长度为0                     */
        pActIndMsg->bitOpAcsPointName = 0;                                      /* 设为不存在                               */
    }
    else
    {
        pActIndMsg->bitOpAcsPointName = 1;                                      /* 设为存在                                 */

        pActIndMsg->stAcsPointName.ulApnLen = pMsgIe->Apn.ucLen;                /* 记录pAcsPointName长度                    */
        SM_MemCpy(pActIndMsg->stAcsPointName.aucApnAddr,
                  pMsgIe->Apn.pValue,
                  ( VOS_UINT32 )pMsgIe->Apn.ucLen );                            /* 记录pAcsPointName内容                    */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActIndMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActivateInd:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpActivateCnf
  Function:    作成和发送TAFSM_PDP_ACTIVATE_CNF消息
  Input:       SM_NW_MSG_STRU   *pMsgIe         收到的消息
               VOS_UINT8            ucCnxtIndex     Context索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.张志勇      2003.12.10   新规作成

  2.日    期   : 2012年8月27日
    作    者   : m00217266
    修改内容   : 修改原因值类型，并转换原因值

  3.日    期   : 2013年4月23日
    作    者   : L47619
    修改内容   : V9R1 IPv6&TAF/SM接口优化项目修改
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpActivateCnf(
                               SM_NW_MSG_STRU   *pMsgIe,                        /* 收到的消息                               */
                               VOS_UINT8         ucCnxtIndex                    /* Context索引                              */
                              )
{
    SMREG_PDP_ACTIVATE_CNF_STRU        *pActCnfMsg = VOS_NULL_PTR;              /* 定义TAF结构指针                          */
    VOS_UINT8                           ucCr;

    pActCnfMsg = (SMREG_PDP_ACTIVATE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_CNF_STRU));
    if ( VOS_NULL_PTR == pActCnfMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActivateCnf:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pActCnfMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pActCnfMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActCnfMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActCnfMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_CNF;

    ucCr = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;
    pActCnfMsg->ucConnectId        = ucCr;                                      /* 设定CR                                   */
    pActCnfMsg->stMsgHdr.ulMsgName = ID_SMREG_PDP_ACTIVATE_CNF;                 /* 设定消息类型                             */

    pActCnfMsg->stNegoQos.ulQosLen = pMsgIe->Qos.ucLen;                         /* 存储Qos长度                              */

    SM_MemCpy(pActCnfMsg->stNegoQos.aucQos,
              pMsgIe->Qos.pValue,
              ( VOS_UINT32 )pMsgIe->Qos.ucLen);                                 /* 存储Qos内容                              */

    if( 0 == pMsgIe->PdpAddr.ucLen )
    {                                                                           /* PdpAddr长度为0                           */
        pActCnfMsg->bitOpPdpAddr = 0;                                           /* 设为不存在                               */
    }
    else
    {
        pActCnfMsg->bitOpPdpAddr = 1;                                           /* 设为存在                                 */

        pActCnfMsg->stPdpAddr.ulPdpAddrLen = pMsgIe->PdpAddr.ucLen;             /* 存储PdpAddr长度                          */

        SM_MemCpy(pActCnfMsg->stPdpAddr.aucPdpAddr,
                  pMsgIe->PdpAddr.pValue,
                  ( VOS_UINT32 )pMsgIe->PdpAddr.ucLen);                         /* 存储PdpAddr内容                          */
    }

    if( 0 == pMsgIe->ProCnfgOpt.ucLen )
    {                                                                           /* ProtCfgOpt长度为0                        */
        pActCnfMsg->bitOpProtCfgOpt = 0;                                        /* 设为不存在                               */
    }
    else
    {
        pActCnfMsg->bitOpProtCfgOpt = 1;                                        /* 设为存在                                 */

        pActCnfMsg->stProtCfgOpt.ulPcoLen = pMsgIe->ProCnfgOpt.ucLen;           /* 记录ProtCfgOpt长度                       */

        SM_MemCpy(pActCnfMsg->stProtCfgOpt.aucProtCfgOpt,
                  pMsgIe->ProCnfgOpt.pValue,
                  ( VOS_UINT32 )pMsgIe->ProCnfgOpt.ucLen);                      /* 记录ProtCfgOpt内容                       */
    }
    if( 0 == pMsgIe->Pfi.ucLen )
    {                                                                           /* PacketFlowId长度为0                      */
        pActCnfMsg->bitOpPacketFlowId = 0;                                      /* 设为不存在                               */
    }
    else
    {
        pActCnfMsg->bitOpPacketFlowId = 1;                                      /* 设为存在                                 */

        pActCnfMsg->stPacketFlowId.ulPFILen = pMsgIe->Pfi.ucLen;                /* 记录PacketFlowId长度                     */

        SM_MemCpy(&pActCnfMsg->stPacketFlowId.ucPacketFlowId,
            pMsgIe->Pfi.pValue, ( VOS_UINT32 )pMsgIe->Pfi.ucLen);               /* 记录PacketFlowId内容                     */
    }
    pActCnfMsg->bitOpNsapi = 1;                                                 /* 设为存在                                 */

    pActCnfMsg->ucNsapi = (ucCnxtIndex + SM_NSAPI_OFFSET);                      /* 记录Nsapi                                */

    /*在向TAF发送的消息中赋值以下信息:*/
    if (g_aucSapi[0][0])
    {
        /*将暂存的SAPI读到发送给APS*/
        pActCnfMsg->bitOpSapi = 1;
        pActCnfMsg->ucSapi    = g_aucSapi[0][1];
        g_aucSapi[0][0]       = 0;                                              /*置暂存标识为无效*/
    }

    pActCnfMsg->bitOpRadioPriority = 1;
    pActCnfMsg->ucRadioPriority    = pMsgIe->ucRadioPri;

#if (FEATURE_ON == FEATURE_IPV6)
    if (0 == pMsgIe->stSmCauseTwo.ucLen)
    {
        pActCnfMsg->bitOpSmCause = VOS_FALSE;
    }
    else
    {
        pActCnfMsg->bitOpSmCause = VOS_TRUE;

        pActCnfMsg->enCause = NAS_SM_MapSmNWCause(*(pMsgIe->stSmCauseTwo.pValue));    /* 记录SmCause                              */
    }
#endif

    pActCnfMsg->stTransId.ucTiFlag = NAS_SM_GetPdpTiFlg(ucCnxtIndex);

    if (SM_TI_NET_ORG != NAS_SM_GetPdpTiFlg(ucCnxtIndex))
    {
        if (0x80 == (NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x80))
        {
            pActCnfMsg->stTransId.ucTiValue
                = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x7F;
        }
        else
        {
            pActCnfMsg->stTransId.ucTiValue
                = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x07;
        }
    }
    else
    {
        pActCnfMsg->stTransId.ucTiValue
            = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x7F;
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActCnfMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActivateCnf:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpDeActCnf
  Function:    作成和发送TAFSM_PDP_DEACTIVATE_CNF消息
  Input:       VOS_UINT8           ucCr              Call Reference
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.10   新规作成
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpDeActCnf(
                            VOS_UINT8           ucCr                                /* Call Reference                           */
                           )
{
    SMREG_PDP_DEACTIVATE_CNF_STRU      *pstDeactCnfMsg = VOS_NULL_PTR;          /* 定义TAF结构指针                          */

    pstDeactCnfMsg = (SMREG_PDP_DEACTIVATE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_DEACTIVATE_CNF_STRU));
    if ( VOS_NULL_PTR == pstDeactCnfMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpDeActCnf:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pstDeactCnfMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_DEACTIVATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pstDeactCnfMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDeactCnfMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pstDeactCnfMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_DEACTIVATE_CNF;

    pstDeactCnfMsg->ucConnectId = ucCr;                                         /* 设定CR                                   */

    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* Nsapi值为0xFF                            */
        pstDeactCnfMsg->bitOpNsapi = 0;                                         /* 设为不存在                               */
    }
    else
    {
        pstDeactCnfMsg->bitOpNsapi = 1;                                         /* 设为存在                                 */

        pstDeactCnfMsg->ucNsapi = g_CrMapToNsapi[ucCr] + SM_NSAPI_OFFSET;       /* 记录Nsapi                                */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pstDeactCnfMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpDeActCnf:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpDeActInd
  Function:    作成和发送TAFSM_PDP_DEACTIVATE_IND消息
  Input:       VOS_UINT8                            ucCr              Call Reference
               SM_TAF_CAUSE_ENUM_UINT16             enCause
               VOS_UINT8                            ucTdi
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.  张志勇      2003.12.10   新规作成

  2.日    期   : 2012年8月27日
    作    者   : m00217266
    修改内容   : 修改原因值类型
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpDeActInd(
    VOS_UINT8                           ucCr,                                   /* Call Reference                           */
    SM_TAF_CAUSE_ENUM_UINT16            enCause,
    VOS_UINT8                           ucTdi                                   /* Tear down indicator                      */
)
{
    SMREG_PDP_DEACTIVATE_IND_STRU        *pDeactIndMsg = VOS_NULL_PTR;          /* 定义TAF结构指针                          */

    pDeactIndMsg = (SMREG_PDP_DEACTIVATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_DEACTIVATE_IND_STRU));
    if ( VOS_NULL_PTR == pDeactIndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpDeActInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pDeactIndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_DEACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pDeactIndMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pDeactIndMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pDeactIndMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_DEACTIVATE_IND;

    pDeactIndMsg->ucConnectId = ucCr;                                           /* 设定CR                                   */

    pDeactIndMsg->enCause  = enCause;                                           /* 设定SmCause                              */

    if( SM_TRUE == ucTdi )
    {                                                                           /* Tear down indicator为1                   */
        pDeactIndMsg->bitOpTearDownInd = 1;                                     /* 设为存在                                 */

        pDeactIndMsg->ucTearDownInd = ucTdi;                                    /* TearDownInd赋值                          */
    }
    else
    {
        pDeactIndMsg->bitOpTearDownInd = 0;                                     /* 设为不存在                               */
    }

    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* Nsapi值为0xFF                            */
        pDeactIndMsg->bitOpNsapi = 0;                                           /* 设为不存在                               */
    }
    else
    {
        pDeactIndMsg->bitOpNsapi = 1;                                           /* 设为存在                                 */

        pDeactIndMsg->ucNsapi = g_CrMapToNsapi[ucCr]+SM_NSAPI_OFFSET;           /* 记录Nsapi                                */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pDeactIndMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpDeActInd:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpModifyInd
  Function:    作成和发送TAFSM_PDP_MODIFY_IND消息
  Input:       SM_NW_MSG_STRU   *pMsgIe         收到的消息
               VOS_UINT8            ucCnxtIndex     Context索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.10   新规作成
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpModifyInd(
                               SM_NW_MSG_STRU   *pMsgIe,                        /* 收到的消息                               */
                               VOS_UINT8            ucCnxtIndex                     /* Context索引                              */
                            )
{
    SM_NW_MSG_STRU                     *pRcvMsgIe;
    SMREG_PDP_MODIFY_IND_STRU          *pModIndMsg = VOS_NULL_PTR;              /* 定义TAF结构指针                          */
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucInitType;

    pRcvMsgIe = pMsgIe;

    pModIndMsg = (SMREG_PDP_MODIFY_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_MODIFY_IND_STRU));
    if ( VOS_NULL_PTR == pModIndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpModifyInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pModIndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pModIndMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pModIndMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pModIndMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_MODIFY_IND;

    ucCr = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;
    pModIndMsg->ucConnectId = ucCr;                                             /* 设定CR                                   */

    pModIndMsg->stNewQos.ulQosLen = pRcvMsgIe->Qos.ucLen;                       /* 存储NewQos长度                           */

    SM_MemCpy(pModIndMsg->stNewQos.aucQos,
              pRcvMsgIe->Qos.pValue,
              (VOS_UINT32)pRcvMsgIe->Qos.ucLen);                                /* 存储NewQos内容                           */

    if( 0 == pRcvMsgIe->PdpAddr.ucLen )
    {                                                                           /* PdpAddr长度为0                           */
        pModIndMsg->bitOpPdpAddr = 0;                                           /* 设为不存在                               */
    }
    else
    {
        pModIndMsg->bitOpPdpAddr = 1;                                           /* 设为存在                                 */

        pModIndMsg->stPdpAddr.ulPdpAddrLen = pRcvMsgIe->PdpAddr.ucLen;          /* 存储PdpAddr长度                          */

        SM_MemCpy(pModIndMsg->stPdpAddr.aucPdpAddr,
                  pRcvMsgIe->PdpAddr.pValue,
                  (VOS_UINT32)pRcvMsgIe->PdpAddr.ucLen);                        /* 存储PdpAddr内容                          */

    }

    if( 0 == pRcvMsgIe->Pfi.ucLen )
    {                                                                           /* PacketFlowId长度为0                      */
        pModIndMsg->bitOpPacketFlowId = 0;                                      /* 设为不存在                               */
    }
    else
    {
        pModIndMsg->bitOpPacketFlowId = 1;                                      /* 设为存在                                 */

        pModIndMsg->stPacketFlowId.ulPFILen = pRcvMsgIe->Pfi.ucLen;             /* 记录PacketFlowId长度                     */

        SM_MemCpy(&pModIndMsg->stPacketFlowId.ucPacketFlowId,
                  pRcvMsgIe->Pfi.pValue,
                  (VOS_UINT32)pRcvMsgIe->Pfi.ucLen);                            /* 记录PacketFlowId内容                     */

    }
    if( 0xFF == ucCnxtIndex )
    {                                                                           /* Nsapi值为0xFF                            */
        pModIndMsg->bitOpNsapi = 0;                                             /* 设为不存在                               */
    }
    else
    {
        pModIndMsg->bitOpNsapi = 1;                                             /* 设为存在                                 */

        pModIndMsg->ucNsapi = ucCnxtIndex + SM_NSAPI_OFFSET;                    /* 记录Nsapi                                */
    }

    /*SAPI*/
    if (g_aucSapi[0][0])
    {
        pModIndMsg->bitOpSapi = 1;
        pModIndMsg->ucSapi  = g_aucSapi[0][1];
        g_aucSapi[0][0] = 0;
    }
    else
    {
        pModIndMsg->bitOpSapi = 0;
    }

    /*Radio Priority*/
    pModIndMsg->bitOpRadioPriority = 1;
    pModIndMsg->ucRadioPriority    = pRcvMsgIe->ucRadioPri;
#if (FEATURE_ON == FEATURE_IPV6)
    pModIndMsg->bitOpSpare       = 0;
#else
    pModIndMsg->bitOpSpare       = 0;
#endif
    if (ucCnxtIndex < SM_MAX_NSAPI_NUM)
    {
        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pModIndMsg))
        {
            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "SM_SndTafSmPdpModifyInd:WARNING:Send msg fail!" );
        }

        ucInitType = MODIFY_REQUEST_INIT_TYPE_MT;
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ,
                        (VOS_VOID *)&ucInitType,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ_LEN);
    }
    else
    {
        PS_FREE_MSG(WUEPS_PID_SM, pModIndMsg);
    }
    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpModifyCnf
  Function:    作成和发送TAFSM_PDP_MODIFY_CNF消息
  Input:       SM_NW_MSG_STRU   *pMsgIe         收到的消息
               VOS_UINT8            ucCnxtIndex     Context索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.10   新规作成
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpModifyCnf(
                               SM_NW_MSG_STRU   *pMsgIe,                        /* 收到的消息                               */
                               VOS_UINT8            ucCnxtIndex                     /* Context索引                              */
                            )
{
    SMREG_PDP_MODIFY_CNF_STRU          *pModCnfMsg = VOS_NULL_PTR;              /* 定义TAF结构指针                          */
    VOS_UINT8                           ucCr;

    pModCnfMsg = (SMREG_PDP_MODIFY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_MODIFY_CNF_STRU));
    if ( VOS_NULL_PTR == pModCnfMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpModifyCnf:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pModCnfMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_MODIFY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pModCnfMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pModCnfMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pModCnfMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_MODIFY_CNF;

    ucCr = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;
    pModCnfMsg->ucConnectId = ucCr;                                                       /* 设定CR                                   */

    if( 0 == pMsgIe->Qos.ucLen )
    {                                                                           /* NegotiatedQos长度为0                     */
        pModCnfMsg->bitOpNegotiatedQos = 0;                                     /* 设为不存在                               */
    }
    else
    {
        pModCnfMsg->bitOpNegotiatedQos = 1;                                     /* 设为存在                                 */

        pModCnfMsg->stNegotiatedQos.ulQosLen = pMsgIe->Qos.ucLen;               /* 存储NegotiatedQos长度                    */

        SM_MemCpy(pModCnfMsg->stNegotiatedQos.aucQos,
                  pMsgIe->Qos.pValue,
                  (VOS_UINT32)pMsgIe->Qos.ucLen);                               /* 存储NegotiatedQos内容                    */
    }
    if( 0 == pMsgIe->Pfi.ucLen )
    {                                                                           /* PacketFlowId长度为0                      */
        pModCnfMsg->bitOpPacketFlowId = 0;                                      /* 设为不存在                               */
    }
    else
    {
        pModCnfMsg->bitOpPacketFlowId = 1;                                      /* 设为存在                                 */

        pModCnfMsg->stPacketFlowId.ulPFILen = pMsgIe->Pfi.ucLen;                /* 记录PacketFlowId长度                     */

        SM_MemCpy(&pModCnfMsg->stPacketFlowId.ucPacketFlowId,
                  pMsgIe->Pfi.pValue,
                  (VOS_UINT32)pMsgIe->Pfi.ucLen);                               /* 记录PacketFlowId内容                     */
    }
    if( 0xFF == ucCnxtIndex )
    {                                                                           /* Nsapi值为0xFF                            */
        pModCnfMsg->bitOpNsapi = 0;                                             /* 设为不存在                               */
    }
    else
    {
        pModCnfMsg->bitOpNsapi = 1;                                             /* 设为存在                                 */

        pModCnfMsg->ucNsapi = (ucCnxtIndex + SM_NSAPI_OFFSET);                  /* 记录Nsapi                                */
    }

    /*SAPI*/
    if (g_aucSapi[0][0])
    {
        pModCnfMsg->bitOpSapi = 1;
        pModCnfMsg->ucSapi    = g_aucSapi[0][1];
        g_aucSapi[0][0] = 0;
    }
    else
    {
        pModCnfMsg->bitOpSapi = 0;
    }

    /*Radio Priority*/
    pModCnfMsg->bitOpRadioPriority = 1;
    pModCnfMsg->ucRadioPriority    = pMsgIe->ucRadioPri;
    pModCnfMsg->bitOpSpare         =  0;

    if (ucCnxtIndex < SM_MAX_NSAPI_NUM)
    {
        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pModCnfMsg))
        {
            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "SM_SndTafSmPdpModifyCnf:WARNING:Send msg fail!" );
        }
    }
    else
    {
        PS_FREE_MSG(WUEPS_PID_SM, pModCnfMsg);
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpModifyRej
  Function:    作成和发送TAFSM_PDP_MODIFY_REJ 消息
  Input:       SM_TAF_CAUSE_ENUM_UINT16   enCause
               VOS_UINT8           ucCr
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.  张志勇      2003.12.10   新规作成

  2.日    期   : 2012年8月27日
    作    者   : m00217266
    修改内容   : 修改原因值类型
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpModifyRej(
    SM_TAF_CAUSE_ENUM_UINT16   enCause,
    VOS_UINT8                  ucCr                              /* Call Reference                           */
)
{
    SMREG_PDP_MODIFY_REJ_STRU          *pModRejMsg = VOS_NULL_PTR;

    pModRejMsg = (SMREG_PDP_MODIFY_REJ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_MODIFY_REJ_STRU));
    if ( VOS_NULL_PTR == pModRejMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpModifyRej:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pModRejMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_MODIFY_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pModRejMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pModRejMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pModRejMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_MODIFY_REJ;

    pModRejMsg->ucConnectId = ucCr;                                             /* 设定CR                                   */

    pModRejMsg->enCause     = enCause;                                          /* 设定SmCause                              */

    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* Nsapi值为0xFF                            */
        pModRejMsg->bitOpNsapi = 0;                                             /* 设为不存在                               */
    }
    else
    {
        pModRejMsg->bitOpNsapi = 1;                                             /* 设为存在                                 */

        pModRejMsg->ucNsapi = g_CrMapToNsapi[ucCr]+SM_NSAPI_OFFSET;             /* 记录Nsapi                                */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pModRejMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpModifyRej:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpActSecCnf
  Function:    作成和发送TAFSM_PDP_ACTIVATE_SEC_CNF消息
  Input:       SM_NW_MSG_STRU   *pMsgIe         收到的消息
               VOS_UINT8            ucCnxtIndex     Context索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.10   新规作成
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpActSecCnf(
    SM_NW_MSG_STRU                     *pMsgIe,                                 /* 收到的消息                               */
    VOS_UINT8                           ucCnxtIndex                             /* Context索引                              */
)
{
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pActSecCnfMsg = VOS_NULL_PTR;           /* 定义TAF结构指针                          */
    VOS_UINT8                 ucCr;

    if (ucCnxtIndex >= SM_MAX_NSAPI_NUM)
    {
        return;
    }

    pActSecCnfMsg = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_SEC_CNF_STRU));
    if ( VOS_NULL_PTR == pActSecCnfMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActSecCnf:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pActSecCnfMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_SEC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pActSecCnfMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActSecCnfMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActSecCnfMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_SEC_CNF;

    ucCr = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;
    pActSecCnfMsg->ucConnectId = ucCr;                                          /* 设定CR                                   */

    pActSecCnfMsg->stNegotiatedQos.ulQosLen = pMsgIe->Qos.ucLen;                /* 存储NegotiatedQos长度                    */

    SM_MemCpy(pActSecCnfMsg->stNegotiatedQos.aucQos,
              pMsgIe->Qos.pValue,
              ( VOS_UINT32 )pMsgIe->Qos.ucLen);                                 /* 存储NegotiatedQos内容                    */

    pActSecCnfMsg->bitOpNsapi = 1;                                              /* 设为存在                                 */

    pActSecCnfMsg->ucNsapi = (ucCnxtIndex + SM_NSAPI_OFFSET);                   /* 记录Nsapi                                */

    if( 0 == pMsgIe->Pfi.ucLen )
    {                                                                           /* PacketFlowId长度为0                      */
        pActSecCnfMsg->bitOpPacketFlowId = 0;                                   /* 设为不存在                               */
    }
    else
    {
        pActSecCnfMsg->bitOpPacketFlowId = 1;                                   /* 设为存在                                 */

        pActSecCnfMsg->stPacketFlowId.ulPFILen = pMsgIe->Pfi.ucLen;             /* 记录PacketFlowId长度                     */

        SM_MemCpy(&pActSecCnfMsg->stPacketFlowId.ucPacketFlowId,
                  pMsgIe->Pfi.pValue,
                  (VOS_UINT32)pMsgIe->Pfi.ucLen);                               /* 记录PacketFlowId内容                     */
    }

    /*SAPI*/
    if (g_aucSapi[0][0])
    {
        pActSecCnfMsg->bitOpSapi = 1;
        pActSecCnfMsg->ucSapi    = g_aucSapi[0][1];
        g_aucSapi[0][0] = 0;
    }
    else
    {
        pActSecCnfMsg->bitOpSapi = 0;
    }

    /*Radio Priority*/
    pActSecCnfMsg->bitOpRadioPriority = 1;
    pActSecCnfMsg->ucRadioPriority    = pMsgIe->ucRadioPri;
    pActSecCnfMsg->bitOpSpare         = 0;

    pActSecCnfMsg->stTransId.ucTiFlag = NAS_SM_GetPdpTiFlg(ucCnxtIndex);

    if (SM_TI_NET_ORG != NAS_SM_GetPdpTiFlg(ucCnxtIndex))
    {
        if (0x80 == (NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x80))
        {
            pActSecCnfMsg->stTransId.ucTiValue
                = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x7F;
        }
        else
        {
            pActSecCnfMsg->stTransId.ucTiValue
                = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x07;
        }
    }
    else
    {
        pActSecCnfMsg->stTransId.ucTiValue
            = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x7F;
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActSecCnfMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActSecCnf:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpActSecRej
  Function:    作成和发送TAFSM_PDP_ACTIVATE_SEC_REJ消息
  Input:       VOS_UINT8           ucCr              Call Reference
               VOS_UINT8           ucSmCause         网侧原因
               VOS_UINT8           ucMtCause         内部原因
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.10   新规作成
      2.日    期  : 2012年08月24日
        作    者  : m00217266
        修改内容  : 修改接口SmCause，添加原因值，删除MtCause
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpActSecRej(
                               VOS_UINT8                    ucCr,               /* Call Reference                           */
                               SM_TAF_CAUSE_ENUM_UINT16     enCause             /* 网侧原因                                 */
                            )
{
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU     *pActSecRejMsg = VOS_NULL_PTR;          /* 定义TAF结构指针                          */

    pActSecRejMsg = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_SEC_REJ_STRU));
    if ( VOS_NULL_PTR == pActSecRejMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActSecRej:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息 */
    PS_MEM_SET((VOS_CHAR*)pActSecRejMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_SEC_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写消息头 */
    pActSecRejMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActSecRejMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActSecRejMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_SEC_REJ;

    pActSecRejMsg->ucConnectId = ucCr;                                          /* 设定CR                                   */

    pActSecRejMsg->enCause = enCause;                                           /* 填写参数SmCause                          */

    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* Nsapi值为0xFF                            */
        pActSecRejMsg->bitOpNsapi = 0;                                          /* 设为不存在                               */
    }
    else
    {
        pActSecRejMsg->bitOpNsapi = 1;                                          /* 设为存在                                 */

        pActSecRejMsg->ucNsapi  = (g_CrMapToNsapi[ucCr] + SM_NSAPI_OFFSET);     /* 记录Nsapi                                */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActSecRejMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActSecRej:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndRabmSmActivateInd
  Function:    作成和发送ID_SM_RABM_ACTIVATE_IND消息
  Input:       VOS_UINT8          ucCntxtIndex           PDP context的索引
                              ucActMsgType:          #define RABMSM_ACT_MSG_1        1
                                                     #define RABMSM_ACT_MSG_2        2
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.11   新规作成
      2.  韩鲁峰   2006.01.11   在接口中增加深入参数ucActMsgType

  3.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM/SM原语接口中的动态内存改为静态数组
  4.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理

  5.日    期   : 2013年8月2日
    作    者   : A00165503
    修改内容   : DTS2013040906296: Secondary PDP下行数传无法找到关联的承载ID
*******************************************************************************/
VOS_VOID SM_SndRabmSmActivateInd(
    VOS_UINT8                           ucCntxtIndex,
    VOS_UINT8                           ucActMsgType
)
{
    RABMSM_ACTIVATE_IND_STRU           *pSndMsg = VOS_NULL_PTR;                 /* 发送消息指针                             */
    VOS_UINT8                           ucPDPAddrIndex;
    VOS_UINT8                           ucAddrIndex;

    ucAddrIndex = NAS_SM_GetPdpAddrIndex(ucCntxtIndex);

    pSndMsg = (RABMSM_ACTIVATE_IND_STRU *)
        PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
        sizeof(RABMSM_ACTIVATE_IND_STRU));                                      /* 申请内存                                 */
    if ( VOS_NULL_PTR == pSndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndRabmSmActivateInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息内容 */
    PS_MEM_SET((VOS_CHAR *)pSndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABMSM_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pSndMsg->ulNsapi = ucCntxtIndex + SM_NSAPI_OFFSET;                          /* 填写Nsapi                                */

    /* 填写Linked NSAPI */
    pSndMsg->ulLinkdNsapi = NAS_SM_GetPdpLinkedNsapi(ucAddrIndex);

    ucPDPAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;        /* 计算PDP Addr索引                         */
    if( 0x00 == (0x0F & (g_SmPdpAddrApn.aPdpAddrlist[ucPDPAddrIndex]
                          .PdpAddrInfo.aucAddrValue[0])) )
    {                                                                           /* PDP type organisation为0000              */
        pSndMsg->ulPppFlag = RABM_SM_PPP_PROT;                                  /* 采用PPP协议                              */
    }
    else
    {
        pSndMsg->ulPppFlag = RABM_SM_IP_PROT;                                   /* 采用IP协议                               */
    }

    pSndMsg->Qos.ulLength = g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength; /* 填写Qos长度                              */
    PS_MEM_CPY(pSndMsg->Qos.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);

    if (RABMSM_ACT_MSG_1 == ucActMsgType )
    {
        pSndMsg->ulActMsgType   = RABMSM_ACT_MSG_1;
    }
    else
    {
        pSndMsg->ulActMsgType   = RABMSM_ACT_MSG_2;
    }

    pSndMsg->MsgHeader.ulMsgName   = RABMSM_ACTIVATE_IND;
    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;


    PS_NAS_LOG1( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n ID_SM_RABM_ACTIVATE_IND: ulNsapi = %ld\r",
            (VOS_INT32)(pSndMsg->ulNsapi));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pSndMsg))                          /* 调用消息发送函数                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndRabmSmActivateInd():WARNING:SEND MSG FIAL");
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndRabmSmModifyInd
  Function:    作成和发送RABMSM_MODIFY_IND消息
  Input:       VOS_UINT8          ucCntxtIndex           PDP context的索引
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.11   新规作成

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM/SM原语接口中的动态内存改为静态数组
  3.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*******************************************************************************/
VOS_VOID SM_SndRabmSmModifyInd(
    VOS_UINT8                           ucCntxtIndex                            /* PDP context的索引                        */
)
{
    RABMSM_MODIFY_IND_STRU             *pSndMsg = VOS_NULL_PTR;                 /* 发送消息指针                             */

    pSndMsg = (RABMSM_MODIFY_IND_STRU *)
                PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
                sizeof(RABMSM_MODIFY_IND_STRU));                                /* 申请内存                                 */
    if ( VOS_NULL_PTR == pSndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndRabmSmModifyInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息内容 */
    PS_MEM_SET((VOS_CHAR *)pSndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABMSM_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pSndMsg->ulNsapi = ucCntxtIndex + SM_NSAPI_OFFSET;                          /* 填写Nsapi                                */
    pSndMsg->Qos.ulLength = g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength; /* 填写Qos长度                              */
    PS_MEM_CPY(pSndMsg->Qos.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);

    pSndMsg->MsgHeader.ulMsgName   = RABMSM_MODIFY_IND;
    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;

    PS_NAS_LOG1( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->RABM: RABMSM_MODIFY_IND: ulNsapi = %ld\r",
            (VOS_INT32)(pSndMsg->ulNsapi));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pSndMsg))                                          /* 调用消息发送函数                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndRabmSmModifyInd():WARNING:SEND MSG FIAL");
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndRabmSmDeactivateInd
  Function:    作成和发送RABMSM_DEACTIVATE_IND消息
  Input:       VOS_UINT8          ucCnt            去激活NSAPI的个数
               VOS_UINT8          *pucNsapi        Nsapi的列表
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.  张志勇      2003.12.11   新规作成
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
*******************************************************************************/
VOS_VOID SM_SndRabmSmDeactivateInd(
VOS_UINT8                               ucCnt,                                  /* 去激活NSAPI的个数                        */
VOS_UINT8                              *pucNsapi                                /* Nsapi的列表                              */
)
{
    RABMSM_DEACTIVATE_IND_STRU         *pSndMsg = VOS_NULL_PTR;                 /* 发送消息指针                             */
    VOS_UINT8                           i;                                      /* 循环变量                                 */

    pSndMsg = (RABMSM_DEACTIVATE_IND_STRU *)
                PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
                sizeof(RABMSM_DEACTIVATE_IND_STRU));                            /* 申请内存                                 */
    if ( VOS_NULL_PTR == pSndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndRabmSmDeactivateInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* 初始化消息内容 */
    PS_MEM_SET((VOS_CHAR *)pSndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABMSM_DEACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pSndMsg->ulDeactiveNum = ucCnt;                                             /* 填写去激活NSAPI的个数                    */
    for( i = 0; i < ucCnt; i++ )
    {                                                                           /* 遍历ucCnt                                */
        pSndMsg->aulNsapiList[i] = pucNsapi[i] + SM_NSAPI_OFFSET;               /* 填写Nsapi                                */
    }

    pSndMsg->MsgHeader.ulMsgName   = RABMSM_DEACTIVATE_IND;
    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pSndMsg))                                          /* 调用消息发送函数                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndRabmSmDeactivateInd():WARNING:SEND MSG FIAL");
    }

    PS_NAS_LOG(     WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "\n SM->RABM: RABMSM_DEACTIVATE_IND\r");

    return;
}

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndNwStatusMsg
  Function:    向网侧发送SM_status消息
  Input:       VOS_UINT8          ucTi
               VOS_UINT8          ucSmCause
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.  郑 伟   2003.12.11   新规作成
  2.  张志勇  2005.01.05   移植修改
  3.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  4.日    期  : 2013年03月13日
    作    者  : z00214637
    修改内容  : BodySAR项目

*******************************************************************************/
VOS_VOID SM_SndNwStatusMsg(
                       VOS_UINT8                    ucTi,                           /* TI                                       */
                       VOS_UINT8                    ucSmCause                       /* SM cause                                 */
                     )
{
    VOS_UINT8           *pTemp;                                                     /* 定义UCHAR型临时指针                      */
    VOS_UINT8           *pSendMsg;                                                  /* 定义UCHAR型指针                          */
    VOS_UINT32           ulSum;                                                      /* 定义计数器                               */
    VOS_UINT8            ucTiBak = ucTi;
    GMMSM_DATA_REQ_STRU    *pDataReq = SM_NULL;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                             /* 申请最大内存                             */
    if ( VOS_NULL_PTR == pTemp )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndNwStatusMsg:ERROR:Alloc mem fail!" );
        return;
    }

    pSendMsg = pTemp;                                                           /* 指向临时指针                             */
    ulSum = 0;                                                                  /* 计数器初始值置0                          */

    if(SM_FALSE == g_ucTiExt )
    {
        ucTi = ((ucTi & 0x80) >> 4) | (ucTi & 0x07);
    }
    if((TAF_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT != ucSmCause)
        && (TAF_SM_REJ_CAUSE_PROTOCOL_ERR != ucSmCause ))
    {
        if( 0xFF != g_TiMapToNsapi[ucTiBak] )
        {                                                                       /* 实体存在                                 */
            SM_ComGetTI(g_TiMapToNsapi[ucTiBak], &pTemp, &ulSum);                  /* 调用函数存储TI及TI Flag                  */
        }
        else
        {                                                                       /* 实体不存在                               */
            if( SM_FALSE == g_ucTiExt )
            {                                                                   /* TI占用1/2字节                            */
                /*为了把NET->MS方向的 TI_FLAG 转换成MS->NET方向的 TI_FLAG,
                对BIT8进行异或1*/
                if (TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)
                {
                    ucTi = ucTi ^ 0x08;
                }

                *pTemp = (ucTi << 4) & 0xF0;                                    /* 获得TI                                   */
                *pTemp = *pTemp | NAS_PD_SM;                                    /* 设定PD                                   */
                pTemp++;                                                        /* 更新指针偏移的长度                       */
                ulSum += 1;                                                     /* 计数器加1                                */
            }
            else
            {                                                                   /* TI占用3/2字节                            */
                /*为了把NET->MS方向的 TI_FLAG 转换成MS->NET方向的 TI_FLAG,
                对BIT8进行异或1*/
                if (TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)
                {
                    ucTi = ucTi ^ 0x80;
                }

                *pTemp = 0x70;                                                  /* 设置Ti扩展位                             */
                *pTemp = (VOS_UINT8)(*pTemp | (ucTi & 0x80));                       /* Ti Flag置1                               */
                *pTemp = *pTemp | NAS_PD_SM;                                    /* 设定PD                                   */
                pTemp++;                                                        /* 更新指针偏移的长度                       */
                *pTemp = ucTi|0x80;                                             /* 获得TI                                   */
                pTemp++;                                                        /* 更新指针偏移的长度                       */
                ulSum += 2;                                                     /* 计数器加2                                */
            }
        }
    }
    else
    {                                                                           /* 实体不存在                               */
        if( SM_FALSE == g_ucTiExt )
        {                                                                       /* TI占用1/2字节                            */
            /*为了把NET->MS方向的 TI_FLAG 转换成MS->NET方向的 TI_FLAG,
            对BIT8进行异或1*/
            ucTi = ucTi ^ 0x08;

            *pTemp = (ucTi << 4) & 0xF0;                                        /* 获得TI,Ti Flag置1                        */
            *pTemp = (*pTemp) | NAS_PD_SM;                                      /* 设定PD                                   */
            pTemp++;                                                            /* 更新指针偏移的长度                       */
            ulSum += 1;                                                         /* 计数器加1                                */
        }
        else
        {                                                                       /* TI占用3/2字节                            */
            /*为了把NET->MS方向的 TI_FLAG 转换成MS->NET方向的 TI_FLAG,
            对BIT8进行异或1*/
            ucTi = ucTi ^ 0x80;

            *pTemp = 0x70;                                                      /* 设置Ti扩展位                             */
            *pTemp = *pTemp | (ucTi & 0x80);                                    /* Ti Flag置1                               */
            *pTemp = (*pTemp) | NAS_PD_SM;                                      /* 设定PD                                   */
            pTemp++;                                                            /* 更新指针偏移的长度                       */
            *pTemp = ucTi | 0x80;                                               /* 获得TI                                   */
            pTemp++;                                                            /* 更新指针偏移的长度                       */
            ulSum += 2;                                                         /* 计数器加2                                */
        }
    }
    *pTemp = SM_STATUS;                                                         /* 添加消息类型，更新指针偏移的长度         */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */
    *pTemp = ucSmCause;                                                         /* Sm Cause                                 */
    pTemp++;                                                                    /* 更新指针偏移的长度                       */
    ulSum += 1;                                                                 /* 计数器加1                                */

    pDataReq = (GMMSM_DATA_REQ_STRU *)
                PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
                sizeof(GMMSM_DATA_REQ_STRU));
    if ( VOS_NULL_PTR == pDataReq )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndNwStatusMsg:ERROR:Alloc msg fail!" );
        SM_Free(pSendMsg);
        return;
    }

    pDataReq->MsgHeader.ulMsgName   = GMMSM_DATA_REQ;
    pDataReq->ulEstCause = GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL;

    pDataReq->SmMsg.ulNasMsgSize = ulSum;
    SM_MemCpy(pDataReq->SmMsg.aucNasMsg, pSendMsg, ulSum);
    pDataReq->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pDataReq->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pDataReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pDataReq->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;

    SM_ReportM2NOtaMsg(&(pDataReq->SmMsg));


    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pDataReq))                          /* 调用消息发送函数                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndNwStatusMsg():WARNING:SEND MSG FIAL");
    }

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "SM->NW: SM Status\r");

    SM_Free(pSendMsg);                                                          /* 释放内存                                 */
    return;
}
/*lint +e438 +e830*/

/*******************************************************************************
  Module:      SM_GetMostHighPri
  Function:    选择实体中的最高优先级的traffic class
  Input:       VOS_VOID
  NOTE:
  Return:      VOS_UINT8 ucPriority
  History:
  1.  张志勇      2003.12.11   新规作成

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : SM保存的QOS和APN由动态内存改为静态数组
*******************************************************************************/
VOS_UINT8 SM_GetMostHighPri(VOS_VOID)
{
    VOS_UINT8   i;
    VOS_UINT8   ucPriority;
    VOS_UINT8   ucTempPri;

    ucPriority = GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL;                            /* 初始化优先级                             */
    for(i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if (SM_PDP_INACTIVE != g_SmEntity.aPdpCntxtList[i].ucState)
        {
            ucTempPri = (g_SmEntity.aPdpCntxtList[i].QoS.aucQosValue[3] & NAS_SM_QOS_TRAFFIC_CLASS_MASK) >> 5;
            if(0 != ucTempPri)
            {                                                                   /* 不是保留数或Subscribed Traffic Class     */
                if(ucPriority > ucTempPri)
                {                                                               /* 优先级高于初始的优先级                   */
                    ucPriority = ucTempPri;
                }
            }
        }
    }

#if(PS_UE_REL_VER >= PS_PTL_VER_R6)
    if (NAS_Common_Get_Supported_3GPP_Version(SM_MM_COM_SRVDOMAIN_PS) >= PS_PTL_VER_R6)
    {
        if (GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL == ucPriority)
        {
            ucPriority = GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL;
        }
    }
#endif

    return ucPriority;
}


/*******************************************************************************
  Module:      SM_GetCr
  Function:    获取CR参数
  Input:       VOS_UINT8 ucNsapi
  Output:      VOS_UINT8 *pucCr
  NOTE:
  Return:      VOS_OK
               VOS_ERR
  History:
      1.  L47619      2008.03.18   新规作成
*******************************************************************************/
VOS_UINT32   SM_GetCr(VOS_UINT8 ucNsapi, VOS_UINT8 *pucCr)
{
    if(VOS_NULL_PTR == pucCr)
    {
        return VOS_ERR;
    }

    if((SM_NSAPI_MIN_VALUE > ucNsapi) || (SM_NSAPI_MAX_VALUE < ucNsapi))
    {
        return VOS_ERR;
    }

    if(SM_PDP_ACTIVE != g_SmEntity.aPdpCntxtList[ucNsapi - SM_NSAPI_OFFSET].ucState)
    {
        return VOS_ERR;
    }

    *pucCr = g_SmEntity.aPdpCntxtList[ucNsapi - SM_NSAPI_OFFSET].ucCr;
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : SM_FillMsgData
 功能描述  :
 输入参数  : VOS_VOID *pMsgContent
             VOS_VOID *pData
             VOS_UINT32 ulLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月8日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID SM_FillMsgData(VOS_VOID *pMsgContent,VOS_VOID *pData,VOS_UINT32 ulLen)
{
    SM_MemCpy(pMsgContent, pData, ulLen);
}


/*******************************************************************************
  Module:      SM_IsActivePending
  Function:    PDP激活流程中，SM会向RABM发送两条ID_SM_RABM_ACTIVATE_IND_STRU消息，
               分别在发起激活和激活成功的时候发送。但有可能会遇到如下场景:
               SM向RABM发送了第一条ID_SM_RABM_ACTIVATE_IND_STRU后，状态处于
               SM_PDP_ACTIVE_PENDING态，此时发生异系统流程(正常异系统流程或丢网)，
               则RABM在切入另一个系统后建立状态机时，需要恢复为接收到第一条
               ID_SM_RABM_ACTIVATE_IND_STRU的状态，此时RABM则通过该API来判断在前一个
               系统中是否接收到了第一条ID_SM_RABM_ACTIVATE_IND_STRU
  Input:       VOS_UINT8 ucNsapi
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_OK
               VOS_ERR
  History:
      1.  L47619      2009.03.16   新规作成
*******************************************************************************/
VOS_UINT32   SM_IsActivePending(VOS_UINT8 ucNsapi)
{
    if((SM_NSAPI_MIN_VALUE > ucNsapi) || (SM_NSAPI_MAX_VALUE < ucNsapi))
    {
        return VOS_ERR;
    }

    if(SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[ucNsapi - SM_NSAPI_OFFSET].ucState)
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}


/*******************************************************************************
  Module:      SM_RabmGetFirstActIndMsgInfo
  Function:    PDP激活流程中，SM会向RABM发送两条ID_SM_RABM_ACTIVATE_IND_STRU消息，
               分别在发起激活和激活成功的时候发送。但有可能会遇到如下场景:
               SM向RABM发送了第一条ID_SM_RABM_ACTIVATE_IND_STRU后，状态处于
               SM_PDP_ACTIVE_PENDING态，此时发生异系统流程(正常异系统流程或丢网)，
               则RABM在切入另一个系统后建立状态机时，需要恢复为接收到第一条
               ID_SM_RABM_ACTIVATE_IND_STRU的状态，此时RABM则通过该API来进行状态恢复
               时所需信息的获取。
  Input:       VOS_UINT8 ucNsapi
               RABMSM_ACTIVATE_IND_STRU *pActivateInd;
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_OK
               VOS_ERR
  History:
      1.  L47619      2009.03.16   新规作成

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM/SM原语接口中的动态内存改为静态数组
*******************************************************************************/
VOS_UINT32   SM_RabmGetFirstActIndMsgInfo(
    VOS_UINT8                           ucNsapi,
    RABMSM_ACTIVATE_IND_STRU           *pActivateInd
)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucPDPAddrIndex;

    if (VOS_NULL_PTR == pActivateInd)
    {
        return VOS_ERR;
    }

    if ((SM_NSAPI_MIN_VALUE > ucNsapi) || (SM_NSAPI_MAX_VALUE < ucNsapi))
    {
        return VOS_ERR;
    }

    /* 初始化消息内容 */
    PS_MEM_SET((VOS_CHAR *)pActivateInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABMSM_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    ucCntxtIndex = ucNsapi - SM_NSAPI_OFFSET;

    ucPDPAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;
    if (0x00 == (0x0F & (g_SmPdpAddrApn.aPdpAddrlist[ucPDPAddrIndex].PdpAddrInfo.aucAddrValue[0])))
    {
        pActivateInd->ulPppFlag = RABM_SM_PPP_PROT;
    }
    else
    {
        pActivateInd->ulPppFlag = RABM_SM_IP_PROT;
    }

    pActivateInd->Qos.ulLength = g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength;

    PS_MEM_CPY(pActivateInd->Qos.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : NAS_SM_IsPdpCntxtValid
 功能描述  : 检查实体上下文是否有效
 输入参数  : pstPdpCntxt --- 实体上下文
 输出参数  : 无
 返 回 值  : PS_TRUE/PS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_SM_IsPdpCntxtValid(NAS_SM_PDP_CONTEXT_INFO_STRU *pstPdpCntxt)
{
    if (VOS_NULL_PTR == pstPdpCntxt)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*******************************************************************************
  Module:      SM_SndTafMsg
  Function:    将SM待发送的空口消息发送给GMM
  Input:       VOS_VOID
  NOTE:
  Return:      VOS_UINT8
  History:
      1.  张志勇      2003.12.11   新规作成
      2.  张志勇   2005.03.17   NAS_IT_BUG_004
	  3.日    期   : 2012年12月11日
	    作    者   : l00167671
	    修改内容   : DTS2012121802573, TQE清理
      4.日    期  : 2013年03月13日
        作    者  : z00214637
        修改内容  : BodySAR项目

*******************************************************************************/
VOS_VOID SM_SndTafMsg(
                  VOS_UINT8             *pSendMsg,                                  /* 消息内容的临时指针                       */
                  VOS_UINT8             ucSMIndex,                                  /* SM索引                                   */
                  VOS_UINT32             ulSum,                                      /* 消息的长度                               */
                  VOS_UINT8             ucCause,                                    /* rrc连接建立原因                          */
                  VOS_UINT8             ucSaveFlg
                  )
{
    GMMSM_DATA_REQ_STRU    *pDataReq = SM_NULL;                                 /* 消息指针                                 */

    VOS_UINT32                   Messagelen;
    if(ulSum > 4)
    {
        pDataReq = (GMMSM_DATA_REQ_STRU *)
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
            (sizeof(GMMSM_DATA_REQ_STRU) + ulSum) - 4);
        if (VOS_NULL_PTR == pDataReq)
        {
            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "\n SM_SndTafMsg : Sm_AllocMsg FAIL 1 !!\r");
            return;
        }

        Messagelen= (sizeof(GMMSM_DATA_REQ_STRU) + ulSum) - 4;
    }
    else
    {
        pDataReq = (GMMSM_DATA_REQ_STRU *)
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
            sizeof(GMMSM_DATA_REQ_STRU));
        if (VOS_NULL_PTR == pDataReq)
        {
            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "\n SM_SndTafMsg : Sm_AllocMsg FAIL 2 !!\r");
            return;
        }

        Messagelen = sizeof(GMMSM_DATA_REQ_STRU);
    }

    pDataReq->MsgHeader.ulMsgName   = GMMSM_DATA_REQ;
    pDataReq->SmMsg.ulNasMsgSize    = ulSum;
    pDataReq->ulEstCause = ucCause;

    SM_FillMsgData(pDataReq->SmMsg.aucNasMsg, pSendMsg, ulSum);

    SM_Free(pSendMsg);

    pDataReq->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pDataReq->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pDataReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pDataReq->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;


    if(SM_TRUE == ucSaveFlg)
    {
        g_SmEntity.aPdpCntxtList[ucSMIndex].pHoldSndMsg =(VOS_VOID *)
            SM_Malloc(Messagelen);
        SM_MemCpy(g_SmEntity.aPdpCntxtList[ucSMIndex].pHoldSndMsg,pDataReq,
            Messagelen);                                     /* 备份发送的消息                           */
        g_SmEntity.aPdpCntxtList[ucSMIndex].ulHoldLen =
            Messagelen;                                      /* 备份发送的消息长度                       */

    }
    SM_ReportM2NOtaMsg(&(pDataReq->SmMsg));


    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pDataReq))                          /* 调用消息发送函数                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndTafMsg():WARNING:SEND MSG FIAL");
    }

    return;
}
/*******************************************************************************
  Module:      SM_SndStatusMsg
  Function:    向AGENT及网侧发送SM_status消息
  Input:       VOS_VOID
               Ti:  UCHAR类型,
                    BIT8        -  Ti_Flag, NET->MS的消息中的FLAG
                    BIT7~BIT1   -  Ti 值
  NOTE:
  Return:      VOS_VOID
  History:
  1. 张志勇    2005.01.10   新规作成
  2. 韩鲁峰    2005-04-19   增加函数头中对输入参数Ti的说明

  3.日    期   : 2014年7月22日
    作    者   : A00165503
    修改内容   : DTS2014071601162: SM_STATUS信令流程增机保护
  4.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_SndStatusMsg( VOS_UINT8 ucTi, VOS_UINT8  ucSmCause )
{
    NAS_SM_BeginSession();

    SM_SndNwStatusMsg(ucTi, ucSmCause);

    NAS_SM_EndSession();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_SndGmmEstablishReq
 功能描述  : 发送GMMSM_ESTABLISH_REQ消息至GMM
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_SM_SndGmmEstablishReq(VOS_VOID)
{
    GMMSM_ESTABLISH_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstMsg = (GMMSM_ESTABLISH_REQ_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                            sizeof(GMMSM_ESTABLISH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmEstablishReq: Alloc MSG failed.");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* 填写消息头 */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_ESTABLISH_REQ);

    /* 发送消息 */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_SndGmmPdpDeactivatedInd
 功能描述  : 发送GMMSM_PDP_DEACTIVATED_IND消息至GMM
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月9日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 封装消息接口
*****************************************************************************/
VOS_VOID NAS_SM_SndGmmPdpDeactivatedInd(VOS_VOID)
{
    GMMSM_PDP_DEACTIVATED_IND_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* 申请OSA消息 */
    pstMsg = (GMMSM_PDP_DEACTIVATED_IND_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                                    sizeof(GMMSM_PDP_DEACTIVATED_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmPdpDeactivatedInd: Alloc MSG failed.");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* 填写消息头 */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_PDP_DEACTIVATED_IND);

    /* 填写消息内容 */
    for (ulIndex = 0; ulIndex < SM_MAX_NSAPI_NUM; ulIndex++)
    {
        if ((SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ulIndex].ucState)
         || (SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[ulIndex].ucState)
         || (SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ulIndex].ucState))
        {
            pstMsg->ulPdpContextStatus
                |= (VOS_UINT32)0x00000001 << (ulIndex + SM_NSAPI_OFFSET);
        }
    }

    /* 发送消息 */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_SndGmmAbortReq
 功能描述  : 发送GMMSM_ABORT_REQ消息至GMM, 清除SM缓存
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 封装消息接口
*****************************************************************************/
VOS_VOID NAS_SM_SndGmmAbortReq(VOS_VOID)
{
    GMMSM_ABORT_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstMsg = (GMMSM_ABORT_REQ_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                        sizeof(GMMSM_ABORT_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmAbortReq: Alloc MSG failed.");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* 填写消息头 */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_ABORT_REQ);

    /* 发送消息 */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_SndGmmPdpModifyInd
 功能描述  : 发送GMMSM_PDP_MODIFY_IND消息给GMM
 输入参数  : ucNsapi - 取值范围[5, 15]
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月28日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 封装消息接口
*****************************************************************************/
VOS_VOID NAS_SM_SndGmmPdpModifyInd(VOS_UINT8 ucNsapi)
{
    GMMSM_PDP_MODIFY_IND_STRU              *pstMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstMsg = (GMMSM_PDP_MODIFY_IND_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                            sizeof(GMMSM_PDP_MODIFY_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmPdpModifyInd: Alloc MSG failed.");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* 填写消息头 */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_PDP_MODIFY_IND);

    /* 填写消息内容 */
    pstMsg->ucNsapi = ucNsapi;

    /* 发送消息 */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}


/*****************************************************************************
 函 数 名  : NAS_SM_SndGmmPdpStatusInd
 功能描述  : 发送GMMSM_PDP_STATUS_IND原语, 增加SM_PDP_ACTIVE_PENDING条件
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月9日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 封装消息接口

  3.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*****************************************************************************/
VOS_VOID NAS_SM_SndGmmPdpStatusInd(VOS_VOID)
{
    GMMSM_PDP_STATUS_IND_STRU          *pstMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucState;
    VOS_UINT8                           i;

    /* 申请OSA消息 */
    pstMsg = (GMMSM_PDP_STATUS_IND_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                            sizeof(GMMSM_PDP_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmPdpStatusInd: Alloc MSG failed.");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* 填写消息头 */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_PDP_STATUS_IND);

    /* 填写消息内容 */
    for ( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        ucState = NAS_SM_GET_PDP_STATE(i);

        if ( (SM_PDP_MODIFY_PENDING == ucState)
          || (SM_PDP_ACTIVE == ucState)
          || (SM_PDP_NW_MODIFY == ucState) )
        {
            pstMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_ACTIVE;
        }
        else if (SM_PDP_ACTIVE_PENDING == ucState)
        {
            pstMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_ACTIVE_PENDING;
        }
        else if (SM_PDP_INACTIVE_PENDING == ucState)
        {
            pstMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_INACTIVE_PENDING;
        }
        else
        {
            pstMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_INACTIVE;
        }
    }

    /* 发送消息 */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_SndPdpCntxtHoldMsg
 功能描述  : 发送实体上下文中保存的消息
 输入参数  : ucCntxtId --- 实体索引(有效性由调用者保证)
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_SM_SndPdpCntxtHoldMsg(NAS_SM_PDP_CONTEXT_INFO_STRU *pstPdpCntxt)
{
    MSG_HEADER_STRU                    *pstMsg = VOS_NULL_PTR;

    /* 检查上下文 */
    if (PS_FALSE == NAS_SM_IsPdpCntxtValid(pstPdpCntxt))
    {
        NAS_SM_WARN_LOG("NAS_SM_SndPdpCntxtHoldMsg: PDP context is not valid.");
        return;
    }

    /* 申请OSA消息 */
    pstMsg = (MSG_HEADER_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(pstPdpCntxt->ulHoldLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndPdpCntxtHoldMsg: Alloc MSG failed.");
        return;
    }

    /* 复制消息 */
    PS_MEM_CPY(pstMsg, pstPdpCntxt->pHoldSndMsg, pstPdpCntxt->ulHoldLen);

    /* 发送消息 */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_SndGmmBeginSessionNotify
 功能描述  : 发送GMMSM_BEGIN_SESSION_NOTIFY原语
 输入参数  : enSessionType --- 会话类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_SM_SndGmmBeginSessionNotify(GMMSM_SESSION_TYPE_ENUM_UINT8 enSessionType)
{
    GMMSM_BEGIN_SESSION_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstMsg = (GMMSM_BEGIN_SESSION_NOTIFY_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                                    sizeof(GMMSM_BEGIN_SESSION_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmBeginSessionNotify: Alloc MSG failed.");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* 填写消息头 */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_BEGIN_SESSION_NOTIFY);

    /* 填写消息内容 */
    pstMsg->enSessionType = enSessionType;

    /* 发送消息 */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_SndGmmEndSessionNotify
 功能描述  : 发送GMMSM_END_SESSION_NOTIFY原语
 输入参数  : enSessionType --- 会话类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_SM_SndGmmEndSessionNotify(GMMSM_SESSION_TYPE_ENUM_UINT8 enSessionType)
{
    GMMSM_END_SESSION_NOTIFY_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请OSA消息 */
    pstMsg = (GMMSM_END_SESSION_NOTIFY_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                                    sizeof(GMMSM_END_SESSION_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmEndSessionNotify: Alloc MSG failed.");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* 填写消息头 */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_END_SESSION_NOTIFY);

    /* 填写消息内容 */
    pstMsg->enSessionType = enSessionType;

    /* 发送消息 */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}



/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

