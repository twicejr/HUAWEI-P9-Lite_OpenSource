/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SSA_EncodeDef.h
  Author      : ---
  Version     : V200R001
  Date        : 2005-08-16
  Description : 该头文件定义了SSA模块编码函数的接口
  History     :
  1. Date:2005-04-19
     Author: ---
     Modification:Create
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  3.Date:2007-01-19
    Author: h44270
    Modification: 问题单号:A32D08448
  4.Date:2007-04-29
    Author: Li Jilin 60827
    Modification: 问题单号:A32D10708

************************************************************************/

#ifndef _SSA_ENCODEDEF_H_
#define _SSA_ENCODEDEF_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "TafAppSsa.h"
#include "vos.h"
#include "Ssa_Define.h"

#pragma pack(4)

/*对操作中整型参数的编码的宏定义*/
/******************************************************************************************/
/**编码参数ccbs-Index,参见24.080的Annex A的ASN.1的描述*/
#define SSA_EncodeCcbsIndex(pucContent, pucCodeLen, iSrc, TagMode)              SSA_EncodeInt(pucContent, pucCodeLen, iSrc, 5, 1, TagMode)
/*编码参数noReplyConditionTime,参见24.080的Annex A的ASN.1的描述*/
#define SSA_EncodeNoRepCondTime(pucContent, pucCodeLen, iSrc, TagMode)          SSA_EncodeInt(pucContent, pucCodeLen, iSrc, 30, 5, TagMode)
/*编码参数defaultPriority,参见24.080的Annex A的ASN.1的描述*/
#define SSA_EncodeDefaultPriority(pucContent, pucCodeLen, iSrc, TagMode)        SSA_EncodeInt(pucContent, pucCodeLen, iSrc, 15, 0, TagMode)
/*编码参数nbrUser,参见24.080的Annex A的ASN.1的描述*/
#define SSA_EncodeNbrUser(pucContent, pucCodeLen, iSrc, TagMode)                SSA_EncodeInt(pucContent, pucCodeLen, iSrc, 7, 1, TagMode)
/*******************************************************************************************/

/*对操作中字符串类型的参数的编码的宏定义*/
/******************************************************************************************/
/*编码参数alertingPattern参见24.080的Annex A的ASN.1的描述*/
#define SSA_EncodeAlertingPattern(pucContent, pucCodeLen, pucSrc, ucTagMode)        SSA_EncodeString(pucContent, pucCodeLen, pucSrc, 1, ucTagMode)
/*参数ussd-DataCodingScheme的编码，参见24.080 Annex A的ASN.1描述*/
#define SSA_EncodeUssdDataCodingScheme(pucContent, pucCodeLen, pucSrc, ucTagMode)   SSA_EncodeString(pucContent, pucCodeLen, pucSrc, 1, ucTagMode)
/*参数teleService的编码，参见24.080 Annex A的ASN.1描述*/
#define SSA_EncodeTeleService(pucContent, pucCodeLen, pucSrc, ucTagMode)            SSA_EncodeString(pucContent, pucCodeLen, pucSrc, 1, ucTagMode)
/*参数bearerService的编码，参见24.080 Annex A的ASN.1描述*/
#define SSA_EncodeBearerService(pucContent, pucCodeLen, pucSrc, ucTagMode)          SSA_EncodeString(pucContent, pucCodeLen, pucSrc, 1, ucTagMode)
/*参数ss-code的编码，参见24.080 Annex A的ASN.1描述*/
#define SSA_EncodeSsCode(pucContent, pucCodeLen, pucSrc, ucTagMode)                 SSA_EncodeString(pucContent, pucCodeLen, pucSrc, 1, ucTagMode)
/*对IA5 String类型的编码*/
#define SSA_EncodeIa5String(pucContent, pucCodeLen, pucSrc, ucSrcLen, ucTagMode)                 SSA_EncodeString(pucContent, pucCodeLen, pucSrc, ucSrcLen, ucTagMode)

/*******************************************************************************************/

extern VOS_UCHAR  Smt_Put7bits( VOS_UINT8 *pucEncodedMsg,
	                            VOS_UINT32 ulBitAddress,
	                            VOS_UINT8 ucChar );

VOS_UINT32  SSA_EncodeRegisterSSReq(VOS_UINT8                               *pucContent,
                                    VOS_UINT8                               *pucCodeLen,
                                    TAF_SS_REGISTERSS_REQ_STRU              *pSrc);
VOS_UINT32  SSA_EncodeEraseSSReq(VOS_UINT8                                  *pucContent,
                                 VOS_UINT8                                  *pucCodeLen,
                                 TAF_SS_ERASESS_REQ_STRU                    *pSrc);
VOS_UINT32  SSA_EncodeActivateSSReq(VOS_UINT8                               *pucContent,
                                    VOS_UINT8                               *pucCodeLen,
                                    TAF_SS_ACTIVATESS_REQ_STRU              *pSrc);
VOS_UINT32  SSA_EncodeDeactivateSSReq(VOS_UINT8                             *pucContent,
                                      VOS_UINT8                             *pucCodeLen,
                                      TAF_SS_DEACTIVATESS_REQ_STRU          *pSrc);
VOS_UINT32  SSA_EncodeInterrogateSsReq(VOS_UINT8                            *pucContent,
                                       VOS_UINT8                            *pucCodeLen,
                                       TAF_SS_INTERROGATESS_REQ_STRU        *pSrc);
VOS_UINT32  SSA_EncodeRegPwdReq(VOS_UINT8                                   *pucContent,
                                VOS_UINT8                                   *pucCodeLen,
                                TAF_SS_REGPWD_REQ_STRU                      *pSrc);
VOS_UINT32  SSA_EncodeGetPwdRsp(VOS_UINT8                                   *pucContent,
                                VOS_UINT8                                   *pucCodeLen,
                                TAF_SS_GETPWD_RSP_STRU                      *pSrc);
VOS_UINT32  SSA_EncodeProcessUntructuredSSReq(VOS_UINT8                     *pucContent,
                                              VOS_UINT8                     *pucCodeLen,
                                              VOS_UINT8 ucTi);
VOS_UINT32  SSA_EncodeUssData(VOS_UINT8                                     *pucContent,
                              VOS_UINT8                                     *pucCodeLen,
                              TAF_SS_PROCESS_USSDATA_REQ_STRU               *pSrc);

VOS_UINT32  SSA_EncodeUntructuredSSRsp(VOS_UINT8                            *pucContent,
                                       VOS_UINT8                            *pucCodeLen,
                                       TAF_SS_USS_RSP_STRU                  *pSrc);
VOS_UINT32  SSA_EncodeEraseCCEntryReq(VOS_UINT8                             *pucContent,
                                      VOS_UINT8                             *pucCodeLen,
                                      TAF_SS_ERASECC_ENTRY_REQ_STRU         *pSrc);
VOS_UINT32  SSA_EncodeBasicService(VOS_UINT8                                *pucContent,
                                   VOS_UINT8                                *pucCodeLen,
                                   TAF_SS_BASIC_SERVICE_STRU                *pstSrc,
                                   TAG_MODE                                  ucTagMode);
VOS_UINT32  SSA_EncodeForwardedToNumber(VOS_UINT8                           *pucContent,
                                        VOS_UINT8                           *pucCodeLen,
                                        VOS_UINT8                            ucNumType,
                                        VOS_UINT8                           *pucFwdNum,
                                        TAG_MODE                             ucTagMode);
VOS_UINT32  SSA_EncodeForwardedToSubaddress(VOS_UINT8                       *pucContent,
                                            VOS_UINT8                       *pucCodeLen,
                                            VOS_UINT8                        ucSubAddrType,
                                            VOS_UINT8                       *paucFwdToSubAddr,
                                            TAG_MODE                         ucTagMode);
VOS_UINT32  SSA_EncodeUssdString(VOS_UINT8                                  *pucContent,
                                 VOS_UINT8                                  *pucCodeLen,
                                 TAF_SS_USSD_STRING_STRU                    *pSrc,
                                 TAG_MODE                                    ucTagMode);
VOS_UINT32  SSA_EncodeMsisdn(VOS_UINT8                                      *pucContent,
                             VOS_UINT8                                      *pucCodeLen,
                             VOS_UINT8                                      *pucSrc,
                             TAG_MODE                                        ucTagMode);
VOS_VOID    SSA_EncodeProblemCode(VOS_UINT8                                 *pucContent,
                                  VOS_UINT8                                 *pucCodeLen,
                                  VOS_UINT8                                  ucProblemCode);
VOS_VOID    SSA_EncodeOperationCode(VOS_UINT8                               *pucContent,
                                    VOS_UINT8                               *pucCodeLen,
                                    VOS_UINT8                                ucOpCode);
VOS_VOID    SSA_EncodeInvokeId(VOS_UINT8                                    *pucContent,
                               VOS_UINT8                                    *pucCodeLen,
                               VOS_UINT8                                     ucInvokeId);
VOS_VOID    SSA_EncodeComponentType(VOS_UINT8                               *pucContent,
                                    VOS_UINT8                               *pucCodeLen,
                                    VOS_UINT8                                ucComponentTag);

VOS_UINT32  SSA_PackTL(VOS_UINT8                                             ucTag,
                       VOS_UINT8                                            *pucContent,
                       VOS_UINT8                                            *pucCodeLen);
VOS_UINT32  SSA_EncodeNumericString(VOS_UINT8                               *pucCodeContent,
                                    VOS_UINT8                               *pucCodeLen,
                                    VOS_UINT8                               *pucSrc,
                                    VOS_UINT8                                ucSrcLen,
                                    TAG_MODE                                 ucTagMode);
VOS_UINT32  SSA_EncodeIA5String(VOS_UINT8                                   *pucCodeContent,
                                VOS_UINT8                                   *pucCodeLen,
                                VOS_UINT8                                   *pucSrc,
                                VOS_UINT8                                    ucSrcLen,
                                TAG_MODE                                     ucTagMode);
VOS_UINT32  SSA_EncodeInt(VOS_UINT8                                         *pucCodeContent,
                          VOS_UINT8                                         *pucCodeLen,
                          VOS_INT                                            iSrc,
                          VOS_INT                                            iMaxNum,
                          VOS_INT                                            iMiniNum,
                          TAG_MODE                                           TagMode);
VOS_UINT32  SSA_EncodeString(VOS_UINT8                                      *pucCodeContent,
                             VOS_UINT8                                      *pucCodeLen,
                             VOS_UINT8                                      *pucSrc,
                             VOS_UINT8                                       ucSrcLen,
                             TAG_MODE                                        ucTagMode);
VOS_VOID  SSA_EncodeLength(VOS_UINT8                                       ucSrcLen,
                             VOS_UINT8                                      *pucContent,
                             VOS_UINT8                                      *pucCodeLen);
VOS_UINT32  SSA_EncodeOtherString(VOS_UINT8                                  ucTagNum,
                                  VOS_UINT8                                 *pucCodeContent,
                                  VOS_UINT8                                 *pucCodeLen,
                                  VOS_UINT8                           *pucSrc ,
                                  VOS_UINT8                                  ucSrcLen,
                                  TAG_MODE                                   ucTagMode);
VOS_UINT32  SSA_EncodeNullType(VOS_UINT8                                     ucTag,
                               VOS_UINT8                                    *pucContent,
                               VOS_UINT8                                    *pucCodeLen,
                               TAG_MODE                                      ucTagMode);
VOS_UINT32 SSA_AsciiNumToBcdNum(VOS_UINT8                                     *pucAsciiNum,
                              VOS_UINT8                                      ucAsciiNumLen,
                              VOS_UINT8                                     *pucBcdNum,
                              VOS_UINT8                                     *pucBcdNumLen,
                              VOS_UINT8                                     *pucNewNumType); /*A32D10708*/
VOS_VOID Taf_EncodeForwardingInfo(TAF_SS_FORWARDINGINFO_STRU  *pFwdInfo, VOS_UINT8 *pucOuputBuf,
                              VOS_UINT16 *pusLen);
VOS_VOID Taf_EncodeFwdFeaturelist(TAF_SS_FWDFEATURELIST_STRU  *pFwdFeatureList, VOS_UINT8 *pucOutputBuf,
                              VOS_UINT16 *pusLen);
VOS_VOID Taf_EncodeCallbraringInfo(TAF_SS_CALLBRARINGINFO_STRU  *pCallBarInfo, VOS_UINT8 *pucOutputBuf,
                               VOS_UINT16 *pusLen);
VOS_VOID Taf_EncodeCallBarFeaturelist(TAF_SS_CALLBARFEATURELIST_STRU  *pCallBarFeatureList, VOS_UINT8 *pucOuputBuf,
                                  VOS_UINT16 *pusLen);
VOS_VOID Taf_EncodeSsData(TAF_SS_SSDATA_STRU  *pSsData, VOS_UINT8 *pucOuputBuf,
                      VOS_UINT16 *pusLen);
VOS_VOID Taf_EncodeCcbsFeatureList(TAF_SS_CCBS_FEATURELIST_STRU  *pCcBsFeatureList, VOS_UINT8 *pucOuputBuf,
                               VOS_UINT16 *pusLen);
VOS_VOID Taf_EncodeGenericServiceInfo(TAF_SS_GENERIC_SERV_INFO_STRU  *pGenericServInfo, VOS_UINT8 *pucOuputBuf,
                             VOS_UINT16 *pusLen);
VOS_VOID Taf_EncodeSsEventRep(VOS_UINT8  *pucOutbuff, VOS_UINT8  ucMsgType, TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent,
                          VOS_UINT32 ulIeMask, VOS_UINT16 *pusLen);
VOS_VOID SSA_EncodeErrorCode(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT16 usErrCode);
VOS_VOID SSA_EncodeSequenceTag(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of SSA_EncodeDef.h*/
