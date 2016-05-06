/*

                Copyright 2005, Huawei Technologies Co. Ltd.
                           ALL RIGHTS RESERVED

------------------------------------------------------------------------------

                              pkcs7.h

  Project Code: SeCertV100R001
   Module Name: PKCS7
  Date Created: 2005-07-01
        Author: konark
   Description: This module creates and parses PKCS7 message. Which  is used
				 to communicate where ever message integrity and  security is
				 required .  PKCS7 is used to send Certification request , to
				 send back  issued certificates  and in many other places.
				 PKCS7 message format is inter operable with the
			     Privacy-Enhanced Mail (PEM) and vise versa. In this section
				 functions are defined to create and parse a PKCS #7 message                                                                                *

*/

#include "ipsi_pse_build_conf.h"

#ifndef _IPSI_PKCS7_H_
#define _IPSI_PKCS7_H_

#include "asn-types.h"
#include "x509_basictypes.h"
#include "sec_sys.h"
#include "sec_crypto.h"
#include "ipsi_types.h"
#include "sec_list.h"
#include "x509v3_extn.h"

#ifdef __cplusplus
extern "C" {
#endif


/* version is the syntax version number. It shall be 1 for this version of the standard.
	The differences between version '1' SignedData and version '0' is
	1.The digestAlgorithms and signerInfos fields may contain zero
	   elements in version 1, but not in version 0.
	2. The CRLs field is allowed in version 1, but not in version 0.  */
#define  PKCS7_SIGNED_VERSION          1

/*version is the syntax version number. It shall be 0 for this version of the standard. */
#define  PKCS7_ENVELOPED_VERSION       0

/* version is the syntax version number. It shall be 1 for this version of the standard.
	The difference between version 1 SignedAndEnvelopedData and version 0 SignedAndEnvelopedData
	is that the CRLs field is allowed in version 1, but not in version 0. */
#define  PKCS7_SIGNENVELOPED_VERSION   1

/* version is the syntax version number. It shall be 0 for this version of the standard. */
#define  PKCS7_DIGESTED_VERSION        0

/* version is the syntax version number. It shall be 0 for this version of the standard. */
#define  PKCS7_ENCRYPTED_VERSION       0

/* version is the syntax version number. It shall be 1 for this version of the standard.
	The difference between version 1 SignerInfo and version 0 SignerInfo
	is in the message-digest encryption process .Only the PEM-compatible processes are different */
#define  PKCS7_SIGNERINFO_VERSION      1

/* version is the syntax version number. It shall be 0 for this version of the standard. */
#define  PKCS7_RECIPINFO_VERSION       0



/*This type is defined in PKCS #6  A type that consists of an X.509 public-key certificate
	and a set of attributes, collectively signed by the issuer of the X.509 public-key certificate.
	 Not supported in current implementation  */
typedef SEC_VOID*  PKCS7_EXTNDCERT_S;
/** @defgroup pkcs7
* This section contains the pkcs7 Enums, Structures, Unions, and Functions.
*/

/** @defgroup pkcs7Enum
* @ingroup pkcs7
* This section contains the pkcs7 Enum.
*/

/** @defgroup pkcs7Structures
* @ingroup pkcs7
* This section contains the pkcs7 Structures.
*/

/** @defgroup pkcs7Union
* @ingroup pkcs7
* This section contains the pkcs7 Union.
*/

/* This Enum is used identify X509 certificate and Extended certificate */
/**
* @defgroup PKCS7_CERT_E
* @ingroup pkcs7Enum
* @par Prototype
* @code
* typedef enum enPKCS7CertType
* {
* PKCS7_CERT_TYPE_X509,
* PKCS7_CERT_TYPE_EXTND
* }PKCS7_CERT_E;
* @endcode
*
* @datastruct PKCS7_CERT_TYPE_X509 Enum for X509 certificate.
* @datastruct PKCS7_CERT_TYPE_EXTND Enum for Extended certificate.
*/
typedef enum enPKCS7CertType
{
	PKCS7_CERT_TYPE_X509,						/* Enum for X509 certificate */
	PKCS7_CERT_TYPE_EXTND						/* Enum for Extended certificate */
}   PKCS7_CERT_E;

/* Union of X509 and Extentded certificate pointers. The PKCS7_CERT_U
	type gives either a PKCS #6 extended certificate or an X.509 certificate*/
/**
* @defgroup PKCS7_CERT_U
* @ingroup pkcs7Union
* @par Prototype
* @code
* typedef  union unPKCS7CertType
* {
* X509_CERT_S*       pstX509;
* PKCS7_EXTNDCERT_S* pstExtended;
* }PKCS7_CERT_U;
* @endcode
*
* @datastruct pstX509 pointer to an X509 certificate.
* @datastruct pstExtended PKCS7 ExtendedCertificate which is defined in PKCS#6.
* Not supported in current implementation.
*/

typedef  union unPKCS7CertType
{
	X509_CERT_S* pstX509;						/* X509 Certificate */
	PKCS7_EXTNDCERT_S* pstExtended;				/* PKCS7 ExtendedCertificate which is defined in PKCS#6
													Not supported in current implementation*/
}PKCS7_CERT_U;

/* PKCS7 certificate structure. First field enum (PKCS7_CERT_E) decides the whether the
	unCert pointer points to the X509 certificate OR the Extended certificate defined in PKCS#6 */

/**
* @defgroup PKCS7_CERT_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7CertType
* {
* PKCS7_CERT_E enCertType;
* PKCS7_CERT_U unCert;
* } PKCS7_CERT_S;
* @endcode
*
* @datastruct enCertType Enum to choose either X509 OR Extended certificate.
* @datastruct unCert Union of X509 and Extended certificate struct pointers.
*/
typedef struct stPKCS7CertType
{
     PKCS7_CERT_E enCertType;					/* Enum to choose either X509 OR Extended certificate */
    PKCS7_CERT_U unCert;						/* Union of X509 and Extended certificate struct pointers */
} PKCS7_CERT_S;

/* Encrypted Content info structure holds the encrypted data and assosiated information like
	type of the content encrypted (can be any of the 6 PKCS7 types), algorithm used to encrypt
	the data and finally encrypted content*/
/**
* @defgroup PKCS7_ENCRYPTED_INFO_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7EncryptedContentInfo
* {
*  SEC_AsnOid_S          stContentType;
*  SEC_ALG_IDENTIFIER_S* pstEncryptAlg;
*  SEC_AsnOcts_S         stEncryptedContent;
* } PKCS7_ENCRYPTED_INFO_S;
* @endcode
*
* @datastruct stContentType Indicates the type of the content Encrypted.
* @datastruct pstEncryptAlg Content Encryption Algorithm Identifier,
* encryption algorithm (symmetric) and any associated parameters under which the content is encrypted.
* @datastruct stEncryptedContent EncryptedContent is the result of encrypting the content.
*/
typedef struct stPKCS7EncryptedContentInfo
{
	SEC_AsnOid_S stContentType;					/* contentType indicates the type of the content Encrypted*/
	SEC_ALG_IDENTIFIER_S* pstEncryptAlg;		/* Content Encryption Algorithm Identifier, encryption algorithm (symmetric)
												and any associated parameters under which the content is encrypted */
	SEC_AsnOcts_S  stEncryptedContent;			/*  EncryptedContent is the result of encrypting the content */
} PKCS7_ENCRYPTED_INFO_S;

/*  Per-recipient information is represented in the type RecipientInfo. It consist of the information like
	intended recipients certificate issuer name and serial number, Key encryption algorithm and the encrypted key  */
/**
* @defgroup PKCS7_RECIPIENT_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7Recipient
* {
*  SEC_AsnInt               version;
*  SEC_ISSUER_AND_SERIAL_S* pstIssuerAndSN;
*  SEC_ALG_IDENTIFIER_S*    pstKeyEncryptionAlg;
*  SEC_AsnOcts_S            stEncryptedKey;
* } PKCS7_RECIPIENT_S;
* @endcode
*
* @datastruct version It is the syntax version number. It shall be 0 for this version of the standard.
* @datastruct pstIssuerAndSN Issuer And SerialNumber identifies the recipient's certificate (and thereby
* the recipient's distinguished name and public key) by issuer distinguished name and issuer-specific serial number.
* @datastruct pstKeyEncryptionAlg KeyEncryptionAlgorithm identifies the key-encryption algorithm (and any associated
* parameters) under which the content-encryption key is encrypted with the recipient's public key ALGID_RSA ( R S A)
* ALGID_DSA ( D S A ), ALGID _ECDSA ( E C D S A ).
* @datastruct stEncryptedKey Encrypted Key is the result of encrypting the content-encryption key with the
* recipient's public key.
*/
typedef struct stPKCS7Recipient
{
	SEC_AsnInt version;							/* version is the syntax version number. It shall be 0 for
													this version of the standard */
	SEC_ISSUER_AND_SERIAL_S* pstIssuerAndSN;	/* issuer And SerialNumber identifies the recipient's certificate
													(and thereby the recipient's distinguished name and public key)
													by issuer distinguished name and issuer-specific serial number */
	SEC_ALG_IDENTIFIER_S* pstKeyEncryptionAlg;	/* keyEncryptionAlgorithm identifies the key-encryption algorithm
													(and any associated parameters) under which the content-encryption
													key is encrypted with the recipient's public key ALGID_RSA ( R S A)
													ALGID_DSA ( D S A ), ALGID _ECDSA ( E C D S A ) */
	SEC_AsnOcts_S  stEncryptedKey;				/* Encrypted Key is the result of encrypting the content-encryption
													key with the recipient's public key  */
} PKCS7_RECIPIENT_S;

/* Per-signer information is represented in the type Signer Info. It consist of the signer's information like
	signer certificate issuer name and serial number, Key Digest algorithm used to calculate hash while signing,
	Asymmetric algorithm OR Public key assosiated algorithm used to encrypt hash and optional Authenticated and
    Un authenticated attributes which are specific to signer defined in PKCS#9 . There are 6 PKCS7 attributes
	1. Content type ( CID_PKCS9_AT_CONTENTTYPE ) it's of type OID
	2. Message digest ( CID_PKCS9_AT_MESSAGEDIGEST ) Message digest calculated over the content
	3. Signing time ( CID_PKCS9_AT_SIGNINGTIME ) It specifies the time at which the signer (purportedly)
					 performed the signing process.
	4. Random nonce ( CID_PKCS9_AT_RANDOMNONCE ) It may beused by a signer unable (or unwilling) to specify the
					time at which the signing process was performed. it will make it possible for the signer to
					protect against certain attacks, i.e. replay attacks.
	5. Sequence number ( CID_PKCS9_AT_SEQUENCENUMBER ) A signer wishing to associate a sequence number to all
						signature operations  may use it as an alternative to the randomNonce attribute.
	6. Counter signature ( CID_PKCS9_AT_COUNTERSIGNATURE ) The counterSignature attribute type specifies
							one or more signatures on the content octets. The countersignature attribute must
							be an unauthenticated PKCS #7 attribute.*/
/**
* @defgroup PKCS7_SIGNER_INFO_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7SignerInfo
* {
*  SEC_AsnInt               version;
*  SEC_ISSUER_AND_SERIAL_S* pstIssuerAndSN;
*  SEC_ALG_IDENTIFIER_S*    pstDigestAlg;
*  SEC_List_S*              pstAuthAttrs;
*  SEC_ALG_IDENTIFIER_S*    digestEncryptionAlg;
*  SEC_AsnOcts_S            stEncryptedDigest;
*  SEC_List_S*              pstUnauthAttrs;
* } PKCS7_SIGNER_INFO_S;
* @endcode
*
* @datastruct version Version is the syntax version number. It shall be 1 for this version of the standard.
* @datastruct pstIssuerAndSN IssuerAndSerialNumber specifies the signer's certificate (and thereby the signer's
* distinguished name and public key) by issuer distinguished name and issuer-specific	serial number.
* @datastruct pstDigestAlg DigestAlgorithm identifies the message-digest algorithm (and any associated parameters)
* under which the content and authenticated attributes (if present) are digested.
* @datastruct pstAuthAttrs AuthenticatedAttributes is a set of attributes that are signed (i.e., authenticated) by
* the signer. The field is optional If the field is present, it must contain, at a minimum, two attributes:
* 1. Content type and 2. Message digest
* @datastruct digestEncryptionAlg digestEncryptionAlgorithm identifies the digest-encryption algorithm (and any
* associated parameters) under which the message digest and associated information are encrypted with the signer's private key.
* @datastruct stEncryptedDigest encryptedDigest is the result of encrypting the message digest and associated information
* with the signer's private key.
* @datastruct pstUnauthAttrs unauthenticatedAttributes is a set of attributes that are not signed.
*/
typedef struct stPKCS7SignerInfo
{
	SEC_AsnInt version;							/* version is the syntax version number. It shall be 1 for
													this version of the standard. */
	SEC_ISSUER_AND_SERIAL_S* pstIssuerAndSN;	/* issuerAndSerialNumber specifies the signer's certificate
				(and thereby the signer's distinguished name and public key) by issuer distinguished name and
				issuer-specific	serial number. */
	SEC_ALG_IDENTIFIER_S* pstDigestAlg;			/* DigestAlgorithm identifies the message-digest algorithm
				(and any associated parameters) under which the content and authenticated attributes (if present)
				are digested */
	SEC_List_S* pstAuthAttrs;					/* authenticatedAttributes is a set of attributes that are signed
				(i.e., authenticated) by the signer. The field is optional If the field is present, it must contain,
				at a minimum, two attributes: 1. Content type and 2. Message digest */
	SEC_ALG_IDENTIFIER_S* digestEncryptionAlg;	/* digestEncryptionAlgorithm identifies the digest-encryption algorithm
				(and any associated parameters) under which the message digest and associated information are encrypted
				with the signer's private key. */
	SEC_AsnOcts_S stEncryptedDigest;			/* encryptedDigest is the result of encrypting the message digest and
				associated information with the signer's private key. */
	SEC_List_S* pstUnauthAttrs;					/* unauthenticatedAttributes is a set of attributes that are not signed  */
} PKCS7_SIGNER_INFO_S;


/**
* @defgroup PKCS7_CONTENT_INFO_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7_ContentInfo
*{
*	SEC_AsnOid_S stContentType;
*	SEC_AsnAnyDefinedBy_S stContent;
*}PKCS7_CONTENT_INFO_S;
* @endcode
*
* @datastruct stContentType object Identifier.
* @datastruct stContent ASN info.
*/

typedef struct stPKCS7_ContentInfo/* SEQUENCE */
{
	SEC_AsnOid_S stContentType; /* OBJECT IDENTIFIER */
	SEC_AsnAnyDefinedBy_S stContent; /* [0] EXPLICIT ANY DEFINED BY contentType OPTIONAL */
}PKCS7_CONTENT_INFO_S;


/* Signed data holds the Data ( present inside content info)  , signature ( part of signer info) , Certificates and CRL's to
	facilitate recipient to verify signature. The signed-data content type consists of content of any defined PKCS7 type and encrypted message
	digests of the content for zero or more signers. The encrypted digest for a signer is a "digital signature" on the content
	for that signer. Any type of content can be signed by any number of signers in parallel. Furthermore, the syntax has a degenerate
	case in which there are no signers on the content. The degenerate case provides a means for disseminating certificates and
	certificate-revocation lists.  */
/**
* @defgroup PKCS7_SIGNED_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7SignedData
* {
*  SEC_AsnInt            version;
*  SEC_List_S*           pstDigestAlg;
*  PKCS7_CONTENT_INFO_S* pstContentInfo;
*  SEC_List_S*           pstCertificates;
*  SEC_List_S*           pstCrls;
*  SEC_List_S*           pstSignerInfos;
* } PKCS7_SIGNED_S;
* @endcode
*
* @datastruct version It shall be 1 for this version of the standard.
* @datastruct pstDigestAlg digestAlgorithms is a collection of message-digest algorithm identifiers. There may be any
* number of elements in the collection, including zero. Each element identifies the message-digest algorithm (and any
* associated parameters) under which the content is digested for a some signer.
* @datastruct pstContentInfo contentInfo is the content that is signed. It can have any of the PKCS#7 data type.
* @datastruct pstCertificates certificates is a set of PKCS #6 extended certificates OR X.509 certificates. It is
* intended that the set be sufficient to contain chains from a recognized "root" or "top-level certification authority" to
* all of the signers in the signerInfos field.
* @datastruct pstCrls CRLs is a set of certificate-revocation lists. It is intended that the set contain
* information sufficient to determine whether or not the certificates in the certificates field are "hot listed," but such
* correspondence is not necessary.
* @datastruct pstSignerInfos signerInfos is a collection of per-signer information. It holds infor mation of Signers
* Certificate Issuer , serial number and signature .There may be any number of elements in the collection, including zero.
*/
typedef struct stPKCS7SignedData
{
	SEC_AsnInt version;							/* It shall be 1 for this version of the standard.*/
	SEC_List_S* pstDigestAlg;					/* digestAlgorithms is a collection of message-digest algorithm identifiers.
				There may be any number of elements in the collection, including zero. Each element identifies the message-digest
				algorithm (and any associated parameters) under which the content is digested for a some signer.  */
	PKCS7_CONTENT_INFO_S* pstContentInfo;		/* contentInfo is the content that is signed. It can have any of the PKCS#7 data type */
	SEC_List_S* pstCertificates;				/* certificates is a set of PKCS #6 extended certificates OR X.509 certificates. It is
				intended that the set be sufficient to contain chains from a recognized "root" or "top-level certification authority" to
				all of the signers in the signerInfos field.*/
	SEC_List_S* pstCrls;						/* CRLs is a set of certificate-revocation lists. It is intended that the set contain
				information sufficient to determine whether or not the certificates in the certificates field are "hot listed," but such
				correspondence is not necessary. */
	SEC_List_S* pstSignerInfos;					/* signerInfos is a collection of per-signer information. It holds infor mation of Signers
												    Certificate Issuer , serial number and signature .There may be any number of
													elements in the collection, including zero. */
} PKCS7_SIGNED_S;


/* Enveloped holds encrypted data ( part of Encrypted content info ) and intended recipient info.
	The combination of encrypted content and encrypted content-encryption key  is a
	"Digital Envelope" for that recipient. Any type of content can be enveloped for any number of recipients
	in parallel ( same enveloped data can be sent to mulitple recipients by adding recipient info). */
/**
* @defgroup PKCS7_ENVELOPED_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7EnvelopedData
* {
*  SEC_AsnInt              version;
*  SEC_List_S*             pstRecipientInfos;
*  PKCS7_ENCRYPTED_INFO_S* pstEncryptedContentInfo;
* }  PKCS7_ENVELOPED_S;
* @endcode
*
* @datastruct version It shall be 0 for this version of the standard.
* @datastruct pstRecipientInfos RecipientInfos is a collection of per-recipient information.
* There must be at least one element in the collection.
* @datastruct pstEncryptedContentInfo pstEncryptedContentInfo is the encrypted content information.
* It include information like type of Content encrypted, Algorithm used to encrypt and encrypted data.
*/
typedef struct stPKCS7EnvelopedData
{
	SEC_AsnInt version;							/* It shall be 0 for this version of the standard. */
	SEC_List_S* pstRecipientInfos;				/* RecipientInfos is a collection of per-recipient information.
													There must be at least one element in the collection.*/
	PKCS7_ENCRYPTED_INFO_S* pstEncryptedContentInfo; /* pstEncryptedContentInfo is the encrypted content information.
														It include information like type of Content encrypted , Algorithm
														used to encrypt and encrypted data*/
}  PKCS7_ENVELOPED_S;

/* The signed-and-enveloped-data content type is sequential combination of signed-data and
	enveloped-data content types. The signed-and-enveloped-data content type consists of encrypted content
	of any defined PKCS7 type, encrypted content-encryption keys ( key used to encrypt content) for one or more recipients,
	and doubly encrypted message digests for one or more signers.
	1. The "double encryption" consists of an encryption with a signer's private key followed by an encryption
	with the content-encryption key.
	2. signed-and-enveloped-data content type does not have authenticated or unauthenticated attributes */
/**
* @defgroup PKCS7_SIGN_ENVELOPED_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7SignedEnvelopedData
* {
* SEC_AsnInt              version;
* SEC_List_S*             pstRecipientInfos;
* SEC_List_S*             pstDigestAlg;
* PKCS7_ENCRYPTED_INFO_S* pstEncryptedContentInfo;
* SEC_List_S*             pstCertificates;
* SEC_List_S*             pstCrls;
* SEC_List_S*             pstSignerInfos;
* } PKCS7_SIGN_ENVELOPED_S;
* @endcode
*
* @datastruct version It shall be 1 for this version of the standard.
* @datastruct pstRecipientInfos recipientInfos is a collection of per-recipient information. There must be at least one
* element in the collection. It holds encrypted content-encryption keys ( key used to encrypt content) encrypted with
* recipients public key.
* @datastruct pstDigestAlg DigestAlgorithms is a collection of message-digest algorithm identifiers.
* @datastruct pstEncryptedContentInfo pstEncryptedContentInfo is the encrypted content information.
* It include information like type of Content encrypted , Algorithm used to encrypt and encrypted data.
* @datastruct pstCertificates certificates is a set of PKCS #6 extended certificates OR X.509 certificates. It is
* intended that the set be sufficient to contain chains from a recognized "root" or "top-level certification authority" to
* all of the signers in the signerInfos field.
* @datastruct pstCrls CRLs is a set of certificate-revocation lists. It is intended that the set contain
* information sufficient to determine whether or not the certificates in the certificates field are "hot listed," but such
* correspondence is not necessary.
* @datastruct pstSignerInfos signerInfos is a collection of per-signer information. It holds information of Signers
* Certificate Issuer , serial number and signature .There may be any number of elements in the collection, There must be at least one element in the collection.
*/
typedef struct stPKCS7SignedEnvelopedData
{
	SEC_AsnInt version;							/*It shall be 1 for this version of the standard */
	SEC_List_S* pstRecipientInfos;				/* recipientInfos is a collection of per-recipient
				information. There must be at least one element in the collection. It holds encrypted
				content-encryption keys ( key used to encrypt content) encrypted with recipients public key*/
	SEC_List_S* pstDigestAlg;					/* DigestAlgorithms is a collection of message-digest
													algorithm identifiers */
	PKCS7_ENCRYPTED_INFO_S* pstEncryptedContentInfo; /* pstEncryptedContentInfo is the encrypted content information.
														It include information like type of Content encrypted , Algorithm
														used to encrypt and encrypted data*/
	SEC_List_S* pstCertificates;				/* certificates is a set of PKCS #6 extended certificates OR X.509 certificates. It is
				intended that the set be sufficient to contain chains from a recognized "root" or "top-level certification authority" to
				all of the signers in the signerInfos field.*/
	SEC_List_S* pstCrls;						/* CRLs is a set of certificate-revocation lists. It is intended that the set contain
				information sufficient to determine whether or not the certificates in the certificates field are "hot listed," but such
				correspondence is not necessary. */
	SEC_List_S* pstSignerInfos;					/* signerInfos is a collection of per-signer information. It holds infor mation of Signers
												    Certificate Issuer , serial number and signature .There may be any number of
													elements in the collection, There must be at least one element in the collection. */
} PKCS7_SIGN_ENVELOPED_S;

/* The digested-data content type consists of content of any defined PKCS7 type and a message digest of the content. */
/**
* @defgroup PKCS7_DIGESTED_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7DigestedData
* {
*  SEC_AsnInt            version;
*  SEC_ALG_IDENTIFIER_S* pstDigestAlg;
*  PKCS7_CONTENT_INFO_S* pstContentInfo;
*  SEC_AsnOcts_S         stDigest;
* }  PKCS7_DIGESTED_S;
* @endcode
*
* @datastruct version It shall be 0 for this version of the standard.
* @datastruct pstDigestAlg digestAlgorithm identifies the message-digest algorithm (and any associated parameters)
* under which the content is digested.
* @datastruct pstContentInfo contentInfo is the content that is digested. It can have any of the PKCS7 defined content types.
* @datastruct stDigest digest is the result of the message-digesting process over the data present in pstContentInfo.
*/
typedef struct stPKCS7DigestedData
{
	SEC_AsnInt version;							/* It shall be 0 for this version of the standard. */
	SEC_ALG_IDENTIFIER_S* pstDigestAlg;			/*digestAlgorithm identifies the message-digest algorithm (and any
												associated parameters) under which the content is digested.  */
	PKCS7_CONTENT_INFO_S* pstContentInfo;	/* contentInfo is the content that is digested. It can have any of
												the PKCS7 defined content types. */
	SEC_AsnOcts_S  stDigest;					/* digest is the result of the message-digesting process over the data
													present in pstContentInfo .*/
}  PKCS7_DIGESTED_S;


/* The encrypted-data content type consists of encrypted content of any defined PKCS7 type.
	 Keys used to encrypt content are assumed to be managed by other means. It is expected that the
	typical application of the encrypted-data content type will be to encrypt content of the
	data content type for local storage*/
/**
* @defgroup PKCS7_ENCRYPTED_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7EncryptedData
* {
*  SEC_AsnInt              version;
*  PKCS7_ENCRYPTED_INFO_S* pstEncryptedContentInfo;
* } PKCS7_ENCRYPTED_S;
* @endcode
*
* @datastruct version It shall be 0 for this version of the standard.
* @datastruct pstEncryptedContentInfo pstEncryptedContentInfo is the encrypted content information. It include information
* like type of Content encrypted , Algorithm used to encrypt and encrypted data.
*/
typedef struct stPKCS7EncryptedData
{
	SEC_AsnInt version;							/* It shall be 0 for this version of the standard. */
	PKCS7_ENCRYPTED_INFO_S* pstEncryptedContentInfo;  /* pstEncryptedContentInfo is the encrypted content information.
														It include information like type of Content encrypted , Algorithm
														used to encrypt and encrypted data*/
} PKCS7_ENCRYPTED_S;




/*	PKCS7 structure is a generalized structure for all PKCS7 data types . This  data type
	allows efficient utilization of local functions .  User friendly interfaces to all PKCS7
	data types.   */

/**
* @defgroup PKCS7_MSG_S
* @ingroup pkcs7Structures
* @par Prototype
* @code
* typedef struct stPKCS7Msg
* {
*  SEC_UINT32     enContentType;
*  union
*  {
*   SEC_AsnOcts_S*          pstData;
*   PKCS7_SIGNED_S*         pstSigned;
*   PKCS7_ENVELOPED_S*      pstEnveloped;
*   PKCS7_SIGN_ENVELOPED_S* pstSignEnv;
*   PKCS7_DIGESTED_S*       pstDigest;
*   PKCS7_ENCRYPTED_S*      pstEncrypted;
*   SEC_VOID*               value;
*  } content;
*   SEC_UCHAR*              pucCEK;
*   SEC_UINT32              uiCEKLen;
*   SEC_UINT32              enCEAlgo;
*   SEC_AsnOcts_S           stEncodedCont;
* } PKCS7_MSG_S;
* @endcode
*
* @datastruct enContentType Type of the PKCS7 data.
* @datastruct pstData Pointer to the simple data (Octet string ).
* @datastruct pstSigned Pointer to the signed data structure.
* @datastruct pstEnveloped Pointer to the Enveloped data structure.
* @datastruct pstSignEnv Pointer to the signed Enveloped data structure.
* @datastruct pstDigest Pointer to the digested data structure.
* @datastruct pstEncrypted Pointer to the Encrypted data structure.
* @datastruct value Void pointer to support other data types.
* @datastruct pucCEK Pointer to hold encryption key temporarily.
* @datastruct uiCEKLen Encryption key length.
* @datastruct enCEAlgo Encryption key related algorithm.
* @datastruct stEncodedCont structure to hold data  temporarily.
*/
typedef struct stPKCS7Msg
{

	SEC_UINT32  enContentType;					/* Type of the PKCS7 data  */
	union
	{
		SEC_AsnOcts_S*  pstData;				/* Pointer to the simple data (Octet string ) */
		PKCS7_SIGNED_S* pstSigned;				/* Pointer to the signed data structure*/
		PKCS7_ENVELOPED_S* pstEnveloped;		/* Pointer to the Enveloped data structure */
		PKCS7_SIGN_ENVELOPED_S* pstSignEnv;	    /* Pointer to the signed Enveloped data structure */
		PKCS7_DIGESTED_S* pstDigest;			/* Pointer to the digested data structure */
		PKCS7_ENCRYPTED_S *pstEncrypted;		/* Pointer to the Encrypted data structure */
		SEC_VOID* value;						/* Void pointer to support other data types */
	} content;
	SEC_UCHAR* pucCEK ;							/* Pointer to hold encryption key temporarily  */
	SEC_UINT32  uiCEKLen ;						/* Encryption key length */
	SEC_UINT32  enCEAlgo ;						/* Encryption key related algorithm */
	SEC_AsnOcts_S stEncodedCont;				/* structure to hold data  temporarily  */
} PKCS7_MSG_S;



/* PKCS7 Function Declaration */

/** @defgroup pkcs7Functions
* @ingroup pkcs7
* This section contains the pkcs7 Functions.
*/


/**
* @defgroup PKCS7_createSimple
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S*   PKCS7_createSimple ( const SEC_UCHAR *  pucContent,
* SEC_UINT32 uiContentLen);
* @endcode
*
* @par Purpose
* To prepare a Simple-data message.
*
* @par Description
* Prepares a Simple-data message. Simple data is just an AsnOcts having Char pointer and length.
* Simple data is prepared in the sequence preparation of complex Data types (Any of the  othter five PKCS7 data types).
*
* @param[in] pucContent Simple data char string. [N/A]
* @param[in] uiContentLen Length of the  input message. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Any of the six PKCS7 data. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* One of the input parameter may be invalid. [SEC_NULL|N/A]
* @retval PKCS7_MSG_S* If memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL PKCS7_MSG_S*   PKCS7_createSimple ( const SEC_UCHAR *  pucContent,
				                        SEC_UINT32 uiContentLen);



/**
* @defgroup PKCS7_createSigned
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S* PKCS7_createSigned (SEC_UINT32    uiVersion,
* const PKCS7_MSG_S* pstPKCS7);
* @endcode
*
* @par Purpose
* To prepare a signed-data message.
*
* @par Description
* Prepares a signed-data message. The output of this function is a correctly formatted  Signed-Data message. The data
* content can be any of six pkcs7  data types . When user want to give buffer ( Bit String ) as input, then it is a 2
* step process:\n
* 1. Create Simple data (PKCS7_createSimple())whose input is an octet String   And\n
* 2. Pass created Simple data as input to this function\n
* To complete Creation of Signed data requires, few OPTIONAL Steps\n
* 1. Create Signer Info (PKCS7_createSignerInfo()), Creates Signer info with Cert serial etc.\n
* 2. Add Signer Info (PKCS7_addSignerInfo()) ,Adds signer info to signed data and signs.\n
* 3. Add Certificate (PKCS7_addCert()), adds list of certs may useful to sign verifier.\n
* 4. Add CRLs (PKCS7_addCrl()), adds list of CRL's may useful to verifier.
*
* @param[in] uiVersion It shall be 1 for this version of the standard (PKCS7_SIGNED_VERSION). [N/A]
* @param[in] pstPKCS7  Any of the six PKCS7 data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Created Signed data. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* One of the input parameter may be invalid. [SEC_NULL|N/A]
* @retval PKCS7_MSG_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
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

PSELINKDLL PKCS7_MSG_S* PKCS7_createSigned (SEC_UINT32    uiVersion,
									const PKCS7_MSG_S* pstPKCS7);



/**
* @defgroup PKCS7_createEnveloped
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S *  PKCS7_createEnveloped(SEC_UINT32    uiVersion,
* SEC_UINT32    enCEAlgo ,
* const PKCS7_MSG_S *  pstPKCS7 );
* @endcode
*
* @par Purpose
* To prepare an Enveloped-data message.
*
* @par Description
* Prepares an Enveloped-data message. The output of this function is a correctly formatted  Enveloped-Data message.
* The data content can be any of six pkcs7 data types. When user want to give buffer ( Bit String ) as input, then
* it is a 2 step process\n
* 1. Create Simple data(PKCS7_createSimple()) whose input is Octet String   And\n
* 2. Pass the created Simple data as input to this function\n
* To complete Creation of Enveloped data requires, one MANDATORY Step\n
* 1. Add Recipient Info (PKCS7_addRecipient()), which creates Recipient info and adds the created Recipient info to
* the Enveloped data.
*
* @param[in] uiVersion It shall be 0 for this version of the standard (PKCS7_ENVELOPED_VERSION). [N/A]
* @param[in] enCEAlgo Content Encryption Algorithm (symmetric algorithm) under which the content is encrypted. [N/A]
* @param[in] pstPKCS7 Any of the six PKCS7 data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Created Enveloped data. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* One of the input parameter may be invalid. [SEC_NULL|N/A]
* @retval PKCS7_MSG_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* There should be atleast one recipient.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL PKCS7_MSG_S *  PKCS7_createEnveloped(SEC_UINT32    uiVersion,
									 SEC_UINT32    enCEAlgo ,
									 const PKCS7_MSG_S *  pstPKCS7 );




/**
* @defgroup PKCS7_createSignedAndEnveloped
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S*   PKCS7_createSignedAndEnveloped ( SEC_UINT32 uiVersion,
* SEC_UINT32 uiCEAlgo, const PKCS7_MSG_S* pstPKCS7 );
* @endcode
*
* @par Purpose
* To prepare a Signed-Enveloped-data message.
*
* @par Description
* Prepares a Signed-Enveloped-data message. The output of this function is a correctly formatted Signed-Enveloped-Data
* message The data content can be any of six pkcs7 data types. When user want to give buffer ( Bit String ) as input,
* then it is 2 step process\n
* 1. Create Simple data (PKCS7_createSimple())whose input is Bit String   And\n
* 2. Pass the created Simple data as input to this function\n
* To complete Creation of Signed Enveloped data requires 3 MANDATORY Steps\n
* 1. Create Signer Info (PKCS7_createSignerInfo()), Creates Signer info with Cert serial etc.\n
* 2. Add Signer Info (PKCS7_addSignerInfo()) ,Adds signer info to signed data and signs.\n
* 3. Add Recipient Info (PKCS7_addRecipient()), which creates Recipient info and adds the created Recipient info to the
* Signed Enveloped data.
*
* @param[in] uiVersion It shall be 1 for this version of the standard (PKCS7_SIGNENVELOPED_VERSION). [N/A]
* @param[in] uiCEAlgo Content Encryption Algorithm (symmetric algorithm) under which the content is encrypted. [N/A]
* @param[in] pstPKCS7 Any of the six PKCS7 data. [N/A]
* @param[out]  N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Created Signed Enveloped data. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* One of the input parameter may be invalid. [SEC_NULL|N/A]
* @retval PKCS7_MSG_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
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

PSELINKDLL PKCS7_MSG_S*   PKCS7_createSignedAndEnveloped ( SEC_UINT32    uiVersion,
													SEC_UINT32    uiCEAlgo,
													const PKCS7_MSG_S*   pstPKCS7 );






/**
* @defgroup PKCS7_createDigested
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S* PKCS7_createDigested (SEC_UINT32 uiVersion,
* SEC_UINT32 uiDigestAlgo, const PKCS7_MSG_S* pstPKCS7);
* @endcode
*
* @par Purpose
* To prepare a Digested-data message.
*
* @par Description
* Prepares a Digested-data message. The output of this function is a correctly formatted Digested-Data message.
* The data content can be any of six pkcs7 data types. When user want to give buffer ( Bit String ) as input,
* then it is 2 step process\n
* 1. Create Simple data (PKCS7_createSimple())whose input is Octet String   And\n
* 2. Pass the created Simple data as input to this function.
*
* @param[in] uiVersion It shall be 0 for this version of the standard (PKCS7_DIGESTED_VERSION). [N/A]
* @param[in] uiDigestAlgo Content Digestion Algorithm identifieer. [N/A]
* @param[in] pstPKCS7 Any of the six PKCS7 data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Created Digested data structure. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* One of the input parameters may be invalid. [SEC_NULL|N/A]
* @retval PKCS7_MSG_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
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

PSELINKDLL PKCS7_MSG_S*  PKCS7_createDigested (  SEC_UINT32 uiVersion,
									  SEC_UINT32  uiDigestAlgo,
									  const PKCS7_MSG_S* pstPKCS7);




/**
* @defgroup PKCS7_createEncrypted
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S*  PKCS7_createEncrypted( SEC_UINT32 uiVersion,
* SEC_UCHAR* pucCEKey,
* SEC_UINT32 uiCEKeyLength,
* SEC_UINT32 enCEAlgo ,
* const PKCS7_MSG_S* pstPKCS7 );
* @endcode
*
* @par Purpose
* To prepare a Encrypted-data message.
*
* @par Description
* Prepares a Encrypted-data message. The output of this function is a correctly formatted  Encrypted-Data message.
* The data content can be any of six pkcs7 data types. When user wants to give buffer ( Bit String ) as input,
* then it is 2 step process\n
* 1. Create Simple data (PKCS7_createSimple())whose input is Octet String   And\n
* 2. Pass the created Simple data as input to this function.
*
* @param[in] uiVersion It shall be 0 for this version of the standard (PKCS7_ENCRYPTED_VERSION). [N/A]
* @param[in] pucCEKey Key used to encrypt content. It should be created using the algorithm in uiCEAlgo field. [N/A]
* @param[in] uiCEKeyLength Content Encryption key length. [N/A]
* @param[in] enCEAlgo Content Encryption Algorithm (symmetric algorithm) under which the content is encrypted. [N/A]
* @param[in] pstPKCS7 Any of the six PKCS7 data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Created encrypted data structure. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* One of the input parameters may be invalid. [SEC_NULL|N/A]
* @retval PKCS7_MSG_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* Input key should be generated with the same algorithm as the "uiCEAlgo".
*
* @par Related Topics
* N/A
*
* 
*/
PSELINKDLL PKCS7_MSG_S*  PKCS7_createEncrypted( SEC_UINT32 uiVersion,
									SEC_UCHAR* pucCEKey,
									SEC_UINT32 uiCEKeyLength,
									SEC_UINT32 enCEAlgo ,
									const PKCS7_MSG_S* pstPKCS7 );







/**
* @defgroup PKCS7_createSignerInfo
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_SIGNER_INFO_S* PKCS7_createSignerInfo(SEC_UINT32    uiVersion,
* SEC_UINT32    uiDigestAlgo,
* SEC_UINT32    uiDigEncryAlgo,
* SEC_NAME_S* pstIssuer ,
* SEC_BIGINT_S*  pstSN);
* @endcode
*
* @par Purpose
* To create signer info.
*
* @par Description
* This function creates signer info which consists of information about the Signer like serial number, issuer name of the
* Signer certificate. Issuer and serialnumber inputs should be of the signer certificate.
* There are 2 Optional steps to complete Signer info creation ( These two steps only for the signer info of the Signed
* data)\n
* 1. Add Authenticated attributes (PKCS7_addAuthAttrToSignerInfo()). Authenticated by the signer, Sign is calculated over
* these attributes if exists. If there are Authenticated attributes there should be 2 mandatory attributes
* A.Content type B. Message digest\n
* 2. Add UnAuthenticated attributes(PKCS7_addUnauthAttrToSignerInfo()). Not Authenticated by the signer.
*
* @param[in] uiVersion It shall be 1 for this version of the standard (PKCS7_SIGNERINFO_VERSION). [N/A]
* @param[in] uiDigestAlgo Algorithm used to calculate digest over the encoded message. [N/A]
* @param[in] uiDigEncryAlgo Algorithm (asymmetric algorithm) used to encrypt the  message digest. [N/A]
* @param[in] pstIssuer Issuer Name of the signer's certificate. [N/A]
* @param[in] pstSN Serial Number of the signer's certificate. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_SIGNER_INFO_S* Created Signer Info. [PKCS7_SIGNER_INFO_S*|N/A]
* @retval PKCS7_SIGNER_INFO_S* One of the input parameters may be invalid. [SEC_NULL|N/A]
* @retval PKCS7_SIGNER_INFO_S* Memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created signer info, to free this memory
* application has to call the PKCS7_freeSignerInfo.
*
* @par Note
* RSA Standard does not support ALGID_SHA224 for signing and hence the same should not be
* passed as parameter uiDigestAlgo while using ALGID_RSA as the encryption algorithm.
*
*
* @par Related Topics
* N/A
*/
PSELINKDLL PKCS7_SIGNER_INFO_S* PKCS7_createSignerInfo(SEC_UINT32    uiVersion,
										 SEC_UINT32    uiDigestAlgo,
										 SEC_UINT32    uiDigEncryAlgo,
										 SEC_NAME_S* pstIssuer ,
										 SEC_BIGINT_S*  pstSN);




/**
* @defgroup PKCS7_addSignerInfo
* @ingroup pkcs7Functions
* @par Prototype
* @code
*  SEC_UINT32   PKCS7_addSignerInfo ( PKCS7_SIGNER_INFO_S*  pstSignerInfo,
* SEC_PKEY_S*  pstPrivInfo,
* PKCS7_MSG_S*  pstPKCS7);
* @endcode
*
* @par Purpose
* To add signer's info to the PKCS7 signed data OR Signed Enveloped data structure.
*
* @par Description
* This function adds signer's info to the PKCS7 signed data OR Signed Enveloped data structure. Calculates signature over
* the content Or authenticated attributes and saves signature value in signers info. Adds the digest algorithm to Signed
* data digest algorithm list.
*
* @param[in] pstSignerInfo Signer info structure. [N/A]
* @param[in] pstPrivKey	Private Key info structure. [N/A]
* @param[in] pstPKCS7 PKCS7 Message structure. Signed data OR Signed Enveloped data will be accessed. [N/A]
* @param[out] pstPKCS7 PKCS7 structure after successful addition of the given Signer info structure. [N/A]
*
* @retval SEC_UINT32 Successful addition of signer Info to signed data OR Signed Enveloped data structure. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 One of the input parameter is invalid like input parameters may be NULL, inappropriate PKCS7 data
* type (Other than Signed and signed enveloped data ) OR Structure explicitly modified by user / corrupted. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Dup Signer info failed due to corrupted Signer info OR memory allocation failure. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Private key type is invalid, algorithm type mismatch with signer info uiDigEncryAlgo type. [SEC_CRYPT_ERR_INVALID_PKEY_TYPE|N/A]
* @retval SEC_UINT32 Memory allocation failed. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Authenticated attributes are present, but One OR both of the mandatory attributes are missing. [SEC_ERR_ATTR_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Authenticated attributes encode failed, may be because of hash table not being initialised
* (InitAnyPKCS_7() ). [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Buffer copy failed after encoding. Buffer may be corrupted. [SEC_ERR_BUF_COPY_FAILED|N/A]
* @retval SEC_UINT32 Conversion from PKCS7 data type to content info failed. [SEC_ERR_CONVERT_FAILED|N/A]
* @retval SEC_UINT32 Digest algorithm specified in signer info is invalid, Corrupted  after signer info creation. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 One of the mandatory field is NULL like PKCS7_ENCRYPTED_INFO_S field may be NULL in signed enveloped
* data. [SEC_ERR_NULL_PTR|N/A]
* @retval SEC_UINT32 If context values are not correct. [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If algorithm undefined for operation. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If operation is undefined for key. [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Invalid Padding Mode [SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 Invalid Keylength for alg [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid IVlength for alg mode. [SEC_ERR_INVALID_IV_LEN|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
* pstPKCS7 acts as both an input and output parameter, it will be accessed and updated also.
*
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_UINT32   PKCS7_addSignerInfo ( PKCS7_SIGNER_INFO_S*  pstSignerInfo,
									SEC_PKEY_S*  pstPrivInfo,
									PKCS7_MSG_S*  pstPKCS7);





/**
* @defgroup PKCS7_addCert
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_addCert (X509_CERT_S*  pstX509,
* PKCS7_MSG_S * pstPKCS7);
* @endcode
*
* @par Purpose
* To add certificate either to the signed data or to the Signed Enveloped data certificate list.
*
* @par Description
* This function adds certificate either to the signed data or to the Signed Enveloped data certificate list so that the
* intended receiver of the message can process the message even if he does not have sender certificates in repository.
*
* @param[in] pstX509 Certificate to be added. It's either Certificate of the signer OR certificate in the path of trusted
* CA ( certification authority). [N/A]
* @param[in] pstPKCS7 PKCS7 Message structure. It can be either Signed data or Signed Enveloped data. [N/A]
* @param[out] pstPKCS7 The update PKCS7 Message structure after addition of the given Certificate. [N/A]
*
* @retval SEC_UINT32 Certificate is added successfully. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 One of the Inputs is NULL OR inappropriate type to add Certificate. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory Allocation failed. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Create new List (Certificate List)failed. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 Dup certificate failed. [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
* pstPKCS7 acts as both an input and output parameter, it will be accessed and updated also.
*
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32  PKCS7_addCert (X509_CERT_S*  pstX509,
									PKCS7_MSG_S * pstPKCS7);




/**
* @defgroup PKCS7_addCrl
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_addCrl (X509_CRL_S*  pstCrl,
* PKCS7_MSG_S* pstPKCS7 );
* @endcode
*
* @par Purpose
* To add CRLs to signed data.
*
* @par Description
* This function adds CRLs to signed data so the intended receiver of the message can know about the revoked certificates
* even if he does not have the latest CRL's.
*
* @param[in] pstCrl CRL to be added. It is intended that the set contains information sufficient to determine whether
* or not the certificates in the certificates field are revoked OR not but such correspondence is not necessary.
*
* @param[in] pstPKCS7 PKCS7 Message structure. It can be either Signed data or Signed Enveloped data. [N/A]
* @param[out] pstPKCS7 The updated PKCS7 Message structuer after the addition of the given CRL. [N/A]
*
* @retval SEC_UINT32 CRL's are added successfully. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 One of the Inputs is NULL OR inappropriate type to add CRL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 One of the copy operation failed. It may be because of memory allocation failure OR corrupted
* input structure in which mandatory field is NULL. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Invalid data type. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
* pstPKCS7 acts as both an input and output parameter, it will be accessed and updated also.
*
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32  PKCS7_addCrl (X509_CRL_S*  pstCrl,
					   PKCS7_MSG_S* pstPKCS7 );




/**
* @defgroup PKCS7_addAuthAttrToSignerInfo
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_addAuthAttrToSignerInfo(SEC_UINT32  enAttrType,
* SEC_VOID* pAttributeValue ,
* PKCS7_SIGNER_INFO_S*  pstSignerInfo );
* @endcode
*
* @par Purpose
* To set attributes to Authenticated Attributes of the SignerInfo.
*
* @par Description
* This function sets Attributes to Authenticated Attributes of the SignerInfo. These attributes are any of the PKCS7
* Attributes present in PKCS9. If there are Authenticated attributes there should be 2 mandatory attributes:\n
* 1.Content type\n	2. Message digest
*
* @param[in] enAttrType Type of the attribute . Any of the following types:\n
*						1. Content type  CID_PKCS9_AT_CONTENTTYPE\n
*						2. message digest CID_PKCS9_AT_MESSAGEDIGEST\n
*						3. Signing time   CID_PKCS9_AT_SIGNINGTIME\n
*						4. Random nonce  CID_PKCS9_AT_RANDOMNONCE\n
*						5. Sequence number  CID_PKCS9_AT_SEQUENCENUMBER [N/A]
* @param[in] pAttributeValue Value of the attribute. Value structure depends on Attribute type(enAttrType) of input.
*						1. For CID_PKCS9_AT_CONTENTTYPE OID is structure input (SEC_AsnOid_S )\n
*						2. For CID_PKCS9_AT_MESSAGEDIGEST Octs structure is input (SEC_AsnOcts_S)\n
*						3. For CID_PKCS9_AT_SIGNINGTIME time structure is input (SEC_TIME_S )\n
*						4. For CID_PKCS9_AT_RANDOMNONCE Octs structure is input (SEC_AsnOcts_S )\n
*						5. For CID_PKCS9_AT_SEQUENCENUMBER integer is structure input (SEC_UINT32 ) [N/A]
* @param[in] pstSignerInfo PKCS7 Signer info structure to which the attribute is added. [N/A]
* @param[out] pstSignerInfo PKCS7 Signer info structure after addition of the given attribute. [N/A]
*
* @retval SEC_UINT32 Attribute is added successfully. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 One of the inputs may be NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 List creation failed. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 Memory allocation failed. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Dup attribute failed may be because of memory allocation failure OR
* one of mandatory fields being NULL. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Invalid Attribute type. [SEC_ERR_INVALID_CID|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
* pstSignerInfo acts as both an input and output parameter, it will be accessed and updated also.
*

* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32  PKCS7_addAuthAttrToSignerInfo(SEC_UINT32  enAttrType,
								 SEC_VOID* pAttributeValue ,
								 PKCS7_SIGNER_INFO_S*  pstSignerInfo );






/**
* @defgroup PKCS7_addUnauthAttrToSignerInfo
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_addUnauthAttrToSignerInfo(SEC_UINT32 enAttrType,
* SEC_VOID * pAttributeValue ,
* PKCS7_SIGNER_INFO_S*  pstSignerInfo );
* @endcode
*
* @par Purpose
* To set Authenticated Attributes to UnAuthenticated Attributes of the SignerInfo.
*
* @par Description
* This function sets Authenticated Attributes to UnAuthenticated Attributes of the SignerInfo. These attributes
* are any of the PKCS7 Attributes present in PKCS9.
*
* @param[in] enAttrType  Type of the attribute . Any of the following types:\n
*						1. Content type  CID_PKCS9_AT_CONTENTTYPE\n
*						2. message digest CID_PKCS9_AT_MESSAGEDIGEST\n
*						3. Signing time   CID_PKCS9_AT_SIGNINGTIME\n
*						4. Random nonce  CID_PKCS9_AT_RANDOMNONCE\n
*						5. Sequence number  CID_PKCS9_AT_SEQUENCENUMBER\n
*						6. Counter signature CID_PKCS9_AT_COUNTERSIGNATURE [N/A]
* @param[in] pAttributeValue Value of the attribute. Value structure depends on Attribute type(enAttrType) of input.\n
*						1. For CID_PKCS9_AT_CONTENTTYPE OID is structure input (SEC_AsnOid_S )\n
*						2. For CID_PKCS9_AT_MESSAGEDIGEST Octs structure is input (SEC_AsnOcts_S )\n
*						3. For CID_PKCS9_AT_SIGNINGTIME time structure is input (SEC_TIME_S )\n
*						4. For CID_PKCS9_AT_RANDOMNONCE Octs structure is input (SEC_AsnOcts_S )\n
*						5. For CID_PKCS9_AT_SEQUENCENUMBER integer is structure input (SEC_UINT32 )\n
*						6. For CID_PKCS9_AT_COUNTERSIGNATURE Signer info is structure input (PKCS7_SIGNER_INFO_S ) [N/A]
* @param[in] pstSignerInfo PKCS7 Signer info structure to which attribute is added. [N/A]
* @param[out] pstSignerInfo PKCS7 Signer info structure after the addition of the given attribute. [N/A]
*
* @retval SEC_UINT32 Attribute is added successfully. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 One of the inputs may be NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 List creation failed. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 Memory allocation failed. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Dup attribute faild may be because memory allocation
* failed OR one of mandatory fields is NULL. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Invalid Attribute type. [SEC_ERR_INVALID_CID|N/A]
* @retval SEC_UINT32 One of the mandatory fields input structure is NULL. [SEC_ERR_NULL_PTR|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
* pstSignerInfo acts as both an input and output parameter, it will be accessed and updated also.
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32  PKCS7_addUnauthAttrToSignerInfo(SEC_UINT32 enAttrType,
								   SEC_VOID * pAttributeValue ,
								   PKCS7_SIGNER_INFO_S*  pstSignerInfo );




/**
* @defgroup PKCS7_addRecipient
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_addRecipient (SEC_UINT32    uiVersion,
* X509_CERT_S *  pstX509,
* PKCS7_MSG_S *  pstPKCS7 );
* @endcode
*
* @par Purpose
* To create and add the recipient info either to the Enveloped data OR Signed Enveloped data.
*
* @par Description
* This function Creates and adds the recipient info either to the Enveloped data OR Signed Enveloped data.
* This is 2 step process:\n
* 1. It creates Recipient info, Recipient info holds the information like Content Encryption key (key under
* which content is encrypted ) which is encrypted with the Recipient public key and Recipient Certificate Issuer
* and serial number.\n
* 2. Adds the created Recipient info either to the Enveloped data OR to Signed Envelope data.
*
* @param[in] uiVersion It shall be 0 for this version of the standard (PKCS7_RECIPINFO_VERSION). [N/A]
* @param[in] pstX509 Certificate of the recipient. [N/A]
* @param[in] pstPKCS7 PKCS7 Message structure. It can be either Enveloped data OR Signed Enveloped data. [N/A]
* @param[out] pstPKCS7 The updated PKCS7 Message structure after the given Recipient info is added. [N/A]
*
* @retval SEC_UINT32 Recipient added successfully. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Some of the Inputs are NULL OR (invalid)incorrect. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Recipient info creation failed may be due to invalid certificate, memory allocation failure OR Key
* encryption failure. [SEC_PKCS7_ERR_CREATE_RECIP_FAILED|N/A]
* @retval SEC_UINT32 Memory Allocation failed. [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* Recipient info is mandatory for both Enveloped and Signed Enveloped data.
* pstPKCS7 acts as both an input and output parameter, it will be accessed and updated also.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32  PKCS7_addRecipient (SEC_UINT32    uiVersion,
							 X509_CERT_S *  pstX509,
							 PKCS7_MSG_S *  pstPKCS7 );






/**
* @defgroup PKCS7_getContentType
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_INT32 PKCS7_getContentType (PKCS7_MSG_S* pstPKCS7);
* @endcode
*
* @par Purpose
* To get type of the PKCS7 data	from PKCS7_MSG_S structure.
*
* @par Description
* This function gets type of the PKCS7 data	from PKCS7_MSG_S structure.
*
* @param[in] pstPKCS7  Any of the PKCS7 data type. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 Type of the PKCS7 data is returned. [Type of PKCS7 data|N/A]
* @retval SEC_INT32	If content type is invalid means other than defined PKCS7 type. [-1|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32  PKCS7_getContentType (PKCS7_MSG_S*  pstPKCS7);




/**
* @defgroup PKCS7_getRecipInfoList
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_List_S*    PKCS7_getRecipInfoList( PKCS7_MSG_S* pstPKCS7 );
* @endcode
*
* @par Purpose
* To get Recipient Infolist either from the Enveloped data OR Signed Enveloped data.
*
* @par Description
* Gets Recipient Infolist either from the Enveloped data OR Signed Enveloped data.
*
* @param[in] pstPKCS7 PKCS7 message of either Enveloped data OR Enveloped data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* List of Recipient Infos if exists, list can be with '0' Recipient infos. [SEC_List_S*|N/A]
* @retval SEC_List_S* Some of the Inputs are NULL OR invalid. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_List_S*    PKCS7_getRecipInfoList( PKCS7_MSG_S* pstPKCS7 );




/**
* @defgroup PKCS7_getSignerInfoList
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_List_S* PKCS7_getSignerInfoList( PKCS7_MSG_S* pstPKCS7 );
* @endcode
*
* @par Purpose
* To get Signer Infolist either from the Signed data OR Signed Enveloped data.
*
* @par Description
* Gets Signer Infolist either from the Signed data OR Signed Enveloped data.
*
* @param[in] pstPKCS7 Signed data OR Enveloped data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* List of Signer Infos if exists, list can be with '0' signer infos. [SEC_List_S*|N/A]
* @retval SEC_List_S* Some of the Inputs are NULL OR invalid. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_List_S* PKCS7_getSignerInfoList( PKCS7_MSG_S* pstPKCS7 );






/**
* @defgroup PKCS7_extractCertList
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_List_S*  PKCS7_extractCertList( PKCS7_MSG_S* pstPKCS7 );
* @endcode
*
* @par Purpose
* To extract Certificate list from the Signed data OR Signed Enveloped data.
*
* @par Description
* Extracts Certificate list from the Signed data OR Signed Enveloped data. This function creates cert list from the
* Extended certificate list of the Signed data OR Signed Enveloped data.
*
* @param[in] pstPKCS7 PKCS7 message of Sigened data OR Signed Enveloped data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* List of cerificates. [SEC_List_S*|N/A]
* @retval SEC_List_S* Some of the Inputs are NULL, memory allocation failed, OR List operation faild. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the list returned to application, to free this memory
* application has to call the SEC_LIST_FREE i.e. SEC_LIST_FREE(list,X509_freeCert);
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_List_S*  PKCS7_extractCertList( PKCS7_MSG_S* pstPKCS7 );





/**
* @defgroup PKCS7_getCrlList
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_List_S*  PKCS7_getCrlList ( PKCS7_MSG_S* pstPKCS7 );
* @endcode
*
* @par Purpose
* To get CRL list from the Signed data OR Signed Enveloped data.
*
* @par Description
* Gets CRL list from the Signed data OR Signed Enveloped data.
*
* @param[in] pstPKCS7 PKCS7 message of Sigened data OR Signed Enveloped data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* List of CRL's. [SEC_List_S*|N/A]
* @retval SEC_List_S* Some of the Inputs are NULL or memory allocation failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_List_S*  PKCS7_getCrlList ( PKCS7_MSG_S* pstPKCS7 );




/**
* @defgroup PKCS7_getVersion
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_getVersion ( PKCS7_MSG_S* pPKCS7 );
* @endcode
*
* @par Purpose
* To get version from the Any of the PKCS7 Data type.
*
* @par Description
* Gets version from the Any of the PKCS7 Data type.
*
* @param[in] pPKCS7 Any of the PKCS7 message types except simple data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Version of the PKCS7 message is returned. [Version of PKCS7 message|N/A]
* @retval SEC_UINT32 Some of the Inputs are NULL OR invalid. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32  PKCS7_getVersion ( PKCS7_MSG_S* pPKCS7 );




/**
* @defgroup PKCS7_getUnAuthAttrList
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_List_S* PKCS7_getUnAuthAttrList( PKCS7_SIGNER_INFO_S* pstSignerInfo);
* @endcode
*
* @par Purpose
* To get UnAuthenticated attribute list from the Signer Info.
*
* @par Description
* Gets UnAuthenticated attribute list from the Signer Info.
*
* @param[in] pstSignerInfo Signer info data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* List of Attributes if it exists. [SEC_List_S*|N/A]
* @retval SEC_List_S* Either signer info is null OR Attributes are NULL. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_List_S* PKCS7_getUnAuthAttrList( PKCS7_SIGNER_INFO_S* pstSignerInfo);




/**
* @defgroup PKCS7_getAuthAttrList
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_List_S* PKCS7_getAuthAttrList ( PKCS7_SIGNER_INFO_S* pstSignerInfo );
* @endcode
*
* @par Purpose
* To get Authenticated attribute list from the Signer Info.
*
* @par Description
* Gets Authenticated attrib list from the Signer Info.
*
* @param[in] pstSignerInfo Signer info data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* List of Attributes if it exists. [SEC_List_S*|N/A]
* @retval SEC_List_S* Either signer info is NULl OR Attributes are NULL. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_List_S* PKCS7_getAuthAttrList ( PKCS7_SIGNER_INFO_S* pstSignerInfo );





/**
* @defgroup PKCS7_getSignerVersion
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_getSignerVersion ( PKCS7_SIGNER_INFO_S* pstSignerInfo );
* @endcode
*
* @par Purpose
* To get version from the Signer Info.
*
* @par Description
* Gets version from the Signer Info.
*
* @param[in] pstSignerInfo Signer Info Structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Version of the Signer info is returned on success. [Version of the Signer info|N/A]
* @retval SEC_UINT32 Some of the Inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32  PKCS7_getSignerVersion ( PKCS7_SIGNER_INFO_S* pstSignerInfo );



/**
* @defgroup PKCS7_getIssuerAndSNFromSigner
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_ISSUER_AND_SERIAL_S* PKCS7_getIssuerAndSNFromSigner (PKCS7_SIGNER_INFO_S* pstSignerInfo);
* @endcode
*
* @par Purpose
* To extract Issuer And Serialnumber structure from the Signer Info.
*
* @par Description
* This function extracts Issuer And Serialnumber structure from the Signer Info.
*
* @param[in] pstSignerInfo Signer Info data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ISSUER_AND_SERIAL_S* Issuer And Serialnumber structure. [SEC_ISSUER_AND_SERIAL_S*|N/A]
* @retval SEC_ISSUER_AND_SERIAL_S* Signer info may be NULL. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_ISSUER_AND_SERIAL_S* PKCS7_getIssuerAndSNFromSigner (PKCS7_SIGNER_INFO_S* pstSignerInfo);



/**
* @defgroup PKCS7_getRecipVersion
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_getRecipVersion (PKCS7_RECIPIENT_S* pstRecipInfo );
* @endcode
*
* @par Purpose
* To get version from the Recipient Info.
*
* @par Description
* Gets version from the Recipient Info.
*
* @param[in] pstRecipInfo Recipient Info Structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Version of the recipient is returned on success. [Version of the recipient|N/A]
* @retval SEC_UINT32 Some of the Inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32  PKCS7_getRecipVersion (PKCS7_RECIPIENT_S* pstRecipInfo );



/**
* @defgroup PKCS7_getIssuerAndSNFromRecip
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_ISSUER_AND_SERIAL_S* PKCS7_getIssuerAndSNFromRecip (PKCS7_RECIPIENT_S* pstRecipientInfo );
* @endcode
*
* @par Purpose
* To extract Issuer And Serialnumber structure from the  Recipient Info structure.
*
* @par Description
* This function extracts  Issuer And Serialnumber structure from the  Recipient Info structure.
*
* @param[in] pstRecipientInfo Recipient Info data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ISSUER_AND_SERIAL_S* Issuer And Serialnumber structure. [SEC_ISSUER_AND_SERIAL_S*|N/A]
* @retval SEC_ISSUER_AND_SERIAL_S* Recipient info OR Issuer and serial number of Recipient info may be NULL. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ISSUER_AND_SERIAL_S* PKCS7_getIssuerAndSNFromRecip (PKCS7_RECIPIENT_S* pstRecipientInfo );



/**
* @defgroup PKCS7_verifySignature
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_verifySignature (	PKCS7_MSG_S*  pstPKCS7,
* SEC_List_S*  pCertList,
* SEC_NAME_S* pstSignerIssuer ,
* SEC_BIGINT_S*  pstSignerSN,
* SEC_NAME_S* pstRecipIssuer ,
* SEC_BIGINT_S*  pstRecipSN,
* SEC_PKEY_S* pstPrivKeyInfo );
* @endcode
*
* @par Purpose
* To verify the signatures of the Signed data OR Signed Enveloped data.
*
* @par Description
* This function verifies the  signatures of the Signed data OR Signed Enveloped data. Depending on the issuer and
* serial number searches for the signer info and verifies signature. If Signer info not found it returns
* SEC_ERR_INVALID_ARG.
*
* @param[in] pstPKCS7 PKCS7 data structure. It can be either Signed data OR Signed Enveloped data. [N/A]
* @param[in] pCertList List of the Certificates. It's expected that the list includes signers certificate. [N/A]
* @param[in] pstSignerIssuer Issuer name of the signer certificate. [N/A]
* @param[in] pstSignerSN Serial number of the signer certificate. [N/A]
* @param[in] pstRecipIssuer Issuer name of the recipient certificate. It can be NULL for the signed data. [N/A]
* @param[in] pstRecipSN Serial number of the recipient certificate. It can be NULL for the signed data. [N/A]
* @param[in] pstPrivKeyInfo Private key information of the Receiver. It can be NULL for the signed data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Signature verified successfully. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Sign Verification Failed. [SEC_ERR_SIGN_VERIFY_FAILED|N/A]
* @retval SEC_UINT32 Some of the mandatory Inputs are NULL OR invalid. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 One of the mandatory attribute is missing. [SEC_ERR_ATTR_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Memory allocation failed. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Invalid Signed OR signed enveloped data. [SEC_ERR_CONVERT_FAILED|N/A]
* @retval SEC_UINT32 Encode failed may be because of Invalid Signed OR signed enveloped data. [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 One of the mandatory fields is NULL in signed OR signed enveloped data.
* It may be because the structure is corrupted. [SEC_ERR_NULL_PTR|N/A]
* @retval SEC_UINT32 Digest algorithm OID present in Signer info is invalid. [SEC_ERR_INVALID_CID|N/A]
* @retval SEC_UINT32 If padding mode requested is undefined. [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If padding in data is not of the requested type. [SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 If key structure is malformed. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 If cipher is larger than key. [SEC_CRYPT_ERR_LARGE_DATA_SIZE|N/A]
* @retval SEC_UINT32 If key type is not public or pair. [SEC_CRYPT_ERR_INVALID_PKEY_TYPE|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key. [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Invalid AlgorithmId. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Keylength for alg. [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid IVlength for alg mode. [SEC_ERR_INVALID_IV_LEN|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32  PKCS7_verifySignature (	PKCS7_MSG_S*  pstPKCS7,
									SEC_List_S*  pCertList,
									SEC_NAME_S* pstSignerIssuer ,
									SEC_BIGINT_S*  pstSignerSN,
									SEC_NAME_S* pstRecipIssuer ,
									SEC_BIGINT_S*  pstRecipSN,
									SEC_PKEY_S* pstPrivKeyInfo );




/**
* @defgroup PKCS7_verifyAllSignature
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_verifyAllSignature ( PKCS7_MSG_S*  pstPKCS7,
* SEC_List_S*  pCertList,
* SEC_NAME_S* pstRecipIssuer ,
* SEC_BIGINT_S*  pstRecipSN,
* SEC_PKEY_S* pstPrivKeyInfo
* );
* @endcode
*
* @par Purpose
* To verify all the signatures of the Signed data and Signed Enveloped data.
*
* @par Description
* This function going to verify all the signatures of the Signed data and Signed Enveloped data. If there are no
* signerinfos to verify then it returns SUCCESS.
*
* @param[in] pstPKCS7 PKCS7 data structure. It can be either Signed data OR Signed Enveloped data. [N/A]
* @param[in] pCertList List of the Certificates. It is expected that the list includes signers certificate. [N/A]
* @param[in] pstRecipIssuer Issuer name of the recipient certificate. It can be NULL for the signed data. [N/A]
* @param[in] pstRecipSN Serial number of the recipient certificate. It can be NULL for the signed data. [N/A]
* @param[in] pstPrivKeyInfo Private key information of the Receiver. It can be NULL for the signed data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Signature verified successfully. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Sign Verification Failed. [SEC_ERR_SIGN_VERIFY_FAILED|N/A]
* @retval SEC_UINT32 Some of the mandatory Inputs are NULL OR invalid. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 One of the mandatory attributes is missing. [SEC_ERR_ATTR_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Memory allocation failed. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Invalid Signed OR signed enveloped data. [SEC_ERR_CONVERT_FAILED|N/A]
* @retval SEC_UINT32 Encode failed may be because of Invalid Signed OR signed enveloped data. [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 One of the mandatory field is NULL in signed OR signed enveloped data.
* It may be because of structure corrupted. [SEC_ERR_NULL_PTR|N/A]
* @retval SEC_UINT32 Digest algorithm OID prest in Signer info is invalid. [SEC_ERR_INVALID_CID|N/A]
* @retval SEC_UINT32 If padding mode requested is undefined. [SEC_CRYPT_ERR_UNDEFINED_PADDING|N/A]
* @retval SEC_UINT32 If padding in data is not the requested type. [SEC_CRYPT_ERR_INVALID_PADDING|N/A]
* @retval SEC_UINT32 If key struct is malformed. [SEC_CRYPT_ERR_INVALID_PKEY|N/A]
* @retval SEC_UINT32 If cipher is larger than key. [SEC_CRYPT_ERR_LARGE_DATA_SIZE|N/A]
* @retval SEC_UINT32 If key type is not public or pair. [SEC_CRYPT_ERR_INVALID_PKEY_TYPE|N/A]
* @retval SEC_UINT32 If operation cannot be performed on key. [SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION|N/A]
* @retval SEC_UINT32 Invalid AlgorithmId. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Invalid Keylength for alg [SEC_ERR_INVALID_KEY_LEN|N/A]
* @retval SEC_UINT32 Invalid IVlength for alg mode. [SEC_ERR_INVALID_IV_LEN|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32  PKCS7_verifyAllSignature ( PKCS7_MSG_S*  pstPKCS7,
									   SEC_List_S*  pCertList,
									   SEC_NAME_S* pstRecipIssuer ,
									   SEC_BIGINT_S*  pstRecipSN,
									   SEC_PKEY_S* pstPrivKeyInfo
									     );



/**
* @defgroup PKCS7_verifyDigest
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32  PKCS7_verifyDigest ( PKCS7_MSG_S*  pstPKCS7 ) ;
* @endcode
*
* @par Purpose
* To verify the digest calculated over the content field of the content Info structure of Digested data.
*
* @par Description
* Verifies the digest calculated over the content field of the content Info structure of Digested data.
*
* @param[in] pstPKCS7 PKCS7 digested data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Digest verified successfully. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Digest verification faild. [SEC_ERR_DIGEST_VERIFY_FAILED|N/A]
* @retval SEC_UINT32 Some of the mandatory Inputs are NULL OR invalid. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Digest algorithm present in digested data is invalid. [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Digested data is corrupted. [SEC_ERR_NULL_PTR|N/A]
* @retval SEC_UINT32 PKCS7 message may be invalid OR corrupted. [SEC_ERR_CONVERT_FAILED|N/A]
* @retval SEC_UINT32 Encode of digested data failed. [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Memory allocation failed. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If context values are not correct. [SEC_CRYPT_ERR_INVALID_CTX|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32  PKCS7_verifyDigest ( PKCS7_MSG_S*  pstPKCS7 ) ;



/**
* @defgroup PKCS7_encodePKCS7Msg
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UCHAR*  PKCS7_encodePKCS7Msg( PKCS7_MSG_S* pstPKCS7, SEC_UINT32* puiEncLen);
* @endcode
*
* @par Purpose
* To encode PKCS7_MSG_S Data Structure to (DER format).
*
* @par Description
* Encodes PKCS7_MSG_S Data Structure to (DER format).
*
* @param[in] pstPKCS7 Any of the six PKCS7 defined type. [N/A]
* @param[out] puiEncLen Length of the Encoded bit string. Address of the integer should be sent as input. [N/A]
*
* @retval SEC_UCHAR* Encoded bit string ( DER format). [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Some of the Inputs are NULL, memory allocation may have failed OR Encode failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the character pointer returned to application, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UCHAR*  PKCS7_encodePKCS7Msg( PKCS7_MSG_S* pstPKCS7, SEC_UINT32* puiEncLen);





/**
* @defgroup PKCS7_decodePKCS7Msg
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S*  PKCS7_decodePKCS7Msg(SEC_UCHAR* pucPKCS7Msg ,
* SEC_UINT32  uiMsgLen,
* SEC_UINT32* puiDecLen );
* @endcode
*
* @par Purpose
* To decode encoded(DER format) PKCS7 message into PKCS7_MSG_S structure.
*
* @par Description
* Decodes encoded (DER format)PKCS7 message into PKCS7_MSG_S structure.
*
* @param[in] pucPKCS7Msg Encoded (DER format) PKCS7 message string. [N/A]
* @param[in] uiMsgLen Encode string Length. [N/A]
* @param[out] puiDecLen Total number of bytes decoded. [N/A]
*
* @retval PKCS7_MSG_S* Deocded PKCS7 message structure(PKCS7_MSG_S). [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* Some of the Inputs are NULL, memory allocation may have failed, OR Decode failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL PKCS7_MSG_S*  PKCS7_decodePKCS7Msg(SEC_UCHAR* pucPKCS7Msg ,
											SEC_UINT32  uiMsgLen,
											SEC_UINT32* puiDecLen );





/**
* @defgroup PKCS7_freePKCS7Msg
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID  PKCS7_freePKCS7Msg ( PKCS7_MSG_S*  pstPKCS7 );
* @endcode
*
* @par Purpose
* To free any of the 6 PKCS7 data types.
*
* @par Description
* This function is used to free any of the 6 PKCS7 data types.
*
* @param[in] pstPKCS7 Any of the six PKCS7 data type. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID  PKCS7_freePKCS7Msg ( PKCS7_MSG_S*  pstPKCS7 );




/**
* @defgroup PKCS7_freeSignerInfo
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID  PKCS7_freeSignerInfo (PKCS7_SIGNER_INFO_S* pstSignerInfo );
* @endcode
*
* @par Purpose
* To free Signer info data structure.
*
* @par Description
* This function is used to free Signer info data structure.
*
* @param[in] pstSignerInfo Signer info data structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID  PKCS7_freeSignerInfo (PKCS7_SIGNER_INFO_S* pstSignerInfo );





/**
* @defgroup PKCS7_freeRecipInfo
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID  PKCS7_freeRecipInfo (PKCS7_RECIPIENT_S* pstRecipientInfo);
* @endcode
*
* @par Purpose
* To free Recipient info data structure.
*
* @par Description
* This function is used to free Recipient info data structure.
*
* @param[in] pstRecipientInfo Recipient Info structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID  PKCS7_freeRecipInfo (PKCS7_RECIPIENT_S* pstRecipientInfo);




/**
* @defgroup PKCS7_createPBEncrypted
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S *  PKCS7_createPBEncrypted(	SEC_UINT32 uiVersion,
* SEC_UCHAR* ulPassWrd,
* SEC_UINT32 pucPassLen,
* SEC_UINT32 ulPBEAlgo ,
* const PKCS7_MSG_S*  pstPKCS7 );
* @endcode
*
* @par Purpose
* To prepare a Password Based Encrypted-data message.
*
* @par Description
* Prepares a Password Based Encrypted-data message.Password is used to generate Encryption key. Data is encrypted with
* generated symmetric key and algorithm specified, the data content can be any of six pkcs7 data types. When user wants
* to give buffer ( Bit String ) as input,then it is a 2 step process:\n
* 1. Create Simple data whose input is Bit String   And\n
* 2. Pass the created Simple data as input to this function
*
* @param[in] uiVersion It shall be 0 for this version of the standard. [N/A]
* @param[in] ulPassWrd Password used to generate encryption key. [N/A]
* @param[in] pucPassLen	Password length. [N/A]
* @param[in] ulPBEAlgo Algorithm used to encrypt the content. It should be a password based algorithm defined in PKCS#5. [N/A]
* @param[in] pstPKCS7 Any of the six defined PKCS#7 data types. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S * Created encrypted data structure. [PKCS7_MSG_S *|N/A]
* @retval PKCS7_MSG_S * Invalid password OR algorithm, Memory Allocation might failed,
* Password based crypto operation might failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL PKCS7_MSG_S *  PKCS7_createPBEncrypted(	SEC_UINT32 uiVersion,
											SEC_UCHAR* ulPassWrd,
											 SEC_UINT32 pucPassLen,
											SEC_UINT32 ulPBEAlgo ,
											const PKCS7_MSG_S*  pstPKCS7 );




/**
* @defgroup PKCS7_decryptPBEncrypted
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S*  PKCS7_decryptPBEncrypted(	PKCS7_MSG_S*  pstPKCS7,
* SEC_UCHAR*  pucPassWrd,
* SEC_UINT32   ulPassLen );
* @endcode
*
* @par Purpose
* To extract PKCS7Msg from the Encrypted data.
*
* @par Description
* It extracts PKCS7Msg from the Encrypted data It decrypts the Encrypted content part of the Encrypted content Info and
* Decodes decrypted content and creates PKCS7Msg.
*
* @param[in] pstPKCS7 PKCS7 Local structure. [N/A]
* @param[in] pucPassWrd Password used decrypt encryption key. [N/A]
* @param[in] ulPassLen Password length. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Decrypted data in form of PKCS7 nessage (PKCS7_MSG_S). [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* Invalid password OR algorithm, Memory Allocation might have failed,
* Password based crypto operation might have failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL PKCS7_MSG_S*  PKCS7_decryptPBEncrypted(	PKCS7_MSG_S*  pstPKCS7,
														 SEC_UCHAR*  pucPassWrd,
														 SEC_UINT32   ulPassLen );



/**
* @defgroup PKCS7_decryptEncrypted
* @ingroup pkcs7Functions
* @par Prototype
* @code
*  PKCS7_MSG_S*  PKCS7_decryptEncrypted ( PKCS7_MSG_S*  pstPKCS7,
* SEC_UCHAR*  pucCEKey,
* SEC_UINT32   uiCEKeyLen);
* @endcode
*
* @par Purpose
* To extract PKCS7Msg from the Encrypted data.
*
* @par Description
* It extracts PKCS7Msg from the Encrypted data. It  is a two step process:\n
* 1. It decrypts the Encrypted content info structure's content.\n
* 2. Decodes the decrypted content into appropriate PKCS7_MSG_S structure.
*
* @param[in] pstPKCS7 PKCS7 local structure. [N/A]
* @param[in] pucCEKey Decryption key. [N/A]
* @param[in] uiCEKeyLen Decryption key length. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Decrypted data. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* Some of the inputs may be NULL, memory allocation failed,
* Decrypt operation failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* Key (input) should match with the encryption key.
*
* @par Related Topics
* N/A
*/

PSELINKDLL  PKCS7_MSG_S*  PKCS7_decryptEncrypted ( PKCS7_MSG_S*  pstPKCS7,
										  SEC_UCHAR*  pucCEKey,
										  SEC_UINT32   uiCEKeyLen);


/**
* @defgroup PKCS7_openEnveloped
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S* PKCS7_openEnveloped (PKCS7_MSG_S*  pstPKCS7,
* SEC_PKEY_S*  pstPrivKeyInfo,
* SEC_NAME_S* pstIssuer ,
* SEC_BIGINT_S*  pstSN );
* @endcode
*
* @par Purpose
* To create PKCS7 Msg From Encrypted content Info structure.
*
* @par Description
* This function creates PKCS7 Msg From Encrypted content Info structure. It is a two step process:\n
* 1. It decrypts the Encrypted data part Encrypted Content info.\n
* 2. Decodes the decrypted content into appropriate PKCS7_MSG_S structure.
*
* @param[in] pstPKCS7 PKCS7 Message of either Enveloped OR Signed enveloped data. [N/A]
* @param[in] pstPrivKeyInfo Private key of the Recipient. [N/A]
* @param[in] pstIssuer Issuer Name of the recipient certificate. [N/A]
* @param[in] pstSN Serial number of the recipient certificate. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Decrypted data decoded into PKCS7 message. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* Some of the inputs may be null, memory allocation failed,
* Decrypt operation failed OR Decode failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* Private key should correspond to the recipient certificate public key.
*
* @par Related Topics
* N/A
*/

PSELINKDLL PKCS7_MSG_S* PKCS7_openEnveloped (PKCS7_MSG_S*  pstPKCS7,
								SEC_PKEY_S*  pstPrivKeyInfo,
								SEC_NAME_S* pstIssuer ,
								SEC_BIGINT_S*  pstSN );



/**
* @defgroup PKCS7_getDataFromSimpleData
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* PKCS7_getDataFromSimpleData(PKCS7_MSG_S* pstPKCS7);
* @endcode
*
* @par Purpose
* To get the pointer to the octs of the simple data if it is a simple data.
*
* @par Description
* This function gets the pointer to the octs of the simple data if it is a simple data.
*
* @param[in] pstPKCS7 Simple data structure pointer. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* Pointer to the octs of simple data. [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S Some of the inpiuts may be null OR invalid. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_AsnOcts_S* PKCS7_getDataFromSimpleData(PKCS7_MSG_S* pstPKCS7);




/**
* @defgroup PKCS7_extractContentFromPKCS7Msg
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S* PKCS7_extractContentFromPKCS7Msg(PKCS7_MSG_S* pstPKCS7);
* @endcode
*
* @par Purpose
* To extract the data into appropriate pkcs7 data type.
*
* @par Description
* This function extracts the data into  appropriate pkcs7 data type.
*
* @param[in] pstPKCS7 Any of the defined PKCS7 types except Simple data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Extracted PKCS7 message. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* Some of the inputs may be NULL OR failed to extract. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL PKCS7_MSG_S* PKCS7_extractContentFromPKCS7Msg(PKCS7_MSG_S* pstPKCS7);



/**
* @defgroup PKCS7_getDigestAlgFromSignerInfo
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS7_getDigestAlgFromSignerInfo(PKCS7_SIGNER_INFO_S* pstSignerInfo);
* @endcode
*
* @par Purpose
* To get digest algorithm from the signer info structure which is extracted either from Signed OR Signed
* enveloped data.
*
* @par Description
* This function gets digest algorithm from the signer info structure which is extracted either from Signed OR Signed
* enveloped data.
*
* @param[in] pstSignerInfo Signer info structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 CID of the digest algorithm identifier is returned on success. [CID of the digest algorithm identifier|N/A]
* @retval SEC_UINT32 Some of the inputs may be NULL OR invalid. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Algorithm identifier is invalid. [SEC_ERR_INVALID_CID|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32 PKCS7_getDigestAlgFromSignerInfo(PKCS7_SIGNER_INFO_S* pstSignerInfo);



/**
* @defgroup PKCS7_getDigestEncAlgFromSignerInfo
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS7_getDigestEncAlgFromSignerInfo(PKCS7_SIGNER_INFO_S* pstSignerInfo);
* @endcode
*
* @par Purpose
* To get digest encryption algorithm from the signer info structure which is extracted either from Signed OR
* Signed enveloped data.
*
* @par Description
* This function gets digest encryption algorithm from the signer info structure which is extracted either from Signed OR
* Signed enveloped data. How to get signer info? Get the Signer info list using PKCS7_getSignerInfoList and then get
* signer info using list functions (sec_list.h).
*
* @param[in] pstSignerInfo Signer info structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 CID of the algorithm identifier is returned on success. [CID of the algorithm identifier|N/A]
* @retval SEC_UINT32 Some of the inputs may be NULL OR invalid. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Algorithm identifier is invalid. [SEC_ERR_INVALID_CID|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32 PKCS7_getDigestEncAlgFromSignerInfo(PKCS7_SIGNER_INFO_S* pstSignerInfo);



/**
* @defgroup PKCS7_getKeyEncAlgFromRecipInfo
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UINT32 PKCS7_getKeyEncAlgFromRecipInfo(PKCS7_RECIPIENT_S* pstRecipInfo);
* @endcode
*
* @par Purpose
* To get KEY encryption algorithm from the Recipient info structure which is extracted either from Enveloped
* OR Signed enveloped data.
*
* @par Description
* This function gets KEY encryption algorithm from the Recipient info structure which is extracted either from Enveloped
* OR Signed enveloped data. How to get Recipient info? Get the Recipient info list using PKCS7_getRecipInfoList and then
* get Recipient info using list functions (sec_list.h).
*
* @param[in] pstRecipInfo Recipient info structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 CID of the algorithm identifier is returned on success. [CID of the algorithm identifier|N/A]
* @retval SEC_UINT32 Some of the inputs may be NULL OR invalid. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Algorithm identifier is invalid. [SEC_ERR_INVALID_CID|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 PKCS7_getKeyEncAlgFromRecipInfo(PKCS7_RECIPIENT_S* pstRecipInfo);



/**
* @defgroup PKCS7_encodeSigned
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UCHAR*  PKCS7_encodeSigned (PKCS7_SIGNED_S* pstSign, SEC_UINT32* puiEncLen);
* @endcode
*
* @par Purpose
* To encode Signed Data Structure into DER format.
*
* @par Description
* Encodes Signed Data Structure into DER format.
*
* @param[in] pstSign Signed data structure (PKCS7_SIGNED_S). [N/A]
* @param[out] puiEncLen Length of the Encoded bit string. [N/A]
*
* @retval SEC_UCHAR* Encoded bit string in DER format. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Input are invalid OR NULL,Encode failed OR memory allocation failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the character pointer returned to application, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UCHAR*  PKCS7_encodeSigned (PKCS7_SIGNED_S* pstSign, SEC_UINT32* puiEncLen);



/**
* @defgroup PKCS7_encodeEnveloped
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UCHAR*  PKCS7_encodeEnveloped ( PKCS7_ENVELOPED_S* pstEnveloped , SEC_UINT32* puiEncLen );
* @endcode
*
* @par Purpose
* To encode Enveloped Data Structure in DER format.
*
* @par Description
* Encodes Enveloped Data Structure in DER format.
*
* @param[in] pstEnveloped Enveloped data structure (PKCS7_ENVELOPED_S). [N/A]
* @param[out] puiEncLen Length of the Encoded bit string. [N/A]
*
* @retval SEC_UCHAR* Encoded bit string in DER format. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Input are invalid OR NULL,Encode failed OR memory allocation failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the character pointer returned to application, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR*  PKCS7_encodeEnveloped ( PKCS7_ENVELOPED_S* pstEnveloped , SEC_UINT32* puiEncLen );



/**
* @defgroup PKCS7_encodeSignEnveloped
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UCHAR*  PKCS7_encodeSignEnveloped (PKCS7_SIGN_ENVELOPED_S* pstSignEnv,SEC_UINT32* puiEncLen );
* @endcode
*
* @par Purpose
* To encode Signed Enveloped Data Structure in DER format.
*
* @par Description
* Encodes Signed Enveloped Data Structure in DER format.
*
* @param[in] pstSignEnv Signed Enveloped data structure (PKCS7_SIGN_ENVELOPED_S). [N/A]
* @param[out] puiEncLen Length of the Encoded bit string. [N/A]
*
* @retval SEC_UCHAR* Encoded bit string in DER format. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Input are invalid OR NULL,Encode failed OR memory llocation failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the character pointer returned to application, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UCHAR*  PKCS7_encodeSignEnveloped (PKCS7_SIGN_ENVELOPED_S* pstSignEnv,SEC_UINT32* puiEncLen );


/**
* @defgroup PKCS7_encodeDigested
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UCHAR*  PKCS7_encodeDigested (  PKCS7_DIGESTED_S* pstDigest, SEC_UINT32* puiEncLen);
* @endcode
*
* @par Purpose
* To encode Digested Data Structure in DER format.
*
* @par Description
* Encodes Digested Data Structure in DER format.
*
* @param[in] pstDigest Digested data structure (PKCS7_DIGESTED_S). [N/A]
* @param[out] puiEncLen Length of the Encoded bit string. [N/A]
*
* @retval SEC_UCHAR* Encoded bit string in DER format. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Input are invalid OR NULL,Encode failed OR memory allocation failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the character pointer returned to application, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UCHAR*  PKCS7_encodeDigested (  PKCS7_DIGESTED_S* pstDigest, SEC_UINT32* puiEncLen);


/**
* @defgroup PKCS7_encodeEncrypted
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_UCHAR*  PKCS7_encodeEncrypted ( PKCS7_ENCRYPTED_S* pstEncrypted, SEC_UINT32* puiEncLen );
* @endcode
*
* @par Purpose
* To encode Encrypted Data Structure in DER format.
*
* @par Description
* Encodes Encrypted Data Structure in DER format.
*
* @param[in] pstEncrypted Encrypted data structure (PKCS7_ENCRYPTED_S). [N/A]
* @param[out] puiEncLen Length of the Encoded bit string. [N/A]
*
* @retval SEC_UCHAR* Encoded bit string in DER format. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Input are invalid OR NULL, Encode failed, OR memory allocation failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the character pointer returned to application, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR*  PKCS7_encodeEncrypted ( PKCS7_ENCRYPTED_S* pstEncrypted, SEC_UINT32* puiEncLen );



/**
* @defgroup PKCS7_decodeSigned
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_SIGNED_S* PKCS7_decodeSigned (	SEC_UCHAR* pucPKCS7Msg ,
* SEC_UINT32  uiMsgLen,
* SEC_UINT32* puiDecLen );
* @endcode
*
* @par Purpose
* To decode Encoded Signed data structure.
*
* @par Description
* Decodes Encoded Signed data structure.
*
* @param[in] pucPKCS7Msg Encoded Signed data structure (DER format). [N/A]
* @param[in] uiMsgLen Length of the encoded message. [N/A]
* @param[out] puiDecLen Total no of bytes decoded. [N/A]
*
* @retval PKCS7_SIGNED_S* Decoded Signed data Structure. [PKCS7_SIGNED_S*|N/A]
* @retval PKCS7_SIGNED_S* Inputs may be NULL OR invalid, Decode may have failed,
* OR memory allocation may have failed. [N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 signed data, to free this memory
* application has to call the PKCS7_freeSignedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL PKCS7_SIGNED_S* PKCS7_decodeSigned (	SEC_UCHAR* pucPKCS7Msg ,
											SEC_UINT32  uiMsgLen,
											SEC_UINT32* puiDecLen );


/**
* @defgroup PKCS7_decodeEnveloped
* @ingroup pkcs7Functions
* @par Prototype
* @code
*  PKCS7_ENVELOPED_S* PKCS7_decodeEnveloped (SEC_UCHAR* pucPKCS7Msg ,
* SEC_UINT32  uiMsgLen,
* SEC_UINT32* puiDecLen);
* @endcode
*
* @par Purpose
* To decode encoded Encoded Enveloped data.
*
* @par Description
* Decodes encoded Encoded Enveloped data.
*
* @param[in] pucPKCS7Msg Encoded Enveloped data structure. [N/A]
* @param[in] uiMsgLen Encoded message Length. [N/A]
* @param[out] puiDecLen Total no of bytes decoded. [N/A]
*
* @retval PKCS7_ENVELOPED_S* Decoded Enveloped data Structure. [PKCS7_ENVELOPED_S*|N/A]
* @retval PKCS7_ENVELOPED_S* Inputs may be NULL OR invalid, Decode may have failed,
* OR memory allocation may have failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 envelope data, to free this memory
* application has to call the PKCS7_freeEnvelopedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  PKCS7_ENVELOPED_S* PKCS7_decodeEnveloped (SEC_UCHAR* pucPKCS7Msg ,
											  SEC_UINT32  uiMsgLen,
											  SEC_UINT32* puiDecLen);



/**
* @defgroup PKCS7_decodeSignEnveloped
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_SIGN_ENVELOPED_S* PKCS7_decodeSignEnveloped (SEC_UCHAR* pucSigEnvMsg ,
* SEC_UINT32  uiMsgLen,
* SEC_UINT32* puiDecLen);
* @endcode
*
* @par Purpose
* To decode Encoded Signed Enveloped data.
*
* @par Description
* Decodes Encoded Signed Enveloped data.
*
* @param[in] pucSigEnvMsg Encoded Signed Enveloped data Structure. [N/A]
* @param[in] uiMsgLen Encoded message Length. [N/A]
* @param[out] puiDecLen Total number of bytes decoded. [N/A]
*
* @retval PKCS7_SIGN_ENVELOPED_S* Decoded Signed Enveloped data Structure. [PKCS7_SIGN_ENVELOPED_S*|N/A]
* @retval PKCS7_SIGN_ENVELOPED_S* Inputs may be NULL OR invalid, Decode may be failed,
* OR memory allocation may be failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 signed and envelope data, to free
* this memory application has to call the PKCS7_freeSignedAndEnvelopedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL PKCS7_SIGN_ENVELOPED_S* PKCS7_decodeSignEnveloped (SEC_UCHAR* pucSigEnvMsg ,
													SEC_UINT32  uiMsgLen,
													SEC_UINT32* puiDecLen);



/**
* @defgroup PKCS7_decodeDigested
* @ingroup pkcs7Functions
* @par Prototype
* @code
*  PKCS7_DIGESTED_S* PKCS7_decodeDigested ( SEC_UCHAR* pucDigMsg ,
* SEC_UINT32  uiMsgLen,
* SEC_UINT32* puiDecLen);
* @endcode
*
* @par Purpose
* To decode Encoded Digested data.
*
* @par Description
* Decodes Encoded Digested data.
*
* @param[in] pucDigMsg Encoded Digested data structure. [N/A]
* @param[in] uiMsgLen Encoded message Length. [N/A]
* @param[out] puiDecLen Total number of bytes decoded. [N/A]
*
* @retval PKCS7_DIGESTED_S* Decoded Digested data. [PKCS7_DIGESTED_S*|N/A]
* @retval PKCS7_DIGESTED_S* Inputs may be NULL OR invalid, Decode may be failed,
* OR memory allocation may be failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 digested data, to free this memory
* application has to call the PKCS7_freeDigestedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS7_DIGESTED_S* PKCS7_decodeDigested ( SEC_UCHAR* pucDigMsg ,
												SEC_UINT32  uiMsgLen,
												SEC_UINT32* puiDecLen);



/**
* @defgroup PKCS7_decodeEncrypted
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_ENCRYPTED_S* PKCS7_decodeEncrypted (SEC_UCHAR* pucEncMsg ,
* SEC_UINT32  uiMsgLen,
* SEC_UINT32* puiDecLen);
* @endcode
*
* @par Purpose
* To decode encoded Encrypted data structure.
*
* @par Description
* Decodes encoded Encrypted data structure.
*
* @param[in] pucEncMsg Encoded encrypted data. [N/A]
* @param[in] uiMsgLen Encoded message Length. [N/A]
* @param[out] puiDecLen Total number of bytes decoded. [N/A]
*
* @retval PKCS7_ENCRYPTED_S* Decoded Encrypted data. [PKCS7_ENCRYPTED_S*|N/A]
* @retval PKCS7_ENCRYPTED_S* Inputs may be NULL OR invalid, Decode may have failed,
* OR memory allocation may have failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 encrypted data, to free this memory
* application has to call the PKCS7_freeEncryptedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL PKCS7_ENCRYPTED_S* PKCS7_decodeEncrypted (SEC_UCHAR* pucEncMsg ,
												SEC_UINT32  uiMsgLen,
												SEC_UINT32* puiDecLen);



/**
* @defgroup PKCS7_createPKCS7Msg
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S* PKCS7_createPKCS7Msg (SEC_VOID* pstContent, SEC_UINT32 uiContentType );
* @endcode
*
* @par Purpose
* To create PKCS7_MSG_S structure from any of the six PKCS7 types.
*
* @par Description
* This function creates PKCS7_MSG_S structure from any of the six PKCS7 types.
*
* @param[in] pstContent Any of the six PKCS7 types:\n
* 1. Simple data (SEC_AsnOcts_S).\n
* 2. Signed data (PKCS7_SIGNED_S).\n
* 3. Enveloped data (PKCS7_ENVELOPED_S).\n
* 4. Signed Enveloped data (PKCS7_SIGN_ENVELOPED_S).\n
* 5. Digested data (PKCS7_DIGESTED_S).\n
* 6. Encrypted data  (PKCS7_ENCRYPTED_S) [N/A]
* @param[in] uiContentType Type of the PKCS7 data input ( CID_PKCS7_SIMPLEDATA, CID_PKCS7_SIGNEDDATA,
* CID_PKCS7_ENVELOPEDDATA, CID_PKCS7_SIGNED_ENVELOPEDDATA, CID_PKCS7_DIGESTEDDATA, CID_PKCS7_ENCRYPTEDDATA). [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* Created PKCS7 message. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* Inputs may be NULL OR invalid, OR memory allocation may be failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL PKCS7_MSG_S* PKCS7_createPKCS7Msg (SEC_VOID* pstContent, SEC_UINT32 uiContentType );



/**
* @defgroup PKCS7_getContent
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID* PKCS7_getContent(PKCS7_MSG_S* pstPKCS7, SEC_UINT32* puiContentType );
* @endcode
*
* @par Purpose
* To get specific data from the PKCS7 message.
*
* @par Description
* Gets specific data from the PKCS7 message depends on the type the data.
*
* @param[in] pstPKCS7 PKCS7 message. [N/A]
* @param[out] puiContentType Type of the data returned. [N/A]
*
* @retval SEC_VOID* Any of the six PKCS7 data types:\n
* 1. Simple data (SEC_AsnOcts_S).\n
* 2. Signed data (PKCS7_SIGNED_S).\n
* 3. Enveloped data (PKCS7_ENVELOPED_S).\n
* 4. Signed Enveloped data (PKCS7_SIGN_ENVELOPED_S).\n
* 5. Digested data (PKCS7_DIGESTED_S).\n
* 6. Encrypted data  (PKCS7_ENCRYPTED_S) [SEC_VOID*|N/A]
* @retval SEC_VOID* Some of the inputs may be NULL OR invalid. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID* PKCS7_getContent(PKCS7_MSG_S* pstPKCS7, SEC_UINT32* puiContentType );



/**
* @defgroup PKCS7_dupPKCS7Msg
* @ingroup pkcs7Functions
* @par Prototype
* @code
* PKCS7_MSG_S* PKCS7_dupPKCS7Msg(PKCS7_MSG_S* pstSrcP7);
* @endcode
*
* @par Purpose
* To dup PKCS7_MSG_S structure it can consist of any of the six PKCS7 data types.
*
* @par Description
* This function dups PKCS7_MSG_S structure it can consist of any of the six PKCS7 data types.
*
* @param[in] pstSrcP7 PKCS7 message structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_MSG_S* PKCS7 message structure duplicated. [PKCS7_MSG_S*|N/A]
* @retval PKCS7_MSG_S* Some of the inputs may be NULL, corrupted structure, OR memory allocation failed. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 message, to free this memory
* application has to call the PKCS7_freePKCS7Msg.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL PKCS7_MSG_S* PKCS7_dupPKCS7Msg(PKCS7_MSG_S* pstSrcP7);




/**
* @defgroup PKCS7_freeCertList
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID  PKCS7_freeCertList(SEC_List_S* pstCertList);
* @endcode
*
* @par Purpose
* To free the certificate List ( X509 certificate).
*
* @par Description
* This function frees the certificate List ( X509 certificate). This list is extracted using function
* PKCS7_extractCertList.
*
* @param[in] pstCertList List of certificates. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID  PKCS7_freeCertList(SEC_List_S* pstCertList);




/**
* @defgroup PKCS7_freeSignedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID PKCS7_freeSignedData(PKCS7_SIGNED_S *pstSigned);
* @endcode
*
* @par Purpose
* To free Signed data.
*
* @par Description
* This function is used to free Signed data.
*
* @param[in] pstSigned Signed data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID PKCS7_freeSignedData(PKCS7_SIGNED_S *pstSigned);



/**
* @defgroup PKCS7_freeEnvelopedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID PKCS7_freeEnvelopedData( PKCS7_ENVELOPED_S *pstEnv);
* @endcode
*
* @par Purpose
* To free Enveloped data.
*
* @par Description
* This function is used to free Enveloped data.
*
* @param[in] pstEnv Enveloped data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID PKCS7_freeEnvelopedData( PKCS7_ENVELOPED_S *pstEnv);




/**
* @defgroup PKCS7_freeSignedAndEnvelopedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID PKCS7_freeSignedAndEnvelopedData(PKCS7_SIGN_ENVELOPED_S *pstSigEnv);
* @endcode
*
* @par Purpose
* To free Signed Enveloped data.
*
* @par Description
* This function is used to free Signed Enveloped data.
*
* @param[in] pstSigEnv Signed Enveloped data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID PKCS7_freeSignedAndEnvelopedData(PKCS7_SIGN_ENVELOPED_S *pstSigEnv);




/**
* @defgroup PKCS7_freeDigestedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID PKCS7_freeDigestedData( PKCS7_DIGESTED_S *pstDigst);
* @endcode
*
* @par Purpose
* To free Digested data.
*
* @par Description
* This function is used to free Digested data.
*
* @param[in] pstDigst Digested data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID PKCS7_freeDigestedData( PKCS7_DIGESTED_S *pstDigst);




/**
* @defgroup PKCS7_freeEncryptedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
* SEC_VOID PKCS7_freeEncryptedData(PKCS7_ENCRYPTED_S *pstEncry);
* @endcode
*
* @par Purpose
* To free Encrypted data.
*
* @par Description
* This function is used to free Encrypted data.
*
* @param[in] pstEncry Encrypted data. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID PKCS7_freeEncryptedData(PKCS7_ENCRYPTED_S *pstEncry);




/**
* @defgroup PKCS7_dupSignedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
*  PKCS7_SIGNED_S* PKCS7_dupSignedData(PKCS7_SIGNED_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate signed data.
*
* @par Description
* This function duplicates signed data.
*
* @param[in] pSrc Valid Signed data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_SIGNED_S* Duplicated signed data structure. [PKCS7_SIGNED_S*|N/A]
* @retval PKCS7_SIGNED_S* Failed to duplicate may be because of incomplete structure OR insufficient memory. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 signed data, to free this memory
* application has to call the PKCS7_freeSignedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS7_SIGNED_S* PKCS7_dupSignedData(PKCS7_SIGNED_S* pSrc);



/**
* @defgroup PKCS7_dupEnvelopedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
*  PKCS7_ENVELOPED_S* PKCS7_dupEnvelopedData( PKCS7_ENVELOPED_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate Enveloped data.
*
* @par Description
* This function duplicates Enveloped data.
*
* @param[in] pSrc Valid Enveloped data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_ENVELOPED_S* Duplicated Enveloped data structure. [PKCS7_ENVELOPED_S*|N/A]
* @retval PKCS7_ENVELOPED_S* Failed to duplicate may be because of incomplete structure
* OR insufficient memory. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 envelope data, to free this memory
* application has to call the PKCS7_freeEnvelopedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS7_ENVELOPED_S* PKCS7_dupEnvelopedData( PKCS7_ENVELOPED_S* pSrc);



/**
* @defgroup PKCS7_dupSignedAndEnvelopedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
*  PKCS7_SIGN_ENVELOPED_S* PKCS7_dupSignedAndEnvelopedData(PKCS7_SIGN_ENVELOPED_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate signed Enveloped data.
*
* @par Description
* This function duplicates signed Enveloped data.
*
* @param[in] pSrc Valid Signed Enveloped data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_SIGN_ENVELOPED_S* Duplicated signed Enveloped data structure. [PKCS7_SIGN_ENVELOPED_S*|N/A]
* @retval PKCS7_SIGN_ENVELOPED_S* Failed to duplicate may be because of incomplete structure OR
* insufficient memory. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 signed and envelope data, to free
* this memory application has to call the PKCS7_freeSignedAndEnvelopedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS7_SIGN_ENVELOPED_S* PKCS7_dupSignedAndEnvelopedData(PKCS7_SIGN_ENVELOPED_S* pSrc);



/**
* @defgroup PKCS7_dupDigestedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
*  PKCS7_DIGESTED_S* PKCS7_dupDigestedData( PKCS7_DIGESTED_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate Digested data.
*
* @par Description
* This function duplicates Digested data.
*
* @param[in] pSrc Valid Digested data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_DIGESTED_S* Duplicated Digested data structure. [PKCS7_DIGESTED_S*|N/A]
* @retval PKCS7_DIGESTED_S* Failed to duplicate may be because of incomplete structure
* OR insufficient memory. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 digested data, to free this memory
* application has to call the PKCS7_freeDigestedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  PKCS7_DIGESTED_S* PKCS7_dupDigestedData( PKCS7_DIGESTED_S* pSrc);



/**
* @defgroup PKCS7_dupEncryptedData
* @ingroup pkcs7Functions
* @par Prototype
* @code
*  PKCS7_ENCRYPTED_S* PKCS7_dupEncryptedData(PKCS7_ENCRYPTED_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate Encrypted data.
*
* @par Description
* This function duplicates Encrypted data.
*
* @param[in] pSrc Valid Encrypted data structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS7_ENCRYPTED_S* Duplicated Encrypted data structure. [PKCS7_ENCRYPTED_S*|N/A]
* @retval PKCS7_ENCRYPTED_S* Failed to duplicate may be because of incomplete structure
* OR insufficient memory. [SEC_NULL|N/A]
*
* @par Dependency
* pkcs7.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created PKCS7 encrypted data, to free this memory
* application has to call the PKCS7_freeEncryptedData.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A

*/
PSELINKDLL  PKCS7_ENCRYPTED_S* PKCS7_dupEncryptedData(PKCS7_ENCRYPTED_S* pSrc);

#ifdef __cplusplus
}
#endif

#endif /* _IPSI_PKCS7_H_*/

