/*

                Copyright 2005, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

------------------------------------------------------------------------------

                              x509.h

  Project Code: SeCert
   Module Name: X509
  Date Created: Mon 2005-07-11
        Author: Brijoo and Guru
  Descrption  : X509.h provides all the basic API for create,set,add and get
				 on a X509Certificate and X509CRL

*/

#include "ipsi_pse_build_conf.h"

#ifndef _IPSI_x509_H
#define _IPSI_x509_H



#include "sec_sys.h"
#include "sec_util.h"
#include "sec_crypto.h"
#include "asn-types.h"
#include "sec_list.h"
#include "sec_error.h"
#include "x509_basictypes.h"
#include "x509v3_extn.h"


#ifdef  __cplusplus
extern "C"{
#endif

/* Key Usage */

/*When the encipherOnly bit is asserted and
the keyAgreement bit is also set, the subject public key may be
used only for enciphering data while performing key agreement.*/
#define X509_KU_ENCIPHER_ONLY		0x0001

/*The cRLSign bit is asserted when the subject public key is used
for verifying a signature on certificate revocation list*/
#define X509_KU_CRL_SIGN			0x0002

/*The keyCertSign bit is asserted when the subject public key is
used for verifying a signature on public key certificates.*/
#define X509_KU_KEY_CERT_SIGN		0x0004

/*The keyAgreement bit is asserted when the subject public key is
used for key agreement. For example, when a Diffie-Hellman key is
to be used for key management, then this bit is set.*/
#define X509_KU_KEY_AGREEMENT		0x0008

/*The dataEncipherment bit is asserted when the subject public key
is used for enciphering user data, other than cryptographic keys.*/
#define X509_KU_DATA_ENCIPHERMENT	0x0010

/*The keyEncipherment bit is asserted when the subject public key is
used for key transport. For example, when an RSA key is to be
used for key management, then this bit is set.*/
#define X509_KU_KEY_ENCIPHERMENT	0x0020

/*The nonRepudiation bit is asserted when the subject public key is
used to verify digital signatures used to provide a nonrepudiation
service which protects against the signing entity
falsely denying some action, excluding certificate or CRL signing.
In the case of later conflict, a reliable third party may
determine the authenticity of the signed data.*/
#define X509_KU_NON_REPUDIATION		0x0040

/*The digitalSignature bit is asserted when the subject public key*/
/*is used with a digital signature mechanism to support security*/
/*services other than certificate signing (bit 5), or CRL signing (bit 6)*/
#define X509_KU_DIGITAL_SIGNATURE	0x0080

/*When the decipherOnly bit is asserted and
the keyAgreement bit is also set, the subject public key may be
used only for deciphering data while performing key agreement.*/
#define X509_KU_DECIPHER_ONLY	 	0x0100


/*Extended key usage*/
/*WWW server authentication*/
#define X509_EXT_KU_SERVERAUTH			( X509_KU_DIGITAL_SIGNATURE | ( X509_KU_KEY_ENCIPHERMENT | X509_KU_KEY_AGREEMENT ))
/*WWW client authentication*/
#define X509_EXT_KU_CLIENTAUTH			( X509_KU_DIGITAL_SIGNATURE | X509_KU_KEY_AGREEMENT )
/*Signing of downloadable executable code*/
#define X509_EXT_KU_CODE_SINGING		( X509_KU_DIGITAL_SIGNATURE )
/*Binding the hash of an object to a time*/
/*Signing OCSP responses*/
#define X509_EXT_KU_TIMESTAMP_OCSPSIGNING  	( X509_KU_DIGITAL_SIGNATURE | X509_KU_NON_REPUDIATION )
/*E-mail protection*/
#define X509_EXT_KU_EMAIL_PROTECTION ( X509_KU_DIGITAL_SIGNATURE | X509_KU_NON_REPUDIATION | \
									   X509_KU_KEY_ENCIPHERMENT | X509_KU_KEY_AGREEMENT )


/*REVOCATION TYPE */

/*If the authority compromises*/
#define X509_REVOKED_AA_COMPROMISE         0x00800000/*If the AA compromises*/

/*If the privlege has been withdrawn from the user*/
#define X509_REVOKED_PRIVILEGE_WITHDRAWN   0x01000000/*If the privelge has been withdrawn*/

/*CertificateHold shall be used to indicate that the
certificate's status is questionable and may be revoked*/
#define X509_REVOKED_CERT_HOLD			   0x02000000

/*CessationOfOperation indicates that the certificate is no longer needed for the purpose for
 * which it was issued but there is no cause to suspect that the private key has been compromised*/
#define X509_REVOKED_CESSATION_OF_OPER     0x04000000

/*Superseded indicates that the certificate has been superseded
 *but there is no cause to suspect that the private key has been compromised;*/
#define X509_REVOKED_SUPER_SEDED           0x08000000

/*AffiliationChanged indicates that the subject’s name or other information in the certificate
 *has been modified but there is no cause to suspect that the private key has been compromised;*/
#define X509_REVOKED_AFFILIATION_CHANGED   0x10000000

/*CACompromise is used in revoking a CA-certificate;
 *It indicates that it is known or suspected that the subject’s private key, or other aspects of
 *the subject validated in the certificate, have been compromised;*/
#define X509_REVOKED_CA_COMPROMISE         0x20000000

/*KeyCompromise is used in revoking an end-entity certificate
 *It indicates that it is known or suspected that the subject’s
 *private key, or other aspects of the subject validated in the certificate, have been compromised*/
#define X509_REVOKED_KEY_COMPROMISE        0x40000000

/*If the certificate is no longer used*/
#define X509_REVOKED_UNUSED_CERT           0x80000000

/*Macro for a valid CRL after validating the date*/
#define  X509_CRL_VALID 0
/*Macro for a Invalid CRL after validating the date*/
#define  X509_CRL_INVALID 1
/*Enum that needs to be used to set the vesrion of CRL*/

/*Macro when cert is revoked*/
#define X509_CERT_REVOKED  (-2)
/*Macro when cert is not revoked*/
#define X509_CERT_UNREVOKED (-3)

/**
* @defgroup x509
* This section contains x509 Enums, Structures and Functions
*/

/**
* @defgroup x509Enums
* @ingroup x509
* This section contains x509 Enums
*/

/*Enum that needs to be used to set the vesrion of CRL*/

/**
* @defgroup X509_CRLVERSION_E
* @ingroup x509Enums
* @par Prototype
* @code
* typedef enum enCRLVersion
* {
*   X509_CRL_VERSION1 = 0,
*   X509_CRL_VERSION2 = 1
* }X509_CRLVERSION_E;
* @endcode
*
* @datastruct X509_CRL_VERSION1=0 For version 1 CRL.
* @datastruct X509_CRL_VERSION2=1 For version 2 CRL.
*/
typedef enum enCRLVersion
{

	/*For version 1 CRL*/
	X509_CRL_VERSION1 = 0,
	/*For version 2 CRL*/
	X509_CRL_VERSION2 = 1

}X509_CRLVERSION_E;


/*Enum that needs to be used to set the vesrion of Certificate*/
/**
* @defgroup X509_CERTVERSION_E
* @ingroup x509Enums
* @par Prototype
* @code
* typedef enum enCertificateVersion
* {
*   X509_CERT_VERSION1 = 0,
*   X509_CERT_VERSION2 = 1,
*   X509_CERT_VERSION3 = 2
* } X509_CERTVERSION_E;
* @endcode
*
* @datastruct X509_CERT_VERSION1=0 For version 1 certificate.
* @datastruct X509_CERT_VERSION2=1 For version 2 certificate.
* @datastruct X509_CERT_VERSION3=2 For version 3 certificate.
*/
typedef enum enCertificateVersion
{
	/*For version 1 certificate*/
	X509_CERT_VERSION1 = 0,
    /*For version 2 certificate*/
    X509_CERT_VERSION2 = 1,
	/*For version 3 certificate*/
    X509_CERT_VERSION3 = 2
}X509_CERTVERSION_E;


/*Enum that needs to be used to indicate the type of Key Generation*/
/**
* @defgroup X509_KIDGENTYPE_E
* @ingroup x509Enums
* @par Prototype
* @code
* typedef enum enKID_GenerationType
* {
*   X509_KID_SHA1_160 = 0,
*   X509_KID_SHA1_60  = 1
* } X509_KIDGENTYPE_E;
* @endcode
*
* @datastruct X509_KID_SHA1_160=0 For 20 bytes hash.
* @datastruct X509_KID_SHA1_60=1 For 8 byte hash.
*/
typedef enum enKID_GenerationType
{
	/*For 20 bytes hash*/
	X509_KID_SHA1_160 = 0,
    /*For 8 byte hash*/
    X509_KID_SHA1_60 = 1
}X509_KIDGENTYPE_E;


/*Enum that can be used to indicate the type of Attributes in A X500 Name*/
/**
* @defgroup X509_NAME_ATTR_TYPE_E
* @ingroup x509Enums
* @par Prototype
* @code
* typedef enum enAttrTypesInName
* {
*   TYPE_COUNTRY = CID_AT_COUNTRYNAME,
*   TYPE_ORGANIZATION = CID_AT_ORGANIZATIONNAME,
*   TYPE_ORG_UNIT_NAME = CID_AT_ORGANIZATIONALUNITNAME,
*   TYPE_DNQUALIFIER = CID_AT_DNQUALIFIER,
*   TYPE_STATE = CID_AT_STATEORPROVINCENAME,
*   TYPE_NAME = CID_AT_NAME,
*   TYPE_COMMON_NAME = CID_AT_COMMONNAME,
*   TYPE_SERIAL_NUMBER = CID_AT_SERIALNUMBER,
*   TYPE_LOCALITY = CID_AT_LOCALITYNAME,
*   TYPE_TITLE = CID_AT_TITLE,
*   TYPE_SURNAME = CID_AT_SURNAME,
*   TYPE_GIVENNAME = CID_AT_GIVENNAME,
*   TYPE_INITIALS = CID_AT_INITIALS,
*   TYPE_PSEUDONYM = CID_AT_PSEUDONYM,
*   TYPE_GENQUALIFIER = CID_AT_GENERATIONQUALIFIER,
*   TYPE_EMAIL = CID_EMAILADDRESS,
*   TYPE_DOMAIN_COMPONENT = CID_DOMAINCOMPONENT
*   TYPE_UNSTRUCTURED_NAME = CID_UNSTRUCTURED_NAME,
*   TYPE_UNSTRUCTURED_ADDR = CID_UNSTRUCTURED_ADDR
* } X509_NAME_ATTR_TYPE_E;
* @endcode
*
* @datastruct TYPE_COUNTRY=CID_AT_COUNTRYNAME Country Name.
* @datastruct TYPE_ORGANIZATION=CID_AT_ORGANIZATIONNAME Organization Name.
* @datastruct TYPE_ORG_UNIT_NAME=CID_AT_ORGANIZATIONALUNITNAME Organization Unit Name.
* @datastruct TYPE_DNQUALIFIER=CID_AT_DNQUALIFIER DN Qualifier.
* @datastruct TYPE_STATE=CID_AT_STATEORPROVINCENAME State or Province name.
* @datastruct TYPE_NAME=CID_AT_NAME Name.
* @datastruct TYPE_COMMON_NAME=CID_AT_COMMONNAME Common Name.
* @datastruct TYPE_SERIAL_NUMBER=CID_AT_SERIALNUMBER Serial Number.
* @datastruct TYPE_LOCALITY=CID_AT_LOCALITYNAME Locality name.
* @datastruct TYPE_TITLE=CID_AT_TITLE Title.
* @datastruct TYPE_SURNAME=CID_AT_SURNAME Surname.
* @datastruct TYPE_GIVENNAME=CID_AT_GIVENNAME Given Name.
* @datastruct TYPE_INITIALS=CID_AT_INITIALS Initial.
* @datastruct TYPE_PSEUDONYM=CID_AT_PSEUDONYM Psuedonym.
* @datastruct TYPE_GENQUALIFIER=CID_AT_GENERATIONQUALIFIER Generation Qualifier.
* @datastruct TYPE_EMAIL=CID_EMAILADDRESS Email Address.
* @datastruct TYPE_DOMAIN_COMPONENT=CID_DOMAINCOMPONENT Domain Component.
* @datastruct TYPE_UNSTRUCTURED_NAME=CID_UNSTRUCTURED_NAME Unstructured Name.
* @datastruct TYPE_UNSTRUCTURED_ADDR=CID_UNSTRUCTURED_ADDR Unstructured Address.
*/
typedef enum enAttrTypesInName
{
	/*Country Name */
	TYPE_COUNTRY = CID_AT_COUNTRYNAME,
	/* Organization Name*/
	TYPE_ORGANIZATION = CID_AT_ORGANIZATIONNAME,
	/* Organization Unit Name*/
	TYPE_ORG_UNIT_NAME = CID_AT_ORGANIZATIONALUNITNAME,
	 /* DN Qualifier*/
    TYPE_DNQUALIFIER = CID_AT_DNQUALIFIER,
	/* State or Province name*/
    TYPE_STATE = CID_AT_STATEORPROVINCENAME,
	 /* Name */
	TYPE_NAME = CID_AT_NAME,
	 /* Common Name */
	TYPE_COMMON_NAME = CID_AT_COMMONNAME,
	 /*Serial Number */
	TYPE_SERIAL_NUMBER = CID_AT_SERIALNUMBER,
	/* Locality name*/
	TYPE_LOCALITY = CID_AT_LOCALITYNAME,
	/* Title */
    TYPE_TITLE = CID_AT_TITLE,
	/* Surname*/
    TYPE_SURNAME = CID_AT_SURNAME,
	/* Given Name */
    TYPE_GIVENNAME = CID_AT_GIVENNAME,
	/* Initial */
    TYPE_INITIALS = CID_AT_INITIALS,
	/* Psuedonym */
    TYPE_PSEUDONYM = CID_AT_PSEUDONYM,
	/*Generation Qualifier */
    TYPE_GENQUALIFIER = CID_AT_GENERATIONQUALIFIER,
	 /* Email Address*/
	TYPE_EMAIL = CID_EMAILADDRESS,
	/* Domain Component*/
	TYPE_DOMAIN_COMPONENT = CID_DOMAINCOMPONENT,
	/* UnstructuredName*/
    TYPE_UNSTRUCTURED_NAME = CID_UNSTRUCTURED_NAME,
    /* UnstructuredAddress*/
    TYPE_UNSTRUCTURED_ADDR = CID_UNSTRUCTURED_ADDR
}X509_NAME_ATTR_TYPE_E;




/* This enum is used to create an Subject Directory Attributes Extensions which can
   take a list of any in the below mention types as inputs*/

/**
* @defgroup X509_EXTN_SUBJDIRATTR_E
* @ingroup x509Enums
* @par Prototype
* @code
* typedef enum enAttrInSubDirAttr
* {
*   TYPE_DOB                  = CID_PDA_DATEOFBIRTH,
*   TYPE_PLACEOFBIRTH         = CID_PDA_PLACEOFBIRTH,
*   TYPE_GENDER               = CID_PDA_GENDER,
*   TYPE_COUNTRYOFCITIZENSHIP = CID_PDA_COUNTRYOFCITIZENSHIP,
*   TYPE_COUNTRYOFRESIDENCE   = CID_PDA_COUNTRYOFRESIDENCE,
* } X509_EXTN_SUBJDIRATTR_E;
* @endcode
*
* @datastruct TYPE_DOB=CID_PDA_DATEOFBIRTH To represent Date Of Birth in GeneralizedTime.
* @datastruct TYPE_PLACEOFBIRTH=CID_PDA_PLACEOFBIRTH To represent Place Of Birth in Directory String Format.
* @datastruct TYPE_GENDER=CID_PDA_GENDER To represent Gender in IA5String Format.
* @datastruct TYPE_COUNTRYOFCITIZENSHIP=CID_PDA_COUNTRYOFCITIZENSHIP To represent Country of
* CitizenShip in IA5String Format.
* @datastruct TYPE_COUNTRYOFRESIDENCE=CID_PDA_COUNTRYOFRESIDENCE To represent Country of Residence in IA5String Format.
*/
typedef enum enAttrInSubDirAttr
{
	 /* To represent Date Of Birth in GeneralizedTime*/
	TYPE_DOB = CID_PDA_DATEOFBIRTH,
	 /* To represent Place Of Birth in Directory String Format*/
	TYPE_PLACEOFBIRTH = CID_PDA_PLACEOFBIRTH,
	 /* To represent Gender in IA5String Format */
	TYPE_GENDER = CID_PDA_GENDER,
	/* To represent Country of CitizenShip in IA5String Format */
	TYPE_COUNTRYOFCITIZENSHIP = CID_PDA_COUNTRYOFCITIZENSHIP,
	/* To represent Country of Residence in IA5String Format */
	TYPE_COUNTRYOFRESIDENCE = CID_PDA_COUNTRYOFRESIDENCE
} X509_EXTN_SUBJDIRATTR_E;

/*The enum is used to provide options to create Policy Qualifiers in
  Certificate Policies*/


/*This enum, Defines all constants that is used in the creation of ORADDRESS structure ,
EDI Party name ,URL ,RFC822 name ,DNS Name ,IPAddress, Regester id ,OTHER name ,which internally will be used in the
 creation of General Name*/
/*All these constants need to be used in the creation of common nodes ,which internally
will be formed into a list of common and  provided as input to create general name Api*/
/**
* @defgroup X509_TYPE_E
* @ingroup x509Enums
* @par Prototype
* @code
* typedef enum enCommonType
* {
*   TYPE_ORADDRESS                                        = 0,
*   TYPE_BUILTINSTANDARDATTRIBUTE                         = 1,
*   TYPE_COUNTRYNAME                                      = 2,
*   TYPE_ADMINISTRATIONDOMAINNAME                         = 3,
*   TYPE_NETWORKADDRESS                                   = 4,
*   TYPE_TERMINALIDENTIFIER                               = 5,
*   TYPE_PRIVATEDOMAINNAME                                = 6,
*   TYPE_ORGANIZATIONNAME                                 = 7,
*   TYPE_NUMERICUSERIDENTIFIER                            = 8,
*   TYPE_PERSONALNAME                                     = 9,
*   TYPE_ORGANIZATIONALUNITNAME                           = 10,
*   TYPE_BUILTINDOMAINDEFINEDATTRIBUTE                    = 11,
*   TYPE_EXTENSIONATTRIBUTE                               = 12,
*   TYPE_EDIPARTYNAME                                     = 13,
*   TYPE_NAMEASSIGNER                                     = 14,
*   TYPE_PARTYNAME                                        = 15,
*   TYPE_RFC822NAME                                       = 16,
*   TYPE_DNSNAME                                          = 17,
*   TYPE_IPADDRESS                                        = 18,
*   TYPE_REGISTEREDID                                     = 19,
*   TYPE_URL                                              = 20,
*   TYPE_OTHERNAME                                        = 21,
*   TYPE_IDENTIFIERVALUE                                  = 22,
*   TYPE_ASSIGNER                                         = 23,
*   TYPE_STRING                                           = 24,
*   TYPE_ORADDRESS_SURNAME                                = 25,
*   TYPE_ORADDRESS_GENQUALIFIER                           = 26,
*   TYPE_ORADDRESS_INITIALS                               = 27,
*   TYPE_ORADDRESS_GIVENNAME                              = 28,
*   COMMON_NAME_ANY_ID                                    = 29,
*   TELETEX_COMMON_NAME_ANY_ID                            = 30,
*   TELETEX_ORGANIZATION_NAME_ANY_ID                      = 31,
*   TELETEX_PERSONAL_NAME_ANY_ID                          = 32,
*   TELETEX_ORGANIZATIONAL_UNIT_NAMES_ANY_ID              = 33,
*   PDS_NAME_ANY_ID                                       = 34,
*   PHYSICAL_DELIVERY_COUNTRY_NAME_ANY_ID                 = 35,
*   POSTAL_CODE_ANY_ID                                    = 36,
*   PHYSICAL_DELIVERY_OFFICE_NAME_ANY_ID                  = 37,
*   PHYSICAL_DELIVERY_OFFICE_NUMBER_ANY_ID                = 38,
*   EXTENSION_OR_ADDRESS_COMPONENTS_ANY_ID                = 39,
*   PHYSICAL_DELIVERY_PERSONAL_NAME_ANY_ID                = 40,
*   PHYSICAL_DELIVERY_ORGANIZATION_NAME_ANY_ID            = 41,
*   EXTENSION_PHYSICAL_DELIVERY_ADDRESS_COMPONENTS_ANY_ID = 42,
*   UNFORMATTED_POSTAL_ADDRESS_ANY_ID                     = 43,
*   STREET_ADDRESS_ANY_ID                                 = 44,
*   POST_OFFICE_BOX_ADDRESS_ANY_ID                        = 45,
*   POSTE_RESTANTE_ADDRESS_ANY_ID                         = 46,
*   UNIQUE_POSTAL_NAME_ANY_ID                             = 47,
*   LOCAL_POSTAL_ATTRIBUTES_ANY_ID                        = 48,
*   EXTENDED_NETWORK_ADDRESS_ANY_ID                       = 49,
*   TERMINAL_TYPE_ANY_ID                                  = 50,
*   EXTNETWORKADDR_E1634ADDR                              = 51,
*   EXTNETWORKADDR_PSAPADDR                               = 52,
*   TYPE_ORGANIZATIONALUNITNAME_LIST                      = 53,
*   TYPE_POLICYID                                         = 54,
*   TYPE_USERNOTICE                                       = 55,
*   TYPE_EXPLICITTEXT                                     = 56,
*   TYPE_ORGTXT                                           = 57,
*   TYPE_NOTICENUMBERS                                    = 58,
*   TYPE_CPS                                              = 59
* } X509_TYPE_E;
*
* @endcode
*
* @datastruct TYPE_ORADDRESS=0 TO CREATE ORADRESS STRUCTURE.
* @datastruct TYPE_BUILTINSTANDARDATTRIBUTE=1 TO CREATE Built in standard attribute structure.
* @datastruct TYPE_COUNTRYNAME=2 To set the country name.
* @datastruct TYPE_ADMINISTRATIONDOMAINNAME=3 To set the adminisatration domain name.
* @datastruct TYPE_NETWORKADDRESS=4 To set the network adderss.
* @datastruct TYPE_TERMINALIDENTIFIER=5 To set the terminal identifier.
* @datastruct TYPE_PRIVATEDOMAINNAME=6 To set the private domain name.
* @datastruct TYPE_ORGANIZATIONNAME=7 To set the organization name.
* @datastruct TYPE_NUMERICUSERIDENTIFIER=8 To set the numeric user identifier.
* @datastruct TYPE_PERSONALNAME=9 To set the personal name.
* @datastruct TYPE_ORGANIZATIONALUNITNAME=10 To set the organization name.
* @datastruct TYPE_BUILTINDOMAINDEFINEDATTRIBUTE=11 To set the domain defined attribiutes.
* @datastruct TYPE_EXTENSIONATTRIBUTE=12 To set the extension attributes.
* @datastruct TYPE_EDIPARTYNAME=13 To Create EDI Party Name.
* @datastruct TYPE_NAMEASSIGNER=14 To Create EDI Party Name.
* @datastruct TYPE_PARTYNAME=15 To Create EDI Party Name.
* @datastruct TYPE_RFC822NAME=16 To set RFC822 Name.
* @datastruct TYPE_DNSNAME=17 To set DNS Name.
* @datastruct TYPE_IPADDRESS=18 To set IP Address.
* @datastruct TYPE_REGISTEREDID=19 To set RegisteredID.
* @datastruct TYPE_URL=20 To set URL.
* @datastruct TYPE_OTHERNAME=21 To create Other Name.
* @datastruct TYPE_IDENTIFIERVALUE=22 To create Other Name.
* @datastruct TYPE_ASSIGNER=23 To create Other Name.
* @datastruct TYPE_STRING=24 To create Other Name.
* @datastruct TYPE_ORADDRESS_SURNAME=25 To create the intrenal fields of personal Name and teletex personal
* Name structure.
* @datastruct TYPE_ORADDRESS_GENQUALIFIER=26 To create the intrenal fields of personal Name and teletex personal
* Name structure.
* @datastruct TYPE_ORADDRESS_INITIALS=27 To create the intrenal fields of personal Name and teletex personal
* Name structure.
* @datastruct TYPE_ORADDRESS_GIVENNAME=28 To create the intrenal fields of personal Name and teletex personal
* Name structure.
* @datastruct COMMON_NAME_ANY_ID=29 This is used to create the  CommonName strcuture of extension attribute.
* @datastruct TELETEX_COMMON_NAME_ANY_ID=30 This is used to create the  Teletex CommonName strcuture
* of extension attribute.
* @datastruct TELETEX_ORGANIZATION_NAME_ANY_ID=31 This is used to create the  Organization name strcuture
* of extension attribute
* @datastruct TELETEX_PERSONAL_NAME_ANY_ID=32 This is used to create the  Personal name strcuture of extension attribute.
* @datastruct TELETEX_ORGANIZATIONAL_UNIT_NAMES_ANY_ID=33 This is used to create the list of organization unit
* name of extension attribute.
* @datastruct PDS_NAME_ANY_ID=34 To create the PDS NAME.
* @datastruct PHYSICAL_DELIVERY_COUNTRY_NAME_ANY_ID=35 To create the Physical delivery country NAME.
* @datastruct POSTAL_CODE_ANY_ID=36 To create the postal address structure.
* @datastruct PHYSICAL_DELIVERY_OFFICE_NAME_ANY_ID=37 To create the physical delivery Office name.
* @datastruct PHYSICAL_DELIVERY_OFFICE_NUMBER_ANY_ID=38 To create the physical delivery Office number.
* @datastruct EXTENSION_OR_ADDRESS_COMPONENTS_ANY_ID=39 To create the extension OR Address structure.
* @datastruct PHYSICAL_DELIVERY_PERSONAL_NAME_ANY_ID=40 To create the physical delivery country name.
* @datastruct PHYSICAL_DELIVERY_ORGANIZATION_NAME_ANY_ID=41 To create the physical delivery organization name.
* @datastruct EXTENSION_PHYSICAL_DELIVERY_ADDRESS_COMPONENTS_ANY_ID=42 To create the physical delivery Address components.
* @datastruct UNFORMATTED_POSTAL_ADDRESS_ANY_ID=43 To create the unformatted postal address.
* @datastruct STREET_ADDRESS_ANY_ID=44 To create the street address.
* @datastruct POST_OFFICE_BOX_ADDRESS_ANY_ID=45 To create the post office box address.
* @datastruct POSTE_RESTANTE_ADDRESS_ANY_ID=46 To create the post restant address.
* @datastruct UNIQUE_POSTAL_NAME_ANY_ID=47 To create the unique postal name.
* @datastruct LOCAL_POSTAL_ATTRIBUTES_ANY_ID=48 To create the local postal attributes.
* @datastruct EXTENDED_NETWORK_ADDRESS_ANY_ID=49 To create the extended network address.
* @datastruct TERMINAL_TYPE_ANY_ID=50 To create the terminal type.
* @datastruct EXTNETWORKADDR_E1634ADDR=51 If e163-4-address is used.
* @datastruct EXTNETWORKADDR_PSAPADDR=52 If psap-address is used.
* @datastruct TYPE_ORGANIZATIONALUNITNAME_LIST=53 To create the organization unit name list.
* @datastruct TYPE_POLICYID=54 FOR CREATION OF CERTIFICATE POLICIES.
* @datastruct TYPE_USERNOTICE=55 To create UserNotice Qualifier.
* @datastruct TYPE_EXPLICITTEXT=56 To set the explicit text in Notice Reference.
* @datastruct TYPE_ORGTXT=57 To set the organization text in Notice Reference.
* @datastruct TYPE_NOTICENUMBERS=58 To set the notice numbers.
* @datastruct TYPE_CPS=59 To create CPS URI Qualifier.
*/
typedef enum enCommonType
{
 	/*TO CREATE ORADRESS STRUCTURE*/
	TYPE_ORADDRESS = 0,
    /*TO CREATE Built in standard attribute structure*/
	TYPE_BUILTINSTANDARDATTRIBUTE = 1,
	/*To set the country name*/
	TYPE_COUNTRYNAME  = 2,
	/*To set the adminisatration domain name*/
	TYPE_ADMINISTRATIONDOMAINNAME = 3,
	/*To set the network adderss*/
	TYPE_NETWORKADDRESS = 4,
	/*To set the terminal identifier*/
	TYPE_TERMINALIDENTIFIER = 5,
	/*To set the private domain name*/
	TYPE_PRIVATEDOMAINNAME = 6,
	/*To set the organization name*/
	TYPE_ORGANIZATIONNAME = 7,
	/*To set the numeric user identifier*/
	TYPE_NUMERICUSERIDENTIFIER = 8,
	/*To set the personal name*/
	TYPE_PERSONALNAME = 9,
	/*To set the organization name*/
	TYPE_ORGANIZATIONALUNITNAME = 10,
	/*To set the domain defined attribiutes*/
	TYPE_BUILTINDOMAINDEFINEDATTRIBUTE =11,
	/*To set the extension attributes*/
	TYPE_EXTENSIONATTRIBUTE = 12,



	/* To Create EDI Party Name*/
	TYPE_EDIPARTYNAME = 13,
	TYPE_NAMEASSIGNER = 14,
	TYPE_PARTYNAME = 15,

	/* To set RFC822 Name*/
	TYPE_RFC822NAME = 16,

	/* To set DNS Name*/
	TYPE_DNSNAME = 17,

	/* To set IP Address*/
	TYPE_IPADDRESS = 18,

	/* To set RegisteredID*/
	TYPE_REGISTEREDID = 19,

	/*To set URL*/
	TYPE_URL = 20,

	/*To create Other Name*/
	TYPE_OTHERNAME = 21,
	TYPE_IDENTIFIERVALUE = 22,
	TYPE_ASSIGNER = 23,
	TYPE_STRING = 24,
	/*To create the intrenal fields of personal Name and teletex personal Name structure*/
	TYPE_ORADDRESS_SURNAME = 25,
	TYPE_ORADDRESS_GENQUALIFIER = 26,
	TYPE_ORADDRESS_INITIALS = 27,
	TYPE_ORADDRESS_GIVENNAME = 28,
	/*This is used to create the  CommonName strcuture of extension attribute*/
	COMMON_NAME_ANY_ID = 29,
	/*This is used to create the  Teletex CommonName strcuture of extension attribute*/
    TELETEX_COMMON_NAME_ANY_ID = 30,
	/*This is used to create the  Organization name strcuture of extension attribute*/
    TELETEX_ORGANIZATION_NAME_ANY_ID = 31,
	/*This is used to create the  Personal name strcuture of extension attribute*/
    TELETEX_PERSONAL_NAME_ANY_ID =32 ,
	/*This is used to create the list of organization unit name of extension attribute*/
    TELETEX_ORGANIZATIONAL_UNIT_NAMES_ANY_ID = 33 ,
	/*To create the PDS NAME*/
    PDS_NAME_ANY_ID = 34,
	/*To create the Physical delivery country NAME*/
    PHYSICAL_DELIVERY_COUNTRY_NAME_ANY_ID = 35,
	/*To create the postal address structure*/
    POSTAL_CODE_ANY_ID =36,
	/*To create the physical delivery Office name */
    PHYSICAL_DELIVERY_OFFICE_NAME_ANY_ID = 37,
	/*To create the physical delivery Office number */
    PHYSICAL_DELIVERY_OFFICE_NUMBER_ANY_ID = 38,
	/*To create the extension OR Address structure*/
    EXTENSION_OR_ADDRESS_COMPONENTS_ANY_ID = 39,
	/*To create the physical delivery country name*/
    PHYSICAL_DELIVERY_PERSONAL_NAME_ANY_ID = 40,
	/*To create the physical delivery organization name*/
    PHYSICAL_DELIVERY_ORGANIZATION_NAME_ANY_ID =41,
	/*To create the physical delivery Address components*/
    EXTENSION_PHYSICAL_DELIVERY_ADDRESS_COMPONENTS_ANY_ID =42,
	/*To create the unformatted postal address*/
    UNFORMATTED_POSTAL_ADDRESS_ANY_ID  = 43,
	/*To create the street address*/
    STREET_ADDRESS_ANY_ID = 44,
	/*To create the post office box address*/
    POST_OFFICE_BOX_ADDRESS_ANY_ID = 45,
	/*To create the post restant address*/
    POSTE_RESTANTE_ADDRESS_ANY_ID = 46,
	/*To create the unique postal name*/
    UNIQUE_POSTAL_NAME_ANY_ID =47 ,
	/*To create the local postal attributes*/
    LOCAL_POSTAL_ATTRIBUTES_ANY_ID = 48,
	/*To create the extended network address*/
    EXTENDED_NETWORK_ADDRESS_ANY_ID = 49,
	/*To create the terminal type*/
    TERMINAL_TYPE_ANY_ID =50,
    /*If e163-4-address is used*/
	EXTNETWORKADDR_E1634ADDR = 51,
	/*If psap-address is used*/
    EXTNETWORKADDR_PSAPADDR = 52,

	/*To create the organization unit name list*/
	TYPE_ORGANIZATIONALUNITNAME_LIST = 53,


	/*FOR CREATION OF CERTIFICATE POLICIES */
	TYPE_POLICYID = 54,

	/*To create UserNotice Qualifier*/
	TYPE_USERNOTICE = 55 ,


	/* To set the explicit text in Notice Reference*/
	TYPE_EXPLICITTEXT = 56,

	/* To set the organization text in Notice Reference*/
	TYPE_ORGTXT = 57,

	/* To set the notice numbers*/
	TYPE_NOTICENUMBERS = 58 ,

	/*To create CPS URI Qualifier*/
	TYPE_CPS = 59

}X509_TYPE_E;


/*The below enum defines the differnt string formats that are supported*/
/**
* @defgroup X509_STRINGTYPE_E
* @ingroup x509Enums
* @par Prototype
* @code
* typedef enum enStringType
* {
*   X509_STRING_FORMAT_TELETEX   = 0,
*   X509_STRING_FORMAT_PRINTABLE = 1,
*   X509_STRING_FORMAT_UNIVERSAL = 2,
*   X509_STRING_FORMAT_UTF8      = 3,
*   X509_STRING_FORMAT_BMP       = 4,
*   X509_STRING_FORMAT_VISIBLE   = 5,
*   X509_STRING_FORMAT_NUMERIC   = 6,
*   X509_STRING_FORMAT_IA5       = 7
* } X509_STRINGTYPE_E;
* @endcode
*
* @datastruct X509_STRING_FORMAT_TELETEX=0 This is for TELETEX string.
* @datastruct X509_STRING_FORMAT_PRINTABLE=1 This is for PRINTABLE string.
* @datastruct X509_STRING_FORMAT_UNIVERSAL=2 This is for UNIVERSAL string.
* @datastruct X509_STRING_FORMAT_UTF8=3 This is for UTF8 string.
* @datastruct X509_STRING_FORMAT_BMP=4 This is for BMP string.
* @datastruct X509_STRING_FORMAT_VISIBLE=5 This is for VISIBLE string.
* @datastruct X509_STRING_FORMAT_NUMERIC=6 This is for NUMERIC string.
* @datastruct X509_STRING_FORMAT_IA5=7 This is for IA5 string.
*/
typedef enum enStringType
{
	/*This is for TELETEX string*/
     X509_STRING_FORMAT_TELETEX=0,
	 /*This is for PRINTABLE string*/
     X509_STRING_FORMAT_PRINTABLE = 1,
	 /*This is for UNIVERSAL string*/
	 X509_STRING_FORMAT_UNIVERSAL = 2,
	 /*This is for UTF8 string*/
	 X509_STRING_FORMAT_UTF8 = 3,
	 /*This is for BMP string*/
	 X509_STRING_FORMAT_BMP = 4,
	 /*This is for VISIBLE string*/
	 X509_STRING_FORMAT_VISIBLE = 5,
	 /*This is for NUMERIC string*/
	 X509_STRING_FORMAT_NUMERIC = 6,
	 /*This is for IA5 string*/
	 X509_STRING_FORMAT_IA5 = 7

}X509_STRINGTYPE_E;


/*The below enum indicates the name choice type*/
/**
* @defgroup X509_NAMECHOICE_E
* @ingroup x509Enums
* @par Prototype
* @code
* typedef enum enNameChoice
* {
*   X509_CRL_ISSUER_FULL_NAME     = 0,
*   X509_CRL_ISSUER_RELATIVE_NAME = 1
* } X509_NAMECHOICE_E;
* @endcode
*
* @datastruct X509_CRL_ISSUER_FULL_NAME=0 Choice used to specify that the input passed to X509_createDistPointName
* function is CRL Issuer Alternate Name.
* @datastruct X509_CRL_ISSUER_RELATIVE_NAME=1 Choice used to specify that the input passed to X509_createDistPointName
* function is Relative Distinguished Name of the CRL.
*/
typedef enum enNameChoice
{
	/* Choice used to specify that the input passed to X509_createDistPointName
		function is CRL Issuer Alternate Name*/
	X509_CRL_ISSUER_FULL_NAME = 0,
	/* Choice used to specify that the input passed to X509_createDistPointName
		function is Relative Distinguished Name of the CRL*/
	X509_CRL_ISSUER_RELATIVE_NAME = 1
}X509_NAMECHOICE_E;


/*The below enum indicates the choice of info acess*/
/**
* @defgroup X509_INFO_ACCESS_CHOICE_E
* @ingroup x509Enums
* @par Prototype
* @code
* typedef enum enInfoChoice
* {
*   X509_AUTHORITY_INFORMATION_ACCESS = 0,
*   X509_SUBJECT_INFO_ACCESS          = 1
* } X509_INFO_ACCESS_CHOICE_E;
* @endcode
*
* @datastruct X509_AUTHORITY_INFORMATION_ACCESS=0 Choice to create Authority Info Access Extension that is used in
* X509Extn_createInfoAccess.
* @datastruct X509_SUBJECT_INFO_ACCESS=1 Choice to create Subject Info Access Extension that is used in
* X509Extn_createInfoAccess.
*/
typedef enum enInfoChoice
{
    /* Choice to create Authority Info Access Extension that is used in
    X509Extn_createInfoAccess*/
    X509_AUTHORITY_INFORMATION_ACCESS = 0,

    /* Choice to create Subject Info Access Extension that is used in
    X509Extn_createInfoAccess*/
#ifndef IPSI_RESOLVE_SYMBOL_CONFLICTS
    X509_SUBJECT_INFO_ACCESS = 1
#else
    IPSI_X509_SUBJECT_INFO_ACCESS = 1
#endif

}X509_INFO_ACCESS_CHOICE_E;



/**
* @defgroup x509Structures
* @ingroup x509
* This section contains x509 Structures
*/

/*Structure for name creation*/

/**
* @defgroup X509_DN_ATTR_VALUE_S
* @ingroup x509Structures
* @par Prototype
* @code
* typedef struct stDNAttrValue
* {
*   SEC_UINT32 uiCID;
*   SEC_UCHAR *pucAttrValue;
*   SEC_UINT32 uiStringType;
* } X509_DN_ATTR_VALUE_S;
* @endcode
*
* @datastruct uiCID Integer value to the Attribute that has to be created.
* @datastruct pucAttrValue The String corresponding to the CID.
* @datastruct uiStringType The string type for representing the attribute value. The string type can be
* choosen using enum X509_STRINGTYPE_E.
*/

typedef struct stDNAttrValue
{
	/* Integer value to the Attribute that has to be created */
	SEC_UINT32 uiCID;
	/* The String corresponding to the CID */
	SEC_UCHAR *pucAttrValue;
	/* The string type for representing the attribute value.  The string type can be
	     choosen using enum X509_STRINGTYPE_E */
	SEC_UINT32 uiStringType;
}	X509_DN_ATTR_VALUE_S;


/*The below structure is used in the creation of common data that is internally used
in the creation of many extensions*/
/*During the creation of Common data struct it is neccessary to make sure
that either of the pucData or pDataList is present */
/*If both the fields,pointer to the string and list are present the struct  will not be created instead a NULL will be returned
back,the same if both the fields are absent,either of these fields should be present for the successfull creation*/
/*The type field needs to be provided by using the X509_TYPE_E enum*/
/*The String type field needs to be provided by using the X509_STRINGTYPE_E enum*/
/*It is recommended to provide the correct  string type recommended for X509_TYPE_E else will affect in the later
flow of api*/
/*The String type needs to be provided only for leaf nodes that is when the pucData field is set*/
/*The list provided as input should consist of only common nodes and can extend to any level*/
/*Memory for the simple field (pucData) will be alloted internally,i.e the simple char pointer
will be duplicated ,hence user can free the memory which he has sent to the create function  */
/*The list provided as input will not be dupicated there fore it is recommended that the
user should not free it once the structure is created.The list memory goes part of the
structure*/

/**
* @defgroup X509_COMMONDATA_S
* @ingroup x509Structures
* @par Prototype
* @code
* typedef struct stX509_CommonData
* {
*   X509_TYPE_E       enType;
*   SEC_UCHAR*        pucData;
*   SEC_List_S*       pDataList;
*   X509_STRINGTYPE_E enStringFormat;
* } X509_COMMONDATA_S;
* @endcode
*
* @datastruct enType Indicates the type of field.
* @datastruct pucData Indicates the pointer to Data string.
* @datastruct pDataList Indicates a pointer to the list of Common nodes.
* @datastruct enStringFormat Indicates the type of string.
*/
typedef struct stX509_CommonData
{
	/*Indicates the type of field*/
	X509_TYPE_E enType;
	/*Indicates the pointer to Data string*/
	SEC_UCHAR* pucData;
	/*Indicates a pointer to the list of Common nodes*/
	SEC_List_S*  pDataList;
	/*Indicates the type of string*/
	X509_STRINGTYPE_E enStringFormat;
}X509_COMMONDATA_S;

/*
Data structures of X509Certificate
*/


/** @defgroup x509Functions
* @ingroup x509
* This section contains the x509 Functions
*/



/**
* @defgroup X509CRL_encode
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509CRL_encode( X509_CRL_S* pstCRL, SEC_UINT32* pulLength);
* @endcode
* @par Purpose
* To encode a given X509 CRL to DER format.
* @par Description
* The function can be used to encode a given X509 CRL in DER format.
* All the mandatory fields should be present for encoding,else the encoding will not be successfull.If encoded successfully
* the DER code of the CRL will be returned back to the user in a character buffer.If not encoded succesfully SEC_NULL will
* be returned.
*
* @param[in] pstCRL The pointer to a structure that contains CRL with all mandatory fields [N/A]
* @param[out] pulLength Size of the encoded buffer [N/A]
*
* @retval SEC_UCHAR* Pointer to a buffer containing the encoded value of the CRL [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* If any one the mandatory field is absent [SEC_NULL|N/A]
* @retval SEC_UCHAR* If encode fails [SEC_NULL|N/A]
* @retval SEC_UCHAR* If buffer copy fails [SEC_NULL|N/A]
* @retval SEC_UCHAR* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded buffer, to free this memory
* application has to call the ipsi_free.
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*
*/

PSELINKDLL SEC_UCHAR* X509CRL_encode( X509_CRL_S*  pstCRL,
						   SEC_UINT32* pulLength);




/**
* @defgroup X509CRL_decode
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CRL_S* X509CRL_decode (SEC_UCHAR* pucEncodedCRL, SEC_UINT32 uiLength, SEC_UINT32* puiDLength);
* @endcode
* @par Purpose
* To decode the encoded CRL to form a X509_CRL_S structure.
* @par Description
* This method is used to decode the CRL which has been encoded in a DER format.
* The input to the method is the buffer containing the encoded CRL along with the length of the encoded buffer.
* Pointer to the decoded length has to be provided explicitly by the user.
* If any one of the pointer is null, SEC_NULL will be returned back to the user.
* If the input encoded length is zero, SEC_NULL is returned.
*
* @param[in] pucEncodedCRL The buffer containing the encoded CRL in DER format [N/A]
* @param[in] uiLength The size of the encoded buffer [N/A]
* @param[out] puiDLength Length of the decoded buffer [N/A]
*
* @retval X509_CRL_S* The CRL struct that is constructed after decoding [SEC_UCHAR*|N/A]
* @retval X509_CRL_S* If any of the input paramater is null [SEC_NULL|N/A]
* @retval X509_CRL_S* If memory allocation fails [SEC_NULL|N/A]
* @retval X509_CRL_S* If the decode fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the decoded CRL, to free this memory
* application has to call the X509CRL_free.
*
* @par Note
* N/A
*
*
* @par Related Topics
* N/A
*
*/


PSELINKDLL X509_CRL_S* X509CRL_decode(	SEC_UCHAR*  pucEncodedCRL,
							SEC_UINT32  uiLength,
							SEC_UINT32* puiDLength);


/**
* @defgroup X509CRL_verify
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_verify (SEC_PKEY_S* pstPublickey,
* const X509_CRL_S* pstCRL
* );
* @endcode
* @par Purpose
* To verify whether the CRL is signed by a trusted issuer.
* @par Description
* This method is used to verify whether the CRL is signed by a trusted issuer.
* The input to the method is the signed CRL.If the sign field is absent, an error code
* indicating the absence of the field will be returned back to the user.
* This method verifies the CRL and returns SEC_SUCCESS if the hash matches else returns verification failed error code.
* Internally encode will be called hence it is necessary that all the mandatory fields be present before verification.
* This method will decrypt the hash and generates new hash on the to be TBS structure and both the hashes will be compared.
* The public key needs to be extracted from the issuer certificate and passed to the method.
*
* @param[in] pstPublickey The public key of the issuer that needs to be used in signature verification process [N/A]
* @param[in] pstCRL The pointer to the CRL structure with all mandatory fields [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 If the digests matches and when the CRL is verified [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If verification fails [SEC_ERR_SIGN_VERIFY_FAILED|N/A]
* @retval SEC_UINT32 If any one of the mandatory fields are absent [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If encode fails [SEC_ERR_ENCODE_FAILED|N/A]
*
* @par Dependency
* x509.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*
*/

PSELINKDLL SEC_UINT32 X509CRL_verify(	SEC_PKEY_S* pstPublickey,
							const X509_CRL_S*  pstCRL);



/**
* @defgroup X509CRL_create
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CRL_S* X509CRL_create();
* @endcode
* @par Purpose
* To create an empty CRL structure.
* @par Description
* This method is used to create a empty CRL structure.Each fields need to be added or set independently.
* Only memory for CRL and TBSCRL will be alloted during this process.
* All the internal fields will be intialized to NULL during this creation.
*
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CRL_S* A pointer to the CRL structure that has just been created	[X509_CRL_S*|N/A]
* @retval X509_CRL_S* If the memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the created CRL, to free this memory
* application has to call the X509CRL_free.
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*
*
*/

PSELINKDLL X509_CRL_S* X509CRL_create(SEC_VOID);




/**
* @defgroup X509CRL_sign
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32  X509CRL_sign (SEC_PKEY_S* pstPrivateKey,
* X509_CRL_S* pstCRL
* );
* @endcode
* @par Purpose
* To sign a CRL using the given private key.
* @par Description
* This function signs the CRL by a given private key.The signature is actually calculated on the hash computed on tbsCRL
* structure. The calculated signature value is then assigned to the signature field.
* Intially the given CRL is assumed to have a null signature value,if present will be overwritten with a new value
* The CRL issuer has to use the private key to sign the CRL.It is also necessary to make sure that the
* all the valid extensions are present, if any invalid extension is present then signing will not be a performed.
* If an invalid version is present then too the CRL will not be signed.
* The hash algorithm required for signing will be fetched internally from the algorithm identifier.Therefore it is necessary
* for the user to set the appropriate algorithm identifier.
*
* @param[in] pstPrivateKey The private key that is used to sign the CRL [N/A]
* @param[out] pstCRL A pointer to  CRL structure with all mandatory fields that is updated with new signature if signed
* successfully [N/A]
*
* @retval SEC_UINT32 If the argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If encoding fails [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 If the signing is successful [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If it has an invalid version in the version field [SEC_ERR_INVALID_VERSION|N/A]
* @retval SEC_UINT32 If the signing operation failed [SEC_ERR_SIGNING_FAILED|N/A]
* @retval SEC_UINT32 If the given algorithm is not valid or if the key does not match with the given algorithm.
* [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_ERR_OID_MISMATCH If the signature algoritm field is different [N/A|N/A]
* @retval SEC_ERR_INVALID_EXTN If duplicates are there in the list or extension and entry extensions is not valid [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*   - For ALGID_SM2DSA signature, the pstPrivateKey should be a key pair i.e. public and private key should be
*      available in pstPrivateKey because public key will be used for the generation of ZA and private key
*      will be used for signature
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32  X509CRL_sign( SEC_PKEY_S* pstPrivateKey,
						  X509_CRL_S*  pstCRL );




/**
* @defgroup X509CRL_addExtn
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_addExtn (SEC_EXTN_S* pstExtension,
* X509_CRL_S* pstCRL
* );
* @endcode
* @par Purpose
* To add an extention to the extension list in a given CRL.
* @par Description
* This function adds an extension to the extension list in a given CRL.If the number of extensions in the list are already
* seven, then there cannot be anymore extensions added to the list.If an invalid extension is given then the extension will not
* be added to the list. If the add operation is successful then a success code will be returned.
* Trying to add an extension that is already in the list will not be successful. Extension can be created using the api
* X509_createExtn.The valid extensions that can be added are
* Authority Key Identifier
* Issuer Alternative Name
* CRL Number
* Freshest CRL
* Issuing Distribution Point
* Delta CRL Indicator
* Authority Information Access
* @param[in] pstExtension The extension that has to be added to the CRL [N/A]
* @param[out] pstCRL A reference to CRL structure in the memory [N/A]
* @retval SEC_UINT32 If the input paramater is null [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the add extension is done successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If the list add operation fails [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 If the extension is already present in the list [SEC_ERR_DUPLICATE_LIST_DATA|N/A]
* @retval SEC_UINT32 If the extension is invalid for CRL.This error code may be returned when criticality
* is not correct or extension data is not valid or it is not a valid CRL extension. [SEC_ERR_INVALID_EXTN|N/A]
* @par Dependency
* x509.h
* @par Note
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_addExtn( SEC_EXTN_S* pstExtension,
					         X509_CRL_S*  pstCRL);




/**
* @defgroup X509CRL_addCert
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_addCert (SEC_BIGINT_S* pstCertSNumber,
* DATETIME_S* pstRevocationDate,
* SEC_List_S* pExtension,
* X509_CRL_S* pstCRL
* );
* @endcode
* @par Purpose
* To add a new revoked certificate to the CRL.
* @par Description
* This method adds a new revoked certificate to the list of revoked certificates. If the certificate serial number is already
* in the list it cannot be added.Before the serial number is sent as input it needs to be converted to hexadecimal
* representation using the api SEC_cvtToBigInt.
* If the revocation date is not present then an appropriate return code will be returned to the user. Entry extension list is
* an optional parameter,if present it should be valid else an appropriate error code will be returned back to the user.
* If added succesfully SEC_SUCCESS will be returned. The certificate serial number should not have more than 20 Octets.
* If it has more than 20 octets an appropriate error code will be returned back to the user.
* Note this API adds the certificate successfully even if the extension list has zero nodes.
* The valid entry extensions that can be present in the entry extension list are :
* Reason Code
* Hold Instruction Code
* Invalidity Date
* Certificate Issuer
* @param[in] pstCertSNumber The certificate serial number that is revoked [N/A]
* @param[in] pstRevocationDate The date on which the certificate is revoked [N/A]
* @param[in] pExtension The entry extension list that is part of the revoked node [N/A]
* @param[out] pstCRL A reference to CRL structure in the memory,into which the new node has been added [N/A]
* @retval SEC_ERR_INVALID_ARG If the mandatory input paramater is NULL or serial number length is greater than 20 Octets.
* [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If the provided date input is invalid [SEC_ERR_INVALID_DATETIME|N/A]
* @retval SEC_UINT32 If the certificate already exists in the revoked list [SEC_ERR_DUPLICATE_LIST_DATA|N/A]
* @retval SEC_UINT32 If the entry extension list provided has more than 4 nodes [SEC_ERR_EXCESS_NODES|N/A]
* @retval SEC_UINT32 If the list add operation fails	[SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 If the entry extension is invalid for CRL
* This error code may be returned when criticality is not correct or extension data is not valid or it is not a valid CRL
* entry extension.
* It retuns SEC_ERR_INVALID_EXTN if invalidity date has UTC Time encoded field
* It retuns SEC_ERR_INVALID_EXTN if HOLD code has invalid OID
* It retuns SEC_ERR_INVALID_EXTN if REASONS has an invalid value attached to it. [SEC_ERR_INVALID_EXTN|N/A]
* @retval SEC_UINT32 If the revoked certificate serial number is added successfully [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* The ucUTCSign, ucUTCHour, ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function.
* Trying to add negative numbers like 0xff and 0xffff that result in same integer value will not be considered same and hence
* will be added sucessfully.
*
* @par Related Topics
* N/A
* 
* 
*/



PSELINKDLL SEC_UINT32 X509CRL_addCert (SEC_BIGINT_S*  pstCertSNumber,
						    DATETIME_S*    pstRevocationDate,
						    SEC_List_S*    pExtension,
						    X509_CRL_S*    pstCRL);




/**
* @defgroup X509CRL_setVersion
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_setVersion( X509_CRLVERSION_E enVersion,
* X509_CRL_S* pstCRL
* );
* @endcode
* @par Purpose
* To set the version of the CRL.
* @par Description
* This function is used to set the version of the CRL.For setting V1 CRL and if it is already V2 the memory allocated for V2
* will be freed and SEC_SUCCESS will be returned.
* For a V2 CRL it allocates memory and sets the version.
* Default version is 1.It is better to set the appropraiate version based on the existence of extensions
* An invalid version will not allow the user to sign the CRL.
* Providing an invalid extension will result in an appropriate error code.
* Two versions that are valid are X509_CRL_VERSION1 and X509_CRL_VERSION2
* For a V2 CRL the value present in the version field is 1.
* @param[in] enVersion The version of the CRL that needs be set [N/A]
* @param[out] pstCRL A reference to CRL structure in memory [N/A]
* @retval SEC_UINT32 If the version is set successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input is a invalid version [SEC_ERR_INVALID_VERSION|N/A]
* @retval SEC_UINT32 If malloc fails [SEC_ERR_MALLOC_FAIL|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_setVersion( X509_CRLVERSION_E enVersion,X509_CRL_S* pstCRL);




/**
* @defgroup X509CRL_setNextUpdate
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_setNextUpdate(DATETIME_S*   pstnextUpdate,                          	
*  X509_CRL_S*    pstCRL
* );
* @endcode
* @par Purpose
* To set the next update field in the CRL.
* @par Description
* This function is used to set the optional next update field to the CRL.
* The Next Update field indicates when the next CRL will be Issued. If an invalid date is given the next update field will not
* be added. If added successfully an appropriate success code will be returned. The user is allowed to set any date but needs
* to ensure its value with ThisUpdate. If ThisUpdate is greater than NextUpdate condition arises then CRL will not be signed.
* For years through 2049, nextUpdate will be encoded in UTCTime format.
* GeneralizedTime encoding will be used for dates in the year 2050 or later.This is an optional field.
* @param[in] pstnextUpdate The time indicating when the next CRL will be issued [N/A]
* @param[out] pstCRL A reference to CRL structure in the memory [N/A]
* @retval SEC_UINT32 If the input argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory alloction fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If the given date is invalid [SEC_ERR_INVALID_DATETIME|N/A]
* @retval SEC_UINT32 If the time conversion fails [SEC_ERR_TIME_CONVERT|N/A]
* @retval SEC_UINT32 If the set date happens successfully [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* The ucUTCSign,ucUTCHour,ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function.Dates with year
* less than 1970 will not be considered valid.
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_setNextUpdate(DATETIME_S*   pstnextUpdate,
                            	 X509_CRL_S*    pstCRL);




/**
* @defgroup X509CRLExtn_setDPToIDP
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRLExtn_setDPToIDP(X509_DPN_S* pstDistributionPoint,
* X509_IDP_S* pstIssuingDPoint
* );
* @endcode
* @par Purpose
* To set the Distribution point to IDP structure.
* @par Description
* This function allows to sets the optional DistributionPoint structure to the existing IDP structure.
* If any one of the input pointer is NULL an appropraite error code is returned.
* The Distribution point structure can be created using the API X509Extn_createDP.
* If the old structure exists then the already existing one will be freed and replaced by a new one.
* The Issuing distribution point structure can be created using the api X509CRLExtn_createIDP
* @param[in] pstDistributionPoint The pointer to the structure that contains the distribution point details [N/A]
* @param[out] pstIssuingDPoint The pointer to the IDP structure in memory into which
* the DistributionPoint details need to be set [N/A]
* @retval SEC_UINT32 If the input argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the memory allocation fails during duplication [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If the set operation is sucessfull [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 X509CRLExtn_setDPToIDP(X509_DPN_S* pstDistributionPoint,
								  X509_IDP_S* pstIssuingDPoint);




/**
* @defgroup X509CRLExtn_setReasonsToIDP
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRLExtn_setReasonsToIDP(SEC_UINT32 uiReasonFlags,
* X509_IDP_S* pstIDP
* );
* @endcode
* @par Purpose
* To add reason flags to the X509 Information Distribution Point structure.
* @par Description
* This function allows to add the optional reason flags to the X509_IDP_S structure.
* This field should be set by using the revocation macros. The reasons can be any of the below.
* Each of these can be Bitwise ored to indicate more than one reasons. The Issuing distribution point structure can be created
* using the api	X509CRLExtn_createIDP. If the reasons already exist the one existing will be freed and replaced by the
* new valid reasons.The valid reasons that need to be set are given below
* X509_REVOKED_UNUSED_CERT
* X509_REVOKED_KEY_COMPROMISE
* X509_REVOKED_CA_COMPROMISE
* X509_REVOKED_AFFILIATION_CHANGED
* X509_REVOKED_SUPER_SEDED
* X509_REVOKED_CESSATION_OF_OPER
* X509_REVOKED_CERT_HOLD
* X509_REVOKED_PRIVILEGE_WITHDRAWN
* X509_REVOKED_AA_COMPROMISE
* @param[in] uiReasonFlags The different revocation reasons for which the revoked certificates are available. [N/A]
* @param[out] pstIDP The structure that has been set with the given reasons. [N/A]
* @retval SEC_UINT32 If the input argunment is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If the function is executed successfully [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509CRLExtn_setReasonsToIDP(SEC_UINT32 uiReasonFlags,
                                       X509_IDP_S* pstIDP);





/**
* @defgroup X509CRL_setThisUpdate
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_setThisUpdate (DATETIME_S* pstThisUpdate,
* X509_CRL_S*  pstCRL
* );
* @endcode
* @par Purpose
* To set the ThisUpdate field of the CRL.
* @par Description
* This function is used to set the ThisUpdate field of the CRL. ThisUpdate field indicates when the CRL was issued.
* Since it is a mandatory field it has to be present in any valid CRL.
* If the given input Date structure is invalid, an appropriate error message will be returned.
* The date provided can be any valid Date but the issuer needs to ensure that ThisUpdate will not be greater than
* NextUpdate.If any such condition occurs then CRL will not be signed.
* For years till 2049, nextUpdate will be encoded in UTCTime format.
* GeneralizedTime encoding will be used for dates of year 2050 or later.
* @param[in] pstThisUpdate The valid Date indicating when the CRL was issued [N/A]
* @param[out] pstCRL A reference to CRL structure in the memory. [N/A]
* @retval SEC_UINT32 If the input argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 It the time converion fails [SEC_ERR_TIME_CONVERT|N/A]
* @retval SEC_UINT32 If the given date is invalid	[SEC_ERR_INVALID_DATETIME|N/A]
* @retval SEC_UINT32 If the this update is set successfully [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* The ucUTCSign,ucUTCHour,ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function.
* Dates with year less than 1970 will not be considered valid.
*
* @par Related Topics
* N/A
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_setThisUpdate(DATETIME_S*  pstThisUpdate,
        						 X509_CRL_S*  pstCRL);


/**
* @defgroup X509CRL_setIssuer
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_setIssuer(SEC_NAME_S* pstIssuer,
* X509_CRL_S* pstCRL
* );
* @endcode
* @par Purpose
* To set issuer name field of an existing CRL.
* @par Description
* This function is used to set the mandatory issuer name field to the existing CRL.
* This field indicates the name of the CRL issuer.The input name provided needs to be x509 name.
* If the name structure is null an appropriate error code will be returned.Internally the given strucure will be
* duplicated and added to the struct.If the name structure already exists the old structure will be freed and replaced by a
* new one.The name structure can be created using the API X509_createDN.
* @param[in] pstIssuer Name of the issuer who has issued the CRL
* @param[out] pstCRL A reference to CRL structure in the memory.
* @retval SEC_UINT32 If the input argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the memory allocation fails during duplication. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If the issuer name is set successfully [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_setIssuer(SEC_NAME_S*  pstIssuer,
							 X509_CRL_S*   pstCRL);




/**
* @defgroup X509CRL_setSignAlgId
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_setSignAlgId(SEC_ALG_IDENTIFIER_S* pstSignatureID,
* X509_CRL_S* pstCRL
* );
* @endcode
* @par Purpose
* To set the Signature algorithm field of the CRL.
* @par Description
* This function is used to set the mandatory Signature algorithm field to  the CRL .
* This field contains the algorithm identifier for the algorithm used to sign the CRL.
* If a NULL structure is given as input an appropriate error code will be returned to the user.
* Internally the structure will be duplicated and added to the CRL.
* If the structure already exists the old struct would be freed and replaced by a new one.
* This function sets both Signature algorithm fields of CRL.
* The algorithm structure can be created using the api X509_createAlgId.
* The valid algorithms that can be set are:
* ALGID_MD5WITHRSA
* ALGID_SHA1WITHRSA
* ALGID_DSA_WITH_SHA1
* ALGID_DSAWITHSHA1_2
* ALGID_ECDSA_WITH_SHA1
* ALGID_ECDSA_WITH_SHA224
* ALGID_ECDSA_WITH_SHA256
* ALGID_ECDSA_WITH_SHA384
* ALGID_ECDSA_WITH_SHA512
* ALGID_SHA256WITHRSAENCRYPTION
* ALGID_SHA384WITHRSAENCRYPTION
* ALGID_SHA512WITHRSAENCRYPTION
* @param[in] pstSignatureID The structure that indicates the algorithm used to sign the CRL. [N/A]
* @param[out] pstCRL A reference to CRL structure in the memory. [N/A]
* @retval SEC_UINT32 If the input argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the memory allocation fails during duplication. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If the function is executed successfully [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/



PSELINKDLL SEC_UINT32 X509CRL_setSignAlgId(SEC_ALG_IDENTIFIER_S*  pstSignatureID,
								 X509_CRL_S*  pstCRL);




/**
* @defgroup X509CRLExtn_getRevReason
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509CRLExtn_getRevReason(SEC_List_S*  pCRLEEList );
* @endcode
* @par Purpose
* To fetch the reason for revocation from the CRL entry extention list.
* @par Description
* This function fetches the revocation reason from the CRL entry Extension List.
* The List from which the value needs to be fetched has to be provided as input.
* The ReasonCode extension is a CRL entry extension that identifies the reason for the certificate revocation.
* Since reason is a part of entry extensions, the list for a given certificate serial number can be
* feched using X509CRL_getEntryExtns.The revocation reason returned can be one of the below
* CRL_UNSPECIFIED
* CRL_KEY_COMPROMISE
* CRL_CA_COMPROMISE
* CRL_AFFILIATION_CHANGED
* CRL_SUPERSEEDED
* CRL_CESSATION_OPERATION
* CRL_CERTIFICATE_HOLD
* CRL_REM_FROM_CRL
* CRL_PRIV_WITHDRAWN
* CRL_AUTH_ATTR_COMPROMISE
* @param[in] pCRLEEList A pointer to a list containing all the entry extension for a given certificate [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 If the input argument is null [-1|N/A]
* @retval SEC_INT32 If the requested data is not available [-1|N/A]
* @retval SEC_INT32 Reason of revocation [SEC_INT32|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509CRLExtn_getRevReason(SEC_List_S*  pCRLEEList );




/**
* @defgroup X509CRLExtn_getHIC
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32  X509CRLExtn_getHIC( SEC_List_S* pCRLEEList );
* @endcode
* @par Purpose
* To fetch the HIC from a the CRL entry extensions list.
* @par Description
* This function fetches the Hold Instruction Code from a list containing the entry extensions.
* The HoldInstructionCode extension is a CRL entry extension that allows an instruction code identifying how to process a
* certificate that has a reason code of CertificateHold.
* The List from which the value needs to be fetched has to be provided as a mandatory field.
* Since HIC is a part of entry extensions,the list for a given certificate can be feched using the method
* X509CRL_getEntryExtns.The Hold code returned is a CID  of some valid Hold OID.
* The value returned should be one of the below
* CID_HOLDINSTRUCTION_NONE
* CID_HOLDINSTRUCTION_CALLISSUER
* CID_HOLDINSTRUCTION_REJECT
* @param[in] pCRLEEList A pointer to a list containing all the extension for a given certificate [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 The hold instruction code that will be returned [SEC_INT32|N/A]
* @retval SEC_INT32 If the arguments is missing [-1|N/A]
* @retval SEC_INT32 If the requested data is not available [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32  X509CRLExtn_getHIC( SEC_List_S* pCRLEEList );




/**
* @defgroup X509CRLExtn_extractInvalidityDate
* @ingroup x509Functions
* @par Prototype
* @code
* DATETIME_S* X509CRLExtn_extractInvalidityDate (SEC_List_S* pCRLEEList);
* @endcode
* @par Purpose
* To extract the invalidity date from CRL list.
* @par Description
* This function extracts the InvalidityDate field from a given CRL.
* The InvalidityDate extension is a CRL entry extension that identifies the date at which it is known or suspected that a
* private key was compromised.The extension is always non-critical.
* The List from which the value needs to be fetched has to be provided as a mandatory field.
* Since Invalidity Date is a part of entry extensions,the list for a given certificate can be fetched using
* X509CRL_getEntryExtns. The memory consisting of the invalidity date needs to be freed explicitly by the user.
* If the list is null,SEC_NULL will be returned back to the user.
* @param[in] pCRLEEList A pointer to a list containing all the entry extension for a given certificate [N/A]
* @param[out] N/A N/A [N/A]
* @retval DATETIME_S* The date on which the certificate is submitted for revocaton [N/A|N/A]
* @retval DATETIME_S* If the input argument is null or requested data is not available [SEC_NULL|N/A]
* @retval DATETIME_S* If the Date is encoded in UTC time format or Date is corrupted [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the DATETIME_S structure, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* The ucUTCSign,ucUTCHour,ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S*  X509CRLExtn_extractInvalidityDate(SEC_List_S* pCRLEEList);




/**
* @defgroup X509CRLExtn_extractCertIssuer
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509CRLExtn_extractCertIssuer(SEC_List_S* pCRLEEList);
* @endcode
* @par Purpose
* To extract the certificate issuer field from a given CRL entry extension list.
* @par Description
* This function extracts the certificate issuer field from a given CRL entry extension list.
* This entry extension is present when the CRL is issued by some third party.
* This indicates the name of the Certificate issuer.
* The SEC_List_S from which the value needs to be fetched has to be provided as a mandatory field.
* Since reason is a part of entry extensions, the list for a given certificate can be fetched using X509CRL_getEntryExtns.
* The return value list will be of General Name structures.
* The certificate issuer list needs to be freed explicitly by the user
* @param[in] pCRLEEList A pointer to a list containing all the entry extensions for a given certificate [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* The certificate issuer list that contains the issuer name.
* The list contains the General Name structures. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input data is null or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* On success this function will allocate the memory for the certissuer list
* (the list may contain one or more entries) to free this memory 
* application has to call X509_freeGeneralNameList
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* X509CRLExtn_extractCertIssuer(SEC_List_S*  pCRLEEList);




/**
* @defgroup X509CRL_extractThisUpdate
* @ingroup x509Functions
* @par Prototype
* @code
* DATETIME_S* X509CRL_extractThisUpdate(const X509_CRL_S* pstCRL);
* @endcode
* @par Purpose
* To extract the ThisUpdate field from a given CRL.
* @par Description
* This function extracts the ThisUpdate field from a given CRL.
* ThisUpdate indicates the date and time when the revocation list was published.
* The pointer i.e returned needs to be freed explicitly by the user.
* If the ThisUpdate field is not available, SEC_NULL will be returned.
* Internally the Date will be fetched from the Time structure.
* @param[in] pstCRL A reference pointer to CRL structure in the memory. [N/A]
* @param[out] N/A N/A [N/A]
* @retval DATETIME_S* It is a pointer to a structure containing the update field from the CRLlist [DATETIME_S*|N/A]
* @retval DATETIME_S* If the requested data is not available or input param is null or Time conversion fails. [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the DATETIME_S structure, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* X509CRL_extractThisUpdate(const X509_CRL_S* pstCRL);




/**
* @defgroup X509CRL_getSignAlgorithmID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_ALG_IDENTIFIER_S*  X509CRL_getSignAlgorithmID(const X509_CRL_S* pstCRL );
* @endcode
* @par Purpose
* To fetch the algorithm identifier used to sign the CRL.
* @par Description
* This function is used to fetch the algorithm Identifier i.e used to sign the CRL.
* If the algorithm field is not available a NULL will be returned back to the user.
* The return value is a pointer to the signature algorithm structure in CRL.
* @param[in] pstCRL A reference to CRL structure in the memory. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_ALG_IDENTIFIER_S* The pointer to the structure that indicates the algorithm used to sign the CRL
* [SEC_ALG_IDENTIFIER_S*|N/A]
* @retval SEC_ALG_IDENTIFIER_S* If the input parameter is NULL or the requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_ALG_IDENTIFIER_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ALG_IDENTIFIER_S*  X509CRL_getSignAlgorithmID(const X509_CRL_S* pstCRL );




/**
* @defgroup X509CRL_getIssuer
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_NAME_S* X509CRL_getIssuer(const X509_CRL_S* pstCRL );
* @endcode
* @par Purpose
* To fetch the Issuer name from a given CRL.
* @par Description
* This function fetches the Issuer name from a given CRL. If the name field is not available SEC_NULL will be returned.
* The return value is a pointer to the already existing name structure in CRL.
* @param[in] pstCRL A reference to CRL structure in the memory. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_NAME_S* A pointer to the Name structure containing the issuer name [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* If the input param is null or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_NAME_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_NAME_S* X509CRL_getIssuer(const X509_CRL_S* pstCRL );




/**
* @defgroup X509CRL_getVersion
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509CRL_getVersion (const X509_CRL_S* pstCRL);
* @endcode
* @par Purpose
* To fetch the version of the given CRL.
* @par Description
* This function fetches the Version of the given CRL.
* If a 0 is retured it is a V1 CRL. If 1 is returned it is a V2 CRL
* @param[in] pstCRL A reference to CRL structure in the memory. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 If the argument is missing. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 for v1 CRL [0|N/A]
* @retval SEC_INT32 for v2 CRL [1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509CRL_getVersion(const X509_CRL_S* pstCRL);




/**
* @defgroup X509CRL_extractNextUpdate
* @ingroup x509Functions
* @par Prototype
* @code
* DATETIME_S* X509CRL_extractNextUpdate(const X509_CRL_S* pstCRL);
* @endcode
* @par Purpose
* To extract the NextUpdate field from a given CRL.
* @par Description
* This function extracts the NextUpdate field from a given CRL.
* It indicates the time by which the next revocation list will be issued.
* Since nextdate is a optional field it can be fetched only in case it is already added to the structure.
* The pointer that is returned back needs to be freed explicitly by the user.
* @param[in] pstCRL A reference pointer to CRL structure in the memory. [N/A]
* @param[out] N/A N/A [N/A]
* @retval DATETIME_S* A pointer to a structure containing the extracted next update field from the CRL. [DATETIME_S*|N/A]
* @retval DATETIME_S* If the input is NULL or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the DATETIME_S structure, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* X509CRL_extractNextUpdate(const X509_CRL_S* pstCRL);




/**
* @defgroup X509CRL_getRevokedCertificates
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509CRL_getRevokedCertificates(const X509_CRL_S* pstCRL);
* @endcode
* @par Purpose
* To get a list of revoked certificates from a given CRL.
* @par Description
* This function returns a pointer to the list of revoked certificates from the given input CRL.
* Since  revoked certificate list is a optional field it can be fetched only in case it is already added to the CRL.
* @param[in] pstCRL A reference to CRL structure in the memory. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Pointer to a list of revoked nodes. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_List_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* X509CRL_getRevokedCertificates(const X509_CRL_S* pstCRL);




/**
* @defgroup X509CRL_getExtns
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509CRL_getExtns(const X509_CRL_S* pstCRL);
* @endcode
* @par Purpose
* To get the list of extension from a given CRL.
* @par Description
* This function returns a pointer to the extension list in a given CRL.
* Since CRL extensions is a optional field it can be fetched only in case it is already added to the CRL structure.
* @param[in] pstCRL pointer to the CRL structure in the memory. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* A pointer to a list containing all the CRL extensions [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_List_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* X509CRL_getExtns(const X509_CRL_S* pstCRL);




/**
* @defgroup X509CRL_getEntryExtns
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S*  X509CRL_getEntryExtns( const X509_CRL_S*  pstCRL,
* SEC_BIGINT_S* pstSNumber
* );
* @endcode
* @par Purpose
* To get the list of entry extensions for a given certificate from a given CRL.
* @par Description
* This function returns a pointer to the Entry Extension list for a given Certificate serial number from a given CRL.
* Since  CRL entry extensions is a optional field of a revoked node,it can be fetched if it is a part of the revoked node.
* If the list is not available then a NULL is returned.
* @param[in] pstCRL A reference to CRL structure in the memory. [N/A]
* @param[in] pstSNumber Serial number that needs to be searched [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* A pointer to a structure containing all the entry extensions for a given Serial number * [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input parameter is NULL or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_List_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S*  X509CRL_getEntryExtns( const X509_CRL_S*  pstCRL,
									SEC_BIGINT_S* pstSNumber);



/**
* @defgroup X509CRLExtn_extractCRLNumber
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BIGINT_S* X509CRLExtn_extractCRLNumber(SEC_List_S* pCRLEList);
* @endcode
* @par Purpose
* To fetch the CRL Number from the given CRL extension list.
* @par Description
* The function fetches the CRLNumber from the given CRL extension list.
* The CRLNumber extension is a CRL extension that contains a sequence number that allows a CRL user to determine whether all
* CRLs prior to the current CRL have been seen. The sequence number increases sequentially.The extension is always marked
* non-critical. Since CRL number is a part of extension list it can be fetched only if the Extension list exists.
* If the CRL Number is returned, the memory for the structure needs to be freed explicitly by the user.
* The List from which the value needs to be fetched has to be provided as a mandatory field.
* The pointer to the list is obtained using X509CRL_getExtns.
* @param[in] pCRLEList A pointer to a list containing all the extensions [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BIGINT_S* The CRL number of a given CRL present as part of the extension [SEC_BIGINT_S*|N/A]
* @retval SEC_BIGINT_S* If the input is NULL or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_BIGINT_S structure, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BIGINT_S* X509CRLExtn_extractCRLNumber(SEC_List_S* pCRLEList);




/**
* @defgroup X509CRLExtn_extractIDP
* @ingroup x509Functions
* @par Prototype
* @code
* X509_IDP_S* X509CRLExtn_extractIDP(SEC_List_S* pCRLEList);
* @endcode
* @par Purpose
* To fetch the IDP from a given CRL extension list.
* @par Description
* The function extracts the Issuing distribution point from a given extension list.
* The Issuing Distribution Point extension is a critical CRL extension.
* Since IDP is a part of CRL extension list it can be fetched only if the Extensions exist.
* The pointer to the extension list is obtained using X509CRL_getExtns.
* If the IDP structure is returned, the memory for the struct needs to be freed explicitly by the user.
* If the list is not available a NULL will be returned back to the user.
* The CRL extension list can be obtained using the API X509CRL_getExtns.
* @param[in] pCRLEList A pointer to a list containing all the extensions [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_IDP_S* Pointer to the structure that has been retrieved.
* IDP indicates the point in which the CRL is available along with its properties [X509_IDP_S*|N/A]
* @retval X509_IDP_S* If the input is NULL or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_IDP_S structure, to free this memory
* application has to call the X509CRLExtn_freeIDP.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_IDP_S* X509CRLExtn_extractIDP(SEC_List_S* pCRLEList);



/**
* @defgroup X509CRL_getExtnCount
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509CRL_getExtnCount(const X509_CRL_S* pstCRL );
* @endcode
* @par Purpose
* To get the count of the extensions available in the CRL.
* @par Description
* This function returns the count of extensions available in CRL.
* If the extension list is not available it retuns a appropriate error code.
* @param[in] pstCRL A pointer to the CRL structure in memory. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 If the requested data is not available [-1|N/A]
* @retval SEC_INT32 If the input data is null [-1|N/A]
* @retval SEC_INT32 The number of extensions present [SEC_INT32|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_INT32 X509CRL_getExtnCount(const X509_CRL_S* pstCRL );




/**
* @defgroup X509CRLExtn_extractDeltaCRLIndicator
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BIGINT_S* X509CRLExtn_extractDeltaCRLIndicator(SEC_List_S* pCRLEList);
* @endcode
* @par Purpose
* To extract the DeltaCRLindicator from a given CRL extension list.
* @par Description
* The function extracts the DeltaCRLindicator from a given CRL extension list.
* The Delta CRL Indicator extension is a critical CRL extension that identifies this CRL as a delta CRL rather than a base CRL.
* The corresponding base CRL is identified using a CRL number issued by the Certification Authority.
* Since delta CRL indicator is a part of  CRL extension, the list can be fetched only if the Extension exists.
* If the pointer is returned, memory for the returned structure needs to be freed explicitly by the user.
* If the extension is not available SEC_NULL will be returned.
* The CRL extension list can be obtained using the API X509CRL_getExtns.
* @param[in] pCRLEList Pointer to the List of CRL extensions [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BIGINT_S* An bignumber structure indicating the base CRL number. [SEC_BIGINT_S*|N/A]
* @retval SEC_BIGINT_S* If the input param is null or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_BIGINT_S structure, to free this memory
* application has to call the ipsi_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BIGINT_S* X509CRLExtn_extractDeltaCRLIndicator(SEC_List_S* pCRLEList);




/**
* @defgroup X509CRLExtn_extractFreshestCRLIndicator
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509CRLExtn_extractFreshestCRLIndicator(SEC_List_S* pCRLEList);
* @endcode
* @par Purpose
* To extract the freshestCRL indicator from a given CRL Extension list.
*
* @par Description
* The function extracts the freshestCRL indicator from a given CRL Extension list.The Freshest CRL extension is a
* certificate extension that identifies the  freshest CRL that should be used when checking the revocation status of
* the certificate.Since Freshest CRL indicator is a part of CRL xtension list,it can be fetched only if extensions exist.
* If the extension is not available then a NULL will be returned.If the pointer is returned the memory needs to be freed
* explicitly by the user.The CRL extension list can be obtained using the API  X509CRL_getExtns.
*
* @param[in] pCRLEList A pointer to a list of CRL extensions [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* An list of the CRL distribution points [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input param is null or requested data is not available [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List_S structure, to free this memory
* application has to call the X509Extn_freeCRLDistPoint.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* X509CRLExtn_extractFreshestCRLIndicator(SEC_List_S* pCRLEList);



/**
* @defgroup X509CRL_queryCertStatus
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509CRL_queryCertStatus(  const X509_CRL_S*  pstCRL,
* SEC_BIGINT_S* pstCertsnum,
* DATETIME_S* pstRevokedDate);
* @endcode
* @par Purpose
* To check whether a given certificate is present in the CRL or not.
* @par Description
* Given the certificate serial number this method finds if the given certificate is present in the CRL structure.
* It searches the CRL and based on the availability of the serial number it returns
* the status and the revocation date as the output parameter.
* Memory for output parametr revocation date needs to be provided by the user.
* If Cert is revoked and revocation type is not available then X509_CERT_REVOKED
* If the revocation date is present and return value is X509_CERT_REVOKED then the certificate is revoked,
* but the reason is not present.
* If the revocation date value is NULL and return value is X509_CERT_REVOKED then there is failure in time
* conversion but the certificate is revoked.
* If X509_CERT_UNREVOKED is returned then the cert is not revoked.
* @param[in] pstCRL A pointer to the CRL structure in memory. [N/A]
* @param[in] pstCertsnum The certificate serial number whose status has to be found in the CRL. [N/A]
* @param[out] pstRevokedDate The time during which the cert is revoked,if
* values not set then cert is not revoked or mandatory date not available [N/A]
* @retval SEC_INT32 If the argument is missing [-1|N/A]
* @retval SEC_INT32 If the given input serial number has more than 20 octets [-1|N/A]
* @retval SEC_INT32 If the cert is revoked and reason is not available [X509_CERT_REVOKED|N/A]
* @retval SEC_INT32 If the cert if not revoked [X509_CERT_UNREVOKED|N/A]
* @retval SEC_INT32 Reason of revocation [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* The ucUTCSign,ucUTCHour,ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_INT32 X509CRL_queryCertStatus(  const X509_CRL_S*  pstCRL,
								    SEC_BIGINT_S*     pstCertsnum,
								    DATETIME_S* pstRevokedDate);



/**
* @defgroup X509_queryIndirectCrlCertStatus
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_queryIndirectCrlCertStatus(  const X509_CRL_S*  pstCRL,
* SEC_BIGINT_S* pstCertsnum,
* DATETIME_S* pstRevokedDate,
* SEC_NAME_S **dpstIssuerName);
* @endcode
* @par Purpose
* To check whether a given certificate is present in the indirect CRL or not .
* @par Description
* Given the certificate serial number this method finds if the given certificate is present in the indirect CRL structure.
* It searches the CRL and based on the availability of the serial number it returns
* the status,the revocation date and the cert issuer as the output parameter.
* Memory for output parameter revocation date needs to be provided by the user.
* If Cert is revoked and revocation type is not available then X509_CERT_REVOKED
* If the revocation date is present and return value is X509_CERT_REVOKED then the certificate is revoked,
* but the reason is not present.
* If the revocation date value is NULL and return value is X509_CERT_REVOKED then there is failure in time
* conversion but the certificate is revoked.
* If X509_CERT_UNREVOKED is returned then the cert is not revoked.
* @param[in] pstCRL A pointer to the CRL structure in memory. [N/A]
* @param[in] pstCertsnum The certificate serial number whose status has to be found in the CRL. [N/A]
* @param[out] dpstIssuerName The time during which the cert is revoked,if
* values not set then cert is not revoked or mandatory date not available [N/A]
* @param[out] pstRevokedDate The cert issuer[N/A]
* @retval SEC_INT32 If the argument is missing [-1|N/A]
* @retval SEC_INT32 If the given input serial number has more than 20 octets [-1|N/A]
* @retval SEC_INT32 If the cert is revoked and reason is not available [X509_CERT_REVOKED|N/A]
* @retval SEC_INT32 If the cert if not revoked [X509_CERT_UNREVOKED|N/A]
* @retval SEC_INT32 Reason of revocation [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* The ucUTCSign,ucUTCHour,ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function
*
* @par Related Topics
* N/A
* 
* 
*/
PSELINKDLL SEC_INT32 X509_queryIndirectCrlCertStatus(  const X509_CRL_S*  pstCRL,
								    SEC_BIGINT_S*     pstCertsnum,
								    DATETIME_S* pstRevokedDate,
                                    SEC_NAME_S **dpstIssuerName);


/**
* @defgroup X509CRL_delCert
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32  X509CRL_delCert (SEC_BIGINT_S* pstSNumber,
* SEC_List_S* pRevokedList
* );
* @endcode
* @par Purpose
* To delete a given certificate serial number from the CRL.
* @par Description
* This function deletes a certificate serial number from a given CRL.
* If the certificate is deleted successfully then a success code will be returned
* else an appropriate error code will be returned.
* During this process all the memory assigned for the revoked certificate will be freed completely.
* The revoked list can be obtained using the API X509CRL_getRevokedCertificates.
* @param[in] pstSNumber The certificate serial number that has to be removed from the CRL [N/A]
* @param[out] pRevokedList A reference to Revoked structure list in memory. [N/A]
* @retval SEC_UINT32 If the input argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the certificate serial number is deleted successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If the requested serial number is not available [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32  X509CRL_delCert(SEC_BIGINT_S*  pstSNumber,
							SEC_List_S*    pRevokedList);


/**
* @defgroup X509CRL_validateDate
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_validateDate (const X509_CRL_S* pstCRL,
* DATETIME_S* pstDate
* );
* @endcode
* @par Purpose
* To check for the validity of a given CRL, in terms of date.
* @par Description
* This method is used to validate the given CRL. The input to the method is the pointer to CRL structure along with the Date
* which needs to be validated on a given CRL.This method will compare the given date with the one available in the CRL and
* returns the appropriate error code to ensure the validity of CRL .
* @param[in] pstCRL A pointer to the CRL structure in memory. [N/A]
* @param[in] pstDate The date that needs to be compared. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_UINT32 If the input argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the CRL is invalid [x509_CRL_INVALID|N/A]
* @retval SEC_UINT32 If the CRL is valid [X509_CRL_VALID|N/A]
* @retval SEC_UINT32 If the nextupdate field is not available [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 If the input Date is invalid [SEC_ERR_INVALID_TIME_FORMAT|N/A]
* @par Dependency
* x509.h
*
* @par Note
* The ucUTCSign,ucUTCHour,ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_validateDate( const X509_CRL_S* pstCRL,
								 DATETIME_S* pstDate);


/**
* @defgroup X509CRLExtn_isCritical
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BOOL X509CRLExtn_isCritical (const SEC_EXTN_S* pstExtension);
* @endcode
* @par Purpose
* To check whether a given extension is critical or not.
* @par Description
* This method checks if the given extension is a critical extension or not.
* The boolean value for criticality of the extension is returned.
* @param[in] pstExtension Pointer to the extension whose critcality needs to be known. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BOOL If the input argument is missing [SEC_FALSE|N/A]
* @retval SEC_BOOL If the extension is critical [SEC_TRUE|N/A]
* @retval SEC_BOOL If the extension is not critical [SEC_FALSE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BOOL X509CRLExtn_isCritical(const SEC_EXTN_S* pstExtension );



/**
* @defgroup X509CRLExtn_isDelta
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BOOL X509CRLExtn_isDelta(const X509_CRL_S*  pstCRL);
* @endcode
* @par Purpose
* To check whether the given CRL is delta CRL or not.
* @par Description
* This method checks if the given CRL is a delta CRL or not.
* Based on the existence of the delta CRL indicator an appropriate bool value is returned.
* @param[in] pstCRL A reference to CRL structure in the memory [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BOOL If the input argument is missing [SEC_FALSE|N/A]
* @retval SEC_BOOL If the CRL is delta [SEC_TRUE|N/A]
* @retval SEC_BOOL If the CRL is not delta [SEC_FALSE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BOOL X509CRLExtn_isDelta(const X509_CRL_S*  pstCRL);


/**
* @defgroup X509CRL_save
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_save (SEC_CHAR* pcfileName,
* X509_CRL_S* pstCRL
* );
* @endcode
* @par Purpose
* To save the CRL in DER format.
* @par Description
* This method is used to save the CRL in DER format on the local machine.
* The CRL will be encoded and saved in DER fomat only.
* Since the CRL will be encoded internally all the mandatory fields need to be present.
* The user needs to provide a pointer to the CRL struct along with the name of the file in which the CRL has to be saved.
* If the CRL is stored successfully then SEC_SUCCESS is returned, else an appropriate error code will be returned.
* @param[in] pcfileName The name of the file where the CRL has to be saved [N/A]
* @param[in] pstCRL A reference to CRL structure in the memory [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_UINT32 If any of the input arguments are NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the file write fails [SEC_ERR_FILE_WRITE_FAILED|N/A]
* @retval SEC_UINT32 If the encode fails [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 The DER code is written successfully to the file [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_save( SEC_CHAR*   pcfileName,
						 X509_CRL_S* pstCRL);


/**
* @defgroup X509CRL_read
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CRL_S* X509CRL_read (SEC_CHAR* pcfileName,
* SEC_INT32* piRetVal
* );
* @endcode
* @par Purpose
* To convert the CRL from the DER code format to X509 CRL structure.
* @par Description
* This method is used to read the CRL from the local machine.The CRL needs to be available in its encoded format(DER only).
* The application needs to provide the name of the file from which the CRL needs to be decoded.
* Once the CRL is decoded successfully then CRL structure is returned back to the user.
* @param[in] pcfileName The name of the file where the DER code of the CRL is available [N/A]
* @param[out] piRetVal The number of bytes read successfully [N/A]
* @retval X509_CRL_S* A reference to CRL structure in the memory [X509_CRL_S*|N/A]
* @retval X509_CRL_S* If the input arguments are NULL [SEC_NULL|N/A]
* @retval X509_CRL_S* If the input file could not be opened [SEC_NULL|N/A]
* @retval X509_CRL_S* If the memory allocation fails [SEC_NULL|N/A]
* @retval X509_CRL_S* If the decode fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the read CRL, to free this memory
* application has to call the X509CRL_free.
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

PSELINKDLL X509_CRL_S* X509CRL_read( SEC_CHAR*   pcfileName,
						  SEC_INT32*  piRetVal);


/**
* @defgroup X509CRL_getEntryExtnCount
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509CRL_getEntryExtnCount( const X509_REVOKED_S* pstRevoked);
* @endcode
* @par Purpose
* To fetch the count of entry extensions in a given revoked node.
* @par Description
* This function returns the count of  entry extension in a given revoked node.
* The revoked node can be obtained using the API X509CRL_getRevoked.
* If the entry extension list is absent an appropriate error code
* will be returned back to the user.
* @param[in] pstRevoked A pointer to a revoked node in memory [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 If the argument is missing [-1|N/A]
* @retval SEC_INT32 If the requested data is not available [-1|N/A]
* @retval SEC_INT32 If successfull then the count [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509CRL_getEntryExtnCount( const X509_REVOKED_S* pstRevoked);


/**
* @defgroup X509CRL_getEntryExtnByCID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_EXTN_S* X509CRL_getEntryExtnByCID( const X509_REVOKED_S* pstRevoked,
* SEC_UINT32 uiExtensionID
* );
* @endcode
* @par Purpose
* To fetch an entry extension for a CID in the given revoked node.
* @par Description
* This method fetches an entry extension for a given CID in a given revoked node.
* The revoked node can be obtained using the API X509CRL_getRevoked.
* If a extension matching the given input CID is not available then SEC_NULL will be returned back to the user.
* @param[in] pstRevoked The pointer to the revoked node in memory [N/A]
* @param[in] uiExtensionID The number that maps to the Object identifier for the extension [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_EXTN_S* The reference pointer to the extension that matches the CID [SEC_EXTN_S*|N/A]
* @retval SEC_EXTN_S* If the input param is null [SEC_NULL|N/A]
* @retval SEC_EXTN_S* If the CID is invalid [SEC_NULL|N/A]
* @retval SEC_EXTN_S* If a matching extension is not found [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_EXTN_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_EXTN_S* X509CRL_getEntryExtnByCID( const X509_REVOKED_S* pstRevoked,
									   SEC_UINT32            uiExtensionID);


/**
* @defgroup X509CRL_getEntryExtnByIndex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_EXTN_S* X509CRL_getEntryExtnByIndex (const X509_REVOKED_S* pstRevoked,
* SEC_UINT32 uiIndex
* );
* @endcode
* @par Purpose
* To fetch an entry extension from a revoked node by a given index.
* @par Description
* This method fetches an entry extension corresponding to a given Index in the revoked node.
* The revoked node can be obtained using the API X509CRL_getRevoked.
* SEC_NULL will be returned if such an index is not available. Index value starts with zero.
* @param[in] pstRevoked The pointer to the revoked node in memory [N/A]
* @param[in] uiIndex The index in the entry extension list from which the data needs to be fetched [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_EXTN_S* The extension that matches the ID of the identifier. Returns NULL if not available [SEC_EXTN_S*|N/A]
* @retval SEC_EXTN_S* If the input argument is null [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_EXTN_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_EXTN_S* X509CRL_getEntryExtnByIndex( const X509_REVOKED_S* pstRevoked,
							              SEC_UINT32           uiIndex);



/**
* @defgroup X509CRL_delEntryExtnByIndex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_delEntryExtnByIndex (X509_REVOKED_S* pstRevoked,
* SEC_UINT32 uiIndex
* );
* @endcode
* @par Purpose
* To delete an entry extension corresponding to a given index in the revoked node
* @par Description
* This method deletes a entry extension by a given Index.
* It searches through the list and deletes the extension if available,
* else an appropriate error message is returned. Index value starts with zero.
* @param[in] uiIndex The index in the entry extension list from which the extension needs to be deleted [N/A]
* @param[out] pstRevoked The pointer to the revoked node in memory [N/A]
* @retval SEC_UINT32 If the input argument is null [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the extenion is deleted successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If the requested extension is not available [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509CRL_delEntryExtnByIndex(X509_REVOKED_S* pstRevoked,
								       SEC_UINT32      uiIndex);





/**
* @defgroup X509CRL_delEntryExtnByCID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_delEntryExtnByCID (X509_REVOKED_S* pstRevoked,
* SEC_UINT32 uiCID
* );
* @endcode
* @par Purpose
* To delete an entry extension corresponding to a given CID in the revoked node.
* @par Description
* This method deletes a Entry extension by a given CID.
* It searches through the list and deletes the extension if available,
* else an appropriate error code is returned.
* @param[in] uiCID The CID for which the extension needs to be searched and deleted [N/A]
* @param[out] pstRevoked The pointer to the revoked node in memory [N/A]
* @retval SEC_UINT32 If the input argument is null [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the given CID is invalid [SEC_ERR_INVALID_CID|N/A]
* @retval SEC_UINT32 If the requested extension is not available [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 If entry extension is deleted successfully [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/



PSELINKDLL SEC_UINT32 X509CRL_delEntryExtnByCID(X509_REVOKED_S* pstRevoked,
								     SEC_UINT32      uiCID);



/**
* @defgroup X509CRL_getExtnByCID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_EXTN_S* X509CRL_getExtnByCID(const X509_CRL_S* pstCRL,
* SEC_UINT32 uiExtensionID
* );
* @endcode
* @par Purpose
* To fetch a CRL extension corresponding to a given CID.
* @par Description
* This method fetches a CRL extension for a given CID.
* The function searches through the list and if available returns a
* pointer to the extension, else SEC_NULL will be returned.
* @param[in] pstCRL The pointer to the CRL struct in memory [N/A]
* @param[in] uiExtensionID The number that maps to the Object identifier for the extension [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_EXTN_S* The extension that matches the ID of the identifier [N/A|N/A]
* @retval SEC_EXTN_S* If the input arguments are null or if the CID is invalid or the requested data is not available
* [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_EXTN_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_EXTN_S* X509CRL_getExtnByCID(  const X509_CRL_S* pstCRL,
								   SEC_UINT32        uiExtensionID);


/**
* @defgroup X509CRL_getExtnByIndex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_EXTN_S* X509CRL_getExtnByIndex (const X509_CRL_S* pstCRL,
* SEC_UINT32 uiIndex
* );
* @endcode
* @par Purpose
*
* @par Description
* This method fetches a CRL  extension by a given Index,It searches through the list and if the extension is available an
* appropriate pointer will be returned,else a null will be returned.Index value starts with zero.
* @param[in] pstCRL The pointer to the CRL struct in memory [N/A]
* @param[in] uiIndex The index in the CRL extension list from which the data needs to be fetched [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_EXTN_S* The reference to extension that is present in the given index [N/A|N/A]
* @retval SEC_EXTN_S* If extension at such a index is not available [SEC_NULL|N/A]
* @retval SEC_EXTN_S* If the input argument is null [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_EXTN_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_EXTN_S* X509CRL_getExtnByIndex(const X509_CRL_S*  pstCRL,
							      SEC_UINT32        uiIndex);


/**
* @defgroup X509CRL_delExtnByIndex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_delExtnByIndex(X509_CRL_S* pstCRL,
* SEC_UINT32 uiIndex
* );
* @endcode
* @par Purpose
* To delete a CRL extension corresponding to the given index.
* @par Description
* This method deletes a CRL extension using a given Index.
* It searches through the list and if the extension is available it deletes
* it else it sends an appropriate error code. Index value starts with zero.
* @param[in] uiIndex The index in the extension list from which the extension needs to be deleted [N/A]
* @param[out] pstCRL The pointer to the CRL structure in memory [N/A]
* @retval SEC_UINT32 If the argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the extension is deleted successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If the requested extension is not available or if such an index is not present.
* [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/


PSELINKDLL SEC_UINT32 X509CRL_delExtnByIndex(X509_CRL_S* pstCRL,
							      SEC_UINT32  uiIndex);


/**
* @defgroup X509CRL_delExtnByCID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_delExtnByCID(X509_CRL_S* pstCRL,
* SEC_UINT32 uiCID
* );
* @endcode
* @par Purpose
* To delete a CRL extension coresponding to a given CID.
* @par Description
* This method deletes a CRL extension by a given CID.
* It searches through the list and if the extension is available it
* deletes it successfully, else an appropriate error code will be returned back to the user.
* @param[in] uiCID The CID for which the extension needs to be searched and deleted [N/A]
* @param[out] pstCRL The pointer to the CRL structure in memory [N/A]
* @retval SEC_UINT32 If the argument is not available [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the CID is invalid [SEC_ERR_INVALID_CID|N/A]
* @retval SEC_UINT32 If the extension is deleted successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If the requested extension is not available [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_delExtnByCID(X509_CRL_S* pstCRL,
							   SEC_UINT32   uiCID);



/**
* @defgroup X509CRL_getRevoked
* @ingroup x509Functions
* @par Prototype
* @code
* X509_REVOKED_S*  X509CRL_getRevoked( const X509_CRL_S* pstCRL,
* SEC_BIGINT_S* pstCertsnum
* );
* @endcode
* @par Purpose
* To fetched the revoked node from a CRL, given certificate serial number.
* @par Description
* This function fetches the revoked node by a given certificate serial number from the given CRL.
* Since revoked node will be available only in case it is already added to the struct,
* the pointer to the revoked node willbe returned if its avaialable else SEC_NULL is returned.
* @param[in] pstCRL A pointer to the existing CRL [N/A]
* @param[in] pstCertsnum The serial number for which the revoked node has to be fetched.[N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_REVOKED_S* Pointer to the revoked node that is in the revoked list [X509_REVOKED_S*|N/A]
* @retval X509_REVOKED_S* If the input arguments are null or revoked node is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the X509_REVOKED_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_REVOKED_S*  X509CRL_getRevoked( const X509_CRL_S* pstCRL,
									 SEC_BIGINT_S* pstCertsnum );


/**
* @defgroup X509CRL_getRevokedByIndex
* @ingroup x509Functions
* @par Prototype
* @code
* X509_REVOKED_S* X509CRL_getRevokedByIndex (const X509_CRL_S* pstCRL,
* SEC_UINT32 uiIndex
* );
* @endcode
* @par Purpose
* To fetch the revoked certificate from the CRL, given the index.
* @par Description
* This function fetches the revoked certificate node by a given index from the given CRL. Since revoked certificate
* node will be available only if its available else SEC_NULL is returned. Index always starts with zero.
* @param[in] pstCRL A pointer to the existing CRL [N/A]
* @param[in] uiIndex The index for which the revoked node has to be fetched [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_REVOKED_S* Pointer to the revoked node that is available in the List [X509_REVOKED_S*|N/A]
* @retval X509_REVOKED_S* If the input arguments are null or revoked node is not avialable or if the revoked node with such a * index is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the X509_REVOKED_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_REVOKED_S*  X509CRL_getRevokedByIndex ( const X509_CRL_S* pstCRL,
										     SEC_UINT32      uiIndex);


/**
* @defgroup X509CRL_sortRevokedListBySN
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_sortRevokedListBySN(X509_CRL_S*  pstCRL);
* @endcode
* @par Purpose
* To sort a CRL by serial number.
* @par Description
* This method sorts a given Certificate revoked list according to serial number.
* The sorted list will be in ascending order of the serial number.
* Internally the sorting is done using quicksort.
* @param[in] N/A N/A [N/A]
* @param[out] pstCRL The pointer to the CRL structure in memory [N/A]
* @retval SEC_UINT32 Input arguments are null or not available [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If sort is performed is successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 List sort has failed [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @par Dependency
* x509.h
* @par Note
*
* The CRL has to be signed again once it has been sorted.
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_sortRevokedListBySN(X509_CRL_S*  pstCRL);



/**
* @defgroup X509CRL_sortRevokedListByDate
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_sortRevokedListByDate (X509_CRL_S* pstCRL);
* @endcode
* @par Purpose
* To sort a CRL by revocation date.
* @par Description
* This method sorts a given revoked list on the basis of revocation date.
* The revoked list will be sorted in ascending order of revocation date.
* Internally the sorting is performed using Quicksort.
* @param[in] N/A N/A [N/A]
* @param[out] pstCRL The pointer to the CRL struct in memory [N/A]
* @retval SEC_UINT32 Input arguments are null [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If sort is performed is successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 List sort has failed [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @par Dependency
* x509.h
* @par Note
*
* The CRL has to be signed again once it has been sorted.
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32 X509CRL_sortRevokedListByDate(X509_CRL_S*  pstCRL);



/**
* @defgroup X509CRL_delRevokedByIndex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509CRL_delRevokedByIndex (X509_CRL_S* pstCRL,
* SEC_UINT32 uiIndex
* );
* @endcode
* @par Purpose
* To delete a revoked node corresponding to the given Index.
* @par Description
* This method deletes a revoked node by a given Index. Internally the list will be searched and deletes the revoked node if
* available else returns the appropriate error code. Index always starts with zero.
* @param[in] uiIndex The index in the  Revoked list from which the revoked node needs to be deleted [N/A]
* @param[out] pstCRL The pointer to the CRL struct in memory [N/A]
* @retval SEC_UINT32 Input arguments are missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the certificate is deleted succsesfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If the node is not available for deletion or if such a index is not available
* [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/


PSELINKDLL SEC_UINT32 X509CRL_delRevokedByIndex (X509_CRL_S*  pstCRL,
							          SEC_UINT32  uiIndex);


/**
* @defgroup X509CRLExtn_createIDP
* @ingroup x509Functions
* @par Prototype
* @code
* X509_IDP_S* X509CRLExtn_createIDP (SEC_BOOL bonlyContainsUCerts,
* SEC_BOOL bonlyContainsCACerts,
* SEC_BOOL bindirectCRL,
* SEC_BOOL bonlyContainsACerts
* );
* @endcode
* @par Purpose
* To create an IDP structure with all the mandatory fields.
* @par Description
* This method is used to create an IDP strcuture with all the mandatory fields.
* The issuing distribution point is a critical CRL extension that identifies the
* CRL distribution point and scope for a particular CRL and it indicates whether the CRL
* covers revocation for end entity  certificates only, CA certificates only, attribute certificates only, or a limited set of
* reason codes.ALL the input fields are mandatory and the input value should be either SEC_FALSE or SEC_TRUE.
* If the input data is not a boolean value then NULL will be returned.
* @param[in] bonlyContainsUCerts This flag indicates it contains revoked user certs [N/A]
* @param[in] bonlyContainsCACerts This flag indicates it contains revoked CA certs [N/A]
* @param[in] bindirectCRL If the scope of the CRL includes certificates issued by authorities other
* than the CRL issuer this flag is used [N/A]
* @param[in] bonlyContainsACerts A flag that indicates if it has attribute certificate [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_IDP_S* The pointer to the structure that is constructed [X509_IDP_S*|N/A]
* @retval X509_IDP_S* If memory allocation fails or if invalid data is given as input [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_IDP_S structure, to free this memory
* application has to call the X509CRLExtn_freeIDP.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_IDP_S*  X509CRLExtn_createIDP(SEC_BOOL bonlyContainsUCerts,
								   SEC_BOOL bonlyContainsCACerts,
								   SEC_BOOL bindirectCRL,
								   SEC_BOOL bonlyContainsACerts);


/**
* @defgroup X509CRLExtn_isContainingUserCerts
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BOOL X509CRLExtn_isContainingUserCerts (const X509_IDP_S* pstIDP);
* @endcode
* @par Purpose
* To check whether the given IDP contains user certificates or not.
* @par Description
* This method checks if given issuing distribution point contains user Certificates or not.
* @param[in] pstIDP A reference pointer to IDP structure in the memory [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BOOL If the input argument is missing [SEC_FALSE|N/A]
* @retval SEC_BOOL If the IDP conatins user certificates [SEC_TRUE|N/A]
* @retval SEC_BOOL If the IDP does not conatins user certificates [SEC_FALSE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BOOL X509CRLExtn_isContainingUserCerts(const X509_IDP_S*  pstIDP);


/**
* @defgroup X509CRLExtn_isContainingCACerts
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BOOL X509CRLExtn_isContainingCACerts(const X509_IDP_S* pstIDP);
* @endcode
* @par Purpose
* To check whether the given IDP contains CA certificates or not.
* @par Description
* This method checks if given Issuing distribution point contains CA certificates or not.
* @param[in] pstIDP A reference pointer to IDP structure in the memory [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BOOL If the input argument is missing [SEC_FALSE|N/A]
* @retval SEC_BOOL If the IDP conatins CA certificates [SEC_TRUE|N/A]
* @retval SEC_BOOL If the IDP does not conatins CA certificates [SEC_FALSE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_BOOL X509CRLExtn_isContainingCACerts(const X509_IDP_S*  pstIDP);


/**
* @defgroup X509CRLExtn_isContainingAttrCerts
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BOOL X509CRLExtn_isContainingAttrCerts(const X509_IDP_S*  pstIDP);
* @endcode
* @par Purpose
* To check whether the IDP contains attribute certificates or not.
* @par Description
* This method checks if the given IDP contains Attribute certificates or not.
* @param[in] pstIDP A reference pointer to IDP structure in the memory [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BOOL If the input argument is missing [SEC_FALSE|N/A]
* @retval SEC_BOOL If the IDP contains attribute certificates [SEC_TRUE|N/A]
* @retval SEC_BOOL If the IDP does not contain attribute certificates [SEC_FALSE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BOOL X509CRLExtn_isContainingAttrCerts(const X509_IDP_S*  pstIDP);


/**
* @defgroup X509CRLExtn_isIndirectCRL
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BOOL X509CRLExtn_isIndirectCRL(const X509_IDP_S* pstIDP);
* @endcode
* @par Purpose
* To check whether the given CRL in indirect CRL or not.
* @par Description
* This method checks if given CRL is an Indirect CRL or Not.
* @param[in] pstIDP A reference pointer to the IDP structure in the memory [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BOOL If the input argument is missing [SEC_FALSE|N/A]
* @retval SEC_BOOL If the CRL is indirect CRL [SEC_TRUE|N/A]
* @retval SEC_BOOL If the CRL is not indirect CRL [SEC_FALSE|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BOOL X509CRLExtn_isIndirectCRL(const X509_IDP_S*  pstIDP);


/**
* @defgroup X509CRLExtn_getDPN
* @ingroup x509Functions
* @par Prototype
* @code
* X509_DPN_S* X509CRLExtn_getDPN (X509_IDP_S* pstIDP);
* @endcode
* @par Purpose
* To fetch the DPN from a given IDP.
* @par Description
* This method returns a refernce to the Distribution point name(DPN) structure from a given IDP.
* DistributionPointName specifies the names of the distribution points that may be used to look up a CRL.
* @param[in] pstIDP A reference pointer to IDP structure in the memory [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_DPN_S* Pointer to the DPN structure [X509_DPN_S*|N/A]
* @retval X509_DPN_S* If the DPN strcuture is not available or the input argument is missing [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the X509_DPN_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_DPN_S* X509CRLExtn_getDPN(X509_IDP_S*  pstIDP);


/**
* @defgroup X509CRLExtn_getReasonsFromIDP
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509CRLExtn_getReasonsFromIDP(X509_IDP_S* pstIDP);
* @endcode
* @par Purpose
* To fetch the reason flag from the given IDP.
* @par Description
* This method returns the reason flag from the given IDP structure.
* The return value is integer equivalent of the bit flags set.
* The user needs to compare the return value against these macros
* X509_REVOKED_AA_COMPROMISE
* X509_REVOKED_PRIVILEGE_WITHDRAWN
* X509_REVOKED_CERT_HOLD
* X509_REVOKED_CESSATION_OF_OPER
* X509_REVOKED_SUPER_SEDED
* X509_REVOKED_AFFILIATION_CHANGED
* X509_REVOKED_CA_COMPROMISE
* X509_REVOKED_KEY_COMPROMISE
* X509_REVOKED_UNUSED_CERT
* Sometimes the value may not be simple of the above types but may be the bitwise or of the different reasons.
* @param[in] pstIDP A reference pointer to IDP structure in the memory [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 If the input argument is missing [-1|N/A]
* @retval SEC_INT32 Reasons of revocation [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509CRLExtn_getReasonsFromIDP(X509_IDP_S*  pstIDP);


/**
* @defgroup X509_dupCRL
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CRL_S* X509_dupCRL(X509_CRL_S* pstCRL);
* @endcode
* @par Purpose
* To duplicate a CRL structure.
* @par Description
* This function duplicates a given CRL structure.
* @param[in] pstCRL [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_CRL_S* Pointer to the duplicated structure [X509_CRL_S*|N/A]
* @retval X509_CRL_S* If input param is null or memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_CRL_S structure, to free this memory
* application has to call the X509CRL_free.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_CRL_S* X509_dupCRL(X509_CRL_S* pstCRL);


/**
* @defgroup X509_dupIssuingDistPoint
* @ingroup x509Functions
* @par Prototype
* @code
* X509_IDP_S* X509_dupIssuingDistPoint(X509_IDP_S* pstIDP);
* @endcode
* @par Purpose
* To duplicate an IDP structure.
* @par Description
* This function duplicates a given Issuing distribution point structure.
* @param[in] pstIDP [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_IDP_S* Pointer to the duplicated structure [X509_IDP_S*|N/A]
* @retval X509_IDP_S* If input param is null or memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_IDP_S structure, to free this memory
* application has to call the X509CRLExtn_freeIDP.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_IDP_S* X509_dupIssuingDistPoint(X509_IDP_S* pstIDP);


/**
* @defgroup X509CRLExtn_freeIDP
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID  X509CRLExtn_freeIDP(X509_IDP_S*  pstIDP);
* @endcode
* @par Purpose
* To free an IDP structure.
* @par Description
* This function releases all the memory assigned for a given IDP structure.
* @param[in] pstIDP Pointer to a IDP struct that needs to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval N/A [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID  X509CRLExtn_freeIDP(X509_IDP_S*  pstIDP);


/**
* @defgroup X509CRL_free
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509CRL_free(X509_CRL_S* pstCRL);
* @endcode
* @par Purpose
* To free a CRL structure.
* @par Description
* This function releases all the memory assigned for a given input CRL
* @param[in] pstCRL Pointer to a CRL struct which has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval N/A [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID  X509CRL_free(X509_CRL_S* pstCRL);

/*
X509 CERTIFICATE FUNCTION DECLARATIONS
*/

/**
* @defgroup X509_createCert
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CERT_S* X509_createCert (X509_CERTVERSION_E enVersion,
* SEC_BIGINT_S* pCertSelNo,
* SEC_ALG_IDENTIFIER_S* pstSignatureAlgoId,
* SEC_NAME_S* pstIssuerName,
* SEC_VALIDITY_S* pstValidity,
* SEC_NAME_S* pstSubjectName,
* SEC_PKEY_S* pstSubjectPubKey
* );
* @endcode
* @par Purpose
* To create X509 certificate with mandatory fields.
*
* @par Description
* This function is used to create X509 certificate with mandatory fields. The function can be used to create a Version
* 1 certificate. Along with this function to create Version 2 certiticate the other APIs to be used are X509_setIssuerUID
* and X509_setSubjectUID. To create Version 3 certificate all the extension structures that have been created has to be
* added to the certificate using X509_addExtnToCert API. All the input parameters mentioned has to be created before
* calling this function. The signature algorithm field in the certificate structure and the signature algorithm in the
* TBSCertificate structure is set with the same algorithm. The PublicKeyInfo structure is set with the encoded public
* key and the OID of the Key Generation Algorithm (eg : RSA, DSA, * ECDSA) DH certificate can also be generated by passing
* the DH Public key to this function.
* Steps for Input data preparation for this function are listed below:
* 1. pstIssuerName and pstSubjectName has to be created using X509_createDN API.\n
* 2. pstSignatureAlgId is created using X509_createAlgId API.\n
* 3. pstValidity has to be created using X509_createValidity API.\n
* 4. pCertSelNo has to be created using SEC_cvtToBigInt API.\n
* 5. pstSubjectPubKey is created using CRYPT_genKeyPair Crypto API.
*
* @param[in] enVersion Version of the certificate that has to be set [N/A]
* @param[in] pCertSelNo A unique number to represent the certificate.
* A	hexadecimal number that is obtain by converting a string of number to hexadecimal
* using SEC_cvtToBigInt function, which converts a string of numbers to hexadecimal string.[N/A]
* @param[in] pstSignatureAlgoId Algorithm used for signing the certificate.
* Some of the signing algorithm are RSA, DSA, ECDSA etc [N/A]
* @param[in] pstIssuerName Certificate Issuer Name. This field identifies the issuer of the certificate [N/A]
* @param[in] pstValidity Identifies the duration within which the certificate is valid [N/A]
* @param[in] pstSubjectName Subject Name for whom the certificate is created [N/A]
* @param[in] pstSubjectPubKey Public key associated with the certificate.
* The public key is encoded and set to the PublicKeyInfo field of the certificate [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* On successful execution X509_CERT_S certificate pointer filled
* with the passed fields is set and returned [X509_CERT_S|N/A]
* @retval X509_CERT_S* On failure conditions. The failure conditions may be\n
* 1.Input parameter NULL\n
* 2.Memory Allocation fails\n
* 3.Creation of SubjectPublicKeyInfo fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_CERT_S structure, to free this memory
* application has to call the X509_freeCert API.
*
* @par Note
* N/A
* 
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL X509_CERT_S* X509_createCert (X509_CERTVERSION_E enVersion,
							  SEC_BIGINT_S* pCertSelNo,
							  SEC_ALG_IDENTIFIER_S* pstSignatureAlgoId,
							  SEC_NAME_S* pstIssuerName,
							  SEC_VALIDITY_S* pstValidity,
							  SEC_NAME_S* pstSubjectName,
							  SEC_PKEY_S* pstSubjectPubKey);



/**
* @defgroup X509_addExtnToCert
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_addExtnToCert(SEC_EXTN_S* pstExtesnion,
* X509_CERT_S* pstCertificate
* );
* @endcode
* @par Purpose
* To add an extension to the given certificate.
* @par Description
* This function is used to add the extension to the certificate.
* The extension that are to be placed in the certificate has
* to be created before using X509_createExtn API.
* @param[in] pstExtension The extension that has to be placed in the certificate [N/A]
* @param[out] pstCertificate The certificate to which the extension has to be added [N/A]
* @retval SEC_UINT32 On successful execution SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Duplication of the extension fails [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Returned when the input argument is incorrect [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory Allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @par Dependency
* x509.h
* @par Note
*
* Extension structure passed as input to this function has to be freed since the structure is duplicated.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_addExtnToCert(SEC_EXTN_S* pstExtension,
							  X509_CERT_S* pstCertificate);


/**
* @defgroup X509_checkPrivateKey
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_checkPrivateKey(X509_CERT_S* pstCertificate,
* SEC_PKEY_S* pstPrivateKey
* );
* @endcode
* @par Purpose
* To check whether the public & private key correspond to each other.
* @par Description
* This method checks whether the public key and the private key matches.
* This method is called when self signed certificate is being created.
* @param[in] pstCertificate The certificate from which the public key is extracted that has to be matched [N/A]
* @param[in] pstPrivateKey The private key that has to be checked [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_UINT32 Public key in certificate and passed private key match. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Private key does not match the public key in certificate [SEC_ERR_KEYPAIR_MISMATCH|N/A]
* @retval SEC_UINT32 Returned when input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_checkPrivateKey(X509_CERT_S* pstCertificate,
								SEC_PKEY_S* pstPrivateKey);


/**
* @defgroup X509_signCertificate
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_signCertificate(X509_CERT_S* pstCertificate,
* SEC_PKEY_S* pstPrivateKey
* );
* @endcode
* @par Purpose
* To sign a x509 certificate with the given private key.
* @par Description
* This function signs the certificate given the private key for signing.
* Before signing the certificate the algorithm Object Identifiers that are set in the certificate is compared.
* The certificate extensions is verified to find whether there are
* multiple existence of same extensions.Based on the certificate version set comaparison is made to check whether the
* certificate consists of only the permitted fields corresponding to the certificate version.
* The algorithm used to sign the certificate has to match the algorithm object identifier set in the certificate.
* For CA certificate, if Digital signature bit is set in Key usage extension and basic constraint extension present then the
* criticality of the Basic Constriant extension has to be set to TRUE by the application.  Since the DigitalSignature key
* usage depends on other extensions like Name constraints, Policy Mappings, Policy Constraints etc that has to be validated
* by the Application.If all the conditions are verified then the certificate is signed and the set to the signature field of
* the certificate structure.
* @param[in] pstPrivateKey The private key that is used to sign the certificate [N/A]
* @param[out] pstCertificate The certificate to be signed [N/A]
* @retval SEC_UINT32 On successful signing of the certificate SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL or has incorrect data [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Validation of the extension fail [SEC_ERR_INVALID_EXTN|N/A]
* @retval SEC_UINT32 Encoding of the certificate fails [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Sign of certificate fails [SEC_ERR_SIGNING_FAILED|N/A]
* @retval SEC_UINT32 The algorithm set in the certificate is not a signature algorithm [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If there is mismatch in the signature OIDs in the X509_CERT_S structure and SEC_TBSCERT_S
* structure. [SEC_ERR_OID_MISMATCH|N/A]
* @retval SEC_UINT32 Subject Name is not present which is a mandatory field [SEC_ERR_NAME_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Invalid version.Data is not consistent with version [SEC_ERR_INVALID_VERSION|N/A]
* @retval SEC_UINT32 Duplicate Extension available [SEC_ERR_DUPLICATE_EXTN|N/A]
* @retval SEC_UINT32 Required extension not available in certificate [SEC_ERR_EXTN_NOT_AVAILABLE|N/A]
* @par Dependency
* x509.h
* @par Note
* @par Note
*   - For ALGID_SM2DSA signature, the pstPrivateKey should be a key pair i.e. public and private key should be
*      available in pstPrivateKey because public key will be used for the generation of ZA and private key
*      will be used for signature
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_signCertificate(X509_CERT_S* pstCertificate,
								SEC_PKEY_S* pstPrivateKey);


/**
* @defgroup X509_setVersion
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_setVersion(X509_CERTVERSION_E enCertVersion,
* X509_CERT_S* pstCertificate
* );
* @endcode
* @par Purpose
* To set the version of the certificate.
* @par Description
* Sets the version to the certificate. The function checks whether the certificate version set is a valid version.
* The certificate version can be either X509_CERT_VERSION1, X509_CERT_VERSION2 or X509_CERT_VERSION3 has to be passed.
* @param[in] enCertVersion Certificate version[v1/v2/v3] [N/A]
* @param[out] pstCertificate Certificate to which the version has to be set [N/A]
* @retval SEC_UINT32 When the version is set to certificate [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 When input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 When memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_setVersion(X509_CERTVERSION_E enCertVersion,
						   X509_CERT_S* pstCertificate);


/**
* @defgroup X509_getVersion
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_getVersion(X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To fetch the version of a certificate.
* @par Description
* This function returns the version from the certificate.
* @param[in] pstCertificate Certificate from which the version has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 Version of the certificate is returned. The returned version can be either X509_CERT_VERSION1,
* X509_CERT_VERSION2 or X509_CERT_VERSION3 [SEC_INT32|N/A]
* @retval SEC_INT32 Returned when input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509_getVersion(X509_CERT_S* pstCertificate);


/**
* @defgroup X509_createTime
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_TIME_S* X509_createTime(DATETIME_S* pSysTime);
* @endcode
* @par Purpose
* To convert a Datetime structure to UTC or generalized time structure.
* @par Description
* This function converts DATETIME_S structure to either UTC Time or Generalized time.
* If the date passed to the function is
* greater than 1970 and lesser than 2050 the date is converted to UTC format, else to Generalized Time Format.
* @param[in] pSysTime Date that has to be converted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_TIME_S* Structure is created containing the time in either UTC or Generalized time format [SEC_TIME_S*|N/A]
* @retval SEC_TIME_S* When the input parameter is NULL or the time conversion fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_TIME_S structure, to free this memory
* application has to call the X509_freeTime API.
*
* @par Note
*
* The ucUTCSign,ucUTCHour,ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function.
* Dates with year less than 1970 will not be considered valid.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_TIME_S* X509_createTime(DATETIME_S* pSysTime);


/**
* @defgroup X509_createValidity
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VALIDITY_S* X509_createValidity (DATETIME_S* pNotBefore,
* DATETIME_S* pNotAfter
* );
* @endcode
* @par Purpose
* To create a SEC_VALIDITY_S structure.
* @par Description
* This function creates Validity structure. The structure specifies the validity period for the certificate.
* The Validity structure has two fields namely NotBefore and NotAfter.
* NotBefore time indicates the time after which the certificate is valid.
* NotAfter time indicates the time after which the certificate is invalid.
* If the date passed to the function is greater than 1970 and lesser than 2050 the format is UTC,else the format is
* Generalized Time Format.
* @param[in] pNotBefore The notBefore time to be converted.The time format is taken as either Generalized or UTC based on the
* year set in pSysTime input parameter [N/A]
* @param[in] pNotAfter The notAfter time to be converted. The time format is taken as either Generalized or UTC based on the
* year set in pSysTime input parameter [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VALIDITY_S* On successful execution pointer to SEC_VALIDITY_S structure is returned that contains the
* validity time period of the certificate [SEC_VALIDITY_S*|N/A]
* @retval SEC_VALIDITY_S* On failure conditions SEC_NULL is returned.The failures conditions can be one of the following:\n
* 1) Input parameter NULL\n
* 2) Memory Allocation fails\n
* 3) Time conversion fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_VALIDITY_S structure, to free this memory
* application has to call the X509_freeValidity API.
*
* @par Note
* The ucUTCSign,ucUTCHour,ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function
* Dates with year less than 1970 or greater than 2038 will not be considered valid.
* Calendar times  before  20:45:52  UTC,  December  13,  1901  or after
* 03:14:07 UTC,  January 19, 2038 cannot be represented by structure time_t. 
* Portable  applications should  not  try  to create dates before 00:00:00 UTC, 
* January 1, 1970 or after 00:00:00 UTC, January 1, 2038.
* Depending on system architecture(32 bit or 64 bit), dates beyond 2038 may also 
* be represented correctly on certain platforms. However this should not be used.
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_VALIDITY_S* X509_createValidity (DATETIME_S* pNotBefore,
							 DATETIME_S* pNotAfter);


/**
* @defgroup X509_extractNotBefore
* @ingroup x509Functions
* @par Prototype
* @code
* DATETIME_S* X509_extractNotBefore (X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To fetch the NotBefore time from the given certificate.
* @par Description
* This function extracts the notBefore time from the certificate.
* This function is used during certificate verification process.
* @param[in] pstCertificate Certificate from which the time has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval DATETIME_S* UTC Time or Generalized Time that is converted to DATETIME_S format [DATETIME_S*|N/A]
* @retval DATETIME_S* If the input is NULL or the time conversion fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the DATETIME_S structure, to free this memory
* application has to call the ipsi_free API.
*
* @par Note
* Memory has to be de-allocated after usage of NotBefore Time
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* X509_extractNotBefore (X509_CERT_S* pstCertificate);


/**
* @defgroup X509_extractNotAfter
* @ingroup x509Functions
* @par Prototype
* @code
* DATETIME_S* X509_extractNotAfter (X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To fetch the notAfter time from the given certificate.
* @par Description
* This function extracts the notAfter time from the certificate.
* This function is used during certificate verification process.
* @param[in] pstCertificate Certificate from which the time has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval DATETIME_S* UTC Time or Generalized Time that is converted to DATETIME_S format [DATETIME_S*|N/A]
* @retval DATETIME_S* If the input is NULL or the time conversion fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the DATETIME_S structure, to free this memory
* application has to call the ipsi_free API.
*
* @par Note
*
* Memory has to be de-allocated after usage of NotAfter Time
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* X509_extractNotAfter (X509_CERT_S* pstCertificate);


/**
* @defgroup X509_extractPublicKey
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_PKEY_S* X509_extractPublicKey (X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To fetch the public key from the given certificate.
* @par Description
* This function extracts the subject public key from the certificate.The encoded public key is extracted from the
* PublicKeyInfo structure and the Public Key is obtained by decoding.
* @param[in] pstCertificate Certificate from which the key has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_PKEY_S* On successful execution pointer to SEC_PKEY_S structure containing the public key is returned
* [SEC_PKEY_S*|N/A]
* @retval SEC_PKEY_S* On all failure conditions SEC_NULL is returned. The possible failures are:\n
* 1) Input parameter is NULL,\n
* 2) Decode of SubjectPubKeyInfo fails,\n
* 3) Memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
* @par Note
*
* Memory has to be de-allocated after usage of PublicKey using the function CRYPT_PKEY_free API.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_PKEY_S* X509_extractPublicKey (X509_CERT_S* pstCertificate);


/**
* @defgroup X509_getSN
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BIGINT_S* X509_getSN (X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To fetch the serial number from the given certificate.
* @par Description
* This function gets the certificate serial number from the certificate
* @param[in] pstCertificate Certificate from which the Serial number has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BIGINT_S* Pointer to SEC_BIGINT_S structure is returned for successful condition [SEC_BIGINT_S|N/A]
* @retval SEC_BIGINT_S* SEC_NULL is returned when the input parameter is NULL or incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_BIGINT_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BIGINT_S* X509_getSN (X509_CERT_S* pstCertificate);


/**
* @defgroup X509_getSignAlgId
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_ALG_IDENTIFIER_S* X509_getSignAlgId(X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To fetch the signature algorithm from the given cerfificate.
* @par Description
* The function gets the Signature algorithm structure that contains the OID and the parameter associated with the algorithm
* if any.
* @param[in] pstCertificate Certificate from which the signature algorihm has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_ALG_IDENTIFIER_S* On successful execution pointer to SEC_ALG_IDENTIFIER_S structure is returned
* [SEC_ALG_IDENTIFIER_S*|N/A]
* @retval SEC_ALG_IDENTIFIER_S* This is returned when the input parameter is NULL or incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_ALG_IDENTIFIER_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ALG_IDENTIFIER_S* X509_getSignAlgId(X509_CERT_S* pstCertificate);


/**
* @defgroup X509_setSubjectUID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_setSubjectUID (SEC_UCHAR* pucUniqueID,
* SEC_UINT32 uiUIDLength,
* X509_CERT_S* pstCertificate
* );
* @endcode
* @par Purpose
* To set the Subject Unique identifier in a certificate.
* @par Description
* This function is used to set the Subject Unique identifier of the certificate.
* The Unique Identifier is a string that helps in reusing the subject name.
* @param[in] pucUniqueID Pointer to the unique identifier string that has to be set [N/A]
* @param[in] uiUIDLength The length of the String [N/A]
* @param[out] pstCertificate The certificate to which the subjectUID has to be set [N/A]
* @retval SEC_UINT32 On successful execution SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Returned if the input passed in NULL [SEC_ERR_INVALID_ARG|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_setSubjectUID (SEC_UCHAR* pucUniqueID,
							   SEC_UINT32 uiUIDLength,
							   X509_CERT_S* pstCertificate);

/**
* @defgroup X509_getSubjectUID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnBits_S* X509_getSubjectUID (X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To get the Subject UID from a certificate.
* @par Description
* This function is used to return the Subject unique identifier from the certificate.
* @param[in] pstCertificate The certificate from which the UID has to be retrieved [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_AsnBits_S* The pointer structure that contains the String and the length. The length has to be divided by
* 8 to indicate the exact byte length of the string since the length in the structure is bitlength [SEC_AsnBits_S*|N/A]
* @retval SEC_AsnBits_S* Returned if the input to the function is NULL ot the SubjectUID is not present [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnBits_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnBits_S* X509_getSubjectUID (X509_CERT_S* pstCertificate);


/**
* @defgroup X509_setIssuerUID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_setIssuerUID (SEC_UCHAR* pucUniqueID,
* SEC_UINT32 uiUIDLength,
* X509_CERT_S* pstCertificate
* );
* @endcode
* @par Purpose
* To set the Issuer unique identifier of a certificate.
* @par Description
* This function is used to set the Issuer Unique identifier of the certificate. The Unique Identifier is a string that
* identifies the issuer name.
* @param[in] pucUniqueID Pointer to the unique identifier string that has to be set [N/A]
* @param[in] uiUIDLength The length of the String [N/A]
* @param[out] pstCertificate The certificate to which the issuerUID has to be set [N/A]
* @retval SEC_UINT32 On successful execution SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Returned if the input passed in NULL [SEC_ERR_INVALID_ARG|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_setIssuerUID (SEC_UCHAR* pucUniqueID,
							  SEC_UINT32 uiUIDLength,
							  X509_CERT_S* pstCertificate);

/**
* @defgroup X509_getIssuerUID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnBits_S* X509_getIssuerUID (X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To get the Issuer UID from a certificate.
* @par Description
* This function is used to extract the Issuer unique identifier from the certificate
* @param[in] pstCertificate The certificate  from which the UID has to be retrieved [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_AsnBits_S* The structure that contains the String and the length.The length has to be divided by 8 to indicate * the exact byte length of the string since the length in the structure is bitlength [SEC_AsnBits_S*|N/A]
* @retval SEC_AsnBits_S* Returned if the input to the function is NULL ot the IssuerUID is not present [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnBits_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnBits_S* X509_getIssuerUID (X509_CERT_S* pstCertificate);


/**
* @defgroup X509_createDN
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_NAME_S* X509_createDN(SEC_UINT32 uiDNAttrLen, X509_DN_ATTR_VALUE_S* pstDNAttrValue);
* @endcode
* @par Purpose
* To create an X509 Name structure.
* @par Description
* This functions is used to create X509 name structure. Input to this function is an array of structures and the count
* of the number of structures in the array. Each structure contains the CID of the attribute,stringtype and data.
* Internally the input structure will be parsed and the name will be created.
* The CID types that can be used are:\n
* Country, [TYPE_COUNTRY]\n
* Organization, [TYPE_ORGANIZATION]\n
* Organization Unit Name, [TYPE_ORG_UNIT_NAME]\n
* DNQualifier, [TYPE_DNQUALIFIER]\n
* State, [TYPE_STATE]\n
* Serial Number, [TYPE_SERIAL_NUMBER]\n
* Locality, [TYPE_LOCALITY]\n
* Title, [TYPE_TITLE]\n
* Surname, [TYPE_SURNAME]\n
* GivenName, [TYPE_GIVENNAME]\n
* Initials, [TYPE_INITIALS]\n
* Pseudonym, [TYPE_PSEUDONYM]\n
* Generation Qualifier, [TYPE_GENQUALIFIER]\n
* Email Address, [TYPE_EMAIL]\n
* Domain Component, [TYPE_DOMAIN_COMPONENT]\n
* Common Name, [TYPE_COMMON_NAME] \n
* Name [TYPE_NAME] \n
* Unstructured Name [TYPE_UNSTRUCTURED_NAME] and \n
* Unstructured Address [TYPE_UNSTRUCTURED_ADDR]
*
* @param[in] uiDNAttrLen Number of array elements [N/A]
* @param[in] pstDNAttrValue Pointer to the array of structures TYPE_DNQUALIFIER, TYPE_COUNTRY, TYPE_SERIAL_NUMBER
* can only be represented in PrintableString format. TYPE_DOMAIN_COMPONENT, TYPE_EMAIL can only be represented in
* IA5String. All the other remaining types can take one of the following types as input PrintableString, UTF8String,
* UniversalString, TeletexString or BMPString. The string is not validated for String Type other than Printable
* string [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_NAME_S* On successful execution pointer to SEC_NAME_S structure is returned [SEC_NAME_S|N/A]
* @retval SEC_NAME_S* On failure conditions SEC_NULL is returned. The failures conditions can be one of the following:\n
* 1) Input parameter is NULL\n
* 2) Memory Allocation fail\n
* 3) Attribute Type may not be represented in the requested String format\n
* 4) Input data is incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_NAME_S structure, to free this memory
* application has to call the X509_freeName API.
*
* @par Note
* 1. An empty SEC_NAME_S cannot be created with this API. \n
* 2. Creation of multi-valued unstructuredName, unstructuredAddress and email address is not supported
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_NAME_S* X509_createDN(SEC_UINT32 uiDNAttrLen, X509_DN_ATTR_VALUE_S* pstDNAttrValue);


/**
* @defgroup X509_createAttrTypeAndValue
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* X509_createAttrTypeAndValue(SEC_UINT32 uiAttributeID,
* SEC_UINT32 uiStringFormat,
* SEC_UINT32 uiAttrValueLen,
* SEC_UINT32 pucAttrValue
* );
* @endcode
* @par Purpose
* To create Attribute type & value structure.
*
* @par Description
* This function creates the SEC_ATTR_TYPE_AND_VALUE_S structure that is present in the Name structure.
* The AttributeTypeAndValue structure contains an OID and AnyDefinedBy type in which the data has to be copied.
* Depending on the OID the value in the AnyDefinedBy Type is determined.
*
* @param[in] uiAttributeID The CID for which the Structure has to be created [N/A]
* @param[in] uiStringFormat The string format that has to be used to store the data in the structure. Mostly the string
* format is PrintableString. Email, DomainComponent are represented in IA5String. All the string formats to be used are
* present in X509_STRINGTYPE_E.	[N/A]
* @param[in] uiAttrValueLen The length of the input data that to be put in the AttributeTypeAndValue structure member [N/A]
* @param[in] pucAttrValue The string that has to be set in the AnyDefinedBy field of the AttributeTypeAndValue structure
* The string is not validated for String Type other than Printable string. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ATTR_TYPE_AND_VALUE_S On successful execution pointer to SEC_ATTR_TYPE_AND_VALUE_S structure is returned
* [SEC_ATTR_TYPE_AND_VALUE_S|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S On failure conditions SEC_NULL is returned. The failures conditions can be one of the
* following:\n
* 1.Input parameter is NULL\n
* 2.Memory Allocation fails\n
* 3.Attribute Type may not be represented in the requested String format\n
* 4.Input data is incorrect [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_ATTR_TYPE_AND_VALUE_S structure, to free this memory
* application has to call the X509_freeAttrTypeAndValue API.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S* X509_createAttrTypeAndValue(SEC_UINT32 uiAttributeID,
													   SEC_UINT32 uiStringFormat,
													   SEC_UINT32 uiAttrValueLen,
													   SEC_UCHAR* pucAttrValue);

/**
* @defgroup X509_setSubjectName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_setSubjectName (SEC_NAME_S* pstSubjectName,
* X509_CERT_S* pstCertificate
* );
* @endcode
* @par Purpose
* To set the subject name to the certificate.
*
* @par Description
* This function sets the subject name to certificate. Before calling this method, the name has to be created
* using X509_createDN API.
*
* @param[in] pstSubjectName The name that has to be set to the subject name field of the certificate [N/A]
* @param[out] pstCertificate The certificate to which the subject name has to be set [N/A]
*
* @retval SEC_UINT32 On successful execution SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Returned if the input passed in NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Returned when duplicating of subject name fails [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* x509.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_setSubjectName (SEC_NAME_S* pstSubjectName,
								X509_CERT_S* pstCertificate);


/**
* @defgroup X509_getSubjectName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_NAME_S* X509_getSubjectName (X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To get the subject name from the given certificate.
* @par Description
* The function returns a pointer to the structure containing the Subject name from the given certificate.
* @param[in] pstCertificate Certificate from which the subject name has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_NAME_S* Pointer to subject name from the certificate [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* Returned if the input in NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_NAME_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_NAME_S* X509_getSubjectName (X509_CERT_S* pstCertificate);


/**
* @defgroup X509_setIssuerName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_setIssuerName(SEC_NAME_S* pstIssuerName,
* X509_CERT_S* pstCertificate
* );
* @endcode
* @par Purpose
* To set the issuer name to a given certificate.
* @par Description
* Sets the issuer name to certificate.
* Before calling this method, the name has to be created using X509_createDN API
* @param[in] pstIssuerName The name that has to be set to the issuer name field of the certificate [N/A]
* @param[out] pstCertificate The certificate to which the issuer name has to be set [N/A]
* @retval SEC_UINT32 On successful execution SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 if the input passed in NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 when duplicating of issuer name fails [SEC_ERR_DATA_COPY_FAILED|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_setIssuerName(SEC_NAME_S* pstIssuerName,
							  X509_CERT_S* pstCertificate);

/**
* @defgroup X509_getIssuerName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_NAME_S* X509_getIssuerName (X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To get the issuer name from the given certificate.
* @par Description
* The function gets the Issuer name from the certificate.
* The function is used to verify the Certificate Issuer name with a trusted CA certificate list.
* @param[in] pstCertificate Certificate from which the issuer name has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_NAME_S* Pointer to issuer name from the certificate [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* Returned if the input in NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_NAME_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_NAME_S* X509_getIssuerName (X509_CERT_S* pstCertificate);


/**
* @defgroup X509Extn_getEffectiveKeyUsages
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509Extn_getEffectiveKeyUsages (SEC_UINT32 uiKeyUsage,
* SEC_List_S* pExtnKeyUsageList
* );
* @endcode
* @par Purpose
* To get a count of the number of effective key usages for a given certificate.
* @par Description
* This function gets the effective key usage for the certificate. This function returns the combined key usage that is
* permitted for the certificate. During the certification validation, this method can be used to get the effective key usage.
* In this case the key usages consistent with both the extensions has to be used.
* @param[in] uiKeyUsage The integer value of the keyUsage. Key Usage specifies for what purpose the certificate has to be
* used [N/A]
* @param[in] pExtnKeyUsageList The extended key usage used to get the effective key usage [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 On successful execution the combined key usage(integer value) is returned.0 is also a valid key usage.
* [SEC_INT32|N/A]
* @retval SEC_INT32 Is returned if the input parameters is NULL [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509Extn_getEffectiveKeyUsages (SEC_UINT32 uiKeyUsage,
										  SEC_List_S* pExtnKeyUsageList);


/**
* @defgroup X509_getExtnByCID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_EXTN_S* X509_getExtnByCID (X509_CERT_S* pstCertificate,
* SEC_UINT32 uiExtnID
* );
* @endcode
* @par Purpose
* To fetch in a certificate, the extension corresponding to a given CID.
* @par Description
* The function returns the extension from the certificate based on the CID.
* If a match is found then the extension is returned.
* In order to use the extension, X509Extn_extractContent has to be called which returns a void pointer after decoding.
* @param[in] pstCertificate The certificate from which the extension has to be extracted [N/A]
* @param[in] uiExtnID The extension that has to be searched from the certificate [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_EXTN_S* Pointer to the extension structure that is present in the certificate [SEC_EXTN_S*|N/A]
* @retval SEC_EXTN_S* On all failure conditions SEC_NULL is returned. The failure condition can be one of the following:
* Input parameter is NULL,
* Unknown CID,
* Extension matching the CID is not present in the certificate [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_EXTN_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_EXTN_S* X509_getExtnByCID (X509_CERT_S* pstCertificate,
							   SEC_UINT32 uiExtnID);

/**
* @defgroup X509_getExtnByCriticalFlag
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S*  X509_getExtnByCriticalFlag (X509_CERT_S* pstCertificate,
* SEC_BOOL bCritical
* );
* @endcode
* @par Purpose
* To fetch the list of extensions whose critical field matches the ones from the certificate.
* @par Description
* Returns the list of extensions whose critical field matches from the certificate. The function is used during parsing
* the certificate and also during certificate path validation.
* @param[in] pstCertificate The certificate from which the extensions has to be returned based on critical flag [N/A]
* @param[in] bCritical The critical flag based on which the extension has to be extracted from the certificate [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* The pointer to list of extension that matches the critical value [SEC_List_S*|N/A]
* @retval SEC_List_S* Memory allocation fails for creation of list or the input parameter is NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
* @par Note
*
* List returned from this function has to be deleted after use. Use X509_freeExtensionList API to free.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S*  X509_getExtnByCriticalFlag (X509_CERT_S* pstCertificate,
										 SEC_BOOL bCritical);


/**
* @defgroup X509_createExtn
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_EXTN_S* X509_createExtn (SEC_UINT32 uiExtnCID,
* SEC_BOOL bCritical,
* SEC_VOID* pstExtnData
* );
* @endcode
* @par Purpose
* To create an SEC_EXTN_S structure.
* @par Description
* This function is used to create an extension. The extension structure is created and the CID is mapped to an OID and
* copied to the extension. The data that has to be set in the Extension is encoded and the encoded data is copied to
* the extnValue of the extension structure along with the critical flag. Some of the extension structure should always
* be set to a predefined criticality. If the criticality is other than the mentioned value the extension is not created.
* For CA certificate, if Digital signature bit is set in Key usage extension and basic constraint extension present then
* the criticality of the Basic Constriant extension has to be set to TRUE by the application. Some of the extension
* criticality that has to be always SEC_FALSE are listed below.\n
* For X509 EXTENSIONS:\n
* Authority Key Identifier,\n
* Subject Key Identifier,\n
* Private Key Usage Period,\n
* Subject Directory Attributes,\n
* Freshest CRL,\n
* Authority Info Access,\n
* Subject Info Access,\n
* Issuer Alternate Name,\n
* CRL Distribution Point,\n
* CRL Number\n
* For X509 CRL ENTRY EXTENSIONS\n
* CRL Reasons,\n
* Hold Instruction Code and\n
* Invalidity Date\n
* Some of the extension criticality that has to be always SEC_TRUE.\n
* For X509 EXTENSIONS\n
* Name Constraints\n
* Inhibit Any Policy\n
* Delta CRL Indicator\n
* Issuing Distribution Point\n
* Policy Mapping\n
* Policy Constraints\n
* To create the CRL reason extension always use the enum X509_CRL_REASON_E.\n
* To create the Reason Code extension, provide the pointer to the enum as input to the create function.\n
* To create the Hold Instruction code, provide the pointer to OID as input to the create function.\n
* To create the the Invalidity Date Extension, provide the pointer to DATETIME_S structure. Internally the Date will be
* transformed into generalized Time. Valid Date formats are only supported.\n
* To create KEY USAGE extension, the macros that are provided are to be used to specify the key usages of the certificate.\n
* To create ANY POLICY extension, the number that has to be set has to be passed to function using a pointer variable.
*
* @param[in] uiExtnCID Extension that has to be created [N/A]
* @param[in] bCritical The critical flag that has to be set [N/A]
* @param[in] pstExtnData The extension data that has to be encoded and copied into the extension [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_EXTN_S* On successful execution pointer to SEC_EXTN_S structure is returned [SEC_EXTN_S*|N/A]
* @retval SEC_EXTN_S* On failure conditions SEC_NULL is returned. The failures conditions can be one of the following:\n
* 1. Input parameter is NULL\n
* 2. Memory Allocation fails\n
* 3. Encoding of data fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_EXTN_S structure, to free this memory
* application has to call the X509_freeExtension API.
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

PSELINKDLL SEC_EXTN_S* X509_createExtn (SEC_UINT32 uiExtnCID,
							 SEC_BOOL bCritical,
							 SEC_VOID* pstExtnData);

/**
* @defgroup X509_getCIDFromExtn
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_getCIDFromExtn(SEC_EXTN_S* pstExtn);
* @endcode
* @par Purpose
* To get the CID from the given extension.
* @par Description
* The function returns the Common ID from the extension. The function calls the SEC_getCID function to get the integer mapping of
* of the OID in Extension.
* @param[in] pstExtn The extension from which the CID has to be obtained [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 The integer mapping of the OID in extension is returned on successful execution [0ID|N/A]
* @retval SEC_INT32 Returned when input parameter is NULL or incorrect [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509_getCIDFromExtn(SEC_EXTN_S* pstExtn);


/**
* @defgroup X509Extn_extractContent
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID* X509Extn_extractContent(SEC_EXTN_S* pstExtn);
* @endcode
* @par Purpose
* To get the decoded data from the given extension.
* @par Description
* This function is used to get the decoded data from the extension. The extension structure passed is decoded depending on
* the OID in the extension.The function returns the pointer to the decoded data from the extension.
* @param[in] pstExtn The extension that has to be decoded [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID* On successful execution pointer to SEC_VOID is returned after decoding the extension. The SEC_VOID*
* has to be mapped to respective structure based on the OID present in the extension [SEC_VOID*|N/A]
* @retval SEC_VOID* On failure conditions SEC_NULL is returned. The failures conditions can be one of the following:
* Input parameter is NULL,
* Memory Allocation fails,
* Decoding of extension value fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the Extension value, to free this memory
* application has to call the corresponding free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID* X509Extn_extractContent(SEC_EXTN_S* pstExtn);


/**
* @defgroup X509Extn_setCritical
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509Extn_setCritical(SEC_BOOL bCriticalFlag,
* SEC_EXTN_S* pstExtn
* );
* @endcode
* @par Purpose
* To set the criticality of the extension.
* @par Description
* This function is used to set the criticality of the extension
* @param[in] bCriticalFlag The critical flag that has to be set [N/A]
* @param[out] pstExtn Extension to which the criticality has to be set [N/A]
* @retval SEC_UINT32 On successful execution SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Returned if the input passed in NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Returned when duplicating of issuer name fails [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509Extn_setCritical(SEC_BOOL bCriticalFlag,
								SEC_EXTN_S* pstExtn);


/**
* @defgroup X509Extn_getCritical
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509Extn_getCritical(SEC_EXTN_S* pstExtn);
* @endcode
* @par Purpose
* To fetch the criticality of the extension.
* @par Description
* Returns the criticality of the extension
* @param[in] pstExtn Extension from which the criticality has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 The criticality value from the extension is returned on successful execution [SEC_INT32|N/A]
* @retval SEC_INT32 This is returned for failure conditions [-1|N/A]
* @retval SEC_INT32 This is returned when Input parameter is NULL [1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509Extn_getCritical(SEC_EXTN_S* pstExtn);


/**
* @defgroup X509_getExtnCount
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_getExtnCount(X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To get the number of extensions in the given certificate.
* @par Description
* Returns the number of extensions in the certificate
* @param[in] pstCertificate The certificate from which the number of extensions has to be returned [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 The  Count of extensions in the certificate is returned on successful execution [SEC_INT32|N/A]
* @retval SEC_INT32 This is returned for failure conditions if the input parameter is NULL or Extensions field in
* certificate is NULL [-1|N/A]
*
* @par Dependency
* x509.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509_getExtnCount(X509_CERT_S* pstCertificate);




/**
* @defgroup x509CRL_getExtnFromList
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* x509CRL_getExtnFromList(SEC_List_S* pEList,SEC_UINT32  uiExtensionID);
* @endcode
* @par Purpose
* To get the extension from a list of extensions.
* @par Description
* This function returns a pointer to the extension corresponding to the Extension ID.
* @param[in] pEList pointer to the Extensions List in the memory. [N/A]
* @param[in] uiExtensionID Extension ID. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_EXTN_S* A pointer to the Extension corresponding to the Extn ID [SEC_List_S*|N/A]
* @retval SEC_EXTN_S* If the input is NULL or requested data is not available [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_EXTN_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_EXTN_S* x509CRL_getExtnFromList( SEC_List_S* pEList,
                                    SEC_UINT32  uiExtensionID);


/**
* @defgroup X509Extn_extractAKID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID* X509Extn_extractAKID(SEC_List_S* pCRLEList);
* @endcode
* @par Purpose
* To get the decoded AKID Extn from the given extension list.
* @par Description
* This function is used to get the decoded AKID extn from the extension list. 
* The function returns the pointer to the decoded AKID Extn from the extension.
* @param[in] pCRLEList The extension list from which the AKID Extn has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_AKID_S* On successful execution pointer to X509_AKID_S is returned after decoding the extension. 
* [SEC_VOID*|N/A]
* @retval X509_AKID_S* On failure conditions SEC_NULL is returned. The failures conditions can be one of the following:
* Input parameter is NULL,
* Memory Allocation fails,
* Decoding of extension value fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_AKID_S structure, to free this memory
* application has to call the X509Extn_freeAKID function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_AKID_S* X509Extn_extractAKID(SEC_List_S* pCRLEList);

/**
* @defgroup X509_compareName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_compareName(SEC_NAME_S* pstSrcName, SEC_NAME_S* pstTrgName);
* @endcode
* @par Purpose
* To compare two SEC_NAME_S structures.
* @par Description
* The function compares two names structures. The comparison is done by first comparing the length and then the comparison of
* the value in the AttributeTypeAndValue structure that holds the data.
* @param[in] pstSrcName The source name that has to be compared [N/A]
* @param[in] pstTrgName The name that has to be compared against the source name [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_UINT32 This is returned if the name mathces [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If the input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Error code when the name mismatch [SEC_ERR_NAME_MISMATCH|N/A]
* @retval SEC_UINT32 If duplication of name fails [SEC_ERR_DATA_COPY_FAILED|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_compareName(SEC_NAME_S* pstSrcName, SEC_NAME_S* pstTrgName);

/**
* @defgroup X509_compareName_ex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_compareName_ex(SEC_NAME_S* pstSrcName, SEC_NAME_S* pstTrgName);
* @endcode
* @par Purpose
* To compare two SEC_NAME_S structures.
* @par Description
* The function compares two names structures. The comparison is done by first comparing the length and then the comparison of
* the value in the AttributeTypeAndValue structure that holds the data.The comparison is continued in the'
* second list until the match is found.
* @param[in] pstSrcName The source name that has to be compared [N/A]
* @param[in] pstTrgName The name that has to be compared against the source name [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_UINT32 This is returned if the name mathces [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If the input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Error code when the name mismatch [SEC_ERR_NAME_MISMATCH|N/A]
* @retval SEC_UINT32 If duplication of name fails [SEC_ERR_DATA_COPY_FAILED|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_compareName_ex(SEC_NAME_S* pstSrcName, SEC_NAME_S* pstTrgName);

/**
* @defgroup X509_compareIssuerAndSerial
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_compareIssuerAndSerial(X509_CERT_S* pstSourceCert,
* X509_CERT_S* pstTargetCert
* );
* @endcode
* @par Purpose
* To compare the Issuer name and Serial number of two certificates.
* @par Description
* The function extracts the issuer name and serial number from the certificates. This Compares the Issuer name and serial
* number of two certificates. This is Used during certificate verification and validation.
* @param[in] pstSourceCert The certificate that has to be compared [N/A]
* @param[in] pstTargetCert The ceritifcate to which the name and serial number has to be compared with [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_UINT32 This is returned if the name and serial number mathces [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input parameters is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the serial number does not match [SEC_ERR_ISSUERSERIAL_MISMATCH|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_compareIssuerAndSerial(X509_CERT_S* pstSourceCert, X509_CERT_S* pstTargetCert);



/**
* @defgroup X509_calcNameHash
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_calcNameHash(SEC_NAME_S* pstName,SEC_UINT32 uiHashAlgoID,
* SEC_UINT32* puiHashLen
* );
* @endcode
* @par Purpose
* To calculate the hash of the name structure using the given hash algorithm.
* @par Description
* The function generates the hash of the Name structure.The name is encoded and then hash on in it calculated
* based on the hash algorithm given as input. The hash value can be used for verification of the name.The hash
* algorithms to be used are one of the below:
* CID_MD5
* CID_SHA1
* CID_SHA256
* CID_SHA384
* CID_SHA512
* CID_SHA224
* @param[in] pstName The name for which the hash has to be generated [N/A]
* @param[in] uiHashAlgoID The hash algorithm that is to be used [N/A]
* @param[out] puiHashLen The length of the hash value [N/A]
* @retval SEC_UCHAR* On successful execution pointer to the hash value is returned [SEC_UCHAR*|N/A]
* @retval SEC_NULL On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:
* Input parameters is NULL,
* Memory allocation fails,
* Encoding of name fails,
* Hash calculation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the Name Hash, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* Memory of hash value returned from this function has to be deallocated
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* X509_calcNameHash(SEC_NAME_S* pstName,SEC_UINT32 uiHashAlgoID,SEC_UINT32* puiHashLen);


/**
* @defgroup X509_calcIssuerAndSerialHash
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_calcIssuerAndSerialHash(SEC_ISSUER_AND_SERIAL_S* pstIssuerAndSerial,
* SEC_UINT32 uiHashAlgoID,
* SEC_UINT32* puiHashLen
* );
* @endcode
* @par Purpose
* To calculate the hash of the SEC_ISSUER_AND_SERIAL_S structure using the given hash algorithm.
* @par Description
* The function generates the hash of the Issuer Name and serial number.The pstIssuerAndSerial structure is encoded and then
* hash on in it calculated based on the hash algorithm given as input. The hash value can be used for verification of the
* issuer name and serial number.The hash algorithms to be used are one of the below:
* CID_MD5
* CID_SHA1
* CID_SHA256
* CID_SHA384
* CID_SHA512
* CID_SHA224
* @param[in] pstIssuerAndSerial The structure that has the issuer and serial number [N/A]
* @param[in] uiHashAlgoID The hash algorithm that has to be used [N/A]
* @param[out] puiHashLen The length of the hash value [N/A]
* @retval SEC_UCHAR* On successful execution pointer to the hash value is returned [N/A|N/A]
* @retval SEC_UCHAR* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:
* Input parameters is NULL,
* Memory allocation fails,
* Encoding of name fails,
* Hash calculation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the Issuer and Serial Hash, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* X509_calcIssuerAndSerialHash(SEC_ISSUER_AND_SERIAL_S* pstIssuerAndSerial,
							SEC_UINT32 uiHashAlgoID,
							SEC_UINT32* puiHashLen);


/**
* @defgroup X509Extn_createBasicConstraint
* @ingroup x509Functions
* @par Prototype
* @code
* X509_BASIC_CONSTRAINT_S* X509Extn_createBasicConstraint(SEC_BOOL bCAFlag,
* SEC_INT32 iPathLength
* );
* @endcode
* @par Purpose
* To create a X509_BASIC_CONSTRAINT_S extension structure.
* @par Description
* The function creates the BasicConstraint extension. The basic constraints extension is used only in CA certificate. The
* path length field in the structure indicates number of certificates that appear in the certificate path. This number is
* used during certificate path validation. The use of Pathlength in BAsic Constraint extension has to be decided by the
* application. If this field has to be optional then a negative value has to be provided as input.
* @param[in] bCAFlag Variable to indicate CA certificate [N/A]
* @param[in] iPathLength Number of certificate in certificate path used during verification. If the pathlength should not be
* created then input to the function has to be negative value. Zero and any positive value creates pathLength optional field
* [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_BASIC_CONSTRAINT_S* Pointer to the created structure [X509_BASIC_CONSTRAINT_S*|N/A]
* @retval X509_BASIC_CONSTRAINT_S* Returned if the memoy allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_BASIC_CONSTRAINT_S structure, to free this memory
* application has to call the X509Extn_freeBasicConstraints function.
*
* @par Note
* The value of pathlength will not be validated. Hence the application has to take care not to set the
* pathlength value greater than zero in case of end entity certificate.
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_BASIC_CONSTRAINT_S* X509Extn_createBasicConstraint(SEC_BOOL bCAFlag,SEC_INT32 iPathLength);


/**
* @defgroup X509_setCABasicConstraintMandatoryCheck
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID  X509_setCABasicConstraintMandatoryCheck(SEC_INT iEnable);
* @endcode
*
* @par Purpose
* This is used to set or reset the mandatory CA "Basic Constraint parameter" extension checking.
* For V3 Certificates the parameter "Basic Constraint" is mandatory.
* By default, this check will be enabled. If "Basic Constraint" field is not present then loading
* of the certificate will fail.
*
*  If this check is disabled then the "Basic Constraint" parameter will not be
* verified for CA certificates.
*
* @par Description
* X509_setCABasicConstraintMandatoryCheck function sets or resets the mandatory
* CA "Basic Constraint "extension checking for a CA certificate.
*
* @param[in] iEnable 1 is passed to enable the check and 0 to disable the check. [0-1]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Required Header File
* x509.h
*
* @par Note
* \n
* If the checking is enabled, it is required that the "Basic Constraint" extension be set in the
* certificate. The default is enabled.
* This API should be used in the main thread, ie it should be
* called right after the library initialization.
*
*/
PSELINKDLL SEC_VOID  X509_setCABasicConstraintMandatoryCheck(SEC_INT iEnable);

/**
* @defgroup X509_isCACert
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_isCACert(X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To check whether the given certificate is a CA certificate or not.
* @par Description
* This function is used to check whether the given certificate is a CA certificate.
* The function checks the cA field of the Basic Constraint Extension in
* the certifcate to determine whether the certificate is a CA certificate or not.
* @param[in] pstCertificate The certificate that is to be inspected [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 On successful execution SEC_TRUE or SEC_FALSE is returned [SEC_TRUE|N/A]
* @retval SEC_INT32 This is returned for a CA certificate [SEC_TRUE|N/A]
* @retval SEC_INT32 Returned for end entity certificate [SEC_FALSE|N/A]
* @retval SEC_INT32 On failure situation -1 is returned if\n
* 1> Input parameter is NULL,\n
* 2> Extension not available in certificate,\n
* 3> Decoding of the extension fails [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* If V1 or V2 certificate is passed, then the API return SEC_ERROR. Hence use 
* the alternate API SEC_PKI_isCACert which returns SEC_PKI_SUCCESS considering 
* V1 and V2 certificates as CA certificate.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509_isCACert(X509_CERT_S* pstCertificate);


/**
* @defgroup X509_getPathLen
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_getPathLen(X509_BASIC_CONSTRAINT_S* pstBasicConstraint);
* @endcode
* @par Purpose
* To fetch the path length from
* @par Description
* The function gets the path length from the certificate if the certificate is CA certificate.
* This function is used after X509_isCACert.
* This function is used during certificate path validation process.
* @param[in] pstBasicConstraint The structure from which the path length has to be returned [N/A]
* @param[out] N/A  [N/A]
* @retval SEC_INT32 On successful execution path length is returned [SEC_INT32|N/A]
* @retval SEC_INT32 On failure situation -1 is returned i.e. if Input parameter is NULL [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509_getPathLen(X509_BASIC_CONSTRAINT_S* pstBasicConstraint);


/**
* @defgroup X509Extn_createAKID
* @ingroup x509Functions
* @par Prototype
* @code
* X509_AKID_S* X509Extn_createAKID(SEC_BIGINT_S* pstCertSerialNum,
* SEC_List_S* pCertificateIssuer,
* SEC_PKEY_S* pstPublicKey,
* X509_KIDGENTYPE_E enKIDType
* );
* @endcode
* @par Purpose
* To create an authority key identifier structure.
* @par Description
* This API is used for a CA certificate. This extension is used when the CA has more than one signing keys and this extension
* helps in finding the key pair. The keyIdentifier field of the extension must be included in all certificates generated by
* confirming CAs to facilitate certification path construction. The key identifier generation is either 160 bit SHA1 hash
* value or 64 bit value.
* But the usage of this API is deprecated. Please refer the Note section for 
* further details.
* @param[in] pstCertSerialNum The unique serialNumber of the CA [N/A]
* @param[in] pCertificateIssuer The Alternate Name of the Certificate Issuer [N/A]
* @param[in] pstPublicKey The public key that has to be encoded and hash calculated on it using
* the option passed in the enKIDType argument in the function [N/A]
* @param[in] enKIDType The method of generating the KeyIdentifier [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_AKID_S* On successful execution pointer to the X509_AKID_S structure is returned [X509_AKID_S*|N/A]
* @retval X509_AKID_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:\n
* 1> Input parameters is NULL,\n
* 2> Memory allocation fails,
* 3> Encoding of Public key fails,
* 4> Hash calculation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_AKID_S structure, to free this memory
* application has to call the X509Extn_freeAKID function.
*
* @par Note
* The AKID generation using this API is not as per the standard. Hence it is 
* not interoperable with third party libraries. It is strongly recommended to 
* use the API X509Extn_createAKID_ex instead of this API.
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL X509_AKID_S* X509Extn_createAKID(SEC_BIGINT_S* pstCertSerialNum,
								 SEC_List_S* pCertificateIssuer,
								 SEC_PKEY_S* pstPublicKey,
								 X509_KIDGENTYPE_E enKIDType);


/**
* @defgroup X509Extn_getSNFromAKID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_BIGINT_S* X509Extn_getSNFromAKID(X509_AKID_S* pAKID);
* @endcode
* @par Purpose
* To fetch the serial number from the AKID
* @par Description
* Returns the Serial number from the Authority Key identifier.
* @param[in] pAKID The structure from which the serial number has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_BIGINT_S* Pointer to the serial number and length of the serial number [SEC_BIGINT_S*|N/A]
* @retval SEC_BIGINT_S* Returned if the input in NULL or the serial number is not set [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_BIGINT_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BIGINT_S* X509Extn_getSNFromAKID(X509_AKID_S* pAKID);


/**
* @defgroup X509Extn_getIssuerFromAKID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509Extn_getIssuerFromAKID(X509_AKID_S* pAKID);
* @endcode
* @par Purpose
* To fetch the certificate issuer name from the AKID.
* @par Description
* Returns the Certificate Issuer Alternate name from the Authority Key Identifier.
* @param[in] pstAKID The structure from which the Issuer Alternate Name has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Pointer to the List of AlternateName. The list is a sequence of General Names [SEC_List_S*|N/A]
* @retval SEC_List_S* Returned if the input in NULL or the Certificate Issuer name is not set [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_List_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* X509Extn_getIssuerFromAKID(X509_AKID_S* pAKID);


/**
* @defgroup X509Extn_getKIDFromAKID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509Extn_getKIDFromAKID(X509_AKID_S* pAKID);
* @endcode
* @par Purpose
* To fetch the Key Identifier from the AKID.
* @par Description
* Returns the keyIdentifier from the Authority Key Identifier extension structure.
* @param[in] pAKID The structure from which the key identifier has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_AsnOcts_S* Pointer to the KeyIdentifier structure that consists of the hash of the public key and the hash
* length [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* Returned if the input is NULL or the KID is not present [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnOcts_S.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* X509Extn_getKIDFromAKID(X509_AKID_S* pAKID);


/**
* @defgroup X509Extn_generateKID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509Extn_generateKID(SEC_UCHAR* pucPublicKey,
* SEC_UINT32 uiPubKeyLen,
* X509_KIDGENTYPE_E enType,
* SEC_UINT32* puiHashLength
* );
* @endcode
* @par Purpose
* To generate the Key Identifier structure.
* @par Description
* The function is used to generate KeyIdentifier based on the given method. This function is used for calculating the hash on the
* public key. The length of the hash value is determined by the KID generation type. The process is to encode the Public Key
* and then hash the encoded public key using SHA1 algorithm
* @param[in] pucPublicKey The encoded public key that has to be hashed depending on the method of generation [N/A]
* @param[in] uiPubKeyLen The length of the encoded public key [N/A]
* @param[in] enType The method to be used to generate the KID [N/A]
* @param[out] puiHashLength The length of the key identifier that is generated [N/A]
* @retval SEC_UCHAR* The KeyIdentifier generated [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Returned if the KID generation fails or the input data is incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the Key Identifier generated, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* X509Extn_generateKID(SEC_UCHAR* pucPublicKey,
								SEC_UINT32 uiPubKeyLen,
								X509_KIDGENTYPE_E enType,
								SEC_UINT32* puiHashLength);



/**
* @defgroup X509_createGeneralName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_GEN_NAME_S* X509_createGeneralName(SEC_List_S* pDataList);
* @endcode
* @par Purpose
* To create and populate a general name structure
* @par Description
* This function creates the SEC_GEN_NAME_S structure using the List given as input parameter.
* The GeneralName is set with one of the options supported. The list that needs to be provided as input should contain
* X509_COMMONDATA_S structure nodes. Providing invalid list or accesing the structures directly should never be done.
* Such an action will lead to undefined behaviour. The list to the function is a sequence of SEC_COMMONDATA_S structures,
* containing either a SEC_COMMONDATA_S with the List in the structure set or a String containing the data that has to be set.
* In case the type of X509_COMMONDATA_S is TYPE_URL, TYPE_DNSNAME or TYPE_RFC822NAME it should contain an IA5String.
* Options in General Name structure created with String only as input\n
* URI, All the validation for the URL has to be taken care in the application.\n
* DNSName, All the validation for the DNSName has to be taken care in the application.\n
* RFC822Name, All the validation for the RFC822Name has to be taken care in the application.\n
* IPAddress, The IPAddress is validated only for IPv4\n
* RegisteredID Input to this type will be a OID of this format. Example - 4.23.567.89  \n
* Options in GeneralName structure created with List provided as input.
* The list has to be a number of SEC_COMMONDATA_S structures only.\n
* To set EDIPartyName, ORAddress or OtherName options in GeneralName then pass the list as input that contains
* TYPE_EDIPARTYNAME, TYPE_OTHERNAME or TYPE_ORADDRESS and the list of input to set the appropriate data in those structures.\n
* In GeneralName\n
* EDIPArtyName - The list should contain either or both TYPE_NAMEASSINGER or TYPE_PARTYNAME as the type to be created
* in the SEC_COMMONDATA_S structures added to the list.\n
* TYPE_NAMEASSIGNER only does not create the structure alone, It should always go along with TYPE_PARTYNAME.\n
* OtherName - The other Name contains a AnyDefinedType value in which a structure PermanentIdentifier has to be created
* and set to the parameter value. To create PermanentIDentifier, the list can contain either or both TYPE_IDENTIFIERVALUE and
* TYPE_ASSIGNER as the types in the SEC_COMMONDATA_S structures added to the list. Both Types are optional.
* Hence any one option will create the OtherName structure.\n
* ORAddress - It is another type of struture that can give the name information in a more clearer way.
* The structure needs to be created using the the below API.The input to create the ORAddress structure is a list of common
* nodes. The user should never acces the structure directly, any creation should go through the create
* X509_createGeneralName. All input validation will be done in the internal API.
*
* @param[in] pDataList The list that contains data to create GeneralName with all options other than Directory Name.
* To create GeneralName with DirectoryName option call X509Extn_setNameToGeneralName function. The list is a sequence of
* SEC_COMMONDATA_S structures that hold the data to create the general name [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_GEN_NAME_S* Upon successful execution, a pointer to SEC_GEN_NAME_S structure is returned [SEC_GEN_NAME_S*|N/A]
* @retval SEC_GEN_NAME_S* Uponn failure, SEC_NULL is returned. The failure conditions can be one of the following:\n
* 1> Input parameter is NULL,\n
* 2> Memory Allocation fails,\n
* 3> Input data incorrect [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_GEN_NAME_S structure, to free this memory
* application has to call the X509_freeGeneralName function.
*
* @par Note
*
*- The list should contain only one common data. Even if it contains more,only the first data in the list
* will be set in the general name.
*- If the common data type is TYPE_ORADDRESS and the TYPE_ORADDRESS list contain more than one
* data of same type then first one is considered and added in the general name and the other duplicate one
* will be ignored.
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_GEN_NAME_S* X509_createGeneralName(SEC_List_S* pDataList);

/*
 enGenNameType - GeneralName Type, following types are supported
TYPE_RFC822NAME, TYPE_DNSNAME, TYPE_URL, TYPE_IPADDRESS
pucData - data
uLen - Length of the data
 
*/

/**
* @defgroup X509_createGeneralName_ex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_GEN_NAME_S* X509_createGeneralName_ex(X509_TYPE_E enGenNameType,
*              SEC_UCHAR *pucData,
*              SEC_UINT32 uLen);
* @endcode
* @par Purpose
* To create and populate a general name structure
* @par Description
* This function creates the SEC_GEN_NAME_S structure using the pucData given as input parameter.
* The GeneralName is set with one of the options supported. 
* In case the type of enGenNameType is TYPE_URL, TYPE_DNSNAME or TYPE_RFC822NAME it should contain an IA5String.
* Options in General Name structure created with String only as input\n
* URI, All the validation for the URL has to be taken care in the application.\n
* DNSName, All the validation for the DNSName has to be taken care in the application.\n
* RFC822Name, All the validation for the RFC822Name has to be taken care in the application.\n
* IPAddress, The IPAddress is validated only for IPv4\n
* The user should never acces the structure directly, any creation should go through the create
* X509_createGeneralName. All input validation will be done in the internal API.
*
* @param[in] enGenNameType The type of data to create GeneralName with the options TYPE_RFC822NAME,TYPE_DNSNAME
* TYPE_URL,TYPE_IPADDRESS [N/A]
* @param[in] pucData data [N/A]
* @param[in] uLen Length of the data [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_GEN_NAME_S* Upon successful execution, a pointer to SEC_GEN_NAME_S structure is returned [SEC_GEN_NAME_S*|N/A]
* @retval SEC_GEN_NAME_S* Uponn failure, SEC_NULL is returned. The failure conditions can be one of the following:\n
* 1> Input parameter is NULL,\n
* 2> Memory Allocation fails,\n
* 3> Input data incorrect [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_GEN_NAME_S structure, to free this memory
* application has to call the X509_freeGeneralName function.
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

PSELINKDLL SEC_GEN_NAME_S* X509_createGeneralName_ex (
               X509_TYPE_E enGenNameType,
               SEC_UCHAR *pucData,
               SEC_UINT32 uLen);

/*
Function converts the name into GeneralName
*/

/**
* @defgroup X509_createGenNameFromName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_GEN_NAME_S* X509_createGenNameFromName(SEC_NAME_S* pstName);
* @endcode
* @par Purpose
* To Create the  SEC_GEN_NAME_S structure with the Directory name option in it.
* @par Description
* This function sets the Directory name option in SEC_GEN_NAME_S structure that is part of the Issuer Alternate Name or
* Subject. For Creating the input parameter use X509_createDN.
* @param[in] pstName The name that has to be set to SEC_GEN_NAME_S Structure [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_GEN_NAME_S* The pointer to the GeneralName strucute that is set with the Directory Name option
* [SEC_GEN_NAME_S*|N/A]
* @retval SEC_GEN_NAME_S* Upon failure SEC_NULL is returned. The conditions can be one of the following: Input
* parameter is NULL or Memory allocation fails [NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_GEN_NAME_S structure, to free this memory
* application has to call the X509_freeGeneralName function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_GEN_NAME_S*  X509_createGenNameFromName(SEC_NAME_S *pstName);
/**
* @defgroup X509Extn_createExtendedKeyUsage
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509Extn_createExtendedKeyUsage(SEC_List_S* pDataList);
* @endcode
* @par Purpose
* To create the Extended key usage extension for a given certificate.
* @par Description
* This function creates the extended keyusage extension for the certificate. The list here is a list of CIDs that specifies
* the Extended Key Usages that need to be supported. The options that are allowed to create the Extended key usage are:\n
* CID_KP_SERVERAUTH\n
* CID_KP_CLIENTAUTH,\n
* CID_KP_CODESIGNING,\n
* CID_KP_EMAILPROTECTION,\n
* CID_KP_TIMESTAMPING,\n
* CID_KP_OCSPSIGNING.\n
* This extension specifies additional usage of the certificate.
* @param[in] pDataList The list of CIDs representing the extended key usage for the certificate [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Upon successful execution, extended key usage list is created with the OIDs corresponding to the CIDs
* passed as input [SEC_List_S*|N/A]
* @retval SEC_List_S* Upon failure, it returns SEC_NULL if \n
* Input parameter is NULL, \n
* Unknown key usage CID passed, \n
* Memory allocation failure [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List_S, to free this memory
* application has to call the X509Extn_freeExtendedKeyUsage function.
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

PSELINKDLL SEC_List_S* X509Extn_createExtendedKeyUsage(SEC_List_S* pDataList);


/**
* @defgroup X509Extn_createSubjectDirAttr
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509Extn_createSubjectDirAttr(SEC_List_S* pDataList);
* @endcode
* @par Purpose
* To create the Subject Alternate Directory list from the list of SEC_COMMONDATA_S structures.
* @par Description
* This API creates a list of Attribute structures. This is an extension supported by the standard. This extension is used to
* provide additional identification of the certificate user. The input list consists of a list of SEC_COMMONDATA_S
* structures.Some of the values in the Subject Directory Attributes extension are
* a) Place of Birth [ TYPE_PLACEOFBIRTH ]\n
* b) Date of Birth  [ TYPE_DOB]\n
* Date of Birth has to be a string in Generalized time format.
* Use SEC_DateTimeToGenTime to convert time to generalized time.
* The input list has to be generalized time. \n
* c) Gender [ TYPE_GENDER ] Input to this can either be (M or F or m or f)\n
* d) Country of Residence [ TYPE_COUNTRYOFCITIZENSHIP ]\n
* e) Country of CitizenShip [ TYPE_COUNTRYOFRESIDENCE ]\n
* For all the above mentioned types the SEC_COMMONDATA_S structures contain a list used to create the extension.
* Gender, CountryOfResidence and CountryOFCitizenship is always represented inIA5String format.
* @param[in] pDataList The list that contains data to create the Subject Directory Attributes list[N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Upon successful execution Subject Directory Attribute list is created [SEC_List_S*|N/A]
* @retval SEC_List_S* SEC_NULL is returned when\n
* if Input parameter is NULL, \n
* if Input data is Incorrect \n
* upon Memory allocation failure [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List_S, to free this memory
* application has to call the X509Extn_freeSubjectDirAttr function.
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

PSELINKDLL SEC_List_S* X509Extn_createSubjectDirAttr(SEC_List_S* pDataList);



/**
* @defgroup X509Extn_createPrivKeyValidity
* @ingroup x509Functions
* @par Prototype
* @code
* X509_PRIVKEY_VALIDITY_S* X509Extn_createPrivKeyValidity(DATETIME_S* pstNotBefore,
* DATETIME_S* pstNotAfter
* );
* @endcode
* @par Purpose
* To create the X509_PRIVKEY_VALIDITY_S structure given the date & time of the validity period.
* @par Description
* The function creates the Private Key Usage period. This extension is used to restrict the usage of the certificate after
* the validity period of the private key has elapsed. The extension identifies the time period from which the private key is
* usable and the time after which the private key is no longer trusted/used. The time period is converted to Generalized
* Time format. When both the inputs are SEC_NULL the structure is not created.
* @param[in] pstNotBefore The notBefore Time period of the private key [N/A]
* @param[in] pstNotAfter The notAfter Time period of the private key after which the private key is invalid [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_PRIVKEY_VALIDITY_S* On successful execution, a pointer to the X509_PRIVKEY_VALIDITY_S structure is returned
* [X509_PRIVKEY_VALIDITY_S*|N/A]
* @retval SEC_NULL On failure conditions SEC_NULL is returned. The failures conditions can be one of the following
* Input parameter is NULL, Memory Allocation fails or Time conversion fails [X509_PRIVKEY_VALIDITY_S*|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_PRIVKEY_VALIDITY_S structure, to free this memory
* application has to call the X509Extn_freePrivateKeyUsage function.
*
* @par Note
*
* The ucUTCSign,ucUTCHour,ucUTCMinute, uwMillSecond fields of DATETIME_S are not considered in this function
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL X509_PRIVKEY_VALIDITY_S* X509Extn_createPrivKeyValidity(DATETIME_S* pstNotBefore,
														DATETIME_S* pstNotAfter);


/**
* @defgroup X509Extn_extractNotAfter
* @ingroup x509Functions
* @par Prototype
* @code
* DATETIME_S* X509Extn_extractNotAfter(X509_PRIVKEY_VALIDITY_S* pstPrivKUPeriod);
* @endcode
* @par Purpose
* To extract the notAfter time period of the given private key.
* @par Description
* Returns the Time period in DATETIME_S format of notAfter time period of the private key.
* @param[in] pstPrivKUPeriod The structure from the date has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval DATETIME_S* The notAfter Time period [DATETIME_S*|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the DATETIME_S structure, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* Memory has to be deallocted after using the DATETIME_S pointer variable
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* X509Extn_extractNotAfter(X509_PRIVKEY_VALIDITY_S* pstPrivKUPeriod);



/**
* @defgroup X509Extn_extractNotBefore
* @ingroup x509Functions
* @par Prototype
* @code
* DATETIME_S* X509Extn_extractNotBefore(X509_PRIVKEY_VALIDITY_S* pstPrivKUPeriod);
* @endcode
* @par Purpose
* To fetch the notBefore time period of the given private key.
* @par Description
* Returns the Time period in DATETIME_S format of notBefore time period of the private key.
* @param[in] pstPrivKUPeriod The structure from the date has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval DATETIME_S* The notBefore Time period [DATETIME_S*|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the DATETIME_S structure, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* Memory has to be deallocted after using the DATETIME_S pointer variable
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* X509Extn_extractNotBefore(X509_PRIVKEY_VALIDITY_S* pstPrivKUPeriod);



/**
* @defgroup X509_createCommonData
* @ingroup x509Functions
* @par Prototype
* @code
* X509_COMMONDATA_S* X509_createCommonData(X509_TYPE_E enInfoType,
* SEC_UCHAR* pucDataString,
* SEC_List_S* pDataList,
* X509_STRINGTYPE_E enStrType
* );
* @endcode
* @par Purpose
* To create and populate a X509_COMMONDATA_S structure.
* @par Description
* This function creates the common data structure that is used in creation of certificate extensions.
* The data may be either as Character string or List of data items.
* If both pucDataString and pDataList is present the structure will not be created instead SEC_NULL will be returned back.
* @param[in] enInfoType The type of information for which the the structure is being created [N/A]
* @param[in] pucDataString Character string that has to be used depending on the type of previous argument [N/A]
* @param[in] pDataList The list of data for an info type to create the extension [N/A]
* @param[in] enStrType The string type is used only when the enInfoType has a string and the string type in which the
* string has to be represented [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_COMMONDATA_S* Upon successful execution, a pointer to the X509_COMMONDATA_S structure is returned [N/A|N/A]
* @retval X509_COMMONDATA_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:
* If either or both simple string and List are NULL or If Memory Allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_COMMONDATA_S structure, to free this memory
* application has to call the X509_freeCommonData function.
*
* @par Note
*
* Memory has to be deallocted after using the DATETIME_S pointer variable
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_COMMONDATA_S* X509_createCommonData(X509_TYPE_E enInfoType,
										 SEC_UCHAR* pucDataString,
										 SEC_List_S* pDataList,
										 X509_STRINGTYPE_E enStrType);



/**
* @defgroup X509Extn_createPolicyInformation
* @ingroup x509Functions
* @par Prototype
* @code
* X509_POLICY_INFO_S* X509Extn_createPolicyInformation(SEC_List_S* pCommonDataList);
* @endcode
* @par Purpose
* To create the Certificate Policy for the given certificate.
* @par Description
* This function is used to create the Certificate Policy for the certificate.
* The certificate policy can contain CPS URL, UserNotice qualifiers.
* The certificate Policy is used during certificate path validation during which only the policy that
* are acceptable is considered. Each policy has an OID associated with it. The policy is set using the TYPE_POLICYID and the
* string containing the OID. If the policy alone is not sufficient then the qualifiers are used. Each policy consists of
* CPS URI or UserNotice qualifiers.	The list is a set of SEC_COMMONDATA_S structures which are used to set CPS URI, or UserNotice
* qualifier.\n
* CPS URI - The SEC_COMMONDATA_S has the simple string containing the URI where the Certificate Policy Statements can be
* referred.Uses TYPE_CPS to create this qualifier.\n
* UserNotice - The UserNotice contains the explict text, organization text and list of numbers. To create UserNotice the
* structure contains  a list of SEC_COMMONDATA_S structures.\n
* TYPE_USERNOTICE - To create UserNotice the types to be used are TYPE_ORG_TXT, TYPE_EXPLICIT_TEXT and 	TYPE_NOTICE_NUMBERS.
* The API fails, if more than one data of the same type is tried to be added.
* @param[in] pCommonDataList The list that contains data to create the certificate policy qualifiers and stored in
* X509_POLICY_INFO_S structure [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_POLICY_INFO_S* On successful execution pointer to X509_POLICY_INFO_S structure is returned
* [X509_POLICY_INFO_S*|N/A]
* @retval X509_POLICY_INFO_S* On failure conditions SEC_NULL is returned. The failures conditions can be one of the
* following: Input parameter is NULL, Memory Allocation fails or Input data is incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_POLICY_INFO_S structure, to free this memory
* application has to call the X509Extn_freePolicyInfo function.
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

PSELINKDLL X509_POLICY_INFO_S* X509Extn_createPolicyInformation(SEC_List_S* pCommonDataList);



/**
* @defgroup X509Extn_getExplicitText
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509Extn_getExplicitText(X509_USER_NOTICE_S* pstUNotice,
* SEC_UINT32* puiStringType
* );
* @endcode
* @par Purpose
* To extract the explicit text data from the X509_USER_NOTICE_S certificate policy qualifier
* @par Description
* Extracts the explict text from the X509_USER_NOTICE_S certificate policy qualifier.
* This text is used during certificate path validation process.
* @param[in] pstUNotice The qualifier from which the text has to be retrieved [N/A]
* @param[out] puiStringType The string format in which the text has been represented [N/A]
* @retval SEC_AsnOcts_S* Pointer to the explicit Text [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If input parameter is Empty [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnOcts_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* X509Extn_getExplicitText(X509_USER_NOTICE_S* pstUNotice,
										SEC_UINT32* puiStringType);



/**
* @defgroup X509Extn_getOrganizationText
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509Extn_getOrganizationText(X509_USER_NOTICE_S* pstUNotice,
* SEC_UINT32* puiStringType
* );
* @endcode
* @par Purpose
* To fetch the organization text data from the X509_USER_NOTICE_S certificate policy qualifier.
* @par Description
* Returns the organization text from the X509_USER_NOTICE_S certificate policy qualifier. The organization text states the
* policy acceptable to an organization. This text is used during certificate path validation process
* @param[in] pstUNotice The qualifier from which the text has to be retrieved [N/A]
* @param[out] puiStringType The string format in which the text has been represented [N/A]
* @retval SEC_AsnOcts_S* Pointer to the Organization Text [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the input parameter is Empty [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnOcts_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* X509Extn_getOrganizationText(X509_USER_NOTICE_S* pstUNotice,
											SEC_UINT32* puiStringType);



/**
* @defgroup X509Extn_getNoticeNumbers
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509Extn_getNoticeNumbers(X509_USER_NOTICE_S* pstUNotice);
* @endcode
* @par Purpose
* To fetch a list of Notice Numbers from the given X509_USER_NOTICE_S structure.
* @par Description
* Returns a list of NoticeNumbers from the NoticeReference structure in the X509_USER_NOTICE_S qualifer of the certificate
* policy. The list of numbers point to the organization text that has to be referred during certificate policy verification.
* @param[in] pstUNotice The structure from which the data has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Pointer to the list of Notice reference number [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input parameter is empty or if there is no notice number list left [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_List_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* X509Extn_getNoticeNumbers(X509_USER_NOTICE_S* pstUNotice);



/**
* @defgroup X509Extn_createPolicyMappings
* @ingroup x509Functions
* @par Prototype
* @code
* X509_POLICY_MAPPING_LIST* X509Extn_createPolicyMappings(SEC_List_S* pIssuerDomPolicyList,
* SEC_List_S* pSubjectDomPolicyList
* );
* @endcode
* @par Purpose
* To identify the mapping of the policies between Subject & Issuer Domain policies.
* @par Description
* This function is used to identify the mapping of policy between the subject CA domain and other CA domain policies.
* The function creates and list with a pair of policy OIDs. The pairing indicates the issuing CA's
* issuerDomainPolicy equivalent to the subject CA's subjectDomainPolicy.
* @param[in] pIssuerDomPolicyList The list of Issuer Domain policy. This List contains the list of policies supported by
* the CA within its domain [N/A]
* @param[in] pSubjectDomPolicyList The list of Subject Domain policy equivalent to the Issuing CA domain policies [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_POLICY_MAPPING_LIST* The structure that contains the mappings of the Issuing and Subject Domain policy * [X509_POLICY_MAPPING_LIST*|N/A]
* @retval X509_POLICY_MAPPING_LIST* On failure conditions SEC_NULL is returned. The failure conditions can be one of the
* following:
* Input parameter is NULL, Memory Allocation fails or Input data is incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_POLICY_MAPPING_LIST structure, to free this memory
* application has to call the X509Extn_freePolicyMappings function.
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

PSELINKDLL X509_POLICY_MAPPING_LIST* X509Extn_createPolicyMappings(SEC_List_S*	pIssuerDomPolicyList,
												        SEC_List_S*	pSubjectDomPolicyList);


/**
* @defgroup X509Extn_getIssuerDomainPolicy
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509Extn_getIssuerDomainPolicy (X509_POLICY_MAPPING_S* pPolMapping);
* @endcode
* @par Purpose
* To fetch the Issuer Domain policy from the given policy mappings structure.
* @par Description
* This function returns the issuer domain policy from the given policy mappings structure.
* The CID returned can be used to map the Issuer policy of the CA with other CA domian policies.
* @param[in] pPolMapping Pointer to the policy mapping extension [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 Returns the equivalent CID of the issuer domain policy as the output [SEC_INT32|N/A]
* @retval SEC_INT32 If the input parameter is NULL [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509Extn_getIssuerDomainPolicy(X509_POLICY_MAPPING_S* pPolMapping);



/**
* @defgroup X509Extn_getSubjectDomainPolicy
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509Extn_getSubjectDomainPolicy(X509_POLICY_MAPPING_S* pPolMapping);
* @endcode
* @par Purpose
* To fetch the Subject Domain policy from the given policy mappings structure.
* @par Description
* This function returns the subject domain policy from the given policy mappings structure.
* The CID returned is the policy that has to be mapped against the issuing CA policies.
* @param[in] pPolMapping Pointer to the policy mapping extension [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 Returns the equivalent CID of the subject domain policy as the output [SEC_INT32|N/A]
* @retval SEC_INT32 If the input parameter is NULL [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509Extn_getSubjectDomainPolicy(X509_POLICY_MAPPING_S* pPolMapping);



/**
* @defgroup X509Extn_createPolicyConstraints
* @ingroup x509Functions
* @par Prototype
* @code
* X509_POLICY_CONSTRAINT_S* X509Extn_createPolicyConstraints(SEC_INT32 iReqExplicitPolicy,
* SEC_INT32 iInhibitPolicy
* );
* @endcode
* @par Purpose
* To create and populate a X509_POLICY_CONSTRAINT_S extension structure.
* @par Description
* The function is used to create PolicyConstraint extension. This extension constraints path validation.
* It can be used to prohibit policy mapping or require that each certificate in a path contain an acceptable policy identifier.
* This extension is used in CA certificates. If any of the Policies has to be omitted then the value to the function has to negative value.
* If both the values are negative then the structure is not created. Positive values indicate the value that has to be
* reflected in the certificate.
* @param[in] iReqExplicitPolicy The number of certificates in the entire certificate path after which
* all certificates in the path should contain a common Policy Identifier.
* Please note that the negative value should be used if this field is intended to be omitted during creation of the
* structure. It should contain a common Policy Identifier otherwise. [N/A]
* @param[in] iInhibitPolicy Indicates the number of additional certification path after which
* the policy mapping is not required
* Please note that negative value should be used if this field is intended to be omitted during creation of the structure.[N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_POLICY_CONSTRAINT_S* On successful execution pointer to X509_POLICY_CONSTRAINT_S structure is returned
* [X509_POLICY_CONSTRAINT_S*|N/A]
* @retval X509_POLICY_CONSTRAINT_S* On failure conditions SEC_NULL is returned. The failure conditions can be
* one of the following:
* Both Input parameters are negative integers or if Memory Allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_POLICY_CONSTRAINT_S structure, to free this memory
* application has to call the X509Extn_freePolicyConstraints function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_POLICY_CONSTRAINT_S* X509Extn_createPolicyConstraints(SEC_INT32 iReqExplicitPolicy,
														   SEC_INT32 iInhibitPolicy);



/**
* @defgroup X509Extn_getExplicitPolicy
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509Extn_getExplicitPolicy (X509_POLICY_CONSTRAINT_S* pPolConstraint);
* @endcode
* @par Purpose
* To fetch the Explicit policy of the given Policy constraint extension.
* @par Description
* Returns the explict policy of the X509_POLICY_CONSTRAINT_S extension in the certificate.
* This function is used during the certificate path validation.
* @param[in] pPolConstraint The structure from which explict policy has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 The explicit policy value is returned [SEC_INT32|N/A]
* @retval SEC_INT32 If the input parameter is NULL [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509Extn_getExplicitPolicy (X509_POLICY_CONSTRAINT_S* pPolConstraint);



/**
* @defgroup X509Extn_getInhibitPolicy
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509Extn_getInhibitPolicy(X509_POLICY_CONSTRAINT_S* pPolConstraint);
* @endcode
* @par Purpose
* To fetch the Inhibit policy from the given policy constraint extension.
* @par Description
* Returns the inhibit policy of the X509_POLICY_CONSTRAINT_S extension in the certificate.
* This function is used during the certificate path validation.
* The return value indicates the number of additional certificates that may appear in the path before
* policy mapping is no longer permitted.
* @param[in] pPolConstraint The structure from which inhibit policy has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 On success [The inhibit policy value is returned|N/A]
* @retval SEC_INT32 If the input parameter is NULL [-1|N/A]
*
* @par Dependency
* x509.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509Extn_getInhibitPolicy(X509_POLICY_CONSTRAINT_S* pPolConstraint);



/**
* @defgroup X509Extn_createEDIPartyName
* @ingroup x509Functions
* @par Prototype
* @code
* X509_EDI_PARTYNAME_S* X509Extn_createEDIPartyName(SEC_List_S* pDataList);
* @endcode
* @par Purpose
* To create an Electonic Document Interface(EDI) party name structure given the necessary data.
* @par Description
* This function creates the EDIPartyName structure that is part of the GeneralName Structure. The EDIPartyName consists of
* PartyName and NameAssigner fields. The input to this function is a list of SEC_COMMONDATA_S structures. The structues
* should contain only simple strings and the list member must be NULL for the types mentioned below.  This function should
* not be used for creating EDIPartyName in GeneralName structure. To set EDIPartyName in GeneralName use
* X509_createGeneralName function and provide list of X509_COMMONDATA_S as input.
* The types that has to be used to create EDIPartyName Structure are TYPE_NAMEASSIGNER and TYPE_PARTYNAME.
*
* @param[in] pDataList The list that contains the necessary data to create EDIPartyName. The List contains X509_COMMONDATA_S
* structure, that contain the data to create the EDIPartyName [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_EDI_PARTYNAME_S* On successful execution, a pointer to X509_EDI_PARTYNAME_S structure is returned
* [X509_EDI_PARTYNAME_S*|N/A]
* @retval X509_EDI_PARTYNAME_S* On failure conditions, SEC_NULL is returned. The failure conditions can be one
* of the following:
* Input parameter is NULL, Memory Allocation fails or Input data is incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_EDI_PARTYNAME_S structure, to free this memory
* application has to call the X509Extn_freeEDIPartyName function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_EDI_PARTYNAME_S* X509Extn_createEDIPartyName(SEC_List_S* pDataList);




/**
* @defgroup X509Extn_freeEDIPartyName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeEDIPartyName(X509_EDI_PARTYNAME_S* pstEDIPartyName);
* @endcode
* @par Purpose
* To free a X509_EDI_PARTYNAME_S structure.
* @par Description
* This is used to free memory for the EDIPartyName structure.
* @param[in] pstEDIPartyName Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeEDIPartyName(X509_EDI_PARTYNAME_S* pstEDIPartyName);


/**
* @defgroup X509Extn_getPartyName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509Extn_getPartyName(X509_EDI_PARTYNAME_S* pstEDIPartyName,
* SEC_UINT32* puiStringType
* );
* @endcode
* @par Purpose
* To fetch the Party Name from the EDI party name structure.
* @par Description
* Returns the PartyName from the EDIPartyName Structure. The EDIPartyName structure has to be obtained from the GeneralName Structure.
* @param[in] pstEDIPartyName The structure from which the PartyName has to be obtained [N/A]
* @param[out] puiStringType The string format in which the string is represented [N/A]
* @retval SEC_AsnOcts_S* Pointer to the Structure that contains the character string and its length [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the input is NULL or the PartyName is not set in EDIPartyName Structure [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnOcts_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* X509Extn_getPartyName(X509_EDI_PARTYNAME_S* pstEDIPartyName,
									 SEC_UINT32* puiStringType);


/**
* @defgroup X509Extn_getNameAssigner
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509Extn_getNameAssigner(X509_EDI_PARTYNAME_S* pstEDIPartyName,
* SEC_UINT32* puiStringType
* );
* @endcode
* @par Purpose
* To return the NameAssigner from the EDIPartyName structure.
*
* @par Description
* Returns the NameAssigner from the EDIPartyName Structure. The EDIPartyName structure has to be obtained from the
* GeneralName Structure.
* @param[in] pstEDIPartyName The structure from which the NameAssigner has to be obtained [N/A]
* @param[out] puiStringType The string format in which the string is represented.
* It will be any of the values of the enum enDirectoryStringChoiceId under the X509_DIRECTORY_STRING_S structure.[N/A]
* @retval SEC_AsnOcts_S* Pointer to the Structure that contains the character string and its length [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the input is NULL or the NameAssigner is not set in EDIPartyName Structure [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnOcts_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* X509Extn_getNameAssigner(X509_EDI_PARTYNAME_S* pstEDIPartyName,
										SEC_UINT32* puiStringType);


/**
* @defgroup X509Extn_createInfoAccess
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509Extn_createInfoAccess(X509_INFO_ACCESS_CHOICE_E enInfoAccessChoice,
* SEC_List_S* pAccessOIDList,
* SEC_List_S* pGenNameList
* );
* @endcode
* @par Purpose
* To create a list containing Authority Information Access structures(X509_ACCESS_DESC_S).
* @par Description
* This function is used to create AuthorityInfoAccess or SubjectInfoAccess. The list contains X509_ACCESS_DESC_S structures
* that specifies the method from where the services from the CA can be accessed in case of CA certificate or
* the information describes the type of services offered and how to access them in case of an End entity certificate.
* To create AuthorityInfoAccess the AccessOIDList should contain only CID_AD_CAISSUERS and CID_AD_OCSP.
* To create SubjectInfoAccess the AccessOIDList should contain only CID_AD_CAREPOSITORY and CID_AD_TIMESTAMPING.
* @param[in] enInfoAccessChoice The enum that indicates whether the SubjectInfoAccess or the AuthorityInfoAccess list has to
* be created [N/A]
* @param[in] pAccessOIDList The list of CIDs [N/A]
* @param[in] pGenNameList The access location from where the services can be accessed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* On successful execution, a pointer to Subject Info Access or Issuer Info Access list is returned
* [SEC_List_S*|N/A]
* @retval SEC_List_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:
* Any of the Input parameter are NULL, Memory Allocation fails or Input data is incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List_S structure, to free this memory
* application has to call the X509Extn_freeAuthorityInfoAccess function.
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

PSELINKDLL SEC_List_S* X509Extn_createInfoAccess(X509_INFO_ACCESS_CHOICE_E enInfoAccessChoice,
									  SEC_List_S* pAccessOIDList,
									  SEC_List_S* pGenNameList);



/**
* @defgroup X509CrlExtn_createAuthorityInfoAccess
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509CrlExtn_createAuthorityInfoAccess(
*                             SEC_List_S* pAccessOIDList,
*                             SEC_List_S* pGenNameList);
* @endcode
* @par Purpose
* To create a list of Authority Information Access structures(X509_ACCESS_DESC_S).
* @par Description
* This function is used to create AuthorityInfoAccess. The list contains X509_ACCESS_DESC_S structures
* that specifies the method how to locate certificates that may be useful in the construction of a valid CRL
* issuer certification path  to an appropriate trust anchor in case of crls.
*	- To create AuthorityInfoAccess for the crl, the AccessOIDList should contain only CID_AD_CAISSUERS.
* @param[in] pAccessOIDList The list of CIDs [N/A]
* @param[in] pGenNameList The access location from where the services can be accessed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* On successful execution, a pointer to Authority Info Access is returned
* [SEC_List_S*|N/A]
* @retval SEC_List_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:
* Any of the Input parameter are NULL, Memory Allocation fails or Input data is incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List_S structure, to free this memory
* application has to call the X509Extn_freeAuthorityInfoAccess function.
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
PSELINKDLL SEC_List_S* X509CRLExtn_createAuthorityInfoAccess(
                                  SEC_List_S*    pAccessOIDList,
                                  SEC_List_S*    pGenNameList);

/**
* @defgroup X509Extn_createGeneralSubTree
* @ingroup x509Functions
* @par Prototype
* @code
* X509_GEN_SUBTREE_S* X509Extn_createGeneralSubTree(SEC_GEN_NAME_S* pstGeneralName,
* SEC_UINT32 uiMinimum,
* SEC_INT32 iMaximum
* );
* @endcode
* @par Purpose
* To create and populate a General SubTree structure given the General Name and other required fields.
* @par Description
* The function is used to create the SubTree that helps in certificate path validation. The structure contains the name that
* is either added to the permitted or excluded list.
* @param[in] pstGeneralName The name that has to be either included in permitted or excluded list [N/A]
* @param[in] uiMinimum This value must be 0 [N/A]
* @param[in] iMaximum Usually does not contain any value. So the input value must be always -1.
* This is Provided for future implementations [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_GEN_SUBTREE_S* On successful execution pointer to X509_GEN_SUBTREE_S structure is returned
* [X509_GEN_SUBTREE_S*|N/A]
* @retval X509_GEN_SUBTREE_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the
* following:
* Any of the Input parameters are NULL, Memory Allocation fails or Input data is incorrect [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_GEN_SUBTREE_S structure, to free this memory
* application has to call the X509Extn_freeGeneralSubTree function.
*
* @par Note
*
* N/A
*
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_GEN_SUBTREE_S* X509Extn_createGeneralSubTree(SEC_GEN_NAME_S* pstGeneralName,
												  SEC_UINT32 uiMinimum,
												  SEC_INT32 iMaximum);


/**
* @defgroup X509Extn_createNameConstraints
* @ingroup x509Functions
* @par Prototype
* @code
* X509_NAME_CONSTRAINT_S* X509Extn_createNameConstraints(SEC_List_S* pPermittedList,
* SEC_List_S* pExcludedList
* );
* @endcode
* @par Purpose
* To create the Name Constraints Structure given the list of names to be permitted and excluded.
* @par Description
* This function creates the Name Constraints structure that contains the Permitted and Excluded subtrees that indicates a
* name space with all subject names in subsequent certificates in a certification path. This extension is only used
* in CA certificate. This extension consists of the list of permitted and excluded certificate names that has to be verified
* during path validation. If the certificate name is in the excluded list then certificate is invalid. Each of the permitted
* and excluded name in the NameConstraint consists of GeneralSubTree. The minimum value in the SubTree is usually 0
* and maximum is not used, hence the value for maximum has to be always -1
* @param[in] pPermittedList The list of names that are permitted in the certification path [N/A]
* @param[in] pExcludedList The list of names that are excluded in the certification path [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_NAME_CONSTRAINT_S* On successful execution pointer to X509_NAME_CONSTRAINT_S structure is returned * [X509_NAME_CONSTRAINT_S*|N/A]
* @retval X509_NAME_CONSTRAINT_S* On failure conditions SEC_NULL is returned. The failures conditions can be one of the
* following:
* Input parameter is NULL or Memory Allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_NAME_CONSTRAINT_S structure, to free this memory
* application has to call the X509Extn_freeNameConstraint function.
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

PSELINKDLL X509_NAME_CONSTRAINT_S* X509Extn_createNameConstraints(SEC_List_S* pPermittedList,
													   SEC_List_S* pExcludedList);


/**
* @defgroup X509Extn_getPermittedSubTree
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509Extn_getPermittedSubTree(X509_NAME_CONSTRAINT_S* pstNameConstr);
* @endcode
* @par Purpose
* To fetch the list of permitted names from the Name constraint structure.
* @par Description
* Returns the permitted list of names from the structure. The list is used during certificate path validation process.
* @param[in] pstNameConstr The structure from which the permitted list has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Pointer to the List of Permitted Names in the certificate path [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_List_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* X509Extn_getPermittedSubTree(X509_NAME_CONSTRAINT_S* pstNameConstr);


/**
* @defgroup X509Extn_getExcludedSubTree
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509Extn_getExcludedSubTree(X509_NAME_CONSTRAINT_S* pstNameConstr);
* @endcode
* @par Purpose
* To fetch the list of Excluded names from a Name constraint structure.
* @par Description
* Gets the excluded list of names from the structure. The list is used during certificate path validation process.
* @param[in] pstNameConstr The structure from which the excluded list has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Pointer to the List of Excluded Names in the certificate path [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_List_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* X509Extn_getExcludedSubTree(X509_NAME_CONSTRAINT_S* pstNameConstr);


/**
* @defgroup X509Extn_createDPN
* @ingroup x509Functions
* @par Prototype
* @code
* X509_DPN_S* X509Extn_createDPN(X509_NAMECHOICE_E enNameChoice,SEC_VOID* pstName);
* @endcode
* @par Purpose
* To create and populate a DPN structure given the required name to be set and also the DistributionPointNameChoiceId.
* @par Description
* Creates the DistributionPointName structure that contains the the name of the CRL issuer[Issuer Alternate Name]. This
* Structure is part of the CRL DistributionPoint extension which is present in the CA certificate.
* @param[in] enNameChoice The enum that specifies which name has to be set in the structure variable [N/A]
* @param[in] pstName The name that has to be set. The pstName can be either the RelativeDistinguishedName or the FullName
* i.e, the AlternateName (list of General Name) [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_DPN_S* The structure that contains the name of of the CRL Issuer. The name can be either the Full Name or the
* Relative distinguished Name of the CA that has issued the CRL [X509_DPN_S*|N/A]
* @retval X509_DPN_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:
* Any of the Input parameters are NULL or Memory Allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_DPN_S structure, to free this memory
* application has to call the X509Extn_freeDistPointName function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_DPN_S* X509Extn_createDPN(X509_NAMECHOICE_E enNameChoice,SEC_VOID* pstName);



/**
* @defgroup X509Extn_createDP
* @ingroup x509Functions
* @par Prototype
* @code
* X509_DP_S* X509Extn_createDP(X509_DPN_S* pstDistPointName,
* SEC_UINT32 uiReason,
* SEC_List_S* pGenNamesList
* );
* @endcode
* @par Purpose
* To create and populate a X509_DP_S structure given the required fields.
*
* @par Description
* X509_DP_S, the CRL Distribution point, indicates where and how the CRL can be accessed. The structure also contains the
* reasons for the creation of CRL along with the CRL Issuer Name. The CRLIssuer field is filled when the CRL is
* generated by a different CA. The reason flags has to be present with either The CRLIssuer or the DistributionPointName.
* The Distribution Point must consist of either of the following combinations:\n
* X509_DPN_S and reasons\n
* CRL Issuer and reasons\n
* X509_DPN_S, CRL Issuer and reasons
*
* @param[in] pstDistPointName The structure that contains the RelativeDistinguishedName or FullName of the CRL issuer [N/A]
* @param[in] uiReason The reason associated with the CRL that is generated by the CRL Issuer [N/A]
* @param[in] pGenNamesList CRL Issuer Alternate name if the CRL is issued by a CA that has not created the certificate [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_DP_S* Pointer to the created Structure. This structure is added to the CRL Distribution Point List [X509_DP_S*|N/A]
* @retval X509_DP_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:\n
* 1. Any of the input parameters are NULL\n
* 2. Memory Allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_DP_S structure, to free this memory
* application has to call the X509Extn_freeDistPoint function.
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

PSELINKDLL X509_DP_S* X509Extn_createDP(X509_DPN_S*  pstDistPointName,
							 SEC_UINT32	  uiReason,
							 SEC_List_S*  pGenNamesList);



/**
* @defgroup X509Extn_getCRLIssuerFromDistPoint
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* X509Extn_getCRLIssuerFromDistPoint(X509_DP_S* pstDistPoint);
* @endcode
* @par Purpose
* To fetch the CRL Issuer from the X509_DP_S structure.
* @par Description
* This function returns the CRL Issuer which is a list of GeneralName from DistributionPoint structure
* @param[in] pstDistPoint Pointer to the dist point structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to the CRLIssuer [SEC_List_S*|N/A]
* @retval SEC_List_S* When input is NULL or the CRL Issuer is not set [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_List_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* X509Extn_getCRLIssuerFromDistPoint(X509_DP_S* pstDistPoint);



/**
* @defgroup X509Extn_getDPNFromDistPoint
* @ingroup x509Functions
* @par Prototype
* @code
* X509_DPN_S* X509Extn_getDPNFromDistPoint(X509_DP_S* pstDistPoint);
* @endcode
* @par Purpose
* To fetch the Distribution point name from the Distribution point structure.
* @par Description
* This function gets the distribution point name from the given X509_DP_S structure.
* @param[in] X509_DP_S* pstDistPoint pointer to the distribution structure [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_DPN_S* Pointer to the X509_DPN_S structure variable in DistributionPoint [X509_DPN_S*|N/A]
* @retval X509_DPN_S* When input is NULL or the DistributionPoint is not set [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the X509_DPN_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_DPN_S* X509Extn_getDPNFromDistPoint(X509_DP_S* pstDistPoint);


/**
* @defgroup X509Extn_getReasonFromDistPoint
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509Extn_getReasonFromDistPoint(X509_DP_S* pstDistPoint);
* @endcode
* @par Purpose
* To fetch the CRL reason from the X509_DP_S structure.
* @par Description
* This function gets the CRL reason from distribution point name structure.
* The reasons specifies the reason for which the CRL has been generated.
* @param[in] pstDistPoint pointer to the distribution strcuture [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 Returns the reason from the structure [SEC_INT32|N/A]
* @retval SEC_INT32 If the input parameter is NULL [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509Extn_getReasonFromDistPoint(X509_DP_S* pstDistPoint);



/**
* @defgroup X509_encodeCert
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_encodeCert(X509_CERT_S* pstCertificate,SEC_UINT32* puiEncodedLen);
* @endcode
* @par Purpose
* To encode the given certificate.
*
* @par Description
* This function performs the encoding of the certificate.
*
* @param[in] pstCertificate The certificate that has to be encoded [N/A]
* @param[out] puiEncodedLen The length of the encoded certificate [N/A]
*
* @retval SEC_UCHAR* Pointer to the DER Encoded character stream of Certificate [N/A|N/A]
* @retval SEC_UCHAR* On failure conditions SEC_NULL is returned.
* The failure conditions can be one of the following:\n
* 1. Encoding of the certificate fails\n
* 2. Memory allocation fails\n
* 3. Input parameter is NULL [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded certificate, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* X509_encodeCert(X509_CERT_S* pstCertificate,SEC_UINT32* puiEncodedLen);



/**
* @defgroup X509_decodeCert
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CERT_S* X509_decodeCert(SEC_UCHAR* pucEncodedCertificate,
* SEC_UINT32 uiEncodedLength,
* SEC_UINT32* puiDecodedLength);
* @endcode
* @par Purpose
* To generate a decoded X509 Certificate from a DER encoded certificate.
*
* @par Description
* This function returns a pointer to certificate structure after decoding the input data
* passed to this function using the first parameter.
*
* @param[in] pucEncodedCertificate The encoded certificate data that has to be decoded [N/A]
* @param[in] uiEncodedLength The length of the encoded character stream [N/A]
* @param[out] puiDecodedLength Bytes that is decoded [N/A]
*
* @retval X509_CERT_S* The certificate structure after decoding [X509_CERT_S*|N/A]
* @retval X509_CERT_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:\n
* 1. Decoding of the certificate fails\n
* 2. Memory allocation fails\n
* 3. Input parameter is NULL [SEC_NULL|N/A]	 	
*		
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_CERT_S structure, to free this memory
* application has to call the X509_freeCert function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_CERT_S* X509_decodeCert(SEC_UCHAR* pucEncodedCertificate,
							 SEC_UINT32 uiEncodedLength,
							 SEC_UINT32* puiDecodedLength);



/**
* @defgroup X509_genCertFingerPrint
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_genCertFingerPrint(X509_CERT_S* pstCertificate,
* SEC_UINT32 uiHashAlgo,
* SEC_UINT32* uiHashLength
* );
* @endcode
* @par Purpose
* This function generates the fingerprint of the certificate.
* @par Description
* The certificate is encoded and then hash on the encoded character string is calculated.
* The hash algorithms to be used are one of the following: CID_MD5, CID_SHA1, CID_SHA256,
* CID_SHA384, CID_SHA512, or CID_SHA224
* @param[in] pstCertificate The certificate on which the hash has to be calculated [N/A]
* @param[in] uiHashAlgo Hash Algorithm that is used to generate the hash of the certificate [N/A]
* @param[out]uiHashLength The length of the hash value on the encoded certificate [N/A]
* @retval SEC_UCHAR* On successful completion the hash value obtained on the certificate is returned [N/A|N/A]
* @retval SEC_UCHAR* If any of the input parameters are NULL or memory allocation fails or
* decode of the certificate fails or uiHashAlgo is not a valid Hash Algorithm [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the generated finger print, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* X509_genCertFingerPrint(X509_CERT_S* pstCertificate,
								   SEC_UINT32 uiHashAlgo,
								   SEC_UINT32* uiHashLength);



/**
* @defgroup X509_searchByName
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CERT_S* X509_searchByName(SEC_List_S* pCertList,
* SEC_NAME_S* pstName);
* @endcode
* @par Purpose
* To search for a certificate in a list based on the subject name.
* @par Description
* The function is used to find the certicate in a list based on the subject name.
* The name is compared against the issuer name from the list of certificates.
* If the name matches then return the pointer to the certificate that matches the name.
* The list can contain a list of CA certificates that can be used by the application to
* check whether the Certificate is issued by one of the trusted Certificate authority.
* @param[in] pCertList The list of certificates whose issuer name has to be compared against
* the name given as part of input [N/A]
* @param[in] pstName The name that has to be compared [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_CERT_S* The pointer to the certificate that matches the the name [N/A|N/A]
* @retval X509_CERT_S* On failure conditions SEC_NULL is returned. Failure conditions are:\n
* If none of the certificates in the list matches the given name or if
* any of the Input parameters are NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the X509_CERT_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_CERT_S* X509_searchByName(SEC_List_S* pCertList,SEC_NAME_S* pstName);



/**
* @defgroup X509_searchByIssuerAndSerial
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CERT_S* X509_searchByIssuerAndSerial(SEC_List_S* pCertList,
* SEC_NAME_S* pstIssuerName,
* SEC_BIGINT_S* pstSerialNumber
* );
* @endcode
* @par Purpose
* To search for a certificate in a list based on the issuer name & serial number.
* @par Description
* The function is used to find the certificate in a list based on the issuer name and serial number. The name and serial
* number passed as input are compared against the issuer name and serial number in the list of certificates. If both name and
* serial number matches then the pointer to the certificate that matches the name and serial number is returned.
* The list can contain a list of CA certificates that can be used by the application to check whether the Certificate is issued by one of
* the trusted Certificate authority.
* @param[in] pCertList The list of certificates whose issuer name and serial number that has to be compared against the name
* given as part of input [N/A]
* @param[in] pstIssuerName The Issuer name that has to be compared [N/A]
* @param[in] pstSerialNumber Serial number that has to be compared against the certificate in the list [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_CERT_S* The pointer to the certificate that mathces the name and serial number [N/A|N/A]
* @retval X509_CERT_S* On failure conditions SEC_NULL is returned. Failure conditions are
* 1. If none of the certificate in the list matches the serial number and name.
* 2. Input parameter is NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the X509_CERT_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_CERT_S* X509_searchByIssuerAndSerial(SEC_List_S* pCertList,
										  SEC_NAME_S* pstIssuerName,
										  SEC_BIGINT_S* pstSerialNumber);



/**
* @defgroup X509_verifySignature
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_verifySignature(X509_CERT_S* pstCertificate,SEC_PKEY_S* pstPublicKey);
* @endcode
* @par Purpose
* To verify the signature on a certificate.
* @par Description
* The function takes the certificate and the public key and verifies the signature on the certificate. Before
* calling this API use X509_extractPublicKey to get the public key from the certificate. The process is to verify the
* signature field in the certificate structure with the public key using the signature algorithm mentioned in the
* certificate. To verify an End entity certificate with DSA or ECDSA key. The parameters have to be retrieved from the CA
* certificate and have to be set to the publickey decoded from the certificate using CRYPT_PKEY_getAlgParams. For RSA the
* certificate can be validation by decoding the public key using X509_extractPublicKey API and calling this API.
* @param[in] pstCertificate The certificate to be verified [N/A]
* @param[in] pstPublicKey The public key using which the signature has to be verified [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_UINT32 On successful verification of the certificate, SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input is NULL or incorrect [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Encoding of the certificate fails [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Signature verification fails [SEC_ERR_SIGN_VERIFY_FAILED|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_verifySignature(X509_CERT_S* pstCertificate,SEC_PKEY_S* pstPublicKey);



/**
* @defgroup X509_addCertToList
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_addCertToList(X509_CERT_S* pstCertificate, SEC_List_S* pCertList);
* @endcode
* @par Purpose
* To add a new certificate to an existing Certificate list.
* @par Description
* This function adds a certificate to the certificate List. The certificate passed as input is duplicated and added to the
* list. The list has to be created by the user before adding a certificate to the list.
* @param[in] pstCertificate The certificate that has to be added [N/A]
* @param[in] pCertList The list that contains the trusted certificate list [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_UINT32 On successful execution SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input pointer is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Duplication of the certificate fails [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_addCertToList(X509_CERT_S* pstCertificate, SEC_List_S* pCertList);



/**
* @defgroup X509_delCertByName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_delCertByName(SEC_NAME_S* pSearchName,SEC_List_S* pCertList);
* @endcode
* @par Purpose
* To remove a certificate from an existing Certificate list given the certificate name.
* @par Description
* This function is used to delete certificate(s) from the list based on Issuer Name.
* @param[in] pSearchName The name on which the certificate has to be deleted [N/A]
* @param[in] pCertList The list of certificates in which the name is compared [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 On successful execution returns the number of certificates deleted [SEC_INT32|N/A]
* @retval SEC_INT32 If the input parameter is NULL [-1|N/A]
* @par Dependency
* x509.h
* @par Note
* All the matching certificates in the list will be deleted.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509_delCertByName(SEC_NAME_S* pSearchName,SEC_List_S* pCertList);



/**
* @defgroup X509_delCertBySN
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_delCertBySN(SEC_BIGINT_S* pstSerailNum,SEC_List_S* pCertList);
* @endcode
* @par Purpose
* To remove a Certificate from an existing Certificate list given its serial number.
* @par Description
* This function is used to delete a certificate from the list based on the certificate serial number.
* @param[in] pstSerailNum The serial number of the certificate that has to be searched and deleted [N/A]
* @param[in] pCertList The list of certificates from which the serial number is compared [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 On successful execution returns the number of certificates deleted [SEC_INT32|N/A]
* @retval SEC_INT32 If the input parameter is NULL [-1|N/A]
* @par Dependency
* x509.h
* @par Note
* All the matching certificates in the list will be deleted.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509_delCertBySN(SEC_BIGINT_S* pstSerailNum,SEC_List_S* pCertList);



/**
* @defgroup X509_compareSN
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_compareSN (SEC_BIGINT_S* pstSrcSerialNum,SEC_BIGINT_S* pstDestSerialNum);
* @endcode
* @par Purpose
* To compare two serial numbers.
* @par Description
* Compares whether two serial numbers are the same or different.
* @param[in] pstSrcSerialNum The source serial number [N/A]
* @param[in] pstDestSerialNum The target serial number that has to be compared with the source[N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 If the serial number matches [SEC_SUCCESS|N/A]
* @retval SEC_INT32 Upon failure in execution, SEC_ERROR is returned. The failure conditions can be one of the below:
* Any of the Input parameters are NULL or If the serial numbers do not match [SEC_ERROR|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509_compareSN (SEC_BIGINT_S* pstSrcSerialNum,SEC_BIGINT_S* pstDestSerialNum);



/**
* @defgroup X509_freeCert
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeCert(X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To free an X509_CERT_S structure.
* @par Description
* This function is used to deallocate memory for the given X509 certificate structure.
* @param[in] pstCertificate The certificate structure whose memory has to be deallocated [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This function does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeCert(X509_CERT_S* pstCertificate);


/**
* @defgroup X509_createAlgId
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_ALG_IDENTIFIER_S* X509_createAlgId(SEC_UINT32 uiAlgoID, SEC_VOID* pstParameter);
* @endcode
* @par Purpose
* To create the algorithm identifier structure with the given parameter and algorighm ID.
* @par Description
* This function is used to create the algorithm identifier structure with the parameter and CID of the algorithm. The OID of
* the algorithm is obtained inside the function.
* @param[in] uiAlgoID The integer value(CID) for the Algorithm. For All the signing algorithms the parameters
* are directly taken from the public key and so parameter should be NULL. The signature algorithms to be set are one of the
* following.
* ALGID_MD5WITHRSA
* ALGID_SHA1WITHRSA
* ALGID_SHA1WITHRSAOLD
* ALGID_DSA_WITH_SHA1
* ALGID_DSAWITHSHA1_2
* ALGID_ECDSA_WITH_SHA1
* ALGID_ECDSA_WITH_SHA224
* ALGID_ECDSA_WITH_SHA256
* ALGID_ECDSA_WITH_SHA384
* ALGID_ECDSA_WITH_SHA512
* ALGID_SHA256WITHRSAENCRYPTION
* ALGID_SHA384WITHRSAENCRYPTION
* ALGID_SHA512WITHRSAENCRYPTION
* ALGID_SM2DSA_WITH_SM3
* ALGID_SM2DSA_WITH_SHA1
* ALGID_SM2DSA_WITH_SHA256
* @param[in] pstParameter The parameter that has to be filled in the parameter field of the algorithm identifier. For the
* signing algorithms the parameter is null and is taken from the Public Key [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_ALG_IDENTIFIER_S* Algorithm structure that is returned [N/A|N/A]
* @retval SEC_ALG_IDENTIFIER_S* If the input parameter is NULL [SEC_NULL|N/A]
* @retval SEC_ALG_IDENTIFIER_S* Algorithm Identifier mapping fails [SEC_NULL|N/A]
* @retval SEC_ALG_IDENTIFIER_S* Memory Allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_ALG_IDENTIFIER_S structure, to free this memory
* application has to call the X509_freeAlgId function.
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

PSELINKDLL SEC_ALG_IDENTIFIER_S* X509_createAlgId(SEC_UINT32 uiAlgoID, SEC_VOID* pstParameter);



/**
* @defgroup X509_getCIDFromAlgId
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_INT32 X509_getCIDFromAlgId(SEC_ALG_IDENTIFIER_S*  pstAlgoId);
* @endcode
* @par Purpose
* To fetch the CID corresponding to a particular Algorithm Identifier.
* @par Description
* Returns the integer representation(CID) of the algorithm set in the algorithm identifier structure.
* @param[in] pstAlgoId The structure from which the OID value has to be converted to integer [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_INT32 The integer value equivalent for the Object Identifier(OID) of the Algorithm [SEC_INT32|N/A]
* @retval SEC_INT32 When the input parameter is NULL [-1|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 X509_getCIDFromAlgId(SEC_ALG_IDENTIFIER_S*  pstAlgoId);



/**
* @defgroup X509_getParamFromAlgId
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID* X509_getParamFromAlgId(SEC_ALG_IDENTIFIER_S* pstAlgoId);
* @endcode
* @par Purpose
* To get the parameter structure corresponding to a particular Algorithm Identifier structure.
* @par Description
* This function gets the parameter structure corresponding to the algorithm set in the algorithm structure.
* The parameter for signing algorithms can be mapped using the CID that is obtained using X509_getCIDFromAlgId API.\n
* SIGNING ALGORITHM 	- PARAMETER\n
* DSA 					- DSA_PARA_S\n
* ECDSA 				- EC_PARA_S\n
* @param[in] pstAlgoId The Algorithm Identifier structure from which the parameter has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID* The pointer to the parameter value of the Algorithm identifier [SEC_VOID*|N/A]
* @retval SEC_VOID* If the input Parameter is NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the parameters.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID* X509_getParamFromAlgId(SEC_ALG_IDENTIFIER_S* pstAlgoId);



/**
* @defgroup X509_createPubKeyInfo
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_PUBKEY_INFO_S* X509_createPubKeyInfo(SEC_PKEY_S* pstPubKey);
* @endcode
* @par Purpose
* To create the SEC_PUBKEY_INFO_S structure using the given public key.
* @par Description
* The function creates the SubjectPublicKeyInfo structure which takes the algorithm and the Public Key that
* has to be encoded and stored in the structure.The Public Key is encoded and stored
* in the structure along with the Object Identifier of the key generation algorithm.
* @param[in] pstPubKey The public key that si to be used to generate the Subject Public Key Info.[N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_PUBKEY_INFO_S* On Successful execution pointer to SEC_PUBKEY_INFO_S structure is returned
* [SEC_PUBKEY_INFO_S*|N/A]
* @retval SEC_PUBKEY_INFO_S* On all failure conditions SEC_NULL is returned. The failure conditons can be one of the
* following:
* Input parameter is NULL, Memory allocation fails or Encoding of Public Key fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_PUBKEY_INFO_S structure, to free this memory
* application has to call the X509_freePubKeyInfo function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_PUBKEY_INFO_S* X509_createPubKeyInfo(SEC_PKEY_S* pstPubKey);



/**
* @defgroup X509_encodePubKeyInfo
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_encodePubKeyInfo(SEC_PUBKEY_INFO_S* pstPubkKeyInfo,
* SEC_UINT32 *puiEncodedLen
* );
* @endcode
* @par Purpose
* To encode the Public Key Info structure.
* @par Description
* This function encodes the PublicKeyInfo structure. The PublicKeyInfo structure contains the Public Key and Algorithm
* Identifier which specifies the algorithm used to generate the key. Encoded length is reflected in puiEncodedLen
* parameter after encoding.
* @param[in] pstPubkKeyInfo The structure to be encoded [N/A]
* @param[out] puiEncodedLen The length of the encoded string [N/A]
* @retval SEC_UCHAR* Pointer to the encoded string [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* On all failure conditions SEC_NULL is returned. The failure conditons can be one of the following:
* Input parameter is NULL, Memory allocation fails or Encoding of the Public Key fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded PubKey Info, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* X509_encodePubKeyInfo(SEC_PUBKEY_INFO_S* pstPubkKeyInfo,
								 SEC_UINT32 *puiEncodedLen);



/**
* @defgroup X509_decodePubKeyInfo
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_PUBKEY_INFO_S* X509_decodePubKeyInfo(SEC_UCHAR* pucBuffer,
* SEC_UINT32 uiEncodedLength,
* SEC_UINT32* puiDecodedLen
* );
* @endcode
* @par Purpose
* To generate a SEC_PUBKEY_INFO_S structure from the encoded PublicKeyInfo data.
* @par Description
* This function returns pointer to SubjectPublicKeyInfo structure by decoding using the input parameter passed to this
* function. The PublicKeyInfo structure contains the Public Key and Algorithm Identifier.
* @param[in] pucBuffer The encoded PublicKeyInfo data that has to be decoded [N/A]
* @param[in] uiEncodedLength The length of the encoded character stream [N/A]
* @param[out] puiDecodedLen Number of Bytes that is decoded [N/A]
* @retval SEC_PUBKEY_INFO_S* On Successful execution pointer to SEC_PUBKEY_INFO_S structure is returned after decoding
* [SEC_PUBKEY_INFO_S*|N/A]
* @retval SEC_PUBKEY_INFO_S* On all failure conditions SEC_NULL is returned. The failure conditons can be one of the
* following:
* Input parameter is NULL, Memory allocation fails or Decoding of input data fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_PUBKEY_INFO_S structure, to free this memory
* application has to call the X509_freePubKeyInfo function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_PUBKEY_INFO_S* X509_decodePubKeyInfo(SEC_UCHAR* pucBuffer,
										 SEC_UINT32 uiEncodedLength,
										 SEC_UINT32* puiDecodedLen);


/**
* @defgroup X509_getAlgIdFromPubKeyInfo
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_ALG_IDENTIFIER_S* X509_getAlgIdFromPubKeyInfo(SEC_PUBKEY_INFO_S* pstSubjPKInfo);
* @endcode
* @par Purpose
* To extract the Algorithm ID structure from Public Key Info structure.
* @par Description
* This fucntion gets the Algorithm Identifier structure from the SubjectPuclicKeyInfo. The SubjectPuclicKeyInfo contains the
* algorithm used to create the public key. The algorithm used may be RSA, DSA, ECDSA,DH etc.
* @param[in] pstSubjPKInfo Structure from which the algorithm has to be extracted [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_ALG_IDENTIFIER_S* The algorithm that is used to generate public key [SEC_ALG_IDENTIFIER_S*|N/A]
* @retval SEC_ALG_IDENTIFIER_S* If the input is NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_ALG_IDENTIFIER_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ALG_IDENTIFIER_S* X509_getAlgIdFromPubKeyInfo(SEC_PUBKEY_INFO_S* pstSubjPKInfo);


/**
* @defgroup X509_setSN
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32 X509_setSN(SEC_BIGINT_S* pstSerialNumber,
* X509_CERT_S* pstCertificate);
* @endcode
* @par Purpose
* To set the serial number to a given x509 certificate structure.
* @par Description
* This function is used to set the serial number. The serial number has to be a unique number.
* The input to the function is a SEC_BIGINT_S structure that is a hexadecimal string.
* The function to convert a numberic string to hexadecimal string is SEC_cvtToBigInt.
* @param[in] pstSerialNumber The certificate serial number that has to be set in the certificate [N/A]
* @param[in] pstCertificate The certificate to which the serial number has to be set [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_UINT32 Error code when input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Error when memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 When serial number is set successfully [SEC_SUCCESS|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 X509_setSN(SEC_BIGINT_S* pstSerialNumber,
					  X509_CERT_S* pstCertificate);


/**
* @defgroup X509_encodeName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_encodeName(SEC_NAME_S* pstName,
* SEC_UINT32* uiReturnEncodedLen
* );
* @endcode
* @par Purpose
* To encode the given SEC_NAME_S structure.
* @par Description
* The function performs the encoding of the name structure. The length of the encoded name is reflected in uiReturnEncodedLen
* parameter.
* @param[in] pstName The name to be encoded [N/A]
* @param[out] uiReturnEncodedLen The length of the encoded data [N/A]
* @retval SEC_UCHAR* pointer to the encoded name buffer [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* when memory allocation or encoding of name fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded name, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* X509_encodeName(SEC_NAME_S* pstName,
						   SEC_UINT32* uiReturnEncodedLen);


/**
* @defgroup X509_decodeName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_NAME_S*  X509_decodeName( SEC_UCHAR* pstDERCodeOfName,
* SEC_UINT32 uiEncNameLen,
* SEC_UINT32* puiReturnDecodedLen
* );
* @endcode
* @par Purpose
* To generate a decoded SEC_NAME_S Structure from the encoded name buffer.
* @par Description
* The function performs the decoding of name structure. The length of the encoded name is passed in uiEncNameLen parameter.
* The decoded length is returned in puiReturnDecodedLen.
* @param[in] pstDERCodeOfName The encoded name as a string [N/A]
* @param[in] uiEncNameLen Length of the encoded string [N/A]
* @param[out] puiReturnDecodedLen The length of the decoded data [N/A]
* @retval SEC_NAME_S* Pointer to decoded name [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* Returns when memory allocation or encode of name fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_NAME_S structure, to free this memory
* application has to call the X509_freeName function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_NAME_S*  X509_decodeName( SEC_UCHAR*	pstDERCodeOfName,
							  SEC_UINT32    uiEncNameLen,
							  SEC_UINT32*	puiReturnDecodedLen);


/**
* @defgroup X509_freeCommonData
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeCommonData(X509_COMMONDATA_S* pstCommonData);
* @endcode
* @par Purpose
* To free a X509_COMMONDATA_S structure.
* @par Description
* This is Used to free memory for the CommonData structure variable
* @param[in] pstCommonData Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeCommonData(X509_COMMONDATA_S* pstCommonData);



/**
* @defgroup X509Extn_setNameToGeneralName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_GEN_NAME_S* X509Extn_setNameToGeneralName(SEC_NAME_S* pstName);
* @endcode
* @par Purpose
* To set the Directory name option in SEC_GEN_NAME_S structure.
* @par Description
* This function sets the Directory name option in SEC_GEN_NAME_S structure that is part of the Issuer Alternate Name or
* Subject. For Creating the input parameter use X509_createDN.
* @param[in] pstName The name that has to be set to SEC_GEN_NAME_S Structure [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_GEN_NAME_S* The pointer to the GeneralName strucute that is set with the Directory Name option
* [SEC_GEN_NAME_S*|N/A]
* @retval SEC_GEN_NAME_S* Upon failure SEC_NULL is returned. The conditions can be one of the following: Input
* parameter is NULL or Memory allocation fails [NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_GEN_NAME_S structure, to free this memory
* application has to call the X509_freeGeneralName function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_GEN_NAME_S* X509Extn_setNameToGeneralName(SEC_NAME_S* pstName);



/**
* @defgroup X509Extn_createSKID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509Extn_createSKID(SEC_PKEY_S* pstPublicKey,
* X509_KIDGENTYPE_E enKIDGenType);
* @endcode
* @par Purpose
* To create and populate a Subject Key Identifier structure.
* @par Description
* This function generates the SubjectKeyIdentifier given the Public key and the mode in which the key identifier has to be
* generated.  The mode can be either SHA1 160 bits or 64 bits. Returns hash value of the public key along with the length.
* But the usage of this API is deprecated. Please refer the Note section for 
* further details.
* @param[in] pstPublicKey The public key that has to be encoded upon which hash has to be generated [N/A]
* @param[in] enKIDGenType The method of generating the the KeyIdentifier [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_AsnOcts_S* On successful execution the hash of the PublicKey is returned along with its length
* [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* Upon failure SEC_NULL is returned. The conditions can be one of the following:
* Input parameter is NULL, Encoding of the PublicKey fails, Hash operation on encoded public key fails or Memory allocation
* fails [NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_AsnOcts_S structure, to free this memory
* application has to call the SEC_freeAsnOcts function.
*
* @par Note
* The SKID generation using this API is not as per the standard. Hence it is 
* not interoperable with third party libraries. It is strongly recommended to 
* use the API X509Extn_createSKID_ex instead of this API.
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_AsnOcts_S* X509Extn_createSKID(SEC_PKEY_S* pstPublicKey,
								   X509_KIDGENTYPE_E enKIDGenType);



/**
* @defgroup X509_getAttrFromName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509_getAttrFromName(SEC_UINT32 uiAttrType,
* SEC_NAME_S* pstName,
* SEC_UINT32* puiStringType
* );
* @endcode
* @par Purpose
* To extract the value of a particular attribute in the given name structure.
* @par Description
* This function returns the pointer to the Attribute value for a given attribute type present in the name structure.
* The attribute type can be any of the type supported in Name Structure. The Types include
* Country, [TYPE_COUNTRY]\n
* Organization, [TYPE_ORGANIZATION]\n
* Organization Unit Name, [TYPE_ORG_UNIT_NAME]\n
* DNQualifier, [TYPE_DNQUALIFIER]\n
* State, [TYPE_STATE ]\n
* Serial Number, [TYPE_SERIAL_NUMBER]\n
* Locality, [TYPE_LOCALITY]\n
* Title, [TYPE_TITLE \n
* Surname, [TYPE_SURNAME \n
* GivenName, [TYPE_GIVENNAME]\n
* Initials, [TYPE_INITIALS \n
* Pseudonym, [TYPE_PSEUDONYM \n
* Generation Qualifier, [TYPE_GENQUALIFIER]\n
* Email Address, [TYPE_EMAIL ]
* Domain Component, [TYPE_DOMAIN_COMPONENT]\n
* Common Name [TYPE_COMMON_NAME] and\n
* Name [TYPE_NAME]
* For all these type Enum X509_NAME_ATTR_TYPE_E has been declared.
* @param[in] uiAttrType The Attribute type that has to be searched in the name structure [N/A]
* @param[in] pstName The name from which the information has to be retrieved [N/A]
* @param[out] puiStringType The string type that is used to to represent in the name structure [N/A]
* @retval SEC_AsnOcts_S* Pointer to the string in the Attribute type. The output parameter puiStringType specifies the string
* format used to represent the string [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* On all unsuccessful conditions NULL is returned. The conditions can be one of the following:
* Any of the input parameters are NULL or Attribute is not present in Name [NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnOcts_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* X509_getAttrFromName(SEC_UINT32 uiAttrType,
									SEC_NAME_S* pstName,
									SEC_UINT32* puiStringType);



/**
* @defgroup X509_getDataFromAttr
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509_getDataFromAttr(SEC_ATTR_TYPE_AND_VALUE_S* pstAttrTypeAndValue,
* SEC_UINT32* puiStringType
* );
* @endcode
* @par Purpose
* To get the corresponding string from an Attribute type and value structure.
* @par Description
* The function is used to get the string and the type that is used to represent the string.
* The returned value is SEC_AsnOcts_S which contains the string and the length of the string.
* @param[in] pstAttrTypeAndValue The structure from which the data has to be extracted [N/A]
* @param[out] puiStringType The string type that is used to to represent in the name structure [N/A]
* @retval SEC_AsnOcts_S* Pointer to the string in the Attribute type. The output parameter puiStringType specifies the string * format used to represent the string [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* On all unsuccessful conditions NULL is returned [NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnOcts_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* X509_getDataFromAttr(SEC_ATTR_TYPE_AND_VALUE_S* pstAttrTypeAndValue,
									SEC_UINT32* puiStringType);



/**
* @defgroup X509_getAttrFromNameByIndex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* X509_getAttrFromNameByIndex(SEC_NAME_S* pstName, SEC_UINT32 uiIndex);
* @endcode
* @par Purpose
* To fetch the Attribute type & value structure from the given name structure based on the given index as input.
* @par Description
* Retrieves the AttributeTypeAndValue Structure from Name structure based on the index given as input. The index starts from
* 0. The function returns the pointer to the AttributeTypeAndValue structure. This function can be used to for comparing of
* name attributes during certificate verification.
* @param[in] pstName Pointer to the Name structure. The name can be either the Subject name or the Issuer Name [N/A]
* @param[in] uiIndex The index identifies the position from which AttributeTypeAndValue structure is to be retrieved [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* Pointer to the the AttributeTypeAndValue structure retrieved
* [SEC_ATTR_TYPE_AND_VALUE_S*|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* On all unsuccessful conditions NULL is returned. The conditions can be one of the
* following:
* If the input is NULL or if the index is greater than the RDNSequence count in Name structure [NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_ATTR_TYPE_AND_VALUE_S structure.Hence this memory
* should not be freed.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S*	X509_getAttrFromNameByIndex(SEC_NAME_S* pstName,
														SEC_UINT32 uiIndex);


/**
* @defgroup X509Extn_freeBasicConstraints
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeBasicConstraints(X509_BASIC_CONSTRAINT_S* pstBasicConstr);
* @endcode
* @par Purpose
* To free a X509_BASIC_CONSTRAINT_S structure.
* @par Description
* Used to free memory for the BasicConstraint structure.
* @param[in] pstBasicConstr Pointer to the Structure that has to be freed. [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeBasicConstraints(X509_BASIC_CONSTRAINT_S* pstBasicConstr);



/**
* @defgroup X509Extn_freePrivateKeyUsage
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freePrivateKeyUsage(X509_PRIVKEY_VALIDITY_S* pstPrivKUPeriod);
* @endcode
* @par Purpose
* To free a X509_PRIVKEY_VALIDITY_S structure.
* @par Description
* This is used to free memory for the PrivateKeyUsagePeriod structure
* @param[in] pstPrivKUPeriod Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freePrivateKeyUsage(X509_PRIVKEY_VALIDITY_S* pstPrivKUPeriod);



/**
* @defgroup X509Extn_freePolicyConstraints
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freePolicyConstraints(X509_POLICY_CONSTRAINT_S* pstPolConstr);
* @endcode
* @par Purpose
* To free a X509_POLICY_CONSTRAINT_S structure.
* @par Description
* This is used to free memory for the PolicyConstraint structure.
* @param[in] pstPolConstr Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freePolicyConstraints(X509_POLICY_CONSTRAINT_S* pstPolConstr);



/**
* @defgroup X509Extn_freeNameConstraint
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeNameConstraint(X509_NAME_CONSTRAINT_S* pstNameConstr);
* @endcode
* @par Purpose
* To free a X509_NAME_CONSTRAINT_S structure.
* @par Description
* This is used to free memory for the NameConstraint structure
* @param[in] pstNameConstr Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeNameConstraint(X509_NAME_CONSTRAINT_S* pstNameConstr);



/**
* @defgroup X509Extn_freeGeneralSubTree
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeGeneralSubTree(X509_GEN_SUBTREE_S* pstGenSubTree);
* @endcode
* @par Purpose
* To free a X509_GEN_SUBTREE_S structure.
* @par Description
* This is used to free memory for the GeneralSubTree structure
* @param[in] pstGenSubTree Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeGeneralSubTree(X509_GEN_SUBTREE_S*	pstGenSubTree);



/**
* @defgroup X509Extn_freeDistPointName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeDistPointName(X509_DPN_S*  pstDistPointName);
* @endcode
* @par Purpose
* To free a X509_DPN_S structure.
* @par Description
* This is used to free memory for the DistributionPointName structure.
* @param[in] pstDistPointName Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeDistPointName(X509_DPN_S*  pstDistPointName);



/**
* @defgroup X509Extn_freeDistPoint
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeDistPoint(X509_DP_S* pstDistPoint);
* @endcode
* @par Purpose
* To free a X509_DP_S structure.
* @par Description
* This is used to free memory for the DistributionPoint structure
* @param[in] pstDistPoint Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeDistPoint(X509_DP_S*  pstDistPoint);



/**
* @defgroup X509Extn_freeAKID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeAKID(X509_AKID_S* pstAKID);
* @endcode
* @par Purpose
* To free a X509_AKID_S structure.
* @par Description
* This is used to free memory for the AKID structure
* @param[in] pstAKID Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeAKID(X509_AKID_S* pstAKID);



/**
* @defgroup X509_freeExtensionList
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeExtensionList(SEC_List_S* pstExtnList);
* @endcode
* @par Purpose
* To free a SEC_List_S(extension list) structure.
* @par Description
* This is used to free memory for the Extension List
* @param[in] pstExtnList Pointer to the List that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeExtensionList(SEC_List_S* pstExtnList);



/**
* @defgroup X509_freeExtension
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeExtension(SEC_EXTN_S* pstExtn);
* @endcode
* @par Purpose
* To free a SEC_EXTN_S structure.
* @par Description
* This is used to free memory for the Extension structure
* @param[in] pstExtn Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeExtension(SEC_EXTN_S* pstExtn);



/**
* @defgroup X509Extn_freeSubjectDirAttr
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeSubjectDirAttr(SEC_List_S* pstSubDirAttrList);
* @endcode
* @par Purpose
* To free a SEC_List_S - Subject Directory Attribute list.
* @par Description
* This is used to free memory for the SubjectDirectoryAttirbute List
* @param[in] pstSubDirAttrList Pointer to the List that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeSubjectDirAttr(SEC_List_S* pstSubDirAttrList);



/**
* @defgroup X509_freeGeneralName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeGeneralName(SEC_GEN_NAME_S* pstGenName);
* @endcode
* @par Purpose
* To free a SEC_GEN_NAME_S structure.
* @par Description
* This is used to free memory for the GeneralName structure
* @param[in] pstGenName Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeGeneralName(SEC_GEN_NAME_S* pstGenName);



/**
* @defgroup X509Extn_freeExtendedKeyUsage
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeExtendedKeyUsage(SEC_List_S* pstExtendedKUList);
* @endcode
* @par Purpose
* To free a SEC_List_S structure - Extended Key usage list.
* @par Description
* This is used to free memory for the ExtendedKeyUsage List
* @param[in] pstExtendedKUList Pointer to the List that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeExtendedKeyUsage(SEC_List_S* pstExtendedKUList);



/**
* @defgroup X509Extn_freeCRLDistPoint
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeCRLDistPoint(SEC_List_S* pstCRLDistPoint);
* @endcode
* @par Purpose
* To free a SEC_List_S structure - CRL distribution point list.
* @par Description
* This is used to free memory for the CRLDistributionPoint List
* @param[in] pstCRLDistPoint Pointer to the List that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeCRLDistPoint(SEC_List_S* pstCRLDistPoint);



/**
* @defgroup X509Extn_freeSubjInfoAccess
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeSubjInfoAccess(SEC_List_S* pstInfoAccessList);
* @endcode
* @par Purpose
* To free a SEC_List_S structure - Subject info access list.
* @par Description
* This is used to free memory for the SubjectInfoAccess List
* @param[in] pstInfoAccessList Pointer to the List that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeSubjInfoAccess(SEC_List_S* pstInfoAccessList);



/**
* @defgroup X509Extn_freeAuthorityInfoAccess
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeAuthorityInfoAccess(SEC_List_S* pstInfoAccessList);
* @endcode
* @par Purpose
* To free a SEC_List_S structure - Authority Info Access list.
* @par Description
* This is used to free memory for the AuthorityInfoAccess List
* @param[in] pstInfoAccessList Pointer to the List that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeAuthorityInfoAccess(SEC_List_S* pstInfoAccessList);



/**
* @defgroup X509Extn_freePolicyMappings
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freePolicyMappings(SEC_List_S* pstPolicyMappingList);
* @endcode
* @par Purpose
* To free a SEC_List_S structure - the Policy mappings list.
* @par Description
* This is used to free memory for the PolicyMappings List
* @param[in] pstPolicyMappingList Pointer to the List that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freePolicyMappings(SEC_List_S* pstPolicyMappingList);



/**
* @defgroup X509Extn_freeCertPolicies
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freeCertPolicies(SEC_List_S* pstCertPolicyList);
* @endcode
* @par Purpose
* To free a SEC_List_S structure - the Certificate policies list.
* @par Description
* This is used to free memory for the Certificate Policies List
* @param[in] pstCertPolicyList Pointer to the List that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freeCertPolicies(SEC_List_S* pstCertPolicyList);



/**
* @defgroup X509_freeAttrTypeAndValue
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeAttrTypeAndValue(SEC_ATTR_TYPE_AND_VALUE_S *pstAttr);
* @endcode
* @par Purpose
* To free a SEC_ATTR_TYPE_AND_VALUE_S structure.
* @par Description
* This is used to free memory for the AttributeTypeAndValue structure variable
* @param[in] pstAttr Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeAttrTypeAndValue(SEC_ATTR_TYPE_AND_VALUE_S *pstAttr);



/**
* @defgroup X509_freeName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeName(SEC_NAME_S* pstName);
* @endcode
* @par Purpose
* To free a SEC_NAME_S structure.
* @par Description
* This is used to free memory for the Name structure variable
* @param[in] pstName Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeName(SEC_NAME_S* pstName);



/**
* @defgroup X509_freeTime
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeTime(SEC_TIME_S* pstTime);
* @endcode
* @par Purpose
* To free a SEC_TIME_S structure.
* @par Description
* This is used to free memory for the Time structure variable
* @param[in] pstTime Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeTime(SEC_TIME_S* pstTime);



/**
* @defgroup X509_freeValidity
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeValidity(SEC_VALIDITY_S* pstValidity);
* @endcode
* @par Purpose
* To free a SEC_VALIDITY_S structure.
* @par Description
* This is used to free memory for the Validity structure variable
* @param[in] pstValidity Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeValidity(SEC_VALIDITY_S* pstValidity);



/**
* @defgroup X509_freeAlgId
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeAlgId(SEC_ALG_IDENTIFIER_S* pstAlgId);
* @endcode
* @par Purpose
* To free a SEC_ALG_IDENTIFIER_S structure.
* @par Description
* This is used to free memory for the Algorithm Identifier structure variable
* @param[in] pstAlgId Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeAlgId(SEC_ALG_IDENTIFIER_S* pstAlgId);



/**
* @defgroup X509_freePubKeyInfo
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freePubKeyInfo(SEC_PUBKEY_INFO_S* pstPubKey);
* @endcode
* @par Purpose
* To free a SEC_PUBKEY_INFO_S structure.
* @par Description
* This is used to free memory for the PublicKeyInfo structure variable
* @param[in] pstPubKey Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freePubKeyInfo(SEC_PUBKEY_INFO_S* pstPubKey);



/**
* @defgroup X509_freeGeneralNameList
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeGeneralNameList(SEC_List_S* pGenNameList);
* @endcode
* @par Purpose
* To free a SEC_List_S structure - the Issuer Alternate name & subject alternate name list.
* @par Description
* This is used to free memory for the IssuerAlternateName and SubjectAlternateName List
* @param[in] pGenNameList Pointer to the List that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeGeneralNameList(SEC_List_S* pGenNameList);



/**
* @defgroup X509Extn_freePolicyInfo
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509Extn_freePolicyInfo(X509_POLICY_INFO_S* pstPolInfo);
* @endcode
* @par Purpose
* To free a X509_POLICY_INFO_S structure.
* @par Description
* This is Used to free memory for the PolicyInformation structure
* @param[in] pstPolInfo Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509Extn_freePolicyInfo(X509_POLICY_INFO_S* pstPolInfo);



/**
* @defgroup  X509_freeAttribute
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeAttribute(SEC_ATTR_S* pstAttr);
* @endcode
* @par Purpose
* To free a SEC_ATTR_S structure.
* @par Description
* This is used to free memory for the Attribute structure
* @param[in] pstAttr Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeAttribute(SEC_ATTR_S* pstAttr);



/**
* @defgroup  X509_freeIssuerAndSerial
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID X509_freeIssuerAndSerial(SEC_ISSUER_AND_SERIAL_S* pstIssuerAndSerial);
* @endcode
* @par Purpose
* To free a SEC_ISSUER_AND_SERIAL_S structure.
* @par Description
* This is used to free memory for the IssuerAndSerial structure variable
* @param[in] pstIssuerAndSerial Pointer to the Structure that has to be freed [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VOID This does not return any value [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID X509_freeIssuerAndSerial(SEC_ISSUER_AND_SERIAL_S* pstIssuerAndSerial);



/**
* @defgroup  X509_deleteExtn
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32  X509_deleteExtn (SEC_UINT32 uiExtnCID ,X509_CERT_S *pstCert);
* @endcode
* @par Purpose
* To remove an extension from the given certificate based on the extension CID.
* @par Description
* This function is used to delete the extension from the certificate.Extension are deleted based on extension CID which is
* taken as input.
* @param[in] uiExtnCID CID of the extension which has to be deleted [N/A]
* @param[out] pstCert Certificate which contains the extension [N/A]
* @retval SEC_UINT32 On successful deletion of extension [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If the input is NULL(certificate or extension) [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If extension is not present [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 If invalid CID is given as input [SEC_ERR_INVALID_CID|N/A]
* @par Dependency
* x509.h
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32  X509_deleteExtn (SEC_UINT32 uiExtnCID ,X509_CERT_S *pstCert);



/**
* @defgroup  X509_decodeExtnList
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S*  X509_decodeExtnList( SEC_UCHAR* pucEncodedExtnList,
* SEC_UINT32 uiEncLen,
* SEC_UINT32* puiDecLen
* );
* @endcode
* @par Purpose
* To generate a decoded list of x509 extensions from the encoded x509 extension list.
* @par Description
* This function is used to decode extension list
* @param[in] pucEncodedExtnList Encoded extension list that has to be decoded [N/A]
* @param[in] uiEncLen The length of the encoded character stream [N/A]
* @param[out] puiDecLen Bytes that is decoded [N/A]			                                                      
* @retval SEC_List_S* Pointer to the list containing extensions [SEC_List_S*|N/A]
* @retval SEC_List_S* Input parameters are invalid, memory allocation fails or decoding of extension fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List structure, to free this memory
* application has to call the SEC_LIST_FREE macro with X509_freeExtension as free function.
*
* @par Note
*
* Memory is allocated during decode of extension. Delete the list after using the the list.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S*  X509_decodeExtnList( SEC_UCHAR* pucEncodedExtnList,
								  SEC_UINT32  uiEncLen,
								  SEC_UINT32* puiDecLen);



/**
* @defgroup  X509_encodeExtnList
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR*  X509_encodeExtnList( SEC_List_S* pExtnList, SEC_UINT32* puiEncLen);
* @endcode
* @par Purpose
* To encode a given x509 extension
* @par Description
* This function is used to encode the given X509 extension list
* @param[in] pExtnList Pointer to the list which has to be encoded
* @param[out] puiEncLen Pointer to the encoded length [N/A]		                                                     
* @retval SEC_CHAR* Pointer to the buffer containing the encoded data [SEC_CHAR*|N/A]
* @retval SEC_CHAR* If the input parameters are invalid or encoding is unsuccessful [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded ExtnList, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* Memory is allocated during decode of extension. Delete the list after using the list.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR*  X509_encodeExtnList( SEC_List_S* pExtnList, SEC_UINT32* puiEncLen);



/**
* @defgroup X509_encodeCertList
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_encodeCertList (SEC_List_S* pstCertList,
* SEC_UINT32* puiEncodedLen
* );
* @endcode
* @par Purpose
* To encode the given X509 Certificate list.
* @par Description
* This function is used to encode the given certificate list
* @param[in] pstCertList Pointer to the list which has to be encoded
* @param[out] puiEncodedLen Pointer to the encoded length [N/A]
* @retval SEC_CHAR* Pointer to the buffer containing the encoded data [SEC_CHAR*|N/A]
* @retval SEC_CHAR* If the input parameters is wrong or encode is unsuccesful [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded CertList, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* Memory is allocated during decode of extension. Delete the list after using the the list.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* X509_encodeCertList (SEC_List_S*	pstCertList,
								SEC_UINT32*	puiEncodedLen);




/**
* @defgroup X509_decodeCertList
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S*  X509_decodeCertList(SEC_UCHAR* pucEncodedCertList,
* SEC_UINT32 uiEncodedLength,
* SEC_UINT32* puiDecodedLength
* );
* @endcode
* @par Purpose
* To decode the X509 Certificate list from the given encoded certificate list.
* @par Description
* This function is used to decode certificate list
* @param[in] pucEncodedCertList Encoded certiticate list that has to be decoded [N/A]
* @param[in] uiEncodedLength The length of the encoded character stream [N/A]
* @param[out] puiDecodedLength Bytes that is decoded [N/A]
* @retval SEC_List_S* Pointer to the list containing extensions [SEC_List_S*|N/A]
* @retval SEC_List_S* Input parameters are invalid, Memory allocation fails or decoding of certificate fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List_S structure, to free this memory
* application has to call the SEC_LIST_FREE macro with X509_freeCert function.
*
* @par Note
*
* Memory is allocated during decode of extension. Detele the list after using it.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S*  X509_decodeCertList(SEC_UCHAR*		pucEncodedCertList,
							     SEC_UINT32		uiEncodedLength,
							     SEC_UINT32*    puiDecodedLength);

/*To duplicate certificate structure*/


/*
The following function are duplicate functions that takes the pointer to a
structure to be duplicated and returns a pointer to newly created structure
copied with the information passed to the function.
*/


/**
* @defgroup SEC_dupCertificate
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CERT_S* SEC_dupCertificate(X509_CERT_S* pSrc);
* @endcode
* @par Purpose
* To duplicate an X509 Certificate structure.
* @par Description
* The following method allows duplicating an X509 Certificate structure by internally allocating memory.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_CERT_S* Pointer to the duplicated structure [X509_CERT_S*|N/A]
* @retval X509_CERT_S* If the input is NULL [SEC_NULL|N/A]
* @retval X509_CERT_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List_S structure, to free this memory
* application has to call the X509_freeCert function.
*
* @par Note
*
* N/A
*
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_CERT_S* SEC_dupCertificate(X509_CERT_S* pSrc);

/**
* @defgroup SEC_refCertificate
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CERT_S* SEC_refCertificate(X509_CERT_S* pSrc);
* @endcode
* @par Purpose
* To refer an input X509 Certificate structure.
* @par Description
* The following method allows refering an X509 Certificate structure 
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_CERT_S* Pointer to the duplicated structure [X509_CERT_S*|N/A]
* @retval X509_CERT_S* If the input is NULL [SEC_NULL|N/A]
* @par Dependency
* x509.h
* @par Note
* To free the output certificate application should call the X509_freeCert
* 
* @par Related Topics
* N/A
*/

PSELINKDLL X509_CERT_S *SEC_refCertificate(X509_CERT_S* pstSrcCert);

/*To duplicate Name structure*/


/**
* @defgroup SEC_dupName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_NAME_S* SEC_dupName(SEC_NAME_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a SEC_NAME_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory
* to duplicate Name structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_NAME_S* Pointer to the duplicated structure [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_NAME_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_NAME_S structure, to free this memory
* application has to call the X509_freeName function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_NAME_S* SEC_dupName(SEC_NAME_S* pSrc);




/**
* @defgroup SEC_dupValidity
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VALIDITY_S* SEC_dupValidity(SEC_VALIDITY_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a SEC_VALIDITY_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory
* to duplicate X509 Validity structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_VALIDITY_S* Pointer to the duplicated structure [SEC_VALIDITY_S*|N/A]
* @retval SEC_VALIDITY_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_VALIDITY_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_VALIDITY_S structure, to free this memory
* application has to call the X509_freeValidity function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VALIDITY_S* SEC_dupValidity(SEC_VALIDITY_S* pSrc);


/**
* @defgroup SEC_dupSubjectPublicKeyInfo
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_PUBKEY_INFO_S* SEC_dupSubjectPublicKeyInfo(SEC_PUBKEY_INFO_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a SEC_PUBKEY_INFO_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory
* to duplicate Public Key Information structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_PUBKEY_INFO_S* Pointer to the duplicated structure [SEC_PUBKEY_INFO_S*|N/A]
* @retval SEC_PUBKEY_INFO_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_PUBKEY_INFO_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_PUBKEY_INFO_S structure, to free this memory
* application has to call the X509_freePubKeyInfo function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_PUBKEY_INFO_S* SEC_dupSubjectPublicKeyInfo(SEC_PUBKEY_INFO_S* pSrc);

/*To duplicate Extension List*/


/**
* @defgroup SEC_dupExtensions
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* SEC_dupExtensions(SEC_List_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a list of X509 Extension.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory
* to duplicate Extension List.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Pointer to the duplicated structure [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_List_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List structure, to free this memory
* application has to call the SEC_LIST_FREE macro with X509_freeExtension as free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupExtensions(SEC_List_S* pSrc);


/*To duplicate Attribute structure*/


/**
* @defgroup SEC_dupAttribute
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_ATTR_S* SEC_dupAttribute(SEC_ATTR_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a SEC_ATTR_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate Attribute structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_ATTR_S* Pointer to the duplicated structure [SEC_ATTR_S*|N/A]
* @retval SEC_ATTR_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_ATTR_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_ATTR_S structure, to free this memory
* application has to call the X509_freeAttribute function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ATTR_S* SEC_dupAttribute(SEC_ATTR_S* pSrc);

/*To duplicate Extension structure*/


/**
* @defgroup SEC_dupExtension
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_EXTN_S* SEC_dupExtension(SEC_EXTN_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a SEC_EXTN_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate Extension structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_EXTN_S* Pointer to the duplicated structure [SEC_EXTN_S*|N/A]
* @retval SEC_EXTN_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_EXTN_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_EXTN_S structure, to free this memory
* application has to call the X509_freeExtension function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_EXTN_S* SEC_dupExtension(SEC_EXTN_S* pSrc);

/*To duplicate Time structure*/


/**
* @defgroup SEC_dupTime
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_TIME_S* SEC_dupTime(SEC_TIME_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a SEC_TIME_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory
* to duplicate Time structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_TIME_S* Pointer to the duplicated structure [SEC_TIME_S*|N/A]
* @retval SEC_TIME_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_TIME_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_TIME_S structure, to free this memory
* application has to call the X509_freeTime function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_TIME_S* SEC_dupTime(SEC_TIME_S* pSrc);

/*To duplicate AlgorithmIdentifier structure*/


/**
* @defgroup SEC_dupAlgorithmIdentifier
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_ALG_IDENTIFIER_S* SEC_dupAlgorithmIdentifier(SEC_ALG_IDENTIFIER_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a SEC_ALG_IDENTIFIER_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory
* to duplicate AlgorithmIdentifier structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_ALG_IDENTIFIER_S* Pointer to the duplicated structure [SEC_ALG_IDENTIFIER_S*|N/A]
* @retval SEC_ALG_IDENTIFIER_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_ALG_IDENTIFIER_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_ALG_IDENTIFIER_S structure, to free this memory
* application has to call the X509_freeAlgId function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ALG_IDENTIFIER_S* SEC_dupAlgorithmIdentifier(SEC_ALG_IDENTIFIER_S* pSrc);

/*To duplicate PrivateKeyValidity structure*/


/**
* @defgroup SEC_dupPrivateKeyUsagePeriod
* @ingroup x509Functions
* @par Prototype
* @code
* X509_PRIVKEY_VALIDITY_S* SEC_dupPrivateKeyUsagePeriod(X509_PRIVKEY_VALIDITY_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a X509_PRIVKEY_VALIDITY_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate PrivateKeyValidity structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_PRIVKEY_VALIDITY_S* Pointer to the duplicated structure [X509_PRIVKEY_VALIDITY_S*|N/A]
* @retval X509_PRIVKEY_VALIDITY_S* If the input is NULL [SEC_NULL|N/A]
* @retval X509_PRIVKEY_VALIDITY_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_PRIVKEY_VALIDITY_S structure, to free this memory
* application has to call the X509Extn_freePrivateKeyUsage function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_PRIVKEY_VALIDITY_S* SEC_dupPrivateKeyUsagePeriod(X509_PRIVKEY_VALIDITY_S* pSrc);

/*To duplicate BasicConstraint structure*/


/**
* @defgroup SEC_dupBasicConstraintsSyntax
* @ingroup x509Functions
* @par Prototype
* @code
* X509_BASIC_CONSTRAINT_S* SEC_dupBasicConstraintsSyntax(X509_BASIC_CONSTRAINT_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a X509_BASIC_CONSTRAINT_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate BasicConstraint structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_BASIC_CONSTRAINT_S* Pointer to the duplicated structure [X509_BASIC_CONSTRAINT_S*|N/A]
* @retval X509_BASIC_CONSTRAINT_S* If the input is NULL [SEC_NULL|N/A]
* @retval X509_BASIC_CONSTRAINT_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_BASIC_CONSTRAINT_S structure, to free this memory
* application has to call the X509Extn_freeBasicConstraints function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_BASIC_CONSTRAINT_S* SEC_dupBasicConstraintsSyntax(X509_BASIC_CONSTRAINT_S* pSrc);

/*To duplicate Policy Information structure*/


/**
* @defgroup SEC_dupPolicyInformation
* @ingroup x509Functions
* @par Prototype
* @code
* X509_POLICY_INFO_S* SEC_dupPolicyInformation(X509_POLICY_INFO_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a X509_POLICY_INFO_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate Policy Information structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_POLICY_INFO_S* Pointer to the duplicated structure [X509_POLICY_INFO_S*|N/A]
* @retval X509_POLICY_INFO_S* If the input is NULL [SEC_NULL|N/A]
* @retval X509_POLICY_INFO_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_POLICY_INFO_S structure, to free this memory
* application has to call the X509Extn_freePolicyInfo function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_POLICY_INFO_S* SEC_dupPolicyInformation(X509_POLICY_INFO_S* pSrc);

/*To duplicate Policy Mapping list*/


/**
* @defgroup SEC_dupPolicyMappingsSyntax
* @ingroup x509Functions
* @par Prototype
* @code
* X509_POLICY_MAPPING_LIST* SEC_dupPolicyMappingsSyntax(X509_POLICY_MAPPING_LIST* pSrc);
* @endcode
* @par Purpose
* To duplicate a X509_POLICY_MAPPING_LIST structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate Policy Mapping list.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_POLICY_MAPPING_LIST* Pointer to the duplicated structure [X509_POLICY_MAPPING_LIST*|N/A]
* @retval X509_POLICY_MAPPING_LIST* If the input is NULL [SEC_NULL|N/A]
* @retval X509_POLICY_MAPPING_LIST* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_POLICY_MAPPING_LIST structure, to free this memory
* application has to call the X509Extn_freePolicyMappings function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_POLICY_MAPPING_LIST* SEC_dupPolicyMappingsSyntax(X509_POLICY_MAPPING_LIST* pSrc);


/*To duplicate General Name structure*/


/**
* @defgroup SEC_dupGeneralName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_GEN_NAME_S* SEC_dupGeneralName(SEC_GEN_NAME_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a SEC_GEN_NAME_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate General Name structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_GEN_NAME_S* Pointer to the duplicated structure [SEC_GEN_NAME_S*|N/A]
* @retval SEC_GEN_NAME_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_GEN_NAME_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_GEN_NAME_S structure, to free this memory
* application has to call the X509_freeGeneralName function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_GEN_NAME_S* SEC_dupGeneralName(SEC_GEN_NAME_S* pSrc);

/*To duplicate General Subtree structure*/


/**
* @defgroup SEC_dupGeneralSubtree
* @ingroup x509Functions
* @par Prototype
* @code
* X509_GEN_SUBTREE_S* SEC_dupGeneralSubtree(X509_GEN_SUBTREE_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a X509_GEN_SUBTREE_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate General Subtree structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_GEN_SUBTREE_S* Pointer to the duplicated structure [N/A|N/A]
* @retval SEC_NULL If the input is NULL [SEC_NULL|N/A]
* @retval SEC_NULL If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_GEN_SUBTREE_S structure, to free this memory
* application has to call the X509Extn_freeGeneralSubTree function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_GEN_SUBTREE_S* SEC_dupGeneralSubtree(X509_GEN_SUBTREE_S* pSrc);

/*To duplicate Policy constraint structure*/



/**
* @defgroup SEC_dupPolicyConstraintsSyntax
* @ingroup x509Functions
* @par Prototype
* @code
* X509_POLICY_CONSTRAINT_S* SEC_dupPolicyConstraintsSyntax(X509_POLICY_CONSTRAINT_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a X509_POLICY_CONSTRAINT_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate Policy constraint structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_POLICY_CONSTRAINT_S* Pointer to the duplicated structure [N/A|N/A]
* @retval SEC_NULL If the input is NULL [SEC_NULL|N/A]
* @retval SEC_NULL If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_POLICY_CONSTRAINT_S structure, to free this memory
* application has to call the X509Extn_freePolicyConstraints function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_POLICY_CONSTRAINT_S* SEC_dupPolicyConstraintsSyntax(X509_POLICY_CONSTRAINT_S* pSrc);

/*To duplicate CRL Distribution points*/



/**
* @defgroup SEC_dupCRLDistributionPoints
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* SEC_dupCRLDistributionPoints(SEC_List_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a CRL Distribution point list.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate ExtendedKeyUsage List.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Pointer to the duplicated structure [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_List_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List_S structure, to free this memory
* application has to call the X509Extn_freeCRLDistPoint function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupCRLDistributionPoints(SEC_List_S* pSrc);

/*To duplicate Distribution point Name structure*/


/**
* @defgroup SEC_dupDistributionPointName
* @ingroup x509Functions
* @par Prototype
* @code
* X509_DPN_S* SEC_dupDistributionPointName(X509_DPN_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a CRL Distribution point name list.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate Distribution point Name structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_DPN_S* Pointer to the duplicated structure [X509_DPN_S*|N/A]
* @retval X509_DPN_S* If the input is NULL [SEC_NULL|N/A]
* @retval X509_DPN_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_DPN_S structure, to free this memory
* application has to call the X509Extn_freeDistPointName function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_DPN_S* SEC_dupDistributionPointName(X509_DPN_S* pSrc);

/*To duplicate Authority Key Identifier structure*/


/**
* @defgroup SEC_dupAuthorityKeyIdentifier
* @ingroup x509Functions
* @par Prototype
* @code
* X509_AKID_S* SEC_dupAuthorityKeyIdentifier(X509_AKID_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a X509_AKID_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate Authority Key Identifier structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_AKID_S* Pointer to the duplicated structure [X509_AKID_S*|N/A]
* @retval X509_AKID_S* If the input is NULL [SEC_NULL|N/A]
* @retval X509_AKID_S* If memory allocation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_DPN_S structure, to free this memory
* application has to call the X509Extn_freeAKID function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_AKID_S* SEC_dupAuthorityKeyIdentifier(X509_AKID_S* pSrc);

/*To duplicate NameConstraint structure*/


/**
* @defgroup SEC_dupNameConstraintsSyntax
* @ingroup x509Functions
* @par Prototype
* @code
* X509_NAME_CONSTRAINT_S* SEC_dupNameConstraintsSyntax(X509_NAME_CONSTRAINT_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a X509_NAME_CONSTRAINT_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate NameConstraint structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_NAME_CONSTRAINT_S* Pointer to the duplicated structure [X509_NAME_CONSTRAINT_S*|N/A]
* @retval X509_NAME_CONSTRAINT_S* If the input is NULL [SEC_NULL|N/A]
* @retval X509_NAME_CONSTRAINT_S* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_NAME_CONSTRAINT_S structure, to free this memory
* application has to call the X509Extn_freeNameConstraint function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_NAME_CONSTRAINT_S* SEC_dupNameConstraintsSyntax(X509_NAME_CONSTRAINT_S* pSrc);

/*To duplicate Distribution Point structure*/


/**
* @defgroup SEC_dupDistributionPoint
* @ingroup x509Functions
* @par Prototype
* @code
* X509_DP_S* SEC_dupDistributionPoint(X509_DP_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a X509_DP_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate Distribution Point structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_DP_S* Pointer to the duplicated structure [X509_DP_S*|N/A]
* @retval X509_DP_S* If the input is NULL [SEC_NULL|N/A]
* @retval X509_DP_S* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_DP_S structure, to free this memory
* application has to call the X509Extn_freeDistPoint function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_DP_S* SEC_dupDistributionPoint(X509_DP_S* pSrc);

/*To duplicate ExtendedKeyUsage List*/


/**
* @defgroup SEC_dupExtKeyUsageExtension
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_List_S* SEC_dupExtKeyUsageExtension(SEC_List_S* pSrc);
* @endcode
* @par Purpose
* To duplicate an key usage extension structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate ExtendedKeyUsage List.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_List_S* Pointer to the duplicated structure [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_List_S* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_List_S structure, to free this memory
* application has to call the X509Extn_freeExtendedKeyUsage function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupExtKeyUsageExtension(SEC_List_S* pSrc);

/*To duplicate AttributeTypeAndValue structure*/


/**
* @defgroup SEC_dupAttributeTypeAndValue
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* SEC_dupAttributeTypeAndValue(SEC_ATTR_TYPE_AND_VALUE_S* pSrc);
* @endcode
* @par Purpose
* To duplicate a SEC_ATTR_TYPE_AND_VALUE_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory to
* duplicate AttributeTypeAndValue structure.
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ATTR_TYPE_AND_VALUE_S* Pointer to the duplicated structure [SEC_ATTR_TYPE_AND_VALUE_S*|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_ATTR_TYPE_AND_VALUE_S structure, to free this memory
* application has to call the X509_freeAttrTypeAndValue function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S* SEC_dupAttributeTypeAndValue(SEC_ATTR_TYPE_AND_VALUE_S* pSrc);

/**
* @defgroup X509_encodeGeneralName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_encodeGeneralName( SEC_GEN_NAME_S* pstGenName,
*                                    SEC_UINT32* uiReturnEncodedLen);
* @endcode
* @par Purpose
* To encode General name.
* @par Description
* The following method allows encoding of general name.
* @param[in] pstGenName General name [N/A]
* @param[out] uiReturnEncodedLen The encoded length. [N/A]
*
* @retval SEC_UCHAR* Encoded General name. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* If the input is NULL. [SEC_NULL|N/A]
* @retval SEC_UCHAR* If memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded general name, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_UCHAR* X509_encodeGeneralName(SEC_GEN_NAME_S* pstGenName,
        SEC_UINT32* uiReturnEncodedLen);



/**
* @defgroup X509_decodeGeneralName
* @ingroup x509Functions
* @par Prototype
* @code
* X509_CERT_S* X509_decodeGeneralName(SEC_CHAR* pcEncBuf,
* SEC_UINT32 uiEncLen,
* SEC_UINT32* puiDecLen);
* @endcode
* @par Purpose
* To generate a decoded General Name from a DER encoded General Name.
*
* @par Description
* This function returns a pointer to General Name structure after decoding the input data
* passed to this function using the first parameter.
*
* @param[in] pcEncBuf The encoded General Name that has to be decoded [N/A]
* @param[in] uiEncLen The length of the encoded character stream [N/A]
* @param[out] puiDecodedLength Bytes that is decoded [N/A]
*
* @retval X509_CERT_S* The General Name structure after decoding [SEC_GEN_NAME_S*|N/A]
* @retval X509_CERT_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:\n
* 1. Decoding of the General Name fails\n
* 2. Memory allocation fails\n
* 3. Input parameter is NULL [SEC_NULL|N/A]	 	
*		
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_GEN_NAME_S structure, to free this memory
* application has to call the X509_freeGeneralName function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_GEN_NAME_S* X509_decodeGeneralName(SEC_CHAR*pcEncBuf,
       SEC_UINT32  uiEncLen, SEC_UINT32* puiDecLen);


/**
* @defgroup X509_encodeAKID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_encodeAKID( X509_AKID_S* pstAkid,
*                               SEC_UINT32* uiReturnEncodedLen);
* @endcode
* @par Purpose
* To encode Authority key identifier.
* @par Description
* ThIS method allows encoding of authority key identifier.
* @param[in] pstAkid Authority key identifier. [N/A]
* @param[out] uiReturnEncodedLen The encoded length. [N/A]
*
* @retval SEC_UCHAR* Encoded Authority key identifier. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* If the input is NULL. [SEC_NULL|N/A]
* @retval SEC_UCHAR* If memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded AKID extension, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL  SEC_UCHAR* X509_encodeAKID(X509_AKID_S* pstAkid,
        SEC_UINT32* uiReturnEncodedLen);

/**
* @defgroup X509_encodeIDP
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_encodeIDP( X509_IDP_S* pstIdp,
*        SEC_UINT32* uiReturnEncodedLen);
* @endcode
* @par Purpose
* To encode Issuing Distribution Point.
* @par Description
* This method allows encoding of Issuing Distribution Point.
* @param[in] pstIdp Issuing Distribution Point. [N/A]
* @param[out] uiReturnEncodedLen The encoded length. [N/A]
*
* @retval SEC_UCHAR* Encoded Issuing Distribution Point. [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* If the input is NULL. [SEC_NULL|N/A]
* @retval SEC_UCHAR* If memory allocation fails. [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded IDP extension, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UCHAR* X509_encodeIDP(X509_IDP_S* pstIdp,
        SEC_UINT32* uiReturnEncodedLen);

/**
* @defgroup X509_compareGeneralName
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_compareGeneralName( SEC_GEN_NAME_S *pstSrcGenName,
*                                     SEC_GEN_NAME_S *pstDestGenName);
* @endcode
* @par Purpose
* To compare General name.
* @par Description
* This method allows comparing of general names.
* @param[in] pstSrcGenName First General name. [N/A]
* @param[in] pstDestGenName Second General name. [N/A]
*
* @retval 0 Both General names are same. [SEC_INT|N/A]
* @retval -1 Invalid arguments.[SEC_INT|N/A]
* @retval !(0) General names are different.[SEC_INT|N/A]
*
* @par Dependency
* x509.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_INT X509_compareGeneralName(SEC_GEN_NAME_S *pstSrcGenName, 
    SEC_GEN_NAME_S *pstDestGenName);

/**
* @defgroup X509_compareAkid
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_compareAkid( X509_AKID_S *pstSrcAkid, 
*                              X509_AKID_S *pstDestAkid);
* @endcode
* @par Purpose
* To compare Authority key identifier.
* @par Description
* The following method allows comparing of AKIDs
* @param[in] pstSrcAkid First AKID. [N/A]
* @param[in] pstDestAkid Second AKID. [N/A]
*
* @retval 0 Both AKIDs are same. [SEC_INT|N/A]
* @retval -1 Invalid arguments. [SEC_INT|N/A]
* @retval !(0) AKIDs are different.[SEC_INT|N/A]
*
* @par Dependency
* x509.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_INT X509_compareAkid(X509_AKID_S *pstSrcAkid, 
   X509_AKID_S *pstDestAkid);

/**
* @defgroup X509_compareIdp
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_compareIdp( X509_IDP_S *pstSrcIdp, 
*                            X509_IDP_S *pstDesIdp);
* @endcode
* @par Purpose
* To compare Issuing Distribution Point.
* @par Description
* This method allows comparing of IDPs.
* @param[in] pstSrcIdp First IDP. [N/A]
* @param[in] pstDesIdp Second IDP. [N/A]
*
* @retval 0 Both IDPs are same. [SEC_INT|N/A]
* @retval -1 Invalid arguments. [SEC_INT|N/A]
* @retval !(0) IDPs are different.[SEC_INT|N/A]
*
* @par Dependency
* x509.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT X509_compareIdp(X509_IDP_S *pstSrcIdp, 
   X509_IDP_S *pstDesIdp);

/**
* @defgroup X509_encodeSN
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UCHAR* X509_encodeSN(SEC_BIGINT_S* pstSN,
*         SEC_UINT32* uiReturnEncodedLen);
* @endcode
* @par Purpose
* To encode Serial Number
* @par Description
* The following method allows encoding of the Serial Number
* @param[in] pstSN Serial Number [N/A]
* @param[out] uiReturnEncodedLen The encoded length [N/A]
*
* @retval SEC_UCHAR* Encoded Serial Number [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_UCHAR* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the encoded Serial Number, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_UCHAR* X509_encodeSN(SEC_BIGINT_S *pstSN,
              SEC_UINT32* uiReturnEncodedLen);

/**
* @defgroup X509_decodeSN
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_NAME_S*  X509_decodeSN(SEC_UCHAR* pstDERCodeOfName,
* SEC_UINT32 uiEncSNLen,
* SEC_UINT32* puiRetDecodedLen
* );
* @endcode
* @par Purpose
* Decode the Serial Number
* @par Description
* The function performs the decoding of serial number. The length of the encoded 
* serial umber uiEncSNLen parameter.
* The decoded length is returned in puiReturnDecodedLen.
* @param[in] pstDERCodeOfSN The encoded serial number as a string [N/A]
* @param[in] uiEncSNLen Length of the encoded string [N/A]
* @param[out] puiRetDecodedLen The length of the decoded data [N/A]
* @retval SEC_NAME_S* Pointer to decoded Serial Number [SEC_BIGINT_S*|N/A]
* @retval SEC_NAME_S* Returns when memory allocation or encode of name fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_BIGINT_S structure, to free this memory
* application has to call the ipsi_free function.
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL  SEC_BIGINT_S* X509_decodeSN(SEC_UCHAR* pstDERCodeOfSN,
        SEC_UINT32 uiEncSNLen, SEC_UINT32* puiRetDecodedLen);



/**
* @defgroup X509Extn_createAKID_ex
* @ingroup x509Functions
* @par Prototype
* @code
* X509_AKID_S* X509Extn_createAKID_ex(SEC_BIGINT_S* pstCertSerialNum,
* SEC_List_S* pCertificateIssuer,
* SEC_PKEY_S* pstPublicKey,
* X509_KIDGENTYPE_E enKIDType
* );
* @endcode
* @par Purpose
* To create an authority key identifier structure.
* @par Description
* This API is used for a CA certificate. This extension is used when the CA has more than one signing keys and this extension
* helps in finding the key pair. The keyIdentifier field of the extension must be included in all certificates generated by
* confirming CAs to facilitate certification path construction. The key identifier generation is either 160 bit SHA1 hash
* value or 64 bit value.
* @param[in] pstCertSerialNum The unique serialNumber of the CA [N/A]
* @param[in] pCertificateIssuer The Alternate Name of the Certificate Issuer [N/A]
* @param[in] pstPublicKey The public key that has to be encoded and hash calculated on it using
* the option passed in the enKIDType argument in the function [N/A]
* @param[in] enKIDType The method of generating the KeyIdentifier [N/A]
* @param[out] N/A N/A [N/A]
* @retval X509_AKID_S* On successful execution pointer to the X509_AKID_S structure is returned [X509_AKID_S*|N/A]
* @retval X509_AKID_S* On failure conditions SEC_NULL is returned. The failure conditions can be one of the following:\n
* 1> Input parameters is NULL,\n
* 2> Memory allocation fails,
* 3> Encoding of Public key fails,
* 4> Hash calculation fails [SEC_NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the X509_AKID_S structure, to free this memory
* application has to call the X509Extn_freeAKID function.
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

PSELINKDLL X509_AKID_S* X509Extn_createAKID_ex(SEC_BIGINT_S* pstCertSerialNum,
								 SEC_List_S* pCertificateIssuer,
								 SEC_PKEY_S* pstPublicKey,
								 X509_KIDGENTYPE_E enKIDType);



/**
* @defgroup X509Extn_createSKID_ex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509Extn_createSKID_ex(SEC_PKEY_S* pstPublicKey,
* X509_KIDGENTYPE_E enKIDGenType);
* @endcode
* @par Purpose
* To create and populate a Subject Key Identifier structure.
* @par Description
* This function generates the SubjectKeyIdentifier given the Public key and the mode in which the key identifier has to be
* generated.  The mode can be either SHA1 160 bits or 64 bits. Returns hash value of the public key along with the length.
* @param[in] pstPublicKey The public key that has to be encoded upon which hash has to be generated [N/A]
* @param[in] enKIDGenType The method of generating the the KeyIdentifier [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_AsnOcts_S* On successful execution the hash of the PublicKey is returned along with its length
* [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* Upon failure SEC_NULL is returned. The conditions can be one of the following:
* Input parameter is NULL, Encoding of the PublicKey fails, Hash operation on encoded public key fails or Memory allocation
* fails [NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will allocate the memory for the SEC_AsnOcts_S structure, to free this memory
* application has to call the SEC_freeAsnOcts function.
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

PSELINKDLL SEC_AsnOcts_S* X509Extn_createSKID_ex(SEC_PKEY_S* pstPublicKey,
								   X509_KIDGENTYPE_E enKIDGenType);


/**
* @defgroup X509_signCertificate_ex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32  X509_signCertificate_ex(X509_CERT_S* pstCertificate,SEC_PKEY_S* pstPrivateKey, 
*                                    SEC_UINT32 uiCtrlFlag, IPSI_AUX_PAR_S *pstAuxPar);
* @endcode
* @par Purpose
* To sign a x509 certificate with the given private key.
* @par Description
* This function is extended feature of X509_signCertificate. The functionality is same as X509_signCertificate but it has some extra
* features supported. It has control flags as the input parameter which can define different behaviour for this API. Currently 
* SEC_EC_NO_TRUNCATION is the only option available to this parameter.
* This function signs the certificate given the private key for signing.
* Before signing the certificate the algorithm Object Identifiers that are set in the certificate is compared.
* The certificate extensions is verified to find whether there are
* multiple existence of same extensions.Based on the certificate version set comaparison is made to check whether the
* certificate consists of only the permitted fields corresponding to the certificate version.
* The algorithm used to sign the certificate has to match the algorithm object identifier set in the certificate.
* For CA certificate, if Digital signature bit is set in Key usage extension and basic constraint extension present then the
* criticality of the Basic Constriant extension has to be set to TRUE by the application.  Since the DigitalSignature key
* usage depends on other extensions like Name constraints, Policy Mappings, Policy Constraints etc that has to be validated
* by the Application.If all the conditions are verified then the certificate is signed and the set to the signature field of
* the certificate structure.
* @param[in] pstPrivateKey The private key that is used to sign the certificate [N/A]
* @param[in] uiCtrlFlag Control flag is used to define the different operation. Currently only option available is 
* SEC_EC_NO_TRUNCATION. The control flag should be passed as 0 or SEC_EC_NO_TRUNCATION. 
* SEC_EC_NO_TRUNCATION is only valid for ECDSA and SM2DSA signing algorithm, for other algorithm
* application should pass 0.[N/A]
* @param[in] pstAuxPar This parameter is reserved for future use. Application can pass NULL. [N/A]
* @param[out] pstCertificate The certificate to be signed [N/A]
* @retval SEC_UINT32 On successful signing of the certificate SEC_SUCCESS is returned [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL or has incorrect data [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Validation of the extension fail [SEC_ERR_INVALID_EXTN|N/A]
* @retval SEC_UINT32 Encoding of the certificate fails [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Sign of certificate fails [SEC_ERR_SIGNING_FAILED|N/A]
* @retval SEC_UINT32 The algorithm set in the certificate is not a signature algorithm [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 If there is mismatch in the signature OIDs in the X509_CERT_S structure and SEC_TBSCERT_S
* structure. [SEC_ERR_OID_MISMATCH|N/A]
* @retval SEC_UINT32 Subject Name is not present which is a mandatory field [SEC_ERR_NAME_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Invalid version.Data is not consistent with version [SEC_ERR_INVALID_VERSION|N/A]
* @retval SEC_UINT32 Duplicate Extension available [SEC_ERR_DUPLICATE_EXTN|N/A]
* @retval SEC_UINT32 Required extension not available in certificate [SEC_ERR_EXTN_NOT_AVAILABLE|N/A]
* @par Dependency
* x509.h
* @par Note
* @par Note
*   - For ALGID_SM2DSA signature, the pstPrivateKey should be a key pair i.e. public and private key should be
*      available in pstPrivateKey because public key will be used for the generation of ZA and private key
*      will be used for signature
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UINT32  X509_signCertificate_ex(X509_CERT_S* pstCertificate,SEC_PKEY_S* pstPrivateKey, 
                                    SEC_UINT32 uiCtrlFlag, IPSI_AUX_PAR_S *pstAuxPar);




/**
* @defgroup X509CRL_sign_ex
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT32  X509CRL_sign_ex (SEC_PKEY_S* pstPrivateKey, X509_CRL_S*  pstCRL,
*                          SEC_UINT32 uiCtrlFlag, IPSI_AUX_PAR_S *pstAuxPar);
* @endcode
* @par Purpose
* To sign a CRL using the given private key.
* @par Description
* This function is extended feature of X509CRL_sign. The functionality is same as X509CRL_sign but it has some extra
* features supported. It has control flags as the input parameter which has define certain behaviour for this API. Currently 
* SEC_EC_NO_TRUNCATION is the only option available to this parameter.
* This function signs the CRL by a given private key.The signature is actually calculated on the hash computed on tbsCRL
* structure. The calculated signature value is then assigned to the signature field.
* Intially the given CRL is assumed to have a null signature value,if present will be overwritten with a new value
* The CRL issuer has to use the private key to sign the CRL.It is also necessary to make sure that the
* all the valid extensions are present, if any invalid extension is present then signing will not be a performed.
* If an invalid version is present then too the CRL will not be signed.
* The hash algorithm required for signing will be fetched internally from the algorithm identifier.Therefore it is necessary
* for the user to set the appropriate algorithm identifier.
*
* @param[in] pstPrivateKey The private key that is used to sign the CRL [N/A]
* @param[in] uiCtrlFlag Control flag is used to define the different operation. Currently only option available is 
* SEC_EC_NO_TRUNCATION. The control flag should be passed as 0 or SEC_EC_NO_TRUNCATION. 
* SEC_EC_NO_TRUNCATION is only valid for ECDSA and SM2DSA signing algorithm, for other algorithm
* application should pass 0.[N/A]
* @param[in] pstAuxPar This parameter is reserver for future use. Application can pass NULL. [N/A]
* @param[out] pstCRL A pointer to  CRL structure with all mandatory fields that is updated with new signature if signed
* successfully [N/A]
*
* @retval SEC_UINT32 If the argument is missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If encoding fails [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 If the signing is successful [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If it has an invalid version in the version field [SEC_ERR_INVALID_VERSION|N/A]
* @retval SEC_UINT32 If the signing operation failed [SEC_ERR_SIGNING_FAILED|N/A]
* @retval SEC_UINT32 If the given algorithm is not valid or if the key does not match with the given algorithm.
* [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_ERR_OID_MISMATCH If the signature algoritm field is different [N/A|N/A]
* @retval SEC_ERR_INVALID_EXTN If duplicates are there in the list or extension and entry extensions is not valid [N/A|N/A]
* @par Dependency
* x509.h
* @par Note
*   - For ALGID_SM2DSA signature, the pstPrivateKey should be a key pair i.e. public and private key should be
*      available in pstPrivateKey because public key will be used for the generation of ZA and private key
*      will be used for signature
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_UINT32  X509CRL_sign_ex (SEC_PKEY_S* pstPrivateKey, X509_CRL_S*  pstCRL,
                          SEC_UINT32 uiCtrlFlag, IPSI_AUX_PAR_S *pstAuxPar);



/**
* @defgroup IPSI_AR_enableCheckPointSupport
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT IPSI_AR_enableCheckPointSupport(SEC_VOID)
* @endcode
* @par Purpose
* To enable the checkpoint support ONLY FOR AR product.
* @par Description
* Enables the check point support.
* This API is provided for special operations only specific to AR product line. It is not advised to use by any other
* product as it does not have any value for them. If used, the behavior will be undefined
*
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT returns SEC_SUCCESS on success [SEC_INT|N/A]
* @retval SEC_INT returns SEC_ERROR on failure [SEC_INT|N/A]
*
* @par Dependency
* x509.h
* @par Note
*   - This API is provided for special operations only for AR product. It is not suggested or recommended to use by any
*      other products.
*   - This API is not multi-thread safe and should not be called in multiple threads. This API should be called at the time
*      of system initialization only once. Calling IPSI_AR_enableCheckPointSupport & IPSI_AR_disableCheckPointSupport
*      dynamically is not supported.
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/

PSELINKDLL SEC_INT IPSI_AR_enableCheckPointSupport(SEC_VOID);


/**
* @defgroup IPSI_AR_disableCheckPointSupport
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_UINT IPSI_AR_disableCheckPointSupport(SEC_VOID)
* @endcode
* @par Purpose
* To disable the checkpoint support ONLY FOR AR product.
* @par Description
* Disables the check point support.
* This API is provided for special operations only specific to AR product line. It is not advised to use by any other
* product as it does not have any value for them. If used, the behavior will be undefined
*
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT returns SEC_SUCCESS on success [SEC_INT|N/A]
* @retval SEC_INT returns SEC_ERROR on failure [SEC_INT|N/A]
*
* @par Dependency
* x509.h
* @par Note
*   - This API is provided for special operations only for AR product. It is not suggested or recommended to use by any
*      other products.
*   - This API is not multi-thread safe and should not be called in multiple threads. This API should be called at the time
*      once all operations are finished & no check point support is required. Calling
*      IPSI_AR_enableCheckPointSupport & IPSI_AR_disableCheckPointSupport dynamically is not supported.
* N/A
*
* @par Related Topics
* N/A
* 
* 
*/
PSELINKDLL SEC_INT IPSI_AR_disableCheckPointSupport(SEC_VOID);


/**
* @defgroup X509_getAttrFromNamePvtOID
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_AsnOcts_S* X509_getAttrFromNamePvtOID(SEC_AsnOid_S* pstPvtOID,
* SEC_NAME_S* pstName,
* SEC_UINT32* puiStringType
* );
* @endcode
* @par Purpose
* To extract the value of a particular attribute in the given name structure.
* @par Description
* This function returns the pointer to the Attribute value for a given OID present in the name structure.
* @param[in] pstPvtOID The OID that has to be searched in the name structure [N/A]
* @param[in] pstName The name from which the information has to be retrieved [N/A]
* @param[out] puiStringType The string type that is used to represent in the name structure [N/A]
* @retval SEC_AsnOcts_S* Pointer to the the Attribute value. The output parameter puiStringType specifies the
* string format used to represent the attribute string [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* On all unsuccessful conditions NULL is returned. The conditions can be one of the following:
* Any of the input parameters are NULL or OID is not present in Name [NULL|N/A]
* @par Dependency
* x509.h
*
* @par Memory Handling
* ipsi will not allocate the memory for the SEC_AsnOcts_S structure. Hence this memory should not be freed.
*
* @par Note
*
* 1. Support for Private OIDs is provided only for 'Subject Name' and 'Issuer Name' fileds of the X.509 Certificates.
*
* 2. This API and its related structures are enabled for only for CGP PDT on specific requirement. Users are not 
* allowed to use this API without contacting the VPP support team. If used, it leads to unresolved symbols.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* X509_getAttrFromNamePvtOID(SEC_AsnOid_S* pstPvtOID,
                                    SEC_NAME_S* pstName,
                                    SEC_UINT32* puiStringType);



/**
* @defgroup IPSI_X509_setCertAlgIdCheck
* @ingroup x509Functions
* @par Prototype
* @code
* SEC_VOID  IPSI_X509_setCertAlgIdCheck(SEC_INT iEnable);
* @endcode
*
* @par Purpose
* This is used to set or reset the check for matching AlgorithmIdentifier inside TBS and one in the
* certificate signature
* By default, this check will be enabled. 
*
* @par Description
* IPSI_X509_setCertAlgIdCheck function sets or resets the check for matching AlgorithmIdentifier inside TBS and one 
* in the certificate signature
*
* @param[in] iEnable 1 is passed to enable the check and 0 to disable the check. [0-1]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Required Header File
* x509.h
*
* @par Note
* \n
* This API should be used in the main thread, ie it should be called right after the library initialization.
*
*/
PSELINKDLL SEC_VOID  IPSI_X509_setCertAlgIdCheck(SEC_INT iEnable);

#ifdef __cplusplus
}
#endif


#endif /*_IPSI_x509_H*/





