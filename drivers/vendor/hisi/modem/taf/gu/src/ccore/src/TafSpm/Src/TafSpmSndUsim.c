/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmSndUsim.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : TafSpmSndUsim.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月22日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafLog.h"
#include "TafSpmSndUsim.h"
#include "siappstk.h"
#include "UsimPsInterface.h"
#include "TafSpmMntn.h"
#include "TafMmiEncode.h"
#include "TafSdcCtx.h"
#include "MnErrorCode.h"
#include "TafStdlib.h"
#include "MnMsgApi.h"
/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
#include "mnmsgcbencdec.h"
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

#include "NasUsimmApi.h"

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, begin */
#include "NasCcIe.h"
#include "MnCallBcProc.h"
#include "TafSpmComFunc.h"
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_SND_USIM_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_SPM_SendUsimSsEnvelopeReq
 功能描述  : 调用USIMAPI发送SS业务请求的envelope消息 请求进行call ctrl结果
 输入参数  : usClientId:状态机的client ID
             pstMsg     待CALL CONTROL的SS业务请求消息
 输出参数  : 无
 返 回 值  : VOS_TRUE            发起SS的call ctrl检查请求成功
             VOS_FALSE           发起SS的call ctrl检查请求失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
  3.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32  TAF_SPM_SendUsimSsEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           aucLI[MN_MO_CTRL_LAI_LEN];
    VOS_UINT8                           aucSsString[TAF_SPM_CALL_CTRL_SS_STRING_LEN];
    VOS_UINT8                           ucSscStringBcdLen;
    SI_STK_ENVELOPE_STRU                stEnvelopeMsg;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcSscString     = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppReq       = VOS_NULL_PTR;
    MN_APP_SS_REGISTER_REQ_STRU        *pstRegister     = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;

    pcSscString = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SPM_SSC_MAX_LEN);

    if (VOS_NULL_PTR == pcSscString)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimSsEnvelopeReq: Fail to alloc memory for SS info.");
        return VOS_FALSE;
    }

    PS_MEM_SET(pcSscString, 0, TAF_SPM_SSC_MAX_LEN);
    /* 根据消息转换出SSC STRING */
    ulRet        = TAF_MmiEncodeMmiString(pstMsg, pcSscString);
    if (VOS_TRUE != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimSsEnvelopeReq: Fail to Encode SSC string.");
        PS_MEM_FREE(WUEPS_PID_TAF, pcSscString);
        return VOS_FALSE;
    }

    /*
    SS STRING的第一个字节是TON and NPI，从第二字节开始为SSC 的BCD编码
    参考协议 11.11: 10.5.1  EFADN (Abbreviated dialling numbers)
    TON and NPI
    Contents:
        Type of number (TON) and numbering plan identification (NPI).
    Coding:
        according to TS 04.08 [15]. If the Dialling Number/SSC String does not contain a dialling number,
        e.g. a control string deactivating a service, the TON/NPI byte shall be set to 'FF' by the ME (see note 2).
    NOTE 2: If a dialling number is absent, no TON/NPI byte is transmitted over the radio interface (see TS 04.08 [15]).
        Accordingly, the ME should not interpret the value 'FF' and not send it over the radio interface.
    */
    PS_MEM_SET(aucSsString, 0, TAF_SPM_CALL_CTRL_SS_STRING_LEN);
    aucSsString[0] = TAF_SPM_NUM_TYPE_INVALID;
    pstAppReq = (MN_APP_REQ_MSG_STRU *)pstMsg;
    ulEventType = TAF_BuildEventType(pstAppReq->ulSenderPid, pstAppReq->usMsgName);
    ulRet = TAF_MmiGetOperationType(ulEventType, &enSsOpType);
    if ((VOS_TRUE == ulRet)
     && (TAF_MMI_REGISTER_SS == enSsOpType))
    {
        pstRegister    = (MN_APP_SS_REGISTER_REQ_STRU *)pstMsg;
        /* 仅呼叫转移有注册操作，呼叫转移注册操作必须有号码类型 */
        aucSsString[0] = pstRegister->stTafSsRegisterSsReq.NumType;
    }

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertAsciiNumberToBcd(pcSscString,
                                &aucSsString[TAF_SPM_SSC_OFFSET],
                                &ucSscStringBcdLen);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    PS_MEM_FREE(WUEPS_PID_TAF, pcSscString);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stEnvelopeMsg, 0, sizeof(SI_STK_ENVELOPE_STRU));
    PS_MEM_SET(aucLI, 0, MN_MO_CTRL_LAI_LEN);

    /*
    3GPP 1114:
    9.1.6   Structure of ENVELOPE (CALL CONTROL)
    Description                         Section M/O Min Length
    Call control tag                    13.1    M   Y   1
    Length (A+B+C+D+E+F)                -       M   Y   1 or 2
    Device identities                   12.7    M   Y   A
    Address or SS string or USSD string 12.1,   M   Y   B
                                        12.14
                                        or 12.17
    Location information                12.19   M   N   E
    其中，
    Location information 通过TAF_SDC_GetCurrentLai获取
    Call control tag对应stEnvelopeMsg.EnvelopeType
    Device identities对应stEnvelopeMsg.DeviceId
    Address or SS string or USSD string这里是SS string，参考协议1114 12.14
    */
    stEnvelopeMsg.enEnvelopeType    = SI_STK_ENVELOPE_CALLCRTL;
    stEnvelopeMsg.DeviceId.ucSDId   = SI_STK_DEV_TERMINAL;
    stEnvelopeMsg.DeviceId.ucDDId   = SI_STK_DEV_UICC;

    /*
        12.14    SS string
        SS or USSD string:
        for SS:
            Byte(s)                 Description         Length
            1                       SS string tag           1
            2 to (Y 1)+2            Length (X)              Y
            (Y 1)+3                 TON and NPI             1
            (Y 1)+4 to (Y 1)+X+2    SS or USSD string   X - 1
        其中，
        SS string tag对应stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag
        Length对应stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen
        TON and NPI和SS string对应stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue
    */
    stEnvelopeMsg.uEnvelope.CallCtrl.OP_SepcialData          = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag       = SI_CC_SS_TAG;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen       = (VOS_UINT8)(ucSscStringBcdLen + TAF_SPM_SSC_OFFSET);
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue      = aucSsString;

    /* 获取ENVELOPE消息参数: 服务小区信息 */
    stEnvelopeMsg.uEnvelope.CallCtrl.OP_LocInfo              = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.pucATSLI        = aucLI;
    TAF_SDC_Get3GppCurrentLai(aucLI, &stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.ulLen);

    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, usClientId, &stEnvelopeMsg);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimSsEnvelopeReq: Usim Returns Error.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_BuildUssdStringInfo
 功能描述  : 根据编码方式构造USSD STRING
 输入参数  : TAF_SS_DATA_CODING_SCHEME           ucDatacodingScheme
             TAF_SS_USSD_STRING_STRU            *pstSrcUssd
 输出参数  : TAF_SS_USSD_STRING_STRU            *pstDstUssd
 返 回 值  : VOS_TRUE            构造DCS指示格式USSD结构成功
             VOS_FALSE           构造DCS指示格式USSD结构失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
*****************************************************************************/
VOS_UINT32 TAF_SPM_BuildUssdStringInfo(
    TAF_SS_DATA_CODING_SCHEME           ucDatacodingScheme,
    TAF_SS_USSD_STRING_STRU            *pstSrcUssd,
    TAF_SS_USSD_STRING_STRU            *pstDstUssd
)
{
    VOS_UINT32                          ulRslt;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;

    PS_MEM_SET(&stDcsInfo, 0, sizeof(stDcsInfo));

    /* USSD与CBS的DCS的协议相同，调用CBS的DCS解析函数解码，详细情况参考23038 */
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    ulRslt = MN_MSG_DecodeCbsDcs(ucDatacodingScheme,
                                 pstSrcUssd->aucUssdStr,
                                 pstSrcUssd->usCnt,
                                 &stDcsInfo);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    if (MN_ERR_NO_ERROR != ulRslt)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo:WARNING: Decode Failure");
        return VOS_FALSE;
    }

    if (MN_MSG_MSG_CODING_7_BIT == stDcsInfo.enMsgCoding)
    {
        PS_MEM_CPY(pstDstUssd, pstSrcUssd, sizeof(TAF_SS_USSD_STRING_STRU));

        /* 非透传模式，编码方式为7bit时，上层是没有按7Bit压缩的，
           仍然是ASCII，此处需要保证DCS指示的编码方式与实际内容的编码方式一致 */
        if (TAF_SDC_USSD_NON_TRAN_MODE == TAF_SDC_GetUssdTransMode())
        {
            ulRslt = TAF_MmiEncodeUssdMessage(pstDstUssd);
            if (VOS_FALSE == ulRslt)
            {
                TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo: SSA_EncodeUssdMessage encode failure");
                return VOS_FALSE;
            }
        }
        /* 透传模式，编码方式为7bit时，上层是按7Bit压缩的，但用户输入每一个USSD数字，
           经过7Bit压缩后， 每个字节的高4bit和低4bit在此处是分别由一个Byte表示的，此处需要将两个byte还原为一个字节
           例如用户要输入*199#,7bit压缩后为aa 58 2e 37 02，拆分后为61 61 35 38 32 65 33 37 30 32
            */
        else
        {
            if (pstDstUssd->usCnt > TAF_SS_MAX_USSD_CHAR_HEX_FORMAT)
            {
                TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo: String too Long failure");
                return VOS_FALSE;
            }

            ulRslt = TAF_STD_AsciiNum2HexString(pstDstUssd->aucUssdStr, &pstDstUssd->usCnt);

            if (VOS_FALSE == ulRslt)
            {
                TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo: TAF_AsciiNum2HexString encode failure");
                return VOS_FALSE;
            }
        }
    }
    else
    {
        if (pstSrcUssd->usCnt > TAF_SS_MAX_USS_CHAR)
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo: String too Long failure");
            return VOS_FALSE;
        }

        PS_MEM_CPY(pstDstUssd, pstSrcUssd, sizeof(TAF_SS_USSD_STRING_STRU));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SendUsimUssdEnvelopeReq
 功能描述  : 调用USIMAPI发送USSD业务请求的envelope消息 请求进行call ctrl结果
 输入参数  : usClientId:状态机的client ID
             pstMsg     待CALL CONTROL的USSD业务请求消息
 输出参数  : 无
 返 回 值  : VOS_TRUE            发起USSD的call ctrl检查请求成功
             VOS_FALSE           发起USSD的call ctrl检查请求失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
*****************************************************************************/
VOS_UINT32  TAF_SPM_SendUsimUssdEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           aucLI[MN_MO_CTRL_LAI_LEN];
    SI_STK_ENVELOPE_STRU                stEnvelopeMsg;
    VOS_UINT32                          ulRet;
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    TAF_SS_PROCESS_USS_REQ_STRU        *pstUssdMsg      = VOS_NULL_PTR;
    TAF_SS_USSD_STRING_STRU            *pstUssdInfo     = VOS_NULL_PTR;
    VOS_UINT8                           aucCallCtrlUssdString[TAF_SPM_CALL_CTRL_USSD_STRING_LEN];

    PS_MEM_SET(aucCallCtrlUssdString, 0, sizeof(aucCallCtrlUssdString));

    pstUssdInfo = PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_SS_USSD_STRING_STRU));

    if (VOS_NULL_PTR == pstUssdInfo)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimUssdEnvelopeReq: Fail to alloc memory for USSD string.");
        return VOS_FALSE;
    }

    PS_MEM_SET(pstUssdInfo, 0, sizeof(TAF_SS_USSD_STRING_STRU));

    pstAppMsg                = (MN_APP_REQ_MSG_STRU *)pstMsg;
    pstUssdMsg               = (TAF_SS_PROCESS_USS_REQ_STRU *)pstAppMsg->aucContent;
    aucCallCtrlUssdString[0] = pstUssdMsg->DatacodingScheme;

    /* 转换用户请求中的USSD字符串为空口消息的USSD码流  */
    ulRet = TAF_SPM_BuildUssdStringInfo(pstUssdMsg->DatacodingScheme,
                                        &pstUssdMsg->UssdStr,
                                        pstUssdInfo);
    if (VOS_FALSE == ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstUssdInfo);
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimUssdEnvelopeReq: Fail to TAF_SPM_BuildUssdStringInfo.");
        return VOS_FALSE;
    }

    PS_MEM_CPY(&aucCallCtrlUssdString[TAF_SPM_SSC_OFFSET], pstUssdInfo->aucUssdStr, pstUssdInfo->usCnt);

    /*
    3GPP 1114:
    9.1.6   Structure of ENVELOPE (CALL CONTROL)
    Description                         Section M/O Min Length
    Call control tag                    13.1    M   Y   1
    Length (A+B+C+D+E+F)                -       M   Y   1 or 2
    Device identities                   12.7    M   Y   A
    Address or SS string or USSD string 12.1,   M   Y   B
                                        12.14
                                        or 12.17
    Location information                12.19   M   N   E
    其中，
    Location information 通过TAF_SDC_GetCurrentLai获取
    Call control tag对应stEnvelopeMsg.EnvelopeType
    Device identities对应stEnvelopeMsg.DeviceId
    Address or SS string or USSD string这里是USSD string，参考协议1114 12.17
    */
    PS_MEM_SET(&stEnvelopeMsg, 0, sizeof(SI_STK_ENVELOPE_STRU));

    stEnvelopeMsg.enEnvelopeType    = SI_STK_ENVELOPE_CALLCRTL;
    stEnvelopeMsg.DeviceId.ucSDId   = SI_STK_DEV_TERMINAL;
    stEnvelopeMsg.DeviceId.ucDDId   = SI_STK_DEV_UICC;

    /*
        3GPP 1114:
        12.17    USSD string
        for USSD:
            Byte(s)                 Description         Length
            1                       USSD string tag         1
            2 to (Y-1)+2            Length (X)              Y
            (Y-1)+3                 Data coding scheme      1
            (Y-1)+4 to (Y-1)+X+2    USSD string           X-1
        其中，
        USSD string tag对应stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag
        Length对应stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen
        Data coding scheme和USSD string对应stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue
    */
    stEnvelopeMsg.uEnvelope.CallCtrl.OP_SepcialData          = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag       = SI_CC_USSD_TAG;

    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen       = (VOS_UINT8)(sizeof(pstUssdMsg->DatacodingScheme)
                                                             + pstUssdInfo->usCnt);
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue      = (SI_UINT8 *)aucCallCtrlUssdString;

    /* 获取ENVELOPE消息参数: 服务小区信息 */
    stEnvelopeMsg.uEnvelope.CallCtrl.OP_LocInfo              = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.pucATSLI        = aucLI;
    TAF_SDC_Get3GppCurrentLai(aucLI, &stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.ulLen);

    PS_MEM_FREE(WUEPS_PID_TAF, pstUssdInfo);

    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, usClientId, &stEnvelopeMsg);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimUssdEnvelopeReq: Usim Returns Error.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_BuildSsFdnInfo
 功能描述  : 构造SS的FDN信息
 输入参数  : pstMsg:at或STK发过来的SS请求消息
 输出参数  : pstFdnInfo:构造好的SS的FDN信息
 返 回 值  : VOS_TRUE            构造消息成功
             VOS_FALSE           构造消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月22日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32  TAF_SPM_BuildSsFdnInfo(
    struct MsgCB                       *pstMsg,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcMmiStr       = VOS_NULL_PTR;

    /* 根据消息转换出SSC STRING */
    pcMmiStr   = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SPM_SSC_MAX_LEN);

    if (VOS_NULL_PTR == pcMmiStr)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildSsFdnInfo: Fail to alloc memory for encode SSC.");
        return VOS_FALSE;
    }

    PS_MEM_SET(pcMmiStr, 0, TAF_SPM_SSC_MAX_LEN);
    ulRet          = TAF_MmiEncodeMmiString(pstMsg, pcMmiStr);

    if (VOS_TRUE != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildSsFdnInfo: Fail to Encode SSC string.");
        PS_MEM_FREE(WUEPS_PID_TAF, pcMmiStr);

        return VOS_FALSE;
    }

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertAsciiNumberToBcd(pcMmiStr, pstFdnInfo->aucNum1, (VOS_UINT8 *)&(pstFdnInfo->ulNum1Len));
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    PS_MEM_FREE(WUEPS_PID_TAF, pcMmiStr);

    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_SendPbSsFdnCheckReq
 功能描述  : 调用PB的API发起SS的FDN检查请求
 输入参数  : usClientId:状态机的client ID
             pstMsg:SS业务请求消息
 返 回 值  : VOS_TRUE            发起SS的FDN检查请求成功
             VOS_FALSE           发起SS的FDN检查请求失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
*****************************************************************************/
VOS_UINT32  TAF_SPM_SendPbSsFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    SI_PB_FDN_NUM_STRU                  stFdnInfo;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stFdnInfo, 0x00, sizeof(stFdnInfo));
    ulRet = TAF_SPM_BuildSsFdnInfo(pstMsg, &stFdnInfo);

    if (VOS_FALSE == ulRet)
    {
        return VOS_FALSE;
    }


    ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, usClientId, &stFdnInfo);


    if (VOS_OK != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetUssdStringSeptetLength
 功能描述  : 获取USSD 7位位组长度
 输入参数  : ulOctetLength USSD STRING的8位位组长度
             ucLastByte    USSD STRING的8位位组最后一个字节
 输出参数  : 无
 返 回 值  : USSD 7位位组长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetUssdStringSeptetLength(
    VOS_UINT32                          ulOctetLength,
    VOS_UINT8                           ucLastByte
)
{
    VOS_UINT16                          usFillBit;
    VOS_UINT32                          ulSeptetLength;

    /*
    23038 6.1.2.3 USSD packing
    If the total number of characters to be sent equals (8n-1) where n=1,2,3 etc.
    then there are 7 spare bits at the end of the message. To avoid the situation
    where the receiving entity confuses 7 binary zero pad bits as the @ character,
    the carriage return or <CR> character (defined in clause 6.1.1) shall be used
    for padding in this situation, just as for Cell Broadcast.
    USSD 7BIT压缩方式下，若8位位组的冗余BIT数是1个7位位组的BIT数，协议要求填充CR
    计算USSD的7位位组数时需要去除无效的CR占用的1个7位位组
    */
    ulSeptetLength = (VOS_UINT32)((TAF_SDC_BITS_PER_OCTET * ulOctetLength) / TAF_SDC_BITS_PER_SEPTET);
    usFillBit      = (VOS_UINT32)((TAF_SDC_BITS_PER_OCTET * ulOctetLength) % TAF_SDC_BITS_PER_SEPTET);
    if (0 == usFillBit)
    {
        if (TAF_SDC_USSD_7BIT_PAD == (ucLastByte & TAF_SDC_USSD_7BIT_PAD))
        {
            ulSeptetLength--;
        }
    }

    return ulSeptetLength;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_TransUssdMsgToAsciiStr
 功能描述  : 完成SS的7BIT压缩编码后的ASCII码字符串到ASCII码流的转换
 输入参数  : pstUssdMsg---需要转换的USSD消息
 输出参数  : pucAsciiStr     - ASCII码流
             pulUnpackStrLen - ASCII码流长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目，
                 TAF_SPM_TransUssdMsgToAsciiStr => TAF_SDC_TransUssdMsgToAsciiStr
                 扩展功能为公共接口，不限制在FDN使用
  3.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  4.日    期   : 2013年10月11日
    作    者   : z00161729
    修改内容  : DTS2013071808373:TQE告警清理
*****************************************************************************/
VOS_UINT32 TAF_SPM_TransUssdMsgToAsciiStr(
    TAF_SS_PROCESS_USS_REQ_STRU        *pstUssdMsg,
    VOS_UINT8                          *pucAsciiStr,
    VOS_UINT32                         *pulAsciiStrLength
)
{
    VOS_UINT8                          *pucUssdStr          = VOS_NULL_PTR;
    VOS_UINT8                          *pucUssdTransTbl     = VOS_NULL_PTR;
    VOS_UINT8                           aucUnpackUssdStr[TAF_SS_MAX_USSDSTRING_LEN];
    VOS_UINT32                          ulUssdStrLength;
    VOS_UINT32                          ulUnpackUssdStrLength;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;

    PS_MEM_SET(&stDcsInfo, 0, sizeof(stDcsInfo));

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    ulRet = MN_MSG_DecodeCbsDcs(pstUssdMsg->DatacodingScheme,
                                pstUssdMsg->UssdStr.aucUssdStr,
                                pstUssdMsg->UssdStr.usCnt,
                                &stDcsInfo);
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    if (MN_ERR_NO_ERROR != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr:WARNING: Decode Failure");
        return VOS_FALSE;
    }

    /*
       非透传模式或非7BIT编码，TAF接收到的用户USSD字符串编码格式为ASCII码或UCS2码流，
       不需要转换，直接拷贝到输出参数
    */
    if ((TAF_SDC_USSD_TRAN_MODE != TAF_SDC_GetUssdTransMode())
     || (MN_MSG_MSG_CODING_7_BIT != stDcsInfo.enMsgCoding))
    {
        if (pstUssdMsg->UssdStr.usCnt > TAF_SS_MAX_USSDSTRING_LEN)
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr: USSD length overflow in none transparent mode.");
            return VOS_FALSE;
        }

        *pulAsciiStrLength  = pstUssdMsg->UssdStr.usCnt;

         PS_MEM_CPY(pucAsciiStr, pstUssdMsg->UssdStr.aucUssdStr, *pulAsciiStrLength);

        return VOS_TRUE;
    }

    /*
       这段代码完成从7BIT压缩编码的数字字符串到ASCII码流的转换
       透传模式并且DCS为7bit编码格式，用户输入每一个USSD数字，经过7Bit压缩后，
       每个字节的高4bit和低4bit在此处是分别由一个Byte表示的
       TAF接收到的用户USSD字符串就是2个字符表示一个数字，最大长度为320字符，
       USSD空口码流容量为160BYTE，160BYTE 传输7BIT编码的字符，可以传输182个字符，

       示例:
       用户输入*199#的情况，应用接收到ASCII码流2A 31 39 39 23，进行7BIT编码后为
       aa 58 2e 37 02，转换为数字字符串为61 61 35 38 32 65 33 37 30 32，通过AT命令
       AT+CUSD=1,"61613538326533373032",15 AT透传"61613538326533373032"到TAF，所以
       本函数输入: 61 61 35 38 32 65 33 37 30 32
       本函数输出: ASCII码流为2A 31 39 39 23，长度为5
       实现步骤:
       1) TAF_AsciiNum2HexStr: 61 61 35 38 32 65 33 37 30 32 => aa 58 2e 37 02
       2) MN_UnPack7Bit:          aa 58 2e 37 02                => 2A 31 39 39 23
       因为此处的ASCII码属于标准ASCII码，所以USSD的字符转换表对输出字符串无影响

       16进制表示的USSD码流字符串转换为16进制表示的USSD码流
       举例说明:
       16进制表示的7BIT字符表压缩编码的USSD码流字符串 0x61 0x61 0x35 0x38 0x32 0x65 0x33 0x37 0x30 0x32
       转换成
               16进制表示的7BIT字符表压缩编码的码流 0xaa 0x58 0x2e 0x37 0x02
       其中，0x61表示ASCII码的a 0x65表示ASCII码的e
    */
    if (pstUssdMsg->UssdStr.usCnt > TAF_SS_MAX_USSD_CHAR_HEX_FORMAT)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr: USSD length overflow in transparent mode.");
        return VOS_FALSE;
    }

    pucUssdStr = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SS_MAX_USSD_CHAR_HEX_FORMAT);
    if (VOS_NULL_PTR == pucUssdStr)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr: Fail to alloc memory.");
        return VOS_FALSE;
    }

    PS_MEM_SET(pucUssdStr, 0, TAF_SS_MAX_USSD_CHAR_HEX_FORMAT);

    ulUssdStrLength = pstUssdMsg->UssdStr.usCnt;
    PS_MEM_CPY(pucUssdStr, pstUssdMsg->UssdStr.aucUssdStr, pstUssdMsg->UssdStr.usCnt);
    ulRet = TAF_STD_AsciiNum2HexString(pucUssdStr, (VOS_UINT16 *)&ulUssdStrLength);
    if (VOS_FALSE == ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr: Fail to TAF_AsciiNum2HexString.");
        PS_MEM_FREE(WUEPS_PID_TAF, pucUssdStr);
        return VOS_FALSE;
    }

    /*
    16进制表示的7BIT字符表压缩编码USSD码流转换成7BIT字符表非压缩编码USSD码流
    举例说明:
          16进制表示的7BIT字符表压缩编码USSD码流 0xaa 0x58 0x2e 0x37 0x02
    转换成
          7BIT字符表非压缩编码USSD码流           0x2A 0x31 0x39 0x39 0x23
    */
    /*lint -e961*/
    ulUnpackUssdStrLength = TAF_SPM_GetUssdStringSeptetLength(ulUssdStrLength,
                                            *(pucUssdStr + ulUssdStrLength - 1));
    /*lint +e961*/

    PS_MEM_SET(aucUnpackUssdStr, 0, sizeof(aucUnpackUssdStr));
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    /* Added by b00269685 for Coverify清理, 2014-7-24, begin */
    if (ulUssdStrLength > TAF_SS_MAX_USSDSTRING_LEN)
    {
        ulUssdStrLength = TAF_SS_MAX_USSDSTRING_LEN;
    }
    /* Added by b00269685 for Coverify清理, 2014-7-24, end */
    ulRet = TAF_STD_UnPack7Bit(pucUssdStr, ulUssdStrLength, 0, aucUnpackUssdStr);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr:TAF_STD_UnPack7Bit Err.");
    }
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
    PS_MEM_FREE(WUEPS_PID_TAF, pucUssdStr);

    /*
    7BIT字符表非压缩编码USSD码流转换成ASCII码字符表编码的码流
    示例中不涉及7BIT字符表和ASCII码字符表存在差异的字符，所以无变化
    */
    pucUssdTransTbl = TAF_SDC_GetCurr7BitToAsciiTableAddr();
    for (i = 0; i < ulUnpackUssdStrLength; i++)
    {
        pucAsciiStr[i]  = pucUssdTransTbl[aucUnpackUssdStr[i]];
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_BuildUssdFdnInfo
 功能描述  : 构造USSD的FDN信息
 输入参数  : pstMsg:at或STK发过来的ussd请求消息
 输出参数  : pstFdnInfo:构造好的ussd的FDN信息
 返 回 值  : VOS_TRUE            构造消息成功
             VOS_FALSE           构造消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月22日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年12月24日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32  TAF_SPM_BuildUssdFdnInfo(
    struct MsgCB                       *pstMsg,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
)
{
    VOS_UINT32                          ulAsciiStrLen;
    VOS_UINT8                          *pucAsciiStr = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 调用转换函数获取ASCII格式的字符串 */
    pucAsciiStr = PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SS_MAX_USSDSTRING_LEN);
    if (VOS_NULL_PTR == pucAsciiStr)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdFdnInfo: Fail to alloc memory.");
        return VOS_FALSE;
    }

    pstAppMsg       = (MN_APP_REQ_MSG_STRU *)pstMsg;

    ulAsciiStrLen  = 0;
    PS_MEM_SET(pucAsciiStr,  0, TAF_SS_MAX_USSDSTRING_LEN);

    ulRet = TAF_SPM_TransUssdMsgToAsciiStr((TAF_SS_PROCESS_USS_REQ_STRU*)pstAppMsg->aucContent,
                                            pucAsciiStr,
                                            &ulAsciiStrLen);
    if (VOS_FALSE == ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pucAsciiStr);
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdFdnInfo: Fail to TAF_SDC_TransUssdMsgToAsciiStr.");
        return VOS_FALSE;
    }

    /* FDN中的num1只能保存40个ascii码 */
    PS_MEM_SET(pucAsciiStr + TAF_SPM_FDN_CHECK_STR_MAX_LEN, 0, TAF_SPM_FDN_CHECK_7BIT_MAX_LEN - TAF_SPM_FDN_CHECK_STR_MAX_LEN);

    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, begin */
    ulRet = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)pucAsciiStr, pstFdnInfo->aucNum1, (VOS_UINT8 *)&pstFdnInfo->ulNum1Len);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */
    PS_MEM_FREE(WUEPS_PID_TAF, pucAsciiStr);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SendPbUssdFdnCheckReq
 功能描述  : 调用PB的API发起USSD的FDN检查请求
 输入参数  : usClientId:状态机的client ID
             pstMsg:USSD业务请求消息
 返 回 值  : VOS_TRUE            发起USSD的FDN检查请求成功
             VOS_FALSE           发起USSD的FDN检查请求失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    作    者   : f62575
    修改内容   : 新生成函数
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
*****************************************************************************/
VOS_UINT32 TAF_SPM_SendPbUssdFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    SI_PB_FDN_NUM_STRU                  stFdnInfo;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stFdnInfo, 0x00, sizeof(stFdnInfo));
    ulRet = TAF_SPM_BuildUssdFdnInfo(pstMsg, &stFdnInfo);

    if (VOS_FALSE == ulRet)
    {
        return VOS_FALSE;
    }

    ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, usClientId, &stFdnInfo);

    if (VOS_OK != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_SendPbCallFdnCheckReq
 功能描述  : 调用PB的API发起CALL的FDN检查请求
 输入参数  : usClientId:状态机的client ID
             pstMsg:语音业务请求消息
 返 回 值  : VOS_TRUE            发起USSD的FDN检查请求成功
             VOS_FALSE           发起USSD的FDN检查请求失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月14日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 增强型多方通话
*****************************************************************************/
VOS_UINT32 TAF_SPM_SendPbCallFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    SI_PB_FDN_NUM_STRU                  stFdnInfo;

#if (FEATURE_ON == FEATURE_IMS)
	VOS_UINT32                          ulEventType;
#endif
    MN_CALL_CALLED_NUM_STRU             stDialNumber;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_MODE_ENUM_U8                enCallMode;
    MN_CALL_CS_DATA_CFG_STRU            stDataCfg;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stFdnInfo, 0x00, sizeof(stFdnInfo));
    PS_MEM_SET(&stDataCfg, 0x00, sizeof(stDataCfg));
    PS_MEM_SET(&stDialNumber, 0x00, sizeof(stDialNumber));

#if (FEATURE_ON == FEATURE_IMS)
    ulEventType         = TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg();
#endif

    /* 由于增强型多方通话已经解析过了，这里不再需要解析  */
#if (FEATURE_ON == FEATURE_IMS)
    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        return TAF_SPM_SendUsimEconfFdnReq(usClientId, pstMsg);
    }
#endif

    /* 获取呼叫发起请求主动的stDialNumber */
    TAF_SPM_GetCallInfoFromFsmEntryMsg(&stDialNumber, &enCallType, &enCallMode, &stDataCfg);

    stFdnInfo.ulNum1Len = (stDialNumber.ucNumLen <= MN_CALL_MAX_BCD_NUM_LEN) ?
                          stDialNumber.ucNumLen : MN_CALL_MAX_BCD_NUM_LEN;

    PS_MEM_CPY(stFdnInfo.aucNum1, stDialNumber.aucBcdNum, MN_CALL_MAX_BCD_NUM_LEN);

    ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, usClientId, &stFdnInfo);

    if (VOS_OK != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_SendUsimCallEnvelopeReq
 功能描述  : 调用USIMAPI发送CALL业务请求的envelope消息 请求进行call ctrl结果
 输入参数  : pstCalledNumber -- 电话号码结构体
             pstDataCfgInfo  -- 数据配置结构体
             ulSendPara      -- 消息参数
             enCallType      -- call Type
             enCallMode      -- Call Mode
 输出参数  : 无
 返 回 值  : VOS_TRUE            发起call的call ctrl检查请求成功
             VOS_FALSE           发起call的call ctrl检查请求失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_SPM_SendUsimCallEnvelopeReq(
    MN_CALL_CALLED_NUM_STRU            *pstCalledNumber,
    MN_CALL_CS_DATA_CFG_INFO_STRU      *pstDataCfgInfo,
    VOS_UINT32                          ulSendPara,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode
)
{
    VOS_UINT8                           aucLI[MN_MO_CTRL_LAI_LEN];
    VOS_UINT8                           aucStkBcdNum[MN_CALL_MAX_CALLED_BCD_NUM_LEN + 1];
    SI_STK_ENVELOPE_STRU                stEnvelopeMsg;
    NAS_CC_IE_BC_STRU                   stBc1;
    NAS_CC_IE_BC_STRU                   stBc2;
    MN_CALL_REP_IND_ENUM_U8             enBcRepeatInd;
    VOS_UINT32                          ulNumOfBc;


    PS_MEM_SET(&stEnvelopeMsg, 0, sizeof(SI_STK_ENVELOPE_STRU));

    stEnvelopeMsg.enEnvelopeType    = SI_STK_ENVELOPE_CALLCRTL;
    stEnvelopeMsg.DeviceId.ucSDId   = SI_STK_DEV_TERMINAL;
    stEnvelopeMsg.DeviceId.ucDDId   = SI_STK_DEV_UICC;
    enBcRepeatInd                   = MN_CALL_REP_IND_NULL;

    /* 根据呼叫类型, 呼叫模式和数据呼叫配置生成BC和Repeat Ind参数 */
    PS_MEM_SET(&stBc1, 0, sizeof(NAS_CC_IE_BC_STRU));
    PS_MEM_SET(&stBc2, 0, sizeof(NAS_CC_IE_BC_STRU));

    ulNumOfBc = MN_CALL_BuildBcOfSetup(enCallType,
                                       enCallMode,
                                       pstDataCfgInfo,
                                       &stBc1,
                                       &stBc2);

    if (0 == ulNumOfBc)
    {
        return VOS_FALSE;
    }

    if (TAF_CALL_MAX_BC_NUM == ulNumOfBc)
    {
        /* 有两个BC的情况下，repeat indicator设为alternate */
        enBcRepeatInd = MN_CALL_REP_IND_ALTER;
    }
    else
    {
        /* 此处需要参考24.008 10.5.4.22 中的定义确认 */
        enBcRepeatInd = MN_CALL_REP_IND_NULL;
    }

    stEnvelopeMsg.uEnvelope.CallCtrl.OP_Capability1          = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.Capability1.ulLen       = stBc1.LastOctOffset;
    stEnvelopeMsg.uEnvelope.CallCtrl.Capability1.pucCCP      = (VOS_UINT8 *)&stBc1.Octet3;

    if ((MN_CALL_REP_IND_NULL != enBcRepeatInd)
     && (0                    != stBc2.IsExist))
    {
        stEnvelopeMsg.uEnvelope.CallCtrl.OP_Capability2      = VOS_TRUE;
        stEnvelopeMsg.uEnvelope.CallCtrl.OP_BCRepInd         = VOS_TRUE;
        stEnvelopeMsg.uEnvelope.CallCtrl.Capability2.ulLen   = stBc2.LastOctOffset;
        stEnvelopeMsg.uEnvelope.CallCtrl.Capability2.pucCCP  = (VOS_UINT8 *)&stBc2.Octet3;
    }

    stEnvelopeMsg.uEnvelope.CallCtrl.OP_SepcialData          = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag       = SI_CC_ADDRESS_TAG;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen       = pstCalledNumber->ucNumLen
                                                             + sizeof(MN_CALL_NUM_TYPE_ENUM_U8);
    PS_MEM_SET(aucStkBcdNum, 0, sizeof(aucStkBcdNum));
    aucStkBcdNum[0]                                          = pstCalledNumber->enNumType;
    PS_MEM_CPY(&aucStkBcdNum[sizeof(pstCalledNumber->enNumType)],
               pstCalledNumber->aucBcdNum,
               pstCalledNumber->ucNumLen);

    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue      = aucStkBcdNum;

    stEnvelopeMsg.uEnvelope.CallCtrl.OP_LocInfo              = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.pucATSLI        = aucLI;
    TAF_SDC_GetCurrentLai(aucLI, &stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.ulLen);

    if (VOS_OK != NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, ulSendPara, &stEnvelopeMsg))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimCallEnvelopeReq: Usim Returns Error.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_SPM_SendUsimEconfEnvelopeReq
 功能描述  : 发起增强型多方通话的Call Ctrl检查
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE            发起call的call ctrl检查请求成功
             VOS_FALSE           发起call的call ctrl检查请求失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 增强型多方通话
*****************************************************************************/
VOS_UINT32  TAF_SPM_SendUsimEconfEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_MODE_ENUM_U8                enCallMode;
    VOS_UINT32                          ulSendPara;

    PS_MEM_SET(&stCalledNumber, 0x0, sizeof(stCalledNumber));
    PS_MEM_SET(&stDataCfgInfo, 0x0, sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();

    pstEconfInfoAddr->ucSendSuccNum = 0;
    pstEconfInfoAddr->ucRcvNum      = 0;
    enCallType                      = pstEconfInfoAddr->enCallType;
    enCallMode                      = pstEconfInfoAddr->enCallMode;
    PS_MEM_CPY(&stDataCfgInfo, &pstEconfInfoAddr->stDataCfg, sizeof(stDataCfgInfo));

    for (ucIndex = 0; ucIndex < pstEconfInfoAddr->ucCallNum; ucIndex++)
    {
        PS_MEM_CPY(&stCalledNumber,
               &pstEconfInfoAddr->astEconfCheckInfo[ucIndex].stCalledNumber,
               sizeof(MN_CALL_CALLED_NUM_STRU));

        pstEconfInfoAddr->astEconfCheckInfo[ucIndex].ulCheckCnfFlag = VOS_FALSE;

        /* 增强型多方通话情况下，高16位为表示第几个电话号码，低16位为ClinedId */
        ulSendPara = TAF_SPM_ECONF_SET_SEND_PARA(ucIndex, usClientId);

        ulRet = TAF_SPM_SendUsimCallEnvelopeReq(&stCalledNumber,
                                                &stDataCfgInfo,
                                                ulSendPara,
                                                enCallType,
                                                enCallMode);
        if (VOS_FALSE == ulRet)
        {
            /* 记录为失败 */
            TAF_SPM_RecordEconfCheckRslt(ucIndex, TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER);
        }
        else
        {
            pstEconfInfoAddr->ucSendSuccNum++;
        }
    }

    /* 全部发送失败，则退出 */
    if (0 == pstEconfInfoAddr->ucSendSuccNum)
    {
        /* 上报结果 */
        TAF_SPM_ReportEconfCheckRslt();
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_SPM_SendUsimEconfFdnReq
 功能描述  : 发起增强型多方通话的Fdn检查
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE            发起call的call ctrl检查请求成功
             VOS_FALSE           发起call的call ctrl检查请求失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 增强型多方通话
*****************************************************************************/
VOS_UINT32  TAF_SPM_SendUsimEconfFdnReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    MN_CALL_CALLED_NUM_STRU            *pstCalledNumber     = VOS_NULL_PTR;
    SI_PB_FDN_NUM_STRU                  stFdnInfo;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSendPara;

    PS_MEM_SET(&stFdnInfo, 0x0, sizeof(stFdnInfo));
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();

    pstEconfInfoAddr->ucSendSuccNum = 0;
    pstEconfInfoAddr->ucRcvNum      = 0;
    for (ucIndex = 0; ucIndex < pstEconfInfoAddr->ucCallNum; ucIndex++)
    {
        pstEconfInfoAddr->astEconfCheckInfo[ucIndex].ulCheckCnfFlag = VOS_FALSE;

        pstCalledNumber = &pstEconfInfoAddr->astEconfCheckInfo[ucIndex].stCalledNumber;

        stFdnInfo.ulNum1Len = pstCalledNumber->ucNumLen <= MN_CALL_MAX_BCD_NUM_LEN ?
                          pstCalledNumber->ucNumLen : MN_CALL_MAX_BCD_NUM_LEN;

        PS_MEM_CPY(stFdnInfo.aucNum1, pstCalledNumber->aucBcdNum, stFdnInfo.ulNum1Len);

        /* 增强型多方通话情况下，高16位为表示第几个电话号码，低16位为ClinedId */
        ulSendPara = TAF_SPM_ECONF_SET_SEND_PARA(ucIndex, usClientId);

        ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, ulSendPara, &stFdnInfo);
        if (VOS_OK != ulRet)
        {
            /* 记录为失败 */
            TAF_SPM_RecordEconfCheckRslt(ucIndex, TAF_CS_CAUSE_FDN_CHECK_FAILURE);
        }
        else
        {
            pstEconfInfoAddr->ucSendSuccNum++;
        }
    }

    /* 全部发送失败，则退出 */
    if (0 == pstEconfInfoAddr->ucSendSuccNum)
    {
        /* 上报结果 */
        TAF_SPM_ReportEconfCheckRslt();
        return VOS_FALSE;
    }

    return VOS_TRUE;

}
#endif

/*****************************************************************************
 函 数 名  : TAF_SPM_SendUsimCallEnvelopeReq_Call
 功能描述  : 发送CALL业务请求的envelope消息 请求进行call ctrl结果
 输入参数  : usClientId:状态机的client ID
             pstMsg     待CALL CONTROL的call业务请求消息
 输出参数  : 无
 返 回 值  : VOS_TRUE            发起call的call ctrl检查请求成功
             VOS_FALSE           发起call的call ctrl检查请求失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 增强型多方通话
*****************************************************************************/
VOS_UINT32  TAF_SPM_SendUsimCallEnvelopeReq_Call(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                          ulEventType;
#endif
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_MODE_ENUM_U8                enCallMode;

    PS_MEM_SET(&stCalledNumber, 0x0, sizeof(stCalledNumber));
    PS_MEM_SET(&stDataCfgInfo, 0x0, sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));
#if (FEATURE_ON == FEATURE_IMS)
    ulEventType         = TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg();
#endif

    /* 由于增强型多方通话已经解析过了，这里不再需要解析  */
#if (FEATURE_ON == FEATURE_IMS)
    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        return TAF_SPM_SendUsimEconfEnvelopeReq(usClientId, pstMsg);
    }
    else
#endif
    {
        /* 从消息中获取电话号码相关信息 */
        TAF_SPM_GetCallInfoFromFsmEntryMsg(&stCalledNumber, &enCallType, &enCallMode, (MN_CALL_CS_DATA_CFG_STRU *)&stDataCfgInfo);

        /* 发起检查 */
        return TAF_SPM_SendUsimCallEnvelopeReq(&stCalledNumber,
                                               &stDataCfgInfo,
                                               usClientId,
                                               enCallType,
                                               enCallMode);
    }
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

