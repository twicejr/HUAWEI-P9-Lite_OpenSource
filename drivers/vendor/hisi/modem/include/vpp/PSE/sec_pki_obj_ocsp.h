#include "ipsi_pse_build_conf.h"

#ifndef __SEC_PKI_OBJ_OCSP_H__
#define __SEC_PKI_OBJ_OCSP_H__

#include "ipsi_types.h"
#include "x509_basictypes.h"
#include "sec_pki_buildconf.h"
#include "sec_list.h"
#include "sec_sys.h"
#include "sec_pki_def.h"
#include "sec_pki_ocsp_def.h"
#include "ipsi_trans_method.h"
#include "ocsp.h"
#include "x509v3_extn.h"

#ifdef  __cplusplus
extern "C" {
#endif


/**
* @defgroup SEC_PKI_objSetTransMethod
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetTransMethod(
*                                SEC_PKI_OBJ_S *pstObject,
*                                IPSI_TRANS_METH_S *pstTransMeth);
* @endcode
* @par Purpose
* This function is used to set the transport method into the object.
*
* @par Description
* SEC_PKI_objSetTransMethod function sets the transport method into
* the object which is used for doing the transaction into the server.
* NULL for transport method pointer is allowed for resetting.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[out] pstTransMeth Holds the transport method that is to be set [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- If the transport method is freed, then in the object also
*     it has to be reset by passing NULL.
*	- The transport method that is set in the 
*     object will not be freed while freeing the PKI object.
*/
PSELINKDLL SEC_INT SEC_PKI_objSetTransMethod(
    SEC_PKI_OBJ_S *pstObject,
    IPSI_TRANS_METH_S *pstTransMeth);


/**
* @defgroup SEC_PKI_objGetTransMethod
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetTransMethod(
*                               const SEC_PKI_OBJ_S *pstObject,
*                               IPSI_TRANS_METH_S **dpstTransMethod);
* @endcode
*
* @par Purpose
* This function is used to get the transport method type.
*
* @par Description
* SEC_PKI_objGetTransMethod function is used to get the transport method
* which is previously set in the object. If the transport method is not set 
* or if it was reset, then this API returns failure.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[out] dpstTransMethod Stores the transport method (HTTP) [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
*/

PSELINKDLL SEC_INT SEC_PKI_objGetTransMethod(
             const SEC_PKI_OBJ_S *pstObject,
             IPSI_TRANS_METH_S **dpstTransMethod);


/**
* @defgroup SEC_PKI_objGetCtxOCSPCertReq
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetCtxOCSPCertReq(
*                                      const SEC_PKI_OBJ_S *pstObject,
*                                      SEC_List_S **dpOutList);
* @endcode
*
* @par Purpose
* This function is used to get the list of responder certificate hashes.
*
* @par Description
* SEC_PKI_objGetCtxOCSPCertReq function gets the list of
* responder certificate hashes that are marked to be part of
* OCSP request list while loading the trusted responder
* certificate(s).
* 
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[out] dpOutList List of responder certificate hashes [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
*\n
*	- This function will allocate the memory for dpOutList(the list may
*     contain one or more entries). To free this memory, application has to
*     call SEC_LIST_FREE, with the free function as SEC_PKI_freeDataBuf.
*
*/

PSELINKDLL SEC_INT SEC_PKI_objGetCtxOCSPCertReq(
    const SEC_PKI_OBJ_S *pstObject,
    SEC_List_S **dpOutList);

/**
* @defgroup SEC_PKI_objGetCtxOCSPResponderURLByCert
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetCtxOCSPResponderURLByCert(
                                  const SEC_PKI_OBJ_S *pstObject,
*                                 X509_CERT_S *pstCert,
*                                 SEC_PKI_DATA_BUF_S *pstURLInfo);
* @endcode
*
* @par Purpose
* This function is used to get URL corresponding to the input
* certificate from the local store.
*
* @par Description
* SEC_PKI_objGetCtxOCSPResponderURLByCert function gets URL corresponding to the
* input certificate.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[in] pstCert Input certificate [NA/NA]
* @param[out] pstURLInfo URL associated with the 
* input certificate. User needs to pass a valid pstURLInfo pointer [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
*	- ipsi will allocate the memory for the "pstURLInfo-> buf". 
*     To free this memory,application has to call the ipsi_free.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetCtxOCSPResponderURLByCert(
                                              const SEC_PKI_OBJ_S *pstObject,
                                              X509_CERT_S *pstCert,
                                              SEC_PKI_DATA_BUF_S *pstURLInfo);

/**
* @defgroup SEC_PKI_objDoOCSPAsyncReq
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objDoOCSPAsyncReq( SEC_PKI_OBJ_S *pstObject,
*                                SEC_List_S *pstCertList,
*                                SEC_UINT uOCSPFlags,
*                                SEC_UINT32 ulReqId);
* @endcode
* @par Purpose
* This function is used to send the OCSP request for the given list of
* certificates to OCSP server and to obtain the status.
*
* @par Description
* SEC_PKI_objDoOCSPAsyncReq function sends the ocsp request
* for the input certificate list to the OCSP server. The response
* from the server is obtained asynchronously in the http
* library, and given back to the user in the IPSI_HTTP_RESP_CB
* callback set by the user. If the response did not come within the
* timeout value, then it will be indicated in the IPSI_HTTP_ERROR_CB
* set by the user. The user can process the response or the error that
* is obtained in the callbacks using the APIs SEC_PKI_objProcessOCSPResponse
* or SEC_PKI_objProcessOCSPError accordingly.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[in] pstCertList Certificate list [NA/NA]
* @param[in] uOCSPFlags OCSP flags 
* which can be one among
* SEC_PKI_OCSP_RESP_CHECK_TIME,
* SEC_PKI_OCSP_SIGN_REQUEST,
* SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN,
* SEC_PKI_OCSP_TRUST_RESP_CERTS_IN_MSG,
* SEC_PKI_OCSP_EXTN_NONCE,
* SEC_PKI_OCSP_EXTN_RESP_TYPES,
* SEC_PKI_OCSP_RESP_CHECK_CRL,
* SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL,
* SEC_PKI_OCSP_RESP_X509_V_FLAG_IGNORE_CRITICAL [NA/NA]
* @param[in] ulReqId OCSP Request identifier [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
* 
** @par Note
* \n
*	- The OCSP request Id should be unique across multiple objects and it should
*     be greater than zero.
*	- The SEC_PKI_OCSP_SIGN_REQUEST and SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN
*     are mutually exclusive flags.
*	- To use delta CRL in OCSP validation, both SEC_PKI_OCSP_RESP_CHECK_CRL and
*      SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL flag should be enabled.
*   - The Maximum number of OCSP requests that can be sent parallely 
*     in one object is 32.
*/
PSELINKDLL SEC_INT SEC_PKI_objDoOCSPAsyncReq(
                                  SEC_PKI_OBJ_S *pstObject,
                                  SEC_List_S *pstCertList,
                                  SEC_UINT uOCSPFlags,
                                  SEC_UINT32 ulReqId);


/**
* @defgroup SEC_PKI_objProcessOCSPResponse
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objProcessOCSPResponse( SEC_PKI_OBJ_S *pstObject,
*                                       SEC_UINT32 ulReqId,
*                                       SEC_CHAR *pcOCSPRespMsg,
*                                       SEC_UINT uiMsgLen,
*                                       SEC_List_S **dpstSingleRespList,
*                                       OCSP_RESP_S **dpstOutResp);
* @endcode
* @par Purpose
* This function is used to verify the OCSP response message and get the
* decoded OCSP response or the extracted OCSP single response list.
*
* @par Description
* SEC_PKI_objProcessOCSPResponse function verifies the OCSP response
* and gets the decoded OCSP response or the extracted OCSP single response list.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[in] ulReqId The OCSP request Id [NA/NA]
* @param[in] pcOCSPRespMsg OCSP response Message [NA/NA]
* @param[in] uiMsgLen OCSP response message length [NA/NA]
* @param[out] dpstSingleRespList OCSP single response list.
* NULL can be passed to this parameter if single response list is
* not needed [NA/NA]
* @param[out] dpstOutResp OCSP response. NULL can be passed if
* the decoded OCSP response is not needed [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the dpstSingleRespList.
* The list contains OCSP single responses of type OCSP_SINGLE_RESP_S.
* To free this memory application has to call the SEC_LIST_FREE with
* the OCSP_freeSingleResp as the free function.
* The memory of OCSP_RESP_S returned in dpstOutResp parameter can be freed using
* OCSP_freeOCSPResp API.
*
* @par Note
* \n
*	- If the OCSP response is validated successfully then
*     each of the single response is extracted from the OCSP response and
*     cached.
*	- Only one output parameter can be returned back to the user at a time.
* Hence only one of the output parameters which is expected, should not be NULL
* and the other one, should be NULL.
*	- The OCSP request Id should be unique across multiple objects and it should
* be greater than zero.
*   - The producedAt field of OCSP response will not get 
*     processed during validation.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objProcessOCSPResponse(
               SEC_PKI_OBJ_S *pstObject,
               SEC_UINT32 ulReqId,
               SEC_CHAR *pcOCSPRespMsg,
               SEC_UINT uiMsgLen,
               SEC_List_S **dpstSingleRespList,
               OCSP_RESP_S **dpstOutResp);


/**
* @defgroup SEC_PKI_objProcessOCSPError
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objProcessOCSPError( SEC_PKI_OBJ_S *pstObject,
*                                    SEC_UINT32 ulReqId,
*                                    SEC_UINT32 ulErrType);
* @endcode
* @par Purpose
* This function is used to perform the cleanup operation when the response is
* not received from the OCSP server.
*
* @par Description
* SEC_PKI_objProcessOCSPError performs the cleanup operation when the response
* is not received from the OCSP server within the timeout value.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[in] ulReqId The OCSP request ID [NA/NA]
* @param[in] ulErrType The reason code for the response error [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
* 
** @par Note
* \n
*	- This function has to be called when the response is not obtained within
*     the timeout period. Then the details of that request ID will be
*     permanently deleted from the object.
*	- The OCSP request Id should be unique across multiple objects and it should
*     be greater than zero.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objProcessOCSPError(
               SEC_PKI_OBJ_S *pstObject,
               SEC_UINT32 ulReqID,
               SEC_UINT32 ulErrType);

/**
* @defgroup SEC_PKI_objSetOCSPConfParam
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetOCSPConfParam( SEC_PKI_OBJ_S *pstObject,
*                                    SEC_UINT  uiConfFlags);
*
* @endcode
*
* @par Purpose
* This function is used to set the OCSP configuration Params into the
* PKI object.
*
* @par Description
* SEC_PKI_objSetOCSPConfParam sets the OCSP Configuration
* Params into the PKI object.
* Following configuration flags should be supported \n
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
* @param[in] pstObject Pointer to PKI object.[NA/NA]
* @param[in] uiConfFlags Type of OCSP PARAMETER. The values can be
* SEC_PKI_OCSP_SIGN_REQUEST, SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN, 
* SEC_PKI_OCSP_EXTN_NONCE, SEC_PKI_OCSP_EXTN_RESP_TYPES, 
* SEC_PKI_OCSP_TRUST_RESP_CERTS_IN_MSG, SEC_PKI_OCSP_RESP_CHECK_TIME,
* SEC_PKI_OCSP_RESP_CHECK_CRL, SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL, 
* SEC_PKI_OCSP_RESP_X509_V_FLAG_IGNORE_CRITICAL [Refer-Description]
* 
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*	- Passing zero to "uiConfFlags" will reset the configuration parameters.
*	- If valid parameters are passed then the parameters is ORed
*   with the existing parameters.
*   - The SEC_PKI_OCSP_SIGN_REQUEST and  SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN
*   are mutually exclusive flags.
*  
*  
*   - To use delta CRL in OCSP validation, both SEC_PKI_OCSP_RESP_CHECK_CRL and
*   SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL flag should be enabled.
*/
PSELINKDLL SEC_INT SEC_PKI_objSetOCSPConfParam(
    SEC_PKI_OBJ_S *pstObject,
    SEC_UINT  uiConfFlags);

/**
* @defgroup SEC_PKI_objGetOCSPConfParam
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetOCSPConfParam( const SEC_PKI_OBJ_S *pstObject,
*                                     SEC_UINT *puConfFlags);
* @endcode
*
* @par Purpose
* This function is used to get the OCSP configuration parameter
* set in the object.
*
* @par Description
* SEC_PKI_objGetOCSPConfParam function gets OCSP configuration
* parameter set in the object.
* Following configuration flags should be supported \n
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
* 
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
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
PSELINKDLL SEC_INT SEC_PKI_objGetOCSPConfParam(
                          const SEC_PKI_OBJ_S *pstObject,
                          SEC_UINT *puConfFlags);

/**
* @defgroup SEC_PKI_objSetOCSPRequestorName
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetOCSPRequestorName( SEC_PKI_OBJ_S *pstObject,
*                          SEC_GEN_NAME_S *pstGeneralName);
*
* @endcode
*
* @par Purpose
* SEC_PKI_objSetOCSPRequestorName is used to set OCSP requestor name
* into the PKI object.

* @par Description
* SEC_PKI_objSetOCSPRequestorName function sets OCSP requestor
* name into the PKI object. This is an optional API , if the user wants to sign
* the OCSP request then user can set the requestor name. Based on this name,
* library will fetch the appropriate certificate and sign the request
* if user has enabled the signing of the request.
*
* @param[in] pstObject Pointer to PKI Object.[NA/NA]
* @param[in] pstGeneralName Pointer to OCSP Requestor Name.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*
* @par 
*/
PSELINKDLL SEC_INT SEC_PKI_objSetOCSPRequestorName(
         SEC_PKI_OBJ_S *pstObject,
         SEC_GEN_NAME_S *pstGeneralName);


/**
* @defgroup SEC_PKI_objGetOCSPRequestorName
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetOCSPRequestorName( const SEC_PKI_OBJ_S *pstObject,
*                                 SEC_GEN_NAME_S **dpstGeneralName);
* @endcode
*
* @par Purpose
* This function is used to get the OCSP requestor name.
*
* @par Description
* SEC_PKI_objGetOCSPRequestorName function gets the requestor
* name from PKI object. The requestor name is sent as a part
* of OCSP request if signing flag is enabled.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S.[NA/NA]
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
PSELINKDLL SEC_INT SEC_PKI_objGetOCSPRequestorName(
                const SEC_PKI_OBJ_S *pstObject,
                SEC_GEN_NAME_S **dpstGeneralName);

/**
* @defgroup SEC_PKI_objSetOCSPSignAlgType
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetOCSPSignAlgType( SEC_PKI_OBJ_S *pstObject,
*                                SEC_PKI_OCSP_SIGNALG_TYPE_E enSignAlgType);
*
* @endcode
*
* @par Purpose
* This function is used to set hash algorithm into the PKI object, which will 
* be used to create signing algorithm while signing the OCSP request
*
* @par Description
* SEC_PKI_objSetOCSPSignAlgType sets Signature algorithm in
* PKI object.The same hash algorithm is used along with
* the private key to sign the OCSP request.
*
* @param[in] pstObject Pointer to PKI object.[NA/NA]
* @param[in] enSignAlgType Type of Signature Algorithm.[NA/NA]
* [SEC_PKI_OCSP_WITH_SHA1|SEC_PKI_OCSP_WITH_SHA256/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*
* @par Note
* \n
*   - The hash algorithm is set here. The signature algorithm is formed by 
*   taking the signer certificate based on the requestor name.
*   - SEC_PKI_OCSP_WITH_SHA256 is not supported with DSA keys
*/
PSELINKDLL SEC_INT SEC_PKI_objSetOCSPSignAlgType(
         SEC_PKI_OBJ_S *pstObject,
         SEC_PKI_OCSP_SIGNALG_TYPE_E enSignAlgType);


/**
* @defgroup SEC_PKI_objGetOCSPSignAlgType
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetOCSPSignAlgType( const SEC_PKI_OBJ_S *pstObject,
*                              SEC_PKI_OCSP_SIGNALG_TYPE_E *penOutSignAlgType);
* @endcode
*
* @par Purpose

* This function is used to get the signature algorithm type (Only hash 
* algorithm).
*
* @par Description
* SEC_PKI_objGetOCSPSignAlgType function is used to get the signature
* algorithm type set in the object (only hash algorithm). By default hash 
* algorithm is SEC_PKI_OCSP_WITH_SHA1.
*
* @param[in] pstObject Pointer to PKI object. [NA/NA]
* @param[out] penOutProtAlgType Pointer that contains the algorithm type.
* [NA/SEC_PKI_OCSP_WITH_SHA1]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*   The default algorithm type is SEC_PKI_OCSP_WITH_SHA1.
*/
PSELINKDLL SEC_INT SEC_PKI_objGetOCSPSignAlgType(
                  const SEC_PKI_OBJ_S *pstObject,
                  SEC_PKI_OCSP_SIGNALG_TYPE_E *penOutSignAlgType);


#ifndef __SEC_PKI_NO_OCSP_CACHE__

/**
* @defgroup SEC_PKI_objGetOCSPCertStatusFromCtxCache
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetOCSPCertStatusFromCtxCache( SEC_PKI_OBJ_S *pstObj,
*                                       X509_CERT_S  *pstCert,
*                                       OCSP_CERT_STATUS_TYPE_E *peCertStatus);
* @endcode
* @par Purpose
* This function is used to get the OCSP status for the certificate
* which is previously cached.
*
* @par Description
* SEC_PKI_objGetOCSPCertStatusFromCtxCache function gives
* the OCSP status from previously cached OCSP response.
*
* @param[in] pstObj Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param[in] pstCert Pointer to Certificate.[NA/NA]
* @param[out] peCertStatus OCSP response status [NA/NA]
* 
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If response status is expired, then the API will return
* cert status is not found in cache.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetOCSPCertStatusFromCtxCache(
    SEC_PKI_OBJ_S *pstObj,
    X509_CERT_S  *pstCert,
    OCSP_CERT_STATUS_TYPE_E *peCertStatus);
#endif


/**
* @defgroup SEC_PKI_objOCSPSetVerifyCb
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objOCSPSetVerifyCb( SEC_PKI_OBJ_S *pstObject,
*                SEC_INT (*pfCallback) (SEC_INT iVerifyResult,
*                SEC_VOID *pstStoreCtx,SEC_VOID *pAppData),
*                SEC_VOID *pAppData);

* @endcode
* 
* @par Purpose
* This function is used to set the error verify callback function to the 
* PKI object.
* 
* @par Description
* SEC_PKI_objOCSPSetVerifyCb function sets the error verify callback 
* function pointer for OCSP responder cert validation to SEC_PKI_OBJ_S.

* @param[in,out] pstObject Pointer to SEC_PKI_OBJ_S in which 
* callback fields are set. [NA/NA]
* @param[in] pfCallback Function pointer callback 
* to verify the certificates and CRLs during verification of responder's 
* certificate chain. Callback function takes 3 arguments: 
	- iVerifyResult result of certificate validation.
	This can have following values when callback function is called:
*		- SEC_PKI_CB_ERROR - if any error occurs during certificate validation.
*		- SEC_PKI_CB_SUCCESS - if individual certificate validation is
*         successful.
* 	- pstStoreCtx - void pointer which contains information of store context.
* 	- pAppData - void pointer which contains application data. [NA/NA]
* @param[in] pAppData void pointer which contains application data. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT On success. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT If the input is invalid 
* (NULL Pointer is passed). [SEC_PKI_ERROR|NA]
* @par Note
* \n
*	- In the call back function (pfCallback) use the following PKI functions:\n
*		- SEC_PKI_X509_storeCtxGetError\n
*		- SEC_PKI_X509_storeCtxGetErrorDepth\n
*		- SEC_PKI_X509_storeCtxGetCurrentCert\n
*	- Call back function should return any one of the following value:
*		- SEC_PKI_CB_SUCCESS if call back function success
*		- SEC_PKI_CB_ERROR if call back function fails
*/
PSELINKDLL SEC_INT SEC_PKI_objOCSPSetVerifyCb(SEC_PKI_OBJ_S *pstObject,
                SEC_INT (*pfCallback) (SEC_INT iVerifyResult,
                SEC_VOID *pstStoreCtx,SEC_VOID *pAppData),
                SEC_VOID *pAppData);

/**
* @defgroup SEC_PKI_objSetOCSPMsgTraceCB
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objSetOCSPMsgTraceCB( SEC_PKI_OBJ_S *pstObj,
*                          IPSI_OCSP_MSG_TRACE_CB pfMsgTraceCB,
*						   SEC_VOID *pAppData);
*
* @endcode
*
* @par Purpose
* This function is used to set OCSP message trace callback function in object.
*
* @par Description
* SEC_PKI_ctxSetOCSPMsgTraceCB function sets the OCSP message trace callback 
* function to object. This callback will be called whenever OCSP module sends a
* message to HTTP module.
*
* @param [in] pstObj Pointer to SEC_PKI_OBJ_S.[NA/NA]
* @param [in] pfMsgTraceCB Function pointer to OCSP msg trace callback. [NA/NA]
* @param [in] pAppData void * Pointer to Application data.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*  This callback can be used for debugging.
*/

PSELINKDLL SEC_INT SEC_PKI_objSetOCSPMsgTraceCB(
        SEC_PKI_OBJ_S *pstObj,
        IPSI_OCSP_MSG_TRACE_CB pfMsgTraceCB,
        SEC_VOID * pAppData);

/**
* @defgroup SEC_PKI_objLoadOCSPRespBuffer
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objLoadOCSPRespBuffer(
*                               SEC_PKI_OBJ_S * pstObject,
*                               SEC_CHAR *pcOCSPRespMsg,
*                               SEC_UINT uiMsgLen,
*                               const SEC_INT iBuffType,
*                               const SEC_PKI_OCSP_LOAD_RESP_FLAG_E enLoadFlag);
*
* @endcode
*
* @par Purpose
* This function is used to load the OCSP response 
* into the object. The OCSP response will
* be decoded and will be stored in the object store.
* 
* 
* @par Description
* SEC_PKI_objLoadOCSPRespBuffer function loads the OCSP 
* response in the Object. The OCSP response will not
* be validated before loading to the object.
*
* @param[in] pstObject Pointer to PKI Object [NA/NA]
* @param[in] pcOCSPRespMsg OCSP reponse buffer [NA/NA]
* @param[in] uiMsgLen OCSP reponse buffer length [NA/NA]
* @param[in] iBuffType OCSP reponse buffer type [SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] enLoadFlag Load OCSP Response Flags. These flags can be used to 
* load the OCSP response with/without the certificates that are present in the
* OCSP response buffer. The values can be SEC_PKI_OCSP_LOAD_COMPLETE_RESP,
* SEC_PKI_OCSP_LOAD_WITHOUT_CERTS_IN_MSG [Refer-Description]
* 
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*	- The OCSP response is decoded and stored in the object store.
*	- The OCSP responses with status other than OCSP_SUCCESSFUL will not be 
*     loaded.
*	- If the user tries to load the same OCSP response then the API returns 
*     failure.
*/
PSELINKDLL SEC_INT SEC_PKI_objLoadOCSPRespBuffer(SEC_PKI_OBJ_S * pstObject,
                            const SEC_CHAR *pcOCSPRespMsg,
                            const SEC_UINT uiMsgLen,
                            const SEC_INT iBuffType,
                            const SEC_PKI_OCSP_LOAD_RESP_FLAG_E enLoadFlag);


/**
* @defgroup SEC_PKI_objGetCtxOCSPRespByCert
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetCtxOCSPRespByCert(
*    SEC_PKI_OBJ_S *pstObject,
*    SEC_UCHAR **dpucOCSPResp,
*    SEC_UINT32 pulRespLen);
*
* @endcode
* @par Purpose
* This function is used to get the DER encoded OCSP response from the
* context OCSP store.
*
* @par Description
* SEC_PKI_objGetCtxOCSPRespByCert function gets
* the OCSP response from context store.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[in] pstCert Certificate [NA/NA]
* @param[out] dpucOCSPResp DER Encoded OCSP response [NA/NA]
* @param[out] pulRespLen OCSP response length [NA/NA]
* 
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* ipsi will allocate the memory for the pucOCSPResp 
* to free this memory application has to call the ipsi_free.
*/
PSELINKDLL SEC_INT SEC_PKI_objGetCtxOCSPRespByCert(
                                        SEC_PKI_OBJ_S *pstObject,
                                        X509_CERT_S  *pstCert,
                                        SEC_UCHAR **dpucOCSPResp,
                                        SEC_UINT32 *pulRespLen);



/**
* @defgroup SEC_PKI_objGetOCSPRespByCert
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetOCSPRespByCert(
*    SEC_PKI_OBJ_S *pstObject,
*    SEC_UCHAR **dpucOCSPResp,
*    SEC_UINT32 pulRespLen);
*
* @endcode
* @par Purpose
* This function is used to get the DER encoded OCSP response from the
* object OCSP store.
*
* @par Description
* SEC_PKI_objGetOCSPRespByCert function gets
* the best OCSP response from object store.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[in] pstCert Certificate [NA/NA]
* @param[out] dpucOCSPResp DER Encoded OCSP response [NA/NA]
* @param[out] pulRespLen OCSP response length [NA/NA]
* 
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* ipsi will allocate the memory for the pucOCSPResp 
* to free this memory application has to call the ipsi_free.
*
* @par Dependency
* sec_pki_obj_ocsp.h
*
* @attribute Yes No
*
* @par Note
*
* This function should not be used across multiple threads.
*
* @par Example
* None
*
* @par Related Topics
* SEC_PKI_objLoadOCSPRespBuffer
*/
PSELINKDLL SEC_INT SEC_PKI_objGetOCSPRespByCert(
                                        SEC_PKI_OBJ_S *pstObject,
                                        X509_CERT_S  *pstCert,
                                        SEC_UCHAR **dpucOCSPResp,
                                        SEC_UINT32 *pulRespLen);



/**
* @defgroup SEC_PKI_objRemoveAllOCSPResp
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objRemoveAllOCSPResp( SEC_PKI_OBJ_S *pstObject);
*
* @endcode
*
* @par Purpose
* This function is used to remove all the OCSP responses from the
* object.
*
* @par Description
* SEC_PKI_objRemoveAllOCSPResp function removes all the trusted OCSP 
* responses from the Object.
*
* @param[in] pstObject Pointer to PKI Object [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*.	- If no OCSP response is Loaded in the Object,
* then API returns failure.
*/
PSELINKDLL SEC_INT SEC_PKI_objRemoveAllOCSPResp(SEC_PKI_OBJ_S * pstObject);


/**
* @defgroup SEC_PKI_objClearAllOCSPReqID
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objClearAllOCSPReqID( SEC_PKI_OBJ_S *pstObject);
*
* @endcode
*
* @par Purpose
* This function is used to clear the details of all the OCSP
* request IDs present in the object.
*
* @par Description
* SEC_PKI_objClearAllOCSPReqID function clears the details of  
* all the OCSP request IDs present in the Object.
*
* @param[in] pstObject Pointer to PKI Object [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*   - If no OCSP request ID is present in the Object,
* then API returns failure.
*/
PSELINKDLL SEC_INT SEC_PKI_objClearAllOCSPReqID(SEC_PKI_OBJ_S *pstObject);



/**
* @defgroup SEC_PKI_objClearOCSPReqID
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objClearOCSPReqID( SEC_PKI_OBJ_S *pstObject,
*									SEC_UINT32 ulReqID);
*
* @endcode
*
* @par Purpose
* This function is used to clear the details of the given OCSP
* request ID present in the object.
*
* @par Description
* SEC_PKI_objClearOCSPReqID function clears the details of  
* the given OCSP request ID present in the Object.
*
* @param[in] pstObject Pointer to PKI Object [NA/NA]
* @param[in] ulReqID The OCSP request ID to be deleted [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*   - If the given OCSP request ID is not present in the Object,
* then API returns failure.
*/

PSELINKDLL SEC_INT SEC_PKI_objClearOCSPReqID(SEC_PKI_OBJ_S *pstObject,
                                             SEC_UINT32 ulReqID);

/**
* @defgroup SEC_PKI_objGetCtxOCSPResponderCertByHash
* @ingroup Object_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_objGetCtxOCSPResponderCertByHash(
*                                         const SEC_PKI_OBJ_S *pstObject,
*                                         SEC_UINT uAlgType,
*                                         const SEC_UCHAR *pucHash,
*                                         SEC_UINT uLen,
*                                         X509_CERT_S **dpstCert);
* @endcode
*
* @par Purpose
* This function gets the responder certificate from the OCSP store,
* corresponding to certificate hash.
*
* @par Description
* SEC_PKI_objGetCtxOCSPResponderCertByHash gets the responder certificate,
* corresponding to the certificate hash which is passed as an argument.
*
* @param[in] pstObject Pointer to SEC_PKI_OBJ_S [NA/NA]
* @param[in] uAlgType Hash Algorithm [ALGID_SHA1/ALGID_SHA1]
* @param[in] pcHash Hash of the Der Encoded certificate [NA/NA]
* @param[in] uLen Hash length [NA/20]
* @param[out] dpstCert Contains the matching certificate [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- Memory for dpstCert will be allocated inside the library and
*     needs to be freed by X509_freeCert.
*	- Only SHA1 hash algorithm is supported.
*
*/
PSELINKDLL SEC_INT SEC_PKI_objGetCtxOCSPResponderCertByHash(
                                               const SEC_PKI_OBJ_S *pstObject,
                                               SEC_UINT uAlgType,
                                               const SEC_UCHAR *pucHash,
                                               SEC_UINT uLen,
                                               X509_CERT_S **dpstCert);



/**
* @defgroup SEC_PKI_X509_storeCtxGetCurrentOCSPResp
* @ingroup Object_Functions
* @par Prototype
* @code
* OCSP_BASIC_RESP_S  *SEC_PKI_X509_storeCtxGetCurrentOCSPResp(
*                                                     SEC_VOID *pstStoreCtx);
* @endcode
* 
* @par Purpose
* This is used to get current OCSP Basic Response.
* 
* @par Description
* SEC_PKI_X509_storeCtxGetCurrentOCSPResp function gets the OCSP 
* Basic Response corresponding to certificate which is being currently 
* validated.
* 
* @param[in] pstStoreCtx void pointer. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval OCSP_BASIC_RESP_S* In Case of Success 
* OCSP_BASIC_RESP_S OCSP Basic Response is returned .
* [Pointer%to%OCSP_BASIC_RESP_S|NA]
* @retval OCSP_BASIC_RESP_S* In Case of failure,
* SEC_NULL is returned failure occurs in case of input pointer is
* SEC_NULL. [SEC_NULL|Do%not%pass%SEC_NULL]
* @par Note
* \n
* Do not manipulate anything to return pointer as it will be used in library.
*
*/
PSELINKDLL
OCSP_BASIC_RESP_S  *SEC_PKI_X509_storeCtxGetCurrentOCSPResp(
    SEC_VOID *pstStoreCtx);


#ifdef  __cplusplus
}
#endif

#endif /*__SEC_PKI_OBJ_OCSP_H__*/
