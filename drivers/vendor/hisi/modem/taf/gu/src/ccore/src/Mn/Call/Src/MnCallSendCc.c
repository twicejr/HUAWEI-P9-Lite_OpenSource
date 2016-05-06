/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallSendCc.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年9月20日
  最近修改   : 2007年9月20日
  功能描述   : 向CC发送MNCC原语
  函数列表   :
  修改历史   :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年6月12日
    作    者   : h44270
    修改内容   : modified for AT2D03670

  3.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/


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

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-21, begin */
#include "MnCallSendApp.h"
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-21, end */

/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */

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
/*****************************************************************************
 函 数 名  : MN_CALL_FillIeBc
 功能描述  :
 输入参数  : enCauseVal - 原因值
 输出参数  : pstCauseIe - 填好的Cause IE
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

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

/*****************************************************************************
 函 数 名  : MN_CALL_FillIeRepeatInd
 功能描述  :
 输入参数  : enCauseVal - 原因值
 输出参数  : pstRepeatInd - 填好的Cause IE
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_CALL_FillIeSupCodecList
 功能描述  : 填写支持的codec list列表
 输入参数  : 无
 输出参数  : pstCodecList - 支持的codec list
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年6月12日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年2月9日
    作    者   : z40661
    修改内容   : 从NVIM中获取支持的语音能力
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_FillIeLlc
 功能描述  :
 输入参数  : pstLLC1 - IE项LLC
 输出参数  : pstLLC1 - LLC的值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_FillIeCcCap
 功能描述  :
 输入参数  : pstCcCap - call control capability
 输出参数  : pstCcCap - call control capability赋值
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2013年04月17日
    作    者   : l65478
    修改内容   : DTS2013022007252:SETUP消息中没有包含CC capability

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_AllocMnccPrimitive
 功能描述  : 分配一条MNCC原语消息
 输入参数  : callId    - 原语中的CallId值
             enPrimName  - 原语名称
 输出参数  : ppunParam - 原语内容的存放位置(调用者用来填写原语内容)
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendMnccPrimitive
 功能描述  : 发送一条MNCC原语消息
 输入参数  : pMsg - 指项消息的首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  MN_CALL_SendMnccPrimitive(MsgBlock * pMsg)
{
    /*
    调用VOS_SendMsg发送消息
    */
    return PS_SEND_MSG(WUEPS_PID_TAF, pMsg);
}

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcSetupReq
 功能描述  : 发送MNCC_SETUP_REQ原语
 输入参数  : ucRepeatInd   - Repeat Indicator, 如果pstBc2为空该参数将被忽略
             pstBc1        - Bear capability 1
             pstBc2        - Bear capability 2 (可选)
             pstCallInfo   - 呼叫实体消息
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年09月18日
    作    者   : y00213812
    修改内容   : STK&DCM 项目增加带子地址的呼叫,重构该函数，以MN_CALL_MGMT_STRU
                 替代原有入参。
  3.日    期   : 2012年10月29日
    作    者   : l00198894
    修改内容   : DTS2012100901666: 修改被叫号码、被叫子地址
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年04月17日
    作    者   : l65478
    修改内容   : DTS2013022007252:SETUP消息中没有包含CC capability
  6.日    期   : 2014年4月22日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
  7.日    期   : 2015年8月13日
    作    者   : s00217060
    修改内容   : User_Exp_Improve：增加redial标志
*****************************************************************************/
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

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-15, begin */
    /* 如果支持呼叫重建功能，则缓存setup的消息 */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(pstCallInfo->stCallInfo.callId))
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-15, end */
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcEmergSetupReq
 功能描述  : 发送MNCC_EMERG_SETUP_REQ原语
 输入参数  : CallId        - 呼叫的ID
             ucCategory    - 紧急呼叫种类
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数

  2.日    期   : 2010年5月22日
    作    者   : o00132663
    修改内容   : AT2D19371,紧急呼过程中G->W切换掉话。
  3.日    期   : 2012年02月24日
    作    者   : 傅映君/f62575
    修改内容   : C50_IPC Project    为适配FDN业务删除了输入参数const NAS_CC_IE_BC_STRU             *pstBc

  4.日    期   : 2012年9月25日
    作    者   : A00165503
    修改内容   : STK&DCM项目: CS域错误码上报
  5.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  6.日    期   : 2012年12月13日
    作    者   : l65478
    修改内容   : DTS2012120706360:没有包含supported codec，GCF测试失败
  7.日    期   : 2015年8月15日
    作    者   : s00217060
    修改内容   : User_Exp_Improve修改：新增redial标志
*****************************************************************************/
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
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-15, begin */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(callId))
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-15, end */
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcCallConfReq
 功能描述  : 发送MNCC_CALL_CONF_REQ原语
 输入参数  : CallId        - 呼叫的ID
             ucRepeatInd   - Repeat Indicator, 如果pstBc2为空该参数将被忽略
             pstBc1        - Bear capability 1 (可选)
             pstBc2        - Bear capability 2 (可选), 如果pstBc1为空该参数将被忽略
             Cause         - 原因值
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2008年6月12日
    作    者   : h44270
    修改内容   : modified for AT2D03670
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcDiscReq
 功能描述  : 发送MNCC_DISC_REQ原语(不携带Facility)
 输入参数  : CallId        - 呼叫的ID
             Cause         - 挂断的原因
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目新增函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcRelReq
 功能描述  : 发送MNCC_REL_REQ原语(不携带Facility)
 输入参数  : CallId        - 呼叫的ID
             Cause         - 挂断的原因
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目新增函数
  3.日    期   : 2013年01月29日
    作    者   : Y00213812
    修改内容   : DTS2013012909872,记录CALL挂断的方向
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcRejReq
 功能描述  : 发送MNCC_REJ_REQ原语
 输入参数  : CallId        - 呼叫的ID
             Cause         - 拒绝的原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目新增函数
  3.日    期   : 2013年01月29日
    作    者   : Y00213812
    修改内容   : DTS2013012909872,记录CALL挂断的方向
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcSetupRsp
 功能描述  : 发送MNCC_SETUP_RES原语
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年5月8日
    作    者   : z00161729
    修改内容   : 修改问题单AT2D19265:增加清除f_stWaitSendAlert.bWaitSendAlertStatus
  3.日    期   : 2010年7月21日
    作    者   : h44270
    修改内容   : 修改问题单DTS2010062601120
  4.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcHoldReq
 功能描述  : 发送MNCC_HOLD_REQ原语
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcRetrieveReq
 功能描述  : 发送MNCC_RETRIEVE_REQ原语
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcSimpleFacility
 功能描述  : 发送简单的MNCC_FACILITY_REQ原语(除Operation Code之外没有其它参数)
 输入参数  : CallId - 呼叫的ID
             OpCode - Operation Code
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2014年8月7日
    作    者   : w00242748
    修改内容   : DTS2014080700610:不带版本号的话，兼容性差的网络会直接将ECT发送的
                 facility直接给拒绝
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcStartDtmfReq
 功能描述  : 发送MNCC_START_DTMF_REQ原语
 输入参数  : CallId - 呼叫的ID
             ucKey  - 要发送的DTMF按键
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcStopDtmfReq
 功能描述  : 发送MNCC_STOP_DTMF_REQ原语
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcAlertReq
 功能描述  : 发送MNCC_ALERT_REQ原语
 输入参数  : CallId        - 呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcActCcbsReq
 功能描述  : 发送MNCC_REL_REQ原语, 其中携带激活CCBS业务的Facility IE
 输入参数  : CallId - 呼叫的ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   :新生成函数
*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : MN_CALL_SendCcEstCnfReq
 功能描述  : 发送MNCC_CC_EST_CNF_REQ原语
 输入参数  : CallId        - 呼叫的ID
             ucRepeatInd   - Repeat Indicator, 如果pstBc2为空该参数将被忽略
             pstBc1        - Bear capability 1 (可选)
             pstBc2        - Bear capability 2 (可选), 如果pstBc1为空该参数将被忽略
             Cause         - 原因值
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功, VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   :新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcbsSetupReq
 功能描述  : 发送MNCC_SETUP_REQ原语
 输入参数  : CallId        - 呼叫的ID
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功
             VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-12-25
    作    者   : z00161729
    修改内容   :新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : MN_CALL_SendCcDeflectFacility
 功能描述  : 发送MNCC_DISC_REQ原语, 其中携带激活呼叫偏转业务的Facility IE
 输入参数  : CallId      - 呼叫的ID
             pstRedirNum - 偏转号码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcBufferedSetupReq
 功能描述  : 呼叫重建发送缓存的setup消息
 输入参数  : pstBufferdSetupMsg - 缓存的setup消息
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功
             VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2015年8月13日
    作    者   : s00217060
    修改内容   : User_Exp_Improve修改：增加redial标志

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : MN_CALL_SendCcBufferedEmgSetupReq
 功能描述  : 呼叫重建发送缓存的紧急呼叫的setup消息
 输入参数  : pstBufferdSetupMsg - 缓存的紧急呼叫的setup消息
 输出参数  : 无
 返 回 值  : VOS_OK - 发送成功
             VOS_ERR - 发送失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2015年8月15日
    作    者   : s00217060
    修改内容   : User_Exp_Improve修改：新增redial标志

*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : TAF_CALL_ProcCallStatusFail
 功能描述  : 电话挂断时通知底层呼叫建立失败
 输入参数  : VOS_UINT8                           ucCallId
             MN_CALL_STATE_ENUM_U8               enCallState
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月21日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_SendCcCallStatusNty
 功能描述  : 通知CC呼叫建立状态
 输入参数  : VOS_UINT8                           ucCallId,
             MNCC_CALL_STATUS_ENUM_UINT8         enCallStatus
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月14日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
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

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_CALL_SendCcSrvccCallInfoNtf
 功能描述  : 向CC模块发送MNCC_SRVCC_CALL_INFO_NOTIFY消息
 输入参数  : pstEntitySta - 呼叫实体信息
             ucCallNum    - 呼叫实体个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
