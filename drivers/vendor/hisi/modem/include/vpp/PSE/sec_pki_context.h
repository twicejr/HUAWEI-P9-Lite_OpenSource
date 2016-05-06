/***************************************************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: sec_pki_context.h
Version: 1
Author:
Creation Date:
Description: This file contains the identified functions of PKI context.
To authenticate each session using PKI, each session should have the following
information Trusted CA Certificate(s), CRL(s), Verification Configuration, and
Local end entity certificate(s) and associated private key(s).

For a particular client each session different peers, will have the same set of
trusted CA certificate(s), CRL(s). Verification Configuration and end entity
certificate(s) may differ.

PKI Context eliminates the need for storing same kind of information in all the
session level objects. It will store all the CA Certificate(s), CRL(S) and
local certificate(s) and its associated private key(s) and Verification
Configuration.

PKI objects will be derived using this context, All PKI Objects which are
derived from the same context will have the same trust store but each object
can override the local certificate(s) and verification configuration which are
derived from the context.

Ideally for a particular client one Context is enough, using this many objects
can be derived for each different session.

Context should be created and used in the main thread. Objects are created
and used in a separate thread.Parallel opeations on a single conext/Object is
not supported.

Function List:

History:
<Author>   <date>          <desc>

***************************************************************************/
#include "ipsi_pse_build_conf.h"

#ifndef __SEC_PKI_CONTEXT_H__
#define __SEC_PKI_CONTEXT_H__

#include "ipsi_types.h"
#include "sec_pki_buildconf.h"
#include "sec_sys.h"
#include "sec_list.h"
#include "sec_crypto.h"
#include "sec_pki_def.h"
#include "x509_basictypes.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef IPSI_SEC_NO_PKI

/**
* @defgroup PKI
* This section contains all the enums, structures, and functions in the PKI 
* library.
*/

/**
* @defgroup Context_Functions
* @ingroup PKI
* This contains all the context functions of PKI library.
*/

/**
* @defgroup SEC_PKI_ctxNew
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_PKI_CTX_S * SEC_PKI_ctxNew(SEC_VOID);
* @endcode
*
* @par Purpose
* This function is used to create a new PKI context object.
*
* @par Description
* SEC_PKI_ctxNew creates a new SEC_PKI_CTX_S object.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_PKI_CTX_S* If the creation of a new SEC_PKI_CTX_S context is 
* successful.[NA|NA]
* @retval NULL If the creation of a new SEC_PKI_CTX_S context is fails.
* [NULL|NA]
*
*
* @par Memory Handling
* \n
* ipsi will allocate memory for SEC_PKI_CTX_S and returns to the application.
* To free this memory user has to call the SEC_PKI_ctxFree function.
*/
PSELINKDLL SEC_PKI_CTX_S *SEC_PKI_ctxNew(SEC_VOID);

/**
* @defgroup SEC_PKI_ctxSetName
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxSetName( SEC_PKI_CTX_S *pstContext,
*                        SEC_CHAR *pcName,SEC_UINT ilen);
* @endcode
*
* @par Purpose
* This function is used to set the name for the context.
*
* @par Description
* SEC_PKI_ctxSetName function is used to set the name for the object.
* If the input name is NULL terminated, then user should pass the length 
* of the name including the NULL.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcName Name of the pstContext.[NA/NA]
* @param[in] ilen Length of the name. Length cannot be more than 
* PKI_NAME_MAXLEN(256). [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxSetName(SEC_PKI_CTX_S *pstContext,
                       SEC_CHAR *pcName,SEC_UINT iLen);

/**
* @defgroup SEC_PKI_ctxGetName
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetName( SEC_PKI_CTX_S *pstContext,
*                        SEC_CHAR *pcName,SEC_UINT ilen,
*                        SEC_UINT* pinamelen);
* @endcode
*
* @par Purpose
* This function is used to get the name from the context.
*
* @par Description
* SEC_PKI_ctxGetName is used to get the name associated with the context.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S. [NA/NA]
* @param[in] ilen Length of the pcName buffer.[NA/NA]
* @param[out] pinamelen Store length of context name. [NA/NA]
* @param[out] pcName Contains the name associated with the pstContext else
* contains NULL.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* Application should allocate and free the memory for the pcName.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetName(SEC_PKI_CTX_S *pstContext,
                       SEC_CHAR *pcName,SEC_UINT ilen,
                       SEC_UINT* pinamelen);


/**
* @defgroup SEC_PKI_ctxFree
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_VOID SEC_PKI_ctxFree ( SEC_PKI_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This function is used to free an PKI context object.
*
* @par Description
* The SEC_PKI_ctxFree function checks the reference count of context and
* removes the SEC_PKI_CTX_S object pointed to ctx and frees the allocated
* memory. If there are no reference to this context.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_VOID This function does not return any value. [NA|NA]
*/
PSELINKDLL SEC_VOID SEC_PKI_ctxFree(SEC_PKI_CTX_S *pstContext);

/**
* @defgroup SEC_PKI_ctxLoadTrustCACertificateFile
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadTrustCACertificateFile( SEC_PKI_CTX_S *pstContext,
*                                           const SEC_CHAR *pcCAfile,
                                          SEC_INT iType,
                                          SEC_CHAR *pcCertPasswd,
                                          SEC_UINT uCertPwdLen,
                                          SEC_BOOL bAddToCAReqList);
* @endcode
*
* @par Purpose
* This function is used to load the CA certificate(s) from file into the trust
* store of PKI context.
*
* @par Description
* SEC_PKI_ctxLoadTrustCACertificateFile function reads a file that contains the
* certificate in "PEM","PFX", or "DER" format, and adds the certificate to the
* trust store. Password is an optional input, and password is needed only for
* certificates which are in PFX format. To make this CA to be part of "CA
* Request list" user needs to pass bAddToCAReqList as true.
*
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S. [NA/NA]
* @param[in] pcCAfile CA file name. [NA/NA]
* @param[in] iType Mentions the file type to be loaded. 
* [SEC_PKI_FILETYPE_ASN1/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_PFX/NA]
* @param[in] pcCertPasswd Password of the certificate, if present. [
* NA/NA].
* @param[in] uCertPwdLen Length of the Password. [0-255/NA]
* @param[in] bool bAddToCAReqList Flag to indicate, if the CA has to be added to
* CA request list or not. [True/False/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid
* (NULL pointer).The failure occurs when file cannot be opened,
*  or decoding of certificate fails. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- Same file can have an end entity certificate, key file and more than one 
* intermediate CA certificates, in this case only the CA certificates are
* loaded.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*/

PSELINKDLL SEC_INT SEC_PKI_ctxLoadTrustCACertificateFile(
                                          SEC_PKI_CTX_S *pstContext,
                                          const SEC_CHAR *pcCAfile,
                                          SEC_INT iType,
                                          SEC_CHAR *pcCertPasswd,
                                          SEC_UINT uCertPwdLen,
                                          SEC_BOOL bAddToCAReqList);

/**
* @defgroup SEC_PKI_ctxLoadTrustCACertificateBuffer
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadTrustCACertificateBuffer( SEC_PKI_CTX_S *pstContext,
*                                          SEC_CHAR *pcCertBuf,
*                                          SEC_UINT uCertBufLen,
*                                          SEC_INT iType,
*                                          SEC_CHAR *pcCertPasswd,
*                                          SEC_UINT uCertPwdLen,
*                                          SEC_BOOL bAddToCAReqList);
* @endcode
*
* @par Purpose
* This function is used to load the CA certificate(s) from buffer into the trust
* store of PKI context.
*
* @par Description
* SEC_PKI_ctxLoadTrustCACertificateBuffer function reads the buffer
* that contains certificate in "PEM","PFX" or "DER" format and adds the
* certificate to the trust store. Password is an optional input, and it is
* needed only for certificates which are in PFX format. To make this 
* CA to be part of "CA Request list" user needs to pass 
* bAddToCAReqList as true.
*
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCertBuf Certificate buffer.[NA/NA]
* @param[in] uCertBufLen Certificate buffer length.[NA/NA]
* @param[in] iType Mentions the file type to be loaded.
* [SEC_PKI_FILETYPE_ASN1/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_PFX/NA]
* @param[in] pcCertPasswd Required only for SEC_PKI_FILETYPE_PFX type.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
* @param[in] bAddToCAReqList Flag to indicate, if the CA has to be added to
* CA request list or not.[NA/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid (NULL
* pointer), or decoding of certificate fails. [SEC_PKI_ERROR|NA]
*
* @Par Note
* \n
*	- A buffer can have an end entity certificate and more than one
* intermediate CA certificates, in this case only the CA certificates are
* loaded.
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). Any value other than the actual
* buffer length API behavioris undefined.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadTrustCACertificateBuffer (
                                          SEC_PKI_CTX_S *pstContext,
                                          SEC_CHAR *pcCertBuf,
                                          SEC_UINT uCertBufLen,
                                          SEC_INT iType,
                                          SEC_CHAR *pcCertPasswd,
                                          SEC_UINT uCertPwdLen,
                                          SEC_BOOL bAddToCAReqList);



/**
* @defgroup SEC_PKI_ctxLoadTrustCrossCACertificateFile
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadTrustCrossCACertificateFile(
*                                          SEC_PKI_CTX_S *pstContext,
*                                          const SEC_CHAR *pcCAfile,
*                                          SEC_INT iType,
*                                          SEC_CHAR *pcCertPasswd,
*                                          SEC_UINT uCertPwdLen);
* @endcode
*
* @par Purpose
* This function is used to load the Cross CA certificate(s) from file into the
* trust store of PKI context.
*
* @par Description
* SEC_PKI_ctxLoadTrustCrossCACertificateFile function reads a file that
* contains the cross ca certificate in "PEM","PFX", or "DER" format and adds the
* certificate to the trust store. Password is an optional input, and it is
* needed only for certificates which are in PFX format.
*
*
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCAfile CA File Name.[NA/NA]
* @param[in] iType Mentions the file type to be loaded.
* [SEC_PKI_FILETYPE_ASN1/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_PFX/NA]
* @param[in] pcCertPasswd Password of the certificate, if present [
* NA/NA].
* @param[in] uCertPwdLen Length of the password.[0-255/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid 
* (NULL pointer), when file cannot be opened, 
* or decoding of certificate fails  [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- If a file contains more than one certificate, all certificates
* will be loaded (other than X509 V3 end
* entity certificate and self signed certificates). 
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadTrustCrossCACertificateFile(
                                          SEC_PKI_CTX_S *pstContext,
                                          const SEC_CHAR *pcCAfile,
                                          SEC_INT iType,
                                          SEC_CHAR *pcCertPasswd,
                                          SEC_UINT uCertPwdLen);


/**
* @defgroup SEC_PKI_ctxLoadTrustCrossCACertificateBuffer
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadTrustCrossCACertificateBuffer (
*                                             SEC_PKI_CTX_S *pstContext,
*                                             SEC_CHAR *pcCertBuf,
*                                             SEC_UINT uCertBufLen,
*                                             SEC_INT iType,
*                                             SEC_CHAR *pcCertPasswd,
*                                             SEC_UINT uCertPwdLen);
* @endcode
*
* @par Purpose
* This function is used to load the Cross CA certificate(s) from buffer into the
* trust store of PKI context.
*
* @par Description
* SEC_PKI_ctxLoadTrustCrossCACertificateBuffer function reads a buffer that
* contains the cross ca certificate in "PEM","PFX", or "DER" format, and adds 
* the certificate to the trust store. Password is an optional input, and it is 
* needed only for certificates which are in PFX format.
*
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCertBuf Certificate buffer.[NA/NA]
* @param[in] uCertBufLen Certificate buffer length.[NA/NA]
* @param[in] iType Mentions the file type to be loaded.
* [SEC_PKI_FILETYPE_ASN1/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_PFX./NA]
* @param[in] pcCertPasswd Required only for SEC_PKI_FILETYPE_PFX type.[NA/NA]
* @param[in] uCertPwdLen Length of the password.[0-255/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid (NULL
* pointer) or decoding of certificate fails. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- If a buffer contains more than one certificate, other than X509 V3 end 
* entity certificate and self signed certificates, all other certificates
* will be loaded.
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). Any value other than the actual
* buffer length API behavioris undefined.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadTrustCrossCACertificateBuffer (
                                          SEC_PKI_CTX_S *pstContext,
                                          SEC_CHAR *pcCertBuf,
                                          SEC_UINT uCertBufLen,
                                          SEC_INT iType,
                                          SEC_CHAR *pcCertPasswd,
                                          SEC_UINT uCertPwdLen);


/**
* @defgroup SEC_PKI_ctxLoadCrlFile
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadCrlFile( SEC_PKI_CTX_S *pstContext,
*                            const SEC_CHAR *CRLfile,
*                            SEC_INT iType);
* @endcode
*
* @par Purpose
* This function is used to load the CRL from the file to the store.
*
* @par Description
* SEC_PKI_ctxLoadCrlFile function reads a file that contains a CRL
* (Certificate Revocation List) in "PEM" or "DER" format and adds the CRL to
* the context.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] CRLfile FileName.[NA/NA]
* @param[in] iType Mentions the file type to be loaded.
* [SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid 
* (NULL pointer), when file cannot be opened, 
* or decoding of CRL fails.[SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- It is recommended that crl dates are verified before loading the same.\n
*	- PEM list of CRL is not suppoted.
*	- If the same crl already exist in the store then error will be returned.
*/

PSELINKDLL SEC_INT SEC_PKI_ctxLoadCrlFile(SEC_PKI_CTX_S *pstContext,
                           const SEC_CHAR *pcCrlFile,
                           SEC_INT iType);

/**
* @defgroup SEC_PKI_ctxLoadCrlBuffer
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadCrlBuffer( SEC_PKI_CTX_S *pstContext,
*                               SEC_CHAR *pcCrlBuffer,
*                               SEC_UINT uCrlBufLen,
*                               SEC_INT type);
* @endcode
*
* @par Purpose
* This function is used to load the CRL from the buffer to store.
*
* @par Description
* SEC_PKI_ctxLoadCrlBuffer function decodes buffer that contains a CRL 
* (Certificate Revocation List) in "PEM" or "DER" format, and adds the CRL 
* to the store.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S. [NA/NA]
* @param[in] pcCrlBuffer CRL buffer.[NA/NA]
* @param[in] uCrlBufLen CRL buffer length.[NA/NA]
* @param[in] iType Mentions the file type to be loaded.
* [SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid 
* (NULL pointer)or decoding of CRL fails. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- It is recommended that crl dates are verified before loading the same.\n
*	- In case of buffer length, validation is done only for the value of zero.
*    [Value zero is considered to be invalid].Any value other than the actual
*    buffer length ,API behavioris undefined.
*	- If the same crl already exist in the store then error will be returned.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadCrlBuffer(SEC_PKI_CTX_S *pstContext,
                             SEC_CHAR *pcCrlBuffer,
                             SEC_UINT uCrlBufLen,
                             SEC_INT iType);


/**
* @defgroup SEC_PKI_ctxLoadDfltLocalCertAndKeyFile
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadDfltLocalCertAndKeyFile( SEC_PKI_CTX_S *pstContext,
                                            const SEC_CHAR *pcCertFile,
                                            SEC_INT iCertFileType,
                                            const SEC_CHAR *pcCertPasswd,
                                            SEC_UINT uCertPwdLen,
                                            const SEC_CHAR *pcKeyFile,
                                            SEC_INT iKeyFileType,
                                            const SEC_CHAR *pcKeyPasswd,
                                            SEC_UINT uKeyPwdLen,
                                            const SEC_CHAR *pcURL,
                                            SEC_UINT uUrlLen);

* @endcode
*
* @par Purpose
* This function is used to load the certificate and key from the file to
* default certificate and key of the PKI context.
*
* @par Description
* SEC_PKI_ctxLoadDfltLocalCertAndKeyFile function reads a certificate and key 
* file that contains the certificate and key in "PEM","PFX", or "DER" format,
* and adds the certificate and key to the default certificate and key of 
* the PKI Context. Certificate Password is an optional input but, applicable 
* only for PFX format. Key file password is also optional. To associate URL for 
* this certificate set pcURL to the appropriate URL but it is an optional input.
* If SEC_PKI_IGNORE_PVT_KEY_LOAD option is set in the context, then only local 
* certificate will be loaded without the privatekey. Private key parameters will
* be completely ignored.
*
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCertFile The name of the file from which the certificate has to
* be loaded.[NA/NA]
* @param[in] iCertFileType Mentions the file type to be loaded.
*[SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the password.[0-255/NA]
* @param[in] pcKeyFile The file which contains the private key of the
* certificate.[NA/NA]
* @param[in] iKeyFileType Mentions the key file type to be loaded.
*[SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[in] pcURL URL Where this Certificate can be downloaded.[NA/NA]
* @param[in] uUrlLen Length of the URL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid
* (NULL pointer).
* The failure can occur, if the input is invalid(NULL pointer),
* file cannot be opened, or decoding of certificate
* fails. [SEC_PKI_ERROR|NA]
* @par Note
* \n
*	- A file can contain both the certificate and key, in such a case same file
*    name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- Only one url is supported.
*	- In case of file having multiple certificates, first certificate will be
*  considered as end entity certificate.
*	- Default local cert is a special kind of local cert, where 
* the default certificate is the preferred certificate.
* All search on local cert begins with default cert. 
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
* present in PFX.
*		- Enc password - Used for encrypting the baglist or 
* the key before storing into bag. Cert can be encrypted 
* only by encrypting the baglist. But, key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		- Same file containing both the certificate and private key 
*    whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
*         password are also different
*		- If a file has multiple encrypted or unencrypted baglists.
* Then the first certificate from the first encrypted baglist will be taken
* for checking. If the certificate is not present in the first encrypted 
* baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
* baglists, the first private key from the first encrypted/unencrypted 
* baglist is taken.
* If the privatekey is not present in the first baglist, then 
* the privatekey is searched in the other baglists. If the 
* private key is not present in any of the baglists,
* then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadDfltLocalCertAndKeyFile (
                                            SEC_PKI_CTX_S *pstContext,
                                            const SEC_CHAR *pcCertFile,
                                            SEC_INT iCertFileType,
                                            const SEC_CHAR *pcCertPasswd,
                                            SEC_UINT uCertPwdLen,
                                            const SEC_CHAR *pcKeyFile,
                                            SEC_INT iKeyFileType,
                                            const SEC_CHAR *pcKeyPasswd,
                                            SEC_UINT uKeyPwdLen,
                                            const SEC_CHAR *pcURL,
                                            SEC_UINT uUrlLen);


/**
* @defgroup SEC_PKI_ctxLoadDfltLocalCertAndKeyBuffer
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadDfltLocalCertAndKeyBuffer( SEC_PKI_CTX_S *pstContext,
*                                              const SEC_CHAR *pcCertBuffer,
*                                              SEC_UINT uCertBufLen,
*                                              SEC_INT iCertType,
*                                              const SEC_CHAR *pcCertPasswd,
*                                              SEC_UINT uCertPwdLen,
*                                              const SEC_CHAR *pcKeyBuffer,
*                                              SEC_UINT uKeyBufLen
*                                              SEC_INT iKeyType,
*                                              const SEC_CHAR *pcKeyPasswd,
*                                              SEC_UINT uKeyPwdLen
*                                              const SEC_CHAR *pcURL,
*                                              SEC_UINT uUrlLen);
* @endcode
*
* @par Purpose
* This function is used to load the certificate and key from the buffer to the
* default certificate and key of the PKI context.
*
* @par Description
* SEC_PKI_ctxLoadDfltLocalCertAndKeyBuffer function reads a buffer that contains
* the certificate and key in "PEM","PFX", or "DER" format and Adds the
* Certificate and key to the default certificate and key of the PKI context.
* Certificate password is an optional input and applicable only
* for PFX format. Key password is also optional. To associate URL for this
* Certificate set pcURL to the appropriate URL but it is an optional Input.
* If SEC_PKI_IGNORE_PVT_KEY_LOAD option is set in the context, then only local 
* certificate will be loaded without the privatekey. Private key parameters will
* be completely ignored.
*
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCertBuffer The buffer from which the certificate has to be
* loaded. [NA/NA]
* @param[in] uCertBufLen Length of the certificate Buffer.[NA/NA]
* @param[in] iCertFileType certificate file type, Mentions the file type 
* to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
* @param[in] pcKeyBuffer The buffer which contains the private key.[NA/NA]
* @param[in] uKeyBufLen Length of the private key Buffer.[NA/NA]
* @param[in] iKeyType Mentions the key type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[in] pcURL URL where this certificate can be downloaded.[NA/NA]
* @param[in] uUrlLen Length of the URL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. If the input is invalid
* (NULL pointer).
* [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- A file can contain both the certificate and key, in this case same file
*    Name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- Only one url is supported.
*	- In case of buffer length, validation is done only for the value of zero.
*  (Value zero is considered to be invalid). Any value other than the actual
*  buffer length ,API behavior is undefined.
*	- In case of buffer having multiple certificates, first certificate will be
*  considered as end entity certificate.
*	- Default local cert is a special kind of local cert, where 
* the default certificate is the preferred certificate.
* All search on local cert begins with default cert. 
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
*		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
* present in PFX.
*		- Enc password - Used for encrypting the baglist or 
* the key before storing into bag. Cert can be encrypted 
* only by encrypting the baglist. But, key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		- Same file containing both the certificate and private key 
*    whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
*         password are also different
*		- If a file has multiple encrypted or unencrypted baglists.
* Then the first certificate from the first encrypted baglist will be taken
* for checking. If the certificate is not present in the first encrypted 
* baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
* baglists, then the first private key from the first encrypted/unencrypted 
* baglist is taken.
* If the privatekey is not present in the first baglist, then 
* the privatekey is searched in the other baglists. If the 
* private key is not present in any of the baglists,
* then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadDfltLocalCertAndKeyBuffer(
                                             SEC_PKI_CTX_S *pstContext,
                                             const SEC_CHAR *pcCertBuffer,
                                             SEC_UINT uCertBufLen,
                                             SEC_INT iCertType,
                                             const SEC_CHAR *pcCertPasswd,
                                             SEC_UINT uCertPwdLen,
                                             const SEC_CHAR *pcKeyBuffer,
                                             SEC_UINT uKeyBufLen,
                                             SEC_INT iKeyType,
                                             const SEC_CHAR *pcKeyPasswd,
                                             SEC_UINT uKeyPwdLen,
                                             const SEC_CHAR *pcURL,
                                             SEC_UINT uUrlLen);

#ifndef __SEC_PKI_NO_PEER_CACHE__

/**
* @defgroup SEC_PKI_ctxGetPeerCacheSize
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetPeerCacheSize( SEC_PKI_CTX_S *pstContext,
*                                     SEC_UINT *puiSize);
*
* @endcode
*
* @par Purpose
* This function is used to get the cache size for the peer certificates.
*
* @par Description
* SEC_PKI_ctxGetPeerCacheSize function will return the size of the cache for
* the peer certififcates.
*
* @param [in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] puiSize Size of cache. [NA/10]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*
* @par Related Topics
* SEC_PKI_ctxResizePeerCache\n
* SEC_PKI_objGetCtxPeerCertByHash
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetPeerCacheSize(SEC_PKI_CTX_S *pstContext,
                                               SEC_UINT *puiSize);


/**
* @defgroup SEC_PKI_ctxResizePeerCache
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxResizePeerCache( SEC_PKI_CTX_S *pstContext,
*                                   SEC_INT iSize);
*
* @endcode
*
* @par Purpose
* This function is used to resize the cache for the peer certificates.
*
* @par Description
* SEC_PKI_ctxResizePeerCache function will resize cache for
* the peer certififcates that is, it will increase/decrease the list element of 
* the peer cache.
*
* @param [in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param [in] iSize New size of the peer cache.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. Negative value is not a valid
* input. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* Zero will disable the cache.
*
* @par Related Topics
* SEC_PKI_ctxGetPeerCacheSize\n
* SEC_PKI_objGetCtxPeerCertByHash
*/
PSELINKDLL SEC_INT SEC_PKI_ctxResizePeerCache(SEC_PKI_CTX_S *pstContext,
                                              SEC_INT iSize);

#endif

#ifndef __SEC_PKI_NO_MULTIPLE_LOCAL_CERT__

/**
* @defgroup SEC_PKI_ctxLoadLocalCertAndKeyFile
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadLocalCertAndKeyFile( SEC_PKI_CTX_S *pstContext,
*                                            const SEC_CHAR *pcCertFile,
*                                            SEC_INT iCertFieType,
*                                            SEC_CHAR *pcCertPasswd,
*                                            SEC_UINT uCertPwdLen,
*                                            const SEC_CHAR *pcKeyFile,
*                                            SEC_INT iKeyFileType,
*                                            SEC_CHAR *pcKeyPasswd,
*                                            SEC_UINT uKeyPwdLen
*                                            SEC_CHAR *pcURL,
*                                            SEC_UINT uUrlLen);
* @endcode
*
* @par Purpose
* This function is used to load the certificate and key from the file to
* local certificate and key list of the PKI context.
*
* @par Description
* SEC_PKI_ctxLoadLocalCertAndKeyFile function reads a certificate and key 
* file that contains the certificate and key in "PEM","PFX", or "DER" format,
* and adds the certificate and key to the local certificate and key list of 
* the PKI Context. The local certificates are added to the local list and not 
* overridden like default certificate.
* Certificate password is an optional input but, applicable 
* only for PFX format and key file password is also optional. To associate URL 
* for this certificate set pcURL to the appropriate URL but it is an optional
* input.If SEC_PKI_IGNORE_PVT_KEY_LOAD option is set in the context, then only  
* local certificate will be loaded without the privatekey. Private key 
* parameters will be completely ignored.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCertFile The name of the file from which the certificate has to
* be loaded.[NA/NA]
* @param[in] iCertFileType Mentions the file type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the password. [0-255/NA]
* @param[in] pcKeyFile The file which contains the private key of the
* certificate.[NA/NA]
* @param[in] iKeyFileType Mentions the key file type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[in] pcURL URL Where this Certificate can be downloaded.[NA/NA]
* @param[in] uUrlLen Length of the URL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- A file can contain both the certificate and key, in such a case same file
*    name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- Only one url is supported per local certificate loaded.
*	- In case of file having multiple certificates, first certificate will be
* considered as end entity certificate.
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
*		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
* present in PFX.
*		- Enc password - Used for encrypting the baglist or encrypting 
* the key before storing into bag. Hence cert can be encrypted 
* only by encrypting the baglist. But, key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		-  Same file containing both the certificate and private key 
*    whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
*         password are also different
*		- If a file has multiple encrypted or unencrypted baglists.
* Then the first certificate from the first encrypted baglist will be taken
* for checking. If the certificate is not present in the first encrypted 
* baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
* baglists, then the first private key from the first encrypted/unencrypted 
* baglist is taken.
* If the privatekey is not present in the first baglist, then 
* the privatekey is searched in the other baglists. If the 
* private key is not present in any of the baglists,
* then the API returns failure.
*	- For PFX file type zero password length is not supported.
*	- If the file type is PFX, then the PFX file should be created with 
* encrypted password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadLocalCertAndKeyFile (
                                            SEC_PKI_CTX_S *pstContext,
                                            const SEC_CHAR *pcCertFile,
                                            SEC_INT iCertFileType,
                                            const SEC_CHAR *pcCertPasswd,
                                            SEC_UINT uCertPwdLen,
                                            const SEC_CHAR *pcKeyFile,
                                            SEC_INT iKeyFileType,
                                            const SEC_CHAR *pcKeyPasswd,
                                            SEC_UINT uKeyPwdLen,
                                            const SEC_CHAR *pcURL,
                                            SEC_UINT uUrlLen);


/**
* @defgroup SEC_PKI_ctxLoadLocalCertAndKeyBuffer
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadLocalCertAndKeyBuffer( SEC_PKI_CTX_S *pstContext,
*                                              const SEC_CHAR *pcCertBuffer,
*                                              SEC_UINT uCertBufLen,
*                                              SEC_INT iCertType,
*                                              const SEC_CHAR *pcCertPasswd,
*                                              SEC_UINT uCertPwdLen,
*                                              const SEC_CHAR *pcKeyBuffer,
*                                              SEC_UINT uKeyBufLen
*                                              SEC_INT iKeyType,
*                                              const SEC_CHAR *pcKeyPasswd,
*                                              SEC_UINT uKeyPwdLen
*                                              const SEC_CHAR *pcURL,
*                                              SEC_UINT uUrlLen);
* @endcode
*
* @par Purpose
* This function is used to load the certificate and key from the buffer to the
* local certificate and key list of the PKI context.
*
* @par Description
* SEC_PKI_ctxLoadLocalCertAndKeyFile function reads a buffer that contains
* the certificate and key in "PEM","PFX", or "DER" format and adds the
* certificate and key to the local certificate and key list of the PKI context.
* The local certificates are added to the local list and not overridden as
* default certificate.
* Certificate password is an optional input and applicable only
* for PFX format and key password is also optional. To associate URL for this
* certificate set pcURL to the appropriate URL but it is an optional Input.
* If SEC_PKI_IGNORE_PVT_KEY_LOAD option is set in the context, then only local 
* certificate will be loaded without the privatekey. Private key parameters will
* be completely ignored.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCertBuffer The buffer from which the certificate has to be
* loaded. [NA/NA]
* @param[in] uCertBufLen Length of the certificate Buffer.[NA/NA]
* @param[in] iCertFileType certificate file type, Mentions the file type 
* to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
* @param[in] pcKeyBuffer The buffer which contains the private key.[NA/NA]
* @param[in] uKeyBufLen Length of the private key Buffer.[NA/NA]
* @param[in] iKeyType Mentions the key type to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcKeyPasswd Password of the private key file.[NA/NA]
* @param[in] uKeyPwdLen Length of the password.[0-255/NA]
* @param[in] pcURL URL where this certificate can be downloaded.[NA/NA]
* @param[in] uUrlLen Length of the URL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- A file can contain both the certificate and key, in such a case same file
* mame should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- Only one url is supported per local certificate loaded.
*	- In case of buffer length, validation is done only for the value of zero.
*  (Value zero is considered to be invalid). If any value other than the actual
*  buffer length, API behaviour is undefined.
*	- In case of buffer having multiple certificates, first certificate will be
*  considered as end entity certificate.
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
*		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
* present in PFX.
*		- Enc password - Used for encrypting the baglist or encrypting 
* the key before storing into bag. Hence cert can be encrypted 
* only by encrypting the baglist, whereas key can be encrypted 
* by encrypting baglist or storing encrypted key in bag.        
*	- In PFX format,the following type of file(s) are supported:
*		-  Same file containing both the certificate and private key 
*    whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
*         password are also different
*		- If a file has multiple encrypted or unencrypted baglists.
*    The first certificate from the first encrypted baglist will be taken
*    for checking. If the certificate is not present in the first encrypted 
*    baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
*    baglists, the first private key from the first encrypted/unencrypted 
*    baglist is taken.
*    If the privatekey is not present in the first baglist, then 
*    the privatekey is searched in the other baglists. If the 
*    private key is not present in any of the baglists,
*    then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadLocalCertAndKeyBuffer(
                                             SEC_PKI_CTX_S *pstContext,
                                             const SEC_CHAR *pcCertBuffer,
                                             SEC_UINT uCertBufLen,
                                             SEC_INT iCertType,
                                             const SEC_CHAR *pcCertPasswd,
                                             SEC_UINT uCertPwdLen,
                                             const SEC_CHAR *pcKeyBuffer,
                                             SEC_UINT uKeyBufLen,
                                             SEC_INT iKeyType,
                                             const SEC_CHAR *pcKeyPasswd,
                                             SEC_UINT uKeyPwdLen,
                                             const SEC_CHAR *pcURL,
                                             SEC_UINT uUrlLen);


#endif

/**
* @defgroup SEC_PKI_ctxSetTime
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxSetTime( SEC_PKI_CTX_S *pstContext,
*                       const DATETIME_S *pstTime);
* @endcode
*
* @par Purpose
* This function is used to set time in the context.
*
* @par Description
* SEC_PKI_ctxSetTime function sets the time in the context, this time is used
* for checking the certificate and CRL validity period.
*
* @param [in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param [in] pstTime Time to be set[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- The ucUTCSign, ucUTCHour, ucUTCMinute, and uwMillSecond fields of 
* DATETIME_S structure will not be used by our functionality and hence these 
* fields are not considered and validated.
* \n
*	- On windows the input time is considered valid, if it can be converted to a
* calender value using mktime.
* \n
*	- For Dopra the value of uwYear field in DATETIME_S structure can 
* be in the range from 1970 to 2134.
*	- If the setTime is not used during validation with the check time flag, 
* system time will be used.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxSetTime(SEC_PKI_CTX_S *pstContext,
                       const DATETIME_S *pstTime);

/**
* @defgroup SEC_PKI_ctxGetTime
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetTime( SEC_PKI_CTX_S *pstContext,
*                       DATETIME_S **dpstTime);
* @endcode
*
* @par Purpose
* This function is used to get the time set in the context.
*
* @par Description
* SEC_PKI_ctxGetTime function gets the time set in the context
* this time is used for checking the certificate and CRL validity period.
*
* @param [in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param [out] dpstTime Contains the time set in the context.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- If time is not set, then the function will return an error.
* \n
*	- The ucUTCSign, ucUTCHour, ucUTCMinute, and uwMillSecond fields 
* of DATETIME_S structure is not used by our functionality and hence time 
* check that has been set will be provided as the output, without giving 
* importance to these fields are valid.
*@par Menory Handling
* \n
* This function internally allocates memory for the time structure,
* memory allocated can be freed using ipsi_free function.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetTime(SEC_PKI_CTX_S *pstContext,
                       DATETIME_S **dpstTime);


/**
* @defgroup SEC_PKI_ctxSetVerifyDepth
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxSetVerifyDepth ( SEC_PKI_CTX_S *pstContext,
                               SEC_INT iDepth);
* @endcode
*
* @par Purpose
* This function is used to set verification depth in the context.
*
* @par Description
* SEC_PKI_ctxSetVerifyDepth function sets verification depth in the context.
* The certificate validation has to be performed until this depth.
* Verification depth [iDepth] value should be greater or equal to 0, otherwise 
* API returns error.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] iDepth Depth of the certificate validation.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If the verification depth is not set, (Depth is not set in context 
* and object), and SEC_PKI_objValidateCertChain API is called,
* then depth value of zero will be considered.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxSetVerifyDepth (SEC_PKI_CTX_S *pstContext,
                               SEC_INT iDepth);

/**
* @defgroup SEC_PKI_ctxGetVerifyDepth
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetVerifyDepth ( SEC_PKI_CTX_S *pstContext,
*                                SEC_INT *piDepth);
* @endcode
*
* @par Purpose
* This function is used to get the verification depth of the context.
*
* @par Description
* SEC_PKI_ctxGetVerifyDepth function gets verification depth of the context.
* The certificate validation has to be performed until this depth.
* If this API is called before calling the set depth then API returns error.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] piDepth Contains the depth of the certificate validation.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetVerifyDepth (SEC_PKI_CTX_S *pstContext,
                               SEC_INT *piDepth);


/**
* @defgroup SEC_PKI_ctxSetVerifyParam
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxSetVerifyParam( SEC_PKI_CTX_S *pstContext,
*                                   SEC_UINT  verifyFlags);
* @endcode
*
* @par Purpose
* This function is used to set the verify parameter in to context.
*
* @par Description
* SEC_PKI_ctxSetVerifyParam function sets the verify parameter in to context.
* Each new flag passed is ORed with existing flag.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] verifyFlags Verify parameter flags to be set.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* Setting of the CRL flags and OCSP flags results in the API failure.
* 
* The following CRL flags (SEC_PKI_CHECK_CRL | SEC_PKI_CHECK_CRL_ALL 
* | SEC_PKI_CHECK_DELTA_CRL | SEC_PKI_CHECK_CRL_CROSS_CA | 
* SEC_PKI_EXTENDED_CRL_SUPPORT | SEC_PKI_OBJ_CRL_SUPPORT) conflict
* with the OCSP flags (SEC_PKI_CHECK_OCSP | SEC_PKI_CHECK_OCSP_ALL 
* | SEC_PKI_OCSP_RESPONDER_CHECK_CRL | SEC_PKI_OCSP_RESPONDER_CHECK_DELTA_CRL | 
* SEC_PKI_OCSP_TRUST_RESPONDER_CERTS_IN_MSG | SEC_PKI_OBJ_OCSP_SUPPORT)
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxSetVerifyParam(SEC_PKI_CTX_S *pstContext,
                                   SEC_UINT  verifyFlags);


/**
* @defgroup SEC_PKI_ctxGetVerifyParam
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetVerifyParam( SEC_PKI_CTX_S *pstContext,
*                               SEC_UINT *pVerifyFlags);
* @endcode
*
* @par Purpose
* This function is used to get the verify parameter set in the context.
*
* @par Description
* SEC_PKI_ctxGetVerifyParam function gets verify parameter set in the context.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] pVerifyFlags Contains the verify paramerter flags.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If no flags are set, then the function will return error.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetVerifyParam(SEC_PKI_CTX_S *pstContext,
                               SEC_UINT *pVerifyFlags);

/**
* @defgroup SEC_PKI_ctxClearVerifyParam
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxClearVerifyParam( SEC_PKI_CTX_S *pstContext,
*                                 SEC_UINT verifyFlags);
* @endcode
* @par Purpose
* This function is used to clear the verify parameter set in the context.
*
* @par Description
* SEC_PKI_ctxClearVerifyParam function clears the verify parameter flags
* set in the Context.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] verifyFlags Verify paramerter flags to be reset.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxClearVerifyParam(SEC_PKI_CTX_S *pstContext,
                                 SEC_UINT verifyFlags);

/**
* @defgroup SEC_PKI_ctxGetCACertReq
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetCACertReq( SEC_PKI_CTX_S *pstContext,
*                            SEC_PKI_PARAMETER_E enId,
*                            SEC_List_S **dpOutList);
* @endcode
*
* @par Purpose
* This function is used to get the list of hash (or)
* encoded subject name (or) certificates,
* of CA's from CA request list using the context pointer.
*
* @par Description
* SEC_PKI_ctxGetCACertReq function gets the CA Certificate(s) or CA 
* Certificate(s) information (hash/encoded subject name) based on the input
* subject name) based on the input parameter type enId, and provide
* the required output list in dpOutList. The requested data will be
* extracted from the trust store of CA certs which are indicated to be
* part of cert request list while loading of the CA certificate(s).
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] enId parameter type 
* [SEC_PKI_CAPUBLICKEY/SEC_PKI_CASUBJECT/SEC_PKI_CACERT/NA]
* @param[out] dpOutList List which contains output list. 
*	- If the SEC_PKI_PARAMETER_E is SEC_PKI_CAPUBLICKEY or
* SEC_PKI_CASUBJECT then the dpOutList contains the elements 
* of type SEC_PKI_DATA_BUF_S\n
*	- If the SEC_PKI_PARAMETER_E is SEC_PKI_CACERT
* then the dpOutList contains the elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* This function will allocate the memory for dpOutList (the list may
* contain one or more entries), to free this memory application has to
* call SEC_LIST_FREE, with the free function as SEC_PKI_freeDataBuf,
* if the SEC_PKI_PARAMETER_E is SEC_PKI_CAPUBLICKEY or SEC_PKI_CASUBJECT
* else with the free function X509_freeCert if the SEC_PKI_PARAMETER_E is
* SEC_PKI_CACERT.
*
* @par Note
* \n
*	- Output subject name will be provided in encoded DER format.
*	- Output hash will be of type SHA1.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetCACertReq(SEC_PKI_CTX_S *pstContext,
                            SEC_PKI_PARAMETER_E enId,
                            SEC_List_S **dpOutList);


/**
* @defgroup SEC_PKI_ctxGetAllTrustCA
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetAllTrustCA( SEC_PKI_CTX_S *pstContext,
*                              SEC_List_S **dpOutCertList);
* @endcode
*
* @par Purpose
* This function is used to get all CA certificates.
*
* @par Description
* SEC_PKI_ctxGetAllTrustCA function gets All CA certificates
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] dpOutCertList List which contains all the certs.
* pOutCertList is a list which holds elements of type X509_CERT_S[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* ipsi will allocate the memory for the pOutCertList (the list may contain one
* or more entries), to free this memory application has to call the
* SEC_LIST_FREE,with the free function as X509_freeCert.
* @par Note
* \n
* - Retrival order might not be same as loading order of CA.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetAllTrustCA(SEC_PKI_CTX_S *pstContext,
                            SEC_List_S **dpOutCertList);


/**
* @defgroup SEC_PKI_ctxGetAllCRL
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetAllCRL( SEC_PKI_CTX_S *pstContext,
*                               SEC_List_S **dpOutCRLList);
* @endcode
*
* @par Purpose
* This function is used to get all CRL from store.
*
* @par Description
* SEC_PKI_ctxGetAllCRL function gets all CRL from store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] dpOutCRLList List which contains all the CRLs.
* dpOutCRLList is a list which holds elements of type X509_CRL_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* ipsi will allocate the memory for the dpOutCRLList (the list may contain one
* or more entries) to free this memory application as to call the
* SEC_LIST_FREE, with the free function as X509CRL_free.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetAllCRL(SEC_PKI_CTX_S *pstContext,
                         SEC_List_S **dpOutCRLList);

/**
* @defgroup SEC_PKI_ctxGetAllTrustCrossCA
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetAllTrustCrossCA( SEC_PKI_CTX_S *pstContext,
*                            SEC_List_S **dpOutCrossCAList)
* @endcode
*
* @par Purpose
* This function is used to get all cross CA from store.
*
* @par Description
* SEC_PKI_ctxGetAllTrustCrossCA function gets all cross CA from store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] dpOutCrossCAList List which contains all cross CA.
* dpOutCrossCAList is a list which holds elements of type X509_CERT_S[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* ipsi will allocate the memory for the dpOutCrossCAList ( the list may 
* contain one or more entries), to free this memory application has to 
* call the SEC_LIST_FREE, with the free function as X509_freeCert.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetAllTrustCrossCA(SEC_PKI_CTX_S *pstContext,
                            SEC_List_S **dpOutCrossCAList);

/**
* @defgroup SEC_PKI_ctxGetDfltLocalCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetDfltLocalCert( SEC_PKI_CTX_S  *pstContext,
*                               X509_CERT_S  **pstCert);
* @endcode
*
* @par Purpose
* This function is used to get the default local cert.
*
* @par Description
* SEC_PKI_ctxGetDfltLocalCert function gets the default local cert associated
* with the context. If the default local cert is not loaded before calling this
* API then the output pstCert contains NULL.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] pstCert Contains the default local cert associated with the
* context. pstCert Contains NULL if default cert is not 
* loaded to Context.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* ipsi will allocate the memory for the pstCert, to free this memory
* application has to call the X509_freeCert.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetDfltLocalCert(SEC_PKI_CTX_S *pstContext,
                               X509_CERT_S  **pstCert);


/**
* @defgroup SEC_PKI_ctxGetAllLocalCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetAllLocalCert( SEC_PKI_CTX_S *pstContext,
*                                SEC_List_S **dpOutCertList);
* @endcode
*
* @par Purpose
* This function is used to get all certificates from local store
* of the passed context.
*
* @par Description
* SEC_PKI_ctxGetAllLocalCert function gets all certificates from local store,
* the default local certificate is also included in the output list.
*
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] dpOutCertList List which contains all the certs.
* dpOutCertList is a list which holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* On success this function will allocate the memory for the dpOutCertList
* (the list may contain one or more entries) to free this memory 
* application has to call SEC_LIST_FREE with the free function as
* X509_freeCert.
*
* @par Note
* \n
* The dpOutCertList contains only the certificates stored in the local store.
* If the multiple local certificates is tailored to be not supported,then it 
* will give a list containing only default certificate.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetAllLocalCert(SEC_PKI_CTX_S *pstContext,
                               SEC_List_S **dpOutCertList);

/**
* @defgroup SEC_PKI_ctxGetPvtKeyByCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetPvtKeyByCert ( SEC_PKI_CTX_S *pstContext,
*                                 X509_CERT_S *pstCert,
*                                 SEC_PKEY_S **pstPvtKey);
* @endcode
*
* @par Purpose
* This function is used to get private key corresponding to the input
* certificate.
*
* @par Description
* SEC_PKI_ctxGetPvtKeyByCert function gets private key corresponding to the 
* input certificate from the local store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstCert Input certificate.[NA/NA]
* @param[out] pstPvtKey Private key associated with the 
* input certificate.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* ipsi will allocate the memory for the pstPvtKey, to free this memory
* application has to call the "CRYPT_PKEY_free".
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetPvtKeyByCert (SEC_PKI_CTX_S *pstContext,
                                X509_CERT_S *pstCert,
                                SEC_PKEY_S **pstPvtKey);


/**
* @defgroup SEC_PKI_ctxRemoveTrustedCA
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxRemoveTrustedCA( SEC_PKI_CTX_S *pstContext,
*                               SEC_NAME_S *pstIssuerName,
*                               SEC_BIGINT_S *pstSerialNum);
* @endcode
*
* @par Purpose
* This function is used to remove the CA certificate from the trusted store.
*
* @par Description
* SEC_PKI_ctxRemoveTrustedCA function removes the CA for which the 
* input issuer name and serial number matches from the trusted store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.
* Issuer name and serial number are unique identifier in RFC.[NA/NA]
* @param[in] pstIssuerName Issuer name of the CA.[NA/NA]
* @param[in] pstSerialNum Serial number of the CA.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxRemoveTrustedCA(SEC_PKI_CTX_S *pstContext,
                               SEC_NAME_S *pstIssuerName,
                               SEC_BIGINT_S *pstSerialNum);

#ifndef __SEC_PKI_NO_MULTIPLE_LOCAL_CERT__

/**
* @defgroup SEC_PKI_ctxRemoveLocalCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxRemoveLocalCert( SEC_PKI_CTX_S *pstContext,
*                               SEC_NAME_S *pstIssuerName,
*                               SEC_BIGINT_S *pstSerialNum);
* @endcode
*
* @par Purpose
* This function is used to remove the local cert and key from the local store.
*
* @par Description
* SEC_PKI_ctxRemoveLocalCert removes the local cert, it removes all the 
* information associated with the local cert like private key and URL
* information. Default local certificate details can also be removed 
* using this API.
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
PSELINKDLL SEC_INT SEC_PKI_ctxRemoveLocalCert(SEC_PKI_CTX_S *pstContext,
                               SEC_NAME_S *pstIssuerName,
                               SEC_BIGINT_S *pstSerialNum);

#endif


/**
* @defgroup SEC_PKI_ctxRemoveCrl
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxRemoveCrl( SEC_PKI_CTX_S *pstContext,
*                               SEC_NAME_S *pstIssuerName,
*                               SEC_BIGINT_S *pstExtnCRLNum);
* @endcode
* @par Purpose
* This function is used to remove the CRL from the store.
*
* @par Description
* SEC_PKI_ctxRemoveCrl function removes the CRL  for which the 
* input issuer name and CRL number matches from the trusted store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstIssuerName Issuer name of the CRL.[NA/NA]
* @param[in] pstExtnCRLNum Extension CRL number of the CRL.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
*	- If the user inputs only Issuer Name then all the matching CRL(S) 
* and Delta CRL(S) will be removed.
*	- If the user inputs both the Issuer Name and the CRL number then all 
* the matching CRL(S) and Delta CRL(S) will be removed.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxRemoveCrl(SEC_PKI_CTX_S *pstContext,
                         SEC_NAME_S *pstIssuerName,
                         SEC_BIGINT_S *pstExtnCRLNum);

/**
* @defgroup SEC_PKI_ctxRemoveCrossCA
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxRemoveCrossCA( SEC_PKI_CTX_S *pstContext,
*                               SEC_NAME_S *pstIssuerName,
*                               SEC_BIGINT_S *pstSerialNum);
* @endcode
*
* @par Purpose
* This function is used to remove the CA certificate from the trusted store.
*
* @par Description
* SEC_PKI_ctxRemoveCrossCA function removes the cross CA for which the 
* input issuer name and serial number matches from the trusted store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.
* Issuer name and serial number are unique identifier in RFC.[NA/NA]
* @param[in] pstIssuerName Issuer name of the CA.[NA/NA]
* @param[in] pstSerialNum Serial Number of the CA.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxRemoveCrossCA(SEC_PKI_CTX_S *pstContext,
                                            SEC_NAME_S *pstIssuerName,
                                            SEC_BIGINT_S *pstSerialNum);

#endif // IPSI_SEC_NO_PKI


/**
* @defgroup SEC_PKI_libraryInit
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_libraryInit(SEC_VOID);
* @endcode
* @par Purpose
* This function is used to initialize the PKI library.
*
* @par Description
* SEC_PKI_libraryInit function initializes the error strings and locks.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT If initialization successful [SEC_PKI_SUCCESS|NA]
* @par Note
* \n
* - This function should be called only in main thread at the starting
* of the application.
* - Resources allocated at the time of SEC_PKI_libraryInit will be released 
* on process exit.
*/
PSELINKDLL SEC_INT SEC_PKI_libraryInit(SEC_VOID);

/**
* @defgroup SEC_PKI_libraryFini
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_VOID SEC_PKI_libraryFini();
* @endcode
* @par Purpose
* This function is deprecated.
*
* @par Description
* This function is deprecated.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval NA This function does not return any value.[NA|NA]
* @par Note
* \n
*  Resources allocated at the time of SEC_PKI_libraryInit will be released 
* on process exit.
*/
PSELINKDLL SEC_VOID SEC_PKI_libraryFini(SEC_VOID);




/**
* @defgroup SEC_PKI_enable_multithread
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_enable_multithread(void);
* @endcode
* @par Purpose
* This function is used to enable the multithreading feature.
*
* @par Description
* SEC_PKI_enable_multithread function is used to enable the multithreading 
* functionality of the library.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
* @par Note
* \n
* This function should be called only in main thread at the starting
* of the application.
*/
PSELINKDLL SEC_INT SEC_PKI_enable_multithread(void);

/**
* @defgroup SEC_PKI_get_error_string
* @ingroup Context_Functions
* @par Prototype
* @code
* const SEC_CHAR* SEC_PKI_get_error_string( SEC_UINT uierrCode)
* @endcode
* 
* @par Purpose
* This function is used to get the error string for a particular error code.
* @par Description
* SEC_PKI_get_error_string function gets the error string for 
* a particular error code.
*
* @param[in] uierrCode Error code. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_CHAR Character pointer to error string. [NA|NA]
*/

#ifdef __SEC_PKI_ERROR_STRING__
PSELINKDLL const SEC_CHAR* SEC_PKI_get_error_string(SEC_UINT uierrCode);
#endif


/**
* @defgroup SEC_PKI_getlast_error
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_UINT SEC_PKI_getlast_error(SEC_VOID)
* @endcode
* 
* @par Purpose
* This function is used to get the last error occurred.
* @par Description
* SEC_PKI_getlast_error function gets the last error occurred.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval SEC_UINT Error code. [NA|NA]
*/
PSELINKDLL SEC_UINT SEC_PKI_getlast_error(SEC_VOID);

/**
* @defgroup SEC_PKI_thread_cleanup
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_VOID SEC_PKI_thread_cleanup();
* @endcode
* 
* @par Purpose
* This function should be called before thread is going to exit.
* @par Description
* SEC_PKI_thread_cleanup function deletes the error stack of the
* current thread.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
*
* 
* @retval SEC_VOID This function does not return any value. [NA|NA]
*/


PSELINKDLL SEC_VOID SEC_PKI_thread_cleanup(SEC_VOID);

#ifndef IPSI_SEC_NO_PKI

/**
* @defgroup SEC_PKI_ctxRemoveDefaultCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxRemoveDefaultCert( SEC_PKI_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This function is used to remove the default certificate from the context.
*
* @par Description
* SEC_PKI_ctxRemoveDefaultCert function removes the default certificate from 
* the context. When certificate is removed the corresponding private key 
* is also removed.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S..[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If the default certificate is not present then also this API will
* return SEC_SUCCESS.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxRemoveDefaultCert(SEC_PKI_CTX_S *pstContext);

#ifndef __SEC_PKI_NO_PRESHARED_PEER_CERT__

/**
* @defgroup SEC_PKI_ctxLoadDfltPreSharedPeerCertFile
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadDfltPreSharedPeerCertFile( SEC_PKI_CTX_S *pstContext,
*                                                    const SEC_CHAR *pcCertFile,
*                                                    SEC_INT iCertFileType,
*                                                    SEC_CHAR *pcCertPasswd,
*                                                    SEC_UINT uCertPwdLen);
* @endcode
*
* @par Purpose
* This function is used to load the default preshared peer certificate in 
* the context.
*
* @par Description
* SEC_PKI_ctxLoadDfltPreSharedPeerCertFile function is used to load
* the default preshared peer certificate in the context.
* Certificate Password is an optional input but, applicable 
* only for PFX format.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S. [NA/NA]
* @param[in] pcCertFile The name of the file from which the certificate has to
* be loaded.[NA/NA]
* @param[in] iCertFileType Certificate file type, mentions the type of the
* to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the password.[0-255/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
*	- A file should not contain more than one end entity certificate.\n
*	- In case of file having multiple certificates, first certificate will be
* considered as end entity certificate.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, MIC_CLEAR mode is not support .
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadDfltPreSharedPeerCertFile(
                                                SEC_PKI_CTX_S *pstContext,
                                                const SEC_CHAR *pcCertFile,
                                                SEC_INT iCertFileType,
                                                const SEC_CHAR *pcCertPasswd,
                                                SEC_UINT uCertPwdLen);


/**
* @defgroup SEC_PKI_ctxLoadDfltPreSharedPeerCertBuffer
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadDfltPreSharedPeerCertBuffer( SEC_PKI_CTX_S *pstContext,
*                                            const SEC_CHAR *pcCertBuffer,
*                                            SEC_UINT uCertBufLen, 
*                                            SEC_INT iCertFileType,
*                                            SEC_CHAR *pcCertPasswd,
*                                            SEC_UINT uCertPwdLen);
* @endcode
*
* @par Purpose
* This function is used to load the default preshared peer certificate in 
* the context.
*
* @par Description
* SEC_PKI_ctxLoadDfltPreSharedPeerCertBuffer function is used to load
* the default preshared peer certificate in the context.
* Certificate Password is an optional input but, applicable 
* only for PFX format.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCertBuffer The buffer that contains the certificate.[NA/NA]
* @param[in] uCertBufLen Length of the certificate buffer.[NA/NA]
* @param[in] iCertFileType certificate file type, mentions the type of the
* to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd password for the Certificate buffer.[NA/NA]
* @param[in] uCertPwdLen Length of the password.[0-255/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
*	- A buffer should not contain more than one end entity certificate.\n
*	- In case of buffer length, validation is done only for the value of zero.
*  (Value zero is considered to be invalid). If any value other than the actual
*  buffer length, API behaviour is undefined.
*	- In case of buffer having multiple certificates, first certificate will be
* considered as end entity certificate.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, MIC_CLEAR mode is not supported .
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadDfltPreSharedPeerCertBuffer(
                                                 SEC_PKI_CTX_S *pstContext,
                                                 const SEC_CHAR *pcCertBuffer,
                                                 SEC_UINT uCertBufLen, 
                                                 SEC_INT iCertFileType,
                                                 const SEC_CHAR *pcCertPasswd,
                                                 SEC_UINT uCertPwdLen);

/**
* @defgroup SEC_PKI_ctxLoadPreSharedPeerCertFile
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadPreSharedPeerCertFile( SEC_PKI_CTX_S *pstContext,
*                                          const SEC_CHAR *pcCertFile,
*                                          SEC_INT iCertFieType,
*                                          const SEC_CHAR *pcCertPasswd,
*                                          const SEC_UINT uCertPwdLen);
* @endcode
*
* @par Purpose
* Load the Peer Certificate(s) from the file to the peer cert list of the PKI 
* Context. 
* 
* @par Description
* SEC_PKI_ctxLoadPreSharedPeerCertFile function reads a certificate(s) file
* that contains the certificate(s) in "PEM","PFX", or "DER" format and adds the 
* certificate to the preshared peer certificate list of the context. 
* Certificate Password is an optional input but, applicable 
* only for PFX format.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCertFile The name of the file from which the certificate has to
* be loaded.[NA/NA]
* @param[in] iCertFileType certificate file type, mentions the type of the
* to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd Password for the certificate file.[NA/NA]
* @param[in] uCertPwdLen Length of the password.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
*	- A file can contain more than one end entity certificate.\n
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, MIC_CLEAR mode is not supported .
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadPreSharedPeerCertFile (
                                          SEC_PKI_CTX_S *pstContext,
                                          const SEC_CHAR *pcCertFile,
                                          SEC_INT iCertFileType,
                                          const SEC_CHAR *pcCertPasswd,
                                          const SEC_UINT uCertPwdLen);

/**
* @defgroup SEC_PKI_ctxLoadPreSharedPeerCertBuffer
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxLoadPreSharedPeerCertBuffer ( SEC_PKI_CTX_S *pstContext,
*                                             const SEC_CHAR *pcCertBuffer,
*                                             SEC_UINT uCertBufLen, 
*                                             SEC_INT iCertFieType,
*                                             const SEC_CHAR *pcCertPasswd,
*                                             const SEC_UINT uCertPwdLen);
* @endcode
*
* @par Purpose
* Load the Peer Certificate(s) from the buffer to the peer cert list of the PKI
* context.
*
* @par Description
* SEC_PKI_ctxLoadPreSharedPeerCertBuffer function reads a certificate(s) buffer 
* That contains the certificate(s) in "PEM","PFX" or "DER" format and Adds the 
* Certificate to the preshared peer cert list of the context. For Certificate 
* Password is an optional input but password is applicable only for PFX format. 
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pcCertBuffer The buffer that contains the certificate.[NA/NA]
* @param[in] uCertBufLen Length of the certificate buffer.[NA/NA]
* @param[in] iCertFileType certificate file type, mentions the type of the
* to be loaded.
* [SEC_PKI_FILETYPE_PFX/SEC_PKI_FILETYPE_PEM/SEC_PKI_FILETYPE_ASN1/NA]
* @param[in] pcCertPasswd password for the Certificate buffer.[NA/NA]
* @param[in] uCertPwdLen Length of the Password.[0-255/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
*	- A buffer can contain more than one end entity certificate.\n
*	- In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). Any value other than the actual
* buffer length, API behaviour is undefined.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
*	- For the PEM file type, MIC_CLEAR mode not support .
*/
PSELINKDLL SEC_INT SEC_PKI_ctxLoadPreSharedPeerCertBuffer (
                                            SEC_PKI_CTX_S *pstContext,
                                            const SEC_CHAR *pcCertBuffer,
                                            SEC_UINT uCertBufLen,
                                            SEC_INT iCertFileType,
                                            const SEC_CHAR *pcCertPasswd,
                                            const SEC_UINT uCertPwdLen);

/**
* @defgroup SEC_PKI_ctxGetDfltPreSharedPeerCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetDfltPreSharedPeerCert( SEC_PKI_CTX_S *pstContext,
*                                           X509_CERT_S **pstCert);
* @endcode
*
* @par Purpose
* This function is used to get the default preshared peer certificate from 
* the context.
*
* @par Description
* SEC_PKI_ctxGetDfltPreSharedPeerCert function is used to get
* the default preshared peer certificate from the context.
* If the default preshared peer cert is not loaded before calling this
* API then the output pstCert contains NULL.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA|NA]
* @param[out] pstCert Default Certificate.[NA|NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* ipsi will allocate the memory for the pstCert, to free this memory 
* application has to call the X509_freeCert.
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetDfltPreSharedPeerCert(
                                               SEC_PKI_CTX_S *pstContext,
                                               X509_CERT_S **pstCert);

#endif

/**
* @defgroup SEC_PKI_ctxGetURLByCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetURLByCert( SEC_PKI_CTX_S *pstContext,
*                                 X509_CERT_S *pstCert,
*                                 SEC_PKI_DATA_BUF_S **pstURL);
* @endcode
*
* @par Purpose
* This function is used to get URL corresponding to the input
* certificate from the local store.
*
* @par Description
* SEC_PKI_ctxGetURLByCert function gets URL corresponding to the 
* input certificate.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstCert Input certificate.[NA/NA]
* @param[out] pstURL URL associated with the 
* input certificate.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* ipsi will allocate the memory for the "pstURL". To free this memory
* application has to call the SEC_PKI_freeDataBuf.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetURLByCert (SEC_PKI_CTX_S *pstContext,
                                X509_CERT_S *pstCert,
                                SEC_PKI_DATA_BUF_S **pstURL);

#ifndef __SEC_PKI_NO_PEER_CACHE__

/**
* @defgroup SEC_PKI_ctxGetAllPeerCerts
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_List_S * SEC_PKI_ctxGetAllPeerCerts( SEC_PKI_CTX_S *pstContext,
*                                         SEC_List_S **dpOutCertList);
* @endcode
*
* @par Purpose
* This function is used to get all peer certificate in context.
*
* @par Description
* SEC_PKI_ctxGetAllPeerCerts gets all peer certificate from the peer cache 
* in context. 
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] dpOutCertList List which contains all the certs.
* dpOutCertList is a list which holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
*  ipsi will allocate the memory for the dpOutCertList 
*  (the list may contain one or more entries), to free this memory 
*  application has to call the SEC_LIST_FREE, with the 
*  free function as X509_freeCert.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetAllPeerCerts(SEC_PKI_CTX_S *pstContext,
                                      SEC_List_S **dpOutCertList);
#endif

#ifndef __SEC_PKI_NO_PRESHARED_PEER_CERT__

/**
* @defgroup SEC_PKI_ctxGetAllPreSharedPeerCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetAllPreSharedPeerCert( SEC_PKI_CTX_S *pstContext,
                                             SEC_List_S **dpOutCertList)
* @endcode
*
* @par Purpose
* This function is used to get all certificates from the preShared 
* peer store of the passed context.
*
* @par Description
* SEC_PKI_ctxGetAllPreSharedPeerCert function is used to get all certificates
* from the preShared peer store of the passed context.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] dpOutCertList List which contains all the certs.
* dpOutCertList is a list which holds elements of type X509_CERT_S.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* On success this function will allocate the memory for the dpOutCertList
* (the list may contain one or more entries). To free this memory 
* application has to call SEC_LIST_FREE with the free function as
* X509_freeCert.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetAllPreSharedPeerCert(
    SEC_PKI_CTX_S *pstContext,SEC_List_S **dpOutCertList);

/**
* @defgroup SEC_PKI_ctxRemovePreSharedPeerCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxRemovePreSharedPeerCert( SEC_PKI_CTX_S *pstContext,
                                             SEC_NAME_S *pstIssuerName,
                                             SEC_BIGINT_S *pstSerialNum);
* @endcode
*
* @par Purpose
* This function is used to remove desired certificate from the preShared 
* peer store of the passed context.
*
* @par Description 
* SEC_PKI_ctxRemovePreSharedPeerCert function removes the pre shared peer
* certificate for which the input issuer name and serial number matches 
* from the pre shared peer store.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstIssuerName Issuer name of the certificate.[NA/NA]
* @param[in] pstSerialNum Serial number of the certificate.[NA/NA]
*
* @param[out] NA NA [NA|NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
*/
PSELINKDLL 
SEC_INT SEC_PKI_ctxRemovePreSharedPeerCert(SEC_PKI_CTX_S *pstContext,
                                            SEC_NAME_S *pstIssuerName,
                                            SEC_BIGINT_S *pstSerialNum);

/**
* @defgroup SEC_PKI_ctxRemoveDfltPreSharedPeerCert
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxRemoveDfltPreSharedPeerCert( SEC_PKI_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This function is used to remove the default preshared peer 
* certificate from the context.
*
* @par Description
* SEC_PKI_ctxRemoveDfltPreSharedPeerCert function removes the default preshared 
* peer certificate from the context.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions[SEC_PKI_ERROR|NA]
*
* @par Note
* \n
* If the default preshared peer certificate is not present then also this API 
* will return SEC_SUCCESS.
*
*/
PSELINKDLL SEC_INT SEC_PKI_ctxRemoveDfltPreSharedPeerCert(SEC_PKI_CTX_S 
                                                          *pstContext);


/**
* @defgroup SEC_PKI_free_multithread
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_VOID SEC_PKI_free_multithread(SEC_VOID);
* @endcode
* @par Purpose
* This function is used to free the multithreading feature.
*
* @par Description
* SEC_PKI_free_multithread function is used to free the multithreading 
* functionality of the library.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval NA
* @par Note
* \n
* This function should be called only in main thread at the end
* of the application.
*/
PSELINKDLL SEC_VOID SEC_PKI_free_multithread(SEC_VOID);

/**
* @defgroup SEC_PKI_ctxGetBaseCRLbyCert
* @ingroup Context_Functions
* @par Prototype
* @code
* X509_CRL_S* SEC_PKI_ctxGetBaseCRLbyCert(
*                                        SEC_PKI_CTX_S *pstContext,
*                                       X509_CERT_S *pstCert);
* @endcode
*
* @par Purpose
* This function is used for getting the base crl for the certificate 
* from the context.
*
* @par Description
* SEC_PKI_ctxGetBaseCRLbyCert function gets the 
* base crl for the certificate from the context.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstCert Pointer to X509_CERT_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval X509_CRL_S* On successful execution. [NA|NA]
* @retval NULL On all failure conditions[NULL|NA]
*
* @par Note
* \n
*	- If user loads more than one base crl in the context, then this API
* will return the appropriate base crl suitable for the certificate passed.
*
*	- Finding of the appropriate CRL based on the following checks:
* Time, AKID, IDP Reasons, Direct/Indirect CRL, and Criticality extensions.
*/
PSELINKDLL X509_CRL_S* SEC_PKI_ctxGetBaseCRLbyCert(
                                        SEC_PKI_CTX_S *pstContext,
                                        X509_CERT_S *pstCert);



/**
* @defgroup SEC_PKI_ctxGetDeltaCRLbyCert
* @ingroup Context_Functions
* @par Prototype
* @code
* X509_CRL_S* SEC_PKI_ctxGetDeltaCRLbyCert(
*                                        SEC_PKI_CTX_S *pstContext,
*                                        X509_CERT_S *pstCert);
* @endcode
*
* @par Purpose
* This function is used for getting the delta crl for the certificate 
* from the context.
*
* @par Description
* SEC_PKI_ctxGetDeltaCRLbyCert function gets the 
* delta crl for the certificate from the context.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] pstCert Pointer to X509_CERT_S.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval X509_CRL_S* On successful execution. [NA|NA]
* @retval NULL On all failure conditions[NULL|NA]
*
* @par Note
* \n
*	- If user loads more than one base crl and more than one delta crl
* for the corresponding base crls in the context, then this API
* will return the appropriate delta crl corresponding to the appropriate 
* base crl for the certificate passed.
*
*	- Finding of the appropriate CRL  based on the following checks :  
* Time , AKID, IDP Reasons, Direct/Indirect CRL, Criticality extensions.
*
*/
PSELINKDLL X509_CRL_S* SEC_PKI_ctxGetDeltaCRLbyCert(
                                        SEC_PKI_CTX_S *pstContext,
                                        X509_CERT_S *pstCert);





/**
* @defgroup SEC_PKI_ctxSetOptions
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxSetOptions
* ( 
*      SEC_PKI_CTX_S *pstContext,
*      SEC_UINT uiOptions
* );
* @endcode
*
* @par Purpose
* This function is used to set the PKI options for the context.
*
* @par Description
* SEC_PKI_ctxSetOptions function is used to set the PKI options for the context.
* Each new option will be ORed with the existing option.The option flags should 
* be of type SEC_PKI_OPTIONS_E. By passing zero, the options in the context
* can be reset.
*
* @param[in,out] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[in] uiOptions PKI option flags to be set. <b> Default value is 0. </b>
* [0-Maximum.of.SEC_UINT]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Dependency
* sec_pki_def.h  \n
* sec_pki_context.h
*
* @attribute Yes No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* SEC_PKI_ctxGetOptions
*/
PSELINKDLL SEC_INT SEC_PKI_ctxSetOptions(SEC_PKI_CTX_S *pstContext,
                       SEC_UINT uiOptions);


/**
* @defgroup SEC_PKI_ctxGetOptions
* @ingroup Context_Functions
* @par Prototype
* @code
* SEC_INT SEC_PKI_ctxGetOptions
* ( 
*      SEC_PKI_CTX_S *pstContext,
*      SEC_UINT *puiOptions
* );
* @endcode
*
* @par Purpose
* This function is used to get the PKI option flags from the context.
*
* @par Description
* SEC_PKI_ctxGetOptions is used to get the PKI option flags associated 
* with the context.It will give the ORed value of the PKI option flags
* that are set in the context. If no option is set, zero is returned.
*
* @param[in] pstContext Pointer to SEC_PKI_CTX_S.[NA/NA]
* @param[out] puiOptions Contains the option flags. <b> Default value is 0. </b>
* [0-Maximum.of.SEC_UINT]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @par Memory Handling
* \n
* Application should pass the address of an unsigned integer variable.
*
* @par Dependency
* sec_pki_def.h  \n
* sec_pki_context.h
*
* @attribute Yes No
*
* @par Note
*
* None
*
* @par Example
* None
*
* @par Related Topics
* SEC_PKI_ctxSetOptions
*/
PSELINKDLL SEC_INT SEC_PKI_ctxGetOptions(SEC_PKI_CTX_S *pstContext,
                       SEC_UINT *puiOptions);




#endif // IPSI_SEC_NO_PKI

#endif
#ifdef  __cplusplus
}
#endif

#endif /*__SEC_PKI_CONTEXT_H__*/



