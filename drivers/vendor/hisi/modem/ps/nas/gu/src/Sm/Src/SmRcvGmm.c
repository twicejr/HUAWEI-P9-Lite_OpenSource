/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SmRcvGmm.c
  Description  : SM接收GMM消息的处理
  Function List:
                 1.  SM_ComSaveTICheck
                 2.  SM_ComOptionalCheck
                 3.  SM_ComActPdpCntxtAccCheck
                 4.  SM_ComActPdpCntxtRejCheck
                 5.  SM_ComReqPdpCntxtActMsgCheck
                 6.  SM_ComModifyPdpCntxtAccCheck
                 7.  SM_ComModifyPdpCntxtReqCheck
                 8.  SM_ComActSecPdpCntxtAccCheck
                 9.  SM_ComActSecPdpCntxtRejCheck
                10.  SM_ComModifyPdpCntxtRejCheck
                11.  SM_ComDeActPdpCntxtReqCheck
                12.  SM_ComDeActPdpCntxtAccCheck
                13.  SM_RcvGmmSmEstabishCnf
                14.  SM_RcvGmmSmStatusInd
                15.  SM_RcvNwReqPdpCntxtActMsg
                16.  SM_RcvNwActPdpCntxtAccMsg
                17.  SM_RcvNwActPdpCntxtRejMsg
                18.  SM_RcvNwActSecPdpCntxtAccMsg
                19.  SM_RcvNwActSecPdpCntxtRejMsg
                20.  SM_RcvNwModifyPdpCntxtReqMsg
                21.  SM_RcvNwModifyPdpCntxtAccMsg
                22.  SM_RcvNwModifyPdpCntxtRejMsg
                23.  SM_RcvNwDeActPdpCntxtReqMsg
                24.  SM_RcvNwDeActPdpCntxtAccMsg
                25.  SM_ComFindNullAddrApn
                26.  SM_ComClearPdpCntxt
                27.  SM_ComClearPdpAddrApn
                28.  SM_ComDelNsapiFromAddr
                29.  SM_RcvNwReqPdpCnxtActMsg_S00
                30.  SM_RcvNwReqPdpCnxtActMsg_S01
                31.  SM_RcvNwReqPdpCnxtActMsg_S02
  History:
      1.  张志勇  2003.12.08   新规作成
      2.  H41410  2006-04-18   for A32D03243
      3.  H41410  2006-04-27   for A32D02981
      4.  L47619  2007-01-16   for A32D08447
      5.  L47619  2007-10-27   for A32D13038
      6.  l107747 2007-12-18   for A32D13917
*******************************************************************************/
#include "SmInclude.h"
#include "Taf_Common.h"
#include "mdrv.h"
#include "NVIM_Interface.h"


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
#define    THIS_FILE_ID        PS_FILE_ID_SM_RCVGMM_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

extern VOS_UINT8* SM_GetSystemAppConfigAddr(VOS_VOID);


/*******************************************************************************
  Module:      SM_ComSaveTICheck
  Function:    存储Transaction identifier
  Input:       VOS_UINT8                              *tempMsg     网侧消息
               VOS_UINT32                              *ulSum       计数器
               SM_NW_MSG_STRU                     *pMsgIE      数据结构指针
  Output:      VOS_VOID
  NOTE:
  Return:      SM_RETURN_OK
               SM_RETURN_NG
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
VOS_UINT8 SM_ComSaveTICheck(
                       VOS_UINT8                              ucMsgType,
                       VOS_UINT8                              **tempMsg,            /* 网侧消息                                 */
                       VOS_UINT32                              *ulSum,               /* 计数器                                   */
                       SM_NW_MSG_STRU                     *pMsgIE               /* 数据结构指针                             */
                      )
{
    VOS_UINT8    ucRet;

    ucRet = SM_RETURN_OK;
    if(0x70 == (0x70 & (**tempMsg)))
    {                                                                           /* TI有扩展位                               */
        pMsgIE->ucTi = **tempMsg & 0x80;                                        /* 存储TI Flag                              */
        (*tempMsg)++;                                                           /* 更新指针偏移的长度                       */
        *ulSum += 1;                                                            /* 计数器加1                                */
        pMsgIE->ucTi = (**tempMsg & 0x7f) | (pMsgIE->ucTi & 0x80);              /* 存储Transaction identifier               */
        (*tempMsg)++;                                                           /* 更新指针偏移的长度                       */
        *ulSum += 1;                                                            /* 计数器加1                                */
        pMsgIE->ucTiFlg = pMsgIE->ucTi & 0x80;
    }
    else
    {                                                                           /* TI无扩展                                 */
        pMsgIE->ucTi = **tempMsg;                                               /* 获得空口消息中的第一字节                 */
        pMsgIE->ucTiFlg = pMsgIE->ucTi & 0x80;                                  /* 存储TI Flag                              */
        if(0x80 == (pMsgIE->ucTi & 0x80))
        {
            pMsgIE->ucTi = (pMsgIE->ucTi & 0x80) | ((pMsgIE->ucTi>>4) & 0x07);  /* TI为指针的第7、6、5位的值                */
        }
        else
        {
            pMsgIE->ucTi = pMsgIE->ucTi >> 4;                                   /* TI为指针的第7、6、5位的值                */
        }
        (*tempMsg)++;                                                           /* 更新指针偏移的长度                       */
        *ulSum += 1;                                                            /* 计数器加1                                */
    }

    switch(ucMsgType)
    {
    case SM_REQ_PDP_CONTEXT_ACT:
        if( 0x80 == pMsgIE->ucTiFlg )
        {
            ucRet = SM_RETURN_NG;

            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "SM_ComSaveTICheck:WARNING:NW->SM: Invalid transaction identifier value !");

        }
        break;
    case SM_ACT_PDP_CONTEXT_ACC:
    case SM_ACT_PDP_CONTEXT_REJ:
    case SM_DEACT_PDP_CONTEXT_REQ:
    case SM_DEACT_PDP_CONTEXT_ACC:
    case SM_MOD_PDP_CONTEXT_REQ_N2M:
    case SM_MOD_PDP_CONTEXT_ACC_N2M:
    case SM_MOD_PDP_CONTEXT_REJ:
    case SM_ACT_SEC_PDP_CONTEXT_ACC:
    case SM_ACT_SEC_PDP_CONTEXT_REJ:
        if(0xff != g_TiMapToNsapi[pMsgIE->ucTi])
        {
            if((( 1 == (pMsgIE->ucTiFlg >> 7 ))
                  &&( SM_TI_NET_ORG == g_SmEntity.
                  aPdpCntxtList[g_TiMapToNsapi[pMsgIE->ucTi]].ucTiFlg ))
                || (( 0 == (pMsgIE->ucTiFlg >> 7 ))
                   &&( SM_TI_MS_ORG == g_SmEntity.
                   aPdpCntxtList[g_TiMapToNsapi[pMsgIE->ucTi]].ucTiFlg )))
            {
                SM_SndStatusMsg(pMsgIE->ucTi,TAF_SM_REJ_CAUSE_PROTOCOL_ERR);    /* cause:protocol errors                    */
                ucRet = SM_RETURN_NG;

            }
        }
        break;
    default :
        break;
    }
    return ucRet;
}

/*****************************************************************************
 函 数 名  : NAS_SM_ComSaveLlcSapi
 功能描述  : 存储IE项中LLC SAPI的内容
 输入参数  : VOS_UINT8      **ppucMsg - 网侧消息
             VOS_UINT32     *pulSum   - 计数器
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月29日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_SM_ComSaveLlcSapi(
    VOS_UINT8                           **ppucMsg,
    VOS_UINT32                          *pulSum
)
{
    /* 消息指针指向IEI的后一位，并更新计数器 */
    (*ppucMsg)++;
    *pulSum += 1;

    /* 有效标识设置为有效，获取SAPI并暂存到g_aucSapi[0][1]位置 */
    g_aucSapi[0][0] = 1;
    g_aucSapi[0][1] = 0x0F & (**ppucMsg);

    /* 消息指针后移一位，并更新计数器 */
    (*ppucMsg)++;
    *pulSum += 1;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : NAS_SM_ComSaveSmCauseTwo
 功能描述  : 存储IE项中SM CAUSE的内容
 输入参数  : VOS_UINT8      **ppucMsg - 网侧消息
             VOS_UINT32     *pulSum   - 计数器
 输出参数  : SM_MSG_IE_COMMON_STRU  *pstIE    - 存储IE内容的结构指针
 返 回 值  : VOS_VOID

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月13日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_SM_ComSaveSmCauseTwo(
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                         **ppucMsg,
    VOS_UINT32                         *pulSum,
    SM_MSG_IE_COMMON_STRU              *pstIE

)
{
    /*----------------------------------------------------------------------
       8   7   6   5   4   3   2   1
       SM cause 2 IEI                  octet 1
       Length of SM cause 2 contents   octet 2
       SM cause 2 value                octet 3
    ----------------------------------------------------------------------*/
    /*----------------------------------------------------------------------
      A SM cause 2 value is coded as octet 2 of the SM cause information element.
    ----------------------------------------------------------------------*/

    /* 消息指针指向IEI的后一位，并更新计数器 */
    (*ppucMsg)++;
    *pulSum += 1;

    /* 若计数器超过消息长度，直接返回 */
    if (*pulSum < ulPduLen)
    {
        /* 获取IE长度和内容指针 */
        pstIE->ucLen  = **ppucMsg;
        pstIE->pValue = *ppucMsg + 1;

        /* 更新消息指针偏移和计数器 */
        *ppucMsg      += pstIE->ucLen + 1;
        *pulSum       += pstIE->ucLen + 1;

        /* 若计数器超过消息长度，清空该IE长度 */
        if (*pulSum > ulPduLen)
        {
            pstIE->ucLen = 0;
        }
    }

}
#endif

/*****************************************************************************
 函 数 名  : NAS_SM_ComProcUnknowIEs
 功能描述  : 处理不识别的IE
 输入参数  : VOS_UINT32             ulPduLen   - 网侧消息长度
             VOS_UINT8              **ppucMsg  - 网侧消息
             VOS_UINT32             *pulSum    - 计数器
 输出参数  : VOS_UINT8
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月29日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_SM_ComProcUnknowIE(
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                           **ppucMsg,
    VOS_UINT32                          *pulSum
)
{
    VOS_UINT32                          ullen;

    if (0x00 == ((**ppucMsg) & 0xF0))
    {
        /*----------------------------------------------------------------------
          An IE is encoded as 'comprehension required' if bits 5, 6, 7 and 8 of
          its IEI are set to zero. Refer to section 8.5 in TS 24.008
        ----------------------------------------------------------------------*/
        return SM_RETURN_NG;
    }
    else
    {
        /*---------------------------------------------------------
          Ignore unknown IE. Refer to section 11.2.4 in TS 24.007
        ---------------------------------------------------------*/
        if (0x80 == ((**ppucMsg) & 0x80))
        {
            /*----------------------------------------------------------------
              A 1 valued bit 8 indicates that the whole IE is one octet long
            ----------------------------------------------------------------*/
            (*ppucMsg)++;                                                       /* 更新指针偏移的长度                       */
            *pulSum += 1;                                                       /* 计数器加1                                */
        }
        else
        {
            /*------------------------------------------------------------------
              A 0 valued bit 8 indicates that the following octet is a length
              octet
            ------------------------------------------------------------------*/
            (*ppucMsg)++;                                                       /* 更新指针偏移的长度,指向IEI的后一位       */
            *pulSum += 1;                                                       /* 计数器加1                                */

            if (*pulSum < ulPduLen)
            {                                                                   /* 计数器小于消息长度                       */
                ullen = *pulSum + **ppucMsg + 1;
                if (ullen <= ulPduLen)
                {
                    *pulSum     += **ppucMsg + 1;                               /* 更新计数器长度                           */
                    *ppucMsg    += **ppucMsg + 1;                               /* 更新指针偏移的长度                       */
                }
            }
        }
    }

    return SM_RETURN_OK;
}

/*****************************************************************************
 函 数 名  : NAS_SM_ComSaveIEValue
 功能描述  : 存储Optional项中的IE内容
 输入参数  : VOS_UINT32             ulPduLen  - 网侧消息长度
             VOS_UINT8              **ppucMsg - 网侧消息
             VOS_UINT32             *pulSum   - 计数器
 输出参数  : SM_MSG_IE_COMMON_STRU  *pstIE    - 存储IE内容的结构指针
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月29日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_SM_ComSaveIEValue(
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                           **ppucMsg,
    VOS_UINT32                          *pulSum,
    SM_MSG_IE_COMMON_STRU               *pstIE
)
{
    /* 消息指针指向IEI的后一位，并更新计数器 */
    (*ppucMsg)++;
    *pulSum += 1;

    /* 若计数器超过消息长度，直接返回 */
    if (*pulSum < ulPduLen)
    {
        /* 获取IE长度和内容指针 */
        pstIE->ucLen  = **ppucMsg;
        pstIE->pValue = *ppucMsg + 1;

        /* 更新消息指针偏移和计数器 */
        *ppucMsg    += pstIE->ucLen + 1;
        *pulSum     += pstIE->ucLen + 1;

        /* 若计数器超过消息长度，清空该IE长度 */
        if (*pulSum > ulPduLen)
        {
            pstIE->ucLen = 0;
        }
    }
}

/*******************************************************************************
  Module:      SM_ComOptionalCheck
  Function:    消息中Optional项的检查存储
  Input:       VOS_UINT8                        *tempMsg     网侧消息
               VOS_UINT32                       ulSmPduLen   网侧消息长度
               VOS_UINT32                       *ulSum       计数器
               SM_NW_MSG_STRU                   *pMsgIE      数据结构指针
  Output:      VOS_UINT32                       ucRet
  NOTE:
  Return:      VOS_VOID
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
VOS_UINT32 SM_ComOptionalCheck(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          ulSmPduLen,
    VOS_UINT32                          *pulSum,
    SM_NW_MSG_STRU                      *pMsgIE
)
{
    VOS_UINT32                          ucRet;                                  /* 定义返回值                               */

    ucRet = SM_RETURN_OK;                                                       /* 置返回值为成功                           */

    for ( ; *pulSum < ulSmPduLen; )
    {                                                                           /* 循环option项,达到指定消息长度时跳出      */
        if (NAS_SM_IEI_NEW_RADIO_PRIORITY == ((*pucMsg) >> 4))
        {
            /*-------------------------------------------------
               8     7     6     5  |   4  |   3     2     1
              -----------------------------------------------
               Radio priority IEI   |   0  |  Radio priority
                                    | spare|   level value
            -------------------------------------------------*/
            pMsgIE->ucRadioPri = (*pucMsg) & 0x07;                              /* 存储Radio priority                       */
            pucMsg++;                                                           /* 更新指针偏移的长度                       */
            *pulSum += 1;                                                       /* 计数器加1                                */
        }
        else if (NAS_SM_IEI_TEARDOWN_INDICATOR == ((*pucMsg) & 0xF0))
        {
            /*--------------------------------------------------
               8     7     6     5  |   4     3     2  |   1
              -----------------------------------------------
               Tear down indicator  |   0     0     0  |  TDI
                       IEI          |       spare      | flag
            --------------------------------------------------*/
            pMsgIE->ucTdi = (*pucMsg) & 0x01;                                   /* 存储Tear down indicator                  */
            pucMsg++;                                                           /* 更新指针偏移的长度                       */
            *pulSum += 1;                                                       /* 计数器加1                                */
        }
        else
        {
            switch (*pucMsg)
            {                                                                   /* 判定IEI                                  */
                case NAS_SM_IEI_PDP_ADDRESS:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->PdpAddr));
                    break;

                case NAS_SM_IEI_PROTOCOL_CFG_OPTIONS:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->ProCnfgOpt));
                    break;

                case NAS_SM_IEI_PACKET_FLOW_ID:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->Pfi));
                    break;

                case NAS_SM_IEI_ACCESS_POINT_NAME:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->Apn));
                    break;

                case NAS_SM_IEI_NEW_QOS:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->Qos));
                    break;

                case NAS_SM_IEI_REQUEST_LLC_SAPI:
                    NAS_SM_ComSaveLlcSapi(&pucMsg, pulSum);
                    break;

#if (FEATURE_ON == FEATURE_IPV6)
                case NAS_SM_IEI_CAUSE_TWO:
                    NAS_SM_ComSaveSmCauseTwo(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->stSmCauseTwo));
                    break;
#endif

                default:
                    ucRet = NAS_SM_ComProcUnknowIE(ulSmPduLen, &pucMsg, pulSum);
                    if (SM_RETURN_NG == ucRet)
                    {
                        return ucRet;
                    }
                    break;
            }
        }
    }

    return ucRet;
}

/*******************************************************************************
  Module:      SM_ComActPdpCntxtAccCheck
  Function:    检查存储网侧发给MS的ACTIVATE PDP CONTEXT ACCEPT消息的处理
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComActPdpCntxtAccCheck(
    VOS_UINT8                 *pMsg,             /* 网侧消息 */
    VOS_UINT32                ulSmPduLen         /* 网侧消息长度 */
)
{
    SM_NW_MSG_STRU                         *pMsgIE;                             /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                            /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                              /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComActPdpCntxtAccCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet((VOS_VOID *)pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum   = 0;                                                                /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */


    if ( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if ( SM_RETURN_NG == SM_ComSaveTICheck(SM_ACT_PDP_CONTEXT_ACC,
            &tempMsg, &ulSum, pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");

        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }

    ulSum   ++;
    tempMsg ++;                                                                 /*只忽略MSG TYPE,不忽略SAPI*/
    g_aucSapi[0][0] = 1;                                                        /*有效标识设置为有效*/
    g_aucSapi[0][1] = 0x0F & (*tempMsg);                                        /*获取SAPI,并 暂存到g_aucSapi[0][1]位置*/
    ulSum   ++;
    tempMsg ++;

    if ( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->Qos.ucLen = *(tempMsg);                                         /* 存储Negotiated QoS的长度                 */
        pMsgIE->Qos.pValue = tempMsg + 1;                                       /* 存储Negotiated QoS的指针                 */
        tempMsg += pMsgIE->Qos.ucLen + 1;                                       /* 更新指针偏移的长度                       */
        ulSum += pMsgIE->Qos.ucLen + 1;                                         /* 更新计数器长度                           */
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");

        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }

    if ( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->ucRadioPri=0x07 & (*tempMsg);                                   /* 存储Radio priority                       */
        tempMsg++;                                                              /* 更新指针偏移的长度                       */
        ulSum++;                                                                /* 计数器加1                                */
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }

    if ( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if (SM_RETURN_OK != SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE))               /* 调用函数存储Option项IE                   */
        {
            SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtAccCheck:WARNING:Unknown IE encoded as comprehension required!");
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}

/*******************************************************************************
  Module:      SM_ComActPdpCntxtRejCheck
  Function:    检查存储网侧发给MS的ACTIVATE PDP CONTEXT REJECT消息的处理
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComActPdpCntxtRejCheck(
                                             VOS_UINT8   *pMsg,                     /* 网侧消息                                 */
                                             VOS_UINT32   ulSmPduLen                 /* 网侧消息长度                             */
                                             )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                                /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                                   /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComActPdpCntxtRejCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_NG == SM_ComSaveTICheck(SM_ACT_PDP_CONTEXT_REJ
            ,&tempMsg, &ulSum, pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* 忽略IE"消息类型",更新指针偏移,计数器加1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->SmCause = *(tempMsg);                                           /* 存储SM cause                             */
        tempMsg++;                                                              /* 更新指针偏移的长度                       */
        ulSum++;                                                                /* 计数器加1                                */
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* 调用函数存储Option项IE                   */
    }

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}

/*******************************************************************************
  Module:      SM_ComReqPdpCntxtActMsgCheck
  Function:    检查存储网侧发给MS的REQUEST PDP CONTEXT ACTIVATION消息的处理
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComReqPdpCntxtActMsgCheck(
                                                     VOS_UINT8   *pMsg,             /* 网侧消息                                 */
                                                     VOS_UINT32   ulSmPduLen         /* 网侧消息长度                             */
                                                )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                                /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                                   /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComReqPdpCntxtActMsgCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_NG == SM_ComSaveTICheck(SM_REQ_PDP_CONTEXT_ACT,
            &tempMsg, &ulSum, pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComReqPdpCntxtActMsgCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* 忽略IE"小心类型",更新指针偏移,计数器加1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if( 0x02 == *tempMsg )
        {                                                                       /* 长度为0                                  */
            pMsgIE->PdpAddr.ucLen = 2;                                          /* 长度赋值                                 */
            pMsgIE->PdpAddr.pValue= tempMsg + 1;                                /* 存储PDP address的指针                    */
            tempMsg += 3;                                                       /* 更新指针偏移的长度                       */
            ulSum += 3;                                                         /* 更新计数器                               */
        }
        else
        {
            pMsgIE->PdpAddr.ucLen = *tempMsg;                                   /* 存储Offered PDP address的长度            */
            pMsgIE->PdpAddr.pValue= tempMsg + 1;                                /* 存储Offered PDP address的指针            */
            tempMsg += pMsgIE->PdpAddr.ucLen + 1;                               /* 更新指针偏移的长度                       */
            ulSum += pMsgIE->PdpAddr.ucLen + 1;                                 /* 更新计数器长度                           */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComReqPdpCntxtActMsgCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* 调用函数存储Option项IE                   */
    }
    else if( ulSum > ulSmPduLen )
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComReqPdpCntxtActMsgCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    else
    {
    }

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}

/*******************************************************************************
  Module:      SM_ComModifyPdpCntxtAccCheck
  Function:    检查存储网侧发给MS的MODIFY PDP CONTEXT ACCEPT消息的处理
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComModifyPdpCntxtAccCheck(
                                                     VOS_UINT8   *pMsg,             /* 网侧消息                                 */
                                                     VOS_UINT32   ulSmPduLen         /* 网侧消息长度                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                                /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                                   /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComModifyPdpCntxtAccCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_MOD_PDP_CONTEXT_ACC_N2M,&tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* 忽略IE"消息类型",更新指针偏移,计数器加1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* 调用函数存储Option项IE                   */
    }
    else if( ulSum > ulSmPduLen )
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    else
    {
    }

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}

/*******************************************************************************
  Module:      SM_ComModifyPdpCntxtReqCheck
  Function:    检查存储网侧发给MS的MODIFY PDP CONTEXT REQUEST消息的处理
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComModifyPdpCntxtReqCheck(
                                                     VOS_UINT8   *pMsg,             /* 网侧消息                                 */
                                                     VOS_UINT32   ulSmPduLen         /* 网侧消息长度                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                                /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                                   /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComModifyPdpCntxtReqCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_MOD_PDP_CONTEXT_REQ_N2M, &tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* 忽略IE"消息类型",更新指针偏移,计数器加1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->ucRadioPri=0x07 & (*tempMsg);                                   /* 存储Radio priority                       */
        tempMsg++;                                                              /* 更新指针偏移的长度                       */
        ulSum++;                                                                /* 计数器加1                                */
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }

    g_aucSapi[0][0] = 1;
    g_aucSapi[0][1] = 0x0F & (*tempMsg);                      /*读取SAPI*/

    if( (SM_SAPI_NOT_ASSIGN != g_aucSapi[0][1]) && (SM_SAPI_3 != g_aucSapi[0][1])
         && (SM_SAPI_5 != g_aucSapi[0][1]) && (SM_SAPI_9 != g_aucSapi[0][1])
         && (SM_SAPI_11 != g_aucSapi[0][1]))
    {
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }

    ulSum += 1;
    tempMsg += 1;                                                               /* 忽略IE"LLC SAPI",更新指针偏移,计数器加1  */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->Qos.ucLen = *(tempMsg);                                         /* 存储New QoS的长度                        */
        pMsgIE->Qos.pValue=(tempMsg + 1);                                       /* 存储New QoS的指针                        */
        tempMsg += pMsgIE->Qos.ucLen + 1;                                       /* 更新指针偏移的长度                       */
        ulSum += pMsgIE->Qos.ucLen + 1;                                         /* 更新计数器长度                           */
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_OK != SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE))            /* 调用函数存储Option项IE                   */
        {
            SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
            SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:Unknown IE encoded as comprehension required!");
            return SM_NULL;                                                         /* 返回SM_NULL                              */
        }
    }
    else if( ulSum > ulSmPduLen )
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    else
    {
    }

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}

/*******************************************************************************
  Module:      SM_ComActSecPdpCntxtAccCheck
  Function:    检查存储网侧发给MS的ACTIVATE SECONDARY PDP CONTEXT ACCEPT消息
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComActSecPdpCntxtAccCheck(
                                                     VOS_UINT8   *pMsg,             /* 网侧消息                                 */
                                                     VOS_UINT32   ulSmPduLen         /* 网侧消息长度                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                                /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                                   /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComActSecPdpCntxtAccCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_ACT_SEC_PDP_CONTEXT_ACC, &tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }

    ulSum++;                                        /* 忽略IE"消息类型"*/
    tempMsg++;                                      /* 忽略IE"消息类型"*/

    g_aucSapi[0][0] = 1;
    g_aucSapi[0][1] = 0x0F & (*tempMsg);

    ulSum++;                                        /* 处理完 "SAPI"，指针下移*/
    tempMsg++;                                      /* 处理完 "SAPI"，指针下移*/

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->Qos.ucLen = *(tempMsg);                                         /* 存储Negotiated QoS的长度                 */
        pMsgIE->Qos.pValue = (tempMsg + 1);                                     /* 存储Negotiated QoS的指针                 */
        tempMsg += pMsgIE->Qos.ucLen + 1;                                       /* 更新指针偏移的长度                       */
        ulSum += pMsgIE->Qos.ucLen + 1;                                         /* 更新计数器长度                           */
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->ucRadioPri=0x07 & (* tempMsg);                                  /* 存储Radio priority                       */
        tempMsg++;                                                              /* 更新指针偏移的长度                       */
        ulSum++;                                                                /* 计数器加1                                */
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* 调用函数存储Option项IE                   */
    }

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}
/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_ComActSecPdpCntxtRejCheck
  Function:    检查存储网侧发给MS的ACTIVATE SECONDARY PDP CONTEXT REJECT消息
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComActSecPdpCntxtRejCheck(
                                                     VOS_UINT8   *pMsg,             /* 网侧消息                                 */
                                                     VOS_UINT32   ulSmPduLen         /* 网侧消息长度                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                                /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                                   /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComActSecPdpCntxtRejCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_ACT_SEC_PDP_CONTEXT_REJ, &tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* 忽略IE"消息类型",更新指针偏移,计数器加1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->SmCause = *(tempMsg);                                           /* 存储SM cause                             */
        tempMsg++;                                                              /* 更新指针偏移的长度                       */
        ulSum++;                                                                /* 计数器加1                                */
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}

/*******************************************************************************
  Module:      SM_ComModifyPdpCntxtRejCheck
  Function:    检查存储网侧发给MS的MODIFY PDP CONTEXT REJECT消息的处理
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComModifyPdpCntxtRejCheck(
                                                     VOS_UINT8   *pMsg,             /* 网侧消息                                 */
                                                     VOS_UINT32   ulSmPduLen         /* 网侧消息长度                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                                /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                                   /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComModifyPdpCntxtRejCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_NG == SM_ComSaveTICheck(SM_MOD_PDP_CONTEXT_REJ,
            &tempMsg, &ulSum,pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* 忽略IE"消息类型",更新指针偏移,计数器加1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->SmCause = *(tempMsg);                                           /* 存储SM cause                             */
        tempMsg++;                                                              /* 更新指针偏移的长度                       */
        ulSum++;                                                                /* 计数器加1                                */
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}

/*******************************************************************************
  Module:      SM_ComDeActPdpCntxtReqCheck
  Function:    检查存储网侧发给MS的DEACTIVATE PDP CONTEXT REQUEST消息的处理
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComDeActPdpCntxtReqCheck(
                                                     VOS_UINT8   *pMsg,             /* 网侧消息                                 */
                                                     VOS_UINT32   ulSmPduLen         /* 网侧消息长度                             */
                                              )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                                /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                                   /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComDeActPdpCntxtReqCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_DEACT_PDP_CONTEXT_REQ,&tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComDeActPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* 忽略IE"消息类型",更新指针偏移,计数器加1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        pMsgIE->SmCause = *(tempMsg);                                           /* 存储SM cause                             */
        tempMsg++;                                                              /* 更新指针偏移的长度                       */
        ulSum++;                                                                /* 计数器加1                                */
    }
    else
    {                                                                           /* 消息长度错误                             */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComDeActPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        pMsgIE->SmCause = TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE;
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* 调用函数存储Option项IE                   */
    }

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}

/*******************************************************************************
  Module:      SM_ComDeActPdpCntxtAccCheck
  Function:    检查存储网侧发给MS的DEACTIVATE PDP CONTEXT ACCEPT消息的处理
  Input:       VOS_UINT8   *pMsg                      网侧消息
               VOS_UINT32   ulSmPduLen                 网侧消息长度
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  张志勇      2003.12.08   新规作成
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComDeActPdpCntxtAccCheck(
                                                     VOS_UINT8   *pMsg,             /* 网侧消息                                 */
                                                     VOS_UINT32   ulSmPduLen         /* 网侧消息长度                             */
                                              )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* 定义指针                                 */
    VOS_UINT8                              *tempMsg;                                /* 定义局部指针                             */
    VOS_UINT32                              ulSum;                                   /* 定义计数器                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* 申请内存                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComDeActPdpCntxtAccCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* 计数器初始值置0                          */
    tempMsg = pMsg;                                                             /* 指向网侧消息                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* 计数器小于消息长度                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_DEACT_PDP_CONTEXT_ACC,&tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* 调用函数存储Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* 释放申请的内存                           */
            return SM_NULL;                                                     /* 返回SM_NULL                              */
        }
    }
    else
    {                                                                           /* 消息长度错误                             */
        SM_Free(pMsgIE);                                                        /* 释放申请的内存                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComDeActPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* 返回SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* 忽略IE"消息类型",更新指针偏移,计数器加1  */

    return pMsgIE;                                                              /* 返回存储的结构体指针                     */
}
/*lint +e438 +e830*/

/*****************************************************************************
 函 数 名  : NAS_SM_ComMsgCheck
 功能描述  : 检查存储网侧发给MS的消息
 输入参数  : VOS_UINT8              ucMsgType   - 消息类型
             VOS_UINT32             ulPduLen    - 网侧消息长度
             VOS_UINT8              *pucMsg     - 网侧消息
 输出参数  : SM_NW_MSG_STRU         **ppstMsgIe - 存储网侧消息内容
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月9日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_SM_ComMsgCheck(
    VOS_UINT8                           ucMsgType,
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                           *pucMsg,
    SM_NW_MSG_STRU                      **ppstMsgIe
)
{
    VOS_UINT32                           ucStatus;

    ucStatus    = VOS_FALSE;
    *ppstMsgIe  = VOS_NULL_PTR;

    switch( ucMsgType )
    {
        case SM_REQ_PDP_CONTEXT_ACT:
            *ppstMsgIe = SM_ComReqPdpCntxtActMsgCheck(pucMsg, ulPduLen);
            break;

        case SM_ACT_PDP_CONTEXT_ACC:
            *ppstMsgIe = SM_ComActPdpCntxtAccCheck(pucMsg, ulPduLen);
            break;

        case SM_ACT_PDP_CONTEXT_REJ:
            *ppstMsgIe = SM_ComActPdpCntxtRejCheck(pucMsg, ulPduLen);
            break;

        case SM_ACT_SEC_PDP_CONTEXT_ACC:
            *ppstMsgIe = SM_ComActSecPdpCntxtAccCheck(pucMsg, ulPduLen);
            break;

        case SM_ACT_SEC_PDP_CONTEXT_REJ:
            *ppstMsgIe = SM_ComActSecPdpCntxtRejCheck(pucMsg, ulPduLen);
            break;

        case SM_MOD_PDP_CONTEXT_REQ_N2M:
            *ppstMsgIe = SM_ComModifyPdpCntxtReqCheck(pucMsg, ulPduLen);
            break;

        case SM_MOD_PDP_CONTEXT_ACC_N2M:
            *ppstMsgIe = SM_ComModifyPdpCntxtAccCheck(pucMsg, ulPduLen);
            break;

        case SM_MOD_PDP_CONTEXT_REJ:
            *ppstMsgIe = SM_ComModifyPdpCntxtRejCheck(pucMsg, ulPduLen);
            break;

        case SM_DEACT_PDP_CONTEXT_REQ:
            *ppstMsgIe = SM_ComDeActPdpCntxtReqCheck(pucMsg, ulPduLen);
            break;

        case SM_DEACT_PDP_CONTEXT_ACC:
            *ppstMsgIe = SM_ComDeActPdpCntxtAccCheck(pucMsg, ulPduLen);
            break;

        case SM_STATUS:
        default:
            /* SM_STATUS消息和其他错误消息不需要检查，直接置检查状态为VOS_TRUE */
            ucStatus = VOS_TRUE;
            break;
    }

    if (VOS_NULL_PTR != *ppstMsgIe)
    {
        ucStatus = VOS_TRUE;
    }

    return ucStatus;
}

/*****************************************************************************
 函 数 名  : NAS_SM_ValidNasMsg
 功能描述  : 检查L3消息，并获取SM消息类型和TI
 输入参数  : GMMSM_DATA_IND_STRU    *pRcvMsg    - 网侧消息
 输出参数  : VOS_UINT8              *pucMsgType - 消息类型
             VOS_UINT8              *pucTi      - TI值
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月9日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_SM_ValidNasMsg(
    GMMSM_DATA_IND_STRU                 *pRcvMsg,
    VOS_UINT8                           *pucMsgType,
    VOS_UINT8                           *pucTi
)
{
    GMMSM_DATA_IND_STRU                 *pGmmDataInd;

    pGmmDataInd = ( GMMSM_DATA_IND_STRU*) pRcvMsg;

    /* 检查消息类型是否存在 */
    /*--------------------------------------------------------------------------
      A L3 protocol may define that bits 5 to 8 of octet 1 of a standard L3
      message of the protocol contains the transaction identifier (TI). The
      extended TI shall not be used unless TI values of 7 or greater are needed.
      Refer to section 11.2.3.1.3 in TS 24.007
    --------------------------------------------------------------------------*/
    if (((0x70 == (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x70))
     && (2 == pGmmDataInd->SmMsg.ulNasMsgSize))
     || (2 > pGmmDataInd->SmMsg.ulNasMsgSize))
    {
        NAS_WARNING_LOG(WUEPS_PID_SM,
            "NAS_SM_ValidNasMsg:WARNING:NW->SM Message type non-existent or not implemented!");
        return VOS_FALSE;
    }

    if (0x70 == (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x70))
    {
        /* 检查TI扩展标志位，EXT flag (bit 8 of octet 2) 默认值为"1" */
        if (0x80 != (pGmmDataInd->SmMsg.aucNasMsg[1] & 0x80))
        {
            NAS_WARNING_LOG(WUEPS_PID_SM,
                "NAS_SM_ValidNasMsg:WARNING:NW->SM Invalid transaction identifier value!");
            return VOS_FALSE;
        }

        /* 获取消息类型和TI值 */
        /*-------------------------------------------------------------------
          Where the extended TI is used, the TI IE includes a second octet.
          The TI value in the first octet is ignored, and the TI value is
          encoded in bits 7-1 of the second octet.
          Refer to section 11.2.3.1.3 in TS 24.007
        -------------------------------------------------------------------*/
        *pucMsgType  = pGmmDataInd->SmMsg.aucNasMsg[2];
        *pucTi       = (pGmmDataInd->SmMsg.aucNasMsg[1] & 0x7F)
                     | (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x80);

        /* 记录TI有扩展标志 */
        g_ucTiExt   = VOS_TRUE;
    }
    else
    {
        /* 获取消息类型和TI值 */
        *pucMsgType  = pGmmDataInd->SmMsg.aucNasMsg[1];
        *pucTi       = (pGmmDataInd->SmMsg.aucNasMsg[0] & 0xF0) >> 4;
        *pucTi       = ((*pucTi & 0x08) << 4) | (*pucTi & 0x07);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_SM_RcvGmmSmDataInd
 功能描述  : 接收GMMSM_DATA_IND消息处理
 输入参数  : GMMSM_STATUS_IND_STRU      *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月25日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期  : 2013年03月13日
    作    者  : z00214637
    修改内容  : BodySAR项目

*****************************************************************************/
VOS_VOID NAS_SM_RcvGmmSmDataInd(
    GMMSM_DATA_IND_STRU                 *pstRcvMsg
)
{
    VOS_UINT8                           ucMsgType;
    VOS_UINT8                           ucTi;
    VOS_UINT32                          ucStatus;
    GMMSM_DATA_IND_STRU                 *pstGmmDataInd;
    SM_NW_MSG_STRU                      *pstMsgIe;

    pstGmmDataInd = (GMMSM_DATA_IND_STRU*)pstRcvMsg;
    pstMsgIe      = VOS_NULL_PTR;

    /* 检查L3消息，并获取SM消息类型和TI */
    ucStatus = NAS_SM_ValidNasMsg(pstGmmDataInd, &ucMsgType, &ucTi);
    if (VOS_FALSE == ucStatus)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvGmmSmDataInd:WARNING: Invalid message type or transaction identifier!");
        return;
    }

    /*Report DL message*/
    SM_ReportN2MOtaMsg(ucMsgType, &(pstGmmDataInd->SmMsg));


    /* 检查存储网侧发给MS的消息 */
    ucStatus = NAS_SM_ComMsgCheck(ucMsgType,
                            pstGmmDataInd->SmMsg.ulNasMsgSize,
                            pstGmmDataInd->SmMsg.aucNasMsg,
                            &pstMsgIe);
    if (VOS_TRUE == ucStatus)
    {
        switch( ucMsgType )
        {
            case SM_REQ_PDP_CONTEXT_ACT:
                SM_RcvNwReqPdpCntxtActMsg(pstMsgIe);
                break;

            case SM_ACT_PDP_CONTEXT_ACC:
                SM_RcvNwActPdpCntxtAccMsg(pstMsgIe);
                break;

            case SM_ACT_PDP_CONTEXT_REJ:
                SM_RcvNwActPdpCntxtRejMsg(pstMsgIe);
                break;

            case SM_ACT_SEC_PDP_CONTEXT_ACC:
                SM_RcvNwActSecPdpCntxtAccMsg(pstMsgIe);
                break;

            case SM_ACT_SEC_PDP_CONTEXT_REJ:
                SM_RcvNwActSecPdpCntxtRejMsg(pstMsgIe);
                break;

            case SM_MOD_PDP_CONTEXT_REQ_N2M:
                SM_RcvNwModifyPdpCntxtReqMsg(pstMsgIe);
                break;

            case SM_MOD_PDP_CONTEXT_ACC_N2M:
                SM_RcvNwModifyPdpCntxtAccMsg(pstMsgIe);
                break;

            case SM_MOD_PDP_CONTEXT_REJ:
                SM_RcvNwModifyPdpCntxtRejMsg(pstMsgIe);
                break;

            case SM_DEACT_PDP_CONTEXT_REQ:
                SM_RcvNwDeActPdpCntxtReqMsg(pstMsgIe);
                break;

            case SM_DEACT_PDP_CONTEXT_ACC:
                SM_RcvNwDeActPdpCntxtAccMsg(pstMsgIe);
                break;

            case SM_STATUS:
                SM_RcvStatusMsg(pstGmmDataInd);
                break;

            default:
                /* cause: "message type non-existent" */
                SM_SndStatusMsg(ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT);
                NAS_WARNING_LOG(WUEPS_PID_SM,
                    "NAS_SM_RcvGmmSmDataInd:WARNING: NW->SM Message type non-existent or not implemented!");
                break;
        }
    }
}

/*****************************************************************************
 函 数 名  : SM_RcvGmmSmEstabishCnf
 功能描述  : 接收GMMSM_ESTABLISH_CNF消息处理
 输入参数  : GMMSM_ESTABLISH_CNF_STRU           *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月09日
    作    者   : 郑伟
    修改内容   : 新生成函数

  2.日    期   : 2010年12月21日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010122305913，CS Only下PDP去激活后GMM在完成Detach前，
                 又发起PDP激活，导致SM在受到GMM的Detach指示后，做本地去激活

  3.日    期   : 2011年5月5日
    作    者   : c00173809
    修改内容   : 问题单号: DTS2011042804771,UE PPP拨号失败.在GPRS挂起时,用户PDP激活,
                 然后解挂后,RAU失败原因为9,SM重发PDP激活,GMM ATTACH失败,导致UE与PPP的
                 状态不一致.

  4.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  5.日    期   : 2015年1月12日
    作    者   : A00165503
    修改内容   : DTS2015011001363: PS域注册成功后, 处理缓存未释放内存
  6.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID SM_RcvGmmSmEstabishCnf(
    GMMSM_ESTABLISH_CNF_STRU           *pRcvMsg                                 /* 接收到的消息                             */
)
{
    VOS_UINT8                           i;
    MSG_HEADER_STRU                    *pHoldMsg;
    GMMSM_DATA_REQ_STRU                *ptemp = SM_NULL;                        /* 临时消息指针                             */
    VOS_UINT32                          ulTimerLen = 0;
    VOS_UINT8                           ucTimerType = 0;
    VOS_UINT8                           ucExpireTimes;
    VOS_UINT8                           ucAddrIndex;

    SM_TimerStop(SM_REGISTER_TIMER_ID);                                         /* 停止注册保护Timer                        */
    if( GMM_SM_EST_SUCCESS == pRcvMsg->ulEstResult )
    {                                                                           /* 注册成功                                 */
        g_SmEntity.ucRegisterFlg = SM_PS_REGISTERED;                            /* 设定注册标志为已经注册                   */
        for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
        {
            if( SM_NULL != g_SmEntity.aHoldMsg[i].pHoldRcvMsg )
            {                                                                   /* 存在缓存消息                             */
                pHoldMsg = (MSG_HEADER_STRU *)g_SmEntity.aHoldMsg[i].pHoldRcvMsg;
                switch( pHoldMsg->ulMsgName )
                {                                                               /* 消息类型                                 */
                case ID_SMREG_PDP_ACTIVATE_REQ:
                    NAS_SM_ProcTafPdpActiveReq((SMREG_PDP_ACTIVATE_REQ_STRU *)pHoldMsg);
                    break;
                case ID_SMREG_PDP_DEACTIVATE_REQ:
                    NAS_SM_ProcTafPdpDeActiveReq((SMREG_PDP_DEACTIVATE_REQ_STRU *)pHoldMsg);
                    break;
                default:
                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvGmmSmEstabishCnf:WARNING:SM: Message type non-existent!");
                   break;
                }

                SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);                    /* 释放保留消息                             */
                g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;                   /* 清除缓存消息：                           */
            }
            else if (SM_NULL != g_SmEntity.aPdpCntxtList[i].pHoldSndMsg)
            {
                ptemp = (GMMSM_DATA_REQ_STRU *)g_SmEntity.aPdpCntxtList[i].pHoldSndMsg;
                if ( SM_ACT_PDP_CONTEXT_REQ == *( (ptemp->SmMsg.aucNasMsg) + sizeof(VOS_UINT8)) )
                {
                    /* 如果存在缓存的SM_ACT_PDP_CONTEXT_REQ消息，则表示之前发生了激活过程中收到GMM去注册消息，
                       此时模拟收到GMMSM_REL_IND消息进行处理*/
                    if (SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
                    {
                        SM_T3380Expire(i);
                        ucTimerType = SM_TIMER_TYPE_T3380;
                        ulTimerLen  = SM_T3380_LENGTH;
                        /* 若定时器还处于开启状态，则需要重新启动，以便重新计时 */
                        if (SM_TIMER_STA_ON == g_SmEntity.aPdpCntxtList[i].TimerInfo.ucTimerStaFlg)
                        {
                            /* 保存ucExpireTimes,由于ucExpireTimes已经在超时处理函数中累加了，现在只许保存即可，无需累加 */
                            ucExpireTimes = g_SmEntity.aPdpCntxtList[i].TimerInfo.ucExpireTimes;

                            /* 停止并启动相应定时器 */
                            SM_TimerStop(i);
                            SM_TimerStart(i, ulTimerLen, ucTimerType);

                            /* 恢复ucExpireTimes */
                            g_SmEntity.aPdpCntxtList[i].TimerInfo.ucExpireTimes = ucExpireTimes;
                        }
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    else
    {                                                                           /* 注册失败                                 */
        NAS_MNTN_RecordPdpActiveFail(NAS_MNTN_ACTIVE_FAIL_TYPE_PS_SERVICE_UNAVAILABLE,
                                     0,                                         /* 此处可能不是唯一关联一个PDP上下文，该数值无效 */
                                     NAS_MNTN_SM_REJ_CAUSE_INVALID,
                                     g_SmEntity.ucRegisterFlg);

        g_SmEntity.ucRegisterFlg = SM_PS_NOTREGISTER;                           /* 设定注册标志为没有注册                   */
        for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
        {
            if( SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState )
            {
                ucAddrIndex = g_SmEntity.aPdpCntxtList[i].ucAddrIndex;
                SM_ComClearPdpCntxt(i);
                SM_SndTafSmPdpActivateRej(
                    g_SmEntity.aPdpCntxtList[i].ucCr,
                    NAS_SM_MapGmmCause(pRcvMsg->enCause),
                    VOS_NULL_PTR);

                SM_SndRabmSmDeactivateInd(1,&i);
                SM_ComClearPdpAddrApn(ucAddrIndex);
                g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_INACTIVE;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucCr] = 0xFF;
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucTi] = 0xFF;
            }
            else if( SM_NULL != g_SmEntity.aHoldMsg[i].pHoldRcvMsg )
            {                                                                   /* 存在缓存消息                             */
                pHoldMsg = (MSG_HEADER_STRU *)g_SmEntity.aHoldMsg[i].pHoldRcvMsg;
                switch( pHoldMsg->ulMsgName )
                {                                                               /* 消息类型                                 */
                case ID_SMREG_PDP_ACTIVATE_REQ:
                    SM_SndTafSmPdpActivateRej(
                        ((SMREG_PDP_ACTIVATE_REQ_STRU *)pHoldMsg)->ucConnectId,
                        NAS_SM_MapGmmCause(pRcvMsg->enCause),
                        VOS_NULL_PTR);                                          /* 回拒绝消息                               */
                    break;
                case ID_SMREG_PDP_DEACTIVATE_REQ:
                    SM_SndTafSmPdpDeActInd (
                        ((SMREG_PDP_DEACTIVATE_REQ_STRU *)pHoldMsg)->ucConnectId,
                        NAS_SM_MapGmmCause(pRcvMsg->enCause),
                        SM_FALSE);                                              /* 回拒绝消息                               */
                    break;
                default:
                    break;
                }

                SM_ComClearPdpCntxt(i);                                         /* 调用清除PDP实体的处理                    */
                SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);                    /* 释放保留消息                             */
                g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;                   /* 清除缓存消息                             */
            }
            else
            {

            }
        }

        NAS_SM_EndSession();

    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_SM_ProcGmmLteMoDetachInd
 功能描述  : 处理GMM的LTE去附着指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月10日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  3.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
  4.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID NAS_SM_ProcGmmLteMoDetachInd(VOS_VOID)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo = VOS_NULL_PTR;
    VOS_UINT8                           i;

    if (SM_PS_REGISTERED == NAS_SM_GET_REGISTER_FLG())
    {
        NAS_SM_SET_REGISTER_FLG(SM_PS_NOTREGISTER);

        for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
        {
            pstPdpCtxInfo = NAS_SM_GetPdpCtxInfoAddr(i);
            if (SM_PDP_ACTIVE_PENDING == pstPdpCtxInfo->ucState)
            {
                /* 通知TAF模块PDP激活失败 */
                SM_SndTafSmPdpActivateRej(pstPdpCtxInfo->ucCr,
                                          SM_TAF_CAUSE_GMM_PS_DETACH,
                                          VOS_NULL_PTR);

                /* SM实体状态置为INACTIVE */
                pstPdpCtxInfo->ucState = SM_PDP_INACTIVE;

                /* 清除TI, CR和NSAPI的映射 */
                NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);
                NAS_SM_ClearNsapiToCrMap(pstPdpCtxInfo->ucCr);

                /* 清除对应的PDP实体信息 */
                SM_ComClearPdpCntxt(i);
                SM_ComDelNsapiFromAddr(pstPdpCtxInfo->ucAddrIndex, i);

                /* 通知RABM更新承载状态 */
                SM_SndRabmSmDeactivateInd(1,&i);

                /* 通知GMM更新PDP状态 */
                NAS_SM_SndGmmPdpStatusInd();
            }
        }

        NAS_SM_EndSession();
    }
    else
    {
       ;
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : SM_RcvGmmSmStatusInd
 功能描述  : 接收GMMSM_STATUS_IND消息处理
 输入参数  : GMMSM_STATUS_IND_STRU         *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月09日
    作    者   : 郑伟
    修改内容   : 新生成函数

  2.日    期   : 2010年10月25日
    作    者   : z00161729
    修改内容   : CS Only情况,PDP去激活后,SM需要通过pdp_deactive_ind消息通知GMM进行detach

  3.日    期   : 2010年12月21日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010122305913，CS Only下PDP去激活后GMM在完成Detach前，
                 又发起PDP激活，导致SM在受到GMM的Detach指示后，做本地去激活

  4.日    期   : 2012-07-27
    作    者   : A00165503
    修改内容   : DTS2012072600458:cs ps mode 2 L下联合注册成功，用户detach ps disable lte
                 到W搜网成功cs注册成功，gmm 收到lmm的mo detach ind未通知sm当前detach状态，
                 导致后续ndis拨号sm没通知gmm attach拨号失败

  5.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2012080604402, PDP激活去激活后发生内存泄露

  6.日    期   : 2014年3月10日
    作    者   : A00165503
    修改内容   : DTS2014030708580: PDP激活过程中搜LTE, 上策下发PS域去附着请
                 求, LTE本地去附着后, SM状态维护异常, 没有终止PDP激活流程

  7.日    期   : 2014年05月05日
    作    者   : Y00213812
    修改内容   : 如果当前为正在注册状态需要停止定时器

  8.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  9.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
  10.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID SM_RcvGmmSmStatusInd(GMMSM_STATUS_IND_STRU *pRcvMsg)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNsapiNum;
    VOS_UINT8                           aucNspaiList[SM_MAX_NSAPI_NUM];
    VOS_UINT8                           ucActPending;                           /* 收到去注册消息时，使用该变量保存处于SM_PDP_ACTIVE_PENDING状态的PDP的个数 */
    VOS_UINT8                           ucAddrIndex;

    ucNsapiNum = 0;
    ucActPending = 0;

#if (FEATURE_ON == FEATURE_LTE)
    if ( (GMM_SM_STATUS_DETACHED == pRcvMsg->ulGmmStatus )
      && (GMM_SM_CAUSE_LTE_MO_DETACH == pRcvMsg->enCause) )
    {
        NAS_SM_ProcGmmLteMoDetachInd();
        return;
    }
#endif

    if ( (GMM_SM_STATUS_DETACHED == pRcvMsg->ulGmmStatus )
      || (GMM_SM_SER_REJ_CAUSE_PDP_NOEXIT == pRcvMsg->ulGmmStatus) )
    {                                                                           /* 状态为detached                           */
        SM_TimerStop(SM_REGISTER_TIMER_ID);                                     /* 停止注册保护Timer                        */

        if (GMM_SM_STATUS_DETACHED == pRcvMsg->ulGmmStatus)
        {
            g_SmEntity.ucRegisterFlg = SM_PS_NOTREGISTER;                       /* 设定注册标志为没有注册                   */
        }
        else
        {
            g_SmEntity.ucRegisterFlg = SM_PS_REGISTERED;                        /* 设定注册标志为没有注册                   */
        }

        g_SmPdpAddrApn.usPdpAddrFlg = 0;                                        /* 清除usPdpAddrFlg                         */
        SM_MemSet(g_TiMapToNsapi, (VOS_CHAR)0xff, 256);                                   /* 初始化g_TiMapToNsapi[]                   */
        SM_MemSet(g_CrMapToNsapi, (VOS_CHAR)0xff, 256);                                   /* 初始化g_CrMapToNsapi[]                   */

        for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
        {
            if (SM_PDP_INACTIVE != g_SmEntity.aPdpCntxtList[i].ucState)
            {                                                                   /* 当前的状态为SM_PDP_INACTIVE              */
                if ( (SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
                  && (GMM_SM_STATUS_DETACHED == pRcvMsg->ulGmmStatus) )
                {
                    ucActPending++;
                    ucAddrIndex = g_SmEntity.aPdpCntxtList[i].ucAddrIndex;

                    /*在for循环之前已经将如下全局变量统一清了一次，在该分支中需还原这些全局变量的值*/
                    g_SmPdpAddrApn.usPdpAddrFlg |= (VOS_UINT16)((VOS_UINT32)0x0001<<ucAddrIndex);
                    g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucTi] = i;
                    g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucCr] = i;
                }
                else
                {
                    SM_TimerStop(i);
                    SM_SndTafSmPdpDeActInd(
                        g_SmEntity.aPdpCntxtList[i].ucCr,
                        NAS_SM_MapGmmCause(pRcvMsg->enCause),
                        SM_FALSE);                                                  /* 向TAF发送去激活请求                      */
                    aucNspaiList[ucNsapiNum] = i;                                   /* 记录去激活的NSAPI                        */
                    ucNsapiNum++;                                                   /* 去激活NSAPI个数加1                       */

                    SM_ComClearPdpCntxt(i);                                         /* 调用清除PDP实体的处理                    */

                    SM_ComDelNsapiFromAddr(g_SmEntity.aPdpCntxtList[i].ucAddrIndex, i);

                    g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_INACTIVE;          /* 状态切换到SM_PDP_INACTIVE                */

                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvGmmSmStatusInd:NORMAL:SM state = SM_PDP_INACTIVE");

                    NAS_SM_SndGmmPdpStatusInd();
                }
            }

            if (SM_NULL != g_SmEntity.aHoldMsg[i].pHoldRcvMsg)
            {
                SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);
                g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;
            }
        }
        if (ucNsapiNum > 0)
        {
            SM_SndRabmSmDeactivateInd (ucNsapiNum, aucNspaiList);               /* 通知RABM去激活所有Nsapi                  */
        }

        if (ucActPending > 0)
        {
            NAS_SM_SndGmmEstablishReq();                                            /* 送注册请求                               */
            SM_TimerStart(SM_REGISTER_TIMER_ID,SM_T0001_LENGTH
                ,SM_TIMER_TYPE_T0001);                                          /* 启动注册保护Timer                        */
            g_SmEntity.ucRegisterFlg = SM_PS_REGISTERING;
        }
        else
        {
            if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg )
            {
                NAS_SM_SndGmmPdpDeactivatedInd();                                   /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */
            }
        }

        NAS_SM_EndSession();

    }
    else
    {
        g_SmEntity.ucRegisterFlg = SM_PS_REGISTERED;                            /* 设定注册标志为已经注册                   */

        SM_TimerStop(SM_REGISTER_TIMER_ID);
    }
    return;
}


/*******************************************************************************
  Module:   SM_RcvGmmSmServiceRej
  Function: 接收GMMSM_SERVICE_REJ消息处理
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1.   L47619  2007.10.27   Create function
  2. 日    期  : 2009年3月11日
     作    者  : ouyangfei 00132663
     修改内容  : 根据问题单号：AT2D09927，如果PS域不可用，回复SM SERVICE REJ，
                 中止当前请求，避免SM启定时器，重复发起请求。

  3.日    期   : 2010年10月25日
    作    者   : z00161729
    修改内容   : CS Only情况,PDP去激活后,SM需要通过pdp_deactive_ind消息通知GMM进行detach

  4.日    期   : 2012年03月05日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012022405416，G下正常驻留，发起PDP MOD REQ,
                 PDP修改完成异系统到W下，PS被BAR，SM没有GMM的处理拒绝消息

  5.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源
  6.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_RcvGmmSmServiceRej(GMMSM_SERVICE_REJ_STRU  *pRcvMsg)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucPdpUpdateFlg;

    ucPdpUpdateFlg = VOS_FALSE;

    for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        if(SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
        {                                                                       /* 当前的状态为SM_PDP_ACTIVE_PENDING */
            ucAddrIndex = g_SmEntity.aPdpCntxtList[i].ucAddrIndex;

            SM_SndTafSmPdpActivateRej(
                g_SmEntity.aPdpCntxtList[i].ucCr,
                NAS_SM_MapGmmCause(pRcvMsg->enCause),
                VOS_NULL_PTR);

            SM_ComClearPdpCntxt(i);                                             /* 调用清除PDP实体的处理 */
            SM_SndRabmSmDeactivateInd(1, &i);
            ucPdpUpdateFlg = VOS_TRUE;
            SM_ComClearPdpAddrApn(ucAddrIndex);                                 /* 清除Addr Apn实体                         */
            g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_INACTIVE;              /* 状态切换到SM_PDP_INACTIVE */
            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucCr]=0xff;              /* 维护g_CrMapToNsapi */
            g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucTi]=0xff;              /* 维护g_TiMapToNsapi */
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvGmmSmServiceRej:NORMAL:SM state = SM_PDP_INACTIVE");
        }
        else if(SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
        {
            /* 释放备份的消息 */
            SM_Free(g_SmEntity.aPdpCntxtList[i].pHoldSndMsg);
            g_SmEntity.aPdpCntxtList[i].pHoldSndMsg = SM_NULL;

            /* 停止该实体的TIMER */
            SM_TimerStop(i);

            /* 向TAF回拒绝消息 */
            SM_SndTafSmPdpModifyRej(
                NAS_SM_MapGmmCause(pRcvMsg->enCause),
                g_SmEntity.aPdpCntxtList[i].ucCr);

            /* 状态切换到SM_PDP_ACTIVE */
            g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_ACTIVE;
        }
        else
        {
            ;
        }
    }

    if ((VOS_TRUE == ucPdpUpdateFlg) && (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg))
    {
        NAS_SM_SndGmmPdpDeactivatedInd();                                       /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */
    }

    NAS_SM_EndSession();


    return;
}


/*******************************************************************************
  Module:   SM_RcvGmmSysInfoInd
  Function: 接收GMMSM_SYS_INFO_IND_STRU消息处理
  Input:    GMMSM_SYS_INFO_IND_STRU *pRcvMsg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. L47619  2009.05.06   Create function
  2.日    期   : 2010年10月25日
    作    者   : z00161729
    修改内容   : CS Only情况,PDP去激活后,SM需要通过pdp_deactive_ind消息通知GMM进行detach

  3.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  4.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
  5.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_RcvGmmSysInfoInd(GMMSM_SYS_INFO_IND_STRU *pRcvMsg)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucPdpStatusFlag;

    ucPdpStatusFlag = VOS_FALSE;

    switch (pRcvMsg->ucSgsnRelVer)
    {
        case GMMSM_SGSN_RELEASE98_OR_OLDER:
            if (GMMSM_SGSN_RELEASE99_ONWARDS == g_SmSgsnVersion)
            {
                /* 23.060，TDoc: SP-020604, CR:385 － 扩展TI的处理
                     23.060, TDoc: SP-020768, CR:402 － MAX UL =0 && MAX DL =0 的处理*/
                for(ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
                {
                    if (SM_PDP_INACTIVE != g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
                    {
                        if ( ( (g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi & 0x7F) >= 0x7)
                            || ( (0 == g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue[5])
                              && (0 == g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue[6]) ) )
                        {
                            /* 执行本地去激活操作 */
                            ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;
                            if( SM_PDP_INACTIVE_PENDING
                                == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
                            {                                                                   /* 状态为SM_PDP_INACTIVE_PENDING            */
                                NAS_SM_NORM_LOG("SM_RcvGmmSysInfoInd:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE ");
                                SM_TimerStop(ucCntxtIndex);                                     /* 停止T3390                                */
                                SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);    /* 释放备份的消息                           */
                                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                                SM_SndTafSmPdpDeActCnf(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);          /* 向TAF回响应消息                          */
                                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                                    = SM_PDP_INACTIVE;                                          /* 状态切换到SM_PDP_INACTIVE                */
                                ucPdpStatusFlag = VOS_TRUE;
                            }
                            else
                            {
                                NAS_SM_NORM_LOG("SM_RcvGmmSysInfoInd:NORMAL: SM state = SM_PDP_INACTIVE");
                                SM_SndRabmSmDeactivateInd (1, &ucCntxtIndex);                   /* 通知RABM去激活Nsapi                      */
                                SM_SndTafSmPdpDeActInd(
                                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                                    SM_TAF_CAUSE_SM_SGSN_VER_PRE_R99,
                                    SM_FALSE);                                                  /* 通知TAF去激活                            */
                                SM_ComClearPdpCntxt(ucCntxtIndex);                              /* 释放实体                                 */
                                SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);               /* 从PDP Addr and Apn实体中删除Nsapi        */
                                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                                    = SM_PDP_INACTIVE;                                          /* 状态切换到SM_PDP_INACTIVE                */

                                NAS_SM_SndGmmPdpStatusInd();
                                ucPdpStatusFlag = VOS_TRUE;
                            }
                            g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xFF;                                /* 维护g_TiMapToNsapi                       */
                            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF; /* 维护g_CrMapToNsapi                       */
                        }
                    }
                }

                if ((VOS_TRUE == ucPdpStatusFlag) && (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg))
                {
                    NAS_SM_SndGmmPdpDeactivatedInd();                           /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */
                }
            }

            NAS_SM_EndSession();

            /* 更新SGSN版本信息 */
            g_SmSgsnVersion = GMMSM_SGSN_RELEASE98_OR_OLDER;
            break;
        case GMMSM_SGSN_RELEASE99_ONWARDS:
            /* 更新SGSN版本信息 */
            g_SmSgsnVersion = GMMSM_SGSN_RELEASE99_ONWARDS;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvGmmSysInfoInd:WARNING:ucSgsnRelVer is abnormal!");
            break;
    }

    return;
}


/*******************************************************************************
  Module:   SM_RcvGmmSmPdpStatusInd
  Function: 接收GMMSM_PDP_STATUS_IND消息处理
  Input:    GMMSM_PDP_STATUS_IND_STRU *pRcvMsg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. L47619  2007.10.27   Create function

  2.日    期   : 2010年10月25日
    作    者   : z00161729
    修改内容   : CS Only情况,PDP去激活后,SM需要通过pdp_deactive_ind消息通知GMM进行detach

  3.日    期   : 2012年3月17日
    作    者   : z00161729
    修改内容   : V7R1C50支持ISR修改

  4.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  5.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*******************************************************************************/
VOS_VOID SM_RcvGmmSmPdpStatusInd(GMMSM_PDP_STATUS_IND_STRU *pRcvMsg)
{
    VOS_UINT8       i;
    VOS_UINT32      ulPdpContextStatus;
    VOS_UINT8       ucPdpStatusFlag;

    ucPdpStatusFlag = VOS_FALSE;

    for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        ulPdpContextStatus = pRcvMsg->aucPdpContextStatus[i];

        if ( 0 == ulPdpContextStatus )  /*网侧指示PDP context状态为INACTIVE*/
        {
            if( (SM_PDP_INACTIVE != g_SmEntity.aPdpCntxtList[i].ucState)
                 && (SM_PDP_ACTIVE_PENDING != g_SmEntity.aPdpCntxtList[i].ucState) )
            {                                                                   /* 当前的状态不是SM_PDP_INACTIVE              */
                SM_TimerStop(i);
                SM_SndTafSmPdpDeActInd(
                    g_SmEntity.aPdpCntxtList[i].ucCr,
                    NAS_SM_MapGmmCause(pRcvMsg->enCause),
                    SM_FALSE);                                                  /* 向TAF发送去激活请求                      */
                SM_ComClearPdpCntxt(i);                                         /* 调用清除PDP实体的处理                    */
                SM_ComDelNsapiFromAddr(g_SmEntity.aPdpCntxtList[i].ucAddrIndex, i);
                SM_SndRabmSmDeactivateInd(1,&i);
                g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_INACTIVE;          /* 状态切换到SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvGmmSmPdpStatusInd:NORMAL:SM state = SM_PDP_INACTIVE");

                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucTi] = 0xff;        /* 维护g_TiMapToNsapi                       */
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucCr] = 0xff;        /* 维护g_CrMapToNsapi                       */

                ucPdpStatusFlag = VOS_TRUE;
            }
        }
        else
        {
            if( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState)
            {
                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                      "SM_RcvGmmSmPdpStatusInd:WARNING:SM state = SM_PDP_INACTIVE,But Network Indicate PDP STATUS = ACTIVE!!");
            }
            else if( SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
            {
                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                      "SM_RcvGmmSmPdpStatusInd:WARNING:SM state = SM_PDP_ACTIVE_PENDING,But Network Indicate PDP STATUS = ACTIVE!!");
            }
            else
            {
            }
        }

    }

    if( VOS_TRUE == ucPdpStatusFlag )
    {
        NAS_SM_SndGmmPdpStatusInd();
        NAS_SM_SndGmmPdpDeactivatedInd();
    }

    NAS_SM_EndSession();

    return;
}

/*******************************************************************************
  Module:   SM_RcvGmmRelInd
  Function: 接收GMMSM_REL_IND消息处理
  Input:    GMMSM_REL_IND_STRU *pRcvMsg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   L47619  2009.07.23   Create function
*******************************************************************************/
VOS_VOID SM_RcvGmmRelInd(GMMSM_REL_IND_STRU *pRcvMsg)
{
    VOS_UINT8           ucCntxtIndex;
    VOS_UINT32          ulTimerLen = 0;
    VOS_UINT8           ucTimerType = 0;
    VOS_UINT8           ucFlag;
    VOS_UINT8           ucExpireTimes;

    /* 收到GMMSM_REL_IND消息，将之等同于超时消息进行相应处理(注意:需要重启定时器)
        否则若仅重发消息而不累加ucExpireTimes的话，在如下情况下，有可能导致死循环:
        PDP激活请求发送给网络后，PS信令连接被释放 */
    for(ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
    {
        ucFlag = VOS_FALSE;

        switch(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {
            case SM_PDP_ACTIVE_PENDING:
                SM_T3380Expire(ucCntxtIndex);
                ucTimerType = SM_TIMER_TYPE_T3380;
                ulTimerLen  = SM_T3380_LENGTH;
                ucFlag = VOS_TRUE;
                break;
            case SM_PDP_MODIFY_PENDING:
                SM_T3381Expire(ucCntxtIndex);
                ucTimerType = SM_TIMER_TYPE_T3381;
                ulTimerLen  = SM_T3381_LENGTH;
                ucFlag = VOS_TRUE;
                break;
            case SM_PDP_INACTIVE_PENDING:
                SM_T3390Expire(ucCntxtIndex);
                ucTimerType = SM_TIMER_TYPE_T3390;
                ulTimerLen  = SM_T3390_LENGTH;
                ucFlag = VOS_TRUE;
                break;
            default :
                /* 其他状态下，无需处理该消息 */
                break;
        }

        if (VOS_TRUE == ucFlag)
        {
            /* 若定时器还处于开启状态，则需要重新启动，以便重新计时 */
            if (SM_TIMER_STA_ON == g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucTimerStaFlg)
            {
                /* 保存ucExpireTimes,由于ucExpireTimes已经在超时处理函数中累加了，现在只许保存即可，无需累加 */
                ucExpireTimes = g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes;

                /* 停止并启动相应定时器 */
                SM_TimerStop(ucCntxtIndex);
                SM_TimerStart(ucCntxtIndex, ulTimerLen, ucTimerType);

                /* 恢复ucExpireTimes */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = ucExpireTimes;
            }
        }
    }
}


/*******************************************************************************
  Module:   SM_RcvNwReqPdpCntxtActMsg
  Function: 接收REQUEST PDP CONTEXT ACTIVATION消息的处理
  Input:    SM_NW_MSG_STRU     *pMsgIe
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1.郑 伟   2003.12.09   新规作成
  2.日    期   : 2012年8月25日
    作    者   : m00217266
    修改内容   : 修改接口SM_SndTafSmPdpDeActInd原因值类型,修改上报错误码

  3.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*******************************************************************************/
VOS_VOID SM_RcvNwReqPdpCntxtActMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8       i;
    VOS_UINT8       ucCollisionFlg;
    VOS_UINT8       ucPdpActiveFlg;
    VOS_UINT8       ucTi;
    VOS_UINT8       ucCntxtIndex;
    VOS_UINT8       ucCntxtIndex2;
    VOS_UINT8       ucApnAddrFlg = SM_FALSE;  /*A32D00461,zzy,pclint*/                                                  /* 标识是否是APN&PDP addr冲突               */
    VOS_UINT8       ucCollisionFlg2;                                                /* 标识是否与已存在的APN&PDP addr相同       */
    VOS_UINT8       ucCntxtIndex3;                                                  /* 发生ucCollisionFlg2指示冲突对应实体索引  */
    VOS_UINT8       ucAddrIndex;
    VOS_UINT8       ucInitType;

    ucTi                = (VOS_UINT8)(pMsgIe->ucTi & 0x7F);                         /* 取TI的实际值                             */
    ucCollisionFlg      = SM_FALSE;                                             /* 初始化为False                            */
    ucPdpActiveFlg      = SM_FALSE;                                             /* 初始化为False                            */
    ucCntxtIndex        = SM_MAX_NSAPI_NUM;
    ucCollisionFlg2     = SM_FALSE;                                             /* 初始化为无效值                           */
    ucCntxtIndex2       = SM_MAX_NSAPI_NUM;                                     /* 初始化为无效值                           */
    ucCntxtIndex3       = SM_MAX_NSAPI_NUM;                                     /* 初始化为无效值                           */
    ucAddrIndex         = SM_MAX_NSAPI_NUM;                                     /* 初始化为无效值                           */

    ucInitType = ACTIVE_REQUEST_INIT_TYPE_MT;
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_ACTIVE_REQ,
                    (VOS_VOID *)&ucInitType,
                    NAS_OM_EVENT_PDP_ACTIVE_REQ_LEN);
    if( pMsgIe->PdpAddr.ucLen > 2 )
    {                                                                           /* PDP addr为静态地址                       */
        for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
        {
            if( SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
            {                                                                   /* 当前的状态为SM_PDP_ACTIVE_PENDING        */
                if(0 == pMsgIe->Apn.ucLen)
                {
                    SM_SndReqPdpActRejMsg(SM_NULL, ucTi);                       /* 回拒绝消息                               */
                    ucCollisionFlg = SM_TRUE;                                   /* 设定ucCollisionFlg为True                 */
                    break;
                }
                ucCollisionFlg = SM_RcvNwReqPdpCnxtActMsg_S01(pMsgIe, i, ucTi);
                if(SM_TRUE == ucCollisionFlg)
                {
                    break;
                }
            }
            else if( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState )
            {                                                                   /* 状态为SM_PDP_INACTIVE                    */
                ucCntxtIndex = i;
                break;
            }
            else
            {                                                                   /* 状态为SM_PDP_ACTIVE                      */
                if(pMsgIe->ucTi == g_SmEntity.aPdpCntxtList[i].ucTi )
                {                                                               /* 指定的Ti与该实体的Ti相同                 */
                    ucPdpActiveFlg = SM_TRUE;                                   /* ucPdpActiveFlg设定为True                 */
                    ucCntxtIndex2 = i;                                          /* 记录实体的索引                           */
                }
                else
                {
                    ucCollisionFlg2
                        = SM_RcvNwReqPdpCnxtActMsg_S01(pMsgIe, i, ucTi);        /* 比较APN&PDP addr是否发生冲突             */
                    if( SM_TRUE == ucCollisionFlg2 )
                    {                                                           /* 发生冲突                                 */
                        ucApnAddrFlg = SM_TRUE;                                 /* ucApnAddrFlg设定为发生冲突               */
                        ucCntxtIndex3 = i;                                      /* 记录实体的索引                           */
                    }
                }
            }
        }
        if( SM_FALSE == ucCollisionFlg )
        {                                                                       /* 没有发生冲突                             */
            if( (SM_TRUE == ucPdpActiveFlg) || (SM_TRUE == ucApnAddrFlg) )
            {                                                                   /* 激活状态                                 */
                if( (SM_TRUE == ucPdpActiveFlg) && (SM_TRUE == ucApnAddrFlg) && (ucCntxtIndex2 < SM_MAX_NSAPI_NUM))
                {                                                               /* Ti已使用且APN&PDP addr与另一个PDP
                                                                                 * context 相同的情况                       */
                    ucAddrIndex
                        = g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucAddrIndex;
                    SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex2);               /* 通知RABM去激活Nsapi                      */
                    SM_SndTafSmPdpDeActInd(
                                g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucCr,
                                SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,
                                SM_FALSE);                                      /* 通知TAF去激活                            */
                    SM_ComClearPdpCntxt(ucCntxtIndex2);
                    SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex2);
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucState
                        = SM_PDP_INACTIVE;                                      /* 状态切换到SM_PDP_INACTIVE                */

                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, ":NORMAL: SM state = SM_PDP_INACTIVE");
                    g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucTi]
                         = 0xFF;
                    g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucCr]
                         = 0xFF;

                    NAS_SM_SndGmmPdpStatusInd();

                    SM_RcvNwReqPdpCnxtActMsg_S02(pMsgIe, ucCntxtIndex3);
                }
                else
                {
                    if(SM_TRUE == ucApnAddrFlg)
                    {
                        ucCntxtIndex2 = ucCntxtIndex3;
                    }
                    SM_RcvNwReqPdpCnxtActMsg_S02(pMsgIe, ucCntxtIndex2);
                }
            }
            else
            {
                if( SM_MAX_NSAPI_NUM == ucCntxtIndex )
                {                                                               /* 如果没有找到                             */
                    SM_SndReqPdpActRejMsg(SM_NULL,ucTi);                        /* 回拒绝消息                               */
                }
                else
                {
                    SM_RcvNwReqPdpCnxtActMsg_S00(pMsgIe,ucCntxtIndex);          /* SM_PDP_INACTIVE状态接收此消息的处理      */
                }
            }
        }
        else
        {   /*终端发现终端已经使用该参数发起了PDP激活，并处于ACT_PENDING状态,
            则抛弃该网络的激活指示*/
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "SM_RcvNwReqPdpCntxtActMsg Discard ACT_IND_MSG ");
        }
    }
    else
    {                                                                           /* 动态地址                                 */
        if( 0xFF == g_TiMapToNsapi[pMsgIe->ucTi] )
        {                                                                       /* 状态为SM_PDP_INACTIVE                    */
            for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
            {
                if( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState )
                {                                                               /* 当前的状态为SM_PDP_ACTIVE_PENDING        */
                    SM_RcvNwReqPdpCnxtActMsg_S00(pMsgIe, i);
                    break;
                }
            }
            if( SM_MAX_NSAPI_NUM == i )
            {                                                                   /* 如果没有找到                             */
                SM_SndReqPdpActRejMsg(SM_NULL, ucTi);                           /* 回拒绝消息                               */
            }
        }
        else
        {
            SM_RcvNwReqPdpCnxtActMsg_S02(pMsgIe, g_TiMapToNsapi[pMsgIe->ucTi]);
        }
    }
    SM_Free(pMsgIe);                                                            /* 释放内存                                 */
    return;
}

/*****************************************************************************
 函 数 名  : SM_RcvNwActPdpCntxtAccMsg
 功能描述  : 接收ACTIVATE PDP CONTEXT ACCEPT消息的处理
 输入参数  : SM_NW_MSG_STRU     *pMsgIe
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月10日
    作    者   : 郑 伟
    修改内容   : 新生成函数

  2.日    期   : 2010年11月10日
    作    者   : A00165503
    修改内容   : 问题单号:DTS2010101601395，SM-STATUS报给网侧的原因值错误

  3.日    期   : 2010年11月10日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011012600147，UE连续发送两条PDP激活请求给网侧，
                 网侧连续下发两条PDP ACTIVATE ACCEPT消息，且消息中的IP地址不
                 同，有可能导致无法数传

  4.日    期   : 2012年04月09日
    作    者   : s62952
    修改内容   : 问题单号:DTS2012031904228

  5.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  6.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*****************************************************************************/
VOS_VOID SM_RcvNwActPdpCntxtAccMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_BOOL                            bResult;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* 根据TI获取ucCntxtIndex                   */
    if ( 0xFF == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);             /* 向network回SM STATUS消息#98             */

        NAS_SM_SndGmmPdpDeactivatedInd();
    }
    else if ( SM_PDP_ACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {
        SM_TimerStop(ucCntxtIndex);                                             /* 停止T3380                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* 释放备份的消息                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri = pMsgIe->ucRadioPri; /* 存储ucRadioPri                           */
        if (0 != pMsgIe->PdpAddr.ucLen)
        {                                                                       /* 存在PDP addr                             */
            ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;   /* 获得addr索引                             */
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength
                = pMsgIe->PdpAddr.ucLen;                                        /* 存储PDP addr长度                         */
            SM_MemCpy(
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
                pMsgIe->PdpAddr.pValue,
                pMsgIe->PdpAddr.ucLen);                                         /* 存储PDP addr                             */
        }

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = (pMsgIe->Qos.ucLen <= sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue)) ?
              (pMsgIe->Qos.ucLen) : (sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pMsgIe->Qos.pValue,
                   g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);     /* 更新Qos                                  */
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_2);                /* 通知RABM激活Nsapi                        */
        SM_SndTafSmPdpActivateCnf(pMsgIe, ucCntxtIndex);                        /* 向TAF回响应消息                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* 状态切换到SM_PDP_ACTIVE                  */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwActPdpCntxtAccMsg:NORMAL: SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_ACTIVE");
        NAS_SM_SndGmmPdpStatusInd();
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_ACTIVE_SUCC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }
    else
    {
        /*置暂存标识为无效*/
        g_aucSapi[0][0] = 0;

        /* 向network回SM STATUS消息#98 */
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);

        if (SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {
            ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

            bResult = NAS_SM_ComparePdpAddr(&pMsgIe->PdpAddr,
                                            &g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo);
            if (VOS_FALSE == bResult)
            {
                /*----------------------------------------------------------------
                  收到重复的 PDP Activate Accept 消息，此时数据业务已经使用第一
                  条消息中的 PDP Address，而网侧可能会使用此消息中的 PDP Address，
                  PPP模块或NDIS模块与PC侧的协商一旦完成就不可能再次协商，有可能
                  导致数据业务不可用，唯一的解决办法是本地去激活该 PDP
                ----------------------------------------------------------------*/
                SM_SndTafSmPdpDeActInd(
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                    SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,
                    SM_FALSE);

                /* 清除PDP实体 */
                SM_ComClearPdpCntxt(ucCntxtIndex);
                SM_ComDelNsapiFromAddr(ucAddrIndex, ucCntxtIndex);
                SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;

                NAS_NORMAL_LOG(WUEPS_PID_SM,
                    "SM_RcvNwActPdpCntxtAccMsg:NORMAL:SM state = SM_PDP_INACTIVE");

                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xFF;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF;

                NAS_SM_SndGmmPdpStatusInd();
                NAS_SM_SndGmmPdpDeactivatedInd();
            }
        }
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}

/*****************************************************************************
 函 数 名  : SM_RcvNwActPdpCntxtRejMsg
 功能描述  : 接收ACTIVATE PDP CONTEXT REJECT消息的处理
 输入参数  : SM_NW_MSG_STRU     *pMsgIe
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月10日
    作    者   : 郑 伟
    修改内容   : 新生成函数

  2.日    期   : 2010年10月25日
    作    者   : z00161729
    修改内容   : CS Only情况,PDP去激活后,SM需要通过pdp_deactive_ind消息通知GMM进行detach

  3.日    期   : 2010年11月10日
    作    者   : A00165503
    修改内容   : 问题单号:DTS2010101601395，SM-STATUS报给网侧的原因值错误

  4.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源
*****************************************************************************/
VOS_VOID SM_RcvNwActPdpCntxtRejMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    SM_OCT_VARY_STRU                   *pProtCfgOpt;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* 根据TI获取ucCntxtIndex                   */
    pProtCfgOpt         = SM_NULL;
    if( 0xFF == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* 向network回SM STATUS消息#81              */
    }
    else if( SM_PDP_ACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {
        NAS_MNTN_RecordPdpActiveFail(NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_REJECT,
                                     ucCntxtIndex,
                                     pMsgIe->SmCause,
                                     g_SmEntity.ucRegisterFlg);

        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;       /* 获得ucAddrIndex                          */
        SM_ComClearPdpCntxt(ucCntxtIndex);                                      /* 释放实体                                 */
        if( 0 != pMsgIe->ProCnfgOpt.ucLen )
        {                                                                       /* 存在数据                                 */
            pProtCfgOpt = (SM_OCT_VARY_STRU*)(&pMsgIe->ProCnfgOpt);
        }

        SM_SndTafSmPdpActivateRej(
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
            NAS_SM_MapSmNWCause(pMsgIe->SmCause),
            pProtCfgOpt );

        SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                            /* 通知RABM去激活                           */
        SM_ComClearPdpAddrApn(ucAddrIndex);                                     /* 清除Addr Apn实体                         */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* 状态切换到SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwActPdpCntxtRejMsg:NORMAL:SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_INACTIVE");
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;     /* 维护g_CrMapToNsapi                       */
        g_TiMapToNsapi[pMsgIe->ucTi] = 0xff;                                    /* 维护g_TiMapToNsapi                       */
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL,
                        (VOS_VOID *)&(pMsgIe->SmCause),
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL_LEN);
        if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
        {
            NAS_SM_SndGmmPdpDeactivatedInd();                                   /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */
        }

    }
    else
    {
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);               /* 向network回SM STATUS消息#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}

/*****************************************************************************
 函 数 名  : SM_RcvNwActSecPdpCntxtAccMsg
 功能描述  : 接收ACTIVATE SECONDARY PDP CONTEXT ACCEPT消息的处理
 输入参数  : SM_NW_MSG_STRU     *pMsgIe
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月10日
    作    者   : 郑 伟
    修改内容   : 新生成函数

  2.日    期   : 2010年11月10日
    作    者   : A00165503
    修改内容   : 问题单号:DTS2010101601395，SM-STATUS报给网侧的原因值错误

  3.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  4.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*****************************************************************************/
VOS_VOID SM_RcvNwActSecPdpCntxtAccMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8                           ucCntxtIndex;

    ucCntxtIndex = g_TiMapToNsapi[pMsgIe->ucTi];                                /* 根据TI获取ucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
         g_aucSapi[0][0] = 0;
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* 向network回SM STATUS消息#81              */
         NAS_SM_SndGmmPdpDeactivatedInd();
    }
    else if( SM_PDP_ACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {
        NAS_SM_NORM_LOG("SM_RcvNwActSecPdpCntxtAccMsg: SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_ACTIVE");

        SM_TimerStop(ucCntxtIndex);                                             /* 停止T3380                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* 释放备份的消息                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri = pMsgIe->ucRadioPri; /* 存储ucRadioPri                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = (pMsgIe->Qos.ucLen <= sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue)) ?
              (pMsgIe->Qos.ucLen) : (sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pMsgIe->Qos.pValue,
                   g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);     /* 更新Qos                                  */
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_2);                /* 通知RABM激活Nsapi                        */
        SM_SndTafSmPdpActSecCnf(pMsgIe,ucCntxtIndex);                           /* 向TAF回响应消息                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* 状态切换到SM_PDP_ACTIVE                  */

        NAS_SM_SndGmmPdpStatusInd();
    }
    else
    {
        g_aucSapi[0][0] = 0;
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE); /* 向network回SM STATUS消息#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);                                                            /* 释放内存                                 */
    return;
}

/*****************************************************************************
 函 数 名  : SM_RcvNwActSecPdpCntxtRejMsg
 功能描述  :
 输入参数  : SM_NW_MSG_STRU     *pMsgIe
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月10日
    作    者   : 郑 伟
    修改内容   : 新生成函数

  2.日    期   : 2010年11月10日
    作    者   : A00165503
    修改内容   : 问题单号:DTS2010101601395，SM-STATUS报给网侧的原因值错误

  3.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源
*****************************************************************************/
VOS_VOID SM_RcvNwActSecPdpCntxtRejMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8       i,j;
    VOS_UINT8       ucCntxtIndex;
    VOS_UINT8       ucAddrIndex;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* 根据TI获取ucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
         SM_SndStatusMsg(pMsgIe->ucTi,TAF_SM_REJ_CAUSE_INVALID_TI);             /* 向network回SM STATUS消息#81              */
    }
    else if( SM_PDP_ACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* 状态为SM_PDP_ACTIVE_PENDING              */
        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;       /* 获得ucAddrIndex                          */
        SM_ComClearPdpCntxt(ucCntxtIndex);                                      /* 释放实体                                 */
        SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                            /* 通知RABM去激活                           */

        SM_SndTafSmPdpActSecRej(
          g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
          NAS_SM_MapSmNWCause(pMsgIe->SmCause));                           /* 向TAF回拒绝消息                          */

        for(i=0; i<g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt; i++)
        {                                                                       /* 遍历Nsapi列表                            */
            if( g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i]
                == ucCntxtIndex)
            {                                                                   /* 为拒绝的Nsapi                            */
                for( j = i; j
                   < (g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt-1);j++)
                {
                    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[j]
                      =g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[j+1];  /* 更新对应的nsapi                          */
                }
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt--;          /* Nsapi的个数减1                           */
                break;
            }
        }
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* 状态切换到SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwActSecPdpCntxtRejMsg:NORMAL:SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_INACTIVE");
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;     /* 维护g_CrMapToNsapi                       */
        g_TiMapToNsapi[pMsgIe->ucTi] = 0xff;                                    /* 维护g_TiMapToNsapi                       */
    }
    else
    {
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);              /* 向network回SM STATUS消息#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}

/*******************************************************************************
  Module:   SM_RcvNwModifyPdpCntxtReqMsg
  Function: 接收MODIFY PDP CONTEXT REQUEST消息的处理
  Input:    SM_NW_MSG_STRU     *pMsgIe
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1.   郑 伟   2003.12.10   新规作成

  2.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程发起前申请资源
  3.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_RcvNwModifyPdpCntxtReqMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8               ucCntxtIndex;
    VOS_UINT8               ucAddrIndex;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* 根据TI获取ucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
         g_aucSapi[0][0] = 0;
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* 向network回SM STATUS消息#81              */
    }
    else
    {
        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;       /* 获得Addr Index                           */
        if( SM_PDP_MODIFY_PENDING
            == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {                                                                       /* 状态为SM_PDP_MODIFY_PENDING              */
            SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_MODIFY_COLLISION,
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);                                /* 通知Taf拒绝修改                          */

            SM_TimerStop(ucCntxtIndex);                                         /* 停止T3381                                */
            SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);        /* 释放备份的消息                           */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;     /* 状态切换到SM_PDP_ACTIVE                  */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwModifyPdpCntxtReqMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
        }
        if( SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {                                                                       /* 当前状态为SM_PDP_ACTIVE                  */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
                = (pMsgIe->Qos.ucLen <= sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue)) ?
                  (pMsgIe->Qos.ucLen) : (sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));
            PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                       pMsgIe->Qos.pValue,
                       g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength); /* 更新Qos                                  */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri
                = pMsgIe->ucRadioPri;                                           /* 存储ucRadioPri                           */
            if( 0 != pMsgIe->PdpAddr.ucLen )
            {                                                                   /* 要更新PdpAddr                            */
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo
                    .ulAddrLength = pMsgIe->PdpAddr.ucLen;                      /* 设定长度                                 */
                SM_MemCpy(
                    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
                    pMsgIe->PdpAddr.pValue,
                    pMsgIe->PdpAddr.ucLen);                                     /* 存储PdpAddr                              */
            }

            NAS_SM_BeginSession();

            SM_SndTafSmPdpModifyInd(pMsgIe, ucCntxtIndex);                      /* 通知TAF修改请求                          */
            SM_TimerStart(ucCntxtIndex,SM_T0003_LENGTH,SM_TIMER_TYPE_T0003);    /* 启动Network发起PDP context Modify保护
                                                                                 * Timer                                    */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_NW_MODIFY;  /* 状态切换到SM_PDP_NW_MODIFY               */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwModifyPdpCntxtReqMsg:NORMAL: SM state: SM_PDP_ACTIVE ==> SM_PDP_NW_MODIFY");
        }
        else if(SM_PDP_NW_MODIFY
            == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {                                                                       /* 当前状态为SM_PDP_NW_MODIIFY              */
        }
        else
        {
            g_aucSapi[0][0] = 0;

            SM_SndStatusMsg(pMsgIe->ucTi,TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE); /* 向network回SM STATUS消息#98              */
        }
    }
    SM_Free(pMsgIe);                                                            /* 释放内存                                 */
    return;
}

/*****************************************************************************
 函 数 名  : SM_RcvNwModifyPdpCntxtAccMsg
 功能描述  : 接收MODIFY PDP CONTEXT ACCEPT消息的处理
 输入参数  : SM_NW_MSG_STRU     *pMsgIe
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月10日
    作    者   : 郑 伟
    修改内容   : 新生成函数

  2.日    期   : 2010年11月10日
    作    者   : A00165503
    修改内容   : 问题单号:DTS2010101601395，SM-STATUS报给网侧的原因值错误

  3.日    期   : 2012年3月31日
    作    者   : z00161729
    修改内容   : 支持ISR修改

  4.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源
*****************************************************************************/
VOS_VOID SM_RcvNwModifyPdpCntxtAccMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8               ucCntxtIndex;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* 根据TI获取ucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
         g_aucSapi[0][0] = 0;
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* 向network回SM STATUS消息#81              */
    }
    else if( SM_PDP_MODIFY_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {
        SM_TimerStop(ucCntxtIndex);                                             /* 停止T3380                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* 释放备份的消息                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
        if( 0 != pMsgIe->ucRadioPri )
        {                                                                       /* 存在ucRadioPri                           */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri
                = pMsgIe->ucRadioPri;                                           /* 存储ucRadioPri                           */
        }
        if( 0 != pMsgIe->Qos.ucLen )
        {                                                                       /* 消息中存在Qos                            */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
                = (pMsgIe->Qos.ucLen <= sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue)) ?
                  (pMsgIe->Qos.ucLen) : (sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));
            PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                       pMsgIe->Qos.pValue,
                       g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength); /* 更新Qos                                  */
        }
        SM_SndRabmSmModifyInd(ucCntxtIndex);                                    /* 通知修改Nsapi                            */
        SM_SndTafSmPdpModifyCnf(pMsgIe, ucCntxtIndex);                          /* 向TAF回响应消息                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* 状态切换到SM_PDP_ACTIVE                  */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwModifyPdpCntxtAccMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_SUCC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);

        /* 网侧pdp上下文修改成功，需通知GMM */
        NAS_SM_SndGmmPdpModifyInd(ucCntxtIndex + SM_NSAPI_OFFSET);
    }
    else
    {
        g_aucSapi[0][0] = 0;
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);               /* 向network回SM STATUS消息#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}

/*****************************************************************************
 函 数 名  : SM_RcvNwModifyPdpCntxtRejMsg
 功能描述  : 接收MODIFY PDP CONTEXT REJECT消息的处理
 输入参数  : SM_NW_MSG_STRU     *pMsgIe
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月10日
    作    者   : 郑 伟
    修改内容   : 新生成函数

  2.日    期   : 2010年11月10日
    作    者   : A00165503
    修改内容   : 问题单号:DTS2010101601395，SM-STATUS报给网侧的原因值错误

  3.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源
*****************************************************************************/
VOS_VOID SM_RcvNwModifyPdpCntxtRejMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8       ucCntxtIndex;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* 根据TI获取ucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* 向network回SM STATUS消息#81              */
    }
    else if( SM_PDP_MODIFY_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* 状态为SM_PDP_MODIFY_PENDING              */
        SM_TimerStop(ucCntxtIndex);                                             /* 停止T3381                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* 释放备份的消息                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;

        SM_SndTafSmPdpModifyRej(NAS_SM_MapSmNWCause(pMsgIe->SmCause),
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* 状态切换到SM_PDP_ACTIVE                  */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwModifyPdpCntxtRejMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL,
                        (VOS_VOID *)&(pMsgIe->SmCause),
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL_LEN);
    }
    else
    {
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);               /* 向network回SM STATUS消息#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);                                                            /* 释放内存                                 */
    return;
}

/*******************************************************************************
  Module:   SM_RcvNwDeActPdpCntxtReqMsg
  Function: 接收DEACTIVATE PDP CONTEXT REQUEST消息的处理
  Input:    SM_NW_MSG_STRU     *pMsgIe
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1.郑 伟   2003.12.10   新规作成

  2.日    期   : 2010年10月25日
    作    者   : z00161729
    修改内容   : CS Only情况,PDP去激活后,SM需要通过pdp_deactive_ind消息通知GMM进行detach

  3.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程发起前申请资源

  4.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接

  5.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改

  6.日    期   : 2015年7月23日
    作    者   : wx270776
    修改内容   : OM融合
*******************************************************************************/
VOS_VOID SM_RcvNwDeActPdpCntxtReqMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8               i;
    VOS_UINT8               ucCntxtIndex;
    VOS_UINT8               ucAddrIndex;
    VOS_UINT8               ucLinkNsapi;
    VOS_UINT8               ucInitType;
    /* Deleted by wx270776 for OM融合, 2015-7-23, begin */

    /* Deleted by wx270776 for OM融合, 2015-7-23, end */

    ucCntxtIndex = g_TiMapToNsapi[pMsgIe->ucTi];                                /* 根据TI获取ucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);
    }
    else
    {
        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;       /* 获得Addr Index                           */
        NAS_SM_BeginSession();
        SM_SndPdpDeActAccMsg(ucCntxtIndex);                                     /* 向network回ACCEPT消息                    */
        if( SM_TRUE == pMsgIe->ucTdi )
        {                                                                       /* 包含Tear down indicator IE并且 requested */
            if( SM_PDP_INACTIVE_PENDING
                == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
            {                                                                   /* 状态为SM_PDP_INACTIVE_PENDING            */
                NAS_SM_NORM_LOG("SM_RcvNwDeActPdpCntxtReqMsg: SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE");
                SM_TimerStop(ucCntxtIndex);                                     /* 停止T3390                                */
                SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);    /* 释放备份的消息                           */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* 状态切换到SM_PDP_INACTIVE                */

                g_TiMapToNsapi[pMsgIe->ucTi] = 0xFF;                            /* 维护g_TiMapToNsapi                       */
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr]
                    = 0xFF;                                                     /* 维护g_CrMapToNsapi                       */
            }

            SM_SndRabmSmDeactivateInd(
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt,
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi);             /* 通知RABM去激活Nsapi列表:                 */
            SM_SndTafSmPdpDeActInd(
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                NAS_SM_MapSmNWCause(pMsgIe->SmCause),
                SM_TRUE);

            /* 绿色通道 */
            /* Deleted by wx270776 for OM融合, 2015-7-23, begin */
            /* Deleted by wx270776 for OM融合, 2015-7-23, end */

            for(i=0;i<g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;i++)
            {                                                                   /* Nsapi列表                                */
                ucLinkNsapi
                    = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i];     /* 获得ucLinkNsapi                          */
                SM_ComClearPdpCntxt(ucLinkNsapi);                               /* 释放实体                                 */
                g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucState
                    = SM_PDP_INACTIVE;                                          /* 状态切换到SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwDeActPdpCntxtReqMsg:NORMAL: SM state = SM_PDP_INACTIVE");
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucTi]
                    = 0xFF;                                                     /* 维护g_TiMapToNsapi                       */
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucCr]
                    = 0xFF;                                                     /* 维护g_CrMapToNsapi                       */
            }

            SM_ComClearPdpAddrApn(ucAddrIndex);                                 /* 清除Addr Apn实体                         */
            NAS_SM_SndGmmPdpStatusInd();
        }
        else
        {                                                                       /* 不包含Tear down IE或者not requested      */
            if( SM_PDP_INACTIVE_PENDING
                == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
            {                                                                   /* 状态为SM_PDP_INACTIVE_PENDING            */
                NAS_SM_NORM_LOG("SM_RcvNwDeActPdpCntxtReqMsg:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE ");

                SM_TimerStop(ucCntxtIndex);                                     /* 停止T3390                                */
                SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);    /* 释放备份的消息                           */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                SM_SndTafSmPdpDeActCnf(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);          /* 向TAF回响应消息                          */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* 状态切换到SM_PDP_INACTIVE                */

            }
            else
            {
                NAS_SM_NORM_LOG("SM_RcvNwDeActPdpCntxtReqMsg:NORMAL: SM state = SM_PDP_INACTIVE");

                SM_SndRabmSmDeactivateInd (1, &ucCntxtIndex);                   /* 通知RABM去激活Nsapi                      */
                SM_SndTafSmPdpDeActInd(
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                    NAS_SM_MapSmNWCause(pMsgIe->SmCause),
                    SM_FALSE);

                /* 绿色通道 */
                /* Deleted by wx270776 for OM融合, 2015-7-23, begin */
                /* Deleted by wx270776 for OM融合, 2015-7-23, end */
                SM_ComClearPdpCntxt(ucCntxtIndex);                              /* 释放实体                                 */
                SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);               /* 从PDP Addr and Apn实体中删除Nsapi        */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* 状态切换到SM_PDP_INACTIVE                */

                NAS_SM_SndGmmPdpStatusInd();
            }
            g_TiMapToNsapi[pMsgIe->ucTi] = 0xFF;                                /* 维护g_TiMapToNsapi                       */
            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF; /* 维护g_CrMapToNsapi                       */
        }
        ucInitType = DEACTIVE_REQUEST_INIT_TYPE_MT;
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_DEACTIVE_REQ,
                        (VOS_VOID *)&ucInitType,
                        NAS_OM_EVENT_PDP_DEACTIVE_REQ_LEN);
        NAS_SM_SndGmmPdpDeactivatedInd();
        NAS_SM_EndSession();
    }

    SM_Free(pMsgIe);                                                            /* 释放内存                                 */
    return;
}

/*****************************************************************************
 函 数 名  : SM_RcvNwDeActPdpCntxtAccMsg
 功能描述  : 接收DEACTIVATE PDP CONTEXT ACCEPT消息的处理
 输入参数  : SM_NW_MSG_STRU     *pMsgIe
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月10日
    作    者   : 郑 伟
    修改内容   : 新生成函数

  2.日    期   : 2010年08月13日
    作    者   : A00165503
    修改内容   : 问题单号:DTS2010070502076，接收到PDP去激活时，CS ONLY下待SM指示PDP去激活完成后进行PS DETACH

  3.日    期   : 2010年11月10日
    作    者   : A00165503
    修改内容   : 问题单号:DTS2010101601395，SM-STATUS报给网侧的原因值错误

  4.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  5.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*****************************************************************************/
VOS_VOID SM_RcvNwDeActPdpCntxtAccMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8                           ucCntxtIndex;

    ucCntxtIndex = g_TiMapToNsapi[pMsgIe->ucTi];                                /* 根据TI获取ucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* 状态为SM_PDP_INACTIVE                    */
         SM_SndStatusMsg(pMsgIe->ucTi,TAF_SM_REJ_CAUSE_INVALID_TI);             /* 向network回SM STATUS消息#81              */
    }
    else if( SM_PDP_INACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* 状态为SM_PDP_INACTIVE_PENDING            */
        SM_TimerStop(ucCntxtIndex);                                             /* 停止T3390                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* 释放备份的消息                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
        SM_SndTafSmPdpDeActCnf(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* 状态切换到SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwDeActPdpCntxtAccMsg:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE");
        g_TiMapToNsapi[pMsgIe->ucTi] = 0xff;                                    /* 维护g_TiMapToNsapi                       */
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;     /* 维护g_CrMapToNsapi                       */

        NAS_SM_SndGmmPdpStatusInd();

        /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */
        NAS_SM_SndGmmPdpDeactivatedInd();
    }
    else
    {
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);               /* 向network回SM STATUS消息#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}

/*******************************************************************************
  Module:   SM_ComFindNullAddrApn
  Function: 查找未使用的Addr 和 Apn的索引
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   ucAddrIndex
  History:
      1.   郑 伟   2003.12.10   新规作成
*******************************************************************************/
VOS_UINT8 SM_ComFindNullAddrApn()
{
    VOS_UINT8            i;

    for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {                                                                           /* 遍历所有的Addr 和 Apn实体                */
        if( 0 == (g_SmPdpAddrApn.usPdpAddrFlg & (VOS_UINT16)((VOS_UINT32)0x0001 << i)))
        {                                                                       /* 对应的索引没有使用                       */
            return i;                                                           /* 返回Addr 和 Apn的索引                    */
        }
    }
    return SM_MAX_NSAPI_NUM;                                                    /* 返回无效，没有未使用的索引               */
}

/*******************************************************************************
  Module:   SM_ComClearPdpCntxt
  Function: 维护内部全局变量
  Input:    VOS_UINT8          ucCntxtIndex
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.10   新规作成

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : SM保存的QOS和APN由动态内存改为静态数组
*******************************************************************************/
VOS_VOID SM_ComClearPdpCntxt(
     VOS_UINT8                          ucCntxtIndex                            /* PDPcontext实体的索引                     */
 )
{
    VOS_UINT8    ucAddrIndex;

    SM_TimerStop(ucCntxtIndex);                                                 /* 停止该实体的Timer                        */
    ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;
    if(0 == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt)
    {                                                                           /* ucNsapiCnt的个数为0                      */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength = 0;        /* 初始化长度信息                           */
        PS_MEM_SET(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
                   0x00,
                   sizeof(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue));
    }

    g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength = 0;
    PS_MEM_SET(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
               0x00,
               sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));

    if( SM_NULL != g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg )
    {                                                                           /* 存在缓存的重发消息                       */
        SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);            /* 释放缓存的重发消息                       */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
    }


    PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_ComClearPdpCntxt:NORMAL: Destroy SM entity(index):", ucCntxtIndex);

    return;
}

/*******************************************************************************
  Module:   SM_ComClearPdpAddrApn
  Function: 释放PDP Addr和APN实体
  Input:    VOS_UINT8          ucAddrIndex
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.10   新规作成

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : SM保存的QOS和APN由动态内存改为静态数组
*******************************************************************************/
VOS_VOID SM_ComClearPdpAddrApn(
    VOS_UINT8                           ucAddrIndex                             /* PDPAddr实体的索引                        */
)
{
    VOS_UINT32                          ulTmp = 1;

    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength = 0;
    PS_MEM_SET(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
               0x00,
               sizeof(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue));

    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength = 0;      /* 清除PdpAddrInfo长度                      */
    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt = 0;                    /* nsapi个数清0                             */
    g_SmPdpAddrApn.usPdpAddrFlg &= ( ~ (ulTmp << ucAddrIndex));

    return;
}

/*******************************************************************************
  Module:   SM_ComDelNsapiFromAddr
  Function: PDP Addr and Apn实体中删除Nsapi
  Input:    VOS_UINT8          ucAddrIndex
            VOS_UINT8          ucNsapi
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.10   新规作成
*******************************************************************************/
VOS_VOID SM_ComDelNsapiFromAddr(
                            VOS_UINT8          ucAddrIndex,                         /* PDP Addr and Apn实体的索引               */
                            VOS_UINT8          ucNsapi                              /* 要删除的NSAPI                            */
                            )
{
    VOS_UINT8        i;
    VOS_UINT8        j;

    for(i = 0;i< g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;i++)
    {                                                                           /* 遍历Nsapi列表                            */
        if(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i] == ucNsapi)
        {                                                                       /* 找到指定的Nsapi                          */
            for(j = i; j
                < (g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt-1); j++ )
            {
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[j]
                    = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[j+1];   /* 删除指定的Nsapi                          */
            }
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt--;              /* NSAPI个数减1                             */
            break;
        }
    }
    if( 0 == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt )
    {                                                                           /* ucNsapiCnt的个数为0                      */
        SM_ComClearPdpAddrApn(ucAddrIndex);                                     /* 清除Addr和Apn实体                        */
    }
    return;
}

/*******************************************************************************
  Module:   SM_RcvNwReqPdpCnxtActMsg_S00
  Function: SM_PDP_INACTIVE状态接收到REQUEST PDP CONTEXT ACTIVATION消息的处理
  Input:    SM_NW_MSG_STRU    *pMsgIe            收到的消息
            VOS_UINT8             ucCntxtIndex       PDP context的索引
  Output:   VOS_VOID
  NOTE:     8-0
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.10   新规作成
*******************************************************************************/
VOS_VOID SM_RcvNwReqPdpCnxtActMsg_S00(
                                  SM_NW_MSG_STRU                *pMsgIe,        /* 收到的消息                               */
                                  VOS_UINT8                         ucCntxtIndex    /* PDP context的索引                        */
                                 )
{
    VOS_UINT16                  i;      /*A32D00461,zzy,pclint*/
    VOS_UINT8                   ucCr;
    VOS_UINT8                   ucTi;

    ucTi = (VOS_UINT8)(pMsgIe->ucTi & 0x7F);                                        /* 取TI的实际值                             */
    ucCr = 0xff;

    for( i = 0; i <= (SM_MAX_NSAPI_NUM - 1);    i++ )
    {                                                                           /* 查找MT过程的CR                           */
        if( 0xff == g_CrMapToNsapi[i] )
        {                                                                       /* 申请没有使用的CR                         */
            ucCr = (VOS_UINT8)i;        /*A32D00461,zzy,pclint*/                                                   /* 获取CR                                   */
            break;
        }
    }
    if( 0xFF != ucCr )
    {                                                                           /* 申请 CR成功                              */
        PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwReqPdpCnxtActMsg_S00:NORMAL: Create SM entity(index):", ucCntxtIndex);
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTiFlg = SM_TI_NET_ORG;         /* 设定实体的发起标志 NET发起               */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi = ucTi;                     /* 存储TI                                   */
        g_TiMapToNsapi[pMsgIe->ucTi]= ucCntxtIndex;                             /* 维护Ti和NSAPI的映射                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr = ucCr;                     /* 存储CR                                   */
        g_CrMapToNsapi[ucCr] = ucCntxtIndex;                                    /* 维护Cr和NSAPI的映射                      */

        SM_SndTafSmPdpActivateInd(pMsgIe, ucCntxtIndex);                        /* 向所有的TAF发送激活请求                  */
    }
    else
    {
        SM_SndReqPdpActRejMsg(SM_NULL, ucTi);                                   /* 回拒绝消息                               */
    }

    return;
}

/*******************************************************************************
  Module:   SM_RcvNwReqPdpCnxtActMsg_S01
  Function: 比较PDP type, PDP address and APN是否相同
  Input:    SM_NW_MSG_STRU    *pMsgIe            收到的消息
            VOS_UINT8             ucCntxtIndex       PDP context的索引
            VOS_UINT8             ucTi               网侧Ti
  Output:   VOS_VOID
  NOTE:     VOS_VOID
  Return:   SM_TRUE     PDP type, PDP address and APN相同
            SM_FALSE    PDP type, PDP address and APN不相同
  History:
      1.   郑 伟   2003.12.10   新规作成

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : SM保存的QOS和APN由动态内存改为静态数组
*******************************************************************************/
VOS_UINT8 SM_RcvNwReqPdpCnxtActMsg_S01(
    SM_NW_MSG_STRU                     *pMsgIe,             /* 收到的消息                               */
    VOS_UINT8                           ucCntxtIndex,       /* PDP context的索引                        */
    VOS_UINT8                           ucTi                /* 网侧Ti                                   */
)
{
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucResult1;
    VOS_UINT8                           ucResult2;

    ucResult1   = 0xFF;
    ucResult2   = 0xFF;
    ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

    if(( 0 != pMsgIe->Apn.ucLen )
        &&( pMsgIe->Apn.ucLen
        == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength)
        &&( pMsgIe->PdpAddr.ucLen
        == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength))
    {                                                                           /* 能够比较PDP type, PDP address and APN    */
        ucResult1 = SM_MemCmp(
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
            pMsgIe->Apn.pValue,
            pMsgIe->Apn.ucLen);                                                 /* 调用内存比较函数                         */
        ucResult2 = SM_MemCmp(
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
            pMsgIe->PdpAddr.pValue,
            pMsgIe->PdpAddr.ucLen);                                             /* 调用内存比较函数                         */
        if(( 0 == ucResult1 )
            &&( 0 == ucResult2 ))
        {                                                                       /* PDP type, PDP address and APN相同        */
            return SM_TRUE;
        }
    }

    return SM_FALSE;
}

/*******************************************************************************
  Module:   SM_RcvNwReqPdpCnxtActMsg_S02
  Function: SM_PDP_ACTIVE状态接收到REQUEST PDP CONTEXT ACTIVATION消息的处理
  Input:    SM_NW_MSG_STRU    *pMsgIe            收到的消息
            VOS_UINT8             ucCntxtIndex       PDP context的索引
  Output:   VOS_VOID
  NOTE:     8-2
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.10   新规作成

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : SM保存的QOS和APN由动态内存改为静态数组

  3.日    期   : 2012年8月27日
    作    者   : m00217266
    修改内容   : 修改接口SM_SndTafSmPdpDeActInd，添加原因值

  4.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*******************************************************************************/
VOS_VOID SM_RcvNwReqPdpCnxtActMsg_S02(
    SM_NW_MSG_STRU                     *pMsgIe,
    VOS_UINT8                           ucCntxtIndex
)
{
    VOS_UINT8               i;
    VOS_UINT8               ucAddrIndex;
    VOS_UINT8               ucLinkIndex;

    VOS_UINT8                   ucResult1;
    VOS_UINT8                   ucResult2;

    ucResult1   = 0xFF;
    ucResult2   = 0xFF;

    if ( ucCntxtIndex >= SM_MAX_NSAPI_NUM )
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvNwReqPdpCnxtActMsg_S02:WARNING:ucCntxtIndex >= SM_MAX_NSAPI_NUM ");
        return;    /*A32D00461,zzy,pclint*/
    }
    ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

    if(( 0 != pMsgIe->Apn.ucLen )
        &&( pMsgIe->Apn.ucLen
        == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength)
        &&( pMsgIe->PdpAddr.ucLen > 2 )
        &&( pMsgIe->PdpAddr.ucLen
        == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength))
    {                                                                           /* 能够比较PDP type, PDP address and APN    */
        ucResult1 = SM_MemCmp(
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
            pMsgIe->Apn.pValue,
            pMsgIe->Apn.ucLen);                                                 /* 调用内存比较函数                         */
        ucResult2 = SM_MemCmp(
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
            pMsgIe->PdpAddr.pValue,
            pMsgIe->PdpAddr.ucLen);                                             /* 调用内存比较函数                         */
        if(( 0 == ucResult1 )
            &&( 0 == ucResult2 ))
        {                                                                       /* PDP type, PDP address and APN相同        */
            SM_SndRabmSmDeactivateInd(
                        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt,
                        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi);     /* 通知RABM去激活Nsapi列表:                 */
            for(i = 0;i < g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;
                i++)
            {                                                                   /* Nsapi列表                                */
                ucLinkIndex
                     = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i];

                SM_SndTafSmPdpDeActInd(
                        g_SmEntity.aPdpCntxtList[ucLinkIndex].ucCr,
                        SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,
                        SM_TRUE);                                               /* 通知TAF去激活                            */

                SM_ComClearPdpCntxt( ucLinkIndex );                             /* 释放实体                                 */
                g_SmEntity.aPdpCntxtList[ucLinkIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* 状态切换到SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwReqPdpCnxtActMsg_S02:NORMAL: SM state = SM_PDP_INACTIVE");
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkIndex].ucTi]
                    = 0xFF;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkIndex].ucCr]
                    = 0xFF;
            }
            SM_ComClearPdpAddrApn(ucAddrIndex);                                 /* 清除Addr Apn实体                         */
        }
        else
        {
            SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                        /* 通知RABM去激活Nsapi列表:                 */
            SM_SndTafSmPdpDeActInd(
                        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                        SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,
                        SM_FALSE);

            SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);
            SM_ComClearPdpCntxt( ucCntxtIndex );                                /* 释放实体                                 */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;   /* 状态切换到SM_PDP_INACTIVE                */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwReqPdpCnxtActMsg_S02:NORMAL: SM state = SM_PDP_INACTIVE");
            g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xFF;
            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF;
        }
    }
    else
    {
        if( SM_PDP_INACTIVE_PENDING
            == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {
            SM_TimerStop(ucCntxtIndex);                                         /* 停止T3390                                */
            SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);        /* 释放备份的消息                           */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
            SM_SndTafSmPdpDeActCnf(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);              /* 向TAF回响应消息                          */
        }
        else
        {
            SM_SndRabmSmDeactivateInd (1, &ucCntxtIndex);                       /* 通知RABM去激活Nsapi                      */
            SM_SndTafSmPdpDeActInd(
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,
                SM_FALSE);
            SM_ComClearPdpCntxt(ucCntxtIndex);
            SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);
        }
        g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xFF;
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF;
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* 状态切换到SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwReqPdpCnxtActMsg_S02:NORMAL: SM state = SM_PDP_INACTIVE");
    }

    SM_RcvNwReqPdpCnxtActMsg_S00(pMsgIe,ucCntxtIndex);                          /* 调用在SM_PDP_INACTIVE状态的处理          */
    NAS_SM_SndGmmPdpStatusInd();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_ComparePdpAddr
 功能描述  : 比较两个PDP ADDRESS是否完全相同
 输入参数  : SM_MSG_IE_COMMON_STRU  *pstReqPdpAddr
             SM_PDP_ADDR_STRU       *pstExistPdpAddr
 输出参数  : 无
 返 回 值  : VOS_TURE   - 相同
             VOS_FALSE  - 不相同
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月10日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL NAS_SM_ComparePdpAddr(
    SM_MSG_IE_COMMON_STRU              *pstReqPdpAddr,
    SM_PDP_ADDR_STRU                   *pstExistPdpAddr
)
{
    if ( (pstReqPdpAddr->ucLen > 2)
      && (pstReqPdpAddr->ucLen == pstExistPdpAddr->ulAddrLength) )
    {
/*lint -e961*/
        if (!VOS_MemCmp(pstReqPdpAddr->pValue, pstExistPdpAddr->aucAddrValue, pstExistPdpAddr->ulAddrLength))
        {
            return VOS_TRUE;
        }
/*lint +e961*/
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_SM_RcvGmmSigConnInd
 功能描述  : 处理 GMMSM_SIG_CONN_IND 连接建立成功原语, 根据当前SM状态重启
             T3380, T3381或T3390
 输入参数  : pstSigConnInd - 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_SM_RcvGmmSigConnInd(
    GMMSM_SIG_CONN_IND_STRU            *pstSigConnInd
)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    VOS_UINT32                          ulTimerLen = 0;
    VOS_UINT8                           ucTimerType = 0;
    VOS_UINT8                           ucTmrReStartFlg;
    VOS_UINT8                           ucExpireTimes;
    VOS_UINT8                           i;

    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        /* 获取PDP实体信息 */
        pstPdpCtxInfo   = NAS_SM_GetPdpCtxInfoAddr(i);

        /* 重置定时器重启标识 */
        ucTmrReStartFlg = VOS_FALSE;

        switch (pstPdpCtxInfo->ucState)
        {
            case SM_PDP_ACTIVE_PENDING:
                ucTimerType     = SM_TIMER_TYPE_T3380;
                ulTimerLen      = SM_T3380_LENGTH;
                ucTmrReStartFlg = VOS_TRUE;
                break;

            case SM_PDP_MODIFY_PENDING:
                ucTimerType     = SM_TIMER_TYPE_T3381;
                ulTimerLen      = SM_T3381_LENGTH;
                ucTmrReStartFlg = VOS_TRUE;
                break;

            case SM_PDP_INACTIVE_PENDING:
                ucTimerType     = SM_TIMER_TYPE_T3390;
                ulTimerLen      = SM_T3390_LENGTH;
                ucTmrReStartFlg = VOS_TRUE;
                break;

            default :
                break;
        }

        if (VOS_TRUE == ucTmrReStartFlg)
        {
            /* 若定时器还处于开启状态，则需要重新启动，以便重新计时 */
            if (SM_TIMER_STA_ON == pstPdpCtxInfo->TimerInfo.ucTimerStaFlg)
            {
                /* 保存ucExpireTimes, 定时器启动后恢复 */
                ucExpireTimes = pstPdpCtxInfo->TimerInfo.ucExpireTimes;

                /* 停止并启动相应定时器 */
                SM_TimerStop(i);
                SM_TimerStart(i, ulTimerLen, ucTimerType);

                /* 恢复ucExpireTimes */
                pstPdpCtxInfo->TimerInfo.ucExpireTimes = ucExpireTimes;
            }
        }
    }
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
