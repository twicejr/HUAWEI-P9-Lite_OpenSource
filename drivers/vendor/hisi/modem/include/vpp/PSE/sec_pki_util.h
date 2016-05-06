/***************************************************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: sec_pki_util.h
Version: 1
Author:
Creation Date:
Description: This file contains the utility functions of PKI.
Function List:

History:
<Author>   <date>          <desc>

***************************************************************************/
#include "ipsi_pse_build_conf.h"

#ifndef IPSI_SEC_NO_PKI

#ifndef __SEC_PKI_UTIL_H__
#define __SEC_PKI_UTIL_H__

#include "ipsi_types.h"
#include "x509.h"
#include "sec_sys.h"
#include "sec_list.h"
#include "x509_basictypes.h"
#include "sec_pki_def.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
* @defgroup PKI
* This section contains all the enums, structures, and functions in the PKI 
* library.
*/
/**
* @defgroup Utility_Functions
*.@ingroup PKI
* This section contains all the utility functions of PKI library..
*/

/**
* @defgroup SEC_PKI_getCertChainByCert
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_getCertChainByCert ( SEC_List_S *pCertList,
*                                 X509_CERT_S *pstCert,
                                 SEC_List_S **dpOutCertChain);
* @endcode
*
* @par Purpose
* This function is used to get cert chain for the input certificate
* from the certificate list provided in the input.
*
* @par Description
* SEC_PKI_getCertChainByCert function forms the certificate chain
* for the input certificate from the certificate list provided
* in the input and then the corresponding chain will be returned
* in the output list.
*
* @param[in] pCertList Input cert list from which the cert chain has
* to be formed.
* pCertList is a list which holds elements of type X509_CERT_S.[NA/NA]
* @param[in] pstCert Input certificate.
* @param[out] dpOutCertChain Output certificate chain.[NA/NA]
* dpOutCertChain is a list which holds elements of type X509_CERT_S[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* On success this function will allocate the memory for the dpOutCertChain
* (the list may contain one or more entries), to free this memory 
* application has to call SEC_LIST_FREE, with the free function as
* X509_freeCert.
*
* @par Note
* \n
*	- The first element in the output certificate chain is the
* input certificate.
* \n
*	- Possible certificate chain that can be built for the input certificate.
* Input certificate list will be considered in the output chain, if the
* issuer certificate for input certificate is not found in the input
* certificate list.
* Hence the chain obtained in the output for the 
* input certificate, can be incomplete.
* \n
*	- Only basic validation is done to construct the certificate chain.
*
*/
PSELINKDLL SEC_INT SEC_PKI_getCertChainByCert(SEC_List_S *pCertList,
                               X509_CERT_S *pstCert,
                                 SEC_List_S **dpOutCertChain);


/**
* @defgroup SEC_PKI_getAllCertChainByAltName
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_getAllCertChainByAltName (
*                                   SEC_List_S *pstCertChainList, 
*                                   SEC_CHAR *pcAltName,
*                                   SEC_UINT ulLen,
*                                   SEC_PKI_X509_ALT_NAME_TYPE_E enId,
*                                   SEC_List_S **dpOutCertChainList);
* @endcode
*
* @par Purpose
* This function is used to get all matching certificate(s) chain from the 
* input certificate(s) chain list by matching subject alternative name.
*
* @par Description
* SEC_PKI_getAllCertChainByAltName function gets the certificate(s) chain from
* the pstCertChainList by matching alt name. If there are multiple 
* certs which are having same alt name, then it will return the cert chain(s)
* corresponding to the all the starting certs which are matching the
* alt name. If it fails to find the altName in the starting certs,
* then appropriate error will be returned.
*
* @param[in] pstCertChainList Input cert chain list.
* pstCertChainList is a list which holds elements of type SEC_List_S which
* in turn holds elements of type X509_CERT_S.[NA/NA]
* @param[in] pcAltName Alt Name.[NA/NA]
* @param[in] ulLen Length of the Alt Name.[NA/NA]
* @param[in] enId Id to identify the Alt Name type.[NA/NA]
* @param[out] dpOutCertChainList which contains the chain(s) for the 
* matching alt name.
* dpOutCertChainList is a list which holds elements of type SEC_List_S which
* in turn holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* On success function will allocate the memory for the dpOutCertChainList
* (the list may contain one or more entries), to free this memory, application
* has to call SEC_PKI_freeCertChainList function.
*
* @par Note
* \n
*	- If multiple end certificates matches the Alt Name then
* multiple chains will be provided as output.
* \n
*	- In each and every certificate chain, only the first certificate will
* be considered for checking.
* \n
*	- The input list of lists pstCertChainList. If empty list is
* passed (that is list with no certificates) in between loaded lists, then
* appropriate error will be returned.
* \n
*	- Only IPV4 address is supported for input alt name of type IP address. 
* \n
*	- IP address should be given in decimal dotted format.
* \n
*	- Alt name of type SEC_PKI_TYPE_DNSNAME and SEC_PKI_TYPE_EMAILID
* are case insensitive.  
* \n
*	- Error will be returned if the input Alt Name length is zero.
*
*/
PSELINKDLL SEC_INT SEC_PKI_getAllCertChainByAltName (
                                   SEC_List_S *pstCertChainList, 
                                   SEC_CHAR *pcAltName,
                                   SEC_UINT ulLen,
                                   SEC_PKI_X509_ALT_NAME_TYPE_E enId,
                                   SEC_List_S **dpOutCertChainList);

/**
* @defgroup SEC_PKI_getAllCertChainByAlgId
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_getAllCertChainByAlgId ( SEC_List_S *pstCertChainList,
*                                     SEC_PKI_X509_ALG_TYPE_E enAlgId,
*                                     SEC_List_S **dpOutCertChainList);
* @endcode
* @par Purpose
* This function is used to get the certificate chain of matching algorithm id
* from the input certificate(s) chain list.
*
* @par Description
* SEC_PKI_getAllCertChainByAlgId function gets the certificate(s) chain from
* the pstCertChainList by matching algorithm id. If there are multiple starting
* certs which are having same algorithm id, then it will return the
* cert chain(s) corresponding to the all the starting certs which are
* matching the algorithm id. If it fails to find the algorithm id in the
* the starting certs, then appropriate error will be returned.
*
*
* @param[in] pstCertChainList Input cert chain list.
* pstCertChainList is a list which holds elements of type SEC_List_S which
* in turn holds elements of type X509_CERT_S.[NA/NA]
* @param[in] enAlgId Id to identify the public key algorithm type.[NA/NA]
* @param[out] dpOutCertChainList which contains the chain(s) for the 
* matching algorithm type.
* dpOutCertChainList is a list which holds elements of type SEC_List_S which
* in turn holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* On success function will allocate the memory for the dpOutCertChainList
* (the list may contain one or more entries), to free this memory, application
* has to call SEC_PKI_freeCertChainList function.
*
* @par Note
* \n
*	- If multiple end certificates matches the algorithm id then
* multiple chains will be provided as output.
* \n
*	- In each and every certificate chain, only the first certificate will
* be considered for checking.
* \n
*	- The input list of lists pstCertChainList. If empty list is
* passed (that is, list with no certificates) in between loaded lists, then
* appropriate error will be returned.
*
*/
PSELINKDLL SEC_INT SEC_PKI_getAllCertChainByAlgId (SEC_List_S *pstCertChainList,
                                     SEC_PKI_X509_ALG_TYPE_E enAlgId,
                                     SEC_List_S **dpOutCertChainList);


/**
* @defgroup SEC_PKI_getAllCertChainBySamePubKey
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_getAllCertChainBySamePubKey (
*                                     SEC_List_S *pstCertChainList,
*                                     SEC_List_S **dpOutCertChainList);
* @endcode
*
* @par Purpose
* This function is used to get all the certificate chains which are having
* same public key from the input certificate chain list. 
* 
* @par Description
* SEC_PKI_getAllCertChainBySamePubKey function gets the certificate(s) chain
* from the pstCertChainList which are having same public key. If there are
* multiple start certs which are having same public key, then it will
* return the cert chain(s) corresponding to the all the starting certs
* which are having same public key. If it fails to find the matching public
* key end entities, then it will return the chain corresponding to the first
* certificate found in the input certificate chain list.
*
* @param[in] pstCertChainList Input cert chain list.
* pstCertChainList is a list which holds elements of type SEC_List_S which
* in turn holds elements of type X509_CERT_S.[NA/NA]
* @param[out] dpOutCertChainList Which contains the chain(s) having
* same public key within the input certificate chain list.
* dpOutCertChainList is a list which holds elements of type SEC_List_S which
* in turn holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* On success function will allocate the memory for the dpOutCertChainList
* (the list may contain one or more entries), to free this memory application
* has to call SEC_PKI_freeCertChainList function.
*
* @par Note
* \n
*	- This function will provide only the first matching (having the same
* public key) certificate chains within the input certificate
* chain list. If multiple end entity certificates have the same public
* key then multiple chains will be provided as output.
* \n
*	- In each and every certificate chain, only the first certificate will
* be considered for checking.
* \n
*	- The input list of lists pstCertChainList, If empty list is
* passed (that is, list with no certificates) in between loaded lists, then
* appropriate error will be returned.
*
*/
PSELINKDLL SEC_INT SEC_PKI_getAllCertChainBySamePubKey (
                                     SEC_List_S *pstCertChainList,
                                     SEC_List_S **dpOutCertChainList);

/**
* @defgroup SEC_PKI_VerifyCertFileTime
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_VerifyCertFileTime( const SEC_CHAR *pcCertFile,
*                               SEC_INT iCertFileType,
*                               SEC_CHAR *pcCertPasswd,
*                               SEC_UINT uCertPwdLen,
*                               DATETIME_S *pstChecktime,
*                               SEC_TIME_T iDifference,
*                               SEC_List_S **pstVerifyResult);
* @endcode
*
* @par Purpose
* This function is used to read the certificate(s) from the file and validates
* with the given time.
*
* @par Description
* SEC_PKI_VerifyCertFileTime function reads the certificates from the file and 
* validates with the input time. If the input time is NULL then the current time
* system time is taken for the validation. If there are multiple 
* certificates in the file then the output contains the list of verify time 
* result for each of these certificates.
*
* @param[in] pcCertFile Certificate file. [NA/NA]
* @param[in] iCertFileType Certificate file type. Mentions the certificate file 
* type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uLen Length of the password.[0-255/NA]
* @param[in] pstChecktime Validates with this time.[NA/NA]
* @param[in] iDifference In seconds, Can be positive or negative seconds.[NA/NA]
* @param[out] pstVerifyResult The list of verify time result unions.
* The verify result will contain the following information:
*	- iErrorCode - Indicates whether certificate is valid or expired.
*	- lBefore_thisUpdate_Diff - Contains time difference between the 
* not before field and the effective check time (includes input 
* iDifference seconds).
*	- lAfter_Nextupdate_Diff - Contains time difference between the 
* effective Check time and the not after field. [NA/NA]
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note 
* \n
*	- The range of time supported is from 1970 January 2, 0:0:0(HH:MM:SS)
* to 2038 January 19, 3:14:07(HH:MM:SS) in windows and 
* 1970 January 1, 0:0:0(HH:MM:SS) to 2038 January 19, 3:14:07(HH:MM:SS)
* in Dopra.
*	- In Dopra, if the user passes checkime and certificate.
* The difference in range between checktime and NotBefore field,
* and NotAfter and checktime field, exceeds the size of long data type, then
* the behavior is inconsistent. If the verification of both the certificate
* fields with the checktime fails we mention the certificate as expired.
*	- For PFX file type, password length as zero is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, MIC_CLEAR mode is not supported .
*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the pstVerifyResult (the list may 
* contain one or more entries of type SEC_PKI_VERIFY_TIME_RESULT_S)
* to free this memory application has to call the SEC_LIST_FREE 
* (pass "ipsi_free" as free function to SEC_LIST_FREE)
*/
PSELINKDLL SEC_INT SEC_PKI_VerifyCertFileTime (const SEC_CHAR *pcCertFile,
                                SEC_INT iCertFileType,
                                SEC_CHAR *pcCertPasswd,
                                SEC_UINT uCertPwdLen,
                                DATETIME_S *pstChecktime, 
                                SEC_TIME_T iDifference,
                                SEC_List_S **pstVerifyResult);


/**
* @defgroup SEC_PKI_VerifyCertBufTime
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_VerifyCertBufTime ( const SEC_CHAR *pcCertBuffer,
*                               SEC_UINT uCertBufLen,
*                               SEC_INT iCertType,
*                               SEC_CHAR *pcCertPasswd,
*                               SEC_UINT uCertPwdLen,
*                               DATETIME_S *pstChecktime, 
*                               SEC_TIME_T iDifference,
*                               SEC_List_S **pstVerifyResult);
* @endcode
*
* @par Purpose
* This function is used to read the certificate(s) from the buffer and validates
* with the given time.
*
* @par Description
* SEC_PKI_VerifyCertBufTime function reads the certificates from the buffer and
* validates with the input time. If the input time is NULL then the current time
* system time is taken for the validation. If there are multiple certificates in
* the file then the output contains the list of verify time 
* result unions for each of these certificates.
*
* @param[in] pcCertBuffer Buffer that contains the certificate.[NA/NA]
* @param[in] uCertBufLen Buffer length.[NA/NA]
* @param[in] iCertType  Certificate type. Mentions the Certificate 
* type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the Certificate.[NA/NA]
* @param[in] uLen Length of the Password.[0-255/NA]
* @param[in] pstChecktime Validates with this time.[NA/NA]
* @param[in] iDifference In Seconds, can be positive or negative seconds.[NA/NA]
* @param[out] pstVerifyResult The list of verify time result unions.
* SEC_PKI_VERIFY_TIME_RESULT_S\n
* The verify result will contain the following information:
*	- iErrorCode - Indicates whether certificate is valid or expired.
*	- lBefore_thisUpdate_Diff - Contains time difference between the 
* not before field and the effective check time (includes input 
* iDifference seconds).
*	- lAfter_Nextupdate_Diff - Contains time difference between the 
* effective check time and the not after field.[NA/NA]
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- The range of time supported is from 1970 January 2, 0:0:0(HH:MM:SS)
* to 2038 January 19, 3:14:07(HH:MM:SS) in windows and 
* 1970 January 1, 0:0:0(HH:MM:SS) to 2038 January 19, 3:14:07(HH:MM:SS)
* in Dopra.
*	- In Dopra, if the user passes checkime and certificate. 
* The difference in range between checktime and NotBefore field,
* and NotAfter and checktime field, exceeds the size of long data type, then
* the behavior is inconsistent. If the verification of both the certificate
* fields with the checktime fails we mention the certificate as expired.
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). Any value other than the actual
* buffer length API behavior is undefined.
*	- For PFX file type, password length as zero is not supported
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.

*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the pstVerifyResult (the list may 
* contain one or more entries of type SEC_PKI_VERIFY_TIME_RESULT_S),
* to free this memory application has to call the SEC_LIST_FREE 
* (pass "ipsi_free" as free function to SEC_LIST_FREE).
*/
PSELINKDLL SEC_INT SEC_PKI_VerifyCertBufTime(const SEC_CHAR *pcCertBuffer,
                              SEC_UINT uCertBufLen,
                              SEC_INT iCertFileType,
                              SEC_CHAR *pcCertPasswd,
                              SEC_UINT uCertPwdLen,
                              DATETIME_S *pstChecktime, 
                              SEC_TIME_T iDifference,
                              SEC_List_S **pstVerifyResult);


/**
* @defgroup SEC_PKI_VerifyCRLFileTime
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_VerifyCRLFileTime ( const SEC_CHAR *pcCrlFile,
*                                SEC_INT iType,
*                                DATETIME_S *pstCheckTime,
*                                SEC_TIME_T iDifference,
*                                SEC_List_S **pstVerifyResult);
* @endcode
*
* @par Purpose
* This function is used to verify the input CRL with the given time.
*
* @par Description
* SEC_PKI_VerifyCRLFileTime function reads the file that contains CRL
* (certificate revocation list) in "PEM" or "DER" format and validates with the
* input time. If the input time is NULL then the current system time is taken
* for the validation. The this update and next update will be compared 
* to ensure the validity of CRL. The output contains the list of verify time 
* result for the CRL.
*
*
* @param[in] pcCRLfile FileName.[NA/NA]
* @param[in] iType Type of the file. Mentions the CRL file 
* type to be loaded.
* [SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pstChecktime validates with this time.The checktime 
* should be a valid time[NA/NA]
* @param[in] iDifference In seconds, Can be positive or negative seconds.[NA/NA]
* @param[out] pstVerifyResult The list of verify time result unions.
* The output list contains the elements of type 
* SEC_PKI_VERIFY_TIME_RESULT_S.\n
* The verify result will contain the following information:
*	- iErrorCode - Indicates whether certificate is valid or expired.
*	- lBefore_thisUpdate_Diff - Contains time difference between the 
* this update and the effective check time (includes input 
* iDifference seconds)
*	- lAfter_Nextupdate_Diff - Contains time difference between the 
* effective check time and the next update field.[NA/NA]
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- The range of time supported is from 1970 January 2, 0:0:0(HH:MM:SS)
* to 2038 January 19, 3:14:07(HH:MM:SS) in windows and 
* 1970 January 1, 0:0:0(HH:MM:SS) to 2038 January 19, 3:14:07(HH:MM:SS)
* in Dopra.
*	- In Dopra,if the user passed checkime and CRL. Such that
* the difference in range between checktime and this Update field
* and nextUpdate and checktime field, exceeds the size of long data type, then
* the behavior is inconsistent. If the verification of both the CRL
* fields with the checktime fails we mention the CRL as expired.
*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the pstVerifyResult (the list may 
* contain one or more entries of type SEC_PKI_VERIFY_TIME_RESULT_S)
* to free this memory application has to call the SEC_LIST_FREE 
* (pass "ipsi_free" as free function to SEC_LIST_FREE).
*/
PSELINKDLL SEC_INT SEC_PKI_VerifyCRLFileTime (const SEC_CHAR *pcCrlFile,
                               SEC_INT iType,
                               DATETIME_S *pstCheckTime,
                               SEC_TIME_T iDifference,
                               SEC_List_S **pstVerifyResult);



/**
* @defgroup SEC_PKI_freeCertChainList
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_VOID SEC_PKI_freeCertChainList( SEC_List_S *pstCertChainList);
* @endcode
*
* @par Purpose
* This function is used to free the list of certificate chains.
*
* @par Description
* SEC_PKI_freeCertChainList function is used to free the list formed 
* using SEC_List_S which holds elements of type SEC_List_S which in turn
* holds elements of type X509_CERT_S.
*
*
* @param[in] pstCertChainList Input list which holds elements of type 
* SEC_List_S which in turn holds elements of type X509_CERT_S. [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_VOID This function does not return any value. [NA|NA]
* 
*/
PSELINKDLL SEC_VOID SEC_PKI_freeCertChainList(SEC_List_S *pstCertChainList);


/**
* @defgroup SEC_PKI_freeDataBuf
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_VOID SEC_PKI_freeDataBuf( SEC_PKI_DATA_BUF_S * pstDataBuff);
* @endcode
*
* @par Purpose
* This function is used to free the data buffer.
*
* @par Description
* SEC_PKI_freeDataBuf function is used to free the data buffer of
* type SEC_PKI_DATA_BUF_S. This function will first free the character
* pointer with in the buffer and then frees the entire SEC_PKI_DATA_BUF_S
* structure.
*
*
* @param[in] pstDataBuff Pointer to data buffer. [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_VOID This function does not return any value. [NA/NA]
* 
*/
PSELINKDLL SEC_VOID SEC_PKI_freeDataBuf(SEC_PKI_DATA_BUF_S * pstDataBuff);



/**
* @defgroup SEC_PKI_VerifyCRLBufTime
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_VerifyCRLBufTime ( const SEC_CHAR *pcCRLBuffer,
*                              SEC_UINT uCertBufLen, 
*                              SEC_INT iType,
*                              DATETIME_S *pstCheckTime,
*                              SEC_TIME_T iDifference,
*                              SEC_List_S **pstVerifyResult);
* @endcode
*
* @par Purpose
* This function verifies the input CRL with the given time.
*
* @par Description
* SEC_PKI_VerifyCRLBufTime function reads the file that contains CRL
* (certificate revocation list) in "PEM" or "DER" format and validates with the
* input time. If the input time is NULL then the current system time is taken
* for the validation. This update and next update will be compared
* to ensure the validity of CRL. The output contains the list of verify time 
* result unions for the CRL.
*
*
* @param[in] pcCRLBuffer Buffer that contains the CRL.[NA/NA]
* @param[in] uCertBufLen Certificate buffer length.[NA/NA]
* @param[in] iType Type of the file. Mentions the CRL file 
* type to be loaded.
* [SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pstChecktime Validates with this time.[NA/NA]
* @param[in] iDifference In seconds, Can be positive or negative seconds.[NA/NA]
* @param[out] pstVerifyResult The list of verify time result unions.
* The output list contains the elements of type 
* SEC_PKI_VERIFY_TIME_RESULT_S.
* The verify result will contain the following information:
*	- iErrorCode - Indicates whether certificate is valid or expired.
*	- lBefore_thisUpdate_Diff - Contains time difference between the 
* this update and the effective check time (includes input 
* iDifference seconds)
*	- lAfter_Nextupdate_Diff - Contains time difference between the 
* effective check time and the next update field.[NA/NA]
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- The range of time supported is from 1970 January 2, 0:0:0(HH:MM:SS)
* to 2038 January 19, 3:14:07(HH:MM:SS) in windows and 
* 1970 January 1, 0:0:0(HH:MM:SS) to 2038 January 19, 3:14:07(HH:MM:SS)
* in Dopra.
*	- In Dopra,if the user passes checkime and CRL. Such that
* the difference in range between checktime and this Update field,
* and nextUpdate and checktime field, exceeds the size of long data type, then
* the behavior is inconsistent. If the verification of both the CRL
* fields with the checktime fails we mention the CRL as expired.
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). Any value other than the actual
* buffer length API behavior is undefined.
*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the pstVerifyResult (the list may 
* contain one or more entries of type SEC_PKI_VERIFY_TIME_RESULT_S),
* to free this memory application has to call the SEC_LIST_FREE 
* (pass "ipsi_free" as free function to SEC_LIST_FREE).
*/
PSELINKDLL SEC_INT SEC_PKI_VerifyCRLBufTime (const SEC_CHAR *pcCRLBuffer,
                              SEC_UINT uCertBufLen,
                              SEC_INT iType,
                              DATETIME_S *pstCheckTime,
                              SEC_TIME_T iDifference,
                              SEC_List_S **pstVerifyResult);


/**
* @defgroup SEC_PKI_enCodeCert
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_enCodeCert ( X509_CERT_S *pstCert,
*                          SEC_PKI_ENCODE_TYPE_E enCtype, 
*                          SEC_CHAR **pcEncodedCert,
*                          SEC_UINT *puLen);
* @endcode
*
* @par Purpose
* This function is used to encode the certificate.
*
* @par Description
* SEC_PKI_enCodeCert function encodes the certificate based on the
* encoding type.
*
* @param[in] pstCert Certificate which is to be encoded.[NA/NA]
* @param[in] encType Encoding type, Following type is supported\n
* SEC_PKI_DER_ENCODE\n
* @param[out] pcEncodedData Which contains the Encoded data.[NA/NA]
* @param[out] puLen Contains the Encoded buffer length. [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.[SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the pcEncodedCert, to free this memory
* application has to call the ipsi_free
*
*/
PSELINKDLL SEC_INT SEC_PKI_enCodeCert (X509_CERT_S *pstCert,
                        SEC_PKI_ENCODE_TYPE_E encType,
                        SEC_CHAR **pcEncodedCert,
                        SEC_UINT *puLen);

/**
* @defgroup SEC_PKI_deCodeCert
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_deCodeCert ( SEC_CHAR *pcEncodedCert, 
*                          SEC_UINT uiLen,
*                          SEC_PKI_ENCODE_TYPE_E enCtype,
*                          X509_CERT_S **pstCert);
* @endcode
*
* @par Purpose
* This function is used to decode the certificate.
*
* @par Description
* SEC_PKI_deCodeCert function decodes the input data and returns the decoded
* certificate based on the encoding type, if it fails to decode pstCert 
* contains NULL.
*
* @param[in] pcEncodedCert Encoded data.[NA/NA]
* @param[in] uiLen Length the of the encoded data.[NA/NA]
* @param[in] encType Encoding type, Following type is supported\n
* SEC_PKI_DER_ENCODE.[NA/NA]
* @param[out ] pstCert Contains the decoded certificate.[NA/NA]
* 
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the pstCert.
* To free this memory application has to call the X509_freeCert
*
*/
PSELINKDLL SEC_INT SEC_PKI_deCodeCert (SEC_CHAR *pcEncodedCert,
                        SEC_UINT uiLen,
                        SEC_PKI_ENCODE_TYPE_E encType,
                        X509_CERT_S **pstCert);

/**
* @defgroup SEC_PKI_getAllEndEntityCertFromList
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_getAllEndEntityCertFromList ( SEC_List_S *pstInCertList,
*                                          SEC_List_S **pstCertList);
* @endcode
*
* @par Purpose
* This function is used to get all the end entity certificate(s) from the input
* cert list.
*
* @par Description
* SEC_PKI_getAllEndEntityCertFromList function gets all the end entity
* certificate(s) from the input certs list. All the end entity certificate from
* the input cert list is extracted and list is formed and this list is returned
* to the user. NULL will be returned if it fails to find any end entity
* certificate.
* If the Certificate is of Version 3 then only it is checked for end entity or
* CA, V1/V2 certificates are treated as end entity.
*
* @param[in] pstInCertList Input Cert list. 
* pstInCertList is a list which holds elements of type X509_CERT_S.[NA/NA]
* @param[out] pstCertList Contains end entity certificate(s).
* pstCertList is a list which holds elements of type X509_CERT_S[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the pstCert to free this memory application 
* has to call the SEC_LIST_FREE.
*
*/
PSELINKDLL SEC_INT SEC_PKI_getAllEndEntityCertFromList (
                                         SEC_List_S *pstInCertList,
                                         SEC_List_S **pstCertList);


/**
* @defgroup SEC_PKI_isSelfSignedCertificate
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_isSelfSignedCertificate ( X509_CERT_S *pstCert);
* @endcode
*
* @par Purpose
* This function is used to check the input certificate is a self signed
* certificate or not.
*
* @par Description
* SEC_PKI_isSelfSignedCertificate function checks the input certificate is
* a self signed cert or not.\n
* To determine a self signed cert following checks are done:
*	- Subject Name and Issuer Name check
*	- Signature Verification check
*
* @param[in] pstCert Input Cert[NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_INT If the input cert is a self signed cert. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_isSelfSignedCertificate (X509_CERT_S *pstCert);


/**
* @defgroup SEC_PKI_extractCDPFromCert
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_extractCDPFromCert ( X509_CERT_S *pstCert, 
*                             SEC_List_S ** pListOutDataBuf);
* @endcode
*
* @par Purpose
* This function is used to extract the CDP from the input cert.
*
* @par Description
* SEC_PKI_extractCDPFromCert function extract the CDP [CRL Distribution point]
* from the input cert.
*
* @param[in] pstCert Input Cert[NA/NA]
* @param[out] pListOutDataBuf contains the CDP data buffer list.
* The output list contains elements of type SEC_PKI_DATA_BUF_S
* where the buf corresponds to CDP string and
* len corresponds to CDP string length [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the pListOutDataBuf. To free this memory 
* application has to call SEC_LIST_FREE with SEC_PKI_freeDataBuf as 
* free function.
*
@par Note
* \n
*	- API supports extraction of CDP only if the CDP is present
* in the URI field of the FullName [GeneralName] of the 
* DistributionPointName.
*	- The Relative URIs like empty string or blank space 
* are not supported by the library.
*	- Even there are multiple CDP names of different type only URI type will be
* added in the list and given to the user and the API returns SUCCESS.
*	- If there is no URI CDP name among the CDP name(s) the API returns fail
* and no output list is given to the user.
*/
PSELINKDLL SEC_INT SEC_PKI_extractCDPFromCert (X509_CERT_S *pstCert, 
                               SEC_List_S ** pListOutDataBuf);



/**
* @defgroup SEC_PKI_CheckPrivateKeyFile
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_CheckPrivateKeyFile( const SEC_CHAR *pcCertFile,
*                                   SEC_INT iCertFileType,
*                                   const SEC_CHAR *pcCertPasswd,
*                                   SEC_UINT uCertPwdLen,
*                                   const SEC_CHAR *pcKeyFile,
*                                   SEC_INT iKeyFileType,
*                                   const SEC_CHAR *pcKeyPasswd,
*                                   SEC_UINT uKeyPwdLen);
* @endcode
*
* @par Purpose
* This function is used to check the certificate and key from the file if
* they are matching or not.
*
* @par Description
* SEC_PKI_CheckPrivateKeyFile function reads a certificate and key 
* file that contains the certificate and key in "PEM","PFX", or "DER" format,
* and checks the certificate and key are matching or not. 
* Certificate password is an optional input but, applicable 
* only for PFX format. Key file password is also optional. *
*
* @param[in] pcCertFile The name of the file from which the certificate has to
* be loaded.[NA/NA]
* @param[in] iCertFileType Certificate file type, Mentions the type of cert file
* to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the password.[0-255/NA]
* @param[in] pcKeyFile The file which contains the private key of the
* certificate.[NA/NA]
* @param[in] iKeyFileType Key file type, Mentions the type of key
* to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. 
* The failure can occur, if the input is invalid(NULL pointer),
* file cannot be opened, or decoding of certificate
* fails. [SEC_PKI_ERROR|NA]
* @par Note
* \n
*	- A file can contain both the certificate and key in this case same file
* name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
*		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
*		- present in PFX.
*		- Enc password - Used for encrypting the baglist or 
* the key before storing into bag. Cert can be encrypted 
* only by encrypting the baglist. But, key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		- Same file containing both the certificate and private key 
* whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
* password are also different.
*		- If a file has multiple encrypted or unencrypted baglists.
* Then the first certificate from the first encrypted baglist will be taken
* for checking. If the certificate is not present in the first encrypted 
* baglist then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
* baglists, then the first private key from the first encrypted/unencrypted 
*  baglist is taken.
*		- If the privatekey is not present in the first baglist, then 
* the privatekey is searched in the other baglists. If the 
* private key is not present in any of the baglists,
* then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*/

PSELINKDLL SEC_INT SEC_PKI_CheckPrivateKeyFile(const SEC_CHAR *pcCertFile,
                                    SEC_INT iCertFileType,
                                    const SEC_CHAR *pcCertPasswd,
                                    SEC_UINT uCertPwdLen,
                                    const SEC_CHAR *pcKeyFile,
                                    SEC_INT iKeyFileType,
                                    const SEC_CHAR *pcKeyPasswd,
                                    SEC_UINT uKeyPwdLen);


/**
* @defgroup SEC_PKI_CheckPrivateKeyBuffer
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_CheckPrivateKeyBuffer( 
                                              const SEC_CHAR *pcCertBuffer,
*                                             SEC_UINT uCertBufLen,
*                                             SEC_INT iCertType,
*                                             const SEC_CHAR *pcCertPasswd,
*                                             SEC_UINT uCertPwdLen,
*                                             const SEC_CHAR *pcKeyBuffer,
*                                             SEC_UINT uKeyBufLen,
*                                             SEC_INT iKeyType,
*                                             const SEC_CHAR *pcKeyPasswd,
*                                             SEC_UINT uKeyPwdLen);
* @endcode
*
* @par Purpose
* This function is used to check the certificate and key from the buffer if
* they are matching or not.
*
* @par Description
* SEC_PKI_CheckPrivateKeyBuffer function reads a buffer that contains
* the certificate and key in "PEM","PFX", or "DER" format and 
* checks the certificate and key are matching or not.
* Certificate password is an optional input and applicable only
* for PFX format. Key password is also optional. 
*
* @param[in] pcCertBuffer The buffer from which the certificate has to be
* loaded. [NA/NA]
* @param[in] uCertBufLen Length of the certificate Buffer.[NA/NA]
* @param[in] iCertFileType certificate file type, Mentions the type 
* of file to be loaded
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
* @param[in] pcKeyBuffer The buffer which contains the private key.[NA/NA]
* @param[in] uKeyBufLen Length of the private key Buffer.[NA/NA]
* @param[in] iKeyType. Mentions the type 
* of key to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid
* (NULL pointer). [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- A file can contain both the certificate and key, in this case same file
* Name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
*		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
* present in PFX.
*		- Enc password - Used for encrypting the baglist or 
* the key before storing into bag. Cert can be encrypted 
* only by encrypting the baglist but, key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		- Same file containing both the certificate and private key 
* whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
* password are also different.
*		- If a file has multiple encrypted or unencrypted baglists. Then
* the first certificate from the first encrypted baglist will be taken
* for checking. If the certificate is not present in the first encrypted 
* baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
* baglists, then the first private key from the first encrypted/unencrypted 
* baglist is taken.
*		- If the privatekey is not present in the first baglist, then 
* the privatekey is searched in the other baglists. If the 
* it is not present in any of the baglists,
* then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*/

PSELINKDLL SEC_INT SEC_PKI_CheckPrivateKeyBuffer(const SEC_CHAR *pcCertBuffer,
                                              SEC_UINT uCertBufLen,
                                              SEC_INT iCertType,
                                              const SEC_CHAR *pcCertPasswd,
                                              SEC_UINT uCertPwdLen,
                                              const SEC_CHAR *pcKeyBuffer,
                                              SEC_UINT uKeyBufLen,
                                              SEC_INT iKeyType,
                                              const SEC_CHAR *pcKeyPasswd,
                                              SEC_UINT uKeyPwdLen);

/**
* @defgroup SEC_PKI_getAttrFromSubjectName
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_getAttrFromSubjectName( X509_CERT_S *pstCert, 
*                                        X509_NAME_ATTR_TYPE_E uiAttrType, 
*                                        SEC_CHAR ** pcName);
* @endcode
* @par Purpose
* To get the value of a particular attribute from the subject name of
* of the certificate.
* @par Description
* SEC_PKI_getAttrFromSubjectName returns an attribute value and length 
* for a given attribute type 
* present in the subject name of the certificate as a data buffer.
* The data buffer is filled and function returns successful only if 
* all the character/symbol in attribute lie in set of 32 to 126 in ascii plus 
* horizontal tab(9), line feed(10) and carriage return(13).
*	- All ASN1 Strings are converted to NULL terminated character string.
*	- For Printable String all the characters are supported.
*	- For IA5string,T61String and UTF8String all the characters/symbol that 
* are in the set of 32 to 126 in ascii plus horizontal tab(9), line feed (10)
* and carriage return(13) are supported.
*	- For BMPString in which each character/symbol is represented by two bytes
* the first byte (Most Significant) must be zero. The second 
* byte(least Significant) character/symbol must lie in the set of  32 to 126 in 
* ascii plus horizontal tab(9), line feed(10) and carriage return(13). While 
* returning the NULL terminated string first byte(Most Significant) is removed. 
* Only Remaining byte are copied.\n
* Example if BMP string is 0x00 0x41 0x00 0x41  
* the null terminated string returned is 0x41 0x41 0x00.
*	- For Universal String in which each character/symbol is represented by 
* four bytes. the first 3 byte (Most Significant) must be zero. The last 
* byte (least Significant) character/symbol must lie in the set of 32 to 126 in 
* ascii plus horizontal tab(9), line feed(10) and carriage return(13). While  
* returning the NULL terminated string first byte (Most Significant) is 
* removed.  Only Remaining byte are copied. example. if Universal string  
* is 0x00 0x00  0x00 0x41 0x00 0x00 0x00 0x41 the null terminated string 
* returned is 0x41 0x41 0x00.\n
* 
* The attribute type can be any of the type supported in Name Structure.\n
* The Types include are as follows:\n
*	- Country, [TYPE_COUNTRY]\n
*	- Organization, [TYPE_ORGANIZATION]\n
*	- Organization Unit Name, [TYPE_ORG_UNIT_NAME]\n
*	- DNQualifier, [TYPE_DNQUALIFIER]\n
*	- State, [TYPE_STATE ]\n
*	- Serial Number, [TYPE_SERIAL_NUMBER]\n
*	- Locality, [TYPE_LOCALITY]\n
*	- Title, [TYPE_TITLE \n
*	- Surname, [TYPE_SURNAME \n
*	- GivenName, [TYPE_GIVENNAME]\n
*	- Initials, [TYPE_INITIALS \n
*	- Pseudonym, [TYPE_PSEUDONYM \n
*	- Generation Qualifier, [TYPE_GENQUALIFIER]\n
*	- Email Address, [TYPE_EMAIL ]
*	- Domain Component, [TYPE_DOMAIN_COMPONENT]\n
*	- Common Name [TYPE_COMMON_NAME] and\n
*	- Name [TYPE_NAME]\n
* For all these type Enum X509_NAME_ATTR_TYPE_E is available in X509.h.\n
* @param[in] pstCert The certificate from which a particular 
* attribute has to be obtained [NA/NA]
* @param[in] uiAttrType The Attribute type that has to be searched
* in the name structure [NA/NA]
* @param[out] pstDataBuff The Buffer structure containing the 
* value and the length [NA/NA]
* @retval SEC_INT On successful retrieval of the attribute. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* API will fail to retrieve the attributes which is of type BMP 
* and Universal string.
*
* @Par Memory Handling
* \n
* The memory for pcName will be allocated by the function. 
* To free the memory the 
* application has to call ipsi_free.
*
*/
PSELINKDLL SEC_INT SEC_PKI_getAttrFromSubjectName(X509_CERT_S *pstCert, 
                                        X509_NAME_ATTR_TYPE_E uiAttrType, 
                                        SEC_CHAR ** pcName);



/**
* @defgroup SEC_PKI_getAttrFromIssuerName
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_getAttrFromIssuerName( X509_CERT_S *pstCert, 
*                                        X509_NAME_ATTR_TYPE_E uiAttrType, 
*                                        SEC_CHAR ** pcName);
* @endcode
* @par Purpose
* To get the value of a particular attribute from the Issuer name of
* of the certificate.
* @par Description
* SEC_PKI_getAttrFromIssuerName returns an attribute value 
* and length for a given attribute type 
* present in the Issuer name of the certificate as a data buffer.
* The data buffer is filled and function returns successful only if 
* all the character/symbol in attribute lie in set of 32 to 126 in ascii plus 
* horizontal tab(9), line feed(10) and carriage return(13).
*	- All ASN1 Strings are converted to NULL terminated character string.
*	- For Printable String all the characters are supported.
*	- For IA5string,T61String and UTF8String all the characters/symbol that 
* are in the set of  32 to 126 in ascii plus horizontal tab(9), line feed (10)
* and carriage return(13) are supported.
*	- For BMPString in which each character/symbol is represented by two bytes
* the first byte (Most Significant) must be zero. The second 
* byte (least Significant) character/symbol must lie in the set of  32 to 126
* in ascii plus horizontal tab(9), line feed(10) and carriage return(13). While
* returning the NULL terminated string first byte(Most Significant) is removed. 
* Only Remaining byte are copied.\n
* Example if BMP string is 0x00 0x41 0x00 0x41  
* the null terminated string returned is 0x41 0x41 0x00.
*	- For Universal String in which each character/symbol is represented by 
* four bytes. the first 3 byte (Most Significant) must be zero. The last 
* byte (least Significant) character/symbol must lie in the set of 32 to 126 in 
* ascii plus horizontal tab(9), line feed(10) and carriage return(13). While  
* returning the NULL terminated string first byte (Most Significant) is
* removed. Only Remaining byte are copied.\n 
* Example if Universal string is 0x00 0x00
* 0x00 0x41 0x00 0x00 0x00 0x41 the null terminated string 
* returned is 0x41 0x41 0x00.\n
*
* The attribute type can be any of the type supported in Name Structure.\n
* The Types include are as follows:\n
*	- Country, [TYPE_COUNTRY]\n
*	- Organization, [TYPE_ORGANIZATION]\n
*	- Organization Unit Name, [TYPE_ORG_UNIT_NAME]\n
*	- DNQualifier, [TYPE_DNQUALIFIER]\n
*	- State, [TYPE_STATE ]\n
*	- Serial Number, [TYPE_SERIAL_NUMBER]\n
*	- Locality, [TYPE_LOCALITY]\n
*	- Title, [TYPE_TITLE \n
*	- Surname, [TYPE_SURNAME \n
*	- GivenName, [TYPE_GIVENNAME]\n
*	- Initials, [TYPE_INITIALS \n
*	- Pseudonym, [TYPE_PSEUDONYM \n
*	- Generation Qualifier, [TYPE_GENQUALIFIER]\n
*	- Email Address, [TYPE_EMAIL ]
*	- Domain Component, [TYPE_DOMAIN_COMPONENT]\n
*	- Common Name [TYPE_COMMON_NAME] and\n
*	- Name [TYPE_NAME]
* For all these type Enum X509_NAME_ATTR_TYPE_E is available in X509.h.\n
* @param[in] pstCert The certificate from which a particular attribute
* has to be obtained [NA/NA]
* @param[in] uiAttrType The Attribute type that has to be searched in
* the name structure [NA/NA]
* @param[out] pstDataBuff The Buffer structure containing the value 
* and the length [NA/NA]
* @retval SEC_INT On successful retrieval of the attribute. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* API will fail to retrieve the attributes which is of type BMP 
* and Universal string.
*
* @Par Memory Handling
* \n
* The memory for pcName will be allocated by the function. 
* To free the memory the 
* application has to call ipsi_free.
*
*/
PSELINKDLL SEC_INT SEC_PKI_getAttrFromIssuerName(X509_CERT_S *pstCert, 
                                        X509_NAME_ATTR_TYPE_E uiAttrType, 
                                        SEC_CHAR ** pcName);


/**
* @defgroup SEC_PKI_readCertFromFile
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_readCertFromFile( SEC_CHAR *pcCertfile,
* SEC_INT iType, 
* SEC_CHAR * pucPassword, 
* SEC_UINT uCertPwdLen,
* SEC_List_S **pstCertList);
*
* @endcode
*
* @par Purpose
* This function is used to extract the certificate(s) from the file.
*
* @par Description
* SEC_PKI_readCertFromBuffer function reads a file that
* contains the certificate(s) in "PEM","PFX" or "DER" format and extracts
* all the certificate(s) from the buffer and returns.
* Password is an optional input, Password is needed only for Certificates 
* which are in PFX format.
*
* @param[in] pcCertfile certificate(s) file.[NA/NA]
* @param[in] iType Mentions the formatting type 
* [SEC_PKI_FILETYPE_ASN1/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_PFX/NA]
* @param[in] pcCertPasswd password of the certificate if there [
* SEC_PKI_FILETYPE_PFX/NA].
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
* @param[out] pstCertList Contains the extracted certificate(s) [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* ipsi will allocate the memory for the pstCertList to free this memory
* application has to call the SEC_LIST_FREE with the X509_freeCert as 
* the free function.
*
* @par Note
* \n
*	- For PFX file type, zero password length is not supported.
* \n
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
* \n
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*
*/
PSELINKDLL SEC_INT SEC_PKI_readCertFromFile(
        SEC_CHAR *pcCertfile,
        SEC_INT iType, 
        SEC_CHAR * pucPassword, 
        SEC_UINT uCertPwdLen,
        SEC_List_S **pstCertList);


/**
* @defgroup SEC_PKI_isCACert
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_isCACert ( X509_CERT_S *pstCert);
*
* @endcode
*
* @par Purpose
* This function is used to check if the certificate passed 
* is a CA Certificate or not.
*
* @par Description
* SEC_PKI_isCACert function checks the input certificate
* "pstCert" is a CA Certificate or not.
* If the Input Certificate is of V1 and V2 Version then this
* function returns it as CA Certificate. Only if the Certificate 
* is of type version V3 then it will check whether it is an end 
* entity or CA Certificate.
*
* @param[in] pstCert X509 Certificate [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT if pstCert is CA [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT if pstCert is not a CA or On all failure 
* conditions [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* Basic Constraint being present and set as CA is the only condition 
* in which a v3 certificate is considered to be a CA certificate.
*
*/
PSELINKDLL SEC_INT SEC_PKI_isCACert (X509_CERT_S *pstCert);

/**
* @defgroup SEC_PKI_sortCertChain
* @ingroup Utility_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_sortCertChain(SEC_List_S *pstCertChain, 
*    SEC_List_S **pstOutChain);
*
* @endcode
*
* @par Purpose
* This function is used to sort the input certificate chain
*
* @par Description
* SEC_PKI_sortCertChain function sorts the input certificate chain
*
* @param[in] pstCertChain X509 Certificate chain [NA/NA]
* @param[out] pstOutChain X509 Certificate chain [NA/NA]
*
* @retval SEC_INT on success  [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT on failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* To free the output chain pstOutChaapplication should
* call the SEC_LIST_FREE with the X509_freeCert as free function
*
*/
PSELINKDLL SEC_INT SEC_PKI_sortCertChain(SEC_List_S *pstCertChain, 
    SEC_List_S **pstOutChain);
#ifdef  __cplusplus
}
#endif

#endif /*__SEC_PKI_UTIL_H__*/

#endif // IPSI_SEC_NO_PKI

