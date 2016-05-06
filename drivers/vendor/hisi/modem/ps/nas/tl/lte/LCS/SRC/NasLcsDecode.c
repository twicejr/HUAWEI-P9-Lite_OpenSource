

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "NasLcsDecode.h"
#include    "NasCommPrint.h"
#include    "NasLcsPublic.h"
#include    "NasLcsOm.h"
#include    "PsCommonDef.h"
#include    "PsLogdef.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASLCSDECODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSDECODE_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/* CN消息码流解码后的结构体，消息太长，不适合作函数的局部变量 */
NAS_LCS_CN_MSG_STRU                     g_stLcsCnDecodeMsgStru;

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCnMsg
 Description     : LCS空口消息解析入口函数
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulDecodeMsgLen              :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCnMsg
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32     enCnMsgType;
    VOS_UINT8                          *pucTemMsg        = pucMsg;
    VOS_UINT32                          ulTmpLen;
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT32                          ulSum            = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enResult         = NAS_LCS_CAUSE_SUCCESS;

    *pulLen = 0;

    NAS_LCS_MEM_SET_S(pstCnMsgStru, sizeof(NAS_LCS_CN_MSG_STRU), 0, sizeof(NAS_LCS_CN_MSG_STRU));

    /* 检查空口长度是否合法 */
    if (NAS_LCS_MSG_MIN_LEN > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_MSG_LEN,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    NAS_LCS_MSG_MIN_LEN);

        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeCnMsg UndecodeMsgLen Invalid ", ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_FAIL;
    }

    /* 获取保存transaction identifier */
    pstCnMsgStru->ucTi = pucTemMsg[ulSum++] >> NAS_LCS_MOVEMENT_4_BITS;

    /* 获取Message type */
    enCnMsgType = pucMsg[ulSum++] & NAS_LCS_MSG_LOW_6_BIT;

    /* 保存Message type */
    pstCnMsgStru->enCnMsgType = enCnMsgType;

    /* 计算剩余未解析长度 */
    ulUndecodeMsgLen = ulUndecodeMsgLen - ulSum;
    ulTmpLen      = ulUndecodeMsgLen;

    /* 根据消息类型进行解析 */
    switch(enCnMsgType)
    {
        case NAS_LCS_CN_MSG_REL_CML:
            enResult = NAS_LCS_DecodeRelCmpl(pucMsg + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_CN_MSG_FACILITY:
            enResult = NAS_LCS_DecodeFacility(pucMsg + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_CN_MSG_REGISTER:
            enResult = NAS_LCS_DecodeRegister(pucMsg + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        default:
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_MSG_TYPE,
                                        NAS_LCS_MSG_TYPE_INVALID,
                                        enCnMsgType,
                                        NAS_LCS_NULL_PTR);

            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeCnMsg Msg Type Invalid ", enCnMsgType);
            enResult = NAS_LCS_CAUSE_MSG_TYPE_ERR_OR_NOT_IMPLEMENT;
            break;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enResult)
    {
        return enResult;
    }

    /* 获取已解析消息长度 */
    ulSum       = ulSum + ulTmpLen;
    *pulLen     = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRegister
 Description     : 解析Register空口码流
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRegister
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pucTemMsg        = pucMsg;
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT32                          ulTmpLen         = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt           = NAS_LCS_CAUSE_SUCCESS;

    *pulLen = 0;

    /* 检查剩余未解析码流长度 */
    if(NAS_LCS_IE_FACILITY_MIN_LEN > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_MSG_LEN,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    NAS_LCS_IE_FACILITY_MIN_LEN);

        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeRegister UndecodeMsgLen Invalid ", ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 解析必选信元FACILITY，格式时TLV */
    if (NAS_LCS_MSG_FACILITY_IEI == pucTemMsg[ulSum])
    {
        /* 可选信元存在Facility IEI, 跳过IEI */
        ulSum++;

        ulUndecodeMsgLen = ulUndecodeMsgLen - 1;

        ulTmpLen = ulUndecodeMsgLen;
        enRslt = NAS_LCS_DecodeIeFacility(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);

        /* 判断FACILITY信元解析解析结果 */
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            NAS_LCS_INFO_LOG(" NAS_LCS_DecodeRegister Facility IE Decode Fail ");
            return enRslt;
        }

        ulSum = ulSum + ulTmpLen;
    }
    else
    {
        /* 缺少必选信元Facility, 译码失败 */
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_FACILITY,
                                    NAS_LCS_MISS_MANDATORY_IE,
                                    pucTemMsg[ulSum],
                                    NAS_LCS_MSG_FACILITY_IEI);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeRegister Miss Facility IE ", pucTemMsg[ulSum]);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeFacility
 Description     : 解析Facility空口消息
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeFacility
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pucTemMsg        = pucMsg;
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT32                          ulTmpLen         = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt           = NAS_LCS_CAUSE_SUCCESS;

    *pulLen = 0;

    /* 检查剩余未解析码流长度 */
    if(NAS_LCS_IE_FACILITY_MIN_LEN > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_MSG_LEN,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    NAS_LCS_IE_FACILITY_MIN_LEN);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeFacility UndecodeMsgLen Invalid ", ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 解析必选信元FACILITY，格式是LV */

    ulTmpLen = ulUndecodeMsgLen;

    /* 判断FACILITY信元解析解析结果 */
    enRslt = NAS_LCS_DecodeIeFacility(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeFacility Facility Ie Decode Fail ", enRslt);
        return enRslt;
    }
    ulSum = ulSum + ulTmpLen;


    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRelCmpl
 Description     : 解析Rel Complete空口消息
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRelCmpl
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pucTemMsg       = pucMsg;
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT32                          ulTmpLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pulLen = 0;

    /* 判断是否存在可选信元 */
    if (0 == ulUndecodeMsgLen)
    {
        return NAS_LCS_CAUSE_SUCCESS;
    }

    /* 解析可选信元Cause */
    if (NAS_LCS_MSG_CAUSE_IEI == pucTemMsg[ulSum])
    {
        /* 获取剩余码流长度 */
        ulTmpLen = ulUndecodeMsgLen;
        enRslt = NAS_LCS_DecodeCause(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* 可选信元译码失败返回成功, 跳过剩余码流 */
            ulSum   = ulSum + ulUndecodeMsgLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过CAUSE */
        ulSum = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeMsgLen = ulUndecodeMsgLen - ulTmpLen;
    }

    /* 解析可选信元FACILITY */
    if ((NAS_LCS_IE_FACILITY_MIN_LEN <= ulUndecodeMsgLen)&&(NAS_LCS_MSG_FACILITY_IEI == pucTemMsg[ulSum]))
    {
        /* 可选信元存在Facility IEI, 跳过IEI */
        ulSum++;

        ulUndecodeMsgLen = ulUndecodeMsgLen - 1;

        /* 获取剩余码流长度 */
        ulTmpLen = ulUndecodeMsgLen;
        enRslt = NAS_LCS_DecodeIeFacility(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* 可选信元译码失败返回成功, 跳过剩余码流 */
            ulSum   = ulSum + ulUndecodeMsgLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过Facility */
        ulSum = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeMsgLen = ulUndecodeMsgLen - ulTmpLen;
    }

    ulSum = ulSum + ulUndecodeMsgLen;

    /* 获取解析已长度 */
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeIeFacility
 Description     : 解析Facility信元
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeIeFacility
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT8                          *pucTemMsg        = pucMsg;
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT8                           ulValueLen       = 0;
    VOS_UINT32                          ulTmpLen         = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt           = NAS_LCS_CAUSE_SUCCESS;

    /* 获取Facility Len */
    ulValueLen = pucTemMsg[ulSum++];

    /* 获取剩余码流长度  */
    ulUndecodeMsgLen = ulUndecodeMsgLen - ulSum;

    /* 检查长度是否合法 */
    if ((0 == ulValueLen) || (ulUndecodeMsgLen < ulValueLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_FACILITY,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen,
                                    ulUndecodeMsgLen);
        NAS_LCS_INFO_LOG2(" NAS_LCS_DecodeIeFacility ValueLen Invalid ", ulValueLen, ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 剩余码流长度以信元实际长度为准 */
    ulUndecodeMsgLen = ulValueLen;
    ulTmpLen         = ulUndecodeMsgLen;

    /* 解析Component */
    enRslt = NAS_LCS_DecodeComponent(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /* 跳过IE */
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeIeFacility Component decode fail ", enRslt);
        return enRslt;
    }

    ulSum   = ulSum + ulTmpLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCause
 Description     : 解析CASUE信元
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : puLen                        :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCause
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *puLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT32                          ulLen            = 0;
    VOS_UINT32                          ulUndecodeMsgLen = *puLen;
    VOS_UINT8                          *pucMsgTem        = pucMsg;
    VOS_UINT32                          ulIeLen;

    *puLen = 0;

    /* 检查剩余消息长度 */
    if (NAS_LCS_CAUSE_IE_MIN_LEN > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CAUSE,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    NAS_LCS_CAUSE_IE_MIN_LEN);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeCause UndecodeLen Invalid ", ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过IEI */
    ulSum++;

    /* 获取IE长度 */
    ulLen     = pucMsgTem[ulSum++];

    /* 计算整个IE长度为TL长度加上Value长度 */
    ulIeLen   = ulSum + ulLen;

    /* 检查消息长度,剩余码流必须大于等于整个IE长度 */
    if (ulIeLen > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CAUSE,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    ulIeLen);
        NAS_LCS_INFO_LOG2(" NAS_LCS_DecodeCause UndecodeLen Invalid ", ulUndecodeMsgLen, ulIeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* IE Cause暂不使用 */
    /* 跳过整个IE */
    *puLen = ulIeLen;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeComponent
 Description     : 解析component
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeComponent
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT8                           ucComponentType;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTem       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;

    /* 获取保存Component type */
    ucComponentType = pucMsgTem[ulSum];
    pstCnMsgStru->ucComponentType = ucComponentType;

    /* 获取剩余码流长度 */
    ulTmpLen = ulUndecodeLen;

    /* 根据component type类型，进行相应解码，类型:INVOKE, return result, return error, reject */
    switch (ucComponentType)
    {
        case NAS_LCS_COMPONENT_INVOKE_TAG:
            enRslt = NAS_LCS_DecodeInvoke(pucMsgTem + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_COMPONENT_RETURN_RSLT_TAG:
            enRslt = NAS_LCS_DecodeRtrnRslt(pucMsgTem + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_COMPONENT_RETURN_ERR_TAG:
            enRslt = NAS_LCS_DecodeRtrnErr(pucMsgTem + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_COMPONENT_REJECT:
            enRslt = NAS_LCS_DecodeReject(pucMsgTem + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        default:
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_COMPONENT,
                                        NAS_LCS_CMPONENT_INVALID,
                                        ucComponentType, 0);
            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeComponent unknow ComponentType ", ucComponentType);
            return NAS_LCS_CAUSE_UNRECOGNIZED_COMPONENT;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过Component */
    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulUndecodeLen -ulTmpLen;

    /* 跳过未解析码流剩余长度 */
    ulSum         = ulSum + ulUndecodeLen;
    *pulLen       = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRtrnRslt
 Description     : 解析Retrun Result Component对应Para
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRtrnRslt
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                           ucOperationCode;
    VOS_UINT32                          enRslt              = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum               = 0;
    VOS_UINT8                          *pucMsgTmp           = pucSrc;
    VOS_UINT32                          ulUndecodeLen       = *pulLen;
    VOS_UINT32                          ulTmpLen            = 0;
    VOS_UINT32                          ulValueLen          = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    *pulLen  = 0;

    /* 获取component长度, TLV格式 */
    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_RTN_RSLT,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_DecodeRtrnRslt Len Decode Fail ");
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过Len */
    ulSum              = ulSum + ulTmpLen;

    /* 获取剩余解析长度,以实际信元中LEN为准 */
    ulUndecodeLen      = ulValueLen;
    ulTmpLen           = ulUndecodeLen;

    /* 解析INVOKE ID */
    enRslt  = NAS_LCS_DecodeInvokeId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_INVOKE, NAS_LCS_MISS_MANDATORY_IE, 0, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_DecodeRtrnRslt Invoke Id Decode Fail ");

        /*缺少Invoke Id,返回信息给网络侧*/
        return enRslt;
    }

    /* 跳过INVOKE ID */
    ulSum         = ulSum + ulTmpLen;

    /* 计算剩余解析长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 解析可选信元Sequence */
    if ((0 < ulUndecodeLen) && (NAS_LCS_SEQUENCE_TAG == pucMsgTmp[ulSum]))
    {
        ulTmpLen = ulUndecodeLen;

        /* 解析Len */
        enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);

        /* 可选信元译码失败, 结束译码 */
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            ulSum     = ulSum + ulUndecodeLen;
            *pulLen   = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过Sequence */
        ulSum         = ulSum + ulTmpLen;

        /* 计数剩余长度 */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
    }

    /* 解析可选信元Operation Code和Parameters */
    if ((0 < ulUndecodeLen) && (NAS_LCS_OPERATION_CODE_TAG == pucMsgTmp[ulSum]))
    {
        /* 解析Operation Code */
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeOperationCode(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru, &ucOperationCode);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过Opertion Code */
        ulSum = ulSum + ulTmpLen;

        /* 计算剩余长度 */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* 根据操作码，如果有component参数，做相应的解码处理 */
        if (0 < ulUndecodeLen)
        {
            ulTmpLen = ulUndecodeLen;
            switch(ucOperationCode)
            {
                /* 解析Mo-lr Result */
                case NAS_LCS_OPERATION_MO_LR:
                    enRslt = NAS_LCS_DecodeMoLrResult(  pucMsgTmp + ulSum,
                                                        &ulTmpLen,
                                                        &pstCnMsgStru->stMolrResult);
                    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                    {
                        pstCnMsgStru->bitOpMolrResult = pstCnMsgStru->stMolrResult.bitOpDecipherKeys \
                                                        | pstCnMsgStru->stMolrResult.bitOpHGmlcAddr \
                                                        | pstCnMsgStru->stMolrResult.bitOpLocationEstimate \
                                                        | pstCnMsgStru->stMolrResult.bitOpReferNumber \
                                                        | pstCnMsgStru->stMolrResult.bitOpRepPlmnList \
                                                        | pstCnMsgStru->stMolrResult.bitOpShortCircuit \
                                                        | pstCnMsgStru->stMolrResult.bitOpVelocityEstimate;
                    }

                    /* 跳过Parameters */
                    ulSum         = ulSum + ulTmpLen;
                    ulUndecodeLen = ulUndecodeLen - ulTmpLen;
                    break;

                default:
                    /* 跳过剩余剩余长度 */
                    ulSum   = ulSum + ulUndecodeLen;
                    *pulLen = ulSum;
                    NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_OPERA,
                                                NAS_LCS_UNKNOWN_OPER,
                                                ucOperationCode, 0);
                    NAS_LCS_INFO_LOG(" NAS_LCS_DecodeRtrnRslt Invoke Id Decode Fail ");
                    return NAS_LCS_CAUSE_SUCCESS;
            }
        }
    }

    /* 跳过剩余未解析码流长度 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstLocEstimate
 Description     : 解析Mo LR网侧回复中信元LocEstimate Value
 Input           : pucSrc                       :码流
                   ulLen                        :信元LEN值
                   pstMolrRst                   :解析后结构
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    /* 防止不定长度结束标志当做信元解析 */
    if (NAS_LCS_OP_TRUE == pstMolrRst->bitOpLocationEstimate)
    {
        return;
    }

    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeLocEstimate( pucSrcTmp + ulSum,
                                        &ulTmpLen,
                                        &pstMolrRst->stLocationEstimate);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        pstMolrRst->bitOpLocationEstimate = NAS_LCS_OP_TRUE;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstDecipherKey
 Description     : 解析Mo LR网侧回复中信元DecipherKey
 Input           : pucSrc                       :码流
                   ulLen                        :信元LEN值
                   pstMolrRst                   :解析后结构
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstDecipherKey
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulSum = 0;

    if (NAS_LCS_DECIPHER_KEYS_LEN == ulUndecodeLen)
    {
        NAS_LCS_MEM_CPY_S(  pstMolrRst->aucDecipherKeys,
                            NAS_LCS_DECIPHER_KEYS_LEN,
                            pucSrcTmp + ulSum,
                            NAS_LCS_DECIPHER_KEYS_LEN);

        pstMolrRst->bitOpDecipherKeys = NAS_LCS_OP_TRUE;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstAddLocEstimate
 Description     : 解析Mo LR网侧回复中信元AddLocEstimate
 Input           : pucSrc                       :码流
                   ulLen                        :信元LEN值
                   pstMolrRst                   :解析后结构
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstAddLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    ulTmpLen = ulUndecodeLen;

    if (NAS_LCS_OP_TRUE == pstMolrRst->bitOpLocationEstimate)
    {
        return;
    }

    enRslt = NAS_LCS_DecodeAddLocEstimate(  pucSrcTmp + ulSum,
                                            &ulTmpLen,
                                            &pstMolrRst->stLocationEstimate);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        pstMolrRst->bitOpLocationEstimate = NAS_LCS_OP_TRUE;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstVelEstimate
 Description     : 解析Mo LR网侧回复中信元VelEstimate
 Input           : pucSrc                       :码流
                   ulLen                        :信元LEN值
                   pstMolrRst                   :解析后结构
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstVelEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    ulTmpLen = ulUndecodeLen;

    enRslt = NAS_LCS_DecodeVelEstimate( pucSrcTmp + ulSum,
                                        &ulTmpLen,
                                        &pstMolrRst->stVelocityEstimate);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        pstMolrRst->bitOpVelocityEstimate = NAS_LCS_OP_TRUE;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstHGmlcAddr
 Description     : 解析Mo LR网侧回复中信元HGmlcAddr
 Input           : pucSrc                       :码流
                   ulLen                        :信元LEN值
                   pstMolrRst                   :解析后结构
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstHGmlcAddr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeHGmlcAddr(   pucSrcTmp + ulSum,
                                        &ulTmpLen,
                                        &pstMolrRst->stHGmlcAddr);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        pstMolrRst->bitOpHGmlcAddr = NAS_LCS_OP_TRUE;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstShortCircuit
 Description     : 解析Mo LR网侧回复中信元ShortCircuit
 Input           : pucSrc                       :码流
                   ulLen                        :信元LEN值
                   pstMolrRst                   :解析后结构
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstShortCircuit
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    VOS_UINT32                          ulUndecodeLen           = ulLen;

    if (0 == ulUndecodeLen)
    {
        pstMolrRst->bitOpShortCircuit = NAS_LCS_OP_TRUE;
    }
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstReportPlmnList
 Description     : 解析Mo LR网侧回复中信元ReportPlmnList
 Input           : pucSrc                       :码流
                   ulLen                        :信元LEN值
                   pstMolrRst                   :解析后结构
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstReportPlmnList
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeReportPlmnList(  pucSrcTmp + ulSum,
                                            &ulTmpLen,
                                            &pstMolrRst->stRepPlmnList);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        if (0 != pstMolrRst->stRepPlmnList.stPlmnList.ucPlmnNum)
        {
            pstMolrRst->bitOpRepPlmnList = NAS_LCS_OP_TRUE;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMoLrResult
 Description     : 解析Mo LR网侧定位结果回复
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeMoLrResult
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;
    VOS_UINT32                          ulLoop                  = 0;

    *pulLen = 0;

    /* 解析TAG和LEN */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /* 跳过剩余码流 */
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PARA,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_DecodeMoLrResult TL decode fail ");
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和LEN */
    ulSum = ulSum + ulTmpLen;

    /* 获取剩余长度,以实际信元中LEN为准 */
    ulUndecodeLen = ulValueLen;

    /* 解析可选信元, 最大循环可选信元个数 */
    while((0 != ulUndecodeLen) && (ulLoop < NAS_LCS_MOLR_RESLT_OP_IE_MAX_NUM))
    {
        ulTmpLen = ulUndecodeLen;

        /* 解析TAG和LEN */
        enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* 可选信元TL解析失败, 跳过该信元剩余码流长度 */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过TAG和LEN */
        ulSum = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen = ulUndecodeLen -ulTmpLen;

        /* 获取该可选信元Value长度 */
        ulTmpLen = ulValueLen;

        /* 根据TAG值解析可选信元 */
        switch(stTagStru.ulNumber)
        {
            /* 解析LocationEstimate */
            case 0:
                NAS_LCS_DecodeMolrRstLocEstimate(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* 解析decipheringKeys */
            case 1:
                NAS_LCS_DecodeMolrRstDecipherKey(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* 解析add-Locationestimate */
            case 2:
                NAS_LCS_DecodeMolrRstAddLocEstimate(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* 解析velocityEstimate */
            case 3:
                NAS_LCS_DecodeMolrRstVelEstimate( pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* 解析referenceNumber */
            case 4:
                pstMolrRst->bitOpReferNumber = NAS_LCS_OP_TRUE;
                pstMolrRst->ucReferNumber = pucSrcTmp[ulSum];
                break;

            /* 解析h-gmlc-address */
            case 5:
                NAS_LCS_DecodeMolrRstHGmlcAddr(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* 解析mo-lrShortCircuit */
            case 6:
                NAS_LCS_DecodeMolrRstShortCircuit(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* 解析reportingPLMNList */
            case 7:
                NAS_LCS_DecodeMolrRstReportPlmnList(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

             default:
                ulSum   = ulSum + ulUndecodeLen;
                *pulLen = ulSum;
                NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PARA,
                                            NAS_LCS_UNKNOWN_OP_IE,
                                            stTagStru.ulNumber, 0);
                NAS_LCS_INFO_LOG(" NAS_LCS_DecodeMoLrResult TL decode fail ");
                return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过可选信元Value长度 */
        ulSum         = ulSum + ulValueLen;
        ulUndecodeLen = ulUndecodeLen - ulValueLen;

        /* 循环解析次数加1 */
        ulLoop++;
    }

    ulSum = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLatitude
 Description     : 解析纬度
 Input           : pucSrc                       :码流
 Output          : penLatitudeSign              :南北纬标识
                   pulDegreeLatitude            :纬度
 Return          : None

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeLatitude
(
    VOS_UINT8                          *pucSrc,
    LOC_COM_LATITUDE_SIGN_ENUM_UINT8   *penLatitudeSign,
    VOS_UINT32                         *pulDegreeLatitude
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* 赋值南北纬枚举 */
    if (0 == (pucMsgTmp[ulSum] & NAS_LCS_MSG_8_BIT))
    {
        *penLatitudeSign = LOC_COM_LATITUDE_SIGN_NORTH;
    }
    else
    {
        *penLatitudeSign = LOC_COM_LATITUDE_SIGN_SOUTH;
    }

    /* 赋值纬度 */
    *pulDegreeLatitude  =   (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT) << NAS_LCS_MOVEMENT_16_BITS;
    *pulDegreeLatitude  |=  (pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS);
    *pulDegreeLatitude  |=  pucMsgTmp[ulSum++];
}

/*lint -e713*/
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLongitude
 Description     : 解析经度
 Input           : pucSrc                       :码流
                   pulDegreeLongitude           :经度
 Return          : None

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeLongitude
(
    VOS_UINT8                          *pucSrc,
    VOS_INT32                          *plDegreeLongitude
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* 赋值经度 */
    *plDegreeLongitude  = 0;
    *plDegreeLongitude  =  (pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_16_BITS);
    *plDegreeLongitude  |= (pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS);
    *plDegreeLongitude  |=  pucMsgTmp[ulSum++];

    /* 如果空口传输的24比特是负数，则需要将高8比特补齐为"0xff" */
    if (*plDegreeLongitude >= 0x800000)
    {
        *plDegreeLongitude |= 0xff000000;
    }
}
/*lint +e713*/

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeAltitude
 Description     : 解析纬度
 Input           : pucSrc                       :码流
 Output          : penAltitudeDirection         :高深度标识
                   pusAltitude                  :高度或者深度
 Return          : None

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeAltitude
(
    VOS_UINT8                          *pucSrc,
    LOC_COM_LATITUDE_DIR_ENUM_UINT8    *penAltitudeDirection,
    VOS_UINT16                         *pusAltitude
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* 赋值高深度标识 */
    if (0 == (pucMsgTmp[ulSum] & NAS_LCS_MSG_8_BIT))
    {
        *penAltitudeDirection = LOC_COM_LATITUDE_DIR_HEITHT;
    }
    else
    {
        *penAltitudeDirection = LOC_COM_LATITUDE_DIR_DEPTH;
    }

    /* 赋值高度或者深度 */
    *pusAltitude  =   (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    *pusAltitude  |=  pucMsgTmp[ulSum++];
}


/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPoint
 Description     : 解析位置信息POINT格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstLocationEstimate          :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPoint
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 7)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_POINT, NAS_LCS_LEN_INVAILID, ulLen, 7);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPoint Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_CHOSEN;

    /* 跳过shap type */
    ulSum++;

    /* 译码纬度 */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPoint.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPoint.ulDegreeLatitude);
    ulSum += 3;

    /* 译码经度 */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPoint.lDegreesLongitude);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPointWithCircle
 Description     : 解析位置信息POINT WITH UNCERTAINTITY CIRCLE格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstLocationEstimate          :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPointWithCircle
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 8)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_CIRCLE, NAS_LCS_LEN_INVAILID, ulLen, 8);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPointWithCircle Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_CHOSEN;

    /* 跳过shap type */
    ulSum++;

    /* 译码纬度 */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyCircle.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyCircle.ulDegreesLatitude);
    ulSum += 3;

    /* 译码经度 */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyCircle.lDegreeLongitude);
    ulSum += 3;

    /* 译码不确定度 */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyCircle.ulUncretainty
                                = (pucMsgTmp[ulSum] & NAS_LCS_MSG_LOW_7_BIT);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPointWithEllipse
 Description     : 解析位置信息POINT WITH UNCERTAINTITY ELLIPSE格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstLocationEstimate          :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPointWithEllipse
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 11)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_ELLIPSE, NAS_LCS_LEN_INVAILID, ulLen, 11);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPointWithEllipse Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_CHOSEN;

    /* 跳过shap type */
    ulSum++;

    /* 译码纬度 */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ulDegreesLatitude);
    ulSum += 3;

    /* 译码经度 */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.lDegreesLongitude);
    ulSum += 3;

    /* 译码SEMI MAJOR */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ucUncertaintySemiMajor
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* 译码SEMI MINOR */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ucUncertaintySemiMinor
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* 译码ORIENTATION OF MAJOR AXIS */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ucOrientationMajorAxis
                                = pucMsgTmp[ulSum++];

    /* 译码CONFIDENCE */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ucConfidence
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPointWithAlititudeAndEllipsoid
 Description     : 解析位置信息POINT WITH ALTITUDE AND UNCERTAINTITY ELLIPSOID格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstLocationEstimate          :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPointWithAlititudeAndEllipsoid
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 14)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_ALIT_ELLI, NAS_LCS_LEN_INVAILID, ulLen, 14);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPointWithAlititudeAndEllipsoid Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_CHOSEN;

    /* 跳过shap type */
    ulSum++;

    /* 译码纬度 */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ulDegreesLatitude);
    ulSum += 3;

    /* 译码经度 */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.lDegreesLongtitude);
    ulSum += 3;

    /* 译码高度 */
    NAS_LCS_DecodeAltitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.enAltitudeDirection,
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.usAltitude);
    ulSum += 2;

    /* 译码SEMI MAJOR */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucUncertaintySemiMajor
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* 译码SEMI MINOR */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucUncertaintySemiMinor
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* 译码ORIENTATION OF MAJOR AXIS */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucOrientationMajorAxis
                                = pucMsgTmp[ulSum++];

    /* 译码不确定度 */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucUncertaintyAltitude
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* 译码CONFIDENCE */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucConfidence
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocArc
 Description     : 解析位置信息ARC格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstLocationEstimate          :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocArc
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 13)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_ARC, NAS_LCS_LEN_INVAILID, ulLen, 13);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocArc Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOIDARC_CHOSEN;

    /* 跳过shap type */
    ulSum++;

    /* 译码纬度 */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidArc.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidArc.ulDegreesLatitude);
    ulSum += 3;

    /* 译码经度 */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidArc.lDegreesLongtitude);
    ulSum += 3;

    /* 译码INNER RADIUS */
    pstLocationEstimate->u.stEllipsoidArc.ulInnerRadius = (pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS);
    pstLocationEstimate->u.stEllipsoidArc.ulInnerRadius |= pucMsgTmp[ulSum++];

    /* 译码UNCERTAINTY RADIUS */
    pstLocationEstimate->u.stEllipsoidArc.ucUncertaintyRadius = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* 译码OFFSET ANGLE */
    pstLocationEstimate->u.stEllipsoidArc.ucOffsetAngle = pucMsgTmp[ulSum++];

    /* 译码INCLUEDED ANGLE */
    pstLocationEstimate->u.stEllipsoidArc.ucIncludedAngle = pucMsgTmp[ulSum++];

    /* 译码CONFIDENCE */
    pstLocationEstimate->u.stEllipsoidArc.ucConfidence
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPointWithAltitude
 Description     : 解析位置信息POINT WITH ALTITUDE格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstLocationEstimate          :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPointWithAltitude
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 9)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_ALT, NAS_LCS_LEN_INVAILID, ulLen, 9);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPointWithAltitude Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_CHOSEN;

    /* 跳过shap type */
    ulSum++;

    /* 译码纬度 */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.ulDegreesLatitude);
    ulSum += 3;

    /* 译码经度 */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.lDegreesLatitude);
    ulSum += 3;

    /* 译码高度 */
    NAS_LCS_DecodeAltitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.enAltitudeDirection,
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.usAltitude);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPolygon
 Description     : 解析位置信息POLYGON格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstLocationEstimate          :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPolygon
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;
    VOS_UINT8                           ucPointsNum     = 0;
    VOS_UINT32                          i               = 0;


    /* 取出点个数 */
    ucPointsNum = (pucMsgTmp[ulSum] & NAS_LCS_MSG_LOW_BIT);

    if (0 == ucPointsNum)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_POLYGON, NAS_LCS_POINT_NUM_INVALID, ucPointsNum, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPolygon Point Num Null ", ucPointsNum);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 长度不正确，直接返回失败 */
    if (ulLen < (VOS_UINT32)((6 * ucPointsNum) + 1))
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_POLYGON, NAS_LCS_LEN_INVAILID, ulLen, ((6 * ucPointsNum) + 1));
        NAS_LCS_INFO_LOG2(" NAS_LCS_DecodeLocPolygon Len Invalid ", ulLen, ((6 * ucPointsNum) + 1));
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_POLYGON_CHOSEN;

    /* 跳过shap type */
    ulSum++;

    pstLocationEstimate->u.stPolygon.ulPolygonCnt = ucPointsNum;
    for (i = 0; i < ucPointsNum; i++)
    {
        /* 译码纬度 */
        NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                    &pstLocationEstimate->u.stPolygon.astPolygonArray[i].enLatitudeSign,
                                    &pstLocationEstimate->u.stPolygon.astPolygonArray[i].ulDegreesLatitude);
        ulSum += 3;

        /* 译码经度 */
        NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                    &pstLocationEstimate->u.stPolygon.astPolygonArray[i].lDegreesLatitude);
        ulSum += 3;
    }

    return NAS_LCS_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocEstimate
 Description     : 解析信元locationEstimate
 Input           : pucSrc                       :码流
                   pulLen                       :Value长度
 Output          : pulLen                       :已解析长度
                   pstLocationEstimate          :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT8                           ucShapeType     = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt          = NAS_LCS_CAUSE_SUCCESS;

    *pulLen = 0;

    /* 判断长度是否在1-20之间 */
    if ((0 == ulUndecodeLen) || (NAS_LCS_LOC_ESTIMATE_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_LOC_ESTIMATE,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeLen,
                                    NAS_LCS_LOC_ESTIMATE_MAX_LEN);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocEstimate Undecode Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 取出SHAPE类型 */
    ucShapeType = (pucMsgTmp[ulSum] & NAS_LCS_MSG_HIGH_BIT) >> NAS_LCS_MOVEMENT_4_BITS;

    switch (ucShapeType)
    {
        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT:
            enRslt = NAS_LCS_DecodeLocPoint(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE:
            enRslt = NAS_LCS_DecodeLocPointWithCircle(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE:
            enRslt = NAS_LCS_DecodeLocPointWithEllipse(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID:
            enRslt = NAS_LCS_DecodeLocPointWithAlititudeAndEllipsoid(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOIDARC:
            enRslt = NAS_LCS_DecodeLocArc(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        default :
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_LOC_ESTIMATE,
                                        NAS_LCS_UNKNOWN_SHAPE_TYPE,
                                        ucShapeType,
                                        0);
            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocEstimate Unknown Shape Type ", ucShapeType);
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过IE */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_LCS_DecodeAddLocEstimate
 Description     : 解析信元AdditionallocationEstimate
 Input           : pucSrc                       :码流
                   pulLen                       :Value长度
 Output          : pulLen                       :已解析长度
                   pstLocationEstimate          :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeAddLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT8                           ucShapeType     = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pulLen = 0;

    /* 判断Len是否在1-91之间 */
    if ((0 == ulUndecodeLen) || (NAS_LCS_ADD_LOC_ESTIMATE_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_ADD_LOC_EST,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeLen,
                                    NAS_LCS_ADD_LOC_ESTIMATE_MAX_LEN);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeAddLocEstimate Undecode Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 取出SHAPE类型 */
    ucShapeType = (pucMsgTmp[ulSum] & NAS_LCS_MSG_HIGH_BIT) >> NAS_LCS_MOVEMENT_4_BITS;

    switch (ucShapeType)
    {
        case NAS_LCS_LOC_SHAP_POLYGON:
            enRslt = NAS_LCS_DecodeLocPolygon(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_ALTITUDE:
            enRslt = NAS_LCS_DecodeLocPointWithAltitude(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        default :
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_ADD_LOC_EST,
                                        NAS_LCS_UNKNOWN_SHAPE_TYPE,
                                        ucShapeType, 0);
            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeAddLocEstimate Unknown Shape Type ", ucShapeType);
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHorizontalVelocity
 Description     : 解析速度信息HORIZAONTAL VELOCITY格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstVelEstimate               :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-14  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHorizontalVelocity
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 4)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_HOR_VEL, NAS_LCS_LEN_INVAILID, ulLen, 4);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHorizontalVelocity Len Ivalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstVelEstimate,
                        sizeof(LOC_COM_VELOCITY_STRU),
                        0,
                        sizeof(LOC_COM_VELOCITY_STRU));

    pstVelEstimate->ulChoice = LOC_COM_HORIZONTAL_VELCOCTIY_CHOSEN;

    /* 译码BEARING */
    pstVelEstimate->u.stHorizontalVelocity.usBearing
                        = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_1_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalVelocity.usBearing |= pucMsgTmp[ulSum++];

    /* 译码horizontal speed */
    pstVelEstimate->u.stHorizontalVelocity.usHorizontalSpeed
                        = pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalVelocity.usHorizontalSpeed
                        |= pucMsgTmp[ulSum++];

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHorizontalAndVerticalVelocity
 Description     : 解析速度信息HORIZAONTAL AND VERTICAL VELOCITY格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstVelEstimate               :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-14  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHorizontalAndVerticalVelocity
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 5)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_HOR_VER_VEL,
                                    NAS_LCS_LEN_INVAILID,
                                    ulLen, 5);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHorizontalAndVerticalVelocity Len Ivalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstVelEstimate,
                        sizeof(LOC_COM_VELOCITY_STRU),
                        0,
                        sizeof(LOC_COM_VELOCITY_STRU));

    pstVelEstimate->ulChoice = LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_CHOSEN;

    /* 译码垂直方向 */
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.enVerticalDirection
                        = (pucMsgTmp[ulSum] & NAS_LCS_MSG_2_BIT) >> NAS_LCS_MOVEMENT_1_BITS;

    /* 译码BEARING */
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.usBearing
                        = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_1_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.usBearing |= pucMsgTmp[ulSum++];

    /* 译码horizontal speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.usHorizontalSpeed
                        = pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.usHorizontalSpeed
                        |= pucMsgTmp[ulSum++];

    /* 译码Vertical Speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.ulVerticalSpeed = pucMsgTmp[ulSum++];

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHorizontalVelocityWithUncertainty
 Description     : 解析速度信息HORIZAONTAL VELOCITY WITH UNCERTAINTY格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstVelEstimate               :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-14  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHorizontalVelocityWithUncertainty
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 5)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_HOR_VER_UNCERT, NAS_LCS_LEN_INVAILID, ulLen, 5);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHorizontalVelocityWithUncertainty Len Ivalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstVelEstimate,
                        sizeof(LOC_COM_VELOCITY_STRU),
                        0,
                        sizeof(LOC_COM_VELOCITY_STRU));

    pstVelEstimate->ulChoice = LOC_COM_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_CHOSEN;

    /* 译码BEARING */
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.usBearing
                        = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_1_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.usBearing |= pucMsgTmp[ulSum++];

    /* 译码horizontal speed */
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.usHorizontalSpeed
                        = pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.usHorizontalSpeed
                        |= pucMsgTmp[ulSum++];

    /* 译码Uncertainty Speed */
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.ulUncertaintySpeed = pucMsgTmp[ulSum++];

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHorizontalAndVerticalVelocityWithUncertainty
 Description     : 解析速度信息HORIZAONTAL AND VERTICAL VELOCITY WITH UNCERTAINTY格式
 Input           : pucSrc                       :码流
                   ulLen                        :Value长度
 Output          : pstVelEstimate               :解析后结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.lihong 00150010    2015-10-14  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHorizontalAndVerticalVelocityWithUncertainty
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;

    /* 长度不正确，直接返回失败 */
    if (ulLen < 7)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_HOR_VER_VEL_UNCERT,
                                    NAS_LCS_LEN_INVAILID,
                                    ulLen, 7);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHorizontalAndVerticalVelocityWithUncertainty Len Ivalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstVelEstimate,
                        sizeof(LOC_COM_VELOCITY_STRU),
                        0,
                        sizeof(LOC_COM_VELOCITY_STRU));

    pstVelEstimate->ulChoice = LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_CHOSEN;

    /* 译码垂直方向 */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.enVerticalDirection
                        = (pucMsgTmp[ulSum] & NAS_LCS_MSG_2_BIT) >> NAS_LCS_MOVEMENT_1_BITS;

    /* 译码BEARING */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.usBearing
                        = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_1_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.usBearing |= pucMsgTmp[ulSum++];

    /* 译码horizontal speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.usHorizontalSpeed
                        = pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.usHorizontalSpeed
                        |= pucMsgTmp[ulSum++];

    /* 译码Vertical Speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.ucVerticalSpeed = pucMsgTmp[ulSum++];

    /* 译码Horizonal Uncertainty Speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.ucHorizontalUncertaintySpeed = pucMsgTmp[ulSum++];

    /* 译码Vertical Uncertainty Speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.ucVerticalUncertaintySpeed = pucMsgTmp[ulSum++];

    return NAS_LCS_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_LCS_DecodeVelEstimate
 Description     : 解析信元velocityEstimate
 Input           : pucSrc                       :码流
                   pstRepPlmnList               :解析后结构
                   pulLen                       :剩余解析长度
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeVelEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT8                           ucVelocityType  = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    if ((NAS_LCS_VEL_ESTIMATE_MIN_LEN > ulUndecodeLen)
        || (NAS_LCS_VEL_ESTIMATE_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_VEL_ESTIMATE,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeVelEstimate Len Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 取出速度类型 */
    ucVelocityType = (pucMsgTmp[ulSum] & NAS_LCS_MSG_HIGH_BIT) >> NAS_LCS_MOVEMENT_4_BITS;

    switch (ucVelocityType)
    {
        case NAS_LCS_VELOCITY_TYPE_HORIZONTAL_VELOCITY:
            enRslt = NAS_LCS_DecodeHorizontalVelocity(pucMsgTmp, ulUndecodeLen, pstVelEstimate);
            break;

        case NAS_LCS_VELOCITY_TYPE_HORIZONTAL_WITH_VERTICAL_VELOCITY:
            enRslt = NAS_LCS_DecodeHorizontalAndVerticalVelocity(pucMsgTmp, ulUndecodeLen, pstVelEstimate);
            break;

        case NAS_LCS_VELOCITY_TYPE_HORIZONTAL_VELOCITY_WITH_UNCERTAINTY:
            enRslt = NAS_LCS_DecodeHorizontalVelocityWithUncertainty(pucMsgTmp, ulUndecodeLen, pstVelEstimate);
            break;

        case NAS_LCS_VELOCITY_TYPE_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY:
            enRslt = NAS_LCS_DecodeHorizontalAndVerticalVelocityWithUncertainty(pucMsgTmp, ulUndecodeLen, pstVelEstimate);
            break;

        default :
            NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_VEL_ESTIMATE, NAS_LCS_UNKNOWN_VEL_TYPE, ucVelocityType, 0);
            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeVelEstimate Unknown VelocityType ", ucVelocityType);
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHGmlcAddr
 Description     : 解析信元h-gmlc-address
 Input           : pucSrc                       :码流
                   pstRepPlmnList               :解析后结构
                   pulLen                       :剩余解析长度
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHGmlcAddr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_HGMLC_ADDR_STRU             *pstHGmlcAddr
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen = 0;

    /* 判断Len是否在5-17之间 */
    if ((NAS_LCS_HGMALC_ADD_MIN_LEN > ulUndecodeLen)
        || (NAS_LCS_HGMALC_ADD_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_HGMLC_ADDR,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHGmlcAddr Len Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 保存Hgmlc */
    NAS_LCS_MEM_CPY_S(  pstHGmlcAddr->aucHGmlcAddr,
                        NAS_LCS_HGMALC_ADD_MAX_LEN,
                        pucMsgTmp,
                        ulUndecodeLen);

    pstHGmlcAddr->ucLen = (VOS_UINT8)ulUndecodeLen;

    *pulLen = ulUndecodeLen;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeReportPlmnList
 Description     : 解析信元reportingPLMNList
 Input           : pucSrc                       :码流
                   pstRepPlmnList               :解析后结构
                   pulLen                       :剩余解析长度
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeReportPlmnList
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REPORT_PLMN_LIST_STRU       *pstRepPlmnList
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulValueLen      = 0;

    ulTmpLen = ulUndecodeLen;

    /* 解析可选信元plmn-ListPrioritized */
    /* 解析TAG和LEN */
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        ulSum   = ulSum + ulUndecodeLen;
        *pulLen = ulSum;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_REP_PLMN_LIST,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeReportPlmnList Len Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    if (0 == stTagStru.ulNumber)
    {
        /* 跳过TAG和LEN */
        ulSum         = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* 判断长度是否合法 */
        if (0 == ulValueLen)
        {
            pstRepPlmnList->bitOpPlmnPriority = NAS_LCS_OP_TRUE;
        }

        /* 跳过Value长度 */
        ulSum         = ulSum + ulValueLen;
        ulUndecodeLen = ulUndecodeLen - ulValueLen;
    }

    /* 获取剩余码流长度 */
    ulTmpLen = ulUndecodeLen;

    /* 解析必选信元plmn-list */
    enRslt   = NAS_LCS_DecodePlmnList(pucMsgTmp + ulSum, &ulTmpLen, &pstRepPlmnList->stPlmnList);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过plmn-list */
    ulSum = ulSum + ulTmpLen;
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return enRslt;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodePlmnList
 Description     : 解析信元plmn-list
 Input           : pucSrc                       :码流
                   pstPlmnList                  :解析后结构
                   pulLen                       :剩余解析长度
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodePlmnList
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_PLMN_LIST_STRU              *pstPlmnList
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulValueLen      = 0;
    VOS_UINT8                           ucIndex         = 0;

    *pulLen = 0;

    /* 解析TAG和LEN */
    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_REP_PLMN_LIST,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeReportPlmnList Len Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和LEN */
    ulSum         = ulSum + ulTmpLen;

    /* 获取实际IE剩余码流长度 */
    ulUndecodeLen = ulValueLen;

    /* 判断TAG是否正确 */
    if (1 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_REP_PLMN_LIST,
                                    NAS_LCS_MISS_MANDATORY_IE,
                                    stTagStru.ulNumber, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeReportPlmnList decode Plmn-list fail ", ulUndecodeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 循环解析PLMN信息 */
    while(0 != ulUndecodeLen)
    {
        /* 解析并跳过Sequence TL */
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PLMN_LIST,
                                        NAS_LCS_LEN_DECODE_FAIL,
                                        ulUndecodeLen,
                                        0);
            return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
        }

        /* 跳过TAG和LEN */
        ulSum = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /*获取该信元Value长度*/
        ulTmpLen = ulValueLen;

        /* 解析PLMN */
        ucIndex = pstPlmnList->ucPlmnNum;
        enRslt = NAS_LCS_DecodePlmn(    pucMsgTmp + ulSum,
                                        &ulTmpLen,
                                        &pstPlmnList->astPlmn[ucIndex]);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            *pulLen = ulSum + ulUndecodeLen;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* PLMN个数加1 */
        pstPlmnList->ucPlmnNum++;

        /* 跳过Value长度 */
        ulSum = ulSum + ulValueLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen = ulUndecodeLen - ulValueLen;

        /* 最多支持携带20个PLMN信息 */
        if (NAS_LCS_REP_PLMN_MAX_NUM <= pstPlmnList->ucPlmnNum)
        {
            /* 跳过剩余未解析码流长度 */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }
    }

    /* 跳过剩余未解析码流长度 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodePlmn
 Description     : 解析信元plmn
 Input           : pucSrc                       :码流
                   pstPlmn                      :解析后结构
                   pulLen                       :剩余解析长度
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodePlmn
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_PLMN_STRU                   *pstPlmn
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulValueLen      = 0;
    VOS_UINT32                          ulLoop          = 0;

    *pulLen = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PLMN, NAS_LCS_UNDECODE_LEN_INVAlID,
                                    0, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodePlmn Undecode Len Invalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和LEN */
    ulSum = ulSum + ulTmpLen;

    /* 计算剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 解析必选信元plmn-id */
    if ((0 == stTagStru.ulNumber) && (3 == ulValueLen))
    {
        pstPlmn->stPlmnId.aucPlmnId[0] = pucMsgTmp[ulSum];
        ulSum++;
        pstPlmn->stPlmnId.aucPlmnId[1] = pucMsgTmp[ulSum];
        ulSum++;
        pstPlmn->stPlmnId.aucPlmnId[2] = pucMsgTmp[ulSum];
        ulSum++;
        ulUndecodeLen = ulUndecodeLen - ulValueLen;
    }
    else
    {
        ulSum = ulSum + ulUndecodeLen;
        *pulLen = ulSum;
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_PLMN, NAS_LCS_MISS_PLMN_ID, 0, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodePlmn Miss Plmn Id ", stTagStru.ulNumber);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 解析可选信元 */
    while ((0 < ulUndecodeLen) && (ulLoop < NAS_LCS_PLMN_OP_IE_MAX_NUM))
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过TAG和LEN */
        ulSum = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* 根据TAG值解析可选信元 */
        switch(stTagStru.ulNumber)
        {
            /* 解析ran-Technology */
            case 1:
                pstPlmn->enRanTech = pucMsgTmp[ulSum];
                pstPlmn->bitOpRanTech = NAS_LCS_OP_TRUE;
                break;

            /* 解析ran-PerodicLocationSupport */
            case 2:
                if (0 == ulValueLen)
                {
                    pstPlmn->bitOpRanPerLocSupp = NAS_LCS_OP_TRUE;
                }
                break;

            default:
                /* 跳过剩余码流 */
                ulSum = ulSum + ulUndecodeLen;
                *pulLen = ulSum;
                return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 可选信元跳过Value长度, 不用考虑解析结果 */
        ulSum         = ulSum + ulValueLen;
        ulUndecodeLen = ulUndecodeLen - ulValueLen;

        /* 循环次数加1, 最大循环次数为可选信元个数 */
        ulLoop++;
    }

    /* 跳过剩余未解析码流 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeErrorCode
 Description     : 解析Error code
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulDecodeMsgLen              :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeErrorCode
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    VOS_UINT32                          ulValueLen      = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    /* 判断ERROR CODE TAG是否正确 */
    if ((0 == ulUndecodeLen) || (NAS_LCS_ERROR_CODE_TAG != pucMsgTmp[ulSum]))
    {
        *pulLen = ulUndecodeLen;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_ERROR_CODE,
                                    NAS_LCS_TAG_ERROR,
                                    pucMsgTmp[ulSum],
                                    NAS_LCS_ERROR_CODE_TAG);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeRtrnErr Error code Tag Invalid ", pucMsgTmp[ulSum]);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 获取Error Code长度, TLV格式 */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        *pulLen = ulUndecodeLen;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_ERROR_CODE,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和Len */
    ulSum = ulSum + ulTmpLen;

    /* TAG和ERROR CODE组合成网络原因值 */
    pstCnMsgStru->enNwCause = (NAS_LCS_ERROR_CODE_TAG << NAS_LCS_MOVEMENT_8_BITS) + pucMsgTmp[ulSum];
    pstCnMsgStru->bitOpNwCause = NAS_LCS_OP_TRUE;

    /* 跳过Value */
    ulSum = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRtrnErr
 Description     : 解析Retrun Error Component
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulDecodeMsgLen              :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRtrnErr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    VOS_UINT32                          ulValueLen      = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    *pulLen = 0;

    /*获取component长度, TLV格式，同时指针移位至V，确定结束位置*/
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和Len */
    ulSum         = ulSum + ulTmpLen;

    /* 获取剩余该信元码流长度, 以信元中携带的L为准 */
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* 解析INVOKE ID */
    enRslt  = NAS_LCS_DecodeInvokeId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /*缺少Invoke Id,返回信息给网络侧*/
        return enRslt;
    }

    /* 跳过INVOKE ID */
    ulSum = ulSum + ulTmpLen;

    /* 计算剩余信元长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 解析Error Code */
    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeErrorCode(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /*缺少Error Code,返回信息给网络侧*/
        return enRslt;
    }

    /* 跳过Error Code */
    ulSum = ulSum + ulTmpLen;

    /* 计算信元剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 跳过剩余未解析码流 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodePromblemCode
 Description     : 解析Promblem Code
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodePromblemCode
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    VOS_UINT32                          ulValueLen      = 0;
    NAS_LCS_PROBLEM_TAG_ENUM_UINT8      enProblemTag;
    NAS_LCS_TAG_STRU                    stTagStru;

    /* 解析Problem Code */
    /* 检查Problem TAG值是否合法 */
    if ((0 == ulUndecodeLen) || (NAS_LCS_CAUSE_SUCCESS != NAS_LCS_CheckProblemTagVaild(pucMsgTmp[ulSum])))
    {
        /* 跳过剩余码流 */
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PROBLEM_CODE,
                                    NAS_LCS_TAG_ERROR,
                                    pucMsgTmp[ulSum], 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 获取ProblemTag */
    enProblemTag = pucMsgTmp[ulSum];

    ulTmpLen     = ulUndecodeLen;

    /* 获取Problem Code长度, TLV格式 */
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /* 跳过剩余码流 */
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_PROBLEM_CODE, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和Len */
    ulSum = ulSum + ulTmpLen;

    /* TAG和ERROR CODE组合成网络原因值 */
    pstCnMsgStru->enNwCause = (enProblemTag << NAS_LCS_MOVEMENT_8_BITS) + pucMsgTmp[ulSum];
    pstCnMsgStru->bitOpNwCause = NAS_LCS_OP_TRUE;

    /* 跳过Problem IE Value */
    ulSum   = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeReject
 Description     : 解析Rej Component
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeReject
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    VOS_UINT32                          ulValueLen      = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    ulTmpLen = ulUndecodeLen;

    *pulLen = 0;

    /*获取component长度, TLV格式，同时指针移位至V，确定结束位置*/
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_COMPONENT, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_DecodeReject Len decode Fail ");
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和Len */
    ulSum         = ulSum + ulTmpLen;

    /* 获取Component IE剩余码流长度*/
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* 解析必选信元INVOKE ID */
    enRslt  = NAS_LCS_DecodeInvokeId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /*缺少Invoke Id,返回信息给网络侧*/
        return enRslt;
    }

    /* 跳过INVOKE ID */
    ulSum         = ulSum + ulTmpLen;

    /* 计算剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 解析必选Problem Code */
    enRslt = NAS_LCS_DecodePromblemCode(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过Problem Code */
    ulSum         = ulSum + ulTmpLen;

    /* 计算剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 跳过剩余码流 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeInvoke
 Description     : 解析Invoke Component
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeInvoke
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                           ucOperationCode;
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulValueLen         = 0;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    *pulLen = 0;

    ulTmpLen = ulUndecodeLen;

    /* 获取component长度, TLV格式 */
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_COMPONENT, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和Len */
    ulSum         = ulSum + ulTmpLen;

    /* 获取剩余码流长度, 以Component信元中L为准 */
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* 解析INVOKE ID */
    enRslt  = NAS_LCS_DecodeInvokeId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /* 缺少Invoke Id,返回信息给网络侧 */
        return enRslt;
    }

    /* 跳过INVOKE ID */
    ulSum = ulSum + ulTmpLen;

    /* 计算剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 解析LINKED ID */
    enRslt = NAS_LCS_DecodeLinkedId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        /* 跳过LINKED ID */
        ulSum = ulSum + ulTmpLen;
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
        pstCnMsgStru->bitOpLinkedId = NAS_LCS_OP_TRUE;
    }

    /* 解析Operation Code */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeOperationCode(   pucMsgTmp + ulSum,
                                            &ulTmpLen,
                                            pstCnMsgStru,
                                            &ucOperationCode);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过Opertion Code */
    ulSum         = ulSum + ulTmpLen;

    /* 获取剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /*根据操作码，如果有component参数，做相应的解码处理*/
    if (0 < ulUndecodeLen)
    {
        ulTmpLen      = ulUndecodeLen;
        switch(ucOperationCode)
        {
            /* 解析Loc Notification Parameters */
            case NAS_LCS_OPERATION_LOC_NOTIFICATION:
                enRslt = NAS_LCS_DecodeLocNotification( pucMsgTmp + ulSum,
                                                        &ulTmpLen,
                                                        &pstCnMsgStru->stLocNotication);
                if (NAS_LCS_CAUSE_SUCCESS != enRslt)
                {
                    return enRslt;
                }

                pstCnMsgStru->bitOpLocNotification = NAS_LCS_OP_TRUE;
                break;

            /* 当前LCS不支持Operation, 抛出可维可测, 由外层回复Rel Cmp */
            default:
                ulSum   = ulSum + ulUndecodeLen;
                *pulLen = ulSum;
                NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_COMPONENT,
                                            NAS_LCS_OPERA_INVALID,
                                            ucOperationCode, 0);
                return NAS_LCS_CAUSE_SUCCESS;
        }

        ulSum = ulSum + ulTmpLen;
    }

    *pulLen = ulSum;
    return enRslt;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeInvokeId
 Description     : 解析Invoke Id
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulDecodeMsgLen              :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeInvokeId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    /* 检查剩余码流长度和TAG是否正确 */
    if ((3 <= ulUndecodeLen) && (NAS_LCS_INVOKE_ID_TAG == pucMsgTmp[ulSum]))
    {
        /* 跳过TAG */
        ulSum++;

        /* 跳过Len */
        ulSum++;

        /* 保存Invoke id */
        pstCnMsgStru->ucInvokeId = pucMsgTmp[ulSum++];
        pstCnMsgStru->bitOpInvokeId = NAS_LCS_OP_TRUE;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_INVOKE,
                                    NAS_LCS_MISS_INVOKE_ID,
                                    pucMsgTmp[ulSum],
                                    NAS_LCS_INVOKE_ID_TAG);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLinkedId
 Description     : 解析Linked Id
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLinkedId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen = 0;

    if ((3 <= ulUndecodeLen) && (NAS_LCS_LINKED_ID_TAG == pucMsgTmp[ulSum]))
    {
        /* 跳过Tag */
        ulSum++;

        /* 跳过Len */
        ulSum++;

        /* 保存Linked Id */
        pstCnMsgStru->bitOpLinkedId = NAS_LCS_OP_TRUE;
        pstCnMsgStru->ucLinkedId    = pucMsgTmp[ulSum];

        /* 跳过Linked Id */
        ulSum++;
    }
    else
    {
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeOperationCode
 Description     : 解析Operation Code
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulDecodeMsgLen              :已解析长度
                   pucOperationCode             :Operation Code
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeOperationCode
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru,
    VOS_UINT8                           *pucOperationCode
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ucOperationCode;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen = 0;

    /* 检查剩余码流是否大于OPeration Code IE长度 */
    if (3 > ulUndecodeLen)
    {
        /*缺少operation code，返回信息给网络侧*/
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    if (NAS_LCS_OPERATION_CODE_TAG == pucMsgTmp[ulSum])
    {
        /* 跳过Operation Code Tag */
        ulSum++;

        /* 跳过Len */
        ulSum++;

        /*获取操作码*/
        ucOperationCode = pucMsgTmp[ulSum++];

        /*如果检查Operation是否当前LCS支持, 若不支持抛出可维可测, 由外层处理回复Rel Cmp*/
        if (NAS_LCS_CAUSE_SUCCESS != NAS_LCS_CheckOperationCode(ucOperationCode))
        {
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_OPERA_CODE,
                                        NAS_LCS_OPERA_INVALID,
                                        ucOperationCode, 0);

        }

        /* 记录operationcode */
        pstCnMsgStru->bitOperationCode = NAS_LCS_OP_TRUE;
        pstCnMsgStru->ucOperationCode  = ucOperationCode;
        *pucOperationCode              = ucOperationCode;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_OPERA_CODE,
                                    NAS_LCS_TAG_ERROR,
                                    pucMsgTmp[ulSum],
                                    NAS_LCS_OPERATION_CODE_TAG);

        /*缺少operation code，返回信息给网络侧*/
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocNotification
 Description     : 解析Operation Lcs-LocationNotification 相应para
 Input           : pucSrc                       :码流
                   pstCnMsgStru                 :解析后结构
 Output          : pulDecodeMsgLen              :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocNotification
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOC_NOTFICATION_STRU        *pstLocNtfStru
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;
    ulTmpLen = ulUndecodeLen;

    /* 解析TAG和LEN */
    enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_NTF, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和LEN */
    ulSum = ulSum + ulTmpLen;

    /* 获取剩余长度,以实际信元中LEN为准 */
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* 解析notificationType */
    enRslt = NAS_LCS_DecodeNotificationType(    pucSrcTmp + ulSum,
                                                &ulTmpLen,
                                                &pstLocNtfStru->enNtfType);

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过notificationType */
    ulSum = ulSum + ulTmpLen;

    /* 计算剩余长度 */
    ulUndecodeLen   = ulUndecodeLen - ulTmpLen;
    ulTmpLen        = ulUndecodeLen;

    /* 解析locationtype */
    enRslt = NAS_LCS_DecodeLocationType(    pucSrcTmp + ulSum,
                                            &ulTmpLen,
                                            &pstLocNtfStru->stLocationType);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过notificationType */
    ulSum = ulSum + ulTmpLen;

    /* 计算剩余Value长度 */
    ulUndecodeLen  = ulUndecodeLen - ulTmpLen;
    ulTmpLen       = ulUndecodeLen;

    /* 解析Notifcation中的可选信元 */
    (VOS_VOID)NAS_LCS_DecodeNotificationOpIe(pucSrcTmp + ulSum, &ulTmpLen, pstLocNtfStru);

    /* 跳过剩余长度 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeNotificationOpIe
 Description     : 解析Loc Notification可选信元
 Input           : pucSrc                       :码流
                   pstLocNtfStru                :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeNotificationOpIe
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOC_NOTFICATION_STRU        *pstLocNtfStru
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;
    VOS_UINT32                          ulLoop                  = 0;

    *pulLen = 0;

    while ((0 != ulUndecodeLen) && (ulLoop < NAS_LCS_LOC_NTF_OP_IE_MAX_NUM))
    {
        ulTmpLen = ulUndecodeLen;

        /* 解析TAG和LEN */
        enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if ((NAS_LCS_CAUSE_SUCCESS != enRslt))
        {
            /* 可选信元TL译码失败, 直接返回, 跳过剩余长度 */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过TAG和LEN */
        ulSum         = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* 获取信元Value长度 */
        ulTmpLen      = ulValueLen;

        switch (stTagStru.ulNumber)
        {
            case 2:
                enRslt = NAS_LCS_DecodeCilentExtId( pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstLocNtfStru->stClientExternalId);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    /* 该可选信元是由子可选信元组成 */
                    pstLocNtfStru->bitOpClientExternalId = pstLocNtfStru->stClientExternalId.bitOpExternalAddr;
                }
                break;

            case 3:
                enRslt = NAS_LCS_DecodeClientName(  pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstLocNtfStru->stClientName);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    /* 该信元的自信元中有必选信元, 译码成功, Bit位置上 */
                    pstLocNtfStru->bitOpClientName = NAS_LCS_OP_TRUE;
                }
                break;

            case 4:
                enRslt = NAS_LCS_DecodeRequestorID( pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstLocNtfStru->stRequestorId);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    pstLocNtfStru->bitOpRequestorId = NAS_LCS_OP_TRUE;
                }
                break;

            case 5:
                enRslt = NAS_LCS_DecodeCodeWord(    pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstLocNtfStru->stCodeWord);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    pstLocNtfStru->bitOpCodeWord = NAS_LCS_OP_TRUE;
                }
                break;

            case 6:
                enRslt = NAS_LCS_DecodeServiceTypeId(   pucSrcTmp + ulSum,
                                                        &ulTmpLen,
                                                        &pstLocNtfStru->ucServiceTypeId);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    pstLocNtfStru->bitOpServiceTypeId = NAS_LCS_OP_TRUE;
                }
                break;

            default:
                ulSum   = ulSum + ulUndecodeLen;
                *pulLen = ulSum;
                return NAS_LCS_CAUSE_SUCCESS;
        }

        ulSum          = ulSum + ulValueLen;
        ulUndecodeLen  = ulUndecodeLen - ulValueLen;

        /* 循环解析次数累加 */
        ulLoop++;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeNotificationOpIe
 Description     : 解析Requestor ID信元中的必选信元DataCodingScheme
 Input           : pucSrc                       :码流
                   pstRequestorId               :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeReqIdDataCodingScheme
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REQUESTOR_ID_STRU           *pstRequestorId
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_REQUESTOR_ID,
                                    NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和LEN */
    ulSum         = ulSum + ulTmpLen;

    /* 获取该信元剩余码流长度 */
    ulUndecodeLen = ulValueLen;

    /* 解析dataCodingScheme */
    if (0 == stTagStru.ulNumber)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeDataCodingScheme(    pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstRequestorId->ucDataCodeScheme);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return enRslt;
        }

        /* 跳过dataCodingScheme */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
        ulSum         = ulSum + ulTmpLen;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_DATA_CODE_SHM,
                                    NAS_LCS_TAG_ERROR,
                                    stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过该IE剩余码流 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRequestorID
 Description     : 解析Requestor ID信元
 Input           : pucSrc                       :码流
                   pstRequestorId               :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRequestorID
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REQUESTOR_ID_STRU           *pstRequestorId
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;

    /* 解析必选dataCodingScheme */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeReqIdDataCodingScheme(pucSrcTmp + ulSum, &ulTmpLen, pstRequestorId);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过dataCodingScheme */
    ulSum         = ulSum + ulTmpLen;

    /* 获取该IE剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 解析RequestorIDString */
    ulTmpLen      = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeRequestorIDString(pucSrcTmp + ulSum, &ulTmpLen, &pstRequestorId->stReqString);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过RequestorIDString */
    ulSum         = ulSum + ulTmpLen;

    /* 获取该IE剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 判断是否有可选信元 */
    if (0 < ulUndecodeLen)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt   = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* 可选信元跳过剩余长度 */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过TAG和LEN */
        ulSum         = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* 获取可选信元Value长度 */
        ulTmpLen      = ulValueLen;

        /* 解析可选信元lcs-FormatIndicator */
        if (2 == stTagStru.ulNumber)
        {
            ulTmpLen = ulValueLen;
            enRslt = NAS_LCS_DecodeFormatIndicator( pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstRequestorId->enLcsFormat);
            if (NAS_LCS_CAUSE_SUCCESS == enRslt)
            {
                pstRequestorId->bitOpLcsFormat = NAS_LCS_OP_TRUE;
            }
        }
        /* 跳过可选信元Value长度 */
        ulSum           = ulSum + ulValueLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen   = ulUndecodeLen - ulValueLen;
    }

    /* 跳过该信元剩余未解析码流 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRequestorIDString
 Description     : 解析RequestorIDString信元
 Input           : pucSrc                       :码流
                   pstReqString                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRequestorIDString
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REQUESTOR_ID_STRING_STRU    *pstReqString
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    *pulLen = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_REQ_ID_STRING,
                                    NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TL */
    ulSum = ulSum + ulTmpLen;

    /* 获取该信元剩余码流长度 */
    ulUndecodeLen = ulValueLen;

    /* 判断TAG是否正确 */
    if (1 != stTagStru.ulNumber)
    {
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 检查长度是否合法 */
    if ((NAS_LCS_REQUESTOR_ID_STRING_MAX_LEN < ulValueLen) || (0 == ulValueLen))
    {
        ulSum  = ulUndecodeLen;
        *pulLen = ulSum;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_REQ_ID_STRING,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen,
                                    ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 保存 */
    pstReqString->ucLen = (VOS_UINT8)ulValueLen;

    NAS_LCS_MEM_CPY_S(  pstReqString->aucReqIdString,
                        NAS_LCS_REQUESTOR_ID_STRING_MAX_LEN,
                        (pucSrcTmp + ulSum),
                        ulValueLen);

    /* 跳过Value */
    ulSum = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCodeWordDataCodingScheme
 Description     : 解析lcs Code Word信元中的必选信元DataCodingScheme
 Input           : pucSrc                       :码流
                   pstCodeWord                  :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCodeWordDataCodingScheme
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CODE_WORD_STRU              *pstCodeWord
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen  = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_CODE_WORD, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和LEN */
    ulSum           = ulSum + ulTmpLen;

    /* 获取信元剩余码流长度 */
    ulUndecodeLen   = ulValueLen;

    /* 解析dataCodingScheme */
    if (0 == stTagStru.ulNumber)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeDataCodingScheme(    (pucSrcTmp + ulSum),
                                                    &ulTmpLen,
                                                    &pstCodeWord->ucDataCodeScheme);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return enRslt;
        }

        /* 跳过dataCodingScheme */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
        ulSum         = ulSum + ulTmpLen;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_DATA_CODE_SHM,
                                    NAS_LCS_TAG_ERROR,
                                    stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过该信元剩余码流长度 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCodeWord
 Description     : 解析lcs Code Word信元
 Input           : pucSrc                       :码流
                   pstCodeWord                  :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCodeWord
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CODE_WORD_STRU              *pstCodeWord
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulSum                   = 0;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;

    /* 解析必选信元dataCodingScheme */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeCodeWordDataCodingScheme(pucSrcTmp + ulSum, &ulTmpLen, pstCodeWord);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过dataCodingScheme */
    ulSum = ulSum + ulTmpLen;

    /* 计算该信元剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 解析必选信元Code Word String */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeCodeWordString(pucSrcTmp + ulSum, &ulTmpLen, &pstCodeWord->stCodeWord);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过CodeWordString */
    ulSum = ulSum + ulTmpLen;

    /* 计算该信元剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 跳过剩余未解析码流 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCodeWordString
 Description     : 解析lcs Code Word String信元
 Input           : pucSrc                       :码流
                   pstCodeWord                  :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCodeWordString
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CODE_WORD_STRING_STRU       *pstCodeWord
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_CODE_WORD_STRING,
                                    NAS_LCS_LEN_DECODE_FAIL,
                                    0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TL */
    ulSum = ulSum + ulTmpLen;

    /* 判断TAG是否正确 */
    if (1 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_CODE_WORD_STRING,
                                    NAS_LCS_TAG_ERROR,
                                    stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 判断长度是否合法 */
    if ((NAS_LCS_CODE_WORD_STRING_MAX_LEN < ulValueLen) || (0 == ulValueLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_CODE_WORD_STRING,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen,
                                    ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 保存Code Word */
    pstCodeWord->ucLen = (VOS_UINT8)ulValueLen;

    NAS_LCS_MEM_CPY_S(  pstCodeWord->aucCodeWord,
                        NAS_LCS_CODE_WORD_STRING_MAX_LEN,
                        (pucSrcTmp + ulSum),
                        ulValueLen);

    /* 跳过Code Word */
    ulSum = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeServiceTypeId
 Description     : 解析Service Type Id信元
 Input           : pucSrc                       :码流
                   pucServiceTypeId             :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeServiceTypeId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucServiceTypeId
)
{
    VOS_UINT32                          ulSum                   = 0;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;

    /* 检查LEN */
    if (1 != ulUndecodeLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_SER_TYPE_ID,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    *pucServiceTypeId = pucSrcTmp[ulSum];

    /* 判断ServiceTypeId是否小于127 */
    if (NAS_LCS_MAX_SERVICE_TYPE_ID < *pucServiceTypeId)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_SER_TYPE_ID,
                                    NAS_LCS_VALUE_IVALID,
                                    *pucServiceTypeId,
                                    NAS_LCS_MAX_SERVICE_TYPE_ID);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    ulSum++;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCilentExtId
 Description     : 解析CilentExternalId信元
 Input           : pucSrc                       :码流
                   pstClientExternalId          :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCilentExtId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU     *pstClientExternalId
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;
    VOS_UINT32                          ulLoop          = 0;

    /* 判断是否有可选信元 */
    if (0 == ulUndecodeLen)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    /* 解析可选信元 */
    while ((0 != ulUndecodeLen) && (ulLoop < NAS_LCS_CLIENT_EXT_ID_OP_MAX_NUM))
    {
        ulTmpLen = ulUndecodeLen;
        enRslt   = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* 可选信元TL译码失败跳过剩余码流长度 */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_EXT_CLIENT_ID, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过TAG和LEN */
        ulSum              = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen      = ulUndecodeLen - ulTmpLen;

        /* 获取可选信元Value Len */
        ulTmpLen           = ulValueLen;
        switch (stTagStru.ulNumber)
        {
            /* 解析externalAddress */
            case 0:
                (VOS_VOID)NAS_LCS_DecodeExternalAddr(   pucSrcTmp + ulSum,
                                                        &ulTmpLen,
                                                        pstClientExternalId);
                break;

            /* 解析externsionContainer */
            case 1:
                (VOS_VOID)NAS_LCS_DecodeExtensionContainer( pucSrcTmp + ulSum,
                                                            &ulTmpLen,
                                                            pstClientExternalId);
                break;

            default:
                ulSum              = ulSum + ulUndecodeLen;
                *pulLen            = ulSum;
                NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_EXT_CLIENT_ID,
                                            NAS_LCS_TAG_ERROR,
                                            stTagStru.ulNumber, 0);
                return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过可选信元Value长度, 不用考虑可选信元 */
        ulSum         = ulSum + ulValueLen;

        /*计算该信元剩余码流长度*/
        ulUndecodeLen = ulUndecodeLen - ulValueLen;

        /* 解析次数累加, 循环次数不能大于可选信元个数 */
        ulLoop++;
    }

    /* 跳过该信元剩余未解析码流长度 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeExternalAddr
 Description     : 解析CilentExternal Address信元
 Input           : pucSrc                       :码流
                   pstClientExternalId          :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeExternalAddr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU     *pstClientExternalId
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    /* 判断长度是否在1-20之间 */
    if ((0 == ulUndecodeLen) || (LCS_CLIENT_EXID_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_EXT_ADDR,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen,
                                    0);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_CPY_S(  pstClientExternalId->stExternalAddr.aucAddr,
                                 LCS_CLIENT_EXID_MAX_LEN,
                                 pucSrcTmp,
                                 ulUndecodeLen);

    pstClientExternalId->bitOpExternalAddr = NAS_LCS_OP_TRUE;
    pstClientExternalId->stExternalAddr.ucLen = (VOS_UINT8)ulUndecodeLen;
    *pulLen = ulUndecodeLen;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeExtensionContainer
 Description     : 解析Extension Container信元
 Input           : pucSrc                       :码流
                   pstClientExternalId          :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeExtensionContainer
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU     *pstClientExternalId
)
{
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen  = ulUndecodeLen;

    /* 暂不解析 */
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeDataCodingScheme
 Description     : 解析Data Coding Scheme信元
 Input           : pucSrc                       :码流
                   pucDataCodeScheme            :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeDataCodingScheme
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucDataCodeScheme
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    /* 判断长度是否合法 */
    if ( NAS_LCS_DATA_CODING_SCHEME_LEN != ulUndecodeLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_DATA_CODE_SHM,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen,
                                    NAS_LCS_DATA_CODING_SCHEME_LEN);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 保存DataCodeScheme */
    *pucDataCodeScheme = pucSrcTmp[ulSum++];

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeClientNameDataCodingScheme
 Description     : 解析Clent Name信元中必选信元Data Coding Scheme信元
 Input           : pucSrc                       :码流
                   pucDataCodeScheme            :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeClientNameDataCodingScheme
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_NAME_STRU            *pstClientName
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    ulTmpLen    = ulUndecodeLen;
    enRslt      = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_CLIENT_NAME, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过Tag和Len */
    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulValueLen;

    /* 判断TAG是否正确 */
    if (0 == stTagStru.ulNumber)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeDataCodingScheme((pucSrcTmp + ulSum), &ulTmpLen, &pstClientName->ucDataCodeScheme);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
        }

        /* 计算剩余长度 */
        ulSum         = ulSum + ulTmpLen;
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
    }
    else
    {
        ulSum   = ulSum + ulUndecodeLen;
        *pulLen = ulSum;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CLIENT_NAME,
                                    NAS_LCS_MISS_DATA_CODE_SCH,
                                    stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeClientName
 Description     : 解析Client Name信元
 Input           : pucSrc                       :码流
                   pstClientName                :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeClientName
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_NAME_STRU            *pstClientName
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    /* 解析必选信元DataCodingScheme */
    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeClientNameDataCodingScheme(pucSrcTmp + ulSum, &ulTmpLen, pstClientName);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeClientNameString(pucSrcTmp + ulSum, &ulTmpLen, pstClientName);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 判断是否有可选信元 */
    if (0 < ulUndecodeLen)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* 跳过剩余长度 */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* 跳过TAG和LEN */
        ulSum         = ulSum + ulTmpLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* 解析可选信元Lcs-FormatIndeicator */
        ulTmpLen = ulValueLen;
        if (3 == stTagStru.ulNumber)
        {
            enRslt = NAS_LCS_DecodeFormatIndicator( pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstClientName->enLcsFormat);
            if (NAS_LCS_CAUSE_SUCCESS == enRslt)
            {
                pstClientName->bitOpLcsFormat = NAS_LCS_OP_TRUE;
            }
        }

        /* 跳过可选信元Value长度 */
        ulSum           = ulSum + ulValueLen;

        /* 计算剩余码流长度 */
        ulUndecodeLen   = ulUndecodeLen - ulValueLen;
    }

    /* 跳过该信元剩余码流长度 */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeFormatIndicator
 Description     : 解析Format Indicator信元
 Input           : pucSrc                       :码流
                   penLcsFormat                 :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeFormatIndicator
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_FORMAT_INDICATOR_ENUM_UINT8 *penLcsFormat
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    /* 判断可选信元长度是否合法 */
    if (1 != ulUndecodeLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_FORMAT_IND, NAS_LCS_LEN_INVAILID, ulUndecodeLen, 1);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 保存LcsFormat */
    *penLcsFormat = pucSrcTmp[ulSum++];

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeClientNameString
 Description     : 解析Client Name String信元
 Input           : pucSrc                       :码流
                   pstClientName                :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeClientNameString
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_NAME_STRU            *pstClientName
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CLIENT_NAME,
                                    NAS_LCS_LEN_DECODE_FAIL,
                                    0,
                                    0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 判断TAG是否正确 */
    if (2 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CLIENT_NAME,
                                    NAS_LCS_TAG_ERROR,
                                    stTagStru.ulNumber,
                                    2);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TL */
    ulSum = ulSum + ulTmpLen;

    if ((0 == ulValueLen) || (LCS_CLIENT_NAME_MAX_LEN < ulValueLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CLIENT_NAME,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen,
                                    LCS_CLIENT_EXID_MAX_LEN);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 保存 */
    pstClientName->stNameString.ucLen = (VOS_UINT8)ulValueLen;

    NAS_LCS_MEM_CPY_S(    pstClientName->stNameString.aucNameString,
                          LCS_CLIENT_NAME_MAX_LEN,
                          (pucSrcTmp + ulSum),
                          ulValueLen);

    /* 跳过Value */
    ulSum = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeNotificationType
 Description     : 解析Notication Type
 Input           : pucSrc                       :码流
                   pucNtfType                   :解析后参数
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeNotificationType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucNtfType
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen       = 0;

    ulTmpLen    = ulUndecodeLen;
    enRslt      = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if(NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_NTF_TYPE, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 检查TAG */
    if (0 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_NTF_TYPE, NAS_LCS_TAG_ERROR, stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过Tag和Len */
    ulSum           = ulSum + ulTmpLen;

    /* 保存Notication Type */
    *pucNtfType     = pucSrcTmp[ulSum];

    /* 跳过整个IE */
    *pulLen = ulSum + ulValueLen;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocEstimateType
 Description     : 解析locationEstimateType
 Input           : pucSrc                       :码流
                   pstLocNtfStru                :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocEstimateType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOCATION_TYPE_STRU          *pstLocationType
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    /* 解析必选locationEstimateType */
    ulTmpLen    = ulUndecodeLen;
    enRslt      = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_EST_TYPE, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* 跳过TAG和LEN */
    ulSum         = ulSum + ulTmpLen;

    /* 计算剩余码流长度 */
    ulUndecodeLen = ulValueLen;

    /* 判断TAG和LEN是否有效 */
    if ((0 == stTagStru.ulNumber) && (1 == ulValueLen))
    {
        pstLocationType->enLocType = pucSrcTmp[ulSum++];
        ulUndecodeLen = ulUndecodeLen - 1;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_EST_TYPE, NAS_LCS_LEN_INVAILID, ulValueLen, 1);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocationType
 Description     : 解析Location Type
 Input           : pucSrc                       :码流
                   pstLocNtfStru                :解析后结构
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocationType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOCATION_TYPE_STRU          *pstLocationType
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    ulTmpLen    = ulUndecodeLen;
    enRslt      = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if(NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_TYPE, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    if (1 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_EST_TYPE, NAS_LCS_TAG_ERROR, stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }
    /* 跳过TAG和LEN */
    ulSum         = ulSum + ulTmpLen;

    /* 获取该信元未解析长度, 以IE中LEN为准 */
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* 解析必选locationEstimateType */
    enRslt      = NAS_LCS_DecodeLocEstimateType(pucSrcTmp + ulSum, &ulTmpLen, pstLocationType);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* 跳过locationEstimateType */
    ulSum         = ulSum + ulTmpLen;

    /* 计算剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 判断是否存在可选信元 */
    if (0 < ulUndecodeLen)
    {
        ulTmpLen = ulUndecodeLen;

        /* 解析deferredLocationEventType */
        enRslt      = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if ((NAS_LCS_CAUSE_SUCCESS == enRslt)&& (1 == stTagStru.ulNumber))
        {
            /* 跳过TAG和LEN */
            ulSum = ulSum + ulTmpLen;

            /* 计算剩余码流长度 */
            ulUndecodeLen = ulUndecodeLen - ulTmpLen;

            /* 获取deferredLocationEventType信元长度 */
            ulTmpLen = ulValueLen;
            enRslt = NAS_LCS_DecodeDeferLocEventType(   pucSrcTmp + ulSum,
                                                        &ulTmpLen,
                                                        &pstLocationType->ucDeferLocEventType);
            if (NAS_LCS_CAUSE_SUCCESS == enRslt)
            {
                pstLocationType->bitOpDeferLocEventType = NAS_LCS_OP_TRUE;
            }

            /* 跳过deferredLocationEventType Value */
            ulSum = ulSum + ulValueLen;

            /* 计算剩余码流长度 */
            ulUndecodeLen = ulUndecodeLen - ulValueLen;
        }
    }

    /* 跳过整个IE */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeDeferLocEventType
 Description     : 解析解析枚举
 Input           : pucSrc                       :码流
                   pucDest                      :解析后参数
                   ucTagMode                    :TAG模式
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeDeferLocEventType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucDeferLocEventType
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT8                           ucValue;
    VOS_UINT8                           ucFillBitNum    = 0;
    VOS_UINT8                           ucTmpLen;

    /* 检查长度 */
    if (NAS_LCS_BIT_STRING_MIN_LEN > ulUndecodeLen)
    {
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 该信元为bitString编码格式, V中第一个字节为填充bit长度 */
    /* 获取填充BIT长度 */
    ucFillBitNum = pucSrcTmp[ulSum++];

    /* 获取真实Sting字节数 */
    ucTmpLen     = (VOS_UINT8)ulUndecodeLen - 1;

    /* 获取DeferLocEventType, 当前只用一个字节 */
    if (1 == ucTmpLen)
    {
        /* 当长度为1时, 根据填充Bit数, 获取有效数据 */
        switch(ucFillBitNum)
        {
            case 0:
                ucValue = pucSrcTmp[ulSum];
                break;

            case 1:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_7_BIT;
                break;

            case 2:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_6_BIT;
                break;

            case 3:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_5_BIT;
                break;

            case 4:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_4_BIT;
                break;

            case 5:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_3_BIT;
                break;

            case 6:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_2_BIT;
                break;

            case 7:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_1_BIT;
                break;

            default:
                ucValue = 0;
                break;
        }
    }
    else
    {
        /* 当前只用一个字节, 所以该字节都为有效数据 */
        ucValue = pucSrcTmp[ulSum];
    }

    /* 跳过整个信元 */
    *pulLen = ulUndecodeLen;
    *pucDeferLocEventType = ucValue;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeTL
 Description     : 解析TAG和Len
 Input           : pucSrc                       :码流
 Output          : pulLen                       :已解析长度
                   pulIeLen                     :IE LEN
                   pstTagStru                   :解析后TAG结构
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeTL
(
    VOS_UINT8                           *pucSrc,
    NAS_LCS_TAG_STRU                    *pstTagStru,
    VOS_UINT32                          *pulValueLen,
    VOS_UINT32                          *pulLen
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulUndecodeLen = *pulLen;
    VOS_UINT8                          *pucSrTmp      = pucSrc;
    VOS_UINT32                          ulSum         = 0;
    VOS_UINT32                          ulTmpLen      = 0;
    VOS_UINT32                          ulValueLen    = 0;

    *pulValueLen    = 0;
    *pulLen         = 0;

    /* 初始化 */
    NAS_LCS_MEM_SET_S(  pstTagStru,
                        sizeof(NAS_LCS_TAG_STRU),
                        0,
                        sizeof(NAS_LCS_TAG_STRU));

    if (0 == ulUndecodeLen)
    {
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 获取剩余码流长度 */
    ulTmpLen        = ulUndecodeLen;

    /* 对标签进行解码，解码TLV中的T和L,确定结束位置 */
    enRslt = NAS_LCS_DecodeTag(pucSrTmp + ulSum, pstTagStru, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_TAG, NAS_LCS_TAG_DECODE_FAIL, 0, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_TAG_DECODE_FAIL TAG decode fail ");
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 跳过TAG */
    ulSum           = ulSum + ulTmpLen;

    /* 获取剩余码流长度 */
    ulUndecodeLen   = ulUndecodeLen - ulTmpLen;
    ulTmpLen        = ulUndecodeLen;

    /* 解析LEN */
    enRslt          = NAS_LCS_DecodeLength(pucSrTmp + ulSum, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LENGTH, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_TAG_DECODE_FAIL LENGTH decode fail ");
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* 跳过L */
    ulSum         = ulSum + ulTmpLen;

    /* 获取剩余码流长度 */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* 检查剩余码流长度是否小于Value长度 */
    if (ulUndecodeLen < ulValueLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_LENGTH,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeLen,
                                    ulValueLen);
        NAS_LCS_INFO_LOG(" NAS_LCS_TAG_DECODE_FAIL unDecode Len Invalid ");
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    *pulLen       = ulSum;
    *pulValueLen  = ulValueLen;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeTag
 Description     : 解析解析枚举
 Input           : pucSrc                       :码流
                   pucDest                      :解析后参数
                   ucTagMode                    :TAG模式
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeTag
(
    VOS_UINT8                           *pucSrc,
    NAS_LCS_TAG_STRU                    *pstTagStru,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT8                           ucCounter       = 0;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen = 0;

    /*获取标签类型和结构*/
    pstTagStru->ucClass = pucSrcTmp[ulSum] >> NAS_LCS_MOVEMENT_6_BITS;
    pstTagStru->ucStructed = (VOS_UINT8)(pucSrcTmp[ulSum] & 0x20);

    /*获取标签值*/
    ucTmp = (VOS_UINT8)(pucSrcTmp[ulSum++] & NAS_LCS_MSG_LOW_5_BIT);

    /*单字节格式*/
    if (ucTmp != NAS_LCS_MULTI_BYTE_TAG_FLAG)
    {
        pstTagStru->ulNumber = ucTmp;
        *pulLen = ulSum;
        return NAS_LCS_CAUSE_SUCCESS;
    }

    /* 多字节格式时,获取标签值,最高位为1时,表示有后续字节 */
    /* 把后续字节的第一个字节到最后一个字节的第7位到第一位连起来就是标签的值 */
    pstTagStru->ulNumber = 0;
    do
    {
        /* 判断码流是否解析完了 */
        if (ulUndecodeLen <= ulSum)
        {
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
        }

        ucCounter++;

        /*最多的循环次数和VOS_UINT32型的长度相关*/
        if (ucCounter > sizeof(VOS_UINT32))
        {
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
        }

        ucTmp = pucSrcTmp[ulSum++];
        pstTagStru->ulNumber = (VOS_INT32)(((VOS_UINT32)pstTagStru->ulNumber << NAS_LCS_MOVEMENT_7_BITS) + (ucTmp & NAS_LCS_MSG_LOW_7_BIT));
    }while(ucTmp >= NAS_LCS_MULTI_BYTE_TAG_CON_OCT_MIN_VALUE);

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLength
 Description     : 解析LEN
 Input           : pucSrc                       :码流
                   pucDest                      :解析后参数
                   ucTagMode                    :TAG模式
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32  NAS_LCS_DecodeLength
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulValueLen,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT8                           ucTmpLen      = 0;
    VOS_UINT8                          *pucTmpMsg     = pucSrc;
    VOS_UINT32                          ulSum         = 0;
    VOS_UINT32                          ulUndecodeLen = *pulLen;

    *pulValueLen = 0;

    if ((0 == ulUndecodeLen)||(NAS_LCS_MAX_COMPONENT_LENGTH < ulUndecodeLen))
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    /* 跳过长度 */
    ucTmpLen = pucTmpMsg[ulSum++];

    /* 如果是短格式模式，明确长度，计算长度 */
    if (ucTmpLen < NAS_LCS_INDEF_LENGTH_FLAG)
    {
        *pulValueLen = ucTmpLen;
        *pulLen      = ulSum;
        return NAS_LCS_CAUSE_SUCCESS;
    }

    ulUndecodeLen = ulUndecodeLen - ulSum;

    /* 非短格式 */
    switch (ucTmpLen)
    {
        case NAS_LCS_INDEF_LENGTH_FLAG:

            /* 不定长度的计算处理 */
            /* 由于在LCS的para的总长都是可知的，所以不应该出现直接传送内容而并不清楚整个数据的长度 */
            ucTmpLen = (VOS_UINT8)ulUndecodeLen;
            if (NAS_LCS_CAUSE_SUCCESS != NAS_LCS_DecodeIndefLen(pucTmpMsg + ulSum, &ucTmpLen))
            {
                return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
            }

            *pulValueLen = ucTmpLen;
            break;

        case (NAS_LCS_INDEF_LENGTH_FLAG + 1):

            /* 长格式，多字节 */
            *pulValueLen = pucTmpMsg[ulSum++];
            break;

        default:
            /*
            大于129的情况，由于Facility Ie长度不会超过一个字节，在使用多字节表示时，不会超过一个字节
            若更长，则出错处理
            */
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }
    *pulLen     = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;

}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeIndefLen
 Description     : 解析不定LEN
 Input           : pucSrc                       :码流
                   pucDest                      :解析后参数
                   ucTagMode                    :TAG模式
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeIndefLen(VOS_UINT8 *pucSrc, VOS_UINT8 *pucLen)
{
    VOS_UINT8                           aucEndFlag[]    = {0,0};
    VOS_UINT8                           ucEndFlagLength;
    VOS_UINT32                          ulLoop = 0;
    VOS_UINT8                           ucLength        = 0;
    VOS_UINT8                           ucLengthBytes;
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT8                           ucUndoceLen     = *pucLen;

    /* 获取结束符长度 */
    ucEndFlagLength = sizeof(aucEndFlag);

    /* 若剩余码流长度小于结束符长度, 返回失败 */
    if (ucEndFlagLength > ucUndoceLen)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    ulLoop          = 0;

    /* 循环解析长度, 防止出现IE中还存在不定长的IE */
    while (ulLoop < ucUndoceLen)
    {
        if (0 == PS_MEM_CMP(pucSrcTmp + ulLoop, aucEndFlag, ucEndFlagLength))
        {
            /* 实际码流长度, 包含结束符 */
            *pucLen      = (VOS_UINT8)ulLoop + ucEndFlagLength;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* TAG */
        ulLoop++;

        /* LENGTH */
        ucLength    = pucSrcTmp[ulLoop];
        ulLoop++;

        /* 不定长方式:Length所在八位组固定编码为0x80，Value编码结束后以两个0x00结尾。*/
        if (NAS_LCS_INDEF_LENGTH_FLAG == ucLength)
        {
            ucLength = ucUndoceLen - (VOS_UINT8)ulLoop;
            ulRet = NAS_LCS_DecodeIndefLen(pucSrcTmp + ulLoop, &ucLength);
            if (NAS_LCS_CAUSE_SUCCESS != ulRet)
            {
                return ulRet;
            }
            ulLoop  += ucLength;
        }
        else
        {
            if (NAS_LCS_INDEF_LENGTH_FLAG == (ucLength & NAS_LCS_INDEF_LENGTH_FLAG))
            {
                /* 定长方式长格式: 第一个八位组的低七位指明整个L所占用的八位组个数，后续八位组表示V的长度 */
                /* SS仅支持长度为1字节的长度 */
                ucLengthBytes = ucLength & NAS_LCS_MSG_LOW_7_BIT;
                if ((ucLengthBytes > sizeof(VOS_UINT8)) || (ulLoop >= ucUndoceLen))
                {
                    return NAS_LCS_CAUSE_FAIL;
                }

                /* LENGTH */
                ucLength    = pucSrcTmp[ulLoop];
                ulLoop++;

                ulLoop  += ucLength;
            }
            else
            {
                /* 定长方式短格式 */
                ulLoop  += ucLength;
            }
        }
    }
    return NAS_LCS_CAUSE_FAIL;
}

/*****************************************************************************
 Function Name   : NAS_LCS_CheckOperationCode
 Description     : 解析不定LEN
 Input           : pucSrc                       :码流
                   pucDest                      :解析后参数
                   ucTagMode                    :TAG模式
 Output          : pulLen                       :已解析长度
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :解析结果

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_CheckOperationCode(NAS_LCS_OPERATION_TYPE_UINT32 enOperationCode)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    /* 检查OperationCode */
    switch(enOperationCode)
    {
        case NAS_LCS_OPERATION_MO_LR:
        case NAS_LCS_OPERATION_LOC_NOTIFICATION:
            enRslt = NAS_LCS_CAUSE_SUCCESS;
            break;

        default:
            enRslt = NAS_LCS_CAUSE_FAIL;
            break;
    }
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_CheckProblemTagVaild
 Description     : 判断Problem Code是否合法
 Input           : enProblemTag :Problem Tag
 Output          : None
 Return          : 0:合法, 1:非法

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_CheckProblemTagVaild(NAS_LCS_PROBLEM_TAG_ENUM_UINT8 enProblemTag)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    /* 检查ProblemTag */
    switch (enProblemTag)
    {
        case NAS_LCS_PROBLEM_GENERAL_TAG:
        case NAS_LCS_PROBLEM_INVOKE_TAG:
        case NAS_LCS_PROBLEM_RTN_RSLT_TAG:
        case NAS_LCS_PROBLEM_RTN_ERR_TAG:

            enRslt = NAS_LCS_CAUSE_SUCCESS;
            break;

         default:
            enRslt = NAS_LCS_CAUSE_FAIL;
            break;
    }
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_GetRegisterOperaCode
 Description     : 获取Register空口的消息Operation Code
 Input           : pucFacilityIe                  : FacilityIe码流
                   ulLen                          : 码流长度
 Output          : None
 Return          : NAS_LCS_OPERATION_TYPE_UINT32  : Operation Code

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_OPERATION_TYPE_UINT32 NAS_LCS_GetRegisterOperaCode
(
    VOS_UINT8                          *pucFacilityIe,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulUndecodeLen = ulLen;
    NAS_LCS_OPERATION_TYPE_UINT32       enOperaCode   = NAS_LCS_OPERATION_NULL;
    VOS_UINT8                          *pucMsgTem     = pucFacilityIe;
    VOS_UINT32                          ulSum         = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulValueLen    = 0;
    VOS_UINT32                          ulTmpLen      = 0;

    /* 判断剩余码流长度是否满足Register空口Facility Ie最小长度 */
    if (NAS_LCS_REG_IE_FACILITY_MIN_LEN > ulUndecodeLen)
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* 判断IEI是否正确 */
    if (NAS_LCS_MSG_FACILITY_IEI != pucMsgTem[ulSum])
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* 跳过Facility IEI和Len */
    ulSum         = ulSum + 2;
    ulUndecodeLen = ulUndecodeLen - 2;

    /* 判断Component type是否为Invoke */
    if (NAS_LCS_COMPONENT_INVOKE_TAG != pucMsgTem[ulSum])
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* 解析Component type Tag和Length */
    ulTmpLen      = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucMsgTem + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* 跳过Component type Tag和Length */
    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulValueLen;

    /* 跳过Invoke Id */
    if ((NAS_LCS_INVOKE_ID_TAG == pucMsgTem[ulSum])&&(3 <= ulUndecodeLen))
    {
        ulSum         = ulSum + 3;
        ulUndecodeLen = ulUndecodeLen - 3;
    }
    else
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* 判断是否存在Linked Id */
    if (NAS_LCS_LINKED_ID_TAG == pucMsgTem[ulSum])
    {
        if (3 <= ulUndecodeLen)
        {
            ulSum         = ulSum + 3;
            ulUndecodeLen = ulUndecodeLen - 3;
        }
        else
        {
            return NAS_LCS_OPERATION_NULL;
        }
    }

    /* 获取Operation Code */
    if ((NAS_LCS_OPERATION_CODE_TAG == pucMsgTem[ulSum])&&(3 <= ulUndecodeLen))
    {
        ulSum = ulSum + 2;
        enOperaCode = pucMsgTem[ulSum];
    }
    else
    {
        return NAS_LCS_OPERATION_NULL;
    }
    return enOperaCode;
}

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


