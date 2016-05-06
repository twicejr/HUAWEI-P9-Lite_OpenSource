/***************************************************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: sec_pki_def.h
Version: 1
Author:
Creation Date:
Description: This file contains definitions of the PKI

Function List:

History:
<Author>   <date>          <desc>

***************************************************************************/

#include "ipsi_pse_build_conf.h"

#ifndef __SEC_PKI_DEF_H__
#define __SEC_PKI_DEF_H__

#include "ipsi_types.h"
#include "asn-types.h"
#include "x509_basictypes.h"
#include "sec_sys.h"
#include "sec_crypto.h"
#include "x509v3_extn.h"
#include "ipsi_time.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define SEC_PKI_SUCCESS 0
#define SEC_PKI_ERROR  (-1)
#define SEC_PKI_CB_SUCCESS 1
#define SEC_PKI_CB_ERROR 0
#define SEC_PKI_NAME_MAXLEN 256

#ifndef IPSI_SEC_NO_PKI

/**
* @defgroup PKI
* This section contains all the enums, structures, and functions in the PKI 
* library.
*/
/**
* @defgroup Constants
* @ingroup PKI
* This section contains all the enums and structure used in PKI library.
*/

/**
* @defgroup Enums
* @ingroup Constants
* This section contains all the enums used in PKI library.
*/

/**
* @defgroup Structures
* @ingroup Constants
* This section contains all the structures used in PKI library.
*/

/* Flag to indicate PEM format*/
#define SEC_PKI_FILETYPE_PEM                1

/* Flag to indicate ASN format*/
#define SEC_PKI_FILETYPE_ASN1               2

/* Flag to indicate PFX format*/
#define SEC_PKI_FILETYPE_PFX                4

/* Algorithm ID for SHA1 */
#define SEC_ALG_SHA1 ALGID_SHA1

/* Verify parameters */
/**
* @defgroup SEC_PKI_VERIFY_TYPE_E
* @ingroup Enums
* @par Description
* Flags indicating verification type.
* @par Prototype
* @code
* typedef enum
* {
*    SEC_PKI_CHECK_TIME      = 0x00000001,
*    SEC_PKI_CHECK_CRL       = 0x00000002,
*    SEC_PKI_CHECK_CRL_ALL   = 0x00000004,
*    SEC_PKI_CHECK_DELTA_CRL = 0x00000008,
*    SEC_PKI_CHECK_CRL_CROSS_CA = 0x00000010,
*    SEC_PKI_CHECK_OCSP      = 0x00000020,
*    SEC_PKI_X509_V_FLAG_IGNORE_CRITICAL      = 0x00000040,
*    SEC_PKI_CHECK_CROSS_CA      = 0x00000080,
*    SEC_PKI_EXTENDED_CRL_SUPPORT = 0x00000100,
*    SEC_PKI_OBJ_CRL_SUPPORT = 0x00000200,
*    SEC_PKI_CHECK_OCSP_ALL      = 0x00000400,
*    SEC_PKI_OCSP_RESPONDER_CHECK_CRL = 0x00000800,
*    SEC_PKI_OCSP_RESPONDER_CHECK_DELTA_CRL = 0x00001000,
*    SEC_PKI_OCSP_TRUST_RESPONDER_CERTS_IN_MSG  = 0x00002000,
*    SEC_PKI_OBJ_OCSP_SUPPORT = 0x00004000
* }SEC_PKI_VERIFY_TYPE_E;
* @endcode
* @datastruct SEC_PKI_CHECK_TIME checks time validation with respect to time
* in verify parameter.
* @datastruct SEC_PKI_CHECK_CRL Enables CRL validation only for end entity cert.
* @datastruct SEC_PKI_CHECK_CRL_ALL Enables CRL validation for entire chain.
* @datastruct SEC_PKI_CHECK_DELTA_CRL Enables delta CRL validation.
* @datastruct SEC_PKI_CHECK_CRL_CROSS_CA Enables cross CA validation with CRL.
* @datastruct SEC_PKI_CHECK_OCSP Enables OCSP validation.
* @datastruct SEC_PKI_X509_V_FLAG_IGNORE_CRITICAL ignores critical extension
* @datastruct SEC_PKI_CHECK_CROSS_CA Enables cross CA validation.
* @datastruct SEC_PKI_EXTENDED_CRL_SUPPORT Supports reason codes or
* @datastruct SEC_PKI_OBJ_CRL_SUPPORT Supports object inband CRL
* @datastruct SEC_PKI_OCSP_RESPONDER_CHECK_CRL Enables OCSP Responder 
* certificate CRL validation
* @datastruct SEC_PKI_OCSP_RESPONDER_CHECK_DELTA_CRL Enables OCSP Responder 
* certificate Delta CRL validation
* @datastruct SEC_PKI_OCSP_TRUST_RESPONDER_CERTS_IN_MSG Enables to use OCSP 
* Responder certificate available in the response message.
* @datastruct SEC_PKI_OBJ_OCSP_SUPPORT Supports Object inband OCSP support.
*/
typedef enum
{
    SEC_PKI_CHECK_TIME      = 0x00000001,
    SEC_PKI_CHECK_CRL       = 0x00000002,
    SEC_PKI_CHECK_CRL_ALL   = 0x00000004,
    SEC_PKI_CHECK_DELTA_CRL = 0x00000008,
    SEC_PKI_CHECK_CRL_CROSS_CA = 0x00000010,
    SEC_PKI_CHECK_OCSP      = 0x00000020,
    SEC_PKI_X509_V_FLAG_IGNORE_CRITICAL = 0x00000040,
    SEC_PKI_CHECK_CROSS_CA = 0x00000080,
    SEC_PKI_EXTENDED_CRL_SUPPORT = 0x00000100,
    SEC_PKI_OBJ_CRL_SUPPORT = 0x00000200,
    SEC_PKI_CHECK_OCSP_ALL      = 0x00000400,
    SEC_PKI_OCSP_RESPONDER_CHECK_CRL = 0x00000800,
    SEC_PKI_OCSP_RESPONDER_CHECK_DELTA_CRL = 0x00001000,
    SEC_PKI_OCSP_TRUST_RESPONDER_CERTS_IN_MSG  = 0x00002000,
    SEC_PKI_OBJ_OCSP_SUPPORT = 0x00004000
}SEC_PKI_VERIFY_TYPE_E;


/**
* @defgroup SEC_PKI_VERIFY_TIME_RESULT_S
* @ingroup Structures
* @par Description
* Data buffer to hold the verify cert/crl time differences and error code
* @par Prototype
* @code
* typedef struct stVerifyTimeResult
* {
*   SEC_INT iErrorCode;
*   signed ipsi_time_t lBefore_thisUpdate_Diff;
*   signed ipsi_time_t lAfter_Nextupdate_Diff;
* }SEC_PKI_VERIFY_TIME_RESULT_S;
* @endcode
* @datastruct iErrorCode Holds the errorcode which indicates
* if the certificate is valid, expired or not yet valid. 
* It can be any one of the time related errorcodes, among the 
* certificate chain validation errors defined below. 
* In success case the errorcode is 0.
* @datastruct lBefore_thisUpdate_Diff Contains time difference between the 
* not before field and the effective check time (includes input 
* iDifference seconds).
* @datastruct lAfter_Nextupdate_Diff Contains time difference between the 
* effective check time and the not after field.
*
* @par Note
* \n
* This structure is stored in a list and returned to the user which
* will not be freed by the library.
*/

typedef struct stVerifyTimeResult
{
    SEC_INT iErrorCode;
    ipsi_time_t lBefore_thisUpdate_Diff;
    ipsi_time_t lAfter_Nextupdate_Diff;
}SEC_PKI_VERIFY_TIME_RESULT_S;


/**
* @defgroup SEC_PKI_PARAMETER_E
* @ingroup Enums
* @par Description
* Indicates the type of information to be used for generate Certificate
* request.
* @par Prototype
* @code
* typedef enum
* {
*    SEC_PKI_CAHASH = 1,
*    SEC_PKI_CASUBJECT,
*    SEC_PKI_CACERT
* } SEC_PKI_PARAMETER_E;
* @endcode
* @datastruct SEC_PKI_CAHASH If this flag is selected the 
* certificate request generated will contain CA_public_keyHash.
* @datastruct SEC_PKI_CASUBJECT If this flag is selected the 
* certificate request generated will contain CA_public_keySubject.
* @datastruct SEC_PKI_CACERT If this flag is selected the 
* certificate request generated will contain CA_public_keyCert.
*
*/

typedef enum
{
    /* Request type is SHA1 hash of CA's Public Key */
    SEC_PKI_CAHASH = 1,

    /* Request type is encoded subject name of CA's */
    SEC_PKI_CASUBJECT,

    /* Request type is encoded certificates of CA's */
    SEC_PKI_CACERT 
}SEC_PKI_PARAMETER_E;


/**
* @defgroup SEC_PKI_X509_ALT_NAME_TYPE_E
* @ingroup Enums
* @par Description
* Indicates the type of subject alternative name.
* @par Prototype
* @code
* typedef enum
* {
*    SEC_PKI_TYPE_DNSNAME = GENERALNAME_DNSNAME,
*    SEC_PKI_TYPE_IPADDRESS = GENERALNAME_IPADDRESS,
*    SEC_PKI_TYPE_EMAILID = GENERALNAME_RFC822NAME
* } SEC_PKI_X509_ALT_NAME_TYPE_E;
* @endcode
* @datastruct SEC_PKI_TYPE_DNSNAME  DNS Name as subject alternative name.
* @datastruct SEC_PKI_TYPE_IPADDRESS IP address as subject alternative name.
* @datastruct SEC_PKI_TYPE_EMAILID RFC822 name as subject alternative name.

*
*/
typedef enum enPKIX509AltNameType
{
    SEC_PKI_TYPE_DNSNAME = GENERALNAME_DNSNAME,     /* ID type FQDN */
    SEC_PKI_TYPE_IPADDRESS = GENERALNAME_IPADDRESS,  /* ID type IPV4 address */
    SEC_PKI_TYPE_EMAILID = GENERALNAME_RFC822NAME  /* ID type  e-mail id*/
} SEC_PKI_X509_ALT_NAME_TYPE_E;


/**
* @defgroup SEC_PKI_X509_ALG_TYPE_E
* @ingroup Enums
* @par Description
* Indicates the type of public key algorithm type
* @par Prototype
* @code
* typedef enum
* {
*    SEC_ALG_RSA = ALGID_RSA,
*    SEC_ALG_DSA = ALGID_DSA,
*    SEC_ALG_ECDSA = ALGID_ECDSA
* } SEC_PKI_X509_ALG_TYPE_E;
* @endcode
* @datastruct SEC_ALG_RSA RSA as public key algorithm type.
* @datastruct SEC_ALG_DSA DSA as public key algorithm type.
* @datastruct SEC_ALG_ECDSA ECDSA as public key algorithm type.
*
*/
typedef enum enPKIX509AlgID
{
    SEC_ALG_RSA = ALGID_RSA, /* Algorithm type RSA */
    SEC_ALG_DSA = ALGID_DSA,  /* Algorithm type DSA */
    SEC_ALG_ECDSA = ALGID_ECDSA  /* Algorithm type ECDSA */
} SEC_PKI_X509_ALG_TYPE_E;



/**
* @defgroup SEC_PKI_ENCODE_TYPE_E
* @ingroup Enums
* @par Description
* Indicates the type of encoding.
* @par Prototype
* @code
* typedef enum
* {
*    SEC_PKI_DER_ENCODE,
*    SEC_PKI_PKCS7_WRAPPED,
* } SEC_PKI_ENCODE_TYPE_E;
* @endcode
* @datastruct SEC_PKI_DER_ENCODE DER/ASN1 encoding.
* @datastruct SEC_PKI_PKCS7_WRAPPED PKCS7 encoding.
*
*/

/*Encoding Types*/
typedef enum
{
    SEC_PKI_DER_ENCODE,
    SEC_PKI_PKCS7_WRAPPED
} SEC_PKI_ENCODE_TYPE_E;




/**
* @defgroup SEC_PKI_SYNC_TYPE_E
* @ingroup Enums
* @par Prototype
* @code
* typedef enum
* {
*   SEC_PKI_DFLT_LOCAL_CERT = 0x1,
*   SEC_PKI_VERIFY_PARAM = 0x2,
*   SEC_PKI_ALL_LOCAL_CERT = 0x4,
*   SEC_PKI_DFLT_PRE_SHARED_CERT = 0x8,
*   SEC_PKI_ALL_PRE_SHARED_CERT = 0x10
* }SEC_PKI_SYNC_TYPE_E;
* @endcode
* 
* @par Description
* Indicates the parameters to be considered from context to object.
* 
* @datastruct SEC_PKI_DFLT_LOCAL_CERT Default local cert to be 
* taken from context.
* @datastruct SEC_PKI_VERIFY_PARAM Verify parameter to be 
* taken from context.
* @datastruct SEC_PKI_ALL_LOCAL_CERT Default and local cert to be 
* taken from context.
* @datastruct SEC_PKI_DFLT_PRE_SHARED_CERT Default pre-shared cert 
* to be taken from context.
* @datastruct SEC_PKI_ALL_PRE_SHARED_CERT Default and all other pre-shared  
* cert to be taken from context.
*/

typedef enum
{
    SEC_PKI_DFLT_LOCAL_CERT = 0x1,
    SEC_PKI_VERIFY_PARAM = 0x2,
    SEC_PKI_ALL_LOCAL_CERT = 0x4,
    SEC_PKI_DFLT_PRE_SHARED_CERT = 0x8,
    SEC_PKI_ALL_PRE_SHARED_CERT = 0x10
} SEC_PKI_SYNC_TYPE_E;



/* PKI Option Flags */
/**
* @defgroup SEC_PKI_OPTIONS_E
* @ingroup Enums
* @par Description
* Flags indicating PKI options.
* @par Prototype
* @code
* typedef enum
* {
*    SEC_PKI_IGNORE_PVT_KEY_LOAD      = 0x00000001
* }SEC_PKI_OPTIONS_E;
* @endcode
* @datastruct SEC_PKI_IGNORE_PVT_KEY_LOAD Loads only the local certificate 
* ignoring the privatekey.
*/
typedef enum
{
    SEC_PKI_IGNORE_PVT_KEY_LOAD      = 0x00000001
}SEC_PKI_OPTIONS_E;



/**
* @defgroup SEC_PKI_DATA_BUF_S
* @ingroup Structures
* @par Description
* Data buffer is used to hold the generated certificate request data.
* @par Prototype
* @code
* typedef struct stDataBuf
* {
*    char *buf;
*    size_t len;
* }SEC_PKI_DATA_BUF_S;
* @endcode
* @datastruct buf Holds the generic data depending on the type of
* certificate request.
* @datastruct len Length of the data.
*/

/* Data buffer */
typedef struct stDataBuf
{
    /*Pointer to character data*/
    char *buf;

    /*Length of the data*/
    size_t len;
}SEC_PKI_DATA_BUF_S;

/**
* @defgroup SEC_PKI_CTX_S
* @ingroup Structures
* @par Description
* This structure holds the common configurations and
* is the common repository for PKI based authentication.
* @par Prototype
* @code
* typedef struct stPKICtx SEC_PKI_CTX_S;
* @endcode
*
*/
typedef struct stPKICtx SEC_PKI_CTX_S;

/**
* @defgroup SEC_PKI_OBJ_S
* @ingroup Structures
* @par Description
* This structure holds the session configuration and
* is the additional repository for a PKI based authentication. 
* @par Prototype
* @code
* typedef struct stPKIObj SEC_PKI_OBJ_S;
* @endcode
*
*/
typedef struct stPKIObj SEC_PKI_OBJ_S;

/* error related to certificate chain validation */

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




#define     X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT        2
#define     X509_V_ERR_UNABLE_TO_GET_CRL            3
#define     X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE 4
#define     X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE  5
#define     X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY   6
#define     X509_V_ERR_CERT_SIGNATURE_FAILURE       7
#define     X509_V_ERR_CRL_SIGNATURE_FAILURE        8
#define     X509_V_ERR_CERT_NOT_YET_VALID           9
#define     X509_V_ERR_CERT_HAS_EXPIRED         10
#define     X509_V_ERR_CRL_NOT_YET_VALID            11
#define     X509_V_ERR_CRL_HAS_EXPIRED          12
#define     X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD   13
#define     X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD    14
#define     X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD   15
#define     X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD   16
#define     X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT      18
#define     X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN        19
#define     X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY    20
#define     X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE  21
#define     X509_V_ERR_CERT_CHAIN_TOO_LONG          22
#define     X509_V_ERR_CERT_REVOKED             23
#define     X509_V_ERR_INVALID_CA               24
#define     X509_V_ERR_PATH_LENGTH_EXCEEDED         25
#define     X509_V_ERR_INVALID_PURPOSE          26
#define     X509_V_ERR_CERT_UNTRUSTED           27
#define     X509_V_ERR_CERT_REJECTED            28

//Error in comparing certificate not before field
#define     X509_V_ERR_ERROR_IN_CMP_CERT_NOT_BEFORE_FIELD   44

//Error in comparing certificate not after field
#define     X509_V_ERR_ERROR_IN_CMP_CERT_NOT_AFTER_FIELD    45

//Error in comparing CRL this update field
#define     X509_V_ERR_ERROR_IN_CMP_CRL_THIS_UPDATE_FIELD   46

//Error in comparing CRL next update field
#define     X509_V_ERR_ERROR_IN_CMP_CRL_NEXT_UPDATE_FIELD   47

/* These are 'informational' when looking for issuer cert */
#define     X509_V_ERR_SUBJECT_ISSUER_MISMATCH      29
#define     X509_V_ERR_AKID_SKID_MISMATCH           30
#define     X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH      31
#define     X509_V_ERR_KEYUSAGE_NO_CERTSIGN         32
#define     X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER     33
#define     X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION     34
#define     X509_V_ERR_KEYUSAGE_NO_CRL_SIGN         35
#define     X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION 36
#define     X509_V_ERR_INVALID_NON_CA           37
#define     X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED       38
#define     X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE    39
#define     X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED   40

#define     X509_V_ERR_INVALID_EXTENSION            41
#define     X509_V_ERR_INVALID_POLICY_EXTENSION     42
#define     X509_V_ERR_NO_EXPLICIT_POLICY           43
#define     X509_V_ERR_DIFFERENT_CRL_SCOPE     44
#define     X509_V_ERR_CRL_PATH_VALIDATION_ERROR    45

#define     X509_V_ERR_NO_CERT_IN_CA_STORE 101

#ifndef __SEC_PKI_NO_OCSP__

/* The OCSP Valchain error when Unable to Find the OCSP response */
#define     X509_V_ERR_UNABLE_TO_FIND_OCSP_RESPONSE               102

/* The OCSP Valchain error when unable to find the OCSP responder certificate */
#define     X509_V_ERR_UNABLE_TO_FIND_OCSP_RESPONDER              103

/* The OCSP Valchain error when the response is found to be unknown */
#define     X509_V_ERR_UNKNOWN_OCSP_RESPONSE                      104

/* The OCSP Valchain error when Responder validation failed */
#define     X509_V_ERR_OCSP_RESPONDER_VALIDATION_FAILED           105

/* The OCSP Valchain error when Responder validation with CRL failed */
#define     X509_V_ERR_OCSP_RESPONDER_VALIDATION_WITH_CRL_FAILED  106

/* The OCSP Valchain error when Responder validation with time failed */
#define     X509_V_ERR_OCSP_RESPONDER_VALIDATION_WITH_TIME_FAILED 107

/* The OCSP Valchain error when the response is found to be not yet valid */
#define     X509_V_ERR_OCSP_RESP_NOT_YET_VALID                    108

/* The OCSP Valchain error when the response is found to be expired */
#define     X509_V_ERR_OCSP_RESP_HAS_EXPIRED                      109

/* The OCSP Valchain error when error happended in checking This Update field */
#define     X509_V_ERR_ERROR_IN_OCSP_RESP_THIS_UPDATE_FIELD       110

/* The OCSP Valchain error when error happended in checking Next Update field */
#define     X509_V_ERR_ERROR_IN_OCSP_RESP_NEXT_UPDATE_FIELD       111

/* The OCSP Valchain error when Signature Verification Failed */
#define     X509_V_ERR_OCSP_SIGN_VERIFY_FAILED                    112

/* The OCSP Valchain error when the certificate is found to be revoked 
using OCSP response*/
#define     X509_V_ERR_CERT_REVOKED_BY_OCSP_RESP                          113

#endif

//This struct contains the length fields from the cert extensions
typedef struct stPKICertLengthFields
{
    // Path length that has to be obtained from the Basic constraint
    // extension for certificate chain validation. 
    SEC_INT32 iPathLen;

    // Length of the Proxy certificate 
    SEC_UINT ulExProxyPathLen;

} SEC_PKI_X509_CERT_EXT_LENGTH_FIELD_S;

//This struct contains the flag fields from the cert extensions
typedef struct stPKICertFlagFields
{
    // Used to stored the flags to indicate whether the certificate is
    // CA certificate along with other flag values used for certificate
    // chain validation 
    SEC_UINT ulExtnFlags;

    // To store extended key usage details 
    SEC_UINT uiExtKeyUsage;

    // To store key usage of the certificate 
    SEC_UINT uiKeyusage;

} SEC_PKI_X509_CERT_EXT_FLAG_FIELD_S;

//This struct contains the key id fields from the cert extensions
typedef struct stPKICertKeyIdFields
{
    // Subject key identifier extension that contains the hash of the
    // public key 
    SEC_AsnOcts_S *pstSKID;

    // Authorioty key identifier extension that contains the hash of the
    // public key of the issuer along with the name of the certificate
    // issuer and the serial number of the issuer 
    X509_AKID_S* pstAKID;

} SEC_PKI_X509_CERT_EXT_KEYID_FIELD_S;

//This struct contains the crypto related fields from the cert extensions
typedef struct stPKICertCryptFields
{
    // Digest of the Certificate 
    SEC_UCHAR aucSha1Hash[20];

    // This is used to hold the public key of the certificate 
    SEC_PKEY_S* pstPublicKey;

} SEC_PKI_X509_CERT_EXT_CRYPT_FIELD_S;


//This structure contains all the fields from the certificate extension
typedef struct stPKICertExtnFields
{

    //This struct contains the length fields from the cert extensions
    SEC_PKI_X509_CERT_EXT_LENGTH_FIELD_S extLengths;

    //This struct contains the flag fields from the cert extensions
    SEC_PKI_X509_CERT_EXT_FLAG_FIELD_S extFlags;

    //This struct contains the key id fields from the cert extensions
    SEC_PKI_X509_CERT_EXT_KEYID_FIELD_S extKeyId;

    //This struct contains the crypto related fields from the cert extensions
    SEC_PKI_X509_CERT_EXT_CRYPT_FIELD_S extCrypt;

} SEC_PKI_X509_CERT_EXT_FIELD_S;

//structure holds the certificate as well as some extension fields
typedef struct stPKICertExtnData
{
    // Certificate for which the following certificate chain information
    // has to be exytracted from the extension fields 
    X509_CERT_S* pstCert;
    
    // Flag to indicate whether the certificate is valid 
    SEC_INT iValid;

    //structure containing the extensions of certificates
    SEC_PKI_X509_CERT_EXT_FIELD_S extCertFields;

    // Value indicates number of objects that are referring to this
    // structure
    SEC_INT iReferences;

} SEC_PKI_X509_CERT_EXTENDED_S;

#endif // IPSI_SEC_NO_PKI

#ifdef __cplusplus
}
#endif

#endif /*__SEC_PKI_DEF_H__*/


