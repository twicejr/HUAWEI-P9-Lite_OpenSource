/*****************************************************************************

				Copyright (C), 2008, Huawei Tech. Co., Ltd.                
							ALL RIGHTS RESERVED                             

------------------------------------------------------------------------------


FileName     :sec_pki_ctx_ocsp.h
Author       :
Version      :1
Date         :20-04-2010
Description  :OCSP context APIs
Function List: 

History:
<author>   <date>          <desc>
----------------------------------------------------------------------------
****************************************************************************/
#include "ipsi_pse_build_conf.h"

#ifndef IPSI_SEC_NO_PKI
#ifndef __SEC_PKI_NO_OCSP__

#ifndef __SEC_PKI_CTX_OCSP_H__
#define __SEC_PKI_CTX_OCSP_H__

#include "sec_pki_buildconf.h"
#include "ipsi_types.h"
#include "x509_basictypes.h"
#include "sec_crypto.h"
#include "sec_sys.h"
#include "sec_list.h"
#include "sec_pki_def.h"
#include "sec_pki_ocsp_def.h"
#include "x509v3_extn.h"

#ifdef  __cplusplus
extern "C" {
#endif

/** @defgroup OCSP_Validation
* This section contains the OCSP_Validation Functions.
*/



/** @defgroup Context_Function
* @ingroup OCSP_Validation
* This section contains the Context Functions.
*/

/** @defgroup Object_Function
* @ingroup OCSP_Validation
* This section contains the Object Functions.
*/

/**
* @defgroup SEC_PKI_ctxLoadTrustOCSPResponderCertBuffer
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadTrustOCSPResponderCertBuffer(
*                               SEC_PKI_CTX_S *pstContext,
*                               const SEC_CHAR *pcOCSPRespCertBuf,
*                               SEC_UINT uCertBufLen,
*                               SEC_INT iType,
*                               const SEC_CHAR *pcCertPasswd,
*                               SEC_UINT uCertPwdLen,
*                               const SEC_CHAR *pcURL,
*                               SEC_UINT uUrlLen,
*                               SEC_BOOL bAddToOCSPReqList);
*
* @endcode
*
* @par Purpose
* This function is used to load the trusted ocsp responder certificate buffer 
* into the context.
*
* @par Description
* SEC_PKI_ctxLoadTrustOCSPResponderCertBuffer function reads the buffer
* that contains certificate in "PEM","PFX" or "DER" format and adds the
* certificate to the trusted OCSP responder store. Password is an optional 
* input, and it is required only for certificates which are in PFX format. To 
* make this certificate to be part of "Responder certificate Request list"
* user needs to pass bAddToOCSPReqList as true.
*
* @param[in] pstContext Pointer to PKI Context [NA/NA]
* @param[in] pcOCSPRespCertBuf Pointer to OCSP 
* Responder Certificate buffer [NA/NA]
* @param[in] uCertBufLen Responder Certificate buffer length [NA/NA]
* @param[in] iType Responder Certificate buffer type
* [SEC_PKI_FILETYPE_ASN1|SEC_PKI_FILETYPE_PEM|SEC_PKI_FILETYPE_PFX/NA]
* @param[in] pcCertPasswd Pointer to Certificate password. Required only for 
* SEC_PKI_FILETYPE_PFX certificate type.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
* @param[in] pcURL URL of the responder [NA/NA]
* @param[in] uUrlLen URL Length [0-255/NA]
* @param[in] bAddToOCSPReqList indicates 
* whether to be a part of the request list or not [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*	- If a buffer contains more than one certificate,then all certificates
* will be loaded .
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). Any value other than the actual
* buffer length API behaviour is undefined.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*/

PSELINKDLL SEC_INT SEC_PKI_ctxLoadTrustOCSPResponderCertBuffer(
    SEC_PKI_CTX_S *pstContext,
    const SEC_CHAR *pcOCSPRespCertBuf,
    SEC_UINT uCertBufLen,
    SEC_INT iType,
    const SEC_CHAR *pcCertPasswd,
    SEC_UINT uCertPwdLen,
    const SEC_CHAR *pcURL,
    SEC_UINT uUrlLen,
    SEC_BOOL bAddToOCSPReqList);


/**
* @defgroup SEC_PKI_ctxLoadTrustOCSPResponderCertFile
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadTrustOCSPResponderCertFile(
*                               SEC_PKI_CTX_S *pstContext,
*                               const SEC_CHAR *pcOCSPRespCertFile,
*                               SEC_INT iType,
*                               SEC_CHAR *pcCertPasswd,
*                               SEC_UINT uCertPwdLen,
*                               const SEC_CHAR *pcURL,
*                               SEC_UINT uUrlLen,
*                               SEC_BOOL bAddToOCSPReqList);
*
* @endcode
*
* @par Purpose
* This function is used to load the trusted OCSP responder certificate file 
* into the OCSP context.
*
* @par Description
* SEC_PKI_ctxLoadTrustOCSPResponderCertFile function reads a file that
* contains the trusted responder certificate in "PEM","PFX", or "DER" 
* format and adds the certificate to the trusted OCSP responder store. 
* Password is an optional input, and it is needed only for certificates 
* which are in PFX format.
*
* @param[in] pstContext Pointer to PKI Context [NA/NA]
* @param[in] pcOCSPRespCertFile Pointer to OCSP Responder Certificate
* file [NA/NA]
* @param[in] iType Responder Certificate file type
* [SEC_PKI_FILETYPE_ASN1|SEC_PKI_FILETYPE_PEM|SEC_PKI_FILETYPE_PFX/NA]
* @param[in] pcCertPasswd Pointer to Certificate password. Required only for 
* SEC_PKI_FILETYPE_PFX certificate type.[NA/NA]
* @param[in] uCertPwdLen Password Length [0-255/NA]
* @param[in] pcURL URL of the responder.[NA/NA]
* @param[in] uUrlLen URL Length. [0-255/NA]
* @param[in] bAddToOCSPReqList indicates whether to be 
* part of the request list or not. [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*
* @par Note
* \n
*	- If a file contains more than one certificate, all certificates
* will be loaded . 
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadTrustOCSPResponderCertFile(
    SEC_PKI_CTX_S *pstContext,
    const SEC_CHAR *pcOCSPRespCertFile,
    SEC_INT iType,
    const SEC_CHAR *pcCertPasswd,
    SEC_UINT uCertPwdLen,
    const SEC_CHAR *pcURL,
    SEC_UINT uUrlLen,
    SEC_BOOL bAddToOCSPReqList);


/**
* @defgroup SEC_PKI_ctxGetAllTrustOCSPResponderCert
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetAllTrustOCSPResponderCert( SEC_PKI_CTX_S *pstContext,
*                                               SEC_List_S **dpOutCertList);
* @endcode
*
* @par Purpose
* This function is used to get all Responder certificates.
*
* @par Description
* SEC_PKI_ctxGetAllTrustOCSPResponderCert function gets all 
* trusted responder certificates.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] dpOutCertList List which contains all the certs.
* dpOutCertList is a list which holds elements of type X509_CERT_S[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* ipsi will allocate the memory for dpOutCertList (the list may contain one
* or more entries). To free this memory in application, user has to call the
* SEC_LIST_FREE, with the free function as X509_freeCert.
* @par Note
* \n
* Retrival order might not be same as loading order of Certificate.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetAllTrustOCSPResponderCert(
        SEC_PKI_CTX_S *pstContext,
        SEC_List_S **dpOutCertList);


/**
* @defgroup SEC_PKI_ctxRemoveTrustedOCSPResponderCert
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxRemoveTrustedOCSPResponderCert(
*                               SEC_PKI_CTX_S *pstContext,
*                               SEC_NAME_S *pstIssuerName,
*                               SEC_BIGINT_S *pstSerialNum);
* @endcode
*
* @par Purpose
* This function is used to remove the ocsp responder certificate 
* from the trusted store.
*
* @par Description
* SEC_PKI_ctxRemoveTrustedOCSPResponderCert function 
* removes the ocsp responder certificate for which the input issuer name 
* and serial number matches from the trusted store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.
* Issuer name and serial number are unique identifier in RFC.[NA/NA]
* @param[in] pstIssuerName Issuer name of the certificate.[NA/NA]
* @param[in] pstSerialNum Serial number of the certificate.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxRemoveTrustedOCSPResponderCert(
                               SEC_PKI_CTX_S *pstContext,
                               SEC_NAME_S *pstIssuerName,
                               SEC_BIGINT_S *pstSerialNum);


/**
* @defgroup SEC_PKI_ctxSetOCSPConfParam
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxSetOCSPConfParam( SEC_PKI_CTX_S *pstContext,
*                                     SEC_UINT uiConfFlags);
*
* @endcode
*
* @par Purpose
* This function is used to set the OCSP configuration Params into 
* the PKI context.
*
* @par Description
* SEC_PKI_ctxSetOCSPConfParam sets the OCSP Configuration
* Params into the PKI context.
* Following configuration flags should be supported
* \n
* 1. SEC_PKI_OCSP_RESP_CHECK_TIME
* \n
* 2. SEC_PKI_OCSP_SIGN_REQUEST
* \n
* 3. SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN
* \n
* 4. SEC_PKI_OCSP_TRUST_RESP_CERTS_IN_MSG
* \n
* 5. SEC_PKI_OCSP_EXTN_NONCE
* \n
* 6. SEC_PKI_OCSP_EXTN_RESP_TYPES
* \n
* 7. SEC_PKI_OCSP_RESP_CHECK_CRL
* \n
* 8. SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL
* \n
* 9. SEC_PKI_OCSP_RESP_X509_V_FLAG_IGNORE_CRITICAL
*
* @param[in] pstContext Pointer to PKI Context.[NA/NA]
* @param[in] uiConfFlags Type of OCSP PARAMETER. The values can be 
* SEC_PKI_OCSP_SIGN_REQUEST, SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN, 
* SEC_PKI_OCSP_EXTN_NONCE, SEC_PKI_OCSP_EXTN_RESP_TYPES, 
* SEC_PKI_OCSP_TRUST_RESP_CERTS_IN_MSG, SEC_PKI_OCSP_RESP_CHECK_TIME, 
* SEC_PKI_OCSP_RESP_CHECK_CRL, SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL,
* SEC_PKI_OCSP_RESP_X509_V_FLAG_IGNORE_CRITICAL [Refer-Description]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*	- Passing zero to "uiConfFlags" will reset the configuration parameters.
*	- If valid parameters are passed then the parameters are ORed
*   with the existing parameters.
*	- The SEC_PKI_OCSP_SIGN_REQUEST and  SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN
*   are mutually exclusive flags.
*	- To use delta crl in OCSP validation, both SEC_PKI_OCSP_RESP_CHECK_CRL and
*   SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL flag should be enabled.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxSetOCSPConfParam(
    SEC_PKI_CTX_S *pstContext,
    SEC_UINT  uiConfFlags);

/**
* @defgroup SEC_PKI_ctxGetOCSPConfParam
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetOCSPConfParam( const SEC_PKI_CTX_S *pstContext,
*                                   SEC_UINT *puConfFlags;
* @endcode
*
* @par Purpose
* This function is used to get the OCSP configuration parameter 
* set in the context.
*
* @par Description
* SEC_PKI_ctxGetOCSPConfParam function gets OCSP configuration
* parameter set in the context. 
* Following configuration flags should be supported 
* \n
* 1. SEC_PKI_OCSP_RESP_CHECK_TIME
* \n
* 2. SEC_PKI_OCSP_SIGN_REQUEST
* \n
* 3. SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN
* \n
* 4. SEC_PKI_OCSP_TRUST_RESP_CERTS_IN_MSG
* \n
* 5. SEC_PKI_OCSP_EXTN_NONCE
* \n
* 6. SEC_PKI_OCSP_EXTN_RESP_TYPES
* \n
* 7. SEC_PKI_OCSP_RESP_CHECK_CRL
* \n
* 8. SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL
* \n
* 9. SEC_PKI_OCSP_RESP_X509_V_FLAG_IGNORE_CRITICAL
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] puConfFlags Contains the OCSP configuration
* parameter flags.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If no flags are set, then the function will return error.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetOCSPConfParam(
                          const SEC_PKI_CTX_S *pstContext,
                          SEC_UINT *puConfFlags);

/**
* @defgroup SEC_PKI_ctxSetOCSPRequestorName
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxSetOCSPRequestorName( SEC_PKI_CTX_S *pstContext,
*                                    SEC_GEN_NAME_S *pstGeneralName);
*
* @endcode
*
* @par Purpose
* SEC_PKI_ctxSetOCSPRequestorName function is used to set OCSP requestor.
*
* @par Description
* SEC_PKI_ctxSetOCSPRequestorName sets OCSP requestor name 
* into the PKI context. This is an optional API, if the user wants to
* sign the OCSP request then user can set the requestor name. Based on this
* name, library will fetch the appropriate certificate and sign the request 
* if user has enabled signing of the request.
*
* @param[in] pstContext Pointer to PKI Context. [NA/NA]
* @param[in] pstGeneralName Pointer to OCSP Requestor Name.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*
* @par Note
* \n
* It will search the PKI local store with the same requestor name to 
* fetch the certificate.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxSetOCSPRequestorName(
         SEC_PKI_CTX_S *pstContext,
         SEC_GEN_NAME_S *pstGeneralName);



/**
* @defgroup SEC_PKI_ctxGetOCSPRequestorName
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetOCSPRequestorName( const SEC_PKI_CTX_S *pstContext,
*                                      SEC_GEN_NAME_S **dpstGeneralName);
* @endcode
*
* @par Purpose
* This function is used to get the OCSP requestor name.
*
* @par Description
* SEC_PKI_ctxGetOCSPRequestorName function gets the requestor
* name from context. The requestor name is sent as a part
* of OCSP request if signing flag is enabled.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] dpstGeneralName Pointer to hold the sender 
* name or client name.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
@par Memory Handling
* \n
* Memory allocated for the output general name dpstGeneralName,
* should be freed by calling the function X509_freeGeneralName.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetOCSPRequestorName(
                const SEC_PKI_CTX_S *pstContext,
                SEC_GEN_NAME_S **dpstGeneralName);

/**
* @defgroup SEC_PKI_ctxSetOCSPSignAlgType
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxSetOCSPSignAlgType( SEC_PKI_CTX_S *pstContext,
*                                   SEC_PKI_OCSP_SIGNALG_TYPE_E enSignAlgType);
*
* @endcode
*
* @par Purpose
* This function is used to set hash algorithm into the PKI context, which will 
* be used to create signing algorithm while signing the OCSP request.
*
* @par Description
* SEC_PKI_ctxSetOCSPSignAlgType sets the hash algorithm in
* PKI context. The object copies the same hash algorithm if it is set 
* in context.By default hash algorithm is SEC_PKI_OCSP_WITH_SHA1.
*
* @param[in] pstContext Pointer to PKI Context. [NA/NA]
* @param[in] enSignAlgType Type of Signature Algorithm.
* [SEC_PKI_OCSP_WITH_SHA1|SEC_PKI_OCSP_WITH_SHA256/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*
* @par Note
* \n
*	- Only hash algorithm is set here. Signature algorithm is formed by 
* taking the signer certificate based on the requestor name.
*	- SEC_PKI_OCSP_WITH_SHA256 is not supported with DSA keys 
*/
PSELINKDLL SEC_INT SEC_PKI_ctxSetOCSPSignAlgType(
         SEC_PKI_CTX_S *pstContext,
         SEC_PKI_OCSP_SIGNALG_TYPE_E enSignAlgType);


/**
* @defgroup SEC_PKI_ctxGetOCSPSignAlgType
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetOCSPSignAlgType( const SEC_PKI_CTX_S *pstContext,
*                               SEC_PKI_OCSP_SIGNALG_TYPE_E *penOutSignAlgType)
* @endcode
*
* @par Purpose
* This function is used to get the signature algorithm type(Only hash 
* algorithm).
*
* @par Description
* SEC_PKI_ctxGetOCSPSignAlgType function gets the signature
* algorithm type set in the context (Only hash algorithm).By default hash 
* algorithm is SEC_PKI_OCSP_WITH_SHA1.
*
* @param[in] pstContext Pointer to PKI Context. [NA/NA]
* @param[out] penOutProtAlgType Pointer that contains the 
* algorithm type.[NA/SEC_PKI_OCSP_WITH_SHA1]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetOCSPSignAlgType(
                  const SEC_PKI_CTX_S *pstContext,
                  SEC_PKI_OCSP_SIGNALG_TYPE_E *penOutSignAlgType);



#ifndef __SEC_PKI_NO_OCSP_CACHE__

/**
* @defgroup SEC_PKI_ctxResizeOCSPCache
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxResizeOCSPCache( SEC_PKI_CTX_S *pstContext,
*                                   SEC_INT iSize);
*
* @endcode
*
* @par Purpose
* This function is used to resize the cache for the ocsp cache.
*
* @par Description
* SEC_PKI_ctxResizeOCSPCache function will resize cache for
* the OCSP responses, that is, it will increase/decrease the list element of 
* the OCSP cache.
*
* @param [in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param [in] iSize New size of the OCSP cache.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. Negative value is not a valid
* input. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- By default cache size is set to zero, if this API is not used.
*	- If Cache size is set to Zero it will disable the cache & old response
*     status will be deleted.
*	- The maximum limit of cache size is the maximum limit of an integer.
*	- If cache is resized to a size smaller than the existing one,
*    then the extra cache elements are removed in the FIFO order.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxResizeOCSPCache(
    SEC_PKI_CTX_S *pstContext,
    SEC_INT iSize);

/**
* @defgroup SEC_PKI_ctxGetOCSPCacheSize
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetOCSPCacheSize( SEC_PKI_CTX_S *pstContext,
*                                    SEC_UINT *piSize);
*
* @endcode
*
* @par Purpose
* This function is used to get the cache size for the OCSP cache.
*
* @par Description
* SEC_PKI_ctxGetOCSPCacheSize function will return the size of the cache for
* the OCSP responses. By default cache size will be zero, if 
* SEC_PKI_ctxResizeOCSPCache is not used.
*
* @param [in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] piSize Size of cache. [NA/0]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*/


PSELINKDLL SEC_INT SEC_PKI_ctxGetOCSPCacheSize(
    const SEC_PKI_CTX_S *pstContext,
    SEC_INT *piSize);

/**
* @defgroup SEC_PKI_ctxSetOCSPMsgTraceCB
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxSetOCSPMsgTraceCB( SEC_PKI_CTX_S *pstCtx,
*                                  IPSI_OCSP_MSG_TRACE_CB pfMsgTraceCB,
*								   SEC_VOID *pAppData);
*
* @endcode
*
* @par Purpose
* This function is used to set OCSP message trace callback function in context.
*
* @par Description
* SEC_PKI_ctxSetOCSPMsgTraceCB function sets the OCSP message trace callback 
* function to context. This callback function will be called whenever 
* OCSP module sends a message to HTTP module.
*
*
* @param [in] pstCtx Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param [in] pfMsgTraceCB Function pointer to OCSP msg trace callback [NA/NA]
* @param [in] pAppData void * Pointer to application data [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*  This callback can be used for debugging.
*/

PSELINKDLL SEC_INT SEC_PKI_ctxSetOCSPMsgTraceCB(
        SEC_PKI_CTX_S *pstCtx,
        IPSI_OCSP_MSG_TRACE_CB pfMsgTraceCB,
        SEC_VOID *pAppData);

#endif




/**
* @defgroup SEC_PKI_ctxLoadOCSPRespBuffer
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadOCSPRespBuffer(
*                               SEC_PKI_CTX_S *pstContext,
*                               SEC_CHAR *pcOCSPRespMsg,
*                               SEC_UINT uiMsgLen,
*                               const SEC_INT iBuffType,
*                               const SEC_PKI_OCSP_LOAD_RESP_FLAG_E enLoadFlag);
*
* @endcode
*
* @par Purpose
* This function is used to load the OCSP response 
* into the context. The OCSP response will
* be decoded and stored in the context store.
* 
* @par Description
* SEC_PKI_ctxLoadOCSPRespBuffer function loads the OCSP 
* response in the Context. The OCSP response will not
* be validated before loading in the context.
*
* @param[in] pstContext Pointer to PKI Context [NA/NA]
* @param[in] pcOCSPRespMsg OCSP Reponse buffer [NA/NA]
* @param[in] uiMsgLen OCSP reponse buffer length [NA/NA]
* @param[in] iBuffType OCSP reponse buffer type [SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] enLoadFlag Load OCSP Response Flags. These flags can be used to 
* load the OCSP response with/without the certificates that are present in the
* OCSP response buffer. The values can be SEC_PKI_OCSP_LOAD_COMPLETE_RESP,
* SEC_PKI_OCSP_LOAD_WITHOUT_CERTS_IN_MSG [Refer-Description]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*	- The OCSP response is decoded and stored in the context store.
*	- The OCSP responses with status other than OCSP_SUCCESSFUL will not be 
*     loaded.
*	- If the user tries to load the same OCSP response then the API returns 
*     failure.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadOCSPRespBuffer(SEC_PKI_CTX_S *pstContext,
                            const SEC_CHAR *pcOCSPRespMsg,
                            const SEC_UINT uiMsgLen,
                            const SEC_INT iBuffType,
                            const SEC_PKI_OCSP_LOAD_RESP_FLAG_E enLoadFlag);



/**
* @defgroup SEC_PKI_ctxRemoveAllOCSPResp
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxRemoveAllOCSPResp(SEC_PKI_CTX_S *pstContext);
*
* @endcode
*
* @par Purpose
* This function is used to remove all the OCSP responses 
* from the context.
*
* @par Description
* SEC_PKI_ctxRemoveAllOCSPResp function removes all the trusted OCSP 
* responses from the Context.
*
* @param[in] pstContext Pointer to PKI Context [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*	- If no OCSP response is loaded in the context, then API returns failure.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxRemoveAllOCSPResp(
                                SEC_PKI_CTX_S *pstContext);



/**
* @defgroup SEC_PKI_ctxCreateOCSPLock
* @ingroup Context_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxCreateOCSPLock (SEC_PKI_CTX_S*pstContext);
*
* @endcode
*
* @par Purpose
* This function is used to create OCSP lock at PKI context level. Object created using this context will
* not create any OCSP lock at Object level.
*
* @par Description
* SEC_PKI_ctxCreateOCSPLock function creates OCSP lock at PKI context Object create using this 
* context will not create any OCSP lock at object level. All the PKI object created from this context uses same OCSP 
* lock at PKI context.
*
* @param[in] pstContext Pointer to PKI Context [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*	- If this API is used, it must be called before creating any PKI Object using this PKI Context.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxCreateOCSPLock (SEC_PKI_CTX_S*pstContext); 

#ifdef  __cplusplus
}
#endif

#endif /*__SEC_PKI_CTX_OCSP_H__*/

#endif // __SEC_PKI_NO_OCSP__
#endif // IPSI_SEC_NO_PKI

