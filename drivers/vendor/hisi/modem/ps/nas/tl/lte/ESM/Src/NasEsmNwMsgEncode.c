/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmNwMsgEncode.c
    Description : SM模块组装空口消息发给网侧
    History     :
     1.丁丽   00128736      2008-09-01  Draft Enact
     2.聂州渝 00108792
     3.杨茜惠 00135146      2008-12-18  Modify  BA8D00752
     4.杨茜惠 00135146      2008-12-24  Modify  BA8D00795
     5.孙兵 49683           2009-01-06  Modify  BA8D00870
     6.杨茜惠 00135146      2009-03-06  Modify  BA8D01127
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmNwMsgEncode.h"
#include    "NasEsmNwMsgProc.h"
#include    "NasLmmPubMOm.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGENCODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMNWMSGENCODE_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_UINT32                              g_ulPcscfFlag = NAS_ESM_FUN_CTRL_OFF;
VOS_UINT32                              g_ulBcmFlag = NAS_ESM_FUN_CTRL_OFF;
NAS_ESM_GET_IPV6_DNS_CTRL_ENUM_UINT32   g_enIpv6DnsFlag = NAS_ESM_GET_IPV6_DNS_CTRL_ON;

VOS_UINT32                              g_ulLocalIpSupportFlag = NAS_ESM_FUN_CTRL_OFF;
VOS_UINT32                              g_ulNwLocalIpSupportFlag = NAS_ESM_NW_LOCAL_IP_CAP_UNSUPPORT;

#if (VOS_OS_VER == VOS_WIN32)
NAS_ESM_OM_ENCODE_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU  g_EsmEncodeFailCausePrintTable[] =
{
    {ESM_ENCODE_CN_MSG_IE_LEN_INVALID                       , "ESM_ENCODE_CN_MSG_IE_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_IE_TYPE_INVALID                      , "ESM_ENCODE_CN_MSG_IE_TYPE_INVALID"},
    {ESM_ENCODE_CN_MSG_PD_INVALID                           , "ESM_ENCODE_CN_MSG_PD_INVALID"},
    {ESM_ENCODE_CN_MSG_MSG_TYPE_INVALID                     , "ESM_ENCODE_CN_MSG_MSG_TYPE_INVALID"},
    {ESM_ENCODE_CN_MSG_NOT_PARA_LIST_ID                     , "ESM_ENCODE_CN_MSG_NOT_PARA_LIST_ID"},
    {ESM_ENCODE_CN_MSG_TAD_TYPE_INVALID                     , "ESM_ENCODE_CN_MSG_TAD_TYPE_INVALID"},
    {ESM_ENCODE_CN_MSG_PF_NUM_INVALID                       , "ESM_ENCODE_CN_MSG_PF_NUM_INVALID"},
    {ESM_ENCODE_CN_MSG_SAME_PF_ID                           , "ESM_ENCODE_CN_MSG_SAME_PF_ID"},
    {ESM_ENCODE_CN_MSG_SAME_PF_PRECEDENCE                   , "ESM_ENCODE_CN_MSG_SAME_PF_PRECEDENCE"},
    {ESM_ENCODE_CN_MSG_SIGLE_PORT_AND_PORT_RANGE_COEXIST    , "ESM_ENCODE_CN_MSG_SIGLE_PORT_AND_PORT_RANGE_COEXIST"},
    {ESM_ENCODE_CN_MSG_IP_LEN_INVALID                       , "ESM_ENCODE_CN_MSG_IP_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_BCM_TYPE_INVALID                     , "ESM_ENCODE_CN_MSG_BCM_TYPE_INVALID"},
    {ESM_ENCODE_CN_MSG_PCO_CONFIG_PROTOCOL_INVALID          , "ESM_ENCODE_CN_MSG_PCO_CONFIG_PROTOCOL_INVALID"},
    {ESM_ENCODE_CN_MSG_IP_TYPE_INVALID                      , "ESM_ENCODE_CN_MSG_IP_TYPE_INVALID"},
    {ESM_ENCODE_CN_MSG_QOS_RATE_0                           , "ESM_ENCODE_CN_MSG_QOS_RATE_0"},
    {ESM_ENCODE_CN_MSG_PF_ITEM_TYPE_INVALID                 , "ESM_ENCODE_CN_MSG_PF_ITEM_TYPE_INVALID"},
    {ESM_ENCODE_CN_MSG_APN_CHARACTER_INVALID                , "ESM_ENCODE_CN_MSG_APN_CHARACTER_INVALID"},
    {ESM_ENCODE_CN_MSG_PARA_LIST_ID_INVALID                 , "ESM_ENCODE_CN_MSG_PARA_LIST_ID_INVALID"},
    {ESM_ENCODE_CN_MSG_IPV4_LEN_INVALID                     , "ESM_ENCODE_CN_MSG_IPV4_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_IPV6_LEN_INVALID                     , "ESM_ENCODE_CN_MSG_IPV6_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_BCM_LEN_INVALID                      , "ESM_ENCODE_CN_MSG_BCM_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_IPCP_LEN_INVALID                     , "ESM_ENCODE_CN_MSG_IPCP_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_IPCP_PRI_DNS_LEN_INVALID             , "ESM_ENCODE_CN_MSG_IPCP_PRI_DNS_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_IPCP_SEC_DNS_LEN_INVALID             , "ESM_ENCODE_CN_MSG_IPCP_SEC_DNS_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_IPCP_OTHER_LEN_INVALID               , "ESM_ENCODE_CN_MSG_IPCP_OTHER_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_LEN_INVALID                          , "ESM_ENCODE_CN_MSG_LEN_INVALID"},
    {ESM_ENCODE_CN_MSG_ESM_MSG_PD_INVALID                   , "ESM_ENCODE_CN_MSG_ESM_MSG_PD_INVALID"},
    {ESM_ENCODE_CN_MSG_ESM_MSG_TYPE_INVALID                 , "ESM_ENCODE_CN_MSG_ESM_MSG_TYPE_INVALID"},
    {ESM_ENCODE_CN_MSG_QCI_INVALID                          , "ESM_ENCODE_CN_MSG_QCI_INVALID"},
    {ESM_ENCODE_CN_MSG_MAXRATE_INVALID                      , "ESM_ENCODE_CN_MSG_MAXRATE_INVALID"},
    {ESM_ENCODE_CN_MSG_OPERATION_TYPE_INVALID               , "ESM_ENCODE_CN_MSG_OPERATION_TYPE_INVALID"},
    {ESM_ENCODE_CN_MSG_NOT_DEFAULT_BEARER                   , "ESM_ENCODE_CN_MSG_NOT_DEFAULT_BEARER"},
    {ESM_ENCODE_CN_MSG_NO_BEARER_CONTEXT                    , "ESM_ENCODE_CN_MSG_NO_BEARER_CONTEXT"}
};

const VOS_UINT32 g_EsmEncodeFailCausePrintTableSize =
              (sizeof(g_EsmEncodeFailCausePrintTable)/sizeof(NAS_ESM_OM_ENCODE_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU));

extern NAS_ESM_OM_CN_MSG_IE_PRINT_STR_STRU  g_EsmDecodeFailIePrintTable[];
#endif



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ESM_IsExistSamePrecedenceBeforeEncodeMsg
 Description     : 判断列表中优先级是否有相同的
 Input           : pstSdfPara  -- SDF 参数
                   ucPfNum     -- Packetfilter个数
                   pstPfPVList -- Packetfilter列表
 Output          : None
 Return          : NAS_ESM_SUCCESS -- 有相同的
                   NAS_ESM_FAILURE -- 没有相同的
 History         :
    1.liuwenyu 00143951      2010-11-15  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_ESM_IsExistSamePrecedenceBeforeEncodeMsg
(
    const NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    VOS_UINT8                                 ucPfNum,
    const NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList
)
{
    VOS_UINT8                           ucCnt1      = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt2      = NAS_ESM_NULL;

    for (ucCnt1 = NAS_ESM_NULL; ucCnt1 < pstSdfPara->ulPfNum; ucCnt1++)
    {
        for (ucCnt2 = NAS_ESM_NULL; ucCnt2 < ucPfNum; ucCnt2++)
        {
            if (pstSdfPara->astCntxtTftInfo[ucCnt1].ucPrecedence !=
                                            pstPfPVList[ucCnt2].ucPrecedence)
            {
                continue;
            }

            if (pstSdfPara->ulCId == pstPfPVList[ucCnt2].ucCid)
            {
                continue;
            }
            NAS_ESM_INFO_LOG2("Precedence Collision in these CID:", pstSdfPara->ulCId, pstPfPVList[ucCnt2].ucCid);
            TLPS_PRINT2LAYER_INFO2(NAS_ESM_IsExistSamePrecedenceBeforeEncodeMsg_ENUM, 1, pstSdfPara->ulCId, pstPfPVList[ucCnt2].ucCid);
            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;
}
/*****************************************************************************
 Function Name   : NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg
 Description     : 编码前判断当前此PDN下所有承载的PF的优先级是否冲突
 Input           : ulLinkEpsbId-----------------关联的EpsbId
                   pstSdfPara  -----------------SDF 参数
 Output          : None
 Return          : NAS_ESM_SUCCESS -- 验证成功
                   NAS_ESM_FAILURE -- 验证失败
 History         :
    1.liuwenyu 00143951      2010-11-15  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg
(
    VOS_UINT32                         ulLinkEpsbId,
    const NAS_ESM_SDF_PARA_STRU       *pstSdfPara
)
{
    VOS_UINT8                           ucPfNum     = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt      = NAS_ESM_FAILURE;
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList = VOS_NULL_PTR;

    /* 申请优先级验证列表存储空间 */
    pstPfPVList = NAS_ESM_MEM_ALLOC(NAS_ESM_MAX_EPSB_NUM * NAS_ESM_MAX_SDF_PF_NUM
                                    * sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU));

    if (VOS_NULL_PTR == pstPfPVList)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg:NAS_ESM_MEM_ALLOC failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg_ENUM, LNAS_EMM_ALLOC_FAIL);

        return NAS_ESM_FAILURE;
    }

    /* 形成优先级验证列表 */
    ulRslt = NAS_ESM_CreatePfPrecedenceValidateListInPdn(ulLinkEpsbId,
                                                         &ucPfNum,
                                                         pstPfPVList);

    if (ulRslt != NAS_ESM_SUCCESS)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg:NAS_ESM_CreatePfPrecedenceValidateListInPdn failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg_ENUM, 1);

        /* 释放优先级验证列表存储空间 */
        NAS_ESM_MEM_FREE(pstPfPVList);

        return NAS_ESM_FAILURE;
    }

    ulRslt = NAS_ESM_IsExistSamePrecedenceBeforeEncodeMsg(pstSdfPara,
                                                          ucPfNum,
                                                          pstPfPVList);

    /* 释放优先级验证列表存储空间 */
    NAS_ESM_MEM_FREE(pstPfPVList);

    if (ulRslt == NAS_ESM_SUCCESS)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg:precedence not unique!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg_ENUM, 2);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeBearerResAllocReqMsg
 Description     : SM模块组装Bearer resource allocation request消息函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-7-20  Draft Enact
    2.lihong00150010      2010-3-11  Modify

*****************************************************************************/
VOS_UINT32  NAS_ESM_EncodeBearerResAllocReqMsg
(
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt              = NAS_ESM_FAILURE;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stEpsQosInfo                      ;

    NAS_ESM_MEM_SET_S(  &stEpsQosInfo,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeBearerResAllocReqMsg:INFO:NAS_ESM_EncodeBearerResAllocReqMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeBearerResAllocReqMsg_ENUM, LNAS_ENTRY);

    pstSdfPara = NAS_ESM_GetSdfParaAddr(stEncodeInfo.ulCid);

    /*判断必选参数在APP中是否存在，不存在则返回错误*/
    if((NAS_ESM_NULL == pstSdfPara->ulPfNum) ||
        (NAS_ESM_OP_FALSE == pstSdfPara->bitOpSdfQos))
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_ENCODE_CN_MSG_PF_NUM_INVALID,
                                        pstSdfPara->ulPfNum);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResAllocReqMsg_ENUM, 1);

        return NAS_ESM_FAILURE;
    }

    /* 检查发起的消息优先级是否唯一 */
    ulRslt = NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg(stEncodeInfo.ulLinkedEpsbId,
                                                         pstSdfPara);
    if (NAS_ESM_FAILURE == ulRslt)
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_ENCODE_CN_MSG_SAME_PF_PRECEDENCE,
                                        stEncodeInfo.ulLinkedEpsbId);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResAllocReqMsg_ENUM, 2);

        return NAS_ESM_FAILURE;
    }

    /* 检查是否存在上行PF */
    if(ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        /* 24301 CR1937R4(Rel-11) 6.5.3.2: The packet filters in the Traffic flow aggregate
        IE shall include at least one packet filter applicable for the uplink direction.  */
        if(NAS_ESM_SUCCESS != NAS_ESM_CheckSdfHaveUplinkPacketFilter(pstSdfPara))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResAllocReqMsg: WARN, R11 no uplink PF!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResAllocReqMsg_ENUM, 3);
            return NAS_ESM_FAILURE;
        }
    }

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum++] = ((VOS_UINT8)(NAS_ESM_UNASSIGNED_EPSB_ID << NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = stEncodeInfo.ucPti;

    /*存放Message type: NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REQ，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REQ;

    /* 存放关联缺省承载号 */
    pTmpSendMsg[ulSum++] = (VOS_UINT8)stEncodeInfo.ulLinkedEpsbId & NAS_ESM_MSG_LOW_BIT;

    /* 编码TFT信息 */
    if(NAS_ESM_FAILURE == NAS_ESM_EncodeTftCreateTftOrReplacePf(NAS_ESM_TFT_CREATE_TFT,
                                                                stEncodeInfo.ulCid,
                                                                pTmpSendMsg+ulSum,
                                                                &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResAllocReqMsg:WARNING:NAS->ESM Message Tft encode failure!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResAllocReqMsg_ENUM, 4);
        return NAS_ESM_FAILURE;
    }

    ulSum += ulIndex;

    /*ulIndex归零*/
    ulIndex = NAS_ESM_NULL;

    /*SDF QoS*/
    NAS_ESM_MEM_CPY_S(  &stEpsQosInfo.stQosInfo,
                        sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                        &pstSdfPara->stSdfQosInfo,
                        sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    stEpsQosInfo.ucNwQCI = pstSdfPara->stSdfQosInfo.ucQCI;

    if(NAS_ESM_FAILURE == NAS_ESM_EncodeEpsQos(&stEpsQosInfo,
                                               pTmpSendMsg+ulSum,
                                               &ulIndex,
                                               NAS_MSG_FORMAT_LV))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResAllocReqMsg:WARNING:NAS->ESM Message SDF QOS encode failure!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResAllocReqMsg_ENUM, 5);
        return NAS_ESM_FAILURE;
    }

    ulSum += ulIndex;

    /*ulIndex归零*/
    ulIndex = NAS_ESM_NULL;



    *pulLength = ulSum + ulIndex;
    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ModPfDirection
 Description     : 根据操作类型修改PF的方向
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ESM_ModPfDirection
(
    APP_ESM_TRANSFER_DIRECTION_ENUM_UINT8 *pdstDirection,
    APP_ESM_TRANSFER_DIRECTION_ENUM_UINT8 *psrcDirection,
    NAS_ESM_SDF_OP_TYPE_ENUM_UINT8         enSdfOpType
)
{
    /* 删除则强制设置为无效值 */
    if((NAS_ESM_SDF_OP_TYPE_DELETE_SDF == enSdfOpType)
        ||(NAS_ESM_SDF_OP_TYPE_DELETE_PF == enSdfOpType))
    {
        *pdstDirection = APP_ESM_TRANSFER_DIRECTION_BUTT;
    }
    else if(NAS_ESM_SDF_OP_TYPE_MOD_PF == enSdfOpType)
    {
        *pdstDirection = *psrcDirection;
    }
    else if(NAS_ESM_SDF_OP_TYPE_MOD_QOS_AND_PF == enSdfOpType)
    {
        *pdstDirection = *psrcDirection;
    }
    else
    {
        /* 其他操作类型无动作 */
    }

    return;

}


/*****************************************************************************
 Function Name   : NAS_ESM_ValidateAppOpSdfPfDirection
 Description     : 在编码消息之前先检查修改SDF后的PF的方向是否合法
 Input           : NAS_ESM_RES_MOD_ENCODE_INFO_STRU    修改参数
                   NAS_ESM_PF_PRCDNC_VLDT_STRU         原承载下的所有PF信息列表
                   VOS_UINT32                          参数2中PF总数
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_ESM_ValidateAppOpSdfPfDirection
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU   *pstResModEncodeInfo,
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList,
    VOS_UINT32                          ulPfNum
)
{
    NAS_ESM_SDF_PARA_STRU               *pstSdfParaAddr   = VOS_NULL_PTR;
    VOS_UINT32                           ulCnt            = 0;
    VOS_UINT32                           ulCnt2           = 0;
    VOS_UINT32                           ulCnt3           = 0;

    /* 取出要操作的SDF */
    pstSdfParaAddr  = NAS_ESM_GetSdfParaAddr(pstResModEncodeInfo->ulCid);

    /* 如果只是增加PF，直接返回成功，增加不会导致没有上行PF */
    /* Add by y00307272删除sdf类型，且只有一个CID，即删除后没有pf的情况下，直接返回成功 */
    if((NAS_ESM_SDF_OP_TYPE_ADD_SDF == pstResModEncodeInfo->enSdfOpType)
        ||(NAS_ESM_SDF_OP_TYPE_ADD_PF == pstResModEncodeInfo->enSdfOpType)
        ||(NAS_ESM_SDF_OP_TYPE_NO_CHANGE == pstResModEncodeInfo->enSdfOpType)
        ||(NAS_ESM_SDF_OP_TYPE_MOD_QOS == pstResModEncodeInfo->enSdfOpType)
        ||((NAS_ESM_SDF_OP_TYPE_DELETE_SDF == pstResModEncodeInfo->enSdfOpType)
            &&(ulPfNum == pstSdfParaAddr->ulPfNum)))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ValidateAppOpSdfPfDirection:ADD or NO CHANGE PF!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ValidateAppOpSdfPfDirection_ENUM, LNAS_ENTRY);
        return NAS_ESM_SUCCESS;
    }

    /* 每一个PF，都查找一下是否在要操作的CID中，如果是，将其PF方向修改一下 */
    for(ulCnt = 0; ulCnt < ulPfNum; ulCnt++)
    {
        /* 如果CID相同 */
        if(pstPfPVList[ulCnt].ucCid == pstResModEncodeInfo->ulCid)
        {
            /* 循环查找要操作的CID下的每个PF，看是否在LIST中，如果在，将方向强行设置为修改后的方向 */
            for(ulCnt2 = 0; ulCnt2 < pstSdfParaAddr->ulPfNum; ulCnt2++)
            {
                if(pstPfPVList[ulCnt].ucPfId== pstSdfParaAddr->astCntxtTftInfo[ulCnt2].ucPacketFilterId)
                {
                    /* 根据相应的操作类型，对表中的PF方向进行处理 */
                    NAS_ESM_ModPfDirection(&pstPfPVList[ulCnt].enDirection,
                                             &pstSdfParaAddr->astCntxtTftInfo[ulCnt2].enDirection,
                                             pstResModEncodeInfo->enSdfOpType);
                }
            }
        }
    }

    /* 全部操作完成，循环查找列表中是否还有上行PF */
    for(ulCnt3 = 0; ulCnt3 < ulPfNum; ulCnt3++)
    {
        if((APP_ESM_TRANSFER_DIRECTION_UPLINK == pstPfPVList[ulCnt3].enDirection)
            ||(APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK == pstPfPVList[ulCnt3].enDirection))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ValidateAppOpSdfPfDirection:Have uplink PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ValidateAppOpSdfPfDirection_ENUM, 1);
            break;
        }
    }

    /* 没有找到上行PF，返回失败 */
    if(ulCnt3 >= ulPfNum)
    {
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;

}


/*****************************************************************************
 Function Name   : NAS_ESM_ValidatePfDirectionBeforeEncodeMsg
 Description     : 在编码消息之前先检查修改后的PF的方向是否合法
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_ESM_ValidatePfDirectionBeforeEncodeMsg
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU          *pstResModEncodeInfo
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    VOS_UINT8                           ucPfNum             = 0;
    VOS_UINT32                          ulRet               = 0;
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList         = VOS_NULL_PTR;

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstResModEncodeInfo->ulEpsbId);

    /* 不是专有承载，可以没有上行PF */
    if(NAS_ESM_BEARER_TYPE_DEDICATED != pstEpsbCntxtInfo->enBearerCntxtType)
    {
        return NAS_ESM_SUCCESS;
    }

    /* 申请优先级验证列表存储空间，一个承载下不管多少CID，最多只能有16个PF */
    pstPfPVList = NAS_ESM_MEM_ALLOC(NAS_ESM_MAX_SDF_PF_NUM*sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU));

    /* 申请内存失败直接返回失败 */
    if(VOS_NULL_PTR == pstPfPVList)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePfDirectionBeforeEncodeMsg: Alloc pflist fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidatePfDirectionBeforeEncodeMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return NAS_ESM_FAILURE;
    }

    NAS_ESM_MEM_SET_S(  pstPfPVList,
                        NAS_ESM_MAX_SDF_PF_NUM * sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU),
                        0,
                        NAS_ESM_MAX_SDF_PF_NUM*sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU));

    /* 取出当前承载下所有的PF */
    NAS_ESM_GetPfPrecedenceValidateListInBearer((VOS_UINT8)pstResModEncodeInfo->ulEpsbId, &ucPfNum, pstPfPVList);

    /* 验证APP修改后的PF方向是否合法 */
    ulRet = NAS_ESM_ValidateAppOpSdfPfDirection(pstResModEncodeInfo, pstPfPVList, ucPfNum);

    /* 释放申请的内存 */
    NAS_ESM_MEM_FREE(pstPfPVList);

    return ulRet;

}



VOS_UINT32  NAS_ESM_ValidateSdfParaBeforeEncodeMsg
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU          stResModEncodeInfo
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = NAS_ESM_FAILURE;

    pstSdfPara = NAS_ESM_GetSdfParaAddr(stResModEncodeInfo.ulCid);

    /*判断必选参数在APP中是否存在，不存在则返回错误*/
    if (NAS_ESM_NULL == pstSdfPara->ulPfNum)
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_ENCODE_CN_MSG_PF_NUM_INVALID,
                                        pstSdfPara->ulPfNum);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateSdfParaBeforeEncodeMsg_ENUM, 1);

        return NAS_ESM_FAILURE;
    }

    /* 删除SDF和修改Qos不需要携带优先级,不用验证优先级 */
    if ((NAS_ESM_SDF_OP_TYPE_DELETE_SDF != stResModEncodeInfo.enSdfOpType)
     && (NAS_ESM_SDF_OP_TYPE_MOD_QOS != stResModEncodeInfo.enSdfOpType))
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(stResModEncodeInfo.ulEpsbId);

        /* 检查发起的消息优先级是否唯一 */
        ulRslt = NAS_ESM_ValidatePfPrecedenceBeforeEncodeMsg(pstEpsbCntxtInfo->ulLinkedEpsbId,
                                                             pstSdfPara);
        if (NAS_ESM_FAILURE == ulRslt)
        {
            NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_ENCODE_CN_MSG_SAME_PF_PRECEDENCE,
                                            pstEpsbCntxtInfo->ulLinkedEpsbId);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateSdfParaBeforeEncodeMsg_ENUM, 2);

            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_ESM_GetBearerAllPacketFilter
 Description     : 搜索承载下的所有Packetfilter
 Input           : ulEpsbId   -- 承载号
 Output          : pulPfNum   -- 承载下的packetfilter的个数
                   pstTFTInfo -- 所有packetfilter的数组
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-11-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_GetBearerAllPacketFilter
(
    VOS_UINT32                           ulEpsbId,
    VOS_UINT32                          *pulPfNum,
    NAS_ESM_CONTEXT_TFT_STRU            *pstTFTInfo
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEspbCntxtInfo    = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt1              = NAS_ESM_NULL;

    *pulPfNum = NAS_ESM_NULL;

    pstEspbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* 遍历所有SDF,如果关联的承载是ulEpsbId*/
    /* 将这个SDF下的所有Packetfilter拷贝到pstTFTInfo*/
    for(ulCnt1 = NAS_ESM_MIN_CID; ulCnt1 <= NAS_ESM_MAX_CID; ulCnt1++)
    {
        if(NAS_ESM_OP_TRUE !=((pstEspbCntxtInfo->ulBitCId >> ulCnt1 )& NAS_ESM_BIT_0))
        {
            continue;
        }

        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt1);

        if (((*pulPfNum) + pstSdfCntxtInfo->ulSdfPfNum) <= NAS_ESM_MAX_SDF_PF_NUM)
        {
            NAS_ESM_MEM_CPY_S(  &pstTFTInfo[*pulPfNum],
                                (pstSdfCntxtInfo->ulSdfPfNum * sizeof(NAS_ESM_CONTEXT_TFT_STRU)),
                                pstSdfCntxtInfo->astSdfPfInfo,
                                (pstSdfCntxtInfo->ulSdfPfNum * sizeof(NAS_ESM_CONTEXT_TFT_STRU)));

            (*pulPfNum) += pstSdfCntxtInfo->ulSdfPfNum;
        }
        else
        {
            NAS_ESM_WARN_LOG("NAS_ESM_GetBearerAllPacketFilter:there are more than 16 packeter in one bearer !");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_GetBearerAllPacketFilter_ENUM, 1);
        }
    }
}


VOS_UINT32  NAS_ESM_EncodeBearerResModReqMsgRelBearer
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulPfArrayLen        = NAS_ESM_NULL;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    VOS_UINT32                          ulPfNum             = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_TFT_STRU           *pstSdfPfArray       = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeBearerResModReqMsgRelBearer is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeBearerResModReqMsgRelBearer_ENUM, LNAS_ENTRY);

    pTmpSendMsg[ulSum++] = ((VOS_UINT8)(NAS_ESM_UNASSIGNED_EPSB_ID << NAS_ESM_MOVEMENT_4_BITS)\
                            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = stResModEncodeInfo.ucPti;

    /*存放Message type: NAS_ESMCN_BEARER_RES_MODIFICATION_REQ，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ;

    pTmpSendMsg[ulSum++] = stResModEncodeInfo.ulLinkedEpsbId & NAS_ESM_MSG_LOW_BIT;

    ulPfArrayLen = sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM;

    /*分配空间并检验分配是否成功*/
     pstSdfPfArray = (VOS_VOID*)NAS_ESM_MEM_ALLOC(ulPfArrayLen);

     /*检测是否分配成功*/
     if (VOS_NULL_PTR == pstSdfPfArray)
     {
         /*打印异常信息*/
         NAS_ESM_ERR_LOG("NAS_ESM_EncodeBearerResModReqMsgRelBearer:Memory Alloc FAIL!");
         TLPS_PRINT2LAYER_ERROR(NAS_ESM_EncodeBearerResModReqMsgRelBearer_ENUM, LNAS_EMM_ALLOC_FAIL);
         return NAS_ESM_FAILURE;
     }

    NAS_ESM_MEM_SET_S(pstSdfPfArray, ulPfArrayLen, NAS_ESM_NULL, ulPfArrayLen);


    NAS_ESM_GetBearerAllPacketFilter(stResModEncodeInfo.ulEpsbId,
                                     &ulPfNum,
                                      pstSdfPfArray);

    NAS_ESM_EncodeTftDeletePf(pstSdfPfArray,
                              ulPfNum,
                              pTmpSendMsg + ulSum,
                             &ulIndex);

    ulSum = ulSum + ulIndex;

    /*存放ESM cause和IEI*/
    pTmpSendMsg[ulSum++] = NAS_ESM_MSG_ESM_CAU_IEI;
    pTmpSendMsg[ulSum++] = stResModEncodeInfo.ucESMCau;

    *pulLength = ulSum;

    /* 释放内存空间 */
    NAS_ESM_MEM_FREE(pstSdfPfArray);

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EncodeBearerResModReqMsg()
 Description    : SM模块组装Bearer resource modification request消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.聂州渝 00108792      2008-09-19  Draft Enact
      2.sunbing 49683        2009-02-05  Modify
      3.lihong 00150010      2009-05-18  Modify
*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodeBearerResModReqMsg
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    VOS_UINT32                          ulRet               = NAS_ESM_NULL;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    VOS_UINT32                          ulRslt              = NAS_ESM_FAILURE;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeBearerResModReqMsg:INFO:NAS_ESM_EncodeBearerResModReqMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeBearerResModReqMsg_ENUM, LNAS_ENTRY);

    ulRslt = NAS_ESM_ValidateSdfParaBeforeEncodeMsg(stResModEncodeInfo);
    if (NAS_ESM_FAILURE == ulRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidateSdfParaBeforeEncodeMsg: precedence is not unique!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsg_ENUM, 1);

        return NAS_ESM_FAILURE;
    }

    /* R11以上版本修改后不存在上行PF则认为出现错误，不能发起修改 */
    /* 24301 CR1937R4(Rel-11) 6.5.4.2
    If the UE request the modification of a traffic flow aggregate, which is assigned to a dedicated EPS
    bearer context, it shall ensure that at least one packet filter applicable for the uplink direction
    remains among the packet filters created on request from the UE in that TFT, or no own packet filters*/
    if(ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        if(NAS_ESM_SUCCESS != NAS_ESM_ValidatePfDirectionBeforeEncodeMsg(&stResModEncodeInfo))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DedictdAttMsgAppSdfModifyReq:WARN, R11 modify render no uplink PF.");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsg_ENUM, 2);
            return NAS_ESM_FAILURE;
        }
    }

    pTmpSendMsg[ulSum++] = ((VOS_UINT8)(NAS_ESM_UNASSIGNED_EPSB_ID << NAS_ESM_MOVEMENT_4_BITS)\
        & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = stResModEncodeInfo.ucPti;

    /*存放Message type: NAS_ESMCN_BEARER_RES_MODIFICATION_REQ，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ;

    pTmpSendMsg[ulSum++] = stResModEncodeInfo.ulLinkedEpsbId & NAS_ESM_MSG_LOW_BIT;

    switch(stResModEncodeInfo.enSdfOpType)
    {
        case NAS_ESM_SDF_OP_TYPE_ADD_SDF:
            ulRet = NAS_ESM_EncodeBearerResModReqMsgAddSdf(stResModEncodeInfo,
                                                pTmpSendMsg + ulSum,
                                                &ulIndex);
            break;
        case NAS_ESM_SDF_OP_TYPE_DELETE_SDF:
            ulRet = NAS_ESM_EncodeBearerResModReqMsgDeleteSdf(stResModEncodeInfo,
                                                pTmpSendMsg + ulSum,
                                                &ulIndex);
            break;
        case NAS_ESM_SDF_OP_TYPE_MOD_QOS:
            ulRet = NAS_ESM_EncodeBearerResModReqMsgModQos(stResModEncodeInfo,
                                                pTmpSendMsg + ulSum,
                                                &ulIndex);
            break;


        case NAS_ESM_SDF_OP_TYPE_MOD_PF:
            ulRet = NAS_ESM_EncodeBearerResModReqMsgModPf(  stResModEncodeInfo,
                                                            pTmpSendMsg + ulSum,
                                                            &ulIndex);
            break;

        case NAS_ESM_SDF_OP_TYPE_MOD_QOS_AND_PF:
            ulRet = NAS_ESM_EncodeBearerResModReqMsgModQosAndPf(stResModEncodeInfo,
                                                pTmpSendMsg + ulSum,
                                                &ulIndex);
            break;

        default:
            NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_ENCODE_CN_MSG_OPERATION_TYPE_INVALID,
                                            stResModEncodeInfo.enSdfOpType);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsg_ENUM, 3);
            return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_FAILURE == ulRet)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsg:WARNING:Encode Tad failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsg_ENUM, 4);
        return NAS_ESM_FAILURE;
    }

    ulSum += ulIndex;

    /*ulIndex归零*/
    ulIndex = NAS_ESM_NULL;

    if( NAS_ESM_OP_TRUE == stResModEncodeInfo.bitOpESMCau)
    {
        /*存放ESM cause和IEI*/
        pTmpSendMsg[ulSum++] = NAS_ESM_MSG_ESM_CAU_IEI;
        pTmpSendMsg[ulSum++] = stResModEncodeInfo.ucESMCau;
    }



    *pulLength = ulSum + ulIndex;
    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeBearerResModReqMsgAddSdf
 Description     : 编码承载资源修改中的添加SDF
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2009-4-17  Draft Enact
    2.lihong00150010    2010-3-11  Modify

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodeBearerResModReqMsgAddSdf
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo,
    VOS_UINT8                           *pSendMsg,
    VOS_UINT32                          *pulLength
)
{
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = *pulLength;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stEpsQosInfo                      ;

    NAS_ESM_MEM_SET_S(  &stEpsQosInfo,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    pstSdfPara = NAS_ESM_GetSdfParaAddr(stResModEncodeInfo.ulCid);

    /* 编码TFT信息 */
    if(NAS_ESM_FAILURE == NAS_ESM_EncodeTftCreateTftOrReplacePf(NAS_ESM_TFT_CREATE_TFT,
                                                                stResModEncodeInfo.ulCid,
                                                                pTmpSendMsg+ulSum,
                                                                &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgAddSdf:WARNING:NAS->ESM Message Tft encode failure!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgAddSdf_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    ulSum += ulIndex;

    /*ulIndex归零*/
    ulIndex = NAS_ESM_NULL;

    /*SDF QoS*/
    if(NAS_ESM_OP_TRUE == pstSdfPara->bitOpSdfQos)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EncodeBearerResModReqMsgAddSdf:INFO:NAS->ESM Message contain SDF QOS!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeBearerResModReqMsgAddSdf_ENUM, 2);

        NAS_ESM_MEM_CPY_S(  &stEpsQosInfo.stQosInfo,
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU),
                            &pstSdfPara->stSdfQosInfo,
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));

        stEpsQosInfo.ucNwQCI = pstSdfPara->stSdfQosInfo.ucQCI;
        if(NAS_ESM_FAILURE == NAS_ESM_EncodeEpsQos(&stEpsQosInfo,
                                               pTmpSendMsg+ulSum,
                                               &ulIndex,
                                               NAS_MSG_FORMAT_TLV))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgAddSdf:WARNING:NAS->ESM Message SDF QOS encode failure!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgAddSdf_ENUM, 3);
            return NAS_ESM_FAILURE;
        }

        ulSum = ulSum + ulIndex;
        /* ulIndex = NAS_ESM_NULL; */
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgAddSdf:WARNING:NAS->ESM The must para is not selected!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgAddSdf_ENUM, 4);

        return NAS_ESM_FAILURE;

    }

    *pulLength = ulSum;
    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ModEpsQos
 Description     : 根据承载QOS的变化修改相应SDF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-4-24  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ModEpsQos
(
    const APP_ESM_EPS_QOS_INFO_STRU                      *pstEpsQoSInfoOld,
    const APP_ESM_EPS_QOS_INFO_STRU                      *pstEpsQoSInfoNew,
    APP_ESM_EPS_QOS_INFO_STRU                            *pstEpsQoSInfo
)
{
    /* 修改 ULMaxRate */
    if (pstEpsQoSInfoOld->ulULMaxRate < pstEpsQoSInfoNew->ulULMaxRate)
    {
        pstEpsQoSInfo->ulULMaxRate += (pstEpsQoSInfoNew->ulULMaxRate -
                                                pstEpsQoSInfoOld->ulULMaxRate);
    }
    else
    {
        pstEpsQoSInfo->ulULMaxRate -= (pstEpsQoSInfoOld->ulULMaxRate -
                                                pstEpsQoSInfoNew->ulULMaxRate);
    }

    /* 修改 DLMaxRate */
    if (pstEpsQoSInfoOld->ulDLMaxRate < pstEpsQoSInfoNew->ulDLMaxRate)
    {
        pstEpsQoSInfo->ulDLMaxRate += (pstEpsQoSInfoNew->ulDLMaxRate -
                                                pstEpsQoSInfoOld->ulDLMaxRate);
    }
    else
    {
        pstEpsQoSInfo->ulDLMaxRate -= (pstEpsQoSInfoOld->ulDLMaxRate -
                                                pstEpsQoSInfoNew->ulDLMaxRate);
    }

    /* 修改 ULGMaxRate */
    if (pstEpsQoSInfoOld->ulULGMaxRate < pstEpsQoSInfoNew->ulULGMaxRate)
    {
        pstEpsQoSInfo->ulULGMaxRate += (pstEpsQoSInfoNew->ulULGMaxRate -
                                                pstEpsQoSInfoOld->ulULGMaxRate);
    }
    else
    {
        pstEpsQoSInfo->ulULGMaxRate -= (pstEpsQoSInfoOld->ulULGMaxRate -
                                                pstEpsQoSInfoNew->ulULGMaxRate);
    }

    /* 修改 DLGMaxRate */
    if (pstEpsQoSInfoOld->ulDLGMaxRate < pstEpsQoSInfoNew->ulDLGMaxRate)
    {
        pstEpsQoSInfo->ulDLGMaxRate += (pstEpsQoSInfoNew->ulDLGMaxRate -
                                                pstEpsQoSInfoOld->ulDLGMaxRate);
    }
    else
    {
        pstEpsQoSInfo->ulDLGMaxRate -= (pstEpsQoSInfoOld->ulDLGMaxRate -
                                                pstEpsQoSInfoNew->ulDLGMaxRate);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetEpsQosAfterMod
 Description     : 获取修改后的承载QOS
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu 143951      2010-1-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_GetEpsQosAfterMod
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstEpsQoSInfo
)
{
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara       = VOS_NULL_PTR;

    pstSdfPara = NAS_ESM_GetSdfParaAddr(stResModEncodeInfo.ulCid);

    if (NAS_ESM_OP_TRUE == pstSdfPara->bitOpSdfQos)
    {
        /*根据EpsId取出承载信息*/
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(stResModEncodeInfo.ulEpsbId);

        NAS_ESM_MEM_CPY_S(  pstEpsQoSInfo,
                            sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                            &pstEpsbCntxtInfo->stEpsQoSInfo,
                            sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(stResModEncodeInfo.ulCid);

            /* 根据QOS的变化获得相应的Eps Qos 值 */
            NAS_ESM_ModEpsQos(&pstSdfCntxtInfo->stSdfQosInfo.stQosInfo,
                              &pstSdfPara->stSdfQosInfo,
                              &pstEpsQoSInfo->stQosInfo);
        }
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_GetEpsQosAfterMod:WARNING:NAS->ESM The must para is not selected!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_GetEpsQosAfterMod_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeBearerResModReqMsgDeleteSdf
 Description     : 编码承载资源修改中的删除SDF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-4-17  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodeBearerResModReqMsgDeleteSdf
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo,
    VOS_UINT8                           *pSendMsg,
    VOS_UINT32                          *pulLength
)
{

    VOS_UINT8                           *pTmpSendMsg      = pSendMsg;
    VOS_UINT32                           ulIndex          = NAS_ESM_NULL;
    VOS_UINT32                           ulSum            = NAS_ESM_NULL;
    VOS_UINT32                           ulActCidNum      = NAS_ESM_NULL;
    APP_ESM_EPS_QOS_INFO_STRU           *pstSdfQosInfo    = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_LTE_QOS_STRU         stEpsQosInfo;
    NAS_ESM_EPSB_CNTXT_INFO_STRU        *pstEpsbCntxtInfo = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU         *pstSdfCntxtInfo  = VOS_NULL_PTR;

    pstSdfCntxtInfo  = NAS_ESM_GetSdfCntxtInfo(stResModEncodeInfo.ulCid);

    NAS_ESM_EncodeTftDeletePf(&pstSdfCntxtInfo->astSdfPfInfo[0],
                               pstSdfCntxtInfo->ulSdfPfNum,
                               pTmpSendMsg,
                              &ulIndex);

    ulSum = ulSum + ulIndex;
    ulIndex = NAS_ESM_NULL;

    if (NAS_ESM_DEL_SDF_WITH_QOS_ON == NAS_ESM_GetDelSdfWithQosFlag())
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(stResModEncodeInfo.ulEpsbId);

        ulActCidNum = NAS_ESM_GetBearerLinkedCidNum(stResModEncodeInfo.ulEpsbId);

        /* 如果只对应一个激活的Cid,不携带Qos */
        if (ulActCidNum == NAS_ESM_BEARER_ACT_CID_NUM_ONE)
        {
            /*记录长度*/
            *pulLength = ulSum;
            return NAS_ESM_SUCCESS;
        }

        /* 编码新的EPS QOS */
        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            pstSdfQosInfo = &pstSdfCntxtInfo->stSdfQosInfo.stQosInfo;

            NAS_ESM_MEM_CPY_S(  &stEpsQosInfo,
                                sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                                &pstEpsbCntxtInfo->stEpsQoSInfo,
                                sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

            stEpsQosInfo.stQosInfo.ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            stEpsQosInfo.stQosInfo.ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            stEpsQosInfo.stQosInfo.ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            stEpsQosInfo.stQosInfo.ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;

            /* coverity[uninit_use_in_call] */
            if(NAS_ESM_FAILURE == NAS_ESM_EncodeEpsQos(&stEpsQosInfo,
                                                       pTmpSendMsg+ulSum,
                                                      &ulIndex,
                                                       NAS_MSG_FORMAT_TLV))
            {
                NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgDeleteSdf:NAS->ESM Message SDF QOS encode failure!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgDeleteSdf_ENUM, ESM_SDF_ERROR);

                return NAS_ESM_FAILURE;
            }

            ulSum = ulSum + ulIndex;
            /* ulIndex = NAS_ESM_NULL; */
        }
    }

    /*记录长度*/
    *pulLength = ulSum;

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeBearerResModReqMsgModPf
 Description     : 编码承载资源修改中的修改PF
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2009-4-17  Draft Enact
    2.lihong00150010    2010-3-11  Modify

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodeBearerResModReqMsgModPf
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo,
    VOS_UINT8                           *pSendMsg,
    VOS_UINT32                          *pulLength
)
{
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = *pulLength;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;

    /* 编码TFT信息 */
    if(NAS_ESM_FAILURE == NAS_ESM_EncodeTftCreateTftOrReplacePf(NAS_ESM_TFT_REPLACE_FILTER,
                                                                stResModEncodeInfo.ulCid,
                                                                pTmpSendMsg+ulSum,
                                                                &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgAddSdf:WARNING:NAS->ESM Message Tft encode failure!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgModPf_ENUM, LNAS_FAIL);
        return NAS_ESM_FAILURE;
    }

    ulSum += ulIndex;

    *pulLength = ulSum;

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_EncodeBearerResModReqMsgModQos
 Description     : 编码承载资源修改中的修改Qos
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-05-18  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodeBearerResModReqMsgModQos
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = *pulLength;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    VOS_UINT8                           aucNwPacketFilterId[NAS_ESM_MAX_SDF_PF_NUM] = {0};
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stEpsQoSInfo                      ;

    NAS_ESM_MEM_SET_S(  &stEpsQoSInfo,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    pstSdfPara = NAS_ESM_GetSdfParaAddr(stResModEncodeInfo.ulCid);

    for ( ulCnt = NAS_ESM_NULL ; ulCnt < pstSdfPara->ulPfNum ; ulCnt++ )
    {
        (VOS_VOID)NAS_ESM_QueryNWPacketFilterID(pstSdfPara->astCntxtTftInfo[ulCnt].ucPacketFilterId,
                                                stResModEncodeInfo.ulCid,
                                               &aucNwPacketFilterId[ulCnt]);
    }

    /* 赋值临时TFT信息变量 */
    /* 编码修改SDF的QOS消息中TFT部分 */
    NAS_ESM_EncodeTftNoOperation(aucNwPacketFilterId,
                                  pstSdfPara->ulPfNum,
                                  pSendMsg + ulSum,
                                  &ulIndex);


    /*记录长度*/
    ulSum = ulSum + ulIndex;

    /*ulIndex归零*/
    ulIndex = NAS_ESM_NULL;

    /*SDF QoS*/
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEpsQosAfterMod(stResModEncodeInfo,&stEpsQoSInfo))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EncodeBearerResModReqMsgModQos:INFO:NAS->ESM Message contain SDF QOS!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeBearerResModReqMsgModQos_ENUM, 1);
        if(NAS_ESM_FAILURE == NAS_ESM_EncodeEpsQos(&stEpsQoSInfo,
                                                    pTmpSendMsg+ulSum,
                                                    &ulIndex,
                                                    NAS_MSG_FORMAT_TLV))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgModQos:WARNING:NAS->ESM Message SDF QOS encode failure!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgModQos_ENUM, ESM_SDF_ERROR);
            return NAS_ESM_FAILURE;
        }

        ulSum = ulSum + ulIndex;
        /* ulIndex = NAS_ESM_NULL; */
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgModQos:WARNING:NAS->ESM get Modify Eps Qos error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgModQos_ENUM, LNAS_ERROR);

        return NAS_ESM_FAILURE;

    }

    *pulLength = ulSum;
    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeBearerResModReqMsgModQosAndPf
 Description     : 编码承载资源修改中的修改Qos和PF
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-05-18  Draft Enact
    2.lihong00150010      2010-3-11   Modify

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodeBearerResModReqMsgModQosAndPf
(
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo,
    VOS_UINT8                           *pSendMsg,
    VOS_UINT32                          *pulLength
)
{
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = *pulLength;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stEpsQoSInfo                  ;

    NAS_ESM_MEM_SET_S(  &stEpsQoSInfo,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    /* 编码TFT信息 */
    if(NAS_ESM_FAILURE == NAS_ESM_EncodeTftCreateTftOrReplacePf(NAS_ESM_TFT_REPLACE_FILTER,
                                                                stResModEncodeInfo.ulCid,
                                                                pTmpSendMsg+ulSum,
                                                                &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgModQosAndPf:WARNING:NAS->ESM Message Tft encode failure!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgModQosAndPf_ENUM, LNAS_ERROR);
        return NAS_ESM_FAILURE;
    }

    ulSum += ulIndex;

    /*ulIndex归零*/
    ulIndex = NAS_ESM_NULL;

    /*SDF QoS*/
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEpsQosAfterMod(stResModEncodeInfo,&stEpsQoSInfo))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EncodeBearerResModReqMsgModQosAndPf:INFO:NAS->ESM Message contain SDF QOS!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeBearerResModReqMsgModQosAndPf_ENUM, 1);
        if(NAS_ESM_FAILURE == NAS_ESM_EncodeEpsQos(&stEpsQoSInfo,
                                               pTmpSendMsg+ulSum,
                                               &ulIndex,
                                               NAS_MSG_FORMAT_TLV))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgModQosAndPf:WARNING:NAS->ESM Message SDF QOS encode failure!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgModQosAndPf_ENUM, 2);
            return NAS_ESM_FAILURE;
        }

        ulSum = ulSum + ulIndex;
        /* ulIndex = NAS_ESM_NULL; */
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeBearerResModReqMsgModQosAndPf:WARNING:NAS->ESM get Modify Eps Qos error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeBearerResModReqMsgModQosAndPf_ENUM, 3);

        return NAS_ESM_FAILURE;

    }

    *pulLength = ulSum;
    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EncodeActDedictdEpsbCntxtAccMsg()
 Description    : SM模块组装Activate dedicated EPS bearer context accept消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong  00150010   2009-07-31  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_EncodeActDedictdEpsbCntxtAccMsg( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8        *pTmpSendMsg  = pSendMsg;
    VOS_UINT32        ulSum        = NAS_ESM_NULL;
    VOS_UINT32        ulEpsbId     = stEncodeInfo.ulEpsbId;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeActDedictdEpsbCntxtAccMsg:INFO:NAS_ESM_EncodeActDedictdEpsbCntxtAccMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeActDedictdEpsbCntxtAccMsg_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(ulEpsbId << NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESM_PTI_UNASSIGNED_VALUE;

    /*存放Message type: NAS_ESMCN_ACT_DEDICTD_EPS_BEARER_CNTXT_ACC，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_ACC;

    *pulLength = ulSum ;
    return ;
}
/*****************************************************************************
 Function Name  : NAS_ESM_EncodeActDedictdEpsbCntxtRejMsg()
 Description    : SM模块组装Activate dedicated EPS bearer context reject消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong  00150010   2009-07-31  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_EncodeActDedictdEpsbCntxtRejMsg( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8        *pTmpSendMsg  = pSendMsg;
    VOS_UINT32        ulSum        = NAS_ESM_NULL;
    VOS_UINT32        ulEpsbId     = stEncodeInfo.ulEpsbId;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeActDedictdEpsbCntxtRejMsg:INFO:NAS_ESM_EncodeActDedictdEpsbCntxtRejMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeActDedictdEpsbCntxtRejMsg_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(ulEpsbId << NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESM_PTI_UNASSIGNED_VALUE;

    /*存放Message type: NAS_ESMCN_ACT_DEDICTD_EPS_BEARER_CNTXT_REJ，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REJ;

    /*存放ESM cause*/
    pTmpSendMsg[ulSum++] = stEncodeInfo.ucESMCau;

    *pulLength = ulSum ;

}

/*****************************************************************************
 Function Name  : NAS_ESM_EncodeModEpsbCntxtAccMsg
 Description    : SM模块组装Modify EPS bearer context accept消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong  00150010   2009-07-31  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_EncodeModEpsbCntxtAccMsg( const NAS_ESM_ENCODE_INFO_STRU *pstEncodeInfo,
                                                            VOS_UINT8  *pSendMsg,
                                                            VOS_UINT32 *pulLength)
{
    VOS_UINT8        *pTmpSendMsg  = pSendMsg;
    VOS_UINT32        ulSum        = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeModEpsbCntxtAccMsg:INFO:NAS_ESM_EncodeModEpsbCntxtAccMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeModEpsbCntxtAccMsg_ENUM, LNAS_ENTRY);


    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(pstEncodeInfo->ulEpsbId<< NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESM_PTI_UNASSIGNED_VALUE;

    /*存放Message type: NAS_ESMCN_MOD_EPS_BEARER_CNTXT_ACC，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_ACC;

    *pulLength = ulSum ;
    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EncodeModEpsbCntxtRejMsg()
 Description    : SM模块组装Modify EPS bearer context reject消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong  00150010   2009-07-31  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_EncodeModEpsbCntxtRejMsg( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8        *pTmpSendMsg  = pSendMsg;
    VOS_UINT32        ulIndex      = NAS_ESM_NULL;
    VOS_UINT32        ulSum        = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeModEpsbCntxtRejMsg:INFO:NAS_ESM_EncodeModEpsbCntxtRejMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeModEpsbCntxtRejMsg_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(stEncodeInfo.ulEpsbId<< NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESM_PTI_UNASSIGNED_VALUE;

    /*存放Message type: NAS_ESMCN_MOD_EPS_BEARER_CNTXT_REJ，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REJ;

    /*存放ESM cause*/
    pTmpSendMsg[ulSum++] = stEncodeInfo.ucESMCau;

    *pulLength = ulSum + ulIndex;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EncodePdnConReqMsg()
 Description    : SM模块组装PDN_CON_REQ消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.liuwenyu 00143951  2009-09-08  Modify
      4.leili  00132387    2010-07-15  Modify
*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodePdnConReqMsg( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8                           ucPti        = NAS_ESM_NULL;
    VOS_UINT8                           ucPDNType    = NAS_ESM_NULL;
    VOS_UINT32                          ulIndex      = NAS_ESM_NULL;
    VOS_UINT32                          ulSum        = NAS_ESM_NULL;
    VOS_UINT8                          *pTmpSendMsg  = pSendMsg;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara   = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodePdnConReqMsg:INFO:NAS_ESM_EncodePdnConReqMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePdnConReqMsg_ENUM, LNAS_ENTRY);

    ucPti = (VOS_UINT8)stEncodeInfo.ucPti;

    pstSdfPara = NAS_ESM_GetSdfParaAddr(stEncodeInfo.ulCid);

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(NAS_ESM_UNASSIGNED_EPSB_ID<< NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = ucPti;

    /*存放Message type: NAS_ESMCN_PDN_CONNECT_REQ，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    if (pstSdfPara->bitOpPdnType == NAS_ESM_OP_TRUE)
    {
        ucPDNType = (VOS_UINT8)pstSdfPara->enPdnType;
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodePdnConReqMsg:The sdf doesn't have pdn type!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePdnConReqMsg_ENUM, ESM_SDF_ERROR);

        ucPDNType = APP_ESM_PDN_TYPE_IPV4;
    }
    /*存放Request type为第4字节低四位，存放PDN type、为字节高四位
    Request type可能会删除，目前默认为init attach状态 */
    if(NAS_ESM_PDN_REQ_TYPE_HANDOVER == stEncodeInfo.enPdnReqType)
    {
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(NAS_ESM_MSG_PDNCONREQ_HANDOVER\
                        |((ucPDNType & NAS_ESM_MSG_LOW_BIT)<< NAS_ESM_MOVEMENT_4_BITS));

    }
    else if (APP_ESM_BEARER_TYPE_EMERGENCY == pstSdfPara->enBearerCntxtType)
    {
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(NAS_ESM_MSG_PDNCONREQ_EMERGENCY\
                |((ucPDNType & NAS_ESM_MSG_LOW_BIT)<< NAS_ESM_MOVEMENT_4_BITS));
    }
    else
    {
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(NAS_ESM_MSG_PDNCONREQ_INIT\
                |((ucPDNType & NAS_ESM_MSG_LOW_BIT)<< NAS_ESM_MOVEMENT_4_BITS));
    }

    /* set ESM information transfer flag when MM is attaching */
    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
    {
        if (NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn)
        {
            NAS_ESM_INFO_LOG("NAS_ESM_EncodePdnConReqMsg:NAS->SM Message encode esm info flag!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePdnConReqMsg_ENUM, LNAS_ENTRY);

            pTmpSendMsg[ulSum++] = NAS_ESM_MSG_ESMTXFG_IEI
                                  |NAS_ESM_INFO_FLAG_ON;
        }
        else /*如果用户没有设置APN和网关鉴权信息，可以直接在PDN连接请求中携带PCO消息*/
        {
            if(NAS_ESM_FAILURE == NAS_ESM_EncodePco(pstSdfPara,
                                                    pTmpSendMsg+ulSum,
                                                    &ulIndex,
                                                    NAS_MSG_FORMAT_TLV))
            {
                 /*打印异常信息*/
                NAS_ESM_WARN_LOG("NAS_ESM_EncodePdnConReqMsg:WARNING:NAS->SM Message PCO encode failure!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePdnConReqMsg_ENUM, LNAS_FAIL);
                return NAS_ESM_FAILURE;
            }
        }

        *pulLength = ulSum + ulIndex;
        return NAS_ESM_SUCCESS;
    }

    /*如果UE已经注册成功，则在PDN Connect Req消息携带APN和PCO信元*/
    if ((NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn) &&
        (APP_ESM_BEARER_TYPE_EMERGENCY != pstSdfPara->enBearerCntxtType))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EncodePdnConReqMsg:INFO:NAS->SM Message contain APN!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePdnConReqMsg_ENUM, 1);

        if(NAS_ESM_FAILURE == NAS_ESM_EncodeAPN(&pstSdfPara->stApnInfo,
                                                pTmpSendMsg+ulSum,
                                                &ulIndex,
                                                NAS_MSG_FORMAT_TLV))
        {
             /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_EncodePdnConReqMsg:WARNING:NAS->SM Message APN encode failure!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePdnConReqMsg_ENUM, ESM_APN_ERROR);
            return NAS_ESM_FAILURE;
        }
    }

    ulSum = ulSum + ulIndex;
    ulIndex = NAS_ESM_NULL;

    if(NAS_ESM_FAILURE == NAS_ESM_EncodePco(pstSdfPara,
                                            pTmpSendMsg+ulSum,
                                            &ulIndex,
                                            NAS_MSG_FORMAT_TLV))
    {
         /*打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_EncodePdnConReqMsg:WARNING:NAS->SM Message PCO encode failure!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePdnConReqMsg_ENUM, 2);
        return NAS_ESM_FAILURE;
    }

    *pulLength = ulSum + ulIndex;
    return NAS_ESM_SUCCESS;

}

/*****************************************************************************
 Function Name  : NAS_ESM_EncodePdnConReqMsg_PPP()
 Description    : SM模块组装PPP拨号场景PDN_CON_REQ消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.niuxiufan 00181501     2012-08-16  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodePdnConReqMsg_PPP( const APP_ESM_PDP_SETUP_REQ_STRU *pstAppEsmSetupReqMsg,
                                                     NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8                           ucPti        = NAS_ESM_NULL;
    VOS_UINT8                           ucPDNType    = NAS_ESM_NULL;
    VOS_UINT32                          ulIndex      = NAS_ESM_NULL;
    VOS_UINT32                          ulSum        = NAS_ESM_NULL;
    VOS_UINT8                          *pTmpSendMsg  = pSendMsg;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara   = VOS_NULL_PTR;


    NAS_ESM_INFO_LOG("NAS_ESM_EncodePdnConReqMsg_PPP:INFO:NAS_ESM_EncodePdnConReqMsg_PPP been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePdnConReqMsg_PPP_ENUM, LNAS_ENTRY);

    ucPti = (VOS_UINT8)stEncodeInfo.ucPti;

    pstSdfPara = NAS_ESM_GetSdfParaAddr(stEncodeInfo.ulCid);

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(NAS_ESM_UNASSIGNED_EPSB_ID<< NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = ucPti;

    /*存放Message type: NAS_ESMCN_PDN_CONNECT_REQ，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /*PPP拨号目前都按照IPv4处理*/
    if (pstSdfPara->bitOpPdnType != NAS_ESM_OP_TRUE)

    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodePdnConReqMsg_PPP:The sdf doesn't have pdn type!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePdnConReqMsg_PPP_ENUM, ESM_SDF_ERROR);
        pstSdfPara->bitOpPdnType = NAS_ESM_OP_TRUE;
    }

    if (pstSdfPara->enPdnType!= APP_ESM_PDN_TYPE_IPV4)

    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodePdnConReqMsg_PPP:The pdn type is not IPv4!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePdnConReqMsg_PPP_ENUM, 1);
        pstSdfPara->enPdnType = APP_ESM_PDN_TYPE_IPV4;
    }

    /* PPP拨号均按照IPv4处理*/
    ucPDNType = APP_ESM_PDN_TYPE_IPV4;

    /*存放Request type为第4字节低四位，存放PDN type、为字节高四位
    Request type可能会删除，目前默认为init attach状态*/
    if (APP_ESM_BEARER_TYPE_EMERGENCY == pstSdfPara->enBearerCntxtType)
    {
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(NAS_ESM_MSG_PDNCONREQ_EMERGENCY\
                |((ucPDNType & NAS_ESM_MSG_LOW_BIT)<< NAS_ESM_MOVEMENT_4_BITS));
    }
    else
    {
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(NAS_ESM_MSG_PDNCONREQ_INIT\
                |((ucPDNType & NAS_ESM_MSG_LOW_BIT)<< NAS_ESM_MOVEMENT_4_BITS));
    }


    /*如果UE已经注册成功，则在PDN Connect Req消息携带APN和PCO信元*/
    if((NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn)
        && (NAS_ESM_PS_REGISTER_STATUS_ATTACHED == NAS_ESM_GetEmmStatus())
        && (APP_ESM_BEARER_TYPE_EMERGENCY != pstSdfPara->enBearerCntxtType))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EncodePdnConReqMsg_PPP:INFO:NAS->SM Message contain APN!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePdnConReqMsg_PPP_ENUM, 2);

        if(NAS_ESM_FAILURE == NAS_ESM_EncodeAPN(&pstSdfPara->stApnInfo,
                                                pTmpSendMsg+ulSum,
                                                &ulIndex,
                                                NAS_MSG_FORMAT_TLV))
        {
             /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_EncodePdnConReqMsg_PPP:WARNING:NAS->SM Message APN encode failure!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePdnConReqMsg_PPP_ENUM, 3);
            return NAS_ESM_FAILURE;
        }
    }

    ulSum = ulSum + ulIndex;
    ulIndex = NAS_ESM_NULL;

    if(NAS_ESM_FAILURE == NAS_ESM_EncodePco_PPP(pstSdfPara,
                                            &pstAppEsmSetupReqMsg->stPppInfo,
                                            pTmpSendMsg+ulSum,
                                            &ulIndex,
                                            NAS_MSG_FORMAT_TLV))
    {
         /*打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_EncodePdnConReqMsg_PPP:WARNING:NAS->SM Message PCO encode failure!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePdnConReqMsg_PPP_ENUM, 4);
        return NAS_ESM_FAILURE;
    }

    *pulLength = ulSum + ulIndex;
    return NAS_ESM_SUCCESS;

}


/*****************************************************************************
 Function Name   : NAS_ESM_EncodeEsmInformationRspMsg
 Description     : 编码ESM information response消息
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2009-3-9  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodeEsmInformationRspMsg( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength )
{
    VOS_UINT8                           ucPti               = NAS_ESM_NULL;
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeEsmInformationRspMsg:INFO: NAS_ESM_EncodeEsmInformationRspMsg entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEsmInformationRspMsg_ENUM, LNAS_ENTRY);

    ucPti = stEncodeInfo.ucPti;

    /*根据PTI查找当前PDN连接请求过程*/
    if(NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByPti(ucPti,&ulStateTblIndex))
    {
        /*打印错误消息*/
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_ENCODE_CN_MSG_NO_BEARER_CONTEXT,
                                        ucPti);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEsmInformationRspMsg_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*检查承载类型是否是缺省承载*/
    if(PS_FALSE == NAS_ESM_IsDefaultEpsBearerType(pstStateAddr->enBearerCntxtType))
    {
        /*打印错误消息*/
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_ENCODE_CN_MSG_NOT_DEFAULT_BEARER,
                                        ulStateTblIndex);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEsmInformationRspMsg_ENUM, 2);
        return NAS_ESM_FAILURE;
    }

    /*根据缺省承载CID，获得对应CID参数设置表地址*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(NAS_ESM_UNASSIGNED_EPSB_ID<< NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = ucPti;

    /*存放Message type: NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_RSP，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_RSP;

    if(NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EncodeEsmInformationRspMsg:INFO:NAS->SM Message contain APN!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEsmInformationRspMsg_ENUM, 3);

        if(NAS_ESM_FAILURE == NAS_ESM_EncodeAPN(&pstSdfPara->stApnInfo,
                                               pTmpSendMsg+ulSum,
                                               &ulIndex,
                                               NAS_MSG_FORMAT_TLV))
        {
             /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_EncodeEsmInformationRspMsg:WARNING:NAS->SM Message APN encode failure!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEsmInformationRspMsg_ENUM, 4);
            return NAS_ESM_FAILURE;
        }
    }

    ulSum = ulSum + ulIndex;
    ulIndex = NAS_ESM_NULL;
    if(NAS_ESM_FAILURE == NAS_ESM_EncodePco(pstSdfPara,
                                            pTmpSendMsg+ulSum,
                                            &ulIndex,
                                            NAS_MSG_FORMAT_TLV))
    {
         /*打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeEsmInformationRspMsg:WARNING:NAS->SM Message PCO encode failure!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEsmInformationRspMsg_ENUM, 5);
        return NAS_ESM_FAILURE;
    }

    *pulLength = ulSum + ulIndex;
    return NAS_ESM_SUCCESS;

}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeEsmStatus
 Description     : 编码ESM Status消息
 Input           : NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                 VOS_UINT8  *pSendMsg,
                                 VOS_UINT32 *pulLength
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2009-3-9  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_EncodeEsmStatus( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8        *pTmpSendMsg  = pSendMsg;
    VOS_UINT32        ulSum        = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeEsmStatus:INFO:NAS_ESM_EncodeEsmStatus been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEsmStatus_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(stEncodeInfo.ulEpsbId << NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = stEncodeInfo.ucPti;

    /*存放Message type: NAS_ESMCN_MSG_TYPE_ESM_STATUS，*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_ESM_STATUS;

    /*存放ESM cause*/
    pTmpSendMsg[ulSum++] = stEncodeInfo.ucESMCau;

    *pulLength = ulSum ;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EncodeActDefltEpsbCntxtAccMsg()
 Description    : SM模块组装Activate default EPS bearer context accept消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong  00150010   2009-07-31  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_EncodeActDefltEpsbCntxtAccMsg( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8        *pTmpSendMsg  = pSendMsg;
    VOS_UINT32        ulIndex      = NAS_ESM_NULL;
    VOS_UINT32        ulSum        = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeActDefltEpsbCntxtAccMsg:INFO:NAS_ESM_EncodeActDefltEpsbCntxtAccMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeActDefltEpsbCntxtAccMsg_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(stEncodeInfo.ulEpsbId << NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESM_PTI_UNASSIGNED_VALUE;

    /*存放Message type: NAS_ESMCN_ACT_DEFLT_EPS_BEARER_CNTXT_ACC，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC;

    *pulLength = ulSum + ulIndex;
    return ;

}

/*****************************************************************************
 Function Name  : NAS_ESM_EncodeActDefltEpsbCntxtRejMsg()
 Description    : SM模块组装Activate default EPS bearer context reject消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong  00150010   2009-07-31  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_EncodeActDefltEpsbCntxtRejMsg( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8        *pTmpSendMsg  = pSendMsg;
    VOS_UINT32        ulSum        = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeActDefltEpsbCntxtRejMsg:INFO:NAS_ESM_EncodeActDefltEpsbCntxtRejMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeActDefltEpsbCntxtRejMsg_ENUM, LNAS_ENTRY);


    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(stEncodeInfo.ulEpsbId << NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESM_PTI_UNASSIGNED_VALUE;

    /*存放Message type: NAS_ESMCN_ACT_DEDICTD_EPS_BEARER_CNTXT_REJ，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REJ;

    /*存放ESM cause*/
    pTmpSendMsg[ulSum++] = stEncodeInfo.ucESMCau;

    *pulLength = ulSum ;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EncodePdnDisconReqMsg()
 Description    : SM模块组装PDN_DISCON_REQ消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodePdnDisconReqMsg( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8         ucPti        = NAS_ESM_NULL;
    VOS_UINT8        *pTmpSendMsg  = pSendMsg;
    VOS_UINT32        ulSum        = NAS_ESM_NULL;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_EncodePdnDisconReqMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePdnDisconReqMsg_ENUM, LNAS_ENTRY);

    ucPti = stEncodeInfo.ucPti;

    /*存放Protocol discriminator和没有分配的承载ID，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(NAS_ESM_UNASSIGNED_EPSB_ID << NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = ucPti;

    /*存放Message type: NAS_ESMCN_PDN_DISCONNECT_REQ，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REQ;

    /*s49683 20081027 begin*/
    /*pTmpSendMsg[ulSum++] = pstEpsbCntxtInfo->ulLinkedEpsbId & NAS_ESM_MSG_LOW_BIT;*/
    /*协议要求Linked Id为缺省承载Id*/
    pTmpSendMsg[ulSum++] =(VOS_UINT8)(stEncodeInfo.ulEpsbId & NAS_ESM_MSG_LOW_BIT);
    /*s49683 20081027 end*/

    *pulLength = ulSum ;
    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EncodeDeactEpsbCntxtAccMsg()
 Description    : SM模块组装Deactivate EPS bearer context accept消息函数
 Input          : VOS_UINT32 ulEpsbId,
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.丁丽 00128736      2008-09-01  Draft Enact
      2.sunbing 49683      2009-02-05  Modify
      3.lihong  00150010   2009-07-31  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_EncodeDeactEpsbCntxtAccMsg( NAS_ESM_ENCODE_INFO_STRU stEncodeInfo,
                                                     VOS_UINT8  *pSendMsg,
                                                     VOS_UINT32 *pulLength)
{
    VOS_UINT8        *pTmpSendMsg  = pSendMsg;
    VOS_UINT32        ulSum        = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeDeactEpsbCntxtAccMsg:INFO:NAS_ESM_EncodeDeactEpsbCntxtAccMsg been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeDeactEpsbCntxtAccMsg_ENUM, LNAS_ENTRY);

    /*存放Protocol discriminator和EpsbId，记录消息长度*/
    pTmpSendMsg[ulSum] = ((VOS_UINT8)(stEncodeInfo.ulEpsbId << NAS_ESM_MOVEMENT_4_BITS)\
            & NAS_ESM_MSG_HIGH_BIT) | NAS_ESM_MSG_PD;

    /*记录消息长度*/
    ulSum++;

    /*存放PTI，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESM_PTI_UNASSIGNED_VALUE;

    /*存放Message type: NAS_ESMCN_DEACT_EPS_BEARER_CNTXT_ACC，记录消息长度*/
    pTmpSendMsg[ulSum++] = NAS_ESMCN_MSG_TYPE_DEACT_EPS_BEARER_CNTXT_ACC;

    *pulLength = ulSum ;

}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodePapContent
 Description     : PAP鉴权码流编码
 Input           : VOS_UINT8                   *pSendMsg
                   APP_ESM_GW_AUTH_INFO_STRU   *pstGwAuthInfo
                   VOS_UINT32                  *pulLength

 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-7-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodePapContent
(
    VOS_UINT8                          *pSendMsg,
    APP_ESM_GW_AUTH_INFO_STRU          *pstGwAuthInfo,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;
    APP_ESM_GW_AUTH_INFO_STRU          *pstTmpGwAuthInfo=pstGwAuthInfo;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                           ucGwAuthId      = NAS_ESM_NULL;
    VOS_UINT32                          ulIndex         = NAS_ESM_NULL;
    VOS_UINT32                          ulIndex1        = NAS_ESM_NULL;
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;

    NAS_ESM_NORM_LOG("NAS_ESM_EncodePapContent:enter ");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePapContent_ENUM, LNAS_ENTRY);

    /*赋值 Protocol ID */
    usItemId                            = NAS_ESM_PCO_ITEM_TYPE_PAP;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE) >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Length of protocol ID contents*/
    /*保存PAP信元长度index，统计长度后存入*/
    ulIndex                             = ulSum++;

    /*赋值Protocol ID content*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_PCO_AUTH_REQ_TYPE;
    NAS_ESM_AssignGwIpId(&ucGwAuthId);
    pTmpSendMsg[ulSum++]                = ucGwAuthId;

    /*保存PAP配置请求信元长度index，统计长度后存入，长度占用2个字节，
     实际不会超过一个字节，因此记录的index在第2个字节处*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_NULL;
    ulIndex1                            = ulSum++;

    pTmpSendMsg[ulSum++]                = pstTmpGwAuthInfo->ucUserNameLen;

    NAS_ESM_MEM_CPY_S(  &pTmpSendMsg[ulSum],
                        pstTmpGwAuthInfo->ucUserNameLen,
                        pstTmpGwAuthInfo->aucUserName,
                        pstTmpGwAuthInfo->ucUserNameLen);
    ulSum                               += pstTmpGwAuthInfo->ucUserNameLen;

    pTmpSendMsg[ulSum++]                = pstTmpGwAuthInfo->ucPwdLen;
    NAS_ESM_MEM_CPY_S(  &pTmpSendMsg[ulSum],
                        pstTmpGwAuthInfo->ucPwdLen,
                        pstTmpGwAuthInfo->aucPwd,
                        pstTmpGwAuthInfo->ucPwdLen);
    ulSum                               += pstTmpGwAuthInfo->ucPwdLen;

    /*填充相应长度信息*/
    pTmpSendMsg[ulIndex1]               = (VOS_UINT8)((ulSum-ulIndex)-1);
    pTmpSendMsg[ulIndex]                = (VOS_UINT8)((ulSum-ulIndex)-1);

    *pulLength                          = ulSum;

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeChapContent
 Description     : CHAP鉴权码流编码
 Input           : VOS_UINT8                   *pSendMsg
                   APP_ESM_GW_AUTH_INFO_STRU   *pstGwAuthInfo
                   VOS_UINT32                  *pulLength
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-7-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeChapContent
(
    VOS_UINT8                          *pSendMsg,
    APP_ESM_GW_AUTH_INFO_STRU          *pstGwAuthInfo,
    VOS_UINT32                         *pulLength
)

{

    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;
    APP_ESM_GW_AUTH_INFO_STRU          *pstTmpGwAuthInfo=pstGwAuthInfo;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                           ucGwAuthId      = NAS_ESM_NULL;
    VOS_UINT8                           aucChlgVal[NAS_ESM_AUTH_CHALLENGE_VALUE_LEN];
    VOS_UINT8                           aucRspVal[NAS_ESM_AUTH_RESPONSE_VALUE_LEN];
    VOS_UINT32                           ulIndex         = NAS_ESM_NULL;
    VOS_UINT32                           ulIndex1        = NAS_ESM_NULL;
    VOS_UINT32                          usItemId     = NAS_ESM_NULL;

    NAS_ESM_NORM_LOG("NAS_ESM_EncodeChapContent:enter ");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeChapContent_ENUM, LNAS_ENTRY);

    /*填充CHAP Challenge message*/
    /*赋值 Protocol ID */
    usItemId                            = NAS_ESM_PCO_ITEM_TYPE_CHAP;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE) >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Length of protocol ID contents*/
    /*保存CHAP信元长度index，统计长度后存入*/
    ulIndex                             = ulSum ++;

    /*赋值Protocol ID content*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_PCO_AUTH_REQ_TYPE;
    NAS_ESM_AssignGwIpId(&ucGwAuthId);
    pTmpSendMsg[ulSum++]                = ucGwAuthId;

    /*保存CHAP配置请求信元长度index，统计长度后存入，长度占用2个字节，
      实际不会超过一个字节，因此记录的index在第2个字节处*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_NULL;
    ulIndex1                            = ulSum++;


    pTmpSendMsg[ulSum++]                = NAS_ESM_AUTH_CHALLENGE_VALUE_LEN;

    NAS_ESM_GetGwAuthChallengeValue(aucChlgVal);
    /* coverity[uninit_use_in_call] */

    NAS_ESM_MEM_CPY_S(  &pTmpSendMsg[ulSum],
                        NAS_ESM_AUTH_CHALLENGE_VALUE_LEN,
                        aucChlgVal,
                        NAS_ESM_AUTH_CHALLENGE_VALUE_LEN);
    ulSum                               += NAS_ESM_AUTH_CHALLENGE_VALUE_LEN;

    NAS_ESM_MEM_CPY_S(  &pTmpSendMsg[ulSum],
                        pstTmpGwAuthInfo->ucUserNameLen,
                        pstTmpGwAuthInfo->aucUserName,
                        pstTmpGwAuthInfo->ucUserNameLen);

    ulSum                               += pstTmpGwAuthInfo->ucUserNameLen;

    /*填充相应长度信息*/
    pTmpSendMsg[ulIndex1]               = (VOS_UINT8)((ulSum-ulIndex)-1);
    pTmpSendMsg[ulIndex]                = (VOS_UINT8)((ulSum-ulIndex)-1);


    /*填充CHAP Response message*/
    /*l00258641 消除fortify告警 begin*/
    /*ulIndex                             = NAS_ESM_NULL;*/
    /*l00258641 消除fortify告警 end*/
    ulIndex1                            = NAS_ESM_NULL;
    /*赋值 Protocol ID */
    usItemId                            = NAS_ESM_PCO_ITEM_TYPE_CHAP;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE) >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Length of protocol ID contents*/
    /*保存CHAP信元长度index，统计长度后存入*/
    ulIndex                             = ulSum ++;

    /*赋值Protocol ID content*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_PCO_AUTH_RSP_TYPE;
    pTmpSendMsg[ulSum++]                = ucGwAuthId;

    /*保存CHAP配置请求信元长度index，统计长度后存入，长度占用2个字节，
      实际不会超过一个字节，因此记录的index在第2个字节处*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_NULL;
    ulIndex1                            = ulSum++;

    pTmpSendMsg[ulSum++]                = NAS_ESM_AUTH_RESPONSE_VALUE_LEN;

    NAS_ESM_GetGwAuthRpsValue(          pstTmpGwAuthInfo->aucPwd,
                                        pstTmpGwAuthInfo->ucPwdLen,
                                        ucGwAuthId,
                                        aucChlgVal,
                                        aucRspVal);

    /* coverity[uninit_use_in_call] */

    NAS_ESM_MEM_CPY_S(                  &pTmpSendMsg[ulSum],
                                        NAS_ESM_AUTH_RESPONSE_VALUE_LEN,
                                        aucRspVal,
                                        NAS_ESM_AUTH_RESPONSE_VALUE_LEN);
    ulSum                               += NAS_ESM_AUTH_RESPONSE_VALUE_LEN;

    NAS_ESM_MEM_CPY_S(                  &pTmpSendMsg[ulSum],
                                        pstTmpGwAuthInfo->ucUserNameLen,
                                        pstTmpGwAuthInfo->aucUserName,
                                        pstTmpGwAuthInfo->ucUserNameLen);

    ulSum                               += pstTmpGwAuthInfo->ucUserNameLen;

    /*填充相应长度信息*/
    pTmpSendMsg[ulIndex1]               = (VOS_UINT8)((ulSum-ulIndex)-1);
    pTmpSendMsg[ulIndex]                = (VOS_UINT8)((ulSum-ulIndex)-1);

    *pulLength                          = ulSum;
    return;
}
/*****************************************************************************
 Function Name   : NAS_ESM_EncodeChapContent_PPP
 Description     : PPP拨号时CHAP鉴权码流编码
 Input           : VOS_UINT8                   *pSendMsg
                   APP_ESM_GW_AUTH_INFO_STRU   *pstGwAuthInfo
                   VOS_UINT32                  *pulLength
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    niuxiufan  00181501      2012-8-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeChapContent_PPP
(
    VOS_UINT8                          *pSendMsg,
    const APP_ESM_AUTH_INFO_STRU       *pstAuthInfo,
    VOS_UINT32                         *pulLength
)

{

    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;
    VOS_UINT32                          ulSum           = *pulLength;

    VOS_UINT32                          ulIndex         = NAS_ESM_NULL;
    VOS_UINT32                          ulIndex1        = NAS_ESM_NULL;
    VOS_UINT32                          usItemId     = NAS_ESM_NULL;

    /*填充CHAP Challenge message*/
    /*赋值 Protocol ID */
    usItemId                            = NAS_ESM_PCO_ITEM_TYPE_CHAP;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE) >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Length of protocol ID contents*/
    /*保存CHAP信元长度index，统计长度后存入*/
    ulIndex                             = ulSum ++;

    /*赋值Protocol ID content*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_PCO_AUTH_REQ_TYPE;

    pTmpSendMsg[ulSum++]                = pstAuthInfo->ucAuthId;

    /*保存CHAP配置请求信元长度index，统计长度后存入，长度占用2个字节，
      实际不会超过一个字节，因此记录的index在第2个字节处*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_NULL;
    ulIndex1                            = ulSum++;


    pTmpSendMsg[ulSum++]                = (VOS_UINT8)pstAuthInfo->unAuthParam.stChapParam.ulChallengeLen;

    NAS_ESM_MEM_CPY_S(                  &pTmpSendMsg[ulSum],
                                        pstAuthInfo->unAuthParam.stChapParam.ulChallengeLen,
                                        pstAuthInfo->unAuthParam.stChapParam.aucChallenge,
                                        pstAuthInfo->unAuthParam.stChapParam.ulChallengeLen);
    ulSum                               += pstAuthInfo->unAuthParam.stChapParam.ulChallengeLen;

    NAS_ESM_MEM_CPY_S(                  &pTmpSendMsg[ulSum],
                                        pstAuthInfo->unAuthParam.stChapParam.ulChallengeNameLen,
                                        pstAuthInfo->unAuthParam.stChapParam.aucChallengeName,
                                        pstAuthInfo->unAuthParam.stChapParam.ulChallengeNameLen);

    ulSum                               += pstAuthInfo->unAuthParam.stChapParam.ulChallengeNameLen;

    /*填充相应长度信息*/
    pTmpSendMsg[ulIndex1]               = (VOS_UINT8)((ulSum-ulIndex)-1);
    pTmpSendMsg[ulIndex]                = (VOS_UINT8)((ulSum-ulIndex)-1);


    /*填充CHAP Response message*/
    /*l00258641 消除fortify告警 begin*/
    /*ulIndex                             = NAS_ESM_NULL;*/
    /*l00258641 消除fortify告警 end*/
    /*ulIndex1                            = NAS_ESM_NULL;*/
    /*赋值 Protocol ID */
    usItemId                            = NAS_ESM_PCO_ITEM_TYPE_CHAP;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE) >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Length of protocol ID contents*/
    /*保存CHAP信元长度index，统计长度后存入*/
    ulIndex                             = ulSum ++;

    /*赋值Protocol ID content*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_PCO_AUTH_RSP_TYPE;
    pTmpSendMsg[ulSum++]                = pstAuthInfo->ucAuthId;

    /*保存CHAP配置请求信元长度index，统计长度后存入，长度占用2个字节，
      实际不会超过一个字节，因此记录的index在第2个字节处*/
    pTmpSendMsg[ulSum++]                = NAS_ESM_NULL;
    ulIndex1                            = ulSum++;

    pTmpSendMsg[ulSum++]                = (VOS_UINT8)pstAuthInfo->unAuthParam.stChapParam.ulResponseLen;

    NAS_ESM_MEM_CPY_S(                  &pTmpSendMsg[ulSum],
                                        pstAuthInfo->unAuthParam.stChapParam.ulResponseLen,
                                        pstAuthInfo->unAuthParam.stChapParam.aucResponse,
                                        pstAuthInfo->unAuthParam.stChapParam.ulResponseLen);
    ulSum                               += pstAuthInfo->unAuthParam.stChapParam.ulResponseLen;

    NAS_ESM_MEM_CPY_S(                  &pTmpSendMsg[ulSum],
                                        pstAuthInfo->unAuthParam.stChapParam.ucResponseNameLen,
                                        pstAuthInfo->unAuthParam.stChapParam.aucResponseName,
                                        pstAuthInfo->unAuthParam.stChapParam.ucResponseNameLen);

    ulSum                               += pstAuthInfo->unAuthParam.stChapParam.ucResponseNameLen;

    /*填充相应长度信息*/
    pTmpSendMsg[ulIndex1]               = (VOS_UINT8)((ulSum-ulIndex)-1);
    pTmpSendMsg[ulIndex]                = (VOS_UINT8)((ulSum-ulIndex)-1);

    *pulLength                          = ulSum;
    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_EncodeIpcpContent
 Description     : IPCP码流编码
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-7-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeIpcpContent
(
    const NAS_ESM_SDF_PARA_STRU        *pstSdfPara,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;
    VOS_UINT32                          ulTmpIndex      = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpIndex2     = NAS_ESM_NULL;
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                           ucGwAuthId      = NAS_ESM_NULL;

    if ((NAS_ESM_OP_TRUE == pstSdfPara->bitOpPdnType)
        && (APP_ESM_PDN_TYPE_IPV6 == pstSdfPara->enPdnType))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_EncodeIpcpContent:PDN type is ipv6!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeIpcpContent_ENUM, LNAS_ENTRY);

        *pulLength = ulSum;

        return ;
    }

    /*IPCP for DNS Server begin*/
    usItemId = NAS_ESM_PCO_ITEM_TYPE_IPCP;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE)
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*保存IPCP信元长度index，统计长度后存入*/
    ulTmpIndex = ulSum++;

    /*填写IPCP内容*/
    /*
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |     Code      |  Identifier   |            Length             |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    | Options ...
    +-+-+-+-+
    */
    pTmpSendMsg[ulSum++] = NAS_ESM_IPCP_MSG_TYPE_CONFIGURE_REQ;

    NAS_ESM_AssignGwIpId(&ucGwAuthId);
    pTmpSendMsg[ulSum++] = ucGwAuthId;/*id*/

    /*保存IPCP配置请求信元长度index，统计长度后存入，长度占用2个字节，
      实际不会超过一个字节，因此记录的index在第2个字节处*/
    pTmpSendMsg[ulSum++] = NAS_ESM_NULL;
    ulTmpIndex2 = ulSum++;

    /*填写IPCP Options内容*/
    /*
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |     Type      |    Length     |           IP-Address
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            IP-Address (cont)       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    pTmpSendMsg[ulSum++] = NAS_ESM_IPCP_OPTIONS_PRI_DNS_ADDR;
    pTmpSendMsg[ulSum++] = NAS_ESM_IPCP_OPTION_DNS_LEN;
    pTmpSendMsg[ulSum++] = 0;
    pTmpSendMsg[ulSum++] = 0;
    pTmpSendMsg[ulSum++] = 0;
    pTmpSendMsg[ulSum++] = 0;
    pTmpSendMsg[ulSum++] = NAS_ESM_IPCP_OPTIONS_SEC_DNS_ADDR;
    pTmpSendMsg[ulSum++] = NAS_ESM_IPCP_OPTION_DNS_LEN;
    pTmpSendMsg[ulSum++] = 0;
    pTmpSendMsg[ulSum++] = 0;
    pTmpSendMsg[ulSum++] = 0;
    pTmpSendMsg[ulSum++] = 0;

    /*保存相应长度信息*/
    pTmpSendMsg[ulTmpIndex2] = (VOS_UINT8)((ulSum - ulTmpIndex) -1);
    pTmpSendMsg[ulTmpIndex]  = (VOS_UINT8)((ulSum - ulTmpIndex) -1);
    /*IPCP for DNS Server end*/

    *pulLength = ulSum;
}
/*****************************************************************************
 Function Name   : NAS_ESM_EncodeIpv4AllocMode
 Description     : 编码IPV4 获取方式
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-03-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeIpv4AllocMode
(
    const NAS_ESM_SDF_PARA_STRU        *pstSdfPara,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;

    if ((NAS_ESM_OP_TRUE == pstSdfPara->bitOpPdnType)
        && (APP_ESM_PDN_TYPE_IPV6 == pstSdfPara->enPdnType))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_EncodeIpv4AllocMode:PDN type is ipv6!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeIpv4AllocMode_ENUM, LNAS_ENTRY);

        *pulLength = ulSum;

        return ;
    }

    /*赋值Container ID:IP address allocation via NAS signalling */
    usItemId = NAS_ESM_PCO_ITEM_TYPE_NAS_SIGNALING;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE)
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Container LEN:IP address allocation via NAS signalling */
    pTmpSendMsg[ulSum++] = NAS_ESM_NULL;

    *pulLength                          = ulSum;
    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_EncodeIpv4DnsReq
 Description     : 编码IPV4 DNS请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-03-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeIpv4DnsReq
(
    const NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;

    if ((NAS_ESM_OP_TRUE == pstSdfPara->bitOpPdnType)
        && (APP_ESM_PDN_TYPE_IPV6 == pstSdfPara->enPdnType))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_EncodeIpv4DnsReq:PDN type is ipv6!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeIpv4DnsReq_ENUM, LNAS_ENTRY);

        *pulLength = ulSum;

        return ;
    }

    /*赋值Container ID:DNS Server IPv4 Address Request */
    usItemId = NAS_ESM_PCO_ITEM_TYPE_DNS_SERVER_IPV4;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE)
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Container LEN:DNS Server IPv4 Address Request */
    pTmpSendMsg[ulSum++] = NAS_ESM_NULL;

    *pulLength                          = ulSum;
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeIpv4PcscfReq
 Description     : 编码IPV4 P-CSCF请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-03-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeIpv4PcscfReq
(
    const NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;

    if ((NAS_ESM_OP_TRUE == pstSdfPara->bitOpPdnType)
        && (APP_ESM_PDN_TYPE_IPV6 == pstSdfPara->enPdnType))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_EncodeIpv4PcscfReq:PDN type is ipv6!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeIpv4PcscfReq_ENUM, LNAS_ENTRY);

        *pulLength = ulSum;

        return ;
    }

    /*赋值Container ID:P-CSCF IPv4 Address Request */
    usItemId = NAS_ESM_PCO_ITEM_TYPE_PCSCF_IPV4;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE)
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Container LEN:P-CSCF IPv4 Address Request */
    pTmpSendMsg[ulSum++] = NAS_ESM_NULL;

    *pulLength                          = ulSum;
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeIpv6PcscfReq
 Description     : 编码IPV6 P-CSCF请求
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2013-07-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeIpv6PcscfReq
(
    const NAS_ESM_SDF_PARA_STRU        *pstSdfPara,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;

    if ((NAS_ESM_OP_TRUE == pstSdfPara->bitOpPdnType)
        && (APP_ESM_PDN_TYPE_IPV4 == pstSdfPara->enPdnType))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_EncodeIpv6PcscfReq:PDN type is ipv4!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeIpv6PcscfReq_ENUM, LNAS_ENTRY);

        *pulLength = ulSum;

        return ;
    }

    /*赋值Container ID:P-CSCF IPv6 Address Request */
    usItemId = NAS_ESM_PCO_ITEM_TYPE_PCSCF_IPV6;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE)
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Container LEN:P-CSCF IPv6 Address Request */
    pTmpSendMsg[ulSum++] = NAS_ESM_NULL;

    *pulLength                          = ulSum;
    return;
}



/*****************************************************************************
 Function Name   : NAS_ESM_EncodePcoBcm
 Description     : 编码BCM
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodePcoBcm
(
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;
    /*EMM_ESM_RAT_TYPE_ENUM_UINT8         enRatType       = EMM_ESM_RAT_BUTT;*/

    if (NAS_ESM_GetBcmFlag() == NAS_ESM_FUN_CTRL_OFF)
    {
        return ;
    }

    /* 如果只支持LTE，不支持A/Gb或者Iu时，不编码BCM */
    if (NAS_ESM_FAILURE == NAS_EMM_lteRatIsExist())
    {
        return ;
    }

    /*赋值MS Support of Network Requested Bearer Control indicator */
    usItemId = NAS_ESM_PCO_ITEM_TYPE_BCM;
    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE)
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Container LEN:MS Support of Network Requested Bearer Control indicator */
    pTmpSendMsg[ulSum++] = NAS_ESM_NULL;

    *pulLength                          = ulSum;
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeIpv6DnsReq
 Description     : 编码IPV6 DNS请求
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-03-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeIpv6DnsReq
(
    const NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;

    if ((NAS_ESM_OP_TRUE == pstSdfPara->bitOpPdnType)
        && ((APP_ESM_PDN_TYPE_IPV6 == pstSdfPara->enPdnType)
            || (APP_ESM_PDN_TYPE_IPV4_IPV6 == pstSdfPara->enPdnType)))
    {
        /*赋值Container ID:DNS Server IPv6 Address Request */
        usItemId = NAS_ESM_PCO_ITEM_TYPE_DNS_SERVER_IPV6;
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE)
                                                        >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

        /*赋值Container LEN:DNS Server IPv6 Address Request */
        pTmpSendMsg[ulSum++] = NAS_ESM_NULL;
    }

    *pulLength                          = ulSum;
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeImCnSignalFlag
 Description     : 编码"IM CN Subsystem Signaling Flag"
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2013-07-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeImCnSignalFlag
(
    const NAS_ESM_SDF_PARA_STRU        *pstSdfPara,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;

    if ((NAS_ESM_OP_TRUE != pstSdfPara->bitOpImsCnSignalFlag)
        || (APP_ESM_PDP_FOR_IMS_CN_SIG_ONLY != pstSdfPara->enImsCnSignalFlag))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_EncodeImCnSignalFlag:not ims bearer!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeImCnSignalFlag_ENUM, LNAS_ENTRY);

        *pulLength = ulSum;

        return ;
    }

    /*赋值Container ID:IM CN Subsystem Signaling Flag */
    usItemId                = NAS_ESM_PCO_ITEM_TYPE_IM_CN_SIGNAL_FLAG;
    pTmpSendMsg[ulSum++]    = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE)
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
    pTmpSendMsg[ulSum++]    = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    /*赋值Container LEN:IM CN Subsystem Signaling Flag */
    pTmpSendMsg[ulSum++]    = NAS_ESM_NULL;

    *pulLength              = ulSum;
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodePcoLocalIp
 Description     : 编码"MS support of Local address in TFT indicator"
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2014-09-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodePcoLocalIp
(
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT16                          usItemId        = NAS_ESM_NULL;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;

    if (NAS_ESM_GetLocalIpSupFlag() == NAS_ESM_FUN_CTRL_OFF)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_EncodePcoLocalIp:not support local ip!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePcoLocalIp_ENUM, LNAS_ENTRY);

        *pulLength = ulSum;
        return ;
    }
    usItemId = NAS_ESM_PCO_ITEM_TYPE_LOCAL_ADDRESS;

    pTmpSendMsg[ulSum++] = (VOS_UINT8)((usItemId & NAS_ESM_HIGH_BYTE)
                                                    >> NAS_ESM_MOVEMENT_8_BITS);

    pTmpSendMsg[ulSum++] = (VOS_UINT8)(usItemId & NAS_ESM_LOW_BYTE);

    pTmpSendMsg[ulSum++] = NAS_ESM_NULL;

    *pulLength                          = ulSum;

    return;

}

/*****************************************************************************
 Function Name  : NAS_ESM_IsNeedEncodePapOrChap
 Description    : 判断是否需要编码PAP或者CHAP
 Input          : NAS_ESM_SDF_PARA_STRU              *pstSdfPara
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong00150010      2012-11-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsNeedEncodePapOrChap
(
    const NAS_ESM_SDF_PARA_STRU        *pstSdfPara
)
{
    if ((APP_ESM_BEARER_TYPE_EMERGENCY != pstSdfPara->enBearerCntxtType) &&
        (NAS_ESM_OP_TRUE == pstSdfPara->bitOpGwAuthInfo) &&
        (pstSdfPara->stGwAuthInfo.ucUserNameLen > NAS_ESM_NULL) &&
        (NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
/*****************************************************************************
 Function Name  : NAS_ESM_EncodePapOrChap
 Description    : 编码PAP或者CHAP
 Input          : NAS_ESM_SDF_PARA_STRU              *pstSdfPara
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2014-09-28  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodePapOrChap
(
    VOS_UINT8                          *pSendMsg,
    APP_ESM_GW_AUTH_INFO_STRU          *pstGwAuthInfo,
    VOS_UINT32                         *pulLength,
    VOS_UINT8                           ucUserNameLen,
    VOS_UINT8                           ucPwdLen
)
{
    /* PCO消息最大长度为253，若用户名和密码为127时将超过PCO消息最大长度，GU在AUTH编码时允许用户名和密码最大长度为99,根据GU此处用户名或者密码大于99时不编码AUTH */
    if ((APP_ESM_MAX_USER_NAME_ENCODE_LEN < ucUserNameLen)
        || (APP_ESM_MAX_PASSWORD_ENCODE_LEN < ucPwdLen))
    {
         NAS_ESM_NORM_LOG("NAS_ESM_EncodePco:Input gw auth len is err!");
         TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePapOrChap_ENUM, LNAS_ENTRY);

    }
    else
    {
        if (APP_ESM_AUTH_TYPE_PAP == pstGwAuthInfo->enGwAuthType)
        {
            NAS_ESM_EncodePapContent(pSendMsg,pstGwAuthInfo,pulLength);
        }

        if (APP_ESM_AUTH_TYPE_CHAP == pstGwAuthInfo->enGwAuthType)
        {

            NAS_ESM_EncodeChapContent(pSendMsg,pstGwAuthInfo,pulLength);
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EncodePco()
 Description    : SM模块组装PCO消息函数
 Input          : VOS_UINT8 *pSendMsg,
                  VOS_UINT32 ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.聂州渝 00108792      2008-09-22  Draft Enact
      2.sunbing 49683        2009-02-05  Modify
      3.niuxiufan 00181501   2012-4-23   Modify DTS2012042104730

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodePco
(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength,
    NAS_MSG_FORMAT_ENUM_UINT8           enEncodeTp
)
{
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT32                          ulIndex         = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpIndex      = NAS_ESM_NULL;
    APP_ESM_GW_AUTH_INFO_STRU          *pstTmpGwAuthInfo =&pstSdfPara->stGwAuthInfo;
    VOS_UINT8                           ucImsSuppFlag   = VOS_FALSE;


    NAS_ESM_INFO_LOG("NAS_ESM_EncodePco:INFO:NAS_ESM_EncodePCO been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePco_ENUM, LNAS_ENTRY);

    if( VOS_NULL_PTR == pTmpSendMsg)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodePco:ERROR: No SmMsg!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePco_ENUM, 1);
        return NAS_ESM_FAILURE;
    }
    /* 删除PCO flag相关无效代码 y00307272 20151205 DTS2015101700432 */
    if(NAS_MSG_FORMAT_TLV == enEncodeTp)
    {
        /*可选参数,存放PCO信息IEI参数*/
        pTmpSendMsg[ulSum++] = NAS_ESM_MSG_PCO_IEI;
    }

    /*保存长度Index，长度统计后再存放*/
    ulIndex = ulSum++;

    /*按照PPP for use with IP PDP type处理*/
    pTmpSendMsg[ulSum++] = NAS_ESM_PCO_CONFIG_PROTOCOL;

    /* 目前判断bitOpGwAuthInfo为1，且用户名长度大于0，才认为存在鉴权信息 ,且存在APN时才会在编码PCO信元中带给网侧*/
    if (VOS_TRUE == NAS_ESM_IsNeedEncodePapOrChap(pstSdfPara))
    {
        ulTmpIndex                      = NAS_ESM_NULL;
        (VOS_VOID)NAS_ESM_EncodePapOrChap(pTmpSendMsg + ulSum,pstTmpGwAuthInfo,&ulTmpIndex,pstSdfPara->stGwAuthInfo.ucUserNameLen,
                                pstSdfPara->stGwAuthInfo.ucPwdLen);
        ulSum                           = ulSum + ulTmpIndex;


    }

    /*#if (NAS_ESM_RELEASE_CTRL_R8 == NAS_ESM_RELEASE_CTRL)*/
    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodeIpcpContent(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;
    /*#endif*/

    if (NAS_ESM_GET_IPV6_DNS_CTRL_ON == NAS_ESM_GetIpv6DnsFlag())
    {
       ulTmpIndex                          = NAS_ESM_NULL;

       /*赋值Container ID:IPv6 DNS Request */
       NAS_ESM_EncodeIpv6DnsReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
       ulSum                               = ulSum + ulTmpIndex;

       /*为获取第二个IPv6 DNS，根据实际网络验证，需要携带第二个IPv6的DNS请求 */
       /*赋值Container ID:IPv6 DNS Request */
       /*ulTmpIndex                          = NAS_ESM_NULL;
       NAS_ESM_EncodeIpv6DnsReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
       ulSum                               = ulSum + ulTmpIndex;*/
    }

    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodeIpv4AllocMode(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;

    /* 如果是IMS承载，则携带"0002H (IM CN Subsystem Signaling Flag)" */
    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodeImCnSignalFlag(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;

    if (VOS_OK != APP_GetCidImsSuppFlag((VOS_UINT8)pstSdfPara->ulCId, &ucImsSuppFlag))
    {
        ucImsSuppFlag                   = VOS_FALSE;
    }
    if (((NAS_ESM_OP_TRUE == pstSdfPara->bitOpImsCnSignalFlag)
        && (APP_ESM_PDP_FOR_IMS_CN_SIG_ONLY == pstSdfPara->enImsCnSignalFlag))
        || (VOS_TRUE == ucImsSuppFlag))
    {
        ulTmpIndex                          = NAS_ESM_NULL;
        NAS_ESM_EncodeIpv4PcscfReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
        ulSum                               = ulSum + ulTmpIndex;

        /*为获取备用IPV4 P-CSCF，需在编码第二个IPV4 P-CSCF请求
          移动VoLTE测试，阿郎网络不支持发送两个P-CSCF请求，协议没有明确描述，删除两次获取
        */
        /*ulTmpIndex                          = NAS_ESM_NULL;
        NAS_ESM_EncodeIpv4PcscfReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
        ulSum                               = ulSum + ulTmpIndex;*/

        ulTmpIndex                          = NAS_ESM_NULL;
        NAS_ESM_EncodeIpv6PcscfReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
        ulSum                               = ulSum + ulTmpIndex;

        /*为获取备用IPV6 P-CSCF，需在编码第二个IPV6 P-CSCF请求
          移动VoLTE测试，阿郎网络不支持发送两个P-CSCF请求，协议没有明确描述，删除两次获取
        */
        /*ulTmpIndex                          = NAS_ESM_NULL;
        NAS_ESM_EncodeIpv6PcscfReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
        ulSum                               = ulSum + ulTmpIndex;*/
    }


    /*#if (NAS_ESM_RELEASE_CTRL_R9 == NAS_ESM_RELEASE_CTRL)*/
    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodeIpv4DnsReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;
    /*为获取备用DNS，需在编码第二个DNS请求 */
    /*ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodeIpv4DnsReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;*/
    /*#endif*/


    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodePcoBcm((pTmpSendMsg + ulSum), &ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_EncodePco:R11!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePco_ENUM, 3);
        ulTmpIndex                          = NAS_ESM_NULL;
        NAS_ESM_EncodePcoLocalIp((pTmpSendMsg + ulSum), &ulTmpIndex);
        ulSum                               = ulSum + ulTmpIndex;
    }

    /*赋值Length of protocol config. options contents*/
    pTmpSendMsg[ulIndex] = (VOS_UINT8)((ulSum - ulIndex) - 1);

    if(ulSum <= NAS_ESM_MAX_PCO_BYTE)
    {
        *pulLength = ulSum;
    }
    else
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_ENCODE_CN_MSG_IE_LEN_INVALID,
                                        ulSum);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePco_ENUM, 4);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}
/*****************************************************************************
 Function Name  : NAS_ESM_EncodePco_PPP()
 Description    : SM模块组装PPP拨号PCO消息函数
 Input          : VOS_UINT8 *pSendMsg,
                  VOS_UINT32 ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.niuxiufan 00181501   2012-8-14   Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodePco_PPP
(
    const NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    const APP_ESM_PPP_INFO_STRU        *pstPppInfo,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength,
    NAS_MSG_FORMAT_ENUM_UINT8           enEncodeTp
)
{
    VOS_UINT8                          *pTmpSendMsg     = pSendMsg;
    VOS_UINT32                          ulSum           = *pulLength;
    VOS_UINT32                          ulIndex         = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpIndex      = NAS_ESM_NULL;
    APP_ESM_GW_AUTH_INFO_STRU          *pstTmpGwAuthInfo = {NAS_ESM_NULL};


    NAS_ESM_INFO_LOG("NAS_ESM_EncodePco_PPP:INFO:NAS_ESM_EncodePco_PPP been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodePco_PPP_ENUM, LNAS_ENTRY);

    if( VOS_NULL_PTR == pTmpSendMsg)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodePco_PPP:ERROR: No SmMsg!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePco_PPP_ENUM, 1);
        return NAS_ESM_FAILURE;
    }
    /* 删除PCO flag相关无效代码 y00307272 20151205 DTS2015101700432 */
    /*申请临时变量内存 */
    pstTmpGwAuthInfo = NAS_ESM_MEM_ALLOC(sizeof(APP_ESM_GW_AUTH_INFO_STRU));
    if (VOS_NULL_PTR == pstTmpGwAuthInfo)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_EncodePco_PPP:Mem Alloc Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_EncodePco_PPP_ENUM, LNAS_EMM_ALLOC_FAIL);
        return NAS_ESM_FAILURE;
    }

    if(NAS_MSG_FORMAT_TLV == enEncodeTp)
    {
        /*可选参数,存放PCO信息IEI参数*/
        pTmpSendMsg[ulSum++] = NAS_ESM_MSG_PCO_IEI;
    }

    /*保存长度Index，长度统计后再存放*/
    ulIndex = ulSum++;

    /*按照PPP for use with IP PDP type处理*/
    pTmpSendMsg[ulSum++] = NAS_ESM_PCO_CONFIG_PROTOCOL;

    /* 鉴权方式不为NONE时且APN存在时才编码鉴权信息*/
    if ((APP_ESM_AUTH_TYPE_NONE != pstPppInfo->stAuthInfo.enAuthType)
         && (NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn)
         && (VOS_TRUE == NAS_ESM_VerifyAppAuthParam_PPP(&(pstPppInfo->stAuthInfo)))
         && (APP_ESM_BEARER_TYPE_EMERGENCY != pstSdfPara->enBearerCntxtType))
    {
        if (APP_ESM_AUTH_TYPE_PAP == pstPppInfo->stAuthInfo.enAuthType)
        {

            pstTmpGwAuthInfo->ucUserNameLen = pstPppInfo->stAuthInfo.unAuthParam.stPapParam.ucUsernameLen;
            pstTmpGwAuthInfo->ucPwdLen = pstPppInfo->stAuthInfo.unAuthParam.stPapParam.ucPasswordLen;

            NAS_ESM_MEM_CPY_S(  pstTmpGwAuthInfo->aucUserName,
                                APP_ESM_MAX_USER_NAME_LEN,
                                pstPppInfo->stAuthInfo.unAuthParam.stPapParam.aucUsername,
                                pstTmpGwAuthInfo->ucUserNameLen);

            NAS_ESM_MEM_CPY_S(  pstTmpGwAuthInfo->aucPwd,
                                APP_ESM_MAX_PASSWORD_LEN,
                                pstPppInfo->stAuthInfo.unAuthParam.stPapParam.aucPassword,
                                pstTmpGwAuthInfo->ucPwdLen);

            ulTmpIndex                      = NAS_ESM_NULL;
            NAS_ESM_EncodePapContent(pTmpSendMsg + ulSum,pstTmpGwAuthInfo,&ulTmpIndex);
            ulSum                           = ulSum + ulTmpIndex;

        }

        if (APP_ESM_AUTH_TYPE_CHAP == pstPppInfo->stAuthInfo.enAuthType)
        {

            NAS_ESM_EncodeChapContent_PPP(pTmpSendMsg + ulSum,&(pstPppInfo->stAuthInfo),&ulTmpIndex);
            ulSum                           = ulSum + ulTmpIndex;
        }
    }

    /*释放内存 */
    NAS_ESM_MEM_FREE(pstTmpGwAuthInfo);

    #if (NAS_ESM_RELEASE_CTRL_R8 == NAS_ESM_RELEASE_CTRL)
    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodeIpcpContent(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;
    #endif


    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodeIpv4AllocMode(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;

    if (NAS_ESM_GetPcscfFlag() == NAS_ESM_FUN_CTRL_ON)
    {
        ulTmpIndex                          = NAS_ESM_NULL;
        NAS_ESM_EncodeIpv4PcscfReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
        ulSum                               = ulSum + ulTmpIndex;
    }


    #if (NAS_ESM_RELEASE_CTRL_R9 == NAS_ESM_RELEASE_CTRL)
    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodeIpv4DnsReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;
    /*为获取备用DNS，需在编码第二个DNS请求 */
    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodeIpv4DnsReq(pstSdfPara, (pTmpSendMsg + ulSum),&ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;
    #endif


    ulTmpIndex                          = NAS_ESM_NULL;
    NAS_ESM_EncodePcoBcm((pTmpSendMsg + ulSum), &ulTmpIndex);
    ulSum                               = ulSum + ulTmpIndex;

    /*赋值Length of protocol config. options contents*/
    pTmpSendMsg[ulIndex] = (VOS_UINT8)((ulSum - ulIndex) - 1);

    if(ulSum <= NAS_ESM_MAX_PCO_BYTE)
    {
        *pulLength = ulSum;
    }
    else
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_ENCODE_CN_MSG_IE_LEN_INVALID,
                                        ulSum);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodePco_PPP_ENUM, LNAS_FAIL);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_IsApnCharacterValid
 Description     : 判断APN某一字符是否有效
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2009-7-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsApnCharacterValid
(
    VOS_UINT8 ucCharacter,
    NAS_ESM_APN_VERIFY_CHARACTER_TYPE_ENUM_UINT8 enApnVerifyCharacterType
)
{
    PS_BOOL_ENUM_UINT8                  enIsUpperAToZ = PS_FALSE;
    PS_BOOL_ENUM_UINT8                  enIsLowerAToZ = PS_FALSE;
    PS_BOOL_ENUM_UINT8                  enIsDigit     = PS_FALSE;
    PS_BOOL_ENUM_UINT8                  enIsHyphen    = PS_FALSE;

    /* 判断是否为字符A-Z */
    enIsUpperAToZ = ((ucCharacter >= 'A') && (ucCharacter <= 'Z'));

    /* 判断是否为字符a-z */
    enIsLowerAToZ = ((ucCharacter >= 'a') && (ucCharacter <= 'z'));

    /* 判断是否为字符0-9 */
    enIsDigit = ((ucCharacter >= '0') && (ucCharacter <= '9'));

    /* 判断是否为连接符- */
    enIsHyphen = (ucCharacter == '-');

    /* 当前字符是某个LABEL的第一字符或最后一个字符 */
    if((NAS_ESM_APN_VERIFY_CHARACTER_TYPE_BEGIN == enApnVerifyCharacterType) ||
        (NAS_ESM_APN_VERIFY_CHARACTER_TYPE_END == enApnVerifyCharacterType))
    {
        /* 判断是否为字符A-Z或者a-z或者0-9 */
        if((PS_TRUE == enIsUpperAToZ) || (PS_TRUE == enIsLowerAToZ) ||
            (PS_TRUE == enIsDigit))
        {
            return NAS_ESM_SUCCESS;
        }
        else
        {
            return NAS_ESM_FAILURE;
        }
    }

    /* 当前字符是某个LABEL的中间字符 */
    if(NAS_ESM_APN_VERIFY_CHARACTER_TYPE_MIDDLE == enApnVerifyCharacterType)
    {
        /* 判断是否为字符A-Z或者a-z或者0-9或者- */
        if((PS_TRUE == enIsUpperAToZ) || (PS_TRUE == enIsLowerAToZ) ||
            (PS_TRUE == enIsDigit) || (PS_TRUE == enIsHyphen))
        {
            return NAS_ESM_SUCCESS;
        }
        else
        {
            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name   : NAS_ESM_VerifyApnCharacter
 Description     : 验证APN内容中的某一字符
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2009-7-10  Draft Enact
    2.niuxiufan 00181501   2011-12-14 Modify

*****************************************************************************/
VOS_UINT32  NAS_ESM_VerifyApnCharacter
(
    VOS_UINT32 ulCur,
    const VOS_UINT8* pucApnName,
    const VOS_UINT8  ucApnLen
)
{
    /* 判断输入参数是否合法 */
    if((VOS_NULL_PTR == pucApnName) || (ulCur >= ucApnLen))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_VerifyApnCharacter:Error:Input parameter is null!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_VerifyApnCharacter_ENUM, LNAS_ENTRY);
        return NAS_ESM_FAILURE;
    }

    /* 判断当前字符是否为整个APN的开始字符 */
    if(NAS_ESM_NULL == ulCur)
    {
        return NAS_ESM_IsApnCharacterValid(pucApnName[ulCur],
                                           NAS_ESM_APN_VERIFY_CHARACTER_TYPE_BEGIN);
    }

    /* 判断当前字符是否为整个APN的结束字符 */
    if((ucApnLen - 1) == ulCur)
    {
        return NAS_ESM_IsApnCharacterValid(pucApnName[ulCur],
                                           NAS_ESM_APN_VERIFY_CHARACTER_TYPE_END);
    }

    /* 判断当前字符是否为分隔符的前一个字符 */
    if(NAS_ESM_APN_LABEL_INTERVAL_CHARACTER == pucApnName[ulCur + 1])
    {
        return NAS_ESM_IsApnCharacterValid(pucApnName[ulCur],
                                           NAS_ESM_APN_VERIFY_CHARACTER_TYPE_END);
    }

    /* 判断当前字符是否为分隔符的后一个字符 */
    if(NAS_ESM_APN_LABEL_INTERVAL_CHARACTER == pucApnName[ulCur - 1])
    {
        return NAS_ESM_IsApnCharacterValid(pucApnName[ulCur],
                                           NAS_ESM_APN_VERIFY_CHARACTER_TYPE_BEGIN);
    }

    /* 当前字符为中间字符 */
    return NAS_ESM_IsApnCharacterValid(pucApnName[ulCur],
                                           NAS_ESM_APN_VERIFY_CHARACTER_TYPE_MIDDLE);
}
/* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 begin */
/*****************************************************************************
 Function Name   : NAS_ESM_VerifyApnCharacter
 Description     : 判断ApnReverseTransformation入参是否合法
 Input           : None
 Output          : None
 Return          : NAS_ESM_ERROR_CODE_ENUM

 History         :
    1.leixiantiao 00258641      2014-7-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_CheckApnReverseTransformationParaValid
(
    const APP_ESM_APN_INFO_STRU  *pstAPNInfoAfterTrans,
    const NAS_ESM_CONTEXT_APN_STRU  *pstAPNInfoBeforeTrans
)
{
    if((VOS_NULL_PTR == pstAPNInfoBeforeTrans) || (VOS_NULL_PTR == pstAPNInfoAfterTrans)
        || (NAS_ESM_NULL == pstAPNInfoBeforeTrans->ucApnLen)
        || (NAS_ESM_MAX_APN_NUM < pstAPNInfoBeforeTrans->ucApnLen))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckApnReverseTransformationPara:Error:Input parameter is invalid!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckApnReverseTransformationParaValid_ENUM, LNAS_PARAM_INVALID);
        return (VOS_UINT32)PS_FALSE;
    }
    return (VOS_UINT32)PS_TRUE;
}
/* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 end */


/*****************************************************************************
 Function Name   : NAS_ESM_ApnReverseTransformation
 Description     : 反转化APN的存放格式
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2009-7-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_ApnReverseTransformation
(
    APP_ESM_APN_INFO_STRU  *pstAPNInfoAfterTrans,
    const NAS_ESM_CONTEXT_APN_STRU  *pstAPNInfoBeforeTrans
)
{
    VOS_UINT32                          ulPointIndex            = NAS_ESM_NULL;
    VOS_UINT32                          ulTemp                  =  NAS_ESM_NULL;
    PS_BOOL_ENUM_UINT8                  enIsApnLabelLenValid    = PS_FALSE;
    VOS_UINT32                          ulCur                   = NAS_ESM_NULL;
    APP_ESM_APN_INFO_STRU               stTmpApnInfo;

    /* 输入参数合法性判断 */
    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 begin */
    if(PS_FALSE == NAS_ESM_CheckApnReverseTransformationParaValid(pstAPNInfoAfterTrans, pstAPNInfoBeforeTrans))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_APN_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        pstAPNInfoBeforeTrans->ucApnLen);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnReverseTransformation_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_FAILURE;
    }
    /* leixiantiao 00258641 重构代码降低圈复杂度 2014-7-30 end */

    NAS_ESM_MEM_SET_S(  &stTmpApnInfo,
                        sizeof(APP_ESM_APN_INFO_STRU),
                        NAS_ESM_NULL,
                        sizeof(APP_ESM_APN_INFO_STRU));

    /*APN Name为空*/
    if(APP_APN_NULL_APN_LEN == pstAPNInfoBeforeTrans->ucApnLen)
    {
        stTmpApnInfo.ucApnLen = 0;
        return NAS_ESM_SUCCESS;
    }

    /* 转化后长度为转化前长度减1 */
    stTmpApnInfo.ucApnLen = pstAPNInfoBeforeTrans->ucApnLen - 1;

    NAS_ESM_MEM_CPY_S(  stTmpApnInfo.aucApnName,
                        APP_MAX_APN_LEN,
                        (pstAPNInfoBeforeTrans->aucApnName + 1),
                        stTmpApnInfo.ucApnLen);

    /* 判断LABEL的长度是否有效 */
    /* 判断APN第一个长度，若第一个为0，则表明APN为空 */
    NAS_ESM_IsApnLabelLenValid(pstAPNInfoBeforeTrans->aucApnName[0], enIsApnLabelLenValid);
    if(PS_TRUE != enIsApnLabelLenValid)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_APN_IE,
                                        ESM_DECODE_CN_MSG_APN_CHARACTER_INVALID,
                                        0);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnReverseTransformation_ENUM, 1);

        NAS_ESM_MEM_SET_S(  pstAPNInfoAfterTrans,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            0,
                            sizeof(APP_ESM_APN_INFO_STRU));

        return NAS_ESM_FAILURE;
    }
    /* 替换LABEL的长度为分隔字符'.' */
    ulPointIndex = pstAPNInfoBeforeTrans->aucApnName[0];
    /* 检测APN信元值长度，若为空，则中断检测，总长度仅统计0之前的部分; */
    while(ulPointIndex < stTmpApnInfo.ucApnLen)
    {
        /* 判断LABEL的长度是否有效 */
        NAS_ESM_IsApnLabelLenValid(stTmpApnInfo.aucApnName[ulPointIndex], enIsApnLabelLenValid);
        if(PS_TRUE != enIsApnLabelLenValid)
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_APN_IE,
                                            ESM_DECODE_CN_MSG_APN_CHARACTER_INVALID,
                                            ulPointIndex);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnReverseTransformation_ENUM, 2);
            /* return NAS_ESM_FAILURE; */
            stTmpApnInfo.ucApnLen = (unsigned char)ulPointIndex;
            break;

        }

        ulTemp = ulPointIndex;
        ulPointIndex = (ulTemp + stTmpApnInfo.aucApnName[ulTemp]) + 1;
        stTmpApnInfo.aucApnName[ulTemp] = NAS_ESM_APN_LABEL_INTERVAL_CHARACTER;
    }
    /* 判断各LABEL的之和，再加上各分隔符的个数，是否等于总长度 */

    if(ulPointIndex != stTmpApnInfo.ucApnLen)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_APN_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ulPointIndex);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnReverseTransformation_ENUM, 3);
        return NAS_ESM_FAILURE;
    }

    /* 判断每个字符的有效性 */
    for(ulCur = 0; ulCur < stTmpApnInfo.ucApnLen; ulCur++)
    {
        /* 判断当前字符是否为分隔字符 */
        if(NAS_ESM_APN_LABEL_INTERVAL_CHARACTER != stTmpApnInfo.aucApnName[ulCur])
        {
            /* 判断当前字符是否有效 */
            if(NAS_ESM_FAILURE == NAS_ESM_VerifyApnCharacter(ulCur, stTmpApnInfo.aucApnName, stTmpApnInfo.ucApnLen))
            {
                NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_APN_IE,
                                                ESM_DECODE_CN_MSG_APN_CHARACTER_INVALID,
                                                ulCur);
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnReverseTransformation_ENUM, 4);
                return NAS_ESM_FAILURE;
            }
        }
        else
        {
            /* 第一个字符和最后一个字符不允许为分隔字符'.' */
            if((NAS_ESM_NULL == ulCur) || ((stTmpApnInfo.ucApnLen - 1) == ulCur))
            {
                NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_APN_IE,
                                                ESM_DECODE_CN_MSG_APN_CHARACTER_INVALID,
                                                ulCur);
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnReverseTransformation_ENUM, 5);
                return NAS_ESM_FAILURE;
            }
        }
    }

    /* 拷贝转化后的结果到pstAPNInfoAfterTrans */
    NAS_ESM_MEM_CPY_S(  pstAPNInfoAfterTrans,
                        sizeof(APP_ESM_APN_INFO_STRU),
                        &stTmpApnInfo,
                        sizeof(APP_ESM_APN_INFO_STRU));

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_ApnTransformaton
 Description     : 转化APN的存放格式
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2009-7-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_ApnTransformaton
(
    NAS_ESM_CONTEXT_APN_STRU  *pstAPNInfoAfterTrans,
    const APP_ESM_APN_INFO_STRU  *pstAPNInfoBeforeTrans
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    VOS_UINT32                          ulCur               = NAS_ESM_NULL;
    VOS_UINT32                          ulLabelLenPostion   = NAS_ESM_NULL;
    VOS_INT32                           lLastPointIndex     = -1;

    /* 输入参数合法性判断 */
    if(APP_MAX_APN_LEN <  pstAPNInfoBeforeTrans->ucApnLen)
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_APN_IE,
                                        ESM_ENCODE_CN_MSG_IE_LEN_INVALID,
                                        pstAPNInfoBeforeTrans->ucApnLen);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnTransformaton_ENUM, LNAS_PARAM_INVALID);
        return APP_ERR_SM_APN_LEN_ILLEGAL;
    }

    /*APN名字为空*/
    if(NAS_ESM_NULL == pstAPNInfoBeforeTrans->ucApnLen)
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_APN_IE,
                                        ESM_ENCODE_CN_MSG_IE_LEN_INVALID,
                                        pstAPNInfoBeforeTrans->ucApnLen);
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ApnTransformaton_ENUM, 1);
        pstAPNInfoAfterTrans->ucApnLen = 1;
        pstAPNInfoAfterTrans->aucApnName[0] = 0;
        return APP_SUCCESS;
    }

    /* 判断APN第一个字符是否有效 */
    if(NAS_ESM_FAILURE == NAS_ESM_VerifyApnCharacter(NAS_ESM_NULL, pstAPNInfoBeforeTrans->aucApnName, pstAPNInfoBeforeTrans->ucApnLen))
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_APN_IE,
                                        ESM_ENCODE_CN_MSG_APN_CHARACTER_INVALID,
                                        NAS_ESM_NULL);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnTransformaton_ENUM, 2);
        return APP_ERR_SM_APN_SYNTACTICAL_ERROR;
    }

    /* 判断APN最后一个字符是否有效 */
    if(NAS_ESM_FAILURE == NAS_ESM_VerifyApnCharacter((pstAPNInfoBeforeTrans->ucApnLen - 1), pstAPNInfoBeforeTrans->aucApnName, pstAPNInfoBeforeTrans->ucApnLen))
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_APN_IE,
                                        ESM_ENCODE_CN_MSG_APN_CHARACTER_INVALID,
                                        pstAPNInfoBeforeTrans->ucApnLen-1);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnTransformaton_ENUM, 3);
        return APP_ERR_SM_APN_SYNTACTICAL_ERROR;
    }

    pstAPNInfoAfterTrans->ucApnLen = pstAPNInfoBeforeTrans->ucApnLen + 1;

    /* 跳过APN中第一个LABEL的长度存放位置 */
    ulLabelLenPostion = ulSum++;
    for(ulCur = 0; ulCur < pstAPNInfoBeforeTrans->ucApnLen; ulCur++)
    {
        /* 判断当前字符是否为分隔字符 */
        if(NAS_ESM_APN_LABEL_INTERVAL_CHARACTER != pstAPNInfoBeforeTrans->aucApnName[ulCur])
        {
            /* 判断当前字符是否有效 */
            if(NAS_ESM_FAILURE == NAS_ESM_VerifyApnCharacter(ulCur, pstAPNInfoBeforeTrans->aucApnName, pstAPNInfoBeforeTrans->ucApnLen))
            {
                NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_APN_IE,
                                                ESM_ENCODE_CN_MSG_APN_CHARACTER_INVALID,
                                                ulCur);
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_ApnTransformaton_ENUM, 4);
                return APP_ERR_SM_APN_SYNTACTICAL_ERROR;
            }

            /* 存放当前字符 */
            pstAPNInfoAfterTrans->aucApnName[ulSum++] = pstAPNInfoBeforeTrans->aucApnName[ulCur];
        }
        else
        {
            /* 设置APN中当前Label的长度 */
            pstAPNInfoAfterTrans->aucApnName[ulLabelLenPostion] = (VOS_UINT8)(((VOS_INT32)ulCur - lLastPointIndex) -1);
            lLastPointIndex = (VOS_INT)ulCur;
            ulLabelLenPostion = ulSum++;
        }
    }
    /* 设置APN中最后一个Label的长度 */
    pstAPNInfoAfterTrans->aucApnName[ulLabelLenPostion] = (VOS_UINT8)(((VOS_INT32)ulCur - lLastPointIndex) -1);

    return APP_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EncodeAPN()
 Description    : SM模块组装PCO消息函数
 Input          : NAS_ESM_CONTEXT_APN_STRU  *pstAPNInfo
                  VOS_UINT8 *pSendMsg,
                  VOS_UINT32 *ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.聂州渝 00108792      2008-09-22  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_EncodeAPN( const APP_ESM_APN_INFO_STRU*pstAPNInfo,
                                      VOS_UINT8  *pSendMsg,
                                      VOS_UINT32 *pulLength,
                                      NAS_MSG_FORMAT_ENUM_UINT8  enEncodeTp)
{
    VOS_UINT8       *pTmpSendMsg = pSendMsg;
    VOS_UINT32       ulSum       = *pulLength;
    VOS_UINT32       i           = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_APN_STRU     stTmpApnInfo  = {NAS_ESM_NULL};
    VOS_UINT32                   ulRslt = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeAPN:INFO:NAS_ESM_EncodeAPN been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeAPN_ENUM, LNAS_ENTRY);


    ulRslt = NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                         pstAPNInfo);
    if(NAS_ESM_SUCCESS != ulRslt)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_EncodeAPN:ERROR: APN transformation fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_EncodeAPN_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    if( VOS_NULL_PTR == pTmpSendMsg)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeAPN:ERROR: No SmMsg!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeAPN_ENUM, 2);
        return NAS_ESM_FAILURE;
    }

    if(NAS_MSG_FORMAT_TLV == enEncodeTp)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_MSG_APN_IEI;
    }

    if((NAS_ESM_NULL == stTmpApnInfo.ucApnLen)
        ||(stTmpApnInfo.ucApnLen > NAS_ESM_MAX_APN_NUM))
    {
        NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_APN_IE,
                                        ESM_ENCODE_CN_MSG_IE_LEN_INVALID,
                                        stTmpApnInfo.ucApnLen);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeAPN_ENUM, 3);
        return NAS_ESM_FAILURE;
    }

    pTmpSendMsg[ulSum++] = stTmpApnInfo.ucApnLen;

    for(i = 0; i < stTmpApnInfo.ucApnLen; i++)
    {
        pTmpSendMsg[ulSum++] = stTmpApnInfo.aucApnName[i];
    }

    *pulLength = ulSum;

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EpsQosRateTranTo32
 Description     : 将QoS速率从32位格式变为16位格式
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-4-23  Draft Enact
    2.wangchen 00209181     2014-09-01 Modify:R11
*****************************************************************************/
VOS_UINT32 NAS_ESM_EpsQosRate1To256EncodeTo32
(
    VOS_UINT32                          ulRate32,
    VOS_UINT32                         *pusRate32
)
{
    VOS_UINT32                          ulRateTmp = NAS_ESM_NULL;

    /*  ulRate32取值1-63kb，pusRate16低8位: 取值位于00000001 - 00111111 */
    if (ulRate32 < NAS_ESM_QOS_RATE_64KB)
    {
        *pusRate32 = (VOS_UINT32)(VOS_UINT8)ulRate32;
        return NAS_ESM_SUCCESS;
    }

    /* ulRate32取值64-568kb，pusRate16低8位: 取值位于01000000 - 01111111 */
    if (ulRate32 <= NAS_ESM_QOS_RATE_568KB)
    {

        ulRateTmp = (VOS_UINT32)((ulRate32 - NAS_ESM_QOS_RATE_64KB)
                                        / NAS_ESM_QOS_RATE_GRANULARITY_8KB);
        ulRateTmp += (1 << NAS_ESM_MOVEMENT_6_BITS);
        *pusRate32 = (VOS_UINT32)(VOS_UINT8)ulRateTmp;
        return NAS_ESM_SUCCESS;
    }

    /* ulRate32取值569-575kb, pusRate16低8位:0x7F */
    if (ulRate32 < NAS_ESM_QOS_RATE_576KB)
    {
        *pusRate32 = NAS_ESM_QOS_RATE_RANGE_568KB_GRANULARITY_8KB;
        return NAS_ESM_SUCCESS;
    }

    /* ulRate32取值576-8640kb, pusRate16低8位: 取值位于10000000 - 11111110 */
    if (ulRate32 <= NAS_ESM_QOS_RATE_8640KB)
    {
        ulRateTmp = (VOS_UINT32)((ulRate32 - NAS_ESM_QOS_RATE_576KB)
                                        / NAS_ESM_QOS_RATE_GRANULARITY_64KB);
        ulRateTmp += (1 << NAS_ESM_MOVEMENT_7_BITS);
        *pusRate32 = (VOS_UINT32)(VOS_UINT8)ulRateTmp;
        return NAS_ESM_SUCCESS;
    }

    /* ulRate32取值8641-8699kb, pusRate16低8位:0xFE */
    if (ulRate32 < NAS_ESM_QOS_RATE_8700KB)
    {
        *pusRate32 = NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
        return NAS_ESM_SUCCESS;
    }

    /* ulRate32取值8700-16000kb, pusRate16高8位: 取值位于00000001 - 01001010 */
    if (ulRate32 <= NAS_ESM_QOS_RATE_16000KB)
    {
        ulRateTmp = (VOS_UINT32)((ulRate32 - NAS_ESM_QOS_RATE_8600KB)
                                        / NAS_ESM_QOS_RATE_GRANULARITY_100KB);
        *pusRate32 = (((VOS_UINT32)(VOS_UINT8)ulRateTmp) << NAS_ESM_MOVEMENT_8_BITS)
                      | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
        return NAS_ESM_SUCCESS;
    }

    /* ulRate32取值160001-17407kb, pusRate16高8位:0xFE */
    if (ulRate32 < NAS_ESM_QOS_RATE_17MB)
    {
        *pusRate32 = NAS_ESM_QOS_RATE_RANGE_16000KB_GRANULARITY_64KB;
        *pusRate32 = ((VOS_UINT32)(*pusRate32 << NAS_ESM_MOVEMENT_8_BITS))
                      | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
        return NAS_ESM_SUCCESS;
    }

    /* ulRate32取值17-128Mb, pusRate16高8位: 取值位于01001011 - 10111010 */
    if (ulRate32 <= NAS_ESM_QOS_RATE_128MB)
    {
        ulRateTmp = (VOS_UINT32)((ulRate32 - NAS_ESM_QOS_RATE_16MB)
                                    / NAS_ESM_QOS_RATE_GRANULARITY_1MB) + NAS_ESM_QOS_RATE_RANGE_16000KB_GRANULARITY_64KB;
        *pusRate32 = (((VOS_UINT32)(VOS_UINT8)ulRateTmp) << NAS_ESM_MOVEMENT_8_BITS)
                      | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
        return NAS_ESM_SUCCESS;
    }

    /* ulRate32取值128-130Mb, pusRate16高8位:0xFE */
    if (ulRate32 < NAS_ESM_QOS_RATE_130MB)
    {
        *pusRate32 = NAS_ESM_QOS_RATE_RANGE_128MB_GRANULARITY_1MB;
        *pusRate32 = ((VOS_UINT32)(*pusRate32 << NAS_ESM_MOVEMENT_8_BITS))
                     | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
        return NAS_ESM_SUCCESS;
    }

    /* ulRate32取值130-256Mb, pusRate16高8位: 取值位于10111011 - 11111010 */
    if (ulRate32 <= NAS_ESM_QOS_RATE_256MB)
    {
        ulRateTmp = (VOS_UINT32)((ulRate32 - NAS_ESM_QOS_RATE_128MB)
                                    / NAS_ESM_QOS_RATE_GRANULARITY_2MB) + NAS_ESM_QOS_RATE_RANGE_128MB_GRANULARITY_1MB;
        *pusRate32 = (((VOS_UINT32)(VOS_UINT8)ulRateTmp) << NAS_ESM_MOVEMENT_8_BITS)
                     | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;;
        return NAS_ESM_SUCCESS;
    }
    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EpsQosRateTranTo32
 Description     : 将QoS速率从32位格式变为16位格式
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-4-23  Draft Enact
    2.wangchen 00209181     2014-09-01 Modify:R11
*****************************************************************************/
VOS_VOID NAS_ESM_EpsQosRateEncodeTo32
(
    VOS_UINT32                          ulRate32,
    VOS_UINT32                         *pusRate32
)
{
    *pusRate32 = NAS_ESM_NULL;

    if ((NAS_ESM_NULL == ulRate32))
    {
        return;
    }

    if (NAS_ESM_SUCCESS == NAS_ESM_EpsQosRate1To256EncodeTo32(ulRate32,pusRate32))
    {
        return;
    }

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        /* ulRate32取值256-260Mb, pusRate16高8位:0xFE */
        if (ulRate32 < NAS_ESM_QOS_RATE_260MB)
        {
            *pusRate32 = NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB;
            *pusRate32 = ((VOS_UINT32)(*pusRate32 << NAS_ESM_MOVEMENT_8_BITS))
                         | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
            return;
        }

        /* ulRate32取值260-500Mb, pusRate32 16~23位:取值位于00000001 - 00111101 */
        if (ulRate32 <= NAS_ESM_QOS_RATE_500MB)
        {
            *pusRate32 = (VOS_UINT32)((ulRate32 - NAS_ESM_QOS_RATE_256MB)
                                        / NAS_ESM_QOS_RATE_GRANULARITY_4MB);
            *pusRate32 = ((VOS_UINT32)(*pusRate32 << NAS_ESM_MOVEMENT_16_BITS))
                         | (NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB << NAS_ESM_MOVEMENT_8_BITS)
                         | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
            return;
        }

        /* ulRate32取值500-510 Mb, pusRate32 16~23位:0x3D */
        if (ulRate32 < NAS_ESM_QOS_RATE_510MB)
        {
            *pusRate32 = NAS_ESM_QOS_RATE_RANGE_500MB_GRANULARITY_4MB;
            *pusRate32 = ((VOS_UINT32)(*pusRate32 << NAS_ESM_MOVEMENT_16_BITS))
                         | (NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB << NAS_ESM_MOVEMENT_8_BITS)
                         | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
            return;
        }

        /* ulRate32取值510-1500Mb, pusRate32 16~23位:取值位于00111110 - 10100001 */
        if (ulRate32 <= NAS_ESM_QOS_RATE_1500MB)
        {
            *pusRate32 = (VOS_UINT32)((ulRate32 - NAS_ESM_QOS_RATE_500MB)
                                        / NAS_ESM_QOS_RATE_GRANULARITY_10MB) + NAS_ESM_QOS_RATE_RANGE_500MB_GRANULARITY_4MB;
            *pusRate32 = ((VOS_UINT32)(*pusRate32 << NAS_ESM_MOVEMENT_16_BITS))
                         | (NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB << NAS_ESM_MOVEMENT_8_BITS)
                         | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
            return;
        }

        /* ulRate32取值1500-1600 Mb, pusRate32 16~23位:0x3D */
        if (ulRate32 < NAS_ESM_QOS_RATE_1600MB)
        {
            *pusRate32 = NAS_ESM_QOS_RATE_RANGE_1500MB_GRANULARITY_10MB;
            *pusRate32 = ((VOS_UINT32)(*pusRate32 << NAS_ESM_MOVEMENT_16_BITS))
                         | (NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB << NAS_ESM_MOVEMENT_8_BITS)
                         | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
            return;
        }

        /* ulRate32取值1600Mb- 10GB, pusRate32 16~23位:取值位于10100010 - 11110110 */
        if (ulRate32 <= NAS_ESM_QOS_RATE_10GB)
        {
            *pusRate32 = (VOS_UINT32)((ulRate32 - NAS_ESM_QOS_RATE_1500MB)
                                        / NAS_ESM_QOS_RATE_GRANULARITY_100MB) + NAS_ESM_QOS_RATE_RANGE_1500MB_GRANULARITY_10MB;
            *pusRate32 = ((VOS_UINT32)(*pusRate32 << NAS_ESM_MOVEMENT_16_BITS))
                         | (NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB << NAS_ESM_MOVEMENT_8_BITS)
                         | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
            return;
        }

        /* ulRate32取值大于10Gb, pusRate32 16~23位: 0xF6 */
        *pusRate32 = NAS_ESM_QOS_RATE_RANGE_10GB_GRANULARITY_100MB;
        *pusRate32 = ((VOS_UINT32)(*pusRate32 << NAS_ESM_MOVEMENT_16_BITS))
                     | (NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB<< NAS_ESM_MOVEMENT_8_BITS);
        *pusRate32 = ((VOS_UINT32)(*pusRate32))
                     | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
    }
    else
    {
        /* ulRate32取值大于256Mb, pusRate16高8位: 0xFA */
        *pusRate32 = NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB;
        *pusRate32 = ((VOS_UINT16)(*pusRate32 << NAS_ESM_MOVEMENT_8_BITS))
                     | NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB;
    }
}
/*****************************************************************************
 Function Name  : NAS_ESM_EncodeEpsQos
 Description    : SM模块组装PCO消息函数
 Input          : VOS_UINT8 *pSendMsg,
                  VOS_UINT32 ulLength
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.聂州渝 00108792      2008-09-22  Draft Enact
      2.wangchen 00209181   2014-09-02   Modify:R11
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
VOS_UINT32 NAS_ESM_EncodeEpsQos
(
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstEpsQosInfo,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength,
    NAS_MSG_FORMAT_ENUM_UINT8           enEncodeTp
)
{
    VOS_UINT32                          ulSum               = *pulLength;
    VOS_UINT32                          ulTmpSum            = NAS_ESM_NULL;
    VOS_UINT32                          ulLength            = NAS_ESM_NULL;
    VOS_UINT32                          ulULMaxRateTmp      = NAS_ESM_NULL;
    VOS_UINT32                          ulDLMaxRateTmp      = NAS_ESM_NULL;
    VOS_UINT32                          ulULGMaxRateTmp     = NAS_ESM_NULL;
    VOS_UINT32                          ulDLGMaxRateTmp     = NAS_ESM_NULL;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    APP_ESM_EPS_QOS_INFO_STRU          *pstTmpEpsQosInfo    = VOS_NULL_PTR;
    VOS_UINT8                           ucHigh8BitValue     = 0;
    VOS_UINT8                           ucHigh16BitValue    = 0;
    VOS_UINT32                          ulTempAllValue      = 0;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeEpsQos:INFO:NAS_ESM_EncodeEpsQos been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEpsQos_ENUM, LNAS_ENTRY);

    if((VOS_NULL_PTR == pTmpSendMsg) || (VOS_NULL_PTR == pstEpsQosInfo))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeEpsQos:ERROR: No SmMsg or No Qos Info!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEpsQos_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    pstTmpEpsQosInfo = &pstEpsQosInfo->stQosInfo;

    /*  编码前对QOS进行合法性检测 */
    if (NAS_ESM_FAILURE == NAS_ESM_IsSdfQosValid(pstTmpEpsQosInfo))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeEpsQos:ERROR: Check qos failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEpsQos_ENUM, 2);
        return NAS_ESM_FAILURE;
    }
    if(NAS_MSG_FORMAT_TLV == enEncodeTp)
    {
        /*可选参数,存放EPS_QOS信息IEI参数*/
        pTmpSendMsg[ulSum++] = NAS_ESM_MSG_EPS_QOS_IEI;
    }

    /*记录SDF QOS长度位索引*/
    ulTmpSum = ulSum++;

    pTmpSendMsg[ulSum++] = pstEpsQosInfo->ucNwQCI;

    if (PS_TRUE == NAS_ESM_IsGbrBearer(pstTmpEpsQosInfo->ucQCI))
    {
        /* 转化ULMaxRate */
        NAS_ESM_EpsQosRateEncodeTo32(pstTmpEpsQosInfo->ulULMaxRate, &ulULMaxRateTmp);

        /* 转化DLMaxRate */
        NAS_ESM_EpsQosRateEncodeTo32(pstTmpEpsQosInfo->ulDLMaxRate, &ulDLMaxRateTmp);

        /* 转化ULGMaxRate */
        NAS_ESM_EpsQosRateEncodeTo32(pstTmpEpsQosInfo->ulULGMaxRate, &ulULGMaxRateTmp);

        /* 转化DLGMaxRate */
        NAS_ESM_EpsQosRateEncodeTo32(pstTmpEpsQosInfo->ulDLGMaxRate, &ulDLGMaxRateTmp);

        ulTempAllValue = (ulULMaxRateTmp | ulDLMaxRateTmp | ulULGMaxRateTmp | ulULGMaxRateTmp);

        ucHigh8BitValue = (VOS_UINT8)((ulTempAllValue & NAS_ESM_HIGH_BYTE) \
                                        >> NAS_ESM_MOVEMENT_8_BITS);
        ucHigh16BitValue = (VOS_UINT8)((ulTempAllValue & NAS_ESM_THIRD_BYTE) \
                                >> NAS_ESM_MOVEMENT_16_BITS);

        pTmpSendMsg[ulSum++] = (VOS_UINT8)(ulULMaxRateTmp & NAS_ESM_LOW_BYTE);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(ulDLMaxRateTmp & NAS_ESM_LOW_BYTE);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(ulULGMaxRateTmp & NAS_ESM_LOW_BYTE);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(ulDLGMaxRateTmp & NAS_ESM_LOW_BYTE);

        /*如果某个EPS QOS速率等于或高于8700kbps，则需要填充扩展位4字节*/
        if(ucHigh8BitValue)
        {
            pTmpSendMsg[ulSum++] = (VOS_UINT8)((ulULMaxRateTmp & NAS_ESM_HIGH_BYTE)  \
                                                        >> NAS_ESM_MOVEMENT_8_BITS);
            pTmpSendMsg[ulSum++] = (VOS_UINT8)((ulDLMaxRateTmp & NAS_ESM_HIGH_BYTE)  \
                                                        >> NAS_ESM_MOVEMENT_8_BITS);
            pTmpSendMsg[ulSum++] = (VOS_UINT8)((ulULGMaxRateTmp & NAS_ESM_HIGH_BYTE)  \
                                                        >> NAS_ESM_MOVEMENT_8_BITS);
            pTmpSendMsg[ulSum++] = (VOS_UINT8)((ulDLGMaxRateTmp & NAS_ESM_HIGH_BYTE)  \
                                                        >> NAS_ESM_MOVEMENT_8_BITS);

             /*如果某个EPS QOS速率等于或高于260mbps，则需要填充扩展位4字节*/
            if(ucHigh16BitValue)
            {
                pTmpSendMsg[ulSum++] = (VOS_UINT8)(( ulULMaxRateTmp& NAS_ESM_THIRD_BYTE)  \
                                                                        >> NAS_ESM_MOVEMENT_16_BITS);
                pTmpSendMsg[ulSum++] = (VOS_UINT8)(( ulDLMaxRateTmp& NAS_ESM_THIRD_BYTE)  \
                                                                        >> NAS_ESM_MOVEMENT_16_BITS);
                pTmpSendMsg[ulSum++] = (VOS_UINT8)(( ulULGMaxRateTmp& NAS_ESM_THIRD_BYTE)  \
                                                                        >> NAS_ESM_MOVEMENT_16_BITS);
                pTmpSendMsg[ulSum++] = (VOS_UINT8)(( ulDLGMaxRateTmp& NAS_ESM_THIRD_BYTE)  \
                                                                        >> NAS_ESM_MOVEMENT_16_BITS);
            }
        }
    }

    ulLength = ulSum - (ulTmpSum + 1);

    pTmpSendMsg[ulTmpSum] = (VOS_UINT8)ulLength;

    *pulLength = ulSum;

    return NAS_ESM_SUCCESS;
}

#else
VOS_UINT32 NAS_ESM_EncodeEpsQos
(
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstEpsQosInfo,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength,
    NAS_MSG_FORMAT_ENUM_UINT8           enEncodeTp
)
{
    VOS_UINT32                          ulSum               = *pulLength;
    VOS_UINT32                          ulTmpSum            = NAS_ESM_NULL;
    VOS_UINT32                          ulLength            = NAS_ESM_NULL;
    VOS_UINT32                          ulULMaxRateTmp      = NAS_ESM_NULL;
    VOS_UINT32                          ulDLMaxRateTmp      = NAS_ESM_NULL;
    VOS_UINT32                          ulULGMaxRateTmp     = NAS_ESM_NULL;
    VOS_UINT32                          ulDLGMaxRateTmp     = NAS_ESM_NULL;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    APP_ESM_EPS_QOS_INFO_STRU          *pstTmpEpsQosInfo    = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeEpsQos:INFO:NAS_ESM_EncodeEpsQos been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeEpsQos_ENUM, LNAS_ENTRY);

    if((VOS_NULL_PTR == pTmpSendMsg) || (VOS_NULL_PTR == pstEpsQosInfo))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeEpsQos:ERROR: No SmMsg or No Qos Info!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEpsQos_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    pstTmpEpsQosInfo = &pstEpsQosInfo->stQosInfo;

    /*  编码前对QOS进行合法性检测 */
    if (NAS_ESM_FAILURE == NAS_ESM_IsSdfQosValid(pstTmpEpsQosInfo))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeEpsQos:ERROR: Check qos failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeEpsQos_ENUM, 2);
        return NAS_ESM_FAILURE;
    }
    if(NAS_MSG_FORMAT_TLV == enEncodeTp)
    {
        /*可选参数,存放EPS_QOS信息IEI参数*/
        pTmpSendMsg[ulSum++] = NAS_ESM_MSG_EPS_QOS_IEI;
    }

    /*记录SDF QOS长度位索引*/
    ulTmpSum = ulSum++;

    pTmpSendMsg[ulSum++] = pstEpsQosInfo->ucNwQCI;

    if (PS_TRUE == NAS_ESM_IsGbrBearer(pstTmpEpsQosInfo->ucQCI))
    {
        /* 转化ULMaxRate */
        NAS_ESM_EpsQosRateEncodeTo32(pstTmpEpsQosInfo->ulULMaxRate, &ulULMaxRateTmp);

        /* 转化DLMaxRate */
        NAS_ESM_EpsQosRateEncodeTo32(pstTmpEpsQosInfo->ulDLMaxRate, &ulDLMaxRateTmp);

        /* 转化ULGMaxRate */
        NAS_ESM_EpsQosRateEncodeTo32(pstTmpEpsQosInfo->ulULGMaxRate, &ulULGMaxRateTmp);

        /* 转化DLGMaxRate */
        NAS_ESM_EpsQosRateEncodeTo32(pstTmpEpsQosInfo->ulDLGMaxRate, &ulDLGMaxRateTmp);

        pTmpSendMsg[ulSum++] = (VOS_UINT8)(ulULMaxRateTmp & NAS_ESM_LOW_BYTE);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(ulDLMaxRateTmp & NAS_ESM_LOW_BYTE);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(ulULGMaxRateTmp & NAS_ESM_LOW_BYTE);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(ulDLGMaxRateTmp & NAS_ESM_LOW_BYTE);

        pTmpSendMsg[ulSum++] = (VOS_UINT8)((ulULMaxRateTmp & NAS_ESM_HIGH_BYTE)  \
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((ulDLMaxRateTmp & NAS_ESM_HIGH_BYTE)  \
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((ulULGMaxRateTmp & NAS_ESM_HIGH_BYTE)  \
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((ulDLGMaxRateTmp & NAS_ESM_HIGH_BYTE)  \
                                                    >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(( ulULMaxRateTmp& NAS_ESM_THIRD_BYTE)  \
                                                                >> NAS_ESM_MOVEMENT_16_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(( ulDLMaxRateTmp& NAS_ESM_THIRD_BYTE)  \
                                                                >> NAS_ESM_MOVEMENT_16_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(( ulULGMaxRateTmp& NAS_ESM_THIRD_BYTE)  \
                                                                >> NAS_ESM_MOVEMENT_16_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(( ulDLGMaxRateTmp& NAS_ESM_THIRD_BYTE)  \
                                                                >> NAS_ESM_MOVEMENT_16_BITS);
    }


    ulLength = ulSum - (ulTmpSum + 1);

    pTmpSendMsg[ulTmpSum] = (VOS_UINT8)ulLength;

    *pulLength = ulSum;

    return NAS_ESM_SUCCESS;
}
#endif

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeTftNoOperation
 Description     : 编码修改SDF的QOS消息中TFT部分
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-05-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_EncodeTftNoOperation
(
    const VOS_UINT8                    *pucNwPfId,
    VOS_UINT32                          ulPFNum,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT8       *pTmpSendMsg = pSendMsg;
    VOS_UINT32       ulSum       = *pulLength;
    VOS_UINT32       ulTmpSum    = NAS_ESM_NULL;
    VOS_UINT32       ulCnt       = NAS_ESM_NULL;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeTftNoOperation:INFO:NAS_ESM_EncodeTftNoOperation been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeTftNoOperation_ENUM, LNAS_ENTRY);

    ulTmpSum = ulSum++;

    /*保存TFT第3字节的内容，按创建一个新filter保存*/
    pTmpSendMsg[ulSum++] = NAS_ESM_TFT_NO_OPERATION;

    /* 设置一个Parameter */
    pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PARA_LIST_ID;

    pTmpSendMsg[ulSum++] = ( VOS_UINT8 )ulPFNum;

    for ( ulCnt=0; ulCnt < ulPFNum; ulCnt++ )
    {
        pTmpSendMsg[ulSum++] = pucNwPfId[ulCnt];
    }

    /*记录TFT消息内容的长度,为进入TFT下一个信息单元，ulSum多+了1*/
    pTmpSendMsg[ulTmpSum] = (VOS_UINT8)(ulSum - (ulTmpSum + 1));

    *pulLength = ulSum;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeOneFilterContent
 Description     : 编码一个packet filter内容
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-4-21  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_EncodeOneFilterContent
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT8       *pTmpSendMsg = pSendMsg;
    VOS_UINT32       ulSum       = *pulLength;
    VOS_UINT32       ulIndex     = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_TFT_STRU    *pstTmpTFTInfo = pstTFTInfo;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeOneFilterContent:INFO:NAS_ESM_EncodeOneFilterContent been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeOneFilterContent_ENUM, LNAS_ENTRY);

    /*目前只做一个filter,用于演示*/
    /* OCTET4 Packet filter identifier 1 */

    pTmpSendMsg[ulSum++] = pstTmpTFTInfo->ucNwPacketFilterId
                          |((pstTmpTFTInfo->enDirection & NAS_ESM_LOW_2_BIT_MASK)
                         << NAS_ESM_MOVEMENT_4_BITS);

    /* OCTET5 ,Packet filter evaluation precedence 1 */
    pTmpSendMsg[ulSum++] = pstTmpTFTInfo->ucPrecedence;
    /* 跳过Length of Pactket fileter contents1*/
    ulIndex = ulSum++;

    if(NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpRmtIpv4AddrAndMask)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_IPV4_ADDR;
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv4Address[0];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv4Address[1];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv4Address[2];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv4Address[3];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv4Mask[0];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv4Mask[1];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv4Mask[2];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv4Mask[3];
    }

    if (NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpRmtIpv6AddrAndMask)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_IPV6_ADDR;
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[0];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[1];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[2];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[3];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[4];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[5];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[6];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[7];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[8];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[9];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[10];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[11];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[12];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[13];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[14];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Address[15];

        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[0];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[1];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[2];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[3];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[4];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[5];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[6];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[7];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[8];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[9];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[10];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[11];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[12];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[13];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[14];
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucRmtIpv6Mask[15];
    }
    if(NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpProtocolId)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_PROTOCOL_ID;
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->ucProtocolId;
    }

    if(NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpSingleLocalPort)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_SINGLE_LOCAL_PORT;
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->usSingleLcPort & NAS_ESM_HIGH_BYTE)
                                      >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(pstTmpTFTInfo->usSingleLcPort & NAS_ESM_LOW_BYTE);
    }

    if(NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpLocalPortRange)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_LOCAL_PORT_RANGE;
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->usLcPortLowLimit & NAS_ESM_HIGH_BYTE)
                                      >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(pstTmpTFTInfo->usLcPortLowLimit & NAS_ESM_LOW_BYTE);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->usLcPortHighLimit & NAS_ESM_HIGH_BYTE)
                                      >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(pstTmpTFTInfo->usLcPortHighLimit & NAS_ESM_LOW_BYTE);
    }

    if(NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpSingleRemotePort)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_SINGLE_REMOTE_PORT;
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->usSingleRmtPort & NAS_ESM_HIGH_BYTE)
                                      >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(pstTmpTFTInfo->usSingleRmtPort & NAS_ESM_LOW_BYTE);
    }

    if(NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpRemotePortRange)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_REMOTE_PORT_RANGE;
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->usRmtPortLowLimit & NAS_ESM_HIGH_BYTE)
                                      >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(pstTmpTFTInfo->usRmtPortLowLimit & NAS_ESM_LOW_BYTE);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->usRmtPortHighLimit & NAS_ESM_HIGH_BYTE)
                                      >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(pstTmpTFTInfo->usRmtPortHighLimit & NAS_ESM_LOW_BYTE);
    }

    if(NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpSecuParaIndex)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_SPI;
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->ulSecuParaIndex & NAS_ESM_FOURTH_BYTE)
                                      >> NAS_ESM_MOVEMENT_24_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->ulSecuParaIndex & NAS_ESM_THIRD_BYTE)
                                      >> NAS_ESM_MOVEMENT_16_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->ulSecuParaIndex & NAS_ESM_HIGH_BYTE)
                                      >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(pstTmpTFTInfo->ulSecuParaIndex & NAS_ESM_LOW_BYTE);
    }

    if(NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpTypeOfService)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_TOS;
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->ucTypeOfService;
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->ucTypeOfServiceMask;
    }

    if(NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpFlowLabelType)
    {
        pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_FLOW_LABLE;
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(((pstTmpTFTInfo->ulFlowLabelType & NAS_ESM_THIRD_BYTE)
                                      >> NAS_ESM_MOVEMENT_16_BITS) & NAS_ESM_MSG_LOW_BIT);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)((pstTmpTFTInfo->ulFlowLabelType & NAS_ESM_HIGH_BYTE)
                                      >> NAS_ESM_MOVEMENT_8_BITS);
        pTmpSendMsg[ulSum++] = (VOS_UINT8)(pstTmpTFTInfo->ulFlowLabelType & NAS_ESM_LOW_BYTE);
    }


    if ((ERABM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
        && (NAS_ESM_FUN_CTRL_ON == NAS_ESM_GetLocalIpSupFlag()))
    {
        if (NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpLocalIpv4AddrAndMask)
        {
            pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_IPV4_LOCAL_ADDR;
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv4Addr[0];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv4Addr[1];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv4Addr[2];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv4Addr[3];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv4Mask[0];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv4Mask[1];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv4Mask[2];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv4Mask[3];
        }

        if (NAS_ESM_OP_TRUE == pstTmpTFTInfo->bitOpLocalIpv6AddrAndMask)
        {
            pTmpSendMsg[ulSum++] = NAS_ESM_TFT_PF_COP_TYPE_IPV6_LOCAL_ADDR;
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[0];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[1];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[2];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[3];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[4];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[5];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[6];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[7];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[8];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[9];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[10];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[11];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[12];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[13];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[14];
            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->aucLocalIpv6Addr[15];

            pTmpSendMsg[ulSum++] = pstTmpTFTInfo->ucLocalIpv6Prefix;
        }
    }

    /*记录tft packet filter contents长度*/
    pTmpSendMsg[ulIndex] = (VOS_UINT8)(ulSum - (ulIndex + 1));

    *pulLength = ulSum;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeTftDeletePf
 Description     : SM组装修改TFT消息函数
 Input           : VOS_UINT8 *pSendMsg,
                   VOS_UINT32 ulLength
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yangqianhui 00135146      2009-2-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_EncodeTftDeletePf
(
    NAS_ESM_CONTEXT_TFT_STRU            *pstTFTInfo,
    VOS_UINT32                           ulPFNum,
    VOS_UINT8                           *pSendMsg,
    VOS_UINT32                          *pulLength
)
{
    VOS_UINT8                           *pTmpSendMsg   = pSendMsg;
    VOS_UINT32                           ulSum         = *pulLength;
    VOS_UINT32                           ulTmpSum      = NAS_ESM_NULL;
    VOS_UINT32                           ulCnt         = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_TFT_STRU            *pstTmpTFTInfo = pstTFTInfo;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeTftDeletePf:INFO:NAS_ESM_EncodeDeleteFilterTTF been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeTftDeletePf_ENUM, LNAS_ENTRY);

    ulTmpSum = ulSum++;

    /*保存TFT第3字节的内容，按创建一个新filter保存*/
    pTmpSendMsg[ulSum++] =(NAS_ESM_TFT_DELETE_FILTER
                          |((VOS_UINT8)ulPFNum
                             & NAS_ESM_TFT_LOW_4_BIT_MASK));

    /*目前只做一个filter,用于演示*/
    /* OCTET4 Packet filter identifier 1 */
    for (ulCnt = NAS_ESM_NULL; ulCnt < ulPFNum; ulCnt++)
    {
        pTmpSendMsg[ulSum++] = pstTmpTFTInfo->ucNwPacketFilterId;
        pstTmpTFTInfo++;
    }

    /*记录TFT消息内容的长度,为进入TFT下一个信息单元，ulSum多+了1*/
    pTmpSendMsg[ulTmpSum] = (VOS_UINT8)(ulSum - (ulTmpSum + 1));

    *pulLength = ulSum;
}

/*****************************************************************************
 Function Name  : NAS_ESM_IsSdfQueryNwPfIdSuc()
 Description    : 查询Sdf的packetfilter id 是否都有对应的网络packetfilter id
 Input          : pstResModEncodeInfo -- 查询需要的相关参数的集合

 Output         : None
 Return Value   : NAS_ESM_SUCCESS     -- 所有的packetfilterID都找到了对应的网络packetfilterID
                  NAS_ESM_FAILURE     -- 不是所有的packetfilterID都找到了对应的网络packetfilterID
 History        :
      1.liuwenyuy 00143951      2009-11-10  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_IsSdfQueryNwPfIdSucc
(
    const NAS_ESM_RES_MOD_ENCODE_INFO_STRU    *pstResModEncodeInfo
)
{

    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt              = NAS_ESM_FAILURE;
    VOS_UINT8                           ucNwPacketFilterId  = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;


    pstSdfPara = NAS_ESM_GetSdfParaAddr(pstResModEncodeInfo->ulCid);

    for (ulCnt = NAS_ESM_NULL; ulCnt < pstSdfPara->ulPfNum; ulCnt++)
    {
        ulRslt = NAS_ESM_QueryNWPacketFilterID( pstSdfPara->astCntxtTftInfo[ulCnt].ucPacketFilterId,
                                                pstResModEncodeInfo->ulCid,
                                                &ucNwPacketFilterId);

        if (NAS_ESM_FAILURE == ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_IsSdfQueryNwPfIdSuc:WARNING:NAS->ESM no network TFT matched!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_IsSdfQueryNwPfIdSucc_ENUM, 1);

            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_EncodeTftCreateTftOrReplacePf
 Description     : 编码TFT信息,TAD码为CREATE_TFT或者REPLACE_FILTER
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-3-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_EncodeTftCreateTftOrReplacePf
(
    VOS_UINT8                           ucTadType,
    VOS_UINT32                          ulCid,
    VOS_UINT8                          *pSendMsg,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpSum            = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_TFT_STRU            stTFTInfo;
    VOS_UINT8                          *pTmpSendMsg         = pSendMsg;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EncodeTftCreateTftOrReplacePf:INFO:NAS_ESM_EncodeTftCreateTftOrReplacePf been entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EncodeTftCreateTftOrReplacePf_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(  &stTFTInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU));

    if( VOS_NULL_PTR == pTmpSendMsg)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EncodeTftCreateTftOrReplacePf:ERROR: No SmMsg!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeTftCreateTftOrReplacePf_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /* 记录存储TFT长度的位置 */
    ulTmpSum = ulSum++;

    if (ucTadType == NAS_ESM_TFT_CREATE_TFT)
    {
        /*保存TFT第3字节的内容，按创建多个新filter保存*/
        pTmpSendMsg[ulSum++] =(NAS_ESM_TFT_CREATE_TFT
                               |((VOS_UINT8)pstSdfPara->ulPfNum
                                  & NAS_ESM_TFT_LOW_4_BIT_MASK));
    }
    else
    {
        /*保存TFT第3字节的内容，按创建多个新filter保存*/
        pTmpSendMsg[ulSum++] =(NAS_ESM_TFT_REPLACE_FILTER
                               |((VOS_UINT8)pstSdfPara->ulPfNum
                                  & NAS_ESM_TFT_LOW_4_BIT_MASK));
    }

    /* add 1,the  byte length of TFT operation code locate in */
    pTmpSendMsg[ulTmpSum]++;

    for (ulCnt = NAS_ESM_NULL; ulCnt < pstSdfPara->ulPfNum; ulCnt++)
    {
        NAS_ESM_MEM_CPY_S(  &stTFTInfo,
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU),
                            &pstSdfPara->astCntxtTftInfo[ulCnt],
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU));

        if (ucTadType == NAS_ESM_TFT_CREATE_TFT)
        {
            stTFTInfo.ucNwPacketFilterId = NAS_ESM_NULL;
        }
        else
        {
            (VOS_VOID)NAS_ESM_QueryNWPacketFilterID(stTFTInfo.ucPacketFilterId,
                                                    ulCid,
                                                    &stTFTInfo.ucNwPacketFilterId);
        }

        NAS_ESM_EncodeOneFilterContent(&stTFTInfo,
                                        pTmpSendMsg + ulSum,
                                        &ulIndex);

        /* 判断TFT的长度是否超出了最大允许的范围 */
        if ((ulIndex + pTmpSendMsg[ulTmpSum]) > NAS_ESM_MAX_TFT_BYTE)
        {
            NAS_ESM_SndOmLogCnMsgEncodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_ENCODE_CN_MSG_IE_LEN_INVALID,
                                            ulIndex + pTmpSendMsg[ulTmpSum]);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_EncodeTftCreateTftOrReplacePf_ENUM, 2);
            return NAS_ESM_FAILURE;
        }

        pTmpSendMsg[ulTmpSum] += (VOS_UINT8)ulIndex;

        /*记录长度*/
        ulSum = ulSum + ulIndex;

        /*ulIndex归零*/
        ulIndex = NAS_ESM_NULL;
    }

    *pulLength = ulSum;

    return NAS_ESM_SUCCESS;
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_ESM_VerifyAppAuthParam_PPP
 Description     : 对PPP拨号的场景及拨号鉴权参数进行检查
 Input           : None
 Output          : VOS_TRUE : 参数合法
                   VOS_FALSE: 参数非法
 Return          : VOS_VOID

 History         :
    1.niuxiufan 00181501      2012-08-16  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_VerifyAppAuthParam_PPP( const APP_ESM_AUTH_INFO_STRU *pstAuthInfo )
{
    if (APP_ESM_AUTH_TYPE_PAP == pstAuthInfo->enAuthType)
    {
        if ((APP_ESM_PPP_MAX_USERNAME_LEN < pstAuthInfo->unAuthParam.stPapParam.ucUsernameLen)
             || (APP_ESM_PPP_MAX_PASSWORD_LEN < pstAuthInfo->unAuthParam.stPapParam.ucPasswordLen))
        {
             NAS_ESM_NORM_LOG("NAS_ESM_VerifyAppAuthParam_PPP:PAP Input gw auth len is err!");
             TLPS_PRINT2LAYER_INFO(NAS_ESM_VerifyAppAuthParam_PPP_ENUM, 1);
             return VOS_FALSE;
        }
    }

    if (APP_ESM_AUTH_TYPE_CHAP == pstAuthInfo->enAuthType)
    {
        if ((APP_ESM_PPP_CHAP_CHALLNGE_LEN != pstAuthInfo->unAuthParam.stChapParam.ulChallengeLen)
             || (APP_ESM_PPP_CHAP_RESPONSE_LEN != pstAuthInfo->unAuthParam.stChapParam.ulResponseLen)
             || (APP_ESM_PPP_MAX_USERNAME_LEN < pstAuthInfo->unAuthParam.stChapParam.ucResponseNameLen)
             || (APP_ESM_PPP_CHAP_CHALLNGE_NAME_LEN < pstAuthInfo->unAuthParam.stChapParam.ulChallengeNameLen))
        {

             NAS_ESM_NORM_LOG("NAS_ESM_VerifyAppAuthParam_PPP:Input CHAP gw auth len is err!");
             TLPS_PRINT2LAYER_INFO(NAS_ESM_VerifyAppAuthParam_PPP_ENUM, 2);
             return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}


/*****************************************************************************
 Function Name   : NAS_ESM_SndOmLogCnMsgEncodeFail
 Description     : ESM空口信元编码失败，可维可测上报
 Input           : enIeType 信元类型
                   enCause  失败原因
                   ulValue  失败值
 Output          : None
 Return          : None

 History         :
    1.chengmin 00285307      2015-6-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndOmLogCnMsgEncodeFail
(
    NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32                  enIeType,
    NAS_ESM_ENCODE_CN_MSG_FAIL_CAUSE_ENUM_UINT32        enCause,
    VOS_UINT32                                          ulValue
)
{
    NAS_ESM_OM_LOG_ENCODE_CN_MSG_FAIL_STRU      *pstMsg = VOS_NULL_PTR;
#if (VOS_OS_VER == VOS_WIN32)
        VOS_CHAR                                     acPrintStr[MAX_PRINT_CHAR_NUM] = {0};
        VOS_CHAR                                     acValue[MAX_PRINT_CHAR_NUM]    = {0};
#endif

    pstMsg = (NAS_ESM_OM_LOG_ENCODE_CN_MSG_FAIL_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_OM_LOG_ENCODE_CN_MSG_FAIL_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndOmLogCnMsgEncodeFail: mem alloc fail!.");
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_ESM_OM_LOG_ENCODE_CN_MSG_FAIL_STRU),
                        0,
                        sizeof(NAS_ESM_OM_LOG_ENCODE_CN_MSG_FAIL_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_ESM_OM_LOG_ENCODE_CN_MSG_FAIL_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_ESM_OM_LOG_ENCODE_CN_MSG_FAIL;
    pstMsg->enIeType                    = enIeType;
    pstMsg->enCause                     = enCause;
    pstMsg->ulValue                     = ulValue;

#if (VOS_OS_VER == VOS_WIN32)
        VOS_StrCpy(acPrintStr, "CN MSG Encode Fail, Fail IE:");
        VOS_StrCat(acPrintStr, g_EsmDecodeFailIePrintTable[enIeType-1].aucPrintStr);
        VOS_StrCat(acPrintStr, ", Fail Cause:");
        VOS_StrCat(acPrintStr, g_EsmEncodeFailCausePrintTable[enCause-1].aucPrintStr);
        VOS_sprintf(acValue, ", Value:%d", ulValue);
        VOS_StrCat(acPrintStr, acValue);
        NAS_ESM_ERR_LOG(acPrintStr);
#endif


    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
    return;
}


#ifdef __cplusplus
    #if __cplusplus
                                                }
    #endif
#endif

