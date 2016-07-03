


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MnCallSendCc.h"
#include "NasIeUtil.h"
#include "MnCall.h"
#include "MnCallApi.h"
#include "NasCcIe.h"
#include "PsCommonDef.h"
#include "MnComm.h"
#include "MnCallMgmt.h"
#include "MnCallFacilityEncode.h"
#include "NasIeUtil.h"
#include "MnErrorCode.h"
#include "MnCallReqProc.h"

#include "MnCallCtx.h"

#include "MnCallSendApp.h"

#include "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_SEND_CC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/*****************************************************************************
   2 函数实现
*****************************************************************************/

LOCAL VOS_VOID  MN_CALL_FillIeCause(
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCauseVal,
    NAS_CC_IE_CAUSE_STRU                *pstCauseIe
)
{
    NAS_IE_SET_PRESENT(pstCauseIe);

    /* Set octet3 to 0xe0:
           Coding standard: GSM
           Location :       User
           No extended octet
    */
    NAS_IE_SET_OCTET(pstCauseIe, Octet3, 0xe0);

    pstCauseIe->Octet4.CauseValue = enCauseVal;
    pstCauseIe->Octet4.Ext = NAS_CC_IE_NO_EXT;

    NAS_IE_SET_LAST_OCTET_OFFSET(pstCauseIe, Octet4);
}


LOCAL VOS_VOID  MN_CALL_FillIeRepeatInd(
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    NAS_CC_IE_REPEAT_INDICATOR_STRU     *pstRepeatInd
)
{

    /* 如果repeat indicator不存在，置位不存在，返回 */
    if (MN_CALL_REP_IND_NULL == enRepeatInd)
    {
        NAS_IE_SET_ABSENT(pstRepeatInd);
        return;
    }

    /* 如果repeat indicator存在，则置存在，并赋值 */
    NAS_IE_SET_PRESENT(pstRepeatInd);

    pstRepeatInd->RepeatIndication = enRepeatInd;

}


LOCAL VOS_VOID  MN_CALL_FillIeSupCodecList(
    NAS_CC_IE_SUPPORTED_CODEC_LIST_STRU *pstCodecList
)
{
    MN_CALL_SUPPORT_CODEC_UNION         unCodec;

    NAS_IE_SET_PRESENT(pstCodecList);

    /* 设置支持的列表，目前填入了GSM和UMTS支持的codec list,
       00 表示GSM, 04表示UMTS */
    /* 具体赋值的含义参见26.103 */

    PS_MEM_SET(&unCodec,0x00,sizeof(unCodec));
    pstCodecList->LastOctOffset = 8;
    pstCodecList->CodecInfo[0].SysId = 0x04;
    pstCodecList->CodecInfo[0].LastOctOffsetengthOfBitMap = 0x02;
    MN_CALL_FillUmtsSupCodecList(&(unCodec));
    pstCodecList->CodecInfo[0].CodecBitmapL = (VOS_UINT8)(unCodec.usSupportCodec);
    pstCodecList->CodecInfo[0].CodecBitmapH = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

    /* 填写GSM支持的codec类型 */
    PS_MEM_SET(&unCodec,0x00,sizeof(unCodec));
    MN_CALL_FillGsmSupCodecList(&(unCodec));
    pstCodecList->CodecInfo[1].SysId = 0x00;
    pstCodecList->CodecInfo[1].LastOctOffsetengthOfBitMap = 0x02;
    pstCodecList->CodecInfo[1].CodecBitmapL = (VOS_UINT8)(unCodec.usSupportCodec);
    pstCodecList->CodecInfo[1].CodecBitmapH = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

}



LOCAL VOS_VOID  MN_CALL_FillIeLlc(
    NAS_CC_IE_LLC_STRU                  *pstLLC1
)
{
    NAS_IE_SET_PRESENT(pstLLC1);

    pstLLC1->LastOctOffset = 3;

    /* 此处根据IOT 北美测试，标杆填写的内容填写 */
    pstLLC1->LLCContents[0] = 0x88;
    pstLLC1->LLCContents[1] = 0x90;
    pstLLC1->LLCContents[2] = 0xA6;
}



LOCAL VOS_VOID  MN_CALL_FillIeCcCap(
    NAS_CC_IE_CC_CAP_STRU               *pstCcCap
)
{
    NAS_IE_SET_PRESENT(pstCcCap);

    pstCcCap->LastOctOffset = 3;


    pstCcCap->Octet3.DTMF  = NAS_CC_DTMF_SPECIFIED;
    pstCcCap->Octet3.PCP   = NAS_CC_PCP_NOT_SUPPORT;
    pstCcCap->Octet3.ENICM = NAS_CC_ENICM_NOT_SUPPORT;
    pstCcCap->Octet4.MaxSpeechBearers = NAS_CC_SPEECH_BEARER_1;
}



MsgBlock* MN_CALL_AllocMnccPrimitive(
    VOS_UINT8                           callId,
    MNCC_PRIM_NAME_ENUM_U16             enPrimName,
    MNCC_REQ_PARAM_UNION                **ppunParam
)
{
/*
    申请VOS消息, 大小为sizeof(MNCC_REQ_PRIM_MSG_STRU)
    if 申请失败
        返回 NULL

    填写VOS消息头

    根据CallId获得CC实体ID

    填写CC实体ID, CallId, enPrimName等公共信息

    输出Payload指针

    返回VOS消息头指针
*/
    MNCC_REQ_PRIM_MSG_STRU *pstMsg =
        (MNCC_REQ_PRIM_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                sizeof(MNCC_REQ_PRIM_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_CALL_AllocMnccPrimitive: Failed to alloc VOS message.");
        return VOS_NULL_PTR;
    }


    PS_MEM_SET(pstMsg, 0, sizeof(MNCC_REQ_PRIM_MSG_STRU));

    /* 填写VOS消息头 */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_CC;
    pstMsg->ulLength        = sizeof(MNCC_REQ_PRIM_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写公共信息 */
    pstMsg->enPrimName = enPrimName;
    pstMsg->ucTi       = (VOS_UINT8)MN_CALL_GetCcTi(callId);
    pstMsg->ucCallId     = callId;
    pstMsg->ulParamLen = sizeof(MNCC_REQ_PARAM_UNION);

    MN_INFO_LOG4("MN_CALL_AllocMnccPrimitive: enPrimName, ucTi, ucCallId, ulParamLen:",
                 pstMsg->enPrimName,
                 pstMsg->ucTi,
                 pstMsg->ucCallId,
                 (VOS_INT32)pstMsg->ulParamLen);


    *ppunParam = &pstMsg->unParam;

    return (MsgBlock*)pstMsg;


}



VOS_UINT32  MN_CALL_SendMnccPrimitive(MsgBlock * pMsg)
{
    /*
    调用VOS_SendMsg发送消息
    */
    return PS_SEND_MSG(WUEPS_PID_TAF, pMsg);
}


VOS_UINT32  MN_CALL_SendCcSetupReq(
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU            *pstBc1,
    const NAS_CC_IE_BC_STRU            *pstBc2,
    const MN_CALL_MGMT_STRU            *pstCallInfo
)
{

    NAS_CC_MSG_SETUP_MO_STRU            *pstSetup;
    MsgBlock                            *pMsg;
    MN_CALL_SS_COMPONENT_UNION          unComponent;
    VOS_UINT32                          ulLen;

    MN_CALL_MSG_BUFF_STRU              *pstBufferdSetupMsg = VOS_NULL_PTR;

    /* 申请MNCC_SETUP_REQ原语 */
    pMsg = MN_CALL_AllocMnccPrimitive(pstCallInfo->stCallInfo.callId,
                                      MNCC_SETUP_REQ,
                                      (MNCC_REQ_PARAM_UNION**)&pstSetup);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcSetupReq: Failed to alloc setup message.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    /* 填写redial标志  */
    ((MNCC_REQ_PRIM_MSG_STRU *)pMsg)->ucRedialFlg = VOS_FALSE;

    /* 填写repeat indicator*/
    MN_CALL_FillIeRepeatInd(enRepeatInd, &pstSetup->stBCRepeatInd);

    /* 填写BC1和BC2 */
    pstSetup->stBC1 = *pstBc1;
    pstSetup->stBC2 = *pstBc2;


    /* 填写被叫号码 */
    if (0 != pstCallInfo->stCallInfo.stCalledNumber.ucNumLen)
    {
        NAS_IE_SET_PRESENT(&pstSetup->stCalledNum);

        *((VOS_UINT8*)&pstSetup->stCalledNum.Octet3) = pstCallInfo->stCallInfo.stCalledNumber.enNumType;

        PS_MEM_CPY(pstSetup->stCalledNum.BCDNum,
                   pstCallInfo->stCallInfo.stCalledNumber.aucBcdNum,
                   pstCallInfo->stCallInfo.stCalledNumber.ucNumLen);

        NAS_IE_SET_BLOCK_SIZE(&pstSetup->stCalledNum,
                              BCDNum,
                              pstCallInfo->stCallInfo.stCalledNumber.ucNumLen);
    }
    else
    {
        return TAF_CS_CAUSE_UNKNOWN;
    }

    /* 填写被叫号码的子地址 */
    if (VOS_TRUE == pstCallInfo->stCallInfo.stCalledSubAddr.IsExist)
    {
        NAS_IE_SET_PRESENT(&pstSetup->stCalledSubaddr);
        pstSetup->stCalledSubaddr.LastOctOffset = pstCallInfo->stCallInfo.stCalledSubAddr.LastOctOffset;

        PS_MEM_CPY((VOS_UINT8 *)&pstSetup->stCalledSubaddr.Octet3,
                   &pstCallInfo->stCallInfo.stCalledSubAddr.Octet3,
                   sizeof(VOS_UINT8));

        ulLen = pstCallInfo->stCallInfo.stCalledSubAddr.LastOctOffset - sizeof(pstCallInfo->stCallInfo.stCalledSubAddr.Octet3);
        PS_MEM_CPY(pstSetup->stCalledSubaddr.SubAddrInfo,
                   pstCallInfo->stCallInfo.stCalledSubAddr.SubAddrInfo,
                   ulLen);
    }


    /* 如果存在CUG信息，那么进行CUG编码 */
    if (VOS_TRUE == pstCallInfo->stCugCfg.bEnable)
    {
        unComponent.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
        if (VOS_OK == MN_CALL_InvokeIdAlloc(pstCallInfo->stCallInfo.callId,
                                            &unComponent.invokeComp.ucInvokeId,
                                            MN_CALL_SS_CUG_OPERATION))
        {
            unComponent.invokeComp.ucCompType       = MN_CALL_SS_INVOKE_TYPE_TAG;
            unComponent.invokeComp.ucOperateCode    = MN_CALL_SS_CUG_OPERATION;
            unComponent.invokeComp.bitOpArg         = 1;
            unComponent.invokeComp.unArg.cugInfoArg = pstCallInfo->stCugCfg;

            NAS_IE_SET_PRESENT(&pstSetup->stFacility);
            ulLen = MN_CALL_FacilityEncode(pstSetup->stFacility.aucFacility, &unComponent);

            /*数据块中的数据长度为TLV结构中的V的长度*/
            NAS_IE_SET_BLOCK_SIZE(&pstSetup->stFacility,
                                  aucFacility,
                                  ulLen);
        }
    }

    /*填写CLIR的配置条件*/
    switch(pstCallInfo->enClirCfg)
    {
    case MN_CALL_CLIR_AS_SUBS:
        break;

    case MN_CALL_CLIR_INVOKE:
        NAS_IE_SET_PRESENT(&pstSetup->stCLIR_I);
        break;

    case MN_CALL_CLIR_SUPPRESS:
        NAS_IE_SET_PRESENT(&pstSetup->stCLIR_S);
        break;

    default:
        MN_WARN_LOG("MN_CALL_SendCcSetupReq: Failed to send message.");
        break;

    }

    /* 目前没有填写其他的参数，如果需要，后续可以根据需求增加相应的参数 */
    if (MN_CALL_TYPE_VIDEO != pstCallInfo->stCallInfo.enCallType)
    {
        MN_CALL_FillIeCcCap(&(pstSetup->stCCCap));
        MN_CALL_FillIeSupCodecList(&pstSetup->stCodecList);
    }
    else
    {
        MN_CALL_FillIeLlc(&pstSetup->stLLC1);
        MN_CALL_FillIeCcCap(&pstSetup->stCCCap);
    }

    /* 如果支持呼叫重建功能，则缓存setup的消息 */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(pstCallInfo->stCallInfo.callId))
    {
        pstBufferdSetupMsg                        = MN_CALL_GetBufferedMsg();
        pstBufferdSetupMsg->bitOpBufferedSetupMsg = VOS_TRUE;
        PS_MEM_CPY(&pstBufferdSetupMsg->stBufferedSetupMsg,
                   (MNCC_REQ_PRIM_MSG_STRU *)pMsg, sizeof(MNCC_REQ_PRIM_MSG_STRU));
    }

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcSetupReq: Failed to send message.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    MN_NORM_LOG("MN_CALL_SendCcSetupReq: send message to cc.");
    return TAF_CS_CAUSE_SUCCESS;

}



VOS_UINT32  MN_CALL_SendCcEmergSetupReq(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                          *pucCategory
)
{
/*
    申请MNCC_EMERG_SETUP_REQ原语
    if 申请失败
        返回 FAIL

    根据输入参数填写payload中的stEmerg结构

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/
    NAS_CC_MSG_EMERGENCY_STEUP_STRU    *pstEmerg = VOS_NULL_PTR;
    MsgBlock                           *pMsg     = VOS_NULL_PTR;


    MN_CALL_MSG_BUFF_STRU              *pstBufferdSetupMsg = VOS_NULL_PTR;

    NAS_CC_IE_BC_STRU                   stBc1;
    NAS_CC_IE_BC_STRU                   stBc2;
    MN_CALL_REP_IND_ENUM_U8             enBcRepeatInd;
    VOS_UINT32                          ulRet;

    ulRet = MN_CALL_GetMoCallBc(callId, &stBc1, &stBc2, &enBcRepeatInd);
    if (VOS_OK != ulRet)
    {
        /* 构造BC失败，释放呼叫 */
        MN_WARN_LOG("MN_CALL_SendCcEmergSetupReq: BUILD BC FAIL.");

        return TAF_CS_CAUSE_UNKNOWN;
    }

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_EMERG_SETUP_REQ, (MNCC_REQ_PARAM_UNION **)&pstEmerg);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcEmergSetupReq: Failed to alloc EmergSetup message.");

        return TAF_CS_CAUSE_UNKNOWN;
    }

    /* 填写redial标志  */
    ((MNCC_REQ_PRIM_MSG_STRU *)pMsg)->ucRedialFlg = VOS_FALSE;

    pstEmerg->stBC = stBc1;

    if (VOS_NULL_PTR != pucCategory)
    {
        NAS_IE_SET_PRESENT(&pstEmerg->stEmergencyCAT);
        pstEmerg->stEmergencyCAT.Octet3.EmergencyCAT = *pucCategory;
        NAS_IE_SET_LAST_OCTET_OFFSET(&pstEmerg->stEmergencyCAT,Octet3);
    }

    /* 2010-05-22, OuyangFei:
       紧急呼，在进行G->W切换时，网络会将电话中止，经与标杆比对，发现是可选IE Supported Codecs引起，
       原因未知，可能是紧急呼时不支持Supported Codecs选项，
       因此将该IE去除。
    MN_CALL_FillIeSupCodecList(&pstEmerg->stCodecList);
    */
    /* 根据24.008 9.3.8.3,UE应该包含此IE */
    MN_CALL_FillIeSupCodecList(&pstEmerg->stCodecList);

    /* 如果支持呼叫重建功能，则缓存setup的消息 */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(callId))
    {
        pstBufferdSetupMsg                        = MN_CALL_GetBufferedMsg();
        pstBufferdSetupMsg->bitOpBufferedSetupMsg = VOS_TRUE;
        PS_MEM_CPY(&pstBufferdSetupMsg->stBufferedSetupMsg,
                   (MNCC_REQ_PRIM_MSG_STRU *)pMsg, sizeof(MNCC_REQ_PRIM_MSG_STRU));
    }

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcEmergSetupReq: Failed to send message.");

        return TAF_CS_CAUSE_UNKNOWN;
    }

    MN_NORM_LOG("MN_CALL_SendCcEmergSetupReq: send message to cc.");

    return TAF_CS_CAUSE_SUCCESS;
}



VOS_UINT32  MN_CALL_SendCcCallConfReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU             *pstBc1,
    const NAS_CC_IE_BC_STRU             *pstBc2,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{
/*
    申请MNCC_CALL_CONF_REQ原语
    if 申请失败
        返回 FAIL

    根据输入参数填写payload中的stCallConf结构

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/

    NAS_CC_MSG_CALL_CNF_STRU            *pstCallCnf;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_CALL_CONF_REQ, (MNCC_REQ_PARAM_UNION **)&pstCallCnf);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcCallConfReq: Failed to alloc CallConf message.");
        return VOS_ERR;
    }

    /*填写pstCallCnf结构中的repeat indicator值*/
    MN_CALL_FillIeRepeatInd(enRepeatInd, &pstCallCnf->stRepeatInd);

    /* 填写pstCallCnf结构中的Cause值 */
    if(MN_CALL_INVALID_CAUSE != enCause)
    {
        MN_CALL_FillIeCause(enCause, &pstCallCnf->stCause);
    }

    /* 对BC1和BC2进行赋值 */
    pstCallCnf->stBC1 = *pstBc1;
    pstCallCnf->stBC2 = *pstBc2;

    if (MN_CALL_TYPE_VIDEO != MN_CALL_GetCallType(callId))
    {
        MN_CALL_FillIeSupCodecList(&pstCallCnf->stCodecList);
    }
    else
    {
        MN_CALL_FillIeCcCap(&pstCallCnf->stCCCap);
    }

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcCallConfReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcCallConfReq: send message to cc.");

    return VOS_OK;


}



VOS_UINT32  MN_CALL_SendCcDiscReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{
/*
    申请MNCC_DISC_REQ原语
    if 申请失败
        返回 FAIL

    根据输入参数填写payload中的stDisc结构

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/
    NAS_CC_MSG_DISCONNECT_MO_STRU       *pstDisc;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_DISC_REQ, (MNCC_REQ_PARAM_UNION **)&pstDisc);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcDiscReq: Failed to alloc Disc message.");
        return VOS_ERR;
    }

#if (FEATURE_ON == FEATURE_PTM)
    MN_CALL_CsCallDiscInfoRecord(callId, enCause);
#endif

    /* 填写pstDisc结构中的Cause值 */
    MN_CALL_FillIeCause(enCause, &pstDisc->stCause);

    /* 下发CALL DISCONNECT EVENT到USIM模块 */
    MN_CALL_SndStkCallDiscEvent(pMsg, MNCC_DISC_REQ, VOS_FALSE);

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcDiscReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcDiscReq: send message to cc.");

    return VOS_OK;


}



VOS_UINT32  MN_CALL_SendCcRelReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{
/*
    申请MNCC_REL_REQ原语
    if 申请失败
        返回 FAIL

    根据输入参数填写payload中的stRel结构

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/
    NAS_CC_MSG_RELEASE_MO_STRU          *pstRel;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_REL_REQ, (MNCC_REQ_PARAM_UNION **)&pstRel);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcRelReq: Failed to alloc CcRel message.");
        return VOS_ERR;
    }

    /* 填写pstRel结构中的Cause值 */
    MN_CALL_FillIeCause(enCause, &pstRel->stCause);

    /* 记录主动释放的原因值 */
    MN_CALL_UpdateCcCause(callId, enCause);

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* 下发CALL DISCONNECT EVENT到USIM模块 */
    MN_CALL_SndStkCallDiscEvent(pMsg, MNCC_REL_REQ, VOS_FALSE);

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcRelReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcRelReq: send message to cc.");

    return VOS_OK;


}



VOS_VOID  MN_CALL_SendCcRejReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{
/*
    申请MNCC_REJ_REQ原语
    if 申请失败
        返回 FAIL

    根据输入参数填写payload中的stRej结构

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/

    /*申请MNCC_REJ_REQ原语*/
    NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU *pstRelComp;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_REJ_REQ, (MNCC_REQ_PARAM_UNION **)&pstRelComp);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcRejReq: Failed to alloc CcRel message.");
        return;
    }

    /* 填写pstRelComp结构中的Cause值 */
    MN_CALL_FillIeCause(enCause, &pstRelComp->stCause);

    /* 记录拒绝原因值 */
    MN_CALL_UpdateCcCause(callId, enCause);

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* 下发CALL DISCONNECT EVENT到USIM模块 */
    MN_CALL_SndStkCallDiscEvent(pMsg, MNCC_REJ_REQ, VOS_FALSE);

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcRejReq: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcRejReq: send message to cc.");

    return;

}



VOS_UINT32  MN_CALL_SendCcSetupRsp(
    MN_CALL_ID_T                        callId
)
{
/*
    申请MNCC_SETUP_RES原语
    if 申请失败
        返回 FAIL

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/

    MNCC_REQ_PARAM_UNION                *punParam;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_SETUP_RES, &punParam);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcSetupRsp: Failed to alloc SetupRsp message.");
        return VOS_ERR;
    }

    /* 目前暂时还不需要对CONNECT消息填充具体内容 */

    MN_CALL_SndStkCallConnEvent((VOS_UINT8)MN_CALL_GetCcTi(callId), MN_CALL_DIR_MT);

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcSetupRsp: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcSetupRsp: send message to cc.");

    return VOS_OK;


}



VOS_VOID MN_CALL_SendCcHoldReq(
    MN_CALL_ID_T                        callId
)
{
/*
    申请MNCC_HOLD_REQ原语
    if 申请失败
        返回 FAIL

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/

    MNCC_REQ_PARAM_UNION                *punParam;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_HOLD_REQ, &punParam);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcHoldReq: Failed to alloc Hold message.");
        return;
    }

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcHoldReq: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcHoldReq: send message to cc.");

    return;
}



VOS_VOID  MN_CALL_SendCcRetrieveReq(
    MN_CALL_ID_T                        callId
)
{
/*
    申请MNCC_RETRIEVE_REQ原语
    if 申请失败
        返回 FAIL

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/

    MNCC_REQ_PARAM_UNION                *punParam;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_RETRIEVE_REQ, &punParam);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcRetrieveReq: Failed to alloc Retrieve message.");
        return;
    }

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcRetrieveReq: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcRetrieveReq: send message to cc.");

    return;
}



VOS_VOID  MN_CALL_SendCcSimpleFacility(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_OPERATION_CODE_T         opCode
)
{
/*
    申请MNCC_FACILITY_REQ原语
    if 申请失败
        返回 FAIL

    根据输入参数填写payload中的stFac结构

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/
    NAS_CC_MSG_FACILITY_MO_STRU         *pstFac;
    MsgBlock                            *pMsg;
    MN_CALL_SS_COMPONENT_UNION          unComponent;
    VOS_UINT32                          ulLen;

    MN_INFO_LOG2("MN_CALL_SendCcSimpleFacility: callId, opCode", callId, opCode);

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_FACILITY_REQ, (MNCC_REQ_PARAM_UNION **)&pstFac);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcSimpleFacility: Failed to alloc Facility message.");
        return;
    }

    NAS_IE_SET_PRESENT(&pstFac->stFacility);

    /* 从6610的代码看，目前只有AOC有可能回复return result */
    #if 0
    if (opCode == MN_CALL_SS_AOC_OPERATION)
    {
        unComponent.ucCompType = MN_CALL_SS_RETURN_RESULT_TYPE_TAG;
        unComponent.resultComp.ucCompType = MN_CALL_SS_RETURN_RESULT_TYPE_TAG;
        unComponent.resultComp.ucOperateCode = MN_CALL_SS_AOC_OPERATION;

        /*此处暂时遗漏Invoke Id的填写*/
    }
    else
    #endif
    {
        unComponent.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
        unComponent.invokeComp.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
        unComponent.invokeComp.ucOperateCode = opCode;
        unComponent.invokeComp.bitOpLinkId = 0;
        if (VOS_OK != MN_CALL_InvokeIdAlloc(callId, &unComponent.invokeComp.ucInvokeId,
                                             opCode))
        {
            MN_ERR_LOG("MN_CALL_SendCcSimpleFacility: Invoke Id Alloc Fail.");
            return;
        }

    }

    ulLen = MN_CALL_FacilityEncode( pstFac->stFacility.aucFacility, &unComponent);

    /*是否填入SS version indicator,目前填1*/
    pstFac->stSSVersion.IsExist         = 1;
    pstFac->stSSVersion.LastOctOffset   = 1;
    pstFac->stSSVersion.Version         = 0;

    /*数据块中的数据长度为LV结构中的L的大小加上Tag的长度，也就是为L+1*/
    NAS_IE_SET_BLOCK_SIZE(&pstFac->stFacility, aucFacility, ulLen);

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcSimpleFacility: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcSimpleFacility: send message to cc.");

    return;



}



VOS_UINT32  MN_CALL_SendCcStartDtmfReq(
    MN_CALL_ID_T                        callId,
    VOS_INT8                            cKey
)
{
/*
    申请MNCC_START_DTMF_REQ原语
    if 申请失败
        返回 FAIL

    根据输入参数填写payload中的stStartDtmf结构

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/

    NAS_CC_MSG_START_DTMF_STRU          *pstDtmf = VOS_NULL_PTR;
    MsgBlock                            *pMsg    = VOS_NULL_PTR;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_START_DTMF_REQ, (MNCC_REQ_PARAM_UNION **)&pstDtmf);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcStartDtmfReq: Failed to alloc StartDtmf message.");
        return VOS_ERR;
    }

    /* 填写pstDtmf结构中的KeypadFacility值 */
    NAS_IE_SET_PRESENT(&pstDtmf->stKeypadFacility);
    pstDtmf->stKeypadFacility.KeypadInfo = (VOS_UINT8)cKey;


    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcStartDtmfReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcStartDtmfReq: send message to cc.");

    return VOS_OK;

}



VOS_UINT32  MN_CALL_SendCcStopDtmfReq(
    MN_CALL_ID_T                        callId
)
{
    MNCC_REQ_PARAM_UNION                *punParam;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_STOP_DTMF_REQ, &punParam);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcStopDtmfReq: Failed to alloc StopDtmf message.");
        return VOS_ERR;
    }

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcStopDtmfReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcStopDtmfReq: send message to cc.");
    return VOS_OK;

}


VOS_UINT32  MN_CALL_SendCcAlertReq(
    MN_CALL_ID_T                        callId
)
{
    /*申请MNCC_ALERT_REQ原语*/
    NAS_CC_MSG_ALERTING_MO_STRU         *pstAlert;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_ALERT_REQ, (MNCC_REQ_PARAM_UNION **)&pstAlert);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcRejReq: Failed to alloc CcRel message.");
        return VOS_ERR;
    }

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcRejReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcRejReq: send message to cc.");
    return VOS_OK;

}



VOS_VOID  MN_CALL_SendCcActCcbsReq(
    MN_CALL_ID_T                        callId
)
{
/*
    申请MNCC_REL_REQ原语
    if 申请失败
        返回 FAIL

    填写payload中stRel中的Facility IE

    发送原语
    if 发送失败
        释放申请的原语
        返回 FAIL
    else
        返回 OK
*/
       NAS_CC_MSG_RELEASE_MO_STRU          *pstRel;
       MsgBlock                            *pMsg;
       MN_CALL_SS_COMPONENT_UNION           unComponent;
       VOS_UINT32                           ulLen;

       pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_REL_REQ, (MNCC_REQ_PARAM_UNION **)&pstRel);
       if (VOS_NULL_PTR == pMsg)
       {
           MN_ERR_LOG("MN_CALL_SendCcActCcbsReq: Failed to alloc CcRel message.");
           return;
       }

       /* 填写pstRel结构中的facility值 */
       NAS_IE_SET_PRESENT(&pstRel->stFacility);
       unComponent.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
       unComponent.invokeComp.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
       unComponent.invokeComp.ucOperateCode = MN_CALL_SS_REG_CC_ENTRY_OPERATION;
       unComponent.invokeComp.bitOpLinkId = 0;
       if (VOS_OK != MN_CALL_InvokeIdAlloc(callId, &unComponent.invokeComp.ucInvokeId,
                                           MN_CALL_SS_REG_CC_ENTRY_OPERATION))
       {
            MN_ERR_LOG("MN_CALL_SendCcActCcbsReq: Invoke Id Alloc Fail.");
            return;
       }
       ulLen = MN_CALL_FacilityEncode(pstRel->stFacility.aucFacility, &unComponent);

       /*数据块中的数据长度为LV结构中的L的大小加上Tag的长度，也就是为L+1*/
       NAS_IE_SET_BLOCK_SIZE(&pstRel->stFacility, aucFacility, ulLen);
       NAS_IE_SET_PRESENT(&pstRel->stSSVersion);
       pstRel->stSSVersion.LastOctOffset = 1;
       pstRel->stSSVersion.Version = NAS_SS_VERSION_INDICATOR_PHASE2;

       /* 发送消息给CC */
       if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
       {
           MN_ERR_LOG("MN_CALL_SendCcActCcbsReq: Failed to send message.");
           return;
       }

       MN_NORM_LOG("MN_CALL_SendCcActCcbsReq: send message to cc.");

       return;

}

VOS_UINT32  MN_CALL_SendCcEstCnfReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU             *pstBc1,
    const NAS_CC_IE_BC_STRU             *pstBc2,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{

    NAS_CC_MSG_CC_EST_CNF_STRU          *pstCcEstCnf;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId,
                                      MNCC_EST_CNF_REQ,
                                      (MNCC_REQ_PARAM_UNION **)&pstCcEstCnf);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcEstCnfReq: Failed to alloc cc establishment cnf message.");
        return VOS_ERR;
    }

    /*填写pstCcEstCnf结构中的repeat indicator值*/
    MN_CALL_FillIeRepeatInd(enRepeatInd, &pstCcEstCnf->stRepeatInd);

    /* 填写pstCcEstCnf结构中的Cause值 */
    if(MN_CALL_INVALID_CAUSE != enCause)
    {
        MN_CALL_FillIeCause(enCause, &pstCcEstCnf->stCause);
    }

    /* 对BC1和BC2进行赋值 */
    pstCcEstCnf->stBC1 = *pstBc1;
    pstCcEstCnf->stBC2 = *pstBc2;

    MN_CALL_FillIeSupCodecList(&pstCcEstCnf->stCodecList);

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcEstCnfReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcEstCnfReq: send message to cc.");

    return VOS_OK;


}


VOS_UINT32  MN_CALL_SendCcbsSetupReq(
    MN_CALL_ID_T                        callId
)
{
    NAS_CC_MSG_SETUP_MO_STRU            *pstSetup;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_SETUP_REQ, (MNCC_REQ_PARAM_UNION**)&pstSetup);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcbsSetupReq: Failed to alloc setup message.");
        return VOS_ERR;
    }
    MN_CALL_GetCcbsSetup(pstSetup);

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcbsSetupReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcbsSetupReq: send message to cc.");
    return VOS_OK;

}



VOS_VOID MN_CALL_SendCcDeflectFacility(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstRedirNum
)
{
    NAS_CC_MSG_DISCONNECT_MO_STRU       *pstDiscMo;
    MsgBlock                            *pMsg;
    MN_CALL_SS_COMPONENT_UNION          unComponent;
    VOS_UINT32                          ulLen;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_DISC_REQ, (MNCC_REQ_PARAM_UNION **)&pstDiscMo);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcDeflectFacility: Failed to alloc StartDtmf message.");
        return;
    }

    /* 填写pstDiscMo结构中的Facility值 */
    PS_MEM_SET(&unComponent, 0, sizeof(unComponent));
    unComponent.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
    if (VOS_OK == MN_CALL_InvokeIdAlloc(callId, &unComponent.invokeComp.ucInvokeId,
                                        MN_CALL_SS_CD_OPERATION))
    {
        unComponent.invokeComp.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
        unComponent.invokeComp.ucOperateCode = MN_CALL_SS_CD_OPERATION;
        unComponent.invokeComp.bitOpArg = 1;
        unComponent.invokeComp.unArg.stCdArg.ucNumberLen = pstRedirNum->ucNumLen + sizeof(MN_CALL_NUM_TYPE_ENUM_U8);

        unComponent.invokeComp.unArg.stCdArg.aucNumber[0] = pstRedirNum->enNumType;
        PS_MEM_CPY(unComponent.invokeComp.unArg.stCdArg.aucNumber + 1,
                   pstRedirNum->aucBcdNum,
                   pstRedirNum->ucNumLen);


        NAS_IE_SET_PRESENT(&pstDiscMo->stFacility);
        ulLen = MN_CALL_FacilityEncode(pstDiscMo->stFacility.aucFacility, &unComponent);

        /*数据块中的数据长度为TLV结构中的V的长度*/
        NAS_IE_SET_BLOCK_SIZE(&pstDiscMo->stFacility,
                              aucFacility,
                              ulLen);
    }
    else
    {
        MN_ERR_LOG("MN_CALL_SendCcDeflectFacility: Failed to alloc Invoke Id.");
        return;
    }

    MN_CALL_FillIeCause(NAS_CC_CAUSE_127, &pstDiscMo->stCause);

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcDeflectFacility: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcDeflectFacility: send message to cc.");

    return;

}


VOS_UINT32  MN_CALL_SendCcBufferedSetupReq(
    MNCC_REQ_PRIM_MSG_STRU             *pstBufferdSetupMsg
)
{
    NAS_CC_MSG_SETUP_MO_STRU           *pstSetup = VOS_NULL_PTR;
    MsgBlock                           *pMsg     = VOS_NULL_PTR;

    /* 申请MNCC_SETUP_REQ原语 */
    pMsg = MN_CALL_AllocMnccPrimitive(pstBufferdSetupMsg->ucCallId,
                                      MNCC_SETUP_REQ,
                                      (MNCC_REQ_PARAM_UNION**)&pstSetup);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcBufferedSetupReq: Failed to alloc setup message.");
        return VOS_FALSE;
    }

    /* 填写redial标志  */
    ((MNCC_REQ_PRIM_MSG_STRU *)pMsg)->ucRedialFlg = VOS_TRUE;

    PS_MEM_CPY(pstSetup, &pstBufferdSetupMsg->unParam.stSetup, sizeof(NAS_CC_MSG_SETUP_MO_STRU));

    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcBufferedSetupReq: Failed to send message.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32  MN_CALL_SendCcBufferedEmgSetupReq(
    MNCC_REQ_PRIM_MSG_STRU             *pstBufferdEmgSetupMsg
)
{
    NAS_CC_MSG_EMERGENCY_STEUP_STRU    *pstEmgSetup = VOS_NULL_PTR;
    MsgBlock                           *pMsg        = VOS_NULL_PTR;

    /* 申请MNCC_SETUP_REQ原语 */
    pMsg = MN_CALL_AllocMnccPrimitive(pstBufferdEmgSetupMsg->ucCallId,
                                      MNCC_EMERG_SETUP_REQ,
                                      (MNCC_REQ_PARAM_UNION**)&pstEmgSetup);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcBufferedEmgSetupReq: Failed to alloc setup message.");
        return VOS_FALSE;
    }


    /* 填写redial标志  */
    ((MNCC_REQ_PRIM_MSG_STRU *)pMsg)->ucRedialFlg = VOS_TRUE;

    PS_MEM_CPY(pstEmgSetup, &pstBufferdEmgSetupMsg->unParam.stEmerg, sizeof(NAS_CC_MSG_EMERGENCY_STEUP_STRU));

    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcBufferedEmgSetupReq: Failed to send message.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}




VOS_VOID TAF_CALL_ProcCallStatusFail(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    /* 呼叫状态为active或held时，之前已经通知过cc setup_succ了，不需要再通知失败 */
    if ((MN_CALL_S_ACTIVE == enCallState)
     || (MN_CALL_S_HELD == enCallState))
    {
        return;
    }

    TAF_CALL_SendCcCallStatusNty(ucCallId, MNCC_CALL_STATUS_SETUP_FAIL);

    return;
}


VOS_VOID TAF_CALL_SendCcCallStatusNty(
    VOS_UINT8                           ucCallId,
    MNCC_CALL_STATUS_ENUM_UINT8         enCallStatus
)
{
    /* 通知MNCC_CALL_STATUS_NTY的点:
        1.电话接通时
        2.电话接通前失败，需要通知AT MN_CALL_EVT_RELEASE事件时
    */

    MNCC_CALL_STATUS_NTY_STRU          *pstCallStatusNty    = VOS_NULL_PTR;
    MsgBlock                           *pstMsg                = VOS_NULL_PTR;

    /* 申请MNCC_CALL_STATUS_NTY原语 */
    pstMsg = MN_CALL_AllocMnccPrimitive(ucCallId,
                                      MNCC_CALL_STATUS_NTY,
                                      (MNCC_REQ_PARAM_UNION**)&pstCallStatusNty);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_CALL_SendCcCallStatusNty: Failed to alloc call status nty message.");
        return;
    }

    pstCallStatusNty->enCallStatus  = enCallStatus;

    if (VOS_OK != MN_CALL_SendMnccPrimitive(pstMsg))
    {
        MN_ERR_LOG("TAF_CALL_SendCcCallStatusNty: Failed to send message.");
    }

    return;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID  TAF_CALL_SendCcSrvccCallInfoNtf(
    VOS_UINT8                           ucCallNum,
    MNCC_ENTITY_STATUS_STRU            *pstEntitySta
)
{
    VOS_UINT8                           i;
    MsgBlock                           *pMsg                = VOS_NULL_PTR;
    MNCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstSrvccCallInfoNtf = VOS_NULL_PTR;

    /* 申请MNCC_ALERT_REQ原语:call id对该消息来说是无效的,不用关注,因此填写为0 */
    pMsg = MN_CALL_AllocMnccPrimitive(0, MNCC_SRVCC_CALL_INFO_NOTIFY, (MNCC_REQ_PARAM_UNION **)&pstSrvccCallInfoNtf);

    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("TAF_CALL_SendCcSrvccCallInfoNtf: Failed to alloc CcRel message.");
        return;
    }

    /* 填充消息 */
    pstSrvccCallInfoNtf->ucCallNum = ucCallNum;

    for (i = 0; i < ucCallNum; i++)
    {
        PS_MEM_CPY(&(pstSrvccCallInfoNtf->astEntityStatus[i]), &pstEntitySta[i], sizeof(MNCC_ENTITY_STATUS_STRU));
    }

    if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
    {
        pstSrvccCallInfoNtf->ucTchAvail  = VOS_TRUE;
    }

    /* 发送消息给CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("TAF_CALL_SendCcSrvccCallInfoNtf: Failed to send message.");
        return;
    }

    MN_NORM_LOG("TAF_CALL_SendCcSrvccCallInfoNtf: send message to cc.");

    return;
}
#endif

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
