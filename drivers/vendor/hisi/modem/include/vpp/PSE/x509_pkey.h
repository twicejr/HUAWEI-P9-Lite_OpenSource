/*
                                                                              
                Copyright 2003, Huawei Technologies Co. Ltd.                  
                            ALL RIGHTS RESERVED                               
                                                                              
------------------------------------------------------------------------------
                                                                              
                              sec_pkixkey.h                                   
                                                                              
  Project Code: SeCert                                                        
   Module Name: Common Module                                                 
  Date Created: 2005-07-17                                                    
        Author: Jimmy Bahuleyan                                               
   @brief: Contains prototypes for the encode - decode functions for     
				converting PKEY struct to DER (as per pkix1alg88) and back     
                                                                                                                                             
                                                                              
*/

#include "ipsi_pse_build_conf.h"

#ifndef	_SEC_PKIXKEY_H
#define	_SEC_PKIXKEY_H

#include "sec_crypto.h"
#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */


/** @defgroup x509_pkey
* This section contains the x509_pkey Functions.
*/




/** @defgroup x509_pkeyFunctions
* @ingroup x509_pkey
* This section contains the x509_pkey Functions.
*/

/**
* @defgroup SEC_encodePrivKey
* @ingroup x509_pkeyFunctions
* @par Prototype
* @code
* SEC_UCHAR* SEC_encodePrivKey ( SEC_PKEY_S* pstKey, SEC_UINT32* pulLen);
* @endcode
* 
* @par Purpose
* To encode a given PKEY struct to the ASN struct in pkix1alg88 key struct has a private key.
* 
* @par Description
* This function encodes a given PKEY struct to the ASN struct in pkix1alg88
* key struct has a private key.
* @param[in] pstKey Key to be encoded [N/A]
* @param[out] pulLen Length of the DER code generated in buffer [N/A]
* 
* @retval SEC_UCHAR* The buffer containing the DER code [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* If encode fails [NULL|N/A]
* 
* @par Dependency
* x509_pkey.h
* 
* @par Note
*\n
* The buffer allocated by this API for return value should be freed by using function "ipsi_free".
*
* @par Related Topics
* N/A
* 
*/

PSELINKDLL SEC_UCHAR* SEC_encodePrivKey (
    SEC_PKEY_S* pstKey,
    SEC_UINT32* pulLen);




/** 
* @defgroup SEC_encodePubKey
* @ingroup x509_pkeyFunctions
* @par Prototype
* @code
* SEC_UCHAR* SEC_encodePubKey( SEC_PKEY_S* pstKey, SEC_UINT32* pulLen);
* @endcode
* 
* @par Purpose
* To encode a given PKEY struct to the ASN struct in pkix1alg88 key struct has a public key.
*
* @par Description
* This function encodes a given PKEY struct to the ASN struct in pkix1alg88
* key struct has a public key.
*
* @param[in] pstKey Key to be encoded [N/A]
* @param[out] pulLen Length of the DER code generatedin buffer [N/A]
* 
* @retval SEC_UCHAR* The buffer containing the DER code [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* If encode fails [NULL|N/A]
* 
* @par Dependency
* x509_pkey.h
* 
* @par Note
*\n
* The buffer allocated by this API for return value should be freed by using function "ipsi_free".
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UCHAR* SEC_encodePubKey(
    SEC_PKEY_S* pstKey,
    SEC_UINT32* pulLen);




/**
* @defgroup SEC_decodePrivKey
* @ingroup x509_pkeyFunctions
* @par Prototype
* @code
* SEC_PKEY_S* SEC_decodePrivKey( SEC_UINT32 ulAlg, SEC_UCHAR* pucBuf, SEC_UINT32 ulLen, SEC_UINT32* pulLen);
* @endcode
* 
* @par Purpose
* To decode a PKEY struct given a ASN struct as per pkix1alg88 key struct has a private key.
* 
* @par Description
* This function decodes to a PKEY struct given a ASN struct as per pkix1alg88
* key struct has a private key.
*
* @param[in] ulAlg The algorithm type [N/A]
* @param[in] pucBuf The buffer containing the DER code [N/A]
* @param[in] ulLen Buffer length [N/A]
* @param[in] pulLen Bytes used in decoding [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval SEC_PKEY_S* The key struct [SEC_PKEY_S*|N/A]
* @retval SEC_PKEY_S* If decode fails [NULL|N/A]
* 
* @par Dependency
* x509_pkey.h
* 
* @par Note
*\n
* The key structure returned by this API should be freed by using function "CRYPT_PKEY_free".
* 
* @par Related Topics
* N/A
*/


/*This function is used by SSL. Hence the import define is added here*/
PSELINKDLL SEC_PKEY_S* SEC_decodePrivKey(
    SEC_UINT32 ulAlg,
    SEC_UCHAR* pucBuf,
    SEC_UINT32 ulLen,
    SEC_UINT32* pulLen);



/**
* @defgroup SEC_decodePubKey
* @ingroup x509_pkeyFunctions
* @par Prototype
* @code
* SEC_PKEY_S* SEC_decodePubKey( SEC_UINT32 ulAlg, SEC_UCHAR* pucBuf, SEC_UINT32 ulLen, SEC_UINT32* pulLen);
* @endcode
* 
* @par Purpose
* To decode a PKEY struct given a ASN struct as per pkix1alg88
* key struct has a public key.
* 
* @par Description
* This function decodes to a PKEY struct given a ASN struct as per pkix1alg88
* key struct has a public key.
*
* @param[in] ulAlg The algorithm type [N/A]
* @param[in] pucBuf The buffer containing the DER code [N/A]
* @param[in] ulLen Buffer length [N/A]
* @param[in] pulLen Bytes used in decoding [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval SEC_PKEY_S* The key struct [SEC_PKEY_S*|N/A]
* @retval SEC_PKEY_S* If decode fails [NULL|N/A]
* 
* @par Dependency
* x509_pkey.h
* 
* @par Note
*\n
* The key structure returned by this API should be freed by using function "CRYPT_PKEY_free".
*
* @par Related Topics
* N/A
*/



PSELINKDLL SEC_PKEY_S* SEC_decodePubKey(
    SEC_UINT32 ulAlg,
    SEC_UCHAR* pucBuf,
    SEC_UINT32 ulLen,
    SEC_UINT32* pulLen);

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif	/* _SEC_PKIXKEY_H */
