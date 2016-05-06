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

#ifndef _IPSI_TLS_CONTEXT_H_
#define _IPSI_TLS_CONTEXT_H_


#include "sec_sys.h" 
#include "sec_list.h"
#include "sec_error.h"
#include "x509_basictypes.h"
#include "tls_x509verify.h"



#ifdef  __cplusplus
extern "C"{
#endif

/*
SSL_CTX -> X509_STORE    
		-> X509_LOOKUP_S
			->X509_LOOKUP_METHOD
		-> X509_LOOKUP_S
			->X509_LOOKUP_METHOD
 
SSL	-> X509_STORE_CTX_S
		->X509_STORE    

The X509_STORE holds the tables etc for verification stuff.
A X509_STORE_CTX_S is used while validating a single certificate.
The X509_STORE has X509_LOOKUPs for looking up certs.
The X509_STORE then calls a function to actually verify the
certificate chain.
*/


/* Begin */
#undef     X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT
#undef     X509_V_ERR_UNABLE_TO_GET_CRL
#undef     X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE
#undef     X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE
#undef     X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY
#undef     X509_V_ERR_CERT_SIGNATURE_FAILURE
#undef     X509_V_ERR_CRL_SIGNATURE_FAILURE
#undef     X509_V_ERR_CERT_NOT_YET_VALID
#undef     X509_V_ERR_CERT_HAS_EXPIRED
#undef     X509_V_ERR_CRL_NOT_YET_VALID
#undef     X509_V_ERR_CRL_HAS_EXPIRED
#undef     X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD
#undef     X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD
#undef     X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD
#undef     X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD
#undef     X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT
#undef     X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN
#undef     X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY
#undef     X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE
#undef     X509_V_ERR_CERT_CHAIN_TOO_LONG
#undef     X509_V_ERR_CERT_REVOKED
#undef     X509_V_ERR_INVALID_CA
#undef     X509_V_ERR_PATH_LENGTH_EXCEEDED
#undef     X509_V_ERR_INVALID_PURPOSE
#undef     X509_V_ERR_CERT_UNTRUSTED
#undef     X509_V_ERR_CERT_REJECTED
#undef     X509_V_ERR_ERROR_IN_CMP_CERT_NOT_BEFORE_FIELD
#undef     X509_V_ERR_ERROR_IN_CMP_CERT_NOT_AFTER_FIELD
#undef     X509_V_ERR_ERROR_IN_CMP_CRL_THIS_UPDATE_FIELD
#undef     X509_V_ERR_ERROR_IN_CMP_CRL_NEXT_UPDATE_FIELD
#undef     X509_V_ERR_SUBJECT_ISSUER_MISMATCH
#undef     X509_V_ERR_AKID_SKID_MISMATCH
#undef     X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH
#undef     X509_V_ERR_KEYUSAGE_NO_CERTSIGN
#undef     X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER
#undef     X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION
#undef     X509_V_ERR_KEYUSAGE_NO_CRL_SIGN
#undef     X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION
#undef     X509_V_ERR_INVALID_NON_CA
#undef     X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED
#undef     X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE
#undef     X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED
#undef     X509_V_ERR_INVALID_EXTENSION
#undef     X509_V_ERR_INVALID_POLICY_EXTENSION
#undef     X509_V_ERR_NO_EXPLICIT_POLICY


/* END */




#define		X509_V_OK					0
/* illegal error (for uninitialized values, to avoid X509_V_OK): 1 */

#define		X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT		2
#define		X509_V_ERR_UNABLE_TO_GET_CRL			3
#define		X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE	4
#define		X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE	5
#define		X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY	6
#define		X509_V_ERR_CERT_SIGNATURE_FAILURE		7
#define		X509_V_ERR_CRL_SIGNATURE_FAILURE		8
#define		X509_V_ERR_CERT_NOT_YET_VALID			9
#define		X509_V_ERR_CERT_HAS_EXPIRED			10
#define		X509_V_ERR_CRL_NOT_YET_VALID			11
#define		X509_V_ERR_CRL_HAS_EXPIRED			12
#define		X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD	13
#define		X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD	14
#define		X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD	15
#define		X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD	16
#define		X509_V_ERR_OUT_OF_MEM				17
#define		X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT		18
#define		X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN		19
#define		X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY	20
#define		X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE	21
#define		X509_V_ERR_CERT_CHAIN_TOO_LONG			22
#define		X509_V_ERR_CERT_REVOKED				23
#define		X509_V_ERR_INVALID_CA				24
#define		X509_V_ERR_PATH_LENGTH_EXCEEDED			25
#define		X509_V_ERR_INVALID_PURPOSE			26
#define		X509_V_ERR_CERT_UNTRUSTED			27
#define		X509_V_ERR_CERT_REJECTED			28
/* These are 'informational' when looking for issuer cert */
#define		X509_V_ERR_SUBJECT_ISSUER_MISMATCH		29
#define		X509_V_ERR_AKID_SKID_MISMATCH			30
#define		X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH		31
#define		X509_V_ERR_KEYUSAGE_NO_CERTSIGN			32
#define		X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER		33
#define		X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION		34
#define		X509_V_ERR_KEYUSAGE_NO_CRL_SIGN			35
#define		X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION	36
#define		X509_V_ERR_INVALID_NON_CA			37
#define		X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED		38
#define		X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE	39
#define		X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED	40

#define		X509_V_ERR_INVALID_EXTENSION			41
#define		X509_V_ERR_INVALID_POLICY_EXTENSION		42
#define		X509_V_ERR_NO_EXPLICIT_POLICY			43


/*Error for cert verfiy chain */

#define		IPSI_X509_V_ERR_DIFFERENT_CRL_SCOPE			44
#define		IPSI_X509_V_ERR_CRL_PATH_VALIDATION_ERROR		45





/**
* @defgroup tls_context
* This section describes the Structure and Functions in tls_context.h.
*/

/**
* @defgroup tls_contextStructure
* @ingroup tls_context
* This section contains the tls_context Structure.
*/


/*
#ifndef HEADER_SSL_LOCL_H
#define  CERT		char
#endif
*/


/*
Structure which holds the information related to the connection state of SSLv2 . 
*/ 

/**
* @defgroup X509_STORE_CTX_S 
* @ingroup tls_contextStructure
* @par Prototype
* @code
* struct stX509StoreCtx      
* {
*  X509_STORE_S *pstX509Store;
*  SEC_INT iCurrentMethod;	
*  X509_CERT_EXTENDED_S *pstExtndCert;		
*  SEC_List_S* pUntrustedCertList;	
*  SEC_List_S* pCRLs;  
*  X509_VERIFY_PARAM_S *pstParam;
*  SEC_VOID *pOtherContext;	
*  SEC_INT (*pfVerify)(struct stX509StoreCtx *pstContext);	
*  SEC_INT (*pfVerify_cb)(SEC_INT iOk, struct stX509StoreCtx *pstContext);	
*  SEC_INT (*pfGetIssuer)(X509_CERT_EXTENDED_S **pstIssuerCert, struct stX509StoreCtx *pstContext, X509_CERT_EXTENDED_S *pstExtndCert);	
*  SEC_INT (*pfCheckIssued)(struct stX509StoreCtx *pstContext, X509_CERT_EXTENDED_S *pstExtndCert, X509_CERT_EXTENDED_S *pstIssuerCert); 
*  SEC_INT (*pfCheckRevocation)(struct stX509StoreCtx *pstContext); 
*  SEC_INT (*pfGetCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S **pstCRL, X509_CERT_EXTENDED_S *pstExtndCert);
*  SEC_INT (*pfcheckCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S *pstCRL);
*  SEC_INT (*pfCertCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S *pstCRL, X509_CERT_EXTENDED_S *pstExtndCert);
*  SEC_INT (*pfCheckPolicy)(struct stX509StoreCtx *pstContext);
*  SEC_INT (*pfCleanup)(struct stX509StoreCtx *pstContext);
*  SEC_INT iValid;
*  SEC_INT iLastUntrusted;	
*  SEC_INT iDepth;
*  SEC_List_S* pstCertChain; 
*  SEC_INT iExplicitPolicy;	
*  SEC_INT iErrorDepth;
*  SEC_INT iError;
*  X509_CERT_EXTENDED_S *pstCurrentCert;
*  X509_CERT_EXTENDED_S* pstCurrentIssuer;
*  X509_CRL_S *pstCurrentCRL;
*  SEC_INT  current_crl_score;
*  SEC_UINT current_reasons;
*  struct stX509StoreCtx *parent;
*  SEC_INT iCrossCaPos;
*  SEC_UINT isCrossCA;
*  SEC_VOID *pVerifyCBAppData;
*  SEC_INT iVerifyMode;
* };
* @endcode
*
* @par Description
* This is used while verifying cert chains.  Since the gathering of the cert chain can take some time (and have to be
* 'retried', this needs to be kept and passed around.) 
*
* @datastruct pstX509Store Structure used for certificate validation. It points to the X509_STORE_S object in SSL Context
* object. See Building X509_STORE_S.
* @datastruct iCurrentMethod  Used when looking up certs 
* @datastruct pstExtndCert The certificate to check, recieved from the peer side. 	
* @datastruct pUntrustedCertList chain of X509_CERT_EXTENDED_S untrusted certificates- passed in, recieved from the peer
* side.
* @datastruct pCRLs  List of X509_CRL_S. It is SEC_NULL if application does not set this field directly. CRL can be got
* in pstX509Store.
* @datastruct pstParam pointer to verify parameter.
* @datastruct pOtherContext Stack of Trusted certificates, used with pfGetIssuer().
* @datastruct pfVerify Callback to verify a certificate. See pfVerify.
* @datastruct pfVerify_cb Error Callback. See pfVerify_cb.
* @datastruct pfGetIssuer Function to get the issuer certificate from X509 store ctx.
* @datastruct pfCheckIssued Function to check whether the subject certificate was issued by issuer certificate.
* @datastruct pfCheckRevocation Function to check revocation status of chain.
* @datastruct pfGetCrl Function to retrieve CRL.
* @datastruct pfcheckCrl Function to check CRL validity.
* @datastruct pfCertCrl Function to check certificate against CRL.
* @datastruct pfCheckPolicy Function to check Certificate policy.
* @datastruct pfCleanup Function to clean x509 store ctx.
* @datastruct iValid if 0 rebuild chain.
* @datastruct iLastUntrusted index of last untrusted cert.
* @datastruct iDepth Number indicating the depth to which the certificate validation had to be performed.
* @datastruct pstCertChain  Chain of X509_CERT_EXTENDED_S certificates - built up based on the untrusted certificate
* chain received from peer side and trusted certificate loaded in X509_STORE_S object in SSL Context object.
* @datastruct iExplicitPolicy Require explicit policy value.
* @datastruct iErrorDepth If error occured, error depth shows which certificate in the chain has an Error, used along with
* iError. If internal verify success, it shows which certificate in the chain is being checked now.
* @datastruct iError Has the error related to certificate chains, used along with iErrorDepth.
* @datastruct pstCurrentCert Current Certificate.
* @datastruct pstCurrentIssuer Certificate currently being tested as valid issuer.
* @datastruct pstCurrentCRL Current CRL.
* @datastruct current_crl_score Score of current CRL
* @datastruct current_reasons CRL reasons
* @datastruct parent Parent context for CRL validation
* @datastruct CrossCaPos Variable to indicate the cross ca position
* @datastruct isCrossCA Variable to check if it is cross CA
* @datastruct pVerifyCBAppData Variable to hold the application data of pfVerify_cb.
* @datastruct iVerifyMode Variable to hold the Verify Mode.
*
* @par Note
* \n
* This Structure is type defined as X509_STORE_CTX_S and same can be used.
*/

struct stX509StoreCtx      /* X509_STORE_CTX_S */
{
    X509_STORE_S *pstX509Store;

    SEC_INT iCurrentMethod;	/* used when looking up certs */

    /* The following are set by the caller */
    X509_CERT_EXTENDED_S *pstExtndCert;		/* The cert to check */


    SEC_List_S* pUntrustedCertList;	/* chain of X509_CERT_EXTENDED_S untrusted certificates- passed in */

    SEC_List_S* pCRLs;  // List of X509_CRL_S

    X509_VERIFY_PARAM_S *pstParam;


    SEC_VOID *pOtherContext;	/* Other info for use with pfGetIssuer() */

    /* CALLBACKS FOR VARIOUS OPERATIONS */

    SEC_INT (*pfVerify)(struct stX509StoreCtx *pstContext);	/* called to verify a certificate */

    SEC_INT (*pfVerify_cb)(SEC_INT iOk, struct stX509StoreCtx *pstContext);	/* error callback */

    SEC_INT (*pfGetIssuer)(X509_CERT_EXTENDED_S **pstIssuerCert, struct stX509StoreCtx *pstContext, X509_CERT_EXTENDED_S *pstExtndCert);	/* get issuers cert from ctx */


    SEC_INT (*pfCheckIssued)(struct stX509StoreCtx *pstContext, X509_CERT_EXTENDED_S *pstExtndCert, X509_CERT_EXTENDED_S *pstIssuerCert); /* check issued */

    SEC_INT (*pfCheckRevocation)(struct stX509StoreCtx *pstContext); /* Check revocation status of chain */


    SEC_INT (*pfGetCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S **pstCRL, X509_CERT_EXTENDED_S *pstExtndCert); /* retrieve CRL */

    SEC_INT (*pfcheckCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S *pstCRL); /* Check CRL validity */


    SEC_INT (*pfCertCrl)(struct stX509StoreCtx *pstContext, X509_CRL_S *pstCRL, X509_CERT_EXTENDED_S *pstExtndCert); /* Check certificate against CRL */

    //Check certificate policy
    SEC_INT (*pfCheckPolicy)(struct stX509StoreCtx *pstContext);

    SEC_INT (*pfCleanup)(struct stX509StoreCtx *pstContext);


    /* The following is built up */
    SEC_INT iValid;		/* if 0, rebuild chain */

    SEC_INT iLastUntrusted;	/* index of last untrusted cert */


    SEC_INT iDepth;

    /* chain of X509s - built up and trusted */
    SEC_List_S* pstCertChain; 


    SEC_INT iExplicitPolicy;	/* Require explicit policy value */

    /* When something goes wrong, this is why */
    SEC_INT iErrorDepth;

    SEC_INT iError;

    X509_CERT_EXTENDED_S *pstCurrentCert;

    /* cert currently being tested as valid issuer */
    X509_CERT_EXTENDED_S* pstCurrentIssuer;


    /* current CRL */
    X509_CRL_S *pstCurrentCRL;

    SEC_INT  current_crl_score;  /* score of current CRL */
    SEC_UINT current_reasons;  /* Reason mask */

    struct stX509StoreCtx *parent; /* For CRL path validation: parent context */

    /*Variable to indicate the cross ca position*/
    SEC_INT iCrossCaPos;

    /* Variable to check if it is cross CA */
    SEC_UINT isCrossCA;

    /* variable to hold app data of the verify call back */
    SEC_VOID *pVerifyCBAppData;

    /* Variable to hold  the Verify Mode */
    SEC_INT iVerifyMode; 
};



/** @defgroup tls_contextFunctions
* @ingroup tls_context
* This section contains the Functions of tls_context.
*/


/*
    Func Name: X509_storeCtxNew												   
*/

/**
* @defgroup X509_storeCtxNew
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* struct stX509StoreCtx *X509_storeCtxNew(SEC_VOID);
* @endcode
* 
* @par Purpose
* This is used to create X509_STORE_CTX_S structure.
* 
* @par Description
* X509_storeCtxNew function creates a new X509_STORE_CTX_S structure.
*
* @par Parameters
* N/A
*
* @retval X509_STORE_CTX_S* The pointer to X509_STORE_CTX_S structure is returned. [Pointer to X509_STORE_CTX_S|N/A]
* @retval X509_STORE_CTX_S* If memory allocation fails. [SEC_NULL|N/A]
* 
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509StoreCtx is typedef to X509_STORE_CTX_S, and same can be used.
*
* @par Related Topics
* X509_storeCtxFree,\n
* X509_storeCtxInit,\n
* X509_storeCtxCleanUp.
*/
SSLLINKDLL struct stX509StoreCtx *X509_storeCtxNew(SEC_VOID);



/*
    Func Name: X509_storeCtxFree                                                 
*/

/**
* @defgroup X509_storeCtxFree
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_VOID X509_storeCtxFree(struct stX509StoreCtx *ctx);
* @endcode
* 
* @par Purpose
* This is used to free the structure X509_STORE_CTX_S.
* 
* @par Description
* X509_storeCtxFree function frees the X509_STORE_CTX_S structure created using X509_storeCtxNew.
* 
* @param[in] ctx The X509_STORE_CTX_S structure that has to be freed. [N/A]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
* 
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509StoreCtx is typedef to X509_STORE_CTX_S, and same can be used.
*
* @par Related Topics
* X509_storeCtxNew,\n
* X509_storeCtxInit,\n
* X509_storeCtxCleanUp.
*/
								   
SSLLINKDLL SEC_VOID X509_storeCtxFree(struct stX509StoreCtx *ctx);

/*
    Func Name: X509_storeCtxInit
*/

/**
* @defgroup X509_storeCtxInit
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_INT X509_storeCtxInit(struct stX509StoreCtx *ctx,
* X509_STORE_S *store,
* X509_CERT_EXTENDED_S *x509,
* SEC_List_S *chain); 
* @endcode
* 
* @par Purpose
* This is used to initialize the structure X509_STORE_CTX_S.
* 
* @par Description
* X509_storeCtxInit function initializes the X509_STORE_CTX_S structure created with X509_storeCtxNew.
* The initialization values being taken from X509_STORE_S,X509_CERT_EXTENDED_S and  SEC_List_S passed as input parameters.
* 
* @param[in] store The X509_STORE_S structure that has to be copied. [N/A]
* @param[in] x509 The X509_CERT_EXTENDED_S extended certificate that has to be copied. [N/A]
* @param[in] chain The chain of X509_CERT_EXTENDED_S certificate that has to be copied. [N/A]
* @param[in] ctx The X509_STORE_CTX_S structure that has been initialized. [N/A]
* 
* @retval SEC_INT In case of success, 1 is returned. [TLS_SUCCESS|N/A]
* @retval SEC_INT In case of failure, 0 is returned. Failure happens in case of a memory allocation failure[SEC_NULL|N/A]
* @retval SEC_INT In case of failure when input ctx is NULL, SEC_ERROR is returned. [SEC_ERROR|N/A]
*
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509Store is typedef to X509_STORE_CTX_S, and same can be used
*
* @par Related Topics
* X509_storeCtxNew,\n
* X509_storeCtxFree,\n
* X509_storeCtxCleanUp.
*/
SSLLINKDLL SEC_INT X509_storeCtxInit(struct stX509StoreCtx *ctx, X509_STORE_S *store,
			            X509_CERT_EXTENDED_S *x509, SEC_List_S *chain); 

/*
    Func Name: X509_storeCtxCleanUp                                      
*/

/**
* @defgroup X509_storeCtxCleanUp
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_VOID X509_storeCtxCleanUp(struct stX509StoreCtx *ctx);
* @endcode
* 
* @par Purpose
* This is used to cleanup context store.
* 
* @par Description
* X509_storeCtxCleanUp function is called to free up all the elements in X509_STORE_CTX_S structure.
*
* @param[in] ctx X509_STORE_CTX_S structure that has to be cleaned. [N/A]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* 1. struct stX509Store is typedef to X509_STORE_CTX_S, and same can be used.\n\n
* 2. Usually, this API should not be called directly. X509_storeCtxFree will call this API internally. So calling this
*    API along with X509_storeCtxFree will lead to crash.
*
* @par Related Topics
* X509_storeCtxNew,\n
* X509_storeCtxFree,\n
* X509_storeCtxInit.
*/ 
SSLLINKDLL SEC_VOID X509_storeCtxCleanUp(struct stX509StoreCtx *ctx);

/*
    Func Name: X509_storeCtxGetError                                      
*/

/**
* @defgroup X509_storeCtxGetError
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_INT X509_storeCtxGetError(struct stX509StoreCtx *ctx);
* @endcode
* 
* @par Purpose
* This is used to get Errors in X509_STORE_CTX_S structure.
* 
* @par Description
* X509_storeCtxGetError function can be used to get the errors in case of certificates chains verification.
* Example: if returned X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER means unable to get the crl issuer.
* And the respective error depth can be obtained using the function X509_storeCtxGetErrorDepth.
*
* @param[in] ctx X509_STORE_CTX_S structure that has certificates. [N/A]
* 
* @retval SEC_INT Returns the value of Error. [Error|N/A]
*
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509Store is typedef to X509_STORE_CTX_S, and same can be used.
*
* @par Related Topics
* X509_storeCtxGetErrorDepth.
*/  
SSLLINKDLL SEC_INT	X509_storeCtxGetError(struct stX509StoreCtx *ctx);

/*
    Func Name: X509_storeCtxGetErrorDepth                                      
*/

/**
* @defgroup X509_storeCtxGetErrorDepth
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_INT X509_storeCtxGetErrorDepth(struct stX509StoreCtx *ctx);
* @endcode
* 
* @par Purpose
* This is used to get Error Depth in the certificate chain.
* 
* @par Description
* In case of certificate chains verification, this function can be used to get the error depth, error depth shows which
* certificate in the chain has an Error. And the respective error can be obtained using the function
* X509_storeCtxGetError.
*
* @param[in] ctx X509_STORE_CTX_S structure that has certificate chain. [N/A]
* 
* @retval SEC_INT Returns the value of Error Depth . [Error Depth|N/A]
* @retval SEC_INT SEC_ERROR is returned if ctx passed is NULL. [SEC_ERROR|N/A]
*
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509Store is typedef to X509_STORE_CTX_S, and same can be used.
*
* @par Related Topics
* X509_storeCtxGetError.
*/   
SSLLINKDLL SEC_INT	X509_storeCtxGetErrorDepth(struct stX509StoreCtx *ctx);
  
/*
    Func Name: X509_storeCtxGetCurrentCert                                      
*/

/**
* @defgroup X509_storeCtxGetCurrentCert
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* X509_CERT_EXTENDED_S*	X509_storeCtxGetCurrentCert(struct stX509StoreCtx *ctx);
* @endcode
* 
* @par Purpose
* This is used to get current X509_CERT_EXTENDED_S certificate.
* 
* @par Description
* X509_storeCtxGetCurrentCert function gets the current X509_CERT_EXTENDED_S certificate from ctx.
*
* @param[in] ctx X509_STORE_CTX_S structure that has certificate. [N/A]
* 
* @retval X509_CERT_EXTENDED_S* In Case of Success X509_CERT_EXTENDED_S certificate is returned .
* [Pointer to X509_CERT_EXTENDED_S|N/A]
* @retval X509_CERT_EXTENDED_S* In Case of failure, SEC_NULL is returned, failure Happens in case of input ctx is
* SEC_NULL [SEC_NULL|Do not pass SEC_NULL]
*
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509Store is typedef to X509_STORE_CTX_S, and same can be used.
*
* @par Related Topics
* X509_storeCtxGetChain.
*/ 
SSLLINKDLL X509_CERT_EXTENDED_S*	X509_storeCtxGetCurrentCert(struct stX509StoreCtx *ctx);
  

/*
    Func Name: X509_storeCtxGetChain                                      
*/

/**
* @defgroup X509_storeCtxGetChain
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_List_S* X509_storeCtxGetChain(struct stX509StoreCtx *ctx);
* @endcode
* 
* @par Purpose
* This is used to get list of X509_CERT_EXTENDED_S certificate.
* 
* @par Description
* X509_storeCtxGetChain function gets the X509_CERT_EXTENDED_S certificate chain from ctx.
*
* @param[in] ctx X509_STORE_CTX_S structure that has certificate chain. [N/A]
* 
* @retval SEC_List_S* In Case of Success list of X509_CERT_EXTENDED_S certificate is returned .
* [Pointer to SEC_List_S|N/A]
* @retval SEC_List_S* In Case of failure, SEC_NULL is returned, failure Happens in case of input ctx is SEC_NULL
* [SEC_NULL|Do not pass SEC_NULL]
*
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509Store is typedef to X509_STORE_CTX_S, and same can be used.
*
* @par Related Topics
* X509_storeCtxGetCurrentCert.
*/  
SSLLINKDLL SEC_List_S* X509_storeCtxGetChain(struct stX509StoreCtx *ctx);
	
/*
    Func Name: X509_storeCtxSetFlags
*/

/**
* @defgroup X509_storeCtxSetFlags
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_VOID X509_storeCtxSetFlags(struct stX509StoreCtx *ctx, SEC_UINT32 flags);
* @endcode
* 
* @par Purpose
* This is used to set the certificate verification flag.
* 
* @par Description
* X509_storeCtxSetFlags function sets the certificate verification flag in pstParam field of X509_STORE_CTX_S structure.
* Each new flag passed is ORed with existing flag. The final flag value is used for certificate verification and/or CRL
* validation. Example: pass X509_V_FLAG_ALLOW_PROXY_CERTS flag to enable proxy certificate validation.
* Also refer to Certificate verification flags in tls_x509.h for more flags.
*
* @param[in] Flags The flags that has to be set. [N/A]
* @param[in] ctx The X509_STORE_CTX_S structure that is set with flags. [N/A]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
* 
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509Store is typedef to X509_STORE_CTX_S, and same can be used.
*
* @par Related Topics
* X509_storeCtxSetTime.
*/ 
SSLLINKDLL SEC_VOID X509_storeCtxSetFlags(struct stX509StoreCtx *ctx, SEC_UINT32 flags);

  
/*
    Func Name: X509_storeCtxSetTime                                              
*/

/**
* @defgroup X509_storeCtxSetTime
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_VOID X509_storeCtxSetTime(struct stX509StoreCtx *ctx, SEC_UINT32 flags, DATETIME_S t);
* @endcode
* 
* @par Purpose
* This is used to set and enable check time, for certificate validity period.
* 
* @par Description
* X509_storeCtxSetTime function sets date and time to the pstParam field in X509_STORE_CTX_S structure and 
* also X509_V_FLAG_USE_CHECK_TIME(Use check time instead of current time) is set in certificate 
* verification flag in pstParam field.The time is used for checking the certificate validity period.
* 
* @param[in] t The time that has to be set in pstStore. [N/A]
* @param[in] flags Not used [N/A]
* @param[in] ctx The X509_STORE_S structure that is set with date and time. [N/A]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
* 
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509Store is typedef to X509_STORE_CTX_S, and same can be used.
*
* @par Related Topics
* X509_storeCtxSetFlags.
*/	
SSLLINKDLL SEC_VOID X509_storeCtxSetTime(struct stX509StoreCtx *ctx, SEC_UINT32 flags,
								DATETIME_S t);

/*
    Func Name: X509_storeCtxGetCrossCaPos                                      
*/

/**
* @defgroup X509_storeCtxGetCrossCaPos
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_INT X509_storeCtxGetCrossCaPos(struct stX509StoreCtx *ctx);
* @endcode
* 
* @par Purpose
* This is used to get position of cross CA certificate from certificate chain.
* 
* @par Description
* X509_storeCtxGetCrossCaPos function gets the position of cross CA certificate
* from certificate chain.
*
* @param[in] ctx X509_STORE_CTX_S structure that has certificate chain. [N/A]
* 
* @retval SEC_INT In Case of Success position of cross CA certificate is returned.
* @retval SEC_INT In Case of failure, SEC_ERROR is returned
*
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* Struct stX509Store is typedef to X509_STORE_CTX_S, and same can be used.
*
*/

SSLLINKDLL SEC_INT X509_storeCtxGetCrossCaPos(struct stX509StoreCtx *ctx);


/*
    Func Name: X509_storeCtxGetAppData
*/

/**
* @defgroup X509_storeCtxGetAppData
* @ingroup tls_contextFunctions
* @par Prototype
* @code
* SEC_VOID *X509_storeCtxGetAppData(struct stX509StoreCtx *pstStoreCtx)
* @endcode
* 
* @par Purpose
* This is used to get the verify callback application data from X509 
* certificate store context. \n
* 
* @par Description
* X509_storeCtxGetAppData function gets the verify callback application
* data from X509 certificate store context. This application data value has
* been taken from the SSL object before doing ceritificate verification.
* SSL library will not do any validation or memory allocation/deallocation 
* for the application data.\n
*
* @param[in] pstStoreCtx Pointer to X509 certificate store context [N/A|N/A]
* 
* @retval SEC_VOID* Pointer to application data will be returned, \n
* or\n
* SEC_NULL will be returned in following conditions: \n
* 1. If the input is invalid (NULL pointer is passed as input) \n
* 2. If pointer to the application data is not set.
* [Pointer to application data or SEC_NULL|N/A]
*
* @par Required Header File
* tls_context.h
* 
* @par Note
* \n
* NA
*
* @par Related Topics
* SSL_setVerifyCBAppData \n
* SSL_ctxSetVerifyCBAppData \n
* SSL_getVerifyCBAppData \n
* SSL_ctxGetVerifyCBAppData
*/

SSLLINKDLL SEC_VOID *X509_storeCtxGetAppData(struct stX509StoreCtx *
                                                                pstStoreCtx);


#ifdef __cplusplus
}
#endif


#endif /*_IPSI_TLS_CONTEXT_H_*/



