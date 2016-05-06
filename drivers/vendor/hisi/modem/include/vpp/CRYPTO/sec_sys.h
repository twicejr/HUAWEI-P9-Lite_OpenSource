/*****************************************************************************
                                                                            
                Copyright (C), 2008, Huawei Tech. Co., Ltd.                
                            ALL RIGHTS RESERVED                             
                                                                            
------------------------------------------------------------------------------


FileName     : sec_sys.h
Author       : Sanjay Vasudevan
Version      : 1
Date         : 2005-07-13
Description  : 
Function List:

          History:
                    <author>   <date>          <desc>
----------------------------------------------------------------------------
****************************************************************************/

/*
                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED


 Project Code:     iPsi
 Module Name:      Common Module
 Date Created:     2005-07-13
 Author:           Sanjay Vasudevan
 @brief:           Contains structures and functions required in two or more
 modules - The list of items in this file are:
 SEC_REPORT_ERROR- To log errors if _SEC_DEBUG_MODE is set
 Memory Macros-    To allocate,free,set,copy,compare memory blocks
 SEC_fprintf-      To print to a file
 SEC_CertType_E-   enumeration to hold Certificate type: used in
 PKCS12,SCEPTo print to a file
 SEC_getPubKey-    functions to convert SubjPubKeyInfo to SEC_PKEY
 SEC_createSubjPubKeyInfoand viceversa
 SEC_GenTimeToDateTime-  To convert GeneralizedTime to Dtae Time
 SEC_DateTimeToGenTime-  and viceversa
*/
#ifndef  _SEC_SYS_H_
#define  _SEC_SYS_H_

#include "ipsi_time.h"

#include "ipsi_types.h"
#include "ipsi_misc.h"

#ifdef   __cplusplus
extern  "C"{
#endif


#if defined(__CRYPTO_BUILD_DLL_)
# define CRYPTOLINKDLL __declspec(dllexport)
#elif defined(__CRYPTO_USR_DLL_) 
# define CRYPTOLINKDLL __declspec(dllimport)
#else
# define CRYPTOLINKDLL
#endif

#if defined(__PSE_BUILD_DLL_)
# define PSELINKDLL __declspec(dllexport)
#elif defined(__PSE_USR_DLL_) 
# define PSELINKDLL __declspec(dllimport)
#else
# define PSELINKDLL
#endif

#if defined(__SSL_BUILD_DLL_)
# define SSLLINKDLL __declspec(dllexport)
#elif defined(__SSL_USR_DLL_) 
# define SSLLINKDLL __declspec(dllimport)
#else
# define SSLLINKDLL
#endif

#if defined(__HTTP_BUILD_DLL_)
# define HTTPLINKDLL __declspec(dllexport)
#elif defined(__HTTP_USR_DLL_) 
# define HTTPLINKDLL __declspec(dllimport)
#else
# define HTTPLINKDLL
#endif


/** @defgroup sec_sys
* This section contains the sec_sys Enum, Structure and Functions.
*/


/** @defgroup sec_sysEnum
* @ingroup sec_sys
* This section contain the sec_sys Enum.
*/

/** @defgroup sec_sysStructure
* @ingroup sec_sys
* This section contain the sec_sys Structure.
*/


/** @defgroup sec_sysFunctions
* @ingroup sec_sys
* This section contains the sec_sys Functions.
*/


/*
    Func Name:  setAesKey
*/

/** 
* @defgroup setAesKey
* @ingroup sec_sysFunctions
* @par Prototype
* @code
* void setAesKey();
* @endcode
*
* @par Purpose
* This is used to set key to core algorithm.
*
* @par Description
* setAesKey function sets key to AES encryption algorithm.
*
* @par Parameters
* N/A
*
* @retval void This function does not return any value [N/A|N/A]
* 
* @par Required Header File
* ses_sys.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/

void setAesKey();

/*
    Func Name:  RNGinit
*/

/** 
* @defgroup RNGinit
* @ingroup sec_sysFunctions
* @par Prototype
* @code
* int RNGinit(SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to initialize RNG object.
*
* @par Description
* RNGinit function initializes the global RNG object.
*
* @par Parameters
* N/A
*
* @retval int Invalid algorithm id [false|N/A]
* @retval int Internal error encountered [SEC_ERR|N/A]
* @retval int Initializes successfully global object [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_sys.h
*
* @par Note
* \n
* N/A
*
* @par Related Topic
* N/A
*/

int RNGinit(SEC_VOID);


/* the enum to hold all the common IDs corresponding to
the OIDs (in the algtable) */

/*
* @defgroup SEC_CID_E
* @ingroup sec_sysEnum
* @par Prototype
* @code
* typedef enum
* {
*  CID_UNKNOWN,
*  CID_RC4,
*  CID_DES_ECB,
*  CID_DES_CBC,
*  CID_DES_OFB,
*  CID_DES_CFB,
*  CID_SCB2_128_ECB,
*  CID_SCB2_128_CBC,
*  CID_SCB2_256_ECB,
*  CID_SCB2_256_CBC,
*  CID_DES_EDE_ECB,
*  CID_DES_EDE_CBC,
*  CID_DES_EDE_OFB,
*  CID_DES_EDE_CFB,
*  CID_DES_EDE3_ECB,
*  CID_DES_EDE3_CBC,
*  CID_DES_EDE3_OFB,
*  CID_DES_EDE3_CFB,
*  CID_AES128_ECB,
*  CID_AES128_CBC,
*  CID_AES128_OFB,
*  CID_AES128_CFB,
*  CID_AES192_ECB,
*  CID_AES192_CBC,
*  CID_AES192_OFB,
*  CID_AES192_CFB,
*  CID_AES256_ECB,
*  CID_AES256_CBC,
*  CID_AES256_OFB,
*  CID_AES256_CFB,
*  CID_KASUMI_ECB,
*  CID_KASUMI_CBC,
*  CID_KASUMI_OFB,
*  CID_KASUMI_CFB,
*  CID_RSA,
*  CID_DSA,
*  CID_ECDSA,
*  CID_ECDSA192,
*  CID_DH,
*  CID_ECDH,
*  CID_MD5,
*  CID_SHA1,
*  CID_SHA224,
*  CID_SHA256,
*  CID_SHA384,
*  CID_SHA512,
*  CID_HMAC_MD5,
*  CID_HMAC_SHA1,
*  CID_HMAC_SHA224,
*  CID_HMAC_SHA256,
*  CID_HMAC_SHA384,
*  CID_HMAC_SHA512,
*  CID_MD5WITHRSA,
*  CID_SHA1WITHRSA,
*  CID_SHA1WITHRSAOLD,
*  CID_DSAWITHSHA1,
*  CID_DSAWITHSHA1_2,
*  CID_ECDSAWITHSHA1,
*  CID_ECDSAWITHSHA224,
*  CID_ECDSAWITHSHA256,
*  CID_ECDSAWITHSHA384,
*  CID_ECDSAWITHSHA512,
*  CID_ECDSA192WITHSHA256,
*  CID_SHA256WITHRSAENCRYPTION,
*  CID_SHA384WITHRSAENCRYPTION,
*  CID_SHA512WITHRSAENCRYPTION,
*  CID_KEYEXCHANGEALGORITHM,
*  CID_PKCS1,
*  CID_ANSI_X9_62,
*  CID_ECSIGTYPE,
*  CID_FIELDTYPE,
*  CID_PRIME_FIELD,
*  CID_CHARACTERISTIC_TWO_FIELD,
*  CID_CHARACTERISTIC_TWO_BASIS,
*  CID_GNBASIS,
*  CID_TPBASIS,
*  CID_PPBASIS,
*  CID_PUBLICKEYTYPE,
*  CID_ELLIPTICCURVE,
*  CID_C_TWOCURVE,
*  CID_C2PNB163V1,
*  CID_C2PNB163V2,
*  CID_C2PNB163V3,
*  CID_C2PNB176W1,
*  CID_C2TNB191V1,
*  CID_C2TNB191V2,
*  CID_C2TNB191V3,
*  CID_C2ONB191V4,
*  CID_C2ONB191V5,
*  CID_C2PNB208W1,
*  CID_C2TNB239V1,
*  CID_C2TNB239V2,
*  CID_C2TNB239V3,
*  CID_C2ONB239V4,
*  CID_C2ONB239V5,
*  CID_C2PNB272W1,
*  CID_C2PNB304W1,
*  CID_C2TNB359V1,
*  CID_C2PNB368W1,
*  CID_C2TNB431R1,
*  CID_PRIMECURVE,
*  CID_PRIME192V1,
*  CID_PRIME192V2,
*  CID_PRIME192V3,
*  CID_PRIME239V1,
*  CID_PRIME239V2,
*  CID_PRIME239V3,
*  CID_PRIME256V1,
*  CID_VERISIGN,
*  CID_PKI,
*  CID_ATTRIBUTES,
*  CID_MESSAGETYPE,
*  CID_PKISTATUS,
*  CID_FAILINFO,
*  CID_SENDERNONCE,
*  CID_RECIPIENTNONCE,
*  CID_TRANSID,
*  CID_EXTENSIONREQ,
*  CID_RSADSI,
*  CID_PKCS,
*  CID_PKCS5,
*  CID_PBKDF2,
*  CID_PBE_MD2WITHDESCBC,
*  CID_PBE_MD2WITHRC2CBC,
*  CID_PBE_MD5WITHDESCBC,
*  CID_PBE_MD5WITHRC2CBC,
*  CID_PBE_SHA1WITHDESCBC,
*  CID_PBE_SHA1WITHRC2CBC,
*  CID_PBES2,
*  CID_PBMAC1,
*  CID_DIGESTALGORITHM,
*  CID_ENCRYPTIONALGORITHM,
*  CID_RC2CBC,
*  CID_RC5_CBC_PAD,
*  CID_RSAES_OAEP,
*  CID_PKIX_OCSP_BASIC,
*  CID_PKIX_OCSP_NONCE,
*  CID_PKIX_OCSP_CRL,
*  CID_PKIX_OCSP_RESPONSE,
*  CID_PKIX_OCSP_NOCHECK,
*  CID_PKIX_OCSP_ARCHIVE_CUTOFF,
*  CID_PKIX_OCSP_SERVICE_LOCATOR,
*  CID_CHALLENGE_PWD_ATTR,
*  CID_EXTENSIONREQUEST,
*  CID_PKIX,
*  CID_PE,
*  CID_QT,
*  CID_KP,
*  CID_AD,
*  CID_QT_CPS,
*  CID_QT_UNOTICE,
*  CID_AD_OCSP,
*  CID_AD_CAISSUERS,
*  CID_AD_TIMESTAMPING,
*  CID_AD_CAREPOSITORY,
*  CID_AT,
*  CID_AT_NAME,
*  CID_AT_SURNAME,
*  CID_AT_GIVENNAME,
*  CID_AT_INITIALS,
*  CID_AT_GENERATIONQUALIFIER,
*  CID_AT_COMMONNAME,
*  CID_AT_LOCALITYNAME,
*  CID_AT_STATEORPROVINCENAME,
*  CID_AT_ORGANIZATIONNAME,
*  CID_AT_ORGANIZATIONALUNITNAME,
*  CID_AT_TITLE,
*  CID_AT_DNQUALIFIER,
*  CID_AT_COUNTRYNAME,
*  CID_AT_SERIALNUMBER,
*  CID_AT_PSEUDONYM,
*  CID_DOMAINCOMPONENT,
*  CID_EMAILADDRESS,
*  CID_CE,
*  CID_CE_AUTHORITYKEYIDENTIFIER,
*  CID_CE_SUBJECTKEYIDENTIFIER,
*  CID_CE_KEYUSAGE,
*  CID_CE_PRIVATEKEYUSAGEPERIOD,
*  CID_CE_CERTIFICATEPOLICIES,
*  CID_ANYPOLICY,
*  CID_CE_POLICYMAPPINGS,
*  CID_CE_SUBJECTALTNAME,
*  CID_CE_ISSUERALTNAME,
*  CID_CE_SUBJECTDIRECTORYATTRIBUTES,
*  CID_CE_BASICCONSTRAINTS,
*  CID_CE_NAMECONSTRAINTS,
*  CID_CE_POLICYCONSTRAINTS,
*  CID_CE_CRLDISTRIBUTIONPOINTS,
*  CID_CE_EXTKEYUSAGE,
*  CID_ANYEXTENDEDKEYUSAGE,
*  CID_KP_SERVERAUTH,
*  CID_KP_CLIENTAUTH,
*  CID_KP_CODESIGNING,
*  CID_KP_EMAILPROTECTION,
*  CID_KP_TIMESTAMPING,
*  CID_KP_OCSPSIGNING,
*  CID_CE_INHIBITANYPOLICY,
*  CID_CE_FRESHESTCRL,
*  CID_PE_AUTHORITYINFOACCESS,
*  CID_PE_SUBJECTINFOACCESS,
*  CID_CE_CRLNUMBER,
*  CID_CE_ISSUINGDISTRIBUTIONPOINT,
*  CID_CE_DELTACRLINDICATOR,
*  CID_CE_CRLREASONS,
*  CID_CE_CERTIFICATEISSUER,
*  CID_CE_HOLDINSTRUCTIONCODE,
*  CID_HOLDINSTRUCTION,
*  CID_HOLDINSTRUCTION_NONE,
*  CID_HOLDINSTRUCTION_CALLISSUER,
*  CID_HOLDINSTRUCTION_REJECT,
*  CID_CE_INVALIDITYDATE,
*  CID_PDA_DATEOFBIRTH,
*  CID_PDA_PLACEOFBIRTH,
*  CID_PDA_GENDER,
*  CID_PDA_COUNTRYOFCITIZENSHIP,
*  CID_PDA_COUNTRYOFRESIDENCE,
*  CID_PDA,
*  CID_ON_PERMANENTIDENTIFIER,
*  CID_ON,
*  CID_CE_DOMAININFO,
*  CID_PASSWORDBASEDMAC,
*  CID_DHBASEDMAC,
*  CID_IT,
*  CID_CAPROTENCCERT,
*  CID_SIGNKEYPAIRTYPES,
*  CID_ENCKEYPAIRTYPES,
*  CID_PREFERREDSYMMALG,
*  CID_CAKEYUPDATEINFO,
*  CID_CURRENTCRL,
*  CID_PKIP,
*  CID_REGCTRL,
*  CID_REGCTRL_REGTOKEN,
*  CID_REGCTRL_AUTHENTICATOR,
*  CID_REGCTRL_PKIPUBLICATIONINFO,
*  CID_REGCTRL_PKIARCHIVEOPTIONS,
*  CID_REGCTRL_OLDCERTID,
*  CID_REGCTRL_PROTOCOLENCRKEY,
*  CID_REGINFO,
*  CID_REGINFO_UTF8PAIRS,
*  CID_REGINFO_CERTREQ,
*  CID_PKCS12,
*  CID_PKCS12PBEIDS,
*  CID_PBE_SHAWITH128BITRC4,
*  CID_PBE_SHAWITH40BITRC4,
*  CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC,
*  CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC,
*  CID_PBE_SHAWITH128BIT_RC2CBC,
*  CID_PBE_SHAWITH40BIT_RC2CBC,
*  CID_BAGTYPES,
*  CID_KEYBAG,
*  CID_PKCS8SHROUDEDKEYBAG,
*  CID_CERTBAG,
*  CID_CRLBAG,
*  CID_SECRETBAG,
*  CID_SAFECONTENTSBAG,
*  CID_X509CERTIFICATE,
*  CID_SDSICERTIFICATE,
*  CID_FRIENDLYNAME,
*  CID_LOCALKEYID,
*  CID_CERTIFICATEREVOCATIONLIST,
*  CID_PKCS7,
*  CID_PKCS7_SIMPLEDATA,
*  CID_PKCS7_SIGNEDDATA,
*  CID_PKCS7_ENVELOPEDDATA,
*  CID_PKCS7_SIGNED_ENVELOPEDDATA,
*  CID_PKCS7_DIGESTEDDATA,
*  CID_PKCS7_ENCRYPTEDDATA,
*  CID_PKCS9,
*  CID_PKCS9_AT_CONTENTTYPE,
*  CID_PKCS9_AT_MESSAGEDIGEST,
*  CID_PKCS9_AT_SIGNINGTIME,
*  CID_PKCS9_AT_COUNTERSIGNATURE,
*  CID_PKCS9_AT_RANDOMNONCE,
*  CID_PKCS9_AT_SEQUENCENUMBER,
*  CID_MD4,
*  CID_HMAC_MD4,
*  CID_CMAC_AES,
*  CID_CMAC_TDES,
*  CID_RNG_HW,
*  CID_RNG_SW,
*  CID_XCBC_AES,
*  CID_RC2_ECB,
*  CID_RC2_CBC,
*  CID_RC2_OFB,
*  CID_RC2_CFB,
*  CID_MD5_SHA1,
*  CID_SM3,
*  CID_HMAC_SM3,
*  CID_SM2DSAWITHSM3,
*  CID_SM2DSAWITHSHA1,
*  CID_SM2DSAWITHSHA256,
*  CID_SM2PRIME256,
*  CID_SM2DSA,
*  CID_SM2KEP,
*  CID_SM2PKEA

* }SEC_CID_E;
* @endcode
*
* @datastruct CID_UNKNOWN Unknown alg id.
* @datastruct CID_RC4 identifies the RC4 algorithm.
* @datastruct CID_DES_ECB identifies DES algorithm in ECB mode
* @datastruct CID_DES_CBC identifies DES algorithm in CBC mode
* @datastruct CID_DES_OFB identifies DES algorithm in OFB mode
* @datastruct CID_DES_CFB identifies DES algorithm in CFB mode
* @datastruct CID_SCB2_128_ECB Algorithm Id for SSX31B HW support.
     Identifies SCB2-128 algorithm in ECB mode.
* @datastruct CID_SCB2_128_CBC Algorithm Id for SSX31B HW support.
     Identifies SCB2-128 algorithm in CBC mode.
* @datastruct CID_SCB2_256_ECB Algorithm Id for SSX31B HW support.
     Identifies SCB2-256 algorithm in ECB mode.
* @datastruct CID_SCB2_256_CBC Algorithm Id for SSX31B HW support.
     Identifies SCB2-256 algorithm in CBC mode.
* @datastruct CID_DES_EDE_ECB identifies 2 key triple DES algorithm in ECB mode
* @datastruct CID_DES_EDE_CBC Identifies 2 key triple DES algorithm in CBC mode
* @datastruct CID_DES_EDE_OFB Identifies 2 key triple DES algorithm in OFB mode
* @datastruct CID_DES_EDE_CFB Identifies 2 key triple DES algorithm in CFB mode
* @datastruct CID_DES_EDE3_ECB Identifies 3 key triple DES algorithm in ECB mode
* @datastruct CID_DES_EDE3_CBC Identifies 3 key triple DES algorithm in CBC mode
* @datastruct CID_DES_EDE3_OFB Identifies 3 key triple DES algorithm in OFB mode
* @datastruct CID_DES_EDE3_CFB Identifies 3 key triple DES algorithm in CFB mode
* @datastruct CID_AES128_ECB Identifies AES-128 algorithm in ECB mode.
* @datastruct CID_AES128_CBC Identifies AES-128 algorithm in CBC mode.
* @datastruct CID_AES128_OFB Identifies AES-128 algorithm in OFB mode.
* @datastruct CID_AES128_CFB Identifies AES-128 algorithm in CFB mode.
* @datastruct CID_AES192_ECB Identifies AES-192 algorithm in ECB mode.
* @datastruct CID_AES192_CBC Identifies AES-192 algorithm in CBC mode.
* @datastruct CID_AES192_OFB Identifies AES-192 algorithm in OFB mode.
* @datastruct CID_AES192_CFB Identifies AES-192 algorithm in CFB mode.
* @datastruct CID_AES256_ECB Identifies AES-256 algorithm in ECB mode.
* @datastruct CID_AES256_CBC Identifies AES-256 algorithm in CBC mode.
* @datastruct CID_AES256_OFB Identifies AES-256 algorithm in OFB mode.
* @datastruct CID_AES256_CFB Identifies AES-256 algorithm in CFB mode.
* @datastruct CID_KASUMI_ECB Identifies Kasumi algorithm in ECB mode.
* @datastruct CID_KASUMI_CBC Identifies Kasumi algorithm in CBC mode.
* @datastruct CID_KASUMI_OFB Identifies Kasumi algorithm in OFB mode.
* @datastruct CID_KASUMI_CFB Identifies Kasumi algorithm in CFB mode.
* @datastruct CID_RSA Identifies the RSA algorithm.
* @datastruct CID_DSA Identifies the DSA algorithm.
* @datastruct CID_ECDSA Identifies the ECDSA algorithm.
* @datastruct CID_ECDSA192 Identifies the ECDSA192 algorithm.
* @datastruct CID_DH Identifies the Diffie-Hellman algorithm.
* @datastruct CID_ECDH Identifies the EC Diffie-Hellman algorithm.
* @datastruct CID_MD5 Identifies the MD5 hash algorithm.
* @datastruct CID_SHA1 Identifies the SHA1 hash algorithm.
* @datastruct CID_SHA224 Identifies the SHA224 hash algorithm.
* @datastruct CID_SHA256 Identifies the SHA256 hash algorithm.
* @datastruct CID_SHA384 Identifies the SHA384 hash algorithm.
* @datastruct CID_SHA512 Identifies the SHA512 hash algorithm.
* @datastruct CID_HMAC_MD5 Identifies hmac with MD5.
* @datastruct CID_HMAC_SHA1 Identifies hmac with SHA1.
* @datastruct CID_HMAC_SHA224 Identifies hmac with SHA224.
* @datastruct CID_HMAC_SHA256 Identifies hmac with SHA256.
* @datastruct CID_HMAC_SHA384 Identifies hmac with SHA384.
* @datastruct CID_HMAC_SHA512 Identifies hmac with SHA512.
* @datastruct CID_MD5WITHRSA Identifies signature using MD5 and RSA.    
* @datastruct CID_SHA1WITHRSA Identifies signature using SHA1 and RSA.
* @datastruct CID_SHA1WITHRSAOLD Identifies signature using SHA1 and 
            RSA (coresponds to old Oid).
* @datastruct CID_DSAWITHSHA1 Identifies signature using SHA1 and DSA.
* @datastruct CID_DSAWITHSHA1_2 Identifies signature using SHA1 and DSA.
* @datastruct CID_ECDSAWITHSHA1 Identifies signature using SHA1 and ECDSA.
* @datastruct CID_ECDSAWITHSHA224 Identifies signature using SHA224 and ECDSA.
* @datastruct CID_ECDSAWITHSHA256 Identifies signature using SHA256 and ECDSA.
* @datastruct CID_ECDSAWITHSHA384 Identifies signature using SHA384 and ECDSA.
* @datastruct CID_ECDSAWITHSHA512 Identifies signature using SHA512 and ECDSA.
* @datastruct CID_ECDSA192WITHSHA256 Identifies signature using 
            SHA256 and ECDSA-192 bit.
* @datastruct CID_SHA256WITHRSAENCRYPTION Identifies signature using SHA256
            and RSA.
* @datastruct CID_SHA384WITHRSAENCRYPTION Identifies signature using SHA384
            and RSA.
* @datastruct CID_SHA512WITHRSAENCRYPTION Identifies signature using SHA512 
            and RSA.
* @datastruct CID_KEYEXCHANGEALGORITHM Identifies Key exchange algorithm.
* @datastruct CID_PKCS1 Identifies PKCS1.
* @datastruct CID_ANSI_X9_62 Identifies ANSI_X9_62.
* @datastruct CID_ECSIGTYPE Identifies ECSIGTYPE.
* @datastruct CID_FIELDTYPE Identifies Field Type.
* @datastruct CID_PRIME_FIELD Identifies PRIME Field.
* @datastruct CID_CHARACTERISTIC_TWO_FIELD Identifies Characterstic Two field.
* @datastruct CID_CHARACTERISTIC_TWO_BASIS Identifies Characterstic Two Basis.
* @datastruct CID_GNBASIS Identifies GNBASIS.
* @datastruct CID_TPBASIS Identifies TPBASIS.
* @datastruct CID_PPBASIS Identifies PPBASIS.
* @datastruct CID_PUBLICKEYTYPE Identifies PUBLICKEYTYPE.
* @datastruct CID_ELLIPTICCURVE Identifies ELLIPTICCURVE.
* @datastruct CID_C_TWOCURVE Identifies C_TWOCURVE.
* @datastruct CID_C2PNB163V1 Identifies C2PNB163V1.
* @datastruct CID_C2PNB163V2 Identifies C2PNB163V2.
* @datastruct CID_C2PNB163V3 Identifies C2PNB163V3.
* @datastruct CID_C2PNB176W1 Identifies C2PNB176W1.
* @datastruct CID_C2TNB191V1 Identifies C2TNB191V1.
* @datastruct CID_C2TNB191V2 Identifies C2TNB191V2.
* @datastruct CID_C2TNB191V3 Identifies C2TNB191V3.
* @datastruct CID_C2ONB191V4 Identifies C2ONB191V4.
* @datastruct CID_C2ONB191V5 Identifies C2ONB191V5.
* @datastruct CID_C2PNB208W1 Identifies C2PNB208W1.
* @datastruct CID_C2TNB239V1 Identifies C2TNB239V1.
* @datastruct CID_C2TNB239V2 Identifies C2TNB239V2.
* @datastruct CID_C2TNB239V3 Identifies C2TNB239V3.
* @datastruct CID_C2ONB239V4 Identifies C2ONB239V4.
* @datastruct CID_C2ONB239V5 Identifies C2ONB239V5.
* @datastruct CID_C2PNB272W1 Identifies C2PNB272W1.
* @datastruct CID_C2PNB304W1 Identifies C2PNB304W1.
* @datastruct CID_C2TNB359V1 Identifies C2TNB359V1.
* @datastruct CID_C2PNB368W1 Identifies C2PNB368W1.
* @datastruct CID_C2TNB431R1 Identifies C2TNB431R1.
* @datastruct CID_PRIMECURVE Identifies PRIMECURVE.
* @datastruct CID_PRIME192V1 Identifies PRIME192V1.
* @datastruct CID_PRIME192V2 Identifies PRIME192V2.
* @datastruct CID_PRIME192V3 Identifies PRIME192V3.
* @datastruct CID_PRIME239V1 Identifies PRIME239V1.
* @datastruct CID_PRIME239V2 Identifies PRIME239V2.
* @datastruct CID_PRIME239V3 Identifies PRIME239V3.
* @datastruct CID_PRIME256V1 Identifies PRIME256V1.
* @datastruct CID_VERISIGN Identifies VERISIGN.
* @datastruct CID_PKI Identifies PKI.
* @datastruct CID_ATTRIBUTES Identifies ATTRIBUTES.
* @datastruct CID_MESSAGETYPE Identifies MESSAGETYPE.
* @datastruct CID_PKISTATUS Identifies PKISTATUS.
* @datastruct CID_FAILINFO Identifies FAILINFO.
* @datastruct CID_SENDERNONCE Identifies SENDERNONCE.
* @datastruct CID_RECIPIENTNONCE Identifies RECIPIENTNONCE.
* @datastruct CID_TRANSID Identifies TRANSID.
* @datastruct CID_EXTENSIONREQ Identifies EXTENSIONREQ.
* @datastruct CID_RSADSI Identifies RSADSI.
* @datastruct CID_PKCS Identifies PKCS.
* @datastruct CID_PKCS5 Identifies PKCS5.
* @datastruct CID_PBKDF2 Identifies PBKDF2.
* @datastruct CID_PBE_MD2WITHDESCBC Identifies PBE_MD2WITHDESCBC.
* @datastruct CID_PBE_MD2WITHRC2CBC Identifies PBE_MD2WITHRC2CBC.
* @datastruct CID_PBE_MD5WITHDESCBC Identifies PBE_MD5WITHDESCBC.
* @datastruct CID_PBE_MD5WITHRC2CBC Identifies PBE_MD5WITHRC2CBC.
* @datastruct CID_PBE_SHA1WITHDESCBC Identifies PBE_SHA1WITHDESCBC.
* @datastruct CID_PBE_SHA1WITHRC2CBC Identifies PBE_SHA1WITHRC2CBC.
* @datastruct CID_PBES2 Identifies PBES2.
* @datastruct CID_PBMAC1 Identifies PBMAC1.
* @datastruct CID_DIGESTALGORITHM Identifies DIGESTALGORITHM.
* @datastruct CID_ENCRYPTIONALGORITHM Identifies ENCRYPTIONALGORITHM.
* @datastruct CID_RC2CBC Identifies RC2CBC.
* @datastruct CID_RC5_CBC_PAD Identifies RC5_CBC_PAD.
* @datastruct CID_RSAES_OAEP Identifies RSAES_OAEP.
* @datastruct CID_PKIX_OCSP_BASIC Identifies OCSP_BASIC.
* @datastruct CID_PKIX_OCSP_NONCE Identifies OCSP_NONCE.
* @datastruct CID_PKIX_OCSP_CRL Identifies OCSP_CRL.
* @datastruct CID_PKIX_OCSP_RESPONSE Identifies OCSP_RESPONSE.
* @datastruct CID_PKIX_OCSP_NOCHECK Identifies OCSP_NOCHECK.
* @datastruct CID_PKIX_OCSP_ARCHIVE_CUTOFF Identifies OCSP_ARCHIVE_CUTOFF.
* @datastruct CID_PKIX_OCSP_SERVICE_LOCATOR Identifies OCSP_SERVICE_LOCATOR.
* @datastruct CID_CHALLENGE_PWD_ATTR Identifies Challenge Password Attr.
* @datastruct CID_EXTENSIONREQUEST Identifies EXTENSIONREQUEST.
* @datastruct CID_PKIX Identifies PKIX.
* @datastruct CID_PE Identifies PE.
* @datastruct CID_QT Identifies QT.
* @datastruct CID_KP Identifies KP.
* @datastruct CID_AD Identifies AD.
* @datastruct CID_QT_CPS Identifies CPS.
* @datastruct CID_QT_UNOTICE Identifies UNOTICE.
* @datastruct CID_AD_OCSP Identifies OCSP.
* @datastruct CID_AD_CAISSUERS Identifies CAISSUERS.
* @datastruct CID_AD_TIMESTAMPING Identifies TIMESTAMPING.
* @datastruct CID_AD_CAREPOSITORY Identifies CAREPOSITORY.
* @datastruct CID_AT Identifies AT.
* @datastruct CID_AT_NAME Identifies NAME.
* @datastruct CID_AT_SURNAME Identifies SURNAME.
* @datastruct CID_AT_GIVENNAME Identifies GIVENNAME.
* @datastruct CID_AT_INITIALS Identifies INITIALS.
* @datastruct CID_AT_GENERATIONQUALIFIER Identifies GENERATIONQUALIFIER.
* @datastruct CID_AT_COMMONNAME Identifies COMMONNAME.
* @datastruct CID_AT_LOCALITYNAME Identifies LOCALITYNAME.
* @datastruct CID_AT_STATEORPROVINCENAME Identifies STATEORPROVINCENAME.
* @datastruct CID_AT_ORGANIZATIONNAME Identifies ORGANIZATIONNAME.
* @datastruct CID_AT_ORGANIZATIONALUNITNAME Identifies ORGANIZATIONALUNITNAME.
* @datastruct CID_AT_TITLE Identifies TITLE.
* @datastruct CID_AT_DNQUALIFIER Identifies DNQUALIFIER.
* @datastruct CID_AT_COUNTRYNAME Identifies COUNTRYNAME.
* @datastruct CID_AT_SERIALNUMBER Identifies SERIALNUMBER.
* @datastruct CID_AT_PSEUDONYM Identifies PSEUDONYM.
* @datastruct CID_DOMAINCOMPONENT Identifies DOMAINCOMPONENT.
* @datastruct CID_EMAILADDRESS Identifies EMAILADDRESS.
* @datastruct CID_CE Identifies CE.
* @datastruct CID_CE_AUTHORITYKEYIDENTIFIER Identifies AUTHORITYKEYIDENTIFIER.
* @datastruct CID_CE_SUBJECTKEYIDENTIFIER Identifies SUBJECTKEYIDENTIFIER.
* @datastruct CID_CE_KEYUSAGE Identifies KEYUSAGE.
* @datastruct CID_CE_PRIVATEKEYUSAGEPERIOD Identifies PRIVATEKEYUSAGEPERIOD.
* @datastruct CID_CE_CERTIFICATEPOLICIES Identifies CERTIFICATEPOLICIES.
* @datastruct CID_ANYPOLICY Identifies ANYPOLICY.
* @datastruct CID_CE_POLICYMAPPINGS Identifies POLICYMAPPINGS.
* @datastruct CID_CE_SUBJECTALTNAME Identifies SUBJECTALTNAME.
* @datastruct CID_CE_ISSUERALTNAME Identifies ISSUERALTNAME.
* @datastruct CID_CE_SUBJECTDIRECTORYATTRIBUTES Identifies 
            SUBJECTDIRECTORYATTRIBUTES.
* @datastruct CID_CE_BASICCONSTRAINTS Identifies BASICCONSTRAINTS.
* @datastruct CID_CE_NAMECONSTRAINTS Identifies NAMECONSTRAINTS.
* @datastruct CID_CE_POLICYCONSTRAINTS Identifies POLICYCONSTRAINTS.
* @datastruct CID_CE_CRLDISTRIBUTIONPOINTS Identifies CRLDISTRIBUTIONPOINTS.
* @datastruct CID_CE_EXTKEYUSAGE Identifies EXTKEYUSAGE.
* @datastruct CID_ANYEXTENDEDKEYUSAGE Identifies ANYEXTENDEDKEYUSAGE.
* @datastruct CID_KP_SERVERAUTH Identifies SERVERAUTH.
* @datastruct CID_KP_CLIENTAUTH Identifies CLIENTAUTH.
* @datastruct CID_KP_CODESIGNING Identifies CODESIGNING.
* @datastruct CID_KP_EMAILPROTECTION Identifies EMAILPROTECTION.
* @datastruct CID_KP_TIMESTAMPING Identifies TIMESTAMPING.
* @datastruct CID_KP_OCSPSIGNING Identifies OCSPSIGNING.
* @datastruct CID_CE_INHIBITANYPOLICY Identifies INHIBITANYPOLICY.
* @datastruct CID_CE_FRESHESTCRL Identifies FRESHESTCRL.
* @datastruct CID_PE_AUTHORITYINFOACCESS Identifies AUTHORITYINFOACCESS.
* @datastruct CID_PE_SUBJECTINFOACCESS Identifies SUBJECTINFOACCESS.
* @datastruct CID_CE_CRLNUMBER Identifies CRLNUMBER.
* @datastruct CID_CE_ISSUINGDISTRIBUTIONPOINT Identifies 
            ISSUINGDISTRIBUTIONPOINT.
* @datastruct CID_CE_DELTACRLINDICATOR Identifies DELTACRLINDICATOR.
* @datastruct CID_CE_CRLREASONS Identifies CRLREASONS.
* @datastruct CID_CE_CERTIFICATEISSUER Identifies CERTIFICATEISSUER.
* @datastruct CID_CE_HOLDINSTRUCTIONCODE Identifies HOLDINSTRUCTIONCODE.
* @datastruct CID_HOLDINSTRUCTION Identifies HOLDINSTRUCTION.
* @datastruct CID_HOLDINSTRUCTION_NONE Identifies HOLDINSTRUCTION_NONE.
* @datastruct CID_HOLDINSTRUCTION_CALLISSUER Identifies 
            HOLDINSTRUCTION_CALLISSUER.
* @datastruct CID_HOLDINSTRUCTION_REJECT Identifies HOLDINSTRUCTION_REJECT.
* @datastruct CID_CE_INVALIDITYDATE Identifies INVALIDITYDATE.
* @datastruct CID_PDA_DATEOFBIRTH Identifies DATEOFBIRTH.
* @datastruct CID_PDA_PLACEOFBIRTH Identifies PLACEOFBIRTH.
* @datastruct CID_PDA_GENDER Identifies GENDER.
* @datastruct CID_PDA_COUNTRYOFCITIZENSHIP Identifies COUNTRYOFCITIZENSHIP.
* @datastruct CID_PDA_COUNTRYOFRESIDENCE Identifies COUNTRYOFRESIDENCE.
* @datastruct CID_PDA Identifies PDA.
* @datastruct CID_ON_PERMANENTIDENTIFIER Identifies PERMANENTIDENTIFIER.
* @datastruct CID_ON Identifies ON.
* @datastruct CID_CE_DOMAININFO Identifies DOMAININFO.
* @datastruct CID_PASSWORDBASEDMAC Identifies Password Based MAC.
* @datastruct CID_DHBASEDMAC Identifies DH Based MAC.
* @datastruct CID_IT Identifies IT.
* @datastruct CID_CAPROTENCCERT Identifies CAPROTENCCERT.
* @datastruct CID_SIGNKEYPAIRTYPES Identifies Sign KeyPair Types.
* @datastruct CID_ENCKEYPAIRTYPES Identifies KeyPair Types.
* @datastruct CID_PREFERREDSYMMALG Identifies Preferred Symmetric Algo.
* @datastruct CID_CAKEYUPDATEINFO Identifies CA Key Update Info.
* @datastruct CID_CURRENTCRL Identifies Current CRL.
* @datastruct CID_PKIP Identifies PKIP.
* @datastruct CID_REGCTRL Identifies REGCTRL.
* @datastruct CID_REGCTRL_REGTOKEN Identifies REGTOKEN.
* @datastruct CID_REGCTRL_AUTHENTICATOR Identifies AUTHENTICATOR.
* @datastruct CID_REGCTRL_PKIPUBLICATIONINFO Identifies PKIPUBLICATIONINFO.
* @datastruct CID_REGCTRL_PKIARCHIVEOPTIONS Identifies PKIARCHIVEOPTIONS.
* @datastruct CID_REGCTRL_OLDCERTID Identifies OLDCERTID.
* @datastruct CID_REGCTRL_PROTOCOLENCRKEY Identifies PROTOCOLENCRKEY.
* @datastruct CID_REGINFO Identifies REGINFO.
* @datastruct CID_REGINFO_UTF8PAIRS Identifies UTF8PAIRS.
* @datastruct CID_REGINFO_CERTREQ Identifies CERTREQ.
* @datastruct CID_PKCS12 Identifies PKCS12.
* @datastruct CID_PKCS12PBEIDS Identifies PKCS12 PBE.
* @datastruct CID_PBE_SHAWITH128BITRC4 Identifies PBE Algo (SHAWITH128BITRC4).
* @datastruct CID_PBE_SHAWITH40BITRC4 Identifies PBE Algo (SHAWITH40BITRC4).
* @datastruct CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC Identifies PBE Algo
            (SHAWITH3KEY_TRIPLE_DESCBC).
* @datastruct CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC Identifies PBE Algo 
            (SHAWITH2KEY_TRIPLE_DESCBC).
* @datastruct CID_PBE_SHAWITH128BIT_RC2CBC Identifies PBE Algo 
            (SHAWITH128BIT_RC2CBC).
* @datastruct CID_PBE_SHAWITH40BIT_RC2CBC Identifies PBE Algo 
            (SHAWITH40BIT_RC2CBC).
* @datastruct CID_BAGTYPES Identifies Bag Types.
* @datastruct CID_KEYBAG Identifies Key Bag.
* @datastruct CID_PKCS8SHROUDEDKEYBAG Identifies Bag Types.
* @datastruct CID_CERTBAG Identifies CERT Bag.
* @datastruct CID_CRLBAG Identifies CRL Bag.
* @datastruct CID_SECRETBAG Identifies Secret Bag.
* @datastruct CID_SAFECONTENTSBAG Identifies Safe Content Bag.
* @datastruct CID_X509CERTIFICATE Identifies x509 Certificate.
* @datastruct CID_SDSICERTIFICATE Identifies SDSI Certificate.
* @datastruct CID_FRIENDLYNAME Identifies Freidnly Name.
* @datastruct CID_LOCALKEYID Identifies Local Key ID.
* @datastruct CID_CERTIFICATEREVOCATIONLIST Identifies Certificate 
            Revocation List.
* @datastruct CID_PKCS7 Identifies PKCS7.
* @datastruct CID_PKCS7_SIMPLEDATA Identifies PKCS7 Simple Data.
* @datastruct CID_PKCS7_SIGNEDDATA Identifies PKCS7 Signed Data.
* @datastruct CID_PKCS7_ENVELOPEDDATA Identifies PKCS7 Enveloped Data.
* @datastruct CID_PKCS7_SIGNED_ENVELOPEDDATA Identifies PKCS7 Signed 
            Enveloped Data.
* @datastruct CID_PKCS7_DIGESTEDDATA Identifies PKCS7 Degested Data.
* @datastruct CID_PKCS7_ENCRYPTEDDATA Identifies PKCS7 Encrypted Data.
* @datastruct CID_PKCS9 Identifies PKCS9.
* @datastruct CID_PKCS9_AT_CONTENTTYPE Identifies PKCS9 Content Type.
* @datastruct CID_PKCS9_AT_MESSAGEDIGEST Identifies PKCS9 Message Digest.
* @datastruct CID_PKCS9_AT_SIGNINGTIME Identifies PKCS9 Signing time.
* @datastruct CID_PKCS9_AT_COUNTERSIGNATURE Identifies PKCS9 Counter Signature.
* @datastruct CID_PKCS9_AT_RANDOMNONCE Identifies PKCS9 Signed Enveloped Data.
* @datastruct CID_PKCS9_AT_SEQUENCENUMBER Identifies PKCS9 Sequence number.
* @datastruct CID_MD4 Identifies MD4 hash algorithm.
* @datastruct CID_HMAC_MD4 Identifies hmac with MD4.
* @datastruct CID_CMAC_AES Identifies CMAC-AES.
* @datastruct CID_CMAC_TDES Identifies CMAC-Triple DES.
* @datastruct CID_RNG_HW Identifies TRNG.
* @datastruct CID_RNG_SW Identifies PRNG.   
* @datastruct CID_XCBC_AES Identifies XCBC-MAC-AES.
* @datastruct CID_RC2_ECB Identifies RC2 algorithm in ECB mode.
* @datastruct CID_RC2_CBC Identifies RC2 algorithm in CBC mode.
* @datastruct CID_RC2_OFB Identifies RC2 algorithm in OFB mode.
* @datastruct CID_RC2_CFB Identifies RC2 algorithm in CFB mode.
* @datastruct CID_MD5_SHA1 Identifies that hash info should not be considered for sign and verify
* @datastruct CID_SECP384R1 Identifies NIST prime curve 384
* @datastruct CID_SECP521R1 Identifies NIST prime curve 521
* @datastruct CID_SM3 Identifies SM3 hash algorithm
* @datastruct CID_HMAC_SM3 Identifies hmac with SM3
* @datastruct CID_SM2DSAWITHSM3 Identifies SM2DSA with SM3
* @datastruct CID_SM2DSAWITHSHA1 Identifies SM2DSA with SHA1
* @datastruct CID_SM2DSAWITHSHA256 Identifies SM2DSA with SHA256
* @datastruct CID_SM2PRIME256 Identifies SM2 PRIME256 Curve
* @datastruct CID_SM2DSA Identifies SM2 DSA
* @datastruct CID_SM2KEP Identifies SM2 KEP
* @datastruct CID_SM2PKEA Identifies SM2 PKEA
*/

// If new symmetric encryption algo is added then g_AlgTable array and 
// ipsi_algid_to_g_AlgTable_idx() function should be modified accordingly
typedef enum
{
    CID_UNKNOWN, //Unknown alg id

    /* Algorithm Ids from crypto*/

    CID_RC4,    /* identifies the RC4 algorithm */

    CID_DES_ECB, /* identifies DES algorithm in ECB mode */
    CID_DES_CBC, /* identifies DES algorithm in CBC mode */
    CID_DES_OFB, /* identifies DES algorithm in OFB mode */
    CID_DES_CFB, /* identifies DES algorithm in CFB mode */

    CID_SCB2_128_ECB,   /* identifies SCB2-128 algorithm in ECB mode */
    CID_SCB2_128_CBC,   /* identifies SCB2-128 algorithm in CBC mode */

    CID_SCB2_256_ECB,   /* identifies SCB2-256 algorithm in ECB mode */
    CID_SCB2_256_CBC,

    CID_DES_EDE_ECB,    /* identifies 2 key triple DES algorithm in ECB mode */
    CID_DES_EDE_CBC,    /* identifies 2 key triple DES algorithm in CBC mode */
    CID_DES_EDE_OFB,    /* identifies 2 key triple DES algorithm in OFB mode */
    CID_DES_EDE_CFB,    /* identifies 2 key triple DES algorithm in CFB mode */

    CID_DES_EDE3_ECB,   /* identifies 3 key triple DES algorithm in ECB mode */
    CID_DES_EDE3_CBC,   /* identifies 3 key triple DES algorithm in CBC mode */
    CID_DES_EDE3_OFB,   /* identifies 3 key triple DES algorithm in OFB mode */
    CID_DES_EDE3_CFB,   /* identifies 3 key triple DES algorithm in CFB mode */

    CID_AES128_ECB,     /* identifies AES-128 algorithm in ECB mode */
    CID_AES128_CBC,     /* identifies AES-128 algorithm in CBC mode */
    CID_AES128_OFB,     /* identifies AES-128 algorithm in OFB mode */
    CID_AES128_CFB,     /* identifies AES-128 algorithm in CFB mode */

    CID_AES192_ECB,     /* identifies AES-192 algorithm in ECB mode */
    CID_AES192_CBC,     /* identifies AES-192 algorithm in CBC mode */
    CID_AES192_OFB,     /* identifies AES-192 algorithm in OFB mode */
    CID_AES192_CFB,     /* identifies AES-192 algorithm in CFB mode */

    CID_AES256_ECB,     /* identifies AES-256 algorithm in ECB mode */
    CID_AES256_CBC,     /* identifies AES-256 algorithm in CBC mode */
    CID_AES256_OFB,     /* identifies AES-256 algorithm in OFB mode */
    CID_AES256_CFB,     /* identifies AES-256 algorithm in CFB mode */

    CID_KASUMI_ECB,     /* identifies Kasumi algorithm in ECB mode */
    CID_KASUMI_CBC,     /* identifies Kasumi algorithm in CBC mode */
    CID_KASUMI_OFB,     /* identifies Kasumi algorithm in OFB mode */
    CID_KASUMI_CFB,     /* identifies Kasumi algorithm in CFB mode */

    CID_RSA,    /* identifies the RSA algorithm */
    CID_DSA,    /* identifies the DSA algorithm */
    CID_ECDSA,  /* identifies the ECDSA algorithm */
    CID_ECDSA192, /* identifies the ECDSA192 algorithm */
    CID_DH,     /* identifies the Diffie-Hellman algorithm */
    CID_ECDH,   /* identifies the EC Diffie-Hellman algorithm */

    CID_MD5,    /* identifies the MD5 hash algorithm */
    CID_SHA1,   /* identifies the SHA1 hash algorithm */
    CID_SHA224, /* identifies the SHA224 hash algorithm */
    CID_SHA256, /* identifies the SHA256 hash algorithm */
    CID_SHA384, /* identifies the SHA384 hash algorithm */
    CID_SHA512, /* identifies the SHA512 hash algorithm */

    CID_HMAC_MD5,   /* identifies hmac with MD5 */
    CID_HMAC_SHA1,  /* identifies hmac with SHA1 */
    CID_HMAC_SHA224,    /* identifies hmac with SHA224 */
    CID_HMAC_SHA256,    /* identifies hmac with SHA256 */
    CID_HMAC_SHA384,    /* identifies hmac with SHA384 */
    CID_HMAC_SHA512,    /* identifies hmac with SHA512 */

    CID_MD5WITHRSA, /* identifies signature using MD5 and RSA */
    CID_SHA1WITHRSA,    /* identifies signature using SHA1 and RSA */

    /* identifies signature using SHA1 and RSA (coresponds to old Oid)*/
    CID_SHA1WITHRSAOLD, 
    CID_DSAWITHSHA1,    /* identifies signature using SHA1 and DSA */
    CID_DSAWITHSHA1_2,  /* identifies signature using SHA1 and DSA */
    CID_ECDSAWITHSHA1,  /* identifies signature using SHA1 and ECDSA */
    CID_ECDSAWITHSHA224,  /* identifies signature using SHA224 and ECDSA */
    CID_ECDSAWITHSHA256,  /* identifies signature using SHA256 and ECDSA */
    CID_ECDSAWITHSHA384,  /* identifies signature using SHA384 and ECDSA */
    CID_ECDSAWITHSHA512,  /* identifies signature using SHA512 and ECDSA */
    CID_ECDSA192WITHSHA256, /* identifies signature using SHA256 
    and ECDSA-192 bit */

    /* identifies signature using SHA256 and RSA */
    CID_SHA256WITHRSAENCRYPTION,   

    /* identifies signature using SHA384 and RSA */
    CID_SHA384WITHRSAENCRYPTION,    

    /* identifies signature using SHA512 and RSA */
    CID_SHA512WITHRSAENCRYPTION,    
    
    /*RFC 3279 */

    CID_KEYEXCHANGEALGORITHM, /* identifies Key exchange algorithm*/
    CID_PKCS1, /* identifies PKCS1*/ 
    CID_ANSI_X9_62, /* identifies ANSI_X9_62*/
    CID_ECSIGTYPE, /* identifies ECSIGTYPE*/
    CID_FIELDTYPE, /* identifies Field Type */
    CID_PRIME_FIELD, /* identifies PRIME Field*/
    CID_CHARACTERISTIC_TWO_FIELD, /* identifies Characterstic Two field*/
    CID_CHARACTERISTIC_TWO_BASIS, /* identifies Characterstic Two Basis*/
    CID_GNBASIS, /* identifies GNBASIS*/
    CID_TPBASIS, /* identifies TPBASIS*/
    CID_PPBASIS, /* identifies PPBASIS*/
    CID_PUBLICKEYTYPE, /* identifies PUBLICKEYTYPE*/
    CID_ELLIPTICCURVE, /* identifies ELLIPTICCURVE*/
    CID_C_TWOCURVE, /* identifies C_TWOCURVE*/
    CID_C2PNB163V1, /* identifies C2PNB163V1*/
    CID_C2PNB163V2, /* identifies C2PNB163V2*/
    CID_C2PNB163V3, /* identifies C2PNB163V3*/
    CID_C2PNB176W1, /* identifies C2PNB176W1*/
    CID_C2TNB191V1, /* identifies C2TNB191V1*/
    CID_C2TNB191V2, /* identifies C2TNB191V2*/
    CID_C2TNB191V3, /* identifies C2TNB191V3*/
    CID_C2ONB191V4, /* identifies C2ONB191V4*/
    CID_C2ONB191V5, /* identifies C2ONB191V5*/
    CID_C2PNB208W1, /* identifies C2PNB208W1*/
    CID_C2TNB239V1, /* identifies C2TNB239V1*/
    CID_C2TNB239V2, /* identifies C2TNB239V2*/
    CID_C2TNB239V3, /* identifies C2TNB239V3*/
    CID_C2ONB239V4, /* identifies C2ONB239V4*/
    CID_C2ONB239V5, /* identifies C2ONB239V5*/
    CID_C2PNB272W1, /* identifies C2PNB272W1*/
    CID_C2PNB304W1, /* identifies C2PNB304W1*/
    CID_C2TNB359V1, /* identifies C2TNB359V1*/
    CID_C2PNB368W1, /* identifies C2PNB368W1*/
    CID_C2TNB431R1, /* identifies C2TNB431R1*/
    CID_PRIMECURVE, /* identifies PRIMECURVE*/
    CID_PRIME192V1, /* identifies PRIME192V1*/
    CID_PRIME192V2, /* identifies PRIME192V2*/
    CID_PRIME192V3, /* identifies PRIME192V3*/
    CID_PRIME239V1, /* identifies PRIME239V1*/
    CID_PRIME239V2, /* identifies PRIME239V2*/
    CID_PRIME239V3, /* identifies PRIME239V3*/
    CID_PRIME256V1, /* identifies PRIME256V1*/


    /* SCEP */

    CID_VERISIGN, /* identifies VERISIGN*/
    CID_PKI, /* identifies PKI*/
    CID_ATTRIBUTES, /* identifies ATTRIBUTES*/
    CID_MESSAGETYPE, /* identifies MESSAGETYPE*/
    CID_PKISTATUS, /* identifies PKISTATUS*/
    CID_FAILINFO, /* identifies FAILINFO*/
    CID_SENDERNONCE, /* identifies SENDERNONCE*/
    CID_RECIPIENTNONCE, /* identifies RECIPIENTNONCE*/
    CID_TRANSID, /* identifies TRANSID*/
    CID_EXTENSIONREQ, /* identifies EXTENSIONREQ*/

    /* PKCS 5 */

    CID_RSADSI, /* identifies RSADSI*/
    CID_PKCS, /* identifies PKCS*/
    CID_PKCS5, /* identifies PKCS5*/
    CID_PBKDF2, /* identifies PBKDF2*/
    CID_PBE_MD2WITHDESCBC, /* identifies PBE_MD2WITHDESCBC*/
    CID_PBE_MD2WITHRC2CBC, /* identifies PBE_MD2WITHRC2CBC*/
    CID_PBE_MD5WITHDESCBC, /* identifies PBE_MD5WITHDESCBC*/
    CID_PBE_MD5WITHRC2CBC, /* identifies PBE_MD5WITHRC2CBC*/
    CID_PBE_SHA1WITHDESCBC, /* identifies PBE_SHA1WITHDESCBC*/
    CID_PBE_SHA1WITHRC2CBC, /* identifies PBE_SHA1WITHRC2CBC*/
    CID_PBES2, /* identifies PBES2*/
    CID_PBMAC1, /* identifies PBMAC1*/
    CID_DIGESTALGORITHM, /* identifies DIGESTALGORITHM*/
    CID_ENCRYPTIONALGORITHM, /* identifies ENCRYPTIONALGORITHM*/
    CID_RC2CBC, /* identifies RC2CBC*/
    CID_RC5_CBC_PAD, /* identifies RC5_CBC_PAD*/
    CID_RSAES_OAEP,/* from pkcs1 */ /* identifies RSAES_OAEP*/

    /* OCSP */

    CID_PKIX_OCSP_BASIC, /* identifies OCSP_BASIC*/
    CID_PKIX_OCSP_NONCE, /* identifies OCSP_NONCE*/
    CID_PKIX_OCSP_CRL, /* identifies OCSP_CRL*/
    CID_PKIX_OCSP_RESPONSE, /* identifies OCSP_RESPONSE*/
    CID_PKIX_OCSP_NOCHECK, /* identifies OCSP_NOCHECK*/ 
    CID_PKIX_OCSP_ARCHIVE_CUTOFF, /* identifies OCSP_ARCHIVE_CUTOFF*/
    CID_PKIX_OCSP_SERVICE_LOCATOR, /* identifies OCSP_SERVICE_LOCATOR*/

    /* PKCS 10 */

    CID_CHALLENGE_PWD_ATTR, /* identifies Challenge PWD Attr*/
    CID_EXTENSIONREQUEST, /* identifies EXTENSIONREQUEST*/

    /* FROM PKIXEXPLICIT */

    CID_PKIX, /* identifies PKIX*/
    CID_PE, /* identifies PE*/
    CID_QT, /* identifies QT*/
    CID_KP, /* identifies KP*/
    CID_AD, /* identifies AD*/
    CID_QT_CPS, /* identifies CPS*/
    CID_QT_UNOTICE, /* identifies UNOTICE*/
    CID_AD_OCSP, /* identifies OCSP*/
    CID_AD_CAISSUERS, /* identifies CAISSUERS*/
    CID_AD_TIMESTAMPING, /* identifies TIMESTAMPING*/
    CID_AD_CAREPOSITORY, /* identifies CAREPOSITORY*/
    CID_AT, /* identifies AT*/
    CID_AT_NAME, /* identifies NAME*/
    CID_AT_SURNAME, /* identifies SURNAME*/
    CID_AT_GIVENNAME, /* identifies GIVENNAME*/
    CID_AT_INITIALS, /* identifies INITIALS*/
    CID_AT_GENERATIONQUALIFIER, /* identifies GENERATIONQUALIFIER*/
    CID_AT_COMMONNAME, /* identifies COMMONNAME*/
    CID_AT_LOCALITYNAME, /* identifies LOCALITYNAME*/
    CID_AT_STATEORPROVINCENAME, /* identifies STATEORPROVINCENAME*/
    CID_AT_ORGANIZATIONNAME, /* identifies ORGANIZATIONNAME*/
    CID_AT_ORGANIZATIONALUNITNAME, /* identifies ORGANIZATIONALUNITNAME*/
    CID_AT_TITLE, /* identifies TITLE*/
    CID_AT_DNQUALIFIER, /* identifies DNQUALIFIER*/
    CID_AT_COUNTRYNAME, /* identifies COUNTRYNAME*/
    CID_AT_SERIALNUMBER, /* identifies SERIALNUMBER*/
    CID_AT_PSEUDONYM, /* identifies PSEUDONYM*/
    CID_DOMAINCOMPONENT, /* identifies DOMAINCOMPONENT*/
    CID_EMAILADDRESS, /* identifies EMAILADDRESS*/

    /* PKIXIMPLICIT */

    CID_CE, /* identifies CE*/
    CID_CE_AUTHORITYKEYIDENTIFIER, /* identifies AUTHORITYKEYIDENTIFIER*/
    CID_CE_SUBJECTKEYIDENTIFIER, /* identifies SUBJECTKEYIDENTIFIER*/
    CID_CE_KEYUSAGE, /* identifies KEYUSAGE*/
    CID_CE_PRIVATEKEYUSAGEPERIOD, /* identifies PRIVATEKEYUSAGEPERIOD*/
    CID_CE_CERTIFICATEPOLICIES, /* identifies CERTIFICATEPOLICIES*/
    CID_ANYPOLICY, /* identifies ANYPOLICY*/
    CID_CE_POLICYMAPPINGS, /* identifies POLICYMAPPINGS*/
    CID_CE_SUBJECTALTNAME, /* identifies SUBJECTALTNAME*/
    CID_CE_ISSUERALTNAME, /* identifies ISSUERALTNAME*/
    CID_CE_SUBJECTDIRECTORYATTRIBUTES,/*identifies SUBJECTDIRECTORYATTRIBUTES*/
    CID_CE_BASICCONSTRAINTS, /* identifies BASICCONSTRAINTS*/
    CID_CE_NAMECONSTRAINTS, /* identifies NAMECONSTRAINTS*/
    CID_CE_POLICYCONSTRAINTS, /* identifies POLICYCONSTRAINTS*/
    CID_CE_CRLDISTRIBUTIONPOINTS, /* identifies CRLDISTRIBUTIONPOINTS*/
    CID_CE_EXTKEYUSAGE, /* identifies EXTKEYUSAGE*/
    CID_ANYEXTENDEDKEYUSAGE, /* identifies ANYEXTENDEDKEYUSAGE*/
    CID_KP_SERVERAUTH, /* identifies SERVERAUTH*/
    CID_KP_CLIENTAUTH, /* identifies CLIENTAUTH*/
    CID_KP_CODESIGNING, /* identifies CODESIGNING*/
    CID_KP_EMAILPROTECTION, /* identifies EMAILPROTECTION*/
    CID_KP_TIMESTAMPING, /* identifies TIMESTAMPING*/
    CID_KP_OCSPSIGNING, /* identifies OCSPSIGNING*/
    CID_KP_IPSECIKE, /*identifies IPSECIKE */
    CID_CE_INHIBITANYPOLICY, /* identifies INHIBITANYPOLICY*/
    CID_CE_FRESHESTCRL, /* identifies FRESHESTCRL*/
    CID_PE_AUTHORITYINFOACCESS, /* identifies AUTHORITYINFOACCESS*/
    CID_PE_SUBJECTINFOACCESS, /* identifies SUBJECTINFOACCESS*/
    CID_CE_CRLNUMBER, /* identifies CRLNUMBER*/
    CID_CE_ISSUINGDISTRIBUTIONPOINT, /* identifies ISSUINGDISTRIBUTIONPOINT*/
    CID_CE_DELTACRLINDICATOR, /* identifies DELTACRLINDICATOR*/
    CID_CE_CRLREASONS, /* identifies CRLREASONS*/ 
    CID_CE_CERTIFICATEISSUER, /* identifies CERTIFICATEISSUER*/
    CID_CE_HOLDINSTRUCTIONCODE, /* identifies HOLDINSTRUCTIONCODE*/
    CID_HOLDINSTRUCTION, /* identifies HOLDINSTRUCTION*/
    CID_HOLDINSTRUCTION_NONE, /* identifies HOLDINSTRUCTION_NONE*/
    CID_HOLDINSTRUCTION_CALLISSUER, /* identifies HOLDINSTRUCTION_CALLISSUER*/
    CID_HOLDINSTRUCTION_REJECT, /* identifies HOLDINSTRUCTION_REJECT*/
    CID_CE_INVALIDITYDATE, /* identifies INVALIDITYDATE*/
    CID_PDA_DATEOFBIRTH, /* identifies DATEOFBIRTH*/
    CID_PDA_PLACEOFBIRTH, /* identifies PLACEOFBIRTH*/
    CID_PDA_GENDER, /* identifies GENDER*/
    CID_PDA_COUNTRYOFCITIZENSHIP, /* identifies COUNTRYOFCITIZENSHIP*/
    CID_PDA_COUNTRYOFRESIDENCE, /* identifies COUNTRYOFRESIDENCE*/
    CID_PDA, /* identifies PDA*/
    CID_ON_PERMANENTIDENTIFIER,  /* identifies PERMANENTIDENTIFIER*/
    CID_ON, /* identifies ON*/
    CID_CE_DOMAININFO, /* identifies DOMAININFO*/

    /* CMP */

    CID_PASSWORDBASEDMAC, /* identifies PWD Based MAC*/
    CID_DHBASEDMAC, /* identifies DH Based MAC*/
    CID_IT, /* identifies IT*/
    CID_CAPROTENCCERT, /* identifies CAPROTENCCERT*/
    CID_SIGNKEYPAIRTYPES, /* identifies Sign KeyPair Types*/
    CID_ENCKEYPAIRTYPES, /* identifies KeyPair Types*/
    CID_PREFERREDSYMMALG, /* identifies Preferred Symmetric Algo*/
    CID_CAKEYUPDATEINFO, /* identifies CA Key Update Info*/
    CID_CURRENTCRL, /* identifies Current CRL*/
    CID_CONFIRMWAITTIME, /*identifies ConfirmWaitTime*/

    /*CRMF*/

    CID_PKIP, /* identifies PKIP*/
    CID_REGCTRL, /* identifies REGCTRL*/
    CID_REGCTRL_REGTOKEN, /* identifies REGTOKEN*/
    CID_REGCTRL_AUTHENTICATOR, /* identifies AUTHENTICATOR*/
    CID_REGCTRL_PKIPUBLICATIONINFO, /* identifies PKIPUBLICATIONINFO*/
    CID_REGCTRL_PKIARCHIVEOPTIONS, /* identifies PKIARCHIVEOPTIONS*/
    CID_REGCTRL_OLDCERTID, /* identifies OLDCERTID*/
    CID_REGCTRL_PROTOCOLENCRKEY, /* identifies PROTOCOLENCRKEY*/
    CID_REGINFO, /* identifies REGINFO*/
    CID_REGINFO_UTF8PAIRS, /* identifies UTF8PAIRS*/
    CID_REGINFO_CERTREQ, /* identifies CERTREQ*/

    /* PKCS12 */

    CID_PKCS12, /* identifies PKCS12*/
    CID_PKCS12PBEIDS, /* identifies PKCS12 PBE*/
    CID_PBE_SHAWITH128BITRC4, /* identifies PBE Algo (SHAWITH128BITRC4)*/
    CID_PBE_SHAWITH40BITRC4, /* identifies PBE Algo (SHAWITH40BITRC4)*/

    /* identifies PBE Algo (SHAWITH3KEY_TRIPLE_DESCBC)*/
    CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC, 

    /* identifies PBE Algo (SHAWITH2KEY_TRIPLE_DESCBC)*/
    CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC, 

    /* identifies PBE Algo (SHAWITH128BIT_RC2CBC)*/
    CID_PBE_SHAWITH128BIT_RC2CBC, 
    CID_PBE_SHAWITH40BIT_RC2CBC, /* identifies PBE Algo (SHAWITH40BIT_RC2CBC)*/
    CID_BAGTYPES, /* identifies Bag Types*/
    CID_KEYBAG, /* identifies Key Bag*/
    CID_PKCS8SHROUDEDKEYBAG, /* identifies Bag Types*/
    CID_CERTBAG, /* identifies CERT Bag*/    
    CID_CRLBAG, /* identifies CRL Bag*/ 
    CID_SECRETBAG, /* identifies Secret Bag*/
    CID_SAFECONTENTSBAG, /* identifies Safe Content Bag*/
    CID_X509CERTIFICATE, /* identifies x509 Certificate*/
    CID_SDSICERTIFICATE, /* identifies SDSI Certificate*/
    CID_FRIENDLYNAME, /* identifies Freidnly Name*/
    CID_LOCALKEYID, /* identifies Local Key ID*/

    /* auth_frame*/

    CID_CERTIFICATEREVOCATIONLIST, /* identifies Certificate Revocation List*/


    /*PKCS7 & 9*/

    CID_PKCS7, /* identifies PKCS7 */
    CID_PKCS7_SIMPLEDATA, /* identifies PKCS7 Simple Data*/
    CID_PKCS7_SIGNEDDATA, /* identifies PKCS7 Signed Data*/
    CID_PKCS7_ENVELOPEDDATA, /* identifies PKCS7 Enveloped Data*/
    CID_PKCS7_SIGNED_ENVELOPEDDATA, /* identifies PKCS7 Signed Enveloped Data*/
    CID_PKCS7_DIGESTEDDATA, /* identifies PKCS7 Degested Data*/
    CID_PKCS7_ENCRYPTEDDATA, /* identifies PKCS7 Encrypted Data*/


    CID_PKCS9, /* identifies PKCS9 */
    CID_PKCS9_AT_CONTENTTYPE, /* identifies PKCS9 Content Type*/
    CID_PKCS9_AT_MESSAGEDIGEST, /* identifies PKCS9 Message Digest*/
    CID_PKCS9_AT_SIGNINGTIME, /* identifies PKCS9 Signing time*/
    CID_PKCS9_AT_COUNTERSIGNATURE, /* identifies PKCS9 Counter Signature*/
    CID_PKCS9_AT_RANDOMNONCE, /* identifies PKCS9 Signed Enveloped Data*/
    CID_PKCS9_AT_SEQUENCENUMBER, /* identifies PKCS9 Sequence number*/

    /* Additional Algorithms provided by crypto */
    CID_MD4,    /* identifies MD4 hash algorithm */
    CID_HMAC_MD4,   /* identifies hmac with MD4 */  
    CID_CMAC_AES,   /* identifies CMAC-AES*/    
    CID_CMAC_TDES,  /* identifies CMAC-Triple DES*/
    CID_RNG_HW,     /* identifies TRNG */
    CID_RNG_SW,      /* identifies PRNG*/    
    CID_XCBC_AES,   /* identifies XCBC-MAC-AES*/    

    CID_RC2_ECB,         /* identifies RC2 algorithm in ECB mode */
    CID_RC2_CBC,         /* identifies RC2 algorithm in CBC mode */
    CID_RC2_OFB,         /* identifies RC2 algorithm in OFB mode */
    CID_RC2_CFB,         /* identifies RC2 algorithm in CFB mode */

    // added for ssl special case in which hash info is not added 
    // in the signature.
    CID_MD5_SHA1,

    CID_SECP384R1, /*identifies NIST prime curve 384*/
    CID_SECP521R1, /*identifies NIST prime curve 521*/

    CID_SM3,  /* identifies SM3 hash algorithm */
    CID_HMAC_SM3,   /* identifies hmac with SM3 */ 

    CID_SM2DSAWITHSM3, /*identifies CID_SM2DSAWITHSM3*/
    CID_SM2DSAWITHSHA1, /*identifies CID_SM2DSAWITHSHA1*/
    CID_SM2DSAWITHSHA256, /*identifies CID_SM2DSAWITHSHA256*/
    CID_SM2PRIME256, /* identifies CID_PRIME256SM2*/
    CID_SM2DSA, /*identifies SM2 DSA*/
    CID_SM2KEP, /*CID_SM2KEP*/
    CID_SM2PKEA, /*CID_SM2PKEA*/

    CID_AES128_GCM, /* Identifies the AES128 algorithm in GCM mode */
    CID_AES192_GCM, /* Identifies the AES128 algorithm in GCM mode */
    CID_AES256_GCM, /* Identifies the AES256 algorithm in GCM mode */
    CID_AES128_CTR, /* Identifies the AES128 algorithm in CTR mode */
    CID_AES192_CTR, /* Identifies the AES128 algorithm in CTR mode */
    CID_AES256_CTR, /* Identifies the AES128 algorithm in CTR mode */

    CID_UNSTRUCTURED_NAME, /* identifies unstructuredName */
    
    CID_UNSTRUCTURED_ADDR,  /* identifies unstructuredAddress */
    

    CID_BF_ECB,  /* Identifies the Blowfish algorithm in ECB mode */
    CID_BF_CBC,  /* Identifies the Blowfish algorithm in CBC mode */
    CID_BF_CFB,   /* Identifies the Blowfish algorithm in CFB mode */ 
    CID_BF_OFB   /* Identifies the Blowfish algorithm in OFB mode */

    
    // If new symmetric encryption algo is added then g_AlgTable array and 
    // ipsi_algid_to_g_AlgTable_idx() function should be modified accordingly


}SEC_CID_E;


#define SEC_ALGID_E SEC_CID_E


/* logging error if in debug mode */
typedef SEC_UINT32 SEC_ERROR_CODE;

/*
    Func Name:  SEC_getErrorText
*/

/**
* @defgroup SEC_getErrorText
* @ingroup sec_sysFunctions
* @par Prototype
* @code
* SEC_CHAR* SEC_getErrorText(SEC_ERROR_CODE ulErrorNo);
* @endcode
*
* @par Purpose
* This is used to get error string using error number.
*
* @par Description
* SEC_getErrorText function gets error string using error number. 
    For example, when the function is called for error
* SEC_ERR_MALLOC_FAIL, the function returns pointer to string 
    "Memory allocation failed".
*
* @param[in] ulErrorNo Error number [N/A]
*
* @retval SEC_CHAR* Pointer to character array [Error message|N/A]
*
* @par Required Header File
* sec_sys.h
*
* @par Note
* \n
* N/A
*
* @par Related Topic
* N/A
*/

CRYPTOLINKDLL SEC_CHAR* SEC_getErrorText(SEC_ERROR_CODE ulErrorNo);

/*
    Func Name:  SEC_memCalloc
*/

/**
* @defgroup SEC_memCalloc
* @ingroup sec_sysFunctions
* @par Prototype
* @code
* void* SEC_memCalloc(SEC_UINT32 ulNumOfElmnts,SEC_UINT32 ulSizeOfElmnt);
* @endcode
*
* @par Purpose
* This is used to get memory allocation.
*
* @par Description
* SEC_memCalloc function gets memory allocation through calloc.
*
* @param[in] ulNumOfElmnts Number of elements [N/A]
* @param[in] ulSizeOfElmnt Size of each element [N/A]
*
* @retval void* Pointing to the allocated memory [Pointer to the 
    allocated memory|N/A]
* @retval void* If memory allocation fails [SEC_NULL|N/A]
*
* @par Required Header File
* sec_sys.h
*
* @par Note
* \n
* N/A
*
* @par Related Topic
* N/A
*/

CRYPTOLINKDLL void* SEC_memCalloc(SEC_UINT32 ulNumOfElmnts,
SEC_UINT32 ulSizeOfElmnt);

#define SEC_DEBUG_OFF   0
#define SEC_DEBUG_ON    1

/*This macro is used for report error.On the basis of errno it logs 
filename,line no,errorno */ 
#ifndef __IPSI_NO_CRYPTO_LOG__
#define SEC_REPORT_ERROR(ulErrorNo) \
        SEC_reportError(__FILE__,__LINE__,ulErrorNo,0,SEC_NULL)
#else
#define SEC_REPORT_ERROR(ulErrorNo)
#endif


/* TO DO : As now only DOPRA1.6 has been taken care in OSAL.
 * Need to implement for other versions also which we support
 * And also, PID is mentioned as directly as 1 in OSAL DOPRA
 * implementation. But some customers want to register PID
 * themselves. One way we can follow is we can add one macro
 * internally to disable PID or enable it so that customer 
 * can choose one */

/* This macro is used to allocate memory */
#define SEC_MEM_ALLOC(ulSizeOfMemBlock) \
    ((ulSizeOfMemBlock > 0)? SEC_memCalloc(1, ulSizeOfMemBlock) :SEC_NULL)

/* This macro is used to free memory */
#define SEC_MEM_FREE(pAddr)                 \
((SEC_NULL != (pAddr))?( ipsi_free(pAddr), (pAddr) = NULL ,\
SEC_SUCCESS) : SEC_SUCCESS)

/* This macro is used to Allocate  memory */
#define SEC_MEM_CALLOC(ulNumOfElmnts,ulSizeOfElmnt) \
((ulSizeOfElmnt>0)?SEC_memCalloc(ulNumOfElmnts,ulSizeOfElmnt):SEC_NULL)

/* This macro should be used to free the EC para created by the
 * APIs CRYPT_createECParamsById or CRYPT_createECParamsById_ex */
#define IPSI_EC_PARA_FREE(pEcPara) \
if (SEC_NULL != pEcPara) \
{ \
    if (SEC_NULL != pEcPara->pCoFactor) \
    { \
        ipsi_free(pEcPara->pCoFactor); \
        pEcPara->pCoFactor = NULL; \
    } \
    ipsi_free(pEcPara); \
    pEcPara = NULL; \
}


/*
    Func Name:  SEC_reportError
*/

/** 
* @defgroup SEC_reportError
* @ingroup sec_sysFunctions
* @par Prototype
* @code
* SEC_VOID SEC_reportError(SEC_CHAR* pucFileName,SEC_UINT ulLineNum,
SEC_UINT32 uiErrorNo,
* SEC_UINT uiParaLen, SEC_VOID* pPara);
* @endcode
*
* @par Purpose
* This is used to log the error.
*
* @par Description
* SEC_reportError function logs the error. If the user of crypto 
library wants to log any errors, this function can
* be called with file name, line number, error number, error text 
to be logged along with error text length as parameters.
*
* @param[in] pucFileName File name [N/A]
* @param[in] ulLineNum Line number [N/A]
* @param[in] uiErrorNo Error number [N/A]
* @param[in] uiParaLen Para len [N/A]
* @param[in] pPara Pointer to para [N/A]
*
* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Required Header File
* sec_sys.h
*
* @par Note
* \n
* N/A
*
* @par Related Topic
* N/A
*/
CRYPTOLINKDLL SEC_VOID SEC_reportError(SEC_CHAR* pucFileName,
SEC_UINT ulLineNum,SEC_UINT32 uiErrorNo,SEC_UINT uiParaLen, SEC_VOID* pPara);




/*
    Func Name:  SEC_getCryptoErrorText
*/

/** 
* @defgroup SEC_getCryptoErrorText
* @ingroup sec_sysFunctions
* @par Prototype
* @code
* SEC_CHAR* SEC_getCryptoErrorText(SEC_ERROR_CODE ulErrorNo);
* @endcode
*
* @par Purpose
* This is used to get error string using error number.
*
* @par Description
* SEC_getCryptoErrorText function gets error string using error number.
For Example: When the function is called for
* error SEC_ERR_MALLOC_FAIL, the functions return pointer to string 
"Memory allocation failed".
*
* @param[in] ulErrorNo Crypto error [N/A]
*
* @retval SEC_CHAR* Pointer to the text [Error message|N/A]
*
* @par Required Header File
* sec_sys.h
*
* @par Note
* \n
* N/A
*
* @par Related Topic
* N/A
*/


CRYPTOLINKDLL SEC_CHAR* SEC_getCryptoErrorText(SEC_ERROR_CODE ulErrorNo);

#ifdef  __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _SEC_SEC_H */

