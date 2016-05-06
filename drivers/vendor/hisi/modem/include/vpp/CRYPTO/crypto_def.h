#ifndef _IPSI_CRYPTO_DEF_H
#define _IPSI_CRYPTO_DEF_H

#include "sec_crypto.h"
#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef  __cplusplus
extern "C" {
#endif


/* Use the below Algorithm Ids to identify algorithms */

#define ALGID_BASE          (CID_RC4 - 1)
#define ALGID_SYMM_BASE     ALGID_BASE

#define ALGID_SYMM_MAX      CID_KASUMI_CFB
#define ALGID_ASYM_BASE     (CID_RSA - 1)
#define ALGID_ASYM_MAX      CID_ECDH
#define ALGID_HASH_BASE     (CID_MD5 - 1)
#define ALGID_HASH_MAX      CID_SHA512
#define ALGID_HMAC_BASE     (CID_HMAC_MD5 - 1)
#define ALGID_HMAC_MAX      CID_HMAC_SHA512
#define ALGID_SIGN_BASE     (CID_MD5WITHRSA - 1)
#define ALGID_SIGN_MAX      CID_SHA512WITHRSAENCRYPTION
#define ALGID_MAX           ALGID_SIGN_MAX


/* Get index of algorithm from id */
#define CRYPT_SYMM_ALG_IDX(x)   (CRYPT_MASK_PAD(x) - ALGID_SYMM_BASE)
#define CRYPT_ASYM_ALG_IDX(x)   ((x) - ALGID_ASYM_BASE) 
#define CRYPT_HASH_ALG_IDX(x)   ((x) - ALGID_HASH_BASE) 
#define CRYPT_HMAC_ALG_IDX(x)   ((x) - ALGID_HMAC_BASE) 
#define CRYPT_PRNG_ALG_IDX(x)   ((x) - ALGID_PRNG_BASE) 

/* Total number of symmetric algorithms */
#define SYMMALG_COUNT       CID_KASUMI_CFB - ALGID_SYMM_BASE

/* Macro to set the sign option in asymmetric algorithm the parameter 'a' must be an l-value */
#define CRYPT_SET_SIGN_OPTION(a,m) ((a) |= (((SEC_UINT32)(m))<<16))

/* Macro to get the sign option in asymmetric algorithm the parameter 'a' must be an l-value */
#define CRYPT_GET_SIGN_OPTION(a)   (((SEC_UINT32)(a)) >> 16) 

/* Macro to reset the sign option in asymmetric algorithm the parameter 'a' must be an l-value */
#define CRYPT_RESET_SIGN_OPTION(a) ((a) &= 0x0000ffff) 

/*Macro for setting the no truncation mode for hash while doing the signature using the EC keys */
#define SEC_EC_NO_TRUNCATION 1

/** @defgroup crypto_def
* This section contains the crypto_def Functions
*/


/** @defgroup crypto_defFunctions
* @ingroup crypto_def
* This section contains the crypto_def Functions.
*/

/**
* @defgroup crypt_cvtInt
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 crypt_cvtInt (
* SEC_BIGINT_S* pN,
* SEC_INT8* pI,
* SEC_UINT32 uiLen);
* @endcode
*
* @par Purpose
* To convert machine representation of big integer to octet form
*
* @par Description
* This function converts machine representation of big integer to octet form.
*
* @param[in] pN Big integer input [N/A]
* @param[in] uiLen Length of the octet structure [N/A]
* @param[out] pI The output octet form [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 In case of error in library initialization( if ssx31b enabled). [SEC_ERROR|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 crypt_cvtInt (
    SEC_BIGINT_S* pN,
    SEC_INT8* pI,
    SEC_UINT32 uiLen);

/**
* @defgroup crypt_cvtOcts
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 crypt_cvtOcts (
* SEC_BIGINT_S* pN,
* SEC_INT8* pI,
* SEC_UINT32 uiILen);
* @endcode
*
* @par Purpose
* To convert octets to machine representation of big integer.
*
* @par Description
* This function converts octets to machine representation of big integer.
*
* @param[in] pI Octet input [N/A]
* @param[in] uiLen Length of the octet structure [N/A]
* @param[out] pN Big integer form output [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 In case of error in library initialization(if ssx31b enabled). [SEC_ERROR|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 crypt_cvtOcts (
    SEC_BIGINT_S* pN,
    SEC_INT8* pI,
    SEC_UINT32 uiILen);

/**
* @defgroup crypt_cmpECPoint
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT crypt_cmpECPoint (
* EC_POINT_S* pA,
* EC_POINT_S* pB);
* @endcode
*
* @par Purpose
* To compare two elliptic curve points.
*
* @par Description
* This function is used to compare two elliptic curve points.
*
* @param[in] pA Elliptic curve point A [N/A]
* @param[in] pB Elliptic curve point B [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT If both points are same [0|N/A]
* @retval SEC_UINT If the points are not the same [Greater than zero or Less than zero|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT crypt_cmpECPoint (
    EC_POINT_S* pA,
    EC_POINT_S* pB);

/**
* @defgroup crypt_copyECPoint
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT crypt_copyECPoint (
* EC_POINT_S* pA,
* EC_POINT_S* pB);
* @endcode
*
* @par Purpose
* To copy an elliptic point from one to another.
*
* @par Description
* This function is used to copy an elliptic point from one to another.
*
* @param[in] pA Source Elliptic curve point [N/A]
* @param[out] pB Destination Elliptic curve point, copy of A [N/A]
*
* @retval SEC_UINT On success [SEC_SUCCESS|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT crypt_copyECPoint (
    EC_POINT_S* pA,
    EC_POINT_S* pB);

/**
* @defgroup crypt_ecCmpParam
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 crypt_ecCmpParam (
* EC_PARA_S* pSrc,
* EC_PARA_S* pDst);
* @endcode
*
* @par Purpose
* To compare elliptic curve parameters.
*
* @par Description
* This function is used to compare elliptic curve parameters.
*
* @param[in] pSrc The Source Elliptic curver parameter [N/A]
* @param[in] pDst The Destination Elliptic curve parameter [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 If both the Elliptic curve parameters are the same. [0|N/A]
* @retval SEC_UINT32 If the Parameters are not the same. [Less than zero or Greater than zero|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 crypt_ecCmpParam (
    EC_PARA_S* pSrc, 
    EC_PARA_S* pDst);

/* This function is used by SSL, hence import define added */
/**
* @defgroup crypt_freeCtx
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_VOID crypt_freeCtx(CRYPT_CTX* pCtx);
* @endcode
*
* @par Purpose
* To free the Ctx structure.
*
* @par Description
* This function is used to free the Ctx structure.
*
* @param[in] pCtx The CRYPT_CTX structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_VOID crypt_freeCtx(CRYPT_CTX* pCtx);

/**
* @defgroup CRYPT_encryptUpdate_ssl
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_encryptUpdate_ssl (
* CRYPT_CTX     ctx,
* SEC_UCHAR*    pucPlainText,
* SEC_UINT32    ulPlainLen,
* SEC_UCHAR*    pucCipherText,
* SEC_UINT32*   pulCLen);
* @endcode
*
* @par Purpose
* To encrypt plaintext to get ciphertext.
* 
* @par Description
* This function uses the initialized symmetric context to encrypt plaintext to get ciphertext.
* It uses symmetric encryption. This can be used only by SSL for perf improvement.
* 
* @param[in] ctx The context to be used. [N/A]
* @param[in] pucPlainText Plaintext to be encrypted. [N/A]
* @param[in] ulPlainLen Length of plaintext. [N/A]
* @param[out] pucCipherText Encrypted ciphertext. [N/A]
* @param[out] pulCLen Length of encrypted ciphertext. [N/A]
* 
* @retval SEC_UINT32 Successful return. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Other error. [SEC_ERR|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_encryptUpdate_ssl (
    CRYPT_CTX       ctx,
    SEC_UCHAR*      pucPlainText,
    SEC_UINT32      ulPlainLen,
    SEC_UCHAR*      pucCipherText,
    SEC_UINT32*     pulCLen);

/**
* @defgroup CRYPT_decryptUpdate_ssl
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_decryptUpdate_ssl (
* CRYPT_CTX     ctx,
* SEC_UCHAR*    pucCipherText,
* SEC_UINT32    ulCLen,
* SEC_UCHAR*    pucPlainText,
* SEC_UINT32*   pulPLen);
* @endcode
*
* @par Purpose 
* To decrypt cipher text to get plain text.
* 
* @par Description
* This function uses the initialized symmetric context to decrypt cipher text to get plaintext. It uses symmetric 
* decryption. This can be used only by SSL for perf improvement.
* 
* @param[in] ctx The context to be used. [N/A]
* @param[in] pucCipher Text Encrypted cipher text. [N/A]
* @param[in] ulCLen Cipher text length. [N/A]
* @param[out] pucPlainText Decrypted plain text. [N/A]
* @param[out] pulPLen Length of decrypted plain text. [N/A]
* 
* @retval SEC_UINT32 Successful return. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Other error. [SEC_ERR|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_decryptUpdate_ssl (
    CRYPT_CTX       ctx,
    SEC_UCHAR*      pucCipherText,
    SEC_UINT32      ulCLen,
    SEC_UCHAR*      pucPlainText,
    SEC_UINT32*     pulPLen);

/**
* @defgroup CRYPT_setIV
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_setIV(CRYPT_CTX ctx, SEC_UCHAR *pucIV,SEC_UINT32 ulIVLen);
* @endcode
*
* @par Purpose
* To set the IV for Block Cipher context.
* 
* @par Description
* This function is used to set the IV for Block Cipher context.
* 
* @param[in] ctx Context for block cipher. [N/A]
* @param[in] pucIV Intialize vector for operation mode. [N/A]
* @param[in] ulIVLen Intialize vector length. [N/A]
* @param[out] ctx Context for block cipher. [N/A]
* 
* @retval SEC_UINT32 Successfully set IV to context. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid context. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_setIV(CRYPT_CTX ctx, SEC_UCHAR *pucIV,SEC_UINT32 ulIVLen);

/**
* @defgroup CRYPT_sign_ssl
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_sign_ssl(
* SEC_PKEY_S*      pKey,
* SEC_UCHAR*       pucData,
* SEC_UINT32       ulDataLen,
* SEC_UCHAR*       pucSign,
* SEC_UINT32*      pulSignLen);
* @endcode
*
* @par Purpose
* To sign SSL where hash is not computed.
* 
* @par Description
* The CRYPT_sign_ssl function is used for SSL signing where hash is not computed.
* 
* @param[in] pKey The private key. [N/A]
* @param[in] pucData Input data. [N/A]
* @param[in] ulDataLen Input data length. [N/A]
* @param[out] pucSign The signature. [N/A]
* @param[out] pulSignLen The sign length. [N/A]
* 
* @retval SEC_UINT32 On Success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation failure. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key. [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Invalid key. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Key size not supported. [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Library not initialized. [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure [SEC_ERR|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* This is a deprecated API and recommended to use CRYPT_signData
*
* @par Related Topics
* None
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_sign_ssl(
    SEC_PKEY_S*     pKey,
    SEC_UCHAR*      pucData,
    SEC_UINT32      ulDataLen,
    SEC_UCHAR*      pucSign,
    SEC_UINT32*     pulSignLen);

/**
* @defgroup CRYPT_verify_ssl
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_verify_ssl(
* SEC_PKEY_S*      pKey,
* SEC_UCHAR*       pucDta,
* SEC_UINT32       ulDtaLen,
* SEC_UCHAR*       pucSig,
* SEC_UINT32       ulSigLen);
* @endcode
*
* @par Purpose
* To verify SSL where hash is not computed.
* 
* @par Description
* The CRYPT_verify_ssl function is used for SSL verification where hash is not computed.
* 
* @param[in] pKey The public key. [N/A]
* @param[in] pucData Input data. [N/A]
* @param[in] ulDataLen Input data length. [N/A]
* @param[in] pucSign The signature. [N/A]
* @param[in] pulSignLen The sign length. [N/A]
* 
* @retval SEC_UINT32 On Success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid key. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Memory allocation failure. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key. [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Key size not supported. [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Library not initialized. [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure. [SEC_ERR|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* This is a deprecated API and recommended to use CRYPT_verifyData.
*
* @par Related Topics
* None
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_verify_ssl(
    SEC_PKEY_S*     pKey,
    SEC_UCHAR*      pucDta,
    SEC_UINT32      ulDtaLen,
    SEC_UCHAR*      pucSig,
    SEC_UINT32      ulSigLen);

/**
* @defgroup SEC_setLogFilePointer
* @ingroup sec_logFunctions
* @par Prototype
* @code
* SEC_VOID SEC_setLogFilePointer(SEC_FILE_F *pFile);
* @endcode
*
* @par Purpose
* To update the global log file pointer.
* 
* @par Description
* The SEC_setLogFilePointer function is used for updating the global log file pointer.
* 
* @param[in] pFile The file descriptor. [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval SEC_VOID [N/A]
*
* @par Dependency
* sec_log.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID SEC_setLogFilePointer(SEC_FILE_F *pFile);


/**
* @defgroup CRYPT_signData
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_signData(SEC_PKEY_S *pKey, SEC_UCHAR *pucDta,
*                                 SEC_UINT32 ulDtaLen, SEC_UCHAR *pucSgn,
*                                 SEC_UINT32 *pulSgnLen, SEC_UINT32 ulAlgType);
* @endcode
*
* @par Purpose
* To sign data where hash is not computed.
* 
* @par Description
* The CRYPT_signData function is used for data signing where hash
* is not computed and if the ulAlgType is passed apart from ALGID_MD5_SHA1
* then the hash info will be considered for the signature.
* 
* @param[in] pKey The private key. [N/A]
* @param[in] pucData Input data. [N/A]
* @param[in] ulDataLen Input data length. [N/A]
* @param[in] ulAlgType Hash algorithm. [N/A]
* @param[out] pucSign The signature. [N/A]
* @param[out] pulSignLen The sign length. [N/A]
* 
* @retval SEC_UINT32 On Success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid key. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Memory allocation failure. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key. 
* [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Key size not supported. [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Library not initialized. [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure. [SEC_ERR|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
*
* ulAlgType is required only for RSA Key. RSA signing uses RSA_PKCS1_PADDING method.
* SM2 Signing is not supported by this API.
*
* @par Related Topics
* None
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_signData(SEC_PKEY_S *pKey, SEC_UCHAR *pucDta,
                                  SEC_UINT32 ulDtaLen, SEC_UCHAR *pucSgn,
                                  SEC_UINT32 *pulSgnLen, SEC_UINT32 ulAlgType);

/**
* @defgroup CRYPT_verifyData
* @ingroup crypto_defFunctions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_verifyData(SEC_PKEY_S *pKey, SEC_UCHAR *pucDta,
*                                   SEC_UINT32 ulDtaLen, SEC_UCHAR *pucSig,
*                                   SEC_UINT32 ulSigLen, SEC_UINT32 ulAlgType);
* @endcode
*
* @par Purpose
* To verify data where hash is not computed.
* 
* @par Description
* The CRYPT_verifyData function is used for data verification where hash
* is not computed and if the ulAlgType is used apart from ALGID_MD5_SHA1
* then the hash info will be considered for the verification.
* 
* @param[in] pKey The private key. [N/A]
* @param[in] pucDta Input data. [N/A]
* @param[in] ulDtaLen Input data length. [N/A]
* @param[in] pucSign The signature. [N/A]
* @param[in] pulSignLen The sign length. [N/A]
* @param[in] ulAlgType Hash algorithm. [N/A]
* 
* @retval SEC_UINT32 On Success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Invalid key. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Memory allocation failure. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key. 
* [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Key size not supported. [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Library not initialized. [SEC_ERR_INITLIB|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 On Failure. [SEC_ERR|N/A]
*
* @par Dependency
* crypto_def.h
*
* @par Note
* SM2 Sign Verification is not supported by this API
*
* @par Related Topics
* None
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_verifyData(SEC_PKEY_S *pKey, SEC_UCHAR *pucDta,
                                    SEC_UINT32 ulDtaLen, SEC_UCHAR *pucSig,
                                    SEC_UINT32 ulSigLen, SEC_UINT32 ulAlgType);

/*
    Func Name:  CRYPT_signData_ex
*/

/** 
* @defgroup CRYPT_signData_ex
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_signData_ex(
* SEC_PKEY_S *pKey,
* SEC_UCHAR *pucDigest,
* SEC_UINT32 ulDigestLen,
* SEC_UCHAR *pucSig,
* SEC_UINT32 *pulSigLen,
* SEC_UINT32 ulSigAlgType,
* SEC_UINT32 ulRsaHashType);
* @endcode
*
* @par Purpose
* This function is used for data signing where hash is not computed.
* @par Description
* This function is used for data signing where hash is not computed.
* In RSA signing, hash info (hash OID) is considered for the following hash algorithms types.
*   ALGID_SHA1
*   ALGID_SHA256
*   ALGID_SHA384
*   ALGID_SHA512
*   ALGID_MD5
*   For ALGID_MD5_SHA1, hash info (hash OID) is not used.
*   For any other hash algorithm, signing will fail.
* For any signature algorithm other than RSA, hash algorithm type (ulRsaHashType) is ignored.
*
* @param[in] pKey The private key.
* @param[in] pucDigest Pointer to the hash value to sign i.e. digest operation has to be done
* before calling this API and the digest output should be passed.
* @param[in] ulDigestLen Length of the hash value
* @param[in] ulSigAlgType Signature algorithm to be used. The supported Algorithm ids are:
*   ALGID_SM2DSA
*   ALGID_RSA
*   ALGID_DSA
*   ALGID_ECDSA
* @param[in] ulRsaHashType Hash algorithm type to be used during RSA signing with RSA_PKCS1_PADDING method.
*   This parameter is ignored for signing algorithms other than RSA.
* @param[out] pucSig Buffer to hold the DER encoded signature
* @param[out] pulSigLen Pointer to the length of the returned signature
*
* @retval SEC_UINT32 On Success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid key. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Memory allocation failure. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Key size not supported. [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Mathematical operation failed. [SEC_ERR|N/A]
*
* @par Required Header File
* crypto_def.h
*
* @par Note
* -The size of the buffer pointed by pucSig should be atleast equal to the size
*   returned by the API CRYPT_PKEY_sign_size
* - If the application does not need that the hash will be truncated for the signatures using ECDSA or SM2DSA
*    then the application need to call CRYPT_SET_SIGN_OPTION(ulSigAlgType, SEC_EC_NO_TRUNCATION) before calling the 
*    CRYPT_signData_ex. The value of ulSigAlgType will be changed by the CRYPT_SET_SIGN_OPTION, so the
*    varibale should not be used with anyother API except CRYPT_signData_ex. The value of ulSigAlgType can be reset by
*    calling CRYPT_RESET_SIGN_OPTION(ulSigAlgType).
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_signData_ex(
    SEC_PKEY_S *pKey,
    SEC_UCHAR *pucDigest,
    SEC_UINT32 ulDigestLen,
    SEC_UCHAR *pucSig,
    SEC_UINT32 *pulSigLen,
    SEC_UINT32 ulSigAlgType,
    SEC_UINT32 ulRsaHashType);

/*
    Func Name:  CRYPT_verifyData_ex
*/

/** 
* @defgroup CRYPT_verifyData_ex
* @ingroup HLF High Level Functions
* @par Prototype
* @code
* SEC_UINT32 CRYPT_verifyData_ex(
* SEC_PKEY_S *pKey,
* SEC_UCHAR *pucDigest,
* SEC_UINT32 ulDigestLen,
* SEC_UCHAR *pucSig,
* SEC_UINT32 ulSigLen,
* SEC_UINT32 ulSigAlgType,
* SEC_UINT32 ulRsaHashType);
* @endcode
*
* @par Purpose
* This function is used for signature verification where hash is not computed.
* @par Description
* This function is used for signature verification where hash is not computed.
* In RSA sign verification, hash info (hash OID) is considered for the following hash algorithms types.
*   ALGID_SHA1
*   ALGID_SHA256
*   ALGID_SHA384
*   ALGID_SHA512
*   ALGID_MD5
*   For ALGID_MD5_SHA1, hash info (hash OID) is not used.
*   For any other hash algorithm type, sign verification will fail.
* For any signature algorithm type other than RSA, hash algorithm type (ulRsaHashType) is ignored.
*
* @param[in] pKey The private key.
* @param[in] pucDigest Pointer to the hash value
* @param[in] ulDigestLen Length of the hash value
* @param[in] ulSigAlgType Signature algorithm to be used. The supported Algorithm ids are:
*   ALGID_SM2DSA
*   ALGID_RSA
*   ALGID_DSA
*   ALGID_ECDSA
* @param[in] ulRsaHashType Hash algorithm type required for RSA verification using RSA_PKCS1_PADDING method.
*   This parameter is ignored for signing algorithms other than RSA.
* @param[in] pucSig Pointer to the DER encoded signature
* @param[in] ulSigLen Length of the DER encoded signature
*
* @retval SEC_UINT32 On Success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Invalid arguments. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Incorrect Algorithm ID. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid key. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 Memory allocation failure. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Key size not supported. [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Mathematical operation failed. [SEC_ERR|N/A]
*
* @par Required Header File
* crypto_def.h
*
* @par Note
* \n
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 CRYPT_verifyData_ex(
    SEC_PKEY_S *pKey,
    SEC_UCHAR *pucDigest,
    SEC_UINT32 ulDigestLen,
    SEC_UCHAR *pucSig,
    SEC_UINT32 ulSigLen,
    SEC_UINT32 ulSigAlgType,
    SEC_UINT32 ulRsaHashType);


#ifdef  __cplusplus
}
#endif

#endif /* _IPSI_CRYPTO_DEF_H */


