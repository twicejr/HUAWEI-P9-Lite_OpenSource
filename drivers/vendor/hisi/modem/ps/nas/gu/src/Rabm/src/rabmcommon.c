/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : RabmCommon.c
  Description  : Rabm公共处理
  Function List:
                 1.  RABM_SaveData
                 2.  RABM_ComSaveRabPara
                 3.  RABM_ComRlsRabReource
                 4.  RABM_RelSaveData
                 5.  Rabm_TcInfSave
                 6.  RABM_TcInfRls
                 7.  RABM_TcRbStatus

  History:
      1. 张志勇 2003.12.08   新规作成
      2. L47619 2005.11.26   问题单:A32D00767
      3. L47619 2005.12.22   问题单:A32D00885
      4. L47619 2006.01.10   问题单:A32D01571
      5. L47619 2006.06.26   问题单:A32D05709
      6. L47619 2007.05.30   问题单:A32D11248
      7. L47619 2007.08.15   问题单:AR12D01371
*******************************************************************************/
#include "rabminclude.h"


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
#define    THIS_FILE_ID        PS_FILE_ID_RABM_COMMON_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/



/*******************************************************************************
  Module:   RABM_SaveData
  Function: 缓存数据
  Input:    RABM_DATA_SAVE_STRU    *pSaveDataPtr     缓存数据的链表指针
            VOS_VOID                   *pMsg             被缓存的数据
            VOS_UINT8                  ucMsgType         消息类型
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. 张志勇      2003.12.11   新规作成
*******************************************************************************/
VOS_VOID RABM_SaveData(
                   RABM_DATA_SAVE_STRU  *pSaveDataPtr,                          /* 缓存数据的链表指针                       */
                   VOS_VOID  *pMsg,                                                 /* 被缓存的数据                             */
                   VOS_UINT8 ucMsgType                                              /* 消息类型                                 */
                   )
{
    RABM_DATA_LINK_STRU  *pTemp1 = RABM_POINTER_NULL;
    RABM_DATA_LINK_STRU  *pTemp2 = RABM_POINTER_NULL;

    VOS_VOID           *pSaveMsg = RABM_POINTER_NULL;
    VOS_UINT32         ulDataLen = 0;

    if ( RABM_UPLINK == ucMsgType )
    {                                                                           /* 获得上行数据的长度                       */
        ulDataLen = ((TAFRABM_PS_DATA_REQ_STRU *)pMsg)->MsgHeader.ulLength + VOS_MSG_HEAD_LENGTH;
    }
    else
    {                                                                           /* 获得下行数据的长度                       */
        ulDataLen = sizeof(PDCP_RABM_DATA_BUF_STRU);
    }

    pSaveMsg = RABM_Malloc(ulDataLen);
    if(VOS_NULL_PTR == pSaveMsg)
    {
        return;
    }

    PS_NAS_MEM_CPY(pSaveMsg, pMsg, ulDataLen);                                     /* 获得数据                                 */


    if(0 == pSaveDataPtr->ucNum)
    {                                                                           /* 是链表中的第一个数据                     */
        pSaveDataPtr->Data.pData = pSaveMsg;                                    /* 存储数据消息                             */
        pSaveDataPtr->Data.pNxt = RABM_POINTER_NULL;                            /* 初始化链表指针                           */
    }
    else if(1 == pSaveDataPtr->ucNum)
    {
        pSaveDataPtr->Data.pNxt = (RABM_DATA_LINK_STRU *)
                                       RABM_Malloc(sizeof(RABM_DATA_LINK_STRU));
        pSaveDataPtr->Data.pNxt->pData = pSaveMsg;                              /* 存储数据消息                             */
        pSaveDataPtr->Data.pNxt->pNxt = RABM_POINTER_NULL;
    }
    else
    {
        pTemp1 = pSaveDataPtr->Data.pNxt;
        pTemp2 = pTemp1;

        if(0xff != pSaveDataPtr->ucNum)
        {
            for( ; ; )
            {                                                                   /* 查找链表尾                               */
                if(RABM_POINTER_NULL != pTemp1->pNxt)
                {
                    pTemp1 = pTemp2->pNxt;
                }
                else
                {
                    break;
                }
                pTemp2 = pTemp1;
            }
            pTemp1->pNxt = (RABM_DATA_LINK_STRU *)
                RABM_Malloc(sizeof(RABM_DATA_LINK_STRU));
            pTemp1->pNxt->pData = pSaveMsg;                                     /* 存储数据消息                             */
            pTemp1->pNxt->pNxt = RABM_POINTER_NULL;                             /* 初始化链表指针                           */
        }
        else
        {
            /*释放上行数据的零拷贝内存*/
            if (RABM_UPLINK == ucMsgType)
            {
                TTF_MemFree(WUEPS_PID_RABM, ((TAFRABM_PS_DATA_REQ_STRU *)pMsg)->pData);
            }

            RABM_Free(pSaveMsg);
            return;
        }
    }
    pSaveDataPtr->ucNum++;                                                      /* 更新缓存的数据个数                       */
}

/*******************************************************************************
  Module:   RABM_ComSaveRabPara
  Function: 存储RAB的参数
  Input:    RRRABM_RAB_IND_STRU *pMsg           目前处理的消息
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. 张志勇      2003.12.11   新规作成
      2. 张志勇   2005.01.07   移植修改
      3. 张志勇   2005.03.30   NAS_IT_BUG_41
      4. L47619   2006.01.10   问题单:A32D01571
      5. L47619   2006.06.26   问题单:A32D05709
      6. L47619   2007.08.09   问题单:AR12D01322
      7. L47619   2007.08.15   问题单:AR12D01371

  8.日    期   : 2012年3月24日
    作    者   : A00165503
    修改内容   : DTS2012032305582: CMW500环回建立失败, RABID在环回模式下取值
                 范围检查过于严格
  9.日    期   : 2013年04月12日
    作    者   : l65478
    修改内容   : DTS2013031901654:彩信并发发送失败
 10.日    期   : 2013年8月29日
    作    者   : j00174725
    修改内容   : clean coverity
*******************************************************************************/
VOS_VOID RABM_ComSaveRabPara(
                         RRRABM_RAB_IND_STRU  *pMsg                             /* 目前处理的消息                           */
                         )
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT8                           ucEntId = 0xff;
    VOS_UINT8                           ucTcFlg = RABM_FALSE;
    VOS_UINT16                          k;
    VOS_UINT8                           ucChgMask;

    for(i = 0; i < pMsg->ulRabCnt; i++)
    {
        if(RABM_CN_PS == pMsg->aRabInfo[i].ulCnDomainId)
        {                                                                       /* 是PS域的RAB                              */
            if ( VOS_TRUE == gRabm2GTo3GDataResume )
            {
                /*复位2G向3G切换使用的数传恢复标志:*/
                gRabm2GTo3GDataResume = VOS_FALSE;

                /*向PDCP发送2G向3G切换的数传恢复指示:*/
                NAS_RabmSndPdcpDataResumeInd(pMsg);
            }

            if ( (RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
              && ((pMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET) )
            {
                ucEntId = (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId & 0x0f);
            }
            else
            {
                if ((pMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET)
                {
                   continue;
                }

                ucEntId = (VOS_UINT8)
                ((pMsg->aRabInfo[i].ulRabId & 0x0f) - RABM_NSAPI_OFFSET);       /* 获得PS域的RABM实体ID                     */
            }

            switch(g_aRabmPsEnt[ucEntId].ucState)
            {                                                                   /* 根据实体状态作相应处理                   */
            case RABM_NULL:
                break;
            case RABM_NSAPI_ACTIVE_PENDING:
                if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
                {
                    Rabm_TcInfSave(pMsg, i);
                }
                RABM_SetWState(ucEntId, RABM_ACT_PENDING_WITH_RAB);             /* 改变实体的状态                           */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComSaveRabPara:NORMAL:RABM state: RABM_NSAPI_ACTIVE_PENDING ==> RABM_ACT_PENDING_WITH_RAB");
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* 保存RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* 保存RB的个数                             */

                for ( j = 0 ; j < g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);                  /* 保存RB ID                                */

                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* 保存RB 的传输模式 */
                }

                /*此时RAB_MAP表的实体并未创建，无需更新RAB_MAP中的ucAsId*/
                break;
            case RABM_NSAPI_ACTIVE_NO_RAB:
                if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
                {
                    Rabm_TcInfSave(pMsg, i);
                }
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* 保存RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* 保存RB的个数                             */

                for ( j = 0 ; j < g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);                  /* 保存RB ID                                */
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* 保存RB 的传输模式 */
                }


                RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_WITH_RAB);            /* 改变实体的状态                           */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComSaveRabPara:NORMAL:RABM state: RABM_NSAPI_ACTIVE_NO_RAB ==> RABM_NSAPI_ACTIVE_WITH_RAB");

                /*更新RAB_MAP表中的ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;
                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);

                if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(ucEntId))
                {
                    /* 停止RB建立保护定时器 */
                    NAS_RABM_StopReestRabPendingTmr(ucEntId + RABM_NSAPI_OFFSET);

                    /* 清除RABM实体的重建标识 */
                    NAS_RABM_ClearWPsEntRabReestFlg(ucEntId);

                    g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_FALSE;
                    RABM_SaveDataProcess(ucEntId, RABM_UPLINK);                 /* 处理缓存的上行数据                       */

                    /* 通知CDS发送缓存数据 */
                    NAS_RABM_SndCdsSendBuffDataInd(ucEntId + RABM_NSAPI_OFFSET,
                                                   CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
                }
                break;
            case RABM_ACT_PENDING_WITH_RAB:
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* 保存RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* 保存RB的个数                             */

                for ( j = 0 ; j < g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                            (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);              /* 保存RB ID                                */
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* 保存RB 的传输模式 */
                }

                /*此时RAB_MAP表的实体并未创建，无需更新RAB_MAP中的ucAsId*/
                break;
            case RABM_NSAPI_ACTIVE_WITH_RAB:
            case RABM_DATA_TRANSFER_STOP:
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* 保存RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* 保存RB的个数                             */

                for ( j = 0 ; j < g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                            (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);              /* 保存RB ID                                */
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* 保存RB 的传输模式 */
                }

                /*更新RAB_MAP表中的ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;
                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);
                break;
            case RABM_TC_STATE_NULL:
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* 保存RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* 保存RB的个数                             */

                for ( j = 0 ; j < pMsg->aRabInfo[i].ulRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);              /* 保存RB ID                                */
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* 保存RB 的传输模式 */
                }
                Rabm_TcInfSave(pMsg, i);
                break;
            default:
                break;
            }

            if(RABM_NSAPI_ACTIVE_WITH_RAB == g_aRabmPsEnt[ucEntId].ucState)
            {
                if(0 != g_aRabmPsEnt[ucEntId].DlDataSave.ucNum)
                {                                                               /* 有缓存的下行数据                         */
                    RABM_SaveDataProcess(ucEntId,RABM_DOWNLINK);                /* 处理缓存的下行数据                       */
                }
            }
        }
        else
        {
            if( NAS_RRC_RAB_SETUP_SUCCESS == pMsg->ulRabChangeType )
            {

                ucTcFlg = RABM_FALSE;
                for( j = 0; j < RABM_CS_MAX_ENT_NUM; j++ )
                {
                    for( k = 0; k < 256; k++ )
                    {
                        if ( g_aucSiMapEnt[k] == j )
                        {
                            break;
                        }
                    }

                    if( k < 256 )
                    {
                        continue;
                    }
                    if( RABM_NULL == g_aRabmCsEnt[j].ucState)
                    {
                        g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId] = j;
                        break;
                    }
                    else if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
                    {
                        Rabm_TcInfSave(pMsg, i);
                        ucTcFlg = RABM_TRUE;
                        break;
                    }
                    else
                    {
                    }
                }
                if(RABM_TRUE == ucTcFlg)
                {
                    g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId] = j;
                    ucEntId = g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId];
                    g_aRabmCsEnt[ucEntId].RabInfo.ucRabId = (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);
                    g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum = (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);
                    for(j = 0; j < pMsg->aRabInfo[i].ulRbNum; j++)
                    {
                        g_aRabmCsEnt[ucEntId].RabInfo.aucRbId[j] = (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);
                        g_aRabmCsEnt[ucEntId].RabInfo.aucRbTxMode[j] = (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);
                    }
                    continue;
                }
                if( RABM_CS_MAX_ENT_NUM == j )
                {
                    PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "RABM_ComSaveRabPara:WARNING:Exceed RABM_CS_MAX_ENT_NUM!");
                    return;
                }
            }
            ucEntId = g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId];

            for(j = 0; j < pMsg->aRabInfo[i].ulRbNum; j++)
            {
                g_aRabmCsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);
            }
            switch(g_aRabmCsEnt[ucEntId].ucState)
            {
            case RABM_NULL:
                g_aRabmCsEnt[ucEntId].ucState = RABM_SI_ACTIVE_WITH_RAB;
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComSaveRabPara:NORMAL:RABM state: RABM_NULL ==> RABM_SI_ACTIVE_WITH_RAB");
                g_aRabmCsEnt[ucEntId].ucSi = (VOS_UINT8)pMsg->aRabInfo[i].ulRabId;  /* 存储SI                                   */

                RABM_SndCcSyncInd(RABMCC_RAB_ACTIVE, pMsg->aRabInfo[i].ulRabId);/* 通知cc                                   */

                RABM_SndCallSyncInd(RABMCALL_RAB_ACTIVE, &pMsg->aRabInfo[i]);   /* 通知CALL */
                g_aRabmCsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* 保存RAB ID                               */
                g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* 保存RB的个数                             */
                for(j = 0; j < g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum; j++)
                {                                                               /* 保存RB ID                                */
                    g_aRabmCsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);
                }
                break;

            case RABM_SI_ACTIVE_WITH_RAB:
                g_aRabmCsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* 保存RAB ID                               */
                g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* 保存RB的个数                             */
                for(j = 0; j < g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum; j++)
                {                                                               /* 保存RB ID                                */
                    g_aRabmCsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);
                }
                break;
            default:
                break;
            }
        }
    }

    return;
}

/*******************************************************************************
  Module:   RABM_ComRlsRabReource
  Function: 释放RAB的参数
  Input:    RRRABM_RAB_IND_STRU *pMsg           目前处理的消息
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. 张志勇      2003.12.11   新规作成
      2. L47619      2007.08.09   问题单:AR12D01322

  3.日    期   : 2012年3月24日
    作    者   : A00165503
    修改内容   : DTS2012032305582: CMW500环回建立失败, RABID在环回模式下取值
                 范围检查过于严格

  4.日    期   : 2012年6月15日
    作    者   : A00165503
    修改内容   : DTS2012061401093: 多承载业务时, RABM处理RB释放的逻辑错误,
                 有可能导致业务中断

  5.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM保存的QOS由动态内存改为静态数组
  6.日    期   : 2013年8月29日
    作    者   : j00174725
    修改内容   : clean coverity
*******************************************************************************/
VOS_VOID RABM_ComRlsRabReource(
    RRRABM_RAB_IND_STRU                 *pMsg                                   /* 目前处理的消息                           */
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucEntId;
    VOS_UINT8                           ucChgMask;
    VOS_UINT8                           ucSndGmmRabRlsIndFlg = VOS_FALSE;

    for(i = 0; i < pMsg->ulRabCnt; i++)
    {
        if(RABM_CN_PS == pMsg->aRabInfo[i].ulCnDomainId)
        {                                                                       /* 是PS域的RAB                              */
            if ( (RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
              && ((pMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET) )
            {
                ucEntId = (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId & 0x0f);
            }
            else
            {
                if ((pMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET)
                {
                    continue;
                }

                ucEntId = (VOS_UINT8)
                    ((pMsg->aRabInfo[i].ulRabId & 0x0f) - RABM_NSAPI_OFFSET);       /* 获得PS域的RABM实体ID                     */
            }

            switch(g_aRabmPsEnt[ucEntId].ucState)
            {
            case RABM_NULL:
            case RABM_NSAPI_ACTIVE_PENDING:
            case RABM_NSAPI_ACTIVE_NO_RAB:
                break;
            case RABM_NSAPI_ACTIVE_WITH_RAB:
            case RABM_DATA_TRANSFER_STOP:

                if ( ( (g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_TRAFFIC_CLASS_MASK) == RABM_CONVERSATION_CLASS)
                  || ( (g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_TRAFFIC_CLASS_MASK) == RABM_STREAM_CLASS) )
                {                                                               /* 是实时业务                               */
                    RABM_SndSmDeactReq((VOS_UINT8)(ucEntId + RABM_NSAPI_OFFSET));   /* 通知SM                                   */
                }
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId = 0xff;                   /* 初始化RAB ID为无效                       */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum = 0;                      /* 初始化RB的个数为0                        */

                RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_NO_RAB);

                /*更新RAB_MAP表中的ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;

                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComRlsRabReource:NORMAL:RABM state = RABM_NSAPI_ACTIVE_NO_RAB");

                /* 置位ucSndGmmRabRlsIndFlg标记 */
                ucSndGmmRabRlsIndFlg = VOS_TRUE;
                break;
            case RABM_ACT_PENDING_WITH_RAB:
                RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_PENDING);             /* 改变实体的状态                           */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComRlsRabReource:NORMAL:RABM state: RABM_ACT_PENDING_WITH_RAB ==> RABM_NSAPI_ACTIVE_PENDING");
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId = 0xff;                   /* 初始化RAB ID为无效                       */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum = 0;                      /* 初始化RB的个数为0                        */

                /*更新RAB_MAP表中的ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;

                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);

                /* 置位ucSndGmmRabRlsIndFlg标记 */
                ucSndGmmRabRlsIndFlg = VOS_TRUE;
                break;
            case RABM_TC_STATE_NULL:
                break;
            default:
                break;
            }
            g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_FALSE;
            if(0 != g_aRabmPsEnt[ucEntId].DlDataSave.ucNum)
            {
                /* 释放存储的下行数据                       */
                RABM_RelSaveData(&g_aRabmPsEnt[ucEntId].DlDataSave, RABM_DOWNLINK);
            }

            if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
            {
                RABM_TcInfRls(pMsg, i);
            }
        }
        else
        {                                                                       /* 是CS域的RAB                              */
            if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
            {
                RABM_TcInfRls(pMsg, i);
            }
            ucEntId = g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId];
            if(0xFF == ucEntId)
            {
                continue;
            }

            g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId] = 0xFF;
            switch(g_aRabmCsEnt[ucEntId].ucState)
            {
            case RABM_NULL:
                break;
            case RABM_SI_ACTIVE_WITH_RAB:
                g_aRabmCsEnt [ucEntId].ucState = RABM_NULL;                     /* 改变实体的状态                           */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComRlsRabReource:NORMAL:RABM state: RABM_SI_ACTIVE_WITH_RAB ==> RABM_NULL ");
                g_aRabmCsEnt [ucEntId].RabInfo.ucRabId = 0xff;                  /* 初始化RAB ID为无效                       */
                g_aRabmCsEnt [ucEntId].RabInfo.ucRbNum = 0;                     /* 初始化RB的个数为0                        */
                RABM_SndCcSyncInd(RABMCC_RAB_INACTIVE,
                    pMsg->aRabInfo[i].ulRabId);                                 /* 通知CC相应的信息                         */
                break;
            default:
                break;
            }
        }
    }

    if (VOS_TRUE == ucSndGmmRabRlsIndFlg)
    {
        /* 向GMM发送RAB释放指示 */
        RABM_SndGmmRabRelInd();
    }
}

/*******************************************************************************
  Module:   RABM_RelSaveData
  Function: 释放缓存的数据
  Input:    RABM_DATA_SAVE_STRU      *pLink             存储数据首地址
            VOS_UINT8                    ucMsgType          消息类型
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. 张志勇      2003.12.11   新规作成
*******************************************************************************/
VOS_VOID RABM_RelSaveData(
                      RABM_DATA_SAVE_STRU  *pLink,                              /* 存储数据首地址                           */
                      VOS_UINT8                ucMsgType                            /* 消息类型                                 */
                      )
{
    RABM_DATA_LINK_STRU *pTemp1 = RABM_POINTER_NULL;
    VOS_UINT8    i;

    pTemp1 = pLink->Data.pNxt;
    for( i = 0; i < pLink->ucNum; i++ )
    {
        if ( RABM_DOWNLINK == ucMsgType )
        {                                                                       /* 缓存的下行数据                           */
            RABM_PdcpFree(((PDCP_RABM_DATA_BUF_STRU *)
                    pLink->Data.pData)->pucData);
        }
        else
        {
            /*释放零拷贝内存块:*/
            TTF_MemFree(WUEPS_PID_RABM, ((TAFRABM_PS_DATA_REQ_STRU *)
                    pLink->Data.pData)->pData);
        }

        RABM_PdcpFree(pLink->Data.pData);                                       /* 释放消息                                 */

        if(RABM_POINTER_NULL != pTemp1)
        {                                                                       /* 缓存的数据不为0                          */
            pLink->Data.pData = pTemp1->pData;                                  /* 更新缓存的数据                           */
            pLink->Data.pNxt = pTemp1->pNxt;                                    /* 更新缓存的数据链表                       */
            RABM_Free(pTemp1);                                                  /* 释放链表节点                             */
        }
        pTemp1 = pLink->Data.pNxt;                                              /* 更新指针位置                             */
    }
    pLink->ucNum = 0;

    return;
}

/*******************************************************************************
  Module:   Rabm_TcInfSave
  Function: 记录RAB的信息
  Input:    RRRABM_RAB_IND_STRU      *pMsg
            VOS_UINT8                    ucRabId
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. 张志勇      2003.12.11   新规作成
      2. L47619   2005.11.26   问题单:  A32D00767
      3. L47619   2006.01.10   问题单:A32D01571
*******************************************************************************/
VOS_VOID Rabm_TcInfSave(
                    RRRABM_RAB_IND_STRU  *pMsg,
                    VOS_UINT8  ucRabId
                    )
{
    VOS_UINT8    i,j;
    VOS_UINT8    ucFlag = RABM_FALSE;

    if(0 == g_RabmTcInf.ucLbCnt)
    {                                                                           /* TC的信息中不包含RB信息                   */
        for(i = 0; i < pMsg->aRabInfo[ucRabId].ulRbNum; i++)
        {
            if(g_RabmTcInf.aRbInf[i].ucEstFlg == RABM_FALSE)
            {
                g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_TRUE;                     /* 标志该RB可用                             */
                if(RRC_NAS_CS_DOMAIN == pMsg->aRabInfo[ucRabId].ulCnDomainId)
                {
                    g_RabmTcInf.aRbInf[i].ucDomain = RABM_CN_CS;
                }
                else
                {
                    g_RabmTcInf.aRbInf[i].ucDomain = RABM_CN_PS;
                }
                g_RabmTcInf.aRbInf[i].ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[ucRabId].ulRabId);                   /* 记录RAB ID                               */
                g_RabmTcInf.aRbInf[i].ucRbId =
                    (VOS_UINT8)(pMsg->aRabInfo[ucRabId].aulRbId[i]);
                ucFlag = RABM_TRUE;
                RABM_SndTcRabInd(i, TC_RAB_SETUP);                                      /* 通知TC新建立的RB信息                     */
                g_RabmTcInf.ucLbCnt++;
            }
        }
    }
    else
    {
        for(i = 0; i < pMsg->aRabInfo[ucRabId].ulRbNum; i++)
        {
            for(j = 0; j < g_RabmTcInf.ucLbCnt; j++)
            {
                if ((VOS_UINT8)(pMsg->aRabInfo[ucRabId].aulRbId[i])
                                  == g_RabmTcInf.aRbInf[j].ucRbId)
                {
                    break;
                }
            }
            if((g_RabmTcInf.ucLbCnt == j) && (g_RabmTcInf.ucLbCnt < TC_LB_MAX_RBNUM))
            {
                g_RabmTcInf.aRbInf[j].ucEstFlg = RABM_TRUE;                     /* 标志该RB可用                             */
                if(RRC_NAS_CS_DOMAIN == pMsg->aRabInfo[ucRabId].ulCnDomainId)
                {
                    g_RabmTcInf.aRbInf[j].ucDomain = RABM_CN_CS;
                }
                else
                {
                    g_RabmTcInf.aRbInf[j].ucDomain = RABM_CN_PS;
                }
                g_RabmTcInf.aRbInf[j].ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[ucRabId].ulRabId);                   /* 记录RAB ID                               */
                g_RabmTcInf.aRbInf[j].ucRbId =
                    (VOS_UINT8)(pMsg->aRabInfo[ucRabId].aulRbId[i]);
                g_RabmTcInf.ucLbCnt++;
                /*向TC上报RAB INFO*/
                RABM_SndTcRabInd(j, TC_RAB_SETUP);                                      /* 通知TC新建立的RB信息                     */
            }
        }
    }

    /* RAB建立 */
    if(RABM_FALSE == ucFlag)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Rabm_TcInfSave:WARNING:Rabm_TcInfSave no rab setup ");
    }

    return;
}

/*******************************************************************************
  Module:   RABM_TcInfRls
  Function: 记录RAB的信息
  Input:    RRRABM_RAB_IND_STRU      *pMsg
            VOS_UINT8                    ucRabId
            VOS_UINT8                    ucPsFlg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. 张志勇      2003.12.11   新规作成
      2. L47619      2007.05.30   问题单:  A32D11248
*******************************************************************************/
VOS_VOID RABM_TcInfRls(
                   RRRABM_RAB_IND_STRU  *pMsg,
                   VOS_UINT8  ucRabId
                   )
{
    VOS_UINT8    i;

    if(pMsg->aRabInfo[ucRabId].ulRbNum > 1)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "RABM_TcInfRls:WARNING:RRC->RABM(TC) RAB contains more than one RB!");
        return;
    }

    for(i = 0; i < TC_LB_MAX_RBNUM; i++)
    {
        if(g_RabmTcInf.aRbInf[i].ucRbId ==
            (VOS_UINT8)(pMsg->aRabInfo[ucRabId].aulRbId[0]))
        {
            if(RABM_TRUE == g_RabmTcInf.aRbInf[i].ucEstFlg)
            {
                g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_FALSE;                    /* 标志该RB不可用                           */
                RABM_SndTcRabInd(i, TC_RAB_RELEASE);                            /* 通知TC该RB释放                           */

                /*罗德 GCF用例:7.2.3.36，仪器下发的CLOSE UP TEST LOOP中指示的LB个数为0，
                    与实际建立的RAB不一致，导致环回失败。为了规避该问题，做如下检查:*/
                if (0 != g_RabmTcInf.ucLbCnt)
                {
                    g_RabmTcInf.ucLbCnt--;
                }
                break;
            }
        }
    }
    return;
}

/*******************************************************************************
  Module:   RABM_TcRbStatus
  Function: 记录RAB的信息
  Input:    RRRABM_STATUS_IND_STRU      *pMsg
            VOS_UINT8                       ucRabId
            VOS_UINT8                       ucRelFlg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. 张志勇      2003.12.11   新规作成
*******************************************************************************/
VOS_VOID RABM_TcRbStatus(
                     RRRABM_STATUS_IND_STRU  *pMsg,
                     VOS_UINT8  ucRabId,
                     VOS_UINT8  ucRelFlg
                     )
{
    VOS_UINT8    i;

    for(i = 0; i < TC_LB_MAX_RBNUM; i++)
    {
        if(g_RabmTcInf.aRbInf[i].ucRabId ==
            (VOS_UINT8)(pMsg->aRab[ucRabId].ulRabId))
        {
            if(TC_RAB_RELEASE == ucRelFlg)
            {
                g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_FALSE;                    /* 标志该RB不可用                           */
            }
            else
            {
                g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_TRUE;                     /* 标志该RB可用                             */
            }
            RABM_SndTcRabInd(i, ucRelFlg);                                      /* 通知TC该RB停止/继续                      */
            break;
        }
    }
    return;
}



/*****************************************************************************
 函 数 名  : NAS_RABM_GetGRabIdStatus
 功能描述  : G下获取指定RAB承载的状态
 输入参数  : ucRabId   -  指定的RAB承载ID值
 输出参数  : 无
 返 回 值  : RABM_RAB_STATUS_ENUM_UINT32 - RAB承载状态值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 NAS_RABM_GetGRabIdStatus(
    VOS_UINT32                          ulEntId
)
{
    VOS_UINT8                           ucState;
    RABM_RAB_STATUS_ENUM_UINT32         enRabStatus;

    ucState = NAS_RABM_GetGPsEntState(ulEntId);

    switch (ucState)
    {
        case RABM_2G_NULL:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
        case RABM_NSAPI_OK_TRANSMODE_NO:
            enRabStatus = RABM_RAB_STATUS_SUSPEND;
            break;
        case RABM_DATA_TRANS_READY:
            enRabStatus = RABM_RAB_STATUS_ACTIVE;
            break;
        case RABM_ROUT_AREA_UPDATE:
            enRabStatus = RABM_RAB_STATUS_SUSPEND;
            break;
        case RABM_DATA_TRANS_STOP:
            enRabStatus = RABM_RAB_STATUS_SUSPEND;
            break;
        default:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
    }

    return enRabStatus;

}


/*****************************************************************************
 函 数 名  : NAS_RABM_GetWRabIdStatus
 功能描述  : W下获取指定RAB承载的状态
 输入参数  : ucRabId   -  指定的RAB承载ID值
 输出参数  : 无
 返 回 值  : RABM_RAB_STATUS_ENUM_UINT32 - RAB承载状态值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 NAS_RABM_GetWRabIdStatus(
    VOS_UINT32                          ulEntId
)
{
    VOS_UINT8                           ucState;
    RABM_RAB_STATUS_ENUM_UINT32         enRabStatus;

    ucState = NAS_RABM_GetWPsEntState(ulEntId);

    switch (ucState)
    {
        case RABM_NULL:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
        case RABM_NSAPI_ACTIVE_PENDING:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
        case RABM_NSAPI_ACTIVE_NO_RAB:
            enRabStatus = RABM_RAB_STATUS_IDLE;
            break;
        case RABM_NSAPI_ACTIVE_WITH_RAB:
            enRabStatus = RABM_RAB_STATUS_ACTIVE;
            break;
        case RABM_DATA_TRANSFER_STOP:
            enRabStatus = RABM_RAB_STATUS_SUSPEND;
            break;
        case RABM_ACT_PENDING_WITH_RAB:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
        default:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
    }

    return enRabStatus;

}

/*****************************************************************************
 函 数 名  : NAS_RABM_GetRabIdStatus
 功能描述  : 获取指定RAB承载的状态
 输入参数  : ucRabId   -  指定的RAB承载ID值
 输出参数  : 无
 返 回 值  : RABM_RAB_STATUS_ENUM_UINT32 - RAB承载状态值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
RABM_RAB_STATUS_ENUM_UINT32 NAS_RABM_GetRabIdStatus(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulEntId;
    RABM_RAB_STATUS_ENUM_UINT32         enRabStatus;
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 初始化 */
    enRabStatus = RABM_RAB_STATUS_FAIL;

    /* 判断RABID是否有效 */
    if ((ucRabId < NAS_RABM_RAB_ID_MIN) || (ucRabId > NAS_RABM_RAB_ID_MAX))
    {
        return enRabStatus;
    }

    /* 获取当前的系统模式 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();
    ulEntId          = ucRabId - RABM_NSAPI_OFFSET;

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrentSysMode)
    {
        enRabStatus = NAS_RABM_GetGRabIdStatus(ulEntId);
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrentSysMode)
    {
        enRabStatus = NAS_RABM_GetWRabIdStatus(ulEntId);
    }

    return enRabStatus;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_GetDefaultRabId
 功能描述  : 获取缺省的RABID
 输入参数  : ucRabId      - RABID [5,15]
 输出参数  : pucDeftRabId - Linked RABID [5,15]
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月2日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_RABM_GetDefaultRabId(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                          *pucDeftRabId
)
{
    VOS_UINT8                           ucLinkdRabId = RAB_MAP_INVALID_RAB_ID;

    if (VOS_NULL_PTR == pucDeftRabId)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_GetDefaultRabId: pucDeftRabId is NULL!");
        return PS_FAIL;
    }

    if (!RAB_MAP_RAB_IS_VALID(ucRabId))
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_GetDefaultRabId: ucRabId is invalid! <ucRabId>", ucRabId);
        return PS_FAIL;
    }

    if (PS_TRUE != g_astRabMap[ucRabId].enucExistInd)
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_GetDefaultRabId: RAB MAP Not Exist! <ucRabId>", ucRabId);
        return PS_FAIL;
    }

    ucLinkdRabId = g_astRabMap[ucRabId].ucLinkdRabId;

    if (!RAB_MAP_RAB_IS_VALID(ucLinkdRabId))
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_GetDefaultRabId: Linked RABID is invalid! <ucLinkdRabId>", ucLinkdRabId);
        return PS_FAIL;
    }

    *pucDeftRabId = ucLinkdRabId;

    return PS_SUCC ;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_UL_DataReq
 功能描述  : RABM上行发送函数，供CDS调用
 输入参数  : ucRabId   -  指定的RAB承载ID值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_UL_DataReq (
    CDS_RABM_TRANS_DATA_STRU           *pstUlData
)
{
    /* 调用RABM API  发送上行数据 */
    RABM_SendUlData(pstUlData->ucRabId, pstUlData->pstSdu);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_DL_DataInd
 功能描述  : RABM下行发送函数，调用CDS API发送数据给CDS
 输入参数  : ucRabId   -  指定的RAB承载ID值
             pstData   -  数据块指针
 输出参数  : 无
 返 回 值  : 发送数据成功或失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目CDS接口修改
*****************************************************************************/
VOS_UINT32 NAS_RABM_DL_DataInd(
    VOS_UINT8                           ucRabId,
    TTF_MEM_ST                         *pstData
)
{
    VOS_UINT32                  ulDataLen;
    CDS_RABM_TRANS_DATA_STRU    stCdsDlData;
    VOS_UINT16                  usModemid;

    /* 赋值 */
    ulDataLen = TTF_MemGetLen(WUEPS_PID_RABM, pstData);

    stCdsDlData.ucRabId     = ucRabId;
    stCdsDlData.pstSdu      = pstData;
    stCdsDlData.ulSduLen    = ulDataLen;

    stCdsDlData.aucRev[0]   = 0;
    stCdsDlData.aucRev[1]   = 0;
    stCdsDlData.aucRev[2]   = 0;

    usModemid = VOS_GetModemIDFromPid(WUEPS_PID_RABM);

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_RABM_GetCurrentSysMode())
    {
        /* 调用UMTS CDS API接口发送下行数据 */
        CDS_UMTS_DL_DataInd(&stCdsDlData, usModemid);
    }
    else
    {
        /* 调用GPRS CDS API接口发送下行数据 */
        CDS_GSM_DL_DataInd(&stCdsDlData, usModemid);
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : NAS_RABM_QosParaTransferToQci
 功能描述  : 根据QOS参数转换为QCI等级
 输入参数  : ucTrafficClass            -  会话类型
             ucTransDelay              -  会话时延
             ucTraffHandlPrior         -  会话处理优先级
             ucSrcStatisticsDescriptor -  源数据指示
             ucSignallingIndication    -  信令优化指示
 输出参数  : 无
 返 回 值  : QCI类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
QCI_TYPE_ENUM_UINT8 NAS_RABM_QosParaTransferToQci(
    VOS_UINT8                           ucTrafficClass,
    VOS_UINT8                           ucTransDelay,
    VOS_UINT8                           ucTraffHandlPrior,
    VOS_UINT8                           ucSrcStatisticsDescriptor,
    VOS_UINT8                           ucSignallingIndication
)
{
    QCI_TYPE_ENUM_UINT8                 enQci;

    /* 转换规则参见: 23.401
       Annex E (normative):
        Mapping between EPS and Release 99 QoS parameters
        QCI    Traffic_Class  Traffic_Handling_Priority Signalling_Indication  Src_Stats_Descriptor
         1     Conversational          NA                       NA                  SPEECH
         2     Conversational          NA                       NA                    NA
         3     Conversational          NA                       NA                   Unknown
         4     Streaming               NA                       NA                   Unknown
         5     Interactive              1                       YES                  Unknown
         6     Interactive              1                       NO                    NA
         7     Interactive              2                       NO                    NA
         8     Interactive              3                       NO                    NA
         9     Background              NA                       NA                    NA
    */
    /* 根据QOS trafficClass参数获取QCI */
    if (NAS_RABM_QOS_TRAFFIC_CLASS_CONVERSATIONAL == ucTrafficClass)
    {
        if (NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_SPEECH == ucSrcStatisticsDescriptor)
        {
            enQci       = QCI_TYPE_QCI1_GBR;
        }
        else if (ucTransDelay >= NAS_RABM_QOS_TRANSFER_DELAY_150MS)
        {
            enQci       = QCI_TYPE_QCI2_GBR;
        }
        else
        {
            enQci       = QCI_TYPE_QCI3_GBR;
        }
    }
    else if (NAS_RABM_QOS_TRAFFIC_CLASS_STREAMING == ucTrafficClass)
    {
        enQci       = QCI_TYPE_QCI4_GBR;
    }
    else if (NAS_RABM_QOS_TRAFFIC_CLASS_INTERACTIVE == ucTrafficClass)
    {
        if (NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_1 == ucTraffHandlPrior)
        {
            if (NAS_RABM_QOS_SIGNAL_IND_OPTIMISE == ucSignallingIndication)
            {
                enQci       = QCI_TYPE_QCI5_NONGBR;
            }
            else
            {
                enQci       = QCI_TYPE_QCI6_NONGBR;
            }
        }
        else if (NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_2 == ucTraffHandlPrior)
        {
            enQci       = QCI_TYPE_QCI7_NONGBR;
        }
        else
        {
            enQci       = QCI_TYPE_QCI8_NONGBR;
        }
    }
    else
    {
        enQci       = QCI_TYPE_QCI9_NONGBR;
    }

    return enQci;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_UnpackQos
 功能描述  : 从QOS字节流获取QCI等级
 输入参数  : ulQosLength   -  QOS字节流长度
             pQosValue     -  QOS字节流指针
 输出参数  : 无
 返 回 值  : QCI等级
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
QCI_TYPE_ENUM_UINT8 NAS_RABM_GetQciFromQos(
    VOS_UINT32                      ulQosLength,
    VOS_UINT8                      *pQosValue
)
{
    QCI_TYPE_ENUM_UINT8                 enQci;
    VOS_UINT8                           ucTrafficClass;
    VOS_UINT8                           ucTransDelay;
    VOS_UINT8                           ucTraffHandlPrior;
    VOS_UINT8                           ucSrcStatisticsDescriptor;
    VOS_UINT8                           ucSignallingIndication;


    /* 初始化 */
    enQci          = QCI_TYPE_QCI9_NONGBR;

    /* 获取QOS中trafficClass参数 */
    if (ulQosLength < NAS_RABM_QOS_TRAFFIC_CLASS_BYTE_OFFSET)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_RABM_GetQciFromQos:WARNING:QOS too short!");
        return enQci;
    }

    if (ulQosLength > NAS_RABM_QOS_TRAFFIC_CLASS_BYTE_OFFSET)
    {
        ucTrafficClass = (pQosValue[NAS_RABM_QOS_TRAFFIC_CLASS_BYTE_OFFSET] & NAS_RABM_QOS_TRAFFIC_CLASS_MASK)
                                        >> NAS_RABM_QOS_TRAFFIC_CLASS_BIT_OFFSET;
    }
    else
    {
        ucTrafficClass = NAS_RABM_QOS_TRAFFIC_CLASS_BACKGROUND;
    }

    /* 获取QOS中Transfer Delay参数 */
    if (ulQosLength > NAS_RABM_QOS_TRANSFER_DELAY_BYTE_OFFSET)
    {
        ucTransDelay = (pQosValue[NAS_RABM_QOS_TRANSFER_DELAY_BYTE_OFFSET] & NAS_RABM_QOS_TRANSFER_DELAY_MASK)
                                        >> NAS_RABM_QOS_TRANSFER_DELAY_BIT_OFFSET;
    }
    else
    {
        ucTransDelay = 0;
    }

    /* 获取QOS中Traffic Handling Priority参数 */
    if (ulQosLength > NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_BYTE_OFFSET)
    {
        ucTraffHandlPrior = pQosValue[NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_BYTE_OFFSET]
                                        & NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_MASK;
    }
    else
    {
        ucTraffHandlPrior = NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_1;
    }

    /* 获取QOS中Source Statistics Descriptor参数 */
    if (ulQosLength > NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_BYTE_OFFSET)
    {
        ucSrcStatisticsDescriptor = pQosValue[NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_BYTE_OFFSET]
                                        & NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_MASK;
    }
    else
    {
        ucSrcStatisticsDescriptor = NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN;
    }

    /* Signalling-Indication 的值只取该字节的第5位 */
    if (ulQosLength > NAS_RABM_QOS_SIGNAL_IND_BYTE_OFFSET)
    {
        ucSignallingIndication = (pQosValue[NAS_RABM_QOS_SIGNAL_IND_BYTE_OFFSET] & NAS_RABM_QOS_SIGNAL_IND_MASK)
                                        >> NAS_RABM_QOS_SIGNAL_IND_BIT_OFFSET;
    }
    else
    {
        ucSignallingIndication = NAS_RABM_QOS_SIGNAL_IND_NOT_OPTIMISE;
    }

    enQci = NAS_RABM_QosParaTransferToQci(ucTrafficClass,
                                          ucTransDelay,
                                          ucTraffHandlPrior,
                                          ucSrcStatisticsDescriptor,
                                          ucSignallingIndication);
    return enQci;
}



/*****************************************************************************
 函 数 名  : NAS_RABM_SetFinIpInRdFlag
 功能描述  : 设置CDS读取一次RD后处理最后一个IP包标识
 输入参数  : VOS_UINT32 ulFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月30日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_RABM_SetFinIpInRdFlag(VOS_UINT32 ulFlag)
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 获取当前的系统模式 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();

    switch (enCurrentSysMode)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_UTRANCTRL_RABM_SetFinIpInRdFlag(ulFlag);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_StartReestRabPendingTmr
 功能描述  : 启动RB建立保护定时器
 输入参数  : ucRabId - RABID [5,15]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_RABM_StartReestRabPendingTmr(VOS_UINT8 ucRabId)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucRabId - RABM_NSAPI_OFFSET);

    if (VOS_OK != NAS_StartRelTimer(&(pstWPsEnt->hRabPendingTmrHdl),
                                    WUEPS_PID_RABM,
                                    NAS_RABM_GET_RAB_PENDING_TMR_LEN(),
                                    ucRabId,
                                    RABM_TIMER_RAB_REESTABLISH_PENDING,
                                    VOS_RELTIMER_NOLOOP))
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_StartReestRabPendingTmr: Start timer failed.");
        pstWPsEnt->hRabPendingTmrHdl = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_StopReestRabPendingTmr
 功能描述  : 停止RB建立保护定时器
 输入参数  : ucRabId - RABID [5,15]
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月17日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_RABM_StopReestRabPendingTmr(VOS_UINT8 ucRabId)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucRabId - RABM_NSAPI_OFFSET);

    if (VOS_NULL_PTR != pstWPsEnt->hRabPendingTmrHdl)
    {
        if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_RABM,
                                       RABM_TIMER_RAB_REESTABLISH_PENDING,
                                       &(pstWPsEnt->hRabPendingTmrHdl)))
        {
            NAS_ERROR_LOG(WUEPS_PID_RABM,
                "NAS_RABM_StopReestRabPendingTmr: Stop timer failed.");
            pstWPsEnt->hRabPendingTmrHdl = VOS_NULL_PTR;
        }
    }

    return;
}

/*lint +e958*/


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

