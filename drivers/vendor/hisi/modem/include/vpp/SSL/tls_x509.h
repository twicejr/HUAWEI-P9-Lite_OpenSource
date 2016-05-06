/* crypto/x509/x509_vfy.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */


#include "ipsi_ssl_build_conf.h"

#ifndef _IPSI_TLS_X509_H_
#define _IPSI_TLS_X509_H_


#include "sec_sys.h" 
#include "sec_crypto.h"
#include "asn-types.h"
#include "sec_list.h"
#include "sec_error.h"
#include "x509_basictypes.h"
#include "tls_x509verify.h"

#ifdef  __cplusplus
extern "C"{
#endif


/* Flag to indicate PEM format*/
#define X509_FILETYPE_PEM               1

/* Flag to indicate ASN format*/
#define X509_FILETYPE_ASN1              2

/* Flag to indicate Default format*/
#define X509_FILETYPE_DEFAULT           3

/* Flag to indicate PFX format*/
#define X509_FILETYPE_PFX               4


/* The application is not happy */
#define     X509_V_ERR_APPLICATION_VERIFICATION     50

/* Certificate verify flags */

/* Send issuer+subject checks to verify_cb */
#define X509_V_FLAG_CB_ISSUER_CHECK     0x1
/* Use check time instead of current time */
#define X509_V_FLAG_USE_CHECK_TIME      0x2
/* Lookup CRLs */
#define X509_V_FLAG_CRL_CHECK           0x4
/* Lookup CRLs for whole chain */
#define X509_V_FLAG_CRL_CHECK_ALL       0x8
/* Ignore unhandled critical extensions */
#define X509_V_FLAG_IGNORE_CRITICAL     0x10
/* Disable workarounds for broken certificates */
#define X509_V_FLAG_X509_STRICT         0x20
/* Enable proxy certificate validation */
#define X509_V_FLAG_ALLOW_PROXY_CERTS       0x40

/* Cross CA check */
#define X509_V_FLAG_CHECK_CROSS_CA    0x80

/* Cross CA CRL check */
#define X509_V_FLAG_CRL_CROSS_CA    0x100

/* Extended CRL features such as indirect CRLs, alternate CRL signing keys */
#define IPSI_X509_V_FLAG_EXTENDED_CRL_SUPPORT	0x1000
/* Delta CRL support */
#define IPSI_X509_V_FLAG_USE_DELTAS			0x2000

/* Ceftificate Key Usage extension verify falgs */

/* Mandatory Check CA Key Usage */
#define X509_VK_FLAG_CA_KEYUSAGE_MANDATORY_CHECK        0x1

/* Check Key Usage */
#define X509_VK_FLAG_KEYUSAGE_CHECK       0X2


#define X509_VP_FLAG_DEFAULT            0x1
#define X509_VP_FLAG_OVERWRITE          0x2
#define X509_VP_FLAG_RESET_FLAGS        0x4
#define X509_VP_FLAG_LOCKED         0x8
#define X509_VP_FLAG_ONCE           0x10


/* To set the application specific certificate chain verify function */
#define X509_STORE_SET_VERIFY_CB_FUNC(ctx,func) ((ctx)->pfVerify_cb=(func))

/* To set the certificate chain verify fucntion */
#define X509_STORE_SET_VERIFY_FUNC(ctx,func)    ((ctx)->pfVerify=(func))

/*  Gets the length of the signature in the certificate. Extended certificate has to 
    be passed to this macro*/
#define X509_GET_SIGNATURE_BITLEN(x) ((((x)->pstCert)->signature).bitLen)

/** @defgroup tls_x509
* This section contains the Functions of tls_x509.
*/

/** @defgroup tls_x509Functions
* @ingroup tls_x509
* This section contains the Functions of tls_x509.
*/


/*
    Func Name: X509_dupCertExtnd                                              
*/

/**
* @defgroup X509_dupCertExtnd
* @ingroup tls_x509Functions
* @par Prototype
* @code
* X509_CERT_EXTENDED_S* X509_dupCertExtnd(X509_CERT_EXTENDED_S* pstSrc);
* @endcode
* 
* @par Purpose
* This is used to create duplicate of Extended Certificate.
* 
* @par Description
* X509_dupCertExtnd function duplicates an Extended Certificate structure. The fields inside the source
* extended certificate is copied to a newly created extended certificate. Certificate
* field has to be present in the source certificate passed to this function. The reference
* count will be set to one.
* 
* @param[in] pstSrc The source certificate that has to be duplicated. [N/A]
* 
* @retval X509_CERT_EXTENDED_S* On successful execution, pointer to the X509_CERT_EXTENDED_S
* structure is returned. [Pointer to X509_CERT_EXTENDED_S|N/A]
* @retval X509_CERT_EXTENDED_S* On failure conditions, SEC_NULL is returned. The failure conditions can
* be one of the following:\n
* 1. Input parameters are NULL.\n
* 2. Memory allocation fails.\n [SEC_NULL|N/A]
*
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_createCertExtnd,\n
* X509_freeCertExtended.
*/

SSLLINKDLL X509_CERT_EXTENDED_S* X509_dupCertExtnd(X509_CERT_EXTENDED_S* pstSrc);

/*
    Func Name: X509_freeCertExtended                                          
*/

/**
* @defgroup X509_freeCertExtended
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeCertExtended(X509_CERT_EXTENDED_S* pstCertExtn);
* @endcode
* 
* @par Purpose
* This is used to free the extended certificate.
* 
* @par Description
* X509_freeCertExtended function frees the extended certificate structure.  
* 
* @param[in] pstCertExtn The certificate to be freed. [N/A]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_createCertExtnd,\n
* X509_dupCertExtnd.
*/

SSLLINKDLL SEC_VOID X509_freeCertExtended(X509_CERT_EXTENDED_S* pstCertExtn);

/*
    Func Name: X509_getPubKeyExtnd
*/

/**
* @defgroup X509_getPubKeyExtnd
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_PKEY_S* X509_getPubKeyExtnd(X509_CERT_EXTENDED_S* pstCertExtn);
* @endcode
* 
* @par Purpose
* This is used to get public key in Extended Certificate.
* 
* @par Description
* X509_getPubKeyExtnd function returns the public key in the certificate and increments the reference count by 1.
* And hence has to be freed by the calling function in order to restore the reference count by calling
* CRYPT_PKEY_free.
* 
* @param[in] pstCertExtn The certificate from which the public key has to be extracted. [N/A]
* 
* @retval SEC_PKEY_S* On successful execution, pointer to the SEC_PKEY_S structure is returned.
* [Pointer to SEC_PKEY_S|N/A]
* @retval SEC_PKEY_S* On failure conditions, SEC_NULL is returned. The failure conditions can be one of the
* following:\n
* 1. Input parameters is NULL.\n
* 2. Decoding of the public key fails. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_certPubKeyTypeExtnd,\n
* X509_getSignatureTypeExtnd,\n
* X509_getPubKeyParamExtnd.
*/

SSLLINKDLL SEC_PKEY_S* X509_getPubKeyExtnd(X509_CERT_EXTENDED_S* pstCertExtn);

/*
    Func Name: X509_certPubKeyTypeExtnd                                       
*/

/**
* @defgroup X509_certPubKeyTypeExtnd
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_ALGID_E X509_certPubKeyTypeExtnd (X509_CERT_EXTENDED_S* pstCertExtn);
* @endcode
* 
* @par Purpose
* This is used to get public key type.
* 
* @par Description
* X509_certPubKeyTypeExtnd function returns the public key type from the extended certificate passed.
* 
* @param[in] pstCertExtn The certificate from which the public key generation algorithm type is returned. [N/A]
* 
* @retval SEC_ALGID_E On successful execution. [CID_RSA|N/A]
* @retval SEC_ALGID_E On successful execution. [CID_DSA|N/A]
* @retval SEC_ALGID_E On successful execution. [CID_ECDSA|N/A]
* @retval SEC_ALGID_E On all failure conditions, ALGID_UNKNOWN is returned.
* The failure conditions can be one of the following:\n
* 1. Input parameters is NULL.\n
* 2. Decoding of the public key fails. [ALGID_UNKNOWN|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_getPubKeyExtnd,\n
* X509_getSignatureTypeExtnd,\n
* X509_getPubKeyParamExtnd.
*/

SSLLINKDLL SEC_ALGID_E X509_certPubKeyTypeExtnd (X509_CERT_EXTENDED_S* pstCertExtn);


/*
    Func Name: X509_getSignatureTypeExtnd                                     
*/

/**
* @defgroup X509_getSignatureTypeExtnd
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_ALGID_E X509_getSignatureTypeExtnd (X509_CERT_EXTENDED_S* pstCertExtn);
* @endcode
* 
* @par Purpose
* This is used to get algorithm ID that signs the certificate.
* 
* @par Description
* X509_getSignatureTypeExtnd function gets the algorithm ID that is is used to sign the extended certificate.
* 
* @param[in] pstCertExtn The Extended certificate from which the signature algorithm is returned. [N/A]
* 
* @retval SEC_ALGID_E On successful execution, the signature algorithm identifier is returned.
* [The return value can be one of the following:\n
* CID_MD5WITHRSA\n
* CID_SHA1WITHRSA\n
* CID_SHA1WITHRSAOLD\n
* CID_DSAWITHSHA1\n
* CID_DSAWITHSHA1_2\n
* CID_SHA256WITHRSAENCRYPTION\n
* CID_SHA384WITHRSAENCRYPTION\n
* CID_SHA512WITHRSAENCRYPTION|N/A]
* @retval SEC_ALGID_E On all failure conditions ALGID_UNKNOWN is returned. The failure conditions
* can be one of the following:\n
* 1. Input parameters is NULL.\n
* 2. When the signature algorithm used cannot be identified. [ALGID_UNKNOWN|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_getPubKeyExtnd,\n
* X509_certPubKeyTypeExtnd,\n
* X509_getPubKeyParamExtnd.
*/

SSLLINKDLL SEC_ALGID_E X509_getSignatureTypeExtnd (X509_CERT_EXTENDED_S* pstCertExtn);

/*
    Func Name: X509_getPubKeyParamExtnd                                       
*/

/**
* @defgroup X509_getPubKeyParamExtnd
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_getPubKeyParamExtnd(SEC_List_S* pCertList, SEC_PKEY_S* pstPubKey);
* @endcode
* 
* @par Purpose
* This is used to copy public key parameters from certificate list to the public key.
* 
* @par Description
* X509_getPubKeyParamExtnd function gets the public key parameters from the certificate list. Before calling this
* function the public key has to be extracted using X509_extractPublicKey API. If the public key already contains
* parameters in it then SEC_SUCCESS is returned. Else the function decodes the public key from each certificate in the
* list and then copies the parameters to the public key passed as parameter to the API if the public key type is
* matching. The public key value should not be NULL, so use X509_extractPublicKey before calling this function.
* 
* @param[in] pCertList The certificate list from which the public key parameters have to be extracted. [N/A]
* @param[in] pstPubKey The public key to which the parameters will be copied into. [N/A]
* 
* @retval SEC_UINT32 On successful execution the SEC_SUCCESS is returned. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input parameters are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If algorithm does not have params. [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 If parameters are missing. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If keys are of a different type. [SEC_ERR_KEYPAIR_MISMATCH|N/A]
* @retval SEC_UINT32 If key is corrupted. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_getPubKeyExtnd,\n
* X509_certPubKeyTypeExtnd,\n
*/

SSLLINKDLL SEC_UINT32 X509_getPubKeyParamExtnd(SEC_List_S* pCertList,
                                    SEC_PKEY_S* pstPubKey);

/*
    Func Name: X509_createCertExtnd
*/

/**
* @defgroup X509_createCertExtnd
* @ingroup tls_x509Functions
* @par Prototype
* @code
* X509_CERT_EXTENDED_S* X509_createCertExtnd(X509_CERT_S* pstCert);
* @endcode
* 
* @par Purpose
* This is used to create an extended certificate from certificate passed.
* 
* @par Description
* X509_createCertExtnd function creates an extended certificate, given a certificate. The certificate passed is
* duplicated and stored in the extended certificate and the reference count is set to one.
* 
* @param[in] pstCert The certificate that has to be set in the extended certificate. [N/A]
* 
* @retval X509_CERT_EXTENDED_S* On successful execution, pointer to extended certificate is returned.
* [Pointer to X509_EXTENDED_S|N/A]
* @retval X509_CERT_EXTENDED_S* On all failure conditions SEC_NULL is returned. The failure conditions can be one
* of the following:\n
* 1. Input parameters is NULL.\n
* 2. Duplication of the certificate fails.\n
* 3. Memory allocation fails. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* This function is different from x509_createCertExtnd. Here a certificate is passed.
*
* @par Related Topics
* X509_dupCertExtnd,\n
* X509_freeCertExtended,\n
*/

SSLLINKDLL X509_CERT_EXTENDED_S* X509_createCertExtnd(X509_CERT_S* pstCert);

/*
    Func Name: X509_storeNew                                                   
*/

/**
* @defgroup X509_storeNew
* @ingroup tls_x509Functions
* @par Prototype
* @code
* X509_STORE_S* X509_storeNew(SEC_VOID );
* @endcode
* 
* @par Purpose
* This is use to create X509_STORE_S structure.
* 
* @par Description
* X509_storeNew function creates a new X509_STORE_S structure.
*
* @par Parameters
* N/A
*
* @retval X509_STORE_S* The pointer to X509_Store structure is returned. [Pointer to X509_STORE_S|N/A]
* @retval X509_STORE_S* If memory allocation fails. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_storeFree,\n
* X509_storeSetFlags,\n
* X509_storeSetTime,\n
* X509_storeAddCert,\n
* X509_storeAddCRL,\n
* SSL_ctxGetCertStore,\n
* SSL_ctxSetCertStore.
*/

SSLLINKDLL X509_STORE_S* X509_storeNew(SEC_VOID );

/*
    Func Name: X509_storeFree                                                 
*/

/**
* @defgroup X509_storeFree
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_VOID X509_storeFree(X509_STORE_S *pstStore);
* @endcode
* 
* @par Purpose
* This is used to free the X509_STORE_S structure.
* 
* @par Description
* X509_storeFree function frees the X509_STORE_S structure create using X509_storeNew.
* 
* @param[in] pstStore The X509_STORE_S structure that has to be freed. [N/A]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_storeNew,\n
* X509_storeSetFlags,\n
* X509_storeSetTime,\n
* X509_storeAddCert,\n
* X509_storeAddCRL,\n
* SSL_ctxGetCertStore,\n
* SSL_ctxSetCertStore.
*/

SSLLINKDLL SEC_VOID X509_storeFree(X509_STORE_S *pstStore);

/*
    Func Name: X509_storeSetFlags                                      
*/

/**
* @defgroup X509_storeSetFlags
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_INT X509_storeSetFlags(X509_STORE_S *pstStore, SEC_UINT32 uiFlags);
* @endcode
* 
* @par Purpose
* This is used to set the certificate verification flag.
* 
* @par Description
* X509_storeSetFlags function sets the certificate verification flag in pstParam field of X509_STORE_S structure. Each
* new flag passed is ORed with existing flag. The final flag value is used for certificate verification and/or CRL
* validation. Example: pass X509_V_FLAG_ALLOW_PROXY_CERTS flag to enable proxy certificate validation.
* Also refer to Certificate verification flags in tls_x509.h for more flags.
*
* @param[in] uiFlags The flags that has to be set. [N/A]
* @param[in] pstStore The X509_STORE_S structure that has to be set with flags. [N/A]
* 
* @retval SEC_INT On Success. [TLS_SUCCESS|N/A]
* @retval SEC_INT On Failure. The failure conditions can happen when X509_store passed is NULL.[SEC_NULL|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_storeNew,\n
* X509_storeSetTime,\n
* X509_storeAddCert,\n
* X509_storeAddCRL,\n
* SSL_ctxGetCertStore,\n
* SSL_ctxSetCertStore.
*/

SSLLINKDLL SEC_INT X509_storeSetFlags(X509_STORE_S *pstStore, 
                           SEC_UINT32 uiFlags);

/**
* @defgroup X509_storeClearFlags
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_VOID X509_storeClearFlags(X509_STORE_S *pstStore, 
*                           SEC_UINT32 uiFlags);
* @endcode
* 
*@ par Purpose
* This is used to reset the certificate verification flag.
* 
* @par Description
* The function is used to reset the certificate verification flag in Param field of
* X509_STORE_S. Each new flag passed is reset within existing overall flag. 
* The final flag value is used for certificate verfification and/or CRL validation.
* Example: pass X509_V_FLAG_ALLOW_PROXY_CERTS flag to enable proxy
* certificate validation. Also refer to Certificate verification flags in tls_x509.h 
* for more flags.
*
* @param[in] param pstStore The X509_STORE_S structure that has to be 
* reset with flags. [N/A]
* @param[in] uiFlags The flags that has to be reset. [N/A]
*
* @retval SEC_INT On Success. [1|N/A]
* @retval SEC_INT On Failure conditions [SEC_NULL|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* par Note
* The input "uiFlags" is not validated only pstStore is validated for NULL.
* While clearing the specified flags it will not check whether it exists or not.
*
* @par Related Topics
* X509_storeNew,\n
* X509_storeSetTime,\n
* X509_storeAddCert,\n
* X509_storeAddCRL,\n
* SSL_ctxGetCertStore,\n
* SSL_ctxSetCertStore,\n
* X509_storeSetFlags.
* 
*/

SSLLINKDLL SEC_INT X509_storeClearFlags(X509_STORE_S *pstStore, 
                           SEC_UINT32 uiFlags);

/*
    Func Name: X509_storeSetTime
*/

/**
* @defgroup X509_storeSetTime
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_VOID X509_storeSetTime(X509_STORE_S *pstStore,
* DATETIME_S stTime);
* @endcode
* 
* @par Purpose
* This is used to set and enable check time, for certificate validity period.
* 
* @par Description
* X509_storeSetTim function sets date and time to the pstParam field in X509_STORE_S structure and also
* X509_V_FLAG_USE_CHECK_TIME(Use check time instead of current time) is set in certificate verification flag in pstParam
* field. The time is used for checking the certificate validity period.
* 
* @param[in] pstStore The X509_STORE_S structure that has to be set with date and time. [N/A]
* @param[in] stTime  The time that has to be set in pstStore. [N/A]
* 
* @retval SEC_VOID No value is returned[N/A|N/A].
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* X509_storeNew,\n
* X509_storeSetFlags,\n
* X509_storeSetFlags,\n
* X509_storeAddCert,\n
* X509_storeAddCRL,\n
* SSL_ctxGetCertStore,\n
* SSL_ctxSetCertStore.
*/

SSLLINKDLL SEC_VOID X509_storeSetTime(X509_STORE_S *pstStore, 
                           DATETIME_S stTime);

/*
    Func Name: X509_storeAddCert                                            
*/

/**
* @defgroup X509_storeAddCert
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_INT X509_storeAddCert(X509_STORE_S *pstStore,
* X509_CERT_EXTENDED_S *pstCertExtnd);
* @endcode
* 
* @par Purpose
* This is used to add an extended certificate to the X509_STORE_S.
* 
* @par Description
* X509_storeAddCert function adds an extended certificate to X509_STORE_S structure. The certificate is
* added to the list of X509_OBJECT_S in X509_STORE_S, if it does not already exist in the list.
* 
* @param[in] pstCertExtnd The certificate that has to be stored. [N/A]
* @param[in] pstStore The X509_STORE_S structure to which the certificate has to be added. [N/A]
* 
* @retval SEC_INT When extended certificate is added to the pstObjects field of X509_STORE_S structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT The certificate is being loaded again. [SEC_ERROR|N/A]
* @retval SEC_INT On Failure. The failure conditions can be one of the following:\n
* 1. Input parameters are NULL.\n
* 2. Duplication of the extended certificate fails.\n
* 3. Memory allocation fails.[SEC_NULL|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* The extended certificate is duplicated inside this function. And hence, memory allocation happens.
*
* @par Related Topics
* X509_storeNew,\n
* X509_storeSetFlags,\n
* X509_storeSetTime,\n
* SSL_ctxGetCertStore,\n
* SSL_ctxSetCertStore. 
*/

SSLLINKDLL SEC_INT X509_storeAddCert(X509_STORE_S *pstStore, 
                          X509_CERT_EXTENDED_S *pstCertExtnd);

/*
    Func Name: X509_storeAddCRL                                         
*/

/**
* @defgroup X509_storeAddCRL
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_INT X509_storeAddCRL(X509_STORE_S *pstStore,
*                          X509_CRL_S *pstCRL);
* @endcode
* 
* @par Purpose
* This is used to add CRL to X509_STORE_S.
* 
* @par Description
* X509_storeAddCRL function adds a CRL to X509_STORE_S structure. The CRL is added to the list 
* of X509_OBJECT_S if it does not already exist in the list. A Updated CRL also can be loaded.
* 
* @param[in] pstCRL The CRL that has to be stored. [N/A]
* @param[in] pstStore The X509_STORE_S structure to which the certificate has to be added. [N/A]
* 
* @retval SEC_INT When CRL is added to the pstObjects field of X509_STORE_S structure. [TLS_SUCCESS|N/A]
* @retval SEC_INT If parameter passed are NULL [SEC_NULL|N/A]
* @retval SEC_INT In case of malloc failures or internal error [SEC_ERROR|N/A]
* @retval SEC_INT If the CRL already exists.  [STORE_ADD_SAME_CRL_ALREADY|N/A]
* @retval SEC_INT If the newer CRL already exists.  [STORE_ADD_SSL_NEWER_CRL_EXIST|N/A]
* @retval SEC_INT If the Date comparison failed. [STORE_ADD_SSL_DATE_CMP_FAILS|N/A]
*
* 1. Input parameters are NULL.\n
* 2. Duplication of the CRL fails.\n
* 3. Memory allocation fails.[SEC_NULL|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* 1. The CRL is duplicated inside this function. And hence memory allocation happens.\n\n
* 2. If CRL is used, then X509_V_FLAG_CRL_CHECK flag has to be set in the X509_STORE_S structure.
* 3) It is Recommended that the date fields in crl is verified before loading it as the same is not
* done inside.
*
* @par Related Topics
* X509_storeNew,\n
* X509_storeSetFlags,\n
* X509_storeSetTime,\n
* X509_storeAddCert,\n
* SSL_ctxGetCertStore,\n
* SSL_ctxSetCertStore.
*/

SSLLINKDLL SEC_INT X509_storeAddCRL(X509_STORE_S *pstStore, 
                         X509_CRL_S *pstCRL);

/*
    Func Name: SSL_setCAKeyUsageMandatoryCheck
*/

/**
* @defgroup SSL_setCAKeyUsageMandatoryCheck
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_VOID SSL_setCAKeyUsageMandatoryCheck(SEC_INT iEnable);
* @endcode
* 
* @par Purpose
* This is used to set or reset the mandatory key usage extension checking.
* 
* @par Description
* SSL_setCAKeyUsageMandatoryCheck function sets or resets the mandatory key usage extension checking for a CA certificate.
* 
* @param[in] iEnable 1 is passed to enable the check and 0 to disable the check. [0-1]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* If the checking is enabled, it is required that the key usage extension and the keyCertSign bit be set in the
* certificate. The setting is global to SSL SDK for that application. The default is enabled.
* 
* @par Related Topics
* SSL_setKeyUsageCheck.
*/

SSLLINKDLL SEC_VOID SSL_setCAKeyUsageMandatoryCheck(SEC_INT iEnable);

/*
    Func Name: SSL_setKeyUsageCheck                                         
*/

/**
* @defgroup SSL_setKeyUsageCheck
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_VOID  SSL_setKeyUsageCheck(SEC_INT iEnable);
* @endcode
* 
* @par Purpose
* This is used to set or reset the Key Usage extension check.
* 
* @par Description
* SSL_setKeyUsageCheck function sets or resets the key usage extension checking for a certificate.
* 
* @param[in] iEnable 1 is passed to enable the check and 0 to disable the check. [0-1]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
* 
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* If the checking is enabled, then the key usage extension will be checked, if this extension is present in the
* certificate. The setting is global to SSL SDK for that application. The default is disabled.
*
* @par Related Topics
* SSL_setCAKeyUsageMandatoryCheck.
*/


SSLLINKDLL SEC_VOID  SSL_setKeyUsageCheck(SEC_INT iEnable);


/*
    Func Name: SSL_getCtxStoreTestIndicator
*/

/**
* @defgroup SSL_getCtxStoreTestIndicator
* @ingroup tls_x509Functions
* @par Prototype
* @code
* SEC_UINT SSL_getCtxStoreTestIndicator(SEC_INT *piTestIndicator);
* @endcode
* 
* @par Purpose
* This is used to get the SSL context certficate store test indicator.
* This is purely given for test functionality and does not provide
* any new functionality.
* 
* @par Description
* SSL_getCtxStoreTestIndicator function gets the SSL context certficate store
* test indicator. This is purely given for test functionality and
* does not provide any new functionality. This is not required for all
* application users and should be used on need basis.
* 
* @param[in] piTestIndicator Pointer to indicator where value will be updated [N/A|N/A]
* 
* @retval SEC_UINT On successful updation of indicator [TLS_SUCCESS|N/A]
*         SEC_UINT On failure [SEC_NULL|N/A]
* @par Required Header File
* tls_x509.h
* 
* @par Note
* \n
* NA
*
* @par Related Topics
* NA.
*/
SSLLINKDLL SEC_UINT SSL_getCtxStoreTestIndicator(SEC_INT *piTestIndicator);


//Error Codes used by X509_storeAddCRL
#define STORE_ADD_SAME_CRL_ALREADY (-2)
#define STORE_ADD_SSL_NEWER_CRL_EXIST (-3)
#define STORE_ADD_SSL_DATE_CMP_FAILS (-4)


#ifdef __cplusplus
}
#endif


#endif /*_IPSI_TLS_X509_H_*/


