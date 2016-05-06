/*

                Copyright 2005, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

------------------------------------------------------------------------------

                              pkcs12.h

  Project Code: SeCert
  Module Name: pkcs12
  Version      :1
  Date Created: 2005-06-30
  Author: Vinay Purohit
  Description:  This module provides facility to construct a PFX which is
           used  to exchange the  basic infomation i.e. certificate CRL ,
            Private Key Information etc. It supports four modes for exchanging
        the information two for Privacy of the information
        1. Pasword Privacy Mode
           2. Public Key Privacy Mode
            and Two for integrity of the information
        1. Pasword Integrity Mode
           2. Public Key Integrity Mode
        It also allows user to change the Password Of the PFX File
*/

#include "ipsi_pse_build_conf.h"

#ifndef   _IPSI_PKCS12_H
#define   _IPSI_PKCS12_H

#include "pkcs7.h"
#include "pkcs8.h"

#include "sec_list.h"
#include "x509_basictypes.h"
#include "asn-types.h"
#include "sec_sys.h"
#include "sec_crypto.h"
#include "ipsi_types.h"

#ifdef    __cplusplus
extern  "C"{
#endif


#define PKCS12_PFX_VERSION 3 /*! version of the PFX */
#define WITH_TLV            1
#define DERKEY_SHA1_LENGTH  20
#define PKCS12_MAC_ITER     1000

/** @defgroup pkcs12
* This section contains the pkcs12 Enums, Structures, and Functions.
*/

/** @defgroup pkcs12Enums
* @ingroup pkcs12
* This section contains the pkcs12 Enums.
*/

/*
Enum to indicate the integrity mode of the PFX PDU
*/
/**
* @defgroup PKCS12_INTEGRITY_MODE_E
* @ingroup pkcs12Enums
* @par Prototype
* @code
* typedef enum enPKCS12_INTEGRITY_MODE
* {
* PKCS12_PUBKEY_SIGN =0,
* PKCS12_PASS_SIGN,
* PKCS12_UNSUPPORTED_INTEGRATED_MODE
* } PKCS12_INTEGRITY_MODE_E;
* @endcode
*
* @datastruct PKCS12_PUBKEY_SIGN=0 For public Key Sign Mode.
* @datastruct PKCS12_PASS_SIGN For password Sign Mode.
* @datastruct PKCS12_UNSUPPORTED_INTEGRATED_MODE For unsupported Sign Mode.
*/
typedef enum enPKCS12_INTEGRITY_MODE
{
    PKCS12_PUBKEY_SIGN = 0,          /* for public Key Sign Mode */
    PKCS12_PASS_SIGN,               /* for password Sign Mode */
    PKCS12_UNSUPPORTED_INTEGRATED_MODE /* for unsupported Sign Mode */
} PKCS12_INTEGRITY_MODE_E;

/*Enum to indicate the privacy mode of the PFX PDU */
/**
* @defgroup PKCS12_PRIVACY_MODE_E
* @ingroup pkcs12Enums
* @par Prototype
* @code
* typedef enum enPKCS12_PRIVACY_MODE
* {
* PKCS12_PLAIN_PRIVACY=0,
* PKCS12_PUBKEY_PRIVACY,
* PKCS12_PASS_PRIVACY,
* PKCS12_UNSUPPORTED_PRIVACY_MODE
* } PKCS12_PRIVACY_MODE_E;
* @endcode
*
* @datastruct PKCS12_PLAIN_PRIVACY=0 For plain privacy Mode.
* @datastruct PKCS12_PUBKEY_PRIVACY For encrypted privacy Mode.
* @datastruct PKCS12_PASS_PRIVACY For password privacy Mode.
* @datastruct PKCS12_UNSUPPORTED_PRIVACY_MODE For unsupported privacy Mode.
*/
typedef enum enPKCS12_PRIVACY_MODE
{
    PKCS12_PLAIN_PRIVACY = 0,         /* for plain privacy Mode */
    PKCS12_PUBKEY_PRIVACY,          /* for encrypted privacy Mode */
    PKCS12_PASS_PRIVACY,            /* for password privacy Mode */
    PKCS12_UNSUPPORTED_PRIVACY_MODE /* for unsupported privacy Mode */
} PKCS12_PRIVACY_MODE_E;

/** @defgroup pkcs12Structures
* @ingroup pkcs12
* This section contains the pkcs12 Structures.
*/

/* Structure to Hold the MAC Data used for verifying integrity
                                 in password integrity mode */
/**
* @defgroup PKCS12_MACDATA_S
* @ingroup pkcs12Structures
* @par Prototype
* @code
* typedef struct stPKCS12_MACDATA
* {
* PKCS7_DIGEST_INFO_S* pstMAC;
* SEC_AsnOcts_S        stMacSalt;
* SEC_UINT32*          pIterations;
* } PKCS12_MACDATA_S;
* @endcode
*
* @datastruct pstMAC PKCS7-DigestInfo-S. It is used to store 
the Digest Information of PKCS12 Authenticated Safe.
* @datastruct stMacSalt OCTET STRING contains Salt and Salt Length.
* @datastruct pIterations INTEGER holds iteration count.
*/
typedef struct stPKCS12_MACDATA /* SEQUENCE */
{
    PKCS7_DIGEST_INFO_S* pstMAC; /* PKCS7-DigestInfo-S . It is used to
                   store the Digest Information of PKCS12 Authenticated Safe*/
    SEC_AsnOcts_S stMacSalt; /* OCTET STRING contains Salt and Salt Length*/
    SEC_UINT32* pIterations; /* INTEGER holds iteration count */
} PKCS12_MACDATA_S;

/*
Structure to hold the type and encoded value of certificate crl or any kind of 
encoded Data.
This structure will be put into the PKCS12 Safe Bag.
*/
/**
* @defgroup PKCS12_BAG_S
* @ingroup pkcs12Structures
* @par Prototype
* @code
* typedef struct stPKCS12_BAG
* {
* SEC_AsnOid_S type;
* union
* {
* SEC_AsnOcts_S   x509cert;
* SEC_AsnOcts_S   x509crl;
* SEC_IA5String_S sdsicert;
* SEC_AsnOcts_S   octet;
* }value;
*
* }PKCS12_BAG_S;
* @endcode
*
* @datastruct type Type of the bag it can be anything certificate,
crl,or encoded data.
* @datastruct x509cert DER-encoded X.509 certificate stored in OCTET STRING.
* @datastryct x509crl DER-encoded X.509 CRL stored in OCTET STRING.
* @datastruct sdsicert Base64-encoded SDSI certificate stored in IA5String,
not supported in this version.
* @datastruct octet Used to store secretbag, actually it needn't to support now.
*/
typedef struct stPKCS12_BAG
{
    SEC_AsnOid_S type; /* type of the bag it can be anything
    certificate,crl,or encoded data */
    union
    {
        SEC_AsnOcts_S x509cert;  /* DER-encoded X.509 certificate stored in
                                                      OCTET STRING */
        SEC_AsnOcts_S x509crl;    /* DER-encoded X.509 CRL stored in
                                                      OCTET STRING  */
        SEC_IA5String_S sdsicert;  /* Base64-encoded SDSI certificate stored
                                                       in IA5String,
                                            not supported in this version */
        SEC_AsnOcts_S octet;        /* used to store secretbag, actually it
                                                     needn't to support  now. */
    }value;

}PKCS12_BAG_S;

/*
 Structure of Safe bag to hold any kind of Bag . certificate ,crl or secret bag
 along with the type of the Bag
*/
/**
* @defgroup PKCS12_SAFEBAG_S
* @ingroup pkcs12Structures
* @par Prototype
* @code
* typedef struct stPKCS12_SAFEBAG
* {
* SEC_AsnOid_S bagId;
* SEC_AsnAny_S bagValue;
* SEC_List_S*  bagAttributes;
* } PKCS12_SAFEBAG_S;
* @endcode
*
* @datastruct bagId OBJECT IDENTIFIER of a Bag.
* @datastruct bagValue ANY DEFINED BY bagId.
* @datastruct bagAttributes List Of bag Attribute which
can be either LOCALID or FriendlyID.
*/
typedef struct stPKCS12_SAFEBAG /* SEQUENCE */
{
    SEC_AsnOid_S bagId; /* OBJECT IDENTIFIER of a Bag */
    SEC_AsnAny_S bagValue; /* ANY DEFINED BY bagId */
    SEC_List_S* bagAttributes; /* List Of bag Attribute which
    can be either LOCALID or FriendlyID */
} PKCS12_SAFEBAG_S;


/*
Structure to hold the PFX Data inside along with the optional
MAC field which will be used for integrity
*/
/**
* @defgroup PKCS12_PFX_S
* @ingroup pkcs12Structures
* @par Prototype
* @code
* typedef struct stPKCS12_PFX
* {
* SEC_UINT32        version;
* PKCS7_MSG_S*      authSafe;
* PKCS12_MACDATA_S* macData;
* } PKCS12_PFX_S;
* @endcode
*
* @datastruct version Version of the PKCS12_PFX_S structure.
* @datastruct authSafe PKCS7_MSG_S ,authsafe
which will be either simple Data or Signed Data.
* @datastruct macData MacData OPTIONAL is
used for Password integrity verification.
*/
typedef struct stPKCS12_PFX /* SEQUENCE */
{
    SEC_UINT32 version; /* Version of the PKCS12_PFX_S structure */
    PKCS7_MSG_S* authSafe; /* PKCS7_MSG_S ,authsafe which
                                      will be either
                    simple Data or Signed Data */
    PKCS12_MACDATA_S* macData; /* MacData OPTIONAL is used
                         for Password integrity verification */
} PKCS12_PFX_S;

typedef SEC_List_S PKCS12_BAGLIST_S; /* SEQUENCE OF
                                        SafeBag contains certificate, crl etc*/
typedef SEC_List_S PKCS12_AUTHSAFE_S; /* SEQUENCE OF PKCS7_MSG_S */
typedef SEC_List_S PKCS12_SafeBagSetOf_S;      /* SET OF PKCS12 Attribute in
                                                  PKCS12_SAFEBAG_S */

/** @defgroup pkcs12Functions
* @ingroup pkcs12
* This section contains the pkcs12 Functions.
*/


/**
* @defgroup PKCS12_certToSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_SAFEBAG_S* PKCS12_certToSafeBag (X509_CERT_S* pstCert);
* @endcode
*
* @par Purpose
* To add an X509 certificate to a new PKCS12 safe bag.
*
* @par Description
* This function creates Safe Bag and adds the given X509 certificate into it.
* It first creates a PKCS12_BAG_S and then puts the same
* to the PKCS12_SAFEBAG_S.
*
* @param[in] pstCert Certificate structure which holds the
* certificate. To create certificate call X509_createCert. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_SAFEBAG_S* Pointer to PKCS12_SAFEBAG_S structure which contains
* the given X509 certificate inside it. [PKCS12_SAFEBAG_S*|N/A]
* @retval PKCS12_SAFEBAG_S* If an error occurs during following scenarios:\n
* Memory allocation fails\n
* Duplicate for input parameters fail\n
* Copy for OID fails\n
* Encode for certificate fails [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the safe bag, to free this memory
* application has to call the PKCS12_freeSafeBAG.
*
* @par Note
*
* 1. This safe bag is used to store the certificate in PFX format.\n
* 2. It creates the bag first and puts it into the Safe Bag.
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_SAFEBAG_S* PKCS12_certToSafeBag (X509_CERT_S* pstCert);



/**
* @defgroup PKCS12_crlToSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_SAFEBAG_S *  PKCS12_crlToSafeBag(X509_CRL_S* pstCRL);
* @endcode
*
* @par Purpose
* To add the given X509 CRL to a new PKCS12 Safe Bag.
*
* @par Description
* This function creates Safe Bag and adds X509 CRL into it.
* It first creates a PKCS12_BAG_S and then adds the same to
* the PKCS12_SAFEBAG_S.
*
* @param[in] pstCRL CRL Structure which holds the X509 CRL.
* To create X509_CRL_S call X509CRL_create. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_SAFEBAG_S * Pointer to Safe Bag structure
 which holds the X509 CRL. [PKCS12_SAFEBAG_S *|N/A]
* @retval PKCS12_SAFEBAG_S * If an error occurs during
one of the following scenarios:\n
* Memory allocation failed\n
* Dup for input parameters failed\n
* Copy of OID failed\n
* X509 CRL encode failed [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the safe bag, to free this memory
* application has to call the PKCS12_freeSafeBAG.
*
* @par Note
*
* 1. This safe bag is used to store the CRL in PFX format.\n
* 2. It creates the bag first and puts it into the Safe Bag.
*
* @par Related Topics
* N/A
*
*/

PSELINKDLL PKCS12_SAFEBAG_S *  PKCS12_crlToSafeBag(X509_CRL_S* pstCRL);



/**
* @defgroup PKCS12_dataToSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_SAFEBAG_S * PKCS12_dataToSafeBag (SEC_UCHAR* pucEncodedData,
                                             SEC_UINT32 uiLen);
* @endcode
*
* @par Purpose
* To add the given encoded data to a new PKCS12 safe bag.
*
* @par Description
* This function creates a PKCS12 Safe Bag and adds the input data into it.
* The data here is the encoded secret Bag.
* It first creates a PKCS12_BAG_S and then puts
   the same to the PKCS12_SAFEBAG_S.
*
* @param[in] pucEncodedData Encoded data for
    which Safe Bag has to be formed. [N/A]
* @param[in] uiLen Length of the encoded data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_SAFEBAG_S* Pointer to
Safe Bag structure which hold the data to be
* stored in the PFX format. [PKCS12_SAFEBAG_S*|N/A]
* @retval PKCS12_SAFEBAG_S* If an error occurs
during one of the following scenarios:\n
* Memory allocation fails\n
* Dup of input parameters fail\n
* Copy of OID fails\n [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the safe bag, to free this memory
* application has to call the PKCS12_freeSafeBAG.
*
* @par Note
*
* 1. This safe bag is used to store any kind of data in PFX format.\n
* 2. The data should be encoded information.
*
* @par Related Topics
* N/A
*
*/
PSELINKDLL  PKCS12_SAFEBAG_S *   PKCS12_dataToSafeBag (
                           SEC_UCHAR* pucEncodedData, SEC_UINT32 uiLen);



/**
* @defgroup PKCS12_addAttrToSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UINT32    PKCS12_addAttrToSafeBag(
PKCS12_SAFEBAG_S *pstSafeBag, SEC_ATTR_S* pstAttr);
* @endcode
*
* @par Purpose
* To add the PKCS12 Attribute structure to the given PKCS12 Safe bag.
*
* @par Description
* This function adds PKCS12 SEC_ATTR_S to a Safe Bag. Safe Bag could be any
* type of the Safe Bag i.e Private Key Safe Bag.
*
* @param[in] pstSafeBag Safe Bag in which  SEC_ATTR_S is to be added
* @param[in] pstAttr Pointer to SEC_ATTR_S to add into the Safe Bag which can
*                     be either LocalID(CID_LOCALKEYID) or
                                     FriendlyID(CID_FRIENDLYNAME).
*                   To create SEC_ATTR_S call PKCS12_createAttribute
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 in case attribute is added
successfully to the safe bag. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 In case of failure of duplicate operation of attribute.
[SEC_ERR_BUF_COPY_FAILED|N/A]
* @retval SEC_UINT32 If the list new or list add operation fails.
[SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 If any of the input is NULL. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* 1. This safe bag is used to store any kind of data in PFX format.\n
* 2. The data should be encoded information.
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_UINT32  PKCS12_addAttrToSafeBag(
     PKCS12_SAFEBAG_S *pstSafeBag, SEC_ATTR_S* pstAttr);



/**
* @defgroup PKCS12_createAttribute
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_ATTR_S* PKCS12_createAttribute(
SEC_UINT32 uiTypeAttr, SEC_AsnOcts_S* pstValue);
* @endcode
*
* @par Purpose
* To create a new PKCS12 Attribute structure with the given parameters.
*
* @par Description
* This function creates PKCS12 attribute
which could be either friendlyID or LocalID.
*
* @param[in] uiTypeAttr Type of the PKCS12 Attribute.
* It Could Be either LocalKeyId(CID_LOCALKEYID)
Or Friendly Name (CID_FRIENDLYNAME) [N/A]
* @param[in] pstValue   value of the SEC_ATTR_S (Only one is supported)
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ATTR_S* Pointer to PKCS12 Attribute which hold the value and type
* of the attribute. [SEC_ATTR_S*|N/A]
* @retval SEC_ATTR_S* If an error occurs during following scenarios:\n
* Memory allocation fails\n
* Dup for input parameters fails\n
* Copy for OID fails\n
* CIDs are not correct\n
* Any of the List operation fails [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the attribute, to free this memory
* application has to call the X509_freeAttribute.
*
* @par Note
*
* Type can be any of the LocalID or Friendly name.
*
* @par Related Topics
* N/A
*
*/

PSELINKDLL  SEC_ATTR_S* PKCS12_createAttribute(
  SEC_UINT32 uiTypeAttr, SEC_AsnOcts_S* pstValue);



/**
* @defgroup PKCS12_getAttributeVal
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* PKCS12_getAttributeVal(
SEC_ATTR_S* pstAttr,SEC_UINT32* ulTypeAttr);
* @endcode
*
* @par Purpose
* To fetch the Attribute value from the given PKCS12 Attribute structure.
*
* @par Description
* This function gets attribute type and value from the SEC_ATTR_S.
* It returns the first element of the list that contains attribute values.
*
* @param[in] pstAttr SEC_ATTR_S from which
value and the type to be fetched [N/A]
* @param[out] ulTypeAttr Type of the attribute
which could be LocalID(CID_LOCALKEYID)
* or Friendly name (CID_FRIENDLYNAME). [N/A]
*
* @retval SEC_AsnOcts_S* Value of the PKCS12
Attribute, it contains the value and the length of the string.
* Usually this value  is DER encoded  Secret Bag. [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If an error occurs during following scenarios:\n
* Any of the inputs are invalid\n
* List operation fails [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the attribute
value.Hence this memory should not
* be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_AsnOcts_S* PKCS12_getAttributeVal(
   SEC_ATTR_S* pstAttr,SEC_UINT32* ulTypeAttr);



/**
* @defgroup PKCS12_getAttrFromSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_ATTR_S* PKCS12_getAttrFromSafeBag(PKCS12_SAFEBAG_S* pstSafeBag);
* @endcode
*
* @par Purpose
* To fetch the attribute structure from the given PKCS12 Safe bag.
*
* @par Description
* This function gets the attribute from the Safe Bag. It gives
* the first attribute from the attribute list when called first time
* and successive attribute when called successively.
*
* @param[in] pstSafeBag Contains certificate,crl,privatekey etc. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ATTR_S* A PKCS12 Attribute,
can be either LocalID Or Friendly name.
* The type and value of SEC_ATTR_S is fetched using other API. [SEC_ATTR_S*|N/A]
* @retval SEC_ATTR_S* If an error occurs during following scenarios:\n
* Any of the input is invalid\n
* List operation fails [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the attribute.
Hence this memory should not
* be freed.
*
* @par Note
* 
* The usage of this API is not recommended and it should not be used under 
* multithread scenario. Instead the user can use the API 
* PKCS12_getAttrFromSafeBagByIndex.
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_ATTR_S* PKCS12_getAttrFromSafeBag(PKCS12_SAFEBAG_S* pstSafeBag);


/**
* @defgroup PKCS12_getAttrFromSafeBagByIndex
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_ATTR_S* PKCS12_getAttrFromSafeBagByIndex(
PKCS12_SAFEBAG_S* pstSafeBag,SEC_UINT32 ulIndex);
* @endcode
*
* @par Purpose
* To fetch an Attribute from the given PKCS12 Safe bag based on the given Index.
*
* @par Description
* This function gets the Attribute from the safe bag. It returns
* the attribute at position index from the attribute list.
*
* @param[in] pstSafeBag Contains certificate,crl,privatekey etc. [N/A]
* @param[in] ulIndex Index of the Attribute in the attribute list present in the
* PKCS12_SAFEBAG_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ATTR_S* A PKCS12 attribute which
can be either LocalID or Friendly name.
* Type and value of the SEC_ATTR_S is fetched using other API. [SEC_ATTR_S*|N/A]
* @retval SEC_ATTR_S* If Any of the input is invalid or 
List operation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the attribute.
Hence this memory should not
* be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_ATTR_S* PKCS12_getAttrFromSafeBagByIndex(
    PKCS12_SAFEBAG_S* pstSafeBag,SEC_UINT32 ulIndex);


/**
* @defgroup PKCS12_getSafeBagType
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS12_getSafeBagType(PKCS12_SAFEBAG_S* pstBag);
* @endcode
*
* @par Purpose
* To fetch the type of the given PKCS12 Safe Bag.
*
* @par Description
* This function is used to get the type of the bag i.e certificate and CRL.
*
* @param[in] pstBag Structure contains Safe Bag type and
* bag value. Value could be certificate CRL and private Key. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 If it is certificate Safe Bag [CID_CERTBAG|N/A]
* @retval SEC_UINT32 If it is CRL Safe Bag [CID_CRLBAG|N/A]
* @retval SEC_UINT32 If it is Secret Safe  Bag contains data [CID_SECRETBAG|N/A]
* @retval SEC_UINT32 If it is Private Key Safe  Bag [CID_KEYBAG|N/A]
* @retval SEC_UINT32 If it is encrypted Private Key Safe Bag
[CID_PKCS8SHROUDEDKEYBAG|N/A]
* @retval SEC_UINT32 In case bag does not contain any valid CID
[CID_UNKNOWN|N/A]
* @retval SEC_UINT32 If input is null [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*
*/
PSELINKDLL  SEC_UINT32 PKCS12_getSafeBagType(PKCS12_SAFEBAG_S* pstBag);

/**
* @defgroup PKCS12_extractCertFromSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* X509_CERT_S* PKCS12_extractCertFromSafeBag(PKCS12_SAFEBAG_S* pstBag);
* @endcode
*
* @par Purpose
* To fetch the X509 Certificate from the given PKCS12 Safe Bag.
*
* @par Description
* This function is used to get the X509 certificate  from a safe Bag.
* It first decodes the bagValue field of PKCS12_SAFEBAG_S to
get the encoded certificate.
* It decodes this value and returns the pointer to X509 certificate Structure.
*
* @param[in] pstBag Safe bag containing certificate bag
which contains certificate Value [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* Structure holds X509 certificate value
or SEC_NULL in case of invalid data. [X509_CERT_S*|N/A]
* @retval X509_CERT_S* If an error occures during following scenarios.
[SEC_NULL|N/A]
* @retval X509_CERT_S* If Any of the Input is invalid. [SEC_NULL|N/A]
* @retval X509_CERT_S* If structure contains invalid CID. [SEC_NULL|N/A]
* @retval X509_CERT_S* If certificate decode fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_CERT_S structure,
to free this memory
* application has to call the X509_freeCert API.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*
*
*/

PSELINKDLL  X509_CERT_S* PKCS12_extractCertFromSafeBag(
   PKCS12_SAFEBAG_S* pstBag);



/**
* @defgroup PKCS12_extractCRLFromSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* X509_CRL_S *PKCS12_extractCRLFromSafeBag (PKCS12_SAFEBAG_S* pstBag);
* @endcode
*
* @par Purpose
* To fetch the X509 CRL from the given PKCS12 Safe bag.
*
* @par Description
* This function is used to get the X509CRL from a safe Bag.
* It first decodes the bagValue field of PKCS12_SAFEBAG_S to
get the encoded X509 CRL,
* It decodes this value and returns the pointer to X509 CRL structure.
*
* @param[in] pstBag Safe bag containing CRL Bag which
contains X509 CRL value [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CRL_S* Structure holds X509 CRL value or
SEC_NULL in case of invalid data. [X509_CRL_S*|N/A]
* @retval X509_CRL_S* If any of the Inputs are invalid. [SEC_NULL|N/A]
* @retval X509_CRL_S* If structure contains invalid CID. [SEC_NULL|N/A]
* @retval X509_CRL_S* If CRL decode fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_CRL_S structure,
to free this memory
* application has to call the X509CRL_free API.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL  X509_CRL_S *PKCS12_extractCRLFromSafeBag (PKCS12_SAFEBAG_S* pstBag);



/**
* @defgroup PKCS12_getDataFromSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UCHAR* PKCS12_getDataFromSafeBag (
 PKCS12_SAFEBAG_S* pstSafeBag,SEC_UINT32* puLen);
* @endcode
*
* @par Purpose
* To fetch the data from the given PKCS12 Safe bag.
*
* @par Description
* This function is used to get the data from a Safe Bag.
The data is usually an encoded PKCS12 SecretBag.
*
* @param[in] pstSafeBag Safe bag containing encoded Secret Bag
which can have any kind of data. [N/A]
* @param[out] puLen     Length of he encoded data. [N/A]
*
* @retval SEC_UCHAR* Pointer to  String (Data).
Usually it is encoded PKCS12 Secret Bag. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Any of the input is invalid. [SEC_NULL|N/A]
* @retval SEC_UCHAR* If structure contains invalid CID. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the encoded data.
Hence this memory should not
* be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL  SEC_UCHAR* PKCS12_getDataFromSafeBag (
PKCS12_SAFEBAG_S* pstSafeBag,SEC_UINT32* puLen);



/**
* @defgroup PKCS12_privKeyToSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_SAFEBAG_S* PKCS12_privKeyToSafeBag (PKCS8_PRIVKEY_S* pstPrivKey);
* @endcode
*
* @par Purpose
* To create a PKCS12 Safe bag to hold a PKCS8 Private key structure.
*
* @par Description
* This function  creates a Safe Bag which contains PKCS8_PRIVKEY_S.
It is used to store Private Key into PFX format.
*
* @param[in] pstPrivKey hold private key information i.e
PKCS8_PRIVKEY_S structure
* to create PKCS8_PRIVKEY_S call PKCS8_createPrivKey [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_SAFEBAG_S* Safe Bag having Private Key value.
[PKCS12_SAFEBAG_S*|N/A]
* @retval PKCS12_SAFEBAG_S* Any of the Input is invalid. [SEC_NULL|N/A]
* @retval PKCS12_SAFEBAG_S* Dup operation fails for Priv Key. [SEC_NULL|N/A]
* @retval PKCS12_SAFEBAG_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the safe bag, to free this memory
* application has to call the PKCS12_freeSafeBAG.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_SAFEBAG_S* PKCS12_privKeyToSafeBag (
                                        PKCS8_PRIVKEY_S* pstPrivKey);



/**
* @defgroup PKCS12_encryptedPrivKeyToSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_SAFEBAG_S* PKCS12_encryptedPrivKeyToSafeBag (
PKCS8_ENCRYPTED_PRIVKEY_S* pstEncPrivKeyInfo);
* @endcode
*
* @par Purpose
* To create a PKCS12 Safe bag to hold the given PKCS8 encrypted Key structure.
*
* @par Description
* This function  creates a safe bag which contains encrypted
private key information,
* that is PKCS8_ENCRYPTED_PRIVKEY_S structure.
It is used to Store Encrypted Private Key into PFX Format.
*
* @param[in] pstEncPrivKeyInfo Holds encrypted Private Key.
* To create PKCS8_ENCRYPTED_PRIVKEY_S call PKCS8_encryptPrivKey. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_SAFEBAG_S* Safe Bag having encrypted Private Key.
[PKCS12_SAFEBAG_S*|N/A]
* @retval PKCS12_SAFEBAG_S* Any of the Input is invalid. [SEC_NULL|N/A]
* @retval PKCS12_SAFEBAG_S* Dup operation fails for Encrypted Private Key.
[SEC_NULL|N/A]
* @retval PKCS12_SAFEBAG_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the safe bag, to free this memory
* application has to call the PKCS12_freeSafeBAG.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  PKCS12_SAFEBAG_S* PKCS12_encryptedPrivKeyToSafeBag (
PKCS8_ENCRYPTED_PRIVKEY_S* pstEncPrivKeyInfo);



/**
* @defgroup PKCS12_getPrivKeyFromSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS8_PRIVKEY_S* PKCS12_getPrivKeyFromSafeBag(PKCS12_SAFEBAG_S* pstSafebag);
* @endcode
*
* @par Purpose
* To extract the PKCS8 Private key from the given PKCS12 Safe bag.
*
* @par Description
* This function gets PKCS8 Private Key structure from PKCS12 Safe Bag.
*
* @param[in] pstSafebag Contains PKCS8_PRIVKEY_S structure value. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS8_PRIVKEY_S* Pointer to  PRIVATE KEY
structure contains the Private Key information. [PKCS8_PRIVKEY_S*|N/A]
* @retval PKCS8_PRIVKEY_S* Any of the input is invalid. [SEC_NULL|N/A]
* @retval PKCS8_PRIVKEY_S* Structure contains invalid CID. [SEC_NULL|N/A]
* @retval PKCS8_PRIVKEY_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the PKCS8_PRIVKEY_S structure.
Hence this memory should not
* be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  PKCS8_PRIVKEY_S* PKCS12_getPrivKeyFromSafeBag(
PKCS12_SAFEBAG_S* pstSafebag);



/**
* @defgroup PKCS12_getEncryptedPrivKeyFromSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS8_ENCRYPTED_PRIVKEY_S* PKCS12_getEncryptedPrivKeyFromSafeBag(
PKCS12_SAFEBAG_S* pstSafebag);
* @endcode
*
* @par Purpose
* To extract the encrypted PKCS8 private key from the given PKCS12 safe bag.
*
* @par Description
* This function gets PKCS8 Encrypted  Private Key  structure from safe bag.
*
* @param[in] pstSafebag Contains the Encrypted Private Key information. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS8_ENCRYPTED_PRIVKEY_S* Encrypted Private Key  contains
Encrypted Private Key information.
* [PKCS8_ENCRYPTED_PRIVKEY_S*|N/A]
* @retval PKCS8_ENCRYPTED_PRIVKEY_S* Any of the input is invalid. [SEC_NULL|N/A]
* @retval PKCS8_ENCRYPTED_PRIVKEY_S* Structure contains
invalid CID. [SEC_NULL|N/A]
* @retval PKCS8_ENCRYPTED_PRIVKEY_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the PKCS8_ENCRYPTED_PRIVKEY_S structure.
* Hence this memory should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  PKCS8_ENCRYPTED_PRIVKEY_S* PKCS12_getEncryptedPrivKeyFromSafeBag(
                    PKCS12_SAFEBAG_S* pstSafebag);



/**
* @defgroup PKCS12_createBagList
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_BAGLIST_S* PKCS12_createBagList(SEC_VOID);
* @endcode
*
* @par Purpose
* To create a PKCS12 Bag list.
*
* @par Description
* This function creates an empty Bag List(Safe Contents) ,
i.e. A list to hold Safe Bags.
*
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_BAGLIST_S* Pointer to a list, 
which will hold the Safe Bag. [PKCS12_BAGLIST_S*|N/A]
* @retval PKCS12_BAGLIST_S* If an error occurs,
that is, the list creation operation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_BAGLIST_S structure,
to free this memory
* application has to call the PKCS12_freeBagList.
*
* @par Note
*
* This API creates an empty List. Safe Bags Are added using other
APIs or SEC_NULL in case of error.
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_BAGLIST_S*   PKCS12_createBagList(SEC_VOID);



/**
* @defgroup PKCS12_addBagToBagList
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UINT32    PKCS12_addBagToBagList(
* PKCS12_BAGLIST_S* pSafeContents, PKCS12_SAFEBAG_S* pstSafeBag);
* @endcode
*
* @par Purpose
* To add a safe bag structure to an existing safe bag list.
*
* @par Description
* This function is called to add a Safe Bag to a Bag List (safe Content).
* A list can have any kind of Safe Bag i.e CRL or certificate.
*
* @param[in] pSafeContents List to hold Safe Bags. [N/A]
* @param[in] pstSafeBag Safe Bag which is to be added in Bag List. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Status of the add Bag operaton.
[SEC_UINT32|N/A]
* @retval SEC_UINT32 If Safe Bag was added successfully to the list.
[SEC_SUCCESS|N/A]
* @retval SEC_UINT32 In case list operation fails.
[SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 In case Safe Bag duplication fails.
[SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If any of the input parameters missing/invalid.
[SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_UINT32  PKCS12_addBagToBagList(
    PKCS12_BAGLIST_S* pSafeContents, PKCS12_SAFEBAG_S* pstSafeBag);



/**
* @defgroup PKCS12_getBagFromBagList
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_SAFEBAG_S* PKCS12_getBagFromBagList(PKCS12_BAGLIST_S* pSafeContent);
* @endcode
*
* @par Purpose
* To fetch the PKCS12 Safe bag from the given bag list.
*
* @par Description
* This function is called to get a Safe Bag from a Bag List (Safe Content).
* It will return the current Bag in the Bag List and point to the next Safe Bag.
*
* @param[in] pSafeContents List to hold Safe Bags. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_SAFEBAG_S* Pointer to current Safe Bag 
in Bag List (Safe Contents).
[PKCS12_SAFEBAG_S*|N/A]
* @retval PKCS12_SAFEBAG_S* If the input is invalid i.e SEC_NULL. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the PKCS12_SAFEBAG_S structure.
Hence this memory should not
* be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL  PKCS12_SAFEBAG_S* PKCS12_getBagFromBagList(
                                  PKCS12_BAGLIST_S* pSafeContent);



/**
* @defgroup PKCS12_getBagFromBagListByIndex
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_SAFEBAG_S* PKCS12_getBagFromBagListByIndex(
PKCS12_BAGLIST_S* pSafeContent,SEC_UINT32 ulIndex);
* @endcode
*
* @par Purpose
* To fetch a Safe bag from a bag list given the index of the Safe bag.
*
* @par Description
* This function is called to get a Safe Bag from a Safe Content(Bag List).
* It will return  Bag of the Safe Content at ulIndex position.
*
* @param[in] pSafeContents List to hold Safe Bags. [N/A]
* @param[in] ulIndex Index used to fetch the Safe Bag. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_SAFEBAG_S* Pointer to Safe Bag in the BagList at
ulIndex position.[PKCS12_SAFEBAG_S*|N/A]
* @retval PKCS12_SAFEBAG_S* In case of any invalid or NULL input. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the PKCS12_SAFEBAG_S structure.
Hence this memory should not
* be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  PKCS12_SAFEBAG_S* PKCS12_getBagFromBagListByIndex(
         PKCS12_BAGLIST_S* pSafeContent,SEC_UINT32 ulIndex);


/**
* @defgroup PKCS12_getPrivacyMode
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_PRIVACY_MODE_E PKCS12_getPrivacyMode(PKCS7_MSG_S* pstContentInfo);
* @endcode
*
* @par Purpose
* To fetch the type of the privacy mode corresponding to
the given PKCS7 message.
*
* @par Description
* This function gets the type of the privacy mode applied on data,
i.e it could be plain data,
* encrypted data,Or enveloped data.
*
* @param[in] pstContentInfo Pointer to a PKCS7_MSG_S which
contain the data privacy applied on it. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_PRIVACY_MODE_E This mode is returned
if the privacy mode is plain.
[PKCS12_PLAIN_PRIVACY|N/A]
* @retval PKCS12_PRIVACY_MODE_E This mode is returned
if the privacy mode is Public Key. [PKCS12_PUBKEY_PRIVACY|N/A]
* @retval PKCS12_PRIVACY_MODE_E This mode is returned
if the privacy mode is password. [PKCS12_PASS_PRIVACY|N/A]
* @retval PKCS12_PRIVACY_MODE_E This mode is returned
if the privacy mode is not supported.
* [PKCS12_UNSUPPORTED_PRIVACY_MODE|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  PKCS12_PRIVACY_MODE_E PKCS12_getPrivacyMode(
                                   PKCS7_MSG_S* pstContentInfo);



/**
* @defgroup PKCS12_createAuthSafe
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_AUTHSAFE_S*    PKCS12_createAuthSafe(SEC_VOID);
* @endcode
*
* @par Purpose
* To create an Authenticated Safe.
*
* @par Description
* This function Creates a Authenticated Safe, a list to hold the
* PKCS7_MSG_S which contain privacy applied data.
*
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_AUTHSAFE_S* Pointer to  a list which
will hold the PKCS7_MSG_S. [PKCS12_AUTHSAFE_S*|N/A]
* @retval PKCS12_AUTHSAFE_S* If an error occures 
i.e. list new fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the
PKCS12_AUTHSAFE_S structure, to free this memory
* application has to call the PKCS12_freeAuthSafe.
*
* @par Note
*
* It creates an empty list.
*
* @par Related Topics
* N/A
*
*/
PSELINKDLL  PKCS12_AUTHSAFE_S*  PKCS12_createAuthSafe(SEC_VOID);



/**
* @defgroup PKCS12_addBagListToAuthSafe
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UINT32    PKCS12_addBagListToAuthSafe (PKCS12_AUTHSAFE_S* pAuthSafe,
* PKCS12_BAGLIST_S* pSafeContent);
* @endcode
*
* @par Purpose
* To add a PKCS7 msg, present in a bag list, to the given Authenticated safe.
*
* @par Description
* This function first makes the PKCS7_MSG_S from Bag List (Safe Contents)
and then adds the same to the AuthSafe.
*
* @param[in] pAuthSafe      List of PKCS7_MSG_S. [N/A]
* @param[in] pSafeContent   List of Safe Bags. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 In case Bag List is successfully
added to Auth Safe. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input is invalid. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If encode for baglist fails. [SEC_ERR_ENCODE_FAIL|N/A]
* @retval SEC_UINT32 If creation of PKCS7_MSG_S fails.
[SEC_ERR_CREATE_SIMPLEDATA_FAILED|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* This API is used when no privacy is required on data. 
In this case data will be only plain data.
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_UINT32  PKCS12_addBagListToAuthSafe (
                                          PKCS12_AUTHSAFE_S* pAuthSafe,
                                        PKCS12_BAGLIST_S* pSafeContent);



/**
* @defgroup PKCS12_encryptBagList
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UINT32    PKCS12_encryptBagList(PKCS12_AUTHSAFE_S* pstAuthSafe,
* PKCS12_BAGLIST_S* pstSafeContent,
* SEC_UCHAR* pucPass,
* SEC_UINT32 ulPassLen,
* SEC_UINT32 ulKeyDerAlgId);
* @endcode
*
* @par Purpose
* To encrypt a PKCS7 message, which is in a bag list,
and add it to the given PKCS12 Auth Safe.
*
* @par Description
* This function first creates the encrypted PKCS7_MSG_S
from Bag List (Safe Contents)
* and then adds the encrypted bag list to the AuthSafe.
*
* @param[in] pstAuthSafe List of PKCS7_MSG_S. [N/A]
* @param[in] pstSafeContent Pointer to Bag List contains Safe Bags. [N/A]
* @param[in] pucPass Password used to encrypt the data. [N/A]
* @param[in] ulPassLen Length of the Password [N/A]
* @param[in] ulKeyDerAlgId AlgID used for encrypting data.
* It can be any PBES1 ALgID supported by either PKCS12 or PKCS5.
* Standard possible values are:\n
* CID_PBE_MD5WITHDESCBC\n
* CID_PBE_SHA1WITHDESCBC\n
* CID_PBE_SHAWITH128BITRC4\n
* CID_PBE_SHAWITH40BITRC4\n
*.CID_PBE_SHAWITH40BIT_RC2CBC\n
*.CID_PBE_SHAWITH128BIT_RC2CBC\n
* CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC\n
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 In case list is encrypted and
successfully added to the PKCS12 AuthSafe. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the input is missing or invalid.
[SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If any of the PKCS7 message creation fails.
[SEC_ERR_CREATE_SIMPLEDATA_FAILED|N/A]
* @retval SEC_UINT32 If PKCS7 message encryption fails.
[SEC_PKCS12_ERR_PBEOPERATION_FAILED|N/A]
* @retval SEC_UINT32 If the encode of the Bag List fails.
[SEC_ERR_ENCODE_FAILED|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* This API is used when privacy is required on data.
In this case data will only be encrypted data.
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_UINT32  PKCS12_encryptBagList(PKCS12_AUTHSAFE_S* pstAuthSafe,
                                        PKCS12_BAGLIST_S* pstSafeContent,
                                        SEC_UCHAR* pucPass,
                                        SEC_UINT32 ulPassLen,
                                        SEC_UINT32 ulKeyDerAlgId);



/**
* @defgroup PKCS12_envelopBagList
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UINT32    PKCS12_envelopBagList(PKCS12_AUTHSAFE_S* pstAuthSafe,
* PKCS12_BAGLIST_S* pstSafeContent ,
* SEC_UINT32  enCEAlgo,
* X509_CERT_S*  pstCertificate );
* @endcode
*
* @par Prototype
* To envelop PKCS7 message and add it to the given PKCS12 Auth Safe.
*
* @par Description
* This function first makes the enveloped PKCS7_MSG_S from Bag List
* and then adds the same to the given AuthSafe
*
* @param[in] pstAuthSafe List of PKCS7_MSG_S. [N/A]
* @param[in] pstSafeContent Pointer to Bag List contains Safe Bags. [N/A]
* @param[in] enCEAlgo Any symmetric AlgId used for encryption of the data
* as supported in PKCS7 PKCS7_createEnveloped API. [N/A]
* @param[in] pstCertificate Pointer to X509 certificate from
which information i.e Key, Issuer Name, and
* Serial Number is fetched. To create certificate call X509_createCert. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 In case list is encrypted and successfully
added to the PKCS12 AuthSafe. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the input is missing or invalid.
[SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If any of the PKCS7 message creation fails.
[SEC_ERR_CREATE_SIMPLEDATA_FAILED|N/A]
* @retval SEC_UINT32 If PKCS7 message enveloping fails. 
[SEC_ERR_CREATE_ENVDATA_FAILED|N/A]
* @retval SEC_UINT32 If PKCS7 message add recipent fails. 
[SEC_ERR_ADD_RECIPIENT_FAILED|N/A]
* @retval SEC_UINT32 If the encode of the bag list fails.
[SEC_ERR_ENCODE_FAILED|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* This API is used when privacy is required on data. 
In this case data will be enveloped data.
*
* @par Related Topics
* N/A
*
*/
PSELINKDLL SEC_UINT32   PKCS12_envelopBagList(PKCS12_AUTHSAFE_S* pstAuthSafe,
                                PKCS12_BAGLIST_S* pstSafeContent ,
                                SEC_UINT32  enCEAlgo,
                                X509_CERT_S*  pstCertificate);



/**
* @defgroup PKCS12_extractBagListFromAuthSafe
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_BAGLIST_S* PKCS12_extractBagListFromAuthSafe(PKCS12_AUTHSAFE_S *pAuth);
* @endcode
*
* @par Purpose
* To fetch the bag list from the given PKCS12 Auth Safe.
*
* @par Description
* This function gets the Bag List (Safe Contents) from Auth Safe.
* The Auth Safe contains a PKCS7_MSG_S of plain data.
* Since the decoded Bag List will have the list current pointer at last,
* user should call SEC_LIST_GET_FIRST API
* on the received PKCS12_BAGLIST_S to get the first bag.
*
* @param[in] pAuth List of PKCS7_MSG_S contains data privacy applied on it.
[N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_BAGLIST_S* List of Safe Bags. [PKCS12_BAGLIST_S*|N/A]
* @retval PKCS12_BAGLIST_S* If any of the input parameter is invalid.
[SEC_NULL|N/A]
* @retval PKCS12_BAGLIST_S* Any List Operation Fails. [SEC_NULL|N/A]
* @retval PKCS12_BAGLIST_S* Any Of the PKCS7 operation i.e 
get simple data fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_BAGLIST_S structure,
to free this memory
* application has to call the PKCS12_freeBagList.
*
* @par Note
*
* This API takes the first PKCS7_MSG_S from Auth Safe list,
decodes it and then returns the Bag List.
* It is used when data does not have any privacy.
*
* @par Related Topics
* N/A
*
*/
PSELINKDLL  PKCS12_BAGLIST_S* PKCS12_extractBagListFromAuthSafe(
                                               PKCS12_AUTHSAFE_S *pAuth);




/**
* @defgroup PKCS12_decryptAuthSafe
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_BAGLIST_S* PKCS12_decryptAuthSafe(PKCS12_AUTHSAFE_S* pstAuth,
* SEC_UCHAR *pucPass,
* SEC_UINT32 ulPassLen);
* @endcode
*
* @par Purpose
* To fetch
*
* @par Description
* This function extracts the Bag List (safe contents) from the Auth Safe.
* the authenticated safe contains encrypted PKCS7_MSG_S data.
* Since the recieved Bag List have the list current pointer at last,
user should call SEC_LIST_GET_FIRST API on
* recieved PKCS12_BAGLIST_S to get the first bag.
*
* @param[in] pAuth List of PKCS7_MSG_S. [N/A]
* @param[in] pucPass Password used in encryption. [N/A]
* @param[in] ulPassLen Length of the password. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_BAGLIST_S* List of Safe Bags. [PKCS12_BAGLIST_S*|N/A]
* @retval PKCS12_BAGLIST_S* If any of the input parameter is invalid.
[SEC_NULL|N/A]
* @retval PKCS12_BAGLIST_S* Any List Operation Fails. [SEC_NULL|N/A]
* @retval PKCS12_BAGLIST_S* Any Of the PKCS7 operation i.e
get Simple data fails or PBE Decrypt operation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_BAGLIST_S structure,
to free this memory
* application has to call the PKCS12_freeBagList.
*
* @par Note
*
* This API takes the first PKCS7_MSG_S from Auth Safe List.
Decodes and decrypts it and returns the Bag List.
* It is used when the data is encrypted data i.e the privacy mode
is password privacy.
*
* @par Related Topics
* N/A
*
*/
PSELINKDLL  PKCS12_BAGLIST_S* PKCS12_decryptAuthSafe(PKCS12_AUTHSAFE_S* pstAuth,
                            SEC_UCHAR *pucPass,
                            SEC_UINT32 ulPassLen);


/**
* @defgroup PKCS12_openEnvelop
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_BAGLIST_S* PKCS12_openEnvelop(PKCS12_AUTHSAFE_S* pAuth,
* SEC_PKEY_S*  pstPrivKey,
* X509_CERT_S *pstCert);
* @endcode
*
* @par Purpose
* To extract a PKCS12 bag list from the given Auth Safe which
contains PKCS7 enveloped data.
*
* @par Description
* This function gets the Safe Bag List (safe contents) from Auth Safe.
The authenticated safe contains a
* PKCS7 Enveloped Data. Since the received Bag List will have 
the list current pointer at last, user should call
* SEC_LIST_GET_FIRST API on recieved PKCS12_BAGLIST_S to get the first bag.
*
* @param[in] pAuth List of Safe Contents.[N/A]
* @param[in] pstPrivKey Private Key used to open the envelop.[N/A]
* @param[in] pstCert From which information 
i.e Issuer Name and  Serial Number is fetched.
* This is added as part of the recipient's info while
enveloping the Bag List. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_BAGLIST_S* Upon successful completion,
List of Safe Bags is returned. [PKCS12_BAGLIST_S*|N/A]
* @retval PKCS12_BAGLIST_S* If any of the input parameters are invalid.
[SEC_NULL|N/A]
* @retval PKCS12_BAGLIST_S* Any list operation fails. [SEC_NULL|N/A]
* @retval PKCS12_BAGLIST_S* Any of the PKCS7 operations i.e
get simple data fails or PBE Decrypt operation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_BAGLIST_S structure,
to free this memory
* application has to call the PKCS12_freeBagList.
*
* @par Note
*
* This API takes the first PKCS7_MSG_S from Auth Safe List Decode
and it returns the Bag List.
* It is used when data is enveloped data i.e the privacy mode is
Public Key Privacy.
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_BAGLIST_S* PKCS12_openEnvelop(PKCS12_AUTHSAFE_S* pAuth,
                            SEC_PKEY_S*  pstPrivKey,
                            X509_CERT_S *pstCert);



/**
* @defgroup PKCS12_createPFXWithPubKey
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_PFX_S*  PKCS12_createPFXWithPubKey(PKCS12_AUTHSAFE_S *pstAuthSafe,
* SEC_UINT32 ulVersion,
* X509_CERT_S* pstCert,
* SEC_PKEY_S*  pstPrivKey);
* @endcode
*
* @par Purpose
* To create a PFX PDU in Public Key intergrity mode.
*
* @par Description
* This API is used to apply integrity on PFX.
* It first creates PFX with the given input and then applies Public Key
integrity on it.
*
* @param[in] pstAuthSafe List of PKCS7_MSG_S. [N/A]
* @param[in] ulVersion Version of the PFX. It should be 3. [N/A]
* @param[in] pstCert From which information
i.e Issuer Name and Serial Number, Digest AlgorithmID is fetched. [N/A]
* @param[in] pstPrivKey Contains Private Key used for signature. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_PFX_S* A PFX  used to exchange the information.
[PKCS12_PFX_S*|N/A]
* @retval PKCS12_PFX_S* If any of the input parameter is invalid. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Any list operation fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Any Of the PKCS7 operation i.e
create simple data fails or create signed data fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Encode of the Auth Safe Fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Add signer info fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Add reciepent info fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_PFX_S structure,
to free this memory
* application has to call the PKCS12_freePFX.
*
* @par Note
*
* This API is called after applying privacy on data.
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_PFX_S*  PKCS12_createPFXWithPubKey(
                            PKCS12_AUTHSAFE_S *pstAuthSafe,
                            SEC_UINT32 ulVersion,
                            X509_CERT_S* pstCert,
                            SEC_PKEY_S*  pstPrivKey);


/**
* @defgroup PKCS12_createPFXWithPasswd
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_PFX_S* PKCS12_createPFXWithPasswd(PKCS12_AUTHSAFE_S* pstAuthSafe,
* SEC_UINT32 ulVersion,
* SEC_UCHAR*  pucPassword,
* SEC_UINT32 ulPassLen,
* SEC_UINT32 ulAlgId);
* @endcode
*
* @par Purpose
* To create a PFX PDU in Password Integrity mode.
*
* @par Description
* This API is used to apply integrity on PFX.
* It first creates PFX with the given input and
then applies password integrity on it.
*
* @param[in] pstAuthSafe List of PKCS7_MSG_S. Apply plain,
password or pubkey privacy on it. [N/A]
* @param[in] ulVersion Version of the PFX. It should be 3. [N/A]
* @param[in] pucPassword Password  used for Key derivation. [N/A]
* @param[in] ulPassLen Length of the password. [N/A]
* @param[in] ulAlgId Alg Id used in generating Key.
For the current version it should be CID_SHA1. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_PFX_S* A PFX PDU used to exchange the information
i.e certificate CRL Private Key etc. [PKCS12_PFX_S*|N/A]
* @retval PKCS12_PFX_S* If any of the input parameters are invalid. 
[SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Any list operation fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Any of the PKCS7 operation i.e
create simple data failed or create signed data failed. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Encode of the Auth Safe fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_PFX_S structure,
to free this memory
* application has to call the PKCS12_freePFX.
*
* @par Note
*
* This API is called after applying privacy on data.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL  PKCS12_PFX_S* PKCS12_createPFXWithPasswd(
                            PKCS12_AUTHSAFE_S* pstAuthSafe,
                            SEC_UINT32 ulVersion,
                            SEC_UCHAR*  pucPassword,
                            SEC_UINT32 ulPassLen,
                            SEC_UINT32 ulAlgId);



/**
* @defgroup PKCS12_changePFXPasswd
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_PFX_S* PKCS12_changePFXPasswd(PKCS12_PFX_S* pstPFX,
* SEC_UCHAR *pucOldPass,
* SEC_UINT32 ulOldLen,
* SEC_UCHAR *pucNewPass,
* SEC_UINT32 ulNewLen,
* SEC_UINT32 ulEncAlgId);
* @endcode
*
* @par Purpose
* To change the password for the given PFX.
*
* @par Description
* This is used in the scenario when all the encrypted bag List contains 
the same password.
* It changes the password for all APIs to new password and also sets the same
* integrity password.
*
* @param[in] pstPFX PFX PDU of which password has to be changed. [N/A]
* @param[in] pucOldPass Old password. [N/A]
* @param[in] ulOldLen Old password length. [N/A]
* @param[in] pucNewPass New password. [N/A]
* @param[in] ulNewLen New password length. [N/A]
* @param[in] ulEncAlgId New encryption AlgID used to encrypt the data any 
PBES1 AlgID\n
* CID_PBE_MD5WITHDESCBC\n
* CID_PBE_SHA1WITHDESCBC\n
* CID_PBE_SHAWITH128BITRC4\n
* CID_PBE_SHAWITH40BITRC4\n
*.CID_PBE_SHAWITH40BIT_RC2CBC\n
*.CID_PBE_SHAWITH128BIT_RC2CBC\n
* CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC\n
* CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_PFX_S* A PFX PDU used to exchange the information. 
[PKCS12_PFX_S*|N/A]
* @retval PKCS12_PFX_S* If any of the input parameters are invalid.
[SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Any list operation fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Any of the PKCS7 operation i.e
create simple data fails or create signed data fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Encoding of the Auth Safe fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Decryption of Auth Safe fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Encoding of Bag List fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_PFX_S structure,
to free this memory
* application has to call the PKCS12_freePFX.
*
* @par Note
*
* This API changes both privacy and integrity password when applied on PFX PDU.
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_PFX_S* PKCS12_changePFXPasswd(PKCS12_PFX_S* pstPFX,
                            SEC_UCHAR *pucOldPass,
                            SEC_UINT32 ulOldLen,
                            SEC_UCHAR *pucNewPass,
                            SEC_UINT32 ulNewLen,
                            SEC_UINT32 ulEncAlgId);



/**
* @defgroup PKCS12_extractAuthSafeFromPFX
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_AUTHSAFE_S* PKCS12_extractAuthSafeFromPFX(PKCS12_PFX_S *pstPFX);
* @endcode
*
* @par Purpose
* To extract the PKCS12 Auth Safe from the given PFX.
*
* @par Description
* This function used to extract the Auth Safe from PFX. 
It decodes the PKCS7_MSG_S of PFX and gets
* PKCS12_AUTHSAFE_S. PKCS12_AUTHSAFE_S is a list of PKCS7_MSG_S. 
*After Getting PKCS12_AUTHSAFE_S through his API the current List pointer 
points to the Last this API the current List pointer points to
* the Last PKCS7_MSG_S of the PKCS12_AUTHSAFE_S,
* so user should call SEC_LIST_GET_FIRST on the received
PKCS12_AUTHSAFE_S before 
* using it, if it contains more
* than one PKCS7_MSG_S.
*
* @param[in] pstPFX PFX contains Auth Safe. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_AUTHSAFE_S* A List Of PKCS7_MSG_S.
Privacy is applied on it. [PKCS12_AUTHSAFE_S*|N/A]
* @retval PKCS12_AUTHSAFE_S* If any of the input parameters is invalid. 
[SEC_NULL|N/A]
* @retval PKCS12_AUTHSAFE_S* Any list operation fails. [SEC_NULL|N/A]
* @retval PKCS12_AUTHSAFE_S* Decoding of the Auth Safe fails. [SEC_NULL|N/A]
* @retval PKCS12_AUTHSAFE_S* Integrity mode of PFX is invalid. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_AUTHSAFE_S structure,
to free this memory
* application has to call the PKCS12_freeAuthSafe.
*
* @par Note
*
* It gets the Authsafe back from the PFX.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL  PKCS12_AUTHSAFE_S* PKCS12_extractAuthSafeFromPFX(
                                                      PKCS12_PFX_S *pstPFX);



/**
* @defgroup PKCS12_verifyPFXWithPasswd
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UINT32    PKCS12_verifyPFXWithPasswd(
     PKCS12_PFX_S* pstPFX,SEC_UCHAR * pucPassword,
* SEC_INT32 uiLen);
* @endcode
*
* @par Purpose
* To verify the the given PKCS12_PFX_S structure for integrity using
the given password.
*
* @par Description
* This function verifies the integrity of the PFX when password
integrity mode is applied on it.
* It verifies the MAC available in PFX.
*
* @param[in] pstPFX PFX on which password integrity is to be verified. [N/A]
* @param[in] pucPassword Password used for key derivation. [N/A]
* @param[in] uiLen Length of the password. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 If the password is successfully
verified else error code return by PKCS5. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are missing.
[SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the extracted  authsafe from pfx is invalid. 
[SEC_PKCS12_ERR_INVALID_AUTHSAFE|N/A]
* @retval SEC_UINT32 If the MAC inside PFX and newly generated MAC are not same.
[SEC_ERR_INVALID_MAC|N/A]
* @retval SEC_UINT32 If the pstPFX contains invalid algorithm ALGID.
[SEC_ERR_INVALID_CID|N/A]
* @retval SEC_UINT32 If the key derivation failed. 
[SEC_ERR_KEY_DERIV_FAILED|N/A]
* @retval SEC_UINT32 On memory allocation failure.
[SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If the the encode for PKCS12_AUTHSAFE_S fails.
[SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 If the MAC inside PFX is Null or the Algorithm
inside MAC is null. [SEC_ERR_NULL_PTR|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* It is used only in case of password integrity mode.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL  SEC_UINT32  PKCS12_verifyPFXWithPasswd(
                       PKCS12_PFX_S* pstPFX,SEC_UCHAR * pucPassword,
                                        SEC_INT32 uiLen);


/**
* @defgroup PKCS12_getIntegrityMode
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_INTEGRITY_MODE_E PKCS12_getIntegrityMode(PKCS12_PFX_S* pstPFX);
* @endcode
*
* @par Purpose
* To fetch the integrity mode applied on the given PFX.
*
* @par Description
* This function gets the integrity mode applied on PFX.
*
* @param[in] pstPFX PDU contains data to be exchanged. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_INTEGRITY_MODE_E For public Key Sign Mode.
[PKCS12_PUBKEY_SIGN =0|N/A]
* @retval PKCS12_INTEGRITY_MODE_E For password Sign Mode. [PKCS12_PASS_SIGN|N/A]
* @retval PKCS12_INTEGRITY_MODE_E For unsupported Sign Mode. 
[PKCS12_UNSUPPORTED_INTEGRATED_MODE|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_INTEGRITY_MODE_E PKCS12_getIntegrityMode(
                                                PKCS12_PFX_S* pstPFX);


/**
* @defgroup PKCS12_encodePFX
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UCHAR*    PKCS12_encodePFX(
PKCS12_PFX_S* pstPFX, SEC_UINT32* pulLenEncoded);
* @endcode
*
* @par Purpose
* To encode the given PFX PDU.
*
* @par Description
* This function encodes the PFX PDU and gives DER code.
*
* @param[in] pstPFX PDU to encode. [N/A]
* @param[out] pulLenEncoded Length of the encoded string. [N/A]
*
* @retval SEC_UCHAR* Result of add opration i.e success or error codes. 
[SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* If any of the input parameter is invalid. [SEC_NULL|N/A]
* @retval SEC_UCHAR* Memory allocation fails. [SEC_NULL|N/A]
* @retval SEC_UCHAR* ExpBufCopy fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded PFX, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_UCHAR*  PKCS12_encodePFX(
              PKCS12_PFX_S* pstPFX, SEC_UINT32* pulLenEncoded);



/**
* @defgroup PKCS12_decodePFX
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_PFX_S* PKCS12_decodePFX(SEC_UCHAR* pucEncodedPFX,
* SEC_UINT32 ulEncPFXLen,
* SEC_UINT32* pulLenDecoded);
* @endcode
*
* @par Purpose
* To generate the decoded PFX PDU from the given encoded PFX buffer.
*
* @par Description
* This function decodes the encoded PFX PDU.
*
* @param[in] pucEncodedPFX Encoded PFX value. [N/A]
* @param[in] ulEncPFXLen Encode PFX length. [N/A]
* @param[out] pulLenDecoded Bytes decoded. [N/A]
*
* @retval PKCS12_PFX_S* Decoded PFX information. [PKCS12_PFX_S*|N/A]
* @retval PKCS12_PFX_S* If any of the input parameter is NULL. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Memory allocation fails. [SEC_NULL|N/A]
* @retval PKCS12_PFX_S* Decode of PFX fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_PFX_S structure, 
to free this memory
* application has to call the PKCS12_freePFX.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  PKCS12_PFX_S* PKCS12_decodePFX(SEC_UCHAR* pucEncodedPFX,
                            SEC_UINT32 ulEncPFXLen,
                            SEC_UINT32* pulLenDecoded);


/**
* @defgroup PKCS12_verifyPFXWithPubKey
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS12_verifyPFXWithPubKey(PKCS12_PFX_S *pstPFX,
* X509_CERT_S* pstCERT);
* @endcode
*
* @par Purpose
* To verify the integrity of the PFX PDU.
*
* @par Description
* This function verifies the integrity of the PFX when
Public Key integrity mode is applied on it.
* It verifies the signature on signed data.
*
* @param[in] pstPFX PFX on which Public Key integrity is to be verified. [N/A]
* @param[in] pstCERT X509 certificate contains Public Key serial number
and Issuer Name. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 If successfully verified the PFX. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If dup certificate operation returns NULL. 
[SEC_ERR_NULL_PTR|N/A]
* @retval SEC_UINT32 If any of the list operation failed.
[SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 Sign verification failed. [SEC_ERR_SIGN_VERIFY_FAILED|N/A]
* @retval SEC_UINT32 Some of the mandatory inputs are NULL or invalid. 
[SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 One of the mandatory attribute is missing.
[SEC_ERR_ATTR_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Memory allocation failed. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Invalid Sign OR signed enveloped data.
[SEC_ERR_CONVERT_FAILED|N/A]
* @retval SEC_UINT32 Encode failed may be because of Invalid Signed
OR signed enveloped data. [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 One of the mandatory field is NULL in signed OR
signed enveloped data,
* it may be because of structure corruption. [SEC_ERR_NULL_PTR|N/A]
* @retval SEC_UINT32 Digest algorithm OID present in Signer info is invalid.
[SEC_ERR_INVALID_CID|N/A]
* @retval SEC_UINT32 If padding mode requested is undefined. 
[SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If padding in data is not the requested type. 
[SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 If key struct is malformed. 
[SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 If cipher is larger than key.
[SEC_CRYPT_ERR_LARGE_DATA_SIZE|N/A]
* @retval SEC_UINT32 If key type is not public or pair. 
[SEC_CRYPT_ERR_INVALID_PKEY_TYPE|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key.
[SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Invalid Algorithm Id. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Keylength for alg. [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid IVlength for alg mode. [SEC_ERR_INVALID_IV_LEN|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* It is used only in case of public key integrity mode.
*
* @par Related Topics
* N/A
*
*/

PSELINKDLL  SEC_UINT32 PKCS12_verifyPFXWithPubKey(PKCS12_PFX_S *pstPFX,
                            X509_CERT_S* pstCERT);


/**
* @defgroup PKCS12_freeBagList
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_VOID PKCS12_freeBagList(PKCS12_BAGLIST_S* pSafeContent);
* @endcode
*
* @par Purpose
* To free a PKCS12_BAGLIST_S structure.
*
* @par Description
* This function is used to free the memory allocated to the
PKCS12_BAGLIST_S (Safe Contents).
*
* @param[in] pSafeContent A list of Safe Bag to hold information
i.e certificate CRL. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_VOID PKCS12_freeBagList(PKCS12_BAGLIST_S* pSafeContent);



/**
* @defgroup PKCS12_freeAuthSafe
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_VOID PKCS12_freeAuthSafe(PKCS12_AUTHSAFE_S* pstAuth);
* @endcode
*
* @par Purpose
* To free a PKCS12_AUTHSAFE_S structure.
*
* @par Description
* This function frees the memory allocated to the PKCS12_AUTHSAFE_S.
*
* @param[in] pstAuth A list of PKCS7_MSG_S. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_VOID PKCS12_freeAuthSafe(PKCS12_AUTHSAFE_S* pstAuth);


/**
* @defgroup PKCS12_freeMacData
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_VOID PKCS12_freeMacData(PKCS12_MACDATA_S* pstAuth);
* @endcode
*
* @par Purpose
* To free a PKCS12_MACDATA_S structure.
*
* @par Description
* This function frees the memory allocated to the PKCS12_MACDATA_S.
*
* @param[in] pstMacData PKCS12 MAC Data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID PKCS12_freeMacData(PKCS12_MACDATA_S* pstMacData);



/**
* @defgroup PKCS12_freeSafeBagSetOf
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_VOID PKCS12_freeSafeBagSetOf(PKCS12_SafeBagSetOf_S* pstSafeBagSetOf);
* @endcode
*
* @par Purpose
* To free a PKCS12_SafeBagSetOf_S structure.
*
* @par Description
* This function frees the memory allocated to the PKCS12_SafeBagSetOf_S.
*
* @param[in] pstMacData PKCS12 safe bag attributes list. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID PKCS12_freeSafeBagSetOf(
                    PKCS12_SafeBagSetOf_S * pstSafeBagSetOf);

/**
* @defgroup PKCS12_freePFX
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_VOID PKCS12_freePFX (PKCS12_PFX_S* pstPFX);
* @endcode
*
* @par Purpose
* To free a PKCS12_PFX_S structure.
*
* @par Description
* This function frees the memory allocated to the PFX PDU.
*
* @param[in] pstPFX The PFX containd information i.e certificate,crl etc. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_VOID PKCS12_freePFX (PKCS12_PFX_S* pstPFX);



/**
* @defgroup PKCS12_freeSafeBAG
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_VOID PKCS12_freeSafeBAG (PKCS12_SAFEBAG_S * pstSafeBags);
* @endcode
*
* @par Purpose
* To free a PKCS12_SAFEBAG_S structure.
*
* @par Description
* This function frees the memory allocated to the PKCS12_SAFEBAG_S.
*
* @param[in] pstSafeBags Safe Bag to hold information
i.e certificate,CRL,Private Key. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value.
*
* @par Dependency
* pkcs12.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*
*/
PSELINKDLL  SEC_VOID PKCS12_freeSafeBAG (PKCS12_SAFEBAG_S * pstSafeBags);



/*
    The following functions are duplicate functions that takes the pointer to a
    structure to be duplicated and returns a pointer to newly created structure
    copied with the information passed to the function.
*/


/**
* @defgroup PKCS12_dupMacData
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_MACDATA_S* PKCS12_dupMacData(PKCS12_MACDATA_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a PKCS12_MACDATA_S structure.
*
* @par Description
* Duplicates a PKCS12_MACDATA_S structure.
*
* @param[in] pSrc The PKCS12_MACDATA_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_MACDATA_S* Copy of the PKCS12_MACDATA_S
structure. [PKCS12_MACDATA_S*|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_MACDATA_S structure, 
to free this memory
* application has to call the PKCS12_freeMacData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_MACDATA_S* PKCS12_dupMacData(PKCS12_MACDATA_S* pSrc);

/**
* @defgroup PKCS12_dupSafeBagSetOf
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_SafeBagSetOf_S* PKCS12_dupSafeBagSetOf(PKCS12_SafeBagSetOf_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a PKCS12_SafeBagSetOf_S structure.
*
* @par Description
* Duplicates a PKCS12_SafeBagSetOf_S structure.
*
* @param[in] pSrc Pointer to the PKCS12_SafeBagSetOf_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_SafeBagSetOf_S* Copy of the PKCS12_SafeBagSetOf_S* structure.
[PKCS12_SafeBagSetOf_S*|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_SafeBagSetOf_S structure,
to free this memory
* application has to call the PKCS12_freeSafeBagSetOf.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_SafeBagSetOf_S* PKCS12_dupSafeBagSetOf(
                    PKCS12_SafeBagSetOf_S* pSrc);

/**
* @defgroup PKCS12_dupSafeBag
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_SAFEBAG_S* PKCS12_dupSafeBag(PKCS12_SAFEBAG_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a PKCS12_SAFEBAG_S structure.
*
* @par Description
* Duplicates a PKCS12_SAFEBAG_S structure.
*
* @param[in]  pSrc Pointer to the PKCS12_SAFEBAG_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_SAFEBAG_S* Copy of the PKCS12_SAFEBAG_S structure.
[PKCS12_SAFEBAG_S*|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_SAFEBAG_S structure, 
to free this memory
* application has to call the PKCS12_freeSafeBAG.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_SAFEBAG_S* PKCS12_dupSafeBag(PKCS12_SAFEBAG_S* pSrc);

/**
* @defgroup PKCS12_dupSafeContents
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_BAGLIST_S* PKCS12_dupSafeContents(PKCS12_BAGLIST_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a PKCS12_BAGLIST_S structure.
*
* @par Description
* Duplicates a PKCS12_BAGLIST_S structure.
*
* @param[in]  pSrc Pointer to the PKCS12_BAGLIST_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_BAGLIST_S* Copy of the PKCS12_BAGLIST_S structure. 
[PKCS12_BAGLIST_S*|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_BAGLIST_S structure,
to free this memory
* application has to call the PKCS12_freeBagList.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_BAGLIST_S* PKCS12_dupSafeContents(PKCS12_BAGLIST_S* pSrc);

/**
* @defgroup PKCS12_dupPFX
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_PFX_S* PKCS12_dupPFX(PKCS12_PFX_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a PKCS12_PFX_S structure.
*
* @par Description
* Duplicates a PKCS12_PFX_S structure.
*
* @param[in] pSrc Pointer to the PKCS12_PFX_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_PFX_S* Copy of the PKCS12_PFX_S structure. [PKCS12_PFX_S*|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_PFX_S structure,
to free this memory
* application has to call the PKCS12_freePFX.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_PFX_S* PKCS12_dupPFX(PKCS12_PFX_S* pSrc);

/**
* @defgroup PKCS12_dupAuthenticatedSafe
* @ingroup pkcs12Functions
* @par Prototype
* @code
* PKCS12_AUTHSAFE_S* PKCS12_dupAuthenticatedSafe(PKCS12_AUTHSAFE_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a PKCS12_AUTHSAFE_S structure.
*
* @par Description
* Duplicates a PKCS12_AUTHSAFE_S structure.
*
* @param[in] pSrc Pointer to the PKCS12_AUTHSAFE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS12_AUTHSAFE_S* Copy of the PKCS12_AUTHSAFE_S structure.
[PKCS12_AUTHSAFE_S*|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the PKCS12_AUTHSAFE_S structure, 
to free this memory
* application has to call the PKCS12_freeAuthSafe.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS12_AUTHSAFE_S* PKCS12_dupAuthenticatedSafe(
                                                       PKCS12_AUTHSAFE_S* pSrc);

/**
* @defgroup PKCS12_dupAttribute
* @ingroup pkcs12Functions
* @par Prototype
* @code
* SEC_ATTR_S* PKCS12_dupAttribute(SEC_ATTR_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a SEC_ATTR_S structure.
*
* @par Description
* Duplicates a SEC_ATTR_S structure.
*
* @param[in] pSrc Pointer to the SEC_ATTR_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ATTR_S* Copy of the SEC_ATTR_S structure. [SEC_ATTR_S*|N/A]
*
* @par Dependency
* pkcs12.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_ATTR_S structure, 
to free this memory
* application has to call the X509_freeAttribute.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_ATTR_S* PKCS12_dupAttribute(SEC_ATTR_S* pSrc);


#ifdef __cplusplus
}
#endif

#endif /* _IPSI_PKCS12_H */


