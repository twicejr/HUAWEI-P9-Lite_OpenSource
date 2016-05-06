/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : NasTafApi.h
  Description : NAS提供给TAF的API函数
  History     :
      1.  张志勇      2003.12.04   新版作成RabmApi.h

*******************************************************************************/

#ifndef _RABM_API_H_
#define _RABM_API_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

extern VOS_VOID Taf_RabmPsDataReqApi(VOS_UINT32 ulDataLen,VOS_UINT8 *pucData,VOS_UINT8 ucNsapi);
extern VOS_VOID Taf_RabmCsDataReqApi(VOS_UINT32 ulDataLen,VOS_UINT8 *pucData,VOS_UINT8 ucSi,VOS_UINT8 ucAmrMode);
extern VOS_VOID Taf_RabmPsDataIndApi(VOS_UINT32 ulDataLen,VOS_UINT8 *pucData,VOS_UINT8 ucNsapi,VOS_UINT32 ulDestAddr);
extern VOS_VOID Taf_RabmCsDataIndApi(VOS_UINT32 ulDataLen,VOS_UINT8 *pucData,VOS_UINT8 ucSi);
extern VOS_VOID Taf_RabmInActNsapiIndApi(VOS_UINT8 ucNsapi);
extern VOS_VOID Taf_RabmInActSiIndApi(VOS_UINT8 ucSi);
extern VOS_VOID Taf_RabmStatusIndApi(VOS_UINT8 ucNsapiOrSi,VOS_UINT8 ucStatusFlg,VOS_UINT8 ucCause);
extern VOS_VOID RABM_TafPsDataCnfApi(VOS_UINT32   ulNsapi);
extern VOS_VOID RABM_TafCsDataCnfApi(VOS_UINT32   ulSi);




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
