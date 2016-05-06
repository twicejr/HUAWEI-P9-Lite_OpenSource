/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallFacilityDecode.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年9月20日
  最近修改   : 2007年9月20日
  功能描述   : 实现CS呼叫相关的API接口函数
  函数列表   :
  修改历史   :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
******************************************************************************/
/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "Taf_Ssa_DecodeDef.h"
#include "MnCallFacilityDecode.h"
#include "MnComm.h"
#include "NasCcIe.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/


/*****************************************************************************
  4 宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_FACILITY_DECODE_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*lint -e961*/

#define MN_CALL_DecodeEctCallState(pucDest, pucSrc, TagMode)\
            SSA_DecodeEnum(pucDest, pucSrc, TagMode)

#define MN_CALL_DecodeMultiCallInd(pucDest, pucSrc, TagMode)\
            SSA_DecodeEnum(pucDest, pucSrc, TagMode)
#define MN_CALL_DecodeCallOnHoldInd(pucDest, pucSrc, TagMode)\
            SSA_DecodeEnum(pucDest, pucSrc, TagMode)


#define MN_CALL_DecodeCugIndex(value, content, tagmode)\
            SSA_DecodeInt(value, 32767, content, tagmode)

#define MN_CALL_DecodePartyNumber(NumType, aucNumer, ppucSrc, TagMode) \
            SSA_DecodeForwardedToNumber(NumType, aucNumer, ppucSrc, TagMode)

#define MN_CALL_DecodePartyNumberSubAddr(pucSubAddrType, pucSubAddr, ppucSrc, ucTagMode)\
            SSA_DecodeForwardedToSubaddress(pucSubAddrType, pucSubAddr, ppucSrc, ucTagMode)

#define MN_CALL_DecodePresentationAllowedAddr(pDest, ppucSrc, ucTagMode, pucEndLocation)\
            MN_CALL_DecodePresentationAddress(pDest, ppucSrc, ucTagMode, pucEndLocation)

#define MN_CALL_DecodePresentationRestrictedAddr(pDest, ppucSrc, ucTagMode, pucEndLocation)\
            MN_CALL_DecodePresentationAddress(pDest, ppucSrc, ucTagMode, pucEndLocation)

#define MN_CALL_DecodeNamePresentationRestricted(pDest, ppucSrc, ucTagMode)\
            MN_CALL_DecodeNamePresentation(pDest, ppucSrc, ucTagMode)

#define MN_CALL_DecodeNamePresentationAllowed(pDest, ppucSrc, ucTagMode)\
            MN_CALL_DecodeNamePresentation(pDest, ppucSrc, ucTagMode)


/*lint +e961*/

extern VOS_UINT32 SSA_DecodeSsNull(VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode);
/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数实现
*****************************************************************************/
/*****************************************************************************
 Prototype      : MN_CALL_DecodePresentationAddress
 Description    : 将参数项presentationAllowedAddress和presentationRestrictedAddress解码,类型定义参见24.080,附录
 Input          : **ppucSrc--解码前的字串, ucTagMode -- 标签模式,pucEndLocation--结束位置
 Output         : *pDest--输出的字串
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
  2.日    期   : 2012年10月22日
    作    者   : l65478
    修改内容   : DTS2012101901424,OPTIONAL项不存在时不能认为解码失败
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_DecodePresentationAddress(
    MN_CALL_PRESENTATION_ADDR_STRU      *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt = VOS_OK;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Length Value Error");
            return ulRslt;
        }
    }


    /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Tag Value Wrong");
        return ulRslt;
    }

    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Length Value Error");
        return ulRslt;
    }

    /*判断是否有PartyNumber参数项的Tag值:0x84*/
    if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
         /*解码PartyNumber参数项，解码失败则返回*/
         ulRslt = MN_CALL_DecodePartyNumber(&(pstDest->NumType), pstDest->aucPartyNumber, ppucSrc, IMPLICIT_MODE);
         if (VOS_OK != ulRslt)
         {
             MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: PartyNumber Decode Failure");
             return ulRslt;
         }
     }
     else
     {
         MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: PartyNumber Tag Value Err");
         return VOS_ERR;
     }

    /* 可选子地址不存在,返回成功 */
     if (pucEndLocation <= *ppucSrc)
     {
         return ulRslt;
     }

     /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
     ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
     if (VOS_OK != ulRslt)
     {
         MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Tag Value Wrong");
         return ulRslt;
     }

     ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
     if (VOS_OK != ulRslt)
     {
         MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Length Value Error");
         return ulRslt;
     }
     /*判断是否有partyNumberSubaddress参数项的Tag值:0x84*/
     if ((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
     {
         /*解码partyNumberSubaddress参数项，解码失败则返回*/
         ulRslt = MN_CALL_DecodePartyNumberSubAddr(&(pstDest->NumType), pstDest->aucPartyNumber, ppucSrc, IMPLICIT_MODE);
         if (VOS_OK != ulRslt)
         {
             MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: partyNumberSubaddress Decode Failure");
             return ulRslt;
         }
     }
     else
     {
         MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: partyNumberSubaddress Tag Value Err");
         return VOS_ERR;
     }

     return ulRslt;

}

/*****************************************************************************
 Prototype      : MN_CALL_DecodeNamePresentation
 Description    : 将参数项namePresentationAllowed和namePresentationRestricted解码,类型定义参见24.080,附录
 Input          : **ppucSrc--解码前的字串, ucTagMode -- 标签模式
 Output         : *pDest--输出的字串
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_DecodeNamePresentation(
    MN_CALL_NAME_PRESENTATION_STRU      *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT32                          ulRslt = VOS_OK;
    VOS_UINT8                           ucStrLen;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*解码参数项dataCodingScheme*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: Length Value Error");
        return ulRslt;
    }


    if((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        gulCurStrMaxLen = 1;
        ulRslt = SSA_DecodeString(&(pstDest->DataCodingScheme), &ucStrLen, ppucSrc, IMPLICIT_MODE);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: dataCodingScheme Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: dataCodingScheme Tag Value Err");
        return VOS_ERR;
    }


    /*解码参数项lengthInCharacters*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: Length Value Error");
        return ulRslt;
    }
    if((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        gulCurStrMaxLen = 1;
        ulRslt = SSA_DecodeInt(&(pstDest->LengthInCharacters), 32767, ppucSrc, IMPLICIT_MODE);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: lengthInCharacters Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        MN_WARN_LOG( "MN_CALL_DecodePresentationAddress:WARNING: lengthInCharacters Tag Value Err");
        return VOS_ERR;
    }

    /*解码参数项nameString*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: Length Value Error");
        return ulRslt;
    }
    if((2 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        gulCurStrMaxLen = 161;
        ulRslt = SSA_DecodeString(pstDest->NameString, &ucStrLen, ppucSrc, IMPLICIT_MODE);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: SSA_DecodeString Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        MN_WARN_LOG( "MN_CALL_DecodePresentationAddress:WARNING: lengthInCharacters Tag Value Err");
        return VOS_ERR;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : MN_CALL_DecodeEctIndicator
 Description    : 将参数项ss-Notification解码,类型定义参见24.080,附录
 Input          : **ppucSrc--解码前的字串, ucTagMode -- 标签模式
 Output         : *pucDest--输出的字串
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_DecodeSsNotification(
    VOS_UINT8                           *pucDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           ucStrLen;

    /* 解码，返回解码函数的操作结果 */
    gulCurStrMaxLen = 1;
    return  SSA_DecodeString(pucDest, &ucStrLen, ppucSrc, ucTagMode);

}

/*****************************************************************************
 Prototype      : MN_CALL_DecodeEctIndicator
 Description    : 将参数项ect-Indicator解码,类型定义参见24.080,附录
 Input          : **ppucSrc--解码前的字串, ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据类型
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
  2.Date        : 2007-04-04
    Author      : h44270
    Modification: modified for A32D10114
  3.日    期   : 2012年10月22日
    作    者   : l65478
    修改内容   : DTS2012101901424,OPTIONAL项不存在时不能认为解码失败
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_DecodeEctIndicator(
    MN_CALL_ECT_INDICATOR_STRU          *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT32                          ulRslt = VOS_OK;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*对ect-CallState进行解码*/
    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value Error");
        return ulRslt;
    }

    /*判断标签值的正确性*/
    if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        /*解码ect-CallState参数项,如果解码失败,则返回*/
        ulRslt = MN_CALL_DecodeEctCallState(&(pstDest->EctCallState), ppucSrc, IMPLICIT_MODE);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: ect-CallState decode Failure");
            return ulRslt;
        }
    }
    else
    {
        /*标签值不是ect-CallState的标签值,失败返回*/
        MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: ect-CallState TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*判断是否有参数项rdn,有的话解码,没有跳过*/
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value Error");
            return ulRslt;
        }

        /*判断是否有rdn参数项的Tag值:0x81,choice类型*/
        if ((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*解码rdn参数项,解码失败则返回*/
            /*对标签进行解码，解码TLV中的T和L*/
            ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Wrong");
                return ulRslt;
            }
            ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value Error");
                return ulRslt;
            }

            switch(gSsTagValue.iNumber)
            {
            /*参数项presentationAllowedAddress*/
            case 0x00:
                ulRslt = MN_CALL_DecodePresentationAllowedAddr(&(pstDest->PresentationAllowedAddr),
                                                            ppucSrc,
                                                            IMPLICIT_MODE,
                                                            pucEndLocation);
                if (VOS_OK != ulRslt)
                {
                    MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: presentationAllowedAddress decode Failure");
                    return ulRslt;
                }
                pstDest->OP_PresentationAllowedAddr= 1;
                break;
            /*参数项presentationRestricted*/
            case 0x01:
                ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
                if (VOS_OK != ulRslt)
                {
                    MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: presentationRestricted decode Failure");
                    return ulRslt;
                }
                pstDest->OP_PresentationRestricted= 1;
                break;
            /*参数项numberNotAvailableDueToInterworking*/
            case 0x02:
                ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
                if (VOS_OK != ulRslt)
                {
                    MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: numberNotAvailableDueToInterworking decode Failure");
                    return ulRslt;
                }
                pstDest->OP_NumNotAvailableDueToInterworking= 1;
                break;
            /*参数项presentationRestrictedAddress*/
            case 0x03:
                ulRslt = MN_CALL_DecodePresentationRestrictedAddr(&(pstDest->PresentationRestrictedAddr),
                                                     ppucSrc,
                                                     IMPLICIT_MODE,
                                                     pucEndLocation);
                if (VOS_OK != ulRslt)
                {
                    MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: presentationRestrictedAddress decode Failure");
                    return ulRslt;
                }
                pstDest->OP_PresentationRestrictedAddr= 1;
                break;
            default:
                MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Error");
                break;
            }

        }
        else
        {
            return ulRslt;
        }
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value not equal with actual length");
        return VOS_ERR;
    }

    return ulRslt;
}


/*****************************************************************************
 Prototype      : MN_CALL_DecodeNameIndicator
 Description    : 将参数项nameIndicator解码,类型定义参见24.080,附录
 Input          : **ppucSrc--解码前的字串,ucTagMode -- 标签模式
 Output         : *pDest--解码后的数据类型
 Return Value   : 操作结果
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
  2.Date        : 2007-04-04
    Author      : h44270
    Modification: modified for A32D10114
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_DecodeNameIndicator(
    MN_CALL_NAME_INDICATOR_STRU         *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = VOS_OK;

    /*如果TAG_MODE为EXPLICIT模式*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*对标签进行解码，解码TLV中的T和L,确定结束位置*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*对callingName进行解码*/
    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Length Value Error");
        return ulRslt;
    }

    /*判断标签值的正确性*/
    if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        /*解码callingName参数项,解码失败则返回*/
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "SSA_DecodeCallBarringFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        switch(gSsTagValue.iNumber)
        {
        /*参数项namePresentationAllowed*/
        case 0x00:
            ulRslt = MN_CALL_DecodeNamePresentationAllowed(&(pstDest->NamePresentationAllowed),
                                                 ppucSrc,
                                                 IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: namePresentationAllowed decode failure");
                return ulRslt;
            }
            pstDest->OP_NamePresentationAllowed= 1;
            break;
        /*参数项presentationRestricted*/
        case 0x01:
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: presentationRestricted decode failure");
                return ulRslt;
            }
            pstDest->OP_RresentationRestricted= 1;
            break;
        /*参数项nameUnavailable*/
        case 0x02:
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: nameUnavailable decode failure");
                return ulRslt;
            }
            pstDest->OP_NameUnAvailable= 1;
            break;
        /*参数项namePresentationRestricted*/
        case 0x03:
            ulRslt = MN_CALL_DecodeNamePresentationRestricted(&(pstDest->NamePresentationRestricted),
                                                 ppucSrc,
                                                 IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: namePresentationRestricted decode failure");
                return ulRslt;
            }
            pstDest->OP_NamePresentationRestricted= 1;
            break;
        default:
            MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Tag Value Error");
            break;
        }

    }
    else
    {
        return ulRslt;
    }

    /*判断当前指针的位置和是否和标签长度一致*/
    if (pucEndLocation != *ppucSrc)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Length Value not equal with actual length");
        return VOS_ERR;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsSsCode
 功能描述  : 对IE项的ss-Code解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsSsCode(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x01 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码ss-Code参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeSsCode(&(pstDest->SsCode), ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsSsCode:WARNING: ss-Code decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsCode = 1;
        }
        else
        {
            /*不存在ss-Code项*/
            *ppucSrc           = pucCurLocation;
            pstDest->OP_SsCode = 0;
        }
    }
    else
    {
        pstDest->OP_SsCode = 0;
        ulRslt             = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsSsStatus
 功能描述  : 对IE项的ss-Status解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsSsStatus(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt = SSA_SUCCESS;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x04 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码ss-Status参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeSsStatus(&(pstDest->SsStatus),
                                        ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsSsStatus:WARNING: ss-Status decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsStatus = 1;
        }
        else
        {
            /*不存在ss-Status项*/
            pstDest->OP_SsStatus = 0;
            *ppucSrc             = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_SsStatus = 0;
        ulRslt               = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsSsNotification
 功能描述  : 对IE项的ss-Notification解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsSsNotification(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x05 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码ss-Notification参数项,如果解码失败,则返回*/
            ulRslt = MN_CALL_DecodeSsNotification(&(pstDest->SsNotification),
                                                  ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsSsNotification:WARNING: ss-Notification Failure");
                return ulRslt;
            }
            pstDest->OP_SsNotification = 1;
        }
        else
        {
            /*不存在ss-Notification项*/
            pstDest->OP_SsNotification = 0;
            *ppucSrc                   = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_SsNotification = 0;
        ulRslt                     = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsCallWaitingInd
 功能描述  : 对IE项的callIsWaiting-Indicator解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsCallWaitingInd(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x0e == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc <= pucEndLocation))
        {
            /*解码callIsWaiting-Indicator参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsCallWaitingInd:WARNING: callIsWaiting-Indicator decode Failure");
                return ulRslt;
            }
            pstDest->OP_CallWaitingInd = 1;
        }
        else
        {
            /*不存在callOnHold-Indicator项*/
            pstDest->OP_CallWaitingInd = 0;
            *ppucSrc                   = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_CallWaitingInd = 0;
        ulRslt                     = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsCallOnHoldInd
 功能描述  : 对IE项的callOnHold-Indicator解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsCallOnHoldInd(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x0f == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码callOnHold-Indicator参数项,如果解码失败,则返回*/
            ulRslt = MN_CALL_DecodeCallOnHoldInd(&(pstDest->CallOnHoldIndicator),
                                                 ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsCallOnHoldInd:WARNING: callOnHold-Indicator decode Failure");
                return ulRslt;
            }
            pstDest->OP_CallOnHoldInd = 1;
        }
        else
        {
            /*不存在callOnHold-Indicator项*/
            pstDest->OP_CallOnHoldInd = 0;
            *ppucSrc                  = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_CallOnHoldInd = 0;
        ulRslt                    = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsMptyIndicator
 功能描述  : 对IE项的mpty-Indicator解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsMptyIndicator(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x10 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc <= pucEndLocation))
        {
            /*解码mpty-Indicator参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsMptyIndicator:WARNING: mpty-Indicator decode Failure");
                return ulRslt;
            }
            pstDest->OP_MptyIndicator = 1;
        }
        else
        {
            /*不存在mpty-Indicator项*/
            pstDest->OP_MptyIndicator = 0;
            *ppucSrc                  = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_MptyIndicator = 0;
        ulRslt                    = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsCugIndex
 功能描述  : 对IE项的cug-Index解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsCugIndex(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32       ulRslt = SSA_SUCCESS;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x11 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码cug-Index参数项,如果解码失败,则返回*/
            ulRslt = MN_CALL_DecodeCugIndex(&(pstDest->CugIndex),
                                            ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsCugIndex:WARNING: cug-Index Failure");
                return ulRslt;
            }
            pstDest->OP_CugIndex = 1;
        }
        else
        {
            /*不存在cug-Index项*/
            pstDest->OP_CugIndex = 0;
            *ppucSrc             = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_CugIndex = 0;
        ulRslt               = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsClirSuppressionRej
 功能描述  : 对IE项的clirSuppressionRejected解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsClirSuppressionRej(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x12 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc <= pucEndLocation))
        {
            /*解码clirSuppressionRejected参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsClirSuppressionRej:WARNING: clirSuppressionRejected decode Failure");
                return ulRslt;
            }
            pstDest->OP_ClirSuppressionRej = 1;
        }
        else
        {
            /*不存在clirSuppressionRejected项*/
            pstDest->OP_ClirSuppressionRej = 0;
            *ppucSrc                       = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_ClirSuppressionRej = 0;
        ulRslt                         = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsEctIndicator
 功能描述  : 对IE项的ect-Indicator解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsEctIndicator(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x13 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码ect-Indicator参数项,如果解码失败,则返回*/
            ulRslt = MN_CALL_DecodeEctIndicator(&(pstDest->EctIndicator),
                                                ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsEctIndicator:WARNING: ect-Indicator Failure");
                return ulRslt;
            }
            pstDest->OP_EctIndicator = 1;
        }
        else
        {
            /*不存在ect-Indicator项*/
            pstDest->OP_EctIndicator = 0;
            *ppucSrc                 = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_EctIndicator = 0;
        ulRslt                   = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsEctIndicator
 功能描述  : 对IE项的ect-Indicator解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsNameIndicator(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x14 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码nameIndicator参数项,如果解码失败,则返回*/
            ulRslt = MN_CALL_DecodeNameIndicator(&(pstDest->NameIndicator),
                                                 ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsNameIndicator:WARNING: nameIndicator Failure");
                return ulRslt;
            }
            pstDest->OP_NameIndicator = 1;
        }
        else
        {
            /*不存在nameIndicator项*/
            pstDest->OP_NameIndicator = 0;
            *ppucSrc                  = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_NameIndicator = 0;
        ulRslt                    = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsCcbsFeature
 功能描述  : 对IE项的ccbs-Feature解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsCcbsFeature(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x15 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码ccbs-Feature参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeCcbsFeature(&(pstDest->CcbsFeature),
                                           ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsCcbsFeature:WARNING: ccbs-Feature decode Failure");
                return ulRslt;
            }
            pstDest->OP_CcbsFeature = 1;
        }
        else
        {
            /*不存在ccbs-Feature项*/
            pstDest->OP_CcbsFeature = 0;
            *ppucSrc                = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_CcbsFeature = 0;
        ulRslt                  = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsAlertingPattern
 功能描述  : 对IE项的alertingPattern解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsAlertingPattern(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x16 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码alertingPattern参数项,如果解码失败,则返回*/
            ulRslt = SSA_DecodeAlertingPattern(&(pstDest->AlertingPattern),
                                               ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsAlertingPattern:WARNING: alertingPattern decode Failure");
                return ulRslt;
            }
            pstDest->OP_AlertingPattern = 1;
        }
        else
        {
            /*不存在alertingPattern项*/
            pstDest->OP_AlertingPattern = 0;
            *ppucSrc                    = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_AlertingPattern = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySsMultiCallInd
 功能描述  : 对IE项的multicall-Indicator解码
 输入参数  : VOS_UINT8                           **ppucSrc        -解码前的字串
             VOS_UINT8                           *pucCurLocation  -解码的当前位置
             VOS_UINT8                           *pucEndLocation  -字串的结束位置
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest         -存放解码后参数结构体
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 MN_CALL_DecodeNotifySsMultiCallInd(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32       ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*对标签进行解码，解码TLV中的T和L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*判断标签类型和标签值，并判断结束位置*/
        if ((0x17 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*解码multicall-Indicator参数项,如果解码失败,则返回*/
            ulRslt = MN_CALL_DecodeMultiCallInd(&(pstDest->MulticallIndicator),
                                                ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsMultiCallInd:WARNING: multicall-Indicator decode Failure");
                return ulRslt;
            }
            pstDest->OP_MulticallInd = 1;
        }
        else
        {
            /*最后一个参数，标签值不可能为其他参数，如果不符，则认为出错*/
            MN_WARN_LOG( "MN_CALL_DecodeNotifySsMultiCallInd:WARNING: multicall-Indicator Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;

        }
    }
    else
    {
        pstDest->OP_MulticallInd = 0;
        ulRslt                   = SSA_SUCCESS;
    }

    return ulRslt;
}
/*****************************************************************************
 函 数 名  : MN_CALL_DecodeNotifySs
 功能描述  : 将参数项notifySS解码,类型定义参见24.080,附录
 输入参数  : VOS_UINT8                           **ppucSrc   -待解码的字串
 输出参数  : MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest    -存放解码后的参数
 返 回 值  : LOCAL VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年1月21日
    作    者   :
    修改内容   : 新生成函数
  2.日    期   : 2010年7月15日
    作    者   : 王毛/00166186
    修改内容   : 降圈复杂度

*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_DecodeNotifySs(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT8                           *pucCurLocation;

    *((VOS_UINT32 *)pstDest) = 0;

    /*解码TLV中的T和L,确定结束位置*/
    ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*字串结束点的地址*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数SsCode*/
    ulRslt = MN_CALL_DecodeNotifySsSsCode(pstDest, ppucSrc,
                                          pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数ss-Status*/
    ulRslt = MN_CALL_DecodeNotifySsSsStatus(pstDest, ppucSrc,
                                            pucCurLocation,pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数ss-Notification*/
    ulRslt = MN_CALL_DecodeNotifySsSsNotification(pstDest, ppucSrc,
                                                  pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数callIsWaiting-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsCallWaitingInd(pstDest, ppucSrc,
                                                  pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数callOnHold-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsCallOnHoldInd(pstDest, ppucSrc,
                                                 pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数mpty-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsMptyIndicator(pstDest, ppucSrc,
                                                 pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数cug-Index*/
    ulRslt = MN_CALL_DecodeNotifySsCugIndex(pstDest, ppucSrc,
                                            pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数clirSuppressionRejected*/
    ulRslt = MN_CALL_DecodeNotifySsClirSuppressionRej(pstDest, ppucSrc,
                                                      pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数ect-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsEctIndicator(pstDest, ppucSrc,
                                                pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数nameIndicator*/
    ulRslt = MN_CALL_DecodeNotifySsNameIndicator(pstDest, ppucSrc,
                                                 pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数ccbs-Feature*/
    ulRslt = MN_CALL_DecodeNotifySsCcbsFeature(pstDest, ppucSrc,
                                               pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数alertingPattern*/
    ulRslt = MN_CALL_DecodeNotifySsAlertingPattern(pstDest,ppucSrc,
                                                   pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*标记解码指针当前位置*/
    pucCurLocation = *ppucSrc;

    /*解码参数multicall-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsMultiCallInd(pstDest, ppucSrc,
                                                pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : MN_CALL_SsInvokeArgDecode()
 Description    : 操作结果信息解码
 Input          : ucOpCode - 操作码
                  pucSrc   - 待解码的内容
 Output         : punArg   - 解码后的缓存指针
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsInvokeArgDecode(
    VOS_UINT8                           ucOpCode,
    VOS_UINT8                           *pucSrc,
    MN_CALL_SS_COMPONENT_ARG_UNION      *punArg
)
{
    switch(ucOpCode)
    {
    case MN_CALL_SS_NOTIFYSS_OPERATION:
        return MN_CALL_DecodeNotifySs(&punArg->notifySsArg, &pucSrc);

    default:
        return VOS_ERR;
    }
}

#if 0
LOCAL VOS_UINT32 CALL_SsResultArgEncode(
    VOS_UINT8                            ucOpCode,
    const MN_CALL_SS_COMPONENT_ARG_UNION *punArg,
    VOS_UINT8                            *pucDest
)
{
    return 0;
}
#endif

/*****************************************************************************
 Prototype      : MN_CALL_SsResultArgDecode()
 Description    : 操作结果信息解码
 Input          : ucOpCode - 操作码
                  pucSrc   - 待解码的内容
 Output         : punArg   - 解码后的缓存指针
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsResultArgDecode(
    VOS_UINT8                           ucOpCode,
    VOS_UINT8                           *pucSrc,
    MN_CALL_SS_COMPONENT_ARG_UNION      *punArg
)
{
    return VOS_ERR;
}

#if 0
/*****************************************************************************
 Prototype      : MN_CALL_SsErrorArgDecode()
 Description    : 错误码信息编码
 Input          : ucErrorCode - 需要编码的component的内容
                  punArg      - Component部分的内容
 Output         : pucDest     - 编码后的缓存指针
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsErrorArgDecode(
    VOS_UINT8                            ucErrorCode,
    const MN_CALL_SS_COMPONENT_ARG_UNION *punArg,
    VOS_UINT8                            *pucDest
)
{
    return 0;
}
#endif

/*****************************************************************************
 Prototype      : MN_CALL_SsErrorArgDecode()
 Description    : 错误码信息解码
 Input          : pucSrc      - 需要解码的内容
                  ucErrorCode - 错误码
 Output         : punArg      - 解码后的缓存指针
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsErrorArgDecode(
    VOS_UINT8                           ucErrorCode,
    VOS_UINT8                           *pucSrc,
    MN_CALL_SS_COMPONENT_ARG_UNION      *punArg
)
{
    return VOS_ERR;
}



/*****************************************************************************
 Prototype      : MN_CALL_SsComponentDecode
 Description    : Component部分解码
 Input          : pucSrc - 输入的字串
 Output         : punComponent - Component部分的解码

 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsComponentDecode(
    VOS_UINT8                           *pucSrc,
    MN_CALL_SS_COMPONENT_UNION          *punComponent
)
{
    punComponent->ucCompType = pucSrc[0];

    switch(punComponent->ucCompType)
    {
    case MN_CALL_SS_INVOKE_TYPE_TAG:
        punComponent->invokeComp.ucInvokeId = pucSrc[4];
        if (pucSrc[5] == MN_CALL_SS_LINKED_ID_TAG)
        {
            punComponent->invokeComp.bitOpLinkId = 1;
            punComponent->invokeComp.ucLinkId = pucSrc[7];
            punComponent->invokeComp.ucOperateCode = pucSrc[10];
            if (MN_CALL_SsInvokeArgDecode(punComponent->invokeComp.ucOperateCode,
                                      &pucSrc[11],
                                      &punComponent->invokeComp.unArg) == VOS_OK)
            {
                punComponent->invokeComp.bitOpArg = 1;
            }
        }
        else
        {
            punComponent->invokeComp.bitOpLinkId = 0;
            punComponent->invokeComp.ucOperateCode = pucSrc[7];
            if (MN_CALL_SsInvokeArgDecode(punComponent->invokeComp.ucOperateCode,
                                      &pucSrc[8],
                                      &punComponent->invokeComp.unArg) == VOS_OK)
            {
                punComponent->invokeComp.bitOpArg = 1;
            }
            else
            {
                punComponent->invokeComp.bitOpArg = 0;
            }
        }
        break;

    case MN_CALL_SS_RETURN_RESULT_TYPE_TAG:
        punComponent->resultComp.ucInvokeId = pucSrc[4];
        if (pucSrc[1] > 8)
        {
            /* Omitted if the Return Result component
            does not include any parameters. - 24.080*/
            punComponent->resultComp.bitOpSequence = 1;
            punComponent->resultComp.bitOpOperateCode = 1;
            punComponent->resultComp.ucSequenceTag = pucSrc[5];
            punComponent->resultComp.ucOperateCode = pucSrc[9];
            if (MN_CALL_SsResultArgDecode(punComponent->resultComp.ucOperateCode,
                                     &pucSrc[10],
                                     &punComponent->resultComp.unArg) == VOS_OK)
            {
                punComponent->resultComp.bitOpArg = 1;
            }
            else
            {
                punComponent->resultComp.bitOpArg = 0;
            }
        }
        else
        {
            punComponent->resultComp.bitOpArg = 0;
            punComponent->resultComp.bitOpSequence = 0;
            punComponent->resultComp.bitOpOperateCode = 0;
        }
        break;

    case MN_CALL_SS_RETURN_ERROR_TYPE_TAG:
        punComponent->errorComp.ucInvokeId = pucSrc[4];
        punComponent->errorComp.ucErrorCode = pucSrc[7];
        if (pucSrc[1] > 6)
        {
            if (MN_CALL_SsErrorArgDecode(punComponent->errorComp.ucErrorCode,
                                    &pucSrc[8],
                                    &punComponent->errorComp.unArg) == VOS_OK)
            {
                punComponent->errorComp.bitOpArg = 1;
            }
            else
            {
                punComponent->errorComp.bitOpArg = 0;
            }
        }
        else
        {
            punComponent->errorComp.bitOpArg = 0;
        }
        break;

    case MN_CALL_SS_REJECT_TYPE_TAG:
        punComponent->rejectComp.ucInvokeId = pucSrc[4];
        punComponent->rejectComp.ucProblemCode = pucSrc[7];
        break;

    default:
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 Prototype      : MN_CALL_FacilityDecode()
 Description    : Facility消息解码
 Input          : ulMsgPointer   接收消息的指针
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_UINT32 MN_CALL_FacilityDecode(
    const NAS_CC_IE_FACILITY_STRU       *pstFacility,
    MN_CALL_SS_COMPONENT_UNION          *punComponent
)
{
    VOS_UINT8                           aucFacility[NAS_CC_MAX_FACILITY_LEN];

    PS_MEM_SET(aucFacility, 0x00, sizeof(aucFacility));

    /* 此处为了规避告警，由于后续解码的时候，参数都没有限制成const  */
    PS_MEM_CPY(aucFacility, pstFacility->aucFacility, NAS_CC_MAX_FACILITY_LEN);

    if(0 == pstFacility->LastOctOffset)
    /* if (0 == NAS_IE_GET_BLOCK_SIZE(pstFacility, aucFacility)) */
    {
        MN_ERR_LOG ( "MN_CALL_FacilityDecode:  IE length is 0!\n" );
        return VOS_ERR;
    }

    if (VOS_OK != MN_CALL_SsComponentDecode(aucFacility, punComponent))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif



