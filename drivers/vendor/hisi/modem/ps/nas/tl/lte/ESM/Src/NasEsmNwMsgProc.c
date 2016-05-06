/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmNwMsgProc.c
  Description     :
  History         :
     1.sunbing49683       2009-2-24   Draft Enact
     2.杨茜惠 00135146    2009-03-06  Modify  BA8D01127
     3.李洪00150010       2009-08-03  Modify  BJ9D01608
     4.李洪00150010       2009-08-05  Modify  BJ9D01627

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEsmNwMsgProc.h"
#include  "NasCommBuffer.h"
#include  "NasLmmPubMOm.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMNWMSGPROC_C
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

#if (VOS_OS_VER == VOS_WIN32)
NAS_ESM_OM_VERIFY_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU  g_EsmVerifyCnMsgFailCausePrintTable[] =
{
    {ESM_VERIFY_CN_MSG_VALUE_INVALID                        , "ESM_VERIFY_CN_MSG_VALUE_INVALID"},
    {ESM_VERIFY_CN_MSG_PTI_MISMATCH                         , "ESM_VERIFY_CN_MSG_PTI_MISMATCH"},
    {ESM_VERIFY_CN_MSG_STATE_TABLE_FULL                     , "ESM_VERIFY_CN_MSG_STATE_TABLE_FULL"},
    {ESM_VERIFY_CN_MSG_IN_PDN_DISCONN_PROCEDURE             , "ESM_VERIFY_CN_MSG_IN_PDN_DISCONN_PROCEDURE"},
    {ESM_VERIFY_CN_MSG_FILT_NOT_SAME_CID                    , "ESM_VERIFY_CN_MSG_FILT_NOT_SAME_CID"},
    {ESM_VERIFY_CN_MSG_TAD_INVALID                          , "ESM_VERIFY_CN_MSG_TAD_INVALID"},
    {ESM_VERIFY_CN_PF_RENDER_EMPTY                          , "ESM_VERIFY_CN_PF_RENDER_EMPTY"},
    {ESM_VERIFY_CN_NO_UPLINK_PF                             , "ESM_VERIFY_CN_NO_UPLINK_PF"},
    {ESM_VERIFY_CN_NO_OPERATION_NO_QOS                      , "ESM_VERIFY_CN_NO_OPERATION_NO_QOS"},
    {ESM_VERIFY_CN_ADD_FILTER_NOT_INCREASE                  , "ESM_VERIFY_CN_ADD_FILTER_NOT_INCREASE"},
    {ESM_VERIFY_CN_DEL_FILTER_NOT_DECREASE                  , "ESM_VERIFY_CN_DEL_FILTER_NOT_DECREASE"},
    {ESM_VERIFY_CN_UE_CN_OPERATION_COLLISION                , "ESM_VERIFY_CN_UE_CN_OPERATION_COLLISION"},
    {ESM_VERIFY_CN_UPDATE_STATE_TABLE_FAIL                  , "ESM_VERIFY_CN_UPDATE_STATE_TABLE_FAIL"},
    {ESM_VERIFY_CN_MSG_CN_REJ_EPSBID_NOT_ZERO               , "ESM_VERIFY_CN_MSG_CN_REJ_EPSBID_NOT_ZERO"},
    {ESM_VERIFY_CN_MSG_ESM_INFO_REQ_EPSBID_NOT_ZERO         , "ESM_VERIFY_CN_MSG_ESM_INFO_REQ_EPSBID_NOT_ZERO"},
    {ESM_VERIFY_CN_MSG_CN_MSG_TYPE_INVALID                  , "ESM_VERIFY_CN_MSG_CN_MSG_TYPE_INVALID"},
    {ESM_VERIFY_CN_MSG_ACT_DEDIC_OP_NOT_CREATE_TFT          , "ESM_VERIFY_CN_MSG_ACT_DEDIC_OP_NOT_CREATE_TFT"}
};

const VOS_UINT32 g_EsmVerifyCnMsgFailCausePrintTableSize =
              (sizeof(g_EsmVerifyCnMsgFailCausePrintTable)/sizeof(NAS_ESM_OM_VERIFY_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU));

extern NAS_ESM_OM_CN_MSG_IE_PRINT_STR_STRU  g_EsmDecodeFailIePrintTable[];
#endif


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftOpCreateTftRsltProc
 Description     : 对承载修改的TAD码为Create TFT 检查结果的处理
 Input           : enRslt          -- 检查结果
                   pstEsmNwMsgIE   -- 译码后的空口消息指针
                   ulStateTblIndex -- 动态表索引
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu00143951      2010-5-14  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_ValidateTftOpCreateTftRsltProc
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    NAS_ESM_ENCODE_INFO_STRU           *pstEncodeInfo,
    NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8   enRslt,
    VOS_UINT32                          ulStateTblIndex
)
{
    (VOS_VOID)enRslt;

    /* Create TFT时,对应的专有承载的TFT不能存在 */
    if (NAS_ESM_BEARER_TYPE_DEDICATED == NAS_ESM_GetBearCntxtType(pstEsmNwMsgIE->ucEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidateTftOpCreateTftRsltProc:The created Ttf already exist!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftOpCreateTftRsltProc_ENUM, 1);
        pstEncodeInfo->ucESMCau = NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
        NAS_ESM_BearModFailProc(pstEncodeInfo, ulStateTblIndex);
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftOpNoOpRsltProc
 Description     : 对承载修改的TAD码为No operation 检查结果的处理
 Input           : enRslt          -- 检查结果
                   pstEsmNwMsgIE   -- 译码后的空口消息指针
                   ulStateTblIndex -- 动态表索引
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu00143951      2010-5-14  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_ValidateTftOpNoOpRsltProc
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    NAS_ESM_ENCODE_INFO_STRU           *pstEncodeInfo,
    NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8   enRslt,
    VOS_UINT32                          ulStateTblIndex
)
{
    (VOS_VOID)pstEsmNwMsgIE;

    /* 修改Qos时,对应的filter必须全部找到或者部分找到，且属于同一CID下 */
    if (NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND == enRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidateTftOpNoOpRsltProc:Tad code error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftOpNoOpRsltProc_ENUM, 1);
        pstEncodeInfo->ucESMCau = NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
        NAS_ESM_BearModFailProc(pstEncodeInfo, ulStateTblIndex);
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_CreatePfPrecedenceValidateList
 Description     : 获取某承载下packet filter优先级验证列表
 Input           : ucEpsbId------------------承载号
 Output          : pucPfNum------------------packet filter数
                   pstPfPVList---------------优先级验证列表首地址
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-5-27  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_GetPfPrecedenceValidateListInBearer
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                          *pucPfNum,
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEspbCntxtInfo    = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_TFT_STRU           *pstPacketFilter     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt1              = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt2              = NAS_ESM_NULL;

    pstEspbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucEpsbId);

    NAS_ESM_INFO_LOG1("Show all PF of specefic EPSB ID below:",ucEpsbId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_GetPfPrecedenceValidateListInBearer_ENUM, 1, ucEpsbId);

    for(ulCnt1 = NAS_ESM_MIN_CID; ulCnt1 <= NAS_ESM_MAX_CID; ulCnt1++)
    {
        if(NAS_ESM_OP_TRUE !=((pstEspbCntxtInfo->ulBitCId >> ulCnt1 )& NAS_ESM_BIT_0))
        {
            continue;
        }

        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt1);

        for (ulCnt2 = NAS_ESM_NULL; ulCnt2 < pstSdfCntxtInfo->ulSdfPfNum; ulCnt2++)
        {
            pstPacketFilter = &pstSdfCntxtInfo->astSdfPfInfo[ulCnt2];
            pstPfPVList[*pucPfNum].ucEpsbId = (VOS_UINT8)pstSdfCntxtInfo->ulEpsbId;
            pstPfPVList[*pucPfNum].ucPfId = pstPacketFilter->ucNwPacketFilterId;
            pstPfPVList[*pucPfNum].ucPrecedence = pstPacketFilter->ucPrecedence;
            /* 设置TFT的时候验证优先级会比较Cid */
            pstPfPVList[*pucPfNum].ucCid = (VOS_UINT8)ulCnt1;

            pstPfPVList[*pucPfNum].enDirection = pstPacketFilter->enDirection;

            NAS_ESM_INFO_LOG2("CID: Precedence:", ulCnt1, pstPacketFilter->ucPrecedence);
            TLPS_PRINT2LAYER_INFO2(NAS_ESM_GetPfPrecedenceValidateListInBearer_ENUM, 2, ulCnt1, pstPacketFilter->ucPrecedence);
            (*pucPfNum)++;
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateDelPfRenderEmptyOrNoUplinkPf
 Description     : 验证delete packet filter是否会导致专有承载的TFT为空
 Input           : pstNwMsg-------------------------译码后的空口消息
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong   00150010      2010-5-28  Draft Enact
    2.sunjitan 00193151      2015-04-25 Modify for R11
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateDelPfRenderEmptyOrNoUplinkPf
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{
    VOS_UINT8                           ucPfPVNum       = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt1          = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt2          = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt3          = NAS_ESM_NULL;
    VOS_UINT8                           ucNumTmp        = NAS_ESM_NULL;
    NAS_ESM_PF_PRCDNC_VLDT_STRU         astPfPVListTmp[NAS_ESM_MAX_SDF_PF_NUM];
    const NAS_ESM_CONTEXT_TFT_STRU     *pstPacketFilter = VOS_NULL_PTR;

    NAS_ESM_MEM_SET_S(  astPfPVListTmp,
                        sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU) * NAS_ESM_MAX_SDF_PF_NUM,
                        0,
                        sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU)*NAS_ESM_MAX_SDF_PF_NUM);


    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(pstNwMsg->ucEpsbId)))
    {
        return NAS_ESM_CAUSE_SUCCESS;
    }

    if (NAS_ESM_TFT_OP_TYPE_DELETE_FILTER != pstNwMsg->stTadInfo.enTftOpType)
    {
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* 获取此承载下packet filter优先级验证列表 */
    NAS_ESM_GetPfPrecedenceValidateListInBearer(pstNwMsg->ucEpsbId,
                                                &ucPfPVNum,
                                                astPfPVListTmp);

    NAS_ESM_INFO_LOG1("NAS_ESM_ValidateDelPfRenderEmptyOrNoUplinkPf: release version = ", NAS_EMM_GetNasRelease());
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateDelPfRenderEmptyOrNoUplinkPf_ENUM, 1, NAS_EMM_GetNasRelease());

    /* 判断一共删除了承载下的多少个Packet filter, 计数为ucNumTmp */
    for (ucCnt1 = 0; ucCnt1 < pstNwMsg->stTadInfo.ucSdfPfNum; ucCnt1++)
    {
        pstPacketFilter = &pstNwMsg->stTadInfo.astSdfPfInfo[ucCnt1];
        for (ucCnt2 = 0; ucCnt2 < ucPfPVNum; ucCnt2++)
        {
            if (pstPacketFilter->ucNwPacketFilterId == astPfPVListTmp[ucCnt2].ucPfId)
            {
                /* 被删除的PF，其方向被强行记录为无效，此做法用于R11的版本判断删除后是否存在上行PF */
                astPfPVListTmp[ucCnt2].enDirection = APP_ESM_TRANSFER_DIRECTION_BUTT;
                ucNumTmp++;
            }
        }
    }

    /* PF全部被删掉了，肯定语义错误，因为PF不能为空 */
    if (ucNumTmp >= ucPfPVNum)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_TFT_IE, ESM_VERIFY_CN_PF_RENDER_EMPTY, ucNumTmp);
        return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
    }

    /* PF没有全部被删掉，R11以上版本要判断如果删除后是否还存在上行PF */
    /* 24301 CR1937R4(Rel-11) 6.4.3.4  Semantic errors in packet filters
    2) When the resulting TFT,which is assigned to a dedicated EPS bearer context, does not contain any packet
    filter applicable for the uplink direction among the packet filters create on request from the network */
    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ValidateDelPfRenderEmptyOrNoUplinkPf: R11 release, judge del PF result!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ValidateDelPfRenderEmptyOrNoUplinkPf_ENUM, 11);
        for(ucCnt3 = 0; ucCnt3 < ucPfPVNum; ucCnt3++)
        {
            /* 只要不是下行PF就跳出 */
            if((APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK == astPfPVListTmp[ucCnt3].enDirection)
                ||(APP_ESM_TRANSFER_DIRECTION_UPLINK == astPfPVListTmp[ucCnt3].enDirection))
            {
                break;
            }
        }

        /* 循环结束也没找到上行PF，认为删除后不再存在上行PF，语义错误*/
        if(ucCnt3 >= ucPfPVNum)
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_TFT_IE, ESM_VERIFY_CN_NO_UPLINK_PF, ucPfPVNum);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateDelPfRenderEmptyOrNoUplinkPf_ENUM, LNAS_ERROR);
            return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER;
        }
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftNwOpReplacePfRsltProc
 Description     : 对承载修改的TAD码为Replace PF检查结果的处理
 Input           : const NAS_ESM_NW_MSG_STRU*        空口消息
                   VOS_UINT32                        待修改的承载ID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2015-04-25  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_ValidateTftNwOpReplacePfRsltProc
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_PF_PRCDNC_VLDT_STRU         *pstPfPVList = VOS_NULL_PTR;
    VOS_UINT8                            ucPfNum     = 0;
    VOS_UINT8                            ucCnt       = 0;
    VOS_UINT8                            ucCnt2      = 0;
    VOS_UINT8                            ucCnt3      = 0;

    /* 无操作类型，返回成功 */
    if(NAS_ESM_OP_TRUE != pstEsmNwMsgIE->bitOpTadInfo)
    {
        return NAS_ESM_SUCCESS;
    }

    /* 不是replace操作，说明调用者使用错误，告警返回失败 */
    if(NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER != pstEsmNwMsgIE->stTadInfo.enTftOpType)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidateTftNwOpReplacePfRsltProc: TFT op type is not repalce.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftNwOpReplacePfRsltProc_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    /* 申请优先级验证列表存储空间，一个承载下不管多少CID，最多只能有16个PF */
    pstPfPVList = NAS_ESM_MEM_ALLOC(NAS_ESM_MAX_SDF_PF_NUM*sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU));

    /* 申请内存失败直接返回失败 */
    if(VOS_NULL_PTR == pstPfPVList)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidateTftNwOpReplacePfRsltProc: Alloc pflist fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftNwOpReplacePfRsltProc_ENUM, 2);
        return NAS_ESM_FAILURE;
    }

    NAS_ESM_MEM_SET_S(  pstPfPVList,
                        NAS_ESM_MAX_SDF_PF_NUM*sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU),
                        0,
                        NAS_ESM_MAX_SDF_PF_NUM*sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU));

    /* 取出当前承载下所有的PF */
    NAS_ESM_GetPfPrecedenceValidateListInBearer((VOS_UINT8)ulEpsbId, &ucPfNum, pstPfPVList);

    /* 验证网侧修改后的PF方向是否合法，对于空口中的每一个PF，都在列表中查找是否存在，
    存在就将列表中的PF方向修改为空口中的值，如果列表中不存在，添加到列表中 */
    for(ucCnt = 0; ucCnt < pstEsmNwMsgIE->stTadInfo.ucSdfPfNum; ucCnt++)
    {
        for(ucCnt2 = 0; ucCnt2 < ucPfNum; ucCnt2++)
        {
            if(pstEsmNwMsgIE->stTadInfo.astSdfPfInfo[ucCnt].ucNwPacketFilterId == pstPfPVList[ucCnt2].ucPfId)
            {
                pstPfPVList[ucCnt2].enDirection = pstEsmNwMsgIE->stTadInfo.astSdfPfInfo[ucCnt].enDirection;
                break;
            }
        }

        /* 如果空口中的PF的ID列表中没有，且列表未满，添加到列表中 */
        if((ucCnt2 >= ucPfNum)&&(ucPfNum < NAS_ESM_MAX_SDF_PF_NUM))
        {
            /* 列表中PF的数量加1，由于PF ID具有唯一性，所以不会存在问题 */
            ucPfNum++;

            /* 将新的PF放到表尾 */
            pstPfPVList[ucPfNum-1].ucEpsbId    = (VOS_UINT8)ulEpsbId;
            pstPfPVList[ucPfNum-1].ucPfId      = pstEsmNwMsgIE->stTadInfo.astSdfPfInfo[ucCnt].ucNwPacketFilterId;
            pstPfPVList[ucPfNum-1].enDirection = pstEsmNwMsgIE->stTadInfo.astSdfPfInfo[ucCnt].enDirection;
        }
    }

    /* 全部替换结束，检查当前承载下是否存在上行PF */
    for(ucCnt3 = 0; ucCnt3 < ucPfNum; ucCnt3++)
    {
        if((APP_ESM_TRANSFER_DIRECTION_UPLINK == pstPfPVList[ucCnt3].enDirection)
            ||(APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK== pstPfPVList[ucCnt3].enDirection))
        {
            NAS_ESM_INFO_LOG1("NAS_ESM_ValidateTftNwOpReplacePfRsltProc: Exist uplink pf, ID = ", ucCnt3);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateTftNwOpReplacePfRsltProc_ENUM, 3, ucCnt3);
            break;
        }
    }

    /* 释放申请的内存 */
    NAS_ESM_MEM_FREE(pstPfPVList);

    /* 未找到上行PF，返回失败 */
    if(ucCnt3 >= ucPfNum)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_TFT_IE, ESM_VERIFY_CN_NO_UPLINK_PF, ucPfNum);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;

}


/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftOpDelTftOrDelPfRsltProc
 Description     : 对承载修改的TAD码为Delete filter,Delete TFT
                   检查结果的处理
 Input           : enRslt          -- 检查结果
                   pstEsmNwMsgIE   -- 译码后的空口消息指针
                   ulStateTblIndex -- 动态表索引
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu00143951      2010-5-14  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_ValidateTftOpDelTftOrDelPfRsltProc
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    NAS_ESM_ENCODE_INFO_STRU           *pstEncodeInfo,
    NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8   enRslt,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulSndNwMsgLen   = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause      = NAS_ESM_NULL;


    /* 如果没找到CID，且当前TAD操作码为DELETE_FILTER或者DELETE TFT，则回复修改承载成功 */
    if (NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND == enRslt)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ValidateTftOpDelTftOrDelPfRsltProc: accept delete not exist filter !");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ValidateTftOpDelTftOrDelPfRsltProc_ENUM, 1);

        /*向网侧回复Modify EPS bearer context accept*/
        NAS_ESM_EncodeModEpsbCntxtAccMsg(pstEncodeInfo, \
                                 NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                &ulSndNwMsgLen);
        NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                   ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                   ESM_MOD_EPS_BEARER_CNTXT_ACP);
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
        NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

        return NAS_ESM_MSG_HANDLED;
    }

    /* 专有承载不能删除TFT */
    if ((NAS_ESM_TFT_OP_TYPE_DELETE_TFT == pstEsmNwMsgIE->stTadInfo.enTftOpType)
        && (NAS_ESM_BEARER_TYPE_DEDICATED == NAS_ESM_GetBearCntxtType(pstEsmNwMsgIE->ucEpsbId)))
    {
        /*打印信息*/
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_TFT_IE, ESM_VERIFY_CN_MSG_TAD_INVALID, enRslt);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftOpDelTftOrDelPfRsltProc_ENUM, 2);

        pstEncodeInfo->ucESMCau = NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
        NAS_ESM_BearModFailProc(pstEncodeInfo, ulStateTblIndex);
        return NAS_ESM_MSG_HANDLED;
    }
    /* 验证delete packet filter是否会导致专有承载的TFT为空或无上行PF，若是回复拒绝消息，
       原因值为NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT */
    enEsmCause = NAS_ESM_ValidateDelPfRenderEmptyOrNoUplinkPf(pstEsmNwMsgIE);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        /*打印信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_ValidateTftOpDelTftOrDelPfRsltProc:NAS_ESM_ValidateDelPfRenderEmptyOrNoUplinkPf failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftOpDelTftOrDelPfRsltProc_ENUM, 3);

        pstEncodeInfo->ucESMCau = enEsmCause;
        NAS_ESM_BearModFailProc(pstEncodeInfo, ulStateTblIndex);
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftOpRsltProc
 Description     : 对承载修改的TAD码检查结果的处理
 Input           : enRslt          -- 检查结果
                   pstEsmNwMsgIE   -- 译码后的空口消息指针
                   ulStateTblIndex -- 动态表索引
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu00143951      2010-5-14  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_ValidateTftOpRsltProc
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8   enRslt,
    NAS_ESM_ENCODE_INFO_STRU           *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    /* 修改承载,修改的filter必须在同一个Sdf上*/
    if ((NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_UNEQUAL_CID == enRslt)
     || (NAS_ESM_QUERY_CID_RSLT_PART_FOUND_UNEQUAL_CID == enRslt))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_TFT_IE, ESM_VERIFY_CN_MSG_FILT_NOT_SAME_CID, enRslt);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftOpRsltProc_ENUM, 1);
        pstEncodeInfo->ucESMCau = NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
        NAS_ESM_BearModFailProc(pstEncodeInfo, ulStateTblIndex);
        return NAS_ESM_MSG_HANDLED;
    }

    if (NAS_ESM_OP_TRUE != pstEsmNwMsgIE->bitOpTadInfo)
    {
        return NAS_ESM_SUCCESS;
    }

    switch(pstEsmNwMsgIE->stTadInfo.enTftOpType)
    {

        case NAS_ESM_TFT_OP_TYPE_DELETE_TFT:
        case NAS_ESM_TFT_OP_TYPE_DELETE_FILTER:
            return NAS_ESM_ValidateTftOpDelTftOrDelPfRsltProc(pstEsmNwMsgIE,
                                                              pstEncodeInfo,
                                                              enRslt,
                                                              ulStateTblIndex);
        case NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER:

            /* R11版本要检查修改后的PF是否合法 */
            /* 24301 CR1937R4(Rel-11) 6.4.3.4  Semantic errors in packet filters
            2) When the resulting TFT,which is assigned to a dedicated EPS bearer context, does not contain any packet
            filter applicable for the uplink direction among the packet filters create on request from the network */
            if(ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
            {
                if(NAS_ESM_SUCCESS != NAS_ESM_ValidateTftNwOpReplacePfRsltProc(pstEsmNwMsgIE, pstEncodeInfo->ulEpsbId))
                {
                    pstEncodeInfo->ucESMCau = NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER;
                    NAS_ESM_BearModFailProc(pstEncodeInfo, ulStateTblIndex);
                    return NAS_ESM_MSG_HANDLED;
                }
            }
            break;

        case NAS_ESM_TFT_OP_TYPE_NO_OP:
            return NAS_ESM_ValidateTftOpNoOpRsltProc(pstEsmNwMsgIE,
                                                     pstEncodeInfo,
                                                     enRslt,
                                                     ulStateTblIndex);
        default:
             break;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftOpInModMsg
 Description     : 验证PF的语义是否正确
 Input           : NAS_ESM_NW_MSG_STRU                *pstEsmNwMsgIE
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2009-5-27  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_ValidateTftOpInModMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    NAS_ESM_ENCODE_INFO_STRU           *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulCId               = NAS_ESM_NULL;
    NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8   enRslt              = NAS_ESM_QUERY_CID_RSLT_BUTT;

    enRslt = NAS_ESM_QuerySdfId(pstEsmNwMsgIE,&ulCId);


    return NAS_ESM_ValidateTftOpRsltProc(pstEsmNwMsgIE,
                                         enRslt,
                                         pstEncodeInfo,
                                         ulStateTblIndex);
}
/*****************************************************************************
 Function Name   : NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg
 Description     : 处理ESM STATUS消息，错误原因值为97或81
 Input           : pstEsmNwMsgIE--------------------译码后的网络消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2010-5-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE
)
{
    VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;

    if (pstEsmNwMsgIE->ucPti == NAS_ESM_PTI_UNASSIGNED_VALUE)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg:WARN:PTI is unassigned!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg_ENUM, 1);
        return ;
    }

    /*根据PTI，找到动态表Index*/
    if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByPti(  pstEsmNwMsgIE->ucPti,
                                                            &ulStateTblId))
    {
        switch(NAS_ESM_GetStateTblAppMsgType(ulStateTblId))
        {
            case ID_APP_ESM_PDP_SETUP_REQ:
                NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblId,
                        NAS_ESM_GetAppErrorByEsmCause(pstEsmNwMsgIE->enEsmCau));
                break;
            case ID_APP_ESM_PDP_RELEASE_REQ:
                NAS_ESM_SndEsmAppSdfRelCnfFailMsg(  ulStateTblId,
                        NAS_ESM_GetAppErrorByEsmCause(pstEsmNwMsgIE->enEsmCau));
                break;
            case ID_APP_ESM_PDP_MODIFY_REQ:
                NAS_ESM_SndEsmAppSdfModCnfFailMsg(  ulStateTblId,
                        NAS_ESM_GetAppErrorByEsmCause(pstEsmNwMsgIE->enEsmCau));
                break;
            case ID_APP_ESM_NDISCONN_REQ:
                NAS_ESM_LOG1("NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg:ERROR =", NAS_ESM_GetAppErrorByEsmCause(pstEsmNwMsgIE->enEsmCau));
                TLPS_PRINT2LAYER_INFO1(NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg_ENUM, 2, NAS_ESM_GetAppErrorByEsmCause(pstEsmNwMsgIE->enEsmCau));
                NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblId,
                        NAS_ESM_GetAppErrorByEsmCause(pstEsmNwMsgIE->enEsmCau));
                break;
            default:
                NAS_ESM_NORM_LOG("NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg: Error: Illegal App Msg Type!");
                TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg_ENUM, LNAS_MSG_INVALID);
                break;
        }

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblId);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcEsmStatusCauseInvalidEpsbId
 Description     : 处理ESM STATUS消息，错误原因值为43
 Input           : pstEsmNwMsgIE--------------------译码后的网络消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2010-5-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcEsmStatusCauseInvalidEpsbId
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE
)
{
    VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;

    /* 若PTI已存在于状态表，则先停止流程 */
    NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg(pstEsmNwMsgIE);

    if((pstEsmNwMsgIE->ucEpsbId < NAS_ESM_MIN_EPSB_ID)
        ||(pstEsmNwMsgIE->ucEpsbId > NAS_ESM_MAX_EPSB_ID))
    {
        return ;
    }

    /*通知APP释放缺省承载及其关联承载*/
    NAS_ESM_DeactBearerAndInformApp(pstEsmNwMsgIE->ucEpsbId);

    /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /*根据ulEpsbId查找StatTbl表ID*/
    if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(pstEsmNwMsgIE->ucEpsbId,&ulStateTblId))
    {
        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblId);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcValidNwsMsgEsmStatus
 Description     : 处理ESM STATUS消息
 Input           : pstEsmNwMsgIE--------------------译码后的网络消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-7-8  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcValidNwsMsgEsmStatus
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE
)
{
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwsMsgEsmStatus is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwsMsgEsmStatus_ENUM, LNAS_ENTRY);

    /* 若不带ESM CAUSE信元，则直接返回 */
    if(NAS_ESM_OP_TRUE != pstEsmNwMsgIE->bitOpEsmCause)
    {
        return;
    }

    switch (pstEsmNwMsgIE->enEsmCau)
    {
        case NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED:
        case NAS_ESM_CAUSE_INVALID_PTI_VALUE:
            NAS_ESM_ProcEsmStatusCauseInvalidPtiOrNonExistMsg(pstEsmNwMsgIE);
            break;
        case NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY:
            NAS_ESM_ProcEsmStatusCauseInvalidEpsbId(pstEsmNwMsgIE);
            break;
        default:
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgDeactProcedureCollision
 Description     : 针对同一承载，网络发起的流程与UE发起的流程产生冲突，
                   本函数实现流程冲突处理功能，在状态机函数中不再处理冲突流程
 Input           : EMM_ESM_INTRA_DATA_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-2-20  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgDeactProcedureCollision
(
    VOS_UINT32                          ulStateTblId,
    const NAS_ESM_NW_MSG_STRU           *pRcvMsg
)
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulSndNwMsgLen       = NAS_ESM_NULL;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_ProcNwMsgDeactProcedureCollision is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgDeactProcedureCollision_ENUM, LNAS_ENTRY);

    ulEpsbId = (VOS_UINT32)pRcvMsg->ucEpsbId;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblId);

    /*如果当前承载处于PDN去连接过程中，则处理去激活流程，终止PDN去连接流程*/
    if(NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REQ == \
                                    pstStateAddr->stNwMsgRecord.enEsmCnMsgType)

    {
        /*通知APP释放缺省承载及其关联承载*/
        NAS_ESM_DeactBearerAndInformApp(ulEpsbId);

        /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
        NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblId);
    }
    /*如果当前承载处于承载修改请求过程中(专有承载释放)，则处理去激活流程，终止承载资源修改流程*/
    else if(NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ == \
                                pstStateAddr->stNwMsgRecord.enEsmCnMsgType)
    {
        /*通知APP释放缺省承载及其关联承载*/
        NAS_ESM_DeactBearerAndInformApp(ulEpsbId);

        /*通知EMM当前承载状态信息，发送ID_EMM_ESM_BEARER_STATUS_REQ*/
        NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

        /*释放状态表资源*/
        NAS_ESM_RelStateTblResource(ulStateTblId);
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgDeactProcedureCollision:WARNNING:Undefine Collision Process!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgDeactProcedureCollision_ENUM, 1);
        return;
    }

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_FALSE;
    stEncodeInfo.ucPti       = pRcvMsg->ucPti;
    stEncodeInfo.ulEpsbId    = ulEpsbId;

    /*向网侧回复Deactivate EPS bearer context accept*/
    NAS_ESM_EncodeDeactEpsbCntxtAccMsg(stEncodeInfo, \
                               NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                              &ulSndNwMsgLen);
    /*空口消息上报*/
    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                       ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                       ESM_DEACT_EPS_BEARER_CNTXT_ACP);
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

}

/*****************************************************************************
 Function Name   : NAS_ESM_SndRejAirMsg
 Description     : 发送各种REJ空口消息
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-4-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SndRejAirMsg
(
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enEsmCnMsgType,
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo
)
{
    VOS_UINT32                          ulSndNwMsgLen       = NAS_ESM_NULL;

    switch(enEsmCnMsgType)
    {
        case NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_EncodeActDedictdEpsbCntxtRejMsg(    *pstEncodeInfo,\
                                                        NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                                        &ulSndNwMsgLen);
            NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,
                                       NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                       ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REJ);
            break;

        case NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_EncodeActDefltEpsbCntxtRejMsg(  *pstEncodeInfo,\
                                                    NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                                    &ulSndNwMsgLen);
            NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,
                                       NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                       ESM_ACT_DEFLT_EPS_BEARER_CNTXT_REJ);
            break;

        case NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ:
            NAS_ESM_EncodeModEpsbCntxtRejMsg(   *pstEncodeInfo, \
                                                NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                                &ulSndNwMsgLen);
            NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,
                                       NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                       ESM_MOD_EPS_BEARER_CNTXT_REJ);
            break;
        case NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_REQ:
            NAS_ESM_EncodeEsmStatus(    *pstEncodeInfo, \
                                        NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                        &ulSndNwMsgLen);
            NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,
                                       NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                       ESM_STUS_MO);
            break;
        default:
            NAS_ESM_NORM_LOG("NAS_ESM_SndRejAirMsg:NORM: Ignore NW msg");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SndRejAirMsg_ENUM, LNAS_MSG_INVALID);
            return;
    }

    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILL_CID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);
}

/*sunbing 49683 2013-10-14 VoLTE begin*/
/*****************************************************************************
 Function Name   : NAS_ESM_SndApsEsmNotificationIndMsg
 Description     : 向APS发送ESM Notification ind消息
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing 49683      2013-10-14  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndApsEsmNotificationIndMsg
(
    ESM_APS_NOTIFICATION_IND_ENUM_UINT32   enNotificationIndValue
)
{
    ESM_APS_NOTIFICATION_IND_STRU    *pstNotificationInd  = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstNotificationInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_APS_NOTIFICATION_IND_STRU));

    if ( VOS_NULL_PTR == pstNotificationInd )
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndApsEsmNotificationIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndApsEsmNotificationIndMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*清空*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstNotificationInd),
                        NAS_ESM_GET_MSG_LENGTH(pstNotificationInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstNotificationInd));

    pstNotificationInd->enNotificationIndicator = enNotificationIndValue;

    /*填写消息头*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstNotificationInd, ID_ESM_APS_ESM_NOTIFICATION_IND);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstNotificationInd);
}
/*sunbing 49683 2013-10-14 VoLTE begin*/


/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgForIllegalPti
 Description     : 由于网络携带的PTI不合法，UE根据网络消息内容发拒绝消息或直
                   接忽略
 Input           : NAS_ESM_NW_MSG_STRU stEsmNwMsgIE
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-2-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgForIllegalPti
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
)
{
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    VOS_UINT32                          ulEsmBuffIndex      = NAS_ESM_NULL;
    VOS_UINT8                           ucPti               = pstEsmNwMsgIE->ucPti;
    VOS_UINT32                          ulMsgId             = NAS_ESM_NULL;
    NAS_ESM_PTI_BUFF_ITEM_STRU         *pstPtiBuffItem      = VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIndex;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstEhrpdEntity   = VOS_NULL_PTR;
    #endif

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ucESMCau    = enEsmCause;
    stEncodeInfo.ucPti       = pstEsmNwMsgIE->ucPti;
    stEncodeInfo.ulEpsbId    = (VOS_UINT32)pstEsmNwMsgIE->ucEpsbId;

    if (enEsmCause != NAS_ESM_CAUSE_PTI_MISMATCH)
    {
        /*返回REJ消息*/
        NAS_ESM_SndRejAirMsg(pstEsmNwMsgIE->enEsmCnMsgType, &stEncodeInfo);

        return ;
    }

    /* 根据PTI查找ESM缓存记录 */
    if (NAS_ESM_SUCCESS != NAS_ESM_QueryPtiBuffItemByPti(   ucPti,
                                                            &ulEsmBuffIndex))
    {
        NAS_ESM_LOG1("NAS_ESM_ProcNwMsgForIllegalPti:WARNING:PTI not matched!",ucPti);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ProcNwMsgForIllegalPti_ENUM, 1, ucPti);

        /*返回REJ消息*/
        NAS_ESM_SndRejAirMsg(pstEsmNwMsgIE->enEsmCnMsgType, &stEncodeInfo);

        return ;
    }

    NAS_ESM_INFO_LOG2("NAS_ESM_ProcNwMsgForIllegalPti:NORM:PTI is found in Esm Buffer!",
                 ucPti, ulEsmBuffIndex);
    TLPS_PRINT2LAYER_INFO2(NAS_ESM_ProcNwMsgForIllegalPti_ENUM, 2, ucPti, ulEsmBuffIndex);

    /* 获取缓存记录 */
    pstPtiBuffItem = (NAS_ESM_PTI_BUFF_ITEM_STRU*)
                            NAS_ESM_GetBuffItemAddr(NAS_ESM_BUFF_ITEM_TYPE_PTI, ulEsmBuffIndex);

    if (pstPtiBuffItem == VOS_NULL_PTR)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgForIllegalPti:WARN:Get buffer item failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgForIllegalPti_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /* 原来的消息检测失败，且原因值为NAS_ESM_CAUSE_ERROR时，所以没有回复消息 */
    if (pstPtiBuffItem->stEsmMsg.ulEsmMsgSize == NAS_ESM_NULL)
    {
        return ;
    }

    /* 获取消息ID */
    ulMsgId = pstPtiBuffItem->stEsmMsg.aucEsmMsg[NAS_ESM_MSGID_OFFSET];

    /* 如果当前状态为ATTACHING态，且回复消息为缺省承载激活成功消息，则给
       MM发送EMM_ESM_PDN_CON_SUCC_REQ消息，否则发送EMM_ESM_DATA_REQ消息*/
    if ((ulMsgId == NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC)
        && (NAS_ESM_PS_REGISTER_STATUS_ATTACHING == NAS_ESM_GetEmmStatus()))
    {
        NAS_ESM_SndEsmEmmPdnConSuccReqMsg(pstPtiBuffItem->stEsmMsg.ulEsmMsgSize,
                                          pstPtiBuffItem->stEsmMsg.aucEsmMsg);
    }
    else
    {
        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        /* 激活缺省承载，缓存也是ACP时，检查是否是EHRPD承载恢复流程，如果是，重新分配OPID发送 */
        if ((NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ == pstEsmNwMsgIE->enEsmCnMsgType)
          &&(NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC == ulMsgId))
        {
            if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedApn(&pstEsmNwMsgIE->stApnInfo, &ulIndex))
            {
                pstEhrpdEntity                               = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

                /* 新分配一个OPID并记录在EHRPD的PDN实体中，消息类型为激活缺省承载ACP */
                pstEhrpdEntity->stNwMsgRecord.ulNwMsgOpId    = NAS_ESM_AllocEmmEsmOpId();
                pstEhrpdEntity->stNwMsgRecord.enEsmCnMsgType = NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC;

                NAS_ESM_SndEsmEmmDataReqMsg(pstEhrpdEntity->stNwMsgRecord.ulNwMsgOpId,
                                            PS_FALSE,
                                            pstPtiBuffItem->stEsmMsg.ulEsmMsgSize,
                                            pstPtiBuffItem->stEsmMsg.aucEsmMsg);

                return;
            }
        }
        #endif

        /* 其他情况保持原处理 */
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID,
                                    PS_FALSE,
                                    pstPtiBuffItem->stEsmMsg.ulEsmMsgSize,
                                    pstPtiBuffItem->stEsmMsg.aucEsmMsg);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgForIllegalEpsbId
 Description     : 承载上下文EpsbId错误，UE返回拒绝消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhuyiqiang 00138739      2009-3-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgForIllegalEpsbId
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE
)
{
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    VOS_UINT32                          ulSndNwMsgLen = NAS_ESM_NULL;

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ucPti       = pstEsmNwMsgIE->ucPti;
    stEncodeInfo.ulEpsbId    = (VOS_UINT32)pstEsmNwMsgIE->ucEpsbId;
    stEncodeInfo.ucESMCau    = NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY;

    if (pstEsmNwMsgIE->enEsmCnMsgType == NAS_ESMCN_MSG_TYPE_DEACT_EPS_BEARER_CNTXT_REQ)
    {
        /*向网侧回复Deact EPS bearer context accept*/
        NAS_ESM_EncodeDeactEpsbCntxtAccMsg(stEncodeInfo, \
                                 NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                &ulSndNwMsgLen);
        NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                   ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                   ESM_DEACT_EPS_BEARER_CNTXT_ACP);
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
        NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);
    }
    else
    {
        /*给网侧发拒绝消息*/
        NAS_ESM_SndRejAirMsg(pstEsmNwMsgIE->enEsmCnMsgType, &stEncodeInfo);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgForDecodeError
 Description     : 空口消息译码错误处理
 Input           : NAS_ESM_NW_MSG_STRU *pstMsgIE
                   NAS_ESM_CAUSE_ENUM_UINT8  enEsmCause
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-2-24  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgForDecodeError(const NAS_ESM_NW_MSG_STRU *pstEsmNwMsgIE,
                                                     NAS_ESM_CAUSE_ENUM_UINT8  enEsmCause)
{
    VOS_UINT32                          ulSndNwMsgLen       = NAS_ESM_NULL;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    NAS_ESM_INFO_LOG("NAS_ESM_ProcNwMsgForDecodeError is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgForDecodeError_ENUM, LNAS_ENTRY);

    /* 若原因值为消息太短，则丢弃此消息 */
    if (NAS_ESM_CAUSE_MSG_TOO_SHORT == enEsmCause)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgForDecodeError:Msg too short!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgForDecodeError_ENUM, 1);
        return ;
    }

    /*初始化NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ulEpsbId    = (VOS_UINT32)pstEsmNwMsgIE->ucEpsbId;
    stEncodeInfo.ucPti       = pstEsmNwMsgIE->ucPti;
    stEncodeInfo.ucESMCau    = enEsmCause;

    /*根据接收到的空口消息类型处理*/
    switch(pstEsmNwMsgIE->enEsmCnMsgType)
    {
        /*如果网侧消息类型为ACT_DEFLT_EPS_BEARER_CNTXT_REQ*/
        case NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ:
            /*回复拒绝*/
            NAS_ESM_EncodeActDefltEpsbCntxtRejMsg(stEncodeInfo,\
                                         NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                        &ulSndNwMsgLen);

            NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,\
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                   ESM_ACT_DEFLT_EPS_BEARER_CNTXT_REJ);

            break;

        /*如果网侧消息类型为ACT_DEDICTD_EPS_BEARER_CNTXT_REQ*/
        case NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ:
            /*回复拒绝*/
            NAS_ESM_EncodeActDedictdEpsbCntxtRejMsg(stEncodeInfo,\
                                           NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                          &ulSndNwMsgLen);

            NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,\
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                   ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REJ);

            break;

        /*如果网侧消息类型为MOD_EPS_BEARER_CNTXT_REQ*/
        case NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ:
            /*回复拒绝*/
            NAS_ESM_EncodeModEpsbCntxtRejMsg(stEncodeInfo,\
                                    NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                   &ulSndNwMsgLen);

            NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,\
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                   ESM_MOD_EPS_BEARER_CNTXT_REJ);

            break;

        default:
            /*网络消息解码错误，返回ESM STATUS*/
            NAS_ESM_EncodeEsmStatus(stEncodeInfo,\
                                    NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                   &ulSndNwMsgLen);

            NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,\
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                   ESM_STUS_MO);


            /*打印异常信息*/
            NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmEmmDataInd:WARNING: NW Message Protocol Error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgForDecodeError_ENUM, LNAS_MSG_INVALID);
            break;
    }

    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcValidNwMsgEsmInfoReq
 Description     : 处理ESM INFORMATION REQ消息
 Input           : pstEsmNwMsgIE--------------------译码后的网络消息
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2009-3-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcValidNwMsgEsmInfoReq
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE
)
{
    VOS_UINT32                          ulSndNwMsgLen       = NAS_ESM_NULL;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    NAS_ESM_INFO_LOG("NAS_ESM_ProcValidNwMsgEsmInfoReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgEsmInfoReq_ENUM, LNAS_ENTRY);

    /*填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.ucPti = pstEsmNwMsgIE->ucPti;/*bsun 应该根据PDN连接请求中的PTI处理*/

    /*编码ESM INFORMATION RESPONSE消息*/
    if(NAS_ESM_FAILURE == NAS_ESM_EncodeEsmInformationRspMsg(stEncodeInfo, \
                                  NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                 &ulSndNwMsgLen))
    {
        /*打印错误消息，ESM INFORMATION RESPONSE消息编码错误*/
        NAS_ESM_WARN_LOG("NAS_ESM_ProcValidNwMsgEsmInfoReq:WARNING:EncodeEsmInformationRsp fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcValidNwMsgEsmInfoReq_ENUM, LNAS_FAIL);
        return;
    }

    /*空口消息上报*/
    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                               ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                               ESM_INFO_RSP);

    /*发送ESM INFORMATION RESPONSE消息*/
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);
}


/*****************************************************************************
 Function Name   : NAS_ESM_ValidatePtiInActDefltOrInfoOrRejMsg
 Description     : 对缺省承载激活请求或ESM INFO或REJ消息中的PTI进行合法性检测
 Input           : ulPti-------------------------PTI
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-5-13  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidatePtiInActDefltOrInfoOrRejMsg
(
    VOS_UINT8                           ucPti
)
{
    VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;

    NAS_ESM_LOG1("NAS_ESM_ValidatePtiInActDefltOrInfoOrRejMsg, Pti : ", ucPti);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidatePtiInActDefltOrInfoOrRejMsg_ENUM, LNAS_ENTRY, ucPti);

    if ((ucPti == NAS_ESM_PTI_UNASSIGNED_VALUE)
         || (ucPti == NAS_ESM_PTI_RESERVED_VALUE))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE, ESM_VERIFY_CN_MSG_VALUE_INVALID, ucPti);
        return NAS_ESM_CAUSE_INVALID_PTI_VALUE;
    }

    /* 根据PTI查找到动态表Index */
    if(NAS_ESM_SUCCESS != NAS_ESM_QueryStateTblIndexByPti(ucPti, &ulStateTblId))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE, ESM_VERIFY_CN_MSG_PTI_MISMATCH, ucPti);
        return NAS_ESM_CAUSE_PTI_MISMATCH;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidatePtiInActDedictOrModOrDeactOrStatusMsg
 Description     : 对专有承载激活请求或承载修改或承载去激活或ESM STATUS消息
                   中的PTI进行合法性检测
 Input           : ulPti-------------------------PTI
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-5-13  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidatePtiInActDedictOrModOrDeactOrStatusMsg
(
    VOS_UINT32                          ulPti,
    VOS_UINT32                         *pulStateTblId
)
{
    VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;

    *pulStateTblId = NAS_ESM_ILL_STATETAL_INDEX;

    if (ulPti == NAS_ESM_PTI_RESERVED_VALUE)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE, ESM_VERIFY_CN_MSG_VALUE_INVALID, ulPti);
        return NAS_ESM_CAUSE_INVALID_PTI_VALUE;
    }

    if (ulPti == NAS_ESM_PTI_UNASSIGNED_VALUE)
    {
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* 根据PTI查找到动态表Index */
    if(NAS_ESM_SUCCESS != NAS_ESM_QueryStateTblIndexByPti((VOS_UINT8)ulPti, &ulStateTblId))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE, ESM_VERIFY_CN_MSG_PTI_MISMATCH, ulPti);
        return NAS_ESM_CAUSE_PTI_MISMATCH;
    }

    *pulStateTblId = ulStateTblId;
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateEpsbIdInActMsg
 Description     : 对缺省承载激活请求或专有承载激活请求消息
                   中的承载号进行合法性检测
 Input           : ulEpsbId-------------------------承载号
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-5-14  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateEpsbIdInActMsg
(
    VOS_UINT8                           ucEpsbId
)
{
    if((ucEpsbId < NAS_ESM_MIN_EPSB_ID)||(ucEpsbId > NAS_ESM_MAX_EPSB_ID))
    {
        return NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateEpsbIdInRejOrInfoMsg
 Description     : 对网侧拒绝或ESM INFO消息中的承载号进行合法性检测
 Input           : ulEpsbId-------------------------承载号
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-5-14  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateEpsbIdInRejOrInfoMsg
(
    VOS_UINT8                           ucEpsbId
)
{
    if(ucEpsbId != NAS_ESM_UNASSIGNED_EPSB_ID)
    {
        return NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateEpsbIdInModOrDeactMsg
 Description     : 对承载修改或承载去激活消息中的承载号进行合法性检测
 Input           : ulEpsbId-------------------------承载号
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-14  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateEpsbIdInModOrDeactMsg
(
    VOS_UINT8                           ucEpsbId
)
{
    if(NAS_ESM_BEARER_STATE_ACTIVE != NAS_ESM_GetBearCntxtState(ucEpsbId))
    {
        return NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateLinkedEpsbId
 Description     : 对关联承载号进行合法性检测
 Input           : ucLinkedEpsbId-------------------------关联承载号
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-5-14  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateLinkedEpsbId
(
    VOS_UINT8                           ucLinkedEpsbId
)
{
    VOS_UINT32                          ulStateTblIndex  = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    if((NAS_ESM_BEARER_STATE_ACTIVE != NAS_ESM_GetBearCntxtState(ucLinkedEpsbId))
        || (PS_FALSE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(ucLinkedEpsbId))))
    {
        return NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY;
    }

    /*Linked EPS Bearer正处于PDN DISCONNECT过程中，直接返回ERROR，此条消息不处理*/
    if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ucLinkedEpsbId,&ulStateTblIndex))
    {
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        if(NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REQ == pstStateAddr->stNwMsgRecord.enEsmCnMsgType)
        {
            /*打印信息*/
            NAS_ESM_NORM_LOG("NAS_ESM_ValidateLinkedEpsbId:NORMAL:Link Bearer In Procedure of PDN DISCONNECT !");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ValidateLinkedEpsbId_ENUM, 1);

            return NAS_ESM_CAUSE_ERROR;
        }
    }

    return NAS_ESM_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_CreatePfPVListInBearCreateTft
 Description     : 当TAD码为CREATE TFT时，形成packet filter优先级验证列表
 Input           : pstNwMsg---------------------译码后的空口消息指针
 Output          : pucPfNum---------------------packet filter数
                   pstPfPVList------------------优先级验证列表首地址
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-5-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_CreatePfPVListInBearCreateTft
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg,
    VOS_UINT8                          *pucPfNum,
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    const NAS_ESM_CONTEXT_TFT_STRU     *pstPacketFilter = VOS_NULL_PTR;

    for (ulCnt = NAS_ESM_NULL; ulCnt < pstNwMsg->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        pstPacketFilter = &pstNwMsg->stTadInfo.astSdfPfInfo[ulCnt];
        pstPfPVList[*pucPfNum].ucEpsbId = pstNwMsg->ucEpsbId;
        pstPfPVList[*pucPfNum].ucPfId = pstPacketFilter->ucNwPacketFilterId;
        pstPfPVList[*pucPfNum].ucPrecedence = pstPacketFilter->ucPrecedence;
        (*pucPfNum)++;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_CreatePfPVListInBearAddOrReplaceFilter
 Description     : 当TAD码为Add Packter filter或Replace packet filter时，
                   形成packet filter优先级验证列表
 Input           : pstNwMsg---------------------译码后的空口消息指针
 Output          : pucPfNum---------------------packet filter数
                   pstPfPVList------------------优先级验证列表首地址
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951      2010-5-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_CreatePfPVListInBearAddOrReplaceFilter
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg,
    VOS_UINT8                          *pucPfNum,
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList
)
{
    VOS_UINT32                          ulCnt1          = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt2          = NAS_ESM_NULL;
    VOS_UINT8                           ucPfPVNumTmp    = NAS_ESM_NULL;
    VOS_UINT8                           ucPfPVNum       = NAS_ESM_NULL;
    NAS_ESM_PF_PRCDNC_VLDT_STRU         astPfPVListTmp[NAS_ESM_MAX_SDF_PF_NUM];
    const NAS_ESM_CONTEXT_TFT_STRU     *pstPacketFilter = VOS_NULL_PTR;

    NAS_ESM_MEM_SET_S(  astPfPVListTmp,
                        sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU)*NAS_ESM_MAX_SDF_PF_NUM,
                        0,
                        sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU)*NAS_ESM_MAX_SDF_PF_NUM);


    /* 获取此承载下packet filter优先级验证列表 */
    NAS_ESM_GetPfPrecedenceValidateListInBearer(pstNwMsg->ucEpsbId,
                                                &ucPfPVNum,
                                                astPfPVListTmp);

    ucPfPVNumTmp = ucPfPVNum;

    for (ulCnt1 = NAS_ESM_NULL; ulCnt1 < pstNwMsg->stTadInfo.ucSdfPfNum; ulCnt1++)
    {
        pstPacketFilter = &pstNwMsg->stTadInfo.astSdfPfInfo[ulCnt1];

        for (ulCnt2 = NAS_ESM_NULL; ulCnt2 < ucPfPVNumTmp; ulCnt2++)
        {
            if (pstPacketFilter->ucNwPacketFilterId == astPfPVListTmp[ulCnt2].ucPfId)
            {
                astPfPVListTmp[ulCnt2].ucPrecedence = pstPacketFilter->ucPrecedence;
                break;
            }
        }

        if (ulCnt2 >= ucPfPVNumTmp)
        {
            astPfPVListTmp[ucPfPVNum].ucEpsbId = pstNwMsg->ucEpsbId;
            astPfPVListTmp[ucPfPVNum].ucPfId = pstPacketFilter->ucNwPacketFilterId;
            astPfPVListTmp[ucPfPVNum].ucPrecedence = pstPacketFilter->ucPrecedence;
            ucPfPVNum++;
        }
    }

    NAS_ESM_MEM_CPY_S(  &pstPfPVList[*pucPfNum],
                        ucPfPVNum * sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU),
                        astPfPVListTmp,
                        ucPfPVNum * sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU));

    (*pucPfNum) += ucPfPVNum;

}

/*****************************************************************************
 Function Name   : NAS_ESM_CreatePfPrecedenceValidateList
 Description     : 形成packet filter优先级验证列表
 Input           : ulEpsbId---------------------承载号
 Output          : pucPfNum---------------------packet filter数
                   pstPfPVList------------------优先级验证列表首地址
 Return          : VOS_UINT32

 History         :
    1.liuwenyu 00143951      2010-5-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_CreatePfPrecedenceValidateListInPdn
(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT8                          *pucPfNum,
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    VOS_UINT8                           aucEpsbId[NAS_ESM_MAX_EPSB_NUM] = {0};
    VOS_UINT8                           ucEpsBearNum    = NAS_ESM_NULL;

    *pucPfNum = NAS_ESM_NULL;

    /* 获取某PDN下的所有承载号 */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetAllEpsBearerInPdn((VOS_UINT8)ulEpsbId,
                                                        &ucEpsBearNum,
                                                        aucEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CreatePfPrecedenceValidateListInPdn:NAS_ESM_GetAllEpsBearerInPdn failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CreatePfPrecedenceValidateListInPdn_ENUM, LNAS_FAIL);
        return NAS_ESM_FAILURE;
    }

    /* 获得同一PDN下的其他承载的packet filter优先级列表 */
    for (ulCnt= NAS_ESM_NULL; ulCnt < ucEpsBearNum; ulCnt++)
    {

        /* 获取此承载下packet filter优先级验证列表 */
        NAS_ESM_GetPfPrecedenceValidateListInBearer(aucEpsbId[ulCnt],
                                                    pucPfNum,
                                                    pstPfPVList);
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftInActDedictMsg
 Description     : 对专有承载激活请求消息中的TFT进行合法性检测
 Input           : pstTft-------------------------TFT指针
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-5-14  Draft Enact
    2.sunjitan 00193151   2015-04-25 Modify
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftInActDedictMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg,
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_ENCODE_INFO_STRU              stEncodeInfo = { NAS_ESM_NULL };
    VOS_UINT32                            ulIndex      = 0;
    APP_ESM_TRANSFER_DIRECTION_ENUM_UINT8 enDirection  = APP_ESM_TRANSFER_DIRECTION_BUTT;

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ucPti       = pstNwMsg->ucPti;
    stEncodeInfo.ulEpsbId    = (VOS_UINT32)pstNwMsg->ucEpsbId;

    if (NAS_ESM_TFT_OP_TYPE_CREATE_TFT != pstNwMsg->stTadInfo.enTftOpType)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_VERIFY_CN_MSG_ACT_DEDIC_OP_NOT_CREATE_TFT,
                                        pstNwMsg->stTadInfo.enTftOpType);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftInActDedictMsg_ENUM, 1);

        stEncodeInfo.ucESMCau = NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
        NAS_ESM_ActDediBearFailProc(&stEncodeInfo, ulStateTblIndex);
        return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
    }

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        for(ulIndex = 0; ulIndex < pstNwMsg->stTadInfo.ucSdfPfNum; ulIndex++)
        {
            enDirection = pstNwMsg->stTadInfo.astSdfPfInfo[ulIndex].enDirection;

            /* 存在上行PF，则跳出循环 */
            if((APP_ESM_TRANSFER_DIRECTION_UPLINK == enDirection)
                ||(APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK == enDirection))
            {
                break;
            }
        }

        /* 如果没有上行PF，则认为语义错误 */
        if(ulIndex >= pstNwMsg->stTadInfo.ucSdfPfNum)
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_VERIFY_CN_NO_UPLINK_PF,
                                            pstNwMsg->stTadInfo.ucSdfPfNum);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftInActDedictMsg_ENUM, 2);
            stEncodeInfo.ucESMCau = NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER;
            NAS_ESM_ActDediBearFailProc(&stEncodeInfo, ulStateTblIndex);
            return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER;
        }
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftInModMsg
 Description     : 对承载修改请求消息中的TFT进行合法性检测
 Input           : pstNwMsg-------------------------译码后的空口消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-14  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_ValidateTftInModMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg,
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ucPti       = pstNwMsg->ucPti;
    stEncodeInfo.ulEpsbId    = (VOS_UINT32)pstNwMsg->ucEpsbId;

    if (NAS_ESM_SUCCESS != NAS_ESM_ValidateTftOpInModMsg(pstNwMsg,&stEncodeInfo,ulStateTblIndex))
    {
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ComPareQosRate
 Description     : 比较UINT32数的大小
 Input           : None
 Output          : None
 Return          : NAS_ESM_COMPARE_RESULT_ENUM_UINT8

 History         :
    1.lihong 00150010      2009-6-17  Draft Enact

*****************************************************************************/
NAS_ESM_COMPARE_RESULT_ENUM_UINT8 NAS_ESM_ComPareQosRate
(
    VOS_UINT32 ulData1,
    VOS_UINT32 ulData2
)
{
   if(ulData1 > ulData2)
   {
        return NAS_ESM_COMPARE_RESULT_BIG;
   }
   else if(ulData1 == ulData2)
   {
        return NAS_ESM_COMPARE_RESULT_EQUAL;
   }
   else
   {
        return NAS_ESM_COMPARE_RESULT_SMALL;
   }
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsEpsQosEqual
 Description     : 判断QOS是否相同
 Input           : enUlMaxRateComRslt------------上行最大速率比较结果
                   enDlMaxRateComRslt------------下行最大速率比较结果
                   enULGMaxRateComRslt-----------上行保证速率比较结果
                   enDLGMaxRateComRslt-----------下行保证速率比较结果
 Output          : None
 Return          : NAS_ESM_COMPARE_RESULT_ENUM_UINT8

 History         :
    1.lihong 00150010      2010-06-01  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsEpsQosEqual
(
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enUlMaxRateComRslt,
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enDlMaxRateComRslt,
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enULGMaxRateComRslt,
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enDLGMaxRateComRslt
)
{
    /* 如果都等，则返回PS_TRUE */
    if((NAS_ESM_COMPARE_RESULT_EQUAL == enUlMaxRateComRslt)
        && (NAS_ESM_COMPARE_RESULT_EQUAL == enDlMaxRateComRslt)
        && (NAS_ESM_COMPARE_RESULT_EQUAL == enULGMaxRateComRslt)
        && (NAS_ESM_COMPARE_RESULT_EQUAL == enDLGMaxRateComRslt))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsEpsQosBiggerOrEqual
 Description     : 判断QOS是否为大于或等于
 Input           : enUlMaxRateComRslt------------上行最大速率比较结果
                   enDlMaxRateComRslt------------下行最大速率比较结果
                   enULGMaxRateComRslt-----------上行保证速率比较结果
                   enDLGMaxRateComRslt-----------下行保证速率比较结果
 Output          : None
 Return          : NAS_ESM_COMPARE_RESULT_ENUM_UINT8

 History         :
    1.lihong 00150010      2010-06-01  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsEpsQosBiggerOrEqual
(
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enUlMaxRateComRslt,
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enDlMaxRateComRslt,
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enULGMaxRateComRslt,
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enDLGMaxRateComRslt
)
{
    /* 如果都大或者等于，则返回PS_TRUE */
    if(((NAS_ESM_COMPARE_RESULT_BIG == enUlMaxRateComRslt) || (NAS_ESM_COMPARE_RESULT_EQUAL == enUlMaxRateComRslt))
        && ((NAS_ESM_COMPARE_RESULT_BIG == enDlMaxRateComRslt) || (NAS_ESM_COMPARE_RESULT_EQUAL == enDlMaxRateComRslt))
        && ((NAS_ESM_COMPARE_RESULT_BIG == enULGMaxRateComRslt) || (NAS_ESM_COMPARE_RESULT_EQUAL == enULGMaxRateComRslt))
        && ((NAS_ESM_COMPARE_RESULT_BIG == enDLGMaxRateComRslt) || (NAS_ESM_COMPARE_RESULT_EQUAL == enDLGMaxRateComRslt)))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsEpsQosSmallerOrEqual
 Description     : 判断QOS是否为小于或等于
 Input           : enUlMaxRateComRslt------------上行最大速率比较结果
                   enDlMaxRateComRslt------------下行最大速率比较结果
                   enULGMaxRateComRslt-----------上行保证速率比较结果
                   enDLGMaxRateComRslt-----------下行保证速率比较结果
 Output          : None
 Return          : NAS_ESM_COMPARE_RESULT_ENUM_UINT8

 History         :
    1.lihong 00150010      2010-06-01  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsEpsQosSmallerOrEqual
(
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enUlMaxRateComRslt,
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enDlMaxRateComRslt,
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enULGMaxRateComRslt,
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enDLGMaxRateComRslt
)
{
    /* 如果都小，则返回PS_TRUE */
    if(((NAS_ESM_COMPARE_RESULT_SMALL == enUlMaxRateComRslt) || (NAS_ESM_COMPARE_RESULT_EQUAL == enUlMaxRateComRslt))
        && ((NAS_ESM_COMPARE_RESULT_SMALL == enDlMaxRateComRslt) || (NAS_ESM_COMPARE_RESULT_EQUAL == enDlMaxRateComRslt))
        && ((NAS_ESM_COMPARE_RESULT_SMALL == enULGMaxRateComRslt) || (NAS_ESM_COMPARE_RESULT_EQUAL == enULGMaxRateComRslt))
        && ((NAS_ESM_COMPARE_RESULT_SMALL == enDLGMaxRateComRslt) || (NAS_ESM_COMPARE_RESULT_EQUAL == enDLGMaxRateComRslt)))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ComPareQos
 Description     : 比较QOS的大小
 Input           : None
 Output          : None
 Return          : NAS_ESM_COMPARE_RESULT_ENUM_UINT8

 History         :
    1.lihong 00150010      2009-6-17  Draft Enact

*****************************************************************************/
NAS_ESM_COMPARE_RESULT_ENUM_UINT8 NAS_ESM_CompareEpsQos
(
    const APP_ESM_EPS_QOS_INFO_STRU                      *pstEpsQoSInfo1,
    const APP_ESM_EPS_QOS_INFO_STRU                      *pstEpsQoSInfo2
)
{
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enUlMaxRateComRslt;
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enDlMaxRateComRslt;
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enULGMaxRateComRslt;
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8   enDLGMaxRateComRslt;

    /* 比较UlMaxRate */
    enUlMaxRateComRslt = NAS_ESM_ComPareQosRate(pstEpsQoSInfo1->ulULMaxRate,
                                                pstEpsQoSInfo2->ulULMaxRate);

    /* 比较DlMaxRate */
    enDlMaxRateComRslt = NAS_ESM_ComPareQosRate(pstEpsQoSInfo1->ulDLMaxRate,
                                                pstEpsQoSInfo2->ulDLMaxRate);

    /* 比较UlGMaxRate */
    enULGMaxRateComRslt = NAS_ESM_ComPareQosRate(pstEpsQoSInfo1->ulULGMaxRate,
                                                pstEpsQoSInfo2->ulULGMaxRate);

    /* 比较DlGMaxRate */
    enDLGMaxRateComRslt = NAS_ESM_ComPareQosRate(pstEpsQoSInfo1->ulDLGMaxRate,
                                                pstEpsQoSInfo2->ulDLGMaxRate);

    /* 如果都等，则返回NAS_ESM_COMPARE_RESULT_EQUAL */
    if(PS_TRUE == NAS_ESM_IsEpsQosEqual(enUlMaxRateComRslt, enDlMaxRateComRslt,
                                        enULGMaxRateComRslt, enDLGMaxRateComRslt))
    {
        return NAS_ESM_COMPARE_RESULT_EQUAL;
    }

    /* 如果各项速率都是小于或者等于，则返回NAS_ESM_COMPARE_RESULT_SMALL */
    if(PS_TRUE == NAS_ESM_IsEpsQosSmallerOrEqual(enUlMaxRateComRslt, enDlMaxRateComRslt,
                                                 enULGMaxRateComRslt, enDLGMaxRateComRslt))
    {
        return NAS_ESM_COMPARE_RESULT_SMALL;
    }

    /* 如果各项速率都是大于或者等于，则返回NAS_ESM_COMPARE_RESULT_BIG */
    if(PS_TRUE == NAS_ESM_IsEpsQosBiggerOrEqual(enUlMaxRateComRslt, enDlMaxRateComRslt,
                                                enULGMaxRateComRslt, enDLGMaxRateComRslt))
    {
        return NAS_ESM_COMPARE_RESULT_BIG;
    }

    return NAS_ESM_COMPARE_RESULT_OTHER;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateQos
 Description     : 验证QoS的语义是否正确
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong 00150010      2009-6-17  Draft Enact
    2.lihong00150010       2010-02-10 Modify

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_ValidateEpsQos
(
    NAS_ESM_TFT_OP_TYPE_ENUM_UINT8                           enTftOpType,
    const NAS_ESM_CONTEXT_LTE_QOS_STRU                      *pstEpsQoSInfoOld,
    const NAS_ESM_CONTEXT_LTE_QOS_STRU                      *pstEpsQoSInfoNew
)
{
    NAS_ESM_COMPARE_RESULT_ENUM_UINT8                   enQosCompareResult;

    enQosCompareResult = NAS_ESM_CompareEpsQos(&pstEpsQoSInfoOld->stQosInfo,
                                               &pstEpsQoSInfoNew->stQosInfo);

    if(NAS_ESM_TFT_OP_TYPE_ADD_FILTER == enTftOpType)
    {
        /* 若是添加SDF，则当前保存的QOS应小于或者等于收到消息中的QOS */
        if ((NAS_ESM_COMPARE_RESULT_SMALL == enQosCompareResult)
          ||(NAS_ESM_COMPARE_RESULT_EQUAL == enQosCompareResult))
        {
            return NAS_ESM_CAUSE_SUCCESS;
        }
        else
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPS_QOS_IE, ESM_VERIFY_CN_ADD_FILTER_NOT_INCREASE, enQosCompareResult);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateEpsQos_ENUM, 1);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }
    else if (NAS_ESM_TFT_OP_TYPE_DELETE_FILTER == enTftOpType)
    {
        /* 若是删除SDF，则当前保存的QOS应大于或者等于收到消息中的QOS */
        if ((NAS_ESM_COMPARE_RESULT_BIG == enQosCompareResult)
          ||(NAS_ESM_COMPARE_RESULT_EQUAL == enQosCompareResult))
        {
            return NAS_ESM_CAUSE_SUCCESS;
        }
        else
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPS_QOS_IE, ESM_VERIFY_CN_DEL_FILTER_NOT_DECREASE, enQosCompareResult);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateEpsQos_ENUM, 2);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }
    else
    {
        return NAS_ESM_CAUSE_SUCCESS;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsNwActBearerWithOnlyOneCid
 Description     : 判断只有一个关联CID，且这个关联CID也是网侧主动激活的
 Input           : ucEpsBearer--承载号
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2015-01-20  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsNwActBearerWithOnlyOneCid
(
    VOS_UINT32                      ucEpsBearer
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU    *pstEpsbCntxtInfo = VOS_NULL_PTR;
    VOS_UINT32                      ulCid = NAS_ESM_NULL;

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucEpsBearer);
    ulCid = NAS_ESM_GetCid(ucEpsBearer);

    /* 判断承载关联CID有且只有一个，且网侧主动激活的CID */
    if (pstEpsbCntxtInfo->ulBitCId == ((VOS_UINT32)NAS_ESM_BIT_0 << ulCid))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}


/*****************************************************************************
 Function Name   : NAS_ESM_ValidateQosInModMsg
 Description     : 对承载修改请求中的QOS信息进行合法性检测
 Input           : pstMsgIE -- 译码后的网络消息
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2009-12-2  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateQosInModMsg
(
    const NAS_ESM_NW_MSG_STRU               *pstMsgIE,
    const NAS_ESM_EPSB_CNTXT_INFO_STRU      *pstEpsbCntxtInfo
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause       = NAS_ESM_CAUSE_SUCCESS;

    /* 如果不带QOS */
    if (NAS_ESM_OP_FALSE == pstMsgIE->bitOpEpsQos)
    {
        /* 缺省承载可以不带Qos */
        if(PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(pstMsgIE->ucEpsbId)))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ValidateQosInModMsg:INFO:Default Bearer No QoS Information !");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ValidateQosInModMsg_ENUM, 1);
            return NAS_ESM_CAUSE_SUCCESS;
        }

        /* 当TAD码为NO OPERATION时，必须携带QOS；当承载为GBR承载，且TAD码为ADD SDF,
           则必须携带QOS */
        if (((NAS_ESM_OP_TRUE == pstMsgIE->bitOpTadInfo)
          && (NAS_ESM_TFT_OP_TYPE_NO_OP == pstMsgIE->stTadInfo.enTftOpType)))

        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPS_QOS_IE, ESM_VERIFY_CN_NO_OPERATION_NO_QOS, pstMsgIE->stTadInfo.enTftOpType);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateQosInModMsg_ENUM, 2);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
        else
        {
            return NAS_ESM_CAUSE_SUCCESS;
        }
    }

    /* 判断修改后的Qos是否合理 */
    if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))

    {
        /* 网侧注册修改承载，且修改的承载只有一个关联的CID，且这个关联的CID也是网侧
           主动激活的，这种场景下直接返回SUCCESS */
        if ((NAS_ESM_PTI_UNASSIGNED_VALUE == pstMsgIE->ucPti)
            && (PS_TRUE == NAS_ESM_IsNwActBearerWithOnlyOneCid(pstMsgIE->ucEpsbId)))
        {
            return NAS_ESM_CAUSE_SUCCESS;
        }
        enEsmCause = NAS_ESM_ValidateEpsQos(pstMsgIE->stTadInfo.enTftOpType,
                                            &pstEpsbCntxtInfo->stEpsQoSInfo,
                                            &pstMsgIE->stSdfQosInfo);
        if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_ValidateQosInModMsg:WARNING: Qos invalid!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateQosInModMsg_ENUM, 3);
            return enEsmCause;
        }
    }

    return NAS_ESM_CAUSE_SUCCESS;
}



/*****************************************************************************
 Function Name   : NAS_ESM_ValidateActDefltEpsbReqMsg
 Description     : 对激活缺省承载请求消息进行合法性检测
 Input           : pstNwMsg-------------------------译码后的空口消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-12  Draft Enact

*****************************************************************************/
static VOS_UINT32  NAS_ESM_ValidateActDefltEpsbReqMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause = NAS_ESM_NULL;

    /* 检测PTI，PTI不为0，不为RESERVED，且通过此PTI能检索到状态表
       中的记录，否则回复拒绝消息 */
    enEsmCause = NAS_ESM_ValidatePtiInActDefltOrInfoOrRejMsg(pstNwMsg->ucPti);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_LOG1("NAS_ESM_ValidateActDefltEpsbReqMsg:WARN:Validate Pti failed, cause : ", enEsmCause);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateActDefltEpsbReqMsg_ENUM, 1, enEsmCause);
        NAS_ESM_ProcNwMsgForIllegalPti(pstNwMsg, enEsmCause);
        return NAS_ESM_MSG_HANDLED;
    }

    /* 检测承载号范围，必须位于5-15之间，否则回复拒绝消息 */
    enEsmCause = NAS_ESM_ValidateEpsbIdInActMsg(pstNwMsg->ucEpsbId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE, ESM_VERIFY_CN_MSG_VALUE_INVALID, pstNwMsg->ucEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateActDefltEpsbReqMsg_ENUM, 2, enEsmCause);
        NAS_ESM_ProcNwMsgForIllegalEpsbId(pstNwMsg);
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateActDedictEpsbReqMsg
 Description     : 对激活专有承载请求消息进行合法性检测
 Input           : pstNwMsg-------------------------译码后的空口消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-12  Draft Enact

*****************************************************************************/
static VOS_UINT32  NAS_ESM_ValidateActDedictEpsbReqMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause      = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblId    = NAS_ESM_NULL;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /* 检测PTI，PTI不为RESERVED，当PTI不为0时，通过此PTI能检索到状态表
       中的记录，否则回复拒绝消息*/
    enEsmCause = NAS_ESM_ValidatePtiInActDedictOrModOrDeactOrStatusMsg(pstNwMsg->ucPti,
                                                                       &ulStateTblId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_LOG1("NAS_ESM_ValidateActDedictEpsbReqMsg:WARN:Validate Pti failed, cause : ", enEsmCause);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateActDedictEpsbReqMsg_ENUM, 1, enEsmCause);
        NAS_ESM_ProcNwMsgForIllegalPti(pstNwMsg, enEsmCause);
        return NAS_ESM_MSG_HANDLED;
    }

    /* 检测承载号范围，必须位于5-15之间，否则回复拒绝消息 */
    enEsmCause = NAS_ESM_ValidateEpsbIdInActMsg(pstNwMsg->ucEpsbId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE,
                                        ESM_VERIFY_CN_MSG_VALUE_INVALID,
                                        pstNwMsg->ucEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateActDedictEpsbReqMsg_ENUM, 2, enEsmCause);
        NAS_ESM_ProcNwMsgForIllegalEpsbId(pstNwMsg);
        return NAS_ESM_MSG_HANDLED;
    }

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ucPti       = pstNwMsg->ucPti;
    stEncodeInfo.ulEpsbId    = (VOS_UINT32)pstNwMsg->ucEpsbId;

    /* 检测关联承载号范围，必须位于5-15之间，必须为激活的缺省承载，否则
       回复拒绝消息；若此缺省承载处于PDN DISCONNECT流程中，则丢弃此消息 */
    enEsmCause = NAS_ESM_ValidateLinkedEpsbId(pstNwMsg->ucLinkedEpsbId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE,
                                        ESM_VERIFY_CN_MSG_VALUE_INVALID,
                                        pstNwMsg->ucEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateActDedictEpsbReqMsg_ENUM, 3, enEsmCause);
        stEncodeInfo.ucESMCau = enEsmCause;
        NAS_ESM_ActDediBearFailProc(&stEncodeInfo, ulStateTblId);
        return NAS_ESM_MSG_HANDLED;
    }

    /* 检测TFT */
    if (NAS_ESM_SUCCESS != NAS_ESM_ValidateTftInActDedictMsg(pstNwMsg,
                                                             ulStateTblId))
    {
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateModEpsbReqMsg
 Description     : 对承载修改请求消息进行合法性检测
 Input           : pstNwMsg-------------------------译码后的空口消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-12  Draft Enact

*****************************************************************************/
static VOS_UINT32  NAS_ESM_ValidateModEpsbReqMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblId        = NAS_ESM_NULL;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstTmpEpsbCntxtInfo = VOS_NULL_PTR;


    /* 检测PTI，PTI不为RESERVED，当PTI不为0时，通过此PTI能检索到状态表
          中的记录，否则回复拒绝消息*/
    enEsmCause = NAS_ESM_ValidatePtiInActDedictOrModOrDeactOrStatusMsg(pstNwMsg->ucPti,
                                                                       &ulStateTblId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_LOG1("NAS_ESM_ValidateModEpsbReqMsg:WARN:Validate Pti failed, cause : ", enEsmCause);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateModEpsbReqMsg_ENUM, 1, enEsmCause);
        NAS_ESM_ProcNwMsgForIllegalPti(pstNwMsg, enEsmCause);
        return NAS_ESM_MSG_HANDLED;
    }

    /* 检测承载号范围，必须位于5-15之间，必须为激活态，否则回复拒绝消息 */
    enEsmCause = NAS_ESM_ValidateEpsbIdInModOrDeactMsg(pstNwMsg->ucEpsbId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE, ESM_VERIFY_CN_MSG_VALUE_INVALID, pstNwMsg->ucEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateModEpsbReqMsg_ENUM, 2, enEsmCause);
        NAS_ESM_ProcNwMsgForIllegalEpsbId(pstNwMsg);
        return NAS_ESM_MSG_HANDLED;
    }

    /*初始化，并填充NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ucPti       = pstNwMsg->ucPti;
    stEncodeInfo.ulEpsbId    = (VOS_UINT32)pstNwMsg->ucEpsbId;

    /* 检测此消息是否与PDN DISCONNECT流程冲突，若是则丢弃此消息 */
    pstTmpEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstNwMsg->ucEpsbId);
    if(NAS_ESM_BEARER_TYPE_DEDICATED == pstTmpEpsbCntxtInfo->enBearerCntxtType)
    {
        enEsmCause = NAS_ESM_ValidateLinkedEpsbId((VOS_UINT8)pstTmpEpsbCntxtInfo->ulLinkedEpsbId);
    }
    else
    {
        enEsmCause = NAS_ESM_ValidateLinkedEpsbId(pstNwMsg->ucEpsbId);
    }

    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE, ESM_VERIFY_CN_MSG_IN_PDN_DISCONN_PROCEDURE, pstNwMsg->ucEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateModEpsbReqMsg_ENUM, 3, enEsmCause);
        stEncodeInfo.ucESMCau = enEsmCause;
        NAS_ESM_BearModFailProc(&stEncodeInfo, ulStateTblId);
        return NAS_ESM_MSG_HANDLED;
    }

    /* 检测TFT */
    if (NAS_ESM_SUCCESS != NAS_ESM_ValidateTftInModMsg(pstNwMsg, ulStateTblId))
    {
        return NAS_ESM_MSG_HANDLED;
    }

    /* 检测QOS */
    enEsmCause = NAS_ESM_ValidateQosInModMsg(   pstNwMsg,
                                                NAS_ESM_GetEpsbCntxtInfoAddr(pstNwMsg->ucEpsbId));
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_LOG1("NAS_ESM_ValidateActDedictEpsbReqMsg:WARN:NAS_ESM_ValidateQosInModMsg failed! ", enEsmCause);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateModEpsbReqMsg_ENUM, 4, enEsmCause);
        stEncodeInfo.ucESMCau = enEsmCause;
        NAS_ESM_BearModFailProc(&stEncodeInfo, ulStateTblId);
        return NAS_ESM_MSG_HANDLED;
    }



    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateDeactEpsbReqMsg
 Description     : 对承载去激活请求消息进行合法性检测
 Input           : pstNwMsg-------------------------译码后的空口消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-12  Draft Enact

*****************************************************************************/
static VOS_UINT32  NAS_ESM_ValidateDeactEpsbReqMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause      = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblId    = NAS_ESM_NULL;

    /* 检测PTI，当PTI不为0时，且通过此PTI不能检索到状态表记录，或者若PTI为
       RESERVED，则丢弃此消息*/
    enEsmCause = NAS_ESM_ValidatePtiInActDedictOrModOrDeactOrStatusMsg( pstNwMsg->ucPti,
                                                                        &ulStateTblId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_LOG1("NAS_ESM_ValidateDeactEpsbReqMsg:WARN:Validate Pti failed, cause : ", enEsmCause);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateDeactEpsbReqMsg_ENUM, 1, enEsmCause);
        /* UE发起承载释放，由于时序问题接入层提前把承载释放掉了，导致动态表里找不到对应的PTI，
           所以在收到网侧去激活时由于PTI对应不上，所以没有给网侧回复去激活结果，
           为了提高网络兼容性，不直接return，需要给网侧回复结果 */
        /* return NAS_ESM_MSG_HANDLED; */
    }

    /* 检测承载号范围，必须位于5-15之间，必须为激活态，否则直接回复ACCEPT消息 */
    enEsmCause = NAS_ESM_ValidateEpsbIdInModOrDeactMsg(pstNwMsg->ucEpsbId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE, ESM_VERIFY_CN_MSG_VALUE_INVALID, pstNwMsg->ucEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateDeactEpsbReqMsg_ENUM, 2, enEsmCause);
        NAS_ESM_ProcNwMsgForIllegalEpsbId(pstNwMsg);
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateNwRejMsg
 Description     : 对网侧拒绝消息进行合法性检测
 Input           : pstNwMsg-------------------------译码后的空口消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-12  Draft Enact

*****************************************************************************/
static VOS_UINT32  NAS_ESM_ValidateNwRejMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause = NAS_ESM_NULL;

    /* 检测PTI，PTI不为0，不为RESERVED，通过此PTI能检索到状态表
       中的记录，否则丢弃此消息 */
    enEsmCause = NAS_ESM_ValidatePtiInActDefltOrInfoOrRejMsg(pstNwMsg->ucPti);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_LOG1("NAS_ESM_ValidateNwRejMsg:WARN:Validate Pti failed, cause : ", enEsmCause);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateNwRejMsg_ENUM, 1, enEsmCause);
        return NAS_ESM_MSG_HANDLED;
    }

    /* 如果是GCF测试，需要检查承载号是否为0*/
    if (PS_SUCC == LPS_OM_IsTestMode())
    {
        /* 检测承载号，必须为0，否则丢弃此消息 */
        enEsmCause = NAS_ESM_ValidateEpsbIdInRejOrInfoMsg(pstNwMsg->ucEpsbId);
        if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE,
                                            ESM_VERIFY_CN_MSG_CN_REJ_EPSBID_NOT_ZERO,
                                            pstNwMsg->ucEpsbId);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateNwRejMsg_ENUM, 2, enEsmCause);
            return NAS_ESM_MSG_HANDLED;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateEsmInfoReqMsg
 Description     : 对ESM INFO请求消息进行合法性检测
 Input           : pstNwMsg-------------------------译码后的空口消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-12  Draft Enact

*****************************************************************************/
static VOS_UINT32  NAS_ESM_ValidateEsmInfoReqMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause = NAS_ESM_NULL;

    /* 检测PTI，PTI若为0，或者为RESERVED，则直接丢弃此消息；若通过此PTI不能
       检索到状态表中的记录，则回复ESM STATUS消息 */
    enEsmCause = NAS_ESM_ValidatePtiInActDefltOrInfoOrRejMsg(pstNwMsg->ucPti);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_LOG1("NAS_ESM_ValidateEsmInfoReqMsg:WARN:Validate Pti failed, cause : ", enEsmCause);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateEsmInfoReqMsg_ENUM, 1, enEsmCause);
        if (enEsmCause == NAS_ESM_CAUSE_PTI_MISMATCH)
        {
            NAS_ESM_ProcNwMsgForIllegalPti(pstNwMsg, enEsmCause);
        }
        return NAS_ESM_MSG_HANDLED;
    }

    /* 检测承载号，必须为0，否则回复ESM STATUS消息 */
    enEsmCause = NAS_ESM_ValidateEpsbIdInRejOrInfoMsg(pstNwMsg->ucEpsbId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE,
                                        ESM_VERIFY_CN_MSG_ESM_INFO_REQ_EPSBID_NOT_ZERO,
                                        pstNwMsg->ucEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateEsmInfoReqMsg_ENUM, 2, enEsmCause);
        NAS_ESM_ProcNwMsgForIllegalEpsbId(pstNwMsg);
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateEsmStatusMsg
 Description     : 对ESM STATUS消息进行合法性检测
 Input           : pstNwMsg-------------------------译码后的空口消息指针
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-12  Draft Enact

*****************************************************************************/
static VOS_UINT32  NAS_ESM_ValidateEsmStatusMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause      = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblId    = NAS_ESM_NULL;

    /* 检测PTI，PTI为RESERVED，或者当PTI不为0，且通过此PTI不能检索到状态表
       中的记录，则丢弃此消息 */
    enEsmCause = NAS_ESM_ValidatePtiInActDedictOrModOrDeactOrStatusMsg( pstNwMsg->ucPti,
                                                                        &ulStateTblId);
    if (enEsmCause != NAS_ESM_CAUSE_SUCCESS)
    {
        NAS_ESM_LOG1("NAS_ESM_ValidateEsmStatusMsg:WARN:Validate Pti failed, cause : ", enEsmCause);
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidateEsmStatusMsg_ENUM, LNAS_ENTRY, enEsmCause);
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_UpdateStatetblNwInitProcedure
 Description     : 网络主动发起的流程，获取动态表和Cid
 Input           : pRcvMsg       -- 译码后的空口消息
 Output          : pulStateTblId -- 动态表索引
 Return          : NAS_ESM_MSG_HANDLED -- 处理失败
                   NAS_ESM_SUCCESS     -- 处理成功
 History         :
    1.liuwenyu 00143951      2010-10-26  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_UpdateStatetblNwInitProcedure
(
    const NAS_ESM_NW_MSG_STRU           *pRcvMsg,
    VOS_UINT32                          *pulStateTblId
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    VOS_UINT32                          ulCId               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_UpdateStatetblNwInitProcedure is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_UpdateStatetblNwInitProcedure_ENUM, LNAS_ENTRY);

    ulRslt = NAS_ESM_QuerySdfId(pRcvMsg,&ulCId);

    if ((NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_EQUAL_CID != ulRslt)
     && (NAS_ESM_QUERY_CID_RSLT_PART_FOUND_EQUAL_CID != ulRslt))
    {
        ulCId = NAS_ESM_GetCid(pRcvMsg->ucEpsbId);
    }

    if (NAS_ESM_SUCCESS == NAS_ESM_GetStateTblIndexByCid(ulCId,pulStateTblId))
    {
        pstStateAddr = NAS_ESM_GetStateTblAddr(*pulStateTblId);

        /*填写状态表信息，包括承载状态，承载Id，承载类型*/
        pstStateAddr->ulEpsbId = pRcvMsg->ucEpsbId;
        pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(pstStateAddr->ulEpsbId);
        pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(pstStateAddr->ulEpsbId);
        pstStateAddr->ulCid = ulCId;
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_UpdateStatetblNwInitProcedure:WARNING:insufficient resource!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_UpdateStatetblNwInitProcedure_ENUM, 1);

        /*根据消息内容，回复拒绝或忽略*/
        return NAS_ESM_MSG_HANDLED;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgActDedictdEpsbReqWithBearerActived
 Description     : 处理专有承载已经激活后网侧又下发专有承载激活消息, 为了解决:当激活专有
                   承载回复ACP时, 由于某些原因(如底层发生切换)导致ACP消息没有发到网侧,网
                   侧定时器超时会重新发下激活专有承载消息, 由于是网侧重传,这条专有承载激
                   活消息是通过下行直传, 而不是重配置带下来的, 若按以前处理先去激活再激活
                   处理会导致承载激活没有对应的DRB, 从而出现VoLTE电话不通；
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.leixiantiao      2016-01-22  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgActDedictdEpsbReqWithBearerActived
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32                          ulCId               = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    VOS_UINT32                          ulEpsbId         = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    EMM_ESM_INTRA_DATA_IND_STRU        *pMsg                = VOS_NULL_PTR;
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;

    pMsg  = (EMM_ESM_INTRA_DATA_IND_STRU *) pRcvMsg;

    ulCId = NAS_ESM_GetCid(pRcvMsg->stEsmNwMsgIE.ucEpsbId);

    if (NAS_ESM_SUCCESS != NAS_ESM_GetStateTblIndexByCid(ulCId,&ulStateTblIndex))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE, ESM_VERIFY_CN_MSG_STATE_TABLE_FULL, ulCId);
        return;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 填写状态表信息，包括承载状态，承载Id，承载类型 */
    pstStateAddr->ulEpsbId              = pRcvMsg->stEsmNwMsgIE.ucEpsbId;
    pstStateAddr->enBearerCntxtState    = NAS_ESM_GetBearCntxtState(pstStateAddr->ulEpsbId);
    pstStateAddr->enBearerCntxtType     = NAS_ESM_GetBearCntxtType(pstStateAddr->ulEpsbId);
    pstStateAddr->ulCid                 = ulCId;
    pstStateAddr->bitOpNwMsgRecord      = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.ucPti   = pMsg->stEsmNwMsgIE.ucPti;

    /* 取出承载信息 */
    ulEpsbId = (VOS_UINT32)(pMsg->stEsmNwMsgIE.ucEpsbId);
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* 设置承载类型 */
    pstEpsbCntxtInfo->enBearerCntxtType = NAS_ESM_BEARER_TYPE_DEDICATED;

    /* 初始化，并填充NAS_ESM_ENCODE_INFO_STRU */
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_FALSE;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = ulEpsbId;

     /* 保存专有承载激活的上下文信息 */
    NAS_ESM_SaveNwActDedictdEpsbReqInfo(&(pMsg->stEsmNwMsgIE), ulStateTblIndex);

    /* 编码向网侧回复Activate dedicated bearer context accept */
    NAS_ESM_EncodeActDedictdEpsbCntxtAccMsg(stEncodeInfo,
                                            NAS_ESM_GetCurEsmSndNwMsgAddr(),
                                            &ulSndNwMsgLen);

    /* 勾出空口消息 */
    NAS_ESM_SndAirMsgReportInd( NAS_ESM_GetCurEsmSndNwMsgAddr(),
                                ulSndNwMsgLen,
                                NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                ESM_ACT_DEDICT_EPS_BEARER_CNTXT_ACP);

    /* 把空口消息发送给EMM */
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

    /* 转换状态和设置承载属性 */
    NAS_ESM_SetBearCntxtState(stEncodeInfo.ulEpsbId, NAS_ESM_BEARER_STATE_ACTIVE);
    NAS_ESM_SetBearCntxtType(stEncodeInfo.ulEpsbId, NAS_ESM_BEARER_TYPE_DEDICATED);
    NAS_ESM_SetBearCntxtLinkCid(stEncodeInfo.ulEpsbId,pstStateAddr->ulCid);

    /* 关键事件上报 */
    NAS_ESM_SndKeyEventReportInd((OM_PS_KEY_EVENT_ENUM_UINT8)NAS_ESM_EVENT_BEARER_SETUP(stEncodeInfo.ulEpsbId));

    /* 通知RABM修改相应承载信息, 防止出现当前激活专有承载消息内容与之前激活承载消息内容不同 */
    NAS_ESM_SndEsmRabmMdfIndMsg(stEncodeInfo.ulEpsbId,ESM_ERABM_BEARER_RAT_LTE);

    /* 通知SM修改相应承载信息, 防止出现当前激活专有承载消息内容与之前激活承载消息内容不同 */
    NAS_ESM_SndSmEspBearerMdfIndMsg(stEncodeInfo.ulEpsbId);

    NAS_ESM_UpdateBearCntextLinkCid(&(pMsg->stEsmNwMsgIE),
                                    stEncodeInfo.ulEpsbId,
                                    pstStateAddr->ulCid);

    /* 通知APP修改相应承载信息, 防止出现当前激活专有承载消息内容与之前激活承载消息内容不同 */
    NAS_ESM_InformAppEpsBearerModSucc(&(pMsg->stEsmNwMsgIE),
                                      ulStateTblIndex);

    /* 释放状态表资源 */
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

    /* PF优先级冲突处理 */
    NAS_ESM_ProcPfPrecedenceCollision(&(pMsg->stEsmNwMsgIE));

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgActDedictdEpsbReq
 Description     : 处理专有承载激活流程
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgActDedictdEpsbReq
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32                          ulCId               = NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /* 验证空口消息,不验证TFT 优先级冲突的情况 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateActDedictEpsbReqMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgActDedictdEpsbReq: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgActDedictdEpsbReq_ENUM, 1);
        return;
    }

    /* 如果承载已经激活，先本地去激活 */
    if(NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(pRcvMsg->stEsmNwMsgIE.ucEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgActDedictdEpsbReq : release already active bearer!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgActDedictdEpsbReq_ENUM, 2);

        /* 当当前专有承载已经激活又收到网侧的专有承载激活时, 直接保存相应参数, 回复ACP,
           为了解决:当激活专有承载回复ACP时, 由于某些原因(如底层发生切换)导致ACP消息没有
           发到网侧,网侧定时器超时会重新发下激活专有承载消息, 由于是网侧重传,这条专有承载
           激活消息是通过下行直传, 而不是重配置带下来的, 若按以前处理先去激活再激活
           处理会导致承载激活没有对应的DRB, 从而出现VoLTE电话不通；*/
        NAS_ESM_ProcNwMsgActDedictdEpsbReqWithBearerActived(pRcvMsg);
        return;
    }


    /* 处理动态表和Cid */
    if (NAS_ESM_PTI_UNASSIGNED_VALUE == pRcvMsg->stEsmNwMsgIE.ucPti )
    {
        ulCId = NAS_ESM_GetCid(pRcvMsg->stEsmNwMsgIE.ucEpsbId);

        if (NAS_ESM_SUCCESS == NAS_ESM_GetStateTblIndexByCid(ulCId,&ulStateTblIndex))
        {
            pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

            /*填写状态表信息，包括承载状态，承载Id，承载类型*/
            pstStateAddr->ulEpsbId = pRcvMsg->stEsmNwMsgIE.ucEpsbId;
            pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(pstStateAddr->ulEpsbId);
            pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(pstStateAddr->ulEpsbId);
            pstStateAddr->ulCid = ulCId;
        }
        else
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE, ESM_VERIFY_CN_MSG_STATE_TABLE_FULL, ulCId);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgActDedictdEpsbReq_ENUM, 3);
            return;
        }
    }
    else
    {
        if(NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByPti(pRcvMsg->stEsmNwMsgIE.ucPti,
                                                             &ulStateTblIndex))
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE, ESM_VERIFY_CN_MSG_PTI_MISMATCH, pRcvMsg->stEsmNwMsgIE.ucPti);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgActDedictdEpsbReq_ENUM, 4);
            return ;
        }

        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

        /* 处理网侧下发的PTI已分配，但是承载号不同的情况 */
        NAS_ESM_ProcNwMsgActDediBearSamePtiWithDiffEBI(pRcvMsg,ulStateTblIndex,pstStateAddr);

    }

    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwMsgActDedictdEpsbReq(ulStateTblIndex,pRcvMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgModEpsbReq
 Description     : 处理承载修改流程
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgModEpsbReq
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /* 验证空口消息,不验证TFT 优先级冲突的情况 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateModEpsbReqMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgModEpsbReq: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgModEpsbReq_ENUM, 1);
        return;
    }

    /*根据承载ID，检查网络发起的流程与UE发起的流程是否有冲突*/
    if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(pRcvMsg->stEsmNwMsgIE.ucEpsbId,
                                                            &ulStateTblIndex))
    {
        /*网络和UE同时对同一承载进行操作，UE忽略网络的承载修改请求*/
        if(NAS_ESM_PTI_UNASSIGNED_VALUE == pRcvMsg->stEsmNwMsgIE.ucPti )
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE, ESM_VERIFY_CN_UE_CN_OPERATION_COLLISION, pRcvMsg->stEsmNwMsgIE.ucEpsbId);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgModEpsbReq_ENUM, 2);
            return;
        }
    }

    /* 处理动态表和Cid */
    if (NAS_ESM_PTI_UNASSIGNED_VALUE == pRcvMsg->stEsmNwMsgIE.ucPti )
    {
        ulRslt = NAS_ESM_UpdateStatetblNwInitProcedure(&pRcvMsg->stEsmNwMsgIE,
                                                       &ulStateTblIndex);
        if (NAS_ESM_MSG_HANDLED == ulRslt)
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE, ESM_VERIFY_CN_UPDATE_STATE_TABLE_FAIL, pRcvMsg->stEsmNwMsgIE.ucPti);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgModEpsbReq_ENUM, 3);
            return ;
        }
    }
    else
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgModEpsbReq:NORM:Ue Init procedure!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgModEpsbReq_ENUM, 4);

        if(NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByPti(pRcvMsg->stEsmNwMsgIE.ucPti,
                                                              &ulStateTblIndex))
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE, ESM_VERIFY_CN_MSG_PTI_MISMATCH, pRcvMsg->stEsmNwMsgIE.ucPti);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgModEpsbReq_ENUM, 5);
            return ;
        }

        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

        /* 用户发起的承载修改和去激活，不更新动态表信息 */

        NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI(pRcvMsg,ulStateTblIndex,pstStateAddr);

    }

    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwMsgModEpsbReq(ulStateTblIndex,pRcvMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgActDefltEpsbReq
 Description     : 处理缺省承载激活流程
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgActDefltEpsbReq
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /* 验证空口消息合法性 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateActDefltEpsbReqMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgActDefltEpsbReq: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgActDefltEpsbReq_ENUM, 1);
        return;
    }

    /* 如果承载已经激活，先本地去激活 */
    if(NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(pRcvMsg->stEsmNwMsgIE.ucEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgActDefltEpsbReq : release already active bearer!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgActDefltEpsbReq_ENUM, 2);
        NAS_ESM_DeactBearerAndInformApp(pRcvMsg->stEsmNwMsgIE.ucEpsbId);
    }

    /*根据PTI查找到动态表Index，若没查询到则进行异常处理*/
    if(NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByPti(pRcvMsg->stEsmNwMsgIE.ucPti, &ulStateTblIndex))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE, ESM_VERIFY_CN_MSG_PTI_MISMATCH, pRcvMsg->stEsmNwMsgIE.ucPti);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgActDefltEpsbReq_ENUM, 3);
        return ;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstStateAddr->ulEpsbId = pRcvMsg->stEsmNwMsgIE.ucEpsbId;

    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwMsgActDefltEpsbReq(ulStateTblIndex,pRcvMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgDeactEpsbReq
 Description     : 处理承载去激活流程
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgDeactEpsbReq
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCId               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    /* 验证空口消息 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateDeactEpsbReqMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgDeactEpsbReq: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgDeactEpsbReq_ENUM, 1);
        return;
    }

    /*根据承载ID，检查网络发起的流程与UE发起的流程是否有冲突*/
    if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(pRcvMsg->stEsmNwMsgIE.ucEpsbId,
                                                            &ulStateTblIndex))
    {
        if(NAS_ESM_PTI_UNASSIGNED_VALUE == pRcvMsg->stEsmNwMsgIE.ucPti )
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_EPSBID_IE,
                                            ESM_VERIFY_CN_UE_CN_OPERATION_COLLISION,
                                            pRcvMsg->stEsmNwMsgIE.ucEpsbId);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgDeactEpsbReq_ENUM, 2);

            NAS_ESM_ProcNwMsgDeactProcedureCollision(ulStateTblIndex,&pRcvMsg->stEsmNwMsgIE);
            return;
        }
    }


    /* 处理动态表和Cid */
    if (NAS_ESM_PTI_UNASSIGNED_VALUE == pRcvMsg->stEsmNwMsgIE.ucPti )
    {
        (VOS_VOID)NAS_ESM_QuerySdfId(&pRcvMsg->stEsmNwMsgIE,&ulCId);
        if (NAS_ESM_SUCCESS == NAS_ESM_GetStateTblIndexByCid(ulCId,&ulStateTblIndex))
        {
            pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

            /*填写状态表信息，包括承载状态，承载Id，承载类型*/
            pstStateAddr->ulEpsbId = pRcvMsg->stEsmNwMsgIE.ucEpsbId;
            pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(pstStateAddr->ulEpsbId);
            pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(pstStateAddr->ulEpsbId);
            pstStateAddr->ulCid = ulCId;
        }
        else
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE,
                                            ESM_VERIFY_CN_UPDATE_STATE_TABLE_FAIL,
                                            pRcvMsg->stEsmNwMsgIE.ucPti);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgDeactEpsbReq_ENUM, 3);
            return;
        }
    }
    else
    {
        if(NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByPti(pRcvMsg->stEsmNwMsgIE.ucPti,
                                                             &ulStateTblIndex))
        {
            NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE,
                                            ESM_VERIFY_CN_MSG_PTI_MISMATCH,
                                            pRcvMsg->stEsmNwMsgIE.ucPti);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgDeactEpsbReq_ENUM, 4);
            return ;
        }
        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDiffEBI(pRcvMsg,ulStateTblIndex,pstStateAddr);
    }


    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwMsgDeactEpsbReq(ulStateTblIndex,pRcvMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgPdnConnRej
 Description     : 处理pdn 连接拒绝消息
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgPdnConnRej
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;

    /* 验证空口消息,不验证TFT 优先级冲突的情况 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateNwRejMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgPdnConnRej: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgPdnConnRej_ENUM, 1);
        return;
    }

    /*根据PTI查找到动态表Index，若没查询到则丢弃*/
    if(NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByPti(pRcvMsg->stEsmNwMsgIE.ucPti, &ulStateTblIndex))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE,
                                        ESM_VERIFY_CN_MSG_PTI_MISMATCH,
                                        pRcvMsg->stEsmNwMsgIE.ucPti);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgPdnConnRej_ENUM, 2);
        return ;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_PdnConFailRecord(pRcvMsg, 0);
    #endif

    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwMsgPdnConnRej(ulStateTblIndex,pRcvMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgPdnDisconRej
 Description     : 处理Pdn 去连接 拒绝消息
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgPdnDisconRej
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;

    /* 验证空口消息,不验证TFT 优先级冲突的情况 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateNwRejMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgPdnDisconRej: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgPdnDisconRej_ENUM, LNAS_MSG_INVALID);
        return;
    }

    /*根据PTI查找到动态表Index，若没查询到则丢弃*/
    if(NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByPti(pRcvMsg->stEsmNwMsgIE.ucPti, &ulStateTblIndex))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE,
                                        ESM_VERIFY_CN_MSG_PTI_MISMATCH,
                                        pRcvMsg->stEsmNwMsgIE.ucPti);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgPdnDisconRej_ENUM, LNAS_FAIL);
        return ;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_PdnDisconFailRecord(pRcvMsg, 0);
    #endif

    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwMsgPdnDisconRej(ulStateTblIndex,pRcvMsg);
}


/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgResModRej
 Description     : 处理Pdn 去连接 拒绝消息
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgResModRej
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;

    /* 验证空口消息,不验证TFT 优先级冲突的情况 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateNwRejMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgResModRej: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgResModRej_ENUM, LNAS_MSG_INVALID);
        return;
    }

    /*根据PTI查找到动态表Index，若没查询到则丢弃*/
    if(NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByPti(pRcvMsg->stEsmNwMsgIE.ucPti, &ulStateTblIndex))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE,
                                        ESM_VERIFY_CN_MSG_PTI_MISMATCH,
                                        pRcvMsg->stEsmNwMsgIE.ucPti);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgResModRej_ENUM, LNAS_FAIL);
        return ;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_ResModFailRecord(pRcvMsg, 0);
    #endif

    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwMsgResModRej(ulStateTblIndex,pRcvMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgResAllocRej
 Description     : 处理资源分配拒绝消息
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgResAllocRej
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;

    /* 验证空口消息,不验证TFT 优先级冲突的情况 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateNwRejMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgResAllocRej: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgResAllocRej_ENUM, LNAS_MSG_INVALID);
        return;
    }

    /*根据PTI查找到动态表Index，若没查询到则丢弃*/
    if(NAS_ESM_FAILURE == NAS_ESM_QueryStateTblIndexByPti(pRcvMsg->stEsmNwMsgIE.ucPti, &ulStateTblIndex))
    {
        NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_PTI_IE,
                                        ESM_VERIFY_CN_MSG_PTI_MISMATCH,
                                        pRcvMsg->stEsmNwMsgIE.ucPti);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgResAllocRej_ENUM, LNAS_FAIL);
        return ;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_ResAllocFailRecord(pRcvMsg, 0);
    #endif

    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwMsgResAllocRej(ulStateTblIndex,pRcvMsg);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgEsmInfoReq
 Description     : 处理ESM Information 消息
 Input           : pRcvMsg -- 收到的空口消息
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwMsgEsmInfoReq
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    /* 验证空口消息,不验证TFT 优先级冲突的情况 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateEsmInfoReqMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgEsmInfoReq: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgEsmInfoReq_ENUM, LNAS_MSG_INVALID);
        return;
    }

    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwMsgEsmInfoReq(&pRcvMsg->stEsmNwMsgIE);
}


/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwsMsgEsmStatus
 Description     : 处理ESM Status 消息
 Input           : pRcvMsg -- 收到的空口消
 Output          : None
 Return          : None

 History         :
    1.l00143951      2010-10-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcNwsMsgEsmStatus
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    /* 验证空口消息,不验证TFT 优先级冲突的情况 */
    if (NAS_ESM_MSG_HANDLED == NAS_ESM_ValidateEsmStatusMsg(&pRcvMsg->stEsmNwMsgIE))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcNwsMsgEsmStatus: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwsMsgEsmStatus_ENUM, LNAS_MSG_INVALID);
        return;
    }

    /* 处理已经验证没有问题的空口消息 */
    NAS_ESM_ProcValidNwsMsgEsmStatus(&pRcvMsg->stEsmNwMsgIE);
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgEsmNotification
 Description     : 处理 ESM NOTIFICATION 消息
 Input           : pRcvMsg -- 收到的空口消
 Output          : None
 Return          : None

 History         :
    1.liuhua    00212067    2012-08-02  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgEsmNotification
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg
)
{
    VOS_UINT32 ulStateId;
    VOS_UINT8 ucRcvPti;
    VOS_UINT8 ucRcvEbi;
    NAS_ESM_ENCODE_INFO_STRU stEncodeInfo = {0};
    VOS_UINT32 ulMsgLen = 0;

    NAS_ESM_INFO_LOG("NAS_ESM_ProcNwMsgEsmNotification: entered");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgEsmNotification_ENUM, LNAS_ENTRY);

    if (NAS_ESM_NULL == pRcvMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ProcNwMsgEsmNotification: invalid parameter");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ProcNwMsgEsmNotification_ENUM, LNAS_NULL_PTR);
        return;
    }

    ucRcvPti = pRcvMsg->stEsmNwMsgIE.ucPti;
    ucRcvEbi = pRcvMsg->stEsmNwMsgIE.ucEpsbId;

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
    stEncodeInfo.ucPti       = ucRcvPti;
    stEncodeInfo.ulEpsbId    = ucRcvEbi;

    if (NAS_ESM_PTI_RESERVED_VALUE == ucRcvPti)
    {
        /* If the PTI is a reserved value, the UE shall respond with an ESM
           STATUS message including ESM cause #81 "invalid PTI value" */
        stEncodeInfo.ucESMCau = NAS_ESM_CAUSE_INVALID_PTI_VALUE;

        NAS_ESM_EncodeEsmStatus(stEncodeInfo, NAS_ESM_GetCurEsmSndNwMsgAddr(), &ulMsgLen);
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    }
    else if ((NAS_ESM_PTI_UNASSIGNED_VALUE != ucRcvPti) &&
             (NAS_ESM_SUCCESS != NAS_ESM_QueryStateTblIndexByPti(ucRcvPti, &ulStateId)))
    {
        /* If the PTI is an assigned value that does not match any PTI in use,
           the UE shall respond with an ESM STATUS message including ESM cause
           #47 "PTI mismatch" */
        stEncodeInfo.ucESMCau = NAS_ESM_CAUSE_PTI_MISMATCH;

        NAS_ESM_EncodeEsmStatus(stEncodeInfo, NAS_ESM_GetCurEsmSndNwMsgAddr(), &ulMsgLen);
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    }
    else if (((ucRcvEbi > NAS_ESM_UNASSIGNED_EPSB_ID) && (ucRcvEbi < NAS_ESM_MIN_EPSB_ID)) ||
             (NAS_ESM_BEARER_STATE_ACTIVE != NAS_ESM_GetBearCntxtState(ucRcvEbi)) ||
             ((NAS_ESM_UNASSIGNED_EPSB_ID == ucRcvEbi) && (NAS_ESM_PTI_UNASSIGNED_VALUE == ucRcvPti)))
    {
        /* 1. includes a reserved EPS bearer identity value
           2. includes a assigned EPS bearer identity value that does not match
              an existing EPS bearer context
           3. includes the combination of an unassigned PTI value and an
              unassigned EPS bearer identity value  */
        stEncodeInfo.ucESMCau = NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY;

        NAS_ESM_EncodeEsmStatus(stEncodeInfo, NAS_ESM_GetCurEsmSndNwMsgAddr(), &ulMsgLen);
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    }
    else
    {
        /*sunbing 49683 2013-10-14 VoLTE begin*/
        if(pRcvMsg->stEsmNwMsgIE.stNotificationInd.ucValue == NAS_ESM_NOTIFICATION_INDICATOR_SRVCC_HO_CANCEL)
        {
            NAS_ESM_SndApsEsmNotificationIndMsg(ESM_APS_NOTIFICATION_IND_SRVCC_HO_CANCELLED);
        }
        else
        {
            NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgEsmNotification: Err para!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgEsmNotification_ENUM, LNAS_PARAM_INVALID);
        }
        /*sunbing 49683 2013-10-14 VoLTE end*/
        /* TODO: Notify ESM user */
    }
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name  : NAS_ESM_NwMsgProcess
 Description    : ESM模块对初步译码后的网侧空口消息进行处理
 Input          : EMM_ESM_INTRA_DATA_IND_STRU *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2009-02-05  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_NwMsgProcess
(
    const  EMM_ESM_INTRA_DATA_IND_STRU      *pRcvMsg
)
{
    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_NwMsgProcess is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_NwMsgProcess_ENUM, LNAS_ENTRY);

    switch(pRcvMsg->stEsmNwMsgIE.enEsmCnMsgType)
    {
       case NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ:
           NAS_ESM_ProcNwMsgActDefltEpsbReq(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ:
           NAS_ESM_ProcNwMsgActDedictdEpsbReq(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ:
           NAS_ESM_ProcNwMsgModEpsbReq(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_DEACT_EPS_BEARER_CNTXT_REQ:
           NAS_ESM_ProcNwMsgDeactEpsbReq(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REJ:
           NAS_ESM_ProcNwMsgPdnConnRej(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REJ:
           NAS_ESM_ProcNwMsgPdnDisconRej(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REJ:
           NAS_ESM_ProcNwMsgResModRej(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REJ:
           NAS_ESM_ProcNwMsgResAllocRej(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_REQ:
           NAS_ESM_ProcNwMsgEsmInfoReq(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_ESM_STATUS:
           NAS_ESM_ProcNwsMsgEsmStatus(pRcvMsg);
           break;
       case NAS_ESMCN_MSG_TYPE_ESM_NOTIFICATION:
           NAS_ESM_ProcNwMsgEsmNotification(pRcvMsg);
           break;
       default:
           NAS_ESM_SndOmLogCnMsgVerifyFail(NAS_ESM_CN_MSG_IE_NOIE,
                                           ESM_VERIFY_CN_MSG_CN_MSG_TYPE_INVALID,
                                           pRcvMsg->stEsmNwMsgIE.enEsmCnMsgType);
           TLPS_PRINT2LAYER_WARNING(NAS_ESM_NwMsgProcess_ENUM, LNAS_MSG_INVALID);
           break;
    }
}

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmAppSdfProcCnfSucc
 Description    : 根据用户不同的需求进行回复
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.y00159566     2011-7-1  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfProcCnfSucc
(
    VOS_UINT32                          ulStateTblIndex,
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enModfyType
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* 回复App 修改成功 *//* 由于没有修改请求，无法得知修改的内容，统一回复TFT&QOS
    根据stAppMsgRecord中的enAppMsgType判断 */
    if (ID_APP_ESM_PDP_MODIFY_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)
    {
        NAS_ESM_SndEsmAppSdfModCnfSuccMsg(ulStateTblIndex, enModfyType);
    }
    else if (ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)
    {
        NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg(ulStateTblIndex);
    }
    else if (ID_APP_ESM_PDP_RELEASE_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)
    {
        NAS_ESM_SndEsmAppSdfRelCnfSuccMsg(ulStateTblIndex);
    }
    else
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SndEsmAppSdfProcCnfSucc: Modfy Cnf Type IS Error!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfProcCnfSucc_ENUM, LNAS_MSG_INVALID);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_ProcNwMsgActDediBearSamePtiWithDeffEBI
 Description    : 处理GCF10.8.1，收到网侧的ActDedi处理，PTI相同但承载不同
 Input          : EMM_ESM_INTRA_DATA_IND_STRU *pRcvMsg
                  VOS_UINT32                   ulStateTblIndex,
                  NAS_ESM_STATE_INFO_STRU     *pstStateAddr
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.y00159566     2011-7-1  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgActDediBearSamePtiWithDiffEBI
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg,
    VOS_UINT32                                ulStateTblIndex,
    NAS_ESM_STATE_INFO_STRU                  *pstStateAddr

)
{
    VOS_UINT32                                ulCId = NAS_ESM_NULL;

    if (NAS_ESM_UNASSIGNED_EPSB_ID == pstStateAddr->ulEpsbId)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgActDediBearSamePtiWithDiffEBI:WARNING:Local Eps Id is Unassigned!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgActDediBearSamePtiWithDiffEBI_ENUM, 1);

        pstStateAddr->ulEpsbId = pRcvMsg->stEsmNwMsgIE.ucEpsbId;

        return;
    }

    /* 查询相同的PTI对应的EBI是否相同 */
    if (pstStateAddr->ulEpsbId != pRcvMsg->stEsmNwMsgIE.ucEpsbId)
    {
        /* 回复App 修改成功 *//* 由于没有修改请求，无法得知修改的内容，统一回复TFT&QOS */
        NAS_ESM_SndEsmAppSdfProcCnfSucc(ulStateTblIndex, APP_ESM_BEARER_MODIFY_TFT_QOS);

        /* 释放状态表 */
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        /* 生成1个CID */
        ulCId = NAS_ESM_GetCid(pRcvMsg->stEsmNwMsgIE.ucEpsbId);

        if (NAS_ESM_SUCCESS == NAS_ESM_GetStateTblIndexByCid(ulCId,&ulStateTblIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ProcNwMsgActDediBearSamePtiWithDiffEBI:Get Cid Succ");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgActDediBearSamePtiWithDiffEBI_ENUM, LNAS_SUCC);

            pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

            /*填写状态表信息，包括承载状态，承载Id，承载类型*/
            pstStateAddr->ulEpsbId = pRcvMsg->stEsmNwMsgIE.ucEpsbId;
            pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(pstStateAddr->ulEpsbId);
            pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(pstStateAddr->ulEpsbId);
            pstStateAddr->ulCid = ulCId;
        }
        else
        {
            NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgActDediBearSamePtiWithDeffEBI: state table not enough!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgActDediBearSamePtiWithDiffEBI_ENUM, LNAS_FAIL);
        }
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_ProcNwMsgModDediBearSamePtiWithDeffEBI
 Description    : 处理GCF10.8.1，收到网侧的ModDedi处理，PTI相同但承载不同
 Input          : EMM_ESM_INTRA_DATA_IND_STRU *pRcvMsg
                  VOS_UINT32                   ulStateTblIndex,
                  NAS_ESM_STATE_INFO_STRU     *pstStateAddr
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.y00159566     2011-7-1  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg,
    VOS_UINT32                                ulStateTblIndex,
    NAS_ESM_STATE_INFO_STRU                  *pstStateAddr

)
{
    VOS_UINT32                                ulCId  = NAS_ESM_NULL;
    VOS_UINT32                                ulRslt = NAS_ESM_NULL;

    if (NAS_ESM_UNASSIGNED_EPSB_ID == pstStateAddr->ulEpsbId)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI:WARNING:Local Eps Id is Unassigned!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI_ENUM, 1);

        pstStateAddr->ulEpsbId = pRcvMsg->stEsmNwMsgIE.ucEpsbId;

        return;
    }

    /* 查询相同的PTI对应的EBI是否相同 */
    if (pstStateAddr->ulEpsbId != pRcvMsg->stEsmNwMsgIE.ucEpsbId)
    {
        /* 回复App 修改成功 *//* 由于没有修改请求，无法得知修改的内容，统一回复TFT&QOS */
        NAS_ESM_SndEsmAppSdfProcCnfSucc(ulStateTblIndex, APP_ESM_BEARER_MODIFY_TFT_QOS);

        /* 释放状态表 */
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        /* 查找CID */
        ulRslt = NAS_ESM_QuerySdfId(&(pRcvMsg->stEsmNwMsgIE),&ulCId);

        if ((NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_EQUAL_CID != ulRslt)
         && (NAS_ESM_QUERY_CID_RSLT_PART_FOUND_EQUAL_CID != ulRslt))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI:Not Found!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI_ENUM, LNAS_FAIL);

            /* 是否会出现重复?承载是否有检查? */
            ulCId = NAS_ESM_GetCid(pRcvMsg->stEsmNwMsgIE.ucEpsbId);
        }

        if (NAS_ESM_SUCCESS == NAS_ESM_GetStateTblIndexByCid(ulCId,&ulStateTblIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI:Get Cid Succ!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI_ENUM, LNAS_SUCC);

            pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

            /*填写状态表信息，包括承载状态，承载Id，承载类型*/
            pstStateAddr->ulEpsbId = pRcvMsg->stEsmNwMsgIE.ucEpsbId;
            pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(pstStateAddr->ulEpsbId);
            pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(pstStateAddr->ulEpsbId);
            pstStateAddr->ulCid = ulCId;
        }
        else
        {
            NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgModDediBearSamePtiWithDeffEBI:WARNING:insufficient resource!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgModDediBearSamePtiWithDiffEBI_ENUM, 1);
        }
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDeffEBI
 Description    : 处理GCF10.8.1，收到网侧的DeaDedi处理，PTI相同但承载不同
 Input          : EMM_ESM_INTRA_DATA_IND_STRU *pRcvMsg
                  VOS_UINT32                   ulStateTblIndex,
                  NAS_ESM_STATE_INFO_STRU     *pstStateAddr
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.y00159566     2011-7-1  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDiffEBI
(
    const EMM_ESM_INTRA_DATA_IND_STRU        *pRcvMsg,
    VOS_UINT32                                ulStateTblIndex,
    NAS_ESM_STATE_INFO_STRU                  *pstStateAddr

)
{
    VOS_UINT32                                ulCId  = NAS_ESM_NULL;

    if (NAS_ESM_UNASSIGNED_EPSB_ID == pstStateAddr->ulEpsbId)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDiffEBI:WARNING:Local Eps Id is Unassigned!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDiffEBI_ENUM, 1);

        pstStateAddr->ulEpsbId = pRcvMsg->stEsmNwMsgIE.ucEpsbId;

        return;
    }

    /* 查询相同的PTI对应的EBI是否相同 */
    if (pstStateAddr->ulEpsbId != pRcvMsg->stEsmNwMsgIE.ucEpsbId)
    {
        /* 回复App 修改成功 *//* 由于没有修改请求，无法得知修改的内容，统一回复TFT&QOS */
        NAS_ESM_SndEsmAppSdfProcCnfSucc(ulStateTblIndex, APP_ESM_BEARER_MODIFY_TFT_QOS);

        /* 释放状态表 */
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        (VOS_VOID)NAS_ESM_QuerySdfId(&(pRcvMsg->stEsmNwMsgIE),&ulCId);
        if (NAS_ESM_SUCCESS == NAS_ESM_GetStateTblIndexByCid(ulCId,&ulStateTblIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDiffEBI:Get Cid Succ!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDiffEBI_ENUM, LNAS_SUCC);

            pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

            /*填写状态表信息，包括承载状态，承载Id，承载类型*/
            pstStateAddr->ulEpsbId = pRcvMsg->stEsmNwMsgIE.ucEpsbId;
            pstStateAddr->enBearerCntxtState = NAS_ESM_GetBearCntxtState(pstStateAddr->ulEpsbId);
            pstStateAddr->enBearerCntxtType  = NAS_ESM_GetBearCntxtType(pstStateAddr->ulEpsbId);
            pstStateAddr->ulCid = ulCId;
        }
        else
        {
            NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDeffEBI:state table not enough!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgDeaDediBearSamePtiWithDiffEBI_ENUM, LNAS_FAIL);
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndOmLogCnMsgVerifyFail
 Description     : ESM合法性检查失败
 Input           : enIeType 信元类型
                   enCause  失败原因
                   ulValue  失败值
 Output          : None
 Return          : None

 History         :
    1.chengmin 00285307      2015-6-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndOmLogCnMsgVerifyFail
(
    NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32                  enIeType,
    NAS_ESM_VERIFY_CN_MSG_FAIL_CAUSE_ENUM_UINT32        enCause,
    VOS_UINT32                                          ulValue
)
{
    NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL_STRU      *pstMsg = VOS_NULL_PTR;
#if (VOS_OS_VER == VOS_WIN32)
    VOS_CHAR                                     acPrintStr[MAX_PRINT_CHAR_NUM] = {0};
    VOS_CHAR                                     acValue[MAX_PRINT_CHAR_NUM]    = {0};
#endif

    pstMsg = (NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndOmLogCnMsgVerifyFail: mem alloc fail!.");
        return;
    }

    NAS_ESM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL_STRU),
                        0,
                        sizeof(NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_ESM_OM_LOG_VERIFY_CN_MSG_FAIL;
    pstMsg->enIeType                    = enIeType;
    pstMsg->enCause                     = enCause;
    pstMsg->ulValue                     = ulValue;

#if (VOS_OS_VER == VOS_WIN32)
    VOS_StrCpy(acPrintStr, "ESM CN MSG Verify Fail, Fail IE:");
    VOS_StrCat(acPrintStr, g_EsmDecodeFailIePrintTable[enIeType-1].aucPrintStr);
    VOS_StrCat(acPrintStr, ", Fail Cause:");
    VOS_StrCat(acPrintStr, g_EsmVerifyCnMsgFailCausePrintTable[enCause-1].aucPrintStr);
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

