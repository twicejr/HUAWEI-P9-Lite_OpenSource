
#include "ipsi_pse_build_conf.h"

#ifndef _IPSI_X509V3_EXTN_H_
#define _IPSI_X509V3_EXTN_H_

#include "ipsi_types.h"
#include "sec_crypto.h"
#include "asn-types.h"
#include "sec_list.h"
#include "x509_basictypes.h"
#include "sec_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/*List of subtrees*/
typedef SEC_List_S GeneralSubtrees;

/*List of general name structures*/
typedef SEC_List_S GeneralNames;

/*List of RDN Sequences*/
typedef SEC_List_S RelativeDistinguishedName;

/*List of Notice refernce sequences*/
typedef SEC_List_S NoticeReferenceSeqOf;

/*Contains the list of policy qualifier information policy qualifiers are cps url and user notice*/
typedef SEC_List_S PolicyInformationSeqOf;

typedef SEC_List_S X509_POLICY_MAPPING_LIST; /* SEQUENCE SIZE 1..MAX OF X509_POLICY_MAPPING_S */

#define SEC_SHA1_DIGEST_SIZE 20 /* in bytes */

/**
* @defgroup x509v3_extn
This section contains the x509v3_extn Structures, Functions and Enum
*/

/**
* @defgroup x509v3_extnEnum
* @ingroup x509v3_extn
* This section contains x509v3_extn Enum
*/

/**
* @defgroup x509v3_extnStructures
* @ingroup x509v3_extn
This section contains the x509v3_extn Structures
*/

/* This structure is used to hold the certificate issuer name and the serial number.
	The structure is used to hold during generating the hash of the certificate issuer
	name and serial number. This can be used while finding a matching certificate
	from a list of certificate*/
/**
* @defgroup SEC_ISSUER_AND_SERIAL_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stIssuerAndSerial
* {
*	struct stName* issuerName;
*	SEC_BIGINT_S issuerSerialNumber;
* } SEC_ISSUER_AND_SERIAL_S;
* @endcode
*
* @datastruct issuerName Issuer Who has issued the certificate.
* @datastruct issuerSerialNumber Serial number of the certificate.
*/

typedef struct stIssuerAndSerial
{
	struct stName* issuerName;  /*Issuer who has issued the certificate*/
	SEC_BIGINT_S issuerSerialNumber;  /* Serial number of the certificate*/
} SEC_ISSUER_AND_SERIAL_S;


/* The structure is used during the creation of certificate extension. The structure
	supports the different string formats. Either of these string formats can be present*/
/**
* @defgroup X509_DIRECTORY_STRING_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stDirectoryString
* {
* enum enDirectoryStringChoiceId
*   {
*     DIRECTORYSTRING_TELETEXSTRING,
*     DIRECTORYSTRING_PRINTABLESTRING,
*     DIRECTORYSTRING_UNIVERSALSTRING,
*     DIRECTORYSTRING_UTF8STRING,
*     DIRECTORYSTRING_BMPSTRING
*   } choiceId;
*
*   union unDirectoryStringChoiceUnion
*   {
*     SEC_TeletexString_S* teletexString;
*     SEC_PrintableString_S* printableString;
*     SEC_UniversalString_S* universalString;
*     SEC_UTF8String_S* uTF8String;
*     SEC_BMPString_S* bmpString;
*   } a;
* } X509_DIRECTORY_STRING_S;
* @endcode
*
* @datastruct choiceId The enumerator used for various string formats in which the string can be represented.
* @datastruct DIRECTORYSTRING_TELETEXSTRING To represent TELETEX string format.
* @datastruct DIRECTORYSTRING_PRINTABLESTRING To represent PRINTABLE string format.
* @datastruct DIRECTORYSTRING_UNIVERSALSTRING To represent UNIVERSAL string format.
* @datastruct DIRECTORYSTRING_UTF8STRING To represent UTF8 string format.
* @datastruct DIRECTORYSTRING_BMPSTRING To represent BMP string format.
* @datastruct a Union to hold either one of the string representation.
* @datastruct teletexString Structure that contains the TELETEX string and its length.
* @datastruct printableString Structure that contains the PRINTABLE string and its length.
* @datastruct universalString Structure that contains the UNIVERSAL string and its length.
* @datastruct uTF8String Structure that contains the UTF8 string and its length.
* @datastruct bmpString Structure that contains the BMP string and its length.
*/
typedef struct stDirectoryString
{
	/* The various string formats in which the string can be represented*/
    enum enDirectoryStringChoiceId
    {
		/*To represent TELETEX string format*/
        DIRECTORYSTRING_TELETEXSTRING,
		/*To represent PRINTABLE string format*/
        DIRECTORYSTRING_PRINTABLESTRING,
		/*To represent UNIVERSAL string format*/
        DIRECTORYSTRING_UNIVERSALSTRING,
		/*To represent UTF8 string format*/
        DIRECTORYSTRING_UTF8STRING,
		/*To represent BMP string format*/
        DIRECTORYSTRING_BMPSTRING
    } choiceId;

	/* Union to hold either one of the string representation*/
    union unDirectoryStringChoiceUnion
    {
		/*Structure that contains the string and its length*/
	    SEC_TeletexString_S* teletexString;
		/*Structure that contains the string and its length*/
	    SEC_PrintableString_S* printableString;
		/*Structure that contains the string and its length*/
	    SEC_UniversalString_S* universalString;
		/*Structure that contains the string and its length*/
	    SEC_UTF8String_S* uTF8String;
		/*Structure that contains the string and its length*/
	    SEC_BMPString_S* bmpString;
    } a;
} X509_DIRECTORY_STRING_S;




/* The structure that is used in creation of Name Structure.  This structure is set
	in the values field of the AttributeTypeAndValue structure.  The structure provides
	options of representing the string in the different formats. The types in the Name
	structure that use this structure are as below.
		1) Name
		2) CommonName
		3) Psuedonym
		4) Organization
		5) Organization Unit Name
		6) Title
		7) State or Province name
		8) Initials
		9) Given Name
	   10) Generation Qualifer
	   11) Locality
	   12) Surname
*/
/**
* @defgroup X520_NAME_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stX520Name
* {
*   enum X520nameChoiceId
*    {
*      X520NAME_TELETEXSTRING,
*      X520NAME_PRINTABLESTRING,
*      X520NAME_UNIVERSALSTRING,
*      X520NAME_UTF8STRING,
*      X520NAME_BMPSTRING
*    } choiceId;
*   union X520nameChoiceUnion
*    {
*      SEC_TeletexString_S* teletexString;
*      SEC_PrintableString_S* printableString;
*      SEC_UniversalString_S* universalString;
*      SEC_UTF8String_S* utf8String;
*      SEC_BMPString_S* bmpString;
*    } a;
* } X520_NAME_S;
* @endcode
*
* @datastruct choiceId The enumerator used for various string formats in which the string can be represented.
* @datastruct X520NAME_TELETEXSTRING To represent TELETEX string format.
* @datastruct X520NAME_PRINTABLESTRING To represent PRINTABLE string format.
* @datastruct X520NAME_UNIVERSALSTRING To represent UNIVERSAL string format.
* @datastruct X520NAME_UTF8STRING To represent UTF8 string format.
* @datastruct X520NAME_BMPSTRING To represent BMP string format.
* @datastruct a Union to hold either one of the string representation.
* @datastruct teletexString Structure that contains the TELETEX string and its length.
* @datastruct printableString Structure that contains the PRINTABLE string and its length.
* @datastruct universalString Structure that contains the UNIVERSAL string and its length.
* @datastruct utf8String Structure that contains the UTF8 string and its length.
* @datastruct bmpString Structure that contains the BMP string and its length.
*/
typedef struct stX520Name
{
   	/* The various string formats in which the string can be represented*/
	enum X520nameChoiceId
    {
		/*To represent TELETEX string format*/
        X520NAME_TELETEXSTRING,
		/*To represent PRINTABLE string format*/
        X520NAME_PRINTABLESTRING,
		/*To represent UNIVERSAL string format*/
        X520NAME_UNIVERSALSTRING,
		/*To represent UTF8 string format*/
        X520NAME_UTF8STRING,
		/*To represent BMP string format*/
        X520NAME_BMPSTRING
    } choiceId;

   	/* Union to hold either one of the string representation*/
	union X520nameChoiceUnion
    {
		/*Structure that contains the string and its length*/
		SEC_TeletexString_S* teletexString;
		/*Structure that contains the string and its length*/
		SEC_PrintableString_S* printableString;
		/*Structure that contains the string and its length*/
		SEC_UniversalString_S* universalString;
		/*Structure that contains the string and its length*/
		SEC_UTF8String_S* utf8String;
		/*Structure that contains the string and its length*/
		SEC_BMPString_S* bmpString;
    } a;
} X520_NAME_S;




/* The structure is used during the creation of certificate extension. The structure
	supports the different string formats. Either of these string formats can be present*/
/**
* @defgroup X509_DISPLAY_TEXT_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stDisplayText
* {
*    enum DisplayTextChoiceId
*     {
*       DISPLAYTEXT_IA5STRING,
*       DISPLAYTEXT_VISIBLESTRING,
*       DISPLAYTEXT_BMPSTRING,
*       DISPLAYTEXT_UTF8STRING
*     } choiceId;
*    union DisplayTextChoiceUnion
*     {
*       SEC_IA5String_S* ia5String;
*       SEC_VisibleString_S* visibleString;
*       SEC_BMPString_S* bmpString;
*       SEC_UTF8String_S* utf8String;
*     } a;
* } X509_DISPLAY_TEXT_S;
* @endcode
*
* @datastruct choiceId The enumerator used for various string formats in which the string can be represented.
* @datastruct DISPLAYTEXT_IA5STRING To represent IA5 string format.
* @datastruct DISPLAYTEXT_VISIBLESTRING To represent VISIBLE string format.
* @datastruct DISPLAYTEXT_BMPSTRING To represent BMP string format.
* @datastruct DISPLAYTEXT_UTF8STRING To represent UTF8 string format.
* @datastruct a Union to hold either one of the string representation. The maximum length of the
* string is 200.
* @datastruct ia5String Structure that contains the IA5 string and its length.
* @datastruct visibleString Structure that contains the VISIBLE string and its length.
* @datastruct bmpString Structure that contains the BMP string and its length.
* @datastruct utf8String Structure that contains the UTF8 string and its length.
*/
typedef struct stDisplayText
{
   	/* The various string formats in which the string can be represented*/
	enum DisplayTextChoiceId
    {
		/*To represent IA5 string format*/
        DISPLAYTEXT_IA5STRING,
		/*To represent VISIBLE string format*/
        DISPLAYTEXT_VISIBLESTRING,
		/*To represent BMP string format*/
        DISPLAYTEXT_BMPSTRING,
		/*To represent UTF8 string format*/
        DISPLAYTEXT_UTF8STRING
    } choiceId;

   	/* Union to hold either one of the string representation. The maximum length of the
		string is 200.*/
	union DisplayTextChoiceUnion
    {
		/*Structure that contains the string and its length*/
		SEC_IA5String_S* ia5String;
		/*Structure that contains the string and its length*/
		SEC_VisibleString_S* visibleString;
		/*Structure that contains the string and its length*/
		SEC_BMPString_S* bmpString;
		/*Structure that contains the string and its length*/
		SEC_UTF8String_S* utf8String;
    } a;
} X509_DISPLAY_TEXT_S;




/* The permanent identifier is an optional feature that may be used by a
	CA to indicate that two or more certificates relate to the same
	entity, even if they contain different subject name (DNs) or
	different names in the subjectAltName extension, or if the name or
	the affiliation of that entity stored in the subject or another name
	form in the subjectAltName extension has changed.*/
/**
* @defgroup X509_PERMANENT_IDENTIFIER_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stPermanentIdentifier
* {
*   SEC_UTF8String_S identifierValue;
*   SEC_AsnOid_S assigner;
* } X509_PERMANENT_IDENTIFIER_S;	
* @endcode
*
* @datastruct identifierValue The organization assigning the identifierValue may be the CA that has issued the
* certificate or a different organization called an Assigner Authority. An Assigner Authority may be a government,
* a government agency, a corporation, or any other sort of organization.
* @datastruct assigner When the assigner field is present, then it is an OID which identifies a naming space.
* If the field is absent then the assigner is the Certificate Issuer.
*/
typedef struct stPermanentIdentifier
{
	/* The organization assigning the identifierValue may be the CA that has
		issued the certificate or a different organization called an Assigner
		Authority. An Assigner Authority may be a government, a government agency,
		a corporation, or any other sort of organization*/
	SEC_UTF8String_S identifierValue;

	/* When the assigner field is present, then it is an OID which identifies a
		naming space. If the field is absent then the assigner is the Certificate
		Issuer*/
	SEC_AsnOid_S assigner;
} X509_PERMANENT_IDENTIFIER_S;



/* The NoticeReference policy Qualifier, if used, names an organization and
    identifies, by number, a particular textual statement prepared by
    that organization*/
/**
* @defgroup X509_NOTICE_REFERENCE_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stNoticeReference
* {
*     X509_DISPLAY_TEXT_S* organization;
*     NoticeReferenceSeqOf* noticeNumbers;	
* } X509_NOTICE_REFERENCE_S;
* 
* @endcode
*
* @datastruct organization The notice text that is prepared by the organization that has to be displayed during
* certificate path validation. The notice text has to be the first displayed if the explicit notice text is also
* mentioned in the explicitText field of the UserNotice structure.
* @datastruct noticeNumbers The list of numbers that refer to statements in the organization text.
* 
*/
typedef struct stNoticeReference
{
	/* The notice text that is prepared by the an organization that has to be
		displayed during certificate path validation. The notice text has to be
		the first displayed if the explicit notice text is also mentioned in the
		explicitText field of the UserNotice structure*/
	X509_DISPLAY_TEXT_S* organization;

	/* The list of numbers that refer to statements in the organization text*/
	NoticeReferenceSeqOf* noticeNumbers;
} X509_NOTICE_REFERENCE_S;



/* The structure is part of SubjectInfoAccess and AuthorityInfoAccess extension.
	a)	If the structure goes as part of SubjectInfoAccess or AuthorityInfoAccess ,
		it indicates how to access information and services.
			i)	If the subject is the CA  then, information and services may include
				certificate validation services and CA policy data.
           ii)  When the subject is an end entity, the information describes the type
				of services offered and how to access them*/
/**
* @defgroup X509_ACCESS_DESC_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stAccessDescription
* {
*    SEC_AsnOid_S accessMethod;
*    struct stGeneralName* accessLocation;
* } X509_ACCESS_DESC_S;	
* @endcode
*
* @datastruct accessMethod The accessMethod specifies what type of information has to be extracted. Possible OID
* for accessMethod are:\n
* a) SubjectInfoAccess\n
* i) The ID-AD-CAREPOSITORY OID is used when the subject is a CA, and publishes its certificates
* and CRLs (if issued) in a repository.\n
* ii) The ID-AD-TIMESTAMPING OID is used when the subject offers timestamping services using the Time Stamp Protocol.\n
* b) AuthorityInfoAccess\n
* i) The ID-AD-CAISSUERS OID is used when the additional information lists CAs that have issued certificates superior
* to the CA that issued the certificate containing this extension. The referenced CA issuers description is intended
* to aid certificate users in the selection of a certification path that terminates at a point trusted by the
* certificate user.\n
* ii)  The ID-AD-OCSP OID is used when revocation information for the certificate containing this extension is
* available using the Online Certificate Status Protocol.
* @datastruct accessLocation The accessLocation specifices from where the services or information can be retrieved.\n
* a) SubjectInfoAccess\n
* i) If ID-AD-CAREPOSITORY OID is used then the accessLocation may have one of the following options set.\n
* 1) URL if information is available via http, ftp, ldap.\n
* 2) RFC822Name if information is available via email address.\n
* 3) directoryName if information is available via Directory Access Protocol.\n
* ii) If ID-AD-TIMESTAMPING OID is used then the accessLocation may have one of the following options set.\n
* 1) uRI if information is available via http, ftp, ldap.\n
* 2) rfc822Name if information is available via email address.\n
* 3) dNSName or ipAddress if information is available via TCP/IP.\n
* b) AuthorityInfoAccess\n
* i) If ID-AD-CAISSUERS OID is used then the accessLocation may have one of the following options set.\n
* 1) URL if information is available via http, ftp, ldap.\n
* 2) RFC822Name if information is available via email address.\n
* 3) directoryName if information is available via Directory Access Protocol.\n
* ii) If ID-AD-TIMESTAMPING OID is used then the accessLocation may have one of the following options set.\n
* 1) uRI if information is available via http, ftp, ldap.\n
* 2) rfc822Name if information is available via email address.\n
* 3) dNSName or ipAddress if information is available via TCP/IP.
*/
typedef struct stAccessDescription
{
	/* The accessMethod specifies the what type of information has to be extracted
		Possible OID for accessMethod are:
		a) SubjectInfoAccess
			i) The ID-AD-CAREPOSITORY OID is used when the subject is a CA, and
			   publishes its certificates and CRLs (if issued) in a repository

		   ii) The ID-AD-TIMESTAMPING OID is used when the subject offers
			   timestamping services using the Time Stamp Protocol

		b) AuthorityInfoAccess
			i) The ID-AD-CAISSUERS OID is used when the additional information lists
			   CAs that have issued certificates superior to the CA that issued the
			   certificate containing this extension. The referenced CA issuers
			   description is intended to aid certificate users in the selection of
			   a certification path that terminates at a point trusted by the
			   certificate user.

		   ii) The ID-AD-OCSP OID is used when revocation information for the
			   certificate containing this extension is available using the Online
			   Certificate Status Protocol*/
	SEC_AsnOid_S accessMethod;

	/* The accessLocation specifices from where the services or information can be
		retrieved.
		a) SubjectInfoAccess
			i) If ID-AD-CAREPOSITORY OID is used then the accessLocation may have one
			   of the following options set.
			    1) URL if information is available via http, ftp, ldap.
				2) RFC822Name if information is available via email address.
				3) directoryName if information is available via Directory Access Protocol.

			ii)	If ID-AD-TIMESTAMPING OID is used then the accessLocation may have one
				of the following options set.
				 1) uRI if information is available via http, ftp, ldap.
				 2) rfc822Name if information is available via email address.
				 3) dNSName or ipAddress if information is available via TCP/IP.

		b) AuthorityInfoAccess
			i) If ID-AD-CAISSUERS OID is used then the accessLocation may have one
			   of the following options set.
			    1) URL if information is available via http, ftp, ldap.
				2) RFC822Name if information is available via email address.
				3) directoryName if information is available via Directory Access Protocol.

		   ii) If ID-AD-TIMESTAMPING OID is used then the accessLocation may have one
			   of the following options set.
			    1) uRI if information is available via http, ftp, ldap.
				2) rfc822Name if information is available via email address.
				3) dNSName or ipAddress if information is available via TCP/IP.
	*/
	struct stGeneralName* accessLocation;
} X509_ACCESS_DESC_S;



/* The UserNotice structure is used one of the qualifiers that can be in
	Certificate Policies. User notice is intended for display to a relying
	party when a certificate is used.  The application software should display
	all user notices in all certificates of the certification path used,
	except that if a notice is duplicated only one copy need be displayed.

	If both the options are set then the application must first use the notice
	present in the noticeRef field.*/
/**
* @defgroup X509_USER_NOTICE_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stUserNotice
* {
*     X509_NOTICE_REFERENCE_S* noticeRef;
*     X509_DISPLAY_TEXT_S* explicitText;
* } X509_USER_NOTICE_S; 	
* @endcode
*
* @datastruct noticeRef Optional - Notices text issued by an organization and identifies, by number, a particular textual
* statement prepared by that organization.
* @datastruct explicitText Optional - An explicitText field which includes the textual statement directly in the certificate
* that has to be displayed to a relying party when a certificate is used.
*/
typedef struct stUserNotice
{
	/* Notice text issued by an organization and identifies, by number, a
		particular textual statement prepared by that organization*/
	X509_NOTICE_REFERENCE_S* noticeRef; /* Optional*/

	/* An explicitText field includes the textual statement directly in
	the certificate that has to be displayed to a relying party when a
	certificate is used*/
	X509_DISPLAY_TEXT_S* explicitText; /* Optional*/

} X509_USER_NOTICE_S;



/* This structure goes as part of the CRLDistributionPoint extension. The information
	present in the structure specifies who has generated the CRL*/
/**
* @defgroup X509_DPN_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stDistributionPointName
* {
*   enum DistributionPointNameChoiceId
*    {
*      DISTRIBUTIONPOINTNAME_FULLNAME,
*      DISTRIBUTIONPOINTNAME_NAMERELATIVETOCRLISSUER
*    } choiceId;
*   union DistributionPointNameChoiceUnion
*    {
*      GeneralNames* fullName;
*      RelativeDistinguishedName* nameRelativeToCRLIssuer;
*    } a;
* } X509_DPN_S;
* @endcode
*
* @datastruct choiceId Choice that can be set.
* @datastruct DISTRIBUTIONPOINTNAME_FULLNAME Full name of the issuer.
* @datastruct DISTRIBUTIONPOINTNAME_NAMERELATIVETOCRLISSUER The value provides a distinguished name fragment. The
* fragment is appended to the X.500 distinguished name of the CRL issuer to obtain the distribution point name.
* @datastruct fullName Full name of the issuer.
* @datastruct nameRelativeToCRLIssuer The value provides a distinguished name fragment.
* The fragment is appended to the X.500 distinguished name of the CRL issuer to obtain the distribution point name.
* @datastruct a If the DistributionPointName contains the single
* value nameRelativeToCRLIssuer, the value provides a distinguished name fragment. The fragment is appended to
* the X.500 distinguished name of the CRL issuer to obtain the distribution point name. If the cRLIssuer field
* in the DistributionPoint is present, then the name fragment is appended to the distinguished name that it contains;
* otherwise, the name fragment is appended to the certificate issuer distinguished name. The DistributionPointName
* must not use the nameRealtiveToCRLIssuer alternative when cRLIssuer contains more than one distinguished name.
*/
typedef struct stDistributionPointName
{
	/* Choice that can be set.*/
    enum DistributionPointNameChoiceId
    {
		/*Full name of the issuer */
        DISTRIBUTIONPOINTNAME_FULLNAME,
		/*The value provides a distinguished name
		  fragment. The fragment is appended to the X.500 distinguished name
		  of the CRL issuer to obtain the distribution point name.*/
        DISTRIBUTIONPOINTNAME_NAMERELATIVETOCRLISSUER
    } choiceId;

	/*  If the DistributionPointName contains the single value nameRelativeToCRLIssuer,
		 the value provides a distinguished name fragment. The fragment is appended to
		 the X.500 distinguished name of the CRL issuer to obtain the distribution point
		 name. If the cRLIssuer field in the DistributionPoint is present, then the name
		 fragment is appended to the distinguished name that it contains; otherwise, the
		 name fragment is appended to the certificate issuer distinguished name.  The
		 DistributionPointName must not use the nameRealtiveToCRLIssuer alternative when
		 cRLIssuer contains more than one distinguished name.*/
    union DistributionPointNameChoiceUnion
    {
		/*Full name of the issuer*/
	    GeneralNames* fullName;
		/*The value provides a distinguished name
		  fragment. The fragment is appended to the X.500 distinguished name
		  of the CRL issuer to obtain the distribution point name.*/
	    RelativeDistinguishedName* nameRelativeToCRLIssuer;
    } a;
    
    SEC_NAME_S *dpname;
} X509_DPN_S;



/* The issuing distribution point is a critical CRL extension that identifies
	the CRL distribution point and scope for a particular CRL, and it indicates
	whether the CRL covers revocation for end entity certificates only, CA
	certificates only, attribute certificates only, or a limited set of reason
	codes*/
/**
* @defgroup X509_IDP_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stIssuingDistributionPoint
* {
*   struct stDistributionPointName* distributionPoint;
*   SEC_AsnBool* onlyContainsUserCerts;
*   SEC_AsnBool* onlyContainsCACerts;
*   SEC_AsnBits_S onlySomeReasons;
*   SEC_AsnBool* indirectCRL;
*   SEC_AsnBool* onlyContainsAttributeCerts;
* } X509_IDP_S;
* @endcode
* @datastruct distributionPoint This optional field is used when the CRL issuer is the same as the certificate issuer.
* If this field is set then reason also has to be associated with it.
* @datastruct onlyContainsUserCerts If this flag is set then the CRL generated contains only user certificates.
* The flag can be either TRUE or FALSE.
* @datastruct onlyContainsCACerts If this flag is set then the CRL generated contains only CA certificates.
* The flag can be either TRUE or FALSE.
* @datastruct onlySomeReasons The reason flags indicate the reason for which the CRL is being generated.
* The reasons that can be used are:\n
* 1) X509_REVOKED_AA_COMPROMISE			If the AA compromises\n
* 2) X509_REVOKED_PRIVILEGE_WITHDRAWN   If the privilege has been withdrawn\n
* 3) X509_REVOKED_CERT_HOLD			    If the certificate is kept on hold\n
* 4) X509_REVOKED_CESSATION_OF_OPER     If the rights have been removed\n
* 5) X509_REVOKED_SUPER_SEDED           If the user is superseded\n
* 6) X509_REVOKED_AFFILIATION_CHANGED   If the affilation of the user has changed\n
* 7) X509_REVOKED_CA_COMPROMISE         If the CA private key is compromised\n
* 8) X509_REVOKED_KEY_COMPROMISE        If the Private key is compromised\n
* 9) X509_REVOKED_UNUSED_CERT           If the certificate is no longer needed\n
* @datastruct indirectCRL This flag is set when the certificate issuer is not the CRL issuer.
* @datastruct onlyContainsAttributeCerts This flag is set when the CRL contains only attribute certificates
*/
typedef struct stIssuingDistributionPoint
{
	struct stDistributionPointName* distributionPoint; /* Optional */

	/* If this flag is set then the CRL generated contains only user certificates.
	    The flag can be either TRUE or FALSE*/
	SEC_AsnBool* onlyContainsUserCerts;

	/* If this flag is set then the CRL generated contains only CA certificates.
	    The flag can be either TRUE or FALSE*/
	SEC_AsnBool* onlyContainsCACerts;

	/* The reason flags indicate the reason for which the CRL is being genereated
		The reasons that can be used are
			X509_REVOKED_AA_COMPROMISE			If the AA compromises
			X509_REVOKED_PRIVILEGE_WITHDRAWN    If the privelge has been withdrawn
			X509_REVOKED_CERT_HOLD			    If the certificate is kept on hold
			X509_REVOKED_CESSATION_OF_OPER      If the rights have been removed
			X509_REVOKED_SUPER_SEDED            If the user is superseded
			X509_REVOKED_AFFILIATION_CHANGED    If the affilation of the user has changed
			X509_REVOKED_CA_COMPROMISE          If the CA private key is compromised
			X509_REVOKED_KEY_COMPROMISE         If the Private key is compromised
			X509_REVOKED_UNUSED_CERT            If the certificate is no longer needed*/
	SEC_AsnBits_S onlySomeReasons; /* Optional*/

	/* This flag is set when the certificate issuer is not the CRL issuer.*/
	SEC_AsnBool* indirectCRL;

	/* This flag is set when the CRL contains only attribute certificates*/
	SEC_AsnBool* onlyContainsAttributeCerts;
} X509_IDP_S;



/* The authority key identifier extension provides a means of identifying the
	public key corresponding to the private key used to sign a CRL. The identification
	can be based on either the key identifier (the subject key identifier in the
	CRL signer's certificate) or on the issuer name and serial number.  This extension
    is especially useful where an issuer has more than one signing key
	Note:	CRL Issuer must use the key identifier method and should be present in all
			CRL.*/
/**
* @defgroup X509_AKID_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stAuthorityKeyIdentifier
* {
*   SEC_AsnOcts_S keyIdentifier;
*   GeneralNames* authorityCertIssuer;
*   SEC_BIGINT_S* authorityCertSerialNumber;
* } X509_AKID_S;
* @endcode
*
* @datastruct keyIdentifier Optional - Hash of the PublicKey after the public key is encoded.
* @datastruct authorityCertIssuer Optional - The name of Certificate of the CRL Issuer(incase used in CRL as an extension).
* @datastruct authorityCertSerialNumber Optional - The certificate issuer serial number.
*/
typedef struct stAuthorityKeyIdentifier
{
	/* Hash of the PublicKey after the public key is encoded*/
	SEC_AsnOcts_S keyIdentifier; /* Optional*/

	/* The name of Certificate of the CRL Issuer(incase used in CRL as an extension)*/
	GeneralNames* authorityCertIssuer; /* Optional*/

	/*The certificate issuer serial number */
	SEC_BIGINT_S* authorityCertSerialNumber; /* Optional*/
} X509_AKID_S;




/* The structure that identifies the period within which the private key is valid*/
/**
* @defgroup X509_PRIVKEY_VALIDITY_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stPrivateKeyUsagePeriod
* {
*   SEC_GeneralizedTime_S notBefore;
*   SEC_GeneralizedTime_S notAfter;
* } X509_PRIVKEY_VALIDITY_S;
* @endcode
*
* @datastruct notBefore Optional - Time before which the private key corresponding to the public key is invalid.
* @datastruct notAfter Optional - Time after which the private key corresponding to the public key is invalid.
*/
typedef struct stPrivateKeyUsagePeriod
{
	/* Time before which the private key corresponding to the public key is invalid*/
	SEC_GeneralizedTime_S notBefore; /* Optional*/

	/* Time after which the private key corresponding to the public key is invalid*/
	SEC_GeneralizedTime_S notAfter; /* Optional*/
} X509_PRIVKEY_VALIDITY_S;





/*	The structure is used to hold the policy qualifier information. This structure is
	used during the creation of Certificate policies for the certificate. The structure
	contains an policy OID. Where an OID alone is insufficient, then use of qualifiers
	are recommended.
	There are two types of Policy Qualifiers that can be used
	a) CPS Pointers and
	b) UserNotices

	The CPS Pointer qualifier contains a pointer to a Certification	Practice Statement
	(CPS) published by the CA. The pointer is in the form of a URI.

	User notice is intended for display to a relying party when a
	certificate is used*/
/**
* @defgroup X509_POLICY_QUAL_INFO_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stPolicyQualifierInfo
* {
*   SEC_AsnOid_S policyQualifierId;
*   SEC_AsnAnyDefinedBy_S qualifier;
* } X509_POLICY_QUAL_INFO_S;
* @endcode
*
* @datastruct policyQualifierId An OID that defines a Policy.
* @datastruct qualifier Optional - The field contains either of the Policy Qualifiers. The qualifiers can either be
* CPS URL or the UserNotice structure.
*/
typedef struct stPolicyQualifierInfo
{
	/* An OID that defines an Policy*/
	SEC_AsnOid_S policyQualifierId;

	/* The field contains either of the Policy Qualifiers. The qualifiers can either be
		CPS URL or the UserNotice structure */
	SEC_AsnAnyDefinedBy_S qualifier; /* Optional*/
} X509_POLICY_QUAL_INFO_S;



/* The OtherName structure is a part of GeneralName. Other Name to label a unique
	identifier for the Subject of an end entity certificate*/
/**
* @defgroup SEC_OTHER_NAME_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stOtherName
* {
*   SEC_AsnOid_S id;
*   SEC_AsnAnyDefinedBy_S type;
* } SEC_OTHER_NAME_S;
* @endcode
*
* @datastruct id OID of the PermanentIdentifier structure that is set to AsnAnyDefineBy field.
* @datastruct type The structure that contains the PermanentIdentifier in the values field of type.
*/
typedef struct stOtherName
{
	/* OID of the PermanentIdentifier structure that is set to AsnAnyDefineBy
		field.*/
	SEC_AsnOid_S id;

	/*	The structure that contains the PermanentIdentifier in the values field of
	   	type*/
	SEC_AsnAnyDefinedBy_S type;
} SEC_OTHER_NAME_S;





/* The structure is part of the GeneralName Structure.  The Electonic Document
	Interface(EDI) is used for information exchanage through electronic means.*/
/**
* @defgroup X509_EDI_PARTYNAME_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stEDIPartyName
* {
*   struct stDirectoryString* nameAssigner;
*   struct stDirectoryString* partyName;
* } X509_EDI_PARTYNAME_S;
* @endcode
*
* @datastruct nameAssigner Assigner of the partyName. This is an optional field.
* @datastruct partyName Optional - The string that is given.
*/
typedef struct stEDIPartyName
{
	/* Assigner of the partyName. This is an optional field*/
	struct stDirectoryString* nameAssigner; /* Optional */

	/* The string that is given*/
	struct stDirectoryString* partyName;
} X509_EDI_PARTYNAME_S;



/*	The basic constraints extension identifies whether the certificate is a
	CA certificate and the maximum depth of valid certification	paths that
	include this certificate*/
/**
* @defgroup X509_BASIC_CONSTRAINT_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stBasicConstraints
* {
*   SEC_AsnBool* cA;
*   SEC_AsnInt* pathLenConstraint;
* } X509_BASIC_CONSTRAINT_S;
* @endcode
*
* @datastruct cA The cA boolean indicates whether the certified public key belongs to a CA. If the cA boolean
* is not asserted, then the keyCertSign bit in the key usage extension must not be asserted.
* @datastruct pathLenConstraint Optional (0...MAX) - The pathLenConstraint field is meaningful only if the cA boolean is asserted and
* the key usage extension asserts the keyCertSign bit. It gives the maximum number of non-self-issued intermediate
* certificates that may follow this certificate in a valid certification path.
*/
typedef struct stBasicConstraints
{
	/* The cA boolean indicates whether the certified public key belongs to
		a CA. If the cA boolean is not asserted, then the keyCertSign bit in
		the key usage extension must not be asserted*/
	SEC_AsnBool* cA;

	/* The pathLenConstraint field is meaningful only if the cA boolean is
		asserted and the key usage extension asserts the keyCertSign bit. It
		gives the maximum number of non-self-issued intermediate certificates
		that may follow this certificate in a valid certification path*/
	SEC_AsnInt* pathLenConstraint; /* Optional (0...MAX) */
} X509_BASIC_CONSTRAINT_S;



/* This structure contains a pair of OIDs which are used for mapping a certificate
	policy of a issuer equivalent to that of the subject domain policy*/
/**
* @defgroup X509_POLICY_MAPPING_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stPolicyMappingsSyntaxSeq
* {
*   SEC_AsnOid_S issuerDomainPolicy;
*   SEC_AsnOid_S subjectDomainPolicy;
* } X509_POLICY_MAPPING_S;
* @endcode
*
* @datastruct issuerDomainPolicy OID of the issuer CA.
* @datastruct subjectDomainPolicy OID equivalent to the OID mentioned in issuerDomainPolicy.
*/
typedef struct stPolicyMappingsSyntaxSeq
{
	/* OID of the issuer CA*/
	SEC_AsnOid_S issuerDomainPolicy;

	/* OID equivalent to the OID mentioned in issuerDomainPolicy*/
	SEC_AsnOid_S subjectDomainPolicy;
} X509_POLICY_MAPPING_S;




/*Policy information
	terms indicate the policy under which the certificate has been issued and the
	purposes for which the certificate may be used.  In a CA certificate,these policy
	information terms limit the set of policies for
   certification paths which include this certificate */
/**
* @defgroup X509_POLICY_INFO_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stPolicyInformation
* {
*   SEC_AsnOid_S policyIdentifier;
*	PolicyInformationSeqOf* policyQualifiers;
* } X509_POLICY_INFO_S;
* @endcode
* 
* @datastruct policyIdentifier SEC_AsnOid_S.
* @datastruct policyQualifiers PolicyInformationSeqOf SIZE 1..MAX OPTIONAL.
*/
typedef struct stPolicyInformation /* SEQUENCE */
{
	SEC_AsnOid_S policyIdentifier; /* SEC_AsnOid_S */
	PolicyInformationSeqOf* policyQualifiers; /* PolicyInformationSeqOf SIZE 1..MAX OPTIONAL */
} X509_POLICY_INFO_S;


/* The GeneralName structure is used in several extension. The structure is
	used in providing additional details about the subject or the issuer of
	the certificate.  GeneralName provides several options in which the these
	information can be supplied*/
    enum GeneralNameChoiceId
    {
        GENERALNAME_OTHERNAME,
        GENERALNAME_RFC822NAME,
        GENERALNAME_DNSNAME,
        GENERALNAME_X400ADDRESS,
        GENERALNAME_DIRECTORYNAME,
        GENERALNAME_EDIPARTYNAME,
        GENERALNAME_UNIFORMRESOURCEIDENTIFIER,
        GENERALNAME_IPADDRESS,
        GENERALNAME_REGISTEREDID
    };
/**
* @defgroup SEC_GEN_NAME_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stGeneralName
* {
*   enum GeneralNameChoiceId
*    {
*      GENERALNAME_OTHERNAME,
*      GENERALNAME_RFC822NAME,
*      GENERALNAME_DNSNAME,
*      GENERALNAME_X400ADDRESS,
*      GENERALNAME_DIRECTORYNAME,
*      GENERALNAME_EDIPARTYNAME,
*      GENERALNAME_UNIFORMRESOURCEIDENTIFIER,
*      GENERALNAME_IPADDRESS,
*      GENERALNAME_REGISTEREDID
*    } choiceId;
*   union GeneralNameChoiceUnion
*    {
*      struct stOtherName* otherName;
*      SEC_IA5String_S* rfc822Name;
*      SEC_IA5String_S* dNSName;
*      struct stORAddress* x400Address;
*      struct stName* directoryName;
*      struct stEDIPartyName* ediPartyName;
*      SEC_IA5String_S* uniformResourceIdentifier;
*      SEC_AsnOcts_S* iPAddress;
*      SEC_AsnOid_S* registeredID;
*     } a;
* } SEC_GEN_NAME_S;
* @endcode
*
* @datastruct choiceId Options among which one can be used at an instance.
* @datastruct a Union which can carry the information.
* @datastruct otherName The OtherName structure is a part of GeneralName. Other Name to label a unique
* identifier for the Subject of an end entity certificate.
* @datastruct rfc822Name Email Address.
* @datastruct dNSName Domain Name Service.
* @datastruct x400Address ORAddress.
* @datastruct directoryName X.500 Directory Access Protocol Name.
* @datastruct ediPartyName Electronic Document Interface information of how the information and services can be exchanged.
* @datastruct uniformResourceIdentifier URL information.
* @datastruct iPAddress IP Address.
* @datastruct registeredID Registered OID obtained from the trusted authority.
*/
typedef struct stGeneralName
{
	/* Choices among which one can be used at an instance*/
    enum GeneralNameChoiceId choiceId;
	/* Union which can carry the information*/
    union GeneralNameChoiceUnion
    {
	    /* The OtherName structure is a part of GeneralName. Other Name to label a unique
			identifier for the Subject of an end entity certificate*/
		struct stOtherName* otherName;

		/* Email Address*/
	    SEC_IA5String_S* rfc822Name;

		/* Domain Name Service*/
	    SEC_IA5String_S* dNSName;

		/* ORAddress*/
	    struct stORAddress* x400Address;

		/* X.500 Directory Access Protocol Name*/
	    struct stName* directoryName;

		/* Electronic Document Interface information of how the information
			and services can be exchanged*/
	    struct stEDIPartyName* ediPartyName;

		/* URL information*/
	    SEC_IA5String_S* uniformResourceIdentifier;

		/* IPAddress*/
	    SEC_AsnOcts_S* iPAddress;

		/*	Registered OID obtained from the trusted authority*/
		SEC_AsnOid_S* registeredID;
    } a;
} SEC_GEN_NAME_S;



/* The structure is associated witha a subject name that may contain either iPAddress
	rfc822Name, directoryName etc which can be placed either in the permitted
	or excluded list. Te minimum and maximum fields are not used with any name forms,
	thus minimum must be zero, and maximum must be absent*/
/**
* @defgroup X509_GEN_SUBTREE_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stGeneralSubtree
* {
*   struct stGeneralName* base;
*   SEC_AsnInt* minimum;
*   SEC_AsnInt* maximum;
* } X509_GEN_SUBTREE_S;
* @endcode
*
* @datastruct base The name which will be either in the permitted or the excluded list.
* @datastruct minimum Minimum value is 0 since it is not used.
* @datastruct maximum Optional - The maximum value is usually absent.
*/
typedef struct stGeneralSubtree
{
	/* The name which will be either in the permitted or the excluded list.*/
	struct stGeneralName* base;

	/* Minimum value is 0 since it is not used*/
	SEC_AsnInt* minimum;

	/* The maximum value is usually absent*/
	SEC_AsnInt* maximum; /*Optional*/
} X509_GEN_SUBTREE_S;



/* The policy constraints extension can be used in certificates issued
   to CAs.  The policy constraints extension constrains path validation
   in two ways.  It can be used to prohibit policy mapping or require
   that each certificate in a path contain an acceptable policy identifier*/
/**
* @defgroup X509_POLICY_CONSTRAINT_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stPolicyConstraintsSyntax
* {
*   SEC_AsnInt* requireExplicitPolicy;
*   SEC_AsnInt* inhibitPolicyMapping;
* } X509_POLICY_CONSTRAINT_S;
* @endcode
*
* @datastruct requireExplicitPolicy This field is optional. If the requireExplicitPolicy field is present, its value
* indicates the number of additional certificates that may appear in the path before an explicit policy is required 
* for the entire path.
* @datastruct inhibitPolicyMapping This field is also optional. If the inhibitPolicyMapping field is present, its value
* indicates the number of additional certificates that may appear in the path before policy mapping is no longer permitted.
*/
typedef struct stPolicyConstraintsSyntax
{
	/* If the requireExplicitPolicy field is present, the value of
		requireExplicitPolicy indicates the number of additional certificates
		that may appear in the path before an explicit policy is required for
		the entire path*/
	SEC_AsnInt* requireExplicitPolicy; /* Optional*/

	/* If the inhibitPolicyMapping field is present, the value indicates the
		number of additional certificates that may appear in the path before
		policy mapping is no longer permitted*/
	SEC_AsnInt* inhibitPolicyMapping;  /* Optional*/
} X509_POLICY_CONSTRAINT_S;



/* The name constraints extension, which must be used only in a CA certificate
	and must be set to critical. Restrictions apply to the subject distinguished
	name and apply to subject alternative names. Restrictions are defined in terms
	of permitted or excluded name subtrees. Any name matching a restriction in the
	excludedSubtrees field is invalid regardless of information appearing in the
	permittedSubtrees.*/
/**
* @defgroup X509_NAME_CONSTRAINT_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stNameConstraintsSyntax
* {
*   GeneralSubtrees* permittedSubtrees;
*   GeneralSubtrees* excludedSubtrees;
* } X509_NAME_CONSTRAINT_S;
* @endcode
*
* @datastruct permittedSubtrees This field id optional. If present, it contains the list of permitted names that are
* valid during certificate path validation. 
* @datastruct excludedSubtrees This field is also optional. If present, it contains the list of excluded names that are
* not allowed during path validation. If a name is present in excluded list, the validation should stop even if the name
* is present in permitted list.
*/

typedef struct stNameConstraintsSyntax
{
	/* The list of permitted names that are valid during certificate path validation*/
	GeneralSubtrees* permittedSubtrees; /* Optional*/

	/* The list of excluded names that are not allowed during path validation. If a
		name is present in excluded list, the validation should stop even if the name
		is present in permitted list.*/
	GeneralSubtrees* excludedSubtrees; /* Optional*/
} X509_NAME_CONSTRAINT_S;




/* This structure is used in specifying how the CRL can be obtained. The structure
	contains 3 fields which are optional. But the reason flags must not be only set
	it has to go along with distributionPoint or cRLIssuer.
	a)	If the certificate issuer is not the CRL issuer, then the cRLIssuer field must
		be present and contain the Name of the CRL issuer which has generate the CRL.
	b)  If the certificate issuer is also the CRL issuer, then the cRLIssuer field must
		be omitted and the distributionPoint field must be present*/
/**
* @defgroup X509_DP_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stDistributionPoint
* {
*   struct stDistributionPointName* distributionPoint;
*   SEC_AsnBits_S reasons;
*   GeneralNames* cRLIssuer;
* } X509_DP_S;
* @endcode
*
* @datastruct distributionPoint This optional field is used when the CRL issuer is the same as the certificate issuer.
* If this field is set then reason also has to be associated with it.
* @datastruct reasons This optional field specifies the reason on which the CRL is generated. The reason field should not
* be the only option set in the structure. The reasons include:\n
* 1) unused\n
* 2) keyCompromise\n
* 3) cACompromise\n
* 4) affiliationChanged\n
* 5) superseded\n
* 6) cessationOfOperation\n
* 7) certificateHold\n
* 8) privilegeWithdrawn\n
* 9) aACompromise
* @datastruct cRLIssuer This optional field identifies the entity who signs and issues the CRL. If present, this field is
* set when the certificate issuer is not the CRL issuer.
*/
typedef struct stDistributionPoint
{
	/* Field is used when the CRL issuer is the same as the certificate issuer.
		If this field is set then reason also has to be associated with it*/
	struct stDistributionPointName* distributionPoint; /* Optional*/

	/* Specifies the reason on which the CRL is generated. The reason field should
		not be the only option set in the structure. The reasons includes
		1) unused
        2) keyCompromise
        3) cACompromise
        4) affiliationChanged
        5) superseded
        6) cessationOfOperation
        7) certificateHold
        8) privilegeWithdrawn
        9) aACompromise*/
	SEC_AsnBits_S reasons; /* Optional*/

	/* The cRLIssuer identifies the entity who signs and issues the CRL.  If
	    present.  This field is set when the certificate issuer is not the CRL
		issuer*/
	GeneralNames* cRLIssuer; /* Optional*/
} X509_DP_S;



/*	This structure is used by OCSP responder to indicate the CRL on which a revoked or
	onHold certificate is found. The CRL may be specified by a URL (the URL at which the
    CRL is available), a number (CRL number) or a time (the time at which the relevant CRL
	was created). These extensions are used as singleExtensions.*/
/**
* @defgroup CRL_CID_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct CRL_CID_S
* {
*	SEC_IA5String_S crlUrl;
*	SEC_AsnInt* crlNum;
*	SEC_GeneralizedTime_S crlTime;
* } CRL_CID_S;
* @endcode
*
* @datastruct crlUrl This optional field conatins the URL at which the CRL is available.
* @datastruct crlNum This optional field contains the CRL number of the relevant CRL.
* @datastruct crlTime This optional field contains the time at which the relevant CRL was issued.
*/
typedef struct CRL_CID_S
{
	SEC_IA5String_S crlUrl;			/* Optional - URL at which the CRL is available*/
	SEC_AsnInt* crlNum;				/* Optional - CRL number of the relevant CRL*/
	SEC_GeneralizedTime_S crlTime;	/* Optional - Time at which the relevant CRL was issued */
} CRL_CID_S;

/**
* @defgroup x509v3_extnFunctions
* @ingroup x509v3_extn
This section contains the x509v3_extn Functions
*/

/* To free the CRL Reference structure */



/**
* @defgroup FreeCRLID
* @ingroup x509v3_extnFunctions
* @par Prototype
* @code
* SEC_VOID FreeCRLID(CRL_CID_S *pCRLId);
* @endcode
* @par Purpose
* To free the CRL Reference structure.
* @par Description
* This function is used to free the CRL Reference structure.
*
* @param[in] pCRLId The CRL Structure to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* x509v3_extn.h
*
* @par Note
*
* N/A
* 
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID FreeCRLID(CRL_CID_S *pCRLId);

/* To generate a duplicate of CRL Reference structure */



/**
* @defgroup SEC_dupCRLID
* @ingroup x509v3_extnFunctions
* @par Prototype
* @code
* CRL_CID_S* SEC_dupCRLID(CRL_CID_S* pSrc);
* @endcode
* @par Purpose
* To generate a duplicate of CRL Reference structure.
* @par Description
* This function is used to generate a duplicate of CRL Reference structure.
*
* @param[in] pSrc The CRL Reference structure to be duplicated [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRL_CID_S* A copy of the CRL Reference Structure [CRL_CID_S*|N/A]
*
* @par Dependency
* x509v3_extn.h
*
* @par Note
*
* N/A
* 
* @par Related Topics
* N/A
*/
PSELINKDLL CRL_CID_S* SEC_dupCRLID(CRL_CID_S* pSrc);


/*Reasons for revocation*/
/**
* @defgroup X509_CRL_REASON_E
* @ingroup x509v3_extnEnum
* @par Prototype
* @code
* typedef enum CRLReason
* {
*   CRL_UNSPECIFIED          = 0,
*   CRL_KEY_COMPROMISE       = 1,
*   CRL_CA_COMPROMISE        = 2,
*   CRL_AFFILIATION_CHANGED  = 3,
*   CRL_SUPERSEEDED          = 4,
*   CRL_CESSATION_OPERATION  = 5,
*   CRL_CERTIFICATE_HOLD     = 6,
*   CRL_REM_FROM_CRL         = 8,
*   CRL_PRIV_WITHDRAWN       = 9,
*   CRL_AUTH_ATTR_COMPROMISE = 10
* } X509_CRL_REASON_E;
* @endcode
*
* @datastruct CRL_UNSPECIFIED=0 Reason is not known.
* @datastruct CRL_KEY_COMPROMISE=1 Reason is Key compromise.
* @datastruct CRL_CA_COMPROMISE=2 Reason is CA compromise.
* @datastruct CRL_AFFILIATION_CHANGED=3 Reason is Affiliation changed.
* @datastruct CRL_SUPERSEEDED=4 Reason is Superseded.
* @datastruct CRL_CESSATION_OPERATION=5 Reason is Cessation of operation.
* @datastruct CRL_CERTIFICATE_HOLD=6 Reason is Certificate Hold.
* @datastruct CRL_REM_FROM_CRL=8 Reason is remove from CRL.
* @datastruct CRL_PRIV_WITHDRAWN=9 Reason is Privelge withdrawn.
* @datastruct CRL_AUTH_ATTR_COMPROMISE=10 Reason is ATTR cert compromise.
*/
typedef enum CRLReason
    {
		/*Reason is not known*/
        CRL_UNSPECIFIED = 0,
		/*Reason is Key compromise*/
        CRL_KEY_COMPROMISE = 1,
		/*Reason is CA compromise*/
        CRL_CA_COMPROMISE = 2,
		/*Reason is Affiliation changed*/
        CRL_AFFILIATION_CHANGED = 3,
		/*Reason is Superseded*/
        CRL_SUPERSEEDED = 4,
		/*Reason is Cessation of operation*/
        CRL_CESSATION_OPERATION = 5,
		/*Reason is Certificate Hold*/
        CRL_CERTIFICATE_HOLD = 6,
		/*Reason is remove from CRL*/
        CRL_REM_FROM_CRL = 8,
		/*Reason is Privelge withdrawn*/
        CRL_PRIV_WITHDRAWN = 9,
		/*Reason is ATTR cert compromise*/
        CRL_AUTH_ATTR_COMPROMISE = 10
} X509_CRL_REASON_E; /* ENUMERATED { UNSPECIFIED (0), 
                                     KEYCOMPROMISE (1),
                                     CACOMPROMISE (2),
                                     AFFILIATIONCHANGED (3),
                                     SUPERSEDED (4),
                                     CESSATIONOFOPERATION (5),
                                     CERTIFICATEHOLD (6),
                                     REMOVEFROMCRL (8),
                                     PRIVILEGEWITHDRAWN (9),
                                     AACOMPROMISE (10) }  */

typedef SEC_List_S CRLDistributionPoints; /* SEQUENCE SIZE 1..MAX OF DistributionPoint */

typedef SEC_AsnBits_S ReasonFlags;

typedef SEC_List_S AuthorityInfoAccessSyntax; /* SEQUENCE SIZE 1..MAX OF X509_ACCESS_DESC_S */

/*	This extension provides location information [like URL] about the OCSP server, which provides
	status information about the identified certificates
*/
/**
* @defgroup OCSP_SERV_LOCATOR_S
* @ingroup x509v3_extnStructures
* @par Prototype
* @code
* typedef struct stSERV_LOCATOR_S
* {
*	SEC_NAME_S* pstIssuer;
*	AuthorityInfoAccessSyntax* pstLocator;
* } OCSP_SERV_LOCATOR_S;
* @endcode
*
* @datastruct pstIssuer Name of the Issuer.
* @datastruct pstLocator This specifices the location from where the services or information can be retrieved.
*/
typedef struct stSERV_LOCATOR_S
{
	SEC_NAME_S* pstIssuer;					/* Name of the Issuer */
	AuthorityInfoAccessSyntax* pstLocator;  /* Locator - specifices from where the services or information can be
											   retrieved */
} OCSP_SERV_LOCATOR_S;


//Crl Number info
typedef struct stPKICrlNumbersInfo
{
    SEC_BIGINT_S *pCrlNumber;
    SEC_BIGINT_S *pBaseCrlNumber;
}SEC_PKI_CRL_NUMBER_INFO;

//IDP info
typedef struct stPKICrlIdpAkidInfo
{
    X509_IDP_S *pstIdp;
    X509_AKID_S *pstAkid;
    SEC_INT32 iIdpFlags;
    SEC_INT32 iIdpReasons; 
}SEC_PKI_CRL_IDP_AKID_INFO;


//This structure contains all the fields from the certificate extension
typedef struct stPKICrlExtnFields
{
    SEC_UINT32 uiFlags;

    SEC_PKI_CRL_NUMBER_INFO stCrlNumInfo;

    SEC_PKI_CRL_IDP_AKID_INFO stPKICrlIdpAkidInfo;

    SEC_UCHAR ucCrlHash[SEC_SHA1_DIGEST_SIZE];

}SEC_PKI_X509_CRL_EXT_FIELD_S;



/* To free the ocsp service locator structure */



/**
* @defgroup FreeServLocator
* @ingroup x509v3_extnFunctions
* @par Prototype
* @code
* SEC_VOID FreeServLocator(OCSP_SERV_LOCATOR_S *v);
* @endcode
* @par Purpose
* To free the OCSP service locator structure.
* @par Description
* This function is used to free the OCSP service locator structure.
*
* @param[in] v The OCSP Service locator to be freed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* x509v3_extn.h
*
* @par Note
*
* N/A
* 
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_VOID FreeServLocator(OCSP_SERV_LOCATOR_S *v);

/*	To duplicate the OCSP service locator structure */



/**
* @defgroup SEC_dupServLocator
* @ingroup x509v3_extnFunctions
* @par Prototype
* @code
* OCSP_SERV_LOCATOR_S* SEC_dupServLocator(OCSP_SERV_LOCATOR_S* pSrc);
* @endcode
* @par Purpose
* To duplicate the OCSP service locator structure.
* @par Description
* This function is used to duplicate the OCSP service locator structure.
*
* @param[in] pSrc The OCSP service locator structure to be duplicated [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_SERV_LOCATOR_S* A copy of the OCSP service locator structure [OCSP_SERV_LOCATOR_S*|N/A]
*
* @par Dependency
* x509v3_extn.h
*
* @par Note
*
* N/A
* 
* @par Related Topics
* N/A
*/
PSELINKDLL OCSP_SERV_LOCATOR_S* SEC_dupServLocator(OCSP_SERV_LOCATOR_S* pSrc);

/*	The date obtained by subtracting retention interval value from the producedAt time in a response is
    defined as the certificate's "archive cutoff" date */
typedef SEC_GeneralizedTime_S ARCHIVE_CUT_OFF_S;


#ifdef __cplusplus
}
#endif

#endif /* _IPSI_X509V3_EXTN_H_ */

