/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LnasLppEncode.c
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
#include  "NasLppAirMsg.h"
#include  "NasLppOm.h"
#include  "NasLppEncodeDecodePublic.h"
#include  "NasLppPublic.h"
#include  "NasLppEncode.h"
#include  "NasCommPrint.h"
#include  "LPPLRrcInterface.h"
#include  "NasLppSendMsg.h"
#include  "NasLppLcsMsgProc.h"

#define NAS_LPP_ENCODE_WARNING

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPENCODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPENCODE_C


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/
#if (FEATURE_LPP == FEATURE_ON)

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDUIdentifier
 Description     : 编码LPP_EPDU_IDENTIFIER_STRU
 Input           : pstEPDUIBody               需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 EPDU-Identifier ::= SEQUENCE {
                     ePDU-ID                 EPDU-ID,
                     ePDU-Name               EPDU-Name       OPTIONAL,
                     ...
                 }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDUBody
(
    LPP_EPDU_BODY_STRU                 *pstEPDUIBody,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT32                          ulTempCount         = 0;

    /*编码OCTET STRING 长度*/
    /*协议没有限定长度，但是处理过程中开辟的内存空间为256，超过256内存会溢出覆盖其他
    内容所以这里直接返回错误*/
    if(pstEPDUIBody->ulBodyLen > 256)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_EPDUBODY_ERROR,
                                 NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }
    /*如果长度为256，需要编入0x81,然后编入0x00然后编入BODY数据*/
    if(pstEPDUIBody->ulBodyLen == 256)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0x81);
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0);
    }
    /*如果长度大于等于128，需要占用两个字节，第一个字节值为0x80，第二个字节为长度值*/
    else if(pstEPDUIBody->ulBodyLen >= 128)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0x80);
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)(pstEPDUIBody->ulBodyLen));
    }
    /*如果长度小于128，直接编码八位即可*/
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)(pstEPDUIBody->ulBodyLen));
    }



    /*编码结构体数据*/
    for(ulTempCount = 0;ulTempCount < pstEPDUIBody->ulBodyLen;ulTempCount++)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, pstEPDUIBody->aucBodyData[ulTempCount]);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDUIdentifier
 Description     : 编码LPP_EPDU_IDENTIFIER_STRU
 Input           : pstEPDUIdentifier          需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 EPDU-Identifier ::= SEQUENCE {
                     ePDU-ID                 EPDU-ID,
                     ePDU-Name               EPDU-Name       OPTIONAL,
                     ...
                 }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDUIdentifier
(
    LPP_EPDU_IDENTIFIER_STRU           *pstEPDUIdentifier,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucTempCount         = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);

    /* 编码OPTIONAL标志位*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstEPDUIdentifier->bitOpEpduName));

    /*编码结构体数据*/
    /*编码EPDU-ID*/

    if((pstEPDUIdentifier->ulEpduId < 1) ||(pstEPDUIdentifier->ulEpduId > 256))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EPDUIDENTIFIER_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    ucTempCount = (VOS_UINT8)(pstEPDUIdentifier->ulEpduId - 1);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucTempCount);

    /*编码EPDU-NAME,如果被选中*/
    if(NAS_LPP_NO_SLCT == pstEPDUIdentifier->bitOpEpduName)
    {
        return  NAS_LPP_ENCODE_SUCC;
    }

    /*编码EPDU-NAME长度*/
    if((pstEPDUIdentifier->ulEpduNameLength < 1)||(pstEPDUIdentifier->ulEpduNameLength > 32))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EPDUIDENTIFIER_ERROR, NAS_LPP_CHAR_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR;
    }
    ucTempCount = (VOS_UINT8)(pstEPDUIdentifier->ulEpduNameLength - 1);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 5, ucTempCount);

    /*编码EPDU-NAME值*/
    for(ucTempCount = 0; ucTempCount < (pstEPDUIdentifier->ulEpduNameLength);ucTempCount++)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, pstEPDUIdentifier->acEpduName[ucTempCount]);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDU
 Description     : 编码pstEPDU
 Input           : pstEPDU                    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 EPDU ::= SEQUENCE {
                     ePDU-Identifier         EPDU-Identifier,
                     ePDU-Body               EPDU-Body
                 }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDU
(
    LPP_EPDU_STRU                      *pstEPDU,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usReturnReslt;


    /*编码结构体数据*/
    /*编码EPDU-Identifier*/
    usReturnReslt = NAS_LPP_EncodeEPDUIdentifier(&(pstEPDU->stEpduIdentifier),
                                                    pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
    {
        return  usReturnReslt;
    }

    /*编码EPDU-Body*/
    usReturnReslt = NAS_LPP_EncodeEPDUBody(&(pstEPDU->stEpduBody),
                                              pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
    {
        return  usReturnReslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDUSequence
 Description     : 编码LPP_EPDU_SEQUENCE_STRU
 Input           : pstEPDUSequence            需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

                 maxEPDU INTEGER ::= 16

                 EPDU ::= SEQUENCE {
                     ePDU-Identifier         EPDU-Identifier,
                     ePDU-Body               EPDU-Body
                 }

                 EPDU-Identifier ::= SEQUENCE {
                     ePDU-ID                 EPDU-ID,
                     ePDU-Name               EPDU-Name       OPTIONAL,
                     ...
                 }

                 EPDU-ID ::= INTEGER (1..256)

                 EPDU-Name ::= VisibleString (SIZE (1..32))

                 EPDU-Body ::= OCTET STRING

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDUSequence
(
    LPP_EPDU_SEQUENCE_STRU             *pstEPDUSequence,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usReturnReslt;
    VOS_UINT32                          ulCount             = 0;
    VOS_UINT32                          ulLoop              = 0;
    /*判定长度合法性*/
    if((pstEPDUSequence->ulEpduNum > 16)||(pstEPDUSequence->ulEpduNum < 1))
    {
        NAS_LPP_ENCODE_WARNING;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EPDUSEQUENCE_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*编码长度值*/
    ulCount = pstEPDUSequence->ulEpduNum - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)ulCount);
    /*循环编码EPDU数据*/

    for(ulLoop = 0;ulLoop < pstEPDUSequence->ulEpduNum;ulLoop++)
    {
        usReturnReslt = NAS_LPP_EncodeEPDU(&(pstEPDUSequence->astEpduArray[ulLoop]),
                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
        {
            return  usReturnReslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeInitiator
 Description     : LPP pucInitiator编码
 Input           : pucInitiator         需要编码的LPP消息
                   pusBitPos              编码之后码流的总的BIT数
                   pucEncodeOutMsg        编码之后存放的buf
 Asn             :
             Initiator ::= ENUMERATED {
                 locationServer,
                 targetDevice,
                 ...
             }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-04-28  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeInitiator
(
    LPP_INITIATOR_TYPE_ENUM_UINT8      *pucInitiator,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    if( *pucInitiator > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_INITIATOR_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    /*编码枚举项的扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码枚举项的实际值*/
    /*解释一下，这里枚举只有两项，所以只用1个bit就可以表示*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, *pucInitiator);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeTransactionId
 Description     : LPP transationId编码
 Input           : psLppTranscationId   需要编码的LPP消息
                   pusBitPos              编码之后码流的总的BIT数
                   pucEncodeOutMsg        编码之后存放的buf
 Asn             :
         LPP-TransactionID ::= SEQUENCE {
             initiator               Initiator,
             transactionNumber       TransactionNumber,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-04-28  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeTransactionId
(
    LPP_TRANSACTION_ID_STRU             *pstLppTranscationId,
    VOS_UINT16                          *pusBitPos,
    VOS_UINT8                           *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRelst             = 0;

    /*编码扩展位*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码Initiator*/
    usRelst = NAS_LPP_EncodeInitiator(&(pstLppTranscationId->enInitiator),
                                         pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRelst)
    {
        return  usRelst;
    }

    /*编码整型变量transactionNumber*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8,
                              pstLppTranscationId->ucTransactionNumber);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAcknowLedgement
 Description     : LPP AcknowLedgment编码
 Input           : pstLppAcknowLedgement    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         Acknowledgement ::= SEQUENCE {
             ackRequested    BOOLEAN,
             ackIndicator    SequenceNumber      OPTIONAL
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAcknowLedgement
(
    LPP_ACKNOWLEDGEMENT_STRU           *pstLppAcknowLedgement,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstLppAcknowLedgement->bitOpAckIndicator));

    /*编码ackRequested*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstLppAcknowLedgement->bAckRequested));

    /*编码ackIndicator*/
    if(NAS_LPP_SLCT == pstLppAcknowLedgement->bitOpAckIndicator)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8,
                                  pstLppAcknowLedgement->stAckIndicator.ucSequenceNumber);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeCommonIEsProvideCapabilities
 Description     : 编码pstCommonIesProvideCap
 Input           : pstCommonIesProvideCap   需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         CommonIEsProvideCapabilities ::= SEQUENCE {
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCommonIEsProvideCapabilities
(
    LPP_COMMON_IES_PROVIDE_CAP_STRU    *pstCommonIesProvideCap,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展位*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssId
 Description     : 编码GnssId
 Input           : pstGnssId                需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-ID ::= SEQUENCE {
             gnss-id             ENUMERATED{ gps, sbas, qzss, galileo, glonass, ...},
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssId
(
    LPP_GNSS_ID_STRU                   *pstGnssId,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展位*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码枚举项的扩展项, 无实际扩展，编码一个bit为0即可*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码枚举项的实际值,枚举项总共5项，所以用3个bit表示即可*/
    /*如果枚举值超过范围，则返回，并且抛出异常*/
    if(4 < (pstGnssId->enGnssId))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSID_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, pstGnssId->enGnssId);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSbasIds
 Description     : 编码SbasIds
 Input           : pstSbasIds               需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         SBAS-IDs ::= SEQUENCE {
             sbas-IDs        BIT STRING {    waas        (0),
                                             egnos       (1),
                                             msas        (2),
                                             gagan       (3)  } (SIZE (1..8)),
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSbasIds
(
    LPP_SBAS_IDS_STRU                  *pstSbasIds,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码bit string的长度字段，采用最少编码原则, 长度字段编码
      等于实际长度减去最少界，然后将有效的数据放到最高位*/
    /*因为这个有效的长度目前只有4个bit，即便长度在4-8之间，也认为是错误*/
    if((pstSbasIds->ucSabsIdsLen < 1)
        || (pstSbasIds->ucSabsIdsLen > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SBASIDS_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, (pstSbasIds->ucSabsIdsLen - 1));

    /*编码具体的bit string*/
    /*将有效的数据移到最高位，然后编码实际长度的码流到buffer中即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstSbasIds->ucSabsIdsLen, pstSbasIds->ucSBASIDs);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodePositionMode
 Description     : 编码PositionMode
 Input           : pstPositionMode          需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         PositioningModes ::= SEQUENCE {
             posModes        BIT STRING {    standalone  (0),
                                             ue-based    (1),
                                             ue-assisted (2)  } (SIZE (1..8)),
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodePositionMode
(
    LPP_POSITIONING_MODES_STRU         *pstPositionMode,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码bit string的长度字段，采用最少编码原则, 长度字段编码
      等于实际长度减去最少界，然后将有效的数据放到最高位*/
    if((pstPositionMode->ucPosModeLen < 1)
        || (pstPositionMode->ucPosModeLen > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_POSITIONMODE_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, (pstPositionMode->ucPosModeLen) - 1);

    /*编码具体的bit string*/
    /*将有效的数据移到最高位，然后编码实际长度的码流到buffer中即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstPositionMode->ucPosModeLen,
                              pstPositionMode->ucPositioningModes);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssSignalIds
 Description     : 编码GnssSignalIds
 Input           : pstGnssSignalIds         需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-SignalIDs  ::= SEQUENCE {
             gnss-SignalIDs      BIT STRING (SIZE(8)),
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssSignalIds
(
    LPP_GNSS_SIGNAL_IDS_STRU           *pstGnssSignalIds,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码具体的bit string*, 固定长度无需长度字段*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, pstGnssSignalIds->ucGNSSSignalIds);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAccessTypes
 Description     : 编码AccessTypes
 Input           : pstAccessTypes           需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         AccessTypes ::= SEQUENCE {
             accessTypes     BIT STRING {    eutra       (0),
                                             utra        (1),
                                             gsm         (2)  } (SIZE (1..8)),
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAccessTypes
(
    LPP_ACCESS_TYPES_STRU                       *pstAccessTypes,
    VOS_UINT16                                  *pusBitPos,
    VOS_UINT8                                   *pucEncodeOutMsg)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码bit string的长度字段，采用最少编码原则, 长度字段编码
      等于实际长度减去最少界，然后将有效的数据放到最高位*/
    if((pstAccessTypes->ucAccessTypesCnt < 1)
        || (pstAccessTypes->ucAccessTypesCnt > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ACCESSTYPES_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, (pstAccessTypes->ucAccessTypesCnt) - 1);

    /*编码具体的bit string*/
    /*将有效的数据移到最高位，然后编码实际长度的码流到buffer中即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstAccessTypes->ucAccessTypesCnt,
                              pstAccessTypes->ucAccessTypes);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodePositionMode
 Description     : 编码FtaMeasSupport
 Input           : pstFtaMeasSupport        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         fta-MeasSupport                 SEQUENCE {
                                             cellTime    AccessTypes,
                                             mode        PositioningModes,
                                             ...
                                         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeFtaMeasSupport
(
    LPP_FTA_MEAS_SUPPORT_STRU          *pstFtaMeasSupport,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt = 0;
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码AccessTypes*/
    usRslt = NAS_LPP_EncodeAccessTypes(&(pstFtaMeasSupport->stAccessTypes),
                                          pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码PositioningModes*/
    usRslt = NAS_LPP_EncodePositionMode(&(pstFtaMeasSupport->stPositioningModes),
                                           pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesGnssSuportList
 Description     : 编码AgnssSupporElement
 Input           : pstAgnssSupporElement    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-SupportList ::= SEQUENCE (SIZE(1..16)) OF GNSS-SupportElement

         GNSS-SupportElement ::= SEQUENCE {
             gnss-ID                         GNSS-ID,
             sbas-IDs                        SBAS-IDs                    OPTIONAL,   -- Cond GNSS-ID-SBAS
             agnss-Modes                     PositioningModes,
             gnss-Signals                    GNSS-SignalIDs,
             fta-MeasSupport                 SEQUENCE {
                                                 cellTime    AccessTypes,
                                                 mode        PositioningModes,
                                                 ...
                                             }                           OPTIONAL,   -- Cond fta
             adr-Support                     BOOLEAN,
             velocityMeasurementSupport      BOOLEAN,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapGnssSupportElement
(
    LPP_GNSS_SUPPORT_ELEMENT_STRU      *pstAgnssSupporElement,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucOption        = 0;
    VOS_UINT16                          usRslt          = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    ucOption = (VOS_UINT8)((((pstAgnssSupporElement->bitOpSbasIds) << 1))
                | (pstAgnssSupporElement->bitOpFtaMeasSupport));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, ucOption);

    /*编码GNSS-ID*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstAgnssSupporElement->stGnssId),
                                     pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码SBAS-IDs*/
    if(NAS_LPP_SLCT == pstAgnssSupporElement->bitOpSbasIds)
    {
        usRslt = NAS_LPP_EncodeSbasIds(&(pstAgnssSupporElement->stSbasIds),
                                          pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码PositioningModes*/
    usRslt = NAS_LPP_EncodePositionMode(&(pstAgnssSupporElement->stAgnssModes),
                                           pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码GNSS-SignalIDs*/
    NAS_LPP_EncodeGnssSignalIds(&(pstAgnssSupporElement->stGnssSignals),
                                   pusBitPos, pucEncodeOutMsg);

    /*编码fta-MeasSupport*/
    if(NAS_LPP_SLCT == pstAgnssSupporElement->bitOpFtaMeasSupport)
    {
        usRslt = NAS_LPP_EncodeFtaMeasSupport(&(pstAgnssSupporElement->stFtaMeasSupport),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码adr-Support*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssSupporElement->bSdrSupport));

    /*编码velocityMeasurementSupport*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssSupporElement->bVelocityMeasurementSupport));

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesGnssSuportList
 Description     : 编码AgnssSupportList
 Input           : pstAgnssSupportList    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-SupportList ::= SEQUENCE (SIZE(1..16)) OF GNSS-SupportElement

         GNSS-SupportElement ::= SEQUENCE {
             gnss-ID                         GNSS-ID,
             sbas-IDs                        SBAS-IDs                    OPTIONAL,   -- Cond GNSS-ID-SBAS
             agnss-Modes                     PositioningModes,
             gnss-Signals                    GNSS-SignalIDs,
             fta-MeasSupport                 SEQUENCE {
                                                 cellTime    AccessTypes,
                                                 mode        PositioningModes,
                                                 ...
                                             }                           OPTIONAL,   -- Cond fta
             adr-Support                     BOOLEAN,
             velocityMeasurementSupport      BOOLEAN,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesGnssSupportList
(
    LPP_GNSS_SUPPORT_LIST_STRU         *pstAgnssSupportList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8   ucLoop = 0;
    VOS_UINT16  usRslt = 0;
    VOS_UINT8   ucGnssSupportNum = 0;

    /*编码GnssSupport计数，这里是有约束的结构体数组，所以长度采用最小bit编码原则，
      具体的值采用相对位置的值为准,有约束的长度是16-1=15，表示15最大需要4个bit
      表示，所以编码也只需要编4个bit即可*/
    if((1 > (pstAgnssSupportList->ulSupportElementNum))
       || (LPP_MAX_GNSS_SUPPORT_ELEMENT_NUM < (pstAgnssSupportList->ulSupportElementNum)))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_AGNSSIESPROVIDECAPABILITIESGNSSSUPPORTLIST_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*编码结构体的计数*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4,
                             (VOS_UINT8)((pstAgnssSupportList->ulSupportElementNum) - 1));

    /*编码结构体数组的具体成员GNSS-SupportElement*/
    ucGnssSupportNum = (VOS_UINT8)(pstAgnssSupportList->ulSupportElementNum);
    for(ucLoop = 0; ucLoop < ucGnssSupportNum; ucLoop++)
    {
        usRslt = NAS_LPP_EncodeAGNSSIEsProvideCapGnssSupportElement(&(pstAgnssSupportList->astGnssSupportElementArray[ucLoop]),
                                                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssSystemTime
 Description     : 编码GnssIdBitMap
 Input           : pstGnssIdBitMap                  需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     GNSS-ID-Bitmap ::= SEQUENCE {
         gnss-ids            BIT STRING {    gps         (0),
                                             sbas        (1),
                                             qzss        (2),
                                             galileo     (3),
                                             glonass     (4)  } (SIZE (1..16)),
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssSystemTime
(
    LPP_GNSS_ID_BITMAP_STRU            *pstGnssIdBitMap,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码bit string的长度字段，采用最少编码原则, 长度字段编码
      等于实际长度减去最少界，然后将有效的数据放到最高位*/
    if((pstGnssIdBitMap->usGnssIdsCnt < 1)
        || (pstGnssIdBitMap->usGnssIdsCnt > 16))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSYSTEMTIME_ERROR,
                                 NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4,
                             (VOS_UINT8)((pstGnssIdBitMap->usGnssIdsCnt) - 1));
    /*编码具体的bit map*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos,
                                  pstGnssIdBitMap->usGnssIdsCnt,
                                  (VOS_UINT32)(pstGnssIdBitMap->usGNSSIDs));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGNSSCommonAssistanceDataSupportRefTime
 Description     : 编码GnssRefTimeSupport
 Input           : pstGnssRefTimeSupport            需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     GNSS-ReferenceTimeSupport ::=   SEQUENCE {
         gnss-SystemTime     GNSS-ID-Bitmap,
         fta-Support         AccessTypes                                     OPTIONAL, -- Cond fta
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupportRefTime
(
    LPP_GNSS_REFERENCE_TIME_SUPPORT_STRU                    *pstGnssRefTimeSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    VOS_UINT8                                                ucOption       = 0;
    VOS_UINT16                                               usRslt         = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    ucOption = (VOS_UINT8)(pstGnssRefTimeSupport->bitOpFtaSupport);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, ucOption);

    /*编码GNSS-SystemTime*/
    usRslt = NAS_LPP_EncodeGnssSystemTime(&(pstGnssRefTimeSupport->stGnssSystemTime),
                                             pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码FTA_Support*/
    if(NAS_LPP_SLCT == pstGnssRefTimeSupport->bitOpFtaSupport)
    {
        usRslt = NAS_LPP_EncodeAccessTypes(&(pstGnssRefTimeSupport->stFtaSupport),
                                              pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGNSSCommonAssistanceDataSupportLocSupport
 Description     : 编码GnssLocationSupport
 Input           : pstGnssLocationSupport           需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     GNSS-ReferenceLocationSupport ::=   SEQUENCE {
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupportLocSupport
(
    LPP_GNSS_REFERENCE_LOCATION_SUPPORT_STRU                *pstGnssLocationSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    /*这里比较特殊就只有...扩展位，所以只需要编码扩展位即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGNSSCommonAssistanceDataSupportInonModelSupport
 Description     : 编码GnssIonModeSupport
 Input           : pstGnssIonModeSupport            需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     GNSS-IonosphericModelSupport ::=    SEQUENCE {
         ionoModel       BIT STRING {    klobuchar   (0),
                                         neQuick     (1) } (SIZE (1..8)),
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupportInonModelSupport
(
    LPP_GNSS_IONOSPHERIC_MODE_SUPPORT_STRU                  *pstGnssIonModeSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码bit string的长度字段，采用最少编码原则, 长度字段编码
      等于实际长度减去最少界，然后将有效的数据放到最高位*/
    if((pstGnssIonModeSupport->ucIonoModelLen < 1)
        || (pstGnssIonModeSupport->ucIonoModelLen > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSCOMMONASSISTANCEDATASUPPORTINONMODELSUPPORT_ERROR,
                                 NAS_LPP_BIT_STRING_LEN_ERROR, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, (pstGnssIonModeSupport->ucIonoModelLen) - 1);

    /*编码具体的bit string*/
    /*将有效的数据移到最高位，然后编码实际长度的码流到buffer中即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstGnssIonModeSupport->ucIonoModelLen,
                              pstGnssIonModeSupport->ucIonoModel);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGNSSCommonAssistanceDataSupportEarthOrientParaSupport
 Description     : 编码GnssEarthOrientParaSupport
 Input           : pstGnssEarthOrientParaSupport    需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     GNSS-EarthOrientationParametersSupport ::=  SEQUENCE {
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupportEarthOrientParaSupport
(
    LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_SUPPORT_STRU      *pstGnssEarthOrientParaSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    /*这里比较特殊就只有...扩展位，所以只需要编码扩展位即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGNSSCommonAssistanceDataSupport
 Description     : 编码CommonAssitDataSupport
 Input           : pstCommonAssitDataSupport        需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     GNSS-CommonAssistanceDataSupport ::= SEQUENCE {
         gnss-ReferenceTimeSupport               GNSS-ReferenceTimeSupport
                                                                     OPTIONAL, -- Cond RefTimeSup
         gnss-ReferenceLocationSupport           GNSS-ReferenceLocationSupport
                                                                     OPTIONAL, -- Cond RefLocSup
         gnss-IonosphericModelSupport            GNSS-IonosphericModelSupport
                                                                     OPTIONAL, -- Cond IonoModSup
         gnss-EarthOrientationParametersSupport  GNSS-EarthOrientationParametersSupport
                                                                     OPTIONAL, -- Cond EOPSup
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupport
(
    LPP_GNSS_COMMON_ASSISTANCE_DATA_SUPPORT_STRU            *pstCommonAssitDataSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    VOS_UINT8                                                ucOption       = 0;
    VOS_UINT16                                               usRslt         = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    ucOption = (VOS_UINT8)(((pstCommonAssitDataSupport->bitOpGnssReferenceTimeSupport) << 3)
                | ((pstCommonAssitDataSupport->bitOpGnssReferenceLocationSupport) << 2)
                | ((pstCommonAssitDataSupport->bitOpGnssIonosphericModelSupport) << 1)
                | (pstCommonAssitDataSupport->bitOpGnssEarthOrientationParametersSupport));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, ucOption);

    /*编码ReferenceTimeSupport*/
    if(NAS_LPP_SLCT == pstCommonAssitDataSupport->bitOpGnssReferenceTimeSupport)
    {
        usRslt = NAS_LPP_EncodeGNSSCommonAssistanceDataSupportRefTime(&(pstCommonAssitDataSupport->stGnssReferenceTimeSupport),
                                                                         pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码ReferenceLocationSupport*/
    if(NAS_LPP_SLCT == pstCommonAssitDataSupport->bitOpGnssReferenceLocationSupport)
    {
        NAS_LPP_EncodeGNSSCommonAssistanceDataSupportLocSupport(&(pstCommonAssitDataSupport->stGnssReferenceLocationSupport),
                                                                   pusBitPos, pucEncodeOutMsg);
    }

    /*编码IonosphericModelSupport*/
    if(NAS_LPP_SLCT == pstCommonAssitDataSupport->bitOpGnssIonosphericModelSupport)
    {
        usRslt = NAS_LPP_EncodeGNSSCommonAssistanceDataSupportInonModelSupport(&(pstCommonAssitDataSupport->stGnssIonosphericModelSupport),
                                                                                  pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码EarthOrientationParametersSupport*/
    if(NAS_LPP_SLCT == pstCommonAssitDataSupport->bitOpGnssEarthOrientationParametersSupport)
    {
        NAS_LPP_EncodeGNSSCommonAssistanceDataSupportEarthOrientParaSupport(&(pstCommonAssitDataSupport->stGnssEarthOrientationParametersSupport),
                                                                               pusBitPos, pucEncodeOutMsg);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSbasId
 Description     : 编码SbasId
 Input           : pstSbasId                需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         SBAS-ID ::= SEQUENCE {
             sbas-id             ENUMERATED { waas, egnos, msas, gagan, ...},
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSbasId
(
    LPP_SBAS_ID_STRU                   *pstSbasId,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展位*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码枚举项initiator*/
    /*编码枚举项的扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码枚举项的实际值, 因为有4项，所以需要2个bit来表示*/
    if(pstSbasId->enLppSbasId > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SBASID_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, pstSbasId->enLppSbasId);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssTimeModelListSupport
 Description     : 编码GnssTimeModeListSupport
 Input           : pstGnssTimeModeListSupport   需要编码的LPP消息
                   pusBitPos                      编码之后码流的总的BIT数
                   pucEncodeOutMsg                编码之后存放的buf
 Asn             :
         GNSS-TimeModelListSupport ::=   SEQUENCE {
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssTimeModelListSupport
(
    LPP_GNSS_TIME_MODE_LIST_SUPPORT_STRU                   *pstGnssTimeModeListSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssDifferentialCorrectionsSupport
 Description     : 编码GnssDiffCorrectSupport
 Input           : pstGnssDiffCorrectSupport    需要编码的LPP消息
                   pusBitPos                      编码之后码流的总的BIT数
                   pucEncodeOutMsg                编码之后存放的buf
 Asn             :
         GNSS-DifferentialCorrectionsSupport ::=     SEQUENCE {
             gnssSignalIDs           GNSS-SignalIDs,
             dgnss-ValidityTimeSup   BOOLEAN,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssDifferentialCorrectionsSupport
(
    LPP_GNSS_DIFFERENTIAL_CORRECTIONS_SUPPORT_STRU         *pstGnssDiffCorrectSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码GnssSignals*/
    NAS_LPP_EncodeGnssSignalIds(&(pstGnssDiffCorrectSupport->stGnssSignalIDs), pusBitPos, pucEncodeOutMsg);

    /*编码DGNSS-Validity*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssDiffCorrectSupport->bDgnssValidityTimeSup));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssNavigationModelSupport
 Description     : 编码GnssNavigationModeSupport
 Input           : pstGnssNavigationModeSupport 需要编码的LPP消息
                   pusBitPos                      编码之后码流的总的BIT数
                   pucEncodeOutMsg                编码之后存放的buf
 Asn             :
         GNSS-NavigationModelSupport ::= SEQUENCE {
             clockModel      BIT STRING {    model-1     (0),
                                             model-2     (1),
                                             model-3     (2),
                                             model-4     (3),
                                             model-5     (4) } (SIZE (1..8))     OPTIONAL,
             orbitModel      BIT STRING {    model-1     (0),
                                             model-2     (1),
                                             model-3     (2),
                                             model-4     (3),
                                             model-5     (4) } (SIZE (1..8))     OPTIONAL,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssNavigationModelSupport
(
    LPP_GNSS_NAVIGATION_MODE_SUPPORT_STRU                  *pstGnssNavigationModeSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8       ucOption = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    ucOption = (VOS_UINT8)(((pstGnssNavigationModeSupport->bitOpClockModel) << 1)
                | (pstGnssNavigationModeSupport->bitOpOrbitModel));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, ucOption);

    /*编码ClockModel*/
    /*编码bit string的长度字段，采用最少编码原则, 长度字段编码
      等于实际长度减去最少界，然后将有效的数据放到最高位*/
    if(NAS_LPP_SLCT == pstGnssNavigationModeSupport->bitOpClockModel)
    {
        if((pstGnssNavigationModeSupport->stClockModel.ucClockModelCnt < 1)
            || (pstGnssNavigationModeSupport->stClockModel.ucClockModelCnt > 8))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSNAVIGATIONMODELSUPPORT_ERROR,
                                     NAS_LPP_BIT_STRING_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
        }

        /*编码L*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (pstGnssNavigationModeSupport->stClockModel.ucClockModelCnt) - 1);

        /*编码具体的bit string*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos,
                                  pstGnssNavigationModeSupport->stClockModel.ucClockModelCnt,
                                  pstGnssNavigationModeSupport->stClockModel.ucClockModel);
    }

    if(NAS_LPP_SLCT == pstGnssNavigationModeSupport->bitOpOrbitModel)
    {
        if((pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModelCnt < 1)
            || (pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModelCnt > 8))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSNAVIGATIONMODELSUPPORT_ERROR,
                                     NAS_LPP_BIT_STRING_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
        }

        /*编码L*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModelCnt) - 1);

        /*编码具体的bit string*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos,
                                  pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModelCnt,
                                  pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModel);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeRealTimeIntegritySupport
 Description     : 编码GnssRealTimeIntegritySupport
 Input           : pstGnssRealTimeIntegritySupport  需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
         GNSS-RealTimeIntegritySupport ::=   SEQUENCE {
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeRealTimeIntegritySupport
(
    LPP_GNSS_REAL_TIME_INTEGRITY_SUPPORT_STRU              *pstGnssRealTimeIntegritySupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeDataBitAssistanceSupport
 Description     : 编码GnssDataBitAssitSupport
 Input           : pstGnssDataBitAssitSupport  需要编码的LPP消息
                   pusBitPos                     编码之后码流的总的BIT数
                   pucEncodeOutMsg               编码之后存放的buf
 Asn             :
         GNSS-DataBitAssistanceSupport ::=   SEQUENCE {
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeDataBitAssistanceSupport
(
    LPP_GNSS_DATA_BIT_ASSISTANCE_SUPPORT_STRU              *pstGnssDataBitAssitSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAcquisitionAssistanceSupport
 Description     : 编码GnssAcquistionAssitSupport
 Input           : pstGnssAcquistionAssitSupport    需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
         GNSS-AcquisitionAssistanceSupport ::=   SEQUENCE {
             ...,
             confidenceSupport-r10                   ENUMERATED { true }     OPTIONAL,
             dopplerUncertaintyExtSupport-r10        ENUMERATED { true }     OPTIONAL
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAcquisitionAssistanceSupport
(
    LPP_GNSS_ACQUISITION_ASSISTANCE_SUPPORT_STRU           *pstGnssAcquistionAssitSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*这里解释一下，...前置， 说明...之后都是扩展项，那么该场景就是扩展位的编码*/
    /*编码扩展项*/
    VOS_UINT8                                               ucExtIe             = 0;
    VOS_UINT8                                               ucExtOption         = 0;
    VOS_UINT8                                               ucConfidenceLV      = 0;
    VOS_UINT8                                               ucConfidenceFill    = 0;
    VOS_UINT8                                               ucDopplerLV         = 0;
    VOS_UINT8                                               ucDopplerSupportFill = 0;

    /*编码扩展项*/
    ucExtIe = (VOS_UINT8)(pstGnssAcquistionAssitSupport->bitOpGNSSAcquisitionAssistSupExt);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, ucExtIe);

    if(NAS_LPP_NO_SLCT == pstGnssAcquistionAssitSupport->bitOpGNSSAcquisitionAssistSupExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*编码扩展项的L-1, 2-1编码1个扩展项即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, 1);

    /*编码扩展项的可选项*/
    ucExtOption = (VOS_UINT8)(((pstGnssAcquistionAssitSupport->bitOpConfidenceSupportR10) << 1)
                | (pstGnssAcquistionAssitSupport->bitOpDopplerUncertaintyExtSupportR10));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, ucExtOption);

    if(NAS_LPP_SLCT == pstGnssAcquistionAssitSupport->bitOpConfidenceSupportR10)
    {
        /*编码confidenceSupport 的L+V, 这里占用一个byte， 具体数据表示占用多少个byte*/
        ucConfidenceLV = 1;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucConfidenceLV);

        /*注意这里枚举项只有一项，不占用bit，也就是只要选中，肯定有值，所以这里编码8个填充位即可*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucConfidenceFill);
    }

    if(NAS_LPP_SLCT == pstGnssAcquistionAssitSupport->bitOpDopplerUncertaintyExtSupportR10)
    {
        /*编码dopplerUncertaintyExtSupport 的L+V, 这里占用一个byte， 具体数据表示占用多少个byte*/
        ucDopplerLV = 1;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucDopplerLV);

        /*注意这里枚举项只有一项，不占用bit，也就是只要选中，肯定有值*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucDopplerSupportFill);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAlmanacSupport
 Description     : 编码GnssAlanacSupport
 Input           : pstGnssAlanacSupport    需要编码的LPP消息
                   pusBitPos                 编码之后码流的总的BIT数
                   pucEncodeOutMsg           编码之后存放的buf
 Asn             :
         GNSS-AlmanacSupport ::=     SEQUENCE {
             almanacModel        BIT STRING {    model-1     (0),
                                                 model-2     (1),
                                                 model-3     (2),
                                                 model-4     (3),
                                                 model-5     (4),
                                                 model-6     (5) } (SIZE (1..8))     OPTIONAL,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAlmanacSupport
(
    LPP_GNSS_ALMANAC_SUPPORT_STRU      *pstGnssAlanacSupport,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssAlanacSupport->bitOpAlmanacModel));

    /*编码bit string的长度字段，采用最少编码原则*/
    if(NAS_LPP_SLCT == pstGnssAlanacSupport->bitOpAlmanacModel)
    {
        if((pstGnssAlanacSupport->stAlmanacModel.ulAlmanacModelCnt < 1)
            ||(pstGnssAlanacSupport->stAlmanacModel.ulAlmanacModelCnt > 8))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_ALMANACSUPPORT_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
        }

        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (VOS_UINT8)((pstGnssAlanacSupport->stAlmanacModel.ulAlmanacModelCnt) - 1));

        /*编码具体的bit string*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos,
                                 (VOS_UINT8)(pstGnssAlanacSupport->stAlmanacModel.ulAlmanacModelCnt),
                                  pstGnssAlanacSupport->stAlmanacModel.ucAlmanacModel);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeUTCModelSupport
 Description     : 编码GnssUtcModelSupport
 Input           : pstGnssUtcModelSupport       需要编码的LPP消息
                   pusBitPos                      编码之后码流的总的BIT数
                   pucEncodeOutMsg                编码之后存放的buf
 Asn             :
         GNSS-UTC-ModelSupport ::=   SEQUENCE {
             utc-Model       BIT STRING {    model-1     (0),
                                             model-2     (1),
                                             model-3     (2),
                                             model-4     (3) } (SIZE (1..8))     OPTIONAL,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeUTCModelSupport
(
    LPP_GNSS_UTC_MODEL_SUPPORT_STRU    *pstGnssUtcModelSupport,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssUtcModelSupport->bitOpUtcModel));

    /*编码bit string的长度字段，采用最少编码原则, 长度字段编码
      等于实际长度减去最少界，然后将有效的数据放到最高位*/
    if(NAS_LPP_SLCT == pstGnssUtcModelSupport->bitOpUtcModel)
    {
        if((pstGnssUtcModelSupport->stUtcModel.ulUtcModelCnt < 1)
            || (pstGnssUtcModelSupport->stUtcModel.ulUtcModelCnt > 8))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_UTCMODELSUPPORT_ERROR,
                                     NAS_LPP_BIT_STRING_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
        }

        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (VOS_UINT8)((pstGnssUtcModelSupport->stUtcModel.ulUtcModelCnt) -1));

        /*编码具体的bit string*/
        /*将有效的数据移到最高位，然后编码实际长度的码流到buffer中即可*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos,
                                 (VOS_UINT8)(pstGnssUtcModelSupport->stUtcModel.ulUtcModelCnt),
                                  pstGnssUtcModelSupport->stUtcModel.ucUTCModel);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAuxiliaryInformationSupport
 Description     : 编码GnssAuxiliaryInfoSupport
 Input           : pstGnssAuxiliaryInfoSupport  需要编码的LPP消息
                   pusBitPos                      编码之后码流的总的BIT数
                   pucEncodeOutMsg                编码之后存放的buf
 Asn             :
         GNSS-AuxiliaryInformationSupport ::=    SEQUENCE {
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAuxiliaryInformationSupport
(
    LPP_GNSS_AUXILIARY_INFORMATION_SUPPORT_STRU            *pstGnssAuxiliaryInfoSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAGNSSIEsProvideCapGenericAssitDataSupportList
 Description     : 编码GnssGenericAssitDataSupportElement
 Input           : pstGnssGenericAssitDataSupportElement    需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     GNSS-GenericAssistDataSupportElement ::= SEQUENCE {
         gnss-ID                             GNSS-ID,
         sbas-ID                             SBAS-ID                     OPTIONAL, -- Cond GNSS ID SBAS
         gnss-TimeModelsSupport              GNSS-TimeModelListSupport
                                                                         OPTIONAL, -- Cond TimeModSup
         gnss-DifferentialCorrectionsSupport GNSS-DifferentialCorrectionsSupport
                                                                         OPTIONAL, -- Cond DGNSS-Sup
         gnss-NavigationModelSupport         GNSS-NavigationModelSupport
                                                                         OPTIONAL, -- Cond NavModSup
         gnss-RealTimeIntegritySupport       GNSS-RealTimeIntegritySupport
                                                                         OPTIONAL, -- Cond RTISup
         gnss-DataBitAssistanceSupport       GNSS-DataBitAssistanceSupport
                                                                         OPTIONAL, -- Cond DataBitsSup
         gnss-AcquisitionAssistanceSupport   GNSS-AcquisitionAssistanceSupport
                                                                         OPTIONAL, -- Cond AcquAssistSup
         gnss-AlmanacSupport                 GNSS-AlmanacSupport
                                                                         OPTIONAL, -- Cond AlmanacSup
         gnss-UTC-ModelSupport               GNSS-UTC-ModelSupport
                                                                         OPTIONAL, -- Cond UTCModSup
         gnss-AuxiliaryInformationSupport    GNSS-AuxiliaryInformationSupport
                                                                         OPTIONAL, -- Cond AuxInfoSup
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapGenericAssitDataSupportList
(
    LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_STRU   *pstGnssGenericAssitDataSupportElement,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    VOS_UINT16                                               usOption       = 0;
    VOS_UINT16                                               usRslt         = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    usOption = (VOS_UINT16)(((pstGnssGenericAssitDataSupportElement->bitOpSbasIds) << 9)
                | ((pstGnssGenericAssitDataSupportElement->bitOpGnssTimeModelListSupport) << 8)
                | ((pstGnssGenericAssitDataSupportElement->bitOpGnssDifferentialCorrectionsSupport) << 7)
                | ((pstGnssGenericAssitDataSupportElement->bitOpGnssNavigationModelSupport) << 6)
                | ((pstGnssGenericAssitDataSupportElement->bitOpRealTimeIntegritySupport) << 5)
                | ((pstGnssGenericAssitDataSupportElement->bitOpDataBitAssistanceSupport) << 4)
                | ((pstGnssGenericAssitDataSupportElement->bitOpAcquisitionAssistanceSupport) << 3)
                | ((pstGnssGenericAssitDataSupportElement->bitOpAlmanacSupport) << 2)
                | ((pstGnssGenericAssitDataSupportElement->bitOpUtcModelSupport) << 1)
                | (pstGnssGenericAssitDataSupportElement->bitOpAuxiliaryInformationSupport));

    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10, usOption);

    /*编码GNSS-ID*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstGnssGenericAssitDataSupportElement->stGnssId),
                                     pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码SBAS-IDS*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpSbasIds)
    {
        usRslt = NAS_LPP_EncodeSbasId(&(pstGnssGenericAssitDataSupportElement->stSbasId), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码TimeModelListSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpGnssTimeModelListSupport)
    {
        NAS_LPP_EncodeGnssTimeModelListSupport(&(pstGnssGenericAssitDataSupportElement->stGnssTimeModelListSupport),
                                                  pusBitPos, pucEncodeOutMsg);
    }

    /*编码DifferentialCorrectionsSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpGnssDifferentialCorrectionsSupport)
    {
        NAS_LPP_EncodeGnssDifferentialCorrectionsSupport(&(pstGnssGenericAssitDataSupportElement->stGnssDifferentialCorrectionsSupport),
                                                            pusBitPos, pucEncodeOutMsg);
    }

    /*编码NavigationModelSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpGnssNavigationModelSupport)
    {
        usRslt = NAS_LPP_EncodeGnssNavigationModelSupport(&(pstGnssGenericAssitDataSupportElement->stGnssNavigationModelSupport),
                                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码RealTimeIntegritySupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpRealTimeIntegritySupport)
    {
        NAS_LPP_EncodeRealTimeIntegritySupport(&(pstGnssGenericAssitDataSupportElement->stGnssRealTimeIntegritySupport),
                                                  pusBitPos, pucEncodeOutMsg);
    }

    /*编码DataBitAssistanceSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpDataBitAssistanceSupport)
    {
        NAS_LPP_EncodeDataBitAssistanceSupport(&(pstGnssGenericAssitDataSupportElement->stGnssDataBitAssistanceSupport),
                                                  pusBitPos, pucEncodeOutMsg);
    }

    /*编码AcquisitionAssistanceSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpAcquisitionAssistanceSupport)
    {
        usRslt = NAS_LPP_EncodeAcquisitionAssistanceSupport(&(pstGnssGenericAssitDataSupportElement->stGnssAcquisitionAssistanceSupport),
                                                               pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码AlmanacSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpAlmanacSupport)
    {
        usRslt = NAS_LPP_EncodeAlmanacSupport(&(pstGnssGenericAssitDataSupportElement->stGnssAlmanacSupport),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码UTC-ModelSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpUtcModelSupport)
    {
        usRslt = NAS_LPP_EncodeUTCModelSupport(&(pstGnssGenericAssitDataSupportElement->stGnssUtcModelSupport),
                                                  pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码AuxiliaryInformationSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpAuxiliaryInformationSupport)
    {
        NAS_LPP_EncodeAuxiliaryInformationSupport(&(pstGnssGenericAssitDataSupportElement->stGnssAuxiliaryInformationSupport),
                                                     pusBitPos, pucEncodeOutMsg);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGNSSGenericAssistanceDataSupport
 Description     : 编码GenericAssitDataSupport
 Input           : pstGenericAssitDataSupport       需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     GNSS-GenericAssistanceDataSupport ::=
                                     SEQUENCE (SIZE (1..16)) OF GNSS-GenericAssistDataSupportElement

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGNSSGenericAssistanceDataSupport
(
    LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_STRU          *pstGenericAssitDataSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucGenericAssitDataSupportNum    = 0;
    VOS_UINT8                                               ucLoop                          = 0;
    VOS_UINT16                                              usReslt                         = 0;

    /*编码GnssSupport计数，这里是有约束的结构体数组，所以长度采用最小bit编码原则，
      具体的值采用相对位置的值为准,有约束的长度是16-1=15，表示15最大需要4个bit
      表示，所以编码也只需要编4个bit即可*/
    if((1 > pstGenericAssitDataSupport->ulSupportElementNum)
        || (LPP_MAX_GNSS_GENERIC_ASSIST_DATA_SUPPORT_ELMENT_LEN < pstGenericAssitDataSupport->ulSupportElementNum))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSGENERICASSISTANCEDATASUPPORT_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 4,
                                 (pstGenericAssitDataSupport->ulSupportElementNum) - 1);

    /*编码结构体数组的具体成员GNSS-SupportElement*/
    ucGenericAssitDataSupportNum = (VOS_UINT8)(pstGenericAssitDataSupport->ulSupportElementNum);
    for(ucLoop = 0; ucLoop < ucGenericAssitDataSupportNum; ucLoop++)
    {
        usReslt = NAS_LPP_EncodeAGNSSIEsProvideCapGenericAssitDataSupportList(&(pstGenericAssitDataSupport->astSupportElementArray[ucLoop]),
                                                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usReslt)
        {
            return  usReslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesAssistanceDataSupportList
 Description     : 编码AgnssAssitDataSupportList
 Input           : pstAgnssAssitDataSupportList     需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     AssistanceDataSupportList ::= SEQUENCE {
         gnss-CommonAssistanceDataSupport    GNSS-CommonAssistanceDataSupport,
         gnss-GenericAssistanceDataSupport   GNSS-GenericAssistanceDataSupport,
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesAssistanceDataSupportList
(
    LPP_ASSISTANCE_DATA_SUPPORT_LIST_STRU                  *pstAgnssAssitDataSupportList,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt             = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码GNSS-CommonAssistanceDataSupport*/
    usRslt = NAS_LPP_EncodeGNSSCommonAssistanceDataSupport((LPP_GNSS_COMMON_ASSISTANCE_DATA_SUPPORT_STRU*)&(pstAgnssAssitDataSupportList->stGnssCommonAssistanceDataSupport),
                                                              pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码GNSS-CommonAssistanceDataSupport*/
    usRslt = NAS_LPP_EncodeGNSSGenericAssistanceDataSupport((LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_STRU*)&(pstAgnssAssitDataSupportList->stGnssGenericAssistanceDataSupport),
                                                               pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationCoordinateTypes
 Description     : 编码AgnssLocCoordinateType
 Input           : pstAgnssLocCoordinateType        需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     LocationCoordinateTypes ::= SEQUENCE {
         ellipsoidPoint                                          BOOLEAN,
         ellipsoidPointWithUncertaintyCircle                     BOOLEAN,
         ellipsoidPointWithUncertaintyEllipse                    BOOLEAN,
         polygon                                                 BOOLEAN,
         ellipsoidPointWithAltitude                              BOOLEAN,
         ellipsoidPointWithAltitudeAndUncertaintyEllipsoid       BOOLEAN,
         ellipsoidArc                                            BOOLEAN,
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationCoordinateTypes
(
    LPP_LOCATION_COORDINATE_TYPE_STRU                      *pstAgnssLocCoordinateType,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码ellipsoidPoint*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                 (VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPoint));

    /*编码ellipsoidPointWithUncertaintyCircle*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPointWithUncertaintyCircle)));

    /*编码ellipsoidPointWithUncertaintyEllipse*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPointWithUncertaintyEllipse)));

    /*编码polygon*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bPolygon)));

    /*编码ellipsoidPointWithAltitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPointWithAltitude)));

    /*编码ellipsoidPointWithAltitudeAndUncertaintyEllipsoid*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPointWithAltitudeAndUncertaintyEllipsoid)));

    /*编码ellipsoidArc*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidArc)));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationVelocityTypes
 Description     : 编码AgnssLocVelocityTypes
 Input           : pstAgnssLocVelocityTypes        需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
     VelocityTypes ::= SEQUENCE {
         horizontalVelocity                                      BOOLEAN,
         horizontalWithVerticalVelocity                          BOOLEAN,
         horizontalVelocityWithUncertainty                       BOOLEAN,
         horizontalWithVerticalVelocityAndUncertainty            BOOLEAN,
         ...
     }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationVelocityTypes
(
    LPP_VELOCITY_TYPES_STRU                                *pstAgnssLocVelocityTypes,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码horizontalVelocity*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocVelocityTypes->bHorizontalVelocity)));

    /*编码horizontalWithVerticalVelocity*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocVelocityTypes->bHorizontalWithVerticalVelocity)));

    /*编码horizontalVelocityWithUncertainty*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocVelocityTypes->bHorizontalVelocityWithUncertainty)));

    /*编码horizontalWithVerticalVelocityAndUncertainty*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocVelocityTypes->bHorizontalWithVerticalVelocityAndUncertainty)));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAGNSSIEsProvideCapabilities
 Description     : 编码AGNSSIesProvideCap
 Input           : pstAGNSSIesProvideCap    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         A-GNSS-ProvideCapabilities ::= SEQUENCE {
             gnss-SupportList            GNSS-SupportList                OPTIONAL,
             assistanceDataSupportList   AssistanceDataSupportList       OPTIONAL,
             locationCoordinateTypes     LocationCoordinateTypes         OPTIONAL,
             velocityTypes               VelocityTypes                   OPTIONAL,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilities
(
    LPP_AGNSS_PROVIDE_CAP_STRU                             *pstAGNSSIesProvideCap,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucOption        = 0;
    VOS_UINT16                                              usRslt          = 0;

    /*编码扩展位*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);


    /*编码可选项*/
    ucOption = (VOS_UINT8)(((pstAGNSSIesProvideCap->bitOpGnssSupportList) << 3)
                | ((pstAGNSSIesProvideCap->bitOpAssistanceDataSupportList) << 2)
                | ((pstAGNSSIesProvideCap->bitOpLocationCoordinateTypes) << 1)
                | (pstAGNSSIesProvideCap->bitOpVelocityTypes));
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 4, ucOption);

    /*编码GNSS-SupportList*/
    if(NAS_LPP_SLCT == pstAGNSSIesProvideCap->bitOpGnssSupportList)
    {
        usRslt = NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesGnssSupportList((LPP_GNSS_SUPPORT_LIST_STRU*)&(pstAGNSSIesProvideCap->stGnssSupportList),
                                                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码AssistanceDataSupportList*/
    if(NAS_LPP_SLCT == pstAGNSSIesProvideCap->bitOpAssistanceDataSupportList)
    {
        usRslt = NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesAssistanceDataSupportList(&(pstAGNSSIesProvideCap->stAssistanceDataSupportList),
                                                                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码LocationCoordinateTypes*/
    if(NAS_LPP_SLCT == pstAGNSSIesProvideCap->bitOpLocationCoordinateTypes)
    {
        NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationCoordinateTypes(&(pstAGNSSIesProvideCap->stLocationCoordinateTypes),
                                                                            pusBitPos, pucEncodeOutMsg);
    }

    /*编码VelocityTypes*/
    if(NAS_LPP_SLCT == pstAGNSSIesProvideCap->bitOpVelocityTypes)
    {
        NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationVelocityTypes(&(pstAGNSSIesProvideCap->stVelocityTypes),
                                                                          pusBitPos, pucEncodeOutMsg);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeOTDOAMode
 Description     : 编码LPP_OTDOA_MODE_STRU
 Input           : pstOTDOAIesProvideCap    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
 otdoa-Mode      BIT STRING {    ue-assisted (0) } (SIZE (1..8)),

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOTDOAMode
(
    LPP_OTDOA_MODE_STRU                *pstOTDOAMode,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucLen               = 0;

    /*编码bit string 的长度*/
    if((pstOTDOAMode->ucOTDOAModeLen < 1)||(pstOTDOAMode->ucOTDOAModeLen > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOAMODE_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }
    ucLen = pstOTDOAMode->ucOTDOAModeLen - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, ucLen);

    /*编码bit string*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstOTDOAMode->ucOTDOAModeLen,
                              pstOTDOAMode->ucOTDOAMode);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSupBandEUTRA
 Description     : 编码LPP_SUPPORTED_BAND_EUTRA_STRU
 Input           : pstOTDOAIesProvideCap    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
 SupportedBandEUTRA ::= SEQUENCE {
        bandEUTRA                           INTEGER (1..maxFBI)
    }

    maxFBI                          INTEGER::=64-- Maximum value of frequency band indicator

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSupBandEUTRA
(
    LPP_SUPPORTED_BAND_EUTRA_STRU      *pstSupBandEUTRA,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT32  ucCount ;
    if((pstSupBandEUTRA->ulBandEutra < 1)||(pstSupBandEUTRA->ulBandEutra > 64))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SUPBANDEUTRA_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    ucCount = pstSupBandEUTRA->ulBandEutra - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)ucCount);
    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSupBandListEUTRA
 Description     : 编码LPP_SUPPORTED_BAND_LIST_EUTRA_STRU
 Input           : pstOTDOAIesProvideCap    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
 supportedBandListEUTRA      SEQUENCE (SIZE (1..maxBands)) OF SupportedBandEUTRA

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSupBandListEUTRA
(
    LPP_SUPPORTED_BAND_LIST_EUTRA_STRU *pstSupBandListEUTRA,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          ulReturnReslt;
    VOS_UINT32                          ucCount ;
    VOS_UINT32                          ucTotalLen          = 0;
    VOS_UINT32                          ulByteCount         = 0;
    VOS_UINT32                          ulTempLen           = 0;

    /*检查sequence of 的长度*/
    if((pstSupBandListEUTRA->ulSupportBandNum < 1)||(pstSupBandListEUTRA->ulSupportBandNum > 64))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SUPBANDLISTEUTRA_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    /*此项为扩展项，需要编码L+V然后编码L和V，需要先行计算,后续加的6是L占得bit数*/
    ucTotalLen = 6 * (pstSupBandListEUTRA->ulSupportBandNum) + 6;
    if((ucTotalLen %8) == 0)
    {
        ulByteCount = ucTotalLen / 8 ;
        ulTempLen = 0;
    }
    else
    {
        ulByteCount = (ucTotalLen/8) +1;
        ulTempLen = 8 - (ucTotalLen % 8);
    }
    /*编码L + V字段*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulByteCount);

    ucCount = pstSupBandListEUTRA->ulSupportBandNum - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)ucCount);

    /*循环编码SEQUENCE*/
    for(ucCount = 0; ucCount < pstSupBandListEUTRA->ulSupportBandNum; ucCount++)
    {
        ulReturnReslt = NAS_LPP_EncodeSupBandEUTRA(&(pstSupBandListEUTRA->astSupportedBandArray[ucCount]),
                                                      pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    /*补齐到字节*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (VOS_UINT16)ulTempLen, 0);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSupBandEUTRAV9A0
 Description     : 编码LPP_SUPPORTED_BAND_EUTRA_V9A0_STRU
 Input           : pstOTDOAIesProvideCap    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
     SupportedBandEUTRA-v9a0 ::=     SEQUENCE {
        bandEUTRA-v9a0                      INTEGER (maxFBI-Plus1..maxFBI2)     OPTIONAL
    }

    maxFBI-Plus1                        INTEGER ::= 65  -- lowest value extended FBI range
    maxFBI2                             INTEGER ::= 256 -- highest value extended FBI range

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSupBandEUTRAV9A0
(
    LPP_SUPPORTED_BAND_EUTRA_V9A0_STRU *pstSupBandEUTRAV9A0,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucCount             = 0;
    if((pstSupBandEUTRAV9A0->ulBandEutraV9A0 < 65)||(pstSupBandEUTRAV9A0->ulBandEutraV9A0 > 256))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SUPBANDEUTRAV9A0_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码一个扩展标志位*/
    if(NAS_LPP_SLCT == pstSupBandEUTRAV9A0->bitOpBandEutraV9A0)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
        ucCount = (VOS_UINT8)(pstSupBandEUTRAV9A0->ulBandEutraV9A0 - 65);
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucCount);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSupBandListEUTRAV9A0
 Description     : 编码LPP_SUPPORTED_BAND_LIST_EUTRA_V9A0_STRU
 Input           : pstOTDOAIesProvideCap    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
 supportedBandListEUTRA-v9a0 SEQUENCE (SIZE (1..maxBands)) OF SupportedBandEUTRA-v9a0

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSupBandListEUTRAV9A0
(
    LPP_SUPPORTED_BAND_LIST_EUTRA_V9A0_STRU                *pstSupBandListEUTRAV9a0,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              ulReturnReslt   = 0;
    VOS_UINT32                                              ucCount         = 0;
    VOS_UINT32                                              ucTotalLen      = 0;
    VOS_UINT32                                              ulByteCount     = 0;
    VOS_UINT32                                              ulTempLen       = 0;

    /*检查sequence of 的长度*/
    if((pstSupBandListEUTRAV9a0->ulSupportBandNum < 1)||(pstSupBandListEUTRAV9a0->ulSupportBandNum > LPP_MAX_SUPPORTED_BAND_EUTRA_NUM))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SUPBANDLISTEUTRAV9A0_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;

    }

    /*此项为扩展项，需要编码L+V然后编码L和V，需要先行计算,有可选项的占用九个bit，没有的占用一个bit，L编码需要6个bit*/
    ucTotalLen = 0;
    for(ucCount = 0; ucCount < pstSupBandListEUTRAV9a0->ulSupportBandNum;ucCount++)
    {
        if(NAS_LPP_SLCT == pstSupBandListEUTRAV9a0->astSupportedBandArray[ucCount].bitOpBandEutraV9A0)
        {
            ucTotalLen += 9;
        }
        else
        {
            ucTotalLen +=1;
        }
    }
    ucTotalLen += 6;
    if((ucTotalLen % 8) == 0)
    {
        ulByteCount = ucTotalLen / 8;
        ulTempLen = 0;
    }
    else
    {
        ulByteCount = (ucTotalLen / 8 ) + 1;
        ulTempLen = 8 - ( ucTotalLen % 8);
    }
    /*编码L + V字段*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulByteCount);

    /*编码L字段*/
    ucCount = pstSupBandListEUTRAV9a0->ulSupportBandNum - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)ucCount);

    /*循环编码SEQUENCE*/
    for(ucCount = 0; ucCount < pstSupBandListEUTRAV9a0->ulSupportBandNum;ucCount++)
    {
        ulReturnReslt = NAS_LPP_EncodeSupBandEUTRAV9A0(&(pstSupBandListEUTRAV9a0->astSupportedBandArray[ucCount]),
                                                          pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }
    /*补齐到字节*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (VOS_UINT16)ulTempLen, 0);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeFreqRSTDMeasurementR10
 Description     : 编码LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_ENUM_UINT32
 Input           : pstOTDOAIesProvideCap    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
 interFreqRSTDmeasurement-r10        ENUMERATED { supported }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeFreqRSTDMeasurementR10
(
    LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_ENUM_UINT32        *pstFreqRSTDMeasurementR10,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码枚举值，没有扩展项的直接编值即可，只有一个枚举项*/
    /*扩展项中的枚举，需要编码L + V，然后编码枚举值，后填补0到满字节*/
    /* 第一个8bit的1是L+V，表示L和V占的字节数，后续的8个bit表示的是值占0个字节 */
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 1);
    if(*pstFreqRSTDMeasurementR10 > 0)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_FREQRSTDMEASUREMENTR10_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAdNeighbourCellInfoListR10
 Description     : 编码LPP_ADDITIONAL_NEIGH_CELL_INFO_LIST_R10_ENUM_UINT32
 Input           : pstOTDOAIesProvideCap    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
 additionalNeighbourCellInfoList-r10 ENUMERATED { supported }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAdNeighbourCellInfoListR10
(
    LPP_ADDITIONAL_NEIGH_CELL_INFO_LIST_R10_ENUM_UINT32    *pstAdNeighbourCellInfoListR10,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码枚举值，没有扩展项的直接编值即可，只有一个枚举项*/

    /*扩展项中的枚举，需要编码L + V，然后编码枚举值，后填补0到满字节*/
    /* 第一个8bit的1是L+V，表示L和V占的字节数，后续的8个bit表示的是值占0个字节 */
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 1);
    if(*pstAdNeighbourCellInfoListR10 > 0)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ADNEIGHBOURCELLINFOLISTR10_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeOTDOAIEsProvideCapabilities
 Description     : 编码OTDOAIesProvideCap
 Input           : pstOTDOAIesProvideCap    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         OTDOA-ProvideCapabilities ::= SEQUENCE {
             otdoa-Mode      BIT STRING {    ue-assisted (0) } (SIZE (1..8)),
             ...,
             supportedBandListEUTRA      SEQUENCE (SIZE (1..maxBands)) OF SupportedBandEUTRA     OPTIONAL,
             supportedBandListEUTRA-v9a0 SEQUENCE (SIZE (1..maxBands)) OF SupportedBandEUTRA-v9a0
                                                                                                 OPTIONAL,
             interFreqRSTDmeasurement-r10        ENUMERATED { supported }                        OPTIONAL,
             additionalNeighbourCellInfoList-r10 ENUMERATED { supported }                        OPTIONAL
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOTDOAIEsProvideCapabilities
(
    LPP_OTDOA_PROVIDE_CAP_STRU                             *pstOTDOAIesProvideCap,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              ulReturnReslt;
    VOS_UINT8                                               ucExtObjectCount    = 0;

    /*编码扩展项,必存在的,如果扩展项有被选中则为1*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpOtdoaProvideCapExt)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*编码OTDOA-Mode*/
    ulReturnReslt = NAS_LPP_EncodeOTDOAMode(&(pstOTDOAIesProvideCap->stOtdoaMode),
                                               pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
    {
        return  ulReturnReslt;
    }

    if(NAS_LPP_NO_SLCT == pstOTDOAIesProvideCap->bitOpOtdoaProvideCapExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*编码扩展项bit-map，共四项，L-1*/
    ucExtObjectCount = 3;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, ucExtObjectCount);

    /*编码扩展项标志位bitOpSupportedBandListEutra*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpSupportedBandListEutra)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*编码扩展项标志位bitOpSupportedBandListEutraV9A0*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpSupportedBandListEutraV9A0)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*编码扩展项标志位bitOpInterFreqRSTDmeasurementR10*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpInterFreqRSTDmeasurementR10)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*编码扩展项标志位bitOpAdditionalNeighbourCellInfoListR10*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpAdditionalNeighbourCellInfoListR10)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*如果扩展项被选中，编码扩展项*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpSupportedBandListEutra)
    {
        ulReturnReslt = NAS_LPP_EncodeSupBandListEUTRA(&(pstOTDOAIesProvideCap->stSupportedBandListEutra),
                                                          pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    /*如果扩展项被选中，编码扩展项*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpSupportedBandListEutraV9A0)
    {
        ulReturnReslt = NAS_LPP_EncodeSupBandListEUTRAV9A0(&(pstOTDOAIesProvideCap->stSupportedBandListEutraV9A0),
                                                              pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    /*如果扩展项被选中，编码扩展项*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpInterFreqRSTDmeasurementR10)
    {
        ulReturnReslt = NAS_LPP_EncodeFreqRSTDMeasurementR10(&(pstOTDOAIesProvideCap->enInterFreqRSTDmeasurementR10),
                                                                pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    /*如果扩展项被选中，编码扩展项*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpAdditionalNeighbourCellInfoListR10)
    {
        ulReturnReslt = NAS_LPP_EncodeAdNeighbourCellInfoListR10(&(pstOTDOAIesProvideCap->enAdditionalNeighbourCellInfoListR10),
                                                                    pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeECIDMeasSupported
 Description     : 编码LPP_ECID_MEAS_SUPPORTED_STRU
 Input           : pstEPDUIesProvideCap     需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
 ecid-MeasSupported  BIT STRING {    rsrpSup     (0),
                                                  rsrqSup     (1),
                                                  ueRxTxSup   (2) } (SIZE(1..8))

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeECIDMeasSupported
(
    LPP_ECID_MEAS_SUPPORTED_STRU                           *pstECIDMeasSupported,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucCount         = 0;

    /*判断长度的合法性*/
    if((pstECIDMeasSupported->ucEcidMeasSupCnt <1)||(pstECIDMeasSupported->ucEcidMeasSupCnt > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ECIDMEASSUPPORTED_ERROR,
                                 NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    /*编码长度*/
    ucCount = pstECIDMeasSupported->ucEcidMeasSupCnt - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, ucCount);

    /*编码BIT STRING*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, pstECIDMeasSupported->ucEcidMeasSupCnt,
                               pstECIDMeasSupported->ucEcidMeasSup);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeECIDIEsProvideCapabilities
 Description     : 编码ECIDIesProvideCap
 Input           : pstECIDIesProvideCap     需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ECID-ProvideCapabilities ::= SEQUENCE {
             ecid-MeasSupported  BIT STRING {    rsrpSup     (0),
                                                 rsrqSup     (1),
                                                 ueRxTxSup   (2) } (SIZE(1..8)),
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeECIDIEsProvideCapabilities
(
    LPP_ECID_PROVIDE_CAP_STRU                              *pstECIDIesProvideCap,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16  usReturnReslt;

    /*编码扩展项标志位，没有扩展项直接为0*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);


    /*编码结构体内容*/
    usReturnReslt = NAS_LPP_EncodeECIDMeasSupported(&(pstECIDIesProvideCap->stEcidMeasSupported),
                                                       pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
    {
        return      usReturnReslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDUIEsProvideCapabilities
 Description     : 编码EPDUIesProvideCap
 Input           : pstEPDUIesProvideCap     需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

                 maxEPDU INTEGER ::= 16

                 EPDU ::= SEQUENCE {
                     ePDU-Identifier         EPDU-Identifier,
                     ePDU-Body               EPDU-Body
                 }

                 EPDU-Identifier ::= SEQUENCE {
                     ePDU-ID                 EPDU-ID,
                     ePDU-Name               EPDU-Name       OPTIONAL,
                     ...
                 }

                 EPDU-ID ::= INTEGER (1..256)

                 EPDU-Name ::= VisibleString (SIZE (1..32))

                 EPDU-Body ::= OCTET STRING

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-18  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDUIEsProvideCapabilities
(
    LPP_EPDU_SEQUENCE_STRU             *pstEPDUIesProvideCap,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usReturnReslt;

    /*调用公共编码函数*/
    usReturnReslt = NAS_LPP_EncodeEPDUSequence(pstEPDUIesProvideCap, pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
    {
        return      usReturnReslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeProvideCapaBilityR9IEs
 Description     : 编码ProvideCapability
 Input           : pstProvideCapR9Ies       需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ProvideCapabilities-r9-IEs ::= SEQUENCE {
             commonIEsProvideCapabilities        CommonIEsProvideCapabilities        OPTIONAL,
             a-gnss-ProvideCapabilities          A-GNSS-ProvideCapabilities          OPTIONAL,
             otdoa-ProvideCapabilities           OTDOA-ProvideCapabilities           OPTIONAL,
             ecid-ProvideCapabilities            ECID-ProvideCapabilities            OPTIONAL,
             epdu-ProvideCapabilities            EPDU-Sequence                       OPTIONAL,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeProvideCapaBilityR9IEs
(
    LPP_PROVIDE_CAPABILITIES_R9_IES_STRU                   *pstProvideCapR9Ies,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucOption    = 0;
    VOS_UINT16                                              usRslt      = 0;

    /*编码扩展位*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    ucOption = (VOS_UINT8)(((pstProvideCapR9Ies->bitOpCommonIEsProvideCapabilities) << 4)
                | ((pstProvideCapR9Ies->bitOpAGNSSProvideCapabilities) << 3)
                | ((pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities) << 2)
                | ((pstProvideCapR9Ies->bitOpECIDProvideCapabilities) << 1)
                | (pstProvideCapR9Ies->bitOpEPDUProvideCapabilities));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 5, ucOption);

    /*编码CommonIEsProvideCapabilities*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpCommonIEsProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeCommonIEsProvideCapabilities(&(pstProvideCapR9Ies->stCommonIEsProvideCapabilities),
                                                               pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码A-GNSS-ProvideCapabilities*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpAGNSSProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeAGNSSIEsProvideCapabilities(&(pstProvideCapR9Ies->stAGNSSProvideCapabilities),
                                                              pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码OTDOA-ProvideCapabilities*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeOTDOAIEsProvideCapabilities(&(pstProvideCapR9Ies->stOTDOAProvideCapabilities),
                                                              pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    /*编码ECID-ProvideCapabilities*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpECIDProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeECIDIEsProvideCapabilities(&(pstProvideCapR9Ies->stECIDProvideCapabilities),
                                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    /*编码EPDU-Sequence*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpEPDUProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeEPDUIEsProvideCapabilities(&(pstProvideCapR9Ies->stEPDURequestCapabilities),
                                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeProvideCapaBilityC1
 Description     : 编码ProvideCapability
 Input           : pstExtProvideCapability          需要编码的LPP消息
                   pusBitPos                          编码之后码流的总的BIT数
                   pucEncodeOutMsg                    编码之后存放的buf
 Asn             :
         ProvideCapabilities ::= SEQUENCE {
             criticalExtensions      CHOICE {
                 c1                      CHOICE {
                     provideCapabilities-r9      ProvideCapabilities-r9-IEs,
                     spare3 NULL, spare2 NULL, spare1 NULL
                 },
                 criticalExtensionsFuture    SEQUENCE {}
             }
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeProvideCapaBilityC1
(
    LPP_CRITI_EXT_PROVIDE_CAPABILITIES_STRU                *pstExtProvideCapability,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    /*编码choice项*/
    if(pstExtProvideCapability->ulChoice > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PROVIDECAPABILITYC1_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*4个choice项，所以用2个bit表示即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstExtProvideCapability->ulChoice));

    switch(pstExtProvideCapability->ulChoice)
    {
        case LPP_PROVIDE_CAPABILITIES_R9_CHOSEN:
            usRslt = NAS_LPP_EncodeProvideCapaBilityR9IEs(&(pstExtProvideCapability->u.stProvideCapabilitiesR9),
                                                             pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeProvideCapability
 Description     : 编码ProvideCapability
 Input           : pstProvideCapabilty      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ProvideCapabilities ::= SEQUENCE {
             criticalExtensions      CHOICE {
                 c1                      CHOICE {
                     provideCapabilities-r9      ProvideCapabilities-r9-IEs,
                     spare3 NULL, spare2 NULL, spare1 NULL
                 },
                 criticalExtensionsFuture    SEQUENCE {}
             }
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeProvideCapability
(
    LPP_MESSAGE_PROVIDE_CAPABILITIES_STRU                  *pstProvideCapabilty,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    /*编码choice项*/
    if(pstProvideCapabilty->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PROVIDECAPABILITY_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*两个choice项，所以用一个bit表示即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstProvideCapabilty->ulChoice));

    switch(pstProvideCapabilty->ulChoice)
    {
        case LPP_C1_CRITI_EXT_PROVIDE_CAPABILITIES_CHOSEN:
            usRslt = NAS_LPP_EncodeProvideCapaBilityC1(&(pstProvideCapabilty->u.stC1),
                                                          pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeEpduReqAssistData
 Description     : 编码LPP_EPDU_REQ_ASSIST_DATA_STRU
 Input           :
 Asn             :
 EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEpduReqAssistData
(
    LPP_EPDU_REQ_ASSIST_DATA_STRU                          *pstEpduReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    usRslt = NAS_LPP_EncodeEPDUSequence(&(pstEpduReqAssistData->astReqAssistDataEpduSeq),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return      usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeOTDOAReqAssistData
 Description     : 编码LPP_OTDOA_REQ_ASSIST_DATA_STRU
 Input           :
 Asn             :
 OTDOA-RequestAssistanceData ::= SEQUENCE {
         physCellId      INTEGER (0..503),
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOTDOAReqAssistData
(
    LPP_OTDOA_REQ_ASSIST_DATA_STRU                         *pstOTDOAReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    if(pstOTDOAReqAssistData->usPhyCellId > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOAREQASSISTDATA_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码结构体内容*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg, pusBitPos, 9, pstOTDOAReqAssistData->usPhyCellId);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssRefTimeReq
 Description     : 编码LPP_GNSS_REFERENCE_TIME_REQ_STRU
 Input           :
 Asn             :
 GNSS-ReferenceTimeReq ::= SEQUENCE {
         gnss-TimeReqPrefList    SEQUENCE (SIZE (1..8)) OF GNSS-ID,
         gps-TOW-assistReq       BOOLEAN                             OPTIONAL, -- Cond gps
         notOfLeapSecReq         BOOLEAN                             OPTIONAL, -- Cond glonass
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssRefTimeReq
(
    LPP_GNSS_REFERENCE_TIME_REQ_STRU                       *pstGnssRefTimeReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16          usRslt = 0;
    VOS_UINT8           ucCount = 0;

    if((pstGnssRefTimeReq->ulGNSSTimeReqPrefListCnt < 1)||(pstGnssRefTimeReq->ulGNSSTimeReqPrefListCnt > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSREFTIMEREQ_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码OPTIONAL项标志位*/
    if(NAS_LPP_SLCT == pstGnssRefTimeReq->bitOpGpsTowAssistReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssRefTimeReq->bitOpNotOfLeapSecReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }


    /*编码结构体内容*/

    /*编码GNSSID-SEQUENCE OF*/
    ucCount = (VOS_UINT8)(pstGnssRefTimeReq->ulGNSSTimeReqPrefListCnt - 1);
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 3, ucCount);
    /*循环编码GNSSID数组内容*/
    for(ucCount = 0;ucCount < pstGnssRefTimeReq->ulGNSSTimeReqPrefListCnt;ucCount++)
    {
        usRslt = NAS_LPP_EncodeGnssId(&(pstGnssRefTimeReq->astGNSSTimeReqPrefListArray[ucCount]),
                                         pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    /*编码gps-TOW-assistReq*/
    if(NAS_LPP_SLCT == pstGnssRefTimeReq->bitOpGpsTowAssistReq)
    {
        if(TRUE == pstGnssRefTimeReq->bGpsTowAssistReq)
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
        }
        else
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
        }
    }

    /*编码notofLeapSecReq*/
    if(NAS_LPP_SLCT == pstGnssRefTimeReq->bitOpNotOfLeapSecReq)
    {
        if(TRUE == pstGnssRefTimeReq->bNotOFLeapSecReq)
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
        }
        else
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
        }
    }



    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssRefLocatReq
 Description     : 编码LPP_GNSS_REFERENCE_LOCATION_REQ_STRU
 Input           :
 Asn             :

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssRefLocatReq
(
    LPP_GNSS_REFERENCE_LOCATION_REQ_STRU                   *pstGnssRefLocatReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*结构体内容为空，只编码扩展位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssIonoModelReq
 Description     : 编码LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU
 Input           :
 Asn             :
 GNSS-IonosphericModelReq ::=    SEQUENCE {
         klobucharModelReq       BIT STRING (SIZE(2))    OPTIONAL,   -- Cond klobuchar
         neQuickModelReq         NULL                    OPTIONAL,   -- Cond nequick
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssIonoModelReq
(
    LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU                    *pstGnssIonoModelReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg)
{
    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码OPTIONAL项标志位*/
    if(NAS_LPP_SLCT == pstGnssIonoModelReq->bitOpKlobucharModelReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }
    if(NAS_LPP_SLCT == pstGnssIonoModelReq->bitOpNeQuickModelReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*编码结构体内容*/
    /*编码BIT STRING*/
    if(NAS_LPP_SLCT == pstGnssIonoModelReq->bitOpKlobucharModelReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                                 (pstGnssIonoModelReq->ucKlobucharModelReq));
    }
    /*第二项为NULL类型，不需要编码*/

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssOrientParamReq
 Description     : 编码LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU
 Input           :
 Asn             :
 GNSS-EarthOrientationParametersReq ::= SEQUENCE {
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssEarthOrientParamReq
(
    LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU         *pstGnssOrientParamReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展标志位，结构体内容为空*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeComReqAssistData
 Description     : 编码LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU
 Input           :
 Asn             :
 GNSS-CommonAssistDataReq ::= SEQUENCE {
        gnss-ReferenceTimeReq               GNSS-ReferenceTimeReq
                                                                    OPTIONAL, -- Cond RefTimeReq
        gnss-ReferenceLocationReq           GNSS-ReferenceLocationReq
                                                                    OPTIONAL, -- Cond RefLocReq
        gnss-IonosphericModelReq            GNSS-IonosphericModelReq
                                                                    OPTIONAL, -- Cond IonoModReq
        gnss-EarthOrientationParametersReq  GNSS-EarthOrientationParametersReq
                                                                    OPTIONAL, -- Cond EOPReq
        ...
    }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssComReqAssistData
(
    LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU                   *pstComReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码OPTIONAL项标志位*/
    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSRefTimeReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSRefLocationReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSIonoModelReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSEarthOriParaReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*编码OPTIONAL项结构数据*/
    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSRefTimeReq)
    {
        usRslt = NAS_LPP_EncodeGnssRefTimeReq(&(pstComReqAssistData->stGNSSReferenceTimeReq),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSRefLocationReq)
    {
        usRslt = NAS_LPP_EncodeGnssRefLocatReq(&(pstComReqAssistData->stGNSSReferenceLocationReq),
                                                  pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSIonoModelReq)
    {
        usRslt = NAS_LPP_EncodeGnssIonoModelReq(&(pstComReqAssistData->stIonosphericModelReq),
                                                   pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSEarthOriParaReq)
    {
        usRslt = NAS_LPP_EncodeGnssEarthOrientParamReq(&(pstComReqAssistData->stEarthOrientationParametersReq),
                                                          pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssTimeModelElementReq
 Description     : 编码LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU
 Input           :
 Asn             :
 GNSS-TimeModelElementReq ::= SEQUENCE {
        gnss-TO-IDsReq  INTEGER (1..15),
        deltaTreq       BOOLEAN,
        ...
    }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssTimeModelElementReq
(
    LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU                   *pstGnssTimeModelElementReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucValue         = 0;

    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码结构体内容*/
    if((pstGnssTimeModelElementReq->ucGNSSToIdsReq > 15)||(pstGnssTimeModelElementReq->ucGNSSToIdsReq < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSTIMEMODELELEMENTREQ_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    ucValue = pstGnssTimeModelElementReq->ucGNSSToIdsReq - 1;
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, ucValue);

    if(TRUE == pstGnssTimeModelElementReq->bdeltaTreq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }


    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssTimeModelListReq
 Description     : 编码LPP_GNSS_TIME_MODEL_LIST_REQ_STRU
 Input           :
 Asn             :
 GNSS-TimeModelListReq ::= SEQUENCE (SIZE(1..15)) OF GNSS-TimeModelElementReq

     GNSS-TimeModelElementReq ::= SEQUENCE {
         gnss-TO-IDsReq  INTEGER (1..15),
         deltaTreq       BOOLEAN,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssTimeModelListReq
(
    LPP_GNSS_TIME_MODEL_LIST_REQ_STRU                      *pstGnssTimeModelListReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;
    VOS_UINT8                                               ucCount         = 0;
    /*合法性检查*/
    if((pstGnssTimeModelListReq->ulGNSSTimeModelListReqCnt > 15)||(pstGnssTimeModelListReq->ulGNSSTimeModelListReqCnt < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSTIMEMODELLISTREQ_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*编码长度值*/
    ucCount = (VOS_UINT8)(pstGnssTimeModelListReq->ulGNSSTimeModelListReqCnt - 1);
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, ucCount);

    /*循环编码结构体*/
    for(ucCount = 0;ucCount < pstGnssTimeModelListReq->ulGNSSTimeModelListReqCnt;ucCount++)
    {
        usRslt = NAS_LPP_EncodeGnssTimeModelElementReq(&(pstGnssTimeModelListReq->astGNSSTimeModelListElementReq[ucCount]),
                                                          pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssDiffCorrectReq
 Description     : 编码LPP_GNSS_DIFF_CORRECT_REQ_STRU
 Input           :
 Asn             :
 GNSS-DifferentialCorrectionsReq ::=     SEQUENCE {
         dgnss-SignalsReq            GNSS-SignalIDs,
         dgnss-ValidityTimeReq       BOOLEAN,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssDiffCorrectReq
(
    LPP_GNSS_DIFF_CORRECT_REQ_STRU                         *pstGnssDiffCorrectReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码结构体内容*/
    NAS_LPP_EncodeGnssSignalIds(&(pstGnssDiffCorrectReq->stDGNSSSignalReq),  pusBitPos,  pucEncodeOutMsg);

    if(TRUE == pstGnssDiffCorrectReq->bDGNSSValidityTimeReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,  1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,  0);
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeSVID
 Description     : 编码LPP_SV_ID_STRU
 Input           :
 Asn             :
 SV-ID ::= SEQUENCE {
        satellite-id        INTEGER(0..63),
        ...
    }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSVID
(
    LPP_SV_ID_STRU                                         *pstSVID,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8           ucValue = 0;

    if(pstSVID->ucSatelliteId > 63)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SVID_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码结构体内容*/
    ucValue = pstSVID->ucSatelliteId;
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 6, ucValue);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeSatListRelatedDataListElement
 Description     : 编码LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU
 Input           :
 Asn             :
 SatListRelatedDataElement ::= SEQUENCE {
         svID                SV-ID,
         iod                 BIT STRING (SIZE(11)),
         clockModelID        INTEGER (1..8)          OPTIONAL,
         orbitModelID        INTEGER (1..8)          OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSatListRelatedDataListElement
(
    LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU              *pstSatListRelatedDataListElement,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;
    VOS_UINT8                                               ucValue         = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码OPTIONAL标志位*/
    if(NAS_LPP_SLCT == pstSatListRelatedDataListElement->bitOpClockModelId)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }


    if(NAS_LPP_SLCT == pstSatListRelatedDataListElement->bitOpOrbitModelId)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*编码SV-ID*/
    usRslt = NAS_LPP_EncodeSVID(&(pstSatListRelatedDataListElement->stSvId),
                                   pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*iod*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg,  pusBitPos, 11, pstSatListRelatedDataListElement->usIod);

    /*编码clockModelID*/
    if(NAS_LPP_SLCT == pstSatListRelatedDataListElement->bitOpClockModelId)
    {
        if((pstSatListRelatedDataListElement->ucClockModelId > 8)||(pstSatListRelatedDataListElement->ucClockModelId < 1))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_SATLISTRELATEDDATALISTELEMENT_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        ucValue = pstSatListRelatedDataListElement->ucClockModelId - 1;
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);
    }
    /*编码orbitModelID*/
    if(NAS_LPP_SLCT == pstSatListRelatedDataListElement->bitOpOrbitModelId)
    {
        if((pstSatListRelatedDataListElement->ucOrbitModelId> 8)||(pstSatListRelatedDataListElement->ucOrbitModelId< 1))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_SATLISTRELATEDDATALISTELEMENT_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        ucValue = pstSatListRelatedDataListElement->ucOrbitModelId - 1;
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeSatlistRelatedDataList
 Description     : 编码LPP_SATLIST_RELATED_DATALIST_STRU
 Input           :
 Asn             :
 SatListRelatedDataList ::= SEQUENCE (SIZE (1..64)) OF SatListRelatedDataElement

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSatlistRelatedDataList
(
    LPP_SATLIST_RELATED_DATALIST_STRU                      *pstSatlistRelatedDataList,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucCount         = 0;
    VOS_UINT16                                              usRslt          = 0;
    /*编码SEQUENCE OF 的值*/
    if((pstSatlistRelatedDataList->ulSatListRelatedDataListCnt < 1)||(pstSatlistRelatedDataList->ulSatListRelatedDataListCnt > LPP_MAX_SAT_LIST_RELATED_DATA_ELEMENT_LEN))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SATLISTRELATEDDATALIST_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    ucCount = (VOS_UINT8)(pstSatlistRelatedDataList->ulSatListRelatedDataListCnt - 1);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 6,  ucCount);

    for(ucCount = 0; ucCount < (pstSatlistRelatedDataList->ulSatListRelatedDataListCnt);ucCount++)
    {
        usRslt = NAS_LPP_EncodeSatListRelatedDataListElement(&(pstSatlistRelatedDataList->astSatListRelatedDataListElementArray[ucCount]),
                                                                pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeStoreNavListInfo
 Description     : 编码LPP_STORED_NAVLIST_STRU
 Input           :
 Asn             :
 StoredNavListInfo ::= SEQUENCE {
         gnss-WeekOrDay          INTEGER (0..4095),
         gnss-Toe                INTEGER (0..255),
         t-toeLimit              INTEGER (0..15),
         satListRelatedDataList  SatListRelatedDataList  OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeStoreNavListInfo
(
    LPP_STORED_NAVLIST_STRU                                *pstStoreNavListInfo,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16          usRslt = 0;

    /*编码扩展项标志位*/
    if((pstStoreNavListInfo->ucGNSSTToeLimit > 15) || (pstStoreNavListInfo->usGNSSWeekOrDay > 4095))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_STORENAVLISTINFO_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);
    /*编码OPTIONAL标志位*/
    if(NAS_LPP_SLCT == pstStoreNavListInfo->bitOpSatListREalatedDataList)
    {
        NAS_LPP_EncodeBitsLess8(  pucEncodeOutMsg,  pusBitPos,  1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(  pucEncodeOutMsg,  pusBitPos,  1, 0);
    }

    /*编码12个bit-gnss-WeekOrDay*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg, pusBitPos, 12, pstStoreNavListInfo->usGNSSWeekOrDay);

    /*编码gnss-Toe*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,  pstStoreNavListInfo->ucGNSSToe);

    /*t-toeLimit*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, pstStoreNavListInfo->ucGNSSTToeLimit);

    /*编码satListRelatedDataList*/
    if(NAS_LPP_SLCT == pstStoreNavListInfo->bitOpSatListREalatedDataList)
    {
        usRslt = NAS_LPP_EncodeSatlistRelatedDataList((LPP_SATLIST_RELATED_DATALIST_STRU*)&(pstStoreNavListInfo->stSatlistRelatedDataList),
                                                         pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeOrbitModelID
 Description     : 编码LPP_Orbit_MODEL_ID_STRU
 Input           :
 Asn             :
 orbitModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOrbitModelID
(
    LPP_ORBIT_MODEL_ID_STRU            *pstOrbitModelID,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucCount         = 0;
    VOS_UINT8                           ucValue         = 0;

    /*验证长度和值的合法性*/
    if((pstOrbitModelID->ucOrbitModelIDCount > 8)||(pstOrbitModelID->ucOrbitModelIDCount < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ORBITMODELID_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    for(ucCount = 0;ucCount < pstOrbitModelID->ucOrbitModelIDCount;ucCount++)
    {
        if((pstOrbitModelID->ucOrbitModelIDList[ucCount] > 8)||(pstOrbitModelID->ucOrbitModelIDList[ucCount] < 1))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_ORBITMODELID_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    /*编码长度值*/
    ucValue = pstOrbitModelID->ucOrbitModelIDCount - 1;
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);

    /*编码值*/
    for(ucCount = 0;ucCount < pstOrbitModelID->ucOrbitModelIDCount;ucCount++)
    {
        ucValue = pstOrbitModelID->ucOrbitModelIDList[ucCount] - 1;
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeClockModelID
 Description     : 编码LPP_CLOCK_MODEL_ID_STRU
 Input           :
 Asn             :
 clockModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeClockModelID
(
    LPP_CLOCK_MODEL_ID_STRU            *pstClockModelID,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucCount             = 0;
    VOS_UINT8                           ucValue             = 0;

    /*验证长度和值的合法性*/
    if((pstClockModelID->ucClockModelIDCount > 8)||(pstClockModelID->ucClockModelIDCount < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_CLOCKMODELID_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    for(ucCount = 0;ucCount < pstClockModelID->ucClockModelIDCount;ucCount++)
    {
        if((pstClockModelID->ucClockModelIDList[ucCount] > 8)||(pstClockModelID->ucClockModelIDList[ucCount] < 1))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_CLOCKMODELID_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    /*编码长度值*/
    ucValue = pstClockModelID->ucClockModelIDCount - 1;
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);

    /*编码值*/
    for(ucCount = 0;ucCount < pstClockModelID->ucClockModelIDCount;ucCount++)
    {
        ucValue = pstClockModelID->ucClockModelIDList[ucCount] - 1;
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeReqNavListInfo
 Description     : 编码LPP_REQ_NAVLIST_STRU
 Input           :
 Asn             :
 ReqNavListInfo ::=  SEQUENCE {
         svReqList               BIT STRING (SIZE (64)),
         clockModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)      OPTIONAL,
         orbitModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)      OPTIONAL,
         addNavparamReq          BOOLEAN             OPTIONAL,   -- Cond orbitModelID-2
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeReqNavListInfo
(
    LPP_REQ_NAVLIST_STRU               *pstReqNavListInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt             = 0;
    VOS_UINT8                           ucCount            = 0;
    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码OPTIONAL项标志位*/
    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpClockModelIDPrefList)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpOrbitModelIDPrefList)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpAddNavparamReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*编码结构体内容*/
    /*svReqList共64个bit*/
    for(ucCount = 0; ucCount < 8;ucCount++)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 8, pstReqNavListInfo->aucSvReqList[ucCount]);
    }
    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpClockModelIDPrefList)
    {
        usRslt = NAS_LPP_EncodeClockModelID( &(pstReqNavListInfo->stClockModelID),  pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpOrbitModelIDPrefList)
    {
        usRslt = NAS_LPP_EncodeOrbitModelID( &(pstReqNavListInfo->stOrbitModelID),  pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpAddNavparamReq)
    {
        if(TRUE == pstReqNavListInfo->bAddNavparamReq)
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
        }
        else
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssNavModelReq
 Description     : 编码LPP_GNSS_NAVIGATION_MODEL_REQ_STRU
 Input           :
 Asn             :
 GNSS-NavigationModelReq ::=     CHOICE {
         storedNavList       StoredNavListInfo,
         reqNavList          ReqNavListInfo,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssNavModelReq
(
    LPP_GNSS_NAVIGATION_MODEL_REQ_STRU *pstGnssNavModelReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码结构体扩展项标志位*/
    if(pstGnssNavModelReq->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSNAVMODELREQ_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码结构体内容*/
    /*编码CHOICE项序号*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstGnssNavModelReq->ulChoice));
    switch(pstGnssNavModelReq->ulChoice)
    {
        case LPP_STORED_NAVLIST_CHOSEN:
            usRslt = NAS_LPP_EncodeStoreNavListInfo(&(pstGnssNavModelReq->u.stStoredNavList),
                                                       pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return  usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeReqNavListInfo(&(pstGnssNavModelReq->u.stReqNavList),
                                                     pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return  usRslt;
            }
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssDataBitReqSatElement
 Description     : 编码LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU
 Input           :
 Asn             :
 GNSS-DataBitsReqSatElement ::= SEQUENCE {
         svID                SV-ID,s
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssDataBitReqSatElement
(
    LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU                 *pstGnssDataBitReqSatElement,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16          usRslt = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码结构体内容*/
    usRslt = NAS_LPP_EncodeSVID(&(pstGnssDataBitReqSatElement->stSvId),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssDataBitReqSatList
 Description     : 编码LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU
 Input           :
 Asn             :
 GNSS-DataBitsReqSatList ::= SEQUENCE (SIZE(1..64)) OF GNSS-DataBitsReqSatElement

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssDataBitReqSatList
(
    LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU                    *pstGnssDataBitReqSatList,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucCount     = 0;
    VOS_UINT16                                              usRslt      = 0;

    /* 检验长度合法性，并编码长度值*/
    if((pstGnssDataBitReqSatList->ulGNSSDataBitsReqListCnt >LPP_MAX_GNSS_DATA_BITS_REQ_SAT_LIST_LEN)||(pstGnssDataBitReqSatList->ulGNSSDataBitsReqListCnt < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSDATABITREQSATLIST_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, pstGnssDataBitReqSatList->ulGNSSDataBitsReqListCnt);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    ucCount = (VOS_UINT8)(pstGnssDataBitReqSatList->ulGNSSDataBitsReqListCnt - 1);
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 6, ucCount);

    /*编码结构体内容*/
    for(ucCount = 0;ucCount <pstGnssDataBitReqSatList->ulGNSSDataBitsReqListCnt; ucCount++)
    {
        usRslt = NAS_LPP_EncodeGnssDataBitReqSatElement(&(pstGnssDataBitReqSatList->astGNSSDataBitReqSatList[ucCount]),
                                                           pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssRealTimeIntReq
 Description     : 编码LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU
 Input           :
 Asn             :
 协议为空

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssRealTimeIntReq
(
    LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU                  *pstGnssRealTimeIntReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssDataBitAssistReq
 Description     : 编码LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU
 Input           :
 Asn             :
 GNSS-DataBitAssistanceReq ::=   SEQUENCE {
         gnss-TOD-Req        INTEGER (0..3599),
         gnss-TOD-FracReq    INTEGER (0..999)        OPTIONAL,
         dataBitInterval     INTEGER (0..15),
         gnss-SignalType     GNSS-SignalIDs,
         gnss-DataBitsReq    GNSS-DataBitsReqSatList OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssDataBitAssistReq
(
    LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU                      *pstGnssDataBitAssistReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    if((pstGnssDataBitAssistReq->ulGNSSTodReq > 3599) ||(pstGnssDataBitAssistReq->usGNSSTodFracReq > 999)||(pstGnssDataBitAssistReq->usDataBitInterval > 15))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSDATABITASSISTREQ_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);


    /*编码OPTIONAL项标志位*/
    if(NAS_LPP_SLCT == pstGnssDataBitAssistReq->bitOpGNSSTodFracREq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }
    if(NAS_LPP_SLCT == pstGnssDataBitAssistReq->bitOpGNSSDataBitsReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*编码结构体内容*/
    /*GNSS-tod-req*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg,  pusBitPos, 12, pstGnssDataBitAssistReq->ulGNSSTodReq);

    /*GNSS-TOD-FRACrEQ*/
    if(NAS_LPP_SLCT == pstGnssDataBitAssistReq->bitOpGNSSTodFracREq)
    {
        NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg,  pusBitPos, 10, pstGnssDataBitAssistReq->usGNSSTodFracReq);
    }

    /*dataBitInterval*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, (VOS_UINT8)(pstGnssDataBitAssistReq->usDataBitInterval));

    /*gnss-SignalType*/
    NAS_LPP_EncodeGnssSignalIds( &(pstGnssDataBitAssistReq->stGNSSSignalType), pusBitPos, pucEncodeOutMsg);

    /*gnss-DataBitsReq*/
    if(NAS_LPP_SLCT == pstGnssDataBitAssistReq->bitOpGNSSDataBitsReq)
    {
        usRslt = NAS_LPP_EncodeGnssDataBitReqSatList((LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU*)&(pstGnssDataBitAssistReq->stGNSSDataBitsReqSatList),
                                                        pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssSignalID
 Description     : 编码LPP_GNSS_SIGNAL_ID_STRU
 Input           :
 Asn             :
 GNSS-SignalID   ::= SEQUENCE {
         gnss-SignalID       INTEGER (0 .. 7),
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssSignalID
(
    LPP_GNSS_SIGNAL_ID_STRU                                *pstGnssSignalID,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    if(pstGnssSignalID->ucGNSSSignalId > 7)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSSIGNALID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, pstGnssSignalID->ucGNSSSignalId);



    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssAcqAssistReq
 Description     : 编码LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU
 Input           :
 Asn             :
 GNSS-AcquisitionAssistanceReq ::=   SEQUENCE {
         gnss-SignalID-Req       GNSS-SignalID,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssAcqAssistReq
(
    LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU  *pstGnssAcqAssistReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码结构体内容*/
    usRslt = NAS_LPP_EncodeGnssSignalID(&(pstGnssAcqAssistReq->stGNSSSignalIdReq),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssAlmanacReq
 Description     : 编码LPP_GNSS_ALMANAC_REQ_STRU
 Input           :
 Asn             :
 GNSS-AlmanacReq ::= SEQUENCE {
         modelID             INTEGER(1..8)   OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssAlmanacReq
(
    LPP_GNSS_ALMANAC_REQ_STRU          *pstGnssAlmanacReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8           ucTempValue = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    if ( NAS_LPP_SLCT == pstGnssAlmanacReq->bitOpModelId )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if (NAS_LPP_SLCT == pstGnssAlmanacReq->bitOpModelId)
    {
        if ( (pstGnssAlmanacReq->ucModelId < 1) || (pstGnssAlmanacReq->ucModelId > 8) )
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSALMANACREQ_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }

        ucTempValue = pstGnssAlmanacReq->ucModelId - 1;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 3, ucTempValue);
    }
    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssUTCModelReq
 Description     : 编码LPP_GNSS_UTC_MODEL_REQ_STRU
 Input           :
 Asn             :
 GNSS-UTC-ModelReq ::=   SEQUENCE {
         modelID             INTEGER(1..8)   OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssUTCModelReq
(
    LPP_GNSS_UTC_MODEL_REQ_STRU        *pstGnssUTCModelReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucTempValue         = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    if ( NAS_LPP_SLCT == pstGnssUTCModelReq->bitOpModelId )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if (NAS_LPP_SLCT == pstGnssUTCModelReq->bitOpModelId)
    {
        if ( (pstGnssUTCModelReq->ucModelId < 1) || (pstGnssUTCModelReq->ucModelId > 8) )
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSUTCMODELREQ_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }

        ucTempValue = pstGnssUTCModelReq->ucModelId - 1;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 3, ucTempValue);
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssAuxInfoReq
 Description     : 编码LPP_GNSS_AUX_INFO_REQ_STRU
 Input           :
 Asn             :
 协议为空

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssAuxInfoReq
(
    LPP_GNSS_AUX_INFO_REQ_STRU         *pstGnssAuxInfoReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssGenAssisDataReqElement
 Description     : 编码LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU
 Input           :
 Asn             :
 GNSS-GenericAssistDataReqElement ::= SEQUENCE {
         gnss-ID                         GNSS-ID,
         sbas-ID                         SBAS-ID                         OPTIONAL, -- Cond GNSS-ID-SBAS
         gnss-TimeModelsReq              GNSS-TimeModelListReq           OPTIONAL, -- Cond TimeModReq
         gnss-DifferentialCorrectionsReq GNSS-DifferentialCorrectionsReq OPTIONAL, -- Cond DGNSS-Req
         gnss-NavigationModelReq         GNSS-NavigationModelReq         OPTIONAL, -- Cond NavModReq
         gnss-RealTimeIntegrityReq       GNSS-RealTimeIntegrityReq       OPTIONAL, -- Cond RTIReq
         gnss-DataBitAssistanceReq       GNSS-DataBitAssistanceReq       OPTIONAL, -- Cond DataBitsReq
         gnss-AcquisitionAssistanceReq   GNSS-AcquisitionAssistanceReq   OPTIONAL, -- Cond AcquAssistReq
         gnss-AlmanacReq                 GNSS-AlmanacReq                 OPTIONAL, -- Cond AlmanacReq
         gnss-UTCModelReq                GNSS-UTC-ModelReq               OPTIONAL, -- Cond UTCModReq
         gnss-AuxiliaryInformationReq    GNSS-AuxiliaryInformationReq    OPTIONAL, -- Cond AuxInfoReq
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssGenAssisDataReqElement
(
    LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU          *pstGnssGenAssisDataReqElement,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;
    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*编码OPTIONAL项标志位*/
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpSbasId)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSTimeModelIsReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSDiffCorrectionReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSNavigationModelReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSRealTimeIntegrityReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSDataBitAssitReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAcqAssitReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAlmanacReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSUtcModelReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAuxInfoReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*编码GNSS-ID*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstGnssGenAssisDataReqElement->stGNSSId),
                                     pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return  usRslt;
    }
    /*编码SBAS-ID*/
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpSbasId)
    {
        usRslt = NAS_LPP_EncodeSbasId(&(pstGnssGenAssisDataReqElement->stSbasId),
                                         pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    /*编码GNSS_TimeModelListReq*/
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSTimeModelIsReq)
    {
        usRslt = NAS_LPP_EncodeGnssTimeModelListReq(&(pstGnssGenAssisDataReqElement->stGNSSTimeModelsReq),
                                                       pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSDiffCorrectionReq)
    {
        usRslt = NAS_LPP_EncodeGnssDiffCorrectReq(&(pstGnssGenAssisDataReqElement->stGNSSDiffCorrectReq),
                                                     pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSNavigationModelReq)
    {
        usRslt = NAS_LPP_EncodeGnssNavModelReq(&(pstGnssGenAssisDataReqElement->stGNSSNavigationModelReq),
                                                  pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSRealTimeIntegrityReq)
    {
        usRslt = NAS_LPP_EncodeGnssRealTimeIntReq(&(pstGnssGenAssisDataReqElement->stGNSSRealTimeIntergrityReq),
                                                     pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSDataBitAssitReq)
    {
        usRslt = NAS_LPP_EncodeGnssDataBitAssistReq(&(pstGnssGenAssisDataReqElement->stGNSSDataBitAssistanceReq),
                                                       pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAcqAssitReq)
    {
        usRslt = NAS_LPP_EncodeGnssAcqAssistReq(&(pstGnssGenAssisDataReqElement->stGNSSAcquisitAssitReq),pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAlmanacReq)
    {
        usRslt = NAS_LPP_EncodeGnssAlmanacReq(&(pstGnssGenAssisDataReqElement->stGNSSAlmanacReq),
                                                 pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSUtcModelReq)
    {
        usRslt = NAS_LPP_EncodeGnssUTCModelReq(&(pstGnssGenAssisDataReqElement->stGNSSUtcModelReq),
                                                  pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAuxInfoReq)
    {
        usRslt = NAS_LPP_EncodeGnssAuxInfoReq(&(pstGnssGenAssisDataReqElement->stGNSSAuxInfoReq),
                                                 pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGenReqAssistData
 Description     : 编码LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU
 Input           :
 Asn             :
 GNSS-GenericAssistDataReq ::= SEQUENCE (SIZE (1..16)) OF GNSS-GenericAssistDataReqElement

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssGenReqAssistData
(
    LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU                  *pstGenReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;
    VOS_UINT8                                               ucCount         = 0;

    /*检验长度合法性，如果合法编码sequence of 长度*/
    if ((pstGenReqAssistData->ulGNSSGenericAssistDataReqCnt > LPP_MAX_GEN_ASSIT_DATA_ELEMENT_LEN) ||
                        (pstGenReqAssistData->ulGNSSGenericAssistDataReqCnt < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSGENREQASSISTDATA_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    ucCount = (VOS_UINT8)(pstGenReqAssistData->ulGNSSGenericAssistDataReqCnt - 1);
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, ucCount);

    /*循环编码结构体*/
    for(ucCount = 0;ucCount < pstGenReqAssistData->ulGNSSGenericAssistDataReqCnt;ucCount++)
    {
        usRslt = NAS_LPP_EncodeGnssGenAssisDataReqElement(&(pstGenReqAssistData->astGNSSGenericAssistDataReqElement[ucCount]),
                                                             pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC !=usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


/*****************************************************************************
 Function Name   :NAS_LPP_EncodeAGNSSReqAssistData
 Description     : 编码LPP_AGNSS_REQ_ASSIST_DATA_STRU
 Input           :
 Asn             :
 A-GNSS-RequestAssistanceData ::= SEQUENCE {
         gnss-CommonAssistDataReq        GNSS-CommonAssistDataReq        OPTIONAL, -- Cond CommonADReq
         gnss-GenericAssistDataReq       GNSS-GenericAssistDataReq       OPTIONAL, -- Cond GenADReq
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAGNSSReqAssistData
(
    LPP_AGNSS_REQ_ASSIST_DATA_STRU     *pstAGNSSReqAssistData,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{

    VOS_UINT16                          usRslt             = 0;

    /* 编码扩展标志位*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码OPTIONAL标志位*/
    if ( NAS_LPP_SLCT == pstAGNSSReqAssistData->bitOpGNSSCommAssistData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    if ( NAS_LPP_SLCT == pstAGNSSReqAssistData->bitOpGNSSGenericAssistData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*编码存在的OPTIONAL项*/
    if ( NAS_LPP_SLCT == pstAGNSSReqAssistData->bitOpGNSSCommAssistData )
    {
        usRslt = NAS_LPP_EncodeGnssComReqAssistData(&(pstAGNSSReqAssistData->stGNSSCommonAssistDataReq),
                                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    if ( NAS_LPP_SLCT == pstAGNSSReqAssistData->bitOpGNSSGenericAssistData )
    {
        usRslt = NAS_LPP_EncodeGnssGenReqAssistData(&(pstAGNSSReqAssistData->stGNSSGenericAssistDataReq),
                                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeCellIdentity
 Description     : 编码BIT STRING
 Input           :
 Asn             :
         cellidentity    BIT STRING (SIZE (28))
     }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCellIdentity
(
    VOS_UINT32                         *pulCellIdentity,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码cellidentity*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg, pusBitPos, 28, *pulCellIdentity);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodePrimaryCellID
 Description     : 编码LPP_PLMN_IDENTITY_STRU
 Input           :
 Asn             :
 plmn-Identity       SEQUENCE {
                                 mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                                 mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                             },

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodePrimaryCellID
(
    LPP_PLMN_IDENTITY_STRU             *pstPlmnIdentity,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucCount            = 0;

    /*MCC合法性检查*/
    if ( (pstPlmnIdentity->aucMcc[0] > 9) || (pstPlmnIdentity->aucMcc[1] > 9) ||
                                        (pstPlmnIdentity->aucMcc[2] > 9))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLID_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*MNC数据合法性检查*/
    if ((pstPlmnIdentity->aucMnc[0] > 9) || (pstPlmnIdentity->aucMnc[1] > 9) ||
                                            (pstPlmnIdentity->aucMnc[2] > 9))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLID_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    if ( (pstPlmnIdentity->ucMncNum < 2) || (pstPlmnIdentity->ucMncNum > 3))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLID_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*编码MCC,integer值0-9，只需要编码4bit共计3个*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, pstPlmnIdentity->aucMcc[0]);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, pstPlmnIdentity->aucMcc[1]);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, pstPlmnIdentity->aucMcc[2]);

    /*编码MNC的个数计数值*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, pstPlmnIdentity->ucMncNum);

    /*编码MNC,integer值0-9，只需要编码4bit共计2-3个*/
    for(ucCount = 0; ucCount < (pstPlmnIdentity->ucMncNum) ;ucCount++)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 4, pstPlmnIdentity->aucMnc[ucCount]);
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeECGI
 Description     : 编码LPP_ECGI_STRU
 Input           :
 Asn             :
     ECGI ::= SEQUENCE {
        mcc             SEQUENCE (SIZE (3))     OF INTEGER (0..9),
        mnc             SEQUENCE (SIZE (2..3))  OF INTEGER (0..9),
        cellidentity    BIT STRING (SIZE (28))

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeECGI
(
    LPP_ECGI_STRU                      *pstECGI,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt             = 0;

    /*编码PLMN_IDENTIFY*/
    usRslt = NAS_LPP_EncodePrimaryCellID(&(pstECGI->stPlmnIdentity), pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码cellidentity TYPE:BIT STRING*/
    usRslt = NAS_LPP_EncodeCellIdentity(&(pstECGI->ulCellIdentity), pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeCommIEsAssistData
 Description     : 编码LPP_COMMON_IES_REQ_ASSIST_DATA_STRU
 Input           :
 Asn             :
 CommonIEsRequestAssistanceData ::= SEQUENCE {
         primaryCellID       ECGI        OPTIONAL,   -- Cond EUTRA
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCommIEsAssistData
(
    LPP_COMMON_IES_REQ_ASSIST_DATA_STRU                    *pstCommIEsAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*如果OPNTIONAL项存在，编码OPTIONAL项*/
    if(NAS_LPP_NO_SLCT == pstCommIEsAssistData->bitOpPrimaryCellID)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
        return NAS_LPP_ENCODE_SUCC;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    usRslt = NAS_LPP_EncodeECGI(&(pstCommIEsAssistData->stPrimaryCellID),  pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeReqAssistDataR9IEs
 Description     : 编码LPP_REQUEST_ASSIST_DATA_R9_IES_STRU
 Input           :
 Asn             :
 RequestAssistanceData-r9-IEs ::= SEQUENCE {
         commonIEsRequestAssistanceData      CommonIEsRequestAssistanceData      OPTIONAL,
         a-gnss-RequestAssistanceData        A-GNSS-RequestAssistanceData        OPTIONAL,
         otdoa-RequestAssistanceData         OTDOA-RequestAssistanceData         OPTIONAL,
         epdu-RequestAssistanceData          EPDU-Sequence                       OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeReqAssistDataR9IEs
(
    LPP_REQUEST_ASSIST_DATA_R9_IES_STRU                    *pstReqAssistDataR9IEs,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;


    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*编码OPTIONAL项bitOpCommonIEsRequestAssitData标志位*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpCommonIEsRequestAssitData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*编码OPTIONAL项bitOpAGNSSRequestAssistData标志位*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpAGNSSRequestAssistData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 0);
    }
    /*编码OPTIONAL项bitOpOTDOARequestAssistData标志位*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpOTDOARequestAssistData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 0);
    }
    /*编码OPTIONAL项bitOpEPDUSequence标志位*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpEPDUSequence)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*编码结构体内容*/
    /*如果可选项存在，则编码*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpCommonIEsRequestAssitData )
    {
        usRslt = NAS_LPP_EncodeCommIEsAssistData(&(pstReqAssistDataR9IEs->stCommonIEsRequestAssistanceData),
                                                    pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpAGNSSRequestAssistData)
    {
        usRslt = NAS_LPP_EncodeAGNSSReqAssistData(&(pstReqAssistDataR9IEs->stAGNSSRequestAssistanceData),
                                                     pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpOTDOARequestAssistData)
    {
        usRslt = NAS_LPP_EncodeOTDOAReqAssistData(&(pstReqAssistDataR9IEs->stOTDOARequestAssistanceData),
                                                     pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpEPDUSequence)
    {
        usRslt = NAS_LPP_EncodeEpduReqAssistData(&(pstReqAssistDataR9IEs->stEPDURequestAssistanceData),
                                                    pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}



/*****************************************************************************
 Function Name   : NAS_LPP_EncodeExtRequestAssistData
 Description     : 编码LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU
 Input           :
 Asn             :
 c1                      CHOICE {
                 requestAssistanceData-r9    RequestAssistanceData-r9-IEs,
                 spare3 NULL, spare2 NULL, spare1 NULL
             },

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeExtRequestAssistData
(
    LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU                 *pstExtReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*编码choice项*/
    /*四个choice项，所以用两个bit表示*/
    if(pstExtReqAssistData->ulChoice > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EXTREQUESTASSISTDATA_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstExtReqAssistData->ulChoice));

    switch(pstExtReqAssistData->ulChoice)
    {
        case LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_R9_CHOSEN:
            usRslt = NAS_LPP_EncodeReqAssistDataR9IEs(&(pstExtReqAssistData->u.stRequestAssitDataR9),
                                                         pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }

            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeRequestAssistData
 Description     : 编码LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU
 Input           : pstProvideCapabilty      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeRequestAssistData
(
    LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU                   *pstReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*编码choice项*/
    /*两个choice项，所以用一个bit表示即可*/
    if ( pstReqAssistData->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_REQUESTASSISTDATA_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstReqAssistData->ulChoice));

    switch(pstReqAssistData->ulChoice)
    {
        case LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN:
            usRslt = NAS_LPP_EncodeExtRequestAssistData(&(pstReqAssistData->u.stC1),
                                                           pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_CRITI_EXT_FUTURE_REQUEST_ASSIST_DATA_CHOSEN:
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEllipsoidPoint
 Description     : 编码pstEllipsoidPoint
 Input           : pstEllipsoidPoint        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         Ellipsoid-Point ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEllipsoidPoint
(
    LPP_ELLIPSOID_POINT_STRU           *pstEllipsoidPoint,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstEllipsoidPoint->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23,
                                  pstEllipsoidPoint->ulDegreeLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidPoint->lDegreesLongitude + 8388608));

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEllipsoidPointWithUncertaintyCircle
 Description     : 编码pstEllipsoidPoint
 Input           : pstEllipsoidPoint        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         Ellipsoid-PointWithUncertaintyCircle ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
             uncertainty                 INTEGER (0..127)
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEllipsoidPointWithUncertaintyCircle
(
    LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU       *pstEllipsoidPointWithCircle,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipsoidPointWithCircle->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstEllipsoidPointWithCircle->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24, (VOS_UINT32)(pstEllipsoidPointWithCircle->lDegreeLongitude + 8388608));

    /*编码uncertainty*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstEllipsoidPointWithCircle->ulUncretainty));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEllipsoidPointWithUncertaintyEllipse
 Description     : 编码EllipsoidPointWithUncertaintyEllipse
 Input           : pstEllipsoidPointWithUncertaintyEllipse        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         EllipsoidPointWithUncertaintyEllipse ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
             uncertaintySemiMajor        INTEGER (0..127),
             uncertaintySemiMinor        INTEGER (0..127),
             orientationMajorAxis        INTEGER (0..179),
             confidence                  INTEGER (0..100)
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEllipsoidPointWithUncertaintyEllipse
(
    LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU      *pstEllipsoidPointWithUncertaintyEllipse,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg)
{
    LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU      *pstTempStru = pstEllipsoidPointWithUncertaintyEllipse;

    if ( pstTempStru->enLatitudeSign > 1 )
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstTempStru->ulDegreesLatitude > 8388607) || (pstTempStru->ucUncertaintySemiMajor > 127) ||
         (pstTempStru->ucUncertaintySemiMinor > 127) || (pstTempStru->ucOrientationMajorAxis >179)
       ||(pstTempStru->ucConfidence >100)||((pstTempStru->lDegreesLongitude >8388607)
       ||(pstTempStru->lDegreesLongitude < -8388608)))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1,
                             (VOS_UINT8)(pstEllipsoidPointWithUncertaintyEllipse->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23,
                                  pstEllipsoidPointWithUncertaintyEllipse->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidPointWithUncertaintyEllipse->lDegreesLongitude + 8388608));

    /*编码uncertaintySemiMajor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7,
                              pstEllipsoidPointWithUncertaintyEllipse->ucUncertaintySemiMajor);

    /*编码uncertaintySemiMinor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7,
                              pstEllipsoidPointWithUncertaintyEllipse->ucUncertaintySemiMinor);

    /*编码orientationMajorAxis*/
    if(pstEllipsoidPointWithUncertaintyEllipse->ucUncertaintySemiMinor > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipsoidPointWithUncertaintyEllipse->ucOrientationMajorAxis);

    /*编码confidence*/
    if(pstEllipsoidPointWithUncertaintyEllipse->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7,
                              pstEllipsoidPointWithUncertaintyEllipse->ucConfidence);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodePolygonPoints
 Description     : 编码PolygonPoints
 Input           : pstPolygonPoints         需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         Polygon ::= SEQUENCE (SIZE (3..15)) OF PolygonPoints

         PolygonPoints ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodePolygonPoints
(
    LPP_POLYGON_POINTS_STRU            *pstPolygonPoints,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    if(pstPolygonPoints->enLatitudeSign >1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_POLYGONPOINTS_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstPolygonPoints->lDegreesLatitude > 8388607)
       ||(pstPolygonPoints->lDegreesLatitude < -8388608)
       ||(pstPolygonPoints->ulDegreesLatitude > 8388607))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_POLYGONPOINTS_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstPolygonPoints->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstPolygonPoints->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24, (VOS_UINT32)(pstPolygonPoints->lDegreesLatitude + 8388608));

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodePolygon
 Description     : 编码Polygon
 Input           : pstPolygon               需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         Polygon ::= SEQUENCE (SIZE (3..15)) OF PolygonPoints

         PolygonPoints ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodePolygon
(
    LPP_POLYGON_STRU                   *pstPolygon,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulLoop          = 0;

    /*编码结构体计数值*/
    if ( ((pstPolygon->ulPolygonCnt) < 3) || ((pstPolygon->ulPolygonCnt) > 15))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_POLYGON_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 4, (VOS_UINT8)((pstPolygon->ulPolygonCnt) - 3));

    /*编码结构体实体*/
    for(ulLoop = 0; ulLoop < pstPolygon->ulPolygonCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodePolygonPoints(&(pstPolygon->astPolygonArray[ulLoop]),
                                                pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEllipsoidPointWithaltitude
 Description     : 编码EllipsoidPointWithAltitude
 Input           : pstEllipsoidPointWithAltitude  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         EllipsoidPointWithAltitude ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
             altitudeDirection           ENUMERATED {height, depth},
             altitude                    INTEGER (0..32767)              -- 15 bit field
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEllipsoidPointWithaltitude
(
    LPP_ELLIPSOID_POINT_WITH_ALTITUDE_STRU                 *pstEllipsoidPointWithAltitude,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    if((pstEllipsoidPointWithAltitude->enLatitudeSign >1)||(pstEllipsoidPointWithAltitude->enAltitudeDirection > 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstEllipsoidPointWithAltitude->lDegreesLatitude > 8388607)
       ||(pstEllipsoidPointWithAltitude->lDegreesLatitude < -8388608)
       ||(pstEllipsoidPointWithAltitude->ulDegreesLatitude > 8388607)
       ||(pstEllipsoidPointWithAltitude->usAltitude > 32767))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_INTEGER, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstEllipsoidPointWithAltitude->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23,
                                  pstEllipsoidPointWithAltitude->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidPointWithAltitude->lDegreesLatitude + 8388608));

    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstEllipsoidPointWithAltitude->enAltitudeDirection));

    /*编码tltitude*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg,  pusBitPos,  15,
                                   pstEllipsoidPointWithAltitude->usAltitude);

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEllipsoidPointWithAltitudeAndEllipoid
 Description     : 编码EllipsoidPointWithAltitudeAndUncertaintyEllipsoid
 Input           : pstEllipPointAndUncertEllip  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         EllipsoidPointWithAltitudeAndUncertaintyEllipsoid ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
             altitudeDirection           ENUMERATED {height, depth},
             altitude                    INTEGER (0..32767),             -- 15 bit field
             uncertaintySemiMajor        INTEGER (0..127),
             uncertaintySemiMinor        INTEGER (0..127),
             orientationMajorAxis        INTEGER (0..179),
             uncertaintyAltitude         INTEGER (0..127),
             confidence                  INTEGER (0..100)
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEllipsoidPointWithAltitudeAndEllipoid
(
    LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU    *pstEllipPointAndUncertEllip,
    VOS_UINT16                                                          *pusBitPos,
    VOS_UINT8                                                           *pucEncodeOutMsg
)
{
    LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU    *pstTempStru = pstEllipPointAndUncertEllip;
    if((pstTempStru->enAltitudeDirection > 1)||(pstTempStru->enLatitudeSign > 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstTempStru->ucConfidence > 100)
       ||(pstTempStru->ucOrientationMajorAxis > 179)
       ||(pstTempStru->ucUncertaintyAltitude > 127)
       ||(pstTempStru->ucUncertaintySemiMajor > 127)
       ||(pstTempStru->ucUncertaintySemiMinor > 127)
       ||(pstEllipPointAndUncertEllip->lDegreesLongtitude > 8388607)
       ||(pstEllipPointAndUncertEllip->lDegreesLongtitude < -8388608)
       ||(pstEllipPointAndUncertEllip->usAltitude > 32767))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipPointAndUncertEllip->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstEllipPointAndUncertEllip->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24, (VOS_UINT32)(pstEllipPointAndUncertEllip->lDegreesLongtitude + 8388608));

    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipPointAndUncertEllip->enAltitudeDirection));

    /*编码tltitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 15, pstEllipPointAndUncertEllip->usAltitude);

    /*编码ucUncertaintySemiMajor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstEllipPointAndUncertEllip->ucUncertaintySemiMajor));

    /*编码uncertaintySemiMinor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstEllipPointAndUncertEllip->ucUncertaintySemiMinor));

    /*编码orientationMajorAxis*/
    if ( pstEllipPointAndUncertEllip->ucUncertaintySemiMinor > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipPointAndUncertEllip->ucOrientationMajorAxis);

    /*编码uncertaintyAltitude*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipPointAndUncertEllip->ucUncertaintyAltitude);

    /*编码confidence*/
    if ( pstEllipPointAndUncertEllip->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipPointAndUncertEllip->ucConfidence);

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEllipsoidArc
 Description     : 编码EllipsoidArc
 Input           : pstEllipsoidArc          需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         EllipsoidArc ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
             innerRadius                 INTEGER (0..65535),             -- 16 bit field,
             uncertaintyRadius           INTEGER (0..127),
             offsetAngle                 INTEGER (0..179),
             includedAngle               INTEGER (0..179),
             confidence                  INTEGER (0..100)
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEllipsoidArc
(
    LPP_ELLIPSOIDARC_STRU              *pstEllipsoidArc,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    if(pstEllipsoidArc->enLatitudeSign > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if((pstEllipsoidArc->lDegreesLongtitude > 8388607)
     || (pstEllipsoidArc->lDegreesLongtitude < -8388608)
     || (pstEllipsoidArc->ucConfidence > 100)
     || (pstEllipsoidArc->ucIncludedAngle > 179)
     || (pstEllipsoidArc->ucOffsetAngle > 179)
     || (pstEllipsoidArc->ucUncertaintyRadius > 127)
     || (pstEllipsoidArc->ulDegreesLatitude > 8388607)
     || (pstEllipsoidArc->ulInnerRadius > 65535))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipsoidArc->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstEllipsoidArc->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidArc->lDegreesLongtitude + 8388608));

    /*编码innerRadius*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg,  pusBitPos, 16, pstEllipsoidArc->ulInnerRadius);

    /*编码uncertaintyRadius*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipsoidArc->ucUncertaintyRadius);

    /*编码offsetAngle*/
    if(pstEllipsoidArc->ucOffsetAngle > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipsoidArc->ucOffsetAngle);

    /*编码includedAngle*/
    if(pstEllipsoidArc->ucIncludedAngle > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipsoidArc->ucIncludedAngle);

    /*编码confidence*/
    if(pstEllipsoidArc->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipsoidArc->ucConfidence);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLoctionEstimate
 Description     : 编码LocationCoordinates
 Input           : pstLocationCoordinate    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         LocationCoordinates ::= CHOICE {
             ellipsoidPoint                              Ellipsoid-Point,
             ellipsoidPointWithUncertaintyCircle         Ellipsoid-PointWithUncertaintyCircle,
             ellipsoidPointWithUncertaintyEllipse        EllipsoidPointWithUncertaintyEllipse,
             polygon                                     Polygon,
             ellipsoidPointWithAltitude                  EllipsoidPointWithAltitude,
             ellipsoidPointWithAltitudeAndUncertaintyEllipsoid
                                                         EllipsoidPointWithAltitudeAndUncertaintyEllipsoid,
             ellipsoidArc                                EllipsoidArc,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLoctionEstimate
(
    LPP_LOCATION_COORDINATE_STRU       *pstLocationCoordinate,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*编码choice项*/
    if(pstLocationCoordinate->ulChoice > 6)
    {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_LOCTIONESTIMATE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, (VOS_UINT8)(pstLocationCoordinate->ulChoice));

    switch(pstLocationCoordinate->ulChoice)
    {
        case LOC_COM_ELLIPSOID_POINT_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPoint(&(pstLocationCoordinate->u.stEllipsoidPoint),
                                                     pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPointWithUncertaintyCircle(&(pstLocationCoordinate->u.stEllipsoidPointWithUncertaintyCircle),
                                                                          pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPointWithUncertaintyEllipse(&(pstLocationCoordinate->u.stEllipsoidPointWithUncertaintyEllipse),
                                                                           pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LOC_COM_POLYGON_CHOSEN:
            usRslt = NAS_LPP_EncodePolygon(&(pstLocationCoordinate->u.stPolygon), pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;


        case LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPointWithaltitude(&(pstLocationCoordinate->u.stEllipsoidPointWithAltitude),
                                                                 pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPointWithAltitudeAndEllipoid(&(pstLocationCoordinate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid),
                                                                            pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeEllipsoidArc(&(pstLocationCoordinate->u.stEllipsoidArc),
                                                   pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeHorizontalVelcoctiy
 Description     : 编码HorizontalVelocity
 Input           : pstHorizontalVelcoctiy   需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         HorizontalVelocity ::= SEQUENCE {
             bearing                     INTEGER(0..359),
             horizontalSpeed             INTEGER(0..2047)
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeHorizontalVelcoctiy
(
    LPP_HORIZONTAL_VELCOCTIY_STRU      *pstHorizontalVelcoctiy,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码bearing*/
    if(((pstHorizontalVelcoctiy->usBearing) > 359)||(pstHorizontalVelcoctiy->usHorizontalSpeed > 2047))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALVELCOCTIY_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstHorizontalVelcoctiy->usBearing);

    /*编码horizontalSpeed*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 11, pstHorizontalVelcoctiy->usHorizontalSpeed);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeHorizontalWithVerticalVelocity
 Description     : 编码HorizontalWithVerticalVelocity
 Input           : pstHorizontalWithVelocity   需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         HorizontalWithVerticalVelocity ::= SEQUENCE {
             bearing                     INTEGER(0..359),
             horizontalSpeed             INTEGER(0..2047),
             verticalDirection           ENUMERATED{upward, downward},
             verticalSpeed               INTEGER(0..255)
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeHorizontalWithVerticalVelocity
(
    LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU             *pstHorizontalWithVelocity,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码bearing*/
    if(((pstHorizontalWithVelocity->usBearing) > 359)
      ||(pstHorizontalWithVelocity->usHorizontalSpeed > 2047)
      ||(pstHorizontalWithVelocity->ulVerticalSpeed >2055))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHVERTICALVELOCITY_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    if(pstHorizontalWithVelocity->enVerticalDirection > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHVERTICALVELOCITY_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstHorizontalWithVelocity->usBearing);

    /*编码horizontalSpeed*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 11, pstHorizontalWithVelocity->usHorizontalSpeed);

    /*编码VerticalDirection*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1,
                             (VOS_UINT8)(pstHorizontalWithVelocity->enVerticalDirection));

    /*编码verticalSpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,
                             (VOS_UINT8)(pstHorizontalWithVelocity->ulVerticalSpeed));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeHorizontalWithUnceritanity
 Description     : 编码HorizontalVelocityWithUncertainty
 Input           : pstHorizontalWithUncertainty   需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         HorizontalVelocityWithUncertainty ::= SEQUENCE {
             bearing                     INTEGER(0..359),
             horizontalSpeed             INTEGER(0..2047),
             uncertaintySpeed            INTEGER(0..255)
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeHorizontalWithUnceritanity
(
    LPP_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU          *pstHorizontalWithUncertainty,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码bearing*/
    if(((pstHorizontalWithUncertainty->usBearing) > 359)
      ||(pstHorizontalWithUncertainty->ulUncertaintySpeed >255)
      ||(pstHorizontalWithUncertainty->usHorizontalSpeed > 2047))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHUNCERITANITY_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstHorizontalWithUncertainty->usBearing);

    /*编码horizontalSpeed*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 11, pstHorizontalWithUncertainty->usHorizontalSpeed);

    /*编码verticalSpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, (VOS_UINT8)(pstHorizontalWithUncertainty->ulUncertaintySpeed));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeHorizontalWithVeloctiyAndUncertaainty
 Description     : 编码HorizontalWithVerticalVelocityAndUncertainty
 Input           : pstHorizontalWithVelocityAndUncerta   需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         HorizontalWithVerticalVelocityAndUncertainty ::= SEQUENCE {
             bearing                     INTEGER(0..359),
             horizontalSpeed             INTEGER(0..2047),
             verticalDirection           ENUMERATED{upward, downward},
             verticalSpeed               INTEGER(0..255),
             horizontalUncertaintySpeed  INTEGER(0..255),
             verticalUncertaintySpeed    INTEGER(0..255)
         }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeHorizontalWithVeloctiyAndUncertaainty
(
    LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU      *pstHorizontalWithVelocityAndUncerta,
    VOS_UINT16                                                      *pusBitPos,
    VOS_UINT8                                                       *pucEncodeOutMsg
)
{
    /*编码bearing*/
    if (((pstHorizontalWithVelocityAndUncerta->usBearing) > 359)
       ||(pstHorizontalWithVelocityAndUncerta->usHorizontalSpeed > 2048))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHVELOCTIYANDUNCERTAAINTY_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    if(pstHorizontalWithVelocityAndUncerta->enVerticalDirection > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHVELOCTIYANDUNCERTAAINTY_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9,
                                  pstHorizontalWithVelocityAndUncerta->usBearing);

    /*编码horizontalSpeed*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 11,
                                  pstHorizontalWithVelocityAndUncerta->usHorizontalSpeed);

    /*编码VerticalDirection*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1,
                             (VOS_UINT8)(pstHorizontalWithVelocityAndUncerta->enVerticalDirection));

    /*编码verticalSpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,
                              pstHorizontalWithVelocityAndUncerta->ucVerticalSpeed);

    /*编码horizontalUncertaintySpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,
                              pstHorizontalWithVelocityAndUncerta->ucHorizontalUncertaintySpeed);

    /*编码verticalUncertaintySpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,
                              pstHorizontalWithVelocityAndUncerta->ucVerticalUncertaintySpeed);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeVelocityEstimate
 Description     : 编码Velocity
 Input           : pstVelocityCoordinate    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         Velocity ::= CHOICE {
             horizontalVelocity                          HorizontalVelocity,
             horizontalWithVerticalVelocity              HorizontalWithVerticalVelocity,
             horizontalVelocityWithUncertainty           HorizontalVelocityWithUncertainty,
             horizontalWithVerticalVelocityAndUncertainty
                                                         HorizontalWithVerticalVelocityAndUncertainty,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeVelocityEstimate
(
    LPP_VELOCITY_STRU                  *pstVelocityCoordinate,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16 usRslt = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*编码choice项*/
    if(pstVelocityCoordinate->ulChoice > 3)
    {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_VELOCITYESTIMATE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 2,
                              (VOS_UINT8)(pstVelocityCoordinate->ulChoice));

    switch(pstVelocityCoordinate->ulChoice)
    {
        case LOC_COM_HORIZONTAL_VELCOCTIY_CHOSEN:
            usRslt = NAS_LPP_EncodeHorizontalVelcoctiy(&(pstVelocityCoordinate->u.stHorizontalVelocity),
                                                          pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_CHOSEN:
            usRslt = NAS_LPP_EncodeHorizontalWithVerticalVelocity(&(pstVelocityCoordinate->u.stHorizontalWithVerticalVelocity),
                                                                     pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LOC_COM_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_CHOSEN:
            usRslt = NAS_LPP_EncodeHorizontalWithUnceritanity(&(pstVelocityCoordinate->u.stHorizontalVelocityWithUncertainty),
                                                                 pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeHorizontalWithVeloctiyAndUncertaainty(&(pstVelocityCoordinate->u.stHorizontalWithVerticalVelocityAndUncertainty),
                                                                            pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLocatonFailureCause
 Description     : 编码LocationFailureCause
 Input           : enLocationFailureCause         需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         LocationFailureCause ::= ENUMERATED {
             undefined,
             requestedMethodNotSupported,
             positionMethodFailure,
             periodicLocationMeasurementsNotAvailable,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLocatonFailureCause
(
    LPP_LOCATION_FAILURE_CAUSE_ENUM_UINT32                  enLocationFailureCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展位*/
    if(enLocationFailureCause > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_LOCATONFAILURECAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码枚举项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)enLocationFailureCause);

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLocationError
 Description     : 编码LocationError
 Input           : pstLocationError         需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         LocationError ::= SEQUENCE {
             locationfailurecause            LocationFailureCause,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLocationError
(
    LPP_LOCATION_ERROR_STRU            *pstLocationError,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
   VOS_UINT16                           usRslt              = 0;

    /*编码扩展位*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);
    /*解码枚举项*/
    usRslt = NAS_LPP_EncodeLocatonFailureCause(pstLocationError->enLocationFailureCasue,
                                               pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeCommonIesProvideLocation
 Description     : 编码CommonIEsProvideLocationInformation
 Input           : pstcommonIesProvideLocInfo 需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         CommonIEsProvideLocationInformation ::= SEQUENCE {
             locationEstimate            LocationCoordinates     OPTIONAL,
             velocityEstimate            Velocity                OPTIONAL,
             locationError               LocationError           OPTIONAL,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCommonIesProvideLocation
(
    LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU              *pstcommonIesProvideLocInfo,
    VOS_UINT16                                             *pusPos,
    VOS_UINT8                                              *puEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusPos,  puEncodeOutMsg);

    /*编码option*/
    NAS_LPP_EncodeBitsLess8(puEncodeOutMsg, pusPos, 1,
                             (VOS_UINT8)(pstcommonIesProvideLocInfo->bitOpLocationEstimate));
    NAS_LPP_EncodeBitsLess8(puEncodeOutMsg, pusPos, 1,
                             (VOS_UINT8)(pstcommonIesProvideLocInfo->bitOpVelocityEstimate));
    NAS_LPP_EncodeBitsLess8(puEncodeOutMsg, pusPos, 1,
                             (VOS_UINT8)(pstcommonIesProvideLocInfo->bitOpLocationError));

    /*编码locationEstimate*/
    if(NAS_LPP_SLCT == pstcommonIesProvideLocInfo->bitOpLocationEstimate)
    {
        usRslt = NAS_LPP_EncodeLoctionEstimate(&(pstcommonIesProvideLocInfo->stLocationEstimate),
                                                  pusPos,  puEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码VelocityEstimate*/
    if(NAS_LPP_SLCT == pstcommonIesProvideLocInfo->bitOpVelocityEstimate)
    {
        usRslt = NAS_LPP_EncodeVelocityEstimate(&(pstcommonIesProvideLocInfo->stVelocityEstimate),
                                                   pusPos,  puEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码LocationError*/
    if(NAS_LPP_SLCT == pstcommonIesProvideLocInfo->bitOpLocationError)
    {
        usRslt = NAS_LPP_EncodeLocationError(&(pstcommonIesProvideLocInfo->stLocationError),
                                                pusPos,  puEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodePlmnIdentity
 Description     : 编码plmn-Identity
 Input           : pstPlmnIndentity          需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :

                 CellGlobalIdEUTRA-AndUTRA ::= SEQUENCE {
                     plmn-Identity       SEQUENCE {
                                             mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                                             mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                                         },
                     cellIdentity        CHOICE {
                         eutra   BIT STRING (SIZE (28)),
                         utra    BIT STRING (SIZE (32))
                     },
                     ...
                 }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodePlmnIdentity
(
    LPP_PLMN_IDENTITY_STRU             *pstPlmnIndentity,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT32  ulLoop = 0;

    /*编码MCC*/
    for(ulLoop = 0; ulLoop < 3; ulLoop++)
    {
        if(pstPlmnIndentity->aucMcc[ulLoop] > 9)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PLMNIDENTITY_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)(pstPlmnIndentity->aucMcc[ulLoop]));
    }
    /*编码MNC*/
    if((pstPlmnIndentity->ucMncNum < 2) || (pstPlmnIndentity->ucMncNum  > 3))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PLMNIDENTITY_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)((pstPlmnIndentity->ucMncNum) - 2));
    for(ulLoop = 0; ulLoop < pstPlmnIndentity->ucMncNum; ulLoop++)
    {
        if(pstPlmnIndentity->aucMnc[ulLoop] > 9)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PLMNIDENTITY_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)(pstPlmnIndentity->aucMnc[ulLoop]));
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeCellIdentityEtranAndUtran
 Description     : 编码CellGlobalIdEUTRA-AndUTRA
 Input           : pstCellGolablId          需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :

                 CellGlobalIdEUTRA-AndUTRA ::= SEQUENCE {
                     plmn-Identity       SEQUENCE {
                                             mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                                             mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                                         },
                     cellIdentity        CHOICE {
                         eutra   BIT STRING (SIZE (28)),
                         utra    BIT STRING (SIZE (32))
                     },
                     ...
                 }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCellIdentityEtranAndUtran
(
    LPP_CELL_IDENTITY_STRU             *pstCellIdentity,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码choice*/
    if(pstCellIdentity->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_CELLIDENTITYETRANANDUTRAN_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstCellIdentity->ulChoice));

    switch(pstCellIdentity->ulChoice)
    {
        case LPP_EUTRA_CHOSEN:
            NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 28, pstCellIdentity->u.ulEutra);
            break;

        default:
            NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 32, pstCellIdentity->u.ulUtra);
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeCellGlobalIdEuranAndUtran
 Description     : 编码CellGlobalIdEUTRA-AndUTRA
 Input           : pstCellGolablId          需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :

                 CellGlobalIdEUTRA-AndUTRA ::= SEQUENCE {
                     plmn-Identity       SEQUENCE {
                                             mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                                             mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                                         },
                     cellIdentity        CHOICE {
                         eutra   BIT STRING (SIZE (28)),
                         utra    BIT STRING (SIZE (32))
                     },
                     ...
                 }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCellGlobalIdEuranAndUtran
(
    LPP_CELL_GLO_EUTRA_UTRA_STRU       *pstCellGolablId,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码plmn-identity*/
    usRslt = NAS_LPP_EncodePlmnIdentity(&(pstCellGolablId->stPlmnIdentity),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*CellIdentity*/
    usRslt = NAS_LPP_EncodeCellIdentityEtranAndUtran(&(pstCellGolablId->stCellIdentity),
                                                        pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEutra
 Description     : 编码eUTRA
 Input           : pstNetWorkTimeEutan      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :

                 eUTRA   SEQUENCE {
                         physCellId          INTEGER (0..503),
                         cellGlobalId        CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
                         systemFrameNumber   BIT STRING (SIZE (10)),
                         ...
                         },


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEutra
(
    LPP_MEAS_REF_TIME_EUTRA            *pstNetWorkTimeEutan,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNetWorkTimeEutan->bitCellGlobalId));

    /*编码physCellId*/
    if(pstNetWorkTimeEutan->ulPhysCellId > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EUTRA_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9,  pstNetWorkTimeEutan->ulPhysCellId);

    /*编码cellGloabalId*/
    if(NAS_LPP_SLCT == pstNetWorkTimeEutan->bitCellGlobalId)
    {
        usRslt = NAS_LPP_EncodeCellGlobalIdEuranAndUtran(&(pstNetWorkTimeEutan->stCellGlobalId),
                                                            pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码systemFrameNumber*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10,  pstNetWorkTimeEutan->ulSystemFramNumber);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeUtranMode
 Description     : 编码mode
 Input           : pstMode                  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 uTRA    SEQUENCE {
                         mode                    CHOICE {
                                                 fdd         SEQUENCE {
                                                             primary-CPICH-Info  INTEGER (0..511),
                                                             ...
                                                             },
                                                 tdd         SEQUENCE {
                                                             cellParameters      INTEGER (0..127),
                                                             ...
                                                             }
                                                 },
                         cellGlobalId            CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
                         referenceSystemFrameNumber
                                                 INTEGER (0..4095),
                         ...
                         },

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeUtranMode
(
    LPP_MODE_SELECT_STRU               *pstMode,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码choice*/
    if(pstMode->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_UTRANMODE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstMode->ulChoice));

    switch(pstMode->ulChoice)
    {
        case LPP_FDD_CHOSEN:
            /*编码扩展标志位*/
            NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);
            /*编码primary-cpich-info*/
            if(pstMode->u.stFdd.ulPrimaryCpichInfo  > 511)
            {
                NAS_LPP_ASN_FAIL_Message(NAS_LPP_UTRANMODE_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                        *pusBitPos, __LINE__, 0);
                return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
            }
            NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9,  pstMode->u.stFdd.ulPrimaryCpichInfo);
            break;

        default:
            /*编码扩展标志位*/
            NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);
            /*编码cellParametres*/
            if(pstMode->u.stTdd.ulCellParameters > 127)
            {
                NAS_LPP_ASN_FAIL_Message(NAS_LPP_UTRANMODE_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                        *pusBitPos, __LINE__, 0);
                return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
            }
            NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7,
                                     (VOS_UINT8)(pstMode->u.stTdd.ulCellParameters));
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeUtra
 Description     : 编码uTRA
 Input           : pstNetWorkTimeUtan      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 uTRA    SEQUENCE {
                         mode                    CHOICE {
                                                 fdd         SEQUENCE {
                                                             primary-CPICH-Info  INTEGER (0..511),
                                                             ...
                                                             },
                                                 tdd         SEQUENCE {
                                                             cellParameters      INTEGER (0..127),
                                                             ...
                                                             }
                                                 },
                         cellGlobalId            CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
                         referenceSystemFrameNumber
                                                 INTEGER (0..4095),
                         ...
                         },

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeUtra
(
    LPP_MEAS_REF_TIME_UTRA             *pstNetWorkTimeUtan,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNetWorkTimeUtan->bitCellGlobalId));

    /*编码mode*/
    usRslt = NAS_LPP_EncodeUtranMode(&(pstNetWorkTimeUtan->stMode),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码cellGloabalId*/
    if(NAS_LPP_SLCT == pstNetWorkTimeUtan->bitCellGlobalId)
    {
        usRslt = NAS_LPP_EncodeCellGlobalIdEuranAndUtran(&(pstNetWorkTimeUtan->stCellGlobalId),
                                                            pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码referenceSystemFrameNumber*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 12, pstNetWorkTimeUtan->ulRefSystemFramNumber);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeCellGlobalGeran
 Description     : 编码CellGlobalIdGERAN
 Input           : pstCellGlobalGeran        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 CellGlobalIdGERAN ::= SEQUENCE {
                     plmn-Identity       SEQUENCE {
                                             mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                                             mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                                             },
                     locationAreaCode        BIT STRING (SIZE (16)),
                     cellIdentity            BIT STRING (SIZE (16)),
                     ...
                 }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCellGlobalGeran
(
    LPP_CELL_GLO_ID_GERAN_STRU         *pstCellGlobalGeran,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码plmn-identity*/
    usRslt = NAS_LPP_EncodePlmnIdentity(&(pstCellGlobalGeran->stPlmnIdentity),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码locationAreaCode*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, pstCellGlobalGeran->usLocationAreaCode);

    /*编码locationAreaCode*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, pstCellGlobalGeran->usCellIdentity);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeRefFrame
 Description     : 编码referenceFrame
 Input           : pstRefFrame              需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 referenceFrame      SEQUENCE {
                                     referenceFN         INTEGER (0..65535),
                                     referenceFNMSB      INTEGER (0..63)     OPTIONAL,
                                     ...
                        }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeRefFrame
(
    LPP_REF_FRAME_STRU                 *pstRefFrame,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
     /*编码扩展标志位*/
     NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

     /*编码可选项*/
     NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstRefFrame->bitOpRefEnmsb));

     /*编码refFn*/
     NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, pstRefFrame->usRefFn);

     /*编码refFnmsb*/
     if(NAS_LPP_SLCT == pstRefFrame->bitOpRefEnmsb)
     {
        if(pstRefFrame->usRefFnmsn > 63)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_REFFRAME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstRefFrame->usRefFnmsn));
     }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGSM
 Description     : 编码gSM
 Input           : pstNetWorkTimeGsm        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
                 gSM     SEQUENCE {
                         bcchCarrier         INTEGER (0..1023),
                         bsic                INTEGER (0..63),
                         cellGlobalId        CellGlobalIdGERAN                   OPTIONAL,
                         referenceFrame      SEQUENCE {
                                             referenceFN         INTEGER (0..65535),
                                             referenceFNMSB      INTEGER (0..63)     OPTIONAL,
                                             ...
                                             },
                         deltaGNSS-TOD       INTEGER (0 .. 127)      OPTIONAL,
                         ...
                         },
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGSM
(
    LPP_MEAS_REF_TIME_GSM              *pstNetWorkTimeGsm,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNetWorkTimeGsm->bitCellGlobalId));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNetWorkTimeGsm->bitDelataGnssTod));

    /*编码bcchCarrier*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10, pstNetWorkTimeGsm->usBcchCarrier);

    /*编码bsic*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstNetWorkTimeGsm->usBsic));

    /*编码cellGlobalId*/
    if(NAS_LPP_SLCT == pstNetWorkTimeGsm->bitCellGlobalId)
    {
        usRslt = NAS_LPP_EncodeCellGlobalGeran(&(pstNetWorkTimeGsm->stCellGlobalId),  pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码refFrame*/
    usRslt = NAS_LPP_EncodeRefFrame(&(pstNetWorkTimeGsm->stRefFrame),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码deltaGnssTod*/
    if(NAS_LPP_SLCT == pstNetWorkTimeGsm->bitDelataGnssTod)
    {
        if(pstNetWorkTimeGsm->ulDelaGnssTod > 127)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GSM_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, (VOS_UINT8)(pstNetWorkTimeGsm->ulDelaGnssTod));
    }

    return NAS_LPP_ENCODE_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_LPP_EncodeNetWorkTime
 Description     : 编码networkTime
 Input           : pstNetWorkTime           需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         MeasurementReferenceTime  ::= SEQUENCE {
             gnss-TOD-msec       INTEGER (0..3599999),
             gnss-TOD-frac       INTEGER (0..3999)           OPTIONAL,
             gnss-TOD-unc        INTEGER (0..127)            OPTIONAL,
             gnss-TimeID         GNSS-ID,
             networkTime         CHOICE {
                 eUTRA   SEQUENCE {
                         physCellId          INTEGER (0..503),
                         cellGlobalId        CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
                         systemFrameNumber   BIT STRING (SIZE (10)),
                         ...
                         },
                 uTRA    SEQUENCE {
                         mode                    CHOICE {
                                                 fdd         SEQUENCE {
                                                             primary-CPICH-Info  INTEGER (0..511),
                                                             ...
                                                             },
                                                 tdd         SEQUENCE {
                                                             cellParameters      INTEGER (0..127),
                                                             ...
                                                             }
                                                 },
                         cellGlobalId            CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
                         referenceSystemFrameNumber
                                                 INTEGER (0..4095),
                         ...
                         },
                 gSM     SEQUENCE {
                         bcchCarrier         INTEGER (0..1023),
                         bsic                INTEGER (0..63),
                         cellGlobalId        CellGlobalIdGERAN                   OPTIONAL,
                         referenceFrame      SEQUENCE {
                                             referenceFN         INTEGER (0..65535),
                                             referenceFNMSB      INTEGER (0..63)     OPTIONAL,
                                             ...
                                             },
                         deltaGNSS-TOD       INTEGER (0 .. 127)      OPTIONAL,
                         ...
                         },
                 ...
                 }       OPTIONAL,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeNetWorkTime
(
    LPP_NET_WORK_TIME_MEAS_REF_STRU    *pstNetWorkTime,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*编码choice项*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 2, (VOS_UINT8)(pstNetWorkTime->ulChoice));

    switch(pstNetWorkTime->ulChoice)
    {
        case LPP_NETTIME_EUTRA_CHOSEN:
            usRslt = NAS_LPP_EncodeEutra(&(pstNetWorkTime->u.stLppMeasRefTimeEutra),
                                            pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_NETTIME_UTRAN_CHOSEN:
            usRslt = NAS_LPP_EncodeUtra(&(pstNetWorkTime->u.stLppMeasRefTimeUtra),
                                           pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_NETTIME_GSM_CHOSEN:
            usRslt = NAS_LPP_EncodeGSM(&(pstNetWorkTime->u.stLppMeasRefTimeGsm),
                                          pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_LPP_EncodeMeasRefTime
 Description     : 编码pstMeasRefTime
 Input           : pstAgnssSignalMeasInfo  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         MeasurementReferenceTime  ::= SEQUENCE {
             gnss-TOD-msec       INTEGER (0..3599999),
             gnss-TOD-frac       INTEGER (0..3999)           OPTIONAL,
             gnss-TOD-unc        INTEGER (0..127)            OPTIONAL,
             gnss-TimeID         GNSS-ID,
             networkTime         CHOICE {
                 eUTRA   SEQUENCE {
                         physCellId          INTEGER (0..503),
                         cellGlobalId        CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
                         systemFrameNumber   BIT STRING (SIZE (10)),
                         ...
                         },
                 uTRA    SEQUENCE {
                         mode                    CHOICE {
                                                 fdd         SEQUENCE {
                                                             primary-CPICH-Info  INTEGER (0..511),
                                                             ...
                                                             },
                                                 tdd         SEQUENCE {
                                                             cellParameters      INTEGER (0..127),
                                                             ...
                                                             }
                                                 },
                         cellGlobalId            CellGlobalIdEUTRA-AndUTRA       OPTIONAL,
                         referenceSystemFrameNumber
                                                 INTEGER (0..4095),
                         ...
                         },
                 gSM     SEQUENCE {
                         bcchCarrier         INTEGER (0..1023),
                         bsic                INTEGER (0..63),
                         cellGlobalId        CellGlobalIdGERAN                   OPTIONAL,
                         referenceFrame      SEQUENCE {
                                             referenceFN         INTEGER (0..65535),
                                             referenceFNMSB      INTEGER (0..63)     OPTIONAL,
                                             ...
                                             },
                         deltaGNSS-TOD       INTEGER (0 .. 127)      OPTIONAL,
                         ...
                         },
                 ...
                 }       OPTIONAL,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeMeasRefTime
(
    LPP_MEAS_REF_TIME_STRU             *pstMeasRefTime,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstMeasRefTime->bitOpGNSSTodFrac));
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstMeasRefTime->bitOpGNSSTodUnc));
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstMeasRefTime->bitOpNetWorkTime));

    /*编码gnss-TOD-msec*/
    if(pstMeasRefTime->ulGNSSTodMsec > 35999)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASREFTIME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 22, (VOS_UINT32)(pstMeasRefTime->ulGNSSTodMsec));

    /*编码 gnss-TOD-frac*/
    if(NAS_LPP_SLCT == pstMeasRefTime->bitOpGNSSTodFrac)
    {
        if(pstMeasRefTime->usGNSSTodFrac > 3999)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASREFTIME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 12, (VOS_UINT16)(pstMeasRefTime->usGNSSTodFrac));
    }

    /*编码gnss-TOD-unc*/
    if((pstMeasRefTime->bitOpGNSSTodUnc == 1)&&(pstMeasRefTime->usGNSSTodUnc > 127))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASREFTIME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    if(NAS_LPP_SLCT == pstMeasRefTime->bitOpGNSSTodUnc)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstMeasRefTime->usGNSSTodUnc));
    }

    /*编码gnss-TimeID*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstMeasRefTime->stGNSSId),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码networkTime*/
    if(NAS_LPP_SLCT == pstMeasRefTime->bitOpNetWorkTime)
    {
        usRslt = NAS_LPP_EncodeNetWorkTime(&(pstMeasRefTime->stNetWorktime),  pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssSatMeasElment
 Description     : 编码pstGnssSatMeasElment
 Input           : pstGnssSatMeasElment     需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-SatMeasElement ::= SEQUENCE {
             svID                SV-ID,
             cNo                 INTEGER (0..63),
             mpathDet            ENUMERATED {notMeasured (0), low (1), medium (2), high (3), ...},
             carrierQualityInd   INTEGER (0..3)              OPTIONAL,
             codePhase           INTEGER (0..2097151),
             integerCodePhase    INTEGER (0..127)            OPTIONAL,
             codePhaseRMSError   INTEGER (0..63),
             doppler             INTEGER (-32768..32767)     OPTIONAL,
             adr                 INTEGER (0..33554431)       OPTIONAL,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssSatMeasElment
(
    LPP_GNSS_SAT_MEAS_ELEMENT_STRU     *pstGnssSatMeasElment,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssSatMeasElment->bitOpCarrierQualityInd));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssSatMeasElment->bitOpIntegerCodePhase));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssSatMeasElment->bitOpDoppler));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssSatMeasElment->bitOpAdr));


    /*编码svid*/
    usRslt = NAS_LPP_EncodeSVID(&(pstGnssSatMeasElment->stSvId),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码cno*/
    if(pstGnssSatMeasElment->ulCNo > 63)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, pstGnssSatMeasElment->ulCNo);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstGnssSatMeasElment->ulCNo));

    /*编码mpatchDet*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstGnssSatMeasElment->enMpathDet));

    /*编码carrierqualityInd*/
    if(NAS_LPP_SLCT == pstGnssSatMeasElment->bitOpCarrierQualityInd)
    {
        if(pstGnssSatMeasElment->ucCrrierQualityInd > 3)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstGnssSatMeasElment->ucCrrierQualityInd));
    }

    /*编码codePhase*/
    if(pstGnssSatMeasElment->ulCodePhase > 2097151)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 21, pstGnssSatMeasElment->ulCodePhase);

    /*编码integercodephase*/
    if(NAS_LPP_SLCT == pstGnssSatMeasElment->bitOpIntegerCodePhase)
    {
        if(pstGnssSatMeasElment->ucIntgerCodePhase > 127)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, (VOS_UINT8)(pstGnssSatMeasElment->ucIntgerCodePhase));
    }

    /*编码codephasepmserror*/
    if(pstGnssSatMeasElment->ucCodePhaseRmsError > 63)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstGnssSatMeasElment->ucCodePhaseRmsError));

    /*编码dopploer*/
    if(NAS_LPP_SLCT == pstGnssSatMeasElment->bitOpDoppler)
    {
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, (VOS_UINT16)((pstGnssSatMeasElment->sDoppler) + 32768));
    }

    /*编码adr*/
    if(NAS_LPP_SLCT == pstGnssSatMeasElment->bitOpAdr)
    {
        if(pstGnssSatMeasElment->ulAdr > 33554431)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 25, pstGnssSatMeasElment->ulAdr);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssSatMeasList
 Description     : 编码pstGnssSatMeasList
 Input           : pstGnssSatMeasList       需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
    GNSS-SatMeasList ::= SEQUENCE (SIZE(1..64)) OF GNSS-SatMeasElement

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssSatMeasList
(
    LPP_GNSS_SAT_MEAS_LIST_STRU        *pstGnssSatMeasList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt      = 0;
    VOS_UINT32                          ulLoop      = 0;

    /*编码计数值*/
    if((pstGnssSatMeasList->ulGNSSSatMeasListCnt < 1)
    || (LPP_MAX_GNSS_SAT_MEAS_ELMENT_LEN < pstGnssSatMeasList->ulGNSSSatMeasListCnt))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 6, (VOS_UINT8)((pstGnssSatMeasList->ulGNSSSatMeasListCnt) - 1));

    /*编码消息实体*/
    for(ulLoop = 0; ulLoop < pstGnssSatMeasList->ulGNSSSatMeasListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodeGnssSatMeasElment(&(pstGnssSatMeasList->astGNSSSatMeasListArray[ulLoop]),
                                                    pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssSgnMeasElement
 Description     : 编码pstGnssSgnMeasElement
 Input           : pstGnssSgnMeasElement    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
    GNSS-SatMeasList ::= SEQUENCE (SIZE(1..64)) OF GNSS-SatMeasElement
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssSgnMeasElement
(
    LPP_GNSS_SGN_MEAS_ELEMENT_STRU     *pstGnssSgnMeasElement,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstGnssSgnMeasElement->bitOpGNSSCodePhaseAmbiguity));

    /*编码gnss-SignalID*/
    usRslt = NAS_LPP_EncodeGnssSignalID(&(pstGnssSgnMeasElement->stGNSSSignalId),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码codephaseAmbi*/
    if(NAS_LPP_SLCT == pstGnssSgnMeasElement->bitOpGNSSCodePhaseAmbiguity)
    {
        if(pstGnssSgnMeasElement->ulGNSSCodePhaseAmbiguity > 127)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSGNMEASELEMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstGnssSgnMeasElement->ulGNSSCodePhaseAmbiguity));
    }

    /*编码GNSS-SATMEASLIST*/
    usRslt = NAS_LPP_EncodeGnssSatMeasList((LPP_GNSS_SAT_MEAS_LIST_STRU*)&(pstGnssSgnMeasElement->stGNSSSatMeasList),
                                              pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssSgnMeasList
 Description     : 编码pstGnssSgnMeasList
 Input           : pstGnssSgnMeasList       需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
    GNSS-SgnMeasList ::= SEQUENCE (SIZE(1..8)) OF GNSS-SgnMeasElement
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssSgnMeasList
(
    LPP_GNSS_SGN_LIST_STRU             *pstGnssSgnMeasList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulLoop          = 0;

    /*编码计数值*/
    if((pstGnssSgnMeasList->ulGNSSSgnMeasListCnt < 1) || (pstGnssSgnMeasList->ulGNSSSgnMeasListCnt > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSGNMEASLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3,
                              (VOS_UINT8)((pstGnssSgnMeasList->ulGNSSSgnMeasListCnt) - 1));

    /*编码消息实体*/
    for(ulLoop = 0; ulLoop < pstGnssSgnMeasList->ulGNSSSgnMeasListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodeGnssSgnMeasElement(&(pstGnssSgnMeasList->astGNSSSgnMeasListArray[ulLoop]),
                                                     pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssMeasList
 Description     : 编码MeasurementForOneGNSS
 Input           : pstGnssMeasForOneGnss  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-MeasurementForOneGNSS ::= SEQUENCE {
             gnss-ID                 GNSS-ID,
             gnss-SgnMeasList        GNSS-SgnMeasList,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssMeasList
(
    LPP_GNSS_MEAS_FOR_ONE_GNSS_STRU    *pstGnssMeasForOneGnss,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt             = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*编码gnss-id*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstGnssMeasForOneGnss->stGNSSId), pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码gnss-SgnMeasList*/
    usRslt = NAS_LPP_EncodeGnssSgnMeasList(&(pstGnssMeasForOneGnss->stGNSSSgnMeasList),
                                              pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_Encdoe_AgnssSignalMeasInfo
 Description     : 编码SignalMeasurementInformation
 Input           : pstAgnssSignalMeasInfo  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-MeasurementList  ::= SEQUENCE (SIZE(1..16)) OF GNSS-MeasurementForOneGNSS

         GNSS-MeasurementForOneGNSS ::= SEQUENCE {
             gnss-ID                 GNSS-ID,
             gnss-SgnMeasList        GNSS-SgnMeasList,
             ...
         }

         GNSS-SgnMeasList ::= SEQUENCE (SIZE(1..8)) OF GNSS-SgnMeasElement

         GNSS-SgnMeasElement ::= SEQUENCE {
             gnss-SignalID           GNSS-SignalID,
             gnss-CodePhaseAmbiguity INTEGER (0..127)        OPTIONAL,
             gnss-SatMeasList        GNSS-SatMeasList,
             ...
         }

         GNSS-SatMeasList ::= SEQUENCE (SIZE(1..64)) OF GNSS-SatMeasElement

         GNSS-SatMeasElement ::= SEQUENCE {
             svID                SV-ID,
             cNo                 INTEGER (0..63),
             mpathDet            ENUMERATED {notMeasured (0), low (1), medium (2), high (3), ...},
             carrierQualityInd   INTEGER (0..3)              OPTIONAL,
             codePhase           INTEGER (0..2097151),
             integerCodePhase    INTEGER (0..127)            OPTIONAL,
             codePhaseRMSError   INTEGER (0..63),
             doppler             INTEGER (-32768..32767)     OPTIONAL,
             adr                 INTEGER (0..33554431)       OPTIONAL,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeMeasList
(
    LPP_GNSS_MEAS_LIST_STRU            *pstGnssMeasList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulLoop          = 0;


    if((pstGnssMeasList->ulGNSSMeasListCnt < 1) ||(pstGnssMeasList->ulGNSSMeasListCnt > LPP_MAX_GNSS_MEAS_FOR_ONE_GNSS_LEN))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)pstGnssMeasList->ulGNSSMeasListCnt - 1);


    /*编码消息实体*/
    for(ulLoop = 0; ulLoop < pstGnssMeasList->ulGNSSMeasListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodeGnssMeasList(&(pstGnssMeasList->astGNSSMeasListArray[ulLoop]),
                                               pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_Encdoe_AgnssSignalMeasInfo
 Description     : 编码SignalMeasurementInformation
 Input           : pstAgnssSignalMeasInfo  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-SignalMeasurementInformation ::= SEQUENCE {
             measurementReferenceTime        MeasurementReferenceTime,
             gnss-MeasurementList            GNSS-MeasurementList,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_Encdoe_AgnssSignalMeasInfo
(
    LPP_GNSS_SIGNAL_MEAS_INFO_STRU     *pstAgnssSignalMeasInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码measurementReferenceTime*/
    usRslt = NAS_LPP_EncodeMeasRefTime(&(pstAgnssSignalMeasInfo->stMeasRefTime),
                                          pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码MeasurementList*/
    usRslt = NAS_LPP_EncodeMeasList(&(pstAgnssSignalMeasInfo->stGNSSMeasList),
                                       pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAgnssList
 Description     : 编码GNSS-ID-Bitmap
 Input           : pstAgnssIdnBitmap        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-ID-Bitmap ::= SEQUENCE {
             gnss-ids            BIT STRING {    gps         (0),
                                                 sbas        (1),
                                                 qzss        (2),
                                                 galileo     (3),
                                                 glonass     (4)  } (SIZE (1..16)),
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAgnssList
(
    LPP_GNSS_ID_BITMAP_STRU            *pstAgnssIdnBitmap,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举项的长度字段*/
    if((pstAgnssIdnBitmap->usGnssIdsCnt < 1) || (pstAgnssIdnBitmap->usGnssIdsCnt > 16))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_AGNSSLIST_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)((pstAgnssIdnBitmap->usGnssIdsCnt) - 1));

    /*编码枚举项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstAgnssIdnBitmap->usGnssIdsCnt,
                             (VOS_UINT8)(pstAgnssIdnBitmap->usGNSSIDs));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_Encdoe_AgnssLocationInfo
 Description     : 编码LocationInformation
 Input           : pstAgnssLocationInfo  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-LocationInformation ::= SEQUENCE {
             measurementReferenceTime        MeasurementReferenceTime,
             agnss-List                      GNSS-ID-Bitmap,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_Encdoe_AgnssLocationInfo
(
    LPP_GNSS_LOCATION_INFO_STRU        *pstAgnssLocationInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码measurementReferenceTime*/
    usRslt = NAS_LPP_EncodeMeasRefTime(&(pstAgnssLocationInfo->stMeasRefTime),
                                          pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*编码agnss-List*/
    usRslt = NAS_LPP_EncodeAgnssList(&(pstAgnssLocationInfo->stAGNSSList),
                                        pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssLocationServerErrorCause
 Description     : 编码pstAgnssLocationServerErrorCause
 Input           : pstAgnssLocationServerErrorCause  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-LocationServerErrorCauses ::= SEQUENCE {
             cause       ENUMERATED  {
                             undefined,
                             undeliveredAssistanceDataIsNotSupportedByServer,
                             undeliveredAssistanceDataIsSupportedButCurrentlyNotAvailableByServer,                               undeliveredAssistanceDataIsPartlyNotSupportedAndPartlyNotAvailableByServer,
                             ...
                             },
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssLocationServerErrorCause
(
    LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU              *pstAgnssLocationServerErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    if(pstAgnssLocationServerErrorCause->enGNSSLocationServerCause > 2)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_GNSSLOCATIONSERVERERRORCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举的扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举值*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
    (VOS_UINT8)(pstAgnssLocationServerErrorCause->enGNSSLocationServerCause));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssTargetDeviceErrorCause
 Description     : 编码pstAgnsTargetDeviceErrorCause
 Input           : pstAgnsTargetDeviceErrorCause  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         GNSS-TargetDeviceErrorCauses ::= SEQUENCE {
             cause       ENUMERATED {    undefined,
                                         thereWereNotEnoughSatellitesReceived,
                                         assistanceDataMissing,
                                         notAllRequestedMeasurementsPossible,
                                         ...
                                     },
             fineTimeAssistanceMeasurementsNotPossible       NULL        OPTIONAL,
             adrMeasurementsNotPossible                      NULL        OPTIONAL,
             multiFrequencyMeasurementsNotPossible           NULL        OPTIONAL,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssTargetDeviceErrorCause
(
    LPP_GNSS_TARGET_DEVICE_ERROR_CAUSE_STRU                *pstAgnsTargetDeviceErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    if(pstAgnsTargetDeviceErrorCause->enGNSSTargetDeviceErrorCause > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_GNSSTARGETDEVICEERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnsTargetDeviceErrorCause->bitOpFineTimeAssistMeasNotPossible));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnsTargetDeviceErrorCause->bitOpAdrMeasNotPossibleExt));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnsTargetDeviceErrorCause->bitOpMultiFreqMeasNotPossibleExt));

    /*编码枚举的扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举值*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                             (VOS_UINT8)(pstAgnsTargetDeviceErrorCause->enGNSSTargetDeviceErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_Encdoe_AgnssError
 Description     : 编码A-GNSS-Error
 Input           : pstAgnssError  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         A-GNSS-Error ::= CHOICE {
             locationServerErrorCauses       GNSS-LocationServerErrorCauses,
             targetDeviceErrorCauses         GNSS-TargetDeviceErrorCauses,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_Encdoe_AgnssError
(
    LPP_GNSS_ERROR_STRU                *pstAgnssError,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码choice*/
    if(pstAgnssError->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_AGNSSERROR_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstAgnssError->ulChoice));

    switch(pstAgnssError->ulChoice)
    {
        case LPP_LOCATION_SERVER_ERROR_CAUSE_CHOSEN:
            usRslt = NAS_LPP_EncodeGnssLocationServerErrorCause(&(pstAgnssError->u.stLocationServerErrorCauses),
                                                                   pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeGnssTargetDeviceErrorCause(&(pstAgnssError->u.stTargetDeviceErrorCauses),
                                                                 pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }

            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAgnssProvideLocation
 Description     : 编码 A-GNSS-ProvideLocationInformation
 Input           : pstAgnssProvideLocation  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         A-GNSS-ProvideLocationInformation ::= SEQUENCE {
             gnss-SignalMeasurementInformation   GNSS-SignalMeasurementInformation       OPTIONAL,
             gnss-LocationInformation            GNSS-LocationInformation                OPTIONAL,
             gnss-Error                          A-GNSS-Error                            OPTIONAL,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAgnssProvideLocation
(
    LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU                   *pstAgnssProvideLocation,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                             usRslt = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssProvideLocation->bitOpGNSSSignalMeasInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssProvideLocation->bitOpGNSSLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssProvideLocation->bitOpGNSSError));

    /*编码SignalMeasurementInformation*/
    if(NAS_LPP_SLCT == pstAgnssProvideLocation->bitOpGNSSSignalMeasInfo)
    {
        usRslt = NAS_LPP_Encdoe_AgnssSignalMeasInfo(&(pstAgnssProvideLocation->stGNSSsignalMeasInfo),
                                                      pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码LocationInformation*/
    if(NAS_LPP_SLCT == pstAgnssProvideLocation->bitOpGNSSLocationInfo)
    {
        usRslt = NAS_LPP_Encdoe_AgnssLocationInfo(&(pstAgnssProvideLocation->stGNSSLocationInfo),
                                                    pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码Error*/
    if(NAS_LPP_SLCT == pstAgnssProvideLocation->bitOpGNSSError)
    {
        usRslt = NAS_LPP_Encdoe_AgnssError(&(pstAgnssProvideLocation->stGNSSError),
                                             pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEarfcnRefV9a0
 Description     : 编码ARFCN-ValueEUTRA-v9a0
 Input           : pstArfcnValueEutranV9a0  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ARFCN-ValueEUTRA-v9a0 ::=   INTEGER (maxEARFCN-Plus1..maxEARFCN2)

         maxEARFCN                   INTEGER ::= 65535   -- Maximum value of EUTRA carrier frequency

         maxEARFCN-Plus1             INTEGER ::= 65536   -- Lowest value extended EARFCN range

         maxEARFCN2                  INTEGER ::= 262143  -- Highest value extended EARFCN range

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEarfcnRefV9a0
(
    LPP_ARFCN_VALUE_EUTRA_V9A0_STRU    *pstArfcnValueEutranV9a0,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码ARFCN-ValueEUTRA-v9a0*/
    if((pstArfcnValueEutranV9a0->ulArfcnValueEUTRAv9a0 < 65536)
    || (pstArfcnValueEutranV9a0->ulArfcnValueEUTRAv9a0 > 262143))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EARFCNREFV9A0_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 18,
                                 (VOS_UINT32)((pstArfcnValueEutranV9a0->ulArfcnValueEUTRAv9a0) - 65536));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEarfcnRefV9a0
 Description     : 编码ARFCN-ValueEUTRA
 Input           : pstArfcnValueEutran      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ARFCN-ValueEUTRA ::= INTEGER (0..maxEARFCN)
         maxEARFCN   INTEGER ::= 65535   -- Maximum value of EUTRA carrier frequency


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeArfcnValueEutran
(
    LPP_ARFCN_VALUE_EUTRA_STRU         *pstArfcnValueEutran,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码ARFCN-ValueEUTRA-v9a0*/
    if(pstArfcnValueEutran->ulArfcnValueEUTRA > 65535)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ARFCNVALUEEUTRAN_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, pstArfcnValueEutran->ulArfcnValueEUTRA);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeReferenceQuality
 Description     : 编码OTDOA-MeasQuality
 Input           : pstOtdoaRefQuality       需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         OTDOA-MeasQuality ::= SEQUENCE {
             error-Resolution        BIT STRING (SIZE (2)),
             error-Value             BIT STRING (SIZE (5)),
             error-NumSamples        BIT STRING (SIZE (3))               OPTIONAL,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeReferenceQuality
(
    LPP_OTDOA_MEAS_QUALITY_STRU        *pstOtdoaRefQuality,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaRefQuality->bitOpErrorNumSampiles));

    /*编码error-Resolution*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                             (VOS_UINT8)(pstOtdoaRefQuality->ucErrorResolution));

    /*编码error-Value*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 5,
                             (VOS_UINT8)(pstOtdoaRefQuality->ucErrorValuse));

    /*编码error-NumSamples*/
    if(NAS_LPP_SLCT == pstOtdoaRefQuality->bitOpErrorNumSampiles)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (VOS_UINT8)(pstOtdoaRefQuality->ucErrorNumSamples));
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeNeighbourMeasElement
 Description     : 编码NeighbourMeasElement
 Input           : pstNeighbourMeasElement  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         NeighbourMeasurementList ::= SEQUENCE (SIZE(1..24)) OF NeighbourMeasurementElement

         NeighbourMeasurementElement ::= SEQUENCE {
             physCellIdNeighbour     INTEGER (0..503),
             cellGlobalIdNeighbour   ECGI                    OPTIONAL,
             earfcnNeighbour         ARFCN-ValueEUTRA        OPTIONAL,       -- Cond NotSameAsRef2
             rstd                    INTEGER (0..12711),
             rstd-Quality            OTDOA-MeasQuality,
             ...,
             [[ earfcnNeighbour-v9a0 ARFCN-ValueEUTRA-v9a0   OPTIONAL        -- Cond NotSameAsRef3
             ]]
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeNeighbourMeasElement
(
    LPP_NEIGHBOUR_MEAS_ELEMENT_STRU    *pstNeighbourMeasElement,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt                  = 0;
    VOS_UINT32                          ulMeasInfoLV            = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstNeighbourMeasElement->bitOpNeighbourMeasElementExt));

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstNeighbourMeasElement->bitOpCellGlobalIdNeighbour));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstNeighbourMeasElement->bitOpArfcnValueEutra));

    /*编码physCellIdNeighbour*/
    if(pstNeighbourMeasElement->ulPhysCellIdNeighbor > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_NEIGHBOURMEASELEMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9,
                                  pstNeighbourMeasElement->ulPhysCellIdNeighbor);

    /*编码cellGlobalIdRef*/
    if(NAS_LPP_SLCT == pstNeighbourMeasElement->bitOpCellGlobalIdNeighbour)
    {
        usRslt = NAS_LPP_EncodeECGI(&(pstNeighbourMeasElement->stCellGlobalIdNeighbour),
                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码earfcnRef*/
    if(NAS_LPP_SLCT == pstNeighbourMeasElement->bitOpArfcnValueEutra)
    {
        usRslt = NAS_LPP_EncodeArfcnValueEutran(&(pstNeighbourMeasElement->stEarfcnNeighbour),
                                                   pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码rstd*/
    if(pstNeighbourMeasElement->ulRstd > 12711)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_NEIGHBOURMEASELEMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 14, pstNeighbourMeasElement->ulRstd);

    /*编码rstd-Quality*/
    usRslt = NAS_LPP_EncodeReferenceQuality(&(pstNeighbourMeasElement->stRstdQuality),
                                               pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    if(NAS_LPP_NO_SLCT == pstNeighbourMeasElement->bitOpNeighbourMeasElementExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*编码扩展项的L-1*/
    /*为什么这里编码的是0进去呢，因为当前扩展项的计数是1，编码值是L-1即是0*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, 0);

    /*编码扩展项的option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstNeighbourMeasElement->bitOpArfcnValueEutraV9a0));

    if(NAS_LPP_SLCT == pstNeighbourMeasElement->bitOpArfcnValueEutraV9a0)
    {
        /*编码confidenceSupport 的L+V, 这里占用3个byte， 具体数据表示占用多少个byte*/
        ulMeasInfoLV = 3;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulMeasInfoLV);
        /*编码[[]]中的option项*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNeighbourMeasElement->stEarfcnNeighbourV9a0.bitOpARFCNValueEutraV9A0));
        usRslt = NAS_LPP_EncodeEarfcnRefV9a0(&(pstNeighbourMeasElement->stEarfcnNeighbourV9a0),
                                                pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }

        /*编码填充位*/
        /*填充位的编码总共占用24个bit，变量本身占用了18个bit， 1个bit的option，另外5个bit则是需要填充的bit*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (VOS_UINT16)(ulMeasInfoLV*8 - 18 - 1), 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeNeighbourMeasList
 Description     : 编码NeighbourMeasurementList
 Input           : pstNeighbourMeasList     需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         NeighbourMeasurementList ::= SEQUENCE (SIZE(1..24)) OF NeighbourMeasurementElement

         NeighbourMeasurementElement ::= SEQUENCE {
             physCellIdNeighbour     INTEGER (0..503),
             cellGlobalIdNeighbour   ECGI                    OPTIONAL,
             earfcnNeighbour         ARFCN-ValueEUTRA        OPTIONAL,       -- Cond NotSameAsRef2
             rstd                    INTEGER (0..12711),
             rstd-Quality            OTDOA-MeasQuality,
             ...,
             [[ earfcnNeighbour-v9a0 ARFCN-ValueEUTRA-v9a0   OPTIONAL        -- Cond NotSameAsRef3
             ]]
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeNeighbourMeasList
(
    LPP_NEIGHBOUR_MEAS_LIST_STRU       *pstNeighbourMeasList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16 usRslt = 0;
    VOS_UINT32 ulLoop = 0;

    /*编码计数值*/
    if((pstNeighbourMeasList->ulNeighbourMeasListCnt < 1)
    || (pstNeighbourMeasList->ulNeighbourMeasListCnt > 24))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_NEIGHBOURMEASLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 5,
                              (VOS_UINT8)((pstNeighbourMeasList->ulNeighbourMeasListCnt) - 1));

    /*编码消息实体*/
    for(ulLoop = 0; ulLoop < pstNeighbourMeasList->ulNeighbourMeasListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodeNeighbourMeasElement(&(pstNeighbourMeasList->astNeighbourMeasListArray[ulLoop]),
                                                       pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeOtdoaSignalMeasInfo
 Description     : 编码OTDOA-SignalMeasurementInformation
 Input           : pstOtdoaSignalMeasInfo   需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         OTDOA-SignalMeasurementInformation ::= SEQUENCE {
             systemFrameNumber       BIT STRING (SIZE (10)),
             physCellIdRef           INTEGER (0..503),
             cellGlobalIdRef         ECGI                    OPTIONAL,
             earfcnRef               ARFCN-ValueEUTRA        OPTIONAL,       -- Cond NotSameAsRef0
             referenceQuality        OTDOA-MeasQuality       OPTIONAL,
             neighbourMeasurementList    NeighbourMeasurementList,
             ...,
             [[ earfcnRef-v9a0       ARFCN-ValueEUTRA-v9a0   OPTIONAL        -- Cond NotSameAsRef1
             ]]
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOtdoaSignalMeasInfo
(
    LPP_OTDOA_SIGNAL_MEAS_INFO_STRU    *pstOtdoaSignalMeasInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulMeasInfoLV    = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpOtdoaSignalMeasInfoExt));

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpCellGlobalIdRef));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpArfcnValueEutra));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpRefQuality));

    /*编码systemFrameNumber*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10, pstOtdoaSignalMeasInfo->usSystemFrameNumber);

    /*编码physCellIdRef*/
    if(pstOtdoaSignalMeasInfo->usPhysCellIdRef > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOASIGNALMEASINFO_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstOtdoaSignalMeasInfo->usPhysCellIdRef);

    /*编码cellGlobalIdRef*/
    if(NAS_LPP_SLCT == pstOtdoaSignalMeasInfo->bitOpCellGlobalIdRef)
    {
        usRslt = NAS_LPP_EncodeECGI(&(pstOtdoaSignalMeasInfo->stCellGlobalIdRef),
                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码earfcnRef*/
    if(NAS_LPP_SLCT == pstOtdoaSignalMeasInfo->bitOpArfcnValueEutra)
    {
        usRslt = NAS_LPP_EncodeArfcnValueEutran(&(pstOtdoaSignalMeasInfo->stEarfcnRef),
                                                   pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码referenceQuality*/
    if(NAS_LPP_SLCT == pstOtdoaSignalMeasInfo->bitOpRefQuality)
    {
        usRslt = NAS_LPP_EncodeReferenceQuality(&(pstOtdoaSignalMeasInfo->stReferenceQuality),
                                                   pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码neighbourMeasurementList*/
    usRslt = NAS_LPP_EncodeNeighbourMeasList(&(pstOtdoaSignalMeasInfo->stNeighbourMeasList),
                                                pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    if(NAS_LPP_NO_SLCT == pstOtdoaSignalMeasInfo->bitOpOtdoaSignalMeasInfoExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*编码扩展项的L-1*/
    /*为什么这里编码的是0进去呢，因为当前扩展项的计数是1，编码值是L-1即是0*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, 0);

    /*编码扩展项的option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpArfcnValueEutraV9a0));

    if(NAS_LPP_SLCT == pstOtdoaSignalMeasInfo->bitOpArfcnValueEutraV9a0)
    {
        /*编码confidenceSupport 的L+V, 这里占用3个byte， 具体数据表示占用多少个byte*/
        ulMeasInfoLV = 3;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulMeasInfoLV);
        /*编码[[]]中的option项*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpArfcnValueEutraV9a0));
        usRslt = NAS_LPP_EncodeEarfcnRefV9a0(&(pstOtdoaSignalMeasInfo->stEarfcnRefV9a0),
                                                pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }


        /*编码填充位*/
        /*填充位的编码总共占用24个bit，变量本身占用了18个bit， 1个bit的option，另外5个bit则是需要填充的bit*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 5, 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeOtdoaLocationServerErrorCause
 Description     : 编码pstAgnssLocationServerErrorCause
 Input           : pstAgnssLocationServerErrorCause  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         OTDOA-LocationServerErrorCauses ::= SEQUENCE {
             cause       ENUMERATED  {   undefined,
                                         assistanceDataNotSupportedByServer,
                                         assistanceDataSupportedButCurrentlyNotAvailableByServer,
                                         ...
                                     },
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOtdoaLocationServerErrorCause
(
    LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_STRU             *pstOtdoaLocationServerErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    if(pstOtdoaLocationServerErrorCause->enOtdoaLocationServerErrorCause > 2)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_OTDOALOCATIONSERVERERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举的扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举值*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                             (VOS_UINT8)(pstOtdoaLocationServerErrorCause->enOtdoaLocationServerErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssTargetDeviceErrorCause
 Description     : 编码pstAgnsTargetDeviceErrorCause
 Input           : pstAgnsTargetDeviceErrorCause  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         OTDOA-TargetDeviceErrorCauses ::= SEQUENCE {
             cause       ENUMERATED {    undefined,
                                         assistance-data-missing,
                                         unableToMeasureReferenceCell,
                                         unableToMeasureAnyNeighbourCell,
                                         attemptedButUnableToMeasureSomeNeighbourCells,
                                         ...
                                     },
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOtdoaTargetDeviceErrorCause
(
    LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_STRU               *pstOtdoaTargetDeviceErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    if(pstOtdoaTargetDeviceErrorCause->enOtoaTargetDeviceErrorCause > 4)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_OTDOATARGETDEVICEERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__,
                                 pstOtdoaTargetDeviceErrorCause->enOtoaTargetDeviceErrorCause);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举的扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举值*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                             (VOS_UINT8)(pstOtdoaTargetDeviceErrorCause->enOtoaTargetDeviceErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeOtdoaError
 Description     : 编码OTDOA-Error
 Input           : pstOtdoaError            需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         OTDOA-Error ::= CHOICE {
             locationServerErrorCauses       OTDOA-LocationServerErrorCauses,
             targetDeviceErrorCauses         OTDOA-TargetDeviceErrorCauses,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOtdoaError
(
    LPP_OTDOA_ERROR_STRU               *pstOtdoaError,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt      = 0;

    /*编码choice*/
    if(pstOtdoaError->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_OTDOAERROR_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstOtdoaError->ulChoice));

    switch(pstOtdoaError->ulChoice)
    {
        case LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_CHOSEN:
            usRslt = NAS_LPP_EncodeOtdoaLocationServerErrorCause(&(pstOtdoaError->u.stLocationServerErrorCauses),
                                                                    pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeOtdoaTargetDeviceErrorCause(&(pstOtdoaError->u.stTargetDeviceErrorCauses),
                                                                  pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeOtdoaProvideLocation
 Description     : 编码OTDOA-ProvideLocationInformation
 Input           : pstAgnssProvideLocation  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         OTDOA-ProvideLocationInformation ::= SEQUENCE {
             otdoaSignalMeasurementInformation   OTDOA-SignalMeasurementInformation  OPTIONAL,
             otdoa-Error                         OTDOA-Error                         OPTIONAL,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOtdoaProvideLocation
(
    LPP_OTDOA_PROVIDE_LOCATION_INFO_STRU                   *pstOtdoaProvideLocation,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstOtdoaProvideLocation->bitOpOtdoaSignalMeasInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstOtdoaProvideLocation->bitOpOtdoaError));

    /*编码otdoaSignalMeasementInformation*/
    if(NAS_LPP_SLCT == pstOtdoaProvideLocation->bitOpOtdoaSignalMeasInfo)
    {
        usRslt = NAS_LPP_EncodeOtdoaSignalMeasInfo(&(pstOtdoaProvideLocation->stOtdoaSignalMeasInfo),
                                                      pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码otdoaerror*/
    if(NAS_LPP_SLCT == pstOtdoaProvideLocation->bitOpOtdoaError)
    {
        usRslt = NAS_LPP_EncodeOtdoaError(&(pstOtdoaProvideLocation->stOtdoaError),
                                             pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodePrimaryCellMeasuredRslt
 Description     : 编码MeasuredResultsElement
 Input           : pstMeasRsltElment        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         MeasuredResultsElement ::= SEQUENCE {
             physCellId      INTEGER (0..503),
             cellGlobalId    CellGlobalIdEUTRA-AndUTRA           OPTIONAL,
             arfcnEUTRA      ARFCN-ValueEUTRA,
             systemFrameNumber
                             BIT STRING (SIZE (10))              OPTIONAL,
             rsrp-Result     INTEGER (0..97)                     OPTIONAL,
             rsrq-Result     INTEGER (0..34)                     OPTIONAL,
             ue-RxTxTimeDiff INTEGER (0..4095)                   OPTIONAL,
             ...,
             [[ arfcnEUTRA-v9a0      ARFCN-ValueEUTRA-v9a0       OPTIONAL        -- Cond EARFCN-max
             ]]
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodePrimaryCellMeasuredRslt
(
    LPP_MEAS_RESULT_ELEMENT_STRU       *pstMeasRsltElment,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulMeasInfoLV    = 0;

    /*编码扩展标志位*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpMeasResultElementExt));

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpCellGlobalId));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpSystemFrameNumber));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpRsrpResult));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpRsrqResult));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpUeRxTxTimeDiff));

    /*编码physCellIdRef*/
    if(pstMeasRsltElment->ulPhyCellId > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstMeasRsltElment->ulPhyCellId);

    /*编码cellGlobalId*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpCellGlobalId)
    {
        usRslt = NAS_LPP_EncodeCellGlobalIdEuranAndUtran(&(pstMeasRsltElment->stCellGloId),
                                                            pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码earfcnRef*/
    usRslt = NAS_LPP_EncodeArfcnValueEutran(&(pstMeasRsltElment->stArfcnEutra),
                                               pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }


    /*编码systemFrameNumber*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpSystemFrameNumber)
    {
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10, pstMeasRsltElment->usSystemFrameNumber);
    }

    /*编码rsrp-Result*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpRsrpResult)
    {
        if(pstMeasRsltElment->ucRsrpResult > 97)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, (VOS_UINT8)(pstMeasRsltElment->ucRsrpResult));
    }

    /*编码rsrq-Result*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpRsrqResult)
    {
        if(pstMeasRsltElment->ucRsrqResult > 34)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstMeasRsltElment->ucRsrqResult));
    }

    /*编码ue-RxTxTimeDiff*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpUeRxTxTimeDiff)
    {
        if(pstMeasRsltElment->ulUeRxTxTimeDiff > 4095)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 12, pstMeasRsltElment->ulUeRxTxTimeDiff);
    }

    if(NAS_LPP_NO_SLCT == pstMeasRsltElment->bitOpMeasResultElementExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*编码扩展项的L-1*/
    /*为什么这里编码的是0进去呢，因为当前扩展项的计数是1，编码值是L-1即是0*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, 0);

    /*编码扩展项的option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstMeasRsltElment->bitOpArfcnEutraV9a0));

    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpArfcnEutraV9a0)
    {
        /*编码confidenceSupport 的L+V, 这里占用3个byte， 具体数据表示占用多少个byte*/
        ulMeasInfoLV = 3;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulMeasInfoLV);
        /*编码[[]]中的option项*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstMeasRsltElment->bitOpArfcnEutraV9a0));
            usRslt = NAS_LPP_EncodeEarfcnRefV9a0(&(pstMeasRsltElment->stArfcnEutraV9a0),
                                                    pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }

        /*编码填充位*/
        /*填充位的编码总共占用24个bit，变量本身占用了18个bit， 1个bit的option，另外5个bit则是需要填充的bit*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (VOS_UINT16)(ulMeasInfoLV*8 - 18 - 1), 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeMeasRsltList
 Description     : 编码MeasuredResultsList
 Input           : pstMeasRsltList          需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         MeasuredResultsList ::= SEQUENCE (SIZE(1..32)) OF MeasuredResultsElement

         MeasuredResultsElement ::= SEQUENCE {
             physCellId      INTEGER (0..503),
             cellGlobalId    CellGlobalIdEUTRA-AndUTRA           OPTIONAL,
             arfcnEUTRA      ARFCN-ValueEUTRA,
             systemFrameNumber
                             BIT STRING (SIZE (10))              OPTIONAL,
             rsrp-Result     INTEGER (0..97)                     OPTIONAL,
             rsrq-Result     INTEGER (0..34)                     OPTIONAL,
             ue-RxTxTimeDiff INTEGER (0..4095)                   OPTIONAL,
             ...,
             [[ arfcnEUTRA-v9a0      ARFCN-ValueEUTRA-v9a0       OPTIONAL        -- Cond EARFCN-max
             ]]
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeMeasRsltList
(
    LPP_MEAS_RESULT_LIST_STRU          *pstMeasRsltList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulLoop          = 0;

    /*编码计数值*/
    if((pstMeasRsltList->ulMeasResultsListCnt < 1) || (pstMeasRsltList->ulMeasResultsListCnt > 32))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASRSLTLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 5,
                              (VOS_UINT8)((pstMeasRsltList->ulMeasResultsListCnt) - 1));

    /*编码消息实体*/
    for(ulLoop = 0; ulLoop < pstMeasRsltList->ulMeasResultsListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodePrimaryCellMeasuredRslt(&(pstMeasRsltList->astMeasResultsList[ulLoop]),
                                                          pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEcellIdSignalMeasInfo
 Description     : 编码ECID-SignalMeasurementInformation
 Input           : pstEcellIdSignalMeasInfo 需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ECID-SignalMeasurementInformation ::= SEQUENCE {
             primaryCellMeasuredResults  MeasuredResultsElement  OPTIONAL,
             measuredResultsList         MeasuredResultsList,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEcellIdSignalMeasInfo
(
    LPP_ECID_SIGNAL_MEAS_INFO_STRU     *pstEcellIdSignalMeasInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstEcellIdSignalMeasInfo->bitOpPrimaryCellMeasRslt));

    /*编码primaryCellMeasuredResults*/
    if(NAS_LPP_SLCT == pstEcellIdSignalMeasInfo->bitOpPrimaryCellMeasRslt)
    {
        usRslt = NAS_LPP_EncodePrimaryCellMeasuredRslt(&(pstEcellIdSignalMeasInfo->stPrimaryCellMeasResult),
                                                          pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码measuredResultsList*/
    usRslt = NAS_LPP_EncodeMeasRsltList(&(pstEcellIdSignalMeasInfo->stMeasResultList),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEcellIdLocationServerErrorCause
 Description     : 编码ECID-LocationServerErrorCauses
 Input           : pstEcidLocationServerErrorCause  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ECID-LocationServerErrorCauses ::= SEQUENCE {
             cause       ENUMERATED  {   undefined,
                                         ...
                                     },
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEcellIdLocationServerErrorCause
(
    LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_STRU              *pstEcidLocationServerErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    if(pstEcidLocationServerErrorCause->enEcidLocatSerErrorCause > 0)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ECELLIDLOCATIONSERVERERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举的扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举值*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstEcidLocationServerErrorCause->enEcidLocatSerErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeGnssTargetDeviceErrorCause
 Description     : 编码pstAgnsTargetDeviceErrorCause
 Input           : pstAgnsTargetDeviceErrorCause  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ECID-TargetDeviceErrorCauses ::= SEQUENCE {
             cause       ENUMERATED {    undefined,
                                         requestedMeasurementNotAvailable,
                                         notAllrequestedMeasurementsPossible,
                                         ...
                                     },
             rsrpMeasurementNotPossible              NULL        OPTIONAL,
             rsrqMeasurementNotPossible              NULL        OPTIONAL,
             ueRxTxMeasurementNotPossible            NULL        OPTIONAL,
             ...
         }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-6  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEcellIdTargetDeviceErrorCause
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_STRU                *pstEcidTargetDeviceErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*编码扩展项*/
    if(pstEcidTargetDeviceErrorCause->enEcidTargetDeviceErrorCause > 2)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ECELLIDTARGETDEVICEERRORCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcidTargetDeviceErrorCause->bitOpRsrpMeasNotPossible));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcidTargetDeviceErrorCause->bitOpRsrqMeasNotPossible));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcidTargetDeviceErrorCause->bitOpRxTxMeasNotPossible));

    /*编码枚举的扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码枚举值*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                             (VOS_UINT8)(pstEcidTargetDeviceErrorCause->enEcidTargetDeviceErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEcellIdSignalMeasInfo
 Description     : 编码ECID-SignalMeasurementInformation
 Input           : pstEcellIdSignalMeasInfo 需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ECID-Error ::= CHOICE {
             locationServerErrorCauses       ECID-LocationServerErrorCauses,
             targetDeviceErrorCauses         ECID-TargetDeviceErrorCauses,
             ...
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEcellIdError
(
    LPP_ECID_ERROR_STRU                *pstEcellIdError,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码choice*/
    if(pstEcellIdError->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ECELLIDERROR_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*编码扩展标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstEcellIdError->ulChoice));

    switch(pstEcellIdError->ulChoice)
    {
        case LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_CHOSEN:
            usRslt = NAS_LPP_EncodeEcellIdLocationServerErrorCause(&(pstEcellIdError->u.stLocationServerErrorCauses),
                                                                      pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeEcellIdTargetDeviceErrorCause(&(pstEcellIdError->u.stTargetDeviceErrorCauses),
                                                                    pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }

            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEcellIdProvideLocation
 Description     : 编码ECID-ProvideLocationInformation
 Input           : pstAgnssProvideLocation  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ECID-ProvideLocationInformation ::= SEQUENCE {
             ecid-SignalMeasurementInformation   ECID-SignalMeasurementInformation       OPTIONAL,
             ecid-Error                          ECID-Error                              OPTIONAL,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEcellIdProvideLocation
(
    LPP_ECID_PROVIDE_LOCATION_INFO_STRU                    *pstEcellIdProvideLocation,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*编码扩展项*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码可选项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcellIdProvideLocation->bitOpEcidSignalMeasInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcellIdProvideLocation->bitOpEcidError));

    /*编码ecid-SignalMeasurementInformation*/
    if(NAS_LPP_SLCT == pstEcellIdProvideLocation->bitOpEcidSignalMeasInfo)
    {
        usRslt = NAS_LPP_EncodeEcellIdSignalMeasInfo(&(pstEcellIdProvideLocation->stEcidSignalMeasInfo),
                                                        pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码ecid-Error*/
    if(NAS_LPP_SLCT == pstEcellIdProvideLocation->bitOpEcidError)
    {
        usRslt = NAS_LPP_EncodeEcellIdError(&(pstEcellIdProvideLocation->stEcidError),
                                                pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEcellIdProvideLocation
 Description     : 编码ECID-ProvideLocationInformation
 Input           : pstAgnssProvideLocation  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

         maxEPDU INTEGER ::= 16

         EPDU ::= SEQUENCE {
             ePDU-Identifier         EPDU-Identifier,
             ePDU-Body               EPDU-Body
         }

         EPDU-Identifier ::= SEQUENCE {
             ePDU-ID                 EPDU-ID,
             ePDU-Name               EPDU-Name       OPTIONAL,
             ...
         }

         EPDU-ID ::= INTEGER (1..256)

         EPDU-Name ::= VisibleString (SIZE (1..32))

         EPDU-Body ::= OCTET STRING

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEpduProvideLocation
(
    LPP_EPDU_PROVIDE_LOCATION_INFO_STRU                    *pstProvideLocation,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    usRslt = NAS_LPP_EncodeEPDUSequence((LPP_EPDU_SEQUENCE_STRU *)pstProvideLocation,
                                          pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return      usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeExtProvideLocationInfoR9
 Description     : 编码ProvideLocationInformation-r9-IEs
 Input           : pstExtProLocInfoR9       需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ProvideLocationInformation-r9-IEs ::= SEQUENCE {
             commonIEsProvideLocationInformation
                                             CommonIEsProvideLocationInformation     OPTIONAL,
             a-gnss-ProvideLocationInformation   A-GNSS-ProvideLocationInformation   OPTIONAL,
             otdoa-ProvideLocationInformation    OTDOA-ProvideLocationInformation    OPTIONAL,
             ecid-ProvideLocationInformation     ECID-ProvideLocationInformation     OPTIONAL,
             epdu-ProvideLocationInformation     EPDU-Sequence                       OPTIONAL,
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeExtProvideLocationInfoR9
(
    LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU                  *pstExtProLocInfoR9,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*编码扩展项标志位*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*编码option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpCommonIEsPRovideLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpAGNSSPRovideLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpOtdoaPRovideLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpEcidPRovideLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpEpduSequence));

    /*编码commonIesProvideLocation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpCommonIEsPRovideLocationInfo)
    {
        usRslt = NAS_LPP_EncodeCommonIesProvideLocation(&(pstExtProLocInfoR9->stCommonIEsPRovideLocationInfo),
                                                           pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码 a-gnss-ProvideLocationInformation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpAGNSSPRovideLocationInfo)
    {
        usRslt = NAS_LPP_EncodeAgnssProvideLocation(&(pstExtProLocInfoR9->stAGNSSPRovideLocationInfo),
                                                       pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码 otdoa-ProvideLocationInformation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpOtdoaPRovideLocationInfo)
    {
        usRslt = NAS_LPP_EncodeOtdoaProvideLocation(&(pstExtProLocInfoR9->stOtdoaPRovideLocationInfo),
                                                       pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码 ecid-ProvideLocationInformation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpEcidPRovideLocationInfo)
    {
        usRslt = NAS_LPP_EncodeEcellIdProvideLocation(&(pstExtProLocInfoR9->stEcidPRovideLocationInfo),
                                                         pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码 epdu-ProvideLocationInformation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpEpduSequence)
    {
        usRslt = NAS_LPP_EncodeEpduProvideLocation(&(pstExtProLocInfoR9->stEpduPRovideLocationInfo),
                                                      pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeExtProvideLocationInfo
 Description     : 编码LPP_CRITI_EXT_PROVIDE_LOCATION_INFO_STRU
 Input           : pstExtProLocInfo         需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ProvideLocationInformation ::= SEQUENCE {
                 criticalExtensions      CHOICE {
                     c1                      CHOICE {
                         provideLocationInformation-r9   ProvideLocationInformation-r9-IEs,
                         spare3 NULL, spare2 NULL, spare1 NULL
                     },
                     criticalExtensionsFuture    SEQUENCE {}
                 }
             }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeExtProvideLocationInfo
(
    LPP_CRITI_EXT_PROVIDE_LOCATION_INFO_STRU               *pstExtProLocInfo,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*编码choice项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstExtProLocInfo->ulChoice));

    switch(pstExtProLocInfo->ulChoice)
    {
        case LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_R9_CHOSEN:
            usRslt = NAS_LPP_EncodeExtProvideLocationInfoR9(&(pstExtProLocInfo->u.stProLocationInfoR9),
                                                               pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeProvideLocInfo
 Description     : 编码LPP_MESSAGE_PROVIDE_LOCATION_INFO_STRU
 Input           : pstProvideCapabilty      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         ProvideLocationInformation ::= SEQUENCE {
                 criticalExtensions      CHOICE {
                     c1                      CHOICE {
                         provideLocationInformation-r9   ProvideLocationInformation-r9-IEs,
                         spare3 NULL, spare2 NULL, spare1 NULL
                     },
                     criticalExtensionsFuture    SEQUENCE {}
                 }
             }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeProvideLocInfo
(
    LPP_MESSAGE_PROVIDE_LOCATION_INFO_STRU                 *pstProLocInfo,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*编码choice项*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstProLocInfo->ulChoice));

    switch(pstProLocInfo->ulChoice)
    {
        case LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN:
            usRslt = NAS_LPP_EncodeExtProvideLocationInfo(&(pstProLocInfo->u.stC1),
                                                             pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :
 Description     : 编码
 Input           :       需要编码的LPP消息
                                     编码之后码流的总的BIT数
                               编码之后存放的buf
 Asn             :
 CommonIEsAbort ::= SEQUENCE {
     abortCause          ENUMERATED {
         undefined,
         stopPeriodicReporting,
         targetDeviceAbort,
         networkAbort,
         ...
     }



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCommonIEsAbort
(
    LPP_COMMON_IES_ABORT_STRU          *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码枚举扩展项*/
    if((NAS_LPP_SLCT == pstAbortMessage->bitOpCommonIEsAbortExt)
     ||(pstAbortMessage->enCommonIesAbortCasue > 3))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_COMMONIESABORT_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return      NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, 0);

    /*编码枚举值*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 2,
                              (VOS_UINT8)(pstAbortMessage->enCommonIesAbortCasue));
    return  NAS_LPP_ENCODE_SUCC;

}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeEpduAbort
 Description     : 编码LPP_EPDU_SEQUENCE_STRU
 Input           :       需要编码的LPP消息
                                     编码之后码流的总的BIT数
                               编码之后存放的buf
 Asn             :



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEpduAbort
(
    LPP_EPDU_SEQUENCE_STRU             *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    usRslt = NAS_LPP_EncodeEPDUSequence( pstAbortMessage, pusBitPos, pucEncodeOutMsg);
    return  usRslt;

}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeAbortR9IEs
 Description     : 编码
 Input           : pstAbortMessage            需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
 Abort-r9-IEs ::= SEQUENCE {
     commonIEsAbort      CommonIEsAbort          OPTIONAL,   -- Need ON
     ...,
     epdu-Abort          EPDU-Sequence           OPTIONAL    -- Need ON
 }



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAbortR9IEs
(
    LPP_ABORT_R9_IES_STRU              *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt                  = 0;
    VOS_UINT16                          usEncodeTempLen         = 0;
    VOS_UINT16                          usCurrentBitPos         = 0;
    VOS_UINT8                           ucByteNum               = 0;
    VOS_UINT8                           ucAddtionalBitNum       = 0;

    /*编码扩展项标志位*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstAbortMessage->bitOpAbortR9IEsExt));

    /*编码OPTIONAL项标志位*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstAbortMessage->bitOpCommonIesAbort));

    /*编码结构体内容*/
    if(NAS_LPP_SLCT == pstAbortMessage->bitOpCommonIesAbort)
    {
        usRslt = NAS_LPP_EncodeCommonIEsAbort(&(pstAbortMessage->stCommonIesAbort),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    /*编码扩展项*/
    if(NAS_LPP_NO_SLCT == pstAbortMessage->bitOpAbortR9IEsExt)
    {
        return  NAS_LPP_ENCODE_SUCC;
    }
    /*编码扩展项个数 L-1*/
    /*L 为 1*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 7, 0);

    /*编码扩展项标志位*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstAbortMessage->bitOpEpduAbort));

    /*先跳过L+V的编码，先编码内容，然后计算长度，再编码L+V字节数*/
    if(NAS_LPP_SLCT == pstAbortMessage->bitOpEpduAbort)
    {
        usCurrentBitPos = *pusBitPos;
        *pusBitPos +=8;
        usRslt = NAS_LPP_EncodeEpduAbort(&(pstAbortMessage->stEpduAbort), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        };
        usEncodeTempLen = *pusBitPos - usCurrentBitPos - 8;
        if(usEncodeTempLen / 8 > 128)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_EPDU_SEQUENCE, NAS_LPP_EPDU_SEQUENCE_LEN_ERROR, *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_EPDU_ERROR_VALUE_ERROR;
        }

        if((usEncodeTempLen % 8) == 0)
        {
            ucByteNum = (VOS_UINT8)(usEncodeTempLen / 8);
        }
        else
        {
            ucAddtionalBitNum = 8 - (usEncodeTempLen % 8);
            NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, ucAddtionalBitNum, 0);
            ucByteNum = (VOS_UINT8)(usEncodeTempLen / 8 + 1);
        }
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, &(usCurrentBitPos), 8, ucByteNum);
    }

    return  NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeC1ExtAbortMessage
 Description     : 编码LPP_C1_EXT_ABORT_STRU
 Input           : pstAbortMessage      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :

 c1                      CHOICE {
                 abort-r9        Abort-r9-IEs,
                 spare3 NULL, spare2 NULL, spare1 NULL
             }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeC1ExtAbortMessage
(
    LPP_C1_EXT_ABORT_STRU              *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码choice项*/
    /*两个choice项，所以用一个bit表示即可*/
    if(pstAbortMessage->ulChoice > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_C1EXTABORTMESSAGE_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                            ((VOS_UINT8)(pstAbortMessage->ulChoice)));

    switch(pstAbortMessage->ulChoice)
    {
        case LPP_C1_CRITI_EXT_ABORT_R9_CHOSEN:
            usRslt = NAS_LPP_EncodeAbortR9IEs(&(pstAbortMessage->u.stAbortR9),
                                                 pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return  usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeExtAbortMessage
 Description     : 编码LPP_CRIT_EXT_ABORT_STRU
 Input           : pstAbortMessage      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         criticalExtensions      CHOICE {
                     c1                      CHOICE {
                         abort-r9        Abort-r9-IEs,
                         spare3 NULL, spare2 NULL, spare1 NULL
                     },
                     criticalExtensionsFuture    SEQUENCE {}
                 }
             }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeExtAbortMessage(
                                LPP_CRIT_EXT_ABORT_STRU                    *pstAbortMessage,
                                VOS_UINT16                                  *pusBitPos,
                                VOS_UINT8                                   *pucEncodeOutMsg)
{
    VOS_UINT16       usRslt = 0;

    /*编码choice项*/
    /*两个choice项，所以用一个bit表示即可*/
    if(pstAbortMessage->ulChoice > 1)
    {
        NAS_LPP_ENCODE_WARNING;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EXTABORTMESSAGE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, ((VOS_UINT8)(pstAbortMessage->ulChoice)));

    switch(pstAbortMessage->ulChoice)
    {
        case LPP_CRITI_EXT_ABORT_CHOSEN:
            usRslt = NAS_LPP_EncodeC1ExtAbortMessage(&(pstAbortMessage->u.stAbortExtC1),
                                                        pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return  usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAbortMessage
 Description     : 编码LPP_MESSAGE_ABORT_STRU
 Input           : pstProvideCapabilty      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         Abort ::= SEQUENCE {
                 criticalExtensions      CHOICE {
                     c1                      CHOICE {
                         abort-r9        Abort-r9-IEs,
                         spare3 NULL, spare2 NULL, spare1 NULL
                     },
                     criticalExtensionsFuture    SEQUENCE {}
                 }
             }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAbortMessage
(
    LPP_MESSAGE_ABORT_STRU             *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    usRslt = NAS_LPP_EncodeExtAbortMessage(&(pstAbortMessage->stC1), pusBitPos,pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return  usRslt;
    };
    return  NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :
 Description     : 编码
 Input           :       需要编码的LPP消息
                                     编码之后码流的总的BIT数
                               编码之后存放的buf
 Asn             :
 CommonIEsError ::= SEQUENCE {
     errorCause      ENUMERATED {
         undefined,
         lppMessageHeaderError,
         lppMessageBodyError,
         epduError,
         incorrectDataValue,
         ...
     }



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCommonIEsError
(
    LPP_COMMON_IES_ERROR_STRU          *pstErrorMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*编码枚举扩展项*/
    if((NAS_LPP_SLCT == pstErrorMessage->bitOpCommonIEsErrorExt)
     ||(pstErrorMessage->enCommonIesErrorCasue > 4))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_COMMONIESERROR_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return      NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, 0);
    /*编码枚举值*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 3,
                              (VOS_UINT8)(pstErrorMessage->enCommonIesErrorCasue));
    return  NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :
 Description     : 编码
 Input           :       需要编码的LPP消息
                                     编码之后码流的总的BIT数
                               编码之后存放的buf
 Asn             :



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEpduError
(
    LPP_EPDU_SEQUENCE_STRU             *pstErrorMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    usRslt = NAS_LPP_EncodeEPDUSequence( pstErrorMessage, pusBitPos, pucEncodeOutMsg);
    return  usRslt;

}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeErrorR9IEs
 Description     : 编码LPP_ERROR_R9_STRU
 Input           :       需要编码的LPP消息
                                     编码之后码流的总的BIT数
                               编码之后存放的buf
 Asn             :

 Error-r9-IEs ::= SEQUENCE {
         commonIEsError      CommonIEsError          OPTIONAL,   -- Need ON
         ...,
         epdu-Error          EPDU-Sequence           OPTIONAL    -- Need ON
     }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeErrorR9IEs
(
    LPP_ERROR_R9_STRU                  *pstErrorMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;
    VOS_UINT16                          usEncodeTempLen     = 0;
    VOS_UINT16                          usCurrentBitPos     = 0;
    VOS_UINT8                           ucByteNum           = 0;
    VOS_UINT8                           ucAddtionalBitNum   = 0;

    /*编码扩展项标志位*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstErrorMessage->bitOpErrorR9IEsExt));

    /*编码OPTIONAL项标志位*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstErrorMessage->bitOpCommonIesError));

    /*编码结构体内容*/
    if(NAS_LPP_SLCT == pstErrorMessage->bitOpCommonIesError)
    {
        usRslt = NAS_LPP_EncodeCommonIEsError(&(pstErrorMessage->stCommonIesError),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    /*编码扩展项*/
    if(NAS_LPP_NO_SLCT == pstErrorMessage->bitOpErrorR9IEsExt)
    {
        return  NAS_LPP_ENCODE_SUCC;
    }
    /*编码扩展项个数 L-1*/
    /*L 为 1*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 7, 0);

    /*编码扩展项标志位*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstErrorMessage->bitOpEpduError));

    /*先跳过L+V的编码，先编码内容，然后计算长度，再编码L+V字节数*/
    if(NAS_LPP_SLCT == pstErrorMessage->bitOpEpduError)
    {
        usCurrentBitPos = *pusBitPos;
        *pusBitPos +=8;
        usRslt = NAS_LPP_EncodeEpduError(&(pstErrorMessage->stEpduError), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        };

        usEncodeTempLen = *pusBitPos - usCurrentBitPos - 8;
        if((usEncodeTempLen % 8) == 0)
        {
            ucByteNum = (VOS_UINT8)(usEncodeTempLen / 8);
        }
        else
        {
            ucAddtionalBitNum = 8 - (usEncodeTempLen % 8);
            NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, ucAddtionalBitNum, 0);
            ucByteNum = (VOS_UINT8)(usEncodeTempLen / 8 + 1);
        }
        if(ucByteNum > 128)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_ERRORR9IES_ERROR, NAS_LPP_EPDU_SEQUENCE_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_EPDU_ERROR_VALUE_ERROR;
        }

        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, &(usCurrentBitPos), 8, ucByteNum);
    }
    return  NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeErrorMessage
 Description     : 编码LPP_MESSAGE_ABORT_STRU
 Input           : pstProvideCapabilty      需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :

 Error ::= CHOICE {
         error-r9                    Error-r9-IEs,
         criticalExtensionsFuture    SEQUENCE {}
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeErrorMessage
(
    LPP_MESSAGE_ERROR_STRU              *pstErrorMessage,
    VOS_UINT16                          *pusBitPos,
    VOS_UINT8                           *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt = 0;

    /*编码choice项*/
    /*两个choice项，所以用一个bit表示即可*/
    if(pstErrorMessage->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ERRORMESSAGE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, ((VOS_UINT8)(pstErrorMessage->ulChoice)));

    switch(pstErrorMessage->ulChoice)
    {
        case LPP_ERROR_R9_IES_CHOSEN:
            usRslt = NAS_LPP_EncodeErrorR9IEs( &(pstErrorMessage->u.stErrorR9), pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC !=usRslt)
            {
                return  usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLppMsgC1
 Description     : 编码具体的LPP消息
 Input           : pstSupportLppMsgBody     需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         c1                      CHOICE {
             requestCapabilities         RequestCapabilities,
             provideCapabilities         ProvideCapabilities,
             requestAssistanceData       RequestAssistanceData,
             provideAssistanceData       ProvideAssistanceData,
             requestLocationInformation  RequestLocationInformation,
             provideLocationInformation  ProvideLocationInformation,
             abort                       Abort,
             error                       Error,
             spare7 NULL, spare6 NULL, spare5 NULL, spare4 NULL,
             spare3 NULL, spare2 NULL, spare1 NULL, spare0 NULL
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLppMsgC1
(
    LPP_SUPPORT_MESSAGE_BODY_STRU      *pstSupportLppMsgBody,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码choice项*/
    /*16个choice项，所以需要用4个bit表示*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)(pstSupportLppMsgBody->ulChoice));
    /*编码消息体*/
    switch(pstSupportLppMsgBody->ulChoice)
    {
        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_CAPABILITIES_CHOSEN:
            usRslt = NAS_LPP_EncodeProvideCapability(&(pstSupportLppMsgBody->u.stProvideCapabilities),
                                                        pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
        case LPP_SUPPORT_MESSAGE_BODY_PEQUEST_ASSISTANCE_DATA_CHOSEN:
            usRslt = NAS_LPP_EncodeRequestAssistData(&(pstSupportLppMsgBody->u.stRequestAssistanceData), pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_LOCATION_INFO_CHOSEN:
            usRslt = NAS_LPP_EncodeProvideLocInfo(&(pstSupportLppMsgBody->u.stProvideLocationInformation),
                                                     pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
        case LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN:
            usRslt = NAS_LPP_EncodeAbortMessage(&(pstSupportLppMsgBody->u.stAbort),
                                                   pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
        case LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN:
            usRslt = NAS_LPP_EncodeErrorMessage(&(pstSupportLppMsgBody->u.stError),
                                                   pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

            /*FIXME:LIFUXIN ToDo继续添加其他待编码的数据*/

        default:
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_LPPMSGC1_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;

    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLppMsgBody
 Description     : 需要编码的lpp消息总体结构
 Input           : pstLppMsgBody            需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         LPP-MessageBody ::= CHOICE {
             c1                      CHOICE {
                 requestCapabilities         RequestCapabilities,
                 provideCapabilities         ProvideCapabilities,
                 requestAssistanceData       RequestAssistanceData,
                 provideAssistanceData       ProvideAssistanceData,
                 requestLocationInformation  RequestLocationInformation,
                 provideLocationInformation  ProvideLocationInformation,
                 abort                       Abort,
                 error                       Error,
                 spare7 NULL, spare6 NULL, spare5 NULL, spare4 NULL,
                 spare3 NULL, spare2 NULL, spare1 NULL, spare0 NULL
             },
             messageClassExtension   SEQUENCE {}
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLppMsgBody
(
    LPP_MESSAGE_BODY_STRU              *pstLppMsgBody,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*编码choice项*/
    /*两个choice项，所以用一个bit表示即可*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstLppMsgBody->ulChoice));

    switch(pstLppMsgBody->ulChoice)
    {
        case LPP_C1_MESSAGE_BODY_CHOSEN:
            usRslt = NAS_LPP_EncodeLppMsgC1(&(pstLppMsgBody->u.stC1), pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_C1_MESSAGE_CLASS_EXTENSION:
            break;

        default:
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_LPPMSGBODY_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;

    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeMessage
 Description     : LPP上行消息编码入口函数
 Input           : pstLppMsg     需要编码的LPP消息
                   pusBitPos       编码之后码流的总的BIT数
                   pucEncodeOutMsg 编码之后存放的buf
 Asn             :

 LPP-Message ::= SEQUENCE {
     transactionID           LPP-TransactionID   OPTIONAL,   -- Need ON
     endTransaction          BOOLEAN,
     sequenceNumber          SequenceNumber      OPTIONAL,   -- Need ON
     acknowledgement         Acknowledgement     OPTIONAL,   -- Need ON
     lpp-MessageBody         LPP-MessageBody     OPTIONAL    -- Need ON
 }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982      2015-04-28  Draft Enact
*****************************************************************************/
VOS_UINT16  NAS_LPP_EncodeMessage
(
    LPP_MESSAGE_STRU                   *pstLppMsg,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucOption        = 0;
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT8                           ucAllignBit     = 0;

    if((NAS_LPP_NULL_PTR == pstLppMsg)
        || (NAS_LPP_NULL_PTR == pusBitPos)
        || (NAS_LPP_NULL_PTR == pucEncodeOutMsg))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_MESSAGE_ERROR, NAS_LPP_EMPTY_POINT, 0, __LINE__, 0);
        return NAS_LPP_ENCODE_NULL_PTR;
    }

    /*到这里码流从计数为0*/
    *pusBitPos = 0;

    /*编码可选项*/
    ucOption = (VOS_UINT8)(((pstLppMsg->bitOpLppTransactionId) << 3)
                | ((pstLppMsg->bitOpSequenceNumber) << 2)
                | ((pstLppMsg->bitOpAcknowledgement) << 1)
                | (pstLppMsg->bitOpLppMessageBody));

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, ucOption);

    /*编码transactionId*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpLppTransactionId)
    {
        usRslt = NAS_LPP_EncodeTransactionId(&(pstLppMsg->stTransactionId), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码endTransaction*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstLppMsg->bEndTransaction));

    /*编码SequenceNumber*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpSequenceNumber)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, pstLppMsg->stSequenceNumber.ucSequenceNumber);
    }

    /*编码acknowledgement*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpAcknowledgement)
    {
        usRslt = NAS_LPP_EncodeAcknowLedgement(&(pstLppMsg->stAcknowledgement), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码LPP主体消息*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpLppMessageBody)
    {
        usRslt = NAS_LPP_EncodeLppMsgBody(&(pstLppMsg->stLppMessageBody), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*编码完成之后，保证8bit对齐*/
    ucAllignBit = (*pusBitPos) % 8;
    if(0 != ucAllignBit)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (8 - ucAllignBit), 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLocInfoEllipsoidPoint
 Description     : 编码stEllipsoidPoint
 Input           : pstEllipsoidPoint        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
    locationCoordinates-r10         CHOICE{
    ellipsoid-Point-r10     OCTET   STRING,
    ellipsoidPointWithAltitude-r10  OCTET STRING,
    ...,
    ellipsoidPointWithUncertaintyCircle-r11     OCTET STRING,
    ellipsoidPointWithUncertaintyEllipse-r11    OCTET STRING,
    ellipsoidPoinWithAltitudeAndUncertaintyEllipsoid-r11    OCTET STRING,
    ellipsoidArc-r11                            OCTET STRING,
    polygon-r11                                 OCTET STRING,
    }
         Ellipsoid-Point ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863    2015-10-21  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_EncodeLocInfoEllipsoidPoint
(
    LPP_ELLIPSOID_POINT_STRU           *pstEllipsoidPoint,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{

    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstEllipsoidPoint->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23,
                                  pstEllipsoidPoint->ulDegreeLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidPoint->lDegreesLongitude + 8388608));
    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLocInfoEllipsoidPointWithUncertaintyCircle
 Description     : 编码stEllipsoidPoint
 Input           : pstEllipsoidPoint        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
    locationCoordinates-r10         CHOICE{
    ellipsoid-Point-r10     OCTET   STRING,
    ellipsoidPointWithAltitude-r10  OCTET STRING,
    ...,
    ellipsoidPointWithUncertaintyCircle-r11     OCTET STRING,
    ellipsoidPointWithUncertaintyEllipse-r11    OCTET STRING,
    ellipsoidPoinWithAltitudeAndUncertaintyEllipsoid-r11    OCTET STRING,
    ellipsoidArc-r11                            OCTET STRING,
    polygon-r11                                 OCTET STRING,
    }
         Ellipsoid-Point ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863    2015-10-21  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_EncodeLocInfoEllipsoidPointWithUncertaintyCircle
(
    LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU           *pstEllipsoidPointWithCircle,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{

    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipsoidPointWithCircle->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstEllipsoidPointWithCircle->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24, (VOS_UINT32)(pstEllipsoidPointWithCircle->lDegreeLongitude + 8388608));

    /*编码uncertainty*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstEllipsoidPointWithCircle->ulUncretainty));

    /* 补齐bit 数到整字节 */
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,0);

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLocInfoEllipsoidPointWithUncertaintyEllipse
 Description     : 编码EllipsoidPointWithUncertaintyEllipse
 Input           : pstEllipsoidPointWithUncertaintyEllipse        需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         EllipsoidPointWithUncertaintyEllipse ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
             uncertaintySemiMajor        INTEGER (0..127),
             uncertaintySemiMinor        INTEGER (0..127),
             orientationMajorAxis        INTEGER (0..179),
             confidence                  INTEGER (0..100)
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863    2015-10-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLocInfoEllipsoidPointWithUncertaintyEllipse
(
    LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU      *pstEllipsoidPointWithUncertaintyEllipse,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg)
{
    LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU      *pstTempStru = pstEllipsoidPointWithUncertaintyEllipse;

    if ( pstTempStru->enLatitudeSign > 1 )
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstTempStru->ulDegreesLatitude > 8388607) || (pstTempStru->ucUncertaintySemiMajor > 127) ||
         (pstTempStru->ucUncertaintySemiMinor > 127) || (pstTempStru->ucOrientationMajorAxis >179)
       ||(pstTempStru->ucConfidence >100)||((pstTempStru->lDegreesLongitude >8388607)
       ||(pstTempStru->lDegreesLongitude < -8388608)))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1,
                             (VOS_UINT8)(pstEllipsoidPointWithUncertaintyEllipse->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23,
                                  pstEllipsoidPointWithUncertaintyEllipse->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidPointWithUncertaintyEllipse->lDegreesLongitude + 8388608));

    /*编码uncertaintySemiMajor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7,
                              pstEllipsoidPointWithUncertaintyEllipse->ucUncertaintySemiMajor);

    /*编码uncertaintySemiMinor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7,
                              pstEllipsoidPointWithUncertaintyEllipse->ucUncertaintySemiMinor);

    /*编码orientationMajorAxis*/
    if(pstEllipsoidPointWithUncertaintyEllipse->ucUncertaintySemiMinor > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipsoidPointWithUncertaintyEllipse->ucOrientationMajorAxis);

    /*编码confidence*/
    if(pstEllipsoidPointWithUncertaintyEllipse->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7,
                              pstEllipsoidPointWithUncertaintyEllipse->ucConfidence);

    /* 补齐bit 数到整字节 */
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3,0);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLocInfoPolygon
 Description     : 编码Polygon
 Input           : pstPolygon               需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         Polygon ::= SEQUENCE (SIZE (3..15)) OF PolygonPoints

         PolygonPoints ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607)     -- 24 bit field
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.lifuxin 00253982    2015-6-2  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLocInfoPolygon
(
    LPP_POLYGON_STRU                   *pstPolygon,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;
    VOS_UINT32                          ulLoop              = 0;
    VOS_UINT8                           ucLessByteBitNum    = 0;
    VOS_UINT8                           ucFillInBitNum      = 0;

    /*编码结构体计数值*/
    if ( ((pstPolygon->ulPolygonCnt) < 3) || ((pstPolygon->ulPolygonCnt) > 15))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_POLYGON_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 4, (VOS_UINT8)((pstPolygon->ulPolygonCnt) - 3));

    /*编码结构体实体*/
    for(ulLoop = 0; ulLoop < pstPolygon->ulPolygonCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodePolygonPoints(&(pstPolygon->astPolygonArray[ulLoop]),
                                                pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }
    ucLessByteBitNum = *pusBitPos % 8;
    if (0 == ucLessByteBitNum)
    {
        return NAS_LPP_ENCODE_SUCC;
    }
    ucFillInBitNum   = 8 - ucLessByteBitNum;

    /* 补齐bit 数到整字节 */
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, ucFillInBitNum, 0);

    return NAS_LPP_ENCODE_SUCC;

}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLocInfoEllipsoidPointWithaltitude
 Description     : 编码EllipsoidPointWithAltitude
 Input           : pstEllipsoidPointWithAltitude  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         EllipsoidPointWithAltitude ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
             altitudeDirection           ENUMERATED {height, depth},
             altitude                    INTEGER (0..32767)              -- 15 bit field
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863    2015-10-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLocInfoEllipsoidPointWithaltitude
(
    LPP_ELLIPSOID_POINT_WITH_ALTITUDE_STRU                 *pstEllipsoidPointWithAltitude,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    if((pstEllipsoidPointWithAltitude->enLatitudeSign >1)||(pstEllipsoidPointWithAltitude->enAltitudeDirection > 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstEllipsoidPointWithAltitude->lDegreesLatitude > 8388607)
       ||(pstEllipsoidPointWithAltitude->lDegreesLatitude < -8388608)
       ||(pstEllipsoidPointWithAltitude->ulDegreesLatitude > 8388607)
       ||(pstEllipsoidPointWithAltitude->usAltitude > 32767))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_INTEGER, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstEllipsoidPointWithAltitude->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23,
                                  pstEllipsoidPointWithAltitude->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidPointWithAltitude->lDegreesLatitude + 8388608));

    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstEllipsoidPointWithAltitude->enAltitudeDirection));

    /*编码tltitude*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg,  pusBitPos,  15,
                                   pstEllipsoidPointWithAltitude->usAltitude);

    return NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLocInfoEllipsoidPointWithAltitudeAndEllipoid
 Description     : 编码EllipsoidPointWithAltitudeAndUncertaintyEllipsoid
 Input           : pstEllipPointAndUncertEllip  需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         EllipsoidPointWithAltitudeAndUncertaintyEllipsoid ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
             altitudeDirection           ENUMERATED {height, depth},
             altitude                    INTEGER (0..32767),             -- 15 bit field
             uncertaintySemiMajor        INTEGER (0..127),
             uncertaintySemiMinor        INTEGER (0..127),
             orientationMajorAxis        INTEGER (0..179),
             uncertaintyAltitude         INTEGER (0..127),
             confidence                  INTEGER (0..100)
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863    2015-10-26  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLocInfoEllipsoidPointWithAltitudeAndEllipoid
(
    LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU    *pstEllipPointAndUncertEllip,
    VOS_UINT16                                                          *pusBitPos,
    VOS_UINT8                                                           *pucEncodeOutMsg
)
{
    LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU    *pstTempStru = pstEllipPointAndUncertEllip;
    if((pstTempStru->enAltitudeDirection > 1)||(pstTempStru->enLatitudeSign > 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstTempStru->ucConfidence > 100)
       ||(pstTempStru->ucOrientationMajorAxis > 179)
       ||(pstTempStru->ucUncertaintyAltitude > 127)
       ||(pstTempStru->ucUncertaintySemiMajor > 127)
       ||(pstTempStru->ucUncertaintySemiMinor > 127)
       ||(pstEllipPointAndUncertEllip->lDegreesLongtitude > 8388607)
       ||(pstEllipPointAndUncertEllip->lDegreesLongtitude < -8388608)
       ||(pstEllipPointAndUncertEllip->usAltitude > 32767))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipPointAndUncertEllip->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstEllipPointAndUncertEllip->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24, (VOS_UINT32)(pstEllipPointAndUncertEllip->lDegreesLongtitude + 8388608));

    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipPointAndUncertEllip->enAltitudeDirection));

    /*编码tltitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 15, pstEllipPointAndUncertEllip->usAltitude);

    /*编码ucUncertaintySemiMajor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstEllipPointAndUncertEllip->ucUncertaintySemiMajor));

    /*编码uncertaintySemiMinor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstEllipPointAndUncertEllip->ucUncertaintySemiMinor));

    /*编码orientationMajorAxis*/
    if ( pstEllipPointAndUncertEllip->ucUncertaintySemiMinor > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipPointAndUncertEllip->ucOrientationMajorAxis);

    /*编码uncertaintyAltitude*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipPointAndUncertEllip->ucUncertaintyAltitude);

    /*编码confidence*/
    if ( pstEllipPointAndUncertEllip->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipPointAndUncertEllip->ucConfidence);

    /* 补齐4bit 数到整字节 */
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 4, 0);

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeLocInfoEllipsoidArc
 Description     : 编码EllipsoidArc
 Input           : pstEllipsoidArc          需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
 Asn             :
         EllipsoidArc ::= SEQUENCE {
             latitudeSign                ENUMERATED {north, south},
             degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
             degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
             innerRadius                 INTEGER (0..65535),             -- 16 bit field,
             uncertaintyRadius           INTEGER (0..127),
             offsetAngle                 INTEGER (0..179),
             includedAngle               INTEGER (0..179),
             confidence                  INTEGER (0..100)
         }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863    2015-10-26  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLocInfoEllipsoidArc
(
    LPP_ELLIPSOIDARC_STRU              *pstEllipsoidArc,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    if(pstEllipsoidArc->enLatitudeSign > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if((pstEllipsoidArc->lDegreesLongtitude > 8388607)
     || (pstEllipsoidArc->lDegreesLongtitude < -8388608)
     || (pstEllipsoidArc->ucConfidence > 100)
     || (pstEllipsoidArc->ucIncludedAngle > 179)
     || (pstEllipsoidArc->ucOffsetAngle > 179)
     || (pstEllipsoidArc->ucUncertaintyRadius > 127)
     || (pstEllipsoidArc->ulDegreesLatitude > 8388607)
     || (pstEllipsoidArc->ulInnerRadius > 65535))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*编码latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipsoidArc->enLatitudeSign));

    /*编码degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstEllipsoidArc->ulDegreesLatitude);

    /*编码degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidArc->lDegreesLongtitude + 8388608));

    /*编码innerRadius*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg,  pusBitPos, 16, pstEllipsoidArc->ulInnerRadius);

    /*编码uncertaintyRadius*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipsoidArc->ucUncertaintyRadius);

    /*编码offsetAngle*/
    if(pstEllipsoidArc->ucOffsetAngle > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipsoidArc->ucOffsetAngle);

    /*编码includedAngle*/
    if(pstEllipsoidArc->ucIncludedAngle > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipsoidArc->ucIncludedAngle);

    /*编码confidence*/
    if(pstEllipsoidArc->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipsoidArc->ucConfidence);

    /* 补2bit 数到整字节 */
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 2, 0);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_LRrc_Encode_LocationCoordinates
 Description     : 编码pstLocationCoordinates(完成两个结构的映射)
 Input           : LOC_COM_COORDINATE_STRU                    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf
locationInfo-r10 ::=SEQUENCE{
    locationCoordinates-r10         CHOICE{
    ellipsoid-Point-r10     OCTET   STRING,
    ellipsoidPointWithAltitude-r10  OCTET STRING,
    ...,
    ellipsoidPointWithUncertaintyCircle-r11     OCTET STRING,
    ellipsoidPointWithUncertaintyEllipse-r11    OCTET STRING,
    ellipsoidPoinWithAltitudeAndUncertaintyEllipsoid-r11    OCTET STRING,
    ellipsoidArc-r11                            OCTET STRING,
    polygon-r11                                 OCTET STRING,
    }
}

 LocationCoordinates ::= CHOICE {
     ellipsoidPoint                              Ellipsoid-Point,
     ellipsoidPointWithUncertaintyCircle         Ellipsoid-PointWithUncertaintyCircle,
     ellipsoidPointWithUncertaintyEllipse        EllipsoidPointWithUncertaintyEllipse,
     polygon                                     Polygon,
     ellipsoidPointWithAltitude                  EllipsoidPointWithAltitude,
     ellipsoidPointWithAltitudeAndUncertaintyEllipsoid
                                                 EllipsoidPointWithAltitudeAndUncertaintyEllipsoid,
     ellipsoidArc                                EllipsoidArc,
     ...
 }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-07-1  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeLocationInfo
(
    LOC_COM_COORDINATE_STRU                                *pstLocationCommonCoordinate,
    LPP_LRRC_LOCATION_COORDINATES_DATA_STRU                *pstLocationCoordinate
)
{
    VOS_UINT16                          usRslt        = NAS_LPP_ENCODE_FAIL;
    VOS_UINT16                          usBitPosition = 0;
    /*编码结构体数据*/
    switch(pstLocationCommonCoordinate->ulChoice)
    {
        case LOC_COM_ELLIPSOID_POINT_CHOSEN:

            /* 给RRC的结构中，此结构有扩展项，与空口消息有所不同,此结构编码后的码流长度为6 */
            pstLocationCoordinate->enLocationCoordinatesType =
                                LPP_LRRC_LOC_COOR_ELLIP_POINT;
            NAS_LPP_EncodeLocInfoEllipsoidPoint(&(pstLocationCommonCoordinate->u.stEllipsoidPoint),
                                                &usBitPosition,
                                                pstLocationCoordinate->aucLocationCoordinatesData);
            pstLocationCoordinate->usLocationCoordinatesDataLen =
                                LPP_ELLIPSOID_POINT_LEN;
            break;

        case LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_CHOSEN:

            /* 给RRC的结构中，此结构有扩展项，与空口消息有所不同,此结构编码后的码流长度为7 */
            pstLocationCoordinate->enLocationCoordinatesType =
                                LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_UNCERTAIN_CIRCLE;
            NAS_LPP_EncodeLocInfoEllipsoidPointWithUncertaintyCircle(&(pstLocationCommonCoordinate->u.stEllipsoidPointWithUncertaintyCircle),
                                                                     &usBitPosition,
                                                                     pstLocationCoordinate->aucLocationCoordinatesData);
            pstLocationCoordinate->usLocationCoordinatesDataLen =
                                LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_LEN;
            break;

        case LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_CHOSEN:
            pstLocationCoordinate->enLocationCoordinatesType =
                                LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_UNCERTAIN_ELLIPS;
            usRslt = NAS_LPP_EncodeLocInfoEllipsoidPointWithUncertaintyEllipse(&(pstLocationCommonCoordinate->u.stEllipsoidPointWithUncertaintyEllipse),
                                                                               &usBitPosition,
                                                                               pstLocationCoordinate->aucLocationCoordinatesData);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            pstLocationCoordinate->usLocationCoordinatesDataLen =
                                LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_LEN;
            break;

        case LOC_COM_POLYGON_CHOSEN:
            pstLocationCoordinate->enLocationCoordinatesType = LPP_LRRC_LOC_COOR_POLYGON;
            usRslt = NAS_LPP_EncodeLocInfoPolygon(&(pstLocationCommonCoordinate->u.stPolygon),
                                                  &usBitPosition,
                                                  pstLocationCoordinate->aucLocationCoordinatesData);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            pstLocationCoordinate->usLocationCoordinatesDataLen = usBitPosition / 8;
            break;


        case LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_CHOSEN:
            pstLocationCoordinate->enLocationCoordinatesType =
                                LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_ALTI;
            usRslt = NAS_LPP_EncodeLocInfoEllipsoidPointWithaltitude(&(pstLocationCommonCoordinate->u.stEllipsoidPointWithAltitude),
                                                                     &usBitPosition,
                                                                     pstLocationCoordinate->aucLocationCoordinatesData);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            pstLocationCoordinate->usLocationCoordinatesDataLen =
                                LPP_ELLIPSOID_POINT_WITH_ALTITUD_LEN;
            break;

        case LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_CHOSEN:
            pstLocationCoordinate->enLocationCoordinatesType =
                                LPP_LRRC_LOC_COOR_ELLIP_POINT_WITH_ALTI_AND_UNCERTAIN_ELLIPS;
            usRslt = NAS_LPP_EncodeLocInfoEllipsoidPointWithAltitudeAndEllipoid(&(pstLocationCommonCoordinate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid),
                                                                                &usBitPosition,
                                                                                pstLocationCoordinate->aucLocationCoordinatesData);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            pstLocationCoordinate->usLocationCoordinatesDataLen =
                                LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_LEN;
            break;

        default:
            pstLocationCoordinate->enLocationCoordinatesType = LPP_LRRC_LOC_COOR_ELLIP_ARC;
            usRslt = NAS_LPP_EncodeLocInfoEllipsoidArc(&(pstLocationCommonCoordinate->u.stEllipsoidArc),
                                                       &usBitPosition,
                                                       pstLocationCoordinate->aucLocationCoordinatesData);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            pstLocationCoordinate->usLocationCoordinatesDataLen = LPP_ELLIPSOID_ARC_LEND;
            break;
    }

    return  NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeHorizontalLocInfo
 Description     : 编码pstLocationCoordinates
 Input           : LOC_COM_COORDINATE_STRU                    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-07-1  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeHorizontalLocInfo
(
    LOC_COM_VELOCITY_STRU              *pstHorizontalVelocityLocInfo,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usReturnReslt = NAS_LPP_ENCODE_FAIL;
    VOS_UINT16                          usBitPos = 0;
    LOC_COM_HORIZONTAL_VELCOCTIY_STRU   stHorizontalVelocity = {0};

    if ( LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_CHOSEN < pstHorizontalVelocityLocInfo->ulChoice)
    {
        return NAS_LPP_ENCODE_FAIL;
    }
    /*编码结构体数据*/
    switch(pstHorizontalVelocityLocInfo->ulChoice)
    {
        case LOC_COM_HORIZONTAL_VELCOCTIY_CHOSEN:
            stHorizontalVelocity.usBearing = pstHorizontalVelocityLocInfo->u.stHorizontalVelocity.usBearing;
            stHorizontalVelocity.usHorizontalSpeed = pstHorizontalVelocityLocInfo->u.stHorizontalVelocity.usHorizontalSpeed;
            break;

        case LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_CHOSEN:
            stHorizontalVelocity.usBearing = pstHorizontalVelocityLocInfo->u.stHorizontalWithVerticalVelocity.usBearing;
            stHorizontalVelocity.usHorizontalSpeed = pstHorizontalVelocityLocInfo->u.stHorizontalWithVerticalVelocity.usHorizontalSpeed;
            break;

        case LOC_COM_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_CHOSEN:
            stHorizontalVelocity.usBearing = pstHorizontalVelocityLocInfo->u.stHorizontalVelocityWithUncertainty.usBearing;
            stHorizontalVelocity.usHorizontalSpeed = pstHorizontalVelocityLocInfo->u.stHorizontalVelocityWithUncertainty.usHorizontalSpeed;
            break;

        default:
            stHorizontalVelocity.usBearing = pstHorizontalVelocityLocInfo->u.stHorizontalWithVerticalVelocityAndUncertainty.usBearing;
            stHorizontalVelocity.usHorizontalSpeed = pstHorizontalVelocityLocInfo->u.stHorizontalWithVerticalVelocityAndUncertainty.usHorizontalSpeed;
            break;
    }

    usReturnReslt = NAS_LPP_EncodeHorizontalVelcoctiy(&stHorizontalVelocity,&usBitPos,  pucEncodeOutMsg);

    return usReturnReslt;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeHorizontalLocInfo
 Description     : 编码pstLocationCoordinates
 Input           : LOC_COM_COORDINATE_STRU                    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-07-1  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssTodMsecForLocInfo
(
    LPP_MEAS_REF_TIME_STRU             *pstMeasRefTime,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usBitPos = 0;

    if(pstMeasRefTime->ulGNSSTodMsec > 35999)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASREFTIME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                 usBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, &usBitPos, 22, (VOS_UINT32)(pstMeasRefTime->ulGNSSTodMsec));

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeMtaRrcLocInfo
 Description     : 编码pstLocationCoordinates
 Input           : LOC_COM_COORDINATE_STRU                    需要编码的LPP消息
                   pusBitPos                  编码之后码流的总的BIT数
                   pucEncodeOutMsg            编码之后存放的buf

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-07-1  Draft Enact
*****************************************************************************/
VOS_UINT16  NAS_LPP_EncodeRrcLocInfo
(
    MTA_LPP_MEAS_REF_TIME_STRU                             *pstMtaLppMeasRefTime,
    LOC_COM_VELOCITY_STRU                                  *pstVelocityEstimate,
    LOC_COM_COORDINATE_STRU                                *pstLocationEstimate,
    LPP_LRRC_GNSS_DATA_INFO_IND_STRU                       *pstLppLrrcGnssDataInfo
)
{
    VOS_UINT16                          usReturnRslt = NAS_LPP_ENCODE_SUCC;
    /* 如果位置信息存在，则编码 */
    if (NAS_LPP_NULL_PTR != pstLocationEstimate)
    {
        pstLppLrrcGnssDataInfo->ucLocationDataFlag = LPP_LRRC_INFO_FLAG_VALID;
        usReturnRslt = NAS_LPP_EncodeLocationInfo(pstLocationEstimate,
                                                  &pstLppLrrcGnssDataInfo->stLocationCoordinatesData);
        if ( NAS_LPP_ENCODE_SUCC != usReturnRslt )
        {
            return usReturnRslt;
        }
    }

    if (NAS_LPP_NULL_PTR != pstVelocityEstimate)
    {
        pstLppLrrcGnssDataInfo->ucHorizontalVelocityFlag = LPP_LRRC_INFO_FLAG_VALID;
        usReturnRslt = NAS_LPP_EncodeHorizontalLocInfo(pstVelocityEstimate,
                                                        pstLppLrrcGnssDataInfo->aucHorizontalVelocityData);
        if ( NAS_LPP_ENCODE_SUCC != usReturnRslt )
        {
            return usReturnRslt;
        }
    }

    if (NAS_LPP_NULL_PTR != pstMtaLppMeasRefTime)
    {
        pstLppLrrcGnssDataInfo->ucGnssTodMsecFlag = LPP_LRRC_INFO_FLAG_VALID;
        usReturnRslt = NAS_LPP_EncodeGnssTodMsecForLocInfo(pstMtaLppMeasRefTime,
                                                            pstLppLrrcGnssDataInfo->aucGnssTodMsecData);
        if ( NAS_LPP_ENCODE_SUCC != usReturnRslt )
        {
            return usReturnRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

