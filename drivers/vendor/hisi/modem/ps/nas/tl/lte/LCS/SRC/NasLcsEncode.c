/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLcsEncode.c
  Description     :
  History         :
     1.HANLUFENG 41410       2013-8-8   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "vos.h"
#include  "NasLcsPublic.h"
#include  "NasLcsEncode.h"
#include  "NasLcsDecode.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLCSENCODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSENCODE_C

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRelComplete
 Description     : 编码Release Complete空口消息
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRelComplete
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT32                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucTi     = pstEncodeInfo->ucTi;
    VOS_UINT16                          usTmpLen = 0;
    VOS_UINT8                           ucTag;

    *pusIeLen = 0;

    /* 编码PD和TI */
    pucEncodeOutMsg[usSum]  = NAS_LCS_PROTOCOL_DISCRIMINATOR;
    pucEncodeOutMsg[usSum]  = pucEncodeOutMsg[usSum] | (VOS_UINT8)(ucTi << NAS_LCS_MOVEMENT_4_BITS);
    usSum++;

    /* 编码Msg Type */
    pucEncodeOutMsg[usSum++] = NAS_LCS_CN_MSG_REL_CML;

    /* 编码Fccility Ie */
    /* 判断是否携带Cause,若携带Cause则说明Rel Cmp消息中携带Return Error或者Retrun Rej */
    if (NAS_LCS_OP_TRUE == pstEncodeInfo->bitOpCause)
    {
        /* 取Cause中低16位中的高8位, 其为Component Code */
        ucTag = (VOS_UINT8)((pstEncodeInfo->enCause & NAS_LCS_MSG_LOW_16_BIT) >> NAS_LCS_MOVEMENT_8_BITS);
        if (NAS_LCS_ERROR_CODE_TAG == ucTag)
        {
            enRslt = NAS_LCS_EncodeIeFacility(      pucEncodeOutMsg + usSum,
                                                    &usTmpLen,
                                                    pstEncodeInfo,
                                                    NAS_LCS_CN_MSG_REL_CML,
                                                    NAS_LCS_COMPONENT_RETURN_ERR_TAG);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
        }
        else
        {
            enRslt = NAS_LCS_EncodeIeFacility(      pucEncodeOutMsg + usSum,
                                                    &usTmpLen,
                                                    pstEncodeInfo,
                                                    NAS_LCS_CN_MSG_REL_CML,
                                                    NAS_LCS_COMPONENT_REJECT);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
        }
        usSum = usSum + usTmpLen;
    }
    /* 判断是否为MT-LR RSP */
    else if (NAS_LCS_OP_TRUE == pstEncodeInfo->bitLocNtfRsp)
    {
        enRslt = NAS_LCS_EncodeIeFacility(  pucEncodeOutMsg + usSum,
                                            &usTmpLen,
                                            pstEncodeInfo,
                                            NAS_LCS_CN_MSG_REL_CML,
                                            NAS_LCS_COMPONENT_RETURN_RSLT_TAG);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return NAS_LCS_CAUSE_FAIL;
        }
        usSum = usSum + usTmpLen;
    }
    /* 若都不是,则为正常流程结束, 不携带Facility信元  */
    else
    {
        enRslt = NAS_LCS_CAUSE_SUCCESS;
    }

    *pusIeLen = usSum;
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRegister
 Description     : 编码register空口消息
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRegister
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT32                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucTi     = pstEncodeInfo->ucTi;
    VOS_UINT16                          usTmpLen = 0;

    *pusIeLen = 0;

    /* 编码PD和TI */
    pucEncodeOutMsg[usSum]  = NAS_LCS_PROTOCOL_DISCRIMINATOR;
    pucEncodeOutMsg[usSum]  = pucEncodeOutMsg[usSum] | (VOS_UINT8)(ucTi << NAS_LCS_MOVEMENT_4_BITS);
    usSum++;

    /* 编码Msg Type */
    pucEncodeOutMsg[usSum++] = NAS_LCS_CN_MSG_REGISTER;

    /* 编码Facility Ie */
    enRslt = NAS_LCS_EncodeIeFacility(  pucEncodeOutMsg + usSum,
                                        &usTmpLen,
                                        pstEncodeInfo,
                                        NAS_LCS_CN_MSG_REGISTER,
                                        NAS_LCS_COMPONENT_INVOKE_TAG);

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeFacility
 Description     : 编码FACILITY空口消息
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT32                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucTi     = pstEncodeInfo->ucTi;
    VOS_UINT16                          usTmpLen = 0;

    *pusIeLen = 0;

    /* 编码PD和TI */
    pucEncodeOutMsg[usSum]  = NAS_LCS_PROTOCOL_DISCRIMINATOR;
    pucEncodeOutMsg[usSum]  = pucEncodeOutMsg[usSum] | (VOS_UINT8)(ucTi << NAS_LCS_MOVEMENT_4_BITS);
    usSum++;

    /* 编码Msg Type */
    pucEncodeOutMsg[usSum++] = NAS_LCS_CN_MSG_FACILITY;

    /* 编码Facility Ie */
    enRslt = NAS_LCS_EncodeIeFacility(  pucEncodeOutMsg + usSum,
                                        &usTmpLen,
                                        pstEncodeInfo,
                                        NAS_LCS_CN_MSG_FACILITY,
                                        NAS_LCS_COMPONENT_INVOKE_TAG);

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeIeFacility
 Description     : 编码空口信元Facility
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
                   enMsgType                    :空口消息类型
                   enComponent                  :Component类型
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeIeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo,
    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32     enMsgType,
    NAS_LCS_COMPONENT_ENUM_UINT8        enComponent
)
{
    VOS_UINT16                          usSum       = 0;
    VOS_UINT16                          usTmpLen    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT16                          usValueLen  = 0;
    VOS_UINT16                          usLenIndex  = 0;

    *pusIeLen = 0;

    /* 根据空口消息类型, 变异信元内容 */
    switch(enMsgType)
    {
        case NAS_LCS_CN_MSG_REL_CML:

            /* Rel Cmp的Facility信元结构为TLV, 编码IEI */
            pucEncodeOutMsg[usSum++] = NAS_LCS_MSG_FACILITY_IEI;

            /* 跳过长度,待编码完Facility Value后填写长度 */
            usLenIndex = usSum;
            usSum++;
            enRslt = NAS_LCS_EncodeRelCmpIeFacility(    pucEncodeOutMsg + usSum,
                                                        &usTmpLen,
                                                        pstEncodeInfo,
                                                        enComponent);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
            usSum = usSum + usTmpLen;
            usValueLen = usTmpLen;
            break;

        case NAS_LCS_CN_MSG_REGISTER:

            /* REGISTER的Facility信元结构为TLV,  编码IEI */
            pucEncodeOutMsg[usSum++] = NAS_LCS_MSG_FACILITY_IEI;

            /* 跳过长度,待编码完Facility Value后填写长度 */
            usLenIndex = usSum;
            usSum++;
            enRslt = NAS_LCS_EncodeRegisterIeFacility(  pucEncodeOutMsg + usSum,
                                                        &usTmpLen,
                                                        pstEncodeInfo,
                                                        enComponent);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
            usSum = usSum + usTmpLen;
            usValueLen = usTmpLen;
            break;

        case NAS_LCS_CN_MSG_FACILITY:

            /* Facility的Facility信元结构为LV, 没有IEI */
            /* 跳过长度,待编码完Facility Value后填写长度 */
            usLenIndex = usSum;
            usSum++;
            enRslt = NAS_LCS_EncodeRegisterIeFacility(  pucEncodeOutMsg + usSum,
                                                        &usTmpLen,
                                                        pstEncodeInfo,
                                                        enComponent);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
            usSum = usSum + usTmpLen;
            usValueLen = usTmpLen;
            break;

        default:
            TLPS_PRINT2LAYER_ERROR1(NAS_LCS_EncodeIeFacility_ENUM, LNAS_LCS_MsgTypeInvalid, enMsgType);
            return NAS_LCS_CAUSE_FAIL;
    }

    /* Component Len最大为255 */
    if (NAS_LCS_MAX_COMPONENT_LENGTH < usValueLen)
    {
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_EncodeIeFacility_ENUM, LNAS_LCS_EnocdeLenFail, usValueLen);
        return NAS_LCS_CAUSE_FAIL;
    }

    /* 填充LEHGTH */
    pucEncodeOutMsg[usLenIndex] = (VOS_UINT8)usValueLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRegisterIeFacility
 Description     : 编码Register空口信元Facility
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRegisterIeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo,
    NAS_LCS_COMPONENT_ENUM_UINT8         enComponent
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    NAS_LCS_POS_PDUS_STRU               stPosPdus;
    NAS_LCS_LPP_MSG_RECORD_STRU         *pstLppMsgRecord = NAS_LCS_GetLppMolrRecord();

    *pusIeLen = 0;

    /* 编码INVOKE ID */
    pucEncodeOutMsg[usSum++] = NAS_LCS_INVOKE_ID_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = pstEncodeInfo->ucInvokeId;

    /* 编码OPERATION CODE */
    pucEncodeOutMsg[usSum++] = NAS_LCS_OPERATION_CODE_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = NAS_LCS_OPERATION_MO_LR;

    /* 编码Parameters */
    if (NAS_LCS_START_SOURCE_LPP == pstEncodeInfo->enStartSource)
    {
        /* 当前LPP请求辅助信息只有一条 */
        stPosPdus.ucPduNum = 1;
        stPosPdus.astPosPdu[0].ucPduLen = (VOS_UINT8)pstLppMsgRecord->ulLppMsgSize;
        stPosPdus.astPosPdu[0].pucPdu   = pstLppMsgRecord->aucLppMsg;

        enRslt = NAS_LCS_EncodeAssDataMoLrReq(pucEncodeOutMsg + usSum, &usTmpLen, &stPosPdus);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return NAS_LCS_CAUSE_FAIL;
        }
    }
    else if(NAS_LCS_START_SOURCE_TAF == pstEncodeInfo->enStartSource)
    {
        enRslt = NAS_LCS_EncodeLocEstimateMoLrReq(pucEncodeOutMsg + usSum, &usTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return NAS_LCS_CAUSE_FAIL;
        }
    }
    else
    {
        TLPS_PRINT2LAYER_ERROR1(    NAS_LCS_EncodeRegisterIeFacility_ENUM,
                                    LNAS_LCS_StartSourceInvalid,
                                    pstEncodeInfo->enStartSource);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;

    /* 编码Component Tag和Length */
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(enComponent, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeRelCmpIeFacility_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeAssDataMoLrReq
 Description     : 编码请求辅助信息的MoLr请求的Paramesters
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeAssDataMoLrReq
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_POS_PDUS_STRU               *pstPosPdus
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* 编码信元mo-lr */
    NAS_LCS_EncodeMolrType(pucEncodeOutMsg + usSum, &usTmpLen, NAS_LCS_MOLR_ASSISTANCE_DATA);
    usSum = usSum + usTmpLen;

    /* 编码信元multiplePostioningProtocolPDUs */
    enRslt = NAS_LCS_EncodeMuliPosPDUS(pucEncodeOutMsg + usSum, &usTmpLen, pstPosPdus);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_FAIL;
    }
    usSum = usSum + usTmpLen;
    usTmpLen = usSum;

    /* 编码mo-lr parameters TAG和LENGTH */
    enRslt = NAS_LCS_PackTL(NAS_LCS_SEQUENCE_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeAssDataMoLrReq_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeMuliPosPDUS
 Description     : 编码信元mutiplePositioningProtocolPDUs
 Input           : pucEncodeOutMsg              :编码后码流
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeMuliPosPDUS
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_POS_PDUS_STRU               *pstPosPdus
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucLoop;

    *pusIeLen = 0;

    /* 编码PositioningProtocolPDU, */
    for (ucLoop = 0; ucLoop < pstPosPdus->ucPduNum; ucLoop++)
    {
        enRslt = NAS_LCS_EncodePosPDU(  pucEncodeOutMsg + usSum,
                                        &usTmpLen,
                                        &pstPosPdus->astPosPdu[ucLoop]);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return NAS_LCS_CAUSE_FAIL;
        }
        usSum = usSum + usTmpLen;
    }

    /* 编码mutiplePositioningProtocolPDUs的TAG和LENGTH */
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(NAS_LCS_MOLR_MULI_POS_PROTOC_PDUS_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeMuliPosPDUS_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLppMsg
 Description     : 编码信元单个PositioningProtocolPDU
 Input           : pucEncodeOutMsg              :编码后码流
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodePosPDU
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_POS_PDU_STRU                *pstPosPdu
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* 拷贝Pdu内容 */
    NAS_LCS_MEM_CPY_S(pucEncodeOutMsg, NAS_LCS_MAX_LPP_MSG_LEN, pstPosPdu->pucPdu, pstPosPdu->ucPduLen);

    usSum = pstPosPdu->ucPduLen;
    usTmpLen = usSum;

    /* 编码TAG和LENGTH */
    enRslt = NAS_LCS_PackTL(NAS_LCS_OCTETSTRING_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeMuliPosPDUS_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLocEstimateMoLrReq
 Description     : 编码LocationEstimate类型的MoLr请求的Paramesters
 Input           : pucEncodeOutMsg              :编码后码流
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLocEstimateMoLrReq
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen
)
{
    VOS_UINT16                          usSum       = 0;
    VOS_UINT16                          usTmpLen    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    LCS_MOLR_PARA_STRU                 *pstMolrPara = NAS_LCS_GetTafMolrRecord();

    *pusIeLen = 0;

    /* 编码信元mo-lr type */
    NAS_LCS_EncodeMolrType(pucEncodeOutMsg + usSum, &usTmpLen, NAS_LCS_MOLR_LOCATION_ESTIMATE);
    usSum = usSum + usTmpLen;

    /* 编码信元location method */
    NAS_LCS_EncodeLocationMethod(pucEncodeOutMsg + usSum, &usTmpLen, pstMolrPara->enMethod);
    usSum = usSum + usTmpLen;

    /* 编码LCS QOS */
    NAS_LCS_EncodeLcsQos(pucEncodeOutMsg + usSum, &usTmpLen, pstMolrPara);
    usSum = usSum + usTmpLen;

    NAS_LCS_EncodeClentExtId(pucEncodeOutMsg + usSum, &usTmpLen, pstMolrPara);
    usSum = usSum + usTmpLen;

    /* 编码信元SupportGADShapes */
    NAS_LCS_EncodeSuppGADShapes(pucEncodeOutMsg + usSum, &usTmpLen, pstMolrPara);
    usSum = usSum + usTmpLen;

    /* 编码mo-lr parameters TAG和LENGTH */
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(NAS_LCS_SEQUENCE_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLocEstimateMoLrReq_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeSuppGADShapes
 Description     : 编码supportedGADShapes
 Input           : pucEncodeOutMsg              :编码后码流
                   pstTafMsgRecord              :Taf下发的MoLr请求参数
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeSuppGADShapes
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_PARA_STRU                  *pstMolrPara
)
{
    VOS_UINT16                          usSum           = 0;
    LCS_SHAPE_REP_STRU                  *pstShapeRep;
    VOS_UINT8                           ucTmp           = 0;

    *pusIeLen = 0;

    /* 计算Value,转换成空口格式 */
    pstShapeRep = &pstMolrPara->u.stShapeRep;
    ucTmp = pstShapeRep->bitEllipPoint << NAS_LCS_MOVEMENT_7_BITS;
    ucTmp = ucTmp | (pstShapeRep->bitEllipPointUncertCircle << NAS_LCS_MOVEMENT_6_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitEllipPointUncertEllip << NAS_LCS_MOVEMENT_5_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitPolygon << NAS_LCS_MOVEMENT_4_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitEllipPointAlt << NAS_LCS_MOVEMENT_3_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitEllipPointAltUncertEllip << NAS_LCS_MOVEMENT_2_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitEllipArc << NAS_LCS_MOVEMENT_1_BITS);

    /* 编码TAG */
    pucEncodeOutMsg[usSum++] = NAS_LCS_SUPP_GAD_SHAPES_TAG;

    /* 编码LEN */
    pucEncodeOutMsg[usSum++] = 2;

    /* 编码保留位LEN */
    pucEncodeOutMsg[usSum++] = 1;

    /* 编码VALUE */
    pucEncodeOutMsg[usSum++] = ucTmp;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeClentExtId
 Description     : 编码lcsClientExternalId
 Input           : pucEncodeOutMsg              :编码后码流
                   pstTafMsgRecord              :Taf下发的MoLr请求参数
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeClentExtId
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_PARA_STRU                  *pstMolrPara
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;
    if ((LCS_MOLR_METHOD_TRANSFER_TP_ADDR == pstMolrPara->enMethod)
        || (LCS_MOLR_METHOD_RETRIEVAL_TP_ADDR == pstMolrPara->enMethod))
    {
        if (0 < pstMolrPara->stTPAddr.ucLength)
        {
            usTmpLen = pstMolrPara->stTPAddr.ucLength;
            pucEncodeOutMsg[usSum++] = NAS_LCS_CLIENT_EXT_ID_ADDR_TAG;
            pucEncodeOutMsg[usSum++] = (VOS_UINT8)usTmpLen;
            NAS_LCS_MEM_CPY_S(  pucEncodeOutMsg + usSum,
                                         LCS_CLIENT_EXID_MAX_LEN,
                                         pstMolrPara->stTPAddr.aucValue,
                                         usTmpLen);

            usSum = usSum + usTmpLen;
        }
    }

    if (0 == usSum)
    {
        return NAS_LCS_CAUSE_SUCCESS;
    }

    usTmpLen = usSum;
    enRslt   = NAS_LCS_PackTL(NAS_LCS_CLIENT_EXT_ID_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLocEstimateMoLrReq_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLcsQos
 Description     : 编码lcs-qos
 Input           : pucEncodeOutMsg              :编码后码流
                   pstTafMsgRecord              :Taf下发的MoLr请求参数
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLcsQos
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_PARA_STRU                  *pstMolrPara
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* 编码horizontal-accuracy */
    if (LCS_HOR_ACC_SET_PARAM == pstMolrPara->enHorAccSet)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_QOS_HOR_ACC_TAG;
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = pstMolrPara->ucHorAcc;
    }

    /* 编码verticalCoordinateRequest */
    if (LCS_VER_REQUESTED == pstMolrPara->enVerReq)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_QOS_VER_REQ_TAG;
        pucEncodeOutMsg[usSum++] = 0;
    }

    /* 编码vertical-accuracy */
    if ((LCS_VER_ACC_SET_PARAM == pstMolrPara->enVerAccSet) && (LCS_VER_REQUESTED == pstMolrPara->enVerReq))
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_QOS_VER_ACC_TAG;
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = pstMolrPara->ucVerAcc;
    }

    /* 编码velocityRequest */
    if (LCS_VEL_NOT_REQUESTED != pstMolrPara->enVelReq)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_QOS_VEL_REQ_TAG;
        pucEncodeOutMsg[usSum++] = 0;
    }

    /* 编码长度为0时,说明Qos为空,则不携带可选信元Qos */
    if (0 == usSum)
    {
        return NAS_LCS_CAUSE_SUCCESS;
    }
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(NAS_LCS_MOLR_QOS_TAG, pucEncodeOutMsg, &usTmpLen);

    if(NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLcsQos_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeMolrType
 Description     : 编码信元Mo-lr type
 Input           : pucEncodeOutMsg              :编码后码流
                   enMolrType                   :mo-lr type
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeMolrType
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_MOLR_TYPE_ENUM_UINT8         enMolrType
)
{
    VOS_UINT16                          usSum    = 0;

    *pusIeLen = 0;

    /* 编码TLV */
    pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_TYPE_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = enMolrType;

    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLocationMethod
 Description     : 编码信元Location Method
 Input           : pucEncodeOutMsg              :编码后码流
                   enMethod                     :At下发的Loc method
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_EncodeLocationMethod
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_METHOD_ENUM_UINT8           enMethod
)
{
    NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8   enMoLrMethod;
    VOS_UINT16                          usSum = 0;

    *pusIeLen = 0;
    enMoLrMethod = NAS_LCS_MapLocationMethod(enMethod);

    /* 判断转换后的Method是否有效 */
    if (NAS_LCS_NW_MOLR_METHOD_BUTT == enMoLrMethod)
    {
        return;
    }
    pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_LOC_METHOD_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = enMoLrMethod;
    *pusIeLen = usSum;
    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_MapLocationMethod
 Description     : 把TAF消息中的Method转换为空口中的LocationMethod
 Input           : enMethod                             :编码前的method
 Output          : NULL
 Return          : NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8    :转换后的method

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8 NAS_LCS_MapLocationMethod(LCS_MOLR_METHOD_ENUM_UINT8  enMethod)
{
    NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8 enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_BUTT;

    /* 把AT命令中携带的method转换为空中method枚举 */
    switch(enMethod)
    {
        case LCS_MOLR_METHOD_AGPS:
            enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_AGPS;
            break;

        case LCS_MOLR_METHOD_AGNSS:
            enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_AGANSS;
            break;

        case LCS_MOLR_METHOD_AGPS_AGNSS:
            enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_AGPS_GANSS;
            break;

        default:
            enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_BUTT;
            break;
    }
    return enMoLrMethod;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLocNtyReslt
 Description     : 编码Mtlr location notification Result空口消息信元
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLocNtyReslt
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* 编码Operation Code */
    pucEncodeOutMsg[usSum++] = NAS_LCS_OPERATION_CODE_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = NAS_LCS_OPERATION_LOC_NOTIFICATION;

    /* 编码Parameters */
    enRslt = NAS_LCS_EncodeLocNtfRsp(pucEncodeOutMsg + usSum, &usTmpLen, pstEncodeInfo);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum    = usSum + usTmpLen;
    usTmpLen = usSum;

    /* 编码可选信元Sequence */
    enRslt   = NAS_LCS_PackTL(NAS_LCS_SEQUENCE_TAG , pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
       TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLocNtyReslt_ENUM, LNAS_LCS_EncodeTLFail);
       return NAS_LCS_CAUSE_FAIL;
    }

    usSum     = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRelCmpIeFacility
 Description     : 编码Release Complete空口消息信元Facility
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
                   enComponent                  :Component类型
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRelCmpIeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo,
    NAS_LCS_COMPONENT_ENUM_UINT8        enComponent
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* 编码Invoke Id */
    if (NAS_LCS_OP_TRUE == pstEncodeInfo->bitOpInvokeId)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_INVOKE_ID_TAG;
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = pstEncodeInfo->ucInvokeId;
    }
    else
    {
        /* 只有Reject Component能不携带Invoke Id, 其他Component必须携带Invoke Id */
        if (NAS_LCS_COMPONENT_REJECT == enComponent)
        {
            /* 协议规定不懈怠INVOKE ID时, TAG使用NULL */
            pucEncodeOutMsg[usSum++] = NAS_LCS_NULL_TAG;
            pucEncodeOutMsg[usSum++] = 0;
        }
        else
        {
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeRelCmpIeFacility_ENUM, LNAS_LCS_MissInvokeId);
            return NAS_LCS_CAUSE_FAIL;
        }
    }

    /* 编码Return Rslt Component */
    if (NAS_LCS_COMPONENT_RETURN_RSLT_TAG == enComponent)
    {
        /* 编码Location Notification Rsp */
        if (NAS_LCS_OPERATION_LOC_NOTIFICATION == pstEncodeInfo->enOperType)
        {
            /* 编码Parameters */
            enRslt = NAS_LCS_EncodeLocNtyReslt(pucEncodeOutMsg + usSum, &usTmpLen, pstEncodeInfo);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
            usSum = usSum + usTmpLen;
        }
    }
    else if(NAS_LCS_COMPONENT_RETURN_ERR_TAG == enComponent)
    {
        /* 编码Error Code */
        pucEncodeOutMsg[usSum++] = NAS_LCS_ERROR_CODE_TAG;
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = (VOS_UINT8)(pstEncodeInfo->enCause & NAS_LCS_MSG_LOW_8_BIT);
    }
    else if(NAS_LCS_COMPONENT_REJECT == enComponent)
    {
        /* 编码Problem Code */
        pucEncodeOutMsg[usSum++] = (VOS_UINT8)((pstEncodeInfo->enCause & NAS_LCS_MSG_LOW_16_BIT) >> NAS_LCS_MOVEMENT_8_BITS);
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = (VOS_UINT8)(pstEncodeInfo->enCause & NAS_LCS_MSG_LOW_8_BIT);
    }
    else
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    /* 编码Component Tag和Length */
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(enComponent, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeRelCmpIeFacility_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRelCmpIeFacility
 Description     : 编码LOCATION NOTIFICATION RESULT PARA
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLocNtfRsp
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT16                          usTmpLen = 0;

    *pusIeLen = 0;

    if (NAS_LCS_OP_TRUE == pstEncodeInfo->bitLocNtfRsp)
    {
        enRslt = NAS_LCS_EncodeVerifyRsp(pucEncodeOutMsg + usSum, &usTmpLen, pstEncodeInfo);
        if (NAS_LCS_CAUSE_SUCCESS == enRslt)
        {
            usSum = usSum + usTmpLen;
        }
        else
        {
            return enRslt;
        }
    }

    usTmpLen = usSum;
    enRslt   = NAS_LCS_PackTL(NAS_LCS_SEQUENCE_TAG , pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
       TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLocNtfRsp_ENUM, LNAS_LCS_EncodeTLFail);
       return NAS_LCS_CAUSE_FAIL;
    }

    usSum     = usSum + usTmpLen;
    *pusIeLen = usSum;
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeVerifyRsp
 Description     : 编码LOCATION NOTIFICATION RESULT PARA中的信元verificationResponse
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
 Output          : pusIeLen                     :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeVerifyRsp
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum       = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT16                          usTmpLen    = 0;

    *pusIeLen = 0;

    if (LCS_MTLRA_ALLOW == pstEncodeInfo->enLocNtfRsp)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_VER_RSP_PERMISSON_GRANTED;
    }
    else
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_VER_RSP_PERMISSON_DENIED;
    }

    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(NAS_LCS_VERIFICATION_RSP_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeVerifyRsp_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum     = usSum + usTmpLen;
    *pusIeLen = usSum;
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_PackTL
 Description     : 编码TAG和LEN
 Input           : pucEncodeOutMsg              :编码后码流
                   stEncodeInfo                 :编码所需要的信息
 Output          : pusCodeLen                   :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32  NAS_LCS_PackTL
(
    VOS_UINT8                           ucTag,
    VOS_UINT8                          *pucEncodeOutMsg,
    VOS_UINT16                         *pusCodeLen
)
{
    VOS_UINT8                           aucTmppool[5];
    VOS_UINT8                           ucHeaderLen     = 0;
    VOS_UINT16                          usSum           = 0;
    VOS_UINT16                          usValueLen      = *pusCodeLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucTmpLen        = 0;

    *pusCodeLen = 0;

    /* 如果当前还没有进行任何的参数的编码,整个长度为0 */
    if (0 == usValueLen)
    {
        pucEncodeOutMsg[usSum++] = ucTag;
        pucEncodeOutMsg[usSum++] = 0;
        *pusCodeLen = usSum;
        return NAS_LCS_CAUSE_SUCCESS;
    }

    aucTmppool[ucHeaderLen++] = ucTag;

    /* 对长度进行编码 */
    enRslt = NAS_LCS_EncodeLength(usValueLen, aucTmppool + ucHeaderLen, &ucTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR2(NAS_LCS_PackTL_ENUM, LNAS_LCS_EnocdeLenFail, ucTag, usValueLen);
        return NAS_LCS_CAUSE_FAIL;
    }

    ucHeaderLen = ucHeaderLen + ucTmpLen;

    /* 对当前字串进行移位(为TL预留出空间)和拷贝 */
    (VOS_VOID)VOS_MemMove(pucEncodeOutMsg + ucHeaderLen, pucEncodeOutMsg, usValueLen);

    NAS_LCS_MEM_CPY_S(pucEncodeOutMsg, ucHeaderLen, aucTmppool, ucHeaderLen);

    /*当前已经编码的字串长度*/
    *pusCodeLen = ucHeaderLen;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLength
 Description     : 编码LEN
 Input           : pucEncodeOutMsg              :编码后码流
                   usSrcLen                     :信元中LEN值
 Output          : pusCodeLen                   :已编码长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :编码结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32  NAS_LCS_EncodeLength
(
    VOS_UINT16                           usSrcLen,
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT8                           *pucCodeLen
)
{
    VOS_UINT8                           ucSum = 0;

    *pucCodeLen = 0;

    /* 这里只采用了两种编码方式，不明确长度的编码方式没有采用 */
    /* 如果是明确长度形式的短格式，编码处理 */
    if (usSrcLen < NAS_LCS_INDEF_LENGTH_FLAG)
    {
        /* L、V赋值 */
        pucEncodeOutMsg[ucSum++] = (VOS_UINT8)usSrcLen;
    }
    /* 如果是明确长度形式的长格式,编码处理 */
    else
    {
        /* 小于等于255,长度用一字节表示 */
        if (usSrcLen <= NAS_LCS_MAX_COMPONENT_LENGTH)
        {
            /* L、V赋值 */
            pucEncodeOutMsg[ucSum] = NAS_LCS_INDEF_LENGTH_FLAG + 1;
            ucSum++;
            pucEncodeOutMsg[ucSum] = (VOS_UINT8)usSrcLen;
            ucSum++;
            *pucCodeLen = ucSum;
        }
        else
        {
            TLPS_PRINT2LAYER_ERROR1(NAS_LCS_EncodeLength_ENUM, LNAS_LCS_EnocdeLenFail, usSrcLen);
            return NAS_LCS_CAUSE_FAIL;
        }
    }

    *pucCodeLen = ucSum;
    return NAS_LCS_CAUSE_SUCCESS;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

