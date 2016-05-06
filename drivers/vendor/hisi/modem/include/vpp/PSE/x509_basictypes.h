#include "ipsi_pse_build_conf.h"

#ifndef _IPSI_X509_BASICTYPES_H_
#define _IPSI_X509_BASICTYPES_H_


#include "sec_crypto.h"
#include "asn-types.h"
#include "sec_list.h"
#include "ipsi_types.h"


#ifdef __cplusplus
extern "C" {
#endif

/* SEQUENCE OF RelativeDistinguishedName*/
typedef SEC_List_S RDNSequence; 

/* List of certificate extensions*/	
typedef SEC_List_S Extensions; 
/* List of revoked certificates in the CRL*/
typedef SEC_List_S X509_REVOKED_LIST; 

/*Function to encode version content*/
#define DEncVersionContent DEncAsnIntContent
/*Function to decode version content*/
#define DDecVersionContent DDecAsnIntContent
/*Function to Print the version */
#define PrintVersion PrintAsnInt
/*Function to Free the version*/
#define FreeVersion FreeAsnInt 

/**
* @defgroup x509_basictypes
This section contains the x509_basictypes Structures
*/

/**
* @defgroup x509_basictypesStructures
* @ingroup x509_basictypes
This section contains the x509_basictypes Structures
*/

/* The structure is used to in user identification information and the 
	Attribute types of Issuer and Subject*/
/**
* @defgroup SEC_ATTR_TYPE_AND_VALUE_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stAttributeTypeAndValue 
* {
*	SEC_AsnOid_S type;
*	SEC_AsnAnyDefinedBy_S value;
*	 
* } SEC_ATTR_TYPE_AND_VALUE_S;
* @endcode
*
* @datastruct type Object Identifier of the Attribute.
* @datastruct value This field contains the actual identification information.
*/
typedef struct stAttributeTypeAndValue 
{
	/* Object Identifier of the Attribute*/
	SEC_AsnOid_S type; 
	/* This field contains the actual identification information*/
	SEC_AsnAnyDefinedBy_S value; 
} SEC_ATTR_TYPE_AND_VALUE_S;



/* This structure is used in all certificates that identifies the Certificate 
    Issuer and the Subject of the certificate. The name is a list of RDNSequence*/
/**
* @defgroup SEC_NAME_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stName 
* {
*   enum NameChoiceId
*    {
*       NAME_RDNSEQUENCE
*    } choiceId;
*   union NameChoiceUnion
*    {
*       RDNSequence* rdnSequence; 
*     } a;
* } SEC_NAME_S;
* @endcode
*
* @datastruct choiceId Enumerator used to indicate choice of RDNSequence.
* @datastruct NAME_RDNSEQUENCE Choice to indicate RDNSequence.
* @datastruct a Union that contains the RDNSequence List.
* @datastruct rdnSequence List that contains the information of Subject or the Issuer of the Certificate.
*/
typedef struct stName 
{
	/* Choice to be used to indicate RDNSequence*/
    enum NameChoiceId
    {
        /* Choice to indicate RDNSequence*/ 
		NAME_RDNSEQUENCE
    } choiceId;

	/* Union that contains the RDNSequence List*/
    union NameChoiceUnion
    {
    	/* List that contains the information of Subject or the Issuer of the
			Certificate*/
		RDNSequence* rdnSequence; 
    } a;
} SEC_NAME_S;




/*The algorithm identifier is used to identify a cryptographic
	algorithm. The OBJECT IDENTIFIER component identifies the algorithm
	(such as DSA with SHA-1). The contents of the optional parameters
	field will vary according to the algorithm identified.*/
/**
* @defgroup SEC_ALG_IDENTIFIER_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stAlgorithmIdentifier  
* {
*     SEC_AsnOid_S algorithm;				
*     SEC_AsnAnyDefinedBy_S parameters;		
* } SEC_ALG_IDENTIFIER_S;
* @endcode
*
* @datastruct algorithm Algorithm OID.
* @datastruct parameters Parameters for the Algorithm used if any.
*/

typedef struct stAlgorithmIdentifier  
{
	SEC_AsnOid_S algorithm;	  /* Algorithm OID*/			
	SEC_AsnAnyDefinedBy_S parameters;	/* Parameters for the Algorithm used if any*/	
} SEC_ALG_IDENTIFIER_S;


/* This structure is used in the creation of Either of UTC Time or generalized time
Since it is internally a  Union either of the formats will be used
This structure as such will not be handled directly by the user
This structure is used in a variety of other structures like Validity ,thisUpdate etc*/
/**
* @defgroup SEC_TIME_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stTime
* {
*   enum TimeChoiceId
*    {
*        TIME_UTCTIME,
*        TIME_GENERALIZEDTIME
*    } choiceId;
*   union TimeChoiceUnion
*    {
*        SEC_UTCTime_S* utcTime;					
*        SEC_GeneralizedTime_S* generalizedTime;	
*    } a;
* } SEC_TIME_S;
* @endcode
* 
* @datastruct choiceId Formats in which the time will be represented.
* @datastruct a Union that can hold either the UTC Time or Generalized Time.
* @datastruct TIME_UTCTIME UTC time format.
* @datastruct TIME_GENERALIZEDTIME Genaralized time format.
* @datastruct utcTime UTC time.
* @datastruct generalizedTime Generalized time.
*/
typedef struct stTime /* CHOICE */
{
    /* Formats in which the time will be represented */
	enum TimeChoiceId
    {
        TIME_UTCTIME,         /* UTC time format */
        TIME_GENERALIZEDTIME  /* Genaralized time format */
    } choiceId;
	/* Union that can hold either the UTC Time or Generalized Time */
    union TimeChoiceUnion
    {
	    SEC_UTCTime_S* utcTime;		/* UTC time */			
	    SEC_GeneralizedTime_S* generalizedTime;	/* Genaralized time */
    } a;
} SEC_TIME_S; 


/*SEC_EXTN_S*/
/*The below structure will be used in the creation of extension*/
/*Different extension have different type critcality*/
/*Criticality needs to be always input as boolean value*/
/*Extension id field is a object identifier that uniquely identifies the extension*/
/*Extension value is encoded DER value of a given input field*/
/**
* @defgroup SEC_EXTN_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stExtension 
* {
*	SEC_AsnOid_S extnId;
*	SEC_AsnBool* critical;
*	SEC_AsnOcts_S extnValue;
* } SEC_EXTN_S;
* @endcode
*
* @datastruct extnId OID of the Extension.
* @datastruct critical Criticality of the extension.
* @datastruct extnValue Encoded value of the extension structure.
*/

typedef struct stExtension 
{
	SEC_AsnOid_S extnId;	/*OID of the Extension*/
	SEC_AsnBool* critical;  /*Criticality of the extension*/
	SEC_AsnOcts_S extnValue;  /*Encoded value of the extension structure*/
} SEC_EXTN_S;


/*This structure wraps the total details of a revoked certificate*/
/*Certificates revoked by the CA are uniquely identified by the certificate serial number.*/
/**
* @defgroup X509_REVOKED_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stX509Revoked 
* {
*	SEC_BIGINT_S userCertificate;
*	SEC_TIME_S*  revocationDate;	
*	Extensions*  crlEntryExtensions;
* } X509_REVOKED_S;
* @endcode
*
* @datastruct userCertificate The userCertificate, revocationDate are mandatory fields that needs to be
* present always.
* @datastruct revocationDate The time for revocationDate expresses when a certificate has been revoked.
* @datastruct crlEntryExtensions The entry extension are stated for a single revoked certificate.
* The entry extensions that can be present are Reason Code,Hold Instruction Code,
* Certificate Issuer,Invalidity Date.
*/
typedef struct stX509Revoked 
{
	SEC_BIGINT_S userCertificate;	/*The userCertificate, revocationDate are mandatory fields that needs to be 
		                                   present always*/	
	SEC_TIME_S* revocationDate;	    /*The time for revocationDate expresses when a certificate has been revoked*/			
			
	Extensions* crlEntryExtensions;	/*The entry extension are stated for a single revoked certificate.
									*The entry extensions that can be present are Reason Code,Hold Instruction Code,
									Certificate Issuer,Invalidity Date*/
} X509_REVOKED_S;




/* The structue is used to specify the period within which the certificate
	is valid. This structure has to be set in the Certificate Structure*/
/**
* @defgroup SEC_VALIDITY_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stValidity
* {
*	SEC_TIME_S* notBefore;
*	SEC_TIME_S* notAfter;
* } SEC_VALIDITY_S;
* @endcode
*
* @datastruct notBefore Notbefore time specifies the date and time after which the certificate is valid. 
* @datastruct notAfter NotAfter time specifies the date and time after which the certificate is invalid.
*/
typedef struct stValidity 
{
	SEC_TIME_S* notBefore; /* Notbefore time specifies the date and time after which the certificate 
	                            is valid*/
	SEC_TIME_S* notAfter;  /* NotAfter time specifies the date and time after which the certificate 
	                           is invalid*/
} SEC_VALIDITY_S;



/* The structure contains the algorithm that is used to generate the public key
    which has to be set in the certificate.  The algorithms can be either RSA, DSA,
	ECDSA, or Diffie-Hellman etc. The structure also contains the encoded public key*/
/**
* @defgroup SEC_PUBKEY_INFO_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stSubjectPublicKeyInfo 
* {
*	SEC_ALG_IDENTIFIER_S* algorithm;
*	SEC_AsnBits_S         subjectPublicKey;
* } SEC_PUBKEY_INFO_S;
* @endcode
*
* @datastruct algorithm Algorithm that is used to generate the public key which has to be set in the certificate.
* This structure also contains a field which holds the parameters associated with the algorithm, which may be optional.
* @datastruct subjectPublicKey Encoded public key.
*/
typedef struct stSubjectPublicKeyInfo 
{
	SEC_ALG_IDENTIFIER_S* algorithm;  /* Algorithm that is used to generate the public key which has to be set in 
	                                       the certificate. This structure also contains a field which holds the 
		                                   parameters associated with the algorithm, which may be optional*/

	SEC_AsnBits_S subjectPublicKey;  /* Encoded public key*/

} SEC_PUBKEY_INFO_S;



/*The sequence TBSCertificate contains information associated with the
subject of the certificate and the CA who issued it. Every
TBSCertificate contains the names of the subject and issuer, a public
key associated with the subject, a validity period, a version number,
and a serial number; some MAY contain optional unique identifier
fields. The remainder of this section describes the syntax and
semantics of these fields. A TBSCertificate usually includes
extensions.*/
/**
* @defgroup X509_CERTINFO_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stCertInfo					
* {
*	SEC_AsnInt* version;
*	SEC_BIGINT_S serialNumber;
*	SEC_ALG_IDENTIFIER_S* signature
*	SEC_NAME_S* issuer;	
*	SEC_VALIDITY_S* validity;
*	SEC_NAME_S* subject;
*	SEC_PUBKEY_INFO_S* subjectPubKey;
*	SEC_AsnBits_S issuerUID;
*	SEC_AsnBits_S subjectUID;
*	Extensions* extensions;
* } X509_CERTINFO_S;
* @endcode
*
* @datastruct version This field describes the version of the encoded certificate. When extensions are used,
* as expected in this profile, version MUST be 3 (value is 2).
* @datastruct serialNumber The serial number MUST be a positive integer assigned by the CA to 
* sign the certificate.
* @datastruct signature This field contains the algorithm identifier for the algorithm used
* by the CA to sign the certificate.
* @datastruct issuer The issuer field identifies the entity who has signed and issued the certificate. 
* @datastruct validity The certificate validity period is the time interval during which the CA warrants that
* it will maintain information about the status of the certificate.
* @datastruct subject The subject field identifies the entity associated with the public
* key stored in the subject public key field.
* @datastruct subjectPubKey This field is used to carry the public key and identify the algorithm
* with which the key is used (e.g., RSA, DSA, or Diffie-Hellman).
* @datastruct issuerUID The subject and issuer unique identifiers are present in the certificate
* to handle the possibility of reuse of subject and/or issuer names over time.
* @datastruct subjectUID The subject and issuer unique identifiers are present in the certificate
* to handle the possibility of reuse of subject and/or issuer names over time.
* @datastruct extensions This field MUST only appear if the version is 3.
*/
typedef struct stCertInfo					
{
	SEC_AsnInt* version;  /*This field describes the version of the encoded certificate. When
	                         extensions are used, as expected in this profile, version MUST be 3
	                          (value is 2).*/
	
	SEC_BIGINT_S serialNumber; /*The serial number MUST be a positive integer assigned by the CA to
	                               each certificate.*/
	
	SEC_ALG_IDENTIFIER_S* signature; /*This field contains the algorithm identifier for the algorithm used
	                                     by the CA to sign the certificate.*/
	
	SEC_NAME_S* issuer;  /*The issuer field identifies the entity who has signed and issued the
	                          certificate.*/
		
	SEC_VALIDITY_S* validity;  /*The certificate validity period is the time interval during which the
	                               CA warrants that it will maintain information about the status of the
	                               certificate.*/
	
	SEC_NAME_S* subject;  /*The subject field identifies the entity associated with the public
	                          key stored in the subject public key field.*/
	
	SEC_PUBKEY_INFO_S* subjectPubKey;  /*This field is used to carry the public key and identify the algorithm
	                                        with which the key is used (e.g., RSA, DSA, or Diffie-Hellman).*/
	
	  /*The subject and issuer unique identifiers are present in the certificate
	    to handle the possibility of reuse of subject and/or issuer names
	                              over time.*/
	SEC_AsnBits_S issuerUID;
	SEC_AsnBits_S subjectUID;

	Extensions* extensions;	 /*This field MUST only appear if the version is 3*/				
} X509_CERTINFO_S;

/**This is a sequence containing the name of the issuer, issue date,
issue date of the next list, the optional list of revoked
certificates, and optional CRL extensions. When there are no revoked
certificates, the revoked certificates list is absent. When one or
more certificates are revoked, each entry on the revoked certificate
list is defined by a sequence of user certificate serial number,
revocation date, and optional CRL entry extensions.*/
/**
* @defgroup X509_CRLINFO_S
* @ingroup x509_basictypesStructures
* @par Protoype
* @code
* typedef struct stCRLInfo					
* {
*	SEC_AsnInt* pVersion;
*	SEC_ALG_IDENTIFIER_S* pstSignatureAlgo;
*	SEC_NAME_S* issuer;
*	SEC_TIME_S* thisUpdate;
*	SEC_TIME_S* nextUpdate;	
*	X509_REVOKED_LIST* revokedCertificates;
*	Extensions* crlExtensions;
* } X509_CRLINFO_S;
* @endcode
*
* @datastruct pVersion if present, MUST be v2.
* @datastruct pstSignatureAlgo The signatureAlgorithm field contains the algorithm identifier for the algorithm
* used by the CRL issuer to sign the CertificateList.
* @datastruct issuer The issuer field identifies the entity who has signed and issued the	CRL.
* @datastruct thisUpdate This field indicates the issue date of this CRL.
* @datastruct nextUpdate This field indicates the date by which the next CRL will be issued.It is optional.
* @datastruct revokedCertificates List of revoked certificates nodes.It is optional.
* @datastruct crlExtensions The X.509 v2 CRL format also allows communities to define private extensions to carry
* information unique to those communities.It is optional.
*/
typedef struct stCRLInfo					
{
	SEC_AsnInt* pVersion;	/*if present, MUST be v2*/

	SEC_ALG_IDENTIFIER_S* pstSignatureAlgo;  /*The signatureAlgorithm field contains the algorithm identifier for
	                                            the algorithm used by the CRL issuer to sign the CertificateList.*/

	SEC_NAME_S* issuer;  /*The issuer field identifies the entity who has signed and issued the	CRL.*/

	SEC_TIME_S* thisUpdate;  /*This field indicates the issue date of this CRL.*/

	SEC_TIME_S* nextUpdate;   /*This field indicates the date by which the next CRL will be issued.It is optional*/	
	
	X509_REVOKED_LIST* revokedCertificates;   /*List of revoked certificates nodes.It is optional */

	Extensions* crlExtensions;    /*The X.509 v2 CRL format also allows communities to define private extensions	
	                                 to carry information unique to those communities.It is optional*/
										
} X509_CRLINFO_S;

/*This is a sequence containing the names of the subject and issuer, a public key
associated with the subject, a validity period, and other associated
information.*/
/**
* @defgroup X509_CERT_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stCertificate 				
* {
*	X509_CERTINFO_S* toBeSigned;
*	SEC_ALG_IDENTIFIER_S* algorithm;
*	SEC_AsnBits_S signature;
*	SEC_INT iReferences;
* } X509_CERT_S;
* @endcode
*
* @datastruct toBeSigned The structure that contains the certificate user information.
* @datastruct algorithm The signatureAlgorithm field contains the identifier for the cryptographic algorithm
* used by the CA to sign this certificate.
* @datastruct signature This field contains the algorithm identifier for the algorithm used by the CA
* to sign the certificate.
* @datastruct iReferences Count that tells how many objects are using this certificate.
*/
typedef struct stCertificate 				
{
	X509_CERTINFO_S* toBeSigned;   /* The structure that contains the certificate user information*/
	
	SEC_ALG_IDENTIFIER_S* algorithm;  /*The signatureAlgorithm field contains the identifier for the
	                                    cryptographic algorithm used by the CA to sign this certificate.*/
	
	SEC_AsnBits_S signature;   /*This field contains the algorithm identifier for the algorithm used
	                             by the CA to sign the certificate.*/
	
	SEC_INT iReferences;   /*Count that tells how many objects are using this certificate*/
	
} X509_CERT_S;



/*This is a sequence containing three required fields of a CRL the third field is signature that 
will be populated once the CRL has been signed successfully*/
/*!The second field is the algorithm field that indicates the signing algorithm 
used for signing the CRL*/
/**
* @defgroup X509_CRL_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stX509Crl	  
* {
*	X509_CRLINFO_S* pstTbsCertList;
*	SEC_ALG_IDENTIFIER_S* algorithm;
*	SEC_AsnBits_S signature; 
*	SEC_INT iReferences;
*     void * pstCrlExField;
* }X509_CRL_S;
* @endcode
*
* @datastruct pstTbsCertList The structure that contains the CRL information.
* @datastruct algorithm The signatureAlgorithm field contains the algorithm identifier for the algorithm
* used by the CRL issuer to sign the CertificateList.
* @datastruct signature The signatureValue field contains a digital signature computed upon the ASN.1
* DER encoded tbsCertList.
* @datastruct iReferences Count that tells how many objects are referecing the CRL.
* @datastruct pstCrlExField Pointer to Cached CRL extensions.
*/
typedef struct stX509Crl	  
{
	X509_CRLINFO_S* pstTbsCertList;  /* The structure that contains the CRL information*/
	
	SEC_ALG_IDENTIFIER_S* algorithm; /*The signatureAlgorithm field contains the algorithm identifier for
	                                    the algorithm used by the CRL issuer to sign the CertificateList.*/
	 
	SEC_AsnBits_S signature;   /*The signatureValue field contains a digital signature computed upon
	                             the ASN.1 DER encoded tbsCertList.*/

	SEC_INT iReferences;  /* Count that tells how many objects are referecing the CRL*/


	SEC_VOID * pstCrlExField; /*Pointer to Cached CRL extension*/

}X509_CRL_S;




/* This structure is used as a part of Certificate Extension that holds values 
	of the same type*/
/**
* @defgroup SEC_ATTR_S
* @ingroup x509_basictypesStructures
* @par Prototype
* @code
* typedef struct stAttribute  
* {
*	SEC_AsnOid_S type;
*	SEC_List_S *values;
* } SEC_ATTR_S;
* @endcode
*
* @datastruct type The type of the Attribute that has to be set.
* @datastruct values This field contains a list of values of the same type.
*/
typedef struct stAttribute  
{
	SEC_AsnOid_S type;  /* The type of the Attribute that has to be set*/
				
	SEC_List_S *values;  /* This field contains a list of values of the same type*/
	 
} SEC_ATTR_S;




#ifdef __cplusplus
}
#endif

#endif /* _IPSI_X509_BASICTYPES_H_ */

