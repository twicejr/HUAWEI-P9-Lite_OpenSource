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
#ifndef _IPSI_TLS_X509VERIFY_H_
#define _IPSI_TLS_X509VERIFY_H_

#include "ipsi_types.h"
#include "sec_crypto.h"
#include "sec_def.h"
#include "sec_list.h"
#include "asn-types.h"
#include "x509.h"
#include "x509_basictypes.h"
#include "x509v3_extn.h"



#ifdef  __cplusplus
extern "C"{
#endif

/* Declaration of struct stX509StoreCtx structure*/
struct stX509StoreCtx;

/** @defgroup tls_x509verify
* This section describes the Structures  of tls_x509verify.h.
*/

/** @defgroup tls_x509verifyStructures
* @ingroup tls_x509verify
* This sections contains the Stuctures in tls_x509verify.h.
*/

/* This structure holds all parameters associated with a verify operation
 * by including an X509_VERIFY_PARAM_S structure in related structures. The
 * parameters used can be customized.
 */

/** 
* @defgroup X509_VERIFY_PARAM_S
* @ingroup tls_x509verifyStructures
* @par Prototype
* @code
* typedef struct stX509VerifyParam
* {
*  SEC_CHAR *pcName;
*  DATETIME_S stCheckTime;
*  SEC_UINT32 ulInhFlags;
*  SEC_UINT32 ulFlags;
*  SEC_INT iDepth;
*  SEC_INT iPurpose;
* }X509_VERIFY_PARAM_S;
* @endcode
* 
* @par Description
* This structure holds all parameters associated with a verify operation by including an X509_VERIFY_PARAM_S structure
* in related structures. The parameters used can be customized.
*
* @datastruct pcName Name of the verification parameter.
* @datastruct stCheckTime The time that is used during certificate validation operation, for comparing the certificate 
* validity period.
* @datastruct ulInhFlags Inheritance flags.
* @datastruct ulFlags Flags that are to be used for certificate verification and CRL validation.
* @datastruct iDepth Depth to which the certificate validation has to be done.
* @datastruct iPurpose Purpose to check untrusted certificates.
*/
typedef struct stX509VerifyParam
{
    /*Name of the verification parameter.*/
    SEC_CHAR *pcName;
    
    /* The time is used during certificate validation operation.  The time is 
        used for comparing the certificate validity period.*/
    DATETIME_S stCheckTime;    
    
    /* Inheritance flags */
    SEC_UINT32 ulInhFlags; 
    
    /* Flags that are to be used for certificate verfification, CRL validation*/
    SEC_UINT32 ulFlags;    

    /* Depth to which the certificate validation has to be done*/
    SEC_INT iDepth;
    
    /* purpose to check untrusted certificates */
    SEC_INT iPurpose;        
    
} X509_VERIFY_PARAM_S;

/* This is an extended certificate structure that holds the certificate and extracted
    extensions from the certificate.  These extensions are used during the certificate
    chain validation*/
/** 
* @defgroup X509_CERT_EXTENDED_S
* @ingroup tls_x509verifyStructures
* @par Prototype
* @code
* typedef struct stCertExtnData
* {
*  X509_CERT_S* pstCert;    
*  SEC_INT iValid;
*  SEC_INT32 iPathLen;
*  SEC_UINT32 ulExtnFlags;
*  SEC_UINT32 uiExtKeyUsage;
*  SEC_UINT32 uiKeyusage;
*  SEC_UINT32 ulExProxyPathLen;
*  SEC_INT iReferences;
*  SEC_AsnOcts_S *pstSKID;
*  X509_AKID_S* pstAKID;
*  SEC_UCHAR aucSha1Hash[20];
*  SEC_PKEY_S* pstPublicKey;
* }X509_CERT_EXTENDED_S;
* @endcode
* 
* @par Description
* This is an extended certificate structure that holds the certificate and extracted extensions from the certificate.
* These extensions are used during the certificate chain validation.
*
* @datastruct pstCert Certificate for which the following certificate chain information
* has to be extracted from the extension fields.
* @datastruct iValid Flag to indicate whether the certificate is valid.
* @datastruct iPathLen Path length that has to be obtained from the Basic constraint
* extension for certificate chain validation.
* @datastruct ulExtnFlags Used to store the flags to indicate whether the certificate
* is CA certificate, along with other flag values used for certificate chain validation.
* @datastruct uiExtKeyUsage To store extended key usage details.
* @datastruct uiKeyusage To store key usage of the certificate.
* @datastruct ulExProxyPathLen Length of the Proxy certificate.
* @datastruct iReferences Value that indicates number of objects that are referring to this structure.
* @datastruct pstSKID Subject key identifier extension that contains the hash of the public key.
* @datastruct pstAKID Authority key identifier extension that contains the hash of the public key of the issuer
* along with the name of the certificate issuer and the serial number of the issuer.
* @datastruct aucSha1Hash[20] Digest of the Certificate.
* @datastruct pstPublicKey This is used to hold the public key of the certificate.
*/
typedef struct stCertExtnData                 
{
    /*    Certificate for which the following certificate chain information has to be 
        exytracted from the extension fields*/
    X509_CERT_S* pstCert;    
    
    /* Flag to indicate whether the certificate is valid*/
    SEC_INT iValid;

    /* Path length that has to be obtained from the Basic constraint extension for certificate 
    chain validation.*/
    SEC_INT32 iPathLen;
    
    /*    Used to stored the flags to indicate whether the certificate is CA certificate along with 
        other flag values used for certificate chain validation*/
    SEC_UINT32 ulExtnFlags;

    /*    To store extended key usage details*/
    SEC_UINT32 uiExtKeyUsage;

    /*    To store key usage of the certificate */
    SEC_UINT32 uiKeyusage;

    /* Length of the Proxy certificate */
    SEC_UINT32 ulExProxyPathLen;

    /* Value indicates number of objects that are referring to this structure*/
    SEC_INT iReferences;

    /* Subject key identifier extension that contains the hash of the public key*/
    SEC_AsnOcts_S *pstSKID;

    /* Authorioty key identifier extension that contains the hash of the public key of the issuer 
        along with the name of the certificate issuer and the serial number of the issuer*/
    X509_AKID_S* pstAKID;

    /*Digest of the Certificate*/
    SEC_UCHAR aucSha1Hash[20];

    /*This is used to hold the public key of the certificate*/
    SEC_PKEY_S* pstPublicKey;

    SEC_List_S *pCdpList;

    SEC_INT iX509StoreReference;

} X509_CERT_EXTENDED_S;

/* This is used to hold everything.  It is used for all certificate
 * validation.  Once we have a certificate chain, the 'verify'
 * function is then called to actually check the cert chain. */
/**
* @defgroup X509_STORE_S
* @ingroup tls_x509verifyStructures
* @par Prototype
* @code
* typedef struct stX509Store
* {
*  SEC_INT iCache;
*  SEC_List_S* pstObjects;
*  X509_VERIFY_PARAM_S *pstParam;
*  SEC_INT (*pfVerify)(struct stX509StoreCtx *pstContext);
*  SEC_INT (*pfVerify_cb)(SEC_INT iOk, struct stX509StoreCtx *pstContext);
*  SEC_INT (*pfGetIssuer)(X509_CERT_EXTENDED_S **pstIssuerCert, struct stX509StoreCtx *pstContext, X509_CERT_EXTENDED_S *pstExtndCert);
*  SEC_INT (*pfCheckIssued)(struct stX509StoreCtx *pstContext, X509_CERT_EXTENDED_S *pstExtndCert, X509_CERT_EXTENDED_S *pstIssuerCert);
*  SEC_INT (*pfCheckRevocation)(struct stX509StoreCtx *pstContext);
*  SEC_INT (*pfGetCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S **pstCRL, X509_CERT_EXTENDED_S *pstExtndCert);
*  SEC_INT (*pfCheckCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S *pstCRL);
*  SEC_INT (*pfCertCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S *pstCRL, X509_CERT_EXTENDED_S *pstExtndCert);
*  SEC_INT (*pfCleanup)(struct stX509StoreCtx *pstContext);
*  SEC_INT iReferences;
* }X509_STORE_S;
* @endcode
* 
* @par Description 
* This is used to hold everything.  It is used for all certificate validation. Once we have a certificate chain, the
* 'verify' function is then called to actually check the cert chain. 
*
* @datastruct iCache The following is a cache of trusted certs. If true, stash any hits.
* @datastruct pstObjects Cache of all objects.
* @datastruct pstParam verify parameters.
* @datastruct pfVerify This is a callback function that is used to verify the certificate chain. See pfVerify.
* @datastruct pfVerify_cb Error callback function. See pfVerify_cb.
* @datastruct pfGetIssuer This function is used to obtain the issuer certificate from the Context.
* @datastruct pfCheckIssued This function is used check whether pstExtndCert is issued by pstIssuerCert.
* @datastruct pfCheckRevocation Check revocation status of chain.
* @datastruct pfGetCrl Retrieve CRL from the Store context.
* @datastruct pfCheckCrl Check CRL validity.
* @datastruct pfCertCrl Check certificate against CRL.
* @datastruct pfCleanup Cleanup of the StoreContext structure.
* @datastruct iReferences Number indicates number of objects that refer this structure.
*/
typedef struct stX509Store
{
    /* The following is a cache of trusted certs */
    SEC_INT iCache;     /* if true, stash any hits */
    
    /* Cache of all objects */
    SEC_List_S* pstObjects; //List of X509_OBJECT_S

    X509_VERIFY_PARAM_S *pstParam;

    /* CALLBACKS FOR VARIOUS OPERATIONS */
    /* This is a callback function that is used to verify the certificate chain*/
    SEC_INT (*pfVerify)(struct stX509StoreCtx *pstContext);    

    /* Error CallBack function*/
    SEC_INT (*pfVerify_cb)(SEC_INT iOk, struct stX509StoreCtx *pstContext);    

    /* This CallBack function is used to obtain the issuer certificate from the Context*/
    SEC_INT (*pfGetIssuer)(X509_CERT_EXTENDED_S **pstIssuerCert, struct stX509StoreCtx *pstContext, X509_CERT_EXTENDED_S *pstExtndCert);    


    /* This callback function is used check whether pstExtndCert is issued by pstIssuerCert*/
    SEC_INT (*pfCheckIssued)(struct stX509StoreCtx *pstContext, X509_CERT_EXTENDED_S *pstExtndCert, X509_CERT_EXTENDED_S *pstIssuerCert); 

    /* Check revocation status of chain */
    SEC_INT (*pfCheckRevocation)(struct stX509StoreCtx *pstContext); 

    
    /* Retrieve CRL from the Store context*/
    SEC_INT (*pfGetCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S **pstCRL, X509_CERT_EXTENDED_S *pstExtndCert); /* retrieve CRL */
    
    /* Check CRL validity */
    SEC_INT (*pfCheckCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S *pstCRL); /* Check CRL validity */
    
    
    /* Check certificate against CRL */
    SEC_INT (*pfCertCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S *pstCRL, X509_CERT_EXTENDED_S *pstExtndCert); /* Check certificate against CRL */
    
    /* Cleanup of the StoreContext structure*/
    SEC_INT (*pfCleanup)(struct stX509StoreCtx *pstContext);

    /* Number indicates number of objects that refer this structure*/
    SEC_INT iReferences;

} X509_STORE_S;


/* This is a utility structure that is used to hold Certificate, CRL, Key and 
    an pointer to character*/
/**
* @defgroup X509_OBJECT_S
* @ingroup tls_x509verifyStructures
* @par Prototype
* @code
* typedef struct stX509Object
* {
*  SEC_INT iType;
*  union    
*  {
*   SEC_CHAR *ptr;
*   X509_CERT_EXTENDED_S *pstX509;
*   X509_CRL_S *pstCRL;
*   SEC_PKEY_S *pstKey;
*  }data;
* }X509_OBJECT_S;
* @endcode
* 
* @par Description 
* This is a utility structure that is used to hold Certificate, CRL, Key and an pointer to character.
*
* @datastruct iType Identifies the type of data the union contains.
* @datastruct ptr Pointer
* @datastruct pstX509 Pointer to extended certificate.
* @datastruct pstCRL Pointer to CRL structure.
* @datastruct pstKey Pointer to Key structure.
*/
typedef struct stX509Object
{
    /* Identifies the type of data the union contains*/
    SEC_INT iType;

    /*    Pointer to one of the following member*/
    union    
    {
        /* Pointer */
        SEC_CHAR *ptr;
        
        /*Pointer to extended certificate*/
        X509_CERT_EXTENDED_S *pstX509;
        
        /* Pointer to CRL structure*/
        X509_CRL_S *pstCRL;

        /* Pointer to Key structure*/
        SEC_PKEY_S *pstKey;
    } data;

} X509_OBJECT_S;





#ifdef __cplusplus
}
#endif


#endif /*_IPSI_TLS_X509VERIFY_H_*/

