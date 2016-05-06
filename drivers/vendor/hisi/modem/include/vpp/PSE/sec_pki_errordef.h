/******************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: sec_pki_errordef.h
Version: 1
Author:  Mallesh
Creation Date: 2009-4-24
Description: This file declares the error
codes

Function List:


History:<author>   <date>          <desc>
              
*********************************************/
#include "ipsi_pse_build_conf.h"

#ifndef __SEC_PKI_ERROR_DEF_H__
#define __SEC_PKI_ERROR_DEF_H__


#ifdef  __cplusplus
extern "C" {
#endif

#define SEC_PKI_ERR_RANGE 1000
    
#define SEC_PKI_ERR_INIT 1000
    
// System Error: Include mem allocation failure,socket  closed , 
// file open error......
#define SEC_PKI_ERR_SYSTEM_INIT (SEC_PKI_ERR_INIT + 1)

//MAX Total System error limit
#define SEC_PKI_ERR_SYSTEM_LIMIT \
    (SEC_PKI_ERR_SYSTEM_INIT + SEC_PKI_ERR_RANGE - 1)

#define SEC_PKI_ERR_CONTEXT_OBJECT_INIT (SEC_PKI_ERR_SYSTEM_LIMIT + 1)

//MAX Total Context error limit
#define SEC_PKI_ERR_CONTEXT_OBJECT_LIMIT \
(SEC_PKI_ERR_CONTEXT_OBJECT_INIT + SEC_PKI_ERR_RANGE - 1)


#define SEC_PKI_ERR_COMMON_INIT (SEC_PKI_ERR_CONTEXT_OBJECT_LIMIT + 1)

//MAX Total Common error limit
#define SEC_PKI_ERR_COMMON_LIMIT \
(SEC_PKI_ERR_COMMON_INIT + SEC_PKI_ERR_RANGE - 1)

#define SEC_PKI_ERR_LOAD_CERT_KEY_INIT (SEC_PKI_ERR_COMMON_LIMIT + 1)

//MAX Total cert error limit
#define SEC_PKI_ERR_LOAD_CERT_KEY_LIMIT \
(SEC_PKI_ERR_LOAD_CERT_KEY_INIT + SEC_PKI_ERR_RANGE - 1)


#define SEC_PKI_ERR_CRL_INIT (SEC_PKI_ERR_LOAD_CERT_KEY_LIMIT + 1)

//Max Total crl error limit
#define SEC_PKI_ERR_CRL_LIMIT \
(SEC_PKI_ERR_CRL_INIT + SEC_PKI_ERR_RANGE - 1)

#define SEC_PKI_ERR_OCSP_INIT (SEC_PKI_ERR_CRL_LIMIT + 1)

//Max Total ocsp error limit
#define SEC_PKI_ERR_OCSP_LIMIT \
(SEC_PKI_ERR_OCSP_INIT + SEC_PKI_ERR_RANGE - 1)


//Syetem errors
typedef enum SEC_PKI_system_errors
{    
    // Malloc fails
    SEC_PKI_ERR_MALLOC_FAILED = SEC_PKI_ERR_SYSTEM_INIT,

    // crypt memory allocation fails
    SEC_PKI_ERR_CRYPT_NEW_FAILED,

    // crypt copy fails
    SEC_PKI_ERR_CRYPT_COPY_FAILED,

    // crypt copy param fails
    SEC_PKI_ERR_CRYPT_COPY_PARAM_FAILED,

    // Realloc fails
    SEC_PKI_ERR_REALLOC_FAILED,

    SEC_PKI_ERR_MEMCPY_FAILED,

    SEC_PKI_ERR_MEMSET_FAILED,

    SEC_PKI_ERR_MEMMOVE_FAILED,

    // Please add all error between init and max
    SEC_PKI_ERR_SYSTEM_MAX
    
}SEC_PKI_SYSTEM_ERRORS;


//enum to  hold the context and object errors
typedef enum SEC_PKI_context_object_errors
{
    // create local store fail
    SEC_PKI_ERR_LOCALSTORE_CREATION_FAILED = SEC_PKI_ERR_CONTEXT_OBJECT_INIT,

    // ctx/obj name is not set
    SEC_PKI_ERR_NAME_NOT_SET,

    // buf length is not sufficient
    SEC_PKI_ERR_BUF_LEN_NOT_SUFFICIENT,

    // Creation of SEC_List_S Failed
    SEC_PKI_ERR_CREATE_LIST_FAILED,

    // Add to SEC_List_S Failed
    SEC_PKI_ERR_ADD_TO_LIST_FAILED,

    // cert chain validate fail
    SEC_PKI_ERR_VALIDATE_CERT_CHAIN,

    // In use cert not set in the object
    SEC_PKI_ERR_INUSE_CERT_NOT_SET,

    // In use cert not set in the object
    SEC_PKI_ERR_VERIFY_DEPTH_NOT_SET,

    // Local store copy failed
    SEC_PKI_ERR_LOCALSTORE_COPY_FAILED,

    // copy preshared cert list failed
    SEC_PKI_ERR_PRESHARED_CERT_LIST_COPY_FAILED,

    SEC_PKI_ERR_CONTEXT_OBJECT_MAX

}SEC_PKI_CONTEXT_ERRORS_S;



//enum to  hold the context and object errors
typedef enum SEC_PKI_common_errors
{
    // Invalid arguments
    SEC_PKI_ERR_INVALID_ARGS = SEC_PKI_ERR_COMMON_INIT,

    // Input time is invalid (or) not supported
    SEC_PKI_ERR_INVALID_TIME,

    // No flag is set
    SEC_PKI_ERR_FLAG_NOT_SET,

    // Time is not set
    SEC_PKI_ERR_TIME_NOT_SET,

    // create lock fail
    SEC_PKI_ERR_CTX_LOCK_CREATION_FAILED,

    // Invalid flag value
    SEC_PKI_ERR_INVALID_FLAG,

    // certificate encoding failed
    SEC_PKI_ERR_CERT_ENCODING_FAILED,

    // certificate decoding failed
    SEC_PKI_ERR_CERT_DECODING_FAILED,

    // Unable to get algorithm id from certificate
    SEC_PKI_ERR_UNABLE_TO_GET_ALG_ID,

    // Unable to add certificate list to output chain
    SEC_PKI_ERR_UNABLE_TO_ADD_CERT_LIST,

    // Failed to create list
    SEC_PKI_ERR_FAILED_TO_CREATE_LIST,

    // Duplicate certificate creation failed
    SEC_PKI_ERR_DUP_CERT_CREATION_FAILED,

    // Adding certificate to the list failed
    SEC_PKI_ERR_ADD_CERT_TO_LIST_FAILED,

    // Adding certificate list to chain failed
    SEC_PKI_ERR_ADD_CERT_LIST_TO_CHAIN_FAILED,

    // No matching certificate chain found
    SEC_PKI_ERR_NO_MATCH_CERT_CHAIN,

    // Invalid input certificate chain list
    SEC_PKI_ERR_INVALID_LIST,

    // Not an end entity certificate
    SEC_PKI_ERR_NOT_END_ENTITY_CERT,

    // No matching hash found
    SEC_PKI_ERR_NO_MATCHING_HASH,

    // Failed to add to list
    SEC_PKI_ERR_FAILED_TO_ADD_TO_LIST,

    // Encoding of the subject name failed
    SEC_PKI_ERR_ENCODE_SUBJECT_NAME_FAILED,

    // CA request list is empty
    SEC_PKI_ERR_CA_REQ_LIST_EMPTY,

    // No issuer found
    SEC_PKI_NO_ISSUER_FOUND,

    // No matching subject name found
    SEC_PKI_ERR_NO_MATCHING_SUB_NAME,

    // Decoding of Name Failed
    SEC_PKI_ERR_DECODE_NAME_FAILED,

    // No end entity certificate found 
    SEC_PKI_ERR_FAILED_TO_FIND_END_ENTITY_CERT,

    // Certificate chain could not formed
    SEC_PKI_ERR_CERT_CHAIN_COULD_NOT_BE_FORMED,

    // End entity list could not be formed
    SEC_PKI_ERR_END_ENTITY_LIST_COULD_NOT_BE_FORMED,

    // No local certificates found in the store
    SEC_PKI_ERR_NO_LOCAL_CERTS,

    // Creation of extended certificate failed
    SEC_PKI_ERR_EXTENDED_CERT_CREATION_FAILED,

    // Verification in terms of time failed.
    SEC_PKI_ERR_VALIDITY_CHECK_FAILED,

    // Time verification of one certificate failed
    SEC_PKI_ERR_CERT_VERIFY_FAILED,

    // Time verification of crl failed
    SEC_PKI_ERR_CRL_VERIFY_FAILED,

    // Getting the system time failed
    SEC_PKI_ERR_SYS_TIME_FAILED,

    // Cross CA not found
    SEC_PKI_ERR_CROSS_CA_NOT_FOUND,

    // No matching hash found in cache
    SEC_PKI_NO_MATCHING_HASH_FOUND,

    // Issuer and Subject name not matching
    SEC_PKI_ERR_ISSUER_SUBJECT_NAME_MISMATCH,

    // Peer cache is empty
    SEC_PKI_ERR_PEER_CACHE_NO_CERT,

    // No pre shared default cert found in the preshared peer store
    SEC_PKI_ERR_NO_PRE_DHARED_DFLT_CERT,

    // No preshared certificates found in the store
    SEC_PKI_ERR_NO_PRE_SHARED_CERTS,

    // The Object Lock creation failed
    SEC_PKI_ERR_OBJ_LOCK_CREATION_FAILED,

    SEC_PKI_ERR_COMMON_MAX

}SEC_PKI_COMMON_ERRORS_S;

//enum to  hold the certificate errors
typedef enum SEC_PKI_cert_errors
{
    // decode failed
    SEC_PKI_ERR_DECODE_FAILED = SEC_PKI_ERR_LOAD_CERT_KEY_INIT,

    // store certificate failed
    SEC_PKI_ERR_STORE_CERTIFICATE_FAILED,

    // extract public key failed
    SEC_PKI_ERR_EXTRACT_PUBKEY_FAILED,

    // Unknown certificate type
    SEC_PKI_ERR_UNKNOWN_CERTIFICATE_TYPE,

    // no certificate
    SEC_PKI_ERR_NO_CERTIFICATE,

    // load from certificate buffer failed
    SEC_PKI_ERR_LOAD_CERT_BUFFER_FAILED,

    // load from certificate file failed
    SEC_PKI_ERR_LOAD_CERT_FILE_FAILED,

    // decode PFX failed
    SEC_PKI_ERR_DECODE_PFX_FAILED,

    // decrypt auth safe failed
    SEC_PKI_ERR_DECRYPT_AUTH_SAFE_FAILED,

    // Get bag from bag list failed
    SEC_PKI_ERR_GET_BAG_FROM_BAGLIST_FAILED,

    // Extract cert from safe bag failed
    SEC_PKI_ERR_EXTRCT_CERT_FRM_SAFEBAG_FAILED,

    // Verify PFX failed
    SEC_PKI_ERR_VERIFY_PFX_FAILED,

    // Extract auth safe from PFX failed
    SEC_PKI_ERR_EXTRACT_AUTHSAFE_FROM_PFX_FAILED,

    // Certificate copy failed
    SEC_PKI_ERR_DUP_CERTIFICATE_FAILED,

    // Read from certificate file failed
    SEC_PKI_ERR_READ_CERTIFICATE_FILE_FAILED,

    // Certificate already present
    SEC_PKI_ERR_CERT_ALREADY_PRESENT,
    
    // Digest Calculation Failed
    SEC_PKI_ERR_DIGEST_CALC_FAILED,
    
    // Save to Store Map Failed
    SEC_PKI_ERR_SAVE_TO_MAP_FAILED,
    
    // Insert to Store Map Failed
    SEC_PKI_ERR_INSERT_TO_MAP_FAILED,

    // public key under same issuer name present already
    SEC_PKI_ERR_SAME_PUBKEY_UNDER_ISSUER,

    // subject name under same issuer name present already
    SEC_PKI_ERR_SAME_SUBNAME_UNDER_ISSUER,

    // Certificate Duplication Failed
    SEC_PKI_CERT_DUP_FAILED,

    // Extended Certificate Duplication Failed
    SEC_PKI_ERR_DUPCERTEXTD_FAILED,

    // Get extended certificate from list failed
    SEC_PKI_ERR_GET_EXTENDED_CERT_LIST_FAILED,

    // Key size not supported
    SEC_PKI_ERR_KEY_SIZE_NOT_SUPPORTED,

    // Loading key failed
    SEC_PKI_ERR_LOAD_KEY_FILE_FAILED,

    // Reading key file failed
    SEC_PKI_ERR_READ_KEY_FILE_FAILED,

    // Loading key buffer failed
    SEC_PKI_ERR_LOAD_KEY_BUFFER_FAILED,

    // No private key loaded in the local store of context/object
    SEC_PKI_ERR_NO_PRVKEY,

    // certificate-key pair match failed
    SEC_PKI_ERR_CERT_KEY_MATCH_FAILED,

    // Storing certificate-key pair failed
    SEC_PKI_ERR_STORE_CERT_KEY_FAILED,

    // Input certificate is not matched with any context/object certificates
    SEC_PKI_CERT_NOT_MATCHED,

    // CA certificate already exists
    SEC_PKI_ERR_CA_ALREADY_EXISTS,

    // Loading End entity certificate not allowed in trust store
    SEC_PKI_ERR_END_ENTITY_CERT_NOT_ALLOWED,

    // Hash of the extended certificate failed
    SEC_PKI_ERR_CACHE_EXTEND_CERT_FAIL,

    // Creation of the extended certificate failed
    SEC_PKI_ERR_CREATE_EXTEND_CERT_FAIL,

    // Certificate check failed
    SEC_PKI_ERR_LOAD_CERT_CHECK_FAILED,
    
    // Adding privatekey in the list failed
    SEC_PKI_ERR_ADD_IN_LIST_FAILED,

    // Loading self sign certificate not allowed in cross CA store
    SEC_PKI_ERR_SELF_SIGN_CERT_NOT_ALLOWED,

    // CA not found
    SEC_PKI_ERR_CA_NOT_FOUND,

    // No CA certificate in trust store
    SEC_PKI_ERR_EMPTY_CA_LIST,

    // No cross CA certificate in trust store
    SEC_PKI_ERR_EMPTY_CROSS_CA_LIST,

    // Extracting certificate extension content failed
    SEC_PKI_ERR_EXTRACT_EXTN_CON_FAIL,

    // Extract CDP failed
    SEC_PKI_ERR_EXTRACT_CDP_FAIL,

    // Extracting certificate extension failed
    SEC_PKI_ERR_EXTRACT_EXTN_FAIL,

    // URI field is empty
    SEC_PKI_ERR_URI_FIELD_EMPTY,

    // Subject Name not in the certificate
    SEC_PKI_ERR_SUBJECT_NAME_NOT_FOUND,

    // Issuer Name not in the certificate
    SEC_PKI_ERR_ISSUER_NAME_NOT_FOUND,

    // Attibute not printable in the screen
    SEC_PKI_ERR_NOT_PRINTABLE_ON_SCREEN,

    // Attribute not found
    SEC_PKI_ERR_ATTIBUTE_NOT_FOUND,

    // Not a CA certificate
    SEC_PKI_ERR_NOT_CA_CERT,

    // Certificate not found
    SEC_PKI_ERR_CERT_NOT_FOUND,

    // No URL loaded in the local store of context/object
    SEC_PKI_ERR_NO_URL,

    // Certificate already loaded in the local store
    SEC_PKI_ERR_CERT_ALREADY_LOADED,

    // Matching certificate not found in the local store
    SEC_PKI_ERR_CERT_MATCH_NOT_FOUND,

    // Certificate signature verification failed
    SEC_PKI_ERR_SIGNATURE_VERIFY_FAILED,

    // Certificate already loaded in the preshared store
    SEC_PKI_ERR_PRESHARED_CERT_ALREADY_LOADED,

    // Encoding the certificate bundle failed
    SEC_PKI_ENCODE_CERT_BUNDLE_FAILED,

    // Decoding the certificate bundle failed
    SEC_PKI_DECODE_CERT_BUNDLE_FAILED,

    // No Certs are found in the bundle
    SEC_PKI_ERR_NO_CERTS_FOUND,    

    // Extracting content from extenstion failed
    SEC_PKI_ERR_EXTRACT_CONTENT_FROM_EXTN,

    // Corresponding Private key is not loaded
    SEC_PKI_ERR_PVT_KEY_NOT_LOADED,

    //IA5String content does not match with ASN.1 IA5String standard
    SEC_PKI_ERR_IA5STRING_NOT_MATCH_STANDARD,

    //UTF8String content does not match with ASN.1 UTF8String standard
    SEC_PKI_ERR_UTF8STRING_NOT_MATCH_STANDARD,

    //NumericString content does not match with ASN.1 NumericString standard
    SEC_PKI_ERR_NUMERICSTRING_NOT_MATCH_STANDARD,

    //PrintableString content does not match with ASN.1 PrintableString standard
    SEC_PKI_ERR_PRINTABLESTRING_NOT_MATCH_STANDARD,

    //VisibleString content does not match with ASN.1 VisibleString standard
    SEC_PKI_ERR_VISIBLESTRING_NOT_MATCH_STANDARD,

    SEC_PKI_ERR_LOAD_CERT_KEY_MAX

}SEC_PKI_CERT_ERRORS_S;



//enum to  hold the crl errors
typedef enum SEC_PKI_crl_errors
{
    // Reading of CRL file failed
    SEC_PKI_ERR_READ_CRL_FILE_FAILED = SEC_PKI_ERR_CRL_INIT,

    // Loading CRL buffer failed
    SEC_PKI_ERR_LOAD_CRL_BUFFER_FAILED,

    // Decoding of CRL failed
    SEC_PKI_ERR_CRL_DECODE_FAILED ,

    // Adding CRL to list failed
    SEC_PKI_ERR_ADD_CRL_TO_LIST_FAILED,

    // Same CRL already exist in CRL store
    SEC_PKI_ERR_CRL_ALREADY_EXIST,

    // Newer CRL already exist in CRL store
    SEC_PKI_ERR_NEWER_CRL_ALREADY_EXIST,

    // CRL time compare failed
    SEC_PKI_ERR_CRL_TIME_CHECK_FAILED,

    // CRL not found
    SEC_PKI_ERR_CRL_NOT_FOUND,

    // Failed to dup CRL
    SEC_PKI_ERR_FAILED_DUP_CRL,

    // No CRL in store
    SEC_PKI_ERR_EMPTY_CRL_LIST,

    // Hash Calculation for CRL failed
    SEC_PKI_ERR_CRL_HASH_CALC_FAILED,

    // No Crls are found in the bundle
    SEC_PKI_ERR_NO_CRLS_FOUND,

    // Base CRL for the cert is not present in the context
    SEC_PKI_ERR_BASE_CRL_FOR_CERT_NOT_PRESENT,

    // Delta CRL for the cert is not present in the context
    SEC_PKI_ERR_DELTA_CRL_FOR_CERT_NOT_PRESENT,    

    // Getting Base CRL for the cert failed
    SEC_PKI_ERR_GET_BASE_CRL_FOR_CERT_FAILED,

    // Getting Delta CRL fot the cert failed
    SEC_PKI_ERR_GET_DELTA_CRL_FOR_CERT_FAILED,

    // Max error of CRL
    SEC_PKI_ERR_CRL_MAX

}SEC_PKI_CRL_ERRORS_S;


//enum to  hold the OCSP errors
typedef enum SEC_PKI_ocsp_errors
{
    // Transport method not set
    SEC_PKI_ERR_NO_TRANS_METHOD = SEC_PKI_ERR_OCSP_INIT,

    // Responder certificate already exists
    SEC_PKI_ERR_RESPONDER_CERT_ALREADY_EXISTS,

    // No responder certificate in trust store
    SEC_PKI_ERR_EMPTY_RESP_CERT_LIST,

    // Matching certificate not found in the responder store
    SEC_PKI_ERR_RESPONDER_CERT_NOT_FOUND,

    // The certificate list sent for status request is found to be empty
    SEC_PKI_OCSP_ERR_EMPTY_REQ_CERT_LIST,

    // The OCSP request Id is already present in the object
    SEC_PKI_OCSP_ERR_REQ_ID_ALREADY_PRESENT,

    // Unable to create OCSP request for the given list of certificates
    SEC_PKI_OCSP_ERR_CREATE_ASYNC_REQ_FAILED,

    // Unable to find the issuer certificate from the trust CA store
    SEC_PKI_OCSP_ERR_UNABLE_TO_FIND_ISSUER,

    // Unable to create OCSP single request
    SEC_PKI_OCSP_ERR_CREATE_SINGLE_REQ_FAILED,

    // Unable to create OCSP request
    SEC_PKI_OCSP_ERR_CREATE_OCSP_REQ_FAILED,

    // Adding the single request to OCSP request failed
    SEC_PKI_OCSP_ERR_ADD_SINGLE_REQ_FAILED,

    // Adding the ocsp request in the request store of the object failed
    SEC_PKI_OCSP_ERR_ADD_REQ_IN_STORE_FAILED,

    // Encoding OCSP request failed
    SEC_PKI_OCSP_ERR_ENCODE_REQUEST_FAILED,

    // The OCSP request Id is not present in the object
    SEC_PKI_OCSP_ERR_REQ_ID_NOT_PRESENT,

    // Decoding OCSP response failed
    SEC_PKI_OCSP_ERR_DECODE_RESPONSE_FAILED,

    // Malformed OCSP Request
    SEC_PKI_OCSP_ERR_RESP_STATUS_MALFORMED,

    // Internal error occurred in issuer
    SEC_PKI_OCSP_ERR_RESP_STATUS_INTER_ERROR,

    // Try again later  
    SEC_PKI_OCSP_ERR_RESP_STATUS_TRYLATER,

    // Signature is required in the OCSP Request
    SEC_PKI_OCSP_ERR_RESP_STATUS_SIG_REQUIRED,

    // OCSP Request unauthorized
    SEC_PKI_OCSP_ERR_RESP_STATUS_UNAUTHORIZED,

    // OCSP response status is found to be unsuccessful
    SEC_PKI_OCSP_ERR_RESP_STATUS_FAILURE,

    // Invalid OCSP response type
    SEC_PKI_OCSP_ERR_RESP_TYPE_INVALID,

    // Extracting Basic response from OCSP response failed
    SEC_PKI_OCSP_ERR_EXTR_BASIC_RESP_FAILED,

    // Invalid OCSP Basic Response Version
    SEC_PKI_OCSP_ERR_BASIC_RESP_INVALID_VERSION,

    // Number of OCSP Single responses varies from number of single requests
    SEC_PKI_OCSP_ERR_SINGLE_RESP_COUNT_MISMATCH,

    // Validation of OCSP Single Responses Failed
    SEC_PKI_OCSP_ERR_INVALID_SINGLE_RESP,

    // URL not present for the input certificate
    SEC_PKI_OCSP_ERR_URL_FOR_CERT_NOT_PRESENT,

    // No responder certificate for the input CA
    SEC_PKI_OCSP_ERR_RESP_CERT_FOR_CA_NOT_PRESENT,

    // The end entity certificates are found to be issued by different CAs
    SEC_PKI_OCSP_ERR_ISSUED_BY_DIFF_CA,

    // Unable to find the responder certificate
    SEC_PKI_OCSP_ERR_FIND_RESP_CERT_FAILED,

    // Signature Verification of OCSP Basic Response failed
    SEC_PKI_OCSP_ERR_RESP_SIGN_VRF_FAILED,

    // Extracting Public key of Responder certificate's issuer failed
    SEC_PKI_OCSP_ERR_EXTR_ISSUER_PUBKEY_FAILED,

    // Hash operation of Responder certificate issuer PubKey failed
    SEC_PKI_OCSP_ERR_HASH_ISSUER_PUBKEY_FAILED,

    // OCSP Signing flag is not set in the responder certificate
    SEC_PKI_OCSP_ERR_OCSP_SIGN_FLAG_NOT_SET,

    // Checking whether the responder certificate is delegated failed
    SEC_PKI_OCSP_ERR_OCSP_CHECK_IS_RESP_DELEG_FAILED,

    // Extracting Public key of Responder certificate failed
    SEC_PKI_OCSP_ERR_EXTR_RESP_PUBKEY_FAILED,

    // Hash operation of Responder certificate PubKey failed
    SEC_PKI_OCSP_ERR_HASH_RESP_PUBKEY_FAILED,

    // Checking whether the responder certificate is CA failed
    SEC_PKI_OCSP_ERR_OCSP_CHECK_IS_RESP_CA_FAILED,

    //The responder is not supposed to give the status of the
    //requested certificates
    SEC_PKI_OCSP_ERR_OCSP_RESP_CERT_FORBID_STATUS,

    // Sending OCSP request through Configured transport method failed
    SEC_PKI_OCSP_ERR_TRANS_SEND_REQ_FAILED,

    // The CertIDs in OCSP Single request and OCSP Single response mismatched
    SEC_PKI_OCSP_ERR_SING_RESP_CERTID_MISMATCH,

    // The Generalised time to Datetime conversion of 
    // ThisUpdate field of OCSP response is failed
    SEC_PKI_OCSP_ERR_THISUPD_GENTIME_DATETIME_CONV_FAILED,

    // The Generalised time to Datetime conversion of 
    // NextUpdate field of OCSP response is failed
    SEC_PKI_OCSP_ERR_NEXTUPD_GENTIME_DATETIME_CONV_FAILED,

    // ThisUpdate field of OCSP response is invalid
    SEC_PKI_OCSP_ERR_THISUPD_INVALID,

    // NextUpdate field of OCSP response is invalid
    SEC_PKI_OCSP_ERR_NEXTUPD_INVALID,

    // The Single Resopnse Time Validation Failed
    SEC_PKI_OCSP_ERR_SING_RESP_TIME_INVALID,

    // The responder certificate chain is invalid
    SEC_PKI_OCSP_ERR_RESPONDER_CERT_CHAIN_INVALID,

    // Copying the Single response list from Basic Response failed
    SEC_PKI_OCSP_ERR_COPY_SINGLE_RESP_LIST_FAILED,

    // Unable to delete the given request ID from Object store
    SEC_PKI_OCSP_ERR_DELETE_REQID_FAILED,

    // Invalid OCSP flags
    SEC_PKI_OCSP_ERR_INVALID_FLAGS,

    // Invalid OCSP request Id
    SEC_PKI_OCSP_ERR_INVALID_REQID,

    // Extracting Subject Name of Responder certificate's issuer failed
    SEC_PKI_OCSP_ERR_EXTR_ISSUER_NAME_FAILED,

    // Hash operation of Responder certificate Issuer Subject Name failed
    SEC_PKI_OCSP_ERR_HASH_ISSUER_NAME_FAILED,

    // Extracting Subject Name of Responder certificate failed
    SEC_PKI_OCSP_ERR_EXTR_RESP_NAME_FAILED,

    // Hash operation of Responder certificate Subject Name failed
    SEC_PKI_OCSP_ERR_HASH_RESP_NAME_FAILED,

    // Multithread should be enabled for using OCSP functionalities
    SEC_PKI_MULTITHREAD_DISABLED,

    // No responder cert part of request list
    SEC_PKI_ERR_EMPTY_RESP_CERT_LIST_REQ,

    // Both CRL and OCSP flags cannot be set together
    SEC_PKI_ERR_CRL_OCSP_CHECK_FLAG,

    // Authority Information Access extension is not present in certificate
    SEC_PKI_OCSP_ERR_NO_AIA_EXTN,

    // OCSP access method is not present in Authority Information Access 
    // extension
    SEC_PKI_OCSP_ERR_NO_OCSP_ACCESS_METHOD,
    
    //No response is availbale in cache.
    SEC_PKI_ERR_RESPONSE_CACHE_IS_EMPTY,

    //Certificate response is not found in context cache
    SEC_PKI_ERR_CERT_NOT_FOUND_IN_CACHE,

    //Reponder certificate validation with time failed
    SEC_PKI_OCSP_ERR_RESPONDER_TIME_CHECK_FAILED,


    // Validation Error

    // Unable to get issuer certificate
    SEC_PKI_OCSP_ERR_UNABLE_TO_GET_ISSUER_CERT,

    // Unable to get responder certificate CRL
    SEC_PKI_OCSP_ERR_UNABLE_TO_GET_CRL,

    // Unable to decrypt certificate's signature
    SEC_PKI_OCSP_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE,

    // Unable to decrypt CRL's signature
    SEC_PKI_OCSP_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE,

    // Unable to decode issuer public key
    SEC_PKI_OCSP_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY,

    // certificate signature failure
    SEC_PKI_OCSP_ERR_CERT_SIGNATURE_FAILURE,

    // CRL signature failure
    SEC_PKI_OCSP_ERR_CRL_SIGNATURE_FAILURE,

    // Certificate is not yet valid
    SEC_PKI_OCSP_ERR_CERT_NOT_YET_VALID,

    // Certificate has expired
    SEC_PKI_OCSP_ERR_CERT_HAS_EXPIRED,

    // Responder Cert's CRL is not yet valid
    SEC_PKI_OCSP_ERR_CRL_NOT_YET_VALID,

    // Responder's CRL has expired
    SEC_PKI_OCSP_ERR_CRL_HAS_EXPIRED,

    // Format error in certificate's notBefore field
    SEC_PKI_OCSP_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD,

    // Format error in certificate's notAfter field
    SEC_PKI_OCSP_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD,

    // Format error in CRL's lastUpdate field
    SEC_PKI_OCSP_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD,

    // Format error in CRL's nextUpdate field
    SEC_PKI_OCSP_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD,

    // No self signed cert present in CA store
    SEC_PKI_OCSP_ERR_DEPTH_ZERO_SELF_SIGNED_CERT,

    // Self signed certificate in certificate chain
    SEC_PKI_OCSP_ERR_SELF_SIGNED_CERT_IN_CHAIN,

    // Unable to get local issuer certificate
    SEC_PKI_OCSP_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY,

    // Unable to verify the first certificate
    SEC_PKI_OCSP_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE,

    // Certificate chain too long
    SEC_PKI_OCSP_ERR_CERT_CHAIN_TOO_LONG,

    // Responder certificate revoked
    SEC_PKI_OCSP_ERR_CERT_REVOKED,

    // Invalid CA certificate
    SEC_PKI_OCSP_ERR_INVALID_CA,

    // Path length constraint exceeded
    SEC_PKI_OCSP_ERR_PATH_LENGTH_EXCEEDED,

    // Unsupported certificate purpose
    SEC_PKI_OCSP_ERR_INVALID_PURPOSE,

    // Certificate not trusted
    SEC_PKI_OCSP_ERR_CERT_UNTRUSTED,

    // Certificate rejected
    SEC_PKI_OCSP_ERR_CERT_REJECTED,

    // Subject issuer mismatch
    SEC_PKI_OCSP_ERR_SUBJECT_ISSUER_MISMATCH,

    // Authority and subject key identifier mismatch
    SEC_PKI_OCSP_ERR_AKID_SKID_MISMATCH,

    // Authority and issuer serial number mismatch
    SEC_PKI_OCSP_ERR_AKID_ISSUER_SERIAL_MISMATCH,

    // Key usage does not include certificate signing
    SEC_PKI_OCSP_ERR_KEYUSAGE_NO_CERTSIGN,

    // Unable to get CRL issuer certificate
    SEC_PKI_OCSP_ERR_UNABLE_TO_GET_CRL_ISSUER,

    // Unhandled critical extension
    SEC_PKI_OCSP_ERR_UNHANDLED_CRITICAL_EXTENSION,

    // Key usage does not include CRL signing
    SEC_PKI_OCSP_ERR_KEYUSAGE_NO_CRL_SIGN,

    // Unhandled critical CRL extension
    SEC_PKI_OCSP_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION,

    // Invalid non-CA certificate (has CA markings)
    SEC_PKI_OCSP_ERR_INVALID_NON_CA,

    // Proxy path length constraint exceeded
    SEC_PKI_OCSP_ERR_PROXY_PATH_LENGTH_EXCEEDED,

    // Key usage does not include digital signature
    SEC_PKI_OCSP_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE,

    // Proxy cerificates not allowed please set the appropriate flag
    SEC_PKI_OCSP_ERR_PROXY_CERTIFICATES_NOT_ALLOWED,

    // Invalid or inconsistent certificate extension
    SEC_PKI_OCSP_ERR_INVALID_EXTENSION,

    // Invalid or inconsistent certificate policy extension
    SEC_PKI_OCSP_ERR_INVALID_POLICY_EXTENSION,

    // No explicit policy
    SEC_PKI_OCSP_ERR_NO_EXPLICIT_POLICY,

    // Different CRL scope
    SEC_PKI_OCSP_ERR_DIFFERENT_CRL_SCOPE,

    // CRL path validation error
    SEC_PKI_OCSP_ERR_CRL_PATH_VALIDATION_ERROR,

    //Responder certificate validation with CRL failed
    SEC_PKI_OCSP_ERR_RESPONDER_REVOC_CHECK_FAILED,

    //Unable to find the Responder's issuer certificate from the trust CA store
    SEC_PKI_OCSP_ERR_UNABLE_TO_FIND_RESPONDER_ISSUER,

    //Requestor name is not set.
    SEC_PKI_OCSP_ERR_REQUESTOR_NAME_NOT_SET,

    //Duplicate general name is failed.
    SEC_PKI_OCSP_ERR_DUP_GENERAL_NAME_FAILED,

    // Add ocsp extension failed.
    SEC_PKI_OCSP_ERR_ADD_EXTENSION_FAILED,

    // Add ocsp Nonce extension failed.
    SEC_PKI_OCSP_ERR_ADD_NONCE_EXTN_FAILED,

    // Add ocsp response type extension failed.
    SEC_PKI_OCSP_ERR_ADD_RESPONSE_TYPE_EXTN_FAILED,

    // Random Nonce Generation failed
    SEC_PKI_ERR_RANDOM_NONCE_GEN_FAILED,

    // Basic response OID not found.
    SEC_PKI_ERR_BASIC_RESPONSE_OID_NOT_FOUND,

    // Add extensions to OCSP request failed.
    SEC_PKI_ERR_ADD_EXTENSION_TO_OCSP_REQUEST_FAILED,

    // Sign OCSP request failed.
    SEC_PKI_ERR_SIGN_OCSP_REQUEST_FAILED,

    // Requestor Cert not found in store.
    SEC_PKI_ERR_REQUESTOR_CERT_NOT_FOUND,

    // Requestor private key not found in store.
    SEC_PKI_ERR_REQUESTOR_PRIVATE_KEY_NOT_FOUND,

    // Set requestor name in request failed.
    SEC_PKI_ERR_SET_REQUESTOR_NAME_IN_REQUEST_FAILED,

    // OCSP NONCE OID not found.
    SEC_PKI_ERR_NONCE_OID_NOT_FOUND,

    // OCSP response nonce does not match.
    SEC_PKI_ERR_NONCE_NOT_MATCHED,

    // OCSP response does not contain nonce extension.
    SEC_PKI_ERR_NONCE_EXT_NOT_AVAILABLE,
    
    // Both Sign with cert & sign with cert chain are mutually exclusive flag
    SEC_PKI_ERR_BOTH_SIGNING_FLAGS_ENABLED,

    // Nonce extension generation failed
    SEC_PKI_ERR_NONCE_EXTN_GEN_FAILED,

    // Create ocsp response type extension failed.
    SEC_PKI_OCSP_ERR_CREATE_RESPONSE_TYPE_EXTN_FAILED,

    //Not even a single OCSP Single Response is stored.
    SEC_PKI_OCSP_ERR_NO_VALID_SINGLE_RESP_LOADED,

    //Empty OCSP Response List
    SEC_PKI_OCSP_ERR_EMPTY_RESP_LIST,

    //Setting Unknown OCSP response is not allowed
    SEC_PKI_OCSP_ERR_SET_UNKNOWN_RESP_NOT_ALLOWED,

    //Empty OCSP request store
    SEC_PKI_OCSP_ERR_EMPTY_REQ_STORE,

    //Calculating OCSP Response Hash Failed
    SEC_PKI_OCSP_ERR_CALC_RESP_HASH_FAILED,

    //Same OCSP Response already exists in the Response Store
    SEC_PKI_OCSP_ERR_RESP_ALREADY_EXIT,

    //Unable to create OCSP Cert ID
    SEC_PKI_OCSP_ERR_CREATE_CERTID_FAILED,

    //Unable to find the OCSP response
    SEC_PKI_OCSP_ERR_UNABLE_TO_FIND_OCSP_RESPONSE,

    //Unable to Create the OCSP response
    SEC_PKI_OCSP_ERR_UNABLE_TO_CREATE_OCSP_RESPONSE,

    //Unable to Encode the OCSP response
    SEC_PKI_OCSP_ERR_ENCODE_OCSP_RESPONSE_FAILED,

	// Validation Error

    /* The OCSP error when unable to find the OCSP 
    responder certificate */
    SEC_PKI_OCSP_ERR_UNABLE_TO_FIND_OCSP_RESPONDER,

    /* The OCSP error when the response is found to be unknown */
    SEC_PKI_OCSP_ERR_UNKNOWN_OCSP_RESPONSE,

    /* The OCSP error when Responder validation failed */
    SEC_PKI_OCSP_ERR_OCSP_RESPONDER_VALIDATION_FAILED,

    /* The OCSP error when Responder validation with CRL failed */
    SEC_PKI_OCSP_ERR_OCSP_RESPONDER_VALIDATION_WITH_CRL_FAILED,

    /* The OCSP error when Responder validation with time failed */
    SEC_PKI_OCSP_ERR_OCSP_RESPONDER_VALIDATION_WITH_TIME_FAILED,

    /* The OCSP error when the response is found to be not yet valid */
    SEC_PKI_OCSP_ERR_OCSP_RESP_NOT_YET_VALID,

    /* The OCSP error when the response is found to be expired */
    SEC_PKI_OCSP_ERR_OCSP_RESP_HAS_EXPIRED,

    /* The OCSP error when error happended in 
    checking This Update field */
    SEC_PKI_OCSP_ERR_ERROR_IN_OCSP_RESP_THIS_UPDATE_FIELD,

    /* The OCSP error when error happended in 
    checking Next Update field */
    SEC_PKI_OCSP_ERR_ERROR_IN_OCSP_RESP_NEXT_UPDATE_FIELD,

    /* The OCSP error when Signature Verification Failed */
    SEC_PKI_OCSP_ERR_OCSP_SIGN_VERIFY_FAILED,

    /* The OCSP error when the certificate is found to be revoked 
    using OCSP response*/
    SEC_PKI_OCSP_ERR_CERT_REVOKED_BY_OCSP_RESP,

    /*OCSP Lock creation failed at PKI context*/
    SEC_PKI_OCSP_ERR_CTX_LOCK_CREATION_FAILED,

    // Max error of OCSP
    SEC_PKI_ERR_OCSP_MAX

}SEC_PKI_OCSP_ERRORS_S;


// Gives the error code
#define SEC_PKI_ERR_REASON_CODE(err)\
    (err & 0x0000FFFF)

// Gives the function code where error is occured
#define SEC_PKI_FUNC_REASON_CODE(err)\
    (err >> 16)


#ifdef  __cplusplus
}
#endif

#endif


