/*
                                                                              
                Copyright 2003, Huawei Technologies Co. Ltd.                  
                            ALL RIGHTS RESERVED                              
                                                                             
-----------------------------------------------------------------------------
                                                                             
                              wpki.h		                                  
                                                                             
  Project Code: SeCert                                                       
   Module Name: WPKI Module    	                                          
  Date Created: 2006-01-03                                                   
        Author: Karthik.P,Brijoo Bopanna					                  
  Descrption: Contains various wpki interface functions		              
                                                 
*/
#include "ipsi_pse_build_conf.h"

#ifndef IPSI_NO_WPKI
#ifndef _IPSI_WPKI_H
#define _IPSI_WPKI_H

#include "x509.h"
#include "x509_basictypes.h"

#include "sec_crypto.h"
#include "sec_list.h"
#include "asn-types.h"
#include "ipsi_types.h"
#include "sec_sys.h"

#ifdef __cplusplus
extern  "C" {
#endif


/* Identifies the usage value for different types of certificate */
/* Identifies certificate usage for client authentication*/
#define WPKI_CLIENT_AUTHENTICATION	0x01
/* Identifies certificate usage for digital signature certificates*/
#define WPKI_DIGITAL_SIGNATURE 0x02
/* Identifies certificate usage as a server cert*/
#define WPKI_X509_SERVER_CERT 0x04
/* Identifies certificate usage for code signing*/
#define WPKI_CODE_SIGNING   0x08
/* Identifies certificate usage as authority cert*/
#define WPKI_AUTHORITY_CERT 0x10


/*Flag to indicate whether OCSP has to be used*/
#define WPKI_ONLINESTATUS_REQUEST 0x80000000


/** @defgroup wpki
* This section contains the wpki Structures and Functions.
*/


/** @defgroup wpkiStructures
* @ingroup wpki
* This section contains the wpki Structures.
*/

/*  Structure which holds the algorithm identifier (i.e. is used to create the hash on the extensions)
	 and the digest of the extensions stored at the URL present in the extension refernce structure.*/

/**
* @defgroup WPKI_EXTNDIGEST_S
* @ingroup wpkiStructures
* @par Prototype
* @code
* typedef struct stDigest
* {
* 
* SEC_ALG_IDENTIFIER_S* pstDigestAlgorithm;
* SEC_AsnOcts_S stDigest;
* 
* }WPKI_EXTNDIGEST_S;
* @endcode
* 
* @datastruct pstDigestAlgorithm Contains the algorithm identifier that is used  to create the hash of the extensions.
* @datastruct stDigest Stores the digest which has been calculated on the whole DER-value, including tag and length,
* of an Extensions PDU.This digest is optional.
*/
typedef struct structDigest
{

	SEC_ALG_IDENTIFIER_S* pstDigestAlgorithm; /* contains the algorithm identifier that is used  to
											      create the hash of the extensions*/
	SEC_AsnOcts_S stDigest;					  /* Stores the digest which has been calculated on the whole DER-value,
											  including tag and length, of an Extensions PDU.This digest is optional*/

}WPKI_EXTNDIGEST_S;

/* This is a structure that stores the URL where the DER code of the extensions are kept and the digest for
	checking the integrity of those extensions. The URL points to a resource containing a DER-encoded
	value of type Extensions, carrying more (non-critical) extensions linked  with a certificate.
*/

/**
* @defgroup WPKI_EXTNREF_S
* @ingroup wpkiStructures
* @par Prototype
* @code
* typedef struct stExtnRef
* {
* 
* SEC_IA5String_S stURL;
* WPKI_EXTNDIGEST_S* pstDigest;
* } WPKI_EXTNREF_S;
* @endcode
* 
* @datastruct stURL URL points to a resource containing a DER-encoded value of type Extensions.
* @datastruct pstDigest Structure which holds the algorithm identifier and the digest of the extensions
* stored at the above URL.
*/
typedef struct stExtnRef
{

 	SEC_IA5String_S stURL;		  /* URL points to a resource containing a DER-encoded value of type Extensions */
 	WPKI_EXTNDIGEST_S* pstDigest; /* Structure which holds the algorithm identifier and the
								  digest of the extensions stored at the above URL*/
} WPKI_EXTNREF_S;

/* This is a structure which holds the domain information .It contains information about domain flags,
	authority identifiers and other non critical extensions that are stored at a mentioned URL.
	This structure carries information that pertain to the usage of the certificate and the domain
	in which it has been issued.The pstRCAName and pstExtnRef fields of this structure are optional.
 */
/**
* @defgroup WPKI_DOMAIN_INFO_S
* @ingroup wpkiStructures
* @par Prototype
* @code
* typedef struct stDomainInfo
* {
* 
* SEC_AsnBits_S  stFlags;
* SEC_NAME_S* pstRCAName;
* WPKI_EXTNREF_S* pstExtnRef;
*
* } WPKI_DOMAIN_INFO_S;
* @endcode
* 
* @datastruct stFlags Indicates that a certificate-processing application should perform some on-line
* checking of the certificates.
* @datastruct pstRCAName Contains the distinguished name of the domain root CA.This is optional field.
* @datastruct pstExtnRef Contain a URL pointing to other (non-critical) extensions pertaining to this
* certificate, and a digest of those extensions. This is optional field.
*/
typedef struct stDomainInfo
{

	SEC_AsnBits_S  stFlags;		/*Indicates that a certificate-processing
									application should perform some on-line checking of the certificates*/
	SEC_NAME_S* pstRCAName;		/* Contains the distinguished name of the domain root CA.This is optional field*/
	WPKI_EXTNREF_S* pstExtnRef;	/* Contain a URL pointing to other (non-critical)
									extensions pertaining to this certificate, and a digest of those extensions.
									This is optional field*/

 } WPKI_DOMAIN_INFO_S;


/** @defgroup wpkiFunctions
* @ingroup wpki
* This section contains the wpki Functions.
*/



/** 
* @defgroup WPKI_createCert
* @ingroup wpkiFunctions
* @par Prototype
* @code
* X509_CERT_S* WPKI_createCert(X509_CERTVERSION_E enVersion,
* SEC_BIGINT_S* pstCertSelNum,
* SEC_ALG_IDENTIFIER_S*	pstSignatureAlgoId,
* SEC_NAME_S* pstIssuerName,
* SEC_VALIDITY_S* pstValidity,
* SEC_NAME_S* pstSubjectName,
* SEC_PKEY_S* pstSubjectPubKey);
* @endcode
*
* @par Purpose
* To create WPKI certificate with mandatory fields.
* 	
* @par Description
* This function is used to create WPKI certificate with mandatory fields.
* The function can be used to create a Version 1 or a Version 3 certificate without extensions.
* To create Version 3 certificate all the extension structures that have been created
* has to be added to the certificate using WPKI_addExtnToCert API.
* All the input parameters mentioned has to be created before calling this function.
* The signature algorithm field in the certificate structure and the
* signature algorithm in the TBSCertificate structure is set with the same
* algorithm. The PublicKeyInfo structure is set with the encoded public
* key and the OID of the subjects Key type (eg : RSA,ECDSA).
* ECDH certificate can aslo be generated by passing the ECDH Public key to this function.
* WPKI certificates do not have a Issuer UID and subject  UID field.\n
* pstIssuerName and pstSubjectName has to be created using WPKI_createDN API.\n
* pstSignatureAlgId is created using X509_createAlgId API.\n
* pstValidity has to be created using X509_createValidity API.\n
* pstCertSelNum has to be created using SEC_cvtToBigInt API.\n
* pstSubjectPubKey is created using CRYPT_genKeyPair Crypto API.
*
* @param[in] enVersion Version of the certificate that has to be set [N/A]
* @param[in] pstCertSelNum A unique number to represent the certificate. A
* hexadecimal number that is obtain by converting a string of number to
* hexadecimal using SEC_cvtToBigInt function, which converts a string of
* numbers to hexadecimal string. [N/A]
* @param[in] pstSignatureAlgoId Algorithm used for signing the certificate.
* signing algorithm are RSA, ECDSA. [N/A]
* @param[in] pstIssuerName Certificate Issuer Name. This field identifies the
* issuer of the certificate. [N/A]
* @param[in] pstValidity Identifies the duration within which the
* certificate is valid. [N/A]
* @param[in] pstSubjectName Subject Name for whom the certificate is created. [N/A]
* @param[in] pstSubjectPubKey Public key associated with
* the certificate. The public key is encoded and set to the PublicKeyInfo field of
* the certificate. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* On successful execution X509_CERT_S certificate pointer filled with the passed
* fields is set and returned. [X509_CERT_S*|N/A]
* @retval X509_CERT_S* On failure conditions SEC_NULL is returned. The failure conditions may be\n
* 1. Input parameter NULL\n
* 2. Memory Allocation fails\n
* 3. Creation of SubjectPublicKeyInfo fails. [SEC_NULL|N/A]
*
* @par Dependency
* wpki.h
*
* @par Note
*
* N/A
*		
* @par Related Topics
*	N/A
*
* 
*/



PSELINKDLL X509_CERT_S* WPKI_createCert(X509_CERTVERSION_E	enVersion,
							 SEC_BIGINT_S* pstCertSelNum,
							 SEC_ALG_IDENTIFIER_S*	pstSignatureAlgoId,
							 SEC_NAME_S* pstIssuerName,
							 SEC_VALIDITY_S* pstValidity,
							 SEC_NAME_S* pstSubjectName,
							 SEC_PKEY_S* pstSubjectPubKey);







/**
* @defgroup WPKIExtn_createDomainInfo
* @ingroup wpkiFunctions
* @par Prototype
* @code
* WPKI_DOMAIN_INFO_S* WPKIExtn_createDomainInfo (SEC_UINT32  uiStatusFlag,
* SEC_NAME_S* pstAuthId ,
* SEC_CHAR*   pcURL,
* SEC_UCHAR*  pucEncodedExtn,
* SEC_UINT32  uiHashAlgID,
* SEC_UINT32  uiEncLen);
* @endcode
*
* @par Purpose
* To create the domain information structure.
* 
* @par Description
* The function creates the domain information structure.The status
* flag indicates whether the OCSP has to be used before using this
* certificate or not.The status flag indicates whether the OCSP
* must be used before	using the certificate by a client.
* The macro WPKI_ONLINESTATUS_REQUEST can be used as a
* status flag.Internally the given input will be cloned and then
* assigned for the domain information structure.
* If URL  field is present then DER code and hash algorithm must always
* be present.User should pass encoded data of the extensions list with
* correct encoded length.Note URL field will not be validated.The pstRCAName
* and pstExtnRef fields of WPKI_DOMAIN_INFO_S structure are optional.
*
* @param[in] uiStatusFlag Macro flag which indicates whether OCSP has to be used. [N/A]	 
* @param[in] pstAuthId Pointer to the authority identifier name structure.This is optional field. [N/A]
* @param[in] pcURL The URL from which the extensions has to be fetched.This is optional depending on
* pucEncodedExtn and  uiHashAlgID parameters. [N/A]
* @param[in] pucEncodedExtn Pointer to the der encoded value of type extensions.
* This is optional depending on pcURL and uiHashAlgID. [N/A]
* @param[in] uiHashAlgID The digest algorithm.This is optional depending on pucEncodedExtn and pcURL parameters. [N/A]
* @param[in] uiEncLen The size of the encoded buffer. [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval WPKI_DOMAIN_INFO_S* Pointer to the domain info struct. [WPKI_DOMAIN_INFO_S*|N/A]
* @retval WPKI_DOMAIN_INFO_S* If any of the input arguments NULL. [SEC_NULL|N/A]
* @retval WPKI_DOMAIN_INFO_S* If memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* wpki.h
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



PSELINKDLL WPKI_DOMAIN_INFO_S* WPKIExtn_createDomainInfo (SEC_UINT32  uiStatusFlag,
											   SEC_NAME_S* pstAuthId ,
											   SEC_CHAR*   pcURL,
											   SEC_UCHAR*  pucEncodedExtn,
											   SEC_UINT32  uiHashAlgID,
											   SEC_UINT32  uiEncLen);


/**
* @defgroup WPKI_getCertUsage
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_UINT32  WPKI_getCertUsage(X509_CERT_S* pstCert);
* @endcode
*
* @par Purpose
* To return the usage of the certificate.
*
* @par Description
* This function returns the usage of the certificate.
* This function returns an integer field, each bit of
* which is based on the certificate usage(Normally found in the first byte).
* The macros used for bit set are given below.The return value may
* be Zero,Value of one of the below or a combination of these.\n
* WPKI_CLIENT_AUTHENTICATION\n
* WPKI_CODE_SIGNING\n
* WPKI_DIGITAL_SIGNATURE\n
* WPKI_AUTHORITY_CERT\n
* WPKI_X509_SERVER_CERT
*
* @param[in] pstCert Pointer to the certificate structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 If input arguments NULL [0|N/A]
* @retval SEC_UINT32 Integer field indicating the usage of the certificate [SEC_UINT32|N/A]
*
* @par Dependency
* wpki.h
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




PSELINKDLL SEC_UINT32  WPKI_getCertUsage(X509_CERT_S* pstCert);


/**
* @defgroup WPKI_getURLFromDomainInfo
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_CHAR*  WPKI_getURLFromDomainInfo (WPKI_DOMAIN_INFO_S* pstDomainInfo);
* @endcode
*
* @par Purpose
* To get the URL from the domain information structure.
*
* @par Description
* This function is used to get the URL from the domain
* information structure.It returns a pointer to the URL
* in the given domain info structure.
* @param[in] pstDomainInfo Pointer to structure from which URL has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR* Holds the URL. [SEC_CHAR*|N/A]
* @retval SEC_CHAR* If the input is NULL or requested data is not available. [SEC_NULL|N/A]
*
* @par Dependency
* wpki.h
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



PSELINKDLL SEC_CHAR*  WPKI_getURLFromDomainInfo (WPKI_DOMAIN_INFO_S* pstDomainInfo);




/**
* @defgroup WPKI_getDomainInfoFlag
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_INT32  WPKI_getDomainInfoFlag(WPKI_DOMAIN_INFO_S* pstDomainInfo);
* @endcode
*
* @par Purpose
* To extract the domain info flag.
*
* @par Description
* This function is used to extract the domain info flag.
*
* @param[in] pstDomainInfo Structure from which domain info flag has to be extracted.
* When set indicates that a certificate processing application should perform some
* on-line checking of the certificates status before using it. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 On success [Value of the flag|N/A]
* @retval SEC_INT32 If the input is NULL [-1|N/A]
*
* @par Dependency
* wpki.h
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


PSELINKDLL SEC_INT32  WPKI_getDomainInfoFlag(WPKI_DOMAIN_INFO_S* pstDomainInfo);




/**
* @defgroup WPKI_getRCAName
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_NAME_S* WPKI_getRCAName (WPKI_DOMAIN_INFO_S* pstDomainInfo);
* @endcode
*
* @par Purpose
* To get the domain authority name from the domain info structure.
*
* @par Description
* This function is used to get the domain authority name
* from the domain info structure.It returns a pointer to the
* authority name in domain info structure.
*
* @param[in] pstDomainInfo Structure from which 
* authority identifier has to extracted. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_NAME_S* Holds the authority identifier [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* If the input is NULL or requested data is not available [SEC_NULL|N/A]
*
* @par Dependency
* wpki.h
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



PSELINKDLL SEC_NAME_S*   WPKI_getRCAName (WPKI_DOMAIN_INFO_S* pstDomainInfo);




/**
* @defgroup WPKI_signCertificate
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_UINT32 WPKI_signCertificate (X509_CERT_S* pstCert,
* SEC_PKEY_S* pstPrivateKey);
* @endcode
*
* @par Purpose
* To sign the certificate given the private key for signing.
*
* @par Description
* This function signs the certificate given the private key for signing.
* Before signing the certificate the algorithm Object Identifiers that
* are set in the certificate is compared. The certificate extensions is
* verified to find whether there are multiple existence of same extensions.
* The certificate will be verified for the valid or permitted fields corresponding
* to the certificate version.\n
* The private key used to sign the certificate has to match the algorithm
* object identifier set in the certificate.
* For CA certificate, if Cert sign bit is set in Key usage extension and basic constraint
* extension present then the criticality of the Basic Constriant extension has to be set
* to TRUE by the application.\n
* If all the conditions are verified then the certificate is signed and the
* set to the signature field of the certificate structure.
* 
* @param[in] pstPrivateKey The private key that is used to sign the certificate. [N/A]
* @param[out] pstCert The certificate to be signed. [N/A]
*
* @retval SEC_UINT32 On successful signing of the certificate. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 This error code is returned if input parameter is NULL or has incorrect data.
* [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 This error code is returned if validation of the extension fails. [SEC_ERR_INVALID_EXTN|N/A]
* @retval SEC_UINT32 This error code is returned if encoding of the certificate fails. [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 This error code is returned if sign of certificate fails. [SEC_ERR_SIGNING_FAILED|N/A]
* @retval SEC_UINT32 This error code is returned if the algorithm set in the certificate is not a signature algorithm.
* [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 This error code is returned if there is mismatch in the signature OIDs in the X509_CERT_S structure
* and SEC_TBSCERT_S structure. [SEC_ERR_OID_MISMATCH|N/A]
* @retval SEC_UINT32 This error code is returned if Subject Name is not present, which is a mandatory field.
* [SEC_ERR_NAME_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 This error code is returned in case of Invalid version. Data is not consistent with version.
* [SEC_ERR_INVALID_VERSION|N/A]
* @retval SEC_UINT32 This error code is returned if duplicate Extension is available. [SEC_ERR_DUPLICATE_EXTN|N/A]
* @retval SEC_UINT32 This error code is returned if required extension is not available in certificate.
* [SEC_ERR_EXTN_NOT_AVAILABLE|N/A]
*
* @par Dependency
* wpki.h
*
* @par Note
*
* While creating certificate, WPKI specific API's must be used.
*		
* @par Related Topics
* N/A
* 
* 
*/


PSELINKDLL SEC_UINT32  WPKI_signCertificate (X509_CERT_S* pstCert, SEC_PKEY_S* pstPrivateKey);



/**
* @defgroup WPKI_createDN
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_NAME_S* WPKI_createDN(SEC_UINT32 uiDNAttrLen, X509_DN_ATTR_VALUE_S* pstDNAttrValue);
* @endcode
*
* @par Purpose
* To create X509 name structure.
*
* @par Description
* This functions is used to create X509 name structure. Input to this
* function is an array of structures and the count of the number of
* structures in the array. Each structure contains the CID of the attribute,
* stringtype and data. Internally the input structure will be parsed and the
* name  will be created. There cannot be more than 5 structures in the input
* array.There should be a minimum of one structure atleast.
* The CID that can be input are given below.\n
* Country,  [ TYPE_COUNTRY ]\n
* Organization, [ TYPE_ORGANIZATION ]\n
* Organization Unit Name, [ TYPE_ORG_UNIT_NAME ]\n
* State or Province name, [ TYPE_STATE ]\n
* Serial Number, [ TYPE_SERIAL_NUMBER ]\n
* Domain Component, [ TYPE_DOMAIN_COMPONENT ]\n
* Common Name, [ TYPE_COMMON_NAME ]\n
* TYPE_COUNTRY, TYPE_SERIAL_NUMBER can only be represented
* in PrintableString format.\n
* TYPE_DOMAIN_COMPONENT, can only be represented in IA5String.\n
* All the other remaining types can take one of the following types as input:\n
* PrintableString\n
* UTF8String\n
* UniversalString\n
* TeletexString\n
* BMPString.\n
* The string is not validated for String Type other than Printable string.
* 
* @param[in] uiDNAttrLen The number of structures in the array. [N/A]
* @param[in] pstDNAttrValue Pointer to the array of structures. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_NAME_S* On successful execution pointer to SEC_NAME_S structure is returned. [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* On failure conditions SEC_NULL is returned.
* The failures conditions can be one of the following:\n
* 1. Input parameter is NULL.\n
* 2. Memory Allocation fails\n
* 3. Attribute Type may not be represented in the requested String format.\n
* 4. Input data is incorrect.\n
* 5. More than 5 attributes in name. [SEC_NULL|N/A]
*
*
* @par Dependency
* wpki.h
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


PSELINKDLL SEC_NAME_S* WPKI_createDN(SEC_UINT32 uiDNAttrLen, X509_DN_ATTR_VALUE_S* pstDNAttrValue);



/**
* @defgroup WPKI_addExtnToCert
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_UINT32 WPKI_addExtnToCert(SEC_EXTN_S* pstExtension,
* X509_CERT_S* pstCertificate);
* @endcode
*
* @par Purpose
* To add the extension to the certificate.
*
* @par Description
* This function is used to add the extension to the certificate.The given
* extension that is input will be cloned internally.
* The extension structure has to be created  using
* X509_createExtn API.The possible extensions that can be added accoring to
* OMA standard are as given below.\n
* AUTHORITYKEYIDENTIFIER,\n
* SUBJECTKEYIDENTIFIER,\n
* KEYUSAGE,\n
* CERTIFICATEPOLICIES,\n
* SUBJECTALTNAME,\n
* BASICCONSTRAINTS,\n
* NAMECONSTRAINTS,\n
* POLICYCONSTRAINTS,\n
* AUTHORITYINFOACCESS,\n
* EXTKEYUSAGE,\n
* DOMAINCOMPONENT\n
* In addition to the above it allows to add any unrecognized non critical extensions.
*
* @param[in] pstExtension The extension that has to be placed
* in the certificate. [N/A]
* @param[out] pstCertificate The certificate to which
* the extension has to be added. [N/A]
*
* @retval SEC_UINT32 On successful execution. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 This error code is returned if duplication of the extension fails.
* [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 This error code is returned when the input argument is incorrect.
* [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 This error code is returned if memory allocation fails.
* [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 This error code is returned if the extension is not valid for a WPKI certificate.
* [SEC_ERR_INVALID_EXTN|N/A]
*
* @par Dependency
* wpki.h
*
* @par Note
*
* Extension structure passed as input to this function has to be freed since the structure is duplicated.
*		
* @par Related Topics
* N/A	
*
* 
*/


PSELINKDLL SEC_UINT32 WPKI_addExtnToCert(SEC_EXTN_S* pstExtension,
							  X509_CERT_S* pstCertificate);




/**
* @defgroup WPKI_validateCertUsage
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_BOOL  WPKI_validateCertUsage(X509_CERT_S* pstCert,SEC_UINT32 uiType);
* @endcode
*
* @par Purpose
* To verify whether the given certificate will match
* all the constraints for a given usage of the certificate.
*
* @par Description
* This function will be used to verify whether the given certificate will match
* all the constraints for a given usage of the certificate.If the certificate
* matches all the constraints for a given type then a TRUE will be returned else
* a FALSE will be retuned to the user.The usage type for a given certificate
* can be entered by using the following set of macros.\n
* WPKI_CLIENT_AUTHENTICATION\n
* WPKI_CODE_SIGNING\n
* WPKI_DIGITAL_SIGNATURE\n
* WPKI_AUTHORITY_CERT\n
* WPKI_X509_SERVER_CERT\n
* If the given usage type has a bit set other than the appropraite one a
* SEC_FALSE will be returned.
*
* @param[in] pstCert Pointer to the certificate structure. [N/A]
* @param[in] uiType The usage type of the certificate. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BOOL If input arguments NULL. [FALSE|N/A]
* @retval SEC_BOOL If it satisfies all the constraints for a given type. [True|N/A]
* @retval SEC_BOOL If it does not satisfy the constraints for a certain usage. [False|N/A]
*
* @par Dependency
* wpki.h
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


PSELINKDLL SEC_BOOL  WPKI_validateCertUsage(X509_CERT_S* pstCert,SEC_UINT32 uiType);



/**
* @defgroup WPKI_verifyExtnDigest
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_BOOL  WPKI_verifyExtnDigest (WPKI_DOMAIN_INFO_S* pstDomainInfo,
* SEC_UCHAR*  pucEncodedExtn,
* SEC_UINT32  uiEncLen);
* @endcode
*
* @par Purpose
* To take domain information and encoded extension list
* and its length as input and to calculate the hash on the extension structure
* and compare it with the digest structure.
*
* @par Description
* This function will take domain information and encoded extension list
* and its length as input,calculates the hash on the extension structure
* and compares it with the digest structure.The digest for verification
* is present internally in the extension refernce structure. If extension
* reference inside domain information is null,SEC_TRUE will be returned
* to the caller.If encoded length is equal to 0 SEC_FALSE will be returned.
* User should pass encoded data of the extensions list with correct encoded length.
*
* @param[in] pstDomainInfo Pointer to the domain information structure. [N/A]
* @param[in] pucEncodedExtn The buffer containing the encoded extension in DER format. [N/A]
* @param[in] uiEncLen The size of the encoded buffer. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BOOL If the digest matches or digest structure is not present internally. [SEC_TRUE|N/A]
* @retval SEC_BOOL If the digest does not match. [SEC_FALSE|N/A]
*
* @par Dependency
* wpki.h
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


PSELINKDLL SEC_BOOL  WPKI_verifyExtnDigest (WPKI_DOMAIN_INFO_S* pstDomainInfo,
								 SEC_UCHAR*  pucEncodedExtn,
								 SEC_UINT32  uiEncLen);



/**
* @defgroup WPKI_encodeExtnList
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_UCHAR*  WPKI_encodeExtnList( SEC_List_S* pExtnList, SEC_UINT32* puiEncLen);
* @endcode
*
* @par Purpose
* To encode the given extension list.
*
* @par Description
* This function is used to encode the given extension list.The extensions present
* in the list must be non critical extensions.
*
* @param[in] pExtnList Pointer to the list which has to be encoded. [N/A]
* @param[out] puiEncLen Pointer to the encoded length. [N/A]
*
* @retval SEC_UCHAR* Pointer to the buffer containing the encoded data. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* It returns null in the following cases\n
* 1) Invalid parameter\n
* 2) memory allocation fails\n
* 3) Encode fails\n
* 4) Passing critical extensions in the list. [SEC_NULL|N/A]
*
* @par Dependency
* wpki.h
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


PSELINKDLL SEC_UCHAR*  WPKI_encodeExtnList( SEC_List_S* pExtnList, SEC_UINT32* puiEncLen);



/**
* @defgroup WPKI_decodeExtnList
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_List_S*  WPKI_decodeExtnList( SEC_UCHAR* pucEncodedExtnList,
* SEC_UINT32 uiEncLen, SEC_UINT32* puiDecLen);
* @endcode
*
* @par Purpose
* To decode the encoded extension list.
*
* @par Description
* This function is used to decode the encoded extension list.
* Error is returned if decoded extension contains critical extensions.
*
* @param[in] pucEncodedExtnList Encoded extension list that has
* to be decoded. [N/A]
* @param[in] uiEncLen The length of the encoded data. [N/A]
* @param[out] puiDecLen Bytes that are decoded. [N/A]
*
* @retval SEC_List_S* Pointer to the list containing extensions [SEC_List_S*|N/A]
* @retval SEC_List_S* It returns null in the following cases\n
* 1) Invalid parameters\n
* 2) memory allocation fails\n
* 3) Decode fails\n
* 4) If critical extensions present in decoded extension list. [SEC_NULL|N/A]
*
* @par Dependency
* wpki.h
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



PSELINKDLL SEC_List_S*  WPKI_decodeExtnList( SEC_UCHAR*  pucEncodedExtnList,SEC_UINT32  uiEncLen,SEC_UINT32* puiDecLen);



/**
* @defgroup WPKI_freeDomainInfo
* @ingroup wpkiFunctions
* @par Prototype
* @code
* SEC_VOID WPKI_freeDomainInfo(WPKI_DOMAIN_INFO_S* pstDomainInfo);
* @endcode
*
* @par Purpose
* To free the domain information structure.
*
* @par Description
* This function is used to free the domain information structure.
*
* @param[in] pstDomainInfo Domain information structure that
* has to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* wpki.h
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


PSELINKDLL SEC_VOID WPKI_freeDomainInfo(WPKI_DOMAIN_INFO_S* pstDomainInfo);

#ifdef __cplusplus
}
#endif

#endif /* _IPSI_WPKI_H */
#endif
